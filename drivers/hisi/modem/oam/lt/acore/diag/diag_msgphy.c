




#include <mdrv.h>
#include "diag_msgphy.h"
#include "diag_debug.h"
#include "diag_common.h"
#include "diag_cfg.h"
#include "soc_socp_adapter.h"


#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGDSP_C



/*****************************************************************************
 Function Name   : diag_GuDspTransProc
 Description     : GU DSP������ֱ��͸����Ϣ��GUDSP������MSP����ظ�
 Input           : pData    ����������������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2015-06-14  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GuDspTransProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet                    = ERR_MSP_SUCCESS;
    DIAG_COMM_CNF_STRU stRttCnf         = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo   = {0};
    DIAG_OSA_MSG_STRU *pstMsg           = NULL;
    DIAG_OSA_MSG_STRU *pstVosMsg        = NULL;

    pstMsg = (DIAG_OSA_MSG_STRU *)(pData->aucData + sizeof(MSP_DIAG_DATA_REQ_STRU));

    pstVosMsg = (DIAG_OSA_MSG_STRU *)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, pstMsg->ulLength);

    if (pstVosMsg != NULL)
    {
        pstVosMsg->ulReceiverPid  = pstMsg->ulReceiverPid;

        VOS_MemCpy(&pstVosMsg->ulMsgId, &pstMsg->ulMsgId, pstMsg->ulLength);

        ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstVosMsg);
        if (ulRet != VOS_OK)
        {
            diag_printf("diag_debug_write VOS_SendMsg failed!\n");
        }
    }

    stRttCnf.ulRet  = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo, stRttCnf, pData);

    stDiagInfo.ulMsgType = pData->stID.pri4b;

    /*����ظ�*/
    ulRet = DIAG_MsgReport(&stDiagInfo, &stRttCnf, sizeof(stRttCnf));

    return ulRet;
}



/*****************************************************************************
 Function Name   : diag_DspMsgProc
 Description     : DSP������Ϣ����������ӶϿ�
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_UINT32 diag_DspMsgProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ulRet                    = ERR_MSP_SUCCESS;
    DIAG_COMM_CNF_STRU stRttCnf         = {0};
    MSP_DIAG_CNF_INFO_STRU stDiagInfo   = {0};

    VOS_UINT32 ulLen;
    DIAG_PHY_MSG_A_TRANS_C_STRU *pstInfo;

    switch(pData->stID.mode4b)
    {
        /* GUDSP��������A��ֱ��͸����GUDSP���� */
        case DIAG_MODE_GSM:
        case DIAG_MODE_UMTS:
        case DIAG_MODE_1X:
        case DIAG_MODE_HRPD:
            return diag_GuDspTransProc(pData);

        default:
            break;

        /* GU����Ϣ�Ѿ���A�˴���C��ֻ����TL������ */
    }

    ulLen = sizeof(DIAG_PHY_MSG_A_TRANS_C_STRU)-VOS_MSG_HEAD_LENGTH + pData->ulMsgLen;
    pstInfo = (DIAG_PHY_MSG_A_TRANS_C_STRU*)VOS_AllocMsg(MSP_PID_DIAG_APP_AGENT, ulLen);
    if(VOS_NULL == pstInfo)
    {
        ulRet = ERR_MSP_MALLOC_FAILUE;
        goto DIAG_ERROR;
    }
    pstInfo->ulReceiverPid = MSP_PID_DIAG_AGENT;
    pstInfo->ulSenderPid   = MSP_PID_DIAG_APP_AGENT;
    pstInfo->ulMsgId       = DIAG_MSG_PHY_A_TRANS_C_REQ;
    ulLen = sizeof(DIAG_FRAME_INFO_STRU)+pData->ulMsgLen;
    (VOS_VOID)VOS_MemCpy(&pstInfo->stInfo, pData, ulLen);
    ulRet = VOS_SendMsg(MSP_PID_DIAG_APP_AGENT, pstInfo);
    if(ulRet)
    {
        goto DIAG_ERROR;
    }

    return ulRet;
DIAG_ERROR:

    stRttCnf.ulRet = ulRet;
    DIAG_MSG_COMMON_PROC(stDiagInfo, stRttCnf, pData);

    stDiagInfo.ulMsgType = pData->stID.pri4b;
    stDiagInfo.ulMode    = pData->stID.mode4b;

    /*����ظ�*/
    ulRet = DIAG_MsgReport(&stDiagInfo, &stRttCnf, sizeof(stRttCnf));
    return ulRet;
}

/*****************************************************************************
 Function Name   : diag_DspMsgInit
 Description     : MSP dsp���ֳ�ʼ��
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_DspMsgInit(VOS_VOID)
{

    /*ע��message��Ϣ�ص�*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_PHY, diag_DspMsgProc);

}




