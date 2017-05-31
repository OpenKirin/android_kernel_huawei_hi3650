/************************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 *************************************************************************
 文 件 名		: eagle_eye.c
 版 本 号		: 初稿
 作    者		: 蒋孝伟 j00207786
 生成日期	: 2016年4月25日
 最近修改	:
 功能描述	: 内核预警，提供可注册的预警检测和处理机制。
				:
 修改历史	:
 1.日  期		: 2016年4月25日
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
#include <linux/jiffies.h>
#include <linux/uaccess.h>
#include <linux/fcntl.h>
#include <linux/fs.h>
#include <linux/kthread.h>
#include <linux/notifier.h>
#include <linux/delay.h>
#include <linux/syscalls.h>
#include <linux/preempt.h>
#include <linux/slab.h>
#include <linux/semaphore.h>

#include <linux/hisi/eagle_eye.h>
#include <linux/hisi/util.h>
#include <mntn_public_interface.h>

int g_function_trace_enabled;
static bool early_alarm_init_done;
static struct semaphore early_alarm_sem;

/*
-1: 表示没有预警检测正在进行中，
0到(NR_CPUS-1)表示有对应编号的cpu在
进行预警检测；其他值无效。
*/
static int is_alarm_detecting = -1;
static DEFINE_SPINLOCK(g_is_alarm_detecting_lock);

static LIST_HEAD(alarm_detect_funcs_list);
static DEFINE_SPINLOCK(g_alarm_detect_funcs_list_lock);
static LIST_HEAD(alarm_process_list);
static DEFINE_SPINLOCK(g_alarm_process_list_lock);

/*记录各cpu的预警检测时间*/
static DEFINE_PER_CPU(unsigned long, alarm_detecting_timestamp);

/************************************************************************
Function:	eeye_comm_init
Description:    初始化函数，为了满足在本模块初始化之前就
			调用预警接口；
Input:		NA；
Return:		true: 初始化成功，false: 初始化失败；
Author:			j00207786
*************************************************************************/
bool eeye_comm_init(void)
{
	if (early_alarm_init_done)
		return early_alarm_init_done;

	sema_init(&early_alarm_sem, 0);
	early_alarm_init_done = true;

	pr_err("%s, early_alarm_init_done!\n", __func__);
	return early_alarm_init_done;
}

/************************************************************************
Function:	eeye_is_alarm_in_process
Description:    判断预警是否已经在处理过程中；
Input:		info：待处理的预警结构体；
Return:		0：未触发；非0：已在处理链表中；
Author:			j00207786
*************************************************************************/
static int eeye_is_alarm_in_process(u32 reason)
{
	struct alarm_detect_info *aptr;
	struct list_head *cur, *next;
	unsigned long flags;

	spin_lock_irqsave(&g_alarm_process_list_lock, flags);
	list_for_each_safe(cur, next, &alarm_process_list) {
		aptr = list_entry(cur, struct alarm_detect_info, list);
		if (NULL == aptr) {
			pr_info("%s, It might be better to look around here!\n",
				__func__);
			continue;
		}

		if (aptr->reason == reason) {
			pr_err("%s, alarm [%s] is in process!\n",
			       __func__, aptr->desc);
			spin_unlock_irqrestore(&g_alarm_process_list_lock,
					       flags);
			return 1;
		}
	}
	spin_unlock_irqrestore(&g_alarm_process_list_lock, flags);
	return 0;
}

/*************************************************************************
Function:	eeye_early_alarm
Description:	对外提供的预警接口，在系统发生异常征兆时，
			调用此接口，会通知预警系统做相关处理；
Constraints：此函数要能在原子上下文调用；
Input:		reason：预警原因；
Return:		0：预警成功；非0：预警失败；
Author:			j00207786
**************************************************************************/
int eeye_early_alarm(u32 reason, u32 cpu)
{
	struct alarm_detect_info *aptr = NULL, *p_alarm_process;
	struct list_head *cur, *next;
	unsigned long flags;

	pr_err("%s, enter!\n", __func__);

	if (EARLY_ALARM_NORMAL >= reason || EARLY_ALARM_MAX <= reason) {
		pr_err("%s, reason [%d] is invalid!\n", __func__, reason);
		return -1;
	}

	if (!eeye_comm_init()) {
		pr_err("%s, eeye_comm_init failed!\n", __func__);
		return -1;
	}

	if (eeye_is_alarm_in_process(reason)) {
		pr_err("%s, alarm is in process!\n", __func__);
		return 0;
	}

	spin_lock_irqsave(&g_alarm_detect_funcs_list_lock, flags);
	list_for_each_safe(cur, next, &alarm_detect_funcs_list) {
		aptr = list_entry(cur, struct alarm_detect_info, list);
		if (NULL == aptr) {
			pr_info("%s, It might be better to look around here!\n",
				__func__);
			continue;
		}

		if (aptr->reason == reason)
			break;
	}
	spin_unlock_irqrestore(&g_alarm_detect_funcs_list_lock, flags);

	if (NULL == aptr || aptr->reason != reason) {
		pr_err("%s, there is no alarm for reason [%d]!\n",
		       __func__, reason);
		return -1;
	}

	/*the matching kfree in eeye_early_alarm_main_process() */
	p_alarm_process = (struct alarm_detect_info *)
	    kmalloc(sizeof(struct alarm_detect_info), GFP_ATOMIC);
	if (!p_alarm_process) {
		pr_err("%s, p_alarm_process is NULL!\n", __func__);
		return -1;
	}

	memcpy((void *)p_alarm_process, (void *)aptr,
	       sizeof(struct alarm_detect_info));

	p_alarm_process->alarm_cpu = cpu;

	spin_lock_irqsave(&g_alarm_process_list_lock, flags);
	list_add_tail(&(p_alarm_process->list), &alarm_process_list);
	spin_unlock_irqrestore(&g_alarm_process_list_lock, flags);

	up(&early_alarm_sem);
	pr_err("%s, exit!\n", __func__);
	return 0;
}

/*************************************************************************
Function:		eeye_is_alarm_detecting
Description:	判断是否已经在进行预检过程中；
Input:		cpu: 发起查询的cpu编号；
Return:		0：当前无预警检测；1：有预检且未超时；
			2：有预检，但是预检超时； -1：查询无效；
Author:			j00207786
*************************************************************************/
int eeye_is_alarm_detecting(int cpu)
{
	unsigned long timestamp;
	unsigned long curtime;
	unsigned long flags;
	int ret;

	spin_lock_irqsave(&g_is_alarm_detecting_lock, flags);
	if (-1 == is_alarm_detecting) {
		ret = 0;
		goto out;
	}

	if (is_alarm_detecting < 0 ||
		is_alarm_detecting >= num_possible_cpus()) {
		pr_err("%s, is_alarm_detecting is invalid!\n", __func__);
		is_alarm_detecting = -1;
		ret = -1;
		goto out;
	}

	if (cpu == is_alarm_detecting) {
		ret = 0;
		goto out;
	}

	timestamp = per_cpu(alarm_detecting_timestamp, is_alarm_detecting);
	curtime = sched_clock();
	if ((curtime - timestamp) < ALARM_DETECT_TIMEOUT) {
		ret = 1;
		goto out;
	}

	pr_info("%s, alarm detecting on cpu [%d] is timeout!timestamp [%lu].\n",
		__func__, is_alarm_detecting, timestamp);
	ret = 2;
out:
	spin_unlock_irqrestore(&g_is_alarm_detecting_lock, flags);
	return ret;
}

/*************************************************************************
Function:		eeye_alarm_detect
Description:	内核预警检测主函数，
			此函数将植入lockup detector的timer处理函数中；
Constraints:	此函数运行在原子上下文，
			其内的操作不能含有睡眠调度；
Input:		NA；
Return:		0：无异常；非0：检测到异常；
Author:			j00207786
*************************************************************************/
int eeye_alarm_detect(void)
{
	struct alarm_detect_info *aptr;
	struct list_head *cur, *next;
	unsigned long flags;
	int cpu = smp_processor_id();

	if (unlikely(oops_in_progress))
		return 0;

	if (list_empty(&alarm_detect_funcs_list))
		return 0;

	if (1 == eeye_is_alarm_detecting(cpu))
		return 0;

	spin_lock_irqsave(&g_is_alarm_detecting_lock, flags);
	is_alarm_detecting = cpu;
	__this_cpu_write(alarm_detecting_timestamp,/*lint !e666 */
					sched_clock());
	spin_unlock_irqrestore(&g_is_alarm_detecting_lock, flags);

	spin_lock_irqsave(&g_alarm_detect_funcs_list_lock, flags);
	list_for_each_safe(cur, next, &alarm_detect_funcs_list) {
		aptr = list_entry(cur, struct alarm_detect_info, list);
		if (NULL == aptr) {
			pr_info("%s, It might be better to look around here!\n",
				__func__);
			continue;
		}

		if (NULL == aptr->detect) {
			pr_err("%s, detect func of alarm [%d] is null !\n",
			       __func__, aptr->reason);
			continue;
		}

		if (aptr->detect(aptr)) {
			spin_unlock_irqrestore(&g_alarm_detect_funcs_list_lock,
					       flags);
			if (eeye_early_alarm(aptr->reason,
							is_alarm_detecting)) {
				pr_err
				    ("%s, eeye_early_alarm failed!reason [%d]\n",
				     __func__, aptr->reason);
			}
			spin_lock_irqsave(&g_alarm_detect_funcs_list_lock,
					  flags);
		}
	}
	spin_unlock_irqrestore(&g_alarm_detect_funcs_list_lock, flags);
	return 0;
}

/*************************************************************************
Function:		eeye_alarm_process_list_empty
Description:	判断alarm_process_list是否为空；
Input:		NA；
Return:		false：链表非空； true：链表空；
Author:		j00207786
*************************************************************************/
static bool eeye_alarm_process_list_empty(void)
{
	return list_empty(&alarm_process_list);
}

/*************************************************************************
Function:		eeye_early_alarm_main_process
Description:	预警处理线程的处理函数；
Input:		NULL；
Return:		NULL；
Author:		j00207786
*************************************************************************/
static int eeye_early_alarm_main_process(void *data)
{
	struct list_head *cur, *next;
	struct alarm_detect_info *aptr;
	unsigned long jiffies, flags;

	while (!kthread_should_stop()) {
		jiffies = msecs_to_jiffies(ALARM_DETECT_TIMEOUT / USEC_PER_SEC);
		if (down_timeout(&early_alarm_sem, jiffies)) {
			if (eeye_alarm_process_list_empty())
				continue;
		}

		while (!eeye_alarm_process_list_empty()) {
			spin_lock_irqsave(&g_alarm_process_list_lock, flags);
			list_for_each_safe(cur, next, &alarm_process_list) {
				aptr =
				    list_entry(cur, struct alarm_detect_info,
					       list);
				if (NULL == aptr) {
					pr_info
					    ("%s, Something unexpected happened!\n",
					     __func__);
					continue;
				}

				if (NULL == aptr->process) {
					pr_err
					    ("%s, process func for reason [%d] is null!\n",
					     __func__, aptr->reason);
					continue;
				}

				spin_unlock_irqrestore
				    (&g_alarm_process_list_lock, flags);
				(void)aptr->process(aptr);
				spin_lock_irqsave(&g_alarm_process_list_lock,
						  flags);

				list_del(&(aptr->list));

				/*the matching kmalloc in eeye_early_alarm(). */
				kfree(aptr);
				aptr = NULL;
			}
			spin_unlock_irqrestore(&g_alarm_process_list_lock,
					       flags);
		}
	}
	return 0;
}

/*************************************************************************
Function:	eeye_is_alarm_registered
Description:    判断预警是否已经注册过；
Input:		info：待注册的预警结构体；
Return:		0：未注册过；非0：已注册过；
Author:			j00207786
*************************************************************************/
static int eeye_is_alarm_registered(struct alarm_detect_info *info)
{
	struct list_head *cur, *next;
	struct alarm_detect_info *aptr;
	unsigned long flags;

	if (IS_ERR_OR_NULL(info) || IS_ERR_OR_NULL(info->detect)) {
		pr_err("%s, info is invalid!\n", __func__);
		return -1;
	}

	spin_lock_irqsave(&g_alarm_detect_funcs_list_lock, flags);
	list_for_each_safe(cur, next, &alarm_detect_funcs_list) {
		aptr = list_entry(cur, struct alarm_detect_info, list);
		if (NULL == aptr) {
			pr_info("%s, It might be better to look around here!\n",
				__func__);
			continue;
		}

		if (aptr->reason == info->reason) {
			spin_unlock_irqrestore(&g_alarm_detect_funcs_list_lock,
					       flags);
			pr_err("%s, reason [%d] has already registered!\n",
			       __func__, info->reason);
			return info->reason;	/*reason大于0 */
		}
	}
	spin_unlock_irqrestore(&g_alarm_detect_funcs_list_lock, flags);
	return 0;
}

/*************************************************************************
Function:	eeye_register_alarm_detect_function
Description:    对外提供的预警注册接口；
Input:		info：待注册的预警结构体；
Return:		0：注册成功；非0：注册失败；
Author:			j00207786
*************************************************************************/
int eeye_register_alarm_detect_function(struct alarm_detect_info *info)
{
	struct alarm_detect_info *p_alarm_info;
	unsigned long flags;

	if (IS_ERR_OR_NULL(info) || IS_ERR_OR_NULL(info->detect)) {
		pr_err("%s, info is invalid!\n", __func__);
		return -1;
	}

	if (info->reason >= EARLY_ALARM_MAX
	    || info->reason <= EARLY_ALARM_NORMAL) {
		pr_err("%s, reason is invalid!\n", __func__);
		return -1;
	}

	if (!eeye_comm_init()) {
		pr_err("%s, eeye_comm_init failed!\n", __func__);
		return -1;
	}

	/*wether is already in the list */
	if (eeye_is_alarm_registered(info) > 0) {
		pr_err("%s, the alarm has already registered!\n", __func__);
		return 0;
	}

	p_alarm_info = kmalloc(sizeof(struct alarm_detect_info), GFP_ATOMIC);
	if (p_alarm_info == NULL) {
		pr_err("%s, p_alarm_info is NULL!\n", __func__);
		return -1;
	}
	memcpy((void *)p_alarm_info, (void *)info,
	       sizeof(struct alarm_detect_info));

	spin_lock_irqsave(&g_alarm_detect_funcs_list_lock, flags);
	list_add_tail(&(p_alarm_info->list), &alarm_detect_funcs_list);
	spin_unlock_irqrestore(&g_alarm_detect_funcs_list_lock, flags);

	pr_err("%s, success!\n", __func__);
	return 0;
}

/*************************************************************************
Function:		eeye_print_all_alarm_detect_info
Description:	预警信息打印函数；
Input:		NA
Return:		NA
Author:			j00207786
*************************************************************************/
void eeye_print_all_alarm_detect_info(void)
{
	struct list_head *cur, *next;
	struct alarm_detect_info *aptr;
	unsigned long flags;

	spin_lock_irqsave(&g_alarm_detect_funcs_list_lock, flags);
	list_for_each_safe(cur, next, &alarm_detect_funcs_list) {
		aptr = list_entry(cur, struct alarm_detect_info, list);
		if (NULL == aptr) {
			pr_info("%s, It might be better to look around here!\n",
				__func__);
			continue;
		}

		pr_err("%s, alarm reason [%d] desc [%s]!\n",
		       __func__, aptr->reason, aptr->desc);
	}
	spin_unlock_irqrestore(&g_alarm_detect_funcs_list_lock, flags);
}

/*************************************************************************
Function:	eeye_early_alarm_init
Description:    预警系统的初始化函数，包括守护线程的初始化；
Input:		NA；
Return:		0：初始化成功；非0：初始化失败；
Author:			j00207786
*************************************************************************/
static int __init eeye_early_alarm_init(void)
{
	struct task_struct *eeye_main = NULL;
	struct sched_param param;

	if (!check_himntn(HIMNTN_FTRACE)) {
		pr_err("%s, HIMNTN_EAGLE_EYE is closed!\n", __func__);
		return 0;
	}

	if (!eeye_comm_init()) {
		pr_err("%s, eeye_comm_init failed!\n", __func__);
		return -1;
	}

	eeye_main = kthread_run(eeye_early_alarm_main_process,
				NULL, "eagle_eye_main_process");
	if (!eeye_main) {
		pr_err("%s, create thread eagle_eye_main_process failed.\n",
		       __func__);
		return -1;
	}

	param.sched_priority = EAGLE_EYE_RT_PRIORITY;
	if (sched_setscheduler(eeye_main, SCHED_FIFO, &param)) {
		pr_err
		    ("%s, sched_setscheduler eagle_eye_main_process failed.\n",
		     __func__);
		kthread_stop(eeye_main);
		return -1;
	}
	pr_err("%s, success!\n", __func__);
	return 0;
}

static void __exit eeye_early_alarm_exit(void)
{
}

core_initcall(eeye_early_alarm_init);
module_exit(eeye_early_alarm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("j00207786 <j00207786@notesmail.huawei.com>");
