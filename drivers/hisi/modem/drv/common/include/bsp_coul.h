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

#ifndef _BSP_COUL_H_
#define _BSP_COUL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include "osl_types.h"
#ifdef __FASTBOOT__
#include "types.h"
#include <boot/boot.h>
#endif
//#include "bsp_pmu.h"

/*�жϺţ��������������pmu�ĺ�*/
#if 0
typedef enum{
    COUL_INT = PMU_INT_COUL_INT,   /*cl_out>cl_intʱ�ϱ��ж�*/
    COUL_OUT = PMU_INT_COUL_OUT,    /*cl_out������81.25%�ϱ��ж�*/
    COUL_IN = PMU_INT_COUL_IN ,      /*cl_in������81.25%�ϱ��ж�*/
    COUL_CHG_TIMER = PMU_INT_CHG_TIMER,  /*chg_timer������81.25%�ϱ��ж�*/
    COUL_LOAD_TIMER = PMU_INT_LOAD_TIMER,/*load_timer������81.25%�ϱ��ж�*/
    COUL_VBAT_INT = PMU_INT_VBAT_INT,    /*vbat��ѹ<�趨��vbat_intֵ*/
    COUL_INT_BUILT
}COUL_INT_TYPE;
#endif
typedef enum{
    COUL_INT = 25,   /*cl_out>cl_intʱ�ϱ��ж�*/
    COUL_OUT = 26,    /*cl_out������81.25%�ϱ��ж�*/
    COUL_IN = 27 ,      /*cl_in������81.25%�ϱ��ж�*/
    COUL_CHG_TIMER = 28,  /*chg_timer������81.25%�ϱ��ж�*/
    COUL_LOAD_TIMER = 29,/*load_timer������81.25%�ϱ��ж�*/
    COUL_VBAT_INT = 30,    /*vbat��ѹ<�趨��vbat_intֵ*/
    COUL_INT_BUILT
}COUL_INT_TYPE;
/*eco modeȥ��ʱ��*/
typedef enum{
    COUL_FILETR_20MS = 0,
    COUL_FILETR_25MS,
    COUL_FILETR_30MS,
    COUL_FILETR_35MS,
    COUL_FILETR_BUILT
}COUL_FILETR_TIME;

/*��������*/
/*****************************************************************************
 �� �� ��  : bsp_coul_voltage
 ��������  : ��ǰ��ѹ��ȡ����λ:mV
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_voltage(void);
/*****************************************************************************
 �� �� ��  : bsp_coul_voltage_before
 ��������  : ��ȡ��ǰ��ѹ��times�ε�ѹֵ����λ:mV
 �������  : times:Ҫ��ȡ��ǰ�ڼ��εĵ�ѹֵ([��Χ[1,20])
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_voltage_before(unsigned int times);
/*****************************************************************************
 �� �� ��  : bsp_coul_current
 ��������  : ��ǰ������ȡ,��λ:mA
 �������  : void
 �������  : ��
 �� �� ֵ  : signed int
 ���ú���  :
 ��������  :
*****************************************************************************/
signed int  bsp_coul_current(void);
/*****************************************************************************
 �� �� ��  : bsp_coul_current_before
 ��������  : ��ȡ��ǰ����ǰtimes�ε���ֵ����λ:mA
 �������  : times:Ҫ��ȡ��ǰ�ڼ��εĵ���ֵ([��Χ[1,20])
 �������  : ��
 �� �� ֵ  : signed int
 ���ú���  :
 ��������  :
*****************************************************************************/
signed int bsp_coul_current_before(unsigned int times);
/*****************************************************************************
 �� �� ��  : bsp_coul_in_capacity
 ��������  : ������������ȡ,��λ:uC
 �������  : void
 �������  : ��
 �� �� ֵ  : signed long long
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned long long bsp_coul_in_capacity(void);
/*****************************************************************************
 �� �� ��  : bsp_coul_out_capacity
 ��������  : ������������ȡ,��λ:uC
 �������  : void
 �������  : ��
 �� �� ֵ  : signed long long
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned long long bsp_coul_out_capacity(void);
/*****************************************************************************
 �� �� ��  : bsp_coul_charge_time
 ��������  : ���ʱ���ȡ,��λ:s
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_charge_time(void);
/*****************************************************************************
 �� �� ��  : bsp_coul_charge_time
 ��������  : ���ʱ���ȡ,��λ:s
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_discharge_time(void);
/*****************************************************************************
 �� �� ��  : bsp_coul_eco_filter_time
 ��������  : ���ÿ��ؼ�eco�˲�ʱ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void bsp_coul_eco_filter_time(COUL_FILETR_TIME filter_time);
/*****************************************************************************
 �� �� ��  : coul_ocv_get
 ��������  : ��ؿ�·��ѹ����ֵ��ȡ
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_ocv_get(void);
/*����У׼����ʱ��*/
/*****************************************************************************
 �� �� ��  : bsp_coul_voltage_uncali
 ��������  : ��ȡδ��У׼��ǰ��ѹ����λ:mV
 �������  : void
 �������  : ��
 �� �� ֵ  : unsigned int
 ���ú���  :
 ��������  :
*****************************************************************************/
unsigned int bsp_coul_voltage_uncali(void);
/*****************************************************************************
 �� �� ��  : bsp_coul_current_uncali
 ��������  : ��ȡδ��У׼��ǰ����,��λ:mA
 �������  : void
 �������  : ��
 �� �� ֵ  : signed long long
 ���ú���  :
 ��������  :
*****************************************************************************/
signed int  bsp_coul_current_uncali(void);

#ifdef __KERNEL__
typedef void (*COUL_INT_FUNC)(void *);
/*****************************************************************************
 �� �� ��  : bsp_coul_int_register
 ��������  : ע����ؼ��жϻص�����
 �������  : int:�жϺţ�func:�жϴ���ص�������data:�ص���������ָ��
 �������  : ��
 �� �� ֵ  : ע��ɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_coul_int_register(COUL_INT_TYPE irq,COUL_INT_FUNC func,void *data);
#ifdef CONFIG_PMU_NEW
void bsp_coul_int_mask(unsigned int irq);
void bsp_coul_int_unmask(unsigned int irq);
int bsp_coul_int_is_masked(unsigned int irq);
#endif
#endif

#ifdef __FASTBOOT__
/*****************************************************************************
 �� �� ��  : bsp_coul_init
 ��������  : ���ؼ�ģ���ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��ʼ���ɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_coul_init(void);
/*****************************************************************************
 �� �� ��  : bsp_coul_ready
 ��������  : �ȴ����ؼ��ȶ�
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
void bsp_coul_ready(void);
#endif

/*������*/
#define BSP_COUL_OK (0)
#define BSP_COUL_ERR (-1)
#define BSP_COUL_UNVALID (0xffffffff)

#ifdef __cplusplus
}
#endif

#endif /* end #define _BSP_COUL_H_*/


