/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_vap.c
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   : DMAC����Ҫdestroy�Ķ�����
               ��Ϊdestroy�Ǵ�hmac����ģ��ֱ�����down��del
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

#include "wlan_spec.h"
#include "mac_ie.h"
#include "mac_vap.h"
#include "dmac_vap.h"
#include "dmac_user.h"
#include "dmac_main.h"
#include "dmac_blockack.h"
#include "dmac_alg.h"
#include "dmac_beacon.h"
#include "dmac_mgmt_bss_comm.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_mgmt_sta.h"
#include "dmac_uapsd.h"
#include "dmac_psm_ap.h"
#ifdef _PRE_WIFI_DMT
#include "dmt_stub.h"
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_sta_pm.h"
#endif
#include "dmac_device.h"
#include "mac_device.h"
#include "dmac_config.h"
#ifdef _PRE_WLAN_SW_CTRL_RSP
#include "dmac_resource.h"
#endif
#ifdef _PRE_WLAN_FEATURE_11K
#include "dmac_11k.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_VAP_C
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_BTCOEX
oal_uint16 g_us_occupied_point[BTCOEX_LINKLOSS_OCCUPIED_NUMBER];
#endif

#ifdef _PRE_WLAN_FEATURE_11K
extern oal_uint8 g_pm_switch;
#endif
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_vap_linkloss_init
 ��������  :  ��ʼ��linkloss��⹤��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : zhongwen
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_vap_linkloss_init(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    oal_uint8 uc_index;
    dmac_vap_btcoex_occupied_stru *pst_dmac_vap_btcoex_occupied;
#endif

    dmac_vap_linkloss_clean(pst_dmac_vap);
    if (WLAN_VAP_MODE_BSS_STA != pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        pst_dmac_vap->st_linkloss_info.us_linkloss_threshold  = 0; /* ��Ч */
        return;
    }

    /* ��δ������Ԥ�����öԶ�ap��beacon����Ϊ100 */
    pst_dmac_vap->st_linkloss_info.ul_old_dot11BeaconPeriod = WLAN_BEACON_INTVAL_DEFAULT;
    pst_dmac_vap->st_linkloss_info.uc_linkloss_times = 1;
    pst_dmac_vap->st_linkloss_info.en_old_bt_on        = OAL_FALSE;
    pst_dmac_vap->st_linkloss_info.en_old_dbac_runing  = OAL_FALSE;
    pst_dmac_vap->st_linkloss_info.en_old_far_distance = OAL_FALSE;
    /* staut/p2p cl linkloss����һ�� */
    pst_dmac_vap->st_linkloss_info.us_linkloss_threshold  = (oal_uint16)(40); /* 4s */

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    g_us_occupied_point[0] = 5;     /* pst_dmac_vap->st_linkloss_info.us_linkloss_threshold / BTCOEX_LINKLOSS_OCCUPIED_NUMBER */

    for (uc_index = 0; uc_index < BTCOEX_LINKLOSS_OCCUPIED_NUMBER - 1; uc_index++)
    {
        g_us_occupied_point[uc_index + 1] = g_us_occupied_point[uc_index] + 5;
    }

    pst_dmac_vap_btcoex_occupied = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied);
    pst_dmac_vap_btcoex_occupied->uc_linkloss_index = 1;
    pst_dmac_vap_btcoex_occupied->uc_linkloss_occupied_times = 0;
#endif

}
#ifdef _PRE_WLAN_FEATURE_VOWIFI
/*****************************************************************************
 �� �� ��  : dmac_vap_vowifi_init
 ��������  : ��ʼ��dmac vowifi����Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : oal_int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��19��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
void dmac_vap_vowifi_init(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint64  ull_timestamp_ms;

    if (WLAN_VAP_MODE_BSS_STA != pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        return;
    }
    if (OAL_PTR_NULL == pst_dmac_vap->pst_vowifi_status)
    {
        pst_dmac_vap->pst_vowifi_status = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_vowifi_status_stru), OAL_TRUE);
        if (OAL_PTR_NULL == pst_dmac_vap->pst_vowifi_status)
        {
            OAM_ERROR_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_VOWIFI, "{dmac_vap_vowifi_init::pst_vowifi_status alloc null, size[%d].}", OAL_SIZEOF(mac_vowifi_status_stru));
            return ;
        }
    }

    OAL_MEMZERO((oal_uint8 *)(pst_dmac_vap->pst_vowifi_status), OAL_SIZEOF(mac_vowifi_status_stru));
    ull_timestamp_ms = OAL_TIME_GET_STAMP_MS();
    pst_dmac_vap->pst_vowifi_status->ull_rssi_timestamp_ms = ull_timestamp_ms;
    pst_dmac_vap->pst_vowifi_status->ull_arp_timestamp_ms  = ull_timestamp_ms;
}
/*****************************************************************************
 �� �� ��  : dmac_vap_vowifi_exit
 ��������  : ȥ��ʼ��dmac vowifi����Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : oal_int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��19��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
void dmac_vap_vowifi_exit(dmac_vap_stru *pst_dmac_vap)
{
    mac_vowifi_status_stru    *pst_vowifi_status;

    if (OAL_PTR_NULL == pst_dmac_vap->pst_vowifi_status)
    {
        return;
    }

    pst_vowifi_status = pst_dmac_vap->pst_vowifi_status;

    /*���ÿ����ͷ�*/
    pst_dmac_vap->pst_vowifi_status = OAL_PTR_NULL;
    OAL_MEM_FREE(pst_vowifi_status, OAL_TRUE);

}
#endif /* _PRE_WLAN_FEATURE_VOWIFI */

/*****************************************************************************
 �� �� ��  : dmac_vap_init
 ��������  : ��ʼ��Ҫ��ӵ�dmac vap��һЩ������Ϣ
 �������  : ָ��Ҫ��ӵ�vap��ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��24��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_vap_init(
                dmac_vap_stru              *pst_dmac_vap,
                oal_uint8                   uc_chip_id,
                oal_uint8                   uc_device_id,
                oal_uint8                   uc_vap_id,
                mac_cfg_add_vap_param_stru *pst_param)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32  ul_ret;
#endif
    mac_device_stru               *pst_mac_device = mac_res_get_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_vap_init::pst_mac_device[%d] null!}", uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* DMAC VAP ���ֳ�ʼ���� */
    OAL_MEMZERO(((oal_uint8 *)pst_dmac_vap) + OAL_SIZEOF(mac_vap_stru), OAL_SIZEOF(dmac_vap_stru) - OAL_SIZEOF(mac_vap_stru));
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

    /* ͳ����Ϣ���� */
    oam_stats_clear_vap_stat_info(uc_vap_id);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /* �ڷ�OFFLOAD����£���Щ����HMAC���Ѿ������� */
    /* ��ʼ��mac vap */
    ul_ret = mac_vap_init(&pst_dmac_vap->st_vap_base_info,
                           uc_chip_id,
                           uc_device_id,
                           uc_vap_id,
                           pst_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(uc_vap_id, OAM_SF_CFG,
                         "{dmac_vap_init::dmac_vap_init failed[%d].", ul_ret);
        return ul_ret;
    }
    pst_dmac_vap->bit_beacon_timeout_times = 0;
#endif
#ifdef _PRE_WLAN_FEATURE_VOWIFI
    if (WLAN_LEGACY_VAP_MODE == pst_param->en_p2p_mode)
    {
        dmac_vap_vowifi_init(pst_dmac_vap);
    }
#endif
    pst_dmac_vap->en_bfer_actived       = pst_mac_device->bit_su_bfmer;
    pst_dmac_vap->en_bfee_actived       = pst_mac_device->bit_su_bfmee;
    pst_dmac_vap->en_mu_bfee_actived    = pst_mac_device->bit_mu_bfmee;
    pst_dmac_vap->en_txstbc_actived     = pst_mac_device->bit_tx_stbc;
    pst_dmac_vap->en_multi_user_multi_ac_flag = OAL_FALSE;
    pst_dmac_vap->uc_traffic_type    = OAL_TRAFFIC_NORMAL;

    /* ��ʼ�����Ա�ʶ��BEACON֡���������� */
    pst_dmac_vap->en_beacon_chain_active = OAL_FALSE;

    /* VAP����ͨ��Ĭ��ֵ��ֵ������device��������ֵ */
    pst_dmac_vap->uc_vap_tx_chain = pst_mac_device->uc_tx_chain;

    /* ���ʽṹ�帳��ֵ */
    /* ����PHY�����ĳ�ʼֵ ul_value = 0x00800211 */
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_count = 1;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_stbc_mode = 0;
#endif
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna = 2;


    /* FPGA zhangyu Debug 11n */
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_ht_mcs = 0;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_ht_rate.bit_protocol_mode = WLAN_HT_PHY_PROTOCOL_MODE;

    /* Ĭ����HOST VAP */
    pst_dmac_vap->en_is_host_vap = OAL_TRUE;

    /* Ĭ��������� */
    pst_dmac_vap->uc_default_ant_bitmap = 0xFF;

    /* ��ʼ��������ز��� */
    pst_dmac_vap->uc_ps_user_num = 0;
    pst_dmac_vap->uc_dtim_count  = WLAN_DTIM_DEFAULT;
#ifdef _PRE_WLAN_CHIP_TEST
    pst_dmac_vap->pst_wow_probe_resp = OAL_PTR_NULL;
    pst_dmac_vap->pst_wow_null_data  = OAL_PTR_NULL;
#endif
    pst_dmac_vap->uc_sw_retry_limit  = DMAC_MAX_SW_RETRIES;

    if (WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
        if (OAL_PTR_NULL != pst_dmac_vap->puc_tim_bitmap)
        {
            OAL_MEM_FREE(pst_dmac_vap->puc_tim_bitmap, OAL_TRUE);
            pst_dmac_vap->puc_tim_bitmap = OAL_PTR_NULL;
        }

        /* DTS2015050301014,˫оƬʵ��ʱbitmap_len����Ҫ����device(Ҳ����chip)����  */
        pst_dmac_vap->uc_tim_bitmap_len = (oal_uint8)(2 + (((g_us_max_asoc_user + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE)* MAC_RES_MAX_DEV_NUM + 7 ) >> 3));
        pst_dmac_vap->puc_tim_bitmap = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, pst_dmac_vap->uc_tim_bitmap_len, OAL_TRUE);
        if (OAL_PTR_NULL == pst_dmac_vap->puc_tim_bitmap)
        {
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_vap_init::puc_tim_bitmap null.}");

            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        OAL_MEMZERO(pst_dmac_vap->puc_tim_bitmap, pst_dmac_vap->uc_tim_bitmap_len);
        /* TIM bitmap len is default 1*/
        pst_dmac_vap->puc_tim_bitmap[0] = 1;
    }
    if(WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
    {
#ifdef _PRE_WLAN_FEATURE_DFS
        mac_mib_set_SpectrumManagementImplemented(&pst_dmac_vap->st_vap_base_info, OAL_TRUE);
#endif
    }

#ifdef _PRE_WLAN_FEATURE_11K
    pst_dmac_vap->pst_rrm_info = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_rrm_info_stru), OAL_TRUE);
    if (OAL_PTR_NULL == pst_dmac_vap->pst_rrm_info)
    {
        if ((WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode) && (OAL_PTR_NULL != pst_dmac_vap->puc_tim_bitmap))
        {
            OAL_MEM_FREE(pst_dmac_vap->puc_tim_bitmap, OAL_TRUE);
            pst_dmac_vap->puc_tim_bitmap = OAL_PTR_NULL;
        }
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_vap_init::pst_rrm_info null.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    OAL_MEMZERO(pst_dmac_vap->pst_rrm_info, OAL_SIZEOF(mac_rrm_info_stru));
    oal_dlist_init_head(&(pst_dmac_vap->pst_rrm_info->st_meas_rpt_list));

    pst_dmac_vap->bit_bcn_table_switch  = OAL_FALSE; //���ʱĬ��ʹ�ܣ����޸�
    //pst_dmac_vap->bit_voe_enable        = OAL_FALSE;
    pst_dmac_vap->bit_11k_enable        = OAL_FALSE;
    pst_dmac_vap->bit_11v_enable        = OAL_FALSE;

#endif //_PRE_WLAN_FEATURE_11K

#ifdef _PRE_WLAN_FEATURE_11R
    pst_dmac_vap->bit_11r_enable        = OAL_FALSE;
#endif

    /* ��ʼ��������ʱʱ�� */
    pst_dmac_vap->us_del_timeout                = DMAC_BA_DELBA_TIMEOUT;

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    pst_dmac_vap->pst_ip_addr_info = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(dmac_vap_ip_entries_stru), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap->pst_ip_addr_info))
    {
        if ((WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode) && (OAL_PTR_NULL != pst_dmac_vap->puc_tim_bitmap))
        {
            OAL_MEM_FREE(pst_dmac_vap->puc_tim_bitmap, OAL_TRUE);
            pst_dmac_vap->puc_tim_bitmap = OAL_PTR_NULL;
        }
#ifdef _PRE_WLAN_FEATURE_11K
        if(OAL_PTR_NULL != pst_dmac_vap->pst_rrm_info)
        {
            OAL_MEM_FREE(pst_dmac_vap->pst_rrm_info, OAL_TRUE);
            pst_dmac_vap->pst_rrm_info = OAL_PTR_NULL;
        }
#endif
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_PWR, "{dmac_vap_init::Alloc memory for IP address record array failed.}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    oal_memset(pst_dmac_vap->pst_ip_addr_info, 0, OAL_SIZEOF(dmac_vap_ip_entries_stru));

#endif

    pst_dmac_vap->st_query_stats.ul_signal = DMAC_INVALID_SIGNAL_INITIAL;

    pst_dmac_vap->us_beacon_timeout  = DMAC_DEFAULT_STA_BEACON_WAIT_TIME;
    pst_dmac_vap->us_in_tbtt_offset  = DMAC_DEFAULT_STA_INTER_TBTT_OFFSET;
    pst_dmac_vap->us_ext_tbtt_offset = DMAC_DEFAULT_EXT_TBTT_OFFSET;
    pst_dmac_vap->uc_bcn_tout_max_cnt = DMAC_DEFAULT_STA_BCN_TOUT_MAX_CNT;

    pst_dmac_vap->uc_psm_dtim_period = 0;
    pst_dmac_vap->us_psm_listen_interval = 0;

    pst_dmac_vap->en_non_erp_exist = OAL_FALSE;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_vap_init_tx_data_ucast
 ��������  : ��ʼ����������֡�������ʲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��7��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_vap_init_tx_data_ucast(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_protocol_mode, oal_uint8 uc_legacy_rate)
{
    oal_uint32          ul_data_rate = 0;

    pst_dmac_vap->st_tx_alg.ast_per_rate[0].ul_value = 0x0;

    /* ��������֡���� */
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_count           = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_stbc_mode          = 0;
#endif
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna     = 1;

    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = uc_legacy_rate;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = uc_protocol_mode;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable     = 0;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_txbf_mode          = 0;

    /* 11b 1M���ʲ�����ʹ�ö̵��� */
    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0 == uc_legacy_rate))
    {
        pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 0;
    }
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable    = 0;
    pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.bit_reserve            = 0;

    ul_data_rate = pst_dmac_vap->st_tx_alg.ast_per_rate[0].ul_value;

    pst_dmac_vap->st_tx_alg.ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_alg.ast_per_rate[1].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_alg.ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_alg.ast_per_rate[2].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_alg.ast_per_rate[3].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_alg.ast_per_rate[3].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_alg.st_rate.bit_lsig_txop = OAL_FALSE;
}


/*****************************************************************************
 �� �� ��  : dmac_vap_init_tx_data_mcast
 ��������  : ��ʼ���鲥����֡�������ʲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_vap_init_tx_data_mcast(
                dmac_vap_stru               *pst_dmac_vap,
                wlan_protocol_enum_uint8     en_protocol,
                wlan_channel_band_enum_uint8 en_band)
{
    oal_uint8       uc_protocol_mode;
    oal_uint8       uc_legacy_rate;
    oal_uint32      ul_data_rate;

    switch (en_protocol)
    {
        /* 11b 1M */
        case WLAN_LEGACY_11B_MODE:
        case WLAN_MIXED_ONE_11G_MODE:
        case WLAN_HT_MODE:
            if (WLAN_BAND_2G == en_band)
            {
                uc_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0;
#ifdef _PRE_WLAN_FEATURE_P2P
                /* P2P �豸���ܷ���11b ���ʵ�֡ */
                uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0xB;
#endif  /* _PRE_WLAN_FEATURE_P2P */
            }
            else
            {
                uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0xB;
            }
            break;

        /* OFDM 6M */
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
        case WLAN_VHT_MODE:
        case WLAN_HT_11G_MODE:
            uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            uc_legacy_rate   = 0xB;
            break;

        /* OFDM 24M */
        case WLAN_HT_ONLY_MODE:
        case WLAN_VHT_ONLY_MODE:
            uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            uc_legacy_rate   = 0x9;
            break;

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{dmac_vap_init_tx_data_mcast::invalid en_protocol[%d].}", en_protocol);
            return;
    }


    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value = 0x0;

    /* �㲥����֡���� */
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_count           = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_stbc_mode          = 0;

    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0x3 == pst_dmac_vap->uc_vap_tx_chain))
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
    }
#else
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
#endif
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna     = 1;

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = uc_legacy_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = uc_protocol_mode;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable     = 0;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_txbf_mode          = 0;

    /* 11b 1M���ʲ�����ʹ�ö̵��� */
    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0 == uc_legacy_rate))
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 0;
    }

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable    = 0;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].rate_bit_stru.bit_reserve            = 0;

    ul_data_rate = pst_dmac_vap->st_tx_data_mcast.ast_per_rate[0].ul_value;

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[1].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[2].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[3].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_mcast.ast_per_rate[3].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_mcast.st_rate.bit_lsig_txop = OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_vap_init_tx_data_bcast
 ��������  : ��ʼ���㲥����֡�������ʲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_data_bcast(
                dmac_vap_stru               *pst_dmac_vap,
                wlan_protocol_enum_uint8     en_protocol,
                wlan_channel_band_enum_uint8 en_band)
{
    oal_uint8       uc_protocol_mode;
    oal_uint8       uc_legacy_rate;
    oal_uint32      ul_data_rate;

    switch (en_protocol)
    {
        /* 11b 1M */
        case WLAN_LEGACY_11B_MODE:
        case WLAN_MIXED_ONE_11G_MODE:
        case WLAN_HT_MODE:
            if (WLAN_BAND_2G == en_band)
            {
                uc_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0;
#ifdef _PRE_WLAN_FEATURE_P2P
                /* P2P �豸���ܷ���11b ���ʵ�֡ */
                uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0xB;
#endif  /* _PRE_WLAN_FEATURE_P2P */
            }
            else
            {
                uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
                uc_legacy_rate   = 0xB;
            }
            break;

        /* OFDM 6M */
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
        case WLAN_VHT_MODE:
        case WLAN_HT_11G_MODE:
            uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            uc_legacy_rate   = 0xB;
            break;

        /* OFDM 24M */
        case WLAN_HT_ONLY_MODE:
        case WLAN_VHT_ONLY_MODE:
            uc_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            uc_legacy_rate   = 0x9;
            break;

        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{dmac_vap_init_tx_data_bcast::invalid en_protocol[%d].}", en_protocol);
            return OAL_FAIL;
    }

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].ul_value = 0x0;

    /* �㲥����֡���� */
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_tx_count           = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_stbc_mode          = 0;

    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0x3 == pst_dmac_vap->uc_vap_tx_chain))
    {
        pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
    }
#else
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection = pst_dmac_vap->uc_vap_tx_chain;
#endif
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna     = 1;

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = uc_legacy_rate;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = uc_protocol_mode;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable     = 0;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_txbf_mode          = 0;

    /* 11b 1M���ʲ�����ʹ�ö̵��� */
    if ((WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode) && (0 == uc_legacy_rate))
    {
        pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 1;
    }
    else
    {
        pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_preamble_mode  = 0;
    }

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_short_gi_enable    = 0;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].rate_bit_stru.bit_reserve            = 0;

    ul_data_rate = pst_dmac_vap->st_tx_data_bcast.ast_per_rate[0].ul_value;

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[1].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[2].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[3].ul_value = ul_data_rate;
    pst_dmac_vap->st_tx_data_bcast.ast_per_rate[3].rate_bit_stru.bit_tx_count = 0;

    pst_dmac_vap->st_tx_data_bcast.st_rate.bit_lsig_txop = OAL_FALSE;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_vap_init_tx_mgmt_ucast
 ��������  : ��ʼ����������֡�������ʲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_mgmt_ucast(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint32 ul_value;

    /* ��ʼ��2.4G���� */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode            = 0;
#endif
    if (0x3 == pst_dmac_vap->uc_vap_tx_chain)
    {
        pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = 1;
    }
    else
    {
        pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = pst_dmac_vap->uc_vap_tx_chain;
    }

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna       = 1;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable       = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode            = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable      = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_reserve              = 0;

    /* 2.4G��ʼ��Ϊ11b 1M, long preable */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode                            = 1;
#ifdef _PRE_WLAN_FEATURE_P2P
    if (!IS_LEGACY_VAP(&(pst_dmac_vap->st_vap_base_info)))
    {
        /* P2P �豸���ܷ���11b ���ʵ�֡ */
        pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0xb;  /* 6M */
        pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    }
#endif  /* _PRE_WLAN_FEATURE_P2P */

    ul_value = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[0].ul_value;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[1].ul_value = ul_value;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[2].ul_value = ul_value;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].ast_per_rate[3].ul_value = ul_value;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_2G].st_rate.bit_lsig_txop = OAL_FALSE;

    /* ��ʼ��5G���� */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 3;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode            = 0;
#endif
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = pst_dmac_vap->uc_vap_tx_chain;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna       = 1;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable       = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode            = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable      = 0;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_reserve              = 0;

    /* 5G��ʼ��ΪOFDM 6M, short preable */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0xb;  /* 6M */
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode                            = 0;

    ul_value = pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[0].ul_value;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[1].ul_value = ul_value;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[2].ul_value = ul_value;
    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].ast_per_rate[3].ul_value = ul_value;

    pst_dmac_vap->ast_tx_mgmt_ucast[WLAN_BAND_5G].st_rate.bit_lsig_txop = OAL_FALSE;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_vap_init_tx_mgmt_bmcast
 ��������  : ��ʼ���鲥���㲥����֡�������ʲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_mgmt_bmcast(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint32  ul_data_rate;

    /* ��ʼ��2.4G���� */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].ul_value                               = 0x0;
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 4;
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 3;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode            = 0;
#endif
    if (0x3 == pst_dmac_vap->uc_vap_tx_chain)
    {
        pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = 1;
    }
    else
    {
        pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = pst_dmac_vap->uc_vap_tx_chain;
    }

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna       = 1;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable       = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode            = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable      = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_reserve              = 0;

    /* 2.4G��ʼ��Ϊ11b 1M, long preable */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_11B_PHY_PROTOCOL_MODE;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode                            = 1;
#ifdef _PRE_WLAN_FEATURE_P2P
    if (!IS_LEGACY_VAP(&(pst_dmac_vap->st_vap_base_info)))
    {
        /* P2P �豸���ܷ���11b ���ʵ�֡ */
		/* DTS2015033002930:��ʼ��P2P �㲥����֡�������ʺ�Э��ģʽΪ6Mbps��OFDM  */
        pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0xb;  /* 6M */
        pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    }
#endif  /* _PRE_WLAN_FEATURE_P2P */

    ul_data_rate = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[0].ul_value;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].ast_per_rate[3].ul_value = ul_data_rate;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_2G].st_rate.bit_lsig_txop = OAL_FALSE;

    /* ��ʼ��5G���� */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].ul_value                               = 0x0;
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 4;
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_tx_count             = 3;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_stbc_mode            = 0;
#endif
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_tx_chain_selection   = pst_dmac_vap->uc_vap_tx_chain;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.uc_tx_data_antenna       = 1;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_rts_cts_enable       = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_txbf_mode            = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_short_gi_enable      = 0;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_reserve              = 0;

    /* 5G��ʼ��ΪOFDM 6M, short preable */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_legacy_rate   = 0xb;  /* 6M */
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].rate_bit_stru.bit_preamble_mode                            = 0;

    ul_data_rate = pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[0].ul_value;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[1].ul_value = ul_data_rate;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[2].ul_value = ul_data_rate;
    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].ast_per_rate[3].ul_value = ul_data_rate;

    pst_dmac_vap->ast_tx_mgmt_bmcast[WLAN_BAND_5G].st_rate.bit_lsig_txop = OAL_FALSE;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_vap_tx_frame_init
 ��������  : ��ʼ������������֡����֡�ķ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_frame_params(dmac_vap_stru *pst_dmac_vap, oal_bool_enum_uint8  en_mgmt_rate_init_flag)
{
    wlan_protocol_enum_uint8            en_protocol;        /* ������Э��ģʽ */
    wlan_channel_band_enum_uint8        en_band;            /* Ƶ�� */

    en_protocol  = pst_dmac_vap->st_vap_base_info.en_protocol;
    en_band      = pst_dmac_vap->st_vap_base_info.st_channel.en_band;

    if (OAL_TRUE == en_mgmt_rate_init_flag)
    {
        /* ��ʼ����������֡���� */
        dmac_vap_init_tx_mgmt_ucast(pst_dmac_vap);

        /* ��ʼ���鲥���㲥����֡���� */
        dmac_vap_init_tx_mgmt_bmcast(pst_dmac_vap);
    }

    /* ��ʼ���鲥����֡���Ͳ��� */
    dmac_vap_init_tx_data_mcast(pst_dmac_vap, en_protocol, en_band);

    /* ��ʼ���㲥����֡���Ͳ��� */
    dmac_vap_init_tx_data_bcast(pst_dmac_vap, en_protocol, en_band);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_vap_init_tx_ucast_data_frame_params
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��7��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_vap_init_tx_ucast_data_frame(dmac_vap_stru *pst_dmac_vap)
{
    switch(pst_dmac_vap->st_vap_base_info.en_protocol)
    {
        /* BPSK 1M */
        case WLAN_LEGACY_11B_MODE:
        case WLAN_MIXED_ONE_11G_MODE:
             dmac_vap_init_tx_data_ucast(pst_dmac_vap,WLAN_11B_PHY_PROTOCOL_MODE,0);
            break;

        /* OFDM 6M*/
        case WLAN_LEGACY_11A_MODE:
        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
            dmac_vap_init_tx_data_ucast(pst_dmac_vap,WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE,0xB);
            break;

        /* HT MCS0*/
        case WLAN_HT_ONLY_MODE:
        case WLAN_HT_11G_MODE:
        case WLAN_HT_MODE:
            dmac_vap_init_tx_data_ucast(pst_dmac_vap,WLAN_HT_PHY_PROTOCOL_MODE,0);
        break;

        /* VHT MCS0 */
        case WLAN_VHT_MODE:
        case WLAN_VHT_ONLY_MODE:
            dmac_vap_init_tx_data_ucast(pst_dmac_vap,WLAN_VHT_PHY_PROTOCOL_MODE,0);
             break;
        default:
            OAM_WARNING_LOG1(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                             "{dmac_vap_init_tx_ucast_data_frame::invalid en_protocol[%d].}", pst_dmac_vap->st_vap_base_info.en_protocol);
        return OAL_FAIL;
    }

    OAM_WARNING_LOG2(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_TX,
                     "{dmac_vap_init_tx_ucast_data_frame::en_protocol[%d], bit_protocol_mode:%d.}",
                     pst_dmac_vap->st_vap_base_info.en_protocol,
                     pst_dmac_vap->st_tx_alg.ast_per_rate[0].rate_bit_stru.un_nss_rate.st_legacy_rate.bit_protocol_mode);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_vap_is_host
 ��������  : �ж��Ƿ���master VAP,��Ҫexport_symbol
 �������  : pst_vap VAP�ṹ��;
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��4��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8  dmac_vap_is_host(mac_vap_stru *pst_vap)
{
    return ((dmac_vap_stru *)pst_vap)->en_is_host_vap;
}

#if 0
/*****************************************************************************
 �� �� ��  : dmac_vap_get_default_ant
 ��������  : ��ȡVAP��Ĭ�ϵ�������ϣ����ص��ǿ�����д���������е�BITMAP
 �������  : pst_vap VAP�ṹ��;
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��4��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8  dmac_vap_get_default_ant(mac_vap_stru *pst_vap)
{
    return ((dmac_vap_stru *)pst_vap)->uc_default_ant_bitmap;
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_vap_sta_reset
 ��������  : STA��ĳ��APȥ������ĸ�λ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_vap_sta_reset(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8                       auc_bssid[WLAN_MAC_ADDR_LEN] = {0, 0, 0, 0, 0, 0};
    mac_device_stru *pst_device = mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_vap_sta_reset::pst_device[%d] null!}", pst_dmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ָ�֡���˼Ĵ��� */
    //hal_disable_non_frame_filter(pst_dmac_vap->pst_hal_device);

    /* ɾ��BSSID */
    hal_set_sta_bssid(pst_dmac_vap->pst_hal_vap, auc_bssid);

    /* ֹͣSTA tsf */
    hal_disable_sta_tsf_tbtt(pst_dmac_vap->pst_hal_vap);

    /* �ָ�slottime����Ϊshort */
    hal_cfg_slottime_type(pst_dmac_vap->pst_hal_device, 0);

    /* �ָ�TXOP��ʹ��״̬ */
    if (pst_device->en_txop_enable)
    {
        pst_device->en_txop_enable = OAL_FALSE;
        hal_vap_set_machw_txop_limit_bkbe(pst_dmac_vap->pst_hal_vap,
                                          (oal_uint16)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BE].ul_dot11QAPEDCATableTXOPLimit,
                                          (oal_uint16)pst_dmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_qap_edac[WLAN_WME_AC_BK].ul_dot11QAPEDCATableTXOPLimit);
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_pause_tx
 ��������  : ��ͣVAP, ��vap״̬Ϊpause�����������жϴ�״̬: ���Ϊpause��ֹͣ����
 �������  : mac_vap_stru *pst_vap
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_pause_tx(mac_vap_stru *pst_vap)
{
    pst_vap->en_vap_state = MAC_VAP_STATE_PAUSE;

    return  OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_resume_tx
 ��������  : ʹ��VAP
 �������  : mac_vap_stru *pst_vap
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_resume_tx(mac_vap_stru *pst_vap)
{
    pst_vap->en_vap_state = MAC_VAP_STATE_UP;

    return  OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_vap_pause_tx
 ��������  : ��ͣ��VAP�ķ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_vap_pause_tx(mac_vap_stru *pst_mac_vap)
{
    dmac_vap_stru  *pst_dmac_vap;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_TX, "dmac_vap_pause_tx: dmac vap is null. vap mode:%d, vap state:%d",
                        pst_mac_vap->en_vap_mode, pst_mac_vap->en_vap_state);
        return;
    }

    if (MAC_VAP_STATE_UP != pst_mac_vap->en_vap_state)
    {
        return;
    }

    mac_vap_pause_tx(pst_mac_vap);
    hal_vap_beacon_suspend(pst_dmac_vap->pst_hal_vap);
}


/*****************************************************************************
 �� �� ��  : dmac_vap_pause_tx_by_chl
 ��������  : ���ŵ�ǰ����ͣԭ�ŵ���VAP�ķ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_vap_pause_tx_by_chl(mac_device_stru *pst_device, mac_channel_stru *pst_src_chl)
{
    oal_uint8               uc_vap_idx;
    mac_vap_stru           *pst_vap;

    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_vap_pause_tx_by_chl::pst_vap null, vap id is %d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (OAL_TRUE == mac_fcs_is_same_channel(&pst_vap->st_channel, pst_src_chl) && (MAC_VAP_STATE_UP == pst_vap->en_vap_state))
        {
            dmac_vap_pause_tx(pst_vap);
        }
    }
}

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
/*****************************************************************************
 �� �� ��  : dmac_one_packet_send_null_data
 ��������  : ͨ��one packet���Ʒ���null����
 �������  : pst_dmac_vap
             pst_dmac_user
 �������  : ��
 �� �� ֵ  : OAL_SUCC��������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��4��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_one_packet_send_null_data(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_ps)
{
    mac_fcs_mgr_stru               *pst_fcs_mgr;
    mac_fcs_cfg_stru               *pst_fcs_cfg;
    hal_one_packet_status_stru      st_status;

    pst_fcs_mgr = dmac_fcs_get_mgr_stru(pst_mac_device);
    pst_fcs_cfg = &pst_mac_device->st_fcs_cfg;

    OAL_MEMZERO(pst_fcs_cfg, OAL_SIZEOF(mac_fcs_cfg_stru));

    mac_fcs_prepare_one_packet_cfg(pst_mac_vap, &pst_fcs_cfg->st_one_packet_cfg, 20);
    mac_fcs_send_one_packet_start(pst_fcs_mgr, &pst_fcs_cfg->st_one_packet_cfg, pst_mac_device->pst_device_stru, &st_status, en_ps);

    /* ����PAֻ��Ҫ��02�Ĳ�Ʒ�д� */
    hal_disable_machw_phy_and_pa(pst_mac_device->pst_device_stru);

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    if(1 == pst_mac_device->pst_device_stru->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on)
    {
        hal_reset_phy_machw(pst_mac_device->pst_device_stru, HAL_RESET_HW_TYPE_MAC, HAL_RESET_MAC_LOGIC, OAL_FALSE, OAL_FALSE);
    }
#endif
    hal_one_packet_stop(pst_mac_device->pst_device_stru);

    hal_enable_machw_phy_and_pa(pst_mac_device->pst_device_stru);
}
#endif /* _PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV */

#ifdef _PRE_WLAN_SW_CTRL_RSP
/*****************************************************************************
 �� �� ��  : dmac_vap_update_rsp_frm_rate
 ��������  : �����������ݵ�Э��ģʽ�������������������Ӧ֡����
 �������  : uc_vap_id: vap id
             uc_protocol_mode: Э��ģʽ
             uc_bandwidth:����
             uc_ref_rate:����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��12��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_vap_update_rsp_frm_rate(oal_uint8 uc_vap_id, oal_uint8 uc_protocol_mode, oal_uint8 uc_bandwidth, oal_uint8 uc_ref_rate)
{
    mac_vap_stru                    *pst_mac_vap = OAL_PTR_NULL;
    dmac_device_stru                *pst_dmac_dev = OAL_PTR_NULL;

    pst_mac_vap = mac_res_get_mac_vap(uc_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_WARNING_LOG1(0, OAM_SF_RX, "{pst_mac_vap is NULL, fail to set rsp frm datarate, vap id[%d]}", uc_vap_id);
        return;
    }

    pst_dmac_dev = dmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_dev)
    {
        OAM_WARNING_LOG1(0, OAM_SF_RX, "{pst_dmac_dev is NULL, fail to set rsp frm datarate, dev id[%d]}", pst_mac_vap->uc_device_id);
        return;
    }

    /* ��������Ϊ11ac */
    if (WLAN_VHT_PHY_PROTOCOL_MODE == uc_protocol_mode)
    {
        /* 80M */
        if (uc_bandwidth >= WLAN_BAND_ASSEMBLE_80M)
        {
            /* ��Ӧ֡ʹ��24M���� */
            if (WLAN_PHY_RATE_24M != pst_dmac_dev->uc_rsp_frm_rate_val)
            {
                pst_dmac_dev->uc_rsp_frm_rate_val = WLAN_PHY_RATE_24M;
                hal_set_rsp_rate((oal_uint32)pst_dmac_dev->uc_rsp_frm_rate_val);
            }
        }
        /* 40M */
        else if (uc_bandwidth >= WLAN_BAND_ASSEMBLE_40M)
        {
            if (WLAN_VHT_MCS0 == uc_ref_rate)
            {
                if (WLAN_PHY_RATE_12M != pst_dmac_dev->uc_rsp_frm_rate_val)
                {
                    pst_dmac_dev->uc_rsp_frm_rate_val = WLAN_PHY_RATE_12M;
                    hal_set_rsp_rate((oal_uint32)pst_dmac_dev->uc_rsp_frm_rate_val);
                }
            }
            else
            {
                /* ��Ӧ֡ʹ��24M���� */
                if (WLAN_PHY_RATE_24M != pst_dmac_dev->uc_rsp_frm_rate_val)
                {
                    pst_dmac_dev->uc_rsp_frm_rate_val = WLAN_PHY_RATE_24M;
                    hal_set_rsp_rate((oal_uint32)pst_dmac_dev->uc_rsp_frm_rate_val);
                }
            }
        }
        /* 20M���� */
        else
        {
            if (uc_ref_rate >= WLAN_VHT_MCS3)
            {
                /* 24M */
                if (WLAN_PHY_RATE_24M != pst_dmac_dev->uc_rsp_frm_rate_val)
                {
                    pst_dmac_dev->uc_rsp_frm_rate_val = WLAN_PHY_RATE_24M;
                    hal_set_rsp_rate((oal_uint32)pst_dmac_dev->uc_rsp_frm_rate_val);
                }
            }
            else if (uc_ref_rate >= WLAN_VHT_MCS1)
            {
                /* 12M */
                if (WLAN_PHY_RATE_12M != pst_dmac_dev->uc_rsp_frm_rate_val)
                {
                    pst_dmac_dev->uc_rsp_frm_rate_val = WLAN_PHY_RATE_12M;
                    hal_set_rsp_rate((oal_uint32)pst_dmac_dev->uc_rsp_frm_rate_val);
                }
            }
            else
            {
                /* 6M */
                if (WLAN_PHY_RATE_6M != pst_dmac_dev->uc_rsp_frm_rate_val)
                {
                    pst_dmac_dev->uc_rsp_frm_rate_val = WLAN_PHY_RATE_6M;
                    hal_set_rsp_rate((oal_uint32)pst_dmac_dev->uc_rsp_frm_rate_val);
                }
            }
        }


    }
    /* 11a */
    else if (WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE == uc_protocol_mode)
    {
        if (WLAN_PHY_RATE_6M != pst_dmac_dev->uc_rsp_frm_rate_val)
        {
            pst_dmac_dev->uc_rsp_frm_rate_val = WLAN_PHY_RATE_6M;
            hal_set_rsp_rate((oal_uint32)pst_dmac_dev->uc_rsp_frm_rate_val);
        }
    }
    /* DBAC������1��VAPΪ11bʱ */
    else if (WLAN_11B_PHY_PROTOCOL_MODE == uc_protocol_mode)
    {
        if (WLAN_11B_PHY_PROTOCOL_MODE != pst_dmac_dev->uc_rsp_frm_rate_val)
        {
            pst_dmac_dev->uc_rsp_frm_rate_val = WLAN_11B_PHY_PROTOCOL_MODE;
            hal_set_rsp_rate((oal_uint32)pst_dmac_dev->uc_rsp_frm_rate_val);
        }
    }
}
#endif /* _PRE_WLAN_SW_CTRL_RSP */

/*****************************************************************************
 �� �� ��  : dmac_vap_resume_tx_by_chl
 ��������  : ���ŵ��󣬻ָ�Ŀ���ŵ���VAP�ķ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_vap_resume_tx_by_chl(mac_device_stru *pst_device, mac_channel_stru *pst_dst_channel)
{
    dmac_vap_stru                  *pst_dmac_vap;
    oal_uint8                       uc_vap_idx;
    dmac_user_stru                 *pst_dmac_user;

#ifdef _PRE_WLAN_FEATURE_STA_PM
    mac_sta_pm_handler_stru        *pst_sta_pm_handler;
#endif
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        pst_dmac_vap = mac_res_get_dmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{dmac_vap_resume_tx_by_chl::pst_dmac_vap null, vap id is %d.}",
                           pst_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if (OAL_TRUE == mac_fcs_is_same_channel(&(pst_dmac_vap->st_vap_base_info.st_channel), pst_dst_channel))
        {
#ifdef _PRE_WLAN_FEATURE_ROAM
            /* ���ص�����vap���ڵ��ŵ�ʱ������Ҫ��vap��״̬��*/
            if (MAC_VAP_STATE_ROAMING == pst_dmac_vap->st_vap_base_info.en_vap_state)
            {
                pst_dmac_user = mac_res_get_dmac_user(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id);
                if(OAL_PTR_NULL == pst_dmac_user)
                {
                    OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "{dmac_vap_resume_tx_by_chl::mac_res_get_dmac_user failed! uc_assoc_vap_id=%d. vap_mode:%d, p2p_mode:%d}",
                                            pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id,
                                            pst_dmac_vap->st_vap_base_info.en_vap_mode,
                                            mac_get_p2p_mode(&(pst_dmac_vap->st_vap_base_info)));
                    return;
                }
            #ifdef _PRE_WLAN_FEATURE_STA_PM
                pst_sta_pm_handler = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
                if (STA_GET_PM_STATE(pst_sta_pm_handler) == STA_PWR_SAVE_STATE_ACTIVE)
            #endif
                {
            #if defined(_PRE_PRODUCT_ID_HI110X_DEV)
                    dmac_one_packet_send_null_data(pst_device, &pst_dmac_vap->st_vap_base_info, OAL_FALSE);
            #else
                    dmac_psm_send_null_data(pst_dmac_vap, pst_dmac_user, OAL_FALSE);
            #endif /* */
                }
                continue;
            }
#endif //_PRE_WLAN_FEATURE_ROAM

            if (MAC_VAP_STATE_PAUSE != pst_dmac_vap->st_vap_base_info.en_vap_state)
            {
                continue;
            }

            mac_vap_resume_tx(&(pst_dmac_vap->st_vap_base_info));
            hal_vap_beacon_resume(pst_dmac_vap->pst_hal_vap);

            /* �ж�Ŀ���ŵ��ϵ�vapģʽ, �����sta����Ҫ������λ��0��null data */
            if (WLAN_VAP_MODE_BSS_STA == pst_dmac_vap->st_vap_base_info.en_vap_mode)
            {
                pst_dmac_user = mac_res_get_dmac_user(pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id);
                if(OAL_PTR_NULL == pst_dmac_user)
                {
                    OAM_WARNING_LOG3(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_DBAC, "{dmac_vap_resume_tx_by_chl::mac_res_get_dmac_user failed! uc_assoc_vap_id=%d. vap_mode:%d, p2p_mode:%d}",
                                            pst_dmac_vap->st_vap_base_info.uc_assoc_vap_id,
                                            pst_dmac_vap->st_vap_base_info.en_vap_mode,
                                            mac_get_p2p_mode(&(pst_dmac_vap->st_vap_base_info)));
                    return;
                }
            #ifdef _PRE_WLAN_FEATURE_STA_PM
                pst_sta_pm_handler = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);
                if (STA_GET_PM_STATE(pst_sta_pm_handler) == STA_PWR_SAVE_STATE_ACTIVE)
            #endif
                {
            #if defined(_PRE_PRODUCT_ID_HI110X_DEV)
                    dmac_one_packet_send_null_data(pst_device, &pst_dmac_vap->st_vap_base_info, OAL_FALSE);
            #else
                    dmac_psm_send_null_data(pst_dmac_vap, pst_dmac_user, OAL_FALSE);
            #endif /* */
                }


            }
        }
    }

    dmac_tx_complete_schedule(pst_device->pst_device_stru, WLAN_WME_AC_BE);
}

/*****************************************************************************
 �� �� ��  : dmac_vap_update_bi_from_hw
 ��������  : ��ȡӲ��beacon���ڼĴ���������mibֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��9��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_vap_update_bi_from_hw(mac_vap_stru *pst_mac_vap)
{
    /* DTS2015122404462 1151 STAUT��֧�ִ�Ӳ����Beacon���ڣ�����Ҫ�˶��� */
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    dmac_vap_stru *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0,OAM_SF_SCAN,"{dmac_vap_update_bi_from_hw::mac_res_get_dmac_vap fail.vap_id[%u]}",pst_mac_vap->uc_vap_id);
        return;
    }

    hal_vap_get_beacon_period(pst_dmac_vap->pst_hal_vap, &(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod));
#endif

}

/*****************************************************************************
 �� �� ��  : dmac_vap_is_in_p2p_listen
 ��������  : DMAC�ж��Ƿ�����p2p listen״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_vap_is_in_p2p_listen(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_mac_device;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_vap_is_in_p2p_listen::pst_mac_device[%d] null!}", pst_mac_vap->uc_device_id);
        return OAL_FALSE;
    }

    if ((MAC_SCAN_STATE_RUNNING == pst_mac_device->en_curr_scan_state) &&
         (MAC_SCAN_FUNC_P2P_LISTEN == pst_mac_device->st_scan_params.uc_scan_func))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
/*****************************************************************************
 �� �� ��  : dmac_ie_proc_opmode_notify
 ��������  : ����Operating Mode�ֶ�
 �������  : pst_mac_user: MAC USER�ṹ��ָ��
             puc_payload : ָ��Operating Mode Notification IE��ָ��
 �������  :
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��7��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32 dmac_ie_proc_opmode_notify(mac_user_stru *pst_mac_user, mac_vap_stru *pst_mac_vap, mac_opmode_notify_stru *pst_opmode_notify)
{
    oal_uint32              ul_relt;
    wlan_bw_cap_enum_uint8  en_bwcap_user = 0;                      /* user֮ǰ�Ĵ�����Ϣ */
	oal_uint8               uc_avail_bf_num_spatial_stream;         /* �û�֧�ֵ�Beamforming�ռ������� */
    oal_uint8               uc_avail_num_spatial_stream;            /* Tx��Rx֧��Nss�Ľ���,���㷨���� */

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_mac_user) || (OAL_PTR_NULL == pst_opmode_notify))
    {
        OAM_ERROR_LOG3(0, OAM_SF_RX, "{dmac_ie_proc_opmode_notify::param null,pst_mac_vap[%p],pst_hmac_user[%p],pst_opmode_notify[%p]!}",
                        pst_mac_vap, pst_mac_user, pst_opmode_notify);
        return OAL_ERR_CODE_PTR_NULL;
    }

    en_bwcap_user = pst_mac_user->en_avail_bandwidth;
    uc_avail_num_spatial_stream = pst_mac_user->uc_avail_num_spatial_stream;
    uc_avail_bf_num_spatial_stream = pst_mac_user->uc_avail_bf_num_spatial_stream;

    ul_relt = mac_ie_proc_opmode_field(pst_mac_vap, pst_mac_user, pst_opmode_notify);
    if (OAL_UNLIKELY(OAL_SUCC != ul_relt))
    {
        OAM_WARNING_LOG1(pst_mac_user->uc_vap_id, OAM_SF_RX, "{dmac_ie_proc_opmode_notify::mac_ie_proc_opmode_field failed[%d].}", ul_relt);
        return ul_relt;
    }

    /* opmode����ı�֪ͨ�㷨,��ͬ��������Ϣ��HOST */
    if (pst_mac_user->en_avail_bandwidth != en_bwcap_user)
    {

        /* user��������㷨�ı����֪ͨ�� */
        dmac_alg_cfg_user_bandwidth_notify(pst_mac_vap, pst_mac_user);

        if (OAL_SUCC != dmac_config_d2h_user_info_syn(pst_mac_vap, pst_mac_user))
        {
            OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                   "{dmac_ie_proc_opmode_notify::dmac_d2h_user_info_syn failed.}");
        }
    }

    if ((pst_mac_user->uc_avail_bf_num_spatial_stream != uc_avail_bf_num_spatial_stream) ||
          (pst_mac_user->uc_avail_num_spatial_stream != uc_avail_num_spatial_stream))
    {
        /* �����㷨���Ӻ��� */
        dmac_alg_cfg_user_spatial_stream_notify(pst_mac_user);
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_check_opmode_notify
 ��������  : ������������STA��Operating Mode Notification
 �������  : hmac_vap_stru    *pst_hmac_vap --VAPָ��
             oal_uint8        *puc_mac_hdr, --֡ͷָ��
             oal_uint8        *puc_payload  --payloadָ��
             oal_uint16        us_info_elem_offset--ƫ�Ƴ���
             oal_uint32        ul_msg_len----��Ϣ����
             hmac_user_stru   *pst_hmac_user_sta --�û�ָ��
 �������  : ��
 �� �� ֵ  : oal_uint16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��10��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32 dmac_check_opmode_notify(
                mac_vap_stru                   *pst_mac_vap,
                oal_uint8                       *puc_payload,
                oal_uint32                       ul_msg_len,
                mac_user_stru                   *pst_mac_user)
{
    mac_opmode_notify_stru *pst_opmode_notify = OAL_PTR_NULL;
    oal_uint8              *puc_opmode_notify_ie;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_payload) || (OAL_PTR_NULL == pst_mac_user))
    {
        OAM_ERROR_LOG3(0, OAM_SF_RX, "{dmac_check_opmode_notify::param null,pst_mac_vap[%p], puc_payload[%p], pst_hmac_user[%p]!}",
                        pst_mac_vap, puc_payload, pst_mac_user);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((OAL_FALSE == mac_mib_get_VHTOptionImplemented(pst_mac_vap))
        || (OAL_FALSE == mac_mib_get_OperatingModeNotificationImplemented(pst_mac_vap)))
    {
        return OAL_SUCC;
    }

    puc_opmode_notify_ie = mac_find_ie(MAC_EID_OPMODE_NOTIFY, puc_payload, (oal_int32)(ul_msg_len));
    if (OAL_PTR_NULL == puc_opmode_notify_ie)
    {
        return OAL_SUCC;
    }

    if (puc_opmode_notify_ie[1] < MAC_OPMODE_NOTIFY_LEN)
    {
        OAM_WARNING_LOG1(0, OAM_SF_RX, "{dmac_check_opmode_notify::invalid opmode notify ie len[%d]!}", puc_opmode_notify_ie[1]);
        return OAL_SUCC;
    }

    pst_opmode_notify = (mac_opmode_notify_stru *)(puc_opmode_notify_ie + MAC_IE_HDR_LEN);

    return dmac_ie_proc_opmode_notify(pst_mac_user,pst_mac_vap,pst_opmode_notify);
}
#endif




/*lint -e578*//*lint -e19*/
oal_module_symbol(dmac_vap_is_host);
#if 0
oal_module_symbol(dmac_vap_get_default_ant);
#endif
oal_module_symbol(mac_vap_pause_tx);
oal_module_symbol(mac_vap_resume_tx);
oal_module_symbol(dmac_vap_pause_tx_by_chl);
oal_module_symbol(dmac_vap_resume_tx_by_chl);
oal_module_symbol(dmac_vap_update_bi_from_hw);
/*lint +e578*//*lint +e19*/









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

