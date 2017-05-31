/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_tx_bss_comm.h
  �� �� ��   : ����
  ��    ��   : mayuan
  ��������   : 2012��11��15��
  ����޸�   :
  ��������   : dmac_tx_bss_comm.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��15��
    ��    ��   : mayuan
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_TX_BSS_COMM_H__
#define __DMAC_TX_BSS_COMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "hal_ext_if.h"
#include "oal_ext_if.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif
#include "dmac_vap.h"
#include "dmac_user.h"
#include "dmac_main.h"
#include "dmac_alg.h"
#include "wlan_types.h"
#include "oal_net.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TX_BSS_COMM_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define DMAC_MAX_FIFO_PUT       10  /* = FIFO DEHPTH + PREFETCH */
#define DMAC_MAX_PENDING_RETRY  6

typedef oal_uint32 (*p_dmac_tx_parse_mpdu_func)(oal_netbuf_stru *pst_netbuf, hal_tx_msdu_address_params *past_msdu);


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
extern oal_uint8 g_auc_default_mac_to_phy_protocol_mapping[WLAN_PROTOCOL_BUTT];
#endif

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    hal_to_dmac_device_stru *pst_hal_device;
    mac_tx_ctl_stru         *pst_tx_cb;
    hal_tx_dscr_stru        *pst_tx_dscr;
    oal_netbuf_stru         *pst_netbuf;
    oal_uint8               *puc_mac_hdr_addr;
    oal_uint8               *puc_mac_payload_addr;
    oal_uint8                auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint16               us_mac_frame_len;      /* ֡ͷ+֡�峤�� */
    oal_uint8                uc_mac_hdr_len;
    oal_switch_enum_uint8    en_frame_switch;
    oal_switch_enum_uint8    en_cb_switch;
    oal_switch_enum_uint8    en_dscr_switch;
}dmac_tx_dump_param_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/
extern oal_uint32  dmac_tx_data(
    dmac_vap_stru            *pst_dmac_vap,
    dmac_user_stru           *pst_dmac_user,
    mac_tx_ctl_stru          *pst_tx_ctl,
    oal_dlist_head_stru      *pst_tx_dscr_list_hdr,
    hal_tx_ppdu_feature_stru *pst_ppdu_feature,
    hal_tx_txop_alg_stru     *pst_txop_alg);
extern oal_uint32  dmac_tx_process_data_event(frw_event_mem_stru *pst_event_mem);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
extern oal_uint32  dmac_tx_get_amsdu_params(
                                        oal_netbuf_stru  *pst_netbuf,
                                        mac_tx_ctl_stru  *pst_tx_ctl,
                                        hal_tx_mpdu_stru *pst_mpdu);
#endif
extern oal_uint32  dmac_tx_process_data(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);
extern oal_uint32  dmac_tx_mgmt(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf_mgmt, oal_uint16 us_len);
extern oal_uint32  dmac_tid_tx_queue_remove(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, dmac_tid_stru *pst_tid_queue, oal_uint8 uc_dscr_num);
extern oal_uint32  dmac_tid_tx_queue_remove_ampdu(hal_to_dmac_device_stru *pst_hal_device, dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_user, dmac_tid_stru *pst_tid_queue, oal_uint8 uc_mpdu_num);
extern oal_void  dmac_tx_excp_free_dscr(oal_dlist_head_stru *pst_tx_dscr_list_hdr, hal_to_dmac_device_stru *pst_hal_device);
extern oal_netbuf_stru* dmac_tx_dequeue_first_mpdu(oal_netbuf_head_stru  *pst_netbuf_head);
extern oal_uint32  dmac_tx_excp_free_netbuf(oal_netbuf_stru *pst_netbuf);
extern oal_uint32  dmac_flush_txq_to_tid_of_vo(hal_to_dmac_device_stru *pst_hal_device);
#if defined (_PRE_WLAN_FEATURE_UAPSD) || defined (_PRE_WLAN_FEATURE_STA_PM)
extern oal_uint32 dmac_send_qosnull(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_uint8 uc_ac, oal_bool_enum_uint8 en_ps);
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32  dmac_tx_force(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint16 us_len, oal_uint8 uc_mgmt);
#endif //_PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_tx_set_htc_field
 ��������  : ����MACͷ��HTC�ֶ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_set_htc_field(
                                    hal_to_dmac_device_stru  *pst_hal_device,
                                    hal_tx_dscr_stru         *pst_tx_dscr,
                                    mac_tx_ctl_stru          *pst_tx_ctl,
                                    hal_tx_ppdu_feature_stru *pst_ppdu_feature)
{
    mac_ieee80211_qos_htc_frame_addr4_stru  *pst_mac_ieee80211_qos_htc_frame_addr4;
    mac_ieee80211_qos_htc_frame_stru        *pst_mac_ieee80211_qos_htc_frame;
    oal_uint8                                uc_mac_header_length;

    /* frame control B15(Order)��Ϊ1������HTC���֣�����HTC�ֶε�B22B23ֵ��11, ��д������ */
    if (OAL_TRUE == mac_get_cb_is_use_4_addr(pst_tx_ctl))
    {
        pst_mac_ieee80211_qos_htc_frame_addr4  = (mac_ieee80211_qos_htc_frame_addr4_stru *)mac_get_cb_frame_hdr(pst_tx_ctl);
        pst_mac_ieee80211_qos_htc_frame_addr4->ul_htc = (BIT22 | BIT23);
        pst_mac_ieee80211_qos_htc_frame_addr4->st_frame_control.bit_order = 1;
        uc_mac_header_length                   = OAL_SIZEOF(mac_ieee80211_qos_htc_frame_addr4_stru);
    }
    else
    {
        pst_mac_ieee80211_qos_htc_frame = (mac_ieee80211_qos_htc_frame_stru *)mac_get_cb_frame_hdr(pst_tx_ctl);
        pst_mac_ieee80211_qos_htc_frame->auc_htc[2] = (oal_uint8)(BIT6 | BIT7);
        pst_mac_ieee80211_qos_htc_frame->st_frame_control.bit_order = 1;
        uc_mac_header_length                   = OAL_SIZEOF(mac_ieee80211_qos_htc_frame_stru);
    }

    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl) = uc_mac_header_length;

    /* DTS2016042106439 ֡ͷ�����б仯��mpdu_lenҲҪ���� */
    pst_tx_dscr->us_original_mpdu_len = uc_mac_header_length + MAC_GET_CB_MPDU_LEN(pst_tx_ctl);

    if (pst_ppdu_feature->uc_ampdu_enable == OAL_TRUE)
    {
        pst_ppdu_feature->ul_ampdu_length  += (OAL_SIZEOF(mac_ieee80211_qos_htc_frame_stru) - OAL_SIZEOF(mac_ieee80211_qos_frame_stru));
    }

    /* �޸���������mac ֡ͷ���� */
    hal_tx_set_dscr_modify_mac_header_length(pst_hal_device,pst_tx_dscr, uc_mac_header_length);

}

/*****************************************************************************
 �� �� ��  : dmac_tx_unset_htc_field
 ��������  : ȥ��MACͷ��HTC�ֶ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��6��3��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_unset_htc_field(
                                    hal_to_dmac_device_stru  *pst_hal_device,
                                    hal_tx_dscr_stru         *pst_tx_dscr,
                                    mac_tx_ctl_stru          *pst_tx_ctl,
                                    hal_tx_ppdu_feature_stru *pst_ppdu_feature)
{
    oal_uint8   uc_mac_header_length;

    if (OAL_TRUE == mac_get_cb_is_use_4_addr(pst_tx_ctl))
    {
        uc_mac_header_length = MAC_80211_QOS_4ADDR_FRAME_LEN;
    }
    else
    {
        uc_mac_header_length = MAC_80211_QOS_FRAME_LEN;
    }

    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl) = uc_mac_header_length;

    pst_tx_dscr->us_original_mpdu_len = uc_mac_header_length + MAC_GET_CB_MPDU_LEN(pst_tx_ctl);

    if (pst_ppdu_feature->uc_ampdu_enable == OAL_TRUE)
    {
        pst_ppdu_feature->ul_ampdu_length  -= (MAC_80211_QOS_HTC_FRAME_LEN - MAC_80211_QOS_FRAME_LEN);
    }

    /* �޸���������mac ֡ͷ���� */
    hal_tx_set_dscr_modify_mac_header_length(pst_hal_device, pst_tx_dscr, uc_mac_header_length);
}

/*****************************************************************************
 �� �� ��  : dmac_free_tx_dscr
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��18��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_free_tx_dscr(hal_tx_dscr_stru *pst_tx_dscr)
{
    oal_netbuf_stru   *pst_netbuf = OAL_PTR_NULL;

    pst_netbuf = pst_tx_dscr->pst_skb_start_addr;
    pst_tx_dscr->pst_skb_start_addr = OAL_PTR_NULL;

    OAL_MEM_FREE(pst_tx_dscr, OAL_TRUE);
    if (OAL_PTR_NULL != pst_netbuf)
    {
        dmac_tx_excp_free_netbuf(pst_netbuf);
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_free_tx_dscr::pst_netbuf null.}");
    }
}

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
/*****************************************************************************
 �� �� ��  : dmac_tx_get_spec_mode_ucast_data_params
 ��������  : ��ȡ����ض�Э��ģʽ�û��ĵ�������֡���Ͳ���
 �������  : pst_dmac_vap
             pst_dmac_user
             pst_tx_ctl
 �������  : ppst_txop_alg
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��10��
    ��    ��   : liwenjun 00330043
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 dmac_tx_get_spec_mode_ucast_data_params(
                                                   dmac_vap_stru         *pst_dmac_vap,
                                                   dmac_user_stru        *pst_dmac_user,
                                                   mac_tx_ctl_stru       *pst_tx_ctl,
                                                   hal_tx_txop_alg_stru  **ppst_txop_alg)
{
    wlan_phy_protocol_enum_uint8 en_phy_protocol = g_auc_default_mac_to_phy_protocol_mapping[pst_dmac_user->st_user_base_info.en_avail_protocol_mode];

    if (en_phy_protocol >= WLAN_PHY_PROTOCOL_BUTT)
    {
        OAM_ERROR_LOG2(0, OAM_SF_TX, "{dmac_tx_get_spec_mode_ucast_data_params::invalid en_phy_protocol(%u), caused by en_avail_protocol_mode(%u).}",
            en_phy_protocol, pst_dmac_user->st_user_base_info.en_avail_protocol_mode);
        return OAL_FAIL;
    }

    /* ����ǰuser���õ�protocol����Ӧ�����ò���valid, ����ø�Э���µ�ucast data���Ͳ��� */
    if ((WLAN_VHT_PHY_PROTOCOL_MODE == en_phy_protocol) && (1 == pst_dmac_vap->un_mode_valid.st_spec_mode.bit_vht_param_vaild))
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg_vht);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg_vht;
    }
    else if ((WLAN_HT_PHY_PROTOCOL_MODE == en_phy_protocol) && (1 == pst_dmac_vap->un_mode_valid.st_spec_mode.bit_ht_param_vaild))
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg_ht);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg_ht;
    }
    else if ((WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE == en_phy_protocol) && (1 == pst_dmac_vap->un_mode_valid.st_spec_mode.bit_11ag_param_vaild))
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg_11ag);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg_11ag;
    }
    else if ((WLAN_11B_PHY_PROTOCOL_MODE == en_phy_protocol) && (1 == pst_dmac_vap->un_mode_valid.st_spec_mode.bit_11b_param_vaild))
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg_11b);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg_11b;
    }
    /* ����, ���ǲ���Ĭ�ϵ�ucast data���Ͳ��� */
    else
    {
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg;
    }

    return OAL_SUCC;
}
#endif


/*****************************************************************************
 �� �� ��  : dmac_tx_get_txop_alg_params
 ��������  : ��ȡ���Ͳ���
 �������  : ��
 �������  : ppst_txop_alg
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��19��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_tx_get_txop_alg_params(
                                                   dmac_vap_stru         *pst_dmac_vap,
                                                   dmac_user_stru        *pst_dmac_user,
                                                   mac_tx_ctl_stru       *pst_tx_ctl,
                                                   hal_tx_txop_alg_stru  **ppst_txop_alg)
{
    if (OAL_TRUE == pst_tx_ctl->bit_is_vipframe)
    {
        *ppst_txop_alg = &pst_dmac_vap->ast_tx_mgmt_bmcast[pst_dmac_vap->st_vap_base_info.st_channel.en_band];
         return OAL_SUCC;
    }

    /* ���㷨��ȡ������������֡���� */
    if (OAL_FALSE == MAC_GET_CB_IS_MCAST(pst_tx_ctl))
    {
    #ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
        /* ��vap��δ��������ض�Э���ucast data���Ͳ���, �����Ĭ�ϵ�ucast data���Ͳ��� */
        if (0 == pst_dmac_vap->un_mode_valid.uc_mode_param_valid)
        {
            dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg);
            *ppst_txop_alg = &pst_dmac_vap->st_tx_alg;
        }
        else
        {
            oal_uint32      ul_ret;
            ul_ret = dmac_tx_get_spec_mode_ucast_data_params(pst_dmac_vap, pst_dmac_user, pst_tx_ctl, ppst_txop_alg);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_get_txop_alg_params::dmac_tx_get_spec_mode_ucast_data_params fail, error code = %u}", ul_ret);
                return ul_ret;
            }
        }
    #else
        /* ���㷨����ȡ��������֡���ʵȷ��Ͳ��� */
        dmac_alg_tx_notify(pst_dmac_vap, (mac_user_stru *)pst_dmac_user, pst_tx_ctl, &pst_dmac_vap->st_tx_alg);
        *ppst_txop_alg = &pst_dmac_vap->st_tx_alg;
    #endif
    }
    else /* �����д�鲥/�㲥����֡���Ͳ��� */
    {
        *ppst_txop_alg = &pst_dmac_vap->st_tx_data_mcast;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_tx_get_ppdu_feature
 ��������  : ��дppdu feature �ֶ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_init_ppdu_feature(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_uint8 uc_mpdu_num, hal_tx_ppdu_feature_stru *pst_ppdu_feature)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    hal_to_dmac_device_stru   *pst_hal_device_base;

    pst_hal_device_base = pst_dmac_vap->pst_hal_device;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hal_device_base))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG, "{dmac_config_set_always_tx::pst_hal_device null.}");
        return;
    }
#endif

    if (OAL_PTR_NULL == pst_dmac_vap->pst_hal_vap)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_init_ppdu_feature::pst_hal_vap null.}");

        return;
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (mac_vap_is_vsta(&pst_dmac_vap->st_vap_base_info))
    {
        /* �������Repeater���ܣ�Proxy STA�ķ����������е�TX VAP index��Ҫ��Ϊ4(����ͨsta��һ����) */
        pst_ppdu_feature->st_ppdu_addr_index.uc_tx_vap_index = WLAN_STA0_HAL_VAP_ID;
        pst_ppdu_feature->st_ppdu_addr_index.uc_ori_tx_vap_index = pst_dmac_vap->pst_hal_vap->uc_vap_id;
    }
    else
    {
        pst_ppdu_feature->st_ppdu_addr_index.uc_tx_vap_index = pst_dmac_vap->pst_hal_vap->uc_vap_id;
        pst_ppdu_feature->st_ppdu_addr_index.uc_ori_tx_vap_index = 0;
    }
#else
    pst_ppdu_feature->st_ppdu_addr_index.uc_tx_vap_index = pst_dmac_vap->pst_hal_vap->uc_vap_id;
#endif

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        pst_ppdu_feature->st_ppdu_addr_index.uc_ra_lut_index = 0;/* �û��ṹ���µ�lut index */
    }
    else
    {
        /* addba req��Ҫ��д��ȷ��ra lut index �Ի�ȡ��ȷ��ssn */
        pst_ppdu_feature->st_ppdu_addr_index.uc_ra_lut_index = pst_dmac_user->uc_lut_index; /* �û��ṹ���µ�lut index */
        /* OAM_INFO_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{dmac_tx_init_ppdu_feature::uc_ra_lut_index=%d.}",
                      pst_ppdu_feature->st_ppdu_addr_index.uc_ra_lut_index); */
    }

    /* ����/����֡ ������Щ�ֶ���Ч��ʼ��Ϊ0 */
    pst_ppdu_feature->uc_mpdu_num               = uc_mpdu_num;
    pst_ppdu_feature->uc_ampdu_enable           = 0;
    pst_ppdu_feature->uc_rifs_enable            = 0;
    pst_ppdu_feature->ul_ampdu_length           = 0;
    pst_ppdu_feature->us_min_mpdu_length        = 0;
    pst_ppdu_feature->en_addba_ssn_hw_bypass    = OAL_TRUE;
    pst_ppdu_feature->en_duration_hw_bypass     = OAL_FALSE;
    pst_ppdu_feature->en_retry_flag_hw_bypass   = OAL_FALSE;
    pst_ppdu_feature->en_seq_ctl_hw_bypass      = OAL_FALSE;
    pst_ppdu_feature->en_timestamp_hw_bypass    = OAL_FALSE;
    pst_ppdu_feature->en_tx_pn_hw_bypass        = OAL_FALSE;
    pst_ppdu_feature->en_long_nav_enable        = OAL_FALSE;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    if(OAL_SWITCH_ON == pst_hal_device_base->uc_al_tx_flag)
    {
        pst_ppdu_feature->en_seq_ctl_hw_bypass      = OAL_TRUE;
        pst_ppdu_feature->en_duration_hw_bypass     = OAL_TRUE;
        pst_ppdu_feature->en_retry_flag_hw_bypass   = OAL_TRUE;
    }
#endif
}

/*****************************************************************************
 �� �� ��  : dmac_tx_update_ppdu_feature
 ��������  : ����ppdu�ṹ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��13��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_tx_update_ppdu_feature(oal_netbuf_stru *pst_netbuf, hal_tx_ppdu_feature_stru *pst_ppdu_feature)
{
    mac_tx_ctl_stru            *pst_cb;
    oal_uint8                   uc_frame_type = 0;           /* 802.11ͷ */

    pst_cb = (mac_tx_ctl_stru *)OAL_NETBUF_CB(pst_netbuf);
    uc_frame_type = (oal_uint8)(((mac_ieee80211_frame_stru *)mac_get_cb_frame_hdr(pst_cb))->st_frame_control.bit_type);

    /* ���·�Qos֡��seq_ctl_hw_bypass ��־ */
    if ((OAL_TRUE!= mac_get_cb_is_qosdata(pst_cb)) && (2 == uc_frame_type))
    {
        pst_ppdu_feature->en_seq_ctl_hw_bypass = mac_get_cb_is_seq_ctrl_bypass(pst_cb);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_get_mgmt_mpdu_param
 ��������  : ��ȡ����֡mpdu����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��1��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_get_mgmt_mpdu_param(oal_netbuf_stru *pst_netbuf_mgmt, mac_tx_ctl_stru *pst_tx_ctl,  oal_uint16 us_len, hal_tx_mpdu_stru *pst_mpdu)
{
    MAC_GET_CB_NETBUF_NUM(pst_tx_ctl) = 1;              /* ����ֻ֡��һ�� */
    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl) = FRW_EVENT_TYPE_WLAN_CTX;
    MAC_GET_CB_MPDU_NUM(pst_tx_ctl)   = 1;              /* ����ֻ֡��һ�� */
    mac_set_cb_is_amsdu(pst_tx_ctl, OAL_FALSE);         /* ����֡����amsdu�ۺ� */
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf_mgmt));

    /* ��дMPDU�������� */
    pst_mpdu->st_wmm.uc_tid_no = 0;
    pst_mpdu->st_wmm.uc_qos_enable = OAL_FALSE;
    if (WLAN_CONTROL == MAC_GET_CB_FRAME_TYPE(pst_tx_ctl))
    {
        pst_mpdu->st_wmm.uc_tid_no = mac_get_cb_tid(pst_tx_ctl);
        pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len = MAC_80211_CTL_HEADER_LEN;
    }
    else
    {
        pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len = MAC_80211_FRAME_LEN;
    }

    pst_mpdu->st_mpdu_mac_hdr.uc_num_sub_msdu = 1;

    pst_mpdu->st_mpdu_addr.ul_mac_hdr_start_addr = (oal_uint32)OAL_NETBUF_HEADER(pst_netbuf_mgmt);
    pst_mpdu->st_mpdu_addr.pst_skb_start_addr    = pst_netbuf_mgmt;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr0 = (oal_uint32)((oal_uint8 *)OAL_NETBUF_DATA(pst_netbuf_mgmt));
#else
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr0 = (oal_uint32)((oal_uint8 *)OAL_NETBUF_HEADER(pst_netbuf_mgmt) + pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len);
#endif

    pst_mpdu->ast_msdu_addr[0].us_msdu0_len  = us_len - pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len;

    pst_mpdu->ast_msdu_addr[0].us_msdu1_len  = 0;
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr1 = 0;

    MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl)  = pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len;
    MAC_GET_CB_MPDU_LEN(pst_tx_ctl)             = us_len - MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl);
}

/*****************************************************************************
 �� �� ��  : dmac_tx_get_txop_feature_params
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��21��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_tx_get_txop_feature_params(
                dmac_vap_stru              *pst_dmac_vap,
                dmac_user_stru             *pst_dmac_user,
                hal_tx_txop_feature_stru   *pst_txop_feature)
{

    pst_txop_feature->pst_security  = &(pst_dmac_user->st_user_base_info.st_user_tx_info.st_security);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_tx_get_mpdu_params
 ��������  : ��ȡMPDU���Ϳ��Ʋ���
 �������  : pst_hal_device:
             pst_dmac_vap  :
             pst_dmac_user :
             pst_netbuf    :
             pst_mpdu      :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��21��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_tx_get_mpdu_params(
                oal_netbuf_stru           *pst_netbuf,
                mac_tx_ctl_stru           *pst_tx_ctl,
                hal_tx_mpdu_stru          *pst_mpdu)
{

    /* ��ȡMPDU��ز��� */
    pst_mpdu->st_mpdu_mac_hdr.uc_mac_hdr_len   = MAC_GET_CB_FRAME_HEADER_LENGTH(pst_tx_ctl);
    pst_mpdu->st_mpdu_mac_hdr.uc_num_sub_msdu  = MAC_GET_CB_NETBUF_NUM(pst_tx_ctl);

    pst_mpdu->st_wmm.en_ack_policy = mac_get_cb_ack_policy(pst_tx_ctl);
    pst_mpdu->st_wmm.uc_tid_no     = mac_get_cb_tid(pst_tx_ctl);
    pst_mpdu->st_wmm.uc_qos_enable = mac_get_cb_is_qosdata(pst_tx_ctl);

    pst_mpdu->st_mpdu_addr.ul_mac_hdr_start_addr = (oal_uint32)mac_get_cb_frame_hdr(pst_tx_ctl);
    pst_mpdu->st_mpdu_addr.pst_skb_start_addr    = pst_netbuf;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr0 = (oal_uint32)oal_netbuf_payload(pst_netbuf);
    pst_mpdu->ast_msdu_addr[0].us_msdu0_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctl);
    pst_mpdu->ast_msdu_addr[0].ul_msdu_addr1 = 0;
    pst_mpdu->ast_msdu_addr[0].us_msdu1_len = 0;
#else
    if (OAL_FALSE == mac_get_cb_is_amsdu(pst_tx_ctl))
    {
        pst_mpdu->ast_msdu_addr[0].ul_msdu_addr0 = (oal_uint32)oal_netbuf_payload(pst_netbuf);
        pst_mpdu->ast_msdu_addr[0].us_msdu0_len = MAC_GET_CB_MPDU_LEN(pst_tx_ctl);
        pst_mpdu->ast_msdu_addr[0].ul_msdu_addr1 = 0;
        pst_mpdu->ast_msdu_addr[0].us_msdu1_len = 0;
    }
    else
    {
        return dmac_tx_get_amsdu_params(pst_netbuf, pst_tx_ctl, pst_mpdu);
    }
#endif

    return OAL_SUCC;
}



extern oal_void  dmac_proc_restore_tx_queue(hal_to_dmac_device_stru     *pst_hal_device,
                                                      hal_tx_dscr_queue_header_stru *pst_fake_queue);
extern oal_void dmac_proc_save_tx_queue(hal_to_dmac_device_stru       *pst_hal_device,
                                                  hal_tx_dscr_queue_header_stru *pst_fake_queue);

extern oal_uint32  dmac_tx_clear_tx_queue(hal_to_dmac_device_stru *pst_hal_device);
extern oal_uint32  dmac_tx_save_tx_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id);
extern oal_uint32  dmac_tx_clear_fake_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id);
extern oal_uint32  dmac_tx_restore_tx_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id);
extern oal_uint32  dmac_tx_switch_tx_queue(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_fake_q_id1, oal_uint8 uc_fake_q_id2);
extern oal_uint32  dmac_tx_fake_queue_empty_assert(
                hal_to_dmac_device_stru *pst_hal_device,
                oal_uint8                uc_fake_q,
                oal_uint32               ul_file_id);
#if 0
extern oal_uint32  dmac_flush_txq_to_tid(hal_to_dmac_device_stru *pst_hal_device);
#endif
extern oal_uint32  dmac_tx_update_protection_all_txop_alg(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32  dmac_tx_mgmt(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf_mgmt, oal_uint16 us_len);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_tx_bss_comm.h */
