/* Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
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
#include <linux/types.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/pm_runtime.h>
#include <linux/coresight.h>
#include <linux/amba/bus.h>
#include <linux/clk.h>

#include <linux/platform_device.h>

#include "coresight-priv.h"

#define FUNNEL_FUNCTL		0x000
#define FUNNEL_PRICTL		0x004

#define FUNNEL_HOLDTIME_MASK	0xf00
#define FUNNEL_HOLDTIME_SHFT	0x8
#define FUNNEL_HOLDTIME		(0x7 << FUNNEL_HOLDTIME_SHFT)

/**
 * struct funnel_drvdata - specifics associated to a funnel component
 * @base:	memory mapped base address for this component.
 * @dev:	the device entity associated to this component.
 * @atclk:	optional clock for the core parts of the funnel.
 * @csdev:	component vitals needed by the framework.
 * @priority:	port selection order.
 * @spinlock:  only one at a time pls.
 */
struct funnel_drvdata {
	void __iomem *base;
	struct device *dev;
	struct clk *atclk;
	struct coresight_device *csdev;
	unsigned long priority;
	u32 functl;		/* backup funnel for restore */
	spinlock_t spinlock;
};
#define MAX_FUNNEL_DEV  (5)
static int funnel_count;
static struct funnel_drvdata *funneldrvdata[MAX_FUNNEL_DEV] = { 0 };

static void funnel_enable_hw(struct funnel_drvdata *drvdata, int port)
{
	u32 functl;

	CS_UNLOCK(drvdata->base);

	functl = readl_relaxed(drvdata->base + FUNNEL_FUNCTL);
	functl &= ~FUNNEL_HOLDTIME_MASK;
	functl |= FUNNEL_HOLDTIME;
	functl |= (1 << port);
	writel_relaxed(functl, drvdata->base + FUNNEL_FUNCTL);
	writel_relaxed(drvdata->priority, drvdata->base + FUNNEL_PRICTL);
	/* backup functl value for restore */
	drvdata->functl = functl;

	CS_LOCK(drvdata->base);
}

static int funnel_enable(struct coresight_device *csdev, int inport,
			 int outport)
{
	struct funnel_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);
	int ret;

	if (!IS_ERR_OR_NULL(drvdata->atclk)) {
		ret = clk_prepare_enable(drvdata->atclk);
		if (ret) {
			dev_err(drvdata->dev, "enable atclk fail \n");
			return ret;
		}
	}

	pm_runtime_get_sync(drvdata->dev);
	funnel_enable_hw(drvdata, inport);

	dev_info(drvdata->dev, "FUNNEL inport %d enabled\n", inport);
	return 0;
}

static void funnel_disable_hw(struct funnel_drvdata *drvdata, int inport)
{
	u32 functl;

	CS_UNLOCK(drvdata->base);

	functl = readl_relaxed(drvdata->base + FUNNEL_FUNCTL);
	functl &= ~(1 << inport);
	writel_relaxed(functl, drvdata->base + FUNNEL_FUNCTL);
	/* backup functl value for restore */
	drvdata->functl = functl;

	CS_LOCK(drvdata->base);
}

static void funnel_disable(struct coresight_device *csdev, int inport,
			   int outport)
{
	struct funnel_drvdata *drvdata = dev_get_drvdata(csdev->dev.parent);

	funnel_disable_hw(drvdata, inport);
	pm_runtime_put(drvdata->dev);

	if (!IS_ERR_OR_NULL(drvdata->atclk)) {
		clk_disable_unprepare(drvdata->atclk);
	}
	dev_info(drvdata->dev, "FUNNEL inport %d disabled\n", inport);
}

static const struct coresight_ops_link funnel_link_ops = {
	.enable = funnel_enable,
	.disable = funnel_disable,
};

static const struct coresight_ops funnel_cs_ops = {
	.link_ops = &funnel_link_ops,
};

static ssize_t priority_show(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct funnel_drvdata *drvdata = dev_get_drvdata(dev->parent);
	unsigned long val = drvdata->priority;

	return snprintf(buf, sizeof(val), "%#lx\n", val);
}

static ssize_t priority_store(struct device *dev,
			      struct device_attribute *attr,
			      const char *buf, size_t size)
{
	int ret;
	unsigned long val;
	struct funnel_drvdata *drvdata = dev_get_drvdata(dev->parent);

	ret = kstrtoul(buf, 16, &val);
	if (ret)
		return ret;

	drvdata->priority = val;
	return size;
}

static DEVICE_ATTR_RW(priority);

static u32 get_funnel_ctrl_hw(struct funnel_drvdata *drvdata)
{
	u32 functl;

	CS_UNLOCK(drvdata->base);
	functl = readl_relaxed(drvdata->base + FUNNEL_FUNCTL);
	CS_LOCK(drvdata->base);

	return functl;
}

static ssize_t funnel_ctrl_show(struct device *dev,
				struct device_attribute *attr, char *buf)
{
	u32 val;
	struct funnel_drvdata *drvdata = dev_get_drvdata(dev->parent);

	pm_runtime_get_sync(drvdata->dev);

	val = get_funnel_ctrl_hw(drvdata);

	pm_runtime_put(drvdata->dev);

	return snprintf(buf, sizeof(val), "%#x\n", val);
}

static DEVICE_ATTR_RO(funnel_ctrl);

static struct attribute *coresight_funnel_attrs[] = {
	&dev_attr_funnel_ctrl.attr,
	&dev_attr_priority.attr,
	NULL,
};

ATTRIBUTE_GROUPS(coresight_funnel);

static int funnel_probe(struct amba_device *adev, const struct amba_id *id)
{
	int ret;
	void __iomem *base;
	struct device *dev = &adev->dev;
	struct coresight_platform_data *pdata = NULL;
	struct funnel_drvdata *drvdata;
	struct resource *res = &adev->res;
	struct coresight_desc *desc;
	struct device_node *np = adev->dev.of_node;

	if (!coresight_access_enabled()) {
		dev_err(dev,
			"coresight trace is sec debug mode ,coresight trace disable\n");
		return -EACCES;
	}

	if (np) {
		pdata = of_get_coresight_platform_data(dev, np);
		if (IS_ERR(pdata))
			return PTR_ERR(pdata);
		adev->dev.platform_data = pdata;
	}
	if (!pdata)
		return -ENOMEM;

	drvdata = devm_kzalloc(dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	drvdata->dev = &adev->dev;
	drvdata->atclk = devm_clk_get(&adev->dev, TOPCS_ATCLK_NAME);	/* optional */
	if (!IS_ERR_OR_NULL(drvdata->atclk)) {
		dev_info(dev, "get atclk OK\n");
		ret = clk_prepare_enable(drvdata->atclk);
		if (ret) {
			goto err_next;
		}
	} else {
		dev_err(dev, "get atclk fail \n");
	}

	dev_set_drvdata(dev, drvdata);

	/* Validity for the resource is already checked by the AMBA core */
	base = devm_ioremap_resource(dev, res);
	if (IS_ERR(base))
		return PTR_ERR(base);

	drvdata->base = base;
	pm_runtime_put(&adev->dev);

	desc = devm_kzalloc(dev, sizeof(*desc), GFP_KERNEL);
	if (!desc) {
		ret = -ENOMEM;
		goto err_next;
	}

	desc->type = CORESIGHT_DEV_TYPE_LINK;
	desc->subtype.link_subtype = CORESIGHT_DEV_SUBTYPE_LINK_MERG;
	desc->ops = &funnel_cs_ops;
	desc->pdata = pdata;
	desc->dev = dev;
	desc->groups = coresight_funnel_groups;
	drvdata->csdev = coresight_register(desc);
	if (IS_ERR(drvdata->csdev)) {
		dev_err(dev, "drvdata->csdev = 0x%lx", PTR_ERR(drvdata->csdev));
		ret = EFAULT;
		goto err_coresight_register;
	}

	spin_lock_init(&drvdata->spinlock);
	if (funnel_count >= MAX_FUNNEL_DEV) {
		dev_err(dev, "ERROR: Too much funnel device \n");
	} else {
		funneldrvdata[funnel_count++] = drvdata;
	}
	dev_info(dev, "FUNNEL initialized\n");
	return 0;
err_coresight_register:
	devm_kfree(dev, desc);
	if (!IS_ERR_OR_NULL(drvdata->atclk)) {
		clk_disable_unprepare(drvdata->atclk);
	}
err_next:
	devm_kfree(dev, drvdata);
	return ret;
}

static int funnel_remove(struct amba_device *adev)
{
	struct funnel_drvdata *drvdata = amba_get_drvdata(adev);

	coresight_unregister(drvdata->csdev);
	return 0;
}

#ifdef CONFIG_PM
int funnel_runtime_suspend(struct device *dev)
{
	struct funnel_drvdata *drvdata = dev_get_drvdata(dev);

	if (drvdata && !IS_ERR_OR_NULL(drvdata->atclk))
		clk_disable_unprepare(drvdata->atclk);

	return 0;
}

int funnel_runtime_resume(struct device *dev)
{
	struct funnel_drvdata *drvdata = dev_get_drvdata(dev);
	int ret;

	if (drvdata && !IS_ERR_OR_NULL(drvdata->atclk)) {
		ret = clk_prepare_enable(drvdata->atclk);
		if (ret) {
			info_print("[%s] clk enable failed\n", __func__);
		}
	}
	return 0;
}
#endif

static const struct dev_pm_ops funnel_dev_pm_ops = {
	SET_RUNTIME_PM_OPS(funnel_runtime_suspend, funnel_runtime_resume, NULL)
};

static struct amba_id funnel_ids[] = {
	{
	 .id = 0x0003b908,
	 .mask = 0x0003ffff,
	 },
	{0, 0},
};

static struct amba_driver funnel_driver = {
	.drv = {
		.name = "coresight-funnel",
		.owner = THIS_MODULE,
		.pm = &funnel_dev_pm_ops,
		},
	.probe = funnel_probe,
	.remove = funnel_remove,
	.id_table = funnel_ids,
};

module_amba_driver(funnel_driver);

/* get tmc drive data by device node's phandle */
void *get_funnel_drvdata_bydevnode(struct device_node *np)
{
	int i;
	struct funnel_drvdata *drvdata;

	for (i = 0; i < funnel_count; i++) {
		drvdata = funneldrvdata[i];
		if (!drvdata) {
			break;
		}
		if (np == drvdata->dev->of_node)
			return (void *)drvdata;
	}

	return NULL;
}

int funnel_restore(void *drv)
{
	struct funnel_drvdata *drvdata;
	drvdata = (struct funnel_drvdata *)drv;

	if (!drvdata) {
		printk("[%s]:NULL pointer \n", __func__);
		return -1;
	}
	spin_lock(&drvdata->spinlock);
	CS_UNLOCK(drvdata->base);
	writel_relaxed(drvdata->functl, drvdata->base + FUNNEL_FUNCTL);
	writel_relaxed(drvdata->priority, drvdata->base + FUNNEL_PRICTL);
	CS_LOCK(drvdata->base);
	spin_unlock(&drvdata->spinlock);
	return 0;
}

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("CoreSight Funnel driver");
