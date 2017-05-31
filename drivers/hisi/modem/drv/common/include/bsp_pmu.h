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

#ifndef _BSP_PMU_H_
#define _BSP_PMU_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include "osl_types.h"

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
#include "mdrv_pmu.h"
#endif

#ifdef __FASTBOOT__
#include <boot/boot.h>
#include "types.h"
#endif

#include <hi_pmu.h>

/*PMU������ܴ�С��3*1024*/
#define SHM_PMU_OCP_INFO_SIZE 0x10
#define SHM_PMU_NPREG_SIZE 0x10
#define SHM_PMU_OCP_INFO_ADDR ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_PMU)
#define SHM_MEM_PMU_NPREG_ADDR (SHM_PMU_OCP_INFO_ADDR + SHM_PMU_OCP_INFO_SIZE)

/*pmu״̬�궨�壬��om����*/
#define PMU_STATE_OK    0
#define PMU_STATE_UNDER_VOL (1 << 0)
#define PMU_STATE_OVER_VOL  (1 << 1)
#define PMU_STATE_OVER_CUR  (1 << 2)
#define PMU_STATE_OVER_TEMP (1 << 3)

#ifdef __KERNEL__

/*PMU 32K CLK ö������ */
typedef enum  _pmu_clk_e
{
    PMU_32K_CLK_A = 0,   /*SOC˯��ʱ�ӣ�����ģ�鲻��ʹ��*/
    PMU_32K_CLK_B,       /**/
#if defined(CONFIG_PMIC_HI6551)
    PMU_32K_CLK_C,       /*ֻ��hi6551���и�·ʱ��*/
#endif
    PMU_32K_CLK_MAX
}pmu_clk_e;

/*��ʹ��pmu�жϵ�ģ�����*/
typedef void (*pmufuncptr)(void *);

/* ioshare */
typedef enum _pmic_ioshare_e
{
    GPIO_FUNC0 = 1,
    GPIO_FUNC1,
    GPIO_FUNC2,
    DR1_FUNC,
    DR2_FUNC,
    DR3_FUNC = 6,
    
    SIM0_HPD,
    SIM1_HPD,
    AUXDAC1_SSI,
    HKADC10_FUNC,
    HKADC11_FUNC0 = 11,
    HKADC11_FUNC1,
    PMIC_IOSHARE_E_MAX,
}pmic_ioshare_e;

#endif

#ifdef __KERNEL__
/*��������*/

/*****************************************************************************
 �� �� ��  : pmic_get_base_addr
 ��������  :���� pmu ����ַ
 �������  : void
 �������  : 
 �� �� ֵ  : pmu ����ַ
 ���ú���  :
 ��������  : ϵͳ��ά�ɲ�
*****************************************************************************/
u32 pmic_get_base_addr(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_get_boot_state
 ��������  :ϵͳ����ʱ���pmu�Ĵ���״̬��
                ȷ���Ƿ�����pmu���������
 �������  : void
 �������  : reset.log
 �� �� ֵ  : pmu�����ok
 ���ú���  :
 ��������  :ϵͳ��ά�ɲ�
*****************************************************************************/
int bsp_pmu_get_boot_state(void);

/*****************************************************************************
 �� �� ��  : bsp_pmu_32k_clk_enable
 ��������  : ����pmu��32kʱ��
 �������  : clk_id:32kʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_32k_clk_enable(pmu_clk_e clk_id);
/*****************************************************************************
 �� �� ��  : bsp_pmu_32k_clk_disable
 ��������  : �ر�pmu��32kʱ��
 �������  : clk_id:32kʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : �رճɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_32k_clk_disable(pmu_clk_e clk_id);
/*****************************************************************************
 �� �� ��  : bsp_pmu_32k_clk_is_enabled
 ��������  : ��ѯpmu��32kʱ���Ƿ���
 �������  : clk_id:32kʱ��ö��ֵ
 �������  : ��
 �� �� ֵ  : ������ر�
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_32k_clk_is_enabled(pmu_clk_e clk_id);
/*****************************************************************************
 �� �� ��  : bsp_pmu_xo_clk_enable
 ��������  : ����pmu��xoʱ��
 �������  : 
 �������  : ��
 �� �� ֵ  : �����ɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_xo_clk_enable(int clk_id);
/*****************************************************************************
 �� �� ��  : bsp_pmu_xo_clk_disable
 ��������  : �ر�pmu��xoʱ��
 �������  : 
 �������  : ��
 �� �� ֵ  : �رճɹ���ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_xo_clk_disable(int clk_id);
/*****************************************************************************
 �� �� ��  : bsp_pmu_xo_clk_is_enabled
 ��������  : ��ѯpmu��xoʱ���Ƿ���
 �������  :
 �������  : ��
 �� �� ֵ  : ������ر�
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_pmu_xo_clk_is_enabled(int clk_id);

/*****************************************************************************
 �� �� ��  : bsp_pmu_version_get
 ��������  : ��ȡusb�Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : usb�����γ�:1:����;0:�γ�
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool bsp_pmu_usb_state_get(void);
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
void bsp_pmu_irq_mask(unsigned int irq);
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
void bsp_pmu_irq_unmask(unsigned int irq);
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
int bsp_pmu_irq_is_masked(unsigned int irq);
/*****************************************************************************
 �� �� ��  : bsp_pmu_key_state_get
 ��������  : ��ȡ�����Ƿ���״̬
 �������  : void
 �������  : ��
 �� �� ֵ  : �����Ƿ���:1:���£�0:δ����
 ���ú���  :
 ��������  : ���ػ�ģ��
*****************************************************************************/
bool bsp_pmu_key_state_get(void);
/*****************************************************************************
 �� �� ��  : bsp_pmu_irq_callback_register
 ��������  : ע���жϴ���ص�����
 �������  : irq
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : ������pmu�ڲ����ж�ģ��
*****************************************************************************/
int bsp_pmu_irq_callback_register(unsigned int irq,pmufuncptr routine,void *data);

/*****************************************************************************
 �� �� ��  : bsp_pmu_sim_debtime_set
 ��������  : ����SIM���ж�ȥ��ʱ�䣬��λ��us��
 �������  : uctime:���õ�ȥ��ʱ��(��Χ��(120,600),step:30;)
 �������  : ���óɹ���ʧ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : sim��ģ��
*****************************************************************************/
int bsp_pmu_sim_debtime_set(u32 uctime);
void bsp_pmu_ldo22_res_enable(void);
void bsp_pmu_ldo22_res_disable(void);
//unsigned int bsp_pmu_irq_inner_id_get(pmu_int_mod_e mod);
int bsp_pmic_ioshare_status_get(pmic_ioshare_e id);

#endif

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__) || defined(__CMSIS_RTOS)
/*****************************************************************************
 �� �� ��  : bsp_pmu_init
 ��������  : ϵͳ������ʼ��pmu����ź���
 �������  : void �������  : ��
 �� �� ֵ  : ��
 ���ú���  :��������  :ccore��mcoreϵͳ��ʼ����غ���
*****************************************************************************/
int bsp_pmu_init(void);
int bsp_sim_upres_disable(u32 sim_id);
#endif

#if defined(__OS_RTOSCK__) || defined(__OS_VXWORKS__)
u32 pmic_get_base_addr(void);
s32 bsp_pmu_apt_enable(void);
s32 bsp_pmu_apt_disable(void);
s32 bsp_pmu_apt_status_get(void);
s32 bsp_pmu_parf_exc_check(void);
void bsp_pmu_dcxo_fre_compensate(DCXO_COMPENSATE_ID_E dcxoId,unsigned int value);
#endif

/*fastboot��a��c��mcore���ṩ*/
/*****************************************************************************
 �� �� ��  : bsp_pmu_version_get
 ��������  : ��ȡpmu�汾��
 �������  : void
 �������  : ��
 �� �� ֵ  : pmu�汾��
 ���ú���  :
 ��������  : ����hso��msp����
*****************************************************************************/
char* bsp_pmu_version_get(void);


/*�ж�ddr�Ƿ񱻸�д��ħ����*/
#define SHM_PMU_VOLTTABLE_MAGIC_START_DATA   0xc7c7c7c7
#define SHM_PMU_VOLTTABLE_MAGIC_END_DATA     0xa6a6a6a6
/*�����붨��*/
#define BSP_PMU_ERROR   -1
#define BSP_PMU_OK      0
#define BSP_PMU_NO_PMIC      0x2001/*ϵͳû��PMUоƬ*/
#define BSP_PMU_PARA_ERROR      0x2002/*��Ч����ֵ*/
#define BSP_PMU_VOLTTABLE_ERROR      0x2003/*DDR����д��table���ƻ�*/

/*om log*/
/*PMU om log ö������ */
typedef enum  _pmu_om_log_e
{
    PMU_OM_LOG_START = 0,   /*PMU om log*/
    PMU_OM_LOG_RESET,
    PMU_OM_LOG_EXC,       /*wifi clk */
    PMU_OM_LOG_END
}pmu_om_log_e;
#define PMU_OM_LOG            "/modem_log/log/pmu_om.log"
/*debug*/

/*��������*/
#if defined(__CMSIS_RTOS)
int bsp_pmu_suspend(void);
int bsp_pmu_resume(void);
int bsp_pmu_sdio_suspend(void);
int bsp_pmu_sdio_resume(void);
void bsp_pmu_volt_state_save(void);
#endif

void bsp_pmu_rfclk_enable(u32 rf_id);
void bsp_pmu_rfclk_disable(u32 rf_id);
int bsp_pmu_rfclk_is_enabled(u32 rf_id);
unsigned int bsp_pmu_get_rtc_value(void);
u32 bsp_pmic_get_base_addr(void);
void bsp_pmic_reg_write(u32 addr, u32 value);
void bsp_pmic_reg_read(u32 addr, u32 *pValue);
void bsp_pmic_reg_write_mask(u32 addr, u32 value, u32 mask);
int bsp_pmic_reg_show(u32 addr);

typedef void (*PMU_OCP_FUNCPTR)(int);
int bsp_pmu_ocp_register(int volt_id,PMU_OCP_FUNCPTR func);


#ifdef __cplusplus
}
#endif

#endif /* end #define _BSP_PMU_H_*/
