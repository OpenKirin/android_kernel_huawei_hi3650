/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_arp_offload.c
  �� �� ��   : ����
  ��    ��   : w00316376
  ��������   : 2015��6��26��
  ����޸�   :
  ��������   : ARP Offloading��غ���ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��6��26��
    ��    ��   : w00316376
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "oal_net.h"
#include "oam_ext_if.h"

#include "wlan_mib.h"

#include "mac_frame.h"
#include "mac_data.h"

#include "dmac_arp_offload.h"
#include "dmac_tx_bss_comm.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_ARP_OFFLOAD_C


#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define DMAC_AO_UNKNOWN_TYPE        (oal_uint8)0xFF
oal_uint32  g_ul_arpoffload_send_arprsp  = 0;
oal_uint32  g_ul_arpoffload_drop_frame   = 0;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_ao_encap_ieee80211_header
 ��������  : ����802.11ͷ(����QOS�ͷ�QOS)
 �������  : dmac_vap_stru *pst_dmac_vap
             dmac_user_stru *pst_dmac_user
             mac_ieee80211_frame_stru *pst_rx_hdr
             oal_netbuf_stru *pst_tx_buf
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��29��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_ao_encap_ieee80211_header(dmac_vap_stru *pst_dmac_vap,
                                                     dmac_user_stru *pst_dmac_user,
                                                     mac_ieee80211_frame_stru *pst_rx_hdr,
                                                     oal_netbuf_stru *pst_tx_buf)
{
    mac_vap_stru                        *pst_mac_vap      = &pst_dmac_vap->st_vap_base_info;
    mac_user_stru                       *pst_mac_user     = &pst_dmac_user->st_user_base_info;
    oal_uint16                           us_tx_direction;
    mac_ieee80211_frame_stru            *pst_tx_hdr;

    pst_tx_hdr = (mac_ieee80211_frame_stru *)OAL_NETBUF_HEADER(pst_tx_buf);

    /* ���ͷ���From AP || To AP */
    us_tx_direction = (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode) ? WLAN_FRAME_FROM_AP : WLAN_FRAME_TO_AP;

    /* FC */
    *(oal_uint16 *)pst_tx_hdr = pst_mac_user->st_cap_info.bit_qos ? ((oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_QOS) | us_tx_direction)
                                : ((oal_uint16)(WLAN_PROTOCOL_VERSION | WLAN_FC0_TYPE_DATA | WLAN_FC0_SUBTYPE_DATA) | us_tx_direction);

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        /* Set Address1 field in the WLAN Header with BSSID */
        oal_set_mac_addr(pst_tx_hdr->auc_address1, pst_rx_hdr->auc_address2);

        /* Set Address2 field in the WLAN Header with the source address */
        oal_set_mac_addr(pst_tx_hdr->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

        /* Set Address3 field in the WLAN Header with the destination address */
        oal_set_mac_addr(pst_tx_hdr->auc_address3, pst_rx_hdr->auc_address3);
    }
    else if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /* Set Address1 field in the WLAN Header with destination address */
        oal_set_mac_addr(pst_tx_hdr->auc_address1, pst_rx_hdr->auc_address2);

        /* Set Address2 field in the WLAN Header with BSSID */
        oal_set_mac_addr(pst_tx_hdr->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

        /* Set Address3 field in the WLAN Header with the source address */
        oal_set_mac_addr(pst_tx_hdr->auc_address3, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    }

    pst_tx_hdr->bit_frag_num    = 0;

    if (OAL_TRUE == pst_mac_user->st_cap_info.bit_qos)
    {
        ((mac_ieee80211_qos_frame_stru *)pst_tx_hdr)->bit_qc_tid                    = WLAN_DATA_VIP_TID;
        ((mac_ieee80211_qos_frame_stru *)pst_tx_hdr)->bit_qc_eosp                   = 0;
        ((mac_ieee80211_qos_frame_stru *)pst_tx_hdr)->bit_qc_ack_polocy             = WLAN_TX_NORMAL_ACK;
        ((mac_ieee80211_qos_frame_stru *)pst_tx_hdr)->bit_qc_amsdu                  = OAL_FALSE;
        ((mac_ieee80211_qos_frame_stru *)pst_tx_hdr)->qos_control.bit_qc_txop_limit = 0;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_ao_encap_cb
 ��������  : ����CB�ֶ�
 �������  : dmac_vap_stru *pst_dmac_vap
             dmac_user_stru *pst_dmac_user
             oal_netbuf_stru *pst_tx_buf
             oal_uint16 us_payload_len
             oal_uint8 *puc_dst_mac_addr
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��29��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_ao_encap_cb(dmac_vap_stru *pst_dmac_vap,
                                       dmac_user_stru *pst_dmac_user,
                                       oal_netbuf_stru *pst_tx_buf,
                                       oal_uint16 us_payload_len,
                                       oal_uint8 *puc_dst_mac_addr)
{
    mac_vap_stru                        *pst_mac_vap  = &pst_dmac_vap->st_vap_base_info;
    mac_user_stru                       *pst_mac_user = &pst_dmac_user->st_user_base_info;
    mac_tx_ctl_stru                     *pst_tx_ctl;
    oal_uint16                           us_user_idx;

    pst_tx_ctl = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_tx_buf);
    OAL_MEMZERO(pst_tx_ctl, OAL_TX_CB_LEN);

    if (OAL_TRUE == pst_mac_user->st_cap_info.bit_qos)
    {
        mac_set_cb_is_qosdata(pst_tx_ctl, OAL_TRUE);
        MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl)    = MAC_80211_QOS_FRAME_LEN;
    }
    else
    {
        mac_set_cb_is_qosdata(pst_tx_ctl, OAL_FALSE);
        MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl)    = MAC_80211_FRAME_LEN;
    }

    MAC_GET_CB_MPDU_NUM(pst_tx_ctl)               = 1;
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctl)             = 1;
    MAC_GET_CB_IS_PROBE_DATA(pst_tx_ctl)          = DMAC_USER_ALG_NON_PROBE;
    MAC_GET_CB_TX_VAP_INDEX(pst_tx_ctl)           = pst_mac_vap->uc_vap_id;
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl)             = FRW_EVENT_TYPE_WLAN_DTX;
    MAC_GET_CB_IS_VIPFRAME(pst_tx_ctl)            = OAL_TRUE;
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)               = OAL_FALSE;
    MAC_GET_CB_IS_FIRST_MSDU(pst_tx_ctl)          = OAL_TRUE;
    MAC_GET_CB_IS_NEEDRETRY(pst_tx_ctl)           = OAL_TRUE;
    MAC_GET_CB_RETRIED_NUM(pst_tx_ctl)            = 0;
    MAC_GET_CB_IS_FROM_PS_QUEUE(pst_tx_ctl)       = OAL_FALSE;
    mac_set_cb_is_amsdu(pst_tx_ctl, OAL_FALSE);
    mac_set_cb_ack_policy(pst_tx_ctl, WLAN_TX_NORMAL_ACK);
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_VO);
    mac_set_cb_tid(pst_tx_ctl, WLAN_TIDNO_VOICE);
    MAC_GET_CB_MPDU_LEN(pst_tx_ctl) = us_payload_len;

    /* APUT �� STAUT user idx ��ȡ��ʽ��һ�� */
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        us_user_idx = (oal_uint8)(pst_mac_vap->uc_assoc_vap_id);
    }
    else if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        if (OAL_SUCC != mac_vap_find_user_by_macaddr(pst_mac_vap, puc_dst_mac_addr, &us_user_idx))
        {
            OAM_ERROR_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_encap_cb::Mac vap find user by mac address failed[%d], do not find user MAC[%02x:XX:XX:%02x:%02x:%02x]}",
                           puc_dst_mac_addr[0], puc_dst_mac_addr[3], puc_dst_mac_addr[4], puc_dst_mac_addr[5]);
            return OAL_FAIL;
        }
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_encap_cb::vap mode wrong not sta/ap[%d]",pst_mac_vap->en_vap_mode);
        return OAL_FAIL;
    }

    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl) = (oal_uint8)us_user_idx;
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_encap_arp_response
 ��������  : ����ARP respons����
 �������  : dmac_vap_stru *pst_dmac_vap
             mac_llc_snap_stru *pst_rx_snap
             oal_netbuf_stru *pst_tx_buf
             oal_uint8 *puc_tx_dst_ip_addr
             oal_uint8 *puc_tx_src_ip_addr
             oal_uint8 *puc_dst_mac_addr
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��29��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_ao_encap_arp_response(dmac_vap_stru *pst_dmac_vap,
                                               mac_llc_snap_stru *pst_rx_snap,
                                               oal_netbuf_stru *pst_tx_buf,
                                               oal_uint8 *puc_tx_dst_ip_addr,
                                               oal_uint8 *puc_tx_src_ip_addr,
                                               oal_uint8 *puc_dst_mac_addr)
{
    mac_vap_stru                        *pst_mac_vap   = &pst_dmac_vap->st_vap_base_info;
    mac_llc_snap_stru                   *pst_tx_snap;
    oal_eth_arphdr_stru                 *pst_tx_arp_hdr;

    /* ����SNAP header */
    pst_tx_snap = (mac_llc_snap_stru *)OAL_NETBUF_PAYLOAD(pst_tx_buf);
    oal_memcopy(pst_tx_snap, pst_rx_snap, OAL_SIZEOF(mac_llc_snap_stru));

    /* ����ARP header */
    pst_tx_arp_hdr = (oal_eth_arphdr_stru *)(pst_tx_snap + 1);

    /*lint -e572 */
    pst_tx_arp_hdr->us_ar_hrd = OAL_HOST2NET_SHORT(0x0001);
    pst_tx_arp_hdr->us_ar_pro = OAL_HOST2NET_SHORT(0x0800);

    pst_tx_arp_hdr->uc_ar_hln = 0x06;
    pst_tx_arp_hdr->uc_ar_pln = 0x04;

    pst_tx_arp_hdr->us_ar_op  = OAL_HOST2NET_SHORT(0x0002);
    /*lint +e572 */


    oal_set_mac_addr(pst_tx_arp_hdr->auc_ar_sha, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    oal_memcopy(pst_tx_arp_hdr->auc_ar_sip, puc_tx_src_ip_addr, OAL_IPV4_ADDR_SIZE);

    oal_set_mac_addr(pst_tx_arp_hdr->auc_ar_tha, puc_dst_mac_addr);
    oal_memcopy(pst_tx_arp_hdr->auc_ar_tip, puc_tx_dst_ip_addr, OAL_IPV4_ADDR_SIZE);
    return;
}

/*****************************************************************************
 �� �� ��  : dmac_ao_is_ipv4_addr_owner
 ��������  : ��ѯIPV4��ַ�Ƿ��ڱ��ش���
 �������  : dmac_vap_stru *pst_dmac_vap
             oal_uint8 *puc_ipv4_addr
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��7��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 dmac_ao_is_ipv4_addr_owner(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_ipv4_addr)
{
    oal_uint32 ul_loop;

    for (ul_loop = 0; ul_loop < DMAC_MAX_IPV4_ENTRIES; ul_loop++)
    {
        if (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv4_entry[ul_loop].auc_ip_addr, puc_ipv4_addr, OAL_IPV4_ADDR_SIZE))
        {
            return OAL_TRUE;
        }
    }
    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_ao_process_arp_offload
 ��������  : ARP���Ĵ�����
 �������  : dmac_vap_stru *pst_dmac_vap
             oal_netbuf_stru *pst_netbuf
 �������  : ��
 �� �� ֵ  : OAL_STATIC dmac_rx_frame_ctrl_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC dmac_rx_frame_ctrl_enum_uint8 dmac_ao_process_arp_offload(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_netbuf)
{
    mac_vap_stru                        *pst_mac_vap   = &pst_dmac_vap->st_vap_base_info;

    mac_ieee80211_frame_stru            *pst_rx_hdr;
    mac_llc_snap_stru                   *pst_rx_snap;
    oal_eth_arphdr_stru                 *pst_rx_arp_hdr;
    oal_netbuf_stru                     *pst_tx_buf;
    oal_uint8                           *puc_dst_mac_addr;

    pst_rx_snap = (mac_llc_snap_stru *)oal_netbuf_payload(pst_netbuf);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_rx_snap))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_arp_offload::Get netbuf snap payload failed.}");
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    pst_rx_arp_hdr = (oal_eth_arphdr_stru *)(pst_rx_snap + 1);
    /* 1.��ARP request����response�أ���ARP response��RARP�ϱ�Host */
    switch (pst_rx_arp_hdr->us_ar_op)
    {
        /*lint -e572 */
        case OAL_HOST2NET_SHORT(MAC_ARP_REQUEST):
            if (OAL_FALSE == dmac_ao_is_ipv4_addr_owner(pst_dmac_vap, pst_rx_arp_hdr->auc_ar_tip))
            {
                return (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode) ?
                    DMAC_RX_FRAME_CTRL_GOON : DMAC_RX_FRAME_CTRL_DROP ;
            }
            break;

        case OAL_HOST2NET_SHORT(MAC_ARP_RESPONSE):
        /*lint +e572 */
            if (OAL_FALSE == dmac_ao_is_ipv4_addr_owner(pst_dmac_vap, pst_rx_arp_hdr->auc_ar_tip))
            {
                return (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode) ?
                    DMAC_RX_FRAME_CTRL_GOON : DMAC_RX_FRAME_CTRL_DROP ;
            }
            return DMAC_RX_FRAME_CTRL_GOON;
        /* RARP */
        default:
            return DMAC_RX_FRAME_CTRL_GOON;
    }

    /* 2.����net_buff */
    pst_tx_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tx_buf))
    {
        /* DTS2015100700242 APUT device���ڴ治��ʱ����ӡ������ERROR�ĳ�WARNING */
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_arp_offload::Alloc MAC memory buf failed.}");
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    oal_set_netbuf_prev(pst_tx_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_tx_buf, OAL_PTR_NULL);

    /* 3.����80211ͷ */
    pst_rx_hdr = (mac_ieee80211_frame_stru *)OAL_NETBUF_HEADER(pst_netbuf);
    dmac_ao_encap_ieee80211_header(pst_dmac_vap, pst_dmac_user, pst_rx_hdr, pst_tx_buf);

    /* 4.����CB */
    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        puc_dst_mac_addr = pst_rx_hdr->auc_address2;
    }
    else
    {
        puc_dst_mac_addr = pst_rx_hdr->auc_address3;
    }

    if (OAL_SUCC != dmac_ao_encap_cb(pst_dmac_vap,
                                     pst_dmac_user,
                                     pst_tx_buf,
                                     OAL_SIZEOF(mac_llc_snap_stru) + OAL_SIZEOF(oal_eth_arphdr_stru),
                                     puc_dst_mac_addr))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_arp_offload::Construct cb failed.}");
        dmac_tx_excp_free_netbuf(pst_tx_buf);
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    /* 5.����ARP response���� */
    dmac_ao_encap_arp_response(pst_dmac_vap, pst_rx_snap, pst_tx_buf, pst_rx_arp_hdr->auc_ar_sip, pst_rx_arp_hdr->auc_ar_tip, puc_dst_mac_addr);

    /* 6.���� */
    if (OAL_SUCC != dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_tx_buf))
    {
	    /* DTS2015100600380 ��Ϊ�û��Ľ��ܶ���overrun������dmac_tx_process_data�ӿڷ���ʧ�ܡ�*/
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_arp_offload::Dmac tx process data failed.}");
        dmac_tx_excp_free_netbuf(pst_tx_buf);
        return DMAC_RX_FRAME_CTRL_GOON;
    }
    g_ul_arpoffload_send_arprsp++;
    return DMAC_RX_FRAME_CTRL_DROP;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_construct_na
 ��������  : ���첻ͨ��;��NA����
 �������  : dmac_vap_stru *pst_dmac_vap
             dmac_user_stru *pst_dmac_user
             oal_netbuf_stru *pst_netbuf
             mac_llc_snap_stru *pst_rx_snap
             oal_bool_enum_uint8 en_is_dad
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��29��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC dmac_rx_frame_ctrl_enum_uint8 dmac_ao_encap_na(dmac_vap_stru *pst_dmac_vap,
                                                          dmac_user_stru *pst_dmac_user,
                                                          oal_netbuf_stru *pst_netbuf,
                                                          mac_llc_snap_stru *pst_rx_snap)
{
    mac_vap_stru                        *pst_mac_vap = &pst_dmac_vap->st_vap_base_info;

    oal_netbuf_stru                     *pst_tx_buf;
    mac_llc_snap_stru                   *pst_tx_snap;
    oal_uint8                           *puc_dst_mac_addr;
    oal_uint16                           us_payload_len;
    oal_uint16                           us_nd_hrd_len;
    oal_bool_enum_uint8                  en_is_dad;

    mac_ieee80211_frame_stru            *pst_rx_hdr;
    oal_ipv6hdr_stru                    *pst_rx_ipv6_hdr;
    oal_ipv6hdr_stru                    *pst_tx_ipv6_hdr;

    oal_nd_msg_stru                     *pst_rx_nd_hdr;
    oal_nd_msg_stru                     *pst_tx_nd_hdr;

    oal_ipv6_pseudo_hdr_stru            *pst_tx_ipv6_pseudo_hdr;

    /* 1.����net_buff */
    pst_tx_buf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tx_buf))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_encap_na::Alloc memory buf failed.}");
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    oal_set_netbuf_prev(pst_tx_buf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_tx_buf, OAL_PTR_NULL);

    /* 2.����80211ͷ */
    pst_rx_hdr = (mac_ieee80211_frame_stru *)OAL_NETBUF_HEADER(pst_netbuf);
    dmac_ao_encap_ieee80211_header(pst_dmac_vap, pst_dmac_user, pst_rx_hdr, pst_tx_buf);

    /* 3.����CB */
    pst_rx_ipv6_hdr = (oal_ipv6hdr_stru *)(pst_rx_snap + 1);
    if (OAL_IPV6_IS_UNSPECIFIED_ADDR(pst_rx_ipv6_hdr->saddr.s6_addr))
    {
        /* �ظ���ַ���DAD��û��ѡ���ֶε� */
        en_is_dad = OAL_TRUE;
        us_nd_hrd_len = sizeof(oal_nd_msg_stru) - 4;
    }
    else
    {
        en_is_dad = OAL_FALSE;
        us_nd_hrd_len = sizeof(oal_nd_msg_stru) - 4 + 8;
    }

    us_payload_len = OAL_SIZEOF(mac_llc_snap_stru) + OAL_SIZEOF(oal_ipv6hdr_stru) + us_nd_hrd_len;

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        puc_dst_mac_addr = pst_rx_hdr->auc_address2;
    }
    else
    {
        puc_dst_mac_addr = pst_rx_hdr->auc_address3;
    }

    if (OAL_SUCC != dmac_ao_encap_cb(pst_dmac_vap,
                                                  pst_dmac_user,
                                                  pst_tx_buf,
                                                  us_payload_len,
                                                  puc_dst_mac_addr))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_encap_na::Create cb failed.}");
        dmac_tx_excp_free_netbuf(pst_tx_buf);
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    /* 4.����SNAP header */
    pst_tx_snap = (mac_llc_snap_stru *)OAL_NETBUF_PAYLOAD(pst_tx_buf);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tx_snap))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_encap_na::OAL_NETBUF_PAYLOAD failed.pst_tx_buf:%x}",pst_tx_buf);
        dmac_tx_excp_free_netbuf(pst_tx_buf);
        return DMAC_RX_FRAME_CTRL_GOON;
    }
    oal_memcopy(pst_tx_snap, pst_rx_snap, OAL_SIZEOF(mac_llc_snap_stru));

    /* 5.����ipv6 header */
    pst_tx_ipv6_hdr = (oal_ipv6hdr_stru *)(pst_tx_snap + 1);
    /*lint -e572 */
    *(oal_uint32 *)pst_tx_ipv6_hdr = OAL_HOST2NET_LONG(0x60000000);
    /*lint +e572 */
    pst_tx_ipv6_hdr->payload_len   = OAL_HOST2NET_SHORT(us_nd_hrd_len);
    pst_tx_ipv6_hdr->nexthdr       = OAL_IPPROTO_ICMPV6;
    pst_tx_ipv6_hdr->hop_limit     = 0xFF;

    pst_rx_nd_hdr   = (oal_nd_msg_stru *)(pst_rx_ipv6_hdr + 1);

    oal_memcopy(pst_tx_ipv6_hdr->saddr.s6_addr, pst_rx_nd_hdr->target.s6_addr, OAL_IPV6_ADDR_SIZE);
    if (OAL_FALSE == en_is_dad)
    {
        oal_memcopy(pst_tx_ipv6_hdr->daddr.s6_addr, pst_rx_ipv6_hdr->saddr.s6_addr, OAL_IPV6_ADDR_SIZE);
    }
    else
    {
        /* �ظ���ַ���DAD�����NA���ģ�Destination Address���������нڵ���鲥��ַ��FF02::1) */
        oal_memset(pst_tx_ipv6_hdr->daddr.s6_addr, 0, 16);
        pst_tx_ipv6_hdr->daddr.s6_addr[0]  = 0xFF;
        pst_tx_ipv6_hdr->daddr.s6_addr[1]  = 0x02;
        pst_tx_ipv6_hdr->daddr.s6_addr[15] = 0x01;
    }

    /* 6.��дICMPV6�ھӷ���Э���NA */
    pst_tx_nd_hdr = (oal_nd_msg_stru *)(pst_tx_ipv6_hdr + 1);
    OAL_MEMZERO(&(pst_tx_nd_hdr->icmph), OAL_SIZEOF(oal_icmp6hdr_stru));
    pst_tx_nd_hdr->icmph.icmp6_type      = MAC_ND_NADVT;
    pst_tx_nd_hdr->icmph.icmp6_code      = 0;
    if (OAL_FALSE == en_is_dad)
    {
        pst_tx_nd_hdr->icmph.icmp6_solicited = 1;
    }
    else
    {
        pst_tx_nd_hdr->icmph.icmp6_solicited = 0;
    }
    pst_tx_nd_hdr->icmph.icmp6_override = 1;
    oal_memcopy(pst_tx_nd_hdr->target.s6_addr, pst_rx_nd_hdr->target.s6_addr, OAL_IPV6_ADDR_SIZE); //NA��target�����NS��targetһ��

    if (OAL_FALSE == en_is_dad)
    {
        /* 7.��дICMPv6ѡ�� */
        /*lint -e415 */
        pst_tx_nd_hdr->opt[0] = OAL_ND_OPT_TARGET_LL_ADDR;
        pst_tx_nd_hdr->opt[1] = 1;   //The length of the option (including the type and length fields) in units of 8 octets.
        /*lint +e415 */

        /*lint -e416 */
        oal_memcopy(&(pst_tx_nd_hdr->opt[2]), pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID, OAL_MAC_ADDR_LEN);

        /* 8.��дIPv6α�ײ� */
        pst_tx_ipv6_pseudo_hdr = (oal_ipv6_pseudo_hdr_stru *)(&(pst_tx_nd_hdr->opt[2]) + OAL_MAC_ADDR_LEN);
        /*lint +e416 */
    }
    else
    {
        /* 7.DADû��ѡ���ֶ� */
        /* 8.��дIPv6α�ײ� */
        pst_tx_ipv6_pseudo_hdr = (oal_ipv6_pseudo_hdr_stru *)&(pst_tx_nd_hdr->opt[0]);
    }

    /*lint -e572 */
    pst_tx_ipv6_pseudo_hdr->payload_len = OAL_HOST2NET_LONG(us_nd_hrd_len);
    oal_memcopy(pst_tx_ipv6_pseudo_hdr->saddr.s6_addr, pst_tx_ipv6_hdr->saddr.s6_addr, OAL_IPV6_ADDR_SIZE);
    oal_memcopy(pst_tx_ipv6_pseudo_hdr->daddr.s6_addr, pst_tx_ipv6_hdr->daddr.s6_addr, OAL_IPV6_ADDR_SIZE);
    pst_tx_ipv6_pseudo_hdr->nexthdr = OAL_HOST2NET_LONG((oal_uint32)OAL_IPPROTO_ICMPV6);
    /*lint +e572 */

    /* 9.����У��� */
    pst_tx_nd_hdr->icmph.icmp6_cksum = oal_csum_ipv6_magic(us_nd_hrd_len + OAL_SIZEOF(oal_ipv6_pseudo_hdr_stru), (oal_uint8 *)pst_tx_nd_hdr);

    /* 10.���� */
    if (OAL_UNLIKELY(OAL_SUCC != dmac_tx_process_data(pst_dmac_vap->pst_hal_device, pst_dmac_vap, pst_tx_buf)))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_encap_na::Dmac tx data failed.}");
        dmac_tx_excp_free_netbuf(pst_tx_buf);
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    return DMAC_RX_FRAME_CTRL_DROP;
}

/*****************************************************************************
 �� �� ��  : dmac_ao_is_ipv6_addr_owner
 ��������  : ��ѯIPV6��ַ�Ƿ��ڱ��ش���
 �������  : dmac_vap_stru *pst_dmac_vap
             oal_uint8 *puc_ipv6_addr
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��7��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_ao_is_ipv6_addr_owner(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_ipv6_addr)
{
    oal_uint32  ul_loop;

    for (ul_loop = 0; ul_loop < DMAC_MAX_IPV6_ENTRIES; ul_loop++)
    {
        if (0 == oal_memcmp(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr, puc_ipv6_addr, OAL_IPV6_ADDR_SIZE))
        {
            return OAL_TRUE;
        }
    }
    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_ao_is_ipv6_global_ucst_exist
 ��������  : �ж�IPv6ȫ�򵥲���ַ�Ƿ����
 �������  : dmac_vap_stru *pst_dmac_vap
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_ao_is_ipv6_global_ucst_exist(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint32  ul_loop;

    for (ul_loop = 0; ul_loop < DMAC_MAX_IPV6_ENTRIES; ul_loop++)
    {
        if (!OAL_IPV6_IS_UNSPECIFIED_ADDR(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr)
            && !OAL_IPV6_IS_LINK_LOCAL_ADDR(pst_dmac_vap->pst_ip_addr_info->ast_ipv6_entry[ul_loop].auc_ip_addr))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_ao_process_nd_offload
 ��������  : ND���Ĵ�����
 �������  : dmac_vap_stru *pst_dmac_vap
             oal_netbuf_stru *pst_netbuf
 �������  : ��
 �� �� ֵ  : OAL_STATIC dmac_rx_frame_ctrl_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC dmac_rx_frame_ctrl_enum_uint8 dmac_ao_process_nd_offload(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_netbuf)
{
    mac_vap_stru                        *pst_mac_vap = &pst_dmac_vap->st_vap_base_info;

    mac_llc_snap_stru                   *pst_rx_snap;
    oal_ipv6hdr_stru                    *pst_rx_ipv6_hdr;
    oal_nd_msg_stru                     *pst_rx_nd_hdr;

    pst_rx_snap     = (mac_llc_snap_stru *)oal_netbuf_payload(pst_netbuf);
    pst_rx_ipv6_hdr = (oal_ipv6hdr_stru *)(pst_rx_snap + 1);
    pst_rx_nd_hdr   = (oal_nd_msg_stru *)(pst_rx_ipv6_hdr + 1);

    /* NDP�������ͱ��Ĺ��� */
    switch (pst_rx_nd_hdr->icmph.icmp6_type)
    {
        case MAC_ND_RSOL:
        {
            if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
            {
                return DMAC_RX_FRAME_CTRL_GOON;
            }

            return DMAC_RX_FRAME_CTRL_DROP;
        }

        case MAC_ND_RADVT:
        {
            if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
            {
                return DMAC_RX_FRAME_CTRL_GOON;
            }

            /* STAUT���IPv6��Destination Address���鲥��ַFF02::1�����Ѿ���ȡȫ�򵥲���ַ��������
               ����δ��ȡȫ�򵥲���ַ�����ϱ�host */
            if (OAL_IPV6_IS_MULTICAST(pst_rx_ipv6_hdr->daddr.s6_addr))
            {
                if (OAL_TRUE == dmac_ao_is_ipv6_global_ucst_exist(pst_dmac_vap))
                {
                    return DMAC_RX_FRAME_CTRL_DROP;
                }

                return DMAC_RX_FRAME_CTRL_GOON;
            }

            /* STAUT������ַȫ���ϱ� */
            return DMAC_RX_FRAME_CTRL_GOON;
        }

        case MAC_ND_NSOL:
        {
            /* NS����Ŀ���IPv6��ַ���������鲥��ַ�������Ǳ�����·������վ�㡢ȫ�ֵ�ַ */
            if (OAL_TRUE == dmac_ao_is_ipv6_addr_owner(pst_dmac_vap, pst_rx_nd_hdr->target.s6_addr))
            {
                /* �ظ���ַ���DAD����ַ�ظ��ˣ���NA֪ͨ�Զ� */
                /* ��ַ�������ھӲ��ɴ���NUD��������Ǳ���MAC��ַ����NA���Զ� */
                return dmac_ao_encap_na(pst_dmac_vap, pst_dmac_user, pst_netbuf, pst_rx_snap);
            }

            if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
            {
                /* AP��ת��/������ */
                return DMAC_RX_FRAME_CTRL_GOON;
            }

            return DMAC_RX_FRAME_CTRL_DROP;
        }

        case MAC_ND_NADVT:
        {
            if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
            {
                return DMAC_RX_FRAME_CTRL_GOON;
            }

            /* �ж�ICMPv6ͷ��Target Address��������Ǳ��ص�ַ�ľͶ����������ϱ�host */
            if ((OAL_TRUE == dmac_ao_is_ipv6_addr_owner(pst_dmac_vap, pst_rx_ipv6_hdr->daddr.s6_addr))
                || (OAL_TRUE == dmac_ao_is_ipv6_addr_owner(pst_dmac_vap, pst_rx_nd_hdr->target.s6_addr)))
            {
                return DMAC_RX_FRAME_CTRL_GOON;
            }

            return DMAC_RX_FRAME_CTRL_DROP;
        }

        case MAC_ND_RMES:
        {
            /* APUT/STAUTȫ���ϱ� */
            return DMAC_RX_FRAME_CTRL_GOON;
        }

        default:
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_nd_offload::ND type[%d] is unknown, send ND to host.}", pst_rx_nd_hdr->icmph.icmp6_type);
            return DMAC_RX_FRAME_CTRL_GOON;
        }
    }
}


/*****************************************************************************
 �� �� ��  : dmac_rx_get_dhcp_type
 ��������  : ��ȡDHCP���ĵ�����
 �������  : oal_uint8 *puc_pos
             oal_uint8 *puc_packet_end
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��29��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint8 dmac_ao_get_dhcp_type(oal_uint8 *puc_pos, oal_uint8 *puc_packet_end)
{
    oal_uint8       *puc_opt;

    /* ��ȡDHCP���� */
    while ((puc_pos < puc_packet_end) && (*puc_pos != 0xFF))
    {
        puc_opt = puc_pos++;

        if (0 == *puc_opt)
        {
            continue;  /* Padding */
        }

        puc_pos += *puc_pos + 1;
        if (puc_pos >= puc_packet_end)
        {
            break;
        }

        if ((53 == *puc_opt) && (puc_opt[1] != 0))  /* Message type */
        {
            return puc_opt[2];
        }
    }

    return DMAC_AO_UNKNOWN_TYPE;
}

/*****************************************************************************
 �� �� ��  : dmac_ao_process_dhcp_filter
 ��������  : STAUT��DHCP���Ĵ�����
 �������  : dmac_vap_stru *pst_dmac_vap
             oal_netbuf_stru *pst_netbuf
 �������  : ��
 �� �� ֵ  : OAL_STATIC dmac_rx_frame_ctrl_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC dmac_rx_frame_ctrl_enum_uint8 dmac_ao_process_dhcp_filter(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_vap_stru                        *pst_mac_vap = &pst_dmac_vap->st_vap_base_info;

    oal_ip_header_stru                  *pst_rx_ip_hdr;
    oal_dhcp_packet_stru                *pst_rx_dhcp_hdr;

    oal_uint8                            uc_type;
    oal_uint8                           *puc_packet_end;
    oal_uint8                           *puc_pos;

    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    puc_pos = oal_netbuf_payload(pst_netbuf);
    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_pos))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_dhcp_filter::Get netbuf snap payload failed.}");
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    puc_pos        += SNAP_LLC_FRAME_LEN;        /* ָ��IP Header */
    pst_rx_ip_hdr   = (oal_ip_header_stru *)puc_pos;
    puc_pos        += (puc_pos[0] & 0x0F) << 2;  /* point udp header */
    pst_rx_dhcp_hdr = (oal_dhcp_packet_stru *)(puc_pos + 8);

    puc_packet_end  = (oal_uint8 *)pst_rx_ip_hdr + OAL_NET2HOST_SHORT(pst_rx_ip_hdr->us_tot_len);
    puc_pos         = &(pst_rx_dhcp_hdr->options[4]);

    uc_type = dmac_ao_get_dhcp_type(puc_pos, puc_packet_end);
    if (DMAC_AO_UNKNOWN_TYPE == uc_type)
    {
        /* DTS2015100700167 �����ȡ����DHCP type���ϱ�Host�ദ�� */
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_dhcp_filter::Get DHCP type failed.}");
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    switch (uc_type)
    {
        /* �����ֱ��Ķ��� */
        case MAC_DHCP_DISCOVER:
        case MAC_DHCP_REQUEST:
        case MAC_DHCP_DECLINE:
        case MAC_DHCP_RELEASE:
        case MAC_DHCP_INFORM:
        {
            return DMAC_RX_FRAME_CTRL_DROP;
        }

        /* �����ֱ����ϱ�Host */
        case MAC_DHCP_OFFER:
        case MAC_DHCP_ACK:
        case MAC_DHCP_NAK:
        {
            /* �ͽ��յ��ı��ĵ�Client Hardware Addr���бȽϣ�������ǻر���MAC��ַ��DHCP���ģ����� */
            /* chaddr[16]��ǰ6���ֽ�Ϊclient��MAC��ַ����10�ֽڱ���δ�� */
            if (0 != oal_memcmp(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID, pst_rx_dhcp_hdr->chaddr, WLAN_MAC_ADDR_LEN))
            {
                return DMAC_RX_FRAME_CTRL_DROP;
            }

            return DMAC_RX_FRAME_CTRL_GOON;
        }

        default:
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_dhcp_filter::Recieve DHCP type[%d] is unknown, send DHCP to host.}", uc_type);
            return DMAC_RX_FRAME_CTRL_GOON;
        }
    }
}

/*****************************************************************************
 �� �� ��  : dmac_ao_get_dhcpv6_client_mac_addr
 ��������  : ��ȡDHCPv6��client Mac��ַ
 �������  : oal_uint8 *puc_pos
             oal_uint8 *puc_packet_end
             oal_uint8 *puc_type
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 dmac_ao_get_dhcpv6_client_mac_addr(oal_uint8 *puc_pos, oal_uint8 *puc_packet_end, oal_uint8 *puc_client_mac_addr)
{
    /****************************************************************
    (1)Format of Client Identifier Option:
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |      OPTION_CLIENTID(1)       |           option-len          |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    .                                                               .
    .                             DUID                              .
    .                       (variable length)                       .
    .                                                               .
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    (2)Format of DUID-LLT:
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |               1               |    hardware type (16 bits)    |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |                          time (32 bits)                       |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    .                                                               .
    .               link-layer address (variable length)            .
    .                                                               .
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    (3)Format of DUID-EN:
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |               2               |      enterprise-number        |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |    enterprise-number (contd)  |                               |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+                               |
    .                          identifier                           .
    .                      (variable length)                        .
    .                                                               .
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

    (4)Format of DUID-LL:
     0                   1                   2                   3
     0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    |               3               |    hardware type (16 bits)    |
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    .                                                               .
    .               link-layer address (variable length)            .
    .                                                               .
    +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
    ****************************************************************/

    oal_uint16       *pus_opt;


    /* ��ȡDHCPv6��client mac addr */
    while (puc_pos < puc_packet_end)
    {
        pus_opt = (oal_uint16 *)puc_pos;

        /* ָ����һ��ѡ��ͷ */
        puc_pos += OAL_NET2HOST_SHORT(*(oal_uint16 *)(puc_pos + 2)) + 4;
        if (puc_pos > puc_packet_end)
        {
            /* ѡ��Ȳ������Ѿ������ */
            break;
        }

        /* option client */
        if (1 == OAL_NET2HOST_SHORT(*pus_opt))
        {
            switch (OAL_NET2HOST_SHORT(*(pus_opt + 2)))
            {
                /* DUID Based on Link-layer Address Plus Time [DUID-LLT] */
                case 1:
                {
                    oal_memcopy(puc_client_mac_addr, (oal_uint8 *)(pus_opt + 6), WLAN_MAC_ADDR_LEN);
                    return OAL_SUCC;
                }

                /* DUID Based on Link-layer Address [DUID-LL] */
                case 3:
                {
                    oal_memcopy(puc_client_mac_addr, (oal_uint8 *)(pus_opt + 4), WLAN_MAC_ADDR_LEN);
                    return OAL_SUCC;
                }

                default:
                {
                    return OAL_FAIL;
                }
            }
        }
    }

    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : dmac_ao_process_dhcpv6_filter
 ��������  : STAUT��DHCPv6���Ĵ�����
 �������  : dmac_vap_stru *pst_dmac_vap
             oal_netbuf_stru *pst_netbuf
 �������  : ��
 �� �� ֵ  : OAL_STATIC dmac_rx_frame_ctrl_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC dmac_rx_frame_ctrl_enum_uint8 dmac_ao_process_dhcpv6_filter(dmac_vap_stru *pst_dmac_vap , oal_netbuf_stru *pst_netbuf)
{
    mac_vap_stru                        *pst_mac_vap = &pst_dmac_vap->st_vap_base_info;

    mac_llc_snap_stru                   *pst_rx_snap;
    oal_ipv6hdr_stru                    *pst_rx_ipv6_hdr;

    oal_uint8                           *puc_dhcpv6_hdr;

    oal_uint8                           *puc_packet_end;
    oal_uint8                           *puc_pos;
    oal_uint8                            auc_client_mac_addr[WLAN_MAC_ADDR_LEN];

    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    pst_rx_snap = (mac_llc_snap_stru *)oal_netbuf_payload(pst_netbuf);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_rx_snap))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_dhcpv6_filter::Get netbuf snap payload failed.}");
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    pst_rx_ipv6_hdr = (oal_ipv6hdr_stru *)(pst_rx_snap + 1);
    if (OAL_UNLIKELY(OAL_IPPROTO_UDP != pst_rx_ipv6_hdr->nexthdr))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_process_dhcpv6_filter::DHCPv6's ipv6 header's next header[%d] is wrong, drop DHCPv6.}", pst_rx_ipv6_hdr->nexthdr);
        return DMAC_RX_FRAME_CTRL_DROP;
    }

    puc_dhcpv6_hdr  = (oal_uint8 *)(pst_rx_ipv6_hdr + 1) + 8;

    switch (*puc_dhcpv6_hdr)
    {
        case MAC_DHCPV6_ADVERTISE:
        case MAC_DHCPV6_REPLY:
        {
            if (OAL_TRUE == dmac_ao_is_ipv6_addr_owner(pst_dmac_vap, pst_rx_ipv6_hdr->daddr.s6_addr))
            {
                return DMAC_RX_FRAME_CTRL_GOON;
            }
            break;
        }

        case MAC_DHCPV6_RECONFIGURE:
        {
            /* һ����IPV6����,ȫ���ϱ�host */
            return DMAC_RX_FRAME_CTRL_GOON;
        }

        default:
        {
            return DMAC_RX_FRAME_CTRL_DROP;
        }
    }

    puc_packet_end = puc_dhcpv6_hdr + (pst_rx_ipv6_hdr->payload_len - 8);
    puc_pos        = puc_dhcpv6_hdr + 4;

    /* �����ȡ����DHCPv6��client Mac��ַ,���� */
    if (OAL_SUCC != dmac_ao_get_dhcpv6_client_mac_addr(puc_pos, puc_packet_end, auc_client_mac_addr))
    {
        return DMAC_RX_FRAME_CTRL_DROP;
    }

    /* ���client��MAC��ַ���Ǳ���MAC��ַ��DHCP����,���� */
    if (0 != oal_memcmp(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID, auc_client_mac_addr, WLAN_MAC_ADDR_LEN))
    {
        return DMAC_RX_FRAME_CTRL_DROP;
    }

    return DMAC_RX_FRAME_CTRL_GOON;
}

/*****************************************************************************
 �� �� ��  : dmac_ao_sta_process_multicast_filter
 ��������  : STAUT���鲥/�㲥���Ĺ��˺���
 �������  : dmac_vap_stru *pst_dmac_vap
             oal_netbuf_stru *pst_netbuf
 �������  : ��
 �� �� ֵ  : OAL_STATIC dmac_rx_frame_ctrl_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC dmac_rx_frame_ctrl_enum_uint8 dmac_ao_sta_process_multicast_filter(dmac_vap_stru * pst_dmac_vap , oal_netbuf_stru *pst_netbuf)
{
    mac_vap_stru                        *pst_mac_vap = &pst_dmac_vap->st_vap_base_info;
    mac_llc_snap_stru                   *pst_snap;
    mac_ieee80211_qos_frame_stru        *pst_rx_hdr;
    oal_uint8                           *puc_dest_addr;
    oal_ip_header_stru                  *pst_ipv4;
    oal_ipv6hdr_stru                    *pst_ipv6;

    pst_rx_hdr    = (mac_ieee80211_qos_frame_stru *)OAL_NETBUF_HEADER(pst_netbuf);
    puc_dest_addr = pst_rx_hdr->auc_address1;

    /* MAC�㲥/�鲥���� */
    if (ETHER_IS_MULTICAST(puc_dest_addr))
    {
        /* ������MAC�㲥/�鲥֡���� */
        return DMAC_RX_FRAME_CTRL_DROP;
    }

    pst_snap = (mac_llc_snap_stru *)oal_netbuf_payload(pst_netbuf);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_snap))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{dmac_ao_sta_process_multicast_filter::Get netbuf snap payload failed.}");
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    /* IP�㲥/�鲥���� */
    if (OAL_HOST2NET_SHORT(ETHER_TYPE_IP) == pst_snap->us_ether_type)
    {
        pst_ipv4 = (oal_ip_header_stru *)(pst_snap + 1);

        if (OAL_IPV4_IS_BROADCAST((oal_uint8 *)(&(pst_ipv4->ul_daddr)))
            || OAL_IPV4_IS_MULTICAST((oal_uint8 *)(&(pst_ipv4->ul_daddr))))
        {
            return DMAC_RX_FRAME_CTRL_DROP;
        }
    }
    else if (OAL_HOST2NET_SHORT(ETHER_TYPE_IPV6) == pst_snap->us_ether_type)
    {
        pst_ipv6 = (oal_ipv6hdr_stru *)(pst_snap + 1);

        if (OAL_IPV6_IS_MULTICAST(pst_ipv6->daddr.s6_addr))
        {
            return DMAC_RX_FRAME_CTRL_DROP;
        }
    }

    return DMAC_RX_FRAME_CTRL_GOON;
}


/*****************************************************************************
 �� �� ��  : dmac_rx_process_arp_and_mcast
 ��������  : �����鲥���㲥��ARP��DHCP�ȱ��ĵ�����ں���
 �������  : dmac_vap_stru *pst_dmac_vap
             oal_netbuf_stru *pst_netbuf
 �������  : ��
 �� �� ֵ  : OAL_STATIC dmac_rx_frame_ctrl_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
dmac_rx_frame_ctrl_enum_uint8 dmac_ao_process_arp_and_mcast(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_netbuf)
{
    oal_uint8           uc_data_type;
    mac_device_stru    *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL  == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id,OAM_SF_PWR,"mac device is null");
        return DMAC_RX_FRAME_CTRL_DROP;
    }

    /* δ������ */
    if (OAL_FALSE == pst_mac_device->uc_arpoffload_switch)
    {
        return DMAC_RX_FRAME_CTRL_GOON;
    }

    uc_data_type = mac_get_data_type(pst_netbuf);

    /* ����֡/�����ȹ��� */
    switch (uc_data_type)
    {
        case MAC_DATA_EAPOL:
        {
            return DMAC_RX_FRAME_CTRL_GOON;
        }

        case MAC_DATA_ARP_REQ:
        case MAC_DATA_ARP_RSP:
        {
            return dmac_ao_process_arp_offload(pst_dmac_vap, pst_dmac_user, pst_netbuf);
        }

        case MAC_DATA_ND:
        {
            return dmac_ao_process_nd_offload(pst_dmac_vap, pst_dmac_user, pst_netbuf);
        }

        case MAC_DATA_DHCP:
        {
            return dmac_ao_process_dhcp_filter(pst_dmac_vap, pst_netbuf);
        }

        case MAC_DATA_DHCPV6:
        {
            return dmac_ao_process_dhcpv6_filter(pst_dmac_vap, pst_netbuf);
        }

        default:
        {
            break;
        }
    }

    /* STAUT��IP�㲥/�鲥���ˡ�MAC�㲥/�鲥���� */
    if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        return dmac_ao_sta_process_multicast_filter(pst_dmac_vap, pst_netbuf);
    }

    return DMAC_RX_FRAME_CTRL_GOON;
}

#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


