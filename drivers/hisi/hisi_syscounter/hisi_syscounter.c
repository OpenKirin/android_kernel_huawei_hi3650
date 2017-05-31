#include <linux/sysfs.h>
#include <linux/platform_device.h>
#include <linux/pm.h>
#include <linux/of.h>
#include <linux/errno.h>
#include <linux/slab.h>
#include <linux/time64.h>
#include <linux/spinlock.h>
#include <linux/device.h>
#include <linux/io.h>
#include <linux/module.h>
#include <asm/arch_timer.h>
#include <linux/hisi/hisi_syscounter.h>
#include <linux/syscore_ops.h>

static struct syscnt_device *syscnt_dev;

int syscounter_to_timespec64(u64 syscnt, struct timespec64 *ts)
{
	struct syscnt_device *dev = syscnt_dev;
	time64_t sec_delta;
	long nsec_delta;
	u64 cnt_delta;

	if (!dev) return -ENXIO;

	if (syscnt < dev->record.syscnt)
		return -EINVAL;

	cnt_delta = syscnt - dev->record.syscnt;
	sec_delta = (time64_t)(cnt_delta / dev->clock_rate);
	nsec_delta = (long)((cnt_delta % dev->clock_rate) * NSEC_PER_SEC / dev->clock_rate);

	ts->tv_sec = dev->record.ts.tv_sec + sec_delta;
	ts->tv_nsec = dev->record.ts.tv_nsec + nsec_delta;
	if (ts->tv_nsec >= NSEC_PER_SEC) {
		ts->tv_sec++;
		ts->tv_nsec -= NSEC_PER_SEC;
	}

	return 0;
}
EXPORT_SYMBOL(syscounter_to_timespec64);

u64 hisi_get_syscount(void)
{
	struct syscnt_device *dev = syscnt_dev;
	union syscnt_val syscnt;
	unsigned long flags;

	if (!dev || !dev->base)
		return 0;

	spin_lock_irqsave(&dev->r_lock, flags);
	syscnt.val_lh32.l32 = (u32)readl(dev->base + SYSCOUNTER_L32);
	syscnt.val_lh32.h32 = (u32)readl(dev->base + SYSCOUNTER_H32);
	spin_unlock_irqrestore(&dev->r_lock, flags);

	return syscnt.val;
}
EXPORT_SYMBOL(hisi_get_syscount);

int hisi_get_timecounter(unsigned long *lastcycle, struct timespec *ts)
{
    struct syscnt_device *dev = syscnt_dev;

    if (!dev) return -ENXIO;

    *lastcycle = dev->record.syscnt;
    ts->tv_sec = dev->record.utc.tv_sec;
    ts->tv_nsec = dev->record.utc.tv_nsec;
    return 0;
}
EXPORT_SYMBOL(hisi_get_timecounter);


static int hisi_syscounter_suspend(void)
{
	pr_info("%s ++", __func__);

	pr_info("%s --", __func__);

	return 0;
}

static void hisi_syscounter_resume(void)
{
	unsigned long flags;

	pr_info("%s ++", __func__);

	if (!syscnt_dev) {
		pr_err("syscnt device is NULL\n");
		return ;
	}

	spin_lock_irqsave(&syscnt_dev->sync_lock, flags);
	get_monotonic_boottime64(&syscnt_dev->record.ts);
	getnstimeofday(&syscnt_dev->record.utc);
	syscnt_dev->record.syscnt = hisi_get_syscount();
	spin_unlock_irqrestore(&syscnt_dev->sync_lock, flags);

	pr_info("%s --", __func__);

	return ;
}

/* sysfs resume/suspend bits for timekeeping */
static struct syscore_ops hisi_syscounter_syscore_ops = {
	.resume	    = hisi_syscounter_resume,
	.suspend    = hisi_syscounter_suspend,
};

static int hisi_syscounter_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct syscnt_device *d;
	int ret;
	unsigned long flags;

	d = kzalloc(sizeof(struct syscnt_device), GFP_KERNEL);
	if (!d) {
		dev_err(dev, "kzalloc mem error\n");
		return -ENOMEM;
	}
	syscnt_dev = d;

	ret = of_property_read_u64(dev->of_node, "clock-rate", &d->clock_rate);
	if (ret) {
		dev_err(dev, "read clock-rate from dts error\n");
		goto err_probe;
	}

	d->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!d->res) {
		dev_err(dev, "platform_get_resource error\n");
		ret = -ENOMEM;
		goto err_probe;
	}

	d->base = ioremap(d->res->start, resource_size(d->res));
	if (!d->base) {
		dev_err(dev, "ioremap baseaddr error\n");
		ret = -ENOMEM;
		goto err_probe;
	}

	spin_lock_init(&d->r_lock);
	spin_lock_init(&d->sync_lock);

	spin_lock_irqsave(&d->sync_lock, flags);
	get_monotonic_boottime64(&d->record.ts);
	getnstimeofday(&syscnt_dev->record.utc);
	d->record.syscnt = hisi_get_syscount();
	spin_unlock_irqrestore(&d->sync_lock, flags);

	platform_set_drvdata(pdev, d);
	register_syscore_ops(&hisi_syscounter_syscore_ops);


	dev_info(dev, "%s success\n", __func__);

	return 0;

err_probe:
	kfree(d);
	syscnt_dev = NULL;
	return ret;
}

static int hisi_syscounter_remove(struct platform_device *pdev)
{
    unregister_syscore_ops(&hisi_syscounter_syscore_ops);
    if (syscnt_dev) {
        iounmap(syscnt_dev->base);
        kfree(syscnt_dev);
        syscnt_dev = NULL;
    }
    return 0;
}

static struct of_device_id hisi_syscounter_of_match[] = {
	{ .compatible = "hisilicon,syscounter-driver" },
	{ }
};

static struct platform_driver hisi_syscounter_driver = {
	.probe  = hisi_syscounter_probe,
	.remove = hisi_syscounter_remove,
	.driver	= {
		.name =	"hisi-syscounter",
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(hisi_syscounter_of_match),
	},
};

static int __init hisi_syscounter_init(void)
{
	return platform_driver_register(&hisi_syscounter_driver);
}

static void __exit hisi_syscounter_exit(void)
{
	platform_driver_unregister(&hisi_syscounter_driver);
}

module_init(hisi_syscounter_init);
module_exit(hisi_syscounter_exit);

MODULE_AUTHOR("Hisilicon Co. Ltd");
MODULE_DESCRIPTION("Hisi SysCounter Driver");
MODULE_LICENSE("GPL");
