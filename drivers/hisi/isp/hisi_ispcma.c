/*
 * hisilicon efuse driver, hisi_ispcma.c
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/mm.h>
#include <linux/dma-mapping.h>
#include <linux/printk.h>
#include <linux/remoteproc.h>
#include <linux/hisi/hisi_drmdriver.h>
#include <linux/platform_data/remoteproc-hisi.h>
#include <linux/of_reserved_mem.h>

#define ISP_CMA_START           (0x1AC00000)
#define ISP_CMA_MEM_SIZE        (0x2400000)
#define DTS_COMP_ISPCMA_NAME    "hisilicon,isp-cma"

extern void create_mapping_late(phys_addr_t phys, unsigned long virt,
                                phys_addr_t size, pgprot_t prot);

struct hisi_ispcma_struct {
    struct device *device;
    void *cma_va;
    dma_addr_t cma_dma;
};

struct hisi_ispcma_struct ispcma_dev;

int hisi_atfisp_cma_alloc(void)
{
    struct hisi_ispcma_struct *dev = (struct hisi_ispcma_struct *)&ispcma_dev;
    dma_addr_t dma;
    void *va;

    pr_info("%s: +\n", __func__);
    if (!dev->device) {
        pr_err("%s: failed.\n", __func__);
        return -EINVAL;
    }

    va = dma_alloc_coherent(dev->device, ISP_CMA_MEM_SIZE, &dma, GFP_KERNEL);
    if (!va) {
        pr_err("%s: alloc failed.\n", __func__);
        return -ENOMEM;
    }
    pr_info("%s: va.0x%p, dma.0x%llx.\n", __func__, va, dma);

    pr_info("%s: phys_to_virt(dma).0x%lx\n", __func__, (unsigned long)phys_to_virt(dma));
    create_mapping_late((phys_addr_t)dma, (unsigned long)phys_to_virt(dma),
            ISP_CMA_MEM_SIZE, __pgprot(PROT_NORMAL_NC));

    atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID,
                        ISP_CMA_START, ISP_CMA_MEM_SIZE, ACCESS_REGISTER_FN_SUB_ID_DDR_ISP_SEC_OPEN);

    dev->cma_va = va;
    dev->cma_dma = dma;

    pr_info("%s: -\n", __func__);
    return 0;
}

void hisi_atfisp_cma_free(void)
{
    struct hisi_ispcma_struct *dev = (struct hisi_ispcma_struct *)&ispcma_dev;

    pr_info("%s: +\n", __func__);

    atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID,
                        ISP_CMA_START, ISP_CMA_MEM_SIZE, ACCESS_REGISTER_FN_SUB_ID_DDR_ISP_SEC_CLOSE);
    pr_info("%s: atfer ISP_SEC_CLOSE.\n", __func__);

    if (dev->cma_va == NULL || dev->cma_dma == 0) {
        pr_info("%s: cma_va.0x%p, cma_dma.0x%llx\n", __func__, dev->cma_va, dev->cma_dma);
        return;
    }

    create_mapping_late((phys_addr_t)dev->cma_dma, (unsigned long)phys_to_virt(dev->cma_dma),
            ISP_CMA_MEM_SIZE, __pgprot(PROT_NORMAL));

    dma_free_coherent(dev->device, ISP_CMA_MEM_SIZE, dev->cma_va, dev->cma_dma);

    dev->cma_va = NULL;
    dev->cma_dma = 0;
    pr_info("%s: -\n", __func__);
}

int hisi_ispcma_probe(struct platform_device *pdev)
{
    struct hisi_ispcma_struct *dev = (struct hisi_ispcma_struct *)&ispcma_dev;
    int ret;

    pr_info("%s: +\n", __func__);

    dev->device = &(pdev->dev);

    ret = of_reserved_mem_device_init(dev->device);
    if (0 != ret) {
        pr_err("%s: init failed, ret.%d\n", __func__, ret);
        goto out;
    }

    dev->cma_va = NULL;
    dev->cma_dma = 0;
    pr_info("%s: -\n", __func__);
    return 0;

out:
    dev->device = NULL;

    pr_err("%s: error-\n", __func__);
    return ret;
}

int hisi_ispcma_remove(struct platform_device *pdev)
{
    struct hisi_ispcma_struct *dev = (struct hisi_ispcma_struct *)&ispcma_dev;

    if (!dev->device) {
        pr_err("%s: failed.\n", __func__);
        return -EINVAL;
    }

    of_reserved_mem_device_release(dev->device);

    return 0;
}

static struct of_device_id hisi_ispcma_of_match[] = {
    { .compatible = DTS_COMP_ISPCMA_NAME},
    { },
};
MODULE_DEVICE_TABLE(of, hisi_ispcma_of_match);

static struct platform_driver hisi_ispcma_driver = {
    .driver = {
        .owner      = THIS_MODULE,
        .name       = "ispcma",
        .of_match_table = of_match_ptr(hisi_ispcma_of_match),
    },
    .probe  = hisi_ispcma_probe,
    .remove = hisi_ispcma_remove,
};

static int __init hisi_ispcma_init(void)
{
    pr_info("%s: +\n", __func__);
    return platform_driver_register(&hisi_ispcma_driver);
}
subsys_initcall(hisi_ispcma_init);

static void __exit hisi_ispcma_exit(void)
{
    platform_driver_unregister(&hisi_ispcma_driver);
}
module_exit(hisi_ispcma_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Hisilicon ispcma module");
