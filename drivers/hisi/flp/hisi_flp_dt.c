/*
 * hisi flp dt driver.
 *
 * Copyright (C) 2015 huawei Ltd.
 * Author: lijiangxiong<lijiangxiong@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/module.h>
#include <linux/of.h>
#include <linux/pm.h>
#include <linux/platform_device.h>

extern int  hisi_flp_register(void);
extern int  hisi_flp_unregister(void);
extern int  hisi_softtimer_init (struct platform_device *pdev);
extern void hisi_softtimer_uninit(void);
extern void flp_port_resume(void);

static int generic_flp_probe(struct platform_device *pdev);
static int generic_flp_remove(struct platform_device *pdev);

unsigned int g_flp_debug_level = 0;
static ssize_t show_debug_level(struct device_driver *d, char *buf)
{
    return snprintf(buf, PAGE_SIZE, "0x%08X\n", g_flp_debug_level);
}

static ssize_t store_debug_level(struct device_driver *d,
        const char *buf, size_t count)
{
    char *p = (char *)buf;
    unsigned int val;

    if (p[1] == 'x' || p[1] == 'X' || p[0] == 'x' || p[0] == 'X') {
        p++;
        if (p[0] == 'x' || p[0] == 'X') {
            p++;
        }
        val = (unsigned int)simple_strtoul(p, &p, 16);
    } else {
        val = (unsigned int)simple_strtoul(p, &p, 10);
    }

    if (p == buf) {
        printk(KERN_INFO ": %s is not in hex or decimal form.\n", buf);
    }

    if ((0 == val) || (1 == val)) {
        g_flp_debug_level = val;
    }
    printk(KERN_INFO "flp:%s debug_level:%d", buf, val);
    return (ssize_t)strnlen(buf, count);
}

/*lint -e846 -e514 -e778 -e866 -e84 */
static DRIVER_ATTR(debug_level, 0660, show_debug_level,
                store_debug_level);
/*lint +e846 +e514 +e778 +e866 +e84 */
static int hisi_flp_pm_suspend(struct device *dev)
{
    dev_info(dev, "%s %d: \n", __func__, __LINE__);

    return 0;
}

static int hisi_flp_pm_resume(struct device *dev)
{
    dev_info(dev, "%s %d: \n", __func__, __LINE__);
    flp_port_resume();
    return 0;
}

struct dev_pm_ops hisi_flp_pm_ops = {
    .suspend = hisi_flp_pm_suspend ,
    .resume  = hisi_flp_pm_resume ,
};

static const struct of_device_id generic_flp[] = {
    { .compatible = "hisilicon,flp-common" },
    {},
};
MODULE_DEVICE_TABLE(of, generic_flp);

static struct platform_driver generic_flp_platdrv = {
    .driver = {
        .name	= "hisi-flp",
        .owner	= THIS_MODULE,
        .of_match_table = of_match_ptr(generic_flp),
        .pm = &hisi_flp_pm_ops,
    },
    .probe		= generic_flp_probe,
    .remove     = generic_flp_remove,
};

static int generic_flp_probe(struct platform_device *pdev)
{
    int ret;
    dev_info(&pdev->dev, "generic_flp_probe \n");
    hisi_softtimer_init(pdev);
    ret = driver_create_file(&generic_flp_platdrv.driver,
                            &driver_attr_debug_level);
    if (ret)
        dev_info(&pdev->dev, "%s %d create file error: \n", __func__, __LINE__);
    return hisi_flp_register();
}

static int generic_flp_remove(struct platform_device *pdev)
{
    dev_info(&pdev->dev, "%s %d: \n", __func__, __LINE__);
    hisi_softtimer_uninit();
    driver_remove_file(&generic_flp_platdrv.driver,
                            &driver_attr_debug_level);
    hisi_flp_unregister();
    return 0;
}

module_platform_driver(generic_flp_platdrv);

MODULE_AUTHOR(" hisi<hisi@huawei.com>");
MODULE_DESCRIPTION("Generic huawei flp driver via DT");
MODULE_LICENSE("GPL");

