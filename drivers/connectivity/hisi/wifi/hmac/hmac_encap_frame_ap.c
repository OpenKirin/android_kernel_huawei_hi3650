/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_encap_frame_ap.c
  �� �� ��   : ����
  ��    ��   : y00184180
  ��������   : 2013��6��28��
  ����޸�   :
  ��������   : APģʽ��֡�ļ���APģʽ����֡����֡
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
#include "oal_cfg80211.h"
#include "wlan_spec.h"
#include "mac_frame.h"
#include "mac_user.h"
#include "mac_vap.h"
#include "dmac_ext_if.h"
#include "hmac_encap_frame_ap.h"
#include "hmac_main.h"
#include "hmac_tx_data.h"
#include "hmac_mgmt_ap.h"
#include "hmac_11i.h"
#include "hmac_blockack.h"
#include "hmac_mgmt_bss_comm.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ENCAP_FRAME_AP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
/*****************************************************************************
 �� �� ��  : mac_get_assoc_comeback_time
 ��������  : ����õ� assoc rsp �������assoc comeback time
 �������  : pst_mac_vap   : mac vap ָ��
             pst_hmac_user : hamc user ָ��
 �������  : ��
 �� �� ֵ  : ����õ���assoc comeback timeֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��28��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_get_assoc_comeback_time(mac_vap_stru *pst_mac_vap,
                                                              hmac_user_stru *pst_hmac_user)
{
    oal_uint32                     ul_timeout = 0;

    oal_uint32                     ul_now_time;
    oal_uint32                     ul_passed_time;
    oal_uint32                     ul_sa_query_maxtimeout;

    /* ��ȡ����ʱ�� */
    ul_now_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ����ASSOCIATION_COMEBACK_TIME��ʹSTA��AP���SA Query����֮���ٷ��͹������� */
    /* ���sa Query Max timeoutֵ */
    ul_sa_query_maxtimeout = mac_mib_get_dot11AssociationSAQueryMaximumTimeout(pst_mac_vap);

    /* �Ƿ�������sa Query�������ڽ��� */
    if ((OAL_TRUE == pst_hmac_user->st_sa_query_info.st_sa_query_interval_timer.en_is_enabled) &&
       (ul_now_time >= pst_hmac_user->st_sa_query_info.ul_sa_query_start_time))
    {
        /* ������SA Query���̽�����ſ��Խ���STA�������Ĺ���֡ */
        ul_passed_time = ul_now_time - pst_hmac_user->st_sa_query_info.ul_sa_query_start_time;
        ul_timeout = ul_sa_query_maxtimeout - ul_passed_time;
    }
    else
    {
        /* ����������SA Query����Ԥ��ʱ�� */
        ul_timeout = ul_sa_query_maxtimeout;
    }

    return ul_timeout;
}
#endif


/*****************************************************************************
 �� �� ��  : hmac_mgmt_encap_asoc_rsp_ap
 ��������  : �������Ӧ֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_mgmt_encap_asoc_rsp_ap(
                mac_vap_stru                   *pst_mac_ap,
                oal_uint8                      *puc_sta_addr,
                oal_uint16                      us_assoc_id,
                mac_status_code_enum_uint16     en_status_code,
                oal_uint8                      *puc_asoc_rsp,
                oal_uint16                      us_type)
{
    oal_uint32                     us_asoc_rsp_len       = 0;
    oal_uint8                      uc_ie_len             = 0;
    oal_uint32                     ul_timeout = 0;
    mac_device_stru               *pst_mac_device;
    oal_uint8                     *puc_asoc_rsp_original;
    mac_Timeout_Interval_type_enum en_tie_type           = MAC_TIE_BUTT;

    mac_user_stru     *pst_mac_user;
    hmac_user_stru    *pst_hmac_user;
    oal_uint16         us_app_ie_len;
#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_txbf_cap_stru *pst_txbf_cap;
#endif

    if ((OAL_PTR_NULL == pst_mac_ap) || (OAL_PTR_NULL == puc_sta_addr) || (OAL_PTR_NULL == puc_asoc_rsp))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ASSOC, "{hmac_mgmt_encap_asoc_rsp_ap::pst_mac_ap[0x%x], puc_data[0x%x], puc_asoc_req[0x%x].}", pst_mac_ap, puc_sta_addr, puc_asoc_rsp);
        return us_asoc_rsp_len;
    }

    /* ������ʼ��ַ��������㳤��*/
    puc_asoc_rsp_original = puc_asoc_rsp;

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_ap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_mac_ap->uc_vap_id, OAM_SF_ASSOC, "{hmac_mgmt_encap_asoc_rsp_ap::pst_mac_device is a null ptr.[0x%x]}", pst_mac_device);
        return us_asoc_rsp_len;
    }

    pst_mac_user = mac_res_get_mac_user(us_assoc_id);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC,"{hmac_mgmt_encap_asoc_rsp_ap::pst_mac_user is a null ptr.}");
        return us_asoc_rsp_len;
    }
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_assoc_id);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ASSOC,"{hmac_mgmt_encap_asoc_rsp_ap::pst_hmac_user(idx=%d) is a null ptr.}", us_assoc_id);
        return us_asoc_rsp_len;
    }

    if(MAC_REJECT_TEMP == en_status_code)
    {
        en_tie_type = MAC_TIE_ASSOCIATION_COMEBACK_TIME;
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
    mac_hdr_set_frame_control(puc_asoc_rsp, us_type);

    /* ���� DA address1: STA MAC��ַ*/
    oal_set_mac_addr(puc_asoc_rsp + WLAN_HDR_ADDR1_OFFSET, puc_sta_addr);

    /* ���� SA address2: dot11MACAddress */
    oal_set_mac_addr(puc_asoc_rsp + WLAN_HDR_ADDR2_OFFSET, pst_mac_ap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    /* ���� DA address3: AP MAC��ַ (BSSID)*/
    oal_set_mac_addr(puc_asoc_rsp + WLAN_HDR_ADDR3_OFFSET, pst_mac_ap->auc_bssid);

    puc_asoc_rsp += MAC_80211_FRAME_LEN;

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*              Association Response Frame - Frame Body                  */
    /* --------------------------------------------------------------------- */
    /* | Capability Information |   Status Code   | AID | Supported  Rates | */
    /* --------------------------------------------------------------------- */
    /* |2                       |2                |2    |3-10              | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* ���� capability information field */
    mac_set_cap_info_ap((oal_void *)pst_mac_ap, puc_asoc_rsp);
    puc_asoc_rsp += MAC_CAP_INFO_LEN;

    /* ���� Status Code */
    mac_set_status_code_ie(puc_asoc_rsp,en_status_code);
    puc_asoc_rsp += MAC_STATUS_CODE_LEN;

    /* ���� Association ID */
    mac_set_aid_ie(puc_asoc_rsp, us_assoc_id);
    puc_asoc_rsp += MAC_AID_LEN;

    /* ���� Supported Rates IE */
    mac_set_supported_rates_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
    puc_asoc_rsp += uc_ie_len;

    /* ���� Extended Supported Rates IE */
    mac_set_exsup_rates_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
    puc_asoc_rsp += uc_ie_len;

    /* ���� EDCA IE */
    //mac_set_wmm_params_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
    mac_set_wmm_params_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, pst_mac_user->st_cap_info.bit_qos, &uc_ie_len);
    puc_asoc_rsp += uc_ie_len;

    /*���� Timeout Interval (Association Comeback time) IE*/
    ul_timeout = hmac_get_assoc_comeback_time(pst_mac_ap, pst_hmac_user);
    mac_set_timeout_interval_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len, en_tie_type, ul_timeout);
    puc_asoc_rsp += uc_ie_len;

    if (OAL_TRUE == pst_mac_user->st_ht_hdl.en_ht_capable)
    {
        /* ���� HT-Capabilities Information IE*/
        mac_set_ht_capabilities_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
#ifdef _PRE_WLAN_FEATURE_TXBF
        if ((OAL_TRUE == pst_mac_user->st_cap_info.bit_11ntxbf)
        && (OAL_TRUE == pst_mac_ap->st_cap_flag.bit_11ntxbf)
        && (0 != uc_ie_len))
        {
            puc_asoc_rsp += MAC_11N_TXBF_CAP_OFFSET;

            pst_txbf_cap  = (mac_txbf_cap_stru *)puc_asoc_rsp;
            pst_txbf_cap->bit_rx_stagg_sounding = OAL_TRUE;
            pst_txbf_cap->bit_explicit_compr_bf_fdbk = 1;
            pst_txbf_cap->bit_compr_steering_num_bf_antssup = 1;
            puc_asoc_rsp -= MAC_11N_TXBF_CAP_OFFSET;
        }
#endif
        puc_asoc_rsp += uc_ie_len;

        /* ���� HT-Operation Information IE */
        mac_set_ht_opern_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
        puc_asoc_rsp += uc_ie_len;

        /* ���� Overlapping BSS Scan Parameters Information IE */
        mac_set_obss_scan_params((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
        puc_asoc_rsp += uc_ie_len;

        /* ���� Extended Capabilities Information IE */
        mac_set_ext_capabilities_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
        puc_asoc_rsp += uc_ie_len;
    }

    if (OAL_TRUE == pst_mac_user->st_vht_hdl.en_vht_capable)
    {

        /* ���� VHT Capabilities IE */
        mac_set_vht_capabilities_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
        puc_asoc_rsp += uc_ie_len;

        /* ���� VHT Opern IE */
        mac_set_vht_opern_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
        puc_asoc_rsp += uc_ie_len;
    }

#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_set_11ntxbf_vendor_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
    puc_asoc_rsp += uc_ie_len;
#endif

    /* ���WPS��Ϣ */
    mac_add_app_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &us_app_ie_len, OAL_APP_ASSOC_RSP_IE);
    puc_asoc_rsp += us_app_ie_len;

#ifdef _PRE_WLAN_FEATURE_HISTREAM
    mac_set_histream_ie((oal_void *)pst_mac_ap, puc_asoc_rsp, &uc_ie_len);
    puc_asoc_rsp += uc_ie_len;
#endif //_PRE_WLAN_FEATURE_HISTREAM

    us_asoc_rsp_len = (oal_uint32)(puc_asoc_rsp - puc_asoc_rsp_original);

    return us_asoc_rsp_len;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_is_challenge_txt_equal
 ��������  : �ж�����challenge txt�Ƿ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��29��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  hmac_mgmt_is_challenge_txt_equal(oal_uint8 *puc_data, oal_uint8 *puc_chtxt)
{

    oal_uint8  *puc_ch_text     = 0;
    oal_uint16  us_idx          = 0;
    oal_uint8   uc_ch_text_len  = 0;

    if (OAL_PTR_NULL == puc_data || OAL_PTR_NULL == puc_chtxt)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY,"{hmac_mgmt_is_challenge_txt_equal::puc_data[0x%x] or puc_chtxt[0x%x] is NULL.}", puc_data, puc_chtxt);
        return OAL_FALSE;
    }

    /* Challenge Text Element                  */
    /* --------------------------------------- */
    /* |Element ID | Length | Challenge Text | */
    /* --------------------------------------- */
    /* | 1         |1       |1 - 253         | */
    /* --------------------------------------- */
    uc_ch_text_len = puc_data[1];
    puc_ch_text     = puc_data + 2;

    for(us_idx = 0; us_idx < uc_ch_text_len; us_idx++)
    {
        /* Return false on mismatch */
        if(puc_ch_text[us_idx] != puc_chtxt[us_idx])
        {
            return OAL_FALSE;
        }
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_encap_auth_rsp_get_user_idx
 ��������  : ��ȡuser idx,����û������ڣ���resend��λ�Ļ�����sta����ap
 �������  : 1.vapָ��
             2.sta��mac��ַ
             3.�Ƿ�Ϊseq1��־λ.���Ϊ�棬��ʾ����û�������,��Ҫ��sta����ap
 �������  : 1. puc_auth_resend �û����ڵ�������յ�seq1,seq1�ж�Ϊ�ش�֡��
                ��λ�˱�־
             2. pus_user_index ���ػ�ȡ����user idx

 �� �� ֵ  :��ȡ��������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��10��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum  hmac_encap_auth_rsp_get_user_idx(mac_vap_stru *pst_mac_vap,
                                                oal_uint8   *puc_mac_addr,
                                                oal_uint8   uc_is_seq1,
                                                oal_uint8   *puc_auth_resend,
                                                oal_uint16  *pus_user_index)
{
    oal_uint32                      ul_ret;
    hmac_vap_stru                  *pst_hmac_vap;
    hmac_user_stru                 *pst_hmac_user;
    hmac_user_stru                 *pst_user;
    mac_vap_stru                   *pst_vap;
    oal_uint16                      us_user_idx;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY,"{hmac_encap_auth_rsp_get_user_idx::mac_res_get_hmac_vap failed!}");
        return OAL_FAIL;
    }

    *puc_auth_resend = OAL_FALSE;
    ul_ret = mac_vap_find_user_by_macaddr(&(pst_hmac_vap->st_vap_base_info), puc_mac_addr, pus_user_index);
    /* �ҵ��û� */
    if(OAL_SUCC == ul_ret)
    {
        /* ��ȡhmac�û���״̬���������0��˵�����ظ�֡ */
        pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(*pus_user_index);
        if (OAL_PTR_NULL == pst_hmac_user)
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_encap_auth_rsp_get_user_idx::mac_res_get_hmac_user return null}");
            return OAL_FAIL;
        }
        /* en_user_asoc_stateΪö�ٱ�����ȡֵΪ1~4����ʼ��ΪMAC_USER_STATE_BUTT��
         * Ӧ��ʹ��!=MAC_USER_STATE_BUTT��Ϊ�жϣ�����ᵼ��WEP share���ܹ�����������
         */
        if (pst_hmac_user->st_user_base_info.en_user_asoc_state != MAC_USER_STATE_BUTT)
        {
            *puc_auth_resend = OAL_TRUE;
        }

        if (pst_hmac_user->st_user_base_info.en_user_asoc_state == MAC_USER_STATE_ASSOC)
        {
            oal_net_device_stru  *pst_net_device;

            pst_net_device = hmac_vap_get_net_device(pst_mac_vap->uc_vap_id);
            if (OAL_PTR_NULL != pst_net_device)
            {
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
                oal_kobject_uevent_env_sta_leave(pst_net_device, puc_mac_addr);
#endif
#endif
            }
        }

        return OAL_SUCC;
    }

    /* ����ͬһdevice�µ�����VAP���ҵ����û���ɾ��֮��������ҵ��ͨ����DBAC�����䳣�� */
    if (OAL_SUCC == mac_device_find_user_by_macaddr(&pst_hmac_vap->st_vap_base_info, puc_mac_addr, &us_user_idx))
    {
        pst_user = mac_res_get_hmac_user(us_user_idx);
        if (OAL_PTR_NULL != pst_user)
        {
            pst_vap  = mac_res_get_mac_vap(pst_user->st_user_base_info.uc_vap_id);
            if (OAL_PTR_NULL != pst_vap)
            {
                hmac_user_del(pst_vap, pst_user);
            }
        }
    }

    /* ���յ���һ����֤֡ʱ�û��Ѵ��� */
    if(!uc_is_seq1)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_encap_auth_rsp_get_user_idx::user should have been added at seq1!}");
        return OAL_FAIL;
    }

    ul_ret = hmac_user_add(pst_mac_vap, puc_mac_addr, pus_user_index);
    if (OAL_SUCC != ul_ret)
    {
        if(OAL_ERR_CODE_CONFIG_EXCEED_SPEC == ul_ret)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY,"{hmac_encap_auth_rsp_get_user_idx::mac_vap_add_assoc_user fail, users exceed config spec.}");
            return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
        }
        else
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY,"{hmac_encap_auth_rsp_get_user_idx::mac_vap_add_assoc_user fail,user_idx[%d]}",*pus_user_index);
            return OAL_FAIL;
        }
    }
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_encap_auth_rsp_seq1
 ��������  : ����seq1��auth req
 �������  : 1.auth_rsp_param ����auth rsp����Ĳ���

 �������  : 1.puc_code ������
             2.pst_usr_ass_stat auth�������֮������Ӧ��user״̬

 �� �� ֵ  :��ȡ��������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��10��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
hmac_ap_auth_process_code_enum_uint8   hmac_encap_auth_rsp_seq1(
                                                        mac_vap_stru *pst_mac_vap,
                                                        hmac_auth_rsp_param_stru *pst_auth_rsp_param,
                                                        oal_uint8 *puc_code,
                                                        mac_user_asoc_state_enum_uint8 *pst_usr_ass_stat)
{
    *puc_code = MAC_SUCCESSFUL_STATUSCODE;
    *pst_usr_ass_stat = MAC_USER_STATE_BUTT;
    /* ��������ش� */
    if(OAL_TRUE != pst_auth_rsp_param->uc_auth_resend)
    {
        if(pst_auth_rsp_param->us_auth_type == WLAN_WITP_AUTH_OPEN_SYSTEM)
        {
            *pst_usr_ass_stat = MAC_USER_STATE_AUTH_COMPLETE;

            return HMAC_AP_AUTH_SEQ1_OPEN_ANY;
        }

        if(OAL_TRUE == pst_auth_rsp_param->en_is_wep_allowed)
        {
            *pst_usr_ass_stat = MAC_USER_STATE_AUTH_KEY_SEQ1;
            /* �˴����غ���Ҫwep����� */
            return HMAC_AP_AUTH_SEQ1_WEP_NOT_RESEND;
        }

        /* ��֧���㷨 */
        *puc_code = MAC_UNSUPT_ALG;
        return HMAC_AP_AUTH_BUTT;
    }

    /* ����û�״̬ */
    if((pst_auth_rsp_param->en_user_asoc_state == MAC_USER_STATE_ASSOC) && (pst_auth_rsp_param->us_auth_type == WLAN_WITP_AUTH_OPEN_SYSTEM))
    {
        /*DTS2015122909216,������PMF����ʱ,�յ��ѹ����û���Auth֡,���ı����״̬ */
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC)
        {
            *pst_usr_ass_stat = MAC_USER_STATE_ASSOC;
        }
        else
        {
            *pst_usr_ass_stat = MAC_USER_STATE_AUTH_COMPLETE;
        }

        return HMAC_AP_AUTH_DUMMY;
    }

    if(pst_auth_rsp_param->us_auth_type == WLAN_WITP_AUTH_OPEN_SYSTEM)
    {
        *pst_usr_ass_stat = MAC_USER_STATE_AUTH_COMPLETE;

        return HMAC_AP_AUTH_SEQ1_OPEN_ANY;
    }

    if(OAL_TRUE == pst_auth_rsp_param->en_is_wep_allowed)
    {
        /* seqΪ1 ����֤֡�ش� */
        *pst_usr_ass_stat = MAC_USER_STATE_AUTH_COMPLETE;
        return HMAC_AP_AUTH_SEQ1_WEP_RESEND;
    }
    /* ��֧���㷨 */
    *puc_code = MAC_UNSUPT_ALG;
    return HMAC_AP_AUTH_BUTT;

}
/*****************************************************************************
 �� �� ��  : hmac_encap_auth_rsp_seq3
 ��������  : ����seq3��auth req
 �������  : 1.auth_rsp_param ����auth rsp����Ĳ���

 �������  : 1.puc_code ������
             2.pst_usr_ass_stat auth�������֮������Ӧ��user״̬

 �� �� ֵ  :��ȡ��������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��10��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
hmac_ap_auth_process_code_enum_uint8   hmac_encap_auth_rsp_seq3(
                                                mac_vap_stru *pst_mac_vap,
                                                hmac_auth_rsp_param_stru *pst_auth_rsp_param,
                                                oal_uint8 *puc_code,
                                                mac_user_asoc_state_enum_uint8 *pst_usr_ass_stat)
{


    /* ��������ڣ����ش��� */
    if (OAL_FALSE == pst_auth_rsp_param->uc_auth_resend)
    {
        *pst_usr_ass_stat = MAC_USER_STATE_BUTT;
        *puc_code = MAC_SUCCESSFUL_STATUSCODE;
        return HMAC_AP_AUTH_BUTT;
    }
    /* ����û�״̬ */
    if((pst_auth_rsp_param->en_user_asoc_state == MAC_USER_STATE_ASSOC) && (pst_auth_rsp_param->us_auth_type == WLAN_WITP_AUTH_OPEN_SYSTEM))
    {
        /*DTS2015122909216,������PMF����ʱ,�յ��ѹ����û���Auth֡,���ı����״ ̬ */
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC)
        {
            *pst_usr_ass_stat = MAC_USER_STATE_ASSOC;
        }
        else
        {
            *pst_usr_ass_stat = MAC_USER_STATE_AUTH_COMPLETE;
        }

        *puc_code = MAC_SUCCESSFUL_STATUSCODE;
        return HMAC_AP_AUTH_DUMMY;
    }

    if(pst_auth_rsp_param->us_auth_type == WLAN_WITP_AUTH_OPEN_SYSTEM)
    {
        *pst_usr_ass_stat = MAC_USER_STATE_AUTH_COMPLETE;
        *puc_code = MAC_SUCCESSFUL_STATUSCODE;
        return HMAC_AP_AUTH_SEQ3_OPEN_ANY;
    }

    if(pst_auth_rsp_param->en_user_asoc_state == MAC_USER_STATE_AUTH_KEY_SEQ1)
    {
        *pst_usr_ass_stat = MAC_USER_STATE_AUTH_COMPLETE;
        *puc_code = MAC_SUCCESSFUL_STATUSCODE;
        return HMAC_AP_AUTH_SEQ3_WEP_COMPLETE;
    }

    if(pst_auth_rsp_param->en_user_asoc_state == MAC_USER_STATE_AUTH_COMPLETE)
    {
        *pst_usr_ass_stat = MAC_USER_STATE_AUTH_COMPLETE;
        *puc_code = MAC_SUCCESSFUL_STATUSCODE;
        return HMAC_AP_AUTH_SEQ3_WEP_COMPLETE;
    }

    if(pst_auth_rsp_param->en_user_asoc_state == MAC_USER_STATE_ASSOC)
    {
        *pst_usr_ass_stat = MAC_USER_STATE_AUTH_KEY_SEQ1;
        *puc_code = MAC_SUCCESSFUL_STATUSCODE;
        return HMAC_AP_AUTH_SEQ3_WEP_ASSOC;
    }

    /* ��֧���㷨 */
    *pst_usr_ass_stat = MAC_USER_STATE_BUTT;
    *puc_code = MAC_UNSUPT_ALG;
    return HMAC_AP_AUTH_BUTT;
}

/*****************************************************************************
 �� �� ��  : hmac_encap_auth_rsp_seq3
 ��������  : ����seq3��auth req
 �������  : 1.auth_rsp_param ����auth rsp����Ĳ�������

 �������  : 1.puc_code ������
             2.pst_usr_ass_stat auth�������֮������Ӧ��user״̬

 �� �� ֵ  :��ȡ��������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��10��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
hmac_auth_rsp_fun hmac_encap_auth_rsp_get_func(oal_uint16 us_auth_seq)
{
    hmac_auth_rsp_fun        st_auth_rsp_fun;
    switch(us_auth_seq)
    {
        case WLAN_AUTH_TRASACTION_NUM_ONE:
            st_auth_rsp_fun = hmac_encap_auth_rsp_seq1;
            /* st_auth_chk.hmac_ap_get_user_idx = hmac_ap_get_user_idx_seq1; */
            break;
        case WLAN_AUTH_TRASACTION_NUM_THREE:
            st_auth_rsp_fun = hmac_encap_auth_rsp_seq3;
            break;
        default:
            st_auth_rsp_fun = OAL_PTR_NULL;
            break;
    }
    return st_auth_rsp_fun;
}

/*****************************************************************************
 �� �� ��  : hmac_encap_auth_rsp_support
 ��������  : �ж���֤�����Ƿ�֧��
 �������  : 1.pst_hmac_vap vapָ��
             2. us_auth_type ��֤����
 �������  :

 �� �� ֵ  :OAL_SUCC-֧�֣�����-��֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��10��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_encap_auth_rsp_support(hmac_vap_stru *pst_hmac_vap, oal_uint16 us_auth_type)
{

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

     /* �����֤�����Ƿ�֧�� ��֧�ֵĻ�״̬λ�ó�UNSUPT_ALG */
    if ((pst_hmac_vap->en_auth_mode) != us_auth_type &&
            (WLAN_WITP_ALG_AUTH_BUTT != pst_hmac_vap->en_auth_mode))
    {
        return OAL_ERR_CODE_CONFIG_UNSUPPORT;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_tid_clear
 ��������  : ɾ��hmac tid��ص���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��13��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_tid_clear(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user)
{
    mac_device_stru   *pst_device;
    oal_uint8          uc_loop;
    hmac_amsdu_stru   *pst_amsdu;
    oal_netbuf_stru   *pst_amsdu_net_buf;
    hmac_tid_stru     *pst_tid;

#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    hmac_vap_stru      *pst_hmac_vap;
#endif

    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_AUTH, "{hmac_tid_clear::pst_hmac_user is null.}");
        return;
    }
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_tid_clear::pst_hmac_vap null.}");
        return;
    }
#endif
    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_BA, "{hmac_tid_clear::pst_device null.}");
        return;
    }



    for (uc_loop = 0; uc_loop < WLAN_WME_MAX_TID_NUM; uc_loop++)
    {
        pst_amsdu =  &(pst_hmac_user->ast_hmac_amsdu[uc_loop]);

        /* tid��, �����ж� */
        oal_spin_lock_bh(&pst_amsdu->st_amsdu_lock);

        if (pst_amsdu->st_amsdu_timer.en_is_registerd == OAL_TRUE)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_amsdu->st_amsdu_timer));
        }

        /* ��վۺ϶��� */
        if (0 != pst_amsdu->uc_msdu_num)
        {
            while (OAL_TRUE != oal_netbuf_list_empty(&pst_amsdu->st_msdu_head))
            {
                pst_amsdu_net_buf = oal_netbuf_delist(&(pst_amsdu->st_msdu_head));

                oal_netbuf_free(pst_amsdu_net_buf);
            }
            pst_amsdu->uc_msdu_num = 0;
        }

        /* tid����, ʹ�����ж� */
        oal_spin_unlock_bh(&pst_amsdu->st_amsdu_lock);

        pst_tid = &(pst_hmac_user->ast_tid_info[uc_loop]);

        if (pst_tid->st_ba_tx_info.st_addba_timer.en_is_registerd == OAL_TRUE)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_tid->st_ba_tx_info.st_addba_timer));
        }

        pst_tid->uc_tid_no        = (oal_uint8)uc_loop;
        pst_tid->us_hmac_user_idx = pst_hmac_user->st_user_base_info.us_assoc_id;

        /* ������շ���Ự��� */
        if (OAL_PTR_NULL != pst_tid->pst_ba_rx_info)
        {
            hmac_ba_reset_rx_handle(pst_device, &pst_tid->pst_ba_rx_info, uc_loop, OAL_TRUE);
        }

        if (DMAC_BA_INIT != pst_tid->st_ba_tx_info.en_ba_status)
        {
            /* ����TX BA�Ự�����Ҫ-- */
#ifdef _PRE_WLAN_FEATURE_AMPDU_VAP
            hmac_tx_ba_session_decr(pst_hmac_vap, uc_loop);
#else
            hmac_tx_ba_session_decr(pst_device, uc_loop);
#endif
        }

        /* ��ʼ��ba tx������� */
        pst_tid->st_ba_tx_info.en_ba_status         = DMAC_BA_INIT;
        pst_tid->st_ba_tx_info.uc_addba_attemps     = 0;
        pst_tid->st_ba_tx_info.uc_dialog_token      = 0;
        pst_tid->st_ba_tx_info.en_ba_switch         = OAL_TRUE;
        pst_hmac_user->auc_ba_flag[uc_loop] = 0;
    }
}

/*****************************************************************************
 �� �� ��  : hmac_encap_auth_rsp_ap
 ��������  : ��װauth rsp֡
 �������  : 1. vapָ��
             2. puc_auth_req auth_req
             3. challenge txt
 �������  : 1. pst_auth_rsp auth_rsp����

 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��28��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

2.��    ��   : 2014��1��10��
    ��    ��   : z00260280
    �޸�����   : �ع�

*****************************************************************************/
oal_uint16  hmac_encap_auth_rsp(mac_vap_stru *pst_mac_vap, oal_netbuf_stru *pst_auth_rsp, oal_netbuf_stru *pst_auth_req, oal_uint8 *puc_chtxt)
{
    oal_uint16       us_auth_rsp_len        = 0;
    hmac_user_stru  *pst_hmac_user_sta      = OAL_PTR_NULL;
    oal_uint8       *puc_frame              = OAL_PTR_NULL;
    oal_uint16       us_index               = 0;
    oal_uint16       us_auth_type           = 0;
    oal_uint8        uc_is_seq1;
    oal_uint16       us_auth_seq            = 0;
    oal_uint8        auc_addr2[6]           = {0};
    hmac_vap_stru   *pst_hmac_vap;
    oal_uint16       us_user_index          = 0xffff;
    oal_uint32       ul_ret                 = 0;

#ifdef _PRE_DEBUG_MODE_USER_TRACK
    mac_user_asoc_state_enum_uint8          en_old_asoc_state;
#endif
    /* ��֤���� */
    hmac_ap_auth_process_code_enum_uint8       ul_auth_proc_rst;

    oal_uint8       *puc_data;
    mac_tx_ctl_stru *pst_tx_ctl;
    hmac_auth_rsp_handle_stru              st_auth_rsp_handle;
    oal_uint32                      ul_alg_suppt = 0;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == pst_auth_rsp || OAL_PTR_NULL == pst_auth_req)
#else
    if (OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == pst_auth_rsp || OAL_PTR_NULL == pst_auth_req || OAL_PTR_NULL == puc_chtxt)
#endif
    {
        OAM_ERROR_LOG4(0, OAM_SF_AUTH,"{hmac_encap_auth_rsp::pst_mac_vap[0x%x], puc_data[0x%x], puc_auth_req[0x%x] and puc_chtxt[0x%x]}", pst_mac_vap, pst_auth_rsp, pst_auth_req, puc_chtxt);
        return us_auth_rsp_len;
    }

    puc_data    = (oal_uint8 *)OAL_NETBUF_HEADER(pst_auth_rsp);
    pst_tx_ctl  = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_auth_rsp);

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

    /* ���ú���ͷ��frame control�ֶ� */
    mac_hdr_set_frame_control(puc_data, WLAN_FC0_SUBTYPE_AUTH);

    /* ��ȡSTA�ĵ�ַ */
    mac_get_address2(oal_netbuf_header(pst_auth_req), auc_addr2);

    /* ��DA����ΪSTA�ĵ�ַ */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address1, auc_addr2);

    /* ��SA����Ϊdot11MacAddress */
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address2, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
    oal_set_mac_addr(((mac_ieee80211_frame_stru *)puc_data)->auc_address3, pst_mac_vap->auc_bssid);

    /*************************************************************************/
    /*                Set the contents of the frame body                     */
    /*************************************************************************/

    /*************************************************************************/
    /*              Authentication Frame - Frame Body                        */
    /* --------------------------------------------------------------------- */
    /* |Auth Algo Number|Auth Trans Seq Number|Status Code| Challenge Text | */
    /* --------------------------------------------------------------------- */
    /* | 2              |2                    |2          | 3 - 256        | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    us_index = MAC_80211_FRAME_LEN;
    puc_frame = (oal_uint8 *)(puc_data + us_index);

    /* ������֤��Ӧ֡�ĳ��� */
    us_auth_rsp_len = MAC_80211_FRAME_LEN + MAC_AUTH_ALG_LEN + MAC_AUTH_TRANS_SEQ_NUM_LEN +
                      MAC_STATUS_CODE_LEN;

    /* ������֤���� */
    us_auth_type = mac_get_auth_algo_num(pst_auth_req);

    /* ����auth transaction number */
    us_auth_seq  = mac_get_auth_seq_num(oal_netbuf_header(pst_auth_req));
    if (us_auth_seq > HMAC_AP_AUTH_SEQ3_WEP_COMPLETE)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_AUTH,"{hmac_encap_auth_rsp::auth recieve invalid seq, auth seq [%d]}", us_auth_seq);
        return 0;
    }

    /* ������֤����IE */
    puc_frame[0] = (us_auth_type & 0x00FF);
    puc_frame[1] = (us_auth_type & 0xFF00) >> 8;

    /* ���յ���transaction number + 1���Ƹ��µ���֤��Ӧ֡ */
    puc_frame[2] = ((us_auth_seq + 1) & 0x00FF);
    puc_frame[3] = ((us_auth_seq + 1) & 0xFF00) >> 8;

    /* ״̬Ϊ��ʼ��Ϊ�ɹ� */
    puc_frame[4] = MAC_SUCCESSFUL_STATUSCODE;
    puc_frame[5] = 0;

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "{hmac_encap_auth_rsp::user mac:%02X:XX:XX:%02X:%02X:%02X}",
                                auc_addr2[0],auc_addr2[3],auc_addr2[4],auc_addr2[5]);

    /* DTS2015092402932,�ж϶Զ�mac��ַ�Ƿ�Ϊ��Ч������Ϊȫ0 */
    if(mac_addr_is_zero(auc_addr2))
    {
        OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "{hmac_encap_auth_rsp::user mac:%02X:XX:XX:%02X:%02X:%02X is all 0 and invaild!}",
                                auc_addr2[0],auc_addr2[3],auc_addr2[4],auc_addr2[5]);
        puc_frame[4] = MAC_UNSPEC_FAIL;
        pst_tx_ctl->us_tx_user_idx = 0xffff;
        pst_tx_ctl->us_mpdu_len    = us_auth_rsp_len;
        return us_auth_rsp_len;
    }

    /* ��ȡ�û�idx */
    uc_is_seq1 = (WLAN_AUTH_TRASACTION_NUM_ONE == us_auth_seq);
    ul_ret = hmac_encap_auth_rsp_get_user_idx(pst_mac_vap,
                                        auc_addr2,
                                        uc_is_seq1,
                                        &st_auth_rsp_handle.st_auth_rsp_param.uc_auth_resend,
                                        &us_user_index);
    if(OAL_SUCC != ul_ret)
    {
        if(OAL_ERR_CODE_CONFIG_EXCEED_SPEC == ul_ret)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH,"{hmac_encap_auth_rsp::hmac_ap_get_user_idx fail, users exceed config spec!}");
            puc_frame[4] = MAC_AP_FULL;
        }
        else
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH,"{hmac_encap_auth_rsp::hmac_ap_get_user_idx Err!}");
            puc_frame[4] = MAC_UNSPEC_FAIL;
        }
        pst_tx_ctl->us_tx_user_idx = 0xffff;
        pst_tx_ctl->us_mpdu_len    = us_auth_rsp_len;
        return us_auth_rsp_len;
    }

    /* ��ȡhmac userָ�� */
    pst_hmac_user_sta = mac_res_get_hmac_user(us_user_index);
    if (OAL_PTR_NULL == pst_hmac_user_sta)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH,"{hmac_encap_auth_rsp::pst_hmac_user_sta is NULL}");
        puc_frame[4] = MAC_UNSPEC_FAIL;
        pst_tx_ctl->us_tx_user_idx = 0xffff;
        pst_tx_ctl->us_mpdu_len    = us_auth_rsp_len;
        return us_auth_rsp_len;
    }


    /* ��ȡhmac vapָ�� */
    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_AUTH,
            "{hmac_encap_auth_rsp::pst_hmac_vap is NULL,and change user[idx==%d] state to BUTT!}",
            pst_hmac_user_sta->st_user_base_info.us_assoc_id);
        puc_frame[4] = MAC_UNSPEC_FAIL;
        pst_tx_ctl->us_tx_user_idx = 0xffff;
        pst_tx_ctl->us_mpdu_len    = us_auth_rsp_len;
    #ifdef _PRE_DEBUG_MODE_USER_TRACK
        mac_user_change_info_event(pst_hmac_user_sta->st_user_base_info.auc_user_mac_addr,
                                   pst_mac_vap->uc_vap_id,
                                   pst_hmac_user_sta->st_user_base_info.en_user_asoc_state,
                                   0, OAM_MODULE_ID_HMAC, OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
    #endif
        mac_user_set_asoc_state(&(pst_hmac_user_sta->st_user_base_info), MAC_USER_STATE_BUTT);
        return us_auth_rsp_len;
    }
    pst_tx_ctl->us_tx_user_idx = us_user_index;
    pst_tx_ctl->us_mpdu_len    = us_auth_rsp_len;

    /* �ж��㷨�Ƿ�֧�� */
    ul_alg_suppt = hmac_encap_auth_rsp_support(pst_hmac_vap, us_auth_type);
    if(OAL_SUCC != ul_alg_suppt)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_AUTH, "{hmac_encap_auth_rsp::auth type[%d] not support!}", us_auth_type);
        puc_frame[4] = MAC_UNSUPT_ALG;
    #ifdef _PRE_DEBUG_MODE_USER_TRACK
        mac_user_change_info_event(pst_hmac_user_sta->st_user_base_info.auc_user_mac_addr,
                                   pst_mac_vap->uc_vap_id,
                                   pst_hmac_user_sta->st_user_base_info.en_user_asoc_state,
                                   0, OAM_MODULE_ID_HMAC, OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
    #endif
        hmac_user_set_asoc_state(&(pst_hmac_vap->st_vap_base_info), &pst_hmac_user_sta->st_user_base_info, MAC_USER_STATE_BUTT);
        return us_auth_rsp_len;
    }

    /*  ��ʼ��������� */
    st_auth_rsp_handle.st_auth_rsp_param.en_is_wep_allowed = mac_is_wep_allowed(pst_mac_vap);
    st_auth_rsp_handle.st_auth_rsp_param.en_user_asoc_state = pst_hmac_user_sta->st_user_base_info.en_user_asoc_state;
    st_auth_rsp_handle.st_auth_rsp_param.us_auth_type = us_auth_type;
    st_auth_rsp_handle.st_auth_rsp_fun  = hmac_encap_auth_rsp_get_func(us_auth_seq);

    /*  ����seq1����seq3 */
    if(OAL_PTR_NULL != st_auth_rsp_handle.st_auth_rsp_fun)
    {
    #ifdef _PRE_DEBUG_MODE_USER_TRACK
        en_old_asoc_state = pst_hmac_user_sta->st_user_base_info.en_user_asoc_state;
    #endif
        ul_auth_proc_rst = st_auth_rsp_handle.st_auth_rsp_fun(pst_mac_vap,
                                                &st_auth_rsp_handle.st_auth_rsp_param,
                                                &puc_frame[4],
                                                &pst_hmac_user_sta->st_user_base_info.en_user_asoc_state);
    #ifdef _PRE_DEBUG_MODE_USER_TRACK
        mac_user_change_info_event(pst_hmac_user_sta->st_user_base_info.auc_user_mac_addr,
                                   pst_mac_vap->uc_vap_id,
                                   en_old_asoc_state,
                                   pst_hmac_user_sta->st_user_base_info.en_user_asoc_state,
                                   OAM_MODULE_ID_HMAC, OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
    #endif
        /* ��� HMAC��TID��Ϣ */
        hmac_tid_clear(pst_mac_vap, pst_hmac_user_sta);
    }
    else
    {
        ul_auth_proc_rst = HMAC_AP_AUTH_BUTT;
    #ifdef _PRE_DEBUG_MODE_USER_TRACK
        mac_user_change_info_event(pst_hmac_user_sta->st_user_base_info.auc_user_mac_addr,
                                   pst_mac_vap->uc_vap_id,
                                   pst_hmac_user_sta->st_user_base_info.en_user_asoc_state,
                                   0, OAM_MODULE_ID_HMAC, OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
    #endif
        mac_user_set_asoc_state(&pst_hmac_user_sta->st_user_base_info, MAC_USER_STATE_BUTT);
        puc_frame[4] = MAC_AUTH_SEQ_FAIL;
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_AUTH,"{hmac_encap_auth_rsp::ul_auth_proc_rst:%d}", ul_auth_proc_rst);

    /*  ���ݷ��ص�code���к������� */
    switch(ul_auth_proc_rst)
    {
        case HMAC_AP_AUTH_SEQ1_OPEN_ANY:
        {
            mac_user_init_key(&pst_hmac_user_sta->st_user_base_info);
            FRW_TIMER_CREATE_TIMER(&pst_hmac_user_sta->st_mgmt_timer,
                                   hmac_mgmt_timeout_ap,
                                   (oal_uint16)pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11AuthenticationResponseTimeOut,
                                   pst_hmac_user_sta,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_HMAC,
                                   pst_mac_vap->ul_core_id);
            break;
        }
        case HMAC_AP_AUTH_SEQ1_WEP_NOT_RESEND:
        {
            hmac_config_11i_add_wep_entry(pst_mac_vap, 6, pst_hmac_user_sta->st_user_base_info.auc_user_mac_addr);

            hmac_mgmt_encap_chtxt(puc_frame, puc_chtxt, &us_auth_rsp_len, pst_hmac_user_sta);
            /* Ϊ���û�����һ����ʱ������ʱ��֤ʧ�� */
            FRW_TIMER_CREATE_TIMER(&pst_hmac_user_sta->st_mgmt_timer,
                                   hmac_mgmt_timeout_ap,
                                   (oal_uint16)pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11AuthenticationResponseTimeOut,
                                   pst_hmac_user_sta,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_HMAC,
                                   pst_mac_vap->ul_core_id);
            pst_hmac_user_sta->st_user_base_info.st_key_info.en_cipher_type = mac_get_wep_type(pst_mac_vap, mac_get_wep_default_keyid(pst_mac_vap));
            break;
        }
        case HMAC_AP_AUTH_SEQ1_WEP_RESEND:
        {
            /* seqΪ1 ����֤֡�ش� */
            hmac_mgmt_encap_chtxt(puc_frame, puc_chtxt, &us_auth_rsp_len, pst_hmac_user_sta);

            /* ������ʱ��ʱ�� */
            frw_timer_restart_timer(&pst_hmac_user_sta->st_mgmt_timer,
                                    pst_hmac_user_sta->st_mgmt_timer.ul_timeout,
                                    OAL_FALSE);
            break;
        }
        case HMAC_AP_AUTH_SEQ3_OPEN_ANY:
        {
            mac_user_init_key(&pst_hmac_user_sta->st_user_base_info);
            break;
        }
        case HMAC_AP_AUTH_SEQ3_WEP_COMPLETE:
        {
            puc_chtxt   = mac_get_auth_ch_text(oal_netbuf_header(pst_auth_req));
            if(hmac_mgmt_is_challenge_txt_equal(puc_chtxt,
                                    pst_hmac_user_sta->auc_ch_text) == OAL_TRUE)
            {
            #ifdef _PRE_DEBUG_MODE_USER_TRACK
                mac_user_change_info_event(pst_hmac_user_sta->st_user_base_info.auc_user_mac_addr,
                                           pst_mac_vap->uc_vap_id,
                                           pst_hmac_user_sta->st_user_base_info.en_user_asoc_state,
                                           MAC_USER_STATE_AUTH_COMPLETE, OAM_MODULE_ID_HMAC,
                                           OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
            #endif
                mac_user_set_asoc_state(&pst_hmac_user_sta->st_user_base_info, MAC_USER_STATE_AUTH_COMPLETE);

                /* cancel timer for auth */
                FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_user_sta->st_mgmt_timer);
            }
            else
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_AUTH,"{hmac_encap_auth_rsp::challenage txt not equal.}");
                puc_frame[4] = MAC_CHLNG_FAIL;
            #ifdef _PRE_DEBUG_MODE_USER_TRACK
                mac_user_change_info_event(pst_hmac_user_sta->st_user_base_info.auc_user_mac_addr,
                                           pst_mac_vap->uc_vap_id,
                                           pst_hmac_user_sta->st_user_base_info.en_user_asoc_state,
                                           0, OAM_MODULE_ID_HMAC, OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
            #endif
                mac_user_set_asoc_state(&pst_hmac_user_sta->st_user_base_info, MAC_USER_STATE_BUTT);
            }
            break;
        }
        case HMAC_AP_AUTH_SEQ3_WEP_ASSOC:
        {
            hmac_mgmt_encap_chtxt(puc_frame, puc_chtxt, &us_auth_rsp_len, pst_hmac_user_sta);

            /* ������ʱ��ʱ�� */
            FRW_TIMER_CREATE_TIMER(&pst_hmac_user_sta->st_mgmt_timer,
                                   hmac_mgmt_timeout_ap,
                                   (oal_uint16)pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.ul_dot11AuthenticationResponseTimeOut,
                                   pst_hmac_user_sta,
                                   OAL_FALSE,
                                   OAM_MODULE_ID_HMAC,
                                   pst_mac_vap->ul_core_id);
            break;
        }
        case HMAC_AP_AUTH_DUMMY:
        {
            break;
        }
        case HMAC_AP_AUTH_BUTT:
        default:
        {
            mac_user_init_key(&pst_hmac_user_sta->st_user_base_info);
        #ifdef _PRE_DEBUG_MODE_USER_TRACK
            mac_user_change_info_event(pst_hmac_user_sta->st_user_base_info.auc_user_mac_addr,
                                       pst_mac_vap->uc_vap_id,
                                       pst_hmac_user_sta->st_user_base_info.en_user_asoc_state,
                                       0, OAM_MODULE_ID_HMAC, OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
        #endif
            pst_hmac_user_sta->st_user_base_info.en_user_asoc_state = MAC_USER_STATE_BUTT;
            break;
        }

    }

    /* dmac offload�ܹ��£�ͬ��user����״̬��Ϣ��dmac */
    ul_ret = hmac_config_user_asoc_state_syn(&(pst_hmac_vap->st_vap_base_info), &pst_hmac_user_sta->st_user_base_info);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                       "{hmac_ap_rx_auth_req::hmac_config_user_asoc_state_syn failed[%d].}", ul_ret);
    }

    return us_auth_rsp_len;

}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

