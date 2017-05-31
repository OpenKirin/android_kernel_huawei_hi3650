/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_mgmt_ap.c
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2013��6��18��
  ����޸�   :
  ��������   : AP������洦��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��18��
    ��    ��   : zhangheng
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
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "hmac_mgmt_ap.h"
#include "hmac_encap_frame.h"
#include "hmac_encap_frame_ap.h"
#include "hmac_mgmt_bss_comm.h"
#include "mac_frame.h"
#include "hmac_rx_data.h"
#include "hmac_uapsd.h"
#include "hmac_tx_amsdu.h"
#include "mac_ie.h"
#include "mac_user.h"
#include "hmac_user.h"
#include "hmac_11i.h"
#include "hmac_protection.h"
#include "hmac_chan_mgmt.h"
#include "hmac_smps.h"
#include "hmac_fsm.h"
#include "hmac_ext_if.h"
#include "hmac_config.h"
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
#include "hmac_custom_security.h"
#endif
#include "hmac_dfs.h"
#include "hmac_p2p.h"
#include "hmac_blockack.h"
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#include "hmac_ext_if.h"
#endif
#ifdef _PRE_WLAN_FEATURE_HILINK
#include "hmac_fbt_main.h"
#endif
#ifdef _PRE_WLAN_FEATURE_WMMAC
#include "hmac_wmmac.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_MGMT_AP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ap_up_update_sta_sup_rates(
                oal_uint8                      *puc_payload,
                hmac_user_stru                 *pst_hmac_user,
                mac_status_code_enum_uint16    *pen_status_code,
                oal_uint32                      ul_msg_len,
                oal_uint16                      us_offset,
                oal_uint8                      *puc_num_rates,
                oal_uint16                     *pus_msg_idx);
OAL_STATIC oal_uint32 hmac_ap_prepare_assoc_req(hmac_user_stru *pst_hmac_user, oal_uint8 *puc_payload, oal_uint32 ul_payload_len, oal_uint8 uc_mgmt_frm_type);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
/*****************************************************************************
 �� �� ��  : hmac_set_pmf_cap
 ��������  : ����ap sta���˵�pmf����������������pmfʹ��״̬
 �������  : pst_mac_vap
             pst_mac_user
             puc_rsn_ie   :�洢user rsn������ָ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��20��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_set_pmf_cap(mac_user_stru  *pst_mac_user, mac_vap_stru  *pst_mac_vap, const oal_uint8  *puc_rsn_ie)
{
    oal_uint16                          us_rsn_capability;
    oal_bool_enum_uint8                 en_ap_mfpc;
    oal_bool_enum_uint8                 en_ap_dot11RSNAActivated;
    oal_bool_enum_uint8                 en_sta_mfpc;

    en_ap_dot11RSNAActivated = pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated;
    us_rsn_capability        = mac_get_rsn_capability(puc_rsn_ie);
    en_ap_mfpc  = pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC;
    en_sta_mfpc = (us_rsn_capability & BIT7) ? OAL_TRUE : OAL_FALSE;

    if ((OAL_FALSE == en_ap_mfpc) || (OAL_FALSE == en_sta_mfpc) || (OAL_FALSE == en_ap_dot11RSNAActivated))
    {
        mac_user_set_pmf_active(pst_mac_user, OAL_FALSE);
        return;
    }
    else
    {
        mac_user_set_pmf_active(pst_mac_user, OAL_TRUE);
        return;
    }

}
#endif
/*****************************************************************************
 �� �� ��  : hmac_handle_disconnect_rsp_ap
 ��������  : AP(����)�ϱ�ȥ����ĳ��STA
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��9��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_handle_disconnect_rsp_ap(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user)

{
    mac_device_stru     *pst_mac_device;
    frw_event_mem_stru  *pst_event_mem;
    frw_event_stru      *pst_event;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_handle_disconnect_rsp_ap::pst_mac_device null.}");
        return ;
    }

    /* ��ɨ������¼���WAL */
    pst_event_mem = FRW_EVENT_ALLOC(WLAN_MAC_ADDR_LEN);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_handle_disconnect_rsp_ap::pst_event_mem null.}");
        return ;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_STA_DISCONNECT_AP,
                       WLAN_MAC_ADDR_LEN,
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    /* ȥ������STA mac��ַ */
    oal_memcopy(frw_get_event_payload(pst_event_mem), (oal_uint8 *)pst_hmac_user->st_user_base_info.auc_user_mac_addr, WLAN_MAC_ADDR_LEN);

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

}



/*****************************************************************************
 �� �� ��  : hmac_handle_connect_rsp_ap
 ��������  : AP(����)�ϱ��¹�����ĳ��STA
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��9��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_handle_connect_rsp_ap(hmac_vap_stru *pst_hmac_vap, hmac_user_stru *pst_hmac_user)
{
    mac_device_stru     *pst_mac_device;
    frw_event_mem_stru  *pst_event_mem;
    frw_event_stru      *pst_event;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    hmac_asoc_user_req_ie_stru *pst_asoc_user_req_info;
#endif

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_handle_connect_rsp_ap::pst_mac_device null.}");
        return;
    }

    /* �׹���һ���µ�sta����¼���WAL */
    pst_event_mem = FRW_EVENT_ALLOC(WLAN_MAC_ADDR_LEN);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_handle_connect_rsp_ap::pst_event_mem null.}");
        return;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_STA_CONNECT_AP,
                       WLAN_MAC_ADDR_LEN,
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    pst_asoc_user_req_info = (hmac_asoc_user_req_ie_stru *)(pst_event->auc_event_data);

    /* �ϱ��ں˵Ĺ���sta���͵Ĺ�������֡ie��Ϣ */
    pst_asoc_user_req_info->puc_assoc_req_ie_buff = pst_hmac_user->puc_assoc_req_ie_buff;
    pst_asoc_user_req_info->ul_assoc_req_ie_len   = pst_hmac_user->ul_assoc_req_ie_len;

    /* ������STA mac��ַ */
    oal_memcopy((oal_uint8 *)pst_asoc_user_req_info->auc_user_mac_addr, pst_hmac_user->st_user_base_info.auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
#else
    /* ȥ������STA mac��ַ */
    oal_memcopy((oal_uint8 *)pst_event->auc_event_data, pst_hmac_user->st_user_base_info.auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
#endif

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

}


/*****************************************************************************
 �� �� ��  : hmac_mgmt_update_auth_mib
 ��������  : ������֤mib ��ӡ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��4��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_mgmt_update_auth_mib(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_auth_rsp)
{
    oal_uint16  us_status = 0;
    oal_uint8   auc_addr1[6] = {0};
#ifdef _PRE_DEBUG_MODE
    oal_uint8   uc_auth_type    = 0;
    oal_uint8   uc_auth_seq_num = 0;
#endif
    oal_uint8   *puc_mac_header = oal_netbuf_header(pst_auth_rsp);

    us_status = mac_get_auth_status(puc_mac_header);

    mac_get_address1(puc_mac_header, auc_addr1);

    if(us_status != MAC_SUCCESSFUL_STATUSCODE)
    {
        mac_mib_set_AuthenticateFailStatus(&pst_hmac_vap->st_vap_base_info, us_status);
        mac_mib_set_AuthenticateFailStation(&pst_hmac_vap->st_vap_base_info, auc_addr1);

        /* DEBUG */
        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                      "{hmac_mgmt_update_auth_mib::Authentication of STA Failed.Status Code=%d.}", us_status);
    }
    else
    {
#ifdef _PRE_DEBUG_MODE
        /* DEBUG */
        uc_auth_type    = (oal_uint8)mac_get_auth_algo_num(pst_auth_rsp);
        uc_auth_seq_num = (oal_uint8)mac_get_auth_seq_num(puc_mac_header);

        if(((uc_auth_type == WLAN_WITP_AUTH_OPEN_SYSTEM) && (uc_auth_seq_num == 2)) ||
           ((uc_auth_type == WLAN_WITP_AUTH_SHARED_KEY) && (uc_auth_seq_num == 4)))
        {
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH,
                         "{hmac_mgmt_update_auth_mib::Successfully Authenticated STA.}");
        }
#endif /* DEBUG_MODE */
    }

}
/*****************************************************************************
 �� �� ��  : hmac_ap_rx_auth_req
 ��������  : ������֤����֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ap_rx_auth_req(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_auth_req, dmac_wlan_crx_event_stru   *pst_mgmt_rx_event)
{
    oal_netbuf_stru  *pst_auth_rsp      = OAL_PTR_NULL;
    oal_uint16        us_auth_rsp_len   = 0;
    oal_uint8        *puc_chtxt         = OAL_PTR_NULL;
    oal_uint32        ul_ret;
    mac_tx_ctl_stru  *pst_tx_ctl;

    if (OAL_PTR_NULL == pst_hmac_vap || OAL_PTR_NULL == pst_auth_req || OAL_PTR_NULL == pst_mgmt_rx_event)
    {
        OAM_ERROR_LOG3(0, OAM_SF_AUTH, "{hmac_ap_rx_auth_req::param null, %d %d %d.}", pst_hmac_vap, pst_auth_req, pst_mgmt_rx_event);
        return;
    }
    puc_chtxt         = pst_mgmt_rx_event->puc_chtxt;

    /* AP���յ�STA��������֤����֡����Ӧ����֤��Ӧ֡ */
    pst_auth_rsp = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);

    if(OAL_PTR_NULL == pst_auth_rsp)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_ap_rx_auth_req::pst_auth_rsp null.}");
        return;
    }

    OAL_MEM_NETBUF_TRACE(pst_auth_rsp, OAL_TRUE);

    OAL_MEMZERO(oal_netbuf_cb(pst_auth_rsp), OAL_NETBUF_CB_SIZE());

    us_auth_rsp_len = hmac_encap_auth_rsp(&pst_hmac_vap->st_vap_base_info,
                                          pst_auth_rsp,
                                          pst_auth_req,
                                          puc_chtxt);
    if (0 == us_auth_rsp_len)
    {
        oal_netbuf_free(pst_auth_rsp);
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_ap_rx_auth_req::us_auth_rsp_len is 0.}");
        return;
    }

    oal_netbuf_put(pst_auth_rsp, us_auth_rsp_len);

    hmac_mgmt_update_auth_mib(pst_hmac_vap, pst_auth_rsp);

    /* ������֤��Ӧ֮֡ǰ�����û��Ľ���״̬��λ */
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_auth_rsp);
    if (OAL_PTR_NULL != mac_res_get_hmac_user(pst_tx_ctl->us_tx_user_idx))
    {
        hmac_mgmt_reset_psm(&pst_hmac_vap->st_vap_base_info, pst_tx_ctl->us_tx_user_idx);
    }

    /* ���¼���dmac������֤֡ */
    ul_ret = hmac_tx_mgmt_send_event(&pst_hmac_vap->st_vap_base_info, pst_auth_rsp, us_auth_rsp_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_auth_rsp);
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_ap_rx_auth_req::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
    }

}

/*****************************************************************************
 �� �� ��  : hmac_ap_is_olbc_present
 ��������  : �ж�obss���Ƿ����non_ERPվ�����
 �������  : puc_payload    : beacon/probe response֡��ָ�� (������phy head��mac head)
             ul_payload_len : beacon/probe response֡�峤��
 �������  : ��
 �� �� ֵ  : OAL_TRUE: obss�д���non ERPվ�㣬  OAL_FALSE: ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum hmac_ap_is_olbc_present(oal_uint8 *puc_payload, oal_uint32 ul_payload_len)
{
    oal_uint8               uc_num_rates = 0;
    mac_erp_params_stru    *pst_erp_params;
    oal_uint8              *puc_ie       = OAL_PTR_NULL;


    if (ul_payload_len <= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_ap_is_olbc_present::payload_len[%d]}", ul_payload_len);
        return OAL_FALSE;
    }

    ul_payload_len -= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);
    puc_payload    += (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);

    puc_ie = mac_find_ie(MAC_EID_ERP, puc_payload, (oal_int32)ul_payload_len);
    if (OAL_PTR_NULL != puc_ie)
    {
        pst_erp_params = (mac_erp_params_stru *)(puc_ie + MAC_IE_HDR_LEN);
        /*���use protection����Ϊ1�� ����TRUE*/
        if (1 == pst_erp_params->bit_non_erp)
        {
            return OAL_TRUE;
        }
    }

    puc_ie = mac_find_ie(MAC_EID_RATES, puc_payload, (oal_int32)ul_payload_len);
    if (OAL_PTR_NULL != puc_ie)
    {
        uc_num_rates += puc_ie[1];
    }

    puc_ie = mac_find_ie(MAC_EID_XRATES, puc_payload, (oal_int32)ul_payload_len);
    if (OAL_PTR_NULL != puc_ie)
    {
        uc_num_rates += puc_ie[1];
    }

    /*����������ʼ���ĿС�ڻ����11bЭ��֧�ֵ�������ʼ������� ����TRUE*/
    if(uc_num_rates <= MAC_NUM_DR_802_11B)
    {
        OAM_INFO_LOG1(0, OAM_SF_ANY, "{hmac_ap_is_olbc_present::invalid uc_num_rates[%d].}", uc_num_rates);
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_process_obss_erp_ie
 ��������  : ����obss����beacon֡/probe response֡�е�ERP��ϢԪ��
 �������  : pst_hmac_vap   : hmac vapָ��
             puc_payload    : beacon/probe response֡��ָ�� (������phy head��mac head)
             ul_payload_len : beacon/probe response֡�峤��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_ap_process_obss_erp_ie(
                hmac_vap_stru                  *pst_hmac_vap,
                oal_uint8                      *puc_payload,
                oal_uint32                      ul_payload_len)
{
    /*����non erpվ��*/
    if (OAL_TRUE == hmac_ap_is_olbc_present(puc_payload, ul_payload_len))
    {
        pst_hmac_vap->st_vap_base_info.st_protection.bit_obss_non_erp_present = OAL_TRUE;
        pst_hmac_vap->st_vap_base_info.st_protection.uc_obss_non_ht_aging_cnt = 0;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_is_obss_non_ht_present
 ��������  : �ж�obss���Ƿ����non_htվ�����
 �������  : puc_payload    : beacon/probe response֡��ָ�� (������phy head��mac head)
             ul_payload_len : beacon/probe response֡�峤��
 �������  : ��
 �� �� ֵ  : OAL_TRUE: obss�д���non htվ�㣬  OAL_FALSE: ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum hmac_ap_is_obss_non_ht_present(oal_uint8 *puc_payload, oal_uint32 ul_payload_len)
{
    mac_ht_opern_stru      *pst_ht_opern;
    oal_uint8              *puc_ie        = OAL_PTR_NULL;

    if (ul_payload_len <= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_ap_is_olbc_present::payload_len[%d]}", ul_payload_len);
        return OAL_TRUE;
    }

    ul_payload_len -= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);
    puc_payload    += (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);

    puc_ie = mac_find_ie(MAC_EID_HT_OPERATION, puc_payload, (oal_int32)ul_payload_len);
    if (OAL_PTR_NULL != puc_ie)
    {
        pst_ht_opern  = (mac_ht_opern_stru *)(puc_ie + MAC_IE_HDR_LEN);
        if (1 == pst_ht_opern->bit_obss_nonht_sta_present)
        {
            /*���OBSS Non-HT STAs Present����Ϊ1�� ����TRUE*/
            return OAL_TRUE;
        }
    }

    puc_ie = mac_find_ie(MAC_EID_HT_CAP, puc_payload, (oal_int32)ul_payload_len);
    if (OAL_PTR_NULL != puc_ie)
    {
        /*�����HT capability��ϢԪ�أ�����FALSE*/
        return OAL_FALSE;
    }

    /*���û��HT capability��ϢԪ�أ�����TRUE*/
    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_process_obss_ht_operation_ie
 ��������  : ����obss����beacon֡/probe response֡�е�ERP��ϢԪ��
 �������  : pst_hmac_vap   : hmac vapָ��
             puc_payload    : beacon/probe response֡��ָ�� (������phy head��mac head)
             ul_payload_len : beacon/probe response֡�峤��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_ap_process_obss_ht_operation_ie(
                hmac_vap_stru                  *pst_hmac_vap,
                oal_uint8                      *puc_payload,
                oal_uint32                      ul_payload_len)
{
    /*�������non-htվ��*/
    if (OAL_TRUE == hmac_ap_is_obss_non_ht_present(puc_payload, ul_payload_len))
    {
        pst_hmac_vap->st_vap_base_info.st_protection.bit_obss_non_ht_present = OAL_TRUE;
        pst_hmac_vap->st_vap_base_info.st_protection.uc_obss_non_ht_aging_cnt = 0;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_rx_obss_beacon
 ��������  : ����obss����beacon֡/probe response֡
 �������  : pst_hmac_vap   : hmac vapָ��
             puc_payload    : beacon/probe response֡��ָ�� (������phy head��mac head)
             ul_payload_len : beacon/probe response֡�峤��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_ap_rx_obss_beacon(
                hmac_vap_stru                  *pst_hmac_vap,
                oal_uint8                      *puc_payload,
                oal_uint32                      ul_payload_len)
{
    /*����ERP���*/
    hmac_ap_process_obss_erp_ie(pst_hmac_vap, puc_payload, ul_payload_len);

    /*����HT operation���*/
    hmac_ap_process_obss_ht_operation_ie(pst_hmac_vap, puc_payload, ul_payload_len);

    /*����AP�б������mib��*/
    hmac_protection_update_mib_ap(&(pst_hmac_vap->st_vap_base_info));

    /*����vap�ı���ģʽ*/
    hmac_protection_update_mode_ap(&(pst_hmac_vap->st_vap_base_info));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_rx_deauth_req
 ��������  : �������ȥ��֤֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_ap_rx_deauth_req(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_mac_hdr, oal_bool_enum_uint8 en_is_protected)
{
    oal_uint8      *puc_sa          = OAL_PTR_NULL;
    oal_uint8      *puc_da          = OAL_PTR_NULL;
    hmac_user_stru *pst_hmac_user   = OAL_PTR_NULL;
	oal_uint16 		us_err_code 	= MAC_UNSPEC_REASON;
    oal_uint32      ul_ret;

    if (OAL_PTR_NULL == pst_hmac_vap || OAL_PTR_NULL == puc_mac_hdr)
    {
        OAM_ERROR_LOG2(0, OAM_SF_AUTH, "{hmac_ap_rx_deauth_req::param null, %p %p.}", pst_hmac_vap, puc_mac_hdr);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_rx_get_sa((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_sa);

	us_err_code	= *((oal_uint16 *)(puc_mac_hdr + MAC_80211_FRAME_LEN));

    /* ���ӽ��յ�ȥ��֤֡ʱ��ά����Ϣ */
    OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{aput rx deauth frame, reason code = %d, sa[XX:XX:XX:%X:%X:%X]}",
      us_err_code, puc_sa[3], puc_sa[4], puc_sa[5]);

    pst_hmac_user = mac_vap_get_hmac_user_by_addr(&pst_hmac_vap->st_vap_base_info, puc_sa);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{aput rx deauth frame, pst_hmac_user null.}");
        return OAL_FAIL;
    }

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    /*����Ƿ���Ҫ����SA query request*/
    if ((MAC_USER_STATE_ASSOC == pst_hmac_user->st_user_base_info.en_user_asoc_state) &&
        (OAL_SUCC == hmac_pmf_check_err_code(&pst_hmac_user->st_user_base_info, en_is_protected, puc_mac_hdr)))
    {
        /*�ڹ���״̬���յ�δ���ܵ�ReasonCode 6/7��Ҫ����SA Query����*/
        ul_ret = hmac_start_sa_query(&pst_hmac_vap->st_vap_base_info, pst_hmac_user, pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active);
        if(OAL_SUCC != ul_ret)
        {
            return OAL_ERR_CODE_PMF_SA_QUERY_START_FAIL;
        }
        return OAL_SUCC;
    }
#endif

    /*������û��Ĺ���֡�������Բ�һ�£������ñ���*/
    mac_rx_get_da((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_da);
    if ((OAL_TRUE != ETHER_IS_MULTICAST(puc_da)) &&
        (en_is_protected != pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active))
    {
        OAM_ERROR_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_ap_rx_deauth_req::PMF check failed %d %d.}",
                       en_is_protected, pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active);
        return OAL_FAIL;
    }
    /* ���¼��ϱ��ںˣ��Ѿ�ȥ����ĳ��STA */
    hmac_handle_disconnect_rsp_ap(pst_hmac_vap,pst_hmac_user);

    hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);
    return OAL_SUCC;

}
/*****************************************************************************
 �� �� ��  : hmac_user_sort_op_rates
 ��������  : ��һ��˳��user��������������
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
OAL_STATIC oal_void  hmac_user_sort_op_rates(hmac_user_stru *pst_hmac_user)
{
    oal_uint8  uc_loop;
    oal_uint8  uc_num_rates;
    oal_uint8  uc_min_rate;
    oal_uint8  uc_temp_rate;  /* ��ʱ���ʣ��������ݽ��� */
    oal_uint8  uc_index;
    oal_uint8  uc_temp_index; /* ��ʱ�������������ݽ��� */

    uc_num_rates = pst_hmac_user->st_op_rates.uc_rs_nrates;

    for (uc_loop = 0; uc_loop < uc_num_rates; uc_loop++)
    {
        /* ��¼��ǰ����Ϊ��С���� */
        uc_min_rate    = (pst_hmac_user->st_op_rates.auc_rs_rates[uc_loop] & 0x7F);
        uc_temp_index  = uc_loop;

        /* ���β�����С���� */
        for(uc_index= uc_loop + 1; uc_index < uc_num_rates; uc_index++)
        {
            /* ��¼����С���ʴ��������ǰ����*/
            if(uc_min_rate > (pst_hmac_user->st_op_rates.auc_rs_rates[uc_index] & 0x7F))
            {
                /* ������С���� */
                uc_min_rate   = (pst_hmac_user->st_op_rates.auc_rs_rates[uc_index] & 0x7F);
                uc_temp_index = uc_index;
            }
        }

        uc_temp_rate = pst_hmac_user->st_op_rates.auc_rs_rates[uc_loop];
        pst_hmac_user->st_op_rates.auc_rs_rates[uc_loop] = pst_hmac_user->st_op_rates.auc_rs_rates[uc_temp_index];
        pst_hmac_user->st_op_rates.auc_rs_rates[uc_temp_index] = uc_temp_rate;
    }
}

/*****************************************************************************
 �� �� ��  : hmac_ap_up_update_sta_cap_info
 ��������  : AP������STA��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��8��
    ��    ��   : zhangyu
    �޸�����   : ��Ӻ����������

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_ap_up_update_sta_cap_info(
                hmac_vap_stru                  *pst_hmac_vap,
                oal_uint16                      us_cap_info,
                hmac_user_stru                 *pst_hmac_user,
                mac_status_code_enum_uint16    *pen_status_code)
{
    mac_vap_stru                          *pst_mac_vap;
    oal_uint32                             ul_ret;
    mac_cap_info_stru *pst_cap_info  = (mac_cap_info_stru *)(&us_cap_info);

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == pen_status_code))
    {
        OAM_ERROR_LOG3(0, OAM_SF_ANY, "{hmac_ap_up_update_sta_cap_info::param null, %d %d %d.}",
                       pst_hmac_vap, pst_hmac_user, pen_status_code);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_mac_vap  =  &(pst_hmac_vap->st_vap_base_info);

    /* check bss capability info MAC,����MAC������ƥ���STA */
    ul_ret = hmac_check_bss_cap_info(us_cap_info, pst_mac_vap);
    if (ul_ret != OAL_TRUE)
    {
         OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY,
                        "{hmac_ap_up_update_sta_cap_info::hmac_check_bss_cap_info failed[%d].}", ul_ret);
        *pen_status_code = MAC_UNSUP_CAP;
        return OAL_FALSE;
    }

    /* ������ϸ�������Ϣ���������Ҫ���������������������Ϣ */
    mac_vap_check_bss_cap_info_phy_ap(us_cap_info, pst_mac_vap);

    if((0 == pst_cap_info->bit_privacy) &&
            (WLAN_80211_CIPHER_SUITE_NO_ENCRYP != pst_hmac_user->st_user_base_info.st_key_info.en_cipher_type))
    {
        *pen_status_code = MAC_UNSPEC_FAIL;
        return OAL_FALSE;
    }


    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_user_check_update_exp_rate
 ��������  : ��鲢������չ����
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
OAL_STATIC oal_uint32  hmac_user_check_update_exp_rate(hmac_user_stru *pst_hmac_user, oal_uint8 *pst_params, oal_uint8 *puc_erp_rates_num)
{

    oal_uint8       uc_rate_idx = 0;
    oal_uint8       uc_loop;
    mac_rate_stru  *pst_mac_rate;

    if((OAL_PTR_NULL == pst_hmac_user) || (OAL_PTR_NULL == pst_params) || (OAL_PTR_NULL == puc_erp_rates_num))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    *puc_erp_rates_num = pst_params[uc_rate_idx + 1];
    uc_rate_idx += MAC_IE_HDR_LEN;
    pst_mac_rate = &(pst_hmac_user->st_op_rates);

    if ((*puc_erp_rates_num) > (oal_uint8)WLAN_MAX_SUPP_RATES)
    {
        return OAL_FAIL;
    }

    for(uc_loop = 0; uc_loop < *puc_erp_rates_num; uc_loop++)
    {
        pst_mac_rate->auc_rs_rates[pst_mac_rate->uc_rs_nrates + uc_loop] = pst_params[uc_rate_idx + uc_loop] & 0x7F;
    }

    return OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : hmac_ap_up_update_sta_sup_rates
 ��������  : ������AP�����STA��������Ϣ
 �������  : oal_uint8                     *puc_payload    -- ����֡֡������ָ��
             oal_uint32                     ul_msg_len     -- ����֡֡�峤��
             hmac_user_stru                *pst_hmac_user  -- �����û��Ľṹ��ָ��
             oal_uint16                    *pus_msg_idx    -- ����֡֡��ƫ������
 �������  : wlan_status_code_enum_uint16  *pen_status_code-- ����״̬��
             oal_uint8                     *puc_num_rates  -- �����û������ʸ���
             oal_uint16                    *pus_msg_idx    -- ����֡֡��ƫ������
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��10��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ap_up_update_sta_sup_rates(
                oal_uint8                      *puc_payload,
                hmac_user_stru                 *pst_hmac_user,
                mac_status_code_enum_uint16    *pen_status_code,
                oal_uint32                      ul_msg_len,
                oal_uint16                      us_offset,
                oal_uint8                      *puc_num_rates,
                oal_uint16                     *pus_msg_idx)
{
    oal_uint8               uc_num_of_erp_rates   = 0;
    oal_uint32              ul_loop;
    mac_user_stru          *pst_mac_user;
    mac_vap_stru           *pst_mac_vap;
    oal_uint8              *puc_sup_rates_ie;
    oal_uint8              *puc_ext_sup_rates_ie;
    oal_uint8               uc_temp_rate;
    oal_uint32              ul_ret;
    oal_uint16              us_msg_idx = 0;

    /* ��ʼ�� */
    *puc_num_rates = 0;

    pst_mac_user = &(pst_hmac_user->st_user_base_info);

    pst_mac_vap = mac_res_get_mac_vap(pst_mac_user->uc_vap_id);

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        *pen_status_code = MAC_UNSUP_RATE;
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY,
                       "{hmac_ap_up_update_sta_sup_rates::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    //puc_sup_rates_ie = mac_get_supported_rates_ie((oal_uint8*)puc_payload, (oal_uint16)ul_msg_len, us_offset);
    puc_sup_rates_ie = mac_find_ie(MAC_EID_RATES, puc_payload + us_offset, (oal_int32)(ul_msg_len - us_offset));
    if (OAL_PTR_NULL == puc_sup_rates_ie)
    {
        *pen_status_code = MAC_UNSUP_RATE;
        OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY,
                       "{hmac_ap_up_update_sta_user::puc_ie null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_EID_RATES == puc_sup_rates_ie[0])
    {
        *puc_num_rates = puc_sup_rates_ie[1];

        /* ������ʸ���Ϊ0 ��ֱ�ӷ���ʧ�� */
        if (0 == *puc_num_rates)
        {
            *pen_status_code = MAC_UNSUP_RATE;
            *pus_msg_idx = us_msg_idx;
            OAM_ERROR_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY,
                       "{hmac_ap_up_update_sta_sup_rates::the sta's rates are not supported.}");
            return OAL_FAIL;
        }

        us_msg_idx += MAC_IE_HDR_LEN;

        if (*puc_num_rates > MAC_MAX_SUPRATES)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "hmac_ap_up_update_sta_sup_rates: *puc_num_rates error: %d", *puc_num_rates);
            *puc_num_rates = MAC_MAX_SUPRATES;
        }

        for (ul_loop = 0; ul_loop < *puc_num_rates; ul_loop++)
        {
            /* �����Ӧ�����ʵ�USER�� */
            pst_hmac_user->st_op_rates.auc_rs_rates[ul_loop] = puc_sup_rates_ie[us_msg_idx+ul_loop] & 0x7F;
        }

        us_msg_idx += *puc_num_rates;
        pst_hmac_user->st_op_rates.uc_rs_nrates = *puc_num_rates;

    }

    /* ���������չ���� */
    //puc_ext_sup_rates_ie = mac_get_exsup_rates_ie((oal_uint8*)puc_payload, (oal_uint16)ul_msg_len, us_offset);
    puc_ext_sup_rates_ie = mac_find_ie(MAC_EID_XRATES, puc_payload + us_offset, (oal_int32)(ul_msg_len - us_offset));
    if (OAL_PTR_NULL == puc_ext_sup_rates_ie)
    {
        /* DTS2015030301708��5G��������չ���ʣ�����Ҫ���� */
        if(WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
        {
            OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY,
                       "{hmac_ap_up_update_sta_user::puc_ext_sup_rates_ie null.}");
        }
    }
    else
    {
        /* ֻ��11g���ģʽ���߸���Э��汾��֧��ERP */
        if (MAC_EID_XRATES == puc_ext_sup_rates_ie[0]
        && (pst_mac_vap->en_protocol > WLAN_LEGACY_11G_MODE))
        {
            /* ����EXTRACE EXTENDED RATES,���õ���չ���ʵĸ��� */
            ul_ret = hmac_user_check_update_exp_rate(pst_hmac_user, puc_ext_sup_rates_ie,&uc_num_of_erp_rates);
            if (OAL_SUCC != ul_ret)
            {
                uc_num_of_erp_rates = 0;
            }
            //us_msg_idx += (puc_ext_sup_rates_ie[1] + MAC_IE_HDR_LEN);
        }
    }
    /* ���ʸ������� */
    *puc_num_rates += uc_num_of_erp_rates;

    /* ����STA֧�ֵ����ʸ��� */
    pst_hmac_user->st_op_rates.uc_rs_nrates = *puc_num_rates;

    /* ��һ��˳�������������� */
    hmac_user_sort_op_rates(pst_hmac_user);

    /*******************************************************************
      ����11gģʽ�Ŀɲ������ʣ�ʹ11b���ʶ��ۼ���11a֮ǰ
      802.11a ����:6��9��12��18��24��36��48��54Mbps
      802.11b ����:1��2��5.5��11Mbps
      ���ڰ���С���������802.11b�е�����11Mbps��802.11a�У��±�Ϊ5
      ���Դӵ���λ���м��鲢����
    *******************************************************************/
    if(pst_hmac_user->st_op_rates.uc_rs_nrates == MAC_DATARATES_PHY_80211G_NUM) /* 11g_compatibility mode */
    {
        if((pst_hmac_user->st_op_rates.auc_rs_rates[5] & 0x7F) == 0x16) /* 11Mbps */
        {
            uc_temp_rate = pst_hmac_user->st_op_rates.auc_rs_rates[5];
            pst_hmac_user->st_op_rates.auc_rs_rates[5] = pst_hmac_user->st_op_rates.auc_rs_rates[4];
            pst_hmac_user->st_op_rates.auc_rs_rates[4] = pst_hmac_user->st_op_rates.auc_rs_rates[3];
            pst_hmac_user->st_op_rates.auc_rs_rates[3] = uc_temp_rate;
        }
    }

    /*******************************************************************
      ���STA��֧�����л������ʷ��ز�֧�����ʵĴ�����
    *******************************************************************/
    hmac_check_sta_base_rate((oal_uint8 *)pst_hmac_user, pen_status_code);

    *pus_msg_idx = us_msg_idx;
    return OAL_SUCC;
}

#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
/*****************************************************************************
 �� �� ��  : hmac_check_assoc_req_security_cap_common
 ��������  : AP ���STA ��������֡�еİ�ȫ��ع�����Ϣ
 �������  : mac_vap_stru                * pst_mac_vap
             oal_uint8                   * puc_ie
             oal_uint32                    ul_msg_len
             oal_uint8                     uc_80211i_mode
             oal_uint8                     uc_offset
             mac_status_code_enum_uint16 * pen_status_code
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��17��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_check_assoc_req_security_cap_common(mac_vap_stru                * pst_mac_vap,
                                                    oal_uint8                   * puc_ie,
                                                    oal_uint32                    ul_msg_len,
                                                    oal_uint8                     uc_80211i_mode,
                                                    oal_uint8                     uc_offset,
                                                    mac_status_code_enum_uint16 * pen_status_code)
{
    wlan_mib_ieee802dot11_stru  *pst_mib_info    = OAL_PTR_NULL;
    oal_uint8                    uc_auth_policy  = 0;
    oal_uint8                    uc_pcip_policy  = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    oal_uint8                    uc_grp_policy   = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    oal_uint8                   *puc_oui         = OAL_PTR_NULL;
    oal_uint8                    uc_index        = uc_offset;
    oal_uint8                    uc_len          = 0;

    pst_mib_info                = pst_mac_vap->pst_mib_info;

    puc_oui = hmac_get_security_oui(uc_80211i_mode);
    if (OAL_PTR_NULL == puc_oui)
    {
        *pen_status_code = MAC_UNSUP_RSN_INFO_VER;
        return OAL_FAIL;
    }

    /* ���汾��Ϣ */
    if (pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigVersion != OAL_MAKE_WORD16(puc_ie[uc_index], puc_ie[uc_index + 1]))
    {
        *pen_status_code = MAC_UNSUP_RSN_INFO_VER;
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_check_assoc_req_security_cap_common::unsup rsn version=%d.}",
                       OAL_MAKE_WORD16(puc_ie[uc_index], puc_ie[uc_index + 1]));
        return OAL_FAIL;
    }

    /* ���԰汾��Ϣ */
    uc_index += 2;

    /* ����鲥OUI ��Ϣ DTS2015052702477 ���жϲ��ٷ��ش���ֻ�����ӡ */
    if (0 != oal_memcmp(puc_oui, puc_ie + uc_index, MAC_OUI_LEN))
    {
// *pen_status_code = MAC_INVALID_INFO_ELMNT;
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_check_assoc_req_security_cap_common::invalid OUI.}");
        //return OAL_FAIL;
    }
    uc_index += MAC_OUI_LEN;
    uc_grp_policy = puc_ie[uc_index++];/* ��ȡ�鲥��Կ */

    /* ��ȡ���������׼� */
    uc_pcip_policy = hmac_get_pcip_policy_auth(puc_ie + uc_index, &uc_len, puc_oui);
    uc_index += uc_len;

    /* ��ȡ��֤�׼���Ϣ */
    uc_auth_policy = hmac_get_auth_policy_auth(puc_ie + uc_index, &uc_len, puc_oui);

    /* �ɶ���Կ�׼��Ƿ�Ϊ�鲥��Կ�׼� */
    if (WLAN_80211_CIPHER_SUITE_GROUP_CIPHER == uc_pcip_policy)
    {
        uc_pcip_policy = uc_grp_policy;
    }

    /* ����鲥�׼� */
    if (pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher != uc_grp_policy)
    {
        *pen_status_code = MAC_INVALID_GRP_CIPHER;
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_check_assoc_req_security_cap_common::invalid group[%d].}", uc_grp_policy);
        return OAL_FAIL;
    }

    /* ��ⵥ����Կ�׼� */
    if (OAL_SUCC != hmac_check_pcip_policy(pst_mib_info, uc_pcip_policy, uc_80211i_mode))
    {
        *pen_status_code = MAC_INVALID_PW_CIPHER;
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_check_assoc_req_security_cap_common::invalid pcip[%d].}", uc_pcip_policy);
        return OAL_FAIL;
    }

    /* �����֤�׼� */
    if (OAL_FALSE == mac_check_auth_policy(pst_mib_info, uc_auth_policy))
    {
        *pen_status_code = MAC_INVALID_AKMP_CIPHER;
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_check_assoc_req_security_cap_common::invalid auth[%d].}", uc_auth_policy);
        return OAL_FAIL;
    }

    /* ��ֹ�����׼�ΪTKIP, �鲥�׼�ΪCCMP */
    if((WLAN_80211_CIPHER_SUITE_CCMP == uc_grp_policy)
        && (WLAN_80211_CIPHER_SUITE_TKIP == uc_pcip_policy))
    {
        *pen_status_code = MAC_CIPHER_REJ;
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_check_assoc_req_security_cap_common::group and pairwise cipher conflict.}");
        return OAL_FAIL;
    }

    if (uc_80211i_mode & DMAC_RSNA_802_11I)
    {
        /* ���RSN ����£����������� RSN capability */
        /* RSN Capabilities Information                          */
        /* ----------------------------------------------------- */
        /* | B15 - B6    | B5 - B4          | B3 - B2          | */
        /* ----------------------------------------------------- */
        /* | Reserved    | GTSKA Replay Ctr | PTSKA Replay Ctr | */
        /* ----------------------------------------------------- */
        /* | B1             | B0                               | */
        /* ----------------------------------------------------- */
        /* | No Pairwise    | Pre-Authentication               | */
        /* ----------------------------------------------------- */

        /* ���Ԥ��֤���� */

        /* �鲥�����׼�ΪWEP���ɶԼ����׼�ΪTKIP��������no-pairwise Ϊ 1 */

    }
    /* ����mib ���� */
    /* pst_mac_vap->uc_80211i_mode = uc_80211i_mode; */
    pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherRequested         = uc_grp_policy;
    pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherRequested      = uc_pcip_policy;
    pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteRequested = uc_auth_policy;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_check_assoc_req_sec_authenticator
 ��������  : AP �����յ���ASOC REQ��Ϣ�е�SECURITY����.�����,�򷵻ض�Ӧ�Ĵ�
             ����
 �������  : hmac_vap_stru               *pst_hmac_vap
             oal_uint8                   *puc_mac_hdr
             oal_uint8                   *puc_payload
             oal_uint32                   ul_msg_len
             hmac_user_stru               pst_hmac_user
             mac_status_code_enum_uint16 *pen_status_code
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��31��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_check_assoc_req_security_cap_authenticator(hmac_vap_stru               *pst_hmac_vap,
                             oal_uint8                   *puc_mac_hdr,
                             oal_uint8                   *puc_payload,
                             oal_uint32                   ul_msg_len,
                             hmac_user_stru              *pst_hmac_user,
                             mac_status_code_enum_uint16 *pen_status_code)
{
    oal_uint8                    uc_pcip_policy  = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    oal_uint8                    uc_grp_policy   = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;
    oal_uint8                    uc_80211i_mode  = 0;
    oal_uint8                   *puc_ie          = OAL_PTR_NULL;
    oal_uint8                   *puc_rsn_ie      = OAL_PTR_NULL;
    oal_uint8                   *puc_wpa_ie      = OAL_PTR_NULL;
    oal_uint8                    uc_index        = 0;
    oal_bool_enum_uint8          en_rsn_found    = OAL_FALSE;     /* AP ���յ���ASSOC REQ֡IE �Ƿ�ƥ�� */
    mac_vap_stru                *pst_mac_vap     = NULL;
    mac_user_stru               *pst_mac_user    = NULL;
    wlan_mib_ieee802dot11_stru  *pst_mib_info    = NULL;
    oal_uint32                   ul_ret;
    oal_uint8                    uc_offset;

    pst_mac_vap      = &(pst_hmac_vap->st_vap_base_info);
    pst_mib_info     = pst_mac_vap->pst_mib_info;

    pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherRequested         = 0;
    pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherRequested      = 0;

    if(OAL_TRUE != pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_check_assoc_req_security_cap_authenticator::dot11RSNAActivated = FALSE.}");
        return OAL_SUCC;
    }

    uc_offset = MAC_CAP_INFO_LEN + MAC_LIS_INTERVAL_IE_LEN;

    if (WLAN_FC0_SUBTYPE_REASSOC_REQ == mac_get_frame_sub_type(puc_mac_hdr))
    {
        uc_offset += OAL_MAC_ADDR_LEN;
    }

    /* ��ȡRSNA��WPA IE��Ϣ */
    puc_rsn_ie = mac_find_ie(MAC_EID_RSN, puc_payload + uc_offset, (oal_int32)(ul_msg_len - uc_offset));
    puc_wpa_ie = mac_find_vendor_ie(MAC_WLAN_OUI_MICROSOFT, MAC_OUITYPE_WPA, puc_payload + uc_offset, (oal_int32)(ul_msg_len - uc_offset));

    /* DTS2015080407959 �˴�����Ϊ�˼�����Щsta����wps����ʱ��Я��wps IE��Ϣ */
    if ((OAL_PTR_NULL == puc_rsn_ie) && (OAL_PTR_NULL == puc_wpa_ie))
    {
        /* ���ܷ�ʽ����WPA/WPA2�� ���ж��Ƿ�ΪWEP */
        uc_grp_policy = pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher;
        if (is_wep_cipher(uc_grp_policy))
        {
            pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherRequested = uc_grp_policy;
        }
        else if (OAL_TRUE == pst_hmac_vap->en_wps_active)
        {
            mac_user_init_key(&pst_hmac_user->st_user_base_info);
            return OAL_SUCC;
        }
        else
        {
            *pen_status_code = MAC_UNSPEC_FAIL;

            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_check_assoc_req_security_cap_authenticator::not WPA/WPA2.}");

            return OAL_FAIL;
        }
    }
    /* RSNA �� WPA���ܷ�ʽ���� */
    else
    {
        if (OAL_TRUE == pst_mac_vap->st_cap_flag.bit_wpa2)
        {
            if (OAL_PTR_NULL != puc_rsn_ie)
            {
                en_rsn_found   = OAL_TRUE;
                uc_80211i_mode = DMAC_RSNA_802_11I;

                /* �Թ� IE + LEN */
                uc_index += 2;

                puc_ie = puc_rsn_ie;
            }
        }

        if ((OAL_FALSE == en_rsn_found)
            &&(OAL_TRUE == pst_mac_vap->st_cap_flag.bit_wpa))
        {
            if (OAL_PTR_NULL != puc_wpa_ie)
            {
                en_rsn_found   = OAL_TRUE;
                uc_80211i_mode = DMAC_WPA_802_11I;

                uc_index += 6;/* �Թ� IE(1�ֽ�) + LEN(1�ֽ�) + WPA OUI(4�ֽ�) */

                puc_ie = puc_wpa_ie;
            }
            else
            {
                *pen_status_code = MAC_CIPHER_REJ;
                return OAL_FAIL;
            }
        }

        if ((OAL_TRUE == en_rsn_found) && (OAL_PTR_NULL != puc_ie))
        {
            ul_ret = hmac_check_assoc_req_security_cap_common(pst_mac_vap, puc_ie, ul_msg_len,
                                                    uc_80211i_mode, uc_index, pen_status_code);
            if (OAL_SUCC != ul_ret)
            {
                return OAL_FAIL;
            }
        }
    }

    if (MAC_SUCCESSFUL_STATUSCODE == *pen_status_code)
    {
        /* �����������Ӳ�����ܷ�ʽӦ�ñ��浽 mac_user -> en_cipher_type �� */
        pst_mac_user = &(pst_hmac_user->st_user_base_info);

        /* �����û��ļ��ܷ�ʽ */
        pst_mac_user->st_key_info.en_cipher_type = (uc_pcip_policy);
    }

    OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{hmac_check_assoc_req_security_cap_authenticator::"
                  "mode=%d, group=%d, pairwise=%d, auth=%d}\r\n", uc_80211i_mode, uc_grp_policy, uc_pcip_policy);

    return OAL_SUCC;
}
#endif /*(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)*/

/*****************************************************************************
 �� �� ��  : hmac_is_erp_sta
 ��������  : �鿴sta�Ƿ�����erpվ��
 �������  : mac_user_stru               pst_mac_user
 �������  : ��
 �� �� ֵ  : OAL_TRUE: staΪerpվ��
            OAL_FALSE:staΪ��erpվ��(11bվ��)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��26��
    ��    ��   : �ܺ���
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_is_erp_sta(hmac_user_stru *pst_hmac_user)
{
    oal_uint32            ul_loop        = 0;
    oal_bool_enum_uint8   en_is_erp_sta;

    /*ȷ���Ƿ���erp վ��*/
    if (pst_hmac_user->st_op_rates.uc_rs_nrates <= MAC_NUM_DR_802_11B)
    {
        en_is_erp_sta = OAL_FALSE;
        for (ul_loop = 0; ul_loop < pst_hmac_user->st_op_rates.uc_rs_nrates; ul_loop++)
        {
            /*���֧�����ʲ���11b��1M, 2M, 5.5M, 11M��Χ�ڣ���˵��վ��Ϊ֧��ERP��վ��*/
            if ((0x2 != (pst_hmac_user->st_op_rates.auc_rs_rates[ul_loop] & 0x7F))
               && (0x4 != (pst_hmac_user->st_op_rates.auc_rs_rates[ul_loop]& 0x7F))
               && (0xb != (pst_hmac_user->st_op_rates.auc_rs_rates[ul_loop]& 0x7F))
               && (0x16 != (pst_hmac_user->st_op_rates.auc_rs_rates[ul_loop]& 0x7F)))
            {
                 en_is_erp_sta = OAL_TRUE;
                 break;
            }
        }
    }
    else
    {
        en_is_erp_sta = OAL_TRUE;;
    }

    return en_is_erp_sta;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_up_update_legacy_capability
 ��������  : AP����assoc req �е�capability info
 �������  : pst_hmac_vap   : hmac vap�ṹ��ָ��
             pst_hmac_user  : hmac user�ṹ��ָ��
             us_cap_info    : ֡����cap info��Ϣ
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : caohaibin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ap_up_update_legacy_capability(
                hmac_vap_stru                  *pst_hmac_vap,
                hmac_user_stru                 *pst_hmac_user,
                oal_uint16                      us_cap_info)
{
    mac_protection_stru  *pst_protection = &(pst_hmac_vap->st_vap_base_info.st_protection);
    mac_user_stru        *pst_mac_user   = &(pst_hmac_user->st_user_base_info);
    oal_bool_enum_uint8   en_is_erp_sta  = OAL_FALSE;

    /*���STA��֧��short slot*/
    if ((us_cap_info & MAC_CAP_SHORT_SLOT) != MAC_CAP_SHORT_SLOT)
    {
        /*���STA֮ǰû�й����� ����֮ǰ��֧��short slotվ����ݹ�������Ҫupdate����*/
        if ((MAC_USER_STATE_ASSOC != pst_mac_user->en_user_asoc_state)
           || (OAL_TRUE == pst_hmac_user->st_hmac_cap_info.bit_short_slot_time))
        {
            pst_protection->uc_sta_no_short_slot_num++;
        }

        pst_hmac_user->st_hmac_cap_info.bit_short_slot_time = OAL_FALSE;
    }
    else/*���STA֧��short slot*/
    {
        /*���STA�Բ�֧��short slotվ����ݹ�������Ҫupdate����*/
        if ((MAC_USER_STATE_ASSOC == pst_mac_user->en_user_asoc_state)
           && (OAL_FALSE == pst_hmac_user->st_hmac_cap_info.bit_short_slot_time)
           && (0 != pst_protection->uc_sta_no_short_slot_num))
        {
            pst_protection->uc_sta_no_short_slot_num--;
        }

        pst_hmac_user->st_hmac_cap_info.bit_short_slot_time = OAL_TRUE;
    }

    pst_hmac_user->st_user_stats_flag.bit_no_short_slot_stats_flag = OAL_TRUE;


    /*���STA��֧��short preamble*/
    if ((us_cap_info & MAC_CAP_SHORT_PREAMBLE) != MAC_CAP_SHORT_PREAMBLE)
    {
        /*���STA֮ǰû�й����� ����֮ǰ��֧��short preambleվ����ݹ�������Ҫupdate����*/
        if ((MAC_USER_STATE_ASSOC != pst_mac_user->en_user_asoc_state)
           || (OAL_TRUE == pst_hmac_user->st_hmac_cap_info.bit_short_preamble))
        {
            pst_protection->uc_sta_no_short_preamble_num++;
        }

        pst_hmac_user->st_hmac_cap_info.bit_short_preamble = OAL_FALSE;
    }
    else/*���STA֧��short preamble*/
    {
        /*���STA֮ǰ�Բ�֧��short preambleվ����ݹ�������Ҫupdate����*/
        if ((MAC_USER_STATE_ASSOC == pst_mac_user->en_user_asoc_state)
           && (OAL_FALSE == pst_hmac_user->st_hmac_cap_info.bit_short_preamble)
           && (0 != pst_protection->uc_sta_no_short_preamble_num))
        {
            pst_protection->uc_sta_no_short_preamble_num--;
        }

        pst_hmac_user->st_hmac_cap_info.bit_short_preamble = OAL_TRUE;
    }

    pst_hmac_user->st_user_stats_flag.bit_no_short_preamble_stats_flag = OAL_TRUE;

    /*ȷ��user�Ƿ���erpվ��*/
    en_is_erp_sta = hmac_is_erp_sta(pst_hmac_user);

    /*���STA��֧��ERP*/
    if(OAL_FALSE == en_is_erp_sta)
    {
        /*���STA֮ǰû�й����� ����֮ǰ��֧��ERPվ����ݹ�������Ҫupdate����*/
        if ((MAC_USER_STATE_ASSOC != pst_mac_user->en_user_asoc_state)
           || (OAL_TRUE == pst_hmac_user->st_hmac_cap_info.bit_erp))
        {
            pst_protection->uc_sta_non_erp_num++;
        }

        pst_hmac_user->st_hmac_cap_info.bit_erp = OAL_FALSE;
    }
    else/*���STA֧��ERP*/
    {
        /*���STA֮ǰ�Բ�֧��ERP���վ���������Ҫupdate����*/
        if ((MAC_USER_STATE_ASSOC == pst_mac_user->en_user_asoc_state)
           && (OAL_FALSE == pst_hmac_user->st_hmac_cap_info.bit_erp)
           && (0 != pst_protection->uc_sta_non_erp_num))
        {
            pst_protection->uc_sta_non_erp_num--;
        }

        pst_hmac_user->st_hmac_cap_info.bit_erp = OAL_TRUE;
    }

    pst_hmac_user->st_user_stats_flag.bit_no_erp_stats_flag = OAL_TRUE;

    if ((us_cap_info & MAC_CAP_SPECTRUM_MGMT) != MAC_CAP_SPECTRUM_MGMT)
    {
        mac_user_set_spectrum_mgmt(&pst_hmac_user->st_user_base_info, OAL_FALSE);
    }
    else
    {
        mac_user_set_spectrum_mgmt(&pst_hmac_user->st_user_base_info, OAL_TRUE);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_up_update_asoc_entry_prot
 ��������  : ����ASOC����ʵ���е�UAPSD��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ap_up_update_asoc_entry_prot(
                oal_uint8                      *puc_mac_hdr,
                oal_uint8                       uc_sub_type,
                oal_uint32                      ul_msg_len,
                oal_uint16                      us_info_elem_offset,
                oal_uint16                      us_cap_info,
                hmac_user_stru                 *pst_hmac_user,
                hmac_vap_stru                  *pst_hmac_vap )
{
    /* WMM */
    //hmac_ap_up_update_asoc_uapsd_status(puc_mac_hdr, uc_sub_type, ul_msg_len, us_info_elem_offset, pst_hmac_user);
	hmac_uapsd_update_user_para(puc_mac_hdr, uc_sub_type, ul_msg_len, pst_hmac_user);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_up_update_sta_user
 ��������  : AP�����STA��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��27��
    ��    ��   : �ο���
    �޸�����   : �޸ĺ�������Ӱ�ȫ��ص���Ϣ

*****************************************************************************/
OAL_STATIC   oal_uint32  hmac_ap_up_update_sta_user(
                hmac_vap_stru                  *pst_hmac_vap,
                oal_uint8                      *puc_mac_hdr,
                oal_uint8                      *puc_payload,
                oal_uint32                      ul_msg_len,
                hmac_user_stru                 *pst_hmac_user,
                mac_status_code_enum_uint16    *pen_status_code)
{
    oal_uint32                  ul_rslt;
    oal_uint16                  us_msg_idx = 0;
    oal_uint16                  us_cap_info;
    oal_uint16                  us_ssid_len;
    oal_uint8                   uc_num_rates;
    oal_uint16                  us_rate_len = 0;
    mac_status_code_enum_uint16 us_ret_val = 0;
    mac_cfg_ssid_param_stru     st_cfg_ssid;
    const oal_uint8             *puc_rsn_ie;
    oal_uint16                  us_offset;
    wlan_bw_cap_enum_uint8      en_bandwidth_cap;
    wlan_bw_cap_enum_uint8      en_bwcap_ap;        /* ap����������� */
    oal_uint32                  ul_ret;
    mac_vap_stru               *pst_mac_vap;
    mac_user_stru              *pst_mac_user;
    wlan_bw_cap_enum_uint8      en_bwcap_vap;
#ifdef _PRE_WLAN_FEATURE_TXBF
    oal_uint8                  *puc_vendor_ie;
#endif

    *pen_status_code = MAC_SUCCESSFUL_STATUSCODE;
    us_offset        = MAC_CAP_INFO_LEN + MAC_LISTEN_INT_LEN;

    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    pst_mac_user  = &(pst_hmac_user->st_user_base_info);

    /***************************************************************************
        ���AP�Ƿ�֧�ֵ�ǰ���ڹ�����STA����������
        |ESS|IBSS|CFPollable|CFPReq|Privacy|Preamble|PBCC|Agility|Reserved|
    ***************************************************************************/
    us_cap_info = puc_payload[us_msg_idx] | (puc_payload[(us_msg_idx + 1)] << 8);

    ul_rslt = hmac_ap_up_update_sta_cap_info(pst_hmac_vap, us_cap_info, pst_hmac_user, pen_status_code);

    if (OAL_TRUE != ul_rslt)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_update_sta_user::hmac_ap_up_update_sta_cap_info failed[%d], status_code=%d.}", ul_rslt, *pen_status_code);
        return ul_rslt;
    }

    us_msg_idx += MAC_CAP_INFO_LEN;
    us_msg_idx += MAC_LIS_INTERVAL_IE_LEN;

    if (WLAN_FC0_SUBTYPE_REASSOC_REQ == mac_get_frame_sub_type(puc_mac_hdr))
    {
        /* �ع����ȹ�������֡ͷ����AP��MAC��ַ  */
        us_msg_idx += WLAN_MAC_ADDR_LEN;
        us_offset += WLAN_MAC_ADDR_LEN;
    }

    /* �ж�SSID,���Ȼ����ݲ�һ��ʱ,��Ϊ��SSID��һ�� */
    if (MAC_EID_SSID == puc_payload[us_msg_idx])
    {
        us_ssid_len = 0;

        st_cfg_ssid.uc_ssid_len = 0;

        hmac_config_get_ssid(pst_mac_vap, &us_ssid_len, (oal_uint8 *)(&st_cfg_ssid));

        if (st_cfg_ssid.uc_ssid_len != puc_payload[(us_msg_idx + 1)])
        {
            *pen_status_code = MAC_UNSPEC_FAIL;
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                             "{hmac_ap_up_update_sta_user::AP refuse STA assoc, ssid len mismatch, status_code=%d.}", *pen_status_code);
            return OAL_FAIL;
        }

        if (0 != oal_memcmp(&puc_payload[(us_msg_idx + 2)], st_cfg_ssid.ac_ssid, st_cfg_ssid.uc_ssid_len))
        {
            *pen_status_code = MAC_UNSPEC_FAIL;
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                             "{hmac_ap_up_update_sta_user::AP refuse STA assoc, ssid mismatch, status_code=%d.}", *pen_status_code);
            return OAL_FAIL;
        }
    }

    us_msg_idx += puc_payload[(us_msg_idx + 1)] + MAC_IE_HDR_LEN;

    /* ��ǰ�û��ѹ��� */
    ul_rslt = hmac_ap_up_update_sta_sup_rates(puc_payload, pst_hmac_user, pen_status_code, ul_msg_len, us_msg_idx, &uc_num_rates, &us_rate_len);
    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_update_sta_user::AP refuse STA assoc, update support rates failed, status_code[%d] ul_rslt[%d].}", *pen_status_code, ul_rslt);
        return ul_rslt;
    }

    us_msg_idx += us_rate_len;

#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    /* �����յ���ASOC REQ��Ϣ�е�SECURITY����.�����,�򷵻ض�Ӧ�Ĵ����� */
    ul_rslt = hmac_check_assoc_req_security_cap_authenticator(pst_hmac_vap, puc_mac_hdr, puc_payload, ul_msg_len, pst_hmac_user, pen_status_code);
    if(OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_update_sta_user::Reject STA because of security_cap_auth[%d].}", ul_rslt);
        return OAL_FAIL;
    }
#endif /* defined (_PRE_WLAN_FEATURE_WPA) ||��defined(_PRE_WLAN_FEATURE_WPA2) */

    /* ���¶�ӦSTA��legacyЭ������ */
    hmac_ap_up_update_legacy_capability(pst_hmac_vap, pst_hmac_user, us_cap_info);

    /* ���HT capability�Ƿ�ƥ�䣬�����д���  */
    us_ret_val = hmac_vap_check_ht_capabilities_ap(pst_hmac_vap, puc_payload, us_msg_idx, ul_msg_len, pst_hmac_user);
    if (MAC_SUCCESSFUL_STATUSCODE != us_ret_val)
    {
        *pen_status_code = us_ret_val;
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_update_sta_user::Reject STA because of ht_capability[%d].}", us_ret_val);
        return us_ret_val;
    }

    /*����AP�б������mib��*/
    ul_ret = hmac_protection_update_mib_ap(pst_mac_vap);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                    "{hmac_ap_up_update_sta_user::protection update mib failed, ret=%d.}", ul_ret);
    }

    /* ���¶�ӦSTA��Э������ update_asoc_entry_prot(ae, msa, rx_len, cap_info, is_p2p); */
    hmac_ap_up_update_asoc_entry_prot(puc_payload, mac_get_frame_sub_type(puc_mac_hdr), ul_msg_len,
                                    us_msg_idx, us_cap_info, pst_hmac_user,pst_hmac_vap);

    /* ����QoS���� */
    hmac_mgmt_update_assoc_user_qos_table(puc_payload, (oal_uint16)ul_msg_len, us_msg_idx, pst_hmac_user);

#ifdef _PRE_WLAN_FEATURE_TXBF
    /* ����11n txbf���� */
    puc_vendor_ie = mac_find_vendor_ie(MAC_HUAWEI_VENDER_IE, MAC_EID_11NTXBF, puc_payload + us_msg_idx, (oal_int32)(ul_msg_len - us_msg_idx));
    hmac_mgmt_update_11ntxbf_cap(puc_vendor_ie, pst_hmac_user);
#endif

    /* ����11ac VHT capabilities ie */
    us_ret_val = hmac_vap_check_vht_capabilities_ap(pst_hmac_vap, puc_payload, us_msg_idx, ul_msg_len, pst_hmac_user);
    if (MAC_SUCCESSFUL_STATUSCODE != us_ret_val)
    {
        *pen_status_code = us_ret_val;
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_update_sta_user::Reject STA because of vht_capability[%d].}", us_ret_val);
        return us_ret_val;
    }

    /* ����RSN��ϢԪ��,���û��RSN��ϢԪ��,���ղ�֧�ִ���*/
    //puc_rsn_ie = mac_get_rsn_ie(puc_payload, (oal_uint16)ul_msg_len, us_offset);
    puc_rsn_ie = mac_find_ie(MAC_EID_RSN, puc_payload + us_offset, (oal_int32)(ul_msg_len - us_offset));

    /* ����RSN��ϢԪ��, �ж�RSN�����Ƿ�ƥ��*/
    ul_ret = hmac_check_rsn_capability(pst_mac_vap, puc_rsn_ie, pen_status_code);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_update_sta_user::Reject STA because of rsn_capability[%d].}", ul_ret);
        return ul_ret;
    }
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    /* �����������ӵ�pmf�������� */
    hmac_set_pmf_cap(pst_mac_user, pst_mac_vap, puc_rsn_ie);
#endif


    /* ��ȡ�û���Э��ģʽ */
    hmac_set_user_protocol_mode(pst_mac_vap,pst_hmac_user);

    /* ��ȡ�û���VAPЭ��ģʽ���� */
    mac_user_set_avail_protocol_mode(pst_mac_user, g_auc_avail_protocol_mode[pst_mac_vap->en_protocol][pst_mac_user->en_protocol_mode]);
    mac_user_set_cur_protocol_mode(pst_mac_user, pst_mac_user->en_avail_protocol_mode);

    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                     "{hmac_ap_up_update_sta_user::mac_vap->en_protocol:%d,mac_user->en_protocol_mode:%d,en_avail_protocol_mode:%d.}",
                     pst_mac_vap->en_protocol, pst_mac_user->en_protocol_mode,
                     pst_mac_user->en_avail_protocol_mode);

    /* ��ȡ�û���VAP ��֧�ֵ�11a/b/g ���ʽ��� */
    hmac_vap_set_user_avail_rates(pst_mac_vap, pst_hmac_user);

    /* ��ȡ�û��Ĵ������� */
    mac_user_get_sta_cap_bandwidth(pst_mac_user, &en_bandwidth_cap);

    /* ��ȡvap�����������û����������Ľ��� */
    mac_vap_get_bandwidth_cap(&pst_hmac_vap->st_vap_base_info, &en_bwcap_ap);
    en_bwcap_vap = OAL_MIN(en_bwcap_ap, en_bandwidth_cap);
    mac_user_set_bandwidth_info(pst_mac_user, en_bwcap_vap, en_bwcap_vap);

    OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                     "{hmac_ap_up_update_sta_user::mac_vap->bandwidth:%d,mac_user->bandwidth:%d,cur_bandwidth:%d.}",
                     en_bwcap_ap, en_bandwidth_cap,
                     pst_mac_user->en_cur_bandwidth);

     ul_ret = hmac_config_user_cap_syn(pst_mac_vap, pst_mac_user);
     if (OAL_SUCC != ul_ret)
     {
         OAM_ERROR_LOG1(pst_mac_user->uc_vap_id, OAM_SF_ASSOC,
                        "{hmac_ap_up_update_sta_user::hmac_config_usr_cap_syn failed[%d].}", ul_ret);
     }

    /* �����û�֧�ִ���������Э�̳���ǰ����dmac offload�ܹ��£�ͬ��������Ϣ��device */
    ul_ret = hmac_config_user_info_syn(pst_mac_vap, pst_mac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_user->uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_ap_up_update_sta_user::usr_info_syn failed[%d].}", ul_ret);
    }

    /* ��ȡ�û���VAP�ռ������� */
    ul_ret = hmac_user_set_avail_num_space_stream(pst_mac_user, pst_mac_vap->en_vap_rx_nss);
    if (OAL_SUCC != ul_ret)
    {
         *pen_status_code = MAC_UNSPEC_FAIL;
         OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_update_sta_user::mac_user_set_avail_num_space_stream failed[%d].}", ul_ret);
    }

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    /* ����Operating Mode Notification ��ϢԪ�� */
    ul_ret = hmac_check_opmode_notify(pst_hmac_vap, puc_mac_hdr, puc_payload, us_msg_idx, ul_msg_len, pst_hmac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_ap_up_update_sta_user::hmac_check_opmode_notify failed[%d].}", ul_ret);
    }
#endif

    return MAC_SUCCESSFUL_STATUSCODE;
}


/*****************************************************************************
 �� �� ��  : hmac_ap_prepare_assoc_req
 ��������  : AP ����STA �Ĺ�������֡��Ϣ���Ա��ϱ��ں�
 �������  : hmac_user_stru *pst_hmac_user
             oal_uint8 *puc_payload
             oal_uint8 *us_len
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��2��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_ap_prepare_assoc_req(hmac_user_stru *pst_hmac_user, oal_uint8 *puc_payload, oal_uint32 ul_payload_len, oal_uint8 uc_mgmt_frm_type)
{
    oal_uint32 ul_payload_size;

    /* AP ����STA �Ĺ�������֡��Ϣ���Ա��ϱ��ں� */
    if(OAL_PTR_NULL != pst_hmac_user->puc_assoc_req_ie_buff)
    {
        OAL_MEM_FREE(pst_hmac_user->puc_assoc_req_ie_buff, OAL_TRUE);
        pst_hmac_user->puc_assoc_req_ie_buff = OAL_PTR_NULL;
        pst_hmac_user->ul_assoc_req_ie_len   = 0;
    }
    ul_payload_size = ul_payload_len;

    /* Ŀǰ11rû��ʵ�֣����Դ����ع���֡�����̺͹���֡һ����11rʵ�ֺ�˴���Ҫ�޸� */
    if (WLAN_FC0_SUBTYPE_REASSOC_REQ == uc_mgmt_frm_type)
    {
        /* �ع����ȹ�������֡ͷ����AP��MAC��ַ  */
        puc_payload += (WLAN_MAC_ADDR_LEN + MAC_CAP_INFO_LEN + MAC_LIS_INTERVAL_IE_LEN);
        ul_payload_len -= (WLAN_MAC_ADDR_LEN + MAC_CAP_INFO_LEN + MAC_LIS_INTERVAL_IE_LEN);
    }
    else
    {
        puc_payload += (MAC_CAP_INFO_LEN + MAC_LIS_INTERVAL_IE_LEN);
        ul_payload_len -= (MAC_CAP_INFO_LEN + MAC_LIS_INTERVAL_IE_LEN);
    }

    pst_hmac_user->puc_assoc_req_ie_buff = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)ul_payload_size, OAL_TRUE);
    if(OAL_PTR_NULL == pst_hmac_user->puc_assoc_req_ie_buff)
    {
        OAM_ERROR_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_ap_prepare_assoc_req::Alloc Assoc Req for kernel failed.}");
        pst_hmac_user->ul_assoc_req_ie_len = 0;
        return OAL_FAIL;
    }
    else
    {
        oal_memcopy(pst_hmac_user->puc_assoc_req_ie_buff, puc_payload, ul_payload_len);
        pst_hmac_user->ul_assoc_req_ie_len = ul_payload_len;
        return OAL_SUCC;
    }
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : hmac_ap_set_is_wavetest_sta
 ��������  : Wavetest STAʶ��
 �������  : hmac_vap_stru *pst_hmac_vap
             oal_uint8 *auc_sta_addr

 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��17��
    ��    ��   : ywx282918
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_ap_set_is_wavetest_sta(hmac_vap_stru *pst_hmac_vap, oal_uint8 *auc_sta_addr)
{
    mac_device_stru             *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{hmac_ap_set_is_wavetest_sta::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����MAC��ַʶ��  */
    pst_mac_device->en_is_wavetest = MAC_IS_WAVETEST_STA(auc_sta_addr);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_ap_up_rx_asoc_req
 ��������  : AP����յ���ӦSTA�Ĺ���������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��2��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ap_up_rx_asoc_req(
                hmac_vap_stru                  *pst_hmac_vap,
                oal_uint8                       uc_mgmt_frm_type,
                oal_uint8                      *puc_mac_hdr,
                oal_uint32                      ul_mac_hdr_len,
                oal_uint8                      *puc_payload,
                oal_uint32                      ul_payload_len)
{
    oal_uint32                      ul_rslt;
    oal_netbuf_stru                *pst_asoc_rsp;
    hmac_user_stru                 *pst_hmac_user;
    oal_uint16                      us_user_idx = 0;
    oal_uint32                      ul_asoc_rsp_len  = 0;
    mac_status_code_enum_uint16     en_status_code;
    oal_uint8                       auc_sta_addr[WLAN_MAC_ADDR_LEN];
    mac_tx_ctl_stru                *pst_tx_ctl;
#ifdef _PRE_WLAN_FEATURE_SMPS
    oal_uint8                       uc_user_prev_smpsmode;
#endif
    mac_cfg_80211_ucast_switch_stru st_80211_ucast_switch;
    mac_cfg_user_info_param_stru    st_hmac_user_info_event;
    oal_net_device_stru            *pst_net_device;
#ifdef _PRE_WLAN_FEATURE_P2P
                oal_int32 l_len;
#endif

    mac_get_address2(puc_mac_hdr, auc_sta_addr);

    ul_rslt = mac_vap_find_user_by_macaddr(&(pst_hmac_vap->st_vap_base_info), auc_sta_addr, &us_user_idx);
    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_asoc_req::mac_vap_find_user_by_macaddr failed[%d].}", ul_rslt);
        OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_asoc_req::user mac:%02X:XX:XX:%02X:%02X:%02X.}",
                         auc_sta_addr[0], auc_sta_addr[3], auc_sta_addr[4], auc_sta_addr[5]);
        hmac_mgmt_send_deauth_frame(&(pst_hmac_vap->st_vap_base_info), auc_sta_addr, MAC_ASOC_NOT_AUTH, OAL_FALSE);

        return ul_rslt;
    }

    OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_asoc_req::us_user_idx[%d].}", us_user_idx);

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_idx);

    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC,
                       "{hmac_ap_up_rx_asoc_req::pst_hmac_user null.}");

        /* û�в鵽��Ӧ��USER,����ȥ��֤��Ϣ */
        hmac_mgmt_send_deauth_frame(&(pst_hmac_vap->st_vap_base_info), auc_sta_addr, MAC_ASOC_NOT_AUTH, OAL_FALSE);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (pst_hmac_user->st_mgmt_timer.en_is_registerd == OAL_TRUE)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_user->st_mgmt_timer);
    }

#ifdef _PRE_WLAN_FEATURE_SMPS
    uc_user_prev_smpsmode = (oal_uint8)pst_hmac_user->st_user_base_info.st_ht_hdl.bit_sm_power_save;
#endif
    en_status_code = MAC_SUCCESSFUL_STATUSCODE;

    /* �Ƿ���ϴ���SA query���̵����� */
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    if ((OAL_TRUE != pst_hmac_user->st_sa_query_info.st_sa_query_interval_timer.en_is_enabled) &&
        (MAC_USER_STATE_ASSOC == pst_hmac_user->st_user_base_info.en_user_asoc_state) &&
        (OAL_TRUE == pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active))
    {
        OAM_INFO_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_ap_up_rx_asoc_req::AP rx STA assoc req ,and start sa query process.}");
        ul_rslt = hmac_start_sa_query(&pst_hmac_vap->st_vap_base_info, pst_hmac_user, pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active);
        if (OAL_SUCC != ul_rslt)
        {
             OAM_ERROR_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_ap_up_rx_asoc_req::hmac_start_sa_query failed[%d].}", ul_rslt);
             return ul_rslt;
        }
        OAM_INFO_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_ap_up_rx_asoc_req::set en_status_code is MAC_REJECT_TEMP.}");
        en_status_code = MAC_REJECT_TEMP;
    }
#endif

    if (MAC_REJECT_TEMP != en_status_code)
    {
        /* �����Բ��ҵ��û�ʱ,˵����ǰUSER��״̬Ϊ�ѹ���������֤��� */
        ul_rslt = hmac_ap_up_update_sta_user(pst_hmac_vap, puc_mac_hdr, puc_payload, ul_payload_len, pst_hmac_user, &en_status_code);
        if (MAC_SUCCESSFUL_STATUSCODE != en_status_code)
        {
            OAM_WARNING_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_ap_up_rx_asoc_req::hmac_ap_up_update_sta_user failed[%d].}", en_status_code);
        #ifdef _PRE_DEBUG_MODE_USER_TRACK
            mac_user_change_info_event(pst_hmac_user->st_user_base_info.auc_user_mac_addr,
                                       pst_hmac_vap->st_vap_base_info.uc_vap_id,
                                       pst_hmac_user->st_user_base_info.en_user_asoc_state,
                                       MAC_USER_STATE_AUTH_COMPLETE, OAM_MODULE_ID_HMAC,
                                       OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
        #endif
            hmac_user_set_asoc_state(&(pst_hmac_vap->st_vap_base_info), &pst_hmac_user->st_user_base_info, MAC_USER_STATE_AUTH_COMPLETE);
        }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        /* ͬ��ap������������Ϣ��dmac*/
        hmac_chan_sync(&pst_hmac_vap->st_vap_base_info, pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number,
                            pst_hmac_vap->st_vap_base_info.st_channel.en_bandwidth, OAL_FALSE);

#endif

        /* �����û�֧�ִ���������Э�̳���ǰ����dmac offload�ܹ��£�ͬ��������Ϣ��device */
        ul_rslt = hmac_config_user_info_syn(&(pst_hmac_vap->st_vap_base_info), &pst_hmac_user->st_user_base_info);
        if (OAL_SUCC != ul_rslt)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                        "{hmac_ap_up_rx_asoc_req::usr_info_syn failed[%d].}", ul_rslt);
        }

        if (MAC_SUCCESSFUL_STATUSCODE == en_status_code)
        {
            ul_rslt = hmac_init_security(&(pst_hmac_vap->st_vap_base_info),auc_sta_addr);
            if (OAL_SUCC != ul_rslt)
            {
                OAM_ERROR_LOG2(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                                "{hmac_ap_up_rx_asoc_req::hmac_init_security failed[%d] status_code[%d].}", ul_rslt, MAC_UNSPEC_FAIL);
                en_status_code = MAC_UNSPEC_FAIL;
            }

        #if defined (_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
            ul_rslt = hmac_init_user_security_port(&(pst_hmac_vap->st_vap_base_info), &(pst_hmac_user->st_user_base_info));
            if (OAL_SUCC != ul_rslt)
            {
                OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                               "{hmac_ap_up_rx_asoc_req::hmac_init_user_security_port failed[%d].}", ul_rslt);
            }
        #endif /* defined(_PRE_WLAN_FEATURE_WPA) ||��defined(_PRE_WLAN_FEATURE_WPA2) */
        }

        if ((OAL_SUCC != ul_rslt)
         || (MAC_SUCCESSFUL_STATUSCODE != en_status_code))
        {
            OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_CFG,
                             "{hmac_ap_up_rx_asoc_req::hmac_ap_up_update_sta_user fail rslt[%d] status_code[%d].", ul_rslt, en_status_code);
        #ifdef _PRE_DEBUG_MODE_USER_TRACK
            mac_user_change_info_event(pst_hmac_user->st_user_base_info.auc_user_mac_addr,
                                       pst_hmac_vap->st_vap_base_info.uc_vap_id,
                                       pst_hmac_user->st_user_base_info.en_user_asoc_state,
                                       MAC_USER_STATE_AUTH_COMPLETE, OAM_MODULE_ID_HMAC,
                                       OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
        #endif
            hmac_user_set_asoc_state(&(pst_hmac_vap->st_vap_base_info), &pst_hmac_user->st_user_base_info, MAC_USER_STATE_AUTH_COMPLETE);
        }
#ifdef _PRE_WLAN_FEATURE_P2P
        l_len = ((uc_mgmt_frm_type == WLAN_FC0_SUBTYPE_REASSOC_REQ) ? (MAC_CAP_INFO_LEN + MAC_LISTEN_INT_LEN + WLAN_MAC_ADDR_LEN) : (MAC_CAP_INFO_LEN + MAC_LISTEN_INT_LEN));
        if (IS_P2P_GO(&pst_hmac_vap->st_vap_base_info) &&
            /* (OAL_PTR_NULL == mac_get_p2p_ie(puc_payload, (oal_uint16)ul_payload_len, MAC_CAP_INFO_LEN + MAC_LISTEN_INT_LEN)) */
            (OAL_PTR_NULL == mac_find_vendor_ie(MAC_WLAN_OUI_WFA, MAC_WLAN_OUI_TYPE_WFA_P2P, puc_payload + l_len, (oal_int32)ul_payload_len - l_len)))
        {
            OAM_INFO_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                       "{hmac_ap_up_rx_asoc_req::GO got assoc request from legacy device, length = [%d]}",ul_payload_len);
            hmac_disable_p2p_pm(pst_hmac_vap);
        }
#endif

    }

    pst_asoc_rsp = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if (OAL_PTR_NULL == pst_asoc_rsp)
    {
        OAM_ERROR_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC, "{hmac_ap_up_rx_asoc_req::pst_asoc_rsp null.}");
        /*�쳣����֮ǰɾ��user*/
        hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_asoc_rsp);
    OAL_MEMZERO(pst_tx_ctl, OAL_NETBUF_CB_SIZE());

    OAL_MEM_NETBUF_TRACE(pst_asoc_rsp, OAL_TRUE);

    if (WLAN_FC0_SUBTYPE_ASSOC_REQ == uc_mgmt_frm_type)
    {
        ul_asoc_rsp_len = hmac_mgmt_encap_asoc_rsp_ap(&(pst_hmac_vap->st_vap_base_info),
                                                      auc_sta_addr,
                                                      pst_hmac_user->st_user_base_info.us_assoc_id,
                                                      en_status_code,
                                                      OAL_NETBUF_HEADER(pst_asoc_rsp),
                                                      WLAN_FC0_SUBTYPE_ASSOC_RSP);
    }
    else if (WLAN_FC0_SUBTYPE_REASSOC_REQ == uc_mgmt_frm_type)
    {
        ul_asoc_rsp_len = hmac_mgmt_encap_asoc_rsp_ap(&(pst_hmac_vap->st_vap_base_info),
                                                      auc_sta_addr,
                                                      pst_hmac_user->st_user_base_info.us_assoc_id,
                                                      en_status_code,
                                                      OAL_NETBUF_HEADER(pst_asoc_rsp),
                                                      WLAN_FC0_SUBTYPE_REASSOC_RSP);
    }

    if (0 == ul_asoc_rsp_len)
    {
        OAM_WARNING_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_asoc_req::hmac_mgmt_encap_asoc_rsp_ap encap msg fail.}");
        oal_netbuf_free(pst_asoc_rsp);

        /*�쳣����֮ǰɾ��user*/
        hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);

        return OAL_FAIL;
    }

    oal_netbuf_put(pst_asoc_rsp, ul_asoc_rsp_len);

    pst_tx_ctl->us_tx_user_idx = pst_hmac_user->st_user_base_info.us_assoc_id;
    pst_tx_ctl->us_mpdu_len    = (oal_uint16)ul_asoc_rsp_len;

    /* ���͹�����Ӧ֮֡ǰ�����û��Ľ���״̬��λ */
    hmac_mgmt_reset_psm(&pst_hmac_vap->st_vap_base_info, pst_tx_ctl->us_tx_user_idx);


    /* �жϵ�ǰ״̬������û��Ѿ������ɹ������ϱ��û��뿪��Ϣ */
    if (MAC_USER_STATE_ASSOC == pst_hmac_user->st_user_base_info.en_user_asoc_state)
    {
        pst_net_device = hmac_vap_get_net_device(pst_hmac_vap->st_vap_base_info.uc_vap_id);
        if (OAL_PTR_NULL != pst_net_device)
        {
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
            oal_kobject_uevent_env_sta_leave(pst_net_device, auc_sta_addr);
#endif
#endif
        }
    }

    if (MAC_SUCCESSFUL_STATUSCODE == en_status_code)
    {
        hmac_user_set_asoc_state(&(pst_hmac_vap->st_vap_base_info), &pst_hmac_user->st_user_base_info, MAC_USER_STATE_ASSOC);
    }

    ul_rslt = hmac_tx_mgmt_send_event(&(pst_hmac_vap->st_vap_base_info), pst_asoc_rsp, (oal_uint16)ul_asoc_rsp_len);

    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_asoc_req::hmac_tx_mgmt_send_event failed[%d].}", ul_rslt);
        oal_netbuf_free(pst_asoc_rsp);

        /*�쳣����֮ǰɾ��user*/
        hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);

        return ul_rslt;
    }

    if (MAC_SUCCESSFUL_STATUSCODE == en_status_code)
    {
        /* Ϊ�˽��wavetest����MCS9 shortGI�������ܵ͵�����:wavetest���Գ����£�AGC�̶���ͨ��0 */
    #if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        hmac_ap_set_is_wavetest_sta(pst_hmac_vap,auc_sta_addr);
    #endif

        /* AP���STA�ɹ�������������ɹ�*/
    #ifdef _PRE_DEBUG_MODE_USER_TRACK
        mac_user_change_info_event(pst_hmac_user->st_user_base_info.auc_user_mac_addr,
                                       pst_hmac_vap->st_vap_base_info.uc_vap_id,
                                       pst_hmac_user->st_user_base_info.en_user_asoc_state,
                                       MAC_USER_STATE_ASSOC, OAM_MODULE_ID_HMAC,
                                       OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
    #endif
        /* ��80211��������֡���أ��۲�������̣������ɹ��˾͹ر� */
        st_80211_ucast_switch.en_frame_direction = OAM_OTA_FRAME_DIRECTION_TYPE_TX;
        st_80211_ucast_switch.en_frame_type = OAM_USER_TRACK_FRAME_TYPE_MGMT;
        st_80211_ucast_switch.en_frame_switch = OAL_SWITCH_OFF;
        st_80211_ucast_switch.en_cb_switch = OAL_SWITCH_OFF;
        st_80211_ucast_switch.en_dscr_switch = OAL_SWITCH_OFF;
        oal_memcopy(st_80211_ucast_switch.auc_user_macaddr,
                (const oal_void *)pst_hmac_user->st_user_base_info.auc_user_mac_addr,
                OAL_SIZEOF(st_80211_ucast_switch.auc_user_macaddr));
        hmac_config_80211_ucast_switch(&(pst_hmac_vap->st_vap_base_info),OAL_SIZEOF(st_80211_ucast_switch),(oal_uint8 *)&st_80211_ucast_switch);

        st_80211_ucast_switch.en_frame_direction = OAM_OTA_FRAME_DIRECTION_TYPE_RX;
        st_80211_ucast_switch.en_frame_type = OAM_USER_TRACK_FRAME_TYPE_MGMT;
        st_80211_ucast_switch.en_frame_switch = OAL_SWITCH_OFF;
        st_80211_ucast_switch.en_cb_switch = OAL_SWITCH_OFF;
        st_80211_ucast_switch.en_dscr_switch = OAL_SWITCH_OFF;
        hmac_config_80211_ucast_switch(&(pst_hmac_vap->st_vap_base_info),OAL_SIZEOF(st_80211_ucast_switch),(oal_uint8 *)&st_80211_ucast_switch);

#ifdef _PRE_WLAN_FEATURE_SMPS
        hmac_smps_user_asoc_update(uc_user_prev_smpsmode,(&pst_hmac_user->st_user_base_info), (&pst_hmac_vap->st_vap_base_info));
#endif


        ul_rslt = hmac_config_user_rate_info_syn(&(pst_hmac_vap->st_vap_base_info), &pst_hmac_user->st_user_base_info);
        if (OAL_SUCC != ul_rslt)
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                           "{hmac_sta_wait_asoc_rx::hmac_config_user_rate_info_syn failed[%d].}", ul_rslt);
        }


        /*  user�Ѿ������ϣ����¼���DMAC����DMAC����û��㷨���� */
        hmac_user_add_notify_alg((&pst_hmac_vap->st_vap_base_info), us_user_idx);

        /* AP ����STA �Ĺ�������֡��Ϣ���Ա��ϱ��ں� */
        hmac_ap_prepare_assoc_req(pst_hmac_user, puc_payload, ul_payload_len, uc_mgmt_frm_type);


        /* �ϱ�WAL��(WAL�ϱ��ں�) AP��������һ���µ�STA */
        hmac_handle_connect_rsp_ap(pst_hmac_vap, pst_hmac_user);
        OAM_WARNING_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_ASSOC,
                        "{hmac_ap_up_rx_asoc_req::STA assoc AP SUCC! STA_indx=%d.}", us_user_idx);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        pst_hmac_vap->en_amsdu_active = OAL_FALSE;
#endif
#endif

    }
    else
    {
        /* AP���STAʧ�ܣ�����ɾ�� */
        if (MAC_REJECT_TEMP != en_status_code)
        {
            hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);
        }
    }

    /* 1102 STA �������ϱ�VAP ��Ϣ���û���Ϣ */
    st_hmac_user_info_event.us_user_idx = us_user_idx;

    hmac_config_vap_info(&(pst_hmac_vap->st_vap_base_info), OAL_SIZEOF(oal_uint32), (oal_uint8 *)&ul_rslt);
    hmac_config_user_info(&(pst_hmac_vap->st_vap_base_info), OAL_SIZEOF(mac_cfg_user_info_param_stru), (oal_uint8 *)&st_hmac_user_info_event);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_up_rx_disasoc
 ��������  : AP����յ���ӦSTA��ȥ����������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��2��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ap_up_rx_disasoc(
                hmac_vap_stru                  *pst_hmac_vap,
                oal_uint8                      *puc_mac_hdr,
                oal_uint32                      ul_mac_hdr_len,
                oal_uint8                      *puc_payload,
                oal_uint32                      ul_payload_len,
                oal_bool_enum_uint8             en_is_protected)
{
    oal_uint32              ul_ret;
    hmac_user_stru         *pst_hmac_user;
    oal_uint8              *puc_da;
    oal_uint8              *puc_sa;
    oal_uint8               auc_sta_addr[WLAN_MAC_ADDR_LEN];

    mac_get_address2(puc_mac_hdr, auc_sta_addr);

    /* ���ӽ��յ�ȥ����֡ʱ��ά����Ϣ */
    mac_rx_get_sa((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_sa);

    OAM_WARNING_LOG4(0, OAM_SF_ASSOC,
                     "{hmac_ap_up_rx_disasoc::Because of err_code[%d], received disassoc frame from source addr %02x:xx:xx:xx:%02x:%02x.}",
                     *((oal_uint16 *)(puc_mac_hdr + MAC_80211_FRAME_LEN)), puc_sa[0], puc_sa[4], puc_sa[5]);

    pst_hmac_user = mac_vap_get_hmac_user_by_addr(&(pst_hmac_vap->st_vap_base_info), auc_sta_addr);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_disasoc::pst_hmac_user null.}");
        /* û�в鵽��Ӧ��USER,����ȥ��֤��Ϣ */
        hmac_mgmt_send_deauth_frame(&(pst_hmac_vap->st_vap_base_info), auc_sta_addr, MAC_NOT_ASSOCED, OAL_FALSE);

        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_disasoc::ap rx a disaasoc req.}");
    if (MAC_USER_STATE_ASSOC == pst_hmac_user->st_user_base_info.en_user_asoc_state)
    {
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
       /*����Ƿ���Ҫ����SA query request*/
        if (OAL_SUCC == hmac_pmf_check_err_code(&pst_hmac_user->st_user_base_info, en_is_protected, puc_mac_hdr))
        {
            /*�ڹ���״̬���յ�δ���ܵ�ReasonCode 6/7��Ҫ����SA Query����*/
            ul_ret = hmac_start_sa_query(&pst_hmac_vap->st_vap_base_info, pst_hmac_user, pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active);
            if (OAL_SUCC != ul_ret)
            {
                OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_disasoc::hmac_start_sa_query failed[%d].}", ul_ret);
                return OAL_ERR_CODE_PMF_SA_QUERY_START_FAIL;
            }
            return OAL_SUCC;
        }
 #endif

        /*������û��Ĺ���֡�������Բ�һ�£������ñ���*/
        mac_rx_get_da((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_da);
        if ((OAL_TRUE != ETHER_IS_MULTICAST(puc_da)) &&
           (en_is_protected != pst_hmac_user->st_user_base_info.st_cap_info.bit_pmf_active))
        {
            OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_disasoc::PMF check failed,en_is_protected=%d.}", en_is_protected);
            return OAL_FAIL;
        }

#ifdef _PRE_DEBUG_MODE_USER_TRACK
        mac_user_change_info_event(pst_hmac_user->st_user_base_info.auc_user_mac_addr,
                                   pst_hmac_vap->st_vap_base_info.uc_vap_id,
                                   pst_hmac_user->st_user_base_info.en_user_asoc_state,
                                   MAC_USER_STATE_AUTH_COMPLETE, OAM_MODULE_ID_HMAC,
                                   OAM_USER_INFO_CHANGE_TYPE_ASSOC_STATE);
#endif
        mac_user_set_asoc_state(&pst_hmac_user->st_user_base_info, MAC_USER_STATE_AUTH_COMPLETE);

        /* ���¼��ϱ��ںˣ��Ѿ�ȥ����ĳ��STA */
        hmac_handle_disconnect_rsp_ap(pst_hmac_vap,pst_hmac_user);

        /* ��Щ����ȥ����ʱֻ����DISASOC,Ҳ��ɾ������AP�ڲ������ݽṹ */
        ul_ret = hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ASSOC,
                         "{hmac_ap_up_rx_disasoc::hmac_user_del failed[%d].}", ul_ret);
        }
    }

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : hmac_ap_up_rx_2040_coext
 ��������  : AP��UP״̬�µĽ���"20/40�������֡"�Ĵ���
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ��
             pst_netbuf  : "20/40�������֡"���ڵ�netbuf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ap_up_rx_2040_coext(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_device_stru    *pst_mac_device;
    mac_vap_stru       *pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    dmac_rx_ctl_stru   *pst_rx_ctrl;
    oal_uint32          ul_index;
    oal_uint8           uc_coext_info;
    oal_uint8          *puc_data;
    oal_uint32          ul_ret  = OAL_SUCC;

    /* 5GHzƵ�κ��� 20/40 BSS�������֡ */
    if ((WLAN_BAND_5G == pst_mac_vap->st_channel.en_band) ||
        (OAL_FALSE    == mac_mib_get_2040BSSCoexistenceManagementSupport(pst_mac_vap)))
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                         "{hmac_ap_up_rx_2040_coext::Now in 5GHz.}");
        return;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040, "{hmac_ap_up_rx_2040_coext::pst_mac_device null.}");
        return;
    }

    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* ��ȡ֡��ָ�� */
    puc_data = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    ul_index = MAC_ACTION_OFFSET_ACTION + 1;

    /* 20/40 BSS Coexistence IE */
    if (MAC_EID_2040_COEXT == puc_data[ul_index])
    {
        uc_coext_info = puc_data[ul_index + MAC_IE_HDR_LEN];

        OAM_INFO_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                      "{hmac_ap_up_rx_2040_coext::20/40 Coexistence Management frame received, Coext Info=0x%x.}", uc_coext_info);
        /* BIT1 - Forty MHz Intolerant */
        /* BIT2 - 20 MHz BSS Width Request */
        if (uc_coext_info & (BIT1 | BIT2))
        {
            hmac_chan_start_40M_recovery_timer(pst_mac_vap);

            /* ���BIT1��BIT2����Ϊ1���ҵ�ǰ�����ŵ���ȴ���20MHz����AP��Ҫ�л���20MHz���� */
            if (pst_mac_vap->st_channel.en_bandwidth > WLAN_BAND_WIDTH_20M)
            {
                hmac_chan_multi_switch_to_20MHz_ap(pst_hmac_vap);
            }
            else
            {
                pst_mac_device->en_40MHz_intol_bit_recd = OAL_TRUE;
            }
        }

        ul_index += (MAC_IE_HDR_LEN + puc_data[ul_index + 1]);
    }

    /* 20/40 BSS Intolerant Channel Report IE */
    if (MAC_EID_2040_INTOLCHREPORT == puc_data[ul_index])
    {
        oal_uint8              uc_len        = puc_data[ul_index + 1];
        oal_uint8              uc_chan_idx   = 0, uc_loop;
        oal_bool_enum_uint8    en_reval_chan = OAL_FALSE;

        ul_index += (MAC_IE_HDR_LEN + 1);   /* skip Element ID��Length��Operating Class */
        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "{hmac_ap_up_rx_2040_coext::Chan Report with len=%d.}\r\n", uc_len);

        for (uc_loop = 0; uc_loop < uc_len - 1; uc_loop++, ul_index++)
        {
            ul_ret = mac_get_channel_idx_from_num(pst_mac_vap->st_channel.en_band, puc_data[ul_index], &uc_chan_idx) ;
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                                 "{hmac_ap_up_rx_2040_coext::mac_get_channel_idx_from_num failed[%d].}", ul_ret);
                continue;
            }

            ul_ret = mac_is_channel_idx_valid(pst_mac_vap->st_channel.en_band, uc_chan_idx);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG2(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                                 "{hmac_ap_up_rx_2040_coext::channel(indx=%d) not valid, return[%d].}", uc_chan_idx, ul_ret);
                continue;
            }

            if (MAC_CH_TYPE_PRIMARY != pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_type)
            {
                pst_mac_device->st_ap_channel_list[uc_chan_idx].en_ch_type = MAC_CH_TYPE_PRIMARY;
                en_reval_chan = OAL_TRUE;
            }
        }

        if (OAL_TRUE == en_reval_chan)
        {
            OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_2040,
                                 "{hmac_ap_up_rx_2040_coext::Re-evaluation needed as some channel status changed.}");

            /* ��������ŵ����ߴ����л����Ž����л� */
            if (0 == pst_hmac_vap->en_2040_switch_prohibited)
            {
                hmac_chan_start_40M_recovery_timer(pst_mac_vap);
                /* ���������Ƿ���Ҫ�����ŵ��л� */
                hmac_chan_reval_status(pst_mac_device, pst_mac_vap);
            }
        }
    }
}
/*****************************************************************************
 �� �� ��  : hmac_ap_is_40MHz_intol_bit_set
 ��������  : �����յ�֡�е�HT Capabilities IE�����"40MHz������"�Ƿ���λ
 �������  : puc_payload   : ֡��ָ��
             us_payload_len: ֡�峤��
 �������  : ��
 �� �� ֵ  : OAL_TRUE : "40MHz������"����1
             OAL_FALSE: "40MHz������"û�б���1
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  oal_bool_enum_uint8  hmac_ap_is_40MHz_intol_bit_set(oal_uint8 *puc_payload, oal_uint16 us_payload_len)
{
    oal_uint16   us_ht_cap_info = 0;
    oal_uint8   *puc_ht_cap     = OAL_PTR_NULL;

    if (us_payload_len <= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_ap_is_40MHz_intol_bit_set::payload_len[%d]}", us_payload_len);
        return OAL_FALSE;
    }

    us_payload_len -= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);
    puc_payload    += (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);

    puc_ht_cap = mac_find_ie(MAC_EID_HT_CAP, puc_payload, us_payload_len);
    if (OAL_PTR_NULL != puc_ht_cap)
    {
        us_ht_cap_info = OAL_MAKE_WORD16(puc_ht_cap[MAC_IE_HDR_LEN], puc_ht_cap[MAC_IE_HDR_LEN + 1]);

        /* Forty MHz Intolerant BIT Ϊ1 */
        if (us_ht_cap_info & BIT14)
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_update_2040_chan_info
 ��������  : ��obss Beacon/Probe Response֡�и����ŵ�ɨ����Ϣ(������AP�ŵ�ѡ����)
 �������  : pst_mac_device:
             pst_mac_vap:
             puc_payload
             us_payload_len
             uc_pri_chan_idx
             en_sec_ch_offset
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8  hmac_ap_update_2040_chan_info(
                mac_device_stru             *pst_mac_device,
                mac_vap_stru                *pst_mac_vap,
                oal_uint8                   *puc_payload,
                oal_uint16                   us_payload_len,
                oal_uint8                    uc_pri_chan_idx,
                mac_sec_ch_off_enum_uint8    en_sec_ch_offset)
{
    wlan_channel_band_enum_uint8    en_band = pst_mac_vap->st_channel.en_band;
    mac_ap_ch_info_stru            *pst_ap_ch_list = pst_mac_device->st_ap_channel_list;
    oal_bool_enum_uint8             en_status_change = OAL_FALSE;
    oal_uint8                       uc_sec_ch_idx_offset = mac_get_sec_ch_idx_offset(en_band);
    oal_uint8                       uc_sec_chan_idx = 0;
    oal_uint32                      ul_ret;

    if (OAL_TRUE == hmac_ap_is_40MHz_intol_bit_set(puc_payload, us_payload_len))
    {
        pst_mac_device->en_40MHz_intol_bit_recd = OAL_TRUE;
    }

    if (MAC_CH_TYPE_PRIMARY != pst_ap_ch_list[uc_pri_chan_idx].en_ch_type)
    {
        pst_ap_ch_list[uc_pri_chan_idx].en_ch_type = MAC_CH_TYPE_PRIMARY;
        en_status_change = OAL_TRUE;
    }

    if (MAC_SCN != en_sec_ch_offset)
    {
        if (MAC_SCA == en_sec_ch_offset)
        {
            uc_sec_chan_idx = uc_pri_chan_idx + uc_sec_ch_idx_offset;
        }
        else if (MAC_SCB == en_sec_ch_offset)
        {
            uc_sec_chan_idx = uc_pri_chan_idx - uc_sec_ch_idx_offset;
        }

        ul_ret =  mac_is_channel_idx_valid(en_band, uc_sec_chan_idx);
        if (OAL_SUCC != ul_ret)
        {
            return en_status_change;
        }

        if (uc_sec_chan_idx >= MAC_MAX_SUPP_CHANNEL)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040,
                             "{hmac_ap_update_2040_chan_info::invalid uc_sec_chan_idx[%d].}", uc_sec_chan_idx);
            return en_status_change;
        }

        if (MAC_CH_TYPE_PRIMARY != pst_ap_ch_list[uc_sec_chan_idx].en_ch_type)
        {
            if (MAC_CH_TYPE_SECONDARY != pst_ap_ch_list[uc_sec_chan_idx].en_ch_type)
            {
                pst_ap_ch_list[uc_sec_chan_idx].en_ch_type = MAC_CH_TYPE_SECONDARY;
                en_status_change = OAL_TRUE;
            }
        }
    }

    return en_status_change;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_process_obss_40mhz_intol
 ��������  : ����obss beacon/probe response֡�е�"40"
 �������  : pst_hmac_vap  : HMAC VAPָ��
             puc_payload   : beacon/probe response֡��ָ�� (������phy head��mac head)
             ul_payload_len: beacon/probe response֡�峤��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ap_process_obss_40mhz_intol(hmac_vap_stru *pst_hmac_vap, oal_uint8 *puc_payload, oal_uint16 us_payload_len)
{
    mac_device_stru   *pst_mac_device;

    /* ��HTվ�㲻֧��OBSS Beacon/Probe Response֡�Ĵ��� */
    if ((OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(&(pst_hmac_vap->st_vap_base_info))))
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                      "{hmac_ap_process_obss_40mhz_intol::HT not support.}");
        return;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                      "{hmac_ap_process_obss_40mhz_intol::pst_mac_device null.}");
        return;
    }

    if (OAL_TRUE == hmac_ap_is_40MHz_intol_bit_set(puc_payload, us_payload_len))
    {
        hmac_chan_start_40M_recovery_timer(&pst_hmac_vap->st_vap_base_info);
        /* ��BSS��ǰ�����ŵ���ȴ���20MHz����AP��Ҫ�л���20MHz���� */
        if ((pst_hmac_vap->st_vap_base_info.st_channel.en_bandwidth > WLAN_BAND_WIDTH_20M) &&
            (WLAN_BW_SWITCH_DONE == pst_hmac_vap->st_vap_base_info.st_ch_switch_info.en_bw_switch_status))
        {
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                          "{hmac_ap_process_obss_40mhz_intol::40MHz Intolerant AP in neighbourhood.}");
            hmac_chan_multi_switch_to_20MHz_ap(pst_hmac_vap);
        }
        else
        {
            pst_mac_device->en_40MHz_intol_bit_recd = OAL_TRUE;
        }
    }
}

#endif

/*****************************************************************************
 �� �� ��  : hmac_ap_up_rx_obss_beacon
 ��������  : ����obss����beacon֡/probe response֡
 �������  : pst_hmac_vap: MAC VAP�ṹ��ָ��
             pst_netbuf  : ����overlapping BBS֡��netbuf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��19��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ap_up_rx_obss_beacon(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf)
{
    dmac_rx_ctl_stru         *pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    oal_uint8                *puc_payload;
    oal_uint16                us_payload_len;

    /* ��ȡ֡�峤�� */
    us_payload_len = pst_rx_ctrl->st_rx_info.us_frame_len - pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* ��ȡ֡��ָ�� */
    puc_payload = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /*����ERP���*/
    if (WLAN_BAND_2G == pst_hmac_vap->st_vap_base_info.st_channel.en_band)
    {
        hmac_ap_process_obss_erp_ie(pst_hmac_vap, puc_payload, us_payload_len);
    }

    /*����HT operation���*/
    hmac_ap_process_obss_ht_operation_ie(pst_hmac_vap, puc_payload, us_payload_len);

    /*����AP�б������mib��*/
    hmac_protection_update_mib_ap(&(pst_hmac_vap->st_vap_base_info));

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    if ((OAL_TRUE     == mac_mib_get_FortyMHzOperationImplemented(&(pst_hmac_vap->st_vap_base_info))) &&
        (WLAN_BAND_2G == pst_hmac_vap->st_vap_base_info.st_channel.en_band))
    {
        hmac_ap_process_obss_40mhz_intol(pst_hmac_vap, puc_payload, us_payload_len);
    }
#endif
}










#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 �� �� ��  : hmac_ap_up_rx_smps_frame
 ��������  : AP��UP״̬�´���"SMPS"֡
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ��
             pst_netbuf  : "SMPS֡"���ڵ�netbuf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ap_up_rx_smps_frame(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf)
{
    mac_user_stru         *pst_mac_user;
    dmac_rx_ctl_stru      *pst_rx_ctrl;
    oal_uint8              auc_sta_addr[WLAN_MAC_ADDR_LEN];
    oal_uint8             *puc_data;
    oal_uint32             ul_ret;
    oal_uint8              uc_smps;
    wlan_mib_mimo_power_save_enum_uint8     en_user_smps_mode;

    if (OAL_FALSE == mac_mib_get_HighThroughputOptionImplemented(&(pst_hmac_vap->st_vap_base_info)))
    {
        return;
    }

    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    mac_get_address2((oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr, auc_sta_addr);

    pst_mac_user = mac_vap_get_user_by_addr(&(pst_hmac_vap->st_vap_base_info), auc_sta_addr);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SMPS, "{hmac_ap_up_rx_smps_frame::pst_mac_user null.}");
        return;
    }

    /* ��ȡ֡��ָ�� */
    puc_data = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* ����STA��sm_power_save field */
    if (0 == (puc_data[MAC_ACTION_OFFSET_ACTION + 1] & BIT0))
    {
        OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SMPS, "{hmac_ap_up_rx_smps_frame::user smps mode change.}");
        /* ���SMPS disable,������ΪMIMO POWER SAVE */
        if (WLAN_MIB_MIMO_POWER_SAVE_MIMO != pst_mac_user->st_ht_hdl.bit_sm_power_save)
        {
            mac_user_set_sm_power_save(pst_mac_user, WLAN_MIB_MIMO_POWER_SAVE_MIMO);
            hmac_smps_update_status((&pst_hmac_vap->st_vap_base_info), pst_mac_user, OAL_TRUE);
        }
    }
    else
    {
        /* ���SMPS enable,������Ϊ��Ӧģʽ */
        uc_smps = ((puc_data[MAC_ACTION_OFFSET_ACTION + 1] & BIT1) >> 1);
        en_user_smps_mode = (wlan_mib_mimo_power_save_enum_uint8)pst_mac_user->st_ht_hdl.bit_sm_power_save;
        if (WLAN_MIB_MIMO_POWER_SAVE_MIMO == en_user_smps_mode)
        {
            hmac_smps_update_status((&pst_hmac_vap->st_vap_base_info), pst_mac_user, OAL_FALSE);
        }

        if (0 == uc_smps)
        {
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SMPS, "{hmac_ap_up_rx_smps_frame::user smps mode change.}");
            mac_user_set_sm_power_save(pst_mac_user, WLAN_MIB_MIMO_POWER_SAVE_STATIC);
        }
        else
        {
            OAM_INFO_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SMPS, "{hmac_ap_up_rx_smps_frame::user smps mode change.}");
            mac_user_set_sm_power_save(pst_mac_user, WLAN_MIB_MIMO_POWER_SAVE_DYNAMIC);
        }
    }
    ul_ret = hmac_config_user_rate_info_syn(&(pst_hmac_vap->st_vap_base_info), pst_mac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SMPS,
                       "{hmac_ap_up_rx_smps_frame::hmac_config_user_rate_info_syn failed[%d].}", ul_ret);
    }

}
#endif

/*****************************************************************************
 �� �� ��  : hmac_ap_up_rx_action
 ��������  : AP��UP״̬�µĽ���ACTION֡����
 �������  : pst_hmac_vap: HMAC VAPָ��
             pst_netbuf  : ����֡���ڵ�sk_buff
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ap_up_rx_action(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf, oal_bool_enum_uint8 en_is_protected)
{
    dmac_rx_ctl_stru               *pst_rx_ctrl;
    oal_uint8                      *puc_data;
    mac_ieee80211_frame_stru       *pst_frame_hdr;          /* ����mac֡��ָ�� */
    hmac_user_stru                 *pst_hmac_user;

    pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* ��ȡ֡ͷ��Ϣ */
    pst_frame_hdr = (mac_ieee80211_frame_stru *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr;

    /* ��ȡ���Ͷ˵��û�ָ�� */
    pst_hmac_user = mac_vap_get_hmac_user_by_addr(&pst_hmac_vap->st_vap_base_info, pst_frame_hdr->auc_address2);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_ap_up_rx_action::mac_vap_find_user_by_macaddr failed.}");
        return;
    }

    /* ��ȡ֡��ָ�� */
    puc_data = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* Category */
    switch (puc_data[MAC_ACTION_OFFSET_CATEGORY])
    {
        case MAC_ACTION_CATEGORY_BA:
        {
            switch(puc_data[MAC_ACTION_OFFSET_ACTION])
            {
                case MAC_BA_ACTION_ADDBA_REQ:
                    hmac_mgmt_rx_addba_req(pst_hmac_vap, pst_hmac_user, puc_data);
                    break;

                case MAC_BA_ACTION_ADDBA_RSP:
                    hmac_mgmt_rx_addba_rsp(pst_hmac_vap, pst_hmac_user, puc_data);
                    break;

                case MAC_BA_ACTION_DELBA:
                    hmac_mgmt_rx_delba(pst_hmac_vap, pst_hmac_user, puc_data);
                    break;

                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_PUBLIC:
        {
            /* Action */
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
            #ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
                case MAC_PUB_COEXT_MGMT:
                    hmac_ap_up_rx_2040_coext(pst_hmac_vap, pst_netbuf);
                    break;
            #endif  /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */
			    case MAC_PUB_VENDOR_SPECIFIC:
			    {
            #ifdef _PRE_WLAN_FEATURE_P2P
                    /*����OUI-OUI typeֵΪ 50 6F 9A - 09 (WFA P2P v1.0)  */
                    /* ����hmac_rx_mgmt_send_to_host�ӿ��ϱ� */
                    if (OAL_TRUE == mac_ie_check_p2p_action(puc_data + MAC_ACTION_OFFSET_ACTION))
                    {
                       hmac_rx_mgmt_send_to_host(pst_hmac_vap, pst_netbuf);
                    }
            #endif  /* _PRE_WLAN_FEATURE_P2P */
                    break;
                }
                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_HT:
        {
            /* Action */
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
            #ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
                case MAC_HT_ACTION_NOTIFY_CHANNEL_WIDTH:
                    hmac_rx_notify_channel_width(&(pst_hmac_vap->st_vap_base_info), pst_netbuf);
                    break;
            #endif
            #ifdef _PRE_WLAN_FEATURE_SMPS
                case MAC_HT_ACTION_SMPS:
                    hmac_ap_up_rx_smps_frame(pst_hmac_vap, pst_netbuf);
                    break;
            #endif
                case MAC_HT_ACTION_BUTT:
                default:
                    break;
            }
        }
        break;
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
        case MAC_ACTION_CATEGORY_SA_QUERY:
        {
            /* Action */
            switch (puc_data[MAC_ACTION_OFFSET_ACTION])
            {
                case MAC_SA_QUERY_ACTION_REQUEST:
                    hmac_rx_sa_query_req(pst_hmac_vap, pst_netbuf, en_is_protected);
                    break;
                case MAC_SA_QUERY_ACTION_RESPONSE:
                    hmac_rx_sa_query_rsp(pst_hmac_vap, pst_netbuf, en_is_protected);
                    break;
                default:
                    break;
            }
        }
        break;
#endif
        case MAC_ACTION_CATEGORY_VHT:
        {
            switch(puc_data[MAC_ACTION_OFFSET_ACTION])
            {
            #ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
                case MAC_VHT_ACTION_OPREATE_MODE_NOTIFY:
                    hmac_mgmt_rx_opmode_notify_frame(pst_hmac_vap, pst_netbuf);
                    break;
            #endif
                case MAC_VHT_ACTION_BUTT:
                default:
                    break;
            }
        }
        break;

        case MAC_ACTION_CATEGORY_VENDOR:
        {
    #ifdef _PRE_WLAN_FEATURE_P2P
        /*����OUI-OUI typeֵΪ 50 6F 9A - 09 (WFA P2P v1.0)  */
        /* ����hmac_rx_mgmt_send_to_host�ӿ��ϱ� */
            if (OAL_TRUE == mac_ie_check_p2p_action(puc_data + MAC_ACTION_OFFSET_CATEGORY))
            {
               hmac_rx_mgmt_send_to_host(pst_hmac_vap, pst_netbuf);
            }
    #endif
        }
        break;

#ifdef _PRE_WLAN_FEATURE_WMMAC
        case MAC_ACTION_CATEGORY_WMMAC_QOS:
        {
            if (OAL_TRUE == g_en_wmmac_switch)
            {
                switch(puc_data[MAC_ACTION_OFFSET_ACTION])
                {
                    case MAC_WMMAC_ACTION_ADDTS_REQ:
                        hmac_mgmt_rx_addts_req_frame(pst_hmac_vap, pst_netbuf);
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
}

/*****************************************************************************
 �� �� ��  : hmac_ap_up_rx_probe_req
 ��������  : AP��UP״̬�µĽ���WPS probe req֡����
 �������  : pst_hmac_vap: HMAC VAPָ��
             pst_netbuf  : ����֡���ڵ�sk_buff
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��17��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ap_up_rx_probe_req(hmac_vap_stru *pst_hmac_vap, oal_netbuf_stru *pst_netbuf)
{
    dmac_rx_ctl_stru           *pst_rx_ctrl;
    mac_rx_ctl_stru            *pst_rx_info;
    enum ieee80211_band         en_band;
    oal_int                     l_freq;

    pst_rx_ctrl     = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    pst_rx_info     = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));

    /* ��ȡAP ��ǰ�ŵ� */
    if (WLAN_BAND_2G == pst_hmac_vap->st_vap_base_info.st_channel.en_band)
    {
        en_band = IEEE80211_BAND_2GHZ;
    }
    else if(WLAN_BAND_5G == pst_hmac_vap->st_vap_base_info.st_channel.en_band)
    {
        en_band = IEEE80211_BAND_5GHZ;
    }
    else
    {
        en_band = IEEE80211_NUM_BANDS;
    }
    l_freq = oal_ieee80211_channel_to_frequency(pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number,
                                                en_band);

    /* �ϱ����յ���probe req ����֡ */
    hmac_send_mgmt_to_host(pst_hmac_vap, pst_netbuf, pst_rx_info->us_frame_len, l_freq);
}

/*****************************************************************************
 �� �� ��  : hmac_ap_up_rx_mgmt
 ��������  : AP��UP״̬�µĽ��չ���֡����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_ap_up_rx_mgmt(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    dmac_wlan_crx_event_stru   *pst_mgmt_rx_event;
    dmac_rx_ctl_stru           *pst_rx_ctrl;
    mac_rx_ctl_stru            *pst_rx_info;
    oal_uint8                  *puc_mac_hdr;
    oal_uint8                  *puc_payload;
    oal_uint32                  ul_msg_len;         /* ��Ϣ�ܳ���,������FCS */
    oal_uint32                  ul_mac_hdr_len;     /* MACͷ���� */
    oal_uint8                   uc_mgmt_frm_type;
    oal_bool_enum_uint8         en_is_protected = OAL_FALSE;
#ifdef _PRE_WLAN_FEATURE_HILINK
    oal_uint8                  *puc_user_addr   = OAL_PTR_NULL;
    hmac_fbt_mgmt_stru         *pst_fbt_mgmt    = OAL_PTR_NULL;
    hmac_fbt_disable_user_info_stru *pst_dis_user = OAL_PTR_NULL;
    oal_uint8                   uc_tmp_idx;
#endif  /* _PRE_WLAN_FEATURE_HILINK */

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
    oal_uint8                  *puc_sa;
    oal_bool_enum_uint8         en_blacklist_result = OAL_FALSE;
#endif

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == p_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_ap_up_rx_mgmt::param null, %d %d.}", pst_hmac_vap, p_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mgmt_rx_event   = (dmac_wlan_crx_event_stru *)p_param;
    pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_mgmt_rx_event->pst_netbuf);
    pst_rx_info         = (mac_rx_ctl_stru *)(&(pst_rx_ctrl->st_rx_info));
    puc_mac_hdr         = (oal_uint8 *)(pst_rx_info->pul_mac_hdr_start_addr);
    ul_mac_hdr_len      = pst_rx_info->uc_mac_header_len;                     /* MACͷ���� */
    puc_payload         = (oal_uint8 *)(puc_mac_hdr) + ul_mac_hdr_len;
    ul_msg_len          = pst_rx_info->us_frame_len;                          /* ��Ϣ�ܳ���,������FCS */
    //en_is_protected     = (pst_rx_ctrl->st_rx_status.bit_cipher_protocol_type == hal_cipher_suite_to_ctype(WLAN_80211_CIPHER_SUITE_CCMP)) ? OAL_TRUE : OAL_FALSE;
    en_is_protected     = (oal_uint8)mac_get_protectedframe(puc_mac_hdr);

    /*Bar frame proc here*/
    if (WLAN_FC0_TYPE_CTL == mac_get_frame_type(puc_mac_hdr))
    {
        uc_mgmt_frm_type = mac_get_frame_sub_type(puc_mac_hdr);
        if (WLAN_BLOCKACK_REQ == (uc_mgmt_frm_type >> 4))
        {
            hmac_up_rx_bar(pst_hmac_vap, pst_rx_ctrl, pst_mgmt_rx_event->pst_netbuf);
        }
    }

    /* AP��UP״̬�� ���յ��ĸ��ֹ���֡���� */
    uc_mgmt_frm_type = mac_get_frame_sub_type(puc_mac_hdr);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if(OAL_TRUE == g_ul_print_wakeup_mgmt)
    {
        g_ul_print_wakeup_mgmt = OAL_FALSE;
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_ap_up_rx_mgmt::wakeup mgmt type[0x%x]}",uc_mgmt_frm_type);
    }
#endif
#ifdef _PRE_WLAN_FEATURE_HILINK
    pst_fbt_mgmt = &(pst_hmac_vap->st_fbt_mgmt);

    /* �ж�����Ϊ����֡ */
    if (WLAN_FC0_TYPE_MGT == mac_get_frame_type(puc_mac_hdr))
    {
        /* ����user�ڽ�ֹ�����б��У�ֱ�ӷ��� */
        mac_rx_get_sa((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_user_addr);

        for (uc_tmp_idx = 0; uc_tmp_idx < pst_fbt_mgmt->uc_disabled_user_cnt; uc_tmp_idx++)
        {
            pst_dis_user = &(pst_fbt_mgmt->ast_fbt_disable_connect_user_list[uc_tmp_idx]);
            if (0 == oal_memcmp(pst_dis_user->auc_user_mac_addr, puc_user_addr, WLAN_MAC_ADDR_LEN))
            {
                return OAL_SUCC;
            }
        }
    }
#endif  /* _PRE_WLAN_FEATURE_HILINK */

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
    mac_rx_get_sa((mac_ieee80211_frame_stru *)puc_mac_hdr, &puc_sa);

    /* �Զ������������� */
    if ((WLAN_FC0_SUBTYPE_ASSOC_REQ == uc_mgmt_frm_type)|| (WLAN_FC0_SUBTYPE_REASSOC_REQ == uc_mgmt_frm_type))
    {
        hmac_autoblacklist_filter(&pst_hmac_vap->st_vap_base_info, puc_sa);
    }

    /* ���������˼�� */
    en_blacklist_result = hmac_blacklist_filter(&pst_hmac_vap->st_vap_base_info, puc_sa);
    if (OAL_TRUE == en_blacklist_result)
    {
        return OAL_SUCC;
    }
#endif

    switch (uc_mgmt_frm_type)
    {
        case WLAN_FC0_SUBTYPE_BEACON:
        case WLAN_FC0_SUBTYPE_PROBE_RSP:
            hmac_ap_up_rx_obss_beacon(pst_hmac_vap, pst_mgmt_rx_event->pst_netbuf);
            break;

        case WLAN_FC0_SUBTYPE_AUTH:
            hmac_ap_rx_auth_req(pst_hmac_vap, pst_mgmt_rx_event->pst_netbuf, pst_mgmt_rx_event);
            break;

        case WLAN_FC0_SUBTYPE_DEAUTH:
            hmac_ap_rx_deauth_req(pst_hmac_vap, puc_mac_hdr, en_is_protected);
            break;

        case WLAN_FC0_SUBTYPE_ASSOC_REQ:
        case WLAN_FC0_SUBTYPE_REASSOC_REQ:
            hmac_ap_up_rx_asoc_req(pst_hmac_vap, uc_mgmt_frm_type, puc_mac_hdr, ul_mac_hdr_len, puc_payload, (ul_msg_len - ul_mac_hdr_len));
            break;

        case WLAN_FC0_SUBTYPE_DISASSOC:
            hmac_ap_up_rx_disasoc(pst_hmac_vap, puc_mac_hdr, ul_mac_hdr_len, puc_payload, (ul_msg_len - ul_mac_hdr_len), en_is_protected);
            break;

        case WLAN_FC0_SUBTYPE_ACTION:
            hmac_ap_up_rx_action(pst_hmac_vap, pst_mgmt_rx_event->pst_netbuf, en_is_protected);
            break;

        case WLAN_FC0_SUBTYPE_PROBE_REQ:
            hmac_ap_up_rx_probe_req(pst_hmac_vap, pst_mgmt_rx_event->pst_netbuf);
            break;

        default:
            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_store_network
 ��������  : �ɼ��յ���֡��������BSSID
 �������  : pst_mac_device: MAC DEVICE�ṹ��ָ��
             pst_netbuf    : �������ĵ�netbufָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ap_store_network(mac_device_stru *pst_mac_device, oal_netbuf_stru *pst_netbuf)
{
    mac_bss_id_list_stru   *pst_bss_id_list = &pst_mac_device->st_bss_id_list;
    dmac_rx_ctl_stru       *pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    oal_uint8               auc_network_bssid[WLAN_MAC_ADDR_LEN] = {0};
    oal_bool_enum_uint8     en_already_present = OAL_FALSE;
    oal_uint8               uc_loop;

    /* ��ȡ֡���е�BSSID */
    mac_get_bssid((oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr, auc_network_bssid);

    /* ���Թ㲥BSSID */
    if (0 == oal_compare_mac_addr(BROADCAST_MACADDR, auc_network_bssid))
    {
        return;
    }

    /* �ж��Ƿ��Ѿ������˸�BSSID */
    for (uc_loop = 0; (uc_loop < pst_bss_id_list->us_num_networks) && (uc_loop < WLAN_MAX_SCAN_BSS_PER_CH); uc_loop++)
    {
        if (0 == oal_compare_mac_addr(pst_bss_id_list->auc_bssid_array[uc_loop], auc_network_bssid))
        {
            en_already_present = OAL_TRUE;
            break;
        }
    }

    /* ����һ���µ�BSS��֡�������BSSID */
    if ((OAL_FALSE == en_already_present) && (pst_bss_id_list->us_num_networks < WLAN_MAX_SCAN_BSS_PER_CH))
    {
        oal_set_mac_addr((oal_uint8 *)pst_bss_id_list->auc_bssid_array[uc_loop], (oal_uint8 *)auc_network_bssid);
        pst_bss_id_list->us_num_networks++;
    }
}

/*****************************************************************************
 �� �� ��  : hmac_ap_get_chan_idx_of_network
 ��������  : ��ȡ��ǰBSS�������ŵ�����
 �������  : pst_mac_vap      : MAC VAP�ṹ��ָ��
             puc_payload      : ֡��
             us_payload_len   : ֡�峤��
             uc_curr_chan_idx : ��ǰ����ɨ����ŵ�����
 �������  : puc_chan_idx     : �ŵ�����
             pen_sec_ch_offset: ���ŵ�ƫ����
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_ap_get_chan_idx_of_network(
                mac_vap_stru                *pst_mac_vap,
                oal_uint8                   *puc_payload,
                oal_uint16                   us_payload_len,
                oal_uint8                    uc_curr_chan_idx,
                oal_uint8                   *puc_chan_idx,
                mac_sec_ch_off_enum_uint8   *pen_sec_ch_offset)
{
    wlan_channel_band_enum_uint8   en_band   = pst_mac_vap->st_channel.en_band;
    oal_uint8                      uc_ch_idx = 0xFF;
    oal_uint32                     ul_ret;
    oal_uint8                     *puc_ie           = OAL_PTR_NULL;

    if (us_payload_len <= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN))
    {
        *puc_chan_idx = uc_curr_chan_idx;

        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_ap_get_chan_idx_of_network::payload_len[%d]}", us_payload_len);
        return OAL_SUCC;
    }

    us_payload_len -= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);
    puc_payload    += (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);

    puc_ie = mac_find_ie(MAC_EID_HT_OPERATION, puc_payload, us_payload_len);
    if (OAL_PTR_NULL != puc_ie)
    {
        ul_ret = mac_get_channel_idx_from_num(en_band, puc_ie[MAC_IE_HDR_LEN], &uc_ch_idx);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                             "{hmac_ap_get_chan_idx_of_network::ht operate get channel idx failed(band [%d], channel[%d])!}",
                             en_band, puc_ie[MAC_IE_HDR_LEN]);
            return ul_ret;
        }

        ul_ret =  mac_is_channel_idx_valid(en_band, uc_ch_idx);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                             "{hmac_ap_get_chan_idx_of_network::channel_idx_valid failed(band [%d], channel[%d], idx[%d])!}",
                             en_band, puc_ie[MAC_IE_HDR_LEN], uc_ch_idx);
            return ul_ret;
        }

        *puc_chan_idx = uc_ch_idx;
        *pen_sec_ch_offset = puc_ie[MAC_IE_HDR_LEN + 1] & 0x03;

        return OAL_SUCC;
    }

    if (WLAN_BAND_2G == en_band)
    {
        puc_ie = mac_find_ie(MAC_EID_DSPARMS, puc_payload, us_payload_len);
        if (OAL_PTR_NULL != puc_ie)
        {
            ul_ret = mac_get_channel_idx_from_num(en_band, puc_ie[MAC_IE_HDR_LEN], &uc_ch_idx);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                                 "{hmac_ap_get_chan_idx_of_network::ht operate get channel idx failed(band [%d], channel[%d])!}",
                                 en_band, puc_ie[MAC_IE_HDR_LEN]);
                return ul_ret;
            }

            ul_ret =  mac_is_channel_idx_valid(en_band, uc_ch_idx);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
                                 "{hmac_ap_get_chan_idx_of_network::channel_idx_valid failed(2.4G, channel[%d], idx[%d])!}",
                                 puc_ie[MAC_IE_HDR_LEN], uc_ch_idx);
                return ul_ret;
            }

            *puc_chan_idx = uc_ch_idx;

            return OAL_SUCC;
        }
    }

    *puc_chan_idx = uc_curr_chan_idx;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_wait_start_rx_obss_beacon
 ��������  : AP��WAIT START״̬�£�����obss����Beacon֡/Probe Response֡
 �������  : pst_mac_device: MAC DEVICE�ṹ��ָ��
             pst_mac_vap   : MAC VAP�ṹ��ָ��
             pst_netbuf    : ����overlapping BBS֡��netbuf
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_ap_wait_start_rx_obss_beacon(
                mac_device_stru   *pst_mac_device,
                mac_vap_stru      *pst_mac_vap,
                oal_netbuf_stru   *pst_netbuf)
{
    dmac_rx_ctl_stru           *pst_rx_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);
    oal_uint8                  *puc_payload;
    oal_uint16                  us_payload_len;
    oal_uint8                   uc_chan_idx = 0xFF;
    oal_uint8                   uc_curr_chan_idx = pst_mac_device->uc_ap_chan_idx;
    mac_sec_ch_off_enum_uint8   en_sec_ch_offset = MAC_SCN;
    oal_uint32                  ul_ret;

    /* ��ȡ֡�峤�� */
    us_payload_len = pst_rx_ctrl->st_rx_info.us_frame_len - pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* ��ȡ֡��ָ�� */
    puc_payload = (oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr + pst_rx_ctrl->st_rx_info.uc_mac_header_len;

    /* ��֡���л�ȡ�ŵ������ʹ��ŵ�ƫ���� */
    ul_ret = hmac_ap_get_chan_idx_of_network(pst_mac_vap, puc_payload, us_payload_len, uc_curr_chan_idx,
                                             &uc_chan_idx, &en_sec_ch_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                                 "{hmac_ap_wait_start_rx_obss_beacon::hmac_ap_get_chan_idx_of_network failed[%d].}", ul_ret);
        return;
    }

    if (uc_chan_idx != uc_curr_chan_idx)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                                 "{hmac_ap_wait_start_rx_obss_beacon::The channel of this BSS not matched to current channel.}");
        return;
    }

    hmac_ap_store_network(pst_mac_device, pst_netbuf);

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    hmac_ap_update_2040_chan_info(pst_mac_device, pst_mac_vap, puc_payload, us_payload_len, uc_chan_idx, en_sec_ch_offset);
#endif
}

/*****************************************************************************
 �� �� ��  : hmac_ap_wait_start_rx_mgmt
 ��������  : AP��WAIT START״̬�½��չ���֡����
 �������  : pst_hmac_vap: HMAC VAP�ṹ��ָ��
             p_param     :
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_ap_wait_start_rx_mgmt(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    mac_device_stru            *pst_mac_device;
    dmac_wlan_crx_event_stru   *pst_mgmt_rx_event;
    dmac_rx_ctl_stru           *pst_rx_ctrl;
    oal_uint8                   uc_mgmt_frm_type;

    if ((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == p_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_ap_wait_start_rx_mgmt::param null, %d %d.}",pst_hmac_vap, p_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{hmac_ap_wait_start_rx_mgmt::pst_mac_device null.}");
        return OAL_FALSE;
    }

    pst_mgmt_rx_event   = (dmac_wlan_crx_event_stru *)p_param;
    pst_rx_ctrl         = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_mgmt_rx_event->pst_netbuf);

    /* �ɼ��յ����κ�֡��������BSSID */
    /* hmac_ap_store_network(pst_mac_device, pst_mgmt_rx_event->pst_netbuf); */

    /* ��ȡ����֡���� */
    uc_mgmt_frm_type = mac_get_frame_sub_type((oal_uint8 *)pst_rx_ctrl->st_rx_info.pul_mac_hdr_start_addr);

    /* AP��WAIT START״̬�� ���յ��ĸ��ֹ���֡���� */
    switch (uc_mgmt_frm_type)
    {
        case WLAN_FC0_SUBTYPE_BEACON:
        case WLAN_FC0_SUBTYPE_PROBE_RSP:
            hmac_ap_wait_start_rx_obss_beacon(pst_mac_device, &(pst_hmac_vap->st_vap_base_info), pst_mgmt_rx_event->pst_netbuf);

            break;

        default:
            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_mgmt_timeout_fn
 ��������  : ����֡��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_mgmt_timeout_ap(oal_void *p_param)
{
    hmac_vap_stru                *pst_hmac_vap;
    hmac_user_stru               *pst_hmac_user;
    oal_uint32                    ul_ret;

    pst_hmac_user = (hmac_user_stru *)p_param;
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_AUTH, "{hmac_mgmt_timeout_ap::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap  = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_hmac_user->st_user_base_info.uc_vap_id);

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_mgmt_timeout_ap::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_mgmt_timeout_ap::Wait AUTH timeout!! After %d ms.}", WLAN_AUTH_TIMEOUT);

    /* ����ȥ����֡��Ϣ��STA */
    hmac_mgmt_send_deauth_frame(&pst_hmac_vap->st_vap_base_info, pst_hmac_user->st_user_base_info.auc_user_mac_addr, MAC_AUTH_NOT_VALID, OAL_FALSE);

    ul_ret = hmac_user_del(&pst_hmac_vap->st_vap_base_info, pst_hmac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_AUTH, "{hmac_mgmt_timeout_ap::hmac_user_del failed[%d].}", ul_ret);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_wait_start_misc
 ��������  : AP��WAIT START״̬�µ�misc�¼�����
 �������  : pst_hmac_vap: HMAC VAPָ��
             p_param     : hmac_misc_input_stru����ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_ap_wait_start_misc(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    hmac_misc_input_stru   *pst_misc_input;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == p_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_ap_wait_start_misc::param null, %d %d.}", pst_hmac_vap, p_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_misc_input = (hmac_misc_input_stru *)p_param;

    switch (pst_misc_input->en_type)
    {
        case HMAC_MISC_RADAR:
    #ifdef _PRE_WLAN_FEATURE_DFS
            hmac_dfs_ap_wait_start_radar_handler(pst_hmac_vap);
    #endif
            break;

        default:
            break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_ap_up_misc
 ��������  : AP��UP״̬�µ�misc�¼�����
 �������  : pst_hmac_vap: HMAC VAPָ��
             p_param     : hmac_misc_input_stru����ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_ap_up_misc(hmac_vap_stru *pst_hmac_vap, oal_void *p_param)
{
    hmac_misc_input_stru   *pst_misc_input;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == p_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_RX, "{hmac_ap_up_misc::param null, %d %d.}", pst_hmac_vap, p_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_misc_input = (hmac_misc_input_stru *)p_param;

    switch (pst_misc_input->en_type)
    {

        case HMAC_MISC_RADAR:
    #ifdef _PRE_WLAN_FEATURE_DFS
            hmac_dfs_ap_up_radar_handler(pst_hmac_vap);
    #endif
            break;

        default:
            break;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_ap_clean_bss
 ��������  : ���BSS�����й����û�
 �������  : hmac_vap_stru *pst_hmac_vap,

 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��24��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32 hmac_ap_clean_bss(hmac_vap_stru *pst_hmac_vap)
{
    oal_dlist_head_stru                 *pst_user_list_head;
    oal_dlist_head_stru                 *pst_entry;
    mac_vap_stru                        *pst_mac_vap;
    mac_user_stru                       *pst_user_tmp;
    hmac_user_stru                      *pst_hmac_user_tmp;
    oal_bool_enum_uint8                  en_is_protected;

    if (!pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{hmac_ap_clean_bss::hmac vap is null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

     /* ɾ��vap�������ѹ����û�����֪ͨ�ں� */
    pst_user_list_head = &pst_hmac_vap->st_vap_base_info.st_mac_user_list_head;
    pst_mac_vap = &pst_hmac_vap->st_vap_base_info;

    for (pst_entry = pst_user_list_head->pst_next; pst_entry != pst_user_list_head;)
    {
        pst_user_tmp      = OAL_DLIST_GET_ENTRY(pst_entry, mac_user_stru, st_user_dlist);
        pst_hmac_user_tmp = mac_res_get_hmac_user(pst_user_tmp->us_assoc_id);

        if (!pst_hmac_user_tmp)
        {
            continue;
        }

        /* ָ��˫��������һ�� */
        pst_entry = pst_entry->pst_next;

        /* ����֡�����Ƿ���*/
        en_is_protected = pst_user_tmp->st_cap_info.bit_pmf_active;

        /* ��ȥ����֡ */
        hmac_mgmt_send_disassoc_frame(pst_mac_vap, pst_user_tmp->auc_user_mac_addr, MAC_DISAS_LV_SS, en_is_protected);

        /* ֪ͨ�ں� */
        hmac_handle_disconnect_rsp_ap(pst_hmac_vap, pst_hmac_user_tmp);

        /* ɾ���û� */
        hmac_user_del(pst_mac_vap, pst_hmac_user_tmp);
    }

    return OAL_SUCC;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

