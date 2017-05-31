#ifndef __SENSOR_DEBUG_H__
#define __SENSOR_DEBUG_H__

#define REGISTER_SENSORHUB_DEBUG_OPERATION(FUNC) \
register_sensorhub_debug_operation(#FUNC, FUNC);

#define UNREGISTER_SENSORHUB_DEBUG_OPERATION(FUNC) \
unregister_sensorhub_debug_operation(FUNC);

#define MAX_STR_SIZE (1024)

typedef int (*sensor_debug_pfunc) (int tag, int argv[], int argc);

struct t_sensor_debug_operations_list {
	struct list_head head;
	struct mutex mlock;
};

/*to find operation by str*/
struct sensor_debug_cmd {
	const char *str;
	sensor_debug_pfunc operation;
	struct list_head entry;
};

/*to find tag by str*/
struct sensor_debug_tag_map {
	const char *str;
	int tag;
};

/*to search info by tag*/
struct sensor_debug_search_info {
	const char *sensor;
	int tag;
	void *private_data;
};

struct sensor_cookie {
	int tag;
	const char *name;
	const struct attribute_group *attrs_group;
	struct device *dev;
};
#define AR_MAX_CONFIG_NUM 12
#pragma pack(1)
typedef struct ar_activity_event {
	unsigned int event_type;
	unsigned int activity;
	unsigned long long timestamp;
} ar_activity_event_t;

typedef struct ar_config_event {
    unsigned int   event_type;
    unsigned int   activity;
} ar_config_event_t;

typedef struct ar_config {
	unsigned int report_interval;
	ar_config_event_t activity_list[AR_MAX_CONFIG_NUM];
} ar_config_t;

typedef struct {
	uint8_t	   core;
	uint8_t	   rsv1;
	uint8_t	   rsv2;
	uint8_t	   sub_cmd;
}core_subcmd_t;

typedef struct ar_start_cmd{
    core_subcmd_t core_cmd;
    ar_config_t   start_param;
}ar_start_cmd_t;

typedef struct ar_update_cmd{
    core_subcmd_t core_cmd;
    ar_config_t   update_param;
}ar_update_cmd_t;

typedef struct ar_stop_cmd{
    core_subcmd_t core_cmd;
    unsigned int   para;
}ar_stop_cmd_t;

typedef struct ar_flush_cmd{
    core_subcmd_t core_cmd;
}ar_flush_cmd_t;

typedef struct ar_data {
	ar_activity_event_t activity_list[48];
} ar_data_t;

typedef struct ar_data_cmd {
	pkt_header_t hd;
	ar_data_t data;
} ar_data_cmd_t;
#pragma pack()

typedef enum {
	EVENT_NONE = 0,
	EVENT_ENTER = 1,
	EVENT_EXIT = 2,
	EVENT_BOTH = 3,
} EVENT_TYPE;

typedef enum {
    AR_ACTIVITY_VEHICLE = 0x00,
    AR_ACTIVITY_RIDING = 0x01,
    AR_ACTIVITY_WALK_SLOW = 0x02,
    AR_ACTIVITY_RUN_FAST = 0x03,
    AR_ACTIVITY_STATIONARY = 0x04,
    AR_ACTIVITY_TILT = 0x05,
    AR_ACTIVITY_END = 0x10,
    AR_VE_BUS = 0x11,				/* ��� */
    AR_VE_CAR = 0x12,				/* С�� */
    AR_VE_METRO = 0x13,				/* ���� */
    AR_VE_HIGH_SPEED_RAIL = 0x14,	/* ���� */
    AR_VE_AUTO = 0x15,				/* ��·��ͨ */
    AR_VE_RAIL = 0x16,				/* ��·��ͨ */
    AR_CLIMBING_MOUNT = 0x17,          /*��ɽ*/
    AR_FAST_WALK = 0x18,                   /*����*/
    AR_UNKNOWN = 0x3F,
} AR_ACTIVITY_TYPE;

extern int register_sensorhub_debug_operation(const char *func_name,
					      sensor_debug_pfunc op);
extern int unregister_sensorhub_debug_operation(sensor_debug_pfunc op);
extern bool find_and_do_cmd(int tag, struct sensor_debug_search_info *tab,
			    int size,
			    int (*op) (struct sensor_debug_search_info *info));
extern struct device *get_sensor_device_by_name(const char *name);
extern void sensor_get_data(struct sensor_data *data);
#endif
