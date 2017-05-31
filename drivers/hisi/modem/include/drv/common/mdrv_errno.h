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

#ifndef _MDRV_ERRNO_H_
#define _MDRV_ERRNO_H_

#ifdef _cplusplus
extern "C"
{
#endif

/* �������system_error��module id���� */
typedef enum _mdrv_errno_e
{
    DRV_ERRNO_DUMP_ARM_EXC      = 0x1000,   /* arm�쳣 */
    DRV_ERRNO_DUMP_CP_WDT       = 0x1001,   /* cp watch dog�쳣 */
    DRV_ERRNO_DUMP_AP_WDT       = 0x1002,   /* ap watch dog�쳣 */
    DRV_ERRNO_DUMP_M3_WDT       = 0x1003,   /* m3 watch dog�쳣 */
    DRV_ERRNO_DUMP_TEEOS_WDT    = 0x1004,   /* teeos watch dog�쳣 */
    DRV_ERRNO_ICC_RING_BUFFER   = 0x1010,   /* iccѭ��buffer���� */
    DRV_ERRNO_PMU_OVER_CUR      = 0x1020,   /* pmu���� */
    DRV_ERRNO_PMU_OVER_TEMP     = 0x1021,   /* pmu���� */
    DRV_ERRNO_PMU_UNDEF_VOL     = 0x1022,   /* pmuǷѹ */
    DRV_ERRNO_NV_ICC_FIFO_FULL  = 0x1030,   /* nv iccͨ���� */
    DRV_ERRNO_AMON_SOC_WR       = 0x1040,   /* amon socд�����쳣 */
    DRV_ERRNO_AMON_SOC_RD       = 0x1041,   /* amon soc�������쳣 */
    DRV_ERRNO_AMON_CPUFAST_WR   = 0x1042,   /* amon fastд�����쳣 */
    DRV_ERRNO_AMON_CPUFAST_RD   = 0x1043,   /* amon fast�������쳣 */
    DRV_ERRNO_MBX_WR_FULL       = 0x1050,   /* ���������� */
    DRV_ERRNO_MBX_DSP_IPC       = 0x1051,   /* ������������DSP IPC֪ͨARM */
    DRV_ERRNO_MBX_PS_TIMEOUT    = 0x1052,   /* PS��DSP��Ϣ��ʱ */
    DRV_ERRNO_MBX_UP_WR         = 0x1053,   /* ��������дָ���쳣 */
    DRV_ERRNO_MBX_DL_MOD        = 0x1054,   /* ���������ָ��MOD�쳣 */
    DRV_ERRNO_RESET_SIM_SWITCH  = 0x1060,   /* �п������modem������λ */
    DRV_ERRNO_RESET_RILD        = 0x1061,   /* RILD�����modem������λ */
    DRV_ERRNO_RESET_3RD_MODEM   = 0x1062,   /* 3rd modem����ķ���ĵ�����λ */
    DRV_ERRNO_RESET_REBOOT_REQ  = 0x1063,   /* modem������λΪ׮ʱ��������λ */
    DRV_ERRNO_WATCHPOINT        = 0x1070,   /* watchpoint������λ */
    DRV_ERRNO_PDLOCK            = 0x1071,   /* pdlock������λ*/
    DRV_ERRNO_XMBX_WR_FULL      = 0x1072,   /* CPHY ���������� */
    DRV_ERRNO_XMBX_DSP_IPC      = 0x1073,   /* CPHY ������������DSP IPC֪ͨARM */
    DRV_ERRNO_XMBX_PS_TIMEOUT   = 0x1074,   /* CPHY PS��DSP��Ϣ��ʱ */
    DRV_ERRNO_XMBX_UP_WR        = 0x1075,   /* CPHY ��������дָ���쳣 */
    DRV_ERRNO_XMBX_DL_MOD       = 0x1076,   /* CPHY ���������ָ��MOD�쳣 */
    DRV_ERROR_LCD_VCC           = 0x1077,    /* PMU������Դ�رգ�vcc��ʧ */
    DRV_ERROR_USER_RESET        = 0x1078,    /* �û�����ĸ�λ*/
    DRV_ERRNO_PAN_RPC           = 0x1080,   /* PAN_RPC ��ʼ��ʧ�ܸ�λ */
    DRV_ERRNO_NV_CRC_ERR        = 0x1081,   /* ��ȡNV�ļ����� */
    DRV_ERRNO_IPF_OUT_REG		= 0x1082,	/* ipf ����Խ��*/
    DRV_ERRNO_PSAM_OUT_REG		= 0x1083,	/* PSAM ����Խ��*/
    DRV_ERRNO_NV_LIST_FULL      = 0x1084,   /* NV ����дNV list��  */
    DRV_ERRNO_CLK_EXCEPT        = 0x1085,   /* PLLֹͣ�쳣 & PLL�����쳣*/
	DRV_ERRNO_MODEM_RST_FAIL    = 0x1086,   /*Modem ������λ��,�ص�DRVʧ��*/
    DRV_ERRNO_BBP_IPC_TIMEOUT   = 0x1087,   /* BBP��ȡ�˼�����ʱ */
    DRV_ERRNO_BUTT              = 0x1FFF
}mdrv_errno_enum;

#ifdef _cplusplus
}
#endif
#endif


