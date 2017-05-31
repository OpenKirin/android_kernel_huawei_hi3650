/* Copyright (c) 2013-2014, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/clk.h>
#include <linux/topology.h>
#include <linux/of.h>
#include <linux/coresight.h>
#include "coresight-priv.h"
#include "coresight-tsgen.h"

static struct tsgen_drvdata *tsgendrvdata;

/*Enable timestamp generator
return 0: success, -1: error
*/

int coresight_tsgen_enable(void)
{
	struct tsgen_drvdata *drvdata;
	int ret;
	u32 tsgenctl;

	drvdata = tsgendrvdata;
	if (!drvdata) {
		printk(KERN_ERR "coresight_tsgen_enable: no tsgen driver\n");
		return -1;
	}

	spin_lock(&drvdata->spinlock);
	if (drvdata->refcnt) {
		/* timestamp is already on, just +1  */
		drvdata->refcnt++;
		dev_info(drvdata->dev,
			"coresight_tsgen_enable: refcont: %d \n", drvdata->refcnt);
		spin_unlock(&drvdata->spinlock);
		return 0;
	}

	if (!IS_ERR_OR_NULL(drvdata->clk)) {
		ret = clk_prepare_enable(drvdata->clk);
		if (ret) {
			spin_unlock(&drvdata->spinlock);
			return -1;
		}
	}

	tsgenctl = readl_relaxed(drvdata->base + TS_CNTCR);
	tsgenctl &= ~(1 << TE_ENABLE_BIT);
	tsgenctl |= 1 << TE_ENABLE_BIT;
	writel_relaxed(tsgenctl, drvdata->base + TS_CNTCR);
	drvdata->refcnt++;
	dev_info(drvdata->dev,
		"coresight_tsgen_enable : refcont: %d \n", drvdata->refcnt);
	spin_unlock(&drvdata->spinlock);
	return 0;
}

/*Disable timestamp generator   */
int coresight_tsgen_disable(void)
{
	struct tsgen_drvdata *drvdata;
	u32 tsgenctl;

	drvdata = tsgendrvdata;
	if (!drvdata) {
		printk(KERN_ERR  "coresight_tsgen_disable: no tsgen driver\n");
		return -1;
	}

	spin_lock(&drvdata->spinlock);
	if (!drvdata->refcnt) {
		goto out;
	}

	drvdata->refcnt--;
	if (drvdata->refcnt) {
	/* timestamp is still used */
		goto out;
	}

	if (!IS_ERR_OR_NULL(drvdata->clk)) {
		clk_disable_unprepare(drvdata->clk);
	}

	tsgenctl = readl_relaxed(drvdata->base + TS_CNTCR);
	tsgenctl &= ~(1 << TE_ENABLE_BIT);
	writel_relaxed(tsgenctl, drvdata->base + TS_CNTCR);

out:
	dev_info(drvdata->dev, "coresight_tsgen_disable: refcont: %d \n", drvdata->refcnt);
	spin_unlock(&drvdata->spinlock);
	return 0;
}

static int tsgen_probe(struct platform_device *pdev)
{
	int ret;
	struct device *dev = &pdev->dev;
	struct coresight_platform_data *pdata = NULL;
	struct tsgen_drvdata *drvdata;
	struct resource *res;

	if (!coresight_access_enabled()) {
		dev_err(dev,
			"coresight trace is sec debug mode ,coresight trace disable\n");
		return -EACCES;
	}

	dev_err(dev, "tsgen probe enter\n");

	if (pdev->dev.of_node) {
		pdata = of_get_coresight_platform_data(dev, pdev->dev.of_node);
		if (IS_ERR_OR_NULL(pdata)) {
			dev_err(dev, "tsgen get platform data err\n");
			return PTR_ERR(pdata);
		}
		pdev->dev.platform_data = pdata;
	}

	drvdata = devm_kzalloc(dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;
	/* Store the driver data pointer for use in exported functions */
	drvdata->dev = &pdev->dev;
	platform_set_drvdata(pdev, drvdata);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		err_print("tsgen: get resource fail\n");
		ret = -ENODEV;
		goto err;
	}

	drvdata->base = devm_ioremap(dev, res->start, resource_size(res));
	if (!drvdata->base) {
		err_print("tsgen: ioremap faill\n");
		ret = -ENOMEM;
		goto err;
	}

	drvdata->clk = devm_clk_get(dev, "clk_timestamp");	/* optional */
	if (!IS_ERR_OR_NULL(drvdata->clk)) {
		dev_info(dev, "get clk OK\n");
	       ret = of_property_read_u32(pdev->dev.of_node, "clock-frequency", &drvdata->freq);
		if (ret) {
			err_print("get tsgen freq error\n");
			ret = -ENODEV;
			goto err;
		}
	} else {
		dev_info(dev, "get clk fail \n");
	}
	spin_lock_init(&drvdata->spinlock);
	drvdata->refcnt = 0;
	tsgendrvdata = drvdata;
	dev_err(dev, "tsgen  initialized\n");
	return 0;
err:
	return ret;
}

static int tsgen_remove(struct platform_device *pdev)
{
	coresight_tsgen_disable();
	return 0;
}

static struct of_device_id tsgen_match[] = {
	{.compatible = "arm,coresight-tsgen"},
	{}
};

static struct platform_driver tsgen_driver = {
	.probe = tsgen_probe,
	.remove = tsgen_remove,
	.driver = {
		   .name = "coresight-stgen",
		   .owner = THIS_MODULE,
		   .of_match_table = tsgen_match,
		   },
};

static int __init tsgen_init(void)
{
	return platform_driver_register(&tsgen_driver);
}

module_init(tsgen_init);

static void __exit tsgen_exit(void)
{
	platform_driver_unregister(&tsgen_driver);
}

module_exit(tsgen_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("CoreSight TSGEN driver");
