

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "RnicCtx.h"
#include "RnicEntity.h"
#include "PsCommonDef.h"
#include "AtRnicInterface.h"
#include "RnicProcMsg.h"
#include "RnicDemandDialFileIO.h"
#include "RnicLog.h"
#include "RnicDebug.h"




/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_RNIC_CTX_C
/*lint +e960*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* RNIC CTX,���ڱ���RNIC��ȫ�ֱ��� */
RNIC_CTX_STRU                           g_stRnicCtx;

extern RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];

extern VOS_UINT8                               g_ucRnicNetifRxType;


/*****************************************************************************
 �� �� ��  : RNIC_RnicCtxInit
 ��������  : ��ʼ��RNIC��CTX
 �������  : pstRnicCtx:RNIC�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��6��05��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406������Ͽ����������޸�
 3.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
 3.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : C�˵�����λ��Ŀ:��ʼ����λ�ź���
 4.��    ��   : 2013��07��222��
   ��    ��   : j00177245
   �޸�����   : �������warning
 5.��    ��   : 2014��02��14��
   ��    ��   : m00217266
   �޸�����   : ��ʼ��L-C��������Ŀ�����ӵ�ȫ�ֱ���
 6.��    ��   : 2014��6��3��
   ��    ��   : m00217266
   �޸�����   : DTS2014052902453
 7.��    ��   : 2015��07��31��
   ��    ��   : w00316404
   �޸�����   : DTS2015071401227
*****************************************************************************/
VOS_VOID RNIC_InitCtx(
    RNIC_CTX_STRU                      *pstRnicCtx
)
{
    VOS_UINT8                           ucIndex;

    PS_MEM_SET(g_astRnicStats, 0, sizeof(g_astRnicStats));

    /* Added by m00217266 for L-C��������Ŀ, 2014-2-19, begin */
    PS_MEM_SET((VOS_VOID *)&g_stRnicRmnetConfigCheckInfo, 0, sizeof(g_stRnicRmnetConfigCheckInfo));
    /* Added by m00217266 for L-C��������Ŀ, 2014-2-19, end */

    for (ucIndex = 0 ; ucIndex < RNIC_NET_ID_MAX_NUM ; ucIndex++)
    {
        /* ��ʼ��RNIC����ͳ�� */
        RNIC_ClearNetDsFlowStats(ucIndex);

        /* ��ʼ��RNIC PDP������ */
        RNIC_InitPdpCtx(&(pstRnicCtx->astSpecCtx[ucIndex].stPdpCtx), ucIndex);

        /* ��ʼ������״̬ */
        pstRnicCtx->astSpecCtx[ucIndex].enFlowCtrlStatus = RNIC_FLOW_CTRL_STATUS_STOP;

        /* ��ʼ��ģ��ID */
        /* ��ʼ����ʱ����Ѿ�ȷ��������������Ӧ�ĸ�MODEM */
        pstRnicCtx->astSpecCtx[ucIndex].enModemId        = RNIC_GET_MODEM_ID_BY_NET_ID(ucIndex);

        /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
        pstRnicCtx->astSpecCtx[ucIndex].enModemType      = RNIC_MODEM_TYPE_INSIDE;
        /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

        pstRnicCtx->astSpecCtx[ucIndex].enRmNetId        = ucIndex;
        pstRnicCtx->astSpecCtx[ucIndex].lSpePort         = RNIC_INVALID_SPE_PORT;
        pstRnicCtx->astSpecCtx[ucIndex].ulIpfPortFlg     = VOS_FALSE;

        pstRnicCtx->astSpecCtx[ucIndex].enRatType        = IMSA_RNIC_IMS_RAT_TYPE_BUTT;
    }

    /* ��ʼ��RABID��Ϣ */
    for (ucIndex = 0 ; ucIndex < RNIC_MODEM_ID_MAX_NUM ; ucIndex++)
    {
        RNIC_InitRabidInfo(&pstRnicCtx->astRabIdInfo[ucIndex]);
    }

    /* Added by m00217266 for L-C��������Ŀ, 2014-1-27, begin */
    /* ��ʼ��PDNID��Ϣ */
    RNIC_InitPdnIdInfo(&pstRnicCtx->stPdnIdInfo);
    /* Added by m00217266 for L-C��������Ŀ, 2014-1-27, end */

    /* ��ʼ��RNIC��ʱ�������� */
    RNIC_InitAllTimers(pstRnicCtx->astTimerCtx);

    /* ��ʼ������ģʽ��Ϣ */
    RNIC_InitDialMode(&(pstRnicCtx->stDialMode));

    /* ��ʼ�����ŶϿ���ʱ����ʱ��������ͳ�� */
    RNIC_ClearTiDialDownExpCount();

    RNIC_SetTimer4WakeFlg(VOS_FALSE);

    /* ��ʼ����λ�ź��� */
    RNIC_InitResetSem();

    /* ���ʹ��netif_rx�ں˺��������� */
    RNIC_GetRnicNetifRxType();

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitRabidInfo
 ��������  : ��ʼ��Rabid��Ӧ����Ϣ
 �������  : pstRabIdInfo:RabId��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��12��10��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitRabidInfo(
    RNIC_RABID_INFO_STAU               *pstRabIdInfo
)
{

    PS_MEM_SET(pstRabIdInfo->aucRmNetId,
               RNIC_RMNET_ID_BUTT,
               RNIC_RAB_ID_MAX_NUM);

    return;
}

/* Added by m00217266 for L-C��������Ŀ, 2014-2-8, begin */
/*****************************************************************************
 �� �� ��  : RNIC_InitPdnIdInfo
 ��������  : ��ʼ��Pdnid��Ӧ����Ϣ
 �������  : pstPdnIdInfo:PdnId��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��02��08��
   ��    ��   : m00217266
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitPdnIdInfo(
    RNIC_PDNID_INFO_STAU               *pstPdnIdInfo
)
{

    PS_MEM_SET(pstPdnIdInfo->aucRmNetId,
               RNIC_RMNET_ID_BUTT,
               RNIC_PDN_ID_MAX);

    return;
}
/* Added by m00217266 for L-C��������Ŀ, 2014-2-8, end */


/*****************************************************************************
 �� �� ��  : RNIC_InitPdpCtx
 ��������  : ��ʼ��ָ������PDP������
 �������  : pstPdpCtx:PDP�������׵�ַ
             ucRmNetId:����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_InitPdpCtx(
    RNIC_PDP_CTX_STRU                  *pstPdpCtx,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_InitIpv4PdpCtx(&(pstPdpCtx->stIpv4PdpInfo));
    RNIC_InitIpv6PdpCtx(&(pstPdpCtx->stIpv6PdpInfo));
    RNIC_InitIpv4v6PdpCtx(&(pstPdpCtx->stIpv4v6PdpInfo), ucRmNetId);

    IMM_ZcQueueHeadInit(&pstPdpCtx->stImsQue);

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ResetDialMode
 ��������  : ���ò���ģʽ��Ϣ
 �������  : pstDialMode:����ģʽ�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ResetDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
)
{
    pstDialMode->enDialMode             = RNIC_DIAL_MODE_MANUAL;
    pstDialMode->ulIdleTime             = RNIC_DIAL_DEMA_IDLE_TIME;
    pstDialMode->enEventReportFlag      = RNIC_FORBID_EVENT_REPORT;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitDialMode
 ��������  : ��ʼ������ģʽ��Ϣ
 �������  : pstDialMode:����ģʽ�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��1��31��
   ��    ��   : w00199382
   �޸�����   : ��ʼ��/proc/dial�µ��ļ�
*****************************************************************************/
VOS_VOID RNIC_InitDialMode(
    RNIC_DIAL_MODE_STRU                *pstDialMode
)
{
    VOS_UINT32                          ulRlst;

    pstDialMode->enDialMode             = RNIC_DIAL_MODE_MANUAL;
    pstDialMode->ulIdleTime             = RNIC_DIAL_DEMA_IDLE_TIME;
    pstDialMode->enEventReportFlag      = RNIC_FORBID_EVENT_REPORT;

    ulRlst                              = RNIC_InitDemandDialFile();

    if ( VOS_ERR == ulRlst)
    {
       RNIC_ERROR_LOG(ACPU_PID_RNIC, "RNIC_InitDialMode:RNIC_InitDemandDialFile ERR!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitIpv4PdpCtx
 ��������  : ��ʼ��IPV4 PDP������
 �������  : pstIpv4PdpCtx:IPV4 PDP�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��19��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitIpv4PdpCtx(
    RNIC_IPV4_PDP_INFO_STRU            *pstIpv4PdpCtx
)
{
    pstIpv4PdpCtx->enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstIpv4PdpCtx->ucRabId     = RNIC_RAB_ID_INVALID;
    pstIpv4PdpCtx->ucPdnId     = RNIC_PDN_ID_INVALID;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */
    pstIpv4PdpCtx->ulIpv4Addr  = 0;


    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitIpv6PdpCtx
 ��������  : ��ʼ��IPV6 PDP������
 �������  : pstIpv4PdpCtx:IPV6 PDP�������׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��19��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_InitIpv6PdpCtx(
    RNIC_IPV6_PDP_INFO_STRU            *pstIpv6PdpCtx
)
{
    pstIpv6PdpCtx->enRegStatus = RNIC_PDP_REG_STATUS_DEACTIVE;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstIpv6PdpCtx->ucRabId     = RNIC_RAB_ID_INVALID;
    pstIpv6PdpCtx->ucPdnId     = RNIC_PDN_ID_INVALID;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

    PS_MEM_SET(pstIpv6PdpCtx->aucIpv6Addr,
               0x00,
               RNIC_MAX_IPV6_ADDR_LEN);


    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitIpv4v6PdpCtx
 ��������  : ��ʼ��ָ������IPV4V6 PDP������
 �������  : pstIpv4v6PdpCtx:IPV4V6 PDP�������׵�ַ
             ucRmNetId:����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��19��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_InitIpv4v6PdpCtx(
    RNIC_IPV4V6_PDP_INFO_STRU          *pstIpv4v6PdpCtx,
    VOS_UINT8                           ucRmNetId
)
{
    RNIC_PDP_CTX_STRU                  *pstPdpAddr;

    /* ��ȡPDP�����ĵ�ַ */
    pstPdpAddr                              = RNIC_GetPdpCtxAddr(ucRmNetId);

    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, begin */
    pstIpv4v6PdpCtx->enRegStatus            = RNIC_PDP_REG_STATUS_DEACTIVE;
    pstIpv4v6PdpCtx->ucRabId                = RNIC_RAB_ID_INVALID;
    pstIpv4v6PdpCtx->ucPdnId                = RNIC_PDN_ID_INVALID;
    /* Modified by l60609 for L-C��������Ŀ, 2014-1-14, end */

    pstPdpAddr->stIpv4PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;
    pstPdpAddr->stIpv6PdpInfo.ucRabId       = RNIC_RAB_ID_INVALID;

    pstIpv4v6PdpCtx->ulIpv4Addr             = 0;

    PS_MEM_SET(pstIpv4v6PdpCtx->aucIpv6Addr,
               0x00,
               RNIC_MAX_IPV6_ADDR_LEN);


}

/*****************************************************************************
 �� �� ��  : RNIC_InitResetSem
 ��������  : ��ʼ��RNIC��λ���ź���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_InitResetSem(VOS_VOID)
{
    g_stRnicCtx.hResetSem  = VOS_NULL_PTR;

    /* ����������ź��� */
    if (VOS_OK != VOS_SmBCreate( "RNIC", 0, VOS_SEMA4_FIFO, &g_stRnicCtx.hResetSem))
    {
        PS_PRINTF("Create rnic acpu cnf sem failed!\r\n");
        RNIC_DBG_SET_SEM_INIT_FLAG(VOS_FALSE);
        RNIC_DBG_CREATE_BINARY_SEM_FAIL_NUM(1);

        return;
    }
    else
    {
        RNIC_DBG_SAVE_BINARY_SEM_ID(g_stRnicCtx.hResetSem);
    }

    RNIC_DBG_SET_SEM_INIT_FLAG(VOS_TRUE);

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetRnicNetifRxType
 ��������  : ��ʼ���Ƿ����ֻ���̬ȫ�ֱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��07��31��
   ��    ��   : w00316404
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_GetRnicNetifRxType(VOS_VOID)
{
    TAF_NV_RNIC_NETIF_RX_TYPE_STRU              stRnicNetifRxType;

    /* ��ȡNV�� */
    if (NV_OK != NV_Read(en_NV_Item_Rnic_Netif_Rx_Type,
                         &stRnicNetifRxType,
                         sizeof(TAF_NV_RNIC_NETIF_RX_TYPE_STRU)))
    {
        return;
    }

    RNIC_SET_NETIF_RX_TYPE(stRnicNetifRxType.ucRnicNetifRxType);

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ClearNetDsFlowStats
 ��������  : ��ʼ������ͳ����Ϣ
 �������  : enRmNetId --- RMNET ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ClearNetDsFlowStats(RNIC_RMNET_ID_ENUM_UINT8 enRmNetId)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;

    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(enRmNetId);

    pstNetCntxt->stDsFlowStats.ulCurrentRecvRate   = 0;
    pstNetCntxt->stDsFlowStats.ulPeriodRecvPktNum  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxLow  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalRecvFluxHigh = 0;

    pstNetCntxt->stDsFlowStats.ulCurrentSendRate   = 0;
    pstNetCntxt->stDsFlowStats.ulPeriodSendPktNum  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalSendFluxLow  = 0;
    pstNetCntxt->stDsFlowStats.ulTotalSendFluxHigh = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetRnicCtxAddr
 ��������  : ��ȡ��ǰRNIC��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰRNIC��CTX��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
RNIC_CTX_STRU* RNIC_GetRnicCtxAddr(VOS_VOID)
{
    return &(g_stRnicCtx);
}

/*****************************************************************************
 �� �� ��  : RNIC_GetRnicTiDialDownExpCount
 ��������  : ��ȡ����ģʽͳ�Ʋ��ŶϿ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����ģʽͳ�Ʋ��ŶϿ�������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_GetTiDialDownExpCount( VOS_VOID)
{
    return (g_stRnicCtx.ulTiDialDownExpCount);
}


/*****************************************************************************
 �� �� ��  : RNIC_TiDialDownExpCountPlusOne
 ��������  : �ۼӲ���ģʽͳ�Ʋ��ŶϿ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_IncTiDialDownExpCount( VOS_VOID)
{
    (g_stRnicCtx.ulTiDialDownExpCount)++;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ClearRnicTiDialDownExpCount
 ��������  : ����ģʽͳ�Ʋ��ŶϿ�����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ClearTiDialDownExpCount( VOS_VOID)
{
    g_stRnicCtx.ulTiDialDownExpCount = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetCurrentUlRate
 ��������  : ��ȡָ����������������
 �������  : ucRmNetId: ����ID
 �������  : ��
 �� �� ֵ  : ��ǰRNIC���ʵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_GetCurrentUlRate(VOS_UINT8 ucRmNetId)
{
    return (g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentSendRate);
}

/*****************************************************************************
 �� �� ��  : RNIC_SetCurrentUlRate
 ��������  : ����ָ����������������
 �������  : ulULDataRate:��������
             ucRmNetId: ����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��13��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_SetCurrentUlRate(
    VOS_UINT32                          ulULDataRate,
    VOS_UINT8                           ucRmNetId
)
{
    g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentSendRate = ulULDataRate;

    return;
}


/*****************************************************************************
 �� �� ��  : RNIC_GetCurrentDlRate
 ��������  : ��ȡָ����������������
 �������  : ucRmNetId: ����ID
 �������  : ��
 �� �� ֵ  : ��ǰRNIC���ʵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_UINT32 RNIC_GetCurrentDlRate(VOS_UINT8 ucRmNetId)
{
    return (g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentRecvRate);
}

/*****************************************************************************
 �� �� ��  : RNIC_SetCurrentDlRate
 ��������  : ����ָ����������������
 �������  : ulDLDataRate:��������
             ucRmNetId: ����ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_SetCurrentDlRate(
    VOS_UINT32                          ulDLDataRate,
    VOS_UINT8                           ucRmNetId
)
{
    g_stRnicCtx.astSpecCtx[ucRmNetId].stDsFlowStats.ulCurrentRecvRate = ulDLDataRate;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetDialModeAddr
 ��������  : ��ȡ���貦�ŵ�ģʽ�Լ�ʱ���ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���貦��ģʽ��ʱ���ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
RNIC_DIAL_MODE_STRU* RNIC_GetDialModeAddr(VOS_VOID)
{
    return &(g_stRnicCtx.stDialMode);
}

/*****************************************************************************
 �� �� ��  : RNIC_GetPdpCtxAddr
 ��������  : ��ȡRNICģ��ָ������PDP�����ĵĵ�ַ
 �������  : ucRmNetId -- ��������
 �������  : ��
 �� �� ֵ  : RNICģ��ָ������PDP�����ĵĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��07��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
RNIC_PDP_CTX_STRU* RNIC_GetPdpCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId].stPdpCtx);
}

/*****************************************************************************
 �� �� ��  : RNIC_GetTimerAddr
 ��������  : ��ȡRNIC CTXģ���ж�ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʱ�������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��12��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
RNIC_TIMER_CTX_STRU*  RNIC_GetTimerAddr( VOS_VOID )
{
    return g_stRnicCtx.astTimerCtx;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetTimer4WakeFlg
 ��������  : ��ȡRNIC CTXģ�����Ƿ�����Timer4���ѱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʱ�������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��5��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406, �����ɺ���

*****************************************************************************/
VOS_UINT32 RNIC_GetTimer4WakeFlg(VOS_VOID)
{
    return g_stRnicCtx.ulSetTimer4WakeFlg;
}

/*****************************************************************************
 �� �� ��  : RNIC_SetTimer4WakeFlg
 ��������  : ����RNIC CTXģ�����Ƿ�����Timer4���ѱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʱ�������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��6��5��
   ��    ��   : z60575
   �޸�����   : DTS2012060508406, �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_SetTimer4WakeFlg(VOS_UINT32 ulFlg)
{
    g_stRnicCtx.ulSetTimer4WakeFlg = ulFlg;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetSpecNetCardCtxAddr
 ��������  : ��ȡRNICָ��������������
 �������  : ucIndex -- ��������
 �������  : ��
 �� �� ֵ  : RNICָ�������������ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2012��11��24��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
RNIC_SPEC_CTX_STRU *RNIC_GetSpecNetCardCtxAddr(VOS_UINT8 ucRmNetId)
{
    return &(g_stRnicCtx.astSpecCtx[ucRmNetId]);
}

/*****************************************************************************
 �� �� ��  : RNIC_GetNetCntxtByRmNetId
 ��������  : ����RMNETID��ȡ����������ָ��
 �������  : enRmNetId --- RMNET ID
 �������  : ��
 �� �� ֵ  : RNIC_SPEC_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
RNIC_SPEC_CTX_STRU* RNIC_GetNetCntxtByRmNetId(RNIC_RMNET_ID_ENUM_UINT8 enRmNetId)
{
    if (enRmNetId >= RNIC_RMNET_ID_BUTT)
    {
        return VOS_NULL_PTR;
    }

    return RNIC_GET_SPEC_NET_CTX(enRmNetId);
}


/*****************************************************************************
 �� �� ��  : RNIC_GetResetSem
 ��������  : ��ȡRNIC��λ�ź���
 �������  : ��
 �������  : ��
 �� �� ֵ  : RNIC��λ�ź���
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��04��15��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_SEM RNIC_GetResetSem(VOS_VOID)
{
    return g_stRnicCtx.hResetSem;
}



