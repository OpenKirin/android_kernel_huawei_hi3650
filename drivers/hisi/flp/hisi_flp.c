/*
 * hisi flp driver.
 *
 * Copyright (C) 2015 huawei Ltd.
 * Author:lijiangxiong <lijingxiong@huawei.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/time.h>
#include <linux/notifier.h>
#include <linux/syscalls.h>
#include <net/genetlink.h>
#include <linux/workqueue.h>
#include <linux/hisi/hisi_syscounter.h>
#include <soc_acpu_baseaddr_interface.h>
#include <soc_syscounter_interface.h>
#include <clocksource/arm_arch_timer.h>
#include <linux/wakelock.h>
#include "protocol.h"
#include "inputhub_route.h"
#include "inputhub_bridge.h"

#include "hisi_flp.h"
#include "hisi_softtimer.h"

/*lint -e750 -esym(750,*) */
#define SAVE_PDR_DATA_TO_FILE       0
#define SAVE_PDR_DATA_TO_FTRACE     1
#define HISI_FLP_DEBUG              KERN_INFO
#define HISI_FLP_DUMP_HEX           0
#if SAVE_PDR_DATA_TO_FTRACE
#define CREATE_TRACE_POINTS
#include "hisi_flp_trace.h"
#endif
#define FLP_PDR_DATA            (0x1<<0)
#define FLP_AR_DATA             (0x1<<1)
#define PDR_DATA_MAX_COUNT      300
#define PDR_SINGLE_SEND_COUNT   48
#ifndef TRUE
#define  TRUE   1
#endif
/*lint +e750 +esym(750,*) */

typedef struct flp_ioctl_cmd{
    pkt_header_t    hd;
    unsigned int    sub_cmd; /*cmd sub type*/
} flp_ioctl_cmd_t;

/*lint -e750 -esym(754,*) */
typedef struct ar_ioctl_cmd{
    pkt_header_t    hd;
    unsigned char   core;
    unsigned char   rsv1;
    unsigned char   rsv2;
    unsigned char   sub_cmd;        /*cmd sub type*/
} ar_ioctl_cmd_t;
/*lint +e750 +esym(754,*) */

typedef struct flp_device {
    struct list_head        list;
    pdr_start_config_t      pdr_config;
    ar_start_config_t       ar_config;
    ar_start_mcu_config_t   ar_mcu_config;
    unsigned int            pdr_start_count;
    unsigned int            ar_start_count;
    unsigned int            pdr_flush_config ;
    unsigned int            service_type ;
    struct mutex            lock ;
    unsigned int            ar_current_state ;
    struct timespec         now;
    unsigned long           cycle_last ;
    unsigned int            pdr_cycle;
    compensate_data_t       pdr_compensate;
    unsigned int            denial_sevice;
    long                    pdr_last_utc;
} flp_device_t;

typedef struct flp_data_buf{
    char                  *data_buf;
    unsigned int          buf_size;
    unsigned int          read_index;
    unsigned int          write_index;
    unsigned int          data_count;
    struct mutex          data_mutex;
    wait_queue_head_t     pollq;
    unsigned int          to_wait;
} flp_data_buf_t;

typedef struct flp_port {
    struct list_head        list;
    unsigned int            port_type ;
    unsigned int            channel_type;
    struct softtimer_list   sleep_timer ;
    flp_data_buf_t          pdr_buf;
    flp_data_buf_t          ar_buf;
    pdr_start_config_t      pdr_config;
    pdr_start_config_t      pdr_update_config;
    ar_start_config_t       ar_config;
    unsigned int            rate ;          /*control get pdr data*/
    unsigned int            interval ;       /*control get pdr data*/
    unsigned int            nextid;         /*control get pdr data*/
    unsigned int            aquiredid;      /*control get pdr data*/
    unsigned int            pdr_flush_config  ;
    unsigned int            portid;
    unsigned long           total_count ;
    struct work_struct      work;
    unsigned int            work_para;
    unsigned int            need_awake;
    unsigned int            need_report;
    unsigned int            ar_current_cmd;
    compensate_data_t       pdr_compensate;
    struct wake_lock        wlock;
    unsigned int            need_hold_wlock;
} flp_port_t;

extern int inputhub_mcu_write_cmd_adapter(const void *buf,
        unsigned int length, read_info_t *rd);
extern int inputhub_mcu_write_cmd_nolock(const void *buf, unsigned int length);
extern int register_mcu_event_notifier(int tag, int cmd,
        int (*notify)(const pkt_header_t *head));
extern int getSensorMcuMode(void);
extern int hisi_get_timecounter(unsigned long *lastcycle, struct timespec *ts);

#define SEND_CMD_TO_SENSORHUB       inputhub_mcu_write_cmd_adapter
#define SEND_CMD_TO_SENSORHUB_NOLOCK  inputhub_mcu_write_cmd_nolock
#define PDR_REGISTER_CALLBACK       register_mcu_event_notifier

extern unsigned int g_flp_debug_level;
flp_device_t  g_flp_dev;

#define FLP_DEBUG(message...) \
do { \
    if (g_flp_debug_level) { \
        printk(message); \
    } \
} while (0)

#if HISI_FLP_DUMP_HEX
static void flp_hex_dump(char *buf, int size, char per_row)
{
    char line[256];
    int  left = size;
    char val;
    int i, row;

    if (!buf) {
        printk(KERN_ERR "(%s:%d):invalid buf.", __FUNCTION__, __LINE__);
        return;
    }

    per_row = (per_row > 60) ? 60 : per_row;
    if (!per_row) {
        per_row = 32;  /* [false alarm]:fortify */
    }

    printk(HISI_FLP_DEBUG "Dump buffer[%pK] size[%d]:\n", buf, size);

#define TO_CHAR(a)      (((a) > 9) ? ((a) - 10 + 'A') : ((a) + '0'))
#define IS_PRINTABLE(a) ((a) > 31 && (a) < 127)
/*lint -e440 -e702 -e679 -esym(440,*) -esym(702,*) -esym(679,*) */
    for (row = 0; left; row++) {
        (void)memset(line, ' ', sizeof(line));

        for (i = 0; (i < per_row) && left; i++, left--, buf++) {
            val = *buf;

            /* The HEX value */
            line[(i * 3)] = TO_CHAR(val >> 4);
            line[(i * 3) + 1] = TO_CHAR(val & 0x0F);

            /* print if it's ascii, or "." */
            line[(per_row * 3) + 2 + i] = IS_PRINTABLE(val) ? val : '.';
        }

        line[(per_row * 3) + 2 + per_row] = '\0';

        printk(HISI_FLP_DEBUG "[%4u]: %s\n", row * per_row, line);
    }
/*lint +e440 +e702 +e679 +esym(440,*) +esym(702,*) +esym(679,*) */
#undef TO_CHAR
#undef IS_PRINTABLE
}
#else
static void flp_hex_dump(char *buf, int size, char per_row)
{
    return;
}
#endif
long syscounter_to_utc(unsigned long cycle)
{
    struct timecounter *tc;
    struct timespec ts;
    unsigned long nsec;
    unsigned long deta;
    unsigned int rate = arch_timer_get_rate();
    if (unlikely(0 == rate)) {
        return 0;
    }
    tc = arch_timer_get_timecounter();
    if (likely(g_flp_dev.cycle_last  < cycle)) {
        deta = cycle - g_flp_dev.cycle_last;
        nsec = cyclecounter_cyc2ns(tc->cc, deta%rate, tc->mask, &tc->frac);
        ts = ns_to_timespec(nsec);
        ts.tv_sec += deta/rate;
        ts = timespec_add_safe(g_flp_dev.now, ts);
    } else  if (g_flp_dev.cycle_last > cycle) {
        deta = g_flp_dev.cycle_last  - cycle ;
        nsec = cyclecounter_cyc2ns(tc->cc, deta%rate, tc->mask, &tc->frac);
        ts = ns_to_timespec(nsec) ;
        ts.tv_sec += deta/rate ;
        set_normalized_timespec(&ts, (g_flp_dev.now.tv_sec -  ts.tv_sec -1),
                g_flp_dev.now.tv_nsec - ts.tv_nsec + NSEC_PER_SEC);
    } else {
        ts.tv_sec = g_flp_dev.now.tv_sec;
    }
    return ts.tv_sec;
}

int calc_GCD(unsigned int a, unsigned int b)
{
        unsigned int tmp;

        if (0 == a || 0 == b) {
                return 0;
        }

        /* Let a be the bigger one! */
        if (a < b) {
                tmp = a; a = b; b = tmp;
        }

        while ((a % b) != 0) {
                tmp = b;
                b = a % b;
                a = tmp;
        }
        return b;
}

static int send_cmd_from_user(unsigned char cmd_tag, unsigned char cmd_type,
    unsigned int subtype, char __user *buf, size_t count)
{
    char buffer[MAX_PKT_LENGTH] = {0};
    /*init sending cmd*/
    ((pkt_header_t *)buffer)->tag = cmd_tag;
    ((pkt_header_t *)buffer)->resp = NO_RESP;
    ((pkt_header_t *)buffer)->cmd = cmd_type;
    printk(HISI_FLP_DEBUG "flp:%s : cmdtype[%d] subtype[%d]\n", __func__, cmd_type, subtype);

    if (CMD_CMN_CONFIG_REQ != cmd_type) {
        if ((count) && (count < (MAX_PKT_LENGTH - sizeof(pkt_header_t)))) {   /* [false alarm]:fortify */
            if (copy_from_user(buffer + sizeof(pkt_header_t), buf, count)) {
                printk(KERN_ERR "copy_to_user error line:%d\n", __LINE__);
                return -EIO;
            }
        }
        ((pkt_header_t *)buffer)->length = count;
        SEND_CMD_TO_SENSORHUB(buffer, (count + sizeof(pkt_header_t)), NULL);
    } else {
        if (TAG_PDR == cmd_tag) {
            ((flp_ioctl_cmd_t *)buffer)->sub_cmd = subtype;
        } else {
            ((ar_ioctl_cmd_t *)buffer)->sub_cmd = (unsigned char)subtype;
        }
        if ((count) && (count < (MAX_PKT_LENGTH - sizeof(flp_ioctl_cmd_t)))) {
            if (copy_from_user(buffer + sizeof(flp_ioctl_cmd_t), buf, count)) {
                printk(KERN_ERR "copy_to_user error line:%d\n", __LINE__);
                return -EIO;
            }
        }
        ((pkt_header_t *)buffer)->length = count + sizeof(unsigned int);
        SEND_CMD_TO_SENSORHUB(buffer, (count + sizeof(flp_ioctl_cmd_t)), NULL);
    }
    return 0;
}

static int send_cmd_from_kernel(unsigned char cmd_tag, unsigned char cmd_type,
    unsigned int subtype, char  *buf, size_t count)
{
    char buffer[MAX_PKT_LENGTH] = {0};
    int ret = 0;
    /*init sending cmd*/
    ((pkt_header_t *)buffer)->tag = cmd_tag;
    ((pkt_header_t *)buffer)->resp = NO_RESP;
    ((pkt_header_t *)buffer)->cmd = cmd_type;
    printk(HISI_FLP_DEBUG "flp:%s : cmdtype[%d] subtype[%d] count[%ld]\n",
        __func__, cmd_type, subtype, count);

    if (CMD_CMN_CONFIG_REQ != cmd_type) {
        if ((count) && (count < (MAX_PKT_LENGTH - sizeof(pkt_header_t)))) {
            memcpy(buffer + sizeof(pkt_header_t), buf, count);
        }
        ((pkt_header_t *)buffer)->length = count;
        ret = SEND_CMD_TO_SENSORHUB(buffer, (count + sizeof(pkt_header_t)), NULL);
    } else {
        if (TAG_PDR == cmd_tag) {
            ((flp_ioctl_cmd_t *)buffer)->sub_cmd = subtype;
        } else {
            ((ar_ioctl_cmd_t *)buffer)->sub_cmd = (unsigned char)subtype;
        }
        if ((count) && (count < (MAX_PKT_LENGTH - sizeof(flp_ioctl_cmd_t)))) {
            memcpy(buffer + sizeof(flp_ioctl_cmd_t), buf, count);
        }
        ((pkt_header_t *)buffer)->length = count + sizeof(unsigned int);
        ret = SEND_CMD_TO_SENSORHUB(buffer, (count + sizeof(flp_ioctl_cmd_t)), NULL);
    }
    if (ret) {
        printk(KERN_ERR "%s error\n", __func__);
    }
    return ret;
}

static int send_cmd_from_kernel_nolock(unsigned char cmd_tag, unsigned char cmd_type,
    unsigned int subtype, char  *buf, size_t count)
{
    char buffer[MAX_PKT_LENGTH] = {0};
    int ret = 0;
    /*init sending cmd*/
    ((pkt_header_t *)buffer)->tag = cmd_tag;
    ((pkt_header_t *)buffer)->resp = NO_RESP;
    ((pkt_header_t *)buffer)->cmd = cmd_type;
    printk(HISI_FLP_DEBUG "flp:%s : cmdtype[%d] subtype[%d]\n", __func__, cmd_type, subtype);

    if (CMD_CMN_CONFIG_REQ != cmd_type) {
        if ((count) && (count < (MAX_PKT_LENGTH - sizeof(pkt_header_t)))){
            memcpy(buffer + sizeof(pkt_header_t), buf, count);
        }
        ((pkt_header_t *)buffer)->length = count;
        ret = SEND_CMD_TO_SENSORHUB_NOLOCK(buffer, (count + sizeof(pkt_header_t)));
    } else {
        if (TAG_PDR == cmd_tag) {
            ((flp_ioctl_cmd_t *)buffer)->sub_cmd = subtype;
        } else {
            ((ar_ioctl_cmd_t *)buffer)->sub_cmd = (unsigned char)subtype;
        }
        if ((count) && (count < (MAX_PKT_LENGTH - sizeof(flp_ioctl_cmd_t)))) {
            memcpy(buffer + sizeof(flp_ioctl_cmd_t), buf, count);
        }
        ((pkt_header_t *)buffer)->length = count + sizeof(unsigned int);
        ret = SEND_CMD_TO_SENSORHUB_NOLOCK(buffer, (count + sizeof(flp_ioctl_cmd_t)));
    }
    if (ret) {
        printk(KERN_ERR "%s error\n", __func__);
    }
    return ret;
}

static int flp_generate_netlink_packet(flp_port_t *flp_port, char *buf,
        unsigned int count, unsigned char cmd_type)
{
    flp_data_buf_t *pdata = NULL ;
    struct sk_buff *skb;
    void *msg_header;
    char *data ;
    int size;
    int result;
    static unsigned int flp_event_seqnum = 0;
    if (((FLP_GENL_CMD_PDR_DATA == cmd_type) || (FLP_GENL_CMD_AR_DATA == cmd_type)) &&
         (!count)) {
        return 0;
    }
    if (!flp_port) {
        printk(KERN_ERR "%s error\n", __func__);
        return -EINVAL;
    }
    if (FLP_GENL_CMD_PDR_DATA == cmd_type) {
        pdata = &flp_port->pdr_buf;
    } else if (FLP_GENL_CMD_AR_DATA == cmd_type) {
        pdata = &flp_port->ar_buf;
    }
    /*app receive pdr data unrecomend block read;*/
    if (0 == flp_port->portid) {
        if (pdata)
            wake_up_interruptible(&pdata->pollq);
        return 0;
    }
    /* allocate memory */
    size = nla_total_size(count + nla_total_size(0));

    skb = genlmsg_new(size, GFP_ATOMIC);
    if (!skb)
        return -ENOMEM;

    /* add the genetlink message header */
    msg_header = genlmsg_put(skb, 0, flp_event_seqnum++,
                                &flp_genl_family, 0,
                                cmd_type);
    if (!msg_header) {
        nlmsg_free(skb);
        return -ENOMEM;
    }

    /* fill the data */
    data = nla_reserve_nohdr(skb, count);
    if (!data) {
        nlmsg_free(skb);
        return -EINVAL;
    }
    switch (cmd_type) {
        case FLP_GENL_CMD_PDR_DATA:
        case FLP_GENL_CMD_AR_DATA:
            if (!pdata) {
                printk(KERN_ERR "%s error\n", __func__);
                return -EINVAL;
            }
            if (count  > pdata->data_count) {
                count = pdata->data_count;
            }

            /*copy data to user buffer*/
            if ((pdata->read_index + count) >  pdata->buf_size) {
                memcpy(data, pdata->data_buf + pdata->read_index, pdata->buf_size - pdata->read_index);
                memcpy(data + pdata->buf_size - pdata->read_index,
                    pdata->data_buf,
                    count + pdata->read_index - pdata->buf_size);
            } else {
                memcpy(data, pdata->data_buf + pdata->read_index, count);
            }
            pdata->read_index = (pdata->read_index + count)%pdata->buf_size;
            pdata->data_count -= count;
            break ;
        default:
            if (buf && count) {
                memcpy(data, buf, count);
            }
            break ;
    };

    genlmsg_end(skb, msg_header);

    printk(HISI_FLP_DEBUG "%s 0x%x:%d: \n", __func__, flp_port->port_type, count);
    /* send unicast genetlink message */
    result = genlmsg_unicast(&init_net, skb, flp_port->portid);
    if (result)
        printk(KERN_ERR "flp:Failed to send netlink event:%d", result);

    return result;
}

static void ar_start_cmd_compress(ar_start_mcu_config_t *pdst, ar_start_config_t *psrc)
{
    unsigned int count;
    ar_activity_config_t *pevent;

    pevent = psrc->activity_list;
    pdst->event_num = 0;
    pdst->report_interval = psrc->report_interval;
    for (pdst->event_num = 0, count = 0; count < AR_STATE_BUTT; count++) {
        if (pevent->event_type != 0) {
            memcpy(&pdst->activity_list[pdst->event_num], pevent, sizeof(ar_activity_config_t));
            pdst->event_num ++ ;
        }
        pevent ++ ;
    }
    return ;
}

static ssize_t  flp_read_cmd(flp_port_t *flp_port, char __user *buf,
    size_t count, unsigned int type)
{
    unsigned int  len = count;
    unsigned long ret = 0;
    flp_data_buf_t *pdata;

    /*check port is valid*/
    if (!flp_port) {
        printk(KERN_ERR "flp_read parameter error\n");
        return -EINVAL;
    }

    if (!(flp_port->channel_type & type)) {
        printk(KERN_ERR "flp_port isnot start;channel_type %x\n", flp_port->channel_type);
        return -EINVAL;
    }
    if (FLP_PDR_DATA == type) {
        pdata = &flp_port->pdr_buf;
    } else {
        pdata = &flp_port->ar_buf;
    }
    pdata->to_wait = true;
    ret = wait_event_interruptible(pdata->pollq, ((pdata->data_count > 0) || (!pdata->to_wait)));
    if (ret)
        return ret;
    /*check data lenghth is valid*/
    if (FLP_PDR_DATA == type) {
        if (count%(sizeof(flp_pdr_data_t))) {
            len = ((count)/(sizeof(flp_pdr_data_t))) * (sizeof(flp_pdr_data_t));
        }
    } else {
        if (count%(sizeof(ar_activity_event_t))) {
            len = ((count)/(sizeof(ar_activity_event_t))) * (sizeof(ar_activity_event_t));
        }
    }

    if (len > pdata->data_count) {
        len = pdata->data_count;
    }
    printk(HISI_FLP_DEBUG "%s 0x%x\n", __func__, len);
    if (!len)
        return 0;

    mutex_lock(&pdata->data_mutex);

    /*copy data to user buffer*/
    if ((pdata->read_index + len) >  pdata->buf_size) {
        ret = copy_to_user(buf, pdata->data_buf + pdata->read_index,
                pdata->buf_size - pdata->read_index);
        ret += copy_to_user(buf + pdata->buf_size - pdata->read_index,
            pdata->data_buf,
            len + pdata->read_index - pdata->buf_size);
        flp_hex_dump((char *)(pdata->data_buf + pdata->read_index),
                    pdata->buf_size - pdata->read_index, sizeof(flp_pdr_data_t));
        flp_hex_dump((char *)(pdata->data_buf),
                    len + pdata->read_index - pdata->buf_size, sizeof(flp_pdr_data_t));
    } else {
        ret = copy_to_user(buf, pdata->data_buf + pdata->read_index , len);
        flp_hex_dump((char *)(pdata->data_buf + pdata->read_index), len, sizeof(flp_pdr_data_t));
    }
    if (ret) {
        mutex_unlock(&pdata->data_mutex);
        printk(KERN_ERR "flp_read copy_to_user error[%ld]\n", ret);
        return 0;
    }
    pdata->read_index = (pdata->read_index + len)%pdata->buf_size;
    pdata->data_count -= len;
    mutex_unlock(&pdata->data_mutex);
    return len ;
}

static int  flp_stop_cmd(flp_port_t *flp_port, unsigned int timeout, unsigned int  type)
{
    struct list_head    *pos;
    flp_port_t      *port;
    unsigned int count;
    unsigned int delay = timeout;

    if (FLP_PDR_DATA == type) {
        g_flp_dev.pdr_start_count-- ;
        if ((flp_port->channel_type & FLP_PDR_DATA) && (0 == flp_port->portid)) {
            flp_port->pdr_buf.data_count = 0;
            flp_port->pdr_buf.to_wait = false;
            wake_up_interruptible(&flp_port->pdr_buf.pollq);
        }
        flp_port->channel_type &= (~FLP_PDR_DATA);
        memset((void *)&flp_port->pdr_config, 0, sizeof(pdr_start_config_t));
        if (0 == g_flp_dev.pdr_start_count) {
            memset((void *)&g_flp_dev.pdr_config, 0, sizeof(pdr_start_config_t));
            delay = 0;
            send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ,
                    CMD_FLP_PDR_STOP_REQ, (char *)&delay, sizeof(int));
            send_cmd_from_kernel(TAG_PDR, CMD_CMN_CLOSE_REQ, 0, NULL, 0);
            g_flp_dev.pdr_cycle = 0;
            g_flp_dev.service_type &= ~FLP_PDR_DATA;
        } else if (1 == g_flp_dev.pdr_start_count) {
            list_for_each(pos, &g_flp_dev.list) {
                port = container_of(pos, flp_port_t, list);
                if ((port != flp_port) && (port->channel_type & FLP_PDR_DATA)) {
                    memcpy((void *)&g_flp_dev.pdr_config, &port->pdr_config, sizeof(pdr_start_config_t));
                    break;
                }
            }
            g_flp_dev.pdr_flush_config = FLP_IOCTL_PDR_STOP(0);
            send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_FLUSH_REQ, NULL, 0);
            send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_UPDATE_REQ,
                 (char *)&g_flp_dev.pdr_config, sizeof(pdr_start_config_t));

        } else {
            return 0;
        }
    } else {
        memset((void *)&g_flp_dev.ar_config, 0, sizeof(ar_start_config_t));
        memset((void *)&flp_port->ar_config, 0, sizeof(ar_start_config_t));
        g_flp_dev.ar_start_count--;
        if ((flp_port->channel_type & FLP_AR_DATA) && (0 == flp_port->portid)){
            flp_port->ar_buf.data_count = 0;
            flp_port->ar_buf.to_wait = false;
            wake_up_interruptible(&flp_port->ar_buf.pollq);
        }
        flp_port->channel_type &= (~FLP_AR_DATA);
        for (count = 0; count < AR_STATE_BUTT; count++) {
             g_flp_dev.ar_config.activity_list[count].activity = count;
        }
        if (g_flp_dev.ar_start_count) {
            list_for_each(pos, &g_flp_dev.list) {
                port = container_of(pos, flp_port_t, list);
                if ((port != flp_port) && (port->channel_type & FLP_AR_DATA)) {
                    if (g_flp_dev.ar_config.report_interval) {
                        g_flp_dev.ar_config.report_interval = (g_flp_dev.ar_config.report_interval > port->ar_config.report_interval) ?
                            port->ar_config.report_interval : g_flp_dev.ar_config.report_interval;
                    } else {
                        g_flp_dev.ar_config.report_interval = port->ar_config.report_interval;
                    }
                    for (count = 0; count < AR_STATE_BUTT ; count++) {
                         g_flp_dev.ar_config.activity_list[count].event_type |=
                            port->ar_config.activity_list[count].event_type ;
                    }
                }
            }
            ar_start_cmd_compress(&g_flp_dev.ar_mcu_config, &g_flp_dev.ar_config);
            send_cmd_from_kernel(TAG_AR, CMD_CMN_CONFIG_REQ, CMD_FLP_AR_UPDATE_REQ,
                (char *)&g_flp_dev.ar_mcu_config + sizeof(unsigned int),
                g_flp_dev.ar_mcu_config.event_num * sizeof(ar_activity_config_t) + sizeof(unsigned int));
        } else {
            delay = 0;
            send_cmd_from_kernel(TAG_AR, CMD_CMN_CONFIG_REQ, CMD_FLP_AR_STOP_REQ, (char *)&delay, sizeof(int));
            send_cmd_from_kernel(TAG_AR, CMD_CMN_CLOSE_REQ, 0, NULL, 0);
            g_flp_dev.service_type &= ~FLP_AR_DATA;
            g_flp_dev.ar_current_state = AR_STATE_BUTT;
        }
    }
    printk(HISI_FLP_DEBUG "flp_stop_cmd report_interval[%d] AR[%d]\n", g_flp_dev.ar_config.report_interval, g_flp_dev.ar_start_count);
    return 0;
}

static int  flp_pdr_start_cmd(flp_port_t *flp_port, const char __user *buf, size_t len)
{
    if (len != sizeof(pdr_start_config_t)) {
        printk(KERN_ERR "flp_start_cmd count error\n");  /* [false alarm]:fortify */
        return -EINVAL;
    }

    if (copy_from_user(&flp_port->pdr_config, buf, len)) {
        printk(KERN_ERR "flp_start_cmd copy_from_user error\n");
        return -EIO;
    }
    if (0 == flp_port->pdr_config.report_interval ||
        0 == flp_port->pdr_config.report_precise ||
        0 == flp_port->pdr_config.report_count) {
        printk(KERN_ERR "flp_start_cmd error  line[%d]\n", __LINE__);
        return -EINVAL;
    }
    if (flp_port->pdr_config.report_interval <
        flp_port->pdr_config.report_count * flp_port->pdr_config.report_precise) {
        printk(KERN_ERR "flp_start_cmd error  line[%d]\n", __LINE__);
        return -EINVAL;
    }
    if (flp_port->pdr_config.report_interval/flp_port->pdr_config.report_precise >
        PDR_DATA_MAX_COUNT) {
        printk(KERN_ERR "flp_start_cmd error  line[%d]\n", __LINE__);
        return -EINVAL;
    }
    /*differ app multi start*/
    if (g_flp_dev.pdr_start_count) {
        g_flp_dev.pdr_config.report_precise = 1000;
        g_flp_dev.pdr_config.report_interval =
            calc_GCD(g_flp_dev.pdr_config.report_interval, flp_port->pdr_config.report_interval);
        g_flp_dev.pdr_config.report_count = 1 ;
        g_flp_dev.pdr_config.report_times = 0;

        flp_port->pdr_flush_config = TRUE;
        g_flp_dev.pdr_flush_config = FLP_IOCTL_PDR_START(0);
        flp_port->rate = flp_port->pdr_config.report_precise / g_flp_dev.pdr_config.report_precise ;
        flp_port->interval = flp_port->pdr_config.report_interval / g_flp_dev.pdr_config.report_precise ;
        send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_FLUSH_REQ, NULL, 0);
        send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_UPDATE_REQ,
            (char *)&g_flp_dev.pdr_config, sizeof(pdr_start_config_t));
    } else {
        memcpy(&g_flp_dev.pdr_config, &flp_port->pdr_config, sizeof(pdr_start_config_t));
        g_flp_dev.pdr_cycle = g_flp_dev.pdr_config.report_precise;
        g_flp_dev.pdr_config.report_times = 0;
        flp_port->rate = 1 ;
        flp_port->interval = flp_port->pdr_config.report_interval/g_flp_dev.pdr_config.report_precise ;
        send_cmd_from_kernel(TAG_PDR, CMD_CMN_OPEN_REQ, 0, NULL, 0);
        g_flp_dev.service_type |= FLP_PDR_DATA;
        send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_START_REQ,
            (char *)&g_flp_dev.pdr_config, sizeof(pdr_start_config_t));
    }
    flp_port->nextid = 0;
    flp_port->aquiredid = 0;
    printk(KERN_ERR "flp[%d]:interval:%d,precise:%d,count:%d\n",
            flp_port->port_type, flp_port->pdr_config.report_interval,
            flp_port->pdr_config.report_precise, flp_port->pdr_config.report_count);
    g_flp_dev.pdr_start_count++ ;
    flp_port->channel_type |= FLP_PDR_DATA;
    return 0;
}

static int  flp_ar_start_cmd(flp_port_t *flp_port, const char __user *buf, size_t len)
{
    unsigned int count;   /* [false alarm]:fortify */
    struct list_head    *pos;
    flp_port_t      *port;
    ar_start_hal_config_t hal_config;
    ar_activity_config_t *plist;
    ar_activity_config_t *pevent;

    if (len != sizeof(ar_start_hal_config_t)) {
        printk(KERN_ERR "flp_start_cmd count error\n"); /* [false alarm]:fortify */
        return -EINVAL;
    }
    if (copy_from_user((void *)&hal_config, buf, len)) {   /* [false alarm]:fortify */
        printk(KERN_ERR "%s copy_to_user error\n", __func__);
        return -EIO;
    }
    if (hal_config.event_num > AR_STATE_BUTT) {
        printk(KERN_ERR "event_num error\n");
        return -EINVAL;
    }
    plist = g_flp_dev.ar_mcu_config.activity_list;
    if (copy_from_user((void *)plist, (void __user *)hal_config.pevent,
            sizeof(ar_activity_config_t) * hal_config.event_num)) {   /* [false alarm]:fortify */
        printk(KERN_ERR "%s copy_to_user error\n", __func__);
        return -EIO;
    }
    memset(&flp_port->ar_config, 0, sizeof(ar_start_config_t));
    flp_port->ar_config.report_interval = hal_config.report_interval;
    pevent = plist;
    for (count = 0; count < hal_config.event_num; count++) {
        if (pevent->activity >= AR_STATE_BUTT) {
            continue ;
        }
        flp_port->ar_config.activity_list[pevent->activity].activity = pevent->activity;
        flp_port->ar_config.activity_list[pevent->activity].event_type= pevent->event_type;
        pevent ++;
    }
     /*differ app multi start; or same app send update*/
    if (g_flp_dev.ar_start_count) {
        memcpy(&g_flp_dev.ar_config, &flp_port->ar_config, sizeof(ar_start_config_t));
        for (count = 0; count < AR_STATE_BUTT; count++) {
             g_flp_dev.ar_config.activity_list[count].activity = count;
        }
        list_for_each(pos, &g_flp_dev.list) {
            port = container_of(pos, flp_port_t, list);
            if ((port != flp_port) && (port->channel_type & FLP_AR_DATA)) {
                for (count = 0; count < AR_STATE_BUTT ; count++) {
                     g_flp_dev.ar_config.activity_list[count].event_type |=
                        port->ar_config.activity_list[count].event_type;
                }
                g_flp_dev.ar_config.report_interval = (g_flp_dev.ar_config.report_interval > flp_port->ar_config.report_interval) ?
                            flp_port->ar_config.report_interval : g_flp_dev.ar_config.report_interval;
            }
        }
        ar_start_cmd_compress(&g_flp_dev.ar_mcu_config, &g_flp_dev.ar_config);
        send_cmd_from_kernel(TAG_AR, CMD_CMN_CONFIG_REQ, CMD_FLP_AR_UPDATE_REQ,
            (char *)&g_flp_dev.ar_mcu_config + sizeof(unsigned int),
            g_flp_dev.ar_mcu_config.event_num * sizeof(ar_activity_config_t) + sizeof(unsigned int));
    } else {
        memcpy(&g_flp_dev.ar_config, &flp_port->ar_config, sizeof(ar_start_config_t));
        ar_start_cmd_compress(&g_flp_dev.ar_mcu_config, &g_flp_dev.ar_config);
        send_cmd_from_kernel(TAG_AR, CMD_CMN_OPEN_REQ, 0, NULL, 0);
        g_flp_dev.service_type |= FLP_AR_DATA;
        send_cmd_from_kernel(TAG_AR, CMD_CMN_CONFIG_REQ, CMD_FLP_AR_START_REQ,
            (char *)&g_flp_dev.ar_mcu_config + sizeof(unsigned int),
            g_flp_dev.ar_mcu_config.event_num * sizeof(ar_activity_config_t) + sizeof(unsigned int));
    }

    g_flp_dev.ar_start_count++ ;
    flp_port->channel_type |= FLP_AR_DATA;
    flp_hex_dump((char *)&g_flp_dev.ar_mcu_config + 8,
        (int)(g_flp_dev.ar_mcu_config.event_num * sizeof(ar_activity_config_t)), (char)sizeof(ar_activity_config_t));
    printk(HISI_FLP_DEBUG "flp_ar_start_cmd report_interval[%d] src[%d]\n",
        g_flp_dev.ar_config.report_interval, flp_port->ar_config.report_interval);
    return 0;
}

static int  flp_pdr_update_cmd(flp_port_t *flp_port, const char __user *buf, size_t len)
{
    if (len != sizeof(pdr_start_config_t)) {
        printk(KERN_ERR "flp_start_cmd count error\n");  /* [false alarm]:fortify */
        return -EINVAL;
    }

    if (copy_from_user(&flp_port->pdr_update_config, buf, len)) {
        printk(KERN_ERR "flp_start_cmd copy_from_user error\n");
        return -EIO;
    }
    if (0 == flp_port->pdr_update_config.report_interval ||
        0 == flp_port->pdr_update_config.report_precise ||
        0 == flp_port->pdr_update_config.report_count) {
        printk(KERN_ERR "flp_start_cmd error  line[%d]\n", __LINE__);
        return -EINVAL;
    }
    if (flp_port->pdr_update_config.report_interval <
        flp_port->pdr_update_config.report_count * flp_port->pdr_update_config.report_precise){
        printk(KERN_ERR "flp_start_cmd error  line[%d]\n", __LINE__);
        return -EINVAL;
    }
    if (flp_port->pdr_update_config.report_interval/flp_port->pdr_update_config.report_precise >
            PDR_DATA_MAX_COUNT) {
        printk(KERN_ERR "flp_start_cmd error  line[%d]\n", __LINE__);
        return -EINVAL;
    }
    /*differ app multi start*/
    if (g_flp_dev.pdr_start_count > 1) {
        g_flp_dev.pdr_config.report_precise = 1000;
        g_flp_dev.pdr_config.report_interval =
            calc_GCD(g_flp_dev.pdr_config.report_interval, flp_port->pdr_update_config.report_interval);
        g_flp_dev.pdr_config.report_count = 1 ;
        g_flp_dev.pdr_config.report_times = 0;
    }   else {
        memcpy(&g_flp_dev.pdr_config, &flp_port->pdr_update_config, sizeof(pdr_start_config_t));
        g_flp_dev.pdr_config.report_times = 0;
    }
    flp_port->pdr_flush_config = TRUE ;
    g_flp_dev.pdr_flush_config = FLP_IOCTL_PDR_UPDATE(0);
    send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_FLUSH_REQ,
        NULL, 0);
    send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_UPDATE_REQ,
        (char *)&g_flp_dev.pdr_config, sizeof(pdr_start_config_t));

    printk(KERN_ERR "flp[%d]:interval:%d,precise:%d,count:%d\n",
            flp_port->port_type, flp_port->pdr_update_config.report_interval,
            flp_port->pdr_update_config.report_precise, flp_port->pdr_update_config.report_count);
    return 0;
}

static int  flp_ar_update_cmd(flp_port_t *flp_port, const char __user *buf, size_t len)
{
    unsigned int count;   /* [false alarm]:fortify */
    struct list_head    *pos;
    flp_port_t      *port;
    ar_start_hal_config_t hal_config;
    ar_activity_config_t  *plist;
    ar_activity_config_t  *pevent;

    if (len != sizeof(ar_start_hal_config_t)) {
        printk(KERN_ERR "flp_start_cmd count error\n"); /* [false alarm]:fortify */
        return -EINVAL;
    }
    if (0 == g_flp_dev.ar_start_count) {
        printk(KERN_ERR "port not start\n");
        return -EIO;
    }
    if (copy_from_user((void *)&hal_config, buf, len)) {   /* [false alarm]:fortify */
        printk(KERN_ERR "flp_write copy_to_user error\n");
        return -EIO;
    }
    if (hal_config.event_num > AR_STATE_BUTT) {
        printk(KERN_ERR "event_num error\n");
        return -EINVAL;
    }

    plist = g_flp_dev.ar_mcu_config.activity_list;
    if (copy_from_user((void *)plist, (void __user *)hal_config.pevent,
            sizeof(ar_activity_config_t) * hal_config.event_num)) {   /* [false alarm]:fortify */
        printk(KERN_ERR "%s copy_to_user error\n", __func__);
        return -EIO;
    }
    memset(&flp_port->ar_config, 0, sizeof(ar_start_config_t));
    flp_port->ar_config.report_interval = hal_config.report_interval;
    pevent = plist;
    for (count = 0; count < hal_config.event_num; count++) {
        if (pevent->activity >= AR_STATE_BUTT) {
            continue ;
        }
        flp_port->ar_config.activity_list[pevent->activity].activity = pevent->activity;
        flp_port->ar_config.activity_list[pevent->activity].event_type= pevent->event_type;
        pevent ++;
    }

    /*differ app multi start; or same app send update*/
    memcpy(&g_flp_dev.ar_config, &flp_port->ar_config, sizeof(ar_start_config_t));
    for (count = 0; count < AR_STATE_BUTT ; count++) {
         g_flp_dev.ar_config.activity_list[count].activity = count;
    }
    if (g_flp_dev.ar_start_count > 1) {
        list_for_each(pos, &g_flp_dev.list) {
            port = container_of(pos, flp_port_t, list);
            if ((port != flp_port) && (port->channel_type & FLP_AR_DATA)) {
                for (count = 0; count < AR_STATE_BUTT; count++) {
                     g_flp_dev.ar_config.activity_list[count].event_type |=
                        port->ar_config.activity_list[count].event_type ;
                }
                g_flp_dev.ar_config.report_interval = (g_flp_dev.ar_config.report_interval > flp_port->ar_config.report_interval) ?
                    flp_port->ar_config.report_interval : g_flp_dev.ar_config.report_interval;
            }
        }
    }
    ar_start_cmd_compress(&g_flp_dev.ar_mcu_config, &g_flp_dev.ar_config);
    send_cmd_from_kernel(TAG_AR, CMD_CMN_CONFIG_REQ, CMD_FLP_AR_UPDATE_REQ,
            (char *)&g_flp_dev.ar_mcu_config + sizeof(unsigned int),
            g_flp_dev.ar_mcu_config.event_num * sizeof(ar_activity_config_t) + sizeof(unsigned int));
    flp_hex_dump((char *)&g_flp_dev.ar_mcu_config + 8,
        (int)(g_flp_dev.ar_mcu_config.event_num * sizeof(ar_activity_config_t)), (char)sizeof(ar_activity_config_t));
    printk(HISI_FLP_DEBUG "flp_ar_update_cmd report_interval[%d] src[%d]\n",
        g_flp_dev.ar_config.report_interval, flp_port->ar_config.report_interval);
    return 0;
}

static ssize_t  pdr_write_cmd(flp_port_t *flp_port, char __user *buf, size_t count)
{
    printk(HISI_FLP_DEBUG "%s %d: \n", __func__, __LINE__);

    /*check input parameter*/
    if (!flp_port) {
        printk(KERN_ERR "flp_write parameter error\n");
        return -EINVAL;
    }
    if (count > (MAX_PKT_LENGTH - sizeof(pkt_header_t))) {
        printk(KERN_ERR "flp_write parameter error\n");
        return -EINVAL;
    }

    send_cmd_from_user(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_WRITE_REQ, buf, count);
    return count;
}

static void copy_data_to_buf(flp_data_buf_t *pdata, char *data,
        unsigned int len, unsigned int align)
{
    unsigned int deta;
    /*no enough space , just overwrite*/
    if ((pdata->data_count + len) > pdata->buf_size) {
        deta = pdata->data_count + len - pdata->buf_size;
        if (deta % align) {
            printk(KERN_ERR "copy_data_to_buf data not align\n");
            deta = (deta/align + 1)*align;
        }
        pdata->read_index = (pdata->read_index + deta)%pdata->buf_size;
    }
    /*copy data to flp pdr driver buffer*/
    if ((pdata->write_index + len) >  pdata->buf_size) {
        memcpy(pdata->data_buf + pdata->write_index , data, pdata->buf_size - pdata->write_index);
        memcpy(pdata->data_buf,
            data + pdata->buf_size - pdata->write_index,
            len + pdata->write_index - pdata->buf_size);
    } else {
        memcpy(pdata->data_buf + pdata->write_index, data , len);
    }
    pdata->write_index = (pdata->write_index + len)%pdata->buf_size;
    pdata->data_count = (pdata->write_index - pdata->read_index + pdata->buf_size)%pdata->buf_size;
    /*if buf is full*/
    if (!pdata->data_count) {
        pdata->data_count = pdata->buf_size;
    }
}

#if SAVE_PDR_DATA_TO_FILE
#define PDR_FILE_PATH           "/storage/sdcard0/PDRdata/data.txt"
#define PDR_FILE_SIZE           (0x1<<16)
static int save_pdr_data_to_file(flp_pdr_data_t *data, unsigned int count)
{
    int ret = 0, flags;
    struct file *fp;
    mm_segment_t old_fs;
    int size;
    char buf[32];
    unsigned int j;
    unsigned long fd;

    if (!(data) || !(count)) {
        return 0;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_access("/storage/sdcard0/PDRdata", 0);
    if (0 != fd) {
        fd  = sys_mkdir("/storage/sdcard0/PDRdata", 0755);
        if (fd < 0) {
            printk(KERN_ERR "%s:create file err:%ld.\n", __func__, fd);
            set_fs(old_fs);
            return -1;
        }
    }

    flags = O_CREAT | O_RDWR | O_TRUNC;
    fp = filp_open(PDR_FILE_PATH, flags, 0666);
    if (IS_ERR(fp)) {
        set_fs(old_fs);
        printk(KERN_ERR "%s():create file err.\n", __func__);
        return -1;
    }
    for (j = 0; j < count; j++)  {
        size = snprintf(buf, 32, "%d:%d\n", data->relative_position_x, data->relative_position_y);
        ret = vfs_write(fp, buf, size, &(fp->f_pos));
        if (ret != size) {
            printk(KERN_ERR "%s():write file exception with ret %d.\n", __func__,  ret);
            goto err;
        }
        data++ ;
    }

err:
    filp_close(fp, NULL);
    set_fs(old_fs);
    return ret ;

}
#endif

static int get_pdr_notify_from_mcu(const pkt_header_t *head)
{
    flp_port_t *flp_port ;
    struct list_head    *pos;
    int *data = (int *) (head + 1);
    int ret = 0;
    if (list_empty(&g_flp_dev.list)) {
        printk(KERN_ERR "flp pdr no port be opened\n");
        return -EFAULT;
    }
    if (CMD_FLP_PDR_UNRELIABLE_REQ == head->cmd) {
        mutex_lock(&g_flp_dev.lock);
        list_for_each(pos, &g_flp_dev.list) {
            flp_port = container_of(pos, flp_port_t, list);
            if (!(flp_port->channel_type&FLP_PDR_DATA)) {
                continue ;
            }

            if (*data < 2) {
                ret |= flp_generate_netlink_packet(flp_port, (char *)data,
                        sizeof(int), FLP_GENL_CMD_PDR_UNRELIABLE);
            } else if ((2 == *data) && (flp_port->need_report)) {
                ret |= flp_generate_netlink_packet(flp_port, (char *)data,
                        sizeof(int), FLP_GENL_CMD_PDR_UNRELIABLE);
            }
        }
        mutex_unlock(&g_flp_dev.lock);
    }
    return ret;
}

static int get_pdr_data_from_mcu(const pkt_header_t *head)
{
    flp_data_buf_t *pdata;
    flp_port_t *flp_port ;
    struct list_head    *pos;
    flp_pdr_data_t *data = (flp_pdr_data_t *) (head + 1);
    flp_pdr_data_t *pevent;
    flp_pdr_data_t *pinsert;
    unsigned int len = head->length;
    unsigned int count;
    unsigned int j;

    flp_hex_dump((char *)data, len, sizeof(flp_pdr_data_t));

    /*check data lenghth is valid*/
    if (len%(sizeof(flp_pdr_data_t))) {
        printk(KERN_ERR "pkt len[%d] error\n", head->length);
        return -EFAULT;
    }

    /*no port be opened ,just discard data*/
    if (list_empty(&g_flp_dev.list)) {
        printk(KERN_ERR "flp pdr no port be opened\n");
        return -EFAULT;
    }

    count = len/(sizeof(flp_pdr_data_t));
    pevent = data;
    /*start first time, get utc of start cmd */
    if (!g_flp_dev.pdr_last_utc) {
        /*lint -e647 -esym(647,*) */
        g_flp_dev.pdr_last_utc = ktime_get_real_seconds() - g_flp_dev.pdr_config.report_count * (g_flp_dev.pdr_cycle/1000);
        /*lint +e647 +esym(647,*) */
        FLP_DEBUG("flputc--first [%ld]\n", g_flp_dev.pdr_last_utc);
    }
    /*for support multi port,transfer one times; timer continue in one fifo transfer*/
    for (j = 0; j < count; j++) {
        pevent = data + j;
        g_flp_dev.pdr_last_utc += g_flp_dev.pdr_cycle/1000;
        FLP_DEBUG("flputc[%ld]: %ld\n", g_flp_dev.pdr_last_utc, pevent->msec);
        pevent->msec = (unsigned long)g_flp_dev.pdr_last_utc;
#if SAVE_PDR_DATA_TO_FTRACE
        trace_flp_pdr_event(pevent->relative_position_x, pevent->relative_position_y);
#endif
    }
    if ((j == count) && (count < PDR_SINGLE_SEND_COUNT)) {
        g_flp_dev.pdr_last_utc = ktime_get_real_seconds();
    }
    /*record last packet*/
    if(count > 0) {
        g_flp_dev.pdr_compensate.compensate_step = pevent->step_count;
        g_flp_dev.pdr_compensate.compensate_position_x = pevent->relative_position_x;
        g_flp_dev.pdr_compensate.compensate_position_y = pevent->relative_position_y;
        g_flp_dev.pdr_compensate.compensate_distance = pevent->migration_distance;
    }

#if SAVE_PDR_DATA_TO_FILE
    save_pdr_data_to_file(data, count);
#endif
    printk(HISI_FLP_DEBUG "flp:recv pkt len[%d]\n", len);

    mutex_lock(&g_flp_dev.lock);
    /*pick up data from inputhub buf*/
    list_for_each(pos, &g_flp_dev.list) {
        flp_port = container_of(pos, flp_port_t, list);
        if (!(flp_port->channel_type&FLP_PDR_DATA)) {
            continue ;
        }
        /* if start pdr ever,just discard history data*/
        if ((FLP_IOCTL_PDR_START(0) == g_flp_dev.pdr_flush_config) &&
            (flp_port->pdr_flush_config)) {
            if (count < PDR_SINGLE_SEND_COUNT) {
                flp_port->pdr_flush_config = 0;
                memcpy(&flp_port->pdr_compensate, &g_flp_dev.pdr_compensate,
                    sizeof(compensate_data_t));
            }
            continue ;
        }
        pdata = &flp_port->pdr_buf ;
        mutex_lock(&pdata->data_mutex);
        while (flp_port->nextid < count) {
            pevent = data + flp_port->nextid;
            pinsert = (flp_pdr_data_t *)(pdata->data_buf + pdata->write_index);
            copy_data_to_buf(pdata, (char *)pevent,
                sizeof(flp_pdr_data_t), sizeof(flp_pdr_data_t));
            /*as multi port scene, need subtract original point*/
            if (flp_port->pdr_compensate.compensate_position_x ||
                flp_port->pdr_compensate.compensate_position_y ||
                flp_port->pdr_compensate.compensate_step) {
                pinsert->step_count -= flp_port->pdr_compensate.compensate_step;
                pinsert->relative_position_x -= flp_port->pdr_compensate.compensate_position_x;
                pinsert->relative_position_y -= flp_port->pdr_compensate.compensate_position_y;
                pinsert->migration_distance -= flp_port->pdr_compensate.compensate_distance;
            }
            flp_port->total_count++ ;
            flp_port->aquiredid++ ;
            if ((flp_port->interval ==  flp_port->pdr_config.report_count) ||
                (flp_port->aquiredid%flp_port->pdr_config.report_count)) {
                flp_port->nextid += flp_port->rate;
            } else {
                flp_port->nextid += flp_port->interval - (flp_port->pdr_config.report_count - 1) * flp_port->rate;
            }
        }
        flp_port->aquiredid = flp_port->aquiredid%flp_port->pdr_config.report_count;
        flp_port->nextid -= count ;
        /*if up to report condition , send packet to hal layer*/
        if ((0 == flp_port->total_count%flp_port->pdr_config.report_count) ||
            (flp_port->pdr_buf.data_count >=
            flp_port->pdr_config.report_count*sizeof(flp_pdr_data_t))) {
            flp_generate_netlink_packet(flp_port, pdata->data_buf,
                    pdata->data_count, FLP_GENL_CMD_PDR_DATA);
        }
        /*check if need update pickup parameter or not*/
        if ((g_flp_dev.pdr_flush_config) && (count < PDR_SINGLE_SEND_COUNT)) {
            if ((FLP_IOCTL_PDR_UPDATE(0) == g_flp_dev.pdr_flush_config) && (flp_port->pdr_flush_config)) {
                memcpy(&flp_port->pdr_config, &flp_port->pdr_update_config,
                    sizeof(pdr_start_config_t));
                flp_port->nextid = 0;
                flp_port->aquiredid = 0;
                flp_port->total_count = 0 ;
            } else {
                flp_port->nextid *=  (flp_port->pdr_config.report_precise/g_flp_dev.pdr_config.report_precise)/flp_port->rate;
            }
            flp_port->rate = flp_port->pdr_config.report_precise/g_flp_dev.pdr_config.report_precise ;
            flp_port->interval = flp_port->pdr_config.report_interval/g_flp_dev.pdr_config.report_precise ;
            /*as send update or flush command to the port, send the received packets immediately*/
            if (((FLP_IOCTL_PDR_UPDATE(0) == g_flp_dev.pdr_flush_config) ||
                (FLP_IOCTL_PDR_FLUSH(0) == g_flp_dev.pdr_flush_config)) &&
                (flp_port->pdr_flush_config)) {
                flp_port->pdr_flush_config = 0;
                flp_generate_netlink_packet(flp_port, pdata->data_buf,
                    pdata->data_count, FLP_GENL_CMD_PDR_DATA);
            }
        }
        mutex_unlock(&pdata->data_mutex);
        printk(HISI_FLP_DEBUG "flp:%s port_type:%d: len:%d,%d\n", __func__,
                                        flp_port->port_type, flp_port->pdr_config.report_count, flp_port->pdr_buf.data_count);
    }
    /*short package indecate history date sending complete*/
    if ((g_flp_dev.pdr_flush_config) && (count < PDR_SINGLE_SEND_COUNT)) {
        g_flp_dev.pdr_flush_config = 0;
        g_flp_dev.pdr_cycle = g_flp_dev.pdr_config.report_precise;
    }
    mutex_unlock(&g_flp_dev.lock);
    return len;
}

static int get_ar_data_from_mcu(const pkt_header_t *head)
{
    flp_data_buf_t *pdata;
    flp_port_t *flp_port;
    struct list_head    *pos;
    ar_activity_event_t *data = (ar_activity_event_t  *) (head + 1);
    ar_activity_event_t *pevent;
    unsigned int j;
    unsigned int len = head->length;
    unsigned int count;
    unsigned long latest_tick;
    unsigned long event_tick;
    unsigned long nsec;

    printk(HISI_FLP_DEBUG "flp:%s %d: len[%d]\n", __func__, __LINE__, len);

    flp_hex_dump((char *)data, len, sizeof(ar_activity_event_t));

    /*check data lenghth is valid*/
    if (len%(sizeof(ar_activity_event_t))) {
        printk(KERN_ERR "pkt len[%d] error\n", head->length);
        return -EFAULT;
    }

    /*no port be opened ,just discard data*/
    if (list_empty(&g_flp_dev.list)) {
        printk(KERN_ERR "flp pdr no port be opened\n");
        return -EFAULT;
    }
    g_flp_dev.ar_current_state = AR_STATE_BUTT;
    count = len/(sizeof(ar_activity_event_t));

    /*for support multi port,transfer one times*/
    if (count > 0) {
        pevent = data + count - 1 ;
        latest_tick = pevent->msec;
        nsec = ktime_get_boot_ns();
        for (j = 0; j < count; j++) {
            pevent = data + j ;
            event_tick = pevent->msec;
            /*one tick = 1 ms, transfer to nanosecond*/
            pevent->msec = nsec - (latest_tick - event_tick) * 1000000;
        #if SAVE_PDR_DATA_TO_FTRACE
            trace_flp_ar_event(pevent->event_type, pevent->activity);
        #endif
            FLP_DEBUG("flp event_type: %d activity:%d tick:%ld nsec:%ld\n", pevent->event_type, pevent->activity,
                event_tick, pevent->msec);
        }
        if (pevent->event_type == AR_STATE_ENTER) {
            g_flp_dev.ar_current_state = pevent->activity ;
        }
    }

    mutex_lock(&g_flp_dev.lock);
    /*pick up data from inputhub buf*/
    list_for_each(pos, &g_flp_dev.list) {
        flp_port = container_of(pos, flp_port_t, list);
        /*this port isnot started,or call stop function*/
        if (!(flp_port->channel_type&FLP_AR_DATA)) {
            continue ;
        }

        pdata = &flp_port->ar_buf ;
        mutex_lock(&pdata->data_mutex);
        for (j = 0; j < count; j++) {
            pevent = data + j ;
            if ((flp_port->ar_config.activity_list[pevent->activity].event_type) &&
                ((flp_port->ar_config.activity_list[pevent->activity].event_type)&pevent->event_type)) {
                copy_data_to_buf(pdata, (char *)pevent,
                    (unsigned int)sizeof(ar_activity_event_t), (unsigned int)sizeof(ar_activity_event_t));
            }
            if ((FLP_IOCTL_AR_FLUSH(0) == flp_port->ar_current_cmd) && (!pevent->event_type)) {
                flp_port->ar_current_cmd = 0;
                copy_data_to_buf(pdata, (char *)pevent,
                    (unsigned int)sizeof(ar_activity_event_t), (unsigned int)sizeof(ar_activity_event_t));
            }
        }
        flp_generate_netlink_packet(flp_port, pdata->data_buf,
            pdata->data_count, FLP_GENL_CMD_AR_DATA);
        mutex_unlock(&pdata->data_mutex);
        printk(HISI_FLP_DEBUG "flp:%s %d: len:%d\n", __func__,
            flp_port->port_type, flp_port->ar_buf.data_count);
    }
    mutex_unlock(&g_flp_dev.lock);
    return len;
}

void show_flp_struct (void)
{
    flp_port_t *flp_port ;
    struct list_head    *pos;
    unsigned int count;
    if (list_empty(&g_flp_dev.list)) {
        printk(KERN_ERR "flp pdr no port be opened\n");
        return ;
    }
    printk(KERN_ERR "flp overall config\n");
    printk(KERN_ERR "interval:%d,precise:%d,count:%d\n", g_flp_dev.pdr_config.report_interval,
                g_flp_dev.pdr_config.report_precise, g_flp_dev.pdr_config.report_count);
    for (count = 0; count < AR_STATE_BUTT; count++) {
        printk(KERN_ERR "event_type[%d],activity[%d]\n",
                        g_flp_dev.ar_config.activity_list[count].event_type,
                        g_flp_dev.ar_config.activity_list[count].activity);
    }
    printk(KERN_ERR "flp port config\n");
    list_for_each(pos, &g_flp_dev.list) {
        flp_port = container_of(pos, flp_port_t, list);
        printk(KERN_ERR "flp port type [%d] channel_type [%d]\n",
            flp_port->port_type, flp_port->channel_type);
        if (flp_port->port_type & FLP_TAG_AR) {
            for (count = 0; count < AR_STATE_BUTT; count++) {
                printk(KERN_ERR "event_type[%d],activity[%d]\n",
                                flp_port->ar_config.activity_list[count].event_type,
                                flp_port->ar_config.activity_list[count].activity);
            }
        } else {
            printk(KERN_ERR "interval:%d,precise:%d,count:%d\n", flp_port->pdr_config.report_interval,
                flp_port->pdr_config.report_precise, flp_port->pdr_config.report_count);
        }
    }
}

void flp_netlink_send_packet (void)
{
    flp_port_t *flp_port;
    flp_pdr_data_t packet;
    struct list_head    *pos;

    if (list_empty(&g_flp_dev.list)) {
        printk(KERN_ERR "flp pdr no port be opened\n");
        return ;
    }
    list_for_each(pos, &g_flp_dev.list) {
        flp_port = container_of(pos, flp_port_t, list);
        printk(KERN_ERR "flp port type [%d] channel_type [%d]\n",
            flp_port->port_type, flp_port->channel_type);
        printk(KERN_ERR "send packet by netlink\n");
        memset(&packet, 0xaa, sizeof(flp_pdr_data_t));
        flp_generate_netlink_packet(flp_port, (char *)&packet,
            sizeof(flp_pdr_data_t), 0);
    }
}


static void  flp_service_recovery(void)
{
    flp_port_t *flp_port;
    unsigned int flag = 0;
    struct list_head    *pos;
    list_for_each(pos, &g_flp_dev.list) {
        flp_port = container_of(pos, flp_port_t, list);
        if ((flp_port->channel_type&FLP_PDR_DATA) &&
            !(flag & FLP_PDR_DATA)) {
            send_cmd_from_kernel_nolock(TAG_PDR, CMD_CMN_OPEN_REQ, 0, NULL, 0);
            send_cmd_from_kernel_nolock(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_START_REQ,
                    (char *)&g_flp_dev.pdr_config, sizeof(pdr_start_config_t));
            flag |= FLP_PDR_DATA;
        }
        if ((flp_port->channel_type & FLP_AR_DATA) &&
            !(flag & FLP_AR_DATA)) {
            send_cmd_from_kernel_nolock(TAG_AR, CMD_CMN_OPEN_REQ, 0, NULL, 0);
            send_cmd_from_kernel_nolock(TAG_AR, CMD_CMN_CONFIG_REQ, CMD_FLP_AR_START_REQ,
                (char *)&g_flp_dev.ar_mcu_config + sizeof(unsigned int),
                g_flp_dev.ar_mcu_config.event_num * sizeof(ar_activity_config_t) + sizeof(unsigned int));
            flag |= FLP_AR_DATA;
        }
    }
    return ;
}

static int flp_notifier(struct notifier_block *nb,
            unsigned long action, void *data)
{
    switch (action) {
        case IOM3_RECOVERY_3RD_DOING:
            flp_service_recovery();
            break;
        default:
            printk(KERN_ERR "register_iom3_recovery_notifier err\n");
            break;
    }
    return 0;
}
extern int register_iom3_recovery_notifier(struct notifier_block *nb);
static struct notifier_block sensor_reboot_notify = {
    .notifier_call = flp_notifier,
    .priority = -1,
};

static void flp_timerout_work(struct work_struct *wk)
{
    flp_port_t *flp_port  = container_of(wk, flp_port_t, work);
    flp_generate_netlink_packet(flp_port, NULL, 0, (unsigned char)flp_port->work_para);
}
static void flp_sleep_timeout(unsigned long data)
{
    flp_port_t *flp_port = (flp_port_t *)data;
    printk(KERN_INFO "flp_sleep_timeout \n");
    if (flp_port) {
        flp_port->work_para = FLP_GENL_CMD_NOTIFY_TIMEROUT;
        queue_work(system_power_efficient_wq, &flp_port->work);
        if (flp_port->need_hold_wlock) {
            wake_lock_timeout(&flp_port->wlock, (long)(2 * HZ));
        }
    }
    return ;
}
void flp_port_resume(void)
{
    struct list_head    *pos;
    flp_port_t      *flp_port;

    mutex_lock(&g_flp_dev.lock);
    list_for_each(pos, &g_flp_dev.list) {
        flp_port = container_of(pos, flp_port_t, list);
        if (flp_port->need_awake) {
            flp_port->work_para = FLP_GENL_CMD_AWAKE_RET;
            queue_work(system_power_efficient_wq, &flp_port->work);
        }
    }
    mutex_unlock(&g_flp_dev.lock);
}

static int flp_set_port_tag(flp_port_t *flp_port, unsigned int cmd)
{
    switch (cmd & FLP_IOCTL_TAG_MASK) {
        case FLP_IOCTL_TAG_FLP:
            flp_port->port_type = FLP_TAG_FLP ;
            break ;
        case FLP_IOCTL_TAG_GPS:
            flp_port->port_type = FLP_TAG_GPS ;
            break ;
        case FLP_IOCTL_TAG_AR:
            flp_port->port_type = FLP_TAG_AR ;
            break ;
        default:
            return -EFAULT;
    }
	return 0 ;
}

static bool flp_check_cmd(int cmd, int type)
{
    switch (type) {
        case FLP_PDR_DATA:
            if (((cmd & FLP_IOCTL_TAG_MASK) == FLP_IOCTL_TAG_FLP) ||
                ((cmd & FLP_IOCTL_TAG_MASK) == FLP_IOCTL_TAG_GPS)) {
                return TRUE;
            }
            break ;
        case FLP_AR_DATA:
            if (((cmd & FLP_IOCTL_TAG_MASK) == FLP_IOCTL_TAG_FLP) ||
                ((cmd & FLP_IOCTL_TAG_MASK) == FLP_IOCTL_TAG_GPS) ||
                ((cmd & FLP_IOCTL_TAG_MASK) == FLP_IOCTL_TAG_AR)) {
                return TRUE;
            }
            break ;
        default :
            break ;
    }
    return 0;
}

static int flp_pdr_ioctl(flp_port_t *flp_port, unsigned int cmd, unsigned long arg)
{
    unsigned int data;
    buf_info_t para;
    int ret = 0;

    if (!flp_check_cmd(cmd, FLP_PDR_DATA))
        return -EPERM;

    switch (cmd & FLP_IOCTL_CMD_MASK) {
        case FLP_IOCTL_PDR_START(0):
            flp_set_port_tag(flp_port, cmd);

            if (flp_port->pdr_buf.data_buf) {
                printk(KERN_ERR "Restart is not permit \n");
                return -EPERM;
            }
            flp_port->total_count = 0;
            flp_port->pdr_buf.buf_size = sizeof(flp_pdr_data_t) * PDR_DATA_MAX_COUNT * 2;
            flp_port->pdr_buf.read_index = 0 ;
            flp_port->pdr_buf.write_index = 0;
            flp_port->pdr_buf.data_count = 0;
            flp_port->pdr_buf.data_buf = (char *) kmalloc(flp_port->pdr_buf.buf_size, GFP_KERNEL);
            if (!flp_port->pdr_buf.data_buf) {
                printk(KERN_ERR "flp_open no mem\n");
                return -ENOMEM;
            }
            mutex_init(&flp_port->pdr_buf.data_mutex);
            init_waitqueue_head(&flp_port->pdr_buf.pollq);
            mutex_lock(&g_flp_dev.lock);
            if (!g_flp_dev.pdr_start_count) {
                g_flp_dev.pdr_last_utc = 0;
            }
            flp_pdr_start_cmd(flp_port, (char __user *)arg, sizeof(pdr_start_config_t));
            mutex_unlock(&g_flp_dev.lock);
            break ;

        case FLP_IOCTL_PDR_STOP(0):
            if (!flp_port->pdr_buf.data_buf) {
                printk(KERN_ERR "Repeat stop is not permit \n");
                return -EPERM;
            }
            if (copy_from_user(&data, (void *)arg, sizeof(unsigned int))) {
                printk(KERN_ERR "flp_ioctl copy_from_user error\n");
                return -EFAULT;
            }
            printk(HISI_FLP_DEBUG "flp_ioctl copy_from_user data[%d]\n", data);
            mutex_lock(&g_flp_dev.lock);
            flp_stop_cmd(flp_port, data, FLP_PDR_DATA);
            kfree(flp_port->pdr_buf.data_buf);
            flp_port->pdr_buf.data_buf = NULL;
            mutex_unlock(&g_flp_dev.lock);
            break ;
        case FLP_IOCTL_PDR_WRITE(0):
            if (copy_from_user(&para, (void *)arg, sizeof(buf_info_t))) {
                printk(KERN_ERR "flp_ioctl copy_from_user error\n");
                return -EFAULT;
            }

            return pdr_write_cmd(flp_port, para.buf, para.len);
        case FLP_IOCTL_PDR_READ(0):
            if (copy_from_user(&para, (void *)arg, sizeof(buf_info_t))) {
                printk(KERN_ERR "flp_ioctl copy_from_user error\n");
                return -EFAULT;
            }
            return flp_read_cmd(flp_port, (char __user *)para.buf, para.len, FLP_PDR_DATA);

        case FLP_IOCTL_PDR_UPDATE(0):
            mutex_lock(&g_flp_dev.lock);
            ret = flp_pdr_update_cmd(flp_port, (char __user *)arg, sizeof(pdr_start_config_t));
            mutex_unlock(&g_flp_dev.lock);
            break ;

        case FLP_IOCTL_PDR_FLUSH(0):
            mutex_lock(&g_flp_dev.lock);
            g_flp_dev.pdr_flush_config = FLP_IOCTL_PDR_FLUSH(0);
            flp_port->pdr_flush_config = TRUE;
            mutex_unlock(&g_flp_dev.lock);
            ret = send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ,
                CMD_FLP_PDR_FLUSH_REQ, NULL, 0);
            break ;
        case FLP_IOCTL_PDR_STEP_CFG(0):
            flp_port->need_report = TRUE;
            ret = send_cmd_from_user(TAG_PDR, CMD_CMN_CONFIG_REQ,
                CMD_FLP_PDR_STEPCFG_REQ, (char __user *)arg, sizeof(step_report_t));
            break ;
        default:
            printk(KERN_ERR "flp_pdr_ioctl input cmd[0x%x] error\n", cmd);
            return -EFAULT;
    }

    return ret;
}

static int flp_ar_ioctl(flp_port_t *flp_port, unsigned int cmd, unsigned long arg)
{
    unsigned int data;
    buf_info_t para;
    int ret = 0;

    if (!flp_check_cmd(cmd, FLP_AR_DATA))
        return -EPERM;
    flp_port->ar_current_cmd = cmd & FLP_IOCTL_CMD_MASK;
    switch (cmd & FLP_IOCTL_CMD_MASK) {
        case FLP_IOCTL_AR_START(0):
            flp_set_port_tag(flp_port, cmd);

            if (flp_port->ar_buf.data_buf) {
                printk(KERN_ERR "Restart is not permit \n");
                return -EPERM;
            }

            flp_port->ar_buf.buf_size = sizeof(ar_activity_event_t)<<10;
            flp_port->ar_buf.read_index = 0 ;
            flp_port->ar_buf.write_index = 0;
            flp_port->ar_buf.data_count = 0;
            flp_port->ar_buf.data_buf = (char *)kmalloc(flp_port->ar_buf.buf_size, GFP_KERNEL);
            if (!flp_port->ar_buf.data_buf) {
                printk(KERN_ERR "flp_open no mem\n");
                return -ENOMEM;
            }
            mutex_init(&flp_port->ar_buf.data_mutex);
            init_waitqueue_head(&flp_port->ar_buf.pollq);
            mutex_lock(&g_flp_dev.lock);
            flp_ar_start_cmd(flp_port, (char __user *)arg, sizeof(ar_start_hal_config_t));
            mutex_unlock(&g_flp_dev.lock);
            break ;

        case FLP_IOCTL_AR_STOP(0):
            if (!flp_port->ar_buf.data_buf) {
                printk(KERN_ERR "Repeat stop is not permit \n");
                return -EPERM;
            }
            if (copy_from_user(&data, (void *)arg, sizeof(unsigned int))) {
                printk(KERN_ERR "flp_ioctl copy_from_user error\n");
                return -EFAULT;
            }
            printk(HISI_FLP_DEBUG "flp_ioctl copy_from_user data[%d]\n", data);

            mutex_lock(&g_flp_dev.lock);
            flp_stop_cmd(flp_port, data, FLP_AR_DATA);
            kfree(flp_port->ar_buf.data_buf);
            flp_port->ar_buf.data_buf = NULL;
            mutex_unlock(&g_flp_dev.lock);
            break ;

        case FLP_IOCTL_AR_READ(0):
            if (copy_from_user(&para, (void *)arg, sizeof(buf_info_t))) {
                printk(KERN_ERR "flp_ioctl copy_from_user error\n");
                return -EFAULT;
            }
            return flp_read_cmd(flp_port, (char __user *)para.buf, para.len, FLP_AR_DATA);

        case FLP_IOCTL_AR_UPDATE(0):
            mutex_lock(&g_flp_dev.lock);
            ret = flp_ar_update_cmd(flp_port, (char __user *)arg, sizeof(ar_start_hal_config_t));
            mutex_unlock(&g_flp_dev.lock);
            break ;

        case FLP_IOCTL_AR_FLUSH(0):
            ret = send_cmd_from_kernel(TAG_AR, CMD_CMN_CONFIG_REQ,
                CMD_FLP_AR_FLUSH_REQ, NULL, 0);
            break ;
        case FLP_IOCTL_AR_STATE(0):
            if (copy_to_user((void *)arg, &g_flp_dev.ar_current_state, sizeof(unsigned int))) {
                printk(KERN_ERR "flp_ioctl copy_from_user error\n");
                return -EFAULT;
            }
            break ;
        default:
            printk(KERN_ERR "flp_ar_ioctrl input cmd[0x%x] error\n", cmd);
            return -EFAULT;
    }

    return ret;
}

static int flp_common_ioctl(flp_port_t *flp_port, unsigned int cmd, unsigned long arg)
{
    unsigned int data;
    long ret = 0;

    switch (cmd) {
        case FLP_IOCTL_COMMON_SLEEP:
            if (copy_from_user(&data, (void *)arg, sizeof(unsigned int))) {
                printk(KERN_ERR "flp_ioctl copy_from_user error[%ld]\n", ret);
                return -EFAULT;
            }
            printk(HISI_FLP_DEBUG "flp:start timer %d\n",  data);
            /*if timer is running just delete it ,then restart it*/
            hisi_softtimer_delete(&flp_port->sleep_timer);
            ret = hisi_softtimer_modify(&flp_port->sleep_timer, data);
            if (!ret)
                hisi_softtimer_add(&flp_port->sleep_timer);
            break ;

        case FLP_IOCTL_COMMON_AWAKE_RET:
            if (copy_from_user(&flp_port->need_awake, (void *)arg, sizeof(unsigned int))) {
                printk(KERN_ERR " copy_from_user error[%ld]\n", ret);
                return -EFAULT;
            }

            break ;
        case FLP_IOCTL_COMMON_SETPID:
            if (copy_from_user(&flp_port->portid, (void *)arg, sizeof(unsigned int))) {
                printk(KERN_ERR "flp_ioctl FLP_IOCTL_PDR_SETPID  error[%ld]\n", ret);
                return -EFAULT;
            }
            break ;
        case FLP_IOCTL_COMMON_CLOSE_SERVICE:
            if (copy_from_user(&g_flp_dev.denial_sevice, (void *)arg, sizeof(unsigned int))) {
                printk(KERN_ERR "flp_ioctl FLP_IOCTL_PDR_SETPID  error[%ld]\n", ret);
                return -EFAULT;
            }
            printk(HISI_FLP_DEBUG "%s 0x%x\n", __func__, g_flp_dev.denial_sevice);
            if (g_flp_dev.denial_sevice) {
                data = 0;
                if ((g_flp_dev.service_type & FLP_AR_DATA) && (g_flp_dev.ar_start_count)) {
                    send_cmd_from_kernel(TAG_AR, CMD_CMN_CONFIG_REQ, CMD_FLP_AR_STOP_REQ,
                        (char *)&data, sizeof(int));
                    send_cmd_from_kernel(TAG_AR, CMD_CMN_CLOSE_REQ, 0, NULL, 0);
                    g_flp_dev.ar_current_state = AR_STATE_BUTT;
                }
                /*if start pdr function ever*/
                if ((g_flp_dev.service_type & FLP_PDR_DATA) &&
                        (g_flp_dev.pdr_start_count)) {
                    send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ,
                        CMD_FLP_PDR_STOP_REQ, (char *)&data, sizeof(int));
                    send_cmd_from_kernel(TAG_PDR, CMD_CMN_CLOSE_REQ, 0, NULL, 0);
                }
            } else {
                if ((g_flp_dev.service_type & FLP_AR_DATA) && (g_flp_dev.ar_start_count)) {
                    send_cmd_from_kernel(TAG_AR, CMD_CMN_OPEN_REQ, 0, NULL, 0);
                    send_cmd_from_kernel(TAG_AR, CMD_CMN_CONFIG_REQ, CMD_FLP_AR_START_REQ,
                        (char *)&g_flp_dev.ar_mcu_config + sizeof(unsigned int),
                        g_flp_dev.ar_mcu_config.event_num * sizeof(ar_activity_config_t) + sizeof(unsigned int));
                }
                /*if start pdr function ever*/
                if ((g_flp_dev.service_type & FLP_PDR_DATA) &&
                        (g_flp_dev.pdr_start_count)) {
                    send_cmd_from_kernel(TAG_PDR, CMD_CMN_OPEN_REQ, 0, NULL, 0);
                    send_cmd_from_kernel(TAG_PDR, CMD_CMN_CONFIG_REQ, CMD_FLP_PDR_START_REQ,
                        (char *)&g_flp_dev.pdr_config, sizeof(pdr_start_config_t));
                }
            }
            break ;
        case FLP_IOCTL_COMMON_HOLD_WAKELOCK:
            if (copy_from_user(&data, (void *)arg, sizeof(unsigned int))) {
                printk(KERN_ERR "flp_ioctl copy_from_user error[%ld]\n", ret);
                return -EFAULT;
            }
            flp_port->need_hold_wlock = data;
            printk(HISI_FLP_DEBUG "%s 0x%x\n", __func__, flp_port->need_hold_wlock);
            break ;
        case FLP_IOCTL_COMMON_RELEASE_WAKELOCK:
            if (flp_port->need_hold_wlock) {
                wake_unlock(&flp_port->wlock);
            }
            break;
        default:
            printk(KERN_ERR "flp_common_ioctl input cmd[0x%x] error\n", cmd);
            return -EFAULT;
    }
    return 0;
}

static long flp_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    flp_port_t *flp_port  = (flp_port_t *)file->private_data;
    if (!flp_port) {
        printk(KERN_ERR "flp_ioctl parameter error\n");
        return -EINVAL;
    }
    printk(HISI_FLP_DEBUG "%s 0x%x\n", __func__, cmd);
    if ((g_flp_dev.denial_sevice) && (cmd != FLP_IOCTL_COMMON_CLOSE_SERVICE)) {
        return 0;
    }
    switch (cmd & FLP_IOCTL_TYPE_MASK) {
        case FLP_IOCTL_TYPE_PDR:
            return (long)flp_pdr_ioctl(flp_port, cmd, arg);
        case FLP_IOCTL_TYPE_AR:
            return (long)flp_ar_ioctl(flp_port, cmd, arg);
        case FLP_IOCTL_TYPE_COMMON:
            return (long)flp_common_ioctl(flp_port, cmd, arg);
        default:
            printk(KERN_ERR "flp_ioctl input cmd[0x%x] error\n", cmd);
            return -EFAULT;
    }
    return 0 ;
}

static int flp_open(struct inode *inode, struct file *filp)
{
    flp_port_t *flp_port ;
    flp_port  = (flp_port_t *) kmalloc(sizeof(flp_port_t), GFP_KERNEL|__GFP_ZERO);
    if (!flp_port) {
        printk(KERN_ERR "flp_open no mem\n");
        return -ENOMEM;
    }
    INIT_LIST_HEAD(&flp_port->list);
    hisi_softtimer_create(&flp_port->sleep_timer,
                            flp_sleep_timeout, (unsigned long)flp_port, 0);
    INIT_WORK(&flp_port->work, flp_timerout_work);
    mutex_lock(&g_flp_dev.lock);
    list_add_tail(&flp_port->list, &g_flp_dev.list);
    mutex_unlock(&g_flp_dev.lock);
    wake_lock_init(&flp_port->wlock, WAKE_LOCK_SUSPEND, "hisi_flp");
    filp->private_data = flp_port;
    printk(KERN_ERR "%s %d: enter\n", __func__, __LINE__);
    return 0;
}

static int flp_release(struct inode *inode, struct file *file)
{
    flp_port_t *flp_port  = (flp_port_t *)file->private_data;
    struct list_head    *pos;
    flp_port_t      *port;

    if (!flp_port) {
        printk(KERN_ERR "flp_close parameter error\n");
        return -EINVAL;
    }
    hisi_softtimer_delete(&flp_port->sleep_timer);
    cancel_work_sync(&flp_port->work);
    if ((flp_port->channel_type & FLP_PDR_DATA) && (0 == flp_port->portid)) {
        flp_port->pdr_buf.data_count = 0;
        flp_port->pdr_buf.to_wait = false;
        wake_up_interruptible(&flp_port->pdr_buf.pollq);
    }
    if ((flp_port->channel_type & FLP_AR_DATA) && (0 == flp_port->portid)) {
        flp_port->ar_buf.data_count = 0;
        flp_port->ar_buf.to_wait = false;
        wake_up_interruptible(&flp_port->ar_buf.pollq);
    }
    wake_lock_destroy(&flp_port->wlock);
    mutex_lock(&g_flp_dev.lock);
    list_del(&flp_port->list);
    /*if andriod vm restart, apk doesnot send stop cmd,just adjust it*/
    g_flp_dev.ar_start_count = 0 ;
    g_flp_dev.pdr_start_count = 0;
    list_for_each(pos, &g_flp_dev.list) {
        port = container_of(pos, flp_port_t, list);
        if (port->channel_type & FLP_AR_DATA) {
                g_flp_dev.ar_start_count++ ;
        }
        if (port->channel_type & FLP_PDR_DATA) {
            g_flp_dev.pdr_start_count++ ;
        }
    }
    /*if start ar function ever*/
    if ((g_flp_dev.service_type & FLP_AR_DATA) && (!g_flp_dev.ar_start_count)) {
        send_cmd_from_kernel(TAG_AR, CMD_CMN_CLOSE_REQ, 0, NULL, 0);
        g_flp_dev.service_type &= ~FLP_AR_DATA;
        g_flp_dev.ar_current_state = AR_STATE_BUTT;
    }
    /*if start pdr function ever*/
    if ((g_flp_dev.service_type & FLP_PDR_DATA) &&
            (!g_flp_dev.pdr_start_count)) {
        send_cmd_from_kernel(TAG_PDR, CMD_CMN_CLOSE_REQ, 0, NULL, 0);
        g_flp_dev.service_type &= ~FLP_PDR_DATA;
    }
    if (flp_port->ar_buf.data_buf) {
        kfree(flp_port->ar_buf.data_buf);
        flp_port->ar_buf.data_buf = NULL;
    }
    if (flp_port->pdr_buf.data_buf) {
        kfree(flp_port->pdr_buf.data_buf);
        flp_port->pdr_buf.data_buf = NULL;
    }
    kfree(flp_port);

    mutex_unlock(&g_flp_dev.lock);

    file->private_data = NULL ;
    printk(KERN_ERR "%s %d:service_type [%d] \n", __func__, __LINE__, g_flp_dev.service_type);
    return 0;
}

static const struct file_operations hisi_flp_fops = {
    .owner =          THIS_MODULE,
    .llseek =         no_llseek,
    .unlocked_ioctl = flp_ioctl,
    .open       =     flp_open,
    .release    =     flp_release,
};

/*******************************************************************************************
Description:   miscdevice to motion
*******************************************************************************************/
static struct miscdevice hisi_flp_miscdev =
{
    .minor =    MISC_DYNAMIC_MINOR,
    .name =     "flp",
    .fops =     &hisi_flp_fops,
};


/*******************************************************************************************
Function:       hisi_flp_register
Description:
Data Accessed:  no
Data Updated:   no
Input:          void
Output:        void
Return:        result of function, 0 successed, else false
*******************************************************************************************/
int  hisi_flp_register(void)
{
    int ret;

    ret = genl_register_family(&flp_genl_family);
    if (ret) {
        return ret ;
    }
    if (!getSensorMcuMode()) {
        printk(KERN_ERR "cannot register hisi flp %d\n", __LINE__);
        genl_unregister_family(&flp_genl_family);
        return -ENODEV;
    }
    INIT_LIST_HEAD(&g_flp_dev.list);
    PDR_REGISTER_CALLBACK(TAG_PDR, CMD_FLP_PDR_DATA_REQ, get_pdr_data_from_mcu);
    PDR_REGISTER_CALLBACK(TAG_PDR, CMD_FLP_PDR_UNRELIABLE_REQ, get_pdr_notify_from_mcu);
    PDR_REGISTER_CALLBACK(TAG_AR, CMD_FLP_AR_DATA_REQ, get_ar_data_from_mcu);

    register_iom3_recovery_notifier(&sensor_reboot_notify);
    mutex_init(&g_flp_dev.lock);
    g_flp_dev.pdr_flush_config = 0;
    g_flp_dev.service_type = 0;
    g_flp_dev.ar_start_count = 0;
    g_flp_dev.pdr_start_count = 0;
    g_flp_dev.denial_sevice = 0;
    g_flp_dev.ar_current_state = AR_STATE_BUTT;
    g_flp_dev.pdr_cycle = 0;

    ret = misc_register(&hisi_flp_miscdev);
    if (ret != 0)    {
        printk(KERN_ERR "cannot register hisi flp err=%d\n", ret);
        goto err;
    }
    printk(KERN_ERR "hisi_flp_register success\n");
    return 0;
err:
    unregister_mcu_event_notifier(TAG_PDR, CMD_FLP_PDR_DATA_REQ, get_pdr_data_from_mcu);
    unregister_mcu_event_notifier(TAG_PDR, CMD_FLP_PDR_UNRELIABLE_REQ, get_pdr_notify_from_mcu);
    unregister_mcu_event_notifier(TAG_AR, CMD_FLP_AR_DATA_REQ, get_ar_data_from_mcu);
    genl_unregister_family(&flp_genl_family);

    return ret ;
}

EXPORT_SYMBOL_GPL(hisi_flp_register);


/*******************************************************************************************
Function:       hisi_flp_unregister
Description:
Data Accessed:  no
Data Updated:   no
Input:          void
Output:        void
Return:        void
*******************************************************************************************/
 int hisi_flp_unregister(void)
{
    int ret;

    unregister_mcu_event_notifier(TAG_PDR, CMD_FLP_PDR_DATA_REQ, get_pdr_data_from_mcu);
    unregister_mcu_event_notifier(TAG_PDR, CMD_FLP_PDR_UNRELIABLE_REQ, get_pdr_notify_from_mcu);
    unregister_mcu_event_notifier(TAG_AR, CMD_FLP_AR_DATA_REQ, get_ar_data_from_mcu);
    genl_unregister_family(&flp_genl_family);

    ret = misc_deregister(&hisi_flp_miscdev);

    printk(HISI_FLP_DEBUG "hisi_flp_unregister ret=%d\n", ret);
    return ret;
}
EXPORT_SYMBOL_GPL(hisi_flp_unregister);

MODULE_AUTHOR("hisiflp <hisi@huawei.com>");
MODULE_DESCRIPTION("Hisi flp driver");
MODULE_LICENSE("GPL");


