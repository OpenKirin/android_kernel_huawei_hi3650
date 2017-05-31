/*
 * =====================================================================================
 *
 *       Filename:  hwboot_time_out.c
 *
 *    Description:  boot time out interface
 *
 *        Version:  1.0
 *        Created:  07/02/2016 11:16:02 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  xiadzh
 *        Company:  Huawei PDU2
 *
 * =====================================================================================
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/stat.h>
#include <linux/spinlock.h>
#include <linux/notifier.h>
#include <linux/kprobes.h>
#include <linux/reboot.h>
#include <linux/io.h>
#include <linux/vmalloc.h>
#include <linux/mm.h>
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/kernel.h>
#include <asm/uaccess.h>
#include <asm/barrier.h>
#include <linux/platform_device.h>
#include <linux/of_fdt.h>
#include <linux/list.h>
#include <linux/miscdevice.h>
#include <linux/of_address.h>
#include <linux/kallsyms.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/jiffies.h>
#include <linux/kthread.h>
#include <chipset_common/hwbfm/hwboot_fail_public_interface.h>

struct hwboot_time_data {
	unsigned int value;
	struct task_struct *boot_time_task;
	struct timer_list boot_timer;
	struct completion boot_complete;
	bool boot_timer_count_enable;
	bool boot_timer_should_run;
	u32 boot_too_long_time;
	u32 boot_too_long_time_exact;
};
static struct hwboot_time_data *btime_data = NULL;
static struct mutex btimer_lock;

static void boot_time_check(struct hwboot_time_data *btime_dd)
{
	static u32 boot_ttime = 0;
	static u32 boot_ttime_no_varible = 0;

	printk(KERN_WARNING "hwboot_timer:update timer\n");
	boot_ttime += btime_dd->value;
	if(btime_dd->boot_timer_count_enable) {
		printk(KERN_WARNING "hwboot_timer:update timer count\n");
		boot_ttime_no_varible += btime_dd->value;
	}

	if ( (boot_ttime_no_varible >= btime_dd->boot_too_long_time_exact)
		|| (boot_ttime >= btime_dd->boot_too_long_time) )
	{
            printk(KERN_ERR "hwboot_timer: %s timer expired! boot fail!\n",
                (boot_ttime_no_varible >= btime_dd->boot_too_long_time_exact)
                ? ("3 minutes") : ("30 minutes"));
            btime_dd->boot_timer_should_run = false;
            boot_fail_err(KERNEL_BOOT_TIMEOUT, NO_SUGGESTION, NULL);
	}

	return;
}

static void boot_task_wakeup(unsigned long data)
{
	struct hwboot_time_data *btime_dd =
		(struct hwboot_time_data *)data;
	complete(&btime_dd->boot_complete);
}

static __ref int boot_time_kthread(void *arg)
{
	struct hwboot_time_data *btime_dd =
		(struct hwboot_time_data *)arg;
	unsigned long delay_time = 0;
	struct sched_param param = {.sched_priority = MAX_RT_PRIO-1};

	sched_setscheduler(current, SCHED_FIFO, &param);
	while (!kthread_should_stop()) {
		while (wait_for_completion_interruptible(
			&btime_dd->boot_complete) != 0)
			;
		reinit_completion(&btime_dd->boot_complete);

		mutex_lock(&btimer_lock);
		delay_time = msecs_to_jiffies(btime_dd->value);
		if(btime_dd->boot_timer_should_run) {
			boot_time_check(btime_dd);
			mod_timer(&btime_dd->boot_timer, jiffies + delay_time);
		}
		else {
			printk("hwboot_timer:%s will stop",__func__);
			btime_data = NULL;
			del_timer_sync(&btime_dd->boot_timer);
			kfree(btime_dd);
			mutex_unlock(&btimer_lock);
			break;
		}
		mutex_unlock(&btimer_lock);

	}
	return 0;
}

void boot_timer_stop(void)
{
	printk(KERN_ERR "func:%s stop timer\n", __func__);
	mutex_lock(&btimer_lock);
	if(btime_data) {
		btime_data->boot_timer_should_run = false;
	}
	mutex_unlock(&btimer_lock);
	return;
}
EXPORT_SYMBOL(boot_timer_stop);

void boot_timer_set_enable(bool enable)
{
	printk(KERN_ERR "func:%s %s!\n", __func__, enable ? "enable timer" : "disable timer");
	mutex_lock(&btimer_lock);
	if(btime_data) {
		btime_data->boot_timer_count_enable = enable;
	}
	mutex_unlock(&btimer_lock);
	return;
}
EXPORT_SYMBOL(boot_timer_set_enable);

void boot_timer_get_enable(bool *enable)
{
	mutex_lock(&btimer_lock);
	if(btime_data) {
		*enable = btime_data->boot_timer_count_enable;
	}
	mutex_unlock(&btimer_lock);
	return;
}
EXPORT_SYMBOL(boot_timer_get_enable);

void boot_timer_set(u32 bt_value)
{
	printk(KERN_ERR "func:%s bt_value: %d\n", __func__, (int)bt_value);
	mutex_lock(&btimer_lock);
	if(btime_data) {
		btime_data->boot_too_long_time_exact = bt_value;
	}
	mutex_unlock(&btimer_lock);
	return;
}
EXPORT_SYMBOL(boot_timer_set);

void boot_timer_get(u32 *bt_value_ptr)
{
	mutex_lock(&btimer_lock);
	if(btime_data) {
		*bt_value_ptr = btime_data->boot_too_long_time_exact;
	}
	mutex_unlock(&btimer_lock);
	return;
}
EXPORT_SYMBOL(boot_timer_get);

int boot_timer_init(void)
{
	int ret = 0;
	unsigned long delay_time = 0;
	struct hwboot_time_data *btime_dd;
	btime_dd = kzalloc(sizeof(struct hwboot_time_data), GFP_KERNEL);
	if (!btime_dd)
		return -EIO;
	btime_data = btime_dd;
	btime_dd->boot_time_task = kthread_create(boot_time_kthread, btime_dd,
			"hwboot_time");
	if (IS_ERR(btime_dd->boot_time_task)) {
		ret = PTR_ERR(btime_dd->boot_time_task);
		goto err;
	}
	btime_dd->value = BOOT_TIMER_INTERVAL;
	btime_dd->boot_too_long_time = BOOT_TOO_LONG_TIME;
	btime_dd->boot_too_long_time_exact = BOOT_TOO_LONG_TIME_EXACT;
	btime_dd->boot_timer_count_enable = true;
	btime_dd->boot_timer_should_run = true;
	mutex_init(&btimer_lock);

	delay_time = msecs_to_jiffies(btime_dd->value);
	init_completion(&btime_dd->boot_complete);
	wake_up_process(btime_dd->boot_time_task);
	init_timer(&btime_dd->boot_timer);
	btime_dd->boot_timer.data = (unsigned long)btime_dd;
	btime_dd->boot_timer.function = boot_task_wakeup;
	btime_dd->boot_timer.expires = jiffies + delay_time;
	add_timer(&btime_dd->boot_timer);
	return 0;
err:
	kzfree(btime_dd);
	return ret;
}
EXPORT_SYMBOL(boot_timer_init);
