/*
 *
 * FocalTech TouchScreen driver.
 *
 * Copyright (c) 2010-2016, FocalTech Systems, Ltd., all rights reserved.
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

/*******************************************************************************
*
* File Name: focaltech_core.c
*
*  Author: Xu YF & ZR, Software Department, FocalTech
*
* Created: 2016-01-20
*
*  Abstract:
*
* Reference:
*
*******************************************************************************/

/*******************************************************************************
* 1.Included header files
*******************************************************************************/

#include <huawei_platform/log/log_jank.h>
#include <../../huawei_touchscreen_chips.h>

#include "focaltech_flash.h"
#include "focaltech_i2c.h"
#include "focaltech_core.h"
#include "focaltech_dts.h"
#include "focaltech_test.h"
#include "focaltech_apk_node.h"
#include "focaltech_sysfs.h"
#include "../../huawei_touchscreen_algo.h"

#if defined(CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif

/* Debug Enable, 0:disable, 1:enable */
#define FTS_MAX_POINT_ID				0x0F
#define FTS_POINT_DATA_SIZE				6

/* the start addr of get touch data */
#define TOUCH_DATA_START_ADDR	0x00

#define ADDR_X_H_POS			(3 - TOUCH_DATA_START_ADDR)
#define ADDR_X_L_POS			(4 - TOUCH_DATA_START_ADDR)
#define ADDR_Y_H_POS			(5 - TOUCH_DATA_START_ADDR)
#define ADDR_Y_L_POS			(6 - TOUCH_DATA_START_ADDR)
#define ADDR_EVENT_POS			(3 - TOUCH_DATA_START_ADDR)
#define ADDR_FINGER_ID_POS		(5 - TOUCH_DATA_START_ADDR)
#define ADDR_POINT_NUM			(2 - TOUCH_DATA_START_ADDR)
#define ADDR_XY_POS			(7 - TOUCH_DATA_START_ADDR)
#define ADDR_MISC			(8 - TOUCH_DATA_START_ADDR)
#define FTS_TOUCH_DATA_LEN		\
	(3 - TOUCH_DATA_START_ADDR + FTS_POINT_DATA_SIZE * FTS_MAX_TOUCH_POINTS)

#define GLOVE_SWITCH_ON 1
#define GLOVE_SWITCH_OFF 0

struct i2c_client *fts_i2c_client = NULL;
struct fts_ts_platform_data *fts_platform_data = NULL;
struct input_dev *fts_input_dev = NULL;

/* hisi varibles */
static DEFINE_MUTEX(ts_power_gpio_sem);
static int ts_power_gpio_ref = 1;

/* hisi functions */
static int fts_chip_detect(struct device_node *device,
				 struct ts_device_data *chip_data,
				 struct platform_device *ts_dev);
static int fts_wrong_touch(void);
static int fts_init_chip(void);
static int fts_irq_top_half(struct ts_cmd_node *cmd);
static int fts_irq_bottom_half(struct ts_cmd_node *in_cmd,
					 struct ts_cmd_node *out_cmd);
static int fts_fw_update_boot(char *file_name);
static int fts_fw_update_sd(void);
static int fts_chip_get_info(struct ts_chip_info_param *info);
static int fts_set_info_flag(struct ts_data *info);
static int fts_before_suspend(void);
static int fts_suspend(void);
static int fts_resume(void);
static int fts_after_resume(void *feature_info);
static int fts_wakeup_gesture_enable_switch(
	struct ts_wakeup_gesture_enable_info *info);
static void fts_shutdown(void);
static int fts_input_config(struct input_dev *input_dev);
static int fts_reset_device(void);
static int fts_get_debug_data(struct ts_diff_data_info *info,
	struct ts_cmd_node *out_cmd);
static int fts_palm_switch(struct ts_palm_info *info);
static int fts_glove_switch(struct ts_glove_info *info);
static int fts_get_glove_switch(u8 *glove_switch);
static int fts_set_glove_switch(u8 glove_switch);
//static int fts_charger_switch(struct ts_charger_info *info);
static int fts_holster_switch(struct ts_holster_info *info);
static int fts_roi_switch(struct ts_roi_info *info);
static unsigned char *fts_roi_rawdata(void);
static int fts_chip_get_capacitance_test_type(struct ts_test_type_info *info);
static int fts_calibrate(void);
static int fts_calibrate_wakeup_gesture(void);
#if defined(CONFIG_HUAWEI_DSM)
static int fts_rmi4_dsm_debug(void);
#endif
static int fts_regs_operate(struct ts_regs_info *info);

struct ts_device_ops ts_fts_ops = {
	.chip_detect = fts_chip_detect,
	.chip_init = fts_init_chip,
	.chip_parse_config = fts_parse_dts,
	.chip_input_config = fts_input_config,
	.chip_irq_top_half = fts_irq_top_half,
	.chip_irq_bottom_half = fts_irq_bottom_half,
	.chip_fw_update_boot = fts_fw_update_boot,
	.chip_fw_update_sd = fts_fw_update_sd,
	.chip_get_info = fts_chip_get_info,
	.chip_get_capacitance_test_type = fts_chip_get_capacitance_test_type,
	.chip_set_info_flag = fts_set_info_flag,
	.chip_before_suspend = fts_before_suspend,
	.chip_suspend = fts_suspend,
	.chip_resume = fts_resume,
	.chip_after_resume = fts_after_resume,
	.chip_wakeup_gesture_enable_switch = fts_wakeup_gesture_enable_switch,
	.chip_get_rawdata = fts_get_raw_data,
	.chip_get_debug_data = fts_get_debug_data,
	.chip_glove_switch = fts_glove_switch,
	.chip_shutdown = fts_shutdown,
	//.chip_charger_switch = fts_charger_switch,
	.chip_holster_switch = fts_holster_switch,
	.chip_roi_switch = fts_roi_switch,
	.chip_roi_rawdata = fts_roi_rawdata,
	.chip_palm_switch = fts_palm_switch,
	.chip_regs_operate = fts_regs_operate,
	.chip_calibrate = fts_calibrate,
	.chip_calibrate_wakeup_gesture = fts_calibrate_wakeup_gesture,
#if defined(CONFIG_HUAWEI_DSM)
	.chip_dsm_debug = fts_rmi4_dsm_debug,
#endif
	.chip_reset = fts_reset_device,
#ifdef HUAWEI_TOUCHSCREEN_TEST
	.chip_test = test_dbg_cmd_test,
#endif
	.chip_wrong_touch = fts_wrong_touch,
};

int fts_hardware_reset(struct fts_ts_platform_data *fts_pdata, int model)
{
	int ret = 0;
	int reset_gpio = 0;
	int reset_enable_delay = 0;

	reset_gpio = fts_pdata->fts_chip_data->reset_gpio;

	ret = gpio_direction_output(reset_gpio, 1);
	if (ret) {
		TS_LOG_ERR("%s:gpio direction output to 1 fail, ret=%d\n",
			__func__, ret);
		return ret;
	}
	msleep(1);

	ret = gpio_direction_output(reset_gpio, 0);
	if (ret) {
		TS_LOG_ERR("%s:gpio direction output to 0 fail, ret=%d\n",
			__func__, ret);
		return ret;
	}
	msleep(1);

	ret = gpio_direction_output(reset_gpio, 1);
	if (ret) {
		TS_LOG_ERR("%s:gpio direction output to 1 fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	switch (model) {
	case FTS_MODEL_BOOTLOADER:
		reset_enable_delay = 6;
		break;
	case FTS_MODEL_FIRST_START:
		reset_enable_delay = 240;
		break;
	case FTS_MODEL_NORMAL:
		reset_enable_delay = 120;
		break;
	default:
		reset_enable_delay = 240;
	}

	msleep(reset_enable_delay);

	return 0;
}

int fts_hardware_reset_to_normal_model(struct fts_ts_platform_data *fts_pdata)
{
	return fts_hardware_reset(fts_pdata, FTS_MODEL_NORMAL);
}

/*
 * description: after finishe control reset gpio, write 0x55 to 0xfc in 6~25ms,
 *              the ic will enter bootloader(rom boot) model
 *
 *param - fts_pdata : truct fts_ts_platform_data
 *
 * return 0 if success, other wize return error code
 */
int fts_hardware_reset_to_rom_update_model(
	struct fts_ts_platform_data *fts_pdata)
{
	int i = 0;
	int ret = 0;
	unsigned delay_time = 0;
	unsigned int chip_id = 0;

	delay_time = 6;
	for (i = 0; i < 10; i++) {

		if (i != 0) {
			delay_time += 2;
		}
	
		ret = fts_hardware_reset(fts_pdata, FTS_MODEL_BOOTLOADER);
		if (ret < 0) {
			TS_LOG_ERR("%s:%s, ret=%d\n", __func__,
				"hardware reset to bootloader fail", ret);
			
			continue;
		}

		ret = fts_write_command(FTS_UPGRADE_55);
		if (ret < 0) {
			TS_LOG_ERR("%s:write command 0x55 fail, ret=%d\n",
				__func__, ret);
			continue;
		}
	
		ret = fts_read_chip_id(&chip_id);
		if (ret || chip_id == 0) {
			TS_LOG_INFO("%s:chip id read fail, retry=%d\n",
				__func__, i);

			delay_time += 2;
			continue;
		} else {
			return 0;
		}
	}

	return -EINVAL;
}


int strtolow(char *src_str, size_t size)
{
	char *str = NULL;
	
	if (NULL == src_str) {
		return -EINVAL;
	}

	str = src_str;
	while(*str != '\0' && size > 0) {
		if (*str >= 'A' && *str <= 'Z') {
			*str += ('a' - 'A');
		}

		str++;
		size--;
	}

	return 0;
}

/*
 * Name: fts_read_touch_data
 * Brief: report the point information
 * Input: event info
 * Output: get touch data in pinfo
 * Return: success is zero
 */
static int fts_read_touch_data(struct ts_event *event_data)
{
	int i = 0;
	int ret = -1;
	unsigned int offset = 0;

	unsigned char buf[FTS_TOUCH_DATA_LEN] = { 0 };

	buf[0] = TOUCH_DATA_START_ADDR;
	ret = fts_i2c_read(buf, 1, buf, FTS_TOUCH_DATA_LEN);
	if (ret < 0) {
		TS_LOG_ERR("%s:read touchdata failed, ret=%d.\n",
			__func__, ret);
		return ret;
	}

	memset(event_data, 0, sizeof(struct ts_event));
	event_data->touch_point = 0;
	event_data->touch_point_num = buf[ADDR_POINT_NUM] & 0x0F;

	for (i = 0; i < FTS_MAX_TOUCH_POINTS; i++) {
		offset = FTS_POINT_DATA_SIZE * i;

		event_data->finger_id[i]
			= (buf[ADDR_FINGER_ID_POS + offset]) >> 4;
		
		if (event_data->finger_id[i] >= FTS_MAX_POINT_ID) {
			break;
		} else {
			event_data->touch_point++;
		}

		event_data->position_x[i] =
			(s16)(buf[ADDR_X_H_POS + offset] & 0x0F) << 8
			| (s16)(buf[ADDR_X_L_POS + offset]);

		event_data->position_y[i] =
			(s16)(buf[ADDR_Y_H_POS + offset] & 0x0F) << 8
			| (s16)(buf[ADDR_Y_L_POS + offset]);

		event_data->touch_event[i] = buf[ADDR_EVENT_POS + offset] >> 6;
		event_data->pressure[i] = (buf[ADDR_XY_POS + offset]);
		event_data->area[i] = (buf[ADDR_MISC + offset]) >> 4;

		/* check event data */
		if (event_data->touch_point_num == 0) {
			if (event_data->touch_event[i] == 0
				|| event_data->touch_event[i] == 2) {
				TS_LOG_ERR("%s:abnormal touch data from fw.\n",
					__func__);
				return -EINVAL;
			}
		}

		TS_LOG_DEBUG("%s:touch data:\n"
			"(id=%d,x=(0x%02x),y=(0x%02x)),point_num=%d,event=%d\n",
			__func__,
			event_data->finger_id[i],
			event_data->position_x[i],
			event_data->position_y[i],
			event_data->touch_point,
			event_data->touch_event[i]);
	}

	return 0;
}

/*
 * TP VCC
 * TP VCC/VDD  power control by GPIO in V8Rx,
 * if controled by ldo in other products, open "return -EINVAL"
 * fts_platform_data->tp_vci is 3.1V ,fts_platform_data->tp_vddio is 1.8V
 */
static int fts_regulator_get(struct fts_ts_platform_data *fts_pdata)
{
	struct device *dev = NULL;

	dev = &fts_pdata->fts_platform_dev->dev;

	if (g_ts_data.fpga_flag == 1)
		return 0;

	if (1 == fts_pdata->fts_chip_data->vci_regulator_type) {
		fts_pdata->tp_vci = regulator_get(dev, FTS_VDD);
		if (IS_ERR(fts_pdata->tp_vci)) {
			TS_LOG_ERR("regulator tp vci not used\n");
			return -EINVAL;
		}
	}

	if (1 == fts_pdata->fts_chip_data->vddio_regulator_type) {
		fts_pdata->tp_vddio =
			regulator_get(dev, FTS_VBUS);
		if (IS_ERR(fts_pdata->tp_vddio)) {
			TS_LOG_ERR("regulator tp vddio not used\n");
			regulator_put(fts_pdata->tp_vci);
			return -EINVAL;
		}
	}

	return 0;
}

static void fts_regulator_put(struct fts_ts_platform_data *fts_pdata)
{
	if (g_ts_data.fpga_flag == 1)
		return;

	if (1 == fts_pdata->fts_chip_data->vci_regulator_type) {
		if (!IS_ERR(fts_pdata->tp_vci))
			regulator_put(fts_pdata->tp_vci);
	}

	if (1 == fts_pdata->fts_chip_data->vddio_regulator_type) {
		if (!IS_ERR(fts_pdata->tp_vddio))
			regulator_put(fts_pdata->tp_vddio);
	}
}

/* dts */
static int fts_pinctrl_get_init(struct fts_ts_platform_data *fts_pdata)
{
	int ret = 0;
	struct device *dev = NULL;

	dev = &fts_pdata->fts_platform_dev->dev;

	if (g_ts_data.fpga_flag == 1)
		return 0;

	fts_pdata->pctrl = devm_pinctrl_get(dev);
	if (IS_ERR(fts_pdata->pctrl)) {
		TS_LOG_ERR("failed to devm pinctrl get\n");
		ret = -EINVAL;
		return ret;
	}

	fts_pdata->pins_default =
		pinctrl_lookup_state(fts_pdata->pctrl, "default");
	if (IS_ERR(fts_pdata->pins_default)) {
		TS_LOG_ERR("failed to pinctrl lookup state default\n");
		ret = -EINVAL;
		goto err_pinctrl_put;
	}

	fts_pdata->pins_idle = pinctrl_lookup_state(fts_pdata->pctrl, "idle");
	if (IS_ERR(fts_pdata->pins_idle)) {
		TS_LOG_ERR("failed to pinctrl lookup state idle\n");
		ret = -EINVAL;
		goto err_pinctrl_put;
	}
	return 0;

err_pinctrl_put:
	devm_pinctrl_put(fts_pdata->pctrl);
	return ret;
}

void fts_power_gpio_enable(void)
{
	if (fts_platform_data == NULL) {
		TS_LOG_ERR("fts_platform_data == NULL\n");
		return;
	}

	if (fts_platform_data->fts_chip_data == NULL) {
		TS_LOG_ERR("fts_chip_data == NULL\n");
		return;
	}

	mutex_lock(&ts_power_gpio_sem);
	if (ts_power_gpio_ref == 0) {
		gpio_direction_output(fts_platform_data->fts_chip_data->
					  vddio_gpio_ctrl, 1);
	}
	ts_power_gpio_ref++;
	TS_LOG_INFO("ts_power_gpio_ref++ = %d\n", ts_power_gpio_ref);
	mutex_unlock(&ts_power_gpio_sem);
}
EXPORT_SYMBOL(fts_power_gpio_enable);

void fts_power_gpio_disable(void)
{
	if (fts_platform_data == NULL) {
		TS_LOG_ERR("fts_platform_data == NULL\n");
		return;
	}

	if (fts_platform_data->fts_chip_data == NULL) {
		TS_LOG_ERR("fts_chip_data == NULL\n");
		return;
	}

	mutex_lock(&ts_power_gpio_sem);
	if (ts_power_gpio_ref == 1) {
		gpio_direction_output(fts_platform_data->fts_chip_data->
					  vddio_gpio_ctrl, 0);
	}
	if (ts_power_gpio_ref > 0)
		ts_power_gpio_ref--;

	TS_LOG_INFO("ts_power_gpio_ref-- = %d\n", ts_power_gpio_ref);
	mutex_unlock(&ts_power_gpio_sem);
}
EXPORT_SYMBOL(fts_power_gpio_disable);

static int fts_gpio_request(struct fts_ts_platform_data *fts_pdata)
{
	int ret = NO_ERR;
	int irq_gpio = 0;
	int reset_gpio = 0;
	int vci_gpio_ctrl = 0;
	int vddio_gpio_ctrl = 0;

	TS_LOG_INFO("fts_gpio_request\n");

	irq_gpio = fts_pdata->fts_chip_data->irq_gpio;
	reset_gpio = fts_pdata->fts_chip_data->reset_gpio;
	TS_LOG_INFO("reset gpio:%d, irq gpio:%d,\n", reset_gpio, irq_gpio);

	ret = gpio_request(reset_gpio, "ts_reset_gpio");
	if (ret < 0) {
		TS_LOG_ERR("Fail request gpio:%d, ret=%d\n", reset_gpio, ret);
		goto ts_reset_out;
	}

	ret = gpio_request(irq_gpio, "ts_irq_gpio");
	if (ret) {
		TS_LOG_ERR("unable to request gpio:%d, ret=%d\n", irq_gpio, ret);
		goto ts_irq_out;
	}

	vci_gpio_ctrl = fts_pdata->fts_chip_data->vci_gpio_ctrl;
	vddio_gpio_ctrl = fts_pdata->fts_chip_data->vddio_gpio_ctrl;
	if ((1 == fts_pdata->fts_chip_data->vci_gpio_type)
		&& (1 == fts_pdata->fts_chip_data->vddio_gpio_type)) {

		if (vci_gpio_ctrl == vddio_gpio_ctrl) {
			ret = gpio_request(vci_gpio_ctrl, "ts_vci_gpio");
			if (ret) {
				TS_LOG_ERR("request ts vci gpio fail, gpio=%d, ret=%d\n",
					 vci_gpio_ctrl, ret);
				goto ts_vci_out;
			}
		} else {
			ret = gpio_request(vci_gpio_ctrl, "ts_vci_gpio");
			if (ret) {
				TS_LOG_ERR("request ts vci gpio fail, gpio=%d, ret=%d\n",
					 vci_gpio_ctrl, ret);
				goto ts_vci_out;
			}

			ret = gpio_request(vddio_gpio_ctrl, "ts_vddio_gpio");
			if (ret) {
				TS_LOG_ERR("request vddio_gpio_ctrl fail, gpio=%d, ret=%d\n",
					 vddio_gpio_ctrl, ret);
				goto ts_vddio_out;
			}
		}
	} else {
		if (1 == fts_pdata->fts_chip_data->vci_gpio_type) {
			ret = gpio_request(vci_gpio_ctrl, "ts_vci_gpio");
			if (ret) {
				TS_LOG_ERR("request ts vci gpio fail, gpio=%d, ret=%d\n",
					 vci_gpio_ctrl, ret);
				goto ts_vci_out;
			}
		}
		if (1 == fts_pdata->fts_chip_data->vddio_gpio_type) {
			ret = gpio_request(vddio_gpio_ctrl, "ts_vddio_gpio");
			if (ret) {
				TS_LOG_ERR("request vddio_gpio_ctrl fail, gpio=%d, ret=%d\n",
					 vddio_gpio_ctrl, ret);
				goto ts_vddio_out;
			}
		}
	}

	goto ts_reset_out;

ts_vddio_out:
	gpio_free(vci_gpio_ctrl);
ts_vci_out:
	gpio_free(irq_gpio);
ts_irq_out:
	gpio_free(reset_gpio);
ts_reset_out:
	return ret;
}

static void fts_gpio_free(struct fts_ts_platform_data *fts_pdata)
{
	TS_LOG_INFO("fts_gpio_free\n");

	gpio_free(fts_pdata->fts_chip_data->irq_gpio);
	gpio_free(fts_pdata->fts_chip_data->reset_gpio);
	/*0 is power supplied by gpio, 1 is power supplied by ldo */
	if (1 == fts_pdata->fts_chip_data->vci_gpio_type) {
		if (fts_pdata->fts_chip_data->vci_gpio_ctrl)
			gpio_free(fts_pdata->fts_chip_data->vci_gpio_ctrl);
	}
	if (1 == fts_pdata->fts_chip_data->vddio_gpio_type) {
		if (fts_pdata->fts_chip_data->vddio_gpio_ctrl)
			gpio_free(fts_pdata->fts_chip_data->vddio_gpio_ctrl);
	}
}

static int i2c_communicate_check(void)
{
	int i = 0;
	int ret = NO_ERR;
	unsigned char cmd = 0;
	unsigned char reg_val = 0;

	for (i = 0; i < I2C_RW_TRIES; i++) {
		cmd = FTS_REG_CHIP_ID;
		ret = fts_i2c_read(&cmd, 1, &reg_val, 1);
		if (ret < 0) {
			TS_LOG_ERR("%s:chip id read fail, ret=%d, i=%d\n",
				__func__, ret, i);
			msleep(50);
		} else {
			TS_LOG_INFO("%s:chip id read success, chip id:0x%X\n",
				__func__, reg_val);
			ret = NO_ERR;
			return ret;
		}
	}

	return ret;
}

static int fts_chip_detect(
	struct device_node *device,
	struct ts_device_data *chip_data,
	struct platform_device *ts_dev)
{
	int ret = NO_ERR;

	if (!device || !chip_data || !ts_dev) {
		TS_LOG_ERR("%s:device, chip_data or ts_dev is NULL\n",
			__func__);
		return -ENOMEM;
	}

	fts_platform_data
		= kmalloc(sizeof(struct fts_ts_platform_data), GFP_KERNEL);
	if (!fts_platform_data) {
		TS_LOG_ERR("%s:Failed to allocate memory\n", __func__);
		return -ENOMEM;
	}

	/* init platform data */
	memset(fts_platform_data, 0, sizeof(struct fts_ts_platform_data));
	
	chip_data->easy_wakeup_info.sleep_mode = TS_POWER_OFF_MODE;
	chip_data->easy_wakeup_info.easy_wakeup_gesture = false;
	chip_data->easy_wakeup_info.easy_wakeup_flag = false;
	chip_data->easy_wakeup_info.palm_cover_flag = false;
	chip_data->easy_wakeup_info.palm_cover_control = false;
	chip_data->easy_wakeup_info.off_motion_on = false;
	chip_data->is_in_cell = true;

	fts_platform_data->fts_chip_data = chip_data;
	fts_platform_data->fts_platform_dev = ts_dev;
	fts_platform_data->fts_platform_dev->dev.of_node = device;

	fts_platform_data->i2c_client = chip_data->client;
	
	fts_platform_data->x_resolution_max = chip_data->x_max - 1;
	fts_platform_data->y_resolution_max = chip_data->y_max - 1;

	g_ts_data.feature_info.holster_info.holster_switch =false;

	fts_i2c_client = g_ts_data.client;

	ret = fts_regulator_get(fts_platform_data);
	if (ret < 0) {
		goto regulator_err;
	}

	ret = fts_gpio_request(fts_platform_data);
	if (ret < 0) {
		goto gpio_err;
	}

	ret = fts_pinctrl_get_init(fts_platform_data);
	if (ret < 0) {
		goto pinctrl_get_err;
	}

	/* reset the chip */
	if (!chip_data->disable_reset) {
		fts_hardware_reset(fts_platform_data, FTS_MODEL_FIRST_START);
		TS_LOG_INFO("%s:chip has been reset\n", __func__);
	} else {
		TS_LOG_INFO("%s:chip not do reset\n", __func__);
	}

	ret = i2c_communicate_check();
	if (ret < 0) {
		TS_LOG_ERR("%s:not find fts device\n", __func__);
		goto check_err;
	} else {
		TS_LOG_INFO("%s:find fts device\n", __func__);
		goto out;
	}
out:
	TS_LOG_INFO("%s:fts chip detect done\n", __func__);
	return NO_ERR;

check_err:
pinctrl_get_err:
	fts_gpio_free(fts_platform_data);
gpio_err:
	fts_regulator_put(fts_platform_data);
regulator_err:
	if (fts_platform_data)
		kfree(fts_platform_data);
	fts_platform_data = NULL;
	TS_LOG_ERR("no power\n");
	return ret;
}

static int fts_wrong_touch(void)
{
	return NO_ERR;
}
static int fts_init_chip(void)
{
	int ret = NO_ERR;
	u8 uc_chip_id=0;
	u8 uc_tp_fm_ver=0;
	u8 vendor_id = 0;

	ret = fts_apk_node_init();
	if (ret < 0) {
		TS_LOG_ERR("%s:fts_apk_node_init error.\n", __func__);
		goto init_err;
	}

	/* init sysfs file node module */
	ret = fts_sysfs_init(fts_i2c_client);
	if(ret < 0) {
		goto apk_node_exit;
	}

	/* init flash TP IC firmware module */
	ret = fts_flash_init(fts_i2c_client);
	if(ret < 0) {
		goto sysfs_exit;
	}

	ret = fts_read_reg(FTS_REG_CHIP_ID, &uc_chip_id);
	if (ret < 0) {
		TS_LOG_ERR("read FTS_REG_CHIP_ID error.\n");
		goto init_err;
	} else {
		TS_LOG_INFO("chip id: 0x%x\n", uc_chip_id);
		ret = NO_ERR;
	}

	fts_upgrade_info_curr.chip_id = fts_upgrade_delay.chip_id;

	ret = fts_get_ic_firmware_version(&uc_tp_fm_ver);
	if (ret < 0) {
		TS_LOG_ERR("read FTS_REG_FW_VER error.\n");
		goto init_err;
	} else {
		TS_LOG_INFO("TP firmware version: 0x%x\n", uc_tp_fm_ver);
		ret = NO_ERR;
	}

	ret = fts_read_reg(FTS_REG_VENDOR_ID, &vendor_id);
	if (ret < 0) {
		TS_LOG_ERR("read FTS_REG_VENDOR_ID error.\n");
		goto init_err;
	} else {
		TS_LOG_INFO("TP vendor id: 0x%x\n", vendor_id);
		ret = NO_ERR;
	}

	if(uc_chip_id != fts_upgrade_info_curr.chip_id){
		fts_upgrade_info_curr.tp_firmware_ver = 0;
		fts_upgrade_info_curr.vendor_id = 0;
	} else {
		fts_upgrade_info_curr.tp_firmware_ver = uc_tp_fm_ver;
		fts_upgrade_info_curr.vendor_id = vendor_id;
	}

	if(0 == fts_upgrade_info_curr.vendor_id) {
		ret = fts_read_vendor_id(fts_platform_data, &vendor_id);
		if ( ret < 0 ) {
			TS_LOG_INFO("[FTS] read boot vendor_id is error\n");
			goto flash_exit;
		}
		fts_upgrade_info_curr.vendor_id = vendor_id;
        	TS_LOG_INFO("read boot vendor_id is success vendor_id: 0x%x\n", fts_upgrade_info_curr.vendor_id);
	} else {
		TS_LOG_INFO("no need read boot vendor id.\n");
	}

	TS_LOG_INFO("[FTS] init chip done.\n");

	return NO_ERR;

flash_exit:
	fts_flash_exit();

sysfs_exit:
	fts_sysfs_exit(fts_i2c_client);

apk_node_exit:
	fts_apk_node_exit();

init_err:
	TS_LOG_ERR("fts init chip error.\n");

	return ret;
}

static int fts_irq_top_half(struct ts_cmd_node *cmd)
{
	cmd->command = TS_INT_PROCESS;
	TS_LOG_DEBUG("[fts]fts irq top half called\n");
	return NO_ERR;
}

static int fts_irq_bottom_half(struct ts_cmd_node *in_cmd,
					 struct ts_cmd_node *out_cmd)
{
	struct ts_fingers *info =
		&out_cmd->cmd_param.pub_params.algo_param.info;
	int x = 0, y = 0, wx = 0, wy = 0, z = 0;

	int i = 0;

	int touch_count = 0;
	struct ts_event st_touch_data;

	out_cmd->command = TS_INPUT_ALGO;
	out_cmd->cmd_param.pub_params.algo_param.algo_order =
		fts_platform_data->fts_chip_data->algo_id;
	TS_LOG_DEBUG("[fts]order: %d\n",
			 out_cmd->cmd_param.pub_params.algo_param.algo_order);

	fts_read_touch_data(&st_touch_data);

	for(i = 0; i<st_touch_data.touch_point; i++)
		{
		x = st_touch_data.position_x[i];
		y = st_touch_data.position_y[i];
		wx = st_touch_data.area[i];
		wy = st_touch_data.area[i];
		z = st_touch_data.pressure[i];

		TS_LOG_DEBUG("[fts] P %d:\n"
				 "x = %d\n"
				 "y = %d\n"
				 "wx = %d\n"
				 "wy = %d\n",
				 st_touch_data.finger_id[i], x, y, wx, wy);
		info->fingers[st_touch_data.finger_id[i]].status = TP_FINGER;

		info->fingers[st_touch_data.finger_id[i]].x = x;
		info->fingers[st_touch_data.finger_id[i]].y = y;
		info->fingers[st_touch_data.finger_id[i]].major = wx;
		info->fingers[st_touch_data.finger_id[i]].minor = wy;
		info->fingers[st_touch_data.finger_id[i]].pressure = z;

		touch_count++;
	}

	info->cur_finger_number = touch_count;
	TS_LOG_DEBUG("[fts]fts_abs_report, touch_count = %d\n", touch_count);

	return NO_ERR;
}

static int fts_fw_update_boot(char *file_name)
{
	return fts_firmware_auto_update(fts_platform_data, file_name);
}

static int fts_fw_update_sd(void)
{
	return fts_firmware_manual_update(fts_platform_data,
		FTS_FW_MANUAL_UPDATE_FILE_NAME);
}

static int fts_chip_get_info(struct ts_chip_info_param *info)
{
	return NO_ERR;
}

static int fts_set_info_flag(struct ts_data *info)
{
	fts_platform_data->fts_ts_data = info;
	return NO_ERR;
}

static int fts_before_suspend(void)
{
	return NO_ERR;
}

static int fts_suspend(void)
{
	fts_write_reg(FTS_REG_SLEEP, 0x03);
	return NO_ERR;
}
static int fts_resume(void)
{
	return NO_ERR;
}
static int fts_after_resume(void *feature_info)
{
	return NO_ERR;
}

static int fts_wakeup_gesture_enable_switch(struct
						  ts_wakeup_gesture_enable_info *info)
{
	return NO_ERR;
}

static void fts_shutdown(void)
{
}

static int fts_input_config(struct input_dev *input_dev)
{
	set_bit(EV_SYN, input_dev->evbit);
	set_bit(EV_KEY, input_dev->evbit);
	set_bit(EV_ABS, input_dev->evbit);
	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOL_FINGER, input_dev->keybit);

	set_bit(TS_PALM_COVERED, input_dev->keybit);

#ifdef INPUT_PROP_DIRECT
	set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
#endif

	input_set_abs_params(input_dev, ABS_X,
				 0, fts_platform_data->x_resolution_max, 0, 0);
	input_set_abs_params(input_dev, ABS_Y,
				 0, fts_platform_data->y_resolution_max, 0, 0);
	input_set_abs_params(input_dev, ABS_PRESSURE, 0, 255, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TRACKING_ID, 0, 10, 0, 0);

	input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0,
				 fts_platform_data->x_resolution_max, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0,
				 fts_platform_data->y_resolution_max, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_PRESSURE, 0, 255, 0, 0);
#ifdef REPORT_2D_W
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0,
				 MAX_ABS_MT_TOUCH_MAJOR, 0, 0);
#endif

#ifdef TYPE_B_PROTOCOL
#ifdef KERNEL_ABOVE_3_7
	/* input_mt_init_slots now has a "flags" parameter */
	input_mt_init_slots(input_dev, 10, INPUT_MT_DIRECT);
#else
	input_mt_init_slots(input_dev, 10);
#endif
#endif

	fts_input_dev = input_dev;

	return NO_ERR;
}

static int fts_reset_device(void)
{
	return NO_ERR;
}

static int fts_get_debug_data(
	struct ts_diff_data_info *info,
	struct ts_cmd_node *out_cmd)
{
	int rc = NO_ERR;
	struct fts_test_params *params = NULL;

	params = vmalloc(sizeof(struct fts_test_params));
	if (NULL == params) {
		TS_LOG_ERR("%s:allocate fts_test_params memory failure\n", __func__);
		return -EIO;
	}
	memset(params, 0, sizeof(struct fts_test_params));
	//read and parse dts settings
	if (fts_set_param_data(fts_platform_data, params) < 0) {
		TS_LOG_ERR("%s:get testparam from dts failure\n", __func__);
		goto err;
	}

	switch(info->debug_type) {
	case READ_DIFF_DATA:
		TS_LOG_INFO("%s:READ_DIFF_DATA\n", __func__);
		rc = fts_get_diff_data_for_debug(info->buff, 1, params);
		break;
	case READ_RAW_DATA:
		TS_LOG_INFO("%s:READ_RAW_DATA\n", __func__);
		rc = fts_get_diff_data_for_debug(info->buff, 0, params);
		break;
	default:
		TS_LOG_ERR("failed to recognize debug_type\n");
		break;
	}

	info->used_size = info->buff[0]*info->buff[1];

	if (NULL != params)
		vfree(params);

	return rc;

err:
	if (NULL != params)
		vfree(params);
	return -EIO;
}



static int fts_palm_switch(struct ts_palm_info *info)
{
	return NO_ERR;
}

static int fts_glove_switch(struct ts_glove_info *info)
{
	int ret = NO_ERR;
	u8 buf = 0;

	if (!info) {
		TS_LOG_ERR("fts_glove_switch: info is Null\n");
		ret = -ENOMEM;
		return ret;
	}

	switch (info->op_action) {
	case TS_ACTION_READ:
		ret = fts_get_glove_switch(&buf);
		if (ret < 0) {
			TS_LOG_ERR("get glove switch(%d), failed : %d", info->glove_switch, ret);
			break;
		}
		info->glove_switch = buf;
		TS_LOG_INFO("read_glove_switch=%d, 1:on 0:off\n",info->glove_switch);
		break;
	case TS_ACTION_WRITE:
		buf = info->glove_switch;
		TS_LOG_INFO("write_glove_switch=%d\n",info->glove_switch);
		if((GLOVE_SWITCH_ON != info->glove_switch) && (GLOVE_SWITCH_OFF != info->glove_switch))
		{
			TS_LOG_ERR("write wrong state: buf = %d\n", buf);
			ret = -EFAULT;
			break;
		}
		ret = fts_set_glove_switch(buf);
		if (ret < 0) {
			TS_LOG_ERR("set glove switch(%d), failed : %d", buf, ret);
		}
		break;
	default:
		TS_LOG_ERR("invalid switch status: %d", info->glove_switch);
		ret = -EINVAL;
		break;
	}

	return ret;

}

static int fts_get_glove_switch(u8 *glove_switch)
{
	int ret = NO_ERR;
	int glove_temp_value;
	unsigned char glove_enable_addr;

	u8 buf[2] ={0};

	glove_enable_addr = g_ts_data.feature_info.glove_info.glove_switch_addr;

	TS_LOG_INFO("fts glove_enable_addr=%d\n", glove_enable_addr);

	if (!glove_enable_addr) {
		TS_LOG_ERR("glove_enable_addr is null, glove feature is not supported.\n");
		goto out;
	}

	buf[0]=glove_enable_addr;

	ret = fts_i2c_read(buf, 1, buf, 1);
	if (ret < 0) {
		TS_LOG_ERR("read glove information failed: %d\n", ret);
		goto out;
	} else {
		ret = 0;
	}
	
	if (buf[0]) {
		glove_temp_value = 1;
	} else {
		glove_temp_value = 0;
	}

	*glove_switch = glove_temp_value;

	TS_LOG_INFO("fts glove_enable_flag=%d\n", *glove_switch);
out:
	return ret;
}

static int fts_set_glove_switch(u8 glove_switch)
{
	int ret = NO_ERR;
	int glove_temp_value;
	unsigned char glove_enable_addr;
	u8 buf[2] = {0};

	glove_enable_addr = g_ts_data.feature_info.glove_info.glove_switch_addr;

	TS_LOG_INFO("fts glove_enable_addr=%d\n", glove_enable_addr);

	if (!glove_enable_addr) {
		TS_LOG_ERR("glove_enable_addr is null, glove feature is not supported.\n");
		goto out;
	}

	if (glove_switch) {
		glove_temp_value = 1;
	}
	else {
		glove_temp_value = 0;
	}

	buf[0]=glove_enable_addr;
	buf[1]=glove_temp_value;

	ret = fts_i2c_write(buf, 2);
	if (ret < 0) {
		TS_LOG_ERR("write glove information failed: %d\n", ret);
	}
	else
		ret = 0;
out:
	return ret;
}

static int fts_charger_switch(struct ts_charger_info *info)
{
	return NO_ERR;
}

static int fts_holster_switch(struct ts_holster_info *info)
{
	return NO_ERR;
}

static int fts_roi_switch(struct ts_roi_info *info)
{
	return NO_ERR;
}

static unsigned char *fts_roi_rawdata(void)
{
	return NO_ERR;
}

static int fts_chip_get_capacitance_test_type(struct ts_test_type_info *info)
{
	int ret = NO_ERR;

	if (!info) {
		TS_LOG_ERR("fts_chip_get_capacitance_test_type: info is Null\n");
		ret = -ENOMEM;
		return ret;
	}
	switch (info->op_action) {
		case TS_ACTION_READ:
			memcpy(info->tp_test_type, fts_platform_data->fts_chip_data->tp_test_type,TS_CAP_TEST_TYPE_LEN);
			TS_LOG_INFO("[FTS] read_chip_get_test_type=%s, \n",info->tp_test_type);
			break;
		case TS_ACTION_WRITE:
			break;
		default:
			TS_LOG_ERR("invalid status: %s", info->tp_test_type);
			ret = -EINVAL;
			break;
	}
	return ret;

	return NO_ERR;
}

static int fts_calibrate(void)
{
	return NO_ERR;
}

static int fts_calibrate_wakeup_gesture(void)
{
	return NO_ERR;
}

#if defined (CONFIG_HUAWEI_DSM)
static int fts_rmi4_dsm_debug(void)
{
	return NO_ERR;
}

#endif
static int fts_regs_operate(struct ts_regs_info *info)
{
	return NO_ERR;
}


