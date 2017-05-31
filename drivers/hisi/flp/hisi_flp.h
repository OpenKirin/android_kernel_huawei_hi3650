/*
 * hisi flp driver.
 *
 * Copyright (C) 2015 huawei Ltd.
 * Author: lijiangxiong <lijiangxiong@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/*ioctrl cmd type*/
#define FLP_TAG_FLP         0
#define FLP_TAG_GPS         1
#define FLP_TAG_AR          2

#define FLP_IOCTL_CMD_MASK              (0xFFFF00FF)

#define FLP_IOCTL_TAG_MASK              (0xFFFFFF00)
#define FLP_IOCTL_TAG_FLP               (0x464C0000)
#define FLP_IOCTL_TAG_GPS               (0x464C0100)
#define FLP_IOCTL_TAG_AR                (0x464C0200)
#define FLP_IOCTL_TAG_COMMON            (0x464CFF00)

#define FLP_IOCTL_TYPE_MASK             (0xFFFF00F0)
#define FLP_IOCTL_TYPE_PDR              (0x464C0000)
#define FLP_IOCTL_TYPE_AR               (0x464C0010)
#define FLP_IOCTL_TYPE_COMMON           (0x464C00F0)

#define FLP_IOCTL_PDR_START(x)          (0x464C0000 + ((x) * 0x100) + 1)
#define FLP_IOCTL_PDR_STOP(x)           (0x464C0000 + ((x) * 0x100) + 2)
#define FLP_IOCTL_PDR_READ(x)           (0x464C0000 + ((x) * 0x100) + 3)
#define FLP_IOCTL_PDR_WRITE(x)          (0x464C0000 + ((x) * 0x100) + 4)
#define FLP_IOCTL_PDR_CONFIG(x)         (0x464C0000 + ((x) * 0x100) + 5)
#define FLP_IOCTL_PDR_UPDATE(x)         (0x464C0000 + ((x) * 0x100) + 6)
#define FLP_IOCTL_PDR_FLUSH(x)          (0x464C0000 + ((x) * 0x100) + 7)
#define FLP_IOCTL_PDR_STEP_CFG(x)       (0x464C0000 + ((x) * 0x100) + 8)

#define FLP_IOCTL_AR_START(x)           (0x464C0000 + ((x) * 0x100) + 0x11)
#define FLP_IOCTL_AR_STOP(x)            (0x464C0000 + ((x) * 0x100) + 0x12)
#define FLP_IOCTL_AR_READ(x)            (0x464C0000 + ((x) * 0x100) + 0x13)
#define FLP_IOCTL_AR_UPDATE(x)          (0x464C0000 + ((x) * 0x100) + 0x15)
#define FLP_IOCTL_AR_FLUSH(x)           (0x464C0000 + ((x) * 0x100) + 0x16)
#define FLP_IOCTL_AR_STATE(x)           (0x464C0000 + ((x) * 0x100) + 0x17)

/*common ioctrl*/
#define FLP_IOCTL_COMMON_GET_UTC        (0x464C0000 + 0xFFF1)   /*reserve*/
#define FLP_IOCTL_COMMON_SLEEP          (0x464C0000 + 0xFFF2)
#define FLP_IOCTL_COMMON_AWAKE_RET      (0x464C0000 + 0xFFF3)
#define FLP_IOCTL_COMMON_SETPID         (0x464C0000 + 0xFFF4)
#define FLP_IOCTL_COMMON_CLOSE_SERVICE  (0x464C0000 + 0xFFF5)
#define FLP_IOCTL_COMMON_HOLD_WAKELOCK      (0x464C0000 + 0xFFF6)
#define FLP_IOCTL_COMMON_RELEASE_WAKELOCK   (0x464C0000 + 0xFFF7)

enum {
    AR_ACTIVITY_VEHICLE         = 0x00,
    AR_ACTIVITY_RIDING          = 0x01,
    AR_ACTIVITY_WALK_SLOW       = 0x02,
    AR_ACTIVITY_RUN_FAST        = 0x03,
    AR_ACTIVITY_STATIONARY      = 0x04,
    AR_ACTIVITY_TILT            = 0x05,
    AR_ACTIVITY_END             = 0x10,
    AR_VE_BUS                   = 0x11, /* 大巴 */
    AR_VE_CAR                   = 0x12, /* 小车 */
    AR_VE_METRO                 = 0x13, /* 地铁 */
    AR_VE_HIGH_SPEED_RAIL       = 0x14, /* 高铁 */
    AR_VE_AUTO                  = 0x15, /* 公路交通 */
    AR_VE_RAIL                  = 0x16, /* 铁路交通 */
    AR_CLIMBING_MOUNT           = 0x17, /* 爬山*/
    AR_FAST_WALK                = 0x18, /* 快走*/
    AR_UNKNOWN                  = 0x3F,
    AR_STATE_BUTT               = 0x40,
};

enum {
    AR_STATE_ENTER = 1,
    AR_STATE_EXIT,
};

typedef struct flp_pdr_data {
    unsigned long       msec ;
    unsigned int        step_count;
    int                 relative_position_x;
    int                 relative_position_y;
    short               velocity_x;
    short               velocity_y;
    unsigned int        migration_distance;
    unsigned int        absolute_altitude;
    unsigned short      absolute_bearing;
    unsigned short      reliability_flag;
}  __packed flp_pdr_data_t  ;

typedef struct compensate_data {
    unsigned int        compensate_step;
    int                 compensate_position_x;
    int                 compensate_position_y;
    unsigned int        compensate_distance;
} compensate_data_t ;

typedef struct  step_report {
    int data[12] ;
} step_report_t;

typedef struct buf_info {
    char            *buf;
    unsigned long   len;
} buf_info_t;

typedef struct pdr_start_config {
    unsigned int   report_interval;
    unsigned int   report_precise;
    unsigned int   report_count;
    unsigned int   report_times;   /*plan to remove */
} pdr_start_config_t;

/*AR struct*/
typedef struct ar_packet_header{
    unsigned char tag;
    unsigned char  cmd;
    unsigned char  resp : 1;
    unsigned char  rsv : 3;
    unsigned char  core : 4;
    unsigned char  partial_order;
    unsigned short tranid;
    unsigned short length;
}ar_packet_header_t;   /* compatable to pkt_header_t */

typedef struct ar_activity_event {
    unsigned int        event_type;         /*0:disable*/
    unsigned int        activity;
    unsigned long       msec ;
}  __packed ar_activity_event_t ;

typedef struct ar_activity_config {
    unsigned int        event_type;         /*0:disable*/
    unsigned int        activity;
}  __packed ar_activity_config_t ;

typedef struct ar_start_config {
    unsigned int            report_interval;
    ar_activity_config_t    activity_list[AR_STATE_BUTT];
} ar_start_config_t;

typedef struct ar_start_hal_config {
    unsigned int            report_interval;
    unsigned int            event_num;
    ar_activity_config_t    *pevent;
} ar_start_hal_config_t ;

typedef struct ar_start_mcu_config {
    unsigned int            event_num;
    unsigned int            report_interval;
    ar_activity_config_t    activity_list[AR_STATE_BUTT];
} ar_start_mcu_config_t;

/********************************************
            define flp netlink
********************************************/
#define FLP_GENL_NAME                   "TASKFLP"
#define TASKFLP_GENL_VERSION            0x01

enum {
    FLP_GENL_ATTR_UNSPEC,
    FLP_GENL_ATTR_EVENT,
    __FLP_GENL_ATTR_MAX,
};
#define FLP_GENL_ATTR_MAX (__FLP_GENL_ATTR_MAX - 1)

enum {
    FLP_GENL_CMD_UNSPEC,
    FLP_GENL_CMD_PDR_DATA,
    FLP_GENL_CMD_AR_DATA,
    FLP_GENL_CMD_PDR_UNRELIABLE,
    FLP_GENL_CMD_NOTIFY_TIMEROUT,
    FLP_GENL_CMD_AWAKE_RET,
    __FLP_GENL_CMD_MAX,
};
#define FLP_GENL_CMD_MAX (__FLP_GENL_CMD_MAX - 1)

static struct genl_family flp_genl_family = {
    .id         = GENL_ID_GENERATE,
    .name       = FLP_GENL_NAME,
    .version    = TASKFLP_GENL_VERSION,
    .maxattr    = FLP_GENL_ATTR_MAX,
};

