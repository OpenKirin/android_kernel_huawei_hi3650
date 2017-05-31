/*
 * deviceboxID.c -- deviceboxID driver
 *
 * Copyright (c) 2014 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/regulator/consumer.h>
#include <linux/string.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/hisi/hisi_adc.h>
#include <linux/pinctrl/consumer.h>
#include <linux/ioctl.h>

#define LOG_TAG "deviceboxID"

#define DEVICEBOX_ID_NAME    "deviceboxID"
#define ADC_READ_COUNT       3
#define DEVICEBOX_ID_LIMIT   500
#define PAGE_SIZE_MAX        1024
#define NAME_LEN_MAX         32
#define VENDOR_DEFAULT       0
#define ELECTRIC_LEVEL_LOW   0
#define ELECTRIC_LEVEL_HIGH  1
#define VENDOR               2
#define BOX_NUM_MAX          4
#define DEVICEBOX_ID_GET_SPEAKER        _IOR('H', 0x01, __u32)
#define DEVICEBOX_ID_GET_RECEIVER       _IOR('H', 0x02, __u32)
#define DEVICEBOX_ID_GET_3rdBOX         _IOR('H', 0x03, __u32)
#define DEVICEBOX_ID_GET_4thBOX         _IOR('H', 0x04, __u32)

#define DEVICEBOX_ID_MODE_OF_GPIO       "gpio"
#define CODEC_GPIO_BASE                 (224)

enum Box_vendor {
    BOX_NAME_DEFAULT = 0,
    BOX_NAME_AAC,
    BOX_NAME_GEER,
    BOX_NAME_GETTOP,
    BOX_NAME_LCHSE,
    BOX_VENDOR_MAX
};

static char *boxtable[BOX_VENDOR_MAX]={"", "AAC", "GK ", "GD ", "LC "};

enum {
	DEVICEBOX_ID_MODE_USE_GPIO          = 0x0,
	DEVICEBOX_ID_MODE_USE_ADC           = 0x1,
};

enum {
	USE_ONE_GPIO            = 1, /*default value*/
	USE_TWO_GPIO            = 2,
};

enum{
	SPEAKER_ID		= 0,
	RECEIVER_ID		= 1,
	BOX_3rd_ID		= 2,
	BOX_4th_ID		= 3,
};

/*define gpio and map name,which is the same as dtsi config*/
static const char * const gpio_name_table[BOX_NUM_MAX] = {
	[SPEAKER_ID]  = "gpio_speakerID",
	[RECEIVER_ID] = "gpio_receiverID",
	[BOX_3rd_ID]  = "gpio_3rdboxID",
	[BOX_4th_ID]  = "gpio_4thboxID",
};

static const char * const box_map_table[BOX_NUM_MAX] = {
	[SPEAKER_ID]  = "speaker_map",
	[RECEIVER_ID] = "receiver_map",
	[BOX_3rd_ID]  = "box3rd_map",
	[BOX_4th_ID]  = "box4th_map",
};

struct box_info_st{
	int box_enable;
	int gpio_num;
	int gpio_id[2];
	int gpio_request_flag[2];
	int gpio_status[2];
	int box_map[VENDOR][VENDOR];
};

static int BoxID_map[VENDOR][VENDOR] = {-1, -1, -1, -1};

struct out_audio_device_id {
	int adc_channel;
	int deviceboxID_limit;
	int check_mode;
	int box_num;
	struct box_info_st box_info[BOX_NUM_MAX];
};

struct out_audio_device_id deviceboxID = {-1};

static int adc_read(void)
{
	int value = VENDOR_DEFAULT;
	int loop = ADC_READ_COUNT;

	while (loop) {
		loop--;
		value = hisi_adc_get_value(deviceboxID.adc_channel);
		pr_info("adc_read adc:%d\n", value);
		if (value < 0) {
			pr_err("%s(%u) : get hkadc error err = %d\n", __func__, __LINE__, value);
			continue;
		}
		break;
	}
	// read err default as ELECTRIC_LEVEL_LOW
	if (value < deviceboxID.deviceboxID_limit)
		return ELECTRIC_LEVEL_LOW;
	else
		return ELECTRIC_LEVEL_HIGH;
}

static int deviceboxID_read(int out_id)
{
	int id = out_id;
	int vendor = VENDOR_DEFAULT;

	if (DEVICEBOX_ID_MODE_USE_GPIO == deviceboxID.check_mode) {
		if (deviceboxID.box_info[id].gpio_num == USE_ONE_GPIO) {
			vendor = deviceboxID.box_info[id].box_map[0][deviceboxID.box_info[id].gpio_status[0]];
		} else if (deviceboxID.box_info[id].gpio_num == USE_TWO_GPIO) {
			vendor = deviceboxID.box_info[id].box_map[deviceboxID.box_info[id].gpio_status[0]][deviceboxID.box_info[id].gpio_status[1]];
		}
	}
#if 0
	else {
		vendor = adc_read();
	}
#endif

	pr_info("deviceboxID_read box_id:%d  vendor:%d\n", id, vendor);
	return vendor;
}

static long deviceboxID_do_ioctl(struct file *file, unsigned int cmd,
				 void __user *p, int compat_mode)
{
	int ret = 0;
	unsigned int value = VENDOR_DEFAULT;
	unsigned int __user *pUser = (unsigned int __user *) p;

	switch (cmd) {
		case DEVICEBOX_ID_GET_SPEAKER:
			if (deviceboxID.box_info[SPEAKER_ID].box_enable) {
				value = deviceboxID_read(SPEAKER_ID);
			}
			ret |= put_user(value, pUser);
			break;
		case DEVICEBOX_ID_GET_RECEIVER:
			if (deviceboxID.box_info[RECEIVER_ID].box_enable) {
				value = deviceboxID_read(RECEIVER_ID);
			}
			ret |= put_user(value, pUser);
			break;
		case DEVICEBOX_ID_GET_3rdBOX:
			if (deviceboxID.box_info[BOX_3rd_ID].box_enable) {
				value = deviceboxID_read(BOX_3rd_ID);
			}
			ret |= put_user(value, pUser);
			break;
		case DEVICEBOX_ID_GET_4thBOX:
			if (deviceboxID.box_info[BOX_4th_ID].box_enable) {
				value = deviceboxID_read(BOX_4th_ID);
			}
			ret |= put_user(value, pUser);
			break;
		default:
			pr_err("unsupport deviceboxID cmd\n");
			ret = -EINVAL;
			break;
	}
	return (long)ret;
}

static long deviceboxID_ioctl(struct file *file, unsigned int command,
						  unsigned long arg)
{
	return deviceboxID_do_ioctl(file, command, (void __user *)arg, 0);
}

#ifdef CONFIG_COMPAT
static long deviceboxID_ioctl_compat(struct file *file, unsigned int command,
							 unsigned long arg)
{
	return deviceboxID_do_ioctl(file, command, compat_ptr(arg), 1);
}
#else
#define deviceboxID_ioctl_compat NULL
#endif

static const struct of_device_id deviceboxID_match[] = {
	{ .compatible = "huawei,deviceboxID", },
	{},
};
MODULE_DEVICE_TABLE(of, deviceboxID_match);

static const struct file_operations deviceboxID_fops = {
	.owner          = THIS_MODULE,
	.unlocked_ioctl = deviceboxID_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = deviceboxID_ioctl,
#endif
};

static struct miscdevice deviceboxID_device = {
	.minor  = MISC_DYNAMIC_MINOR,
	.name   = DEVICEBOX_ID_NAME,
	.fops   = &deviceboxID_fops,
};

char *get_box_name(int map_id)
{
	if((map_id > BOX_NAME_DEFAULT)&&(map_id < BOX_VENDOR_MAX)) {
		return boxtable[map_id];
	}else{
		return "NA ";
	}
}

static ssize_t deviceboxID_info_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	int box_index, gpio_index;
	int map_id = -1;

	if(NULL == buf) {
		return 0;
	}

	snprintf(buf, PAGE_SIZE_MAX, "---deviceboxID info begin---\n");

	snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "GPIO_STATUS:\n");
	for(box_index=0; box_index<deviceboxID.box_num; box_index++) {
		if(1 == deviceboxID.box_info[box_index].box_enable) {
			for (gpio_index = 0; gpio_index < deviceboxID.box_info[box_index].gpio_num; gpio_index++) {
				snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "    box[%d].gpio[%d].status:%d\n",
					box_index, gpio_index, deviceboxID.box_info[box_index].gpio_status[gpio_index]);
			}
		}
	}

	for(box_index=0; box_index<deviceboxID.box_num; box_index++) {
		if(1 == deviceboxID.box_info[box_index].box_enable) {
			snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "Box[%d]_MAP:\n", box_index);
			snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "    -----------------\n");
			snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "    |  %s  |  %s  |\n",
					get_box_name(deviceboxID.box_info[box_index].box_map[0][0]),
					get_box_name(deviceboxID.box_info[box_index].box_map[0][1]));
			snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "    -----------------\n");
			snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "    |  %s  |  %s  |\n",
					get_box_name(deviceboxID.box_info[box_index].box_map[1][0]),
					get_box_name(deviceboxID.box_info[box_index].box_map[1][1]));
			snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "    -----------------\n");
		}
	}

	snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "Box_NAME:\n");
	for(box_index=0; box_index<deviceboxID.box_num; box_index++) {
		if(1 == deviceboxID.box_info[box_index].box_enable) {
			map_id = deviceboxID_read(box_index);
			snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "    box[%d]  :  %s\n", box_index, get_box_name(map_id));
		}
	}

	snprintf(buf+strlen(buf), PAGE_SIZE_MAX-strlen(buf), "---deviceboxID info end---\n");

	return strlen(buf);

}

static DEVICE_ATTR(deviceboxID_info, 0660, deviceboxID_info_show, NULL);

static struct attribute *deviceboxID_attributes[] = {
	&dev_attr_deviceboxID_info.attr,
	NULL,
};

static const struct attribute_group deviceboxID_attr_group = {
	.attrs = deviceboxID_attributes,
};

static int get_check_mode(struct device_node *dev_node)
{
	const char *mode;
	int rc;
	/*get check mode*/
	rc = of_property_read_string(dev_node, "check_mode", &mode);
	if (rc) {
		pr_info("%s: not find dev_node ,rc=%d\n", __func__, rc);
		return DEVICEBOX_ID_MODE_USE_ADC;
	} else {
		pr_info("%s: mode: %s\n", __func__, mode);
	}

	if (!strncmp(mode, DEVICEBOX_ID_MODE_OF_GPIO, sizeof(DEVICEBOX_ID_MODE_OF_GPIO))) {
		return DEVICEBOX_ID_MODE_USE_GPIO;
	} else {
		return DEVICEBOX_ID_MODE_USE_ADC;
	}
}

static int get_box_num(struct device_node *dev_node)
{
	int box_num = -1;
	int rc = 0;

	/*get box number*/
	rc = of_property_read_u32(dev_node, "box_num", &box_num);
	if (rc < 0) {
		pr_info("%s: not find dev_node ,rc=%d\n", __func__, rc);
	} else {
		pr_info("%s: box_num: %d\n", __func__, box_num);
	}

	return box_num;
}


static int get_gpio_status(struct device_node *node, char *propname, int box_index, int gpio_index)
{
	int ret = 0;

	deviceboxID.box_info[box_index].gpio_id[gpio_index]= of_get_named_gpio(node, propname, gpio_index);
	if (deviceboxID.box_info[box_index].gpio_id[gpio_index]  < 0) {
		pr_err("%s: box_info[%d].gpio_id[%d] is unvalid!\n", __func__, box_index, gpio_index);
		return -ENOENT;
	}

	if (!gpio_is_valid(deviceboxID.box_info[box_index].gpio_id[gpio_index])) {
		pr_err("%s:box_info[%d].gpio_id[%d] is unvalid!\n", __func__, box_index, gpio_index);
		return -ENOENT;
	}

	ret = gpio_request(deviceboxID.box_info[box_index].gpio_id[gpio_index], "gpio_id_check");
	if (ret) {
		pr_err("%s:error request, box_info[%d].gpio_id[%d] for gpio_id_check fail %d\n", __func__, box_index, gpio_index, ret);
		return -ENOENT;
	} else {
		deviceboxID.box_info[box_index].gpio_request_flag[gpio_index] = ret;
	}

	/* set gpio to input status */
	gpio_direction_input(deviceboxID.box_info[box_index].gpio_id[gpio_index]);

	deviceboxID.box_info[box_index].gpio_status[gpio_index] = gpio_get_value_cansleep(deviceboxID.box_info[box_index].gpio_id[gpio_index]);

	if (deviceboxID.box_info[box_index].gpio_status[gpio_index] < ELECTRIC_LEVEL_LOW ||
		deviceboxID.box_info[box_index].gpio_status[gpio_index] > ELECTRIC_LEVEL_HIGH ) {
		pr_err("%s:box_info[%d].gpio_status[%d] is invalid\n", __func__, box_index, gpio_index);
		return -ENOENT;

	}
	pr_info("%s:read box_info[%d].gpio_status[%d] is %d\n", __func__, box_index, gpio_index, deviceboxID.box_info[box_index].gpio_status[gpio_index]);

	return 0;
}


static void get_deviceboxID_info(struct device_node *node)
{
	int i;
	int temp;

	deviceboxID.check_mode = get_check_mode(node);
	deviceboxID.box_num = get_box_num(node);

	for(i=0; i<deviceboxID.box_num; i++) {
		if(!of_property_read_u32_index(node, "enable_boxID", i, &temp)) {
			deviceboxID.box_info[i].box_enable = temp;
		} else {
			deviceboxID.box_info[i].box_enable = 0;
		}
	}

	for(i=0; i<deviceboxID.box_num; i++) {
		if(1 == deviceboxID.box_info[i].box_enable) {
			if(!of_property_read_u32_index(node, "gpio_num", i, &temp)) {
				deviceboxID.box_info[i].gpio_num = temp;
			} else {
				deviceboxID.box_info[i].gpio_num = USE_ONE_GPIO;
			}
		}
	}

	return;
}

static int get_deviceboxID_map_priv(struct device_node *node, char *propname, int box_index)
{
	int ret = 0;

	if (deviceboxID.box_info[box_index].gpio_num== USE_ONE_GPIO) {
		if (of_property_read_u32_array(node, propname, deviceboxID.box_info[box_index].box_map,
								sizeof(deviceboxID.box_info[box_index].box_map) / sizeof(int) / 2)) {
			pr_err("of_property_read_u32_array by one gpio box_id_map err,box_index:%d\n",box_index);
			ret = -ENOENT;
		}
	} else if (deviceboxID.box_info[box_index].gpio_num == USE_TWO_GPIO) {
		if (of_property_read_u32_array(node, propname, deviceboxID.box_info[box_index].box_map,
								sizeof(deviceboxID.box_info[box_index].box_map) / sizeof(int))) {
			pr_err("of_property_read_u32_array by two gpio box_id_map err,box_index:%d\n",box_index);
			ret = -ENOENT;
		}
	} else {
		pr_err("gpio_num out of range,box[%d].gpio_num:%d\n", box_index, deviceboxID.box_info[box_index].gpio_num);
		ret = -ENOENT;
	}

	return ret;
}

static int get_deviceboxID_map(struct device_node *node)
{
	int ret = 0;
	int box_index;
	char map_name[NAME_LEN_MAX]={0};

	for(box_index=0; box_index<deviceboxID.box_num; box_index++) {
		if(1 == deviceboxID.box_info[box_index].box_enable) {
			strncpy(map_name, box_map_table[box_index], NAME_LEN_MAX-1);
			ret = get_deviceboxID_map_priv(node, map_name, box_index);
			if(ret) {
				return ret;
			}
			memset(map_name, 0, NAME_LEN_MAX);
		}
	}

	return ret;
}

static int get_deviceboxID_gpio_status(struct device_node *node)
{
	int ret = 0;
	int box_index, gpio_index;
	char gpio_name[NAME_LEN_MAX]={0};

	for(box_index=0; box_index<deviceboxID.box_num; box_index++) {
		strncpy(gpio_name, gpio_name_table[box_index], NAME_LEN_MAX-1);
		if(1 == deviceboxID.box_info[box_index].box_enable) {
			for (gpio_index = 0; gpio_index < deviceboxID.box_info[box_index].gpio_num; gpio_index++) {
				ret = get_gpio_status(node,gpio_name,box_index,gpio_index);
				if(ret != 0) {
					return ret;
				}
			}
		}
		memset(gpio_name, 0, NAME_LEN_MAX);
	}

	return 0;
}

static int deviceboxID_probe(struct platform_device *pdev)
{
	int ret = -ENODEV;
	const struct of_device_id *match;
	struct device_node *node;
	int box_index, gpio_index;
	struct pinctrl *p;
	struct pinctrl_state *pinctrl_def;

	pr_info("deviceboxID_probe++\n");
	match = of_match_device(deviceboxID_match, &pdev->dev);
	if (!match) {
		pr_err("%s:get deviceboxID device info err\n", __func__);
		return -ENOENT;
	}
	node = pdev->dev.of_node;

	/* get deviceboxID info from dts.such as check_mode,gpio_num,box_enable etc */
	get_deviceboxID_info(node);

	/* read boxID map info from dts */
	ret = get_deviceboxID_map(node);
	if(ret){
		pr_err("%s:get boxID_map info err\n", __func__);
		return -ENOENT;
	}

	if (DEVICEBOX_ID_MODE_USE_GPIO == deviceboxID.check_mode) {
		p = devm_pinctrl_get(&pdev->dev);
		if (IS_ERR(p)) {
			pr_err("%s:could not get pinctrl.\n", __func__);
			return -ENOENT;
		}

		pinctrl_def = pinctrl_lookup_state(p, "default");
		if (IS_ERR(pinctrl_def)) {
			pr_err("%s:could not get defstate.\n", __func__);
			return -ENOENT;
		}

		ret = pinctrl_select_state(p, pinctrl_def);
		if (ret) {
			pr_err("%s:could not set pins to default state.\n", __func__);
			return -ENOENT;
		}

		/* create sysfs for debug function */
		if ((sysfs_create_group(&pdev->dev.kobj, &deviceboxID_attr_group)) < 0) {
			pr_err("%s:failed to register sysfs\n", __func__);
			return -ENOENT;
		}

		ret = get_deviceboxID_gpio_status(node);
		if(ret) {
			pr_err("%s:read gpio_status fail.\n", __func__);
			goto err_get_gpio_status;
		}

		/* reset gpio to NP status for saving power */
		pinctrl_def = pinctrl_lookup_state(p, "idle");
		if (IS_ERR(pinctrl_def)) {
			pr_err("%s:could not get idle defstate.\n", __func__);
			goto err_get_gpio_status;
		}

		ret = pinctrl_select_state(p, pinctrl_def);
		if (ret) {
			pr_err("%s:could not set pins to idle state.\n", __func__);
			goto err_get_gpio_status;
		}

		ret = misc_register(&deviceboxID_device);
		if (ret) {
			pr_err("%s: deviceboxID_device register failed", __func__);
			goto err_get_gpio_status;
		}
	}
#if 0
	else {
		/* get channel id */
		if (!of_property_read_u32(node, "channel", &temp)) {
			deviceboxID.adc_channel = temp;
		} else {
			pr_err("get adc channel failed, set default value\n");
			deviceboxID.adc_channel = 5;
		}
		/*get deviceboxID deviceboxID value*/
		if (!of_property_read_u32(node, "deviceboxID_limit", &temp)) {
			deviceboxID.deviceboxID_limit = temp;
			pr_info("get deviceboxID_limit from dts:%d\n", temp);
		} else {
			pr_err("get deviceboxID_limit failed, set default value\n");
			deviceboxID.deviceboxID_limit = DEVICEBOX_ID_LIMIT;
		}
	}
#endif

	pr_info("deviceboxID_probe--\n");
	return 0;

err_get_gpio_status:
	for(box_index=0; box_index<deviceboxID.box_num; box_index++) {
		if(1 == deviceboxID.box_info[box_index].box_enable) {
			for (gpio_index = 0; gpio_index < deviceboxID.box_info[box_index].gpio_num; gpio_index++) {
				if(0 == deviceboxID.box_info[box_index].gpio_request_flag[gpio_index]) {
					gpio_free(deviceboxID.box_info[box_index].gpio_id[gpio_index]);
					deviceboxID.box_info[box_index].gpio_id[gpio_index] = -1;
					deviceboxID.box_info[box_index].gpio_request_flag[gpio_index] = -1;
				}
			}
		}
	}

	sysfs_remove_group(&pdev->dev.kobj, &deviceboxID_attr_group);

	return ret;
}

static int deviceboxID_remove(struct platform_device *pdev)
{
	int box_index, gpio_index;

	if (DEVICEBOX_ID_MODE_USE_GPIO == deviceboxID.check_mode) {
		for(box_index=0; box_index<deviceboxID.box_num; box_index++) {
			if(1 == deviceboxID.box_info[box_index].box_enable){
				for (gpio_index = 0; gpio_index < deviceboxID.box_info[box_index].gpio_num; gpio_index++) {
					if(0 == deviceboxID.box_info[box_index].gpio_request_flag[gpio_index]) {
						gpio_free(deviceboxID.box_info[box_index].gpio_id[gpio_index]);
						deviceboxID.box_info[box_index].gpio_id[gpio_index] = -1;
						deviceboxID.box_info[box_index].gpio_request_flag[gpio_index] = -1;
					}
				}
			}
		}

		sysfs_remove_group(&pdev->dev.kobj, &deviceboxID_attr_group);
		misc_deregister(&deviceboxID_device);
	}

	return 0;
}


static struct platform_driver deviceboxID_driver = {
	.driver = {
		.name  = DEVICEBOX_ID_NAME,
		.owner = THIS_MODULE,
		.of_match_table = of_match_ptr(deviceboxID_match),
	},
	.probe  = deviceboxID_probe,
	.remove = deviceboxID_remove,
};

static int __init deviceboxID_init(void)
{
	return platform_driver_register(&deviceboxID_driver);
}

static void __exit deviceboxID_exit(void)
{
	platform_driver_unregister(&deviceboxID_driver);
}

module_init(deviceboxID_init);
module_exit(deviceboxID_exit);

MODULE_DESCRIPTION("deviceboxID driver");
MODULE_LICENSE("GPL");
