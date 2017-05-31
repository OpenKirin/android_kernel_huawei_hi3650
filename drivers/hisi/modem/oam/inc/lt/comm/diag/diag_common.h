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


#ifndef __DIAG_COMMON_H__
#define __DIAG_COMMON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "msp_diag.h"
#include "msp_debug.h"

/*****************************************************************************
  2 macro
*****************************************************************************/

/* ��֡��󳤶� */
#define DIAG_FRAME_MAX_LEN      (4*1024)

/* �ܳ������ֵ */
#define DIAG_FRAME_SUM_LEN      (DIAG_FRAME_MAX_LEN * 16)

/* DIAG��������ͷ�ĳ��� */
#define DIAG_MESSAGE_DATA_HEADER_LEN  (sizeof(DIAG_SERVICE_HEAD_STRU)   \
                                     + sizeof(DIAG_MSG_INFO_STRU)       \
                                     + sizeof(MSP_DIAG_DATA_REQ_STRU))

#if (VOS_OS_VER == VOS_LINUX)
#define DIAG_SSID_CPU       DIAG_SSID_APP_CPU
#define DIAG_AGENT_PID      MSP_PID_DIAG_APP_AGENT
#else
#define DIAG_SSID_CPU       DIAG_SSID_MODEM_CPU
#define DIAG_AGENT_PID      MSP_PID_DIAG_AGENT
#endif

#define DIAG_MSG_COMMON_PROC(stDiagInfo, Cnf, pData)    \
do{                                                     \
    stDiagInfo.ulSSId       = DIAG_SSID_CPU;            \
    stDiagInfo.ulMode       = pData->stID.mode4b;                        \
    stDiagInfo.ulSubType    = pData->stID.sec5b;        \
    stDiagInfo.ulDirection  = DIAG_MT_CNF;              \
    stDiagInfo.ulModemid    = 0;                        \
    stDiagInfo.ulMsgId      = pData->ulCmdId;           \
    stDiagInfo.ulTransId    = pData->stService.ulMsgTransId;            \
    Cnf.ulAuid = ((MSP_DIAG_DATA_REQ_STRU*)(pData->aucData))->ulAuid;   \
    Cnf.ulSn = ((MSP_DIAG_DATA_REQ_STRU*)(pData->aucData))->ulSn;       \
}while(0)


#define DIAG_MSG_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ret) \
do {    \
    ulLen = sizeof(DIAG_MSG_A_TRANS_C_STRU)-VOS_MSG_HEAD_LENGTH + pstDiagHead->ulMsgLen;  \
    pstInfo = (DIAG_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);  \
    if(VOS_NULL == pstInfo) \
    {   \
        ret = ERR_MSP_MALLOC_FAILUE;    \
        goto DIAG_ERROR;    \
    }   \
    pstInfo->ulReceiverPid = MSP_PID_DIAG_AGENT;    \
    pstInfo->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;    \
    pstInfo->ulMsgId       = DIAG_MSG_MSP_A_TRANS_C_REQ;    \
    ulLen = sizeof(DIAG_FRAME_INFO_STRU)+pstDiagHead->ulMsgLen; \
    VOS_MemCpy(&pstInfo->stInfo, pstDiagHead, ulLen);   \
    ret = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo); \
    if(ret) \
    {   \
        goto DIAG_ERROR;    \
    }   \
}while(0)


/* debug��ʱ��ʱ�� */
#define DIAG_DEBUG_TIMER_LEN      (5*1000)


#define     DIAG_ERRORLOG_TIMER_NAME        (0x00001001)
#define     DIAG_CLTINFO_TIMER_NAME         (0x00002002)
#define     DIAG_DEBUG_TIMER_NAME           (0x00003003)

#define     DIAG_ERRORLOG_TIMER_PARA        (0x0000EFFE)
#define     DIAG_CLTINFO_TIMER_PARA         (0x0000DFFD)
#define     DIAG_DEBUG_TIMER_PARA           (0x0000CFFC)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/
#define     DIAG_MSG_MSP_CONN_REQ               0x00000001
#define     DIAG_MSG_MSP_DISCONN_REQ            0x00000002
#define     DIAG_MSG_MSP_A_TRANS_C_REQ          0x00000003
#define     DIAG_MSG_BSP_A_TRANS_C_REQ          0x00000004
#define     DIAG_MSG_BBP_A_TRANS_C_REQ          0x00000005
#define     DIAG_MSG_PHY_A_TRANS_C_REQ          0x00000006

#define     DIAG_MSG_DIAG_SOCP_VOTE_REQ         0x00000007
#define     DIAG_MSG_DIAG_SOCP_VOTE_CNF         DIAG_MSG_DIAG_SOCP_VOTE_REQ

#define     DIAG_MSG_PHY_SOCP_VOTE_REQ          0x00000008
#define     DIAG_MSG_PHY_SOCP_VOTE_CNF          DIAG_MSG_PHY_SOCP_VOTE_REQ

#define     DIAG_MSG_MSP_A_DEBUG_C_REQ          0x00000009      /* ֪ͨC�˱���debug��Ϣ */

#define     DIAG_MSG_BSP_NV_AUTH_REQ            0x0000000A      /* ֪ͨA�˼�Ȩ��Ϣ */

#define     DIAG_MSG_HIFI_A_TRANS_C_REQ         0x0000000B

#define     DIAG_MSG_UPHY_SOCP_VOTE_REQ         0x0000FE20      /* ��GU�����Լ������ϢID����16��Ч */

/*****************************************************************************
  4 Enum
*****************************************************************************/


/* MSP_DIAG_STID_STRU:cmdid19b */

/*****************************************************************************
0.	HSO���ӹ����ࣨ0x5000-0x50ff ��
1.	�Ĵ��������ࣨ0x5100-0x51ff ��
2.	���ɲ�����  ��0x5200-0x52ff ��
3.	����������  ��0x5300-0x53ff ��
4.	�Զ�����    ��0x5400-0x54ff ��
5.	NV������    ��0x5500-0x55ff ��
*****************************************************************************/
#define DIAG_CATEGORY_CONN             (0)
#define DIAG_CATEGORY_PS               (1)
#define DIAG_CATEGORY_BBP              (2)
#define DIAG_CATEGORY_CFG              (3)
#define DIAG_CATEGORY_GTR              (4)
#define DIAG_CATEGORY_NV               (5)
#define DIAG_CATEGORY_FS               (6)

/* HIDS���ӹ����ࣨ0x5000-0x50ff��*/
#define DIAG_CMD_HOST_CONNECT                   (0x10065000)
#define DIAG_CMD_HOST_CONNECT_AGENT             (0x10066000)
#define DIAG_CMD_HOST_DISCONNECT                (0x10065001)
#define DIAG_CMD_MODEM_WILL_RESET               (0x10014000)
#define DIAG_CMD_GET_TIMESTAMP_VALUE            (0x10014001)
#define DIAG_CMD_GET_MODEM_NUM                  (0x10014002)
#define DIAG_CMD_PID_TABLE_MSG                  (0x10014003)

/*2.	��ʱ�ࣨ0x5100-0x51ff��*/
#define DIAG_CMD_TIMER_OUT_IND                  (0x10015100)

/*3.	���������ࣨ0x5300-0x53ff��*/
#define DIAG_CMD_LOG_CAT_PRINT                  (0x10015310)
#define DIAG_CMD_LOG_CAT_LAYER                  (0x10015311)
#define DIAG_CMD_LOG_CAT_AIR                    (0x10015312)
// #define DIAG_CMD_LOG_CAT_USERPLANE              (0x10015313)    /* delete */
#define DIAG_CMD_LOG_CAT_L1                     (0x10015314)    /* TODO */
#define DIAG_CMD_LOG_CAT_EVENT                  (0x10015315)
#define DIAG_CMD_LOG_CAT_CMD                    (0x10015316)    /* TODO */
#define DIAG_CMD_LOG_CAT_MSG                    (0x10015317)

/* �Զ����ࣨ0x5400-0x54ff��*/
#define DIAG_CMD_GTR_SET                        (0x10015454)
#define DIAG_CMD_GU_GTR_SET                     (0x10015455)    /* GU��RTT���ԣ�ֻת�������ظ� */


/*BBP	���ɲ����� */
#define DIAG_CMD_DRX_SAMPLE_GEN_REQ             (0x4001521B)    /* �͹�������ͨ������*/
#define DIAG_CMD_DRX_SAMPLE_ADDR_REQ            (0x4001521C)    /* �͹�������Hids ��ȡ����ַ*/
#define DIAG_CMD_DRX_SAMPLE_CHNSIZE_REQ         (0x4001521D)    /* �͹������ɻ�ȡͨ����С*/
#define DIAG_CMD_DRX_SAMPLE_GET_VERSION_REQ     (0x4001521E)    /* �͹������ɻ�ȡ�汾��Ϣ*/
#define DIAG_CMD_DRX_SAMPLE_ABLE_CHN_REQ       	(0x4001521F)    /* �͹���������������ͨ����ַ*/


/* BSP CFG BEGIN*/
#define DIAG_CMD_DRX_BSP_SLEEP_IND              (0x90015220)					//�͹��Ŀ�ά�ɲ��ϱ�IND
#define DIAG_CMD_DRX_CHIP_TEMP_IND              (0x90015221)					//�͹��Ŀ�άоƬ�¶��ϱ�IND
#define DIAG_CMD_DRX_BATTERIES_TEMP_IND         (0x90015222)					//�͹��Ŀ�ά����¶��ϱ�IND

#define DIAG_CMD_BSP_LOG_SET_ACORE              (0x90015308)
#define DIAG_CMD_BSP_LOG_SET_CCORE              (0x90015309)

#define DIAG_CMD_BSP_SYSVIEW_SWT_ACORE          (0x9001530A)
#define DIAG_CMD_BSP_SYSVIEW_SWT_CCORE          (0x9001530B)

#define DIAG_CMD_BSP_SYSVIEW_IND_ACORE          (0x90015310)
#define DIAG_CMD_BSP_SYSVIEW_IND_CCORE          (0x90015311)

#define DIAG_CMD_BSP_AXI_DATA_SAMPLE            (0x9001530C)
#define DIAG_CMD_BSP_AXI_DATA_EXPORT            (0x9001530D)
#define DIAG_CMD_BSP_AXI_DATA_MONITOR           (0x9001530F)
#define DIAG_CMD_AXI_DATA_CONFIG                (0x90015318)
#define DIAG_CMD_AXI_REG_CONFIG                 (0x90015319)
#define DIAG_CMD_AXI_DATA_CTRL                  (0x9001531A)
#define DIAG_CMD_AXI_MON_CONFIG                 (0x9001531B)
#define DIAG_CMD_AXI_MON_START                  (0x9001531C)
#define DIAG_CMD_AXI_MON_TERMINATE              (0x9001531D)

#define DIAG_CMD_UTRACE_START                   (0x9001531E)
#define DIAG_CMD_UTRACE_TERMINATE               (0x9001531F)

#define DIAG_CMD_BSP_CPU_SWT_ACORE              (0x90015320)
#define DIAG_CMD_BSP_CPU_SWT_CCORE              (0x90015321)

/* �ļ������ࣨ0x5600-0x56ff��*/
#define DIAG_CMD_FS_QUERY_DIR                   (0x90015601)
#define DIAG_CMD_FS_SCAN_DIR                    (0x90015602)
#define DIAG_CMD_FS_MAKE_DIR                    (0x90015603)
#define DIAG_CMD_FS_OPEN                        (0x90015604)
#define DIAG_CMD_FS_IMPORT                      (0x90015605)
#define DIAG_CMD_FS_EXPORT                      (0x90015606)
#define DIAG_CMD_FS_DELETE                      (0x90015607)
#define DIAG_CMD_FS_SPACE                       (0x90015608)

/* NV�����ࣨ0x5500-0x55ff��*/
#define DIAG_CMD_NV_WR                          (0x90015001)
#define DIAG_CMD_NV_RD                          (0x90015003)
#define DIAG_CMD_GET_NV_LIST                    (0x90015005)
#define DIAG_CMD_NV_AUTH                        (0x90015007)

/* APP LOG */
#define DIAG_CMD_APPLOG_CONFIG                  (0xEF000001)

/* ======================================================================== */

enum DIAG_CONNECT_CMD_ENUM
{
    DIAG_CONNECT_CMD,       /* �������� */
    DIAG_DISCONNECT_CMD,    /* �Ͽ��������� */
    DIAG_CONNECT_CMD_BUTT
};
typedef VOS_UINT32 DIAG_CONNECT_CMD_ENUM_U32;

/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/* �˽ṹ����OSA��MsgBlock��Ӧ�����������޸� */
#pragma pack(1)
typedef struct
{
    VOS_UINT32    ulSenderCpuId;
    VOS_UINT32    ulSenderPid;
    VOS_UINT32    ulReceiverCpuid;
    VOS_UINT32    ulReceiverPid;
    VOS_UINT32    ulLength;
    VOS_UINT32    ulMsgId;
    VOS_UINT8     aucValue[0];
}DIAG_OSA_MSG_STRU;
#pragma pack()


/* ֻ�������ͨ�ûظ��ṹ */
typedef struct
{
    VOS_UINT32  ulAuid;
    VOS_UINT32  ulSn;
    VOS_UINT32  ulRet;
}DIAG_COMM_CNF_STRU;


/* ==============��ϢӦ���ϱ��ӿڲ���====================================== */

typedef struct
{
    DIAG_SSID_TYPE_U32  ulSsid;
    VOS_UINT32          ulModemId;
    VOS_UINT32          ulDirection;    /* 1-req; 2-cnf; 3-ind */
    VOS_UINT32          ulMsgTransId;   /* trans id */
    VOS_UINT32          ulChanId;       /* SOCP channel id */

    union
    {
        VOS_UINT32          ulID;           /* �ṹ��ID */
        MSP_DIAG_STID_STRU  stID;
    }u;

    VOS_UINT32          ulHeaderSize;   /* ����ͷ�ĳ��� */
    VOS_VOID            *pHeaderData;   /* ����ͷ */

    VOS_UINT32          ulDataSize;     /* ucData�ĳ��� */
    VOS_VOID            *pData;         /* ���� */
}DIAG_MSG_REPORT_HEAD_STRU;

/* ======================================================================== */

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32              ulMsgId;           /* ��Ϣ�� */
    VOS_UINT32              ulLen;             /* ���ݳ��� */
    VOS_UINT8               pContext[0];       /* ������ʵ��ַ*/
}DIAG_DATA_MSG_STRU;



/* ==============��ϢӦ���ϱ��ӿڲ���====================================== */

/*diag printV��������ֽ���,����ǰ���ļ������кų��ȣ�-1��Ԥ��\0������*/
#define DIAG_PRINTF_MAX_LEN 	(1000-1)

typedef struct
{
    VOS_UINT32 ulModule;                        /* ��ӡ��Ϣ���ڵ�ģ��ID */
    VOS_UINT32 ulLevel;                         /* ������� */
    VOS_UINT32 ulNo;                            /* IND��� */
    VOS_CHAR   szText[DIAG_PRINTF_MAX_LEN+1];   /* ���д�ӡ�ı����ݣ����ܰ����ļ����к�,��'\0'��β */
} DIAG_CMD_LOG_PRINT_RAW_TXT_IND_STRU;


/* diag event report�ϱ���Ϣ�Ľṹ�� */
typedef struct
{
    VOS_UINT32 ulNo;      /* ���*/
    VOS_UINT32 ulId;      /* ��Ϣ�����¼�ID,��Ҫ�����Ϣ,�տ�,�¼�,��ͨ��ӡ���ʱ�ó�ԱΪ��*/
    VOS_UINT32 ulModule;  /* ��ӡ��Ϣ���ڵ�ģ��ID */
    VOS_INT8   aucDta[0]; /* �û����ݻ�����*/
} DIAG_CMD_LOG_EVENT_IND_STRU;

/* diag air report�ϱ���Ϣ�Ľṹ�� */
typedef struct
{
    VOS_UINT32 ulModule;     /* Դģ��ID*/
    VOS_UINT32 ulSide;       /* 1: NET-->UE, 2: UE-->NET*/
    VOS_UINT32 ulNo;         /* ���*/
    VOS_UINT32 ulId;         /* ID*/
    VOS_INT8 aucDta[0];     /* �û����ݻ�����*/
} DIAG_CMD_LOG_AIR_IND_STRU;

/* diag volte report�ϱ���Ϣ�Ľṹ�� */
typedef struct
{
    VOS_UINT32 ulModule;     /* Դģ��ID*/
    VOS_UINT32 ulSide;       /* 1: NET-->UE, 2: UE-->NET*/
    VOS_UINT32 ulNo;         /* ���*/
    VOS_UINT32 ulId;         /* ID*/
    VOS_INT8   aucDta[0];    /* �û����ݻ�����*/
} DIAG_CMD_LOG_VOLTE_IND_STRU;


/* diag userplane report�ϱ���Ϣ�Ľṹ�� */
typedef struct
{
    VOS_UINT32 ulModule;     /* Դģ��ID*/
    VOS_UINT32 ulNo;         /* ���*/
    VOS_UINT32 ulId;         /* ID*/
    VOS_INT8 aucDta[0];     /* �û����ݻ�����*/
} DIAG_CMD_LOG_USERPLANE_IND_STRU;


/* diag �ṹ�������ϱ���Ϣ�Ľṹ�� */
typedef struct
{
    VOS_UINT32 ulModule;     /* Դģ��ID*/
    VOS_UINT32 ulMsgId;      /* ID*/
    VOS_UINT32 ulNo;         /* ���*/
    VOS_INT8   aucDta[0];    /* �û����ݻ�����*/
} DIAG_CMD_TRANS_IND_STRU;


/* diag trace report�ϱ���Ϣ�Ľṹ�� */
typedef struct
{
    VOS_UINT32 ulModule;     /* Դģ��ID*/
    VOS_UINT32 ulDestMod;    /* Ŀ��ģ��ID*/
    VOS_UINT32 ulNo;         /* ���*/
    VOS_UINT32 ulId;         /* ID*/
    VOS_INT8 aucDta[0];     /* �û����ݻ�����*/
} DIAG_CMD_LOG_LAYER_IND_STRU;

/* ======================================================================== */



#if (VOS_LINUX== VOS_OS_VER)

typedef struct
{
    VOS_UINT32  ulVoteId;
    VOS_UINT32  ulVoteType;
    VOS_UINT32  ulVoteTime;
} DIAG_SOCP_VOTE_INFO_STRU;

#endif


typedef struct
{
    VOS_UINT32  ulIndex;
    VOS_UINT32  ulEnd;
    VOS_UINT8   auctime[8];
    VOS_UINT32  ulLen;
    VOS_UINT8  *pData;
} DIAG_PACKET_INFO_STRU;


/* ======================================================================== */
/* DIAG dump */

#define DIAG_DUMP_LEN 	    (0x2000)
#define DIAG_DUMP_MSG_LEN   (0x400)     /* ��Ϣ����1K/(4*4)=64�� */
#define DIAG_DUMP_DF_LEN    (0x800)     /* ��������2K */

typedef struct
{
    VOS_CHAR *      pcDumpAddr;

    VOS_CHAR *      pcMsgAddr;          /* message��ʼ��ַ */
    VOS_UINT32      ulMsgLen;           /* message�ռ䳤�� */
    VOS_UINT32      ulMsgCur;           /* message�ռ䵱ǰָ�� */
    
    VOS_CHAR *      pcDFAddr;           /* data flow��ʼ��ַ */
    VOS_UINT32      ulDFLen;            /* data flow�ռ䳤�� */
    VOS_UINT32      ulDFCur;            /* data flow�ռ䵱ǰָ�� */
}DIAG_DUMP_INFO_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/
#if(VOS_OS_VER == VOS_LINUX)

/* �˽ӿ��в�������taskdelay����ȡ�ź������������� */
typedef VOS_UINT32 (*DIAG_MESSAGE_FUNC)(DIAG_FRAME_INFO_STRU *pData);

/* ����������ص�ע��ӿ� */
extern VOS_UINT32 DIAG_MsgProcReg (DIAG_MESSAGE_TYPE_U32 ulMsgType, DIAG_MESSAGE_FUNC pMsgfn);

typedef unsigned int (*DIAG_SERVICE_FUNC)(DIAG_FRAME_INFO_STRU *pData);

/* ������ݷ����ص�ע��ӿ� */
extern VOS_VOID diag_ServiceProcReg(DIAG_SERVICE_FUNC pServiceFn);

extern VOS_VOID diag_MessageInit(VOS_VOID);

#endif

#if ((VOS_OS_VER == VOS_RTOSCK) || (VOS_OS_VER == VOS_VXWORKS))

extern VOS_UINT32 diag_AgentMsgProcInit(enum VOS_INIT_PHASE_DEFINE ip);

extern VOS_VOID diag_AgentMsgProc(MsgBlock* pMsgBlock);

extern VOS_VOID diag_AgentPsTransRcv(MsgBlock* pMsgBlock);

extern VOS_UINT32 diag_ProcAppAgentMsg(MsgBlock* pMsgBlock);
#endif
/* DIAGȫ����Ϣ��ʼ���ӿ� */
extern VOS_VOID diag_ServiceInit(VOS_VOID);
extern VOS_VOID diag_MspMsgInit(VOS_VOID);

extern VOS_UINT32 diag_SendMsg(VOS_UINT32 ulSenderId, VOS_UINT32 ulRecverId, VOS_UINT32 ulMsgId, VOS_UINT8* pDta, VOS_UINT32 dtaSize);

/* ������ݷ�������ӿ� */
extern VOS_UINT32 diag_ServicePackData(DIAG_MSG_REPORT_HEAD_STRU *pData);

extern VOS_UINT32 DIAG_MsgReport (MSP_DIAG_CNF_INFO_STRU *pstDiagInfo, VOS_VOID *pstData, VOS_UINT32 ulLen);

extern VOS_UINT32 diag_SetChanDisconn(MsgBlock* pMsgBlock);

extern VOS_UINT32 diag_SrvcPackFirst(DIAG_MSG_REPORT_HEAD_STRU *pData, VOS_UINT8 *puctime);

extern VOS_UINT32 diag_SrvcPackOther(DIAG_PACKET_INFO_STRU *pPacket, DIAG_MSG_REPORT_HEAD_STRU *pstMsg);

extern VOS_VOID diag_AgentVoteToSocp(SOCP_VOTE_TYPE_ENUM_U32 voteType);

extern VOS_UINT32 diag_AgentSocpVoteCnfMsgProc(MsgBlock * pMsgBlock);

extern VOS_VOID diag_DumpDFInfo(DIAG_FRAME_INFO_STRU * pFrame);

/*****************************************************************************
  9 OTHERS
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of msp_common.h */

