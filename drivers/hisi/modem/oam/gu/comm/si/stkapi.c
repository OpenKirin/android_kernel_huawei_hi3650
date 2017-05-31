

/************************************************************************
Copyright   : 2005-2008, Huawei Tech. Co., Ltd.
File name   : STKApi.c
Author      : m00128685
Version     : V200R001
Date        : 2008-12-28
Description : ���ļ�������STKģ��Ķ���ӿ�

Description :
History     :

1.��    ��  : 2008��12��28��
  ��    ��  : m00128685
  �޸�����  : Create
************************************************************************/

#include "siappstk.h"
#include "si_stk.h"
#include "product_config.h"




/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_STK_API_C
/*lint +e767*/

/*****************************************************************************
�� �� ��  : GetMainMenu
��������  : ��ȡSTK���ܵ����˵�
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2009��7��6��
  ��    ��  : H9254
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SendReqMsg(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    VOS_UINT32                          MsgName,
    VOS_UINT32                          CmdType,
    VOS_UINT32                          DataLen,
    VOS_UINT8                           *pData)
{
    SI_STK_REQ_STRU         *pstSTKReq;
    VOS_UINT32              ulSendPid;
    VOS_UINT32              ulReceiverPid;
    MODEM_ID_ENUM_UINT16    enModemID;

    ulSendPid = WUEPS_PID_AT;

    /* ���ýӿڻ�ȡModem ID */
    if(VOS_OK != AT_GetModemIdFromClient(ClientId,&enModemID))
    {
      STK_ERROR_LOG("SI_STK_SendReqMsg: AT_GetModemIdFromClient Return Error");
      return VOS_ERR;
    }

    if(MODEM_ID_1 == enModemID)
    {
        ulReceiverPid = I1_MAPS_STK_PID;
    }
    else if(MODEM_ID_2 == enModemID)
    {
        ulReceiverPid = I2_MAPS_STK_PID;
    }
    else
    {
        ulReceiverPid = I0_MAPS_STK_PID;
    }


    pstSTKReq = (SI_STK_REQ_STRU *)VOS_AllocMsg(ulSendPid, sizeof(SI_STK_REQ_STRU)-VOS_MSG_HEAD_LENGTH+DataLen);

    if(VOS_NULL_PTR == pstSTKReq)
    {
        STK_ERROR_LOG("SI_STK_SendReqMsg: VOS_AllocMsg Return Error");
        return VOS_ERR;
    }

    pstSTKReq->MsgName       = MsgName;
    pstSTKReq->ulReceiverPid = ulReceiverPid;
    pstSTKReq->OpId          = OpId;
    pstSTKReq->ClientId      = ClientId;
    pstSTKReq->SatType       = CmdType;
    pstSTKReq->Datalen       = DataLen;

    if(DataLen != 0)
    {
        /*lint -e534*/
        VOS_MemCpy_s(pstSTKReq->Data, DataLen, pData, DataLen);
        /*lint +e534*/
    }

    if(VOS_OK != VOS_SendMsg(ulSendPid, pstSTKReq))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : GetMainMenu
��������  : ��ȡSTK���ܵ����˵�
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2009��7��6��
  ��    ��  : H9254
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_GetMainMenu(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId)
{
    return SI_STK_SendReqMsg(ClientId,OpId, SI_STK_GETMAINMNUE, SI_STK_NOCMDDATA,0,VOS_NULL_PTR);
}

/*****************************************************************************
�� �� ��  : SI_STK_GetSTKCommand
��������  : ��ȡ�����STK��������
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��18��
  ��    ��  : z00100318
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_GetSTKCommand(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_STK_CMD_TYPE                     CmdType)
{
    return SI_STK_SendReqMsg(ClientId,OpId, SI_STK_GETCOMMAND, CmdType,0,VOS_NULL_PTR);
}

/*****************************************************************************
�� �� ��  : SI_STK_QuerySTKCommand
��������  : ��ѯ���һ��SIM���ϱ�����������
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��18��
  ��    ��  : z00100318
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_QuerySTKCommand(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId)
{
    return VOS_ERR;
}

/*****************************************************************************
�� �� ��  : SI_STK_DataSendSimple
��������  : �ն˸����·����ݺ���
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��18��
  ��    ��  : z00100318
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_DataSendSimple(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_SEND_DATA_TYPE                   SendType,
    VOS_UINT32                          DataLen,
    VOS_UINT8                           *pData)
{
    return SI_STK_SendReqMsg(ClientId,OpId, SI_STK_SIMPLEDOWN,SendType,DataLen,pData);
}

/*****************************************************************************
�� �� ��  : SI_STK_TerminalResponse
��������  : �ն˸�����Ӧ����
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��18��
  ��    ��  : z00100318
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_TerminalResponse(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_STK_TERMINAL_RSP_STRU            *pstTRStru)
{
    return VOS_ERR;
}


/*****************************************************************************
�� �� ��  : SI_STKDualIMSIChangeReq
��������  : ����IMSI�л����̣��ִ�ᶨ������
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2010��02��10��
  ��    ��  : m00128685
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_STKDualIMSIChangeReq(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId)
{
    return TAF_FAILURE;
}

/*****************************************************************************
�� �� ��  : SI_STKIsDualImsiSupport
��������  : �ж��Ƿ�֧��Dual IMSI�л�
�������  : ��
�������  : ��
�� �� ֵ  : ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2010��02��11��
  ��    ��  : m00128685
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_STKIsDualImsiSupport(VOS_VOID)
{
    return TAF_FAILURE;
}

/*****************************************************************************
�� �� ��  : SI_STK_MenuSelection
��������  : STK����ENVELOP���غ���
�������  : ��
�������  : ��
�� �� ֵ  : VOS_UINT32����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��18��
  ��    ��  : z00100318
  �޸�����  : Create
*****************************************************************************/

VOS_UINT32 SI_STK_MenuSelection(
    MN_CLIENT_ID_T                      ClientId,
    MN_OPERATION_ID_T                   OpId,
    SI_STK_ENVELOPE_STRU                *pstENStru)
{
    return TAF_FAILURE;
}

/*****************************************************************************
�� �� ��  : SI_STK_SetUpCallConfirm
��������  : �û��ظ��Ƿ����������
�������  : ulAction -- �û��ظ����
�������  : ��
�� �� ֵ  : ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2012��9��14��
  ��    ��  : j00168360
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_STK_SetUpCallConfirm(
    MN_CLIENT_ID_T                      ClientId,
    SI_STK_SETUPCALLCONFIRM_ENUM_UINT32 enAction)
{
    /* ������� */
    if (SI_STK_SETUPCALL_BUTT <= enAction)
    {
        STK_ERROR_LOG("SI_STK_SetUpCallConfirm: The Input Para is Error");

        return VOS_ERR;
    }

    return SI_STK_SendReqMsg(ClientId, 0, SI_STK_SETUPCALL_CONFIRM, SI_STK_SETUPCALL, sizeof(VOS_UINT32), (VOS_UINT8*)&enAction);
}





