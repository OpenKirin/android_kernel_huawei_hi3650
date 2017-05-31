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

#ifndef __DICC_H__
#define __DICC_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/
#include "TTFLink.h"
#include "TTFComm.h"
#include "DiccInterface.h"

#if( FEATURE_ON == FEATURE_CSD )

/******************************************************************************
  2 �궨��
******************************************************************************/
/*
ע��DICC�ڴ��ǰ���ǰ����ʼ����ͨ��˳����֯��, ����һ���ǰ���ͨ��ID������֯
*/
/************** DICC mem() begin **************
  ->startAddr|                                               |
             |            DICC�ܿ��ƽṹDICC Ctrl            |
             |-----------------------------------------------|
             |   ��һ����ʼ����ͨ���Ŀ��ƽṹ(channel ctrl)  |
             |-----------------------------------------------|
             |   �ڶ�����ʼ����ͨ���Ŀ��ƽṹ(channel ctrl)  |
             |-----------------------------------------------|
             |   ��������ʼ����ͨ���Ŀ��ƽṹ(channel ctrl)  |
             |-----------------------------------------------|
             |   ���ĸ���ʼ����ͨ���Ŀ��ƽṹ(channel ctrl)  |    ��ͨ�����������û�����, ����һ��, Ҳ���Բ�һ��, ������ n != m != k != j, ���ǽ��ṹ��ͬ
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        ��һ����ʼ����ͨ���� ring queue        |  ===> |      queue node_1 *      |     queue node_2 *     | ... |     queue node_n *     |
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        ��һ����ʼ����ͨ���� queue data        |  ===> |       queue node_1       |      queue node_2      | ... |      queue node_n      |
             |-----------------------------------------------|       |--------------------------|------------------------|-----|------------------------|
             |        �ڶ�����ʼ����ͨ���� ring queue        |  ===> |      queue node_1 *      |     queue node_2 *     | ... |     queue node_m *     |
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        �ڶ�����ʼ����ͨ���� queue data        |  ===> |       queue node_1       |      queue node_2      | ... |      queue node_m      |
             |-----------------------------------------------|       |--------------------------|------------------------|-----|------------------------|
             |        ��������ʼ����ͨ���� ring queue        |  ===> |      queue node_1 *      |     queue node_2 *     | ... |     queue node_k *     |
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        ��������ʼ����ͨ���� queue data        |  ===> |       queue node_1       |      queue node_2      | ... |      queue node_k      |
             |-----------------------------------------------|       |--------------------------|------------------------|-----|------------------------|
             |        ���ĸ���ʼ����ͨ���� ring queue        |  ===> |      queue node_1 *      |     queue node_2 *     | ... |     queue node_j *     |
             |-----------------------------------------------|       |---------------------------------------------------|-----|------------------------|
             |        ���ĸ���ʼ����ͨ���� queue data        |  ===> |       queue node_1       |      queue node_2      | ... |      queue node_j      |
             |-----------------------------------------------|       |--------------------------|------------------------|-----|------------------------|
 **************** DICC mem end ****************/


#define DICC_MEM_INIT_MAGIC_NUM                             (0x1D2D3D4D)                    /* DICCͬ��ħ���� */
/* ���ڷ�ֹ���ݱ��۸ĵ�ħ����, ��ֵ�̶�Ϊ0xACAC */
#define DICC_MAGIC_NUM_VALUE                                (0xACAC)

#define DICC_MEMORY_TOTAL_SIZE                              (DICC_QUEUE_MEM_SIZE)   /* �˼�ͨ���ڴ�, ��λ: �ֽ� */

#define DICC_MAX_SENDER_NUM_PER_CPU                         (2)       /* ��CPU�ϳ䵱ͨ��sender�˵�ͨ������ */
#define DICC_MAX_RECVER_NUM_PER_CPU                         (2)       /* ��CPU�ϳ䵱ͨ��recver�˵�ͨ������ */

#define DICC_SERVICE_TYPE_NUM_PER_CPU                       (2)                         /* ��CPU�� ������������ */

/* ���֧�ִ�ӡDICCͨ�����ݵ��ֽ��� */
#define DICC_DEBUG_PRINT_MAX_LEN                            (128)

/* ���ڶ�λ�����trace�����ݿ� */
#define DICC_MAX_TRACE_QUEUE_DATA_CNT                       (10)

/* DICC Interupt */
#define DICC_SERVICE_0_INT_LEVEL                            (IPC_INT_DICC_USRDATA)       /* �˼�������ͨ���ж�������(���ݵ���֪ͨ�ж�) */
#define DICC_SERVICE_1_INT_LEVEL                            (IPC_INT_DICC_RELDATA)       /* �˼�������ͨ���ж�������(�ڴ��ͷ�֪ͨ�ж�) */

/* DICC channel state and mask */
#define DICC_CHAN_BOTH_CLOSE_MASK                           (0x00)     /* ͨ�����˶��ر� */
#define DICC_CHAN_SENDER_OPEN_MASK                          (0x01)    /* ͨ�������Ͷ˴� */
#define DICC_CHAN_RECVER_OPEN_MASK                          (0x02)    /* ͨ�������ն˴� */
#define DICC_CHAN_BOTH_OPEN_MASK                            ((DICC_CHAN_SENDER_OPEN_MASK) | (DICC_CHAN_RECVER_OPEN_MASK))    /* ͨ�����˶��� */

/* �ж�DICCͨ���Ƿ�һֱ������״̬, ���ⲿʹ���߶�ȡ�ĳ���, ��ʱ˵���ⲿʹ���߳����쳣, ���е��帴λ, �ݶ�1s
   ʹ��32Kʱ��������, 1s = 1*32K slice = 32768 slice */
#define DICC_CHAN_QUEUE_FULL_TIME                           (32768)

/* DICCͨ��һ��������״̬, �ͻ����, ������������ô��κ�, ���ϱ�SDTһ�� */
#define DICC_CHAN_QUEUE_FULL_REPORT_TIMES                   (50)

#define TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_ALWAYS_FULL     (0x30000000)    /* DICC��Ϊͨ������һֱ����������λ�ĸ�λmodule-id */
#define TTF_SOFT_REBOOT_MODULE_ID_DICC_CHAN_INIT_FAIL       (0x30000001)    /* DICC��Ϊͨ����ʼ��ʧ�ܶ�������λ�ĸ�λmodule-id */
#define TTF_SOFT_REBOOT_MODULE_ID_DICC_MEM_CLEAN_SYNC_FAIL  (0x30000002)    /* DICC��Ϊͨ���ڴ��ʼ��ʧ�ܶ�������λ�ĸ�λmodule-id */


/* DICC��ӡʹ�õ�module-id */
#define MODULE_DICC_LOG_ID                                  (0x8200)

/* �����жϲ�����¼�ĺ� */
#define SET_ISR_RECORD(pstIsrRecord, Pid, ServiceType, IsrOp, OpResult)\
                                                    {\
                                                        (pstIsrRecord)->ulPid         = (Pid);\
                                                        (pstIsrRecord)->enServiceType = (ServiceType);\
                                                        (pstIsrRecord)->enIsrOp       = (IsrOp);\
                                                        (pstIsrRecord)->enOpResult    = (OpResult);\
                                                    }

/* ��ȡDICC����ṹDFx���ڴ��ַ */
#define DICC_GET_CHAN_DFX(pastDICCMgmt)             ((DICC_DFX_STRU *)(&((pastDICCMgmt)->stDFx)))

/* DICC������, ����IPCʵ�� */
#define DICC_SPIN_LOCK()                            (mdrv_ipc_spin_lock(IPC_SEM_DICC))
#define DICC_SPIN_UNLOCK()                          (mdrv_ipc_spin_unlock(IPC_SEM_DICC))

/* TRACE·����������ĺ� */
#define DICC_TRACE_OK                               (DICC_OK)

/* ���ø��ٺ���ִ�в���ĺ�, TRACEĬ�ϴ�, ������ڵ��������׶�ʹ��, �Լ��ٵ��Զ����ܵ���ʧ */
#define SET_DICC_TRACE_INFO_RECORD(pstTrace, CpuId, Pid, FuncId, LineNo, OpResult)\
                                                    {\
                                                        (pstTrace)->enCpuId           = (CpuId);\
                                                        (pstTrace)->ulPid             = (Pid);\
                                                        (pstTrace)->enFuncId          = (FuncId);\
                                                        (pstTrace)->ulLine            = (LineNo);\
                                                        (pstTrace)->enResult          = (OpResult);\
                                                    }

/* ������λ������Ϣ */
#define SET_DICC_SOFT_REBOOT_INFO(pstRebootInfo, Module, FuncId, LineNo, pUserDataStart, UserDataLen)\
                                                    {\
                                                        (pstRebootInfo)->ulModule     = (Module);\
                                                        (pstRebootInfo)->ulFile       = (FuncId);\
                                                        (pstRebootInfo)->ulLine       = (LineNo);\
                                                        (pstRebootInfo)->pucData      = (VOS_UINT8 *)(pUserDataStart);\
                                                        (pstRebootInfo)->ulDataLen    = (UserDataLen);\
                                                    }

#define DICC_MUTEX_SEM_NOT_CREATE   0
#define DICC_MUTEX_SEM_CREATED      1

/******************************************************************************
  3 ö�ٶ���
******************************************************************************/
/* ��¼ĳ��ͨ���Ƿ��Ѿ�����ʼ����ö�� */
enum DICC_CHAN_INIT_STATUS_ENUM
{
    DICC_CHAN_STATUS_NOT_INITIALED                   = 0,            /* The channel is not initialed */
    DICC_CHAN_STATUS_INITIALED                       = 1,            /* The channel is already initialed */

    DICC_CHAN_STATUS_BUTT
};
typedef VOS_UINT8 DICC_CHAN_INIT_STATUS_ENUM_UINT8;

/* DICC�ж�ʹ��/ȥʹ��ö�� */
enum DICC_SERVICE_ISR_OP_ENUM
{
    DICC_SERVICE_ISR_ENABLE                           = 0,            /* enable interrupt */
    DICC_SERVICE_ISR_DISABLE                          = 1,            /* disable interrupt */

    DICC_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 DICC_SERVICE_ISR_OP_ENUM_UINT8;

/* DICCͨ���ϱ��¼� */
enum DICC_MNTN_EVENT_ID_ENUM
{
    ID_DICC_MNTN_CLOSE_FLUSH_EVENT                  = 0x0001,         /* _H2ASN_MsgChoice DICC_CHAN_CLOSE_FLUSH_EVENT_STRU */
    ID_DICC_MNTN_MAGIC_NUM_CHANGED_EVENT            = 0x0002,         /* _H2ASN_MsgChoice DICC_CHAN_MAGIC_NUM_CHANGED_EVENT_STRU */
    ID_DICC_MNTN_QUEUE_FULL_EVENT                   = 0x0003,         /* _H2ASN_MsgChoice DICC_CHAN_QUEUE_FULL_EVENT_STRU */

    ID_DICC_MNTN_EVENT_TYPE_BUTT
};
typedef VOS_UINT16 DICC_MNTN_EVENT_ID_ENUM_UINT16;

/* DICC��λ�ļ����, ��Ҫ��λ�ĺ��������һ�����,
   �׳�������ĺ����ǵ��������׶�, �����Ǵ˽׶�����,
   ����ͨ���޷���LOG���, ��ӡż�������ӳ�, ������ */
enum DICC_TRACE_FUNC_MARK_ID_ENUM
{
    ID_DICC_TRACE_FUNC_BEGIN                        = 0,    /* ��ȫ�ֱ�����ʼ��Ϊ0 */
    ID_DICC_TRACE_FUNC_MARK_SYNC                    = 1,
    ID_DICC_TRACE_FUNC_MARK_SINGLE_CHAN_INIT        = 2,
    ID_DICC_TRACE_FUNC_MARK_OPEN                    = 3,
    ID_DICC_TRACE_FUNC_MARK_CLOSE                   = 4,

    ID_DICC_TRACE_FUNC_MARK_BUTT
};
typedef VOS_UINT8 DICC_TRACE_FUNC_MARK_ID_ENUM_UINT8;

/******************************************************************************
  4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
  5 ��Ϣͷ����
******************************************************************************/


/******************************************************************************
  6 ��Ϣ����
******************************************************************************/


/******************************************************************************
  7 STRUCT����
******************************************************************************/
#pragma pack(4)

/* �ⲿ�û�������жϵļ�¼�ṹ */
typedef struct
{
    VOS_UINT32                      ulInvalidDisableOpPid;                                 /* ������жϵ�PID */
    VOS_UINT32                      ulInvalidDisableOpTime;                                /* ������жϵ�slice */
    VOS_UINT32                      ulInvalidEnableOpPid;                                  /* ������жϵ�PID */
    VOS_UINT32                      ulInvalidEnableOpTime;                                 /* ������жϵ�slice */
} DICC_ISR_DEBUG_STRU;

/* �ⲿ�û���ȷ�����жϵļ�¼�ṹ */
typedef struct
{
    VOS_UINT32                      ulDisableOpPid;                              /* �����жϵ�PID */
    VOS_UINT32                      ulDisableOpTime;                             /* �����жϵ�slice */
    VOS_UINT32                      ulDisableCnt;                                /* �������� */
    VOS_UINT32                      ulEnableOpPid;                               /* �����жϵ�PID */
    VOS_UINT32                      ulEnableOpTime;                              /* �����жϵ�slice */
    VOS_UINT32                      ulEnableCnt;                                 /* �������� */
} DICC_ISR_OP_STRU;

/* Ӳ���ź���������¼ */
typedef struct
{
    VOS_UINT32                          ulSingnalNum;       /* Ӳ���ź������ */
    VOS_INT32                           lTimeout;           /* ��ȡ�ź����ȴ�ʱ�� */
    VOS_INT32                           lResult;            /* Ӳ���ź���������� */
} DICC_CHAN_HW_SEM_PAPA_STRU;

/* �����ź���������¼ */
typedef struct
{
    VOS_UINT32                          ulResult;            /* �ź���������� */
} DICC_CHAN_LOCAL_SEM_PAPA_STRU;

/* �ⲿ�û������ͨ���ļ�¼�ṹ */
typedef struct
{
    VOS_UINT32                  ulOpPid;                                        /* �����ͨ����PID */
    VOS_UINT32                  ulOpTime;                                       /* �����ͨ����slice */
} DICC_CHAN_DEBUG_STRU;

/* ���ں˼�����ͨ��ͳ�Ƽ����Ľṹ */
typedef struct
{
    VOS_UINT32                  ulInsertPid;                                    /* Insert����PID */
    VOS_UINT32                  ulInsertCnt;                                    /* ������� */
    VOS_UINT32                  ulQueueFullCnt;                                 /* ������ֶ��������� */
    VOS_UINT32                  ulConsecutiveQueueFullCnt;                      /* ����ʱ�������ֶ���������, ������ʱ���� */
    VOS_UINT32                  ulLastInsertTime;                               /* ���һ�β������ݵ�ʱ��, ��λ: slice */
    VOS_UINT32                  ulRemovePid;                                    /* Remove����PID */
    VOS_UINT32                  ulRemoveCnt;                                    /* �Ƴ����� */
    VOS_UINT32                  ulLastRemoveTime;                               /* ���һ���Ƴ����ݵ�ʱ��, ��λ: slice */
    VOS_UINT32                  ulTrigIsrPid;                                   /* �����жϲ���PID */
    VOS_UINT32                  ulTrigIsrCnt;                                   /* �����жϴ��� */
    VOS_UINT32                  ulLastTrigIsrTime;                              /* ���һ�δ����ж����ݵ�ʱ��, ��λ: slice */
} DICC_CHAN_STATISTICS_STRU;

/* ��λʱ, ���ڵ���ͨ���������ݵĽṹ */
typedef struct
{
    VOS_UINT32                  ulInsertTime;                                   /* �������ݵ�ʱ��, ��λ: slice */
    VOS_UINT8                   ucPriDataLen;                                   /* �����ݵ���Ϣ���ݳ���, ��λ: �ֽ� */
    VOS_UINT8                   aucReserve[3];
    VOS_UINT8                   aucPriData[DICC_INFO_BLOCK_MAX_LEN];            /* �����ݵ���Ϣ���� */
} DICC_TRACE_QUEUE_DATA_STRU;

/* ��λʱ, ���ڵ���ͨ�����ݵĽṹ */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChanId;                                       /* ͨ��ID */
    VOS_UINT8                           ucDataCnt;                                      /* ͨ����trace���ݵĿ��� */
    VOS_UINT8                           aucReserve[2];
    DICC_TRACE_QUEUE_DATA_STRU          astQueueData[DICC_MAX_TRACE_QUEUE_DATA_CNT];    /* ͨ����ǰʮ������ */
} DICC_TRACE_QUEUE_STRU;

/* ͨ��״̬��¼ */
typedef struct
{
    DICC_ISR_OP_STRU                    stIsrOp;        /* ��ȷ�����жϵļ�¼ */
    DICC_CHAN_STATISTICS_STRU           stStatistics;       /* ͨ��ͳ����Ϣ */
} DICC_CHAN_STATUS_STRU;

/* DICC DFx�ṹ */
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enDFxEnabled;                           /* DFx����ʹ�����: TRUE��ʾʹ��, FALSE��ʾδʹ��, δʹ�����ܼ�¼ */
    VOS_UINT8                           aucReserve[3];
    DICC_CHAN_STATUS_STRU               astChanStatus[DICC_MAX_CHAN_NUM];       /* ͨ��״̬��¼ */
    DICC_ISR_DEBUG_STRU                 stIsrDbg;                               /* ������жϵļ�¼(�����ֺ�, ֻ��¼���һ��) */
} DICC_DFX_STRU;

/* �˼��ڴ�����ͨ��������ƽṹ */
typedef struct
{
    VOS_UINT32                  ulCurrSize;                                  /* �˼䵱ǰʹ�õ��ڴ��С, ��λ: �ֽ� */
    DICC_DFX_STRU               stDFx;
} DICC_CTRL_STRU;

/* �˼�����ͨ��������ƽṹ */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChanId;                            /* ͨ��ID */
    VOS_UINT8                           ucStateMask;                         /* ���ͨ�����˴򿪻��߹ر�״̬ */
    DICC_CHAN_INIT_STATUS_ENUM_UINT8    enValidFlag;                         /* ���ͨ���Ƿ��Ѿ���ʼ��, 1Ϊ��ʼ��; 0Ϊδ��ʼ�� */
    VOS_UINT8                           ucPriDataLen;                        /* �û�˽�����ݳ���, ��λ: �ֽ� */
    VOS_UINT16                          usChnBlkNum;                         /* �˼䴫���ڴ����� */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulTtfRingQStAddrOffSet;              /* �˼䴫����Ϣ����TTFRINGQST���ڴ�ƫ����, ��λ: �ֽ� */
    VOS_UINT32                          ulQueueNodeAddrOffSet;               /* �˼䴫����Ϣ���ݿ���ڴ�ƫ����, ��λ: �ֽ� */
    TTF_RING_Q_ST                       stRingBuffer;                        /* ���λ������ */
} DICC_CHAN_CTRL_STRU;

/* ��������Ϣ�����ݽṹ(Ҳ�ƺ˼䴫�ݽ��) */
typedef struct
{
    VOS_UINT16                  usIndex;                                     /* �˼䴫���ڴ���� */
    VOS_UINT16                  usMagicNum;                                  /* ���ڷ�ֹ������Ϣ���۸ĵ�ħ���� */
    VOS_UINT8                   ucPriDataLen;                                /* �����ݵ���Ϣ���ݳ���, ��λ: �ֽ� */
    VOS_UINT8                   aucReserve[3];
    VOS_UINT32                  ulInsertTime;                                /* �������ݵ�ʱ��, ��λ: slice */
    VOS_UINT8                   aucPriData[DICC_INFO_BLOCK_MAX_LEN];         /* �����ݵ���Ϣ���� */
} DICC_QUEUE_NODE_STRU;

/* DICCͨ������ӳ��� */
typedef struct
{
    DICC_CPU_ID_ENUM_UINT8      enLocalCpuId;                                /* CPUָʾ�� */
    DICC_CHAN_ID_ENUM_UINT8     aenSender[DICC_MAX_SENDER_NUM_PER_CPU];      /* ��¼�䵱sender��ͨ��ID,�ű�Ϊ�������� */
    DICC_CHAN_ID_ENUM_UINT8     aenRecver[DICC_MAX_RECVER_NUM_PER_CPU];      /* ��¼�䵱recver��ͨ��ID,�ű�Ϊ�������� */
    DICC_CHAN_ROLE_ENUM_UINT8   aenRole[DICC_MAX_CHAN_NUM];                  /* �ű�Ϊͨ���� */
    VOS_UINT8                   aucReserve[2];
    VOS_UINT8                   ucSemCreated;                                /* ���ڷ�ֹͬһ�����ظ�����Ӳ���ź���/���ػ����ź����Ļ����ʶ
                                                                                δ����ʱ, ����Ϊ0, ����������Ϊ1 */
    VOS_SEM                     ulDiccLocalMutexSem;                         /* ��ֹͬһʱ����һ�������ڻ���ı��ػ����ź��� */
    volatile DICC_CTRL_STRU    *pastDICCMgmt;                                /* DICC����ṹ���׵�ַ */
    VOS_UINT32                  ulPid;                                       /* DICC PID */
} DICC_CHAN_ROLE_STRU;

/* �жϲ��������¼ */
typedef struct
{
    VOS_UINT32                          ulIntLevel;    /* �жϷ���� */
    VOS_INT32                           lResult;       /* ������� */
}DICC_INT_OP_STRU;

/* ��ͨ����ʼ���ϱ���Ϣ */
typedef struct
{
    DICC_SERVICE_TYPE_ENUM_UINT8        enServiceType; /* �û���д�ķ���� */
    VOS_UINT8                           aucReserve[3];
    DICC_INIT_CHN_INFO_STRU             stInitPara;    /* ��¼�û���ʼ��ͨ������ */
    DICC_INT_OP_STRU                    stIntOp;       /* ��¼�����жϵĲ��� */
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;     /* ��¼�����ź������� */
} DICC_CHAN_SINGLE_INIT_CONTENT_STRU;

/* ˫ͨ����ʼ���ϱ���Ϣ */
typedef struct
{
    DICC_SERVICE_TYPE_ENUM_UINT8        enServiceType;      /* �û���д�ķ���� */
    VOS_UINT8                           aucReserve[3];
    DICC_INIT_CHN_INFO_STRU             stInitSendChanPara; /* ��¼�û���ʼ��ͨ������(�䵱�����߽�ɫ��ͨ��) */
    DICC_INIT_CHN_INFO_STRU             stInitRecvChanPara; /* ��¼�û���ʼ��ͨ������(�䵱�����߽�ɫ��ͨ��) */
    DICC_INT_OP_STRU                    stIntOp;            /* ��¼�����жϵĲ��� */
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;     /* ��¼�����ź������� */
} DICC_CHAN_DUAL_INIT_CONTENT_STRU;

/* ��ͨ������ */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    DICC_CHAN_ROLE_ENUM_UINT8           enUserRole;
    VOS_UINT8                           aucReserve[2];
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;     /* ��¼�����ź������� */
} DICC_CHAN_OPEN_PAPA_STRU;

/* �ر�ͨ������ */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           aucReserve[3];
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;     /* ��¼�����ź������� */
} DICC_CHAN_CLOSE_PAPA_STRU;

/* ����ͨ�����ݷ��͵ļ�¼ */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           aucReserve[3];
    DICC_INT_OP_STRU                    stIntOp;            /* �жϲ�����¼ */
} DICC_CHAN_TRIG_CONTENT_STRU;

/* DICCͨ����������ס, ��ʹ���߶�ȡ */
typedef struct
{
    VOS_UINT32                          ulResetSlice;       /* ���帴λʱ�� */
    DICC_TRACE_QUEUE_STRU               stTraceQueue;       /* ��λʱ, ���ڵ���ͨ�����ݵĽṹ */
    DICC_ISR_DEBUG_STRU                 stIsrDbg;           /* ������жϵļ�¼ */
    DICC_CHAN_STATUS_STRU               stChanStatus;       /* ͨ��״̬��¼ */
}DICC_CHAN_EXECPTION_STRU;

/* ͨ������������ݲ��� */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    DICC_CHAN_INIT_STATUS_ENUM_UINT8    enChanInitFlag;         /* ���ͨ���Ƿ��Ѿ���ʼ��, 1Ϊ��ʼ��; 0Ϊδ��ʼ�� */
    VOS_UINT8                           ucChanStateMask;        /* 0: ͨ������δ����, 1: �����Ͷ˿���, 2: �����ն˿���, 3: ���˶����� */
    VOS_UINT8                           aucReserve[1];
    DICC_INSERT_DSCP_BLK_STRU           stDscpBlk;              /* �û�����Ϣ���������ṹ */
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;         /* �ź���������¼ */
} DICC_CHAN_INSERT_PAPA_STRU;

/* ͨ��ȡ���������ݲ��� */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    DICC_CHAN_INIT_STATUS_ENUM_UINT8    enChanInitFlag;         /* ���ͨ���Ƿ��Ѿ���ʼ��, 1Ϊ��ʼ��; 0Ϊδ��ʼ�� */
    VOS_UINT8                           ucChanStateMask;        /* 0: ͨ������δ����, 1: �����Ͷ˿���, 2: �����ն˿���, 3: ���˶����� */
    VOS_UINT8                           ucFlushData;            /* 0: û�з���ȡ��, 1: ����ȡ�� */
    VOS_UINT8                          *pucToSaveUsrData;       /* �û��ṩ�����ڴ�ſ����Ϣ��ָ�� */
    DICC_QUEUE_NODE_STRU                stTamperedQueueNode;    /* ��˴�����Ϣ���۸ĵ��ֳ� */
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;         /* �ź���������¼ */
} DICC_CHAN_REMOVE_PAPA_STRU;

/* ��ȡͨ�����ݿ����������� */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    DICC_GET_CHN_NODE_CNT_ENUM_UINT8    enGetChnNodeCntType;    /* ����ָʾ��ȡͨ�����Ѿ���ŵ����ݸ���, ����ͨ���п��Լ�����ŵĸ��� */
    DICC_CHAN_INIT_STATUS_ENUM_UINT8    enChanInitFlag;         /* ���ͨ���Ƿ��Ѿ���ʼ��, 1Ϊ��ʼ��; 0Ϊδ��ʼ�� */
    VOS_UINT8                           ucChanStateMask;        /* 0: ͨ������δ����, 1: �����Ͷ˿���, 2: �����ն˿���, 3: ���˶����� */
} DICC_CHAN_GET_CNT_PAPA_STRU;

/* DICC�ϱ��û��쳣�����¼�(ͨ����ȫ�ر�ʱ, �����ݿ����) */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           ucFlushCnt;        /* ͨ����ȫ�ر�ʱ���������ݿ� */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulOpPid;           /* ����PID */
} DICC_CHAN_CLOSE_FLUSH_EVENT_STRU;

/* DICC�ϱ��û��쳣�����¼�(��ͨ��ȡ����ʱ, ���ݿ鱻�۸�) */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulOpPid;           /* ����PID */
    DICC_QUEUE_NODE_STRU                stQueueNode;       /* ���۸ĵ����ݽ�� */
} DICC_CHAN_MAGIC_NUM_CHANGED_EVENT_STRU;

/* DICC�ϱ��û��쳣�����¼�(��ͨ����������ʱ, ����ͨ��������) */
typedef struct
{
    DICC_CHAN_ID_ENUM_UINT8             ucChnId;
    VOS_UINT8                           aucReserve[3];
    VOS_UINT32                          ulOpPid;           /* ����PID */
    VOS_UINT32                          ulQueueFullCnt;    /* �ϱ��¼�ʱ, �������ܴ��� */
} DICC_CHAN_QUEUE_FULL_EVENT_STRU;

/* ��¼�û��жϲ����Ľṹ */
typedef struct
{
    VOS_UINT32                          ulPid;
    DICC_SERVICE_TYPE_ENUM_UINT8        enServiceType;
    DICC_SERVICE_ISR_OP_ENUM_UINT8      enIsrOp;           /* ���жϵĲ��� */
    PS_BOOL_ENUM_UINT8                  enOpResult;        /* PS_FALSE - ������ж� */
    VOS_UINT8                           aucReserve[1];
} DICC_RECORD_ISR_STRU;

/* ͬ��DICC�ڴ�����ʱ��������ļ�¼ */
typedef struct
{
    DICC_CHAN_LOCAL_SEM_PAPA_STRU       stLocalSemPara;    /* �����ź���������¼ */
    DICC_CHAN_HW_SEM_PAPA_STRU          stHwSemPara;       /* Ӳ���ź���������¼ */
    VOS_UINT32                          ulDiccMagic;
} DICC_CHAN_SYNC_PARA_STRU;

/* �����ڼ�, �ܱ�������벻����,
   ���������ڼ����, ��ΪOM task��������, LOG�򲻳���, ��Ҫ�ڴ��ڴ�ӡ
   ������ƴ˽ṹ, �����ִ��󶼼�¼��һ��, �����ڵ��������׶� */
typedef struct
{
    DICC_CPU_ID_ENUM_UINT8              enCpuId;          /* ����CPU-ID */
    DICC_TRACE_FUNC_MARK_ID_ENUM_UINT8  enFuncId;         /* ���ڸ���ִ�к��� */
    VOS_UINT8                           aucReserve[2];
    VOS_UINT32                          ulPid;            /* ����PID */
    VOS_UINT32                          ulLine;           /* �к� */
    DICC_ERROR_CODE_ENUM_UINT32         enResult;         /* ��¼������� */
} DICC_TRACE_INFO_STRU;

/* DICC��λ������Ϣ */
typedef struct
{
    VOS_UINT32                          ulModule;
    VOS_UINT32                          ulFile;
    VOS_UINT32                          ulLine;
    VOS_UINT8                          *pucData;
    VOS_UINT32                          ulDataLen;
} DICC_SOFT_REBOOT_INFO_STRU;

#if 0
typedef struct
{
    VOS_UINT32 ulErrChanBlkNum;  /* ͨ������������� */
    VOS_UINT32 ulErrChanBlkSize;      /* ͨ�����С������� */
    VOS_UINT32 ulErrMemSize;     /* ͨ���ڴ������������ */
    VOS_UINT32 ulErrRecvIsrNull;       /* ͨ�����ն��ź������Ϊ�մ��� */
    VOS_UINT32 ulErrChanIdUndefined; /* ͨ��δע����� */
    VOS_UINT32 ulErrInfoPtrNull; /* ͨ��һ����Ϣ�� */
    VOS_UINT32 ulErrServceUndefine;    /* ͨ������δע�� */
    VOS_UINT32 ulErrExistedChanId;    /* ͨ���ظ�ע�� */
    VOS_UINT32 ulErrChanIdNotMatchRole;    /* ͨ�������ɫ��ƥ�� */
    VOS_UINT32 ulErrChanAlreadyOpened;    /* ͨ���ظ��� */
    VOS_UINT32 ulErrInsertDespBlkPtrNull;    /* ͨ��������Ϣ������Ϊ�� */
    VOS_UINT32 ulErrInsertDespBlkDataNull;    /* ������ϢΪ�� */
    VOS_UINT32 ulErrDlvDataBlkSize;    /* ������Ϣ���С���� */
    VOS_UINT32 ulErrChanNotOpenInBothSides;    /* ���ݻ�ȡ����Ϣʱ, ͨ��δ��ȫ�� */
    VOS_UINT32 ulErrInvalidChanId;   /* ���Ϸ���ͨ��ID */
    VOS_UINT32 ulErrGetCntTypeUndefined;    /* ��ȡͨ������������ */
    VOS_UINT32 ulErrRemoveDataPtrNull;                          /* ���ȡ�����ݵ�ָ��Ϊ�� */
    VOS_UINT32 ulErrOpChanNotReady;    /* ͨ�����ƽṹδ׼���� */
    VOS_UINT32 ulErrGetNodeFail;    /* ��ȡ�˼䴫�ݽ��ʧ�� */
    VOS_UINT32 ulErrMagicNumChanged;    /* �˼䴫�����ݱ��۸� */
    VOS_UINT32 ulErrRingQueueFail;    /* �˼���в���ʧ�� */
    VOS_UINT32 ulErrLocalSemFail;    /* �����ź�������ʧ�� */
    VOS_UINT32 ulErrIsrConnectFail;    /* �жϹҽ�ʧ�� */
    VOS_UINT32 ulErrUseHwSemFail;    /* Ӳ���ź�������ʧ�� */
    VOS_UINT32 ulErrUseHwSemFail;    /* �����ж�ʧ�� */
} DICC_DEBUG_INFO_STRU;
#endif

#endif  /*FEATURE_ON == FEATURE_CSD*/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/******************************************************************************
  8 UNION����
******************************************************************************/


/******************************************************************************
  9 OTHERS����
******************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* Dicc.h */


