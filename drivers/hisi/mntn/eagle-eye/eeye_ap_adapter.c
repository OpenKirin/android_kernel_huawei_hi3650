/***************************************************************

  版权所有 (C), 2001-2011, 华为技术有限公司

 ***************************************************************
 文 件 名		: eeye_ap_adapter.c
 版 本 号		: 初稿
 作    者		: 蒋孝伟 00207786
 生成日期	: 2016年4月25日
 最近修改	:
 功能描述	: 内核预警，ap适配。
				:
 修改历史	:
 1.日  期		: 2016年4月25日
    作  者		: 蒋孝伟 00207786
    修改内容	: 创建文件

 ***************************************************************/

/***************************************************************
  1 头文件包含
 ***************************************************************/
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
#include <linux/preempt.h>
#include <linux/random.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/timer.h>

#include <linux/hisi/util.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/hisi/hisi_sp805_wdt.h>
#include <linux/hisi/eagle_eye.h>
#include <linux/hisi/eeye_ftrace_pub.h>
#include <mntn_public_interface.h>
#include "eeye_ap_adapter.h"
#include "eeye_ftrace.h"
#include "../../../../kernel/sched/sched.h"

/*eeye_alarm_reentry_test函数使用测试变量*/
static int no_reentry;

static DEFINE_SPINLOCK(g_eeye_test_task_sched_lock);

/*************************************************************************
Function:		eeye_watchdog_kick_detect
Description:	检测硬狗的喂狗状态；
Input:		info: 预警信息；
Return:		0：无异常；非0：有异常；
Author:			j00207786
*************************************************************************/
static int eeye_watchdog_kick_detect(struct alarm_detect_info *info)
{
	u64 cur_slice = get_32k_abs_timer_value();
	u64 last_kick_slice = rdr_get_last_wdt_kick_slice();
	u64 kicktime = (u64) get_wdt_kick_time();

	if (kicktime > DEFAULT_WDT_TIMEOUT) {
		pr_err("%s, kicktime [%llu] is invalid!\n", __func__, kicktime);
		return 0;
	}

	if ((0 == kicktime) || (0 == last_kick_slice)) {
		/*如果关狗，此处可能会频繁走到 */
		return 0;
	}
	pr_debug
		("%s, enter!cur_slice[0x%llu] last_kick_slice [0x%llu] kicktime [0x%llu]\n",
		__func__, cur_slice, last_kick_slice, kicktime);

	if ((cur_slice - last_kick_slice) >
	    ((kicktime + WDT_KICK_TIMEOUT_DELTA) * SLICE_COUNT_PER_SEC)) {
		pr_err("%s, kick timeout!\n", __func__);
		info->alarm_cpu = 0;
		return -1;
	}
	return 0;
}

/*************************************************************************
Function:		eeye_watchdog_kick_eprocess
Description:	硬狗喂狗异常后的处理函数；
Input:		info: 预警信息；
Return:		0：处理正常；非0：处理出现异常；
Author:		j00207786
*************************************************************************/
static int eeye_watchdog_kick_eprocess(struct alarm_detect_info *info)
{
	u64 expires, slice, last_kick_slice;

	pr_err("%s, enter!\n", __func__);
	expires = get_wdt_expires_time();
	slice = get_32k_abs_timer_value();
	last_kick_slice = rdr_get_last_wdt_kick_slice();
	pr_err
		("%s, expires [%llu] jiffies [%llu] slice [%llu] timer_jiffies [%lu] last_kick_slice [%llu]!\n",
	     __func__, expires, jiffies_64, slice,
	     boot_tvec_bases.timer_jiffies, last_kick_slice);

	/*狗复位，ftrace.bin的保存放到重启后 */
	eeye_set_fb_reason(EARLY_ALARM_AWDT_NO_KICK);
	pr_err("%s, exit!\n", __func__);
	return 0;
}

#ifdef CONFIG_SCHEDSTATS
/*************************************************************************
Function:		eeye_task_sched_detect
Description:	检测内核任务调度的侦测函数；
Input:		info: 预警信息；
Return:		0：无异常；非0：有异常；
Author:		j00207786
*************************************************************************/
static int eeye_task_sched_detect(struct alarm_detect_info *info)
{
	int i;
	u64 nr_switches;
	unsigned long long delta, delta2;
	struct rq *rq;
	struct sched_stat_info *sched_info;
	u32 cpu_num = num_possible_cpus();

	pr_debug("%s, enter!\n", __func__);
	sched_info = (struct sched_stat_info *)info->data;

	for (i = 0; i < cpu_num; i++) {
		rq = cpu_rq(i);

		nr_switches = rq->nr_switches;	/*相当于锁 */

		/*如果cpu不在线或处于idle，跳过 */
		if (0 == rq->online || rq->curr == rq->idle)
			continue;

		delta = rq->clock - rq->curr->sched_info.last_arrival;
		delta2 = sched_clock_cpu(i) - rq->curr->sched_info.last_arrival;
		if ((delta > NO_SCHED_TIMEOUT &&
		     (0 == (rq->nr_switches - nr_switches))) ||
		    (delta2 > NO_SCHED_TIMEOUT &&
		     (0 == (rq->nr_switches - nr_switches)))) {
			info->alarm_cpu = i;
			sched_info->last_arrival =
			    rq->curr->sched_info.last_arrival;

			if (0 == sched_info->last_arrival) {
				info->alarm_cpu = -1;
				memset(sched_info, 0,
				       sizeof(struct sched_stat_info));
				continue;
			}

			if (delta > NO_SCHED_TIMEOUT)
				sched_info->delta = delta;
			else
				sched_info->delta = delta2;

			(void)strncpy(sched_info->comm, rq->curr->comm, TASK_COMM_LEN - 1);/* [false alarm] */
			sched_info->comm[TASK_COMM_LEN - 1] = '\0';

			/*如果nr_switches与入口处记录的不等，则发生过任务切换 */
			if (0 != (rq->nr_switches - nr_switches)) {
				info->alarm_cpu = -1;
				memset(sched_info, 0,
				       sizeof(struct sched_stat_info));
				continue;
			}
			pr_warn
			    ("%s, task [%s] on cpu [%d] is blocked [%llu]ns!\n",
			     __func__, sched_info->comm, i, sched_info->delta);
			return -1;
		}
	}
	return 0;
}

/*************************************************************************
Function:		eeye_task_sched_thread_fn
Description:	内核任务调度异常后的处理线程函数，
			包括文件系统操作；
			单独起线程，避免eeye主线程被挂死；
Input:		info: 预警信息；
Return:		0：处理正常；非0：处理出现异常；
Author:			j00207786
*************************************************************************/
static int eeye_task_sched_thread_fn(void *data)
{
	int ret;

	ret = save_eeye_ftrace_buffer(EARLY_ALARM_TASK_NO_SCHED);
	if (ret) {
		pr_err("%s, save_eeye_ftrace_buffer failed!\n", __func__);
		return ret;
	}
	return 0;
}

/*************************************************************************
Function:		eeye_task_sched_eprocess
Description:	内核任务调度异常后的处理函数；
Input:		info: 预警信息；
Return:		0：处理正常；非0：处理出现异常；
Author:			j00207786
*************************************************************************/
static int eeye_task_sched_eprocess(struct alarm_detect_info *info)
{
	struct sched_stat_info *sched_info;
	int ret = 0;

	pr_info("%s, enter!\n", __func__);
	if (NULL == info->data) {
		pr_info("%s, info->data is null!\n", __func__);
		return -1;
	}

	sched_info = (struct sched_stat_info *)info->data;
	pr_warn("%s, last_arrival [%llu] delta [%llu] comm [%s]!\n",
		   __func__, sched_info->last_arrival,
		   sched_info->delta, sched_info->comm);
	memset(sched_info, 0, sizeof(struct sched_stat_info));

	if (!kthread_run(eeye_task_sched_thread_fn,
			 NULL, "eeye_task_sched_thread_fn")) {
		pr_err("%s, create thread eeye_task_sched_thread_fn failed.\n",
		       __func__);
		ret = -1;
	}
	pr_info("%s, exit!\n", __func__);
	return ret;
}
#endif

/*************************************************************************
Function:		eeye_test_detect
Description:	预警测试函数；
Constraints:	此函数在原子上下文，禁止使用会睡眠的函数；
Input:		NA
Return:		0：处理成功；非0：处理失败；
Author:		j00207786
*************************************************************************/
static int eeye_test_detect(struct alarm_detect_info *info)
{
	pr_debug("%s, enter!\n", __func__);
	if (!no_reentry) {
		no_reentry++;
		mdelay(4000);
		return 0;
	}
	return 0;
}

/*[EARLY_ALARM_ID_MAX-1]: 排除EARLY_ALARM_TEST_ID*/
static struct alarm_detect_info
	g_ap_alarm_detect_list[EARLY_ALARM_ID_MAX - 1] = {
	{
	 .reason = EARLY_ALARM_AWDT_NO_KICK,
	 .alarm_cpu = -1,
	 .detect = eeye_watchdog_kick_detect,
	 .process = eeye_watchdog_kick_eprocess,
	 .desc = "ALARM_AWDT_NO_KICK",
	 },
#ifdef CONFIG_SCHEDSTATS
	{
	 .reason = EARLY_ALARM_TASK_NO_SCHED,
	 .alarm_cpu = -1,
	 .data = NULL,
	 .detect = eeye_task_sched_detect,
	 .process = eeye_task_sched_eprocess,
	 .desc = "ALARM_TASK_NO_SCHED",
	 }
#endif
};

static struct alarm_detect_info g_alarm_detect_test = {
	.reason = EARLY_ALARM_TEST,
	.alarm_cpu = -1,
	.detect = eeye_test_detect,
	.process = NULL,
	.desc = "ALARM_TEST",
};

/*************************************************************************
Function:		eeye_test_alarm_reentry
Description:	预警检测重入测试实体功能函数；
Input:		NA
Return:		NA
Author:		j00207786
*************************************************************************/
static int eeye_test_alarm_reentry(void *data)
{
	while (1) {
		if (1 == eeye_is_alarm_detecting(1)) {
			pr_err("%s, alarm detect is already in process!\n",
			       __func__);
			break;
		}
		msleep(500);
	}
	return 0;
}

/*************************************************************************
Function:		eeye_alarm_reentry_test
Description:	预警检测重入测试函数；
Input:		NA
Return:		NA
Author:		j00207786
*************************************************************************/
void eeye_alarm_reentry_test(void)
{
	int ret;

	ret = eeye_register_alarm_detect_function(&g_alarm_detect_test);
	if (ret) {
		pr_err
		    ("%s, eeye_register_alarm_detect_function failed, reason [%d]!\n",
		     __func__, g_alarm_detect_test.reason);
	}

	no_reentry = 0;

	if (!kthread_run(eeye_test_alarm_reentry,
			 NULL, "eeye_test_alarm_reentry")) {
		pr_err("%s, create thread eeye_test_alarm_reentry failed.\n",
		       __func__);
	}
}

/*************************************************************************
Function:		eeye_get_random
Description:	获取随机数；
Input:		NA
Return:		NA
Author:		j00207786
*************************************************************************/
u8 eeye_get_random(u32 range)
{
	u8 r = 0;

	get_random_bytes(&r, 1);
	pr_err("%s, random [%d]!\n", __func__, r);
	r %= range;
	pr_err("%s, range random [%d]!\n", __func__, r);
	return r;
}

/*************************************************************************
Function:		eeye_test_repeat_alarms
Description:	重复预警压力测试函数；
Input:		NA
Return:		NA
Author:		j00207786
*************************************************************************/
static int eeye_test_repeat_alarms(void *data)
{
	u8 r;
	u32 msleep_time;
	int this_cpu = raw_smp_processor_id();

	/*使可以频繁保存ftrace.bin */
	set_ftrace_buffer_lifetime(0);
	while (1) {
		r = eeye_get_random(EARLY_ALARM_MAX - 1);
		(void)eeye_early_alarm(r, this_cpu);
		msleep_time = eeye_get_random(60000);
		msleep(msleep_time);
	}
	return 0;
}

/*************************************************************************
Function:		eeye_pressure_test_repeat_alarms
Description:	预警压力测试函数；
Input:		NA
Return:		NA
Author:		j00207786
*************************************************************************/
void eeye_pressure_test_repeat_alarms(void)
{
	if (!eeye_comm_init()) {
		pr_err("%s,eeye_comm_init failed!\n", __func__);
		return;
	}

	if (!kthread_run(eeye_test_repeat_alarms,
			 NULL, "eeye_test_repeat_alarms")) {
		pr_err("%s, create thread eeye_test_repeat_alarms failed.\n",
		       __func__);
	}
}

/*************************************************************************
Function:		eeye_test_illegal_alarms
Description:	非法预警注册测试函数；
Input:		type: 0,非法reason；1，detect函数非法；
			2，注册TEST预警；
Return:		NA
Author:		j00207786
*************************************************************************/
void eeye_test_illegal_alarms(int type)
{
	struct alarm_detect_info info;

	switch (type) {
	case 0:
		info.reason = EARLY_ALARM_MAX + eeye_get_random(100);
		info.alarm_cpu = -1;
		info.detect = eeye_test_detect;
		info.process = NULL;
		info.desc = "ALARM_ILLEGAL_REASON";
		break;
	case 1:
		info.reason = EARLY_ALARM_TEST;
		info.alarm_cpu = -1;
		info.detect = NULL;
		info.process = NULL;
		info.desc = "ALARM_DETECT_NULL";
		break;
	case 2:
		info.reason = EARLY_ALARM_AWDT_NO_KICK;
		info.alarm_cpu = -1;
		info.detect = eeye_watchdog_kick_detect;
		info.process = eeye_watchdog_kick_eprocess;
		info.desc = "ALARM_AWDT_NO_KICK_FOR_TEST";
		break;
	default:
		return;
	}

	(void)eeye_register_alarm_detect_function(&info);
}

/*************************************************************************
Function:		eeye_test_task_sched_func
Description:	task_sched测试功能函数；
Input:		NA
Return:		NA
Author:		j00207786
*************************************************************************/
static int eeye_test_task_sched_func(void *data)
{
	unsigned long flags;
	unsigned long time_wait;

	time_wait = ALARM_DETECT_TIMEOUT / USEC_PER_SEC + 1000;
	spin_lock_irqsave(&g_eeye_test_task_sched_lock, flags);
	mdelay(time_wait);
	spin_unlock_irqrestore(&g_eeye_test_task_sched_lock, flags);
	return 0;
}

/*************************************************************************
Function:		eeye_test_task_sched
Description:	task_sched测试函数；
Input:		NA
Return:		NA
Author:		j00207786
*************************************************************************/
void eeye_test_task_sched(void)
{
	if (!kthread_run(eeye_test_task_sched_func,
			 NULL, "eeye_test_task_sched_func")) {
		pr_err("%s, create thread eeye_test_task_sched_func failed.\n",
		       __func__);
	}
}

/*************************************************************************
Function:	eeye_ap_adapter_init
Description:    预警系统的ap适配的初始化函数，
			包括预警的注册；
Input:		NA；
Return:		0：初始化成功；非0：初始化失败；
Author:			j00207786
*************************************************************************/
static int __init eeye_ap_adapter_init(void)
{
	int i;
	int ret = 0;

	if (!check_himntn(HIMNTN_FTRACE)) {
		pr_err("%s, HIMNTN_EAGLE_EYE is closed!\n", __func__);
		return 0;
	}
#ifdef CONFIG_SCHEDSTATS
	g_ap_alarm_detect_list[EARLY_ALARM_TASK_NO_SCHED_ID].data =
	    kmalloc(sizeof(struct sched_stat_info), GFP_KERNEL);

	if (!g_ap_alarm_detect_list[EARLY_ALARM_TASK_NO_SCHED_ID].data) {
		pr_err
		    ("%s, kmalloc the data of eeye_task_sched_detect failed !\n",
		     __func__);
		return -1;
	}
#endif

	for (i = 0; i < EARLY_ALARM_ID_MAX - 1; i++) {
		ret =
		    eeye_register_alarm_detect_function(&g_ap_alarm_detect_list
							[i]);
		if (ret) {
			pr_err
			    ("%s, eeye_register_alarm_detect_function failed, reason [%d]!\n",
			     __func__, g_ap_alarm_detect_list[i].reason);
			return ret;
		}
	}
	pr_err("%s, success!\n", __func__);
	return ret;
}

static void __exit eeye_ap_adapter_exit(void)
{
#ifdef CONFIG_SCHEDSTATS
	if (g_ap_alarm_detect_list[EARLY_ALARM_TASK_NO_SCHED_ID].data) {
		kfree(g_ap_alarm_detect_list[1].data);
		g_ap_alarm_detect_list[EARLY_ALARM_TASK_NO_SCHED_ID].data =
		    NULL;
	}
#endif
}

module_init(eeye_ap_adapter_init);
module_exit(eeye_ap_adapter_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("j00207786 <j00207786@notesmail.huawei.com>");
