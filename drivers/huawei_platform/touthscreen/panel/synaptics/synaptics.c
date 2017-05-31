#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/interrupt.h>
#include <linux/completion.h>
#include "synaptics.h"
#include <../../huawei_touchscreen_chips.h>
#include <linux/regulator/consumer.h>
#include <huawei_platform/log/log_jank.h>
#include "../../huawei_touchscreen_algo.h"
#if defined (CONFIG_HUAWEI_DSM)
#include <dsm/dsm_pub.h>
#endif
#if defined (CONFIG_TEE_TUI)
#include "tui.h"
#endif

#define SYNAPTICS_CHIP_INFO "synaptics-"
#define FRD_JDI_11081	"FRD_11081"
#define FRD_JDI_11081_LEN	9
#define FRD_JDI_11080	"FRD_11080"
#define EASY_WAKEUP_FASTRATE 0x011D
#define F54_ANALOG_CMD0  0x016F
#define PALM_REG_BIT 0x01

#define LOCUS_DATA_NUM 24
#define LOCUS_DATA_LENS 4
#define LETTER_LOCUS_NUM 6
#define LINEAR2_LOCUS_NUM 4
#define LINEAR_LOCUS_NUM 2

/*#define GESTURE_FROM_APP(_x) (_x)*/
/*#define F51_CUSTOM_DATA24_OFFSET 24*/
#define F11_2D_DATA38_OFFSET 54
#define F11_2D_DATA39_OFFSET 55
#define F12_2D_CTRL_LEN 14
#define F12_RX_NUM_OFFSET 12
#define F12_TX_NUM_OFFSET 13

/*Gesture register(F11_2D_data38) value*/
#define DOUBLE_CLICK_WAKEUP  (1<<0)
#define LINEAR_SLIDE_DETECTED  (1<<1)
#define CIRCLE_SLIDE_DETECTED  (1<<3)
#define SPECIFIC_LETTER_DETECTED  (1<<6)
#define DOUBLE_CLICK_S3320_NO 0x03
#define LINEAR_SLIDE_S3320_NO 0x07
#define SPECIFIC_LETTER_S3320_NO 0x0b

/*Linear esture register(F51_custom_data0) value*/
#define LINEAR_SLIDE_LEFT_TO_RIGHT 0X01
#define LINEAR_SLIDE_RIGHT_TO_LEFT 0X02
#define LINEAR_SLIDE_TOP_TO_BOTTOM 0X04
#define LINEAR_SLIDE_BOTTOM_TO_TOP 0X08
#define LINEAR_SLIDE_TOP_TO_BOTTOM2 0X80

/*Letter gesture register(F11_2D_DATA39 (04)/01) value*/
#define SPECIFIC_LETTER_c 0x63
#define SPECIFIC_LETTER_e 0x65
#define SPECIFIC_LETTER_m 0x6D
#define SPECIFIC_LETTER_w 0x77

/*F51 no standard account offset ,so this register must be modified following firmware++++++*/
/*#define PEN_SWITCH_OFFSET  4*/
#define S3350_HOLSTER_SWITCH_OFFSET    10
#define S3320_HOLSTER_SWITCH_OFFSET    3
#define S3350_F51_TOUCHPLUS_OFFSET         0x0E
#define S3320_F51_TOUCHPLUS_OFFSET         0x1B
#define TOUCHPLUS_DOWNUP_BIT04         0x10
#define PRODUCT_ID_FW_LEN 5
#define PROJECT_ID_FW_LEN 9
#define S3320_HOLSTER_FORCE_GLOVE_OFFSET 0x19
#define S3320_HOLSTER_WINDOW_REG_BYTES 8
#define S3320_F51_CUSTOM_CTRL19_OFFSET 15
#define S3320_F51_CUSTOM_CTRL15_OFFSET 11
#define S3320_F54_CMD_BASE_ADDR 0x015C

#ifndef SYNA_UPP
#define SYNA_UPP
#endif

#define USE_F12_DATA_15

/* This workaround comes from official driver project of synaptics.
   See https://github.com/SynapticsHostSoftware/synaptics_dsx_public. */
#ifdef USE_F12_DATA_15
#define F12_DATA_15_WORKAROUND
#endif

#ifdef ROI
static bool f51found;
static u8 f51_roi_switch;
static u8 pre_finger_status;
static u8 roi_data_staled;
static struct completion roi_data_done;
static unsigned char roi_data[ROI_DATA_READ_LENGTH] = { 0 };
#endif

#if defined (CONFIG_TEE_TUI)
static struct synaptics_tui_data {
	char device_name[10];
} synaptics_tui_data;
#endif

#define IS_APP_ENABLE_GESTURE(x)  ((u32)(1<<x))
static struct mutex wrong_touch_lock;
char raw_data_limit_flag;
static DEFINE_MUTEX(ts_power_gpio_sem);
static int ts_power_gpio_ref = 1;
static unsigned char config_id_string[CHIP_INFO_LENGTH] = { 0 };
#ifdef SYNA_UPP
extern int fwu_read_f34_queries(void);
#endif

extern int synaptics_debug_data_test(struct ts_diff_data_info *info);
extern int synaptics_fw_s3718_configid(struct synaptics_rmi4_data *rmi4_data,
				 u8 *buf,
				 size_t buf_size);
#ifdef SYNA_UPP
extern unsigned short get_oem_data_info( void );
extern int get_oem_data(unsigned char *oem_data, unsigned short leng);
extern int set_oem_data(unsigned char *oem_data, unsigned short leng);
#endif

static int synaptics_chip_detect(struct device_node *device,
				 struct ts_device_data *chip_data,
				 struct platform_device *ts_dev);
static int synaptics_wrong_touch(void);
static int synaptics_init_chip(void);
static int synaptics_get_brightness_info(void);

static int synaptics_parse_dts(struct device_node *device,
			       struct ts_device_data *chip_data);
static int synaptics_irq_top_half(struct ts_cmd_node *cmd);
static int synaptics_irq_bottom_half(struct ts_cmd_node *in_cmd,
				     struct ts_cmd_node *out_cmd);
static int synaptics_fw_update_boot(char *file_name);
static int synaptics_fw_update_sd(void);
static int synaptics_oem_info_switch(struct ts_oem_info_param *info);
static int synaptics_chip_get_info(struct ts_chip_info_param *info);
static int synaptics_set_info_flag(struct ts_data *info);
static int synaptics_before_suspend(void);
static int synaptics_suspend(void);
static int synaptics_resume(void);
static int synaptics_after_resume(void *feature_info);
static int synaptics_wakeup_gesture_enable_switch(struct
						  ts_wakeup_gesture_enable_info
						  *info);
static void synaptics_shutdown(void);
static int synaptics_input_config(struct input_dev *input_dev);
static int synaptics_reset_device(void);
static int synaptics_rmi4_reset_device(struct synaptics_rmi4_data *rmi4_data);
static int synaptics_rmi4_status_resume(struct synaptics_rmi4_data *rmi4_data);
static int synaptics_rmi4_status_save(struct synaptics_rmi4_data *rmi4_data);
static void synaptics_rmi4_empty_fn_list(struct synaptics_rmi4_data *rmi4_data);
static void synaptics_rmi4_f1a_kfree(struct synaptics_rmi4_fn *fhandler);
static int synaptics_get_debug_data(struct ts_rawdata_info *info,
				    struct ts_cmd_node *out_cmd);
static int synaptics_get_rawdata(struct ts_rawdata_info *info,
				 struct ts_cmd_node *out_cmd);
static int synaptics_get_calibration_data(struct ts_calibration_data_info *info,
		struct ts_cmd_node *out_cmd);
static int synaptics_get_calibration_info(struct ts_calibration_info_param *info,
		struct ts_cmd_node *out_cmd);
static int synaptics_palm_switch(struct ts_palm_info *info);
static int synaptics_glove_switch(struct ts_glove_info *info);
static int synaptics_get_glove_switch(u8 *glove_switch);
static int synaptics_set_glove_switch(u8 glove_switch);
static int synaptics_charger_switch(struct ts_charger_info *info);
static int synaptics_holster_switch(struct ts_holster_info *info);
static int synaptics_roi_switch(struct ts_roi_info *info);
static unsigned char *synaptics_roi_rawdata(void);
static int synaptics_chip_get_capacitance_test_type(struct ts_test_type_info
						    *info);
static int synaptics_calibrate(void);
static int synaptics_calibrate_wakeup_gesture(void);
#if defined (CONFIG_HUAWEI_DSM)
static int synaptics_rmi4_dsm_debug(void);
#endif
static int synaptics_regs_operate(struct ts_regs_info *info);
static void synaptics_rmi4_report_touch(struct synaptics_rmi4_data *rmi4_data,
					struct synaptics_rmi4_fn *fhandler,
					struct ts_fingers *info);

extern int hisifb_esd_recover_disable(int value);
static int g_report_err_log_count = 0;

/* The following is a stub function. For hisilicon platform, it will be redefined in sensorhub module.
For qualcomm platform, it has not been implemented. Thus the stub function can avoid compilation errors.*/

__attribute__((weak)) void preread_fingersense_data(void)
{
    return;
}

#define GLOVE_SWITCH_ADDR 0x0400

#define GESTURE_ENABLE_BIT01 0x02

#define REPORT_2D_W

#define RPT_TYPE (1 << 0)
#define RPT_X_LSB (1 << 1)
#define RPT_X_MSB (1 << 2)
#define RPT_Y_LSB (1 << 3)
#define RPT_Y_MSB (1 << 4)
#define RPT_Z (1 << 5)
#define RPT_WX (1 << 6)
#define RPT_WY (1 << 7)
#define RPT_DEFAULT (RPT_TYPE | RPT_X_LSB | RPT_X_MSB | RPT_Y_LSB | RPT_Y_MSB)

#define MAX_ABS_MT_TOUCH_MAJOR 15

#define F01_STD_QUERY_LEN 21
#define F01_BUID_ID_OFFSET 18
#define F11_STD_QUERY_LEN 9
#define F11_STD_CTRL_LEN 10
#define F11_STD_DATA_LEN 12
/*dts*/
#define SYNAPTCS_IRQ_GPIO "attn_gpio"
#define SYNAPTCS_RST_GPIO "reset_gpio"
#define SYNAPTICS_VDDIO_GPIO_CTRL "vddio_ctrl_gpio"
#define SYNAPTICS_VCI_GPIO_CTRL "vci_ctrl_gpio"
#define SYNAPTCS_IRQ_CFG "irq_config"
#define SYNAPTICS_ALGO_ID "algo_id"
#define SYNAPTICS_VDD	 "synaptics-vdd"
#define SYNAPTICS_VBUS	 "synaptics-io"
#define SYNAPTICS_IC_TYPES	 "ic_type"
#define SYNAPTICS_WD_CHECK	"need_wd_check_status"
#define SYNAPTICS_X_MAX	 "x_max"
#define SYNAPTICS_Y_MAX	 "y_max"
#define SYNAPTICS_X_MAX_MT	 "x_max_mt"
#define SYNAPTICS_Y_MAX_MT	 "y_max_mt"
#define SYNAPTICS_UNIT_CAP_TEST_INTERFACE "unite_cap_test_interface"
#define SYNAPTICS_REPORT_RATE_TEST "report_rate_test"
#define SYNAPTICS_VCI_GPIO_TYPE	 "vci_gpio_type"
#define SYNAPTICS_VCI_REGULATOR_TYPE	 "vci_regulator_type"
#define SYNAPTICS_VDDIO_GPIO_TYPE	 "vddio_gpio_type"
#define SYNAPTICS_PROJECTID_LEN	 "projectid_len"
#define SYNAPTICS_VDDIO_REGULATOR_TYPE	 "vddio_regulator_type"
#define SYNAPTICS_COVER_FORCE_GLOVE     "force_glove_in_smart_cover"
#define SYNAPTICS_TEST_TYPE	 "tp_test_type"
#define SYNAPTICS_HOSTLER_SWITCH_ADDR "holster_switch_addr"
#define SYNAPTICS_HOSTLER_SWITCH_BIT "holster_switch_bit"
#define SYNAPTICS_GLOVE_SWITCH_ADDR "glove_switch_addr"
#define SYNAPTICS_GLOVE_SWITCH_BIT "glove_switch_bit"

#define SYNAPTICS_VCI_LDO_VALUE "vci_value"
#define SYNAPTICS_VDDIO_LDO_VALUE "vddio_value"
#define SYNAPTICS_NEED_SET_VDDIO_VALUE "need_set_vddio_value"

#define SYNAPTICS_FW_UPDATE_LOGIC "fw_update_logic"
#define TEST_ENHANCE_RAW_DATA_CAPACITANCE "test_enhance_raw_data_capacitance"
#define SHOULD_CHECK_TP_CALIBRATION_INFO "should_check_tp_calibration_info"

#define SYNAPTICS_MAX_REGDATA_NUM 32
static char synaptics_reg_status[SYNAPTICS_MAX_REGDATA_NUM] = { 0 };

#define S3718_IC_NAME	 "S3718"
#define S3718_IC_NAME_SIZE	 5

enum TP_register_type {
	SYNA_REG_CTRL = 0,
	SYNA_REG_DATA = 1,
	SYNA_REG_QUERY = 2,
};

enum device_status {
	STATUS_NO_ERROR = 0x00,
	STATUS_RESET_OCCURRED = 0x01,
	STATUS_INVALID_CONFIG = 0x02,
	STATUS_DEVICE_FAILURE = 0x03,
	STATUS_CONFIG_CRC_FAILURE = 0x04,
	STATUS_FIRMWARE_CRC_FAILURE = 0x05,
	STATUS_CRC_IN_PROGRESS = 0x06
};

struct synaptics_work_reg_status {
	unsigned char fhandler_ctrl_base;
	unsigned char offset;
	unsigned char length;
};

static struct synaptics_work_reg_status dsm_dump_register_map[] = {
	/* read tp status whether in easy_wake up mode or power_off mode */
	[0] = {
	       .fhandler_ctrl_base = 0,
	       .offset = 0,
	       .length = 4,
	       },
	[1] = {
	       .fhandler_ctrl_base = 0,
	       .offset = 0,
	       .length = 1,
	       },
};

struct synaptics_rmi4_f54_query {
	union {
		struct {
			/* query 0 */
			unsigned char num_of_rx_electrodes;
			/* query 1 */
			unsigned char num_of_tx_electrodes;
			/* query 2 */
			unsigned char f54_query2_b0__1:2;
			unsigned char has_baseline:1;
			unsigned char has_image8:1;
			unsigned char f54_query2_b4__5:2;
			unsigned char has_image16:1;
			unsigned char f54_query2_b7:1;
			/* queries 3.0 and 3.1 */
			unsigned short clock_rate;
			/* query 4 */
			unsigned char touch_controller_family;
			/* query 5 */
			unsigned char has_pixel_touch_threshold_adjustment:1;
			unsigned char f54_query5_b1__7:7;
			/* query 6 */
			unsigned char has_sensor_assignment:1;
			unsigned char has_interference_metric:1;
			unsigned char has_sense_frequency_control:1;
			unsigned char has_firmware_noise_mitigation:1;
			unsigned char has_ctrl11:1;
			unsigned char has_two_byte_report_rate:1;
			unsigned char has_one_byte_report_rate:1;
			unsigned char has_relaxation_control:1;
		} __packed;
		unsigned char data[8];
	};
};

struct synaptics_rmi4_f1a_query {
	union {
		struct {
			unsigned char max_button_count:3;
			unsigned char reserved:5;
			unsigned char has_general_control:1;
			unsigned char has_interrupt_enable:1;
			unsigned char has_multibutton_select:1;
			unsigned char has_tx_rx_map:1;
			unsigned char has_perbutton_threshold:1;
			unsigned char has_release_threshold:1;
			unsigned char has_strongestbtn_hysteresis:1;
			unsigned char has_filter_strength:1;
		} __packed;
		unsigned char data[2];
	};
};

struct synaptics_rmi4_f1a_control_0 {
	union {
		struct {
			unsigned char multibutton_report:2;
			unsigned char filter_mode:2;
			unsigned char reserved:4;
		} __packed;
		unsigned char data[1];
	};
};

struct synaptics_rmi4_f1a_control {
	struct synaptics_rmi4_f1a_control_0 general_control;
	unsigned char *button_int_enable;
	unsigned char *multi_button;
	struct synaptics_rmi4_f1a_control_3_4 *electrode_map;
	unsigned char *button_threshold;
	unsigned char button_release_threshold;
	unsigned char strongest_button_hysteresis;
	unsigned char filter_strength;
};

struct synaptics_rmi4_f1a_handle {
	int button_bitmask_size;
	unsigned char button_count;
	unsigned char valid_button_count;
	unsigned char *button_data_buffer;
	unsigned char *button_map;
	struct synaptics_rmi4_f1a_query button_query;
	struct synaptics_rmi4_f1a_control button_control;
};
static struct synaptics_rmi4_data *rmi4_data;

#if defined (CONFIG_HUAWEI_DSM)
extern struct dsm_client *tp_dclient;
#endif
extern struct ts_data g_ts_data;
/* when add/remove support TP module need to modify here */

static struct touch_settings synaptics_sett_param_regs_map[] = {
	/*ic_type = 0-S3207, 1 = S3350, 2 = S3320, 3 = S3718 */
	[0] = {
	       .build_id[0] = '0',
	       .build_id[1] = '0',
	       .build_id[2] = '0',
	       .module_name = "oflim",
	       .ic_type = 0,
	       },
	[1] = {
	       .build_id[0] = '0',
	       .build_id[1] = '0',
	       .build_id[2] = '2',
	       /*.id = TRULY,*/
	       .module_name = "truly",
	       .ic_type = 0,
	       },
	[2] = {
	       .build_id[0] = '0',
	       .build_id[1] = '0',
	       .build_id[2] = '4',
	       /*.id = TRULY,*/
	       .module_name = "GIS",
	       .ic_type = 0,
	       },
	[3] = {
	       .build_id[0] = '0',
	       .build_id[1] = '0',
	       .build_id[2] = '7',
	       /*.id = TRULY,*/
	       .module_name = "YASSY",
	       .ic_type = 0,
	       },
	[4] = {
	       .build_id[0] = '0',
	       .build_id[1] = '0',
	       .build_id[2] = '6',
	       .module_name = "lensone",
	       .ic_type = 0,
	       },
	[5] = {
	       .build_id[0] = '0',
	       .build_id[1] = '1',
	       .build_id[2] = '0',
	       /*.id = 0xff,*/
	       .module_name = "jdi",
	       .ic_type = 1,
	       },
	[6] = {
	       .build_id[0] = '0',
	       .build_id[1] = '0',
	       .build_id[2] = '0',
	       /*.id = 0xff,*/
	       .module_name = "jdi",
	       .ic_type = 2,
	       },
	[7] = {
	       .build_id[0] = '3',
	       .build_id[1] = '2',
	       .build_id[2] = 'U',
	       .ic_name[0] = '1',
	       .ic_name[1] = '7',
	       /*.id = 0xff,*/
	       .module_name = "lg",
	       .ic_type = 3,
	       },
	[8] = {
	       .build_id[0] = '1',
	       .build_id[1] = '1',
	       .build_id[2] = '1',
	       /*.id = 0xff,*/
	       .module_name = "null",
	       },
	[9] = {
	       .build_id[0] = '0',
	       .build_id[1] = '9',
	       .build_id[2] = '0',
	       .ic_name[0] = '1',
	       .ic_name[1] = '7',
	       /*.id = 0xff,*/
	       .module_name = "samsung",
	       .ic_type = 3,
	       },
};

static struct touch_settings *synaptics_sett_param_regs =
    &synaptics_sett_param_regs_map[10];
static int synaptics_interrupt_num;

static void synaptics_gpio_reset(void);
static void synaptics_power_on(void);
static void synatpics_regulator_enable(void);
static void synaptics_power_on_gpio_set(void);
static void synaptics_power_off(void);
static void synatpics_regulator_disable(void);
static void synaptics_power_off_gpio_set(void);
static bool synaptics_rmi4_crc_in_progress(struct synaptics_rmi4_data
					   *rmi4_data,
					   struct
					   synaptics_rmi4_f01_device_status
					   *status);
static int synaptics_rmi4_set_page(struct synaptics_rmi4_data *rmi4_data,
				   unsigned int address);
static struct synaptics_rmi4_fn *synaptics_rmi4_alloc_fh(struct
							 synaptics_rmi4_fn_desc
							 *rmi_fd,
							 int page_number);
static int synaptics_rmi4_query_device_info(struct synaptics_rmi4_data
					    *rmi4_data);
static int synaptics_rmi4_query_device(struct synaptics_rmi4_data *rmi4_data);
static int synaptics_rmi4_f11_init(struct synaptics_rmi4_data *rmi4_data,
				   struct synaptics_rmi4_fn *fhandler,
				   struct synaptics_rmi4_fn_desc *fd,
				   unsigned int intr_count);
static int synaptics_rmi4_f12_init(struct synaptics_rmi4_data *rmi4_data,
				   struct synaptics_rmi4_fn *fhandler,
				   struct synaptics_rmi4_fn_desc *fd,
				   unsigned int intr_count);
static int synaptics_rmi4_f1a_init(struct synaptics_rmi4_data *rmi4_data,
				   struct synaptics_rmi4_fn *fhandler,
				   struct synaptics_rmi4_fn_desc *fd,
				   unsigned int intr_count);
static int synaptics_rmi4_f51_init(struct synaptics_rmi4_data *rmi4_data,
				   struct synaptics_rmi4_fn *fhandler,
				   struct synaptics_rmi4_fn_desc *fd,
				   unsigned int intr_count, unsigned char page);
static int synaptics_rmi4_i2c_read(struct synaptics_rmi4_data *rmi4_data,
				   unsigned short addr, unsigned char *data,
				   unsigned short length);
static int synaptics_rmi4_i2c_write(struct synaptics_rmi4_data *rmi4_data,
				    unsigned short addr, unsigned char *data,
				    unsigned short length);
static int synaptics_rmi4_sensor_report(struct synaptics_rmi4_data *rmi4_data,
					struct ts_fingers *info);

/*******************************************************************************
** TP VCC
* TP VCC/VDD  power control by GPIO in V8Rx,
* if controled by ldo in other products, open "return -EINVAL"
rmi4_data->tp_vci is 3.1V ,rmi4_data->tp_vddio is 1.8V
*/
static int synaptics_regulator_get(void)
{
	if (g_ts_data.fpga_flag == 1)
		return 0;

	if (1 == rmi4_data->synaptics_chip_data->vci_regulator_type) {
		rmi4_data->tp_vci =
		    regulator_get(&rmi4_data->synaptics_dev->dev,
				  SYNAPTICS_VDD);
		if (IS_ERR(rmi4_data->tp_vci)) {
			TS_LOG_ERR("regulator tp vci not used\n");
			return -EINVAL;
		}
	}

	if (1 == rmi4_data->synaptics_chip_data->vddio_regulator_type) {
		rmi4_data->tp_vddio =
		    regulator_get(&rmi4_data->synaptics_dev->dev,
				  SYNAPTICS_VBUS);
		if (IS_ERR(rmi4_data->tp_vddio)) {
			TS_LOG_ERR("regulator tp vddio not used\n");
			regulator_put(rmi4_data->tp_vci);
			return -EINVAL;
		}
	}

	return 0;
}

static void synaptics_regulator_put(void)
{
	if (g_ts_data.fpga_flag == 1)
		return;

	if (1 == rmi4_data->synaptics_chip_data->vci_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vci)) {
			regulator_put(rmi4_data->tp_vci);
		}
	}
	if (1 == rmi4_data->synaptics_chip_data->vddio_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vddio)) {
			regulator_put(rmi4_data->tp_vddio);
		}
	}
}

static int synaptics_vci_enable(void)
{
	int retval;
	int vol_vlaue;

	if (g_ts_data.fpga_flag == 1)
		return 0 ;

	if (IS_ERR(rmi4_data->tp_vci)) {
		TS_LOG_ERR("tp_vci is err\n");
		return -EINVAL;
	}

	vol_vlaue = rmi4_data->synaptics_chip_data->regulator_ctr.vci_value;
	if (!IS_ERR(rmi4_data->tp_vci)) {
		TS_LOG_INFO("set vci voltage to %d\n", vol_vlaue);
		retval =
		    regulator_set_voltage(rmi4_data->tp_vci, vol_vlaue,
					  vol_vlaue);
		if (retval < 0) {
			TS_LOG_ERR
			    ("failed to set voltage regulator tp_vci error: %d\n",
			     retval);
			return -EINVAL;
		}

		retval = regulator_enable(rmi4_data->tp_vci);
		if (retval < 0) {
			TS_LOG_ERR("failed to enable regulator tp_vci\n");
			return -EINVAL;
		}
	}
	return 0;
}

static int synaptics_vci_disable(void)
{
	int retval;

	if (g_ts_data.fpga_flag == 1)
		return 0;

	if (IS_ERR(rmi4_data->tp_vci)) {
		TS_LOG_ERR("tp_vci is err\n");
		return -EINVAL;
	}
	retval = regulator_disable(rmi4_data->tp_vci);
	if (retval < 0) {
		TS_LOG_ERR("failed to disable regulator tp_vci\n");
		return -EINVAL;
	}

	return 0;
}

static int synaptics_vddio_enable(void)
{
	int retval;
	int vddio_value;

	if (g_ts_data.fpga_flag == 1)
		return 0 ;

	if (IS_ERR(rmi4_data->tp_vddio)) {
		TS_LOG_ERR("tp_vddio is err\n");
		return -EINVAL;
	}

	vddio_value = rmi4_data->synaptics_chip_data->regulator_ctr.vddio_value;
	if (rmi4_data->synaptics_chip_data->regulator_ctr.need_set_vddio_value) {
		TS_LOG_INFO("set tp_vddio voltage to %d\n", vddio_value);
		retval =
		    regulator_set_voltage(rmi4_data->tp_vddio, vddio_value,
					  vddio_value);
		if (retval < 0) {
			TS_LOG_ERR
			    ("failed to set voltage regulator tp_vddio error: %d\n",
			     retval);
			return -EINVAL;
		}
	}

	retval = regulator_enable(rmi4_data->tp_vddio);
	if (retval < 0) {
		TS_LOG_ERR("failed to enable regulator tp_vddio\n");
		return -EINVAL;
	}

	return 0;
}

static int synaptics_vddio_disable(void)
{
	int retval;

	if (g_ts_data.fpga_flag == 1)
		return 0;

	if (IS_ERR(rmi4_data->tp_vddio)) {
		TS_LOG_ERR("tp_vddio is err\n");
		return -EINVAL;
	}

	retval = regulator_disable(rmi4_data->tp_vddio);
	if (retval < 0) {
		TS_LOG_ERR("failed to disable regulator tp_vddio\n");
		return -EINVAL;
	}

	return 0;
}
#if 0
static void synatpics_regulator_enable(void)
{
	TS_LOG_INFO("synatpics_regulator_enable is called\n");
	if (1 == rmi4_data->synaptics_chip_data->vci_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vci)) {
			TS_LOG_INFO("vci enable is called\n");
			synaptics_vci_enable();
		}
	}
	mdelay(3);
	if (1 == rmi4_data->synaptics_chip_data->vddio_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vddio)) {
			synaptics_vddio_enable();
		}
	}
	mdelay(1);
}

static void synatpics_regulator_disable(void)
{
	if (1 == rmi4_data->synaptics_chip_data->vddio_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vddio)) {
			synaptics_vddio_disable();
		}
	}

	mdelay(12);

	if (1 == rmi4_data->synaptics_chip_data->vci_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vci)) {
			synaptics_vci_disable();
		}
	}

	mdelay(30);
}
#endif
/* dts */
static int synaptics_pinctrl_get_init(void)
{
	int ret = 0;

	if (g_ts_data.fpga_flag == 1)
		return 0;

	rmi4_data->pctrl = devm_pinctrl_get(&rmi4_data->synaptics_dev->dev);
	if (IS_ERR(rmi4_data->pctrl)) {
		TS_LOG_ERR("failed to devm pinctrl get\n");
		ret = -EINVAL;
		return ret;
	}

	rmi4_data->pins_default =
	    pinctrl_lookup_state(rmi4_data->pctrl, "default");
	if (IS_ERR(rmi4_data->pins_default)) {
		TS_LOG_ERR("failed to pinctrl lookup state default\n");
		ret = -EINVAL;
		goto err_pinctrl_put;
	}

	rmi4_data->pins_idle = pinctrl_lookup_state(rmi4_data->pctrl, "idle");
	if (IS_ERR(rmi4_data->pins_idle)) {
		TS_LOG_ERR("failed to pinctrl lookup state idle\n");
		ret = -EINVAL;
		goto err_pinctrl_put;
	}
	return 0;

err_pinctrl_put:
	devm_pinctrl_put(rmi4_data->pctrl);
	return ret;
}

static int synaptics_pinctrl_select_normal(void)
{
	int retval = NO_ERR;

	if (g_ts_data.fpga_flag == 1)
		return 0;

	retval =
	    pinctrl_select_state(rmi4_data->pctrl, rmi4_data->pins_default);
	if (retval < 0) {
		TS_LOG_ERR("set iomux normal error, %d\n", retval);
	}
	return retval;
}

static int synaptics_pinctrl_select_lowpower(void)
{
	int retval = NO_ERR;
	if (g_ts_data.fpga_flag == 1)
		return 0;

	retval = pinctrl_select_state(rmi4_data->pctrl, rmi4_data->pins_idle);
	if (retval < 0) {
		TS_LOG_ERR("set iomux lowpower error, %d\n", retval);
	}
	return retval;
}

#define GLOVE_SIGNAL
#ifdef GLOVE_SIGNAL
static int rmi_f11_read_finger_state(struct ts_fingers *info)
{
	int i;
	int retval = 0;
	u8 finger_state = 0;
	u16 f51_custom_CTRL03 = 0x0015;

	retval = synaptics_rmi4_i2c_read(rmi4_data, f51_custom_CTRL03,
					 (u8 *) &finger_state,
					 sizeof(finger_state));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read f51_custom_CTRL03, code: %d.\n",
			   retval);
		return retval;
	}

	for (i = 0; i < FILTER_GLOVE_NUMBER; i++) {
		info->fingers[i].status = (finger_state >> (2 * i)) & MASK_2BIT;
		if (info->fingers[i].status == 2) {
			info->fingers[i].status = TP_GLOVE;
		}
	}
	return 0;
}
#endif

void synaptics_ghost_detect(int value){
	if (GHOST_OPERATE_TOO_FAST == value){
		TS_LOG_INFO("%s operate too fast\n", __func__);
	}else if (GHOST_OPERATE_TWO_POINT_OPER_TOO_FAST == value){
		TS_LOG_INFO("%s operate 2 point too fast\n", __func__);
	}
	//DMD report
#if defined (CONFIG_HUAWEI_DSM)
	if (!dsm_client_ocuppy(tp_dclient)) {
		dsm_client_record(tp_dclient,
				  "noise record number: noise_record_num is %d.\n",
				  rmi4_data->synaptics_chip_data->noise_record_num);
		dsm_client_notify(tp_dclient,
				  DSM_TP_GHOST_TOUCH_ERROR_NO);
	}
#endif
	rmi4_data->synaptics_chip_data->noise_record_num = 0;
}

int synaptics_chip_check_status(void){
	int retval;
	unsigned char value = 0;

	TS_LOG_DEBUG("%s +\n", __func__);

	if (rmi4_data->synaptics_chip_data->noise_state_reg){
		retval = rmi4_data->i2c_read(rmi4_data, rmi4_data->synaptics_chip_data->noise_state_reg,
							&value, sizeof(unsigned char));
		if (retval < 0){
			atomic_set(&g_ts_data.ts_esd_state, TS_ESD_HAPPENDED);
			TS_LOG_ERR("%s read error\n", __func__);
			return 0;
		}

		switch(value){
			/* noise nomal */
			case NOISE_VALUE_0:
			case NOISE_VALUE_1:
				TS_LOG_DEBUG("%s noise state normal\n", __func__);
				break;
			/* noise abnormal */
			case NOISE_VALUE_2:
				TS_LOG_INFO("%s noise state abnormal\n", __func__);
				if (rmi4_data->synaptics_chip_data->noise_record_num < NOISE_RECORD_NUM_MAX)
					rmi4_data->synaptics_chip_data->noise_record_num++;
				break;
			default:
				TS_LOG_INFO("%s noise state unknown, abnormal:%d\n", __func__, value);
				break;
		}
	}

	TS_LOG_DEBUG("%s -\n", __func__);
	return 0;
}

void synaptics_work_after_input(void)
{
#ifdef ROI
	int retval;
	unsigned short roi_data_addr;
	unsigned char roi_tmp[ROI_DATA_READ_LENGTH];

	if (f51_roi_switch)  {
		if (roi_data_staled == 0)  {  /* roi_data is up to date now. */
			return;
		}

		/* We are about to refresh roi_data. To avoid stale output, use a completion to block possible readers. */
		reinit_completion(&roi_data_done);

		/* Request sensorhub to report fingersense data. */
		preread_fingersense_data();

		roi_data_addr =
		    g_ts_data.feature_info.roi_info.roi_data_addr;
		TS_LOG_DEBUG("roi_data_addr=0x%04x\n", roi_data_addr);

		retval =
		    synaptics_rmi4_i2c_read(rmi4_data, roi_data_addr,
					    roi_tmp,
					    ROI_DATA_READ_LENGTH);
		if (retval < 0) {
			TS_LOG_ERR
			    ("F12 Failed to read roi data, retval= %d \n",
			     retval);
		}
		else {
			/* roi_data pointer will be exported to app by function synaptics_roi_rawdata, so there's a race
			   condition while app reads roi_data and our driver refreshes it at the same time. We use local
			   variable(roi_tmp) to decrease the conflicting time window. Thus app will get consistent data,
			   except when we are executing the following memcpy. */
			memcpy(roi_data, roi_tmp, sizeof(roi_tmp));
		}

		roi_data_staled = 0;
		complete_all(&roi_data_done);  /* If anyone has been blocked by us, wake it up. */
	}
#endif
}

struct ts_device_ops ts_synaptics_ops = {
	.chip_detect = synaptics_chip_detect,
	.chip_init = synaptics_init_chip,
	.chip_get_brightness_info = synaptics_get_brightness_info,
	.chip_parse_config = synaptics_parse_dts,
	.chip_input_config = synaptics_input_config,
	.chip_irq_top_half = synaptics_irq_top_half,
	.chip_irq_bottom_half = synaptics_irq_bottom_half,
	.chip_fw_update_boot = synaptics_fw_update_boot,
	.chip_fw_update_sd = synaptics_fw_update_sd,
	.oem_info_switch = synaptics_oem_info_switch,
	.chip_get_info = synaptics_chip_get_info,
	.chip_get_capacitance_test_type =
	    synaptics_chip_get_capacitance_test_type,
	.chip_set_info_flag = synaptics_set_info_flag,
	.chip_before_suspend = synaptics_before_suspend,
	.chip_suspend = synaptics_suspend,
	.chip_resume = synaptics_resume,
	.chip_after_resume = synaptics_after_resume,
	.chip_wakeup_gesture_enable_switch =
	    synaptics_wakeup_gesture_enable_switch,
	.chip_get_rawdata = synaptics_get_rawdata,
	.chip_get_calibration_data = synaptics_get_calibration_data,
	.chip_get_calibration_info = synaptics_get_calibration_info,
	.chip_get_debug_data = synaptics_get_debug_data,
	.chip_glove_switch = synaptics_glove_switch,
	.chip_shutdown = synaptics_shutdown,
	.chip_charger_switch = synaptics_charger_switch,
	.chip_holster_switch = synaptics_holster_switch,
	.chip_roi_switch = synaptics_roi_switch,
	.chip_roi_rawdata = synaptics_roi_rawdata,
	.chip_palm_switch = synaptics_palm_switch,
	.chip_regs_operate = synaptics_regs_operate,
	.chip_calibrate = synaptics_calibrate,
	.chip_calibrate_wakeup_gesture = synaptics_calibrate_wakeup_gesture,
#if defined (CONFIG_HUAWEI_DSM)
	.chip_dsm_debug = synaptics_rmi4_dsm_debug,
#endif
	.chip_reset = synaptics_reset_device,
#ifdef HUAWEI_TOUCHSCREEN_TEST
	.chip_test = test_dbg_cmd_test,
#endif
	.chip_wrong_touch = synaptics_wrong_touch,
	.chip_work_after_input = synaptics_work_after_input,
	.chip_ghost_detect = synaptics_ghost_detect,
	.chip_check_status = synaptics_chip_check_status,
};

#if defined (CONFIG_HUAWEI_DSM)
static int synaptics_rmi4_dsm_debug(void)
{
	int retval = 0;
	int i = 0;
	int len = 0;
	int index = 0;
	int fhandler_ctrl_base = 0;
	int reg_offset = 0;
	int data_length = 0;
	int reg_start = 0;
	struct synaptics_work_reg_status *ptr = &dsm_dump_register_map[0];

	TS_LOG_INFO("Reading tp work reg status is called by dsm_debug\n");

	memset(synaptics_reg_status, 0, sizeof(synaptics_reg_status));

	for (index = 0;
	     ptr != NULL && index < ARRAY_SIZE(dsm_dump_register_map);
	     ptr++, index++) {
		fhandler_ctrl_base = ptr->fhandler_ctrl_base;
		reg_offset = ptr->offset;
		data_length = ptr->length;
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    fhandler_ctrl_base + reg_offset,
					    &synaptics_reg_status[reg_start],
					    data_length);
		if (retval < 0) {
			TS_LOG_ERR("read tp work status fail !\n");
		}
		len += data_length;
		reg_start = len - 1;
		TS_LOG_INFO
		    ("each length is len = %d , reg_start = %d, data_length = %d\n",
		     len, reg_start, data_length);
	}

	TS_LOG_INFO("synaptics_interrupt_num is %d\n", synaptics_interrupt_num);
	for (i = 0; i < len; i++)
		TS_LOG_INFO
		    ("synaptics_reg_status[%d] read from tp is %d when error was happened\n",
		     i, synaptics_reg_status[i]);
	return retval;
}
#endif
static int synaptics_get_rawdata(struct ts_rawdata_info *info,
				 struct ts_cmd_node *out_cmd)
{
	int retval = 0;
	if (1 == rmi4_data->synaptics_chip_data->unite_cap_test_interface) {
		TS_LOG_INFO("++++ get rawdata in\n");
		retval =
		    synaptics_rmi4_f54_init(rmi4_data,
					    synaptics_sett_param_regs->
					    module_name);
		if (retval < 0) {
			TS_LOG_ERR("Failed to init f54\n");
			return retval;
		}

		retval = synaptics_get_cap_data(info);
		if (retval < 0) {
			TS_LOG_ERR("Failed to get rawdata\n");
			return retval;
		}
		return NO_ERR;
	} else {
		return -EINVAL;
	}
}

static int synaptics_get_calibration_data(struct ts_calibration_data_info *info, struct ts_cmd_node *out_cmd)
{
	int retval = 0;

	TS_LOG_INFO("%s called\n", __FUNCTION__);

	retval = synaptics_rmi4_f54_init(rmi4_data,synaptics_sett_param_regs->module_name);
	if (retval < 0) {
		TS_LOG_ERR("Failed to init f54\n");
		return retval;
	}

	retval = synaptics_get_calib_data(info);
	if (retval < 0) {
		TS_LOG_ERR("Failed to get calibration data\n");
		return retval;
	}

	return NO_ERR;
}

static int synaptics_get_calibration_info(struct ts_calibration_info_param *info, struct ts_cmd_node *out_cmd)
{
	int retval = 0;

	TS_LOG_INFO("%s called\n", __FUNCTION__);

	retval = synaptics_rmi4_f54_init(rmi4_data,synaptics_sett_param_regs->module_name);
	if (retval < 0) {
		TS_LOG_ERR("Failed to init f54\n");
		return retval;
	}

	retval = synaptics_get_calib_info(info);
	if (retval < 0) {
		TS_LOG_ERR("Failed to get calibration info\n");
		return retval;
	}

	return NO_ERR;
}

static int synaptics_get_debug_data(struct ts_rawdata_info *info,
				    struct ts_cmd_node *out_cmd)
{
	int retval = 0;

	TS_LOG_INFO("synaptics get diff data begin\n");

	retval =
	    synaptics_rmi4_f54_init(rmi4_data,
				    synaptics_sett_param_regs->module_name);
	if (retval < 0) {
		TS_LOG_ERR("Failed to init f54\n");
		return retval;
	}

	retval = synaptics_debug_data_test(info);
	if (retval < 0) {
		TS_LOG_ERR("Failed to get diff data\n");
		return retval;
	}

	TS_LOG_INFO("synaptics get diff data end\n");
	return NO_ERR;
}

static int synaptics_set_info_flag(struct ts_data *info)
{
	g_ts_data.get_info_flag = info->get_info_flag;
	return NO_ERR;
}

static u8 tp_result_info[TS_CHIP_TYPE_MAX_SIZE] = {0};
static u8 tp_type_cmd[TS_CHIP_TYPE_MAX_SIZE] = {0};
static int synaptics_set_oem_info(struct ts_oem_info_param *info)
{
	u8 type_reserved = TS_CHIP_TYPE_RESERVED;
	u8 len_reserved = TS_CHIP_TYPE_LEN_RESERVED;
	int store_type_count = 0;
	int flash_size = 0;
	int used_size = 16;
	int error = NO_ERR;
	int index = 0;
	u8 type = 0;
	u8 len = 0;
	int i = 0;

	TS_LOG_INFO("%s called\n", __func__);
	flash_size = get_oem_data_info();
	type = info->data[0];
	len  = info->data[1];
	used_size += len * 16;

	//check type and len below
	TS_LOG_ERR("%s write Type=0x%2x , type data len=%d\n", __func__, type, len);
	if (type == 0x0 || type > type_reserved ) {
		TS_LOG_ERR("%s write Type=0x%2x is RESERVED\n", __func__, type);
		error = EINVAL;
		goto out;
	}

	if ( len > len_reserved ) {
		TS_LOG_ERR("%s TPIC write RESERVED NV STRUCT len\n", __func__);
		error = EINVAL;
		goto out;
	}
	//just store the data in tp_type_cmd buff
	if (len == 0x0) {
		tp_type_cmd[0] = info->data[0];
		TS_LOG_INFO("%s Just store type:%2x and then finished\n", __func__, info->data[0]);
		return error;
	}

	if (strlen(info->data) <= TS_CHIP_TYPE_MAX_SIZE) {
		memset(tp_type_cmd, 0x0, TS_CHIP_TYPE_MAX_SIZE);
		memcpy(tp_type_cmd, info->data, len*16);
	} else {
		error = EINVAL;
		TS_LOG_INFO("%s: invalid test cmd:%s\n", __func__);
		return error;
	}

	error = get_oem_data(info->buff, flash_size);
	if (error < 0) {
		TS_LOG_ERR("%s: get oem data failed,fail line=%d\n", __func__,
			   __LINE__);
		tp_result_info[0] = TS_CHIP_READ_ERROR;
		goto out;
	}

	TS_LOG_INFO("%s: Read data from TPIC flash is below\n", __func__);
	for(i = 0; i< flash_size/16; ++i ){
		TS_LOG_INFO("%s: %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x \n", __func__,
			info->buff[0+i*16],info->buff[1+i*16],info->buff[2+i*16],info->buff[3+i*16],
			info->buff[4+i*16],info->buff[5+i*16],info->buff[6+i*16],info->buff[7+i*16],
			info->buff[8+i*16],info->buff[9+i*16],info->buff[10+i*16],info->buff[11+i*16],
			info->buff[12+i*16],info->buff[13+i*16],info->buff[14+i*16],info->buff[15+i*16]
		);
	}

	// Adding type data into the buffer
	for (index = 1; index < flash_size/16;) {
		u8 tmp_type = info->buff[index*16];
		u8 tmp_len = info->buff[index*16+1];
		if (tmp_len < len_reserved) {
			used_size += tmp_len * 16;
		}

		if (tmp_type == type) {
			store_type_count += 1;
		}

		if (store_type_count >= TS_CHIP_WRITE_MAX_TYPE_COUNT) {
				TS_LOG_ERR("%s: Write TPIC Type:0x%2x are larger than %d times\n", __func__, type, TS_CHIP_WRITE_MAX_TYPE_COUNT );
				tp_result_info[0] = TS_CHIP_MAX_COUNT_ERROR;
				goto out;
		}

		if (used_size > flash_size) {
			TS_LOG_ERR("%s: Used flash size is larger than TPIC Flash size\n", __func__ );
			tp_result_info[0] = TS_CHIP_NO_FLASH_ERROR;
			goto out;
		}

		if ((tmp_type == 0x00 && tmp_len == 0x00) ||(tmp_type == 0xFF && tmp_len == 0xFF)) {
			memcpy(&(info->buff[index*16]), tp_type_cmd, len*16);
			break;
		}
		index += tmp_len;
	}

	TS_LOG_INFO("%s: Add write type data into buff below\n", __func__);
	for(i = 0; i< flash_size/16; ++i ){
		TS_LOG_INFO("%s: %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x \n", __func__,
			info->buff[0+i*16],info->buff[1+i*16],info->buff[2+i*16],info->buff[3+i*16],
			info->buff[4+i*16],info->buff[5+i*16],info->buff[6+i*16],info->buff[7+i*16],
			info->buff[8+i*16],info->buff[9+i*16],info->buff[10+i*16],info->buff[11+i*16],
			info->buff[12+i*16],info->buff[13+i*16],info->buff[14+i*16],info->buff[15+i*16]
		);
	}

	//Write buffer into TPIC flash
	error = set_oem_data(info->buff, flash_size);
	if (error < 0) {
		TS_LOG_ERR("%s: get oem data failed\n", __func__);
		tp_result_info[0] = TS_CHIP_WRITE_ERROR;
		goto out;
	}

	//check the write data.
	memset(info->buff, 0, TS_CHIP_BUFF_MAX_SIZE);
	error = get_oem_data(info->buff, flash_size);
	if (error < 0) {
		TS_LOG_ERR("%s: get oem data failed,fail line=%d\n", __func__,
			   __LINE__);
		tp_result_info[0] = TS_CHIP_READ_ERROR;
		goto out;
	}
	used_size -= len * 16;
	error = strncmp(&(info->buff[used_size]), tp_type_cmd, len*16);
	if( error ) {
		tp_result_info[0] = TS_CHIP_WRITE_ERROR;
		TS_LOG_ERR("%s: Write type data has some error\n", __func__);
	}

out:
	memset(tp_type_cmd, 0x0, TS_CHIP_TYPE_MAX_SIZE);
	TS_LOG_INFO("%s End\n", __func__);
	return error;

}

static int synaptics_get_oem_info(struct ts_oem_info_param *info)
{
	u8 type_reserved = TS_CHIP_TYPE_RESERVED;
	u8 type = tp_type_cmd[0];
	unsigned short flash_size = 0;
	int error = NO_ERR;
	int index =0;
	int latest_index = 0;
	int i;

	TS_LOG_INFO("%s called\n", __func__);
	flash_size = get_oem_data_info();
	if(flash_size <= 0) {
		TS_LOG_ERR("%s: Could not get TPIC flash size,fail line=%d\n", __func__,
			   __LINE__);
		error = EINVAL;
		goto out;
	}

	//return the result info if type is 0x0
	if(type == 0x0) {
		memcpy(info->data, tp_result_info, TS_CHIP_TYPE_MAX_SIZE);
		TS_LOG_INFO("%s:Reurn the write result=%2x to sys node.\n", __func__, info->data[0]);
		goto out;
	}

	//check type
	TS_LOG_INFO("%s: store type=%2x\n", __func__, type);
	if (type > type_reserved) {
		TS_LOG_ERR("%s Read Type=0x%2x is RESERVED\n", __func__, type);
		error = EINVAL;
		goto out;
	}

	error = get_oem_data(info->buff, flash_size);
	if (error < 0) {
		TS_LOG_ERR("%s: memory not enough,fail line=%d\n", __func__,
			   __LINE__);
		error = EINVAL;
		goto out;
	}

	TS_LOG_INFO("%s:Get buff data below\n", __func__);
	for(i = 0; i< flash_size/16; ++i ){
		TS_LOG_INFO("%s: %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x %2x \n", __func__,
			info->buff[0+i*16],info->buff[1+i*16],info->buff[2+i*16],info->buff[3+i*16],
			info->buff[4+i*16],info->buff[5+i*16],info->buff[6+i*16],info->buff[7+i*16],
			info->buff[8+i*16],info->buff[9+i*16],info->buff[10+i*16],info->buff[11+i*16],
			info->buff[12+i*16],info->buff[13+i*16],info->buff[14+i*16],info->buff[15+i*16]
		);
	}

	//scan each NV struct length
	for (index = 1; index < flash_size/16;) {
		u8 tmp_type = info->buff[index*16];
		u8 tmp_len = info->buff[index*16+1];
		if (tmp_type == type) {
			latest_index = index;
		} else if ((tmp_type == 0 && tmp_len == 0)||(tmp_type == 0xFF && tmp_len == 0xFF) ) {
			break;
		}
		index += tmp_len;
	}

	memset(info->data, 0x0, TS_CHIP_TYPE_MAX_SIZE);
	if (latest_index) {
		TS_LOG_INFO("%s type data find. len = %d\n", __func__, info->buff[latest_index*16+1]*16);
		memcpy(info->data, &(info->buff[latest_index*16]), info->buff[latest_index*16+1]*16 );
	} else {
		info->data[0] = 0x1;
		TS_LOG_INFO("%s No type data find. info->data[0] = %2x\n", __func__, info->data[0]);
	}

out:
	TS_LOG_INFO("%s End\n", __func__);
	return error;
}

static int synaptics_oem_info_switch(struct ts_oem_info_param *info)
{
	int retval = NO_ERR;

	if (!info) {
		TS_LOG_ERR("synaptics_oem_info_switch: info is Null\n");
		retval = -ENOMEM;
		return retval;
	}

	switch (info->op_action) {
	case TS_ACTION_WRITE:
		retval = synaptics_set_oem_info(info);
		if (retval != 0) {
			TS_LOG_ERR("%s, synaptics_oem_info_switch faild\n",
				   __func__);
		}
		break;
	case TS_ACTION_READ:
		retval = synaptics_get_oem_info(info);
		if (retval != 0) {
			TS_LOG_ERR("%s, synaptics_get_oem_info faild\n",
				   __func__);
		}
		break;
	default:
		TS_LOG_INFO("invalid oem info switch(%d) action: %d\n",
				info->data_switch, info->op_action);
		retval = -EINVAL;
		break;
	}
	return retval;
}
static int synaptics_chip_get_info(struct ts_chip_info_param *info)
{
	int retval = 0;
	u8 buf[CHIP_INFO_LENGTH];
	unsigned char string_id_buf[CHIP_INFO_LENGTH * 2] = { 0 };
	int projectid_lenth = 0;

	if (rmi4_data->synaptics_chip_data->projectid_len) {
		projectid_lenth = rmi4_data->synaptics_chip_data->projectid_len;
	} else {
		projectid_lenth = PROJECT_ID_FW_LEN;
	}

	memset(buf, 0, sizeof(buf));
	TS_LOG_INFO("g_ts_data.get_info_flag=%d\n", g_ts_data.get_info_flag);
	if (unlikely
	    ((atomic_read(&g_ts_data.state) == TS_SLEEP)
	     || (atomic_read(&g_ts_data.state) == TS_WORK_IN_SLEEP))) {
		strncpy(buf, config_id_string, strlen(config_id_string));
	} else {
		if (!g_ts_data.get_info_flag) {
			if (SYNAPTICS_S3718 != rmi4_data->synaptics_chip_data->ic_type
				&& SYNAPTICS_TD4322 != rmi4_data->synaptics_chip_data->ic_type
				&& SYNAPTICS_TD4300 != rmi4_data->synaptics_chip_data->ic_type) {
				retval =
				    synaptics_fw_configid(rmi4_data, buf,
							  sizeof(buf));
				if (retval < 0)
					TS_LOG_ERR("failed to get configid\n");
				synaptics_fw_data_init(rmi4_data);
				synaptics_fw_data_release();
			} else {
				retval =
				    synaptics_fw_s3718_configid(rmi4_data, buf,
								sizeof(buf));
				if (retval < 0)
					TS_LOG_ERR("failed to get configid\n");
				synaptics_fw_data_s3718_init(rmi4_data);
				synaptics_fw_data_s3718_release();
				synaptics_rmi4_status_resume(rmi4_data);
			}
		}
	}

	memcpy(&string_id_buf, SYNAPTICS_CHIP_INFO,
	       strlen(SYNAPTICS_CHIP_INFO));
	if (0 == strncasecmp(rmi4_data->rmi4_mod_info.project_id_string, FRD_JDI_11081, FRD_JDI_11081_LEN)) {
		strncat(string_id_buf, FRD_JDI_11080, projectid_lenth);
	} else {
		strncat(string_id_buf, rmi4_data->rmi4_mod_info.project_id_string, projectid_lenth);
	}
	memcpy(&info->ic_vendor, string_id_buf, strlen(string_id_buf));
	memcpy(&info->mod_vendor, synaptics_sett_param_regs->module_name,
	       strlen(synaptics_sett_param_regs->module_name));
	memcpy(&info->fw_vendor, buf, strlen(buf));
	return NO_ERR;
}

/*  query the configure from dts and store in prv_data */
void synaptics_parse_chip_specific_dts(struct ts_device_data *chip_data)
{
	struct device_node *device = NULL;
	unsigned char string_id_buf[CHIP_INFO_LENGTH * 2] = { 0 };
	int retval, read_val;
	int array_len = 0;
	int index = 0;
	int synaptics_rawdata_count = 0;
	const char *raw_data_dts = NULL;
	char *producer = NULL;
	int projectid_lenth = 0;

	ts_anti_false_touch_param_achieve(chip_data);
	if (rmi4_data->synaptics_chip_data->projectid_len) {
		projectid_lenth = rmi4_data->synaptics_chip_data->projectid_len;
	} else {
		projectid_lenth = PROJECT_ID_FW_LEN;
	}

	rmi4_data->module_name = NULL;

	memcpy(&string_id_buf, SYNAPTICS_CHIP_INFO,
	       strlen(SYNAPTICS_CHIP_INFO));

	TS_LOG_INFO("project_id_string = %s\n",
		    rmi4_data->rmi4_mod_info.project_id_string);
	TS_LOG_INFO("product_id_string = %s, projectid_lenth=%d\n",
		    rmi4_data->rmi4_mod_info.product_id_string, projectid_lenth);
	strncat(string_id_buf, rmi4_data->rmi4_mod_info.project_id_string,
		projectid_lenth);

	TS_LOG_INFO("try to get chip specific dts: %s\n", string_id_buf);

	device = of_find_compatible_node(NULL, NULL, string_id_buf);
	if (!device) {
		TS_LOG_INFO("No chip specific dts: %s, need to parse\n",
			    string_id_buf);
		return;
	}

	retval = of_property_read_u32(device, SYNAPTICS_IC_TYPES, &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific ic_type = %d\n", read_val);
		chip_data->ic_type = read_val;
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_X_MAX, &chip_data->x_max);
	if (!retval) {
		TS_LOG_INFO("get chip specific x_max = %d\n", chip_data->x_max);
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_Y_MAX, &chip_data->y_max);
	if (!retval) {
		TS_LOG_INFO("get chip specific y_max = %d\n", chip_data->y_max);
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_X_MAX_MT,
				 &chip_data->x_max_mt);
	if (!retval) {
		TS_LOG_INFO("get chip specific x_max_mt = %d\n",
			    chip_data->x_max_mt);
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_Y_MAX_MT,
				 &chip_data->y_max_mt);
	if (!retval) {
		TS_LOG_INFO("get chip specific y_max_mt = %d\n",
			    chip_data->y_max_mt);
	}

	rmi4_data->sensor_max_x = chip_data->x_max - 1;
	rmi4_data->sensor_max_y = chip_data->y_max - 1;
	rmi4_data->sensor_max_x_mt = chip_data->x_max_mt - 1;
	rmi4_data->sensor_max_y_mt = chip_data->y_max_mt - 1;

	retval =
	    of_property_read_u32(device, SYNAPTICS_REPORT_RATE_TEST, &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific report_rate_test = %d\n",
			    read_val);
		chip_data->report_rate_test = read_val;
	}

	retval = of_property_read_u32(device, "rawdata_report_type", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific rawdata_report_type = %d\n",
			    read_val);
		chip_data->rawdata_report_type = read_val;
	} else {
		chip_data->rawdata_report_type = 3;
		TS_LOG_INFO("use default rawdata_report_type = %d\n",
			    chip_data->rawdata_report_type);
	}

	retval = of_property_read_u32(device, "rawdata_arrange_type", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific rawdata_arrange_type = %d\n",
			    read_val);
		chip_data->rawdata_arrange_type = read_val;
	} else {
		chip_data->rawdata_arrange_type = 0;
	}

	retval =
	    of_property_read_u32(device, "supported_func_indicater", &read_val);
	if (!retval) {
		TS_LOG_INFO("get supported_func_indicater = %d\n", read_val);
		chip_data->supported_func_indicater = read_val;
	} else {
		chip_data->supported_func_indicater = 0;
	}

	retval =
	    of_property_read_u32(device, "capacitance_test_config", &read_val);
	if (!retval) {
		TS_LOG_INFO("get capacitance_test_config = %d\n", read_val);
		chip_data->capacitance_test_config = read_val;
	} else {
		chip_data->capacitance_test_config = 0;
	}

	retval = of_property_read_u32(device, "support_3d_func", &read_val);
	if (!retval) {
		chip_data->support_3d_func = read_val;
		TS_LOG_INFO("get support_3d_func = %d\n",
			    chip_data->support_3d_func);
	} else {
		chip_data->support_3d_func = 0;
		TS_LOG_INFO("use default support_3d_func = %d\n",
			    chip_data->support_3d_func);
	}

	if (1 == chip_data->unite_cap_test_interface) {
		array_len = of_property_count_strings(device, "raw_data_limit");
		if (array_len > 0 && array_len <= RAWDATA_NUM) {
			for (index = 0; index < array_len; index++) {
				retval =
				    of_property_read_string_index(device,
								  "raw_data_limit",
								  index,
								  &raw_data_dts);
				if (retval) {
					TS_LOG_INFO
					    ("read index = %d,raw_data_limit = %s,retval = %d error,\n",
					     index, raw_data_dts, retval);
					break;
				}

				chip_data->raw_limit_buf[index] =
				    simple_strtol(raw_data_dts, NULL, 10);
				TS_LOG_INFO
				    ("get chip specific rawdatabuf[%d] = %d\n",
				     index, chip_data->raw_limit_buf[index]);
			}
		}
	}
#if defined(HUAWEI_CHARGER_FB)
	retval = of_property_read_u32(device, "charger_supported", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific charger_supported = %d\n",
			    read_val);
		g_ts_data.feature_info.charger_info.charger_supported =
		    (u8) read_val;
	}

	retval = of_property_read_u32(device, "charger_switch_bit", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific charger_switch_bit  = %d\n",
			    read_val);
		g_ts_data.feature_info.charger_info.charger_switch_bit =
		    (u16) read_val;
	}

	retval = of_property_read_u32(device, "charger_switch_addr", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific charger_switch_addr  = 0x%04x\n",
			    read_val);
		g_ts_data.feature_info.charger_info.charger_switch_addr =
		    (u16) read_val;
	}
#endif

	retval =
	    of_property_read_u32(device, SYNAPTICS_HOSTLER_SWITCH_BIT,
				 &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific holster_switch_bit = %d\n",
			    read_val);
		g_ts_data.feature_info.holster_info.holster_switch_bit =
		    (u16) read_val;
	}

	retval =
	    of_property_read_u32(device, SYNAPTICS_HOSTLER_SWITCH_ADDR,
				 &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific holster_switch_addr = 0x%04x\n",
			    read_val);
		g_ts_data.feature_info.holster_info.holster_switch_addr =
		    (u16) read_val;
	}

	retval =
	    of_property_read_u32(device, SYNAPTICS_GLOVE_SWITCH_BIT, &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific glove_switch_bit = %d\n",
			    read_val);
		g_ts_data.feature_info.glove_info.glove_switch_bit =
		    (u16) read_val;
	}

	retval =
	    of_property_read_u32(device, SYNAPTICS_GLOVE_SWITCH_ADDR,
				 &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific glove_switch_addr = 0x%04x\n",
			    read_val);
		g_ts_data.feature_info.glove_info.glove_switch_addr =
		    (u16) read_val;
	}

	retval = of_property_read_u32(device, "roi_supported", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific roi_supported = %d\n", read_val);
		g_ts_data.feature_info.roi_info.roi_supported = (u8) read_val;
	} else {
		TS_LOG_INFO("can not get roi_supported value\n");
		g_ts_data.feature_info.roi_info.roi_supported = 0;
	}

	retval = of_property_read_u32(device, "roi_control_addr", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific roi_control_addr = 0x%04x\n",
			    read_val);
		g_ts_data.feature_info.roi_info.roi_control_addr =
		    (u16) read_val;
	}

	retval = of_property_read_u32(device, "roi_control_bit", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific roi_control_bit = %d\n",
			    read_val);
		g_ts_data.feature_info.roi_info.roi_control_bit = (u8) read_val;
	}

	retval = of_property_read_u32(device, "roi_data_addr", &read_val);
	if (!retval) {
		TS_LOG_INFO("get chip specific roi_data_addr = 0x%04x\n",
			    read_val);
		g_ts_data.feature_info.roi_info.roi_data_addr = (u16) read_val;
	}

	retval = of_property_read_string(device, "producer", &producer);
	if (NULL != producer) {
		TS_LOG_INFO("producer = %s\n", producer);
		rmi4_data->module_name = producer;
	}

	retval =
	    of_property_read_u32(device, SYNAPTICS_FW_UPDATE_LOGIC,
				 &chip_data->fw_update_logic);
	if (retval) {
		TS_LOG_INFO("get device fw_update_logic null, use default\n");
		chip_data->fw_update_logic = FW_UPDATE_DIFF;
		retval = 0;
	}

	retval = of_property_read_u32(device, TEST_ENHANCE_RAW_DATA_CAPACITANCE, &chip_data->test_enhance_raw_data_capacitance);
	if (retval) {
		TS_LOG_INFO("get device test_enhance_raw_data_capacitance null, use default\n");
		chip_data->test_enhance_raw_data_capacitance = 0;
		retval = 0;
	} else{
		synaptics_rawdata_count = rmi4_data->num_of_rx * rmi4_data->num_of_tx;
		TS_LOG_INFO("synaptics_rawdata_count= %d\n", synaptics_rawdata_count);
		chip_data->upper = (int *)kzalloc(synaptics_rawdata_count * sizeof(int), GFP_KERNEL);
		chip_data->lower = (int *)kzalloc(synaptics_rawdata_count * sizeof(int), GFP_KERNEL);
		if(!chip_data->upper || !chip_data->lower) {
			TS_LOG_ERR("Memory was out\n");
			chip_data->test_enhance_raw_data_capacitance = 0;
		} else {
			retval = of_property_read_u32_array(device, "huawei,enhance_rawdata_upperlimit", chip_data->upper, synaptics_rawdata_count);
			if(retval) {
				TS_LOG_ERR("get device test_enhance_raw_data error\n");
				memset(chip_data->upper, 1, synaptics_rawdata_count*sizeof(int));
				retval = 0;
			}
			retval = of_property_read_u32_array(device, "huawei,enhance_rawdata_lowerlimit", chip_data->lower, synaptics_rawdata_count);
			if(retval){
				TS_LOG_ERR("get device test_enhance_raw_data error\n");
				memset(chip_data->lower, 0, synaptics_rawdata_count*sizeof(int));
				retval = 0;
			}
		}
	}
	TS_LOG_INFO("chip_data->test_enhance_raw_data_capacitance=%d\n", chip_data->test_enhance_raw_data_capacitance);

	retval = of_property_read_u32(device, SHOULD_CHECK_TP_CALIBRATION_INFO, &chip_data->should_check_tp_calibration_info);
	if (retval) {
		TS_LOG_INFO("get device should_check_tp_calibration_info null, use default\n");
		chip_data->should_check_tp_calibration_info = 0;
		retval = 0;
	}

	retval = of_property_read_u32(device, "noise_state_reg", &chip_data->noise_state_reg);
	if (retval) {
		TS_LOG_INFO("device noise_state_reg not exit,use default value.\n");
		chip_data->noise_state_reg = 0;
		retval = 0;
	}else{
		TS_LOG_INFO("get device noise_state_reg:%02x\n", chip_data->noise_state_reg);
	}
	TS_LOG_INFO("chip_data->should_check_tp_calibration_info=%d\n", chip_data->should_check_tp_calibration_info);
}

/*  query the configure from dts and store in prv_data */
static int synaptics_parse_dts(struct device_node *device,
			       struct ts_device_data *chip_data)
{
	int retval = NO_ERR;
	const char *raw_data_dts = NULL;
	int index = 0;
	int array_len = 0;
	chip_data->irq_gpio = of_get_named_gpio(device, SYNAPTCS_IRQ_GPIO, 0);
	if (!gpio_is_valid(chip_data->irq_gpio)) {
		TS_LOG_ERR("irq gpio is not valid, value is %d\n",
			   chip_data->irq_gpio);
	}
	chip_data->reset_gpio = of_get_named_gpio(device, SYNAPTCS_RST_GPIO, 0);
	if (!gpio_is_valid(chip_data->reset_gpio)) {
		TS_LOG_ERR("reset gpio is not valid\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTCS_IRQ_CFG,
				 &chip_data->irq_config);
	if (retval) {
		TS_LOG_ERR("get irq config failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_ALGO_ID,
				 &chip_data->algo_id);
	if (retval) {
		TS_LOG_ERR("get algo id failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_IC_TYPES,
				 &chip_data->ic_type);
	if (retval) {
		TS_LOG_ERR("get device ic_type failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_VCI_LDO_VALUE,
				 &chip_data->regulator_ctr.vci_value);
	if (retval) {
		TS_LOG_INFO("Not define Vci value in Dts, use fault value\n");
		chip_data->regulator_ctr.vci_value = 3100000;
	}

	retval =
	    of_property_read_u32(device, SYNAPTICS_NEED_SET_VDDIO_VALUE,
				 &chip_data->regulator_ctr.
				 need_set_vddio_value);
	if (retval) {
		TS_LOG_INFO
		    ("Not define need set Vddio value in Dts, use fault value\n");
		chip_data->regulator_ctr.need_set_vddio_value = 0;
	} else {
		retval =
		    of_property_read_u32(device, SYNAPTICS_VDDIO_LDO_VALUE,
					 &chip_data->regulator_ctr.vddio_value);
		if (retval) {
			TS_LOG_INFO
			    ("Not define Vddio value in Dts, use fault value\n");
			chip_data->regulator_ctr.vddio_value = 1800000;
		}
	}

	retval =
	    of_property_read_u32(device, SYNAPTICS_WD_CHECK,
				 &chip_data->need_wd_check_status);
	if (retval) {
		TS_LOG_ERR("get device ic_type failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_UNIT_CAP_TEST_INTERFACE,
				 &chip_data->unite_cap_test_interface);
	if (retval) {
		TS_LOG_ERR("get unite_cap_test_interface failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_REPORT_RATE_TEST,
				 &chip_data->report_rate_test);
	if (retval) {
		TS_LOG_ERR("get report_rate_test failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_X_MAX, &chip_data->x_max);
	if (retval) {
		TS_LOG_ERR("get device x_max failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_Y_MAX, &chip_data->y_max);
	if (retval) {
		TS_LOG_ERR("get device y_max failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_X_MAX_MT,
				 &chip_data->x_max_mt);
	if (retval) {
		TS_LOG_ERR("get device x_max failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_Y_MAX_MT,
				 &chip_data->y_max_mt);
	if (retval) {
		TS_LOG_ERR("get device y_max failed\n");
	}

	retval =
	    of_property_read_u32(device, "flip_x",
				 &chip_data->flip_x);
	if (retval) {
		TS_LOG_INFO("device flip_x use default\n");
		chip_data->flip_x = true;
	}

	retval =
	    of_property_read_u32(device, "flip_y",
				 &chip_data->flip_y);
	if (retval) {
		TS_LOG_INFO("device flip_y use default\n");
		chip_data->flip_y = true;
	}

	retval =
	    of_property_read_u32(device, SYNAPTICS_VCI_GPIO_TYPE,
				 &chip_data->vci_gpio_type);
	if (retval) {
		TS_LOG_ERR("get device SYNAPTICS_VCI_GPIO_TYPE failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_VCI_REGULATOR_TYPE,
				 &chip_data->vci_regulator_type);
	if (retval) {
		TS_LOG_ERR("get device SYNAPTICS_VCI_REGULATOR_TYPE failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_VDDIO_GPIO_TYPE,
				 &chip_data->vddio_gpio_type);
	if (retval) {
		TS_LOG_ERR("get device SYNAPTICS_VDDIO_GPIO_TYPE failed\n");
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_PROJECTID_LEN,
				 &chip_data->projectid_len);
	if (retval) {
		TS_LOG_ERR("get device projectid_len failed\n");
		chip_data->projectid_len = 0;
	}
	retval =
	    of_property_read_u32(device, SYNAPTICS_VDDIO_REGULATOR_TYPE,
				 &chip_data->vddio_regulator_type);
	if (retval) {
		TS_LOG_ERR
		    ("get device SYNAPTICS_VDDIO_REGULATOR_TYPE failed\n");
	}
	retval =
	    of_property_read_string(device, SYNAPTICS_TEST_TYPE,
				 &chip_data->tp_test_type);
	if (retval) {
		TS_LOG_INFO
		    ("get device SYNAPTICS_TEST_TYPE not exit,use default value\n");
		strncpy(chip_data->tp_test_type,
			"Normalize_type:judge_different_reslut",
			TS_CAP_TEST_TYPE_LEN);
	}
	/*0 is power supplied by gpio, 1 is power supplied by ldo */
	if (1 == chip_data->vci_gpio_type) {
		chip_data->vci_gpio_ctrl =
		    of_get_named_gpio(device, SYNAPTICS_VCI_GPIO_CTRL, 0);
		if (!gpio_is_valid(chip_data->vci_gpio_ctrl)) {
			TS_LOG_ERR
			    ("SFT: ok; ASIC: Real err----power gpio is not valid\n");
		}
	}
	if (1 == chip_data->vddio_gpio_type) {
		chip_data->vddio_gpio_ctrl =
		    of_get_named_gpio(device, SYNAPTICS_VDDIO_GPIO_CTRL, 0);
		if (!gpio_is_valid(chip_data->vddio_gpio_ctrl)) {
			TS_LOG_ERR
			    ("SFT: ok; ASIC: Real err----power gpio is not valid\n");
		}
	}

	/*0 is cover without glass, 1 is cover with glass that need glove mode */
	retval =
	    of_property_read_u32(device, SYNAPTICS_COVER_FORCE_GLOVE,
				 &chip_data->cover_force_glove);
	if (retval) {
		TS_LOG_INFO
		    ("get device SYNAPTICS_COVER_FORCE_GLOVE failed,use default!\n");
		chip_data->cover_force_glove = 0;	/*if not define in dtsi,set 0 to disable it*/
	}

	if (1 == chip_data->unite_cap_test_interface) {
		array_len = of_property_count_strings(device, "raw_data_limit");
		if (array_len <= 0 || array_len > RAWDATA_NUM) {
			TS_LOG_ERR
			    ("raw_data_limit length invaild or dts number is larger than:%d\n",
			     array_len);
			raw_data_limit_flag = true;
		}

		for (index = 0; index < array_len; index++) {
			retval =
			    of_property_read_string_index(device,
							  "raw_data_limit",
							  index, &raw_data_dts);
			if (retval) {
				TS_LOG_ERR
				    ("read index = %d,raw_data_limit = %s,retval = %d error,\n",
				     index, raw_data_dts, retval);
			}

			if (!retval) {
				chip_data->raw_limit_buf[index] =
				    simple_strtol(raw_data_dts, NULL, 10);
				TS_LOG_INFO("rawdatabuf[%d] = %d\n", index,
					    chip_data->raw_limit_buf[index]);
			}
		}
	}

	retval =
	    of_property_read_u32(device, "bootloader_update_enable",
				 &chip_data->bootloader_update_enable);
	if (retval) {
		chip_data->bootloader_update_enable = 0;
		TS_LOG_INFO("get device bootloader_update_enable fail\n");
	}
	retval =
	    of_property_read_u32(device, "disable_reset_bit",
				 &chip_data->disable_reset);
	if (!retval) {
		TS_LOG_INFO("find disable_reset_bit, diasble_reset = %d\n",
			    chip_data->disable_reset);
	} else {
		chip_data->disable_reset = 0;
		TS_LOG_ERR("NO need to disable reset\n");
	}
	retval =
	    of_property_read_u32(device, "use_ub_supported",
				 &chip_data->use_ub_supported);
	if (retval) {
		chip_data->use_ub_supported = 0;
		TS_LOG_INFO("device use_ub_supported not exit,use default value.\n");
	}

	retval =
	    of_property_read_u32(device, "delay_for_fw_update",
				 &chip_data->delay_for_fw_update);
	if (retval) {
		chip_data->delay_for_fw_update = 0;
		TS_LOG_INFO("device delay_for_fw_update not found.\n");
	}

	retval = of_property_read_u32(device, GHOST_DETECT_SUPPORT, &chip_data->ghost_detect_support);
	if (retval) {
		chip_data->ghost_detect_support = 0;
		TS_LOG_ERR("%s:%s device %s not exit,use default value.\n",
			__func__, GHOST_LOG_TAG, GHOST_DETECT_SUPPORT);
	}else{
		TS_LOG_INFO("%s:%s get device %s : %d\n",
			__func__, GHOST_LOG_TAG, GHOST_DETECT_SUPPORT, chip_data->ghost_detect_support);
		if (chip_data->ghost_detect_support){
			ts_algo_det_ght_init();
		}
	}

	retval = of_property_read_u32(device, "check_status_watchdog_timeout", &chip_data->check_status_watchdog_timeout);
	if (retval) {
		chip_data->check_status_watchdog_timeout = 0;
		TS_LOG_ERR("device check_status_watchdog_timeout not exit,use default value.\n");
	}else{
		TS_LOG_INFO("get device check_status_watchdog_timeout :%d\n", chip_data->check_status_watchdog_timeout);
	}

	retval = of_property_read_u32(device, "rawdata_get_timeout", &chip_data->rawdata_get_timeout);
	if (!retval) {
		TS_LOG_INFO("get chip rawdata limit time = %d\n", chip_data->rawdata_get_timeout);
	} else {
		TS_LOG_INFO("can not get chip rawdata limit time, use default\n");
		chip_data->rawdata_get_timeout = 0;
	}

	TS_LOG_INFO
	    ("reset_gpio = %d, irq_gpio = %d, irq_config = %d, algo_id = %d, ic_type = %d, x_max = %d, y_max = %d, x_mt = %d,y_mt = %d, bootloader_update_enable = %d\n",
	     chip_data->reset_gpio, chip_data->irq_gpio, chip_data->irq_config,
	     chip_data->algo_id, chip_data->ic_type, chip_data->x_max,
	     chip_data->y_max, chip_data->x_max_mt, chip_data->y_max_mt,
	     chip_data->bootloader_update_enable);

	return NO_ERR;
}

static void synaptics_power_on_gpio_set(void)
{
	synaptics_pinctrl_select_normal();
	gpio_direction_input(rmi4_data->synaptics_chip_data->irq_gpio);
	if (SYNAPTICS_S3207 != rmi4_data->synaptics_chip_data->ic_type)
		gpio_direction_output(rmi4_data->synaptics_chip_data->
				      reset_gpio, 1);
}

void ts_power_gpio_enable(void)
{
	if (rmi4_data == NULL) {
		TS_LOG_ERR("rmi4_data == NULL\n");
		return;
	}

	if (rmi4_data->synaptics_chip_data == NULL) {
		TS_LOG_ERR("synaptics_chip_data == NULL\n");
		return;
	}

	mutex_lock(&ts_power_gpio_sem);
	if (ts_power_gpio_ref == 0) {
		gpio_direction_output(rmi4_data->synaptics_chip_data->
				      vddio_gpio_ctrl, 1);
	}
	ts_power_gpio_ref++;
	TS_LOG_INFO("ts_power_gpio_ref++ = %d\n", ts_power_gpio_ref);
	mutex_unlock(&ts_power_gpio_sem);
}

EXPORT_SYMBOL(ts_power_gpio_enable);

void ts_power_gpio_disable(void)
{
	if (rmi4_data == NULL) {
		TS_LOG_ERR("rmi4_data == NULL\n");
		return;
	}

	if (rmi4_data->synaptics_chip_data == NULL) {
		TS_LOG_ERR("synaptics_chip_data == NULL\n");
		return;
	}

	mutex_lock(&ts_power_gpio_sem);
	if (ts_power_gpio_ref == 1) {
		gpio_direction_output(rmi4_data->synaptics_chip_data->
				      vddio_gpio_ctrl, 0);
	}
	if (ts_power_gpio_ref > 0) {
		ts_power_gpio_ref--;
	}
	TS_LOG_INFO("ts_power_gpio_ref-- = %d\n", ts_power_gpio_ref);
	mutex_unlock(&ts_power_gpio_sem);
}

EXPORT_SYMBOL(ts_power_gpio_disable);

static void synaptics_vci_on(void)
{
	TS_LOG_INFO("%s vci enable\n", __func__);
	if (1 == rmi4_data->synaptics_chip_data->vci_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vci)) {
			TS_LOG_INFO("vci enable is called\n");
			synaptics_vci_enable();
		}
	}

	if (rmi4_data->synaptics_chip_data->vci_gpio_type) {
		TS_LOG_INFO("%s vci switch gpio on\n", __func__);
		gpio_direction_output(rmi4_data->synaptics_chip_data->
				      vci_gpio_ctrl, 1);
	}
}

static void synaptics_vddio_on(void)
{
	TS_LOG_INFO("%s vddio enable\n", __func__);
	if (1 == rmi4_data->synaptics_chip_data->vddio_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vddio)) {
			TS_LOG_INFO("vddio enable is called\n");
			synaptics_vddio_enable();
		}
	}

	if (rmi4_data->synaptics_chip_data->vddio_gpio_type) {
		TS_LOG_INFO("%s vddio switch gpio on\n", __func__);
		ts_power_gpio_enable();
	}
}

static void synaptics_power_on(void)
{
	TS_LOG_INFO("synaptics_power_on called\n");
	synaptics_vci_on();
	mdelay(5);
	synaptics_vddio_on();
	mdelay(5);
	synaptics_power_on_gpio_set();
}

static void synaptics_power_off_gpio_set(void)
{
	TS_LOG_INFO("suspend RST out L\n");
	if (SYNAPTICS_S3718 == rmi4_data->synaptics_chip_data->ic_type
		|| SYNAPTICS_TD4322 == rmi4_data->synaptics_chip_data->ic_type
		|| SYNAPTICS_TD4300== rmi4_data->synaptics_chip_data->ic_type)
		gpio_direction_output(rmi4_data->synaptics_chip_data->reset_gpio, 0);
	synaptics_pinctrl_select_lowpower();
	if (SYNAPTICS_S3718 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4322 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4300 != rmi4_data->synaptics_chip_data->ic_type)
		gpio_direction_input(rmi4_data->synaptics_chip_data->reset_gpio);
	mdelay(1);
}

static void synatpics_vddio_off(void)
{
	if (1 == rmi4_data->synaptics_chip_data->vddio_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vddio)) {
			synaptics_vddio_disable();
		}
	}

	if (rmi4_data->synaptics_chip_data->vddio_gpio_type) {
		TS_LOG_INFO("%s vddio switch gpio off\n", __func__);
		ts_power_gpio_disable();
	}
}

static void synatpics_vci_off(void)
{
	if (1 == rmi4_data->synaptics_chip_data->vci_regulator_type) {
		if (!IS_ERR(rmi4_data->tp_vci)) {
			synaptics_vci_disable();
		}
	}

	if (rmi4_data->synaptics_chip_data->vci_gpio_type) {
		TS_LOG_INFO("%s vci switch gpio off\n", __func__);
		gpio_direction_output(rmi4_data->synaptics_chip_data->
				      vci_gpio_ctrl, 0);
	}
}

static void synaptics_power_off(void)
{
	synaptics_power_off_gpio_set();
	synatpics_vddio_off();
	mdelay(12);
	synatpics_vci_off();
	mdelay(30);
}

static void synaptics_gpio_reset(void)
{
	TS_LOG_DEBUG("synaptics_gpio_reset\n");
	gpio_direction_output(rmi4_data->synaptics_chip_data->reset_gpio, 1);
	mdelay(1);
	gpio_direction_output(rmi4_data->synaptics_chip_data->reset_gpio, 0);
	udelay(300);
	gpio_direction_output(rmi4_data->synaptics_chip_data->reset_gpio, 1);
	mdelay(1);
}

static int synaptics_gpio_request(void)
{
	int retval = NO_ERR;
	TS_LOG_INFO("synaptics_gpio_request\n");

	retval =
	    gpio_request(rmi4_data->synaptics_chip_data->reset_gpio,
			 "ts_reset_gpio");
	if (retval < 0) {
		TS_LOG_ERR("Fail request gpio:%d\n",
			   rmi4_data->synaptics_chip_data->reset_gpio);
		goto ts_reset_out;
	}
	retval =
	    gpio_request(rmi4_data->synaptics_chip_data->irq_gpio,
			 "ts_irq_gpio");
	if (retval) {
		TS_LOG_ERR("unable to request gpio:%d\n",
			   rmi4_data->synaptics_chip_data->irq_gpio);
		goto ts_irq_out;
	}
	if ((1 == rmi4_data->synaptics_chip_data->vci_gpio_type)
	    && (1 == rmi4_data->synaptics_chip_data->vddio_gpio_type)) {
		if (rmi4_data->synaptics_chip_data->vci_gpio_ctrl ==
		    rmi4_data->synaptics_chip_data->vddio_gpio_ctrl) {
			retval =
			    gpio_request(rmi4_data->synaptics_chip_data->
					 vci_gpio_ctrl, "ts_vci_gpio");
			if (retval) {
				TS_LOG_ERR
				    ("SFT:Ok;  ASIC: Real ERR----unable to request vci_gpio_ctrl firset:%d\n",
				     rmi4_data->synaptics_chip_data->
				     vci_gpio_ctrl);
				goto ts_vci_out;
			}
		} else {
			retval =
			    gpio_request(rmi4_data->synaptics_chip_data->
					 vci_gpio_ctrl, "ts_vci_gpio");
			if (retval) {
				TS_LOG_ERR
				    ("SFT:Ok;  ASIC: Real ERR----unable to request vci_gpio_ctrl2:%d\n",
				     rmi4_data->synaptics_chip_data->
				     vci_gpio_ctrl);
				goto ts_vci_out;
			}
			retval =
			    gpio_request(rmi4_data->synaptics_chip_data->
					 vddio_gpio_ctrl, "ts_vddio_gpio");
			if (retval) {
				TS_LOG_ERR
				    ("SFT:Ok;  ASIC: Real ERR----unable to request vddio_gpio_ctrl:%d\n",
				     rmi4_data->synaptics_chip_data->
				     vddio_gpio_ctrl);
				goto ts_vddio_out;
			}
		}
	} else {
		if (1 == rmi4_data->synaptics_chip_data->vci_gpio_type) {
			retval =
			    gpio_request(rmi4_data->synaptics_chip_data->
					 vci_gpio_ctrl, "ts_vci_gpio");
			if (retval) {
				TS_LOG_ERR
				    ("SFT:Ok;  ASIC: Real ERR----unable to request vci_gpio_ctrl2:%d\n",
				     rmi4_data->synaptics_chip_data->
				     vci_gpio_ctrl);
				goto ts_vci_out;
			}
		}
		if (1 == rmi4_data->synaptics_chip_data->vddio_gpio_type) {
			retval =
			    gpio_request(rmi4_data->synaptics_chip_data->
					 vddio_gpio_ctrl, "ts_vddio_gpio");
			if (retval) {
				TS_LOG_ERR
				    ("SFT:Ok;  ASIC: Real ERR----unable to request vddio_gpio_ctrl:%d\n",
				     rmi4_data->synaptics_chip_data->
				     vddio_gpio_ctrl);
				goto ts_vddio_out;
			}
		}
	}

	TS_LOG_INFO("reset:%d, irq:%d,\n",
		    rmi4_data->synaptics_chip_data->reset_gpio,
		    rmi4_data->synaptics_chip_data->irq_gpio);

	goto ts_reset_out;

ts_vddio_out:
	gpio_free(rmi4_data->synaptics_chip_data->vci_gpio_ctrl);
ts_vci_out:
	gpio_free(rmi4_data->synaptics_chip_data->irq_gpio);
ts_irq_out:
	gpio_free(rmi4_data->synaptics_chip_data->reset_gpio);
ts_reset_out:
	return retval;
}

static void synaptics_gpio_free(void)
{
	TS_LOG_INFO("synaptics_gpio_free\n");

	gpio_free(rmi4_data->synaptics_chip_data->irq_gpio);
	gpio_free(rmi4_data->synaptics_chip_data->reset_gpio);
	/*0 is power supplied by gpio, 1 is power supplied by ldo */
	if (1 == rmi4_data->synaptics_chip_data->vci_gpio_type) {
		if (rmi4_data->synaptics_chip_data->vci_gpio_ctrl)
			gpio_free(rmi4_data->synaptics_chip_data->
				  vci_gpio_ctrl);
	}
	if (1 == rmi4_data->synaptics_chip_data->vddio_gpio_type) {
		if (rmi4_data->synaptics_chip_data->vddio_gpio_ctrl)
			gpio_free(rmi4_data->synaptics_chip_data->
				  vddio_gpio_ctrl);
	}
}

static int i2c_communicate_check(void)
{
	int retval = NO_ERR;
	int i;
	u8 pdt_entry_addr = PDT_START;
	struct synaptics_rmi4_fn_desc rmi_fd;
	memset(&rmi_fd, 0, sizeof(rmi_fd));

	for (i = 0; i < I2C_RW_TRIES; i++) {
		retval = synaptics_rmi4_i2c_read(rmi4_data, pdt_entry_addr,
						 (unsigned char *)&rmi_fd,
						 sizeof(rmi_fd));
		if (retval < 0) {
			TS_LOG_ERR
			    ("Failed to read register map, i = %d, retval = %d\n",
			     i, retval);
			msleep(50);
		} else {
			TS_LOG_INFO("i2c communicate check success\n");
			retval = NO_ERR;
			return retval;
		}
	}

	return retval;
}

static int synaptics_chip_detect(struct device_node *device,
				 struct ts_device_data *chip_data,
				 struct platform_device *ts_dev)
{
	int retval = NO_ERR;

	TS_LOG_INFO("synaptics chip detect called\n");

	if (!device || !chip_data || !ts_dev) {
		TS_LOG_ERR("device, chip_data or ts_dev is NULL \n");
		return -ENOMEM;
	}

	rmi4_data = kzalloc(sizeof(*rmi4_data) * 2, GFP_KERNEL);
	if (!rmi4_data) {
		TS_LOG_ERR("Failed to alloc mem for struct rmi4_data\n");
		return -ENOMEM;
	}

	rmi4_data->current_page = MASK_8BIT;
	rmi4_data->synaptics_chip_data = chip_data;
	rmi4_data->synaptics_dev = ts_dev;
	rmi4_data->synaptics_dev->dev.of_node = device;
	if (g_ts_data.chip_data->delay_for_fw_update) {
		rmi4_data->reset_delay_ms = 150;
	} else {
		rmi4_data->reset_delay_ms = 100;
	}
#ifdef RED_REMOTE
	rmi4_data->fw_debug = false;
	rmi4_data->i2c_client = chip_data->client;
#endif
	rmi4_data->i2c_read = synaptics_rmi4_i2c_read;
	rmi4_data->i2c_write = synaptics_rmi4_i2c_write;
	rmi4_data->reset_device = synaptics_rmi4_reset_device;
	rmi4_data->status_resume = synaptics_rmi4_status_resume;
	rmi4_data->status_save = synaptics_rmi4_status_save;
	rmi4_data->report_touch = synaptics_rmi4_report_touch;

	rmi4_data->synaptics_chip_data->is_in_cell = true;
	rmi4_data->force_update = false;
	rmi4_data->sensor_max_x = rmi4_data->synaptics_chip_data->x_max - 1;
	rmi4_data->sensor_max_y = rmi4_data->synaptics_chip_data->y_max - 1;
	rmi4_data->sensor_max_x_mt =
	    rmi4_data->synaptics_chip_data->x_max_mt - 1;
	rmi4_data->sensor_max_y_mt =
	    rmi4_data->synaptics_chip_data->y_max_mt - 1;
	rmi4_data->flip_x =
	    rmi4_data->synaptics_chip_data->flip_x;
	rmi4_data->flip_y =
	    rmi4_data->synaptics_chip_data->flip_y;
	rmi4_data->synaptics_chip_data->easy_wakeup_info.sleep_mode =
	    TS_POWER_OFF_MODE;
	rmi4_data->synaptics_chip_data->easy_wakeup_info.easy_wakeup_gesture =
	    false;
	rmi4_data->synaptics_chip_data->easy_wakeup_info.easy_wakeup_flag =
	    false;
	rmi4_data->synaptics_chip_data->easy_wakeup_info.palm_cover_flag =
	    false;
	rmi4_data->synaptics_chip_data->easy_wakeup_info.palm_cover_control =
	    false;
	rmi4_data->synaptics_chip_data->easy_wakeup_info.off_motion_on = false;
#if defined (CONFIG_TEE_TUI)
	strncpy(synaptics_tui_data.device_name, "synaptics", strlen("synaptics"));
	synaptics_tui_data.device_name[strlen("synaptics")] = '\0';
	rmi4_data->synaptics_chip_data->tui_data = &synaptics_tui_data;
#endif
	retval = synaptics_regulator_get();
	if (retval < 0) {
		goto regulator_err;
	}

	retval = synaptics_gpio_request();
	if (retval < 0) {
		goto gpio_err;
	}

	retval = synaptics_pinctrl_get_init();
	if (retval < 0) {
		goto pinctrl_get_err;
	}

	/*power up the chip */
	synaptics_power_on();

	/*reset the chip */
	if (!chip_data->disable_reset) {
		synaptics_gpio_reset();
		TS_LOG_INFO("chip has been reset\n");
	} else {
		TS_LOG_INFO("chip not do reset\n");
	}
	/*for 3350/3320after 100ms, allowed i2c operation, for 3207, time need 250ms */
	msleep(250);

	retval = i2c_communicate_check();
	if (retval < 0) {
		TS_LOG_ERR("not find synaptics device\n");
		goto check_err;
	} else {
		TS_LOG_INFO("find synaptics device\n");
		goto out;
	}

out:
#ifdef ROI
	/*lint -esym(527,init_completion)*/
	init_completion(&roi_data_done);
	/*lint +esym(527,init_completion)*/
#endif
	TS_LOG_INFO("synaptics chip detect done\n");
	return NO_ERR;

check_err:
	synaptics_power_off();
pinctrl_get_err:
	synaptics_gpio_free();
gpio_err:
	synaptics_regulator_put();
regulator_err:
	if (rmi4_data)
		kfree(rmi4_data);
	rmi4_data = NULL;
	TS_LOG_ERR("no power\n");
	return retval;
}

/*    init the chip.
*
*     (1) power up;  (2) detect the chip thourgh bus(i2c).
*/
static int synaptics_wrong_touch(void)
{
	int rc = NO_ERR;
	mutex_lock(&wrong_touch_lock);
	rmi4_data->synaptics_chip_data->easy_wakeup_info.off_motion_on = true;
	mutex_unlock(&wrong_touch_lock);
	TS_LOG_INFO("done\n");
	return rc;
}

static int synaptics_init_fwu_info(void)
{
	int retval = 0;

	retval = synaptics_fw_data_s3718_init(rmi4_data);
	if (retval) {
		TS_LOG_ERR("%s, failed\n", __func__);
	}
	synaptics_fw_data_s3718_release();
	return retval;
}

static int synaptics_get_brightness_info(void)
{
	int error = NO_ERR;
	int bl_max_nit = 0;
	struct ts_oem_info_param *info =NULL;
	TS_LOG_INFO("%s: Enter\n", __func__);

	//setting the read brightness type
	memset(tp_type_cmd, 0x0, TS_CHIP_TYPE_MAX_SIZE);
	tp_type_cmd[0] = TS_CHIP_BRIGHTNESS_TYPE;

	if (TS_UNINIT == atomic_read(&g_ts_data.state)) {
		TS_LOG_INFO("%s:ts module not initialize\n", __func__);
		bl_max_nit = 0;
		return	bl_max_nit;
	}

	info =
	(struct ts_oem_info_param *)
		kzalloc(sizeof(struct ts_oem_info_param), GFP_KERNEL);
	if (!info) {
		TS_LOG_ERR("%s: malloc failed\n", __func__);
		error = -ENOMEM;
	goto out;
	}

	synaptics_get_oem_info( info);

	if(info->data[0] == 0x1) {
		TS_LOG_INFO("%s:brightness info is not find in TPIC FLASH\n", __func__);
		bl_max_nit = 0;
	} else {
		TS_LOG_INFO("%s:brightness info find in TPIC FLASH\n", __func__);
		bl_max_nit = info->data[3] << 8 | info->data[2];
	}

out:
	return bl_max_nit;
}

static int synaptics_init_chip(void)
{
	int rc = NO_ERR;
	int count = 0;
	unsigned char device_fastrate;
	mutex_init(&wrong_touch_lock);
	/*detect the chip */
	rc = synaptics_rmi4_query_device(rmi4_data);
	if (rc < 0) {
		TS_LOG_ERR("Failed to synaptics_rmi4_query_device\n");
		return rc;
	}
	rc = synaptics_init_fwu_info();
	if (rc < 0) {
		TS_LOG_ERR("%s,Failed to init fwu info\n", __func__);
		return rc;
	}

	synaptics_parse_chip_specific_dts(rmi4_data->synaptics_chip_data);

	if (SYNAPTICS_S3207 == rmi4_data->synaptics_chip_data->ic_type) {
		rc = synaptics_rmi4_i2c_read(rmi4_data, EASY_WAKEUP_FASTRATE,
					     &device_fastrate,
					     sizeof(device_fastrate));
		rmi4_data->synaptics_chip_data->easy_wakeup_info.
		    easy_wakeup_fastrate = device_fastrate;
		if (rc < 0) {
			TS_LOG_ERR("Failed to get FASTRATE info\n");
			return rc;
		}
	}
	for (count = 0;
	     synaptics_sett_param_regs_map[count].module_name != NULL;
	     count++) {
		switch (synaptics_sett_param_regs_map[count].ic_type) {
		case SYNAPTICS_S3207:
			if (SYNAPTICS_S3207 !=
			    rmi4_data->synaptics_chip_data->ic_type)
				break;
			if ((synaptics_sett_param_regs_map[count].build_id[0] ==
			     rmi4_data->rmi4_mod_info.synaptics_build_id[0])
			    && (synaptics_sett_param_regs_map[count].
				build_id[1] ==
				rmi4_data->rmi4_mod_info.synaptics_build_id[1])
			    && (synaptics_sett_param_regs_map[count].
				build_id[2] ==
				rmi4_data->rmi4_mod_info.
				synaptics_build_id[2])) {
				synaptics_sett_param_regs =
				    &synaptics_sett_param_regs_map[count];
				TS_LOG_INFO
				    ("SYNAPTICS_S3207 synaptics_sett_param_regs_map count is %d\n",
				     count);
				goto out;
			}
			break;
		case SYNAPTICS_S3350:
			if (SYNAPTICS_S3350 !=
			    rmi4_data->synaptics_chip_data->ic_type)
				break;
			synaptics_sett_param_regs =
			    &synaptics_sett_param_regs_map[count];
			TS_LOG_INFO
			    ("SYNAPTICS_S3350 synaptics_sett_param_regs_map count is %d\n",
			     count);
			goto out;
			break;
		case SYNAPTICS_S3320:
			if (SYNAPTICS_S3320 !=
			    rmi4_data->synaptics_chip_data->ic_type)
				break;
			synaptics_sett_param_regs =
			    &synaptics_sett_param_regs_map[count];
			TS_LOG_INFO
			    (" SYNAPTICS_S3320 synaptics_sett_param_regs_map count is %d\n",
			     count);
			goto out;
			break;
		case SYNAPTICS_S3718:
		case SYNAPTICS_TD4322:
		case SYNAPTICS_TD4300:
			if (SYNAPTICS_S3718 != rmi4_data->synaptics_chip_data->ic_type
				&& SYNAPTICS_TD4322 != rmi4_data->synaptics_chip_data->ic_type
				&& SYNAPTICS_TD4300 != rmi4_data->synaptics_chip_data->ic_type)
				break;
			synaptics_sett_param_regs =
			    &synaptics_sett_param_regs_map[count];
			TS_LOG_INFO
			    ("SYNAPTICS_S3718 synaptics_sett_param_regs_map count is %d\n",
			     count);
			goto out;
			break;
		}
	}
	synaptics_sett_param_regs = NULL;
	if (NULL == synaptics_sett_param_regs) {
		TS_LOG_ERR("no ic_type or module name is found\n");
		rc = -EINVAL;
	}
out:
	if (NULL != rmi4_data->module_name) {
		synaptics_sett_param_regs->module_name = rmi4_data->module_name;
	}
	TS_LOG_INFO("module id is %s\n",
		    synaptics_sett_param_regs->module_name);
	return rc;
}

static int synaptics_fw_update_boot(char *file_name)
{
	int retval = NO_ERR;
	bool need_update = false;
	int projectid_lenth = 0;

	if (rmi4_data->synaptics_chip_data->projectid_len) {
		projectid_lenth = rmi4_data->synaptics_chip_data->projectid_len;
	} else {
		projectid_lenth = PROJECT_ID_FW_LEN;
	}

#ifdef RED_REMOTE
	/*used for red remote fucntion */
	synaptics_fw_debug_dev_init(rmi4_data);
#endif

	TS_LOG_INFO("synaptics_fw_update_boot called\n");

	if (SYNAPTICS_S3718 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4322 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4300 != rmi4_data->synaptics_chip_data->ic_type) {
		retval = synaptics_fw_data_init(rmi4_data);
		if (retval) {
			TS_LOG_ERR("synaptics_fw_data_init failed\n");
			goto data_release;
		}
		strncat(file_name, rmi4_data->rmi4_mod_info.project_id_string,
			projectid_lenth);
		TS_LOG_INFO("file_name name is :%s\n", file_name);
		msleep(1000);
		retval =
		    synaptics_get_fw_data_boot(file_name,
					       synaptics_sett_param_regs);
		if (retval) {
			TS_LOG_ERR("load fw data from bootimage error\n");
			goto data_release;
		}

		need_update = synaptics_check_fw_version();

		if (rmi4_data->force_update || need_update) {
			retval = synaptics_fw_update();
			if (retval) {
				TS_LOG_ERR("failed update fw\n");
				strncpy(config_id_string,
					rmi4_data->rmi4_mod_info.
					device_config_id,
					strlen(rmi4_data->rmi4_mod_info.
					       device_config_id));
#if defined (CONFIG_HUAWEI_DSM)
				if (!dsm_client_ocuppy(tp_dclient)) {
					dsm_client_record(tp_dclient,
							  "fw update result: failed.\nupdata_status is %d.\n",
							  g_ts_data.dsm_info.
							  constraints_UPDATE_status);
					dsm_client_notify(tp_dclient,
							  DSM_TP_FWUPDATE_ERROR_NO);
				}
				strncpy(g_ts_data.dsm_info.fw_update_result,
					"failed", strlen("failed"));
#endif

			} else {
				TS_LOG_INFO("successfully update fw\n");
				strncpy(config_id_string,
					rmi4_data->rmi4_mod_info.
					image_config_id,
					strlen(rmi4_data->rmi4_mod_info.
					       image_config_id));
			}
		} else {
			strncpy(config_id_string,
				rmi4_data->rmi4_mod_info.device_config_id,
				strlen(rmi4_data->rmi4_mod_info.
				       device_config_id));
		}
	} else {
		retval = synaptics_fw_data_s3718_init(rmi4_data);
		if (retval) {
			TS_LOG_ERR("synaptics_fw_data_s3718_init failed\n");
			goto data_release;
		}
		strncat(file_name, rmi4_data->rmi4_mod_info.project_id_string,
			projectid_lenth);
		TS_LOG_INFO("file_name name is :%s\n", file_name);
		msleep(1000);
		retval =
		    synaptics_get_fw_data_s3718_boot(file_name,
						     synaptics_sett_param_regs);
		if (retval) {
			TS_LOG_ERR("load fw data from s3718 bootimage error\n");
			goto data_release;
		}

		need_update = synaptics_check_fw_s3718_version();

		if (rmi4_data->force_update || need_update) {
			retval = synaptics_fw_s3718_update();
			if (retval) {
				TS_LOG_ERR("failed update s3718 fw\n");
				strncpy(config_id_string,
					rmi4_data->rmi4_mod_info.
					device_config_id,
					strlen(rmi4_data->rmi4_mod_info.
					       device_config_id));
#if defined (CONFIG_HUAWEI_DSM)
				if (!dsm_client_ocuppy(tp_dclient)) {
					dsm_client_record(tp_dclient,
							  "fw update result: failed.\nupdata_status is %d.\n",
							  g_ts_data.dsm_info.
							  constraints_UPDATE_status);
					dsm_client_notify(tp_dclient,
							  DSM_TP_FWUPDATE_ERROR_NO);
				}
				strncpy(g_ts_data.dsm_info.fw_update_result,
					"failed", strlen("failed"));
#endif
			} else {
				TS_LOG_INFO("successfully s3718 update fw\n");
				strncpy(config_id_string,
					rmi4_data->rmi4_mod_info.
					image_config_id,
					strlen(rmi4_data->rmi4_mod_info.
					       image_config_id));
			}
		} else {
			strncpy(config_id_string,
				rmi4_data->rmi4_mod_info.device_config_id,
				strlen(rmi4_data->rmi4_mod_info.
				       device_config_id));
		}
	}

data_release:
	if (SYNAPTICS_S3718 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4322 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4300 != rmi4_data->synaptics_chip_data->ic_type)
		synaptics_fw_data_release();
	else
		synaptics_fw_data_s3718_release();
	if (1 != rmi4_data->synaptics_chip_data->unite_cap_test_interface) {
		if (SYNAPTICS_S3207 == rmi4_data->synaptics_chip_data->ic_type) {
			retval = synaptics_rmi4_f54_s3207_init(rmi4_data, synaptics_sett_param_regs->module_name);	/* for test report function*/
			if (retval) {
				TS_LOG_ERR("synaptics_rmi4_f54_init failed\n");
			}
		}
	}
	hisifb_esd_recover_disable(0);
	return retval;
}

static int synaptics_fw_update_sd(void)
{
	int retval = NO_ERR;

	TS_LOG_INFO("synaptics_fw_update_sd called\n");
	TS_LOG_INFO("ic_type = %d\n", rmi4_data->synaptics_chip_data->ic_type);
	synaptics_rmi4_status_save(rmi4_data);

	if (SYNAPTICS_S3718 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4322 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4300 != rmi4_data->synaptics_chip_data->ic_type) {
		retval = synaptics_fw_data_init(rmi4_data);
		if (retval) {
			TS_LOG_ERR("synaptics_fw_data_init failed\n");
			goto data_release;
		}
		msleep(1000);
		retval = synaptics_get_fw_data_sd();
		if (retval) {
			TS_LOG_ERR("load fw data from bootimage error\n");
			goto data_release;
		}

		/*just check the fw version */
		synaptics_check_fw_version();

		retval = synaptics_fw_update();
		if (retval < 0) {
			TS_LOG_ERR("failed update fw\n");
		} else {
			TS_LOG_INFO("success update fw\n");
		}
	} else {
		retval = synaptics_fw_data_s3718_init(rmi4_data);
		if (retval) {
			TS_LOG_ERR("synaptics_fw_data_s3718_init failed\n");
			goto data_release;
		}
		msleep(1000);
		retval = synaptics_get_fw_data_s3718_sd();
		if (retval) {
			TS_LOG_ERR("synaptics_get_fw_data_s3718_sd\n");
			goto data_release;
		}

		/*just check the fw version */
		synaptics_check_fw_s3718_version();

		retval = synaptics_fw_s3718_update();
		if (retval < 0) {
			TS_LOG_ERR("failed update s3718 fw\n");
		} else {
			TS_LOG_INFO("success update s3718 fw\n");
		}
	}

	synaptics_rmi4_status_resume(rmi4_data);
data_release:
	if (SYNAPTICS_S3718 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4322 != rmi4_data->synaptics_chip_data->ic_type
		&& SYNAPTICS_TD4300 != rmi4_data->synaptics_chip_data->ic_type)
		synaptics_fw_data_release();
	else
		synaptics_fw_data_s3718_release();
	return retval;
}

static int synaptics_regs_operate(struct ts_regs_info *info)
{
	int retval = NO_ERR;
	u8 value[TS_MAX_REG_VALUE_NUM] = { 0 };
	u8 value_tmp = info->values[0];
	int i = 0;

	TS_LOG_INFO("addr(%d),op_action(%d),bit(%d),num(%d)\n", info->addr,
		    info->op_action, info->bit, info->num);

	for (i = 0; i < info->num; i++) {
		TS_LOG_INFO("value[%d]=%d\n", i, info->values[i]);
	}
	switch (info->op_action) {
	case TS_ACTION_WRITE:
		for (i = 0; i < info->num; i++) {
			value[i] = info->values[i];
		}

		if ((1 == info->num) && (8 > info->bit)) {
			retval =
			    synaptics_rmi4_i2c_read(rmi4_data, info->addr,
						    value, info->num);
			if (retval < 0) {
				TS_LOG_ERR("TS_ACTION_READ error, addr(%d)\n",
					   info->addr);
				retval = -EINVAL;
				goto out;
			}

			if (0 == value_tmp) {
				value[0] &= ~(1 << info->bit);
			} else if (1 == value_tmp) {
				value[0] |= (1 << info->bit);
			}
		}

		retval =
		    synaptics_rmi4_i2c_write(rmi4_data, info->addr, value,
					     info->num);
		if (retval < 0) {
			TS_LOG_ERR("TS_ACTION_WRITE error, addr(%d)\n",
				   info->addr);
			retval = -EINVAL;
			goto out;
		}
		break;
	case TS_ACTION_READ:
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data, info->addr, value,
					    info->num);
		if (retval < 0) {
			TS_LOG_ERR("TS_ACTION_READ error, addr(%d)\n",
				   info->addr);
			retval = -EINVAL;
			goto out;
		}

		if ((1 == info->num) && (8 > info->bit)) {
			rmi4_data->synaptics_chip_data->reg_values[0] =
			    (value[0] >> info->bit) & 0x01;
		} else {
			for (i = 0; i < info->num; i++) {
				rmi4_data->synaptics_chip_data->reg_values[i] =
				    value[i];
			}
		}
		break;
	default:
		TS_LOG_ERR("%s, reg operate default invalid action %d\n",
			   __func__, info->op_action);
		retval = -EINVAL;
		break;
	}
out:
	return retval;
}
#if 0
/*
 * This effective window zone is defined in f51_ctrl x/y region reg,
 * from F51_CUSTOM_CTRL19 to 26 ,that is:
 * <x0_LSB>,<x0_MSB>,<y0_LSB>,<y0_MSB>,<x1_LSB>,<x1_MSB>,<y1_LSB>,<y1_MSB>;
 * We should change it when holster mode is enabled.
 */
static int s3320_set_effective_window(struct synaptics_rmi4_data *rmi4_data)
{
	int ret = 0;
	unsigned char f51_ctrl_19[S3320_HOLSTER_WINDOW_REG_BYTES] = { 0 };	/*record the zone read from/write to TP register*/
	unsigned char effective_window[S3320_HOLSTER_WINDOW_REG_BYTES] = { 0 };	/*new zone to be written to x/y region reg*/
	unsigned char f51_ctrl_15[4] = { 0 };	/*record the rx/tx cut of TP eage*/
	int i = 0;
	int x0 = g_ts_data.feature_info.window_info.top_left_x0;
	int y0 = g_ts_data.feature_info.window_info.top_left_y0;
	int x1 = g_ts_data.feature_info.window_info.bottom_right_x1;
	int y1 = g_ts_data.feature_info.window_info.bottom_right_y1;
	int x_lcd = g_ts_data.chip_data->x_max_mt;
	int y_lcd_all = g_ts_data.chip_data->y_max_mt;
	int max_x = rmi4_data->sensor_max_x;
	int max_y = rmi4_data->sensor_max_y;

	TS_LOG_DEBUG("%s:in! x_lcd=%d, y_lcd_all=%d,max_x=%d, max_y=%d \n",
		     __func__, g_ts_data.chip_data->x_max_mt,
		     g_ts_data.chip_data->y_max_mt, rmi4_data->sensor_max_x,
		     rmi4_data->sensor_max_y);

	TS_LOG_INFO("Holster window_info is (%d,%d)(%d,%d)\n", x0, y0, x1, y1);

	/* Transform LCD resolution to TP resolution */
	effective_window[0] = (char)(x0 * max_x / x_lcd);
	effective_window[1] =
	    (char)(((u16) (x0 * max_x / x_lcd) & ~MASK_8BIT) >> 8);
	effective_window[2] = (char)(y0 * max_y / y_lcd_all);
	effective_window[3] =
	    (char)(((u16) (y0 * max_y / y_lcd_all) & ~MASK_8BIT) >> 8);
	effective_window[4] = (char)(x1 * max_x / x_lcd);
	effective_window[5] =
	    (char)(((u16) (x1 * max_x / x_lcd) & ~MASK_8BIT) >> 8);
	effective_window[6] = (char)(y1 * max_y / y_lcd_all);
	effective_window[7] =
	    (char)(((u16) (y1 * max_y / y_lcd_all) & ~MASK_8BIT) >> 8);

	for (i = 0; i < S3320_HOLSTER_WINDOW_REG_BYTES; i++) {
		f51_ctrl_19[i] = effective_window[i];
		TS_LOG_INFO("New effective_window[%d] = %d\n", i,
			    effective_window[i]);
	}

	/* This window will only effect when HOLSTER_SWITCH was enabled */
	ret = synaptics_rmi4_i2c_write(rmi4_data,
				       rmi4_data->rmi4_feature.
				       f51_ctrl_base_addr +
				       S3320_F51_CUSTOM_CTRL19_OFFSET,
				       &f51_ctrl_19[0], sizeof(f51_ctrl_19));
	if (ret < 0) {
		TS_LOG_ERR("%s:new effective_window write error!ret = %d\n",
			   __func__, ret);
		return ret;
	} else {
		TS_LOG_INFO("%s: new effective_window is written success!\n",
			    __func__);
	}

	/* Effective window will firstly determined by tx/rx cut reg ,so we need to clear it */
	/* here to Make sure that this window will only be determined by x/y region reg */
	ret = synaptics_rmi4_i2c_write(rmi4_data,
				       rmi4_data->rmi4_feature.
				       f51_ctrl_base_addr +
				       S3320_F51_CUSTOM_CTRL15_OFFSET,
				       &f51_ctrl_15[0], sizeof(f51_ctrl_15));
	if (ret < 0) {
		TS_LOG_ERR("%s:erase effective_window cut error!ret = %d\n",
			   __func__, ret);
	}

	return ret;
}
#endif
static int synaptics_set_wakeup_gesture_enable_switch(u8 enable)
{
	int retval = NO_ERR;
	u8 holster_temp_value;
	unsigned short holster_enable_addr;
	unsigned char holster_bit_num;

	holster_enable_addr =
	    g_ts_data.feature_info.holster_info.holster_switch_addr;
	holster_bit_num =
	    g_ts_data.feature_info.holster_info.holster_switch_bit;
	TS_LOG_INFO
	    ("%s, synaptics holster_enable_addr=0x%04x, holster_bit_num=%d\n",
	     __func__, holster_enable_addr, holster_bit_num);

	if (!holster_enable_addr) {
		TS_LOG_ERR("%s, holster_enable_addr is null.\n", __func__);
		goto out;
	}

	retval =
	    synaptics_rmi4_i2c_read(rmi4_data, holster_enable_addr,
				    &holster_temp_value, 1);
	if (retval < 0) {
		TS_LOG_ERR("read holster information failed: %d\n", retval);
		goto out;
	}
	if (!enable) {
		holster_temp_value |= 1 << holster_bit_num;
	} else {
		holster_temp_value &= ~(1 << holster_bit_num);
	}

	TS_LOG_INFO("%s, write TP IC\n", __func__);
	retval =
	    synaptics_rmi4_i2c_write(rmi4_data, holster_enable_addr,
				     &holster_temp_value, 1);
	if (retval < 0) {
		TS_LOG_ERR("switch wakeup gesture enable mode failed: %d\n",
			   retval);
	}
out:
	return retval;
}

#if defined(HUAWEI_CHARGER_FB)
static int synaptics_set_charger_switch(u8 charger_switch)
{
	int retval = NO_ERR;
	u8 charger_temp_value;
	unsigned short charger_enable_addr;
	unsigned char charger_bit_num;

	charger_enable_addr =
	    g_ts_data.feature_info.charger_info.charger_switch_addr;
	charger_bit_num =
	    g_ts_data.feature_info.charger_info.charger_switch_bit;
	TS_LOG_INFO
	    ("synaptics charger_enable_addr=0x%04x, charger_bit_num=%d\n",
	     charger_enable_addr, charger_bit_num);

	if (!charger_enable_addr) {
		TS_LOG_ERR
		    ("charger_enable_addr is null, charger feature is not supported.\n");
		goto out;
	}

	retval =
	    synaptics_rmi4_i2c_read(rmi4_data, charger_enable_addr,
				    &charger_temp_value, 1);
	if (retval < 0) {
		TS_LOG_ERR("read charger information failed: %d\n", retval);
		goto out;
	}
	if (charger_switch) {
		charger_temp_value |= 1 << charger_bit_num;
	} else {
		charger_temp_value &= ~(1 << charger_bit_num);
	}

	retval =
	    synaptics_rmi4_i2c_write(rmi4_data, charger_enable_addr,
				     &charger_temp_value, 1);
	if (retval < 0) {
		TS_LOG_ERR("write charger information failed: %d\n", retval);
	}
out:
	TS_LOG_INFO("%s, write TP IC, addr=0x%04x, value=0x%04x\n", __func__,
		    charger_enable_addr, charger_temp_value);
	return retval;
}
#endif

static int synaptics_charger_switch(struct ts_charger_info *info)
{
	int retval = NO_ERR;

#if defined(HUAWEI_CHARGER_FB)
	if (!info) {
		TS_LOG_ERR("%s: info is Null\n", __func__);
		retval = -ENOMEM;
		return retval;
	}

	switch (info->op_action) {
	case TS_ACTION_WRITE:
		retval = synaptics_set_charger_switch(info->charger_switch);
		if (retval < 0) {
			TS_LOG_ERR("set charger switch(%d), failed: %d\n",
				   info->charger_switch, retval);
		}
		break;
	default:
		TS_LOG_INFO("%s, invalid cmd\n", __func__);
		retval = -EINVAL;
		break;
	}
#endif

	return retval;
}

static int synaptics_set_holster_switch(u8 holster_switch)
{
	int retval = NO_ERR;
	int holster_temp_value;
	unsigned short holster_enable_addr;
	unsigned char holster_bit_num;

	TS_LOG_INFO("synaptics_set_holster_switch called\n");

	holster_enable_addr =
	    g_ts_data.feature_info.holster_info.holster_switch_addr;
	holster_bit_num =
	    g_ts_data.feature_info.holster_info.holster_switch_bit;
	TS_LOG_INFO
	    ("synaptics holster_enable_addr=0x%04x, holster_bit_num=%d\n",
	     holster_enable_addr, holster_bit_num);

	if (!holster_enable_addr) {
		TS_LOG_ERR
		    ("holster_enable_addr is null, hoslter feature is not supported.\n");
		goto out;
	}

	retval =
	    synaptics_rmi4_i2c_read(rmi4_data, holster_enable_addr,
				    (unsigned char *)&holster_temp_value, 1);
	if (retval < 0) {
		TS_LOG_ERR("read holster information failed: %d\n", retval);
		goto out;
	}
	if (holster_switch) {
		holster_temp_value |= 1 << holster_bit_num;
	} else {
		holster_temp_value &= ~(1 << holster_bit_num);
	}

	retval =
	    synaptics_rmi4_i2c_write(rmi4_data, holster_enable_addr,
				     (unsigned char *)&holster_temp_value, 1);
	if (retval < 0) {
		TS_LOG_ERR("write holster information failed: %d\n", retval);
	}
out:
	return retval;
}

static int synaptics_holster_switch(struct ts_holster_info *info)
{
	int retval = NO_ERR;

	if (!info) {
		TS_LOG_ERR("synaptics_holster_switch: info is Null\n");
		retval = -ENOMEM;
		return retval;
	}

	switch (info->op_action) {
	case TS_ACTION_WRITE:
		retval = synaptics_set_holster_switch(info->holster_switch);
		if (retval < 0) {
			TS_LOG_ERR("set holster switch(%d), failed: %d\n",
				   info->holster_switch, retval);
		}
		break;
	case TS_ACTION_READ:
		TS_LOG_INFO
		    ("invalid holster switch(%d) action: TS_ACTION_READ\n",
		     info->holster_switch);
		break;
	default:
		TS_LOG_INFO("invalid holster switch(%d) action: %d\n",
			    info->holster_switch, info->op_action);
		retval = -EINVAL;
		break;
	}

	return retval;
}

static int synaptics_set_roi_switch(u8 roi_switch)
{
	int retval = NO_ERR;
	int i;
	unsigned short roi_ctrl_addr = 0;
	u8 roi_control_bit, temp_roi_switch;

#ifdef ROI
	if (!f51found)
		return -ENODEV;

	roi_ctrl_addr = g_ts_data.feature_info.roi_info.roi_control_addr;
	roi_control_bit = g_ts_data.feature_info.roi_info.roi_control_bit;
	TS_LOG_INFO
	    ("roi_ctrl_write_addr=0x%04x, roi_control_bit=%d, roi_switch=%d\n",
	     roi_ctrl_addr, roi_control_bit, roi_switch);

	if (!roi_ctrl_addr) {
		TS_LOG_ERR
		    ("roi_ctrl_addr is null, roi feature is not supported.\n");
		goto out;
	}

	retval =
	    synaptics_rmi4_i2c_read(rmi4_data, roi_ctrl_addr, &temp_roi_switch,
				    1);
	if (retval < 0) {
		TS_LOG_ERR("read roi_control value information failed: %d\n",
			   retval);
		return retval;
	}

	if (roi_switch)
		temp_roi_switch |= (1 << roi_control_bit);
	else
		temp_roi_switch &= (~(1 << roi_control_bit));

	retval =
	    synaptics_rmi4_i2c_write(rmi4_data, roi_ctrl_addr, &temp_roi_switch,
				     1);
	if (retval < 0) {
		TS_LOG_ERR
		    ("set roi switch failed: %d, roi_ctrl_write_addr=0x%04x\n",
		     retval, roi_ctrl_addr);
		return retval;
	}
	f51_roi_switch = temp_roi_switch;
	if (!roi_switch) {
		for (i = 0; i < ROI_DATA_READ_LENGTH; i++) {
			roi_data[i] = 0;
		}
	}
#endif
out:
	return retval;
}

static int synaptics_read_roi_switch(void)
{
	int retval = NO_ERR;
	unsigned short roi_ctrl_addr = 0;
	u8 roi_control_bit, roi_switch;
#ifdef ROI
	if (!f51found)
		return -ENODEV;

	roi_ctrl_addr = g_ts_data.feature_info.roi_info.roi_control_addr;
	roi_control_bit = g_ts_data.feature_info.roi_info.roi_control_bit;

	if (!roi_ctrl_addr) {
		TS_LOG_ERR
		    ("roi_ctrl_addr is null, roi feature is not supported.\n");
		goto out;
	}

	retval =
	    synaptics_rmi4_i2c_read(rmi4_data, roi_ctrl_addr, &roi_switch,
				    sizeof(roi_switch));
	if (retval < 0) {
		TS_LOG_ERR("read roi switch failed: %d\n", retval);
		return retval;
	}
	roi_switch &= (1 << roi_control_bit);
	g_ts_data.feature_info.roi_info.roi_switch = roi_switch;
	f51_roi_switch = roi_switch;
#endif
out:
	TS_LOG_INFO("roi_ctrl_read_addr=0x%04x, roi_switch=%d\n", roi_ctrl_addr,
		    roi_switch);
	return retval;
}

static int synaptics_roi_switch(struct ts_roi_info *info)
{
	int retval = NO_ERR;

#ifdef ROI
	if (!info) {
		TS_LOG_ERR("synaptics_roi_switch: info is Null\n");
		retval = -ENOMEM;
		return retval;
	}

	switch (info->op_action) {
	case TS_ACTION_WRITE:
		retval = synaptics_set_roi_switch(info->roi_switch);
		if (retval < 0) {
			TS_LOG_ERR("%s, synaptics_set_roi_switch faild\n",
				   __func__);
		}
		break;
	case TS_ACTION_READ:
		retval = synaptics_read_roi_switch();
		break;
	default:
		TS_LOG_INFO("invalid roi switch(%d) action: %d\n",
			    info->roi_switch, info->op_action);
		retval = -EINVAL;
		break;
	}
#endif
	return retval;
}

static unsigned char *synaptics_roi_rawdata(void)
{
#ifdef ROI
	if (!f51found)
		return NULL;

	if (f51_roi_switch)  {
		if (roi_data_staled)  {  /* roi_data may be refreshing now, wait it for some time(30ms). */
			if (!wait_for_completion_interruptible_timeout(&roi_data_done, msecs_to_jiffies(30))) {
				roi_data_staled = 0;  /* Never wait again if data refreshing gets timeout. */
				memset(roi_data, 0, sizeof(roi_data));
			}
		}
	}

	return (unsigned char *)roi_data;
#else
	return NULL;
#endif
}

static int synaptics_do_calibrate(unsigned char write_value, int count)
{
	int ret = NO_ERR;
	u8 value = 1;
	int delay_time = 200;
	unsigned short addr;

	count = count / delay_time;

	if (strncmp
	    (rmi4_data->rmi4_mod_info.product_id_string, "S332U",
	     strlen("S332U"))) {
		TS_LOG_INFO("%s, not S332U, no need to calibrate\n", __func__);
		goto out;
	}

	addr =
	    synaptics_f54_get_calibrate_addr(rmi4_data,
					     synaptics_sett_param_regs->
					     module_name);
	if (!addr) {
		TS_LOG_ERR("%s, get addr error!\n", __func__);
		ret = -ENOMEM;
		goto out;
	}

	synaptics_rmi4_i2c_write(rmi4_data, addr, &write_value, 1);
	do {
		count--;
		synaptics_rmi4_i2c_read(rmi4_data, addr, &value, sizeof(value));
		TS_LOG_INFO("remain count = %d, value is 0x%04x\n", count,
			    value);
		if (!value) {
			TS_LOG_INFO("%s success\n", __func__);
			goto out;
		}
		msleep(delay_time);
	} while (count > 0);
	ret = -ENOMEM;
	TS_LOG_ERR("%s timeout\n", __func__);

out:
	return ret;

}

/*calirate in sleepin
  1. Write 0x02 to F54_CTRL + 0x2C.
  2. Read value from F54_CTRL + 0x2C until it becomes 0.
*/
static int synaptics_calibrate_wakeup_gesture(void)
{
	int count = 24000;
	unsigned char value = 0x02;
	int ret = NO_ERR;

	ret = synaptics_do_calibrate(value, count);
	if (ret) {
		TS_LOG_ERR("%s error\n", __func__);
	}

	return ret;
}

/*display on*/
/*calibrate in sleepout
  1. Write 0x01 to F54_CTRL + 0x2C.
  2. Read value from F54_CTRL + 0x2C until it becomes 0.*/
static int synaptics_calibrate(void)
{
	int count = 24000;
	unsigned char value = 0x01;
	int ret = NO_ERR;

	ret = synaptics_do_calibrate(value, count);
	if (ret) {
		TS_LOG_ERR("%s error\n", __func__);
	}

	return ret;
}

static int synaptics_get_glove_switch(u8 *glove_switch)
{
	int retval = NO_ERR;
	unsigned short glove_enable_addr;
	unsigned char glove_bit_num;
	u8 value = 0;

	if (!glove_switch) {
		TS_LOG_ERR
		    ("synaptics_get_glove_switch: glove_switch is Null\n");
		return -ENOMEM;
	}

	glove_enable_addr = g_ts_data.feature_info.glove_info.glove_switch_addr;
	glove_bit_num = g_ts_data.feature_info.glove_info.glove_switch_bit;
	TS_LOG_INFO("synaptics glove_enable_addr=%d, glove_bit_num=%d\n",
		    glove_enable_addr, glove_bit_num);

	if (!glove_enable_addr) {
		TS_LOG_ERR
		    ("glove_enable_addr is null, glove feature is not supported.\n");
		goto out;
	}

	retval =
	    synaptics_rmi4_i2c_read(rmi4_data, glove_enable_addr, &value,
				    sizeof(value));
	if (retval < 0) {
		TS_LOG_ERR("read glove switch(%d) err : %d\n", *glove_switch,
			   retval);
		goto out;
	}

	if (!(value & (1 << glove_bit_num))) {
		*glove_switch = GLOVE_SWITCH_OFF;
	} else {
		*glove_switch = GLOVE_SWITCH_ON;
	}

out:
	TS_LOG_DEBUG("synaptics_get_glove_switch done : %d\n", *glove_switch);
	return retval;
}

static int synaptics_set_glove_switch(u8 glove_switch)
{
	int retval = NO_ERR;
	int glove_temp_value;
	unsigned short glove_enable_addr;
	unsigned char glove_bit_num;

	TS_LOG_INFO("synaptics_set_glove_switch called\n");

	glove_enable_addr = g_ts_data.feature_info.glove_info.glove_switch_addr;
	glove_bit_num = g_ts_data.feature_info.glove_info.glove_switch_bit;
	TS_LOG_INFO("synaptics glove_enable_addr=%d, glove_bit_num=%d\n",
		    glove_enable_addr, glove_bit_num);

	if (!glove_enable_addr) {
		TS_LOG_ERR
		    ("glove_enable_addr is null, glove feature is not supported.\n");
		goto out;
	}

	retval =
	    synaptics_rmi4_i2c_read(rmi4_data, glove_enable_addr,
				    (unsigned char *)&glove_temp_value, 1);
	if (retval < 0) {
		TS_LOG_ERR("read glove information failed: %d\n", retval);
		goto out;
	}
	if (glove_switch) {
		glove_temp_value |= 1 << glove_bit_num;
	} else {
		glove_temp_value &= ~(1 << glove_bit_num);
	}

	retval =
	    synaptics_rmi4_i2c_write(rmi4_data, glove_enable_addr,
				     (unsigned char *)&glove_temp_value, 1);
	if (retval < 0) {
		TS_LOG_ERR("write glove information failed: %d\n", retval);
	}
out:
	return retval;
}

static int synaptics_glove_switch(struct ts_glove_info *info)
{
	int retval = NO_ERR;
	u8 buf = 0;

	if (!info) {
		TS_LOG_ERR("synaptics_glove_switch: info is Null\n");
		retval = -ENOMEM;
		return retval;
	}
	switch (info->op_action) {
	case TS_ACTION_READ:
		retval = synaptics_get_glove_switch(&buf);
		if (retval < 0) {
			TS_LOG_ERR("get glove switch(%d), failed : %d",
				   info->glove_switch, retval);
			break;
		}
		info->glove_switch = buf;
		TS_LOG_INFO("read_glove_switch=%d, 1:on 0:off\n",
			    info->glove_switch);
		break;
	case TS_ACTION_WRITE:
		buf = info->glove_switch;
		TS_LOG_INFO("write_glove_switch=%d\n", info->glove_switch);
		if ((GLOVE_SWITCH_ON != info->glove_switch)
		    && (GLOVE_SWITCH_OFF != info->glove_switch)) {
			TS_LOG_ERR("write wrong state: buf = %d\n", buf);
			retval = -EFAULT;
			break;
		}
		retval = synaptics_set_glove_switch(buf);
		if (retval < 0) {
			TS_LOG_ERR("set glove switch(%d), failed : %d", buf,
				   retval);
		}
		break;
	default:
		TS_LOG_ERR("invalid switch status: %d", info->glove_switch);
		retval = -EINVAL;
		break;
	}

	return retval;
}

static int synaptics_chip_get_capacitance_test_type(struct ts_test_type_info
						    *info)
{
	int retval = NO_ERR;

	if (!info) {
		TS_LOG_ERR
		    ("synaptics_chip_get_capacitance_test_type: info is Null\n");
		retval = -ENOMEM;
		return retval;
	}
	switch (info->op_action) {
	case TS_ACTION_READ:
		memcpy(info->tp_test_type,
		       rmi4_data->synaptics_chip_data->tp_test_type,
		       TS_CAP_TEST_TYPE_LEN);
		TS_LOG_INFO("read_chip_get_test_type=%s, \n",
			    info->tp_test_type);
		break;
	case TS_ACTION_WRITE:
		break;
	default:
		TS_LOG_ERR("invalid status: %s", info->tp_test_type);
		retval = -EINVAL;
		break;
	}
	return retval;
}

static int synaptics_get_palm_switch(u8 *palm_switch)
{
	int retval = NO_ERR;
	unsigned char palm_enable_addr = 0;
	unsigned char palm_enable_offset = 0;

	if (!palm_switch) {
		TS_LOG_ERR("synaptics_get_palm_switch: palm_switch is Null\n");
		return -ENOMEM;
	}
	if (SYNAPTICS_S3207 == rmi4_data->synaptics_chip_data->ic_type) {
		*palm_switch =
		    rmi4_data->synaptics_chip_data->easy_wakeup_info.
		    palm_cover_flag;
	} else {
		palm_enable_offset =
		    rmi4_data->rmi4_feature.geswakeup_feature.
		    f12_2d_ctrl22_palm;
		palm_enable_addr =
		    rmi4_data->rmi4_feature.f12_ctrl_base_addr +
		    palm_enable_offset;
		TS_LOG_INFO("get palm addr : 0x%02x\n", palm_enable_addr);

		retval =
		    synaptics_rmi4_i2c_read(rmi4_data, palm_enable_addr,
					    palm_switch, sizeof(*palm_switch));
		if (retval < 0) {
			TS_LOG_ERR("read palm switch(%d) err : %d\n",
				   *palm_switch, retval);
			goto out;
		}
	}

	TS_LOG_DEBUG("synaptics_get_palm_switch done : %d\n", *palm_switch);
out:
	return retval;
}

static int synaptics_set_palm_switch(u8 palm_switch)
{
	int retval = NO_ERR;
	unsigned char palm_enable_addr = 0;
	unsigned char palm_enable_offset = 0;
	if (SYNAPTICS_S3207 == rmi4_data->synaptics_chip_data->ic_type) {
		TS_LOG_INFO
		    ("just set palm_contrlo_flag = control for S3207, palm_switch = %d\n",
		     palm_switch);
		rmi4_data->synaptics_chip_data->easy_wakeup_info.
		    palm_cover_flag =
		    rmi4_data->synaptics_chip_data->easy_wakeup_info.
		    palm_cover_control;
	} else {
		palm_enable_offset =
		    rmi4_data->rmi4_feature.geswakeup_feature.
		    f12_2d_ctrl22_palm;
		palm_enable_addr =
		    rmi4_data->rmi4_feature.f12_ctrl_base_addr +
		    palm_enable_offset;
		TS_LOG_INFO
		    ("set palm addr : 0x%02x , value(%d) (1:close) (0:open)\n",
		     palm_enable_addr, palm_switch);

		retval =
		    synaptics_rmi4_i2c_write(rmi4_data, palm_enable_addr,
					     &palm_switch, 1);
		if (retval < 0) {
			TS_LOG_ERR("open palm function failed: %d\n", retval);
		}
	}
	return retval;
}

static int synaptics_palm_switch(struct ts_palm_info *info)
{
	int retval = NO_ERR;
	u8 buf = 0;

	if (!info) {
		TS_LOG_ERR("synaptics_palm_set_switch: info is Null\n");
		retval = -ENOMEM;
		return retval;
	}
	switch (info->op_action) {
	case TS_ACTION_READ:
		if (SYNAPTICS_S3207 == rmi4_data->synaptics_chip_data->ic_type) {
			info->palm_switch =
			    rmi4_data->synaptics_chip_data->easy_wakeup_info.
			    palm_cover_flag;
		} else {
			retval = synaptics_get_palm_switch(&buf);
			if (retval < 0) {
				TS_LOG_ERR
				    ("get glove switch(%d), failed : %d\n",
				     info->palm_switch, retval);
			}
			if ((buf & PALM_REG_BIT) == 1) {	/*palm close status :1 plam invald*/
				info->palm_switch = 0;
			} else if ((buf & PALM_REG_BIT) == 0) {	/*palm open status :0 palm int - sleep*/
				info->palm_switch = 1;
			} else {
				TS_LOG_ERR("wrong state: buf = %d\n", buf);
				retval = -EFAULT;
			}
		}
		break;
	case TS_ACTION_WRITE:
		if (info->palm_switch == 1) {
			buf = 0;	/*open the palm function*/
		} else if (info->palm_switch == 0) {
			buf = 1;	/*close the palm function*/
		} else {
			TS_LOG_ERR("wrong input : %d\n", info->palm_switch);
			buf = 1;
		}
		retval = synaptics_set_palm_switch(buf);
		if (retval < 0) {
			TS_LOG_ERR("set palm switch(%d), failed : %d\n", buf,
				   retval);
		}
		break;
	default:
		TS_LOG_ERR("invalid switch status: %d\n", info->palm_switch);
		retval = -EINVAL;
		break;
	}

	return retval;
}

static void synaptics_shutdown(void)
{
	TS_LOG_INFO("synaptics_shutdown\n");
	synaptics_power_off();
	synaptics_gpio_free();
	synaptics_regulator_put();
	return;
}

/*  do some things before power off.
*/
static int synaptics_before_suspend(void)
{
	int retval = NO_ERR;

	TS_LOG_INFO("before_suspend +\n");
	TS_LOG_INFO("before_suspend -\n");
	return retval;
}

static void synaptics_put_device_into_easy_wakeup(void)
{
	int retval;
	unsigned char device_ctrl;
	unsigned char device_ctrl_data[4] = { 0 };
	unsigned short f12_ctrl_base = 0;
	unsigned char gusture_ctrl_offset = 0;
	struct ts_easy_wakeup_info *info =
	    &rmi4_data->synaptics_chip_data->easy_wakeup_info;
	TS_LOG_DEBUG
	    ("synaptics_put_device_into_easy_wakeup  info->easy_wakeup_flag =%x \n",
	     info->easy_wakeup_flag);
	/*if the sleep_gesture_flag is ture,it presents that  the tp is at sleep state*/

	if (true == info->easy_wakeup_flag) {
		TS_LOG_INFO
		    ("synaptics_put_device_into_easy_wakeup  info->easy_wakeup_flag =%x \n",
		     info->easy_wakeup_flag);
		return;
	}
	if (SYNAPTICS_S3207 == rmi4_data->synaptics_chip_data->ic_type) {
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    rmi4_data->rmi4_feature.
					    f11_ctrl_base_addr, &device_ctrl,
					    sizeof(device_ctrl));
		if (retval < 0) {
			TS_LOG_ERR(" Failed to enter sleep mode1\n");
			rmi4_data->sensor_sleep = false;
			return;
		}
		device_ctrl = (device_ctrl & ~MASK_3BIT);	/*get the high five bits,i'dont*/
		device_ctrl = (device_ctrl | 0x04);	/*easy-wakeup bit*/
		retval =
		    synaptics_rmi4_i2c_write(rmi4_data,
					     rmi4_data->rmi4_feature.
					     f11_ctrl_base_addr, &device_ctrl,
					     sizeof(device_ctrl));
		if (retval < 0) {
			TS_LOG_ERR("Failed to enter sleep mode2\n");
			rmi4_data->sensor_sleep = false;
			return;
		} else {
			rmi4_data->sensor_sleep = true;
		}
		/*set fast_rate */
		device_ctrl = 0x07;
		retval =
		    synaptics_rmi4_i2c_write(rmi4_data, EASY_WAKEUP_FASTRATE,
					     &device_ctrl, sizeof(device_ctrl));
		if (retval < 0) {
			TS_LOG_ERR("Failed to set fastrate\n");
			rmi4_data->sensor_sleep = false;
			return;
		} else {
			rmi4_data->sensor_sleep = true;
		}
		TS_LOG_DEBUG
		    (" read from  f11_ctrl_base_addr92  rmi4_data->f11_ctrl_base_addr  = 0x%04x rmi4_data->f11_ctrl_base_addr+92 =0x%04x\n",
		     rmi4_data->rmi4_feature.f11_ctrl_base_addr,
		     rmi4_data->rmi4_feature.f11_ctrl_base_addr + 45);

		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    rmi4_data->rmi4_feature.
					    f11_ctrl_base_addr + 45,
					    &device_ctrl, sizeof(device_ctrl));
		if (retval < 0) {
			TS_LOG_ERR("%s: Failed to set wakeup mode3\n",
				   __func__);
			rmi4_data->sensor_sleep = false;
			return;
		} else {
			rmi4_data->sensor_sleep = true;
		}
		TS_LOG_DEBUG
		    (" read from  f11_ctrl_base_addr92  ctrl1 = %0x retval =%0x\n",
		     device_ctrl, retval);

		retval =
		    synaptics_rmi4_i2c_read(rmi4_data, F54_ANALOG_CMD0,
					    &device_ctrl, sizeof(device_ctrl));
		if (retval < 0) {
			TS_LOG_ERR("Failed to set wakeup mode7\n");
			rmi4_data->sensor_sleep = false;
			return;
		} else {
			rmi4_data->sensor_sleep = true;
		}

		device_ctrl = device_ctrl | 0x04;
		TS_LOG_DEBUG
		    (" read from  f11_ctrl_base_addr92  ctrl1 = %0x retval =%0x\n",
		     device_ctrl, retval);
		retval =
		    synaptics_rmi4_i2c_write(rmi4_data, F54_ANALOG_CMD0,
					     &device_ctrl, sizeof(device_ctrl));
		if (retval < 0) {
			TS_LOG_ERR("Failed to set wakeup mode8\n");
			rmi4_data->sensor_sleep = false;
			return;
		} else {
			rmi4_data->sensor_sleep = true;
		}
	} else {
		gusture_ctrl_offset =
		    rmi4_data->rmi4_feature.geswakeup_feature.f12_2d_ctrl20_lpm;
		f12_ctrl_base = rmi4_data->rmi4_feature.f12_ctrl_base_addr;
		/*reg Report Wakeup Gesture Only read first */
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    f12_ctrl_base + gusture_ctrl_offset,
					    &device_ctrl_data[0],
					    sizeof(device_ctrl_data));
		if (retval < 0) {
			TS_LOG_ERR
			    ("read Wakeup Gesture Only reg F12_2D_CTRL20 fail !\n");
		} else {
			TS_LOG_DEBUG
			    ("read Wakeup Gesture Only reg F12_2D_CTRL20(00)/00 Motion Suppression : CTRL20(00)/00 : 0x%02x  CTRL20(00)/01 : 0x%02x CTRL20(01)/00 : 0x%02x CTRL20(04)/00 : 0x%02x\n",
			     device_ctrl_data[0], device_ctrl_data[1],
			     device_ctrl_data[2], device_ctrl_data[3]);
		}

		/*Report Wakeup Gesture Only set bit 1 */
		device_ctrl_data[2] =
		    device_ctrl_data[2] | GESTURE_ENABLE_BIT01;

		/*Wakeup Gesture Only bit(01) set 1 */
		retval =
		    synaptics_rmi4_i2c_write(rmi4_data,
					     f12_ctrl_base +
					     gusture_ctrl_offset,
					     &device_ctrl_data[0],
					     sizeof(device_ctrl_data));
		if (retval < 0) {
			TS_LOG_ERR
			    ("easy wake up suspend write Wakeup Gesture Only reg fail !\n");
		} else {
			TS_LOG_INFO
			    ("easy wake up suspend write Wakeup Gesture Only reg OK address(0x%02x) valve(0x%02x)\n",
			     f12_ctrl_base + gusture_ctrl_offset,
			     device_ctrl_data[2]);
		}
	}
	info->easy_wakeup_flag = true;
	return;
}

static void synaptics_put_device_outof_easy_wakeup(struct synaptics_rmi4_data
						   *rmi4_data)
{
	int retval;
	unsigned char device_ctrl;
	unsigned char device_ctrl_data[4] = { 0 };
	unsigned short f12_ctrl_base = 0;
	unsigned char gusture_ctrl_offset = 0;
	struct ts_easy_wakeup_info *info =
	    &rmi4_data->synaptics_chip_data->easy_wakeup_info;

	TS_LOG_DEBUG
	    ("synaptics_put_device_outof_easy_wakeup  info->easy_wakeup_flag =%d\n",
	     info->easy_wakeup_flag);

	if (false == info->easy_wakeup_flag) {
		return;
	}
	if (SYNAPTICS_S3207 == rmi4_data->synaptics_chip_data->ic_type) {
		/*set fastrate*/
		device_ctrl =
		    rmi4_data->synaptics_chip_data->easy_wakeup_info.
		    easy_wakeup_fastrate;
		retval =
		    synaptics_rmi4_i2c_write(rmi4_data, EASY_WAKEUP_FASTRATE,
					     &device_ctrl, sizeof(device_ctrl));
		if (retval < 0) {
			TS_LOG_ERR("Failed to out of  sleep mode1\n");
			rmi4_data->sensor_sleep = true;
			return;
		}
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    rmi4_data->rmi4_feature.
					    f11_ctrl_base_addr, &device_ctrl,
					    sizeof(device_ctrl));
		if (retval < 0) {
			TS_LOG_ERR("Failed to out of  sleep mode4\n");
			rmi4_data->sensor_sleep = true;
			return;
		}
		device_ctrl = ((device_ctrl & (~MASK_3BIT)) | MASK_1BIT);
		retval =
		    synaptics_rmi4_i2c_write(rmi4_data,
					     rmi4_data->rmi4_feature.
					     f11_ctrl_base_addr, &device_ctrl,
					     sizeof(device_ctrl));
		if (retval < 0) {
			TS_LOG_ERR("Failed to out of  sleep mode5\n");
			rmi4_data->sensor_sleep = true;
			return;
		} else {
			rmi4_data->sensor_sleep = false;
		}
	} else {
		gusture_ctrl_offset =
		    rmi4_data->rmi4_feature.geswakeup_feature.f12_2d_ctrl20_lpm;
		f12_ctrl_base = rmi4_data->rmi4_feature.f12_ctrl_base_addr;
		/*reg Report Wakeup Gesture Only read first */
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    f12_ctrl_base + gusture_ctrl_offset,
					    &device_ctrl_data[0],
					    sizeof(device_ctrl_data));
		if (retval < 0) {
			TS_LOG_ERR
			    ("read Wakeup Gesture Only reg F12_2D_CTRL20 fail !\n");
		} else {
			TS_LOG_DEBUG
			    ("read Wakeup Gesture Only reg F12_2D_CTRL20(00)/00 Motion Suppression : CTRL20(00)/00 : 0x%02x  CTRL20(00)/01 : 0x%02x CTRL20(01)/00 : 0x%02x CTRL20(04)/00 : 0x%02x\n",
			     device_ctrl_data[0], device_ctrl_data[1],
			     device_ctrl_data[2], device_ctrl_data[3]);
		}

		/*Report Wakeup Gesture Only set bit 0 */
		device_ctrl_data[2] =
		    device_ctrl_data[2] & (~GESTURE_ENABLE_BIT01);

		/*Wakeup Gesture Only bit(01) set 0 */
		retval =
		    synaptics_rmi4_i2c_write(rmi4_data,
					     f12_ctrl_base +
					     gusture_ctrl_offset,
					     &device_ctrl_data[0],
					     sizeof(device_ctrl_data));
		if (retval < 0) {
			TS_LOG_ERR
			    ("easy wake up resume write Wakeup Gesture Only reg fail\n");
		} else {
			TS_LOG_INFO
			    ("easy wake up suspend write Wakeup Gesture Only reg OK address(0x%02x) valve(0x%02x)\n",
			     f12_ctrl_base + gusture_ctrl_offset,
			     device_ctrl_data[2]);
		}
	}

	info->easy_wakeup_flag = false;
	return;
}

/**
 * synaptics_sensor_sleep()
 * This function stops finger data acquisition and puts the sensor to sleep.
 */
static void synaptics_sensor_sleep(struct synaptics_rmi4_data *rmi4_data)
{
	int retval;
	unsigned char device_ctrl;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 rmi4_data->rmi4_feature.
					 f01_ctrl_base_addr, &device_ctrl,
					 sizeof(device_ctrl));
	if (retval < 0) {
		TS_LOG_ERR("Failed to enter sleep mode\n");
		return;
	}

	if (!strcmp(g_ts_data.product_name, "venus")) {
		TS_LOG_INFO("%s enter sensor_sleep\n", g_ts_data.product_name);
		device_ctrl = (device_ctrl & ~MASK_3BIT);
		device_ctrl = (device_ctrl | NO_SLEEP_OFF | SENSOR_SLEEP_BIT0);
	} else {
		device_ctrl = (device_ctrl & ~MASK_2BIT);
		device_ctrl =
		    (device_ctrl | NORMAL_OPERATION | SENSOR_SLEEP_BIT1);
	}

	retval = synaptics_rmi4_i2c_write(rmi4_data,
					  rmi4_data->rmi4_feature.
					  f01_ctrl_base_addr, &device_ctrl,
					  sizeof(device_ctrl));
	if (retval < 0)
		TS_LOG_ERR("Failed to enter sleep mode\n");

	return;
}

static int synatpics_sleep_mode_in(struct synaptics_rmi4_data *rmi4_data)
{
	int retval = 0;
	unsigned char intr_status;

	TS_LOG_INFO("synatpics_sleep_mode_in\n");
	/* Clear interrupts first */
	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 rmi4_data->rmi4_feature.
					 f01_data_base_addr + 1, &intr_status,
					 rmi4_data->num_of_intr_regs);
	if (retval < 0)
		return retval;

	synaptics_sensor_sleep(rmi4_data);
	return retval;
}

/**
 * synaptics_sleep_mode_out()
 *
  * This function wakes the sensor from sleep.
 */
static void synaptics_sleep_mode_out(struct synaptics_rmi4_data *rmi4_data)
{
	int retval;
	unsigned char device_ctrl;

	TS_LOG_INFO("synaptics_sleep_mode_out\n");
	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 rmi4_data->rmi4_feature.
					 f01_ctrl_base_addr, &device_ctrl,
					 sizeof(device_ctrl));
	if (retval < 0) {
		TS_LOG_ERR("Failed to wake from sleep mode\n");
		return;
	}

	if (!strcmp(g_ts_data.product_name, "venus")) {
		TS_LOG_INFO("%s  exit sensor_sleep\n", g_ts_data.product_name);
		device_ctrl = (device_ctrl & ~MASK_3BIT);
		device_ctrl = (device_ctrl | NO_SLEEP_ON | NORMAL_OPERATION);
	} else {
		device_ctrl = (device_ctrl & ~MASK_2BIT);
		device_ctrl =
		    (device_ctrl | SENSOR_SLEEP_BIT0 | NORMAL_OPERATION);
	}

	retval = synaptics_rmi4_i2c_write(rmi4_data,
					  rmi4_data->rmi4_feature.
					  f01_ctrl_base_addr, &device_ctrl,
					  sizeof(device_ctrl));
	if (retval < 0)
		TS_LOG_ERR("Failed to wake from sleep mode\n");

	return;
}

static int synaptics_suspend(void)
{
	int retval = NO_ERR;

	TS_LOG_INFO
	    ("in last time wake mode synaptics_interrupt_num = %d interrupts\n",
	     synaptics_interrupt_num);
	synaptics_interrupt_num = 0;
	TS_LOG_INFO("suspend +\n");
	switch (rmi4_data->synaptics_chip_data->easy_wakeup_info.sleep_mode) {
	case TS_POWER_OFF_MODE:
		/*for in_cell, tp will power off in suspend. */
		if (rmi4_data->synaptics_chip_data->is_in_cell) {
			if (!g_tp_power_ctrl)
				synaptics_power_off();
			else
				synatpics_sleep_mode_in(rmi4_data);	/*goto sleep mode*/
		}
		break;
		/*for gesture wake up mode suspend. */
	case TS_GESTURE_MODE:
		if (true ==
		    rmi4_data->synaptics_chip_data->easy_wakeup_info.
		    palm_cover_flag)
			rmi4_data->synaptics_chip_data->easy_wakeup_info.
			    palm_cover_flag = false;
		synaptics_put_device_into_easy_wakeup();
		mutex_lock(&wrong_touch_lock);
		rmi4_data->synaptics_chip_data->easy_wakeup_info.off_motion_on =
		    true;
		mutex_unlock(&wrong_touch_lock);
		break;
	default:
		TS_LOG_ERR("no suspend mode\n");
		return -EINVAL;
	}
	TS_LOG_INFO("suspend -\n");
	return retval;
}

/*    do not add time-costly function here.
*/
static int synaptics_resume(void)
{
	int retval = NO_ERR;
	TS_LOG_INFO
	    ("between suspend and resumed there is synaptics_interrupt_num = %d interrupts\n",
	     synaptics_interrupt_num);
	synaptics_interrupt_num = 0;
	TS_LOG_INFO("resume +\n");
	switch (rmi4_data->synaptics_chip_data->easy_wakeup_info.sleep_mode) {
	case TS_POWER_OFF_MODE:
		/*for in_cell, tp should power on in resume. */
		if (rmi4_data->synaptics_chip_data->is_in_cell) {
			if (!g_tp_power_ctrl)
				synaptics_power_on();
			else
				synaptics_sleep_mode_out(rmi4_data);	/*exit sleep mode*/

			synaptics_gpio_reset();
		}
		break;
	case TS_GESTURE_MODE:
		synaptics_put_device_outof_easy_wakeup(rmi4_data);
		synaptics_gpio_reset();
		break;
	default:
		TS_LOG_ERR("no resume mode\n");
		return -EINVAL;
	}
	pre_finger_status = 0;
	TS_LOG_INFO("resume -\n");
	return retval;
}

/*  do some things after power on. */
static int synaptics_after_resume(void *feature_info)
{
	int retval = NO_ERR;
	TS_LOG_INFO("after_resume +\n");

	if (SYNAPTICS_TD4322 != rmi4_data->synaptics_chip_data->ic_type
	&&SYNAPTICS_TD4300 != rmi4_data->synaptics_chip_data->ic_type) {
		msleep(150);
	}

	TS_LOG_INFO("synaptics_after_resume increase delay 50ms\n");
	/*empty list and query device again */
	synaptics_rmi4_empty_fn_list(rmi4_data);
	retval = synaptics_rmi4_query_device(rmi4_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to query device\n");
		return retval;
	}

	synaptics_rmi4_status_resume(rmi4_data);

	TS_LOG_INFO("after_resume -\n");
	return retval;
}

static int synaptics_wakeup_gesture_enable_switch(struct
						  ts_wakeup_gesture_enable_info
						  *info)
{
	int retval = NO_ERR;

	if (!info) {
		TS_LOG_ERR("%s: info is Null\n", __func__);
		retval = -ENOMEM;
		return retval;
	}

	if (info->op_action == TS_ACTION_WRITE) {
		retval =
		    synaptics_set_wakeup_gesture_enable_switch(info->
							       switch_value);
		TS_LOG_DEBUG("write deep_sleep switch: %d\n",
			     info->switch_value);
		if (retval < 0) {
			TS_LOG_ERR("set deep_sleep switch(%d), failed: %d\n",
				   info->switch_value, retval);
		}
	} else {
		TS_LOG_INFO("invalid deep_sleep switch(%d) action: %d\n",
			    info->switch_value, info->op_action);
		retval = -EINVAL;
	}

	return retval;
}

static int synaptics_rmi4_reset_command(struct synaptics_rmi4_data *rmi4_data)
{
	int retval;
	int page_number;
	unsigned char command = 0x01;
	unsigned short pdt_entry_addr = 0;
	struct synaptics_rmi4_fn_desc rmi_fd;
	struct synaptics_rmi4_f01_device_status status;
	bool done = false;

	memset(&rmi_fd, 0, sizeof(rmi_fd));

rescan:
	/* Scan the page description tables of the pages to service */
	for (page_number = 0; page_number < PAGES_TO_SERVICE; page_number++) {
		for (pdt_entry_addr = PDT_START; pdt_entry_addr > PDT_END;
		     pdt_entry_addr -= PDT_ENTRY_SIZE) {
			pdt_entry_addr |= (page_number << 8);

			retval = synaptics_rmi4_i2c_read(rmi4_data,
							 pdt_entry_addr,
							 (unsigned char *)
							 &rmi_fd,
							 sizeof(rmi_fd));
			if (retval < 0)
				return retval;

			if (rmi_fd.fn_number == 0)
				break;

			switch (rmi_fd.fn_number) {
			case SYNAPTICS_RMI4_F01:
				rmi4_data->rmi4_feature.f01_cmd_base_addr =
				    rmi_fd.cmd_base_addr;
				rmi4_data->rmi4_feature.f01_data_base_addr =
				    rmi_fd.data_base_addr;
				if (synaptics_rmi4_crc_in_progress
				    (rmi4_data, &status))
					goto rescan;
				done = true;
				break;
			}
		}
		if (done) {
			TS_LOG_DEBUG
			    ("Find F01 in page description table 0x%04x\n",
			     rmi4_data->rmi4_feature.f01_cmd_base_addr);
			break;
		}
	}

	if (!done) {
		TS_LOG_ERR("Cannot find F01 in page description table\n");
		return -EINVAL;;
	}

	retval = synaptics_rmi4_i2c_write(rmi4_data,
					  rmi4_data->rmi4_feature.
					  f01_cmd_base_addr, &command,
					  sizeof(command));
	if (retval < 0) {
		TS_LOG_ERR("Failed to issue reset command, error = %d\n",
			   retval);
		return retval;
	}

	msleep(rmi4_data->reset_delay_ms);
	return retval;
}

static void synaptics_rmi4_empty_fn_list(struct synaptics_rmi4_data *rmi4_data)
{
	struct synaptics_rmi4_fn *fhandler = NULL;
	struct synaptics_rmi4_fn *fhandler_temp = NULL;
	struct synaptics_rmi4_device_info *rmi = NULL;

	rmi = &(rmi4_data->rmi4_mod_info);

	if (!list_empty(&rmi->support_fn_list)) {
		list_for_each_entry_safe(fhandler, fhandler_temp,
					 &rmi->support_fn_list, link) {
			list_del(&fhandler->link);
			if (fhandler->fn_number == SYNAPTICS_RMI4_F1A) {
				synaptics_rmi4_f1a_kfree(fhandler);
			} else {
				if (fhandler->data) {
					kfree(fhandler->data);
					fhandler->data = NULL;
				}
				if (fhandler->extra) {
					kfree(fhandler->extra);
					fhandler->extra = NULL;
				}
			}
			kfree(fhandler);
			fhandler = NULL;
		}
	}

	return;
}

static int synaptics_reset_device(void)
{
	return synaptics_rmi4_reset_device(rmi4_data);
}

static int synaptics_rmi4_reset_device(struct synaptics_rmi4_data *rmi4_data)
{
	int retval = NO_ERR;

	if (!rmi4_data) {
		TS_LOG_ERR("rmi4_data is NULL \n");
		retval = -ENOMEM;
		return retval;
	}

	TS_LOG_DEBUG("synaptics_rmi4_reset_device called\n");

	retval = synaptics_rmi4_reset_command(rmi4_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to send command reset\n");
		return retval;
	}

	synaptics_rmi4_empty_fn_list(rmi4_data);

	retval = synaptics_rmi4_query_device(rmi4_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to query device\n");
		return retval;
	}

	TS_LOG_DEBUG("synaptics_rmi4_reset_device end\n");
	return 0;
}

static int synaptics_rmi4_status_save(struct synaptics_rmi4_data *rmi4_data)
{
	int retval = NO_ERR;

	return retval;
}

static int synaptics_rmi4_status_resume(struct synaptics_rmi4_data *rmi4_data)
{
	int retval = 0;
	struct ts_feature_info *info = &g_ts_data.feature_info;

	retval =
	    synaptics_set_holster_switch(info->holster_info.holster_switch);
	if (retval < 0) {
		TS_LOG_ERR("Failed to set holster switch(%d), err: %d\n",
			   info->holster_info.holster_switch, retval);
	}

	if (info->roi_info.roi_supported) {
		retval = synaptics_set_roi_switch(info->roi_info.roi_switch);
		if (retval < 0) {
			TS_LOG_ERR("%s, synaptics_set_roi_switch faild\n",
				   __func__);
		}
	}
#ifdef GLOVE_SIGNAL
	retval = synaptics_set_glove_switch(info->glove_info.glove_switch);
	if (retval < 0) {
		TS_LOG_ERR("Failed to set glove switch(%d), err: %d\n",
			   info->glove_info.glove_switch, retval);
	}
#endif

#if defined(HUAWEI_CHARGER_FB)
	if (info->charger_info.charger_supported) {
		retval =
		    synaptics_set_charger_switch(info->charger_info.
						 charger_switch);
		if (retval < 0) {
			TS_LOG_ERR("Failed to set charger switch(%d), err: %d\n",
			     info->charger_info.charger_switch, retval);
		}
	}
#endif

	retval =
	    synaptics_set_palm_switch(!rmi4_data->synaptics_chip_data->
				      easy_wakeup_info.palm_cover_control);
	if (retval < 0) {
		TS_LOG_ERR("Failed to set plam switch(%d), err: %d\n",
			   rmi4_data->synaptics_chip_data->easy_wakeup_info.
			   palm_cover_control, retval);
	}
	return retval;
}

extern struct ts_data g_ts_data;
#define FORCE_TOUCH_I2C 0x2C
#define SYN_I2C_RETRY_TIMES 0

static int synaptics_rmi4_set_page_f35(struct synaptics_rmi4_data *rmi4_data,unsigned short addr)
{

	int retval;
	unsigned char retry;
	unsigned char buf[PAGE_SELECT_LEN];
	unsigned char page;
	struct i2c_client *i2c = to_i2c_client(rmi4_data->synaptics_dev->dev.parent);
	struct i2c_msg msg[1];

	msg[0].addr = FORCE_TOUCH_I2C;
	msg[0].flags = 0;
	msg[0].len = PAGE_SELECT_LEN;
	msg[0].buf = buf;

	page = ((addr >> 8) & MASK_8BIT);
	buf[0] = MASK_8BIT;
	buf[1] = page;

	for (retry = 0; retry < SYN_I2C_RETRY_TIMES; retry++) {
		if (i2c_transfer(g_ts_data.client->adapter, msg, 1) == 1) {
			retval = PAGE_SELECT_LEN;
			break;
		}
		msleep(20);
	}

	return retval;
}

static int synaptics_rmi4_i2c_read_f35(struct synaptics_rmi4_data *rmi4_data,unsigned short addr, unsigned char *data, unsigned short length)
{
	int retval;
	unsigned char retry;
	unsigned char buf;
	unsigned char rd_msgs = 1;
	unsigned char index = 0;
	unsigned char xfer_msgs;
	unsigned char remaining_msgs;
	unsigned short data_offset = 0;
	unsigned short remaining_length = length;
	struct i2c_client *i2c = to_i2c_client(rmi4_data->synaptics_dev->dev.parent);
	struct i2c_adapter *adap = g_ts_data.client->adapter;
	struct i2c_msg msg[rd_msgs + 1];

	retval = synaptics_rmi4_set_page_f35(rmi4_data, addr);
	if (retval != PAGE_SELECT_LEN) {
		retval = -EIO;
		goto exit;
	}

	buf = addr & MASK_8BIT;

	msg[0].addr = FORCE_TOUCH_I2C;
	msg[0].flags = 0;
	msg[0].len = 1;
	msg[0].buf = &buf;

	msg[rd_msgs].addr = FORCE_TOUCH_I2C;
	msg[rd_msgs].flags = I2C_M_RD;
	msg[rd_msgs].len = remaining_length;
	msg[rd_msgs].buf = &data[data_offset];

	remaining_msgs = rd_msgs + 1;

	while (remaining_msgs) {
		xfer_msgs = remaining_msgs;

		for (retry = 0; retry < SYN_I2C_RETRY_TIMES; retry++) {
			retval = i2c_transfer(adap, &msg[index], xfer_msgs);
			if (retval == xfer_msgs)
				break;

			dev_err(rmi4_data->synaptics_dev->dev.parent,
					"%s: I2C retry %d\n",
					__func__, retry + 1);
			msleep(20);
		}

		if (retry == SYN_I2C_RETRY_TIMES) {
			dev_err(rmi4_data->synaptics_dev->dev.parent,
					"%s: I2C read over retry limit\n",
					__func__);
			retval = -EIO;
			goto exit;
		}

		remaining_msgs -= xfer_msgs;
		index += xfer_msgs;
	}

	retval = length;

exit:
	return retval;

}

static int synaptics_rmi4_i2c_write_f35(struct synaptics_rmi4_data *rmi4_data,unsigned short addr, unsigned char *data, unsigned short length)
{
	int retval;
	unsigned char retry;
	unsigned char *buf;
	unsigned char page;
	struct i2c_client *i2c = to_i2c_client(rmi4_data->synaptics_dev->dev.parent);
	struct i2c_msg msg[1];

	if (length >= F35_WRITE_LENGTH_MAX) {
		TS_LOG_ERR("write f35 length error\n");
		retval = -EIO;
		goto exit;
	}

	retval = synaptics_rmi4_set_page_f35(rmi4_data, addr);
	if (retval != PAGE_SELECT_LEN) {
		retval = -EIO;
		goto exit;
	}

	buf = kzalloc(((length + 1) * sizeof(char)), GFP_KERNEL);
	if (!buf) {
		TS_LOG_ERR("%s: malloc failed\n", __func__);
		retval = -ENOMEM;
		goto exit;
	}

	*buf = addr & MASK_8BIT;
	memcpy((buf + 1), data, length);

	msg[0].addr = FORCE_TOUCH_I2C;
	msg[0].flags = 0;
	msg[0].len = length + 1;
	msg[0].buf = buf;

	for (retry = 0; retry < SYN_I2C_RETRY_TIMES; retry++) {
		if (i2c_transfer(g_ts_data.client->adapter, msg, 1) == 1) {
			retval = length;
			break;
		}
		msleep(20);
	}
	if (retry == SYN_I2C_RETRY_TIMES)
		retval = -EIO;

	kfree(buf);
exit:
	return retval;

}

/**
 * synaptics_rmi4_i2c_read()
 *
 * Called by various functions in this driver, and also exported to
 * other expansion Function modules such as rmi_dev.
 *
 * This function reads data of an arbitrary length from the sensor,
 * starting from an assigned register address of the sensor, via I2C
 * with a retry mechanism.
 */
static int synaptics_rmi4_i2c_read(struct synaptics_rmi4_data *rmi4_data,
				   unsigned short addr, unsigned char *data,
				   unsigned short length)
{
	int retval;
	unsigned char reg_addr = addr & MASK_8BIT;

	if (rmi4_data->use_ub_addr){
		retval = synaptics_rmi4_i2c_read_f35(rmi4_data, addr, data, length);
		return retval;
	}

	retval = synaptics_rmi4_set_page(rmi4_data, addr);
	if (retval != PAGE_SELECT_LEN) {
		if (g_ts_data.chip_data->use_ub_supported) {
			rmi4_data->use_ub_addr = true;
		}
		TS_LOG_ERR("error, retval != PAGE_SELECT_LEN\n");
		goto exit;
	}

	rmi4_data->use_ub_addr = false;
	if (!rmi4_data->synaptics_chip_data->bops->bus_read) {
		TS_LOG_ERR("error, invalid bus_read\n");
		retval = -EIO;
		goto exit;
	}
	retval =
	    rmi4_data->synaptics_chip_data->bops->bus_read(&reg_addr, 1, data,
							   length);
	if (retval < 0) {
		TS_LOG_ERR("error, bus read failed, retval  = %d\n", retval);
		goto exit;
	}

exit:
	return retval;
}

 /**
 * synaptics_rmi4_i2c_write()
 *
 * Called by various functions in this driver, and also exported to
 * other expansion Function modules such as rmi_dev.
 *
 * This function writes data of an arbitrary length to the sensor,
 * starting from an assigned register address of the sensor, via I2C with
 * a retry mechanism.
 */
static int synaptics_rmi4_i2c_write(struct synaptics_rmi4_data *rmi4_data,
				    unsigned short addr, unsigned char *data,
				    unsigned short length)
{
	int retval;
	unsigned char reg_addr = addr & MASK_8BIT;
	unsigned char wr_buf[length + 1];
	wr_buf[0] = reg_addr;

	if (rmi4_data->use_ub_addr) {
		retval = synaptics_rmi4_i2c_write_f35(rmi4_data, addr, data, length);
		return retval;
	}
	memcpy(wr_buf+1, data, length);

	retval = synaptics_rmi4_set_page(rmi4_data, addr);
	if (retval != PAGE_SELECT_LEN) {
		if (g_ts_data.chip_data->use_ub_supported) {
			rmi4_data->use_ub_addr = true;
		}
		TS_LOG_ERR("retval != PAGE_SELECT_LEN, retval = %d\n", retval);
		goto exit;
	}

	rmi4_data->use_ub_addr = false;
	if (!rmi4_data->synaptics_chip_data->bops->bus_write) {
		TS_LOG_ERR("bus_write not exits\n");
		retval = -EIO;
		goto exit;
	}
	retval =
	    rmi4_data->synaptics_chip_data->bops->bus_write(wr_buf, length + 1);
	if (retval < 0) {
		TS_LOG_ERR("bus_write failed, retval = %d\n", retval);
		goto exit;
	}

exit:
	return retval;
}

static int synaptics_rmi4_device_status_check(struct
					      synaptics_rmi4_f01_device_status
					      status)
{
	int ret = 0;

	switch (status.status_code) {
	case STATUS_INVALID_CONFIG:
		TS_LOG_ERR("status value = 0x%02x(STATUS_INVALID_CONFIG)\n",
			   status.status_code);
		ret = -1;
		break;
	case STATUS_DEVICE_FAILURE:
		TS_LOG_ERR("status value = 0x%02x(STATUS_DEVICE_FAILURE)\n",
			   status.status_code);
		ret = -1;
		break;
	case STATUS_CONFIG_CRC_FAILURE:
		TS_LOG_ERR("status value = 0x%02x(STATUS_CONFIG_CRC_FAILURE)\n",
			   status.status_code);
		ret = -1;
		break;
	case STATUS_FIRMWARE_CRC_FAILURE:
		TS_LOG_ERR
		    ("status value = 0x%02x(STATUS_FIRMWARE_CRC_FAILURE)\n",
		     status.status_code);
		ret = -1;
		break;
	case STATUS_CRC_IN_PROGRESS:
		TS_LOG_ERR("status value = 0x%02x(STATUS_CRC_IN_PROGRESS)\n",
			   status.status_code);
		ret = -1;
		break;
	default:
		ret = 0;
		break;
	}
	return ret;
}

 /**
 * synaptics_rmi4_query_device()
 *
 * Called by synaptics_init_chip().
 *
 * This funtion scans the page description table, records the offsets
 * to the register types of Function $01, sets up the function handlers
 * for Function $11 and Function $12, determines the number of interrupt
 * sources from the sensor, adds valid Functions with data inputs to the
 * Function linked list, parses information from the query registers of
 * Function $01, and enables the interrupt sources from the valid Functions
 * with data inputs.
 */
static int synaptics_rmi4_query_device(struct synaptics_rmi4_data *rmi4_data)
{
	int retval;
	unsigned char ii;
	unsigned char page_number;
	unsigned char intr_count;
	unsigned char data_sources;
	unsigned short pdt_entry_addr;
	unsigned short intr_addr;
	struct synaptics_rmi4_f01_device_status status;
	struct synaptics_rmi4_fn_desc rmi_fd;
	struct synaptics_rmi4_fn *fhandler = NULL;
	struct synaptics_rmi4_device_info *rmi = NULL;
	struct synaptics_work_reg_status *ptr = &dsm_dump_register_map[1];

	memset(&rmi_fd, 0, sizeof(rmi_fd));
	rmi = &(rmi4_data->rmi4_mod_info);

rescan:
	INIT_LIST_HEAD(&rmi->support_fn_list);
	intr_count = 0;
	data_sources = 0;

	/* Scan the page description tables of the pages to service */
	for (page_number = 0; page_number < PAGES_TO_SERVICE; page_number++) {
		for (pdt_entry_addr = PDT_START; pdt_entry_addr > PDT_END;
		     pdt_entry_addr -= PDT_ENTRY_SIZE) {
			pdt_entry_addr |= (page_number << 8);
			retval = synaptics_rmi4_i2c_read(rmi4_data,
							 pdt_entry_addr,
							 (unsigned char *)
							 &rmi_fd,
							 sizeof(rmi_fd));
			if (retval < 0) {
				TS_LOG_ERR
				    ("read pdt_entry_addr = %d regiseter error happened\n",
				     pdt_entry_addr);
				return retval;
			}
			fhandler = NULL;

			if (rmi_fd.fn_number == 0) {
				TS_LOG_DEBUG("Reached end of PDT\n");
				break;
			}

			TS_LOG_INFO("F%02x found (page %d)\n", rmi_fd.fn_number,
				    page_number);

			switch (rmi_fd.fn_number) {
			case SYNAPTICS_RMI4_F01:
				rmi4_data->rmi4_feature.f01_query_base_addr =
				    rmi_fd.query_base_addr;
				TS_LOG_DEBUG("f01 query base addr = 0x%04x\n",
					     rmi4_data->rmi4_feature.
					     f01_query_base_addr);
				rmi4_data->rmi4_feature.f01_ctrl_base_addr =
				    rmi_fd.ctrl_base_addr;
				rmi4_data->rmi4_feature.f01_data_base_addr =
				    rmi_fd.data_base_addr;
				ptr->fhandler_ctrl_base =
				    rmi4_data->rmi4_feature.f01_data_base_addr;
				TS_LOG_DEBUG("f01 query base addr = 0x%04x\n",
					     rmi4_data->rmi4_feature.
					     f01_data_base_addr);
				rmi4_data->rmi4_feature.f01_cmd_base_addr =
				    rmi_fd.cmd_base_addr;

				if (synaptics_rmi4_crc_in_progress
				    (rmi4_data, &status))
					goto rescan;

				retval =
				    synaptics_rmi4_query_device_info(rmi4_data);
				if (retval < 0) {
					TS_LOG_ERR
					    ("Failed to read device_info \n");
					return retval;
				}
				if (status.flash_prog == 1) {
					TS_LOG_INFO
					    ("In flash prog mode, status = 0x%02x\n",
					     status.status_code);
					rmi4_data->force_update = true;	/*crc error, force update fw to workaround */
#if defined (CONFIG_HUAWEI_DSM)
					if (!dsm_client_ocuppy(tp_dclient)) {
						TS_LOG_INFO
						    ("try to client record 20003 \n");
						dsm_client_record(tp_dclient,
								  "device status for 20003 is :%d\n",
								  status.
								  status_code);
						dsm_client_notify(tp_dclient,
								  DSM_TP_FW_CRC_ERROR_NO);
					}
#endif
				}

				if (synaptics_rmi4_device_status_check(status)) {
					TS_LOG_ERR
					    ("device  status is error ,status value = 0x%02x\n",
					     status.status_code);
#if defined (CONFIG_HUAWEI_DSM)
					if (!dsm_client_ocuppy(tp_dclient)) {
						TS_LOG_INFO
						    ("try to client record 20004 \n");
						dsm_client_record(tp_dclient,
								  "device status for 20004 is :%d\n",
								  status.
								  status_code);
						dsm_client_notify(tp_dclient,
								  DSM_TP_DEV_STATUS_ERROR_NO);
					}
#endif
				}
				break;

			case SYNAPTICS_RMI4_F11:
				if (rmi_fd.intr_src_count == 0)
					break;

				fhandler =
				    synaptics_rmi4_alloc_fh(&rmi_fd,
							    page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n",
						   rmi_fd.fn_number);
					retval = -ENOMEM;
					return retval;
				}

				retval =
				    synaptics_rmi4_f11_init(rmi4_data, fhandler,
							    &rmi_fd,
							    intr_count);
				if (retval < 0) {
					TS_LOG_ERR
					    ("Failed to init f11 handler , retval = %d\n",
					     retval);
					return retval;
				}
				break;

			case SYNAPTICS_RMI4_F12:
				if (rmi_fd.intr_src_count == 0)
					break;

				fhandler =
				    synaptics_rmi4_alloc_fh(&rmi_fd,
							    page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n",
						   rmi_fd.fn_number);
					retval = -ENOMEM;
					return retval;
				}

				retval =
				    synaptics_rmi4_f12_init(rmi4_data, fhandler,
							    &rmi_fd,
							    intr_count);
				if (retval < 0) {
					TS_LOG_ERR
					    ("Failed to init f12 handler , retval = %d\n",
					     retval);
					return retval;
				}
				break;

			case SYNAPTICS_RMI4_F1A:
				if (rmi_fd.intr_src_count == 0)
					break;

				fhandler =
				    synaptics_rmi4_alloc_fh(&rmi_fd,
							    page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n",
						   rmi_fd.fn_number);
					retval = -ENOMEM;
					return retval;
				}

				retval =
				    synaptics_rmi4_f1a_init(rmi4_data, fhandler,
							    &rmi_fd,
							    intr_count);
				if (retval < 0) {
					TS_LOG_ERR
					    ("Failed to init f1a handler , retval = %d\n",
					     retval);
					return retval;
				}
				break;
			case SYNAPTICS_RMI4_F51:
#ifdef ROI
				f51found = true;
#endif

				TS_LOG_INFO("SYNAPTICS_RMI4_F51\n");
				TS_LOG_INFO("rmi_fd.intr_src_count =0x%04x\n",
					    rmi_fd.intr_src_count);
				fhandler =
				    synaptics_rmi4_alloc_fh(&rmi_fd,
							    page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n",
						   rmi_fd.fn_number);
					retval = -ENOMEM;
					return retval;
				}

				retval =
				    synaptics_rmi4_f51_init(rmi4_data, fhandler,
							    &rmi_fd, intr_count,
							    page_number);
				if (retval < 0)
					return retval;
				break;
			case SYNAPTICS_RMI4_F54:
			case SYNAPTICS_RMI4_F55:
				if (rmi_fd.intr_src_count == 0)
					break;

				fhandler =
				    synaptics_rmi4_alloc_fh(&rmi_fd,
							    page_number);
				if (NULL == fhandler) {
					TS_LOG_ERR("Failed to alloc for F%d\n",
						   rmi_fd.fn_number);
					retval = -ENOMEM;
					return retval;
				}
				break;

			default:
				break;
			}

			/* Accumulate the interrupt count */
			intr_count += (rmi_fd.intr_src_count & MASK_3BIT);
			if (fhandler) {
				list_add_tail(&fhandler->link,
					      &rmi->support_fn_list);
			}
		}
	}

	rmi4_data->num_of_intr_regs = (intr_count + 7) / 8;
	TS_LOG_DEBUG("Number of interrupt registers = %d\n",
		     rmi4_data->num_of_intr_regs);

	memset(rmi4_data->intr_mask, 0x00, sizeof(rmi4_data->intr_mask));

	/*
	 * Map out the interrupt bit masks for the interrupt sources
	 * from the registered function handlers.
	 */
	if (!list_empty(&rmi->support_fn_list)) {
		list_for_each_entry(fhandler, &rmi->support_fn_list, link)
		    data_sources += fhandler->num_of_data_sources;
	}
	if (data_sources) {
		if (!list_empty(&rmi->support_fn_list)) {
			list_for_each_entry(fhandler,
					    &rmi->support_fn_list, link) {
				if (fhandler->num_of_data_sources) {
					rmi4_data->intr_mask[fhandler->
							     intr_reg_num] |=
					    fhandler->intr_mask;
				}
			}
		}
	} else {
		TS_LOG_ERR("the num of data sources init fail from IC == %d\n",
			   data_sources);
	}

	/* Enable the interrupt sources */
	for (ii = 0; ii < rmi4_data->num_of_intr_regs; ii++) {
		if (rmi4_data->intr_mask[ii] != 0x00) {
			TS_LOG_DEBUG("Interrupt enable mask %d = 0x%02x\n", ii,
				     rmi4_data->intr_mask[ii]);
			intr_addr =
			    rmi4_data->rmi4_feature.f01_ctrl_base_addr + 1 + ii;
			retval =
			    synaptics_rmi4_i2c_write(rmi4_data, intr_addr,
						     &(rmi4_data->
						       intr_mask[ii]),
						     sizeof(rmi4_data->
							    intr_mask[ii]));
			if (retval < 0) {
				TS_LOG_ERR
				    ("Failed to enable interrupt sources, error:%d",
				     retval);
				return retval;
			}
		}
	}

	return 0;
}

  /**
 * synaptics_rmi4_crc_in_progress()
 *
 * Check if crc in progress ever occured
 *
 */
static bool synaptics_rmi4_crc_in_progress(struct synaptics_rmi4_data
					   *rmi4_data,
					   struct
					   synaptics_rmi4_f01_device_status
					   *status)
{
	int retval;
	int times = 0;
	bool rescan = false;

	if (g_ts_data.chip_data->delay_for_fw_update)
		msleep(200);

	while (1) {
		retval = synaptics_rmi4_i2c_read(rmi4_data,
						 rmi4_data->rmi4_feature.
						 f01_data_base_addr,
						 status->data,
						 sizeof(status->data));
		if (retval < 0) {
			TS_LOG_ERR
			    ("read rmi4_data->f01_data_base_addr = %d status register failed\n",
			     rmi4_data->rmi4_feature.f01_data_base_addr);
			return false;
		}
		if (status->status_code == STATUS_CRC_IN_PROGRESS) {
			TS_LOG_ERR
			    ("CRC is in progress..., the statu_scode is %d \n",
			     status->status_code);
			rescan = true;
			msleep(20);
		} else {
			TS_LOG_DEBUG("CRC is success, CRC test times = %d\n",
				     times);
			break;
		}
		if (times++ > 500)
			return false;
	}
	return rescan;
}

/**
 * synaptics_rmi4_set_page()
 *
 * Called by synaptics_rmi4_i2c_read() and synaptics_rmi4_i2c_write().
 *
 * This function writes to the page select register to switch to the
 * assigned page.
 */
static int synaptics_rmi4_set_page(struct synaptics_rmi4_data *rmi4_data,
				   unsigned int address)
{
	int retval = NO_ERR;
	unsigned char buf[PAGE_SELECT_LEN];
	unsigned char page;

	page = ((address >> 8) & MASK_8BIT);
	if (page != rmi4_data->current_page) {
		buf[0] = MASK_8BIT;
		buf[1] = page;
		retval =
		    rmi4_data->synaptics_chip_data->bops->bus_write(buf,
								    PAGE_SELECT_LEN);
		if (retval != NO_ERR) {
			TS_LOG_ERR("bus_write failed\n");
		} else {
			rmi4_data->current_page = page;
		}
	} else {
		return PAGE_SELECT_LEN;
	}
	return (retval == NO_ERR) ? PAGE_SELECT_LEN : -EIO;
}

static struct synaptics_rmi4_fn *synaptics_rmi4_alloc_fh(struct
							 synaptics_rmi4_fn_desc
							 *rmi_fd,
							 int page_number)
{
	struct synaptics_rmi4_fn *fhandler;

	fhandler = kzalloc(sizeof(struct synaptics_rmi4_fn), GFP_KERNEL);
	if (!fhandler) {
		TS_LOG_ERR("Failed to alloc memory for fhandler\n");
		return NULL;
	}

	fhandler->full_addr.data_base =
	    (rmi_fd->data_base_addr | (page_number << 8));
	fhandler->full_addr.ctrl_base =
	    (rmi_fd->ctrl_base_addr | (page_number << 8));
	fhandler->full_addr.cmd_base =
	    (rmi_fd->cmd_base_addr | (page_number << 8));
	fhandler->full_addr.query_base =
	    (rmi_fd->query_base_addr | (page_number << 8));
	fhandler->fn_number = rmi_fd->fn_number;
	TS_LOG_DEBUG
	    ("handler number is %d, it's data_base_addr = %d, ctrl_base_addr = %d, cmd_base_addr = %d,query_base_addr = %d, page_number = %d\n",
	     rmi_fd->fn_number, rmi_fd->data_base_addr, rmi_fd->ctrl_base_addr,
	     rmi_fd->cmd_base_addr, rmi_fd->query_base_addr, page_number);
	return fhandler;
}

 /**
 * synaptics_rmi4_query_device_info()
 *
 * Called by synaptics_rmi4_query_device().
 *
 */
static int synaptics_rmi4_query_device_info(struct synaptics_rmi4_data
					    *rmi4_data)
{
	int retval = 0;
	int count = 11;
	unsigned char f01_query[F01_STD_QUERY_LEN] = { 0 };
	struct synaptics_rmi4_device_info *rmi = &(rmi4_data->rmi4_mod_info);

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 rmi4_data->rmi4_feature.
					 f01_query_base_addr, f01_query,
					 sizeof(f01_query));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read f01_query_base_addr %d\n",
			   rmi4_data->rmi4_feature.f01_query_base_addr);
		goto out;
	}
	/* RMI Version 4.0 currently supported */
	rmi->version_major = 4;
	rmi->version_minor = 0;

	rmi->manufacturer_id = f01_query[0];
	rmi->product_props = f01_query[1];
	rmi->product_info[0] = f01_query[2] & MASK_7BIT;
	rmi->product_info[1] = f01_query[3] & MASK_7BIT;
	rmi->date_code[0] = f01_query[4] & MASK_5BIT;
	rmi->date_code[1] = f01_query[5] & MASK_4BIT;
	rmi->date_code[2] = f01_query[6] & MASK_5BIT;
	rmi->tester_id =
	    ((f01_query[7] & MASK_7BIT) << 8) | (f01_query[8] & MASK_7BIT);
	rmi->serial_number =
	    ((f01_query[9] & MASK_7BIT) << 8) | (f01_query[10] & MASK_7BIT);
	memcpy(rmi->product_id_string, &f01_query[11], 10);
	while ((count <= 20) && (f01_query[count] != 0)) {
		count++;
	}
	rmi->synaptics_build_id[0] = f01_query[count - 3];
	rmi->synaptics_build_id[1] = f01_query[count - 2];
	rmi->synaptics_build_id[2] = f01_query[count - 1];
	rmi->synaptics_ic_name[0] = f01_query[count - 5];
	rmi->synaptics_ic_name[1] = f01_query[count - 4];
	TS_LOG_DEBUG("count is %d \n", count);
	TS_LOG_INFO("synaptics_build_id is (%c  %c  %c)\n",
		    f01_query[count - 3], f01_query[count - 2],
		    f01_query[count - 1]);
	TS_LOG_DEBUG("product ic string is %s\n",
		     rmi4_data->rmi4_mod_info.product_id_string);
	TS_LOG_DEBUG("synaptics_ic_name 0 is %d,  synaptics_ic_name 1 is %d\n",
		     rmi->synaptics_ic_name[0], rmi->synaptics_ic_name[1]);
	if (rmi->manufacturer_id != 1) {
		TS_LOG_ERR("Non-Synaptics device found, manufacturer ID = %d\n",
			   rmi->manufacturer_id);
	}
	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 rmi4_data->rmi4_feature.
					 f01_query_base_addr +
					 F01_BUID_ID_OFFSET, rmi->build_id,
					 sizeof(rmi->build_id));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read firmware build id (code %d)\n",
			   retval);
	}
out:
	return retval;
}

  /**
 * synaptics_rmi4_f11_init()
 *
 * Called by synaptics_rmi4_query_device().
 *
 * This funtion parses information from the Function 11 registers
 * and determines the number of fingers supported, x and y data ranges,
 * offset to the associated interrupt status register, interrupt bit
 * mask, and gathers finger data acquisition capabilities from the query
 * registers.
 */
static int synaptics_rmi4_f11_init(struct synaptics_rmi4_data *rmi4_data,
				   struct synaptics_rmi4_fn *fhandler,
				   struct synaptics_rmi4_fn_desc *fd,
				   unsigned int intr_count)
{
	int retval = 0;
	unsigned char ii = 0;
	unsigned char intr_offset = 0;
	unsigned char abs_data_size = 0;
	unsigned char abs_data_blk_size = 0;
	unsigned char query[F11_STD_QUERY_LEN] = { 0 };
	unsigned char control[F11_STD_CTRL_LEN] = { 0 };

	fhandler->fn_number = fd->fn_number;
	fhandler->num_of_data_sources = fd->intr_src_count;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 fhandler->full_addr.query_base,
					 query, sizeof(query));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read f11 query base reg\n");
		return retval;
	}
	/* Maximum number of fingers supported */
	if ((query[1] & MASK_3BIT) <= 4)
		fhandler->num_of_data_points = (query[1] & MASK_3BIT) + 1;
	else if ((query[1] & MASK_3BIT) == 5)
		fhandler->num_of_data_points = 10;

	rmi4_data->num_of_fingers = fhandler->num_of_data_points;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 fhandler->full_addr.ctrl_base,
					 control, sizeof(control));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read f11 ctrl base reg\n");
		return retval;
	}
	/* Maximum x and y */
	rmi4_data->sensor_max_x = ((control[6] & MASK_8BIT) << 0) |
	    ((control[7] & MASK_4BIT) << 8);
	rmi4_data->sensor_max_y = ((control[8] & MASK_8BIT) << 0) |
	    ((control[9] & MASK_4BIT) << 8);

	TS_LOG_INFO("Function %02x max x = %d max y = %d\n",
		    fhandler->fn_number, rmi4_data->sensor_max_x,
		    rmi4_data->sensor_max_y);

	fhandler->intr_reg_num = (intr_count + 7) / 8;
	if (fhandler->intr_reg_num != 0)
		fhandler->intr_reg_num -= 1;

	/* Set an enable bit for each data source */
	intr_offset = intr_count % 8;
	fhandler->intr_mask = 0;
	for (ii = intr_offset;
	     ii < ((fd->intr_src_count & MASK_3BIT) + intr_offset); ii++)
		fhandler->intr_mask |= 1 << ii;

	abs_data_size = query[5] & MASK_2BIT;
	abs_data_blk_size = 3 + (2 * (abs_data_size == 0 ? 1 : 0));
	fhandler->size_of_data_register_block = abs_data_blk_size;
	rmi4_data->rmi4_feature.f11_query_base_addr = fd->query_base_addr;
	rmi4_data->rmi4_feature.f11_ctrl_base_addr = fd->ctrl_base_addr;
	rmi4_data->rmi4_feature.f11_data_base_addr = fd->data_base_addr;
	rmi4_data->rmi4_feature.f11_cmd_base_addr = fd->cmd_base_addr;
	return retval;
}

static int synaptics_rmi4_f12_set_enables(struct synaptics_rmi4_data *rmi4_data,
					  unsigned short ctrl28)
{
	int retval;
	static unsigned short ctrl_28_address;

	if (ctrl28)
		ctrl_28_address = ctrl28;

	retval = synaptics_rmi4_i2c_write(rmi4_data,
					  ctrl_28_address,
					  &rmi4_data->report_enable,
					  sizeof(rmi4_data->report_enable));
	if (retval < 0) {
		TS_LOG_ERR("Failed to set enable f12, error:%d\n", retval);
		return retval;
	}

	return retval;
}

 /**
 * synaptics_rmi4_f12_init()
 *
 * Called by synaptics_rmi4_query_device().
 *
 * This funtion parses information from the Function 12 registers and
 * determines the number of fingers supported, offset to the data1
 * register, x and y data ranges, offset to the associated interrupt
 * status register, interrupt bit mask, and allocates memory resources
 * for finger data acquisition.
 */
static int synaptics_rmi4_f12_init(struct synaptics_rmi4_data *rmi4_data,
				   struct synaptics_rmi4_fn *fhandler,
				   struct synaptics_rmi4_fn_desc *fd,
				   unsigned int intr_count)
{
	int retval;
	unsigned char ii;
	unsigned char intr_offset;
	unsigned char size_of_2d_data;
	unsigned char size_of_query8 = 0;
	unsigned char ctrl_8_offset;
	unsigned char ctrl_23_offset;
	unsigned char ctrl_28_offset;
	unsigned char ctrl_26_offset;
	unsigned char num_of_fingers;
	unsigned char ctrl_20_offset;
	unsigned char ctrl_22_offset;
	unsigned char data_04_offset;
	unsigned char f12_2d_data[F12_2D_CTRL_LEN] = { 0 };
	struct synaptics_rmi4_f12_extra_data *extra_data;
	struct synaptics_rmi4_f12_query_5 query_5;
	struct synaptics_rmi4_f12_query_8 query_8;
	struct synaptics_rmi4_f12_ctrl_8 ctrl_8;
	struct synaptics_rmi4_f12_ctrl_23 ctrl_23;
	struct synaptics_work_reg_status *ptr = &dsm_dump_register_map[0];

	fhandler->fn_number = fd->fn_number;
	fhandler->num_of_data_sources = fd->intr_src_count;
	fhandler->extra = kmalloc(sizeof(*extra_data), GFP_KERNEL);
	if (fhandler->extra == NULL) {
		TS_LOG_ERR("Failed to alloc memory for fhandler->extra\n");
		retval = -ENOMEM;
		return retval;
	}
	TS_LOG_DEBUG
	    ("fhandler->num_of_data_sources = %d, fhandler->fn_number = %d\n",
	     fhandler->num_of_data_sources, fhandler->fn_number);
	extra_data = (struct synaptics_rmi4_f12_extra_data *)fhandler->extra;
	size_of_2d_data = sizeof(struct synaptics_rmi4_f12_finger_data);
	rmi4_data->rmi4_feature.f12_ctrl_base_addr =
	    fhandler->full_addr.ctrl_base;
	rmi4_data->rmi4_feature.f12_data_base_addr =
	    fhandler->full_addr.data_base;
	rmi4_data->rmi4_feature.f12_query_base_addr =
	    fhandler->full_addr.query_base;
	ptr->fhandler_ctrl_base = fd->ctrl_base_addr;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 fhandler->full_addr.query_base + 5,
					 query_5.data, sizeof(query_5.data));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read f12->full_addr.query_base\n");
		return retval;
	}

	ctrl_8_offset = query_5.ctrl0_is_present +
	    query_5.ctrl1_is_present +
	    query_5.ctrl2_is_present +
	    query_5.ctrl3_is_present +
	    query_5.ctrl4_is_present +
	    query_5.ctrl5_is_present +
	    query_5.ctrl6_is_present + query_5.ctrl7_is_present;
	TS_LOG_DEBUG("ctrl_8_offset is %d\n", ctrl_8_offset);
	retval =
	    synaptics_rmi4_i2c_read(rmi4_data,
				    rmi4_data->rmi4_feature.f12_ctrl_base_addr +
				    ctrl_8_offset, f12_2d_data,
				    F12_2D_CTRL_LEN);
	if (retval < 0) {
		TS_LOG_ERR("Failed to read f12_ctrl_base\n");
		return retval;
	}
	TS_LOG_INFO("rx = %d, tx = %d, f12init\n",
		    f12_2d_data[F12_RX_NUM_OFFSET],
		    f12_2d_data[F12_TX_NUM_OFFSET]);
	rmi4_data->num_of_rx = f12_2d_data[F12_RX_NUM_OFFSET];
	rmi4_data->num_of_tx = f12_2d_data[F12_TX_NUM_OFFSET];

	ctrl_20_offset = ctrl_8_offset +
	    query_5.ctrl8_is_present +
	    query_5.ctrl9_is_present +
	    query_5.ctrl10_is_present +
	    query_5.ctrl11_is_present +
	    query_5.ctrl12_is_present +
	    query_5.ctrl13_is_present +
	    query_5.ctrl14_is_present +
	    query_5.ctrl15_is_present +
	    query_5.ctrl16_is_present +
	    query_5.ctrl17_is_present +
	    query_5.ctrl18_is_present + query_5.ctrl19_is_present;
	rmi4_data->rmi4_feature.geswakeup_feature.f12_2d_ctrl20_lpm =
	    ctrl_20_offset;
	ptr->offset = ctrl_20_offset;

	ctrl_22_offset = ctrl_20_offset +
	    query_5.ctrl20_is_present + query_5.ctrl21_is_present;
	rmi4_data->rmi4_feature.geswakeup_feature.f12_2d_ctrl22_palm =
	    ctrl_22_offset;

	ctrl_23_offset = ctrl_22_offset + query_5.ctrl22_is_present;

	ctrl_26_offset = ctrl_23_offset +
	    query_5.ctrl23_is_present +
	    query_5.ctrl24_is_present + query_5.ctrl25_is_present;
	rmi4_data->rmi4_feature.glove_feature.offset = ctrl_26_offset;

	ctrl_28_offset = ctrl_26_offset +
	    query_5.ctrl26_is_present + query_5.ctrl27_is_present;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 fhandler->full_addr.ctrl_base +
					 ctrl_23_offset, ctrl_23.data,
					 sizeof(ctrl_23.data));
	if (retval < 0) {
		TS_LOG_ERR
		    ("Failed to read f12 ->full_addr.ctrl_base = %d + ctrl_23_offset = %d\n",
		     fhandler->full_addr.ctrl_base, ctrl_23_offset);
		return retval;
	}

	/* Maximum number of fingers supported */
	fhandler->num_of_data_points = min(ctrl_23.max_reported_objects,
					   (unsigned char)
					   F12_FINGERS_TO_SUPPORT);

	num_of_fingers = fhandler->num_of_data_points;
	rmi4_data->num_of_fingers = num_of_fingers;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 fhandler->full_addr.query_base + 7,
					 &size_of_query8,
					 sizeof(size_of_query8));
	if (retval < 0) {
		TS_LOG_ERR
		    ("Failed to read f12 ->full_addr.query_base = %d,here is +7\n",
		     fhandler->full_addr.query_base);
		return retval;
	}

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 fhandler->full_addr.query_base + 8,
					 query_8.data, size_of_query8);
	if (retval < 0) {
		TS_LOG_ERR
		    ("Failed to read f12 ->full_addr.query_base = %d,here is +8\n",
		     fhandler->full_addr.query_base);
		return retval;
	}

	/* Determine the presence of the Data0 register */
	extra_data->data1_offset = query_8.data0_is_present;

	if ((size_of_query8 >= 3) && (query_8.data15_is_present)) {
		extra_data->data15_offset = query_8.data0_is_present +
		    query_8.data1_is_present +
		    query_8.data2_is_present +
		    query_8.data3_is_present +
		    query_8.data4_is_present +
		    query_8.data5_is_present +
		    query_8.data6_is_present +
		    query_8.data7_is_present +
		    query_8.data8_is_present +
		    query_8.data9_is_present +
		    query_8.data10_is_present +
		    query_8.data11_is_present +
		    query_8.data12_is_present +
		    query_8.data13_is_present + query_8.data14_is_present;
		extra_data->data15_size = (num_of_fingers + 7) / 8;
	} else {
		extra_data->data15_size = 0;
	}

	data_04_offset = query_8.data0_is_present +
	    query_8.data1_is_present +
	    query_8.data2_is_present + query_8.data3_is_present;
	rmi4_data->rmi4_feature.geswakeup_feature.f12_2d_data04_gesture =
	    data_04_offset;

	rmi4_data->report_enable = RPT_DEFAULT;
#ifdef REPORT_2D_Z
	rmi4_data->report_enable |= RPT_Z;
#endif
#ifdef SYNA_FORCE
	rmi4_data->report_enable |= RPT_Z;
#endif
#ifdef REPORT_2D_W
	rmi4_data->report_enable |= (RPT_WX | RPT_WY);
#endif

	retval = synaptics_rmi4_f12_set_enables(rmi4_data,
						fhandler->full_addr.ctrl_base +
						ctrl_28_offset);
	if (retval < 0) {
		TS_LOG_ERR
		    ("Failed to set enable f12,fhandler->full_addr.ctrl_base =%d, ctrl_28_offset = %d\n",
		     fhandler->full_addr.ctrl_base, ctrl_28_offset);
		return retval;
	}

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 fhandler->full_addr.ctrl_base +
					 ctrl_8_offset, ctrl_8.data,
					 sizeof(ctrl_8.data));
	if (retval < 0) {
		TS_LOG_ERR
		    ("Failed to set enable f12,fhandler->full_addr.ctrl_base =%d, ctrl_8_offset = %d\n",
		     fhandler->full_addr.ctrl_base, ctrl_8_offset);
		return retval;
	}

	/* Maximum x and y */
	rmi4_data->sensor_max_x =
	    ((unsigned short)ctrl_8.max_x_coord_lsb << 0) |
	    ((unsigned short)ctrl_8.max_x_coord_msb << 8);
	rmi4_data->sensor_max_y =
	    ((unsigned short)ctrl_8.max_y_coord_lsb << 0) |
	    ((unsigned short)ctrl_8.max_y_coord_msb << 8);
	TS_LOG_INFO("Function %02x max x = %d max y = %d\n",
		    fhandler->fn_number,
		    rmi4_data->sensor_max_x, rmi4_data->sensor_max_y);

	rmi4_data->num_of_rx = ctrl_8.num_of_rx;
	rmi4_data->num_of_tx = ctrl_8.num_of_tx;
	rmi4_data->max_touch_width = max(rmi4_data->num_of_rx,
					 rmi4_data->num_of_tx);

	fhandler->intr_reg_num = (intr_count + 7) / 8;
	if (fhandler->intr_reg_num != 0)
		fhandler->intr_reg_num -= 1;

	/* Set an enable bit for each data source */
	intr_offset = intr_count % 8;
	fhandler->intr_mask = 0;
	for (ii = intr_offset;
	     ii < ((fd->intr_src_count & MASK_3BIT) + intr_offset); ii++)
		fhandler->intr_mask |= 1 << ii;

	/* Allocate memory for finger data storage space */
	fhandler->data_size = num_of_fingers * size_of_2d_data;
	fhandler->data = kmalloc(fhandler->data_size, GFP_KERNEL);
	if (fhandler->data == NULL) {
		TS_LOG_ERR("Failed to alloc memory for fhandler->data\n");
		retval = -ENOMEM;
		return retval;
	}

	return retval;
}

static int synaptics_rmi4_f1a_alloc_mem(struct synaptics_rmi4_data *rmi4_data,
					struct synaptics_rmi4_fn *fhandler)
{
	int retval;
	struct synaptics_rmi4_f1a_handle *f1a;

	f1a = kzalloc(sizeof(*f1a), GFP_KERNEL);
	if (!f1a) {
		TS_LOG_ERR("Failed to alloc mem for function handle\n");
		return -ENOMEM;
	}

	fhandler->data = (void *)f1a;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 fhandler->full_addr.query_base,
					 f1a->button_query.data,
					 sizeof(f1a->button_query.data));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read query registers\n");
		return retval;
	}

	f1a->button_count = f1a->button_query.max_button_count + 1;
	f1a->button_bitmask_size = (f1a->button_count + 7) / 8;

	f1a->button_data_buffer = kcalloc(f1a->button_bitmask_size,
					  sizeof(*(f1a->button_data_buffer)),
					  GFP_KERNEL);
	if (!f1a->button_data_buffer) {
		TS_LOG_ERR("Failed to alloc mem for data buffer\n");
		return -ENOMEM;
	}

	f1a->button_map = kcalloc(f1a->button_count,
				  sizeof(*(f1a->button_map)), GFP_KERNEL);
	if (!f1a->button_map) {
		TS_LOG_ERR("Failed to alloc mem for button map\n");
		return -ENOMEM;
	}

	return 0;
}

static int synaptics_rmi4_cap_button_map(struct synaptics_rmi4_data *rmi4_data,
					 struct synaptics_rmi4_fn *fhandler)
{
#if 0
	unsigned char ii;
	struct synaptics_rmi4_f1a_handle *f1a = fhandler->data;
	const struct synaptics_dsx_platform_data *pdata = rmi4_data->board;

	if (!pdata->cap_button_map) {
		TS_LOG_ERR("%s: cap_button_map is"
			   "NULL in board file\n", __func__);
		return -ENODEV;
	} else if (!pdata->cap_button_map->map) {
		TS_LOG_ERR("%s: Button map is missing in board file\n",
			   __func__);
		return -ENODEV;
	} else {
		if (pdata->cap_button_map->nbuttons != f1a->button_count) {
			f1a->valid_button_count = min(f1a->button_count,
						      pdata->cap_button_map->
						      nbuttons);
		} else {
			f1a->valid_button_count = f1a->button_count;
		}

		for (ii = 0; ii < f1a->valid_button_count; ii++)
			f1a->button_map[ii] = pdata->cap_button_map->map[ii];
	}

	return 0;
#else
	return 0;
#endif
}

static void synaptics_rmi4_f1a_kfree(struct synaptics_rmi4_fn *fhandler)
{
	struct synaptics_rmi4_f1a_handle *f1a = fhandler->data;

	if (f1a) {
		kfree(f1a->button_data_buffer);
		f1a->button_data_buffer = NULL;
		kfree(f1a->button_map);
		f1a->button_map = NULL;
		kfree(f1a);
		f1a = NULL;
		fhandler->data = NULL;
	}

	return;
}

static int synaptics_rmi4_f1a_init(struct synaptics_rmi4_data *rmi4_data,
				   struct synaptics_rmi4_fn *fhandler,
				   struct synaptics_rmi4_fn_desc *fd,
				   unsigned int intr_count)
{
	int retval;
	unsigned char ii;
	unsigned short intr_offset;

	fhandler->fn_number = fd->fn_number;
	fhandler->num_of_data_sources = fd->intr_src_count;
	TS_LOG_DEBUG
	    ("fhandler->num_of_data_sources = %d, fhandler->fn_number = %d\n",
	     fhandler->num_of_data_sources, fhandler->fn_number);

	fhandler->intr_reg_num = (intr_count + 7) / 8;
	if (fhandler->intr_reg_num != 0)
		fhandler->intr_reg_num -= 1;

	/* Set an enable bit for each data source */
	intr_offset = intr_count % 8;
	fhandler->intr_mask = 0;
	for (ii = intr_offset;
	     ii < ((fd->intr_src_count & MASK_3BIT) + intr_offset); ii++)
		fhandler->intr_mask |= 1 << ii;

	retval = synaptics_rmi4_f1a_alloc_mem(rmi4_data, fhandler);
	if (retval < 0) {
		TS_LOG_ERR("Failed to alloc memory for f1a, retval = %d\n",
			   retval);
		goto error_exit;
	}

	retval = synaptics_rmi4_cap_button_map(rmi4_data, fhandler);
	if (retval < 0)
		goto error_exit;

	rmi4_data->button_0d_enabled = 1;

	return 0;

error_exit:
	synaptics_rmi4_f1a_kfree(fhandler);

	return retval;
}

static int synaptics_rmi4_f51_init(struct synaptics_rmi4_data *rmi4_data,
				   struct synaptics_rmi4_fn *fhandler,
				   struct synaptics_rmi4_fn_desc *fd,
				   unsigned int intr_count, unsigned char page)
{
	unsigned char ii;
	unsigned char intr_offset;
	fhandler->fn_number = fd->fn_number;
	fhandler->num_of_data_sources = fd->intr_src_count;
	fhandler->data = NULL;
	fhandler->extra = NULL;

	fhandler->intr_reg_num = (intr_count + 7) / 8;
	if (fhandler->intr_reg_num != 0)
		fhandler->intr_reg_num -= 1;

	/* Set an enable bit for each data source */
	intr_offset = intr_count % 8;
	fhandler->intr_mask = 0;
	for (ii = intr_offset;
	     ii < ((fd->intr_src_count & MASK_3BIT) + intr_offset); ii++)
		fhandler->intr_mask |= 1 << ii;

	rmi4_data->rmi4_feature.f51_ctrl_base_addr =
	    fd->ctrl_base_addr | (page << 8);
	rmi4_data->rmi4_feature.f51_data_base_addr =
	    fd->data_base_addr | (page << 8);
	rmi4_data->rmi4_feature.f51_query_base_addr =
	    fd->query_base_addr | (page << 8);
	TS_LOG_DEBUG("f51 init , data_base_addr = 0x%04x\n"
		     "ctrl_base_addr = 0x%04x\n" "query_base_addr = 0x%04x\n"
		     "page = %d \n", rmi4_data->rmi4_feature.f51_ctrl_base_addr,
		     rmi4_data->rmi4_feature.f51_data_base_addr,
		     rmi4_data->rmi4_feature.f51_query_base_addr, page);

	return 0;
}

static int synaptics_input_config(struct input_dev *input_dev)
{
	set_bit(EV_SYN, input_dev->evbit);
	set_bit(EV_KEY, input_dev->evbit);
	set_bit(EV_ABS, input_dev->evbit);
	set_bit(BTN_TOUCH, input_dev->keybit);
	set_bit(BTN_TOOL_FINGER, input_dev->keybit);

	set_bit(TS_DOUBLE_CLICK, input_dev->keybit);
	set_bit(TS_SLIDE_L2R, input_dev->keybit);
	set_bit(TS_SLIDE_R2L, input_dev->keybit);
	set_bit(TS_SLIDE_T2B, input_dev->keybit);
	set_bit(TS_SLIDE_B2T, input_dev->keybit);
	set_bit(TS_CIRCLE_SLIDE, input_dev->keybit);
	set_bit(TS_LETTER_c, input_dev->keybit);
	set_bit(TS_LETTER_e, input_dev->keybit);
	set_bit(TS_LETTER_m, input_dev->keybit);
	set_bit(TS_LETTER_w, input_dev->keybit);
	set_bit(TS_PALM_COVERED, input_dev->keybit);

	set_bit(TS_TOUCHPLUS_KEY0, input_dev->keybit);
	set_bit(TS_TOUCHPLUS_KEY1, input_dev->keybit);
	set_bit(TS_TOUCHPLUS_KEY2, input_dev->keybit);
	set_bit(TS_TOUCHPLUS_KEY3, input_dev->keybit);
	set_bit(TS_TOUCHPLUS_KEY4, input_dev->keybit);

#ifdef INPUT_PROP_DIRECT
	set_bit(INPUT_PROP_DIRECT, input_dev->propbit);
#endif

	input_set_abs_params(input_dev, ABS_X,
			     0, rmi4_data->sensor_max_x, 0, 0);
	input_set_abs_params(input_dev, ABS_Y,
			     0, rmi4_data->sensor_max_y, 0, 0);
	input_set_abs_params(input_dev, ABS_PRESSURE, 0, 255, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_TRACKING_ID, 0, 15, 0, 0);

	input_set_abs_params(input_dev, ABS_MT_POSITION_X, 0,
			     rmi4_data->sensor_max_x_mt, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_POSITION_Y, 0,
			     rmi4_data->sensor_max_y_mt, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_PRESSURE, 0, 255, 0, 0);
#if ANTI_FALSE_TOUCH_USE_PARAM_MAJOR_MINOR
	input_set_abs_params(input_dev, ABS_MT_WIDTH_MAJOR, 0, 100, 0, 0);
	input_set_abs_params(input_dev, ABS_MT_WIDTH_MINOR, 0, 100, 0, 0);
#else
	input_set_abs_params(input_dev, ABS_MT_DISTANCE, 0, 100, 0, 0);
#endif
#ifdef REPORT_2D_W
	input_set_abs_params(input_dev, ABS_MT_TOUCH_MAJOR, 0,
			     MAX_ABS_MT_TOUCH_MAJOR, 0, 0);
#endif

#ifdef TYPE_B_PROTOCOL
#ifdef KERNEL_ABOVE_3_7
	/* input_mt_init_slots now has a "flags" parameter */
	input_mt_init_slots(input_dev, rmi4_data->num_of_fingers,
			    INPUT_MT_DIRECT);
#else
	input_mt_init_slots(input_dev, rmi4_data->num_of_fingers);
#endif
#endif

#ifdef RED_REMOTE
	/*used for red remote fucntion */
	rmi4_data->input_dev = input_dev;
#endif

	return NO_ERR;
}

static int easy_wakeup_gesture_report_coordinate(struct synaptics_rmi4_data
						 *rmi4_data,
						 unsigned int
						 reprot_gesture_point_num,
						 struct ts_fingers *info)
{
	int retval = 0;
	unsigned char get_custom_data[LOCUS_DATA_NUM] = { 0 };
	int x = 0;
	int y = 0;
	int i = 0;
	unsigned short f51_data_base = 0;

	if (reprot_gesture_point_num != 0) {
		f51_data_base = rmi4_data->rmi4_feature.f51_data_base_addr;
		retval = synaptics_rmi4_i2c_read(rmi4_data,
						 f51_data_base,
						 get_custom_data,
						 (reprot_gesture_point_num *
						  LOCUS_DATA_LENS));
		if (retval < 0) {
			TS_LOG_ERR("%s:f51_data_base read error!retval = %d",
				   __func__, retval);
			return retval;
		}

		for (i = 0; i < reprot_gesture_point_num; i++) {
			/*
			 *F51_CUSTOM_DATA[00]~[23],every 4 bytes save 1 x/y position of the gesture locus;
			 *i.e.Point 1 has 4 bytes from [00] to [03] :
			 * [00] means LSB of x position,[01] means MSB of x position,
			 * [02] means LSB of y position,[03] means MSB of y position,
			 *The most points num is 6,point from 1(lower address) to 6(higher address) means:
			 *1.beginning 2.end 3.top 4.leftmost 5.bottom 6.rightmost
			 */
			x = ((get_custom_data[LOCUS_DATA_LENS * i + 1] << 8) |
			     (get_custom_data[LOCUS_DATA_LENS * i + 0]));
			y = ((get_custom_data[LOCUS_DATA_LENS * i + 3] << 8) |
			     (get_custom_data[LOCUS_DATA_LENS * i + 2]));
			if (SYNAPTICS_S3207 ==
			    rmi4_data->synaptics_chip_data->ic_type) {
				x = x * g_ts_data.chip_data->x_max_mt /
				    rmi4_data->sensor_max_x;
				if (g_ts_data.chip_data->has_virtualkey) {
					y = y * g_ts_data.chip_data->lcd_full /
					    rmi4_data->sensor_max_y;
				} else {
					y = y * g_ts_data.chip_data->y_max_mt /
					    rmi4_data->sensor_max_y;
				}
				if ((x > g_ts_data.chip_data->x_max_mt)
				    || (x < 0)) {
					TS_LOG_ERR
					    ("x position over the size ,x = %d ",
					     x);
				}
				if ((y > g_ts_data.chip_data->lcd_full)
				    || (y < 0)) {
					TS_LOG_ERR
					    ("x position over the size ,y = %d ",
					     y);
				}
			}

			TS_LOG_INFO("%s: Gesture Repot Point %d:\n"
				    "x = %d\n" "y = %d\n", __func__, i, x, y);
			rmi4_data->synaptics_chip_data->easy_wakeup_info.
			    easywake_position[i] = x << 16 | y;
			TS_LOG_INFO("easywake_position[%d] = 0x%04x\n", i,
				    rmi4_data->synaptics_chip_data->
				    easy_wakeup_info.easywake_position[i]);
		}
	}

	return retval;
}

static int synaptics_rmi4_key_gesture_report(struct synaptics_rmi4_data
					     *rmi4_data,
					     struct ts_fingers *info,
					     struct ts_easy_wakeup_info
					     *gesture_report_info,
					     unsigned char
					     *get_gesture_wakeup_data)
{
	int retval = 0;
	unsigned int reprot_gesture_key_value = 0;
	unsigned int reprot_gesture_point_num = 0;

	TS_LOG_INFO("get_gesture_wakeup_data is %d, 1 click 64 letter,\n",
		    get_gesture_wakeup_data[0]);

	switch (get_gesture_wakeup_data[0]) {
	case DOUBLE_CLICK_WAKEUP:
		if (IS_APP_ENABLE_GESTURE(GESTURE_DOUBLE_CLICK) &
		    gesture_report_info->easy_wakeup_gesture) {
			TS_LOG_INFO("@@@DOUBLE_CLICK_WAKEUP detected!@@@\n");
			reprot_gesture_key_value = TS_DOUBLE_CLICK;
			LOG_JANK_D(JLID_TP_GESTURE_KEY, "JL_TP_GESTURE_KEY");
		}
		reprot_gesture_point_num = LINEAR_LOCUS_NUM;
		break;
	case LINEAR_SLIDE_DETECTED:
		TS_LOG_INFO("@@@LINEAR_SLIDE_DETECTED detected!@@@ \n");

		switch (get_gesture_wakeup_data[1]) {
		case LINEAR_SLIDE_LEFT_TO_RIGHT:
			if (IS_APP_ENABLE_GESTURE(GESTURE_SLIDE_L2R) &
			    gesture_report_info->easy_wakeup_gesture) {
				TS_LOG_INFO
				    ("@@@LINEAR_SLIDE_LEFT_TO_RIGHT detected!@@@\n");
				reprot_gesture_key_value = TS_SLIDE_L2R;
				reprot_gesture_point_num = LINEAR_LOCUS_NUM;
			}
			break;
		case LINEAR_SLIDE_RIGHT_TO_LEFT:
			if (IS_APP_ENABLE_GESTURE(GESTURE_SLIDE_R2L) &
			    gesture_report_info->easy_wakeup_gesture) {
				TS_LOG_INFO
				    ("@@@LINEAR_SLIDE_RIGHT_TO_LEFT detected!@@@\n");
				reprot_gesture_key_value = TS_SLIDE_R2L;
				reprot_gesture_point_num = LINEAR_LOCUS_NUM;
			}
			break;
		case LINEAR_SLIDE_TOP_TO_BOTTOM:
			if (IS_APP_ENABLE_GESTURE(GESTURE_SLIDE_T2B) &
			    gesture_report_info->easy_wakeup_gesture) {
				TS_LOG_INFO
				    ("@@@LINEAR_SLIDE_TOP_TO_BOTTOM detected!@@@\n");
				reprot_gesture_key_value = TS_SLIDE_T2B;
				reprot_gesture_point_num = LINEAR_LOCUS_NUM;
			}
			break;
		case LINEAR_SLIDE_BOTTOM_TO_TOP:
			if (IS_APP_ENABLE_GESTURE(GESTURE_SLIDE_B2T) &
			    gesture_report_info->easy_wakeup_gesture) {
				TS_LOG_INFO
				    ("@@@LINEAR_SLIDE_BOTTOM_TO_TOP detected!@@@\n");
				reprot_gesture_key_value = TS_SLIDE_B2T;
				reprot_gesture_point_num = LINEAR_LOCUS_NUM;
			}
			break;
			/*case LINEAR_SLIDE_TOP_TO_BOTTOM2:
			   if (IS_APP_ENABLE_GESTURE(TS_SLIDE_T2B2) & gesture_report_info->easy_wakeup_gesture) {
			   TS_LOG_INFO("@@@LINEAR_SLIDE_TOP_TO_BOTTOM2 detected!@@@\n");
			   reprot_gesture_key_value = TS_SLIDE_T2B2;
			   reprot_gesture_point_num = LINEAR2_LOCUS_NUM;
			   }
			   break; */
		default:
			TS_LOG_INFO
			    ("@@@unknow LINEAR!f51_custom_data0 = %d@@@\n",
			     get_gesture_wakeup_data[0]);
			return 0;
		}
		break;
	case CIRCLE_SLIDE_DETECTED:
		if (IS_APP_ENABLE_GESTURE(GESTURE_CIRCLE_SLIDE) &
		    gesture_report_info->easy_wakeup_gesture) {
			TS_LOG_INFO("@@@CIRCLE_SLIDE_DETECTED detected!@@@\n");
			reprot_gesture_key_value = TS_CIRCLE_SLIDE;
			reprot_gesture_point_num = LETTER_LOCUS_NUM;
		}
		break;
	case SPECIFIC_LETTER_DETECTED:
		TS_LOG_INFO("@@@SPECIFIC_LETTER_DETECTED detected!@@@\n");
		switch (get_gesture_wakeup_data[2]) {
		case SPECIFIC_LETTER_c:
			if (IS_APP_ENABLE_GESTURE(GESTURE_LETTER_c) &
			    gesture_report_info->easy_wakeup_gesture) {
				TS_LOG_INFO
				    ("@@@SPECIFIC_LETTER_c detected!@@@\n");
				reprot_gesture_key_value = TS_LETTER_c;
				reprot_gesture_point_num = LETTER_LOCUS_NUM;
			}
			break;
		case SPECIFIC_LETTER_e:
			if (IS_APP_ENABLE_GESTURE(GESTURE_LETTER_e) &
			    gesture_report_info->easy_wakeup_gesture) {
				TS_LOG_INFO
				    ("@@@SPECIFIC_LETTER_e detected!@@@\n");
				reprot_gesture_key_value = TS_LETTER_e;
				reprot_gesture_point_num = LETTER_LOCUS_NUM;
			}
			break;
		case SPECIFIC_LETTER_m:
			if (IS_APP_ENABLE_GESTURE(GESTURE_LETTER_m) &
			    gesture_report_info->easy_wakeup_gesture) {
				TS_LOG_INFO
				    ("@@@SPECIFIC_LETTER_m detected!@@@\n");
				reprot_gesture_key_value = TS_LETTER_m;
				reprot_gesture_point_num = LETTER_LOCUS_NUM;
			}
			break;
		case SPECIFIC_LETTER_w:
			if (IS_APP_ENABLE_GESTURE(GESTURE_LETTER_w) &
			    gesture_report_info->easy_wakeup_gesture) {
				TS_LOG_INFO
				    ("@@@SPECIFIC_LETTER_w detected!@@@\n");
				reprot_gesture_key_value = TS_LETTER_w;
				reprot_gesture_point_num = LETTER_LOCUS_NUM;
			}
			break;
		default:
			TS_LOG_INFO
			    ("@@@unknow letter!f11_2d_data39[6] = %d@@@\n",
			     get_gesture_wakeup_data[2]);
			return 0;
		}
		break;
	default:
		TS_LOG_INFO("@@@unknow gesture detected!\n");
		return 0;
	}

	if (0 != reprot_gesture_key_value) {
		/*increase wake_lock time to avoid system suspend.*/
		wake_lock_timeout(&g_ts_data.ts_wake_lock, 5 * HZ);
		mutex_lock(&wrong_touch_lock);
		if (true ==
		    rmi4_data->synaptics_chip_data->easy_wakeup_info.
		    off_motion_on) {
			rmi4_data->synaptics_chip_data->easy_wakeup_info.
			    off_motion_on = false;
			retval =
			    easy_wakeup_gesture_report_coordinate(rmi4_data,
								  reprot_gesture_point_num,
								  info);
			if (retval < 0) {
				mutex_unlock(&wrong_touch_lock);
				TS_LOG_INFO
				    ("%s: report line_coordinate error!retval = %d\n",
				     __func__, retval);
				return retval;
			}
			info->gesture_wakeup_value = reprot_gesture_key_value;
		}
		mutex_unlock(&wrong_touch_lock);
	}
	return NO_ERR;
}

static int synaptics_rmi4_gesture_report(struct synaptics_rmi4_data *rmi4_data,
					 struct synaptics_rmi4_fn *fhandler,
					 struct ts_fingers *info)
{
	int retval;
	unsigned char device_data = 0;
	unsigned char f51_custom_data0 = 0;
	int wake_up_value_addr_offset = 0;
	unsigned short f12_data_base = 0;
	unsigned char f11_2d_data39[8] = { 0 };
	unsigned char get_gesture_wakeup_data[5] = { 0 };

	struct ts_easy_wakeup_info *gesture_report_info =
	    &rmi4_data->synaptics_chip_data->easy_wakeup_info;
	if (false == gesture_report_info->easy_wakeup_flag)
		return NO_ERR;
	if (SYNAPTICS_S3207 == rmi4_data->synaptics_chip_data->ic_type) {
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    rmi4_data->rmi4_feature.
					    f11_data_base_addr +
					    F11_2D_DATA38_OFFSET, &device_data,
					    sizeof(device_data));
		if (retval < 0) {
			TS_LOG_ERR
			    ("F11_2D_DATA38_OFFSET read error, retval = %d\n",
			     retval);
			return 0;
		}
		TS_LOG_DEBUG("f11_data_base_addr = %d,device_data = %d",
			     rmi4_data->rmi4_feature.f11_data_base_addr,
			     device_data);
		get_gesture_wakeup_data[0] = device_data;
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    cherry_guesture_pattern_addr,
					    &f51_custom_data0,
					    sizeof(f51_custom_data0));
		if (retval < 0) {
			TS_LOG_ERR("LINEAR_SLIDE_DETECTED error!retval = %d\n",
				   retval);
			return 0;
		}
		TS_LOG_DEBUG("cherry_guesture is linear, f51_custom_data0 = %d",
			     f51_custom_data0);
		get_gesture_wakeup_data[1] = f51_custom_data0;

		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    rmi4_data->rmi4_feature.
					    f11_data_base_addr +
					    F11_2D_DATA39_OFFSET,
					    &f11_2d_data39[0],
					    sizeof(f11_2d_data39));
		if (retval < 0) {
			TS_LOG_ERR("F11_2D_DATA39_OFFSET error!retval = %d\n",
				   retval);
			return 0;
		}
		TS_LOG_DEBUG
		    ("%s:###read### f11_2d_data39[7] = 0x%02x, f11_2d_data39[6] = 0x%02x\n",
		     __func__, f11_2d_data39[7], f11_2d_data39[6]);
		get_gesture_wakeup_data[2] = f11_2d_data39[6];
	} else {
		f12_data_base = rmi4_data->rmi4_feature.f12_data_base_addr;
		wake_up_value_addr_offset =
		    rmi4_data->rmi4_feature.geswakeup_feature.
		    f12_2d_data04_gesture;
		/*get gesture wake up value, read reg f12_2d_data04 */
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data,
					    f12_data_base +
					    wake_up_value_addr_offset,
					    &get_gesture_wakeup_data[0],
					    sizeof(get_gesture_wakeup_data));
		if (retval < 0) {
			TS_LOG_ERR("%s read wake up value failed!\n", __func__);
			return retval;
		}
		/*read diff registers and get diff value, here we unite the value for 3320 and 3207 */
		if (DOUBLE_CLICK_S3320_NO == get_gesture_wakeup_data[0]) {
			get_gesture_wakeup_data[0] = DOUBLE_CLICK_WAKEUP;
		} else if (LINEAR_SLIDE_S3320_NO == get_gesture_wakeup_data[0]) {
			get_gesture_wakeup_data[0] = LINEAR_SLIDE_DETECTED;
		} else if (SPECIFIC_LETTER_S3320_NO ==
			   get_gesture_wakeup_data[0]) {
			get_gesture_wakeup_data[0] = SPECIFIC_LETTER_DETECTED;
		}
	}

	if (get_gesture_wakeup_data[0] != 0) {
		retval =
		    synaptics_rmi4_key_gesture_report(rmi4_data, info,
						      gesture_report_info,
						      get_gesture_wakeup_data);
		TS_LOG_DEBUG("%s:get_gesture_wakeup_data[0] value is %d!\n",
			     __func__, get_gesture_wakeup_data[0]);
		if (retval < 0) {
			TS_LOG_ERR
			    ("Failed to report gesture event!, retval = %d\n",
			     retval);
			return 1;
		}
	}
	return 0;
}

static int synaptics_rmi4_palm_sleep_report(struct synaptics_rmi4_data
					    *rmi4_data,
					    struct synaptics_rmi4_fn *fhandler,
					    struct ts_fingers *info)
{
	unsigned char palm_status = 0;
	unsigned short f12_data_base = 0;
	unsigned char object_type_and_status[80] = { 0 };
	int retval = 0;

	if (!rmi4_data->synaptics_chip_data->easy_wakeup_info.palm_cover_flag) {
		TS_LOG_DEBUG
		    (" If in easy_wake_up mode,no need to ack palm report, rs_flag = %d\n",
		     rmi4_data->synaptics_chip_data->easy_wakeup_info.
		     palm_cover_flag);
		return NO_ERR;
	}
	if (SYNAPTICS_S3207 == rmi4_data->synaptics_chip_data->ic_type) {
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data, cherry_palm_status_addr,
					    &palm_status, sizeof(palm_status));
		if (retval < 0) {
			TS_LOG_ERR("read plam object_type_and_status fail !\n");
		} else {
			TS_LOG_DEBUG
			    ("read plam object_type_and_status OK object_type_and_status = 0x%04x\n",
			     palm_status);
		}

		if (PALM_COVER_SLEEP == (palm_status & 0x02)) {
			TS_LOG_INFO("%s:palm gesture detected!\n", __func__);
			info->gesture_wakeup_value = TS_PALM_COVERED;
			return PALM_COVER_SLEEP;
		} else {
			TS_LOG_DEBUG
			    ("%s:no palm_data!, palm_data read from ic is\n",
			     __func__);
		}

		return PALM_COVER_NOSLEEP;
	} else {
		f12_data_base = rmi4_data->rmi4_feature.f12_data_base_addr;
		retval =
		    synaptics_rmi4_i2c_read(rmi4_data, f12_data_base,
					    &object_type_and_status[0],
					    sizeof(object_type_and_status));
		if (retval < 0) {
			TS_LOG_ERR("read plam object_type_and_status fail !\n");
		} else {
			TS_LOG_DEBUG
			    ("read plam object_type_and_status OK object_type_and_status = 0x%04x\n",
			     object_type_and_status[0]);
		}

		/*get palm data report for sleep---------------------- */

		if (object_type_and_status[0] == PALM_COVER_SLEEP_S3320) {
			TS_LOG_DEBUG("%s:palm gesture detected!\n", __func__);
			info->gesture_wakeup_value = TS_PALM_COVERED;
			return 1;
		} else {
			TS_LOG_DEBUG
			    ("%s:no palm_data!, palm_data read from ic is %d\n",
			     __func__, object_type_and_status[0]);
			return NO_ERR;
		}
	}
	return NO_ERR;
}

 /**
 * synaptics_rmi4_f11_abs_report()
 *
 * Called by synaptics_rmi4_report_touch() when valid Function $11
 * finger data has been detected.
 *
 * This function reads the Function $11 data registers, determines the
 * status of each finger supported by the Function, processes any
 * necessary coordinate manipulation, reports the finger data to
 * the input subsystem, and returns the number of fingers detected.
 */
static void synaptics_rmi4_f11_abs_report(struct synaptics_rmi4_data *rmi4_data,
					  struct synaptics_rmi4_fn *fhandler,
					  struct ts_fingers *info)
{
	int retval;
	unsigned char touch_count = 0;	/* number of touch points */
	unsigned char reg_index;
	unsigned char finger;
	unsigned char fingers_supported;
	unsigned char num_of_finger_status_regs;
	unsigned char finger_shift;
	unsigned char finger_status;
	unsigned char data_reg_blk_size;
	unsigned char finger_status_reg[3] = { 0 };
	unsigned char data[F11_STD_DATA_LEN] = { 0 };
	unsigned short data_addr;
	unsigned short data_offset;
	int x;
	int y;
	int wx;
	int wy;
	int z;
	/*
	 * The number of finger status registers is determined by the
	 * maximum number of fingers supported - 2 bits per finger. So
	 * the number of finger status registers to read is:
	 * register_count = ceil(max_num_of_fingers / 4)
	 */
	fingers_supported = fhandler->num_of_data_points;
	num_of_finger_status_regs = (fingers_supported + 3) / 4;
	data_addr = fhandler->full_addr.data_base;
	data_reg_blk_size = fhandler->size_of_data_register_block;

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 data_addr,
					 finger_status_reg,
					 num_of_finger_status_regs);
	if (retval < 0) {
		TS_LOG_ERR("Failed to read: %d\n", retval);
		return;
	}
#ifdef GLOVE_SIGNAL
	retval = rmi_f11_read_finger_state(info);
	if (retval < 0) {
		TS_LOG_ERR("error: finger_state = %d\n", retval);
		return;
	}
#endif

	for (finger = 0; finger < fingers_supported; finger++) {
		reg_index = finger / 4;
		finger_shift = (finger % 4) * 2;
		finger_status = (finger_status_reg[reg_index] >> finger_shift)
		    & MASK_2BIT;

		/*
		 * Each 2-bit finger status field represents the following:
		 * 00 = finger not present
		 * 01 = finger present and data accurate
		 * 10 = finger present but data may be inaccurate
		 * 11 = reserved
		 */
		if (finger_status) {
			data_offset =
			    data_addr + num_of_finger_status_regs +
			    (finger * data_reg_blk_size);
			retval =
			    synaptics_rmi4_i2c_read(rmi4_data, data_offset,
						    data, data_reg_blk_size);
			if (retval < 0) {
				TS_LOG_ERR("Failed to read data report: %d\n",
					   retval);
				return;
			}

			x = (data[0] << 4) | (data[2] & MASK_4BIT);
			y = (data[1] << 4) | ((data[2] >> 4) & MASK_4BIT);
			wx = (data[3] & MASK_4BIT);
			wy = (data[3] >> 4) & MASK_4BIT;
			z = data[4];


			if (rmi4_data->flip_x)
				x = rmi4_data->sensor_max_x - x;
			if (rmi4_data->flip_y)
				y = rmi4_data->sensor_max_y - y;

			x = x * g_ts_data.chip_data->x_max_mt /
			    rmi4_data->sensor_max_x;
			if (0 == rmi4_data->synaptics_chip_data->has_virtualkey) {
				y = y * g_ts_data.chip_data->y_max_mt /
				    rmi4_data->sensor_max_y;
			} else {
				y = y * g_ts_data.chip_data->lcd_full /
				    rmi4_data->sensor_max_y;
			}

			TS_LOG_DEBUG("Finger %d:\n"
				     "status = 0x%02x\n"
				     "x = %d\n"
				     "y = %d\n"
				     "wx = %d\n"
				     "wy = %d\n",
				     finger, finger_status, x, y, wx, wy);

			info->fingers[finger].x = x;
			info->fingers[finger].y = y;
			info->fingers[finger].major = wx;
			info->fingers[finger].minor = wy;
			info->fingers[finger].pressure = z;

			touch_count++;
		}
	}
	info->cur_finger_number = touch_count;
	TS_LOG_DEBUG("f11_abs_report, touch_count = %d\n", touch_count);
	return;
}

 /**
 * synaptics_rmi4_f12_abs_report()
 *
 * Called by synaptics_rmi4_report_touch() when valid Function $12
 * finger data has been detected.
 *
 * This function reads the Function $12 data registers, determines the
 * status of each finger supported by the Function, processes any
 * necessary coordinate manipulation, reports the finger data to
 * the input subsystem, and returns the number of fingers detected.
 */
static void synaptics_rmi4_f12_abs_report(struct synaptics_rmi4_data *rmi4_data,
					  struct synaptics_rmi4_fn *fhandler,
					  struct ts_fingers *info)
{
	int retval;
	unsigned char touch_count = 0;	/* number of touch points */
	unsigned char finger;
	unsigned char fingers_to_process = 0;
	unsigned char finger_status;
	unsigned char size_of_2d_data;
	unsigned short data_addr;
	unsigned short temp_finger_status = 0;
	int x = 0;
	int y = 0;
	int wx = 0;
	int wy = 0;
#ifdef USE_F12_DATA_15
	int temp = 0;
#endif
#ifdef F12_DATA_15_WORKAROUND
	static unsigned char fingers_already_present = 0;
#endif
	int z = 1;
#ifdef SYNA_FORCE
	unsigned char force_level = 0;
#endif
	struct synaptics_rmi4_f12_extra_data *extra_data;
	struct synaptics_rmi4_f12_finger_data *data;
	struct synaptics_rmi4_f12_finger_data *finger_data;

	fingers_to_process = fhandler->num_of_data_points;
	data_addr = fhandler->full_addr.data_base;
	extra_data = (struct synaptics_rmi4_f12_extra_data *)fhandler->extra;
	size_of_2d_data = sizeof(struct synaptics_rmi4_f12_finger_data);

#ifdef USE_F12_DATA_15
	/* Determine the total number of fingers to process */
	if (extra_data->data15_size) {
		retval = synaptics_rmi4_i2c_read(rmi4_data,
						 data_addr +
						 extra_data->data15_offset,
						 extra_data->data15_data,
						 extra_data->data15_size);
		if (retval < 0) {
			TS_LOG_ERR("Failed to read data status: %d\n", retval);
			return;
		}

		/* Start checking from the highest bit */
		temp = extra_data->data15_size - 1;	/* Highest byte */
		finger = (fingers_to_process - 1) % 8;	/* Highest bit */
		do {
			if (extra_data->data15_data[temp] & (1 << finger))
				break;

			if (finger) {
				finger--;
			} else {
				temp--;	/* Move to the next lower byte */
				finger = 7;
			}

			fingers_to_process--;
		} while (fingers_to_process);

		TS_LOG_INFO("Number of fingers to process = %d\n",
			    fingers_to_process);
	}

#ifdef F12_DATA_15_WORKAROUND
	fingers_to_process = max(fingers_to_process, fingers_already_present);
#endif

	if (!fingers_to_process) {
		TS_LOG_ERR("fingers to process is 0\n");
		return;
	}
#endif

	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 data_addr + extra_data->data1_offset,
					 (unsigned char *)fhandler->data,
					 fingers_to_process * size_of_2d_data);
	if (retval < 0) {
		TS_LOG_ERR("Failed to read: %d, read data offset is %d \n",
			   retval, extra_data->data1_offset);
		return;
	}

	data = (struct synaptics_rmi4_f12_finger_data *)fhandler->data;

	TS_LOG_DEBUG("Number of fingers = %d\n", fingers_to_process);

	for (finger = 0; finger < fingers_to_process; finger++) {
		finger_data = data + finger;
		finger_status = finger_data->object_type_and_status;

		/*
		 * Each 2-bit finger status field represents the following:
		 * 00 = finger not present
		 * 01 = finger present and data accurate
		 * 10 = finger present but data may be inaccurate
		 * 11 = reserved
		 */

		if (finger_status) {
#ifdef F12_DATA_15_WORKAROUND
			fingers_already_present = finger + 1;
#endif

			x = (finger_data->x_msb << 8) | (finger_data->x_lsb);
			y = (finger_data->y_msb << 8) | (finger_data->y_lsb);
#ifdef REPORT_2D_W
			wx = finger_data->wx;
			wy = finger_data->wy;
#endif

#ifdef REPORT_2D_Z
			z = finger_data->z;
#endif
#ifdef SYNA_FORCE
			if (rmi4_data->synaptics_chip_data->support_3d_func) {
				TS_LOG_DEBUG("Read force value for press\n");
				retval = synaptics_rmi4_i2c_read(rmi4_data,
								 0x041a,
								 &force_level,
								 1);
				if (retval < 0) {
					TS_LOG_ERR
					    ("Failed to read data status: %d\n",
					     retval);
					force_level = 1;
				}
				z = force_level;
				if (!force_level)
					z = 1;
			}
#endif

			if (!rmi4_data->flip_x)
				x = rmi4_data->sensor_max_x - x;
			if (!rmi4_data->flip_y)
				y = rmi4_data->sensor_max_y - y;

			if (1 == rmi4_data->synaptics_chip_data->has_virtualkey) {
				x = x * g_ts_data.chip_data->x_max_mt /
				    rmi4_data->sensor_max_x;
				y = y * g_ts_data.chip_data->lcd_full /
				    rmi4_data->sensor_max_y;
			}

			TS_LOG_DEBUG("Finger %d:\n"
				     "status = 0x%02x\n"
				     "x = %d\n"
				     "y = %d\n"
				     "wx = %d\n"
				     "wy = %d\n"
				     "z = %d\n",
				     finger, finger_status, x, y, wx, wy, z);

			info->fingers[finger].status = finger_status;
			info->fingers[finger].x = x;
			info->fingers[finger].y = y;
			info->fingers[finger].major = wx;
			info->fingers[finger].minor = wy;
			info->fingers[finger].pressure = z;
			touch_count++;
			temp_finger_status |= (1 << finger);
		}
	}
	info->cur_finger_number = touch_count;

#ifdef F12_DATA_15_WORKAROUND
	if (touch_count == 0) {
		fingers_already_present = 0;
	}
#endif

#ifdef ROI
	TS_LOG_DEBUG("pre_finger_status=%d, temp_finger_status=%d\n",
		     pre_finger_status, temp_finger_status);
	if (f51_roi_switch) {
		if ((temp_finger_status != pre_finger_status
		     && ((temp_finger_status & pre_finger_status) !=
			 temp_finger_status))) {
			/* roi_data shoud be refreshed. But that takes too long (about 2ms on i2c bus), we delay
			   this work to function synaptics_work_after_input. It will be called after input report. */
			roi_data_staled = 1;
		}
	}
	pre_finger_status = temp_finger_status;
#endif

	TS_LOG_DEBUG("f12_abs_report, touch_count = %d\n", touch_count);
	return;
}

static void synaptics_rmi4_f51_report(struct synaptics_rmi4_data *rmi4_data,
				      struct synaptics_rmi4_fn *fhandler,
				      struct ts_fingers *info)
{
	int retval = 0;
	unsigned short ctrl_base_addr = 0;
	unsigned short data_addr = 0;
	unsigned short touchplus_offset = 0;
	unsigned char touchplus_data;
	unsigned char button_number;
	unsigned char button_flag;

	ctrl_base_addr = rmi4_data->rmi4_feature.f51_ctrl_base_addr;
	if (!strncmp
	    (rmi4_data->rmi4_mod_info.product_id_string, "S3320",
	     strlen("S3320")))
		touchplus_offset = S3320_F51_TOUCHPLUS_OFFSET;	/*S3320 touchplus addr : 0x0422 */
	else
		touchplus_offset = S3350_F51_TOUCHPLUS_OFFSET;	/*S3350 touchplus addr : 0x040E */

	data_addr = ctrl_base_addr + touchplus_offset;
	TS_LOG_DEBUG("%s : data_addr = 0x%02x \n", __func__, data_addr);
	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 data_addr,
					 &touchplus_data,
					 sizeof(touchplus_data));
	if (retval < 0) {
		TS_LOG_ERR("Failed to read: %d, read ctrl_base_addr is %d\n",
			   retval, ctrl_base_addr);
		return;
	}

	button_flag = touchplus_data & TOUCHPLUS_DOWNUP_BIT04;
	info->special_button_flag = !!button_flag;
	TS_LOG_DEBUG("%s : special_button_flag = %d\n", __func__,
		     info->special_button_flag);

	button_number = touchplus_data & 0x0F;
	TS_LOG_DEBUG("%s : button_number = %d\n", __func__, button_number);
	switch (button_number) {
	case 0:
		TS_LOG_INFO("get button %d\n", button_number);
		info->special_button_key = TS_TOUCHPLUS_KEY0;	/*KEY_F21 */
		break;
	case 1:
		TS_LOG_INFO("get button %d\n", button_number);
		info->special_button_key = TS_TOUCHPLUS_KEY1;	/*KEY_F22 */
		break;
	case 2:
		TS_LOG_INFO("get button %d\n", button_number);
		info->special_button_key = TS_TOUCHPLUS_KEY2;	/*KEY_F23 */
		break;
	case 3:
		TS_LOG_INFO("get button %d\n", button_number);
		info->special_button_key = TS_TOUCHPLUS_KEY3;	/*KEY_F19 */
		break;
	case 4:
		TS_LOG_INFO("get button %d\n", button_number);
		info->special_button_key = TS_TOUCHPLUS_KEY4;	/*KEY_F20 */
		break;
	default:
		TS_LOG_ERR("the get_button_number is invald : %d\n",
			   button_number);
		return;
	}

	return;
}

 /**
 * synaptics_rmi4_report_touch()
 *
 * Called by synaptics_rmi4_sensor_report().
 *
 * This function calls the appropriate finger data reporting function
 * based on the function handler it receives and returns the number of
 * fingers detected.
 */
static void synaptics_rmi4_report_touch(struct synaptics_rmi4_data *rmi4_data,
					struct synaptics_rmi4_fn *fhandler,
					struct ts_fingers *info)
{
	int retval = 0;
	TS_LOG_DEBUG("Function %02x reporting\n", fhandler->fn_number);
	retval = synaptics_rmi4_gesture_report(rmi4_data, fhandler, info);
	if (true == retval) {
		TS_LOG_DEBUG
		    ("synaptics_rmi4_gesture_report is called and report gesture\n");
		return;
	}
	retval = synaptics_rmi4_palm_sleep_report(rmi4_data, fhandler, info);
	if (true == retval) {
		TS_LOG_DEBUG
		    ("synaptics_rmi4_palm_sleep_report is called and report gesture\n");
		return;
	}
	switch (fhandler->fn_number) {
	case SYNAPTICS_RMI4_F11:
		synaptics_rmi4_f11_abs_report(rmi4_data, fhandler, info);
		break;
	case SYNAPTICS_RMI4_F12:
		synaptics_rmi4_f12_abs_report(rmi4_data, fhandler, info);
		break;
	case SYNAPTICS_RMI4_F51:
		synaptics_rmi4_f51_report(rmi4_data, fhandler, info);
		break;

	case SYNAPTICS_RMI4_F1A:
		/*synaptics_rmi4_f1a_report(rmi4_data, fhandler);*/
		break;

	default:
		break;
	}
	return;
}

 /**
 * synaptics_rmi4_sensor_report()
 *
 * Called by synaptics_rmi4_irq().
 *
 * This function determines the interrupt source(s) from the sensor
 * and calls synaptics_rmi4_report_touch() with the appropriate
 * function handler for each function with valid data inputs.
 */
static int synaptics_rmi4_sensor_report(struct synaptics_rmi4_data *rmi4_data,
					struct ts_fingers *info)
{
	int retval;
	unsigned char intr[MAX_INTR_REGISTERS] = { 0 };
	struct synaptics_rmi4_fn *fhandler = NULL;
	struct synaptics_rmi4_device_info *rmi = NULL;

	rmi = &(rmi4_data->rmi4_mod_info);

	/*
	 * Get interrupt status information from F01 Data1 register to
	 * determine the source(s) that are flagging the interrupt.
	 */
	retval = synaptics_rmi4_i2c_read(rmi4_data,
					 rmi4_data->rmi4_feature.
					 f01_data_base_addr + 1, intr,
					 rmi4_data->num_of_intr_regs);
	if (retval < 0) {
		g_report_err_log_count++;

		if (g_report_err_log_count > 30) {
			g_report_err_log_count = 30;
			TS_LOG_DEBUG
				("get interrupts status information failed, retval = %d\n",
				 retval);
		} else {
			TS_LOG_ERR
				("get interrupts status information failed, retval = %d\n",
				 retval);
		}

		return retval;
	}

	/*
	 * Traverse the function handler list and service the source(s)
	 * of the interrupt accordingly.
	 */
	if (!list_empty(&rmi->support_fn_list)) {
		list_for_each_entry(fhandler, &rmi->support_fn_list, link) {
			if (fhandler->num_of_data_sources) {
				if (fhandler->
				    intr_mask & intr[fhandler->intr_reg_num]) {
					synaptics_rmi4_report_touch(rmi4_data,
								    fhandler,
								    info);
				}
			}
		}
	}
	return NO_ERR;
}

static int synaptics_irq_top_half(struct ts_cmd_node *cmd)
{
	cmd->command = TS_INT_PROCESS;
	TS_LOG_DEBUG("synaptics irq top half called\n");
	return NO_ERR;
}

static int synaptics_irq_bottom_half(struct ts_cmd_node *in_cmd,
				     struct ts_cmd_node *out_cmd)
{
	int retval = NO_ERR;
	struct ts_fingers *info =
	    &out_cmd->cmd_param.pub_params.algo_param.info;

	synaptics_interrupt_num++;
#ifdef RED_REMOTE
	/*This interrupts is used for redremote, not report */
	if (rmi4_data->fw_debug == true) {
		out_cmd->command = TS_INVAILD_CMD;
		rmidev_sysfs_irq(rmi4_data);
		return NO_ERR;
	}
#endif

	out_cmd->command = TS_INPUT_ALGO;
	out_cmd->cmd_param.pub_params.algo_param.algo_order =
	    rmi4_data->synaptics_chip_data->algo_id;
	TS_LOG_DEBUG("order: %d\n",
		     out_cmd->cmd_param.pub_params.algo_param.algo_order);

	retval = synaptics_rmi4_sensor_report(rmi4_data, info);
	if (retval < 0) {
		if (g_report_err_log_count < 30) {
			TS_LOG_ERR("synaptics_rmi4_sensor_report, error: %d\n", retval);
		} else {
			TS_LOG_DEBUG("synaptics_rmi4_sensor_report, error: %d\n", retval);
		}
		return retval;
	}

	return NO_ERR;
}
