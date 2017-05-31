/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_mgmt_classifier.c
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2012��12��18��
  ����޸�   :
  ��������   : dmac ����֡����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��18��
    ��    ��   : t00231215
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
#include "mac_frame.h"
#include "mac_resource.h"
#include "mac_ie.h"
#include "dmac_ext_if.h"
#include "dmac_main.h"
#include "dmac_vap.h"
#include "dmac_rx_data.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_blockack.h"
#include "dmac_psm_ap.h"
#include "dmac_mgmt_ap.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_scan.h"
#include "dmac_alg_if.h"
#include "mac_vap.h"
#include "dmac_11w.h"
#include "dmac_dft.h"
#include "dmac_mgmt_sta.h"
#include "dmac_p2p.h"
#include "oal_net.h"
#include "dmac_beacon.h"
#include "dmac_dft.h"
#include "dmac_chan_mgmt.h"
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_psm_sta.h"
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
#include "dmac_p2p.h"
#endif

#ifdef _PRE_WLAN_FEATURE_11K
#include "dmac_11k.h"
#endif

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
#include "hal_ext_if.h"
#include "dmac_config.h"
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_device.h"
#include "dmac_resource.h"
#endif

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
#include "pm_extern.h"
#endif
#ifdef _PRE_WLAN_FEATURE_WMMAC
#include "dmac_wmmac.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_CLASSIFIER_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_rx_process_control
 ��������  : ����֡����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_process_control(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint8 *pen_go_on)
{
    dmac_rx_ctl_stru                 *pst_rx_ctl;
    mac_ieee80211_frame_stru         *pst_frame_hdr;
    mac_ieee80211_pspoll_frame_stru  *pst_pspoll_frame_hdr;
    oal_uint8                        *puc_payload;
    dmac_tid_stru                    *pst_tid;
    dmac_user_stru                   *pst_ta_user;
    oal_uint8                        *puc_sa_addr;
    oal_uint16                        us_user_idx = 0xFFFF;
    oal_uint8                         uc_tidno;
    oal_uint32                        ul_rslt;

    *pen_go_on = OAL_FALSE;//Ĭ�ϲ��ϱ�control֡

    /* ��ȡ֡ͷ��Ϣ */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru  *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));
    /* ����ACK֡ */
    if (WLAN_ACK == pst_frame_hdr->st_frame_control.bit_sub_type)
    {
#if(defined(_PRE_PRODUCT_ID_HI110X_DEV))
    /*****************************************************************************/
        /*��Ϣ�ϱ���ʱʹ�ã��㷨�ṩ��ɾ���ò���*/
        /* ��ȡԴ��ַ */
        puc_sa_addr = pst_frame_hdr->auc_address2;

        /*  ��ȡ�û�ָ�� */
        ul_rslt = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info), puc_sa_addr, &us_user_idx);
        /*
            �����û�ʧ��: �����쳣�����أ�����Χ�ͷſռ�
            û���ҵ���Ӧ���û�: �������ִ��
        */
        if (OAL_SUCC != ul_rslt)
        {
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                             "{dmac_rx_process_control::mac_vap_find_user_by_macaddr failed[%d]}", ul_rslt);

            return ul_rslt;
        }

        /* ת��Ϊdmac user */
        pst_ta_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
        if (OAL_PTR_NULL != pst_ta_user)
        {
            pst_ta_user->st_query_stats.ul_signal = pst_rx_ctl->st_rx_statistic.c_rssi_dbm;
        /*pst_ta_user->st_query_stats.ul_signal = smooth_signal_rssi(pst_ta_user->st_query_stats.ul_signal,pst_rx_ctl->st_rx_statistic.c_rssi_dbm);*/
        }
    /*****************************************************************************/
#endif
        //OAM_INFO_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::ack frame.}\r\n");
        OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_ack_dropped, 1);
        return OAL_SUCC;
    }

    /* ��ȡԴ��ַ */
    puc_sa_addr = pst_frame_hdr->auc_address2;

    /*  ��ȡ�û�ָ�� */
    ul_rslt = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info), puc_sa_addr, &us_user_idx);
    /*
        �����û�ʧ��: �����쳣�����أ�����Χ�ͷſռ�
        û���ҵ���Ӧ���û�: �������ִ��
    */
    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                         "{dmac_rx_process_control::mac_vap_find_user_by_macaddr failed[%d]}", ul_rslt);

        return ul_rslt;
    }

    /* ת��Ϊdmac user */
    pst_ta_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_ta_user)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::pst_ta_user null, us_user_idx=%d.}", us_user_idx);

        mac_rx_report_80211_frame((oal_uint8 *)&(pst_dmac_vap->st_vap_base_info),
                                  (oal_uint8 *)&(pst_rx_ctl->st_rx_info),
                                  pst_netbuf,
                                  OAM_OTA_TYPE_RX_DMAC_CB);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �����ҵ��û�: ����ʱ��� */
    pst_ta_user->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    if (WLAN_BLOCKACK_REQ == (pst_frame_hdr->st_frame_control.bit_sub_type))    /* BAR 1000 */
    {
        /* ��ȡ֡ͷ��payloadָ��*/
        puc_payload = MAC_GET_RX_PAYLOAD_ADDR(&(pst_rx_ctl->st_rx_info), pst_netbuf);

        /*************************************************************************/
        /*                     BlockAck Request Frame Format                     */
        /* --------------------------------------------------------------------  */
        /* |Frame Control|Duration|DA|SA|BAR Control|BlockAck Starting    |FCS|  */
        /* |             |        |  |  |           |Sequence number      |   |  */
        /* --------------------------------------------------------------------  */
        /* | 2           |2       |6 |6 |2          |2                    |4  |  */
        /* --------------------------------------------------------------------  */
        /*                                                                       */
        /*************************************************************************/

        uc_tidno        = (puc_payload[1] & 0xF0) >> 4;
        //us_start_seqnum = mac_get_bar_start_seq_num(puc_payload);

        /*drop bar frame when tid num nonsupport*/
        if(uc_tidno >= WLAN_TID_MAX_NUM)
        {
            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_bar_process_dropped, 1);
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control:: invaild tidno:%d.}", (oal_int32)uc_tidno);
            return OAL_SUCC;
        }

        pst_tid = &(pst_ta_user->ast_tx_tid_queue[uc_tidno]);
        if (OAL_PTR_NULL == pst_tid->pst_ba_rx_hdl)
        {
            OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_process_control::pst_ba_rx_hdl null.}");
            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_bar_process_dropped, 1);
            dmac_mgmt_delba(pst_dmac_vap, pst_ta_user, uc_tidno, MAC_RECIPIENT_DELBA, MAC_QSTA_SETUP_NOT_DONE);
            return OAL_ERR_CODE_PTR_NULL;
        }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /*HOST������ʱ,Bar֡�ϴ���Hmac����*/
        if(OAL_FALSE == PM_WLAN_IsHostSleep())
#endif
        {
            *pen_go_on = OAL_TRUE;
        }
        return OAL_SUCC;

    }

    if (WLAN_PS_POLL == (pst_frame_hdr->st_frame_control.bit_sub_type))         /* PS_POLL 1010 */
    {
        /* �����ps-poll����Ӧ�ð�֡ͷת��Ϊps-poll��֡ͷ��ʽ */
        pst_pspoll_frame_hdr = (mac_ieee80211_pspoll_frame_stru  *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));

        /* AP��Ҫ�ж�PS_POLL�����AID��AP������û�AID�Ƿ�һ��,��һ�µĻ�ֱ�Ӻ��� */
        if (pst_pspoll_frame_hdr->bit_aid_value != pst_ta_user->st_user_base_info.us_assoc_id)
        {
            OAM_ERROR_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                           "{dmac_rx_process_control::AID in pspoll and AID in user_stru mismatch, bit_aid_value=%d us_assoc_id=%d.}",
                           pst_pspoll_frame_hdr->bit_aid_value, pst_ta_user->st_user_base_info.us_assoc_id);

            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_pspoll_process_dropped, 1);
            return OAL_FAIL;
        }

        /* ֱ�ӵ���PS_POLL, ����ʹ��֡���ͼ��� */
        ul_rslt = dmac_psm_resv_ps_poll(pst_dmac_vap, pst_ta_user);
        if (OAL_SUCC != ul_rslt)
        {
            OAM_STAT_VAP_INCR(pst_dmac_vap->st_vap_base_info.uc_vap_id, rx_pspoll_process_dropped, 1);
            return ul_rslt;
        }
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_BTCOEX
OAL_STATIC oal_uint32 dmac_btcoex_wlan_occupied_timeout_callback(oal_void *p_arg)
{
    dmac_vap_stru *pst_dmac_vap = (dmac_vap_stru *)p_arg;
    oal_uint8 *puc_occupied_times = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied.uc_occupied_times);
    if ((*puc_occupied_times) > 0)
    {
        OAM_WARNING_LOG1(0, OAM_SF_COEX, "{dmac_btcoex_wlan_occupied_timeout_callback::g_occupied_times = %d}" , *puc_occupied_times);
        (*puc_occupied_times)--;
        hal_set_btcoex_occupied_period(OCCUPIED_PERIOD);
    }
    else
    {
        FRW_TIMER_DESTROY_TIMER(&(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied.bt_coex_occupied_timer));
    }
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_rx_mgmt_update_tsf
 ��������  : DMAC���չ���֡����TSF
 �������  : pst_dmac_vap
             pst_frame_hdr
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��25��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_void dmac_rx_mgmt_update_tsf(dmac_vap_stru *pst_dmac_vap,
                                            mac_ieee80211_frame_stru *pst_frame_hdr,
                                            mac_device_stru    *pst_mac_device,
                                            oal_netbuf_stru    *pst_netbuf)
{
    /* ɨ��״̬��STA UP/PAUSE״̬���յ�Beacon��probe rsp֡����TSF */
    if (OAL_TRUE == pst_mac_device->st_scan_params.bit_is_p2p0_scan)
    {
        return;
    }

    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state)  ||
        ((WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
          && ((MAC_VAP_STATE_PAUSE  == pst_dmac_vap->st_vap_base_info.en_vap_state)
#ifdef _PRE_WLAN_FEATURE_ROAM
          || (MAC_VAP_STATE_ROAMING == pst_dmac_vap->st_vap_base_info.en_vap_state)
#endif
          || (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state))))
    {
        if (!OAL_MEMCMP(pst_frame_hdr->auc_address3, pst_dmac_vap->st_vap_base_info.auc_bssid, WLAN_MAC_ADDR_LEN))
        {
             if (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type)
             {
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
                dmac_get_tsf_from_bcn(pst_dmac_vap, pst_netbuf);
#endif
                hal_sta_tsf_save(pst_dmac_vap->pst_hal_vap, OAL_TRUE);
             }
             else if (WLAN_PROBE_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
             {
                 /* ��ܲ���AP���͵�beacon֡��probe rsp֡��Я����tsfֵ��һ�µ����� */
                 hal_sta_tsf_restore(pst_dmac_vap->pst_hal_vap);
             }
        }
        else
        {
            if ((WLAN_PROBE_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
            || (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type))
            {
                hal_sta_tsf_restore(pst_dmac_vap->pst_hal_vap);
            }
        }
    }

}
/*****************************************************************************
 �� �� ��  : dmac_rx_notify_channel_width
 ��������  : sta��UP״̬�´���"Notify Channel Width"֡�ϱ�����
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             pst_netbuf  : "Notify Channel Width֡"���ڵ�netbuf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��2��14��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_void  dmac_rx_notify_channel_width(mac_vap_stru *pst_mac_vap,oal_uint8 *puc_data,dmac_user_stru *pst_dmac_user)
{
    wlan_bw_cap_enum_uint8      en_bwcap_vap;

    en_bwcap_vap = puc_data[MAC_ACTION_OFFSET_ACTION + 1] & BIT0;

    /* ����ģʽδ�ı�or HT40��ֹ or��Ҫ����notify channel width ��action�ϱ� */
    if ((pst_dmac_user->st_user_base_info.en_avail_bandwidth == en_bwcap_vap)
         ||(OAL_FALSE == mac_mib_get_FortyMHzOperationImplemented(pst_mac_vap)))
    {
        return;
    }

    pst_mac_vap->st_ch_switch_info.bit_wait_bw_change = OAL_TRUE;

    /* ���µ�"STA Channel Width" field */
    mac_ie_proc_chwidth_field(pst_mac_vap, &(pst_dmac_user->st_user_base_info),en_bwcap_vap);

    /* �����㷨�ı����֪ͨ�� */
    dmac_alg_cfg_user_bandwidth_notify(pst_mac_vap, &(pst_dmac_user->st_user_base_info));
}

/*****************************************************************************
 �� �� ��  : dmac_sta_up_rx_ch_switch
 ��������  : sta��UP״̬�´���"Notify Channel Width"֡�ϱ�����
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             pst_netbuf  : "Notify Channel Width֡"���ڵ�netbuf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��2��14��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_void  dmac_sta_up_rx_ch_switch(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_frame_body,oal_uint16  us_framebody_len)
{
    oal_uint8          *puc_ie                = OAL_PTR_NULL;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_frame_body)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_sta_up_rx_ch_switch::param null,pst_mac_vap = [%p],puc_frame_body = [%p]}",
                       pst_mac_vap,puc_frame_body);
        return;
    }

    if (us_framebody_len <= (MAC_ACTION_OFFSET_ACTION + 1))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_sta_up_rx_ch_switch::framebody_len[%d]}", us_framebody_len);
        return;
    }

    us_framebody_len -= (MAC_ACTION_OFFSET_ACTION + 1);
    puc_frame_body   += (MAC_ACTION_OFFSET_ACTION + 1);


    puc_ie = mac_find_ie(MAC_EID_CHANSWITCHANN, puc_frame_body, us_framebody_len);
    if (OAL_PTR_NULL != puc_ie)
    {
        dmac_ie_proc_ch_switch_ie(pst_mac_vap, puc_ie, MAC_EID_CHANSWITCHANN);
    }

    puc_ie = mac_find_ie(MAC_EID_SEC_CH_OFFSET, puc_frame_body, us_framebody_len);
    if ((OAL_PTR_NULL != puc_ie) && (puc_ie[1] >= MAC_SEC_CH_OFFSET_IE_LEN))
    {
        pst_mac_vap->st_ch_switch_info.en_new_bandwidth = mac_get_bandwidth_from_sco(puc_ie[MAC_IE_HDR_LEN]);
    }

    puc_ie = mac_find_ie(MAC_EID_WIDE_BW_CH_SWITCH, puc_frame_body, us_framebody_len);
    if ((OAL_PTR_NULL != puc_ie) && (OAL_TRUE == mac_mib_get_VHTOptionImplemented(pst_mac_vap)))
    {
        dmac_ie_proc_wide_bandwidth_ie(pst_mac_vap, puc_ie);
    }
}
/*****************************************************************************
 �� �� ��  : dmac_sta_up_rx_ext_ch_switch
 ��������  : STA up״̬����Extended Channel Switch Announcement֡����
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             pst_netbuf : ����Extended Channel Switch Announcement֡��netbuf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_sta_up_rx_ext_ch_switch(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_frame_body,oal_uint16 us_framebody_len)
{
    oal_uint16          us_index;
    oal_uint8          *puc_wide_bw_ch_switch_ie = OAL_PTR_NULL;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_frame_body)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{dmac_sta_up_rx_ext_ch_switch::param null,pst_mac_vap = [%p],pst_netbuf = [%p]}",
                       pst_mac_vap, puc_frame_body);
        return;
    }

    if (OAL_FALSE == mac_mib_get_SpectrumManagementImplemented(pst_mac_vap))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_sta_up_rx_ext_ch_switch::Ignoring Spectrum Management frames.}");
        return;
    }

    dmac_ie_proc_ch_switch_ie(pst_mac_vap, puc_frame_body, MAC_EID_EXTCHANSWITCHANN);

    /* �����֧��VHT������Ժ�����Wide Bandwidth Channel Switch IE */
    if (OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
    {
        return;
    }

    us_index = 6;

    puc_wide_bw_ch_switch_ie = mac_find_ie(MAC_EID_WIDE_BW_CH_SWITCH, &puc_frame_body[us_index], (oal_int32)(us_framebody_len - us_index));
    if (OAL_PTR_NULL != puc_wide_bw_ch_switch_ie)
    {
        dmac_ie_proc_wide_bandwidth_ie(pst_mac_vap, puc_wide_bw_ch_switch_ie);
    }
}

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
/*****************************************************************************
 �� �� ��  : dmac_mgmt_rx_opmode_notify_frame
 ��������  : �ӿտڽ���opmode_notify֡�Ĵ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��7��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_mgmt_rx_opmode_notify_frame(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 *puc_frame_payload)
{
    mac_opmode_notify_stru     *pst_opmode_notify = OAL_PTR_NULL;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_mac_user) || (OAL_PTR_NULL == puc_frame_payload))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "{dmac_mgmt_rx_opmode_notify_frame::pst_hmac_vap = [%p], pst_mac_user = [%p],pst_netbuf = [%p]!}\r\n",
                        pst_mac_vap, pst_mac_user, puc_frame_payload);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
        || (OAL_FALSE == mac_mib_get_OperatingModeNotificationImplemented(pst_mac_vap)))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX, "{dmac_mgmt_rx_opmode_notify_frame::the vap is not support OperatingModeNotification!}");
        return OAL_SUCC;
    }

    /****************************************************/
    /*   OperatingModeNotification Frame - Frame Body   */
    /* -------------------------------------------------*/
    /* |   Category   |   Action   |   OperatingMode   |*/
    /* -------------------------------------------------*/
    /* |   1          |   1        |   1               |*/
    /* -------------------------------------------------*/
    /*                                                  */
    /****************************************************/

    /* ��ȡpst_opmode_notify��ָ�� */
    pst_opmode_notify = (mac_opmode_notify_stru *)(puc_frame_payload + MAC_ACTION_OFFSET_ACTION + 1);

    return dmac_ie_proc_opmode_notify(pst_mac_user, pst_mac_vap, pst_opmode_notify);
}

#endif
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : dmac_send_2040_coext_mgmt_frame_sta
 ��������  : STA����20/40 �������֡(����Trigger Event A & Trigger Event B��д)
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_send_2040_coext_mgmt_frame_sta(mac_vap_stru *pst_mac_vap)
{
    dmac_vap_stru     *pst_dmac_vap;
    oal_netbuf_stru   *pst_netbuf = OAL_PTR_NULL;
    mac_tx_ctl_stru   *pst_tx_ctl;
    oal_uint16         us_frame_len = 0;
    oal_uint8          uc_coext_info = 0;
    oal_uint32         ul_channel_report = pst_mac_vap->st_ch_switch_info.ul_chan_report_for_te_a;

    /* ����dot11FortyMHzIntolerant��д��field */
    if ( (OAL_TRUE == mac_mib_get_FortyMHzIntolerant(pst_mac_vap)) ||
         (OAL_TRUE == pst_mac_vap->st_ch_switch_info.en_te_b))
    {
        uc_coext_info |= BIT1;
    }

    /* ����⵽Trigger Event Bʱ�����ô�fieldΪ1 */
    if (0 != ul_channel_report)
    {
        uc_coext_info |= BIT2;
    }

    /* ����ϴ�ɨ���� */
    pst_mac_vap->st_ch_switch_info.ul_chan_report_for_te_a = 0;
    pst_mac_vap->st_ch_switch_info.en_te_b = OAL_FALSE;

    /* �������֡�ڴ� */
    pst_netbuf = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{dmac_send_2040_coext_mgmt_frame_sta::pst_netbuf null.}");
        return;
    }

    OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);
    oal_set_netbuf_prev(pst_netbuf, OAL_PTR_NULL);
    oal_set_netbuf_next(pst_netbuf, OAL_PTR_NULL);

    /* ��װ20/40 �������֡ */
    us_frame_len = mac_encap_2040_coext_mgmt((oal_void *)pst_mac_vap, pst_netbuf, uc_coext_info, ul_channel_report);

    oal_netbuf_put(pst_netbuf, us_frame_len);

    /* ��дnetbuf��cb�ֶΣ������͹���֡�ͷ�����ɽӿ�ʹ�� */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    OAL_MEMZERO(pst_tx_ctl, OAL_NETBUF_CB_SIZE());
    MAC_GET_CB_MPDU_LEN(pst_tx_ctl) = us_frame_len - MAC_80211_FRAME_LEN;
    MAC_GET_CB_TX_USER_IDX(pst_tx_ctl) = pst_mac_vap->uc_assoc_vap_id;//���͸�����ap�ĵ���,�úϷ�user idx
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040,
        "{dmac_send_2040_coext_mgmt_frame_sta::uc_coext_info=%d, ul_channel_report=%d}",
        uc_coext_info, ul_channel_report);

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);

    if (OAL_SUCC != dmac_tx_mgmt(pst_dmac_vap, pst_netbuf, us_frame_len))
    {
        oal_netbuf_free(pst_netbuf);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_sta_up_rx_2040_coext
 ��������  : STA��UP״̬�´�����յ���20/40�������֡
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             pst_netbuf : ����20/40�������֡��netbufָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_sta_up_rx_2040_coext(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_frame_body)
{
    /* ���STA��֧��"20/40�������"���ԣ���ֱ�Ӻ���AP��������"20/40�������֡"  ��HTվ�㣬�������֡ */
    if (OAL_FALSE == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap) ||
            (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(pst_mac_vap)))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{dmac_sta_up_rx_2040_coext::Ignoring the 20/40 Coexistence Management frame.}");
        return;
    }

    /* "Information Request" field */
    if (puc_frame_body[MAC_ACTION_OFFSET_ACTION + 1 + 1 + 1] & BIT0)
    {
        /* ��STA�յ�һ��Information RequestΪ1��֡����Ҫ��һ��20/40�������֡ */
        dmac_send_2040_coext_mgmt_frame_sta(pst_mac_vap);
    }
}

#endif


/*****************************************************************************
 �� �� ��  : dmac_sta_up_rx_action
 ��������  : STA��UP״̬�µĽ���ACTION֡����
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ��
             pst_netbuf  : Action֡���ڵ�netbuf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 dmac_sta_up_rx_action(dmac_vap_stru *pst_dmac_vap,oal_netbuf_stru *pst_netbuf,oal_uint16 us_user_idx)
{
    mac_vap_stru                   *pst_mac_vap;
    dmac_user_stru                 *pst_dmac_user;
    dmac_rx_ctl_stru               *pst_rx_ctl;
    mac_rx_ctl_stru                *pst_rx_info;
    oal_uint8                      *puc_data;
    oal_uint16                      us_frame_len;
    oal_uint8                       uc_go_on = OAL_TRUE;   //action֡Ĭ���ϱ�host

    if ((OAL_PTR_NULL == pst_dmac_vap) || (OAL_PTR_NULL == pst_netbuf))
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{dmac_sta_up_rx_action::pst_dmac_vap = [%p], pst_netbuf = [%p]!}",
                        pst_dmac_vap, pst_netbuf);
        return OAL_FALSE;
    }

    pst_dmac_user = mac_res_get_dmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                       "{dmac_sta_up_rx_action::pst_dmac_user null.[%d]}",us_user_idx);
        return OAL_FALSE;
    }

    pst_mac_vap    = &pst_dmac_vap->st_vap_base_info;

    pst_rx_ctl     = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_rx_info    = (mac_rx_ctl_stru *)(&(pst_rx_ctl->st_rx_info));

    /* ��ȡ֡��ָ�� */
    puc_data = MAC_GET_RX_PAYLOAD_ADDR(pst_rx_info,pst_netbuf);
    us_frame_len = MAC_GET_RX_CB_PAYLOAD_LEN(pst_rx_info);  /*֡�峤��*/

    switch (puc_data[MAC_ACTION_OFFSET_CATEGORY])
    {
        case MAC_ACTION_CATEGORY_HT:
        {
            /* Action */
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
                case MAC_HT_ACTION_NOTIFY_CHANNEL_WIDTH:
                    uc_go_on = OAL_FALSE;
                    dmac_rx_notify_channel_width(pst_mac_vap,puc_data,pst_dmac_user);
                    break;
#endif

                case MAC_HT_ACTION_BUTT:
                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_PUBLIC:
        {
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
                case MAC_PUB_COEXT_MGMT:
                    uc_go_on = OAL_FALSE;
                    dmac_sta_up_rx_2040_coext(&(pst_dmac_vap->st_vap_base_info), puc_data);
                  break;
#endif  /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */

                case MAC_PUB_EX_CH_SWITCH_ANNOUNCE:
                    uc_go_on = OAL_FALSE;
                    dmac_sta_up_rx_ext_ch_switch(pst_mac_vap,puc_data,us_frame_len);
                    break;

                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_SPECMGMT:
        {
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
                case MAC_SPEC_CH_SWITCH_ANNOUNCE:
                    uc_go_on = OAL_FALSE;
                    dmac_sta_up_rx_ch_switch(pst_mac_vap,puc_data,us_frame_len);
                    break;

                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_VHT:
        {
            switch(puc_data[MAC_ACTION_OFFSET_ACTION])
            {
            #ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
                case MAC_VHT_ACTION_OPREATE_MODE_NOTIFY:
                    uc_go_on = OAL_FALSE;
                    dmac_mgmt_rx_opmode_notify_frame(pst_mac_vap, &(pst_dmac_user->st_user_base_info), puc_data);
                    break;
            #endif
                case MAC_VHT_ACTION_BUTT:
                default:
                    break;
            }
        }
        break;
#ifdef _PRE_WLAN_FEATURE_11K
        case MAC_ACTION_CATEGORY_RADIO_MEASURMENT:
        {
            if (OAL_FALSE == pst_dmac_vap->bit_11k_enable)
            {
                break;
            }

            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
                case MAC_RM_ACTION_RADIO_MEASUREMENT_REQUEST:
                    dmac_rrm_proc_rm_request(pst_dmac_vap, pst_netbuf);
                    uc_go_on = OAL_FALSE;
                    break;

                case MAC_RM_ACTION_LINK_MEASUREMENT_REQUEST:
                    dmac_rrm_get_link_req_info(pst_dmac_vap, puc_data);
                    dmac_rrm_send_link_meas_rpt_action(pst_dmac_vap, pst_netbuf);
                    uc_go_on = OAL_FALSE;
                    break;

                case MAC_RM_ACTION_NEIGHBOR_REPORT_RESPONSE:

                    break;
                default:
                    break;
            }
        }
        break;
#endif //_PRE_WLAN_FEATURE_11K

#ifdef _PRE_WLAN_FEATURE_WMMAC
        case MAC_ACTION_CATEGORY_WMMAC_QOS:
        {
            if(OAL_TRUE == g_en_wmmac_switch)
            {
                switch (puc_data[MAC_ACTION_OFFSET_ACTION])
                {
                    case MAC_WMMAC_ACTION_ADDTS_RSP:
                        dmac_mgmt_rx_addts_rsp(pst_dmac_vap, pst_dmac_user,puc_data);
                        break;

                    case MAC_WMMAC_ACTION_DELTS:
                        dmac_mgmt_rx_delts(pst_dmac_vap, pst_dmac_user,puc_data);

                        break;
                    default:
                        break;
                }
            }
        }
        break;
#endif //_PRE_WLAN_FEATURE_WMMAC

        default:
        break;
    }

    return uc_go_on;
}
/*****************************************************************************
 �� �� ��  : dmac_rx_filter_mgmt
 ��������  : dmac_rx_filter_mgmt
 �������  : pst_dmac_vap
             pst_netbuf
             pst_event_mem
             &en_go_on
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_filter_mgmt(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, frw_event_mem_stru *pst_event_mem, oal_uint8 *pen_go_on)
{
    mac_device_stru            *pst_mac_device;
    dmac_rx_ctl_stru           *pst_rx_ctl;
    mac_ieee80211_frame_stru   *pst_frame_hdr;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    mac_rx_ctl_stru            *pst_rx_info;
    oal_uint8                  *puc_wps_ie      = OAL_PTR_NULL;
    oal_uint8                  *puc_payload     = OAL_PTR_NULL;
    oal_uint16                  us_msg_len;         /* ��Ϣ�ܳ���,������FCS */
#ifdef _PRE_WLAN_FEATURE_HILINK
    oal_uint8                  *puc_hilink_ie   = OAL_PTR_NULL;
    oal_uint8                  *puc_sa;
#endif
#endif

    oal_uint8                   auc_bssid[WLAN_MAC_ADDR_LEN];  /* sta������ap mac��ַ */
    oal_uint8                   auc_bad_bssid[WLAN_MAC_ADDR_LEN] = {0x0,0x0,0x0,0x0,0x0,0x0};  /* �Ƿ�bssid��ȫ0 */
    oal_uint32                  ul_ret;
    oal_bool_enum_uint8         en_report_bss = OAL_FALSE;      /* �Ƿ��ϱ���bss */
    //static oal_uint8 smooth_count = 0;
    oal_uint16                  us_user_idx;
    oal_bool_enum_uint8         en_is_tpc_registered = OAL_TRUE;

#ifdef _PRE_WLAN_FEATURE_P2P
    oal_uint8                   *puc_p2p0_mac_addr;
#endif

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_mgmt::pst_mac_device is NULL.}");
        return OAL_FAIL;
    }

    /* ��ȡ֡ͷ��Ϣ */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));

    *pen_go_on = OAL_TRUE;  /* �������غ��Ƿ񷢵�HMAC����ʼΪtrue */

    mac_get_bssid((oal_uint8 *)pst_frame_hdr, auc_bssid);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type)
    {
        if(OAL_TRUE == PM_WLAN_IsHostSleep())
        {
            *pen_go_on = OAL_FALSE;
        }
        pst_rx_ctl->st_rx_info.bit_is_beacon = OAL_TRUE;
    }
#endif

    /* STA UT��beacon�����Ⱦ��촦������ʱ������ǰ�ر�ǰ�˽��� */
    if((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state)
        && (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
        && (WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type))
    {

        /* ��ȡBeacon֡�е�mac��ַ����AP��mac��ַ */
         #if (!defined(HI1102_EDA))
        if(0 == oal_memcmp(auc_bssid,pst_dmac_vap->st_vap_base_info.auc_bssid,OAL_SIZEOF(auc_bssid)))
        {

            #ifdef _PRE_WLAN_FEATURE_STA_PM
            dmac_psm_process_tim_elm(pst_dmac_vap, pst_netbuf);
            #endif

            #ifdef _PRE_WLAN_FEATURE_P2P
            if (IS_P2P_CL((&pst_dmac_vap->st_vap_base_info)))
            {
                /* ��ȡGO Beacon֡�е�NoA��Ѷ */
                dmac_process_p2p_noa(pst_dmac_vap, pst_netbuf);
            }

            /* DTS2015042506406 P2P WFA 7.1.3��OppPS ���ܽ��յ�beacon ֡�� ��ʹ�ܷ��� */
            if ((IS_P2P_CL(&pst_dmac_vap->st_vap_base_info))&&
                (IS_P2P_OPPPS_ENABLED(pst_dmac_vap)))
            {
                dmac_p2p_oppps_ctwindow_start_event(pst_dmac_vap);
            }
            #endif  /* #ifdef _PRE_WLAN_FEATURE_P2P */

            #ifdef _PRE_WLAN_FEATURE_TSF_SYNC
            dmac_sync_tsf_by_bcn(pst_dmac_vap, pst_netbuf);
            #endif

            #ifdef _PRE_WLAN_FEATURE_11K
            if (OAL_TRUE == pst_dmac_vap->bit_11k_enable)
            {
                dmac_rrm_proc_pwr_constraint(pst_dmac_vap, pst_netbuf);
                dmac_rrm_parse_quiet(pst_dmac_vap, pst_netbuf);
            }
            #endif //_PRE_WLAN_FEATURE_11K


        }
        #else
            #ifdef _PRE_WLAN_FEATURE_STA_PM
            dmac_psm_process_tim_elm(pst_dmac_vap, pst_netbuf);
            #endif
        #endif /*(!defined(HI1102_EDA))*/

        dmac_sta_up_rx_beacon(pst_dmac_vap, pst_netbuf, pen_go_on);
    }


    /* ���TSF�������� */
    dmac_rx_mgmt_update_tsf(pst_dmac_vap, pst_frame_hdr, pst_mac_device, pst_netbuf);

    if(0 == oal_memcmp(auc_bssid,auc_bad_bssid,OAL_SIZEOF(auc_bssid)))
    {
        OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_mgmt::drop bssid zero packet}");
        *pen_go_on = OAL_FALSE;
        oal_netbuf_free(pst_netbuf);
        return OAL_SUCC;
    }


#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)

    ul_ret = dmac_11w_rx_filter(pst_dmac_vap, pst_netbuf);
    if (OAL_SUCC != ul_ret)
    {
        /* �鲥����ʧ�ܣ����ϱ�����֡ */
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                       "{dmac_rx_mgmt_classify::dmac_11w_rx_filter failed[%d].}", ul_ret);
        *pen_go_on = OAL_FALSE;

        oal_netbuf_free(pst_netbuf);
        return OAL_SUCC;
    }
#endif /* #if(_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT) */

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(pst_mac_device->pst_device_stru->st_btcoex_btble_status.un_ble_status.st_ble_status.bit_ble_scan)
    {
        if ((WLAN_ASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
            ||(WLAN_REASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type))
        {
            hal_set_btcoex_occupied_period(OCCUPIED_PERIOD);

            pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied.uc_occupied_times = OCCUPIED_TIMES;
            /* ����occupied��ʱ�� */
            FRW_TIMER_CREATE_TIMER(&(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied.bt_coex_occupied_timer),
                                   dmac_btcoex_wlan_occupied_timeout_callback,
                                   OCCUPIED_INTERVAL,
                                   (oal_void *)pst_dmac_vap,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   pst_mac_device->ul_core_id);
        }
    }
#endif


    /* �����ǰdevice����ɨ��״̬�������յ��Ĺ���֡ */
    if (MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state)
    {
        /* ��������ת�Ƶ�ɨ��ģ�鴦��ʱ��ִ�����´��� */
#ifdef _PRE_WLAN_FEATURE_P2P
        if (MAC_SCAN_FUNC_P2P_LISTEN == pst_mac_device->st_scan_params.uc_scan_func)
        {
            /* P2P �豸���յ�����֡ */
            if (!IS_LEGACY_VAP((&pst_dmac_vap->st_vap_base_info)))
            {
                *pen_go_on = dmac_p2p_listen_rx_mgmt(pst_dmac_vap, pst_netbuf);
            }
        }
        else
#endif
        {
            /* ���ɨ�趯������bss��Ϣ����ô����ɨ�����֡���ˣ����ж�Ӧ�Ĵ�����������do nothing  */
            if (pst_mac_device->st_scan_params.uc_scan_func & MAC_SCAN_FUNC_BSS)
            {
                /*DTS2015102002093 ɨ��ʱҲ�ǻ�ż���лع����ŵ�����,���ܹ��˵����й���֡ */
// *pen_go_on = OAL_FALSE;

                /* ɨ��״̬��֡���˴��� */
                dmac_scan_mgmt_filter(pst_dmac_vap, pst_netbuf, &en_report_bss, pen_go_on);
            }
        }
    }

    if (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state && WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        if (WLAN_PROBE_REQ == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            *pen_go_on      = OAL_FALSE;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
            pst_rx_info     = (mac_rx_ctl_stru *)(&(pst_rx_ctl->st_rx_info));
            puc_payload     = MAC_GET_RX_PAYLOAD_ADDR(pst_rx_info, pst_netbuf);
            us_msg_len      = pst_rx_info->us_frame_len;                          /* ��Ϣ�ܳ���,������FCS */
            //puc_wps_ie      = mac_get_wps_ie(puc_payload, us_msg_len, 0);
            puc_wps_ie      = mac_find_vendor_ie(MAC_WLAN_OUI_MICROSOFT, MAC_WLAN_OUI_TYPE_MICROSOFT_WPS, puc_payload, us_msg_len);
            if (OAL_PTR_NULL != puc_wps_ie)
            {
                *pen_go_on = OAL_TRUE;
            }
#ifdef _PRE_WLAN_FEATURE_HILINK
            puc_hilink_ie      = mac_find_vendor_ie(MAC_WLAN_OUI_HUAWEI, MAC_WLAN_OUI_TYPE_HUAWEI_HILINK, puc_payload, us_msg_len);
            if (OAL_PTR_NULL != puc_hilink_ie)
            {
                mac_rx_get_sa(pst_frame_hdr, &puc_sa);
                OAM_INFO_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac rx hilink probe req:seq num=%d,mac[%x:%x:%x]}",
                                                                                    pst_frame_hdr->bit_seq_num,puc_sa[3],puc_sa[4],puc_sa[5]);

                *pen_go_on = OAL_TRUE;
            }
#endif
#endif
            //OAM_WARNING_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_ap_up_rx_probe}");
            dmac_ap_up_rx_probe_req(pst_dmac_vap, pst_netbuf);
        }
        else if (WLAN_AUTH == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            *pen_go_on = OAL_FALSE;
            ul_ret = dmac_ap_up_rx_generate_chtxt(pst_dmac_vap, pst_netbuf, pst_event_mem);
            if (OAL_SUCC != ul_ret)
            {
                oal_netbuf_free(pst_netbuf);
            }
            /*OAL_SUCC, netbuf�Ѿ��ύ��hcc�ϱ�host*/
            return ul_ret;
        }
        else if(WLAN_ACTION == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
#ifdef _PRE_WLAN_FEATURE_P2P
            /* DTS2015082401460  P2P GO���յ�P2P action ����֡���� */
            if (IS_P2P_GO((&pst_dmac_vap->st_vap_base_info)))
            {
                *pen_go_on = dmac_p2p_listen_rx_mgmt(pst_dmac_vap, pst_netbuf);
            }
#endif

            ul_ret = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info),  pst_frame_hdr->auc_address2, &us_user_idx);
            if(OAL_SUCC != ul_ret)
            {
                *pen_go_on = OAL_FALSE;
            }

        }
        else if (WLAN_DISASOC == pst_frame_hdr->st_frame_control.bit_sub_type||(WLAN_DEAUTH == pst_frame_hdr->st_frame_control.bit_sub_type))
        {
            if(0 != oal_memcmp(auc_bssid,pst_dmac_vap->st_vap_base_info.auc_bssid,OAL_SIZEOF(auc_bssid)))
            {
                *pen_go_on = OAL_FALSE;
                OAM_INFO_LOG4(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX,
                                "{dmac_rx_filter_mgmt::drop  disasoc frame! bssid not match! local bssid[%x:X:X:%x:%x:%x]}",
                                  pst_dmac_vap->st_vap_base_info.auc_bssid[0],
                                  pst_dmac_vap->st_vap_base_info.auc_bssid[3],
                                  pst_dmac_vap->st_vap_base_info.auc_bssid[4],
                                  pst_dmac_vap->st_vap_base_info.auc_bssid[5]);
            }
        }

    }
    else if(MAC_VAP_STATE_PAUSE == pst_dmac_vap->st_vap_base_info.en_vap_state && WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        /* green ap֧�� */
        if (WLAN_PROBE_REQ == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            *pen_go_on = OAL_FALSE;
        }
    }

    if ((MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state) && (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode))
    {
        if(WLAN_ACTION == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
        #ifdef _PRE_WLAN_FEATURE_P2P
            /* P2P0�豸�����յ�actionȫ���ϱ� */
            puc_p2p0_mac_addr = pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID;
            if (0 == oal_compare_mac_addr(pst_frame_hdr->auc_address1, puc_p2p0_mac_addr))
            {
                *pen_go_on = OAL_TRUE;
                return OAL_SUCC;
            }
        #endif
            ul_ret = mac_vap_find_user_by_macaddr(&(pst_dmac_vap->st_vap_base_info), pst_frame_hdr->auc_address2, &us_user_idx);
            if (OAL_SUCC != ul_ret)
            {
                *pen_go_on = OAL_FALSE;
            }
            else
            {
                *pen_go_on = dmac_sta_up_rx_action(pst_dmac_vap,pst_netbuf,us_user_idx);
            }
        }
    }

    if ((WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
         && (0 == oal_memcmp(auc_bssid,pst_dmac_vap->st_vap_base_info.auc_bssid,OAL_SIZEOF(auc_bssid))))
    {
        if (WLAN_PROBE_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
        {
            dmac_vap_linkloss_clean(pst_dmac_vap);
        }
        else
        {
            if (((WLAN_ASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type)
                || (WLAN_REASSOC_RSP == pst_frame_hdr->st_frame_control.bit_sub_type))
                && (MAC_VAP_STATE_UP != pst_dmac_vap->st_vap_base_info.en_vap_state))
            {
                pst_dmac_vap->st_query_stats.ul_signal = pst_rx_ctl->st_rx_statistic.c_rssi_dbm;
            }
        }

        /* ����㷨�����ã����õ�ǰbeacon֡RSSI���� */
        if (((OAL_SUCC != dmac_alg_is_registered(DMAC_ALG_ID_TPC, &en_is_tpc_registered)) || (OAL_FALSE == en_is_tpc_registered))
        && ((WLAN_BEACON == pst_frame_hdr->st_frame_control.bit_sub_type) && (MAC_VAP_STATE_UP == pst_dmac_vap->st_vap_base_info.en_vap_state)))
        {
            pst_dmac_vap->st_query_stats.ul_signal = pst_rx_ctl->st_rx_statistic.c_rssi_dbm;
        }
    }

    if(OAL_TRUE == en_report_bss)
    {
        /*�����ɨ�����Ѿ��ϱ����˴���Ӧ�����ϱ���netbuf,���Ҳ����ͷ�netbuf*/
        *pen_go_on = OAL_FALSE;
        return OAL_SUCC;
    }

    if (OAL_FALSE == *pen_go_on)
    {
        /* ��netbuf�黹�ڴ�� */
        oal_netbuf_free(pst_netbuf);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_mgmt_classify
 ��������  : DMACģ�飬�������̹���֡������ڣ���Ҫ����֡��DMAC����HMAC�ķַ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_mgmt_classify(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                mac_vap_stru                   *pst_vap,
                oal_netbuf_stru                *pst_netbuf)
{
    frw_event_stru                    *pst_event;
    dmac_wlan_crx_event_stru          *pst_crx_event;
    dmac_vap_stru                     *pst_dmac_vap;
    dmac_rx_ctl_stru                  *pst_rx_ctl;
    mac_ieee80211_frame_stru          *pst_frame_hdr;
    oal_bool_enum_uint8                en_go_on          = OAL_TRUE;           /* �Ƿ������hmac���� */
    mac_user_stru                     *pst_user;


    /* ��ȡ�¼�ͷ���¼��ṹ��ָ�� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* �����¼�ͷ�е�VAP ID */
    pst_event_hdr->uc_vap_id = pst_vap->uc_vap_id;

    /* ��ȡ֡ͷ��Ϣ */
    pst_rx_ctl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctl->st_rx_info));

    /* ת��ΪDMAC VAP */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_mgmt_classify::pst_dmac_vap null.}");

        OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_user = (mac_user_stru *)mac_res_get_dmac_user(MAC_GET_RX_CB_TA_USER_IDX(&(pst_rx_ctl->st_rx_info)));

    /* ����֡����Ŀǰû���ϱ���HMAC��ֱ��return */
    if (WLAN_CONTROL == pst_frame_hdr->st_frame_control.bit_type)
    {
        if (OAL_PTR_NULL != pst_user)
        {
            dmac_alg_txbf_rx_cntl_notify(&(pst_dmac_vap->st_vap_base_info), pst_user, pst_netbuf);
        }

        dmac_rx_process_control(pst_dmac_vap, pst_netbuf, &en_go_on);
        if (OAL_FALSE == en_go_on)
        {
            oal_netbuf_free(pst_netbuf);
            return OAL_SUCC;
        }
    }

    /* DMAC����֡���� */
    if (WLAN_MANAGEMENT == pst_frame_hdr->st_frame_control.bit_type)
    {
        /*dmac_rx_filter_mgmt����ܻ����netbuf���ݣ���������֪ͨ�㷨*/
        if (OAL_PTR_NULL != pst_user)
        {
            dmac_alg_rx_mgmt_notify(&(pst_dmac_vap->st_vap_base_info), pst_user, pst_netbuf);
        }


        dmac_rx_filter_mgmt(pst_dmac_vap, pst_netbuf, pst_event_mem, &en_go_on);

    }

    if (OAL_TRUE == en_go_on)
    {
        /* ��������֡ͳһ�ϱ���HMAC���� */
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
#ifdef _PRE_WLAN_DFT_DUMP_FRAME
        mac_rx_report_80211_frame((oal_uint8 *)&(pst_dmac_vap->st_vap_base_info), (oal_uint8 *)&(pst_rx_ctl->st_rx_info), pst_netbuf, OAM_OTA_TYPE_RX_DMAC_CB);
#endif /* #ifdef _PRE_WLAN_DFT_DUMP_FRAME */
#endif /* #if defined(_PRE_PRODUCT_ID_HI110X_DEV) */
        /* �̳��¼��������޸��¼�ͷ����ʱδ����STA��APģʽ */
        FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX);

        pst_crx_event = (dmac_wlan_crx_event_stru *)(pst_event->auc_event_data);
        pst_crx_event->pst_netbuf = pst_netbuf;

        /* �ַ� */
        /*DTS2015031608237 ���ֱ�ӷ��أ�netbuf���ڴ�й¶*/
        return frw_event_dispatch_event(pst_event_mem);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_multi_mgmt_pre_process
 ��������  : Ԥ������������BSS�Ĺ㲥����֡�����ݱ�vap ״̬��֡�����ж��Ƿ���Ҫ����
            probe req ֡(�㲥)
                ��1�������go/ap �����յ�probe req �ŵ��ͱ�vap �����ŵ���ͬ���������ƺͽ�һ������
                ��2�������sta�� ���յ�prob req ���������ƺʹ���
                ��3�������p2p device ����p2p client ,����dao probe req ���ж��Ƿ�Ϊ����״̬������Ǽ���״̬�����ƣ����򲻸��ơ�
            beacon ֡
                ��1��ap/p2p go, �ŵ�ѡ��ʱ��ɨ����յ���beacon ֡��Ҫ����
                ��2��sta/p2p gc/p2p dev һֱ��Ҫbeacon ֡
            action ֡(�㲥)
                ��1���㲥action ֡�����Ƹ�����vap
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��2��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_rx_multi_mgmt_pre_process(mac_device_stru    *pst_mac_device,
                                                                mac_vap_stru     *pst_mac_vap,
                                                                oal_uint8         uc_channel_number,
                                                                oal_uint8         uc_mgmt_type)
{
    oal_bool_enum_uint8          en_need_copy = OAL_TRUE;

    /* �жϽ��յ���beacon / probe req �Ƿ������Ƹ�����vap ���� */
    switch (uc_mgmt_type)
    {
        case (WLAN_FC0_SUBTYPE_PROBE_REQ | WLAN_FC0_TYPE_MGT):
        {
            //OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX,
            //    "{dmac_rx_multi_mgmt_pre_process::rx probe req}");
            if (IS_AP(pst_mac_vap)
                && uc_channel_number != pst_mac_vap->st_channel.uc_chan_number)
            {
                en_need_copy = OAL_FALSE;
            }
            else if (IS_STA(pst_mac_vap))
            {
                if (IS_LEGACY_VAP(pst_mac_vap))
                {
                    en_need_copy = OAL_FALSE;
                }
                else
                {
                    if(OAL_FALSE == mac_device_is_listening(pst_mac_device))
                    {
                        en_need_copy = OAL_FALSE;
                    }
                }
            }
            break;
        }
        case (WLAN_FC0_SUBTYPE_BEACON | WLAN_FC0_TYPE_MGT):
        {
            //OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX,
            //    "{dmac_rx_multi_mgmt_pre_process::rx beacon}");
            if (IS_AP(pst_mac_vap))
            {
                if(OAL_FALSE == mac_device_is_scaning(pst_mac_device))
                {
                    en_need_copy = OAL_FALSE;
                }
            }
            break;
        }
        default:
        {
            en_need_copy = OAL_TRUE;
            break;
        }
    }

    //OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX,
    //    "{dmac_rx_multi_mgmt_pre_process::en_need_copy[%d]}", en_need_copy);
    return en_need_copy;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_multi_mgmt_frame
 ��������  : ������������BSS�Ĺ㲥����֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��2��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_multi_mgmt_frame(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                oal_netbuf_stru                *pst_netbuf)
{
    mac_device_stru    *pst_device;
    mac_vap_stru       *pst_mac_vap;
    oal_netbuf_stru    *pst_netbuf_copy = OAL_PTR_NULL;
    dmac_rx_ctl_stru   *pst_rx_ctrl;
    oal_uint8           uc_vap_idx;
    oal_uint32          ul_rslt;

    mac_ieee80211_frame_stru    *pst_mac_header;
    oal_bool_enum_uint8          en_orig_netbuffer_used = OAL_FALSE;
    oal_uint8                    uc_channel_number;
    oal_uint8                    uc_subtype;

    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX,
                       "{dmac_rx_multi_mgmt_frame::pst_device null, uc_device_id=%d.}", pst_event_hdr->uc_device_id);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��device�µ��豸��Ϊ0ʱ��ֱ���ͷŽ��յ��İ� */
    if (0 == pst_device->uc_vap_num)
    {
        //OAM_INFO_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::the device have none vap.}\r\n");

        oal_netbuf_free(pst_netbuf);
        return OAL_SUCC;
    }

    pst_rx_ctrl       = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_mac_header    = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_rx_ctrl->st_rx_info));
    uc_channel_number = pst_rx_ctrl->st_rx_info.uc_channel_number;
    uc_subtype        = mac_get_frame_sub_type((oal_uint8 *)pst_mac_header);

    /* ��������BSS�Ĺ㲥����֡��ת����ÿһ��VAPһ�� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::pst_mac_vap null, vap id=%d.", pst_device->auc_vap_id[uc_vap_idx]);
            //return OAL_ERR_CODE_PTR_NULL;
            continue;
        }

        if (OAL_FALSE == dmac_rx_multi_mgmt_pre_process(pst_device, pst_mac_vap, uc_channel_number, uc_subtype))
        {
            //OAM_WARNING_LOG0(pst_device->auc_vap_id[uc_vap_idx], OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::probe req or beacon do not dispatch to the vap which do not needed.}");
            continue;
        }

        /* ���һ��VAPֱ�ӷ���ԭ����netbuf */
        if (uc_vap_idx == pst_device->uc_vap_num - 1)
        {
            pst_netbuf_copy = pst_netbuf;
            en_orig_netbuffer_used = OAL_TRUE;
        }
        else
        {
        #ifdef _PRE_WLAN_HW_TEST
            /* ����״̬ */
            if (HAL_ALWAYS_RX_RESERVED == pst_device->pst_device_stru->bit_al_rx_flag)
            {
                pst_netbuf_copy = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, HAL_AL_RX_FRAME_LEN, OAL_NETBUF_PRIORITY_MID);
            }
            else
        #endif
            {
                pst_netbuf_copy = OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_LARGE_NETBUF_SIZE, OAL_NETBUF_PRIORITY_MID);
            }

            if (OAL_PTR_NULL == pst_netbuf_copy)
            {
                OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::pst_netbuf_copy null.}");
                continue;
            }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            OAL_MEM_NETBUF_TRACE(pst_netbuf_copy, OAL_TRUE);
#endif

            pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf_copy);
            /* ��Ϣ���� */
            oal_memcopy(oal_netbuf_cb(pst_netbuf_copy), oal_netbuf_cb(pst_netbuf), OAL_SIZEOF(dmac_rx_ctl_stru));

#if (!defined(_PRE_PRODUCT_ID_HI110X_DEV))
            oal_memcopy(pst_netbuf_copy->head, pst_netbuf->head, (oal_uint32)(pst_netbuf->end - pst_netbuf->head));
#else
            oal_memcopy(oal_netbuf_header(pst_netbuf_copy), oal_netbuf_header(pst_netbuf), (oal_uint32)(pst_rx_ctrl->st_rx_info.bit_mac_header_len));
            oal_memcopy(oal_netbuf_payload(pst_netbuf_copy), oal_netbuf_payload(pst_netbuf),
                       ((oal_uint32)(pst_rx_ctrl->st_rx_info.us_frame_len) - (oal_uint32)(pst_rx_ctrl->st_rx_info.bit_mac_header_len)));
#endif

            /* ����netbuf���ȡ�TAILָ�� */
            oal_netbuf_set_len(pst_netbuf_copy, oal_netbuf_get_len(pst_netbuf));
            oal_set_netbuf_tail(pst_netbuf_copy, oal_netbuf_data(pst_netbuf_copy) + oal_netbuf_get_len(pst_netbuf_copy));

            /* ����MAC֡ͷ��ָ��(copy�󣬶�Ӧ��mac header��ͷ�Ѿ������仯) */
            mac_set_rx_cb_mac_hdr(&(pst_rx_ctrl->st_rx_info), (oal_uint32 *)oal_netbuf_header(pst_netbuf_copy));
        }

        /* ���ô������֡�ӿ� */
        ul_rslt = dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_mac_vap, pst_netbuf_copy);
        if (ul_rslt != OAL_SUCC)
        {
//            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_multi_mgmt_frame::dmac_rx_mgmt_classify failed[%d].", ul_rslt);
            OAL_IO_PRINT("\r\n dmac_rx_multi_mgmt_frame::dmac_rx_mgmt_classify failed[%d].\r\n", ul_rslt);

            oal_netbuf_free(pst_netbuf_copy);
        }
    }

    /* δʹ�ô����netbuffer�� ֱ���ͷ� */
    if(OAL_FALSE == en_orig_netbuffer_used)
    {
        oal_netbuf_free(pst_netbuf);
    }
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_rx_process_mgmt
 ��������  : ����֡�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��2��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_process_mgmt(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                hal_to_dmac_device_stru        *pst_hal_device,
                oal_netbuf_stru                *pst_netbuf)
{
    hal_to_dmac_vap_stru   *pst_hal_vap = OAL_PTR_NULL;
    dmac_rx_ctl_stru       *pst_cb_ctrl;
    oal_uint8               uc_vap_id;
    mac_vap_stru           *pst_vap;
    mac_device_stru        *pst_mac_device;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_ieee80211_frame_stru *pst_mac_ieee80211_frame;
#endif

    pst_cb_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    pst_mac_device = (mac_device_stru *)mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_mgmt::pst_mac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
#ifdef _PRE_WLAN_DFT_STAT
    /* ����֡����ͳ�� */
    dmac_dft_mgmt_stat_incr(pst_mac_device, oal_netbuf_header(pst_netbuf), MAC_DEV_MGMT_STAT_TYPE_RX);
#endif

    /* ��ȡ��֡��Ӧ��VAP ID */
    uc_vap_id = pst_cb_ctrl->st_rx_info.bit_vap_id;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (mac_is_proxysta_enabled(pst_mac_device) && HAL_VAP_ID_IS_VALID_PSTA(uc_vap_id)
    || !mac_is_proxysta_enabled(pst_mac_device) && HAL_VAP_ID_IS_VALID(uc_vap_id))
#else
    if (HAL_VAP_ID_IS_VALID(uc_vap_id))  /* ���Ա�device�µ�ĳһBSS��֡ */
#endif
    {
        hal_get_hal_vap(pst_hal_device, uc_vap_id, &pst_hal_vap);
        if (OAL_PTR_NULL == pst_hal_vap)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::hal vap failed!}");
            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hal_vap->uc_mac_vap_id);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_process_mgmt::mac vap is null!}");

            OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);

            return OAL_ERR_CODE_PTR_NULL;
        }
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (mac_is_proxysta_enabled(pst_mac_device))
        {
            /* ����Ƿ��͸�sta0�Ĺ㲥/�鲥����֡����device�µ�ÿ��vap(����Proxy STA)������һ�� */
            pst_mac_ieee80211_frame = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf);
            if ((WLAN_STA0_HAL_VAP_ID == uc_vap_id) && (ETHER_IS_MULTICAST(pst_mac_ieee80211_frame->auc_address1)))
            {
                return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
            }
        }
#endif

        return dmac_rx_mgmt_classify(pst_event_mem, pst_event_hdr, pst_vap, pst_netbuf);
    }
    else if (WLAN_HAL_OHTER_BSS_ID == uc_vap_id)  /* ��������bss�Ĺ㲥����֡ */
    {
        return dmac_rx_multi_mgmt_frame(pst_event_mem, pst_event_hdr, pst_netbuf);
    }
    else                                                /* �쳣֡ */
    {
        OAM_STAT_VAP_INCR(0, rx_mgmt_abnormal_dropped, 1);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }
}

/*****************************************************************************
 �� �� ��  : dmac_tx_process_action_event
 ��������  : DMACģ�飬ACTION���ʹ���ӿڣ���Ҫ�ǽ�����Ϣͬ���͵��ù���֡���ͽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��10��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tx_process_action_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    dmac_ctx_action_event_stru *pst_ctx_action_event;
    dmac_tx_event_stru         *pst_tx_event;
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;
    oal_uint32                  ul_action_info_offset;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_tx_process_action_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_tx_event            = (dmac_tx_event_stru *)pst_event->auc_event_data;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    ul_action_info_offset   = pst_tx_event->us_frame_len - OAL_SIZEOF(dmac_ctx_action_event_stru) - MAC_80211_FRAME_LEN;
#else
    ul_action_info_offset   = pst_tx_event->us_frame_len - OAL_SIZEOF(dmac_ctx_action_event_stru);
#endif
    pst_ctx_action_event    = (dmac_ctx_action_event_stru *)(oal_netbuf_data(pst_tx_event->pst_netbuf) + ul_action_info_offset);

    /* ��ȡȫ��board������Ϣ */

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    /*��λ״̬��ͣ����*/
    if(OAL_PTR_NULL != pst_device && OAL_TRUE == MAC_DEV_IS_RESET_IN_PROGRESS(pst_device))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX,
                       "{dmac_tx_process_action_event::MAC_DEV_IS_RESET_IN_PROGRESS.}");

        return OAL_SUCC;
    }

    OAM_INFO_LOG2(0, OAM_SF_TX, "{dmac_tx_process_action_event::category %d, action %d.}",
                  pst_ctx_action_event->en_action_category, pst_ctx_action_event->uc_action);

    /* ��ȡvap�ṹ��Ϣ */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

    switch (pst_ctx_action_event->en_action_category)
    {
        case MAC_ACTION_CATEGORY_BA:
            switch (pst_ctx_action_event->uc_action)
            {
                case MAC_BA_ACTION_ADDBA_REQ:
                    dmac_mgmt_tx_addba_req(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                    break;

                case MAC_BA_ACTION_ADDBA_RSP:
                    dmac_mgmt_tx_addba_rsp(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                    break;

                case MAC_BA_ACTION_DELBA:
                    dmac_mgmt_tx_delba(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                    break;

                default:

                    OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_action_event::invalid ba action type.}");
                    break;
            }

            break;
    #ifdef _PRE_WLAN_FEATURE_WMMAC
        case MAC_ACTION_CATEGORY_WMMAC_QOS:
             if(OAL_TRUE == g_en_wmmac_switch)
             {
                 switch (pst_ctx_action_event->uc_action)
                 {
                     case MAC_WMMAC_ACTION_ADDTS_REQ:
                        dmac_mgmt_tx_addts_req((dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                        break;

                     case MAC_WMMAC_ACTION_ADDTS_RSP:
                        dmac_mgmt_tx_addts_rsp((dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                        break;

                     case MAC_WMMAC_ACTION_DELTS:
                        dmac_mgmt_tx_delts((dmac_vap_stru *)pst_mac_vap, pst_ctx_action_event, pst_tx_event->pst_netbuf);
                        break;

                    default:
                        OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_action_event::invalid ba action type.}");
                        break;
                 }
             }
             break;
    #endif  //_PRE_WLAN_FEATURE_WMMAC

        default:
            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_TX, "{dmac_tx_process_action_event::invalid ba action category[%d].}",
                             pst_ctx_action_event->en_action_category);
            break;
    }


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_mgmt_tx_event_process
 ��������  : ͨ�õģ���Щ����Ҫdamc���κ�ҵ����Ĺ���֡����֤����������hmac�����ķ��͹���֡�¼�����д��Ӧcb���������͹���֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��25��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_mgmt_tx_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru          *pst_event;
    frw_event_hdr_stru      *pst_event_hdr;
    dmac_tx_event_stru      *pst_ctx_event;
    dmac_vap_stru           *pst_dmac_vap;
    oal_netbuf_stru         *pst_mgmt_frame;
    mac_tx_ctl_stru         *pst_tx_ctl;
    oal_uint32               ul_ret;
    oal_uint8                uc_mgmt_frm_type;
    mac_user_stru           *pst_mac_user;
    mac_device_stru         *pst_mac_device;

    if ((OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_mgmt_tx_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event       = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr   = &(pst_event->st_event_hdr);

    pst_ctx_event   = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_mgmt_frame  = pst_ctx_event->pst_netbuf;
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_mgmt_frame);

    oal_set_netbuf_next(pst_mgmt_frame, OAL_PTR_NULL);
    oal_set_netbuf_prev(pst_mgmt_frame, OAL_PTR_NULL);
    /* ��дnetbuf��cb�ֶΣ������͹���֡�ͷ�����ɽӿ�ʹ�� */
    MAC_GET_CB_IS_MCAST(pst_tx_ctl)        = OAL_FALSE;
    mac_set_cb_frame_hdr(pst_tx_ctl, (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_mgmt_frame));
    mac_set_cb_ac(pst_tx_ctl, WLAN_WME_AC_MGMT);

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

#ifdef _PRE_WLAN_FEATURE_ROAM
    /* ����״̬ʱ��ǿ�Ʒ��͸ù���֡ */
    if (MAC_VAP_STATE_ROAMING == pst_dmac_vap->st_vap_base_info.en_vap_state)
    {
        ul_ret = dmac_tx_force(pst_dmac_vap, pst_ctx_event->pst_netbuf, pst_ctx_event->us_frame_len, 1);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(0, OAM_SF_TX, "{dmac_mgmt_tx_event_process::dmac_tx_force [roam] len[%d] fail[%ld]}",
                           pst_ctx_event->us_frame_len, ul_ret);
            oal_netbuf_free(pst_ctx_event->pst_netbuf);
        }
        return ul_ret;
    }
#endif //_PRE_WLAN_FEATURE_ROAM
    uc_mgmt_frm_type = mac_get_frame_sub_type((oal_uint8 *)mac_get_cb_frame_hdr(pst_tx_ctl));
    if (uc_mgmt_frm_type == WLAN_FC0_SUBTYPE_AUTH)
    {
        pst_mac_user = mac_res_get_mac_user(MAC_GET_CB_TX_USER_IDX(pst_tx_ctl));
        pst_mac_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
        if (OAL_PTR_NULL == pst_mac_device)
        {
            oal_netbuf_free(pst_ctx_event->pst_netbuf);
            OAM_ERROR_LOG0(0, OAM_SF_TX, "{dmac_mgmt_tx_event_process::pst_mac_device is null.}");
            return OAL_ERR_CODE_PTR_NULL;
        }
        if (OAL_PTR_NULL != pst_mac_user)
        {
            dmac_tid_clear(pst_mac_user, pst_mac_device);
        }
    }

    ul_ret = dmac_tx_mgmt(pst_dmac_vap, pst_ctx_event->pst_netbuf, pst_ctx_event->us_frame_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_ctx_event->pst_netbuf);

        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_process_sync_event
 ��������  : �յ�wlan��Delba��addba rsp���ڵ�dmac��ͬ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��18��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_process_sync_event(frw_event_mem_stru *pst_event_mem)
{

    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    dmac_ctx_action_event_stru *pst_crx_action_sync;
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_sync_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_crx_action_sync    = (dmac_ctx_action_event_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    /* ��ȡvap�ṹ��Ϣ */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

    OAM_INFO_LOG2(0, OAM_SF_RX, "{dmac_rx_process_sync_event::category %d, action %d.}",
                  pst_crx_action_sync->en_action_category, pst_crx_action_sync->uc_action);
    switch (pst_crx_action_sync->en_action_category)
    {
        case MAC_ACTION_CATEGORY_BA:
            switch (pst_crx_action_sync->uc_action)
            {
                case MAC_BA_ACTION_ADDBA_RSP:

                    dmac_mgmt_rx_addba_rsp(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_action_sync);
                    break;

                case MAC_BA_ACTION_DELBA:

                    dmac_mgmt_rx_delba(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_action_sync);
                    break;

                default:

                    OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_sync_event::invalid ba action type.}");

                    break;
            }

            break;

        default:

            OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_sync_event::invalid ba action category.}");
            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_process_priv_req_event
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��26��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_process_priv_req_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    mac_priv_req_args_stru     *pst_crx_priv_req_args;
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_priv_req_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_crx_priv_req_args   = (mac_priv_req_args_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    /* ��ȡvap�ṹ��Ϣ */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);

    switch (pst_crx_priv_req_args->uc_type)
    {
        case MAC_A_MPDU_START:

            dmac_mgmt_rx_ampdu_start(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_priv_req_args);
            break;

        case MAC_A_MPDU_END:
            dmac_mgmt_rx_ampdu_end(pst_device, (dmac_vap_stru *)pst_mac_vap, pst_crx_priv_req_args);
            break;

        default:

            OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_priv_req_event::invalid priv action type.}");
            break;
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 �� �� ��  : dmac_btcoex_tx_addba_rsp_check
 ��������  : �ж�һ��֡�Ƿ���addba_rsp
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_btcoex_tx_addba_rsp_check(oal_netbuf_stru *pst_netbuf, dmac_user_stru *pst_dmac_user)
{
    oal_uint8 *puc_mac_header  = oal_netbuf_header(pst_netbuf);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8 *puc_mac_payload = oal_netbuf_data(pst_netbuf);
#else
    oal_uint8 *puc_mac_payload = puc_mac_header + MAC_80211_FRAME_LEN;
#endif
    dmac_user_btcoex_delba_stru *pst_dmac_user_btcoex_delba;

    /* Management frame */
    if (WLAN_FC0_SUBTYPE_ACTION == mac_get_frame_sub_type(puc_mac_header))
    {
        if ((MAC_ACTION_CATEGORY_BA == puc_mac_payload[0]) && (MAC_BA_ACTION_ADDBA_RSP == puc_mac_payload[1]))
        {
            pst_dmac_user_btcoex_delba = &(pst_dmac_user->st_dmac_user_btcoex_stru.st_dmac_user_btcoex_delba);
            pst_dmac_user_btcoex_delba->uc_get_addba_req_flag = OAL_TRUE;
            pst_dmac_user_btcoex_delba->uc_ba_size_addba_rsp_index = pst_dmac_user_btcoex_delba->uc_ba_size_index;
        }
    }
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_tx_complete_mgmt_notify
 ��������  : ������ɹ���֡�������
 �������  : pst_dscr: ��������ַ
             pst_dmac_user: sta�ṹ��ָ��
             pst_dmac_vap: vap�ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tx_complete_mgmt_notify(
                hal_to_dmac_device_stru *pst_hal_device,
                dmac_user_stru         *pst_dmac_user,
                hal_tx_dscr_stru       *pst_dscr,
                oal_netbuf_stru        *pst_buf)
{
    mac_tx_ctl_stru                *pst_tx_ctl;
    oal_uint8                       uc_tid;

    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_buf);

    if (OAL_TRUE == mac_is_delba_frame(pst_buf, &uc_tid))
    {
        pst_dmac_user->ast_tx_tid_queue[uc_tid].en_is_delba_ing = OAL_FALSE;
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_btcoex_tx_addba_rsp_check(pst_buf, pst_dmac_user);
#endif

    if (OAL_TRUE == mac_get_cb_is_bar(pst_tx_ctl))
    {
        dmac_tid_resume(pst_hal_device, &pst_dmac_user->ast_tx_tid_queue[mac_get_cb_tid(pst_tx_ctl)], DMAC_TID_PAUSE_RESUME_TYPE_BA);
        return OAL_SUCC;
    }

    return OAL_SUCC;
}
#if 0
/*****************************************************************************
 �� �� ��  : dmac_tx_complete_security
 ��������  : ������ɰ�ȫ�������
 �������  : pst_dscr: ��������ַ
             pst_dmac_user: sta�ṹ��ָ��
             pst_dmac_vap: vap�ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��14��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_tx_complete_security_ap(
                dmac_user_stru     *pst_dmac_user,
                hal_tx_dscr_stru   *pst_dscr,
                oal_netbuf_stru    *pst_buf)
{

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_mgmt_connect_set_channel
 ��������  : STA�������ŵ�����AP�����ŵ��ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��8��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_mgmt_connect_set_channel(
                mac_device_stru    *pst_mac_device,
                mac_vap_stru       *pst_up_vap,
                mac_channel_stru   *pst_channel)
{
    /* ��ǰû�д��ڹ���״̬��VAP������ֱ�����ŵ� */
    if (OAL_PTR_NULL == pst_up_vap)
    {
        //dmac_tx_clear_tx_queue(pst_mac_device->pst_device_stru);
        /* �����쳣���̣�VAP����������Ҫ���FIFO */
        dmac_mgmt_switch_channel(pst_mac_device, pst_channel, OAL_TRUE);

        return;
    }

    OAM_WARNING_LOG4(pst_up_vap->uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_connect_set_channel: has up vap. up_vap_chan:%d bw:%d, new_chan:%d bw:%d",
                         pst_up_vap->st_channel.uc_chan_number,
                         pst_up_vap->st_channel.en_bandwidth,
                         pst_channel->uc_chan_number,
                         pst_channel->en_bandwidth);

    if (pst_channel->uc_chan_number != pst_up_vap->st_channel.uc_chan_number)
    {
        /* ��ͣ�����ŵ���VAP���� */
        dmac_vap_pause_tx_by_chl(pst_mac_device, &(pst_up_vap->st_channel));

        OAM_WARNING_LOG1(pst_up_vap->uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_connect_set_channel: diff chan_num. switch off to chan %d.",
                            pst_channel->uc_chan_number);

        /* ������֡���ŵ����� */
        dmac_switch_channel_off(pst_mac_device, pst_up_vap, pst_channel, 20);
    }
    else
    {
        /* DTS2015073102639 ͬ�ŵ�ʱ��Ҫ�е����������ŵ� */
        if (pst_channel->en_bandwidth > pst_up_vap->st_channel.en_bandwidth)
        {
            OAM_WARNING_LOG2(pst_up_vap->uc_vap_id, OAM_SF_SCAN, "dmac_mgmt_connect_set_channel:  same chan_num[%d], switch to bw[%d].",
                            pst_channel->uc_chan_number,
                            pst_channel->en_bandwidth);
            /* �л�����Vvap�Թ����ڵ�ǰ�ŵ��������FIFO */
            dmac_mgmt_switch_channel(pst_mac_device, pst_channel, OAL_FALSE);
        }
    }

}

/*****************************************************************************
 �� �� ��  : dmac_join_set_reg_event_process
 ��������  : ����jion reqʱ��������Ӧ�Ĵ���
 �������  : �¼��ṹ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��4��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_join_set_reg_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                 *pst_event;
    frw_event_hdr_stru             *pst_event_hdr;
    dmac_ctx_join_req_set_reg_stru *pst_reg_params;
    mac_device_stru                *pst_device;
    dmac_vap_stru                  *pst_dmac_vap;
    mac_vap_stru                   *pst_vap_up;     /* ����UP״̬��VAP */
#ifdef _PRE_WLAN_FEATURE_ROAM
    dmac_user_stru                 *pst_dmac_user;
#endif //_PRE_WLAN_FEATURE_ROAM


    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_join_req_set_reg_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_dpd_enbale = OAL_TRUE;

    pst_dmac_vap->st_vap_base_info.st_cap_flag.bit_dpd_done   = OAL_FALSE;

    /* ͬ��dmac vap���ŵ���Ϣ */
    pst_dmac_vap->st_vap_base_info.st_channel = pst_reg_params->st_current_channel;

    mac_vap_set_bssid(&pst_dmac_vap->st_vap_base_info, pst_reg_params->auc_bssid);

    /* дSTA BSSID�Ĵ���*/
    hal_set_sta_bssid(pst_dmac_vap->pst_hal_vap, pst_reg_params->auc_bssid);

    /* ͬ��beacon period */
    pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = pst_reg_params->us_beacon_period;

    if (0 != pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod)
    {
        OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::beacon period[%d]}",
                         pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);
        /* ��beacon������д��Ĵ��� */
        hal_vap_set_psm_beacon_period(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod);
    }
    /* ����tbtt offset��λus */
    hal_set_psm_tbtt_offset(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->us_in_tbtt_offset);

    /* ����sta tbtt��ʱ�� */
    hal_enable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* ����tbtt offset ��λms */
    hal_set_psm_ext_tbtt_offset(pst_dmac_vap->pst_hal_vap, pst_dmac_vap->us_ext_tbtt_offset);

    /* ���ý���beacon��ʱ�жϵ�ʱ�� */
    hal_set_beacon_timeout_val(pst_dmac_vap->pst_hal_device, pst_dmac_vap->us_beacon_timeout);

    /*����beacon timout�ж� */
    hal_vap_set_psm_tsf_ctrl(pst_dmac_vap->pst_hal_vap, 0x3);


#endif

    /* ֪ͨ�㷨 */
	/* DTS2016061707848 ֪ͨ�㷨�û����ߣ��ڸ������û������������ߣ���֤dbac���ŵ���Ϣ��ȷ */
    dmac_alg_vap_down_notify(&pst_dmac_vap->st_vap_base_info);
    dmac_alg_cfg_channel_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_MOVE_WORK);
    dmac_alg_cfg_bandwidth_notify(&pst_dmac_vap->st_vap_base_info, CH_BW_CHG_TYPE_MOVE_WORK);

    /* ����д���UP״̬��VAP���˴��������ŵ���Ҫ������֡ */
    pst_vap_up = mac_device_find_another_up_vap(pst_device, pst_dmac_vap->st_vap_base_info.uc_vap_id);
    dmac_mgmt_connect_set_channel(pst_device, pst_vap_up, &(pst_reg_params->st_current_channel));

/* �����02ģʽ�£���Ҫ���ŵ���Ϣͬ����dmac vap�ṹ���� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_memcopy(&(pst_dmac_vap->st_vap_base_info.st_channel), &(pst_reg_params->st_current_channel), OAL_SIZEOF(mac_channel_stru));
#endif

    dmac_vap_init_tx_ucast_data_frame(pst_dmac_vap);

    /* ��ʼ��Ĭ�Ͻ���beacon֡ */
    /* ��ֹ�����������޸ļĴ�������д�Ĵ�������beacon֡ */
    if(OAL_FALSE == pst_reg_params->ul_beacon_filter)
    {
        /* �ر�beacon֡����  */
        hal_disable_beacon_filter(pst_device->pst_device_stru);
    }

    /* ��ʼ��Ĭ�ϲ�����non_direct_frame֡*/
    /* Ϊ��ֹ�����������޸ļĴ�����д�Ĵ���������non_direct_frame֡ */
    if(OAL_TRUE == pst_reg_params->ul_non_frame_filter)
    {
        /* ��non frame֡���� */
        hal_enable_non_frame_filter(pst_device->pst_device_stru);
    }

    /* �����Ż�����ͬƵ���µ�������һ�� */
    if (WLAN_BAND_2G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
    {
        mac_mib_set_ShortPreambleOptionImplemented(&pst_dmac_vap->st_vap_base_info, WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&pst_dmac_vap->st_vap_base_info, OAL_FALSE);
    }
    else
    {
        mac_mib_set_ShortPreambleOptionImplemented(&pst_dmac_vap->st_vap_base_info, WLAN_LEGACY_11B_MIB_LONG_PREAMBLE);
        mac_mib_set_SpectrumManagementRequired(&pst_dmac_vap->st_vap_base_info, OAL_TRUE);
    }

    /* ͬ������device��FortyMHzOperationImplemented mib�� */
    mac_mib_set_FortyMHzOperationImplemented(&(pst_dmac_vap->st_vap_base_info), pst_reg_params->en_dot11FortyMHzOperationImplemented);

    /* ����ssid */
    oal_memcopy(pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID, pst_reg_params->auc_ssid, WLAN_SSID_MAX_LEN);
    pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID[WLAN_SSID_MAX_LEN - 1] = '\0';

#ifdef _PRE_WLAN_FEATURE_ROAM
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id);
    if (pst_dmac_user)
    {
        /* �����û�mac */
        oal_set_mac_addr(pst_dmac_user->st_user_base_info.auc_user_mac_addr, pst_reg_params->auc_bssid);
        hal_ce_del_peer_macaddr(pst_dmac_vap->pst_hal_device, pst_dmac_user->uc_lut_index);
        hal_ce_add_peer_macaddr(pst_dmac_vap->pst_hal_device, pst_dmac_user->uc_lut_index, pst_reg_params->auc_bssid);
    }

#endif //_PRE_WLAN_FEATURE_ROAM

#if 0
OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{call DPD Calibration Start function}");

#ifdef _PRE_WLAN_RF_110X_CALI_DPD

    if (WLAN_BAND_2G == pst_dmac_vap->st_vap_base_info.st_channel.en_band)
    {
      dmac_start_dpd_calibration(pst_vap_up);
    }
#endif
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_join_set_dtim_reg_event_process
 ��������  : joinʱ����dtim��Ӧ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��4��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_join_set_dtim_reg_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    dmac_ctx_set_dtim_tsf_reg_stru      *pst_reg_params;
    mac_device_stru                     *pst_device;
    dmac_vap_stru                       *pst_dmac_vap;


    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{dmac_join_set_dtim_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_set_dtim_tsf_reg_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_dtim_reg_event_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{dmac_join_set_reg_event_process::pst_dmac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    /* дbssid �Ĵ��� */
    hal_set_sta_bssid(pst_dmac_vap->pst_hal_vap,pst_reg_params->auc_bssid);

    /* */
    mac_vap_set_bssid(&pst_dmac_vap->st_vap_base_info, pst_reg_params->auc_bssid);

    /* дtsf �Ĵ��� */
    if(OAL_TRUE == (oal_uint32)pst_reg_params->us_tsf_bit0)
    {
       /* enable tbtt */
       hal_enable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);
    }

    return OAL_SUCC;

}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 �� �� ��  : dmac_set_smps_process
 ��������  : DMAC����SMPSģʽ������(����MAC�Ĵ�����ʹ��SMPS)
 �������  : pst_event_mem--�¼�ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��17��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_set_smps_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                         *pst_event;
    frw_event_hdr_stru                     *pst_event_hdr;
    mac_cfg_smps_mode_stru                 *pst_smps_mode;
    hal_smps_mode_enum_uint8                en_smps_mode;
    mac_device_stru                        *pst_device;
    mac_vap_stru                           *pst_mac_vap;
    mac_user_stru                          *pst_mac_user;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SMPS, "{dmac_set_smps_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_smps_mode           = (mac_cfg_smps_mode_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device   = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SMPS, "{dmac_set_smps_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SMPS, "{dmac_set_smps_process::pst_mac_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user = mac_res_get_mac_user(pst_smps_mode->us_user_idx);

    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SMPS, "{dmac_set_smps_process::pst_mac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_alg_cfg_smps_notify(pst_mac_vap, pst_mac_user);

    pst_device->uc_dev_smps_mode = pst_smps_mode->uc_smps_mode;

    if (WLAN_MIB_MIMO_POWER_SAVE_MIMO == pst_smps_mode->uc_smps_mode)
    {
        pst_device->en_smps = OAL_FALSE;
        en_smps_mode = HAL_SMPS_MODE_DISABLE;
    }
    else
    {
        pst_device->en_smps = OAL_TRUE;
        en_smps_mode = (hal_smps_mode_enum_uint8)(pst_smps_mode->uc_smps_mode);
    }

    /* дSMPS���ƼĴ��� */
    hal_set_smps_mode(pst_device->pst_device_stru, en_smps_mode);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_asoc_set_reg_event_process
 ��������  : ����ʱд�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��18��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_asoc_set_reg_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    dmac_ctx_asoc_set_reg_stru       *pst_reg_params;
    mac_device_stru                     *pst_device;
    dmac_user_stru                      *pst_dmac_user;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{dmac_asoc_set_reg_event_process::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_reg_params          = (dmac_ctx_asoc_set_reg_stru *)pst_event->auc_event_data;

    /* ��ȡdevice�ṹ����Ϣ */
    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ASSOC, "{dmac_join_set_reg_event_process::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    pst_dmac_user = mac_res_get_dmac_user(pst_reg_params->uc_user_index);

    if (OAL_PTR_NULL == pst_dmac_user)
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ASSOC, "{dmac_join_set_reg_event_process::pst_dmac_user null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ֧��QOS �����Ĵ���*/
    hal_machw_seq_num_index_update_per_tid(pst_device->pst_device_stru, pst_dmac_user->uc_lut_index, OAL_TRUE);

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : dmac_mgmt_conn_result_event
 ��������  : ����hmac�����Ĺ�������¼�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_mgmt_conn_result_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                      *pst_event;
    frw_event_hdr_stru                  *pst_event_hdr;
    oal_uint32                           ul_result;
    mac_device_stru                     *pst_device;
    mac_vap_stru                        *pst_vap_up;

    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "pst_event_mem null.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼����¼�ͷ�Լ��¼�payload�ṹ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    ul_result               = *((oal_uint32 *)pst_event->auc_event_data);

    pst_device = mac_res_get_dev(pst_event_hdr->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_mgmt_conn_result_event::pst_device[%d] is NULL!}", pst_event_hdr->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_SUCC != ul_result)
    {
        /* �����vap up����ָ����Ǹ�vap���ڵ��ŵ� */
        pst_vap_up = mac_device_find_another_up_vap(pst_device, pst_event_hdr->uc_vap_id);
        if (OAL_PTR_NULL != pst_vap_up)
        {
            if (MAC_VAP_STATE_PAUSE == pst_vap_up->en_vap_state)
            {
                pst_device->st_home_channel = pst_vap_up->st_channel;
                dmac_scan_switch_channel_back(pst_device);

                OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_DBAC, "dmac_mgmt_conn_result_event: conn fail, switch to up vap. channel num:%d",
                                pst_device->st_home_channel.uc_chan_number);
            }
        }
    }

    dmac_tx_fake_queue_empty_assert(pst_device->pst_device_stru, HAL_TX_FAKE_QUEUE_BGSCAN_ID, THIS_FILE_ID);

    return OAL_SUCC;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

