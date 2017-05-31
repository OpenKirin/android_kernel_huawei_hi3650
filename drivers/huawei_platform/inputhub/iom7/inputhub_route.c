/*
 *  drivers/misc/inputhub/inputhub_route.c
 *  Sensor Hub Channel driver
 *
 *  Copyright (C) 2012 Huawei, Inc.
 *  Author: qindiwen <inputhub@huawei.com>
 *
 */

#include <linux/types.h>
#include <linux/init.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <linux/freezer.h>
#include <linux/input.h>
#include <linux/i2c.h>
#include <linux/reboot.h>
#include <linux/kernel.h>
#include "protocol.h"
#include "inputhub_route.h"
#include "inputhub_bridge.h"
#include "rdr_sensorhub.h"
#include "sensor_info.h"
#include "sensor_debug.h"
#include "sensor_sys_info.h"
#include "iomcu_power.h"
#include <sensor_detect.h>
#include <huawei_platform/inputhub/motionhub.h>
#include <huawei_platform/inputhub/cahub.h>
#include <huawei_platform/inputhub/sensorhub.h>
#include <huawei_platform/inputhub/fingerprinthub.h>
#include <linux/suspend.h>
#include <linux/fb.h>
#include <linux/timer.h>
#include <linux/rtc.h>
#include <huawei_platform/log/log_exception.h>
#include <linux/wakelock.h>
#include <linux/hisi/hisi_syscounter.h>
#include <linux/time64.h>

#ifdef CONFIG_HUAWEI_DSM
#include <dsm/dsm_pub.h>
#endif

#ifdef CONFIG_CONTEXTHUB_SHMEM
#include "shmem.h"
#endif


//max gap is 600ms
#define MAX_SYSCOUNT_TIME_GAP 600000000LL
//limit is 1 hour
#define SYSCOUNT_DMD_LIMIT (3600*1000000000)

#ifdef CONFIG_HUAWEI_DSM
#define SENSOR_DSM_CONFIG
#endif
#define ROUTE_BUFFER_MAX_SIZE (1024 * 128)
#ifdef TIMESTAMP_SIZE
#undef TIMESTAMP_SIZE
#define TIMESTAMP_SIZE (8)
#endif
#define LENGTH_SIZE sizeof(unsigned int)
#define HEAD_SIZE (LENGTH_SIZE+TIMESTAMP_SIZE)
static int step_ref_cnt;
typedef struct {
	int for_alignment;
	union {
		char effect_addr[sizeof(int)];
		int pkg_length;
	};
	int64_t timestamp;
} t_head;

struct type_record {
	const pkt_header_t *pkt_info;
	struct read_info *rd;
	struct completion resp_complete;
	struct mutex lock_mutex;
	spinlock_t lock_spin;
};

static struct type_record type_record;

sys_status_t iom3_sr_status = ST_WAKEUP;

static struct wake_lock wlock;
int iom3_timeout = 2000;

static struct mutex mutex_write_cmd;
static struct mutex mutex_write_adapter;
static wait_queue_head_t iom3_rec_wq;
int g_iom3_state = IOM3_ST_NORMAL;

static uint32_t valid_step_count;
static uint32_t recovery_step_count;
static uint32_t valid_floor_count = 0;
static uint32_t recovery_floor_count = 0;

int resume_skip_flag;

extern volatile int hall_value;
extern int hall_first_report(bool enable);
extern int ak8789_register_report_data(int ms);
#ifdef SENSOR_DSM_CONFIG
extern struct dsm_client *shb_dclient;
#endif
extern unsigned int sensor_read_number[];
extern void rdr_system_error(u32 modid, u32 arg1, u32 arg2);
extern int iom3_power_state;
extern struct completion iom3_reboot;
extern struct completion iom3_resume_mini;
extern struct completion iom3_resume_all;
extern atomic_t iom3_rec_state;
extern void enable_fingerprint_when_recovery_iom3(void);
extern void disable_fingerprint_when_sysreboot(void);
extern bool is_fingerprint_data_report(const pkt_header_t* head);
extern int send_fingerprint_cmd(unsigned int cmd, unsigned long arg);
extern int send_fingerprint_cmd_internal(int tag, obj_cmd_t cmd, fingerprint_type_t type, bool use_lock);
extern void fingerprint_report(void);
void inputhub_process_sensor_report(const pkt_header_t* head);


extern struct CONFIG_ON_DDR *pConfigOnDDr;
/*k3v5 report stairs level,record_count base on 1000*/
#define EXT_PEDO_VERSION_1 1000
#define EXT_PEDO_VERSION_2 2000
int inputhub_mcu_write_cmd_adapter(const void *buf, unsigned int length,
				   struct read_info *rd);
extern int mcu_reboot_callback(const pkt_header_t *head);
extern int send_fileid_to_mcu(void);
extern int sensor_set_cfg_data(void);

#define ALS_RESET_COUNT 1
#define PS_RESET_COUNT 1
#define RESET_REFRESH_PERIOD (3600*8)
static int als_retry_cnt = ALS_RESET_COUNT;
static int ps_retry_cnt = PS_RESET_COUNT;

static uint64_t als_last_reset_period = 0;
static uint64_t ps_last_reset_period = 0;
extern uint32_t need_reset_io_power;

#define RESUME_INIT 0
#define RESUME_MINI 1
#define RESUME_SKIP 2

struct iom7_log_work {
	void *log_p;
	struct delayed_work log_work;
};

struct inputhub_buffer_pos {
	char *pos;
	unsigned int buffer_size;
};

/*
 *Every route item can be used by one reader and one writer.
 */
struct inputhub_route_table {
	unsigned short port;
	struct inputhub_buffer_pos phead;	/*point to the head of buffer*/
	struct inputhub_buffer_pos pRead;	/*point to the read position of buffer*/
	struct inputhub_buffer_pos pWrite;	/*point to the write position of buffer*/
	wait_queue_head_t read_wait;	/*to block read when no data in buffer*/
	atomic_t data_ready;
	spinlock_t buffer_spin_lock;	/*for read write buffer*/
};

static struct inputhub_route_table package_route_tbl[] = {
	{ROUTE_SHB_PORT, {NULL, 0}, {NULL, 0}, {NULL, 0},
	 __WAIT_QUEUE_HEAD_INITIALIZER(package_route_tbl[0].read_wait)},
	{ROUTE_MOTION_PORT, {NULL, 0}, {NULL, 0}, {NULL, 0},
	 __WAIT_QUEUE_HEAD_INITIALIZER(package_route_tbl[1].read_wait)},
	{ROUTE_CA_PORT, {NULL,0}, {NULL,0}, {NULL,0},
	 __WAIT_QUEUE_HEAD_INITIALIZER(package_route_tbl[2].read_wait)},
	{ROUTE_FHB_PORT, {NULL,0}, {NULL,0}, {NULL,0},
	 __WAIT_QUEUE_HEAD_INITIALIZER(package_route_tbl[3].read_wait)},
};

struct sensors_cmd_map {
	int hal_sensor_type;
	int tag;
};

static const struct sensors_cmd_map sensors_cmd_map_tab[] = {
	{SENSORHUB_TYPE_ACCELEROMETER, TAG_ACCEL},
	{SENSORHUB_TYPE_LIGHT, TAG_ALS},
	{SENSORHUB_TYPE_PROXIMITY, TAG_PS},
	{SENSORHUB_TYPE_GYROSCOPE, TAG_GYRO},
	{SENSORHUB_TYPE_GRAVITY, TAG_GRAVITY},
	{SENSORHUB_TYPE_MAGNETIC, TAG_MAG},
	{SENSORHUB_TYPE_ROTATESCREEN, TAG_SCREEN_ROTATE},
	{SENSORHUB_TYPE_LINEARACCELERATE, TAG_LINEAR_ACCEL},
	{SENSORHUB_TYPE_ORIENTATION, TAG_ORIENTATION},
	{SENSORHUB_TYPE_ROTATEVECTOR, TAG_ROTATION_VECTORS},
	{SENSORHUB_TYPE_PRESSURE, TAG_PRESSURE},
	{SENSORHUB_TYPE_TEMPERATURE, TAG_TEMP},
	{SENSORHUB_TYPE_RELATIVE_HUMIDITY, TAG_HUMIDITY},
	{SENSORHUB_TYPE_AMBIENT_TEMPERATURE, TAG_AMBIENT_TEMP},
	{SENSORHUB_TYPE_MCU_LABC, TAG_LABC},
	{SENSORHUB_TYPE_HALL, TAG_HALL},
	{SENSORHUB_TYPE_MAGNETIC_FIELD_UNCALIBRATED, TAG_MAG_UNCALIBRATED},
	{SENSORHUB_TYPE_GAME_ROTATION_VECTOR, TAG_GAME_RV},
	{SENSORHUB_TYPE_GYROSCOPE_UNCALIBRATED, TAG_GYRO_UNCALIBRATED},
	{SENSORHUB_TYPE_SIGNIFICANT_MOTION, TAG_SIGNIFICANT_MOTION},
	{SENSORHUB_TYPE_STEP_DETECTOR, TAG_STEP_DETECTOR},
	{SENSORHUB_TYPE_STEP_COUNTER, TAG_STEP_COUNTER},
	{SENSORHUB_TYPE_GEOMAGNETIC_ROTATION_VECTOR, TAG_GEOMAGNETIC_RV},
	{SENSORHUB_TYPE_HANDPRESS, TAG_HANDPRESS},
	{SENSORHUB_TYPE_CAP_PROX, TAG_CAP_PROX},
	{SENSORHUB_TYPE_PHONECALL, TAG_PHONECALL},
	{SENSORHUB_TYPE_TILT_DETECTOR, TAG_TILT_DETECTOR},
	{SENSORHUB_TYPE_META_DATA, TAG_FLUSH_META},
};

static int64_t sensors_tm[TAG_SENSOR_END] = { 0, };

static uint8_t tag_to_hal_sensor_type[TAG_SENSOR_END];
static uint8_t hal_sensor_type_to_tag[SENSORHUB_TYPE_END];
static void init_hash_tables(void)
{
	int i;
	for (i = 0;
	     i < sizeof(sensors_cmd_map_tab) / sizeof(sensors_cmd_map_tab[0]);
	     ++i) {
		tag_to_hal_sensor_type[sensors_cmd_map_tab[i].tag] =
		    sensors_cmd_map_tab[i].hal_sensor_type;
		hal_sensor_type_to_tag[sensors_cmd_map_tab[i].hal_sensor_type] =
		    sensors_cmd_map_tab[i].tag;
	}
}

static spinlock_t ref_cnt_lock;
bool really_do_enable_disable(int *ref_cnt, bool enable, int bit)
{
	bool ret = false;
	unsigned long flags = 0;
	if ((bit < 0) || (bit >= sizeof(int32_t) << 3)) {
		hwlog_err("bit %d out of range in %s.\n", bit, __func__);
		return false;
	}

	spin_lock_irqsave(&ref_cnt_lock, flags);
	if (enable) {
		ret = (0 == *ref_cnt);
		*ref_cnt |= 1 << bit;
	} else {
		*ref_cnt &= ~(1 << bit);
		ret = (0 == *ref_cnt);
	}
	/*ret = (0 == (enable ? (*ref_cnt)++ : --*ref_cnt));*/
	spin_unlock_irqrestore(&ref_cnt_lock, flags);
	return ret;
}

static void get_time_stamp(char *timestamp_buf, unsigned int len)
{
	struct timeval tv;
	struct rtc_time tm;
	if (NULL == timestamp_buf) {
		pr_err("timestamp is NULL\n");
		return;
	}
	memset(&tv, 0, sizeof(struct timeval));
	memset(&tm, 0, sizeof(struct rtc_time));
	do_gettimeofday(&tv);
	tv.tv_sec -= sys_tz.tz_minuteswest * 60;
	rtc_time_to_tm(tv.tv_sec, &tm);
	snprintf(timestamp_buf, len, "%04d%02d%02d%02d%02d%02d",
		 tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour,
		 tm.tm_min, tm.tm_sec);
}

static int inputhub_route_item(unsigned short port,
			       struct inputhub_route_table **route_item)
{
	int i;
	for (i = 0;
	     i < sizeof(package_route_tbl) / sizeof(package_route_tbl[0]);
	     ++i) {
		if (port == package_route_tbl[i].port) {
			*route_item = &package_route_tbl[i];
			return 0;
		}
	}

	hwlog_err("unknown port: %d in %s.\n", port, __func__);
	__dmd_log_report(DSM_SHB_ERR_MCU_SYS_MAIN_INIT, __func__,
		       "unknown port\n");
	return -EINVAL;

}

int inputhub_route_open(unsigned short port)
{
	int ret;
	char *pos;
	struct inputhub_route_table *route_item;

	hwlog_info("%s\n", __func__);
	ret = inputhub_route_item(port, &route_item);
	if (ret < 0)
		return -EINVAL;

	if (route_item->phead.pos) {
		hwlog_err("port:%d was already opened in %s.\n", port,
			  __func__);
		return -EINVAL;
	}

	pos = kzalloc(ROUTE_BUFFER_MAX_SIZE, GFP_KERNEL);
	if (!pos)
		return -ENOMEM;

	route_item->phead.pos = pos;
	route_item->pWrite.pos = pos;
	route_item->pRead.pos = pos;
	route_item->phead.buffer_size = ROUTE_BUFFER_MAX_SIZE;
	route_item->pWrite.buffer_size = ROUTE_BUFFER_MAX_SIZE;
	route_item->pRead.buffer_size = 0;

	return 0;
}

EXPORT_SYMBOL_GPL(inputhub_route_open);

void inputhub_route_close(unsigned short port)
{
	int ret;
	struct inputhub_route_table *route_item;

	hwlog_info("%s\n", __func__);
	ret = inputhub_route_item(port, &route_item);
	if (ret < 0)
		return;

	if (route_item->phead.pos)
		kfree(route_item->phead.pos);

	route_item->phead.pos = NULL;
	route_item->pWrite.pos = NULL;
	route_item->pRead.pos = NULL;
}

EXPORT_SYMBOL_GPL(inputhub_route_close);

static inline bool data_ready(struct inputhub_route_table *route_item,
			      struct inputhub_buffer_pos *reader)
{
	unsigned long flags = 0;
	spin_lock_irqsave(&route_item->buffer_spin_lock, flags);
	*reader = route_item->pRead;
	spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
	return reader->buffer_size > 0;
}

ssize_t inputhub_route_read(unsigned short port, char __user *buf,
			    size_t count)
{
	struct inputhub_route_table *route_item;
	struct inputhub_buffer_pos reader;
	char *buffer_end;
	int full_pkg_length;
	int tail_half_len;
	unsigned long flags = 0;

	if (inputhub_route_item(port, &route_item) != 0) {
		hwlog_err("inputhub_route_item failed in %s\n", __func__);
		return 0;
	}

	buffer_end = route_item->phead.pos + route_item->phead.buffer_size;

	/*woke up by signal*/
	if (wait_event_interruptible(route_item->read_wait, data_ready(route_item, &reader)) != 0)
		return 0;

	if (reader.buffer_size > ROUTE_BUFFER_MAX_SIZE) {
		hwlog_err("error reader.buffer_size = %d in port %d!\n",
			  (int)reader.buffer_size, (int)port);
		__dmd_log_report(DSM_SHB_ERR_IOM7_READ, __func__,
			       "error reader.buffer_size in port\n");
		goto clean_buffer;
	}

	if (buffer_end - reader.pos >= LENGTH_SIZE) {
		full_pkg_length = *((int *)reader.pos);
		reader.pos += LENGTH_SIZE;
		if (reader.pos == buffer_end)
			reader.pos = route_item->phead.pos;
	} else {
		tail_half_len = buffer_end - reader.pos;
		memcpy(&full_pkg_length, reader.pos, tail_half_len);
		memcpy((char *)&full_pkg_length + tail_half_len,
		       route_item->phead.pos, LENGTH_SIZE - tail_half_len);
		reader.pos =
		    route_item->phead.pos + (LENGTH_SIZE - tail_half_len);
	}

	if (full_pkg_length + LENGTH_SIZE > reader.buffer_size
	    || full_pkg_length > count) {
		hwlog_err("full_pkg_length = %d is too large in port %d!\n",
			  full_pkg_length, (int)port);
		__dmd_log_report(DSM_SHB_ERR_IOM7_READ, __func__,
			       "full_pkg_length is too large in port\n");
		goto clean_buffer;
	}

	if (buffer_end - reader.pos >= full_pkg_length) {
		if (0 == copy_to_user(buf, reader.pos, full_pkg_length)) {
			reader.pos += full_pkg_length;
			if (reader.pos == buffer_end)
				reader.pos = route_item->phead.pos;
		} else {
			hwlog_err("copy to user failed\n");
			__dmd_log_report(DSM_SHB_ERR_IOM7_READ, __func__,
				       "copy to user failed\n");
			return 0;
		}
	} else {
		tail_half_len = buffer_end - reader.pos;
		if ((0 == copy_to_user(buf, reader.pos, tail_half_len)) &&
		    (0 ==
		     copy_to_user(buf + tail_half_len, route_item->phead.pos,
				  (full_pkg_length - tail_half_len)))) {
			reader.pos =
			    route_item->phead.pos + (full_pkg_length -
						     tail_half_len);
		} else {
			hwlog_err("copy to user failed\n");
			__dmd_log_report(DSM_SHB_ERR_IOM7_READ, __func__,
				       "copy to user failed\n");
			return 0;
		}
	}
	spin_lock_irqsave(&route_item->buffer_spin_lock, flags);
	route_item->pRead.pos = reader.pos;
	route_item->pRead.buffer_size -= (full_pkg_length + LENGTH_SIZE);
	if ((route_item->pWrite.buffer_size > ROUTE_BUFFER_MAX_SIZE)
	    || (route_item->pWrite.buffer_size +
		(full_pkg_length + LENGTH_SIZE) > ROUTE_BUFFER_MAX_SIZE)) {
		hwlog_err("%s:%d write buffer error buffer_size=%u pkg_len=%d\n",
			  __func__, __LINE__, route_item->pWrite.buffer_size,
			  full_pkg_length);
		spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
		goto clean_buffer;
	} else {
		route_item->pWrite.buffer_size +=
		    (full_pkg_length + LENGTH_SIZE);
	}
	spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);

	return full_pkg_length;

clean_buffer:
	hwlog_err("now we will clear the receive buffer in port %d!\n",
		  (int)port);
	spin_lock_irqsave(&route_item->buffer_spin_lock, flags);
	route_item->pRead.pos = route_item->pWrite.pos;
	route_item->pWrite.buffer_size = ROUTE_BUFFER_MAX_SIZE;
	route_item->pRead.buffer_size = 0;
	spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
	return 0;
}

EXPORT_SYMBOL_GPL(inputhub_route_read);

static int64_t getTimestamp(void)
{
	struct timespec ts;
	get_monotonic_boottime(&ts);
	/*timevalToNano*/
	return ts.tv_sec * 1000000000LL + ts.tv_nsec;
}

static inline void write_to_fifo(struct inputhub_buffer_pos *pwriter,
				 char *const buffer_begin,
				 char *const buffer_end, char *buf, int count)
{
	int cur_to_tail_len = buffer_end - pwriter->pos;

	if (cur_to_tail_len >= count) {
		memcpy(pwriter->pos, buf, count);
		pwriter->pos += count;
		if (buffer_end == pwriter->pos) {
			pwriter->pos = buffer_begin;
		}
	} else {
		memcpy(pwriter->pos, buf, cur_to_tail_len);
		memcpy(buffer_begin, buf + cur_to_tail_len,
		       count - cur_to_tail_len);
		pwriter->pos = buffer_begin + (count - cur_to_tail_len);
	}
}

t_ap_sensor_ops_record all_ap_sensor_operations[TAG_SENSOR_END] = {
#ifdef CONFIG_HUAWEI_HALL_INPUTHUB
	[TAG_HALL] = {
		      .work_on_ap = true,
		      .ops = {.setdelay = ak8789_register_report_data}
		      ,
		      }
	,
#endif
};

int register_ap_sensor_operations(int tag, sensor_operation_t *ops)
{
	if (!(TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END)) {
		hwlog_err("tag %d range error in %s\n", tag, __func__);
		return -EINVAL;
	}

	if (!all_ap_sensor_operations[tag].work_on_ap) {
		memcpy(&all_ap_sensor_operations[tag].ops, ops,
		       sizeof(sensor_operation_t));
		all_ap_sensor_operations[tag].work_on_ap = true;
	} else {
		hwlog_warn("tag %d has registered already in %s\n", tag,
			   __func__);
	}

	return 0;
}

int unregister_ap_sensor_operations(int tag)
{
	if (!(TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END)) {
		hwlog_err("tag %d range error in %s\n", tag, __func__);
		return -EINVAL;
	}
	memset(&all_ap_sensor_operations[tag], 0,
	       sizeof(all_ap_sensor_operations[tag]));
	return 0;
}

int report_sensor_event(int tag, int value[], int length)
{
	struct sensor_data event;

	if ((!(TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END))
	    || (length > sizeof(event.value))) {
		hwlog_err("para error (tag : %d), (length : %d) in %s\n", tag,
			  length, __func__);
		return -EINVAL;
	}

	event.type = tag_to_hal_sensor_type[tag];
	event.length = length;
	memcpy(&event.value, value, length);
	sensor_get_data(&event);

	return inputhub_route_write(ROUTE_SHB_PORT, (char *)&event,
				    event.length +
				    OFFSET_OF_END_MEM(struct sensor_data,
						      length));
}

int ap_hall_report(int value)
{
	hall_value = value;
	return report_sensor_event(TAG_HALL, &value, sizeof(value));
}

bool ap_sensor_enable(int tag, bool enable)
{
	bool work_on_ap = all_ap_sensor_operations[tag].work_on_ap;

	if (work_on_ap) {	/*leave this code for furture use*/
		if (all_ap_sensor_operations[tag].ops.enable) {
			all_ap_sensor_operations[tag].ops.enable(enable);
		}
	}

	return work_on_ap;
}

bool ap_sensor_setdelay(int tag, int ms)
{
	bool work_on_ap = all_ap_sensor_operations[tag].work_on_ap;

	if (work_on_ap) {
		if (all_ap_sensor_operations[tag].ops.setdelay) {
			all_ap_sensor_operations[tag].ops.setdelay(ms);
		}
	}

	return work_on_ap;
}

ssize_t inputhub_route_write_batch(unsigned short port, char *buf, size_t count,
				   int64_t timestamp)
{
	struct inputhub_route_table *route_item;
	struct inputhub_buffer_pos writer;
	char *buffer_begin, *buffer_end;
	t_head header;
	unsigned long flags = 0;

	if (inputhub_route_item(port, &route_item) != 0) {
		hwlog_err("inputhub_route_item failed in %s port = %d!\n",
			  __func__, (int)port);
		return 0;
	}
	header.timestamp = timestamp;

	spin_lock_irqsave(&route_item->buffer_spin_lock, flags);
	writer = route_item->pWrite;

	if (writer.buffer_size < count + HEAD_SIZE) {
		spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
		/*hwlog_err("inputhub_route_write_batch failed buffer not enough!\n");*/
		return 0;
	}

	buffer_begin = route_item->phead.pos;
	buffer_end = route_item->phead.pos + route_item->phead.buffer_size;
	if (UINT_MAX - count < sizeof(int64_t)) {
		hwlog_err("inputhub_route_write_batch :count is too large :%zd!\n",
		     count);
		spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
		return 0;
	} else {
		header.pkg_length = count + sizeof(int64_t);
	}
	write_to_fifo(&writer, buffer_begin, buffer_end, header.effect_addr,
		      HEAD_SIZE);
	write_to_fifo(&writer, buffer_begin, buffer_end, buf, count);

	route_item->pWrite.pos = writer.pos;
	route_item->pWrite.buffer_size -= (count + HEAD_SIZE);
	if ((UINT_MAX - route_item->pRead.buffer_size) < (count + HEAD_SIZE)) {
		hwlog_err("inputhub_route_write_batch:pRead :count is too large :%zd!\n",
		     count);
		spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
		return 0;
	} else {
		route_item->pRead.buffer_size += (count + HEAD_SIZE);
	}
	spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
	atomic_set(&route_item->data_ready, 1);
	wake_up_interruptible(&route_item->read_wait);

	return (count + HEAD_SIZE);
}

ssize_t inputhub_route_write(unsigned short port, char *buf, size_t count)
{
	struct inputhub_route_table *route_item;
	struct inputhub_buffer_pos writer;
	char *buffer_begin, *buffer_end;
	t_head header;
	unsigned long flags = 0;

	if (inputhub_route_item(port, &route_item) != 0) {
		hwlog_err("inputhub_route_item failed in %s port = %d!\n",
			  __func__, (int)port);
		return 0;
	}
	header.timestamp = getTimestamp();

	spin_lock_irqsave(&route_item->buffer_spin_lock, flags);
	writer = route_item->pWrite;

	if (writer.buffer_size < count + HEAD_SIZE) {
		spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
		return 0;
	}

	buffer_begin = route_item->phead.pos;
	buffer_end = route_item->phead.pos + route_item->phead.buffer_size;
	header.pkg_length = count + sizeof(int64_t);
	write_to_fifo(&writer, buffer_begin, buffer_end, header.effect_addr,
		      HEAD_SIZE);
	write_to_fifo(&writer, buffer_begin, buffer_end, buf, count);

	route_item->pWrite.pos = writer.pos;
	route_item->pWrite.buffer_size -= (count + HEAD_SIZE);
	route_item->pRead.buffer_size += (count + HEAD_SIZE);
	spin_unlock_irqrestore(&route_item->buffer_spin_lock, flags);
	atomic_set(&route_item->data_ready, 1);
	wake_up_interruptible(&route_item->read_wait);

	return (count + HEAD_SIZE);
}
EXPORT_SYMBOL_GPL(inputhub_route_write);

struct ipc_debug {
	int event_cnt[TAG_END];
	int pack_error_cnt;
};
static struct ipc_debug ipc_debug_info;
static inline void clean_ipc_debug_info(void)
{
	memset(&ipc_debug_info, 0, sizeof(ipc_debug_info));
}

static inline void print_ipc_debug_info(void)
{
	int i;
	for (i = TAG_BEGIN; i < TAG_END; ++i) {
		if (ipc_debug_info.event_cnt[i]) {
			hwlog_info("event_cnt[%d]: %d\n", i,
				   ipc_debug_info.event_cnt[i]);
		}
	}
	if (ipc_debug_info.pack_error_cnt)
		hwlog_err("pack_err_cnt: %d\n", ipc_debug_info.pack_error_cnt);
}

/**begin**/
#define MAX_SEND_LEN (32)
struct link_package {
	int partial_order;
	char link_buffer[MAX_PKT_LENGTH_AP];
	int total_pkg_len;
	int offset;
};

const pkt_header_t *normalpack(const char *buf, unsigned int length)
{
	const pkt_header_t *head = (const pkt_header_t *)buf;
	static struct link_package linker = { -1 };	/*init partial_order to -1 to aviod lost first pkt*/

	/*try to judge which pkt it is*/
	if ((TAG_BEGIN <= head->tag && head->tag < TAG_END)
	    && (head->length <= (MAX_PKT_LENGTH_AP - sizeof(pkt_header_t)))) {
		linker.total_pkg_len =
		    head->length + OFFSET_OF_END_MEM(pkt_header_t, length);
		if (linker.total_pkg_len > (int)length) {	/*need link other partial packages*/
			linker.partial_order = head->partial_order;	/*init partial_order*/
			if (length <= sizeof(linker.link_buffer)) {
				memcpy(linker.link_buffer, buf, length);	/*save first partial package*/
				linker.offset = length;
			} else {
				goto error;
			}
			goto receive_next;	/*receive next partial package*/
		} else {
			return head;	/*full pkt*/
		}
	} else if (TAG_END == head->tag) {	/*check if partial_order effective*/
		pkt_part_header_t *partial = (pkt_part_header_t *) buf;
		if (partial->partial_order == (uint8_t) (linker.partial_order + 1)) {	/*type must keep same with partial->partial_order, because integer promote*/
			int partial_pkt_data_length =
			    length - sizeof(pkt_part_header_t);
			if (linker.offset + partial_pkt_data_length <=
			    sizeof(linker.link_buffer)) {
				++linker.partial_order;
				memcpy(linker.link_buffer + linker.offset,
				       buf + sizeof(pkt_part_header_t),
				       partial_pkt_data_length);
				linker.offset += partial_pkt_data_length;
				if (linker.offset >= linker.total_pkg_len) {	/*link finished*/
					return (pkt_header_t *) linker.
					    link_buffer;
				} else {
					goto receive_next;	/*receive next partial package*/
				}
			}
		}
	}

error:				/*clear linker info when error*/
	++ipc_debug_info.pack_error_cnt;
	linker.partial_order = -1;
	linker.total_pkg_len = 0;
	linker.offset = 0;
receive_next:
	return NULL;
}

const pkt_header_t *pack(const char *buf, unsigned int length)
{
    const pkt_header_t *head = normalpack(buf, length);
#ifdef CONFIG_CONTEXTHUB_SHMEM
    if(head && (head->tag == TAG_SHAREMEM))
    {
        head = shmempack(buf, length);
    }
#endif
    return head;
}


int unpack(const void *buf, unsigned int length)
{
	int ret = 0;
	static int partial_order;

	((pkt_header_t *) buf)->partial_order = partial_order++;	/*inc partial_order in header*/
	if (length <= MAX_SEND_LEN) {
		return inputhub_mcu_send((const char *)buf, length);
	} else {
		char send_partial_buf[MAX_SEND_LEN];
		int send_cnt = 0;

		/*send head*/
		ret = inputhub_mcu_send((const char *)buf, MAX_SEND_LEN);
		if (ret != 0)
			return ret;

		((pkt_part_header_t *) send_partial_buf)->tag = TAG_END;
		for (send_cnt = MAX_SEND_LEN; send_cnt < (int)length;
		     send_cnt += (MAX_SEND_LEN - sizeof(pkt_part_header_t))) {
			((pkt_part_header_t *) send_partial_buf)->partial_order = partial_order++;	/*inc partial_order in partial pkt*/
			memcpy(send_partial_buf + sizeof(pkt_part_header_t),
			       (const char *)buf + send_cnt,
			       MAX_SEND_LEN - sizeof(pkt_part_header_t));
			ret = inputhub_mcu_send(send_partial_buf, MAX_SEND_LEN);
			if (ret != 0)
				return ret;
		}
	}

	return 0;
}

/**end**/

struct mcu_event_wait_list {
	spinlock_t slock;
	struct list_head head;
} mcu_event_wait_list;

static void init_mcu_event_wait_list(void)
{
	INIT_LIST_HEAD(&mcu_event_wait_list.head);
	spin_lock_init(&mcu_event_wait_list.slock);
}

void init_wait_node_add_list(struct mcu_event_waiter *waiter, t_match match,
			     void *out_data, int out_data_len, void *priv)
{
	unsigned long flags = 0;

	waiter->match = match;
	init_completion(&waiter->complete);
	waiter->out_data = out_data;
	waiter->out_data_len = out_data_len;
	waiter->priv = priv;

	spin_lock_irqsave(&mcu_event_wait_list.slock, flags);
	list_add(&waiter->entry, &mcu_event_wait_list.head);
	spin_unlock_irqrestore(&mcu_event_wait_list.slock, flags);
}

void list_del_mcu_event_waiter(struct mcu_event_waiter *self)
{
	unsigned long flags = 0;
	spin_lock_irqsave(&mcu_event_wait_list.slock, flags);
	list_del(&self->entry);
	spin_unlock_irqrestore(&mcu_event_wait_list.slock, flags);
}

static void wake_up_mcu_event_waiter(const pkt_header_t *head)
{
	unsigned long flags = 0;
	struct mcu_event_waiter *pos, *n;

	spin_lock_irqsave(&mcu_event_wait_list.slock, flags);
	list_for_each_entry_safe(pos, n, &mcu_event_wait_list.head, entry) {
		if (pos->match && pos->match(pos->priv, head)) {
			if (pos->out_data != NULL) {
				memcpy(pos->out_data, head, pos->out_data_len);
			}
			complete(&pos->complete);
			/*to support diffrent task wait for same event, here we don't break;*/
		}
	}
	spin_unlock_irqrestore(&mcu_event_wait_list.slock, flags);
}

int inputhub_mcu_write_cmd_nolock(const void *buf, unsigned int length)
{
	int ret = 0;
	pkt_header_t *pkt = (pkt_header_t *) buf;
	((pkt_header_t *) buf)->resp = RESP;
	if (!WAIT_FOR_MCU_RESP_AFTER_SEND(buf, unpack(buf, length), 2000)) {
		hwlog_err("wait for tag:%s:%d\tcmd:%d resp timeout in %s\n",
			  obj_tag_str[pkt->tag], pkt->tag, pkt->cmd, __func__);
		ret = -1;
	}

	return ret;
}

char *obj_tag_str[] = {
	[TAG_ACCEL] = "TAG_ACCEL",
	[TAG_GYRO] = "TAG_GYRO",
	[TAG_MAG] = "TAG_MAG",
	[TAG_ALS] = "TAG_ALS",
	[TAG_PS] = "TAG_PS",
	[TAG_SCREEN_ROTATE] = "TAG_SCREEN_ROTATE",
	[TAG_LINEAR_ACCEL] = "TAG_LINEAR_ACCEL",
	[TAG_GRAVITY] = "TAG_GRAVITY",
	[TAG_ORIENTATION] = "TAG_ORIENTATION",
	[TAG_ROTATION_VECTORS] = "TAG_ROTATION_VECTORS",
	[TAG_PRESSURE] = "TAG_PRESSURE",
	[TAG_TEMP] = "TAG_TEMP",
	[TAG_HUMIDITY] = "TAG_HUMIDITY",
	[TAG_AMBIENT_TEMP] = "TAG_AMBIENT_TEMP",
	[TAG_LABC] = "TAG_LABC",
	[TAG_HALL] = "TAG_HALL",
	[TAG_MAG_UNCALIBRATED] = "TAG_MAG_UNCALIBRATED",
	[TAG_GAME_RV] = "TAG_GAME_RV",
	[TAG_GYRO_UNCALIBRATED] = "TAG_GYRO_UNCALIBRATED",
	[TAG_SIGNIFICANT_MOTION] = "TAG_SIGNIFICANT_MOTION",
	[TAG_STEP_DETECTOR] = "TAG_STEP_DETECTOR",
	[TAG_STEP_COUNTER] = "TAG_STEP_COUNTER",
	[TAG_GEOMAGNETIC_RV] = "TAG_GEOMAGNETIC_RV",
	[TAG_HANDPRESS] = "TAG_HANDPRESS",
	[TAG_CAP_PROX] = "TAG_CAP_PROX",
	[TAG_FINGERSENSE] = "TAG_FINGERSENSE",
	[TAG_PHONECALL] = "TAG_PHONECALL",
	[TAG_GPS_4774_I2C] = "TAG_GPS_4774_I2C",
	[TAG_CA] = "TAG_CA",
	[TAG_OIS] = "TAG_OIS",
	[TAG_TP] = "TAG_TP",
	[TAG_SPI] = "TAG_SPI",
	[TAG_I2C] = "TAG_I2C",
	[TAG_RGBLIGHT] = "TAG_RGBLIGHT",
	[TAG_BUTTONLIGHT] = "TAG_BUTTONLIGHT",
	[TAG_BACKLIGHT] = "TAG_BACKLIGHT",
	[TAG_VIBRATOR] = "TAG_VIBRATOR",
	[TAG_SYS] = "TAG_SYS",
	[TAG_LOG] = "TAG_LOG",
	[TAG_MOTION] = "TAG_MOTION",
	[TAG_CURRENT] = "TAG_CURRENT",
	[TAG_LOG_BUFF] = "TAG_LOG_BUFF",
	[TAG_PDR] = "TAG_PDR",
	[TAG_AR] = "TAG_AR",
	[TAG_FP] = "TAG_FP",
	[TAG_KEY] = "TAG_KEY",
	[TAG_TILT_DETECTOR] = "TAG_TILT_DETECTOR",
	[TAG_FAULT] = "TAG_FAULT",
	[TAG_END] = "TAG_END",
};

static int inputhub_sensor_enable_internal_nolock(int tag, bool enable,
						  close_param_t *param)
{
	if (NULL == param) {
		hwlog_err("NULL pointer param in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "NULL pointer param\n");
		return -EINVAL;
	}

	if (ap_sensor_enable(tag, enable))
		return 0;

	if (TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END) {
		if (enable) {
			pkt_header_t pkt = {
				.tag = tag,
				.cmd = CMD_CMN_OPEN_REQ,
				.resp = NO_RESP,
				.length = 0
			};

			hwlog_info("open sensor %s!\n", obj_tag_str[tag]);
			return inputhub_mcu_write_cmd_nolock(&pkt, sizeof(pkt));
		} else {
			pkt_cmn_close_req_t pkt;
			memset(&pkt, 0, sizeof(pkt));
			pkt.hd.tag = tag;
			pkt.hd.cmd = CMD_CMN_CLOSE_REQ;
			pkt.hd.resp = NO_RESP;
			pkt.hd.length = sizeof(close_param_t);
			memcpy(&pkt.close_param, param,
			       sizeof(pkt.close_param));

			hwlog_info("close sensor %s!\n", obj_tag_str[tag]);
			return inputhub_mcu_write_cmd_nolock(&pkt, sizeof(pkt));
		}
	} else {
		hwlog_err("unknown sensor type in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "unknown sensor type\n");
		return -EINVAL;
	}
}

static inline int send_app_config_cmd(int tag, void *app_config, bool use_lock)
{
	pkt_cmn_interval_req_t i_pkt;

	i_pkt.hd.tag = tag;
	i_pkt.hd.cmd = CMD_CMN_CONFIG_REQ;
	i_pkt.hd.resp = NO_RESP;
	i_pkt.hd.length = sizeof(i_pkt.app_config);
	memcpy(i_pkt.app_config, app_config, sizeof(i_pkt.app_config));

	if (use_lock) {
		return inputhub_mcu_write_cmd_adapter(&i_pkt, sizeof(i_pkt),
						      NULL);
	} else {
		return inputhub_mcu_write_cmd_nolock(&i_pkt, sizeof(i_pkt));
	}
}

static int inputhub_sensor_setdelay_internal_nolock(int tag,
						    open_param_t *param)
{
	if (NULL == param) {
		hwlog_err("NULL pointer param in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "NULL pointer param\n");
		return -EINVAL;
	}

	if (ap_sensor_setdelay(tag, param->period))
		return 0;

	if (TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END) {
		pkt_cmn_interval_req_t pkt;
		memset(&pkt, 0, sizeof(pkt));
		pkt.hd.tag = tag;
		pkt.hd.cmd = CMD_CMN_INTERVAL_REQ;
		pkt.hd.resp = NO_RESP;
		pkt.hd.length = sizeof(open_param_t);
		memcpy(&pkt.param, param, sizeof(pkt.param));
		hwlog_info("set sensor %s delay %d ms!\n",
			   obj_tag_str[pkt.hd.tag], param->period);
		return inputhub_mcu_write_cmd_nolock(&pkt, sizeof(pkt));
	} else {
		hwlog_err("unknown sensor type in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "unknown sensor type\n");
		return -EINVAL;
	}
}

static bool motion_status[MOTION_TYPE_END];
static int motion_ref_cnt;
static void update_motion_info(obj_cmd_t cmd, motion_type_t type)
{
	if (!(MOTION_TYPE_START <= type && type < MOTION_TYPE_END))
		return;

	switch (cmd) {
	case CMD_CMN_OPEN_REQ:
		motion_status[type] = true;
		break;

	case CMD_CMN_CLOSE_REQ:
		motion_status[type] = false;
		break;

	default:
		hwlog_err("unknown cmd type in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "unknown cmd type\n");
		break;
	}
}

extern int send_motion_cmd_internal(int tag, obj_cmd_t cmd, motion_type_t type,
				    bool use_lock);
static int extend_step_counter_process_nolock(bool enable)
{
	uint8_t app_config[16] = { 0, };
	close_param_t extend_close_param;
	memset(&extend_close_param, 0, sizeof(extend_close_param));
	extend_close_param.reserved[0] = TYPE_EXTEND;
	app_config[0] = enable;
	app_config[1] = TYPE_EXTEND;
	/*close step counter*/
	if (!enable) {
		send_app_config_cmd(TAG_STEP_COUNTER, app_config, false);
	}
	hwlog_info("%s extend_step_counte!\n", enable ? "open" : "close");
	if (really_do_enable_disable(&step_ref_cnt, enable, TYPE_EXTEND)) {
		inputhub_sensor_enable_internal_nolock(TAG_STEP_COUNTER, enable,
						       &extend_close_param);
	}
	if (enable) {
		open_param_t extend_open_param = {
			.period = 20,	/*default delay_ms*/
			.batch_count = 1,
			.mode = AUTO_MODE,
			.reserved[0] = TYPE_EXTEND
		};
		inputhub_sensor_setdelay_internal_nolock(TAG_STEP_COUNTER,
							 &extend_open_param);
		return send_app_config_cmd(TAG_STEP_COUNTER, app_config, false);
	}
	return 0;
}

void enable_motions_when_recovery_iom3(void)
{
	motion_type_t type;
	/*save step count when iom3 recovery*/
	recovery_step_count = valid_step_count;
	recovery_floor_count = valid_floor_count;
	motion_ref_cnt = 0;	/*to send open motion cmd when open first type*/
	for (type = MOTION_TYPE_START; type < MOTION_TYPE_END; ++type) {
		if (motion_status[type]) {
			hwlog_info("motion state %d in %s\n", type, __func__);
			send_motion_cmd_internal(TAG_MOTION, CMD_CMN_OPEN_REQ,
						 type, false);
		}
	}
}

void disable_motions_when_sysreboot(void)
{
	motion_type_t type;
	for (type = MOTION_TYPE_START; type < MOTION_TYPE_END; ++type) {
		if (motion_status[type]) {
			hwlog_info("motion state %d in %s\n", type, __func__);
			send_motion_cmd_internal(TAG_MOTION, CMD_CMN_CLOSE_REQ,
						 type, false);
		}
	}
}

struct cas_cmd_map {
    int         chb_ioctl_app_cmd;
    int         ca_type;
    int         tag;
    obj_cmd_t cmd;
};
static const struct cas_cmd_map cas_cmd_map_tab[] = {
    {CHB_IOCTL_CA_START, -1,  TAG_CA, CMD_CA_OPEN_REQ},
    {CHB_IOCTL_CA_STOP,   -1,  TAG_CA, CMD_CA_CLOSE_REQ},
    {CHB_IOCTL_CA_ATTR_START,-1, TAG_CA, CMD_CA_ATTR_ENABLE_REQ},
    {CHB_IOCTL_CA_ATTR_STOP,  -1, TAG_CA, CMD_CA_ATTR_DISABLE_REQ},
    {CHB_IOCTL_CA_INTERVAL_SET, -1, TAG_CA, CMD_CA_INTERVAL_REQ},
};

char * ca_type_str[] = {
	[CA_TYPE_START] = "start",
	[CA_TYPE_PICKUP] = "pickup",
	[CA_TYPE_PUTDOWN] = "putdown",
	[CA_TYPE_ACTIVITY] = "activity",
	[CA_TYPE_HOLDING] = "holding",
	[CA_TYPE_MOTION] = "motion",
	[CA_TYPE_PLACEMENT] = "placement",
	[CA_TYPE_END] = "end",
};

static bool ca_status[CA_TYPE_END];
static int ca_ref_cnt;

static void update_ca_info(obj_cmd_t cmd, ca_type_t type)
{
    if (!(CA_TYPE_START <= type && type < CA_TYPE_END)) {
        return;
    }

    switch (cmd) {
        case CMD_CMN_OPEN_REQ:
            ca_status[type] = true;
            break;

        case CMD_CMN_CLOSE_REQ:
            ca_status[type] = false;
            break;

        default:
            hwlog_err("unknown cmd type in %s\n", __func__);
            __dmd_log_report(DSM_SHB_ERR_MCU_CA, __func__, "unknown cmd type\n");
            break;
    }
}

int send_ca_cmd_internal(int tag, obj_cmd_t cmd, ca_type_t type, bool use_lock)
{
    hwlog_info("send_ca_cmd_internal enter tag is %d\n", TAG_CA);
    uint8_t app_config[16] = {0,};
    pkt_header_t hpkt;
    pkt_cmn_interval_req_t i_pkt;
    pkt_cmn_close_req_t c_pkt;
    app_config[0] = type;
    app_config[1] = cmd;
    memset(&i_pkt, 0, sizeof(i_pkt));
    memset(&c_pkt, 0, sizeof(c_pkt));
    update_ca_info(cmd, type);
    static int print_count = 0;

    if (CMD_CMN_OPEN_REQ == cmd) {
        //send open ca cmd when open first sub type
        if (really_do_enable_disable(&ca_ref_cnt, true, type)) {
            hpkt.tag = tag;
            hpkt.cmd = cmd;
            hpkt.resp = NO_RESP;
            hpkt.length = 0;
            if (use_lock) {
                inputhub_mcu_write_cmd_adapter(&hpkt, sizeof(hpkt), NULL);
            } else {
                inputhub_mcu_write_cmd_nolock(&hpkt, sizeof(hpkt));
            }

            i_pkt.hd.tag = tag;
            i_pkt.hd.cmd = CMD_CMN_INTERVAL_REQ;
            i_pkt.hd.resp = NO_RESP;
            i_pkt.hd.length = sizeof(i_pkt.param);
           // i_pkt.param.reserved[0] = type;

            if (likely((type > CA_TYPE_START)&&(type < CA_TYPE_END))){
                hwlog_info("send_ca_cmd_internal open cmd:%d ca: %s !\n", cmd, ca_type_str[type]);
            }else{
                hwlog_info("send_ca_cmd_internal open cmd:%d ca: %d !\n", cmd, type);
            }
            if (use_lock) {
                inputhub_mcu_write_cmd_adapter(&i_pkt, sizeof(i_pkt), NULL);
            } else {
                inputhub_mcu_write_cmd_nolock(&i_pkt, sizeof(i_pkt));
            }
        }
        //send config cmd to open ca type
        send_app_config_cmd(TAG_CA, app_config, use_lock);
        print_count = ca_ref_cnt;
        hwlog_info("send_ca_cmd_internal config cmd:%d ca: %s !ca_ref_cnt= %x\n", cmd, ca_type_str[type],print_count);

    } else if ( CMD_CMN_CLOSE_REQ == cmd) {
        //send config cmd to close ca type
        send_app_config_cmd(TAG_CA, app_config, use_lock);
        print_count = ca_ref_cnt;
        hwlog_info("send_ca_cmd_internal config cmd:%d ca: %s !ca_ref_cnt= %x\n", cmd, ca_type_str[type], print_count);

        //send close ca cmd when all sub type closed
        if (really_do_enable_disable(&ca_ref_cnt, false, type)) {
            c_pkt.hd.tag = tag;
            c_pkt.hd.cmd = cmd;
            c_pkt.hd.resp = NO_RESP;
            c_pkt.hd.length = sizeof(c_pkt.close_param);
            //c_pkt.close_param.reserved[0] = type;

            if (likely((type > CA_TYPE_START)&&(type < CA_TYPE_END))){
                hwlog_info("send_ca_cmd_internal close cmd:%d ca: %s !\n", cmd, ca_type_str[type]);
            }else{
                hwlog_info("send_ca_cmd_internal close cmd:%d ca: %d !\n", cmd, type);
            }
            if (use_lock) {
                inputhub_mcu_write_cmd_adapter(&c_pkt, sizeof(c_pkt), NULL);
                hwlog_info("send_ca_cmd_internal inputhub_mcu_write_cmd_adapter cmd:%d ca: %d !\n", cmd, type);
            } else {
                inputhub_mcu_write_cmd_nolock(&c_pkt, sizeof(c_pkt));
                hwlog_info("send_ca_cmd_internal inputhub_mcu_write_cmd_nolock cmd:%d ca: %d !\n", cmd, type);
            }
        }
    } else if (CMD_CA_ATTR_ENABLE_REQ == cmd || CMD_CA_ATTR_DISABLE_REQ == cmd) {
        hwlog_info("send_ca_cmd_internal cmd:%d!\n", cmd);
    } else if (CMD_CA_INTERVAL_REQ == cmd) {
        hwlog_info("send_ca_cmd_internal cmd:%d!\n", cmd);
    } else {
        hwlog_err("send_ca_cmd_internal unknown cmd!\n");
        return -EINVAL;
    }

    hwlog_info("send_ca_cmd_internal leave!\n");
    return 0;
}

int send_ca_cmd(unsigned int cmd, unsigned long arg)
{
    void __user *argp = (void __user *)arg;
    int argvalue = 0;
    int i;

    hwlog_info("send_ca_cmd enter!\n");
    for (i = 0; i < sizeof(cas_cmd_map_tab) / sizeof(cas_cmd_map_tab[0]); ++i) {
        if (cas_cmd_map_tab[i].chb_ioctl_app_cmd == cmd) {
            break;
        }
    }

    if (sizeof(cas_cmd_map_tab) / sizeof(cas_cmd_map_tab[0]) == i) {
        hwlog_err("send_ca_cmd unknown cmd %d in parse_ca_cmd!\n", cmd);
        __dmd_log_report(DSM_SHB_ERR_MCU_CA, __func__, "send_ca_cmd unknown cmd in parse_ca_cmd!\n");
        return -EFAULT;
    }

    if (copy_from_user(&argvalue, argp, sizeof(argvalue))) {
        hwlog_err("send_ca_cmd copy_from_user failed!\n");
        return -EFAULT;
    }

    hwlog_info("send_ca_cmd leave before send_ca_cmd_internal!\n");
    return send_ca_cmd_internal(cas_cmd_map_tab[i].tag, cas_cmd_map_tab[i].cmd, argvalue, true);
}

static bool is_ca_data_report(const pkt_header_t *head)
{
	/*all sensors report data with command CMD_PRIVATE*/
	return (head->tag == TAG_CA)
	    && (CMD_CA_REPORT_REQ == head->cmd);
}

void enable_cas_when_recovery_iom3(void)
{
    ca_type_t type;
    //save step count when iom3 recovery
    ca_ref_cnt = 0;//to send open motion cmd when open first type
    for (type = CA_TYPE_START; type < CA_TYPE_END; ++type) {
        if (ca_status[type]) {
            hwlog_info("ca state %d in %s\n", type, __func__);
            send_ca_cmd_internal(TAG_CA, CMD_CA_OPEN_REQ, type, false);
        }
    }
}

void disable_cas_when_sysreboot(void)
{
    ca_type_t type;
    for (type = CA_TYPE_START; type < CA_TYPE_END; ++type) {
        if (ca_status[type]) {
            hwlog_info("ca state %d in %s\n", type, __func__);
            send_ca_cmd_internal(TAG_CA, CMD_CA_CLOSE_REQ, type, false);
        }
    }
}

void notify_modem_when_iom3_recovery_finish(void)
{
	uint16_t status = ST_RECOVERY_FINISH;
	hwlog_info("notify_modem_when_iom3_recovery_finish\n");
	write_customize_cmd_noresp(TAG_SYS, CMD_SYS_STATUSCHANGE_REQ, &status, sizeof(status));
}

void operations_when_recovery_iom3(void)
{
	hwlog_info("operations_when_recovery_iom3!\n");
	/*reset sensor calibrate when first*/
	reset_calibrate_when_recovery_iom3();
	/* recovery key */
	enable_key_when_recovery_iom3();
	/*recovery sensor*/
	enable_sensors_when_recovery_iom3();
	msleep(100);

	/*recovery motion*/
	enable_motions_when_recovery_iom3();
	enable_cas_when_recovery_iom3();
	enable_fingerprint_when_recovery_iom3();
	notify_modem_when_iom3_recovery_finish();
}

static bool is_extend_step_counter_cmd(const pkt_header_t *pkt)
{
	bool ret = false;

	if (pkt->tag != TAG_STEP_COUNTER)
		return false;

	switch (pkt->cmd) {
	case CMD_CMN_OPEN_REQ:
		/*could not judge which type step counter in open protocol*/
		break;

	case CMD_CMN_CLOSE_REQ:
		ret = (TYPE_EXTEND ==
		     ((pkt_cmn_close_req_t *) pkt)->close_param.reserved[0]);
		break;

	case CMD_CMN_INTERVAL_REQ:
		ret = (TYPE_EXTEND ==
		     ((pkt_cmn_interval_req_t *) pkt)->param.reserved[0]);
		break;

	default:
		break;
	}

	return ret;
}

int inputhub_sensor_enable_nolock(int tag, bool enable)
{
	close_param_t default_close_prama;
	memset(&default_close_prama, 0, sizeof(default_close_prama));
	default_close_prama.reserved[0] = TYPE_STANDARD;	/*for step counter*/
	return inputhub_sensor_enable_internal_nolock(tag, enable,
						      &default_close_prama);
}

int inputhub_sensor_setdelay_nolock(int tag, int delay_ms, int batch_count)
{
	open_param_t default_open_param = {
		.period = delay_ms,
		.batch_count = batch_count,
		.mode = AUTO_MODE,
		.reserved[0] = TYPE_STANDARD	/*for step counter only*/
	};
	return inputhub_sensor_setdelay_internal_nolock(tag,
							&default_open_param);
}

static uint16_t tranid;
int inputhub_mcu_write_cmd(const void *buf, unsigned int length)
{
#ifdef CONFIG_IOM3_RECOVERY
	bool is_in_recovery = false;
#endif

	int ret = 0;

	if (length > MAX_PKT_LENGTH) {
		hwlog_err("length = %d is too large in %s\n", (int)length,
			  __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "length is too large\n");
		return -EINVAL;
	}
	mutex_lock(&mutex_write_cmd);
#ifdef CONFIG_IOM3_RECOVERY
	if (g_iom3_state == IOM3_ST_NORMAL) {	/*false - send direct*/
	} else if (g_iom3_state == IOM3_ST_RECOVERY) {	/*true - only update*/
		is_in_recovery = true;
	} else if (g_iom3_state == IOM3_ST_REPEAT) {	/*IOM3_ST_REPEAT...BLOCK IN HERE, WAIT FOR REPEAT COMPLETE*/
		hwlog_err("wait for iom3 recovery complete\n");
		mutex_unlock(&mutex_write_cmd);
		wait_event(iom3_rec_wq, (g_iom3_state == IOM3_ST_NORMAL));
		hwlog_err("wakeup for iom3 recovery complete\n");
		mutex_lock(&mutex_write_cmd);
	} else {
		hwlog_err("unknown iom3 state %d\n", g_iom3_state);
	}
	if (true == is_in_recovery) {
		mutex_unlock(&mutex_write_cmd);
		goto update_info;
	}
#endif
	((pkt_header_t *) buf)->tranid = tranid++;
	ret = unpack(buf, length);
	mutex_unlock(&mutex_write_cmd);

update_info:
	if ((TAG_SENSOR_BEGIN <= ((pkt_header_t *) buf)->tag
	     && ((pkt_header_t *) buf)->tag < TAG_END)) {
	     update_current_app_status(((pkt_header_t *) buf)->tag,((pkt_header_t *) buf)->cmd);
		if (!is_extend_step_counter_cmd(((const pkt_header_t *)buf))) {
			update_sensor_info(((const pkt_header_t *)buf));
		}
	}

	if (ret && (false == is_in_recovery)) {
		iom3_need_recovery(SENSORHUB_MODID, SH_FAULT_IPC_TX_TIMEOUT);
	}

	return 0;
}

struct motions_cmd_map {
	int mhb_ioctl_app_cmd;
	int motion_type;
	int tag;
	obj_cmd_t cmd;
};
static const struct motions_cmd_map motions_cmd_map_tab[] = {
	{MHB_IOCTL_MOTION_START, -1, TAG_MOTION, CMD_CMN_OPEN_REQ},
	{MHB_IOCTL_MOTION_STOP, -1, TAG_MOTION, CMD_CMN_CLOSE_REQ},
	{MHB_IOCTL_MOTION_ATTR_START, -1, TAG_MOTION,
	 CMD_MOTION_ATTR_ENABLE_REQ},
	{MHB_IOCTL_MOTION_ATTR_STOP, -1, TAG_MOTION,
	 CMD_MOTION_ATTR_DISABLE_REQ},
	{MHB_IOCTL_MOTION_INTERVAL_SET, -1, TAG_MOTION,
	 CMD_MOTION_INTERVAL_REQ},
};

static bool is_motion_data_report(const pkt_header_t *head)
{
	/*all sensors report data with command CMD_PRIVATE*/
	return (head->tag == TAG_MOTION)
	    && (CMD_MOTION_REPORT_REQ == head->cmd);
}

static int inputhub_sensor_enable_internal(int tag, bool enable,
					   close_param_t *param)
{
	if (NULL == param) {
		hwlog_err("NULL pointer param in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "NULL pointer param\n");
		return -EINVAL;
	}

	if (ap_sensor_enable(tag, enable)) {
		return 0;
	}

	if (TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END) {
		if (enable) {
			pkt_header_t pkt = (pkt_header_t) {
				.tag = tag,
				.cmd = CMD_CMN_OPEN_REQ,
				.resp = NO_RESP,
				.length = 0
			};

			hwlog_info("open sensor %s (tag:%d)!\n",
				   obj_tag_str[tag] ? obj_tag_str[tag] :
				   "TAG_UNKNOWN", tag);
			return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt),
							      NULL);
		} else {
			pkt_cmn_close_req_t pkt;
			memset(&pkt, 0, sizeof(pkt));
			pkt.hd.tag = tag;
			pkt.hd.cmd = CMD_CMN_CLOSE_REQ;
			pkt.hd.resp = NO_RESP;
			pkt.hd.length = sizeof(close_param_t);
			memcpy(&pkt.close_param, param,
			       sizeof(pkt.close_param));

			hwlog_info("close sensor %s (tag:%d)!\n",
				   obj_tag_str[tag] ? obj_tag_str[tag] :
				   "TAG_UNKNOWN", tag);
			return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt),
							      NULL);
		}
	} else {
		hwlog_err("unknown sensor type in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "unknown sensor type\n");
		return -EINVAL;
	}
}

static int inputhub_sensor_setdelay_internal(int tag, open_param_t *param)
{
	pkt_cmn_interval_req_t pkt;

	if (NULL == param) {
		hwlog_err("NULL pointer param in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "NULL pointer param\n");
		return -EINVAL;
	}

	if (ap_sensor_setdelay(tag, param->period))
		return 0;

	if (tag == TAG_LABC) {
		int labc_data[3];
		labc_data[0] = -1;
		labc_data[1] = -1;
		labc_data[2] = -1;
		report_sensor_event(TAG_LABC, labc_data, sizeof(labc_data));
	}

	if (TAG_SENSOR_BEGIN <= tag && tag < TAG_SENSOR_END) {
		memset(&pkt, 0, sizeof(pkt));
		pkt.hd.tag = tag;
		pkt.hd.cmd = CMD_CMN_INTERVAL_REQ;
		pkt.hd.resp = NO_RESP;
		pkt.hd.length = sizeof(open_param_t);
		memcpy(&pkt.param, param, sizeof(pkt.param));
		hwlog_info("set sensor %s (tag:%d) delay %d ms!\n",
			   obj_tag_str[tag] ? obj_tag_str[tag] : "TAG_UNKNOWN",
			   tag, param->period);
		return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt), NULL);
	} else {
		hwlog_err("unknown sensor type in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "unknown sensor type\n");
		return -EINVAL;
	}
}

static int extend_step_counter_process(bool enable)
{
	uint8_t app_config[16] = { 0, };
	close_param_t extend_close_param;
	memset(&extend_close_param, 0, sizeof(extend_close_param));
	extend_close_param.reserved[0] = TYPE_EXTEND;
	app_config[0] = enable;
	app_config[1] = TYPE_EXTEND;
	hwlog_info("%s extend_step_counte!\n", enable ? "open" : "close");
	/*close step counter*/
	if (!enable) {
		send_app_config_cmd(TAG_STEP_COUNTER, app_config, true);
	}
	if (really_do_enable_disable(&step_ref_cnt, enable, TYPE_EXTEND)) {
		inputhub_sensor_enable_internal(TAG_STEP_COUNTER, enable,
						&extend_close_param);
	}
	if (enable) {
		open_param_t extend_open_param = {
			.period = 20,	/*default delay_ms*/
			.batch_count = 1,
			.mode = AUTO_MODE,
			.reserved[0] = TYPE_EXTEND
		};

		inputhub_sensor_setdelay_internal(TAG_STEP_COUNTER,
						  &extend_open_param);
		return send_app_config_cmd(TAG_STEP_COUNTER, app_config, true);
	}
	return 0;
}

char *motion_type_str[] = {
	[MOTION_TYPE_START] = "start",
	[MOTION_TYPE_PICKUP] = "pickup",
	[MOTION_TYPE_FLIP] = "flip",
	[MOTION_TYPE_PROXIMITY] = "proximity",
	[MOTION_TYPE_SHAKE] = "shake",
	[MOTION_TYPE_TAP] = "tap",
	[MOTION_TYPE_TILT_LR] = "tilt_lr",
	[MOTION_TYPE_ROTATION] = "rotation",
	[MOTION_TYPE_POCKET] = "pocket",
	[MOTION_TYPE_ACTIVITY] = "activity",
	[MOTION_TYPE_TAKE_OFF] = "take_off",
	[MOTION_TYPE_EXTEND_STEP_COUNTER] = "ext_step_counter",
	[MOTION_TYPE_END] = "end",
};

extern int stop_auto_motion;
int send_motion_cmd_internal(int tag, obj_cmd_t cmd, motion_type_t type,
			     bool use_lock)
{
	uint8_t app_config[16] = { 0, };
	pkt_header_t hpkt;
	pkt_cmn_interval_req_t i_pkt;
	pkt_cmn_close_req_t c_pkt;
	static int print_count = 0;
	app_config[0] = type;
	app_config[1] = cmd;
	memset(&i_pkt, 0, sizeof(i_pkt));
	memset(&c_pkt, 0, sizeof(c_pkt));

    if(stop_auto_motion == 1) {
		hwlog_info("%s stop_auto_motion: %d !",
					__func__, stop_auto_motion);
		return 0;
	}

	if (MOTIONHUB_TYPE_HW_STEP_COUNTER == type) {
		if (CMD_CMN_OPEN_REQ == cmd || CMD_CMN_CLOSE_REQ == cmd) {
			if (use_lock) {
				return
				    extend_step_counter_process(CMD_CMN_OPEN_REQ
								== cmd);
			} else {
				return
				    extend_step_counter_process_nolock
				    (CMD_CMN_OPEN_REQ == cmd);
			}
		}
	}

	if (CMD_CMN_OPEN_REQ == cmd) {
		/*send open motion cmd when open first sub type*/
		if (really_do_enable_disable(&motion_ref_cnt, true, type)) {
			hpkt.tag = tag;
			hpkt.cmd = cmd;
			hpkt.resp = NO_RESP;
			hpkt.length = 0;
			if (use_lock) {
				inputhub_mcu_write_cmd_adapter(&hpkt,
							       sizeof(hpkt),
							       NULL);
			} else {
				inputhub_mcu_write_cmd_nolock(&hpkt,
							      sizeof(hpkt));
			}

			i_pkt.hd.tag = tag;
			i_pkt.hd.cmd = CMD_CMN_INTERVAL_REQ;
			i_pkt.hd.resp = NO_RESP;
			i_pkt.hd.length = sizeof(i_pkt.param);
			/* i_pkt.param.reserved[0] = type;*/

			if (likely
			    ((type > MOTION_TYPE_START)
			     && (type < MOTION_TYPE_END))) {
				hwlog_info
				    ("send_motion_cmd open cmd:%d motion: %s !",
				     cmd, motion_type_str[type]);
			} else {
				hwlog_info
				    ("send_motion_cmd open cmd:%d motion: %d !",
				     cmd, type);
			}
			if (use_lock) {
				inputhub_mcu_write_cmd_adapter(&i_pkt,
							       sizeof(i_pkt),
							       NULL);
			} else {
				inputhub_mcu_write_cmd_nolock(&i_pkt,
							      sizeof(i_pkt));
			}
		}
		/*send config cmd to open motion type*/
		send_app_config_cmd(TAG_MOTION, app_config, use_lock);
		print_count = motion_ref_cnt;
		hwlog_info
		    ("send_motion_cmd config cmd:%d motion: %s !motion_ref_cnt= %x",
		     cmd, motion_type_str[type], print_count);

	} else if (CMD_CMN_CLOSE_REQ == cmd) {
		/*send config cmd to close motion type*/
		send_app_config_cmd(TAG_MOTION, app_config, use_lock);
		print_count = motion_ref_cnt;
		hwlog_info("send_motion_cmd config cmd:%d motion: %s !motion_ref_cnt= %x",
		     cmd, motion_type_str[type], print_count);

		/*send close motion cmd when all sub type closed*/
		if (really_do_enable_disable(&motion_ref_cnt, false, type)) {
			c_pkt.hd.tag = tag;
			c_pkt.hd.cmd = cmd;
			c_pkt.hd.resp = NO_RESP;
			c_pkt.hd.length = sizeof(c_pkt.close_param);
			/*c_pkt.close_param.reserved[0] = type;*/

			if (likely
			    ((type > MOTION_TYPE_START)
			     && (type < MOTION_TYPE_END))) {
				hwlog_info("send_motion_cmd close cmd:%d motion: %s !",
				     cmd, motion_type_str[type]);
			} else {
				hwlog_info("send_motion_cmd close cmd:%d motion: %d !",
				     cmd, type);
			}
			if (use_lock) {
				inputhub_mcu_write_cmd_adapter(&c_pkt,
							       sizeof(c_pkt),
							       NULL);
			} else {
				inputhub_mcu_write_cmd_nolock(&c_pkt,
							      sizeof(c_pkt));
			}
		}
	} else if (CMD_MOTION_ATTR_ENABLE_REQ == cmd
		   || CMD_MOTION_ATTR_DISABLE_REQ == cmd) {
		hwlog_err("send_motion_cmd cmd:%d!", cmd);
	} else if (CMD_MOTION_INTERVAL_REQ == cmd) {
		hwlog_err("send_motion_cmd cmd:%d!", cmd);
	} else {
		hwlog_err("send_motion_cmd unknown cmd!\n");
		return -EINVAL;
	}

	return 0;
}

int send_motion_cmd(unsigned int cmd, unsigned long arg)
{
	void __user *argp = (void __user *)arg;
	int argvalue = 0;
	int i;

	for (i = 0;
	     i < sizeof(motions_cmd_map_tab) / sizeof(motions_cmd_map_tab[0]);
	     ++i) {
		if (motions_cmd_map_tab[i].mhb_ioctl_app_cmd == cmd) {
			break;
		}
	}

	if (sizeof(motions_cmd_map_tab) / sizeof(motions_cmd_map_tab[0]) == i) {
		hwlog_err
		    ("send_motion_cmd unknown cmd %d in parse_motion_cmd!\n",
		     cmd);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "send_motion_cmd unknown cmd in parse_motion_cmd!\n");
		return -EFAULT;
	}

	if (copy_from_user(&argvalue, argp, sizeof(argvalue)))
		return -EFAULT;

	if (!
	    (MOTION_TYPE_START <= argvalue
	     && argvalue < MOTION_TYPE_END)) {
		hwlog_err("error motion type %d in %s\n", argvalue, __func__);
		return -EINVAL;
	}
	update_motion_info(motions_cmd_map_tab[i].cmd, argvalue);

	return send_motion_cmd_internal(motions_cmd_map_tab[i].tag,
					motions_cmd_map_tab[i].cmd, argvalue,
					true);
}


int send_apr_log(void)
{
	char cmd[256];
	char time_buf[16];
	int ret = 0;

	get_time_stamp(time_buf, 16);
	snprintf(cmd, 256, "%s%s%s",
		 "archive -i /data/android_logs/kmsgcat-log -i /data/android_logs/kmsgcat-log.1 -i /data/android_logs/applogcat-log "
		 "-i /data/android_logs/applogcat-log.1 -i /data/rdr/dump_00.bin -i /data/rdr/dump_01.bin -i /data/rdr/dump_02.bin -o ",
		 time_buf, "_sensorhubErr -z zip");
	ret = log_to_exception("sensorhub", cmd);
	if (ret < 0)
		hwlog_err("logexception sysfs err.\n");
	__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
		       "logexception sysfs err\n");
	return ret;
}

int inputhub_sensor_enable(int tag, bool enable)
{
	uint8_t app_config[16] = { 0, };
	close_param_t default_close_prama;
	memset(&default_close_prama, 0, sizeof(default_close_prama));
	default_close_prama.reserved[0] = TYPE_STANDARD;	/*for step counter*/
	if (tag == TAG_STEP_COUNTER) {
		hwlog_info("TAG_STEP_COUNTER %d, enabe:%d in %s!\n", tag,
			   enable, __func__);
		if (!enable) {
			app_config[0] = enable;
			app_config[1] = TYPE_STANDARD;
			send_app_config_cmd(TAG_STEP_COUNTER, app_config, true);
			if (really_do_enable_disable
			    (&step_ref_cnt, enable, TYPE_STANDARD))
				return inputhub_sensor_enable_internal(tag,
								       enable,
								       &default_close_prama);
		} else {
			hwlog_info(" TAG_STEP_COUNTER %d, enabe:%d in %s!\n",
				   tag, enable, __func__);
			if (really_do_enable_disable
			    (&step_ref_cnt, enable, TYPE_STANDARD)) {
				return inputhub_sensor_enable_internal(tag,
								       enable,
								       &default_close_prama);
			}
		}
	} else
		return inputhub_sensor_enable_internal(tag, enable,
						       &default_close_prama);
}

int inputhub_sensor_setdelay(int tag, int delay_ms)
{
	open_param_t default_open_param = {
		.period = delay_ms,
		.batch_count = 1,
		.mode = AUTO_MODE,
		.reserved[0] = TYPE_STANDARD	/*for step counter only*/
	};
	return inputhub_sensor_setdelay_internal(tag, &default_open_param);
}

bool ap_sensor_flush(int tag)
{
	struct sensor_data event;
	bool work_on_ap = all_ap_sensor_operations[tag].work_on_ap;

	if (work_on_ap) {
		if (all_ap_sensor_operations[tag].ops.enable) {/*leave this code for furture use*/
			all_ap_sensor_operations[tag].ops.enable(1);
			msleep(60);
		}
		event.type = tag_to_hal_sensor_type[TAG_FLUSH_META];
		event.length = 4;
		event.value[0] = tag_to_hal_sensor_type[tag];
		return inputhub_route_write_batch(ROUTE_SHB_PORT,
						  (char *)&event,
						  event.length +
						  OFFSET_OF_END_MEM(struct
								    sensor_data,
								    length), 0);
	}

	return work_on_ap;
}

int send_sensor_batch_flush_cmd(unsigned int cmd, struct ioctl_para *para,
				int tag)
{
	if (SHB_IOCTL_APP_SENSOR_BATCH == cmd) {
		open_param_t batch_param = {
			.period = para->period_ms,
			.batch_count =
			    (para->timeout_ms >
			     para->period_ms) ? (para->timeout_ms /
						 para->period_ms) : 1,
			.mode = AUTO_MODE,
		};
		hwlog_info("batch in %s period=%d, count=%d\n", __func__,
			   para->period_ms, batch_param.batch_count);
		return inputhub_sensor_setdelay_internal(tag, &batch_param);
	} else if (SHB_IOCTL_APP_SENSOR_FLUSH == cmd) {
		hwlog_info("flush in %s \n", __func__);
		ap_sensor_flush(tag);
		pkt_header_t pkt = (pkt_header_t) {
			.tag = tag,
			.cmd = CMD_CMN_FLUSH_REQ,
			.resp = NO_RESP,
			.length = 0
		};

		hwlog_info("flush sensor %s (tag:%d)!\n",
			   obj_tag_str[tag] ? obj_tag_str[tag] : "TAG_UNKNOWN",
			   tag);
		return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt), NULL);
	}
	return 0;
}

static int send_sensor_cmd(unsigned int cmd, unsigned long arg)
{
	uint8_t app_config[16] = { 0, };
	void __user *argp = (void __user *)arg;
	int tag = 0;
	int ret = 0;
	struct ioctl_para para;

	if (copy_from_user(&para, argp, sizeof(para)))
		return -EFAULT;

	if (!
	    (SENSORHUB_TYPE_BEGIN <= para.shbtype
	     && para.shbtype < SENSORHUB_TYPE_END)) {
		hwlog_err("error shbtype %d in %s\n", para.shbtype, __func__);
		return -EINVAL;
	}

	tag = hal_sensor_type_to_tag[para.shbtype];
	switch (cmd) {
	case SHB_IOCTL_APP_ENABLE_SENSOR:
	case SHB_IOCTL_APP_DISABLE_SENSOR:
		return inputhub_sensor_enable(tag,
					      SHB_IOCTL_APP_ENABLE_SENSOR ==
					      cmd);
		break;

	case SHB_IOCTL_APP_DELAY_SENSOR:
		if (tag == TAG_STEP_COUNTER) {
			inputhub_sensor_setdelay(tag, para.delay_ms);
			app_config[0] = 1;
			app_config[1] = TYPE_STANDARD;
			return send_app_config_cmd(TAG_STEP_COUNTER, app_config,
						   true);
		} else {
			return inputhub_sensor_setdelay(tag, para.delay_ms);
		}

		break;
	case SHB_IOCTL_APP_SENSOR_BATCH:
	case SHB_IOCTL_APP_SENSOR_FLUSH:
		if (tag == TAG_STEP_COUNTER) {
			ret = send_sensor_batch_flush_cmd(cmd, &para, tag);
			if (0 == ret) {
				/*success*/
				app_config[0] = 1;
				app_config[1] = TYPE_STANDARD;
				return send_app_config_cmd(TAG_STEP_COUNTER,
							   app_config, true);
			} else {
				/*fail*/
				hwlog_err
				    ("send_sensor_cmd failed %d in %s %d!\n",
				     cmd, __func__, __LINE__);
				return ret;
			}
		} else {
			return send_sensor_batch_flush_cmd(cmd, &para, tag);
		}
		break;
	default:
		hwlog_err("unknown shb_hal_cmd %d in %s!\n", cmd, __func__);
		return -EINVAL;
	}

	return 0;
}

static bool cmd_match(int req, int resp)
{
	return (req + 1) == resp;
}

/*use lock for all command to avoid conflict*/
int inputhub_mcu_write_cmd_adapter(const void *buf, unsigned int length,
				   struct read_info *rd)
{
	int ret = 0;
	unsigned long flags = 0;
	int retry_count = 2;

	mutex_lock(&mutex_write_adapter);

	if (NULL == rd) {
		ret = inputhub_mcu_write_cmd(buf, length);
	} else {
		mutex_lock(&type_record.lock_mutex);
		spin_lock_irqsave(&type_record.lock_spin, flags);
		type_record.pkt_info = ((pkt_header_t *) buf);
		type_record.rd = rd;
		spin_unlock_irqrestore(&type_record.lock_spin, flags);
		while (retry_count--) {	/*send retry 3 times*/
			/*send data to mcu*/
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
			INIT_COMPLETION(type_record.resp_complete);
#else
			reinit_completion(&type_record.resp_complete);
#endif
			if (inputhub_mcu_write_cmd(buf, length)) {
				hwlog_err("send cmd to mcu failed in %s, retry %d\n",
				     __func__, retry_count);
			} else
			    if (!wait_for_completion_timeout
				(&type_record.resp_complete,
				 msecs_to_jiffies(iom3_timeout))) {
				hwlog_err
				    ("wait for response timeout in %s, retry %d. tag %d cmd %d\n",
				     __func__, retry_count,
				     ((pkt_header_t *) buf)->tag,
				     ((pkt_header_t *) buf)->cmd);
				if (retry_count == 0) {
					iom3_need_recovery(SENSORHUB_MODID, SH_FAULT_IPC_RX_TIMEOUT);
				}
#ifdef SENSOR_DSM_CONFIG
				if (!dsm_client_ocuppy(shb_dclient)) {
					dsm_client_record(shb_dclient,
							  "Command tag - %d, cmd - %d\n",
							  ((pkt_header_t *)
							   buf)->tag,
							  ((pkt_header_t *)
							   buf)->cmd);
					dsm_client_notify(shb_dclient,
							  DSM_SHB_ERR_IOM7_IPC_TIMEOUT);
				}
#endif
			} else {
				ret = 0;	/*send success & response success*/
				break;
			}
		}

		/*clear infor*/
		spin_lock_irqsave(&type_record.lock_spin, flags);
		type_record.pkt_info = NULL;
		type_record.rd = NULL;
		spin_unlock_irqrestore(&type_record.lock_spin, flags);
		mutex_unlock(&type_record.lock_mutex);
	}

	mutex_unlock(&mutex_write_adapter);

	return ret;
}

int write_customize_cmd(const struct write_info *wr, struct read_info *rd)
{
	char buf[MAX_PKT_LENGTH];

	if (NULL == wr) {
		hwlog_err("NULL pointer in %s\n", __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "NULL pointer\n");
		return -EINVAL;
	}

	if (wr->tag < TAG_BEGIN || wr->tag >= TAG_END) {
		hwlog_err("tag = %d error in %s\n", wr->tag, __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__, "tag error\n");
		return -EINVAL;
	}
	if (wr->wr_len + sizeof(pkt_header_t) > MAX_PKT_LENGTH) {
		hwlog_err("-----------> wr_len = %d is too large in %s\n",
			  wr->wr_len, __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "-------> write length is too large\n");
		return -EINVAL;
	}
	memset(&buf, 0, sizeof(buf));
	((pkt_header_t *) buf)->tag = wr->tag;
	((pkt_header_t *) buf)->cmd = wr->cmd;
	((pkt_header_t *) buf)->resp = ((rd != NULL) ? (RESP) : (NO_RESP));
	((pkt_header_t *) buf)->length = wr->wr_len;
	if (wr->wr_buf != NULL) {
		memcpy(buf + sizeof(pkt_header_t), wr->wr_buf, wr->wr_len);
	}

	return inputhub_mcu_write_cmd_adapter(buf,
					      sizeof(pkt_header_t) + wr->wr_len,
					      rd);
}

static bool is_sensor_data_report(const pkt_header_t *head)
{
	/*all sensors report data with command CMD_PRIVATE*/
	return (TAG_SENSOR_BEGIN <= head->tag && head->tag < TAG_SENSOR_END)
	    && (CMD_PRIVATE == head->cmd);
}

static bool is_fingersense_zaxis_data_report(const pkt_header_t *head)
{
	return (TAG_FINGERSENSE == head->tag)
	    && (CMD_ACCEL_FINGERSENSE_DATA_REPORT == head->cmd);
}

static bool is_requirement_resp(const pkt_header_t *head)
{
	return (0 == (head->cmd & 1));	/*even cmds are resp cmd*/
}

static int report_resp_data(const pkt_header_resp_t *head)
{
	int ret = 0;
	unsigned long flags = 0;

	spin_lock_irqsave(&type_record.lock_spin, flags);
	if (type_record.rd != NULL && type_record.pkt_info != NULL	/*check record info*/
	    && (cmd_match(type_record.pkt_info->cmd, head->cmd))
	    && (type_record.pkt_info->tranid == head->tranid)) {	/*rcv resp from mcu*/
		if (head->length <= (MAX_PKT_LENGTH + sizeof(head->errno))) {	/*data length ok*/
			type_record.rd->errno = head->errno;	/*fill errno to app*/
			type_record.rd->data_length = (head->length - sizeof(head->errno));	/*fill data_length to app, data_length means data lenght below*/
			memcpy(type_record.rd->data, (char *)head + sizeof(pkt_header_resp_t), type_record.rd->data_length);	/*fill resp data to app*/
		} else {	/*resp data too large*/
			type_record.rd->errno = -EINVAL;
			type_record.rd->data_length = 0;
			hwlog_err("data too large from mcu in %s\n", __func__);
			__dmd_log_report(DSM_SHB_ERR_IOM7_OTHER, __func__,
				       "data too large from mcu\n");
		}
		complete(&type_record.resp_complete);
	}
	spin_unlock_irqrestore(&type_record.lock_spin, flags);

	return ret;
}

struct mcu_notifier_work {
	struct work_struct worker;
	void *data;
};

struct mcu_notifier_node {
	int tag;
	int cmd;
	int (*notify) (const pkt_header_t *data);
	struct list_head entry;
};

struct mcu_notifier {
	struct list_head head;
	spinlock_t lock;
	struct workqueue_struct *mcu_notifier_wq;
};

static struct mcu_notifier mcu_notifier = { LIST_HEAD_INIT(mcu_notifier.head) };

static void init_mcu_notifier_list(void)
{
	INIT_LIST_HEAD(&mcu_notifier.head);
	spin_lock_init(&mcu_notifier.lock);
	mcu_notifier.mcu_notifier_wq =
	    create_freezable_workqueue("mcu_event_notifier");
}

static void mcu_notifier_handler(struct work_struct *work)
{
	/*find data according work*/
	struct mcu_notifier_work *p =
	    container_of(work, struct mcu_notifier_work, worker);

	/*search mcu_notifier, call all call_backs*/
	struct mcu_notifier_node *pos, *n;
	list_for_each_entry_safe(pos, n, &mcu_notifier.head, entry) {
		if ((pos->tag == ((const pkt_header_t *)p->data)->tag)
		    && (pos->cmd == ((const pkt_header_t *)p->data)->cmd)) {
			if (pos->notify != NULL) {
				pos->notify((const pkt_header_t *)p->data);
			}
		}
	}

	kfree(p->data);
	kfree(p);
}

static void inputhub_process_sensor_report_notifier_handler(struct work_struct *work)
{
	/*find data according work*/
	struct mcu_notifier_work *p =
	    container_of(work, struct mcu_notifier_work, worker);

    inputhub_process_sensor_report((const pkt_header_t *)p->data);
    
	kfree(p->data);
	kfree(p);    
}


static const void *avoid_coverity_p_work;
static const void *avoid_coverity_p_void;
static void mcu_notifier_queue_work(const pkt_header_t *head, void (*fn)(struct work_struct *work))
{
	struct mcu_notifier_work *notifier_work =
	    kmalloc(sizeof(struct mcu_notifier_work), GFP_ATOMIC);
	if (NULL == notifier_work)
		return;
	memset(notifier_work, 0, sizeof(struct mcu_notifier_work));
	notifier_work->data =
	    kmalloc(head->length + sizeof(pkt_header_t), GFP_ATOMIC);
	if (NULL == notifier_work->data) {
		kfree(notifier_work);
		return;
	}
	memset(notifier_work->data, 0, head->length + sizeof(pkt_header_t));
	memcpy(notifier_work->data, head, sizeof(pkt_header_t) + head->length);
	INIT_WORK(&notifier_work->worker, fn);
	queue_work(mcu_notifier.mcu_notifier_wq, &notifier_work->worker);

    /**begin: save alloc ptr, just to solve coverity warning**/
	avoid_coverity_p_work = notifier_work;
	avoid_coverity_p_void = notifier_work->data;
    /**end: save alloc ptr, just to solve coverity warning**/
}

static bool is_mcu_notifier(const pkt_header_t *head)
{
	struct mcu_notifier_node *pos, *n;
	list_for_each_entry_safe(pos, n, &mcu_notifier.head, entry) {
		if ((pos->tag == head->tag) && (pos->cmd == head->cmd))
			return true;
	}

	return false;
}

static bool is_mcu_wakeup(const pkt_header_t *head)
{
	if ((TAG_SYS == head->tag) && (CMD_SYS_STATUSCHANGE_REQ == head->cmd)
	    && (ST_WAKEUP == ((pkt_sys_statuschange_req_t *) head)->status)) {
		return true;
	}
	return false;
}

static bool is_mcu_resume_mini(const pkt_header_t *head)
{
	if ((TAG_SYS == head->tag)
	    && (CMD_SYS_STATUSCHANGE_REQ == head->cmd)
	    && ST_MINSYSREADY == ((pkt_sys_statuschange_req_t *) head)->status
	    && IOM3_RECOVERY_MINISYS != atomic_read(&iom3_rec_state)) {
		return true;
	}
	return false;
}

static bool is_mcu_resume_all(const pkt_header_t *head)
{
	if ((TAG_SYS == head->tag)
	    && (CMD_SYS_STATUSCHANGE_REQ == head->cmd)
	    && ST_MCUREADY == ((pkt_sys_statuschange_req_t *) head)->status
	    && IOM3_RECOVERY_MINISYS != atomic_read(&iom3_rec_state)) {
		return true;
	}
	return false;
}

int register_mcu_event_notifier(int tag, int cmd,
				int (*notify) (const pkt_header_t *head))
{
	struct mcu_notifier_node *pnode, *n;
	int ret = 0;
	unsigned long flags = 0;

	if ((!(TAG_BEGIN <= tag && tag < TAG_END)) || (NULL == notify))
		return -EINVAL;

	spin_lock_irqsave(&mcu_notifier.lock, flags);
	/*avoid regist more than once*/
	list_for_each_entry_safe(pnode, n, &mcu_notifier.head, entry) {
		if ((tag == pnode->tag) && (cmd == pnode->cmd)
		    && (notify == pnode->notify)) {
			hwlog_warn
			    ("tag = %d, cmd = %d, notify = %pf has already registed in %s\n!",
			     tag, cmd, notify, __func__);
			goto out;	/*return when already registed*/
		}
	}

	/*make mcu_notifier_node*/
	pnode = kmalloc(sizeof(struct mcu_notifier_node), GFP_ATOMIC);
	if (NULL == pnode) {
		ret = -ENOMEM;
		goto out;
	}
	memset(pnode, 0, sizeof(struct mcu_notifier_node));
	pnode->tag = tag;
	pnode->cmd = cmd;
	pnode->notify = notify;

	/*add to list*/
	list_add(&pnode->entry, &mcu_notifier.head);
out:
	spin_unlock_irqrestore(&mcu_notifier.lock, flags);
    /**begin: save alloc ptr, just to solve coverity warning**/
	avoid_coverity_p_void = pnode;
    /**end: save alloc ptr, just to solve coverity warning**/

	return ret;
}

int unregister_mcu_event_notifier(int tag, int cmd,
				  int (*notify) (const pkt_header_t *head))
{
	struct mcu_notifier_node *pos, *n;
	unsigned long flags = 0;

	if ((!(TAG_BEGIN <= tag && tag < TAG_END)) || (NULL == notify))
		return -EINVAL;

	spin_lock_irqsave(&mcu_notifier.lock, flags);
	list_for_each_entry_safe(pos, n, &mcu_notifier.head, entry) {
		if ((tag == pos->tag) && (cmd == pos->cmd)
		    && (notify == pos->notify)) {
			list_del(&pos->entry);
			kfree(pos);
			break;
		}
	}
	spin_unlock_irqrestore(&mcu_notifier.lock, flags);

	return 0;
}

static void step_counter_data_process(pkt_step_counter_data_req_t *head)
{
	int standard_data_len = sizeof(head->step_count);
	valid_step_count = recovery_step_count + head->step_count;
	head->total_step_count = head->step_count = valid_step_count;
	valid_floor_count = recovery_floor_count + head->total_floor_ascend;
	head->total_floor_ascend = valid_floor_count;

	if ((head->record_count > 0) && (head->record_count != EXT_PEDO_VERSION_2) ) {//extend step counter data structure changed
		int extend_effect_len = head->hd.length - standard_data_len;	/*skip head and step_count*/
		char motion_data[extend_effect_len + 1];	/*reserve 1 byte for motion type*/
		motion_data[0] = MOTIONHUB_TYPE_HW_STEP_COUNTER;	/*add motion type*/
		memcpy(motion_data + 1, &head->begin_time, extend_effect_len);	/*the offset rely on sizeof enum motion_type_t of mcu, now it is 1, we suggest motion_type_t use uint8_t, because sizeof(enum) may diffrernt between AP and mcu;*/
		hwlog_info
		    ("write extend step counter data to motion event buffer, record_count = %d!\n",
		     (head->record_count >
		      EXT_PEDO_VERSION_2) ? (head->record_count -
				      EXT_PEDO_VERSION_2) : (head->record_count));
		inputhub_route_write(ROUTE_MOTION_PORT, motion_data, extend_effect_len + 1);	/*report extend step counter date to motion HAL*/
	}

	hwlog_info
	    ("convert to standard step counter data to sensor event buffer, step_count = %d!\n",
	     head->step_count);
	head->hd.length = standard_data_len;	/*avoid report extend data to sensor HAL, convert to standard step counter data, just report member step_count to sensor HAL*/
}

#define LOG_LEVEL_FATAL 0
static bool is_dmd_log_data_report(const pkt_header_t *head)
{
	/*all sensors report data with command CMD_PRIVATE*/
	pkt_dmd_log_report_req_t *buf = (pkt_dmd_log_report_req_t *) head;
	return (TAG_LOG == head->tag) && (CMD_LOG_REPORT_REQ == head->cmd)
	    && (buf->level == LOG_LEVEL_FATAL);
}

static bool is_additional_info_report(const pkt_header_t *head)
{
	return CMD_ADDITIONAL_INFO_REQ == head->cmd;
}
int sensor_need_reset_power(pkt_dmd_log_report_req_t* pkt)
{
    struct timespec ts;
    int ret = 0;

    if (!need_reset_io_power)
    { goto OUT; }

    get_monotonic_boottime(&ts);

    if ((pkt->dmd_id == DSM_SHB_ERR_MCU_ALS ) && (pkt->dmd_case == DMD_CASE_ALS_NEED_RESET_POWER ))
    {
        pkt->hd.tag = TAG_ALS;
        if ((ts.tv_sec - als_last_reset_period) > RESET_REFRESH_PERIOD)
        {
            als_last_reset_period = ts.tv_sec;
            als_retry_cnt = ALS_RESET_COUNT;
        }

        if (als_retry_cnt)
        {
            als_retry_cnt--;
            ret = 1;
        }
        else
        {
            hwlog_err("als abnormal exceed reset limit\n");
        }
    }
    if ((pkt->dmd_id == DSM_SHB_ERR_MCU_PS ) && (pkt->dmd_case == DMD_CASE_PS_NEED_RESET_POWER ))
    {
        pkt->hd.tag = TAG_PS;
        if ((ts.tv_sec - ps_last_reset_period) > RESET_REFRESH_PERIOD)
        {
            ps_last_reset_period = ts.tv_sec;
            ps_retry_cnt = PS_RESET_COUNT;
        }

        if (ps_retry_cnt)
        {
            ps_retry_cnt--;
            ret = 1;
        }
        else
        {
            hwlog_err("ps abnormal exceed reset limit\n");
        }
    }

OUT:
     return ret;
}

static int apr_count = 100;
void iom7_dmd_log_handle(struct work_struct *work)
{
	struct iom7_log_work *iom7_log =
	    container_of(work, struct iom7_log_work, log_work.work);
	pkt_dmd_log_report_req_t *pkt =
	    (pkt_dmd_log_report_req_t *) iom7_log->log_p;

	hwlog_err("iom7_dmd_log_handle\n");
	if (apr_count > 0) {
#ifdef SENSOR_DSM_CONFIG
		if (!dsm_client_ocuppy(shb_dclient)) {
			hwlog_err("dsm_client_ocuppy\n");
			dsm_client_record(shb_dclient, "dmd_case = %d",
					  pkt->dmd_case);
			dsm_client_notify(shb_dclient, pkt->dmd_id);
		}
#endif
		apr_count--;
	}
    if(sensor_need_reset_power(pkt))
    {
        hwlog_err(" %s reset sensorhub\n",obj_tag_str[pkt->hd.tag]);
        iom3_need_recovery(SENSORHUB_USER_MODID, SH_FAULT_RESET);
    }

	kfree(iom7_log->log_p);
	kfree(iom7_log);
}

extern int stop_auto_accel;
extern int stop_auto_als;
extern int stop_auto_ps;
int get_airpress_data;
int get_temperature_data;
int fobidden_comm; /*once this flag set to 1, ap/iom3 will not transfer commd */
static int ps_value; /*save ps value for phonecall dmd*/

int report_sensor_event_batch(int tag, int value[], int length,
			      uint64_t timestamp)
{
	struct sensor_data event;
	int64_t ltimestamp = 0;
	struct sensor_data_xyz *sensor_batch_data = value;
	if ((!(TAG_FLUSH_META <= tag && tag < TAG_SENSOR_END))
	    || (length > sizeof(event.value))) {
		hwlog_err("para error (tag : %d), (length : %d) in %s\n", tag,
			  length, __func__);
		return -EINVAL;
	}
	if (TAG_FLUSH_META != tag) {
		ltimestamp = timestamp;
		event.type = tag_to_hal_sensor_type[tag];
		event.length = length;
		memcpy(&event.value, (char *)&(sensor_batch_data->x),
		       event.length);
		sensor_get_data(&event);
	} else {
		ltimestamp = 0;
		event.type = tag_to_hal_sensor_type[tag];
		event.length = 4;
		event.value[0] =
		    tag_to_hal_sensor_type[((pkt_header_t *) value)->tag];
	}
	return inputhub_route_write_batch(ROUTE_SHB_PORT, (char *)&event,
					  event.length +
					  OFFSET_OF_END_MEM(struct sensor_data,
							    length),
					  ltimestamp);
}

#ifdef CONFIG_HW_TOUCH_KEY
extern int touch_key_report_from_sensorhub(int key, int value);
#else
int touch_key_report_from_sensorhub(int key, int value)
{
	return 0;
}
#endif

static int64_t get_sensor_syscounter_timestamp(pkt_batch_data_req_t* sensor_event)
{
	 struct timespec64 ts;
	 int64_t timestamp, kernel_timestamp;
	 static int64_t last_timestamp_dmd_time = 0;
	 static int timestamp_failed_cnt = 0;
	 timestamp = kernel_timestamp = getTimestamp();
	 hwlog_debug("sensor %d origin tick %lld\n", sensor_event->hd.tag, sensor_event->timestamp);

	 if ((sensor_event->data_flag & DATA_FLAG_VALID_TIMESTAMP) && (0 == syscounter_to_timespec64(sensor_event->timestamp, &ts)))
	 {
		 timestamp = ts.tv_sec * 1000000000LL + ts.tv_nsec;

		 if (abs(kernel_timestamp - timestamp) > MAX_SYSCOUNT_TIME_GAP)
		 {
			 timestamp_failed_cnt++;

			 if (kernel_timestamp - last_timestamp_dmd_time > SYSCOUNT_DMD_LIMIT)
			 {
				 //hwlog_warn("syscount failed %lld %lld %d\n", timestamp, getTimestamp(), timestamp_failed_cnt);
				 //__dmd_log_report(DSM_SHB_ERR_SYSCOUNT, __func__,
				 // 				"wrong syscount cal gap\n");
				 last_timestamp_dmd_time = kernel_timestamp;
				 timestamp_failed_cnt = 0;
			 }

			 timestamp = kernel_timestamp;
		 }
	 }

	 return timestamp;
}

void inputhub_process_sensor_report(const pkt_header_t* head)
{
        uint64_t delta = 0, i = 0;
        int64_t timestamp = 0;
        int64_t head_timestamp = 0;
        int16_t flush_flag = 0;
        pkt_batch_data_req_t* sensor_event = (pkt_batch_data_req_t*) head;

        if (TAG_STEP_COUNTER == head->tag)  	/*extend step counter date*/
        {
            wake_lock_timeout(&wlock, HZ);
            hwlog_info("Kernel get pedometer event!\n");
            step_counter_data_process((pkt_step_counter_data_req_t
                                       *) head);
            report_sensor_event(head->tag,
                                (int*)(&((pkt_step_counter_data_req_t*) head)->step_count), head->length);
            flush_flag = ((pkt_step_counter_data_req_t*) head)->data_flag & FLUSH_END;

            if (flush_flag == 1)
            { goto flush_event; }
            else
            { return; }
        }

        sensor_read_number[head->tag] += sensor_event->cnt;
		timestamp = get_sensor_syscounter_timestamp(sensor_event);

        if(timestamp <= sensors_tm[head->tag])
        {
            timestamp = sensors_tm[head->tag] + 1;
        }

        //hwlog_info("[%lld] Kernel get event %d cnt %d!\n",timestamp, head->tag, sensor_event->cnt);
        if (sensor_event->cnt < 0)
        {
            hwlog_err("Kernel get event %d cnt %d error!\n",
                      head->tag, sensor_event->cnt);
        }
        else if (sensor_event->cnt < 1)
        {
            goto flush_event;
        }
        else if (sensor_event->cnt > 1)
        {
            delta = sensor_event->sample_rate * 1000000;
            head_timestamp =
                timestamp - (sensor_event->cnt - 1) * (int64_t)delta;
            //hwlog_info("head_timestamp is %llu delta is %lu\n",
            //           head_timestamp, delta);

            if (head_timestamp <= sensors_tm[head->tag])
            {
                delta = (timestamp - sensors_tm[head->tag]) / sensor_event->cnt;
                timestamp = sensors_tm[head->tag] + delta;
            }
            else
            {
                timestamp = head_timestamp;
            }
			//hwlog_info("timestamp aft is %llu delta is %lu\n",
			//					   timestamp, delta);

            /*hwlog_warn("timestamp is %lld tm is %lld delta is %lld\n",timestamp,sensors_tm[head->tag],delta);*/
            for (i = 0; i < sensor_event->cnt; i++)
            {
                report_sensor_event_batch(head->tag,
                                          (int*)((char*)head + OFFSET(pkt_batch_data_req_t, xyz)
                                                 +  i *  sensor_event->len_element),
                                          sensor_event->len_element, timestamp);
            //    hwlog_info("batch get timestamp =%lld , tag=%d\n", timestamp, head->tag);
                timestamp += delta;
            }

            timestamp -= delta;
            goto flush_event;
        }

        if (head->tag == TAG_TILT_DETECTOR )//&& sensor_event->xyz[0].x != 0)  	/*recieve proximity far*/
        {
            wake_lock_timeout(&wlock, HZ);
            hwlog_info("Kernel get TILT_DETECTOR event!=%d\n",
                       sensor_event->xyz[0].x);
        }
        if (head->tag == TAG_PS && sensor_event->xyz[0].x != 0)  	/*recieve proximity far*/
        {
            wake_lock_timeout(&wlock, HZ);
            hwlog_info("Kernel get far event!pdata=%d\n",
                       sensor_event->xyz[0].y);
            ps_value = sensor_event->xyz[0].x;
        }
        else if (head->tag == TAG_PS)
        {
            ps_value = sensor_event->xyz[0].x;
            hwlog_info("Kernel get near event!!!!pdata=%d\n",
                       sensor_event->xyz[0].y);
        }
        if (head->tag == TAG_CAP_PROX)
        {
            hwlog_info("TAG_CAP_PROX!!!!data[0]=%d,data[1]=%d,data[2]=%d.\n",sensor_event->xyz[0].x,sensor_event->xyz[0].y,sensor_event->xyz[0].z);
        }
        if (unlikely((stop_auto_accel) && (head->tag == TAG_ACCEL)))
        {
            hwlog_info("%s not report accel_data for dt\n",
                       __func__);
            return 0;
        }

        if (unlikely((stop_auto_als) && (head->tag == TAG_ALS)))
        {
            hwlog_info("%s not report als_data for dt\n", __func__);
            return 0;
        }

        if (unlikely((stop_auto_ps) && (head->tag == TAG_PS)))
        {
            hwlog_info("%s not report ps_data for dt\n", __func__);
            return 0;
        }

        if (head->tag == TAG_PRESSURE)
        {
            get_airpress_data = sensor_event->xyz[0].x;
            get_temperature_data = sensor_event->xyz[0].y;
        }

        if (head->tag == TAG_CA)
        {
            hwlog_info("ca tag=%d:data length:%d, [data0:%d][data1:%d][data2:%d]",
                       head->tag, head->length, sensor_event->xyz[0].x, sensor_event->xyz[0].y, sensor_event->xyz[0].y);
        }

        if (head->tag == TAG_PHONECALL)  	/*recieve phonecall event*/
        {
            wake_lock_timeout(&wlock, HZ);
            hwlog_info("Kernel get phonecall event! %d %d %d\n",
                       sensor_event->xyz[0].x,
                       sensor_event->xyz[0].y,
                       sensor_event->xyz[0].z);

            if (sensor_event->xyz[0].y == 1 && ps_value != 0)
            {
                hwlog_info("ps don't get the point!\n");
                __dmd_log_report(DSM_SHB_ERR_MCU_PS, __func__,
                                 "gesture worked\n");
            }
        }

        report_sensor_event_batch(head->tag, (int*)(sensor_event->xyz),
                                  sensor_event->len_element, timestamp);
    flush_event:
        sensors_tm[head->tag] = timestamp;

        if ((sensor_event->data_flag & FLUSH_END) || flush_flag == 1)
        {
            return report_sensor_event_batch(TAG_FLUSH_META,
                                             (int*)head,
                                             sizeof(pkt_header_t),
                                             0);
        }
}


int inputhub_route_recv_mcu_data(const char *buf, unsigned int length)
{
    const pkt_header_t* head = (const pkt_header_t*)buf;
    bool is_notifier = false;
    int info_len = 0;
    int64_t timestamp = 0;
    struct sensor_data event;
    pkt_additional_info_req_t* addi_info = NULL;

	const fingerprint_upload_pkt_t* fingerprint_data_upload = (const fingerprint_upload_pkt_t*)buf;
    head = pack(buf, length);

    if (NULL == head)
    { return 0; }	/*receive next partial package.*/

    if (head->tag < TAG_BEGIN || head->tag >= TAG_END)
    {
        hwlog_err
        ("---------------------->head value : tag=%#.2x, cmd=%#.2x, length=%#.2x in %s\n",
         head->tag, head->cmd, head->length, __func__);
        return -EINVAL;
    }

    ++ipc_debug_info.event_cnt[head->tag];

    wake_up_mcu_event_waiter(head);

    if (is_mcu_resume_mini(head))
    {
        hwlog_err("%s MINI ready\n", __func__);
        resume_skip_flag = RESUME_MINI;
        barrier();
        complete(&iom3_resume_mini);
    }

    if (is_mcu_resume_all(head))
    {
        hwlog_err("%s ALL ready\n", __func__);
        complete(&iom3_resume_all);
    }

    if (is_mcu_wakeup(head))
    {
        if (RESUME_MINI != resume_skip_flag)
        {
            resume_skip_flag = RESUME_SKIP;
            barrier();
            complete(&iom3_resume_mini);
            complete(&iom3_resume_all);
        }

        mcu_reboot_callback(head);
    }

    if (is_mcu_notifier(head))
    {
        mcu_notifier_queue_work(head, mcu_notifier_handler);
        is_notifier = true;
    }
    
#ifdef CONFIG_HUAWEI_CHARGER_SENSORHUB
	if (is_charging_events_data_report(head)) {
		pkt_charging_data_req_t *charging_events = (pkt_charging_data_req_t *) head;

		hwlog_info("charging events %d report\n", charging_events->data);
		struct iom7_charging_work *work = kmalloc(sizeof(struct iom7_charging_work), GFP_ATOMIC);
		if (!work)
			return -ENOMEM;
		work->event = charging_events->data;
		INIT_WORK(&(work->charging_work), iom7_charging_event_handle);
		schedule_work(&(work->charging_work));
	}
#endif

    if (is_fingerprint_data_report(head))
    {
        wake_lock_timeout(&wlock, 2 * HZ);
        char* fingerprint_data = (char*)head + sizeof(pkt_header_t);
        hwlog_debug("fingerprint: %s: tag = %d, data:%d\n", __func__, head->tag, fingerprint_data_upload->data);
        return inputhub_route_write(ROUTE_FHB_PORT, fingerprint_data,
                                        head->length);
    }
    if (is_fingersense_zaxis_data_report(head))
    {
        pkt_fingersense_data_report_req_t* zaxis_report =
            (pkt_fingersense_data_report_req_t*) head;
        update_fingersense_zaxis_data(zaxis_report->zaxis_data,
                                      zaxis_report->hd.length /
                                      sizeof(s16));
    }
    else if (is_sensor_data_report(head))
    {
#ifdef CONFIG_CONTEXTHUB_SHMEM
        mcu_notifier_queue_work(head, inputhub_process_sensor_report_notifier_handler);
#else
        inputhub_process_sensor_report(head);
#endif
    }
    else if (is_additional_info_report(head))
    {
        addi_info = (pkt_additional_info_req_t*)head;

        if (!(TAG_FLUSH_META <= head->tag && head->tag < TAG_SENSOR_END))
        {
            hwlog_err("para error (tag : %d) in %s\n", head->tag, __func__);
            return -EINVAL;
        }

        timestamp = getTimestamp();

        if (addi_info->serial == 1) //create a begin event
        {
            event.type = SENSORHUB_TYPE_ADDITIONAL_INFO;
            event.serial = 0;
            event.sensor_type = tag_to_hal_sensor_type[head->tag];
            event.data_type = AINFO_BEGIN;
            event.length = 12;
            inputhub_route_write_batch(ROUTE_SHB_PORT, (char*)&event, event.length +
                                       OFFSET_OF_END_MEM(struct sensor_data, length), timestamp);
            hwlog_info("###report sensor type %d first addition info event!\n", event.sensor_type);
        }

        //
        info_len = head->length - 8;
        event.type = SENSORHUB_TYPE_ADDITIONAL_INFO;
        event.serial = addi_info->serial;
        event.sensor_type = tag_to_hal_sensor_type[head->tag];
        event.data_type = addi_info->type;
        event.length = info_len + 12;
        memcpy(event.info, addi_info->data_int32, info_len);
        inputhub_route_write_batch(ROUTE_SHB_PORT, (char*)&event, event.length +
                                   OFFSET_OF_END_MEM(struct sensor_data, length), timestamp);
        hwlog_info("report sensor type %d addition info: %d !\n", event.sensor_type, event.info[0]);

        if (addi_info->end == 1)
        {
            event.type = SENSORHUB_TYPE_ADDITIONAL_INFO;
            event.serial = ++addi_info->serial;
            event.sensor_type = tag_to_hal_sensor_type[head->tag];
            event.data_type = AINFO_END;
            event.length = 12;
            inputhub_route_write_batch(ROUTE_SHB_PORT, (char*)&event, event.length +
                                       OFFSET_OF_END_MEM(struct sensor_data, length), timestamp);
            hwlog_info("***report sensor_type %d end addition info event!***\n", event.sensor_type);
        }
    }
    else if (is_dmd_log_data_report(head))
    {
        hwlog_err("[iom7]dmd_log_data_report");
        struct iom7_log_work* work =
            kmalloc(sizeof(struct iom7_log_work), GFP_ATOMIC);

        if (!work)
        { return -ENOMEM; }

        memset(work, 0, sizeof(struct iom7_log_work));
        work->log_p =
            kmalloc(head->length + sizeof(pkt_header_t), GFP_ATOMIC);

        if (!work->log_p)
        {
            kfree(work);
            return -ENOMEM;
        }

        memset(work->log_p, 0, head->length + sizeof(pkt_header_t));
        memcpy(work->log_p, head, head->length + sizeof(pkt_header_t));
        INIT_DELAYED_WORK(&(work->log_work), iom7_dmd_log_handle);
        queue_delayed_work(system_power_efficient_wq, &(work->log_work), msecs_to_jiffies(250));
    }
    else if (is_requirement_resp(head))
    {
        return report_resp_data((const pkt_header_resp_t*)head);
    }
    else if (is_motion_data_report(head))
    {
        char* motion_data = (char*)head + sizeof(pkt_header_t);

        if (((int)motion_data[0]) == MOTIONHUB_TYPE_TAKE_OFF)
        {
            wake_lock_timeout(&wlock, HZ);
            hwlog_err("%s weaklock HZ motiontype = %d \n", __func__,
                      motion_data[0]);
        }

        return inputhub_route_write(ROUTE_MOTION_PORT, motion_data,
                                    head->length);
    }
    else if (is_ca_data_report(head))
    {
        char* ca_data = (char*)head + sizeof(pkt_header_t);
        return inputhub_route_write(ROUTE_CA_PORT, ca_data,
                                    head->length);
    } else if (head->tag == TAG_KEY) {
		uint16_t key_datas[12] = { 0 };
		pkt_batch_data_req_t *key_data = (pkt_batch_data_req_t *)head;

		memcpy(key_datas, key_data->xyz, sizeof(key_datas));
		hwlog_info("status:%2x\n", key_datas[0]);
		touch_key_report_from_sensorhub((int)key_datas[0], 0);
	} else {
		if (!is_notifier) {
			hwlog_err
			    ("--------->tag = %d, cmd = %d is not implement!\n",
			     head->tag, head->cmd);
			fobidden_comm = 1;
			return -EINVAL;
		}
	}

    return 0;
}

extern int flag_for_sensor_test;
/* handle user command as quickly as possible.*/
int inputhub_route_cmd(unsigned short port, unsigned int cmd, unsigned long arg)
{
    hwlog_info("inputhub_route_cmd port : %d in %s\n", port, __func__);
	switch (port) {
	case ROUTE_SHB_PORT:
		{
			if (flag_for_sensor_test) {
				return 0;
			}
			return send_sensor_cmd(cmd, arg);
		}
		break;
	case ROUTE_MOTION_PORT:
		{
			if (flag_for_sensor_test) {
				return 0;
			}
			return send_motion_cmd(cmd, arg);
		}
		break;
	case ROUTE_CA_PORT:
		{
			if(flag_for_sensor_test) {
				return 0;
			}
			return send_ca_cmd(cmd, arg);
		}
		break;

        case ROUTE_FHB_PORT:
        {
            if (flag_for_sensor_test)
            {
                return 0;
            }
            return send_fingerprint_cmd(cmd, arg);
        }
        break;
	default:
		hwlog_err("unimplement port : %d in %s\n", port, __func__);
		__dmd_log_report(DSM_SHB_ERR_IOM7_CMD, __func__,
			       "unimplement port\n");
		return -EINVAL;
		break;
	}
	return 0;
}

EXPORT_SYMBOL_GPL(inputhub_route_cmd);

static char *sys_status_t_str[] = {
	[ST_SCREENON] = "ST_SCREENON",
	[ST_SCREENOFF] = "ST_SCREENOFF",
	[ST_SLEEP] = "ST_SLEEP",
	[ST_WAKEUP] = "ST_WAKEUP",
};

int tell_ap_status_to_mcu(int ap_st)
{
	read_info_t pkg_mcu;
	if ((ST_BEGIN <= ap_st) && (ap_st < ST_END)) {
		pkt_sys_statuschange_req_t pkt;
		pkt.hd.tag = TAG_SYS;
		pkt.hd.cmd = CMD_SYS_STATUSCHANGE_REQ;
		pkt.hd.resp = (ap_st == ST_SLEEP) ? RESP : NO_RESP;
		pkt.hd.length = sizeof(pkt) - sizeof(pkt.hd);
		pkt.status = ap_st;

		if (likely((ap_st >= ST_SCREENON) && (ap_st <= ST_WAKEUP))) {
			hwlog_info("------------>tell mcu ap in status %s\n",
				   sys_status_t_str[ap_st]);
			iom3_sr_status = ap_st;
		} else {
			hwlog_info("------------>tell mcu ap in status %d\n",
				   ap_st);
		}
		return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt),
						      (ap_st ==
						       ST_SLEEP) ? (&pkg_mcu) :
						      NULL);
	} else {
		hwlog_err("error status %d in %s\n", ap_st, __func__);
		return -EINVAL;
	}
}

extern void key_fb_notifier_action(int enable);
static int sensorhub_fb_notifier(struct notifier_block *nb,
				 unsigned long action, void *data)
{
	switch (action) {
	case FB_EVENT_BLANK:	/*change finished*/
		{
			struct fb_event *event = data;
			int *blank = event->data;
			switch (*blank) {
			case FB_BLANK_UNBLANK:	/*screen on */
				tell_ap_status_to_mcu(ST_SCREENON);
				key_fb_notifier_action(1);
				break;

			case FB_BLANK_POWERDOWN:	/* screen off */
				tell_ap_status_to_mcu(ST_SCREENOFF);
				sensor_redetect_enter();
				key_fb_notifier_action(0);
				break;

			default:
				hwlog_err("unknown---> lcd unknown in %s\n",
					  __func__);
				break;
			}
			break;
		}
	default:
		break;
	}

	return NOTIFY_OK;
}

int sensorhub_pm_suspend(struct device *dev)
{
	int ret = 0;

	hwlog_info("%s+\n", __func__);
	if (iom3_sr_status != ST_SLEEP) {
		ret = tell_ap_status_to_mcu(ST_SLEEP);
		iom3_power_state = ST_SLEEP;
		check_current_app();
		clean_ipc_debug_info();
	}
	hwlog_info("%s-\n", __func__);

	return ret;
}

int sensorhub_pm_resume(struct device *dev)
{
	int ret = 0;
	hwlog_info("%s+\n", __func__);
	print_ipc_debug_info();
	resume_skip_flag = RESUME_INIT;

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
	INIT_COMPLETION(iom3_reboot);
	INIT_COMPLETION(iom3_resume_mini);
	INIT_COMPLETION(iom3_resume_all);
#else
	reinit_completion(&iom3_reboot);
	reinit_completion(&iom3_resume_mini);
	reinit_completion(&iom3_resume_all);
#endif
	barrier();
	tell_ap_status_to_mcu(ST_WAKEUP);
	/*wait mini ready*/
	if (!wait_for_completion_timeout
	    (&iom3_resume_mini, msecs_to_jiffies(1000))) {
		hwlog_err("RESUME :wait for MINI timeout\n");
		goto resume_err;
	} else if (RESUME_SKIP != resume_skip_flag) {
		ret = send_fileid_to_mcu();
		if (ret) {
			hwlog_err
			    ("RESUME get sensors cfg data from dts fail,ret=%d, use default config data!\n",
			     ret);
			goto resume_err;
		} else
			hwlog_info
			    ("RESUME get sensors cfg data from dts success!\n");
	} else {
		hwlog_err("RESUME skip MINI\n");
	}

	/*wait all ready*/
	if (!wait_for_completion_timeout
	    (&iom3_resume_all, msecs_to_jiffies(1000))) {
		hwlog_err("RESUME :wait for ALL timeout\n");
		goto resume_err;
	} else if (RESUME_SKIP != resume_skip_flag) {
		hwlog_info("RESUME mcu all ready!\n");
		ret = sensor_set_cfg_data();
		if (ret < 0) {
			hwlog_err("RESUME sensor_chip_detect ret=%d\n", ret);
			goto resume_err;
		}
		reset_calibrate_when_recovery_iom3();
	} else {
		hwlog_err("RESUME skip ALL\n");
	}

	if (!wait_for_completion_timeout(&iom3_reboot, msecs_to_jiffies(1000))) {
		hwlog_err("resume :wait for response timeout\n");
		goto resume_err;
	}

	if (pConfigOnDDr->WrongWakeupMsg.flag) {
		pConfigOnDDr->WrongWakeupMsg.flag = 0;
		hwlog_err("************ sensorhub has wrong wakeup mesg\n");
		hwlog_err("time %lu\n", pConfigOnDDr->WrongWakeupMsg.time);
		hwlog_err("irqs [%x] [%x]\n", pConfigOnDDr->WrongWakeupMsg.irq0,
			  pConfigOnDDr->WrongWakeupMsg.irq1);
		hwlog_err("recvfromapmsg [%x] [%x] [%x] [%x]\n",
			  pConfigOnDDr->WrongWakeupMsg.recvfromapmsg[0],
			  pConfigOnDDr->WrongWakeupMsg.recvfromapmsg[1],
			  pConfigOnDDr->WrongWakeupMsg.recvfromapmsg[2],
			  pConfigOnDDr->WrongWakeupMsg.recvfromapmsg[3]);
		hwlog_err("recvfromlpmsg [%x] [%x] [%x] [%x]\n",
			  pConfigOnDDr->WrongWakeupMsg.recvfromlpmsg[0],
			  pConfigOnDDr->WrongWakeupMsg.recvfromlpmsg[1],
			  pConfigOnDDr->WrongWakeupMsg.recvfromlpmsg[2],
			  pConfigOnDDr->WrongWakeupMsg.recvfromlpmsg[3]);
		hwlog_err("sendtoapmsg [%x] [%x] [%x] [%x]\n",
			  pConfigOnDDr->WrongWakeupMsg.sendtoapmsg[0],
			  pConfigOnDDr->WrongWakeupMsg.sendtoapmsg[1],
			  pConfigOnDDr->WrongWakeupMsg.sendtoapmsg[2],
			  pConfigOnDDr->WrongWakeupMsg.sendtoapmsg[3]);
		hwlog_err("sendtolpmsg [%x] [%x] [%x] [%x]\n",
			  pConfigOnDDr->WrongWakeupMsg.sendtolpmsg[0],
			  pConfigOnDDr->WrongWakeupMsg.sendtolpmsg[1],
			  pConfigOnDDr->WrongWakeupMsg.sendtolpmsg[2],
			  pConfigOnDDr->WrongWakeupMsg.sendtolpmsg[3]);
		hwlog_err("ap lpm3 tap tlpm3 %x %x %x %x\n",
			  pConfigOnDDr->WrongWakeupMsg.recvfromapmsgmode,
			  pConfigOnDDr->WrongWakeupMsg.recvfromlpmsgmode,
			  pConfigOnDDr->WrongWakeupMsg.sendtoapmsgmode,
			  pConfigOnDDr->WrongWakeupMsg.sendtolpmsgmode);
		hwlog_err("************ sensorhub has wrong wakeup mesg end\n");
		memset(&(pConfigOnDDr->WrongWakeupMsg), 0,
		       sizeof(wrong_wakeup_msg_t));
	}
	goto done;
resume_err:
	iom3_need_recovery(SENSORHUB_MODID, SH_FAULT_RESUME);
done:
	iom3_power_state = ST_WAKEUP;
	hwlog_info("%s-\n", __func__);
	return 0;
}

static int sensorhub_pm_notify(struct notifier_block *nb,
			       unsigned long mode, void *_unused)
{
	switch (mode) {
	case PM_SUSPEND_PREPARE:	/*suspend */
		hwlog_info("suspend in %s\n", __func__);
		disable_sensors_when_suspend();
		break;

	case PM_POST_SUSPEND:	/* resume */
		hwlog_info("resume in %s\n", __func__);
		enable_sensors_when_resume();
		break;

	case PM_HIBERNATION_PREPARE:	/* Going to hibernate */
	case PM_POST_HIBERNATION:	/* Hibernation finished */
	case PM_RESTORE_PREPARE:	/* Going to restore a saved image */
	case PM_POST_RESTORE:	/* Restore failed */
	default:
		break;
	}

	return 0;
}

static struct notifier_block fb_notify = {
	.notifier_call = sensorhub_fb_notifier,
};

static int send_current_to_mcu(int current_now)
{
	pkt_current_data_req_t pkt;
	pkt.hd.tag = TAG_CURRENT;
	pkt.hd.cmd = CMD_CURRENT_DATA_REQ;
	pkt.hd.resp = 0;
	pkt.hd.length = sizeof(pkt.current_now);
	pkt.current_now = current_now;
	hwlog_debug("send current val = %d in %s\n", current_now, __func__);
	return inputhub_mcu_write_cmd_adapter(&pkt, sizeof(pkt), NULL);
}

static int mcu_get_current(const pkt_header_t *head)
{
	hwlog_info("iom3 request current in %s\n", __func__);
	return open_send_current(send_current_to_mcu);
}

static int mcu_unget_current(const pkt_header_t *head)
{
	hwlog_info("iom3 unrequest current in %s\n", __func__);
	return close_send_current();
}

extern void disable_sensors_when_reboot(void);
static int shb_reboot_notifier(struct notifier_block *nb, unsigned long foo,
			       void *bar)
{
	/* prevent access the emmc now: */
	hwlog_info("shb:%s: 0x%lu +\n", __func__, foo);
	if (SYS_RESTART == foo) {
		disable_sensors_when_reboot();
		disable_motions_when_sysreboot();
		disable_cas_when_sysreboot();
		disable_fingerprint_when_sysreboot();
		disable_key_when_reboot();
	}
	hwlog_info("shb:%s: -\n", __func__);
	return 0;
}

static struct notifier_block reboot_notify = {
	.notifier_call = shb_reboot_notifier,
	.priority = -1,
};

#ifdef CONFIG_IOM3_RECOVERY
static int shb_recovery_notifier(struct notifier_block *nb, unsigned long foo,
				 void *bar)
{
	/* prevent access the emmc now: */
	hwlog_info("%s (%lu) +\n", __func__, foo);
	mutex_lock(&mutex_write_cmd);
	switch (foo) {
	case IOM3_RECOVERY_START:
	case IOM3_RECOVERY_MINISYS:
		g_iom3_state = IOM3_ST_RECOVERY;
		mutex_unlock(&mutex_write_cmd);
		break;
	case IOM3_RECOVERY_DOING:
	case IOM3_RECOVERY_3RD_DOING:
		g_iom3_state = IOM3_ST_REPEAT;
		mutex_unlock(&mutex_write_cmd);
		break;
	case IOM3_RECOVERY_FAILED:
		hwlog_err("%s -recovery failed\n", __func__);
	case IOM3_RECOVERY_IDLE:
		g_iom3_state = IOM3_ST_NORMAL;
		mutex_unlock(&mutex_write_cmd);
		wake_up_all(&iom3_rec_wq);
		break;
	default:
		hwlog_err("%s -unknow state %ld\n", __func__, foo);
		break;
	}
	hwlog_info("%s -\n", __func__);
	return 0;
}

static struct notifier_block recovery_notify = {
	.notifier_call = shb_recovery_notifier,
	.priority = -1,
};

extern int iom3_rec_sys_callback(const pkt_header_t *head);
extern int register_iom3_recovery_notifier(struct notifier_block *nb);
#endif
extern int mcu_sys_ready_callback(const pkt_header_t *head);
static void set_notifier(void)
{
    /**register mcu event notifier**/
	init_mcu_notifier_list();
	init_mcu_event_wait_list();
	register_mcu_event_notifier(TAG_SYS, CMD_SYS_STATUSCHANGE_REQ,
				    mcu_sys_ready_callback);
#ifdef CONFIG_IOM3_RECOVERY
	register_mcu_event_notifier(TAG_SYS, CMD_SYS_STATUSCHANGE_REQ,
				    iom3_rec_sys_callback);
#endif
	register_mcu_event_notifier(TAG_CURRENT, CMD_CURRENT_GET_REQ,
				    mcu_get_current);
	register_mcu_event_notifier(TAG_CURRENT, CMD_CURRENT_UNGET_REQ,
				    mcu_unget_current);

    /**register to pm**/
	pm_notifier(sensorhub_pm_notify, 0);

    /**register to framebuffer**/
	fb_register_client(&fb_notify);

    /**register to reboot notifier**/
	register_reboot_notifier(&reboot_notify);
#ifdef CONFIG_IOM3_RECOVERY
	init_waitqueue_head(&iom3_rec_wq);
	register_iom3_recovery_notifier(&recovery_notify);
#endif
}


static void init_locks(void)
{
	int i;
	for (i = 0;
	     i < sizeof(package_route_tbl) / sizeof(package_route_tbl[0]);
	     ++i) {
		spin_lock_init(&package_route_tbl[i].buffer_spin_lock);
	}
	mutex_init(&mutex_write_cmd);
	mutex_init(&mutex_write_adapter);
	init_completion(&type_record.resp_complete);
	mutex_init(&type_record.lock_mutex);
	spin_lock_init(&type_record.lock_spin);
	spin_lock_init(&ref_cnt_lock);
	/* Initialize wakelock */
	wake_lock_init(&wlock, WAKE_LOCK_SUSPEND, "sensorhub");
}

int inputhub_route_init(void)
{
	init_locks();
	set_notifier();
	init_hash_tables();
#ifdef CONFIG_CONTEXTHUB_SHMEM
    if(contexthub_shmem_init())
    {
        hwlog_err("failed to init shmem\n");
    }
    else
    {
        hwlog_info("shmem ipc init done\n");
    }
 #endif
	return 0;
}

EXPORT_SYMBOL_GPL(inputhub_route_init);

void close_all_ports(void)
{
	int i;
	for (i = 0;
	     i < sizeof(package_route_tbl) / sizeof(package_route_tbl[0]);
	     ++i) {
		inputhub_route_close(package_route_tbl[i].port);
	}
}

void inputhub_route_exit(void)
{
	/*close all ports*/
	close_all_ports();
	wake_lock_destroy(&wlock);
}

EXPORT_SYMBOL_GPL(inputhub_route_exit);
