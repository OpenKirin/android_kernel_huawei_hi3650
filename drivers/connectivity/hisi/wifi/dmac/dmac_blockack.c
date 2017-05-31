/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_blockack.c
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2013��4��8��
  ����޸�   :
  ��������   : AMPDU�ۺϡ�BA����ӿڶ���Դ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��4��8��
    ��    ��   : huxiaotong
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
#include "dmac_blockack.h"
#include "dmac_main.h"
#include "dmac_rx_data.h"
#include "dmac_tid.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_user.h"
#include "oal_net.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BLOCKACK_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* 11n���ʶ�Ӧ���start spacing��mpdu lenֵ�ı� */
oal_uint16 g_aus_ht_20mhz_rate_lut[WLAN_HT_MCS_BUTT] =
{13, 26, 39, 52, 78, 104, 117, 130, 26, 50, 78, 104, 156, 208, 234, 260};

oal_uint16 g_aus_ht_20mhz_rate_lut_shortgi[WLAN_HT_MCS_BUTT] =
{15, 29, 44, 58, 87, 116, 130, 145, 29, 58, 87, 114, 174, 232, 260, 289};

oal_uint16 g_aus_ht_40mhz_rate_lut[WLAN_HT_MCS_BUTT] =
{27, 54, 81, 108, 162, 243, 972, 270, 54, 108, 162, 216, 324, 432, 486, 540};

oal_uint16 g_aus_ht_40mhz_rate_lut_shortgi[WLAN_HT_MCS_BUTT] =
{30, 60, 90, 120, 180, 240, 270, 300, 60, 120, 180, 240, 360, 480, 540, 600};

/* 11ac���ʶ�Ӧ���start spacing��mpdu lenֵ�ı� */
oal_uint16 g_aus_vht_20mhz_rate_lut[WLAN_TRIPLE_NSS][WLAN_VHT_MCS_BUTT] =
{
    {13, 26, 39, 52, 78, 104, 117, 130, 156},
    {26, 52, 78, 104, 156, 209, 234, 260, 312},
};

oal_uint16 g_aus_vht_20mhz_rate_lut_shortgi[WLAN_TRIPLE_NSS][WLAN_VHT_MCS_BUTT] =
{
    {15, 29, 44, 58, 87, 116, 130, 145, 174, 0},
    {29, 58, 87, 116, 174, 232, 260, 289, 347, 0},
};

oal_uint16 g_aus_vht_40mhz_rate_lut[WLAN_TRIPLE_NSS][WLAN_VHT_MCS_BUTT] =
{
    {27, 54, 81, 108, 162, 216, 243, 270, 324, 360},
    {54, 108, 162, 216, 324, 432, 486, 540, 648, 720},
};

oal_uint16 g_aus_vht_40mhz_rate_lut_shortgi[WLAN_TRIPLE_NSS][WLAN_VHT_MCS_BUTT] =
{
    {30, 60, 90, 120, 180, 240, 270, 300, 360, 400},
    {60, 120, 180, 240, 360, 480, 540, 600, 720, 800},
};

oal_uint16 g_aus_vht_80mhz_rate_lut[WLAN_TRIPLE_NSS][WLAN_VHT_MCS_BUTT] =
{
    {59, 117, 176, 234, 351, 468, 527, 585, 702, 780},
    {117, 234, 351, 468, 702, 936, 1053, 1170, 1404, 1560},
};

oal_uint16 g_aus_vht_80mhz_rate_lut_shortgi[WLAN_TRIPLE_NSS][WLAN_VHT_MCS_BUTT] =
{
    {65, 130, 195, 260, 390, 520, 585, 650, 780, 867},
    {130, 260, 390, 520, 780, 1040, 1170, 1300, 1560, 1734},
};

#ifdef _PRE_WLAN_FEATURE_AMPDU
#ifdef _PRE_DEBUG_MODE
//#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB != _PRE_CONFIG_TARGET_PRODUCT) )
//dmac_tx_ba_track_stru g_ast_tx_ba_track[WLAN_DEVICE_SUPPORT_MAX_NUM_SPEC][HAL_MAX_AMPDU_LUT_SIZE];
//#endif
#endif   /* end of _PRE_DEBUG_MODE */
#endif   /* end of _PRE_WLAN_FEATURE_AMPDU */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_ba_check_rx_aggr
 ��������  : ����Ƿ�����ba��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��28��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_ba_check_rx_aggr(
                                                        mac_vap_stru                   *pst_vap,
                                                        mac_ieee80211_frame_stru       *pst_frame_hdr)
{
    /* ��vap�Ƿ���ht */
    if (OAL_FALSE == pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented)
    {
        //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_BA, "{dmac_ba_check_rx_aggr::ht not supported by this vap.}\r\n");
        return OAL_FAIL;
    }

    /* �жϸ�֡�ǲ���qos֡ */
    if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
    {
        //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_BA, "{dmac_ba_check_rx_aggr::not qos data.}\r\n");
        return OAL_FAIL;
    }

    /* �жϸ�֡�ǲ����鲥 */
    if (mac_is_grp_addr(pst_frame_hdr->auc_address1))
    {
        //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_BA, "{dmac_ba_check_rx_aggr::group data.}\r\n");
        return OAL_FAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_filter_serv
 ��������  : ����ampdu��ÿһ��mpdu ��δȷ�ϱ�����Ҫ���ش�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��10��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_ba_filter_serv(
                mac_vap_stru                   *pst_vap,
                dmac_user_stru                 *pst_dmac_user,
                dmac_rx_ctl_stru               *pst_cb_ctrl,
                mac_ieee80211_frame_stru       *pst_frame_hdr)
{
    dmac_vap_stru          *pst_dmac_vap;
    dmac_tid_stru          *pst_tid_queue;
    oal_uint8               uc_tid;
    dmac_ba_rx_stru        *pst_ba_rx_hdl;
    oal_bool_enum_uint8     en_is_4addr;
    oal_uint8               uc_is_tods;
    oal_uint8               uc_is_from_ds;
    oal_uint32              ul_ret;


    if (OAL_UNLIKELY(
        OAL_PTR_NULL == pst_dmac_user ||
        OAL_PTR_NULL == pst_cb_ctrl ||
        OAL_PTR_NULL == pst_frame_hdr ||
        OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG2(0, OAM_SF_BA, "{pst_dmac_user[0x%x],pst_cb_ctrl[0x%x]}",
                       pst_dmac_user, pst_cb_ctrl);
        OAM_ERROR_LOG2(0, OAM_SF_BA, "{dmac_ba_filter_serv::param null.pst_frame_hdr[0x%x],pst_vap[0x%x]}",
                       pst_frame_hdr, pst_vap);

        if ((OAL_PTR_NULL != pst_frame_hdr) && (OAL_PTR_NULL == pst_dmac_user))
        {
            OAM_ERROR_LOG3(0, OAM_SF_BA, "{dmac_ba_filter_serv:: source addr[0-2] %02X:%02X:%02X}",
                           pst_frame_hdr->auc_address2[0], pst_frame_hdr->auc_address2[1], pst_frame_hdr->auc_address2[2]);
            OAM_ERROR_LOG3(0, OAM_SF_BA, "{dmac_ba_filter_serv:: source addr[3-5] %02X:%02X:%02X}",
                           pst_frame_hdr->auc_address2[3], pst_frame_hdr->auc_address2[4], pst_frame_hdr->auc_address2[5]);
        }

        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = dmac_ba_check_rx_aggr(pst_vap, pst_frame_hdr);
    if (OAL_SUCC != ul_ret)
    {
        return OAL_SUCC;
    }

    /* �����ĵ�ַ�����ȡ���ĵ�tid */
    uc_is_tods    = mac_hdr_get_to_ds((oal_uint8 *)pst_frame_hdr);
    uc_is_from_ds = mac_hdr_get_from_ds((oal_uint8 *)pst_frame_hdr);
    en_is_4addr   = uc_is_tods && uc_is_from_ds;

    uc_tid = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

    //OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_BA, "{dmac_ba_filter_serv::uc_tid=%d.}", uc_tid);

    pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[uc_tid]);

#ifdef _PRE_DEBUG_MODE
    if (OAL_PTR_NULL == pst_tid_queue->pst_tid_ampdu_stat)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_BA, "{dmac_ba_filter_serv::ampdu_stat is null! }");
        return OAL_FAIL;
    }
#endif

    pst_ba_rx_hdl = pst_tid_queue->pst_ba_rx_hdl;

    /* BA�Ựû�н��� */
    if ((OAL_PTR_NULL == pst_ba_rx_hdl) || (DMAC_BA_COMPLETE != pst_ba_rx_hdl->en_ba_conn_status))
    {

        OAM_TID_AMPDU_STATS_INCR(pst_tid_queue->pst_tid_ampdu_stat->ul_ba_recipient_no_ba_session, 1);

        if (OAL_TRUE == pst_cb_ctrl->st_rx_status.bit_AMPDU)
        {
            OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_BA, "{dmac_ba_filter_serv::ba not created but recv ampdu, ba_rx_hdl: %p, ba status: %d.}",
                    pst_ba_rx_hdl, (pst_ba_rx_hdl == OAL_PTR_NULL) ? DMAC_BA_BUTT : pst_ba_rx_hdl->en_ba_conn_status);

            OAM_TID_AMPDU_STATS_INCR(pst_tid_queue->pst_tid_ampdu_stat->ul_ba_recipient_recv_ampdu_no_ba, 1);

            pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);

            pst_tid_queue->uc_rx_wrong_ampdu_num++;

            if (WLAN_RX_RESET_BA_THREHOLD == pst_tid_queue->uc_rx_wrong_ampdu_num)
            {
                /* send del ba */
                dmac_mgmt_delba(pst_dmac_vap, pst_dmac_user, uc_tid, MAC_RECIPIENT_DELBA, MAC_QSTA_SETUP_NOT_DONE);
                pst_tid_queue->uc_rx_wrong_ampdu_num = 0;
            }
        }

    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_ba_reset_rx_handle
 ��������  : ����rx ba�ṹ��,����Mac Ba lut��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��30��
    ��    ��   : h00217255
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_ba_reset_rx_handle(mac_device_stru *pst_device, dmac_ba_rx_stru **ppst_rx_ba, oal_uint8 uc_tid, dmac_user_stru *pst_dmac_user)
{
    if ((OAL_PTR_NULL == *ppst_rx_ba) || (OAL_PTR_NULL == pst_dmac_user))
    {
        return;
    }

    (*ppst_rx_ba)->en_is_ba = OAL_FALSE;

    /*����Ba Lut��*/
    if (MAC_BA_POLICY_IMMEDIATE != (*ppst_rx_ba)->uc_ba_policy)
    {
        OAM_WARNING_LOG0(0, OAM_SF_BA, "{dmac_ba_reset_rx_handle::ba policy is not immediate.}\r\n");
    }

    if (1 == (*ppst_rx_ba)->uc_ba_policy)
    {
    /* 1102����HG530��ɾ��Ӳ������BA��Ϣ */
    #if (!defined(_PRE_PRODUCT_ID_HI110X_DEV))
        hal_remove_machw_ba_lut_entry(pst_device->pst_device_stru, (*ppst_rx_ba)->uc_lut_index);
    #endif /* */
    }

    /*�ͷ�Dmac�����BA�Ự�������ڴ�*/
    OAL_MEM_FREE(*ppst_rx_ba, OAL_TRUE);

    *ppst_rx_ba = OAL_PTR_NULL;

    return;
}
/*****************************************************************************
 �� �� ��  : dmac_nontxop_txba_num_updata
 ��������  : ͳ��device��AMPDU�ۺϵ�TX�Ự����,���ڲ��� Э�̾ۺϸ�����ʱ ʹ��TXOP
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��31��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_nontxop_txba_num_updata(dmac_user_stru *pst_dmac_user, oal_uint8 uc_tid, oal_bool_enum_uint8 en_is_addba)
{
    oal_uint32       ul_max_ampdu_length;
    dmac_tid_stru   *pst_tid = &(pst_dmac_user->ast_tx_tid_queue[uc_tid]);
    mac_device_stru *pst_device = mac_res_get_dev(pst_dmac_user->st_user_base_info.uc_device_id);

    if(OAL_PTR_NULL == pst_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_BA, "{dmac_nontxop_txba_num_updata::pst_device null!}");
        return;
    }

    if ((WLAN_VHT_MODE == pst_dmac_user->st_user_base_info.en_cur_protocol_mode)
      || (WLAN_VHT_ONLY_MODE == pst_dmac_user->st_user_base_info.en_cur_protocol_mode))
    {
        ul_max_ampdu_length = pst_tid->st_ht_tx_hdl.ul_ampdu_max_size_vht;
    }
    else
    {
        ul_max_ampdu_length = pst_tid->st_ht_tx_hdl.us_ampdu_max_size;
    }

    if(ul_max_ampdu_length > 9000 && pst_tid->pst_ba_tx_hdl->uc_ampdu_max_num > 8)
    {
        if(en_is_addba)
        {
            pst_device->uc_tx_ba_num++;
        }
        else
        {
            if (0 != pst_device->uc_tx_ba_num)
            {
                pst_device->uc_tx_ba_num--;
            }
            else
            {
                OAM_ERROR_LOG0(0, OAM_SF_BA, "{dmac_nontxop_txba_num_updata::tx_ba_num make a mistake!}");
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_reset_tx_handle
 ��������  : ���÷���TX ba��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_ba_reset_tx_handle(mac_device_stru *pst_device, dmac_ba_tx_stru **ppst_tx_ba, oal_uint8 uc_tid)
{
    dmac_tid_stru  *pst_tid;
    dmac_user_stru *pst_dmac_user;

    if ((OAL_PTR_NULL == pst_device) || (OAL_PTR_NULL == *ppst_tx_ba))
    {
        //OAM_INFO_LOG0(0, OAM_SF_BA, "{dmac_ba_reset_tx_handle::pst_hal_device or ppst_tx_ba null.}\r\n");
        return;
    }

    oal_del_lut_index(pst_device->auc_tx_ba_index_table, (*ppst_tx_ba)->uc_tx_ba_lut);
    (*ppst_tx_ba)->en_is_ba = OAL_FALSE;


    /* pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user((*ppst_tx_ba)->st_alarm_data.us_mac_user_idx); */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user((*ppst_tx_ba)->us_mac_user_idx);
    if(OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_BA, "{dmac_ba_reset_tx_handle::pst_dmac_user null.}");
        return;
    }

    pst_tid = &(pst_dmac_user->ast_tx_tid_queue[uc_tid]);

    dmac_nontxop_txba_num_updata(pst_dmac_user, uc_tid, OAL_FALSE);

    /* ɾ�����TX-BA�����ص�HT��Ϣ */
    dmac_reset_tx_ba_state_prot(pst_device->pst_device_stru, pst_dmac_user, uc_tid);

    OAL_MEM_FREE(*ppst_tx_ba, OAL_TRUE);
    pst_tid->pst_ba_tx_hdl = OAL_PTR_NULL;

    /* ɾ��ʱ������TID����״̬ */
    dmac_tid_resume(pst_device->pst_device_stru, pst_tid, DMAC_TID_PAUSE_RESUME_TYPE_BA);
}

/*****************************************************************************
 �� �� ��  : dmac_ba_get_min_len_ht
 ��������  : htЭ��ģʽ�£���ȡmpdu��С���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��28��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint16  dmac_ba_get_min_len_ht(hal_tx_txop_alg_stru *pst_txop_alg,
                                                                wlan_phy_protocol_enum_uint8    en_protocl_mode,
                                                                hal_channel_assemble_enum_uint8 en_channel_bandwidth,
                                                                oal_bool_enum_uint8             en_short_gi_enable
                                                                )
{
    oal_uint16                      us_min_mpdu_len = 0;
    wlan_ht_mcs_enum_uint8          en_ht_mcs;

    en_ht_mcs = pst_txop_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs;

    if (en_ht_mcs >= WLAN_HT_MCS_BUTT  && en_ht_mcs != WLAN_HT_MCS32)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_ba_get_min_len_ht::invalid en_ht_mcs[%d].}", en_ht_mcs);
        return us_min_mpdu_len;
    }

    if (WLAN_HT_MCS32 == en_ht_mcs)
    {
        if (OAL_FALSE == en_short_gi_enable)
        {
            us_min_mpdu_len = WLAN_MIN_MPDU_LEN_FOR_MCS32;
        }
        else
        {
            us_min_mpdu_len = WLAN_MIN_MPDU_LEN_FOR_MCS32_SHORTGI;
        }
    }
    else if (WLAN_BAND_ASSEMBLE_20M == en_channel_bandwidth)
    {
        if (OAL_FALSE == en_short_gi_enable)
        {
            us_min_mpdu_len = g_aus_ht_20mhz_rate_lut[en_ht_mcs];
        }
        else
        {
            us_min_mpdu_len = g_aus_ht_20mhz_rate_lut_shortgi[en_ht_mcs];
        }
    }
    else if (WLAN_BAND_ASSEMBLE_40M == en_channel_bandwidth)
    {
        if (OAL_FALSE == en_short_gi_enable)
        {
            us_min_mpdu_len = g_aus_ht_40mhz_rate_lut[en_ht_mcs];
        }
        else
        {
            us_min_mpdu_len = g_aus_ht_40mhz_rate_lut_shortgi[en_ht_mcs];
        }
    }


    return us_min_mpdu_len;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_get_min_len_ht
 ��������  : htЭ��ģʽ�£���ȡmpdu��С���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��28��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint16  dmac_ba_get_min_len_vht(hal_tx_txop_alg_stru *pst_txop_alg,
                                                                wlan_phy_protocol_enum_uint8    en_protocl_mode,
                                                                hal_channel_assemble_enum_uint8 en_channel_bandwidth,
                                                                oal_bool_enum_uint8             en_short_gi_enable
                                                                )
{
    wlan_vht_mcs_enum_uint8         en_vht_mcs;
    wlan_nss_enum_uint8             en_nss;
    oal_uint16                      us_min_mpdu_len = 0;

    en_vht_mcs  = pst_txop_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_vht_mcs;
    en_nss      = pst_txop_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_nss_mode;
    /*OAM_INFO_LOG2(0, OAM_SF_BA, "{dmac_ba_get_min_len_vht::en_vht_mcs=%d en_nss=%d.}", en_vht_mcs, en_nss); */

    if (en_vht_mcs >= WLAN_VHT_MCS_BUTT || en_nss >= WLAN_TRIPLE_NSS)
    {
        OAM_ERROR_LOG2(0, OAM_SF_BA, "{dmac_ba_get_min_len_vht::array over flow, en_vht_mcs=%d en_nss=%d.}", en_vht_mcs, en_nss);

        return us_min_mpdu_len;
    }

    if (WLAN_BAND_ASSEMBLE_20M == en_channel_bandwidth)
    {
        if (OAL_FALSE == en_short_gi_enable)
        {
            us_min_mpdu_len = g_aus_vht_20mhz_rate_lut[en_nss][en_vht_mcs];
        }
        else
        {
            us_min_mpdu_len = g_aus_vht_20mhz_rate_lut_shortgi[en_nss][en_vht_mcs];
        }
    }
    else if (WLAN_BAND_ASSEMBLE_40M == en_channel_bandwidth)
    {
        if (OAL_FALSE == en_short_gi_enable)
        {
            us_min_mpdu_len = g_aus_vht_40mhz_rate_lut[en_nss][en_vht_mcs];
        }
        else
        {
            us_min_mpdu_len = g_aus_vht_40mhz_rate_lut_shortgi[en_nss][en_vht_mcs];
        }
    }
    else if(WLAN_BAND_ASSEMBLE_80M == en_channel_bandwidth)
    {
        if (OAL_FALSE == en_short_gi_enable)
        {
            us_min_mpdu_len = g_aus_vht_80mhz_rate_lut[en_nss][en_vht_mcs];
        }
        else
        {
            us_min_mpdu_len = g_aus_vht_80mhz_rate_lut_shortgi[en_nss][en_vht_mcs];
        }
    }

    return us_min_mpdu_len;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_calculate_min_mpdu_len
 ��������  : ����mcs��������Сmpdu����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��7��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  dmac_ba_calculate_min_mpdu_len(dmac_user_stru *pst_dmac_user, hal_tx_txop_alg_stru *pst_txop_alg)
{
    oal_uint16                      us_min_mpdu_len = 0;
    wlan_phy_protocol_enum_uint8    en_protocl_mode;
    hal_channel_assemble_enum_uint8 en_channel_bandwidth;
    oal_bool_enum_uint8             en_short_gi_enable;
    oal_uint8                       uc_shift_idx;
    oal_uint8                       uc_shift;

    if (0 == pst_dmac_user->st_user_base_info.st_ht_hdl.uc_min_mpdu_start_spacing)
    {
        return us_min_mpdu_len;
    }

    en_protocl_mode         = pst_txop_alg->ast_per_rate[0].rate_bit_stru.un_nss_rate.st_vht_nss_mcs.bit_protocol_mode;
    en_channel_bandwidth    = pst_txop_alg->st_rate.uc_channel_bandwidth;
    en_short_gi_enable      = pst_txop_alg->ast_per_rate[0].rate_bit_stru.bit_short_gi_enable;

    if (WLAN_HT_PHY_PROTOCOL_MODE == en_protocl_mode)
    {
        us_min_mpdu_len = dmac_ba_get_min_len_ht(pst_txop_alg, en_protocl_mode, en_channel_bandwidth, en_short_gi_enable);
    }
    else if (WLAN_VHT_PHY_PROTOCOL_MODE == en_protocl_mode)
    {
        us_min_mpdu_len = dmac_ba_get_min_len_vht(pst_txop_alg, en_protocl_mode, en_channel_bandwidth, en_short_gi_enable);
    }
    /*OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_BA, "{dmac_ba_calculate_min_mpdu_len::us_min_mpdu_len=%d.}", us_min_mpdu_len);*/

    if (0 == us_min_mpdu_len)
    {
        return us_min_mpdu_len;
    }

    uc_shift = (MAC_MAX_START_SPACING - pst_dmac_user->st_user_base_info.st_ht_hdl.uc_min_mpdu_start_spacing);
    /*OAM_INFO_LOG1(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_BA, "{dmac_ba_calculate_min_mpdu_len::uc_min_mpdu_start_spacing=%d.}",
                  pst_dmac_user->st_user_base_info.st_ht_hdl.uc_min_mpdu_start_spacing);*/

    /* start spacingΪ2���������ݣ�ʵ�ʵ�min mpdu lenΪ���ֵ���ƶ�Ӧ�ĸ��� */
    for (uc_shift_idx = 0; uc_shift_idx < uc_shift; uc_shift_idx++)
    {
        us_min_mpdu_len += 1;
        us_min_mpdu_len = us_min_mpdu_len >> 1;
    }

    us_min_mpdu_len = OAL_GET_4BYTE_ALIGN_VALUE(us_min_mpdu_len);

    return us_min_mpdu_len;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_send_bar
 ��������  : ����bar֡������ͣtid����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��7��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_ba_send_bar(dmac_ba_tx_stru *pst_tx_ba_handle, dmac_user_stru *pst_dmac_user, dmac_tid_stru *pst_tid_queue)
{
    dmac_vap_stru   *pst_dmac_vap;
    oal_netbuf_stru *pst_netbuf;
    oal_uint16       us_bar_len = 0;
    mac_tx_ctl_stru *pst_tx_ctl;
    oal_uint32       ul_ret;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_dmac_user->st_user_base_info.uc_vap_id);

    /* ����bar֡�ڴ� */
    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_SHORT_NETBUF_SIZE, OAL_NETBUF_PRIORITY_HIGH);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_ba_send_bar::pst_netbuf null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);

    oal_set_netbuf_prev(pst_netbuf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_netbuf, OAL_PTR_NULL);

    us_bar_len = dmac_ba_encap_blockack_req(pst_dmac_vap, pst_netbuf, pst_tx_ba_handle, pst_tid_queue->uc_tid);
    if (0 == us_bar_len)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_ba_send_bar::us_bar_len=0.}");
        oal_netbuf_free(pst_netbuf);

        return OAL_FAIL;
    }

    /* ��дnetbuf��cb�ֶΣ������͹���֡�ͷ�����ɽӿ�ʹ�� */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    OAL_MEMZERO(pst_tx_ctl, OAL_SIZEOF(mac_tx_ctl_stru));

    MAC_GET_CB_EVENT_TYPE(pst_tx_ctl)            = FRW_EVENT_TYPE_HOST_CRX;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl)           = (oal_uint8)pst_dmac_user->st_user_base_info.us_assoc_id;
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)              = OAL_FALSE;
    mac_set_cb_is_bar(pst_tx_ctl, OAL_TRUE);
    mac_set_cb_tid(pst_tx_ctl, pst_tid_queue->uc_tid);
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);
    MAC_GET_CB_FRAME_TYPE(pst_tx_ctl)            = WLAN_CONTROL;
    mac_set_cb_sub_type(pst_tx_ctl, WLAN_BLOCKACK_REQ);
    mac_set_cb_is_need_pause_tid(pst_tx_ctl, OAL_TRUE);

    /* ���÷��͹���֡�ӿ� */
    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_netbuf, us_bar_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_BA, "{dmac_ba_send_bar::dmac_tx_mgmt failed[%d].}", ul_ret);
        oal_netbuf_free(pst_netbuf);
        return ul_ret;
    }

    /* ��ͣ��tid�ĵ��ȵ�ҵ�� */
    dmac_tid_pause(pst_tid_queue, DMAC_TID_PAUSE_RESUME_TYPE_BA);

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 �� �� ��  : dmac_ba_addto_baw_multi
 ��������  : ���mpdu����ampdu ���¼�¼seq num�Ĵ���
 �������  : uc_new_mpdu_num   :  ampdu��ȫ��mpdu����Ŀ�� ����ampdu�ĺ���
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��16��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_INLINE void dmac_ba_addto_baw_multi(dmac_ba_tx_stru *pst_tx_ba_handle, oal_uint8 uc_new_mpdu_num)
{
    oal_uint16 us_first_mpdu_index;   /*�����´���ĵ�һ��mpdu index*/
    oal_uint16 us_last_mpdu_index;    /*�����´�������һ��mpdu index*/
    oal_uint16 us_first_mpdu_cindex;
    oal_uint16 us_last_mpdu_cindex;
    oal_uint16 us_cindex;

    /*��mpduΪ0����Ҫ�ƴ�����*/
    if (0 == uc_new_mpdu_num)
    {
        return ;
    }

    us_first_mpdu_index = DMAC_BA_INDEX(pst_tx_ba_handle->us_baw_start, DMAC_BA_SEQ_ADD(pst_tx_ba_handle->us_last_seq_num, 1));
    us_first_mpdu_cindex = (pst_tx_ba_handle->us_baw_head + us_first_mpdu_index) & (DMAC_TID_MAX_BUFS - 1);

    /*���������MPDU���к�*/
    pst_tx_ba_handle->us_last_seq_num = DMAC_BA_SEQ_ADD(pst_tx_ba_handle->us_last_seq_num, uc_new_mpdu_num);
    /*��ȡ�����MPDU�͵�һ��δȷ��MPDU֮������кŲ�ֵ*/
    us_last_mpdu_index  = DMAC_BA_INDEX(pst_tx_ba_handle->us_baw_start, pst_tx_ba_handle->us_last_seq_num);
    /*��ȡbitmap�У������MPDU��Ӧλ��*/
    us_last_mpdu_cindex = (pst_tx_ba_handle->us_baw_head + us_last_mpdu_index) & (DMAC_TID_MAX_BUFS - 1);

    /*��λbitmap�ж�Ӧbit*/
    if (us_first_mpdu_cindex <= us_last_mpdu_cindex)
    {
       for (us_cindex = us_first_mpdu_cindex; us_cindex <= us_last_mpdu_cindex; us_cindex++)
       {
           DMAC_TX_BUF_BITMAP_SET(pst_tx_ba_handle->aul_tx_buf_bitmap, us_cindex);
       }
    }
    else
    {
       for (us_cindex = us_first_mpdu_cindex ; us_cindex < DMAC_TID_MAX_BUFS; us_cindex++)
       {
           DMAC_TX_BUF_BITMAP_SET(pst_tx_ba_handle->aul_tx_buf_bitmap, us_cindex);
       }

       for (us_cindex = 0; us_cindex <= us_last_mpdu_cindex; us_cindex++)
       {
           DMAC_TX_BUF_BITMAP_SET(pst_tx_ba_handle->aul_tx_buf_bitmap, us_cindex);
       }
    }

    if (us_last_mpdu_index >= ((pst_tx_ba_handle->us_baw_tail - pst_tx_ba_handle->us_baw_head) & (DMAC_TID_MAX_BUFS - 1)))
    {
        pst_tx_ba_handle->us_baw_tail = us_last_mpdu_cindex;
        OAL_INCR(pst_tx_ba_handle->us_baw_tail, DMAC_TID_MAX_BUFS);
    }
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_ba_window_ahead
 ��������  : ����ba���ڵ�ssn
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_move_ba_window_ahead(dmac_ba_tx_stru *pst_ba_hdl, oal_uint16 us_lsn)
{
    OAM_ERROR_LOG0(0, OAM_SF_BA, "{dmac_move_ba_window_ahead::ATTENTION: the seq num of a retried packet has been reassigned by HW.}");

    OAL_MEMZERO(pst_ba_hdl->aul_tx_buf_bitmap, OAL_SIZEOF(oal_uint32) * DMAC_TX_BUF_BITMAP_WORDS);
    dmac_ba_update_start_seq_num(pst_ba_hdl, us_lsn + 1);
}

/*****************************************************************************
 �� �� ��  : dmac_ba_get_aggr_mpdu_num_limit
 ��������  : ���ߵ����㷨���Է��͵ĸ���
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
oal_uint8  dmac_ba_get_aggr_mpdu_num_limit(dmac_tid_stru *pst_tid_queue)
{
    oal_uint8 uc_mpdu_num = 0;
    dmac_ba_tx_stru *pst_tx_ba;
    oal_uint16  us_baw_end = 0;

    pst_tx_ba = pst_tid_queue->pst_ba_tx_hdl;
    if (OAL_PTR_NULL == pst_tx_ba)
    {
        uc_mpdu_num = 1;
        return uc_mpdu_num;
    }

    us_baw_end = DMAC_BA_SEQNO_ADD(pst_tx_ba->us_baw_start, pst_tx_ba->us_baw_size);
    us_baw_end = DMAC_BA_SEQNO_SUB(us_baw_end, 1);

    uc_mpdu_num = (oal_uint8)DMAC_BA_SEQNO_SUB(us_baw_end, pst_tx_ba->us_last_seq_num);

    return uc_mpdu_num;
}

/*****************************************************************************
 �� �� ��  : dmac_is_ba_setup
 ��������  : device���Ƿ��н���ba
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��12��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum dmac_is_ba_setup(oal_void)
{
    oal_uint8                  uc_vap_idx;
    mac_device_stru           *pst_mac_device;
    mac_vap_stru               *pst_mac_vap;
    mac_user_stru              *pst_user;
    dmac_user_stru             *pst_dmac_user;
    oal_dlist_head_stru        *pst_entry;
    dmac_tid_stru              *pst_tid_queue;
    oal_uint32                  ul_tid_idx;

    pst_mac_device = mac_res_get_dev(0);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_is_ba_setup::pst_mac_device null.}");
        return OAL_FALSE;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_is_ba_setup pst_mac_vap is null.}");
            continue;
        }
        if ((MAC_VAP_STATE_UP != pst_mac_vap->en_vap_state) &&
            (MAC_VAP_STATE_PAUSE != pst_mac_vap->en_vap_state))
        {
            continue;
        }

        /* ����vap�������û�,pause tid ���� */
        OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
        {
            pst_user      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
            pst_dmac_user = (dmac_user_stru *)pst_user;
            if (OAL_PTR_NULL == pst_dmac_user)
            {
                OAM_WARNING_LOG0(0, OAM_SF_ANY,"{dmac_is_ba_setup::OAL_DLIST_GET_ENTRY failed.");
                continue;
            }
            /* �鿴ba ��� */
            for (ul_tid_idx = 0; ul_tid_idx < WLAN_TID_MAX_NUM; ul_tid_idx++)
            {
                pst_tid_queue = &(pst_dmac_user->ast_tx_tid_queue[ul_tid_idx]);
                if ((OAL_PTR_NULL != pst_tid_queue->pst_ba_rx_hdl) || (OAL_PTR_NULL != pst_tid_queue->pst_ba_tx_hdl))
                {
                    return OAL_TRUE;
                }
            }
        }

    }

    return OAL_FALSE;
}

#ifdef _PRE_DEBUG_MODE
#ifdef _PRE_WLAN_FEATURE_AMPDU
//#if ((_PRE_TARGET_PRODUCT_TYPE_5610DMB != _PRE_CONFIG_TARGET_PRODUCT) )
#if 0
/*****************************************************************************
 �� �� ��  : dmac_ba_track_tail_update
 ��������  : ����track tail
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��10��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_ba_track_tail_update(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx)
{
    dmac_tx_ba_track_stru *pst_ba_track_log = OAL_PTR_NULL;

    if (uc_lut_idx >= HAL_MAX_AMPDU_LUT_SIZE)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_ba_track_tail_update::invalid uc_lut_idx[%d].}", uc_lut_idx);
        return;
    }

    pst_ba_track_log = &g_ast_tx_ba_track[uc_device_id][uc_lut_idx];

    pst_ba_track_log->us_track_tail = (pst_ba_track_log->us_track_tail + 1) & (OAM_SEQ_TRACK_NUM - 1);

    if (pst_ba_track_log->us_track_tail == pst_ba_track_log->us_track_head)
    {
        pst_ba_track_log->us_track_head = (pst_ba_track_log->us_track_head + 1) & (OAM_SEQ_TRACK_NUM - 1);
    }

    /*��¼����*/
    OAL_MEMZERO(&pst_ba_track_log->ast_seq_bitmap_log[pst_ba_track_log->us_track_tail], sizeof(dmac_seq_track_stru));

    /*��֤stop���ܼ�¼10��*/
    if (pst_ba_track_log->uc_track_remain != 0)
    {
        pst_ba_track_log->uc_track_remain--;
        if (0 == pst_ba_track_log->uc_track_remain)
        {
            pst_ba_track_log->en_track_off = OAL_TRUE;
        }
    }
}

/*****************************************************************************
 �� �� ��  : dmac_ba_track_ba_hander
 ��������  : ��¼����BA״��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��10��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_ba_track_ba_hander(oal_uint8 uc_device_id, dmac_ba_tx_stru *pst_tx_ba, oal_uint8 uc_tid, oal_bool_enum_uint8 en_is_before_tx)
{
    oal_uint16 us_tail;
    dmac_tx_ba_track_stru *pst_ba_track_log = OAL_PTR_NULL;

    if (pst_tx_ba->uc_tx_ba_lut >= HAL_MAX_AMPDU_LUT_SIZE)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_ba_track_ba_hander::invalid uc_lut_idx[%d].}", pst_tx_ba->uc_tx_ba_lut);
        return;
    }

    pst_ba_track_log = &g_ast_tx_ba_track[uc_device_id][pst_tx_ba->uc_tx_ba_lut];

    if (OAL_TRUE == pst_ba_track_log->en_track_off)
    {
        return;
    }

    us_tail = pst_ba_track_log->us_track_tail;
    if (us_tail > OAM_SEQ_TRACK_NUM - 1)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_ba_track_ba_hander::invalid us_tail[%d].}", us_tail);
        return;
    }

    oal_memcopy(pst_ba_track_log->ast_seq_bitmap_log[pst_ba_track_log->us_track_tail].aul_bitmap,
                pst_tx_ba->aul_tx_buf_bitmap,
                DMAC_TX_BUF_BITMAP_WORDS * OAL_SIZEOF(oal_uint32));
    pst_ba_track_log->ast_seq_bitmap_log[us_tail].us_baw_tail           = pst_tx_ba->us_baw_tail;
    pst_ba_track_log->ast_seq_bitmap_log[us_tail].us_baw_head           = pst_tx_ba->us_baw_head;
    pst_ba_track_log->ast_seq_bitmap_log[us_tail].us_lsn                = pst_tx_ba->us_last_seq_num;
    pst_ba_track_log->ast_seq_bitmap_log[us_tail].us_seq_start          = pst_tx_ba->us_baw_start;
    pst_ba_track_log->ast_seq_bitmap_log[us_tail].uc_tid                = uc_tid;
    pst_ba_track_log->ast_seq_bitmap_log[us_tail].en_is_before_tx_track = en_is_before_tx;

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_track_report_seqnum
 ��������  : ��¼���������������Ҫ�����seqnum
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_ba_track_report_seqnum(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx, oal_uint8 uc_dscr_idx, oal_uint16 us_seq_num)
{
    dmac_tx_ba_track_stru *pst_ba_track_log = OAL_PTR_NULL;

    if (uc_lut_idx >= HAL_MAX_AMPDU_LUT_SIZE)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_ba_track_report_seqnum::invalid uc_lut_idx[%d].}", uc_lut_idx);
        return ;
    }

    pst_ba_track_log = &g_ast_tx_ba_track[uc_device_id][uc_lut_idx];

    if (OAL_TRUE == pst_ba_track_log->en_track_off)
    {
        return ;
    }

    if (uc_dscr_idx < WLAN_AMPDU_TX_MAX_NUM_DEBUG)
    {
        pst_ba_track_log->ast_seq_bitmap_log[pst_ba_track_log->us_track_tail].un_mix_dscr.st_report.aus_report_seqnum[uc_dscr_idx] = us_seq_num;
    }

    return ;
}



/*****************************************************************************
 �� �� ��  : dmac_ba_track_tid_queue
 ��������  : ��¼tid�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_ba_track_tid_queue(oal_uint8 uc_device_id, hal_to_dmac_device_stru * pst_hal_device, oal_uint8 uc_lut_idx, dmac_tid_stru *pst_tid_queue)
{
    dmac_tx_ba_track_stru *pst_ba_track_log = OAL_PTR_NULL;
    oal_dlist_head_stru   *pst_dlist_pos    = OAL_PTR_NULL;
    oal_dlist_head_stru   *pst_dlist_n      = OAL_PTR_NULL;
    hal_tx_dscr_stru      *pst_dscr         = OAL_PTR_NULL;
    oal_uint16             us_seq_num       = 0;
    oal_uint16             us_tail          = 0;
    oal_uint8              uc_dscr_idx      = 0;

    if (uc_lut_idx >= HAL_MAX_AMPDU_LUT_SIZE)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_ba_track_tid_queue: invalid uc_lut_idx[%d].}", uc_lut_idx);
        return ;
    }

    pst_ba_track_log = &g_ast_tx_ba_track[uc_device_id][uc_lut_idx];

    if (OAL_TRUE == pst_ba_track_log->en_track_off)
    {
        return ;
    }

    us_tail = pst_ba_track_log->us_track_tail;

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, &pst_tid_queue->st_hdr)
    {
        pst_dscr = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
        hal_tx_get_dscr_seq_num(pst_hal_device, pst_dscr, &us_seq_num);

        if (uc_dscr_idx < WLAN_AMPDU_TX_MAX_NUM_DEBUG)
        {
            pst_ba_track_log->ast_seq_bitmap_log[us_tail].aus_tid_seqnum[uc_dscr_idx++] = us_seq_num;
        }
    }

    pst_ba_track_log->ast_seq_bitmap_log[us_tail].uc_tid_record_mpdu_num = uc_dscr_idx;
    pst_ba_track_log->ast_seq_bitmap_log[us_tail].uc_tid_retry_mpdu_num  = pst_tid_queue->uc_retry_num;
    pst_ba_track_log->ast_seq_bitmap_log[us_tail].us_tid_total_mpdu_num = pst_tid_queue->us_mpdu_num;

	return ;

}

/*****************************************************************************
 �� �� ��  : dmac_ba_track_schedule_seqnum
 ��������  : ��¼���ȶ��е�seqnum
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_ba_track_schedule_seqnum(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx, oal_dlist_head_stru *pst_sch_dscr_head)
{
    dmac_tx_ba_track_stru *pst_ba_track_log = OAL_PTR_NULL;
    oal_dlist_head_stru   *pst_dlist_pos    = OAL_PTR_NULL;
    oal_dlist_head_stru   *pst_dlist_n      = OAL_PTR_NULL;
    hal_tx_dscr_stru      *pst_dscr         = OAL_PTR_NULL;
    mac_tx_ctl_stru       *pst_cb           = OAL_PTR_NULL;
    oal_netbuf_stru       *pst_netbuf       = OAL_PTR_NULL;
    mac_ieee80211_frame_stru *pst_frame_hdr = OAL_PTR_NULL;
    oal_uint16             us_tail          = 0;
    oal_uint8              uc_dscr_idx      = 0;

    if (uc_lut_idx >= HAL_MAX_AMPDU_LUT_SIZE)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_ba_track_schedule_seqnum: invalid uc_lut_idx[%d].}", uc_lut_idx);
        return ;
    }

    pst_ba_track_log = &g_ast_tx_ba_track[uc_device_id][uc_lut_idx];
    if (OAL_TRUE == pst_ba_track_log->en_track_off)
    {
        return ;
    }

    us_tail = pst_ba_track_log->us_track_tail;

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_dlist_pos, pst_dlist_n, pst_sch_dscr_head)
    {
        pst_dscr      = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_dlist_pos, hal_tx_dscr_stru, st_entry);
        pst_netbuf    = pst_dscr->pst_skb_start_addr;
        pst_cb        = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
        pst_frame_hdr = pst_cb->pst_frame_header;

        if (uc_dscr_idx < WLAN_AMPDU_TX_MAX_NUM_DEBUG)
        {
            pst_ba_track_log->ast_seq_bitmap_log[us_tail].un_mix_dscr.st_schedule.aus_schedule_seqnum[uc_dscr_idx++] = pst_frame_hdr->bit_seq_num;
        }
    }

    pst_ba_track_log->ast_seq_bitmap_log[us_tail].un_mix_dscr.st_schedule.uc_schedule_mpdu_num = uc_dscr_idx;

	return ;
}

/*****************************************************************************
 �� �� ��  : dmac_ba_track_stop
 ��������  : ֹͣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_ba_track_stop(oal_uint8 uc_device_id, oal_uint8 uc_lut_idx)
{
    dmac_tx_ba_track_stru *pst_ba_track_log = OAL_PTR_NULL;

    if (uc_lut_idx >= HAL_MAX_AMPDU_LUT_SIZE)
    {
        OAM_ERROR_LOG1(0, OAM_SF_BA, "{dmac_ba_track_stop::invalid uc_lut_idx[%d].}", uc_lut_idx);
        return;
    }

    pst_ba_track_log = &g_ast_tx_ba_track[uc_device_id][uc_lut_idx];

    pst_ba_track_log->uc_track_remain = 10;

    return;
}
//#endif
#endif
#endif
#endif


/*lint -e578*//*lint -e19*/
oal_module_symbol(dmac_ba_get_aggr_mpdu_num_limit);
/*lint +e578*//*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

