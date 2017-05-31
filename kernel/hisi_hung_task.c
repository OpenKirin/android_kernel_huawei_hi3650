/*
 * Detect Hung Task
 *
 * kernel/hisi_hung_task.c - kernel thread for detecting tasks stuck in D state
 *
 */

#include <linux/mm.h>
#include <linux/cpu.h>
#include <linux/nmi.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/freezer.h>
#include <linux/kthread.h>
#include <linux/lockdep.h>
#include <linux/export.h>
#include <linux/sysctl.h>
#include <linux/utsname.h>
#include <trace/events/sched.h>

#include <huawei_platform/log/log_jank.h>
#include <linux/ptrace.h>
#include <linux/module.h>
#include <linux/sched.h>

#include <linux/proc_fs.h>
#include <linux/errno.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <asm/traps.h>

#ifdef CONFIG_HISI_BB
#include <linux/hisi/rdr_hisi_ap_hook.h>
#endif

#ifdef CONFIG_TZDRIVER
#include <linux/hisi/hisi_teeos.h>
#endif

#define NAME_NUM  16

#define ENABLE_SHOW_LEN 8UL
#define MAX_LIST_LEN 300UL

#define NOT_DEFINE 0
#define WHITE_LIST 1
#define BLACK_LIST 2


#define HT_ENABLE 1
#define HT_DISABLE 0

#define JANK_HUNG_TIMEOUT            3UL
#define JANK_HUNG_SHOWSTACK_COUNT    10
#define JANK_TASK_MAXNUM      8

/*
 * Limit number of tasks checked in a batch.
 *
 * This value controls the preemptibility of khungtaskd since preemption
 * is disabled during the critical section. It also controls the size of
 * the RCU grace period. So it needs to be upper-bound.
 */

#define HUNG_TASK_BATCHING 1024

/* storage names and last switch counts of process in D status */
struct tag_switch_count {
	pid_t p_pid;
	unsigned long last_swithc_count;
};

/* storage proccess list in hung task mechanism */
struct name_table {
	char name[TASK_COMM_LEN];
	pid_t p_pid;
};

struct tag_jankproc_info {
	unsigned long last_swithc_count;
	int pid;
	unsigned short nTickCount;
	bool bFound;
};
/*
 * The number of tasks checked:
 */
int __read_mostly sysctl_hung_task_check_count = PID_MAX_LIMIT;

/*
 * Zero means infinite timeout - no checking done:
 */
unsigned long __read_mostly sysctl_hung_task_timeout_secs = CONFIG_DEFAULT_HUNG_TASK_TIMEOUT;

int __read_mostly sysctl_hung_task_warnings = 10;

int __read_mostly did_panic;

static struct task_struct *watchdog_task;

/*
 * Should we panic (and reboot, if panic_timeout= is set) when a
 * hung task is detected:
 */
unsigned int __read_mostly sysctl_hung_task_panic =
				CONFIG_BOOTPARAM_HUNG_TASK_PANIC_VALUE;


static char p_name[TASK_COMM_LEN * NAME_NUM] = { 0 };
static struct name_table p_name_table[NAME_NUM];
static struct tag_switch_count last_switch_count_table[NAME_NUM];
static int jankproc_pids[JANK_TASK_MAXNUM];
static int jankproc_pids_size;
static int topapp_pid;
unsigned int hungtask_enable = HT_DISABLE;
unsigned int whitelist = BLACK_LIST;
struct tag_jankproc_info jankproc_switchcount[JANK_TASK_MAXNUM + 1];


/*
 * To avoid extending the RCU grace period for an unbounded amount of time,
 * periodically exit the critical section and enter a new one.
 *
 * For preemptible RCU it is sufficient to call rcu_read_unlock in order
 * to exit the grace period. For classic RCU, a reschedule is required.
 */
static bool rcu_lock_break(struct task_struct *g, struct task_struct *t)
{
	bool can_cont;

	get_task_struct(g);
	get_task_struct(t);
	rcu_read_unlock();
	cond_resched();
	rcu_read_lock();
	can_cont = pid_alive(g) && pid_alive(t);
	put_task_struct(t);
	put_task_struct(g);

	return can_cont;
}
static void find_pname_pid(int index)
{
	int max_count = sysctl_hung_task_check_count;
	int batch_count = HUNG_TASK_BATCHING;
	struct task_struct *g, *t;

	rcu_read_lock();
	/*lint -e50 -e1058 -e529 -e826 -e550 -e838 -esym(50,*) -esym(1058,*) -esym(529,*) -esym(826,*) -esym(550,*) -esym(838,*) */
	do_each_thread(g, t) {
	/*lint -e50 -e1058 -e529 -e826 -e550 -e838 +esym(50,*) +esym(1058,*) +esym(529,*) +esym(826,*) +esym(550,*) +esym(838,*) */
		if (!max_count--)
			goto unlock_f;
		if (!--batch_count) {
			batch_count = HUNG_TASK_BATCHING;
			if (!rcu_lock_break(g, t))
				goto unlock_f;
		}
		if (strlen(t->comm) == strlen(p_name_table[index].name))
			if (strncmp(p_name_table[index].name,
				    t->comm, strlen(t->comm)) == 0) {
				p_name_table[index].p_pid = t->pid;
				goto unlock_f;
			}
	} while_each_thread(g, t);
unlock_f:
	rcu_read_unlock();
}

static void find_pname(void)
{
	int i = 0;
	while ((i < NAME_NUM) && ('\0' != p_name_table[i].name[0])) {
		p_name_table[i].p_pid = -1;
		find_pname_pid(i);
		i++;
	}
}

int check_list(pid_t ht_pid, pid_t ht_ppid, unsigned int list_category)
{
	int i = 0;
	int in_list = 0;

	find_pname();

	if (WHITE_LIST == list_category) {
		while ((i < NAME_NUM) && (0 != p_name_table[i].p_pid)) {
			if ((p_name_table[i].p_pid == ht_pid)
			    || (p_name_table[i].p_pid == ht_ppid))
				in_list++;

			i++;
		}
	} else if (BLACK_LIST == list_category) {
		while ((i < NAME_NUM) && (0 != p_name_table[i].p_pid)) {
			if (p_name_table[i].p_pid == ht_pid)
				in_list++;

			i++;
		}
	}

	return in_list;
}
static void jank_print_task_wchan(struct task_struct *task)
{
	unsigned long wchan;
	char symname[KSYM_NAME_LEN];

	wchan = get_wchan(task);

	if (lookup_symbol_name(wchan, symname) < 0)
		if (!ptrace_may_access(task, PTRACE_MODE_READ_FSCREDS))
			return;
		else {
			printk(KERN_CONT "[<%08lx>]\n", wchan);
	} else {
		printk(KERN_CONT "[<%08lx>] %s\n", wchan, symname);
	}
}

static void jank_check_task(struct task_struct *t, unsigned long timeout,
			    int index)
{
	unsigned long switch_count = t->nvcsw + t->nivcsw;

	/*
	 * Ensure the task is not frozen.
	 * Also, skip vfork and any other user process that freezer should skip.
	 */
	if (unlikely(t->flags & (PF_FROZEN | PF_FREEZER_SKIP)))/*lint !e730 */
		return;

	if (unlikely(!switch_count)) {/*lint !e730 */
		jankproc_switchcount[index].last_swithc_count = switch_count;
		return;
	}

	if (switch_count != jankproc_switchcount[index].last_swithc_count) {
		jankproc_switchcount[index].last_swithc_count = switch_count;
		jankproc_switchcount[index].bFound = false;
		jankproc_switchcount[index].nTickCount = 0;
		return;
	}

	jankproc_switchcount[index].nTickCount++;

	LOG_JANK_D(JLID_KERNEL_HUNG_TASK, "#ARG1:<%s>#ARG2:<%d>", t->comm,
		   jankproc_switchcount[index].nTickCount * JANK_HUNG_TIMEOUT);

	if (jankproc_switchcount[index].nTickCount >= JANK_HUNG_SHOWSTACK_COUNT) {
		jankproc_switchcount[index].nTickCount = 0;
		/*hung_task_hook((void *)t, (u32)timeout);*/
		sched_show_task(t);

		debug_show_held_locks(t);
	} else if (!jankproc_switchcount[index].bFound) {
		jank_print_task_wchan(t);
		jankproc_switchcount[index].bFound = true;
	}
} /*lint !e715 */

static void jank_fresh_tasks(void)
{
	int i = 0;
	int tempPid;

	tempPid = topapp_pid;
	if (tempPid != jankproc_switchcount[0].pid) {
		jankproc_switchcount[0].pid = tempPid;
		jankproc_switchcount[0].bFound = false;
		jankproc_switchcount[0].last_swithc_count = 0;
		jankproc_switchcount[0].nTickCount = 0;
	}

	while ((i < JANK_TASK_MAXNUM) && (i < jankproc_pids_size)) {
		tempPid = jankproc_pids[i];
		/*lint -save -e679 */
		if (tempPid != jankproc_switchcount[i + 1].pid) {
			jankproc_switchcount[i + 1].pid = tempPid;
			jankproc_switchcount[i + 1].bFound = false;
			jankproc_switchcount[i + 1].last_swithc_count = 0;
			jankproc_switchcount[i + 1].nTickCount = 0;
		}
		/*lint -restore */
		i++;
	}
}

static int jank_get_tasks_index(pid_t pid)
{
	int i = 0;

	while ((i <= JANK_TASK_MAXNUM) && (i <= jankproc_pids_size)) {
		if (jankproc_switchcount[i].pid == pid)
			return i;
		i++;
	}

	return -1;
}

/*
 * Check whether a TASK_UNINTERRUPTIBLE does not get woken up for
 * a really short time (3 seconds).
 */
void jank_check_uninterruptible_tasks(unsigned long timeout)
{
	int idx = -1;
	int max_count = sysctl_hung_task_check_count;
	int batch_count = HUNG_TASK_BATCHING;
	struct task_struct *g, *t;

	/*
	 * If the system crashed already then all bets are off,
	 * do not report extra hung tasks:
	 */
	if (test_taint(TAINT_DIE) || did_panic)
		return;

	jank_fresh_tasks();

	rcu_read_lock();
	/*lint -e50 -e1058 -e529 -e826 -e550 -e838 -esym(50,*) -esym(1058,*) -esym(529,*) -esym(826,*) -esym(550,*) -esym(838,*) */
	do_each_thread(g, t) {
	/*lint -e50 -e1058 -e529 -e826 -e550 -e838 +esym(50,*) +esym(1058,*) +esym(529,*) +esym(826,*) +esym(550,*) +esym(838,*) */
		if (!max_count--)
			goto unlock;
		if (!--batch_count) {
			batch_count = HUNG_TASK_BATCHING;
			if (!rcu_lock_break(g, t))
				goto unlock;
		}
		/* use "==" to skip the TASK_KILLABLE tasks waiting on NFS */
		if (NULL != t->mm && t->state == TASK_UNINTERRUPTIBLE) {
			idx = jank_get_tasks_index(t->pid);
			if (idx >= 0)
				jank_check_task(t, timeout, idx);
		}
	} while_each_thread(g, t);
unlock:
	rcu_read_unlock();
}

static ssize_t enable_show(struct kobject *kobj, struct kobj_attribute *attr,
			   char *buf)
{
	if (hungtask_enable)
		return snprintf(buf, ENABLE_SHOW_LEN, "on\n");
	else
		return snprintf(buf, ENABLE_SHOW_LEN, "off\n");
} /*lint !e715 */

static ssize_t enable_store(struct kobject *kobj,
			    struct kobj_attribute *attr, const char *buf,
			    size_t count)
{
	char tmp[6];
	size_t len;
	char *p;

	if ((count < 2) || (count > (sizeof(tmp) - 1))) {
		pr_err("hung_task: string too long or too short.\n");
		return -EINVAL;
	}

	p = memchr(buf, '\n', count);
	len = p ? (size_t)(p - buf) : count;

	memset(tmp, 0, sizeof(tmp));
	strncpy(tmp, buf, len);
	pr_err("hung_task:tmp=%s, count %d\n", (char *)tmp, (int)count);

	if (strncmp(tmp, "on", strlen(tmp)) == 0) {
		hungtask_enable = HT_ENABLE;
		pr_err("hung_task: hungtask_enable is set to enable.\n");
	} else if (strncmp(tmp, "off", strlen(tmp)) == 0) {
		hungtask_enable = HT_DISABLE;
		pr_err("hung_task: hungtask_enable is set to disable.\n");
	} else
		pr_err("hung_task: only accept on or off !\n");

	return (ssize_t) count;
} /*lint !e715 */

/*
*	monitorlist_show  -	Called when 'cat' method
*	is used on entry 'pname' in /proc fs.
*	most of the parameters is created by kernel.
*/
static ssize_t monitorlist_show(struct kobject *kobj,
				struct kobj_attribute *attr, char *buf)
{
	char *start = buf;

	if (whitelist == WHITE_LIST)
		buf += snprintf(buf, MAX_LIST_LEN, "whitelist: [%s]\n", p_name);
	else if (whitelist == BLACK_LIST)
		buf += snprintf(buf, MAX_LIST_LEN, "blacklist: [%s]\n", p_name);
	else
		buf += snprintf(buf, MAX_LIST_LEN, "\n");

	return buf - start;
} /*lint !e715 */

/* storage proccess names in [pname] to
 * [pname_table], and return the numbers of process
 */
static size_t rebuild_name_table(char *pname, size_t pname_len)
{
	size_t count = 0;
	int proc_name_len;
	const char *curr = pname;
	char *curr_table;
	int idx = 0;
	int detected = 0;

	whitelist = NOT_DEFINE;

	/* reset the table to empty */

	memset(p_name_table, 0x00, sizeof(p_name_table));

	while ('\0' != *curr && pname_len) {
		/* proccess names are seperated by comma */
		while ((',' == *curr) && pname_len) {
			curr++;
			pname_len--;
		}

		/* check if the number of proccess exceed the limit,
		 * pointer [curr] not an end symbol indicates
		 * that the after [NAME_NUM] proccess,
		 * the [NAME_NUM + 1]th proccess was found
		 */
		if ((size_t)NAME_NUM == count && '\0' != *curr)
			goto err_proc_num;

		/* if the user input [NAME_NUM] proccess name,
		 * but just end his input by a space or comma,
		 * we just jump out the loop
		 */
		if ((size_t)NAME_NUM == count)
			break;

		/* the [count]th name should be storage in corresponding
		 * item in table, and [proc_name_len] is set to count
		 * the length of process name
		 */
		proc_name_len = 0;
		curr_table = p_name_table[count].name;

		while (',' != *curr && '\0' != *curr && pname_len) {
			*curr_table = *curr;
			curr_table++;
			curr++;
			proc_name_len++;

			/* check if the length of
			 * proccess name exceed the limit
			 */
			if (TASK_COMM_LEN == proc_name_len)
				goto err_proc_name;
			pname_len--;
		}
		*curr_table = '\0';

		if ((count == 0) && (detected == 0)) {
			detected++;
			if (strncmp(p_name_table[0].name, "whitelist",
				    strlen(p_name_table[0].name)) == 0) {
				pr_err("hung_task:set to whitelist.\n");
				whitelist = WHITE_LIST;
				continue;
			} else if (strncmp(p_name_table[0].name, "blacklist",
					   strlen(p_name_table[0].name)) == 0) {
				whitelist = BLACK_LIST;
				pr_err("hung_task:set to blacklist.\n");
				continue;
			} else {
				whitelist = BLACK_LIST;
				pr_err("hung_task:default is  blacklist.\n");
			}
		}
		pr_err("\nhung_task: name_table: 0x%lx, %s,name_len: %d\n",
		       count, p_name_table[count].name, proc_name_len);

		/* count how many proccess,
		 * only when [proc_name_len] is not zero,
		 * one new proccess was added into [pname_table]
		 */
		if (proc_name_len)
			count++;
	}
	/*last_switch_count_table  reset */
	for (idx = 0; idx < NAME_NUM; idx++) {
		last_switch_count_table[idx].p_pid = 0;
		last_switch_count_table[idx].last_swithc_count = 0;
	}

	return count;

err_proc_name:
	memset(p_name_table, 0x00, sizeof(p_name_table));
	memset(pname, 0x00, pname_len);
	pr_err("hung_task: rebuild_name_table: Error: process name");
	pr_err(" is invallid, set monitorlist failed.\n");

	return 0;

err_proc_num:
	/* more than 16 processes,remove it */
	pr_err("hung_task: rebuild_name_table: Warnig: too many ");
	pr_err("processess, leave it and do nothing.\n");
	return count;
}

/* since the proccess name written into [pname_table]
 * may be different from original input,
 * [p_name] should be modified to adjust [pname_table]
 */
static int modify_pname(size_t num_count)
{
	unsigned long i;
	int len_count;
	size_t tlen;

	memset((void *)p_name, 0x00, sizeof(p_name));

	for (i = 0; i < num_count; i++) {
		tlen = strlcat(p_name, p_name_table[i].name, sizeof(p_name));
		if (tlen >= sizeof(p_name))
			return -ENAMETOOLONG;

		/* seperate different proccess by a comma and a space */
		if (i != num_count - 1) {
			tlen = strlcat(p_name, ",", sizeof(p_name));
			if (tlen >= sizeof(p_name))
				return -ENAMETOOLONG;
		}
	}
	len_count = (int)strlen(p_name);
	return len_count;
}

/*
*	monitorlist_store	-  Called when 'write/echo' method is
*	used on entry '/sys/kernel/hungtask/monitorlist'.
*/
static ssize_t monitorlist_store(struct kobject *kobj,
				 struct kobj_attribute *attr, const char *buf,
				 size_t n)
{
	size_t len;
	char *p;
	size_t num_count;
	int ret;

	p = memchr(buf, '\n', n);
	len = p ? (size_t)(p - buf) : n;

	if ((len < 2) || (len > (sizeof(p_name) - 1))) {
		pr_err("hung_task: input string is too long or too short\n");
		return -EINVAL;
	}

	/* reset p_name to NULL */
	memset(p_name, 0x00, sizeof(p_name));

	/* -1: remove '\n'      */
	strncpy(p_name, buf, len);

	/* convert [p_name] to a table [p_name_table],
	 * and refresh the buffer [p_name]
	 */
	num_count = rebuild_name_table(p_name, len);
	ret = modify_pname(num_count);

	if (ret < 0)
		return -EFAULT;

	return (ssize_t)n;
} /*lint !e715 */

static int __init hung_task_panic_setup(char *str)
{
	int rc = kstrtouint(str, 0, &sysctl_hung_task_panic);

	if (rc)
		return rc;
	return 1;
}
__setup("hung_task_panic=", hung_task_panic_setup);

static int hung_task_panic(struct notifier_block *this, unsigned long event, void *ptr)
{
	did_panic = 1;

	return NOTIFY_DONE;
} /*lint !e715 */

static struct notifier_block panic_block = {
	.notifier_call = hung_task_panic,
};/*lint !e785 */

static void check_hung_task(struct task_struct *t, unsigned long timeout)
{
	unsigned long switch_count = t->nvcsw + t->nivcsw;
	int idx, first_empty_item = -1;
	int in_list;
	unsigned int list_category = whitelist;
	pid_t ht_pid, ht_ppid;

	/*
	 * Ensure the task is not frozen.
	 * Also, skip vfork and any other user process that freezer should skip.
	 */
	if (unlikely(t->flags & (PF_FROZEN | PF_FREEZER_SKIP)))/*lint !e730 */
	    return;

	/*
	 * When a freshly created task is scheduled once, changes its state to
	 * TASK_UNINTERRUPTIBLE without having ever been switched out once, it
	 * musn't be checked.
	 */
	if (unlikely(!switch_count))/*lint !e730 */
		return;

	if (NOT_DEFINE == list_category)
		return;

	if ((WHITE_LIST == list_category) && ('\0' == p_name_table[0].name[0]))
		return;

#ifdef CONFIG_TZDRIVER
	if (is_tee_hungtask(t)) {
	    pr_info("hungtask related to teeos was detected, dump status of teeos\n");
	    wakeup_tc_siq();
	}
#endif

	ht_pid = t->pid;
	ht_ppid = t->tgid;

	in_list = check_list(ht_pid, ht_ppid, list_category);

	if (0 == in_list) {
		if (WHITE_LIST == list_category) {
			pr_info("hung_task: %s NOT in whitelist.\n", t->comm);
			return;
		}
	} else {
		if (BLACK_LIST == list_category) {
			pr_err("hung_task: %s is in blacklist.\n", t->comm);
			return;
		}
		pr_err("hung_task: %s is in whitelist.\n", t->comm);
	}

	/* find last swich count record in last_switch_count_table */
	for (idx = 0; idx < NAME_NUM; idx++) {
		if (0 == last_switch_count_table[idx].p_pid) {
			if (-1 == first_empty_item)
				first_empty_item = idx;
		} else {
			if (last_switch_count_table[idx].p_pid == ht_pid)
				break;
		}
	}

	/* if current proccess is not in last switch count table,
	 * insert a new record
	 */
	if (NAME_NUM == idx) {
		if (first_empty_item == -1)
			return;
		last_switch_count_table[first_empty_item].p_pid = ht_pid;
		last_switch_count_table[first_empty_item].last_swithc_count = 0;
		idx = first_empty_item;
	}

	if (switch_count != last_switch_count_table[idx].last_swithc_count) {
		last_switch_count_table[idx].last_swithc_count = switch_count;
		return;
	}

	trace_sched_process_hang(t);

	if (!sysctl_hung_task_warnings)
		return;

	if (sysctl_hung_task_warnings > 0)
		sysctl_hung_task_warnings--;

#ifdef CONFIG_HUAWEI_PRINTK_CTRL
	printk_level_setup(LOGLEVEL_DEBUG);
#endif
	/*
	 * Ok, the task did not get scheduled for more than 2 minutes,
	 * complain:
	 */
	pr_err("INFO: task %s:%d blocked for more than %ld seconds.\n",
		t->comm, t->pid, timeout);
#ifdef CONFIG_HISI_BB
	hung_task_hook((void *)t, (u32) sysctl_hung_task_timeout_secs);
#endif
	pr_err("      %s %s %.*s\n",
		print_tainted(), init_utsname()->release,
		(int)strcspn(init_utsname()->version, " "),
		init_utsname()->version);
	pr_err("\"echo 0 > /proc/sys/kernel/hung_task_timeout_secs\""
		" disables this message.\n");
	sched_show_task(t);
	debug_show_held_locks(t);

	touch_nmi_watchdog();

	show_state_filter(TASK_UNINTERRUPTIBLE);/*lint !e747 */
#ifdef CONFIG_HUAWEI_PRINTK_CTRL
	printk_level_setup(sysctl_printk_level);
#endif
	if (sysctl_hung_task_panic) {
		trigger_all_cpu_backtrace();
		panic("hung_task: blocked tasks");
	}
}

/*
 * Check whether a TASK_UNINTERRUPTIBLE does not get woken up for
 * a really long time (120 seconds). If that happens, print out
 * a warning.
 */
static void check_hung_uninterruptible_tasks(unsigned long timeout)
{
	int max_count = sysctl_hung_task_check_count;
	int batch_count = HUNG_TASK_BATCHING;
	struct task_struct *g, *t;

	/*
	 * If the system crashed already then all bets are off,
	 * do not report extra hung tasks:
	 */
	if (test_taint(TAINT_DIE) || did_panic)
		return;

	rcu_read_lock();
	/*lint -e50 -e1058 -e529 -e826 -e550 -e64 -esym(50,*) -esym(1058,*) -esym(529,*) -esym(826,*) -esym(550,*) -esym(64,*) */
	for_each_process_thread(g, t) {
	/*lint -e50 -e1058 -e529 -e826 -e550 -e64 +esym(50,*) +esym(1058,*) +esym(529,*) +esym(826,*) +esym(550,*) +esym(64,*) */
		if (!max_count--)
			goto unlock;
		if (!--batch_count) {
			batch_count = HUNG_TASK_BATCHING;
			if (!rcu_lock_break(g, t))
				goto unlock;
		}
		/* use "==" to skip the TASK_KILLABLE tasks waiting on NFS */
		if (t->state == TASK_UNINTERRUPTIBLE)
			check_hung_task(t, timeout);
	}
 unlock:
	rcu_read_unlock();
}

static unsigned long timeout_jiffies(unsigned long timeout)
{
	/* timeout of 0 will disable the watchdog */
	return timeout ? timeout * HZ : MAX_SCHEDULE_TIMEOUT;
}

/*
 * Process updating of timeout sysctl
 */
int proc_dohung_task_timeout_secs(struct ctl_table *table, int write,
				  void __user *buffer,
				  size_t *lenp, loff_t *ppos)
{
	int ret;

	ret = proc_doulongvec_minmax(table, write, buffer, lenp, ppos);

	if (ret || !write)
		goto out;

	wake_up_process(watchdog_task);

 out:
	return ret;
}

static atomic_t reset_hung_task = ATOMIC_INIT(0);

void reset_hung_task_detector(void)
{
	atomic_set(&reset_hung_task, 1);
}
EXPORT_SYMBOL_GPL(reset_hung_task_detector);

/*
 * kthread which checks for tasks stuck in D state
 */
static int watchdog(void *dummy)
{
	unsigned long substep_timeout = JANK_HUNG_TIMEOUT;
	unsigned long sum_timeout;
	unsigned long timeout;

	set_user_nice(current, 0L);

	for ( ; ; ) {
		timeout = sysctl_hung_task_timeout_secs;
		sum_timeout = 0;
		while (sum_timeout < timeout) {
			while (schedule_timeout_interruptible(
					(long)timeout_jiffies(substep_timeout))) {
				timeout = sysctl_hung_task_timeout_secs;
				sum_timeout = 0;
			}
			sum_timeout += substep_timeout;
			if (jankproc_pids_size > 0 || topapp_pid > 0)
				jank_check_uninterruptible_tasks(substep_timeout);
		}

		/*lint -e1072 -e747 -e50 -esym(1072,*) -esym(747,*) -esym(50,*) */
		if (atomic_xchg(&reset_hung_task, 0))
		/*lint -e1072 -e747 -e50 +esym(1072,*) +esym(747,*) +esym(50,*) */
			continue;
		if (hungtask_enable)
			check_hung_uninterruptible_tasks(timeout);
	}
	return 0;/*lint !e527 */
} /*lint !e715 */



static struct kobj_attribute timeout_attribute = {
	.attr = {
		 .name = "enable",
		 .mode = 0640,
		 },
	.show = enable_show,
	.store = enable_store,
};

static struct kobj_attribute monitorlist_attr = {
	.attr = {
		 .name = "monitorlist",
		 .mode = 0640,
		 },
	.show = monitorlist_show,
	.store = monitorlist_store,
};

static struct attribute *attrs[] = {
	&timeout_attribute.attr,
	&monitorlist_attr.attr,
	NULL
};

static struct attribute_group hungtask_attr_group = {
	.attrs = attrs,
};/*lint !e785 */

struct kobject *hungtask_kobj;

int create_sysfs_hungtask(void)
{
	int retval;
	/* wait for kernel_kobj node ready: */
	while (kernel_kobj == NULL)
		msleep(1000);

	/* Create kobject named "hungtask",located under /sys/kernel/ */
	hungtask_kobj = kobject_create_and_add("hungtask", kernel_kobj);
	if (!hungtask_kobj)
		return -ENOMEM;

	/* Create the files associated with this kobject */
	retval = sysfs_create_group(hungtask_kobj, &hungtask_attr_group);
	if (retval)
		kobject_put(hungtask_kobj);
	return retval;
}

static int __init hung_task_init(void)
{
	int ret;

	ret = create_sysfs_hungtask();
	if (ret)
		pr_err("hung_task: create_sysfs_hungtask fail.\n");

	atomic_notifier_chain_register(&panic_notifier_list, &panic_block);
	watchdog_task = kthread_run(watchdog, NULL, "khungtaskd");

	return 0;
}
subsys_initcall(hung_task_init);

/*lint -e21 -e708 -e753 -e528 -e846 -e514 -e866 -e30 -e84 -e665 -e846 -e778
    -esym(21,*) -esym(708,*) -esym(753,*) -esym(528,*) -esym(846,*) -esym(514,*)
    -esym(866,*) -esym(30,*) -esym(84,*) -esym(665,*) -esym(846,*) -esym(778,*) */
module_param_array_named(jankproc_pids, jankproc_pids, int, &jankproc_pids_size,
			 (S_IRUGO | S_IWUSR));

MODULE_PARM_DESC(jankproc_pids, "jankproc_pids state");
module_param_named(topapp_pid, topapp_pid, int, (S_IRUGO | S_IWUSR));
/*lint -e21 -e708 -e753 -e528 -e846 -e514 -e866 -e30 -e84 -e665 -e846 -e778
    +esym(21,*) +esym(708,*) +esym(753,*) +esym(528,*) +esym(846,*) +esym(514,*)
    +esym(866,*) +esym(30,*) +esym(84,*) +esym(665,*) +esym(846,*) +esym(778,*) */

