/*
 * Copyright (C) huawei company
 *
 * This	program	is free	software; you can redistribute it and/or modify
 * it under	the	terms of the GNU General Public	License	version	2 as
 * published by	the	Free Software Foundation.
 * Filename:  sensor_detect.c
 *
 * Discription: some functions of sensorhub power
 *
 * Owner:DIVS_SENSORHUB
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/err.h>
#include <linux/delay.h>
#include "inputhub_route.h"
#include "inputhub_bridge.h"
#include "rdr_sensorhub.h"
#include "protocol.h"
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <linux/types.h>
#include <linux/wakelock.h>
#include <sensor_info.h>
#include "sensor_sys_info.h"
#include <sensor_detect.h>
#include <sensor_debug.h>
#include <linux/mtd/hisi_nve_interface.h>
#include <linux/of.h>
#include <linux/of_gpio.h>
#include <linux/rtc.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <huawei_platform/devdetect/hw_dev_dec.h>
#endif
#include <linux/regulator/consumer.h>
#include <linux/of_device.h>
#include <huawei_platform/inputhub/sensorhub.h>
#ifdef CONFIG_HUAWEI_DSM
#include <dsm/dsm_pub.h>
#endif

#define HANDPRESS_DEFAULT_STATE		"huawei,default-state"
#define ADAPT_SENSOR_LIST_NUM           20
#define MAX_FILE_ID	64

static struct sensor_redetect_state s_redetect_state ;
static struct wake_lock sensor_rd;
static struct work_struct redetect_work;
static const char *str_soft_para = "softiron_parameter";

int akm_cal_algo;

extern u8 phone_color;
extern u8 tplcd_manufacture;
extern pkt_sys_dynload_req_t *dyn_req ;
extern uint16_t sensorlist[SENSOR_LIST_NUM] ;
extern char sensor_chip_info[SENSOR_MAX][MAX_CHIP_INFO_LEN];
extern int rohm_rgb_flag;
extern int avago_rgb_flag;
extern int txc_ps_flag;
extern int ams_tmd2620_ps_flag;
extern int avago_apds9110_ps_flag;
extern int g_iom3_state;
extern int iom3_power_state;
extern char *sar_calibrate_order;
extern int hifi_supported;
struct sensorlist_info sensorlist_info[SENSOR_MAX];

static struct gyro_platform_data gyro_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval = 10,
	.axis_map_x = 1,
	.axis_map_y = 0,
	.axis_map_z = 2,
	.negate_x = 1,
	.negate_y = 0,
	.negate_z = 1,
	.gpio_int1 = 210,
	.gpio_int2 = 0,
	.gpio_int2_sh = 0,
};

static struct g_sensor_platform_data gsensor_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval = 10,
	.axis_map_x = 1,
	.axis_map_y = 0,
	.axis_map_z = 2,
	.negate_x = 0,
	.negate_y = 1,
	.negate_z = 0,
	.gpio_int1 = 208,
	.gpio_int2 = 0,
	.gpio_int2_sh = 0,
	.calibrate_style = 0,
};

struct compass_platform_data mag_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval = 10,
	.outbit = 0,
	.axis_map_x = 0,
	.axis_map_y = 1,
	.axis_map_z = 2,
	.soft_filter = 0,
	.calibrate_method=1,
	.charger_trigger=0,
};

struct als_platform_data als_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.threshold_value = 1,
	.GA1 = 4166,
	.GA2 = 3000,
	.GA3 = 3750,
	.COE_B = 0,
	.COE_C = 0,
	.COE_D = 0,
	.gpio_int1 = 206,
	.atime = 0xdb,
	.again = 1,
	.poll_interval = 1000,
	.init_time = 150,
	.als_phone_type = 0,
	.als_phone_version = 0,
};

static struct ps_platform_data ps_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.min_proximity_value = 750,
	.pwindows_value = 100,
	.pwave_value = 60,
	.threshold_value = 70,
	.rdata_under_sun = 5500,
	.ps_pulse_count = 5,
	.gpio_int1 = 206,
	.persistent = 0x33,
	.ptime = 0xFF,
	.poll_interval = 250,
	.init_time = 100,
};

struct airpress_platform_data airpress_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval = 1000,
};

static struct handpress_platform_data handpress_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.bootloader_type = 0,
	.poll_interval = 500,
};

struct cap_prox_platform_data cap_prox_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.init_reg_val = {
			 0x00010005, 0x00020529, 0x000300cc, 0x00040001,
			 0x00050F55,
			 0x00069905, 0x000700e8, 0x00080200, 0x00090000,
			 0x000a000C, 0x00798000,
			 0x000b9905, 0x000c00e8, 0x000d0200, 0x000e0000,
			 0x000f000C, 0x007a8000},
	.poll_interval = 200,
};

struct sar_platform_data sar_pdata = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval = 200,
	.calibrate_type = 5,
};

static struct gps_4774_platform_data gps_4774_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.poll_interval = 50,
	.gpio1_gps_cmd_ap = 200,
	.gpio1_gps_cmd_sh = 230,
	.gpio2_gps_ready_ap = 213,
	.gpio2_gps_ready_sh = 242,
	.gpio3_wakeup_gps_ap = 214,
	.gpio3_wakeup_gps_sh = 243,
};

static struct fingerprint_platform_data fingerprint_data =
{
	.bustype = TAG_SPI,
	.busnum = 2,
	.reg = 0xFC,
	.chip_id =0x021b,
	.gpio_irq =207,
	.gpio_irq_sh =236,
	.gpio_reset = 149,
	.gpio_cs = 218,
	.poll_interval =50,
};

static struct key_platform_data key_data = {
	.bustype = TAG_I2C,
	.busnum = 0,
	.i2c_address = 0x27,
	.i2c_address_bootloader = 0x28,
	.poll_interval = 30,
};

static struct sensor_detect_manager s_detect_manager[SENSOR_MAX] = {
    {"acc", 3,ACC,DET_INIT,TAG_ACCEL, &gsensor_data, sizeof(gsensor_data)},
    {"mag",3, MAG,DET_INIT,TAG_MAG, &mag_data, sizeof(mag_data)},
    {"gyro",4, GYRO,DET_INIT,TAG_GYRO, &gyro_data, sizeof(gyro_data)},
    {"als",3, ALS,DET_INIT,TAG_ALS, &als_data, sizeof(als_data)},
    {"ps", 2,PS,DET_INIT,TAG_PS, &ps_data, sizeof(ps_data)},
    {"airpress", 8,AIRPRESS,DET_INIT,TAG_PRESSURE, &airpress_data, sizeof(airpress_data)},
    {"handpress",9, HANDPRESS,DET_INIT,TAG_HANDPRESS, &handpress_data, sizeof(handpress_data)},
    {"cap_prox",8, CAP_PROX,DET_INIT,TAG_CAP_PROX, &sar_pdata, sizeof(sar_pdata)},
    {"gps_4774_i2c", 11,GPS_4774_I2C,DET_INIT,TAG_GPS_4774_I2C,&gps_4774_data,sizeof(gps_4774_data)},
    {"fingerprint", 11, FINGERPRINT, DET_INIT, TAG_FP, &fingerprint_data, sizeof(fingerprint_data)},
    {"key", 3, KEY, DET_INIT, TAG_KEY, &key_data, sizeof(key_data)},
};

SENSOR_DETECT_LIST get_id_by_sensor_tag(int tag)
{
	int i = 0;
	for(i = 0; i < SENSOR_MAX; i++)
	{
		if(s_detect_manager[i].tag == tag)
			break;
	}
	return i;
}

int read_airpress_calibrate_data_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t pkg_ap;
	read_info_t pkg_mcu;
	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = AIRPRESS_CALIDATA_NV_NUM;
	user_info.valid_size = AIRPRESS_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "AIRDATA", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	ret = hisi_nve_direct_access(&user_info);
	if (ret != 0) {
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}
	/*send to mcu*/
	pkg_ap.tag = TAG_PRESSURE;
	pkg_ap.cmd = CMD_AIRPRESS_SET_CALIDATA_REQ;
	pkg_ap.wr_buf = (const void *)&airpress_data;
	pkg_ap.wr_len = sizeof(airpress_data);
	memcpy(&airpress_data.offset, user_info.nv_data,
	       AIRPRESS_CALIDATA_NV_SIZE);
	hwlog_info("***%s***\n", __func__);
	ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
	if (ret != 0) {
		hwlog_err("set airpress_sensor data failed, ret = %d!\n", ret);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CFG_DATA, __func__,
			       "set airpress_sensor data failed\n");
		return -1;
	}
	if (pkg_mcu.errno != 0) {
		hwlog_err("set airpress_sensor offset fail,err=%d\n",
			  pkg_mcu.errno);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CFG_DATA, __func__,
			       "set airpress_sensor offset fail\n");
	} else {
		hwlog_info("send airpress_sensor data %d to mcu success\n",
			   airpress_data.offset);
	}

	return 0;
}

extern union sar_calibrate_data sar_calibrate_datas;
int read_cap_prox_calibrate_data_from_nv(void)
{
	int ret = 0;
	struct hisi_nve_info_user user_info;
	write_info_t pkg_ap;
	read_info_t pkg_mcu;

	if (strlen(sensor_chip_info[CAP_PROX]) == 0)
		return -1;

	memset(&user_info, 0, sizeof(user_info));
	memset(&pkg_ap, 0, sizeof(pkg_ap));

	/*read from nv*/
	user_info.nv_operation = NV_READ_TAG;
	user_info.nv_number = CAP_PROX_CALIDATA_NV_NUM;
	user_info.valid_size = CAP_PROX_CALIDATA_NV_SIZE;
	strncpy(user_info.nv_name, "Csensor", sizeof(user_info.nv_name));
	user_info.nv_name[sizeof(user_info.nv_name) - 1] = '\0';
	ret = hisi_nve_direct_access(&user_info);
	if (ret != 0) {
		hwlog_err("nve_direct_access read error(%d)\n", ret);
		return -1;
	}

	//send to mcu
	pkg_ap.tag = TAG_CAP_PROX;
	pkg_ap.cmd = CMD_CAP_PROX_SET_CALIDATA_REQ;
	if (!strncmp(sensor_chip_info[CAP_PROX], "huawei,cypress_sar_psoc4000", strlen("huawei,cypress_sar_psoc4000"))){
		memcpy((void *)&sar_calibrate_datas, user_info.nv_data, sizeof(sar_calibrate_datas));
		pkg_ap.wr_buf = (const void *)&sar_calibrate_datas;
		pkg_ap.wr_len = sizeof(sar_calibrate_datas);
		hwlog_info("idac:%d, rawdata:%d length:%d %d\n",
				sar_calibrate_datas.cypres_cali_data.sar_idac,
				sar_calibrate_datas.cypres_cali_data.raw_data,
				sizeof(sar_calibrate_datas), pkg_ap.wr_len);
	} else if(!strncmp(sensor_chip_info[CAP_PROX], "huawei,semtech-sx9323", strlen("huawei,semtech-sx9323"))){
		memcpy((void *)&sar_calibrate_datas, user_info.nv_data, sizeof(sar_calibrate_datas));
		pkg_ap.wr_buf = (const void *)&sar_calibrate_datas;
		pkg_ap.wr_len = sizeof(sar_calibrate_datas);
		hwlog_info("sx9323:offset=%d, diff=%d length:%d %d\n",
				sar_calibrate_datas.semtech_cali_data.offset,
				sar_calibrate_datas.semtech_cali_data.diff,
				sizeof(sar_calibrate_datas), pkg_ap.wr_len);
	} 	else {
		pkg_ap.wr_buf = (const void *)&sar_calibrate_datas;
		pkg_ap.wr_len = sizeof(sar_calibrate_datas);
		memcpy(&sar_calibrate_datas, user_info.nv_data,
		       sizeof(sar_calibrate_datas));
		memcpy(sar_pdata.sar_datas.adux_data.swap_flag, user_info.nv_data, 28);
		hwlog_info("CAP_PROX cal_offset[0],digi_offset[0]:%x,%x\n",sar_calibrate_datas.cap_cali_data.cal_offset[0],sar_calibrate_datas.cap_cali_data.digi_offset[0]);
		hwlog_info("CAP_PROX cal_fact_base[0],swap_flag[0]:%x,%x\n",sar_calibrate_datas.cap_cali_data.cal_fact_base[0], sar_calibrate_datas.cap_cali_data.swap_flag[0]);
	}

	ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
	if (ret != 0) {
		hwlog_err("set cap_prox_sensor data failed, ret = %d!\n", ret);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CFG_DATA, __func__,
			       "set cap_prox_sensor data failed\n");
		return ret;
	} else {
		hwlog_info("send cap_prox_sensor data to mcu success\n");
	}

	return 0;
}
void read_sensorlist_info(struct device_node *dn, int sensor)
{
	int temp = 0;
	char *chip_info = NULL;

//for sensorlist parameters
	if(0 <= of_property_read_string(dn, "sensorlist_name", (const char **)&chip_info))
	{
		strncpy(sensorlist_info[sensor].name, chip_info, MAX_CHIP_INFO_LEN-1);
		sensorlist_info[sensor].name[MAX_CHIP_INFO_LEN-1] = '\0';
		hwlog_info("sensor chip info name %s\n", chip_info);
		hwlog_info("sensor SENSOR_DETECT_LIST %d get name %s\n", sensor, sensorlist_info[sensor].name);
	}
	else
		sensorlist_info[sensor].name[0] = '\0';

	if(0 == of_property_read_string(dn, "vendor", (const char **)&chip_info))
	{
		strncpy(sensorlist_info[sensor].vendor, chip_info, MAX_CHIP_INFO_LEN-1);
		sensorlist_info[sensor].vendor[MAX_CHIP_INFO_LEN-1] = '\0';
		hwlog_info("sensor SENSOR_DETECT_LIST %d get vendor %s\n", sensor, sensorlist_info[sensor].vendor);
	}
	else
		sensorlist_info[sensor].name[0] = '\0';

	if (0 == of_property_read_u32(dn, "version", &temp))
	{
		sensorlist_info[sensor].version= temp;
		hwlog_info("sensor SENSOR_DETECT_LIST %d get version %d\n", sensor, temp);
	}
	else
		sensorlist_info[sensor].version = -1;
	if (0 == of_property_read_u32(dn, "maxRange", &temp))
	{
		sensorlist_info[sensor].maxRange= temp;
		hwlog_info("sensor SENSOR_DETECT_LIST %d get maxRange %d\n", sensor, temp);
	}
	else
		sensorlist_info[sensor].maxRange = -1;
	if (0 == of_property_read_u32(dn, "resolution", &temp))
	{
		sensorlist_info[sensor].resolution= temp;
		hwlog_info("sensor SENSOR_DETECT_LIST %d get resolution %d\n", sensor, temp);
	}
	else
		sensorlist_info[sensor].resolution = -1;
	if (0 == of_property_read_u32(dn, "power", &temp))
	{
		sensorlist_info[sensor].power= temp;
		hwlog_info("sensor SENSOR_DETECT_LIST %d get power %d\n", sensor, temp);
	}
	else
		sensorlist_info[sensor].power = -1;
	if (0 == of_property_read_u32(dn, "minDelay", &temp))
	{
		sensorlist_info[sensor].minDelay= temp;
		hwlog_info("sensor SENSOR_DETECT_LIST %d get minDelay %d\n", sensor, temp);
	}
	else
		sensorlist_info[sensor].minDelay = -1;
	if (0 == of_property_read_u32(dn, "fifoReservedEventCount", &temp))
	{
		sensorlist_info[sensor].fifoReservedEventCount= temp;
		hwlog_info("sensor SENSOR_DETECT_LIST %d get fifoReservedEventCount %d\n", sensor, temp);
	}
	else
		sensorlist_info[sensor].fifoReservedEventCount = -1;
	if (0 == of_property_read_u32(dn, "fifoMaxEventCount", &temp))
	{
		sensorlist_info[sensor].fifoMaxEventCount= temp;
		hwlog_info("sensor SENSOR_DETECT_LIST %d get fifoMaxEventCount %d\n", sensor, temp);
	}
	else
		sensorlist_info[sensor].fifoMaxEventCount = -1;
	if (0 == of_property_read_u32(dn, "maxDelay", &temp))
	{
		sensorlist_info[sensor].maxDelay= temp;
		hwlog_info("sensor SENSOR_DETECT_LIST %d get maxDelay %d\n", sensor, temp);
	}
	else
		sensorlist_info[sensor].maxDelay = -1;
	if (0 == of_property_read_u32(dn, "flags", &temp))
	{
		sensorlist_info[sensor].flags= temp;
		hwlog_info("sensor SENSOR_DETECT_LIST %d get flags %d\n", sensor, temp);
	}
	else
		sensorlist_info[sensor].flags = -1;
	return;
}
static void read_acc_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, ACC);

	temp = of_get_named_gpio(dn, "gpio_int1", 0);
	if (temp < 0)
		hwlog_err("%s:read gpio_int1 fail\n", __func__);
	else
		gsensor_data.gpio_int1 = (uint8_t) temp;

	temp = of_get_named_gpio(dn, "gpio_int2", 0);
	if (temp < 0)
		hwlog_err("%s:read gpio_int2 fail\n", __func__);
	else
		gsensor_data.gpio_int2 = (uint8_t) temp;

	if (of_property_read_u32(dn, "gpio_int2_sh", &temp))
		hwlog_err("%s:read acc gpio_int2_sh fail\n", __func__);
	else
		gsensor_data.gpio_int2_sh = (uint8_t) temp;

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read acc poll_interval fail\n", __func__);
	else
		gsensor_data.poll_interval = (uint16_t) temp;

	if (of_property_read_u32(dn, "calibrate_style", &temp))
		hwlog_err("%s:read acc calibrate_style fail\n", __func__);
	else
		gsensor_data.calibrate_style = (uint8_t) temp;

	if (of_property_read_u32(dn, "axis_map_x", &temp))
		hwlog_err("%s:read acc axis_map_x fail\n", __func__);
	else
		gsensor_data.axis_map_x = (uint8_t) temp;

	if (of_property_read_u32(dn, "axis_map_y", &temp))
		hwlog_err("%s:read acc axis_map_y fail\n", __func__);
	else
		gsensor_data.axis_map_y = (uint8_t) temp;

	if (of_property_read_u32(dn, "axis_map_z", &temp))
		hwlog_err("%s:read acc axis_map_z fail\n", __func__);
	else
		gsensor_data.axis_map_z = (uint8_t) temp;

	if (of_property_read_u32(dn, "negate_x", &temp))
		hwlog_err("%s:read acc negate_x fail\n", __func__);
	else
		gsensor_data.negate_x = (uint8_t) temp;

	if (of_property_read_u32(dn, "negate_y", &temp))
		hwlog_err("%s:read acc negate_y fail\n", __func__);
	else
		gsensor_data.negate_y = (uint8_t) temp;

	if (of_property_read_u32(dn, "negate_z", &temp))
		hwlog_err("%s:read acc negate_z fail\n", __func__);
	else
		gsensor_data.negate_z = (uint8_t) temp;

	if (of_property_read_u32(dn, "reg", &temp))
		hwlog_err("%s:read acc reg fail\n", __func__);
	else
		gsensor_data.i2c_address = (uint8_t) temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read acc file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read acc sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t) temp;
	read_sensorlist_info(dn, ACC);
}

static void read_mag_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, MAG);

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read mag poll_interval fail\n", __func__);
	else
		mag_data.poll_interval = (uint16_t) temp;

	if (of_property_read_u32(dn, "axis_map_x", &temp))
		hwlog_err("%s:read mag axis_map_x fail\n", __func__);
	else
		mag_data.axis_map_x = (uint8_t) temp;

	if (of_property_read_u32(dn, "axis_map_y", &temp))
		hwlog_err("%s:read mag axis_map_y fail\n", __func__);
	else
		mag_data.axis_map_y = (uint8_t) temp;

	if (of_property_read_u32(dn, "axis_map_z", &temp))
		hwlog_err("%s:read mag axis_map_z fail\n", __func__);
	else
		mag_data.axis_map_z = (uint8_t) temp;

	if (of_property_read_u32(dn, "negate_x", &temp))
		hwlog_err("%s:read mag negate_x fail\n", __func__);
	else
		mag_data.negate_x = (uint8_t) temp;

	if (of_property_read_u32(dn, "negate_y", &temp))
		hwlog_err("%s:read mag negate_y fail\n", __func__);
	else
		mag_data.negate_y = (uint8_t) temp;

	if (of_property_read_u32(dn, "negate_z", &temp))
		hwlog_err("%s:read mag negate_z fail\n", __func__);
	else
		mag_data.negate_z = (uint8_t) temp;

	if (of_property_read_u32(dn, "outbit", &temp))
		hwlog_err("%s:read mag outbit fail\n", __func__);
	else
		mag_data.outbit = (uint8_t) temp;

	if (of_property_read_u32(dn, "softfilter", &temp))
		hwlog_err("%s:read mag softfilter fail; use default value:%d\n",
			  __func__, mag_data.soft_filter);
	else
		mag_data.soft_filter = (uint8_t) temp;

	if (of_property_read_u32(dn, "calibrate_method", &temp))
		hwlog_err("%s:read mag calibrate_method fail\n", __func__);
	else
		mag_data.calibrate_method = (uint8_t) temp;

	if (of_property_read_u32(dn, "charger_trigger", &temp))
		hwlog_err("%s:read mag charger_trigger fail; use default value:%d\n",
					__func__, mag_data.charger_trigger);
	else
		mag_data.charger_trigger = (uint8_t)temp;

	if (of_property_read_u32(dn, "akm_cal_algo", &temp)) {
		hwlog_err("%s:read mag akm_cal_algo fail\n", __func__);
		akm_cal_algo = 0;
	} else {
		if (1 == temp) {
			akm_cal_algo = 1;
		} else {
			akm_cal_algo = 0;
		}
		hwlog_info("%s: mag akm_cal_algo=%d.\n", __func__,
			   akm_cal_algo);
	}

	if (of_property_read_u32(dn, "reg", &temp))
		hwlog_err("%s:read mag reg fail\n", __func__);
	else
		mag_data.i2c_address = (uint8_t) temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read mag file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read mag sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t) temp;

	temp = of_get_named_gpio(dn, "gpio_reset", 0);
	if (temp < 0)
		hwlog_err("%s:read gpio_rst fail\n", __func__);
	else
		mag_data.gpio_rst = (uint8_t) temp;
	read_sensorlist_info(dn, MAG);
}

static void read_gyro_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, GYRO);

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read mag poll_interval fail\n", __func__);
	else
		gyro_data.poll_interval = (uint16_t) temp;

	if (of_property_read_u32(dn, "axis_map_x", &temp))
		hwlog_err("%s:read gyro axis_map_x fail\n", __func__);
	else
		gyro_data.axis_map_x = (uint8_t) temp;

	if (of_property_read_u32(dn, "axis_map_y", &temp))
		hwlog_err("%s:read gyro axis_map_y fail\n", __func__);
	else
		gyro_data.axis_map_y = (uint8_t) temp;

	if (of_property_read_u32(dn, "axis_map_z", &temp))
		hwlog_err("%s:read gyro axis_map_z fail\n", __func__);
	else
		gyro_data.axis_map_z = (uint8_t) temp;

	if (of_property_read_u32(dn, "negate_x", &temp))
		hwlog_err("%s:read gyro negate_x fail\n", __func__);
	else
		gyro_data.negate_x = (uint8_t) temp;

	if (of_property_read_u32(dn, "negate_y", &temp))
		hwlog_err("%s:read gyro negate_y fail\n", __func__);
	else
		gyro_data.negate_y = (uint8_t) temp;

	if (of_property_read_u32(dn, "negate_z", &temp))
		hwlog_err("%s:read gyro negate_z fail\n", __func__);
	else
		gyro_data.negate_z = (uint8_t) temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read gyro file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read gyro sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t) temp;

	temp = of_get_named_gpio(dn, "gpio_int1", 0);
	if (temp < 0)
		hwlog_err("%s:read gpio_int1 fail\n", __func__);
	else
		gyro_data.gpio_int1 = (uint8_t) temp;
	read_sensorlist_info(dn, GYRO);
}

static void read_ps_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, PS);
	if (!strncmp(sensor_chip_info[PS], "huawei,txc-pa224",
	     sizeof("huawei,txc-pa224"))) {
		txc_ps_flag = 1;
		hwlog_err("%s:txc_ps i2c_address suc,%d \n", __func__, temp);
	}

	if (!strncmp(sensor_chip_info[PS], "huawei,ams-tmd2620",
	     sizeof("huawei,ams-tmd2620"))) {
		ams_tmd2620_ps_flag = 1;
		hwlog_err("%s:ams_tmd2620_ps i2c_address suc,%d \n", __func__,
			  temp);
	}

	if (!strncmp(sensor_chip_info[PS], "huawei,avago-apds9110",
	     sizeof("huawei,avago-apds9110"))) {
		avago_apds9110_ps_flag = 1;
		hwlog_err("%s:avago_apds9110_ps i2c_address suc,%d \n", __func__,
			  temp);
	}

	temp = of_get_named_gpio(dn, "gpio_int1", 0);
	if (temp < 0)
		hwlog_err("%s:read gpio_int1 fail\n", __func__);
	else
		ps_data.gpio_int1 = (uint8_t) temp;

	if (of_property_read_u32(dn, "min_proximity_value", &temp))
		hwlog_err("%s:read mag min_proximity_value fail\n", __func__);
	else
		ps_data.min_proximity_value = temp;

	if (of_property_read_u32(dn, "pwindows_value", &temp))
		hwlog_err("%s:read pwindows_value fail\n", __func__);
	else
		ps_data.pwindows_value = temp;

	if (of_property_read_u32(dn, "pwave_value", &temp))
		hwlog_err("%s:read pwave_value fail\n", __func__);
	else
		ps_data.pwave_value = temp;

	if (of_property_read_u32(dn, "threshold_value", &temp))
		hwlog_err("%s:read threshold_value fail\n", __func__);
	else
		ps_data.threshold_value = temp;

	if (of_property_read_u32(dn, "rdata_under_sun", &temp))
		hwlog_err("%s:read rdata_under_sun fail\n", __func__);
	else
		ps_data.rdata_under_sun = temp;

	if (of_property_read_u32(dn, "ps_pulse_count", &temp))
		hwlog_err("%s:read ps_pulse_count fail\n", __func__);
	else
		ps_data.ps_pulse_count = (uint8_t) temp;

	if (of_property_read_u32(dn, "persistent", &temp))
		hwlog_err("%s:read persistent fail\n", __func__);
	else
		ps_data.persistent = (uint8_t) temp;

	if (of_property_read_u32(dn, "ptime", &temp))
		hwlog_err("%s:read ptime fail\n", __func__);
	else
		ps_data.ptime = (uint8_t) temp;

	if (of_property_read_u32(dn, "p_on", &temp))
		hwlog_err("%s:read p_on fail\n", __func__);
	else
		ps_data.p_on = (uint8_t) temp;

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read poll_interval fail\n", __func__);
	else
		ps_data.poll_interval = (uint16_t) temp;

	if (of_property_read_u32(dn, "init_time", &temp))
		hwlog_err("%s:read init_time fail\n", __func__);
	else
		ps_data.init_time = (uint16_t) temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read ps file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read ps sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t) temp;
	read_sensorlist_info(dn, PS);
}

static void read_airpress_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, AIRPRESS);

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read poll_interval fail\n", __func__);
	else
		airpress_data.poll_interval = (uint16_t) temp;

	if (of_property_read_u32(dn, "reg", &temp))
		hwlog_err("%s:read airpress reg fail\n",__func__);
	else
		airpress_data.i2c_address=(uint8_t)temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read airpress file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read ps sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t) temp;
	read_sensorlist_info(dn, AIRPRESS);
}

static void read_handpress_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, HANDPRESS);

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read poll_interval fail\n", __func__);
	else
		handpress_data.poll_interval = (uint16_t) temp;
	hwlog_info("get handpress dev from dts.sensor name=%d\n",
		   handpress_data.poll_interval);
	if (of_property_read_u32(dn, "bootloader_type", &temp))
		hwlog_err("%s:read handpress file_id_fw fail\n", __func__);
	else
		handpress_data.bootloader_type = (uint8_t)temp;

	hwlog_info("bootloader_type:%d\n", handpress_data.bootloader_type);
	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read handpress file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp;
	dyn_req->file_count++;
	hwlog_info("get handpress dev from dyn_req->file_count=%d\n",
		   dyn_req->file_count);
#if 0
	if (of_property_read_u32(dn, "file_id_fw", &temp))
		hwlog_err("%s:read handpress file_id_fw fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp;
	dyn_req->file_count++;
	hwlog_info("get handpress dev from dyn_req->file_count=%d\n",
		   dyn_req->file_count);
#endif
	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read ps sensor_list_info_id fail\n", __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t) temp;
	hwlog_info("get handpress dev from temp=%d; ++sensorlist[0]:%d\n", temp,
		   sensorlist[0] - 1);
}

static void read_capprox_data_from_dts(struct device_node *dn)
{
	uint16_t threshold_to_ap = 0;
	int temp = 0;
	int i2c_address = 0;
	int i2c_bus_num = 0;
	uint16_t *threshold_to_modem = NULL;
	uint32_t *init_reg_val = NULL;
	uint32_t init_reg_val_default[17] = {
			 0x00010005, 0x00020529, 0x000300cc, 0x00040001,
			 0x00050F55,
			 0x00069905, 0x000700e8, 0x00080200, 0x00090000,
			 0x000a000C, 0x00798000,
			 0x000b9905, 0x000c00e8, 0x000d0200, 0x000e0000,
			 0x000f000C, 0x007a8000};
	read_chip_info(dn, CAP_PROX);

	temp = of_get_named_gpio(dn, "gpio_int", 0);
	if (temp < 0)
		hwlog_err("%s:read gpio_int1 fail\n", __func__);
	else
		sar_pdata.gpio_int = (uint8_t) temp;

	if (of_property_read_u32(dn, "poll_interval", &temp))
		hwlog_err("%s:read poll_interval fail\n", __func__);
	else
		sar_pdata.poll_interval = (uint16_t) temp;
	hwlog_info("sar.poll_interval: %d\n", sar_pdata.poll_interval);

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read sar file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp;
	dyn_req->file_count++;

	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read sar sensor_list_info_id fail\n",
			  __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t) temp;
	if (of_property_read_u32(dn, "calibrate_type", &temp))
		hwlog_err("%s:read sar calibrate_type fail\n", __func__);
	else
		sar_pdata.calibrate_type=temp;
#if 1
	if (of_property_read_string(dn, "calibrate_order", &sar_calibrate_order)) {
		hwlog_err("read calibrate order err.\n");
	}
	hwlog_info("calibrate order:%s\n", sar_calibrate_order);
#endif
	if (!strncmp(sensor_chip_info[CAP_PROX], "huawei,cypress_sar_psoc4000", strlen("huawei,cypress_sar_psoc4000"))) {
		if (of_property_read_u16(dn, "to_ap_threshold", &threshold_to_ap))
			sar_pdata.sar_datas.cypress_data.threshold_to_ap = 0xC8;
		else
			sar_pdata.sar_datas.cypress_data.threshold_to_ap = (uint16_t)threshold_to_ap;

		threshold_to_modem = sar_pdata.sar_datas.cypress_data.threshold_to_modem;
		if (of_property_read_u16_array(dn, "to_modem_threshold", threshold_to_modem, 8)) {
			*threshold_to_modem =  0xC8;
			*(threshold_to_modem+1) = 0;
		}
		hwlog_info("ap:%u, modem:%u %u %u\n", threshold_to_ap, *threshold_to_modem, *(threshold_to_modem+1), *(threshold_to_modem+7));
	} else if (!strncmp(sensor_chip_info[CAP_PROX], "huawei,adi-adux1050", strlen("huawei,adi-adux1050"))) {
		init_reg_val = sar_pdata.sar_datas.adux_data.init_reg_val;
		if (of_property_read_u32_array(dn, "init_reg_val", init_reg_val, 10)) {
			hwlog_err("%s:read init_reg_val fail\n", __func__);
			memcpy(init_reg_val, init_reg_val_default, sizeof(init_reg_val_default));
		}
		hwlog_info("init_reg_val:%8x %8x\n", *init_reg_val, *(init_reg_val+9));

	}else if (!strncmp(sensor_chip_info[CAP_PROX], "huawei,semtech-sx9323", strlen("huawei,semtech-sx9323"))){
		if (of_property_read_u16(dn, "to_ap_threshold", &threshold_to_ap))
			sar_pdata.sar_datas.semteck_data.threshold_to_ap = 0xC8;
		else
			sar_pdata.sar_datas.semteck_data.threshold_to_ap = (uint16_t)threshold_to_ap;
		threshold_to_modem = sar_pdata.sar_datas.semteck_data.threshold_to_modem;
		if (of_property_read_u16_array(dn, "to_modem_threshold", threshold_to_modem, 8)) {
			*threshold_to_modem =  0xC8;
			*(threshold_to_modem+1) = 0;
		}
		hwlog_info("%u %u %u\n", *threshold_to_modem, *(threshold_to_modem+1), *(threshold_to_modem+7));
	}
	read_sensorlist_info(dn, CAP_PROX);
}

static void read_gps_4774_i2c_data_from_dts(struct device_node *dn)
{
	int temp = 0;

	read_chip_info(dn, GPS_4774_I2C);

	if (of_property_read_u32(dn, "gpio1_gps_cmd_ap", &temp))
		hwlog_err("%s:read gpio1_gps_cmd_ap fail\n", __func__);
	else
		gps_4774_data.gpio1_gps_cmd_ap = (uint8_t) temp;

	if (of_property_read_u32(dn, "gpio1_gps_cmd_sh", &temp))
		hwlog_err("%s:read gpio1_gps_cmd_sh fail\n", __func__);
	else
		gps_4774_data.gpio1_gps_cmd_sh = (uint8_t) temp;

	if (of_property_read_u32(dn, "gpio2_gps_ready_ap", &temp))
		hwlog_err("%s:read gpio2_gps_ready_ap fail\n", __func__);
	else
		gps_4774_data.gpio2_gps_ready_ap = (uint8_t) temp;

	if (of_property_read_u32(dn, "gpio2_gps_ready_sh", &temp))
		hwlog_err("%s:read gpio2_gps_ready_sh fail\n", __func__);
	else
		gps_4774_data.gpio2_gps_ready_sh = (uint8_t) temp;

	if (of_property_read_u32(dn, "gpio3_wakeup_gps_ap", &temp))
		hwlog_err("%s:read gpio3_wakeup_gps_ap fail\n", __func__);
	else
		gps_4774_data.gpio3_wakeup_gps_ap = (uint8_t) temp;

	if (of_property_read_u32(dn, "gpio3_wakeup_gps_sh", &temp))
		hwlog_err("%s:read gpio3_wakeup_gps_sh fail\n", __func__);
	else
		gps_4774_data.gpio3_wakeup_gps_sh = (uint8_t) temp;

	if (of_property_read_u32(dn, "file_id", &temp))
		hwlog_err("%s:read gps_4774_i2c file_id fail\n", __func__);
	else
		dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp;

	dyn_req->file_count++;

	hwlog_err("gps 4774 i2c file id is %d\n", temp);
	if (of_property_read_u32(dn, "sensor_list_info_id", &temp))
		hwlog_err("%s:read gps 4774 sensor_list_info_id fail\n",
			  __func__);
	else
		sensorlist[++sensorlist[0]] = (uint16_t) temp;
}
//read gpio reg chip id;
static void read_fingerprint_from_dts(struct device_node* dn)
{
    int temp = 0;
    read_chip_info(dn, FINGERPRINT);

    if (of_property_read_u32(dn, "file_id", &temp))
    { hwlog_err("%s:read fingerprint file_id fail\n", __func__); }
    else
    { dyn_req->file_list[dyn_req->file_count] = (uint16_t) temp; }

    dyn_req->file_count++;
    hwlog_err("fingerprint  file id is %d\n", temp);

    if (of_property_read_u32(dn, "chip_id_register", &temp))
    { hwlog_err("%s:read chip_id_register fail\n", __func__); }
    else
    { fingerprint_data.reg = (uint16_t) temp; }

    if (of_property_read_u32(dn, "chip_id_value", &temp))
    { hwlog_err("%s:read chip_id_value fail\n", __func__); }
    else
    { fingerprint_data.chip_id= (uint16_t) temp; }


    if (of_property_read_u32(dn, "gpio_irq", &temp))
    { hwlog_err("%s:read gpio_irq fail\n", __func__); }
    else
    { fingerprint_data.gpio_irq = (uint16_t) temp; }

    if (of_property_read_u32(dn, "gpio_irq_sh", &temp))
    { hwlog_err("%s:read gpio_irq_sh fail\n", __func__); }
    else
    { fingerprint_data.gpio_irq_sh = (uint16_t) temp; }

    if (of_property_read_u32(dn, "gpio_reset", &temp))
    { hwlog_err("%s:read gpio_reset fail\n", __func__); }
    else
    { fingerprint_data.gpio_reset = (uint16_t) temp; }

    if (of_property_read_u32(dn, "gpio_cs", &temp))
    { hwlog_err("%s:read gpio_cs fail\n", __func__); }
    else
    { fingerprint_data.gpio_cs = (uint16_t) temp; }

}

static void read_key_i2c_data_from_dts(struct device_node *dn)
{
	read_chip_info(dn, KEY);
	key_data.i2c_address = 0x27;
	dyn_req->file_list[dyn_req->file_count] = 59;
	dyn_req->file_count++;

	hwlog_info("key read dts\n");
}

static int get_adapt_file_id_for_dyn_load(void)
{
	u32 wia[ADAPT_SENSOR_LIST_NUM]={ 0 };
	struct property *prop = NULL;
	unsigned int i = 0;
	unsigned int len = 0;
	struct device_node *sensorhub_node = NULL;
	const char *name = "adapt_file_id";
	sensorhub_node =
		of_find_compatible_node(NULL, NULL, "huawei,sensorhub");
	if (!sensorhub_node) {
		hwlog_err("%s, can't find node sensorhub\n", __func__);
		return -1;
	}
	prop = of_find_property(sensorhub_node, name, NULL);
	if (!prop) {
		hwlog_err("%s! prop is NULL!\n", __func__);
		return -EINVAL;
	}
	if (!prop->value) {
		hwlog_err("%s! prop->value is NULL!\n", __func__);
		return -ENODATA;
	}
	len = prop->length /4;
	if(of_property_read_u32_array(sensorhub_node, name, wia, len))
	{
		hwlog_err("%s:read adapt_file_id from dts fail!\n", name);
		return -1;
	}
	for (i = 0; i < len; i++) {
		dyn_req->file_list[dyn_req->file_count] = wia[i];
		dyn_req->file_count++;
	}
	//find hifi supported or not
	if (0 == of_property_read_u32(sensorhub_node, "hifi_support", &i))
	{
		if(1 == i)
		{
			hifi_supported = 1;
			hwlog_info("sensor get hifi support %d\n", i);
		}
	}
	return 0;
}

/* delete the repeated file id by map table*/
static uint8_t check_file_list(uint8_t file_count, uint16_t *file_list)
{
	uint8_t map[MAX_FILE_ID];
	int i;
	uint8_t count = 0;

	memset(map, 0, sizeof(map));
	if ((file_count == 0) || (NULL == file_list)) {
		hwlog_err("%s, val invalid\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_DYNLOAD, __func__,
			       "val invalid\n");
		return count;
	}

	for (i = 0; i < file_count; i++) {
		if (file_list[i] < sizeof(map))
			map[file_list[i]]++;
	}

	for (i = 0; i < sizeof(map); i++) {
		if (map[i]) {
			file_list[count] = i;
			count++;
		}
	}

	return count;
}

static int get_adapt_sensor_list_id(void)
{
	u32 wia[ADAPT_SENSOR_LIST_NUM]={ 0 };
	struct property *prop = NULL;
	unsigned int i = 0, len = 0;
	struct device_node *sensorhub_node = NULL;
	const char *name = "adapt_sensor_list_id";
	sensorhub_node =
	    of_find_compatible_node(NULL, NULL, "huawei,sensorhub");
	if (!sensorhub_node) {
		hwlog_err("%s, can't find node sensorhub\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CFG_DATA, __func__,
			       "can't find node sensorhub\n");
		return -1;
	}
	prop = of_find_property(sensorhub_node, name, NULL);
	if (!prop) {
		hwlog_err("%s! prop is NULL!\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CFG_DATA, __func__,
			       " prop is NULL\n");
		return -EINVAL;
	}
	if (!prop->value) {
		hwlog_err("%s! prop->value is NULL!\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CFG_DATA, __func__,
			       "prop->value is NULL\n");
		return -ENODATA;
	}
	len = prop->length / 4;
	if (of_property_read_u32_array(sensorhub_node, name, wia, len)) {
		hwlog_err("%s:read adapt_sensor_list_id from dts fail!\n",
			  name);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CFG_DATA, __func__,
			       "read adapt_sensor_list_id from dts fail\n");
		return -1;
	}
	for (i = 0; i < len; i++) {
		sensorlist[sensorlist[0] + 1] = (uint16_t) wia[i];
		sensorlist[0]++;
	}
	return 0;
}

static int get_adapt_id_and_send(void)
{
	int ret = 0, i = 0;

	ret = get_adapt_file_id_for_dyn_load();
	if (ret < 0) {
		hwlog_err("get_adapt_file_id_for_dyn_load() failed!\n");
	}
	hwlog_info("get file id number = %d\n", dyn_req->file_count);

	ret = get_adapt_sensor_list_id();
	if (ret < 0) {
		hwlog_err("get_adapt_sensor_list_id() failed!\n");
	}

	sensorlist[0] = check_file_list(sensorlist[0], &sensorlist[1]);
	if (sensorlist[0] > 0) {
		hwlog_info
		    ("sensorhub after check, get sensor list id number = %d, list id: ",
		     sensorlist[0]);
		for (i = 0; i < sensorlist[0]; i++) {
			hwlog_info("--%d", sensorlist[i + 1]);
		}
		hwlog_info("\n");
	} else {
		hwlog_err("%s list num = 0, not send file_id to muc\n",
			  __func__);
		return -EINVAL;
	}

	dyn_req->file_count =
	    check_file_list(dyn_req->file_count, dyn_req->file_list);
	if (dyn_req->file_count) {
		hwlog_info
		    ("sensorhub after check, get dynload file id number = %d, fild id",
		     dyn_req->file_count);
		for (i = 0; i < dyn_req->file_count; i++) {
			hwlog_info("--%d", dyn_req->file_list[i]);
		}
		hwlog_info("\n");
		return send_fileid_to_mcu();
	} else {
		hwlog_err("%s file_count = 0, not send file_id to mcu\n",
			  __func__);
		return -EINVAL;
	}
}

static int handpress_sensor_detect(struct device_node *dn,
			struct handpress_platform_data *handpress_data)
{
	int ret = 0;
	int chip_check_result = 0;
	struct device_node *temp = NULL;
	int num_handpress = 0;
	const char *state = NULL;
	int chips = 0;
	u32 bus_num = 0;
	u32 id = 0, irq = 0, points = 0, reg = 0;
	char chip_value[12] = { 0xff, 0xff, 0x00 };
	char chip_check_cmd_default[8] =
			{ 0x01, 0x40, 0x01, 0x00, 0x00, 0xBE, 0xFF, 0x17 };
/*
	char chip_check_value_default[10] =
		{0x01, 0x00, 0x03, 0x00, 0x02, 0x00, 0xf7, 0x03, 0xff, 0x17};
*/
	char chip_check_cmd[8] = { 0x00 };
/*
	char chip_check_value[10] = {0x00};
*/

	ret = of_property_read_u32(dn, "bus_number", &bus_num);
	if (ret) {
		hwlog_err("get bus_num err ret:%d\n", ret);
		goto out;
	}
#if 0
	ret = of_property_read_u32(dn, "chip_id_register", &chip_id_reg);
	if (ret) {
		hwlog_err("get chip_id_reg err ret:%d\n", ret);
		goto out;
	}
#endif
	ret = of_property_read_u8_array(dn, "chip_check_cmd",
				&chip_check_cmd[0], 8);
	if (ret) {
		hwlog_err("get chip_check_cmd err ret:%d\n", ret);
		memcpy(chip_check_cmd, chip_check_cmd_default,
		       sizeof(chip_check_cmd));
		/*goto out;*/
	}
#if 0
	ret =
	    of_property_read_u8_array(dn, "chip_id_value", chip_check_value,
				      10);
	if (ret) {
		hwlog_err("get chip_id_value err ret:%d\n", ret);
		memcpy(chip_check_value, chip_check_value_default,
		       sizeof(chip_check_value));
		/*goto out;*/
	}
#endif
	while ((temp = of_get_next_child(dn, temp)))
		num_handpress++;

	if (!num_handpress)
		return -ECHILD;

	for_each_child_of_node(dn, temp) {
		ret = of_property_read_string(temp,
				HANDPRESS_DEFAULT_STATE, &state);
		if (!ret) {
			if (strncmp(state, "on", sizeof("on")) == 0) {
				if (chips >= CYPRESS_CHIPS) {
					hwlog_err("The number of chips overflow\n");
					break;
				}
				ret = of_property_read_u32(temp,
							"huawei,id", &id);
				if (ret) {
					hwlog_err("huawei,id ret:%d\n", ret);
					break;
				}
				handpress_data->id[chips] = id;
#if 0
				ret = of_property_read_u32(temp,
							"huawei,irq", &irq);
				if (ret) {
					hwlog_err("huawei,irq ret:%d\n", ret);
					break;
				}
				handpress_data->irq[chips] = irq;
#endif
				ret = of_property_read_u32(temp,
						"huawei,points", &points);
				if (ret) {
					hwlog_err("huawei, points ret:%d\n",
						  ret);
					break;
				}
				handpress_data->t_pionts[chips] = points;

				ret = of_property_read_u32(temp, "reg", &reg);
				if (ret) {
					hwlog_err("reg ret:%d\n", ret);
					break;
				}
				handpress_data->i2c_address[chips] = reg;
#if 0
				ret = mcu_i2c_rw(bus_num, reg, 0x00,
					       CMD_I2C_WRITE_ONLY_REQ,
					       sizeof(chip_check_cmd) /
					       sizeof(chip_check_cmd[0]),
					       chip_check_cmd);
				if (ret < 0) {
					hwlog_err("mcu_i2c_rw write ret:%d\n",
						  ret);
					chip_check_result |= 1 << id;
					continue;
				}
				msleep(10);
#endif
				ret = mcu_i2c_rw(bus_num, reg, 0x00,
						CMD_I2C_READ_ONLY_REQ,
					       sizeof(chip_value) /
					       sizeof(chip_value[0]),
					       chip_value);
				if (ret < 0) {
					hwlog_err("mcu_i2c_rw read ret:%d\n",
						  ret);
					chip_check_result |= 1 << id;
					continue;
				}
				hwlog_err("chip_value: %2x %2x %2x %2x\n",chip_value[0],chip_value[1],chip_value[2],chip_value[3]);
#if 0
				if (chip_value[1]) {
					chip_check_result |= 1 << id;
					hwlog_err
					    ("handpress detect err! chip[%d]:%x\n",
					     id, chip_value[1]);
					continue;
				}
#endif
				chips++;
			}
		}
	}

	if (!chip_check_result)
		ret = 0;
	else
		ret = -1;

	hwlog_info("handpress detect result:%d\n", ret);
out:
	return ret;
}
int cap_prox_sensor_detect(struct device_node *dn)
{
	write_info_t pkg_ap;
	read_info_t pkg_mcu;
	pkt_i2c_read_req_t pkt_i2c_read;
	int i = 0, ret = 0, i2c_address = 0, i2c_bus_num = 0;
	int register_add = 0, len = 0;
	u32 wia[10] = { 0 };
	struct property *prop = NULL;
	int sar_shared_flag = 0;

	ret = of_property_read_u32(dn, "shared_flag", &sar_shared_flag);
	if (!ret && sar_shared_flag) {
		hwlog_info("sar chip shared with key.\n");
		if (of_property_read_u32(dn, "bus_number", &i2c_bus_num)
			|| of_property_read_u32(dn, "reg", &i2c_address)) {
			hwlog_err("read sar sensor bus/reg err.\n");
		}
		sar_pdata.busnum = (uint8_t)i2c_bus_num;
		sar_pdata.i2c_address = (uint8_t)i2c_address;
		return 0;
	}

	memset(&pkt_i2c_read, 0, sizeof(pkt_i2c_read));
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (of_property_read_u32(dn, "bus_number", &i2c_bus_num)
	    || of_property_read_u32(dn, "reg", &i2c_address)
	    || of_property_read_u32(dn, "chip_id_register", &register_add)) {
		hwlog_err
		    ("CAP_PROX:read i2c bus_number (%d)or bus address(%x) or chip_id_register(%x) from dts fail\n",
		     i2c_bus_num, i2c_address, register_add);
		__dmd_log_report(DSM_SHB_ERR_IOM7_DYNLOAD, __func__,
			 "read i2c bus_number or bus address or chip_id_register from dts fail\n");
		return -1;
	}

	prop = of_find_property(dn, "chip_id_value", NULL);
	if (!prop)
		return -EINVAL;
	if (!prop->value)
		return -ENODATA;
	len = prop->length / 4;

	if (of_property_read_u32_array(dn, "chip_id_value", wia, len)) {
		hwlog_err
		    ("CAP_PROX:read chip_id_value (id0=%x) from dts fail len=%d\n",
		      wia[0], len);
		__dmd_log_report(DSM_SHB_ERR_IOM7_DYNLOAD, __func__,
			       "read chip_id_value from dts fail\n");
		return -1;
	}

	hwlog_info
	    ("CAP_PROX:read i2c bus_number (%d) slave address(0x%x) chip_id_register(0x%x) chipid value 0x%x 0x%x 0x%x 0x%x\n",
	     i2c_bus_num, i2c_address, register_add, wia[0],
	     wia[1], wia[2], wia[3]);
	pkt_i2c_read.busid = i2c_bus_num;
	pkt_i2c_read.addr = i2c_address;
	pkt_i2c_read.reg = register_add;
	pkt_i2c_read.length = 1;
	pkg_ap.tag = TAG_I2C;
	pkg_ap.cmd = CMD_I2C_READ_REQ;
	pkg_ap.wr_buf = &pkt_i2c_read.busid;
	pkg_ap.wr_len = sizeof(pkt_i2c_read) - sizeof(pkt_i2c_read.hd);
	ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
	if (ret) {
		hwlog_err
		    ("CAP_PROX:detect_i2c_device:send i2c read cmd to mcu fail,ret=%d\n",ret);
		return -1;
	}
	if (pkg_mcu.errno != 0) {
		hwlog_err("CAP_PROX:detect_i2c_device:i2c read fail\n");
		return -1;
	} else {
			hwlog_info("CAP_PROX: chipid value 0x%x 0x%x\n",pkg_mcu.data[0],pkg_mcu.data[1]);
		for (i = 0; i < len; i++) {
			if (pkg_mcu.data[0] == (char)wia[i]) {
				hwlog_info
				    ("CAP_PROX:i2c detect  suc!chip_value:0x%x\n", pkg_mcu.data[0]);
				return 0;
			}
		}
		hwlog_info("CAP_PROX:i2c detect fail,chip_value:0x%x!\n",pkg_mcu.data[0]);
		return -1;
	}
}

static int key_sensor_detect(struct device_node *dn,
			struct key_platform_data *key_data)
{
	int ret = 0;
	uint8_t values[12] = {0};

	int reg = 0;
	int chip_type = 0;
	int chip_id_register = 0;
	int chip_id_value = 0;
	int bootloader_reg = 0;

	if (!key_data) {
		hwlog_err("[%s] input null\n", __func__);
		return -1;
	}

	ret = of_property_read_u32(dn, "reg", &reg);
	if (ret < 0) {
		hwlog_err("read reg err. ret:%d\n", ret);
		return -1;
	}
	ret = of_property_read_u32(dn, "chip_type", &chip_type);
	if (ret < 0) {
		hwlog_err("read chip type err. ret:%d\n", ret);
	}
	if (chip_type) {
		ret = of_property_read_u32(dn, "reg_bootloader", &bootloader_reg);
		hwlog_info("[%s] debug key reg:%d, btld reg:%d\n", __func__, reg, bootloader_reg);
		msleep(50);
		ret = mcu_i2c_rw(0, bootloader_reg, 0x00, CMD_I2C_READ_ONLY_REQ,
					sizeof(values)/sizeof(values[0]),
					values);
		if (ret < 0) {
			hwlog_info("[%s][28] %d %d %d %d %d %d %d %d\n", __func__,
				values[0], values[0], values[0], values[0],
				values[0], values[0], values[0], values[0]);
			//return ret;
			msleep(10);
			ret = mcu_i2c_rw(0, reg, 0x46, CMD_I2C_READ_REQ,
					2, values);
			if (ret < 0) {
				hwlog_err("i2c 27 read err\n");
				return ret;
			}
		}

		hwlog_info("[%s][28] %d %d %d %d %d %d %d %d\n", __func__,
				values[0], values[1], values[2], values[3],
				values[4], values[5], values[6], values[7]);
	} else {
		ret = of_property_read_u32(dn, "chip_id_value", &chip_id_value);
		ret = of_property_read_u32(dn, "chip_id_register", &chip_id_register);
		if (!chip_id_value && !chip_id_register) {
			hwlog_err("reg and value is 0\n");
			return -1;
		}
		ret = mcu_i2c_rw(0, reg, chip_id_register, CMD_I2C_READ_REQ,
					1, values);
			if (ret < 0) {
				hwlog_err("i2c 27 read err\n");
				return ret;
			}
		hwlog_info("[%s][28] %d %d %d %d %d %d %d %d\n", __func__,
				values[0]);
		if (chip_id_value != values[0]) {
			return -1;
		}
	}

	return 0;
}

static int device_detect(struct device_node *dn, int index)
{
	int ret = 0;

	if (s_detect_manager[index].detect_result== DET_SUCC)
		return -1;

	if (GPS_4774_I2C == s_detect_manager[index].sensor_id) {
		hwlog_info("%s: gps_4774_i2c device detect always ok\n",
			   __func__);
	} else if (HANDPRESS == s_detect_manager[index].sensor_id) {
		ret = handpress_sensor_detect(dn, &handpress_data);
	} else  if (FINGERPRINT == s_detect_manager[index].sensor_id){
		hwlog_info("%s: fingerprint device detect always ok\n",
			   __func__);
	} else if(CAP_PROX == s_detect_manager[index].sensor_id){
		ret = cap_prox_sensor_detect(dn);
	} else if (KEY == s_detect_manager[index].sensor_id) {
		ret = key_sensor_detect(dn, &key_data);
	} else {
		ret = detect_i2c_device(dn, s_detect_manager[index].sensor_name_str);
	}

	if (ret) {
		s_detect_manager[index].detect_result = DET_FAIL;
		return DET_FAIL;
	}

	s_detect_manager[index].detect_result = DET_SUCC;

	return DET_SUCC;
}

static int get_sensor_detect_index(const char* name_buf)
{
	int i = 0;
	for(i = 0; i < SENSOR_MAX; i++){
		if(!strncmp(name_buf, s_detect_manager[i].sensor_name_str,s_detect_manager[i].name_str_length))
			break;
	}
	if(i < SENSOR_MAX)
		return i;
	else{
		hwlog_err("get_sensor_detect_index fail \n");
		return -1;
	}
}

static void __set_hw_dev_flag(SENSOR_DETECT_LIST s_id)
{
/* detect current device successful, set the flag as present */
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
	switch(s_id)
	{
		case ACC:
			set_hw_dev_flag(DEV_I2C_G_SENSOR);
			break;
		case MAG:
			set_hw_dev_flag(DEV_I2C_COMPASS);
			break;
		case GYRO:
			set_hw_dev_flag(DEV_I2C_GYROSCOPE);
			break;
		case ALS:
		case PS:
			set_hw_dev_flag(DEV_I2C_L_SENSOR);
			break;
		case AIRPRESS:
			set_hw_dev_flag(DEV_I2C_AIRPRESS);
			break;
		case HANDPRESS:
			set_hw_dev_flag(DEV_I2C_HANDPRESS);
			break;
		case CAP_PROX:
			break;
		case GPS_4774_I2C:
			/*set_hw_dev_flag(DEV_I2C_GPS_4774);*/
			break;
		case FINGERPRINT:
			break;
		default:
			hwlog_err("__set_hw_dev_flag:err id =%d\n", s_id);
			break;
	}

#endif
}

static void extend_config_after_sensor_detect(struct device_node *dn, int index)
{
	int ret = 0;
	SENSOR_DETECT_LIST s_id;
	s_id = s_detect_manager[index].sensor_id;

	switch(s_id)
	{
		case ACC:
			read_acc_data_from_dts(dn);
			break;
		case MAG:
			read_mag_data_from_dts(dn);
			ret = fill_extend_data_in_dts(dn, str_soft_para,
					mag_data.pdc_data, PDC_SIZE,
					EXTEND_DATA_TYPE_IN_DTS_BYTE);
			if (ret) {
				hwlog_err
				    ("%s:fill_extend_data_in_dts failed!\n",
				     str_soft_para);
			}
			break;
		case GYRO:
			read_gyro_data_from_dts(dn);
			break;
		case ALS:
			read_als_data_from_dts(dn);
			break;
		case PS:
			read_ps_data_from_dts(dn);
			break;
		case AIRPRESS:
			read_airpress_data_from_dts(dn);
			break;
		case HANDPRESS:
			read_handpress_data_from_dts(dn);
			break;
		case CAP_PROX:
			read_capprox_data_from_dts(dn);
			break;
		case GPS_4774_I2C:
			read_gps_4774_i2c_data_from_dts(dn);
			break;
		case FINGERPRINT:
			read_fingerprint_from_dts(dn);
			break;
		case KEY:
			read_key_i2c_data_from_dts(dn);
			break;
		default:
			hwlog_err("%s:err id =%d\n",__func__, s_id);
			break;
	}
	return;
}
static void check_detect_result(DETECT_MODE mode)
{
	int i = 0;
	uint8_t detect_fail_num = 0;
	uint8_t  result = 0;
	int total_len = 0;
	char detect_result[MAX_STR_SIZE] = { 0 };
	const char *sf = " detect fail!";

	for(i = 0; i < SENSOR_MAX; i++)
	{
		result = s_detect_manager[i].detect_result;
		if(result == DET_FAIL){
			detect_fail_num ++;
			total_len += s_detect_manager[i].name_str_length;
			total_len += 2;
			if(total_len < MAX_STR_SIZE){
				strcat(detect_result,s_detect_manager[i].sensor_name_str);
				strcat(detect_result,"  ");
			}
			hwlog_info("%s :  %s detect fail \n",__func__,s_detect_manager[i].sensor_name_str);
		}else if(result == DET_SUCC){
			hwlog_info("%s :  %s detect success \n",__func__,s_detect_manager[i].sensor_name_str);
		}
	}

	if(detect_fail_num > 0){
		s_redetect_state.need_redetect_sensor = 1;
		total_len += strlen(sf);
		if(total_len < MAX_STR_SIZE)
			strcat(detect_result,sf);

		if(mode == BOOT_DETECT)
			__dmd_log_report(DSM_SHB_ERR_IOM7_DYNLOAD, __func__,detect_result);

	}else{
		s_redetect_state.need_redetect_sensor = 0;
	}

	if(detect_fail_num < s_redetect_state.detect_fail_num){
			s_redetect_state.need_recovery = 1;
			hwlog_info("%s : some sensors detect success after redetect \n",__func__);
	}
	s_redetect_state.detect_fail_num = detect_fail_num;

}

static void show_last_detect_fail_sensor(void)
{
	int i = 0;
	uint8_t  result = 0;
	for(i = 0; i < SENSOR_MAX; i++)
	{
		result = s_detect_manager[i].detect_result;
		if(result == DET_FAIL){
			hwlog_err("last detect fail sensor:  %s \n",s_detect_manager[i].sensor_name_str);
		}
	}
}

int init_sensors_cfg_data_from_dts(DETECT_MODE mode)
{
	int ret = 0;
	int index = 0;
	char *sensor_ty = NULL;
	char *sensor_st = NULL;
	struct device_node *dn = NULL;
	const char *st = "disabled";

	for_each_node_with_property(dn, "sensor_type") {
		//sensor type
		ret = of_property_read_string(dn, "sensor_type",
					    (const char **)&sensor_ty);
		if (ret) {
			hwlog_err("get sensor type fail ret=%d\n", ret);
			continue;
		}
		//sensor status:ok or disabled
		ret = of_property_read_string(dn, "status",
					    (const char **)&sensor_st);
		if (ret) {
			hwlog_err("get sensor status fail ret=%d\n", ret);
			continue;
		}

		ret = strcmp(st,sensor_st);
		if( !ret){
			hwlog_info("%s : sensor %s status is %s \n",__func__,sensor_ty,sensor_st);
			continue;
		}

		index = get_sensor_detect_index(sensor_ty);
		if(index < 0){
			hwlog_err("get sensor index fail ret=%d\n", ret);
			continue;
		}

		ret = device_detect(dn,index);
		if(ret != DET_SUCC)
			continue;

		__set_hw_dev_flag(s_detect_manager[index].sensor_id);

		extend_config_after_sensor_detect(dn,index);
	}

	check_detect_result(mode);

	if(mode == BOOT_DETECT){
		if (get_adapt_id_and_send())
			return -EINVAL;
	}

	return 0;
}

static int get_sensor_cmd(SENSOR_DETECT_LIST s_id)
{
	switch(s_id)
	{
		case ACC:
			return CMD_ACCEL_PARAMET_REQ;

		case MAG:
			return CMD_MAG_PARAMET_REQ;

		case GYRO:
			return CMD_GYRO_PARAMET_REQ;

		case ALS:
			return CMD_ALS_PARAMET_REQ;

		case PS:
			return CMD_PS_PARAMET_REQ;

		case AIRPRESS:
			return CMD_AIRPRESS_PARAMET_REQ;

		case HANDPRESS:
			return CMD_HANDPRESS_PARAMET_REQ;

		case CAP_PROX:
			return CMD_CAP_PROX_PARAMET_REQ;
		case FINGERPRINT:
			return CMD_FINGERPRINT_SPI_PARAMET_REQ;

		case GPS_4774_I2C:
			return CMD_GPS_4774_I2C_PARAMET_REQ;

		case KEY:
			return CMD_KEY_PARAMET_REQ;
		default:
			hwlog_err("get_sensor_cmd:err id =%d\n", s_id);
			return -1;
	}
}

static void send_parameter_to_mcu(SENSOR_DETECT_LIST s_id, int cmd)
{
    int ret = 0;
    write_info_t pkg_ap;
    read_info_t pkg_mcu;
    char buf[50] = {0};

    memset(&pkg_ap, 0, sizeof(pkg_ap));
    memset(&pkg_mcu, 0, sizeof(pkg_mcu));

    pkg_ap.tag = s_detect_manager[s_id].tag;
    pkg_ap.cmd = cmd;
    pkg_ap.wr_buf = s_detect_manager[s_id].spara;
    pkg_ap.wr_len = s_detect_manager[s_id].cfg_data_length;

    hwlog_info("%s g_iom3_state = %d,tag =%d ,cmd =%d\n",__func__,g_iom3_state,s_detect_manager[s_id].tag,cmd);

    if (g_iom3_state == IOM3_ST_RECOVERY || iom3_power_state == ST_SLEEP)
    {
        ret = write_customize_cmd_noresp(s_detect_manager[s_id].tag,
                                         cmd,
                                         pkg_ap.wr_buf,
                                         pkg_ap.wr_len);
    }else{
    	ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
    }

    if (ret)
    {
        hwlog_err("send tag %d cfg data to mcu fail,ret=%d\n", s_detect_manager[s_id].tag, ret);
    }else{
        if (pkg_mcu.errno != 0)
        {
            snprintf(buf, 50, "set %s cfg fail\n", s_detect_manager[s_id].sensor_name_str);
            hwlog_err("%s\n",buf);
            __dmd_log_report(DSM_SHB_ERR_IOM7_CFG_DATA,__func__, buf);
        }else{
            snprintf(buf, 50, "set %s cfg to mcu success\n", s_detect_manager[s_id].sensor_name_str);
            hwlog_info("%s\n",buf);
            if (g_iom3_state != IOM3_ST_RECOVERY)
            {
                __set_hw_dev_flag(s_id);
            }
        }
    }
}

static int mag_calibrate_data_from_mcu(const pkt_header_t *head)
{
	return write_magsensor_calibrate_data_to_nv(((const
			pkt_mag_calibrate_data_req_t *)head)->calibrate_data);
}

static int gyro_calibrate_data_from_mcu(const pkt_header_t *head)
{
	return write_gyro_sensor_offset_to_nv(((const
			pkt_gyro_calibrate_data_req_t *)head)->calibrate_data,
					   MAX_GYRO_CALIBRATE_DATA_LENGTH);
}

static void register_priv_notifier(SENSOR_DETECT_LIST s_id)
{
	switch (s_id){
		case GYRO:
			register_mcu_event_notifier(TAG_GYRO, CMD_GYRO_SELFCALI_REQ, gyro_calibrate_data_from_mcu);
			break;
		case MAG:
			register_mcu_event_notifier(TAG_MAG, CMD_MAG_SEND_CALIBRATE_TO_AP_REQ, mag_calibrate_data_from_mcu);
			break;
		default:
			break;
	}
	return;
}
/*******************************************************************************************
Function:	sensor_set_cfg_data
Description: �����ò�������mcu ��
Data Accessed:  ��
Data Updated:   ��
Input:        ��
Output:         ��
Return:         �ɹ�����ʧ����Ϣ: 0->�ɹ�, -1->ʧ��
*******************************************************************************************/
int sensor_set_cfg_data(void)
{
    int ret = 0;
    SENSOR_DETECT_LIST s_id;
    int cmd = 0;

    ret = sensor_set_current_info();

    if (ret)
    {
        hwlog_err("sensor_set_current_info fail, ret = %d\n", ret);
    }

    for (s_id = ACC; s_id < SENSOR_MAX; s_id ++)
    {
        if (strlen(sensor_chip_info[s_id]) != 0)
        {
            cmd = get_sensor_cmd(s_id);

            if (cmd < 0)
            {
                hwlog_err("get_sensor_cmd fail\n");
                continue;
            }

            send_parameter_to_mcu(s_id, cmd);

            if (g_iom3_state != IOM3_ST_RECOVERY)
            { register_priv_notifier(s_id); }
        }

    }

    return ret;
}

static int sensor_fw_dload_flag = 0;
int sensor_set_fw_load(void)
{
	int val = 1;
	int ret = 0;


	if (strlen(sensor_chip_info[KEY]) == 0) {
		hwlog_err("no key\n");
		return 0;
	}

	if (sensor_fw_dload_flag) {
		hwlog_info("fw dloaded, just return.\n");
		return 0;
	}

	ret = write_customize_cmd_noresp(TAG_KEY, CMD_KEY_FW_DLOAD_REQ, &val, sizeof(val));
	sensor_fw_dload_flag = 1;
	hwlog_info("write fw dload.\n");

	return 0;
}

static void redetect_sensor_work_handler(void)
{
	wake_lock(&sensor_rd);
	init_sensors_cfg_data_from_dts(REDETECT_LATER);

	if(s_redetect_state.need_recovery == 1){
		s_redetect_state.need_recovery = 0;
		hwlog_info("%s: some sensor detect success after %d redetect, begin recovery \n",__func__,s_redetect_state.redetect_num);
		iom3_need_recovery(SENSORHUB_USER_MODID, SH_FAULT_REDETECT);
	}else{
		hwlog_info("%s: no sensor redetect success\n",__func__);
	}
	wake_unlock(&sensor_rd);
}

void sensor_redetect_enter(void)
{
	if(g_iom3_state == IOM3_ST_NORMAL)
	{
		if(s_redetect_state.need_redetect_sensor == 1){
			if(s_redetect_state.redetect_num < MAX_REDETECT_NUM){
				queue_work(system_power_efficient_wq, &redetect_work);
				s_redetect_state.redetect_num ++;
			}else{
				hwlog_info("%s: some sensors detect fail  ,but the max redetect num is over flow\n",__func__);
				show_last_detect_fail_sensor();
			}
		}
	}
}

void sensor_redetect_init(void)
{
	memset(&s_redetect_state,0,sizeof(s_redetect_state));
	wake_lock_init(&sensor_rd, WAKE_LOCK_SUSPEND, "sensorhub_redetect");
	INIT_WORK(&redetect_work, redetect_sensor_work_handler);
}
