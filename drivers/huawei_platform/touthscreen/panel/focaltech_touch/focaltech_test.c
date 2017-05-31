/*************************************************************
* copyright (c) 2012-2015, focaltech systems (r)£¬all rights reserved.
*
* file name: test_ft8716.c
*
* author: software development
*
* created: 2015-12-24
*
* abstract: test item for ft8716
*
**************************************************************/

/**************************************************************
* included header files
**************************************************************/
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <huawei_platform/touthscreen/huawei_touchscreen.h>

#include "focaltech_test.h"
#include "focaltech_flash.h"
#include "focaltech_dts.h"

/*buff length*/
#define BUFF_LEN_STORE_MSG_AREA		(1024 * 10)
#define BUFF_LEN_MSG_AREA_LINE2		(1024 * 4)
#define BUFF_LEN_STORE_DATA_AREA	(1024 * 64)
#define BUFF_LEN_TMP_BUFFER		(1024 * 16)

#define MAX_NOISE_FRAMES		32
#define FTS_IC_MODE_ADDR		0x00
#define REG_LINE_NUM			0x01
#define REG_TX_NUM			0x02
#define REG_RX_NUM			0x03
#define FT8716_LEFT_KEY_REG		0X1E
#define FT8716_RIGHT_KEY_REG		0X1F

#define REG_CB_ADDR_H			0x18
#define REG_CB_ADDR_L			0x19
#define REG_ORDER_ADDR_H		0x1A
#define REG_ORDER_ADDR_L		0x1B

#define REG_RAW_BUF0			0x6A
#define REG_RAW_BUF1			0x6B
#define REG_ORDER_BUF0			0x6C
#define REG_CB_BUF0			0x6E

#define REG_K1_DELAY			0x31
#define REG_K2_DELAY			0x32
#define REG_SC_CHANNEL_CF		0x34

#define REG_CLB				0x04

#define REG_IS_DIFF_SWITCH	0x06

#define DATA_TYPE_RAWDATA	0xAD
#define DATA_TYPE_KEYDATA	0xAE

#define REG_SCAN_ADC_SWITCH	0x0F
#define REG_SCAN_ADC_STATUS	0x10
#define REG_ADC_DATA_ADDR	0x89
#define MAX_ADC_NUM		2047
#define REG_K1_ADDR		0x31
#define REG_K2_ADDR		0x32
#define REG_GIP_SWITCH          0x20
#define MAX_CB_VALUE		200

#define MAX_RESULT_STR_LEN	80

#define FTS_RAWDATA_BUFF_MAX (TX_NUM_MAX * RX_NUM_MAX)

#define FTS_DRIVER_LIB_INFO  "Test_Lib_Version   V1.7.0 2016-06-08"

#define FTS_TEST_BUFFER_SIZE		(64 * 1024)
#define FTS_TEST_PRINT_SIZE		128

#define FTS_TEST_STORE_DATA_SIZE		(64 * 1024)

static int fts_start_scan(void);
static unsigned char fts_chip_clb(unsigned char *pclb_result);
static unsigned char fts_read_raw_data(unsigned char freq,
	unsigned char linenum, int bytenum, int *prev_buff);
static unsigned char fts_get_panel_rows(unsigned char *ppanel_rows);
static unsigned char fts_get_panel_cols(unsigned char *ppanel_cols);
static unsigned char fts_get_cb_data(unsigned short start_node_no,
	unsigned short readnum, unsigned char *pread_buffer);
static unsigned char fts_weakshort_get_adc_data(int all_adc_data_len,
	int *prev_buff);
static unsigned char fts_get_rawdata(struct fts_test_params *params);
static unsigned char fts_get_channel_num(struct fts_test_params *params);
static void fts_print_raw_data(char *msg, int row, int col, int max,
	int min, int value);

extern struct fts_upgrade_info fts_upgrade_info_curr;
extern struct fts_ts_platform_data *fts_platform_data;

int fts_abs(int value)
{
	return (value > 0) ? (value) : (-value);
}

/*
 * name: fts_enter_work_model(same function name as ft_multipletest)
 * brief:  enter work mode
 * input: NULL
 * output: NULL
 * return: comm code. code = 0x00 is ok, else fail.
 */
unsigned char fts_enter_work_model_from_factory(void) 
{
	int i = 0;
	unsigned char ret = 0;
	unsigned char ic_status = 0;

	TS_LOG_DEBUG("%s: enter work\n", __func__);

	for (i = 0; i < MAX_RETRY_TIMES; i++) {
		ret = fts_read_reg(FTS_IC_MODE_ADDR, &ic_status);
		if (ret) {
			TS_LOG_ERR("%s:read ic status fail, ret=%d\n",
				__func__, ret);
			return ret;
		}

		if (((ic_status >> 4) & 0x07) == DEVICE_MODE_WORK) {
			TS_LOG_INFO("%s: change work mode success\n", __func__);
			return 0;
		}

		ret = fts_write_reg(FTS_IC_MODE_ADDR, DEVICE_MODE_WORK);
		if (ret) {
			msleep(50);
			continue;
		} else {
			TS_LOG_ERR("%s:change work mode failed, ret=%d\n",
				__func__, ret);
			break;
		}
			
	}

	return -ENODEV;
}

/*
 * name: fts_enter_factory
 * brief:  enter fcatory mode
 * input: NULL
 * output: NULL
 * return: comm code. code = 0 is ok, else fail.
 */
unsigned char fts_enter_factory(void) 
{
	int i = 0;
	unsigned char ret = 0;
	unsigned char ic_status = 0;

	for (i = 0; i < MAX_RETRY_TIMES; i++) {
		ret = fts_read_reg(FTS_IC_MODE_ADDR, &ic_status);
		if (ret) {
			TS_LOG_ERR("%s: read ic status fail, ret-%d\n",
				__func__, ret);
			break;
		}

		if (((ic_status >> 4) & 0x07) == 0x04) {
			TS_LOG_INFO("%s:change factory success\n", __func__);
			return 0;
		}

		ret = fts_write_reg(FTS_IC_MODE_ADDR, DEVICE_MODE_FACTORY);
		if (ERROR_CODE_OK == ret) {
			msleep(50);
			continue;
		} else {
			TS_LOG_ERR("%s:write factory model fail, ret=%d\n",
				__func__, ret);
			break;
		}
	}

	TS_LOG_ERR("%s:enter factory model fail, ret=%d\n", __func__, ret);
	return -ENODEV;
}


/*
 * name: start_test
 *
 * brief:  test entry. determine which test item to test
 *
 * input: none
 *
 * output: none
 *
 * return: test result, pass or fail
 */
static int get_int_average(int *p, size_t len)
{
	int sum = 0;
	int tmp = 0;
	size_t i;

	for (i = 0; i < len; i++)
		sum += p[i];
	if (len != 0) {
		tmp = sum / len;
		return tmp;
	} else {
		return 0;
	}
}

static int get_int_min(int *p, size_t len)
{
	int s_min = SHRT_MAX;
	size_t i;

	for (i = 0; i < len; i++)
		s_min = s_min > p[i] ? p[i] : s_min;

	return s_min;
}

static int get_int_max(int *p, size_t len)
{
	int s_max = SHRT_MIN;
	size_t i;

	for (i = 0; i < len; i++)
		s_max = s_max < p[i] ? p[i] : s_max;

	return s_max;
}

void fts_set_max_channel_num(struct fts_test_params *params) 
{
	params->scap_config.iused_max_tx_num = TX_NUM_MAX;
	params->scap_config.iused_max_rx_num = RX_NUM_MAX;
}

void fts_set_test_item(struct fts_test_params *params) 
{
	int i = 0;
	
	params->item_num = 0;

	/* rawdata test */
	if (1 == params->item_switchs.rawdata_test) {
		params->item_info[i].item_code = code_rawdata_test;
		params->item_info[i].test_num = i;
		params->item_info[i].item_type = RESULT_NULL;
		i++;
	}

	/* cb_test */
	if (1 == params->item_switchs.cb_test) {
		params->item_info[i].item_code = code_cb_test;
		params->item_info[i].test_num = i;
		params->item_info[i].item_type = RESULT_NULL;
		i++;
	}

	/* open_test */
	if (1 == params->item_switchs.open_test) {
		params->item_info[i].item_code = code_open_test;
		params->item_info[i].test_num = i;
		params->item_info[i].item_type = RESULT_NULL;
		i++;
	}

	/* short test */
	if (1 == params->item_switchs.short_test) {
		params->item_info[i].item_code = code_short_circuit_test;
		params->item_info[i].test_num = i;
		params->item_info[i].item_type = RESULT_NULL;
		i++;
	}

	params->item_num = i;
}


bool fts_start_test_tp(struct fts_test_params *params)
{
	bool final_test_result = true;
	bool current_test_result = 1;
	unsigned char ret;
	int i = 0;

	/* 1. init data */
	TS_LOG_INFO("%s: start test tp\n",  __func__);
	params->scap_config.key_num = 0;
	params->scap_config.key_num_total = 6;

	if (0 == params->item_num)
		final_test_result = false;

	ret = fts_raw_data_test(params, &current_test_result);
	if (ret || (!current_test_result)) {
		final_test_result = false;
		params->item_info[i].test_result = RESULT_NG;
	} else {
		params->item_info[i].test_result = RESULT_PASS;
	}

	i++;
	ret = fts_cb_test(&current_test_result, params);
	if (ret || (!current_test_result)) {
		final_test_result = false;
		params->item_info[i].test_result = RESULT_NG;
	} else {
		params->item_info[i].test_result = RESULT_PASS;
	}

	i++;
	ret = fts_open_test(&current_test_result, params);
	if (ret || (!current_test_result)) {
		final_test_result = false;
		params->item_info[i].test_result = RESULT_NG;
	} else {
		params->item_info[i].test_result = RESULT_PASS;
	}
	
	i++;
	ret = fts_short_circuit_test(&current_test_result, params);
	if (ret || (!current_test_result)) {
		final_test_result = false;
		params->item_info[i].test_result = RESULT_NG;
	} else {
		params->item_info[i].test_result = RESULT_PASS;
	}

	return final_test_result;
}

/*
 * name: fts_start_scan(same function name as ft_multipletest)
 * brief:  scan tp, do it before read raw data
 * input: none
 * output: none
 * return: comm code. code = 0x00 is ok, else fail.
 */
static int fts_start_scan(void)
{

	int i = 0;
	int ret = 0;
	
	unsigned char reg_val = 0x00;
	unsigned char max_times = 20;	/* max waiting 160ms */

	ret = fts_read_reg(FTS_IC_MODE_ADDR, &reg_val);
	if (ret) {
		TS_LOG_ERR("%s:read mode reg fail, ret=%d\n", __func__, ret);
		return ret;
	}

	reg_val |= 0x80;
	ret = fts_write_reg(FTS_IC_MODE_ADDR, reg_val);
	if (ret) {
		TS_LOG_ERR("%s:write scan command fail, ret=%d", __func__, ret);
		return ret;
	}

	msleep(8);

	for (i = 0; i < max_times; i++) {
		ret = fts_read_reg(FTS_IC_MODE_ADDR, &reg_val);
		if (ret) {
			TS_LOG_ERR("%s:read scan status fail, ret=%d\n",
				__func__, ret);
			msleep(8);
			continue;
		}

                TS_LOG_INFO("%s: ret_val=0x%X\n",
				__func__, reg_val);
		if ((reg_val >> 7) == 0) {
			TS_LOG_INFO("%s:scan finished, ret_val=0x%X\n",
				__func__, reg_val);
			return 0;
		} else {
			msleep(8);
		}
	}

	TS_LOG_ERR("%s:scan command exec fail, ret=%d\n", __func__, ret);
	return -ENODEV;

}

/*
 * name: fts_read_raw_data(same function name as ft_multipletest)
 * brief:  read raw data
 * input: freq(no longer used, reserved), linenum, bytenum
 * output: prev_buff
 * return: comm code. code = 0x00 is ok, else fail.
 */
static unsigned char fts_read_raw_data(
	unsigned char freq,
	unsigned char line_num,
	int byte_num,
	int *prev_buff)
{
	int ret = 0;
	unsigned char i2c_wbuffer[3] = { 0 };
	unsigned char pread_data[byte_num];
	int i, iread_num;
	unsigned short bytes_num_in_test_mode1 = 0;

	iread_num = byte_num / BYTES_PER_TIME;

	if (0 != (byte_num % BYTES_PER_TIME))
		iread_num++;

	if (byte_num <= BYTES_PER_TIME)
		bytes_num_in_test_mode1 = byte_num;
	else
		bytes_num_in_test_mode1 = BYTES_PER_TIME;

	TS_LOG_INFO("bytes_num_in_test_mode1 = %d\n", bytes_num_in_test_mode1);

	i2c_wbuffer[0] = REG_RAW_BUF0;
	/* set row addr */
	ret = fts_write_reg(REG_LINE_NUM, line_num);
	if (ret) {
		TS_LOG_ERR("%s: write data failed to REG_LINE_NUM\n", __func__);
		return ret;
	}

	msleep(10);
	ret = fts_i2c_read(i2c_wbuffer, 1, pread_data, bytes_num_in_test_mode1);

	for (i = 1; i < iread_num; i++) {
		/* last packet */
		if (i == (iread_num - 1)) {
			msleep(10);
			ret = fts_i2c_read(NULL, 0,
				pread_data + BYTES_PER_TIME * i,
				byte_num - BYTES_PER_TIME * i);
		} else {
			msleep(10);
			ret = fts_i2c_read(NULL, 0,
				pread_data + BYTES_PER_TIME * i,
				BYTES_PER_TIME);
		}
	}

	if (ret == ERROR_CODE_OK) {
		for (i = 0; i < (byte_num >> 1); i++) {
			prev_buff[i] = (pread_data[i << 1] << 8) +
				pread_data[(i << 1) + 1];
		}
	}

	return ret;

}
/************************************************************************
* name: fts_get_cb_data(same function name as ft_multipletest)
* brief:  get cb of tx/rx
* input: start_node_no, readnum
* output: pread_buffer
* return: comm code. code = 0x00 is ok, else fail.
***********************************************************************/
static unsigned char fts_get_cb_data(
	unsigned short start_node_no,
	unsigned short readnum,
	unsigned char *pread_buffer)
{
	unsigned char ret = ERROR_CODE_OK;
	unsigned short usreturn_num = 0;
	unsigned short ustotal_return_num = 0;
	unsigned char wbuffer[4];
	int i, iread_num;

	iread_num = readnum / BYTES_PER_TIME;

	if (0 != (readnum % BYTES_PER_TIME))
			iread_num++;

	wbuffer[0] = REG_CB_BUF0;
	ustotal_return_num = 0;

	for (i = 1; i <= iread_num; i++) {
		if (i * BYTES_PER_TIME > readnum)
			usreturn_num = readnum - (i - 1) * BYTES_PER_TIME;
		else
			usreturn_num = BYTES_PER_TIME;

		/* addr high 8 bits */
		wbuffer[1] = (start_node_no + ustotal_return_num) >> 8;
		/* addr low 8 bits */
		wbuffer[2] = (start_node_no + ustotal_return_num) & 0xff;

		ret = fts_write_reg(REG_CB_ADDR_H, wbuffer[1]);
		ret = fts_write_reg(REG_CB_ADDR_L, wbuffer[2]);
		ret = fts_i2c_read(wbuffer, 1,
			pread_buffer + ustotal_return_num, usreturn_num);

		ustotal_return_num += usreturn_num;

		if (ret != ERROR_CODE_OK)
			return ret;
	}

	return ret;
}

/* get panelrows */
static unsigned char fts_get_panel_rows(unsigned char *ppanel_rows)
{
	return fts_read_reg(REG_TX_NUM, ppanel_rows);
}

/* get panelcols */
static unsigned char fts_get_panel_cols(unsigned char *ppanel_cols) 
{
	return fts_read_reg(REG_RX_NUM, ppanel_cols);
}

/* auto clb */
static unsigned char fts_chip_clb(unsigned char *pclb_result)
{
	int i = 0;
	unsigned char reg_data = 0;
	unsigned char timeouttimes = 50;
	unsigned char ret = ERROR_CODE_OK;

	/*  start auto clb */
	ret = fts_write_reg(REG_CLB, 4);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: write REG_CLB reg failed\n", __func__);
		return ret;
	}

	while (timeouttimes--) {
		msleep(100);
		ret = fts_write_reg(FTS_IC_MODE_ADDR, 0x04 << 4);
		if (ERROR_CODE_OK != ret) {
			TS_LOG_ERR("%s: write reg failed\n", __func__);
			break;
		}
		ret = fts_read_reg(0x04, &reg_data);
		if (ERROR_CODE_OK != ret) {
			TS_LOG_ERR("%s: read 0x04 reg failed\n", __func__);
			break;
		}

		if (reg_data == 0x02) {
			*pclb_result = 1;
			break;
		}
	}

	if (0 == timeouttimes)
		*pclb_result = 0;
	
	return ret;
}

/************************************************************************
* name: fts_get_channel_num
* brief:  get num of ch_x, ch_y and key
* input: none
* output: none
* return: comm code. code = 0x00 is ok, else fail.
***********************************************************************/
static unsigned char fts_get_channel_num(struct fts_test_params *params)
{
	int i;
	unsigned char ret;
	unsigned char rbuffer[1];

	/* get channel x num */
	ret = fts_get_panel_rows(rbuffer);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: failed to get channel x number\n", __func__);
		return ret;
	}

	if (0 < rbuffer[0] && rbuffer[0] <= TX_NUM_MAX) {
		params->scap_config.channel_x_num = rbuffer[0];
		TS_LOG_INFO("%s: params->scap_config.channel_x_num = %d\n",
			__func__, params->scap_config.channel_x_num);
	}

	/* get channel y num */
	ret = fts_get_panel_cols(rbuffer);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: failed to get channel y number\n", __func__);
		return ret;
	}

	if (0 < rbuffer[0] && rbuffer[0] <= RX_NUM_MAX) {
		params->scap_config.channel_y_num = rbuffer[0];
		TS_LOG_INFO("%s: params->scap_config.channel_y_num = %d\n",
			__func__, params->scap_config.channel_y_num);
	}

	return ret;
}

/************************************************************************
* name: fts_get_channel_form_ic
* brief:  check whether tp can enter factory mode, and do some thing
* input: none
* output: none
* return: comm code. code = 0x00 is ok, else fail.
***********************************************************************/
unsigned char fts_get_channel_form_ic(struct fts_test_params *params)
{
	unsigned char ret;

	TS_LOG_INFO("%s: test item:channel test\n", __func__);

	ret = fts_get_channel_num(params);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: get channel num failed\n", __func__);
		return ret;
	}

	if ((params->threshold.channel_num_test_channel_x
		== params->scap_config.channel_x_num)
		&& (params->threshold.channel_num_test_channel_y
		== params->scap_config.channel_y_num)) {
		TS_LOG_INFO("%s: get channels: (chx: %d, chy: %d)\n", __func__,
			params->scap_config.channel_x_num,
			params->scap_config.channel_y_num);
		} else {
		TS_LOG_ERR("%s: get channels: (chx: %d, chy: %d)\n", __func__,
			params->scap_config.channel_x_num,
			params->scap_config.channel_y_num);
		}

	return ret;
}

/************************************************************************
* name: fts_get_rawdata
* brief:  get raw data of va area and key area
* input: none
* output: none
* return: comm code. code = 0x00 is ok, else fail.
***********************************************************************/
static unsigned char fts_get_rawdata(struct fts_test_params *params)
{
	int ret = ERROR_CODE_OK;
	int irow, icol;
	int i = 0;


	/* read rawdata for channel area */
	memset(params->rawdata, 0, sizeof(params->rawdata));
	memset(params->tmp_rawdata, 0, sizeof(params->tmp_rawdata));
	ret = fts_read_raw_data(0, DATA_TYPE_RAWDATA,
		params->scap_config.channel_x_num
		* params->scap_config.channel_y_num * 2,
		params->tmp_rawdata);

	if (ret) {
		TS_LOG_ERR("%s: failed to get rawdata\n", __func__);
		return ret;
	}

	return ret;
}

/*
 * name: fts_raw_data_test
 * brief:  testitem: rawdatatest. check if mcap rawdata is within the range.
 * input: btest_result
 * output: btest_result, pass or fail
 * return: comm code. code = 0x00 is ok, else fail.
 */
unsigned char fts_raw_data_test(
	struct fts_test_params *params,
	bool *test_result)
{
	int i = 0;
	int j = 0;
	int ret = 0;
	bool btmp_result = true;
	int rawdata_min;
	int rawdata_max;
	int ivalue = 0;
	unsigned char channel_x_num = 0;
	unsigned char channel_y_num = 0;

	//int **raw_data = NULL;
	//int *tmp_raw_data = NULL;
	
	TS_LOG_INFO("%s: test item raw data\n", __func__);

	ret = fts_enter_factory();
	if (ret) {
		*test_result = false;
		TS_LOG_ERR("%s:enter factory model fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	ret = fts_start_scan();
	if (ret) {
		TS_LOG_ERR("%s:scan fail, ret=%d\n", __func__, ret);
		return ret;
	}

	/*
	 * read rawdata:  because of first read rawdata data less
	 * so read rawdata need continuation readed third!
	 */
	for (i = 0; i < 3; i++)
		ret = fts_get_rawdata(params);
	if (ret) {
		TS_LOG_ERR("%s: failed to get raw data! error code: %d",
			__func__, ret);
		return ret;
	}

	//raw_data = params->rawdata;
	//tmp_raw_data = params->tmp_rawdata;
	channel_x_num = params->scap_config.channel_x_num;
	channel_y_num = params->scap_config.channel_y_num;

	if (params->rawdata == NULL) {
		TS_LOG_ERR("raw_data\n");
	}

	if (params->tmp_rawdata == NULL) {
		TS_LOG_ERR("tmp_raw_data\n");
	}
	
	for (i = 0; i < channel_x_num; ++i) {
		for (j = 0; j < channel_y_num; ++j) {
			params->rawdata[i][j] = params->tmp_rawdata[i * channel_y_num + j];
		}
	}

	/* show rawdata */
	TS_LOG_INFO("%s: va channels\n", __func__);
	for (i = 0; i < channel_x_num; i++) {
		TS_LOG_DEBUG("\nch_%02d:  ", i + 1);
		for (j = 0; j < channel_y_num; j++) {
			TS_LOG_DEBUG("%5d, ", params->rawdata[i][j]);
		}
	}

	rawdata_min = params->threshold.rawdata_test_min;
	rawdata_max = params->threshold.rawdata_test_max;
	/* to determine rawdata if in range or not */
	for (i = 0; i < channel_x_num; i++) {
		for (j = 0; j < channel_y_num; j++) {
			ivalue = params->rawdata[i][j];
			
			if (ivalue < rawdata_min || ivalue > rawdata_max) {
				btmp_result = false;
				fts_print_raw_data("raw data test fail",
					i, j,
					rawdata_max, rawdata_min, ivalue);
			}
		}
	}

	/* return result */
	if (btmp_result) {
		*test_result = true;
		TS_LOG_INFO("%s: rawdata test is ok!\n", __func__);
	} else {
		*test_result = false;
		TS_LOG_ERR("%s: rawdata test is fail!\n", __func__);
	}

	return ret;
}

static void fts_print_raw_data(
	char *msg,
	int row,
	int col,
	int max,
	int min,
	int value)
{
	
	TS_LOG_ERR("%s:%s,data[%d, %d]=%d, range=[%d, %d]\n",
		__func__, msg, row, col, value, min, max);
}


/************************************************************************
* name: fts_cb_test
* brief:  testitem: cb test. check if cb is within the range.
* input: none
* output: btest_result, pass or fail
* return: comm code. code = 0x00 is ok, else fail.
***********************************************************************/
unsigned char fts_cb_test(bool *btest_result, struct fts_test_params *params)
{
	bool btmp_result = true;
	unsigned char ret = ERROR_CODE_OK;
	int irow = 0;
	int icol = 0;
	int imax_value = 0;
	int imin_value = 0;
	int ix = params->scap_config.channel_x_num;
	int iy = params->scap_config.channel_y_num;

	int **cb_data = NULL;

	TS_LOG_INFO("%s: cb test start\n", __func__);

	ret = fts_get_cb_data(0, (short)(ix * iy 
		+ params->scap_config.key_num), params->uctmp_data);
	if (ret) {
		btmp_result = false;
		TS_LOG_INFO("%s: get cb data failed\n", __func__);
		goto test_err;
	}

	TS_LOG_INFO("%s: %d\n", __func__, __LINE__);

	memset(params->cbdata, 0, sizeof(params->cbdata));
	TS_LOG_INFO("%s: %d\n", __func__, __LINE__);
	cb_data = params->cbdata;
	TS_LOG_INFO("%s: %d\n", __func__, __LINE__);
	/* va area */
	for (irow = 0; irow < ix; ++irow) {
		TS_LOG_INFO("%s: %d\n", __func__, __LINE__);
		for (icol = 0; icol < iy; ++icol) {
			TS_LOG_INFO("%s: %d\n", __func__, __LINE__);
			params->cbdata[irow][icol]
				= params->uctmp_data[irow * iy + icol];
		}
	}

	/* show cb data */
	TS_LOG_INFO("%s: va channels\n", __func__);
	for (irow = 0; irow < ix; irow++) {
		TS_LOG_DEBUG("ch_%02d:\n", irow + 1);
		for (icol = 0; icol < iy; icol++)
			TS_LOG_DEBUG("%3d ", params->cbdata[irow][icol]);
	}

	/*use basic threshold*/
	
	imin_value = params->threshold.cb_test_min;
	imax_value = params->threshold.cb_test_max;

	for (irow = 0; irow < (ix + 1); irow++) {
		for (icol = 0; icol < iy; icol++) {
			if (irow >= ix)
				continue;

			if (fts_abs(params->cbdata[irow][icol]) < imin_value 
				|| fts_abs(params->cbdata[irow][icol])	> imax_value) {
				btmp_result = false;
				fts_print_raw_data("cb test failed", 
					irow + 1, icol + 1, 
					imax_value, imin_value, 
					params->cbdata[irow][icol]);
			}
		}
	}

	if (btmp_result) {
		*btest_result = true;
		TS_LOG_INFO("%s: cb test is ok!\n", __func__);
	} else {
		*btest_result = false;
		TS_LOG_ERR("%s: cb test is fail!\n", __func__);
	}

	return ret;

test_err:

	*btest_result = false;
	TS_LOG_ERR("%s: cb test is fail!\n", __func__);
	return ret;
}
/************************************************************************
* name: fts_open_test
* brief:
* input: none
* output: btest_result, pass or fail
* return: comm code. code = 0x00 is ok, else fail.
***********************************************************************/
unsigned char fts_open_test(
	bool *btest_result,
	struct fts_test_params *params)
{
	bool btmp_result = true;
	unsigned char ret = ERROR_CODE_OK;
	unsigned char chvalue = 0xff;
	int irow = 0;
	int icol = 0;
	int imax_value = 0;
	int imin_value = 0;
	unsigned char bclb_result = 0;
	int ix = params->scap_config.channel_x_num;
	int iy = params->scap_config.channel_y_num;

	TS_LOG_INFO("%s: open test\n", __func__);

	ret = fts_enter_factory();
	if (ERROR_CODE_OK != ret) {
			TS_LOG_INFO("%s: failed to enter factory mode\n",
				__func__);
			return ret;
	}

	/* set gip to connect vgh02/vgl02 (write 0x02 to register 0x20) */
	ret = fts_read_reg(REG_GIP_SWITCH, &chvalue);
	if (ERROR_CODE_OK != ret) {
			TS_LOG_ERR("%s: failed to read reg\n", __func__);
			return ret;
	}
	msleep(50);
	ret = fts_write_reg(REG_GIP_SWITCH, 0x02);
	if (ERROR_CODE_OK != ret) {
			TS_LOG_ERR("%s: failed to write reg\n", __func__);
			goto test_err;
	}

	/*auto clb */
	ret = fts_chip_clb(&bclb_result);
	if (ERROR_CODE_OK != ret) {
			TS_LOG_ERR("%s: failed to auto clb\n", __func__);
			goto test_err;
	}

	/* get cb data */
	ret = fts_get_cb_data(0, (short)(ix * iy +
		params->scap_config.key_num),
		params->uctmp_data);
	if (ERROR_CODE_OK != ret) {
			btmp_result = false;
			TS_LOG_ERR("failed to get cb value...");
			goto test_err;
	}

	memset(params->cbdata, 0, sizeof(params->cbdata));
	/* va area */
	for (irow = 0; irow < ix; ++irow) {
		for (icol = 0; icol < iy; ++icol) {
			params->cbdata[irow][icol] =
				params->uctmp_data[irow * iy + icol];
		}
	}

	/* show cbdata */
	TS_LOG_INFO("%s: show cb data\n", __func__);
	for (irow = 0; irow < ix; irow++) {
		TS_LOG_DEBUG("ch_%02d:\n", irow + 1);
		for (icol = 0; icol < iy; icol++)
			TS_LOG_DEBUG("%3d, ", params->cbdata[irow][icol]);
	}

	imin_value = params->threshold.open_test_cb_min;
	imax_value = MAX_CB_VALUE;
	for (irow = 0; irow < (ix + 1); irow++) {
		for (icol = 0; icol < iy; icol++) {
			if (irow >= ix && icol >= params->scap_config.key_num)
				continue;

			if (fts_abs(params->cbdata[irow][icol]) <
				imin_value ||
				fts_abs(params->cbdata[irow][icol]) >
				imax_value) {
				btmp_result = false;
				fts_print_raw_data("cb test failed", 
					irow + 1, icol + 1, 
					imax_value, imin_value, 
					params->cbdata[irow][icol]);
			}
		}
	}

test_err:
        /* reset reg */
	ret = fts_write_reg(REG_GIP_SWITCH, chvalue);
	msleep(50);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: failed to write reg\n", __func__); 
	}

	if (btmp_result) {
		*btest_result = true;
		TS_LOG_INFO("%s: open test is ok!\n", __func__);
	} else {
		*btest_result = false;
		TS_LOG_ERR("%s: open test is failed!\n", __func__);
	} 
	TS_LOG_ERR("%s: open test is failed!\n", __func__);
	return ret;
}

/************************************************************************
* name: fts_short_circuit_test
* brief:
* input: none
* output: btest_result, pass or fail
* return: comm code. code = 0x00 is ok, else fail.
***********************************************************************/
unsigned char fts_short_circuit_test(
	bool *btest_result,
	struct fts_test_params *params)
{
	bool btmp_result = true;
	unsigned char ret = ERROR_CODE_OK;
	int resmin = 0;
	int tmpadc = 0;
	int irow = 0;
	int icol = 0;

	int iall_adc_data_num = 0;
	unsigned char itx_num = 0, irx_num = 0, ichannel_num = 0;

	TS_LOG_INFO("%s: short circuit test start\n", __func__);

	ret = fts_enter_factory();
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: failed to enter factory mode\n", __func__);
		goto test_err;
	}

	ret = fts_read_reg(REG_TX_NUM, &itx_num);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: failed to read reg\n", __func__);
		goto test_err;
	}

	ret = fts_read_reg(REG_RX_NUM, &irx_num);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: failed to read reg\n", __func__);
		goto test_err;
	}

	ichannel_num = itx_num + irx_num;
	iall_adc_data_num = itx_num * irx_num
		+ params->scap_config.key_num_total;

	memset(params->adc_data, 0, sizeof(params->adc_data));

	ret = fts_weakshort_get_adc_data(
		iall_adc_data_num * 2,
		params->adc_data);
	msleep(50);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: failed to get adcdata\n", __func__);
		goto test_err;
	}

	resmin = params->threshold.short_circuit_test_res_min;
	for (irow = 0; irow < params->scap_config.channel_x_num; ++irow) {
		for (icol = 0; icol < params->scap_config.channel_y_num; 
			++icol) {
			tmpadc = params->adc_data[irow * irx_num + icol];
			if (MAX_ADC_NUM == tmpadc)
				tmpadc = MAX_ADC_NUM-1;
			params->itmp_data[irow][icol] = (tmpadc * 100) /
				(MAX_ADC_NUM - tmpadc);

			if (resmin > params->itmp_data[irow][icol])
				btmp_result = false;
		}
	}

	/* print adc and resistance data */
	TS_LOG_INFO("%s: adc data\n", __func__);
	for (irow = 0; irow < params->scap_config.channel_x_num; ++irow) {
		for (icol = 0; icol < params->scap_config.channel_y_num; 
			++icol) {
			TS_LOG_DEBUG("%d  ",
				params->adc_data[irow * irx_num + icol]);
		}
		TS_LOG_DEBUG("\n");
	}

	TS_LOG_INFO("%s: resistance data\n", __func__);
	for (irow = 0; irow < params->scap_config.channel_x_num; ++irow) {
		for (icol = 0; icol < params->scap_config.channel_y_num;
			++icol) {
			TS_LOG_DEBUG("%d  ", params->itmp_data[irow][icol]);
		}
		TS_LOG_DEBUG("\n");
	}

	if (btmp_result) {
		*btest_result = true;
		TS_LOG_INFO("%s: short circuit test is ok!\n", __func__);
	} else {
		*btest_result = false;
		TS_LOG_ERR("%s: short circuit test is ng!", __func__);
	}

	return ret;

test_err:

	*btest_result = false;
	TS_LOG_ERR("%s: short circuit test is ng!", __func__);
	return ret;
}

static unsigned char fts_weakshort_get_adc_data(
	int all_adc_data_len, int *prev_buff)
{
	unsigned char ret = ERROR_CODE_OK;
	unsigned short usreturn_num = 0;
	unsigned short ustotal_return_num = 0;
	int i = 1;
	int index = 0;
	unsigned char regmark = 0;
	int iread_num = all_adc_data_len / BYTES_PER_TIME;
	unsigned char wbuffer[2];
	int iread_data_len = all_adc_data_len;
	unsigned char *pread_buffer = NULL;
	bool badcok = false;
	int imax_scan_retry = 50;

	pread_buffer = kzalloc(iread_data_len + 1, GFP_KERNEL);
	if (pread_buffer == NULL)
		return ERROR_CODE_ALLOCATE_BUFFER_ERROR;
	memset(pread_buffer, 0, iread_data_len + 1);

	if ((all_adc_data_len % BYTES_PER_TIME) > 0)
		++iread_num;

	memset(wbuffer, 0, sizeof(wbuffer));
	wbuffer[0] = REG_ADC_DATA_ADDR;
	
	/* start adc sample */
	ret = fts_write_reg(REG_SCAN_ADC_SWITCH, 1);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("%s: write reg failed\n", __func__);
		goto end_get_adc;
	}

	for (index = 0; index < imax_scan_retry; ++index) {
		msleep(50);
		/* check if sample finish */
		ret = fts_read_reg(REG_SCAN_ADC_STATUS, &regmark);
		if (ret == ERROR_CODE_OK) {
			if (regmark == 0) {
				badcok = true;
				break;
			}
		}
	}

	if (!badcok) {
		TS_LOG_ERR("%s: adc data not ready\n", __func__);
		ret = ERROR_CODE_COMM_ERROR;
		goto end_get_adc;
	}

	ustotal_return_num = 0;

	usreturn_num = BYTES_PER_TIME;
	if (ret == ERROR_CODE_OK) {
		ret = fts_i2c_read(wbuffer, 1, 
			pread_buffer, usreturn_num);
	}

	for (i = 1; i < iread_num; i++) {
		if (ret != ERROR_CODE_OK) 
			break;

		if (i == iread_num - 1) {
			/* last packet */
			usreturn_num = all_adc_data_len - BYTES_PER_TIME * i;
			ret = fts_i2c_read(NULL, 0, 
				pread_buffer + BYTES_PER_TIME * i,
				usreturn_num);
		} else {
			usreturn_num = BYTES_PER_TIME;
			ret = fts_i2c_read(NULL, 0,
				pread_buffer + BYTES_PER_TIME * i,
				usreturn_num);
		}
	}

	for (index = 0; index < all_adc_data_len / 2; ++index) {
		prev_buff[index] = (pread_buffer[index * 2] << 8) +
			pread_buffer[index * 2 + 1];
	}
end_get_adc:
	if (pread_buffer != NULL) {
		kfree(pread_buffer);
		pread_buffer = NULL;
	}

	return ret;
}

void fts_get_test_result(
	char *result_buff,
	int *rawdata_buff,
	struct fts_test_params *params) 
{
	int i = 0;
	int irow = 0;
	int icol = 0;
	int average;
	int max_num, min_num;
	size_t num_elements = params->scap_config.channel_x_num
		* params->scap_config.channel_y_num;

	/* rawdata_test */
	if (code_rawdata_test == params->item_info[i].item_code) {
		if (RESULT_PASS == params->item_info[i].test_result) 
			strncat(result_buff, "0P-", MAX_RESULT_STR_LEN);
		else 
			strncat(result_buff, "0F-", MAX_RESULT_STR_LEN);

		if (num_elements < FTS_RAWDATA_BUFF_MAX) {
			for (irow = 0; irow < params->scap_config.channel_x_num;
				++irow) {
				for (icol = 0; icol < params
					->scap_config.channel_y_num; ++icol)
					rawdata_buff[2+irow 
					* params->scap_config.channel_y_num
					+ icol] = params->rawdata[irow][icol];
			}
			rawdata_buff[0] = params->scap_config.channel_x_num;
			rawdata_buff[1] = params->scap_config.channel_y_num;
		} else {
			TS_LOG_ERR("too many rawdata:%d.", (int)num_elements);
		}
	}
	i++;

	/* code_cb_test */
	if (code_cb_test == params->item_info[i].item_code) {
		if (RESULT_PASS == params->item_info[i].test_result)
			strncat(result_buff, "1P-", MAX_RESULT_STR_LEN);
		else
			strncat(result_buff, "1F-", MAX_RESULT_STR_LEN);

		if (num_elements < FTS_RAWDATA_BUFF_MAX) {
			for (irow = 0; irow < params->scap_config.channel_x_num;
				++irow) {
				for (icol = 0; icol < params
					->scap_config.channel_y_num; ++icol)
					rawdata_buff[num_elements+2+irow
					* params->scap_config.channel_y_num 
					+ icol] = params->cbdata[irow][icol];
			}
			rawdata_buff[0] = params->scap_config.channel_x_num;
			rawdata_buff[1] = params->scap_config.channel_y_num;
		} else {
			TS_LOG_ERR("too many cbdata:%d.", (int)num_elements);
		}
	}
	i++;

	/* code_weak_short_circuit_test */
	if (code_open_test == params->item_info[i].item_code) {
		if (RESULT_PASS == params->item_info[i].test_result)
			strncat(result_buff, "2P-", MAX_RESULT_STR_LEN);
		else
			strncat(result_buff, "2F-", MAX_RESULT_STR_LEN);
	}
	i++;

	/* code_weak_short_circuit_test */
	if (code_short_circuit_test == params->item_info[i].item_code) {
		if (RESULT_PASS == params->item_info[i].test_result)
			strncat(result_buff, "3P", MAX_RESULT_STR_LEN);
		else
			strncat(result_buff, "3F", MAX_RESULT_STR_LEN);
	}

	average = get_int_average(&rawdata_buff[2], num_elements);
	max_num = get_int_max(&rawdata_buff[2], num_elements);
	min_num = get_int_min(&rawdata_buff[2], num_elements);

	i = strlen(result_buff);
	if (i >= MAX_RESULT_STR_LEN) {
		TS_LOG_ERR("result string length out of range.");
		return;
	}
	snprintf((result_buff+i), MAX_RESULT_STR_LEN-i,
		"[%4d,%4d,%4d]",
		average,
		max_num,
		min_num);

	average =
		get_int_average(&rawdata_buff[2 + num_elements], num_elements);
	max_num =
		get_int_max(&rawdata_buff[2+num_elements], num_elements);
	min_num =
		get_int_min(&rawdata_buff[2+num_elements], num_elements);

	i = strlen(result_buff);
	if (i >= MAX_RESULT_STR_LEN) {
		TS_LOG_ERR("result string length out of range.");
		return;
	}
	snprintf((result_buff+i), MAX_RESULT_STR_LEN-i,
		"[%4d,%4d,%4d]",
		average,
		max_num,
		min_num);

	i = strlen(result_buff);
	if (i >= MAX_RESULT_STR_LEN) {
		TS_LOG_ERR("result string length out of range.");
		return;
	}
	snprintf((result_buff+i), MAX_RESULT_STR_LEN-i,
		"-%s", "ft8716");

	return;
}


/************************************************************************
* Name: fts_get_diff_data_for_debug
* Brief:  Get Raw Data of VA area and Key area
* Input: none
* Output: none
* Return: Comm Code. Code = 0x00 is OK, else fail.
***********************************************************************/
unsigned char fts_get_diff_data_for_debug(
	int *buff, int is_differ, 
	struct fts_test_params *params)
{
	int ret = ERROR_CODE_OK;
	int irow, icol;
	int i = 0;
	int iscan_retry = 6;

	/* Enter Factory Mode */
	ret = fts_enter_factory();
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("Failed to Enter Factory Mode...");
		fts_enter_work_model_from_factory();
		return ret;
	}

	/* Check Num of Channel */
	if (0 == (params->scap_config.channel_x_num +
		params->scap_config.channel_y_num)) {
		ret = fts_get_channel_num(params);
		if (ERROR_CODE_OK != ret) {
			TS_LOG_ERR("Error Channel Num...");
			fts_enter_work_model_from_factory();
			return ERROR_CODE_INVALID_PARAM;
		}
	}

	if (is_differ)
		fts_write_reg(REG_IS_DIFF_SWITCH, 1);
	else
		fts_write_reg(REG_IS_DIFF_SWITCH, 0);
	
	/* Start Scanning */
	for (i = 0; i < iscan_retry; i++) {
		ret = fts_start_scan();
		if (ERROR_CODE_OK == ret)
			break;
		else
			msleep(10);
	}
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("Failed to Scan ...");
		fts_enter_work_model_from_factory();
		return ret;
	}

	/* Read RawData for Channel Area */
	memset(params->rawdata, 0, sizeof(params->rawdata));
	memset(params->tmp_rawdata, 0, sizeof(params->tmp_rawdata));
	ret = fts_read_raw_data(0, DATA_TYPE_RAWDATA,
		params->scap_config.channel_x_num
		* params->scap_config.channel_y_num * 2,
		params->tmp_rawdata);
	if (ERROR_CODE_OK != ret) {
		TS_LOG_ERR("Failed to Get RawData");
		fts_enter_work_model_from_factory();
		return ret;
	}

	for (irow = 0; irow < params->scap_config.channel_x_num; ++irow) {
		for (icol = 0; icol < params->scap_config.channel_y_num;
		++icol) {
			if (is_differ)
				params->rawdata[irow][icol] =
				(short)(unsigned short)params
				->tmp_rawdata[irow * params
				->scap_config.channel_y_num + icol];
			else
				params->rawdata[irow][icol] = 
				params->tmp_rawdata[irow * params
				->scap_config.channel_y_num + icol];

			buff[2+irow * params->scap_config.channel_y_num + icol]
				= params->rawdata[irow][icol];
		}
	}
	buff[0] = params->scap_config.channel_x_num;
	buff[1] = params->scap_config.channel_y_num;

	fts_write_reg(REG_IS_DIFF_SWITCH, 0);
	fts_enter_work_model_from_factory();

	return ret;

}

/*
 * Name: fts_set_param_data
 * Brief:  load Config. Set IC series, init test items, init basic threshold, 
 *			int detailThreshold, and set order of test items
 * Input: TestParamData, from ini file.
 * Output: none
 * Return: 0. No sense, just according to the old format.
 */
int fts_set_param_data(struct fts_ts_platform_data *fts_pdata, struct fts_test_params *params)
{
	int ret = 0;

	TS_LOG_INFO("%s: set param data called\n", __func__);

	fts_set_max_channel_num(params);

	ret = fts_init_capacitance_test_data(fts_pdata, params);
	if (ret < 0) {
		TS_LOG_ERR("%s: analysis tp test data failed\n", __func__);
		return -1;
	}

	fts_set_test_item(params);

	TS_LOG_INFO("%s: set param data success item_num = %d.", __func__,
		params->item_num);

	return 0;
}

int fts_get_raw_data(
	struct ts_rawdata_info *info,
	struct ts_cmd_node *out_cmd)
{
	int ret = 0;
	struct fts_test_params *params = NULL;
        
	TS_LOG_INFO("fts get rawdata called\n");

	params = kzalloc(sizeof(struct fts_test_params), GFP_KERNEL);
	if (NULL == params) {
		TS_LOG_ERR(" allocate fts_test_params memory failure");
		goto err;
	}

        memset(params, 0, sizeof(struct fts_test_params));

        /* 2. get test data from dts */
        ret = fts_set_param_data(fts_platform_data, params);
        if (ret < 0) {
        	TS_LOG_ERR("get testparam from dts failure");
		goto err;    
        }

        /* 3. get info factory mode for cap test */
        ret = fts_enter_factory();
        if (ret) {
            TS_LOG_ERR("%s: failed to enter factory mode\n", __func__);
            return ret;
        }

        /* 4. get TX and RX data */
        ret = fts_get_channel_form_ic(params);
        if (ret) {
            TS_LOG_ERR("%s: get channel num failed\n", __func__);
            return ret;
        }

        /* 5. start test */
	if (true == fts_start_test_tp(params)) 
                TS_LOG_INFO("%s: tp test pass\n", __func__);
	else 
                TS_LOG_ERR("%s: tp test failure\n", __func__);

        /* 6. cat test over get info work mode*/
        ret = fts_enter_work_model_from_factory();
        if (ret < 0) {
        	TS_LOG_ERR("%s: change work mode failed\n", __func__);
		goto err;    
        }

        /* 7. print test result */
	fts_get_test_result(info->result, info->buff, params);

	info->used_size = info->buff[0]*info->buff[1]*2;

	if (NULL != params) {
                vfree(params);
		params = NULL;
	}

	return NO_ERR;

err:
	if (NULL != params) vfree(params);
	return -EIO;
}


