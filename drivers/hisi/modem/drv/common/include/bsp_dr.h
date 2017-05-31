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

#ifndef _BSP_DR_H_
#define _BSP_DR_H_

#include "product_config.h"
#include "osl_types.h"
#ifdef CONFIG_PMU_NEW
#include "hi_dr.h"
#endif

#ifdef __FASTBOOT__
#include <boot/boot.h>
#include "types.h"
#endif

/*error code*/
#define BSP_DR_OK              0
#define BSP_DR_ERROR          (-1)
#define BSP_DR_PARA_ERROR      0x2002/*��Ч����ֵ*/

typedef enum  _dr_mode_e
{
    PMU_DRS_MODE_FLA_FLASH = 0,     /*��˸����ģʽ(DR1/2/3/4/5)*/
    PMU_DRS_MODE_FLA_LIGHT ,        /*��˸����ģʽ(DR1/2/3/4/5)*/
    PMU_DRS_MODE_BRE ,              /*����ģʽ(DR3/4/5)*/
    PMU_DRS_MODE_BRE_FLASH ,        /*������˸ģʽ���߾�����˸(DR1/2)*/
    PMU_DRS_MODE_BRE_LIGHT ,        /*��������ģʽ(DR1/2)*/
    PMU_DRS_MODE_BUTTOM
}dr_mode_e;

typedef enum  _dr_bre_time_e
{
    PMU_DRS_BRE_ON_MS = 0,      /*��������ʱ��(DR1/2/3/4/5)*/
    PMU_DRS_BRE_OFF_MS ,        /*��������ʱ��(DR1/2/3/4/5)*/
    PMU_DRS_BRE_RISE_MS ,       /*��������ʱ��(DR1/2/3/4/5))*/
    PMU_DRS_BRE_FALL_MS ,       /*��������ʱ��(DR1/2/3/4/5))*/
    PMU_DRS_BRE_TIME_BUTTOM
}dr_bre_time_e;

typedef struct
{
    unsigned int fla_on_us;     /*��˸����ʱ��*/
    unsigned int fla_off_us;    /*��˸����ʱ��*/
}DR_FLA_TIME;

typedef struct
{
    unsigned int bre_on_ms;
    unsigned int bre_off_ms;
    unsigned int bre_rise_ms;
    unsigned int bre_fall_ms;
}DR_BRE_TIME;

#define ALWAYS_ON_OFF_TIME_DR12     5000        /*�������߳����Ĵ�������ֵ*/
#define ALWAYS_ON_OFF_TIME_DR345    50000       /*�������߳����Ĵ�������ֵ*/
#define BRE_TIME_NOT_SURE           0xfffffe    
#define DR_VALUE_INVALIED           0xffffffff

#ifdef __KERNEL__
/*****************************************************************************
* �� �� ��  : bsp_dr_list_current
* ��������  :��ѯĳ·����Դָ����λ������
* �������  :dr_id:����Դid�ţ�selector��Ҫ��ѯ�ĵ�λ��
* �������  :��
* ����ֵ��   ����ѯ�ĵ���Դָ����λ�ĵ���ֵ����λ��uA��
*
*****************************************************************************/
int bsp_dr_list_current(int dr_id, unsigned selector);

/*****************************************************************************
* �� �� ��  : bsp_pmu_dr_set_mode
* ��������  :����ĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�mode�����õ�ģʽ��
* �������  :��
* ����ֵ��   �ɹ���ʧ��
*
*****************************************************************************/
int bsp_dr_set_mode(int dr_id, dr_mode_e mode);

/*****************************************************************************
* �� �� ��  : bsp_hi6551_dr_get_mode
* ��������  :��ȡĳ·����Դģʽ��
* �������  :dr_id:����Դid�ţ�
* �������  :��
* ����ֵ��   ����Դ��ǰģʽ
*
*****************************************************************************/
dr_mode_e bsp_dr_get_mode(int dr_id);

/*****************************************************************************
 �� �� ��  : bsp_dr_fla_time_set
 ��������  : ����dr����˸����ʱ��͵���ʱ��
 �������  : dr_fla_time_st:��˸ʱ������ṹ��;��λ:us
 �������  : ��
 �� �� ֵ  : ���óɹ�����ʧ��
 ���ú���  :
 ��ע˵��  : ��Ӧ�Ĵ���ֻ������ʱ��Ĺ��ܣ�����Ҫ������
             ��˸����:reg_value*31.25ms;����ʱ��:reg_value*7.8125ms
*****************************************************************************/
int bsp_dr_fla_time_set(int dr_id, DR_FLA_TIME *dr_fla_time_st);
int bsp_dr_fla_time_get(int dr_id, DR_FLA_TIME *dr_fla_time_st);

/*****************************************************************************
 �� �� ��  : bsp_dr_bre_time_set
 ��������  : ����dr�ĺ���ʱ��(��������������������������ʱ��)
 �������  : dr_id:Ҫ���õĵ���Դ���;dr_bre_time_st:����ʱ������ṹ��;
            û���ҵ����õ�ʱ�䣬������Ϊ����
 �������  : ��
 �� �� ֵ  : ���óɹ�����ʧ��
 ���ú���  :
 ��ע˵��  : ��Ӧ�Ĵ���ֻ������ʱ��Ĺ��ܣ�����Ҫ������
*****************************************************************************/
int bsp_dr_bre_time_set(int dr_id, DR_BRE_TIME *dr_bre_time_st);

/*****************************************************************************
 �� �� ��  : bsp_dr_bre_time_list
 ��������  : ����dr�ĺ���ʱ��(��������������������������ʱ��)����λ��ʱ��ֵ
 �������  : dr_id:Ҫ��ѯ�ĵ���Դ���;bre_time_enum:��Ҫ��ѯ��ʱ������;
             selector��ʱ�䵵λ
 �������  : ��
 �� �� ֵ  : ��λʱ��
 ���ú���  :
 ��ע˵��  :
*****************************************************************************/
unsigned bsp_dr_bre_time_list(int dr_id, dr_bre_time_e bre_time_enum ,unsigned selector);

/*****************************************************************************
 �� �� ��  : bsp_dr_bre_time_selectors_get
 ��������  : ��ȡdr ����ʱ���ܹ���λֵ
 �������  : dr_id:Ҫ���õĵ���Դ���;bre_time_enum:��Ҫ��ѯ��ʱ������;
 �������  : ��
 �� �� ֵ  : ��λʱ��
 ���ú���  :
 ��ע˵��  :
*****************************************************************************/
unsigned bsp_dr_bre_time_selectors_get(int dr_id, dr_bre_time_e bre_time_enum);

/*****************************************************************************
 �� �� ��  : bsp_dr_start_delay_set
 ��������  : ����dr��������ʱʱ��
 �������  : dr_id:Ҫ���õĵ���Դ���;delay_ms:������ʱ��ʱ�䣬��λ:ms
             ���÷�Χ:[0 , 32768]ms
 �������  : ��
 �� �� ֵ  : ���óɹ���ʧ��
 ���ú���  :
 ��ע˵��  : ��Ӧ�Ĵ���ֻ������ʱ��Ĺ��ܣ�����Ҫ��������ֻ��DR3/4/5�д˹���
*****************************************************************************/
int bsp_dr_start_delay_set(int dr_id, unsigned delay_ms);
#else /* __FASTBOOT__ */
#ifdef CONFIG_PMU_NEW
void bsp_dr_init(void);
#else
void bsp_dr_init(void){}
#endif /* end #define CONFIG_PMU_NEW */
#endif /* end #define __KERNEL__ */
#endif /* end #define _BSP_DR_H_*/
