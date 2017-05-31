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

#ifndef __MDRV_ACORE_CHG_H__
#define __MDRV_ACORE_CHG_H__

#include "mdrv_public.h"
#ifdef __cplusplus
extern "C"
{
#endif

typedef enum CHARGING_STATE_E_tag
{
        CHARGING_INIT = -1,
        NO_CHARGING_UP = 0,  /*����δ���*/
        CHARGING_UP ,              /*���������*/
        NO_CHARGING_DOWN ,  /*�ػ�δ���*/
        CHARGING_DOWN         /*�ػ�δ���*/
}CHARGING_STATE_E;

typedef enum BATT_LEVEL_E_tag
{
        BATT_INIT = -2,
        BATT_LOW_POWER =-1,    /*��ص͵�*/
        BATT_LEVEL_0,          /*0���ص���*/
        BATT_LEVEL_1,          /*1���ص���*/
        BATT_LEVEL_2,          /*2���ص���*/
        BATT_LEVEL_3,          /*3���ص���*/
        BATT_LEVEL_4,          /*4���ص���*/
        BATT_LEVEL_MAX
}BATT_LEVEL_E;

typedef struct BATT_STATE_tag
{
    CHARGING_STATE_E  charging_state;
    BATT_LEVEL_E      battery_level;
}BATT_STATE_S;

/*****************************************************************************
 �� �� ��  : mdrv_misc_get_battery_state
 ��������  :��ȡ�ײ���״̬��Ϣ
 �������  :battery_state ������Ϣ
 �������  :battery_state ������Ϣ
 ����ֵ��   0 �����ɹ�
                         -1����ʧ��

*****************************************************************************/
int mdrv_misc_get_battery_state(BATT_STATE_S *battery_state);


/*****************************************************************************
 �� �� ��  : mdrv_misc_get_charging_status
 ��������  :��ѯĿǰ�Ƿ����ڳ����
 �������  :��
 �������  :��
 ����ֵ��   0 δ���
                          1 �����
*****************************************************************************/
int mdrv_misc_get_charging_status(void);


/*****************************************************************************
 �� �� ��  : mdrv_misc_set_charge_state
 ��������  :ʹ�ܻ��߽�ֹ���
 �������  :ulState      0:��ֹ���
 						1:ʹ�ܳ��
 �������  :��
 ����ֵ��    ��
*****************************************************************************/
void mdrv_misc_set_charge_state(unsigned long ulState);

/*****************************************************************************
 �� �� ��  : mdrv_misc_get_charge_state
 ��������  :��ѯ
 �������  :
 �������  :��
 ����ֵ��    ��
*****************************************************************************/
int mdrv_misc_get_charge_state(void);


/*****************************************************************************
 �� �� ��  : mdrv_misc_sply_battery
 ��������  :��ѯ
 �������  :
 �������  :��
 ����ֵ��    ��
*****************************************************************************/
int mdrv_misc_sply_battery(void);


/*****************************************************************************
 �� �� ��  : mdrv_misc_get_cbc_state
 ��������  : ���ص��״̬�͵���
 �������  :pusBcs 0:����ڹ��� 1:�������ӵ��δ���� 2:û����������
                          pucBcl  0:���������û����������
 �������  : pusBcs 0:����ڹ��� 1:�������ӵ��δ���� 2:û����������
                          pucBcl  0:���������û����������
 ����ֵ��   0 �����ɹ�
                         -1����ʧ��

*****************************************************************************/
int mdrv_misc_get_cbc_state(unsigned char *pusBcs,unsigned char *pucBcl);


#ifdef __cplusplus
}
#endif
#endif

