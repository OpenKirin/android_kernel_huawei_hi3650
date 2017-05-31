/*
 * Copyright (C) 2010 - 2016 Novatek, Inc.
 *
 * $Revision: 4017 $
 * $Date: 2016-04-01 09:41:08 +0800 (星期五, 01 四月 2016) $
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
 * more details.
 *
 */
#ifndef 	_LINUX_NVT_TOUCH_H
#define		_LINUX_NVT_TOUCH_H

#include <linux/i2c.h>
#include <linux/input.h>

#ifdef CONFIG_HAS_EARLYSUSPEND
#include <linux/earlysuspend.h>
#endif

//---GPIO number---
#define NVTTOUCH_RST_PIN 980
#define NVTTOUCH_INT_PIN 943
#define NVTTOUCH_DISP_RST_PIN 956


//---INT trigger mode---
//#define IRQ_TYPE_EDGE_RISING 1
//#define IRQ_TYPE_EDGE_FALLING 2
//#define IRQ_TYPE_LEVEL_HIGH 4
//#define IRQ_TYPE_LEVEL_LOW 8
#define INT_TRIGGER_TYPE IRQ_TYPE_EDGE_FALLING


//---I2C driver info.---
#define NVT_I2C_NAME "NVT-ts"
#define I2C_BLDR_Address 0x01
#define I2C_FW_Address 0x01
#define I2C_HW_Address 0x62


//---Input device info.---
#define NVT_TS_NAME "NVTCapacitiveTouchScreen"


//---Touch info.---
#define TOUCH_MAX_WIDTH 1080
#define TOUCH_MAX_HEIGHT 1920
#define TOUCH_MAX_FINGER_NUM 10
#define TOUCH_KEY_NUM 0
#if TOUCH_KEY_NUM > 0
extern const uint16_t touch_key_array[TOUCH_KEY_NUM];
#endif
#define TOUCH_FORCE_NUM 1000

//---Customerized func.---
#define NVT_TOUCH_PROC 1		// for novatek cmdline tools and apk
#define NVT_TOUCH_EXT_PROC 1	// for novatek debug
#define NVT_TOUCH_MP 1

#define BOOT_UPDATE_FIRMWARE 0
#define BOOT_UPDATE_FIRMWARE_NAME "novatek_ts_fw.bin"

#define PROJECT_ID_LEN 9

struct nvt_ts_data {
	struct ts_device_data *chip_data;
	struct platform_device *ts_dev;
	struct regulator *tp_vci;
	struct regulator *tp_vddio;
	
#ifndef CONFIG_OF
	struct iomux_block *tp_gpio_block;
	struct block_config *tp_gpio_block_config;
#else
	struct pinctrl *pctrl;
	struct pinctrl_state *pins_default;
	struct pinctrl_state *pins_idle;
#endif
	struct mutex i2c_mutex;
	struct mutex mp_mutex;
	struct i2c_client *client;
	struct input_dev *input_dev;
	struct work_struct nvt_work;
	struct delayed_work nvt_fwu_work;
	uint16_t addr;
	int8_t phys[32];
#ifdef CONFIG_HAS_EARLYSUSPEND
	struct early_suspend early_suspend;
#endif
	uint16_t abs_x_max;
	uint16_t abs_y_max;
	uint8_t x_num;
	uint8_t y_num;
	uint8_t max_touch_num;
	uint8_t max_button_num;
	uint32_t int_trigger_type;
#if DRAGONBOARD_REGULATOR
	struct regulator *avdd;
	struct regulator *vdd;
	bool power_on;
#endif
	int32_t irq_gpio;
	uint32_t irq_flags;
	int32_t reset_gpio;
	uint32_t reset_flags;
	int32_t disp_rst_gpio;
	uint32_t disp_rst_flags;
};

#if NVT_TOUCH_PROC
struct nvt_flash_data{
	rwlock_t lock;
	struct i2c_client *client;
};
#endif

typedef enum {
	RESET_STATE_INIT = 0xA0,// IC reset
	RESET_STATE_REK,		// ReK baseline
	RESET_STATE_REK_FINISH,	// baseline is ready
	RESET_STATE_NORMAL_RUN	// normal run
} RST_COMPLETE_STATE;

#endif /* _LINUX_NVT_TOUCH_H */
