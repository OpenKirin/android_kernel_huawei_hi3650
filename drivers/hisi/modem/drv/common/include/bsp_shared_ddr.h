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
#ifndef __BSP_SHARED_DDR_H__
#define __BSP_SHARED_DDR_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "product_config.h"
#include "bsp_memmap.h"
#include "bsp_s_memory.h"
#include "bsp_ddr.h"

/* shared  DDR */
#ifndef HI_SHARED_DDR_BASE_ADDR
#define HI_SHARED_DDR_BASE_ADDR           MDDR_FAMA(DDR_SHARED_MEM_ADDR)
#endif

#ifndef HI_SHARED_DDR_SIZE
#define HI_SHARED_DDR_SIZE                (DDR_SHARED_MEM_SIZE)
#endif

/*****************************************************************************************************************************
*�����ڴ����ַ
******************************************************************************************************************************/
#if !defined(__KERNEL__) && !defined(__OS_VXWORKS__) && !defined(__OS_RTOSCK__)
#define SHM_BASE_ADDR                  (HI_SHARED_DDR_BASE_ADDR)
#else
#define SHM_BASE_ADDR                  (g_mem_ctrl.sddr_virt_addr)
#define SHD_DDR_V2P(addr)              (void *)((unsigned long)(addr) - (unsigned long)g_mem_ctrl.sddr_virt_addr + (unsigned long)g_mem_ctrl.sddr_phy_addr)
#define SHD_DDR_P2V(addr)              (void *)((unsigned long)(addr) - (unsigned long)g_mem_ctrl.sddr_phy_addr + (unsigned long)g_mem_ctrl.sddr_virt_addr)
#endif
/*****************************************************************************************************************************
*��ģ�鶨���ƫ�ƺʹ�С,ƫ�ƶ���:SHM_OFFSET_XXX  ��С����:SHM_SIZE_XXXX������������KB������� SHM_OFFSET_SLICE_MEM ���
******************************************************************************************************************************/
#define SHM_OFFSET_HIFI_MBX		    	(0x0)

#define SHM_OFFSET_HIFI		    		(SHM_OFFSET_HIFI_MBX + SHM_SIZE_HIFI_MBX)

#define SHM_OFFSET_TLPHY                (SHM_OFFSET_HIFI + SHM_SIZE_HIFI)

#define SHM_OFFSET_TEMPERATURE	    	(SHM_OFFSET_TLPHY + SHM_SIZE_TLPHY)

#define SHM_OFFSET_DDM_LOAD				(SHM_OFFSET_TEMPERATURE + SHM_SIZE_TEMPERATURE)

/* v7r2 a9_boot_addr ���뷽ʽ�����ã���Ҫ64/32/16KB/8KB���� */
/* 64Kȫռ�� */
#define SHM_OFFSET_APPA9_PM_BOOT        (SHM_OFFSET_DDM_LOAD + SHM_SIZE_DDM_LOAD)

#define SHM_OFFSET_MDMA9_PM_BOOT        (SHM_OFFSET_APPA9_PM_BOOT + SHM_SIZE_MEM_APPA9_PM_BOOT)

/*CT BT*/
#define SHM_OFFSET_TENCILICA_MULT_BAND  (SHM_OFFSET_MDMA9_PM_BOOT + SHM_SIZE_MEM_MDMA9_PM_BOOT)

/* �ܴ�СΪ236KB, ����, GUͨ��192KB, Lͨ��40KB, icc���ƽṹ��Ϊҳ����ȡΪ4KB */
#define SHM_OFFSET_ICC                  (SHM_OFFSET_TENCILICA_MULT_BAND + SHM_SIZE_TENCILICA_MULT_BAND)

/* �ܴ�СΪ64KB, ����, ���ڴ�AXI(SRAM)�ƹ�����IPF��������IPF�͹��ĵļĴ�������ָ�, �׵�ַҪ��8�ֽڶ��� */
#define SHM_OFFSET_IPF             	    (SHM_OFFSET_ICC + SHM_SIZE_ICC)

#define SHM_OFFSET_PSAM             	(SHM_OFFSET_IPF + SHM_SIZE_IPF)

#define SHM_OFFSET_WAN             	    (SHM_OFFSET_PSAM + SHM_SIZE_PSAM)

#define SHM_OFFSET_NV				    (SHM_OFFSET_WAN + SHM_SIZE_WAN)

#define SHM_OFFSET_M3_MNTN		    	(SHM_OFFSET_NV + SHM_SIZE_NV)

#define SHM_OFFSET_TIMESTAMP			(SHM_OFFSET_M3_MNTN + SHM_SIZE_M3_MNTN)

#define SHM_OFFSET_IOS		            (SHM_OFFSET_TIMESTAMP + SHM_SIZE_TIMESTAMP)

#define SHM_OFFSET_RESTORE_AXI          (SHM_OFFSET_IOS + SHM_SIZE_IOS)

/* ��ѹԴ���Կ��Ʊ���С��Ԥ����ʵ��ʹ��Ϊ0x85c */
#define SHM_OFFSET_PMU                  (SHM_OFFSET_RESTORE_AXI + SHM_SIZE_RESTORE_AXI)

/* ������ */
#define SHM_OFFSET_PTABLE               (SHM_OFFSET_PMU + SHM_SIZE_PMU)

/* modem ������λ��� */
#define SHM_OFFSET_CCORE_RESET          (SHM_OFFSET_PTABLE + SHM_SIZE_PTABLE)

/* pm om log�� */
#define SHM_OFFSET_PM_OM                (SHM_OFFSET_CCORE_RESET + SHM_SIZE_CCORE_RESET)

#define SHM_OFFSET_M3PM            (SHM_OFFSET_PM_OM + SHM_SIZE_PM_OM)

/*���ڷ��䲻����KB����ķ���*/
#define SHM_OFFSET_SLICE_MEM            (SHM_OFFSET_M3PM + SHM_SIZE_M3PM)

#define SHM_OFFSET_OSA_LOG            (SHM_OFFSET_SLICE_MEM + SHM_SIZE_SLICE_MEM)

#define SHM_OFFSET_WAS_LOG            (SHM_OFFSET_OSA_LOG + SHM_SIZE_OSA_LOG)

/* sram needs store/restore since hi6950 because of sram powerdown */
#define SHM_OFFSET_SRAM_BAK             (SHM_OFFSET_WAS_LOG + SHM_SIZE_WAS_LOG)  

/* for sec, move sram to ddr */
#define SHM_OFFSET_SRAM_TO_DDR          (SHM_OFFSET_SRAM_BAK + SHM_SIZE_SRAM_BAK)

#define SHM_OFFSET_M3RSRACC_BD             (SHM_OFFSET_SRAM_TO_DDR + SHM_SIZE_SRAM_TO_DDR) 

/* �绰��ʹ���ڴ� */
#define SHM_OFFSET_SIM_MEMORY           (SHM_OFFSET_M3RSRACC_BD + SHM_SIZE_M3RSRACC_BD)

/*�����ڴ�ʣ�ಿ��ƫ�ƺʹ�С*/
#define SHM_OFFSET_MEMMGR               (SHM_OFFSET_SIM_MEMORY + SHM_SIZE_SIM_MEMORY)
#define SHM_SIZE_MEMMGR                 (DDR_SHARED_MEM_SIZE - SHM_OFFSET_MEMMGR)

/**************************************���ڷ��䲻����Kb����ķ���*******************************************************
*����С�ڴ�ķ��䶼����SHM_OFFSET_SLICE_MEM �ڷ��䣬ĿǰSHM_OFFSET_SLICE_MEM��С0x1000,����ע�ⲻҪ����
************************************************************************************************************************/
#define SHM_SIZE_MEMMGR_FLAG            (0x180)
#define SHM_OFFSET_MEMMGR_FLAG          (SHM_OFFSET_SLICE_MEM)

#define SHM_SIZE_SYNC                   (0x60)
#define SHM_OFFSET_SYNC             	(SHM_OFFSET_MEMMGR_FLAG + SHM_SIZE_MEMMGR_FLAG)

#define SHM_SIZE_AT_FLAG                (0x4)
#define SHM_OFFSET_AT_FLAG              (SHM_OFFSET_SYNC + SHM_SIZE_SYNC)

#define SHM_SIZE_CSHELL_FLAG            (0x4)
#define SHM_OFFSET_CHSELL_FLAG          (SHM_OFFSET_AT_FLAG + SHM_SIZE_AT_FLAG)

#define SHM_SIZE_DSP_FLAG               (0x4)
#define SHM_OFFSET_DSP_FLAG             (SHM_OFFSET_CHSELL_FLAG + SHM_SIZE_CSHELL_FLAG)

#define SHM_SIZE_CDSP_FLAG               (0x4)
#define SHM_OFFSET_CDSP_FLAG             (SHM_OFFSET_DSP_FLAG + SHM_SIZE_DSP_FLAG)

/*FIQ */
#define SHM_SIZE_CCORE_FIQ          (0x4*40)
#define SHM_OFFSET_CCORE_FIQ        (SHM_OFFSET_CDSP_FLAG + SHM_SIZE_CDSP_FLAG)

/* modem ������ */
#define SHM_SIZE_LOADM                  (0x0C)
#define SHM_OFFSET_LOADM                (SHM_OFFSET_CCORE_FIQ + SHM_SIZE_CCORE_FIQ)

/*bbp power flag*/
#define SHM_SIZE_MEMREPAIR              (0x20)
#define SHM_OFFSET_MEMREPAIR            (SHM_OFFSET_LOADM + SHM_SIZE_LOADM)
/* nand spec info */
#define SHM_SIZE_NAND_SPEC              (24)
#define SHM_OFFSET_NAND_SPEC            (SHM_OFFSET_MEMREPAIR + SHM_SIZE_MEMREPAIR)

#define SHM_SIZE_VERSION                (0x20)
#define SHM_OFFSET_VERSION              (SHM_OFFSET_NAND_SPEC + SHM_SIZE_NAND_SPEC)

#define SHM_SIZE_UART_FLAG              (0xC)
#define SHM_OFFSET_UART_FLAG            (SHM_OFFSET_VERSION + SHM_SIZE_VERSION)

/* m3pm om */
#define SHM_SIZE_M3PM_LOG               (0x80)
#define SHM_OFFSET_M3PM_LOG             (SHM_OFFSET_UART_FLAG + SHM_SIZE_UART_FLAG)


/* autotest pan_rpc */
#define SHM_SIZE_PAN_RPC                (0x4)
#define SHM_OFFSET_PAN_RPC              (SHM_OFFSET_M3PM_LOG + SHM_SIZE_M3PM_LOG)
#define SHM_SIZE_MODEM_SR_STAMP         (0x170)
#define SHM_OFFSET_MODEM_SR_STAMP       (SHM_OFFSET_PAN_RPC + SHM_SIZE_PAN_RPC)


#define SHM_SIZE_TSENSOR_STAMP         (0x10)
#define SHM_OFFSET_TSENSOR_STAMP       (SHM_OFFSET_MODEM_SR_STAMP + SHM_SIZE_MODEM_SR_STAMP)

/* rffe via modem is active*/
#define SHM_SIZE_RFFE_VIA_LP_FLAG       (0X4)
#define SHM_OFFSET_RFFE_VIA_LP_FLAG     (SHM_OFFSET_TSENSOR_STAMP + SHM_SIZE_TSENSOR_STAMP)

#ifndef CONFIG_MODULE_BUSSTRESS
#define SHM_SIZE_BUSSTRESS_TEST         (70*1024)
#else
#define SHM_SIZE_BUSSTRESS_TEST         (0)
#endif

#define SHM_OFFSET_BUSSTRESS_TEST       (SHM_OFFSET_RFFE_VIA_LP_FLAG + SHM_SIZE_RFFE_VIA_LP_FLAG)

/*deflate*/
#ifndef  CONFIG_DEFLATE
#define SHM_SIZE_DEFLATE                (2*1024)
#else
#define SHM_SIZE_DEFLATE                (0)
#endif
#define SHM_OFFSET_DEFLATE              (SHM_SIZE_BUSSTRESS_TEST + SHM_OFFSET_BUSSTRESS_TEST)
/*****************************************************************************************************************************
*��ȫ�����ڴ���Դ����
******************************************************************************************************************************/
#if (defined(__FASTBOOT__) || defined(__OS_RTOSCK__)) && defined(DDR_SEC_SHARED_ADDR)
#define SHM_SEC_BASE_ADDR          (DDR_SEC_SHARED_ADDR)
#define SHM_SEC_SIZE               (DDR_SEC_SHARED_SIZE)

#define SHM_SIZE_PROTECT_BARRIER   (0x1000)     /* Ԥ��(4K)��ֹ���ȣ���ʼ��ΪȫF */
#define SHM_OFFSET_PROTECT_BARRIER (0x0)

#define SHM_SIZE_PARAM_CFG         (0x4000)     /* ���밲ȫOS�����ò���Ԥ��(16K)��С */
#define SHM_OFFSET_PARAM_CFG       (SHM_OFFSET_PROTECT_BARRIER + SHM_SIZE_PROTECT_BARRIER)

#define SHM_SIZE_SEC_ICC           (0x20000)     /* ��ȫICCʹ��(128K)��С */
#define SHM_OFFSET_SEC_ICC         (SHM_OFFSET_PARAM_CFG + SHM_SIZE_PARAM_CFG)
#endif



#ifdef __cplusplus
}
#endif

#endif    /* __BSP_SHARED_DDR_H__ */



