/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_encap_frame_sta.c
  �� �� ��   : ����
  ��    ��   : y00184180
  ��������   : 2013��6��28��
  ����޸�   :
  ��������   : STAģʽ��֡��HMAC�� STA����֡����֡�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��28��
    ��    ��   : y00184180
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
#include "wlan_spec.h"
#include "wlan_mib.h"
#include "mac_vap.h"
#include "mac_frame.h"
#include "hmac_encap_frame_sta.h"
#include "hmac_user.h"
#include "hmac_main.h"
#include "hmac_tx_data.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_mgmt_sta.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ENCAP_FRAME_STA_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : mac_set_supported_rates_ie
 ��������  : �������ʼ�
 �������  : pst_hmac_sta: ָ��vap
             puc_buffer: ָ��buffer
 �������  : puc_ie_len: element�ĳ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��12��
    ��    ��   : zhangxiang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_set_supported_rates_ie_asoc_req(hmac_vap_stru *pst_hmac_sta, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{

    oal_uint8         uc_nrates;
    oal_uint8         uc_idx;

    /**************************************************************************
                        ---------------------------------------
                        |Element ID | Length | Supported Rates|
                        ---------------------------------------
             Octets:    |1          | 1      | 1~8            |
                        ---------------------------------------
    The Information field is encoded as 1 to 8 octets, where each octet describes a single Supported
    Rate or BSS membership selector.
    **************************************************************************/
    puc_buffer[0] = MAC_EID_RATES;

    uc_nrates = pst_hmac_sta->uc_rs_nrates;

    if (uc_nrates > MAC_MAX_SUPRATES)
    {
        uc_nrates = MAC_MAX_SUPRATES;
    }

    for (uc_idx = 0; uc_idx < uc_nrates; uc_idx++)
    {
        puc_buffer[MAC_IE_HDR_LEN + uc_idx] = pst_hmac_sta->auc_supp_rates[uc_idx];
    }

    puc_buffer[1] = uc_nrates;

    *puc_ie_len = MAC_IE_HDR_LEN + uc_nrates;
}
/*****************************************************************************
 �� �� ��  : mac_set_exsup_rates_ie
 ��������  : ���extended supported rates��Ϣ
 �������  : pst_hmac_sta: ָ��vap
             puc_buffer: ָ��buffer
 �������  : puc_ie_len: element�ĳ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��12��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_set_exsup_rates_ie_asoc_req(hmac_vap_stru *pst_hmac_sta, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len)
{
    oal_uint8         uc_nrates;
    oal_uint8         uc_idx;


    /***************************************************************************
                   -----------------------------------------------
                   |ElementID | Length | Extended Supported Rates|
                   -----------------------------------------------
       Octets:     |1         | 1      | 1-255                   |
                   -----------------------------------------------
    ***************************************************************************/
    if (pst_hmac_sta->uc_rs_nrates <= MAC_MAX_SUPRATES)
    {
        *puc_ie_len = 0;

        return;
    }

    puc_buffer[0] = MAC_EID_XRATES;
    uc_nrates     = pst_hmac_sta->uc_rs_nrates - MAC_MAX_SUPRATES;
    puc_buffer[1] = uc_nrates;

    for (uc_idx = 0; uc_idx < uc_nrates; uc_idx++)
    {
        puc_buffer[MAC_IE_HDR_LEN + uc_idx] = pst_hmac_sta->auc_supp_rates[uc_idx + MAC_MAX_SUPRATES];
    }

    *puc_ie_len = MAC_IE_HDR_LEN + uc_nrates;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_encap_asoc_req_sta
 ��������  : ��֡(Re)assoc
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��28��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_mgmt_encap_asoc_req_sta(hmac_vap_stru *pst_hmac_sta, oal_uint8 *puc_req_frame, oal_uint8 *puc_curr_bssid)
{

    oal_uint8               uc_ie_len            = 0;
    oal_uint32              us_asoc_rsq_len      = 0;
    oal_uint8              *puc_req_frame_origin;
    mac_vap_stru           *pst_mac_vap;
    mac_device_stru        *pst_mac_device;
    oal_uint16              us_app_ie_len        = 0;
    en_app_ie_type_uint8    en_app_ie_type;

#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_txbf_cap_stru *pst_txbf_cap;
#endif

#ifdef _PRE_WLAN_FEATURE_11R
        wlan_wme_ac_type_enum_uint8 en_aci;
        wlan_wme_ac_type_enum_uint8 en_target_ac;
        oal_uint8                   uc_tid;
#endif

    if ((OAL_PTR_NULL == pst_hmac_sta) || (OAL_PTR_NULL == puc_req_frame))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ASSOC, "{hmac_mgmt_encap_asoc_req_sta::null param, pst_hmac_sta=%d puc_req_frame=%d.}",
                       pst_hmac_sta, puc_req_frame);
        return us_asoc_rsq_len;
    }

    /* ������ʼ��ַ��������㳤��*/
    puc_req_frame_origin = puc_req_frame;

    pst_mac_vap = &(pst_hmac_sta->st_vap_base_info);

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_encap_asoc_req_sta::pst_mac_device null.}");
        return us_asoc_rsq_len;
    }

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    /* ���� Frame Control field */
    /* �ж��Ƿ�Ϊreassoc���� */
    if (OAL_PTR_NULL != puc_curr_bssid)
    {
        mac_hdr_set_frame_control(puc_req_frame, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_REASSOC_REQ);

    }
    else
    {
        mac_hdr_set_frame_control(puc_req_frame, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ASSOC_REQ);
    }
    /* ���� DA address1: AP MAC��ַ (BSSID)*/
    oal_set_mac_addr(puc_req_frame + WLAN_HDR_ADDR1_OFFSET, pst_hmac_sta->st_vap_base_info.auc_bssid);

    /* ���� SA address2: dot11MACAddress */
    oal_set_mac_addr(puc_req_frame + WLAN_HDR_ADDR2_OFFSET, pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* ���� DA address3: AP MAC��ַ (BSSID)*/
    oal_set_mac_addr(puc_req_frame + WLAN_HDR_ADDR3_OFFSET, pst_hmac_sta->st_vap_base_info.auc_bssid);

    puc_req_frame += MAC_80211_FRAME_LEN;

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*              Association Request Frame - Frame Body                   */
    /* --------------------------------------------------------------------- */
    /* | Capability Information | Listen Interval | SSID | Supported Rates | */
    /* --------------------------------------------------------------------- */
    /* |2                       |2                |2-34  |3-10             | */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* |Externed Surpported rates| Power Capability | Supported Channels   | */
    /* --------------------------------------------------------------------- */
    /* |3-257                    |4                 |4-256                 | */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* | RSN   | QoS Capability | HT Capabilities | Extended Capabilities  | */
    /* --------------------------------------------------------------------- */
    /* |36-256 |3               |28               |3-8                     | */
    /* --------------------------------------------------------------------- */

    /* --------------------------------------------------------------------- */
    /* | WPS   | P2P |                                                       */
    /* --------------------------------------------------------------------- */
    /* |7-257  |X    |                                                       */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/
    mac_set_cap_info_sta((oal_void *)pst_mac_vap, puc_req_frame);
    puc_req_frame += MAC_CAP_INFO_LEN;

    /* ���� Listen Interval IE */
    mac_set_listen_interval_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* Ressoc��֡����Current AP address */
    if (OAL_PTR_NULL != puc_curr_bssid)
    {
        oal_set_mac_addr(puc_req_frame, puc_curr_bssid);
        puc_req_frame += OAL_MAC_ADDR_LEN;
    }
    /* ���� SSID IE */
    mac_set_ssid_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len, WLAN_FC0_SUBTYPE_ASSOC_REQ);
    puc_req_frame += uc_ie_len;
    /*DTS2015052811128:�ڹ�������ʱʹ��ɨ��ʱ��������ʼ� --z00285102*/
#if  defined(_PRE_WIFI_DMT ) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    /* ���� Supported Rates IE */
    mac_set_supported_rates_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* ���� Extended Supported Rates IE */
    mac_set_exsup_rates_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

#else
    /* ���� Supported Rates IE */
    hmac_set_supported_rates_ie_asoc_req(pst_hmac_sta, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* ���� Extended Supported Rates IE */
    hmac_set_exsup_rates_ie_asoc_req(pst_hmac_sta, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;
#endif
    /* ���� Power Capability IE */
    mac_set_power_cap_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* ���� Supported channel IE */
    mac_set_supported_channel_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

/* DTS2015030605900 Ϊ���Ӽ����ԣ�02��ʹ��������װ��wpa/wpa2 ie��ʹ���ϲ��·��� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    if (pst_hmac_sta->uc_80211i_mode == DMAC_RSNA_802_11I)
    {
        /* ���� RSN Capability IE */
        mac_set_rsn_ie((oal_void *)pst_mac_vap, OAL_PTR_NULL, puc_req_frame, &uc_ie_len);
        puc_req_frame += uc_ie_len;
    }
    else if (pst_hmac_sta->uc_80211i_mode == DMAC_WPA_802_11I)
    {
        /* ���� WPA Capability IE */
        mac_set_wpa_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
        puc_req_frame += uc_ie_len;
    }
#endif /* defined (_PRE_WLAN_FEATURE_WPA) || defiend (_PRE_WLAN_FEATURE_WPA) */
#endif

    /* ���WMM element */
    if (OAL_TRUE == pst_hmac_sta->uc_wmm_cap)
    {
        mac_set_wmm_ie_sta((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
        puc_req_frame += uc_ie_len;
    }

    /* ���� HT Capability IE  */
    mac_set_ht_capabilities_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
#ifdef _PRE_WLAN_FEATURE_TXBF
    if ((OAL_TRUE == pst_mac_vap->bit_ap_11ntxbf)
    && (OAL_TRUE == pst_mac_vap->st_cap_flag.bit_11ntxbf)
    && (0 != uc_ie_len))
    {
        puc_req_frame += MAC_11N_TXBF_CAP_OFFSET;

        pst_txbf_cap  = (mac_txbf_cap_stru *)puc_req_frame;
        pst_txbf_cap->bit_rx_stagg_sounding             = OAL_TRUE;
        pst_txbf_cap->bit_explicit_compr_bf_fdbk        = 1;
        pst_txbf_cap->bit_compr_steering_num_bf_antssup = 1;
        puc_req_frame -= MAC_11N_TXBF_CAP_OFFSET;
    }
#endif
    puc_req_frame += uc_ie_len;

#ifdef _PRE_WLAN_FEATURE_11K
    if (OAL_TRUE == pst_hmac_sta->bit_11k_enable)
    {
        mac_set_rrm_enabled_cap_field((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
        puc_req_frame += uc_ie_len;
    }
#endif //_PRE_WLAN_FEATURE_11K

    /* ���� Extended Capability IE */
    mac_set_ext_capabilities_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;

    /* ���� VHT Capability IE */
    mac_set_vht_capabilities_ie((oal_void *) pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;


#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_set_11ntxbf_vendor_ie(pst_mac_vap, puc_req_frame, &uc_ie_len);
    puc_req_frame += uc_ie_len;
#endif

#ifdef _PRE_WLAN_FEATURE_11R
    if (OAL_TRUE == pst_hmac_sta->bit_11r_enable)
    {
        mac_set_md_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len);
        puc_req_frame += uc_ie_len;

        /* Reasoc�а���RIC-Req */
        if (pst_hmac_sta->bit_reassoc_flag)
        {
            for (en_aci = WLAN_WME_AC_BE; en_aci < WLAN_WME_AC_BUTT; en_aci++)
            {
                if (pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[en_aci].en_dot11QAPEDCATableMandatory)
                {
                    en_target_ac = en_aci;
                    uc_tid = WLAN_WME_AC_TO_TID(en_target_ac);
                    mac_set_rde_ie((oal_void *)pst_mac_vap,puc_req_frame, &uc_ie_len);
                    puc_req_frame += uc_ie_len;

                    mac_set_tspec_ie((oal_void *)pst_mac_vap, puc_req_frame, &uc_ie_len, uc_tid);
                    puc_req_frame += uc_ie_len;
                }
            }
        }
    }

#endif //_PRE_WLAN_FEATURE_11R

    en_app_ie_type = OAL_APP_ASSOC_REQ_IE;

#ifdef _PRE_WLAN_FEATURE_ROAM
    if (OAL_PTR_NULL != puc_curr_bssid)
    {
        en_app_ie_type = OAL_APP_REASSOC_REQ_IE;
#ifdef _PRE_WLAN_FEATURE_11R
        if(OAL_TRUE == pst_hmac_sta->bit_11r_enable)
        {
            if (OAL_TRUE == pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated)
            {
                en_app_ie_type = OAL_APP_FT_IE;
            }
        }

#endif //_PRE_WLAN_FEATURE_11R
    }
#endif //_PRE_WLAN_FEATURE_ROAM

    /* ���P2P/WPS IE ��Ϣ */
    mac_add_app_ie(pst_mac_vap, puc_req_frame, &us_app_ie_len, en_app_ie_type);
    /* DTS2015021504247 P2P���� ������͵Ĺ�������û��P2P WPS IE��Ϣ */
    puc_req_frame += us_app_ie_len;

    us_asoc_rsq_len = (oal_uint32)(puc_req_frame - puc_req_frame_origin);

    return us_asoc_rsq_len;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_prepare_auth_req
 ��������  : ��seq = 1 ��auth req֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_auth_req(hmac_vap_stru *pst_hmac_sta, oal_uint8 *puc_mgmt_frame)
{
    oal_uint16      us_auth_req_len;
    hmac_user_stru *pst_user_ap;
    oal_uint16      us_auth_type;
    oal_uint32      ul_ret;
    oal_uint16      us_user_index;
#ifdef _PRE_WLAN_FEATURE_11R
    oal_uint16      us_app_ie_len;
#endif //_PRE_WLAN_FEATURE_11R

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    mac_hdr_set_frame_control(puc_mgmt_frame, WLAN_FC0_SUBTYPE_AUTH);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address1, pst_hmac_sta->st_vap_base_info.auc_bssid);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address2, pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address3, pst_hmac_sta->st_vap_base_info.auc_bssid);
    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*              Authentication Frame (Sequence 1) - Frame Body           */
    /* --------------------------------------------------------------------  */
    /* |Auth Algorithm Number|Auth Transaction Sequence Number|Status Code|  */
    /* --------------------------------------------------------------------  */
    /* | 2                   |2                               |2          |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    if(OAL_FALSE == pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked)
    {
        /* Open System */
        puc_mgmt_frame[MAC_80211_FRAME_LEN]     = 0x00;
        puc_mgmt_frame[MAC_80211_FRAME_LEN + 1] = 0x00;
    }
    else
    {
        us_auth_type = (oal_uint16)pst_hmac_sta->en_auth_mode;

        if(WLAN_WITP_AUTH_SHARED_KEY == us_auth_type)
        {
            OAM_INFO_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_encap_auth_req::WLAN_WITP_AUTH_SHARED_KEY.}");
            us_auth_type = WLAN_WITP_AUTH_SHARED_KEY;
        }
        else
        {
            OAM_INFO_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_encap_auth_req::WLAN_WITP_AUTH_OPEN_SYSTEM.}");
            us_auth_type = WLAN_WITP_AUTH_OPEN_SYSTEM;
        }

        puc_mgmt_frame[MAC_80211_FRAME_LEN]     = (us_auth_type & 0xFF);
        puc_mgmt_frame[MAC_80211_FRAME_LEN + 1] = ((us_auth_type & 0xFF00) >> 8);
    }

    /* ���� Authentication Transaction Sequence Number Ϊ 1 */
    puc_mgmt_frame[MAC_80211_FRAME_LEN + 2] = 0x01;
    puc_mgmt_frame[MAC_80211_FRAME_LEN + 3] = 0x00;

    /* ���� Status Code Ϊ0. �����������ֶ�û�� . */
    puc_mgmt_frame[MAC_80211_FRAME_LEN + 4] = 0x00;
    puc_mgmt_frame[MAC_80211_FRAME_LEN + 5] = 0x00;

    /* ���� ��֤֡�ĳ��� */
    us_auth_req_len = MAC_80211_FRAME_LEN + MAC_AUTH_ALG_LEN + MAC_AUTH_TRANS_SEQ_NUM_LEN +
                   MAC_STATUS_CODE_LEN;

#ifdef _PRE_WLAN_FEATURE_11R
    if(OAL_TRUE == pst_hmac_sta->bit_11r_enable)
    {
        if ((OAL_TRUE == pst_hmac_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated)
             && (MAC_VAP_STATE_ROAMING == pst_hmac_sta->st_vap_base_info.en_vap_state))
        {
            /* FT System */
            puc_mgmt_frame[MAC_80211_FRAME_LEN] = 0x02;
            puc_mgmt_frame[MAC_80211_FRAME_LEN + 1] = 0x00;
            puc_mgmt_frame += us_auth_req_len;

            mac_add_app_ie((oal_void *)&pst_hmac_sta->st_vap_base_info, puc_mgmt_frame, &us_app_ie_len, OAL_APP_FT_IE);
            us_auth_req_len += us_app_ie_len;
            puc_mgmt_frame += us_app_ie_len;
        }
    }

#endif //_PRE_WLAN_FEATURE_11R

    pst_user_ap = (hmac_user_stru *)mac_res_get_hmac_user((oal_uint16)pst_hmac_sta->st_vap_base_info.uc_assoc_vap_id);
    if (OAL_PTR_NULL == pst_user_ap)
    {
        OAM_INFO_LOG0(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_encap_auth_req::no present ap, alloc new ap.}");
        ul_ret = hmac_user_add(&pst_hmac_sta->st_vap_base_info, pst_hmac_sta->st_vap_base_info.auc_bssid, &us_user_index);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_hmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                             "{hmac_mgmt_encap_auth_req::hmac_user_add failed[%d].}", ul_ret);
            us_auth_req_len = 0;
        }
    }

    return us_auth_req_len;
}

/*****************************************************************************
 �� �� ��  : hmac_prepare_auth_req_seq3
 ��������  : Ϊshared key׼��seq = 3 ����֤֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint16  hmac_mgmt_encap_auth_req_seq3(hmac_vap_stru *pst_sta, oal_uint8 *puc_mgmt_frame, oal_uint8 *puc_mac_hrd)
{
    oal_uint8  *puc_data       = OAL_PTR_NULL;
    oal_uint16  us_index        = 0;
    oal_uint16  us_auth_req_len = 0;
    oal_uint8  *puc_ch_text     = OAL_PTR_NULL;
    oal_uint8   uc_ch_text_len  = 0;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    mac_hdr_set_frame_control(puc_mgmt_frame, WLAN_FC0_SUBTYPE_AUTH);

    /* ��֡�����ֶ���1 */
    mac_set_wep(puc_mgmt_frame, 1);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address1, pst_sta->st_vap_base_info.auc_bssid);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address2, pst_sta->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_mgmt_frame)->auc_address3, pst_sta->st_vap_base_info.auc_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*              Authentication Frame (Sequence 3) - Frame Body           */
    /* --------------------------------------------------------------------- */
    /* |Auth Algo Number|Auth Trans Seq Number|Status Code| Challenge Text | */
    /* --------------------------------------------------------------------- */
    /* | 2              |2                    |2          | 3 - 256        | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* ��ȡ��֤֡payload */
    us_index = MAC_80211_FRAME_LEN;
    puc_data = (oal_uint8 *)(puc_mgmt_frame + us_index);

    /* ���� ��֤֡�ĳ��� */
    us_auth_req_len = MAC_80211_FRAME_LEN + MAC_AUTH_ALG_LEN + MAC_AUTH_TRANS_SEQ_NUM_LEN +
                      MAC_STATUS_CODE_LEN;

    /* In case of no failure, the frame must be WEP encrypted. 4 bytes must  */
    /* be   left for the  IV  in  that  case. These   fields will  then  be  */
    /* reinitialized, using the correct index, with offset for IV field.     */
    puc_data[0] = WLAN_WITP_AUTH_SHARED_KEY;    /* Authentication Algorithm Number               */
    puc_data[1] = 0x00;

    puc_data[2] = 0x03;                    /* Authentication Transaction Sequence Number    */
    puc_data[3] = 0x00;

    /* If WEP subfield in the  incoming  authentication frame is 1,  respond */
    /* with  'challenge text failure' status,  since the STA does not expect */
    /* an encrypted frame in this state.                                     */
    if(1 == mac_is_protectedframe(puc_mac_hrd))
    {
        puc_data[4] = MAC_CHLNG_FAIL;
        puc_data[5] = 0x00;
    }

    /* If the STA does not support WEP, respond with 'unsupported algo'      */
    /* status, since WEP is necessary for Shared Key Authentication.         */
    else if(OAL_FALSE == mac_is_wep_enabled(&(pst_sta->st_vap_base_info)))
    {
        puc_data[4] = MAC_UNSUPT_ALG;
        puc_data[5] = 0x00;
    }

    /* If the default WEP key is NULL, respond with 'challenge text failure' */
    /* status, since a NULL key value cannot be used for WEP operations.     */
    else if(mac_get_wep_default_keysize(&pst_sta->st_vap_base_info) == 0)
    {
        puc_data[4] = MAC_CHLNG_FAIL;
        puc_data[5] = 0x00;
    }

    /* If there is a mapping in dot11WEPKeyMappings matching the address of  */
    /* the AP, and the corresponding key is NULL respond with 'challenge     */
    /* text failure' status. This is currently not being used.               */

    /* No error condition detected */
    else
    {

        /* Set Status Code to 'success' */
        puc_data[4] = MAC_SUCCESSFUL_STATUSCODE;
        puc_data[5] = 0x00;

        /* Extract 'Challenge Text' and its 'length' from the incoming       */
        /* authentication frame                                              */
        uc_ch_text_len = puc_mac_hrd[MAC_80211_FRAME_LEN + 7];
        puc_ch_text     = (oal_uint8 *)(&puc_mac_hrd[MAC_80211_FRAME_LEN + 8]);

        /* Challenge Text Element                  */
        /* --------------------------------------- */
        /* |Element ID | Length | Challenge Text | */
        /* --------------------------------------- */
        /* | 1         |1       |1 - 253         | */
        /* --------------------------------------- */

        puc_mgmt_frame[us_index + 6]   = MAC_EID_CHALLENGE;
        puc_mgmt_frame[us_index + 7]   = uc_ch_text_len;
        oal_memcopy(&puc_mgmt_frame[us_index + 8], puc_ch_text, uc_ch_text_len);

        /* Add the challenge text element length to the authentication       */
        /* request frame length. The IV, ICV element lengths will be added   */
        /* after encryption.                                                 */
        us_auth_req_len += (uc_ch_text_len + MAC_IE_HDR_LEN);
    }

    return us_auth_req_len;
}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 �� �� ��  : hmac_mgmt_encap_smps_sta
 ��������  : Hmac��֡
 �������  : ��
 �������  : ��
 �� �� ֵ  : ֡��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��16��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_mgmt_encap_smps_sta(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buffer)
{

    oal_uint16                     us_index;
    oal_uint8                      uc_smps_mode;
    mac_device_stru               *pst_mac_device;

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/
    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        return 0;
    }

    /* ���� Frame Control field */
    mac_hdr_set_frame_control(puc_buffer, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* ���÷�Ƭ���Ϊ0 */
    mac_hdr_set_fragment_number(puc_buffer, 0);

    /* ���� address1(���ն�): AP MAC��ַ (BSSID)*/
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR1_OFFSET, pst_mac_vap->auc_bssid);

    /* ���� address2(���Ͷ�): dot11StationID */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR2_OFFSET, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* ���� address3: AP MAC��ַ (BSSID) */
    oal_set_mac_addr(puc_buffer + WLAN_HDR_ADDR3_OFFSET, pst_mac_vap->auc_bssid);

    /*************************************************************************/
    /*                  SMPS Management frame - Frame Body                   */
    /* ----------------------------------------------------------------------*/
    /* |Category |HT Action |SMPS Control field|                             */
    /* ----------------------------------------------------------------------*/
    /* |1        |1         |1                 |                             */
    /* ----------------------------------------------------------------------*/
    /*                                                                       */
    /*************************************************************************/
    us_index = MAC_80211_FRAME_LEN;

    puc_buffer[us_index++] = MAC_ACTION_CATEGORY_HT;           /* Category  */
    puc_buffer[us_index++] = MAC_HT_ACTION_SMPS;               /* HT Action */

    /* SMPS Control field */
    /* Bit0 --- enable/disable smps   Bit1 --- SMPS MODE */
    puc_buffer[us_index] = 0;                                /* Element ID */

    uc_smps_mode = mac_mib_get_smps(pst_mac_vap);

    if ((OAL_FALSE == pst_mac_device->en_smps) || (WLAN_MIB_MIMO_POWER_SAVE_MIMO == uc_smps_mode))
    {
        puc_buffer[us_index++] = pst_mac_device->en_smps;
    }
    else
    {
        puc_buffer[us_index++] = ((uc_smps_mode | (pst_mac_device->en_smps)) & (BIT0 | BIT1));
    }

    return us_index;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

