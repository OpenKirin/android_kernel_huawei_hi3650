
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AdsDownLink.h"
#include "AdsDebug.h"
#include "mdrv.h"
#include "AcpuReset.h"
#include "AdsFilter.h"
#include "AdsDhcpInterface.h"
#include "AdsMntn.h"



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_DOWNLINK_C
/*lint +e767*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : ADS_DL_CCpuResetCallback
 ��������  : C�˵�����λʱADS DL�Ļص�������
 �������  : enParam   -- 0��ʾ��λǰ�� ������ʾ��λ��
             lUserData -- �û�����
 �������  : ��
 �� �� ֵ  : VOS_INT
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��10��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT ADS_DL_CCpuResetCallback(
    DRV_RESET_CB_MOMENT_E               enParam,
    VOS_INT                             lUserData
)
{
    ADS_CCPU_RESET_IND_STRU                *pstMsg = VOS_NULL_PTR;

    /* ����Ϊ0��ʾ��λǰ���� */
    if (MDRV_RESET_CB_BEFORE == enParam)
    {
        ADS_TRACE_HIGH("before reset enter.\n");

        /* ��ֹIPF���ݲ���, ������ȡһ��RD */
        ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);
        ADS_DBG_DL_CCORE_RESET_TRIG_EVENT(1);

        /* ������Ϣ */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_DL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_TRACE_HIGH("before reset: alloc msg failed.\n");
            return VOS_ERROR;
        }

        /* ��д��Ϣͷ */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_DL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_START_IND;

        /* ����Ϣ */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg))
        {
            ADS_TRACE_HIGH("before reset: send msg failed.\n");
            return VOS_ERROR;
        }

        /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ���Ϣ��������ź��������� */
        if (VOS_OK != VOS_SmP(ADS_GetDLResetSem(), ADS_RESET_TIMEOUT_LEN))
        {
            ADS_TRACE_HIGH("before reset VOS_SmP failed.\n");
            ADS_DBG_DL_RESET_LOCK_FAIL_NUM(1);
            return VOS_ERROR;
        }

        ADS_TRACE_HIGH("before reset succ.\n");
        return VOS_OK;
    }
    /* ��λ�� */
    else if (MDRV_RESET_CB_AFTER == enParam)
    {
        ADS_TRACE_HIGH("after reset enter.\n");

        /* ������Ϣ */
        pstMsg = (ADS_CCPU_RESET_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_ADS_DL,
                                                                        sizeof(ADS_CCPU_RESET_IND_STRU));
        if (VOS_NULL_PTR == pstMsg)
        {
            ADS_TRACE_HIGH("after reset: alloc msg failed.\n");
            return VOS_ERROR;
        }

        /* ��д��Ϣͷ */
        pstMsg->ulReceiverPid               = ACPU_PID_ADS_DL;
        pstMsg->enMsgId                     = ID_ADS_CCPU_RESET_END_IND;

        /* ����Ϣ */
        if (VOS_OK != PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg))
        {
            ADS_TRACE_HIGH("after reset: send msg failed.\n");
            return VOS_ERROR;
        }

        ADS_TRACE_HIGH("after reset: succ.\n");
        ADS_DBG_DL_RESET_SUCC_NUM(1);
        return VOS_OK;
    }
    else
    {
        return VOS_ERROR;
    }
}

/*****************************************************************************
 �� �� ��  : ADS_DL_IpfIntCB
 ��������  : ADS�������ݴ���ģ����IPFע����жϻص�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_INT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��4��12��
    ��    ��   : A00165503
    �޸�����   : DTS2012020708222: ADS�����Ż�
*****************************************************************************/
VOS_INT32 ADS_DL_IpfIntCB(VOS_VOID)
{
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);
    ADS_DBG_DL_RCV_IPF_RD_INT_NUM(1);
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_IpfAdqEmptyCB
 ��������  : ADS��IPFע�������ADQ���жϴ�����
 �������  : IPF_ADQ_EMPTY_E eAdqEmpty
 �������  : ��
 �� �� ֵ  : VOS_INT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT32 ADS_DL_IpfAdqEmptyCB(IPF_ADQ_EMPTY_E eAdqEmpty)
{
    if (IPF_EMPTY_ADQ0 == eAdqEmpty)
    {
        ADS_DBG_DL_ADQ_RCV_AD0_EMPTY_INT_NUM(1);
    }
    else if (IPF_EMPTY_ADQ1 == eAdqEmpty)
    {
        ADS_DBG_DL_ADQ_RCV_AD1_EMPTY_INT_NUM(1);
    }
    else
    {
        ADS_DBG_DL_ADQ_RCV_AD0_EMPTY_INT_NUM(1);
        ADS_DBG_DL_ADQ_RCV_AD1_EMPTY_INT_NUM(1);
    }

    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
    ADS_DBG_DL_RCV_IPF_ADQ_EMPTY_INT_NUM(1);
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RcvTiAdqEmptyExpired
 ��������  : TI_ADS_DL_ADQ_EMPTY��ʱ������
 �������  : VOS_UINT32                          ulParam,
             VOS_UINT32                          ulTimerName
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_DL_RcvTiAdqEmptyExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    /* ��������ADQ���жϴ����¼� */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
    ADS_DBG_DL_ADQ_EMPTY_TMR_TIMEOUT_NUM(1);
    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_ConfigAdq
 ��������  : ����AD
 �������  : IPF_AD_TYPE_E                       enAdType
             VOS_UINT                            ulIpfAdNum
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 ADS_DL_ConfigAdq(
    IPF_AD_TYPE_E                       enAdType,
    VOS_UINT                            ulIpfAdNum
)
{
    IPF_AD_DESC_S                      *pstAdDesc = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc  = VOS_NULL_PTR;
    VOS_UINT32                          ulPoolId;
    VOS_UINT32                          ulTmp;
    VOS_UINT32                          ulCnt;
    VOS_UINT32                          ulLen;
    VOS_INT32                           lRslt;

    if (IPF_AD_0 == enAdType)
    {
        ulPoolId = ADS_IPF_MEM_POOL_ID_AD0;
        ulLen    = ADS_IPF_AD0_MEM_BLK_SIZE;
    }
    else
    {
        ulPoolId = ADS_IPF_MEM_POOL_ID_AD1;
        ulLen    = ADS_IPF_AD1_MEM_BLK_SIZE;
    }

    for (ulCnt = 0; ulCnt < ulIpfAdNum; ulCnt++)
    {
        pstImmZc = ADS_IPF_AllocMem(ulPoolId, ulLen, IMM_MAC_HEADER_RES_LEN);
        if (VOS_NULL_PTR == pstImmZc)
        {
            ADS_DBG_DL_ADQ_ALLOC_MEM_FAIL_NUM(1);
            break;
        }

        ADS_DBG_DL_ADQ_ALLOC_MEM_SUCC_NUM(1);

        /* ��дAD������: OUTPUT0 ---> Ŀ�ĵ�ַ; OUTPUT1 ---> SKBUFF */
        pstAdDesc = ADS_DL_GET_IPF_AD_DESC_PTR(enAdType, ulCnt);
        pstAdDesc->u32OutPtr0 = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZc->data);
        pstAdDesc->u32OutPtr1 = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZc);
    }

    if (0 == ulCnt)
    {
        return 0;
    }

    /* ���뵽AD����Ҫ����ADQ */
    lRslt = mdrv_ipf_config_dlad(enAdType, ulCnt, ADS_DL_GET_IPF_AD_DESC_PTR(enAdType, 0));
    if (IPF_SUCCESS != lRslt)
    {
        /* ����ʧ�ܣ��ͷ��ڴ� */
        ulTmp = ulCnt;
        for (ulCnt = 0; ulCnt < ulTmp; ulCnt++)
        {
            pstAdDesc = ADS_DL_GET_IPF_AD_DESC_PTR(enAdType, ulCnt);
            pstImmZc  = (IMM_ZC_STRU *)phys_to_virt(pstAdDesc->u32OutPtr1);
            IMM_ZcFree(pstImmZc);
            ADS_DBG_DL_ADQ_FREE_MEM_NUM(1);
        }

        ADS_DBG_DL_ADQ_CFG_IPF_FAIL_NUM(1);
        return 0;
    }

    /* ���ʵ�����õ�AD��Ŀ */
    ADS_DBG_DL_ADQ_CFG_AD_NUM(ulCnt);
    ADS_DBG_DL_ADQ_CFG_IPF_SUCC_NUM(1);
    return ulCnt;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_AllocMemForAdq
 ��������  : ����ADQ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��19��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��24��
    ��    ��   : A00165503
    �޸�����   : DTS2015042201072: �Ż�ADQ���жϴ���, ��ֹ�ڴ��޷���ʱ����

*****************************************************************************/
VOS_VOID ADS_DL_AllocMemForAdq(VOS_VOID)
{
    VOS_INT32                           lRslt;
    VOS_UINT32                          ulIpfAd0Num;
    VOS_UINT32                          ulIpfAd1Num;
    VOS_UINT32                          ulActAd0Num;
    VOS_UINT32                          ulActAd1Num;

    ulIpfAd0Num = 0;
    ulIpfAd1Num = 0;
    ulActAd0Num = 0;
    ulActAd1Num = 0;

    /* ��ȡ����ADQ�Ŀ��е�AD���� */
    lRslt = mdrv_ipf_get_dlad_num(&ulIpfAd0Num, &ulIpfAd1Num);
    if (IPF_SUCCESS != lRslt)
    {
        ADS_DBG_DL_ADQ_GET_FREE_AD_FAIL_NUM(1);
        return;
    }

    ADS_DBG_DL_ADQ_GET_FREE_AD_SUCC_NUM(1);

    /* �������ô��ڴ��ADQ1 */
    if (0 != ulIpfAd1Num)
    {
        ulActAd1Num = ADS_DL_ConfigAdq(IPF_AD_1, ulIpfAd1Num);
        ADS_DBG_DL_ADQ_CFG_AD1_NUM(ulActAd1Num);
    }

    /* ������С�ڴ��ADQ0 */
    if (0 != ulIpfAd0Num)
    {
        ulActAd0Num = ADS_DL_ConfigAdq(IPF_AD_0, ulIpfAd0Num);
        ADS_DBG_DL_ADQ_CFG_AD0_NUM(ulActAd0Num);
    }

    /* AD0Ϊ�ջ���AD1Ϊ����Ҫ����������ʱ�� */
    if ( ((0 == ulActAd0Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd0Num))
      || ((0 == ulActAd1Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd1Num)) )
    {
        /* �������ADQ�κ�һ���������벻���ڴ棬����ʱ�� */
        ADS_StartTimer(TI_ADS_DL_ADQ_EMPTY, TI_ADS_DL_ADQ_EMPTY_LEN);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_SendNdClientDataInd
 ��������  : RA����ECHO REQUEST�ȱ���ͨ��VOS����NDCLIENT
 �������  : VOS_VOID *pData
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_DL_SendNdClientDataInd(IMM_ZC_STRU *pstImmZc)
{
    ADS_NDCLIENT_DATA_IND_STRU         *pstMsg  = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;

    ulDataLen = IMM_ZcGetUsedLen(pstImmZc);

    /* ������Ϣ */
    pstMsg = (ADS_NDCLIENT_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + ulDataLen - 2);
    if (VOS_NULL_PTR == pstMsg)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: pstMsg is NULL!");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_NDCLIENT_DATA_IND_STRU) + ulDataLen - 2 - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    pstMsg->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstMsg->enMsgId       = ID_ADS_NDCLIENT_DATA_IND;
    pstMsg->enModemId     = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
    pstMsg->ucRabId       = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);;
    pstMsg->usLen         = (VOS_UINT16)ulDataLen;

    /* ������������ */
    pucData = IMM_ZcGetDataPtr(pstImmZc);
    PS_MEM_CPY(pstMsg->aucData, pucData, ulDataLen);

    /* ������Ϣ */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg);
    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_SendDhcpClientDataInd
 ��������  : DHCPv6����ͨ��VOS����DHCP CLIENT
 �������  : IMM_ZC_STRU *pstImmZc
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��18��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_DL_SendDhcpClientDataInd(IMM_ZC_STRU *pstImmZc)
{
    ADS_DHCP_DATA_IND_STRU             *pstMsg  = VOS_NULL_PTR;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulResult;

    ulDataLen = IMM_ZcGetUsedLen(pstImmZc);

    /* ������Ϣ */
    pstMsg = (ADS_DHCP_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_DHCP_DATA_IND_STRU) + ulDataLen - 2);

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstMsg )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendDhcpClientDataInd: pstMsg is NULL!");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_DHCP_DATA_IND_STRU) + ulDataLen - 2 - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    pstMsg->ulReceiverPid = UEPS_PID_DHCP;
    pstMsg->enMsgId       = ID_ADS_DHCP_DATA_IND;
    pstMsg->enModemId     = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
    pstMsg->ucRabId       = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);
    pstMsg->usLen         = (VOS_UINT16)ulDataLen;

    /* �������� */
    pucData = IMM_ZcGetDataPtr(pstImmZc);
    PS_MEM_CPY(pstMsg->aucData, pucData, ulDataLen);

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstMsg);
    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendDhcpClientDataInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_FreeIpfUsedAd0
 ��������  : �ͷ�IPF��ʹ�õ�AD0
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��18��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID ADS_DL_FreeIpfUsedAd0(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    /*lint -e813*/ /* added by zwx247453 for pc����ת3650, 2015-08-24, begin */
    IPF_AD_DESC_S                       astAdDesc[IPF_DLAD0_DESC_SIZE];
    /*lint +e813*/ /* added by zwx247453 for pc����ת3650, 2015-08-24, end */

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD0_DESC_SIZE));
    if (IPF_SUCCESS == mdrv_ipf_get_used_dlad(IPF_AD_0, (VOS_UINT32 *)&ulAdNum, astAdDesc))
    {
        /* �ͷ�ADQ0���ڴ� */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD0_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)phys_to_virt(astAdDesc[i].u32OutPtr1));
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_FreeIpfUsedAd1
 ��������  : �ͷ�IPF��ʹ�õ�AD1
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��18��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID ADS_DL_FreeIpfUsedAd1(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    /*lint -e813*/ /* added by zwx247453 for pc����ת3650, 2015-08-24, begin */
    IPF_AD_DESC_S                       astAdDesc[IPF_DLAD1_DESC_SIZE];
    /*lint +e813*/ /* added by zwx247453 for pc����ת3650, 2015-08-24, end */

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD1_DESC_SIZE));
    if (IPF_SUCCESS == mdrv_ipf_get_used_dlad(IPF_AD_1, (VOS_UINT32 *)&ulAdNum, astAdDesc))
    {
        /* �ͷ�ADQ1���ڴ� */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD1_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)phys_to_virt(astAdDesc[i].u32OutPtr1));
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_Xmit
 ��������  : �ַ����ݰ�, ����ÿ�������ϵ����һ�����������
 �������  : ucInstance --- modem ID
             ucRabId    --- RABID [5, 15]
             pstImmZc   --- IP buff
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��29��
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_DL_Xmit(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId,
    IMM_ZC_STRU                        *pstImmZc
)
{
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstLstImmZc    = VOS_NULL_PTR;
    VOS_UINT32                          ulExParam;
    VOS_UINT16                          usIpfResult;
    ADS_PKT_TYPE_ENUM_UINT8             enIpType;
    VOS_UINT8                           ucExRabId;

    /* ���MODEMID */
    if (!ADS_IS_MODEMID_VALID(ucInstance))
    {
        if (VOS_NULL_PTR != pstImmZc)
        {
            IMM_ZcFree(pstImmZc);
            ADS_DBG_DL_RMNET_MODEMID_ERR_NUM(1);
        }

        return;
    }

    /* ��ȡRABID��Ӧ���лص�����ָ�� */
    if (ADS_IS_RABID_VALID(ucRabId))
    {
        pRcvDlDataFunc = ADS_DL_GET_DATA_CALLBACK_FUNC(ucInstance, ucRabId);
        ulExParam      = ADS_DL_GET_DATA_EXPARAM(ucInstance, ucRabId);
    }
    else
    {
        if (VOS_NULL_PTR != pstImmZc)
        {
            IMM_ZcFree(pstImmZc);
            ADS_DBG_DL_RMNET_RABID_ERR_NUM(1);
        }

        return;
    }

    /* ��ȡ��������� */
    pstLstImmZc = ADS_DL_GET_LST_DATA_PTR(ucInstance, ucRabId);

    /* ������������ */
    if (VOS_NULL_PTR != pRcvDlDataFunc)
    {
        if (VOS_NULL_PTR != pstLstImmZc)
        {
            usIpfResult = ADS_DL_GET_IPF_RESULT_FORM_IMM(pstLstImmZc);
            enIpType    = ADS_DL_GET_IPTYPE_FROM_IPF_RESULT(usIpfResult);
            ucExRabId   = ADS_BUILD_EXRABID(ucInstance, ucRabId);

            (VOS_VOID)pRcvDlDataFunc(ucExRabId, pstLstImmZc, enIpType, ulExParam);
            ADS_DBG_DL_RMNET_TX_PKT_NUM(1);
        }

        ADS_DL_SET_LST_DATA_PTR(ucInstance, ucRabId, pstImmZc);
    }
    else
    {
        if (VOS_NULL_PTR != pstImmZc)
        {
            IMM_ZcFree(pstImmZc);
            ADS_DBG_DL_RMNET_NO_FUNC_FREE_PKT_NUM(1);
        }

        if (VOS_NULL_PTR != pstLstImmZc)
        {
            IMM_ZcFree(pstLstImmZc);
            ADS_DBG_DL_RMNET_NO_FUNC_FREE_PKT_NUM(1);
        }

        ADS_DL_SET_LST_DATA_PTR(ucInstance, ucRabId, VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_ProcTxData
 ��������  : ��������RD
 �������  : pstImmZc --- �ǿմ�����������, ��ָ�����Ҫ�������һ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��1��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_DL_ProcTxData(IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;

    if (VOS_NULL_PTR != pstImmZc)
    {
        ucInstance = ADS_DL_GET_MODEMID_FROM_IMM(pstImmZc);
        ucRabId    = ADS_DL_GET_RABID_FROM_IMM(pstImmZc);

        ADS_DL_Xmit(ucInstance, ucRabId, pstImmZc);
    }
    else
    {
        for (ucInstance = 0; ucInstance < ADS_INSTANCE_MAX_NUM; ucInstance++)
        {
            for (ucRabId = ADS_RAB_ID_MIN; ucRabId <= ADS_RAB_ID_MAX; ucRabId++)
            {
                ADS_DL_Xmit(ucInstance, ucRabId, VOS_NULL_PTR);
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RdDescTransImmMem
 ��������  : ��RD������ת����IMM�ڴ��ʽ, ���������������Ϣ
 �������  : pstRdDesc --- RD������
 �������  : ��
 �� �� ֵ  : IMM_ZC_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��06��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
IMM_ZC_STRU* ADS_DL_RdDescTransImmMem(const IPF_RD_DESC_S *pstRdDesc)
{
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                          ulCacheLen;

    /* ��OUTָ��ת��ΪIMM�ڴ�ָ�� */
    pstImmZc = (IMM_ZC_STRU *)phys_to_virt(pstRdDesc->u32OutPtr);
    if (VOS_NULL_PTR == pstImmZc)
    {
        return VOS_NULL_PTR;
    }

    /* ͳһˢCACHE */
    ulCacheLen = pstRdDesc->u16PktLen + IMM_MAC_HEADER_RES_LEN;
    ADS_IPF_DL_MEM_UNMAP(pstImmZc, ulCacheLen);

    /* ����������ʵ���� */
    IMM_ZcPut(pstImmZc, pstRdDesc->u16PktLen);

    /* ������������Ϣ: u16Result/u16UsrField1 */
    ADS_DL_SAVE_RD_DESC_TO_IMM(pstImmZc, pstRdDesc);

    return pstImmZc;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_ProcIpfResult
 ��������  : ADS����IPF�¼�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2012��4��12��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��4��24��
    ��    ��   : s62952
    �޸�����   : DTS2012040103554: D̬���帴λ, ����ι������

  3.��    ��   : 2012��5��4��
    ��    ��   : z60575
    �޸�����   : DTS2012050301768: IPFʧ��ʱ�ڴ�й¶

  4.��    ��   : 2012��5��24��
    ��    ��   : z60575
    �޸�����   : DTS2012052306799: ���ڹ��ǳ����ģ�����Ҫ�жϣ�����WatchDog���
                 �����Ѿ�����ά����ȫ�ֱ������˸�ֵ���жϺ�ʵ�ʾͲ�ι����ɾ���ж�

  5.��    ��   : 2012��11��19��
    ��    ��   : A00165503
    �޸�����   : DTS2012112206761: ����̬�����������

  6.��    ��   : 2013��12��11��
    ��    ��   : A00165503
    �޸�����   : DTS2013120905502: ������IPF����������ݰ�

  7.��    ��   : 2015��9��22��
    ��    ��   : A00165503
    �޸�����   : DTS2015081008249: ADS���������г���, ��ֹϵͳ��������

***************************************************************************/
VOS_VOID ADS_DL_ProcIpfResult(VOS_VOID)
{
    ADS_DL_IPF_RESULT_STRU             *pstIpfResult = VOS_NULL_PTR;
    IPF_RD_DESC_S                      *pstRdDesc = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                          ulRdNum = IPF_DLRD_DESC_SIZE;
    VOS_UINT32                          ulTxTimeout = 0;
    VOS_UINT32                          ulCacheLen;
    VOS_UINT32                          ulCnt;

    /*
    IPF_RD_DESC_S��u16Result����
    [15]Reserve
    [14]bd_cd_noeqBD��len��CD�ĳ��Ȳ��ȴ�����ʾ��0��ʾ����ƥ�䣬1��ʾ���Ȳ�ƥ��
    [13]pkt_parse_err���ݽ�������ָʾ��0��ʾ���ݽ���������1��ʾ���ݽ�������
    [12]bd_pkt_noeqBD��len��IP��ͷָʾ��len���ȴ���ָʾ��0��ʾ����ƥ�䣬1��ʾ���Ȳ�ƥ��
    [11]head_len_err IPV4���ȴ���ָʾ�źţ�IPV6����鳤�ȣ�0��ʾͷ������ȷ��1��ʾͷ���ȴ���
    [10]version_err�汾�Ŵ���ָʾ��0��ʾ�汾����4��6��1��ʾ�汾�Ų���4��6
    [9]ip_type IP�����ͣ�0��ʾIPV4��1��ʾIPV6
    [8]ff_type��Ƭ����һ����Ƭ�Ƿ�����ϲ�ͷָʾ��0��ʾ��Ƭ����һ����Ƭ�����ϲ�ͷ(IP��δ��ƬʱҲΪ0)
     1��ʾ��Ƭ����һ����Ƭ�����ϲ�ͷ
    [7:6]pf_type IP����Ƭָʾ���ͣ�00��ʾIP��δ��Ƭ��01��ʾIP����Ƭ����Ϊ��һ����Ƭ��
       02��ʾ��Ƭ����Ϊ���һ����Ƭ��03��ʾ��Ƭ����Ϊ�м��Ƭ
    [0:5]bear_id���غţ����Ϊ0x3F�������й�������ƥ��
    */

    /*
    IPF_RD_DESC_S��user field����
    u16UsrField1: RabId
    u32UsrField2: Ŀ��TTF_MEM_STָ��
    u32UsrField3: ԴTTF_MEM_STָ��
    */

    /* ��ȡRD */
    pstRdDesc = ADS_DL_GET_IPF_RD_DESC_PTR(0);
    mdrv_ipf_get_dlrd(&ulRdNum, pstRdDesc);

    /* ��ȡ��RDΪ0 */
    if (0 == ulRdNum)
    {
        /* ����RD��ȡ����Ϊ0��ͳ�Ƹ��� */
        ADS_DBG_DL_RDQ_GET_RD0_NUM(1);
        return;
    }


    /* ����RDͳ�Ƹ��� */
    ADS_DBG_DL_RDQ_RX_RD_NUM(ulRdNum);

    /* ������AD���ٴ���RD */
    ADS_DL_AllocMemForAdq();

    for (ulCnt = 0; ulCnt < ulRdNum; ulCnt++)
    {
        pstRdDesc = ADS_DL_GET_IPF_RD_DESC_PTR(ulCnt);

        /* ת��ΪIMM�ڴ� */
        pstImmZc = ADS_DL_RdDescTransImmMem(pstRdDesc);
        if (VOS_NULL_PTR == pstImmZc)
        {
            ADS_DBG_DL_RDQ_TRANS_MEM_FAIL_NUM(1);
            continue;
        }

        /* ͳ�������������յ��������ֽ���������������ѯ */
        ADS_RECV_DL_PERIOD_PKT_NUM(pstRdDesc->u16PktLen);

        /* ��ȡIPF RESULT */
        pstIpfResult = (ADS_DL_IPF_RESULT_STRU *)&(pstRdDesc->u16Result);

        /* BearId 0x3F: �����������ݰ���Ҫת����NDIS/PPP/RNIC*/
        if (CDS_ADS_DL_IPF_BEARER_ID_INVALID == pstIpfResult->usBearedId)
        {
            if (ADS_DL_IPF_RD_RSLT_IS_ERR_PKT(*((VOS_UINT16 *)pstIpfResult)))
            {
                ADS_DBG_DL_RDQ_RX_ERR_PKT_NUM(1);
            }

            ADS_MNTN_HookIpPkt(pstImmZc, ID_IPS_TRACE_ADS_DL,
                               pstRdDesc->u16UsrField1, pstRdDesc->u32UsrField2,
                               pstRdDesc->u32UsrField3, pstRdDesc->u16Result);

            ulTxTimeout = ADS_DL_TX_WAKE_LOCK_TMR_LEN;

            ADS_DL_ProcTxData(pstImmZc);
            ADS_DBG_DL_RDQ_RX_NORM_PKT_NUM(1);
        }
        else
        {
            /* ͳһˢCACHE */
            ulCacheLen = IMM_ZcGetUsedLen(pstImmZc) + IMM_MAC_HEADER_RES_LEN;
            ADS_IPF_SPE_MEM_UNMAP(pstImmZc, ulCacheLen);

            /* ƥ�����й��˹��������
             * BearId 19: NDClient������Ҫת����NDClient
             * BearId 17: DHCPv6������Ҫת����DHCP
             * [0, 15]����Ϊ�Ƿ����ݰ�;
             * [16, 18, 20, 21]Ŀǰֱ���ͷ�
             */
            if (CDS_ADS_DL_IPF_BEARER_ID_ICMPV6 == pstIpfResult->usBearedId)
            {
                ADS_DL_SendNdClientDataInd(pstImmZc);
                ADS_DBG_DL_RDQ_RX_ND_PKT_NUM(1);
            }
            else if (CDS_ADS_DL_IPF_BEARER_ID_DHCPV6 == pstIpfResult->usBearedId)
            {
                ADS_DL_SendDhcpClientDataInd(pstImmZc);
                ADS_DBG_DL_RDQ_RX_DHCP_PKT_NUM(1);
            }
            else
            {
                ADS_DBG_DL_RDQ_FILTER_ERR_PKT_NUM(1);
            }

            ADS_IPF_SPE_MEM_MAP(pstImmZc, ulCacheLen);
            IMM_ZcFree(pstImmZc);
        }
    }

    /* �������һ������ */
    ADS_DL_ProcTxData(VOS_NULL_PTR);

    ADS_DL_EnableTxWakeLockTimeout(ulTxTimeout);
    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_IsFcAssemTuneNeeded
 ��������  : ����Ƿ���Ҫ���������������
 �������  : ulRdNum   - ���ݰ�����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ����
             VOS_FALSE - ����Ҫ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��19��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 ADS_DL_IsFcAssemTuneNeeded(VOS_UINT32 ulRdNum)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemInfo;
    VOS_UINT32                          ulRslt = VOS_FALSE;

    /* ��ȡ������ֵ���� */
    pstFcAssemInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    if (0 != pstFcAssemInfo->ulEnableMask)
    {
        pstFcAssemInfo->ulRdCnt += ulRdNum;

        if (ADS_TIME_AFTER_EQ(ADS_GET_CURR_KERNEL_TIME(), (pstFcAssemInfo->ulTmrCnt + pstFcAssemInfo->ulExpireTmrLen)))
        {
            if (VOS_FALSE == pstFcAssemInfo->ulFcActiveFlg)
            {
                if (pstFcAssemInfo->ulRdCnt >= pstFcAssemInfo->ulRateUpLev)
                {
                    ADS_DBG_DL_FC_ACTIVATE_NUM(1);
                    pstFcAssemInfo->ulFcActiveFlg = VOS_TRUE;
                    ulRslt = VOS_TRUE;
                }
            }
            else
            {
                if (pstFcAssemInfo->ulRdCnt <= pstFcAssemInfo->ulRateDownLev)
                {
                    pstFcAssemInfo->ulFcActiveFlg = VOS_FALSE;
                }
            }

            ADS_DBG_DL_FC_TMR_TIMEOUT_NUM(1);
            pstFcAssemInfo->ulTmrCnt = ADS_GET_CURR_KERNEL_TIME();
            pstFcAssemInfo->ulRdCnt = 0;
        }
    }

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RegDrvAssemFunc
 ��������  : ��������ע�ắ��, ���ڽ������ͻ������, FC�޷���ʱ�������̲���,
             FC��ADSע�����صĻص�����, �Լ�����������ֵ����
 �������  : pstDrvAssemParam - ����������ֵ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��19��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID ADS_DL_RegDrvAssemFunc(FC_ADS_DRV_ASSEM_STRU *pstDrvAssemParam)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemParamInfo;

    pstFcAssemParamInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    pstFcAssemParamInfo->ulEnableMask     = pstDrvAssemParam->ucEnableMask;
    pstFcAssemParamInfo->ulRateUpLev      = pstDrvAssemParam->ulDlRateUpLev;
    pstFcAssemParamInfo->ulRateDownLev    = pstDrvAssemParam->ulDlRateDownLev;
    pstFcAssemParamInfo->ulExpireTmrLen   = pstDrvAssemParam->ulExpireTmrLen;
    pstFcAssemParamInfo->pFcAssemTuneFunc = pstDrvAssemParam->pDrvAssemFunc;

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RegDlDataCallback
 ��������  : ADS�������ݴ���ģ��Ϊ�ϲ�ģ���ṩ��ע���������ݽ��պ����ӿ�
 �������  : ucExRabId --- ��չRABID
             pFunc     --- ���ݽ��ջص�
             ulExParam --- ��չ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 ADS_DL_RegDlDataCallback(
    VOS_UINT8                           ucExRabId,
    RCV_DL_DATA_FUNC                    pFunc,
    VOS_UINT32                          ulExParam
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo = VOS_NULL_PTR;
    VOS_UINT8                           ucInstance;
    VOS_UINT8                           ucRabId;

    /* ���MODEMID */
    ucInstance = ADS_GET_MODEMID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_MODEMID_VALID(ucInstance))
    {
        ADS_ERROR_LOG1(ACPU_PID_ADS_DL,
            "ADS_DL_RegDlDataCallback: ModemId is invalid! <ModemId>", ucInstance);
        return VOS_ERR;
    }

    /* ���RABID */
    ucRabId = ADS_GET_RABID_FROM_EXRABID(ucExRabId);
    if (!ADS_IS_RABID_VALID(ucRabId))
    {
        ADS_ERROR_LOG2(ACPU_PID_ADS_DL,
            "ADS_DL_RegDlDataCallback: RabId is invalid! <ModemId>,<RabId>", ucInstance, ucRabId);
        return VOS_ERR;
    }

    /* �����������ݻص����� */
    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstance, ucRabId);
    pstDlRabInfo->ucRabId           = ucRabId;
    pstDlRabInfo->ulExParam         = ulExParam;
    pstDlRabInfo->pRcvDlDataFunc    = pFunc;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RegFilterDataCallback
 ��������  : ADS�������ݴ���ģ��Ϊ�ϲ�ģ���ṩ��ע���������ݹ��˽��պ����ӿ�
 �������  : VOS_UINT8                           ucRabId
             ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr,
             RCV_DL_DATA_FUNC                    pFunc
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_DL_RegFilterDataCallback(
    VOS_UINT8                           ucRabId,
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr,
    RCV_DL_DATA_FUNC                    pFunc
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId�ĸ�2��bit��ʾmodem id*/
    ucInstanceIndex = ADS_GET_MODEMID_FROM_EXRABID(ucRabId);
    ucRealRabId     = ADS_GET_RABID_FROM_EXRABID(ucRabId);

    /* RabId�Ϸ��Լ�� */
    if (!ADS_IS_RABID_VALID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RegFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* ����ADS�������ݹ��˻ص����� */
    pstDlRabInfo->ucRabId               = ucRealRabId;
    pstDlRabInfo->pRcvDlFilterDataFunc  = pFunc;

    /* ������˵�ַ��Ϣ */
    ADS_FILTER_SaveIPAddrInfo(pstFilterIpAddr);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_DeregFilterDataCallback
 ��������  : ADS�������ݴ���ģ��Ϊ�ϲ�ģ���ṩ��ȥע���������ݹ��˽��պ����ӿ�
 �������  : VOS_UINT8                           ucRabId
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��04��
    ��    ��   : l00198894
    �޸�����   : Share-PDP��Ŀ��������
*****************************************************************************/
VOS_UINT32 ADS_DL_DeregFilterDataCallback(VOS_UINT8 ucRabId)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId�ĸ�2��bit��ʾmodem id*/
    ucInstanceIndex = ADS_GET_MODEMID_FROM_EXRABID(ucRabId);
    ucRealRabId     = ADS_GET_RABID_FROM_EXRABID(ucRabId);

    /* RabId�Ϸ��Լ�� */
    if (!ADS_IS_RABID_VALID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_DeregFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* ȥע��ADS�������ݹ��˻ص����� */
    pstDlRabInfo->pRcvDlFilterDataFunc  = VOS_NULL_PTR;

    /* ���������Ϣ */
    ADS_FILTER_Reset();

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RcvTafPdpStatusInd
 ��������  : ����ID_APS_ADS_PDP_STATUS_IND��Ϣ
 �������  : MsgBlock *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��4��12��
    ��    ��   : A00165503
    �޸�����   : DTS2012020708222: ADS�����Ż�
  3.��    ��   : 2012��11��24��
    ��    ��   : l60609
    �޸�����   : DSDA Phase II:˫ʵ��
  4.��    ��   : 2016��8��16��
    ��    ��   : l00373346
    �޸�����   : DTS2016081611130: VT��Ƶ�޻���
*****************************************************************************/
VOS_UINT32 ADS_DL_RcvTafPdpStatusInd(MsgBlock *pMsg)
{
    ADS_PDP_STATUS_IND_STRU            *pstPdpStatusInd;
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;

    pstPdpStatusInd = (ADS_PDP_STATUS_IND_STRU *)pMsg;

    enPktType       = ADS_CDS_IPF_PKT_TYPE_IP;
    ucInstanceIndex = (VOS_UINT8)(pstPdpStatusInd->enModemId);

    /* RabId�Ϸ��Լ�� */
    if (!ADS_IS_RABID_VALID(pstPdpStatusInd->ucRabId))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_RcvTafPdpStatusInd: Rab Id is invalid");
        return VOS_ERR;
    }

    if (ADS_PDP_PPP == pstPdpStatusInd->enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, pstPdpStatusInd->ucRabId);

    /* PDP���� */
    if (ADS_PDP_STATUS_ACT == pstPdpStatusInd->enPdpStatus)
    {
        /* ����ADS�������ݻص���RABID */
        pstDlRabInfo->ucRabId           = pstPdpStatusInd->ucRabId;
        pstDlRabInfo->enPktType         = enPktType;
    }
    /* PDPȥ����  */
    else if (ADS_PDP_STATUS_DEACT == pstPdpStatusInd->enPdpStatus)
    {
        /* ���ADS�������ݻص����� */
        pstDlRabInfo->ucRabId           = ADS_RAB_ID_INVALID;
        pstDlRabInfo->enPktType         = ADS_CDS_IPF_PKT_TYPE_IP;
        pstDlRabInfo->ulExParam         = 0;

        if (ADS_CLEAN_RCV_CB_FUNC_TURE == pstPdpStatusInd->enCleanRcvCbFlag)
        {
            pstDlRabInfo->pRcvDlDataFunc    = VOS_NULL_PTR;
        }
        else
        {
            ADS_NORMAL_LOG(ACPU_PID_ADS_DL, "ADS_DL_RcvTafPdpStatusInd: Not clean ADS DL data call back func");
        }
    }
    else
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_RcvTafPdpStatusInd: Pdp Status is invalid");
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RcvCcpuResetStartInd
 ��������  : ADS_DL�յ�ADS_DL��ϢID_CCPU_ADS_DL_START_RESET_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��9��1��
    ��    ��   : A00165503
    �޸�����   : DTS2015082300106: ���й�С��, A�˴���C�˵�����λ����������

  3.��    ��   : 2015��9��22��
    ��    ��   : A00165503
    �޸�����   : DTS2015081008249: ADS���������г���, ��ֹϵͳ��������

*****************************************************************************/
VOS_UINT32 ADS_DL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;

    ADS_TRACE_HIGH("proc reset msg: enter.\n");

    /* ֹͣ���������Ķ�ʱ�� */
    for (ucIndex = 0; ucIndex < ADS_MAX_TIMER_NUM; ucIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_DL, ucIndex, ADS_TIMER_STOP_CAUSE_USER);
    }

    /* �������������� */
    ADS_ResetDlCtx();

    /* �ͷ�IPF��AD */
    ADS_DL_FreeIpfUsedAd1();
    ADS_DL_FreeIpfUsedAd0();

    /* �ͷ��ź�����ʹ�õ���API����������� */
    VOS_SmV(ADS_GetDLResetSem());

    ADS_TRACE_HIGH("proc reset msg: leave.\n");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RcvCcpuResetEndInd
 ��������  : ADS_DL�յ�ADS_DL��ϢID_CCPU_ADS_DL_RESET_END_IND�Ĵ���
 �������  : pMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32:VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��09��10��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

  2.��    ��   : 2015��9��1��
    ��    ��   : A00165503
    �޸�����   : DTS2015082300106: ���й�С��, A�˴���C�˵�����λ����������
*****************************************************************************/
VOS_UINT32 ADS_DL_RcvCcpuResetEndInd(
    MsgBlock                           *pstMsg
)
{
    ADS_TRACE_HIGH("proc reset msg: enter.\n");

    /* ���õ�����Ϣ */
    ADS_ResetDebugInfo();

    /* ��λIPF */
    mdrv_ipf_reinit_dlreg();

    /* ���³�ʼ��ADQ */
    ADS_DL_AllocMemForAdq();

    ADS_TRACE_HIGH("proc reset msg: leave.\n");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RcvTafMsg
 ��������  : ��������TAF����Ϣ
 �������  : MsgBlock *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���
 2.��    ��   : 2014��02��14��
   ��    ��   : m00217266
   �޸�����   : pdp status ind ��Ϊtaf aps����
*****************************************************************************/
VOS_UINT32 ADS_DL_RcvTafMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_APS_ADS_PDP_STATUS_IND:
            ADS_DL_RcvTafPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RcvCdsMsg
 ��������  : ��������CDS����Ϣ
             ��ʱû��Ҫ�������Ϣ��Ԥ�����ں�����չ
 �������  : MsgBlock *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 ADS_DL_RcvCdsMsg(MsgBlock *pMsg)
{
    /* ��ʱû��Ҫ�������Ϣ������յ���Ϣ�����д��� */
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_RcvAdsDlMsg
 ��������  : ��������ADS DL����Ϣ
 �������  : MsgBlock *pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��04��15��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 ADS_DL_RcvAdsDlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_ADS_CCPU_RESET_START_IND:
            ADS_DL_RcvCcpuResetStartInd(pMsg);
            break;

        case ID_ADS_CCPU_RESET_END_IND:
            ADS_DL_RcvCcpuResetEndInd(pMsg);
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RcvAdsDlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_ProcMsg
 ��������  : ADS������Ϣ������
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��6��
    ��    ��   : ³��/l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��4��15��
    ��    ��   : f00179208
    �޸�����   : C�˵�����λ��Ŀ
  3.��    ��   : 2014��02��14��
    ��    ��   : m00217266
    �޸�����   : pdp status ind ��Ϊtaf aps����
  4.��    ��   : 2015��6��25��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_VOID ADS_DL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* ��Ϣ�ķַ����� */
    switch ( pMsg->ulSenderPid )
    {
        /* ����APS����Ϣ */
        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            ADS_DL_RcvTafMsg(pMsg);
            return;

        /* ����CDS����Ϣ */
        case UEPS_PID_CDS:
            ADS_DL_RcvCdsMsg(pMsg);
            return;

        /* ����ADS DL����Ϣ */
        case ACPU_PID_ADS_DL:
            ADS_DL_RcvAdsDlMsg(pMsg);
            return;

        default:
            return;
    }
}





