/************************************************************************

  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 *************************************************************************
 �� �� ��		: eagle_eye.c
 �� �� ��		: ����
 ��    ��		: ��Тΰ j00207786
 ��������	: 2016��4��25��
 ����޸�	:
 ��������	: �ں�Ԥ�����ṩ��ע���Ԥ�����ʹ�����ơ�
				:
 �޸���ʷ	:
 1.��  ��		: 2016��4��25��
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
-1: ��ʾû��Ԥ��������ڽ����У�
0��(NR_CPUS-1)��ʾ�ж�Ӧ��ŵ�cpu��
����Ԥ����⣻����ֵ��Ч��
*/
static int is_alarm_detecting = -1;
static DEFINE_SPINLOCK(g_is_alarm_detecting_lock);

static LIST_HEAD(alarm_detect_funcs_list);
static DEFINE_SPINLOCK(g_alarm_detect_funcs_list_lock);
static LIST_HEAD(alarm_process_list);
static DEFINE_SPINLOCK(g_alarm_process_list_lock);

/*��¼��cpu��Ԥ�����ʱ��*/
static DEFINE_PER_CPU(unsigned long, alarm_detecting_timestamp);

/************************************************************************
Function:	eeye_comm_init
Description:    ��ʼ��������Ϊ�������ڱ�ģ���ʼ��֮ǰ��
			����Ԥ���ӿڣ�
Input:		NA��
Return:		true: ��ʼ���ɹ���false: ��ʼ��ʧ�ܣ�
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
Description:    �ж�Ԥ���Ƿ��Ѿ��ڴ�������У�
Input:		info���������Ԥ���ṹ�壻
Return:		0��δ��������0�����ڴ��������У�
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
Description:	�����ṩ��Ԥ���ӿڣ���ϵͳ�����쳣����ʱ��
			���ô˽ӿڣ���֪ͨԤ��ϵͳ����ش���
Constraints���˺���Ҫ����ԭ�������ĵ��ã�
Input:		reason��Ԥ��ԭ��
Return:		0��Ԥ���ɹ�����0��Ԥ��ʧ�ܣ�
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
Description:	�ж��Ƿ��Ѿ��ڽ���Ԥ������У�
Input:		cpu: �����ѯ��cpu��ţ�
Return:		0����ǰ��Ԥ����⣻1����Ԥ����δ��ʱ��
			2����Ԥ�죬����Ԥ�쳬ʱ�� -1����ѯ��Ч��
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
Description:	�ں�Ԥ�������������
			�˺�����ֲ��lockup detector��timer�������У�
Constraints:	�˺���������ԭ�������ģ�
			���ڵĲ������ܺ���˯�ߵ��ȣ�
Input:		NA��
Return:		0�����쳣����0����⵽�쳣��
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
Description:	�ж�alarm_process_list�Ƿ�Ϊ�գ�
Input:		NA��
Return:		false������ǿգ� true������գ�
Author:		j00207786
*************************************************************************/
static bool eeye_alarm_process_list_empty(void)
{
	return list_empty(&alarm_process_list);
}

/*************************************************************************
Function:		eeye_early_alarm_main_process
Description:	Ԥ�������̵߳Ĵ�������
Input:		NULL��
Return:		NULL��
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
Description:    �ж�Ԥ���Ƿ��Ѿ�ע�����
Input:		info����ע���Ԥ���ṹ�壻
Return:		0��δע�������0����ע�����
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
			return info->reason;	/*reason����0 */
		}
	}
	spin_unlock_irqrestore(&g_alarm_detect_funcs_list_lock, flags);
	return 0;
}

/*************************************************************************
Function:	eeye_register_alarm_detect_function
Description:    �����ṩ��Ԥ��ע��ӿڣ�
Input:		info����ע���Ԥ���ṹ�壻
Return:		0��ע��ɹ�����0��ע��ʧ�ܣ�
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
Description:	Ԥ����Ϣ��ӡ������
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
Description:    Ԥ��ϵͳ�ĳ�ʼ�������������ػ��̵߳ĳ�ʼ����
Input:		NA��
Return:		0����ʼ���ɹ�����0����ʼ��ʧ�ܣ�
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
