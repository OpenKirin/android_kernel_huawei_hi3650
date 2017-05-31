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
#ifndef __BSP_OM_H__
#define __BSP_OM_H__

#ifdef __cplusplus
extern "C" {
#endif

#if defined(__KERNEL__)
#include <linux/kernel.h>
#include <asm/string.h>
#endif

#include "product_config.h"
#include "osl_common.h"
#include <stdarg.h>
#include "drv_comm.h"

#ifdef __OS_RTOSCK__
#include "sre_shell.h"
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define BSP_OM_MODU_ID                     THIS_MODU_ID


/*SOCPͷSID:����HiStudio�����Modem������״̬*/
#define BSP_SOCP_SID_DIAG_SERVER          (0x2) /* DIAG Service�����������Ϣ���*/

/*SOCPͷ usSSId:����λ����,����λ;SSIDָ��App CPU*/
#define BSP_SOCP_HIGH4BIT_SSID_ACPU       (0x1)
#define BSP_SOCP_HIGH4BIT_SSID_MCPU       (0x2)      /*Modem*/
#define BSP_SOCP_HIGH4BIT_SSID_M3         (0xA)      /* M3 */

/*SOCPͷ ucServiceSessionId:��ʶService��Client֮�������*/
#define BSP_SOCP_SERVER_SESSION_ID        (0x1) /* Service Session ID�̶�Ϊ1*/

/*SOCPͷ ucMsgType: ��ʾ��Ϣ���ͣ���6���ر�������Ϊ0����2����ȡֵ����*/
#define BSP_SOCP_MSG_TYPE_REQ             (0x1) /* ����*/
#define BSP_SOCP_MSG_TYPE_CNF             (0x2) /* ��Ӧ*/
#define BSP_SOCP_MSG_TYPE_IND             (0x3) /* �ϱ�*/


/* �ṹ��ID�����һ��������λ(28~31)���ֶ�*/
#define BSP_STRU_ID_28_31_GROUP_MSP  (0x1)
#define BSP_STRU_ID_28_31_GROUP_BSP    (0x9)

/* �ṹ��ID����Ķ���������λ(16_23)���ֶ�,��Ӧ��һ���ֶ���BSP_STRU_ID_28_31_GROUP_BSP*/
#define BSP_STRU_ID_16_23_BSP_CMD         (0x1) /* BSP�ڲ��������*/
#define BSP_STRU_ID_16_23_BSP_CPU         (0x2) /* CPUռ���������ϱ�*/
#define BSP_STRU_ID_16_23_BSP_PRINT       (0x3) /* BSP ��ӡ��Ϣ*/
#define BSP_STRU_ID_16_23_BSP_MEM         (0x4) /* BSP�ڴ�TRACEA�ϱ�*/
#define BSP_STRU_ID_16_23_BSP_TASK        (0x5) /* ϵͳ����(�����ж�)������Ϣ�ϱ�*/
#define BSP_STRU_ID_16_23_BSP_CMD_IND   (0x5) /* ����������ϱ���Ϊ������HSO��id����Ϊ5*/
#define BSP_STRU_ID_16_23_BSP_INT_LOCK    (0x6) /* ϵͳ���жϵ�����Ϣ�ϱ�*/
#define BSP_STRU_ID_16_23_BSP_AMON        (0x7) /* AXI Monitorʱ�䴰��ؽ����ϱ� */

#define CMD_BSP_SYSVIEW_IND_ACORE           (0x5310)
#define CMD_BSP_SYSVIEW_IND_CCORE           (0x5311)


/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/

/* ģ�鶨�� */
typedef enum _bsp_module_e
{
    BSP_MODU_ICC = 1,
    BSP_MODU_IPF,
    BSP_MODU_UDI,
    BSP_MODU_DLOAD,
    BSP_MODU_SYNC,
    BSP_MODU_OM,
    BSP_MODU_DUMP,
    BSP_MODU_SOCP,
    BSP_MODU_OMS,
    BSP_MODU_LOG,
    BSP_MODU_SYSVIEW,
    BSP_MODU_RFILE,
    BSP_MODU_MBX,
    BSP_MODU_OTHER_CORE,
    BSP_MODU_SCI,
    BSP_MODU_NV,
    BSP_MODU_SOFTTIMER,
    BSP_MODU_HARDTIMER,
    BSP_MODU_MIPI,
    BSP_MODU_BBP,
    BSP_MODU_DPM,
    BSP_MODU_IPC,
	BSP_MODU_I2C,
    BSP_MODU_RTC,
    BSP_MODU_HI6551_RTC,
    BSP_MODU_MEM,
    BSP_MODU_EARLYSUSPEND,
	BSP_MODU_AMON,
    BSP_MODU_TEST,
	BSP_MODU_LCD,
    BSP_MODU_EMI,
	BSP_MODU_VERSION,
	BSP_MODU_SPI,
	BSP_MODU_PMU,
    BSP_MODU_CLK,
    BSP_MODU_REGULATOR,
    BSP_MUDU_CPUFREQ,
	BSP_MUDU_WDT,
    BSP_MODU_WAKELOCK,
    BSP_MODU_VIC,
    BSP_MODU_CSHELL,
    BSP_MODU_CIPHER,
    BSP_MODU_ACC,
    BSP_MODU_SECURITY,
    BSP_MODU_AT_UART,
    BSP_MODU_EDMA,
    BSP_MODU_UTRACE,
    BSP_MODU_ABB,
    BSP_MODU_DSP,
    BSP_MODU_HKADC,
    BSP_MODU_GPIO,
    BSP_MODU_IOS,
    BSP_MODU_EFUSE,
    BSP_MODU_DDM,
    BSP_MODU_KEY,
    BSP_MODU_ANTEN,
    BSP_MODU_RSE,
    BSP_MODU_TSENSOR,
    BSP_MODU_TEMPERATURE,
    BSP_MODU_PM,
    BSP_MODU_COUL,
	BSP_MODU_HWADP,
    BSP_MODU_ADP_DPM,
    BSP_MODU_M3_CPUFREQ,
    BSP_MODU_LED,
    BSP_MODU_NAND,
    BSP_MODU_HIFIMBX,
    BSP_MODU_ONOFF,
    BSP_MODU_RESET,
    BSP_MODU_TUNER,
    BSP_MODU_HW_SPINLOCK,
    BSP_MODU_MEMREPAIR,
    BSP_MODU_DUAL_MODEM,
    BSP_MODU_PASTAR,
    BSP_MODU_HI6559_RTC,
    BSP_MODU_HSUART,
    BSP_MODU_PARF,
    BSP_MODU_SC,
    BSP_MODU_OF,
    BSP_MODU_PSAM,
    BSP_MODU_SYSCTRL,
    BSP_MODU_STRESS,
    BSP_MODU_L2CACHE,
    BSP_MODU_PM_OM,
    BSP_MODU_PAN_RPC,
    BSP_MODU_CROSS_MIPI,
    BSP_MODU_WATCHPOINT,
    BSP_MODU_PDLOCK,
	BSP_MODU_XMBX,
	BSP_MODU_GCOV,
	BSP_MODU_SYS_BUS,
	BSP_MODU_LOADPS,
	BSP_MODU_CDSP,
	BSP_MODU_TLDSP,
	BSP_MODU_DSPDVS,
	BSP_MODU_RSRACC,
	BSP_MODU_THERMAL_UP,
	BSP_MODU_DSPDFS,
    BSP_MODU_ALL,   /* �������е�ģ�� */
    BSP_MODU_MAX = 128    /* �߽�ֵ */
} bsp_module_e;


typedef enum _bsp_log_level_e
{
    BSP_LOG_LEVEL_DEBUG = 0,  /* 0x0:debug-level                                  */
    BSP_LOG_LEVEL_INFO,      /* 0x1:informational                                */
    BSP_LOG_LEVEL_NOTICE,     /* 0x2:normal but significant condition             */
    BSP_LOG_LEVEL_WARNING,    /* 0x3:warning conditions                           */
    BSP_LOG_LEVEL_ERROR,      /* 0x4:error conditions                             */
    BSP_LOG_LEVEL_CRIT,       /* 0x5:critical conditions                          */
    BSP_LOG_LEVEL_ALERT,      /* 0x6:action must be taken immediately             */
    BSP_LOG_LEVEL_FATAL,      /* 0x7:just for compatibility with previous version */
    BSP_LOG_LEVEL_MAX         /* �߽�ֵ */
} bsp_log_level_e;

typedef enum
{
    BSP_SYSVIEW_MEM_TRACE       = 1,
    BSP_SYSVIEW_CPU_INFO        = 2,
    BSP_SYSVIEW_TASK_INFO       = 3,
    BSP_SYSVIEW_INT_LOCK_INFO   = 4,
    BSP_SYSVIEW_SWT_ALL         = 0xf,
    BSP_SYSVIEW_SWT_MAX         /* �߽�ֵ */
} bsp_sysview_type_e;


/*****************************************************************************
  2 ��������
*****************************************************************************/

/* ��ӡ�ӿڣ����trace��HSO*/
#ifdef ENABLE_BUILD_OM
void bsp_trace(bsp_log_level_e log_level, bsp_module_e mod_id, char *fmt,...);

/* ��¼�쳣���ļ�*/
void error_log(char *fmt ,...);
void print2file(char* filename, char *fmt,...);
int dmesg_write(const char* buffer, const unsigned len);

typedef int (*print_hook)(char *out_char);
void balongv7r2_uart_register_hook(print_hook hook);

void uart_register_hook(print_hook hook);

void bsp_socp_chan_enable(void);

s32 bsp_om_server_init(void);

u32 om_timer_get(void);

u32 om_timer_tick_get(void);

u32 bsp_mod_level_set(bsp_module_e  mod_id ,u32 print_level);

void bsp_om_set_hso_conn_flag(u32 flag);

u32 sysview_get_all_task_name(void *p_task_stru,u32 param_len);

u32  bsp_sysview_swt_set(bsp_sysview_type_e set_type,u32 set_swt,u32 period);

int dmesg_init(void);

/* drx mntn callback */
void bsp_log_bin_ind(s32 str_id, void * ind_data, u32 ind_data_size);

u32 bsp_log_module_cfg_get(bsp_module_e mod_id);

void bsp_print2dmsg(char *fmt, ...);

#else
void bsp_trace(bsp_log_level_e log_level, bsp_module_e mod_id, char *fmt,...);
u32 bsp_log_module_cfg_get(bsp_module_e mod_id);
u32 bsp_mod_level_set(bsp_module_e  mod_id ,u32 print_level);

static void inline error_log(char *fmt ,...)
{
    return;
}

static void inline print2file(char* filename, char *fmt,...)
{
    return;
}

static int inline dmesg_write(const char* buffer, const unsigned len)
{
    return 0;
}

static void inline bsp_socp_chan_enable(void)
{
    return;
}

typedef int (*print_hook)(char *out_char);

static s32 inline bsp_om_server_init(void)
{
    return 0;
}

static u32 inline om_timer_get(void)
{
    return 0;
}
static u32 inline om_timer_tick_get(void)
{
    return 0;
}
static void inline bsp_log_bin_ind(s32 str_id, void * ind_data, u32 ind_data_size)
{
    return;
}
static inline void dmesg_init(void)
{
    return;
}

static void bsp_print2dmsg(fmt, ...)
{
    return;
}


#endif

#ifdef __cplusplus
}
#endif


#endif




