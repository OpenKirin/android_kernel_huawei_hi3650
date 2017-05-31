/*
 * linux/drivers/power/hisi/hisi_bci_battery.c
 *
 * hisi:battery driver for Linux
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
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/power_supply.h>
#include <linux/wakelock.h>
#include <linux/notifier.h>
#include <linux/hisi/usb/hisi_usb.h>
#include <linux/power/hisi/hisi_bci_battery.h>
#include <linux/interrupt.h>
#include <linux/power/hisi/coul/hisi_coul_drv.h>
#include <linux/timer.h>
#include <linux/rtc.h>
#include <linux/module.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/version.h>
#ifdef CONFIG_HUAWEI_CHARGER
#include <huawei_platform/power/vbat_ovp.h>
#endif
#ifdef CONFIG_HUAWEI_TYPEC
#include <huawei_platform/usb/hw_typec_platform.h>
#include <huawei_platform/usb/hw_typec_dev.h>
#endif
#ifdef CONFIG_HUAWEI_CHARGER
#include <huawei_platform/power/huawei_charger.h>
#else
#include <linux/power/hisi/charger/hisi_charger.h>
#endif

#ifdef CONFIG_DIRECT_CHARGER
#include <huawei_platform/power/direct_charger.h>
#endif
#ifdef CONFIG_TCPC_CLASS
#include <huawei_platform/usb/hw_pd_dev.h>
#endif

#ifdef CONFIG_HUAWEI_DSM
#include <dsm/dsm_pub.h>
#endif

#ifdef CONFIG_HUAWEI_PLATFORM
#include <huawei_platform/log/hw_log.h>
#define HWLOG_TAG hisi_bci
HWLOG_REGIST();
#else
#define hwlog_debug(fmt, args...)do { printk(KERN_DEBUG   "[hisi_bci]" fmt, ## args); } while (0)
#define hwlog_info(fmt, args...) do { printk(KERN_INFO    "[hisi_bci]" fmt, ## args); } while (0)
#define hwlog_warn(fmt, args...) do { printk(KERN_WARNING"[hisi_bci]" fmt, ## args); } while (0)
#define hwlog_err(fmt, args...)  do { printk(KERN_ERR   "[hisi_bci]" fmt, ## args); } while (0)
#endif

#define WINDOW_LEN                   (10)
struct batt_dsm {
	int error_no;
	bool notify_enable;
	int (*check_error) (char *buf);
};
static struct wake_lock low_power_lock;
static int is_low_power_locked = 0;
static unsigned int capacity_filter[WINDOW_LEN];
static unsigned int capacity_sum;
static unsigned int suspend_capacity;
static bool capacity_debounce_flag = false;
static int removable_batt_flag = 0;
static int is_board_type = 0;
static int is_fake_battery = 0;
struct kobject *g_sysfs_bq_bci = NULL;
module_param(is_fake_battery, int, 0644);

#if defined(CONFIG_HUAWEI_DSM)
static struct dsm_dev dsm_battery = {
	.name = "dsm_battery",
	.fops = NULL,
	.buff_size = DSM_BATTERY_MAX_SIZE,
};

static struct dsm_dev dsm_charge_monitor = {
	.name = "dsm_charge_monitor",
	.fops = NULL,
	.buff_size = 1024,
};

static struct dsm_client *battery_dclient = NULL;
static struct dsm_client *charge_monitor_dclient = NULL;

struct dsm_client *get_battery_dclient(void)
{
	return battery_dclient;
}
#endif
struct hisi_bci_device_info {
	int bat_voltage;
	int bat_max_volt;
	int bat_temperature;
	int bat_exist;
	int bat_health;
	int bat_capacity;
	int bat_capacity_level;
	int bat_technolog;
	int bat_design_fcc;
	int bat_rm;
	int bat_fcc;
	short bat_current;
	unsigned int bat_err;
	int charge_status;
	int power_supply_status;
	u8 usb_online;
	u8 ac_online;
	u8 chargedone_stat;
	u16 monitoring_interval;
	int watchdog_timer_status;
	unsigned long event;
	unsigned int capacity;
	unsigned int capacity_filter_count;
	unsigned int prev_capacity;
	unsigned int charge_full_count;
	unsigned int wakelock_enabled;
	#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
	struct power_supply bat;
	struct power_supply usb;
	struct power_supply ac;
	struct power_supply bk_bat;
	#else
	struct power_supply    *bat;
	struct power_supply    *usb;
	struct power_supply    *ac;
	struct power_supply    *bk_bat;
	#endif
	struct device *dev;
	struct notifier_block nb;
	struct delayed_work hisi_bci_monitor_work;
	struct work_interval_para interval_data[WORK_INTERVAL_PARA_LEVEL];
};

struct hisi_bci_device_info *g_hisi_bci_dev;

BLOCKING_NOTIFIER_HEAD(notifier_list);

static enum power_supply_property hisi_bci_battery_props[] = {
	POWER_SUPPLY_PROP_STATUS,
	POWER_SUPPLY_PROP_HEALTH,
	POWER_SUPPLY_PROP_PRESENT,
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_TECHNOLOGY,
	POWER_SUPPLY_PROP_CYCLE_COUNT,
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
	POWER_SUPPLY_PROP_CURRENT_NOW,
	POWER_SUPPLY_PROP_CAPACITY,
	POWER_SUPPLY_PROP_CAPACITY_LEVEL,
	POWER_SUPPLY_PROP_TEMP,
	POWER_SUPPLY_PROP_CAPACITY_RM,
	POWER_SUPPLY_PROP_CAPACITY_FCC,
	POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN,
	POWER_SUPPLY_PROP_CHARGE_FULL,
	POWER_SUPPLY_PROP_CHARGE_NOW,
	POWER_SUPPLY_PROP_VOLTAGE_MAX,
	POWER_SUPPLY_PROP_ID_VOLTAGE,
	POWER_SUPPLY_PROP_BRAND,
	POWER_SUPPLY_PROP_FCP_STATUS,
	POWER_SUPPLY_PROP_SCP_STATUS,
	POWER_SUPPLY_PROP_BAT_OVP,
};

static enum power_supply_property hisi_usb_props[] = {
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_HEALTH,
};

static enum power_supply_property hisi_ac_props[] = {
	POWER_SUPPLY_PROP_ONLINE,
	POWER_SUPPLY_PROP_HEALTH,
};

static enum power_supply_property hisi_bk_bci_battery_props[] = {
	POWER_SUPPLY_PROP_VOLTAGE_NOW,
};

static int calc_capacity_from_voltage(void)
{
	int data = 50;
	int battery_voltage = 0;
	int battery_current = 0;

	battery_current = -hisi_battery_current();
	battery_voltage = hisi_battery_voltage();
	if (battery_voltage <= BAT_VOL_3200) {
		data = 0;
		return data;
	}
	battery_voltage = hisi_battery_voltage() - 120 * battery_current / 1000;
	if (battery_voltage < BAT_VOL_3500)
		data = 2;
	else if (battery_voltage < BAT_VOL_3550)
		data = 10;
	else if (battery_voltage < BAT_VOL_3600)
		data = 20;
	else if (battery_voltage < BAT_VOL_3700)
		data = 30;
	else if (battery_voltage < BAT_VOL_3800)
		data = 40;
	else if (battery_voltage < BAT_VOL_3850)
		data = 50;
	else if (battery_voltage < BAT_VOL_3900)
		data = 60;
	else if (battery_voltage < BAT_VOL_3950)
		data = 65;
	else if (battery_voltage < BAT_VOL_4000)
		data = 70;
	else if (battery_voltage < BAT_VOL_4250)
		data = 85;
	else if (battery_voltage >= BAT_VOL_4250)
		data = 100;
	return data;
}

/*only charge-work can not reach full(95%).Change capacity to full after 40min.*/
static int hisi_force_full_timer(int curr_capacity,
				 struct hisi_bci_device_info *di)
{
	if (curr_capacity > CHG_CANT_FULL_THRESHOLD) {
		di->charge_full_count++;
		if (di->charge_full_count >= CHARGE_FULL_TIME) {
			hwlog_info("FORCE_CHARGE_FULL = %d\n", curr_capacity);
			di->charge_full_count = CHARGE_FULL_TIME;
			curr_capacity = 100;
		}
	} else {
		di->charge_full_count = 0;
	}

	return curr_capacity;
}

static int hisi_capacity_pulling_filter(int curr_capacity,
					struct hisi_bci_device_info *di)
{
	int index = 0;
	di->bat_exist = is_hisi_battery_exist();

	if ((!di->bat_exist) || (is_fake_battery)) {
		curr_capacity = calc_capacity_from_voltage();
		return curr_capacity;
	}
	index = di->capacity_filter_count % WINDOW_LEN;

	capacity_sum -= capacity_filter[index];
	capacity_filter[index] = curr_capacity;
	capacity_sum += capacity_filter[index];

	if (++di->capacity_filter_count >= WINDOW_LEN)
		di->capacity_filter_count = 0;

	/*rounding-off 0.5 method */
	curr_capacity = (capacity_sum * 10) / WINDOW_LEN;
	curr_capacity = (curr_capacity + 5) / 10;
	return curr_capacity;
}

void bci_set_work_interval(int capacity, struct hisi_bci_device_info *di)
{
	int i;

	for (i = 0; i < WORK_INTERVAL_PARA_LEVEL; i++) {
		if ((capacity >= di->interval_data[i].cap_min)
			&& (capacity <= di->interval_data[i].cap_max)) {
			di->monitoring_interval = di->interval_data[i].work_interval;
			break;
		}
	}

	if(!di->monitoring_interval)
		di->monitoring_interval = WORK_INTERVAL_NOARMAL;

	if (capacity > CHG_CANT_FULL_THRESHOLD)
		di->monitoring_interval = WORK_INTERVAL_REACH_FULL;
}
static int capacity_changed(struct hisi_bci_device_info *di)
{
	int curr_capacity = 0;
	int low_bat_flag = is_hisi_battery_reach_threshold();

	di->bat_exist = is_hisi_battery_exist();

	/* if battery is not present we assume it is on battery simulator
	 *  if we are in factory mode, BAT FW is not updated yet, we use volt2Capacity
	 */
	if ((!di->bat_exist) || (is_fake_battery) ||
	    (strstr(saved_command_line, "androidboot.swtype=factory") && (COUL_BQ27510 == hisi_coulometer_type()))) {
		curr_capacity = calc_capacity_from_voltage();
	} else {
		curr_capacity = hisi_battery_capacity();
	}
	if ((!di->bat_exist) && strstr(saved_command_line, "androidboot.swtype=factory")) {
		/* when in facotry mode and battery is not exist ,
			keep capacity > 2 to prevent system shutdown */
		if (curr_capacity <= 2) {
			di->capacity = 3;
			di->prev_capacity = 3;
			return 1;
		}
	}

	if ((low_bat_flag & BQ_FLAG_LOCK) != BQ_FLAG_LOCK && is_low_power_locked) {
		wake_unlock(&low_power_lock);
		is_low_power_locked = 0;
	}

	/* Debouncing of power on init. */
	if (di->capacity == -1) {
		di->capacity = curr_capacity;
		di->prev_capacity = curr_capacity;
		return 1;
	}

	/*Only availability if the capacity changed */
	if (curr_capacity != di->prev_capacity) {
		if (abs(di->prev_capacity - curr_capacity) >= CHG_ODD_CAPACITY) {
			hwlog_info("prev_capacity = %d\n"
				   "curr_capacity = %d\n"
				   "curr_voltage = %d\n", di->prev_capacity,
				   curr_capacity, hisi_battery_voltage());
		}
	}

	if (curr_capacity < 2) {
		int battery_volt;

		battery_volt = hisi_battery_voltage();
		if (battery_volt < BAT_VOL_3500) {
			di->capacity = curr_capacity;
			return 1;
		}
		hwlog_info("low capacity reported, battery_vol = %d mv, capacity = %d\n", battery_volt, curr_capacity);
		return 0;
	}

	switch (di->charge_status) {
	case POWER_SUPPLY_STATUS_CHARGING:
		curr_capacity = hisi_force_full_timer(curr_capacity, di);
		break;

	case POWER_SUPPLY_STATUS_FULL:
		if (hisi_battery_current_avg() >= 0) {
			if (hisi_battery_voltage() >= (di->bat_max_volt - RECHG_PROTECT_THRESHOLD)) {
				curr_capacity = 100;
				hwlog_info("Force soc=100\n");
			}
		}
		di->charge_full_count = 0;
		break;

	case POWER_SUPPLY_STATUS_DISCHARGING:
	case POWER_SUPPLY_STATUS_NOT_CHARGING:
		/*capacity-count will always decrease when discharging || notcharging */
		if (di->prev_capacity <= curr_capacity)
			return 0;
		di->charge_full_count = 0;
		break;

	default:
		hwlog_err("%s defualt run.\n", __func__);
		break;
	}

	bci_set_work_interval(curr_capacity, di);

	/*filter */
	curr_capacity = hisi_capacity_pulling_filter(curr_capacity, di);

	if (di->prev_capacity == curr_capacity)
		return 0;

	if((POWER_SUPPLY_STATUS_DISCHARGING == di->charge_status) ||
	    (POWER_SUPPLY_STATUS_NOT_CHARGING == di->charge_status)) {
	    if (di->prev_capacity < curr_capacity)
	        return 0;
	}

	if(POWER_SUPPLY_STATUS_CHARGING == di->charge_status
		&& (-hisi_battery_current() >= CURRENT_THRESHOLD))
	{
		if(di->prev_capacity > curr_capacity)
			return 0;
	}

	hwlog_info("Capacity Updated = %d, charge_full_count = %d, charge_status = %d\n",
							curr_capacity, di->charge_full_count, di->charge_status);

	di->capacity = curr_capacity;
	di->prev_capacity = curr_capacity;
	return 1;
}

static int hisi_charger_event(struct notifier_block *nb, unsigned long event,
			      void *_data)
{
	struct hisi_bci_device_info *di;
	int ret = 0;
	di = container_of(nb, struct hisi_bci_device_info, nb);
	di->event = event;
	switch (event) {
	case VCHRG_START_USB_CHARGING_EVENT:
		di->usb_online = 1;
		di->ac_online = 0;
		di->charge_status = POWER_SUPPLY_STATUS_CHARGING;
		di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
		di->charge_full_count = 0;
		if (g_sysfs_bq_bci)
			sysfs_notify(g_sysfs_bq_bci, NULL, "poll_charge_start_event");
		break;

	case VCHRG_START_AC_CHARGING_EVENT:
		di->ac_online = 1;
		di->usb_online = 0;
		di->charge_status = POWER_SUPPLY_STATUS_CHARGING;
		di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
		di->charge_full_count = 0;
		if (g_sysfs_bq_bci)
			sysfs_notify(g_sysfs_bq_bci, NULL, "poll_charge_start_event");
		break;

	case VCHRG_STOP_CHARGING_EVENT:
		di->usb_online = 0;
		di->ac_online = 0;
		di->charge_status = POWER_SUPPLY_STATUS_DISCHARGING;
		di->power_supply_status = POWER_SUPPLY_HEALTH_UNKNOWN;
		di->charge_full_count = 0;
		if (g_sysfs_bq_bci)
			sysfs_notify(g_sysfs_bq_bci, NULL, "poll_charge_start_event");
		break;

	case VCHRG_START_CHARGING_EVENT:
		di->charge_status = POWER_SUPPLY_STATUS_CHARGING;
		di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
		break;

	case VCHRG_NOT_CHARGING_EVENT:
		di->charge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
		break;
	case VCHRG_CHARGE_DONE_EVENT:
   /****Do not need charge status change to full when bq24192 chargedone.
    because bq27510 will insure the charge status to full when capacity is 100.
	di->charge_status = POWER_SUPPLY_STATUS_FULL;
	di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
    *****************************************************************/
		break;
	case VCHRG_POWER_SUPPLY_OVERVOLTAGE:
		di->charge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		di->power_supply_status = POWER_SUPPLY_HEALTH_OVERVOLTAGE;
		break;

	case VCHRG_POWER_SUPPLY_WEAKSOURCE:
		di->charge_status = POWER_SUPPLY_STATUS_NOT_CHARGING;
		di->power_supply_status = POWER_SUPPLY_HEALTH_UNSPEC_FAILURE;
		break;
	case VCHRG_STATE_WATER_INTRUSED:
		break;
	case BATTERY_LOW_WARNING:
		break;
	case BATTERY_LOW_SHUTDOWN:
		wake_lock(&low_power_lock);
		is_low_power_locked = 1;
		break;
	case VCHRG_STATE_WDT_TIMEOUT:
		di->watchdog_timer_status = POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE;
		break;
	case BATTERY_MOVE:
		di->bat_exist = is_hisi_battery_exist();
		break;
	default:
		hwlog_err("%s defualt run.\n", __func__);
		break;
	}

	if ((di->usb_online || di->ac_online) && di->capacity == 100)
		di->charge_status = POWER_SUPPLY_STATUS_FULL;
	/*in case charger can not get the report of charger removed, so
	 * update the status of charger.*/
#ifdef CONFIG_DIRECT_CHARGER
	if (0 == get_direct_charge_flag()) {
#endif

#ifdef CONFIG_TCPC_CLASS
		if (!pd_dpm_get_pd_finish_flag()) {
#endif
			if (hisi_get_charger_type() == CHARGER_TYPE_NONE) {
				di->usb_online = 0;
				di->ac_online = 0;
				di->charge_status = POWER_SUPPLY_STATUS_DISCHARGING;
				di->power_supply_status = POWER_SUPPLY_HEALTH_UNKNOWN;
				di->charge_full_count = 0;
			}
#ifdef CONFIG_TCPC_CLASS
		}
#endif

#ifdef CONFIG_DIRECT_CHARGER
	}
#endif
	if (event == VCHRG_CHARGE_DONE_EVENT)
		di->chargedone_stat = 1;
	else
		di->chargedone_stat = 0;
	if (VCHRG_START_CHARGING_EVENT != event)
		hwlog_info("received event = %lx, charge_status = %d\n", event, di->charge_status);
	#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
	power_supply_changed(&di->bat);
	#else
	power_supply_changed(di->bat);
	#endif
	return ret;
}

/*for dmd*/
#if defined(CONFIG_HUAWEI_DSM)
int check_batt_not_exist(char *buf)
{
#ifndef CONFIG_HLTHERM_RUNTEST
	if (!is_hisi_battery_exist()) {
		snprintf(buf, 1024, "batt_temp = %d\n", hisi_battery_temperature());
		return 1;
	}
#endif
	return 0;
}

int check_batt_temp_overlow(char *buf)
{
#ifndef CONFIG_HLTHERM_RUNTEST
	int temp = hisi_battery_temperature();
	if (temp < (-10)) {
		snprintf(buf, 1024, "batt_temp = %d\n", temp);
		return 1;
	}
#endif
	return 0;
}

int check_batt_volt_overhigh(char *buf)
{
	int volt, capacity, curr, avg_curr;
	volt = hisi_battery_voltage();
	if (volt > 4550) {
		capacity = hisi_battery_capacity();
		curr = hisi_battery_current();
		avg_curr = hisi_battery_current_avg();
		snprintf(buf, 1024, "batt_volt = %dmV, capacity = %d, curr = %dmA, avg_curr = %dmA\n",
			volt, capacity, curr, avg_curr);
		return 1;
	}
	return 0;
}

int check_batt_volt_overlow(char *buf)
{
	int volt, capacity, curr, avg_curr;
	volt = hisi_battery_voltage();
	if (volt < 2800) {
		capacity = hisi_battery_capacity();
		curr = hisi_battery_current();
		avg_curr = hisi_battery_current_avg();
		snprintf(buf, 1024, "batt_volt = %dmV, capacity = %d, curr = %dmA, avg_curr = %dmA\n",
			volt, capacity, curr, avg_curr);
		return 1;
	}
	return 0;
}

int check_batt_terminate_too_early(char *buf)
{
	struct hisi_bci_device_info *di = g_hisi_bci_dev;
	int capacity = hisi_battery_capacity();
	int volt, current_now, avg_curr, rm;
	char *batt_brand;

	if(NULL == di){
		hwlog_info("NULL point in [%s]\n", __func__);
		return -1;
	}
	if (di->chargedone_stat && capacity <= CHG_CANT_FULL_THRESHOLD) {
		batt_brand = hisi_battery_brand();
		volt = hisi_battery_voltage();
		current_now = -hisi_battery_current();
		avg_curr = hisi_battery_current_avg();
		rm = hisi_battery_rm();
		snprintf(buf, 1024, "battery: %s, batt_volt = %dmV, batt_curr = %dmA, "
			"avg_curr = %dmA, capacity = %d rm = %dmAh\n",
			batt_brand, volt, current_now, avg_curr, capacity, rm);
		return 1;
	}
	return 0;
}

int check_batt_not_terminate(char *buf)
{
	int curr_by_coultype = 1;
	int current_avg = 0;
	int current_now = 0;
	static int times = 0;
	int dpm_state = 0;
	int vbatt = 0;
    struct hisi_bci_device_info *di = g_hisi_bci_dev;

	if(NULL == di){
		hwlog_info("NULL point in [%s]\n", __func__);
		return -1;
	}
	if (COUL_HISI == hisi_coulometer_type())
		curr_by_coultype = -1;

	dpm_state = charge_check_input_dpm_state();
	if ((POWER_SUPPLY_STATUS_FULL == di->charge_status) && (0 == dpm_state)) {
		current_avg = hisi_battery_current_avg();
		current_now = curr_by_coultype * hisi_battery_current();
		if (current_avg <= 50 && current_avg >= 10
		    && current_now <= 50 && current_now >= 10) {
			times++;
		} else {
			times = 0;
		}
		if (times == 10) {
			times = 0;
			vbatt = hisi_battery_voltage();
			snprintf(buf, 1024, "current_avg = %dmA, current_now = %dmA, vbat = %dmV\n",
				current_avg, current_now, vbatt);
			return 1;
		}
	}
	return 0;
}
int check_batt_bad_curr_sensor(char *buf)
{
	static int times = 0;
	int current_now;
	struct hisi_bci_device_info *di = g_hisi_bci_dev;
	int plugged = 0;
	int avg_curr = 0;

	if(NULL == di){
		hwlog_info("NULL point in [%s]\n", __func__);
		return -1;
	}
	current_now = -hisi_battery_current();
	plugged = charge_check_charger_plugged();

	if ((!di->usb_online) && (!di->ac_online) && (0 == plugged)
	    && (current_now > CURRENT_OFFSET)) {
		times++;
	} else {
		times = 0;
	}
	if (times == 5) {
		times = 0;
		avg_curr = hisi_battery_current_avg();
		snprintf(buf, 1024, "current = %dmA, avg_curr = %dmA\n", current_now, avg_curr);
		return 1;
	}
	return 0;
}

int check_vbus_volt_overhigh(char *buf)
{
	static int times = 0;
	struct hisi_bci_device_info *di = g_hisi_bci_dev;
	int vbatt;

	if(NULL == di){
		hwlog_info("NULL point in [%s]\n", __func__);
		return -1;
	}
	if (di->power_supply_status == POWER_SUPPLY_HEALTH_OVERVOLTAGE)
		times++;
	else
		times = 0;

	if (times == 5) {
		times = 0;
		vbatt = hisi_battery_voltage();
		snprintf(buf, 1024, "vbus_status= %s, vbatt = %dmV\n",
			"POWER_SUPPLY_HEALTH_OVERVOLTAGE", vbatt);
		return 1;
	}
	return 0;
}

int check_watchdog_timer_expiration(char *buf)
{
	struct hisi_bci_device_info *di = g_hisi_bci_dev;
	if(NULL == di){
		hwlog_info("NULL point in [%s]\n", __func__);
		return -1;
	}
	if (di->watchdog_timer_status == POWER_SUPPLY_HEALTH_WATCHDOG_TIMER_EXPIRE) {
		snprintf(buf, 1024, "WDT_status=%s\n", "watch dog timer expiration");
		return 1;
	}
	return 0;
}

int check_charge_curr_overhigh(char *buf)
{
	int i;
	int current_now[3];

	for (i = 0; i < 3; i++) {
		current_now[i] = -hisi_battery_current();
		if (current_now[i] > 7000)
			msleep(100);
		else
			break;

	}
	if (3 == i) {
		snprintf(buf, 1024, "current = %d, %d, %d\n", current_now[0], current_now[1], current_now[2]);
		return 1;
	}
	return 0;
}

int check_discharge_curr_overhigh(char *buf)
{
	int i;
	int current_now[3];
	struct hisi_bci_device_info *di = g_hisi_bci_dev;

	if(NULL == di){
		hwlog_info("NULL point in [%s]\n", __func__);
		return -1;
	}
	for (i = 0; i < 3; i++) {
		current_now[i] = -hisi_battery_current();
		if ((!di->usb_online) && (!di->ac_online)
		    && current_now[i] < (-7000)) {
			msleep(100);
		} else {
			break;
		}
	}
	if (3 == i) {
		snprintf(buf, 1024, "current = %d, %d, %d\n", current_now[0], current_now[1], current_now[2]);
		return 1;
	}
	return 0;
}

/* During continuous suspend and resume in 30 seconds, and suspend current < 10ma test,
*  g_curr_zero_times will not exceeding 1 ,it will be cleared when resume
*/
static int g_curr_zero_times;
int check_charge_curr_zero(char *buf)
{
	int plugged = 0;
	int current_now = 0;

	current_now = -hisi_battery_current();
	plugged = charge_check_charger_plugged();

	if ((current_now < 10) && (current_now > (-10)) && (0 == plugged))
		g_curr_zero_times++;
	else
		g_curr_zero_times = 0;

	if (g_curr_zero_times == 5) {
		g_curr_zero_times = 0;
		snprintf(buf, 1024, "current = %d\n", current_now);
		return 1;
	}
	return 0;
}

#define HIGH_TEMP (50)
#define LOW_TEMP  (0)
int check_charge_temp_fault(char *buf)
{
#ifndef CONFIG_HLTHERM_RUNTEST
	int temp = hisi_battery_temperature();
	if (HIGH_TEMP < temp || LOW_TEMP > temp) {
		snprintf(buf, 1024, "temp fault so not charge temp = %d\n", temp);
		return 1;
	}
#endif
	return 0;

}
#define SHUTDOWN_TEMP (68)
int check_charge_batt_shutdown_temp(char *buf)
{
#ifndef CONFIG_HLTHERM_RUNTEST
	int temp = hisi_battery_temperature();
	if (SHUTDOWN_TEMP <= temp) {
		snprintf(buf, 1024, "shutdown because batt_temp = %d\n", temp);
		return 1;
	}
#endif
	return 0;
}

int check_charge_batt_capacity(char *buf)
{
	struct hisi_bci_device_info *di = g_hisi_bci_dev;
	int full_rm = di->bat_rm;
	int fcc_design = hisi_battery_fcc_design();

	if ((VCHRG_CHARGE_DONE_EVENT == di->event) && full_rm < fcc_design*80/100) {
			snprintf(buf, 1024, "battery: %s, batt_vol = %dmV, capacity = %dmAh, full capacity = %dmAh \n",
				hisi_battery_brand(), di->bat_voltage, di->bat_rm, fcc_design);
			return 1;
	}
	return 0;
}

int check_charge_charger_ts(char *buf)
{
	struct hisi_bci_device_info *di = g_hisi_bci_dev;
	if (TRUE == charge_check_charger_ts()) {
		snprintf(buf, 1024, " charger ts error!charge status = %d\n", di->charge_status);
		return 1;
	}
	return 0;
}

int check_charge_otg_ture(char *buf)
{
#ifdef CONFIG_HUAWEI_TYPEC
	int typec_mode = typec_detect_port_mode();

	if(typec_mode < 0)
	{
		hwlog_err("typec not ready %d!!!\n", typec_mode);
		return 0;
	}
	if (TRUE == charge_check_charger_otg_state()
		&& TYPEC_DEV_PORT_MODE_DFP != typec_mode) {
		snprintf(buf, 1024, "charger in otg mode!typec mode = %d\n",typec_mode);
		return 1;
	}
#endif
	return 0;
}

static struct batt_dsm batt_dsm_array[] = {
	{ERROR_BATT_NOT_EXIST, true, check_batt_not_exist},
	{ERROR_BATT_TEMP_LOW, true, check_batt_temp_overlow},
	{ERROR_BATT_VOLT_HIGH, true, check_batt_volt_overhigh},
	{ERROR_BATT_VOLT_LOW, true, check_batt_volt_overlow},
	{ERROR_BATT_TERMINATE_TOO_EARLY, true, check_batt_terminate_too_early},
	{ERROR_BATT_NOT_TERMINATE, true, check_batt_not_terminate},
	{ERROR_BATT_BAD_CURR_SENSOR, true, check_batt_bad_curr_sensor},
	{ERROR_VBUS_VOLT_HIGH, true, check_vbus_volt_overhigh},
	{ERROR_WATCHDOG_RESET, true, check_watchdog_timer_expiration},
	{ERROR_CHARGE_CURR_OVERHIGH, true, check_charge_curr_overhigh},
	{ERROR_DISCHARGE_CURR_OVERHIGH, true, check_discharge_curr_overhigh},
	{ERROR_CHARGE_CURR_ZERO, true, check_charge_curr_zero},
	{ERROR_CHARGE_TEMP_FAULT, true, check_charge_temp_fault},
	{ERROR_CHARGE_BATT_TEMP_SHUTDOWN, true, check_charge_batt_shutdown_temp},
	{ERROR_CHARGE_BATT_CAPACITY, true, check_charge_batt_capacity},
	{ERROR_CHARGE_CHARGER_TS, true, check_charge_charger_ts},
	{ERROR_CHARGE_OTG, true, check_charge_otg_ture},
};

static void hisi_get_error_info(struct hisi_bci_device_info *di)
{
	int i;
	char buf[1024];

	memset(buf, 0, sizeof(buf));
	for (i = 0; i < (sizeof(batt_dsm_array) / sizeof(struct batt_dsm)); ++i) {
		if (batt_dsm_array[i].notify_enable
		    && (BAT_BOARD_ASIC == is_board_type)) {
			if (batt_dsm_array[i].check_error(buf)) {
				di->bat_err = batt_dsm_array[i].error_no;
#if defined(CONFIG_HUAWEI_DSM)
				if (!dsm_client_ocuppy(battery_dclient)) {
					buf[1023] = 0;
					dev_err(di->dev, "%s", buf);
					dsm_client_record(battery_dclient, "%s", buf);
					dsm_client_notify(battery_dclient, di->bat_err);
					batt_dsm_array[i].notify_enable = false;
					break;
				}
#else
				buf[1023] = 0;
				hwlog_err("error_no = %d!!!\n", di->bat_err);
				hwlog_err("error_buf = %s\n", buf);
				break;
#endif
			}
		}
	}
}
#endif
static void hisi_get_battery_info(struct hisi_bci_device_info *di)
{
	di->bat_rm = hisi_battery_rm();
	di->bat_fcc = hisi_battery_fcc();

	if (!(di->bat_exist)) {
		di->bat_health = POWER_SUPPLY_HEALTH_UNKNOWN;
		di->bat_capacity_level = POWER_SUPPLY_CAPACITY_LEVEL_UNKNOWN;
		di->bat_technolog = POWER_SUPPLY_TECHNOLOGY_UNKNOWN;
		di->bat_temperature = 0;
	} else {
		di->bat_health = hisi_battery_health();
		di->bat_capacity_level = hisi_battery_capacity_level();
		di->bat_technolog = hisi_battery_technology();
		di->bat_temperature = hisi_battery_temperature();
	}
}

static void hisi_bci_battery_work(struct work_struct *work)
{
	struct hisi_bci_device_info *di = container_of(work, struct hisi_bci_device_info, hisi_bci_monitor_work.work);

	hisi_get_battery_info(di);
#if defined (CONFIG_HUAWEI_DSM)
	hisi_get_error_info(di);
#endif
	schedule_delayed_work(&di->hisi_bci_monitor_work, msecs_to_jiffies(di->monitoring_interval));

	if (capacity_changed(di)) {
		#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
		power_supply_changed(&di->bat);
		#else
		power_supply_changed(di->bat);
		#endif
	}
}

static int hisi_ac_get_property(struct power_supply *psy,
				enum power_supply_property psp,
				union power_supply_propval *val)
{
    struct hisi_bci_device_info *di = g_hisi_bci_dev;
	if( NULL == di )
	{
		hwlog_info("NULL point in [%s]\n", __func__);
		return -EINVAL;
    }
	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = di->ac_online;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = di->power_supply_status;
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

static int hisi_usb_get_property(struct power_supply *psy,
				 enum power_supply_property psp,
				 union power_supply_propval *val)
{
    struct hisi_bci_device_info *di = g_hisi_bci_dev;

	if( NULL == di )
	{
		hwlog_info("NULL point in [%s]\n", __func__);
		return -EINVAL;
	}
	switch (psp) {
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = di->usb_online;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = di->power_supply_status;
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int hisi_bk_bci_battery_get_property(struct power_supply *psy,
					    enum power_supply_property psp,
					    union power_supply_propval *val)
{

	switch (psp) {
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		/*Use gpadc channel for measuring bk battery voltage */
		val->intval = 0;	/* hisi_get_gpadc_conversion(di, ADC_VBATMON);*/
		break;
	default:
		return -EINVAL;
	}

	return 0;
}

static int hisi_bci_battery_get_property(struct power_supply *psy,
					 enum power_supply_property psp,
					 union power_supply_propval *val)
{
    struct hisi_bci_device_info *di = g_hisi_bci_dev;

	if( NULL == di )
	{
		hwlog_info("NULL point in [%s]\n", __func__);
		return -EINVAL;
	}
	switch (psp) {
	case POWER_SUPPLY_PROP_STATUS:
		val->intval = di->charge_status;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_NOW:
		di->bat_voltage = hisi_battery_voltage();
		if (COUL_HISI == hisi_coulometer_type())
			val->intval = hisi_battery_voltage_uv();
		else
			val->intval = di->bat_voltage * 1000;
		break;
	case POWER_SUPPLY_PROP_CURRENT_NOW:
		di->bat_current = -hisi_battery_current();
		val->intval = di->bat_current;
		break;
	case POWER_SUPPLY_PROP_TEMP:
#ifdef CONFIG_HLTHERM_RUNTEST
		val->intval = 250;
#else
		val->intval = di->bat_temperature * 10;
#endif
		break;
	case POWER_SUPPLY_PROP_PRESENT:
	case POWER_SUPPLY_PROP_ONLINE:
		val->intval = di->bat_exist;
		break;
	case POWER_SUPPLY_PROP_HEALTH:
		val->intval = di->bat_health;
		break;
	case POWER_SUPPLY_PROP_CAPACITY:
		val->intval = di->capacity;
		break;
	case POWER_SUPPLY_PROP_CAPACITY_LEVEL:
		val->intval = di->bat_capacity_level;
		break;
	case POWER_SUPPLY_PROP_TECHNOLOGY:
		val->intval = di->bat_technolog;
		break;
	case POWER_SUPPLY_PROP_CAPACITY_RM:
	case POWER_SUPPLY_PROP_CHARGE_NOW:
		val->intval = di->bat_rm;
		break;
	case POWER_SUPPLY_PROP_CAPACITY_FCC:
	case POWER_SUPPLY_PROP_CHARGE_FULL:
		val->intval = di->bat_fcc;
		break;
	case POWER_SUPPLY_PROP_CHARGE_FULL_DESIGN:
		val->intval = di->bat_design_fcc;
		break;
	case POWER_SUPPLY_PROP_VOLTAGE_MAX:
		val->intval = di->bat_max_volt;
		break;
	case POWER_SUPPLY_PROP_ID_VOLTAGE:
		val->intval = hisi_battery_id_voltage();
		break;
	case POWER_SUPPLY_PROP_BRAND:
		val->strval = hisi_battery_brand();
		break;
	case POWER_SUPPLY_PROP_CYCLE_COUNT:
		val->intval = hisi_battery_cycle_count();
		break;
	case POWER_SUPPLY_PROP_FCP_STATUS:
		#if (defined (CONFIG_HUAWEI_CHARGER) || defined (CONFIG_HISI_CHARGER_ARCH))
		if (FCP_STAGE_SUCESS <= fcp_get_stage_status() && di->ac_online)
			val->intval = 1;
#ifdef CONFIG_DIRECT_CHARGER
		else if (get_quick_charge_flag() && di->ac_online)
			val->intval = 1;
#endif
#ifdef CONFIG_TCPC_CLASS
		else if (true == pd_dpm_get_high_power_charging_status() && di->ac_online)
		{
			val->intval = 1;
			hwlog_info("pd_dpm_get_high_power_charging_status intval 1 [%s]\n", __func__);
		}
#endif
		else
		{
			val->intval = 0;
			hwlog_info("intval 0 [%s]\n", __func__);
		}
		break;
		#endif
	case POWER_SUPPLY_PROP_SCP_STATUS:
		val->intval = 0;
#ifdef CONFIG_DIRECT_CHARGER
		if (get_super_charge_flag() && di->ac_online)
			val->intval = 1;
		else
			val->intval = 0;
#endif
		break;
	case POWER_SUPPLY_PROP_BAT_OVP:
		val->intval = 0;
#ifdef CONFIG_HUAWEI_CHARGER
		val->intval = get_vbat_ovp_status();
		hwlog_info("%s:get_vbat_ovp_status interval = %d\n",__func__,val->intval);
#endif
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

int hisi_bci_show_capacity(void)
{
	struct hisi_bci_device_info *di = g_hisi_bci_dev;

	if( NULL == di )
	{
		hwlog_info("NULL point in [%s]\n", __func__);
		return -EINVAL;
	}

	if(di->capacity > 100) {
		hwlog_err("error capacity, will rewrite from %d to 100\n", di->capacity);
		di->capacity = 100;
	}
	return di->capacity;
}

int hisi_register_notifier(struct notifier_block *nb, unsigned int events)
{
	return blocking_notifier_chain_register(&notifier_list, nb);
}

EXPORT_SYMBOL_GPL(hisi_register_notifier);

int hisi_unregister_notifier(struct notifier_block *nb, unsigned int events)
{
	return blocking_notifier_chain_unregister(&notifier_list, nb);
}

EXPORT_SYMBOL_GPL(hisi_unregister_notifier);

static ssize_t hisi_bci_show_batt_removable(struct device *dev,
					    struct device_attribute *attr,
					    char *buf)
{
	return sprintf(buf, "%d\n", removable_batt_flag);
}

static ssize_t hisi_bci_poll_charge_start_event(struct device *dev,
						struct device_attribute *attr,
						char *buf)
{

	struct hisi_bci_device_info *di = dev_get_drvdata(dev);

	if (di)
		return sprintf(buf, "%ld\n", di->event);
	else
		return 0;
}

static ssize_t hisi_bci_set_charge_event(struct device *dev,
					 struct device_attribute *attr,
					 const char *buf, size_t count)
{
	struct hisi_bci_device_info *di = dev_get_drvdata(dev);
	long val = 0;

	if ((strict_strtol(buf, 10, &val) < 0) || (val < 0) || (val > 3000))
		return -EINVAL;
	di->event = val;
	sysfs_notify(g_sysfs_bq_bci, NULL, "poll_charge_start_event");
	return count;
}

static DEVICE_ATTR(batt_removable, (S_IWUSR | S_IRUGO),
		   hisi_bci_show_batt_removable, NULL);

static DEVICE_ATTR(poll_charge_start_event, (S_IWUSR | S_IRUGO),
		   hisi_bci_poll_charge_start_event, hisi_bci_set_charge_event);

static struct attribute *hisi_bci_attributes[] = {
	&dev_attr_batt_removable.attr,
	&dev_attr_poll_charge_start_event.attr,
	NULL,
};

static const struct attribute_group hisi_bci_attr_group = {
	.attrs = hisi_bci_attributes,
};

static char *hisi_bci_supplied_to[] = {
	"hisi_bci_battery",
};

struct class *hw_power_get_class(void);
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 13, 0))
static const struct power_supply_config hisi_bci_battery_cfg = {
	.supplied_to = hisi_bci_supplied_to,
	.num_supplicants = ARRAY_SIZE(hisi_bci_supplied_to),
};

static const struct power_supply_desc hisi_bci_battery_desc = {
	.name			= "Battery",
	.type			= POWER_SUPPLY_TYPE_BATTERY,
	.properties		= hisi_bci_battery_props,
	.num_properties		= ARRAY_SIZE(hisi_bci_battery_props),
	.get_property		= hisi_bci_battery_get_property,
};

static const struct power_supply_desc hisi_bci_usb_desc = {
	.name			= "USB",
	.type			= POWER_SUPPLY_TYPE_USB,
	.properties		= hisi_usb_props,
	.num_properties		= ARRAY_SIZE(hisi_usb_props),
	.get_property		= hisi_usb_get_property,
};

static const struct power_supply_desc hisi_bci_mains_desc = {
	.name			= "Mains",
	.type			= POWER_SUPPLY_TYPE_MAINS,
	.properties		= hisi_ac_props,
	.num_properties		= ARRAY_SIZE(hisi_ac_props),
	.get_property		= hisi_ac_get_property,
};

static const struct power_supply_desc hisi_bci_bk_battery_desc = {
	.name			= "hisi_bk_battery",
	.type			= POWER_SUPPLY_TYPE_UPS,
	.properties		= hisi_bk_bci_battery_props,
	.num_properties		= ARRAY_SIZE(hisi_bk_bci_battery_props),
	.get_property		= hisi_bk_bci_battery_get_property,
};
#endif

/**********************************************************
*  Function:       hisi_bci_parse_dts
*  Discription:    parse the module dts config value
*  Parameters:   np:device_node
*                      di:hisi_bci_device_info
*  return value:  0-sucess or others-fail
**********************************************************/
static int hisi_bci_parse_dts(struct device_node *np, struct hisi_bci_device_info *di)
{
	int ret = 0;
	int array_len = 0;
	int i = 0;
	const char *bci_data_string = NULL;
	int idata = 0;

	if (of_property_read_u32(np, "battery_design_fcc", &di->bat_design_fcc)) {
		di->bat_design_fcc = hisi_battery_fcc_design();
		hwlog_err("error:get battery_design_fcc value failed, used default value from batt_parm!\n");
	}
	if (of_property_read_u32(np, "battery_is_removable", &removable_batt_flag)) {
		removable_batt_flag = 0;
		hwlog_err("error:get removable_batt_flag value failed!\n");
	}
	if (of_property_read_u32(np, "battery_board_type", &is_board_type)) {
		is_board_type = BAT_BOARD_SFT;
		hwlog_err("error:get battery_board_type value failed!\n");
	}

	/*bci_work_interval_para*/
	array_len = of_property_count_strings(np, "bci_work_interval_para");
	if ((array_len <= 0) || (array_len % WORK_INTERVAL_PARA_TOTAL != 0)) {
		hwlog_err("bci_work_interval_para is invaild,please check iput number!!\n");
		return -EINVAL;
	}

	if (array_len > WORK_INTERVAL_PARA_LEVEL * WORK_INTERVAL_PARA_TOTAL) {
		hwlog_err("bci_work_interval_para is too long,use only front %d paras!!\n", array_len);
		return -EINVAL;
	}

	memset(di->interval_data, 0, WORK_INTERVAL_PARA_LEVEL * sizeof(struct work_interval_para));

	for (i = 0; i < array_len; i++) {
		ret = of_property_read_string_index(np, "bci_work_interval_para", i, &bci_data_string);
		if (ret) {
			hwlog_err("get bci_work_interval_para failed\n");
			return -EINVAL;
		}

		idata = simple_strtol(bci_data_string, NULL, 10);
		switch (i % WORK_INTERVAL_PARA_TOTAL) {
		case WORK_INTERVAL_CAP_MIN:
			if ((idata < CAPACITY_MIN) || (idata > CAPACITY_MAX)) {
				hwlog_err("the bci_work_interval_para cap_min is out of range!!\n");
				return -EINVAL;
			}
			di->interval_data[i / (WORK_INTERVAL_PARA_TOTAL)].cap_min = idata;
			break;
		case WORK_INTERVAL_CAP_MAX:
			if ((idata < CAPACITY_MIN) || (idata > CAPACITY_MAX)) {
				hwlog_err("the bci_work_interval_para cap_max is out of range!!\n");
				return -EINVAL;
			}
			di->interval_data[i / (WORK_INTERVAL_PARA_TOTAL)].cap_max = idata;
			break;
		case WORK_INTERVAL_VALUE:
			if( (idata < WORK_INTERVAL_MIN) || (idata > WORK_INTERVAL_MAX)) {
				hwlog_err("the bci_work_interval_para work_interval is out of range!!\n");
				return -EINVAL;
			}
			di->interval_data[i / (WORK_INTERVAL_PARA_TOTAL)].work_interval = idata;
			break;
		}
		hwlog_info("di->interval_data[%d][%d] = %d\n",
					i / (WORK_INTERVAL_PARA_TOTAL), i % (WORK_INTERVAL_PARA_TOTAL), idata);
	}

	return ret;
}

static int hisi_bci_battery_probe(struct platform_device *pdev)
{
	struct hisi_bci_device_info *di;
	int low_bat_flag = 0;
	int ret = 0;
	unsigned int i = 0;
	struct device_node *np;

	struct class *power_class = NULL;
	struct device *new_dev = NULL;
	np = pdev->dev.of_node;
	if (NULL == np)
		return -1;

	di = kzalloc(sizeof(*di), GFP_KERNEL);
	if (!di)
		return -ENOMEM;
	g_hisi_bci_dev = di;

	di->bat_max_volt = hisi_battery_vbat_max();
	di->monitoring_interval = WORK_INTERVAL_NOARMAL;
	di->dev = &pdev->dev;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
	di->bat.name = "Battery";
	di->bat.supplied_to = hisi_bci_supplied_to;
	di->bat.num_supplicants = ARRAY_SIZE(hisi_bci_supplied_to);
	di->bat.type = POWER_SUPPLY_TYPE_BATTERY;
	di->bat.properties = hisi_bci_battery_props;
	di->bat.num_properties = ARRAY_SIZE(hisi_bci_battery_props);
	di->bat.get_property = hisi_bci_battery_get_property;

	di->usb.name = "USB";
	di->usb.type = POWER_SUPPLY_TYPE_USB;
	di->usb.properties = hisi_usb_props;
	di->usb.num_properties = ARRAY_SIZE(hisi_usb_props);
	di->usb.get_property = hisi_usb_get_property;

	di->ac.name = "Mains";
	di->ac.type = POWER_SUPPLY_TYPE_MAINS;
	di->ac.properties = hisi_ac_props;
	di->ac.num_properties = ARRAY_SIZE(hisi_ac_props);
	di->ac.get_property = hisi_ac_get_property;

	di->bk_bat.name = "hisi_bk_battery";
	di->bk_bat.type = POWER_SUPPLY_TYPE_UPS;
	di->bk_bat.properties = hisi_bk_bci_battery_props;
	di->bk_bat.num_properties = ARRAY_SIZE(hisi_bk_bci_battery_props);
	di->bk_bat.get_property = hisi_bk_bci_battery_get_property;
#endif
	di->bat_health = POWER_SUPPLY_HEALTH_GOOD;
	di->bat_exist = is_hisi_battery_exist();
	di->bat_err = 0;
	di->power_supply_status = POWER_SUPPLY_HEALTH_GOOD;
	di->charge_status = POWER_SUPPLY_STATUS_DISCHARGING;

	di->capacity = -1;
	di->capacity_filter_count = 0;
	di->charge_full_count = 0;

	for (i = 0; i < WINDOW_LEN; i++) {
		capacity_filter[i] = hisi_battery_capacity();
		capacity_sum += capacity_filter[i];
		hwlog_info("capacity_filter[%d] = %d\n", i, capacity_filter[i]);
	}

	hisi_get_battery_info(di);

	platform_set_drvdata(pdev, di);

	wake_lock_init(&low_power_lock, WAKE_LOCK_SUSPEND,
		       "low_power_wake_lock");

	low_bat_flag = is_hisi_battery_reach_threshold();
	if ((low_bat_flag & BQ_FLAG_LOCK) == BQ_FLAG_LOCK) {
		wake_lock(&low_power_lock);
		is_low_power_locked = 1;
	}
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
	ret = power_supply_register(&pdev->dev, &di->bat);
	if (ret) {
		hwlog_debug("failed to register main battery\n");
		goto batt_failed;
	}

	ret = power_supply_register(&pdev->dev, &di->usb);
	if (ret) {
		hwlog_debug("failed to register usb power supply\n");
		goto usb_failed;
	}

	ret = power_supply_register(&pdev->dev, &di->ac);
	if (ret) {
		hwlog_debug("failed to register ac power supply\n");
		goto ac_failed;
	}

	ret = power_supply_register(&pdev->dev, &di->bk_bat);
	if (ret) {
		hwlog_debug("failed to register backup battery\n");
		goto bk_batt_failed;
	}
#else
	di->bat = power_supply_register(&pdev->dev, &hisi_bci_battery_desc, &hisi_bci_battery_cfg);
	if (IS_ERR(di->bat)) {
		hwlog_debug("failed to register main battery\n");
		goto batt_failed;
	}

	di->usb = power_supply_register(&pdev->dev, &hisi_bci_usb_desc, NULL);
	if (IS_ERR(di->usb)) {
		hwlog_debug("failed to register usb power supply\n");
		goto usb_failed;
	}

	di->ac = power_supply_register(&pdev->dev, &hisi_bci_mains_desc, NULL);
	if (IS_ERR(di->ac)) {
		hwlog_debug("failed to register ac power supply\n");
		goto ac_failed;
	}

	di->bk_bat = power_supply_register(&pdev->dev, &hisi_bci_bk_battery_desc, NULL);
	if (IS_ERR(di->bk_bat)) {
		hwlog_debug("failed to register backup battery\n");
		goto bk_batt_failed;
	}
#endif
	power_class = hw_power_get_class();
	if (power_class) {
		new_dev = device_create(power_class, NULL, 0, "%s", "bq_bci");
		if (IS_ERR(new_dev))
			new_dev = NULL;

		if (new_dev) {
			dev_set_drvdata(new_dev, di);
			g_sysfs_bq_bci = &new_dev->kobj;
			ret = sysfs_create_group(&new_dev->kobj, &hisi_bci_attr_group);
			if (ret) {
				hwlog_err("%s, could not create sysfs files hisi_bci!\n", __func__);
			}
		} else {
			hwlog_err("%s, could not create dev hisi_bci!\n", __func__);
		}
	}

	hisi_bci_parse_dts(np, di);

	INIT_DELAYED_WORK(&di->hisi_bci_monitor_work, hisi_bci_battery_work);
	schedule_delayed_work(&di->hisi_bci_monitor_work, 0);

	di->nb.notifier_call = hisi_charger_event;
	hisi_register_notifier(&di->nb, 1);
	hwlog_info("hisi_bci probe ok!\n");
#if defined(CONFIG_HUAWEI_DSM)
	if (!battery_dclient && (BAT_BOARD_ASIC == is_board_type))
		battery_dclient = dsm_register_client(&dsm_battery);

	if (!charge_monitor_dclient && (BAT_BOARD_ASIC == is_board_type)) {
		charge_monitor_dclient = dsm_register_client(&dsm_charge_monitor);
	}
#endif

	return 0;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
bk_batt_failed:
	cancel_delayed_work(&di->hisi_bci_monitor_work);
	power_supply_unregister(&di->ac);
ac_failed:
	power_supply_unregister(&di->usb);
usb_failed:
	power_supply_unregister(&di->bat);
#else
bk_batt_failed:
    cancel_delayed_work(&di->hisi_bci_monitor_work);
    power_supply_unregister(di->ac);
ac_failed:
    power_supply_unregister(di->usb);
usb_failed:
    power_supply_unregister(di->bat);
#endif
batt_failed:
	wake_lock_destroy(&low_power_lock);
	platform_set_drvdata(pdev, NULL);
	kfree(di);
	di = NULL;
	return ret;
}

static int hisi_bci_battery_remove(struct platform_device *pdev)
{
	struct hisi_bci_device_info *di = platform_get_drvdata(pdev);

	if (di == NULL) {
		hwlog_err("di is NULL!\n");
		return -ENODEV;
	}

	hisi_unregister_notifier(&di->nb, 1);
	cancel_delayed_work(&di->hisi_bci_monitor_work);
	wake_lock_destroy(&low_power_lock);
	platform_set_drvdata(pdev, NULL);
	kfree(di);
	di = NULL;

	return 0;
}

static void hisi_bci_battery_shutdown(struct platform_device *pdev)
{
	struct hisi_bci_device_info *di = platform_get_drvdata(pdev);

	hwlog_info("%s ++\n", __func__);
	if (di == NULL) {
		hwlog_err("di is NULL!\n");
		return;
	}

	hisi_unregister_notifier(&di->nb, 1);
	cancel_delayed_work(&di->hisi_bci_monitor_work);
	wake_lock_destroy(&low_power_lock);
	hwlog_info("%s --\n", __func__);

	return;
}

#ifdef CONFIG_PM
static int hisi_bci_battery_suspend(struct platform_device *pdev,
				    pm_message_t state)
{
	struct hisi_bci_device_info *di = platform_get_drvdata(pdev);

	if (di == NULL) {
		hwlog_err("di is NULL!\n");
		return -ENODEV;
	}
	hwlog_info("%s:+\n", __func__);
	suspend_capacity = hisi_battery_capacity();
	cancel_delayed_work(&di->hisi_bci_monitor_work);
	hwlog_info("%s:-\n", __func__);
	return 0;
}

static int hisi_bci_battery_resume(struct platform_device *pdev)
{
	struct hisi_bci_device_info *di = platform_get_drvdata(pdev);
	int i = 0, resume_capacity = 0;

	if (di == NULL) {
		hwlog_err("di is NULL!\n");
		return -ENODEV;
	}

	hwlog_info("%s:+\n", __func__);
	capacity_debounce_flag = true;

	resume_capacity = hisi_battery_capacity();
	if (di->charge_status == POWER_SUPPLY_STATUS_DISCHARGING
	    || di->charge_status == POWER_SUPPLY_STATUS_NOT_CHARGING) {
		if ((suspend_capacity - resume_capacity) >= 2) {
			capacity_sum = 0;
			for (i = 0; i < WINDOW_LEN; i++) {
				capacity_filter[i] = resume_capacity;
				capacity_sum += capacity_filter[i];
			}
		}
	}
#if defined (CONFIG_HUAWEI_DSM)
	g_curr_zero_times = 0;
#endif
	schedule_delayed_work(&di->hisi_bci_monitor_work, 0);
	hwlog_info("%s:-\n", __func__);
	return 0;
}
#endif /* CONFIG_PM */

static struct class *hw_power_class;
struct class *hw_power_get_class(void)
{
	if (NULL == hw_power_class) {
		hw_power_class = class_create(THIS_MODULE, "hw_power");
		if (IS_ERR(hw_power_class)) {
			hwlog_err("hw_power_class create fail");
			return NULL;
		}
	}
	return hw_power_class;
}
EXPORT_SYMBOL_GPL(hw_power_get_class);

static struct of_device_id hisi_bci_battery_match_table[] = {
	{
	 .compatible = "huawei,hisi_bci_battery",
	 .data = NULL,
	 },
	{
	 },
};

static struct platform_driver hisi_bci_battery_driver = {
	.probe = hisi_bci_battery_probe,
	.remove = hisi_bci_battery_remove,
#ifdef CONFIG_PM
	.suspend = hisi_bci_battery_suspend,
	.resume = hisi_bci_battery_resume,
#endif
	.shutdown = hisi_bci_battery_shutdown,
	.driver = {
		   .name = "huawei,hisi_bci_battery",
		   .owner = THIS_MODULE,
		   .of_match_table = of_match_ptr(hisi_bci_battery_match_table),
		   },
};

static int __init hisi_battery_init(void)
{
	return platform_driver_register(&hisi_bci_battery_driver);
}

module_init(hisi_battery_init);

static void __exit hisi_battery_exit(void)
{
	platform_driver_unregister(&hisi_bci_battery_driver);
}

module_exit(hisi_battery_exit);

MODULE_LICENSE("GPL");
MODULE_ALIAS("hisi_bci");
MODULE_AUTHOR("HISILICON");
