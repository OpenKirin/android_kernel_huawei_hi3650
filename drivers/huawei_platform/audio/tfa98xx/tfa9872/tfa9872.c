/*
* tfa9872-mono.c -- ALSA SoC Mono TFA9872 driver
*
* Copyright 2013-2014 Maxim Integrated Products
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 as
* published by the Free Software Foundation.
*/
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <linux/module.h>
#include <linux/regmap.h>
#include <linux/slab.h>
#include <linux/miscdevice.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/irqreturn.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <dsm/dsm_pub.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/list.h>
#include "huawei_platform/audio/tfa98xx.h"
#include "huawei_platform/audio/tfa9872.h"
/*lint -e715 -e785 -e826 -e846 -e838 -e84 -e514 -e516*/
/*lint -e778 -e866 -e30 -e701 -e528 -e750 -e753 -e64*/
#define SUPPORT_DEVICE_TREE
#ifdef SUPPORT_DEVICE_TREE
#include <linux/regulator/consumer.h>
#endif
#define HWLOG_TAG tfa9872
HWLOG_REGIST();
#define SPK_REC_DUAL_SMARTPA    2
static unsigned int tfa98xx_num = 0;
struct tfa98xx_gain_def tfa9872_type_gain_def[] = {
	{0x0a, 0x0a},//spk gain value
	{0x0a, 0x0a},//rcv gain value
};
static struct reg_default tfa9872_reg[] = {
	{ 0x00, 0x1801 },
	{ 0x01, 0x0014 },
};
static ssize_t tfa9872_register_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	unsigned int value, i;
	char valStr[20];
	struct tfa98xx_priv *p = NULL;
	p = find_tfa98xx_by_dev(dev);
	if (NULL == p) {
		return 0;
	}
	buf[0] = '\0';
	for (i = 0; i <= 0xff; i++) {
		regmap_read(p->regmap, i, &value);
		sprintf(valStr, "0x%02x = 0x%04x\n", i, value);
		strcat(buf, valStr);
	}
	return (ssize_t)strlen(buf);
}
static DEVICE_ATTR(register_list, S_IRUGO | S_IWUSR, tfa9872_register_show, NULL);
static ssize_t tfa9872_register_write(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	unsigned int reg = 0;
	unsigned int val = 0;
	char *pEnd = (char *)buf;
	struct tfa98xx_priv *p = NULL;
	p = find_tfa98xx_by_dev(dev);
	if (NULL == p) {
		return 0;
	}
	reg = (unsigned int)simple_strtol(buf, &pEnd, 16);
	pEnd++;
	hwlog_info("tfa9872_register_write reg : 0x%x\n", reg);
	val = (unsigned int)simple_strtol(pEnd, &pEnd, 16);
	hwlog_info("tfa9872_register_write val : 0x%x\n", val);
	regmap_write(p->regmap, reg, val);
	return (ssize_t)count;
}
static DEVICE_ATTR(register_write, 0660, NULL, tfa9872_register_write);
static ssize_t tfa9872_num_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct tfa98xx_priv *p = NULL;
	p = find_tfa98xx_by_dev(dev);
	if (NULL == p) {
		return 0;
	}
	return (ssize_t)snprintf(buf, (unsigned long)32, "%d-%d\n", tfa98xx_num, p->type);
}
static DEVICE_ATTR(tfa98xx_num, S_IRUGO | S_IWUSR, tfa9872_num_show, NULL);
static struct attribute *tfa9872_attributes[] = {
	&dev_attr_register_list.attr,
	&dev_attr_register_write.attr,
	&dev_attr_tfa98xx_num.attr,
	NULL
};
static const struct attribute_group tfa9872_attr_group = {
	.attrs = tfa9872_attributes,
};
static int tfa9872_get_version(struct list_head *tfa98xx, unsigned int type, unsigned int *value)
{
	//to do: return version with 0
	*value = 0;
	return 0;
}
static int tfa9872_get_reg_val(struct list_head *tfa98xx, unsigned int type, struct tfa98xx_reg_ops *reg_val, unsigned int __user *pUser)
{
	int ret = 0;
	struct tfa98xx_priv *p = NULL;

	p = find_tfa98xx_by_type(tfa98xx, type);
	if (NULL == p) {
		hwlog_err("%s: it has no type[%d] in tfa9872 device\n", __func__, type);
		return -ENODEV;
	}

	if (copy_from_user(reg_val, (void *)pUser, sizeof(struct tfa98xx_reg_ops))) {
		hwlog_err("%s: set reg copy_from_user fail", __func__);
		return -1;
	}
	ret = regmap_read(p->regmap, reg_val->reg_addr, &reg_val->reg_val);
	if (copy_to_user((void *)pUser, reg_val, sizeof(struct tfa98xx_reg_ops))) {
		hwlog_err("%s: send reg value to user fail", __func__);
		return -1;
	}

	return ret;
}
static int tfa9872_set_reg_val(struct list_head *tfa98xx, struct tfa98xx_reg_ops *reg_val, unsigned int __user *pUser)
{
	int ret = 0;
	struct list_head *pos = NULL;
	struct tfa98xx_priv *p = NULL;
	if (copy_from_user(reg_val, (void *)pUser, sizeof(struct tfa98xx_reg_ops))) {
		hwlog_err("%s: set reg copy_from_user fail\n", __func__);
		return -1;
	}
	list_for_each(pos, tfa98xx) {
		p = list_entry(pos, struct tfa98xx_priv, list);
		ret |= regmap_write(p->regmap, reg_val->reg_addr, reg_val->reg_val);
	}
	hwlog_info("%s:  tfa98xx smartpa set reg val: addr = 0x%x, val = 0x%x\n", __func__, reg_val->reg_addr, reg_val->reg_val);
	return ret;
}
static void tfa9872_reset(struct tfa98xx_priv *p)
{
	gpio_set_value((unsigned int)p->gpio_reset, 1);
	msleep(TFA9872_HOLD_TIME);
	gpio_set_value((unsigned int)p->gpio_reset, 0);
	msleep(TFA9872_RESET_TIME);
	return;
}
static void tfa9872_set_gain(struct tfa98xx_priv *p, unsigned int volume)
{
	if(NULL == p){
		return;
	}

	if(volume > TFA9872_MAX_VOLUME){
		volume = TFA9872_MAX_VOLUME;
	} else if (volume < TFA9872_MIN_VOLUME){
		volume = TFA9872_MIN_VOLUME;
	} else {
		//nothing to do.
	}

	volume = TFA9872_MAX_VOLUME - volume;

	regmap_update_bits(p->regmap, TFA9872_GAIN_ATT,
			TFA9872_GAIN_ATT_MASK_TDMDCG,
			volume << TFA9872_GAIN_ATT_OFFSET_TDMDCG);
	regmap_update_bits(p->regmap, TFA9872_GAIN_ATT,
			TFA9872_GAIN_ATT_MASK_TDMSPKG,
			volume << TFA9872_GAIN_ATT_OFFSET_TDMSPKG);
}
static int tfa9872_digital_mute(struct list_head *tfa98xx, int mute)
{
	struct list_head *pos = NULL;
	struct tfa98xx_priv *p = NULL;
	if (MUTE_OFF == mute) {
		hwlog_info("%s: tfa98xx smartpa mute.\n", __func__);
		list_for_each(pos, tfa98xx) {
			p = list_entry(pos, struct tfa98xx_priv, list);
			mutex_lock(&p->lock);
			regmap_update_bits(p->regmap, TFA9872_SYS_CONTROL0,
					TFA9872_SYS_CTRL0_MASK_DCA | TFA9872_SYS_CTRL0_MASK_AMPE | TFA9872_SYS_CTRL0_MASK_PWDN,
					TFA9872_SYS_CTRL0_MASK_PWDN);
			regmap_update_bits(p->regmap, TFA9872_TDM_CONFIG2,
					TFA9872_TDM_CONFIG2_MASK_TDMTXUS0, 0x2<<TFA9872_TDM_CONFIG2_OFFSET_TDMTXUS0);
			regmap_update_bits(p->regmap, TFA9872_SYS_CONTROL1,
					TFA9872_SYS_CTRL1_MASK_MANAOOSC | TFA9872_SYS_CTRL1_MASK_MANSCONF, 0);
			mutex_unlock(&p->lock);
		}
	} else {
		hwlog_info("%s: tfa98xx smartpa unmute.\n, ", __func__);
		list_for_each(pos, tfa98xx) {
			p = list_entry(pos, struct tfa98xx_priv, list);
			mutex_lock(&p->lock);
			tfa9872_set_gain(p, p->gain);
			regmap_update_bits(p->regmap, TFA9872_TDM_CONFIG2,
					TFA9872_TDM_CONFIG2_MASK_TDMTXUS0, 0x2<<TFA9872_TDM_CONFIG2_OFFSET_TDMTXUS0);
			regmap_update_bits(p->regmap, TFA9872_SYS_CONTROL0,
					TFA9872_SYS_CTRL0_MASK_DCA | TFA9872_SYS_CTRL0_MASK_AMPE | TFA9872_SYS_CTRL0_MASK_PWDN,
					TFA9872_SYS_CTRL0_MASK_DCA | TFA9872_SYS_CTRL0_MASK_AMPE);
			regmap_update_bits(p->regmap, TFA9872_SYS_CONTROL1,
					TFA9872_SYS_CTRL1_MASK_MANAOOSC | TFA9872_SYS_CTRL1_MASK_MANSCONF,
					TFA9872_SYS_CTRL1_MASK_MANAOOSC | TFA9872_SYS_CTRL1_MASK_MANSCONF);
			mutex_unlock(&p->lock);
		}
	}
	return 0;
}
//tfa9872_spk_digital_mute || tfa9872_rec_digital_mute
//spk is set gain == gain_incall in dts
static int tfa9872_single_digital_mute(struct list_head *tfa98xx, unsigned int type, int mute)
{
	struct tfa98xx_priv *p = NULL;
	//int val = 0;
	p = find_tfa98xx_by_type(tfa98xx, type);
	if (NULL == p) {
		hwlog_err("%s: hardware donot sopport smartpa\n", __func__);
		return -ENODEV;
	}
	mutex_lock(&p->lock);
	if (MUTE_OFF == mute) {
		hwlog_info("%s: tfa98xx smartpa mute\n", __func__);
		regmap_update_bits(p->regmap, TFA9872_SYS_CONTROL0,
				TFA9872_SYS_CTRL0_MASK_DCA | TFA9872_SYS_CTRL0_MASK_AMPE | TFA9872_SYS_CTRL0_MASK_PWDN,
				TFA9872_SYS_CTRL0_MASK_PWDN);
		regmap_update_bits(p->regmap, TFA9872_TDM_CONFIG2,
				TFA9872_TDM_CONFIG2_MASK_TDMTXUS0, 0x2<<TFA9872_TDM_CONFIG2_OFFSET_TDMTXUS0);
		regmap_update_bits(p->regmap, TFA9872_SYS_CONTROL1,
				TFA9872_SYS_CTRL1_MASK_MANAOOSC | TFA9872_SYS_CTRL1_MASK_MANSCONF, 0);
	} else {
		hwlog_info("%s: tfa98xx smartpa unmute\n", __func__);
		tfa9872_set_gain(p, p->gain_incall);
		regmap_update_bits(p->regmap, TFA9872_TDM_CONFIG2,
				TFA9872_TDM_CONFIG2_MASK_TDMTXUS0, 0x0<<TFA9872_TDM_CONFIG2_OFFSET_TDMTXUS0);
		if(TFA98XX_R == p->type){
			regmap_update_bits(p->regmap, TFA9872_SYS_CONTROL0,
					TFA9872_SYS_CTRL0_MASK_DCA | TFA9872_SYS_CTRL0_MASK_AMPE | TFA9872_SYS_CTRL0_MASK_PWDN,
					TFA9872_SYS_CTRL0_MASK_AMPE);
		} else {
			regmap_update_bits(p->regmap, TFA9872_SYS_CONTROL0,
					TFA9872_SYS_CTRL0_MASK_DCA | TFA9872_SYS_CTRL0_MASK_AMPE | TFA9872_SYS_CTRL0_MASK_PWDN,
					TFA9872_SYS_CTRL0_MASK_DCA | TFA9872_SYS_CTRL0_MASK_AMPE);
		}
		regmap_update_bits(p->regmap, TFA9872_SYS_CONTROL1,
				TFA9872_SYS_CTRL1_MASK_MANAOOSC | TFA9872_SYS_CTRL1_MASK_MANSCONF,
				TFA9872_SYS_CTRL1_MASK_MANAOOSC | TFA9872_SYS_CTRL1_MASK_MANSCONF);
	}
	mutex_unlock(&p->lock);
	return 0;
}
static int tfa9872_open(struct inode *inode, struct file *filp)
{
	int ret = 0;
	//int reg = 0;
	unsigned int value = 0;
	struct list_head *pos = NULL;
	struct tfa98xx_priv *p = NULL;
	struct list_head *tfa98xx = get_tfa98xx_list_head();
	tfa98xx_num = (unsigned int)get_tfa98xx_num();
	list_for_each(pos, tfa98xx) {
		p = list_entry(pos, struct tfa98xx_priv, list);

		regmap_read(p->regmap, TFA9872_VERSION_REG, &value); //version register
		switch(value){
			case TFA9872_VERSION_N1A:
				hwlog_info("%s: VERSION is N1A\n", __func__);
				regmap_write(p->regmap, 0x0F, 0x5A6B);
				regmap_read(p->regmap, 0xFB, &value);
				value = value ^ 0x005A;
				regmap_write(p->regmap, 0xA0, value);

				regmap_write(p->regmap, 0x00, 0x1801); //POR=0x0001
				regmap_write(p->regmap, 0x02, 0x2dc8); //POR=0x2028
				regmap_write(p->regmap, 0x22, 0x547c);
				regmap_write(p->regmap, 0x51, 0x0000); //POR=0x0080
				regmap_write(p->regmap, 0x52, 0x1a1c); //POR=0x7ae8
				regmap_write(p->regmap, 0x58, 0x161c); //POR=0x101c
				regmap_write(p->regmap, 0x61, 0x0198); //POR=0x0000
				regmap_write(p->regmap, 0x64, 0x4080); //POR=0x0080
				regmap_write(p->regmap, 0x65, 0x1a8b); //POR=0x0a9a
				regmap_write(p->regmap, 0x70, 0x07f5); //POR=0x06e6
				regmap_write(p->regmap, 0x74, 0xcc84); //POR=0xd823
				regmap_write(p->regmap, 0x82, 0x01ed); //POR=0x000d
				regmap_write(p->regmap, 0x83, 0x0014); //POR=0x0013
				regmap_write(p->regmap, 0x84, 0x0021); //POR=0x0020
				regmap_write(p->regmap, 0x85, 0x0001); //POR=0x0003
				regmap_write(p->regmap, 0x68, 0x0427); //POR=0x0400
				regmap_write(p->regmap, 0x23, 0x0009);

				regmap_write(p->regmap, 0xA0, 0);
				regmap_write(p->regmap, 0x0F, 0);
				switch(p->type){
					case TFA98XX_L: //left(spk)
						regmap_write(p->regmap, 0x26, 0x0010);
						break;
					case TFA98XX_R: //right(rcv)
						regmap_write(p->regmap, 0x26, 0x1001);
						break;
					default:
						//Unsupported type
						break;
				}
				break;
			case TFA9872_VERSION_N1B:
				//same as default.
			default:
				hwlog_info("%s: VERSION is N1B\n", __func__);
				regmap_write(p->regmap, 0x0F, 0x5A6B);
				regmap_read(p->regmap, 0xFB, &value);
				value = value ^ 0x005A;
				regmap_write(p->regmap, 0xA0, value);

				regmap_write(p->regmap, 0x00, 0x0001); //POR=0x0001
				regmap_write(p->regmap, 0x02, 0x2dc8); //POR=0x2028
				regmap_write(p->regmap, 0x05, 0x1e2a);
				regmap_write(p->regmap, 0x20, 0x2890);
				regmap_write(p->regmap, 0x22, 0x047c);
				regmap_write(p->regmap, 0x23, 0x0009);
				regmap_write(p->regmap, 0x51, 0x0000); //POR=0x0080
				regmap_write(p->regmap, 0x52, 0x5a1c); //POR=0x7ae8
				regmap_write(p->regmap, 0x61, 0x019a); //POR=0x0000
				regmap_write(p->regmap, 0x63, 0x001a);
				regmap_write(p->regmap, 0x64, 0x4080); //POR=0x0080
				regmap_write(p->regmap, 0x65, 0x1a82); //POR=0x0a9a
				regmap_write(p->regmap, 0x68, 0x0427); //POR=0x0400
				regmap_write(p->regmap, 0x6b, 0x0003);
				regmap_write(p->regmap, 0x6f, 0x01e3);
				regmap_write(p->regmap, 0x71, 0x307e);
				regmap_write(p->regmap, 0x82, 0x01ed); //POR=0x000d
				regmap_write(p->regmap, 0x83, 0x001a); //POR=0x0013

				regmap_write(p->regmap, 0xA0, 0);
				regmap_write(p->regmap, 0x0F, 0);
				switch(p->type){
					case TFA98XX_L: //left(spk)
						regmap_write(p->regmap, 0x26, 0x0010);
						regmap_write(p->regmap, 0x70, 0x0655); //POR=0x06e6
						regmap_write(p->regmap, 0x74, 0xcc74); //POR=0xd823
						regmap_write(p->regmap, 0x75, 0x112a);
						break;
					case TFA98XX_R: //right(rcv)
						regmap_write(p->regmap, 0x26, 0x1001);
						regmap_write(p->regmap, 0x70, 0x063d); //POR=0x06e6
						regmap_write(p->regmap, 0x74, 0xcc44); //POR=0xd823
						regmap_write(p->regmap, 0x75, 0x1122);
						break;
					default:
						//Unsupported type
						break;
				}
				break;
		}
	}

	ret = nonseekable_open(inode, filp);
	if (ret)
		return ret;
	filp->private_data = (void *)(get_tfa98xx_list_head());
	hwlog_info("%s: exit %d\n", __func__, ret);
	return ret;
}
static int tfa9872_release(struct inode *inode, struct file *filp)
{
	hwlog_info("%s: enter\n", __func__);
	return 0;
}
struct tfa98xx_ioctl_ops tfa9872_ioctl_ops = {
	.tfa98xx_open = tfa9872_open,
	.tfa98xx_release = tfa9872_release,
	.tfa98xx_get_version = tfa9872_get_version,
	.tfa98xx_get_reg_val = tfa9872_get_reg_val,
	.tfa98xx_set_reg_val = tfa9872_set_reg_val,
	.tfa98xx_digital_mute = tfa9872_digital_mute,
	.tfa98xx_single_digital_mute = tfa9872_single_digital_mute,
};
#ifdef CONFIG_PM
static int tfa9872_suspend(struct device *dev)
{
	return 0;
}
static int tfa9872_resume(struct device *dev)
{
	return 0;
}
#else
#define tfa9872_suspend NULL
#define tfa9872_resume NULL
#endif
static const struct regmap_config tfa9872_regmap = {
	.reg_bits         = 8,
	.val_bits         = 16,
	.max_register     = TFA9872_REG_MAX_NUM,
	.reg_defaults     = tfa9872_reg,
	.num_reg_defaults = ARRAY_SIZE(tfa9872_reg),
	//.volatile_reg     = tfa9872_volatile_register,
	//.readable_reg     = tfa9872_readable_register,
	.cache_type       = REGCACHE_NONE,
};
static ssize_t tfa98xx_reg_write(struct file *filp, struct kobject *kobj,
				struct bin_attribute *bin_attr,
				char *buf, loff_t off, size_t count)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct tfa98xx_priv *p = NULL;
	p = find_tfa98xx_by_dev(dev);
	if (NULL == p) {
		return 0;
	}
	p->reg = (u8)buf[0];
	return 1;
}
static ssize_t tfa98xx_rw_write(struct file *filp, struct kobject *kobj,
				struct bin_attribute *bin_attr,
				char *buf, loff_t off, size_t count)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct tfa98xx_priv *p = NULL;
	unsigned int val = 0;
	if(0 == count || count > 2) {
		return 0;
	}
	p = find_tfa98xx_by_dev(dev);
	if (NULL == p) {
		return 0;
	}
	val = (unsigned int)((buf[0] << 8) + buf[1]);
	regmap_write(p->regmap, p->reg, val);
	return 1;
}
static ssize_t tfa98xx_rw_read(struct file *filp, struct kobject *kobj,
				struct bin_attribute *bin_attr,
				char *buf, loff_t off, size_t count)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct tfa98xx_priv *p = NULL;
	unsigned int val = 0;
	p = find_tfa98xx_by_dev(dev);
	if (NULL == p) {
		return 0;
	}
	regmap_read(p->regmap, p->reg, &val);

	buf[1] = (char)(val & 0xFF);
	buf[0] = (char)((val >> 8) & 0xFF);

	return 2;
}
static struct bin_attribute dev_attr_rw = {
	.attr = {
		.name = "rw",
		.mode = S_IRUSR | S_IWUSR,
	},
	.size = 0,
	.read = tfa98xx_rw_read,
	.write = tfa98xx_rw_write,
};
static struct bin_attribute dev_attr_reg = {
	.attr = {
		.name = "reg",
		.mode = S_IWUSR,
	},
	.size = 0,
	.read = NULL,
	.write = tfa98xx_reg_write,
};
static int tfa9872_i2c_probe(struct i2c_client *i2c, const struct i2c_device_id *id)
{
	int ret = FAILED;
	const char *type_dts_name = "smartpa_type";
	const char *gain_dts_name = "gain";
	const char *gain_incall_dts_name = "gain_incall";
	struct tfa98xx_priv *tfa9872 = NULL;
	tfa9872 = kzalloc(sizeof(struct tfa98xx_priv), GFP_KERNEL);
	if (NULL == tfa9872) {
		hwlog_err("%s: tfa9872 kamlloc tfa98xx_priv failed!!!\n", __func__);
		goto err_out;
	}
	tfa9872->gpio_reset = of_get_named_gpio(i2c->dev.of_node, "gpio_reset", 0);
	if (tfa9872->gpio_reset < 0) {
		hwlog_err("gpio_reset is invalid!\n");
		ret = FAILED;
	} else {
		hwlog_info("gpio_reset is %d.\n", tfa9872->gpio_reset);
		ret = gpio_request((unsigned int)tfa9872->gpio_reset, "gpio_reset");
		if (ret != 0) {
			hwlog_err("error request GPIO for gpio_reset fail %d\n", ret);
			goto err_out;
		}
		if (!gpio_is_valid(tfa9872->gpio_reset)) {
			hwlog_err("gpio_reset_%d is invalid.\n", tfa9872->gpio_reset);
			goto err_out;
		}
		ret = gpio_direction_output((unsigned int)tfa9872->gpio_reset, 0);
		if (ret < 0){
			hwlog_err("gpio_direction_output err, ret = %d.\n", ret);
			goto err_out;
		}
		tfa9872_reset(tfa9872);
	}
	ret = of_property_read_u32(i2c->dev.of_node, type_dts_name, &tfa9872->type);
	if (ret || tfa9872->type >= ARRAY_SIZE(tfa9872_type_gain_def)) {
		hwlog_err("%s: get smartPA type from dts failed or type is more than default!!!\n", __func__);
		ret = FAILED;
		goto err_out;
	}
	ret = of_property_read_u32(i2c->dev.of_node, gain_dts_name, &tfa9872->gain);
	if (ret) {
		tfa9872->gain = tfa9872_type_gain_def[tfa9872->type].gain;
	}
	hwlog_info("%s: get tfa9872 type[%d]_gain =0x%x\n", __func__, tfa9872->type, tfa9872->gain);
	ret = of_property_read_u32(i2c->dev.of_node, gain_incall_dts_name, &tfa9872->gain_incall);
	if (ret) {
		tfa9872->gain_incall = tfa9872_type_gain_def[tfa9872->type].gain_incall;
	}
	hwlog_info("%s: get tfa9872 type[%d]_gain_incall =0x%x\n", __func__, tfa9872->type, tfa9872->gain_incall);
	tfa9872->regmap = regmap_init_i2c(i2c, &tfa9872_regmap);
	if (IS_ERR(tfa9872->regmap)) {
		ret = (int)PTR_ERR(tfa9872->regmap);
		dev_err(&i2c->dev, "Failed to allocate smartPA type[%d]'s regmap: %d\n", tfa9872->type, ret);
		goto err_out;
	}
	mutex_init(&tfa9872->lock);
	tfa98xx_list_add(tfa9872);
	if ((ret = sysfs_create_group(&i2c->dev.kobj, &tfa9872_attr_group)) < 0) {
		hwlog_err("%s: failed to register smartPA type[%d]'s i2c sysfs, ret =%d\n", __func__, tfa9872->type, ret);
	}
	if (tfa98xx_ioctl_isregist()) {
		tfa98xx_ioctl_regist(&tfa9872_ioctl_ops);
	}
	/* Register the sysfs files for climax backdoor access */
	ret = device_create_bin_file(&i2c->dev, &dev_attr_rw);
	if (ret)
		dev_info(&i2c->dev, "error creating sysfs files\n");
	ret = device_create_bin_file(&i2c->dev, &dev_attr_reg);
	if (ret)
		dev_info(&i2c->dev, "error creating sysfs files\n");
	hwlog_info("%s: ret %d\n", __func__, ret);
err_out:
	if (ret < 0) {
		if (tfa9872 != NULL) {
			if (tfa9872->regmap) {
				regmap_exit(tfa9872->regmap);
			}
			kfree(tfa9872);
		}
		tfa98xx_list_del_all();
	}
	return ret;
}
static int tfa9872_i2c_remove(struct i2c_client *client)
{
	device_remove_bin_file(&client->dev, &dev_attr_reg);
	device_remove_bin_file(&client->dev, &dev_attr_rw);
	tfa98xx_list_del_all();
	hwlog_info("%s: exit\n", __func__);
	return 0;
}
static void tfa9872_i2c_shutdown(struct i2c_client *client)
{
	struct list_head *head = get_tfa98xx_list_head();
	hwlog_info("%s: shutdown for tfa9872\n", __func__);
	tfa9872_digital_mute(head, MUTE_OFF);
	return;
}
static const struct dev_pm_ops tfa9872_pm_ops = {
	.suspend        = tfa9872_suspend,
	.resume            = tfa9872_resume,
};
static const struct of_device_id tfa9872_match[] = {
	{ .compatible = "huawei,tfa9872", },
	{},
};
MODULE_DEVICE_TABLE(of, tfa9872_match);
static const struct i2c_device_id tfa9872_i2c_id[] = {
	{ "tfa9872", 0 },
	{ }
};
MODULE_DEVICE_TABLE(i2c, tfa9872_i2c_id);
static struct i2c_driver tfa9872_i2c_driver = {
	.driver = {
		.name = "tfa9872",
		.owner = THIS_MODULE,
		.pm = &tfa9872_pm_ops,
		.of_match_table = of_match_ptr(tfa9872_match),
	},
	.probe  = tfa9872_i2c_probe,
	.remove = tfa9872_i2c_remove,
	.shutdown = tfa9872_i2c_shutdown,
	.id_table = tfa9872_i2c_id,
};
static int __init tfa98xx_init(void)
{
	return i2c_add_driver(&tfa9872_i2c_driver);
}
static void __exit tfa98xx_exit(void)
{
	tfa98xx_list_del_all();
	i2c_del_driver(&tfa9872_i2c_driver);
}
module_init(tfa98xx_init);
module_exit(tfa98xx_exit);
MODULE_DESCRIPTION("TFA9872 i2c device driver");
MODULE_AUTHOR("zhujiaxin<zhujiaxin@huawei.com>");
MODULE_LICENSE("GPL");
