/************************************************************************

  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 *************************************************************************
 �� �� ��		: eeye_ftrace.c
 �� �� ��		: ����
 ��    ��		: ��Тΰ j00207786
 ��������	: 2016��5��3��
 ����޸�	:
 ��������	: ftrace��̬Ԥ����¼
				:
 �޸���ʷ	:
 1.��  ��		: 2016��5��3��
    ��  ��		: ��Тΰ j00207786
    �޸�����	: �����ļ�

 *************************************************************************/

/*************************************************************************
  1 ͷ�ļ�����
 *************************************************************************/
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/thread_info.h>
#include <linux/hardirq.h>
#include <linux/uaccess.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/preempt.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/rtc.h>
#include <asm/sections.h>
#include <linux/vmalloc.h>
#include <linux/bitmap.h>
#include <linux/bitops.h>
#include <linux/dma-direction.h>
#include <asm/cacheflush.h>
#include <asm/cachetype.h>

#include <linux/hisi/util.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/rdr_hisi_ap_ringbuffer.h>
#include <linux/hisi/eagle_eye.h>
#include <linux/hisi/eeye_ftrace_pub.h>
#include <mntn_public_interface.h>
#include <linux/hisi/mntn_dump.h>
#include "eeye_ftrace.h"
#include "../../../../kernel/trace/trace.h"

unsigned char *g_ftrace_buffer_addr;
static unsigned int g_buffer_head_size;
static unsigned int g_ftrace_buffer_size;
static unsigned long g_ftrace_buffer_lifetime =
	FTRACE_BUFFER_LIFETIME * NSEC_PER_SEC;
static bool ftrace_buffer_init_done;
static bool mntn_ftrace_enabled;

/*��ʾftrace�����Ƿ���ע��*/
static bool g_eeye_ftrace_register;

/*���ڿ���BUF_B�ļ�¼����*/
static bool g_eeye_ftrace_tracing_on;

/*mntn dumpʹ��*/
static FTRACE_MDUMP_HEAD *g_ftrace_mdump_head;

static int max_ksym_len;

static unsigned long g_ftrace_buffer_size_tbl[HK_FTRACE_BUF_MAX] = {
	AP_TRACE_FTRACE_BUF_A_SIZE,
	AP_TRACE_FTRACE_BUF_B_SIZE,
	AP_TRACE_FTRACE_BUF_Z_SIZE
};

static const char g_ftrace_pattern[] =
	"ftrace::tsk,pid,cpu,flg,p,ktime,ip,r_ip";

static DEFINE_SEMAPHORE(save_fbin_sem);

/*��Ƕ�Ӧcpu��percpu buffer�Ƿ�������Է�ѭ��buffer*/
static DECLARE_BITMAP(is_percpu_buffer_full, NR_CPUS) __read_mostly;

static LIST_HEAD(eeye_ftrace_bin_list);
static DEFINE_SPINLOCK(g_eeye_ftrace_bin_list_lock);

struct linux_dirent {
	unsigned long d_ino;
	unsigned long d_off;
	unsigned short d_reclen;
	char d_name[1];
};

enum ftrace_buf_state {
	BUFFER_NOT_FULL = 0,
	BUFFER_FULL = 1,
	INVALID_QUERY = -1,
};

static void eeye_ftrace_register_func(struct work_struct *work);
static DECLARE_DELAYED_WORK(eeye_ftrace_register_work,
			    eeye_ftrace_register_func);

static void eeye_save_kallsyms_func(struct work_struct *work);
static DECLARE_DELAYED_WORK(eeye_save_kallsyms_work,
			    eeye_save_kallsyms_func);
/*************************************************************************
Function:		set_ftrace_buffer_lifetime
Description:	����ftrace buffer�ı�����С�����
Input:		lifetime: buffer����Ϊ�ļ�����С���ʱ�䣬��λ�룻
Return:		NA
Author:		j00207786
*************************************************************************/
void set_ftrace_buffer_lifetime(unsigned long lifetime)
{
	g_ftrace_buffer_lifetime = lifetime * NSEC_PER_SEC;
}

/*************************************************************************
Function:		ftrace_buffer_alloc
Description:	����ftrace��¼ʹ�õ��ڴ棬����ʼ��buffer������ͷ��
Input:		NA��
Return:		0����ʼ���ɹ�����0����ʼ��ʧ�ܣ�
Author:		j00207786
*************************************************************************/
static int ftrace_buffer_alloc(void)
{
	size_t sum_size = 0;

	if (g_ftrace_buffer_addr) {
		pr_err(
		       "%s, g_ftrace_buffer_addr has been initialized!\n",
		       __func__);
		return 0;
	}
	g_buffer_head_size = ALIGN(sizeof(struct ftrace_root), sizeof(u64)) +
	    HK_FTRACE_BUF_MAX * ALIGN(sizeof(struct ftrace_buffer_head),
				      sizeof(u64));

	sum_size += g_buffer_head_size;

	if (g_buffer_head_size > AP_TRACE_FTRACE_HEAD_MAX_SIZE) {
		pr_err("%s, g_buffer_head_size is greater than AP_TRACE_FTRACE_HEAD_MAX_SIZE [0x%x] !\n",
		       __func__, AP_TRACE_FTRACE_HEAD_MAX_SIZE);
		return -1;
	}

	sum_size = sum_size + AP_TRACE_FTRACE_BUF_A_SIZE +
	    AP_TRACE_FTRACE_BUF_B_SIZE + AP_TRACE_FTRACE_BUF_Z_SIZE;

	sum_size = ALIGN(sum_size, PAGE_SIZE);

	g_ftrace_buffer_addr = kzalloc(sum_size, GFP_KERNEL);
	if (!g_ftrace_buffer_addr) {
		pr_err("%s, kzalloc size [0x%lx] failed!\n", __func__,
		       sum_size);
		return -1;
	}
	g_ftrace_buffer_size = sum_size;
	pr_err("%s, success!g_ftrace_buffer_addr [0x%pK]\n",
	       __func__, g_ftrace_buffer_addr);
	return 0;
}

/*************************************************************************
Function:		print_all_ftrace_buffer_info
Description:	����ftrace��¼ʹ�õ��ڴ棬����ʼ��buffer������ͷ��
Input:		NA��
Return:		NA;
Author:		j00207786
*************************************************************************/
void print_all_ftrace_buffer_info(void)
{
	int i;
	struct ftrace_buffer_head **finfo;

	if (!g_ftrace_buffer_addr) {
		pr_err("%s, g_ftrace_buffer_addr is null!\n",
		       __func__);
		return;
	}

	if (!ftrace_buffer_init_done) {
		pr_err("%s, ftrace_buffer_init_done is false!\n",
		       __func__);
		return;
	}

	finfo = ((struct ftrace_root *)g_ftrace_buffer_addr)->finfo;
	for (i = 0; i < HK_FTRACE_BUF_MAX; i++) {
		pr_err("%s, finfo[%d] [0x%pK]!\n", __func__, i,
		       finfo[i]);
		pr_err("%s, BUF[%d] buffer_addr[0x%llx] buffer_len[0x%llx]\n",
		       __func__, i, finfo[i]->buffer_addr,
			   finfo[i]->buffer_len);
		pr_err("%s, is_percpu [%d] is_loop [%d] is_inuse [%d]!\n",
		       __func__, finfo[i]->is_percpu, finfo[i]->is_loop,
		       finfo[i]->is_inuse);
	}
}

/*************************************************************************
Function:		ftrace_buffer_head_init
Description:	ftrace�켣��¼������ͷ�ĳ�ʼ��
Input:		buffer_info:����ʼ������ͷָ�룻
			buffer_addr:buffer��ַ��������buffer_info��
			idx:buffer��ţ�size:buffer��С��
			is_percpu:buffer�Ƿ�percpu����;
			is_loop:buffer�Ƿ�ѭ����¼;
Return:		0����ʼ���ɹ�����0����ʼ��ʧ�ܣ�
Author:		j00207786
*************************************************************************/
static int ftrace_buffer_head_init(struct ftrace_buffer_head *buffer_info,
				   unsigned char *buffer_addr, u8 idx,
				   unsigned int size, bool is_percpu,
				   bool is_loop)
{
	struct ftrace_buffer_head *finfo;
	u32 cpu_num = num_possible_cpus();
	int cacheline_size;

	/*
	   ��Ϊbuffer�����������֧�����8��cpu�ļܹ���
	   ��һ�б�ʾ��cpu�ܹ����ڰ��д���8�˼ܹ���
	   buffer����Ϊ16�ȷݣ�ÿһ���е���ֵ�����ң�
	   �ֱ����cpu0-n��ռ�ı�����
	 */
	unsigned int ftrace_record_ratio[8][8] = {
		{16, 0, 0, 0, 0, 0, 0, 0},
		{8, 8, 0, 0, 0, 0, 0, 0},
		{8, 4, 4, 0, 0, 0, 0, 0},
		{8, 4, 2, 2, 0, 0, 0, 0},
		{4, 4, 4, 2, 2, 0, 0, 0},
		{4, 4, 2, 2, 2, 2, 0, 0},
		{4, 4, 2, 2, 2, 1, 1, 0},
		{3, 3, 3, 3, 1, 1, 1, 1}
	};

	preempt_disable();
	cacheline_size = icache_get_linesize();
	preempt_enable();
	pr_err("%s, cacheline_size is [%d]!\n", __func__,
	       cacheline_size);

	if (IS_ERR_OR_NULL(buffer_info)) {
		pr_err("%s, buffer_info is invalid!\n", __func__);
		return -1;
	}

	if (IS_ERR_OR_NULL(buffer_addr)) {
		pr_err("%s, buffer_addr is invalid!\n", __func__);
		return -1;
	}

	pr_err("%s, cpu_num [%d]!\n", __func__, cpu_num);

	finfo = buffer_info;
	INIT_LIST_HEAD(&finfo->list);
	finfo->idx = idx;
	finfo->reason = -1;
	finfo->is_inuse = false;
	finfo->is_percpu = is_percpu;
	finfo->is_loop = is_loop;
	finfo->buffer_addr = (u64) buffer_addr;
	finfo->buffer_len = size;
	finfo->start_timestamp = 0;
	finfo->stop_timestamp = 0;

	if (!size) {
		pr_err("%s, buffer_size is zero, no initialization!\n",
		       __func__);
		return 0;
	}

	if (is_percpu) {
		finfo->ftrace_buffer.buffer_addr = buffer_addr;
		finfo->ftrace_buffer.buffer_size = size;
		return percpu_buffer_init(&finfo->ftrace_buffer,
					  ftrace_record_ratio, cpu_num,
					  sizeof(struct function_trace_info),
					  g_ftrace_pattern, cacheline_size);
	}

	return hisiap_ringbuffer_init((struct hisiap_ringbuffer_s *)buffer_addr,
				      size, sizeof(struct function_trace_info),
				      g_ftrace_pattern);
}

/*************************************************************************
Function:		check_buffer_overflow
Description:	����ַ�Ƿ��ںϷ���Χ�ڣ�
Input:		NA
Return:		0����ַδ�������0��buffer�����
Author:		j00207786
*************************************************************************/
static int check_buffer_overflow(u8 *addr)
{
	if (!g_ftrace_buffer_addr || !g_ftrace_buffer_size)
		return -1;

	if (addr >= (g_ftrace_buffer_addr + g_ftrace_buffer_size))
		return 1;

	return 0;
}

/*************************************************************************
Function:		ftrace_buffers_init
Description:	ftrace�켣��¼����ĳ�ʼ��
Input:		NA
Return:		0����ʼ���ɹ�����0����ʼ��ʧ�ܣ�
Author:		j00207786
*************************************************************************/
static int ftrace_buffers_init(void)
{
	struct ftrace_root *froot;
	int i, ret;
	unsigned char *buffer_addr;

	if (!g_ftrace_buffer_addr) {
		if (ftrace_buffer_alloc()) {
			pr_err("%s, ftrace_buffer_alloc failed!\n",
			       __func__);
			return -1;
		}
	}

	froot = (struct ftrace_root *)g_ftrace_buffer_addr;
	froot->magic = FTRACE_BUF_MAGIC;
	froot->buffer_total_num = HK_FTRACE_BUF_MAX;

	froot->finfo[0] = (struct ftrace_buffer_head *)(g_ftrace_buffer_addr +
							ALIGN(sizeof
							      (struct
							       ftrace_root),
							      sizeof(u64)));
	for (i = 1; i < HK_FTRACE_BUF_MAX; i++) {
		froot->finfo[i] =
		    (struct ftrace_buffer_head *)((unsigned char *)froot->
						  finfo[i - 1] +
						  ALIGN(sizeof
							(struct
							 ftrace_buffer_head),
							sizeof(u64)) +
						  g_ftrace_buffer_size_tbl[i -
									   1]);
	}

	for (i = 0; i < HK_FTRACE_BUF_MAX; i++) {
		buffer_addr = (unsigned char *)froot->finfo[i] +
		    ALIGN(sizeof(struct ftrace_buffer_head), sizeof(u64));

		ret =
		    check_buffer_overflow(buffer_addr +
					  g_ftrace_buffer_size_tbl[i]);
		if (ret) {
			pr_err("%s, check_buffer_overflow!\n",
			       __func__);
			return ret;
		}

		ret = ftrace_buffer_head_init(froot->finfo[i], buffer_addr, i,
					      g_ftrace_buffer_size_tbl[i], true,
					      true);
		if (ret) {
			pr_err("%s, ftrace_buffer_head_init failed!\n",
			       __func__);
			return ret;
		}
	}

	ftrace_buffer_init_done = true;
	print_all_ftrace_buffer_info();
	pr_err("%s, success!\n", __func__);
	return 0;
}

/*************************************************************************
Function:		is_ftrace_buffer_full
Description:	�ж�ftrace buffer�Ƿ�����ѭ��buffer��������
Input:		finfo: buffer��������
			cpu: ��Ӧbuffer����cpu(����percpuģʽ��������)��
Return:		0��bufferδ����1��buffer������-1: ��ѯ�����쳣��
Author:		j00207786
*************************************************************************/
static int is_ftrace_buffer_full(struct ftrace_buffer_head *finfo, int cpu)
{
	if (IS_ERR_OR_NULL(finfo) || cpu < 0
		|| cpu >= num_possible_cpus()
	    || !finfo->buffer_len)
		return -1;

	/*ѭ��buffer ���Ϊ���� */
	if (finfo->is_loop)
		return BUFFER_NOT_FULL;

	/*�����percpu�������cpu�ţ��жϾ����percpu buffer�Ƿ��� */
	if (finfo->is_percpu) {
		if (hisiap_is_ringbuffer_full
		    ((void *)finfo->ftrace_buffer.percpu_addr[cpu]))
			return BUFFER_FULL;
	} else {
		if (hisiap_is_ringbuffer_full((void *)finfo->buffer_addr))
			return BUFFER_FULL;
	}

	return BUFFER_NOT_FULL;
}

/*************************************************************************
Function:		ftrace_buffer_write
Description:	ftrace�켣����дbuffer����;
Input:		entry: һ��ftrace�켣����;
Return:		NA��
Author:		j00207786
*************************************************************************/
static void notrace ftrace_buffer_write(struct function_trace_info *entry,
					struct ftrace_buffer_head *finfo)
{
	int ret;

	if (unlikely(IS_ERR_OR_NULL(entry)))
		return;

	if (unlikely(NULL == finfo))
		return;

	if (unlikely(0 == finfo->start_timestamp))
		finfo->start_timestamp = sched_clock();

	if (!finfo->is_loop && test_bit(entry->cpu, is_percpu_buffer_full))
		return;

	ret = is_ftrace_buffer_full(finfo, entry->cpu);
	if (BUFFER_FULL == ret) {
		pr_info(
		       "%s, is_ftrace_buffer_full(idx:%d, cpu:%d) is full!\n",
		       __func__, finfo->idx, entry->cpu);

		finfo->stop_timestamp = sched_clock();
		pr_info(
		       "%s, start_timestamp [%lld] stop_timestamp [%lld]!\n",
		       __func__, finfo->start_timestamp, finfo->stop_timestamp);
		bitmap_set(is_percpu_buffer_full, entry->cpu, 1);
		return;
	} else if (INVALID_QUERY == ret)
		return;

	if (finfo->is_percpu)
		hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
				finfo->ftrace_buffer.percpu_addr[entry->cpu],
				(u8 *) entry);
	else
		hisiap_ringbuffer_write((struct hisiap_ringbuffer_s *)
					finfo->buffer_addr, (u8 *) entry);

}

/*************************************************************************
Function:		ftrace_entry_update
Description:	ftrace�켣��¼������ʹ��BUF_B;
Input:		entry��ftraceһ����¼�����ݽṹ��
			ip: ��ǰָ���ַ��parent_ip:������ָ���ַ��
			flags: �жϱ�־��pc: ��ռ����;
Return:		NA��
Author:		j00207786
*************************************************************************/
static void ftrace_entry_update(struct function_trace_info *entry,
				unsigned long ip, unsigned long parent_ip,
				unsigned long flags, int preempt)
{
	struct task_struct *tsk = current;

	if (IS_ERR_OR_NULL(entry))
		return;

	entry->flags =
#ifdef CONFIG_TRACE_IRQFLAGS_SUPPORT
	    (irqs_disabled_flags(flags) ? TRACE_FLAG_IRQS_OFF : 0) |
#else
	    TRACE_FLAG_IRQS_NOSUPPORT |
#endif
	    ((preempt & HARDIRQ_MASK) ? TRACE_FLAG_HARDIRQ : 0) |
	    ((preempt & SOFTIRQ_MASK) ? TRACE_FLAG_SOFTIRQ : 0) |
	    (need_resched() ? TRACE_FLAG_NEED_RESCHED : 0);

	entry->cpu = (u8) smp_processor_id();
	entry->preempt_count = preempt & 0xff;
	entry->pid = (int)((tsk) ? tsk->pid : 0);
	entry->timestamp = sched_clock();
	entry->ip = ip;
	entry->parent_ip = parent_ip;

	if (!entry->pid) {
		strcpy(entry->comm, "<idle>");
		return;
	}

	if (WARN_ON_ONCE(entry->pid < 0)) {
		strcpy(entry->comm, "<XXX>");
		return;
	}

	if (entry->pid > PID_MAX_DEFAULT) {
		strcpy(entry->comm, "<...>");
		return;
	}

	strncpy(entry->comm, tsk->comm, TASK_COMM_LEN - 1);
	entry->comm[TASK_COMM_LEN - 1] = '\0';
}

/*************************************************************************
Function:		eeye_ftrace_tracing_on
Description:	����ftrace�켣��¼����BUF_B�ļ�¼���أ�
Input:		on: 0,�رգ�1����0ֵ,�򿪣�
Return:		NA��
Author:		j00207786
*************************************************************************/
static void eeye_ftrace_tracing_on(int on)
{
	if (on)
		g_eeye_ftrace_tracing_on = true;
	else
		g_eeye_ftrace_tracing_on = false;
}

/*************************************************************************
Function:		mntn_eeye_ftrace_call
Description:	ftrace�켣��¼������ʹ��BUF_B��BUF_B˵��:
			��buffer��Ԥ������ʱ��ֹͣ��¼�����桢��������¼��
Input:		ip����ǰPC��parent_ip��������pc��op����ǰע���ops��
			regs����ǰִ�мĴ��������ģ���֧�֣�Ĭ��ΪNULL����
Return:		NA��
Author:		j00207786
*************************************************************************/
static void notrace mntn_eeye_ftrace_call(unsigned long ip,
					  unsigned long parent_ip,
					  struct ftrace_ops *op,
					  struct pt_regs *regs)
{
	struct function_trace_info entry;
	struct ftrace_buffer_head *finfo;
	unsigned long flags;
	int preempt;

	if (unlikely(oops_in_progress))
		return;

	if (unlikely(!ftrace_buffer_init_done))
		return;

	if (unlikely(!g_eeye_ftrace_tracing_on))
		return;

	finfo =
	    ((struct ftrace_root *)
	     g_ftrace_buffer_addr)->finfo[HK_FTRACE_BUF_B];

	preempt = preempt_count();
	preempt_disable_notrace();

	local_irq_save(flags);

	ftrace_entry_update(&entry, ip, parent_ip, flags, preempt);

	ftrace_buffer_write(&entry, finfo);

	local_irq_restore(flags);
	preempt_enable_notrace();
}

static struct ftrace_ops mntn_eeye_ftrace_ops __read_mostly = {
	.func = mntn_eeye_ftrace_call,
};

/*************************************************************************
Function:		mntn_comm_ftrace_call
Description:	ftrace�켣��¼������ʹ��BUF_A��BUF_A˵��:
			��buffer�����Դ�ʱ��һֱ�����¼״̬����ͣ��
Input:		ip����ǰPC��parent_ip��������pc��op����ǰע���ops��
			regs����ǰִ�мĴ��������ģ���֧�֣�Ĭ��ΪNULL����
Return:		NA��
Author:		j00207786
*************************************************************************/
static void notrace mntn_comm_ftrace_call(unsigned long ip,
					  unsigned long parent_ip,
					  struct ftrace_ops *op,
					  struct pt_regs *regs)
{
	struct function_trace_info entry;
	struct ftrace_buffer_head *finfo;
	unsigned long flags;
	int preempt;

	if (unlikely(oops_in_progress))
		return;

	if (unlikely(!ftrace_buffer_init_done))
		return;

	finfo =
	    ((struct ftrace_root *)
	     g_ftrace_buffer_addr)->finfo[HK_FTRACE_BUF_A];

	preempt = preempt_count();
	preempt_disable_notrace();

	local_irq_save(flags);

	ftrace_entry_update(&entry, ip, parent_ip, flags, preempt);

	ftrace_buffer_write(&entry, finfo);

	local_irq_restore(flags);
	preempt_enable_notrace();
}

static struct ftrace_ops mntn_comm_ftrace_ops __read_mostly = {
	.func = mntn_comm_ftrace_call,
};

/*************************************************************************
Function:		register_ftrace_call
Description:	ע��ftrace���Ӻ�����
Input:		ops��ftrace����������on��1��ʾע�ᣬ0��ʾȥע�᣻
Return:		0��ע��ɹ�����0ע��ʧ�ܣ�
Other:		��Ԥ��ϵͳ�ĳ�ʼ�������е��ã�
Author:		j00207786
*************************************************************************/
static int register_ftrace_call(struct ftrace_ops *ops, int on)
{
	int ret;

	if (IS_ERR_OR_NULL(ops)) {
		pr_err("%s, ops [%pK] is invalid!\n", __func__, ops);
		return -1;
	}

	if (on < 0 || on > 1) {
		pr_err("%s, on [%d] is invalid!\n", __func__, on);
		return -1;
	}

	if (on)
		ret = register_ftrace_function(ops);
	else
		ret = unregister_ftrace_function(ops);

	if (ret) {
		pr_err("%s: unable to %sregister ftrace ops: %d\n",
		       __func__, on ? "" : "un", ret);
		return -1;
	}
	pr_err("%s, %sregister ftrace ops success!\n",
	       __func__, on ? "" : "un");
	return 0;
}

/*************************************************************************
Function:	eeye_create_dir
Description:	����ָ��Ŀ¼��
Input:		path: ������Ŀ¼����user: Ŀ¼uid; group: Ŀ¼gid��
Return:		0: �����ɹ�����0: ����ʧ�ܣ�
Author:		j00207786
*************************************************************************/
int eeye_create_dir(char *path, uid_t user, gid_t group)
{
	int fd, ret;
	mm_segment_t old_fs;

	if (!path) {
		pr_err("%s, path is null!\n", __func__);
		return -1;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	fd = sys_access(path, 0);
	if (0 != fd) {
		pr_err("%s: need create dir %s !\n", __func__, path);
		fd = sys_mkdir(path, DIR_LIMIT);
		if (fd < 0) {
			pr_err("%s: create dir %s failed! ret = %d\n",
			       __func__, path, fd);
			set_fs(old_fs);
			return fd;
		}

		ret = (int)sys_chown((const char __user *)path, user, group);
		if (ret)
			pr_err(
			       "[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
			       __func__, path, user, group, ret);

		pr_err("%s: create dir %s successed [%d]!!!\n",
		       __func__, path, fd);
	}

	set_fs(old_fs);
	return 0;
}

/*************************************************************************
Function:	eeye_create_dir_recursive
Description:	�ݹ齨��ָ��Ŀ¼��
Input:		path: ������Ŀ¼����user: Ŀ¼uid; group: Ŀ¼gid��
Return:		0: �����ɹ�����0: ����ʧ�ܣ�
Author:		j00207786
*************************************************************************/
int eeye_create_dir_recursive(char *path, uid_t user, gid_t group)
{
	char cur_path[PATH_MAXLEN];
	int index = 0;
	int ret;

	if (!path) {
		pr_err("%s, path is null!\n", __func__);
		return -1;
	}
	pr_debug("%s, enter!\n", __func__);

	memset(cur_path, 0, PATH_MAXLEN);
	if (*path != '/')
		return -1;

	cur_path[index++] = *path++;

	while (*path != '\0') {
		if (*path == '/') {
			ret = eeye_create_dir(cur_path, user, group);
			if (ret) {
				pr_err(
				       "%s, eeye_create_dir unsuccessful!\n",
				       __func__);
				return -1;
			}
		}
		cur_path[index] = *path;
		path++;
		index++;
	}
	pr_debug("%s, exit!\n", __func__);
	return 0;
}

/*************************************************************************
Function:	get_time_from_ftrace_bin
Description:	��ftrace.bin�ļ����л�ȡ���ڣ�
Input:		ftrace_bin: ����ȡ��־���ļ�����
Return:		0: ���ڸ�ʽ���Ϸ���������ת��ʧ�ܣ�
			��0: ���ڣ�
Author:		j00207786
*************************************************************************/
u64 get_time_from_ftrace_bin(char *ftrace_bin)
{
	int i;
	char *buf;
	char tmpbuf[DATE_MAXLEN + 1];
	u64 date = 0;
	int ret ;

	if (!ftrace_bin) {
		pr_err("%s, ftrace_bin is null!\n", __func__);
		return 1;
	}

	if (strnlen(ftrace_bin, FILE_NAME_LEN)
	    < (strlen(PREFIX_FTRACE_BIN) + DATE_MAXLEN))
		return 0;

	buf = ftrace_bin;
	buf += strlen(PREFIX_FTRACE_BIN);

	/* Judge if all char is number */
	for (i = 0; i < DATE_MAXLEN; i++) {
		if (buf[i] > '9' || buf[i] < '0')
			return 0;
	}

	memcpy(tmpbuf, buf, DATE_MAXLEN);
	tmpbuf[DATE_MAXLEN] = '\0';

	ret = kstrtou64(tmpbuf, 10, &date);
	pr_err("%s, tmpbuf [%s] date [%lld] ret [%d]!\n", __func__,
	       tmpbuf, date, ret);
	if (ret) {
		pr_err("[%s], date get failed!\n", __func__);
		return 0;
	}

	return date;
}

/*************************************************************************
Function:	add_ftrace_bin_list
Description:	��ftrace.bin���ļ����е����ڽ������У�
Input:		info: ����ftrace.bin����Ϣ�ṹ�壻
Return:		0: ��ӳɹ�����0: ���ʧ�ܣ�
Author:		j00207786
*************************************************************************/
static int add_ftrace_bin_list(struct ftrace_bin_info *info)
{
	struct list_head *cur, *next;
	struct ftrace_bin_info *fptr;
	unsigned long flags;

	if (IS_ERR_OR_NULL(info)) {
		pr_err("[%s], info is null!\n", __func__);
		return -1;
	}

	spin_lock_irqsave(&g_eeye_ftrace_bin_list_lock, flags);
	if (list_empty(&eeye_ftrace_bin_list)) {
		list_add_tail(&info->list, &eeye_ftrace_bin_list);
		goto out;
	}

	list_for_each_safe(cur, next, &eeye_ftrace_bin_list) {
		fptr = list_entry(cur, struct ftrace_bin_info, list);
		if (NULL == fptr) {
			pr_info(
			       "%s, It might be better to look around here!\n",
			       __func__);
			continue;
		}

		if (info->file_tm == fptr->file_tm) {
			kfree(info);
			goto out;
		}

		if (info->file_tm > fptr->file_tm) {
			list_add_tail(&info->list, cur);
			goto out;
		}
	}
	list_add_tail(&info->list, &eeye_ftrace_bin_list);
out:
	spin_unlock_irqrestore(&g_eeye_ftrace_bin_list_lock, flags);
	return 0;
}

/*************************************************************************
Function:	get_ftrace_bin_list_idx
Description:	�����ļ���eeye_ftrace_bin_list�е���ţ���ʼ���Ϊ0��
Input:		filename: �����ļ�����
Output:		fptrp: ����ftrace_bin�Ľṹ��ָ�룻
Return:		-1: δ���ҵ���>=0: ��Ӧ��ţ�
Author:		j00207786
*************************************************************************/
static int get_ftrace_bin_list_idx(char *filename,
				   struct ftrace_bin_info **fptrp)
{
	struct list_head *cur, *next;
	struct ftrace_bin_info *fptr;
	unsigned long flags;
	int idx = 0;

	if (IS_ERR_OR_NULL(filename) || !fptrp) {
		pr_err("[%s], input args is null!\n", __func__);
		return -1;
	}

	spin_lock_irqsave(&g_eeye_ftrace_bin_list_lock, flags);
	if (list_empty(&eeye_ftrace_bin_list))
		goto out;

	list_for_each_safe(cur, next, &eeye_ftrace_bin_list) {
		fptr = list_entry(cur, struct ftrace_bin_info, list);
		if (NULL == fptr) {
			pr_info(
			       "%s, It might be better to look around here!\n",
			       __func__);
			continue;
		}

		if (!strncmp
		    (fptr->filename, filename, sizeof(fptr->filename) - 1)) {
			*fptrp = fptr;
			spin_unlock_irqrestore(&g_eeye_ftrace_bin_list_lock,
					       flags);
			return idx;
		}
		idx++;
	}
out:
	*fptrp = NULL;
	spin_unlock_irqrestore(&g_eeye_ftrace_bin_list_lock, flags);
	return -1;
}

/*************************************************************************
Function:	print_ftrace_bin_list
Description:	��eeye_ftrace_bin_list�ڵ���Ϣ��ӡ������
Input:		NA
Return:		NA
Author:		j00207786
*************************************************************************/
void print_ftrace_bin_list(void)
{
	struct list_head *cur, *next;
	struct ftrace_bin_info *fptr;
	unsigned long flags;
	int idx = 0;

	spin_lock_irqsave(&g_eeye_ftrace_bin_list_lock, flags);
	if (list_empty(&eeye_ftrace_bin_list)) {
		pr_err("%s, eeye_ftrace_bin_list is empty!\n",
		       __func__);
		goto out;
	}

	list_for_each_safe(cur, next, &eeye_ftrace_bin_list) {
		fptr = list_entry(cur, struct ftrace_bin_info, list);
		if (NULL == fptr) {
			pr_info(
			       "%s, It might be better to look around here!\n",
			       __func__);
			continue;
		}

		pr_err("%s, idx [%d]   filename [%s]!\n",
		       __func__, idx, fptr->filename);
		idx++;
	}
out:
	spin_unlock_irqrestore(&g_eeye_ftrace_bin_list_lock, flags);
}

/*************************************************************************
Function:	get_ftrace_bin_list
Description:	��ָ��·���µ�ftrace.bin�����ڽ������У�
Input:		path:�����Ŀ¼;
Return:		NA��
Author:		j00207786
*************************************************************************/
void create_ftrace_bin_list(char *path)
{
	int fd = -1, bpos, count;
	char *buf;
	int bufsize;
	struct linux_dirent *d;
	char d_type;
	char fullname[PATH_MAXLEN];
	mm_segment_t old_fs;
	u64 date;
	struct ftrace_bin_info *fptr;

	if (!path) {
		pr_err("%s, input arg is invalid!\n", __func__);
		return;
	}

	buf = kzalloc(TMP_BUF_SIZE, GFP_KERNEL);
	if (NULL == buf) {
		pr_err("%s, kzalloc buf failed!\n", __func__);
		return;
	}

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	fd = sys_open(path, O_RDONLY, DIR_LIMIT);
	if (fd < 0) {
		pr_err("[%s], open %s fail, ret:%d\n", __func__, path,
		       fd);
		kfree(buf);
		set_fs(old_fs);
		return;
	}

	for (count = 0; count < LOOP_COUNT_MAX; count++) {	/*��ֹ��ѭ�� */
		bufsize =
		    sys_getdents(fd, (struct linux_dirent *)buf, TMP_BUF_SIZE);
		if (bufsize == -1) {
			pr_err("[%s], sys_getdents failed, ret [%d]\n",
			       __func__, bufsize);
			goto out;
		}

		if (0 == bufsize) {
			/*������� */
			break;
		}

		for (bpos = 0; bpos < bufsize; bpos += d->d_reclen) {
			d = (struct linux_dirent *)(buf + bpos);
			d_type = *(buf + bpos + d->d_reclen - 1);
			snprintf(fullname, sizeof(fullname), "%s/%s", path,
				 d->d_name);

			/*�����ļ� */
			if (d_type == DT_REG) {

				/*����ļ���ʽ����ȡ�ļ��е���־ */
				if (strncmp
				    (d->d_name, PREFIX_FTRACE_BIN,
				     strlen(PREFIX_FTRACE_BIN))
				    && strncmp(d->d_name, KSYMS_BIN,
					       strlen(KSYMS_BIN))) {
					/*���Ϲ���ļ�ɾ�� */
					sys_unlink(fullname);
					continue;
				}

				/*���������ļ�KSYMS_BIN */
				if (!strncmp
				    (d->d_name, KSYMS_BIN, strlen(KSYMS_BIN))) {
					continue;
				}

				date = get_time_from_ftrace_bin(d->d_name);

				fptr =
				    kzalloc(sizeof(struct ftrace_bin_info),
					    GFP_KERNEL);
				if (!fptr) {
					pr_err(
					       "[%s], kzalloc fptr failed!\n",
					       __func__);
					goto out;
				}
				strncpy(fptr->filename, d->d_name,
					sizeof(fptr->filename) - 1);
				fptr->filename[sizeof(fptr->filename) - 1] =
				    '\0';
				fptr->file_tm = date;
				if (add_ftrace_bin_list(fptr)) {
					pr_err(
					       "%s, add_ftrace_bin_list [%s] failed!\n",
					       __func__, d->d_name);
				}
			}
		}
	}
out:
	kfree(buf);
	sys_close(fd);
	set_fs(old_fs);
}

/*************************************************************************
Function:	restrict_ftrace_bin_num
Description:	����ftrace.bin����ĸ���������num���ϵ��ļ�ɾ����
Input:		path:�����Ŀ¼��num:�ɱ�����ftrace.bin�ļ�����;
Return:		NA��
Author:		j00207786
*************************************************************************/
void restrict_ftrace_bin_num(char *path, int num)
{
	int fd = -1, bpos, count, idx;
	char *buf;
	int bufsize;
	struct linux_dirent *d;
	char d_type;
	char fullname[PATH_MAXLEN];
	mm_segment_t old_fs;
	struct ftrace_bin_info *fptr;

	if (!path || num <= 0) {
		pr_err("%s, input arg is invalid!\n", __func__);
		return;
	}

	buf = kzalloc(TMP_BUF_SIZE, GFP_KERNEL);
	if (NULL == buf) {
		pr_err("%s, kzalloc buf failed!\n", __func__);
		return;
	}

	create_ftrace_bin_list(path);

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	fd = sys_open(path, O_RDONLY, DIR_LIMIT);
	if (fd < 0) {
		pr_err("[%s], open %s fail, ret:%d\n", __func__, path,
		       fd);
		kfree(buf);
		set_fs(old_fs);
		return;
	}

	for (count = 0; count < LOOP_COUNT_MAX; count++) {	/*��ֹ��ѭ�� */
		bufsize =
		    sys_getdents(fd, (struct linux_dirent *)buf, TMP_BUF_SIZE);
		if (bufsize == -1) {
			pr_err("[%s], sys_getdents failed, ret [%d]\n",
			       __func__, bufsize);
			goto out;
		}

		if (0 == bufsize) {
			/*������� */
			break;
		}

		for (bpos = 0; bpos < bufsize; bpos += d->d_reclen) {
			d = (struct linux_dirent *)(buf + bpos);
			d_type = *(buf + bpos + d->d_reclen - 1);
			snprintf(fullname, sizeof(fullname), "%s/%s", path,
				 d->d_name);

			/*����Ŀ¼������"."��".."Ŀ¼����������޵ݹ� */
			if (d_type == DT_DIR
			    && strncmp(d->d_name, ".", sizeof("."))
			    && strncmp(d->d_name, "..", sizeof(".."))) {

				/*��ӡ�ļ����� */
				pr_info(
				       "[%s], there should be no dir [%s]!\n",
				       __func__, d->d_name);
			} else if (d_type == DT_REG) {	/*�����ļ� */
				idx = get_ftrace_bin_list_idx(d->d_name, &fptr);
				pr_err(
				       "%s, d->d_name [%s] idx [%d]!\n",
				       __func__, d->d_name, idx);
				if (idx >= num) {
					sys_unlink(fullname);
					list_del(&(fptr->list));
					kfree(fptr);
				}
			}
		}
	}

out:
	kfree(buf);
	sys_close(fd);
	set_fs(old_fs);
}

/*************************************************************************
Function:	eeye_get_timestamp
Description:	��ȡ�����յ�ʱ�����
Input:		NA
Return:		������Сʱ������ַ�����
Author:		j00207786
*************************************************************************/
char *eeye_get_timestamp(void)
{
	struct rtc_time tm;
	struct timeval tv;
	static char databuf[DATE_MAXLEN + 1];

	memset(databuf, 0, DATE_MAXLEN + 1);

	memset(&tv, 0, sizeof(struct timeval));
	memset(&tm, 0, sizeof(struct rtc_time));
	do_gettimeofday(&tv);
	tv.tv_sec -= sys_tz.tz_minuteswest * 60;
	rtc_time_to_tm(tv.tv_sec, &tm);

	snprintf(databuf, DATE_MAXLEN + 1, "%04d%02d%02d%02d%02d%02d",
		 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday,
		 tm.tm_hour, tm.tm_min, tm.tm_sec);

	pr_err("%s: [%s] !\n", __func__, databuf);
	return databuf;
}

/*************************************************************************
Function:	eeye_savebuf2fs
Description:	����buffer���ļ���
Input:		logpath:������Ŀ¼��filename:�ļ�����buf: �������ڴ�buffer��
			len: buf���ȣ� is_append: �Ƿ�׷��д��filename��
Return:		0:����ɹ�����0: ����ʧ�ܣ�
Author:		j00207786
*************************************************************************/
int eeye_savebuf2fs(char *logpath, char *filename,
		    void *buf, u32 len, u32 is_append)
{
	int ret = 0, flags;
	struct file *fp;
	mm_segment_t old_fs;
	char path[PATH_MAXLEN] = {0};

	if (logpath == NULL || filename == NULL || buf == NULL || len <= 0) {
		pr_err(
		       "%s, invalid  parameter. path:%pK, name:%pK buf:%pK len:0x%x\n",
		       __func__, logpath, filename, buf, len);
		ret = -1;
		goto fail;
	}

	memset(path, 0, PATH_MAXLEN);
	snprintf(path, PATH_MAXLEN, "%s/%s", logpath, filename);

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	flags = O_CREAT | O_RDWR | (is_append ? O_APPEND : O_TRUNC);
	fp = filp_open(path, flags, FILE_LIMIT);
	if (IS_ERR(fp)) {
		set_fs(old_fs);
		pr_err("%s():create file %s err.\n", __func__, path);
		ret = -1;
		goto fail;
	}
	vfs_llseek(fp, 0L, SEEK_END);
	ret = vfs_write(fp, buf, len, &(fp->f_pos));
	if (ret != len) {
		pr_err("%s():write file %s exception with ret %d.\n",
		       __func__, path, ret);
		goto write_fail;
	}

	vfs_fsync(fp, 0);
write_fail:
	filp_close(fp, NULL);

	/*����Ȩ��Ҫ��Ŀ¼����Ŀ¼Ⱥ�����Ϊroot-system */
	ret = (int)sys_chown((const char __user *)path, ROOT_UID, SYSTEM_GID);
	if (ret) {
		pr_err(
		       "[%s], chown %s uid [%d] gid [%d] failed err [%d]!\n",
		       __func__, path, ROOT_UID, SYSTEM_GID, ret);
	}
	set_fs(old_fs);
fail:
	return ret;
}

void flush_ftrace_buffer_cache(void)
{
	if (!g_ftrace_buffer_addr || !g_ftrace_buffer_size) {
		pr_err("%s, ftrace_buffer is null!\n", __func__);
		return;
	}
	__dma_map_area((void *)g_ftrace_buffer_addr, g_ftrace_buffer_size,
		       DMA_FROM_DEVICE);
}

/*************************************************************************
Function:		save_ftrace_bin
Description:	����ftrace.bin���ļ�ϵͳ��
Input:		finfo: buffer������;
			type: 0������finfo��ָ��buffer��1��������ftrace_buffer
Return:		0������ɹ���1������ʧ�ܣ�
Author:		j00207786
*************************************************************************/
int save_ftrace_bin(struct ftrace_buffer_head *finfo, int type)
{
	char ftrace_bin[FILE_NAME_LEN + 1] = { '\0' };
	char datebuf[DATE_MAXLEN + 1] = { '\0' };
	int ret;
	size_t fname_len;

	if (!ftrace_buffer_init_done) {
		pr_err("%s, ftrace_buffer_init_done is false!\n",
		       __func__);
		return 1;
	}

	if (!g_ftrace_buffer_size) {
		pr_err("%s, g_ftrace_buffer_size is zero!\n",
		       __func__);
		return 1;
	}

	/*�ж�PATH_FTRACE_BIN�Ƿ���ڣ���������ڣ�����Ŀ¼ */
	if (eeye_create_dir_recursive(PATH_FTRACE_BIN, ROOT_UID, SYSTEM_GID)) {
		pr_err("%s, eeye_create_dir_recursive failed!\n",
		       __func__);
		return 1;
	}

	strncpy(datebuf, eeye_get_timestamp(), DATE_MAXLEN);
	datebuf[DATE_MAXLEN] = '\0';

	fname_len = min((size_t)FILE_NAME_LEN + 1,
			strlen(PREFIX_FTRACE_BIN) + strlen(datebuf)+
			strlen(SUFFIX_FTRACE_BIN) + 1);/*lint !e666 */
	snprintf(ftrace_bin, fname_len, "%s%s%s",
			PREFIX_FTRACE_BIN, datebuf,
			SUFFIX_FTRACE_BIN);

	if (!type) {
		if (IS_ERR_OR_NULL(finfo)) {
			pr_err("%s, finfo is null!\n", __func__);
			return 1;
		}

		/*��ftrace_buffer_headͷ��ϢҲ���浽�ļ��� */
		ret =
		    eeye_savebuf2fs(PATH_FTRACE_BIN, ftrace_bin, (void *)finfo,
				    finfo->buffer_len +
				    sizeof(struct ftrace_buffer_head), false);
		if (ret) {
			pr_err("%s, eeye_savebuf2fs failed!\n",
			       __func__);
			return ret;
		}
	} else {
		ret = eeye_savebuf2fs(PATH_FTRACE_BIN, ftrace_bin,
				      g_ftrace_buffer_addr,
				      (u32) g_ftrace_buffer_size, false);
		if (ret) {
			pr_err("%s, eeye_savebuf2fs failed!\n",
			       __func__);
			return ret;
		}
	}

	return 0;
}

/*************************************************************************
Function:		get_kallsyms
Description:	���������ں˷��ŵ��ļ���
Input:		data�����������namebuf����������
			module_info��δʹ�ã�addr�����ŵ�ַ��
Return:		0������ɹ�����0������ʧ�ܣ�
Author:		j00207786
*************************************************************************/
static int get_kallsyms(void *data, const char *namebuf,
			struct module *module_info, unsigned long addr)
{
	struct kallsyms_info *kinfo;
	char *name;

	if (IS_ERR_OR_NULL(data)) {
		pr_err("%s, data is invalid!\n", __func__);
		return -1;
	}

	kinfo = (struct kallsyms_info *)data;
	if (kinfo->index > kinfo->num_syms) {
		pr_err("%s, overflow!kinfo->index[%lu] num_syms[%lu]\n",
		       __func__, kinfo->index, kinfo->num_syms);
		return -1;
	}

	if (addr >= (unsigned long)_stext && addr <= (unsigned long)_etext) {
		name = (char *)kinfo->kallsyms_ptr[kinfo->index].namebuf;
		strncpy(name, namebuf, KSYM_NAME_LEN - 1);
		name[KSYM_NAME_LEN - 1] = '\0';
		kinfo->kallsyms_ptr[kinfo->index].addr = addr;
		kinfo->index++;
	}

	return 0;
}

/*************************************************************************
Function:		get_ksyms_num
Description:	��ȡ�ں˺������ŵĸ�����
Input:		NA��
Return:		0������ɹ�����0������ʧ�ܣ�
Author:		j00207786
*************************************************************************/
static int get_ksyms_num(void *data, const char *namebuf,
			 struct module *module_info, unsigned long addr)
{
	if (addr >= (unsigned long)_stext && addr <= (unsigned long)_etext) {
		if (strlen(namebuf) > max_ksym_len)
			max_ksym_len = strlen(namebuf);

		(*(unsigned long *)data)++;
	}
	return 0;
}

/*************************************************************************
Function:		save_kallsyms
Description:	���������ں˷��ŵ��ļ���
Input:		NA��
Return:		0������ɹ�����0������ʧ�ܣ�
Author:		j00207786
*************************************************************************/
int save_kallsyms(void)
{
	struct ksym_info *ksyms = NULL;
	struct kallsyms_info *kinfo = NULL;
	char *buf = NULL, *ptr;
	int ret, i;
	unsigned long ksyms_num = 0;
	int fd;
	mm_segment_t old_fs;
	char path[PATH_MAXLEN];

	old_fs = get_fs();
	set_fs(KERNEL_DS);

	memset(path, 0, PATH_MAXLEN);
	snprintf(path, PATH_MAXLEN, "%s/%s", PATH_FTRACE_BIN, KSYMS_BIN);
	fd = sys_access(path, 0);
	if (0 == fd) {		/*KSYMS_BIN�ļ����ڣ�ֱ�ӷ��� */
		set_fs(old_fs);
		return 0;
	}

	set_fs(old_fs);

	ret = kallsyms_on_each_symbol(get_ksyms_num, &ksyms_num);
	if (ret || !ksyms_num) {
		pr_err(
		       "%s, kallsyms_on_each_symbol(get_ksyms_num) failed!\n",
		       __func__);
		goto out;
	}

	pr_err("%s, max_ksym_len [%d]!\n", __func__, max_ksym_len);
	pr_err("%s, ksyms_num [%lu]!\n", __func__, ksyms_num);
	ksyms = vzalloc(ksyms_num * sizeof(struct ksym_info));
	if (!ksyms) {
		pr_err("%s, fail to vzalloc ksyms, size [0x%lu]!\n",
		       __func__, ksyms_num * sizeof(struct ksym_info));
		return -1;
	}

	kinfo = kzalloc(sizeof(struct kallsyms_info), GFP_KERNEL);
	if (!kinfo) {
		pr_err("%s, fail to allocate kinfo!\n", __func__);
		vfree(ksyms);
		return -1;
	}

	kinfo->kallsyms_ptr = ksyms;
	kinfo->num_syms = ksyms_num;
	kinfo->index = 0;

	ret = kallsyms_on_each_symbol(get_kallsyms, kinfo);
	if (ret) {
		pr_err(
		       "%s, kallsyms_on_each_symbol(get_kallsyms) failed!\n",
		       __func__);
		ret = -1;
		goto out;
	}

	buf = (char *)vzalloc(ksyms_num * sizeof(struct ksym_info));
	if (!buf) {
		pr_err("%s, fail to vzalloc buf, size [0x%lu]!\n",
		       __func__, ksyms_num * sizeof(struct ksym_info));
		ret = -1;
		goto out;
	}

	ptr = buf;
	for (i = 0; i < ksyms_num; i++) {
		snprintf(ptr, U64_STR_LEN + KSYM_NAME_LEN + 2,
			 "%lx:%s\n", kinfo->kallsyms_ptr[i].addr,
			 kinfo->kallsyms_ptr[i].namebuf);
		ptr =
		    ptr + (U64_STR_LEN +
			   strnlen(kinfo->kallsyms_ptr[i].namebuf,
				   KSYM_NAME_LEN) + 2);
	}

	ret = eeye_savebuf2fs(PATH_FTRACE_BIN, KSYMS_BIN,
			      (void *)buf, strnlen(buf,
						   ksyms_num *
						   sizeof(struct ksym_info)),
			      false);
	if (ret)
		pr_err("%s, eeye_savebuf2fs failed!\n", __func__);
out:
	vfree(ksyms);
	kfree(kinfo);
	vfree(buf);
	return ret;
}

/*************************************************************************
Function:		eeye_set_fb_reason
Description:	����ftrace buffer��Ԥ��ԭ��
Input:		reason: �˴�buffer�����Ԥ��ԭ��
Return:		NA
Author:		j00207786
*************************************************************************/
void eeye_set_fb_reason(int reason)
{
	struct ftrace_buffer_head *finfo;

	if (!mntn_ftrace_enabled)
		return;

	if (!ftrace_buffer_init_done) {
		pr_info("%s, ftrace_buffer_init_done is false!\n",
		       __func__);
		return;
	}

	finfo =
	    ((struct ftrace_root *)
	     g_ftrace_buffer_addr)->finfo[HK_FTRACE_BUF_B];
	if (reason < EARLY_ALARM_MAX && reason >= EARLY_ALARM_NORMAL) {
		finfo->reason = reason;
	} else {
		pr_info("%s, reason [%d] is invalid!\n", __func__,
		       reason);
	}
}

/*************************************************************************
Function:		save_eeye_ftrace_buffer
Description:	����HK_FTRACE_BUF_BΪ�ļ���
			���ں�Ԥ��ģ����ã�
Input:		reason: �˴�buffer�����Ԥ��ԭ��
Return:		0: ����ɹ�����0: ���治�ɹ���
Author:		j00207786
*************************************************************************/
int save_eeye_ftrace_buffer(int reason)
{
	int ret;
	struct ftrace_buffer_head *finfo;
	u64 delta;

	if (!ftrace_buffer_init_done) {
		pr_err("%s, ftrace_buffer_init_done is false!\n",
		       __func__);
		return 0;
	}

	if (!g_eeye_ftrace_register) {
		pr_err("%s, g_eeye_ftrace_register is false!\n",
		       __func__);
		return 0;
	}
	pr_err("%s, enter!\n", __func__);

	finfo =
	    ((struct ftrace_root *)
	     g_ftrace_buffer_addr)->finfo[HK_FTRACE_BUF_B];

	/*�������д�������¼���Ҳ�����ʱ����ֵ��
	   ����Ҫ�ٴμ�¼ */
	delta = sched_clock() - finfo->stop_timestamp;
	if (delta < g_ftrace_buffer_lifetime && finfo->stop_timestamp) {
		pr_info(
		       "%s, trigger too many ftracer, would not save ftrace.bin!\n",
		       __func__);
		return 0;
	}

	if (reason < EARLY_ALARM_MAX && reason >= EARLY_ALARM_NORMAL)
		finfo->reason = reason;

	/*�Ƚ�ע��ftrace�����������ɺ���ע���ȥ */
	down(&save_fbin_sem);
	finfo->stop_timestamp = sched_clock();
	eeye_ftrace_tracing_on(0);

	flush_ftrace_buffer_cache();

	ret = save_ftrace_bin(finfo, 0);
	if (ret)
		pr_err("%s, save_ftrace_bin failed!\n", __func__);

	eeye_ftrace_tracing_on(1);
	finfo->start_timestamp = sched_clock();
	up(&save_fbin_sem);

	if (save_kallsyms())
		pr_info("%s, save_kallsyms failed!\n", __func__);

	/*����ftrace.bin�ļ��ĸ��� */
	restrict_ftrace_bin_num(PATH_FTRACE_BIN, FTRACE_BIN_NUM_LIMIT);

	if (preemptible()) {
		/* ȷ��֮ǰ�������ļ�ϵͳ��ز���������� */
		sys_sync();
	}
	pr_err("%s, exit!\n", __func__);
	return ret;
}

/*************************************************************************
Function:		test_eeye_ftrace
Description:	ftrace.bin������Ժ�����
Input:		type: 0 ��ʾ����BUF_B��
			1 ��ʾ��������ftrace buffer,����BUF_A;
Return:		NA
Author:		j00207786
*************************************************************************/
int test_eeye_ftrace(int type)
{
	struct ftrace_buffer_head *finfo;
	int ret;

	if (!ftrace_buffer_init_done) {
		pr_err("%s, ftrace_buffer_init_done is false!\n",
		       __func__);
		return -1;
	}

	if (!g_eeye_ftrace_register) {
		pr_err("%s, g_eeye_ftrace_register is false!\n",
		       __func__);
		return 0;
	}

	finfo =
	    ((struct ftrace_root *)
	     g_ftrace_buffer_addr)->finfo[HK_FTRACE_BUF_B];

	/*�Ƚ�ע��ftrace�����������ɺ���ע���ȥ */
	down(&save_fbin_sem);
	eeye_ftrace_tracing_on(0);
	finfo->stop_timestamp = sched_clock();

	ret = save_ftrace_bin(finfo, type);
	if (ret)
		pr_info("%s, save_ftrace_bin failed!\n", __func__);

	/*bitmap_clear(is_percpu_buffer_full, 0, NR_CPUS);*/
	eeye_ftrace_tracing_on(1);
	finfo->start_timestamp = sched_clock();
	up(&save_fbin_sem);

	print_all_ftrace_buffer_info();
	return 0;
}

/*************************************************************************
Function:	register_ftrace_to_mntn_dump
Description:    ��mntn dumpģ��ע�ᣬ����ftrace head����ͷ��
Input:		NA��
Return:		0��ע��ɹ�����0��ע��ʧ�ܣ�
Author:			j00207786
*************************************************************************/
static int register_ftrace_to_mntn_dump(void)
{
	int ret;
	FTRACE_MDUMP_HEAD *fhead;

	if (IS_ERR_OR_NULL(g_ftrace_buffer_addr)) {
		pr_err("%s, g_ftrace_buffer_addr is NULL!\n",
		       __func__);
		return 0;
	}

	if (g_ftrace_mdump_head) {
		pr_err("%s, has already registered!\n", __func__);
		return 0;
	}

	ret =
	    register_mntn_dump(MNTN_DUMP_FTRACE, sizeof(FTRACE_MDUMP_HEAD),
			       (void **)&fhead);
	if (ret || !fhead) {
		pr_err("%s, register_mntn_dump failed!\n", __func__);
		return -1;
	}

	g_ftrace_mdump_head = fhead;
	fhead->magic = FTRACE_MDUMP_MAGIC;
	fhead->paddr = __pa(g_ftrace_buffer_addr);
	fhead->size = g_ftrace_buffer_size;

	pr_err("%s, success!\n", __func__);
	return 0;
}

/*************************************************************************
Function:	eeye_ftrace_register_func
Description:    Ԥ��ftrace��ftrace_call��mntn dumpע�᣻
Input:		work: ִ�б�������workָ�룻
Return:		NA
Author:			j00207786
*************************************************************************/
static void eeye_ftrace_register_func(struct work_struct *work)
{
	int on = 1;
	int ret;

	if (AP_TRACE_FTRACE_BUF_A_SIZE) {
		ret = register_ftrace_call(&mntn_comm_ftrace_ops, on);
		if (ret) {
			pr_err(
			       "%s, register mntn_comm_ftrace_ops failed!\n",
			       __func__);
			return;
		}
	}

	if (AP_TRACE_FTRACE_BUF_B_SIZE) {
		ret = register_ftrace_call(&mntn_eeye_ftrace_ops, on);
		if (ret) {
			pr_err(
			       "%s, register mntn_eeye_ftrace_ops failed!\n",
			       __func__);
		}
		eeye_ftrace_tracing_on(1);
	}

	g_eeye_ftrace_register = true;

	ret = register_ftrace_to_mntn_dump();
	if (ret) {
		pr_err("%s, failed!\n", __func__);
		return;
	}
}

/*************************************************************************
Function:	eeye_save_kallsyms_func
Description:	�����ں˷��ű�
Input:		work: ִ�б�������workָ�룻
Return:		NA
Author:			j00207786
*************************************************************************/
static void eeye_save_kallsyms_func(struct work_struct *work)
{
	while (rdr_wait_partition("/data/lost+found", 1000) != 0)
		;

	/*�ж�PATH_FTRACE_BIN�Ƿ���ڣ���������ڣ�����Ŀ¼ */
	if (!eeye_create_dir_recursive(PATH_FTRACE_BIN, ROOT_UID, SYSTEM_GID)) {
		if (save_kallsyms()) {
			pr_info("%s, save_kallsyms unsuccessful!\n",
			       __func__);
		}
	}
}

/*************************************************************************
Function:	eeye_ftrace_init
Description:    Ԥ��ftrace�ĳ�ʼ������������buffer��ʼ����
			ftrace_callע�᣻
Input:		NA��
Return:		0����ʼ���ɹ�����0����ʼ��ʧ�ܣ�
Author:			j00207786
*************************************************************************/
static int __init eeye_ftrace_init(void)
{
	int ret;

	schedule_delayed_work(&eeye_save_kallsyms_work,
			      msecs_to_jiffies(FTRACE_REG_DELAY));

	if (!check_himntn(HIMNTN_FTRACE)) {
		pr_err("%s, HIMNTN_FTRACE is closed!\n", __func__);
		return 0;
	}

	ret = ftrace_buffers_init();
	if (ret) {
		pr_err("%s, ftrace_buffers_init failed!\n", __func__);
		return ret;
	}

	schedule_delayed_work(&eeye_ftrace_register_work,
			      msecs_to_jiffies(FTRACE_REG_DELAY));

	mntn_ftrace_enabled = true;

	pr_err("%s, success!\n", __func__);
	return 0;
}

/*************************************************************************
Function:	eeye_ftrace_exit
Description:    Ԥ��ftrace���˳�����������ftrace_call��ע�ᣬ
			buffer�ͷţ�
Input:		NA
Return:		NA
Author:			j00207786
*************************************************************************/
static void __exit eeye_ftrace_exit(void)
{
	int ret;

	if (mntn_ftrace_enabled) {
		mntn_ftrace_enabled = false;

		ret = register_ftrace_call(&mntn_eeye_ftrace_ops, 0);
		if (ret) {
			pr_err(
			       "%s, unregister mntn_eeye_ftrace_ops failed!\n",
			       __func__);
		}

		ret = register_ftrace_call(&mntn_comm_ftrace_ops, 0);
		if (ret) {
			pr_err(
			       "%s, unregister mntn_comm_ftrace_ops failed!\n",
			       __func__);
		}
	}

	kfree(g_ftrace_buffer_addr);
}

late_initcall(eeye_ftrace_init);
module_exit(eeye_ftrace_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("j00207786 <j00207786@notesmail.huawei.com>");
