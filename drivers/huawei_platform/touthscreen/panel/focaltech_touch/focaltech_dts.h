/*
 *
 * focaltech touchscreen driver.
 * 
 * copyright (c) 2010-2016, focaltech systems, ltd., all rights reserved.
 *
 * this software is licensed under the terms of the gnu general public
 * license version 2, as published by the free software foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * gnu general public license for more details.
 *
 */

#ifndef __FOCALTECH_DTS_H__
#define __FOCALTECH_DTS_H__

#include <linux/i2c.h>

#define FTS_CHIP_NAME			"fts"
#define FTS_COMPATIBLE_NAME_LEN		32

#define FTS_IRQ_GPIO			"attn_gpio"
#define FTS_RST_GPIO			"reset_gpio"
#define FTS_VDDIO_GPIO_CTRL		"vddio_ctrl_gpio"
#define FTS_VCI_GPIO_CTRL		"vci_ctrl_gpio"
#define FTS_IRQ_CFG			"irq_config"
#define FTS_ALGO_ID			"algo_id"
#define FTS_VDD     			"fts-vdd"
#define FTS_VBUS     			"fts-io"
#define FTS_IC_TYPES			"ic_type"
#define FTS_WD_CHECK    		"need_wd_check_status"
#define FTS_X_MAX			"x_max"
#define FTS_Y_MAX			"y_max"
#define FTS_X_MAX_MT			"x_max_mt"
#define FTS_Y_MAX_MT			"y_max_mt"
#define FTS_UNIT_CAP_TEST_INTERFACE	"unite_cap_test_interface"
#define FTS_REPORT_RATE_TEST		"report_rate_test"
#define FTS_VCI_GPIO_TYPE		"vci_gpio_type"
#define FTS_VCI_REGULATOR_TYPE		"vci_regulator_type"
#define FTS_VDDIO_GPIO_TYPE		"vddio_gpio_type"
#define FTS_VDDIO_REGULATOR_TYPE	"vddio_regulator_type"
#define FTS_COVER_FORCE_GLOVE		"force_glove_in_smart_cover"
#define FTS_TEST_TYPE			"tp_test_type"
#define FTS_HOSTLER_SWITCH_ADDR		"holster_switch_addr"
#define FTS_HOSTLER_SWITCH_BIT		"holster_switch_bit"
#define FTS_GLOVE_SWITCH_ADDR		"glove_switch_addr"
#define FTS_GLOVE_SWITCH_BIT		"glove_switch_bit"

#define FTS_VCI_LDO_VALUE		"vci_value"
#define FTS_VDDIO_LDO_VALUE		"vddio_value"
#define FTS_NEED_SET_VDDIO_VALUE	"need_set_vddio_value"

#define FTS_FW_UPDATE_LOGIC		"fw_update_logic"
#define TEST_ENHANCE_RAW_DATA_CAPACITANCE "test_enhance_raw_data_capacitance"
#define SHOULD_CHECK_TP_CALIBRATION_INFO  "should_check_tp_calibration_info"

#define FTS_CHIP_ID_DTS 		"chip_id"
#define FTS_HARD_RESET_DELAY 		"hard_reset_delay"
#define FTS_ERASE_MIN_DELAY 		"erase_min_delay"
#define FTS_CALC_CRC_DELAY 		"calc_crc_delay"
#define FTS_REBOOT_DELAY 		"reboot_delay"
#define FTS_ERASE_QUERY_PER_TIME_DELAY 	"erase_query_per_time_delay"

#define FTS_WRITE_FLASH_MAX_QUERY_TIME 	"write_flash_max_query_time"
#define FTS_READ_ECC_MAX_QUERY_TIME 	"read_ecc_max_query_time"
#define FTS_ERASE_FLASH_MAX_QUERY_TIME 	"erase_flash_max_query_time"
#define FTS_UPGRADE_LOOP_TIME 		"upgrade_loop_time"

#define DTS_CHANNEL_NUM_TEST		"test_item,channel_num_test"
#define DTS_RAWDATA_TEST		"test_item,rawdata_test"
#define DTS_CB_TEST			"test_item,cb_test"
#define DTS_SHORT_CIRCUIT_TEST		"test_item,short_circuit_test"
#define DTS_OPEN_TEST			"test_item,open_test"

#define DTS_INVALID_NODE		"detail_threshold,invalid_node_"
#define DTS_RAWDATA_TEST_MIN_TX		"detail_threshold,rawdata_test_min_tx"
#define DTS_RAWDATA_TEST_MAX_TX		"detail_threshold,rawdata_test_max_tx"
#define DTS_CB_TEST_MIN_TX		"detail_threshold,cb_test_min_tx"
#define DTS_CB_TEST_MAX_TX		"detail_threshold,cb_test_max_tx"

#define DTS_RAW_DATA_MIN		"basic_threshold,rawdata_test_min"
#define DTS_RAW_DATA_MAX		"basic_threshold,rawdata_test_max"
#define DTS_CB_TEST_MIN			"basic_threshold,cb_test_min"
#define DTS_CB_TEST_MAX			"basic_threshold,cb_test_max"

#define DTS_CHANNEL_NUM_X	"basic_threshold,channel_num_test_channel_x"
#define DTS_CHANNEL_NUM_Y	"basic_threshold,channel_num_test_channel_y"
#define DTS_CHANNEL_NUM_KEY	"basic_threshold,channel_num_test_key_num"

#define DTS_CB_TEST_VA_CHECK		"basic_threshold,cb_test_va_check"
#define DTS_CB_TEST_VKEY_CHECK		"basic_threshold,cb_test_vkey_check"
#define DTS_CB_TEST_MIN_VKEY		"basic_threshold,cb_test_min_vkey"
#define DTS_CB_TEST_MAX_VKEY		"basic_threshold,cb_test_max_vkey"

#define DTS_SHORT_CIRCUIT_TEST_REG_MIN	"basic_threshold,short_circuit_test_res_min"
#define DTS_OPEN_TEST_CB_MIN		"basic_threshold,open_test_cb_min"

#define DTS_OPEN_TEST_CHECK_K1		"basic_threshold,open_test_check_k1"
#define DTS_OPEN_TEST_K1_THRESHOLD	"basic_threshold,open_test_k1_threshold"
#define DTS_OPEN_TEST_CHECK_K2		"basic_threshold,open_test_check_k2"
#define DTS_OPEN_TEST_K2_THRESHOLD	"basic_threshold,open_test_k2_threshold"

int fts_test_dt_find_property(const char *propname);

int fts_test_dt_read_string(const char *propname, u8 *out_value);
int fts_test_dt_read_u32(const char *propname, u32 *out_value);
int fts_test_dt_read_u32_array(const char *propname, u32 *out_value);
int fts_dt_init(struct i2c_client *client);
int fts_dt_exit(struct i2c_client *client);

void fts_test_dt_init_device_node(struct device_node *dev_node);

int fts_get_vendor_name_from_dts(const char *project_id,
	char *vendor_name, size_t size);

int fts_parse_dts(struct device_node *dev_node,
	struct ts_device_data *chip_data);

int fts_init_capacitance_test_data(struct fts_ts_platform_data *fts_pdata,
	struct fts_test_params *params);


#endif
