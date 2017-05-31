

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafAppXsmsInterface.h"
#include "MnClient.h"




#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_API_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
�� �� ��  : TAF_XSMS_GetReceiverPid
��������  : ��Client ID������PID��ת��
�������  : ClientId -- AT�ͻ�ID
�������  : pulReceiverPid -- ����PID
�� �� ֵ  : VOS_OK/VOS_ERR
���ú���  : ��
��������  :

�޸���ʷ      :
 1.��    ��   : 2014��10��31��
   ��    ��   : h00300778
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetReceiverPid(MN_CLIENT_ID_T  ClientId, VOS_UINT32 *pulReceiverPid)
{
    MODEM_ID_ENUM_UINT16    enModemID;

    /* ���ýӿڻ�ȡModem ID */
    if (VOS_OK != AT_GetModemIdFromClient(ClientId, &enModemID))
    {
        return VOS_ERR;
    }

    if (MODEM_ID_1 == enModemID)
    {
        *pulReceiverPid = I1_UEPS_PID_XSMS;
    }
    else if (MODEM_ID_2 == enModemID)
    {
        *pulReceiverPid = I2_UEPS_PID_XSMS;
    }
    else
    {
        *pulReceiverPid = I0_UEPS_PID_XSMS;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_SendSmsReq
 ��������  : APP�Ķ��ŷ�������
 �������  : usClientId:����������Client��ID
             ucOpId:��ʶ���β���
             enSndOption:����ѡ��
             pucData:Ҫ���͵Ķ�������
 �������  : ��
 �� �� ֵ  : VOS_OK -- ��Ϣ���ͳɹ�
             VOS_ERR -- ��Ϣ���ͳɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SendSmsReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_XSMS_SEND_OPTION_ENUM_UINT8     enSndOption,
    VOS_UINT8                          *pucData)
{
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_SetXsmsApMemFullReq
 ��������  : ֪ͨ����ģ�� AP����Ŵ洢�ռ��ǲ������� 0 �� 1 ����
 �������  : usClientId:����������Client��ID
             ucOpId:��ʶ���β���
             ucApMemFullFlag:���Ŵ洢�ռ��ǲ������� 0 �� 1 ����s
 �������  : ��
 �� �� ֵ  : VOS_OK -- ��Ϣ���ͳɹ�
             VOS_ERR -- ��Ϣ���ͳɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_SetXsmsApMemFullReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucApMemFullFlag)
{
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_WriteSmsReq
 ��������  : APP�Ķ���д������
 �������  : usClientId:����������Client��ID
             ucOpId:��ʶ���β���
             enStatus:����״̬
             pucData:Ҫ���͵Ķ�������
 �������  : ��
 �� �� ֵ  : VOS_OK -- ��Ϣ���ͳɹ�
             VOS_ERR -- ��Ϣ���ͳɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_WriteSmsReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_XSMS_STATUS_ENUM_UINT8          enStatus,
    VOS_UINT8                          *pucData)
{
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_DeleteSmsReq
 ��������  : APP�Ķ���ɾ������
 �������  : usClientId:����������Client��ID
             ucOpId:��ʶ���β���
             ucIndex:ɾ����������
 �������  : ��
 �� �� ֵ  : VOS_OK -- ��Ϣ���ͳɹ�
             VOS_ERR -- ��Ϣ���ͳɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_DeleteSmsReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucIndex)
{
    return VOS_ERR;
}




