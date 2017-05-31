/*
 * BDAT drvier.
 *
 * Copyright (C) 2016 Huawei Device Co.,Ltd.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <linux/init.h>
#ifdef CONFIG_COMPAT
#include <linux/compat.h>
#endif
#include <linux/fb.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/suspend.h>

#include <huawei_platform/log/hwlog_kernel.h>
#include <huawei_platform/power/bdat/bdat_common.h>

#define BDAT_MAGIC 'k'
#define BDAT_IOCTL_WAKELOCK_ENABLE _IOW(BDAT_MAGIC, 1, bool)
#define BDAT_IOCTL_WAKELOCK_GET _IOR(BDAT_MAGIC, 2, struct dev_transmit_t)
#define BDAT_IOCTL_PID_CPUTIME_LENGTH _IOR(BDAT_MAGIC, 3, int)
#define BDAT_IOCTL_PID_CPUTIME_GET _IOWR(BDAT_MAGIC, 4, struct dev_transmit_t)
#define BDAT_IOCTL_GPU_ENABLE _IOW(BDAT_MAGIC, 5, bool)
#define BDAT_IOCTL_GPU_INFO_GET _IOR(BDAT_MAGIC, 6, struct dev_transmit_t)

#define IRQ_NAME_SIZE 128

static char irq_name[IRQ_NAME_SIZE];
static int irq_gpio;
static bool resume;

/*
 * Function name: bdat_ioctl
 * Description: main method to exchange data with user space
 * Input: struct file *flip, file pointer
 *        unsigned int cmd, command
 *        unsigned long arg, arguments
 * Output: none
 * Return: 0, success
 *         other value, failed
 * Date: 2016/02/26
 * Author: Pengyu  ID: 00188486
 */
static long bdat_ioctl(struct file *flip, unsigned int cmd, unsigned long arg)
{
	int rc = -EFAULT;
	void __user *argp = (void __user *)arg;

	switch (cmd) {
	case BDAT_IOCTL_WAKELOCK_ENABLE: {
		bool enable;

		if (copy_from_user(&enable, argp, sizeof(bool))) {
			BDAT_LOGE("Failed to set wakelock enable\n");
			rc = -EFAULT;
			break;
		}
		rc = bdat_set_wakelock_enable(enable);
		break;
	}
	case BDAT_IOCTL_WAKELOCK_GET: {
		rc = bdat_get_wakelock(arg);
		break;
	}
	case BDAT_IOCTL_PID_CPUTIME_LENGTH: {
		int length;

		rc = 0;
		length = bdat_update_pid_cputime();
		if (copy_to_user(argp, &length, sizeof(int))) {
			rc = -EFAULT;
			break;
		}
		break;
	}
	case BDAT_IOCTL_PID_CPUTIME_GET: {
		int len, size;
		struct dev_transmit_t *stat = NULL;

		rc = 0;
		if (copy_from_user(&len, argp, sizeof(int))) {
			rc = -EFAULT;
			break;
		}

		if (len > 0) {
			size = sizeof(struct dev_transmit_t)
				+ len * sizeof(struct pid_cputime);
			stat = kzalloc(size, GFP_KERNEL);
			if (stat == NULL) {
				BDAT_LOGE("Failed to alloc cputime buffer\n");
				rc = -ENOMEM;
				break;
			}
			stat->length = len;
			bdat_get_pid_cputime(stat->length, stat->data);
			if (copy_to_user(argp, stat, size))
				rc = -EFAULT;
		}
		if (stat != NULL)
			kfree(stat);

		break;
	}
	case BDAT_IOCTL_GPU_ENABLE: {
		bool enable;

		if (copy_from_user(&enable, argp, sizeof(bool))) {
			BDAT_LOGE("Failed to set wakelock enable\n");
			rc = -EFAULT;
			break;
		}
		rc = bdat_set_gpu_enable(enable);
		break;
	}
	case BDAT_IOCTL_GPU_INFO_GET: {
		rc = bdat_get_gpu_info(arg);
		break;
	}
	default:
		break;
	}

	return rc;
}

/*
 * Function name: bdat_compat_ioctl
 * Description: exchange data with user space
 *              support of 32bit userspace on 64bit platforms
 * Input: struct inode *inode, inode
 *        unsigned int cmd, command
 *        unsigned long arg, arguments
 * Output: none
 * Return: 0, success
 *         other value, failed
 * Date: 2016/02/26
 * Author: Pengyu  ID: 00188486
 */
#ifdef CONFIG_COMPAT
static long bdat_compat_ioctl(struct file *flip,
			unsigned int cmd, unsigned long arg)
{
	return bdat_ioctl(flip, cmd, (unsigned long) compat_ptr(arg));
}
#endif

/*
 * Function name: bdat_open
 * Description: device open
 * Input: struct inode *inode, inode
 *        struct file *filp, file pointer
 * Output: none
 * Return: 0
 * Date: 2016/02/26
 * Author: Pengyu  ID: 00188486
 */
static int bdat_open(struct inode *inode, struct file *filp)
{
	return 0;
}

/*
 * Function name: bdat_release
 * Description: device release
 * Input: struct inode *inode, inode
 *        struct file *filp, file pointer
 * Output: none
 * Return: 0
 * Date: 2016/02/26
 * Author: Pengyu  ID: 00188486
 */
static int bdat_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static const struct file_operations bdat_device_fops = {
	.owner = THIS_MODULE,
	.unlocked_ioctl = bdat_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl	= bdat_compat_ioctl,
#endif
	.open = bdat_open,
	.release = bdat_release,
};

static struct miscdevice bdat_device = {
	.name = "bdat",
	.fops = &bdat_device_fops,
};

/*
 * Function name: bdat_update_wakeup_info
 * Description: update wakeup info
 * Input: const char *name, wakeup irq name
 *        int gpio, irq gpio
 * Output: none
 * Return: none
 * Date: 2016/08/03
 * Author: Songzili  ID: 00349876
 */
void bdat_update_wakeup_info(const char *name, int gpio)
{
	if (name == NULL) {
		BDAT_LOGE("Invalid parameter");
		return;
	}

	strncpy(irq_name, name, IRQ_NAME_SIZE - 1);
	irq_gpio = gpio;
	resume = true;
}

/*
 * Function name: bdat_pm_notify
 * Description: bdat pm notifier
 * Input: struct notifier_block *nb, notifier block
 *        unsigned long mode, suspend events
 *        void *data, unused data
 * Output: none
 * Return: 0, success
 *         other, failed
 * Date: 2016/08/03
 * Author: Songzili  ID: 00349876
 */
static int bdat_pm_notify(struct notifier_block *nb,
			unsigned long mode, void *data)
{
	switch (mode) {
	case PM_SUSPEND_PREPARE:
		HWBDAT_LOGE("BDAT_TAG_KERNEL_SUSPEND", "");
		break;
	case PM_POST_SUSPEND:
		if (resume) {
			HWBDAT_LOGE("BDAT_TAG_KERNEL_WAKEUP",
				"irq=%s gpio=%d", irq_name, irq_gpio);
			resume = false;
		}
		HWBDAT_LOGE("BDAT_TAG_KERNEL_RESUME", "");
		break;
	default:
		break;
	}

	return 0;
}

static struct notifier_block bdat_pm_nb = {
	.notifier_call = bdat_pm_notify,
};

/*
 * Function name: bdat_dev_init
 * Description: bdat device initialize
 * Input: none
 * Output: none
 * Return: 0, success
 *         other, failed
 * Date: 2016/02/26
 * Author: Pengyu  ID: 00188486
 */
static int bdat_dev_init(void)
{
	int ret;

	bdat_device.minor = MISC_DYNAMIC_MINOR;
	ret = misc_register(&bdat_device);
	if (ret) {
		BDAT_LOGE("Failed to register misc device\n");
		return -ENOENT;
	}

	return ret;
}

/*
 * Function name: bdat_init
 * Description: bdat driver initialize
 * Input: none
 * Output: none
 * Return: 0, success
 *         other value, failed
 * Date: 2016/02/26
 * Author: Pengyu  ID: 00188486
 */
static int __init bdat_init(void)
{
	int ret = 0;

	ret = bdat_gpu_init();
	if (ret < 0)
		goto out;
	ret = bdat_wakelock_init();
	if (ret < 0)
		goto out;

	ret = bdat_pid_cputime_init();
	if (ret < 0)
		goto out;

	bdat_dev_init();

	resume = false;
	register_pm_notifier(&bdat_pm_nb);

	BDAT_LOGD("BDAT module initialize success");
out:
	return ret;
}

/*
 * Function name: bdat_exit
 * Description: bdat driver exit
 * Input: none
 * Output: none
 * Return: none
 * Date: 2016/02/26
 * Author: Pengyu  ID: 00188486
 */
static void __exit bdat_exit(void)
{
	bdat_gpu_exit();
	bdat_wakelock_exit();
	bdat_pid_cputime_exit();
	unregister_pm_notifier(&bdat_pm_nb);
}

late_initcall(bdat_init);
module_exit(bdat_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Yu Peng, <pengyu7@huawei.com>");
MODULE_DESCRIPTION("Huawei Big Data Analysis Tools Driver");
