

/************************************************************************
  Copyright    : 2005-2009, Huawei Tech. Co., Ltd.
  File name    : PBApi.c
  Author       : z00100318
  Version      : V200R001
  Date         : 2008-10-28
  Description  : ��C�ļ�������---�ӿ�ģ��ʵ��
  Function List:
  History      :
 ************************************************************************/


#include "TafTypeDef.h"
#include "si_pb.h"
#include "product_config.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define      THIS_FILE_ID     PS_FILE_ID_PBAPI_C
/*lint +e767*/


/*****************************************************************************
�� �� ��  : SI_PB_GetReceiverPid
��������  : FDN����
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��18��
  ��    ��  : H59254
  �޸�����  : Create
*****************************************************************************/
VOS_UINT32 SI_PB_GetReceiverPid(MN_CLIENT_ID_T  ClientId, VOS_UINT32 *pulReceiverPid)
{
    MODEM_ID_ENUM_UINT16    enModemID;

    /* ���ýӿڻ�ȡModem ID */
    if(VOS_OK != AT_GetModemIdFromClient(ClientId,&enModemID))
    {
        return VOS_ERR;
    }

    if(MODEM_ID_1 == enModemID)
    {
        *pulReceiverPid = I1_MAPS_PB_PID;
    }
    else if (MODEM_ID_2 == enModemID)
    {
        *pulReceiverPid = I2_MAPS_PB_PID;
    }
    else
    {
        *pulReceiverPid = I0_MAPS_PB_PID;
    }

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  : SI_PB_Read
��������  : ��ȡ�绰����¼
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��14��
  ��    ��  : H59254
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_Read(  MN_CLIENT_ID_T           ClientId,
                            MN_OPERATION_ID_T        OpId,
                            SI_PB_STORATE_TYPE       Storage,
                            SI_UINT16                Index1,
                            SI_UINT16                Index2)
{
    return TAF_FAILURE;
}

/*****************************************************************************
�� �� ��  : SI_PB_SRead
��������  : ��ȡ���ϵ绰����¼
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2009��06��05��
  ��    ��  : m00128685
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_SRead(  MN_CLIENT_ID_T           ClientId,
                            MN_OPERATION_ID_T        OpId,
                            SI_PB_STORATE_TYPE       Storage,
                            SI_UINT16                Index1,
                            SI_UINT16                Index2)
{
    return TAF_FAILURE;
}

/*****************************************************************************
�� �� ��  : SI_PB_Query
��������  : �绰�������ѯ
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��14��
  ��    ��  : H59254
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_Query(     MN_CLIENT_ID_T           ClientId,
                                MN_OPERATION_ID_T        OpId)
{
    return TAF_FAILURE;
}

/*****************************************************************************
�� �� ��  : SI_PB_Set
��������  : ���õ�ǰ���뱾ʹ�õĴ洢������
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��14��
  ��    ��  : H59254
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_Set(    MN_CLIENT_ID_T           ClientId,
                            MN_OPERATION_ID_T        OpId,
                            SI_PB_STORATE_TYPE      Storage)
{
    SI_PB_SET_REQ_STRU  *pMsg;
    VOS_UINT32          ulReceiverPid;

    if(SI_PB_STORAGE_FD != Storage)
    {
        PB_ERROR_LOG("SI_PB_Set:Double Modem only support the FDN");

        return TAF_FAILURE;
    }

    if (VOS_OK != SI_PB_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PB_ERROR_LOG("SI_PB_Set:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    pMsg = (SI_PB_SET_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Set:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->ulMsgName     = SI_PB_SET_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->ulStorage     = Storage;

    if(VOS_OK != VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Set:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

/*****************************************************************************
�� �� ��  : SI_PB_Add
��������  : �绰����׷��һ����¼
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��14��
  ��    ��  : H59254
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_Add(    MN_CLIENT_ID_T          ClientId,
                            MN_OPERATION_ID_T        OpId,
                             SI_PB_STORATE_TYPE      Storage,
                             SI_PB_RECORD_STRU       *pRecord)
{
    SI_PB_ADD_REP_STRU  *pMsg;
    VOS_UINT32          ulReceiverPid;

    if (VOS_OK != SI_PB_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PB_ERROR_LOG("SI_PB_Add:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    if(VOS_NULL_PTR == pRecord)
    {
        PB_ERROR_LOG("SI_PB_Add:pRecord is a NULL pointer");

        return TAF_FAILURE;
    }

    /*lint -e433  �޸���: j00174725; ������: xucheng */
    pMsg = (SI_PB_ADD_REP_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_ADD_REP_STRU) - VOS_MSG_HEAD_LENGTH);
    /*lint +e433  �޸���: j00174725; ������: xucheng */

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Add:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->ulMsgName     = SI_PB_ADD_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;

    pMsg->ulStorage = SI_PB_STORAGE_FD;     /*ֻ�ܹ�����FDN����*/

    pRecord->Index = 1;

    /*lint -e534*/
    VOS_MemCpy_s(&pMsg->stRecord, sizeof(SI_PB_RECORD_STRU), pRecord, sizeof(SI_PB_RECORD_STRU));
    /*lint +e534*/

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Add:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}
/*****************************************************************************
�� �� ��  : SI_PB_SAdd
��������  : �绰����׷��һ����¼
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2009��06��05��
  ��    ��  : m00128685
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_SAdd(    MN_CLIENT_ID_T          ClientId,
                            MN_OPERATION_ID_T        OpId,
                             SI_PB_STORATE_TYPE      Storage,
                             SI_PB_RECORD_STRU       *pRecord)
{
    return TAF_FAILURE;
}

/*****************************************************************************
�� �� ��  : SI_PB_Modify
��������  : �绰����׷��һ����¼
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��14��
  ��    ��  : H59254
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_Modify(    MN_CLIENT_ID_T          ClientId,
                                MN_OPERATION_ID_T       OpId,
                                SI_PB_STORATE_TYPE      Storage,
                                SI_PB_RECORD_STRU       *pRecord )
{
    SI_PB_MODIFY_REP_STRU  *pMsg;
    VOS_UINT32              ulReceiverPid;

    if (VOS_OK != SI_PB_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PB_ERROR_LOG("SI_PB_Modify:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    if(VOS_NULL_PTR == pRecord)
    {
        PB_ERROR_LOG("SI_PB_Modify:pRecord is a NULL pointer");

        return TAF_FAILURE;
    }

    /*lint -e433  �޸���: j00174725; ������: xucheng */
    pMsg = (SI_PB_MODIFY_REP_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_MODIFY_REP_STRU) - VOS_MSG_HEAD_LENGTH);
    /*lint +e433  �޸���: j00174725; ������: xucheng */

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Modify:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->ulMsgName     = SI_PB_MODIFY_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;

    pMsg->ulStorage = SI_PB_STORAGE_FD;     /*ֻ�ܹ�����FDN����*/

    /*lint -e534*/
    VOS_MemCpy_s(&pMsg->Record, sizeof(SI_PB_RECORD_STRU), pRecord, sizeof(SI_PB_RECORD_STRU));
    /*lint +e534*/

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Modify:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

/*****************************************************************************
�� �� ��  : SI_PB_SModify
��������  : �绰����׷��һ����¼
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2009��06��05��
  ��    ��  : m00128685
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_SModify(    MN_CLIENT_ID_T          ClientId,
                                MN_OPERATION_ID_T       OpId,
                                SI_PB_STORATE_TYPE      Storage,
                                SI_PB_RECORD_STRU       *pRecord )
{
    return TAF_FAILURE;
}

/*****************************************************************************
�� �� ��  : SI_PB_Delete
��������  : �绰����ɾ��һ����¼
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2008��10��14��
  ��    ��  : H59254
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_Delete(     MN_CLIENT_ID_T             ClientId,
                                MN_OPERATION_ID_T           OpId,
                                SI_PB_STORATE_TYPE          Storage,
                                SI_UINT16                   Index)
{
    SI_PB_DELETE_REQ_STRU  *pMsg;
    VOS_UINT32              ulReceiverPid;

    if (VOS_OK != SI_PB_GetReceiverPid(ClientId, &ulReceiverPid))
    {
        PB_ERROR_LOG("SI_PB_Modify:Get ulReceiverPid Error.");

        return TAF_FAILURE;
    }

    pMsg = (SI_PB_DELETE_REQ_STRU *)VOS_AllocMsg(WUEPS_PID_AT, sizeof(SI_PB_DELETE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        PB_ERROR_LOG("SI_PB_Delete:VOS_AllocMsg Failed");

        return TAF_FAILURE;
    }

    pMsg->ulReceiverPid = ulReceiverPid;
    pMsg->ulMsgName     = SI_PB_DELETE_REQ;
    pMsg->usClient      = ClientId;
    pMsg->ucOpID        = OpId;
    pMsg->usIndex       = Index;

    pMsg->ulStorage = SI_PB_STORAGE_FD;     /*ֻ�ܹ�����FDN����*/

    if(VOS_OK !=  VOS_SendMsg(WUEPS_PID_AT, pMsg))
    {
        PB_ERROR_LOG("SI_PB_Delete:VOS_SendMsg Failed");

        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

/*****************************************************************************
�� �� ��  : SI_PB_Search
��������  : �绰���в���һ����¼
�������  : ��
�������  : ��
�� �� ֵ  : SI_UINT32 ����ִ�н��
���ú���  : ��
��������  : �ⲿ�ӿ�
History     :
1.��    ��  : 2009��3��12��
  ��    ��  : H59254
  �޸�����  : Create
*****************************************************************************/
SI_UINT32 SI_PB_Search(    MN_CLIENT_ID_T             ClientId,
                                MN_OPERATION_ID_T           OpId,
                                SI_PB_STORATE_TYPE          Storage,
                                SI_UINT8                    ucLength,
                                SI_UINT8                    *pucContent)
{
    return TAF_FAILURE;
}

/*****************************************************************************
�� �� ��  :SI_PB_GetStorateType
��������  :��ȡ�绰����ǰ�洢����
�������  :��
�������  :��
�� �� ֵ  :�绰����ǰ�洢����

�޶���¼  :
1. ��    ��   : 2011��05��17��
   ��    ��   : j00168360
   �޸�����   : Creat [DTS2011042105653]��at+cpbf��ϲ��ҹ���
*****************************************************************************/
VOS_UINT32 SI_PB_GetStorateType(VOS_VOID)
{
    return SI_PB_STORAGE_UNSPECIFIED;   /*���ص�ǰδָ��*/
}

/*****************************************************************************
�� �� ��  :SI_PB_GetSPBFlag
��������  :��ȡ���ϵ绰����־���ɴ˿��жϳ���ǰ�Ƿ�֧�ָ��ϵ绰��
�������  :��
�������  :��
�� �� ֵ  :���ϵ绰��flag

�޶���¼  :
1. ��    ��   : 2011��05��17��
   ��    ��   : j00168360
   �޸�����   : Creat [DTS2011042105653]��at+cpbf��ϲ��ҹ���
*****************************************************************************/
VOS_UINT32 SI_PB_GetSPBFlag(VOS_VOID)
{
    return VOS_FALSE;   /*����״̬�ر�*/
}







