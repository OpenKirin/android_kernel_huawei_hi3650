


#include "diag_common.h"
#include "diag_msgmsp.h"
#include "diag_msgbbp.h"
#include "diag_msgps.h"
#include "diag_cfg.h"
#include "msp_errno.h"
#include "diag_debug.h"
#include "diag_api.h"



#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGMSP_C

typedef VOS_UINT32 (*DIAG_MSGMSP_PROC_FUNC)(VOS_UINT8* pstReq);

typedef struct
{
    VOS_UINT32              ulCmdId;
    DIAG_MSGMSP_PROC_FUNC   pfnProc;
}DIAG_MSGMSP_PROC_STRU;


DIAG_MSGMSP_PROC_STRU g_astMsgMsp[] =
{
    {DIAG_CMD_LOG_CAT_PRINT,        diag_PrintCfgProc},
    {DIAG_CMD_LOG_CAT_LAYER,        diag_LayerCfgProc},
    {DIAG_CMD_LOG_CAT_AIR,          diag_AirCfgProc},
    {DIAG_CMD_LOG_CAT_EVENT,        diag_EventCfgProc},
    {DIAG_CMD_LOG_CAT_MSG,          diag_MsgCfgProc},

    {DIAG_CMD_GTR_SET,              diag_GtrProcEntry},
    {DIAG_CMD_GU_GTR_SET,           diag_GuGtrProcEntry},

    {DIAG_CMD_HOST_DISCONNECT,      diag_DisConnProc},

    {DIAG_CMD_HOST_CONNECT,         diag_ConnProc},
    {DIAG_CMD_HOST_CONNECT_AGENT,   diag_ConnProc},
    {DIAG_CMD_GET_TIMESTAMP_VALUE,  diag_GetTimeStampInitValue},
    {DIAG_CMD_GET_MODEM_NUM,        diag_GetModemNum},
    {DIAG_CMD_PID_TABLE_MSG,        diag_GetPidTable},

};

VOS_UINT32 diag_MspMsgProc(DIAG_FRAME_INFO_STRU *pData);

/*****************************************************************************
 Function Name   : diag_MspMsgInit
 Description     : MSP��������ʼ���ӿ�

 History         :
    1.c64416         2014-11-18  Draft Enact

*****************************************************************************/
void diag_MspMsgInit(void)
{
    VOS_UINT32 ulRet;

    ulRet = DIAG_MsgProcReg(DIAG_MSG_TYPE_MSP, diag_MspMsgProc);
    if(VOS_OK != ulRet)
    {
        diag_printf("diag_MspMsgInit DIAG_MsgProcReg failed.\n");
    }
}

/*****************************************************************************
 Function Name   : diag_GetModemNum
 Description     : ��ȡmodem num
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

    1.c00326366      2012-11-22  Draft Enact
*****************************************************************************/
VOS_UINT32 diag_GetModemNum(VOS_UINT8* pstReq)
{
    VOS_UINT ret = ERR_MSP_SUCCESS;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_CMD_GET_MODEM_NUM_CNF_STRU stModemNum = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    DIAG_MSG_COMMON_PROC(stDiagInfo, stModemNum, pstDiagHead);

    stDiagInfo.ulMsgType = DIAG_MSG_TYPE_MSP;

    stModemNum.ulNum = 3;

    stModemNum.ulRc  = ERR_MSP_SUCCESS;

    /*�����FW�ظ�*/
    ret = DIAG_MsgReport(&stDiagInfo, &stModemNum, sizeof(stModemNum));

    return (VOS_UINT32)ret;
}


/*****************************************************************************
 Function Name   : diag_GetPidTable
 Description     : ��ȡPID�б�
 Input           : pstReq ����������
 Output          : None
 Return          : VOS_UINT32

    1.c00326366      2016-02-14  Draft Enact
*****************************************************************************/
VOS_UINT32 diag_GetPidTable(VOS_UINT8* pstReq)
{
    VOS_UINT32 i, num, ulRc, len, ret;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_CMD_PID_TABLE_CNF_STRU *pstPidTable = VOS_NULL;
    DIAG_FRAME_INFO_STRU *pstDiagHead = VOS_NULL;
    VOS_UINT32 *pulPid = VOS_NULL;

    num = (VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND) + (VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND);

    pulPid = (VOS_UINT32 *)VOS_MemAlloc(DIAG_AGENT_PID, DYNAMIC_MEM_PT, (num * sizeof(VOS_UINT32)));

    num  = 0;
    ulRc = ERR_MSP_SUCCESS;

    if(VOS_NULL == pulPid)
    {
        ulRc = ERR_MSP_DIAG_UNKNOWNPID_CMD;
        return ERR_MSP_FAILURE;
    }
    else
    {
        /* ��ȡA��PID table */
        for(i = 0; i < (VOS_CPU_ID_1_PID_BUTT - VOS_PID_CPU_ID_1_DOPRAEND); i++)
        {
            if(VOS_PID_AVAILABLE == VOS_CheckPidValidity(VOS_PID_CPU_ID_1_DOPRAEND + i))
            {
                pulPid[num++] = (VOS_PID_CPU_ID_1_DOPRAEND + i);
            }
        }

        /* ��ȡC��PID table */
        for(i = 0; i < (VOS_CPU_ID_0_PID_BUTT - VOS_PID_CPU_ID_0_DOPRAEND); i++)
        {
            if(VOS_PID_AVAILABLE == VOS_CheckPidValidity(VOS_PID_CPU_ID_0_DOPRAEND + i))
            {
                pulPid[num++] = (VOS_PID_CPU_ID_0_DOPRAEND + i);
            }
        }
    }

    len = sizeof(DIAG_CMD_PID_TABLE_CNF_STRU) + (num * sizeof(VOS_UINT32));
    pstPidTable = (DIAG_CMD_PID_TABLE_CNF_STRU *)VOS_MemAlloc(DIAG_AGENT_PID, DYNAMIC_MEM_PT, len);
    if(VOS_NULL == pstPidTable)
    {
        VOS_MemFree(DIAG_AGENT_PID, pulPid);
        return ERR_MSP_FAILURE;
    }

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    DIAG_MSG_COMMON_PROC(stDiagInfo, (*pstPidTable), pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_MSP;

    pstPidTable->ulRc       = ulRc;
    pstPidTable->ulPidNum   = num;

    VOS_MemCpy(pstPidTable->aulPid, pulPid, num*sizeof(VOS_UINT32));

    ret = DIAG_MsgReport(&stDiagInfo, pstPidTable, len);

    VOS_MemFree(DIAG_AGENT_PID, pulPid);
    VOS_MemFree(DIAG_AGENT_PID, pstPidTable);

    return (VOS_UINT32)ret;
}




/*****************************************************************************
 Function Name   : diag_GuGtrProcEntry
 Description     : GU��RTT���������ֻ��Ҫ͸��������Ҫ�ظ�
                    1. ԭֵ͸�������ı�senderpid
                    2. ������GUЭ��ջ��������Ҫ��C��ȥ������Ϣ������Ϣ
                       (senderpid������A�˵�PID������������Ϣ��ʧ��)
                    3. ����Ҫ�ظ���GTRͨ�������Ϣ�Ĺ��������жϳɹ�ʧ��
                    4. GU��RTT���Բ��������汾��RTT�汾(�汾��һ)

 History         :
    1.c00326366      2015-9-6  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_GuGtrProcEntry(VOS_UINT8* pstReq)
{
    VOS_UINT32 ulRet                    = ERR_MSP_SUCCESS;
    DIAG_FRAME_INFO_STRU *pstDiagHead   = NULL;

    VOS_UINT32 ulLen;
    DIAG_MSG_A_TRANS_C_STRU *pstInfo;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    DIAG_MSG_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ulRet);
    return ulRet;

DIAG_ERROR:
    /* ����Ҫ�ظ�ʧ�� */
    return ERR_MSP_FAILURE;
}


/*****************************************************************************
 Function Name   : diag_GtrProcEntry
 Description     : GTR�����ӿ����
                    �˹���ֻ�ڻ�ƬǰRTT����ʱʹ�ã��ᵥ������RTT�����汾
                    ��PS�Ĵ�׮�ӿ�ע�ᵽMSP��MSP�ڴӹ��߲���յ�GTR����ʱ�ص�PS
                    �Ĵ�׮�ӿڣ�PSͨ���������Ϣת����DSP
                    PS���յ�DSP�Ļظ��󣬵���(DIAG_TransReport)�ӿڰ�Ӧ������
                    �������߲�
                    GTR�������-->HIDS-->MSP-->PS-->DSP-->PS-->MSP-->HIDS-->GTR

 History         :
    1.w00182550      2012-12-26  Draft Enact
    2.c64416         2014-11-18  �����µ���ϼܹ�

*****************************************************************************/
VOS_UINT32 diag_GtrProcEntry(VOS_UINT8* pstReq)
{
    DIAG_CMD_GTR_SET_CNF_STRU stGtrCnf = {0};
    VOS_UINT32 ret = ERR_MSP_SUCCESS;
    MSP_DIAG_CNF_INFO_STRU stDiagInfo = {0};
    DIAG_FRAME_INFO_STRU *pstDiagHead = NULL;

    VOS_UINT32 ulLen;
    DIAG_MSG_A_TRANS_C_STRU *pstInfo;

    pstDiagHead = (DIAG_FRAME_INFO_STRU*)(pstReq);

    DIAG_MSG_ACORE_CFG_PROC(ulLen, pstDiagHead, pstInfo, ret);
    return ret;

DIAG_ERROR:

    DIAG_MSG_COMMON_PROC(stDiagInfo, stGtrCnf, pstDiagHead);

    stDiagInfo.ulMsgType    = DIAG_MSG_TYPE_MSP;

    stGtrCnf.ulRc = ERR_HIDS_CORE_ERROR;

    ret = DIAG_MsgReport(&stDiagInfo, &stGtrCnf, sizeof(stGtrCnf));

    return ret;
}


/*****************************************************************************
 Function Name   : diag_MspMsgProc
 Description     : MSP����������
 Input           : pData    ����������������
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c64416      2014-11-18  Draft Enact

*****************************************************************************/
VOS_UINT32 diag_MspMsgProc(DIAG_FRAME_INFO_STRU *pData)
{
    VOS_UINT32 ret = ERR_MSP_FAILURE;
    VOS_UINT32 i;

    if(NULL == pData)
    {
        return ret;
    }

    diag_PTR(EN_DIAG_PTR_MSGMSP_IN);

    if(DIAG_MSG_TYPE_MSP != pData->stID.pri4b)
    {
        return ret;
    }

    for(i = 0; i < sizeof(g_astMsgMsp)/sizeof(DIAG_MSGMSP_PROC_STRU); i++)
    {
        if(pData->ulCmdId == g_astMsgMsp[i].ulCmdId)
        {
            return g_astMsgMsp[i].pfnProc((VOS_UINT8*)pData);
        }
    }

    (VOS_VOID)diag_FailedCmdCnf(pData, ERR_MSP_DIAG_INVALID_CMD);

    return ERR_MSP_SUCCESS;
}




