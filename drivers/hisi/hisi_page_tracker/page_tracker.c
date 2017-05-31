/*
 *  linux/mm/page_tracker.c
 *
 *  This function record the owner of a page, the module which alloc page
 *  and the order of page on alloction. It will help to find bare
 *  alloc_page(s) leaks. Even if you include this feature on your build,
 *  it is disabled in default.
 */
#include <linux/module.h>
#include <linux/bootmem.h>
#include <linux/interrupt.h>
#include <linux/kthread.h>
#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/sched.h>
#include <linux/delay.h>
#include <linux/hisi/page_tracker.h>
#ifdef PGTRACK_TEST
#include <linux/ktime.h>
#endif

#if !defined(CONFIG_PAGE_EXTENSION)
struct page_ext *page_ext_map;
static inline struct page_ext *lookup_page_ext(struct page *page)
{
	return ((page - mem_map) + page_ext_map);
}
#endif

struct page_tracker_shadow {
	struct page_tracker *pgtracker;
	struct rb_node node;
	int pg_sum;
};

static bool page_tracker_disabled = true;
static int page_tracker_watermark[TRACK_MAX] = {
	1024,	/* SLAB 4M */
	1024,	/* LSLAB 4M */
	16,	    /* VMALLOC 64K*/
	32768,	/* FILE 128M*/
	32768,	/* ANON 128M*/
	0,	    /* ION */
	1024,	/* PROC 4M*/
	0,	    /* IRQ */
};
static struct page_tracker_manager {
		int sum;
		struct rb_root root;
} page_tracker_manager[TRACK_MAX];
static const char * const page_tracker_text[TRACK_MAX] = {
	"SLab Page Distribution:",
	"L-SLab Page Distribution:",
	"VMALLOC Page Distribution:",
	"FILE Page Distribution:",
	"ANON Page Distribution:",
	"ION Page Distribution:",
	"PROCESS Page Distribution:",
	"IRQ Page Distribution:",
};

static int early_page_tracker_param(char *buf)
{
	if (!buf)
		return -EINVAL;

	if (strcmp(buf, "on") == 0)
		page_tracker_disabled = false;

	return 0;
}
early_param("page_tracker", early_page_tracker_param);

void page_tracker_show(struct page *page, int order)
{
	struct page_ext *page_ext = NULL;

	if (page_tracker_disabled)
		return;

	if (!page)
		return;

	page_ext = lookup_page_ext(page);
	if (page_ext) {
		unsigned int order = page_ext->page_tracker.order;
		unsigned int head = page_ext->page_tracker.head;
		unsigned int type = page_ext->page_tracker.type;
		unsigned int pid = page_ext->page_tracker.pid;

		pr_err("[order] [head] [type] [pid] [trace]\n");
		pr_err("%8u%8u%8u%8u   %pF\n", order, type, head, pid,
			(void *)page_ext->page_tracker.trace);
	}
}

void page_tracker_set_trace(struct page *page, unsigned long func, int order)
{
	struct page_ext *page_ext = NULL;

	if (page_tracker_disabled)
		return;

	page_ext = lookup_page_ext(page);
	if (page_ext)
		page_ext->page_tracker.trace = func;
}

void page_tracker_set_type(struct page *page, int type, int order)
{
	struct page_ext *page_ext = NULL;

	if (page_tracker_disabled)
		return;

	page_ext = lookup_page_ext(page);
	if (page_ext)
		page_ext->page_tracker.type = type;
}

void page_tracker_set_tracker(struct page *page, int order)
{
	struct page_ext *page_ext = NULL;

	if (page_tracker_disabled)
		return;

	page_ext = lookup_page_ext(page);
	if (page_ext) {
		page_ext->page_tracker.order = (unsigned char)order;
		page_ext->page_tracker.head = (unsigned char)true;
		page_ext->page_tracker.type = TRACK_PROC;
		if (!in_interrupt())
			page_ext->page_tracker.pid = current->pid;
		else {
			page_ext->page_tracker.pid = 65535;
			page_ext->page_tracker.type = TRACK_IRQ;
		}
	}
}

void page_tracker_change_tracker(struct page *new_page,
					struct page *old_page)
{
	struct page_ext *page_old_ext = NULL;
	struct page_ext *page_new_ext = NULL;

	if (page_tracker_disabled)
		return;

	page_old_ext = lookup_page_ext(new_page);
	page_new_ext = lookup_page_ext(old_page);
	if (page_new_ext && page_old_ext) {
		page_new_ext->page_tracker.order =
			page_old_ext->page_tracker.order;
		page_new_ext->page_tracker.head =
			page_old_ext->page_tracker.head;
		page_new_ext->page_tracker.type =
			page_old_ext->page_tracker.type;
		page_new_ext->page_tracker.pid =
			page_old_ext->page_tracker.pid;
		page_new_ext->page_tracker.trace =
			page_old_ext->page_tracker.trace;

		page_old_ext->page_tracker.order = 0;
		page_old_ext->page_tracker.head = true;
		page_old_ext->page_tracker.type = TRACK_PROC;
		page_old_ext->page_tracker.pid = current->pid;
		page_old_ext->page_tracker.trace = _RET_IP_;
	}
}

void page_tracker_reset_tracker(struct page *page, int order)
{
	int nr = 1<<order;
	struct page_ext *page_ext = NULL;

	if (page_tracker_disabled)
		return;

	page_ext = lookup_page_ext(page);
	while(nr--) {
		page_ext->page_tracker.order = 0;
		page_ext->page_tracker.head = true;
		page_ext->page_tracker.pid = 65535;
		page_ext->page_tracker.type = TRACK_BUDDY;
		page_ext->page_tracker.trace = 0;
		page_ext++;
	}
}

#if !defined(CONFIG_PAGE_EXTENSION)
void alloc_node_tracker_map(void *p)
{
	pg_data_t *pgdat = (pg_data_t *)p;

	if (page_tracker_disabled)
		return;

	if (!pgdat->node_spanned_pages)
		return;

	if (!pgdat->node_page_ext) {
		unsigned long size, start, end;
		/*
		 * The zone's endpoints aren't required to be MAX_ORDER
		 * aligned but the node_mem_map endpoints must be in order
		 * for the buddy allocator to function correctly.
		 */
		start = pgdat->node_start_pfn & ~(MAX_ORDER_NR_PAGES - 1);
		end = pgdat_end_pfn(pgdat);
		end = ALIGN(end, MAX_ORDER_NR_PAGES);
		size =  (end - start) * sizeof(struct page_tracker);
		page_ext_map = alloc_bootmem_node_nopanic(pgdat, size);
		pgdat->node_page_ext = page_ext_map + (pgdat->node_start_pfn - start);
	}

}
#endif

void page_tracker_wake_up(void)
{
	int nid;

	if (page_tracker_disabled)
		return;

	for_each_node_state(nid, N_MEMORY)
			wake_up(&(NODE_DATA(nid)->ktracker_wait));
}

static void rbtree_init(void)
{
	int i;
	struct page_tracker_manager *man = &(page_tracker_manager[0]);

	for (i = 0; i < TRACK_MAX; i++) {
		man[i].root = RB_ROOT;
		man[i].sum = 0;
	}
}

static void insert_node
	(struct rb_root *root, struct page_tracker *pgtracker)
{
	struct page_tracker_shadow *shadow, *entry;
	struct rb_node **p = &(root->rb_node);
	struct rb_node *parent = NULL;

	while (*p) {
		parent = *p;
		entry = rb_entry(parent, struct page_tracker_shadow, node);

		if (pgtracker->pid < entry->pgtracker->pid)
			p = &(*p)->rb_left;
		else if (pgtracker->pid > entry->pgtracker->pid)
			p = &(*p)->rb_right;
		else {
			entry->pg_sum += (1<<pgtracker->order);
			return;
		}
	}

	shadow = kzalloc(sizeof(*shadow), GFP_KERNEL);
	if (shadow) {
		shadow->pg_sum = (1<<pgtracker->order);
		shadow->pgtracker = pgtracker;

		rb_link_node(&shadow->node, parent, p);
		rb_insert_color(&shadow->node, root);
	}
}

static void rbtree_kern_show(struct rb_root *root, int type)
{
	struct rb_node *n;

	for (n = rb_first(root); n; n = rb_next(n)) {
		struct page_tracker_shadow *shadow = rb_entry(n,
				struct page_tracker_shadow,
				node);
		struct task_struct *tsk =
			shadow->pgtracker->pid ?
				find_task_by_vpid(shadow->pgtracker->pid) :
						current;

			if (shadow->pg_sum > page_tracker_watermark[type])
				pr_info("%8u %s %8d\n", shadow->pgtracker->pid,
					(char *)(tsk ? tsk->comm : NULL),
					shadow->pg_sum);
	}
}

static void rbtree_user_show
	(struct rb_root *root, struct seq_file *s, int type)
{
	struct rb_node *n;

	for (n = rb_first(root); n; n = rb_next(n)) {
		struct page_tracker_shadow *shadow = rb_entry(n,
				struct page_tracker_shadow,
				node);
		struct task_struct *tsk =
			shadow->pgtracker->pid ?
				find_task_by_vpid(shadow->pgtracker->pid) :
				current;

		if (shadow->pg_sum > page_tracker_watermark[type])
			seq_printf(s, "%8u %s %8d\n",
					shadow->pgtracker->pid,
					(char *)(tsk ? tsk->comm : NULL),
					shadow->pg_sum);
	}
}

static void rbtree_destroy(struct rb_root *root)
{
	struct rb_node *n;

	if (!root)
		return;

	for (n = rb_first(root); n; n = rb_next(n)) {
		struct page_tracker_shadow *shadow = rb_entry(n,
				struct page_tracker_shadow,
				node);
		if (!RB_EMPTY_NODE(&shadow->node))
			rb_erase(&shadow->node, root);
		kfree(shadow);
	}

}

static int page_tracker_info_show(struct seq_file *s, void *unused)
{
	/*
	 * every mode show the page owner,like this:
	 * TRACK_SLAB total pages is xxx KB
	 *      xxxx KB  Pid xxx Name xxx
	 *       xxx KB  Pid xxx Name xxx
	 *        xx KB  Pid xxx Name xxx
	 * TRACK_VMALLOC total pages is xxx KB
	 *      xxxx KB  Pid xxx Name xxx
	 *       xxx KB  Pid xxx Name xxx
	 *        xx KB  Pid xxx Name xxx
	 * TRACK_FILE total pages is xxx KB
	 *      xxxx KB  Pid xxx Name xxx
	 *       xxx KB  Pid xxx Name xxx
	 *        xx KB  Pid xxx Name xxx
	 * TRACK_ANON total pages is xxx KB
	 *      xxxx KB  Pid xxx Name xxx
	 *       xxx KB  Pid xxx Name xxx
	 *        xx KB  Pid xxx Name xxx
	 * TRACK_ION total pages is xxx KB
	 *      xxxx KB  Pid xxx Name xxx
	 *       xxx KB  Pid xxx Name xxx
	 *        xx KB  Pid xxx Name xxx
	 * TRACK_PROC total pages is xxx KB
	 *      xxxx KB  Pid xxx Name xxx
	 *       xxx KB  Pid xxx Name xxx
	 *        xx KB  Pid xxx Name xxx
	 * TRACK_IRQ total pages is xxx KB
	 *      xxxx KB  hardirq xxx
	 *       xxx KB  hardirq xxx
	 *        xx KB  hardirq xxx
	 */
	int i;
	unsigned short nr;
	int nid;
	unsigned long buddy = 0;
	unsigned long total = 0;
	unsigned long reserved = 0;
	struct page_tracker_manager *man = &(page_tracker_manager[0]);

	if (page_tracker_disabled)
		return 0;

	for_each_node_state(nid, N_MEMORY) {
		int step;
		unsigned long flags;
		pg_data_t *pgdat = NODE_DATA(nid);
		unsigned long nd_pg = pgdat->node_spanned_pages;
		struct page *page;
		unsigned long pfn = pgdat->node_start_pfn;
		struct page_ext *page_ext = NULL;

		//drain_all_pages(NULL);

		/*
		 * build rb tree for page tracker
		 */
		rbtree_init();

		/*
		 * build rb tree
		 */
		pgdat_resize_lock(pgdat, &flags);
		for (i = 0; i < nd_pg;
				i += step, pfn += step) {
			step = 1;
			if (!pfn_valid(pfn))
				continue;

			page = pfn_to_page(pfn);
			if (PageReserved(page)) {
				reserved++;
				continue;
			}

			page_ext = lookup_page_ext(page);
			if (page_ext->page_tracker.type == TRACK_BUDDY) {
				buddy++;
				continue;
			}

			nr = page_ext->page_tracker.type;
			insert_node(&man[nr].root, &page_ext->page_tracker);
			man[nr].sum += (1 << page_ext->page_tracker.order);
			step = (1 << page_ext->page_tracker.order);
		}
		pgdat_resize_unlock(pgdat, &flags);

		/*
		 * show page rb tree
		 */
		seq_printf(s, "NODE-%d Page Distribution\n", pgdat->node_id);
		seq_printf(s, "Free Page %lu\n", buddy);
		seq_printf(s, "Reserved Page %lu\n", reserved);

		for (i = 0; i < TRACK_MAX; i++) {
			seq_printf(s, "%s %u\n",
				page_tracker_text[i],
						man[i].sum);
			total += man[i].sum;
			rbtree_user_show(&man[i].root, s, i);
		}
		seq_printf(s, "Total Page %lu\n", (total + buddy));
		/*
		 * destroy page rb tree
		 */
		for (i = 0; i < TRACK_MAX; i++)
			rbtree_destroy(&man[i].root);

	}

	return 0;
}

static int page_tracker_open(struct inode *inode, struct file *file)
{
	return single_open(file, page_tracker_info_show,
			PDE_DATA(file_inode(file)));
}

static const struct file_operations page_tracker_fops = {
	.open = page_tracker_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int ktrackerd(void *p)
{
	int i;
	int step;
	unsigned short nr;
	DEFINE_WAIT(wait);
	pg_data_t *pgdat = p;
	unsigned long buddy = 0;
	unsigned long nd_pg = pgdat->node_spanned_pages;
	struct page_tracker_manager *man = &(page_tracker_manager[0]);
	unsigned long pfn = pgdat->node_start_pfn;
	unsigned long flags;
	struct page *page;
	struct page_ext *page_ext = NULL;

	current->flags |= PF_MEMALLOC;

	do {
		pr_info("-----page tracker init----\n");

		prepare_to_wait(&pgdat->ktracker_wait, &wait, TASK_UNINTERRUPTIBLE);
		schedule();
		finish_wait(&pgdat->ktracker_wait, &wait);
		pr_info("****page tracker init****\n");

		buddy = 0;
		pfn = pgdat->node_start_pfn;

		rbtree_init();

		/*
		 * build rb tree
		 */
		pgdat_resize_lock(pgdat, &flags);
		for (i = 0; i < nd_pg;
				i += step, pfn += step) {
			step = 1;
			if (!pfn_valid(pfn))
				continue;

			page = pfn_to_page(pfn);
			if (PageReserved(page))
				continue;

			page_ext = lookup_page_ext(page);
			if (page_ext->page_tracker.type == TRACK_BUDDY) {
				buddy++;
				continue;
			}
			nr = page_ext->page_tracker.type;
			insert_node(&man[nr].root, &page_ext->page_tracker);
			man[nr].sum += (1 << page_ext->page_tracker.order);
			step = (1<<page_ext->page_tracker.order);

		}
		pgdat_resize_unlock(pgdat, &flags);

		pr_info("NODE-%d Page Distribution\n", pgdat->node_id);
		pr_info("Free Page %lu\n", buddy);

		for (i = 0; i < TRACK_MAX; i++) {
			pr_info("%s %u\n", page_tracker_text[i], man[i].sum);
			rbtree_kern_show(&man[i].root, i);
		}

		for (i = 0; i < TRACK_MAX; i++)
			rbtree_destroy(&man[i].root);

	} while (1);

	return 0;
}

#ifdef PGTRACK_TEST
static int ktrackerd_test_func(void *p)
{
	while (0) {
		struct page *pg = NULL;
		pg = alloc_pages((GFP_USER | __GFP_NOWARN | __GFP_COMP), 4);
		msleep(1000);
	}

	return 0;
}
#endif

static int creat_trackerd(int nid)
{
	int ret = 0;
	char kbuf[32];
	struct proc_dir_entry *entry = NULL;
	pg_data_t *pgdat = NODE_DATA(nid);

	if (pgdat->page_ktrackerd)
		return 0;

	/*
	 * 1. create page track info @ proc API
	 */
	ret = snprintf(kbuf, 32, "page-tracker%d", nid);
	if (ret >= 32)
		goto err;
	entry = proc_create_data(kbuf, 0400,
				 NULL, &page_tracker_fops, NULL);
	if (!entry)
		goto err;

	/*
	 * 2. every pgdata create tracked daemon
	 */
	init_waitqueue_head(&pgdat->ktracker_wait);
	pgdat->page_ktrackerd =
			kthread_run(ktrackerd, pgdat, "page-trackerd-%d", nid);
	if (IS_ERR(pgdat->page_ktrackerd)) {
		pr_err("Failed to start trackd on node %d\n", nid);
		ret = PTR_ERR(pgdat->page_ktrackerd);
		pgdat->page_ktrackerd = NULL;
		goto err;
	}

	return 0;
err:
	if (entry)
		proc_remove(entry);

	return ret;
}

#ifdef CONFIG_PAGE_EXTENSION
static bool need_page_tracker(void)
{
	if (page_tracker_disabled)
		return false;

	return true;
}

static void init_page_tracker(void)
{
	int nid;

	for_each_node_state(nid, N_MEMORY) {
		int i;
		unsigned long flags;
		pg_data_t *pgdat = NODE_DATA(nid);
		unsigned long nd_pg = pgdat->node_spanned_pages;
		struct page *page;
		unsigned long pfn = pgdat->node_start_pfn;
		struct page_ext *page_ext = NULL;

		pgdat_resize_lock(pgdat, &flags);
		for (i = 0; i < nd_pg; i++,pfn++) {
			if (!pfn_valid(pfn))
				continue;

			page = pfn_to_page(pfn);
			if (PageReserved(page))
				continue;

			page_ext = lookup_page_ext(page);
			page_ext->page_tracker.type = TRACK_BUDDY;
			page_ext->page_tracker.pid = 65535;
			page_ext->page_tracker.trace = 0;

		}
		pgdat_resize_unlock(pgdat, &flags);
	}

}

struct page_ext_operations page_tracker_ops = {
	.need = need_page_tracker,
	.init = init_page_tracker,
};
#endif

static int __init page_tracker_init(void)
{
	int nid;
	int ret = 0;
#ifdef PGTRACK_TEST
	struct task_struct *ktrackerd_test = NULL;
#endif

	if (page_tracker_disabled)
		return ret;

	for_each_node_state(nid, N_MEMORY) {
		if (creat_trackerd(nid))
			ret |= 1 << nid;
	}
	WARN_ON(ret);

#ifdef PGTRACK_TEST
	{
		ktrackerd_test =
			kthread_run(ktrackerd_test_func, NULL, "%s", "ktrackerd-test");
		if (IS_ERR(ktrackerd_test))
			ret = -1;
	}
#endif

	return ret;
}
late_initcall(page_tracker_init);

#ifdef PGTRACK_TEST
void page_tracker_test_alloc_free(int order)
{
	struct page *pg = NULL;
	ktime_t start_time, mid_time, end_time, delta1, delta2;

	start_time = ktime_get();
	pg = alloc_pages((GFP_USER | __GFP_NOWARN), order);
	mid_time = ktime_get();
	if (pg)
		__free_pages(pg, order);
	end_time = ktime_get();
	delta1 = ktime_sub(mid_time, start_time);
	delta2 = ktime_sub(end_time, mid_time);
	pr_err("page %pK\n", pg);
	pr_err("alloc time is %lld us\n",
		(long long)ktime_to_ns(delta1) >> 10);
	pr_err("free time is %lld us\n",
		(long long)ktime_to_ns(delta2) >> 10);
}

void page_tracker_test_wakeup(void)
{
	page_tracker_wake_up();
}
#endif
