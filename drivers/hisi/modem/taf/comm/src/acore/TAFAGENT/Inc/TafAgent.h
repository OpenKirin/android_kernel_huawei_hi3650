

#ifndef _TAFAGENT_H_
#define _TAFAGENT_H_

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "MnCallApi.h"
#include  "MnErrorCode.h"
#include  "MnClient.h"
#include "TafAgentInterface.h"

#pragma pack(4)


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define  PS_SYNC_CNF_TIMEOUT_LEN                    (5000)

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
#define TAF_AGENT_TASK_PRIORITY                     (84)

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/
extern VOS_UINT32 TAF_AGENT_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);
extern VOS_VOID TAF_AGENT_ProcMsg(MsgBlock* pstMsg);

#ifdef DMT
extern VOS_UINT32 DMT_GetSysMode(TAF_AGENT_SYS_MODE_STRU *pstSysMode);
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

