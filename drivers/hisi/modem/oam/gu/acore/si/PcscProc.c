

/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : PcscProc.c
Author      : w00184875
Version     : V300R002
Date        : 2011-09-19
Description : ���ļ�������ACPU��PCSC����ʵ��
History     :

1.��    ��  : 2011��9��19��
  ��    ��  : w00184875
  �޸�����  : Create
************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PcscProc.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PCSC_APP_PROC_C
/*lint +e767*/

/*ACPU��ά����״̬��ȫ�ֱ���*/
USIMM_CARD_SERVIC_ENUM_UINT32 g_enAcpuCardStatus = USIMM_CARD_SERVIC_BUTT;

extern VOS_VOID OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber, VOS_UINT32 ulSendPid, VOS_UINT32 ulRcvPid, VOS_UINT32 ulMsgName);
extern VOS_VOID OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_ENUM_UINT32 enNumber);

/*****************************************************************************
�� �� ��  :PCSC_AcpuCmdReq
��������  :PCSC����
�������  :ulCmdType:��������
           pucAPDU  :APDU��������
           ulAPDULen:APDU�����
�������  :��
�� �� ֵ  :VOS_OK
           VOS_ERR
�޶���¼  :
1. ��    ��   : 2010��3��5��
   ��    ��   : h59254
   �޸�����   : Creat
2. ��    ��   : 2011��10��10��
   ��    ��   : w00184875
   �޸�����   : ��CCPU��ֲ����
*****************************************************************************/
VOS_UINT32 PCSC_AcpuCmdReq(VOS_UINT32 ulCmdType, VOS_UINT8 *pucAPDU, VOS_UINT32 ulAPDULen)
{
    SI_PIH_PCSC_REQ_STRU     *pstMsg;

    if((ulAPDULen > 5)&&(pucAPDU[4] != ulAPDULen-5))
    {
        PS_LOG(ACPU_PID_PCSC, 0, PS_PRINT_ERROR, "PCSC_AcpuCmdReq: Data Len is Not Eq P3");
        return VOS_ERR;
    }

    pstMsg = (SI_PIH_PCSC_REQ_STRU *)VOS_AllocMsg(ACPU_PID_PCSC,
                        (sizeof(SI_PIH_PCSC_REQ_STRU) - VOS_MSG_HEAD_LENGTH) + ulAPDULen);
    if (VOS_NULL_PTR == pstMsg)
    {
        /* ��ӡ���� */
        PS_LOG(ACPU_PID_PCSC, 0, PS_PRINT_WARNING, "PCSC_AcpuCmdReq: VOS_AllocMsg is Failed");
        /*lint -e534*/
        vos_printf("PCSC_AcpuCmdReq: VOS_AllocMsg is Failed.\r\n");
        /*lint +e534*/

        return VOS_ERR; /* ���غ���������Ϣ */
    }

    pstMsg->stMsgHeader.ulReceiverPid = MAPS_PIH_PID;
    pstMsg->stMsgHeader.ulMsgName     = SI_PIH_PCSC_DATA_REQ;
    pstMsg->stMsgHeader.ulEventType   = ulCmdType;
    pstMsg->stMsgHeader.usClient      = 0xFFFF;
    pstMsg->ulCmdType                 = ulCmdType;
    pstMsg->ulCmdLen                  = ulAPDULen;

    if(ulAPDULen != 0)
    {
        /*lint -e534*/
        VOS_MemCpy(pstMsg->aucAPDU, pucAPDU, ulAPDULen);
        /*lint +e534*/
    }

    if (VOS_OK != VOS_SendMsg(ACPU_PID_PCSC, pstMsg))
    {
        /*��ӡ����*/
        PS_LOG(ACPU_PID_PCSC, 0, PS_PRINT_WARNING, "PCSC_AcpuCmdReq: VOS_SendMsg is Failed.");
        /*lint -e534*/
        vos_printf("PCSC_AcpuCmdReq: VOS_SendMsg is Failed.");
        /*lint +e534*/
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  :PCSC_GetCardStatus
��������  :��״̬�ӿ�
�������  :��
�������  :��
�� �� ֵ  :VOS_OK - �п�
           VOS_ERROR - �޿�
�޶���¼  :
1. ��    ��   : 2010��10��10��
   ��    ��   : w00184875
   �޸�����   : Creat
*****************************************************************************/
VOS_INT PCSC_AcpuGetCardStatus(VOS_VOID)
{
    if (USIMM_CARD_SERVIC_ABSENT == g_enAcpuCardStatus)
    {
        /*�ϱ��޿�״̬*/
        return VOS_ERROR;
    }
    /*�ϱ��п�״̬*/
    return VOS_OK;
}


/*****************************************************************************
�� �� ��  :PCSC_UpdateCardStatus
��������  :�յ�CCPU�������Ŀ�״̬������Ϣ������
�������  :pstMsg:��Ϣ��
�������  :��
�� �� ֵ  :VOS_VOID
�޶���¼  :
1. ��    ��   : 2011��10��10��
   ��    ��   : w00184875
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID PCSC_UpdateCardStatus(USIMM_CARDSTATUS_IND_STRU *pstMsg)
{
    if (USIMM_CARD_SERVIC_BUTT == g_enAcpuCardStatus)
    {
        /*lint -e534*/
        vos_printf("Reg PCSC Func.\r\n");
        /*lint +e534*/
    }

    /*���±��ؿ�״̬��ȫ�ֱ���*/
    g_enAcpuCardStatus = pstMsg->stUsimSimInfo.enCardService;

    /*lint -e534*/
    vos_printf("Update Card Status: %d .\r\n", g_enAcpuCardStatus);
    /*lint +e534*/


    return;
}

/*****************************************************************************
�� �� ��  :PCSC_AcpuMsgProc
��������  :PCSC��Ϣ������
�������  :pMsg:��Ϣ��
�������  :��
�� �� ֵ  :VOS_VOID
�޶���¼  :
1. ��    ��   : 2010��10��10��
   ��    ��   : w00184875
   �޸�����   : Creat
*****************************************************************************/
VOS_VOID  PCSC_AcpuMsgProc( MsgBlock *pMsg)
{
    SI_PIH_PCSC_CNF_STRU *pstPCSCMsg;

    pstPCSCMsg = (SI_PIH_PCSC_CNF_STRU*)pMsg;

    OM_RecordInfoStart(VOS_EXC_DUMP_MEM_NUM_1, pMsg->ulSenderPid, ACPU_PID_PCSC, *((VOS_UINT32*)pMsg->aucValue));

    switch(pstPCSCMsg->ulMsgName)
    {
        case SI_PIH_PCSC_DATA_CNF:
            break;
        case USIMM_CARDSTATUS_IND:
            PCSC_UpdateCardStatus((USIMM_CARDSTATUS_IND_STRU *)pMsg);
            break;
        default:
            PS_LOG(ACPU_PID_PCSC, 0, PS_PRINT_WARNING, "PCSC_AcpuMsgProc: unknow MsgType");
            break;
    }

    OM_RecordInfoEnd(VOS_EXC_DUMP_MEM_NUM_1);

    return;
}

/*****************************************************************************
�� �� ��  :TestSendPcscCmd
��������  :��׮����˫��PCSC����
�������  :
�������  :��
�� �� ֵ  :VOS_VOID
�޶���¼  :
1. ��    ��   : 2010��10��15��
   ��    ��   : w00184875
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 TestSendPcscCmd(VOS_UINT32 ulCmdType)
{
    VOS_UINT8 aucApduData[5];

    aucApduData[4] = '\0';

    return PCSC_AcpuCmdReq(ulCmdType,aucApduData,5);
}


