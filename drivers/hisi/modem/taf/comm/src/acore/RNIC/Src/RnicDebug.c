

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "RnicDebug.h"
#include "RnicCtx.h"


/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/


/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/

RNIC_MNTN_STATS_STRU                    g_stRnicMntnStats = {0};
RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];
RNIC_RMNET_CONFIG_CHECK_INFO_STRU       g_stRnicRmnetConfigCheckInfo;
VOS_UINT32                              g_ulRnicPrintUlDataFlg = VOS_FALSE;
VOS_UINT32                              g_ulRnicPrintDlDataFlg = VOS_FALSE;


/******************************************************************************
   5 ����ʵ��
******************************************************************************/

VOS_VOID RNIC_SetPrintUlDataFlg(VOS_UINT32 ulFlg)
{
    g_ulRnicPrintUlDataFlg = ulFlg;
}

/*****************************************************************************
 �� �� ��  : RNIC_ShowRnicPdpStats
 ��������  : ��ʾRNIC pdp����Ϣ
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��11��23��
      ��    ��   : f00179208
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ShowRnicPdpStats(VOS_UINT8 ucRmNetId)
{
    RNIC_PDP_CTX_STRU                  *pstPdpCtx;

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowRnicPdpStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    pstPdpCtx                           = RNIC_GetPdpCtxAddr(ucRmNetId);

    PS_PRINTF("RNIC %d IPV4 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV4 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV4 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucPdnId);
    PS_PRINTF("RNIC %d IPV4 PDP IPV4ADDR                   %d\n\n", ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ulIpv4Addr);

    PS_PRINTF("RNIC %d IPV6 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV6 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV6 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucPdnId);
    PS_PRINTF("RNIC %d IPV6 PDP IPV6ADDR                   %s\n\n", ucRmNetId, pstPdpCtx->stIpv6PdpInfo.aucIpv6Addr);

    PS_PRINTF("RNIC %d IPV4V6 PDP STATUS                   %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.enRegStatus);
    PS_PRINTF("RNIC %d IPV4V6 PDP RABID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucRabId);
    PS_PRINTF("RNIC %d IPV4V6 PDP PDNID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucPdnId);
    PS_PRINTF("RNIC %d IPV4V6 PDP IPV4ADDR                 %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ulIpv4Addr);
    PS_PRINTF("RNIC %d IPV4V6 PDP IPV6ADDR                 %s\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.aucIpv6Addr);
}

/*****************************************************************************
 �� �� ��  : RNIC_ShowUlProcStats
 ��������  : ��ʾRNIC����ͳ����Ϣ
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��01��12��
      ��    ��   : S62952
      �޸�����   : �����ɺ���
    2.��    ��   : 2012��11��23��
      ��    ��   : f00179208
      �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_ShowULProcStats(VOS_UINT8 ucRmNetId)
{
    PS_PRINTF("NET TX RMNETID ERR NUM                                 %d\n", g_stRnicMntnStats.ulNetTxRmNetIdErrNum);
    PS_PRINTF("SPE TX PORTID ERR NUM                                  %d\n", g_stRnicMntnStats.ulSpeTxPortIdErrNum);

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowUlProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* ����ͳ���� */
    PS_PRINTF("RNIC %d����״̬                                        %d\n", ucRmNetId, g_stRnicCtx.astSpecCtx[ucRmNetId].enFlowCtrlStatus);
    PS_PRINTF("RNIC %d�յ�����IPV4���ݵĸ���                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4PktNum);
    PS_PRINTF("RNIC %d�յ�����IPV6���ݵĸ���                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv6PktNum);
    PS_PRINTF("IPV4V6���ͼ���ʱRNIC %d�յ��������ݵĸ���IPV4IPV6      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4v6PktNum);
    PS_PRINTF("RNIC %dδ����ʱ�յ��������ݵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvUndiaPktNum);
    PS_PRINTF("RNIC %d���з��͸�ADS���ݵĸ���                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktNum);
    PS_PRINTF("RNIC %d��ADS������������ʧ�ܵĸ���                     %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktFailNum);
    PS_PRINTF("RNIC %dδ���Ϻ�ǰ�����յ�IPV4�㲥���ĸ���              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlIpv4BrdcstPktNum);
    PS_PRINTF("RNIC %d����ת��ΪIMM_ZCʧ�ܵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlImmzcFailPktNum);
    PS_PRINTF("RNIC %d����ȥ��MACͷʧ�ܵĸ���                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRmvMacHdrFailPktNum);
    PS_PRINTF("RNIC %d����˽�����ݴ��󶪵��������ݰ��ĸ���            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetCardDiscardNum);
    PS_PRINTF("RNIC %d����ID���󶪵��������ݰ��ĸ���                  %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetIdDiscardNum);
    PS_PRINTF("RNIC %dModem ID���󶪵��������ݰ��ĸ���                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlModemIdDiscardNum);
    PS_PRINTF("RNIC %d���ض����������ݰ��ĸ���                        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlFlowCtrlDiscardNum);
    PS_PRINTF("RNIC %d�յ��������ݰ��ĸ�����ipv4ipv6��                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvErrPktNum);
    PS_PRINTF("RNIC %d�ɹ��ϱ�APP���貦��                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpSucc);
    PS_PRINTF("RNIC %d�ϱ�APP���貦��ʧ��                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpFail);
    PS_PRINTF("RNIC %d�ɹ��ϱ�APP�Ͽ�����                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownSucc);
    PS_PRINTF("RNIC %d�ϱ�APP�Ͽ�����ʧ��                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownFail);

    if (RNIC_RMNET_ID_0 == ucRmNetId)
    {
        PS_PRINTF("����ģʽ                                           %d\n", g_stRnicCtx.stDialMode.enDialMode);
        PS_PRINTF("���貦���Ƿ��ϱ��¼�                               %d\n", g_stRnicCtx.stDialMode.enEventReportFlag);
        PS_PRINTF("���貦�ŶϿ�ʱ��                                   %d\n", g_stRnicCtx.stDialMode.ulIdleTime);
    }

    PS_PRINTF("RNIC %d RAB ID����RNIC���������ݰ�����                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRabIdErr);
    PS_PRINTF("RNIC %d PDN ID����RNIC���������ݰ�����                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlPdnIdErr);

    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ShowDLProcStats
 ��������  : ��ʾRNIC����ͳ����Ϣ
 �������  : ucRmNetId : ����ID
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��01��12��
      ��    ��   : S62952
      �޸�����   : �����ɺ���
    2.��    ��   : 2012��11��23��
      ��    ��   : f00179208
      �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_ShowDLProcStats(VOS_UINT8 ucRmNetId)
{
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        PS_PRINTF("RNIC_ShowDLProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* ����ͳ���� */
    PS_PRINTF("RNIC %d�յ�����IPV4���ݵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv4PktNum);
    PS_PRINTF("RNIC %d�յ�����IPV6���ݵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv6PktNum);
    PS_PRINTF("RNIC %d�����������ݵĸ���                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktNum);
    PS_PRINTF("RNIC %d������������ʧ�ܵĸ���                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktFailNum);
    PS_PRINTF("RNIC %d�յ��������ݰ�����MTU�ĸ���                 %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvBigPktNum);
    PS_PRINTF("RNIC %d����δ����������ݸ���                    %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlDiscardPktNum);
    PS_PRINTF("RNIC %d���м�MACͷʧ�ܵĸ���                       %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlAddMacHdFailNum);
    PS_PRINTF("RNIC %d����˽�����ݴ��󶪵��������ݰ��ĸ���        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetCardDiscardNum);
    PS_PRINTF("RNIC %d����ID���󶪵��������ݰ��ĸ���              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetIdDiscardNum);
    PS_PRINTF("RNIC %d�յ��������ݰ��ĸ�����ipv4ipv6��            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvErrPktNum);
    PS_PRINTF("\r\n");

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ShowResetStats
 ��������  : ��ʾRNIC�ź�����ʼ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2013��04��15��
      ��    ��   : f00179208
      �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ShowResetStats(VOS_VOID)
{
    PS_PRINTF("ģ���ʼ����ʶ                              %d\n", g_astRnicStats[0].ulSemInitFlg);
    PS_PRINTF("��ǰ�Ķ������ź���                          %p\n", g_stRnicCtx.hResetSem);
    PS_PRINTF("�����Ķ������ź���                          %p\n", g_astRnicStats[0].hBinarySemId);
    PS_PRINTF("�����������ź���ʧ�ܴ���                    %d\n", g_astRnicStats[0].ulCreateBinarySemFailNum);
    PS_PRINTF("���������ź���ʧ�ܴ���                      %d\n", g_astRnicStats[0].ulLockBinarySemFailNum);
    PS_PRINTF("���һ�����������ź���ʧ��ԭ��              %x\n", g_astRnicStats[0].ulLastBinarySemErrRslt);
    PS_PRINTF("��λ�ɹ��Ĵ���                              %d\n", g_astRnicStats[0].ulResetSucessNum);
}

/* Added by m00217266 for L-C��������Ŀ, 2014-2-19, begin */
/*****************************************************************************
 �� �� ��  : RNIC_Rmnet_Config_Check_Info
 ��������  : ��ӡ����������Ϣ����ʧ�ܵ�ͳ����Ϣ
 �������  : VOID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID RNIC_ShowRmnetConfigCheckInfo(VOS_VOID)
{
    PS_PRINTF("Totla req                           %d\n", g_stRnicRmnetConfigCheckInfo.ucTotlaCnt);
    PS_PRINTF("Modem type err                      %d\n", g_stRnicRmnetConfigCheckInfo.ucModemTypeErrCnt);
    PS_PRINTF("Rmnet id err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucRmNetIdErrCnt);
    PS_PRINTF("Modem ID err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucModemIdErrCnt);
    PS_PRINTF("Pdn ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucPdnIdErrCnt);
    PS_PRINTF("Rab ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucRabIdErrCnt);
    PS_PRINTF("Rmnet status err                    %d\n", g_stRnicRmnetConfigCheckInfo.ucRmnetStatusErrCnt);
    PS_PRINTF("IP type err                         %d\n", g_stRnicRmnetConfigCheckInfo.ucIpTypeErrCnt);
    PS_PRINTF("Send err                            %d\n", g_stRnicRmnetConfigCheckInfo.ucSendErrCnt);
    PS_PRINTF("Success                             %d\n", g_stRnicRmnetConfigCheckInfo.ucSuccCnt);
}
/* Added by m00217266 for L-C��������Ŀ, 2014-2-19, end */

/*****************************************************************************
 �� �� ��  : RNIC_Help
 ��������  : RNIC������Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ  :
    1.��    ��   : 2012��01��12��
      ��    ��   : S62952
      �޸�����   : �����ɺ���
    2.��    ��   : 2012��11��23��
      ��    ��   : f00179208
      �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_Help(VOS_VOID)
{

    PS_PRINTF("********************RNIC������Ϣ************************\n");
    PS_PRINTF("RNIC_ShowULProcStats  ucRmNetId                 ��ʾָ��RNIC��������ͳ����Ϣ\n");
    PS_PRINTF("RNIC_ShowDLProcStats  ucRmNetId                 ��ʾָ��RNIC��������ͳ����Ϣ\n");
    PS_PRINTF("RNIC_ShowRnicPdpStats ucRmNetId                 ��ʾָ��RNIC����PDP������Ϣ\n");
    PS_PRINTF("RNIC_ShowResetStats                             ��ʾָ��RNIC��λ״̬��Ϣ\n");

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_ShowDataFromIpStack
 ��������  : ��ӡ�յ�IPЭ��ջ������
 �������  : pstSkb   :SKBUF�����׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��04��25��
   ��    ��   : ����
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ShowDataFromIpStack(
    struct sk_buff                     *pstSkb
)
{
    VOS_UINT32                          i;

    PS_PRINTF("RNIC_ShowDataFromIpStack: data len is %d. \r\n", pstSkb->len);

    PS_PRINTF("RNIC_ShowDataFromIpStack: data content is: \r\n");

    for (i = 0; i < pstSkb->len; i++)
    {
        if (pstSkb->data[i] > 0xf)
        {
            PS_PRINTF("%x", pstSkb->data[i]);
        }
        else
        {
            PS_PRINTF("0%x", pstSkb->data[i]);
        }
    }

    PS_PRINTF("\r\n");

    return;
}




