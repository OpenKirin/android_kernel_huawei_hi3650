/*
 * Copyright (C) huawei company
 *
 * This	program	is free	software; you can redistribute it and/or modify
 * it under	the	terms of the GNU General Public	License	version	2 as
 * published by	the	Free Software Foundation.
 
  * Filename:  sensor_detect.h
 *
 * Discription: some functions of sensorhub power
 *
 * Owner:DIVS_SENSORHUB
 */
#ifndef __SENSOR_DETECT_H
#define __SENSOR_DETECT_H

typedef enum {
	ACC,
	MAG,
	GYRO,
	ALS,
	PS,
	AIRPRESS,
	HANDPRESS,
	CAP_PROX,
	GPS_4774_I2C,
	FINGERPRINT,
	KEY,
	SENSOR_MAX
}SENSOR_DETECT_LIST;

typedef enum{
	BOOT_DETECT,
	REDETECT_LATER
}DETECT_MODE;

#define MAX_SENSOR_NAME_LENGTH 20
struct sensor_detect_manager{
	char sensor_name_str[MAX_SENSOR_NAME_LENGTH];
	uint8_t name_str_length;
	SENSOR_DETECT_LIST sensor_id;
	uint8_t detect_result;
	int tag;
	const void *spara;
    	int cfg_data_length;
};

#define MAX_REDETECT_NUM 100
struct sensor_redetect_state{
	uint8_t need_redetect_sensor;
	uint8_t need_recovery;
	uint8_t detect_fail_num;
	uint8_t redetect_num;
};

int init_sensors_cfg_data_from_dts(DETECT_MODE mode);
SENSOR_DETECT_LIST get_id_by_sensor_tag(int tag);
int sensor_set_cfg_data(void);
void sensor_redetect_enter(void);
void sensor_redetect_init(void);
int sensor_set_fw_load(void);
#endif