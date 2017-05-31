

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: v_msg.c                                                         */
/*                                                                           */
/* Author: Yang Xiangqian                                                    */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2006-10                                                             */
/*                                                                           */
/* Description: implement message function                                   */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/* 2. Date: 2006-10                                                          */
/*    Author: Xu Cheng                                                       */
/*    Modification: Standardize code                                         */
/*                                                                           */
/*****************************************************************************/


#include "v_msg.h"
#include "v_blkMem.h"
#include "v_queue.h"
#include "vos_Id.h"
#include "v_timer.h"
#include "v_iddef.h"
#include "mdrv.h"

 /* LINUX ��֧�� */



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 modify:x51137; review:h59254; cause:print log */
#define    THIS_FILE_ID        PS_FILE_ID_V_MSG_C
/*lint +e767 modify:x51137; review:h59254; */


extern VOS_MSG_HOOK_FUNC                vos_MsgHook;

#define MSG_SEND_SIZE    ( sizeof(VOS_UINT_PTR) )


typedef struct
{
    VOS_UINT32 ulQid;
    VOS_UINT32 ulSendPid;
    VOS_UINT32 ulRcvPid;
    VOS_UINT32 ulMsgName;
}VOS_DUMP_MSG_STRU;

/* dump msg info */
#define     DUMP_MSG_INFO_LEN      1024
VOS_CHAR    g_aucDumpMsgInfo[DUMP_MSG_INFO_LEN];

typedef struct
{
    VOS_UINT32 ulSendNum;
    VOS_UINT32 ulSendSlice;
    VOS_UINT32 ulRcvNum;
    VOS_UINT32 ulRcvSlice;
}VOS_ICC_DEBUG_INFO_STRU;




VOS_SENDMSG_FUNCLIST_ST g_astVOSSendMsgProcTable[VOS_SUPPORT_CPU_NUM_MAX]={
                            {VOS_CPU_ID_0_PID_BUTT, 0, V_SendMsgByICC,     V_SendMsgByICC},        /*Send Msg to Other ARM*/
                            {VOS_CPU_ID_1_PID_BUTT, 0, V_SendLocalMsg,     V_SendLocalUrgentMsg},  /*Send Local Msg*/
                            {VOS_CPU_ID_2_PID_BUTT, 0, VOS_NULL_PTR,       VOS_NULL_PTR},          /*Send Msg to ZSP, RSV*/
                            {VOS_CPU_ID_3_PID_BUTT, 0, VOS_SendHIFIMsg,    VOS_SendHIFIUrgentMsg}, /*Send Msg to HIFI*/
                            {VOS_CPU_ID_4_PID_BUTT, 0, VOS_NULL_PTR,       VOS_NULL_PTR}};         /*Send Msg to MCU*/



enum
{
    VOS_HIFI_TO_ACPU_VOS_MSG_NORMAL,
    VOS_MCU_TO_ACPU_VOS_MSG_NORMAL,
    VOS_HIFI_TO_CCPU_VOS_MSG_NORMAL,
    VOS_MAIL_BOX_MSG_NORMAL_BUTT,
    VOS_HIFI_TO_ACPU_VOS_MSG_URGENT,
    VOS_MCU_TO_ACPU_VOS_MSG_URGENT,
    VOS_HIFI_TO_CCPU_VOS_MSG_URGENT
};

/* DSP���ƺ��ṩǿ�ƻ��ѹ��� */
Msg_Fun_Type    g_pfnVosAwakeFunHook[MODEM_ID_BUTT] = {VOS_NULL_PTR};

VOS_UINT32 g_msglpm = VOS_FALSE;

VOS_INT VOS_MsgLpmCb(VOS_INT x)
{
    g_msglpm = VOS_TRUE;

    return 0;
}

VOS_ICC_DEBUG_INFO_STRU g_stVosAcoreCcoreIccDebugInfo;
VOS_ICC_DEBUG_INFO_STRU g_stVosCcoreHifiIccDebugInfo;

/*****************************************************************************
 Function   : VOS_IccDebugInfoInit
 Description: the debug info init of Icc
 Input      : NA
 Return     : NA
 Other      :
 *****************************************************************************/
VOS_VOID VOS_IccDebugInfoInit(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemSet_s(&g_stVosAcoreCcoreIccDebugInfo, sizeof(VOS_ICC_DEBUG_INFO_STRU), 0, sizeof(VOS_ICC_DEBUG_INFO_STRU));

    VOS_MemSet_s(&g_stVosCcoreHifiIccDebugInfo, sizeof(VOS_ICC_DEBUG_INFO_STRU), 0, sizeof(VOS_ICC_DEBUG_INFO_STRU));
    /*lint +e534*/

    return;
}

/*****************************************************************************
 Function   : VOS_RegisterAwakeFun
 Description: register awake fun to OSA
 Input      : hook fun
 Return     : ok or error
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_RegisterAwakeFun(MODEM_ID_ENUM_UINT16 enModem, Msg_Fun_Type pfnHook)
{

    return VOS_ERR;


    g_pfnVosAwakeFunHook[enModem]   = pfnHook;

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_ExecuteAwakeFun
 Description: Call Awake fun
 Input      : msg
 Return     : none
 Other      :
 *****************************************************************************/
VOS_VOID VOS_ExecuteAwakeFun(MsgBlock *pstMsgCtrlBlk)
{
    MODEM_ID_ENUM_UINT16                enModem = MODEM_ID_BUTT;

    return;



    enModem = VOS_GetModemIDFromPid(pstMsgCtrlBlk->ulReceiverPid);

    if (enModem >= MODEM_ID_BUTT)
    {
        return;
    }

    if ( VOS_NULL_PTR == g_pfnVosAwakeFunHook[enModem] )
    {
        return;
    }

    (g_pfnVosAwakeFunHook[enModem])(pstMsgCtrlBlk);

    return;
}

/*****************************************************************************
 Function   : VOS_DRVMB_OSAMsg_CB
 Description: DRV MB dallback func, read Msg data from MB, and then send it to receiver.
 Input      : ulChannelId  -- Mile box channel id
              pucbuffer -- the pointer of message
              ulLen     -- Msg data length
 Return     : NA
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_VOID VOS_DRVMB_OSAMsg_CB(VOS_VOID *pUserPara, VOS_VOID *pMailHandle, VOS_UINT32 ulLen)
{
    VOS_UINT8                          *pucMsgData;
    MsgBlock                           *pstMsgCtrlBlk;
    VOS_UINT32                         ulMailboxLen = ulLen;
    VOS_UINT32                         ulMailCode;
    VOS_UINT_PTR                       TempValue;

    TempValue = (VOS_UINT_PTR)pUserPara;

    if (ulLen <= VOS_MSG_HEAD_LENGTH)
    {
        /*lint -e534*/
        LogPrint("\n VOS_DRVMB_OSAMsg_CB: The Data Len is small.\n");

        VOS_SetErrorNo(VOS_ERRNO_MSG_MB_DATALENISNULL);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_MB_DATALENISNULL, (VOS_INT)ulLen, (VOS_INT)TempValue,
                             VOS_NULL_PTR, 0);

        return ;
    }

    /* Alloc message space with static PID number */
    pucMsgData = (VOS_UINT8*)VOS_AllocMsg( VOS_PID_DOPRAEND, (VOS_UINT32)(ulLen-VOS_MSG_HEAD_LENGTH) );

    if ( VOS_NULL_PTR == pucMsgData )
    {
        /*lint -e534*/
        LogPrint("\n VOS_DRVMB_OSAMsg_CB: Alloc Msg memory failed.\n");
        /*lint +e534*/

        return ;
    }

    if (MAILBOX_OK !=  DRV_MAILBOX_READMAILDATA(pMailHandle, pucMsgData, &ulMailboxLen))
    {
        /*lint -e534*/
        VOS_FreeMsg(VOS_PID_DOPRAEND, pucMsgData);

        LogPrint("\n VOS_DRVMB_OSAMsg_CB: DRV_MAILBOX_READMAILDATA failed.\n");

        VOS_SetErrorNo(VOS_ERRNO_MSG_DRV_READ_MAIL_FAIL);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_DRV_READ_MAIL_FAIL, (VOS_INT)ulLen, (VOS_INT)TempValue,
                             VOS_NULL_PTR, 0);
        return ;
    }

    /* get the Message ctrl data from the MB channel */
    pstMsgCtrlBlk = (MsgBlock*)(pucMsgData);

    VOS_ModifyMsgInfo((VOS_VOID *)pstMsgCtrlBlk, pstMsgCtrlBlk->ulSenderPid);

    ulMailCode = (VOS_UINT32)TempValue;

    if ( VOS_MAIL_BOX_MSG_NORMAL_BUTT < ulMailCode )/*urgend msg*/
    {
        (VOS_VOID)V_SendUrgentMsg(VOS_PID_DOPRAEND, (VOS_VOID**)(&(pucMsgData)), VOS_FILE_ID, (VOS_INT32)(VOS_MSG_HEAD_FLAG + ulMailCode) );
    }
    else
    {
        (VOS_VOID)V_SendMsg(VOS_PID_DOPRAEND, (VOS_VOID**)(&(pucMsgData)), VOS_FILE_ID, (VOS_INT32)(VOS_MSG_HEAD_FLAG + ulMailCode) );
    }

    return ;
}

/*****************************************************************************
 Function   : VOS_DRVMB_Init
 Description: Init the DRV's mailebox channle.
 Input      : void
 Return     : VOS_OK / VOS_ERR
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 VOS_DRVMB_Init(VOS_VOID)
{
    /* Register HIFI->ACPU OSA normal Msg CallBack */
    if (VOS_OK != DRV_MAILBOX_REGISTERRECVFUNC(MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_NORMAL,
                                VOS_DRVMB_OSAMsg_CB,
                                (VOS_VOID *)VOS_HIFI_TO_ACPU_VOS_MSG_NORMAL))
    {
        /*lint -e534*/
        LogPrint("\n VOS_DRVMB_Init: Register HIFI->ACPU Normal CB failed.\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /* Register HIFI->ACPU OSA urgent Msg CallBack */
    if (VOS_OK != DRV_MAILBOX_REGISTERRECVFUNC(MAILBOX_MAILCODE_HIFI_TO_ACPU_VOS_MSG_URGENT,
                                VOS_DRVMB_OSAMsg_CB,
                                (VOS_VOID *)VOS_HIFI_TO_ACPU_VOS_MSG_URGENT))
    {
        /*lint -e534*/
        LogPrint("\n VOS_DRVMB_Init: Register HIFI->ACPU Urgent CB failed.\n");
        /*lint +e534*/
        return VOS_ERR;
    }


    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_SendMsgByDrvMB
 Description: Send the msg to another ARM's OSA by the DRV's mailebox channle.
 Input      : Pid        -- process identifier
              pMsg       -- the pointer of message
              pstMsgPara -- the Msg parameter
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 VOS_SendMsgByDrvMB(VOS_PID                 Pid,
                              VOS_VOID                **ppMsg,
                              VOS_DRVMB_MSG_PARA_STRU *pstMsgPara)
{
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;
    MsgBlock                           *pstMsgCtrlBlk;

    pstMsgCtrlBlk = (MsgBlock*)(*ppMsg);

    if ( DOPRA_PID_TIMER == pstMsgCtrlBlk->ulSenderPid )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_MB_PIDTERROR);

        LogPrint1("\n# VOS_SendMsgByDrvMB Error Timer Sender MB Msg, Rec PID %d\n", (VOS_INT)pstMsgCtrlBlk->ulReceiverPid);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_MB_PIDTERROR, (VOS_INT)pstMsgPara->ulFileID, pstMsgPara->lLineNo,
                             (VOS_CHAR*)pstMsgPara, sizeof(VOS_DRVMB_MSG_PARA_STRU));

        return(VOS_ERRNO_MSG_MB_PIDTERROR);
    }

    /* Get the Msg Length */
    ulDataLen   = pstMsgCtrlBlk->ulLength + VOS_MSG_HEAD_LENGTH;

    ulResult     = DRV_MAILBOX_SENDMAIL(pstMsgPara->ulMailBoxCode,
                                        *ppMsg,
                                        ulDataLen );

    /*lint -e534*/
    VOS_FreeMsg(Pid, *ppMsg ); /* need free the Msg memory */
    /*lint +e534*/

    /* ����HIFI��λ��д mailboxͨ��ʧ�ܻ᷵��һ������ֵ�����ܸ�λ���� */
    if (MAILBOX_TARGET_NOT_READY == ulResult )
    {
        /*lint -e534*/
        LogPrint3("\n# VOS_SendMsgByDrvMB Error,HIFI Reset, File  %d. line %d. Size %d.\n",
                    (VOS_INT)pstMsgPara->ulFileID, pstMsgPara->lLineNo,(VOS_INT)ulDataLen);
        /*lint +e534*/

        return VOS_ERRNO_MSG_MAILBOX_RESET;
    }

    if ( MAILBOX_OK != ulResult ) /* Send Data to mail box channle error */
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_MB_SENDERROR);

        LogPrint4("\n# VOS_SendMsgByDrvMB Error,Write DRV MB Error, File  %d. line %d. Size %d result %d.\n",
                    (VOS_INT)pstMsgPara->ulFileID, pstMsgPara->lLineNo,(VOS_INT)ulDataLen,(VOS_INT)ulResult);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_MB_SENDERROR, (VOS_INT)ulResult, 0,
                             (VOS_CHAR*)pstMsgPara, sizeof(VOS_DRVMB_MSG_PARA_STRU));

        return(VOS_ERRNO_MSG_MB_SENDERROR);
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_SendHIFIMsg
 Description: Send the msg to HIFI's OSA by the DRV's mailebox channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/

VOS_UINT32 VOS_SendHIFIMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                           VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_DRVMB_MSG_PARA_STRU             stMsgPara;

    stMsgPara.lLineNo       = lLineNo;
    stMsgPara.ulFileID      = ulFileID;

    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_NORMAL;


    return VOS_SendMsgByDrvMB(Pid, ppMsg, &stMsgPara);
}

/*****************************************************************************
 Function   : VOS_SendHIFIUrgentMsg
 Description: Send the urgent msg to HIFI's OSA by the DRV's mailebox channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/

VOS_UINT32 VOS_SendHIFIUrgentMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                                 VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_DRVMB_MSG_PARA_STRU             stMsgPara;

    stMsgPara.lLineNo       = lLineNo;
    stMsgPara.ulFileID      = ulFileID;

    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_ACPU_TO_HIFI_VOS_MSG_URGENT;


    return VOS_SendMsgByDrvMB(Pid, ppMsg, &stMsgPara);
}


/*****************************************************************************
 Function   : VOS_SendMCUMsg
 Description: Send the msg to MCU's OSA by the DRV's mailebox channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 VOS_SendMCUMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                           VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_DRVMB_MSG_PARA_STRU             stMsgPara;

    stMsgPara.lLineNo       = lLineNo;
    stMsgPara.ulFileID      = ulFileID;

    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_NORMAL;


    return VOS_SendMsgByDrvMB(Pid, ppMsg, &stMsgPara);
}

/*****************************************************************************
 Function   : VOS_SendMCUUrgentMsg
 Description: Send the urgent msg to MCU's OSA by the DRV's mailebox channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/

VOS_UINT32 VOS_SendMCUUrgentMsg( VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    VOS_DRVMB_MSG_PARA_STRU             stMsgPara;

    stMsgPara.lLineNo       = lLineNo;
    stMsgPara.ulFileID      = ulFileID;

    stMsgPara.ulMailBoxCode = MAILBOX_MAILCODE_ACPU_TO_MCU_VOS_MSG_URGENT;


    return VOS_SendMsgByDrvMB(Pid, ppMsg, &stMsgPara);
}

/*****************************************************************************
 Function   : V_AllocMsg
 Description: allocates messages block
 Input      : Pid      -- process identifier
              ulLength -- the length of message
 Return     : The pointer of message on success or VOS_NULL_PTR on failure
 Other      : The pointer of message that returned for application is not the
              actual pointer of message which system used
 *****************************************************************************/
MsgBlock * V_AllocMsg(VOS_PID Pid, VOS_UINT32 ulLength,
                       VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_INT         ulTotalLength;
    MSG_BLOCK_HEAD  *pMsgBlkHead;
    MsgBlock        *MsgBlock_Ptr;

    if(Pid >= VOS_PID_BUTT)
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }

    if( 0 == ulLength )
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }

    ulTotalLength =
        (VOS_INT)(VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH + ulLength);

    pMsgBlkHead = (MSG_BLOCK_HEAD*)VOS_MemBlkMalloc(Pid, ulTotalLength,
        ulFileID, usLineNo);
    if( VOS_NULL_PTR == pMsgBlkHead )
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }

    pMsgBlkHead->ulFlag = VOS_MSG_HEAD_FLAG;

    MsgBlock_Ptr = (MsgBlock*)( (VOS_UINT_PTR)pMsgBlkHead
                        + VOS_MSG_BLK_HEAD_LEN );
    MsgBlock_Ptr->ulSenderCpuId = VOS_LOCAL_CPUID;
    MsgBlock_Ptr->ulSenderPid   = Pid;
    MsgBlock_Ptr->ulReceiverCpuId = VOS_LOCAL_CPUID;
    MsgBlock_Ptr->ulLength = (VOS_UINT32)ulLength;


    return MsgBlock_Ptr;
}

/*****************************************************************************
 Function   : VOS_AllocTimerMsg
 Description: allocates timer messages block
 Input      : Pid      -- process identifier
              ulLength -- the length of message
 Return     : The pointer of message on success or VOS_NULL_PTR on failure
 Other      :
 *****************************************************************************/
MsgBlock * VOS_AllocTimerMsg(VOS_PID Pid, VOS_UINT32 ulLength )
{
    VOS_UINT32      ulTotalLength;
    MSG_BLOCK_HEAD  *pMsgBlkHead;
    MsgBlock        *MsgBlock_Ptr;


    if(Pid >= VOS_PID_BUTT)
    {
        /*lint -e534*/
        LogPrint("# Alloc Timer msg Pid too big.\r\n");
        /*lint +e534*/
        return((MsgBlock*)VOS_NULL_PTR);
    }

    if(0 == ulLength)
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }

    ulTotalLength = VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH + ulLength;

    pMsgBlkHead = (MSG_BLOCK_HEAD*)VOS_TIMER_MemCtrlBlkMalloc( Pid,
        (VOS_INT)ulTotalLength );
    if( VOS_NULL_PTR == pMsgBlkHead )
    {
        return((MsgBlock*)VOS_NULL_PTR);
    }

    pMsgBlkHead->ulFlag     = VOS_MSG_HEAD_FLAG;

    MsgBlock_Ptr = (MsgBlock*)( (VOS_UINT_PTR)pMsgBlkHead
                        + VOS_MSG_BLK_HEAD_LEN );

    MsgBlock_Ptr->ulSenderCpuId   = VOS_LOCAL_CPUID;
    MsgBlock_Ptr->ulSenderPid     = DOPRA_PID_TIMER;
    MsgBlock_Ptr->ulReceiverCpuId = VOS_LOCAL_CPUID;
    MsgBlock_Ptr->ulReceiverPid   = Pid;
    MsgBlock_Ptr->ulLength        = ulLength;

    return MsgBlock_Ptr;
}

/*****************************************************************************
 Function   : V_FreeMsg
 Description: Free a message which status must be ALLOCATED
 Input      : Pid  -- PID who free the message
              pMsg -- Pointer of the message to be freed
 Return     : VOS_OK on success or error number on failure
 Other      : This function was only called to free a message which was
              allocated by VOS_AllocMsg but not been send.
 *****************************************************************************/
VOS_UINT32 V_FreeMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_VOID            *pMsgBlkHead;
    MSG_BLOCK_HEAD      *pstMSG;
    VOS_UINT_PTR         ulBlockAdd;
    VOS_UINT_PTR         ulCtrlkAdd;

    if(Pid >= VOS_PID_BUTT)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTMSGISNULL);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_FREE_INPUTMSGISNULL);
    }

    if( VOS_NULL_PTR == ppMsg )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    if( VOS_NULL_PTR == *ppMsg )
    {
        /*lint -e534*/
        LogPrint3("# V_FreeMsg,free msg again.F %d L %d T %d.\r\n",
            (VOS_INT)ulFileID, usLineNo, (VOS_INT)VOS_GetTick() );

        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    pMsgBlkHead = (VOS_VOID*)( (VOS_UINT_PTR)(*ppMsg)
                         - VOS_MSG_BLK_HEAD_LEN );

    if ( VOS_OK != VOS_MemCheck( pMsgBlkHead, &ulBlockAdd, &ulCtrlkAdd,
        ulFileID, usLineNo ) )
    {
        return VOS_ERR;
    }

    pstMSG = (MSG_BLOCK_HEAD *)pMsgBlkHead;
    if ( VOS_MSG_RESERVED_HEAD_FLAG == pstMSG->ulFlag )
    {
        return VOS_OK;
    }
    else
    {
        /* Clear user's pointer */
        *ppMsg = VOS_NULL_PTR;


        return VOS_MemCtrlBlkFree( (VOS_MEM_CTRL_BLOCK *)ulCtrlkAdd,
            (VOS_MEM_HEAD_BLOCK *)ulBlockAdd, ulFileID, usLineNo );
    }
}

/*****************************************************************************
 Function   : V_ReserveMsg
 Description: In msg proceed function, reserve a message
 Input      : pMsg     -- the pointer of application message (MsgBlock)
              Pid
 Return     : VOS_OK -- success
              ErrorCode -- fail
 *****************************************************************************/
VOS_UINT32 V_ReserveMsg(VOS_PID Pid, MsgBlock * pMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    MSG_BLOCK_HEAD      *MSG_BLOCK_Ptr;
    VOS_UINT_PTR         ulBlockAdd;
    VOS_UINT_PTR         ulCtrlkAdd;

    if(Pid >= VOS_PID_BUTT)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_RESERVE_INVALIDMSG);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_RESERVE_INVALIDMSG);
    }

    if(pMsg == VOS_NULL_PTR)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    MSG_BLOCK_Ptr = (MSG_BLOCK_HEAD*)( (VOS_UINT_PTR)pMsg
                         - VOS_MSG_BLK_HEAD_LEN );

    if ( VOS_OK != VOS_MemCheck( (VOS_VOID *)MSG_BLOCK_Ptr, &ulBlockAdd,
        &ulCtrlkAdd, ulFileID, usLineNo ) )
    {
        return VOS_ERR;
    }

    if ( VOS_MSG_HEAD_FLAG == MSG_BLOCK_Ptr->ulFlag )
    {
        MSG_BLOCK_Ptr->ulFlag = VOS_MSG_RESERVED_HEAD_FLAG;
        return VOS_OK;
    }
    else
    {
        return VOS_ERR;
    }
}

/*****************************************************************************
 Function   : V_UnreserveMsg
 Description: In msg proceed function, unreserve a message
 Input      : pMsg     -- the pointer of application message (MsgBlock)
              Pid
 Return     : VOS_OK -- success
              ErrorCode -- fail
 *****************************************************************************/
VOS_UINT32 V_UnreserveMsg( VOS_PID Pid, MsgBlock * pMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    MSG_BLOCK_HEAD      *MSG_BLOCK_Ptr;
    VOS_UINT_PTR         ulBlockAdd;
    VOS_UINT_PTR         ulCtrlkAdd;

    if(Pid >= VOS_PID_BUTT)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_RESERVE_INVALIDMSG);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_RESERVE_INVALIDMSG);
    }

    if(pMsg == VOS_NULL_PTR)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    MSG_BLOCK_Ptr = (MSG_BLOCK_HEAD*)( (VOS_UINT_PTR)pMsg
                         - VOS_MSG_BLK_HEAD_LEN );

    if ( VOS_OK != VOS_MemCheck( (VOS_VOID *)MSG_BLOCK_Ptr, &ulBlockAdd,
        &ulCtrlkAdd, ulFileID, usLineNo ) )
    {
        return VOS_ERR;
    }

    MSG_BLOCK_Ptr->ulFlag = VOS_MSG_HEAD_FLAG;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : VOS_CheckMsgCPUId
 ��������  : ��鷢�͵���Ϣ�Ƿ�Ϊ�˼���Ϣ
 �������  : VOS_UINT32 ulCPUId
 �������  : ��
 �� �� ֵ  : VOS_BOOL   VOS_TRUE    ���͵���ϢΪ�˼���Ϣ
                        VOS_FALSE   ���͵���ϢΪ������Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��13��
    ��    ��   : s00207770
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_BOOL VOS_CheckMsgCPUId( VOS_UINT32 ulCPUId )
{
    /* ACPU��idΪ1�������Ϣ���յ�cpuid��Ϊacpu id����Ϊ�����Ϣ */
    if (OSA_CPU_ACPU != ulCPUId)
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : VOS_CheckInterrupt
 ��������  : ����Ƿ�Ϊ�ж�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32   ��0        �������ж���������
                          VOS_FALSE  ������������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��13��
    ��    ��   : s00207770
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 VOS_CheckInterrupt( VOS_VOID )
{

    return (VOS_UINT32)in_interrupt();

    /*lint -e527 */
    return VOS_FALSE;
    /*lint -e527 */
}

/*****************************************************************************
 Function   : V_FreeReservedMsg
 Description: Free a reserved message.
 Input      : pMsg -- Point of the message to free
              Pid
 Return     : VOS_OK on success and error code on failure
 *****************************************************************************/
VOS_UINT32 V_FreeReservedMsg(VOS_PID Pid, VOS_VOID ** ppMsg,
                                    VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_VOID            *pMsgBlkHead;
    MSG_BLOCK_HEAD      *pstMSG;
    VOS_UINT_PTR         ulBlockAdd;
    VOS_UINT_PTR         ulCtrlkAdd;

    if(Pid >= VOS_PID_BUTT)
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTMSGISNULL);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_FREE_INPUTMSGISNULL);
    }

    if( VOS_NULL_PTR == ppMsg )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    if( VOS_NULL_PTR == *ppMsg )
    {
        /*lint -e534*/
        LogPrint3("# V_FreeReservedMsg,free reserved msg again.F %d L %d T %d.\r\n",
            (VOS_INT)ulFileID, usLineNo, (VOS_INT)VOS_GetTick() );

        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        /*lint +e534*/
        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    pMsgBlkHead = (VOS_VOID*)( (VOS_UINT_PTR)(*ppMsg)
                         - VOS_MSG_BLK_HEAD_LEN );

    if ( VOS_OK != VOS_MemCheck( pMsgBlkHead, &ulBlockAdd, &ulCtrlkAdd,
        ulFileID, usLineNo ) )
    {
        return VOS_ERR;
    }

    pstMSG = (MSG_BLOCK_HEAD *)pMsgBlkHead;
    if ( VOS_MSG_RESERVED_HEAD_FLAG == pstMSG->ulFlag )
    {
        /* Clear user's pointer */
        *ppMsg = VOS_NULL_PTR;


        return VOS_MemCtrlBlkFree( (VOS_MEM_CTRL_BLOCK *)ulCtrlkAdd,
            (VOS_MEM_HEAD_BLOCK *)ulBlockAdd, ulFileID, usLineNo );
    }
    else
    {
        return VOS_ERRNO_MSG_FREERES_STATUSERROR;
    }
}

/*****************************************************************************
 Function   : VOS_CheckRcvPid
 Description: Check if the receiver pid is correct.
 Input      : ulReceiverPid  -- receiver pid
 Return     : VOS_OK on success and error code on failure
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_CheckRcvPid(VOS_UINT32 ulReceiverPid)
{
    VOS_UINT32                          ulCpuID;

    ulCpuID = VOS_GET_CPU_ID(ulReceiverPid);

    if ( ulCpuID >= VOS_SUPPORT_CPU_NUM_MAX )    /*The CPU ID is too large*/
    {
        return(VOS_ERRNO_MSG_ICC_CPUIDISBIG);
    }

    if ( ulReceiverPid >= g_astVOSSendMsgProcTable[ulCpuID].ulEndPID )  /*The Receive PID is too large*/
    {
        return(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : V_CheckMsgPara
 Description: Check the msg parameter.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      :
 *****************************************************************************/
VOS_UINT32 V_CheckMsgPara(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    VOS_UINT32          ulPid;
    VOS_UINT32          ulCpuID;
    MsgBlock           *pMsgCtrlBlk;

    if ( VOS_NULL_PTR == ppMsg )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        /*lint +e534*/

        VOS_ProtectionReboot(OSA_SEND_MSG_NULL,(VOS_INT)ulFileID,lLineNo,
                             VOS_NULL_PTR,0);

        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    if ( VOS_NULL_PTR == *ppMsg )
    {
        /*lint -e534*/
        LogPrint2("# V_SendMsg,send msg again.F %d L %d.\r\n",
                    (VOS_INT)ulFileID, lLineNo);

        VOS_SetErrorNo(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
        /*lint +e534*/

        VOS_ProtectionReboot(OSA_SEND_MSG_PP_NULL,(VOS_INT)ulFileID,lLineNo,
                             VOS_NULL_PTR,0);

        return(VOS_ERRNO_MSG_FREE_INPUTPIDINVALID);
    }

    pMsgCtrlBlk     = (MsgBlock*)(*ppMsg);
    ulPid           = pMsgCtrlBlk->ulReceiverPid;
    ulCpuID         = VOS_GET_CPU_ID(ulPid);

    if ( ulCpuID >= VOS_SUPPORT_CPU_NUM_MAX )    /*The CPU ID is too large*/
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_CPUIDISBIG);

        LogPrint1("# V_SendMsg Error,invalid CPU id, PID is %d.\n", (VOS_INT)ulPid);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_ICC_CPUIDISBIG,(VOS_INT)ulFileID,lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        /*lint -e534*/
        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return(VOS_ERRNO_MSG_ICC_CPUIDISBIG);
    }

    if ( ulPid >= g_astVOSSendMsgProcTable[ulCpuID].ulEndPID )  /*The Receive PID is too large*/
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);

        LogPrint1("# V_SendMsg Error,invalid PID %d.\n", (VOS_INT)ulPid);
        /*lint +e534*/

        VOS_ProtectionReboot(OSA_SEND_MSG_PID_BIG,(VOS_INT)ulFileID,lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        /*lint -e534*/
        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);
    }

    return VOS_OK;
}
/*****************************************************************************
 Function   : V_SendLocalMsg
 Description: Send the msg to a task, which is in this CPU.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 V_SendLocalMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo )

{
    MsgBlock           *pMsgCtrlBlk;
    VOS_UINT32          ulPid;
    VOS_UINT32          ulFid;
    VOS_UINT32          ulQid;
    VOS_VOID            *pActualMsg;
    VOS_UINT_PTR        ulBlockAdd;
    VOS_UINT_PTR        ulCtrlkAdd;
    VOS_DUMP_MSG_STRU   *pstDumpMsgInfo;
    VOS_UINT32          ulTaskTcb;

    pMsgCtrlBlk      = (MsgBlock*)(*ppMsg);
    ulPid            = pMsgCtrlBlk->ulReceiverPid;

    if ( ulPid < VOS_PID_DOPRAEND )
    {
        /*lint -e534*/
        LogPrint1("# VOS_SendLocalMsg Rec PID %d Check error.\n", (VOS_INT)ulPid);

        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_PIDTOOSMALL);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_ICC_PIDTOOSMALL, (VOS_INT)ulFileID, lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        /*lint -e534*/
        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return VOS_ERR;
    }

    if ( ulPid >= VOS_PID_BUTT )  /*The Receive PID is too large*/
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);

        LogPrint1("# VOS_SendLocalMsgError,invalid PID %d.\n", (VOS_INT)ulPid);
        /*lint +e534*/

        VOS_ProtectionReboot(OSA_SEND_MSG_PID_BIG,(VOS_INT)ulFileID,lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        /*lint -e534*/
        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return VOS_ERR;
    }

    ulFid = (VOS_UINT32)(vos_PidRecords[ulPid-VOS_PID_DOPRAEND].Fid);

    if ( (ulFid < (VOS_UINT32)VOS_FID_DOPRAEND) || (ulFid >= (VOS_UINT32)VOS_FID_BUTT) )
    {
        /*lint -e534*/
        LogPrint1("# *******VOS_SendLocalMsg Rec PID %d.\n", (VOS_INT)ulPid);

        VOS_SetErrorNo(VOS_ERRNO_MSG_PID_NO_FID);
        /*lint +e534*/

        /*VOS_ProtectionReboot(VOS_ERRNO_MSG_PID_NO_FID, (VOS_INT)ulFileID, lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);*/

        /*lint -e534*/
        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return VOS_ERR;
    }

    ulQid = vos_FidCtrlBlk[ulFid].Qid;

    pActualMsg = (VOS_VOID *)((VOS_UINT_PTR)(*ppMsg) - VOS_MSG_BLK_HEAD_LEN);

    if ( VOS_OK != VOS_MemCheck( pActualMsg, &ulBlockAdd, &ulCtrlkAdd,
                                ulFileID, lLineNo ) )
    {
        /*lint -e534*/
        LogPrint("# VOS_SendLocalMsg Mem Check error.\n");
        /*lint +e534*/

        VOS_ProtectionReboot(OSA_SEND_MSG_FAIL_TO_CHECK, (VOS_INT)ulFileID, lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        return VOS_ERR;
    }

    if ( VOS_OK != VOS_FixedQueueWrite( ulQid, pActualMsg, (VOS_UINT32)MSG_SEND_SIZE,
                                        VOS_NORMAL_PRIORITY_MSG, ulPid ) )
    {
        /*lint -e534*/
        LogPrint3("# V_SendMsg Error,queue full,Tx Pid %d Rx Pid %d Name 0x%x.\n",
            (int)(pMsgCtrlBlk->ulSenderPid), (int)ulPid,
            (int)(*(VOS_UINT32 *)(pMsgCtrlBlk->aucValue)) );
        /*lint +e534*/

        pstDumpMsgInfo = (VOS_DUMP_MSG_STRU *)g_aucDumpMsgInfo;

        /*lint -e534*/
        (VOS_VOID)VOS_TaskLock();
        /*lint +e534*/

        pstDumpMsgInfo->ulQid = ulQid;
        pstDumpMsgInfo->ulSendPid = pMsgCtrlBlk->ulSenderPid;
        pstDumpMsgInfo->ulRcvPid = ulPid;
        pstDumpMsgInfo->ulMsgName = *(VOS_UINT32 *)(pMsgCtrlBlk->aucValue);

        pstDumpMsgInfo++;

        VOS_QueuePrintFull(ulQid, (VOS_CHAR *)pstDumpMsgInfo,
            DUMP_MSG_INFO_LEN - sizeof(VOS_DUMP_MSG_STRU) );

        ulTaskTcb = VOS_GetTCBFromTID(vos_FidCtrlBlk[ulFid].Tid);

        VOS_ProtectionReboot(VOS_SAVE_STACK(OSA_SEND_MSG_FAIL_TO_WRITE), (VOS_INT)ulTaskTcb,
                              lLineNo, g_aucDumpMsgInfo, DUMP_MSG_INFO_LEN);

        /*lint -e534*/
        VOS_TaskUnlock();

        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return VOS_ERR;
    }

    if ( VOS_MSG_RESERVED_HEAD_FLAG != ((MSG_BLOCK_HEAD*)pActualMsg)->ulFlag )
    {
        *ppMsg = VOS_NULL_PTR;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_ModifyMsgInfo
 Description: modify the information. alloc msg. who?
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     :
 Other      :
 *****************************************************************************/
VOS_VOID VOS_ModifyMsgInfo(VOS_VOID *pMsg, VOS_PID Pid)
{
    VOS_VOID            *pActualMsg;
    VOS_UINT_PTR         ulBlockAdd;
    VOS_UINT_PTR         ulCtrlkAdd;

    pActualMsg = (VOS_VOID *)((VOS_UINT_PTR)(pMsg) - VOS_MSG_BLK_HEAD_LEN);

    if ( VOS_OK != VOS_MemCheck( pActualMsg, &ulBlockAdd, &ulCtrlkAdd, 0, 0 ) )
    {
        return;
    }

    VOS_ModifyMemBlkInfo(ulBlockAdd, Pid);

    return;
}

/*****************************************************************************
 Function   : V_SendMsgByICC
 Description: Send the msg to another ARM's OSA by the ICC channle.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 V_SendMsgByICC(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    VOS_UINT32              ulDataLen;
    VOS_INT                 lResult;
    MsgBlock                *pMsgCtrlBlk;

    pMsgCtrlBlk = (MsgBlock*)(*ppMsg);

    if ( DOPRA_PID_TIMER == pMsgCtrlBlk->ulSenderPid )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_PIDTERROR);

        LogPrint1("\n# V_SendMsgByICC Error Timer Sender Icc Msg, Rec PID %d\n", (VOS_INT)pMsgCtrlBlk->ulReceiverPid);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_ICC_PIDTERROR, (VOS_INT)ulFileID, lLineNo,
                             (VOS_CHAR*)&lResult, sizeof(lResult));          /*Save the UDI result*/

        return(VOS_ERRNO_MSG_ICC_PIDTERROR);
    }

    ulDataLen   = pMsgCtrlBlk->ulLength + VOS_MSG_HEAD_LENGTH;/*Get the Msg Length*/

    lResult     = DRV_ICC_WRITE(UDI_ICC_GUOM4, *ppMsg, (VOS_INT32)ulDataLen );

    /*lint -e534*/
    VOS_FreeMsg( Pid, *ppMsg ); /*need free the Msg memory*/
    /*lint +e534*/

    /* ����C�˸�λ��дICCͨ��ʧ�ܻ᷵��һ������ֵ�����ܸ�λ���� */
    if (BSP_ERR_ICC_CCORE_RESETTING == lResult )
    {
        /*lint -e534*/
        LogPrint3("\n# V_SendMsgByICC Error,Ccore Reset, File  %d. line %d. Size %d .\n",
                        (VOS_INT)ulFileID, lLineNo,(VOS_INT)ulDataLen);
        /*lint +e534*/

        return VOS_ERRNO_MSG_CCORE_RESET;
    }

    /* дICC��������OSA����������λ */
    if ( ICC_INVALID_NO_FIFO_SPACE == lResult )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_WRITEMSGFULL);

        LogPrint4("\n# V_SendMsgByICC Error,Write ICC Channel Full, File  %d. line %d. Size %d result %d.\n", (VOS_INT)ulFileID, lLineNo,(VOS_INT)ulDataLen,lResult);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_ICC_WRITEMSGFULL, (VOS_INT)ulFileID, lLineNo,
                             (VOS_CHAR*)&lResult, sizeof(lResult));

        return(VOS_ERRNO_MSG_ICC_WRITEMSGFULL);
    }

    if ( ulDataLen != lResult ) /*Write Data to ICC channle Success*/
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_WRITEMSGERROR);

        LogPrint4("\n# V_SendMsgByICC Error,Write ICC Channel Error, File  %d. line %d. Size %d result %d.\n", (VOS_INT)ulFileID, lLineNo,(VOS_INT)ulDataLen,lResult);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_ICC_WRITEMSGERROR, (VOS_INT)ulFileID, lLineNo,
                             (VOS_CHAR*)&lResult, sizeof(lResult));          /*Save the UDI result*/

        return(VOS_ERRNO_MSG_ICC_WRITEMSGERROR);
    }

    g_stVosAcoreCcoreIccDebugInfo.ulSendNum++;
    g_stVosAcoreCcoreIccDebugInfo.ulSendSlice = VOS_GetSlice();

    return VOS_OK;
}




/*****************************************************************************
 Function   : V_SendMsg
 Description: Send the msg to a task, the task may be not in the same CPU.
 Input      : Pid  -- process identifier
              pMsg -- the pointer of message
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/
VOS_UINT32 V_SendMsg(VOS_PID Pid, VOS_VOID **ppMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 lLineNo)
{
    VOS_UINT32          ulResult;
    VOS_UINT32          ulPid;
    VOS_UINT32          ulCpuID;
    MsgBlock           *pMsgCtrlBlk;
    VOS_UINT32          ulSpanMsg;

    ulResult = V_CheckMsgPara( Pid, ppMsg, ulFileID, lLineNo );

    if ( VOS_OK != ulResult)
    {
        return ulResult;
    }

    pMsgCtrlBlk     = (MsgBlock*)(*ppMsg);
    ulPid           = pMsgCtrlBlk->ulReceiverPid;
    ulCpuID         = VOS_GET_CPU_ID(ulPid);

    if (VOS_NULL_PTR == g_astVOSSendMsgProcTable[ulCpuID].pfSendMsg)
    {
        /*lint -e534*/
        LogPrint3("# V_SendMsg, send api is null.F %d L %d RecvPid %d.\r\n",
                    (VOS_INT)ulFileID, lLineNo, (VOS_INT)ulPid);

        VOS_FreeMsg( Pid, *ppMsg );

        VOS_SetErrorNo(VOS_ERRNO_MSG_SEND_FUNCEMPTY);
        /*lint +e534*/

        return(VOS_ERRNO_MSG_SEND_FUNCEMPTY);
    }

    ulSpanMsg = VOS_CheckMsgCPUId(ulCpuID);

    /* �ж��з��Ϳ����Ϣ�����ش��� */
    if ( (VOS_TRUE == ulSpanMsg)
        && (VOS_FALSE != VOS_CheckInterrupt()) )
    {
        /*lint -e534*/
        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return (VOS_ERRNO_MSG_INT_MSGERROR);
    }

    /* �����Ϣ ���Ӻ�����Ϊ�� */
    if ( (VOS_NULL_PTR != vos_MsgHook)
        && (VOS_TRUE == ulSpanMsg))
    {
        /*lint -e534*/
        (vos_MsgHook)(*ppMsg);
        /*lint +e534*/
    }

    return g_astVOSSendMsgProcTable[ulCpuID].pfSendMsg( Pid, ppMsg, ulFileID, lLineNo );
}


/*****************************************************************************
 Function   : OM_ComRx_ICC_OSAMsg_CB
 Description: Receive the msg from the ICC channel, and send it to the Receive PID.
 Input      : ulChannelID   -- The ICC Channel ID
              lLen          -- the Msg data len
 Return     : VOS_OK on success and error code on failure
 Other      : After sending message, the status would be changed to ready.
 *****************************************************************************/

VOS_UINT V_ICC_OSAMsg_CB(VOS_UINT ulChannelID,VOS_INT lLen)
{
    VOS_INT32               lResult;
    VOS_UINT8               *pucMsgData;
    MsgBlock                *pMsgCtrlBlk;
    MsgBlock                stTempDebug;

    g_stVosAcoreCcoreIccDebugInfo.ulRcvNum++;
    g_stVosAcoreCcoreIccDebugInfo.ulRcvSlice = VOS_GetSlice();

    if ( lLen <= VOS_MSG_HEAD_LENGTH )
    {
        /*lint -e534*/
        LogPrint("\nV_ICC_OSAMsg_CB: The Data Len is small.\n");

        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_DATALENISNULL);
        /*lint +e534*/

        lResult = DRV_ICC_READ( UDI_ICC_GUOM4, (VOS_UINT8 *)&stTempDebug, lLen );

        VOS_ProtectionReboot(VOS_ERRNO_MSG_ICC_DATALENISNULL, (VOS_INT)lLen, (VOS_INT)lResult,
                             (VOS_CHAR*)&stTempDebug, sizeof(MsgBlock));

        return VOS_ERR;
    }

    /* Alloc message space with static PID number */
    pucMsgData = (VOS_UINT8*)VOS_AllocMsg( VOS_PID_DOPRAEND, (VOS_UINT32)(lLen-VOS_MSG_HEAD_LENGTH) );

    if ( VOS_NULL_PTR == pucMsgData )
    {
        /*lint -e534*/
        LogPrint("\nV_ICC_OSAMsg_CB: Alloc Msg memory failed.\n");
        /*lint +e534*/

        return VOS_ERR;
    }

    /* get the Message data from the ICC channel */
    lResult = DRV_ICC_READ( UDI_ICC_GUOM4, pucMsgData, lLen );

    if ( lLen != lResult )
    {
        /* Record Debug info */
        /*lint -e534*/
        VOS_MemCpy_s((VOS_CHAR *)&stTempDebug, sizeof(MsgBlock), (VOS_CHAR *)pucMsgData, sizeof(MsgBlock));

        VOS_FreeMsg( VOS_PID_DOPRAEND, pucMsgData );

        LogPrint("\nV_ICC_OSAMsg_CB: DRV_ICC_READ is Failed.\n");

        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_READDATAFAIL);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_ICC_READDATAFAIL, (VOS_INT)lLen, (VOS_INT)lResult,
                             (VOS_CHAR*)&stTempDebug, sizeof(MsgBlock));

        return VOS_ERRNO_MSG_ICC_READDATAFAIL;
    }

    pMsgCtrlBlk = (MsgBlock*)(pucMsgData);

    if(VOS_TRUE == g_msglpm)
    {
        g_msglpm = VOS_FALSE;

        /*lint -e534*/
        vos_printf("[C SR] v_msg senderpid %d, receivepid %d, msgid 0x%x.\n",
            pMsgCtrlBlk->ulSenderPid, pMsgCtrlBlk->ulReceiverPid, *((VOS_UINT32*)(pMsgCtrlBlk->aucValue))); /* [false alarm]: ����Fortify���� */
        /*lint +e534*/
    }

    VOS_ModifyMsgInfo( (VOS_VOID *)pMsgCtrlBlk, pMsgCtrlBlk->ulSenderPid );

    return V_SendMsg(VOS_PID_DOPRAEND, (VOS_VOID**)(&(pucMsgData)), VOS_FILE_ID, __LINE__ );
}

/*****************************************************************************
 Function   : V_SendLocalUrgentMsg
 Description: send urgent message, that in this CPU
 Input      : Pid  -- process identifier to send message
              pMsg -- pointer of the message to be send
 Return     : Rerurn value of Msg_SendMsg
 *****************************************************************************/
VOS_UINT32 V_SendLocalUrgentMsg(VOS_PID Pid, VOS_VOID ** ppMsg,
                                  VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    MsgBlock           *pMsgCtrlBlk;
    VOS_UINT32          ulPid;
    int                 ulFid;
    VOS_UINT32          ulQid;
    VOS_VOID            *pActualMsg;
    VOS_UINT_PTR        ulBlockAdd;
    VOS_UINT_PTR        ulCtrlkAdd;
    VOS_UINT32          ulTaskTcb;
    VOS_DUMP_MSG_STRU   *pstDumpMsgInfo;

    pMsgCtrlBlk      = (MsgBlock*)(*ppMsg);
    ulPid            = pMsgCtrlBlk->ulReceiverPid;

    if ( ulPid < VOS_PID_DOPRAEND )
    {
        /*lint -e534*/
        LogPrint1("# V_SendLocalUrgentMsg Rec PID %d Check error.\n", (VOS_INT)ulPid);

        VOS_SetErrorNo(VOS_ERRNO_MSG_ICC_PIDTOOSMALL);
        /*lint +e534*/

        VOS_ProtectionReboot(VOS_ERRNO_MSG_ICC_PIDTOOSMALL, (VOS_INT)ulFileID, lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        /*lint -e534*/
        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return VOS_ERR;
    }

    if ( ulPid >= VOS_PID_BUTT )  /*The Receive PID is too large*/
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_INPUTPIDINVALID);

        LogPrint1("# V_SendLocalUrgentMsg,invalid PID %d.\n", (VOS_INT)ulPid);
        /*lint +e534*/

        VOS_ProtectionReboot(OSA_SEND_MSG_PID_BIG,(VOS_INT)ulFileID,lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        /*lint -e534*/
        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return VOS_ERR;
    }

    ulFid            = vos_PidRecords[ulPid-VOS_PID_DOPRAEND].Fid;

    /*lint -e574*/
    if ( (ulFid < (VOS_UINT32)VOS_FID_DOPRAEND) || (ulFid >= (VOS_UINT32)VOS_FID_BUTT) )
    {
        /*lint -e534*/
        LogPrint1("# *******V_SendLocalUrgentMsg Rec PID %d.\n", (VOS_INT)ulPid);

        VOS_SetErrorNo(VOS_ERRNO_MSG_PID_NO_FID);
        /*lint +e534*/

        /*VOS_ProtectionReboot(VOS_ERRNO_MSG_PID_NO_FID, (VOS_INT)ulFileID, lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);*/

        /*lint -e534*/
        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return VOS_ERR;
    }
    /*lint +e574*/

    ulQid            = vos_FidCtrlBlk[ulFid].Qid;

    pActualMsg = (VOS_VOID *)((VOS_UINT_PTR)(*ppMsg) - VOS_MSG_BLK_HEAD_LEN);

    if ( VOS_OK != VOS_MemCheck( pActualMsg, &ulBlockAdd, &ulCtrlkAdd,
                                    ulFileID, lLineNo ) )
    {
        /*lint -e534*/
        LogPrint("# V_SendLocalUrgentMsg Error, mem check error.\n");
        /*lint +e534*/

        VOS_ProtectionReboot(OSA_SEND_URG_MSG_FAIL_TO_CHECK, (VOS_INT)ulFileID, lLineNo,
                             (VOS_CHAR*)pMsgCtrlBlk, VOS_MSG_BLOCK_HEAD_AND_RESERVED_LENGTH);

        return VOS_ERR;
    }

    if ( VOS_OK != VOS_FixedQueueWrite( ulQid, pActualMsg, (VOS_UINT32)MSG_SEND_SIZE,
                                        VOS_EMERGENT_PRIORITY_MSG, ulPid ) )
    {
        /*lint -e534*/
        LogPrint3("# V_SendLocalUrgentMsg Error,queue full,Tx Pid %d Rx Pid %d Name 0x%x.\n",
            (int)(pMsgCtrlBlk->ulSenderPid), (int)ulPid,
            (int)(*(VOS_UINT32 *)(pMsgCtrlBlk->aucValue)) );
        /*lint +e534*/

        pstDumpMsgInfo = (VOS_DUMP_MSG_STRU *)g_aucDumpMsgInfo;

        /*lint -e534*/
        (VOS_VOID)VOS_TaskLock();
        /*lint +e534*/

        pstDumpMsgInfo->ulQid = ulQid;
        pstDumpMsgInfo->ulSendPid = pMsgCtrlBlk->ulSenderPid;
        pstDumpMsgInfo->ulRcvPid = ulPid;
        pstDumpMsgInfo->ulMsgName = *(VOS_UINT32 *)(pMsgCtrlBlk->aucValue);

        pstDumpMsgInfo++;

        VOS_QueuePrintFull(ulQid, (VOS_CHAR *)pstDumpMsgInfo,
                            DUMP_MSG_INFO_LEN - sizeof(VOS_DUMP_MSG_STRU) );

        ulTaskTcb = VOS_GetTCBFromTID(vos_FidCtrlBlk[ulFid].Tid);

        VOS_ProtectionReboot(VOS_SAVE_STACK(OSA_SEND_URG_MSG_FAIL_TO_WRITE), (VOS_INT)ulTaskTcb,
                             lLineNo, g_aucDumpMsgInfo, DUMP_MSG_INFO_LEN);

        /*lint -e534*/
        VOS_TaskUnlock();

        VOS_FreeMsg( Pid, *ppMsg );
        /*lint +e534*/

        return VOS_ERR;
    }

    if ( VOS_MSG_RESERVED_HEAD_FLAG != ((MSG_BLOCK_HEAD*)pActualMsg)->ulFlag )
    {
        *ppMsg = VOS_NULL_PTR;
    }

    return VOS_OK;

}

/*****************************************************************************
 Function   : V_SendUrgentMsg
 Description: send urgent message
 Input      : Pid  -- process identifier to send message
              pMsg -- pointer of the message to be send
 Return     : Rerurn value of Msg_SendMsg
 *****************************************************************************/
VOS_UINT32 V_SendUrgentMsg(VOS_PID Pid, VOS_VOID ** ppMsg,
                                  VOS_UINT32 ulFileID, VOS_INT32 lLineNo )
{
    VOS_UINT32          ulResult;
    VOS_UINT32          ulPid;
    VOS_UINT32          ulCpuID;
    MsgBlock           *pMsgCtrlBlk;

    ulResult = V_CheckMsgPara( Pid, ppMsg, ulFileID, lLineNo );

    if ( VOS_OK != ulResult)
    {
        return ulResult;
    }

    pMsgCtrlBlk     = (MsgBlock*)(*ppMsg);
    ulPid           = pMsgCtrlBlk->ulReceiverPid;
    ulCpuID         = VOS_GET_CPU_ID(ulPid);

    if (VOS_NULL_PTR == g_astVOSSendMsgProcTable[ulCpuID].pfSendUrgentMsg)
    {
        /*lint -e534*/
        LogPrint3("# V_SendUrgentMsg, send api is null.F %d L %d RecvPid %d.\r\n",
                    (VOS_INT)ulFileID, lLineNo, (VOS_INT)ulPid);

        VOS_SetErrorNo(VOS_ERRNO_MSG_SEND_FUNCEMPTY);
        /*lint +e534*/

        return(VOS_ERRNO_MSG_SEND_FUNCEMPTY);
    }

    if ( (VOS_NULL_PTR != vos_MsgHook)
        && (VOS_PID_BUTT != g_astVOSSendMsgProcTable[ulCpuID].ulEndPID))
    {
        /*lint -e534*/
        (vos_MsgHook)(*ppMsg);
        /*lint +e534*/
    }

    return g_astVOSSendMsgProcTable[ulCpuID].pfSendUrgentMsg( Pid, ppMsg, ulFileID, lLineNo );
}

/*****************************************************************************
 Function   : V_PostMsg
 Description: This function is synchronization msg send.
              In fact, it calls receiver Pid's Msg Process func to handle
              the message directly.
 Input      : Pid  -- PID who send the message
              pMsg -- Pointer of message to be sent
 Return     : VOS_OK on success and errno on failure
 Other      : 1) The sender Pid and Receiver Pid must in the same local Board.
              2) The caller should Alloc and Release Msg by itself.
 *****************************************************************************/
VOS_UINT32 V_PostMsg(VOS_PID Pid, VOS_VOID * pMsg,
                            VOS_UINT32 ulFileID, VOS_INT32 usLineNo )
{
    VOS_UINT32          ulReceiverPid;
    VOS_UINT32          ulReceiverCpuId;
    VOS_UINT_PTR        ulBlockAdd;
    VOS_UINT_PTR        ulCtrlkAdd;
    VOS_VOID            *pActualMsg;

    if( VOS_NULL_PTR == pMsg )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_INPUTMSGISNULL);
        /*lint +e534*/
        return VOS_ERRNO_MSG_POST_INPUTMSGISNULL;
    }

    /*The sender Pid and Receiver Pid must in one Board */
    ulReceiverCpuId = ((MsgBlock *)pMsg)->ulReceiverCpuId;
    if( VOS_LOCAL_CPUID != ulReceiverCpuId )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_RECVCPUNOTLOCAL);
        /*lint +e534*/
        return VOS_ERRNO_MSG_POST_RECVCPUNOTLOCAL;
    }

    ulReceiverPid = ((MsgBlock*)pMsg)->ulReceiverPid;
    if( ulReceiverPid >= VOS_PID_BUTT )
    {
        /*lint -e534*/
        VOS_SetErrorNo(VOS_ERRNO_MSG_POST_RECVPIDINVALID);
        /*lint +e534*/
        return VOS_ERRNO_MSG_POST_RECVPIDINVALID;
    }

    pActualMsg = (VOS_VOID *)((VOS_UINT_PTR)pMsg - VOS_MSG_BLK_HEAD_LEN);

    if ( VOS_OK != VOS_MemCheck( pActualMsg, &ulBlockAdd, &ulCtrlkAdd,
        ulFileID, usLineNo ) )
    {
        /*lint -e534*/
        LogPrint("# VOS_PostMsg Mem error.\n");
        /*lint +e534*/
        return VOS_ERR;
    }

    /* call receive Pid's Msg Process func */
    (vos_PidRecords[ulReceiverPid-VOS_PID_DOPRAEND].MsgFunction)((MsgBlock *)pMsg);

    return VOS_OK;
}

/*****************************************************************************
 Function   : VOS_GetMsgName
 Description: get message name
 Input      : void
 Return     : void
 Other      :
 *****************************************************************************/
VOS_UINT32 VOS_GetMsgName(VOS_UINT_PTR ulAddrress)
{
    MsgBlock *pstMsgBlock = (MsgBlock*)( ulAddrress + VOS_MSG_BLK_HEAD_LEN );

    return *((VOS_UINT32 *)(pstMsgBlock->aucValue));
}





