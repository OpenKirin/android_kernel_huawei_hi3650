/******************************************************************************

                  版权所有 (C), 2001-2011, 华为技术有限公司

 ******************************************************************************
  文 件 名   : chr_devs.c
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

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/semaphore.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/workqueue.h>
#include <asm/atomic.h>
#include <stdarg.h>
#include <linux/slab.h>
#include <linux/unistd.h>
#include <linux/un.h>
#include <linux/socket.h>
#include <net/sock.h>

#ifdef CONFIG_HWCONNECTIVITY
#include "hisi_oneimage.h"
#endif
#include "chr_devs.h"
#include "oneimage.h"
#include "board.h"

/*****************************************************************************
  2 函数声明
*****************************************************************************/
static int32   chr_misc_open(struct inode *fd, struct file *fp, CHR_DEV_INDEX dev_index);
static ssize_t chr_misc_read(struct file *fp, int8 __user *buff, size_t count, CHR_DEV_INDEX dev_index);
static ssize_t chr_misc_write(struct file *fp,const int8 __user *buff, size_t count, CHR_DEV_INDEX dev_index);
static uint32  chr_misc_poll(struct file *fp, struct poll_table_struct * pts, CHR_DEV_INDEX dev_index);
static int64   chr_misc_ioctl(struct file* fp, uint32 cmd, uint64 arg, CHR_DEV_INDEX dev_index);
static int32   chr_misc_release(struct inode *fd, struct file* fp, CHR_DEV_INDEX dev_index);
static void    chr_log_count(CHR_DEV_INDEX dev_index, size_t index);


/*****************************************************************************
  3 全局变量定义
*****************************************************************************/
/**************** /dev/chrKmsgWifi ops and dev define  ****************/
OPS_OPEN(chrKmsgWifi,   CHR_INDEX_KMSG_WIFI, nd, fp);
OPS_RELEASE(chrKmsgWifi,CHR_INDEX_KMSG_WIFI, nd, fp);
OPS_READ(chrKmsgWifi,   CHR_INDEX_KMSG_WIFI, fp, buf, count, pos);
OPS_WRITE(chrKmsgWifi,  CHR_INDEX_KMSG_WIFI, fp, buf, count, pos);
OPS_IOCTL(chrKmsgWifi,  CHR_INDEX_KMSG_WIFI, fp, cmd, arg);
OPS_POLL(chrKmsgWifi,   CHR_INDEX_KMSG_WIFI, fp, pts);
FILE_OPS(chrKmsgWifi);
MISC_DEV(chrKmsgWifi,   CHR_DEV_KMSG_WIFI);

/**************** /dev/chrKmsgPlat ops and dev define  ****************/
OPS_OPEN(chrKmsgPlat,    CHR_INDEX_KMSG_PLAT, nd, fp);
OPS_RELEASE(chrKmsgPlat, CHR_INDEX_KMSG_PLAT, nd, fp);
OPS_READ(chrKmsgPlat,    CHR_INDEX_KMSG_PLAT, fp, buf, count, pos);
OPS_WRITE(chrKmsgPlat,   CHR_INDEX_KMSG_PLAT, fp, buf, count, pos);
OPS_IOCTL(chrKmsgPlat,  CHR_INDEX_KMSG_PLAT, fp, cmd, arg);
OPS_POLL(chrKmsgPlat,    CHR_INDEX_KMSG_PLAT, fp, pts);
FILE_OPS(chrKmsgPlat);
MISC_DEV(chrKmsgPlat,    CHR_DEV_KMSG_PLAT);

/**************** /dev/chrAppWifi ops and dev define  ****************/
OPS_OPEN(chrAppWifi,    CHR_INDEX_APP_WIFI, nd, fp);
OPS_RELEASE(chrAppWifi, CHR_INDEX_APP_WIFI, nd, fp);
OPS_READ(chrAppWifi,    CHR_INDEX_APP_WIFI, fp, buf, count, pos);
OPS_WRITE(chrAppWifi,   CHR_INDEX_APP_WIFI, fp, buf, count, pos);
OPS_IOCTL(chrAppWifi,  CHR_INDEX_APP_WIFI, fp, cmd, arg);
OPS_POLL(chrAppWifi,    CHR_INDEX_APP_WIFI, fp, pts);
FILE_OPS(chrAppWifi);
MISC_DEV(chrAppWifi,    CHR_DEV_APP_WIFI);

/**************** /dev/chrAppBt ops and dev define ****************/
OPS_OPEN(chrAppBt,      CHR_INDEX_APP_BT, nd, fp);
OPS_RELEASE(chrAppBt,   CHR_INDEX_APP_BT, nd, fp);
OPS_READ(chrAppBt,      CHR_INDEX_APP_BT, fp, buf, count, pos);
OPS_WRITE(chrAppBt,     CHR_INDEX_APP_BT, fp, buf, count, pos);
OPS_IOCTL(chrAppBt,  CHR_INDEX_APP_BT, fp, cmd, arg);
OPS_POLL(chrAppBt,      CHR_INDEX_APP_BT, fp, pts);
FILE_OPS(chrAppBt);
MISC_DEV(chrAppBt,      CHR_DEV_APP_BT);

/**************** /dev/chrAppGnss ops and dev define ****************/
OPS_OPEN(chrAppGnss,    CHR_INDEX_APP_GNSS, nd, fp);
OPS_RELEASE(chrAppGnss, CHR_INDEX_APP_GNSS, nd, fp);
OPS_READ(chrAppGnss,    CHR_INDEX_APP_GNSS, fp, buf, count, pos);
OPS_WRITE(chrAppGnss,   CHR_INDEX_APP_GNSS, fp, buf, count, pos);
OPS_IOCTL(chrAppGnss,  CHR_INDEX_APP_GNSS, fp, cmd, arg);
OPS_POLL(chrAppGnss,    CHR_INDEX_APP_GNSS, fp, pts);
FILE_OPS(chrAppGnss);
MISC_DEV(chrAppGnss,    CHR_DEV_APP_GNSS);
#ifdef CONFIG_CHR_OTHER_DEVS
/**************** /dev/chrAppFm ops and dev define ****************/
OPS_OPEN(chrAppFm,    CHR_INDEX_APP_FM, nd, fp);
OPS_RELEASE(chrAppFm, CHR_INDEX_APP_FM, nd, fp);
OPS_READ(chrAppFm,    CHR_INDEX_APP_FM, fp, buf, count, pos);
OPS_WRITE(chrAppFm,   CHR_INDEX_APP_FM, fp, buf, count, pos);
OPS_IOCTL(chrAppFm,  CHR_INDEX_APP_FM, fp, cmd, arg);
OPS_POLL(chrAppFm,    CHR_INDEX_APP_FM, fp, pts);
FILE_OPS(chrAppFm);
MISC_DEV(chrAppFm, CHR_DEV_APP_FM);
/**************** /dev/chrAppNfc ops and dev define ****************/
OPS_OPEN(chrAppNfc,    CHR_INDEX_APP_NFC, nd, fp);
OPS_RELEASE(chrAppNfc, CHR_INDEX_APP_NFC, nd, fp);
OPS_READ(chrAppNfc,    CHR_INDEX_APP_NFC, fp, buf, count, pos);
OPS_WRITE(chrAppNfc,   CHR_INDEX_APP_NFC, fp, buf, count, pos);
OPS_IOCTL(chrAppNfc,  CHR_INDEX_APP_NFC, fp, cmd, arg);
OPS_POLL(chrAppNfc,    CHR_INDEX_APP_NFC, fp, pts);
FILE_OPS(chrAppNfc);
MISC_DEV(chrAppNfc, CHR_DEV_APP_NFC);
/**************** /dev/chrAppIr ops and dev define ****************/
OPS_OPEN(chrAppIr,    CHR_INDEX_APP_IR, nd, fp);
OPS_RELEASE(chrAppIr, CHR_INDEX_APP_IR, nd, fp);
OPS_READ(chrAppIr,    CHR_INDEX_APP_IR, fp, buf, count, pos);
OPS_WRITE(chrAppIr,   CHR_INDEX_APP_IR, fp, buf, count, pos);
OPS_IOCTL(chrAppIr,  CHR_INDEX_APP_IR, fp, cmd, arg);
OPS_POLL(chrAppIr,    CHR_INDEX_APP_IR, fp, pts);
FILE_OPS(chrAppIr);
MISC_DEV(chrAppIr, CHR_DEV_APP_IR);
#endif

static CHR_EVENT g_chr_event;
static int32     g_log_enable = CHR_LOG_DISABLE;
static int8     *g_chr_logprio_str[] = {
    "D",
    "I",
    "W",
    "E",
};
static int8     *g_subsystem_str[] = {
    "kmsgplat",
    "kmsgwifi",
    "appwifi",
    "appgnss",
    "appbt",
#ifdef CONFIG_CHR_OTHER_DEVS
    "appfm",
    "appnfc",
    "appir",
#endif
};
static CHR_DEV g_log_devs[] = {
    { .dev_index = CHR_INDEX_KMSG_PLAT, .miscdev = &chrKmsgPlat_dev,},
    { .dev_index = CHR_INDEX_KMSG_WIFI, .miscdev = &chrKmsgWifi_dev,},
    { .dev_index = CHR_INDEX_APP_WIFI,  .miscdev = &chrAppWifi_dev,},
    { .dev_index = CHR_INDEX_APP_GNSS,  .miscdev = &chrAppGnss_dev,},
    { .dev_index = CHR_INDEX_APP_BT,    .miscdev = &chrAppBt_dev,},
#ifdef CONFIG_CHR_OTHER_DEVS
    { .dev_index = CHR_INDEX_APP_FM,    .miscdev = &chrAppFm_dev,},
    { .dev_index = CHR_INDEX_APP_NFC,   .miscdev = &chrAppNfc_dev,},
    { .dev_index = CHR_INDEX_APP_IR,    .miscdev = &chrAppIr_dev,},
#endif
};

static int32 g_buffer_size[] = {
    __USER_BUFF_LEN_PLAT,
    __USER_BUFF_LEN_WIFI_KMSG,
    __USER_BUFF_LEN_WIFI_APP,
    __USER_BUFF_LEN_GNSS,
    __USER_BUFF_LEN_BT,
#ifdef CONFIG_CHR_OTHER_DEVS
    __USER_BUFF_LEN_FM,
    __USER_BUFF_LEN_NFC,
    __USER_BUFF_LEN_IR,
#endif
};

/*****************************************************************************
  4 宏定义
*****************************************************************************/

#ifdef CHR_LOG_STAT

#define chr_log_error_count_inc(_dev_index) do{ \
            g_log_devs[_dev_index].log_stat.e_count++; \
        }while(0)

#define chr_log_warning_count_inc(_dev_index) do{ \
            g_log_devs[_dev_index].log_stat.w_count++; \
        }while(0)

#define chr_log_info_count_inc(_dev_index) do{ \
            g_log_devs[_dev_index].log_stat.i_count++; \
        }while(0)

#define chr_log_debug_count_inc(_dev_index) do{ \
            g_log_devs[_dev_index].log_stat.d_count++; \
        }while(0)

#define chr_buff_max_size(_dev_index) do{ \
            size_t r_index   = atomic_read(&(g_log_devs[_dev_index].user.r_off));\
            size_t w_index   = atomic_read(&(g_log_devs[_dev_index].user.w_off));\
            size_t max_size  = g_log_devs[_dev_index].user.size; \
            size_t real_size = 0; \
            if (r_index >= w_index) \
            { \
                real_size = max_size - r_index + w_index; \
            } \
            else \
            { \
                real_size = w_index - r_index; \
            } \
            if(real_size > g_log_devs[_dev_index].log_stat.buff_max_size) \
            { \
                g_log_devs[_dev_index].log_stat.buff_max_size = real_size; \
            } \
        }while(0)

#define chr_log_drop(_dev_index) do{ \
            g_log_devs[_dev_index].log_stat.log_drop++; \
        }while(0)

#define chr_buff_drop(_dev_index) do{ \
            g_log_devs[_dev_index].log_stat.buff_drop++; \
        }while(0)

#else
#define chr_log_error_count_inc(_dev_index)
#define chr_log_warning_count_inc(_dev_index)
#define chr_log_info_count_inc(_dev_index)
#define chr_log_debug_count_inc(_dev_index)
#define chr_buff_max_size(_dev_index)
#define chr_log_drop(_dev_index)
#define chr_buff_drop(_dev_index)
#endif

#define PTR_BUFINFO(dev_idx)  do{ \
            CHR_DBG("Log_Info.name = %s,r_off = %d,w_off = %d\n",\
            g_log_devs[dev_idx].miscdev->name, \
            atomic_read(&g_log_devs[dev_idx].user.r_off), \
            atomic_read(&g_log_devs[dev_idx].user.w_off)); \
        }while(0)

/*****************************************************************************
  5 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : chr_buff_index_covert
 功能描述  : 计算节点BUFF下标 new_index = index % buff_max_size
             节点BUFF物理模型为数组,逻辑模型为环形BUFF
 输入参数  : CHR_DEV_INDEX dev_index
             size_t index
 输出参数  : 无
 返 回 值  : static inline size_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static inline size_t chr_buff_index_covert(CHR_DEV_INDEX dev_index, size_t index)
{
    return (index & (g_log_devs[dev_index].user.size - 1));
}

/*****************************************************************************
 函 数 名  : chr_buff_overflow_check
 功能描述  : 节点BUFF下标安全判断
     case 1: |----date--w_index--nodate--r_index----date--|
     case 2: |--nodate--r_index----date--w_index--nodate--|
 输入参数  : size_t r_index
             size_t w_index
             size_t i_index
 输出参数  : 无
 返 回 值  : static inline int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static inline int32 chr_buff_overflow_check(size_t r_index, size_t w_index, size_t i_index)
{
    if (r_index > w_index)
    {
        if ((i_index <= w_index) || (i_index >= r_index))
        {
            return -CHR_EFAIL;
        }
    }
    else
    {
        if ((i_index <= w_index) && (i_index >= r_index))
        {
            return -CHR_EFAIL;
        }
    }

    return CHR_SUCC;
}

/*****************************************************************************
 函 数 名  : format_prefixstr
 功能描述  : 将日志打印时间和日志优先级转换成字符串
 输入参数  : int8 *prefix_str
             CHR_LOGPRIORITY prio
 输出参数  : 无
 返 回 值  : static void
 调用函数  :
 被调函数  : __chr_printLog

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static void format_prefixstr(int8 *prefix_str, CHR_LOGPRIORITY prio)
{
    struct tm      p_tm;
    struct timeval tv;

    do_gettimeofday(&tv);
    time_to_tm(tv.tv_sec, 0, &p_tm);
    snprintf(prefix_str, CHR_MSG_MAX_LEN, "%04d.%02d.%02d:%02d.%02d.%02d:%03d]%s]", (int)(p_tm.tm_year+1900),\
                p_tm.tm_mon + 1, p_tm.tm_mday, p_tm.tm_hour,\
                p_tm.tm_min, p_tm.tm_sec, (int)(tv.tv_usec/1000), g_chr_logprio_str[prio]);
}

/*****************************************************************************
 函 数 名  : chr_data_write
 功能描述  : 往节点BUFF写数据
 输入参数  : CHR_DEV_INDEX dev_index
             size_t i_index
             void *buff      由调用者保证有效性
             size_t count
 输出参数  : 无
 返 回 值  : static inline void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static inline int32 chr_data_write(CHR_DEV_INDEX dev_index, size_t index, void *buff, size_t count)
{
    size_t write_len = 0;

    write_len = min(count, g_log_devs[dev_index].user.size - index);
    if (NULL == memcpy(&(g_log_devs[dev_index].user.buffer[index]), buff, write_len))
    {
        CHR_DBG("chr %s memcpy fail, line = %d\n", g_log_devs[dev_index].miscdev->name, __LINE__);
        return -CHR_EFAIL;
    }

    if (count != write_len)
    {
        if (NULL == memcpy(g_log_devs[dev_index].user.buffer, buff + write_len, count - write_len))
        {
            CHR_DBG("chr %s memcpy fail, line = %d\n", g_log_devs[dev_index].miscdev->name, __LINE__);
            return -CHR_EFAIL;
        }
    }

    return CHR_SUCC;
}
/*****************************************************************************
 函 数 名  : chr_data_read
 功能描述  : 从节点BUFF读数据
 输入参数  : CHR_DEV_INDEX dev_index
             size_t index
             void *buff
             size_t count
 输出参数  : 无
 返 回 值  : static inline int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static inline int32 chr_data_read(CHR_DEV_INDEX dev_index, size_t index, void *buff, size_t count)
{
    int8 *src       = (int8 *)&(g_log_devs[dev_index].user.buffer[index]);
    int8 *dest      = (int8 *)buff;
    size_t max_size = g_log_devs[dev_index].user.size;
    int32 read_len  = 0;

    read_len = min(count, (max_size - index));
    if (NULL == memcpy(dest, src, read_len))
    {
        CHR_DBG("chr %s memcpy fail, line = %d\n", g_log_devs[dev_index].miscdev->name, __LINE__);
        return -CHR_EFAIL;
    }
    if (read_len != count)
    {
        if (NULL == memcpy((dest + read_len), g_log_devs[dev_index].user.buffer, count - read_len))
        {
            CHR_DBG("chr %s memcpy fail, line = %d\n", g_log_devs[dev_index].miscdev->name, __LINE__);
            return -CHR_EFAIL;
        }
    }

    return CHR_SUCC;
}

/*****************************************************************************
 函 数 名  : chr_write_index_update
 功能描述  : 更新节点BUFF写下标,并写入数据包头,在写日志数据之前被调用


 输入参数  : CHR_DEV_INDEX dev_index
             size_t *index            由调用者保证有效性
             size_t count
 输出参数  : 无
 返 回 值  : static int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int32 chr_write_index_update(CHR_DEV_INDEX dev_index, size_t *index, size_t count)
{
    size_t r_index = atomic_read(&g_log_devs[dev_index].user.r_off);
    size_t w_index = atomic_read(&g_log_devs[dev_index].user.w_off);
    size_t i_index = 0;
    int32  ret     = 0;
    struct chr_logger_entry header = {0};

    /***** step 1): 获取写数据结束时BUFF下标 **************/
    i_index = chr_buff_index_covert(dev_index, w_index + sizeof(header) + count);

    /***** step 2): 判断写结束BUFF下标是否落在数据区 ******/
    if (CHR_SUCC != chr_buff_overflow_check(r_index, w_index, i_index))
    {
        CHR_DBG("chr %s is full! r_index = %d, w_index = %d, i_index =%d\n", g_log_devs[dev_index].miscdev->name,(int32)r_index, (int32)w_index, (int32)i_index);
        chr_log_drop(dev_index);
        wake_up_interruptible(&g_log_devs[dev_index].read_waitqueue);
        return -CHR_EFAIL;
    }

    /***** step 3): 设置写结束BUFF下标 *******************/
    atomic_set(&(g_log_devs[dev_index].user.w_off), i_index);

    /***** step 4): 写数据包头,更新写数据指针并输出 ******/
    header.len = count;
    ret = chr_data_write(dev_index, w_index, &header, sizeof(header));
    if (CHR_SUCC != ret)
    {
        CHR_DBG("chr %s write header fail\n", g_log_devs[dev_index].miscdev->name);
        return -CHR_EFAIL;
    }
    *index = chr_buff_index_covert(dev_index, w_index + sizeof(header));

    return CHR_SUCC;
}


/*****************************************************************************
 函 数 名  : chr_read_index_get
 功能描述  : 获取节点BUFF读下标,判断数据有效性
 输入参数  : CHR_DEV_INDEX dev_index
             size_t *index 有效性由调用者保证
             size_t *count 有效性由调用者保证
 输出参数  : 无
 返 回 值  : static int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int32 chr_read_index_get(CHR_DEV_INDEX dev_index, size_t *index, size_t *count)
{
    struct chr_logger_entry header = {0};
    int32 ret       = 0;
    size_t r_index  = atomic_read(&(g_log_devs[dev_index].user.r_off));
    size_t w_index  = atomic_read(&(g_log_devs[dev_index].user.w_off));

    /***** step 1): 判断BUFF是否为空 **********************/
    if (r_index == w_index)
    {
        CHR_DBG("chr %s is empty, r_index = %d, w_index = %d\n", g_log_devs[dev_index].miscdev->name, (int32)r_index, (int32)w_index);
        return -CHR_EFAIL;
    }

    /***** step 2): 获取数据包头根据长度判断数据有效性 ***/
    ret = chr_data_read(dev_index, r_index, &header, sizeof(header));
    if (CHR_SUCC != ret)
    {
        CHR_DBG("chr %s get header fail\n", g_log_devs[dev_index].miscdev->name);
        return -CHR_EFAIL;
    }
    if (header.len > CHR_LOG_MAX_LEN)
    {
        atomic_set(&(g_log_devs[dev_index].user.r_off), 0);
        atomic_set(&(g_log_devs[dev_index].user.w_off), 0);
        CHR_WARNING("chr %s data is destoried, clean all buffer\n", g_log_devs[dev_index].miscdev->name);
#ifdef  CHR_LOG_STAT
        chr_buff_drop(dev_index);
#endif
        return -CHR_EFAIL;
    }

    /***** step 3): 将数据读下标和数据长度输出 ***********/
    *index = chr_buff_index_covert(dev_index, r_index + sizeof(header));
    *count = header.len;

    return CHR_SUCC;
}

/*****************************************************************************
 函 数 名  : chr_read_index_set
 功能描述  : 设置节点BUFF读下标
 输入参数  : CHR_DEV_INDEX dev_index
             size_t count
 输出参数  : 无
 返 回 值  : static inline void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static inline void chr_read_index_set(CHR_DEV_INDEX dev_index, size_t index, size_t count)
{
    size_t i_index = chr_buff_index_covert(dev_index, index + count);
    atomic_set(&(g_log_devs[dev_index].user.r_off), i_index);
}

/*****************************************************************************
 函 数 名  : chr_copy_from_user
 功能描述  : 从用户空间拷贝数据到节点BUFF
 输入参数  : CHR_DEV_INDEX dev_index
             size_t index
             const int8 __user * buff 有效性由调用者保证
             size_t count
 输出参数  : 无
 返 回 值  : static int
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int chr_copy_from_user(CHR_DEV_INDEX dev_index, size_t index, const int8 __user * buff, size_t count)
{
    size_t  write_len    = 0;
    size_t  max_size     = g_log_devs[dev_index].user.size;

    write_len = min(count, (max_size - index));
    if (copy_from_user(&(g_log_devs[dev_index].user.buffer[index]), buff, write_len))
    {
        CHR_DBG("chr %s copy from user fail, line = %d\n", g_log_devs[dev_index].miscdev->name, __LINE__);
        return -CHR_EFAIL;
    }

    if (count != write_len)
    {
        if(copy_from_user(g_log_devs[dev_index].user.buffer, buff + write_len, count - write_len))
        {
            CHR_DBG("chr %s copy from user fail, line = %d\n", g_log_devs[dev_index].miscdev->name, __LINE__);
            return -CHR_EFAIL;
        }
    }

    return CHR_SUCC;
}
/*****************************************************************************
 函 数 名  : chr_copy_from_kernel
 功能描述  : 从内核空间拷贝数据到节点BUFF
 输入参数  : CHR_DEV_INDEX dev_index
             size_t index
             int8  *buff
             size_t count
 输出参数  : 无
 返 回 值  : static inline int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static inline int32 chr_copy_from_kernel(CHR_DEV_INDEX dev_index, size_t index, int8  *buff, size_t count)
{
    return chr_data_write(dev_index, index, buff, count);
}

/*****************************************************************************
 函 数 名  : chr_copy_to_user
 功能描述  : 从节点BUFF拷贝数据到用户空间
 输入参数  : CHR_DEV_INDEX dev_index
             size_t index
             int8 __user * buff 由调用者保证数据有效性
             size_t count
 输出参数  : 无
 返 回 值  : static int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int32 chr_copy_to_user(CHR_DEV_INDEX dev_index, size_t index, int8 __user * buff, size_t count)
{
    size_t read_len = 0;
    size_t max_size = g_log_devs[dev_index].user.size;

    read_len = min(count, (max_size - index));
    if (copy_to_user(buff, &(g_log_devs[dev_index].user.buffer[index]), read_len))
    {
        CHR_DBG("chr %s copy to user fail, line = %d\n", g_log_devs[dev_index].miscdev->name, __LINE__);
        return -CHR_EFAIL;
    }

    if (count != read_len)
    {
        if (copy_to_user(buff + read_len, g_log_devs[dev_index].user.buffer, count - read_len))
        {
            CHR_DBG("chr %s copy to user fail, line = %d\n", g_log_devs[dev_index].miscdev->name, __LINE__);
            return -CHR_EFAIL;
        }
    }

    return CHR_SUCC;
}

/*****************************************************************************
 函 数 名  : chr_write_done
 功能描述  : 写数据结束,根据策略唤醒日志读取
 输入参数  : CHR_DEV_INDEX dev_index
 输出参数  : 无
 返 回 值  : static void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static void chr_write_done(CHR_DEV_INDEX dev_index)
{
    size_t log_size = 0;
    size_t r_index  = atomic_read(&(g_log_devs[dev_index].user.r_off));
    size_t w_index  = atomic_read(&(g_log_devs[dev_index].user.w_off));
    size_t max_size = g_log_devs[dev_index].user.size;

    if (w_index > r_index)
    {
        log_size = w_index - r_index;
    }
    else
    {
        log_size = max_size - r_index + w_index;
    }

    if (log_size > (max_size / 10))
    {
        wake_up_interruptible(&(g_log_devs[dev_index].read_waitqueue));
    }
}
/*****************************************************************************
 函 数 名  : chr_log_count
 功能描述  : 日志统计
 输入参数  : CHR_DEV_INDEX dev_index
             size_t index
 输出参数  : 无
 返 回 值  : static void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月12日
    作    者   : hello
    修改内容   : 新生成函数

*****************************************************************************/
static void chr_log_count(CHR_DEV_INDEX dev_index, size_t index)
{
#ifdef     CHR_LOG_STAT
    size_t new_index = chr_buff_index_covert(dev_index, index + FLAG_OFFSET);
    int8   log_prio  = g_log_devs[dev_index].user.buffer[new_index];

    switch(log_prio)
    {
        case 'I':
            chr_log_info_count_inc(dev_index);
        break;
        case 'W':
            chr_log_warning_count_inc(dev_index);
        break;
        case 'E':
            chr_log_error_count_inc(dev_index);
        break;
        case 'D':
            chr_log_debug_count_inc(dev_index);
        break;
        default:
            CHR_DBG("chr %s log prio[%c] is not available\n", g_log_devs[dev_index].miscdev->name, log_prio);
        break;
    }
#endif
}

/*****************************************************************************
 函 数 名  : chr_buff_alloc
 功能描述  : 申请节点BUFF,共享型设备
 输出参数  : 无
 返 回 值  : static int32 c
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
 static int32 chr_buff_alloc(CHR_DEV_INDEX dev_index)
 {
     uint32 buf_len = 0;

     down(&g_log_devs[dev_index].user.buf_sema);
     if(0 == atomic_read(&g_log_devs[dev_index].ref_count))
     {
        buf_len = g_log_devs[dev_index].user.size;
        do
        {
            g_log_devs[dev_index].user.buffer = kmalloc(buf_len, GFP_KERNEL | __GFP_NOWARN);
            if (NULL == g_log_devs[dev_index].user.buffer)
            {
                buf_len = buf_len >> 1;
            }
            else
            {
                break;
            }

        }while(buf_len >= CHR_MIN_BUFF_LEN);

        if(NULL == g_log_devs[dev_index].user.buffer)
        {
            CHR_ERR("chr %s kmalloc fail\n", g_log_devs[dev_index].miscdev->name);
            up(&g_log_devs[dev_index].user.buf_sema);
            return -ENOMEM;
        }

        //update buffer size
        g_log_devs[dev_index].user.size = buf_len;
        g_buffer_size[dev_index]        = buf_len;
     }

     PTR_BUFINFO(dev_index);
     atomic_inc(&g_log_devs[dev_index].ref_count);
     CHR_DBG("chr %s ref_count = %d\n", g_log_devs[dev_index].miscdev->name, atomic_read(&(g_log_devs[dev_index].ref_count)));
     up(&g_log_devs[dev_index].user.buf_sema);

     return CHR_SUCC;
 }
/*****************************************************************************
 函 数 名  : chr_buff_read
 功能描述  : 节点读数据
 输出参数  : 无
 返 回 值  : static int c
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static size_t chr_buff_read(CHR_DEV_INDEX dev_index, int8 __user * buff, size_t count)
{
    size_t write_len = 0;
    size_t read_len  = 0;
    size_t index     = 0;
    int    ret       = 0;

    while (write_len < count)
    {
        /***** step 1):获取数据包头并判断数据有效性 ********/
        ret = chr_read_index_get(dev_index, &index, &read_len);
        if (CHR_SUCC != ret)
        {
            CHR_DBG("chr %s read fail, data is not available\n", g_log_devs[dev_index].miscdev->name);
            break;
        }

        /***** step 2):每次读取整条日志,判断空间是否允许 ***/
        if ((write_len + read_len) > count)
        {
            break;
        }

        /***** step 3):拷贝数据到用户空间 ******************/
        ret = chr_copy_to_user(dev_index, index, buff + write_len, read_len);
        if (CHR_SUCC != ret)
        {
            CHR_DBG("chr %s read fail, copy to user fail\n", g_log_devs[dev_index].miscdev->name);
            break;
        }

        /***** step 4):设置BUFF读下标 *********************/
        chr_read_index_set(dev_index, index, read_len);

        write_len += read_len;
    }

    return write_len;
}

/*****************************************************************************
 函 数 名  : chr_buff_write
 功能描述  : 节点写数据
 输入参数  : CHR_DEV_INDEX dev_index
             const int8 __user * buf
             int count
 输出参数  : 无
 返 回 值  : static ssize_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static ssize_t chr_buff_write(CHR_DEV_INDEX dev_index, const int8 __user * buff, int count)
{
    int    ret   = 0;
    size_t index = 0;

    /***** step 1):安全处理 ****************/
    if (NULL == g_log_devs[dev_index].user.buffer)
    {
        CHR_DBG("chr %s user write fail, buff is NULL\n", g_log_devs[dev_index].miscdev->name);
        chr_log_drop(dev_index);
        return -CHR_EFAIL;
    }
    if (count > CHR_LOG_MAX_LEN)
    {
        count = CHR_LOG_MAX_LEN;
    }

    /***** step 2):写入数据包头 ***********/
    ret = chr_write_index_update(dev_index, &index, count);
    if (CHR_SUCC != ret)
    {
        CHR_DBG("chr %s user write fail, upadta index fail\n", g_log_devs[dev_index].miscdev->name);
        return -CHR_EFAIL;
    }

    /***** step 3):从用户空间拷贝数据 *****/
    ret = chr_copy_from_user(dev_index, index, buff, count);
    if (CHR_SUCC != ret)
    {
        CHR_DBG("chr %s user write fail, copy data from user fail\n", g_log_devs[dev_index].miscdev->name);
        return -CHR_EFAIL;
    }

    chr_log_count(dev_index, index);
    chr_buff_max_size(dev_index);

    /***** step 4):唤醒日志读取 ***********/
    chr_write_done(dev_index);

    return count;
}
/*****************************************************************************
 函 数 名  : chr_buff_free
 功能描述  : 释放节点BUFF
 输入参数  : CHR_DEV_INDEX dev_index
 输出参数  : 无
 返 回 值  : static int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int32 chr_buff_free(CHR_DEV_INDEX dev_index)
{
    down(&g_log_devs[dev_index].user.buf_sema);
    if(atomic_dec_and_test(&g_log_devs[dev_index].ref_count))
    {
        if (NULL != g_log_devs[dev_index].user.buffer)
        {
            kfree(g_log_devs[dev_index].user.buffer);
            g_log_devs[dev_index].user.buffer = NULL;
        }
    }
    PTR_BUFINFO(dev_index);
    up(&g_log_devs[dev_index].user.buf_sema);

    return CHR_SUCC;
}
/*****************************************************************************
 函 数 名  : __chr_printLog
 功能描述  : 内核空间打印日志接口
    step 1):判断日志功能是否打开
    step 2):安全检查
    step 3):
    step 4):更新节点缓存指针,并写入数据包头
         注:日志格式详解见本文件头部
    step 5):将日志内容和打印时间一并考入节点缓存
    step 6):根据发送策略,唤醒user空间日志读取

 输入参数  : CHR_LOGPRIORITY prio
             CHR_DEV_INDEX dev_index
             const int8 *fmt
             ...
 输出参数  : 无
 返 回 值  : int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月9日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
int32 __chr_printLog(CHR_LOGPRIORITY prio, CHR_DEV_INDEX dev_index, const int8 *fmt,...)
{
    va_list argptr;
    int8    tmpbuf_str[CHR_MSG_MAX_LEN] = {0x00};
    size_t  prefix_len  = 0;
    size_t  fmt_strlen  = 0;
    size_t  write_index = 0;
    int32   ret         = 0;

    /***** step 1: 安全检查 ********************/
    if (dev_index >= CHR_INDEX_MUTT)
    {
        CHR_DBG("chr kernel write fail, dev_index %d is not available\n", dev_index);
        return -CHR_EFAIL;
    }
    if (prio >= CHR_LOG_MUTT)
    {
        CHR_DBG("chr %s kernel write fail, prio %d is not available\n", g_log_devs[dev_index].miscdev->name, prio);
        return -CHR_EFAIL;
    }
    if (NULL == g_log_devs[dev_index].user.buffer)
    {
        CHR_DBG("chr %s kernel write fail, buff is NULL\n", g_log_devs[dev_index].miscdev->name);
        chr_log_drop(dev_index);
        return -CHR_EFAIL;
    }

    /***** step 2: 判断CHR模块是否开启 **********/
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_DBG("chr %s kernel write fail, module is disable\n", g_log_devs[dev_index].miscdev->name);
        return -CHR_EFAIL;
    }

    /***** step 3: 在日志前增加时间和优先级 ******/
    format_prefixstr(tmpbuf_str, prio);
    prefix_len = strlen(tmpbuf_str);
    va_start(argptr, fmt);
    fmt_strlen = vsnprintf(tmpbuf_str + prefix_len, CHR_LOG_MAX_LEN - prefix_len - 2, fmt, argptr);
    va_end(argptr);
    fmt_strlen = strlen(tmpbuf_str);
    if (fmt_strlen > CHR_LOG_MAX_LEN)
    {
        fmt_strlen = CHR_LOG_MAX_LEN;
    }

    /***** step 4: 写入数据包头,更新BUFF写下标 ***/
    ret = chr_write_index_update(dev_index, &write_index, fmt_strlen);
    if (CHR_SUCC != ret)
    {
        CHR_DBG("chr %s kernel write fail, update index fail\n", g_log_devs[dev_index].miscdev->name);
        return -CHR_EFAIL;
    }


    /***** step 5: 拷贝日志到BUFF ***************/
    ret = chr_copy_from_kernel(dev_index, write_index, tmpbuf_str, fmt_strlen);
    if (CHR_SUCC != ret)
    {
        CHR_DBG("chr %s kernel write fail\n", g_log_devs[dev_index].miscdev->name);
        return -CHR_EFAIL;
    }

    chr_log_count(dev_index, write_index);
    chr_buff_max_size(dev_index);

    /***** step 6: 唤醒user空间读取日志 ********/
    chr_write_done(dev_index);

    return CHR_SUCC;
}
EXPORT_SYMBOL(__chr_printLog);

/*****************************************************************************
 函 数 名  : __chr_exception
 功能描述  : 内核空间抛异常码接口
 输入参数  : uint32 errno
 输出参数  : 无
 返 回 值  : int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月9日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
int32  __chr_exception(uint32 errno)
{
    struct sk_buff *skb = NULL;

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_DBG("chr throw exception fail, module is disable\n");
        return -CHR_EFAIL;
    }

    if(skb_queue_len(&(g_chr_event.errno_queue)) > CHR_ERRNO_QUEUE_MAX_LEN)
    {
        CHR_WARNING("chr errno queue is full, dispose errno=%x\n", errno);
        return -CHR_EFAIL;
    }

    skb = alloc_skb(sizeof(errno), GFP_KERNEL);
    if(NULL == skb)
    {
        CHR_ERR("chr alloc errno skbuff fail, len=%d, errno=%x\n", (int32)sizeof(errno), errno);
        return -CHR_EFAIL;
    }

    skb_put(skb, sizeof(errno));
    *(uint32*)skb->data = errno;

    skb_queue_tail(&g_chr_event.errno_queue, skb);
    wake_up_interruptible(&g_chr_event.errno_wait);

    return CHR_SUCC;
}
EXPORT_SYMBOL(__chr_exception);

/*****************************************************************************
 函 数 名  : chr_misc_open
 功能描述  : 打开设备节点接口
 输入参数  : struct inode *fd
             struct file *fp
             CHR_DEV_INDEX dev_index
 输出参数  : 无
 返 回 值  : static int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月9日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int32 chr_misc_open(struct inode *fd, struct file *fp, CHR_DEV_INDEX dev_index)
{
    int32 ret = 0;

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_DBG("chr %s open fail, module is disable\n", g_log_devs[dev_index].miscdev->name);
        return CHR_SUCC;
    }

    ret = chr_buff_alloc(dev_index);
    if (CHR_SUCC != ret)
    {
        CHR_ERR("chr %s open fail, malloc buff fail\n", g_log_devs[dev_index].miscdev->name);
        return -EAGAIN;
    }

    return CHR_SUCC;
}

/*****************************************************************************
 函 数 名  : chr_misc_read
 功能描述  : 读取设备节点接口
 输入参数  : struct file *fp
             int8 __user *buf
             size_t count
             CHR_DEV_INDEX dev_index
 输出参数  : 无
 返 回 值  : static ssize_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月9日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static ssize_t chr_misc_read(struct file *fp, int8 __user *buff, size_t count, CHR_DEV_INDEX dev_index)
{
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_DBG("chr %s read fail, module is disable\n", g_log_devs[dev_index].miscdev->name);
        return CHR_SUCC;
    }

    if (NULL == buff)
    {
        CHR_DBG("chr %s read fail, user buff is NULL", g_log_devs[dev_index].miscdev->name);
        return -EAGAIN;
    }

    return chr_buff_read(dev_index, buff, count);
}
/*****************************************************************************
 函 数 名  : chr_misc_write
 功能描述  : 写入设备节点接口
 输入参数  : struct file *fp
             const int8 __user *buf
             size_t count
             CHR_DEV_INDEX dev_index
 输出参数  : 无
 返 回 值  : static ssize_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static ssize_t chr_misc_write(struct file *fp,const int8 __user *buff, size_t count, CHR_DEV_INDEX dev_index)
{
    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_DBG("chr %s write fail, module is disable\n", g_log_devs[dev_index].miscdev->name);
        return CHR_SUCC;
    }

    if (NULL == buff)
    {
        CHR_ERR("chr %s write fail, buff is NULL\n", g_log_devs[dev_index].miscdev->name);
        return -EAGAIN;
    }

    return chr_buff_write(dev_index, buff, count);
}
/*****************************************************************************
 函 数 名  : chr_misc_poll
 功能描述  : 阻塞设备节点接口
 输入参数  : struct file *fp
             struct poll_table_struct * pts
             CHR_DEV_INDEX dev_index
 输出参数  : 无
 返 回 值  : static uint32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static uint32 chr_misc_poll(struct file *fp, struct poll_table_struct * pts, CHR_DEV_INDEX dev_index)
{
    uint32 mask       = 0;
    size_t tmp_rIndex = 0;
    size_t tmp_wIndex = 0;

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_DBG("chr %s poll fail, module is disable\n", g_log_devs[dev_index].miscdev->name);
        return mask;
    }

    PTR_BUFINFO(dev_index);
    tmp_rIndex = atomic_read(&g_log_devs[dev_index].user.r_off);
    tmp_wIndex = atomic_read(&g_log_devs[dev_index].user.w_off);
    poll_wait(fp,&g_log_devs[dev_index].read_waitqueue, pts);
    if(tmp_rIndex != tmp_wIndex)
    {
        mask |= (POLLIN | POLLRDNORM);
    }

    return mask;
}
/*****************************************************************************
 函 数 名  : chr_misc_ioctl
 功能描述  : 控制设备节点接口
 输入参数  : struct file* fp
             uint32 cmd
             uint64 arg
             CHR_DEV_INDEX i
 输出参数  : 无
 返 回 值  : static int64
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int64 chr_misc_ioctl(struct file* fp, uint32 cmd, uint64 arg, CHR_DEV_INDEX dev_index)
{
    uint32 __user   *puser = (uint32 __user *)arg;
    struct sk_buff  *skb   =NULL;
    uint32 value           = 0;

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_DBG("chr %s ioctl fail, module is disable\n", g_log_devs[dev_index].miscdev->name);
        return CHR_SUCC;
    }

    switch (cmd)
    {
        case CHR_CMD_SET_ERRNO:
            get_user(value, puser);
            if(skb_queue_len(&g_chr_event.errno_queue) > CHR_ERRNO_QUEUE_MAX_LEN)
            {
                CHR_WARNING("chr errno queue is full, dispose errno=%x\n", value);
                break;
            }

            skb = alloc_skb(sizeof(value), GFP_KERNEL);
            if( NULL == skb)
            {
                CHR_ERR("chr errno alloc skbuff failed! len=%d, errno=%x\n", (int32)sizeof(value), value);
                return -ENOMEM;
            }

            skb_put(skb, sizeof(value));
            *(uint32*)skb->data = value;
            skb_queue_tail(&g_chr_event.errno_queue, skb);
            wake_up_interruptible(&g_chr_event.errno_wait);
            break;
        case CHR_CMD_GET_ERRNO:
            wait_event_interruptible(g_chr_event.errno_wait,  (skb_queue_len(&g_chr_event.errno_queue) > 0));
            skb = skb_dequeue(&g_chr_event.errno_queue);
            if (NULL == skb)
            {
                return -ENOMEM;
            }
            if (copy_to_user(puser, skb->data, sizeof(uint32)))
            {
                CHR_WARNING("copy_to_user err!restore it, len=%d\n", (int32)sizeof(uint32));
                skb_queue_head(&g_chr_event.errno_queue, skb);
                return -EFAULT;
            }
            skb_pull(skb, skb->len);
            kfree_skb(skb);
            break;
        default:
            CHR_WARNING("chr ioctl not support cmd=0x%x\n", cmd);
            break;
    }
    return CHR_SUCC;
}
/*****************************************************************************
 函 数 名  : chr_misc_release
 功能描述  : 释放节点设备接口
 输入参数  : struct inode *fd
             struct file* fp
             CHR_DEV_INDEX dev_index
 输出参数  : 无
 返 回 值  : static int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int32 chr_misc_release(struct inode *fd, struct file* fp, CHR_DEV_INDEX dev_index)
{
    int32 ret = 0;

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_DBG("chr %s release fail, module is disable\n", g_log_devs[dev_index].miscdev->name);
        return CHR_SUCC;
    }

    ret = chr_buff_free(dev_index);
    if (CHR_SUCC != ret)
    {
        CHR_ERR("chr dev %s free fail\n", g_subsystem_str[g_log_devs[dev_index].dev_index]);
        return -EAGAIN;
    }

    return CHR_SUCC;
}

/*****************************************************************************
 函 数 名  : show_chr_log_stat_info
 功能描述  : 查看设备节点状态接口
 输入参数  : struct device *dev
             struct kobj_attribute *attr
             int8 *buff
 输出参数  : 无
 返 回 值  : ssize_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月11日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
ssize_t show_chr_log_stat_info(struct device *dev, struct kobj_attribute *attr, int8 *buff)
{
    int32 len       = 0;
#ifdef CHR_LOG_STAT
    int32 dev_index = 0;
    int32 devs      = 0;

    devs = sizeof(g_log_devs) / sizeof(CHR_DEV);

    if (NULL == buff)
    {
        CHR_ERR("chr buff is NULL, line = %d\n", __LINE__);
        return -CHR_EFAIL;
    }

    for (dev_index = 0; dev_index < devs; dev_index++)
    {
        len += snprintf(buff + len, PAGE_SIZE - len, "dev:%s  open count = %d\n    log : Err %d  War %d  Info %d  Dbg %d  Drop %d\n    buff: Drop %d max_size %d\n", \
                      g_log_devs[dev_index].miscdev->name,     \
                      (int32)atomic_read(&(g_log_devs[dev_index].ref_count)),\
                      g_log_devs[dev_index].log_stat.e_count,  \
                      g_log_devs[dev_index].log_stat.w_count,  \
                      g_log_devs[dev_index].log_stat.i_count,  \
                      g_log_devs[dev_index].log_stat.d_count,  \
                      g_log_devs[dev_index].log_stat.log_drop, \
                      g_log_devs[dev_index].log_stat.buff_drop,\
                      g_log_devs[dev_index].log_stat.buff_max_size);
    }
#endif

    return len;
}

/*****************************************************************************
 函 数 名  : show_chr_log_switch
 功能描述  : 查看CHR功能开关状态接口
 输入参数  : struct device *dev
             struct kobj_attribute *attr
             int8 *buff
 输出参数  : 无
 返 回 值  : ssize_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月11日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
ssize_t show_chr_log_switch(struct device *dev, struct kobj_attribute *attr, int8 *buff)
{
    if (NULL == buff)
    {
        CHR_ERR("buf is NULL, line = %d\n", __LINE__);
        return -CHR_EFAIL;
    }

    if (CHR_LOG_ENABLE == g_log_enable)
    {
        CHR_INFO("chr module is enable\n");
    }
    else
    {
        CHR_INFO("chr module is disable\n");
    }

    return snprintf(buff, PAGE_SIZE, "1:enable other:disable value=%d\n", g_log_enable);
}

/*****************************************************************************
 函 数 名  : store_chr_log_switch
 功能描述  : 设置CHR模块开关状态接口
 输入参数  : struct device *dev
             struct kobj_attribute *attr
             const char *buff
             size_t count
 输出参数  : 无
 返 回 值  : ssize_t
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月11日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
ssize_t store_chr_log_switch(struct device *dev, struct kobj_attribute *attr, const char *buff, size_t count)
{
    int32 log_switch = 0;

    if (NULL == buff)
    {
        CHR_ERR("chr buff is NULL, line = %d\n", __LINE__);
        return -CHR_EFAIL;
    }

    if ((sscanf(buff, "%d", &log_switch) != 1))
    {
        CHR_INFO("set chr module switch fail\n");
        return -CHR_EFAIL;
    }

    if (CHR_LOG_ENABLE == log_switch)
    {
        g_log_enable = log_switch;
        CHR_INFO("set chr module enable\n");
    }
    else if (CHR_LOG_DISABLE == log_switch)
    {
        g_log_enable = log_switch;
        CHR_INFO("set chr module disable\n");
    }

    return count;
}
/*****************************************************************************
 函 数 名  : chr_dev_exception_callback
 功能描述  : device异常回调接口
 输入参数  : uint8 *buff
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月26日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
void chr_dev_exception_callback(void *buff, uint16 len)
{
    CHR_DEV_EXCEPTION_STRU* chr_dev_exception = NULL;

    if (NULL == buff)
    {
        CHR_WARNING("chr recv device errno fail, buff is NULL\n");
        return;
    }

    if (len != sizeof(CHR_DEV_EXCEPTION_STRU))
    {
        CHR_WARNING("chr recv device errno fail, len %d is unavailable\n", (int32)len);
        return;
    }

    chr_dev_exception = (CHR_DEV_EXCEPTION_STRU*)buff;
    if ((CHR_DEV_FRAME_START != chr_dev_exception->framehead) || (CHR_DEV_FRAME_END != chr_dev_exception->frametail))
    {
        CHR_WARNING("chr recv device errno fail, data is destoried\n");
        return;
    }

    __chr_exception(chr_dev_exception->errno);
    CHR_DBG("chr recv device errno = 0x%x\n", chr_dev_exception->errno);
}
EXPORT_SYMBOL(chr_dev_exception_callback);
/*****************************************************************************
 函 数 名  : chr_miscdev_init
 功能描述  :
 输入参数  : CHR_DEV_INDEX dev_index
 输出参数  : 无
 返 回 值  : static int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int32 chr_miscdev_init(CHR_DEV_INDEX dev_index)
{
    int32 ret = 0;

    sema_init(&g_log_devs[dev_index].user.buf_sema, 1);
    init_waitqueue_head(&g_log_devs[dev_index].read_waitqueue);
    g_log_devs[dev_index].user.size = g_buffer_size[dev_index];
    atomic_set(&g_log_devs[dev_index].user.r_off, 0);
    atomic_set(&g_log_devs[dev_index].user.w_off, 0);
    atomic_set(&g_log_devs[dev_index].ref_count,  0);

    if (CHR_INDEX_KMSG_PLAT == dev_index || CHR_INDEX_KMSG_WIFI == dev_index)
    {
        ret = chr_buff_alloc(dev_index);
        if (CHR_SUCC != ret)
        {
            CHR_ERR("chr dev %s alloc buff fail\n", g_subsystem_str[g_log_devs[dev_index].dev_index]);
            return -CHR_EFAIL;
        }
    }

#ifdef CHR_LOG_STAT
    g_log_devs[dev_index].log_stat.e_count       = 0;
    g_log_devs[dev_index].log_stat.w_count       = 0;
    g_log_devs[dev_index].log_stat.i_count       = 0;
    g_log_devs[dev_index].log_stat.d_count       = 0;
    g_log_devs[dev_index].log_stat.log_drop      = 0;
    g_log_devs[dev_index].log_stat.buff_drop     = 0;
    g_log_devs[dev_index].log_stat.buff_max_size = 0;
#endif

    ret = misc_register(g_log_devs[dev_index].miscdev);
    if (ret != CHR_SUCC)
    {
        CHR_ERR("chr dev %s register fail\n", g_subsystem_str[g_log_devs[dev_index].dev_index]);
        return -CHR_EFAIL;
    }

    return CHR_SUCC;
}

/*****************************************************************************
 函 数 名  : chr_miscdevs_register
 功能描述  :
 输入参数  : void
 输出参数  : 无
 返 回 值  : static int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int32 chr_miscdevs_register(void)
{
    int32 num     = 0;
    int32 ret     = 0;
    int32 dev_num = 0;

    init_waitqueue_head(&g_chr_event.errno_wait);
    skb_queue_head_init(&g_chr_event.errno_queue);

    dev_num = sizeof(g_log_devs) / sizeof(CHR_DEV);
    for (num = 0; num < dev_num; num++)
    {
        ret = chr_miscdev_init(num);
        if (CHR_SUCC != ret)
        {
            for (; num >= 0; num--)
            {
                if(NULL != g_log_devs[num].user.buffer)
                {
                    kfree(g_log_devs[num].user.buffer);
                    g_log_devs[num].user.buffer = NULL;
                }
                ret = misc_deregister(g_log_devs[num].miscdev);
                if (0 != ret)
                {
                    CHR_ERR("chr dev %s deregist fail\n", g_subsystem_str[g_log_devs[num].dev_index]);
                }
            }
            g_log_enable = CHR_LOG_DISABLE;
            return -CHR_EFAIL;
        }
    }
    g_log_enable = CHR_LOG_ENABLE;

    /*1103 close chr*/
    if (g_device_subchip_type == BOARD_VERSION_HI1103)
    {
        g_log_enable = CHR_LOG_DISABLE;
        CHR_INFO("chr close in board=%d", g_device_subchip_type);
    }

    return CHR_SUCC;
}

/*****************************************************************************
 函 数 名  : chr_miscdevs_unregister
 功能描述  :
 输入参数  : void
 输出参数  : 无
 返 回 值  : static int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
static int32 chr_miscdevs_unregister(void)
{
    int32 num     = 0;
    int32 ret     = 0;
    int32 result  = CHR_SUCC;
    int32 dev_num = sizeof(g_log_devs) / sizeof(CHR_DEV);

    if (CHR_LOG_ENABLE != g_log_enable)
    {
        CHR_INFO("chr module is diabled\n");
        return CHR_SUCC;
    }

    for(num = 0; num < dev_num; num++)
    {
        if(NULL != g_log_devs[num].user.buffer)
        {
            kfree(g_log_devs[num].user.buffer);
            g_log_devs[num].user.buffer = NULL;
        }
        ret = misc_deregister(g_log_devs[num].miscdev);
        if (CHR_SUCC != ret)
        {
            result = -CHR_EFAIL;
            CHR_ERR("chr dev %s deregister fail\n",g_subsystem_str[g_log_devs[num].dev_index]);
        }
    }

    g_log_enable = CHR_LOG_DISABLE;
    return result;
}

/*****************************************************************************
 函 数 名  : chr_miscdevs_init
 功能描述  :
 输入参数  : void
 输出参数  : 无
 返 回 值  : int32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
int32 chr_miscdevs_init(void)
{
    int32 ret = 0;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if (!is_my_chip()) {
        CHR_INFO("cfg chr log chip type is not match, skip driver init");
        g_log_enable = CHR_LOG_DISABLE;
        return -EINVAL;
    } else {
        CHR_INFO("cfg chr log is matched with hi110x, continue");
    }
#endif
    ret = chr_miscdevs_register();
    if (CHR_SUCC != ret)
    {
        CHR_ERR("chr module init fail\n");
        return -CHR_EFAIL;
    }
    CHR_INFO("chr module init succ\n");

    return CHR_SUCC;
}
/*****************************************************************************
 函 数 名  : chr_miscdevs_exit
 功能描述  :
 输入参数  : void
 输出参数  : 无
 返 回 值  : void
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2016年4月10日
    作    者   : k00355907
    修改内容   : 新生成函数

*****************************************************************************/
void chr_miscdevs_exit(void)
{
    int32 ret = 0;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if (!is_my_chip()) {
        CHR_INFO("cfg chr log chip type is not match, skip driver init");
        return;
    } else {
        CHR_INFO("cfg chr log is matched with hi110x, continue");
    }
#endif
    ret = chr_miscdevs_unregister();
    if (CHR_SUCC != ret)
    {
        CHR_ERR("chr module exit fail\n");
        return;
    }
    CHR_INFO("chr module exit succ\n");
}
MODULE_AUTHOR("Hisilicon platform Driver Group");
MODULE_DESCRIPTION("hi110x chr log driver");
MODULE_LICENSE("GPL");

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


