#ifndef _FOCALTECH_TEST_H_
#define _FOCALTECH_TEST_H_

#include <linux/kernel.h>

#define bool unsigned char
#define BYTE unsigned char
#define false 0
#define true  1
#define TX_NUM_MAX			30
#define RX_NUM_MAX			30
#define MAX_PATH			256
#define MAX_TEST_ITEM			20
#define FTS_IC_MODE_ADDR	0x00
#define DEVICE_MODE_WORK	0x00
#define DEVICE_MODE_FACTORY	0x40

/*-----------------------------------------------------------
error code for comm
-----------------------------------------------------------*/
#define ERROR_CODE_OK						0x00
#define ERROR_CODE_CHECKSUM_ERROR				0x01
#define ERROR_CODE_INVALID_COMMAND				0x02
#define ERROR_CODE_INVALID_PARAM				0x03
#define ERROR_CODE_IIC_WRITE_ERROR				0x04
#define ERROR_CODE_IIC_READ_ERROR				0x05
#define ERROR_CODE_WRITE_USB_ERROR				0x06
#define ERROR_CODE_WAIT_RESPONSE_TIMEOUT			0x07
#define ERROR_CODE_PACKET_RE_ERROR				0x08
#define ERROR_CODE_NO_DEVICE					0x09
#define ERROR_CODE_WAIT_WRITE_TIMEOUT				0x0a
#define ERROR_CODE_READ_USB_ERROR				0x0b
#define ERROR_CODE_COMM_ERROR					0x0c
#define ERROR_CODE_ALLOCATE_BUFFER_ERROR			0x0d
#define ERROR_CODE_DEVICE_OPENED				0x0e
#define ERROR_CODE_DEVICE_CLOSED				0x0f

/*-----------------------------------------------------------
test status
-----------------------------------------------------------*/
#define		RESULT_NULL			0
#define		RESULT_PASS			1
#define		RESULT_NG				2
#define		RESULT_TESTING			3
#define		RESULT_TBD			4
#define		RESULT_REPLACE			5
#define		RESULT_CONNECTING		6

/*-----------------------------------------------------------
read write max bytes per time
-----------------------------------------------------------*/
#define BYTES_PER_TIME				128
#define MAX_IC_NAME_LENGTH				20
#define MAX_RETRY_TIMES					3
#define FTS_PROJECT_ID_FW_LEN				9

enum normalize_type {
	overall_normalize = 0,
	auto_normalize = 1,
};

enum proof_type {
	/* mode 0 */
	proof_normal,
	/* mode 1 */
	proof_level0,
	/* mode 2 */
	proof_nowaterproof,
};



struct test_item_switch {
	bool channel_num_test;
	bool rawdata_test;	
	bool cb_test;
	bool short_test;
	bool open_test;
};
struct basic_threshold {
	unsigned char channel_num_test_channel_x;
	unsigned char channel_num_test_channel_y;
	unsigned char channel_num_test_key_num;

	int rawdata_test_min;
	int rawdata_test_max;
	
	bool cb_test_va_check;
	int cb_test_min;
	int cb_test_max;
	bool cb_test_vkey_check;
	int cb_test_min_vkey;
	int cb_test_max_vkey;

	int short_circuit_test_res_min;

	int open_test_cb_min;
	bool open_test_check_k1;
	int open_test_k1_threshold;
	bool open_test_check_k2;
	int open_test_k2_threshold;
};

enum testitem_code {
	code_enter_factory_mode, 
	code_rawdata_test,
	code_channel_num_test,
	code_cb_test, 
	code_short_circuit_test,
	code_open_test,
};

struct test_item_info {
	unsigned char item_type;
	unsigned char test_num;
	unsigned char test_result;
	unsigned char item_code;
};

struct scap_config {
	int iused_max_tx_num; 
	int iused_max_rx_num;
	unsigned char channel_x_num;
	unsigned char channel_y_num;
	unsigned char key_num;
	unsigned char key_num_total;
	bool bleft_key1;
	bool bleft_key2;
	bool bleft_key3;
	bool bright_key1;
	bool bright_key2;
	bool bright_key3;
};

struct fts_test_params {
	struct test_item_switch item_switchs;
	struct basic_threshold threshold;
	struct test_item_info item_info[MAX_TEST_ITEM];
	struct scap_config scap_config;
	int item_num; 

	int rawdata[TX_NUM_MAX][RX_NUM_MAX];
	int cbdata[TX_NUM_MAX][RX_NUM_MAX];
	int itmp_data[TX_NUM_MAX][RX_NUM_MAX];
	unsigned char uctmp_data[TX_NUM_MAX * RX_NUM_MAX*2];
	int tmp_rawdata[TX_NUM_MAX * RX_NUM_MAX];
	int adc_data[TX_NUM_MAX * RX_NUM_MAX];
};

void fts_set_max_channel_num(struct fts_test_params *params);
void fts_set_test_item(struct fts_test_params *params);
bool fts_start_test_tp(struct fts_test_params *params);
unsigned char fts_raw_data_test(struct fts_test_params *params,
	bool *test_result);
unsigned char fts_get_channel_form_ic(struct fts_test_params *params);
unsigned char fts_cb_test(bool *test_result,
	struct fts_test_params *params);
unsigned char fts_open_test(bool *test_result,
	struct fts_test_params *params);
unsigned char fts_short_circuit_test(bool *test_result,
	struct fts_test_params *params);
unsigned char fts_get_diff_data_for_debug(int *buff,
	int is_differ, struct fts_test_params *params);
void fts_get_test_result(char *result_buff,
	int *rawdata_buff, struct fts_test_params *params);
unsigned char fts_enter_work_model_from_factory(void);
unsigned char fts_enter_factory(void);

int fts_abs(int value);

int fts_get_raw_data(struct ts_rawdata_info *info, struct ts_cmd_node *out_cmd);

#endif /* _FOCALTECH_TEST_H_ */
