/*
 * Histarisp rpmsg client driver
 *
 * Copyright (c) 2013- Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/*lint -e666 -esym(666,*)*/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/cdev.h>
#include <linux/jiffies.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/skbuff.h>
#include <linux/sched.h>
#include <linux/rpmsg.h>
#include <linux/completion.h>
#include <uapi/linux/histarisp.h>

#include <linux/ion.h>
#include <linux/hisi/hisi_ion.h>

static int debug_mask = 0x3;
module_param_named(debug_mask, debug_mask, int, S_IRUGO | S_IWUSR);
#define rpmsg_err(fmt, args...) \
    do {                         \
        if (debug_mask & 0x01)   \
            printk(KERN_INFO "Rpmsg HISI Err: [%s] " fmt, __func__, ##args); \
    } while (0)
#define rpmsg_info(fmt, args...)  \
    do {                         \
        if (debug_mask & 0x02)   \
            printk(KERN_INFO "Rpmsg HISI Info: [%s] " fmt, __func__, ##args);  \
    } while (0)
#define rpmsg_dbg(fmt, args...)  \
    do {                         \
        if (debug_mask & 0x04) \
            printk(KERN_INFO "Rpmsg HISI Debug: [%s] " fmt, __func__, ##args); \
    } while (0)

enum isp_rpmsg_state {
    RPMSG_UNCONNECTED,
    RPMSG_CONNECTED,
};

struct rpmsg_hisi_service {
    struct cdev *cdev;
    struct device *dev;
    struct rpmsg_channel *rpdev;
    struct list_head list;
    struct mutex lock;
};

struct rpmsg_hisi_instance {
    struct list_head node;
    struct rpmsg_hisi_service *hisi_serv;
    struct rpmsg_endpoint *ept;
    struct sk_buff_head queue;
    struct mutex lock;
    wait_queue_head_t readq;
	struct ion_client *client;
    void *rpmsg_msg;
    u32 dst;
    int state;
};

struct cdev_info {
    struct class *rpmsg_hisi_class;
    dev_t rpmsg_hisi_dev;
    struct cdev isp_cdev;
    struct device *isp_dev;
    int minor;
    int enable_rpmsg;
};

static struct cdev_info  cdev_local;
static struct rpmsg_hisi_service *hisi_isp_serv;
static atomic_t instances;

int rpmsg_client_debug = INVALID_CLIENT;
EXPORT_SYMBOL(rpmsg_client_debug);

static const struct file_operations rpmsg_hisi_fops = {
    .owner          = THIS_MODULE,
};

static int rpmsg_hisi_probe(struct rpmsg_channel *rpdev)
{
    struct rpmsg_hisi_service *hisi_serv = NULL;

    hisi_serv = kzalloc(sizeof(*hisi_serv), GFP_KERNEL);
    if (!hisi_serv) {
        rpmsg_err("kzalloc failed\n");
        return -ENOMEM;
    }

    INIT_LIST_HEAD(&hisi_serv->list);
    mutex_init(&hisi_serv->lock);

    hisi_serv->cdev = &cdev_local.isp_cdev;
    hisi_serv->dev = cdev_local.isp_dev;
    hisi_isp_serv = hisi_serv;

    hisi_serv->rpdev = rpdev;

    dev_set_drvdata(&rpdev->dev, hisi_serv);

    rpmsg_info("new HISI connection srv channel: %u -> %u!\n",
                        rpdev->src, rpdev->dst);

    rpmsg_dbg("Exit ...\n");
    return 0;
}

static void rpmsg_hisi_remove(struct rpmsg_channel *rpdev)
{
    struct rpmsg_hisi_service *hisi_serv = dev_get_drvdata(&rpdev->dev);

    /* check list */
    
    mutex_lock(&hisi_serv->lock);
    if (list_empty(&hisi_serv->list)) {
        mutex_unlock(&hisi_serv->lock);
        kfree(hisi_serv);
        hisi_serv = NULL;

        rpmsg_info("hisi_serv->list is empty, instances = %d.\n", atomic_read(&instances));
    } else {
        mutex_unlock(&hisi_serv->lock);
        /* Maybe here need to debug, in case more exception case */
        rpmsg_err("rpmsg remove exception, instances = %d \n", atomic_read(&instances));
        WARN_ON(1);
    }

    rpmsg_info("Exit ...\n");
    return;
}

static void rpmsg_hisi_driver_cb(struct rpmsg_channel *rpdev, void *data,
                        int len, void *priv, u32 src)
{
    rpmsg_dbg("Enter ...\n");
    dev_warn(&rpdev->dev, "uhm, unexpected message\n");

    print_hex_dump(KERN_DEBUG, __func__, DUMP_PREFIX_NONE, 16, 1,
               data, len,  true);
    rpmsg_dbg("Exit ...\n");
}

static struct rpmsg_device_id rpmsg_hisi_id_table[] = {
    { .name    = "rpmsg-isp-debug" },
    { },
};
MODULE_DEVICE_TABLE(platform, rpmsg_hisi_id_table);

static struct rpmsg_driver rpmsg_hisi_driver = {
    .drv.name   = KBUILD_MODNAME,
    .drv.owner  = THIS_MODULE,
    .id_table   = rpmsg_hisi_id_table,
    .probe      = rpmsg_hisi_probe,
    .callback   = rpmsg_hisi_driver_cb,
    .remove     = rpmsg_hisi_remove,
};

static int __init rpmsg_hisi_init(void)
{
    int ret, major;

    rpmsg_dbg("Enter ...\n");
    
    cdev_local.minor = 0;
    atomic_set(&instances, 0);

    ret = alloc_chrdev_region(&cdev_local.rpmsg_hisi_dev, 0, 1,
                            KBUILD_MODNAME);
    if (ret) {
        pr_err("alloc_chrdev_region failed: %d\n", ret);
        goto out;
    }

    cdev_local.rpmsg_hisi_class = class_create(THIS_MODULE, KBUILD_MODNAME);
    if (IS_ERR(cdev_local.rpmsg_hisi_class)) {
        ret = PTR_ERR(cdev_local.rpmsg_hisi_class);
        pr_err("class_create failed: %d\n", ret);
        goto unreg_region;
    }

    major = MAJOR(cdev_local.rpmsg_hisi_dev);
    rpmsg_dbg("cdev_local.rpmsg_hisi_dev major.%u \n", (unsigned int)major);

    cdev_init(&cdev_local.isp_cdev, &rpmsg_hisi_fops);
    rpmsg_dbg("hisi_serv->cdev.%p\n", &cdev_local.isp_cdev);
    
    cdev_local.isp_cdev.owner = THIS_MODULE;
    ret = cdev_add(&cdev_local.isp_cdev, MKDEV(major, cdev_local.minor), 1);
    if (ret) {
        rpmsg_err("cdev_add failed: %d\n", ret);
        goto destroy_class;
    }

    cdev_local.isp_dev = device_create(cdev_local.rpmsg_hisi_class, NULL,
                                    MKDEV(major, cdev_local.minor), NULL,
                                    "rpmsg-hisi%d", cdev_local.minor);
    if (IS_ERR(cdev_local.isp_dev)) {
        ret = PTR_ERR(cdev_local.isp_dev);
        rpmsg_dbg("device_create failed: %d\n", ret);
        goto clean_cdev;
    }

	cdev_local.enable_rpmsg = 0;

    return register_rpmsg_driver(&rpmsg_hisi_driver);

clean_cdev:
    cdev_del(&cdev_local.isp_cdev);
destroy_class:
    class_destroy(cdev_local.rpmsg_hisi_class);
unreg_region:
    unregister_chrdev_region(cdev_local.rpmsg_hisi_dev, 1);
out:
    rpmsg_dbg("Exit ...\n");
    return ret;
}
module_init(rpmsg_hisi_init);

static void __exit rpmsg_hisi_exit(void)
{
    int major = MAJOR(cdev_local.rpmsg_hisi_dev);

    rpmsg_dbg("Enter ...\n");
    unregister_rpmsg_driver(&rpmsg_hisi_driver);
    device_destroy(cdev_local.rpmsg_hisi_class, MKDEV(major, cdev_local.minor));
    cdev_del(&cdev_local.isp_cdev);
    class_destroy(cdev_local.rpmsg_hisi_class);
    unregister_chrdev_region(cdev_local.rpmsg_hisi_dev, 1);
    rpmsg_dbg("Exit ...\n");
}
module_exit(rpmsg_hisi_exit);

MODULE_DESCRIPTION("HISI offloading rpmsg driver");
MODULE_LICENSE("GPL v2");
