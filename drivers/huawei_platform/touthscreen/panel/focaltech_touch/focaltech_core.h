#ifndef __FOCALTECH_CORE_H__
#define __FOCALTECH_CORE_H__

#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/input/mt.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/regulator/consumer.h>
#include <linux/firmware.h>
#include <linux/debugfs.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/time.h>
#include <linux/workqueue.h>
#include <linux/fs.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#include <linux/version.h>
#include <linux/cdev.h>

#include <linux/dma-mapping.h>

#include <huawei_platform/touthscreen/huawei_touchscreen.h>

#define FTS_MAX_TOUCH_POINTS	10

struct ts_event {
	u16 position_x[FTS_MAX_TOUCH_POINTS];
	u16 position_y[FTS_MAX_TOUCH_POINTS];

	u16 pressure[FTS_MAX_TOUCH_POINTS];
	u16 area[FTS_MAX_TOUCH_POINTS];

	/* touch event: 0 -- down; 1-- up; 2 -- contact */
	u8 touch_event[FTS_MAX_TOUCH_POINTS];

	/* touch ID */
	u8 finger_id[FTS_MAX_TOUCH_POINTS];
	u8 touch_point;
	u8 touch_point_num;
	int touchs;
};

/* platform data that can be configured by extern */
struct fts_ts_platform_data {
	u32 x_resolution_max;
	u32 y_resolution_max;
	u32 pressure_max;

	u32 irq_gpio;
	u32 irq_gpio_flags;
	u32 reset_gpio;
	u32 reset_gpio_flags;

	struct ts_device_data *fts_chip_data;
	struct ts_data *fts_ts_data;
	struct platform_device *fts_platform_dev;

	struct i2c_client *i2c_client;
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

	unsigned char full_pm_cycle;
	unsigned char num_of_rx;
	unsigned char num_of_tx;
	unsigned char num_of_fingers;
	unsigned char max_touch_width;
	unsigned char report_enable;
	const char *module_name;
	int sensor_max_x_mt;
	int sensor_max_y_mt;
	bool touch_stopped;
	bool force_update;
	unsigned int reset_delay_ms;

	char *project_id;
	char *product_name;

};

#define FTS_MODEL_NORMAL	0x00
#define FTS_MODEL_BOOTLOADER	0x01
#define FTS_MODEL_FIRST_START	0x02

#define FTS_FW_MANUAL_UPDATE_FILE_NAME "touch_screen_firmware.img"

extern struct i2c_client *fts_i2c_client;
extern struct input_dev *fts_input_dev;
extern struct fts_ts_platform_data *fts_platform_data;
extern struct fts_upgrade_delay_time fts_upgrade_delay;
extern int apk_debug_flag;
extern struct ts_data g_ts_data;

int fts_i2c_read(unsigned char *addr, int addr_len,
	unsigned char *value, int value_len);
int fts_i2c_write(unsigned char *value, int value_len);
int fts_read_reg(unsigned char addr, unsigned char *val);
int fts_write_reg(unsigned char addr, const unsigned char val);
int fts_write_command(unsigned char command);

int fts_hardware_reset_to_normal_model(struct fts_ts_platform_data *fts_pdata);
int fts_hardware_reset_to_rom_update_model(struct
	fts_ts_platform_data *fts_pdata);
int strtolow(char *src_str, size_t size);
int fts_set_param_data(struct fts_ts_platform_data *fts_pdata, struct fts_test_params *params);

#endif
