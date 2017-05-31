/*
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */
#include <linux/timekeeper_internal.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/percpu.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/sched.h>
#include <linux/syscore_ops.h>
#include <linux/clocksource.h>
#include <linux/jiffies.h>
#include <linux/time.h>
#include <linux/tick.h>
#include <linux/stop_machine.h>
#include <linux/pvclock_gtod.h>
#include <linux/compiler.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/of_platform.h>

/*frequency of sp804timer: 32K = 32764.5, so (val*10)/327645*/
#define SP804FREQ            327645
#define SP804SCALE           10
/*offset of registers for free-running and one-shot timer*/
/*lint -e750 */
#define LOADOFF_FREERUN      0x00
#define VALOFF_FREERUN       0x04
#define CTRLOFFSET_FREERUN   0x08
#define LOADOFFSET_ONESHOT   0x20
#define VALUEOFFSET_ONESHOT  0x24
#define CTRLOFFSET_ONESHOT   0x28
#define CLRIRQOFFSET_ONESHOT 0x2C

/* control settings for opening and closing timers*/
#define SP_OPEN_FREERUN      0x82
#define SP_CLOSE_FREERUN     0x02
#define SP_OPEN_ONESHOT      0xA3
#define SP_CLOSE_ONESHOT     0x03

/* value of load register from free-running timer,
 * which can be used for 36 hours */
#define LOAD_FREERUN         0xFFFFFFFF

/* value of load register from one-shot timer,
 * which can be used for 35 hours */
#define LOAD_ONESHOT         0xF6180000

/*reset*/
#define CLRIRQ               0x00

struct hisi_timekeeper {
	void __iomem *base;
	int in_suspend;
};

static struct hisi_timekeeper *mono_timekeeper;

/**
 * read_persistent_clock -  Return time from the persistent clock.
 *
 * Weak dummy function for arches that do not yet support it.
 * Reads the time from the battery backed persistent clock.
 * Returns a timespec with tv_sec=0 and tv_nsec=0 if unsupported.
 *
 *  XXX - Do be sure to remove it once all arches implement it.
 */
void read_persistent_clock(struct timespec *ts)
{
/* current value of freerun timer */
	long val_curr;
/* original value of freerun timer */
	long val_ori;
	long value;

	if ((mono_timekeeper == NULL) || (mono_timekeeper->in_suspend == 0)) {
		ts->tv_sec = 0;
		ts->tv_nsec = 0;
	} else {
		val_curr = (long)readl(mono_timekeeper->base + VALOFF_FREERUN);
		val_ori = (long)readl(mono_timekeeper->base + LOADOFF_FREERUN);
		value = val_ori - val_curr;
		value = value * SP804SCALE;
		ts->tv_sec = value / SP804FREQ;
		ts->tv_nsec = (value % SP804FREQ) * 1000000000 / SP804FREQ;
	}
}

static irqreturn_t hisi_timekeeper_interrupt(int irq, void *dev_id)
{
	writel(CLRIRQ, mono_timekeeper->base + CLRIRQOFFSET_ONESHOT);
	return IRQ_HANDLED;
}/*lint !e715*/

static int __init hisi_timekeeper_probe(struct platform_device *pdev)
{
	struct hisi_timekeeper *timekeeper;
	struct resource *res;
	int ret, irq;

	if (mono_timekeeper) {
		dev_err(&pdev->dev, "mono timekeeper existed !\n");
		return -EEXIST;
	}

	timekeeper = kzalloc(sizeof(struct hisi_timekeeper), GFP_KERNEL);
	if (!timekeeper) {
		dev_err(&pdev->dev, "fail to alloc !\n");
		return -ENOMEM;
	}

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	timekeeper->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(timekeeper->base)) {
		ret = -ENOMEM;
		dev_err(&pdev->dev, "fail to ioremap !\n");
		goto err;
	}

	irq = platform_get_irq(pdev, 0);
	if (irq < 0) {
		ret = -ENXIO;
		dev_err(&pdev->dev, "fail to get irq !\n");
		goto err;
	}

	ret = devm_request_irq(&pdev->dev, (unsigned int)irq,
			hisi_timekeeper_interrupt, (unsigned long) 0,
			"hisi_timekeeper", pdev);
	if (ret < 0) {
		dev_err(&pdev->dev, "fail to request irq !\n");
		goto err;
	}

	mono_timekeeper = timekeeper;
	return 0;
err:
	kfree(timekeeper);
	return ret;
}

static int hisi_timekeeper_suspend(struct platform_device *pdev,
	pm_message_t state)
{
	writel(LOAD_FREERUN, mono_timekeeper->base + LOADOFF_FREERUN);
	writel(LOAD_ONESHOT, mono_timekeeper->base + LOADOFFSET_ONESHOT);
	writel(SP_OPEN_FREERUN, mono_timekeeper->base + CTRLOFFSET_FREERUN);
	writel(SP_OPEN_ONESHOT, mono_timekeeper->base + CTRLOFFSET_ONESHOT);
	mono_timekeeper->in_suspend = 1;
	return 0;
}/*lint !e715*/

static int hisi_timekeeper_resume(struct platform_device *pdev)
{
	mono_timekeeper->in_suspend = 0;
	writel(SP_CLOSE_FREERUN, mono_timekeeper->base + CTRLOFFSET_FREERUN);
	writel(SP_CLOSE_ONESHOT, mono_timekeeper->base + CTRLOFFSET_ONESHOT);
	return 0;
}/*lint !e715*/

static const struct of_device_id hisi_timekeeper_of_match[] = {
	{.compatible = "hisilicon,hisi-timekeeper" },/*lint !e785*/
	{ }/*lint !e785*/
};

MODULE_DEVICE_TABLE(of, hisi_timekeeper_of_match);

static struct platform_driver hisi_timekeeper_driver = {
	.probe = hisi_timekeeper_probe,
	.suspend = hisi_timekeeper_suspend,
	.resume = hisi_timekeeper_resume,
	.driver = {
		.name  = "hisi-timekeeper",
		.of_match_table = of_match_ptr(hisi_timekeeper_of_match),
	},/*lint !e785*/
};/*lint !e785*/

static int __init hisi_timekeeper_init(void)
{
	int ret = 0;

	ret = platform_driver_register(&hisi_timekeeper_driver);/*lint !e64 !e838*/
	if (ret)
		pr_err("register hisi timekeeper driver failed.\n");

	return ret;
}

static void __exit hisi_timekeeper_exit(void)
{
	platform_driver_unregister(&hisi_timekeeper_driver);
}

/*lint -e528 -esym(528,__initcall_hisi_timekeeper_init6,__exitcall_hisi_timekeeper_exit)*/
module_init(hisi_timekeeper_init);
module_exit(hisi_timekeeper_exit);
/*lint -e528 +esym(528,__initcall_hisi_timekeeper_init6,__exitcall_hisi_timekeeper_exit)*/

/*lint -e753 -esym(753,*)*/
MODULE_DESCRIPTION("Hisilicon Timekeeper Driver");
MODULE_LICENSE("GPL V2");
/*lint -e753 +esym(753,*)*/

