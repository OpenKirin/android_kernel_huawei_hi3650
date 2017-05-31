

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/i2c.h>
#include <linux/wakelock.h>
#include <linux/usb/otg.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/power_supply.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/hisi/usb/hisi_usb.h>
#include <linux/power/hisi/hisi_bci_battery.h>
#include <linux/power/hisi/coul/hisi_coul_drv.h>
#include <hisi_scharger_v300.h>
#include <linux/raid/pq.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

#ifdef CONFIG_HUAWEI_CHARGER
#include <huawei_platform/power/huawei_charger.h>
#else
#include <linux/power/hisi/charger/hisi_charger.h>
#endif
#include <linux/hisi/hisi_adc.h>

struct hi6523_device_info *g_hi6523_dev = NULL;
struct mutex hi6523_fcp_detect_lock;
struct mutex hi6523_adc_conv_lock;
static int adc_channel_vbat_sys = -1;
static unsigned int is_board_type = 2;	/*0:sft 1:udp 2:asic */
unsigned char hi6523_version;
static int plugout_check_ibus_ma = 150;
static int plugout_check_delay_ms = 1000;
static unsigned int switch_id_flag = 0;/*switch id status no need changed*/
static char g_batt_ovp_cnt_30s;
static char g_vbat_check_cycle;
static char g_batt_ovp_cnt_1s;
static int hi6523_get_vbus_mv(unsigned int *vbus_mv);
static int hi6523_get_charge_state(unsigned int *state);
static int hi6523_set_charge_enable(int enable);

/**********************************************************
*  Function:       is_hi6523_cv_limit
*  Description:    juege if do cv limit
*  Parameters:   NULL
*  return value:  TRUE or FALSE
**********************************************************/
bool is_hi6523_cv_limit(void)
{
	if ((CHG_VERSION_V300 == hi6523_version)
		|| (CHG_VERSION_V310 == hi6523_version))
		return TRUE;
	else
		return FALSE;
}
EXPORT_SYMBOL(is_hi6523_cv_limit);

/**********************************************************
*  Function:       hi6523_write_block
*  Description:    register write block interface
*  Parameters:   di:hi6523_device_info
*                      value:register value
*                      reg:register name
*                      num_bytes:bytes number
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_write_block(struct hi6523_device_info *di, u8 * value,
			      u8 reg, unsigned num_bytes)
{
	struct i2c_msg msg[1];
	int ret = 0;

	*value = reg;

	msg[0].addr = di->client->addr;
	msg[0].flags = 0;
	msg[0].buf = value;
	msg[0].len = num_bytes + 1;

	ret = i2c_transfer(di->client->adapter, msg, 1);

	/* i2c_transfer returns number of messages transferred */
	if (ret != 1) {
		SCHARGER_ERR("i2c_write failed to transfer all messages\n");
		if (ret < 0)
			return ret;
		else
			return -EIO;
	} else {
		return 0;
	}
}

/**********************************************************
*  Function:       hi6523_read_block
*  Description:    register read block interface
*  Parameters:   di:hi6523_device_info
*                      value:register value
*                      reg:register name
*                      num_bytes:bytes number
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_read_block(struct hi6523_device_info *di, u8 * value,
			     u8 reg, unsigned num_bytes)
{
	struct i2c_msg msg[2];
	u8 buf = 0;
	int ret = 0;

	buf = reg;

	msg[0].addr = di->client->addr;
	msg[0].flags = 0;
	msg[0].buf = &buf;
	msg[0].len = 1;

	msg[1].addr = di->client->addr;
	msg[1].flags = I2C_M_RD;
	msg[1].buf = value;
	msg[1].len = num_bytes;

	ret = i2c_transfer(di->client->adapter, msg, 2);

	/* i2c_transfer returns number of messages transferred */
	if (ret != 2) {
		SCHARGER_ERR("i2c_write failed to transfer all messages\n");
		if (ret < 0)
			return ret;
		else
			return -EIO;
	} else {
		return 0;
	}
}

/**********************************************************
*  Function:       hi6523_write_byte
*  Description:    register write byte interface
*  Parameters:   reg:register name
*                      value:register value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_write_byte(u8 reg, u8 value)
{
	struct hi6523_device_info *di = g_hi6523_dev;
	/* 2 bytes offset 1 contains the data offset 0 is used by i2c_write */
	u8 temp_buffer[2] = { 0 };
	if (NULL == di) {
		SCHARGER_ERR("%s hi6523_device_info is NULL!\n", __func__);
		return -ENOMEM;
	}
	/* offset 1 contains the data */
	temp_buffer[1] = value;
	return hi6523_write_block(di, temp_buffer, reg, 1);
}

/**********************************************************
*  Function:       hi6523_read_byte
*  Description:    register read byte interface
*  Parameters:   reg:register name
*                      value:register value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_read_byte(u8 reg, u8 * value)
{
	struct hi6523_device_info *di = g_hi6523_dev;
	if (NULL == di) {
		SCHARGER_ERR("%s hi6523_device_info is NULL!\n", __func__);
		return -ENOMEM;
	}

	return hi6523_read_block(di, value, reg, 1);
}

/**********************************************************
*  Function:       hi6523_write_mask
*  Description:    register write mask interface
*  Parameters:   reg:register name
*                      MASK:mask value of the function
*                      SHIFT:shift number of the function
*                      value:register value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_write_mask(u8 reg, u8 MASK, u8 SHIFT, u8 value)
{
	int ret = 0;
	u8 val = 0;

	ret = hi6523_read_byte(reg, &val);
	if (ret < 0)
		return ret;

	val &= ~MASK;
	val |= ((value << SHIFT) & MASK);

	ret = hi6523_write_byte(reg, val);

	return ret;
}

/**********************************************************
*  Function:       hi6523_read_mask
*  Description:    register read mask interface
*  Parameters:   reg:register name
*                      MASK:mask value of the function
*                      SHIFT:shift number of the function
*                      value:register value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_read_mask(u8 reg, u8 MASK, u8 SHIFT, u8 * value)
{
	int ret = 0;
	u8 val = 0;

	ret = hi6523_read_byte(reg, &val);
	if (ret < 0)
		return ret;
	val &= MASK;
	val >>= SHIFT;
	*value = val;

	return 0;
}

#define CONFIG_SYSFS_SCHG
#ifdef CONFIG_SYSFS_SCHG
/*
 * There are a numerous options that are configurable on the HI6523
 * that go well beyond what the power_supply properties provide access to.
 * Provide sysfs access to them so they can be examined and possibly modified
 * on the fly.
 */

#define HI6523_SYSFS_FIELD(_name, r, f, m, store)                  \
{                                                   \
    .attr = __ATTR(_name, m, hi6523_sysfs_show, store),    \
    .reg = CHG_##r##_REG,                      \
    .mask = CHG_##f##_MSK,                       \
    .shift = CHG_##f##_SHIFT,                     \
}

#define HI6523_SYSFS_FIELD_RW(_name, r, f)                     \
        HI6523_SYSFS_FIELD(_name, r, f, S_IWUSR | S_IRUGO, \
                hi6523_sysfs_store)

static ssize_t hi6523_sysfs_show(struct device *dev,
				 struct device_attribute *attr, char *buf);
static ssize_t hi6523_sysfs_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count);

struct hi6523_sysfs_field_info {
	struct device_attribute attr;
	u8 reg;
	u8 mask;
	u8 shift;
};

static struct hi6523_sysfs_field_info hi6523_sysfs_field_tbl[] = {
	/* sysfs name reg field in reg */
	HI6523_SYSFS_FIELD_RW(en_hiz, HIZ_CTRL, HIZ_ENABLE),
	HI6523_SYSFS_FIELD_RW(iinlim, INPUT_SOURCE, ILIMIT),
	HI6523_SYSFS_FIELD_RW(reg_addr, NONE, NONE),
	HI6523_SYSFS_FIELD_RW(reg_value, NONE, NONE),
};

static struct attribute *hi6523_sysfs_attrs[ARRAY_SIZE(hi6523_sysfs_field_tbl) +
					    1];

static const struct attribute_group hi6523_sysfs_attr_group = {
	.attrs = hi6523_sysfs_attrs,
};

/**********************************************************
*  Function:       hi6523_sysfs_init_attrs
*  Description:    initialize hi6523_sysfs_attrs[] for HI6523 attribute
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void hi6523_sysfs_init_attrs(void)
{
	int i, limit = ARRAY_SIZE(hi6523_sysfs_field_tbl);

	for (i = 0; i < limit; i++)
		hi6523_sysfs_attrs[i] = &hi6523_sysfs_field_tbl[i].attr.attr;

	hi6523_sysfs_attrs[limit] = NULL;	/* Has additional entry for this */
}

/**********************************************************
*  Function:       hi6523_sysfs_field_lookup
*  Description:    get the current device_attribute from hi6523_sysfs_field_tbl by attr's name
*  Parameters:   name:evice attribute name
*  return value:  hi6523_sysfs_field_tbl[]
**********************************************************/
static struct hi6523_sysfs_field_info *hi6523_sysfs_field_lookup(const char
								 *name)
{
	int i, limit = ARRAY_SIZE(hi6523_sysfs_field_tbl);

	for (i = 0; i < limit; i++)
		if (!strcmp(name, hi6523_sysfs_field_tbl[i].attr.attr.name))
			break;

	if (i >= limit)
		return NULL;

	return &hi6523_sysfs_field_tbl[i];
}

/**********************************************************
*  Function:       hi6523_sysfs_show
*  Description:    show the value for all HI6523 device's node
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*  return value:  0-success or others-fail
**********************************************************/
static ssize_t hi6523_sysfs_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct hi6523_sysfs_field_info *info;
	struct hi6523_sysfs_field_info *info2;
	int ret;
	u8 v;

	info = hi6523_sysfs_field_lookup(attr->attr.name);
	if (!info)
		return -EINVAL;

	if (!strncmp("reg_addr", attr->attr.name, strlen("reg_addr"))) {
		return scnprintf(buf, PAGE_SIZE, "0x%hhx\n", info->reg);
	}

	if (!strncmp(("reg_value"), attr->attr.name, strlen("reg_value"))) {
		info2 = hi6523_sysfs_field_lookup("reg_addr");
		if (!info2)
			return -EINVAL;
		info->reg = info2->reg;
	}

	ret = hi6523_read_mask(info->reg, info->mask, info->shift, &v);
	if (ret)
		return ret;

	return scnprintf(buf, PAGE_SIZE, "0x%hhx\n", v);
}

/**********************************************************
*  Function:       hi6523_sysfs_store
*  Description:    set the value for all HI6523 device's node
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*                      count:unused
*  return value:  0-success or others-fail
**********************************************************/
static ssize_t hi6523_sysfs_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct hi6523_sysfs_field_info *info;
	struct hi6523_sysfs_field_info *info2;
	int ret;
	u8 v;

	info = hi6523_sysfs_field_lookup(attr->attr.name);
	if (!info)
		return -EINVAL;

	ret = kstrtou8(buf, 0, &v);
	if (ret < 0)
		return ret;
	if (!strncmp(("reg_value"), attr->attr.name, strlen("reg_value"))) {
		info2 = hi6523_sysfs_field_lookup("reg_addr");
		if (!info2)
			return -EINVAL;
		info->reg = info2->reg;
	}
	if (!strncmp(("reg_addr"), attr->attr.name, strlen("reg_addr"))) {
		if (v < (u8) HI6523_REG_TOTAL_NUM) {
			info->reg = v;
			return count;
		} else {
			return -EINVAL;
		}
	}

	ret = hi6523_write_mask(info->reg, info->mask, info->shift, v);
	if (ret)
		return ret;

	return count;
}

/**********************************************************
*  Function:       hi6523_sysfs_create_group
*  Description:    create the HI6523 device sysfs group
*  Parameters:   di:hi6523_device_info
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_sysfs_create_group(struct hi6523_device_info *di)
{
	hi6523_sysfs_init_attrs();

	return sysfs_create_group(&di->dev->kobj, &hi6523_sysfs_attr_group);
}

/**********************************************************
*  Function:       charge_sysfs_remove_group
*  Description:    remove the HI6523 device sysfs group
*  Parameters:   di:hi6523_device_info
*  return value:  NULL
**********************************************************/
static void hi6523_sysfs_remove_group(struct hi6523_device_info *di)
{
	sysfs_remove_group(&di->dev->kobj, &hi6523_sysfs_attr_group);
}
#else
static int hi6523_sysfs_create_group(struct hi6523_device_info *di)
{
	return 0;
}

static inline void hi6523_sysfs_remove_group(struct hi6523_device_info *di)
{
}
#endif

/**********************************************************
*  Function:       hi6523_device_check
*  Description:    check chip i2c communication
*  Parameters:   null
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_device_check(void)
{
	int ret = 0;
	u8 reg_chip_id0 = 0xff;

	ret = hi6523_read_byte(CHIP_VERSION_4, &reg_chip_id0);
	if (ret) {
		SCHARGER_ERR("[%s]:read chip_id0 fail\n", __func__);
		return CHARGE_IC_BAD;
	}

	if (CHIP_ID0 == reg_chip_id0 || CHIP_ID1 == reg_chip_id0) {
		SCHARGER_INF("hi6523 is good.\n");
		return CHARGE_IC_GOOD;
	}
	SCHARGER_ERR("hi6523 is bad.\n");
	return CHARGE_IC_BAD;
}

/**********************************************************
*  Function:       hi6523_set_bat_comp
*  Description:    set the bat comp
				schargerv100 can't set ir comp due to lx bug
*  Parameters:   value:bat_comp mohm
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_bat_comp(int value)
{
	u8 reg;

	if ((CHG_VERSION_V300 == hi6523_version)
		|| (CHG_VERSION_V310 == hi6523_version))
		return 0;

	if (value < CHG_IR_COMP_MIN)
		reg = 0;
	else if (value >= CHG_IR_COMP_0mohm && value < CHG_IR_COMP_15mohm)
		reg = 0;
	else if (value >= CHG_IR_COMP_15mohm && value < CHG_IR_COMP_30mohm)
		reg = 1;
	else if (value >= CHG_IR_COMP_30mohm && value < CHG_IR_COMP_45mohm)
		reg = 2;
	else if (value >= CHG_IR_COMP_45mohm && value < CHG_IR_COMP_60mohm)
		reg = 3;
	else if (value >= CHG_IR_COMP_60mohm && value < CHG_IR_COMP_75mohm)
		reg = 4;
	else if (value >= CHG_IR_COMP_75mohm && value < CHG_IR_COMP_95mohm)
		reg = 5;
	else if (value >= CHG_IR_COMP_95mohm && value < CHG_IR_COMP_110mohm)
		reg = 6;
	else
		reg = 7;
	return hi6523_write_mask(CHG_IR_COMP_REG, CHG_IR_COMP_MSK,
				 CHG_IR_COMP_SHIFT, reg);
}

/**********************************************************
*  Function:       hi6523_set_vclamp
*  Description:    set the vclamp
*  Parameters:   value:vclamp mv
				schargerv100 can't set vclamp due to lx bug
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_vclamp(int value)
{
	u8 reg;

	if ((CHG_VERSION_V300 == hi6523_version)
		|| (CHG_VERSION_V310 == hi6523_version))
		return 0;
	if (value < CHG_IR_VCLAMP_MIN)
		value = CHG_IR_VCLAMP_MIN;
	else if (value > CHG_IR_VCLAMP_MAX)
		value = CHG_IR_VCLAMP_MAX;
	else {
		//do nothing
	}
	reg = value / CHG_IR_VCLAMP_STEP;
	return hi6523_write_mask(CHG_IR_VCLAMP_REG, CHG_IR_VCLAMP_MSK,
				 CHG_IR_VCLAMP_SHIFT, reg);
}

/**********************************************************
*  Function:       hi6523_set_adc_channel
*  Description:    select adc channel
*  Parameters:     channel
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_adc_channel(u32 chan)
{
	return hi6523_write_mask(CHG_ADC_CTRL_REG, CHG_ADC_CH_MSK,
				 CHG_ADC_CH_SHIFT, (u8) chan);
}

/**********************************************************
*  Function:       hi6523_adc_enable
*  Description:    enable hi6523 adc
*  Parameters:   value: 1(enable) or 0(disable)
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_adc_enable(u32 enable)
{
	return hi6523_write_mask(CHG_ADC_CTRL_REG, CHG_ADC_EN_MSK,
				 CHG_ADC_EN_SHIFT, (u8) enable);
}

/**********************************************************
*  Function:       hi6523_adc_conv_status
*  Description:    get hi6523 adc conv_status
*  Parameters:     null
*  return value:  0-in conv or others-fail
**********************************************************/
static int hi6523_get_adc_conv_status(u8 * value)
{
	return hi6523_read_mask(CHG_ADC_CONV_STATUS_REG,
				CHG_ADC_CONV_STATUS_MSK,
				CHG_ADC_CONV_STATUS_SHIFT, value);
}

/**********************************************************
*  Function:       hi6523_set_conv_start
*  Description:    set covn start
*  Parameters:     chan:adc channel ,data :adc value
*  return value:   0-success or others-fail
**********************************************************/
static int hi6523_get_adc_value(u32 chan, u32 * data)
{
	int ret = 0;
	u8 reg = 0;
	int i = 0;
	u8 adc_data[2] = { 0 };
	struct hi6523_device_info *di = g_hi6523_dev;
	if (NULL == di) {
		SCHARGER_ERR("%s hi6523_device_info is NULL!\n", __func__);
		return -ENOMEM;
	}

	mutex_lock(&hi6523_adc_conv_lock);
	ret |= hi6523_set_adc_channel(chan);
	ret |= hi6523_adc_enable(CHG_ADC_EN);
	ret |=
	    hi6523_write_mask(CHG_ADC_START_REG, CHG_ADC_START_MSK,
			      CHG_ADC_START_SHIFT, TRUE);
	if (ret) {
		SCHARGER_ERR("set covn fail! ret =%d \n", ret);
		hi6523_adc_enable(CHG_ADC_DIS);
		mutex_unlock(&hi6523_adc_conv_lock);
		return -1;
	}
	/*The conversion result is ready after tCONV, max 10ms */
	for (i = 0; i < 10; i++) {
		ret = hi6523_get_adc_conv_status(&reg);
		if (ret) {
			SCHARGER_ERR(" HI6523 read ADC CONV STAT fail!.\n");
			continue;
		}
		/* if ADC Conversion finished, hkadc_valid bit will be 1 */
		if (reg == 1) {
			break;
		}
		msleep(1);
	}

	if (10 == i) {
		SCHARGER_ERR("Wait for ADC CONV timeout! \n");
		hi6523_adc_enable(CHG_ADC_DIS);
		mutex_unlock(&hi6523_adc_conv_lock);
		return -1;
	}
	ret |= hi6523_read_block(di, adc_data, CHG_ADC_DATA_REG, 2);
	ret |= hi6523_adc_enable(CHG_ADC_DIS);
	if (ret) {
		SCHARGER_ERR("[%s]get ibus_ref_data fail,ret:%d\n", __func__,
			     ret);
		hi6523_adc_enable(CHG_ADC_DIS);
		mutex_unlock(&hi6523_adc_conv_lock);
		return -1;
	}
	*data = (u32) adc_data[0] * 256 + adc_data[1];
	mutex_unlock(&hi6523_adc_conv_lock);
	return 0;
}

/**********************************************************
*  Function:     hi6523_set_fast_safe_timer()
*  Description:  set fast safe timer
*  Parameters:   safe timer value
*  return value:
*                 0-success or others-fail
**********************************************************/
static int hi6523_set_fast_safe_timer(u32 chg_fastchg_safe_timer)
{
	return hi6523_write_mask(CHG_FASTCHG_TIMER_REG, CHG_FASTCHG_TIMER_MSK,
				 CHG_FASTCHG_TIMER_SHIFT,
				 (u8) chg_fastchg_safe_timer);
}

/**********************************************************
*  Function:     hi6523_set_precharge_current()
*  Description:  config precharge current limit
*  Parameters:   precharge current
*  return value:
*                 0-success or others-fail
**********************************************************/
static int hi6523_set_precharge_current(int precharge_current)
{
	u8 prechg_limit;

	if (precharge_current < CHG_PRG_ICHG_MIN) {
		precharge_current = CHG_PRG_ICHG_MIN;
	} else if (precharge_current > CHG_PRG_ICHG_MAX) {
		precharge_current = CHG_PRG_ICHG_MAX;
	} else {
		//do nothing
	}

	prechg_limit =
	    (u8) ((precharge_current - CHG_PRG_ICHG_MIN) / CHG_PRG_ICHG_STEP);

	return hi6523_write_mask(CHG_PRE_ICHG_REG, CHG_PRE_ICHG_MSK,
				 CHG_PRE_ICHG_SHIFT, prechg_limit);
}

/**********************************************************
*  Function:     hi6523_set_precharge_voltage()
*  Description:  config precharge voltage
*  Parameters:   precharge voltage
*  return value:
*                 0-success or others-fail
**********************************************************/
static int hi6523_set_precharge_voltage(u32 pre_vchg)
{
	u8 vprechg;
	if (pre_vchg <= CHG_PRG_VCHG_2800)
		vprechg = 0;
	else if (pre_vchg > CHG_PRG_VCHG_2800 && pre_vchg <= CHG_PRG_VCHG_3000)
		vprechg = 1;
	else if (pre_vchg > CHG_PRG_VCHG_3000 && pre_vchg <= CHG_PRG_VCHG_3100)
		vprechg = 2;
	else if (pre_vchg > CHG_PRG_VCHG_3100 && pre_vchg <= CHG_PRG_VCHG_3200)
		vprechg = 3;
	else
		vprechg = 0;	/*default 2.8V */
	return hi6523_write_mask(CHG_PRE_VCHG_REG, CHG_PRE_VCHG_MSK,
				 CHG_PRE_VCHG_SHIFT, vprechg);
}

/**********************************************************
*  Function:     hi6523_set_batfet_ctrl()
*  Description:  config batfet status 1:enable, 0: disable
*  Parameters:   status
*  return value:
*                 0-success or others-fail
**********************************************************/
static int hi6523_set_batfet_ctrl(u32 status)
{
	return hi6523_write_mask(BATFET_CTRL_CFG_REG, BATFET_CTRL_CFG_MSK,
				 BATFET_CTRL_CFG_SHIFT, status);
}

/**********************************************************
*  Function:     hi6523_get_vbus_vset()
*  Description:  get vbus_vset voltage
*  Parameters:   NULL
*  return value:
*                vbus_set voltage: 5V/9V/12V
*                error: -1
**********************************************************/
#if 0
static int hi6523_get_vbus_vset(void)
{
	u8 data = 0;
	int ret = -1;

	ret = hi6523_read_byte(CHG_VBUS_VSET_REG, &data);
	if (ret) {
		SCHARGER_ERR("[%s]:read vbus_vset fail\n", __func__);
		return -1;
	}

	data &= VBUS_VSET_MSK;
	data = data >> VBUS_VSET_SHIFT;
	switch (data) {
	case 0:
		ret = VBUS_VSET_5V;
		break;
	case 1:
		ret = VBUS_VSET_9V;
		break;
	case 2:
		ret = VBUS_VSET_12V;
		break;
	case 3:
		ret = VBUS_VSET_12V;
		break;
	default:
		break;
	}
	return ret;
}
#endif
/**********************************************************
*  Function:       hi6523_get_charge_enable
*  Description:    get the charge enable in charging process
*  Parameters:     void
*  return value:   TRUE or FALSE
**********************************************************/
static bool hi6523_get_charge_enable(void)
{
	u8 charge_state = 0;

	hi6523_read_mask(CHG_ENABLE_REG, CHG_EN_MSK, CHG_EN_SHIFT, &charge_state);

	if (charge_state) {
		return TRUE;
	} else {
		return FALSE;
	}
}

/**********************************************************
*  Function:     hi6523_vbus_init_set()
*  Description:  set vbus voltage init para
*  Parameters:   vbus_vol:VBUS_VSET_5V&VBUS_VSET_9V
*				charge_stop_flag:1 stop charge; 0 charge
*  return value:
*                 void
**********************************************************/
static void hi6523_vbus_init_set(int vbus_vol)
{
	if (VBUS_VSET_5V == vbus_vol) {
		hi6523_write_mask(0xa0, VBUS_VSET_MSK, VBUS_VSET_SHIFT, 0x00);
		hi6523_write_byte(0x78, 0x0);
		if ((CHG_VERSION_V300 == hi6523_version)
			|| (CHG_VERSION_V310 == hi6523_version)) {
			hi6523_write_byte(0x8e, 0x46);
			hi6523_write_byte(0x62, 0x2c);
		} else {
			hi6523_write_byte(0x8e, 0x48);
			hi6523_write_byte(0x62, 0x24);
		}
		hi6523_write_byte(0x64, 0x28);
		hi6523_write_byte(0x71, 0x54);
		if ((CHG_VERSION_V300 == hi6523_version)
			|| (CHG_VERSION_V310 == hi6523_version))
			hi6523_write_byte(0x95, 0x07);
		else
			hi6523_write_mask(0x95, 0x07, 0x00, 0x00);
	} else if (VBUS_VSET_9V == vbus_vol) {
		hi6523_write_mask(0xa0, VBUS_VSET_MSK, VBUS_VSET_SHIFT, 0x01);
		hi6523_write_byte(0x62, 0x2C);
		hi6523_write_byte(0x64, 0x40);
		hi6523_write_byte(0x71, 0x55);
		if ((CHG_VERSION_V300 == hi6523_version)
			|| (CHG_VERSION_V310 == hi6523_version))
			hi6523_write_byte(0x95, 0x07);
		else
			hi6523_write_mask(0x95, 0x07, 0x00, 0x03);
	}
}

/**********************************************************
*  Function:     hi6523_set_vbus_vset()
*  Description:  set vbus_vset voltage
*  Parameters:   vbus_set voltage: 5V/9V/12V
*  return value:
*                 0-success or others-fail
**********************************************************/
static int hi6523_set_vbus_vset(u32 value)
{
	u8 data = 0;
	u32 charger_flag = 0;

	/*check charge state, if open, close charge.*/
	if (TRUE == hi6523_get_charge_enable()) {
		hi6523_set_charge_enable(CHG_DISABLE);
		charger_flag = 1;
	}
	if (value < VBUS_VSET_9V) {
		hi6523_vbus_init_set(VBUS_VSET_5V);
		data = 0;
	} else if (value < VBUS_VSET_12V) {
		hi6523_vbus_init_set(VBUS_VSET_9V);
		data = 1;
	} else {
		data = 2;
	}

	/*resume charge state*/
	if (1 == charger_flag) {
		hi6523_set_charge_enable(CHG_ENABLE);
	}
	return hi6523_write_mask(CHG_VBUS_VSET_REG, VBUS_VSET_MSK,
				 VBUS_VSET_SHIFT, data);
}

/**********************************************************
*  Function:     hi6523_config_opt_param()
*  Description:  config opt parameters for hi6523
*  Parameters:   vbus_vol:5V/9V/12V
*  return value:
*                 0-success or others-fail
**********************************************************/
static int hi6523_config_opt_param(int vbus_vol)
{
	if (CHG_VERSION_V300 == hi6523_version) {
		hi6523_write_byte(0x78, 0x0);
		hi6523_write_byte(0x8e, 0x46);
		hi6523_write_byte(0x62, 0x2c);
		hi6523_write_byte(0x64, 0x28);
		hi6523_write_byte(0x66, 0xf1);
		hi6523_write_mask(0xE1, 0x07 << 0x04, 0x04, 0x03);
		hi6523_write_mask(0xA0, 0x01 << 0x02, 0x02, 0x01);
		hi6523_write_byte(0xE0, 0x87);
		hi6523_write_byte(0x65, 0x80);
		hi6523_write_byte(0x69, 0xd4);
		hi6523_write_byte(0x6a, 0x1f);
		hi6523_write_byte(0x6b, 0x1c);
		hi6523_write_byte(0x72, 0x5d);
		hi6523_write_byte(0x73, 0x18);
		hi6523_write_byte(0x74, 0x01);
		hi6523_write_byte(0x75, 0xd1);
		hi6523_write_byte(0x71, 0x54);
		hi6523_write_byte(0x76, 0x01);
		hi6523_write_byte(0x79, 0x90);
		hi6523_write_byte(0x84, 0x25);
		hi6523_write_byte(0x87, 0x65);
		hi6523_write_byte(0x95, 0x07);
	} else if (CHG_VERSION_V310 == hi6523_version) {
		hi6523_write_byte(0x78, 0x0);
		hi6523_write_byte(0x8e, 0x46);
		hi6523_write_byte(0x62, 0x2c);
		hi6523_write_byte(0x64, 0x28);
		hi6523_write_byte(0x66, 0xf1);
		hi6523_write_mask(0xE1, 0x07 << 0x04, 0x04, 0x03);
		hi6523_write_mask(0xA0, 0x01 << 0x02, 0x02, 0x01);
		hi6523_write_byte(0xE0, 0x87);
		hi6523_write_byte(0x65, 0x80);
		hi6523_write_byte(0x69, 0xd4);
		hi6523_write_byte(0x6a, 0x1f);
		hi6523_write_byte(0x6b, 0x1c);
		hi6523_write_byte(0x72, 0x5d);
		hi6523_write_byte(0x73, 0x18);
		hi6523_write_byte(0x74, 0x01);
		hi6523_write_byte(0x75, 0xd1);
		hi6523_write_byte(0x71, 0x54);
		hi6523_write_byte(0x76, 0x01);
		hi6523_write_byte(0x79, 0x90);
		hi6523_write_byte(0x84, 0x25);
		hi6523_write_byte(0x87, 0x65);
		hi6523_write_byte(0x95, 0x07);
	} else if (CHG_VERSION_V320 == hi6523_version) {
		hi6523_write_byte(0x78, 0x0);
		hi6523_write_byte(0x8e, 0x48);
		hi6523_write_byte(0x62, 0x24);
		hi6523_write_byte(0x64, 0x28);
		hi6523_write_byte(0x66, 0xf1);
		hi6523_write_mask(0xE1, 0x03 << 0x05, 0x05, 0x01);
		hi6523_write_mask(0xA0, 0x01 << 0x02, 0x02, 0x01);
		hi6523_write_byte(0xE0, 0x87);
		hi6523_write_byte(0x65, 0x80);
		hi6523_write_byte(0x69, 0xd4);
		hi6523_write_byte(0x6a, 0x1f);
		hi6523_write_byte(0x6b, 0x1c);
		hi6523_write_byte(0x72, 0x5d);
		hi6523_write_byte(0x73, 0x18);
		hi6523_write_byte(0x74, 0x01);
		hi6523_write_byte(0x75, 0xd1);
		hi6523_write_byte(0x71, 0x54);
		hi6523_write_byte(0x76, 0x02);
		hi6523_write_byte(0x79, 0x90);
		hi6523_write_byte(0x84, 0x25);
		hi6523_write_byte(0x87, 0x65);
		hi6523_write_byte(0x96, 0x04);
		hi6523_write_byte(0x97, 0xd4);
		hi6523_write_byte(0x9e, 0x8a);
	}

	hi6523_vbus_init_set(vbus_vol);
	return 0;
}

/**********************************************************
*  Function:       hi6523_set_input_current
*  Description:    set the input current in charging process
*  Parameters:   value:input current value
*  return value:  0-success or others-fail
**********************************************************/

static int hi6523_set_input_current(int cin_limit)
{
	u8 Iin_limit;

	if (cin_limit <= CHG_ILIMIT_100)
		Iin_limit = 0;
	else if (cin_limit > CHG_ILIMIT_100 && cin_limit <= CHG_ILIMIT_130)
		Iin_limit = 1;
	else if (cin_limit > CHG_ILIMIT_130 && cin_limit <= CHG_ILIMIT_699)
		Iin_limit = 2;
	else if (cin_limit > CHG_ILIMIT_699 && cin_limit <= CHG_ILIMIT_900)
		Iin_limit = 3;
	else if (cin_limit > CHG_ILIMIT_900 && cin_limit <= CHG_ILIMIT_1000)
		Iin_limit = 4;
	else if (cin_limit > CHG_ILIMIT_1000 && cin_limit <= CHG_ILIMIT_1080)
		Iin_limit = 5;
	else if (cin_limit > CHG_ILIMIT_1080 && cin_limit <= CHG_ILIMIT_1200)
		Iin_limit = 6;
	else if (cin_limit > CHG_ILIMIT_1200 && cin_limit <= CHG_ILIMIT_1300)
		Iin_limit = 7;
	else if (cin_limit > CHG_ILIMIT_1300 && cin_limit <= CHG_ILIMIT_1400)
		Iin_limit = 8;
	else if (cin_limit > CHG_ILIMIT_1400 && cin_limit <= CHG_ILIMIT_1500)
		Iin_limit = 9;
	else if (cin_limit > CHG_ILIMIT_1500 && cin_limit <= CHG_ILIMIT_1600)
		Iin_limit = 10;
	else if (cin_limit > CHG_ILIMIT_1600 && cin_limit <= CHG_ILIMIT_1700)
		Iin_limit = 11;
	else if (cin_limit > CHG_ILIMIT_1700 && cin_limit <= CHG_ILIMIT_1800)
		Iin_limit = 12;
	else if (cin_limit > CHG_ILIMIT_1800 && cin_limit <= CHG_ILIMIT_1900)
		Iin_limit = 13;
	else if (cin_limit > CHG_ILIMIT_1900 && cin_limit <= CHG_ILIMIT_2000)
		Iin_limit = 14;
	else if (cin_limit > CHG_ILIMIT_2000 && cin_limit <= CHG_ILIMIT_2100)
		Iin_limit = 15;
	else if (cin_limit > CHG_ILIMIT_2100 && cin_limit <= CHG_ILIMIT_2200)
		Iin_limit = 16;
	else if (cin_limit > CHG_ILIMIT_2200 && cin_limit <= CHG_ILIMIT_2280)
		Iin_limit = 17;
	else if (cin_limit > CHG_ILIMIT_2280 && cin_limit <= CHG_ILIMIT_2400)
		Iin_limit = 18;
	else if (cin_limit > CHG_ILIMIT_2400 && cin_limit <= CHG_ILIMIT_2480)
		Iin_limit = 19;
	else if (cin_limit > CHG_ILIMIT_2480 && cin_limit <= CHG_ILIMIT_2600)
		Iin_limit = 20;
	else if (cin_limit > CHG_ILIMIT_2600 && cin_limit <= CHG_ILIMIT_2680)
		Iin_limit = 21;
	else if (cin_limit > CHG_ILIMIT_2680 && cin_limit <= CHG_ILIMIT_2800)
		Iin_limit = 22;
	else if (cin_limit > CHG_ILIMIT_2800 && cin_limit <= CHG_ILIMIT_2880)
		Iin_limit = 23;
	else if (cin_limit > CHG_ILIMIT_2880 && cin_limit <= CHG_ILIMIT_3000)
		Iin_limit = 24;
	else if (cin_limit > CHG_ILIMIT_3000 && cin_limit <= CHG_ILIMIT_3080)
		Iin_limit = 25;
	else if (cin_limit > CHG_ILIMIT_3080 && cin_limit <= CHG_ILIMIT_3200)
		Iin_limit = 26;
	else
		Iin_limit = 26;

	SCHARGER_INF("input current reg is set 0x%x\n", Iin_limit);
	return hi6523_write_mask(CHG_INPUT_SOURCE_REG, CHG_ILIMIT_MSK,
				 CHG_ILIMIT_SHIFT, Iin_limit);
}

/**********************************************************
*  Function:       hi6523_get_input_current
*  Description:    get the input current limit
*  Parameters:  NULL
*  return value:  ilimit mA
**********************************************************/

static int hi6523_get_input_current(void)
{
	int ret = 0;
	u8 reg = 0;
	hi6523_read_mask(CHG_INPUT_SOURCE_REG, CHG_ILIMIT_MSK, CHG_ILIMIT_SHIFT,
			 &reg);
	switch (reg) {
	case 0:
		ret = 100;
		break;
	case 1:
		ret = 130;
		break;
	case 2:
		ret = 470;
		break;
	case 3:
		ret = 900;
		break;
	case 4:
		ret = 1000;
		break;
	case 5:
		ret = 1080;
		break;
	case 6:
		ret = 1200;
		break;
	case 7:
		ret = 1300;
		break;
	case 8:
		ret = 1400;
		break;
	case 9:
		ret = 1500;
		break;
	case 10:
		ret = 1600;
		break;
	case 11:
		ret = 1700;
		break;
	case 12:
		ret = 1800;
		break;
	case 13:
		ret = 1900;
		break;
	case 14:
		ret = 2000;
		break;
	case 15:
		ret = 2100;
		break;
	case 16:
		ret = 2200;
		break;
	case 17:
		ret = 2280;
		break;
	case 18:
		ret = 2400;
		break;
	case 19:
		ret = 2480;
		break;
	case 20:
		ret = 2600;
		break;
	case 21:
		ret = 2680;
		break;
	case 22:
		ret = 2800;
		break;
	case 23:
		ret = 2880;
		break;
	case 24:
		ret = 3000;
		break;
	case 25:
		ret = 3080;
		break;
	case 26:
		ret = 3200;
		break;
	default:
		break;
	}
	return ret;
}

/**********************************************************
*  Function:       hi6523_set_charge_current
*  Description:    set the charge current in charging process
*  Parameters:   value:charge current value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_charge_current(int charge_current)
{
	u8 Ichg_limit;
	if (charge_current <= CHG_FAST_ICHG_100MA) {
		Ichg_limit = 0;
	} else if (charge_current > CHG_FAST_ICHG_100MA
		   && charge_current <= CHG_FAST_ICHG_1000MA) {
		Ichg_limit =
		    (charge_current -
		     CHG_FAST_ICHG_100MA) / CHG_FAST_ICHG_STEP_100;
	} else if (charge_current > CHG_FAST_ICHG_1000MA
		   && charge_current <= CHG_FAST_ICHG_2000MA) {
		Ichg_limit =
		    (charge_current -
		     CHG_FAST_ICHG_1000MA) / CHG_FAST_ICHG_STEP_200 + 9;
	} else if (charge_current > CHG_FAST_ICHG_2000MA
		   && charge_current <= CHG_FAST_ICHG_3000MA) {
		Ichg_limit =
		    (charge_current -
		     CHG_FAST_ICHG_2000MA) / CHG_FAST_ICHG_STEP_100 + 14;
	} else if (charge_current > CHG_FAST_ICHG_3000MA
		   && charge_current <= CHG_FAST_ICHG_4200MA) {
		Ichg_limit =
		    (charge_current -
		     CHG_FAST_ICHG_3000MA) / CHG_FAST_ICHG_STEP_200 + 24;
	} else if (charge_current > CHG_FAST_ICHG_4200MA
		   && charge_current < CHG_FAST_ICHG_4500MA) {
		Ichg_limit = 30;
	} else {
		Ichg_limit = 31;
	}
	SCHARGER_INF("charge current reg is set 0x%x\n", Ichg_limit);
	return hi6523_write_mask(CHG_FAST_CURRENT_REG, CHG_FAST_ICHG_MSK,
				 CHG_FAST_ICHG_SHIFT, Ichg_limit);
}

/**********************************************************
*  Function:       hi6523_set_terminal_voltage
*  Description:    set the terminal voltage in charging process
		(v300&v310 scharger's max cv is 4.25V due to lx bug)
*  Parameters:   value:terminal voltage value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_terminal_voltage(int charge_voltage)
{
	u8 data;
	struct hi6523_device_info *di = g_hi6523_dev;

	if (NULL == di) {
		SCHARGER_ERR("%s hi6523_device_info is NULL!\n", __func__);
		return -ENOMEM;
	}

	if (charge_voltage < CHG_FAST_VCHG_MIN) {
		charge_voltage = CHG_FAST_VCHG_MIN;
	} else if (charge_voltage > CHG_FAST_VCHG_MAX) {
		charge_voltage = CHG_FAST_VCHG_MAX;
	} else {
		//do nothing
	}
	if (TRUE == is_hi6523_cv_limit()) {
		if (charge_voltage > CHG_FAST_VCHG_4250)
			charge_voltage = CHG_FAST_VCHG_4250;
	}
	di->term_vol_mv = charge_voltage;
	data =
	    (u8) ((charge_voltage - CHG_FAST_VCHG_MIN) / CHG_FAST_VCHG_STEP_50);
	return hi6523_write_mask(CHG_FAST_VCHG_REG, CHG_FAST_VCHG_MSK,
				 CHG_FAST_VCHG_SHIFT, data);
}

/**********************************************************
*  Function:       hi6523_get_terminal_voltage
*  Description:    get the terminal voltage in charging process
*  Parameters:   value:terminal voltage value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_get_terminal_voltage(void)
{
	u8 data = 0;

	hi6523_read_mask(CHG_FAST_VCHG_REG, CHG_FAST_VCHG_MSK,
				 CHG_FAST_VCHG_SHIFT, &data);
	return (int)(data * CHG_FAST_VCHG_STEP_50 + CHG_FAST_VCHG_MIN);
}
/**********************************************************
*  Function:       hi6523_check_input_dpm_state
*  Description:    check whether VINDPM or IINDPM
*  Parameters:     NULL
*  return value:   TRUE means VINDPM or IINDPM
*                  FALSE means NoT DPM
**********************************************************/
static int hi6523_check_input_dpm_state(void)
{
	u8 reg = 0;
	int ret;

	ret = hi6523_read_byte(CHG_STATUS0_REG, &reg);
	if (ret < 0) {
		SCHARGER_ERR("hi6523_check_input_dpm_state err\n");
		return ret;
	}

	if (CHG_IN_DPM_STATE == (reg & CHG_IN_DPM_STATE))
		return TRUE;
	return FALSE;
}

/**********************************************************
*  Function:       hi6523_get_charge_state
*  Description:    get the charge states in charging process
*  Parameters:   state:charge states
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_get_charge_state(unsigned int *state)
{
	u8 reg1 = 0, reg2 = 0;
	int ret = 0;

	ret |= hi6523_read_byte(CHG_STATUS0_REG, &reg1);
	ret |= hi6523_read_byte(CHG_STATUS1_REG, &reg2);
	if (ret) {
		SCHARGER_ERR("[%s]read charge status reg fail,ret:%d\n",
			     __func__, ret);
		return -1;
	}

	if (HI6523_CHG_BUCK_OK != (reg1 & HI6523_CHG_BUCK_OK))
		*state |= CHAGRE_STATE_NOT_PG;
	if (HI6523_CHG_STAT_CHARGE_DONE == (reg1 & HI6523_CHG_STAT_CHARGE_DONE))
		*state |= CHAGRE_STATE_CHRG_DONE;
	if (HI6523_WATCHDOG_OK != (reg2 & HI6523_WATCHDOG_OK))
		*state |= CHAGRE_STATE_WDT_FAULT;
	return ret;
}

/**********************************************************
*  Function:       hi6523_get_anti_reverbst_state
*  Description:    check if the anti_reverbst is enabled in charging process
*  Parameters:    NULL
*  return value:  TRUE or FALSE
**********************************************************/
static bool hi6523_get_anti_reverbst_enabled(void)
{
	u8 reg_val = 0;

	hi6523_read_mask(CHG_ANTI_REVERBST_REG, CHG_ANTI_REVERBST_EN_MSK, CHG_ANTI_REVERBST_EN_SHIFT, &reg_val);

	if (CHG_ANTI_REVERBST_EN != reg_val) {
		return FALSE;
	}
	return TRUE;
}

/**********************************************************
*  Function:       hi6523_set_dpm_voltage
*  Description:    set the dpm voltage in charging process
*  Parameters:   value:dpm voltage value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_dpm_voltage(int vindpm)
{
	return 0;
}

/**********************************************************
*  Function:       hi6523_set_terminal_current
*  Description:    set the terminal current in charging process
*                   (min value is 400ma for scharger ic bug)
*  Parameters:   value:terminal current value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_terminal_current(int term_current)
{
	u8 Iterm;
	if (term_current <= CHG_TERM_ICHG_400MA)
		Iterm = 5;
	else if (term_current > CHG_TERM_ICHG_400MA
		 && term_current <= CHG_TERM_ICHG_500MA)
		Iterm = 6;
	else if (term_current > CHG_TERM_ICHG_500MA
		 && term_current <= CHG_TERM_ICHG_600MA)
		Iterm = 7;
	else
		Iterm = 5;	/*default 400mA */

	SCHARGER_INF(" term current reg is set 0x%x\n", Iterm);
	return hi6523_write_mask(CHG_TERM_ICHG_REG, CHG_TERM_ICHG_MSK,
				 CHG_TERM_ICHG_SHIFT, Iterm);
}

/**********************************************************
*  Function:       hi6523_set_charge_enable
*  Description:    set the charge enable in charging process
*  Parameters:     enable:charge enable or not
*  return value:   0-success or others-fail
**********************************************************/
static int hi6523_set_charge_enable(int enable)
{
	/*invalidate charge enable on udp board */
	if ((BAT_BOARD_UDP == is_board_type) && (CHG_ENABLE == enable))
		return 0;
	return hi6523_write_mask(CHG_ENABLE_REG, CHG_EN_MSK, CHG_EN_SHIFT,
				 enable);
}

/**********************************************************
*  Function:       hi6523_config_otg_opt_param
*  Description:    config hi6523 opt params for otg
*  Parameters:     NULL
*  return value:   0-success or others-fail
**********************************************************/
static int hi6523_config_otg_opt_param(void)
{
	int ret = 0;
	u8 otg_lim_set = 0;
	hi6523_read_mask(CHG_OTG_REG0, CHG_OTG_LIM_MSK, CHG_OTG_LIM_SHIFT,
			 &otg_lim_set);
	ret |= hi6523_write_byte(0x6a, 0x3f);
	ret |= hi6523_write_byte(0x6b, 0x5c);
	ret |= hi6523_write_byte(0x81, 0x5c);
	ret |= hi6523_write_byte(0x86, 0x39);
	/*need to config regs according to otg current */
	if (3 != otg_lim_set) {
		ret |= hi6523_write_byte(0x8a, 0x10);
		ret |= hi6523_write_byte(0x88, 0xbf);
	} else {
		ret |= hi6523_write_byte(0x8a, 0x18);
		ret |= hi6523_write_byte(0x88, 0x9f);
	}
	return ret;
}

/**********************************************************
*  Function:       hi6523_set_otg_enable
*  Description:    set the otg mode enable in charging process
*  Parameters:   enable:otg mode  enable or not
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_otg_enable(int enable)
{
	if (enable) {
		hi6523_set_charge_enable(CHG_DISABLE);
		hi6523_config_otg_opt_param();
	}
	return hi6523_write_mask(CHG_OTG_REG0, CHG_OTG_EN_MSK, CHG_OTG_EN_SHIFT,
				 enable);
}

/**********************************************************
*  Function:       hi6523_set_otg_current
*  Description:    set the otg mdoe current
*  Parameters:     value :current value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_otg_current(int value)
{
	unsigned int temp_currentmA = 0;
	u8 reg = 0;
	temp_currentmA = value;

	if (temp_currentmA < BOOST_LIM_MIN || temp_currentmA > BOOST_LIM_MAX)
		SCHARGER_INF("set otg current %dmA is out of range!\n", value);
	if (temp_currentmA < BOOST_LIM_500) {
		reg = 3;
	} else if (temp_currentmA >= BOOST_LIM_500
		   && temp_currentmA < BOOST_LIM_1000) {
		reg = 3;
	} else if (temp_currentmA >= BOOST_LIM_1000
		   && temp_currentmA < BOOST_LIM_1500) {
		reg = 1;
	} else if (temp_currentmA >= BOOST_LIM_1500
		   && temp_currentmA < BOOST_LIM_2000) {
		reg = 0;
	} else {
		reg = 0;
	}

	SCHARGER_INF(" otg current reg is set 0x%x\n", reg);
	return hi6523_write_mask(CHG_OTG_REG0, CHG_OTG_LIM_MSK,
				 CHG_OTG_LIM_SHIFT, reg);
}

/**********************************************************
*  Function:       hi6523_vbus_in_dpm
*  Description:    juege if in dpm by vbus vol
*  Parameters:   vbus mv
*  return value:  TRUE or FALSE
**********************************************************/
static bool hi6523_vbus_in_dpm(int vbus)
{
	if ((CHG_VERSION_V300 == hi6523_version)
		|| (CHG_VERSION_V310 == hi6523_version)) {
		if (vbus <= CHG_DPM_VOL_4855_MV)
			return TRUE;
		else
			return FALSE;
	} else {
		if (vbus <= CHG_DPM_VOL_4835_MV)
			return TRUE;
		else
			return FALSE;
	}
}

/**********************************************************
*  Function:       hi6523_set_term_enable
*  Description:    set the terminal enable in charging process
*  Parameters:   enable:terminal enable or not
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_term_enable(int enable)
{
	int vbatt_mv;
	int term_mv;
	u8 state = 0;
	int vbus = 0;
	int ret;

	if (0 == enable)
		return hi6523_write_mask(CHG_EN_TERM_REG, CHG_EN_TERM_MSK,
					 CHG_EN_TERM_SHIFT, (u8)enable);
	hi6523_read_byte(CHG_STATUS0_REG, &state);
	vbatt_mv = hisi_battery_voltage();
	term_mv = hi6523_get_terminal_voltage();
	ret = hi6523_get_vbus_mv((unsigned int *)&vbus);
	if (ret)
		return -1;
	if ((0 == (CHG_TERM_ABLE_STATE & state)) &&
			((FALSE == hi6523_vbus_in_dpm(vbus)) ||
			(0 == (CHG_IN_DPM_STATE & state))) &&
			(vbatt_mv > (term_mv - 100))) {
		return hi6523_write_mask(CHG_EN_TERM_REG, CHG_EN_TERM_MSK,
					 CHG_EN_TERM_SHIFT, (u8)enable);
	} else {
		SCHARGER_INF("cancel term_en state:0x%x,vbatt_mv:%d,term_mv:%d\n",
			state, vbatt_mv, term_mv);
		/*close EOC*/
		hi6523_write_mask(CHG_EN_TERM_REG, CHG_EN_TERM_MSK,
					 CHG_EN_TERM_SHIFT, (u8)CHG_TERM_DIS);
		return -1;
	}
}

/**********************************************************
*  Function:       hi6523_get_vbus_mv
*  Description:    get voltage of vbus
*  Parameters:   vbus_mv:voltage of vbus
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_get_vbus_mv(unsigned int *vbus_mv)
{
	int ret;
	u32 result = 0;
	u32 vref = 2000;	//2000mV

	ret = hi6523_get_adc_value(CHG_ADC_CH_VBUS, &result);
	if (ret) {
		SCHARGER_ERR("[%s]get vbus_mv fail,ret:%d\n", __func__, ret);
		return -1;
	}

	*vbus_mv = result * vref * 7 / 4096;
	return ret;
}

/**********************************************************
*  Function:       hi6523_reset_watchdog_timer
*  Description:    reset watchdog timer in charging process
*  Parameters:   NULL
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_reset_watchdog_timer(void)
{
	return hi6523_write_mask(WATCHDOG_SOFT_RST_REG, WD_RST_N_MSK,
				 WATCHDOG_TIMER_SHIFT, WATCHDOG_TIMER_RST);
}

/**********************************************************
*  Function:       hi6523_get_ibus_ma
*  Description:    get average value for ilim
*  Parameters:     NULL
*  return value:   average value for ilim
**********************************************************/
static int hi6523_get_ibus_ma(void)
{
	int ret = 0;
	int ilimit = 0;
	u32 ibus_ref_data = 0;
	u32 ibus_data = 0;
	u32 ibus = 0;
	u32 state = 0;

	ret |= hi6523_get_charge_state(&state);
	if (ret) {
		SCHARGER_ERR("[%s] get_charge_state fail,ret:%d\n", __func__,
			     ret);
		return -1;
	}
	if (CHAGRE_STATE_NOT_PG & state) {
		SCHARGER_INF("[%s] CHAGRE_STATE_NOT_PG ,state:%d\n", __func__,
			     state);
		return 0;
	}
	ret |= hi6523_get_adc_value(CHG_ADC_CH_IBUS_REF, &ibus_ref_data);
	if (ret) {
		SCHARGER_ERR("[%s]get ibus_ref_data fail,ret:%d\n", __func__,
			     ret);
		return -1;
	}

	ret |= hi6523_get_adc_value(CHG_ADC_CH_IBUS, &ibus_data);
	if (ret) {
		SCHARGER_ERR("[%s]get ibus_data fail,ret:%d\n", __func__, ret);
		return -1;
	}

	ilimit = hi6523_get_input_current();
	if (0 == ibus_ref_data)
		return -1;
	ibus = ibus_data * ilimit / ibus_ref_data;
	return ibus;
}

/**********************************************************
*  Function:       hi6523_vbat_sys
*  Description:    get vsys sample
*  Parameters:     NULL
*  return value:   vsys sample
**********************************************************/
static int hi6523_vbat_sys(void)
{
	int i = 0;
	int retry_times = 3;
	int V_sample = -1;

	if (adc_channel_vbat_sys < 0)
		return V_sample;

	for (i = 0; i < retry_times; ++i) {
		V_sample = hisi_adc_get_value(adc_channel_vbat_sys);
		if (V_sample < 0) {
			SCHARGER_ERR("adc read channel 15 fail!\n");
		} else {
			break;
		}
	}
	return V_sample;
}

/**********************************************************
*  Function:       hi6523_get_vbat_sys
*  Description:    get vsys voltage
*  Parameters:     NULL
*  return value:   vsys voltage
**********************************************************/
static int hi6523_get_vbat_sys(void)
{
	int i;
	int cnt = 0;
	int V_temp;
	int delay_times = 100;
	int sample_num = 5;	// use 5 samples to get an average value
	int sum = 0;

	for (i = 0; i < sample_num; ++i) {
		V_temp = hi6523_vbat_sys();
		if (V_temp >= 0) {
			sum += V_temp;
			++cnt;
		} else {
			SCHARGER_ERR("hi6523 get V_temp fail!\n");
		}
		msleep(delay_times);
	}
	if (cnt > 0) {
		return (3 * 1000 * sum / cnt);
	} else {
		SCHARGER_ERR("use 0 as default Vvlim!\n");
		return 0;
	}
}

/**********************************************************
*  Function:       hi6523_dump_register
*  Description:    print the register value in charging process
*  Parameters:   reg_value:string for save register value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_dump_register(char *reg_value)
{
	u8 reg[HI6523_REG_TOTAL_NUM] = { 0 };
	char buff[26] = { 0 };
	int i = 0;
	int vbus = 0;
	struct hi6523_device_info *di = g_hi6523_dev;
	if (NULL == di) {
		SCHARGER_ERR("%s hi6523_device_info is NULL!\n", __func__);
		return -ENOMEM;
	}
	memset(reg_value, 0, CHARGELOG_SIZE);
	hi6523_read_block(di, &reg[0], 0, HI6523_REG_TOTAL_NUM);
	hi6523_get_vbus_mv((unsigned int *)&vbus);
	snprintf(buff, 26, "%-8.2d", hi6523_get_ibus_ma());
	strncat(reg_value, buff, strlen(buff));
	snprintf(buff, (unsigned long)26, "%-8.2d", vbus);
	strncat(reg_value, buff, strlen(buff));
	for (i = 0; i < HI6523_REG_TOTAL_NUM; i++) {
		snprintf(buff, 26, "0x%-8x", reg[i]);
		strncat(reg_value, buff, strlen(buff));
	}
	return 0;
}

/**********************************************************
*  Function:       hi6523_get_register_head
*  Description:    print the register head in charging process
*  Parameters:   reg_head:string for save register head
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_get_register_head(char *reg_head)
{
	char buff[26] = { 0 };
	int i = 0;

	memset(reg_head, 0, CHARGELOG_SIZE);
	snprintf(buff, 26, "Ibus    ");
	strncat(reg_head, buff, strlen(buff));
	snprintf(buff, (unsigned long)26, "Vbus    ");
	strncat(reg_head, buff, strlen(buff));
	for (i = 0; i < HI6523_REG_TOTAL_NUM; i++) {
		snprintf(buff, 26, "Reg[0x%2x] ", i);
		strncat(reg_head, buff, strlen(buff));
	}
	return 0;
}

/**********************************************************
*  Function:       hi6523_set_batfet_disable
*  Description:    set the batfet disable in charging process
*  Parameters:   disable:batfet disable or not
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_batfet_disable(int disable)
{
	return hi6523_set_batfet_ctrl(!disable);
}

/**********************************************************
*  Function:       hi6523_set_watchdog_timer
*  Description:    set the watchdog timer in charging process
*  Parameters:   value:watchdog timer value
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_watchdog_timer(int value)
{
	u8 val = 0;
	u8 dog_time = value;
	if (dog_time >= WATCHDOG_TIMER_40_S) {
		val = 3;
	} else if (dog_time >= WATCHDOG_TIMER_20_S) {
		val = 2;
	} else if (dog_time >= WATCHDOG_TIMER_10_S) {
		val = 1;
	} else {
		val = 0;
	}
	SCHARGER_INF(" watch dog timer is %d ,the register value is set %u \n",
		     dog_time, val);
	return hi6523_write_mask(WATCHDOG_CTRL_REG, WATCHDOG_TIMER_MSK,
				 WATCHDOG_TIMER_SHIFT, val);
}

/**********************************************************
*  Function:       hi6523_set_charger_hiz
*  Description:    set the charger hiz close watchdog
*  Parameters:   enable:charger in hiz or not
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_set_charger_hiz(int enable)
{
	return hi6523_write_mask(CHG_HIZ_CTRL_REG, CHG_HIZ_ENABLE_MSK,
				 CHG_HIZ_ENABLE_SHIFT, enable);
}

/**********************************************************
*  Function:       hi6523_is_charger_hiz
*  Description:   is charger in hiz or not
*  Parameters:   NULL
*  return value:  TRUE or FALSE
**********************************************************/
static bool hi6523_is_charger_hiz(void)
{
	u8 hiz_state = 0;
	hi6523_read_mask(CHG_HIZ_CTRL_REG, CHG_HIZ_ENABLE_MSK,/*lint !e835*/
		CHG_HIZ_ENABLE_SHIFT, &hiz_state);
	if (hiz_state)
		return TRUE;
	return FALSE;
}
/****************************************************************************
  Function:     hi6523_disable_adapter_detect
  Description:  enable scharger apple adapter detect
  Input:        NA
  Output:       NA
  Return:        0: success
                -1: other fail
***************************************************************************/
static int hi6523_apple_adapter_detect(int enable)
{
	return hi6523_write_mask(CHG_ADC_APPDET_REG, APPLE_DETECT_MASK, APPLE_DETECT_SHIFT,
		enable);
}

/****************************************************************************
  Function:     hi6523_soft_vbatt_ovp_protect
  Description:  vbatt soft ovp check
  Input:        NA
  Output:       NA
  Return:        0: success;-1: other fail
***************************************************************************/
static int hi6523_soft_vbatt_ovp_protect(void)
{
	struct hi6523_device_info *di = g_hi6523_dev;
	int vbatt_mv;

	if (NULL == di)
		return -1;
	vbatt_mv = hisi_battery_voltage();
	if (vbatt_mv >= MIN(CHG_VBATT_SOFT_OVP_MAX, CHG_VBATT_CV_103(di->term_vol_mv))) {
		g_batt_ovp_cnt_30s++;
		if (CHG_VBATT_SOFT_OVP_CNT == g_batt_ovp_cnt_30s) {
			hi6523_set_charger_hiz(TRUE);
			SCHARGER_ERR("%s:vbat:%d,cv_mv:%d,ovp_cnt:%d,shutdown buck.\n",
				__func__, vbatt_mv, di->term_vol_mv, g_batt_ovp_cnt_30s);
			g_batt_ovp_cnt_30s = 0;
			}
	} else
	g_batt_ovp_cnt_30s = 0;
	return 0;
}

/**********************************************************
*  Function:     hi6523_chip_init()
*  Description:  chip init for hi6523
*  Parameters:   NULL
*  return value:
*                 0-success or others-fail
**********************************************************/
static int hi6523_chip_init(void)
{
	int ret = 0;
	struct hi6523_device_info *di = g_hi6523_dev;
	if (NULL == di) {
		SCHARGER_ERR("%s hi6523_device_info is NULL!\n", __func__);
		return -ENOMEM;
	}

	ret |= hi6523_set_charge_enable(CHG_DISABLE);
	ret |= hi6523_config_opt_param(VBUS_VSET_5V);
	ret |= hi6523_set_fast_safe_timer(CHG_FASTCHG_TIMER_20H);
	ret |= hi6523_set_term_enable(CHG_TERM_DIS);
	ret |= hi6523_set_input_current(CHG_ILIMIT_470);
	ret |= hi6523_set_charge_current(CHG_FAST_ICHG_500MA);
	ret |= hi6523_set_terminal_voltage(CHG_FAST_VCHG_4350);
	ret |= hi6523_set_terminal_current(CHG_TERM_ICHG_150MA);
	ret |= hi6523_set_watchdog_timer(WATCHDOG_TIMER_40_S);
	ret |= hi6523_set_precharge_current(CHG_PRG_ICHG_200MA);
	ret |= hi6523_set_precharge_voltage(CHG_PRG_VCHG_2800);
	ret |= hi6523_set_batfet_ctrl(CHG_BATFET_EN);
	/*IR compensation voatge clamp ,IR compensation resistor setting */
	ret |= hi6523_set_bat_comp(di->param_dts.bat_comp);
	ret |= hi6523_set_vbus_vset(VBUS_VSET_5V);
	ret |= hi6523_set_otg_current(BOOST_LIM_1000);
	ret |= hi6523_set_otg_enable(OTG_DISABLE);
	ret |= hi6523_apple_adapter_detect(APPLE_DETECT_DISABLE);
	return ret;
}

/**********************************************************
*  Function:       hi6523_fcp_chip_init
*  Description:    HI6523 chipIC initialization for high voltage adapter
*  Parameters:   NULL
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_fcp_chip_init(void)
{
	int ret = 0;
	struct hi6523_device_info *di = g_hi6523_dev;
	if (NULL == di) {
		SCHARGER_ERR("%s hi6523_device_info is NULL!\n", __func__);
		return -ENOMEM;
	}
	ret |= hi6523_set_charge_enable(CHG_DISABLE);
	ret |= hi6523_config_opt_param(VBUS_VSET_9V);
	ret |= hi6523_set_fast_safe_timer(CHG_FASTCHG_TIMER_20H);
	ret |= hi6523_set_term_enable(CHG_TERM_DIS);
	ret |= hi6523_set_input_current(CHG_ILIMIT_2000);
	ret |= hi6523_set_charge_current(CHG_FAST_ICHG_2000MA);
	ret |= hi6523_set_terminal_voltage(CHG_FAST_VCHG_4350);
	ret |= hi6523_set_terminal_current(CHG_TERM_ICHG_150MA);
	ret |= hi6523_set_watchdog_timer(WATCHDOG_TIMER_40_S);
	ret |= hi6523_set_precharge_current(CHG_PRG_ICHG_200MA);
	ret |= hi6523_set_precharge_voltage(CHG_PRG_VCHG_2800);
	ret |= hi6523_set_batfet_ctrl(CHG_BATFET_EN);
	ret |= hi6523_set_bat_comp(di->param_dts.bat_comp);
	ret |= hi6523_set_vclamp(di->param_dts.vclamp);
	ret |= hi6523_set_otg_current(BOOST_LIM_1000);
	ret |= hi6523_set_otg_enable(OTG_DISABLE);

	return ret;
}

/**********************************************************
*  Function:       hi6523_fcp_get_adapter_output_current
*  Description:    fcp get the output current from adapter max power and output vol
*  Parameters:     NA
*  return value:  input_current(MA)
**********************************************************/
static int hi6523_fcp_get_adapter_output_current(void)
{

	return 0;
}

/****************************************************************************
  Function:     hi6523_fcp_cmd_transfer_check
  Description:  check cmd transfer success or fail
  Input:         NA
  Output:       NA
  Return:        0: success
                   -1: fail
***************************************************************************/
static int hi6523_fcp_cmd_transfer_check(void)
{
	u8 reg_val1 = 0, reg_val2 = 0;
	int i = 0;
	int ret = 0;

	/*read accp interrupt registers until value is not zero */
	do {
		ret |= hi6523_read_byte(CHG_FCP_ISR1_REG, &reg_val1);
		ret |= hi6523_read_byte(CHG_FCP_ISR2_REG, &reg_val2);
		if (ret) {
			SCHARGER_ERR("%s : reg read failed!\n", __func__);
			continue;
		}
		if (reg_val1 || reg_val2) {
			if ((reg_val1 & CHG_FCP_ACK)
			    && (reg_val1 & CHG_FCP_CMDCPL)
			    && !(reg_val1 & CHG_FCP_CRCPAR)
			    && !(reg_val2 & (CHG_FCP_CRCRX | CHG_FCP_PARRX))) {
				SCHARGER_INF
				    ("%s : FCP_TRANSFER_SUCC, ISR1=0x%x,ISR2=0x%x\n",
				     __func__, reg_val1, reg_val2);
				return 0;
			} else {
				SCHARGER_INF
				    ("%s : FCP_TRANSFER_FAIL, ISR1=0x%x,ISR2=0x%x\n",
				     __func__, reg_val1, reg_val2);
				return -1;
			}
		}

		msleep(10);
		i++;
	} while (i < 50);

	SCHARGER_INF("%s : fcp adapter transfer time out,total time %d ms\n",
		     __func__, i * 10);
	return -1;
}

/****************************************************************************
  Function:     hi6523_fcp_adapter_reg_read
  Description:  read adapter register
  Input:        reg:register's num
                val:the value of register
  Output:       NA
  Return:       0: success
                others: fail
***************************************************************************/
static int hi6523_fcp_adapter_reg_read(u8 * val, u8 reg)
{
	int ret = 0;
	u8 reg_val1 = 0, reg_val2 = 0;
	/*before send cmd, clear accp interrupt registers */
	ret |= hi6523_read_byte(CHG_FCP_ISR1_REG, &reg_val1);
	ret |= hi6523_read_byte(CHG_FCP_ISR2_REG, &reg_val2);
	if (reg_val1 != 0) {
		ret |= hi6523_write_byte(CHG_FCP_ISR1_REG, reg_val1);
	}
	if (reg_val2 != 0) {
		ret |= hi6523_write_byte(CHG_FCP_ISR2_REG, reg_val2);
	}

	ret |= hi6523_write_byte(CHG_FCP_CMD_REG, CHG_FCP_CMD_SBRRD);
	ret |= hi6523_write_byte(CHG_FCP_ADDR_REG, reg);
	ret |=
	    hi6523_write_mask(CHG_FCP_CTRL_REG, CHG_FCP_SNDCMD_MSK,
			      CHG_FCP_SNDCMD_SHIFT, CHG_FCP_EN);

	if (ret) {
		SCHARGER_ERR("%s: write error ret is %d \n", __func__, ret);
		return -1;
	}

	/* check cmd transfer success or fail */
	if (0 == hi6523_fcp_cmd_transfer_check()) {
		/* recived data from adapter */
		ret |= hi6523_read_byte(CHG_FCP_RDATA_REG, val);
	} else {
		SCHARGER_ERR("%s : fcp cmd transter check fail! \n", __func__);
		return -1;
	}

	return ret;
}

/****************************************************************************
  Function:     hi6523_fcp_adapter_reg_write
  Description:  write value into the adapter register
  Input:        reg:register's num
                val:the value of register
  Output:       NA
  Return:        0: success
                -1: fail
***************************************************************************/
static int hi6523_fcp_adapter_reg_write(u8 val, u8 reg)
{
	int ret = 0;
	u8 reg_val1 = 0, reg_val2 = 0;
	/*before send cmd, clear accp interrupt registers */
	ret |= hi6523_read_byte(CHG_FCP_ISR1_REG, &reg_val1);
	ret |= hi6523_read_byte(CHG_FCP_ISR2_REG, &reg_val2);
	if (reg_val1 != 0) {
		ret |= hi6523_write_byte(CHG_FCP_ISR1_REG, reg_val1);
	}
	if (reg_val2 != 0) {
		ret |= hi6523_write_byte(CHG_FCP_ISR2_REG, reg_val2);
	}
	ret |= hi6523_write_byte(CHG_FCP_CMD_REG, CHG_FCP_CMD_SBRWR);
	ret |= hi6523_write_byte(CHG_FCP_ADDR_REG, reg);
	ret |= hi6523_write_byte(CHG_FCP_WDATA_REG, val);
	ret |=
	    hi6523_write_mask(CHG_FCP_CTRL_REG, CHG_FCP_SNDCMD_MSK,
			      CHG_FCP_SNDCMD_SHIFT, CHG_FCP_EN);

	if (ret) {
		SCHARGER_ERR("%s: write error ret is %d \n", __func__, ret);
		return -1;
	}

	/* check cmd transfer success or fail */
	if (0 != hi6523_fcp_cmd_transfer_check()) {
		SCHARGER_ERR("%s: fcp cmd transter check fail! \n", __func__);
		return -1;
	}

	return ret;
}

/****************************************************************************
  Function:     hi6523_fcp_get_adapter_output_vol
  Description:  get fcp output vol
  Input:        NA.
  Output:       fcp output vol(5V/9V/12V)*10
  Return:        0: success
                -1: fail
***************************************************************************/
static int hi6523_fcp_get_adapter_output_vol(u8 * vol)
{
	u8 num = 0;
	u8 output_vol = 0;
	int ret = 0;

	/*get adapter vol list number,exclude 5V */
	ret |=
	    hi6523_fcp_adapter_reg_read(&num,
					CHG_FCP_SLAVE_DISCRETE_CAPABILITIES);
	/*currently,fcp only support three out vol config(5v/9v/12v) */
	if (ret || num > 2) {
		SCHARGER_ERR("%s: vout list support err, reg[0x21] = %u.\n",
			     __func__, num);
		return -1;
	}

	/*get max out vol value */
	ret |=
	    hi6523_fcp_adapter_reg_read(&output_vol,
					CHG_FCP_SLAVE_REG_DISCRETE_OUT_V(num));
	if (ret) {
		SCHARGER_ERR
		    ("%s: get max out vol value failed ,ouputvol=%u,num=%u.\n",
		     __func__, output_vol, num);
		return -1;
	}
	*vol = output_vol;
	SCHARGER_INF("%s: get adapter max out vol = %u,num= %u.\n", __func__,
		     output_vol, num);
	return 0;
}

/****************************************************************************
  Function:     hi6523_fcp_adapter_vol_check
  Description:  check adapter voltage is around expected voltage
  Input:        adapter_vol_mv : expected adapter vol mv
  Output:       NA
  Return:        0: success
                -1: fail
***************************************************************************/
static int hi6523_fcp_adapter_vol_check(int adapter_vol_mv)
{
	int i = 0, ret = 0;
	int adc_vol = 0;
	if ((adapter_vol_mv < FCP_ADAPTER_MIN_VOL)
	    || (adapter_vol_mv > FCP_ADAPTER_MAX_VOL)) {
		SCHARGER_ERR("%s: check vol out of range, input vol = %dmV\n",
			     __func__, adapter_vol_mv);
		return -1;
	}

	for (i = 0; i < FCP_ADAPTER_VOL_CHECK_TIMEOUT; i++) {
		ret |= hi6523_get_vbus_mv(&adc_vol);
		if (ret) {
			continue;
		}
		if ((adc_vol > (adapter_vol_mv - FCP_ADAPTER_VOL_CHECK_ERROR))
		    && (adc_vol <
			(adapter_vol_mv + FCP_ADAPTER_VOL_CHECK_ERROR))) {
			break;
		}
		msleep(FCP_ADAPTER_VOL_CHECK_POLLTIME);
	}

	if (i == FCP_ADAPTER_VOL_CHECK_TIMEOUT) {
		SCHARGER_ERR("%s: check vol timeout, input vol = %dmV\n",
			     __func__, adapter_vol_mv);
		return -1;
	}
	SCHARGER_INF("%s: check vol success, input vol = %dmV, spent %dms\n",
		     __func__, adapter_vol_mv,
		     i * FCP_ADAPTER_VOL_CHECK_POLLTIME);
	return 0;
}

/****************************************************************************
  Function:     hi6523_fcp_set_adapter_output_vol
  Description:  set fcp adapter output vol
  Input:        NA
  Output:       NA
  Return:        0: success
                -1: fail
***************************************************************************/
static int hi6523_fcp_set_adapter_output_vol(int *output_vol)
{
	u8 val = 0;
	u8 vol = 0;
	int ret = 0;

	/*read ID OUTI , for identify huawei adapter */
	ret = hi6523_fcp_adapter_reg_read(&val, CHG_FCP_SLAVE_ID_OUT0);
	if (ret != 0) {
		SCHARGER_ERR("%s: adapter ID OUTI read failed, ret is %d \n",
			     __func__, ret);
		return -1;
	}
	SCHARGER_INF("%s: id out reg[0x4] = %u.\n", __func__, val);

	/*get adapter max output vol value */
	ret = hi6523_fcp_get_adapter_output_vol(&vol);
	if (ret) {
		SCHARGER_ERR("%s: fcp get adapter output vol err.\n", __func__);
		return -1;
	}

	if (vol > CHG_FCP_OUTPUT_VOL_12V * CHG_FCP_VOL_STEP) {
		vol = CHG_FCP_OUTPUT_VOL_12V * CHG_FCP_VOL_STEP;
	}
	*output_vol = vol / CHG_FCP_VOL_STEP;

	/*retry if write fail */
	ret |= hi6523_fcp_adapter_reg_write(vol, CHG_FCP_SLAVE_VOUT_CONFIG);
	ret |= hi6523_fcp_adapter_reg_read(&val, CHG_FCP_SLAVE_VOUT_CONFIG);
	SCHARGER_INF("%s: vout config reg[0x2c] = %u.\n", __func__, val);
	if (ret || val != vol) {
		SCHARGER_ERR("%s:out vol config err, reg[0x2c] = %u,vol :%d.\n",
			     __func__, val, vol);
		return -1;
	}

	ret |=
	    hi6523_fcp_adapter_reg_write(CHG_FCP_SLAVE_SET_VOUT,
					 CHG_FCP_SLAVE_OUTPUT_CONTROL);
	if (ret) {
		SCHARGER_ERR("%s : enable adapter output voltage failed \n ",
			     __func__);
		return -1;
	}

	ret |= hi6523_fcp_adapter_vol_check(vol / CHG_FCP_VOL_STEP * 1000);
	if (ret) {
		SCHARGER_ERR("%s : adc check adapter output voltage failed \n ",
			     __func__);
		return -1;
	}

	SCHARGER_INF("fcp adapter output vol set ok.\n");
	return 0;
}

/****************************************************************************
  Function:     hi6523_config_uvp_fvp
  Description:  hi6523 config uvp fvp
  Input:        NA
  Output:       NA
  Return:        0: success
                -1: fail
***************************************************************************/
static int hi6523_set_uvp_ovp(void)
{
	int ret = 0;

	ret |=
	    hi6523_write_mask(CHG_UVP_OVP_VOLTAGE_REG, CHG_UVP_OVP_VOLTAGE_MSK,
			      CHG_UVP_OVP_VOLTAGE_SHIFT,
			      CHG_UVP_OVP_VOLTAGE_MAX);

	if (ret) {
		SCHARGER_ERR("%s:uvp&ovp voltage set failed, ret = %d.\n",
			     __func__, ret);
		return -1;
	}

	return ret;
}

/****************************************************************************
  Function:     hi6523_fcp_switch_to_soc
  Description:  switch_to_master
  Input:        NA
  Output:       NA
  Return:        0: success
             other: fail
***************************************************************************/
static int hi6523_fcp_switch_to_soc(void)
{
	SCHARGER_INF("%s\n", __func__);
#ifdef CONFIG_SWITCH_FSA9685
	fsa9685_manual_sw(FSA9685_USB1_ID_TO_IDBYPASS);
#endif
	return 0;
}

/****************************************************************************
  Function:     hi6523_fcp_switch_to_master
  Description:  switch_to_master
  Input:        NA
  Output:       NA
  Return:        0: success
             other: fail
***************************************************************************/
static int hi6523_fcp_switch_to_master(void)
{
	SCHARGER_INF("%s\n", __func__);
#ifdef CONFIG_SWITCH_FSA9685
	fsa9685_manual_sw(FSA9685_USB2_ID_TO_IDBYPASS);
#endif
	return 0;
}

/****************************************************************************
  Function:     hi6523_fcp_adapter_detect
  Description:  detect fcp adapter
  Input:        NA
  Output:       NA
  Return:        0: success
                -1: other fail
                1:fcp adapter but detect fail
***************************************************************************/
static int hi6523_fcp_adapter_detect(void)
{
	u8 reg_val1 = 0;
	u8 reg_val2 = 0;
	int i = 0;
	int ret = 0;

	mutex_lock(&hi6523_fcp_detect_lock);
	ret |= hi6523_read_byte(CHG_FCP_SET_STATUS_REG, &reg_val1);
	ret |= hi6523_read_byte(CHG_FCP_STATUS_REG, &reg_val2);
	if (ret) {
		SCHARGER_ERR("%s:read det attach err,ret:%d.\n", __func__, ret);
		mutex_unlock(&hi6523_fcp_detect_lock);
		return -1;
	}

	if ((reg_val1 & CHG_FCP_SET_STATUS_MSK)
	    && (CHG_FCP_SLAVE_GOOD ==
		(reg_val2 & (CHG_FCP_DVC_MSK | CHG_FCP_ATTATCH_MSK)))) {
		mutex_unlock(&hi6523_fcp_detect_lock);
		SCHARGER_INF("fcp adapter detect ok.\n");
		return CHG_FCP_ADAPTER_DETECT_SUCC;
	}

	ret |=
	    hi6523_write_mask(CHG_FCP_DET_CTRL_REG, CHG_FCP_DET_EN_MSK,
			      CHG_FCP_DET_EN_SHIFT, TRUE);
	ret |= hi6523_fcp_switch_to_master();
	ret |=
	    hi6523_write_mask(CHG_FCP_DET_CTRL_REG, CHG_FCP_CMP_EN_MSK,
			      CHG_FCP_CMP_EN_SHIFT, TRUE);
	if (ret) {
		SCHARGER_ERR("%s:FCP enable detect fail,ret:%d.\n", __func__,
			     ret);
		hi6523_write_mask(CHG_FCP_DET_CTRL_REG, CHG_FCP_CMP_EN_MSK,
				  CHG_FCP_CMP_EN_SHIFT, FALSE);
		hi6523_fcp_switch_to_soc();
		hi6523_write_mask(CHG_FCP_DET_CTRL_REG, CHG_FCP_DET_EN_MSK,
				  CHG_FCP_DET_EN_SHIFT, FALSE);
		mutex_unlock(&hi6523_fcp_detect_lock);
		return -1;
	}
	/* wait for fcp_set */
	for (i = 0; i < CHG_FCP_DETECT_MAX_COUT; i++) {
		ret |= hi6523_read_byte(CHG_FCP_SET_STATUS_REG, &reg_val1);
		if (ret) {
			SCHARGER_ERR("%s:read det attach err,ret:%d.\n",
				     __func__, ret);
			continue;
		}
		if (reg_val1 & CHG_FCP_SET_STATUS_MSK) {
			break;
		}
		msleep(CHG_FCP_POLL_TIME);
	}
	if (CHG_FCP_DETECT_MAX_COUT == i) {
		hi6523_write_mask(CHG_FCP_DET_CTRL_REG, CHG_FCP_CMP_EN_MSK,
				  CHG_FCP_CMP_EN_SHIFT, FALSE);
		hi6523_fcp_switch_to_soc();
		hi6523_write_mask(CHG_FCP_DET_CTRL_REG, CHG_FCP_DET_EN_MSK,
				  CHG_FCP_DET_EN_SHIFT, FALSE);
		mutex_unlock(&hi6523_fcp_detect_lock);
		return CHG_FCP_ADAPTER_DETECT_OTHER;
	}

	/* enable fcp_en */
	hi6523_write_mask(CHG_FCP_CTRL_REG, CHG_FCP_EN_MSK, CHG_FCP_EN_SHIFT,
			  TRUE);

	/*detect hisi fcp charger, wait for ping succ */
	for (i = 0; i < CHG_FCP_DETECT_MAX_COUT; i++) {
		ret |= hi6523_read_byte(CHG_FCP_STATUS_REG, &reg_val2);
		if (ret) {
			SCHARGER_ERR("%s:read det attach err,ret:%d.\n",
				     __func__, ret);
			continue;
		}

		if ((CHG_FCP_SLAVE_GOOD ==
		     (reg_val2 & (CHG_FCP_DVC_MSK | CHG_FCP_ATTATCH_MSK)))) {
			break;
		}
		msleep(CHG_FCP_POLL_TIME);
	}

	if (CHG_FCP_DETECT_MAX_COUT == i) {
		hi6523_write_mask(CHG_FCP_CTRL_REG, CHG_FCP_EN_MSK,
				  CHG_FCP_EN_SHIFT, FALSE);
		hi6523_write_mask(CHG_FCP_DET_CTRL_REG, CHG_FCP_CMP_EN_MSK,
				  CHG_FCP_CMP_EN_SHIFT, FALSE);
		hi6523_fcp_switch_to_soc();
		hi6523_write_mask(CHG_FCP_DET_CTRL_REG, CHG_FCP_DET_EN_MSK,
				  CHG_FCP_DET_EN_SHIFT, FALSE);
		SCHARGER_ERR("fcp adapter detect failed,reg[0x%x]=0x%x\n",
			     CHG_FCP_STATUS_REG, reg_val2);
		mutex_unlock(&hi6523_fcp_detect_lock);
		return CHG_FCP_ADAPTER_DETECT_FAIL;	/*not fcp adapter */

	}
	SCHARGER_INF("fcp adapter detect ok\n");
	mutex_unlock(&hi6523_fcp_detect_lock);
	return CHG_FCP_ADAPTER_DETECT_SUCC;

}

/****************************************************************************
  Function:     hi6523_is_support_fcp
  Description:  check_if_support_fcp
  Input:        NA
  Output:       NA
  Return:        0: success
             other: fail
***************************************************************************/
static int hi6523_is_support_fcp(void)
{
	struct hi6523_device_info *di = g_hi6523_dev;
	if (NULL == di) {
		SCHARGER_ERR("%s hi6523_device_info is NULL!\n", __func__);
		return -ENOMEM;
	}
	if (0 != di->param_dts.fcp_support) {
		SCHARGER_INF("support fcp charge \n");
		return 0;
	} else {
		return 1;
	}
}

/****************************************************************************
  Function:     hi6523_fcp_master_reset
  Description:  reset master
  Input:        NA
  Output:       NA
  Return:        0: success
             other: fail
***************************************************************************/
static int hi6523_fcp_master_reset(void)
{
	int ret = 0;
	ret |= hi6523_write_byte(CHG_FCP_SOFT_RST_REG, CHG_FCP_SOFT_RST_VAL);
	ret |= hi6523_write_byte(CHG_FCP_CTRL_REG, 0);	//clear fcp_en and fcp_master_rst
	return ret;
}

/****************************************************************************
  Function:     hi6523_fcp_adapter_reset
  Description:  reset adapter
  Input:        NA
  Output:       NA
  Return:        0: success
             other: fail
***************************************************************************/
static int hi6523_fcp_adapter_reset(void)
{
	int ret = 0;
	ret |= hi6523_set_vbus_vset(VBUS_VSET_5V);
	ret |=
	    hi6523_write_byte(CHG_FCP_CTRL_REG,
			      CHG_FCP_EN_MSK | CHG_FCP_MSTR_RST_MSK);
	if (ret) {
		SCHARGER_ERR("%s : send rst cmd failed \n ", __func__);
		return ret;
	}

	ret |= hi6523_fcp_adapter_vol_check(FCP_ADAPTER_RST_VOL);
	if (ret) {
		ret |= hi6523_write_byte(CHG_FCP_CTRL_REG, 0);	//clear fcp_en and fcp_master_rst
		SCHARGER_ERR("%s : adc check adapter output voltage failed \n ",
			     __func__);
		return ret;
	}

	ret |= hi6523_write_byte(CHG_FCP_CTRL_REG, 0);	//clear fcp_en and fcp_master_rst
	ret |= hi6523_config_opt_param(VBUS_VSET_5V);
	return ret;
}

/**********************************************************
*  Function:       hi6523_stop_charge_config
*  Description:    config chip after stop charging
*  Parameters:     NULL
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_stop_charge_config(void)
{
	int ret = 0;
	ret |= hi6523_set_vbus_vset(VBUS_VSET_5V);

	return ret;
}

/**********************************************************
*  Function:       hi6523_fcp_stop_charge_config
*  Description:    fcp config chip after stop charging
*  Parameters:     NULL
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_fcp_stop_charge_config(void)
{
	SCHARGER_INF("hi6523_fcp_master_reset");
	hi6523_fcp_master_reset();
	hi6523_apple_adapter_detect(APPLE_DETECT_ENABLE);
	if(!switch_id_flag)/*when charge stop it not need change*/
	{
		hi6523_fcp_switch_to_soc();
	}
	return 0;
}

struct fcp_adapter_device_ops fcp_hi6523_ops = {
	.get_adapter_output_current = hi6523_fcp_get_adapter_output_current,
	.set_adapter_output_vol = hi6523_fcp_set_adapter_output_vol,
	.detect_adapter = hi6523_fcp_adapter_detect,
	.is_support_fcp = hi6523_is_support_fcp,
	.switch_chip_reset = hi6523_fcp_master_reset,
	.fcp_adapter_reset = hi6523_fcp_adapter_reset,
	.stop_charge_config = hi6523_fcp_stop_charge_config,
};

struct charge_device_ops hi6523_ops = {
	.chip_init = hi6523_chip_init,
	.fcp_chip_init = hi6523_fcp_chip_init,
	.dev_check = hi6523_device_check,
	.set_input_current = hi6523_set_input_current,
	.set_charge_current = hi6523_set_charge_current,
	.set_terminal_voltage = hi6523_set_terminal_voltage,
	.set_dpm_voltage = hi6523_set_dpm_voltage,
	.set_terminal_current = hi6523_set_terminal_current,
	.set_charge_enable = hi6523_set_charge_enable,
	.set_otg_enable = hi6523_set_otg_enable,
	.set_term_enable = hi6523_set_term_enable,
	.get_charge_state = hi6523_get_charge_state,
	.reset_watchdog_timer = hi6523_reset_watchdog_timer,
	.dump_register = hi6523_dump_register,
	.get_register_head = hi6523_get_register_head,
	.set_watchdog_timer = hi6523_set_watchdog_timer,
	.set_batfet_disable = hi6523_set_batfet_disable,
	.get_ibus = hi6523_get_ibus_ma,
	.get_vbus = hi6523_get_vbus_mv,
	.get_vbat_sys = hi6523_get_vbat_sys,
	.set_charger_hiz = hi6523_set_charger_hiz,
	.check_input_dpm_state = hi6523_check_input_dpm_state,
	.set_otg_current = hi6523_set_otg_current,
	.stop_charge_config = hi6523_stop_charge_config,
	.set_vbus_vset = hi6523_set_vbus_vset,
	.set_uvp_ovp = hi6523_set_uvp_ovp,
	.soft_vbatt_ovp_protect = hi6523_soft_vbatt_ovp_protect,
};

/**********************************************************
*  Function:       hi6523_plugout_check_process
*  Description:    schedule or cancel check work based on charger type
*                  USB/NON_STD/BC_USB: schedule work
*                  REMOVED: cancel work
*  Parameters:     type: charger type
*  return value:   NULL
**********************************************************/
static void hi6523_plugout_check_process(enum hisi_charger_type type)
{
	struct hi6523_device_info *di = g_hi6523_dev;

	if (NULL == di)
		return;
	switch (type) {
	case CHARGER_TYPE_SDP:
	case CHARGER_TYPE_DCP:
	case CHARGER_TYPE_CDP:
	case CHARGER_TYPE_UNKNOWN:
		schedule_delayed_work(&di->plugout_check_work,
				      msecs_to_jiffies(0));
		break;
	case CHARGER_TYPE_NONE:
		cancel_delayed_work_sync(&di->plugout_check_work);
		g_vbat_check_cycle = 0;
		g_batt_ovp_cnt_1s = 0;
		g_batt_ovp_cnt_30s = 0;
		break;
	default:
		break;
	}
}

/**********************************************************
*  Function:       hi6523_usb_notifier_call
*  Description:    respond the charger_type events from USB PHY
*  Parameters:   usb_nb:usb notifier_block
*                      event:charger type event name
*                      data:unused
*  return value:  NOTIFY_OK-success or others
**********************************************************/
static int hi6523_usb_notifier_call(struct notifier_block *usb_nb,
				    unsigned long event, void *data)
{
	struct hi6523_device_info *di = g_hi6523_dev;

	di->charger_type = (enum hisi_charger_type)event;
	hi6523_plugout_check_process(di->charger_type);
	return NOTIFY_OK;
}

/**********************************************************
*  Function:       hi6523_plugout_check_work
*  Description:    handler for chargerIC plugout detect failure check
*  Parameters:     work: hi6523 plugout check workqueue
*  return value:   NULL
**********************************************************/
static void hi6523_plugout_check_work(struct work_struct *work)
{
	int ibus;
	int vbatt_mv;
	int vbus = 0;
	int ret;
	struct hi6523_device_info *di = g_hi6523_dev;

	if (NULL == di)
		return;
	vbatt_mv = hisi_battery_voltage();
	g_vbat_check_cycle++;
	if (0 == (g_vbat_check_cycle % CHG_VBATT_CHK_CNT)) {
		g_vbat_check_cycle = 0;
		if (vbatt_mv >= MIN(CHG_VBATT_SOFT_OVP_MAX, CHG_VBATT_CV_103(di->term_vol_mv))) {
			g_batt_ovp_cnt_1s++;
			if (CHG_VBATT_SOFT_OVP_CNT <= g_batt_ovp_cnt_1s) {
				hi6523_set_charger_hiz(TRUE);
				SCHARGER_ERR("%s:vbat:%d,cv_mv:%d,ovp_cnt:%d,shutdown buck.\n",
					__func__, vbatt_mv, di->term_vol_mv, g_batt_ovp_cnt_1s);
				g_batt_ovp_cnt_1s = 0;
				}
		} else
			g_batt_ovp_cnt_1s = 0;
	}
	if (!((TRUE == hi6523_get_anti_reverbst_enabled()) && (vbatt_mv < CHG_DPM_VOL_4000_MV))) {
		ret = hi6523_get_vbus_mv(&vbus);
		if (0 == ret) {
			if (TRUE == hi6523_vbus_in_dpm(vbus)) {
				ibus = hi6523_get_ibus_ma();
				if ((ibus < plugout_check_ibus_ma) && FALSE == hi6523_is_charger_hiz()) {
					hi6523_set_charger_hiz(TRUE);
					msleep(50);
					hi6523_set_charger_hiz(FALSE);
					SCHARGER_INF("%s:ibus=%dma, vbus=%dmv, vbat=%dmv\n",
						__func__, ibus, vbus, vbatt_mv);
				}
			}
		}
	}
	schedule_delayed_work(&di->plugout_check_work,
			      msecs_to_jiffies(plugout_check_delay_ms));
}

/**********************************************************
*  Function:       hi6523_irq_work
*  Description:    handler for chargerIC fault irq in charging process
*  Parameters:   work:chargerIC fault interrupt workqueue
*  return value:  NULL
**********************************************************/
static void hi6523_irq_work(struct work_struct *work)
{
	struct hi6523_device_info *di =
	    container_of(work, struct hi6523_device_info, irq_work);
	u8 reg0 = 0, reg1 = 0, reg2 = 0,reg_s1 = 0;
	u8 reg_wdt = 0;
	u8 fcp_irq3_reg = 0, fcp_irq4_reg = 0;
	u8 reg_read = 0;
	static u8 otg_scp_cnt;
	static u8 otg_uvp_cnt;
	u8 vbat_ovp_cnt = 0;
	int i = 0;

	hi6523_read_byte(CHG_IRQ0, &reg0);
	hi6523_read_byte(CHG_IRQ1, &reg1);
	hi6523_read_byte(CHG_IRQ2, &reg2);
	hi6523_read_byte(CHG_WDT_IRQ, &reg_wdt);
	hi6523_read_byte(CHG_FCP_IRQ3_REG, &fcp_irq3_reg);
	hi6523_read_byte(CHG_FCP_IRQ4_REG, &fcp_irq4_reg);

	if (reg0) {
		SCHARGER_INF("%s : CHG_IRQ0, 0x%x\n", __func__, reg0);
		if (CHG_OTG_OCP == (reg0 & CHG_OTG_OCP))
			SCHARGER_ERR("%s : CHARGE_FAULT_OTG_OCP\n", __func__);
		if (CHG_OTG_SCP == (reg0 & CHG_OTG_SCP)) {
			otg_scp_cnt++;
			hi6523_write_byte(CHG_IRQ0, CHG_OTG_SCP);
			msleep(600);
			hi6523_read_byte(CHG_STATUS0_REG, &reg_read);
			if ((reg_read & HI6523_CHG_OTG_ON) == HI6523_CHG_OTG_ON)
				otg_scp_cnt = 0;
			if (otg_scp_cnt > 3) {
				otg_scp_cnt = 0;
				SCHARGER_ERR("%s : CHARGE_FAULT_OTG_SCP\n",
					     __func__);
				atomic_notifier_call_chain(&fault_notifier_list,
					   CHARGE_FAULT_BOOST_OCP,
					   NULL);
			}
		}
		if (CHG_OTG_UVP == (reg0 & CHG_OTG_UVP)) {
			otg_uvp_cnt++;
			hi6523_write_byte(CHG_IRQ0, CHG_OTG_UVP);
			msleep(600);
			hi6523_read_byte(CHG_STATUS0_REG, &reg_read);
			if ((reg_read & HI6523_CHG_OTG_ON) == HI6523_CHG_OTG_ON)
				otg_uvp_cnt = 0;
			if (otg_uvp_cnt > 3) {
				otg_uvp_cnt = 0;
				SCHARGER_ERR("%s : CHARGE_FAULT_OTG_UVP\n",
					     __func__);
				atomic_notifier_call_chain(&fault_notifier_list,
					   CHARGE_FAULT_BOOST_OCP,
					   NULL);
			}
		}
	}

	if (reg1) {
		SCHARGER_INF("%s : CHG_IRQ1, 0x%x\n", __func__, reg1);
		if (CHG_VBAT_OVP == (reg1 & CHG_VBAT_OVP)) {
			for (i = 0; i < 5; i++) {
				hi6523_read_byte(CHG_IRQ_STATUS1, &reg_s1);
				if (CHG_VBAT_OVP == (reg_s1 & CHG_VBAT_OVP)) {
					vbat_ovp_cnt++;
					msleep(5);
				} else {
					vbat_ovp_cnt = 0;
					break;
				}
			}
			hi6523_write_byte(CHG_IRQ1, CHG_VBAT_OVP);
			if (vbat_ovp_cnt >= 5) {
				vbat_ovp_cnt = 0;
				SCHARGER_ERR("%s : CHARGE_FAULT_VBAT_OVP\n",
					     __func__);
				atomic_notifier_call_chain(&fault_notifier_list,
					   CHARGE_FAULT_VBAT_OVP,
					   NULL);
			}
		}
	}

	if (reg2) {
		SCHARGER_INF("%s : CHG_IRQ2, 0x%x\n", __func__, reg2);
	}

	if (reg_wdt) {
		SCHARGER_INF("%s : CHG_WDT_IRQ, 0x%x\n", __func__, reg_wdt);
	}

	if (fcp_irq3_reg) {
		SCHARGER_INF("%s : CHG_FCP_IRQ3_REG, 0x%x\n", __func__,
			     fcp_irq3_reg);
	}

	if (fcp_irq4_reg) {
		SCHARGER_INF("%s : CHG_FCP_IRQ4_REG, 0x%x\n", __func__,
			     fcp_irq4_reg);
	}

	hi6523_write_byte(CHG_IRQ0, reg0);
	hi6523_write_byte(CHG_IRQ1, reg1);
	hi6523_write_byte(CHG_IRQ2, reg2);
	hi6523_write_byte(CHG_WDT_IRQ, reg_wdt);
	hi6523_write_byte(CHG_FCP_IRQ3_REG, fcp_irq3_reg);
	hi6523_write_byte(CHG_FCP_IRQ4_REG, fcp_irq4_reg);

	enable_irq(di->irq_int);
}

/**********************************************************
*  Function:       hi6523_interrupt
*  Description:    callback function for chargerIC fault irq in charging process
*  Parameters:   irq:chargerIC fault interrupt
*                      _di:hi6523_device_info
*  return value:  IRQ_HANDLED-success or others
**********************************************************/
static irqreturn_t hi6523_interrupt(int irq, void *_di)
{
	struct hi6523_device_info *di = _di;
	disable_irq_nosync(di->irq_int);
	schedule_work(&di->irq_work);
	return IRQ_HANDLED;
}

/**********************************************************
*  Function:       parse_dts
*  Description:    parse_dts
*  Parameters:   device_node:hi6523 device_node
*                      _di:hi6523_device_info
*  return value:  NULL
**********************************************************/
static void parse_dts(struct device_node *np, struct hi6523_device_info *di)
{
	int ret = 0;
	struct device_node *batt_node;
	di->param_dts.bat_comp = 80;
	di->param_dts.vclamp = 224;
	ret = of_property_read_u32(np, "bat_comp", &(di->param_dts.bat_comp));
	if (ret) {
		SCHARGER_ERR("get bat_comp failed\n");
		return;
	}
	SCHARGER_INF("prase_dts bat_comp = %d\n", di->param_dts.bat_comp);

	ret = of_property_read_u32(np, "vclamp", &(di->param_dts.vclamp));
	if (ret) {
		SCHARGER_ERR("get vclamp failed\n");
		return;
	}
	SCHARGER_INF("prase_dts vclamp = %d\n", di->param_dts.vclamp);

	ret =
	    of_property_read_u32(np, "adc_channel_vbat_sys",
				 &adc_channel_vbat_sys);
	if (ret) {
		SCHARGER_INF("get adc_channel_vbat_sys failed!\n");
		adc_channel_vbat_sys = -1;
	}

	ret =
	    of_property_read_u32(np, "fcp_support",
				 &(di->param_dts.fcp_support));
	if (ret) {
		SCHARGER_ERR("get fcp_support failed\n");
		return;
	}
	batt_node =
	    of_find_compatible_node(NULL, NULL, "huawei,hisi_bci_battery");
	if (batt_node) {
		if (of_property_read_u32
		    (batt_node, "battery_board_type", &is_board_type)) {
			SCHARGER_ERR("get battery_board_type fail!\n");
			is_board_type = BAT_BOARD_ASIC;
		}
	} else {
		SCHARGER_ERR("get hisi_bci_battery fail!\n");
		is_board_type = BAT_BOARD_ASIC;
	}
	ret = of_property_read_u32(np, "switch_id_change",
				 &switch_id_flag);
	if (ret) {
		SCHARGER_ERR("get switch id change fail!\n");
		return;
	}
	return;
}

/**********************************************************
*  Function:       hi6523_probe
*  Description:    HI6523 module probe
*  Parameters:   client:i2c_client
*                      id:i2c_device_id
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_probe(struct i2c_client *client,
			const struct i2c_device_id *id)
{
	int ret = 0;
	struct hi6523_device_info *di = NULL;
	struct device_node *np = NULL;
	struct class *power_class = NULL;

	di = devm_kzalloc(&client->dev, sizeof(*di), GFP_KERNEL);
	if (NULL == di) {
		SCHARGER_ERR("%s hi6523_device_info is NULL!\n", __func__);
		return -ENOMEM;
	}
	g_hi6523_dev = di;
	di->dev = &client->dev;
	np = di->dev->of_node;
	di->client = client;
	i2c_set_clientdata(client, di);
	parse_dts(np, di);
	INIT_WORK(&di->irq_work, hi6523_irq_work);
	INIT_DELAYED_WORK(&di->plugout_check_work, hi6523_plugout_check_work);
	hi6523_write_byte(0x3B, 0xff);	// disable FCP_IRQ1
	hi6523_write_byte(0x3C, 0xff);	// disable FCP_IRQ2
	hi6523_write_byte(0x42, 0x03);	// disable FCP_IRQ5
	di->gpio_int = of_get_named_gpio(np, "gpio_int", 0);
	if (!gpio_is_valid(di->gpio_int)) {
		SCHARGER_ERR("gpio_int is not valid\n");
		ret = -EINVAL;
		goto hi6523_fail_0;
	}

	ret = gpio_request(di->gpio_int, "charger_int");
	if (ret) {
		SCHARGER_ERR("could not request gpio_int\n");
		goto hi6523_fail_1;
	}
	gpio_direction_input(di->gpio_int);
	di->irq_int = gpio_to_irq(di->gpio_int);
	if (di->irq_int < 0) {
		SCHARGER_ERR("could not map gpio_int to irq\n");
		goto hi6523_fail_2;
	}
	ret = request_irq(di->irq_int, hi6523_interrupt,
			IRQF_TRIGGER_FALLING, "charger_int_irq", di);
	if (ret) {
		SCHARGER_ERR("could not request irq_int\n");
		di->irq_int = -1;
		goto hi6523_fail_3;
	}
	di->charger_type = hisi_get_charger_type();
	di->usb_nb.notifier_call = hi6523_usb_notifier_call;
	ret = hisi_charger_type_notifier_register(&di->usb_nb);
	if (ret < 0) {
		SCHARGER_ERR("hisi_charger_type_notifier_register failed\n");
		goto hi6523_fail_3;
	}
	di->term_vol_mv = hi6523_get_terminal_voltage();
	hi6523_apple_adapter_detect(APPLE_DETECT_ENABLE);/*enable scharger apple detect*/
	mutex_init(&hi6523_fcp_detect_lock);
	mutex_init(&hi6523_adc_conv_lock);
	ret = charge_ops_register(&hi6523_ops);
	if (ret) {
		SCHARGER_ERR("register charge ops failed!\n");
		goto hi6523_fail_3;
	}

	/* if support fcp ,register fcp adapter ops */
	if (0 == hi6523_is_support_fcp()) {
		ret = fcp_adapter_ops_register(&fcp_hi6523_ops);
		if (ret)
			SCHARGER_ERR("register fcp adapter ops failed!\n");
		else
			SCHARGER_INF(" fcp adapter ops register success!\n");
	}
	ret = hi6523_sysfs_create_group(di);
	if (ret) {
		SCHARGER_ERR("create sysfs entries failed!\n");
		goto hi6523_fail_4;
	}
	power_class = hw_power_get_class();
	if (power_class) {
		if (charge_dev == NULL) {
			charge_dev =
			    device_create(power_class, NULL, 0, NULL,
					  "charger");
			if (IS_ERR(charge_dev)) {
				charge_dev = NULL;
				SCHARGER_ERR("create charge_dev failed!\n");
				goto hi6523_fail_4;
			}
		}
		ret =
		    sysfs_create_link(&charge_dev->kobj, &di->dev->kobj,
				      "HI6523");
		if (ret)
			SCHARGER_ERR("create link to HI6523 fail.\n");
	}
	hi6523_read_byte(CHG_VERSION_REG5, &hi6523_version);
	SCHARGER_INF("%s : hi6523_version_5 is 0x%x\n", __func__,
		     hi6523_version);
	hi6523_plugout_check_process(di->charger_type);
	SCHARGER_INF("HI6523 probe ok!\n");
	return 0;

hi6523_fail_4:
	hi6523_sysfs_remove_group(di);
hi6523_fail_3:
	free_irq(di->irq_int, di);
hi6523_fail_2:
	gpio_free(di->gpio_int);
hi6523_fail_1:
hi6523_fail_0:
	g_hi6523_dev = NULL;
	np = NULL;

	return ret;
}

/**********************************************************
*  Function:       hi6523_remove
*  Description:    HI6523 module remove
*  Parameters:   client:i2c_client
*  return value:  0-success or others-fail
**********************************************************/
static int hi6523_remove(struct i2c_client *client)
{
	struct hi6523_device_info *di = i2c_get_clientdata(client);
	if (NULL == di)
		return -1;

	hi6523_sysfs_remove_group(di);

	if (di->irq_int) {
		free_irq(di->irq_int, di);
	}
	if (di->gpio_int) {
		gpio_free(di->gpio_int);
	}
	g_hi6523_dev = NULL;
	return 0;
}

MODULE_DEVICE_TABLE(i2c, HI6523);
static struct of_device_id hi6523_of_match[] = {
	{
	 .compatible = "huawei,hi6523_charger",
	 .data = NULL,
	 },
	{
	 },
};

static const struct i2c_device_id hi6523_i2c_id[] =
    { {"hi6523_charger", 0}, {} };

static struct i2c_driver hi6523_driver = {
	.probe = hi6523_probe,
	.remove = hi6523_remove,
	.id_table = hi6523_i2c_id,
	.driver = {
		   .owner = THIS_MODULE,
		   .name = "hi6523_charger",
		   .of_match_table = of_match_ptr(hi6523_of_match),
		   },
};

/**********************************************************
*  Function:       hi6523_init
*  Description:    HI6523 module initialization
*  Parameters:   NULL
*  return value:  0-success or others-fail
**********************************************************/
static int __init hi6523_init(void)
{
	int ret = 0;

	ret = i2c_add_driver(&hi6523_driver);
	if (ret)
		SCHARGER_ERR("%s: i2c_add_driver error!!!\n", __func__);

	return ret;
}

/**********************************************************
*  Function:       hi6523_exit
*  Description:    HI6523 module exit
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void __exit hi6523_exit(void)
{
	i2c_del_driver(&hi6523_driver);
}

module_init(hi6523_init);
module_exit(hi6523_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("HI6523 charger module driver");
MODULE_AUTHOR("HW Inc");
