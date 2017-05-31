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

#ifndef __MDRV_ACORE_DPM_H__
#define __MDRV_ACORE_DPM_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_public.h"
#include <mdrv_pm_common.h>

typedef enum tagPWC_COMM_CHANNEL_E
{
	PWC_COMM_CHANNEL_0,
	PWC_COMM_CHANNEL_1,
    PWC_COMM_CHANNEL_2,
    PWC_COMM_CHANNEL_BUTT,
} PWC_COMM_CHANNEL_E;

typedef enum tagPWC_COMM_MODULE_E
{
    PWC_COMM_MODULE_PA,
    PWC_COMM_MODULE_RF,
    PWC_COMM_MODULE_ABB,
    PWC_COMM_MODULE_BBE16,

    PWC_COMM_MODULE_BBP_DRX,  /*W:1A,2A,2C,2D,3*/
    PWC_COMM_MODULE_BBP_DPA,  /*W:1B*/
    PWC_COMM_MODULE_BBP_MEM,  /*W:2B*/

    PWC_COMM_MODULE_BUTT,
}PWC_COMM_MODULE_E;

typedef enum pm_wake_src
{
    PM_WAKE_SRC_UART0 = 0, /*for acore at_uart*/
    PM_WAKE_SRC_SOCP ,     /*for acore sd_log*/
    PM_WAKE_SRC_DRX_TIMER, /*for ccore drx timer*/
    PM_WAKE_SRC_BUT,
}PM_WAKE_SRC_E;


typedef enum tagPWC_COMM_STATUS_E
{
    PWRCTRL_COMM_ON = 0x10,
    PWRCTRL_COMM_OFF = 0x20,
    PWC_COMM_STATUS_BUTT
}PWC_COMM_STATUS_E;

typedef void (*PWC_SLEEP_FUNCPTR)(void);
/******************************************************
 * *˯��ͶƱID ,��0��ʼ�����32��
 * *�漰ͶƱ�������Ҫ�ڴ����LOCK ID
 * *��ͬ���޸�wakelock_balong.c�е�debug_wakelock
 * *******************************************************/
typedef enum tagPWC_CLIENT_ID_E
{
    PWRCTRL_SLEEP_TLPS = 0x100,   /*MSP--fuxin*/
    PWRCTRL_SLEEP_PS_G0,        /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_W0,       /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_G1,        /*GU--ganlan*/
    PWRCTRL_SLEEP_PS_W1,       /*GU--ganlan*/
    PWRCTRL_SLEEP_FTM,           /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_FTM_1,       /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_NAS,           /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_NAS_1,       /*GU--zhangyizhan*/
    PWRCTRL_SLEEP_OAM,          /* LTE --yangzhi */
    PWRCTRL_SLEEP_SCI0,            /* LTE --yangzhi */
    PWRCTRL_SLEEP_SCI1,            /* LTE --yangzhi */
    PWRCTRL_SLEEP_DMA,             /* GU --jinguojun*/
    PWRCTRL_SLEEP_MEM,              /*drv,flash or emmc*/
    PWRCTRL_SLEEP_DSFLOW,          /* NAS --zhangyizhan */
    PWRCTRL_SLEEP_TEST,            /* PM  ---shangmianyou */
    PWRCTRL_SLEEP_UART0,        /*UART0 -zhangliangdong */
    PWRCTRL_SLEEP_TDS,         /*TRRC&TL2----leixiantiao*/

    PWRCTRL_SLEEP_CDMAUART,         /*drv cdma uart ����*/
    PWRCTRL_SLEEP_USIM,             /*oam*/
    /*���²��ֵ�ID�Ѿ���ʹ���ˣ����ڻ�ɾ��*/
    PWRCTRL_SLEEP_RNIC,
    PWRCTRL_TEST_DEEPSLEEP  = 0x11f,
    LOCK_ID_BOTTOM =0x120
}PWC_CLIENT_ID_E;
typedef enum
{
    DFS_PROFILE_0 = 0,            /*Ƶ�ʼ���1*/
    DFS_PROFILE_1 = 1,            /*Ƶ�ʼ���2*/
    DFS_PROFILE_2 = 2,            /*Ƶ�ʼ���3*/
    DFS_PROFILE_3 = 3,            /*Ƶ�ʼ���4*/
    DFS_PROFILE_4 = 4,            /*Ƶ�ʼ���5*/
    DFS_PROFILE_BUTT
} PWC_DFS_PROFILE_E;

/*
 *  DFS Device QoS
 */
typedef enum tagDFS_QOS_ID_E
{
    DFS_QOS_ID_ACPU_MINFREQ_E = 0,  /*(0)*/
    DFS_QOS_ID_ACPU_MAXFREQ_E,      /*(1)*/
    DFS_QOS_ID_CCPU_MINFREQ_E,      /*(2)*/
    DFS_QOS_ID_CCPU_MAXFREQ_E,      /*(3)*/
    DFS_QOS_ID_DDR_MINFREQ_E,       /*(4)*/
    DFS_QOS_ID_DDR_MAXFREQ_E,       /*(5)*/
    DFS_QOS_ID_GPU_MINFREQ_E,       /*(6)*/
    DFS_QOS_ID_GPU_MAXFREQ_E,       /*(7)*/
    DFS_QOS_ID_BUS_MINFREQ_E,       /*(8)*/
    DFS_QOS_ID_BUS_MAXFREQ_E        /*(9)*/
}DFS_QOS_ID_E;

/*****************************************************************************
* �� �� ��  : mdrv_pm_pwrup
*
* ��������  : ͨ��ģ����Ƶ�Դ�ϵ�ӿ�
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : 0��ִ�гɹ���1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_pwrup (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_pwrdown
*
* ��������  : ͨ��ģ����Ƶ�Դ�µ�ӿ�
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : 0��ִ�гɹ���1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_pwrdown (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_get_pwrstatus
*
* ��������  : ͨ��ģ����Ƶ�Դ��ѯ�ӿ�
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : PWRCTRL_COMM_ON ����ģ���Ѿ��ϵ�
*             PWRCTRL_COMM_OFF ����ģ���Ѿ��µ�
*             ����������
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_get_pwrstatus(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_enable_pllclk
*
* ��������  : DRX PLLʹ��ʱ��
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  :  0��ִ�гɹ���-1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_enable_pllclk (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_disable_pllclk
*
* ��������  : DRX PLL�ر�ʱ��
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : 0��ִ�гɹ���-1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_disable_pllclk (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem,PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_get_pllclk_status
*
* ��������  : DRX PLL��ѯʱ��
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : PWRCTRL_COMM_ON         ʱ�Ӵ�
*             PWRCTRL_COMM_OFF        ʱ�ӹر�
*             -1                      ��ѯʧ��
*
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_get_pllclk_status (PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enCommModem,PWC_COMM_CHANNEL_E enChannel);

typedef unsigned int (*PWRCTRLFUNCPTR)(unsigned int arg);
/*****************************************************************************
* �� �� ��  : mdrv_pm_register_ccpuload_cb
*
* ��������  : �ṩ��TTF�Ļص�����
*
* �������  : PWRCTRLFUNCPTR pFunc
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
void mdrv_pm_register_ccpuload_cb(PWRCTRLFUNCPTR pFunc );

/*****************************************************************************
* �� �� ��  : mdrv_pm_get_ccpuload
*
* ��������  : ���ص�ǰ��cpuռ����
*
* �������  : ָ�����ɷ���ֵ����ָ��
* �������  :-1����ʾ��ȡֵʧ�ܣ�0����ʾ��ȡ�ɹ����ٷֱ�ͨ����η��ء�
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_get_ccpuload(unsigned int *ptrCCpuLoad);


/*****************************************************************************
* �� �� ��  : mdrv_pm_dfs_qos_get
*
* ��������  : �͹��ĵ�Ƶ������ͶƱ�ӿڡ�
*
* �������  : int qos_id     ͶƱģ��ID ��Ҫʹ��ö��DFS_QOS_ID_E�е�ֵ
*             unsigned int req_value  ͶƱƵ��ֵ����DDRƵ��800M�ȣ���λKHZ
*             int* req_id    ��ͶƱ�ӿ����뵽��ͶƱID�����粻ͬ���ͶƱ������ֵ̬������ÿ�β�һ��
* �������  :
*
* �� �� ֵ  : 0��ִ�гɹ���1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_dfs_qos_get(int qos_id, unsigned int req_value, int* req_id);

/*****************************************************************************
* �� �� ��  : mdrv_pm_dfs_qos_put
*
* ��������  : �͹��ĵ�Ƶ��ͶƱ�ͷŽӿ�
*
* �������  : int qos_id   ͶƱģ��ID��������Ƶ�ʣ�ACPUƵ�ʵ�
*             ��Ҫʹ��ö��DFS_QOS_ID_E�е�ֵ
*             int* req_id  mdrv_pm_dfs_qos_get����ͶƱ�ӿڻ�ȡ��ͶƱID
* �������  :
*
* �� �� ֵ  : 0��ִ�гɹ���1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_dfs_qos_put(int qos_id, int* req_id);

/*****************************************************************************
* �� �� ��  : mdrv_pm_dfs_qos_update
*
* ��������  : �͹��ĵ�Ƶ������ͶƱֵ�ӿ�
*
* �������  : int qos_id    ͶƱģ��ID��������Ƶ�ʣ�ACPUƵ�ʵ�
*             ��Ҫʹ��ö��DFS_QOS_ID_E�е�ֵ
*             int req_id    mdrv_pm_dfs_qos_get����ͶƱ�ӿڻ�ȡ����ͶƱID
*             unsigned int req_value ͶƱƵ��ֵ����DDRƵ��800M��
* �������  :
*
* �� �� ֵ  : 0��ִ�гɹ���1��ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_dfs_qos_update(int qos_id, int req_id, unsigned int req_value);


/*****************************************************************************
* �� �� ��  : mdrv_pm_get_tcxo_status
*
* ��������  : ��ȡTCXO��״̬
*
* �������  : PWC_COMM_MODEM_E enModemId
* �������  :
*
* �� �� ֵ  : PWRCTRL_COMM_ON ʹ��
*             PWRCTRL_COMM_OFF ��ֹ
*             �������쳣
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_E enModemId);

/*****************************************************************************
* �� �� ��  : mdrv_pm_enable_tcxo
*
* ��������  : ��TCXO
*
* �������  : PWC_COMM_MODEM_E  enModemId ����
*             PWC_COMM_MODE_E enModeType  Э��ģʽ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_enable_tcxo(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType);


/*****************************************************************************
* �� �� ��  : mdrv_pm_disable_tcxo
*
* ��������  : �ر�TCXO
*
* �������  : PWC_COMM_MODEM_E  enModemId  ����
*             PWC_COMM_MODE_E enModeType   Э��ģʽ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_disable_tcxo(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType);

/*****************************************************************************
* �� �� ��  : mdrv_pm_start_tcxo_timer
*
* ��������  : ����ר����TCXO�Ķ�ʱ��
*
* �������  : PWC_COMM_MODEM_E  enModemId ����
*             PWC_COMM_MODE_E enModeType  Э��ģʽ
*             PWC_TCXO_FUNCPTR routine   �ص�����
*             int arg                    �ص��������صĲ���
*             unsigned int timerValue    ��ʱ��ʱ��(��λ��ms)
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
typedef int (*PWC_TCXO_FUNCPTR)(int);
int mdrv_pm_start_tcxo_timer(PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_TCXO_FUNCPTR routine,int arg, unsigned int timerValue);

/*****************************************************************************
* �� �� ��  : mdrv_pm_get_tcxo_rfclk_status
*
* ��������  : ��ѯRF CLK״̬
*
* �������  : PWC_COMM_CHANNEL_E enChannel  channel ID
* �������  :
*
* �� �� ֵ  : PWRCTRL_COMM_ON ��״̬
*             PWRCTRL_COMM_OFF �ر�״̬
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_get_tcxo_rfclk_status (PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_enable_tcxo_rfclk
*
* ��������  : ��RF CLK
*
* �������  : PWC_COMM_MODEM_E  enModemId  ����
*             PWC_COMM_MODE_E enModeType    ģʽ
*             PWC_COMM_CHANNEL_E enChannel  channel ID
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_enable_tcxo_rfclk (PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_disable_tcxo_rfclk
*
* ��������  : �ر�RF CLK
*
* �������  : PWC_COMM_MODEM_E  enModemId  ����
*             PWC_COMM_MODE_E enModeType    ģʽ
*             PWC_COMM_CHANNEL_E enChannel  channel ID
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_disable_tcxo_rfclk (PWC_COMM_MODEM_E  enModemId, PWC_COMM_MODE_E enModeType, PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_get_dfs_profile
*
* ��������  : ��ȡ��ǰ��profileֵ
*
* �������  : void
* �������  :
*
* �� �� ֵ  : ��ǰ�����ĸ�profile
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_get_dfs_profile(void);

/*****************************************************************************
* �� �� ��  : mdrv_pm_set_dfs_profile
*
* ��������  : ����Ҫ������Ŀ��profile
*
* �������  : int profile  ��Ҫ�趨��profileֵ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_set_dfs_profile(int profile);

/*****************************************************************************
* �� �� ��  : mdrv_pm_set_dfs_baseprofile
*
* ��������  : ���õ�Ƶprofileֵ����
*
* �������  : int profile  ��Ҫ�趨��profile����ֵ
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_set_dfs_baseprofile(int profile);


/*****************************************************************************
* �� �� ��  : mdrv_pm_lock_dfs
*
* ��������  : ����cpufreq������Ƶ����
*
* �������  : bool lock Lock=0 ������Ƶ����;Lock=1 ������Ƶ����
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
void mdrv_pm_lock_dfs(unsigned int lock);

/*****************************************************************************
* �� �� ��  : mdrv_pm_set_dfs_target
*
* ��������  : ����Ҫ������Ƶ��ֵ
*
* �������  : int a9freq   ��Ҫ�趨��cpuƵ��ֵ
*             int ddrfreq  ��Ҫ�趨��ddrƵ��ֵ
*             int slowfreq ��Ҫ�趨��slowbusƵ��
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_set_dfs_target(int a9freq, int ddrfreq, int slowfreq);

/*****************************************************************************
* �� �� ��  : mdrv_pm_enable_bbpclk
*
* ��������  : ͨ��ģ�����BBPʱ��ʹ�ܽӿ�
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���

* �������  :
*
* �� �� ֵ  :  0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_enable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_disable_bbpclk
*
* ��������  : ͨ��ģ�����BBPʱ�ӹرսӿ�
*
* �������  : PWC_COMM_MODE_E enModeId      Э��ģʽ
*             PWC_COMM_MODULE_E enModuleId  ����ģ��
*             PWC_COMM_MODEM_E enModemId    ����
*             PWC_COMM_CHANNEL_E enChannel  channel���
* �������  :
*
* �� �� ֵ  : 0���ɹ���������ʧ��
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_disable_bbpclk (PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);

/*****************************************************************************
* �� �� ��  : mdrv_pm_set_wakesrc
*
* ��������  : ����ĳ���ж�Ϊ����Դ�ж�
*
* �������  : PM_WAKE_SRC_E wake_src ��Ҫ���õĻ���Դ
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
void mdrv_pm_set_wakesrc(PM_WAKE_SRC_E wake_src);

/*****************************************************************************
* �� �� ��  : mdrv_pm_clear_wakesrc
*
* ��������  : ȡ������ĳ���ж�Ϊ����Դ�ж�
*
* �������  : PM_WAKE_SRC_E wake_src ��Ҫ���õĻ���Դ
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
void mdrv_pm_clear_wakesrc(PM_WAKE_SRC_E wake_src);

/*****************************************************************************
 *  �� �� ��  : mdrv_pm_wake_lock
 *  ��������  : ��������˯��ͶƱ�ӿڡ�
 *  �������  : lock_id id
 *  �������  : None
 *  �� �� ֵ  : ��
 ******************************************************************************/
unsigned int mdrv_pm_wake_lock(PWC_CLIENT_ID_E id);

/*****************************************************************************
 *  �� �� ��  : mdrv_pm_wake_unlock
 *  ��������  : ��������˯��ͶƱ�ӿڡ�
 *  �������  : lock_id id
 *  �������  : None
 *  �� �� ֵ  : ��
 ******************************************************************************/
unsigned int mdrv_pm_wake_unlock(PWC_CLIENT_ID_E id);

/*****************************************************************************
* �� �� ��  : mdrv_pm_register_sleep_ops
*
* ��������  : �ṩ���ϲ�ע��ص���������ϵͳ˯��/����ʱ���á�
*
* �������  : 
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_register_sleep_ops(unsigned char* pname,PWC_SLEEP_FUNCPTR suspend,PWC_SLEEP_FUNCPTR resume);
/*****************************************************************************
* �� �� ��  : mdrv_pm_unregister_sleep_ops
*
* ��������  : ȡ���ص���ע��(�ýӿ��ݲ�Ҫ����)
*
* �������  : 
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_pm_unregister_sleep_ops(unsigned char* pname);
#ifdef __cplusplus
}
#endif
#endif
