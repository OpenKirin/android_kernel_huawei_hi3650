

/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "RnicEntity.h"
#include "RnicDebug.h"
#include "RnicCtx.h"
#include "RnicDev.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/

#define THIS_FILE_ID PS_FILE_ID_RNIC_DEV_C

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/

/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/
/* �������Ĳ������о�̬ӳ�� */
    static const struct net_device_ops rnic_ops = {
           .ndo_stop                = RNIC_StopNetCard,
           .ndo_open                = RNIC_OpenNetCard,
           .ndo_start_xmit          = RNIC_StartXmit,
           .ndo_set_mac_address     = RNIC_SetMacAddress,
           .ndo_change_mtu          = RNIC_ChangeMtu,
           .ndo_tx_timeout          = RNIC_ProcTxTimeout,
           .ndo_do_ioctl            = RNIC_Ioctrl,
           .ndo_get_stats           = RNIC_GetNetCardStats,
    };

#define RNIC_DEV_NAME_PREFIX            "rmnet"
const RNIC_NETCARD_ELEMENT_TAB_STRU           g_astRnicManageTbl[RNIC_NET_ID_MAX_NUM] =
{
    {
      "0",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x06}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x01}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x06}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x01}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_0, {0, 0, 0, 0, 0}},

    { "1",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x07}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x02}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x07}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x02}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_1, {0, 0, 0, 0, 0}},

    { "2",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x08}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x03}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x08}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x03}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_2, {0, 0, 0, 0, 0}},

    { "3",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x09}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x04}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x09}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x04}, 0xDD86, {0, 0}},
      MODEM_ID_1, RNIC_RMNET_ID_3, {0, 0, 0, 0, 0}},

    { "4",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0a}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x05}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0a}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x05}, 0xDD86, {0, 0}},
      MODEM_ID_1, RNIC_RMNET_ID_4, {0, 0, 0, 0, 0}},

    { "5",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0b}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x06}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0b}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x06}, 0xDD86, {0, 0}},
      MODEM_ID_2, RNIC_RMNET_ID_5, {0, 0, 0, 0, 0}},

    { "6",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0c}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x07}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0c}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x07}, 0xDD86, {0, 0}},
      MODEM_ID_2, RNIC_RMNET_ID_6, {0, 0, 0, 0, 0}},


    {
      "_ims",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0d}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x08}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0d}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x08}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_VT, {0, 0, 0, 0, 0}},

    {
      "_vowifi",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0e}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x09}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0e}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x09}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_VOWIFI, {0, 0, 0, 0, 0}},

    {
      "_ims1",
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0f}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0a}, 0x0008, {0, 0}},
      {{0x58, 0x02, 0x03, 0x04, 0x05, 0x0f}, {0x00, 0x11, 0x09, 0x64, 0x01, 0x0a}, 0xDD86, {0, 0}},
      MODEM_ID_0, RNIC_RMNET_ID_IMS1, {0, 0, 0, 0, 0}},

};


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*****************************************************************************
 �� �� ��  : RNIC_StopNetCard
 ��������  : RNIC���ر�ʱ�Ĵ���
 �������  : pstNetDev:�����豸ָ��
 �������  : ��
 �� �� ֵ  : VOS_INT:RNIC_OK, RNIC_ERROR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT RNIC_StopNetCard(
    struct net_device                  *pstNetDev
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    /* ��ȡ����˽������ */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    /* ʹ��netif_stop_queue()ֹͣ�����������շ� */
    netif_stop_queue(pstNetDev);

    /* ��˽�������е�����״̬��־��Ϊ�ر� */
    pstPriv->enStatus = RNIC_NETCARD_STATUS_CLOSED;

    return 0;
}

/*****************************************************************************
 �� �� ��  : RNIC_OpenNetCard
 ��������  : RNIC����ʱ�Ĵ���
 �������  : pstNetDev:�����豸ָ��
 �������  : ��
 �� �� ֵ  : VOS_INT:RNIC_OK, RNIC_ERR, RNIC_BUSY
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT RNIC_OpenNetCard(
    struct net_device                  *pstNetDev
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    /* ��ȡ����˽������ */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    /* ���������������� */
    netif_start_queue(pstNetDev);

    /* ��˽�������е�����״̬��־��Ϊ�� */
    pstPriv->enStatus = RNIC_NETCARD_STATUS_OPENED;

    return 0;
}

/*****************************************************************************
 �� �� ��  : RNIC_StartXmit
 ��������  : RNIC��������ʱ�Ĵ������
 �������  : pstSkb   :SKBUF�����׵�ַ
             pstNetDev:�����豸ָ��
 �������  : ��
 �� �� ֵ  : netdev_tx_t:NETDEV_TX_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��5��31��
   ��    ��   : A00165503
   �޸�����   : DTS2012053004651: PSҵ���ж���, ����A�������ڴ�ľ�, ����
                192.168.1.1 ping��ͨ
 3.��    ��   : 2012��6��20��
   ��    ��   : A00165503
   �޸�����   : DTS2012061904440: �����û���ʱ��ͳ��
 4.��    ��   : 2012��8��30��
   ��    ��   : l60609
   �޸�����   : AP������Ŀ�����ж���������Ƿ�Ϊ�գ����ж������Ƿ���Ч
 5.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
netdev_tx_t RNIC_StartXmit(
    struct sk_buff                     *pstSkb,
    struct net_device                  *pstNetDev
)
{
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;

    pstPriv     = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    pstNetCntxt = RNIC_GetNetCntxtByRmNetId(pstPriv->enRmNetId);
    if (VOS_NULL_PTR == pstNetCntxt)
    {
        IMM_ZcFree(pstSkb);
        RNIC_DBG_NET_TX_RMNETID_ERR_NUM(1);
        return NETDEV_TX_OK;
    }

    /* ��MODEM���ͷַ��������� */
    RNIC_ProcessTxDataByModemType(pstNetCntxt, pstSkb);

    return NETDEV_TX_OK;
}

/*****************************************************************************
 �� �� ��  : RNIC_SetMacAddress
 ��������  : RNIC����������MAC��ַ�Ĵ���
 �������  : pstNetDev:�����豸ָ��
             pMacAddr :MAC��ַ
 �������  : ��
 �� �� ֵ  : VOS_INT:RNIC_OK, RNIC_ADDR_INVALID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT RNIC_SetMacAddress(
    struct net_device                  *pstNetDev,
    VOS_VOID                           *pMacAddr
)
{
    struct sockaddr                    *pstAddr;
    VOS_INT                             lValid;

    /* ����ת�� */
    pstAddr = (struct sockaddr *)pMacAddr;

    /* MAC��ַΪ��Чֵ */
    lValid = is_valid_ether_addr((VOS_UINT8 *)pstAddr->sa_data);
    if (VOS_FALSE == lValid)
    {
        RNIC_DEV_ERR_PRINTK("RNIC_SetMacAddress: Ether addr is invalid!");
        return -EINVAL;
    }

    /* ��MAC��ַ��ֵ������ */
    memcpy(pstNetDev->dev_addr, pstAddr->sa_data, pstNetDev->addr_len);

    return 0;
}

/*****************************************************************************
 �� �� ��  : RNIC_ChangeMtu
 ��������  : RNIC��������MTU��С
 �������  : pstNetDev:�����豸ָ��
             lNewMtu  :MTUֵ
 �������  : ��
 �� �� ֵ  : VOS_INT:RNIC_OK, RNIC_ERROR, RNIC_OUT_RANGE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���

  2.��    ��   : 2016��12��27��
    ��    ��   : A00165503
    �޸�����   : DTS2016121600573: ����VOWIFIר������
*****************************************************************************/
VOS_INT RNIC_ChangeMtu(
    struct net_device                  *pstNetDev,
    VOS_INT                             lNewMtu
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    /* new_mtu���Ȳ�����Ч��Χ�� */
    if ((RNIC_RMNET_ID_IMS1 != pstPriv->enRmNetId) && (lNewMtu > RNIC_MAX_PACKET))
    {
        RNIC_DEV_ERR_PRINTK("RNIC_ChangeMtu: Mtu out of range!");
        return -EINVAL;
    }

    /* ����mtu��ɸ�ֵ */
    pstNetDev->mtu = (VOS_UINT)lNewMtu;

    return 0;
}

/*****************************************************************************
 �� �� ��  : RNIC_Tx_Timeout
 ��������  : RNIC���ͳ�ʱ������,Ŀǰ��Ϊ������ַ��ͳ�ʱ���,�ݲ����κδ���
             �����Ժ���չʹ��
 �������  : pstNetDev:�����豸ָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RNIC_ProcTxTimeout(
    struct net_device                  *pstNetDev
)
{
    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_Ioctrl
 ��������  : RNIC��ioctrl����,Ŀǰû�������ioctrl,�����Ժ���չ
 �������  : pstNetDev:�����豸ָ��
             pstIfr   :�û�����
             lCmd     :��������
 �������  : ��
 �� �� ֵ  : ������֧��  RNIC_NOTSUPP
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_INT RNIC_Ioctrl(
    struct net_device                  *pstNetDev,
    struct ifreq                       *pstIfr,
    VOS_INT                             lCmd
)
{
    return -EOPNOTSUPP;
}

/*****************************************************************************
 �� �� ��  : RNIC_GetNetCardStats
 ��������  : ��ȡRNIC����ͳ����Ϣ
 �������  : pstNetDev:�����豸ָ��
 �������  : ��
 �� �� ֵ  : net_device_stats
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���
*****************************************************************************/
struct net_device_stats *RNIC_GetNetCardStats(
    struct net_device                  *pstNetDev
)

{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv = VOS_NULL_PTR;

    /* ��ȡ˽������ */
    pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);

    /* ���豸��ͳ����Ϣ���� */
    return &pstPriv->stStats;
}

/*****************************************************************************
 �� �� ��  : RNIC_DeInitNetCard
 ��������  : RNIC��ȥע�ᴦ��
 �������  : pNetDev:�����豸ָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��
*****************************************************************************/
VOS_VOID RNIC_DeinitNetCard(
    struct net_device                  *pstNetDev
)
{
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;

    /* ��ȡ����˽������ */
    pstPriv     = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstNetDev);
    pstNetCntxt = RNIC_GET_SPEC_NET_CTX(pstPriv->enRmNetId);

    /* �ر��ز� */
    netif_carrier_off(pstNetDev);

    /* ֹͣ������������ */
    netif_stop_queue(pstNetDev);

    /* ȥע�������豸 */
    unregister_netdev(pstNetDev);

    /* �ͷ������豸 */
    free_netdev(pstNetDev);

    /* ��������豸��Ϣ */
    pstNetCntxt->pstPriv = VOS_NULL_PTR;

    return;
}

/*****************************************************************************
 �� �� ��  : RNIC_InitNetCard
 ��������  : RNIC��������ʼ��ʱ���õĺ��������RNIC��ʼ����ش���
 �������  : ��
 �������  : VOS_VOID
 �� �� ֵ  : VOS_INT:RNIC_NOMEM, RNIC_STATE, RNIC_OK
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��12��06��
   ��    ��   : ����
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��11��23��
   ��    ��   : f00179208
   �޸�����   : DSDA Phase I: RNIC��ʵ��

  3.��    ��   : 2016��12��27��
    ��    ��   : A00165503
    �޸�����   : DTS2016121600573: ����VOWIFIר������
*****************************************************************************/
VOS_INT __init RNIC_InitNetCard(VOS_VOID)
{
    struct net_device                  *pstDev      = VOS_NULL_PTR;
    RNIC_NETCARD_DEV_INFO_STRU         *pstPriv     = VOS_NULL_PTR;
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt = VOS_NULL_PTR;
    VOS_INT                             lRegRst;
    VOS_UINT8                           ucIndex;

    printk("RNIC_InitNetCard: entry, %u", VOS_GetSlice());

    for (ucIndex = 0 ; ucIndex < RNIC_NET_ID_MAX_NUM ; ucIndex++)
    {
        /* ��ʼ������˽����Ϣ */
        pstNetCntxt = RNIC_GET_SPEC_NET_CTX(ucIndex);
        pstNetCntxt->pstPriv = VOS_NULL_PTR;

        /* ���������豸netdev��˽������ */
        /* alloc_etherdev����ӿڷ�����net_device�� RNIC_NETCARD_DEV_INFO_STRU�����ӿڵ��ڴ�
           RNIC_NETCARD_DEV_INFO_STRU�ṹ�ҽ���net_device�ĺ��� */
        pstDev = alloc_etherdev(sizeof(RNIC_NETCARD_DEV_INFO_STRU));
        if (VOS_NULL_PTR == pstDev)
        {
            RNIC_DEV_ERR_PRINTK("RNIC_InitNetCard: net ptr is Null!");
            continue;
        }

        /* ���豸����MAC��ַ,�Ժ���Ҫ��̶�ֵ */
        memcpy(pstDev->dev_addr, RNIC_GET_DST_MAC_ADDR(ucIndex), RNIC_MAC_ADDR_LEN);

        /* ����Ĭ�ϵ�MTUֵ */
        if (RNIC_RMNET_ID_VT == ucIndex)
        {
            pstDev->mtu = 1280;
        }
        else if (RNIC_RMNET_ID_IMS1 == ucIndex)
        {
            pstDev->mtu = 3000;
        }
        else
        {
            pstDev->mtu = RNIC_DEFAULT_MTU;
        }

        snprintf(pstDev->name, sizeof(pstDev->name),
            "%s%s",
            RNIC_DEV_NAME_PREFIX, g_astRnicManageTbl[ucIndex].pucRnicNetCardName);

        /* �����뵽��net_device�ṹ���豸ָ��ĺ�������и�ֵ */
        pstDev->netdev_ops = &rnic_ops;

        /* ����˽�����ݳ�ʼ�� */
        pstPriv = (RNIC_NETCARD_DEV_INFO_STRU *)netdev_priv(pstDev);
        pstPriv->pstDev    = pstDev;
        pstPriv->enRmNetId = ucIndex;

        /* �ر��ز� */
        netif_carrier_off(pstDev);

        /* ֹͣ������������ */
        netif_stop_queue(pstDev);

        /* ����register_netdev������Netcard����ע�� */
        lRegRst = register_netdev(pstDev);
        if (VOS_OK != lRegRst)
        {
            /* ע��ʧ���ͷŴ�����RNIC�豸 */
            RNIC_DEV_ERR_PRINTK("RNIC_InitNetCard:Register netdev failed!");
            free_netdev(pstDev);
            continue;
        }

        /* ��������˽������ */
        pstNetCntxt->pstPriv = pstPriv;

        /* ���ز� */
        netif_carrier_on(pstDev);

        /* ���������������� */
        netif_start_queue(pstDev);
    }

    printk("RNIC_InitNetCard: eixt, %u", VOS_GetSlice());

    return 0;
}

module_init(RNIC_InitNetCard);





