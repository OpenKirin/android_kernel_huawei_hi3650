/*
 * watchdog for preventing the charging work dead
 *
 * Copyright (c) 2013 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/version.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/mod_devicetable.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/kern_levels.h>
#include <huawei_platform/log/hw_log.h>
#include "soc_rtctimerwdtv100_interface.h"
#include <hisi_charging_watchdog.h>
#define HWLOG_TAG hisi_chg_watchdog
HWLOG_REGIST();

static struct hisi_chgwdg_device *g_di;

static inline void __chg_wdt_lock(void __iomem *base, unsigned int lock_key)
{
	__raw_writel(lock_key, CHG_WATHDOG_WDLOCK_ADDR((char *)base));
}

static inline void __chg_wdt_unlock(void __iomem *base, unsigned int value)
{
	__raw_writel(value, CHG_WATHDOG_WDLOCK_ADDR((char *)base));
}

static inline unsigned int __chg_wdt_unlock_check(void __iomem *base)
{
	return __raw_readl(CHG_WATHDOG_WDLOCK_ADDR((char *)base));
}

static inline void __chg_wdt_load(void __iomem *base, unsigned int timeout)
{
	__raw_writel(WATCHDOG_CLOCK_COUNT*timeout, CHG_WATHDOG_WDLOAD_ADDR((char *)base));
}

static inline unsigned int __chg_wdt_get_cnt(void __iomem *base)
{
	return __raw_readl(CHG_WATHDOG_WDVALUE_ADDR((char *)base));
}

static inline void __chg_wdt_intclr(void __iomem *base, unsigned int value)
{
	__raw_writel(value, CHG_WATHDOG_WDINTCLR_ADDR((char *)base));
}

static inline void __chg_wdt_control(void __iomem *base, unsigned int value)
{
	__raw_writel(value, CHG_WATHDOG_WDCTRL_ADDR((char *)base));
}
/*******************************************************************************
Function:       charge_feed_sys_wdt
Description:    set timeout for charge watchdog
Input:          timeout:watchdog timeout
Output:         NA
Return:         NA
********************************************************************************/
void charge_feed_sys_wdt(unsigned int timeout)
{
	unsigned int cnt;

	if (NULL == g_di || NULL == g_di->base) {
		hwlog_err("%s:NULL POINTER\n", __func__);
		return;
	}
	__chg_wdt_unlock(g_di->base, UNLOCK);
	if (0 != __chg_wdt_unlock_check(g_di->base)) {
		hwlog_err("wdt unlock fail\n");
	}
	cnt = __chg_wdt_get_cnt(g_di->base);
	__chg_wdt_load(g_di->base, timeout);
	__chg_wdt_lock(g_di->base, LOCK);
	hwlog_info("++charge watchdog feed, current cnt:%d, timeout is:%d++\n",cnt/WATCHDOG_CLOCK_COUNT, CHG_WATCHDOG_TIME);
}
EXPORT_SYMBOL(charge_feed_sys_wdt);
/*******************************************************************************
Function:       charge_enable_sys_wdt
Description:    enable charge watchdog
Input:          NA
Output:         NA
Return:         NA
********************************************************************************/
void charge_enable_sys_wdt(void)
{
	if (NULL == g_di || NULL == g_di->base) {
		hwlog_err("%s:NULL POINTER\n", __func__);
		return;
	}
	__chg_wdt_unlock(g_di->base, UNLOCK);
	if (0 != __chg_wdt_unlock_check(g_di->base)) {
		hwlog_err("wdt unlock fail\n");
	}
	__chg_wdt_load(g_di->base, CHG_WATCHDOG_TIME);
	__chg_wdt_intclr(g_di->base, 0x0);
	__chg_wdt_control(g_di->base, CHG_WATCHDOG_EN);
	__chg_wdt_lock(g_di->base, LOCK);
	hwlog_info("++charge watchdog start++\n");
}
EXPORT_SYMBOL(charge_enable_sys_wdt);
/*******************************************************************************
Function:       chargr_stop_sys_wdt
Description:    disable charge watchdog
Input:          NA
Output:         NA
Return:         NA
********************************************************************************/
void charge_stop_sys_wdt(void)
{
	if (NULL == g_di || NULL == g_di->base) {
		hwlog_err("%s:NULL POINTER\n", __func__);
		return;
	}
	__chg_wdt_unlock(g_di->base, UNLOCK);
	if (0 != __chg_wdt_unlock_check(g_di->base)) {
		hwlog_err("wdt unlock fail\n");
	}
	__chg_wdt_control(g_di->base, CHG_WATCHDOG_DIS);
	__chg_wdt_lock(g_di->base, LOCK);
	hwlog_info("++charge watchdog stop++\n");
}
EXPORT_SYMBOL(charge_stop_sys_wdt);

static int hisi_chg_wdg_probe(struct platform_device *pdev)
{
	struct device_node *node = pdev->dev.of_node;
	int ret = 0;

	g_di = kmalloc(sizeof(*g_di), GFP_KERNEL);
	if (!g_di) {
		hwlog_err("no mem for chg watchdog resouce\n");
		ret = -ENOMEM;
		goto out;
	}

	g_di->base = of_iomap(node, 0);
	if (!g_di->base) {
		hwlog_err("iomap error\n");
		ret = -ENOMEM;
		goto free_dev;
	}

	g_di->irq = irq_of_parse_and_map(node, 0);
	disable_irq_nosync((unsigned int)g_di->irq);
	charge_stop_sys_wdt();

	platform_set_drvdata(pdev, g_di);
	hwlog_info("Hisi charge watchdog ready\n");
	return 0;

free_dev:
	kfree(g_di);
out:
	return ret;
}

static int hisi_chg_wdg_remove(struct platform_device *pdev)
{
	struct hisi_chgwdg_device *di = platform_get_drvdata(pdev);

	platform_set_drvdata(pdev, NULL);
	if (di) {
		iounmap(di->base);
		free_irq(di->irq, pdev);
		kfree(di);
	}
	return 0;
}

static const struct of_device_id hisi_chgwdg_of_match[] = {
	{
	.compatible = "hisilicon,chgwdg",
	.data = NULL
	},
	{},
};

MODULE_DEVICE_TABLE(of, hisi_chgwdg_of_match);

static struct platform_driver hisi_chgwdg_driver = {
	.probe = hisi_chg_wdg_probe,
	.remove = hisi_chg_wdg_remove,
	.driver = {
			   .name = "Chg-watchdog",
			   .owner = THIS_MODULE,
			   .of_match_table = of_match_ptr(hisi_chgwdg_of_match),
		},
};

static int __init hisi_chgwdg_init(void)
{
	platform_driver_register(&hisi_chgwdg_driver);
	return 0;
}

module_init(hisi_chgwdg_init);

static void __exit hisi_chgwdg_exit(void)
{
	platform_driver_unregister(&hisi_chgwdg_driver);
}

module_exit(hisi_chgwdg_exit);

MODULE_DESCRIPTION("CHG watchdog driver");
MODULE_LICENSE("GPL V2");
