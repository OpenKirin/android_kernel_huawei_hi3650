
#include "vos.h"
#include "Taf_Tafm_Remote.h"

#include "MnCommApi.h"

#include "TafApi.h"

#include "MnClient.h"
#include "TafAppMma.h"




/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID PS_FILE_ID_TAF_TAFM_APPREMOTE_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/****************************************************/
/*    Զ��APIʹ�õ�ȫ�ֱ���ȫ���ڶ���ʱ���г�ʼ��   */
/****************************************************/
/*��¼APP�ص�������Ϣ���*/


/*��¼TAFԶ���Ƿ�ע���MUX�ص�����*/
VOS_UINT8 g_ucTafRetRegMuxCallbackFlag = TAF_REG_MUX_CALLBACK_NO;

/*****************************************************************************
 �� �� ��  : Taf_GetAppMsgLen
 ��������  :
 �������  : VOS_UINT32 ulParaLen
             VOS_UINT32 *pulMsgLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��8��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  Taf_GetAppMsgLen(VOS_UINT32 ulParaLen, VOS_UINT32 *pulMsgLen)
{
    VOS_UINT32  ulMsgLen;

    if(VOS_NULL_PTR == pulMsgLen)
    {
        return VOS_ERR;
    }

    if ( ulParaLen <= 4 )
    {
        ulMsgLen = sizeof(MN_APP_REQ_MSG_STRU);
    }
    else
    {
        ulMsgLen = (sizeof(MN_APP_REQ_MSG_STRU) + ulParaLen) -4;
    }

    *pulMsgLen = ulMsgLen;

    return VOS_OK;

}

/**********************************************************/
/*                  ͨ�Ų������ò�ѯAPI                   */
/**********************************************************/

/**********************************************************
 Function:       Taf_ParaQuery
 Description:    ͨ�Ų�����ѯ����
 Calls:          APP/AT
 Data Accessed:
 Data Updated:
 Input:          ClientId - APP/AT��ʶ
                 OpId - ������ʶ
                 ParaType - ͨ�Ų�������
                 pPara - ��������
 Output:
 Return:         TAF_SUCCESS - �ɹ�
                 TAF_FAILURE - ʧ��
 Others:
  1.   L47619   2006.03.03   ���ⵥ:A32D02338
  2 ��    �� : 2006-12-07
    ��    �� : ��³��
    �޸����� : A32D07824 ����CGEQNEG�Ĵ���
  3.��    �� : 2013��07��08��
    ��    �� : Y00213812
    �޸����� : VoLTE_PhaseI ��Ŀ��ɾ���������
**********************************************************/
VOS_UINT32  Taf_ParaQuery  (
    VOS_UINT16                     ClientId,
    VOS_UINT8                      OpId,
    TAF_PARA_TYPE                  ParaType,
    VOS_VOID                      *pPara
)
{
    VOS_UINT8                           *pucPara;
    VOS_UINT16                           usMsgName;
    VOS_UINT32                           ulParaLen;
    VOS_UINT32                           ulRst;
    VOS_UINT32                           ulReceiverPid;

    if ((ParaType >= TAF_PH_MS_CLASS_PARA)
        && (ParaType < TAF_TELE_PARA_BUTT))
    {
        ulParaLen = sizeof(TAF_PARA_TYPE);
        ulReceiverPid = I0_WUEPS_PID_MMA;
        usMsgName = TAF_MSG_PARA_READ;
    }
    else
    {
        return TAF_FAILURE;
    }

    pucPara = (VOS_UINT8 *)PS_MEM_ALLOC( WUEPS_PID_AT, ulParaLen );

    if (VOS_NULL_PTR == pucPara)
    {
        return TAF_FAILURE;
    }

    PS_MEM_SET( pucPara, 0 , ulParaLen );

    PS_MEM_CPY( pucPara, &ParaType, sizeof(TAF_PARA_TYPE) );

    ulRst = MN_FillAndSndAppReqMsg( ClientId,
                                  OpId,
                                  usMsgName,
                                  pucPara,
                                  ulParaLen,
                                  ulReceiverPid);
    PS_MEM_FREE( WUEPS_PID_AT, pucPara );

    return ulRst;
}



