
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_user.c
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
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
#include "oam_ext_if.h"
#include "dmac_ext_if.h"
#include "hmac_user.h"
#include "hmac_main.h"
#include "hmac_tx_amsdu.h"
#include "hmac_protection.h"
#include "hmac_smps.h"
#include "hmac_ext_if.h"
#include "hmac_config.h"
#include "hmac_mgmt_ap.h"
#include "hmac_chan_mgmt.h"
#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
#include "hmac_proxy_arp.h"
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
#include "hmac_wapi.h"
#endif

#ifdef _PRE_WLAN_FEATURE_MCAST
#include "hmac_m2u.h"
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
#include "hmac_roam_main.h"
#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_SUPPORT_ACS
#include "hmac_acs.h"
#endif

#include "hmac_blockack.h"
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_USER_C
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : mac_res_get_hmac_user_init
 ��������  : ��ȡ��ӦHMAC USER�������ڴ�,��HMAC��ǿתΪ�Լ����ڴ����
 �������  : ��ӦHMAC USER�ڴ�����
 �������  : ��
 �� �� ֵ  : ��Ӧ�ڴ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��3��
    ��    ��   : lingxuemeng
    �޸�����   : �����ɺ���

*****************************************************************************/
hmac_user_stru*  mac_res_get_hmac_user_alloc(oal_uint16 us_idx)
{
    hmac_user_stru *pst_hmac_user;

    pst_hmac_user = (hmac_user_stru*)_mac_res_get_hmac_user(us_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{mac_res_get_hmac_user_init::pst_hmac_user null,user_idx=%d.}", us_idx);
        return OAL_PTR_NULL;
    }

    /* �ظ������쳣,����Ӱ��ҵ����ʱ��ӡerror���������� */
    if (MAC_USER_ALLOCED == pst_hmac_user->st_user_base_info.uc_is_user_alloced)
    {
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{mac_res_get_hmac_user_init::[E]user has been alloced,user_idx=%d.}", us_idx);
    }

    return pst_hmac_user;
}

/*****************************************************************************
 �� �� ��  : mac_res_get_hmac_user
 ��������  : ��ȡ��ӦHMAC USER�������ڴ�,��HMAC��ǿתΪ�Լ����ڴ����
 �������  : ��ӦHMAC USER�ڴ�����
 �������  : ��
 �� �� ֵ  : ��Ӧ�ڴ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��3��
    ��    ��   : lingxuemeng
    �޸�����   : �����ɺ���

*****************************************************************************/
hmac_user_stru*  mac_res_get_hmac_user(oal_uint16 us_idx)
{
    hmac_user_stru *pst_hmac_user;

    pst_hmac_user = (hmac_user_stru*)_mac_res_get_hmac_user(us_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        //OAM_ERROR_LOG1(0, OAM_SF_UM, "{mac_res_get_hmac_user::pst_hmac_user null,user_idx=%d.}", us_idx);
        return OAL_PTR_NULL;
    }

    /* �쳣: �û���Դ�ѱ��ͷ�, user idx0 Ϊ�鲥user */
    if ((MAC_USER_ALLOCED != pst_hmac_user->st_user_base_info.uc_is_user_alloced) && (0 != us_idx))
    {
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{mac_res_get_hmac_user::[E]user has been freed,user_idx=%d.}", us_idx);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        oal_mem_print_funcname(oal_get_func_return_address());
#endif
        //return OAL_PTR_NULL;
    }

    return pst_hmac_user;
}


/*****************************************************************************
 �� �� ��  : hmac_user_alloc
 ��������  : ����DMAC�û�ʵ��
 �������  : oal_mem_stru **ppst_mem_stru
 �������  : oal_mem_stru **ppst_mem_stru
 �� �� ֵ  : �ɹ���ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��11��
    ��    ��   : ������53369
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_user_alloc(oal_uint16 *pus_user_idx)
{
    hmac_user_stru *pst_hmac_user;
    oal_uint32      ul_rslt;
    oal_uint16      us_user_idx_temp;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pus_user_idx))
    {
        OAM_ERROR_LOG0(0, OAM_SF_UM, "{hmac_user_alloc::pus_user_idx null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����hmac user�ڴ� */
    /*lint -e413*/
    ul_rslt = mac_res_alloc_hmac_user(&us_user_idx_temp, OAL_OFFSET_OF(hmac_user_stru, st_user_base_info));
    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{hmac_user_alloc::mac_res_alloc_hmac_user failed[%d].}", ul_rslt);
        return ul_rslt;
    }
    /*lint +e413*/

    pst_hmac_user = mac_res_get_hmac_user_alloc(us_user_idx_temp);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        mac_res_free_mac_user(us_user_idx_temp);
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_alloc::pst_hmac_user null,user_idx=%d.}", us_user_idx_temp);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ʼ��0 */
    OAL_MEMZERO(pst_hmac_user, OAL_SIZEOF(hmac_user_stru));
    /* ���user��Դ�ѱ�alloc */
    pst_hmac_user->st_user_base_info.uc_is_user_alloced = MAC_USER_ALLOCED;

    *pus_user_idx = us_user_idx_temp;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_user_free
 ��������  : �ͷŶ�ӦHMAC USER���ڴ�
 �������  : ��ӦHMAC USER�ڴ�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��3��
    ��    ��   : lingxuemeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_user_free(oal_uint16 us_idx)
{
    hmac_user_stru *pst_hmac_user;
    oal_uint32      ul_ret;

    pst_hmac_user = mac_res_get_hmac_user(us_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_free::pst_hmac_user null,user_idx=%d.}", us_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ظ��ͷ��쳣, �����ͷŲ����� */
    if (MAC_USER_FREED == pst_hmac_user->st_user_base_info.uc_is_user_alloced)
    {
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{hmac_user_free::[E]user has been freed,user_idx=%d.}", us_idx);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        oal_mem_print_funcname(oal_get_func_return_address());
#endif
    }

    ul_ret = mac_res_free_mac_user(us_idx);
    if(OAL_SUCC == ul_ret)
    {
        /* ���alloc��־ */
        pst_hmac_user->st_user_base_info.uc_is_user_alloced = MAC_USER_FREED;
    }

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : hmac_user_init
 ��������  : ��ʼ��HMAC �û�
 �������  : hmac_user_stru *pst_hmac_user
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : ������53369
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_user_init(hmac_user_stru *pst_hmac_user)
{
    oal_uint8        uc_tid_loop;
    hmac_ba_tx_stru *pst_tx_ba;

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    oal_uint8        uc_ac_idx;
    oal_uint8        uc_data_idx;
#endif

    /* ��ʼ��tid��Ϣ */
    for (uc_tid_loop = 0; uc_tid_loop < WLAN_TID_MAX_NUM; uc_tid_loop++)
    {
        pst_hmac_user->ast_tid_info[uc_tid_loop].uc_tid_no      = (oal_uint8)uc_tid_loop;

        //pst_hmac_user->ast_tid_info[uc_tid_loop].pst_hmac_user  = (oal_void *)pst_hmac_user;
        pst_hmac_user->ast_tid_info[uc_tid_loop].us_hmac_user_idx = pst_hmac_user->st_user_base_info.us_assoc_id;

        /* ��ʼ��ba rx������� */
        pst_hmac_user->ast_tid_info[uc_tid_loop].pst_ba_rx_info = OAL_PTR_NULL;

        /* ��ʼ��ba tx������� */
        pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info.en_ba_status     = DMAC_BA_INIT;
        pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info.uc_addba_attemps = 0;
        pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info.uc_dialog_token  = 0;
        pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info.en_ba_switch     = OAL_TRUE;
        pst_hmac_user->auc_ba_flag[uc_tid_loop] = 0;

        /* addba req��ʱ�����������д */
        pst_tx_ba = &pst_hmac_user->ast_tid_info[uc_tid_loop].st_ba_tx_info;
        pst_tx_ba->st_alarm_data.pst_ba = (oal_void *)pst_tx_ba;
        pst_tx_ba->st_alarm_data.uc_tid = uc_tid_loop;
        pst_tx_ba->st_alarm_data.us_mac_user_idx = pst_hmac_user->st_user_base_info.us_assoc_id;
        pst_tx_ba->st_alarm_data.uc_vap_id = pst_hmac_user->st_user_base_info.uc_vap_id;

        /* ��ʼ���û���������֡���� */
        pst_hmac_user->puc_assoc_req_ie_buff = OAL_PTR_NULL;
        pst_hmac_user->ul_assoc_req_ie_len   = 0;

    }

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    for (uc_ac_idx = 0; uc_ac_idx < WLAN_WME_AC_BUTT; uc_ac_idx++)
    {
        for (uc_data_idx = 0; uc_data_idx < WLAN_TXRX_DATA_BUTT; uc_data_idx++)
        {
            pst_hmac_user->aaul_txrx_data_stat[uc_ac_idx][uc_data_idx] = 0;
        }
    }
#endif

    pst_hmac_user->pst_defrag_netbuf = OAL_PTR_NULL;
    pst_hmac_user->en_user_bw_limit  = OAL_FALSE;
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    pst_hmac_user->st_sa_query_info.ul_sa_query_count      = 0;
    pst_hmac_user->st_sa_query_info.ul_sa_query_start_time = 0;
#endif
    OAL_MEMZERO(&pst_hmac_user->st_defrag_timer, OAL_SIZEOF(frw_timeout_stru));
    pst_hmac_user->ul_rx_pkt_drop = 0;

#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
    /* ���usrͳ����Ϣ */
    oam_stats_clear_user_stat_info(pst_hmac_user->st_user_base_info.us_assoc_id);
#endif

    pst_hmac_user->ul_first_add_time = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_user_set_avail_num_space_stream
 ��������  : ��ȡ�û���VAP�������õĿռ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_user_set_avail_num_space_stream(mac_user_stru *pst_mac_user, wlan_nss_enum_uint8 en_vap_nss)
{
    mac_user_ht_hdl_stru         *pst_mac_ht_hdl;
    mac_vht_hdl_stru             *pst_mac_vht_hdl;
    mac_vap_stru                 *pst_mac_vap;
    oal_uint8                     uc_avail_num_spatial_stream = 0;
    oal_uint32                    ul_ret = OAL_SUCC;
    mac_user_nss_stru             st_user_nss;

     /* AP(STA)Ϊlegacy�豸��ֻ֧��1�����ߣ�����Ҫ���ж����߸��� */

    /* ��ȡHT��VHT�ṹ��ָ�� */
    pst_mac_ht_hdl  = &(pst_mac_user->st_ht_hdl);
    pst_mac_vht_hdl = &(pst_mac_user->st_vht_hdl);

    if (OAL_TRUE == pst_mac_vht_hdl->en_vht_capable)
    {
        if (3 != pst_mac_vht_hdl->st_rx_max_mcs_map.us_max_mcs_4ss)
        {
            uc_avail_num_spatial_stream = WLAN_FOUR_NSS;
        }
        else if (3 != pst_mac_vht_hdl->st_rx_max_mcs_map.us_max_mcs_3ss)
        {
            uc_avail_num_spatial_stream = WLAN_TRIPLE_NSS;
        }
        else if (3 != pst_mac_vht_hdl->st_rx_max_mcs_map.us_max_mcs_2ss)
        {
            uc_avail_num_spatial_stream = WLAN_DOUBLE_NSS;
        }
        else if (3 != pst_mac_vht_hdl->st_rx_max_mcs_map.us_max_mcs_1ss)
        {
            uc_avail_num_spatial_stream = WLAN_SINGLE_NSS;
        }
        else
        {
            MAC_WARNING_LOG(0, "mac_user_set_avail_num_space_stream: get vht nss error");
            OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{mac_user_set_avail_num_space_stream::invalid vht nss.}");

            ul_ret =  OAL_FAIL;
        }
    }
    else if (OAL_TRUE == pst_mac_ht_hdl->en_ht_capable)
    {
        if (pst_mac_ht_hdl->uc_rx_mcs_bitmask[3] > 0)
        {
            uc_avail_num_spatial_stream = WLAN_FOUR_NSS;
        }
        else if (pst_mac_ht_hdl->uc_rx_mcs_bitmask[2] > 0)
        {
            uc_avail_num_spatial_stream = WLAN_TRIPLE_NSS;
        }
        else if (pst_mac_ht_hdl->uc_rx_mcs_bitmask[1] > 0)
        {
            uc_avail_num_spatial_stream = WLAN_DOUBLE_NSS;
        }
        else if (pst_mac_ht_hdl->uc_rx_mcs_bitmask[0] > 0)
        {
            uc_avail_num_spatial_stream = WLAN_SINGLE_NSS;
        }
        else
        {
            MAC_WARNING_LOG(0, "mac_user_set_avail_num_space_stream: get ht nss error");
            OAM_WARNING_LOG0(pst_mac_user->uc_vap_id, OAM_SF_ANY, "{mac_user_set_avail_num_space_stream::invalid ht nss.}");

            ul_ret =  OAL_FAIL;
        }
    }
    else
    {
        uc_avail_num_spatial_stream = WLAN_SINGLE_NSS;
    }

    /* ��ֵ���û��ṹ����� */
    mac_user_set_num_spatial_stream(pst_mac_user, uc_avail_num_spatial_stream);
    mac_user_set_avail_num_spatial_stream(pst_mac_user, OAL_MIN(uc_avail_num_spatial_stream, en_vap_nss));

    /* �ռ�����Ϣͬ��dmac */
    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_user->uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG1(pst_mac_user->uc_vap_id, OAM_SF_CFG, "hmac_user_set_avail_num_space_stream::mac vap(idx=%d) is null!", pst_mac_user->uc_vap_id);
        return ul_ret;
    }
    st_user_nss.uc_avail_num_spatial_stream = pst_mac_user->uc_avail_num_spatial_stream;
    st_user_nss.uc_num_spatial_stream       = pst_mac_user->uc_num_spatial_stream;
    st_user_nss.us_user_idx = pst_mac_user->us_assoc_id;

    ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_NSS,
                                    OAL_SIZEOF(mac_user_nss_stru),
                                    (oal_uint8 *)(&st_user_nss));
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_user->uc_vap_id, OAM_SF_CFG, "{hmac_user_set_avail_num_space_stream::hmac_config_send_event failed[%d].}", ul_ret);
    }

    return ul_ret;
}

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
/*****************************************************************************
 �� �� ��  : hmac_stop_sa_query_timer
 ��������  : ɾ��sa query timer
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��27��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void hmac_stop_sa_query_timer(hmac_user_stru *pst_hmac_user)
{
    frw_timeout_stru    *pst_sa_query_interval_timer;

    pst_sa_query_interval_timer = &(pst_hmac_user->st_sa_query_info.st_sa_query_interval_timer);
    if (OAL_FALSE != pst_sa_query_interval_timer->en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(pst_sa_query_interval_timer);
    }

    /* ɾ��timers����δ洢�ռ� */
    if (OAL_PTR_NULL != pst_sa_query_interval_timer->p_timeout_arg)
    {
       OAL_MEM_FREE((oal_void *)pst_sa_query_interval_timer->p_timeout_arg, OAL_TRUE);
       pst_sa_query_interval_timer->p_timeout_arg = OAL_PTR_NULL;
    }
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_user_get_wapi_ptr
 ��������  : ��ȡ�û���wapi����ָ��
 �������  :
 �������  : oal_void
 �� �� ֵ  : ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_WAPI
hmac_wapi_stru * hmac_user_get_wapi_ptr(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_pairwise, oal_uint16 us_pairwise_idx)

{
    hmac_user_stru                  *pst_hmac_user;
    //oal_uint32                       ul_ret;
    oal_uint16                       us_user_index;

    if (OAL_TRUE == en_pairwise)
    {
        us_user_index = us_pairwise_idx;
    }
    else
    {
        us_user_index = pst_mac_vap->us_multi_user_idx;
    }

    //OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_user_get_wapi_ptr::en_pairwise == %u, usridx==%u.}", en_pairwise, us_user_index);
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_index);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_user_get_wapi_ptr::pst_hmac_user null.}");
        return OAL_PTR_NULL;
    }

    return &pst_hmac_user->st_wapi;
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_compability_ap_tpye_identify
 ��������  : ����������APʶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��7��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
mac_ap_type_enum_uint8 hmac_compability_ap_tpye_identify(oal_uint8 *puc_mac_addr)
{
    if(MAC_IS_GOLDEN_AP(puc_mac_addr))
    {
        return MAC_AP_TYPE_GOLDENAP;
    }
    return MAC_AP_TYPE_NORMAL;
}

/*****************************************************************************
 �� �� ��  : hmac_del_user
 ��������  : ɾ��user
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
oal_uint32  hmac_user_del(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user)
{
    oal_uint16                      us_user_index;
    frw_event_mem_stru             *pst_event_mem;
    frw_event_stru                 *pst_event;
    dmac_ctx_del_user_stru         *pst_del_user_payload;
    hmac_vap_stru                  *pst_hmac_vap;
    mac_device_stru                *pst_mac_device;
    mac_user_stru                  *pst_mac_user;
    oal_uint32                      ul_ret;
#ifdef _PRE_WLAN_FEATURE_WMMAC
    oal_uint8                       uc_ac_index = 0;
#endif
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_user_stru                 *pst_hmac_user_multi;
#endif
    mac_ap_type_enum_uint8          en_ap_type = MAC_AP_TYPE_BUTT;

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    oal_int8                        pc_param[16]    = {0};
    oal_int8                        pc_tmp[8]       = {0};
    oal_uint16                      us_len;
#endif

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_hmac_user)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_UM, "{hmac_user_del::param null,%d %d.}", pst_mac_vap, pst_hmac_user);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_user = (mac_user_stru*)(&pst_hmac_user->st_user_base_info);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_del::pst_mac_user param null,%d.}", pst_mac_user);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_del::del user[%d] start,is multi user[%d], user mac:XX:XX:XX:XX:%02X:%02X}",
                                pst_mac_user->us_assoc_id,
                                pst_mac_user->en_is_multi_user,
                                pst_mac_user->auc_user_mac_addr[4],
                                pst_mac_user->auc_user_mac_addr[5]);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    /*����arp̽��timer*/
    if (OAL_TRUE == pst_hmac_user->st_hmac_user_btcoex.st_hmac_btcoex_arp_req_process.st_delba_opt_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_user->st_hmac_user_btcoex.st_hmac_btcoex_arp_req_process.st_delba_opt_timer));
    }
#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    hmac_chan_update_40M_intol_user(pst_mac_vap, &(pst_hmac_user->st_user_base_info), OAL_FALSE);
#endif
    /*ɾ��userʱ����Ҫ���±�������*/
    ul_ret = hmac_protection_del_user(pst_mac_vap, &(pst_hmac_user->st_user_base_info));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_UM, "{hmac_user_del::hmac_protection_del_user[%d]}", ul_ret);
    }

     /* ��ȡ�û���Ӧ������ */
    us_user_index = pst_hmac_user->st_user_base_info.us_assoc_id;

    /* ɾ��hmac user �Ĺ�������֡�ռ� */
    if (OAL_PTR_NULL != pst_hmac_user->puc_assoc_req_ie_buff)
    {
        OAL_MEM_FREE(pst_hmac_user->puc_assoc_req_ie_buff, OAL_TRUE);
        pst_hmac_user->puc_assoc_req_ie_buff = OAL_PTR_NULL;
        pst_hmac_user->ul_assoc_req_ie_len   = 0;
    }
#ifdef _PRE_WLAN_FEATURE_SMPS
    /* ɾ���û�������SMPS���� */
    hmac_smps_update_status(pst_mac_vap, &(pst_hmac_user->st_user_base_info), OAL_FALSE);
    mac_user_set_sm_power_save(&pst_hmac_user->st_user_base_info, 0);
#endif

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    hmac_stop_sa_query_timer(pst_hmac_user);
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
    hmac_proxy_remove_mac(pst_mac_vap, pst_hmac_user->st_user_base_info.auc_user_mac_addr);
#endif

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_del::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_del::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef  _PRE_WLAN_FEATURE_VOWIFI
    if (OAL_PTR_NULL != pst_hmac_vap->st_vap_base_info.pst_vowifi_cfg_param)
    {
        if (VOWIFI_LOW_THRES_REPORT == pst_hmac_vap->st_vap_base_info.pst_vowifi_cfg_param->en_vowifi_mode)
        {
            /* ������κ�ȥ��������,�л�vowifi����״̬ */
            hmac_config_vowifi_report((&pst_hmac_vap->st_vap_base_info), 0, OAL_PTR_NULL);
        }
    }
#endif /* _PRE_WLAN_FEATURE_VOWIFI */

#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_wapi_deinit(&pst_hmac_user->st_wapi);

     /*STAģʽ�£����鲥wapi���ܶ˿�*/
    pst_hmac_user_multi = (hmac_user_stru *)mac_res_get_hmac_user(pst_hmac_vap->st_vap_base_info.us_multi_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user_multi)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_user_del::mac_res_get_hmac_user fail! user_idx[%u]}",pst_hmac_vap->st_vap_base_info.us_multi_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_wapi_reset_port(&pst_hmac_user_multi->st_wapi);

    pst_mac_device->uc_wapi = OAL_FALSE;

#endif

#ifdef _PRE_WLAN_FEATURE_MCAST
    /*�û�ȥ����ʱ���snoop�����еĸó�Ա */
    if (OAL_PTR_NULL != pst_hmac_vap->pst_m2u)
    {
        hmac_m2u_cleanup_snoopwds_node(pst_hmac_user);
    }
#endif

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {

        /* DTS2015091705218 hostɾ�û�ʱmac vap�µĹ���id���� */
#ifdef _PRE_WLAN_FEATURE_STA_PM
        mac_vap_set_aid(pst_mac_vap, 0);
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
        hmac_roam_exit(pst_hmac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM

        en_ap_type = hmac_compability_ap_tpye_identify(pst_mac_user->auc_user_mac_addr);
    }

    /***************************************************************************
        ���¼���DMAC��, ɾ��dmac�û�
    ***************************************************************************/
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_del_user_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_del::pst_event_mem null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_del_user_payload = (dmac_ctx_del_user_stru *)pst_event->auc_event_data;
    pst_del_user_payload->us_user_idx = us_user_index;
    pst_del_user_payload->en_ap_type  = en_ap_type;
#if (_PRE_OS_VERSION_WIN32 != _PRE_OS_VERSION)
    /* TBD: ��Ӵ˲���51DMT�쳣���ݿ������쳣ԭ�� */
    /* �û� mac��ַ��idx ������һ����Ч����dmac����Ҵ�ɾ�����û� */
    oal_memcopy(pst_del_user_payload->auc_user_mac_addr, pst_mac_user->auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
#endif

    /* ����¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_WLAN_CTX,
                        DMAC_WLAN_CTX_EVENT_SUB_TYPE_DEL_USER,
                        OAL_SIZEOF(dmac_ctx_del_user_stru),
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_mac_vap->uc_chip_id,
                        pst_mac_vap->uc_device_id,
                        pst_mac_vap->uc_vap_id);

    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    hmac_tid_clear(pst_mac_vap, pst_hmac_user);

    if (pst_hmac_user->st_mgmt_timer.en_is_registerd == OAL_TRUE)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_user->st_mgmt_timer);
    }

    if (pst_hmac_user->st_defrag_timer.en_is_registerd == OAL_TRUE)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_user->st_defrag_timer);
    }
#ifdef _PRE_WLAN_FEATURE_WMMAC
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
    /*ɾ��userʱɾ������addts req��ʱ��ʱ��*/
    for(uc_ac_index = 0; uc_ac_index < WLAN_WME_AC_BUTT; uc_ac_index++)
    {
        if (pst_hmac_user->st_user_base_info.st_ts_info[uc_ac_index].st_addts_timer.en_is_registerd == OAL_TRUE)
        {
            FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_user->st_user_base_info.st_ts_info[uc_ac_index].st_addts_timer));
        }

        OAL_MEMZERO(&(pst_hmac_user->st_user_base_info.st_ts_info[uc_ac_index]), OAL_SIZEOF(mac_ts_stru));
        pst_hmac_user->st_user_base_info.st_ts_info[uc_ac_index].uc_tsid = 0xFF;
    }
#endif
#endif

    /* ��vap��ɾ���û� */
    mac_vap_del_user(pst_mac_vap, us_user_index);
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    if (pst_mac_vap->us_user_nums == 5)
    {
        /* AP�û��ﵽ5ʱ���������ز���Ϊ�����ļ�ԭ��ֵ */
        oal_itoa(hwifi_get_init_value(CUS_TAG_INI, WLAN_CFG_INIT_USED_MEM_FOR_START), pc_param, 16);
        oal_itoa(hwifi_get_init_value(CUS_TAG_INI, WLAN_CFG_INIT_USED_MEM_FOR_STOP), pc_tmp, 8);
        pc_param[OAL_STRLEN(pc_param)] = ' ';
        oal_memcopy(pc_param + OAL_STRLEN(pc_param), pc_tmp, OAL_STRLEN(pc_tmp));

        us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);
        hmac_config_sdio_flowctrl(pst_mac_vap, us_len, pc_param);
    }
#endif
    /* �ͷ��û��ڴ� */
    ul_ret = hmac_user_free(us_user_index);
    if(OAL_SUCC == ul_ret)
    {
        /* device���ѹ���user����-- */
        pst_mac_device->uc_asoc_user_cnt--;
    }
    else
    {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_del::mac_res_free_mac_user fail[%d].}", ul_ret);
    }

#ifdef _PRE_SUPPORT_ACS
    hmac_acs_register_rescan_timer(pst_mac_vap->uc_device_id);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_user_add
 ��������  : ����û���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_user_add(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint16 *pus_user_index)
{
    hmac_vap_stru                  *pst_hmac_vap;
    hmac_user_stru                 *pst_hmac_user;
    oal_uint32                      ul_ret;
    frw_event_mem_stru             *pst_event_mem;
    frw_event_stru                 *pst_event;
    dmac_ctx_add_user_stru         *pst_add_user_payload;
    oal_uint16                      us_user_idx;
    mac_device_stru                *pst_mac_device;
    mac_cfg_80211_ucast_switch_stru st_80211_ucast_switch;
    mac_ap_type_enum_uint8          en_ap_type = MAC_AP_TYPE_BUTT;
#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
    oal_uint8                       uc_hipriv_ack = OAL_FALSE;
#endif
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    oal_int8                        pc_param[]    = "30 25";
    oal_uint16                      us_len;
#endif

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_mac_addr) || (OAL_PTR_NULL == pus_user_index)))
    {
        OAM_ERROR_LOG3(0, OAM_SF_UM, "{hmac_user_add::param null, %d %d %d.}", pst_mac_vap, puc_mac_addr, pus_user_index);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_UM, "{hmac_user_add::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��HMAC��������Ծ�û����жϣ��Ѵ�32�򷵻ش��� */
    if (pst_mac_device->uc_active_user_cnt >= WLAN_ACTIVE_USER_MAX_NUM)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::invalid uc_active_user_cnt[%d].}", pst_mac_device->uc_active_user_cnt);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    if (pst_mac_device->uc_asoc_user_cnt >= pst_mac_device->us_user_nums_max)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::users nums exceed spec,invalid uc_asoc_user_cnt[%d], us_user_nums_max=%d.}",
                         pst_mac_device->uc_asoc_user_cnt , pst_mac_device->us_user_nums_max);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

#endif

    if (pst_hmac_vap->st_vap_base_info.us_user_nums >= pst_hmac_vap->us_user_nums_max)
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::invalid us_user_nums[%d], us_user_nums_max[%d].}",
                         pst_hmac_vap->st_vap_base_info.us_user_nums, pst_hmac_vap->us_user_nums_max);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    /* ������û��Ѿ��������򷵻�ʧ�� */
    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
    if (OAL_SUCC == ul_ret)
    {
#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
        uc_hipriv_ack = OAL_TRUE;
        hmac_hipriv_proc_write_process_rsp(pst_mac_vap, sizeof(oal_uint8), &uc_hipriv_ack);
#endif
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
        return OAL_FAIL;
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
	/* DTS2015022704828 P2P��ΪCLʱ�������2���û���һ�����ڷ��͹���֡��һ���û���������֡ */
    #ifdef _PRE_WLAN_FEATURE_P2P
        if (IS_P2P_CL(pst_mac_vap))
        {
            if (pst_hmac_vap->st_vap_base_info.us_user_nums >= 2)
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::a STA can only associated with 2 ap.}");
                return OAL_FAIL;
            }
        }
        else
    #endif
        {
            if (pst_hmac_vap->st_vap_base_info.us_user_nums >= 1)
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::a STA can only associated with one ap.}");
                return OAL_FAIL;
            }
            en_ap_type = hmac_compability_ap_tpye_identify(puc_mac_addr);
        }
#ifdef _PRE_WLAN_FEATURE_ROAM
        hmac_roam_init(pst_hmac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM
    }

    /* ����hmac�û��ڴ棬����ʼ��0 */
    ul_ret = hmac_user_alloc(&us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::hmac_user_alloc failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* �����û�����ʹ��useridΪ0������������һ������userid��Ϊaid������Զˣ�����psmʱ����� */
    if (0 == us_user_idx)
    {
        hmac_user_free(us_user_idx);
        ul_ret = hmac_user_alloc(&us_user_idx);
        if ((OAL_SUCC != ul_ret) || (0 == us_user_idx))
        {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::hmac_user_alloc failed ret[%d] us_user_idx[%d].}", ul_ret, us_user_idx);
            return ul_ret;
        }
    }

    *pus_user_index = us_user_idx;  /* ���θ�ֵ */

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ʼ��mac_user_stru */
    mac_user_init(&(pst_hmac_user->st_user_base_info), us_user_idx, puc_mac_addr,
                  pst_mac_vap->uc_chip_id,
                  pst_mac_vap->uc_device_id,
                  pst_mac_vap->uc_vap_id);

#ifdef _PRE_WLAN_FEATURE_WAPI
    /* ��ʼ������wapi���� */
    hmac_wapi_init(&pst_hmac_user->st_wapi, OAL_TRUE);
    pst_mac_device->uc_wapi = OAL_FALSE;
#endif
    /* ����amsdu�� */
    hmac_amsdu_init_user(pst_hmac_user);

    /***************************************************************************
        ���¼���DMAC��, ����dmac�û�
    ***************************************************************************/
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_add_user_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        /* �쳣�����ͷ��ڴ棬device�¹����û�����û��++�����ﲻ��Ҫ�жϷ���ֵ��--���� */
        hmac_user_free(us_user_idx);

        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::pst_event_mem null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_add_user_payload = (dmac_ctx_add_user_stru *)pst_event->auc_event_data;
    pst_add_user_payload->us_user_idx = us_user_idx;
    pst_add_user_payload->en_ap_type  = en_ap_type;
    oal_set_mac_addr(pst_add_user_payload->auc_user_mac_addr, puc_mac_addr);

    /* ����¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_WLAN_CTX,
                        DMAC_WLAN_CTX_EVENT_SUB_TYPE_ADD_USER,
                        OAL_SIZEOF(dmac_ctx_add_user_stru),
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_mac_vap->uc_chip_id,
                        pst_mac_vap->uc_device_id,
                        pst_mac_vap->uc_vap_id);

    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        /* �쳣�����ͷ��ڴ棬device�¹����û�����û��++�����ﲻ��Ҫ�жϷ���ֵ��--���� */
        hmac_user_free(us_user_idx);
        FRW_EVENT_FREE(pst_event_mem);

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::frw_event_dispatch_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    FRW_EVENT_FREE(pst_event_mem);

    /* ����û���MAC VAP */
    ul_ret = mac_vap_add_assoc_user(pst_mac_vap, us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::mac_vap_add_assoc_user failed[%d].}", ul_ret);

        /* �쳣�����ͷ��ڴ棬device�¹����û�����û��++�����ﲻ��Ҫ�жϷ���ֵ��--���� */
        hmac_user_free(us_user_idx);
        return OAL_FAIL;
    }

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    if (pst_mac_vap->us_user_nums == 6)
    {
        /* AP�û��ﵽ6ʱ���������ز���ΪStopΪ25��StartΪ30 */
        us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);
        hmac_config_sdio_flowctrl(pst_mac_vap, us_len, pc_param);
    }
#endif

    /* ��ʼ��hmac user������Ϣ */
    hmac_user_init(pst_hmac_user);

    pst_mac_device->uc_asoc_user_cnt++;

    /* ��80211��������֡���أ��۲�������̣������ɹ��˾͹ر� */
    st_80211_ucast_switch.en_frame_direction = OAM_OTA_FRAME_DIRECTION_TYPE_TX;
    st_80211_ucast_switch.en_frame_type = OAM_USER_TRACK_FRAME_TYPE_MGMT;
    st_80211_ucast_switch.en_frame_switch = OAL_SWITCH_ON;
    st_80211_ucast_switch.en_cb_switch = OAL_SWITCH_ON;
    st_80211_ucast_switch.en_dscr_switch = OAL_SWITCH_ON;
    oal_memcopy(st_80211_ucast_switch.auc_user_macaddr,
                (const oal_void *)puc_mac_addr,
                OAL_SIZEOF(st_80211_ucast_switch.auc_user_macaddr));
    hmac_config_80211_ucast_switch(pst_mac_vap,OAL_SIZEOF(st_80211_ucast_switch),(oal_uint8 *)&st_80211_ucast_switch);

    st_80211_ucast_switch.en_frame_direction = OAM_OTA_FRAME_DIRECTION_TYPE_RX;
    st_80211_ucast_switch.en_frame_type = OAM_USER_TRACK_FRAME_TYPE_MGMT;
    st_80211_ucast_switch.en_frame_switch = OAL_SWITCH_ON;
    st_80211_ucast_switch.en_cb_switch = OAL_SWITCH_ON;
    st_80211_ucast_switch.en_dscr_switch = OAL_SWITCH_ON;
    hmac_config_80211_ucast_switch(pst_mac_vap,OAL_SIZEOF(st_80211_ucast_switch),(oal_uint8 *)&st_80211_ucast_switch);



    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add::user[%d] mac:%02X:XX:XX:XX:%02X:%02X}",
                                us_user_idx,
                                puc_mac_addr[0],
                                puc_mac_addr[4],
                                puc_mac_addr[5]);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_config_add_user
 ��������  : ������������û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_config_add_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_add_user_param_stru    *pst_add_user;
    oal_uint16                      us_user_index;
    hmac_vap_stru                  *pst_hmac_vap;
    hmac_user_stru                 *pst_hmac_user;
    oal_uint32                      ul_ret;
    mac_user_ht_hdl_stru            st_ht_hdl;
    oal_uint32                      ul_rslt;
    mac_device_stru                *pst_mac_device;

    pst_add_user = (mac_cfg_add_user_param_stru *)puc_param;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_UM, "{hmac_config_add_user::pst_hmac_vap null.}");
        return OAL_FAIL;
    }

    ul_ret = hmac_user_add(pst_mac_vap, pst_add_user->auc_mac_addr, &us_user_index);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_add_user::hmac_user_add failed.}", ul_ret);
        return ul_ret;
    }

    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_index);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_add_user::pst_hmac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD hmac_config_add_user �˽ӿ�ɾ������Ӧ������Ҫ���ģ�duankaiyong&guyanjie */

    /* ����qos�򣬺���������Ҫ����ͨ����������������� */
    mac_user_set_qos(&pst_hmac_user->st_user_base_info, OAL_TRUE);

    /* ����HT�� */
    mac_user_get_ht_hdl(&pst_hmac_user->st_user_base_info, &st_ht_hdl);
    st_ht_hdl.en_ht_capable = pst_add_user->en_ht_cap;

    if (OAL_TRUE == pst_add_user->en_ht_cap)
    {
        pst_hmac_user->st_user_base_info.en_cur_protocol_mode                = WLAN_HT_MODE;
        pst_hmac_user->st_user_base_info.en_avail_protocol_mode              = WLAN_HT_MODE;
    }

    /* ����HT��ص���Ϣ:Ӧ���ڹ�����ʱ��ֵ ���ֵ���õĺ������д����� 2012->page:786 */
    st_ht_hdl.uc_min_mpdu_start_spacing = 6;
    st_ht_hdl.uc_max_rx_ampdu_factor    = 3;
    mac_user_set_ht_hdl(&pst_hmac_user->st_user_base_info, &st_ht_hdl);

    mac_user_set_asoc_state(&pst_hmac_user->st_user_base_info, MAC_USER_STATE_ASSOC);

    /* ����amsdu�� */
    hmac_amsdu_init_user(pst_hmac_user);

    /***************************************************************************
        ���¼���DMAC��, ͬ��DMAC����
    ***************************************************************************/
    /* ��������DMAC��Ҫ�Ĳ��� */
    pst_add_user->us_user_idx = us_user_index;

    ul_ret = hmac_config_send_event(&pst_hmac_vap->st_vap_base_info,
                                    WLAN_CFGID_ADD_USER,
                                    us_len,
                                    puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        /* �쳣�����ͷ��ڴ� */
        ul_rslt = hmac_user_free(us_user_index);
        if(OAL_SUCC == ul_rslt)
        {
            pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
            if (OAL_PTR_NULL == pst_mac_device)
            {
                OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_add_user::pst_mac_device null.}");
                return OAL_ERR_CODE_PTR_NULL;
            }

            /* hmac_add_user�ɹ�ʱdevice�¹����û����Ѿ�++, �����device���ѹ���user����Ҫ-- */
            pst_mac_device->uc_asoc_user_cnt--;
        }

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_add_user::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* ��׮����û���Ϣ��ȫ������Ҫ֪ͨ�㷨 */
    //hmac_user_add_notify_alg(&pst_hmac_vap->st_vap_base_info, us_user_index);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (IS_LEGACY_VAP(pst_mac_vap)) //DTS2015022604332 ����û��󣬶���P2P ����Ҫ�޸�vap ״̬
    {
        mac_vap_state_change(pst_mac_vap, MAC_VAP_STATE_UP);
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_config_del_user
 ��������  : ��������ɾ���û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_config_del_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_del_user_param_stru    *pst_del_user;
    hmac_user_stru                 *pst_hmac_user;
    hmac_vap_stru                  *pst_hmac_vap;
    oal_uint16                      us_user_index;
    oal_uint32                      ul_ret = 0;

    pst_del_user = (mac_cfg_add_user_param_stru *)puc_param;

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_del_user::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�û���Ӧ������ */
    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, pst_del_user->auc_mac_addr, &us_user_index);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_del_user::mac_vap_find_user_by_macaddr failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* ��ȡhmac�û� */
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_index);

    ul_ret = hmac_user_del(pst_mac_vap, pst_hmac_user);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_del_user::hmac_user_del failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* ��������DMAC��Ҫ�Ĳ��� */
    pst_del_user->us_user_idx = us_user_index;

    /***************************************************************************
        ���¼���DMAC��, ͬ��DMAC����
    ***************************************************************************/
    ul_ret = hmac_config_send_event(&pst_hmac_vap->st_vap_base_info,
                                    WLAN_CFGID_DEL_USER,
                                    us_len,
                                    puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        /* �쳣�����ͷ��ڴ� */
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_config_del_user::hmac_config_send_event failed[%d].}", ul_ret);
        return ul_ret;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_add_multi_user
 ��������  : hmac�㴴���鲥�û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��23��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_user_add_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_user_index)
{
    oal_uint32      ul_ret;
    oal_uint16      us_user_index;
    mac_user_stru  *pst_mac_user;
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_user_stru *pst_hmac_user;
#endif

    ul_ret = hmac_user_alloc(&us_user_index);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add_multi_user::hmac_user_alloc failed[%d].}", ul_ret);
        return ul_ret;
    }

    /* ��ʼ���鲥�û�������Ϣ */
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(us_user_index);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_UM, "{hmac_user_add_multi_user::pst_mac_user null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_init(pst_mac_user, us_user_index, OAL_PTR_NULL, pst_mac_vap->uc_chip_id,  pst_mac_vap->uc_device_id, pst_mac_vap->uc_vap_id);

    *pus_user_index = us_user_index;

#ifdef _PRE_WLAN_FEATURE_WAPI
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_index);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_user_add_multi_user::get hmac_user fail.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ʼ��wapi���� */
    hmac_wapi_init(&pst_hmac_user->st_wapi, OAL_FALSE);
#endif

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_user_add_multi_user, user index[%d].}", us_user_index);

    return OAL_SUCC;
}



/*****************************************************************************
 �� �� ��  : hmac_user_del_multi_user
 ��������  : hmac��ɾ��multiuser
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��23��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_user_del_multi_user(mac_vap_stru *pst_mac_vap)
{
#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_user_stru      *pst_hmac_user;
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_user_add_multi_user::get hmac_user fail.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_wapi_deinit(&pst_hmac_user->st_wapi);
#endif

    hmac_user_free(pst_mac_vap->us_multi_user_idx);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_user_is_wapi_connected
 ��������  : �ж�wapi�豸�Ƿ����
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��23��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_WAPI
oal_uint8  hmac_user_is_wapi_connected(oal_uint8 uc_device_id)
{
    oal_uint8               uc_vap_idx;
    hmac_user_stru         *pst_hmac_user_multi;
    mac_device_stru        *pst_mac_device;
    mac_vap_stru           *pst_mac_vap;

    pst_mac_device = mac_res_get_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_UM, "{hmac_user_is_wapi_connected::pst_mac_device null.id %u}", uc_device_id);
        return OAL_FALSE;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "vap is null! vap id is %d", pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (!IS_STA(pst_mac_vap))
        {
            continue;
        }

        pst_hmac_user_multi = (hmac_user_stru *)mac_res_get_hmac_user(pst_mac_vap->us_multi_user_idx);
        if ((OAL_PTR_NULL != pst_hmac_user_multi)
    		&& (OAL_TRUE == pst_hmac_user_multi->st_wapi.uc_port_valid))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}
#endif/* #ifdef _PRE_WLAN_FEATURE_WAPI */


/*****************************************************************************
 �� �� ��  : hmac_user_add_notify_alg
 ��������  : ���¼���dmac��������dmac���㷨����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��25��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_user_add_notify_alg(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx)
{
    frw_event_mem_stru             *pst_event_mem;
    frw_event_stru                 *pst_event;
    dmac_ctx_add_user_stru         *pst_add_user_payload;
    oal_uint32                      ul_ret;
    hmac_user_stru                 *pst_hmac_user;

    /* ���¼���Dmac����dmac����û��㷨���� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(dmac_ctx_add_user_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_user_add_notify_alg::pst_event_mem null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;
    pst_add_user_payload = (dmac_ctx_add_user_stru *)pst_event->auc_event_data;
    //oal_memcmp(pst_add_user_payload->auc_bssid, pst_mac_vap->auc_bssid, WLAN_MAC_ADDR_LEN);
    pst_add_user_payload->us_user_idx = us_user_idx;
    pst_add_user_payload->us_sta_aid = pst_mac_vap->us_sta_aid;
    pst_hmac_user = (hmac_user_stru *)mac_res_get_hmac_user(us_user_idx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_user))
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{hmac_user_add_notify_alg::null param,pst_hmac_user[%d].}",us_user_idx);
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_get_vht_hdl(&pst_hmac_user->st_user_base_info, &pst_add_user_payload->st_vht_hdl);
    mac_user_get_ht_hdl(&pst_hmac_user->st_user_base_info, &pst_add_user_payload->st_ht_hdl);
    /* ����¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                        FRW_EVENT_TYPE_WLAN_CTX,
                        DMAC_WLAN_CTX_EVENT_SUB_TYPE_NOTIFY_ALG_ADD_USER,
                        OAL_SIZEOF(dmac_ctx_add_user_stru),
                        FRW_EVENT_PIPELINE_STAGE_1,
                        pst_mac_vap->uc_chip_id,
                        pst_mac_vap->uc_device_id,
                        pst_mac_vap->uc_vap_id);

    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        /* �쳣�����ͷ��ڴ� */
        FRW_EVENT_FREE(pst_event_mem);

        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_user_add_notify_alg::frw_event_dispatch_event failed[%d].}", ul_ret);
        return ul_ret;
    }
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_get_hmac_user_by_addr
 ��������  : ����mac��ַ��ȡmac_userָ��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��8��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
hmac_user_stru  *mac_vap_get_hmac_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr)
{
    oal_uint32              ul_ret;
    oal_uint16              us_user_idx   = 0xffff;
    hmac_user_stru         *pst_hmac_user = OAL_PTR_NULL;

    /*����mac addr��sta����*/
    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
    if(OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_vap_get_hmac_user_by_addr::find_user_by_macaddr failed[%d].}", ul_ret);
        if (OAL_PTR_NULL != puc_mac_addr)
        {
            OAM_WARNING_LOG3(0, OAM_SF_ANY,"{mac_vap_get_hmac_user_by_addr:: mac_addr[%02x XX XX XX %02x %02x]!.}",
                                puc_mac_addr[0], puc_mac_addr[4], puc_mac_addr[5]);
        }
        return OAL_PTR_NULL;
    }

    /*����sta�����ҵ�user�ڴ�����*/
    pst_hmac_user = mac_res_get_hmac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_hmac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_vap_get_hmac_user_by_addr::user ptr null.}");
    }
    return pst_hmac_user;
}

/*lint -e19*/
oal_module_symbol(hmac_user_alloc);
oal_module_symbol(hmac_user_init);
oal_module_symbol(hmac_config_kick_user);
oal_module_symbol(mac_vap_get_hmac_user_by_addr);
oal_module_symbol(mac_res_get_hmac_user);
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

