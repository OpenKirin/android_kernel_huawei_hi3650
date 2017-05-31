/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_uapsd.c
  �� �� ��   : ����
  ��    ��   : zourong
  ��������   : 2013��9��18��
  ����޸�   :
  ��������   : UAPSD hmac�㴦��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��9��18��
    ��    ��   : zourong
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
#include "mac_vap.h"
#include "mac_frame.h"
#include "hmac_mgmt_ap.h"
#include "hmac_encap_frame_ap.h"
#include "hmac_mgmt_bss_comm.h"
#include "hmac_rx_data.h"
#include "hmac_uapsd.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_UAPSD_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : hmac_uapsd_update_user_para
 ��������  : uapsd������������е�WMM IE
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_uapsd_update_user_para (oal_uint8  *puc_mac_hdr,oal_uint8  uc_sub_type,oal_uint32 ul_msg_len,
                                            hmac_user_stru *pst_hmac_user)
{

#ifdef _PRE_WLAN_FEATURE_UAPSD
    oal_uint32          ul_idx;
    oal_uint32          ul_ret;
    oal_uint8           uc_max_sp;
    oal_uint8           uc_found_wmm = OAL_FALSE;
    oal_uint8           uc_en = OAL_FALSE;
    oal_uint8           uc_uapsd_flag = 0;
    mac_user_uapsd_status_stru   st_uapsd_status;
    mac_vap_stru       *pst_mac_vap;
    oal_uint16          us_len;
    oal_uint16          us_len_total;
    oal_uint8          *puc_param;
    oal_uint8          *puc_wmm_ie = OAL_PTR_NULL;

    ul_idx = MAC_CAP_INFO_LEN + MAC_LIS_INTERVAL_IE_LEN;
    if (WLAN_FC0_SUBTYPE_REASSOC_REQ == uc_sub_type)
    {
        ul_idx += WLAN_MAC_ADDR_LEN;
    }

    if (ul_idx < ul_msg_len)
    {
        puc_wmm_ie = mac_get_wmm_ie(puc_mac_hdr + ul_idx, (oal_uint16)(ul_msg_len - ul_idx));
        if (OAL_PTR_NULL != puc_wmm_ie)
        {
            uc_found_wmm = OAL_TRUE;
        }
    }

    /*������WMM IE,ֱ�ӷ���*/
    if ((OAL_FALSE == uc_found_wmm) || (OAL_PTR_NULL == puc_wmm_ie))
    {
        OAM_WARNING_LOG1(pst_hmac_user->st_user_base_info.uc_vap_id, OAM_SF_PWR, "Could not find WMM IE in assoc req,user_id[%d]\n", pst_hmac_user->st_user_base_info.us_assoc_id);
        return;
    }

    OAL_MEMZERO(&st_uapsd_status,  OAL_SIZEOF(mac_user_uapsd_status_stru));
    st_uapsd_status.uc_qos_info = puc_wmm_ie[HMAC_UAPSD_WME_LEN];

    /* 8ΪWMM IE���� */
    if (BIT0 == (puc_wmm_ie[HMAC_UAPSD_WME_LEN] & BIT0))
    {
        st_uapsd_status.uc_ac_trigger_ena[WLAN_WME_AC_VO] = 1;
        st_uapsd_status.uc_ac_delievy_ena[WLAN_WME_AC_VO] = 1;
        uc_en = OAL_TRUE;
    }

    if (BIT1 == (puc_wmm_ie[HMAC_UAPSD_WME_LEN] & BIT1))
    {
        st_uapsd_status.uc_ac_trigger_ena[WLAN_WME_AC_VI] = 1;
        st_uapsd_status.uc_ac_delievy_ena[WLAN_WME_AC_VI] = 1;
        uc_en = OAL_TRUE;
    }

    if (BIT2 == (puc_wmm_ie[HMAC_UAPSD_WME_LEN] & BIT2))
    {
        st_uapsd_status.uc_ac_trigger_ena[WLAN_WME_AC_BK] = 1;
        st_uapsd_status.uc_ac_delievy_ena[WLAN_WME_AC_BK] = 1;
        uc_en = OAL_TRUE;
    }

    if (BIT3 == (puc_wmm_ie[HMAC_UAPSD_WME_LEN] & BIT3))
    {
        st_uapsd_status.uc_ac_trigger_ena[WLAN_WME_AC_BE] = 1;
        st_uapsd_status.uc_ac_delievy_ena[WLAN_WME_AC_BE] = 1;
        uc_en = OAL_TRUE;
    }

    if(OAL_TRUE == uc_en)
    {
        uc_uapsd_flag |= MAC_USR_UAPSD_EN;
    }

    /* ����max SP���� */
    uc_max_sp = (puc_wmm_ie[HMAC_UAPSD_WME_LEN] >> 5) & 0x3;
    switch(uc_max_sp)
    {
       case 1:
        st_uapsd_status.uc_max_sp_len = 2;
        break;
       case 2:
        st_uapsd_status.uc_max_sp_len = 4;
        break;
       case 3:
        st_uapsd_status.uc_max_sp_len = 6;
        break;
       default:
        st_uapsd_status.uc_max_sp_len = HMAC_UAPSD_SEND_ALL;
        break;

    }
    /* Send uapsd_flag & uapsd_status syn to dmac */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_hmac_user->st_user_base_info.uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap)) {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{hmac_uapsd_update_user_para::get mac_vap [%d] null.}", pst_hmac_user->st_user_base_info.uc_vap_id);
        return;
    }
    us_len = OAL_SIZEOF(oal_uint16);
    us_len_total = OAL_SIZEOF(oal_uint16) + OAL_SIZEOF(oal_uint8) + OAL_SIZEOF(mac_user_uapsd_status_stru);
    puc_param = (oal_uint8 *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, us_len_total, OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_param)) {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_uapsd_update_user_para::puc_param null.}");
        return;
    }
    // uc_user_index
    oal_memcopy(puc_param, &pst_hmac_user->st_user_base_info.us_assoc_id, us_len);
    // uc_uapsd_flag
    oal_memcopy(puc_param + us_len, &uc_uapsd_flag, OAL_SIZEOF(oal_uint8));
    us_len += OAL_SIZEOF(oal_uint8);
    // st_uapsd_status
    oal_memcopy(puc_param + us_len, &st_uapsd_status, OAL_SIZEOF(mac_user_uapsd_status_stru));
    us_len += OAL_SIZEOF(mac_user_uapsd_status_stru);

    ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_UAPSD_UPDATE, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_uapsd_update_user_para::hmac_config_send_event fail.  erro code is %u}", ul_ret);
    }
    OAL_MEM_FREE(puc_param, OAL_TRUE);

#endif

    return ;

}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

