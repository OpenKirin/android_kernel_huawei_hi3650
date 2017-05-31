



#include "diag_msghifi.h"
#include "diag_debug.h"
#include "diag_common.h"

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGHIFI_C


/*****************************************************************************
 Function Name   : diag_HifiMsgProc
 Description     : HIFI命令直接透传消息给HIFI，并由MSP代替回复
 Input           : VOS_UINT8* pstReq
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2015-06-14  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_HifiMsgProc(DIAG_FRAME_INFO_STRU* pstReq)
{
    VOS_UINT32 ulRet                    = ERR_MSP_SUCCESS;
    DIAG_COMM_CNF_STRU stHifiCnf        = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo   = {0};
    
    VOS_UINT32 ulLen;
    DIAG_HIFI_MSG_A_TRANS_C_STRU *pstInfo;

    ulLen = sizeof(DIAG_HIFI_MSG_A_TRANS_C_STRU) - VOS_MSG_HEAD_LENGTH + pstReq->ulMsgLen;
    pstInfo = (DIAG_HIFI_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);
    if(VOS_NULL == pstInfo)
    {
        ulRet = ERR_MSP_MALLOC_FAILUE;
        goto DIAG_ERROR;
    }
    
    pstInfo->ulReceiverPid = MSP_PID_DIAG_AGENT;
    pstInfo->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    pstInfo->ulMsgId       = DIAG_MSG_HIFI_A_TRANS_C_REQ;
    
    ulLen = sizeof(DIAG_FRAME_INFO_STRU) + pstReq->ulMsgLen;
    (VOS_VOID)VOS_MemCpy(&pstInfo->stInfo, pstReq, ulLen);
    
    ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo);
    if(ulRet)
    {
        goto DIAG_ERROR;
    }

    return ulRet;
    
DIAG_ERROR:
    

    stHifiCnf.ulRet  = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo, stHifiCnf, pstReq);

    stDiagInfo.ulMsgType = pstReq->stID.pri4b;

    /*组包回复*/
    ulRet = DIAG_MsgReport(&stDiagInfo, &stHifiCnf, sizeof(stHifiCnf));

    return ulRet;
}


/*****************************************************************************
 Function Name   : diag_HifiMsgInit
 Description     : MSG HIFI部分初始化
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_HifiMsgInit(VOS_VOID)
{
    /*注册message消息回调*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_AUDIO, diag_HifiMsgProc);
}



