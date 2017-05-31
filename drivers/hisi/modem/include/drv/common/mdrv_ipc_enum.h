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

#ifndef __MDRV_IPC_ENUM_H__
#define __MDRV_IPC_ENUM_H__
#ifdef __cplusplus
extern "C"
{
#endif

/* ����������*/
typedef enum tagIPC_INT_CORE_E
{
    IPC_CORE_ARM11 = 0x0,   /* P500�ϵ�IPC */
    IPC_CORE_A9,
    IPC_CORE_CEVA,
    IPC_CORE_TENS0,
    IPC_CORE_TENS1,
    IPC_CORE_DSP,
    IPC_CORE_APPARM = 0x0,  /* V7R1/V3R2�ϵ�IPC */
    IPC_CORE_COMARM,
    IPC_CORE_LTEDSP,
    IPC_CORE_VDSP,
    IPC_CORE_ZSP,
    IPC_CORE_DSP_GU,
    IPC_CORE_ACPU = 0x0,    /* V9R1 SFT�ϵ�IPC */
    IPC_CORE_CCPU,
    IPC_CORE_MCU,
    IPC_CORE_HIFI,
    IPC_CORE_BBE16,
    IPC_CORE_ACORE = 0x0,   /*P531,V7R2*/
    IPC_CORE_CCORE,
    IPC_CORE_MCORE,
    IPC_CORE_LDSP,
    IPC_CORE_HiFi,
    IPC_CORE_BBE,           /*..5..P531\V7R2...........P531..*/
    IPC_CORE0_A15,
    IPC_CORE1_A15,
    /* !!!!����Ԫ������ӵ����  */
    IPC_CORE_BUTTOM
}IPC_INT_CORE_E;

/*********************************************************
*  �����IPC��Դ��ö��������ʽ:
*  IPC_<Ŀ�괦����>_INT_SRC_<Դ������>_<����/����>
*  Ŀ�괦����:ACPU��CCPU��MCU��HIFI��BBE16
*  Դ������  :ACPU��CCPU��MCU��HIFI��BBE16
*  ����/���� :
*********************************************************/
typedef enum tagIPC_INT_LEV_E
{
    IPC_CCPU_INT_SRC_HIFI_MSG              = 0, /* HIFI�����Ϣ֪ͨ */
    IPC_CCPU_INT_SRC_MCU_MSG               = 1, /* MCU�����Ϣ֪ͨ */
    IPC_INT_DSP_HALT                       = 2, /* DSP֪ͨARM˯��*/
    IPC_INT_DSP_RESUME                     = 3, /* DSP֪ͨARM��ɻ��Ѻ�Ļָ�����*/
                                                /* 4, ռλ�������������ֵ,��ֵ������IPC_INT_DICC_USRDATAһ��*/
                                                /* 5, ռλ�������������ֵ,��ֵ������IPC_INT_DICC_USRDATAһ��*/
    IPC_INT_WAKE_GU                        = 6, /* ��ģ���Ѵ�ģ�ж�*/
    IPC_INT_SLEEP_GU                          , /* ��ģ˯���ж�*/
    /* ����TDSʹ�õ�����IPC�ж�,begin */
    IPC_INT_WAKE_SLAVE                       , /* BBE16֪ͨCCPU,����GSM��ģ */
    IPC_CCPU_INT_SRC_DSP_DVS,                  /* BBE16֪ͨCCPU��BBP��dsp���е�ѹ */
    IPC_INT_DSP_PS_PUB_MBX                 = 10,/* ����DSP->ARM,��͹���IPC�жϸ��� */
    IPC_INT_DSP_PS_MAC_MBX                 ,/* ����DSP->ARM,��͹���IPC�жϸ��� */
    IPC_INT_DSP_MBX_RSD                    ,/* ����DSP->ARM,��͹���IPC�жϸ��� */
    IPC_CCPU_INT_SRC_DSP_MNTN              ,/* BBE16��ά�ɲ��ж�֪ͨmailbox���޾�ǿ */
    IPC_CCPU_INT_SRC_DSP_RCM_PUB_MBX       ,
    /* ����TDSʹ�õ�����IPC�ж�,end */
    IPC_CCPU_INT_SDR_CCPU_BBP_MASTER_ERROR , /* BBE16֪ͨC�˷�����ͨ���쳣 */
    IPC_CCPU_INT_SRC_COMMON_END            , /* V7��V8���е�C�˽����жϺŽ��� */

    /* C�˽��գ�v7  ���е� ipc �ж� */
    IPC_CCPU_INT_SRC_ACPU_RESET            = IPC_CCPU_INT_SRC_COMMON_END,    /* A/C����C�˵�����λ�ڼ�˼�ͨ��(����C��), v8r2�ߵ��Ǻ˼���Ϣ */
    IPC_CCPU_SRC_ACPU_DUMP                 ,   /* v7r2 ��ά�ɲ⣬ACPU ���͸�CCPU ��IPC�ж� */
    IPC_CCPU_INT_SRC_ICC_PRIVATE           ,   /* v7r2 ICCͨ�ţ�iccר�÷�����Ϣʹ��,ACPU���͸�CCPU��IPC�ж�       */
    IPC_CCPU_INT_SRC_MCPU                  ,   /* ICC��Ϣ, MCU���͸�CCPU��  IPC�ж� */
    IPC_CCPU_INT_SRC_MCPU_WDT              ,   /* ����traceʱͣwdt */
    IPC_CCPU_INT_SRC_XDSP_1X_HALT          ,   /* 1X Halt�ж� */
    IPC_CCPU_INT_SRC_XDSP_HRPD_HALT        ,   /* HRPD Halt�ж� */
    IPC_CCPU_INT_SRC_XDSP_1X_RESUME        ,   /* 1X Resume�ж� */
	IPC_CCPU_INT_SRC_XDSP_HRPD_RESUME      ,   /* HRPD Resume�ж� */
	IPC_CCPU_INT_SRC_XDSP_MNTN             ,   /* XDSP�����쳣ά���ж� */
	IPC_CCPU_INT_SRC_XDSP_PS_MBX           ,   /* PS��Xģ����ͨ��ʹ�õ��ж� */
    IPC_CCPU_INT_SRC_XDSP_RCM_MBX          ,   /* RCM��Xģ����ͨ��ʹ�õ��ж� */

	/*  austin��Ŀ�� mcu ͨ��ʹ�� icc �жϺ�, ���ܱ�� */
    IPC_CCPU_INT_SRC_ACPU_ICC			   = 31, /* acpu����ccpu�ж�*/

    /*  ��ȫICCͨ��ʹ���жϺ�, ���ܱ�� */
    IPC_CCPU_INT_SRC_SECOS_ICC_IFC         = 32, /* ��Ӧ��ȫIPC��0���жϣ���ȫICC����ͨ���ж� */
    IPC_CCPU_INT_SRC_SECOS_ICC_VSIM        = 33, /* ��Ӧ��ȫIPC��1���жϣ���ȫICC���ͨͨ���ж� */

	/* C�˽��գ�v8 ���е�ipc �ж� */
    IPC_CCPU_INT_SRC_ACPU_MSG              = IPC_CCPU_INT_SRC_COMMON_END,      /* ͨ��mailbox,�����ڲ�ʹ��*/
    IPC_CCPU_INT_SRC_ACPU_IFC              ,      /* Զ�̺�������,�����ڲ�ʹ��*/
    IPC_CCPU_INT_SRC_MCU_IFC               ,      /* Զ�̺�������,�����ڲ�ʹ��*/
    IPC_INT_ARM_SLEEP                      ,      /* ˯�߻���ʹ��*/

    /* ����MCU IPC�����Ϣ�ж�Դbitλ�� */
    IPC_MCU_INT_SRC_ACPU_MSG             = 0,    /* ACPU�����Ϣ֪ͨ */
    IPC_MCU_INT_SRC_CCPU_MSG                ,    /* CCPU�����Ϣ֪ͨ */
    IPC_MCU_INT_SRC_HIFI_MSG                ,    /* HIFI�����Ϣ֪ͨ */
    IPC_MCU_INT_SRC_CCPU_IPF                ,    /* IPF�͹��� */
    IPC_MCU_INT_SRC_ACPU_PD                 ,    /* acpu power down */
    IPC_MCU_INT_SRC_HIFI_PD                 ,    /* hifi power down */
    IPC_MCU_INT_SRC_HIFI_DDR_VOTE           ,    /* HIFI DDR��ˢ��ͶƱ */
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLOW    ,
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_SLEEP   ,
    IPC_MCU_INT_SRC_ACPU_I2S_REMOTE_INVALID ,
    IPC_MCU_INT_SRC_COMMON_END              ,
    /* v7  ���е� ipc �ж� */
    /* ACPU��CCPU����IPC�ж�ʱ����Ҫͬʱ��֪��M3 */
    IPC_MCU_INT_SRC_ACPU_DRX                = IPC_MCU_INT_SRC_COMMON_END,
    IPC_MCU_INT_SRC_CCPU_DRX                ,   /* CCPU��ACPU����IPC�ж�ʱ����Ҫͬʱ��֪��M3 */
    IPC_MCU_INT_SRC_ICC_PRIVATE             ,   /* m3 icc˽�е�ipc�жϣ�������ͨ���������������� */
    IPC_MCU_INT_SRC_DUMP                    ,   /* m3 dump�жϣ�ACORE���͸�MCU��IPC�ж�*/
    IPC_MCU_INT_SRC_HIFI_PU                 ,   /* POWERUP,  HIFI���͸�MCU��IPC�ж� */
    IPC_MCU_INT_SRC_HIFI_DDR_DFS_QOS        , /* HIFI��DDR��ƵͶƱ */
    IPC_MCU_INT_SRC_TEST                    ,   /* for test a\c interact with m3 */
    IPC_MCPU_INT_SRC_ACPU_USB_PME_EN        ,  /* acore��M3ͨ��USB��������¼� */
    /* ����3��austin�޸ģ���AP���룬�����޸� */
	IPC_MCU_INT_SRC_ICC 				= 29,	/* m3 icc���õ�ipc�ж� */
	IPC_MCU_INT_SRC_CCPU_PD 			= 30,	 /* ccpu power down */
	IPC_MCU_INT_SRC_CCPU_START			= 31,	/* ֪ͨMCU����CCPU */


    /* v8 ���е�ipc �ж� */
    /* HIFI�����Ϣ֪ͨ,Զ�̺�������,�����ڲ�ʹ�� */
    IPC_MCU_INT_SRC_CCPU_IFC                    = IPC_MCU_INT_SRC_COMMON_END,
    IPC_MCU_INT_SRC_ACPU_IFC                    ,   /* ACPU��˺�������֪ͨ,�����ڲ�ʹ�� */
    IPC_MCU_INT_SRC_HIFI_IFC                    ,   /* HIFI��˺�������֪ͨ*/
    IPC_MCU_INT_SRC_ACPU0_PD                    ,   /* acpu0 power down, V8���� */
    IPC_MCU_INT_SRC_ACPU1_PD                    ,   /* acpu1 power down, V8���� */
    IPC_MCU_INT_SRC_ACPU2_PD                    ,   /* acpu2 power down, V8���� */
    IPC_MCU_INT_SRC_ACPU3_PD                    ,   /* acpu3 power down , V8����*/
    IPC_MCU_INT_SRC_ACPU4_PD                    ,   /* acpu4:cluster1 core0 power down */
    IPC_MCU_INT_SRC_ACPU5_PD                    ,   /* acpu5:cluster1 core1 power down */
    IPC_MCU_INT_SRC_ACPU6_PD                    ,   /* acpu6:cluster1 core2 power down */
    IPC_MCU_INT_SRC_ACPU7_PD                    ,   /* acpu7:cluster1 core3 power down */
    IPC_MCU_INT_SRC_ACPU_HOTPLUG                ,   /* acpu hotplug--no use, V8���� */
    IPC_MCU_INT_SRC_MCU_AGT                     ,   /* mcu agent */
    IPC_MCU_INT_SRC_HIFI_MEMSHARE_DDR_VOTE      ,   /* MP3���͹��Ĳ���ʹ��HARQMEM,HIFI DDR��ˢ��ͶƱ*/
    IPC_MCU_INT_SRC_HIFI_MEMSHARE_DDR_EXIT_VOTE ,   /* MP3���͹��Ĳ���ʹ��HARQMEM,HIFIͶƱDDR�˳���ˢ��*/
    IPC_MCU_INT_SRC_ACPU_DFS                    ,   /*ACPU DFS*/
    
    IPC_MCU_INT_SRC_END                         ,

    /* ����ACPU IPC�����Ϣ�ж�Դbitλ�� */
    IPC_ACPU_INT_SRC_CCPU_MSG             = 0,   /* CCPU�����Ϣ֪ͨ */
    IPC_ACPU_INT_SRC_HIFI_MSG             = 1,   /* HIFI�����Ϣ֪ͨ */
    IPC_ACPU_INT_SRC_MCU_MSG              = 2,   /* ACPU�����Ϣ֪ͨ */
    IPC_ACPU_INT_SRC_CCPU_NVIM            = 3,   /* ����NVIMģ��C����A��֮���ͬ��*/
    IPC_INT_DICC_USRDATA                  = 4,   /* ������CCPU�����жϺ�ͬʱ�޸�*/
    IPC_INT_DICC_RELDATA                  = 5,   /* ������CCPU�����жϺ�ͬʱ�޸�*/
    IPC_ACPU_INT_SRC_CCPU_ICC                ,
    IPC_ACPU_INT_SRC_COMMON_END              ,
    /* v7  ���е� ipc �ж� */
    IPC_ACPU_INT_SRC_ICC_PRIVATE          = IPC_ACPU_INT_SRC_COMMON_END,   /* v7r2 icc ˽�ã�CCPU���͸�ACPU��IPC�ж� */
    IPC_ACPU_SRC_CCPU_DUMP                ,   /* v7r2 ��ά�ɲ⣬CCPU ���͸�ACPU ��IPC�ж� */
    IPC_ACPU_INT_SRC_MCPU                 ,   /* ICC��Ϣ, MCU���͸�ACPU�� IPC�ж� */
    IPC_ACPU_INT_SRC_MCPU_WDT             ,  /* ����traceʱͣwdt */
    IPC_ACPU_INT_MCU_SRC_DUMP             ,  /* dump�ж�?MCU���͸�ACPU��IPC�ж� */
    IPC_ACPU_INT_SRC_CCPU_RESET_IDLE      ,  /* A/C����C�˵�����λ�ڼ�˼�ͨ��(master in idle)��Ҧ���� */
    IPC_ACPU_INT_SRC_CCPU_RESET_SUCC      ,  /* A/C����C�˵�����λ�ڼ�˼�ͨ��(ccore reset ok)��Ҧ���� */

    IPC_ACPU_INT_SRC_CCPU_LOG             ,  /* CCPU���͸�ACPU��LOG�����ж� */
    IPC_ACPU_INT_SRC_MCU_FOR_TEST         ,  /* test, m core to acore */
    IPC_ACPU_INT_SRC_CCPU_TEST_ENABLE     ,  /* IPC�Զ��������ж�ʹ��ʱʹ�ã�����IPC�жϲ���ʹ��ʱ����ɾ�� */
    IPC_ACPU_INT_SRC_MCPU_USB_PME         ,  /* M3��acore�ϱ�USB�����¼� */
    IPC_ACPU_INT_SRC_HIFI_PC_VOICE_RX_DATA,  /* hifi->acore pc voice */
    IPC_ACPU_INT_SRC_CCPU_PM_OM           ,  /* CCPU����ACPU��PMOM�ж�,����д�ļ�, Ҧ���� */

    /* v8 ���е�ipc �ж� */
    IPC_ACPU_INT_SRC_CCPU_IFC             = IPC_ACPU_INT_SRC_COMMON_END,       /* �����ڲ�ʹ��*/
    IPC_ACPU_INT_SRC_MCU_IFC              ,   /* �����ڲ�ʹ��*/
    IPC_ACPU_INT_SRC_MCU_THERMAL_HIGH     ,   /* MCU��طŵ���¹ػ�IPC�ж�֪ͨACPU, �ֻ��ڲ�ʹ��*/
    IPC_ACPU_INT_SRC_MCU_THERMAL_LOW      ,  /* MCU��طŵ���¹ػ�IPC�ж�֪ͨACPU*/
    IPC_ACPU_INI_SRC_MCU_TELE_MNTN_NOTIFY ,  /* �����ڲ�ʹ��,��ά���ɲ�*/
    IPC_ACPU_INI_SRC_MCU_EXC_REBOOT       ,  /* �����ڲ�ʹ��,��ά���ɲ�*/
    IPC_ACPU_INT_SRC_CCPU_EXC_REBOOT      ,  /* �����ڲ�CCPU �쳣���жϸ�ACPUfuwei*/
    IPC_ACPU_INT_SRC_CCPU_NORMAL_REBOOT   ,  /* �����ڲ�;*RIL֪ͨCfuwei, C��ͨ���ú���֪ͨA�˿��Ը�λ*/
    IPC_ACPU_INT_SRC_MCU_DDR_EXC          ,  /* �����ڲ�,MCU*/

    IPC_ACPU_INT_SRC_END              ,

    /* ����HIFI IPC�����Ϣ�ж�Դbitλ�� */
    IPC_HIFI_INT_SRC_ACPU_MSG = 0 ,  /* ACPU�����Ϣ֪ͨ */
    IPC_HIFI_INT_SRC_CCPU_MSG     ,  /* CCPU�����Ϣ֪ͨ */
    IPC_HIFI_INT_SRC_BBE_MSG      ,  /* TDDSP�����Ϣ֪ͨ */
    IPC_HIFI_INT_SRC_MCU_MSG      ,
    IPC_HIFI_INT_SRC_COMMON_END   ,
    
    /* v8 ���е�ipc �ж� */
    IPC_HIFI_INT_SRC_MCU_WAKE_DDR = IPC_HIFI_INT_SRC_COMMON_END,  /* MCU֪ͨHIFI����DDR */
    IPC_HIFI_INT_SRC_MCU_IFC      ,
    
    IPC_HIFI_INT_SRC_END          ,

    /* ����BBE16 IPC�����Ϣ�ж�Դbitλ�� */
    IPC_INT_MSP_DSP_OM_MBX = 0 ,   /* ����ARM->DSP */
    IPC_INT_PS_DSP_PUB_MBX     ,   /* ����ARM->DSP */
    IPC_INT_PS_DSP_MAC_MBX     ,   /* ����ARM->DSP */
    IPC_INT_HIFI_DSP_MBX       ,   /* HIFI->DSP */
    IPC_BBE16_INT_SRC_HIFI_MSG ,   /* ������Ϣ��HIFI���͸�BBE16��IPC�ж� */

    IPC_BBE16_INT_SRC_END  ,


    /* ����XDSP IPC�����Ϣ�ж�Դbitλ�� */
    IPC_XDSP_INT_SRC_CCPU_1X_WAKE = 0 ,   /* 1X Wake�ж� */
    IPC_XDSP_INT_SRC_CCPU_HRPD_WAKE   ,   /* HRPD Wake�ж� */
    IPC_XDSP_INT_SRC_CCPU_OM_MBX      ,   /* C��->XDSP */
    IPC_XDSP_INT_SRC_CCPU_PUB_MBX     ,   /* C��->XDSP */

	IPC_XDSP_INT_SRC_END ,   


    /* ������������� */
    IPC_INT_BUTTOM             = 64,
}IPC_INT_LEV_E;

typedef enum tagIPC_SEM_ID_E
{
    IPC_SEM_MEM          ,
    IPC_SEM_DICC         ,
    IPC_SEM_EMMC         ,
    IPC_SEM_SYNC         , 
    IPC_SEM_SYSCTRL      ,
    IPC_SEM_BBP          ,  /*��ֵ��BBE16����󶨣��޸���֪ͨBBE16����Ӧ�޸�*/
    IPC_SEM_RFILE_LOG    ,  /*����flashless��ά�ɲ�*/
    IPC_SEM_NVIM         ,
    IPC_SEM_EFUSE        , 
    IPC_SEM_DPDT_CTRL_ANT,  /* ���mdrv_ipc_spin_trylockʱ��� */
    IPC_SEM_BBPMASTER_0  ,
    IPC_SEM_BBPMASTER_1  ,
    IPC_SEM_BBPMASTER_2  ,
    IPC_SEM_BBPMASTER_3  ,
    IPC_SEM_BBPMASTER_5  ,
    IPC_SEM_BBPMASTER_6  ,
    IPC_SEM_BBPMASTER_7  ,
    IPC_SEM_COMMON_END   ,

    /* v7 ˽�е�IPC SEM */
    IPC_SEM_SPI0         = IPC_SEM_COMMON_END,
    IPC_SEM_NV           ,
    IPC_SEM_GPIO         ,
    IPC_SEM_CLK          ,
    IPC_SEM_PMU          ,
    IPC_SEM_MTCMOS       ,
    IPC_SEM_IPF_PWCTRL   ,
    IPC_SEM_PMU_FPGA     , /*����pmuоƬʱʹ��,��Ƭ��ʹ��*/
    IPC_SEM_NV_CRC       ,
    IPC_SEM_PM_OM_LOG    ,
    IPC_SEM_MDRV_LOCK    ,
    IPC_SEM_CDMA_DRX     , /* C����XDSPʹ�� */
    IPC_SEM_GU_SLEEP     ,
    IPC_SEM2_IPC_TEST    , /*IPC�Զ�������ʹ��*/
    IPC_SEM_DFS_FIX      = 31, /*M3 DFS��HIFI�������APB����ʹ��,��HI6950оƬƽ̨��ʹ��*/

    /* v8 ˽�е�IPC SEM */
    IPC_SEM_ICC          = IPC_SEM_COMMON_END,
    IPC_SEM_NAND         ,
    IPC_SEM_TELE_MNTN    ,
    IPC_SEM_MEDPLL_STATE ,
    IPC_SEM_SMP_CPU0     ,
    IPC_SEM_SMP_CPU1     ,
    IPC_SEM_SMP_CPU2     ,
    IPC_SEM_SMP_CPU3     ,
    IPC_SEM_CPUIDLE      ,   /*CPUIDLE A/M�˻�����Դ��*/
    IPC_SEM_BBPPS        ,   /*BBP PS���µ�ͶƱ*/
    IPC_SEM_HKADC        ,   /*A��M�˶�ȡHKADC�Ļ�����*/

    IPC_SEM_END          ,

    IPC_SEM_BUTTOM       = 32
} IPC_SEM_ID_E;

#ifdef __cplusplus
}
#endif

#endif
