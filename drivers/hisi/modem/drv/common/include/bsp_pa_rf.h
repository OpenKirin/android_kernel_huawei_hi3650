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

#ifndef __BSP_PA_RF_H__
#define __BSP_PA_RF_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include <osl_types.h>
#include <osl_spinlock.h>
#include <mdrv_pm.h>
enum pa_rf_vote_map_id{
    PA0 = 0,
    PA1,
    RFIC0,
    RFIC1,
    PA_RF_ID_MAX,
};
struct pa_rf_vote_map_stru{
     const char     *name;                              /*��¼ͶƱ��Ŀ*/
     int            status;                             /*��¼��ǰ״̬*/
     unsigned int   vote;                               /*��¼ͶƱ���.bitΪ1��ʾ��Ӧ��ģͬ���ϵ磬bitΪ0��ʾͬ���µ�*/
     unsigned int   enable_count[PWC_COMM_MODE_BUTT];   /*��¼��ģ�Ŀ�����*/
     unsigned int   disable_count[PWC_COMM_MODE_BUTT];  /*��¼��ģ�Ĺش���*/
     unsigned int   enable_real;                        /*��¼��ʵ���Ĵ���*/
     unsigned int   disable_real;                       /*��¼��ʵ�صĴ���*/
     spinlock_t     spinlock;
};

/*****************************************************************************
 �� �� ��  : bsp_pa_rf_init
 ��������  : ��ȡregulator
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0:�ɹ���else - ʧ�ܡ�ʧ��ʱ����ֵ��bit0~bit4��Ӧ��ȡʧ�ܵ�regulator_pmu id
*****************************************************************************/
s32 bsp_pa_rf_init(void);

/*****************************************************************************
 �� �� ��  : bsp_pa_poweron
 ��������  : ��pa�ϵ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pa_poweron(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_pa_poweroff
 ��������  : ��pa�µ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_pa_poweroff(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_get_pa_powerstatus
 ��������  : ��ȡpa���µ�״̬
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
PWC_COMM_STATUS_E bsp_get_pa_powerstatus(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_rf_poweron
 ��������  : ��rf�ϵ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_rf_poweron(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_rf_poweroff
 ��������  : ��rf�µ�
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
s32 bsp_rf_poweroff(PWC_COMM_MODEM_E modem_id);

/*****************************************************************************
 �� �� ��  : bsp_get_rf_powerstatus
 ��������  : ��ȡrf���µ�״̬
 �������  : @modem_id - 0:���� 1:����
 �������  : ��
 �� �� ֵ  : 0 - �ɹ�����0 - ʧ��
*****************************************************************************/
PWC_COMM_STATUS_E bsp_get_rf_powerstatus(PWC_COMM_MODEM_E modem_id);

int bsp_pa_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_pa_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
PWC_COMM_STATUS_E bsp_pa_power_status(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_rfic_power_up(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
int bsp_rfic_power_down(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);
PWC_COMM_STATUS_E bsp_rfic_power_status(PWC_COMM_MODEM_E enModemId, PWC_COMM_CHANNEL_E enChannel);

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_PA_RF_H__ */
