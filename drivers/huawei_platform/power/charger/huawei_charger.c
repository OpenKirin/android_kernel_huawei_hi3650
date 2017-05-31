/*
 * drivers/power/huawei_charger.c
 *
 *huawei charger driver
 *
 * Copyright (C) 2012-2015 HUAWEI, Inc.
 * Author: HUAWEI, Inc.
 *
 * This package is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/hrtimer.h>
#include <linux/wakelock.h>
#include <linux/usb/otg.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/power_supply.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/hisi/usb/hisi_usb.h>
#include <huawei_platform/log/hw_log.h>
#include <huawei_platform/usb/switch/switch_usb_class.h>
#include <linux/delay.h>

#ifdef CONFIG_TCPC_CLASS
#include <huawei_platform/usb/pd/richtek/tcpm.h>
#endif

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif

#include <linux/raid/pq.h>
#if defined CONFIG_HUAWEI_DSM
#include <dsm/dsm_pub.h>
#endif
#include <linux/power/hisi/hisi_bci_battery.h>
#include <huawei_platform/power/huawei_charger.h>
#include <huawei_platform/power/vbat_ovp.h>
#include <linux/power/hisi/coul/hisi_coul_drv.h>
#include <charging_core.h>
#ifdef CONFIG_SWITCH_FSA9685
#include <huawei_platform/usb/switch/switch_fsa9685.h>
#endif
#ifdef CONFIG_DIRECT_CHARGER
#include <huawei_platform/power/direct_charger.h>
#endif
#ifdef  CONFIG_HUAWEI_USB_SHORT_CIRCUIT_PROTECT
#include <huawei_platform/power/usb_short_circuit_protect.h>
#endif

#define HWLOG_TAG huawei_charger
HWLOG_REGIST();
BLOCKING_NOTIFIER_HEAD(charge_wake_unlock_list);

static struct wake_lock charge_lock;
static struct wake_lock stop_charge_lock;
static struct wake_lock uscp_plugout_lock;
struct charge_device_ops *g_ops;
struct charge_switch_ops *g_sw_ops;
struct fcp_adapter_device_ops *g_fcp_ops;
static enum fcp_check_stage_type fcp_stage = FCP_STAGE_DEFAUTL;
struct device *charge_dev;
static struct charge_device_info *g_di;
static u32 is_board_type;	/*0:sft 1:udp 2:asic */
static struct mutex charge_wakelock_flag_lock;
static struct work_struct resume_wakelock_work;
static enum charge_wakelock_flag charge_lock_flag = CHARGE_NO_NEED_WAKELOCK;
static bool charge_done_sleep_dts;
static bool ts_flag = FALSE;
static bool otg_flag = FALSE;
static bool cancel_work_flag = FALSE;
static u32 charger_pd_support = 0;
static u32 charger_pd_cur_trans_ratio = 0;

#define REG_NUM 21
struct hisi_charger_bootloader_info {
	bool info_vaild;
	int ibus;
	char reg[REG_NUM];
};
extern char *get_charger_info_p(void);
static struct hisi_charger_bootloader_info hisi_charger_info = { 0 };

#ifdef CONFIG_HISI_CHARGER_SYS_WDG
extern void charge_enable_sys_wdt(void);
extern void charge_stop_sys_wdt(void);
extern void charge_feed_sys_wdt(unsigned int timeout);
#endif

#define CHARGER_BASE_ADDR 512
#define VBUS_REPORT_NUM 4
#define WORK_DELAY_5000MS 5000

static int vbus_flag;
static int output_num;
static int detect_num;
static int switch_status_num;
static int fcp_vbus_lower_count;

static int ico_enable;
static int nonstand_detect_times;
static int usb_continuous_notify_times;

static void fcp_reg_dump(char* pstr);
static void batt_info_dump(char* pstr);
#if defined CONFIG_HUAWEI_DSM
struct charger_dsm {
	int error_no;
	bool notify_enable;
	void (*dump)(char*);
	char buf[ERR_NO_STRING_SIZE];
};
static struct charger_dsm err_count[] = {
	{ERROR_FCP_VOL_OVER_HIGH, true, .dump = fcp_reg_dump, "fcp vbus is high "},
	{ERROR_FCP_DETECT, true, .dump = fcp_reg_dump, "fcp detect fail "},
	{ERROR_FCP_OUTPUT, true, .dump = fcp_reg_dump, "fcp voltage output fail "},
	{ERROR_SWITCH_ATTACH, true, .dump = fcp_reg_dump, "fcp adapter connect fail "},
	{ERROR_ADAPTER_OVLT, true, .dump = fcp_reg_dump, "fcp adapter voltage over high "},
	{ERROR_ADAPTER_OCCURRENT, true, .dump = fcp_reg_dump, "fcp adapter current over high "},
	{ERROR_ADAPTER_OTEMP, true, .dump = fcp_reg_dump, "fcp adapter temp over high "},
	{ERROR_SAFE_PLOICY_LEARN, true, .dump = batt_info_dump, "battery safe ploicy learn"},
	{ERROR_SAFE_PLOICY_LEARN1, true, .dump = batt_info_dump, "safe ploicy learn 1"},
	{ERROR_SAFE_PLOICY_LEARN2, true, .dump = batt_info_dump, "safe ploicy learn 2"},
	{ERROR_SAFE_PLOICY_LEARN3, true, .dump = batt_info_dump, "safe ploicy learn 3"},
	{ERROR_BOOST_OCP, true, NULL, "otg ocp"},
	{ERROR_CHARGE_VBAT_OVP, true, NULL, "vbat ovp"},
};
#endif
/**********************************************************
*  Function:       charge_wake_lock
*  Description:   apply charge wake_lock
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void charge_wake_lock(void)
{
	if (!wake_lock_active(&charge_lock)) {
		wake_lock(&charge_lock);
		hwlog_info("charge wake lock\n");
	}
}
/**********************************************************
*  Function:       uscp_plugout_wake_lock
*  Description:   apply uscp plugout_wake_lock
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void uscp_plugout_wake_lock(void)
{
	if (!wake_lock_active(&uscp_plugout_lock)) {
		wake_lock(&uscp_plugout_lock);
		hwlog_info("uscp_plugout_lock\n");
	}
}
/**********************************************************
*  Function:       uscp_plugout_wake_unlock
*  Description:   apply uscp plugout_wake_unlock
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void uscp_plugout_wake_unlock(void)
{
	if (wake_lock_active(&uscp_plugout_lock)) {
		wake_unlock(&uscp_plugout_lock);
		hwlog_info("uscp_plugout_unlock\n");
	}
}
/**********************************************************
*  Function:       charge_wake_unlock
*  Description:   release charge wake_lock
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void charge_wake_unlock(void)
{
	if (wake_lock_active(&charge_lock)) {
		wake_unlock(&charge_lock);
		hwlog_info("charge wake unlock\n");
	}
}
static void batt_info_dump(char* pstr)
{
	char buf[CHARGE_DMDLOG_SIZE] = {0};

	char* batt_brand = hisi_battery_brand();
	int capacity = hisi_battery_capacity();
	int tbatt = hisi_battery_temperature();
	int rm = hisi_battery_rm();
	int vbatt = hisi_battery_voltage();
	int curr_now = -hisi_battery_current();
	int avg_curr = hisi_battery_current_avg();

	snprintf(buf, sizeof(buf), "battery: %s, capacity = %d, rm = %dmAh, batt_temp = %d, "
		"batt_volt = %dmV, curr_now = %dmA, avg_curr = %dmA\n",
		batt_brand, capacity, rm, tbatt, vbatt, curr_now, avg_curr);
	strncat(pstr,buf,strlen(buf));
}

static void fcp_reg_dump(char* pstr)
{
	struct charge_device_info *di = g_di;

	if (!di || !di->fcp_ops || !di->fcp_ops->reg_dump) {
		hwlog_err("%s ops is null\n", __func__);
	} else {
		di->fcp_ops->reg_dump(pstr);
	}
}
/**********************************************************
*  Function:       dsm_report
*  Description:    dsm report interface
*  Parameters:     err_no buf
*  return value:  0 :succ -1:fail
**********************************************************/
int dsm_report(int err_no, void *buf)
{
#if defined CONFIG_HUAWEI_DSM
	if (NULL == buf || NULL == get_battery_dclient()) {
		hwlog_info("buf is NULL or battery_dclient is NULL!\n");
		return -1;
	}

	if (!dsm_client_ocuppy(get_battery_dclient())) {
		dsm_client_record(get_battery_dclient(), "%s", buf);
		dsm_client_notify(get_battery_dclient(), err_no);
		hwlog_info("charger dsm report err_no:%d\n", err_no);
		return 0;
	}
	hwlog_info("charger dsm is busy!\n");
	return -1;
#endif

	return 0;
}

/**********************************************************
*  Function:       charger_dsm_report
*  Description:    charger dsm report
*  Parameters:   err_no val
*  return value:  0:succ ;-1 :fail
**********************************************************/
int charger_dsm_report(int err_no, int *val)
{
	int ret = -1;
#if defined CONFIG_HUAWEI_DSM
	char dsm_buff[CHARGE_DMDLOG_SIZE] = { 0 };
	char buf[ERR_NO_STRING_SIZE] = { 0 };
	int i;
	int err_count_size = sizeof(err_count)/sizeof(struct charger_dsm);

	for (i = 0; i < err_count_size; i++) {
		if ((err_no == err_count[i].error_no) &&
			(true == err_count[i].notify_enable)) {/*every err_no report one times */
			strncat(dsm_buff, err_count[i].buf, ERR_NO_STRING_SIZE - 1);
			if (val) {  /*need report reg */
				snprintf(buf, sizeof(buf), "val= %d\n", *val);
				strncat(dsm_buff, buf, strlen(buf));
			}
			if (err_count[i].dump)
				err_count[i].dump(dsm_buff);
			if (!dsm_report(err_no, dsm_buff)) {
				/*when it be set 1,it will not report */
				err_count[i].notify_enable = false;
				ret = 0;
				break;
			}
		}
	}
#endif
	return ret;
}

static int dump_bootloader_info(char *reg_value)
{
	char buff[26] = { 0 };
	int i = 0;

	memset(reg_value, 0, CHARGELOG_SIZE);
	snprintf(buff, 26, "%-8.2d", hisi_charger_info.ibus);
	strncat(reg_value, buff, strlen(buff));
	for (i = 0; i < REG_NUM; i++) {
		snprintf(buff, 26, "0x%-8.2x", hisi_charger_info.reg[i]);
		strncat(reg_value, buff, strlen(buff));
	}
	return 0;
}

static int copy_bootloader_charger_info(void)
{
	char *p = NULL;
	p = get_charger_info_p();

	if (NULL == p) {
		hwlog_err("bootloader pointer NULL!\n");
		return -1;
	}

	memcpy(&hisi_charger_info, p + CHARGER_BASE_ADDR,
	       sizeof(hisi_charger_info));
	hwlog_info("bootloader ibus %d\n", hisi_charger_info.ibus);

	return 0;
}

/**********************************************************
*  Function:       fcp_check_switch_status
*  Description:    check switch chip status
*  Parameters:  void
*  return value:  void
**********************************************************/
void fcp_check_switch_status(struct charge_device_info *di)
{
	int val = -1;
	int reg = 0;
	int ret = -1;

	/*check usb is on or not ,if not ,can not detect the switch status */
	if (di->ops->get_charge_state) {
		ret = di->ops->get_charge_state(&reg);
		if (ret) {
			hwlog_info("%s:read PG STAT fail.\n", __func__);
			return;
		}
		if (reg & CHAGRE_STATE_NOT_PG) {
			hwlog_info
			    ("%s:PG NOT GOOD can not check switch status.\n", __func__);
			return;
		}
	}

	if (!di->fcp_ops->fcp_read_switch_status) {
		hwlog_err("di->ops->fcp_read_switch_status is null.\n");
		return;
	}

	val = di->fcp_ops->fcp_read_switch_status();
	if (val) {
		switch_status_num = switch_status_num + 1;
	} else {
		switch_status_num = 0;
	}
	if (VBUS_REPORT_NUM <= switch_status_num) {
		switch_status_num = 0;
		charger_dsm_report(ERROR_SWITCH_ATTACH, NULL);
	}
}

/**********************************************************
*  Function:       fcp_check_adapter_status
*  Description:    check adapter status
*  Parameters:     void
*  return value:  void
**********************************************************/
void fcp_check_adapter_status(struct charge_device_info *di)
{
	int val = -1;
	int reg = 0;
	int ret = -1;

	/*check usb is on or not ,if not ,can not detect the switch status */
	if (di->ops->get_charge_state) {
		ret = di->ops->get_charge_state(&reg);
		if (ret) {
			hwlog_info("%s:read PG STAT fail.\n", __func__);
			return;
		}
		if (reg & CHAGRE_STATE_NOT_PG) {
			hwlog_info
			    ("%s:PG NOT GOOD can not check adapter status.\n", __func__);
			return;
		}
	}

	if (!di->fcp_ops->fcp_read_adapter_status) {
		hwlog_err("di->ops->fcp_read_adapter_status is null.\n");
		return;
	}
	val = di->fcp_ops->fcp_read_adapter_status();

	if (FCP_ADAPTER_OVLT == val) {
		charger_dsm_report(ERROR_ADAPTER_OVLT, NULL);
	}

	if (FCP_ADAPTER_OCURRENT == val) {
		charger_dsm_report(ERROR_ADAPTER_OCCURRENT, NULL);
	}

	if (FCP_ADAPTER_OTEMP == val) {
		charger_dsm_report(ERROR_ADAPTER_OTEMP, NULL);
	}
}

ATOMIC_NOTIFIER_HEAD(fault_notifier_list);
int charge_set_input_current(int iset)
{
	struct charge_device_info *di = g_di;
	int ret;

	if (NULL == di->ops || NULL == di->ops->set_input_current)
	{
		hwlog_err("%s:set_input_current fail!\n",__func__);
		return -1;
	}
	if (1 == vbat_ovp_set_input_current_flag)
	{
		di->ops->set_input_current(di->core_data->iin_max);
		hwlog_info("%s:vbat_ovp set_input_current = %d,vbat_ovp in process!\n",__func__,di->core_data->iin_max);
	} else
	{
		ret = di->ops->set_input_current(iset);
		if (ret > 0)
		{
			hwlog_info("input current is out of range:%dmA!!\n", ret);
			di->ops->set_input_current(ret);
		} else if (ret < 0)
		{
			hwlog_err("set input current fail!\n");
		}
		hwlog_info("%s:set_input_current = %d!\n",__func__,iset);
	}
	return 0;
}
/**********************************************************
*  Function:       charge_rename_charger_type
*  Description:    rename the charger_type from USB PHY to charger
*  Parameters:   type:charger type from USB PHY
*                      di:charge_device_info
*                      update_flag
*  return value:  true:notify work /false:not notify work
**********************************************************/
static int charge_rename_charger_type(enum hisi_charger_type type,
				       struct charge_device_info *di ,bool update_flag)
{
	bool ret = TRUE;
	switch (type) {
	case CHARGER_TYPE_SDP:
		if(CHARGER_REMOVED == di->charger_type || CHARGER_TYPE_NON_STANDARD == di->charger_type
			|| CHARGER_TYPE_USB == di->charger_type)
		{
			di->charger_type = CHARGER_TYPE_USB;
			di->charger_source = POWER_SUPPLY_TYPE_USB;
			usb_continuous_notify_times++;
			ret = FALSE;
		}
		break;
	case CHARGER_TYPE_CDP:
		if(CHARGER_REMOVED == di->charger_type || CHARGER_TYPE_NON_STANDARD == di->charger_type)
		{
			di->charger_type = CHARGER_TYPE_BC_USB;
			di->charger_source = POWER_SUPPLY_TYPE_USB;
			ret = FALSE;
		}
		break;
	case CHARGER_TYPE_DCP:
		di->charger_type = CHARGER_TYPE_STANDARD;
		di->charger_source = POWER_SUPPLY_TYPE_MAINS;
		if (1 == di->support_standard_ico)
			ico_enable = 1;
		else
			ico_enable = 0;
		ret = FALSE;
		break;
	case CHARGER_TYPE_UNKNOWN:
		if(CHARGER_REMOVED == di->charger_type)
		{
			di->charger_type = CHARGER_TYPE_NON_STANDARD;
			di->charger_source = POWER_SUPPLY_TYPE_MAINS;
			ret = FALSE;
		}
		break;
	case CHARGER_TYPE_NONE:
		if(CHARGER_REMOVED != di->charger_type)
		{
			di->charger_type = CHARGER_REMOVED;
			di->charger_source = POWER_SUPPLY_TYPE_BATTERY;
			ret = FALSE;
		}
		break;
	case PLEASE_PROVIDE_POWER:
		if(CHARGER_REMOVED == di->charger_type)
		{
			di->charger_type = USB_EVENT_OTG_ID;
			di->charger_source = POWER_SUPPLY_TYPE_BATTERY;
			ret = FALSE;
		}
		break;
	default:
		di->charger_type = CHARGER_REMOVED;
		di->charger_source = POWER_SUPPLY_TYPE_BATTERY;
		ret = FALSE;
		break;
	}
	if ((USB_ICO_CNT == usb_continuous_notify_times)
		&& (1 == di->support_usb_nonstandard_ico))
		ico_enable = 1;
	return ret;
}

/**********************************************************
*  Function:       charge_update_charger_type
*  Description:    update charger_type from fsa9685 when the charger_type is CHARGER_TYPE_NON_STANDARD
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_update_charger_type(struct charge_device_info *di)
{
	enum hisi_charger_type type = CHARGER_TYPE_NONE;

	if (di->charger_type != CHARGER_TYPE_NON_STANDARD)
		return;

	nonstand_detect_times++;

	if(di->sw_ops && di->sw_ops->get_charger_type) {
		type = di->sw_ops->get_charger_type();
		if (type != CHARGER_TYPE_NONE) {
			charge_rename_charger_type(type, di,TRUE);
		}
		hwlog_info("[%s]charger type is update to[%d] from nonstd charger!\n",
			__func__, di->charger_type);
	}

	if (nonstand_detect_times >= NONSTAND_ICO_CNT
	&& CHARGER_TYPE_NON_STANDARD == di->charger_type
	&& 1 == di->support_usb_nonstandard_ico)
		ico_enable = 1;
	else
		ico_enable = 0;
}

/**********************************************************
*  Function:       charge_send_uevent
*  Discription:    send charge uevent immediately after charger type is recognized
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_send_uevent(struct charge_device_info *di)
{
	/*send events */
	enum charge_status_event events;
	if (di == NULL) {
		hwlog_err("[%s]di is NULL!\n", __func__);
		return;
	}

	if (di->charger_source == POWER_SUPPLY_TYPE_MAINS) {
		events = VCHRG_START_AC_CHARGING_EVENT;
		hisi_coul_charger_event_rcv(events);
	} else if (di->charger_source == POWER_SUPPLY_TYPE_USB) {
		events = VCHRG_START_USB_CHARGING_EVENT;
		hisi_coul_charger_event_rcv(events);
	} else if (di->charger_source == POWER_SUPPLY_TYPE_BATTERY) {
		events = VCHRG_STOP_CHARGING_EVENT;
		hisi_coul_charger_event_rcv(events);
	} else {
		hwlog_err("[%s]error charger source!\n", __func__);
		/*do nothing*/
	}
}

void vbat_ovp_send_uevent(void)
{
	/*send events */
	struct charge_device_info *di = g_di;
	charge_send_uevent(di);
}

EXPORT_SYMBOL(fcp_get_stage_status);
/**********************************************************
*  Function:       fcp_get_stage_status
*  Description:    get the stage of fcp charge
*  Parameters:     di:charge_device_info
*  return value:   NULL
**********************************************************/
enum fcp_check_stage_type fcp_get_stage_status(void)
{
	return fcp_stage;
}

/**********************************************************
*  Function:       fcp_set_stage_status
*  Description:    set the stage of fcp charge
*  Parameters:     di:charge_device_info
*  return value:   NULL
**********************************************************/
void fcp_set_stage_status(enum fcp_check_stage_type stage_type)
{
	fcp_stage = stage_type;
}
int vbat_ovp_fcp_adaptor_reset(void)
{
	struct charge_device_info *di = g_di;
	int ret;
	int vindpm = CHARGE_VOLTAGE_4520_MV;

	hwlog_info("%s:vbat_ovp!\n",__func__);
	fcp_set_stage_status(FCP_STAGE_ERROR);
	if (NULL == di->fcp_ops || NULL == di->fcp_ops->fcp_adapter_reset ||NULL == di->ops
		||NULL == di->ops->set_vbus_vset ||NULL == di->ops->set_dpm_voltage)
	{
		hwlog_err("%s:invalid pointor\n",__func__);
		return -1;
	}
	if (di->fcp_ops->fcp_adapter_reset())
	{
		hwlog_err("%s:adapter reset failed \n",__func__);
	}
	if (di->ops->set_vbus_vset(ADAPTER_5V))
	{
		hwlog_err("%s:set vbus vset failed \n",__func__);
	}
	ret = di->ops->set_dpm_voltage(vindpm);
	if (ret > 0)
	{
		hwlog_info("%s:dpm voltage is out of range:%dmV!!\n",__func__, ret);
		ret = di->ops->set_dpm_voltage(ret);
		if (ret < 0)
			hwlog_err("%s:set dpm voltage fail!!\n",__func__);
	} else if (ret < 0)
		hwlog_err("%s:set dpm voltage fail!!\n",__func__);
	hwlog_info("%s:for vbat_ovp!\n",__func__, ret);
	return 0;
}

/**********************************************************
*  Function:       fcp_retry_pre_operate
*  Discription:    pre operate before retry fcp enable
*  Parameters:   di:charge_device_info,type : enum fcp_retry_operate_type
*  return value:  0: fcp pre operate success
*                     -1:fcp pre operate fail
**********************************************************/
static int fcp_retry_pre_operate(enum fcp_retry_operate_type type,
				 struct charge_device_info *di)
{
	int pg_state = 0, ret = -1;
	ret = di->ops->get_charge_state(&pg_state);
	if (ret < 0) {
		hwlog_err("get_charge_state fail!!ret = 0x%x\n", ret);
		return ret;
	}
	/*check status charger not power good state */
	if (pg_state & CHAGRE_STATE_NOT_PG) {
		hwlog_err("state is not power good \n");
		return -1;
	}
	switch (type) {
	case FCP_RETRY_OPERATE_RESET_ADAPTER:
		if (NULL != di->fcp_ops->fcp_adapter_reset) {
			hwlog_info("send fcp adapter reset cmd \n");
			ret = di->fcp_ops->fcp_adapter_reset();
		} else {
			ret = -1;
		}
		break;
	case FCP_RETRY_OPERATE_RESET_SWITCH:
		if (NULL != di->fcp_ops->switch_chip_reset) {
			hwlog_info(" switch_chip_reset \n");
			ret = di->fcp_ops->switch_chip_reset();
			msleep(2000);
		} else {
			ret = -1;
		}
		break;
	default:
		break;
	}
	return ret;
}

/**********************************************************
*  Function:       fcp_start_charging
*  Description:    enter fcp charging mode
*  Parameters:   di:charge_device_info
*  return value:  0: fcp start success
*                    -1:fcp start fail
**********************************************************/
static int fcp_start_charging(struct charge_device_info *di)
{
	int ret = -1;
	int output_vol = 0;
	fcp_set_stage_status(FCP_STAGE_SUPPORT_DETECT);
	if ((NULL == di->fcp_ops) || (NULL == di->fcp_ops->is_support_fcp)
	    || (NULL == di->fcp_ops->detect_adapter)
	    || (NULL == di->fcp_ops->set_adapter_output_vol)
	    || (NULL == di->fcp_ops->get_adapter_output_current)) {
		hwlog_err("fcp ops is NULL!\n");
		return -1;
	}
	/*check whether support fcp detect */
	if (di->fcp_ops->is_support_fcp()) {
		hwlog_err("not support fcp!\n");
		return -1;
	}
	/*To avoid to effect accp detect , input current need to be lower than 1A,we set 0.5A */
	di->input_current = CHARGE_CURRENT_0500_MA;
	charge_set_input_current(di->input_current);

	/*detect fcp adapter */
	fcp_set_stage_status(FCP_STAGE_ADAPTER_DETECT);
	ret = di->fcp_ops->detect_adapter();
#ifdef CONFIG_DIRECT_CHARGER
	if (!is_direct_charge_failed()) {
#endif
		if (FCP_ADAPTER_DETECT_SUCC != ret) {
			hwlog_err("fcp detect fail!\n");
			if (FCP_ADAPTER_DETECT_FAIL == ret) {
				return 1;
			}
			return -1;
		}
#ifdef CONFIG_DIRECT_CHARGER
	}
#endif

	fcp_set_stage_status(FCP_STAGE_ADAPTER_ENABLE);
	di->ops->fcp_chip_init();
	/*disable charger when vol is changed */
	di->ops->set_charge_enable(FALSE);

	/*set fcp adapter output vol */
	if (di->fcp_ops->set_adapter_output_vol(&output_vol)) {
		di->ops->chip_init();
		hwlog_err("fcp set vol fail!\n");
		ret = di->fcp_ops->switch_chip_reset();
		return 1;
	}
	hwlog_info("output vol = %d\n", output_vol);

	if (di->ops->set_vbus_vset) {
		ret = di->ops->set_vbus_vset(output_vol);
		if (ret) {
			hwlog_err("set vbus_vset fail!\n");
		}
	}

	/*enable charger when vol is changed */
	di->ops->set_charge_enable(TRUE);
	di->charger_type = CHARGER_TYPE_FCP;
	fcp_set_stage_status(FCP_STAGE_SUCESS);
	hwlog_info("fcp charging start success!\n");
	return 0;
}

int get_charger_vbus_vol(void)
{
	int ret = 0;
	unsigned int vbus_vol = 0;
	struct charge_device_info *di = g_di;

	if (di->ops->get_vbus)
	{
		hwlog_err("[%s] fail.\n", __func__);
		ret = di->ops->get_vbus(&vbus_vol);
	}
	return vbus_vol;
}

/**********************************************************
*  Function:        charge_vbus_voltage_check
*  Description:     check whether the voltage of vbus is normal
*  Parameters:   di:charge_device_info
*  return value:   NULL
**********************************************************/
static void charge_vbus_voltage_check(struct charge_device_info *di)
{
	int ret = 0;
	unsigned int vbus_vol = 0;
	static int nonfcp_vbus_higher_count;

	if (NULL == di->ops->get_vbus)
		return;

	if (di->ops->set_covn_start)
		ret = di->ops->set_covn_start(true);

	if (ret) {
		hwlog_err("[%s]set covn start fail.\n", __func__);
		return;
	}
	ret = di->ops->get_vbus(&vbus_vol);
	hwlog_info("vbus vbus_vol:%d.\n", vbus_vol);

	if (ret)
		hwlog_err("[%s]vbus read failed \n", __func__);

	if(CHARGER_TYPE_PD == di->charger_type)
		return;

	if (FCP_STAGE_SUCESS == fcp_get_stage_status()) {
		/* fcp stage : vbus must be higher than 7000 mV */
		if (vbus_vol < VBUS_VOLTAGE_FCP_MIN_MV) {
			fcp_vbus_lower_count += 1;
			hwlog_err
			    ("[%s]fcp output vol =%d mV, lower 7000 mV , fcp_vbus_lower_count =%d!!\n",
			     __func__, vbus_vol, fcp_vbus_lower_count);
		} else {
			fcp_vbus_lower_count = 0;
		}
		/* check continuous abnormal vbus cout  */
		if (fcp_vbus_lower_count >= VBUS_VOLTAGE_ABNORMAL_MAX_COUNT) {
			vbus_flag = vbus_flag + 1;
			fcp_check_adapter_status(di);
			fcp_set_stage_status(FCP_STAGE_DEFAUTL);
			di->charger_type = CHARGER_TYPE_STANDARD;
			if (di->fcp_ops->fcp_adapter_reset()) {
				hwlog_err("adapter reset failed \n");
			}
			if (di->ops->set_vbus_vset) {
				ret = di->ops->set_vbus_vset(ADAPTER_5V);
				if(ret)
					hwlog_err("set vbus_vset fail!\n");
			}
			fcp_vbus_lower_count = VBUS_VOLTAGE_ABNORMAL_MAX_COUNT;
		}
		if (VBUS_REPORT_NUM <= vbus_flag) {
			vbus_flag = 0;
			charger_dsm_report(ERROR_FCP_VOL_OVER_HIGH, &vbus_vol);
		}
		nonfcp_vbus_higher_count = 0;
	} else {
		/*non fcp stage : vbus must be lower than 6500 mV */
		if (vbus_vol > VBUS_VOLTAGE_NON_FCP_MAX_MV) {
			nonfcp_vbus_higher_count += 1;
			hwlog_info
			    ("[%s]non standard fcp and vbus voltage is %d mv,over 6500mv ,nonfcp_vbus_higher_count =%d!!\n",
			     __func__, vbus_vol, nonfcp_vbus_higher_count);
		} else {
			nonfcp_vbus_higher_count = 0;
		}
		/* check continuous abnormal vbus cout  */
		if (nonfcp_vbus_higher_count >= VBUS_VOLTAGE_ABNORMAL_MAX_COUNT) {
			di->charge_enable = FALSE;
			nonfcp_vbus_higher_count =
			    VBUS_VOLTAGE_ABNORMAL_MAX_COUNT;
			if (di->fcp_ops->is_fcp_charger_type
			    && di->fcp_ops->is_fcp_charger_type()) {
				hwlog_info("[%s]is fcp adapter!!\n", __func__);
			} else {
				hwlog_info("[%s] is not fcp adapter!!\n", __func__);
			}
		}
		fcp_vbus_lower_count = 0;
	}
}

/**********************************************************
*  Function:       fcp_charge_check
*  Description:    check whether start fcp charging,if support try to start fcp charging
*  Parameters:     di:charge_device_info
*  return value:   NULL
**********************************************************/
static void fcp_charge_check(struct charge_device_info *di)
{
	int ret = 0, i = 0;
	/* if chip not support fcp, return */
	if (!di->ops->fcp_chip_init)
		return;

	if (FCP_STAGE_SUCESS == fcp_get_stage_status())
		fcp_check_switch_status(di);

	if (di->charger_type != CHARGER_TYPE_STANDARD
	    || !(is_hisi_battery_exist())) {
		return;
	}
#ifdef CONFIG_DIRECT_CHARGER
	if (is_direct_charge_failed()) {
		fcp_set_stage_status(FCP_STAGE_DEFAUTL);
	}
#endif
	if (FCP_STAGE_DEFAUTL == fcp_get_stage_status()) {
		ret = fcp_start_charging(di);
		for (i = 0; i < 3 && ret == 1; i++) {
			/* reset adapter and try again */
			if ((fcp_retry_pre_operate(FCP_RETRY_OPERATE_RESET_ADAPTER, di)) < 0) {
				hwlog_err("reset adapter failed \n");
				break;
			}
			ret = fcp_start_charging(di);
		}
		if (ret == 1) {
			/* reset fsa9688 chip and try again */
			if ((fcp_retry_pre_operate(FCP_RETRY_OPERATE_RESET_SWITCH, di)) == 0) {
				ret = fcp_start_charging(di);
			} else {
				hwlog_err
				    ("%s : fcp_retry_pre_operate failed \n", __func__);
			}
		}

		if (ret == 1) {
			if (FCP_STAGE_ADAPTER_ENABLE == fcp_get_stage_status())
				output_num = output_num + 1;
			else
				output_num = 0;

			if (VBUS_REPORT_NUM <= output_num) {
				output_num = 0;
				charger_dsm_report(ERROR_FCP_OUTPUT, NULL);
			}
			if (FCP_STAGE_ADAPTER_DETECT == fcp_get_stage_status())
				detect_num = detect_num + 1;
			else
				detect_num = 0;

			if (VBUS_REPORT_NUM <= detect_num) {
				detect_num = 0;
				charger_dsm_report(ERROR_FCP_DETECT, NULL);
			}
		}

		hwlog_info("[%s]fcp stage  %s !!! \n", __func__,
			   fcp_check_stage[fcp_get_stage_status()]);
	}
}
/****************************************************************************
  Function:     fcp_test_is_support
  Description:  check if fcp is support
  Input:        NA
  Output:      NA
  Return:      0: success
               other: fail
***************************************************************************/
int fcp_test_is_support(void)
{
	if(g_fcp_ops == NULL){
		hwlog_info("fcp detect fail \n");
		return -1;
	}

	if(g_fcp_ops -> is_support_fcp){
		return g_fcp_ops -> is_support_fcp();
	}

	return -1;
}
/****************************************************************************
  Function:     fcp_test_detect_adapter
  Description:  check if fcp adapter detect is true
  Input:        NA
  Output:      NA
  Return:      0: success
               -1: other fail
               1:fcp adapter but detect fail
***************************************************************************/
int fcp_test_detect_adapter(void)
{
	if(g_fcp_ops == NULL){
		hwlog_info("fcp detect fail \n");
		return -1;
	}

	if(g_fcp_ops -> detect_adapter){
		return g_fcp_ops -> detect_adapter();
	}

	return -1;
}

/**********************************************************
*  Function:       charge_typec_current
*  Discription:    select typec current or bc1.2 type current
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_typec_current(struct charge_device_info *di)
{
	switch (di->typec_current_mode) {
	case TYPEC_DEV_CURRENT_HIGH:
		di->input_typec_current = di->core_data->iin_typech;	/*3A but the inductance is limit 2A*/
		di->charge_typec_current = di->core_data->ichg_typech;
		hwlog_info("[%s]Type C type  %d,%d,%d !!! \n", __func__,
			   di->typec_current_mode, di->input_typec_current,
			   di->charge_typec_current);
		break;
	case TYPEC_DEV_CURRENT_MID:
		di->input_typec_current = TYPE_C_MID_MODE_CURR;
		di->charge_typec_current = TYPE_C_MID_MODE_CURR;
		hwlog_info("[%s]Type C type   %d,%d,%d !!! \n", __func__,
			   di->typec_current_mode, di->input_typec_current,
			   di->charge_typec_current);
		break;
	case TYPEC_DEV_CURRENT_DEFAULT:
	case TYPEC_DEV_CURRENT_NOT_READY:
		di->input_typec_current = TYPE_C_DEFAULT_MODE_CURR;
		di->charge_typec_current = TYPE_C_DEFAULT_MODE_CURR;
		hwlog_info("[%s]Type C type   %d,%d,%d !!! \n", __func__,
			   di->typec_current_mode, di->input_typec_current,
			   di->charge_typec_current);
		break;
	default:
		di->input_typec_current = TYPE_C_DEFAULT_MODE_CURR;
		di->charge_typec_current = TYPE_C_DEFAULT_MODE_CURR;
		hwlog_info("[%s]Type C type   default,%d,%d !!! \n", __func__,
			   di->input_typec_current, di->charge_typec_current);
		break;
	}
	/*compare typeC current and bc1.2 current */
	di->input_current = di->input_current < di->input_typec_current ?
		di->input_typec_current : di->input_current;
	di->charge_current = di->charge_current < di->charge_typec_current ?
		di->charge_typec_current : di->charge_current;
	return;
}

/**********************************************************
*  Function:       select_ico_current
*  Description:    select ico current
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void select_ico_current(struct charge_device_info *di)
{
	int ret = -1;
	static struct ico_input input;
	static struct ico_output output;

	if (di->start_attemp_ico) {
		if (!di->ops || !di->ops->turn_on_ico) {
			return;
		} else {
			input.charger_type = di->charger_type;
			input.iin_max = di->core_data->iin_max;
			input.ichg_max = di->core_data->ichg_max;
			input.vterm = di->core_data->vterm < di->sysfs_data.vterm_rt ?
						di->core_data->vterm : di->sysfs_data.vterm_rt;
			output.input_current = di->input_current;
			output.charge_current = di->charge_current;
			ret = di->ops->turn_on_ico(&input, &output);
			if (!ret) {
				if (!di->ico_all_the_way) {
					di->start_attemp_ico = 0;
					hwlog_info("ico result: input current is %dmA, charge current is %dmA\n",
						output.input_current, output.charge_current);
				} else {
					di->start_attemp_ico = 1;
				}
			} else {
				hwlog_info("ico current detect fail.");
			}
		}
	}

	di->input_current = output.input_current;
	di->charge_current =  output.charge_current;
}

/**********************************************************
*  Function:       charge_select_charging_current
*  Description:    get the input current and charge current from different charger_type and charging limited value
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_select_charging_current(struct charge_device_info *di)
{
	static unsigned int first_in = 1;

	switch (di->charger_type) {
	case CHARGER_TYPE_USB:
		di->input_current = di->core_data->iin_usb;
		di->charge_current = di->core_data->ichg_usb;
		break;
	case CHARGER_TYPE_NON_STANDARD:
		di->input_current = di->core_data->iin_nonstd;
		di->charge_current = di->core_data->ichg_nonstd;
		break;
	case CHARGER_TYPE_BC_USB:
		di->input_current = di->core_data->iin_bc_usb;
		di->charge_current = di->core_data->ichg_bc_usb;
		break;
	case CHARGER_TYPE_STANDARD:
		di->input_current = di->core_data->iin_ac;
		di->charge_current = di->core_data->ichg_ac;
		break;
	case CHARGER_TYPE_VR:
		di->input_current = di->core_data->iin_vr;
		di->charge_current = di->core_data->ichg_vr;
		break;
	case CHARGER_TYPE_FCP:
		di->input_current = di->core_data->iin_fcp;
		di->charge_current = di->core_data->ichg_fcp;
		break;
	case CHARGER_TYPE_PD:
		di->input_current = di->pd_input_current;
		di->charge_current = di->pd_charge_current;
		pr_info("CHARGER_TYPE_PD input_current %d  charge_current = %d", di->input_current, di->charge_current);
		if(di->charge_current > di->core_data->ichg_max)
			di->charge_current = di->core_data->ichg_max;
		break;
	default:
		di->input_current = CHARGE_CURRENT_0500_MA;
		di->charge_current = CHARGE_CURRENT_0500_MA;
		break;
	}
	/*only the typec is supported ,we need read typec result and
	when adapter is fcp adapter ,we set current by fcp adapter rule */
	if (di->core_data->typec_support && (FCP_STAGE_SUCESS != fcp_get_stage_status())) {
		charge_typec_current(di);
	}

	if((1 == di->sysfs_data.support_ico)
		&& (1 == ico_enable))
		select_ico_current(di);

#ifndef CONFIG_HLTHERM_RUNTEST
	if (strstr(saved_command_line, "androidboot.swtype=factory")
	    && (!is_hisi_battery_exist())) {
		if (first_in) {
			hwlog_info
			    ("facory_version and battery not exist, enable charge\n");
			first_in = 0;
		}
	} else {
#endif
		if (di->sysfs_data.charge_limit == TRUE) {
			di->input_current = di->input_current < di->core_data->iin ?
				di->input_current : di->core_data->iin;
			di->input_current = di->input_current < di->sysfs_data.iin_thl ?
				di->input_current : di->sysfs_data.iin_thl;
			di->input_current = di->input_current < di->sysfs_data.iin_rt ?
				di->input_current : di->sysfs_data.iin_rt;

			di->charge_current = di->charge_current < di->core_data->ichg ?
				di->charge_current : di->core_data->ichg;
			di->charge_current = di->charge_current < di->sysfs_data.ichg_thl ?
				di->charge_current : di->sysfs_data.ichg_thl;
			di->charge_current = di->charge_current < di->sysfs_data.ichg_rt ?
				di->charge_current : di->sysfs_data.ichg_rt;
		}
#ifndef CONFIG_HLTHERM_RUNTEST
	}
#endif

	if (0 != di->sysfs_data.inputcurrent)
		di->input_current = di->sysfs_data.inputcurrent;

	if (1 == di->sysfs_data.batfet_disable)
		di->input_current = CHARGE_CURRENT_2000_MA;
}

/**********************************************************
*  Function:       charge_update_vindpm
*  Description:    update the input dpm voltage setting by battery capacity
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_update_vindpm(struct charge_device_info *di)
{
	int ret = 0;
	int vindpm = CHARGE_VOLTAGE_4520_MV;

	if (FCP_STAGE_SUCESS == fcp_get_stage_status()) {
		vindpm = di->fcp_vindpm;
	} else if (POWER_SUPPLY_TYPE_MAINS == di->charger_source) {
		vindpm = di->core_data->vdpm;
	} else if (POWER_SUPPLY_TYPE_USB == di->charger_source) {
		if (di->core_data->vdpm > CHARGE_VOLTAGE_4520_MV) {
			vindpm = di->core_data->vdpm;
		}
	} else {
		/*do nothing:*/
	}

	if (di->ops->set_dpm_voltage) {
		ret = di->ops->set_dpm_voltage(vindpm);
		if (ret > 0) {
			hwlog_info("dpm voltage is out of range:%dmV!!\n", ret);
			ret = di->ops->set_dpm_voltage(ret);
			if (ret < 0)
				hwlog_err("set dpm voltage fail!!\n");
		} else if (ret < 0)
			hwlog_err("set dpm voltage fail!!\n");
	}
}

/**********************************************************
*  Function:       charge_update_external_setting
*  Description:    update the others chargerIC setting
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_update_external_setting(struct charge_device_info *di)
{
	int ret = 0;
	unsigned int batfet_disable = FALSE;
	unsigned int watchdog_timer = WATCHDOG_TIMER_80_S;

	/*update batfet setting */
	if (di->sysfs_data.batfet_disable == TRUE) {
		batfet_disable = TRUE;
	}
	if (di->ops->set_batfet_disable) {
		ret = di->ops->set_batfet_disable(batfet_disable);
		if (ret)
			hwlog_err("set batfet disable fail!!\n");
	}
	/*update watch dog timer setting */
	if (di->sysfs_data.wdt_disable == TRUE) {
		watchdog_timer = WATCHDOG_TIMER_DISABLE;
	}
	if (di->ops->set_watchdog_timer) {
		ret = di->ops->set_watchdog_timer(watchdog_timer);
		if (ret)
			hwlog_err("set watchdog timer fail!!\n");
	}
}

/**********************************************************
*  Function:       charge_is_charging_full
*  Description:    check the battery is charging full  or not
*  Parameters:   di:charge_device_info
*  return value:  TURE-is full or FALSE-no full
**********************************************************/
static int charge_is_charging_full(struct charge_device_info *di)
{
	int ichg = -hisi_battery_current();
	int ichg_avg = hisi_battery_current_avg();
	int val = FALSE;

	if (!(di->charge_enable) || !(is_hisi_battery_exist()))
		return val;

	if ((ichg > MIN_CHARGING_CURRENT_OFFSET)
	    && (ichg < (int)di->core_data->iterm)
	    && (ichg_avg > MIN_CHARGING_CURRENT_OFFSET)
	    && (ichg_avg < (int)di->core_data->iterm)) {
		di->check_full_count++;
		if (di->check_full_count >= BATTERY_FULL_CHECK_TIMIES) {
			di->check_full_count = BATTERY_FULL_CHECK_TIMIES;
			val = TRUE;
			hwlog_info
			    ("battery is full!capacity = %d,ichg = %d,ichg_avg = %d\n",
			     hisi_battery_capacity(), ichg, ichg_avg);
		}
	} else {
		di->check_full_count = 0;
	}

	return val;
}

/**********************************************************
*  Function:       charge_full_handle
*  Description:    set term enable flag by charge current is lower than iterm
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_full_handle(struct charge_device_info *di)
{
	int ret = 0;
	int is_battery_full = charge_is_charging_full(di);

	if (di->ops->set_term_enable) {
		ret = di->ops->set_term_enable(is_battery_full);
		if (ret)
			hwlog_err("set term enable fail!!\n");
	}
	/*set terminal current */
	ret = di->ops->set_terminal_current(di->core_data->iterm);
	if (ret > 0) {
		di->ops->set_terminal_current(ret);
	} else if (ret < 0) {
		hwlog_err("set terminal current fail!\n");
	}
	/* reset adapter to 5v after fcp charge done,avoid long-term at high voltage */
	if (is_battery_full && FCP_STAGE_SUCESS == fcp_get_stage_status()
	    && hisi_battery_capacity() == 100
	    && NULL != di->fcp_ops->fcp_adapter_reset) {
		if (di->fcp_ops->fcp_adapter_reset()) {
			hwlog_err("adapter reset failed \n");
		}
		fcp_set_stage_status(FCP_STAGE_CHARGE_DONE);
		if (di->ops->set_vbus_vset) {
			ret = di->ops->set_vbus_vset(ADAPTER_5V);
			if(ret)
				hwlog_err("set vbus_vset fail!\n");
		}
		hwlog_info("fcp charge done, reset adapter to 5v !\n");
	}
}

/**********************************************************
*  Function:       charge_set_charge_state
*  Description:    set charge stop or enable
*  Parameters:     state:0 stop 1 enable
*  return value:   old state
**********************************************************/
int charge_set_charge_state(int state)
{
	int old_state;
	int chg_en = 0;
	struct charge_device_info *di = g_di;

	if ((di == NULL)
	    || ((state != 0) && (state != 1))
	    || NULL == di->ops->get_charge_enable_status ){
	    return -1;
	}

	old_state = di->ops->get_charge_enable_status();
	chg_en = state;
	di->ops->set_charge_enable(chg_en);

	return old_state;
}

/**********************************************************
*  Function:       charge_kick_watchdog
*  Description:    kick watchdog timer
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_kick_watchdog(struct charge_device_info *di)
{
	int ret = 0;
	ret = di->ops->reset_watchdog_timer();
	if (ret)
		hwlog_err("charge kick watchdog timer fail!!\n");
#ifdef CONFIG_HISI_CHARGER_SYS_WDG
	charge_feed_sys_wdt(60);
#endif
}

/**********************************************************
*  Function:       charge_disable_watchdog
*  Description:   disable watchdog timer
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_disable_watchdog(struct charge_device_info *di)
{
	int ret = 0;
	ret = di->ops->set_watchdog_timer(WDT_STOP);
	if (ret)
		hwlog_err("charge disable watchdog timer fail!!\n");
	else
		hwlog_info("charge disable watchdog timer");
#ifdef CONFIG_HISI_CHARGER_SYS_WDG
	charge_stop_sys_wdt();
#endif
}

/**********************************************************
*  Function:       charge_start_charging
*  Description:    enter into charging mode
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_start_charging(struct charge_device_info *di)
{
	int ret = 0;

	hwlog_info("---->START CHARGING\n");
	charge_wake_lock();
	di->sysfs_data.charge_enable = TRUE;
	di->check_full_count = 0;
	di->start_attemp_ico = 1;
	/*chip init */
	ret = di->ops->chip_init();
	if (ret)
		hwlog_err("chip init fail!!\n");
#ifdef CONFIG_HISI_CHARGER_SYS_WDG
	charge_enable_sys_wdt();
#endif
	mod_delayed_work(system_wq, &g_di->charge_work, msecs_to_jiffies(0));
}

/**********************************************************
*  Function:       charge_stop_charging
*  Description:    exit charging mode
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_stop_charging(struct charge_device_info *di)
{
	int ret = 0;

	hwlog_info("---->STOP CHARGING\n");
	cancel_work_flag = true;
	charge_wake_lock();
	nonstand_detect_times = 0;
	ico_enable = 0;
	usb_continuous_notify_times = 0;
	di->sysfs_data.charge_enable = FALSE;
	di->sysfs_data.adc_conv_rate = 0;
	di->sysfs_data.water_intrused = 0;
#ifdef CONFIG_TCPC_CLASS
	di->pd_input_current = 0;
	di->pd_charge_current = 0;
#endif
	output_num = 0;
	detect_num = 0;
	vbus_flag = 0;
	fcp_vbus_lower_count = 0;
	if (di->ops->set_adc_conv_rate)
		di->ops->set_adc_conv_rate(di->sysfs_data.adc_conv_rate);
	di->check_full_count = 0;
	ret = di->ops->set_charge_enable(FALSE);
	if (ret)
		hwlog_err("[%s]set charge enable fail!\n", __func__);
	ret = di->ops->set_otg_enable(FALSE);
	if (ret)
		hwlog_err("[%s]set otg enable fail!\n", __func__);
	otg_flag = FALSE;
	cancel_delayed_work_sync(&di->charge_work);
	cancel_delayed_work_sync(&di->otg_work);
	cancel_work_flag = false;
	if ((di->sysfs_data.wdt_disable == TRUE) && (di->ops->set_watchdog_timer)) {	/*when charger stop ,disable watch dog ,only for hiz */
		if (di->ops->set_watchdog_timer(WATCHDOG_TIMER_DISABLE))
			hwlog_err("set watchdog timer fail for hiz!!\n");
	}
	if (di->ops->stop_charge_config) {
		if (di->ops->stop_charge_config()) {
			hwlog_err(" stop charge config failed \n");
		}
	}
	if (di->fcp_ops && di->fcp_ops->stop_charge_config) {
		if (di->fcp_ops->stop_charge_config()) {
			hwlog_err(" fcp stop charge config failed \n");
		}
	}
	/*flag must be clear after charge_work has been canceled */
	fcp_set_stage_status(FCP_STAGE_DEFAUTL);
#ifdef CONFIG_DIRECT_CHARGER
	direct_charge_update_cutoff_flag();
	if (!di->ignore_pluggin_and_plugout_flag)
	{
		direct_charge_stop_charging();
		complete(&usb_detach_completion);
		hwlog_info("%s:vbat_ovp completion call!\n",__func__);
	}
#endif

	wake_lock_timeout(&stop_charge_lock, HZ);
	mutex_lock(&charge_wakelock_flag_lock);
	charge_lock_flag = CHARGE_NO_NEED_WAKELOCK;
	charge_wake_unlock();
	mutex_unlock(&charge_wakelock_flag_lock);
#ifdef CONFIG_HISI_CHARGER_SYS_WDG
	charge_stop_sys_wdt();
#endif
}
extern void hisi_usb_otg_bc_again(void);

/**********************************************************
*  Function:       charge_type_dcp_detected_notify
*  Description:    check high voltage charge once dcp detected
*  Parameters:     NULL
*  return value:   NULL
**********************************************************/
void charge_type_dcp_detected_notify(void)
{
	if (g_di && (CHARGER_TYPE_NON_STANDARD == g_di->charger_type)) {
		hisi_usb_otg_bc_again();
		hwlog_info(" stop phy enter! \n");
		mod_delayed_work(system_wq, &g_di->charge_work, 0);
	}
}

/**********************************************************
*  Function:       charge_start_usb_otg
*  Description:    enter into otg mode
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_start_usb_otg(struct charge_device_info *di)
{
	int ret = 0;

	if (otg_flag) {
		hwlog_info("---->OTG Already Enabled\n");
		return;
	}

	hwlog_info("---->START OTG MODE\n");
	charge_wake_lock();

	ret = di->ops->set_charge_enable(FALSE);
	if (ret)
		hwlog_err("[%s]set charge enable fail!\n", __func__);
	ret = di->ops->set_otg_enable(TRUE);
	if (ret)
		hwlog_err("[%s]set otg enable fail!\n", __func__);
	otg_flag = TRUE;
	if (di->ops->set_otg_current) {
		ret = di->ops->set_otg_current(di->core_data->otg_curr);	/*otg current set 500mA form dtsi */
		if (ret)
			hwlog_err("[%s]set otg current fail!\n", __func__);
	}
	schedule_delayed_work(&di->otg_work, msecs_to_jiffies(0));
}

/**********************************************************
*  Function:       charge_otg_work
*  Description:    monitor the otg mode status
*  Parameters:   work:otg workqueue
*  return value:  NULL
**********************************************************/
static void charge_otg_work(struct work_struct *work)
{
	struct charge_device_info *di =
	    container_of(work, struct charge_device_info, otg_work.work);

	charge_kick_watchdog(di);
	schedule_delayed_work(&di->otg_work,
			      msecs_to_jiffies(CHARGING_WORK_TIMEOUT));
}
static void vbat_ovp_detect_work(struct work_struct *work)
{
	struct charge_device_info *di =
	    container_of(work, struct charge_device_info, vbat_ovp_work);
	int volt;

	while (CHARGER_REMOVED != charge_get_charger_type())
	{
		volt = hisi_battery_voltage();
		hwlog_info("%s:volt = %d\n",__func__,volt);
		if (volt > 4550)
		{
			atomic_notifier_call_chain(&vbat_ovp_notifier_list,0, NULL);
			hwlog_err("%s:vbat_ovp call\n",__func__);
			di->pmu_ovp_detect_flag = 0;
			return;
		}
		msleep(1000);
	}
	di->pmu_ovp_detect_flag = 0;
	hwlog_info("%s:usb detach,not detect pmu ovp!\n",__func__);
	return;
}

/**********************************************************
*  Function:       charge_fault_work
*  Description:    handler the fault events from chargerIC
*  Parameters:   work:fault workqueue
*  return value:  NULL
**********************************************************/
static void charge_fault_work(struct work_struct *work)
{
	struct charge_device_info *di =
	    container_of(work, struct charge_device_info, fault_work);

	switch (di->charge_fault) {
	case CHARGE_FAULT_BOOST_OCP:
		hwlog_err("vbus overloaded in boost mode,close otg mode!!\n");
		di->ops->set_otg_enable(FALSE);
		di->charge_fault = CHARGE_FAULT_NON;
		otg_flag = FALSE;
		charger_dsm_report(ERROR_BOOST_OCP, NULL);
		break;
	case CHARGE_FAULT_VBAT_OVP:
		hwlog_err("vbat_ovp happend\n!!\n");
		di->charge_fault = CHARGE_FAULT_NON;
		charger_dsm_report(ERROR_CHARGE_VBAT_OVP, NULL);
		if (0 == di->pmu_ovp_detect_flag)
		{
			di->pmu_ovp_detect_flag = 1;
			queue_work(di->vbat_ovp_handle_wq, &di->vbat_ovp_work);
		}else
		{
			hwlog_info("%s:pmu ovp detect in process\n",__func__);
		}
		break;
	default:
		break;
	}
}

/**********************************************************
*  Function:       charge_update_status
*  Description:    update the states of charging
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_update_status(struct charge_device_info *di)
{
	enum charge_status_event events = VCHRG_POWER_NONE_EVENT;
	unsigned int state = CHAGRE_STATE_NORMAL;
	int ret = 0;

	if (cancel_work_flag)
	{
		hwlog_info("charge already stop\n");
		return;
	}
#ifdef CONFIG_DIRECT_CHARGER
	if (di->ignore_pluggin_and_plugout_flag)
	{
		hwlog_info("no need to check\n");
		return;
	}
#endif
	ret = di->ops->get_charge_state(&state);
	if (ret < 0) {
		hwlog_err("get_charge_state fail!!ret = 0x%x\n", ret);
		return;
	}
	/*check status charger not power good state */
	if(CHARGER_TYPE_PD != di->charger_type) {
		if (state & CHAGRE_STATE_NOT_PG) {
			hwlog_err("VCHRG_POWER_SUPPLY_WEAKSOURCE\n");
			events = VCHRG_POWER_SUPPLY_WEAKSOURCE;
			hisi_coul_charger_event_rcv(events);
		}
	}
	/*check status charger ovp err */
	if (state & CHAGRE_STATE_VBUS_OVP) {
		hwlog_err("VCHRG_POWER_SUPPLY_OVERVOLTAGE\n");
		events = VCHRG_POWER_SUPPLY_OVERVOLTAGE;
		hisi_coul_charger_event_rcv(events);
	}
	/*check status watchdog timer expiration */
	if (state & CHAGRE_STATE_WDT_FAULT) {
		hwlog_err("CHAGRE_STATE_WDT_TIMEOUT\n");
		/*init chip register when watchdog timeout */
		di->ops->chip_init();
		events = VCHRG_STATE_WDT_TIMEOUT;
		hisi_coul_charger_event_rcv(events);
	}
	/*check status battery ovp */
	if (state & CHAGRE_STATE_BATT_OVP) {
		hwlog_err("CHAGRE_STATE_BATT_OVP\n");
	}

	/*check charger TS state*/
	if(state & CHAGRE_STATE_NTC_FAULT) {
		ts_flag = TRUE;
	}
	else {
		ts_flag = FALSE;
	}
	/*check status charge done, ac charge and usb charge */
	if ((di->charge_enable) && (is_hisi_battery_exist())) {
		di->sysfs_data.charge_done_status = CHARGE_DONE_NON;
		if (state & CHAGRE_STATE_CHRG_DONE) {
			events = VCHRG_CHARGE_DONE_EVENT;
			hwlog_info("VCHRG_CHARGE_DONE_EVENT\n");
			di->sysfs_data.charge_done_status = CHARGE_DONE;
			if ((CHARGE_DONE_SLEEP_ENABLED ==
			     di->sysfs_data.charge_done_sleep_status)
			    || charge_done_sleep_dts) {
				if ((CHARGER_TYPE_STANDARD == di->charger_type)
				    || (CHARGER_TYPE_NON_STANDARD ==
					di->charger_type)
				    || (CHARGER_TYPE_FCP == di->charger_type)) {
					blocking_notifier_call_chain(&charge_wake_unlock_list, NULL, NULL);
					mutex_lock(&charge_wakelock_flag_lock);
					charge_lock_flag = CHARGE_NEED_WAKELOCK;
					charge_wake_unlock();
					mutex_unlock
					    (&charge_wakelock_flag_lock);
					hwlog_info
					    ("charge wake unlock while charging done\n");
				}
			}
		} else if (di->charger_source == POWER_SUPPLY_TYPE_MAINS)
			events = VCHRG_START_AC_CHARGING_EVENT;
		else
			events = VCHRG_START_USB_CHARGING_EVENT;
	} else {
		events = VCHRG_NOT_CHARGING_EVENT;
		hwlog_info("VCHRG_NOT_CHARGING_EVENT\n");
	}
	hisi_coul_charger_event_rcv(events);
}

/**********************************************************
*  Function:       charge_turn_on_charging
*  Description:    turn on charging, set input and charge currrent /CV termminal voltage / charge enable
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_turn_on_charging(struct charge_device_info *di)
{
	int ret = 0;
	unsigned int vterm = 0;

	di->charge_enable = TRUE;
	/* check vbus voltage ,if vbus is abnormal disable charge or abort from fcp */
	charge_vbus_voltage_check(di);
	/*set input current */
	charge_set_input_current(di->input_current);
	/*check if allow charging or not */
	if (di->charge_current == CHARGE_CURRENT_0000_MA) {
		di->charge_enable = FALSE;
		hwlog_info("charge current is set 0mA, turn off charging!\n");
	} else {
		/*set CC charge current */
		ret = di->ops->set_charge_current(di->charge_current);
		if (ret > 0) {
			hwlog_info("charge current is out of range:%dmA!!\n",
				   ret);
			di->ops->set_charge_current(ret);
		} else if (ret < 0)
			hwlog_err("set charge current fail!\n");
		/*set CV terminal voltage */
		vterm =
		    ((di->core_data->vterm <
		      di->sysfs_data.vterm_rt) ? di->core_data->vterm : di->
		     sysfs_data.vterm_rt);
		ret = di->ops->set_terminal_voltage(vterm);
		if (ret > 0) {
			hwlog_info("terminal voltage is out of range:%dmV!!\n",
				   ret);
			di->ops->set_terminal_voltage(ret);
		} else if (ret < 0)
			hwlog_err("set terminal voltage fail!\n");
	}
	/*enable/disable charge */
	di->charge_enable &= di->sysfs_data.charge_enable;
	ret = di->ops->set_charge_enable(di->charge_enable);
	if (ret)
		hwlog_err("set charge enable fail!!\n");

	hwlog_debug
	    ("input_current is [%d],charge_current is [%d],terminal_voltage is [%d],charge_enable is [%d]\n",
	     di->input_current, di->charge_current, vterm, di->charge_enable);
}

/**********************************************************
*  Function:       water_check
*  Description:   water check and its operations
*  Parameters:   charge_device_info
*  return value:  NULL
**********************************************************/
static void water_check(struct charge_device_info *di)
{
	if(!di->water_check_enabled) /*if disabled, don't start water check*/
		return;
	/*in shutdown charge mode or factory version, don't start water check*/
	if (strstr(saved_command_line, "androidboot.mode=charger")
		||strstr(saved_command_line, "androidboot.swtype=factory"))
		return;
	if (CHARGER_TYPE_NON_STANDARD == di->charger_type) {
		if (di->sw_ops && di->sw_ops->is_water_intrused
			&& di->sw_ops->is_water_intrused()) {
			hwlog_info("start protection against water intrusion.\n");
			di->sysfs_data.water_intrused = 1;
			hisi_coul_charger_event_rcv(VCHRG_STATE_WATER_INTRUSED);
		}
	}
}

/**********************************************************
*  Function:       charge_safe_protect
*  Discription:    do safe protect ops
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static void charge_safe_protect(struct charge_device_info *di)
{
	if (NULL == di) {
		hwlog_err("%s:NULL pointer!!\n", __func__);
		return;
	}
	/*do soft ovp protect for 5V/9V charge*/
	if (di->ops && di->ops->soft_vbatt_ovp_protect) {
		di->ops->soft_vbatt_ovp_protect();
	}
}

/**********************************************************
*  Function:       charge_monitor_work
*  Description:    monitor the charging process
*  Parameters:   work:charge workqueue
*  return value:  NULL
**********************************************************/
static void charge_monitor_work(struct work_struct *work)
{
	struct charge_device_info *di =
	    container_of(work, struct charge_device_info, charge_work.work);
	charge_kick_watchdog(di);
	/* update type before get params */
	charge_update_charger_type(di);
	if (di->core_data->typec_support) {	/*only the typec is supported ,we need read typec result */
#ifdef CONFIG_HUAWEI_TYPEC
		di->typec_current_mode = typec_current_mode_detect();
#endif
	}
#ifdef CONFIG_DIRECT_CHARGER
	if (di->charger_type == CHARGER_TYPE_STANDARD)
	{
		direct_charge_check();
	}
#endif
	fcp_charge_check(di);

	di->core_data = charge_core_get_params();
	charge_select_charging_current(di);

	charge_turn_on_charging(di);
	charge_safe_protect(di);

	charge_full_handle(di);
	charge_update_vindpm(di);
	charge_update_external_setting(di);

	charge_update_status(di);
	charge_kick_watchdog(di);
	schedule_delayed_work(&di->charge_work,
			      msecs_to_jiffies(CHARGING_WORK_TIMEOUT));
}

/**********************************************************
*  Function:       charge_usb_work
*  Description:    handler interface by different charger_type
*  Parameters:   work:usb workqueue
*  return value:  NULL
**********************************************************/
static void charge_usb_work(struct work_struct *work)
{
	struct charge_device_info *di =
	    container_of(work, struct charge_device_info, usb_work);

#ifdef CONFIG_TCPC_CLASS
	if(charger_pd_support)
		mutex_lock(&di->tcpc_otg_lock);
#endif
	water_check(di);

	switch (di->charger_type) {
	case CHARGER_TYPE_USB:
		hwlog_info("case = CHARGER_TYPE_USB-> \n");
		charge_start_charging(di);
		break;
	case CHARGER_TYPE_NON_STANDARD:
		hwlog_info("case = CHARGER_TYPE_NON_STANDARD -> \n");
		charge_start_charging(di);
		break;
	case CHARGER_TYPE_BC_USB:
		hwlog_info("case = CHARGER_TYPE_BC_USB -> \n");
		charge_start_charging(di);
		break;
	case CHARGER_TYPE_STANDARD:
		hwlog_info("case = CHARGER_TYPE_STANDARD-> \n");
		charge_start_charging(di);
		break;
	case CHARGER_REMOVED:
		hwlog_info("case = USB_EVENT_NONE-> \n");
		charge_stop_charging(di);
		break;
	case USB_EVENT_OTG_ID:
		hwlog_info("case = USB_EVENT_OTG_ID-> \n");
		charge_start_usb_otg(di);
		break;
	case CHARGER_TYPE_PD:
		hwlog_info("case = CHARGER_TYPE_PD-> \n");
		charge_start_charging(di);
	default:
		break;
	}
#ifdef CONFIG_TCPC_CLASS
	if(charger_pd_support)
		mutex_unlock(&di->tcpc_otg_lock);
#endif
}

/**********************************************************
*  Function:       charge_process_vr_charge_event
*  Description:    deal with vr charge events
*  Parameters:     charge_device_info * di
*  return value:   NULL
**********************************************************/
static void charge_process_vr_charge_event(struct charge_device_info *di)
{
	charge_stop_charging(di);
	charge_wake_lock();

	switch (di->sysfs_data.vr_charger_type) {
	case CHARGER_TYPE_SDP:
		di->charger_type = CHARGER_TYPE_USB;
		di->charger_source = POWER_SUPPLY_TYPE_USB;
		charge_send_uevent(di);
		charge_start_charging(di);
		break;
	case CHARGER_TYPE_CDP:
		di->charger_type = CHARGER_TYPE_BC_USB;
		di->charger_source = POWER_SUPPLY_TYPE_USB;
		charge_send_uevent(di);
		charge_start_charging(di);
		break;
	case CHARGER_TYPE_DCP:
		di->charger_type = CHARGER_TYPE_VR;
		di->charger_source = POWER_SUPPLY_TYPE_MAINS;
		charge_send_uevent(di);
		charge_start_charging(di);
		break;
	case CHARGER_TYPE_UNKNOWN:
		di->charger_type = CHARGER_TYPE_NON_STANDARD;
		di->charger_source = POWER_SUPPLY_TYPE_MAINS;
		charge_send_uevent(di);
		charge_start_charging(di);
		break;
	case CHARGER_TYPE_NONE:
		di->charger_type = USB_EVENT_OTG_ID;
		di->charger_source = POWER_SUPPLY_TYPE_BATTERY;
		charge_send_uevent(di);
		charge_start_usb_otg(di);
		break;
	default:
		hwlog_info("Invalid vr charger type! vr_charge_type = %d\n",
			   di->sysfs_data.vr_charger_type);
		break;
	}
}

/**********************************************************
*  Function:       charge_resume_wakelock_work
*  Description:    apply wake_lock when resume
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void charge_resume_wakelock_work(void)
{
	mutex_lock(&charge_wakelock_flag_lock);
	if (CHARGE_NEED_WAKELOCK == charge_lock_flag) {
		charge_wake_lock();
		hwlog_info("charge wake lock when resume during charging\n");
	}
	mutex_unlock(&charge_wakelock_flag_lock);
}

static void uscp_plugout_send_uevent(void)
{
	struct charge_device_info *di = g_di;

	charge_send_uevent(di);
	uscp_plugout_wake_unlock();
}

int is_pd_supported(void)
{
	return charger_pd_support;
}
void charge_uevent_process(struct charge_device_info *di, unsigned long event)
{
#ifdef CONFIG_DIRECT_CHARGER
	if (!di->ignore_pluggin_and_plugout_flag) {
#endif

#ifdef  CONFIG_HUAWEI_USB_SHORT_CIRCUIT_PROTECT
	if (is_in_uscp_mode() && CHARGER_REMOVED == di->charger_type) {
		uscp_plugout_wake_lock();
		schedule_delayed_work(&di->plugout_uscp_work, msecs_to_jiffies(WORK_DELAY_5000MS));
	} else {
		charge_send_uevent(di);
	}
#else
		charge_send_uevent(di);
#endif

#ifdef CONFIG_DIRECT_CHARGER
	}
	else
	{
		hwlog_info("%s ignore evnet : %ld\n", __func__, event);
	}
#endif
}
/**********************************************************
*  Function:       charge_usb_notifier_call
*  Description:    respond the charger_type events from USB PHY
*  Parameters:   usb_nb:usb notifier_block
*                      event:charger type event name
*                      data:unused
*  return value:  NOTIFY_OK-success or others
**********************************************************/
static int charge_usb_notifier_call(struct notifier_block *usb_nb,
				    unsigned long event, void *data)
{
	struct charge_device_info *di =
	    container_of(usb_nb, struct charge_device_info, usb_nb);
	bool filter_flag = TRUE;

	charge_wake_lock();

	filter_flag = charge_rename_charger_type((enum hisi_charger_type)event, di,FALSE);
	if(filter_flag)
	{
		hwlog_info("not use work,filter_flag=%d\n",filter_flag);
		return NOTIFY_OK;
	}

	charge_uevent_process(di, event);

	schedule_work(&di->usb_work);
	return NOTIFY_OK;
}
enum usb_charger_type charge_get_charger_type(void)
{
	struct charge_device_info *di = g_di;
	return di->charger_type;
}
#ifdef CONFIG_DIRECT_CHARGER
void direct_charger_connect_send_uevent(void)
{
	struct charge_device_info *di = g_di;
	di->charger_type = CHARGER_TYPE_STANDARD;
	di->charger_source = POWER_SUPPLY_TYPE_MAINS;
	charge_send_uevent(di);
}
void direct_charger_disconnect_update_charger_type(void)
{
	struct charge_device_info *di = g_di;
	di->charger_type = CHARGER_REMOVED;
	di->charger_source = POWER_SUPPLY_TYPE_BATTERY;
}
void direct_charger_disconnect_send_uevent(void)
{
	struct charge_device_info *di = g_di;
	charge_send_uevent(di);
}
void ignore_pluggin_and_pluggout_interrupt(void)
{
	struct charge_device_info *di = g_di;

	di->ignore_pluggin_and_plugout_flag = 1;
}
void restore_pluggin_pluggout_interrupt(void)
{
	struct charge_device_info *di = g_di;

	di->ignore_pluggin_and_plugout_flag = 0;
}
int get_direct_charge_flag(void)
{
	struct charge_device_info *di = g_di;

	if (NULL == di)
		return 0;
	return di->ignore_pluggin_and_plugout_flag;
}
#endif
/**********************************************************
*  Function:       charge_fault_notifier_call
*  Description:    respond the fault events from chargerIC
*  Parameters:   fault_nb:fault notifier_block
*                      event:fault event name
*                      data:unused
*  return value:  NOTIFY_OK-success or others
**********************************************************/
static int charge_fault_notifier_call(struct notifier_block *fault_nb,
				      unsigned long event, void *data)
{
	struct charge_device_info *di =
	    container_of(fault_nb, struct charge_device_info, fault_nb);

	di->charge_fault = (enum charge_fault_type)event;
	schedule_work(&di->fault_work);
	return NOTIFY_OK;
}


#ifdef CONFIG_TCPC_CLASS

static void charge_rename_pd_charger_type(enum hisi_charger_type type,
				       struct charge_device_info *di,
					bool ext_power)
{
	switch (type) {
	case PD_DPM_VBUS_TYPE_PD:
		di->charger_type = CHARGER_TYPE_PD;
		hwlog_info("%s is ext_power %d", __func__, ext_power);
		if(ext_power)
			di->charger_source = POWER_SUPPLY_TYPE_MAINS;
		else
			di->charger_source = POWER_SUPPLY_TYPE_USB;
		break;
	case PD_DPM_VBUS_TYPE_TYPEC:
		di->charger_type = CHARGER_TYPE_TYPEC;
		di->charger_source = POWER_SUPPLY_TYPE_MAINS;
		break;
	default:
		di->charger_type = CHARGER_REMOVED;
		di->charger_source = POWER_SUPPLY_TYPE_BATTERY;
		hwlog_info("%s default type %u", __func__, type);
		break;
	}
}


/**********************************************************
*  Function:       tcpc_notifier_call
*  Description:    respond the Type C port event from TCPC
*  Parameters:   tcpc_nb: tcpc notifier_block
*                      event:				PD_DPM_VBUS_TYPE_PD,
*								PD_DPM_VBUS_TYPE_TYPEC,
*								hisi_charger_type,
*                      data: pointer of struct tcp_notify
*  return value:  NOTIFY_OK-success or others
**********************************************************/
static int pd_dpm_notifier_call(struct notifier_block *tcpc_nb, unsigned long event, void *data)
{
	struct pd_dpm_vbus_state *vbus_state;
	struct charge_device_info *di = container_of(tcpc_nb, struct charge_device_info, tcpc_nb);

	if(PD_DPM_VBUS_TYPE_TYPEC == event)
		return NOTIFY_OK;

	charge_wake_lock();

	if(PD_DPM_VBUS_TYPE_PD == event)
	{
		vbus_state = (struct pd_dpm_vbus_state *) data;
		di->pd_input_current = vbus_state->ma;
		di->pd_charge_current = (vbus_state->mv * vbus_state->ma * charger_pd_cur_trans_ratio) / (100 * di->core_data->vterm);
		charge_rename_pd_charger_type(event, di, vbus_state->ext_power);
	}
	else
	{
		charge_rename_charger_type(event, di,FALSE);
	}

	charge_uevent_process(di, event);

	mutex_lock(&di->tcpc_otg_lock);
	if (event == PLEASE_PROVIDE_POWER) {
		hwlog_info("case = USB_EVENT_OTG_ID-> (IM)\n");
		charge_start_usb_otg(di);
		mutex_unlock(&di->tcpc_otg_lock);
	} else if (di->charger_type == CHARGER_REMOVED && otg_flag) {
		hwlog_info("case = USB_EVENT_NONE-> (IM)\n");
		charge_stop_charging(di);
		mutex_unlock(&di->tcpc_otg_lock);
	} else {
		mutex_unlock(&di->tcpc_otg_lock);
		schedule_work(&di->usb_work);
	}

	return NOTIFY_OK;
}
#endif



/**********************************************************
*  Function:       charge_check_input_dpm_state
*  Description:    check charger whether VINDPM or IINDPM
*  Parameters:     NULL
*  return value:   1 means charger VINDPM or IINDPM
*                  0 means charger NoT DPM
*                  -1 means chargeIC not support this function
**********************************************************/
int charge_check_input_dpm_state(void)
{
	if (NULL == g_ops || NULL == g_ops->check_input_dpm_state) {
		return -1;
	}
	return g_ops->check_input_dpm_state();
}

#if CONFIG_SYSFS
#define CHARGE_SYSFS_FIELD(_name, n, m, store)                \
{                                                   \
    .attr = __ATTR(_name, m, charge_sysfs_show, store),    \
    .name = CHARGE_SYSFS_##n,          \
}

#define CHARGE_SYSFS_FIELD_RW(_name, n)               \
	CHARGE_SYSFS_FIELD(_name, n, S_IWUSR | S_IRUGO, charge_sysfs_store)

#define CHARGE_SYSFS_FIELD_RO(_name, n)               \
	CHARGE_SYSFS_FIELD(_name, n, S_IRUGO, NULL)

static ssize_t charge_sysfs_show(struct device *dev,
				 struct device_attribute *attr, char *buf);
static ssize_t charge_sysfs_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count);

struct charge_sysfs_field_info {
	struct device_attribute attr;
	u8 name;
};

static struct charge_sysfs_field_info charge_sysfs_field_tbl[] = {
	CHARGE_SYSFS_FIELD_RW(adc_conv_rate, ADC_CONV_RATE),
	CHARGE_SYSFS_FIELD_RW(iin_thermal, IIN_THERMAL),
	CHARGE_SYSFS_FIELD_RW(ichg_thermal, ICHG_THERMAL),
	CHARGE_SYSFS_FIELD_RW(iin_thermal_aux, IIN_THERMAL_AUX),
	CHARGE_SYSFS_FIELD_RW(ichg_thermal_aux, ICHG_THERMAL_AUX),
	/*iin_runningtest will be used for running test and audio test */
	CHARGE_SYSFS_FIELD_RW(iin_runningtest, IIN_RUNNINGTEST),
	CHARGE_SYSFS_FIELD_RW(ichg_runningtest, ICHG_RUNNINGTEST),
	CHARGE_SYSFS_FIELD_RW(enable_charger, ENABLE_CHARGER),
	CHARGE_SYSFS_FIELD_RW(limit_charging, LIMIT_CHARGING),
	CHARGE_SYSFS_FIELD_RW(regulation_voltage, REGULATION_VOLTAGE),
	CHARGE_SYSFS_FIELD_RW(shutdown_q4, BATFET_DISABLE),
	CHARGE_SYSFS_FIELD_RW(shutdown_watchdog, WATCHDOG_DISABLE),
	CHARGE_SYSFS_FIELD_RO(chargelog, CHARGELOG),
	CHARGE_SYSFS_FIELD_RO(chargelog_head, CHARGELOG_HEAD),
	CHARGE_SYSFS_FIELD_RO(Ibus, IBUS),
	CHARGE_SYSFS_FIELD_RO(Vbus, VBUS),
	CHARGE_SYSFS_FIELD_RW(enable_hiz, HIZ),
	CHARGE_SYSFS_FIELD_RO(chargerType, CHARGE_TYPE),
	CHARGE_SYSFS_FIELD_RO(charge_done_status, CHARGE_DONE_STATUS),
	CHARGE_SYSFS_FIELD_RW(charge_done_sleep_status, CHARGE_DONE_SLEEP_STATUS),
	CHARGE_SYSFS_FIELD_RW(inputcurrent, INPUTCURRENT),
	CHARGE_SYSFS_FIELD_RO(voltage_sys, VOLTAGE_SYS),
	CHARGE_SYSFS_FIELD_RO(bootloader_charger_info, BOOTLOADER_CHARGER_INFO),
	CHARGE_SYSFS_FIELD_RO(ichg_reg, ICHG_REG),
	CHARGE_SYSFS_FIELD_RO(ichg_adc, ICHG_ADC),
	CHARGE_SYSFS_FIELD_RO(ichg_reg_aux, ICHG_REG_AUX),
	CHARGE_SYSFS_FIELD_RO(ichg_adc_aux, ICHG_ADC_AUX),
	CHARGE_SYSFS_FIELD_RW(vr_charger_type, VR_CHARGER_TYPE),
	CHARGE_SYSFS_FIELD_RW(support_ico,    SUPPORT_ICO),
	CHARGE_SYSFS_FIELD_RW(water_intrused,    WATER_INTRUSED),
	CHARGE_SYSFS_FIELD_RO(charge_term_volt_design, CHARGE_TERM_VOLT_DESIGN),
	CHARGE_SYSFS_FIELD_RO(charge_term_curr_design, CHARGE_TERM_CURR_DESIGN),
	CHARGE_SYSFS_FIELD_RO(charge_term_volt_setting, CHARGE_TERM_VOLT_SETTING),
	CHARGE_SYSFS_FIELD_RO(charge_term_curr_setting, CHARGE_TERM_CURR_SETTING),
};

static struct attribute *charge_sysfs_attrs[ARRAY_SIZE(charge_sysfs_field_tbl) + 1];

static const struct attribute_group charge_sysfs_attr_group = {
	.attrs = charge_sysfs_attrs,
};

/**********************************************************
*  Function:       charge_sysfs_init_attrs
*  Description:    initialize charge_sysfs_attrs[] for charge attribute
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void charge_sysfs_init_attrs(void)
{
	int i, limit = ARRAY_SIZE(charge_sysfs_field_tbl);

	for (i = 0; i < limit; i++) {
		charge_sysfs_attrs[i] = &charge_sysfs_field_tbl[i].attr.attr;
	}
	charge_sysfs_attrs[limit] = NULL;	/* Has additional entry for this */
}

/**********************************************************
*  Function:       charge_sysfs_field_lookup
*  Description:    get the current device_attribute from charge_sysfs_field_tbl by attr's name
*  Parameters:   name:device attribute name
*  return value:  charge_sysfs_field_tbl[]
**********************************************************/
static struct charge_sysfs_field_info *charge_sysfs_field_lookup(const char *name)
{
	int i, limit = ARRAY_SIZE(charge_sysfs_field_tbl);

	for (i = 0; i < limit; i++) {
		if (!strncmp
		    (name, charge_sysfs_field_tbl[i].attr.attr.name,
		     strlen(name)))
			break;
	}
	if (i >= limit)
		return NULL;

	return &charge_sysfs_field_tbl[i];
}

/**********************************************************
*  Function:       charge_sysfs_show
*  Description:    show the value for all charge device's node
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*  return value:  0-sucess or others-fail
**********************************************************/
static ssize_t charge_sysfs_show(struct device *dev,
				 struct device_attribute *attr, char *buf)
{
	struct charge_sysfs_field_info *info = NULL;
	struct charge_device_info *di = dev_get_drvdata(dev);
	int ret;

	info = charge_sysfs_field_lookup(attr->attr.name);
	if (!info)
		return -EINVAL;

	switch (info->name) {
	case CHARGE_SYSFS_ADC_CONV_RATE:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.adc_conv_rate);
	case CHARGE_SYSFS_IIN_THERMAL:
		if (!di->is_dual_charger)
			return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.iin_thl);
		else
			return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.iin_thl_main);
	case CHARGE_SYSFS_ICHG_THERMAL:
		if (!di->is_dual_charger)
			return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.ichg_thl);
		else
			return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.ichg_thl_main);
	case CHARGE_SYSFS_IIN_THERMAL_AUX:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.iin_thl_aux);
	case CHARGE_SYSFS_ICHG_THERMAL_AUX:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.ichg_thl_aux);
	case CHARGE_SYSFS_ICHG_REG:
		if (!di->is_dual_charger)
			return -EINVAL;
		return snprintf(buf, PAGE_SIZE, "%d\n", di->ops->get_ichg_reg(MAIN_CHARGER));
	case CHARGE_SYSFS_ICHG_ADC:
		if (!di->is_dual_charger)
			return -EINVAL;
		return snprintf(buf, PAGE_SIZE, "%d\n", di->ops->get_ichg_adc(MAIN_CHARGER));
	case CHARGE_SYSFS_ICHG_REG_AUX:
		if (!di->is_dual_charger)
			return -EINVAL;
		return snprintf(buf, PAGE_SIZE, "%d\n", di->ops->get_ichg_reg(AUX_CHARGER));
	case CHARGE_SYSFS_ICHG_ADC_AUX:
		if (!di->is_dual_charger)
			return -EINVAL;
		return snprintf(buf, PAGE_SIZE, "%d\n", di->ops->get_ichg_adc(AUX_CHARGER));
	case CHARGE_SYSFS_IIN_RUNNINGTEST:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.iin_rt);
	case CHARGE_SYSFS_ICHG_RUNNINGTEST:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.ichg_rt);
	case CHARGE_SYSFS_ENABLE_CHARGER:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.charge_enable);
	case CHARGE_SYSFS_LIMIT_CHARGING:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.charge_limit);
	case CHARGE_SYSFS_REGULATION_VOLTAGE:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.vterm_rt);
	case CHARGE_SYSFS_BATFET_DISABLE:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.batfet_disable);
	case CHARGE_SYSFS_WATCHDOG_DISABLE:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.wdt_disable);
	case CHARGE_SYSFS_CHARGELOG:
		if (BAT_BOARD_UDP == is_board_type) {
			ret = snprintf(buf, PAGE_SIZE, "%s\n", "");
			return ret;
		}
		mutex_lock(&di->sysfs_data.dump_reg_lock);
		di->ops->dump_register(di->sysfs_data.reg_value);
		ret = snprintf(buf, PAGE_SIZE, "%s\n", di->sysfs_data.reg_value);
		mutex_unlock(&di->sysfs_data.dump_reg_lock);
		return ret;
	case CHARGE_SYSFS_CHARGELOG_HEAD:
		mutex_lock(&di->sysfs_data.dump_reg_head_lock);
		di->ops->get_register_head(di->sysfs_data.reg_head);
		ret = snprintf(buf, PAGE_SIZE, "%s\n", di->sysfs_data.reg_head);
		mutex_unlock(&di->sysfs_data.dump_reg_head_lock);
		return ret;
	case CHARGE_SYSFS_IBUS:
		di->sysfs_data.ibus = 0;
		if (di->ops->get_ibus)	/*this is an optional interface for charger*/
			di->sysfs_data.ibus = di->ops->get_ibus();
		return snprintf(buf, PAGE_SIZE, "%d\n", di->sysfs_data.ibus);
	case CHARGE_SYSFS_VBUS:
		di->sysfs_data.vbus = 0;
		if (di->ops->get_vbus)	 { /*this is an optional interface for charger*/
			ret = di->ops->get_vbus(&di->sysfs_data.vbus);
			if (ret)
				hwlog_err("[%s]vbus read failed \n", __func__);
		}
		return snprintf(buf, PAGE_SIZE, "%d\n", di->sysfs_data.vbus);
	case CHARGE_SYSFS_HIZ:
		return snprintf(buf, PAGE_SIZE, "%u\n", di->sysfs_data.hiz_enable);
	case CHARGE_SYSFS_CHARGE_TYPE:
		return snprintf(buf, PAGE_SIZE, "%d\n", di->charger_type);
	case CHARGE_SYSFS_CHARGE_DONE_STATUS:
		return snprintf(buf, PAGE_SIZE, "%d\n", di->sysfs_data.charge_done_status);
	case CHARGE_SYSFS_CHARGE_DONE_SLEEP_STATUS:
		return snprintf(buf, PAGE_SIZE, "%d\n", di->sysfs_data.charge_done_sleep_status);
	case CHARGE_SYSFS_INPUTCURRENT:
		return snprintf(buf, PAGE_SIZE, "%d\n", di->sysfs_data.inputcurrent);
		break;
	case CHARGE_SYSFS_SUPPORT_ICO:
		return snprintf(buf,PAGE_SIZE, "%d\n", di->sysfs_data.support_ico);
	case CHARGE_SYSFS_WATER_INTRUSED:
		ret = snprintf(buf,PAGE_SIZE, "%d\n", di->sysfs_data.water_intrused);
		if(1 == di->sysfs_data.water_intrused)
			di->sysfs_data.water_intrused = 0;
		return ret;
	case CHARGE_SYSFS_VOLTAGE_SYS:
		di->sysfs_data.voltage_sys = 0;
		if (di->ops->get_vbat_sys)
			di->sysfs_data.voltage_sys = di->ops->get_vbat_sys();
		return snprintf(buf, PAGE_SIZE, "%d\n", di->sysfs_data.voltage_sys);
		break;
	case CHARGE_SYSFS_BOOTLOADER_CHARGER_INFO:
		mutex_lock(&di->sysfs_data.bootloader_info_lock);
		if (hisi_charger_info.info_vaild) {
			dump_bootloader_info(di->sysfs_data.bootloader_info);
			ret =
			    snprintf(buf, PAGE_SIZE, "%s\n", di->sysfs_data.bootloader_info);
		} else {
			ret = snprintf(buf, PAGE_SIZE, "\n");
		}
		mutex_unlock(&di->sysfs_data.bootloader_info_lock);
		return ret;
	case CHARGE_SYSFS_VR_CHARGER_TYPE:
		return snprintf(buf, PAGE_SIZE, "%d\n", di->sysfs_data.vr_charger_type);
	case CHARGE_SYSFS_CHARGE_TERM_VOLT_DESIGN:
		return snprintf(buf, PAGE_SIZE, "%d\n", di->core_data->vterm);
	case CHARGE_SYSFS_CHARGE_TERM_CURR_DESIGN:
		return snprintf(buf, PAGE_SIZE, "%d\n", di->core_data->iterm);
	case CHARGE_SYSFS_CHARGE_TERM_VOLT_SETTING:
		return snprintf(buf, PAGE_SIZE, "%d\n",
			((di->core_data->vterm < di->sysfs_data.vterm_rt) ? di->core_data->vterm : di->sysfs_data.vterm_rt));
	case CHARGE_SYSFS_CHARGE_TERM_CURR_SETTING:
		return snprintf(buf, PAGE_SIZE, "%d\n", di->core_data->iterm);
	default:
		hwlog_err("(%s)NODE ERR!!HAVE NO THIS NODE:(%d)\n", __func__, info->name);
		break;
	}
	return 0;
}

/**********************************************************
*  Function:       charge_sysfs_store
*  Description:    set the value for charge_data's node which is can be written
*  Parameters:   dev:device
*                      attr:device_attribute
*                      buf:string of node value
*                      count:unused
*  return value:  0-sucess or others-fail
**********************************************************/
static ssize_t charge_sysfs_store(struct device *dev,
				  struct device_attribute *attr,
				  const char *buf, size_t count)
{
	struct charge_sysfs_field_info *info = NULL;
	struct charge_device_info *di = dev_get_drvdata(dev);
	long val = 0;
	enum charge_status_event events = VCHRG_POWER_NONE_EVENT;

	info = charge_sysfs_field_lookup(attr->attr.name);
	if (!info)
		return -EINVAL;

	switch (info->name) {
		/*NOTICE:
		   it will be charging with default current when the current node has been set to 0/1,
		   include iin_thermal/ichg_thermal/iin_runningtest/ichg_runningtest node
		 */
	case CHARGE_SYSFS_ADC_CONV_RATE:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
			return -EINVAL;
		di->sysfs_data.adc_conv_rate = val;
		if (di->ops->set_adc_conv_rate)
			di->ops->set_adc_conv_rate(di->sysfs_data.adc_conv_rate);
		hwlog_info("set adc conversion rate mode = %d\n",
			   di->sysfs_data.adc_conv_rate);
		break;
	case CHARGE_SYSFS_IIN_THERMAL:
#ifndef CONFIG_HLTHERM_RUNTEST
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 3000))
			return -EINVAL;
		if (!di->is_dual_charger) {
			if ((val == 0) || (val == 1))
				di->sysfs_data.iin_thl = di->core_data->iin_max;
			else if ((val > 1) && (val <= 100))
				di->sysfs_data.iin_thl = 100;
			else
				di->sysfs_data.iin_thl = val;

			if (di->input_current > di->sysfs_data.iin_thl)
				charge_set_input_current(di->sysfs_data.
							   iin_thl);
			hwlog_info("THERMAL set input current = %d\n",
				   di->sysfs_data.iin_thl);
		} else {
			if ((val == 0) || (val == 1))
				di->sysfs_data.iin_thl_main = di->core_data->iin_max / 2;
			else if ((val > 1) && (val <= 100))
				di->sysfs_data.iin_thl_main = 100;
			else
				di->sysfs_data.iin_thl_main = val;

			di->sysfs_data.iin_thl =
				di->sysfs_data.iin_thl_main + di->sysfs_data.iin_thl_aux;

			di->ops->set_input_current_thermal(di->sysfs_data.iin_thl_main,
							   di->sysfs_data.iin_thl_aux);
			hwlog_info("THERMAL set input current main = %d\n",
				   di->sysfs_data.iin_thl_main);
		}
#endif
		break;
	case CHARGE_SYSFS_ICHG_THERMAL:
#ifndef CONFIG_HLTHERM_RUNTEST
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 3000))
			return -EINVAL;
		if (!di->is_dual_charger) {
			if ((val == 0) || (val == 1))
				di->sysfs_data.ichg_thl = di->core_data->ichg_max;
			else if ((val > 1) && (val <= 500)) {
				hwlog_info
				    ("THERMAL set charge current = %ld is less than 500mA\n", val);
				di->sysfs_data.ichg_thl = 500;
			} else
				di->sysfs_data.ichg_thl = val;

			if (di->charge_current > di->sysfs_data.ichg_thl)
				di->ops->set_charge_current(di->sysfs_data.ichg_thl);
			hwlog_info("THERMAL set charge current = %d\n",
				   di->sysfs_data.ichg_thl);
		} else {
			if ((val == 0) || (val == 1))
				di->sysfs_data.ichg_thl_main =
				    di->core_data->ichg_max;
			else
				di->sysfs_data.ichg_thl_main = val;

			di->sysfs_data.ichg_thl =
				di->sysfs_data.ichg_thl_main + di->sysfs_data.ichg_thl_aux;
			if (di->sysfs_data.ichg_thl <= 500) {
				hwlog_info
				    ("THERMAL set charge current = %u is less than 500mA, main = %u, aux = %u\n",
				     di->sysfs_data.ichg_thl,
				     di->sysfs_data.ichg_thl_main,
				     di->sysfs_data.ichg_thl_aux);
				di->sysfs_data.ichg_thl = 500;
			}
			di->ops->set_charge_current_thermal(di->sysfs_data.ichg_thl_main,
							    di->sysfs_data.ichg_thl_aux);
			hwlog_info("THERMAL set charge current main = %d\n",
				   di->sysfs_data.ichg_thl_main);
		}
#endif
		break;
	case CHARGE_SYSFS_IIN_THERMAL_AUX:
#ifndef CONFIG_HLTHERM_RUNTEST
		if (!di->is_dual_charger)
			break;
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 3000))
			return -EINVAL;
		if ((val == 0) || (val == 1))
			di->sysfs_data.iin_thl_aux = di->core_data->iin_max / 2;
		else if ((val > 1) && (val <= 100))
			di->sysfs_data.iin_thl_aux = 100;
		else
			di->sysfs_data.iin_thl_aux = val;

		di->sysfs_data.iin_thl =
		    di->sysfs_data.iin_thl_main + di->sysfs_data.iin_thl_aux;

		di->ops->set_input_current_thermal(di->sysfs_data.iin_thl_main,
						   di->sysfs_data.iin_thl_aux);
		hwlog_info("THERMAL set input current aux = %d\n",
			   di->sysfs_data.iin_thl_aux);
#endif
		break;
	case CHARGE_SYSFS_ICHG_THERMAL_AUX:
#ifndef CONFIG_HLTHERM_RUNTEST
		if (!di->is_dual_charger)
			break;
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 3000))
			return -EINVAL;
		if ((val == 0) || (val == 1))
			di->sysfs_data.ichg_thl_aux = di->core_data->ichg_max;
		else
			di->sysfs_data.ichg_thl_aux = val;

		di->sysfs_data.ichg_thl =
		    di->sysfs_data.ichg_thl_main + di->sysfs_data.ichg_thl_aux;
		if (di->sysfs_data.ichg_thl <= 500) {
			hwlog_info
			    ("THERMAL set charge current = %u is less than 500mA, main = %u, aux = %u\n",
			     di->sysfs_data.ichg_thl,
			     di->sysfs_data.ichg_thl_main,
			     di->sysfs_data.ichg_thl_aux);
			di->sysfs_data.ichg_thl = 500;
		}
		di->ops->set_charge_current_thermal(di->sysfs_data.ichg_thl_main,
						    di->sysfs_data.ichg_thl_aux);
		hwlog_info("THERMAL set charge current aux = %d\n",
			   di->sysfs_data.ichg_thl_aux);
#endif
		break;
	case CHARGE_SYSFS_IIN_RUNNINGTEST:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 3000))
			return -EINVAL;
		if ((val == 0) || (val == 1))
			di->sysfs_data.iin_rt = di->core_data->iin_max;
		else if ((val > 1) && (val <= 100))
			di->sysfs_data.iin_rt = 100;
		else
			di->sysfs_data.iin_rt = val;

		if (di->input_current > di->sysfs_data.iin_rt)
			charge_set_input_current(di->sysfs_data.iin_rt);
		hwlog_info("RUNNINGTEST set input current = %d\n",
			   di->sysfs_data.iin_rt);
		break;
	case CHARGE_SYSFS_ICHG_RUNNINGTEST:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 3000))
			return -EINVAL;
		if ((val == 0) || (val == 1))
			di->sysfs_data.ichg_rt = di->core_data->ichg_max;
		else if ((val > 1) && (val <= 205))
			di->sysfs_data.ichg_rt = 205;
		else
			di->sysfs_data.ichg_rt = val;

		if (di->charge_current > di->sysfs_data.ichg_rt)
			di->ops->set_charge_current(di->sysfs_data.ichg_rt);
		hwlog_info("RUNNINGTEST set charge current = %d\n",
			   di->sysfs_data.ichg_rt);
		break;
	case CHARGE_SYSFS_ENABLE_CHARGER:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
			return -EINVAL;
		di->sysfs_data.charge_enable = val;
		di->sysfs_data.charge_limit = TRUE;
		/*why should send events in this command?
		   because it will get the /sys/class/power_supply/Battery/status immediately
		   to check if the enable/disable command set successfully or not in some product line station
		 */
		if (di->sysfs_data.charge_enable)
			events = VCHRG_START_CHARGING_EVENT;
		else
			events = VCHRG_NOT_CHARGING_EVENT;
#ifdef CONFIG_DIRECT_CHARGER
		if (di->ignore_pluggin_and_plugout_flag)
		{
			hwlog_info("ignore RUNNINGTEST set charge enable = %d\n", di->sysfs_data.charge_enable);
		}
		else
		{
#endif
			di->ops->set_charge_enable(di->sysfs_data.charge_enable);
			hisi_coul_charger_event_rcv(events);
			hwlog_info("RUNNINGTEST set charge enable = %d\n", di->sysfs_data.charge_enable);
#ifdef CONFIG_DIRECT_CHARGER
		}
#endif
		break;
	case CHARGE_SYSFS_LIMIT_CHARGING:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
			return -EINVAL;
		di->sysfs_data.charge_limit = val;
		hwlog_info("PROJECTMUNE set limit charge enable = %d\n",
			   di->sysfs_data.charge_limit);
		break;
	case CHARGE_SYSFS_REGULATION_VOLTAGE:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 3200) || (val > 4400))
			return -EINVAL;
		di->sysfs_data.vterm_rt = val;
		di->ops->set_terminal_voltage(di->sysfs_data.vterm_rt);
		hwlog_info("RUNNINGTEST set terminal voltage = %d\n",
			   di->sysfs_data.vterm_rt);
		break;
	case CHARGE_SYSFS_BATFET_DISABLE:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
			return -EINVAL;
		di->sysfs_data.batfet_disable = val;
		if (1 == val)
			charge_set_input_current(CHARGE_CURRENT_2000_MA);
		di->ops->set_batfet_disable(di->sysfs_data.batfet_disable);
		hwlog_info("RUNNINGTEST set batfet disable = %d\n",
			   di->sysfs_data.batfet_disable);
		break;
	case CHARGE_SYSFS_WATCHDOG_DISABLE:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
			return -EINVAL;
		di->sysfs_data.wdt_disable = val;
		if (val == 1)
			di->ops->set_watchdog_timer(WATCHDOG_TIMER_DISABLE);
		hwlog_info("RUNNINGTEST set wdt disable = %d\n",
			   di->sysfs_data.wdt_disable);
		break;
	case CHARGE_SYSFS_HIZ:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
			return -EINVAL;
		di->sysfs_data.hiz_enable = val;
		if (di->ops->set_charger_hiz)
			di->ops->set_charger_hiz(di->sysfs_data.hiz_enable);
		hwlog_info("RUNNINGTEST set hiz enable = %d\n",
			   di->sysfs_data.hiz_enable);
		break;
	case CHARGE_SYSFS_CHARGE_DONE_STATUS:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 10))
			return -EINVAL;
		di->sysfs_data.charge_done_status = val;
		break;
	case CHARGE_SYSFS_CHARGE_DONE_SLEEP_STATUS:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 10))
			return -EINVAL;
		di->sysfs_data.charge_done_sleep_status = val;
		break;
	case CHARGE_SYSFS_INPUTCURRENT:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 100) || (val > 2000))
			return -EINVAL;
		di->sysfs_data.inputcurrent = val;
		charge_set_input_current(di->sysfs_data.inputcurrent);
		hwlog_info("set input currrent is: %ld\n", val);
		break;
	case CHARGE_SYSFS_SUPPORT_ICO:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
			return -EINVAL;
		di->sysfs_data.support_ico = val;
		hwlog_info("SUPPORT_ICO = %d\n", di->sysfs_data.support_ico);
		break;
	case CHARGE_SYSFS_WATER_INTRUSED:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 1))
			return -EINVAL;
		di->sysfs_data.water_intrused = val;
		hwlog_info("set water_intrused = %d\n", di->sysfs_data.water_intrused);
		break;
	case CHARGE_SYSFS_VR_CHARGER_TYPE:
		if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 4))
			return -EINVAL;
		di->sysfs_data.vr_charger_type = val;
		hwlog_info("Set vr_charger_type = %d\n",
			   di->sysfs_data.vr_charger_type);
		charge_process_vr_charge_event(di);
		break;
	default:
		hwlog_err("(%s)NODE ERR!!HAVE NO THIS NODE:(%d)\n", __func__, info->name);
		break;
	}
	return count;
}

/**********************************************************
*  Function:       charge_check_charger_plugged
*  Description:    detect whether USB or adaptor is plugged
*  Parameters:     NULL
*  return value:    1 means USB or adpator plugged
*                   0 means USB or adaptor not plugged
*                   -1 means chargeIC not support this function
**********************************************************/
int charge_check_charger_plugged(void)
{
	if (NULL == g_ops || NULL == g_ops->check_charger_plugged) {
		return -1;
	}
	return g_ops->check_charger_plugged();
}

bool charge_check_charger_ts(void)
{
    return ts_flag;
}

bool charge_check_charger_otg_state(void)
{
    return otg_flag;
}

/**********************************************************
*  Function:       charge_sysfs_create_group
*  Description:    create the charge device sysfs group
*  Parameters:   di:charge_device_info
*  return value:  0-sucess or others-fail
**********************************************************/
static int charge_sysfs_create_group(struct charge_device_info *di)
{
	charge_sysfs_init_attrs();
	return sysfs_create_group(&di->dev->kobj, &charge_sysfs_attr_group);
}

/**********************************************************
*  Function:       charge_sysfs_remove_group
*  Description:    remove the charge device sysfs group
*  Parameters:   di:charge_device_info
*  return value:  NULL
**********************************************************/
static inline void charge_sysfs_remove_group(struct charge_device_info *di)
{
	sysfs_remove_group(&di->dev->kobj, &charge_sysfs_attr_group);
}
#else
static int charge_sysfs_create_group(struct charge_device_info *di)
{
	return 0;
}

static inline void charge_sysfs_remove_group(struct charge_device_info *di)
{
}
#endif
/**********************************************************
*  Function:       charge_ops_register
*  Description:    register the handler ops for chargerIC
*  Parameters:   ops:operations interface of charge device
*  return value:  0-sucess or others-fail
**********************************************************/
int charge_ops_register(struct charge_device_ops *ops)
{
	int ret = 0;

	if (ops != NULL) {
		g_ops = ops;
	} else {
		hwlog_err("charge ops register fail!\n");
		ret = -EPERM;
	}
	return ret;
}

int charge_switch_ops_register(struct charge_switch_ops *ops)
{
	int ret = 0;

	if (ops != NULL) {
		g_sw_ops = ops;
	} else {
		hwlog_err("charge switch ops register fail!\n");
		ret = -EPERM;
	}
	return ret;
}

/**********************************************************
*  Function:       fcp_adpter_ops_register
*  Description:    register the handler ops for fcp adpter
*  Parameters:   ops:operations interface of fcp adpter
*  return value:  0-sucess or others-fail
**********************************************************/
int fcp_adapter_ops_register(struct fcp_adapter_device_ops *ops)
{
	int ret = 0;

	if (ops != NULL) {
		g_fcp_ops = ops;
	} else {
		hwlog_err("fcp ops register fail!\n");
		ret = -EPERM;
	}
	return ret;
}
/**********************************************************
*  Function:       charge_parse_dts
*  Description:    parse dts
*  Parameters:   charge_device_info di
*  return value:  NULL
**********************************************************/
void charge_parse_dts(struct charge_device_info *di)
{
	int ret = 0;
	ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,dual_charger"),
			"is_dual_charger", &di->is_dual_charger);
	if (ret){
		hwlog_err("get is_dual_charger fail!\n");
		di->is_dual_charger = 0;
	}

	ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,charger"),
			"water_check_enabled", &di->water_check_enabled);
	if (ret)
		hwlog_err("get water_check_enabled fail!\n");

	charge_done_sleep_dts =
		of_property_read_bool(of_find_compatible_node(NULL, NULL, "huawei,charger"),
			"charge_done_sleep_enabled");

	ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,hisi_bci_battery"),
			"battery_board_type", &is_board_type);
	if (ret) {
		hwlog_err("get battery_board_type fail!\n");
		is_board_type = BAT_BOARD_ASIC;
	}

	ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,charger"), \
			"support_usb_nonstandard_ico", &di->support_usb_nonstandard_ico);
	if (ret) {
		hwlog_err("get support_usb_nonstandard_ico fail!\n");
		di->support_usb_nonstandard_ico = 0;
	}
	hwlog_info("support_usb_nonstandard_ico = %d\n", di->support_usb_nonstandard_ico);

	ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,charger"), \
			"support_standard_ico", &di->support_standard_ico);
	if (ret) {
		hwlog_err("get support_standard_ico fail!\n");
		di->support_standard_ico = 0;
	}
	hwlog_info("support_standard_ico = %d\n", di->support_standard_ico);

	ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,charger"), \
			"ico_all_the_way", &di->ico_all_the_way);
	if (ret) {
		hwlog_err("get ico_all_the_way fail!\n");
		di->ico_all_the_way = 0;
	}
	hwlog_info("ico_all_the_way = %d\n", di->ico_all_the_way);

	ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,charger"), \
			"fcp_vindpm", &di->fcp_vindpm);
	if (ret) {
		hwlog_err("get fcp_vindpm fail!\n");
		di->fcp_vindpm = CHARGE_VOLTAGE_4600_MV;
	}
	hwlog_info("fcp_vindpm = %d\n", di->fcp_vindpm);

	ret = of_property_read_u32(of_find_compatible_node(NULL, NULL, "huawei,charger"),
                        "pd_cur_trans_ratio", &charger_pd_cur_trans_ratio);
        if (ret) {
                hwlog_err("get charger_pd_cur_trans_ratio fail!\n");
        }
}
/**********************************************************
*  Function:       charge_probe
*  Description:    chargre module probe
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
static int charge_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct charge_device_info *di;
	enum hisi_charger_type type = hisi_get_charger_type();
	struct class *power_class = NULL;
	struct device_node *hw_charger_node;
	unsigned long local_event;
        struct pd_dpm_vbus_state local_state;

	di = kzalloc(sizeof(*di), GFP_KERNEL);
	if (!di) {
		hwlog_err("alloc di failed\n");
		return -ENOMEM;
	}
	di->core_data = charge_core_get_params();
	if (NULL == di->core_data){
	    hwlog_err("di->core_data is NULL\n");
	    ret = -EINVAL;
	    goto charge_fail_0;
	}
	di->dev = &pdev->dev;
	di->ops = g_ops;
	di->sw_ops = g_sw_ops;
	di->fcp_ops = g_fcp_ops;
	di->pmu_ovp_detect_flag  = 0;
	if ((NULL == di->ops) || (di->ops->chip_init == NULL)
	    || (di->ops->set_input_current == NULL)
	    || (di->ops->set_charge_current == NULL)
	    || (di->ops->set_charge_enable == NULL)
	    || (di->ops->set_otg_enable == NULL)
	    || (di->ops->set_terminal_current == NULL)
	    || (di->ops->set_terminal_voltage == NULL)
	    || (di->ops->dump_register == NULL)
	    || (di->ops->get_charge_state == NULL)
	    || (di->ops->reset_watchdog_timer == NULL)
	    || (di->ops->get_register_head == NULL)) {
		hwlog_err("charge ops is NULL!\n");
		ret = -EINVAL;
		goto charge_fail_1;
	}

	platform_set_drvdata(pdev, di);

	wake_lock_init(&charge_lock, WAKE_LOCK_SUSPEND, "charge_wakelock");
	wake_lock_init(&uscp_plugout_lock, WAKE_LOCK_SUSPEND, "uscp_plugout_lock");
	wake_lock_init(&stop_charge_lock, WAKE_LOCK_SUSPEND, "stop_charge_wakelock");

	di->vbat_ovp_handle_wq = create_singlethread_workqueue("vbat_ovp_handle_wq");
	INIT_WORK(&di->vbat_ovp_work, vbat_ovp_detect_work);
	INIT_DELAYED_WORK(&di->charge_work, charge_monitor_work);
	INIT_DELAYED_WORK(&di->otg_work, charge_otg_work);
	INIT_WORK(&di->usb_work, charge_usb_work);
	INIT_WORK(&di->fault_work, charge_fault_work);
	INIT_WORK(&resume_wakelock_work, charge_resume_wakelock_work);
#ifdef  CONFIG_HUAWEI_USB_SHORT_CIRCUIT_PROTECT
	INIT_DELAYED_WORK(&di->plugout_uscp_work, uscp_plugout_send_uevent);
#endif

#ifdef CONFIG_TCPC_CLASS

	hw_charger_node =
	    of_find_compatible_node(NULL, NULL, "huawei,charger");
	if (hw_charger_node) {
		if(of_property_read_u32(hw_charger_node, "pd_support", &charger_pd_support))
		{
			hwlog_err("get pd_support fail!\n");
		}

		hwlog_info("charger_pd_support = %d \n",charger_pd_support);
	} else {
		hwlog_err("get huawei,charger fail!\n");
	}

	if(charger_pd_support)
	{
		mutex_init(&di->tcpc_otg_lock);
		hwlog_info("Register pd_dpm notifier\n");

		di->tcpc_nb.notifier_call = pd_dpm_notifier_call;
		ret = register_pd_dpm_notifier(&di->tcpc_nb);
		if (ret < 0)
		{
			hwlog_err("register_pd_dpm_notifier failed\n");
		}
		else
		{
			hwlog_info("register_pd_dpm_notifier OK\n");
		}
	}
	else
	{
		di->usb_nb.notifier_call = charge_usb_notifier_call;
		ret = hisi_charger_type_notifier_register(&di->usb_nb);
		if (ret < 0) {
			hwlog_err("hisi_charger_type_notifier_register failed\n");
			goto charge_fail_2;
		}
	}

#else
	hwlog_info("Register usb notifier\n");
	di->usb_nb.notifier_call = charge_usb_notifier_call;
	ret = hisi_charger_type_notifier_register(&di->usb_nb);
	if (ret < 0) {
		hwlog_err("hisi_charger_type_notifier_register failed\n");
		goto charge_fail_2;
	}
#endif

	di->fault_nb.notifier_call = charge_fault_notifier_call;
	ret =
	    atomic_notifier_chain_register(&fault_notifier_list, &di->fault_nb);
	if (ret < 0) {
		hwlog_err("charge_fault_register_notifier failed\n");
		goto charge_fail_2;
	}

	di->sysfs_data.adc_conv_rate = 0;
	di->sysfs_data.iin_thl = di->core_data->iin_max;
	di->sysfs_data.ichg_thl = di->core_data->ichg_max;
	di->sysfs_data.iin_thl_main = di->core_data->iin_max / 2;
	di->sysfs_data.ichg_thl_main = di->core_data->ichg_max;
	di->sysfs_data.iin_thl_aux = di->core_data->iin_max / 2;
	di->sysfs_data.ichg_thl_aux = di->core_data->ichg_max;
	di->sysfs_data.iin_rt = di->core_data->iin_max;
	di->sysfs_data.ichg_rt = di->core_data->ichg_max;
	di->sysfs_data.vterm_rt = hisi_battery_vbat_max();
	di->sysfs_data.charge_enable = TRUE;
	di->sysfs_data.batfet_disable = FALSE;
	di->sysfs_data.wdt_disable = FALSE;
	di->sysfs_data.charge_limit = TRUE;
	di->sysfs_data.hiz_enable = FALSE;
	di->sysfs_data.charge_done_status = CHARGE_DONE_NON;
	di->sysfs_data.charge_done_sleep_status = CHARGE_DONE_SLEEP_DISABLED;
	di->sysfs_data.vr_charger_type = CHARGER_TYPE_NONE;
	di->sysfs_data.support_ico = 1;
	di->charger_type = CHARGER_REMOVED;
	mutex_init(&di->sysfs_data.dump_reg_lock);
	mutex_init(&di->sysfs_data.dump_reg_head_lock);
	mutex_init(&charge_wakelock_flag_lock);
	mutex_init(&di->sysfs_data.bootloader_info_lock);

	di->charge_fault = CHARGE_FAULT_NON;
	di->check_full_count = 0;
	charge_parse_dts(di);
	charge_wake_lock();
#ifdef CONFIG_TCPC_CLASS

	if(charger_pd_support)
	{
		pd_dpm_get_charge_event(&local_event, &local_state);
		pd_dpm_notifier_call(&(di->tcpc_nb), local_event, &local_state);
	}
	else
	{
		charge_rename_charger_type(type, di,FALSE);
		charge_send_uevent(di);
		schedule_work(&di->usb_work);
	}
#else
	charge_rename_charger_type(type, di,FALSE);
	charge_send_uevent(di);
	schedule_work(&di->usb_work);
#endif

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
	/* detect current device successful, set the flag as present */
	if (NULL != di->ops->dev_check) {
		if (CHARGE_IC_GOOD == di->ops->dev_check()) {
			hwlog_info("charger ic is good.\n");
			set_hw_dev_flag(DEV_I2C_CHARGER);
		} else {
			hwlog_err("charger ic is bad.\n");
		}
	} else {
		hwlog_err("ops dev_check is null.\n");
	}
#endif

	ret = charge_sysfs_create_group(di);
	if (ret)
		hwlog_err("can't create charge sysfs entries\n");
	power_class = hw_power_get_class();
	if (power_class) {
		if (charge_dev == NULL)
			charge_dev =
			    device_create(power_class, NULL, 0, NULL, "charger");
		ret =
		    sysfs_create_link(&charge_dev->kobj, &di->dev->kobj, "charge_data");
		if (ret) {
			hwlog_err("create link to charge_data fail.\n");
			goto charge_fail_3;
		}
	}
	g_di = di;

	copy_bootloader_charger_info();
	hwlog_info("huawei charger probe ok!\n");
	return 0;

charge_fail_3:
	charge_sysfs_remove_group(di);
charge_fail_2:
	wake_lock_destroy(&charge_lock);
	wake_lock_destroy(&stop_charge_lock);
charge_fail_1:
	di->ops = NULL;
charge_fail_0:
	platform_set_drvdata(pdev, NULL);
	kfree(di);
	di = NULL;
	return ret;
}

/**********************************************************
*  Function:       charge_remove
*  Description:    charge module remove
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
static int charge_remove(struct platform_device *pdev)
{
	struct charge_device_info *di = platform_get_drvdata(pdev);

	if (di == NULL) {
		hwlog_err("[%s]di is NULL!\n", __func__);
		return -ENODEV;
	}

	hisi_charger_type_notifier_unregister(&di->usb_nb);
	atomic_notifier_chain_unregister(&fault_notifier_list, &di->fault_nb);
	charge_sysfs_remove_group(di);
	wake_lock_destroy(&charge_lock);
	wake_lock_destroy(&uscp_plugout_lock);
	wake_lock_destroy(&stop_charge_lock);
	cancel_delayed_work(&di->charge_work);
	cancel_delayed_work(&di->otg_work);
	cancel_delayed_work(&di->plugout_uscp_work);
	if (NULL != di->ops) {
		di->ops = NULL;
		g_ops = NULL;
	}
	if (NULL != di->fcp_ops) {
		di->fcp_ops = NULL;
		g_fcp_ops = NULL;
	}
	kfree(di);
	di = NULL;
	return 0;
}

/**********************************************************
*  Function:       charge_shutdown
*  Description:    charge module shutdown
*  Parameters:   pdev:platform_device
*  return value:  NULL
**********************************************************/
static void charge_shutdown(struct platform_device *pdev)
{
	struct charge_device_info *di = platform_get_drvdata(pdev);
	int ret = 0;

	hwlog_info("%s ++\n", __func__);
	if (NULL == di) {
		hwlog_err("[%s]di is NULL!\n", __func__);
		return;
	}
	ret = di->ops->set_otg_enable(FALSE);
	if (ret) {
		hwlog_err("[%s]set otg default fail!\n", __func__);
	}

	if (di->ops->set_charger_hiz) {
		ret = di->ops->set_charger_hiz(FALSE);
		if (ret) {
			hwlog_err("[%s]set charger hiz default fail!\n",
				  __func__);
		}
	}

	hisi_charger_type_notifier_unregister(&di->usb_nb);
	atomic_notifier_chain_unregister(&fault_notifier_list, &di->fault_nb);

	cancel_delayed_work(&di->charge_work);
	cancel_delayed_work(&di->otg_work);
	hwlog_info("%s --\n", __func__);

	return;
}

#ifdef CONFIG_PM
/**********************************************************
*  Function:       charge_suspend
*  Description:    charge module suspend
*  Parameters:   pdev:platform_device
*                      state:unused
*  return value:  0-sucess or others-fail
**********************************************************/
static int charge_suspend(struct platform_device *pdev, pm_message_t state)
{
	struct charge_device_info *di = platform_get_drvdata(pdev);
	hwlog_info("%s ++\n", __func__);

	if (di->charger_source == POWER_SUPPLY_TYPE_MAINS) {
		if (charge_is_charging_full(di)) {
			if (!wake_lock_active(&charge_lock)) {
				cancel_delayed_work(&di->charge_work);
			}
		}
	}

	if ((CHARGE_DONE_SLEEP_ENABLED ==
	     di->sysfs_data.charge_done_sleep_status)
	    || charge_done_sleep_dts) {
		charge_disable_watchdog(di);
	}
	hwlog_info("%s --\n", __func__);

	return 0;
}

/**********************************************************
*  Function:       charge_resume
*  Description:    charge module resume
*  Parameters:   pdev:platform_device
*  return value:  0-sucess or others-fail
**********************************************************/
static int charge_resume(struct platform_device *pdev)
{
	struct charge_device_info *di = platform_get_drvdata(pdev);

	hwlog_info("%s ++\n", __func__);
	schedule_work(&resume_wakelock_work);

	if (di->charger_source == POWER_SUPPLY_TYPE_MAINS) {
#ifdef CONFIG_HISI_CHARGER_SYS_WDG
		charge_enable_sys_wdt();
#endif
		schedule_delayed_work(&di->charge_work, msecs_to_jiffies(0));
	}

	hwlog_info("%s --\n", __func__);

	return 0;
}
#endif /* CONFIG_PM */

#ifdef CONFIG_LLT_TEST
struct charge_static_ops charge_ops = {
	.charge_wake_lock = charge_wake_lock,
	.charge_wake_unlock = charge_wake_unlock,
	.charge_rename_charger_type = charge_rename_charger_type,
	.charge_update_charger_type = charge_update_charger_type,
	.charge_send_uevent = charge_send_uevent,
	.fcp_start_charging = fcp_start_charging,
	.charge_vbus_voltage_check = charge_vbus_voltage_check,
	.charge_update_vindpm = charge_update_vindpm,
	.charge_typec_current = charge_typec_current,
	.charge_select_charging_current = charge_select_charging_current,
	.charge_is_charging_full = charge_is_charging_full,
	.charge_update_status = charge_update_status,
	.charge_turn_on_charging = charge_turn_on_charging,
	.charge_suspend = charge_suspend,
	.charge_resume = charge_resume,
	.charge_lock = &charge_lock,
	.fcp_stage = &fcp_stage,
	.g_di = &g_di,
	.charge_done_sleep_dts = &charge_done_sleep_dts,
	.charge_lock_flag = &charge_lock_flag,
};
#endif

static struct of_device_id charge_match_table[] = {
	{
	 .compatible = "huawei,charger",
	 .data = NULL,
	 },
	{
	 },
};

static struct platform_driver charge_driver = {
	.probe = charge_probe,
	.remove = charge_remove,
#ifdef CONFIG_PM
	.suspend = charge_suspend,
	.resume = charge_resume,
#endif
	.shutdown = charge_shutdown,
	.driver = {
		   .name = "huawei,charger",
		   .owner = THIS_MODULE,
		   .of_match_table = of_match_ptr(charge_match_table),
		   },
};

/**********************************************************
*  Function:       charge_init
*  Description:    charge module initialization
*  Parameters:   NULL
*  return value:  0-sucess or others-fail
**********************************************************/
static int __init charge_init(void)
{
	return platform_driver_register(&charge_driver);
}

/**********************************************************
*  Function:       charge_exit
*  Description:    charge module exit
*  Parameters:   NULL
*  return value:  NULL
**********************************************************/
static void __exit charge_exit(void)
{
	platform_driver_unregister(&charge_driver);
}

late_initcall(charge_init);
module_exit(charge_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("huawei charger module driver");
MODULE_AUTHOR("HUAWEI Inc");
