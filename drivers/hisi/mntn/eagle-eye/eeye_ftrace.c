/************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 *************************************************************************
 文 件 名		: eeye_ftrace.c
 版 本 号		: 初稿
 作    者		: 蒋孝伟 j00207786
 生成日期	: 2016年5月3日
 最近修改	:
 功能描述	: ftrace动态预警记录
				:
 修改历史	:
 1.日  期		: 2016年5月3日
    作  者		: 蒋孝伟 j00207786
    修改内容	: 创建文件

 *************************************************************************/

/*************************************************************************
  1 头文件包含
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

/*表示ftrace钩子是否已注册*/
static bool g_eeye_ftrace_register;

/*用于控制BUF_B的记录开关*/
static bool g_eeye_ftrace_tracing_on;

/*mntn dump使用*/
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

/*标记对应cpu的percpu buffer是否满，针对非循环buffer*/
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
Description:	设置ftrace buffer的保存最小间隔；
Input:		lifetime: buffer保存为文件的最小间隔时间，单位秒；
Return:		NA
Author:		j00207786
*************************************************************************/
void set_ftrace_buffer_lifetime(unsigned long lifetime)
{
	g_ftrace_buffer_lifetime = lifetime * NSEC_PER_SEC;
}

/*************************************************************************
Function:		ftrace_buffer_alloc
Description:	申请ftrace记录使用的内存，并初始化buffer的数据头；
Input:		NA；
Return:		0：初始化成功；非0：初始化失败；
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
Description:	申请ftrace记录使用的内存，并初始化buffer的数据头；
Input:		NA；
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
Description:	ftrace轨迹记录区数据头的初始化
Input:		buffer_info:待初始化数据头指针；
			buffer_addr:buffer地址，不包括buffer_info；
			idx:buffer序号；size:buffer大小；
			is_percpu:buffer是否percpu分配;
			is_loop:buffer是否循环记录;
Return:		0：初始化成功；非0：初始化失败；
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
	   此为buffer分配比例，可支持最大8个cpu的架构，
	   第一行表示单cpu架构，第八行代表8核架构；
	   buffer被分为16等份，每一行中的数值从左到右，
	   分别代表cpu0-n所占的比例；
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
Description:	检查地址是否在合法范围内；
Input:		NA
Return:		0：地址未溢出；非0：buffer溢出；
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
Description:	ftrace轨迹记录区域的初始化
Input:		NA
Return:		0：初始化成功；非0：初始化失败；
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
Description:	判断ftrace buffer是否满，循环buffer不会满；
Input:		finfo: buffer描述符；
			cpu: 对应buffer所在cpu(仅在percpu模式下有意义)；
Return:		0：buffer未满，1：buffer已满；-1: 查询条件异常；
Author:		j00207786
*************************************************************************/
static int is_ftrace_buffer_full(struct ftrace_buffer_head *finfo, int cpu)
{
	if (IS_ERR_OR_NULL(finfo) || cpu < 0
		|| cpu >= num_possible_cpus()
	    || !finfo->buffer_len)
		return -1;

	/*循环buffer 则恒为不满 */
	if (finfo->is_loop)
		return BUFFER_NOT_FULL;

	/*如果是percpu，则根据cpu号，判断具体的percpu buffer是否满 */
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
Description:	ftrace轨迹数据写buffer函数;
Input:		entry: 一条ftrace轨迹数据;
Return:		NA；
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
Description:	ftrace轨迹记录函数，使用BUF_B;
Input:		entry：ftrace一条记录的数据结构；
			ip: 当前指令地址；parent_ip:调用者指令地址；
			flags: 中断标志；pc: 抢占计数;
Return:		NA；
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
Description:	控制ftrace轨迹记录区域BUF_B的记录开关；
Input:		on: 0,关闭；1及非0值,打开；
Return:		NA；
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
Description:	ftrace轨迹记录函数，使用BUF_B，BUF_B说明:
			此buffer在预警发生时，停止记录、保存、再启动记录；
Input:		ip：当前PC；parent_ip：调用者pc；op：当前注册的ops；
			regs：当前执行寄存器上下文（不支持，默认为NULL）；
Return:		NA；
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
Description:	ftrace轨迹记录函数，使用BUF_A，BUF_A说明:
			此buffer在特性打开时，一直保存记录状态不会停；
Input:		ip：当前PC；parent_ip：调用者pc；op：当前注册的ops；
			regs：当前执行寄存器上下文（不支持，默认为NULL）；
Return:		NA；
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
Description:	注册ftrace钩子函数；
Input:		ops：ftrace操作函数；on：1表示注册，0表示去注册；
Return:		0：注册成功；非0注册失败；
Other:		在预警系统的初始化函数中调用；
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
Description:	建立指定目录；
Input:		path: 待创建目录名；user: 目录uid; group: 目录gid；
Return:		0: 创建成功，非0: 创建失败；
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
Description:	递归建立指定目录；
Input:		path: 待创建目录名；user: 目录uid; group: 目录gid；
Return:		0: 创建成功，非0: 创建失败；
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
Description:	从ftrace.bin文件名中获取日期；
Input:		ftrace_bin: 待获取日志的文件名；
Return:		0: 日期格式不合法，或日期转换失败；
			非0: 日期；
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
Description:	将ftrace.bin按文件名中的日期降序排列；
Input:		info: 描述ftrace.bin的信息结构体；
Return:		0: 添加成功；非0: 添加失败；
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
Description:	返回文件在eeye_ftrace_bin_list中的序号，起始序号为0；
Input:		filename: 待查文件名；
Output:		fptrp: 描述ftrace_bin的结构体指针；
Return:		-1: 未查找到；>=0: 对应序号；
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
Description:	将eeye_ftrace_bin_list内的信息打印出来；
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
Description:	将指定路径下的ftrace.bin按日期降序排列；
Input:		path:待检查目录;
Return:		NA；
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

	for (count = 0; count < LOOP_COUNT_MAX; count++) {	/*防止死循环 */
		bufsize =
		    sys_getdents(fd, (struct linux_dirent *)buf, TMP_BUF_SIZE);
		if (bufsize == -1) {
			pr_err("[%s], sys_getdents failed, ret [%d]\n",
			       __func__, bufsize);
			goto out;
		}

		if (0 == bufsize) {
			/*处理结束 */
			break;
		}

		for (bpos = 0; bpos < bufsize; bpos += d->d_reclen) {
			d = (struct linux_dirent *)(buf + bpos);
			d_type = *(buf + bpos + d->d_reclen - 1);
			snprintf(fullname, sizeof(fullname), "%s/%s", path,
				 d->d_name);

			/*处理文件 */
			if (d_type == DT_REG) {

				/*检查文件格式，获取文件中的日志 */
				if (strncmp
				    (d->d_name, PREFIX_FTRACE_BIN,
				     strlen(PREFIX_FTRACE_BIN))
				    && strncmp(d->d_name, KSYMS_BIN,
					       strlen(KSYMS_BIN))) {
					/*不合规的文件删除 */
					sys_unlink(fullname);
					continue;
				}

				/*跳过符号文件KSYMS_BIN */
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
Description:	限制ftrace.bin保存的个数，大于num的老的文件删除；
Input:		path:待检查目录，num:可保留的ftrace.bin文件个数;
Return:		NA；
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

	for (count = 0; count < LOOP_COUNT_MAX; count++) {	/*防止死循环 */
		bufsize =
		    sys_getdents(fd, (struct linux_dirent *)buf, TMP_BUF_SIZE);
		if (bufsize == -1) {
			pr_err("[%s], sys_getdents failed, ret [%d]\n",
			       __func__, bufsize);
			goto out;
		}

		if (0 == bufsize) {
			/*处理结束 */
			break;
		}

		for (bpos = 0; bpos < bufsize; bpos += d->d_reclen) {
			d = (struct linux_dirent *)(buf + bpos);
			d_type = *(buf + bpos + d->d_reclen - 1);
			snprintf(fullname, sizeof(fullname), "%s/%s", path,
				 d->d_name);

			/*处理目录，过滤"."和".."目录，否则会无限递归 */
			if (d_type == DT_DIR
			    && strncmp(d->d_name, ".", sizeof("."))
			    && strncmp(d->d_name, "..", sizeof(".."))) {

				/*打印文件夹名 */
				pr_info(
				       "[%s], there should be no dir [%s]!\n",
				       __func__, d->d_name);
			} else if (d_type == DT_REG) {	/*处理文件 */
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
Description:	获取年月日的时间戳；
Input:		NA
Return:		年月日小时分秒的字符串；
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
Description:	保存buffer到文件；
Input:		logpath:待保存目录，filename:文件名；buf: 待保存内存buffer；
			len: buf长度； is_append: 是否追加写到filename；
Return:		0:保存成功，非0: 保存失败；
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

	/*根据权限要求，目录及子目录群组调整为root-system */
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
Description:	保存ftrace.bin到文件系统；
Input:		finfo: buffer描述符;
			type: 0仅保存finfo所指向buffer，1保存整个ftrace_buffer
Return:		0：保存成功；1：保存失败；
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

	/*判断PATH_FTRACE_BIN是否存在，如果不存在，建立目录 */
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

		/*将ftrace_buffer_head头信息也保存到文件中 */
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
Description:	保存所有内核符号到文件；
Input:		data：输出参数；namebuf：符号名；
			module_info：未使用；addr：符号地址；
Return:		0：保存成功；非0：保存失败；
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
Description:	获取内核函数符号的个数；
Input:		NA；
Return:		0：保存成功；非0：保存失败；
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
Description:	保存所有内核符号到文件；
Input:		NA；
Return:		0：保存成功；非0：保存失败；
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
	if (0 == fd) {		/*KSYMS_BIN文件存在，直接返回 */
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
Description:	设置ftrace buffer的预警原因；
Input:		reason: 此次buffer保存的预警原因；
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
Description:	保存HK_FTRACE_BUF_B为文件；
			供内核预警模块调用；
Input:		reason: 此次buffer保存的预警原因；
Return:		0: 保存成功，非0: 保存不成功；
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

	/*如果最近有触发过记录，且不超过时间阈值，
	   则不需要再次记录 */
	delta = sched_clock() - finfo->stop_timestamp;
	if (delta < g_ftrace_buffer_lifetime && finfo->stop_timestamp) {
		pr_info(
		       "%s, trigger too many ftracer, would not save ftrace.bin!\n",
		       __func__);
		return 0;
	}

	if (reason < EARLY_ALARM_MAX && reason >= EARLY_ALARM_NORMAL)
		finfo->reason = reason;

	/*先解注册ftrace函数，添加完成后，再注册回去 */
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

	/*限制ftrace.bin文件的个数 */
	restrict_ftrace_bin_num(PATH_FTRACE_BIN, FTRACE_BIN_NUM_LIMIT);

	if (preemptible()) {
		/* 确保之前的所有文件系统相关操作都能完成 */
		sys_sync();
	}
	pr_err("%s, exit!\n", __func__);
	return ret;
}

/*************************************************************************
Function:		test_eeye_ftrace
Description:	ftrace.bin保存测试函数；
Input:		type: 0 表示保存BUF_B，
			1 表示保存整个ftrace buffer,包括BUF_A;
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

	/*先解注册ftrace函数，添加完成后，再注册回去 */
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
Description:    向mntn dump模块注册，保存ftrace head数据头；
Input:		NA；
Return:		0：注册成功；非0：注册失败；
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
Description:    预警ftrace的ftrace_call及mntn dump注册；
Input:		work: 执行本函数的work指针；
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
Description:	保存内核符号表
Input:		work: 执行本函数的work指针；
Return:		NA
Author:			j00207786
*************************************************************************/
static void eeye_save_kallsyms_func(struct work_struct *work)
{
	while (rdr_wait_partition("/data/lost+found", 1000) != 0)
		;

	/*判断PATH_FTRACE_BIN是否存在，如果不存在，建立目录 */
	if (!eeye_create_dir_recursive(PATH_FTRACE_BIN, ROOT_UID, SYSTEM_GID)) {
		if (save_kallsyms()) {
			pr_info("%s, save_kallsyms unsuccessful!\n",
			       __func__);
		}
	}
}

/*************************************************************************
Function:	eeye_ftrace_init
Description:    预警ftrace的初始化函数，包括buffer初始化，
			ftrace_call注册；
Input:		NA；
Return:		0：初始化成功；非0：初始化失败；
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
Description:    预警ftrace的退出函数，包括ftrace_call解注册，
			buffer释放；
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
