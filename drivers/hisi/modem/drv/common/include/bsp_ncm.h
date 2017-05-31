/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef __BSP_NCM_H__
#define __BSP_NCM_H__

#ifdef __cplusplus
extern "C" { /* allow C++ to use these headers */
#endif /* __cplusplus */

#include <linux/skbuff.h>

#include "mdrv_udi.h"

/* NCM�豸����ö��*/
typedef enum tagNCM_DEV_TYPE_E
{
    NCM_DEV_DATA_TYPE,      /* ����ͨ�����ͣ�PSʹ��*/
    NCM_DEV_CTRL_TYPE       /* ����ͨ����MSP����AT����ʹ��*/
}NCM_DEV_TYPE_E;

/*  �´��ϴ������ذ��ĸ���ͳ����Ϣ��
    �����͸�PC�������ȴ�PC�Ķ�ȡ,NCM_IOCTL_SET_PKT_STATICS�����ֶ�Ӧ�����ṹ*/
typedef struct tagNCM_IOCTL_PKT_STATISTICS_S
{
    unsigned int     u32TxOKCount;         /*���Ͱ���*/
    unsigned int     u32RxOKCount;         /*���հ���*/
    unsigned int     u32TxErrCount;        /*���ʹ���*/
    unsigned int     u32RxErrCount;        /*���մ���*/
    unsigned int     u32TxOverFlowCount;   /*�����������*/
    unsigned int     u32RxOverFlowCount;   /*�����������*/
    unsigned int     u32CurrentTx;         /*��������*/
    unsigned int     u32CurrentRx;         /*��������*/
} NCM_IOCTL_PKT_STATISTICS_S;

typedef struct tagNCM_PKT_INFO_S
{
    unsigned int u32PsRcvPktNum;              /* �հ��͵�PS�İ�����*/
    unsigned int u32RcvUnusedNum;             /* �հ�������PSҪ����������*/
    unsigned int u32NcmSendPktNum;            /* ��������*/
}NCM_PKT_INFO_S;


typedef struct ncm_vendor_ctx
{
    bool is_mbim_mode;              /* if mbim mode now */
    bool connect;
    NCM_IOCTL_CONNECTION_SPEED_S speed;
    struct completion notify_done;  /* notify completion */
    bool tx_task_run;               /* tx task run */
    struct task_struct *tx_task;    /* tx task */
    struct completion tx_task_stop; /* notify tx task stoped */
    struct sk_buff_head tx_frames;  /* hold tx frames from vendor */
    struct completion tx_kick;      /* kick tx task */
    void *ncm_priv;                 /* hold f_ncm */
    void *vendor_priv;              /* hold app_ctx */

    /* stat info */
    ulong stat_rx_total;
    ulong stat_rx_einval;
    ulong stat_tx_total;
    ulong stat_tx_cancel;
    ulong stat_tx_xmit;
    ulong stat_tx_xmit_fail;
    ulong stat_tx_post;
    ulong stat_tx_drop;
    ulong stat_tx_nochl;
    ulong stat_tx_nodev;
    ulong stat_notify_timeout;
}ncm_vendor_ctx_t;

#if defined(CONFIG_BALONG_NCM)
unsigned int bsp_ncm_open(NCM_DEV_TYPE_E enDevType, unsigned int pu32NcmDevId);
unsigned int bsp_ncm_write(unsigned int u32NcmDevId, void *pPktEncap, void *net_priv);
unsigned int bsp_ncm_ioctl(unsigned int u32NcmDevId, NCM_IOCTL_CMD_TYPE_E enNcmCmd, void *param);
unsigned int bsp_ncm_close(NCM_DEV_TYPE_E enDevType, unsigned int u32NcmDevId);
#else
static unsigned int bsp_ncm_open(NCM_DEV_TYPE_E enDevType, unsigned int pu32NcmDevId)
{
    return -1;
}
static unsigned int bsp_ncm_write(unsigned int u32NcmDevId, void *pPktEncap, void *net_priv)
{
    return -1;
}
static unsigned int bsp_ncm_ioctl(unsigned int u32NcmDevId, NCM_IOCTL_CMD_TYPE_E enNcmCmd, void *param)
{
    return -1;
}
static unsigned int bsp_ncm_close(NCM_DEV_TYPE_E enDevType, unsigned int u32NcmDevId)
{
    return -1;
}
#endif


#ifdef __cplusplus
} /* allow C++ to use these headers */
#endif /* __cplusplus */

#endif    /* End of __BSP_ACM_H__ */
