/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : chr_devs.h
  版 本 号   : 2.0
  作    者   : k00355907
  生成日期   : 2016年4月11日
  最近修改   :
  功能描述   :
  函数列表   :
  修改历史   :
  1.日    期   : 2016年4月11日
    作    者   : k00355907
    修改内容   : 创建文件

******************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

#ifndef __CHR_DEVS_H__
#define __CHR_DEVS_H__

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include <linux/debugfs.h>

/*****************************************************************************
  2 CHR性能配置
*****************************************************************************/

#ifndef CHR_LOG_STAT
#define CHR_LOG_STAT
#endif

/*****************************************************************************
  3 宏定义
*****************************************************************************/

#define CHR_DEV_KMSG_PLAT           "chrKmsgPlat"
#define CHR_DEV_KMSG_WIFI           "chrKmsgWifi"
#define CHR_DEV_APP_WIFI            "chrAppWifi"
#define CHR_DEV_APP_BT              "chrAppBt"
#define CHR_DEV_APP_GNSS            "chrAppGnss"
#ifdef CONFIG_CHR_OTHER_DEVS
#define CHR_DEV_APP_FM              "chrAppFm"
#define CHR_DEV_APP_NFC             "chrAppNfc"
#define CHR_DEV_APP_IR              "chrAppIr"
#endif

#define __USER_BUFF_LEN_PLAT        (1 << 14)
#define __USER_BUFF_LEN_WIFI_KMSG   (1 << 14)
#define __USER_BUFF_LEN_WIFI_APP    (1 << 15)
#define __USER_BUFF_LEN_BT          (1 << 14)
#define __USER_BUFF_LEN_GNSS        (1 << 17)
#ifdef CONFIG_CHR_OTHER_DEVS
#define __USER_BUFF_LEN_FM          (1 << 14)
#define __USER_BUFF_LEN_NFC         (1 << 14)
#define __USER_BUFF_LEN_IR          (1 << 14)
#endif
#define CHR_MIN_BUFF_LEN            (4096)
#define FLAG_OFFSET                 (24)
#define CHR_LOG_MAX_LEN             (256)
#define CHR_MSG_MAX_LEN             (260)
#define CHR_LOG_ENABLE              (1)
#define CHR_LOG_DISABLE             (0)
#define CHR_ERRNO_QUEUE_MAX_LEN     (10 )
#define CHR_CMD_SET_ERRNO           (0x0)
#define CHR_CMD_GET_ERRNO           (0x1)
#define CHR_DEV_FRAME_START         (0x7E)
#define CHR_DEV_FRAME_END           (0x7E)



#define OPS_OPEN(_name, _index, _nd, _fp)   \
    static int _name##_open(struct inode* _nd, struct file* _fp) \
{                                           \
    return chr_misc_open(_nd, _fp, _index); \
}                                           \

#define OPS_RELEASE(_name, _index, _nd, _fp)     \
    static int _name##_release(struct inode* _nd, struct file* _fp) \
{                                                \
    return chr_misc_release(_nd, _fp, _index);;  \
}

#define OPS_READ(_name, _index, _fp, _buf, _count, _pos) \
    static ssize_t _name##_read(struct file* _fp, char __user * _buf, size_t _count, loff_t* _pos) \
{                                                       \
    return chr_misc_read(_fp, _buf, _count, _index);    \
}

#define OPS_WRITE(_name, _index, _fp, _buf, _count, _pos)   \
    static ssize_t _name##_write(struct file* _fp, const char __user * _buf, size_t _count, loff_t* _pos) \
{                                                           \
    return chr_misc_write(_fp, _buf, _count, _index);       \
}

#define OPS_IOCTL(_name, _index, _fp, _cmd, _arg)   \
    static int64 _name##_ioctl(struct file* _fp, uint32 _cmd, uint64 _arg) \
{                                            \
    return chr_misc_ioctl(_fp, _cmd, _arg, _index); \
}

#define OPS_POLL(_name, _index, _fp, _pts)   \
    static unsigned int _name##_poll(struct file* _fp, struct poll_table_struct* _pts) \
{                                            \
    return chr_misc_poll(_fp, _pts, _index); \
}

#define FILE_OPS(_name) \
    static const struct file_operations _name##_fops = _FILE_OPS(_name)
#define _FILE_OPS(_name) {        \
    .owner   = THIS_MODULE,       \
    .open    = _name##_##open,    \
    .read    = _name##_##read,    \
    .write   = _name##_##write,   \
    .poll    = _name##_##poll,    \
    .unlocked_ioctl    = _name##_##ioctl,    \
    .release = _name##_##release, \
}

#define MISC_DEV(_name, _str)      \
    static struct miscdevice _name##_dev = _MISC_DEV(_name, _str)
#define _MISC_DEV(_name, _str) {   \
    .minor = MISC_DYNAMIC_MINOR,   \
    .name  = _str,                 \
    .fops  = &_name##_fops,         \
}

#ifdef CHR_DEBUG
#define CHR_DBG(s, args...)          printk(KERN_DEBUG KBUILD_MODNAME ":D]chr %s]" s,__func__, ## args)
#else
#define CHR_DBG(s, args...)
#endif
#define CHR_ERR(s, args...)          printk(KERN_ERR KBUILD_MODNAME ":E]chr %s]" s,__func__, ## args)
#define CHR_WARNING(s, args...)      printk(KERN_WARNING KBUILD_MODNAME ":W]chr %s]" s,__func__, ## args)
#define CHR_INFO(s, args...)         printk(KERN_DEBUG KBUILD_MODNAME ":I]chr %s]" s,__func__, ## args)

/*****************************************************************************
  3 数据类型定义
*****************************************************************************/
typedef unsigned char               uint8;
typedef char                        int8;
typedef unsigned short              uint16;
typedef short                       int16;
typedef unsigned int                uint32;
typedef int                         int32;
typedef unsigned long               uint64;
typedef long                        int64;

/*****************************************************************************
  4 枚举类型定义
*****************************************************************************/

typedef enum chr_dev_index{
    CHR_INDEX_KMSG_PLAT = 0,
    CHR_INDEX_KMSG_WIFI,
    CHR_INDEX_APP_WIFI,
    CHR_INDEX_APP_GNSS,
    CHR_INDEX_APP_BT,
#ifdef CONFIG_CHR_OTHER_DEVS
    CHR_INDEX_APP_FM,
    CHR_INDEX_APP_NFC,
    CHR_INDEX_APP_IR,
#endif
    CHR_INDEX_MUTT,
}CHR_DEV_INDEX;

typedef enum chr_LogPriority{
    CHR_LOG_DEBUG = 0,
    CHR_LOG_INFO,
    CHR_LOG_WARN,
    CHR_LOG_ERROR,
    CHR_LOG_MUTT,
}CHR_LOGPRIORITY;

typedef enum chr_LogTag{
    CHR_LOG_TAG_PLAT = 0,
    CHR_LOG_TAG_WIFI,
    CHR_LOG_TAG_GNSS,
    CHR_LOG_TAG_BT,
#ifdef CONFIG_CHR_OTHER_DEVS
    CHR_LOG_TAG_FM,
    CHR_LOG_TAG_NFC,
    CHR_LOG_TAG_IR,
#endif
    CHR_LOG_TAG_MUTT,
}CHR_LOG_TAG;

enum return_type
{
    CHR_SUCC = 0,
    CHR_EFAIL,
};

/*****************************************************************************
  5 结构体定义
*****************************************************************************/

#ifdef CHR_LOG_STAT
typedef struct {
    uint32             e_count;
    uint32             w_count;
    uint32             i_count;
    uint32             d_count;
    uint32             log_drop;
    uint32             buff_drop;
    uint32             buff_max_size;
}CHR_LOG_STAT_INFO;
#endif

typedef struct chr_logger_entry {
    uint16             len;
    int8               msg[0];
}CHR_LOGGER_ENTRY;

typedef struct chr_logger_log {
    int8              *buffer;
    atomic_t           r_off;
    atomic_t           w_off;
    size_t             size;
    struct semaphore   buf_sema;
}CHR_LOGGER_LOG;

typedef struct {
    CHR_LOGGER_LOG         user;
    CHR_DEV_INDEX          dev_index;
    struct miscdevice     *miscdev;
    wait_queue_head_t      read_waitqueue;
    atomic_t               ref_count;
#ifdef CHR_LOG_STAT
    CHR_LOG_STAT_INFO      log_stat;
#endif
}CHR_DEV;

typedef struct {
    wait_queue_head_t      errno_wait;
    struct sk_buff_head    errno_queue;
}CHR_EVENT;

typedef struct
{
    uint8  framehead;
    uint8  reserved[3];
    uint32 errno;
    uint8  frametail;
}CHR_DEV_EXCEPTION_STRU;

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
