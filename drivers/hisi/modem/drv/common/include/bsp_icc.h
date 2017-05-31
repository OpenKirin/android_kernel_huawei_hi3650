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
#ifndef __BSP_ICC_H__
#define __BSP_ICC_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include <osl_common.h>
#include <bsp_sram.h>
#include <bsp_shared_ddr.h>
#include <mdrv_icc_common.h>
#include <bsp_ipc.h>

#define ICC_CHAN_NUM_MAX            (32)
int BSP_ICC_Open(unsigned int u32ChanId, ICC_CHAN_ATTR_S *pChanAttr);
s32 BSP_ICC_Close(u32 u32ChanId);
int BSP_ICC_Write(unsigned int u32ChanId, unsigned char* pData, int s32Size);
int BSP_ICC_Read(unsigned int u32ChanId, unsigned char* pData, int s32Size);
s32 BSP_ICC_Ioctl(u32 u32ChanId, u32 cmd, void *param);
s32 BSP_ICC_Debug_Register(u32 u32ChanId, FUNCPTR_1 debug_routine, int param);
/* from drv_icc.h start*/


#define ICC_BUSY              (0x03 | NOTIFY_STOP_MASK)
#define ICC_OK                (0)
#define ICC_ERR               (-1)

/* CPU ID ���� */
enum CPU_ID
{
	ICC_CPU_MIN = IPC_CORE_ACORE,
	ICC_CPU_APP = IPC_CORE_ACORE,
	ICC_CPU_MODEM = IPC_CORE_CCORE,
	ICC_CPU_MCU = IPC_CORE_MCORE,
	ICC_CPU_TLDSP = IPC_CORE_LDSP,
	ICC_CPU_HIFI = IPC_CORE_HiFi,
	ICC_CPU_MAX
};

/* �����붨�� */
enum ICC_ERR_NO
{
	ICC_CHN_INIT_FAIL = (0x80000000 + (0 << 16)),
	ICC_MALLOC_CHANNEL_FAIL,
	ICC_MALLOC_VECTOR_FAIL,
	ICC_CREATE_TASK_FAIL,
	ICC_DEBUG_INIT_FAIL,
	ICC_CREATE_SEM_FAIL,
	ICC_REGISTER_INT_FAIL,
	ICC_INVALID_PARA,
	ICC_WAIT_SEM_TIMEOUT,
	ICC_SEND_ERR,
	ICC_RECV_ERR,
	ICC_REGISTER_CB_FAIL,
	ICC_REGISTER_DPM_FAIL,
	ICC_MALLOC_MEM_FAIL,
	ICC_NULL_PTR,
	ICC_INIT_ADDR_TOO_BIG,
	ICC_INIT_SKIP

};

/* ͨ��id���� */
enum ICC_CHN_ID
{
	ICC_CHN_ACORE_CCORE_MIN=0, /* add for modem reset : A/C��ͨ����ʼ��־ */
	ICC_CHN_IFC = 0,     /* acore��ccore֮���IFC������ͨ�� */
	ICC_CHN_RFILE = 1,   /* acore��ccore֮���RFILE������ͨ�� */
	ICC_CHN_NV = 2,      /* acore��ccore֮���NV������ͨ�� */
	ICC_CHN_GUOM0 = 3,  /* acore��ccore֮���GUOM0������ͨ�� */
	ICC_CHN_GUOM1,       /* acore��ccore֮���GUOM1������ͨ�� */
	ICC_CHN_GUOM2,       /* acore��ccore֮���GUOM2������ͨ�� */
	ICC_CHN_GUOM3,       /* acore��ccore֮���GUOM3������ͨ�� */
	ICC_CHN_GUOM4,       /* acore��ccore֮���GUOM4������ͨ�� */
	ICC_CHN_GUOM5,       /* acore��ccore֮���GUOM5������ͨ�� */
	ICC_CHN_CSHELL,      /* acore��ccore֮���CSHELL������ͨ�� */
	ICC_CHN_AC_PANRPC,  /* acore��ccore֮���PAN_RPC������ͨ�� */
	ICC_CHN_ACORE_CCORE_MAX, /* add for modem reset : A/C��ͨ��������־ */
	ICC_CHN_MCORE_CCORE, /* mcore��ccore֮���Ψһ������ͨ�� */
	ICC_CHN_MCORE_ACORE, /* mcore��acore֮���Ψһ������ͨ�� */
	ICC_CHN_CCPU_HIFI_VOS_MSG, /* CCPU  �� HIFI ֮��ĺ˼�ͨ��ͨ�� */
	ICC_CHN_HIFI_TPHY_MSG, /* BBE16 �� HIFI ֮��ĺ˼�ͨ�Ŵ���ͨ�� */
	ICC_CHN_VT_VOIP,       /* for LTE video phone use, ACORE<-->CCORE */
	ICC_CHN_SEC_IFC,       /* ����IPC������ֱ�ӻص�����������ȫOS��ccore��������ͨ�� */
	ICC_CHN_SEC_VSIM,      /* ˽��IPC������ֱ�ӻص������������ͨ��ȫOS��ccore����ͨ�� */

	ICC_CHN_ID_MAX
};

/* ˵��: ���ջص�����ID,��ͨ�����������, "ͨ������_xxx=0��ͨ������_RECV_FUNC_ID_MAX֮�䣬
 * ��: Ҫ��IFCͨ�����һ����ͨ��������ΪIFC_RECV_ONLY_TEST������Ҫ:
    IFC_RECV_FUNC_RTC_SETTIME = 0,
	IFC_RECV_FUNC_BBE,
	IFC_RECV_ONLY_TEST,
	IFC_RECV_FUNC_ID_MAX
 */
enum ICC_RECV_FUNC_ID{
	IFC_RECV_FUNC_RTC_SETTIME = 0,
	IFC_RECV_FUNC_ONOFF,
	IFC_RECV_FUNC_ANTEN,
	IFC_RECV_FUNC_EFUSE,
	IFC_RECV_FUNC_SIM0,
	IFC_RECV_FUNC_SIM1,
	IFC_RECV_FUNC_CSHELL,
	IFC_RECV_FUNC_UART,
    IFC_RECV_FUNC_LED,
    IFC_RECV_FUNC_RESET,
    FC_RECV_FUNC_GPSCLK,
	IFC_RECV_FUNC_PASTAR,
    IFC_RECV_FUNC_PA_RF,
    IFC_RECV_FUNC_WAKEUP,
	IFC_RECV_FUNC_PM_OM,
	IFC_RECV_FUNC_SOCP_DEBUG,
	IFC_RECV_FUNC_REMOTE_CLK,
    IFC_RECV_FUNC_PMU_OCP,
	IFC_RECV_FUNC_SYSTEM_HEATING,
	IFC_RECV_FUNC_SYS_BUS,
	IFC_RECV_FUNC_LOADPS,
	/* ��Ҫ��ICC_CHN_IFC����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	IFC_RECV_FUNC_TEST1,
	IFC_RECV_FUNC_ID_MAX,

	RFILE_RECV_FUNC_ID = 0,
	/* ��Ҫ��ICC_CHN_RFILE����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	RFILE_RECV_FUNC_ID_MAX,

    NV_RECV_FUNC_AC = 0,
    NV_RECV_FUNC_SC = 1,
	/* ��Ҫ��ICC_CHN_NV����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	NV_RECV_FUNC_ID_MAX,

	GUOM0_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM0����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM0_RECV_FUNC_ID_MAX,

	GUOM1_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM1����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM1_RECV_FUNC_ID_MAX,

	GUOM2_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM1����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM2_RECV_FUNC_ID_MAX,

	GUOM3_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM2����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM3_RECV_FUNC_ID_MAX,

	GUOM4_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM4����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM4_RECV_FUNC_ID_MAX,

	GUOM5_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_GUOM5����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	GUOM5_RECV_FUNC_ID_MAX,

	CSHELL_TEST1 = 0,
	/* ��Ҫ��ICC_CHN_CSHELL����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	CSHELL_RECV_FUNC_ID_MAX,

    AC_PANRPC_ID = 0,
    /* ��Ҫ��ICC_CHN_AC_PANRPC����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
    AC_PANRPC_RECV_FUNC_ID_MAX,

	MCORE_CCORE_FUNC_TEST1 = 0,
	MCORE_CCORE_FUNC_TEST2,
	MCORE_CCORE_FUNC_HKADC = 2,  /* austin��ֵ�������޸� */
	MCU_CCORE_CPUFREQ = 3 ,      /* austin��ֵ�������޸� */
	MCU_CCORE_WSRC = 4,          /* austin��ֵ�������޸� */
	MCORE_CCORE_FUNC_WAKEUP = 5, /* austin��ֵ�������޸� */
	MCORE_CCORE_FUNC_REGULATOR,
	MCORE_CCORE_FUNC_SIM0,
	MCORE_CCORE_FUNC_SIM1,
	MCORE_CCORE_FUNC_SOCP = 9,   /* austin��ֵ�������޸� */
	MCORE_CCORE_FUNC_UART,
	MCORE_CCORE_FUNC_TSENSOR,
	MCORE_CCORE_FUNC_PDLOCK,
	/* ��Ҫ��ICC_CHN_MCORE_CCORE����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	MCORE_CCORE_FUNC_ID_MAX,

	MCORE_ACORE_FUNC_TEST1 = 0,
	MCORE_ACORE_FUNC_TEST2,
	MCORE_ACORE_FUNC_HKADC,
	MCU_ACORE_CPUFREQ,
	MCU_ACORE_WSRC,
	NV_RECV_FUNC_AM,
	MCORE_ACORE_FUNC_TEMPERATURE,
	MCU_ACORE_RFILE,    /* for rfile */
	MCORE_ACORE_FUNC_WAKEUP,
	MCORE_ACORE_FUNC_DUMP,
	MCORE_ACORE_FUNC_RESET,
	MCORE_ACORE_FUNC_PM_OM,
	/* ��Ҫ��ICC_CHN_MCORE_ACORE����ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	MCORE_ACORE_FUNC_ID_MAX,

	/* BBE16  �� HIFI ֮�����ϢGUͨ�����ܺ�  */
	HIFI_TPHY_MSG_NRM = 0,
	HIFI_TPHY_MSG_URG,
	HIFI_TPHY_MSG_MAX,

	/* BBE16  �� HIFI ֮�����ϢTDSͨ�����ܺ�  */
	CCPU_HIFI_VOS_MSG_NRM = 0,
	CCPU_HIFI_VOS_MSG_URG,
	CCPU_HIFI_VOS_MSG_MAX,

    //VT_VOIP_FUNC_ID_TEST = 0,
    //VT_VOIP_FUNC_ID_MAX

	SEC_IFC_RECV_FUNC_MODULE_VERIFY = 0,

	/* ��Ҫ������ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	SEC_IFC_RECV_FUNC_ID_MAX,

	SEC_VSIM_RECV_FUNC_TEST = 0,

	/* ��Ҫ������ͨ���϶�����ͨ��,���ڸ�ע����֮ǰ���� */
	SEC_VSIM_RECV_FUNC_ID_MAX 

};
/* ö�ٶ���end */

struct icc_channel_packet
{
	u32 channel_id;               /* �����ݰ���¼��ͨ��id */
	u32 len;                      /* �����ݰ����� */
	u32 src_cpu_id;               /* �����ݰ��ķ����ߵ�cpu id */
	u32 seq_num;                  /* �����ݰ������к�: ͬ�����͵ĵȴ�������Ҫ�õ� */
	u32 need_responsed:1;         /* �����ݰ��Ƿ���Ҫ�ظ����Է��˱�ʶbitλ */
	u32 is_responsed:1;           /* �����ݰ��Ƿ��ǶԷ��˻ظ������ı�ʶbitλ */
	u32 reserved:30;              /* ����bitλ */
	s32 data;                     /* ���ݰ�ͷ��context */
	u32 timestamp;                /* �����ݰ���ʱ��� */
	u32 task_id;                  /* �����ݰ��ķ����ߵ�����id */
};

struct icc_channel_fifo
{
	u32 magic;     /* fifoħ������ʶͨ��fifo��״̬ */
	u32 size;      /* fifo��С */
	u32 write;     /* fifo��ָ�� */
	u32 read;      /* fifoдָ�� */
	u8  data[4];   /* fifo��context */
};

#define ICC_CHANNEL_PAYLOAD                        (sizeof(struct icc_channel_packet) + 4)
#define ICC_CHANNEL_ID_MAKEUP(channel_id, func_id) ((channel_id << 16) | (func_id))
#define SHM_ADDR_ICC                               (char *) ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_ICC)
#define SRAM_ADDR_ICC                              (char *) ((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_ICC)

typedef s32 (*read_cb_func)(u32 channel_id , u32 len, void* context);
typedef s32 (*write_cb_func)(u32 channel_id , void* context);
/* ����ӿ�����start */
/*****************************************************************************
* �� �� ��  : bsp_icc_send
* ��������  : icc�첽�������ݽӿ�
* �������  : u32 cpuid       ����Ҫ���͵�cpu�ı�ţ�ʹ��Լ��: Ҫʹ��enum CPU_ID�����Ա��ö��ֵ
*             u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                               1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID��ö��ֵ
                               2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
*             u8 *buffer      Ҫ���͵�����buffer��ָ��
*             u32 data_len    Ҫ���͵����ݵĴ�С, ʹ��Լ��: ���ֵ < fifo_size - ICC_CHANNEL_PACKET_LEN
* �������  : ��
* �� �� ֵ  : ��ȷ:  ʵ��д��fifo�Ĵ�С;  ����: ��ֵ
* ˵    ��  : 1) ����ͨ��������ʹ�õ�ע���ڶԷ��˵Ļص����������Ҫʹ��bsp_icc_read()���������ݶ���
*            2) ר��ͨ����֧���ڸ�ͨ��ʹ��ģ���������������ʹ��bsp_icc_read()���������ݶ��ߣ������Ͷ˱����з�ѹ��ͨ�����ݷ��ͻ�����������ơ�

*****************************************************************************/
s32 bsp_icc_send(u32 cpuid,u32 channel_id,u8 *buffer,u32 data_len);

/*****************************************************************************
* �� �� ��  : bsp_icc_send_sync
* ��������  : iccͬ���������ݽӿ�
* �������  : u32 cpuid       ����Ҫ���͵�cpu�ı�ţ�ʹ��Լ��: Ҫʹ��enum CPU_ID�����Ա��ö��ֵ
*             u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                               1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID��ö��ֵ
                               2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧ��ͨ��id��ö��ֵ
*             u8 *buffer      Ҫ���͵�����buffer��ָ��
*             u32 data_len    Ҫ���͵����ݵĴ�С, ʹ��Լ��: ���ֵ < fifo_size - ICC_CHANNEL_PACKET_LEN
*             s32 timeout     �Ȼظ���ʱ�䣬ʹ��Լ��: Ҫ���޵���Ҫʹ�ú� MAX_SCHEDULE_TIMEOUT
* �������  : ��
* �� �� ֵ  : ��ȷ: ���պ˻ص������ķ���ֵ;  ����: ��ֵ
* ˵    ��  : 1) ����ʹ�õ�ע���ڶԷ��˵Ļص����������Ҫʹ��bsp_icc_read()���������ݶ���
*             2) ���øýӿڻᵼ�µ���������˯��ֱ����ʱʱ�䵽�����߶Է��˷��غ������ý��
*             3) �ýӿ������ں˼亯������(IFC)�����Σ��˼亯������ֻ�ܷ���ϵͳ�Դ��ļ��������ͣ����ܷ��ؽṹ����û��Զ�������
*             4) �ýӿڲ�����icc�ص���ʹ�ã�������������icc�����ӳٵ����غ��

*****************************************************************************/
s32 bsp_icc_send_sync(u32 cpuid,u32 channel_id,u8 * data,u32 data_len,long timeout);

/*****************************************************************************
* �� �� ��  : bsp_icc_read
* ��������  : icc��fifo��ȡ���ݽӿ�
* �������  : u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID
                2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
*             u8 *buf        Ҫ��ȡfifo������buffer��ָ��
*             u32 buf_len    ����buffer�Ĵ�С
* �������  : ��
* �� �� ֵ  : ��ȷ:  ʵ�ʴ�ͨ����ȡ���ݴ�С;  ����: ��ֵ
* ˵    ��  : 1) ���ڻص�������ʹ�ã���ʹ�����Լ�������������ʹ�ã������Ͷ˱����з�ѹ��ͨ�����ݷ��ͻ�����������ƣ��Ա��ֺ˼�ͨ����������ͨ
*****************************************************************************/
s32 bsp_icc_read(u32 channel_id,u8 * buf,u32 buf_len);

/*****************************************************************************
* �� �� ��  : bsp_icc_event_register
* ��������  : ʹ��iccͨ��ע��ص������ӿ�
* �������  : u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID
                2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
*             read_cb_func read_cb      ���ص�
*             void *read_context        ���������������������Ϣ������չ��
*             write_cb_func write_cb    ���ص�
*             void *write_context       ���������������������Ϣ������չ��
* �������  : ��
* �� �� ֵ  : ��ȷ:  0;  ����: ������
* ˵    ��  : �ص������в������κλ���������������˯�ߵĺ������ã��磺
*             1) taskDelay()
*             2) �ź�����ȡ
*             3) printf()
*             4) malloc()
*             5) bsp_icc_send_sync()
*****************************************************************************/
s32 bsp_icc_event_register(u32 channel_id, read_cb_func read_cb, void *read_context,
                                              write_cb_func write_cb, void *write_context);

/*****************************************************************************
* �� �� ��  : bsp_icc_event_unregister
* ��������  : ʹ��iccͨ��ȥע��ص������ӿ�
* �������  : u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID
                2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
* �������  : ��
* �� �� ֵ  : ��ȷ:  0;  ����: ��ֵ
*****************************************************************************/
s32 bsp_icc_event_unregister(u32 channel_id);

/*****************************************************************************
* �� �� ��  : bsp_icc_debug_register
* ��������  : ʹ��iccͨ��ע��ص������ӿ�
* �������  : u32 channel_id  channel_id = ͨ��id << 16 || function_id, ʹ��Լ��:
                1) channel_id��16bitΪͨ����ʶID��ʹ��enum ICC_CHN_ID
                2) ��16bitΪ�ص�������ʶID��ʹ��ICC_RECV_FUNC_ID��Ӧͨ��id��ö��ֵ
*             FUNCPTR_1 debug_routine     ��һ�������ĵ͹��Ļ��ѻص�
*             int param       �����ص������Ĳ���
* �������  : ��
* �� �� ֵ  : ��ȷ:  0;  ����: ������
* ˵    ��  : �ص������в������κλ���������������˯�ߵĺ������ã��磺
*             1) taskDelay()
*             2) �ź�����ȡ
*             3) printf()
*             4) malloc()
*             5) bsp_icc_send_sync()
*****************************************************************************/
s32 bsp_icc_debug_register(u32 channel_id, FUNCPTR_1 debug_routine, int param);

s32 bsp_icc_init(void);
void bsp_icc_release(void);
s32 bsp_icc_suspend(void);

/* ICCͨ�����ã�ģ���ڲ����ã��Ƕ����ṩ������ģ�鲻Ҫ���� */

#define STRU_SIZE             (sizeof(struct icc_channel_fifo))
#define ICC_IFC_SIZE          (SZ_4K)
#define ICC_RFILE_SIZE        (SZ_4K)
#define ICC_NV_SIZE           (SZ_4K)
#define ICC_GUOM0_SIZE        (SZ_16K)
#define ICC_GUOM1_SIZE        (0)
#define ICC_GUOM2_SIZE        (0)
#define ICC_GUOM3_SIZE        (0)
#define ICC_GUOM4_SIZE        (SZ_128K)
#define ICC_GUOM5_SIZE        (0)
#define ICC_CSHELL_SIZE       (SZ_8K)
#define ICC_PANRPC_SIZE       (SZ_4K)
#define ICC_MCCORE_SIZE       (SZ_512)
#define ICC_MACORE_SIZE       (SZ_512)
#define ICC_HIFI_VOS_SIZE     (6 * 1024)
#define ICC_HIFI_TPHY_SIZE    (6 * 1024)
#define ICC_VT_VOIP_SIZE      (SZ_4K)


/* ddr�����ڴ�ͨ����ַ����, acore��ccore */
#define ICC_DBG_MSG_LEN_IN_DDR  (0x20)
#define ICC_DBG_MSG_ADDR_IN_DDR (char *) (((unsigned long)(SHM_ADDR_ICC) + 3) & ~3)
#define ADDR_IFC_SEND         (ICC_DBG_MSG_ADDR_IN_DDR + ICC_DBG_MSG_LEN_IN_DDR) /* C�˷��ͣ�A�˽��� */
#define ADDR_IFC_RECV         (ADDR_IFC_SEND    + STRU_SIZE + ICC_IFC_SIZE)      /* C�˽��գ�A�˷��� */
#define ADDR_RFILE_SEND       (ADDR_IFC_RECV    + STRU_SIZE + ICC_IFC_SIZE)      /* C�˷��ͣ�A�˽��� */
#define ADDR_RFILE_RECV       (ADDR_RFILE_SEND  + STRU_SIZE + ICC_RFILE_SIZE)    /* C�˽��գ�A�˷��� */
#define ADDR_NV_SEND          (ADDR_RFILE_RECV  + STRU_SIZE + ICC_RFILE_SIZE)    /* C�˷��ͣ�A�˽��� */
#define ADDR_NV_RECV          (ADDR_NV_SEND     + STRU_SIZE + ICC_NV_SIZE)       /* C�˽��գ�A�˷��� */
#define ADDR_GUOM0_SEND       (ADDR_NV_RECV     + STRU_SIZE + ICC_NV_SIZE)       /* C�˷��ͣ�A�˽��� */
#define ADDR_GUOM0_RECV       (ADDR_GUOM0_SEND  + STRU_SIZE + ICC_GUOM0_SIZE)    /* C�˽��գ�A�˷��� */
#define ADDR_GUOM1_SEND       (ADDR_GUOM0_RECV  + STRU_SIZE + ICC_GUOM0_SIZE)    /* C�˷��ͣ�A�˽��� */
#define ADDR_GUOM1_RECV       (ADDR_GUOM1_SEND  + STRU_SIZE + ICC_GUOM1_SIZE)    /* C�˽��գ�A�˷��� */
#define ADDR_GUOM2_SEND       (ADDR_GUOM1_RECV  + STRU_SIZE + ICC_GUOM1_SIZE)    /* C�˷��ͣ�A�˽��� */
#define ADDR_GUOM2_RECV       (ADDR_GUOM2_SEND  + STRU_SIZE + ICC_GUOM2_SIZE)    /* C�˽��գ�A�˷��� */
#define ADDR_GUOM3_SEND       (ADDR_GUOM2_RECV  + STRU_SIZE + ICC_GUOM2_SIZE)    /* C�˷��ͣ�A�˽��� */
#define ADDR_GUOM3_RECV       (ADDR_GUOM3_SEND  + STRU_SIZE + ICC_GUOM3_SIZE)    /* C�˽��գ�A�˷��� */
#define ADDR_GUOM4_SEND       (ADDR_GUOM3_RECV  + STRU_SIZE + ICC_GUOM3_SIZE)    /* C�˷��ͣ�A�˽��� */
#define ADDR_GUOM4_RECV       (ADDR_GUOM4_SEND  + STRU_SIZE + ICC_GUOM4_SIZE)    /* C�˽��գ�A�˷��� */
#define ADDR_GUOM5_SEND       (ADDR_GUOM4_RECV  + STRU_SIZE + ICC_GUOM4_SIZE)    /* C�˷��ͣ�A�˽��� */
#define ADDR_GUOM5_RECV       (ADDR_GUOM5_SEND  + STRU_SIZE + ICC_GUOM5_SIZE)    /* C�˽��գ�A�˷��� */
#define ADDR_CSHELL_SEND      (ADDR_GUOM5_RECV  + STRU_SIZE + ICC_GUOM5_SIZE)    /* C�˷��ͣ�A�˽��� */
#define ADDR_CSHELL_RECV      (ADDR_CSHELL_SEND + STRU_SIZE + ICC_CSHELL_SIZE)   /* C�˽��գ�A�˷��� */
#define ADDR_PANRPC_SEND      (ADDR_CSHELL_RECV + STRU_SIZE + ICC_CSHELL_SIZE)   /* C�˷��ͣ�A�˽��� */
#define ADDR_PANRPC_RECV      (ADDR_PANRPC_SEND + STRU_SIZE + ICC_PANRPC_SIZE)   /* C�˽��գ�A�˷��� */

/* ddr�����ڴ�ͨ����ַ����, ��ȫOS��ccore */
#ifdef SHM_SEC_BASE_ADDR
#define SHM_S_ADDR_ICC            (SHM_SEC_BASE_ADDR + SHM_OFFSET_SEC_ICC)
#define SHM_S_SIZE_ICC            (SHM_SIZE_SEC_ICC)
#else
#define SHM_S_ADDR_ICC            0
#define SHM_S_SIZE_ICC            0
#endif

#define ICC_DBG_MSG_LEN_IN_DDR_S  (0x20)
#define ICC_DBG_MSG_ADDR_IN_DDR_S (char *) (((unsigned long)(SHM_S_ADDR_ICC) + 3) & ~3)

#ifndef BSP_ICC_MCHANNEL_USE_LPM3TCM /* BALONGV7R2 */
/* SRAM(AXI)ͨ����ַ����, mcore��ccore; mcore��acore */
#define ADDR_MCCORE_SEND      (SRAM_ADDR_ICC)  /* M�˷��ͣ�C�˽��� */
#else                          /* K3V3 */
#define ADDR_MCCORE_SEND      (ADDR_PANRPC_RECV + STRU_SIZE + ICC_PANRPC_SIZE) /* M�˷��ͣ�C�˽��� Austin��ʹ��SDDR*/
#endif
#define ADDR_MCCORE_RECV      (ADDR_MCCORE_SEND + STRU_SIZE + ICC_MCCORE_SIZE) /* M�˽��գ�C�˷��� */
#define ADDR_MACORE_SEND      (ADDR_MCCORE_RECV + STRU_SIZE + ICC_MCCORE_SIZE) /* M�˷��ͣ�A�˽��� */
#define ADDR_MACORE_RECV      (ADDR_MACORE_SEND + STRU_SIZE + ICC_MACORE_SIZE) /* M�˽��գ�A�˷��� */

#ifndef BSP_ICC_MCHANNEL_USE_LPM3TCM
#define ADDR_HIFI_VOS_MSG_SEND      (ADDR_PANRPC_RECV + STRU_SIZE + ICC_PANRPC_SIZE)
#else                          
#define ADDR_HIFI_VOS_MSG_SEND      (ADDR_MACORE_RECV + STRU_SIZE + ICC_MACORE_SIZE)
#endif
#define ADDR_HIFI_VOS_MSG_RECV      (ADDR_HIFI_VOS_MSG_SEND + STRU_SIZE + ICC_HIFI_VOS_SIZE)
#define ADDR_HIFI_TPHY_MSG_SEND      (ADDR_HIFI_VOS_MSG_RECV + STRU_SIZE + ICC_HIFI_VOS_SIZE)
#define ADDR_HIFI_TPHY_MSG_RECV      (ADDR_HIFI_TPHY_MSG_SEND + STRU_SIZE + ICC_HIFI_TPHY_SIZE)

#define ADDR_VT_VOIP_CCORE_RECV_ACORE_SEND       (ADDR_HIFI_TPHY_MSG_RECV + STRU_SIZE + ICC_HIFI_TPHY_SIZE)
#define ADDR_VT_VOIP_CCORE_SEND_ACORE_RECV       (ADDR_VT_VOIP_CCORE_RECV_ACORE_SEND + STRU_SIZE + ICC_VT_VOIP_SIZE)


#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_ICC_H__ */
