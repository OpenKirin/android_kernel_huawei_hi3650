/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wal_config.c
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2012��11��6��
  ����޸�   :
  ��������   : WAL���ò���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��6��
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
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "wlan_types.h"

#include "mac_device.h"
#include "mac_vap.h"
#include "mac_resource.h"
//#include "mac_11i.h"

#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_scan.h"
#include "hmac_ext_if.h"
#include "hmac_config.h"
#include "wal_ext_if.h"
#include "wal_main.h"
#include "wal_config.h"
#include "wal_linux_bridge.h"
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)

#include "hmac_cali_mgmt.h"
#endif

#ifdef _PRE_WLAN_CHIP_TEST
#include "hmac_test_main.h"
#endif

#ifdef _PRE_WLAN_DFT_REG
#include "hal_witp_debug.h"
#endif

#ifdef _PRE_WLAN_FEATURE_MCAST
#include "hmac_m2u.h"
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
#include "hmac_proxy_arp.h"
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
#include "hmac_wapi.h"
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_pm_wlan.h"
#endif
#ifdef _PRE_WLAN_FEATURE_HILINK
#include "hmac_fbt_main.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_CONFIG_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* ��̬�������� */
OAL_STATIC oal_uint32  wal_config_add_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_del_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_down_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_start_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_bandwidth(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_mac_addr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_concurrent(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_concurrent(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_bss_type(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_bss_type(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_ssid(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_ssid(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_shortgi20(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_shortgi20(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_shortgi40(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_shortgi40(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_shortgi80(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_shortgi80(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_MONITOR
OAL_STATIC oal_uint32  wal_config_get_addr_filter(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_addr_filter(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
OAL_STATIC oal_uint32  wal_config_get_prot_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_prot_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_auth_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_auth_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_bintval(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_bintval(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_nobeacon(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_nobeacon(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_txchain(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_txchain(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_rxchain(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_rxchain(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_txpower(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_txpower(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_freq(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_freq(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_wmm_params(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_vap_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_BTCOEX
OAL_STATIC oal_uint32 wal_config_print_btcoex_status(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_LTECOEX
OAL_STATIC oal_uint32 wal_config_ltecoex_mode_set(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC oal_uint32  wal_config_lte_gpio_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_wfa_cfg_aifsn(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_wfa_cfg_cw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#endif

#if 0
OAL_STATIC oal_uint32  wal_config_ota_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
OAL_STATIC oal_uint32  wal_config_set_random_mac_addr_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_random_mac_oui(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_add_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_del_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_sta_list(mac_vap_stru *pst_mac_vap, oal_uint16 *us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_rd_pwr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_reduce_sar(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_kick_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_dump_all_rx_dscr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_FEATURE_SMPS
OAL_STATIC oal_uint32  wal_config_set_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_smps_en(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
#endif


#ifdef _PRE_WLAN_FEATURE_UAPSD
OAL_STATIC oal_uint32  wal_config_set_uapsd_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_uapsd_en(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);

#endif

OAL_STATIC oal_uint32  wal_config_set_country(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_country_for_dfs(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_country(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_tid(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_beacon(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

OAL_STATIC oal_uint32 wal_config_add_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_get_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_remove_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_set_default_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_scan_abort(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_cfg80211_start_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_cfg80211_stop_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_cfg80211_start_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_cfg80211_start_join(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_alg_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#if 0
OAL_STATIC oal_uint32  wal_config_tdls_prohibited(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_tdls_channel_switch_prohibited(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
OAL_STATIC oal_uint32  wal_config_rx_fcs_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_FEATURE_DFS
OAL_STATIC oal_uint32  wal_config_dfs_radartool(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

OAL_STATIC oal_uint32  wal_config_frag_threshold(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_rts_threshold(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_VOWIFI
OAL_STATIC oal_uint32  wal_config_vowifi_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif /* _PRE_WLAN_FEATURE_VOWIFI */
#ifdef _PRE_WLAN_FEATURE_SMARTANT
OAL_STATIC oal_uint32  wal_config_get_ant_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_double_ant_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
OAL_STATIC oal_uint32  wal_config_user_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_dscr_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
//#ifdef    _PRE_WLAN_CHIP_TEST

OAL_STATIC oal_uint32  wal_config_set_log_level(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC oal_uint32 wal_config_set_pm_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_set_ant(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_ant(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
OAL_STATIC oal_uint32  wal_config_set_rate(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_mcs(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_mcsac(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_bw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
OAL_STATIC oal_uint32 wal_config_always_tx_1102(mac_vap_stru * pst_mac_vap, oal_uint16 us_len, oal_uint8 * puc_param);
#endif
OAL_STATIC oal_uint32  wal_config_always_rx(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_pcie_pm_level(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_reg_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#if (defined(_PRE_PRODUCT_ID_HI110X_DEV) || defined(_PRE_PRODUCT_ID_HI110X_HOST))
OAL_STATIC oal_uint32  wal_config_sdio_flowctrl(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
OAL_STATIC oal_uint32  wal_config_reg_write(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);



#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
OAL_STATIC oal_uint32  wal_config_set_edca_opt_weight_sta(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_edca_opt_switch_sta(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_edca_opt_switch_ap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_edca_opt_cycle_ap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

OAL_STATIC oal_uint32  wal_config_open_wmm(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_get_version(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

OAL_STATIC oal_uint32 wal_config_set_wps_p2p_ie(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_set_wps_ie(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
OAL_STATIC oal_uint32  wal_config_blacklist_add(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_blacklist_add_only(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_blacklist_del(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_blacklist_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_blacklist_show(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
OAL_STATIC oal_uint32  wal_config_proxyarp_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
OAL_STATIC oal_uint32 wal_config_set_pmksa(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_del_pmksa(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_flush_pmksa(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_remain_on_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_cancel_remain_on_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_mgmt_tx(mac_vap_stru * pst_mac_vap, oal_uint16 us_len, oal_uint8 * puc_param);

OAL_STATIC oal_uint32 wal_config_query_station_stats(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_query_rssi(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_query_rate(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_DFT_STAT
OAL_STATIC oal_uint32  wal_config_query_ani(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_HS20
OAL_STATIC oal_uint32  wal_config_set_qos_map(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
OAL_STATIC oal_uint32  wal_config_set_p2p_ps_ops(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_p2p_ps_noa(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_STA_PM
OAL_STATIC oal_uint32  wal_config_set_sta_pm_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#ifdef _PRE_PSM_DEBUG_MODE
OAL_STATIC oal_uint32  wal_config_show_pm_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
OAL_STATIC oal_uint32  wal_config_set_sta_pm_on(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
OAL_STATIC oal_uint32  wal_config_set_auto_freq_value(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
OAL_STATIC oal_uint32 wal_config_set_uapsd_para(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

OAL_STATIC oal_uint32  wal_config_set_max_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC oal_uint32 wal_config_cfg_vap_h2d(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_host_dev_init(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_host_dev_exit(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

oal_uint32 wal_send_cali_data(oal_net_device_stru *pst_net_dev);

#endif

#ifdef _PRE_WLAN_FEATURE_11R
OAL_STATIC oal_uint32  wal_config_set_ft_ies(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif //_PRE_WLAN_FEATURE_11R

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
OAL_STATIC oal_uint32  wal_config_get_lauch_cap(mac_vap_stru *pst_mac_vap, oal_uint16 *us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_linkloss_threshold(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_all_log_level(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_d2h_hcc_assemble_cnt(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_chn_est_ctrl(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_power_ref(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_pm_cfg_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_cus_rf(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_cus_dts_cali(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_set_cus_nvram_params(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_dev_customize_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */
OAL_STATIC oal_uint32  wal_config_vap_destroy(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
OAL_STATIC oal_uint32  wal_config_set_txrx_chain(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_HILINK
OAL_STATIC oal_uint32 wal_config_set_okc_ie(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32 wal_config_fbt_kick_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
oal_uint32 wal_config_get_all_sta_info(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
OAL_STATIC oal_uint32  wal_config_fbt_start_scan(mac_vap_stru * pst_mac_vap, oal_uint16 us_len, oal_uint8 * puc_param);
#endif

#ifdef _PRE_WLAN_FEATURE_11K
OAL_STATIC oal_uint32  wal_config_send_neighbor_req(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

OAL_STATIC oal_uint32  wal_config_vendor_cmd_get_channel_list(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);

#ifdef _PRE_WLAN_RF_CALI
OAL_STATIC oal_uint32  wal_config_auto_cali(mac_vap_stru * pst_mac_vap, oal_uint16 us_len, oal_uint8 * puc_param);
OAL_STATIC oal_uint32  wal_config_set_cali_vref(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
oal_atomic g_wal_config_seq_num = ATOMIC_INIT(0);
oal_module_symbol(g_wal_config_seq_num);
#else
oal_atomic g_wal_config_seq_num = 0;
#endif
#ifdef _PRE_WLAN_CFGID_DEBUG
extern OAL_CONST wal_wid_op_stru g_ast_board_wid_op_debug[];
extern oal_uint32 wal_config_get_debug_wid_arrysize(oal_void);
#endif
#ifdef _PRE_WLAN_FEATURE_GREEN_AP
OAL_STATIC oal_uint32 wal_config_set_green_ap_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
/* cfgid����ȫ�ֱ��� */
OAL_STATIC OAL_CONST wal_wid_op_stru g_ast_board_wid_op[] =
{
     /* cfgid                   �Ƿ�λmac  ����һ�ֽ�   get����              set���� */
    {WLAN_CFGID_BSS_TYPE,          OAL_TRUE,   {0},   wal_config_get_bss_type,   wal_config_set_bss_type},
    {WLAN_CFGID_ADD_VAP,           OAL_FALSE,  {0},   OAL_PTR_NULL,              wal_config_add_vap},
    {WLAN_CFGID_START_VAP,         OAL_FALSE,  {0},   OAL_PTR_NULL,              wal_config_start_vap},
    {WLAN_CFGID_DEL_VAP,           OAL_FALSE,  {0},   OAL_PTR_NULL,              wal_config_del_vap},
    {WLAN_CFGID_DOWN_VAP,          OAL_FALSE,  {0},   OAL_PTR_NULL,              wal_config_down_vap},
    {WLAN_CFGID_MODE,              OAL_FALSE,  {0},   wal_config_get_mode,       wal_config_set_mode},
    {WLAN_CFGID_BANDWIDTH,         OAL_FALSE,  {0},   OAL_PTR_NULL,              wal_config_set_bandwidth},

    {WLAN_CFGID_CURRENT_CHANEL,    OAL_FALSE,  {0},   wal_config_get_freq,       wal_config_set_freq},
    {WLAN_CFGID_STATION_ID,        OAL_TRUE,   {0},   OAL_PTR_NULL,              wal_config_set_mac_addr},
    {WLAN_CFGID_CONCURRENT,        OAL_TRUE,   {0},   wal_config_get_concurrent, wal_config_set_concurrent},
    {WLAN_CFGID_SSID,              OAL_FALSE,  {0},   wal_config_get_ssid,       wal_config_set_ssid},
    {WLAN_CFGID_SHORTGI,           OAL_FALSE,  {0},   wal_config_get_shortgi20,  wal_config_set_shortgi20},
    {WLAN_CFGID_SHORTGI_FORTY,     OAL_FALSE,  {0},   wal_config_get_shortgi40,  wal_config_set_shortgi40},
    {WLAN_CFGID_SHORTGI_EIGHTY,    OAL_FALSE,  {0},   wal_config_get_shortgi80,  wal_config_set_shortgi80},

    {WLAN_CFGID_SHORT_PREAMBLE,    OAL_FALSE,  {0},   wal_config_get_shpreamble, wal_config_set_shpreamble},
#ifdef _PRE_WLAN_FEATURE_MONITOR
    {WLAN_CFGID_ADDR_FILTER,       OAL_FALSE,  {0},   wal_config_get_addr_filter,wal_config_set_addr_filter},
#endif
    {WLAN_CFGID_PROT_MODE,         OAL_FALSE,  {0},   wal_config_get_prot_mode,  wal_config_set_prot_mode},
    {WLAN_CFGID_AUTH_MODE,         OAL_FALSE,  {0},   wal_config_get_auth_mode,  wal_config_set_auth_mode},
    {WLAN_CFGID_BEACON_INTERVAL,   OAL_FALSE,  {0},   wal_config_get_bintval,    wal_config_set_bintval},
    {WLAN_CFGID_NO_BEACON,         OAL_FALSE,  {0},   wal_config_get_nobeacon,   wal_config_set_nobeacon},
    {WLAN_CFGID_TX_CHAIN,          OAL_FALSE,  {0},   wal_config_get_txchain,    wal_config_set_txchain},
    {WLAN_CFGID_RX_CHAIN,          OAL_FALSE,  {0},   wal_config_get_rxchain,    wal_config_set_rxchain},
    {WLAN_CFGID_TX_POWER,          OAL_FALSE,  {0},   wal_config_get_txpower,    wal_config_set_txpower},
#ifdef _PRE_WLAN_FEATURE_SMPS
    {WLAN_CFGID_SMPS_MODE,         OAL_FALSE,  {0},   wal_config_get_smps_mode,  wal_config_set_smps_mode},
    {WLAN_CFGID_SMPS_EN,           OAL_FALSE,  {0},   wal_config_get_smps_en,    OAL_PTR_NULL},
#endif
#ifdef _PRE_WLAN_FEATURE_UAPSD
    {WLAN_CFGID_UAPSD_EN,          OAL_FALSE,  {0},   wal_config_get_uapsd_en,   wal_config_set_uapsd_en},
#endif
    {WLAN_CFGID_DTIM_PERIOD,       OAL_FALSE,  {0},   wal_config_get_dtimperiod, wal_config_set_dtimperiod},

    {WLAN_CFGID_EDCA_TABLE_CWMIN,          OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_EDCA_TABLE_CWMAX,          OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_EDCA_TABLE_AIFSN,          OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_EDCA_TABLE_TXOP_LIMIT,     OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_EDCA_TABLE_MSDU_LIFETIME,  OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_EDCA_TABLE_MANDATORY,      OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_QEDCA_TABLE_CWMIN,         OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_QEDCA_TABLE_CWMAX,         OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_QEDCA_TABLE_AIFSN,         OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_QEDCA_TABLE_TXOP_LIMIT,    OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_QEDCA_TABLE_MSDU_LIFETIME, OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},
    {WLAN_CFGID_QEDCA_TABLE_MANDATORY,     OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_set_wmm_params},

    {WLAN_CFGID_VAP_INFO,               OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_vap_info},

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    {WLAN_CFGID_BTCOEX_STATUS_PRINT,    OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_print_btcoex_status},
#endif
#ifdef _PRE_WLAN_FEATURE_LTECOEX
    {WLAN_CFGID_LTECOEX_MODE_SET,    	OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_ltecoex_mode_set},
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_WFA_CFG_AIFSN,        OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_wfa_cfg_aifsn},
    {WLAN_CFGID_WFA_CFG_CW,        OAL_FALSE,  {0},    OAL_PTR_NULL,                wal_config_wfa_cfg_cw},
    {WLAN_CFGID_CHECK_LTE_GPIO,              OAL_FALSE,  {0},   OAL_PTR_NULL,        wal_config_lte_gpio_mode},

#endif
#if 0
    {WLAN_CFGID_OTA_SWITCH,             OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_ota_switch},
#endif
    {WLAN_CFGID_SET_RANDOM_MAC_ADDR_SCAN, OAL_FALSE,  {0},    OAL_PTR_NULL,          wal_config_set_random_mac_addr_scan},
    {WLAN_CFGID_SET_RANDOM_MAC_OUI,     OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_random_mac_oui},
    {WLAN_CFGID_ADD_USER,               OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_add_user},
    {WLAN_CFGID_DEL_USER,               OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_del_user},
    {WLAN_CFGID_SET_LOG_LEVEL,          OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_log_level},
#ifdef _PRE_WLAN_FEATURE_GREEN_AP
    {WLAN_CFGID_GREEN_AP_EN,            OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_green_ap_en},
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_SET_PM_SWITCH,          OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_pm_switch},
    {WLAN_CFGID_SET_ANT,          OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_ant},
    {WLAN_CFGID_GET_ANT,        OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_get_ant},
#endif
    {WLAN_CFGID_DUMP_ALL_RX_DSCR,       OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_dump_all_rx_dscr},
    {WLAN_CFGID_KICK_USER,              OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_kick_user},
    {WLAN_CFGID_COUNTRY,                OAL_FALSE,  {0},    wal_config_get_country,  wal_config_set_country},
    {WLAN_CFGID_COUNTRY_FOR_DFS,        OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_country_for_dfs},
    {WLAN_CFGID_TID,                    OAL_FALSE,  {0},    wal_config_get_tid,      OAL_PTR_NULL},


#if 0
    {WLAN_CFGID_TDLS_PROHI,             OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_tdls_prohibited},
    {WLAN_CFGID_TDLS_CHASWI_PROHI,      OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_tdls_channel_switch_prohibited},
#endif
    {WLAN_CFGID_FRAG_THRESHOLD_REG,     OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_frag_threshold},
    {WLAN_CFGID_RX_FCS_INFO,            OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_rx_fcs_info},

#ifdef _PRE_WLAN_FEATURE_DFS
    {WLAN_CFGID_RADARTOOL,              OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_dfs_radartool},
#endif

    {WLAN_CFGID_REGDOMAIN_PWR,          OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_rd_pwr},
    {WLAN_CFGID_USER_INFO,              OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_user_info},
    {WLAN_CFGID_SET_DSCR,               OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_dscr_param},
/*#ifdef _PRE_WLAN_CHIP_TEST  */
    {WLAN_CFGID_SET_RATE,               OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_rate},
    {WLAN_CFGID_SET_MCS,                OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_mcs},
    {WLAN_CFGID_SET_MCSAC,              OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_mcsac},
    {WLAN_CFGID_SET_BW,                 OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_bw},
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    {WLAN_CFGID_SET_ALWAYS_TX_1102,     OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_always_tx_1102},
#endif
    {WLAN_CFGID_SET_ALWAYS_RX,          OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_always_rx},
    {WLAN_CFGID_PCIE_PM_LEVEL,          OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_pcie_pm_level},

    {WLAN_CFGID_REG_INFO,               OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_reg_info},
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV) || defined(_PRE_PRODUCT_ID_HI110X_HOST))
    {WLAN_CFGID_SDIO_FLOWCTRL,          OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_sdio_flowctrl},
#endif
    {WLAN_CFGID_REG_WRITE,               OAL_FALSE,  {0},    OAL_PTR_NULL,           wal_config_reg_write},

    {WLAN_CFGID_SCAN_ABORT,               OAL_FALSE,  {0},    OAL_PTR_NULL,      wal_config_scan_abort},
    /* ����Ϊ�ں�cfg80211���õ����� */
    {WLAN_CFGID_CFG80211_START_SCHED_SCAN,OAL_FALSE,  {0},    OAL_PTR_NULL,      wal_config_cfg80211_start_sched_scan},
    {WLAN_CFGID_CFG80211_STOP_SCHED_SCAN, OAL_FALSE,  {0},    OAL_PTR_NULL,      wal_config_cfg80211_stop_sched_scan},
    {WLAN_CFGID_CFG80211_START_SCAN,      OAL_FALSE,  {0},    OAL_PTR_NULL,      wal_config_cfg80211_start_scan},
    {WLAN_CFGID_CFG80211_START_CONNECT,   OAL_FALSE,  {0},    OAL_PTR_NULL,      wal_config_cfg80211_start_join},
    {WLAN_CFGID_CFG80211_SET_CHANNEL,     OAL_FALSE,  {0},    OAL_PTR_NULL,      wal_config_set_channel},
    {WLAN_CFGID_CFG80211_CONFIG_BEACON,   OAL_FALSE,  {0},    OAL_PTR_NULL,      wal_config_set_beacon},


    {WLAN_CFGID_ADD_KEY,           OAL_FALSE,  {0},   OAL_PTR_NULL,              wal_config_add_key},
    {WLAN_CFGID_GET_KEY,           OAL_FALSE,  {0},   OAL_PTR_NULL,              wal_config_get_key},
    {WLAN_CFGID_REMOVE_KEY,        OAL_FALSE,  {0},   OAL_PTR_NULL,              wal_config_remove_key},

    {WLAN_CFGID_ALG_PARAM,         OAL_FALSE,  {0},   OAL_PTR_NULL,              wal_config_alg_param},


#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    {WLAN_CFGID_EDCA_OPT_SWITCH_STA,  OAL_FALSE,  {0},   OAL_PTR_NULL,           wal_config_set_edca_opt_switch_sta},
    {WLAN_CFGID_EDCA_OPT_WEIGHT_STA,  OAL_FALSE,  {0},   OAL_PTR_NULL,           wal_config_set_edca_opt_weight_sta},
    {WLAN_CFGID_EDCA_OPT_SWITCH_AP,   OAL_FALSE,  {0},   OAL_PTR_NULL,           wal_config_set_edca_opt_switch_ap},
    {WLAN_CFGID_EDCA_OPT_CYCLE_AP,    OAL_FALSE,  {0},   OAL_PTR_NULL,           wal_config_set_edca_opt_cycle_ap},
#endif

    /* START:��ԴAPP �����·���˽������ */
    {WLAN_CFGID_GET_ASSOC_REQ_IE,  OAL_FALSE,  {0},   wal_config_get_assoc_req_ie,   OAL_PTR_NULL},
    {WLAN_CFGID_SET_WPS_IE,        OAL_FALSE,  {0},   OAL_PTR_NULL,             wal_config_set_wps_ie},
    {WLAN_CFGID_SET_RTS_THRESHHOLD,OAL_FALSE,  {0},   OAL_PTR_NULL,             wal_config_rts_threshold},
#ifdef _PRE_WLAN_FEATURE_VOWIFI
    {WLAN_CFGID_VOWIFI_INFO,       OAL_FALSE,  {0},   OAL_PTR_NULL,             wal_config_vowifi_info},
#endif
#ifdef _PRE_WLAN_FEATURE_SMARTANT
    {WLAN_CFGID_GET_ANT_INFO,           OAL_FALSE,  {0},   OAL_PTR_NULL,             wal_config_get_ant_info},
    {WLAN_CFGID_DOUBLE_ANT_SW,          OAL_FALSE,  {0},   OAL_PTR_NULL,             wal_config_double_ant_switch},
#endif
#ifdef _PRE_WLAN_FEATURE_HILINK
    {WLAN_CFGID_SET_OKC_IE,        OAL_FALSE,  {0},   OAL_PTR_NULL,             wal_config_set_okc_ie},
    {WLAN_CFGID_FBT_KICK_USER,     OAL_FALSE,  {0},   OAL_PTR_NULL,             wal_config_fbt_kick_user},
#endif
    /* END:��ԴAPP �����·���˽������ */

    {WLAN_CFGID_DEFAULT_KEY,        OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_set_default_key},

    {WLAN_CFGID_WMM_SWITCH,         OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_open_wmm},

    {WLAN_CFGID_GET_VERSION,        OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_get_version},

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
    /* ���������� */
    {WLAN_CFGID_ADD_BLACK_LIST          ,OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_blacklist_add},
    {WLAN_CFGID_DEL_BLACK_LIST          ,OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_blacklist_del},
    {WLAN_CFGID_BLACKLIST_MODE          ,OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_set_blacklist_mode},
    {WLAN_CFGID_BLACKLIST_SHOW          ,OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_blacklist_show},

    {WLAN_CFGID_ADD_BLACK_LIST_ONLY    ,OAL_FALSE,  {0},   OAL_PTR_NULL,      wal_config_blacklist_add_only},

#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
    {WLAN_CFGID_PROXYARP_EN             ,OAL_FALSE,  {0},    OAL_PTR_NULL,          wal_config_proxyarp_en},
#endif
    {WLAN_CFGID_CFG80211_SET_PMKSA,        OAL_FALSE,  {0},    OAL_PTR_NULL,     wal_config_set_pmksa},
    {WLAN_CFGID_CFG80211_DEL_PMKSA,        OAL_FALSE,  {0},    OAL_PTR_NULL,     wal_config_del_pmksa},
    {WLAN_CFGID_CFG80211_FLUSH_PMKSA,      OAL_FALSE,  {0},    OAL_PTR_NULL,     wal_config_flush_pmksa},

    {WLAN_CFGID_SET_WPS_P2P_IE,                    OAL_FALSE,  {0},    OAL_PTR_NULL,     wal_config_set_wps_p2p_ie},
    {WLAN_CFGID_CFG80211_REMAIN_ON_CHANNEL,        OAL_FALSE,  {0},    OAL_PTR_NULL,     wal_config_remain_on_channel},
    {WLAN_CFGID_CFG80211_CANCEL_REMAIN_ON_CHANNEL, OAL_FALSE,  {0},    OAL_PTR_NULL,     wal_config_cancel_remain_on_channel},
    {WLAN_CFGID_CFG80211_MGMT_TX,   OAL_FALSE,  {0},    OAL_PTR_NULL,           wal_config_mgmt_tx},

    {WLAN_CFGID_QUERY_STATION_STATS,   OAL_FALSE,  {0},    OAL_PTR_NULL,           wal_config_query_station_stats},

    {WLAN_CFGID_QUERY_RSSI,             OAL_FALSE,  {0},    OAL_PTR_NULL,           wal_config_query_rssi},
    {WLAN_CFGID_QUERY_RATE,             OAL_FALSE,  {0},    OAL_PTR_NULL,           wal_config_query_rate},

#ifdef _PRE_WLAN_DFT_STAT
    {WLAN_CFGID_QUERY_ANI,              OAL_FALSE,  {0},    OAL_PTR_NULL,           wal_config_query_ani},
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
    {WLAN_CFGID_SET_PS_MODE,           OAL_FALSE,  {0},   OAL_PTR_NULL,         wal_config_set_sta_pm_mode},
#ifdef _PRE_PSM_DEBUG_MODE
    {WLAN_CFGID_SHOW_PS_INFO,          OAL_FALSE,  {0},   OAL_PTR_NULL,         wal_config_show_pm_info},
#endif
    {WLAN_CFGID_SET_STA_PM_ON,          OAL_FALSE,  {0},   OAL_PTR_NULL,         wal_config_set_sta_pm_on},
#endif

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    {WLAN_CFGID_SET_UAPSD_PARA,        OAL_FALSE, {0},      OAL_PTR_NULL,       wal_config_set_uapsd_para},
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
    {WLAN_CFGID_SET_P2P_PS_OPS,     OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_set_p2p_ps_ops},
    {WLAN_CFGID_SET_P2P_PS_NOA,     OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_set_p2p_ps_noa},
#endif
#ifdef _PRE_WLAN_FEATURE_HS20
    {WLAN_CFGID_SET_QOS_MAP,        OAL_FALSE,  {0},   OAL_PTR_NULL,            wal_config_set_qos_map},
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {WLAN_CFGID_CFG_VAP_H2D,  OAL_FALSE,    {0},    OAL_PTR_NULL,            wal_config_cfg_vap_h2d},
    {WLAN_CFGID_HOST_DEV_INIT,  OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_host_dev_init},
    {WLAN_CFGID_HOST_DEV_EXIT,  OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_host_dev_exit},
#endif
    {WLAN_CFGID_SET_MAX_USER,        OAL_FALSE,  {0},    OAL_PTR_NULL,            wal_config_set_max_user},
    {WLAN_CFGID_GET_STA_LIST,        OAL_FALSE,  {0},    wal_config_get_sta_list, OAL_PTR_NULL},
#ifdef _PRE_WLAN_FEATURE_11R
    {WLAN_CFGID_SET_FT_IES,  OAL_FALSE,  {0},    OAL_PTR_NULL,             wal_config_set_ft_ies},
#endif //_PRE_WLAN_FEATURE_11R

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    {WLAN_CFGID_SET_DEVICE_FREQ_VALUE,        OAL_FALSE,  {0},  OAL_PTR_NULL,     wal_config_set_auto_freq_value},
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    {WLAN_CFGID_LAUCH_CAP,                 OAL_FALSE,  {0},  wal_config_get_lauch_cap, OAL_PTR_NULL},
    {WLAN_CFGID_SET_LINKLOSS_THRESHOLD,    OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_set_linkloss_threshold},
    {WLAN_CFGID_SET_ALL_LOG_LEVEL,         OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_set_all_log_level},
    {WLAN_CFGID_SET_D2H_HCC_ASSEMBLE_CNT,  OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_set_d2h_hcc_assemble_cnt},
    {WLAN_CFGID_SET_CHN_EST_CTRL,          OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_set_chn_est_ctrl},
    {WLAN_CFGID_SET_POWER_REF,             OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_set_power_ref},
    {WLAN_CFGID_SET_PM_CFG_PARAM,          OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_set_pm_cfg_param},
    {WLAN_CFGID_SET_CUS_RF,                OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_set_cus_rf},
    {WLAN_CFGID_SET_CUS_DTS_CALI,          OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_set_cus_dts_cali},
    {WLAN_CFGID_SET_CUS_NVRAM_PARAM,       OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_set_cus_nvram_params},
    /* SHOW DEIVCE CUSTOMIZE INFOS */
    {WLAN_CFGID_SHOW_DEV_CUSTOMIZE_INFOS,  OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_dev_customize_info},
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

    {WLAN_CFGID_DESTROY_VAP,     OAL_FALSE,  {0},    OAL_PTR_NULL,         wal_config_vap_destroy},

    {WLAN_CFGID_REDUCE_SAR,     OAL_FALSE,  {0},    OAL_PTR_NULL,       wal_config_reduce_sar},
#ifdef _PRE_WLAN_FEATURE_HILINK
    {WLAN_CFGID_FBT_START_SCAN,                 OAL_FALSE,  {0},    OAL_PTR_NULL,         wal_config_fbt_start_scan},
#endif

#ifdef _PRE_WLAN_FEATURE_11K
    {WLAN_CFGID_SEND_NEIGHBOR_REQ,             OAL_FALSE,  {0},  OAL_PTR_NULL,        wal_config_send_neighbor_req},
#endif

    {WLAN_CFGID_VENDOR_CMD_GET_CHANNEL_LIST,   OAL_FALSE,  {0},  wal_config_vendor_cmd_get_channel_list, OAL_PTR_NULL},

#ifdef _PRE_WLAN_RF_CALI
    {WLAN_CFGID_AUTO_CALI,       OAL_FALSE,  {0},    OAL_PTR_NULL,           wal_config_auto_cali},
    {WLAN_CFGID_SET_CALI_VREF,   OAL_FALSE,  {0},    OAL_PTR_NULL,           wal_config_set_cali_vref},
#endif

    {WLAN_CFGID_BUTT,                  OAL_FALSE,  {0},    0,                       0},
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : wal_config_add_vap
 ��������  : ����VAP
 �������  : pst_mac_vap  : ָ��mac_vap��ָ��
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_add_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32 ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param)))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_config_add_vap(pst_mac_vap, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        return ul_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_config_del_vap
 ��������  : ɾ��vap
 �������  : pst_mac_vap  : ָ��mac_vap��ָ��
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��14��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_del_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32         ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_config_del_vap::pst_mac_vap or puc_param null ptr error [%d], [%d]}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_config_del_vap(pst_mac_vap, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_config_del_vap:: return error code [%d].}\r\n", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_config_start_vap
 ��������  : ����VAP
 �������  : pst_mac_vap : ָ��vap
             us_len      : ��������
             puc_param   : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��14��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_start_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_config_start_vap::pst_mac_vap or puc_param null ptr error %d,%d.}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_config_start_vap(pst_mac_vap, us_len, puc_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_start_vap:: return error code %d.}\r\n", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_config_down_vap
 ��������  : ͣ��vap
 �������  : pst_mac_vap : ָ��vap
             us_len      : ��������
             puc_param   : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��13��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_down_vap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32    ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_config_down_vap::pst_mac_vap or puc_param null ptr error [%x],[%x].}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_config_down_vap(pst_mac_vap, us_len, puc_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_down_vap:: return error code [%d].}\r\n", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_config_set_bss_type
 ��������  : ����bss type
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_bss_type(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_bss_type(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_bss_type
 ��������  : ��ȡbss type
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_bss_type(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_bss_type(pst_mac_vap, pus_len,  puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_mode
 ��������  : ����ģʽ
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_mode(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_mode
 ��������  : ����ģʽ
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_mode(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_set_mode
 ��������  : ����ģʽ
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : zhangxiang 00285102
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_bandwidth(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_mode_param_stru    *pst_prot_param;

    pst_prot_param = (mac_cfg_mode_param_stru *)puc_param;

    pst_prot_param->en_protocol  = pst_mac_vap->en_protocol;
    pst_prot_param->en_band      = pst_mac_vap->st_channel.en_band;

    return hmac_config_set_mode(pst_mac_vap, us_len, (oal_uint8 *)pst_prot_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_mac_addr
 ��������  : ����mac��ַ
 �������  : pst_mac_vap: ָ��vap��ָ��
             ul_len     : ��������
             puc_param  : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��25��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_mac_addr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32                     ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_config_set_mac_addr::pst_mac_vap or puc_param null ptr error %d,%d.}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_config_set_mac_addr(pst_mac_vap, us_len, puc_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_config_set_mac_addr:: return error code %d.}\r\n", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_config_set_concurrent
 ��������  : �����豸�����û���
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��25��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_concurrent(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32                      ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_config_set_concurrent::pst_mac_vap or puc_param null ptr error %d,%d.}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_config_set_concurrent(pst_mac_vap, us_len, puc_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_config_set_concurrent:: return error code %d.}\r\n", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_config_get_concurrent
 ��������  : ����ssid
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_concurrent(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_concurrent(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_ssid
 ��������  : ����ssid
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_ssid(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_ssid(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_ssid
 ��������  : ����ssid
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_ssid(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_ssid(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_shpreamble
 ��������  : ����ǰ��������λ
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_shpreamble(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_shpreamble
 ��������  : ��ȡǰ��������λ
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_shpreamble(pst_mac_vap, pus_len, puc_param);
}
#ifdef _PRE_WLAN_FEATURE_MONITOR
/*****************************************************************************
 �� �� ��  : wal_config_set_addr_filter
 ��������  : ���õ�ַ��������λ
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_addr_filter(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_addr_filter(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_addr_filter
 ��������  : ��ȡǰ��ַ��������λ
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_addr_filter(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_addr_filter(pst_mac_vap, pus_len, puc_param);
}
#endif

/*****************************************************************************
 �� �� ��  : wal_config_set_shortgi20
 ��������  : ����shortgi
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_shortgi20(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_shortgi20(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_shortgi40
 ��������  : ����shortgi
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_shortgi40(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_shortgi40(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_shortgi80
 ��������  : ����shortgi
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_shortgi80(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_shortgi80(pst_mac_vap, us_len, puc_param);
}


/*****************************************************************************
 �� �� ��  : wal_config_get_shortgi20
 ��������  : ��ȡshortgi
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_shortgi20(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_shortgi20(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_shortgi40
 ��������  : ��ȡshortgi
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_shortgi40(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_shortgi40(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_shortgi80
 ��������  : ��ȡshortgi
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_shortgi80(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_shortgi80(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_prot_mode
 ��������  : ���ñ���ģʽ
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_prot_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_prot_mode(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_prot_mode
 ��������  : ��ȡ����ģʽ
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_prot_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_prot_mode(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_auth_mode
 ��������  : ������֤ģʽ
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_auth_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_auth_mode(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_auth_mode
 ��������  : ��ȡ��֤ģʽ
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_auth_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_auth_mode(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_bintval
 ��������  : ����beacon interval
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_bintval(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_bintval(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_bintval
 ��������  : ��ȡbeacon interval
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_bintval(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_bintval(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_dtimperiod
 ��������  : ����dtim_period
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_dtimperiod(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_dtimperiod
 ��������  : ��ȡdtim_period
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_dtimperiod(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_nobeacon
 ��������  : ������ʽbeacon
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_nobeacon(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_nobeacon(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_nobeacon
 ��������  : ��ȡ��ʽbeacon
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_nobeacon(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_nobeacon(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_txchain
 ��������  : ���÷���ͨ��
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_txchain(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_txchain(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_txchain
 ��������  : ��ȡ����ͨ��
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_txchain(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_txchain(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_rxchain
 ��������  : ���ý���ͨ��
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_rxchain(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_rxchain(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_rxchain
 ��������  : ��ȡ����ͨ��
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_rxchain(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_rxchain(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_txpower
 ��������  : ���÷��书��
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��23��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_txpower(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_txpower(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_txpower
 ��������  : ��ȡ���书��
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_txpower(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_txpower(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_freq
 ��������  : ����Ƶ��/�ŵ�
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��23��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_freq(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_freq(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_freq
 ��������  : ��ȡƵ��/�ŵ�
 �������  : pst_event_hdr: �¼�ͷ
 �������  : pus_len      : ��������
             puc_param    : ����
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_freq(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_freq(pst_mac_vap, pus_len, puc_param);
}


/*****************************************************************************
 �� �� ��  : wal_config_set_cwmin
 ��������  : ����EDCA�������ڲ���
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��23��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_wmm_params(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{

    return hmac_config_set_wmm_params(pst_mac_vap, us_len, puc_param);
}



/*****************************************************************************
 �� �� ��  : wal_config_get_wmm_params
 ��������  : ����EDCA�������ڲ���
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��23��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_config_get_wmm_params(oal_net_device_stru *pst_net_dev, oal_uint8 *puc_param)
{
    mac_vap_stru               *pst_vap;

    pst_vap = OAL_NET_DEV_PRIV(pst_net_dev);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_config_get_wmm_params::OAL_NET_DEV_PRIV(pst_net_dev) is null ptr.}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return hmac_config_get_wmm_params(pst_vap, puc_param);
}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 �� �� ��  : wal_config_set_smps_mode
 ��������  : ����smpsģʽ
 �������  : pst_mac_vap  : vap
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_smps_mode(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_smps_mode
 ��������  : ��ȡsmpsģʽ
 �������  : pst_mac_vap  : vap
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_smps_mode(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_smps_en
 ��������  : ��ȡsmpsģʽ
 �������  : pst_mac_vap  : vap
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_smps_en(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_smps_en(pst_mac_vap, pus_len, puc_param);
}

#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD

/*****************************************************************************
 �� �� ��  : wal_config_set_uapsd_en
 ��������  : ����vap uapsdʹ��
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_uapsd_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_uapsden(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_uapsd_en
 ��������  : ��ȡvap uapsdʹ��
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_uapsd_en(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{

    return hmac_config_get_uapsden(pst_mac_vap, pus_len, puc_param);
}

#endif


/*****************************************************************************
 �� �� ��  : wal_config_set_channel
 ��������  : �����ŵ���Ϣ������Ƶ�Σ��ŵ��ţ�����
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��26��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_channel(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_beacon
 ��������  : �����豸�������������RTS ����ֵ����Ƭ����ֵ
 �������  : pst_event_hdr: �¼�ͷ
             us_len       : ��������
             puc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��24��
    ��    ��   : zex287476
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_beacon(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32                          ul_ret;


    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap) || OAL_UNLIKELY(OAL_PTR_NULL == puc_param) )
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_config_set_beacon::pst_mac_vap or puc_param is null [%x],[%x].}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_config_set_beacon(pst_mac_vap, us_len, puc_param);

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : wal_config_vap_info
 ��������  : ��ӡvap������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��28��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_vap_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_vap_info(pst_mac_vap, us_len, puc_param);
}

#ifdef _PRE_WLAN_FEATURE_BTCOEX
/*****************************************************************************
 �� �� ��  : wal_config_print_btcoex_status
 ��������  : ��ӡ����ά����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��17��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_print_btcoex_status(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_print_btcoex_status(pst_mac_vap, us_len, puc_param);
}
#endif

#ifdef _PRE_WLAN_FEATURE_LTECOEX
/*****************************************************************************
 �� �� ��  : wal_config_ltecoex_mode_set
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��19��
    ��    ��   : z00196432
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_ltecoex_mode_set(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_ltecoex_mode_set(pst_mac_vap, us_len, puc_param);
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
 �� �� ��  : wal_config_wfa_cfg_aifsn
 ��������  : ����aifsn�̶�ֵ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��23��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_wfa_cfg_aifsn(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_wfa_cfg_aifsn(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_wfa_cfg_cw
 ��������  : ����cw�̶�ֵ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��23��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_wfa_cfg_cw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_wfa_cfg_cw(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_lte_gpio_mode
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��20��
    ��    ��   : z00285102
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_lte_gpio_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_lte_gpio_mode(pst_mac_vap, us_len, puc_param);
}

#endif

/*****************************************************************************
 �� �� ��  : wal_config_set_random_mac_addr_scan
 ��������  : �������mac addrɨ�迪��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��18��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_random_mac_addr_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_random_mac_addr_scan(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_random_mac_oui
 ��������  : �������mac oui
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��9��7��
    ��    ��   : d00223710
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_random_mac_oui(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_random_mac_oui(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_add_user
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
OAL_STATIC oal_uint32  wal_config_add_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_add_user(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_del_user
 ��������  : ɾ���û���������
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
OAL_STATIC oal_uint32  wal_config_del_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_del_user(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_sta_list
 ��������  : ȡ�ù���sta list
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_sta_list(mac_vap_stru *pst_mac_vap, oal_uint16 *us_len, oal_uint8 *puc_param)
{
    return hmac_config_get_sta_list(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_rd_pwr
 ��������  : ���ù�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_rd_pwr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_regdomain_pwr(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_reduce_sar
 ��������  : ��SAR
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��27��
    ��    ��   : huchikun
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_reduce_sar(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_reduce_sar(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_dump_all_rx_dscr
 ��������  : ��ӡ���н���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��8��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_config_dump_all_rx_dscr(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_dump_all_rx_dscr(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_cfg80211_start_sched_scan
 ��������  : ����PNO����ɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_cfg80211_start_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_cfg80211_start_sched_scan(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_cfg80211_stop_sched_scan
 ��������  : ֹͣPNO����ɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_cfg80211_stop_sched_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_cfg80211_stop_sched_scan(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_scan_abort
 ��������  : ɨ����ֹ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_scan_abort(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_scan_abort(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_cfg80211_start_scan
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��30��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_cfg80211_start_scan(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_cfg80211_start_scan_sta(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_cfg80211_start_join
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��30��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��10��24��
    ��    ��   : l00218984
    �޸�����   : ���Ӽ�����֤��صĴ���
  3.��    ��   : 2015��5��5��
    ��    ��   : g00260350
    �޸�����   : �����߼�Ų��hmac
*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_cfg80211_start_join(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_connect(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_create_packet
 ��������  : �����һ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��22��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_netbuf_stru*  wal_config_create_packet_sta(oal_uint32 ul_size,
                                                oal_int32 l_reserve,
                                                oal_uint32 ul_put_len,
                                                oal_bool_enum_uint8 en_ismcast,
                                                oal_uint8 uc_tid)
{
    oal_netbuf_stru *pst_buf;
    mac_ether_header_stru  *pst_ether_header;
    mac_ip_header_stru     *pst_ip;
    oal_uint32             ul_loop = 0;

    pst_buf = oal_netbuf_alloc(ul_size, l_reserve, 4);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_buf))
    {
        return OAL_PTR_NULL;
    }

    oal_netbuf_put(pst_buf, ul_put_len);

    if (en_ismcast)
    {
        pst_buf->data[0] = 0xFF;
    }
    else
    {
        pst_buf->data[0] = 0x28;
    }

    pst_buf->data[0] = 0x28;
    pst_buf->data[1] = 0x6E;
    pst_buf->data[2] = 0xD4;
    pst_buf->data[3] = 0x89;
    pst_buf->data[4] = 0x00;
    pst_buf->data[5] = 0xC2;

    pst_buf->data[6] = 0x06;
    pst_buf->data[7] = 0x05;
    pst_buf->data[8] = 0x04;
    pst_buf->data[9] = 0x03;
    pst_buf->data[10] = 0x02;
    pst_buf->data[11] = 0x02;


    pst_buf->data[12] = 0x08;
    pst_buf->data[13] = 0x00;

    for (ul_loop = 0; ul_loop < ul_put_len - 20; ul_loop++)
    {
        pst_buf->data[14 + ul_loop] = (oal_uint8)ul_loop;
    }

    pst_ether_header = (mac_ether_header_stru *)oal_netbuf_data(pst_buf);

    /*lint -e778*/
    pst_ether_header->us_ether_type = OAL_HOST2NET_SHORT(ETHER_TYPE_IP);
    /*lint +e778*/
    pst_ip = (mac_ip_header_stru *)(pst_ether_header + 1);      /* ƫ��һ����̫��ͷ��ȡipͷ */

    pst_ip->uc_tos = (oal_uint8)(uc_tid << WLAN_IP_PRI_SHIFT);

    pst_buf->next = OAL_PTR_NULL;
    pst_buf->prev = OAL_PTR_NULL;

    OAL_MEMZERO(oal_netbuf_cb(pst_buf), OAL_NETBUF_CB_SIZE());

    return pst_buf;

}

/*****************************************************************************
 �� �� ��  : wal_config_frag_threshold
 ��������  : ���÷�Ƭ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_frag_threshold(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_frag_threshold_stru *pst_frag_threshold;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_config_frag_threshold:: pst_mac_vap/puc_param is null ptr %d, %d!}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_frag_threshold = (mac_cfg_frag_threshold_stru *)puc_param;

    if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_frag_threshold:pst_mib_info[%d],ul_frag_threshold[%d] !}\r\n",
                    pst_mac_vap->pst_mib_info);
		return OAL_ERR_CODE_PTR_NULL;
    }

    //pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11FragmentationThreshold = pst_frag_threshold->ul_frag_threshold;
    mac_mib_set_frag_threshold(pst_mac_vap, pst_frag_threshold->ul_frag_threshold);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_config_rts_threshold
 ��������  : ���÷�Ƭ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��20��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_rts_threshold(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_rts_threshold_stru *pst_rts_threshold;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{wal_config_rts_threshold:: pst_mac_vap/puc_param is null ptr %d, %d!}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_rts_threshold = (mac_cfg_rts_threshold_stru *)puc_param;

    if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_config_rts_threshold: pst_mac_vap->pst_mib_info is null ptr!}\r\n");
		return OAL_ERR_CODE_PTR_NULL;
    }

    mac_mib_set_rts_threshold(pst_mac_vap, pst_rts_threshold->ul_rts_threshold);

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_config_rts_threshold: mib rts %d!}\r\n",
                    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11RTSThreshold);

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_SMARTANT
OAL_STATIC oal_uint32  wal_config_get_ant_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_get_ant_info(pst_mac_vap, us_len, puc_param);
}
OAL_STATIC oal_uint32  wal_config_double_ant_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_double_ant_switch(pst_mac_vap, us_len, puc_param);
}
#endif
/*****************************************************************************
 �� �� ��  : wal_config_kick_user
 ��������  : ȥ����1���û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_kick_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_kick_user(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_country
 ��������  : ���ù�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_country(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_country(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_country_for_dfs
 ��������  : ���ù������е�dfs��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��18��
    ��    ��   : zhangxiang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_country_for_dfs(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_country_for_dfs(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_country
 ��������  : ��ȡ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_country(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_country(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_tid
 ��������  : ��ȡ��������֡��tid
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_tid(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_tid(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_user_info
 ��������  : ��ӡuser��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_user_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
   return hmac_config_user_info(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_dscr_param
 ��������  : ��ӡuser��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_dscr_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
   return hmac_config_set_dscr_param(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_log_level
 ��������  : ������־�����¼�����hmac
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��21��
    ��    ��   : jwx222439
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_set_log_level(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_log_level(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_green_ap_en
 ��������  : ����green apʹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��2��21��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_GREEN_AP
OAL_STATIC oal_uint32 wal_config_set_green_ap_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32          ul_ret;

    /***************************************************************************
        ���¼���DMAC��, ͬ��DMAC����
    ***************************************************************************/
    ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_GREEN_AP_EN, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_config_set_green_ap_en::hmac_config_send_event failed[%d].}", ul_ret);
    }

    return ul_ret;

}
#endif
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC oal_uint32 wal_config_set_pm_switch(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32          ul_ret;
    oal_uint8           uc_en;


    uc_en = (oal_uint8)(*puc_param);

    OAM_WARNING_LOG1(0, OAM_SF_PWR, "{wal_config_set_pm_switch:[%d]}\r\n", uc_en);

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if(uc_en)
    {
        g_wlan_pm_switch = OAL_TRUE;
        wlan_pm_enable();
    }
    else
    {
        wlan_pm_disable();
        g_wlan_pm_switch = OAL_FALSE;
    }
#endif
    /***************************************************************************
        ���¼���DMAC��, ͬ��DMAC����
    ***************************************************************************/
    ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_SET_PM_SWITCH, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_config_set_feature_log::hmac_config_send_event failed[%d].}", ul_ret);
    }

    return ul_ret;

}

OAL_STATIC oal_uint32 wal_config_set_ant(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)

{
    oal_uint32          ul_ret;
    oal_uint8           uc_en;


    uc_en = (oal_uint8)(*puc_param);

    OAM_WARNING_LOG1(0, OAM_SF_PWR, "{wal_config_set_ant:[%d]}\r\n", uc_en);

    /***************************************************************************
        ....DMAC., ..DMAC..
    ***************************************************************************/
    ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_SET_ANT, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_config_set_feature_log::hmac_config_send_event failed[%d].}", ul_ret);

    }

    return ul_ret;

}


/*****************************************************************************
 . . .  : wal_config_get_ant
 ....  : ....
 ....  : pst_mac_vap: MAC VAP.....
             us_len     : ....
             puc_param  : ....
 ....  : .
 . . .  :
 ....  :
 ....  :

 ....      :
  1..    .   : 2014.3.28.
    .    .   : zhangyu
    ....   : .....

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_ant(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)

{
    return hmac_config_get_ant(pst_mac_vap, us_len, puc_param);
}

#endif
/*****************************************************************************
 �� �� ��  : wal_config_set_rate
 ��������  : ����non-HT����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
//#ifdef    _PRE_WLAN_CHIP_TEST
OAL_STATIC oal_uint32  wal_config_set_rate(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ret;
    mac_cfg_tx_comp_stru            st_event_set_bcast;

    oal_memset(&st_event_set_bcast, 0, OAL_SIZEOF(mac_cfg_tx_comp_stru));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{wal_config_set_rate::pst_mac_vap/puc_param is null ptr %d %d!}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ò��� */
    ul_ret = hmac_config_set_rate(pst_mac_vap, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {

        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_set_rate::hmac_config_set_rate error!}\r\n");
        return ul_ret;
    }
#if 0
    /* ���³��� */
    if (OAL_SWITCH_ON == pst_mac_vap->bit_al_tx_flag)
    {
       st_event_set_bcast.uc_param = OAL_SWITCH_ON;
       st_event_set_bcast.en_protocol_mode = WLAN_PHY_PROTOCOL_BUTT;
       wal_config_always_tx(pst_mac_vap, us_len, (oal_uint8 *)&st_event_set_bcast);
    }
#endif
    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : wal_config_set_mcs
 ��������  : ����HT����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_mcs(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY,"{wal_config_set_mcs::pst_mac_vap/puc_param is null ptr}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ò��� */
    ul_ret = hmac_config_set_mcs(pst_mac_vap, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_set_mcs::hmac_config_set_mcs error.}\r\n");
        return ul_ret;
    }

    return ul_ret;
}


/*****************************************************************************
 �� �� ��  : wal_config_set_mcsac
 ��������  : ����VHT����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_mcsac(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_config_set_mcsac::pst_mac_vap/puc_param is null ptr!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ò��� */
    ul_ret = hmac_config_set_mcsac(pst_mac_vap, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_set_mcsac::hmac_config_set_mcsac error!}\r\n");
        return ul_ret;
    }

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : wal_config_set_bw
 ��������  : ���ô���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_bw(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32  ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_config_set_bw::pst_mac_vap/puc_param is null ptr!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ò��� */
    ul_ret = hmac_config_set_bw(pst_mac_vap, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_set_bw::hmac_config_set_bw error!}\r\n");
        return ul_ret;
    }

    return ul_ret;
}

#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
/*****************************************************************************
 �� �� ��  : wal_config_always_tx
 ��������  : �㲥���ݰ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_always_tx_1102(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32                      ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_config_always_tx::pst_mac_vap/puc_param is null ptr!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }


    ul_ret = hmac_config_always_tx_1102(pst_mac_vap, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_always_tx::hmac_config_always_tx failed!}\r\n");
        return ul_ret;
    }

    return OAL_SUCC;
}
#endif /* #ifdef _PRE_WLAN_FEATURE_ALWAYS_TX */


/*****************************************************************************
 �� �� ��  : wal_config_always_rx
 ��������  : ���ó���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_always_rx(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32                      ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_config_always_rx::pst_mac_vap/puc_param is null ptr!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_config_always_rx(pst_mac_vap, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_always_rx::hmac_config_always_rx failed!}\r\n");
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_config_pcie_pm_level
 ��������  : ����PCIE�͹���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��2��27��
    ��    ��   : h00212953
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_pcie_pm_level(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32                      ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_config_pcie_pm_level::pst_mac_vap/puc_param is null ptr!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_config_pcie_pm_level(pst_mac_vap, us_len, puc_param);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_pcie_pm_level::hmac_config_set_freq_skew failed!}\r\n");
        return ul_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_config_reg_info
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��31��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_reg_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
     return hmac_config_reg_info(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_reg_write
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_reg_write(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_reg_write(pst_mac_vap, us_len, puc_param);
}

#if (defined(_PRE_PRODUCT_ID_HI110X_DEV) || defined(_PRE_PRODUCT_ID_HI110X_HOST))

/*****************************************************************************
 �� �� ��  : wal_config_sdio_flowctrl
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��30��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_sdio_flowctrl(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_sdio_flowctrl(pst_mac_vap, us_len, puc_param);
}
#endif

/*****************************************************************************
 �� �� ��  : wal_config_alg_param
 ��������  : �㷨����ʾ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��11��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_alg_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{

    return hmac_config_alg_param(pst_mac_vap, us_len, puc_param);
}

#if 0
/*****************************************************************************
 �� �� ��  : wal_config_tdls_prohibited
 ��������  : TDLS���ÿ���
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��26��
    ��    ��   : daihu 00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_tdls_prohibited(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_tdls_prohibited(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_tdls_channel_switch_prohibited
 ��������  : TDLS�ŵ��л����ÿ���
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��26��
    ��    ��   : daihu 00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_tdls_channel_switch_prohibited(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_tdls_channel_switch_prohibited(pst_mac_vap, us_len, puc_param);
}
#endif

/*****************************************************************************
 �� �� ��  : wal_config_rx_fcs_info
 ��������  : ��ӡ����֡��FCS��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_rx_fcs_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_rx_fcs_info(pst_mac_vap, us_len, puc_param);
}

#ifdef _PRE_WLAN_FEATURE_DFS
/*****************************************************************************
 �� �� ��  : wal_config_dfs_radartool
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_dfs_radartool(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_dfs_radartool(pst_mac_vap, us_len, puc_param);
}
#endif

/*Get the cfgid entry*/
OAL_STATIC wal_wid_op_stru* wal_config_get_wid_map(wal_wid_op_stru* pst_wid_map,
                                                    oal_uint16 en_wid,
                                                    oal_uint32 ul_wid_nums)
{
    oal_uint16 us_cfgid;
    wal_wid_op_stru* pst_current_wid;

    for(us_cfgid = 0; us_cfgid < ul_wid_nums; us_cfgid++)
    {
        pst_current_wid = pst_wid_map + us_cfgid;
        if (pst_current_wid->en_cfgid == en_wid)
        {
            return pst_current_wid;
        }
    }

    return NULL;
}

/*****************************************************************************
 �� �� ��  : wal_config_process_query
 ��������  : �������ò�ѯ����
 �������  : pst_event_hdr   : �¼�ͷ
             puc_req_msg     : ������Ϣ
             us_req_msg_len  : ������Ϣ����
 �������  : puc_rsp_msg     : ������Ϣ
             pus_rsp_msg_len : ������Ϣ����
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��9��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_process_query(
                mac_vap_stru       *pst_mac_vap,
                oal_uint8          *puc_req_msg,
                oal_uint16          us_req_msg_len,
                oal_uint8          *puc_rsp_msg,
                oal_uint8          *puc_rsp_msg_len)
{
    oal_uint16          us_req_idx = 0;      /* ������Ϣ���� */
    oal_uint16          us_rsp_idx = 0;      /* ������Ϣ���� */
    oal_uint16          us_len     = 0;      /* WID��Ӧ����ֵ�ĳ��� */
    wal_msg_query_stru *pst_query_msg;
    wal_msg_write_stru *pst_rsp_msg;
    oal_uint32          ul_ret;
    wal_wid_op_stru*    pst_current_wid;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap)
     || (OAL_PTR_NULL == puc_req_msg)
     || (OAL_PTR_NULL == puc_rsp_msg)
     || (OAL_PTR_NULL == puc_rsp_msg_len)))
    {
        OAM_ERROR_LOG4(0, OAM_SF_ANY, "{wal_config_process_query::pst_mac_vap/puc_req_msg/puc_rsp_msg/puc_rsp_msg_len null ptr error: %d, %d, %d, %d!}\r\n",
                       pst_mac_vap, puc_req_msg, puc_rsp_msg, puc_rsp_msg_len);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ѯ��Ϣ��ʽ����:                                                     */
    /* +-------------------------------------------------------------------+ */
    /* | WID0          | WID1         | WID2         | ................... | */
    /* +-------------------------------------------------------------------+ */
    /* |     2 Bytes   |    2 Bytes   |    2 Bytes   | ................... | */
    /* +-------------------------------------------------------------------+ */

    /* ������Ϣ��ʽ����:                                                     */
    /* +-------------------------------------------------------------------+ */
    /* | WID0      | WID0 Length | WID0 Value  | ......................... | */
    /* +-------------------------------------------------------------------+ */
    /* | 2 Bytes   | 2 Byte      | WID Length  | ......................... | */
    /* +-------------------------------------------------------------------+ */

    while (us_req_idx < us_req_msg_len)
    {
        /* �Ӳ�ѯ��Ϣ�еõ�һ��WIDֵ   */
        pst_query_msg = (wal_msg_query_stru *)(&puc_req_msg[us_req_idx]);
        us_req_idx   += WAL_MSG_WID_LENGTH;                       /* ָ����һ��WID */

        /* ��ȡ������Ϣ�ڴ� */
        pst_rsp_msg = (wal_msg_write_stru *)(&puc_rsp_msg[us_rsp_idx]);

        pst_current_wid = wal_config_get_wid_map((wal_wid_op_stru*)g_ast_board_wid_op, pst_query_msg->en_wid, OAL_ARRAY_SIZE(g_ast_board_wid_op));
        if(NULL == pst_current_wid)
        {
#ifdef _PRE_WLAN_CFGID_DEBUG
            pst_current_wid = wal_config_get_wid_map((wal_wid_op_stru*)g_ast_board_wid_op_debug,
                                                     pst_query_msg->en_wid,
                                                     wal_config_get_debug_wid_arrysize());
            if(NULL == pst_current_wid)
            {
                OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_query::cfgid not invalid %d!}\r\n", pst_query_msg->en_wid);
                continue;
            }
            /*else, call the cfgid func.*/
#else
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_query::cfgid not invalid %d!}\r\n", pst_query_msg->en_wid);
            continue;
#endif
        }

        /* �쳣�����cfgid��Ӧ��get����Ϊ�� */
        if (OAL_PTR_NULL == pst_current_wid->p_get_func)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_query:: get_func ptr is null, wid is %d!}\r\n", pst_query_msg->en_wid);
            continue;
        }

        ul_ret = pst_current_wid->p_get_func(pst_mac_vap, &us_len, pst_rsp_msg->auc_value);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_query:: func return no SUCC. wid and ret value is:%d, %d!}\r\n", pst_query_msg->en_wid, ul_ret);
            continue;
        }

        pst_rsp_msg->en_wid = pst_query_msg->en_wid;            /* ���÷�����Ϣ��WID */
        pst_rsp_msg->us_len = us_len;

        us_rsp_idx += us_len + WAL_MSG_WRITE_MSG_HDR_LENGTH;    /* ��Ϣ��ĳ��� �ټ�����Ϣͷ�ĳ��� */

        /*��ϢResponse �ӿ������õ�����ʹ�ó�����Ϣ����ռ䳤�ȣ�
          ������Ҫ���жϣ���鳤�Ⱥ͹��ƣ�������Ҫ����*/
        if(OAL_UNLIKELY(us_rsp_idx + OAL_SIZEOF(wal_msg_hdr_stru) > HMAC_RSP_MSG_MAX_LEN))
        {
            OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_query::us_cfgid:%d reponse msg len:%u over limit:%u}",
                                pst_current_wid->en_cfgid,us_rsp_idx + OAL_SIZEOF(wal_msg_hdr_stru),HMAC_RSP_MSG_MAX_LEN);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
            oal_print_hex_dump((oal_uint8*)puc_rsp_msg, HMAC_RSP_MSG_MAX_LEN,
                                        32, "puc_rsp_msg: ");
            OAL_BUG_ON(1);
#endif
        }
    }

    *puc_rsp_msg_len = (oal_uint8)us_rsp_idx;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_config_process_write
 ��������  : ����������������
 �������  : pst_event_hdr: �¼�ͷ
             puc_req_msg  : ������Ϣ
             us_msg_len   : ������Ϣ����
 �������  : OAL_SUCC������������
             puc_rsp_msg     : ������Ϣ
             pus_rsp_msg_len : ������Ϣ����
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_process_write(
                mac_vap_stru    *pst_mac_vap,
                oal_uint8       *puc_req_msg,
                oal_uint16       us_msg_len,
                oal_uint8       *puc_rsp_msg,
                oal_uint8       *puc_rsp_msg_len)
{
    oal_uint16              us_req_idx = 0;
    oal_uint16              us_rsp_idx = 0;
    wal_msg_write_stru     *pst_write_msg;
    wal_msg_write_rsp_stru *pst_rsp_msg;
    oal_uint32              ul_ret;
    wal_wid_op_stru*        pst_current_wid;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_req_msg)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_config_process_write::pst_mac_vap/puc_req_msg null ptr error %d, %d!}\r\n", pst_mac_vap, puc_req_msg);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ������Ϣ�ĸ�ʽ����:                                                   */
    /* +-------------------------------------------------------------------+ */
    /* | WID0      | WID0 Length | WID0 Value  | ......................... | */
    /* +-------------------------------------------------------------------+ */
    /* | 2 Bytes   | 2 Byte      | WID Length  | ......................... | */
    /* +-------------------------------------------------------------------+ */

    /* ������Ϣ�ĸ�ʽ����:                                                   */
    /* +-------------------------------------------------------------------+ */
    /* | WID0     | resv    | WID0 ������ |  WID1   | resv | WID1������ |  | */
    /* +-------------------------------------------------------------------+ */
    /* | 2 Bytes  | 2 Bytes | 4 Byte      | 2 Bytes | 2 B  |  4 Bytes   |  | */
    /* +-------------------------------------------------------------------+ */

    while (us_req_idx < us_msg_len)
    {
        /* ��ȡһ������WID��Ϣ   */
        pst_write_msg = (wal_msg_write_stru *)(&puc_req_msg[us_req_idx]);

        /* ��ȡ������Ϣ�ڴ� */
        pst_rsp_msg = (wal_msg_write_rsp_stru *)(&puc_rsp_msg[us_rsp_idx]);

        us_req_idx += pst_write_msg->us_len + WAL_MSG_WRITE_MSG_HDR_LENGTH;   /* ָ����һ��WID������Ϣ */

        /* Ѱ��cfgid ��Ӧ��write���� */
        pst_current_wid = wal_config_get_wid_map((wal_wid_op_stru*)g_ast_board_wid_op, pst_write_msg->en_wid, OAL_ARRAY_SIZE(g_ast_board_wid_op));
        if(NULL == pst_current_wid)
        {
#ifdef _PRE_WLAN_CFGID_DEBUG
            pst_current_wid = wal_config_get_wid_map((wal_wid_op_stru*)g_ast_board_wid_op_debug,
                                                     pst_write_msg->en_wid,
                                                     wal_config_get_debug_wid_arrysize());
            if(NULL == pst_current_wid)
            {
                OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_write::cfgid not invalid %d!}\r\n", pst_write_msg->en_wid);
                continue;
            }
            /*else, go on call the cfgid func.*/
#else
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_write::cfgid not invalid %d!}\r\n", pst_write_msg->en_wid);
            continue;
#endif
        }

        /* �쳣�����cfgid��Ӧ��set����Ϊ�� */
        if (OAL_PTR_NULL == pst_current_wid->p_set_func)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_write:: get_func ptr is null, wid is %d!}\r\n", pst_write_msg->en_wid);
            continue;
        }


        ul_ret = pst_current_wid->p_set_func(pst_mac_vap, pst_write_msg->us_len, pst_write_msg->auc_value);

        /* �����ش��������õ�rsp��Ϣ�� */
        pst_rsp_msg->en_wid = pst_write_msg->en_wid;
        pst_rsp_msg->ul_err_code = ul_ret;
        us_rsp_idx += OAL_SIZEOF(wal_msg_write_rsp_stru);

        /*��ϢResponse �ӿ������õ�����ʹ�ó�����Ϣ����ռ䳤�ȣ�
          ������Ҫ���жϣ���鳤�Ⱥ͹��ƣ�������Ҫ����*/
        if(OAL_UNLIKELY(us_rsp_idx + OAL_SIZEOF(wal_msg_hdr_stru) > HMAC_RSP_MSG_MAX_LEN))
        {
            OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_write::us_cfgid:%d reponse msg len:%u over limit:%u}",
                                pst_current_wid->en_cfgid,us_rsp_idx + OAL_SIZEOF(wal_msg_hdr_stru),HMAC_RSP_MSG_MAX_LEN);
            OAL_BUG_ON(1);
        }

        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_write::func return no SUCC. wid and ret value is %d, %d!}\r\n", pst_write_msg->en_wid, ul_ret);
        }

    }

    *puc_rsp_msg_len = (oal_uint8)us_rsp_idx;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_config_process_pkt
 ��������  : ���ð��¼�����
 �������  : pst_event: �¼�
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��6��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_config_process_pkt(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru         *pst_event;
    wal_msg_stru           *pst_msg;
    wal_msg_stru           *pst_rsp_msg = NULL;
    frw_event_hdr_stru     *pst_event_hdr;
    mac_vap_stru           *pst_mac_vap;
    oal_uint16              us_msg_len;
    oal_uint8               uc_rsp_len = 0;
    oal_uint8               uc_rsp_toal_len = 0;
    oal_uint32              ul_ret;
    oal_ulong               ul_request_address;
    oal_uint8               ac_rsp_msg[HMAC_RSP_MSG_MAX_LEN] = {0};

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_config_process_pkt::pst_event_mem null ptr error!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &(pst_event->st_event_hdr);
    ul_request_address = ((wal_msg_rep_hdr*)pst_event->auc_event_data)->ul_request_address;
    pst_msg       = (wal_msg_stru *)(frw_get_event_payload(pst_event_mem) + OAL_SIZEOF(wal_msg_rep_hdr));

    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_event_hdr->uc_vap_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{wal_config_process_pkt::hmac_get_vap_by_id return err code!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* ȡ������Ϣ */
    pst_rsp_msg  = (wal_msg_stru *)ac_rsp_msg;

    /* ȡ������Ϣ�ĳ��� */
    us_msg_len = pst_msg->st_msg_hdr.us_msg_len;

    OAM_INFO_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_ANY, "{wal_config_process_pkt::a config event occur!}\r\n");

    switch (pst_msg->st_msg_hdr.en_msg_type)
    {
        case WAL_MSG_TYPE_QUERY:

            ul_ret = wal_config_process_query(pst_mac_vap, pst_msg->auc_msg_data, us_msg_len, pst_rsp_msg->auc_msg_data, &uc_rsp_len);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_pkt::wal_config_process_query return error code %d!}\r\n", ul_ret);
                return ul_ret;
            }

            break;

        case WAL_MSG_TYPE_WRITE:
            ul_ret = wal_config_process_write(pst_mac_vap, pst_msg->auc_msg_data, us_msg_len, pst_rsp_msg->auc_msg_data, &uc_rsp_len);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_pkt::wal_config_process_write return error code %d!}\r\n", ul_ret);
                return ul_ret;
            }

            break;

        default:
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_pkt::pst_msg->st_msg_hdr.en_msg_type error, msg_type is %d!}\r\n", pst_msg->st_msg_hdr.en_msg_type);

            return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /*response ����Ҫ����ͷ��*/
    uc_rsp_toal_len = uc_rsp_len + OAL_SIZEOF(wal_msg_hdr_stru);

    if(OAL_UNLIKELY(uc_rsp_toal_len > HMAC_RSP_MSG_MAX_LEN))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_config_process_pkt::invaild response len %u!}\r\n", uc_rsp_toal_len);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        OAL_BUG_ON(1);
#endif
    }

    /* ��䷵����Ϣͷ */
    pst_rsp_msg->st_msg_hdr.en_msg_type = WAL_MSG_TYPE_RESPONSE;
    pst_rsp_msg->st_msg_hdr.uc_msg_sn   = pst_msg->st_msg_hdr.uc_msg_sn;
    pst_rsp_msg->st_msg_hdr.us_msg_len  = uc_rsp_len;

    if(ul_request_address)
    {
        /*need response*/
        oal_uint8* pst_rsp_msg_tmp = oal_memalloc(uc_rsp_toal_len);
        if(NULL == pst_rsp_msg_tmp)
        {
            /*no mem*/
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_config_process_pkt::wal_config_process_pkt msg alloc %u failed!", uc_rsp_toal_len);
            wal_set_msg_response_by_addr(ul_request_address, NULL, OAL_ERR_CODE_PTR_NULL, uc_rsp_toal_len);
        }
        else
        {
            oal_memcopy((oal_void*)pst_rsp_msg_tmp, (oal_void*)ac_rsp_msg, uc_rsp_toal_len);
            if(OAL_SUCC != wal_set_msg_response_by_addr(ul_request_address, (oal_void*)pst_rsp_msg_tmp, OAL_SUCC, uc_rsp_toal_len))
            {
                OAL_IO_PRINT("wal_config_process_pkt did't found the request msg, request addr:0x%lx\n", ul_request_address);
                OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_config_process_pkt::wal_config_process_pkt did't found the request msg!");
                oal_free(pst_rsp_msg_tmp);
            }
        }
    }

    /* ����WAL�ȴ��Ľ��� */
    wal_cfg_msg_task_sched();

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_config_add_key
 ��������  : WAL�ڶ���,����hmac��ʵ��������Կ
 �������  :
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  : ��
 ��������  : ��


�޸���ʷ      :
  1.��    ��   : 2013��12��26��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_add_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_11i_add_key(pst_mac_vap, us_len, puc_param);
}
 /*****************************************************************************
 �� �� ��  : wal_config_get_key
 ��������  : WAL�ڶ���,����hmac��ʵ��
 �������  : frw_event_mem_stru *pst_event_mem
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2014��1��4��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_get_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    /*ͨ���������ã�hmac����ʵ��*/
    return (hmac_config_11i_get_key(pst_mac_vap, us_len, puc_param));
}

/*****************************************************************************
 �� �� ��  : wal_config_remove_key
 ��������  : WAL�ڶ��㣬���¼���HMAC
 �������  : frw_event_mem_stru *pst_event_mem
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2014��1��4��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_remove_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    /*ͨ���������ã�hmac����ʵ��*/
    return (hmac_config_11i_remove_key(pst_mac_vap, us_len, puc_param));
}

/*****************************************************************************
 �� �� ��  : wal_set_default_key
 ��������  : WAL�ڶ��㣬����HMAC
 �������  : frw_event_mem_stru *pst_event_mem
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2014��1��4��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_set_default_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    /*ͨ���������ã�hmac����ʵ��*/
    return (hmac_config_11i_set_default_key(pst_mac_vap, us_len, puc_param));
}


/*****************************************************************************
 �� �� ��  : wal_config_get_assoc_req_ie
 ��������  : AP ��ȡSTA ��������IE ��Ϣ
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 *pus_len
             oal_uint8 *puc_param
 �������  : oal_uint32
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��30��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_config_get_assoc_req_ie(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_assoc_req_ie(pst_mac_vap, pus_len, puc_param);
}


/*****************************************************************************
 �� �� ��  : wal_config_set_wps_ie
 ��������  : AP ����WPS ��ϢԪ�ص�VAP �ṹ��
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 *pus_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��16��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_config_set_wps_ie(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_wps_ie(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_wps_p2p_ie
 ��������  : AP ����WPS ��ϢԪ�ص�VAP �ṹ��
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 *pus_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : xiaoyuren x00305155
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_config_set_wps_p2p_ie(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_wps_p2p_ie(pst_mac_vap, us_len, puc_param);
}

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
/*****************************************************************************
 �� �� ��  : wal_config_set_edca_opt_switch_sta
 ��������  : ����edca��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��2��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_edca_opt_switch_sta(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_edca_opt_switch_sta(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_edca_opt_weight_sta
 ��������  : ����STA��edca��������Ȩ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��2��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_edca_opt_weight_sta(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_edca_opt_weight_sta(pst_mac_vap, us_len, puc_param);
}



/*****************************************************************************
 �� �� ��  : wal_config_set_edca_opt_switch_ap
 ��������  : ����edca��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��2��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_edca_opt_switch_ap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_edca_opt_switch_ap(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_edca_opt_cycle
 ��������  : ����edca��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��2��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_edca_opt_cycle_ap(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_edca_opt_cycle_ap(pst_mac_vap, us_len, puc_param);
}

#endif

/*****************************************************************************
 �� �� ��  : wal_config_open_wmm
 ��������  : ���������/�ر�WMM
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_open_wmm(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_config_open_wmm::pst_mac_vap/puc_param is null ptr %d, %d!}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �������vap������ */
    if (WLAN_VAP_MODE_CONFIG == pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_config_open_wmm::this is config vap! can't get info.}");
        return OAL_FAIL;
    }

    return hmac_config_sync_cmd_common(pst_mac_vap, WLAN_CFGID_WMM_SWITCH, us_len, puc_param);
}
#ifdef _PRE_WLAN_FEATURE_VOWIFI
/*****************************************************************************
 �� �� ��  : wal_config_vowifi_info
 ��������  : ����VoWiFi��ز���
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
OAL_STATIC oal_uint32  wal_config_vowifi_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_vowifi_info(pst_mac_vap, us_len, puc_param);
}

#endif /* _PRE_WLAN_FEATURE_VOWIFI */
/*****************************************************************************
 �� �� ��  : wal_config_get_version
 ��������  : ��ȡ�汾
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             us_len     : ��������
             puc_param  : ����ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��28��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_get_version(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_get_version(pst_mac_vap, us_len, puc_param);
}



#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY

/*****************************************************************************
 �� �� ��  : wal_config_blacklist_add
 ��������  : ���Ӻ�����
 �������  : pst_net_dev: net device
             p_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��17��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_blacklist_add(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_blacklist_add(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_blacklist_add_only
 ��������  : ���Ӻ�����
 �������  : pst_net_dev: net device
             p_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��18��
    ��    ��   : d00223710
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_blacklist_add_only(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_blacklist_add_only(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_blacklist_del
 ��������  : ����mac��ַ
 �������  : pst_dev: �����豸
             p_addr : ��ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_blacklist_del(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_blacklist_del(pst_mac_vap, us_len, puc_param);
}


/*****************************************************************************
 �� �� ��  : wal_config_set_blacklist_mode
 ��������  : ���ú�����ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_blacklist_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_blacklist_mode(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_blacklist_show
 ��������  : ��������Ϣ��ӡ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��27��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_blacklist_show(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_show_blacklist(pst_mac_vap, us_len, puc_param);
}
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
/*****************************************************************************
 �� �� ��  : wal_config_proxyarp_en
 ��������  : ��proxyarp���Կ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_proxyarp_en(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_proxyarp_en_stru *pst_proxyarp_en_param;

    pst_proxyarp_en_param = (mac_proxyarp_en_stru *)puc_param;

    hmac_proxyarp_on(pst_mac_vap, pst_proxyarp_en_param->en_proxyarp);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_recv_config_cmd
 ��������  : ע�ᵽsdt����������ص�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : SDT����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  wal_recv_config_cmd(oal_uint8 *puc_buf, oal_uint16 us_len)
{
    oal_int8                ac_vap_name[OAL_IF_NAME_SIZE];
    oal_net_device_stru    *pst_net_dev;
    mac_vap_stru           *pst_mac_vap;
    frw_event_mem_stru     *pst_event_mem;
    frw_event_stru         *pst_event;
    oal_uint32              ul_ret      = OAL_SUCC;
    wal_msg_stru           *pst_msg;
    oal_netbuf_stru        *pst_netbuf;
    oal_uint16              us_netbuf_len; /* ����sdt��skb������������ͷβ�ռ�ĳ��� */
    wal_msg_stru           *pst_rsp_msg;
    wal_msg_rep_hdr        *pst_rep_hdr = NULL;

    oal_uint16              us_msg_size = us_len;
    oal_uint16              us_need_response = OAL_FALSE;

    DECLARE_WAL_MSG_REQ_STRU(st_msg_request);

    WAL_MSG_REQ_STRU_INIT(st_msg_request);

    oal_memcopy(ac_vap_name, puc_buf, OAL_IF_NAME_SIZE);
    ac_vap_name[OAL_IF_NAME_SIZE - 1] = '\0';   /* ��ֹ�ַ����쳣 */

    /* ����dev_name�ҵ�dev */
    pst_net_dev = oal_dev_get_by_name(ac_vap_name);
    if (OAL_PTR_NULL == pst_net_dev)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_recv_config_cmd::oal_dev_get_by_name return null ptr!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_dev_put(pst_net_dev);   /* ����oal_dev_get_by_name�󣬱������oal_dev_putʹnet_dev�����ü�����һ */

    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);    /* ��ȡmac vap */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_recv_config_cmd::OAL_NET_DEV_PRIV(pst_net_dev) is null ptr.}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    us_msg_size -= OAL_IF_NAME_SIZE;

    /* �����ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(us_msg_size + OAL_SIZEOF(wal_msg_rep_hdr));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_recv_config_cmd::request %d mem failed}\r\n", us_msg_size);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CRX,
                       WAL_HOST_CRX_SUBTYPE_CFG,
                       (oal_uint16)(us_msg_size),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    /* ��д�¼�payload */
    oal_memcopy(frw_get_event_payload(pst_event_mem) + OAL_SIZEOF(wal_msg_rep_hdr), puc_buf + OAL_IF_NAME_SIZE, us_msg_size);
    pst_msg = (wal_msg_stru *)(puc_buf + OAL_IF_NAME_SIZE);
    pst_rep_hdr = (wal_msg_rep_hdr*)pst_event->auc_event_data;

    if (WAL_MSG_TYPE_QUERY == pst_msg->st_msg_hdr.en_msg_type)
    {
        /*need response*/
        us_need_response = OAL_TRUE;
    }

    if(OAL_TRUE == us_need_response)
    {
        pst_rep_hdr->ul_request_address = (oal_ulong)&st_msg_request;
        wal_msg_request_add_queue(&st_msg_request);
    }
    else
    {
        pst_rep_hdr->ul_request_address = 0;
    }

    ul_ret = wal_config_process_pkt(pst_event_mem);

    if(OAL_TRUE == us_need_response)
    {
        wal_msg_request_remove_queue(&st_msg_request);
    }

    if (OAL_SUCC != ul_ret)
    {
        FRW_EVENT_FREE(pst_event_mem);
        if(NULL != st_msg_request.pst_resp_mem)
        {
            /*�쳣ʱ�ڴ���Ҫ�ͷ�*/
            oal_free(st_msg_request.pst_resp_mem);
        }
        return (oal_int32)ul_ret;
    }

    /* �ͷ��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    /* ����ǲ�ѯ��Ϣ���ͣ�����ϱ� */
    if(OAL_TRUE == us_need_response)
    {
        if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
        {
            if(NULL != st_msg_request.pst_resp_mem)
            {
                /*�쳣ʱ�ڴ���Ҫ�ͷ�*/
                oal_free(st_msg_request.pst_resp_mem);
            }
            return OAL_ERR_CODE_PTR_NULL;
        }

        if (NULL == st_msg_request.pst_resp_mem)
        {
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_recv_config_cmd::get response ptr failed!}\r\n");
            return (oal_int32)ul_ret;
        }

        pst_rsp_msg  = (wal_msg_stru *)st_msg_request.pst_resp_mem;

        us_netbuf_len = pst_rsp_msg->st_msg_hdr.us_msg_len + 1; /* +1��sdt���ߵ���Ҫ */

        us_netbuf_len = (us_netbuf_len > WLAN_SDT_NETBUF_MAX_PAYLOAD) ? WLAN_SDT_NETBUF_MAX_PAYLOAD : us_netbuf_len;

        pst_netbuf = oam_alloc_data2sdt(us_netbuf_len);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            if(NULL != st_msg_request.pst_resp_mem)
            {
                /*�쳣ʱ�ڴ���Ҫ�ͷ�*/
                oal_free(st_msg_request.pst_resp_mem);
            }
            return OAL_ERR_CODE_PTR_NULL;
        }

        oal_netbuf_data(pst_netbuf)[0] = 'M';     /* sdt��Ҫ */
        oal_memcopy(oal_netbuf_data(pst_netbuf) + 1, (oal_uint8 *)pst_rsp_msg->auc_msg_data, us_netbuf_len - 1);
        oal_free(st_msg_request.pst_resp_mem);
        st_msg_request.pst_resp_mem = NULL;

        oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_CFG, OAM_PRIMID_TYPE_DEV_ACK);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_recv_memory_cmd
 ��������  : ���յ�SDT��ȡ����д�ڴ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ����ߴ�����
 ���ú���  : SDT����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��30��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  wal_recv_memory_cmd(oal_uint8 *puc_buf, oal_uint16 us_len)
{
    oal_netbuf_stru            *pst_netbuf;
    wal_sdt_mem_frame_stru     *pst_mem_frame;
    oal_uint                    ul_mem_addr;    /* ��ȡ�ڴ��ַ */
    oal_uint16                  us_mem_len;     /* ��Ҫ��ȡ�ĳ��� */
    oal_uint8                   uc_offload_core_mode; /* offload�£���ʾ��һ���� */

    pst_mem_frame        = (wal_sdt_mem_frame_stru *)puc_buf;
    ul_mem_addr          = pst_mem_frame->ul_addr;
    us_mem_len           = pst_mem_frame->us_len;
    uc_offload_core_mode = pst_mem_frame->en_offload_core_mode;

    if (WAL_OFFLOAD_CORE_MODE_DMAC == uc_offload_core_mode)
    {
        /* �����offload���Σ�����Ҫ��ȡ���ڴ���wifiоƬ�࣬��Ҫ���¼����������� */
        return OAL_SUCC;
    }

    if (OAL_PTR_NULL == ul_mem_addr)            /* ��д��ַ������ */
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (us_mem_len > WAL_SDT_MEM_MAX_LEN)
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }



    if (MAC_SDT_MODE_READ== pst_mem_frame->uc_mode)
    {
        if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }


        pst_netbuf = oam_alloc_data2sdt(us_mem_len);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        oal_memcopy(oal_netbuf_data(pst_netbuf), (oal_void *)ul_mem_addr, us_mem_len);

        oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_MEM_RW, OAM_PRIMID_TYPE_DEV_ACK);
    }
    else if (MAC_SDT_MODE_WRITE == pst_mem_frame->uc_mode)
    {
        oal_memcopy((oal_void *)ul_mem_addr, pst_mem_frame->auc_data, us_mem_len);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_parse_global_var_cmd
 ��������  : ����ȫ�ֱ�����д�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��30��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  wal_parse_global_var_cmd(
                wal_sdt_global_var_stru    *pst_global_frame,
                oal_uint                   ul_global_var_addr)
{
    oal_netbuf_stru            *pst_netbuf;
    oal_uint16                  us_skb_len;

    if (MAC_SDT_MODE_WRITE == pst_global_frame->uc_mode)
    {
        oal_memcopy((oal_void *)ul_global_var_addr, (oal_void *)(pst_global_frame->auc_global_value), pst_global_frame->us_len);
    }
    else if (MAC_SDT_MODE_READ == pst_global_frame->uc_mode)
    {
        if (OAL_UNLIKELY(OAL_PTR_NULL == g_st_oam_sdt_func_hook.p_sdt_report_data_func))
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        us_skb_len = pst_global_frame->us_len;

        us_skb_len = (us_skb_len > WLAN_SDT_NETBUF_MAX_PAYLOAD) ? WLAN_SDT_NETBUF_MAX_PAYLOAD : us_skb_len;

        pst_netbuf = oam_alloc_data2sdt(us_skb_len);
        if (OAL_PTR_NULL == pst_netbuf)
        {
            return OAL_ERR_CODE_PTR_NULL;
        }

        oal_memcopy(oal_netbuf_data(pst_netbuf), (oal_void *)ul_global_var_addr, us_skb_len);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_GVAR_RW, OAM_PRIMID_TYPE_DEV_ACK);
#else
        oam_report_data2sdt(pst_netbuf, OAM_DATA_TYPE_MEM_RW, OAM_PRIMID_TYPE_DEV_ACK);
#endif
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_recv_global_var_cmd
 ��������  : ���ն�дȫ�ֱ������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : SDT����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��26��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  wal_recv_global_var_cmd(oal_uint8 *puc_buf, oal_uint16 us_len)
{
    wal_sdt_global_var_stru        *pst_global_frame;
    oal_uint                       ul_global_var_addr;

    if (OAL_PTR_NULL == puc_buf)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_global_frame = (wal_sdt_global_var_stru *)puc_buf;

    if (WAL_OFFLOAD_CORE_MODE_DMAC == pst_global_frame->en_offload_core_mode)
    {
        /* offload���Σ�����Ҫ��ȡ��ȫ�ֱ�����wifiоƬ�࣬��Ҫ���¼����������� */
        return OAL_SUCC;
    }

    ul_global_var_addr = oal_kallsyms_lookup_name(pst_global_frame->auc_global_value_name);
    if (0 == ul_global_var_addr)    /* not found */
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_recv_global_var_cmd::kernel lookup global var address returns 0!}\r\n");
        return OAL_FAIL;
    }

    return wal_parse_global_var_cmd(pst_global_frame, ul_global_var_addr);
}

/*****************************************************************************
 �� �� ��  : wal_recv_reg_cmd
 ��������  : �յ�SDT�·��Ķ�д�Ĵ����������Ƕ��Ĵ���������Ҫ���������Ľ�
             ��ͨ���ص����ظ�SDT�������д�Ĵ������������һ��㷢��ȥ��hal
             ��д�Ϳ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ����ߴ�����
 ���ú���  : SDT����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��31��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  wal_recv_reg_cmd(oal_uint8 *puc_buf, oal_uint16 us_len)
{
    oal_int8                     ac_vap_name[OAL_IF_NAME_SIZE];
    oal_net_device_stru         *pst_net_dev;
    mac_vap_stru                *pst_mac_vap;
    wal_sdt_reg_frame_stru      *pst_reg_frame;
    oal_int32                    l_ret;
    hmac_vap_cfg_priv_stru      *pst_cfg_priv;
    oal_netbuf_stru             *pst_net_buf;
    oal_uint32                   ul_ret;

    oal_memcopy(ac_vap_name, puc_buf, OAL_IF_NAME_SIZE);
    ac_vap_name[OAL_IF_NAME_SIZE - 1] = '\0';   /* ��ֹ�ַ����쳣 */

    /* ����dev_name�ҵ�dev */
    pst_net_dev = oal_dev_get_by_name(ac_vap_name);
    if (OAL_PTR_NULL == pst_net_dev)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_recv_reg_cmd::oal_dev_get_by_name return null ptr!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_dev_put(pst_net_dev);   /* ����oal_dev_get_by_name�󣬱������oal_dev_putʹnet_dev�����ü�����һ */

    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);    /* ��ȡmac vap */

    ul_ret = hmac_vap_get_priv_cfg(pst_mac_vap, &pst_cfg_priv);      /* ȡ����˽�нṹ�� */
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_recv_reg_cmd::hmac_vap_get_priv_cfg return null_ptr_err!}\r\n");
        return (oal_int32)ul_ret;
    }

    pst_cfg_priv->en_wait_ack_for_sdt_reg = OAL_FALSE;

    ul_ret = hmac_sdt_recv_reg_cmd(pst_mac_vap, puc_buf, us_len);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_recv_reg_cmd::hmac_sdt_recv_reg_cmd return error code!}\r\n");

        return (oal_int32)ul_ret;
    }

    pst_reg_frame = (wal_sdt_reg_frame_stru *)puc_buf;

    if (MAC_SDT_MODE_READ == pst_reg_frame->uc_mode)
    {
        wal_wake_lock();
        /*lint -e730*//* info, boolean argument to function */
        l_ret = OAL_WAIT_EVENT_INTERRUPTIBLE_TIMEOUT(pst_cfg_priv->st_wait_queue_for_sdt_reg,
                                                     (OAL_TRUE == pst_cfg_priv->en_wait_ack_for_sdt_reg),
                                                     2 * OAL_TIME_HZ);
        /*lint +e730*/
        /*lint -e774*//* ���WIN32�汾�µ�PC LINT���� */
        if (0 == l_ret)
        {
            /* ��ʱ */
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_recv_reg_cmd::wal_netdev_open: wait queue timeout!}\r\n");
            wal_wake_unlock();
            return -OAL_EINVAL;
        }
        else if (l_ret < 0)
        {
            /* �쳣 */
            OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_recv_reg_cmd::wal_netdev_open: wait queue error!}\r\n");
            wal_wake_unlock();
            return -OAL_EINVAL;
        }
        wal_wake_unlock();
        /*lint +e774*/

        /* ��ȡ���صļĴ���ֵ */
        pst_reg_frame->ul_reg_val = *((oal_uint32 *)(pst_cfg_priv->ac_rsp_msg));

        if (OAL_UNLIKELY(OAL_PTR_NULL != g_st_oam_sdt_func_hook.p_sdt_report_data_func))
        {
            pst_net_buf = oam_alloc_data2sdt((oal_uint16)OAL_SIZEOF(wal_sdt_reg_frame_stru));
            if (OAL_PTR_NULL == pst_net_buf)
            {
                return OAL_ERR_CODE_PTR_NULL;
            }

            oal_memcopy(oal_netbuf_data(pst_net_buf), (oal_uint8 *)pst_reg_frame, (oal_uint16)OAL_SIZEOF(wal_sdt_reg_frame_stru));

            oam_report_data2sdt(pst_net_buf, OAM_DATA_TYPE_REG_RW, OAM_PRIMID_TYPE_DEV_ACK);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_drv_cfg_func_hook_init
 ��������  : wal���⹳�Ӻ�����ʼ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void wal_drv_cfg_func_hook_init(oal_void)
{
    g_st_wal_drv_func_hook.p_wal_recv_cfg_data_func     = wal_recv_config_cmd;
    g_st_wal_drv_func_hook.p_wal_recv_mem_data_func     = wal_recv_memory_cmd;
    g_st_wal_drv_func_hook.p_wal_recv_reg_data_func     = wal_recv_reg_cmd;
    g_st_wal_drv_func_hook.p_wal_recv_global_var_func   = wal_recv_global_var_cmd;
}

/*****************************************************************************
 �� �� ��  : wal_config_set_pmksa
 ��������  : ���һ��pmksa
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2016��4��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_pmksa(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_pmksa(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_del_pmksa
 ��������  : ���һ��pmksa
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2016��4��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_del_pmksa(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_del_pmksa(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_flush_pmksa
 ��������  : ���һ��pmksa
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2016��4��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_flush_pmksa(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_flush_pmksa(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_remain_on_channel
 ��������  : ������ָ���ŵ�
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��22��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_remain_on_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_remain_on_channel(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_cancel_remain_on_channel
 ��������  : ֹͣ������ָ���ŵ�
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��22��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_cancel_remain_on_channel(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_cancel_remain_on_channel(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_set_sta_pm_mode
 ��������  : ����sta���ܵ�ģʽ
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��5��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_STA_PM
OAL_STATIC oal_uint32  wal_config_set_sta_pm_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param)))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return hmac_config_set_sta_pm_mode(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_show_pm_info
 ��������  : sta psm��ͳ��ά����Ϣ
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��16��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_PSM_DEBUG_MODE
OAL_STATIC oal_uint32  wal_config_show_pm_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_sync_cmd_common(pst_mac_vap, WLAN_CFGID_SHOW_PS_INFO, us_len, puc_param);
}
#endif

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
OAL_STATIC oal_uint32  wal_config_set_auto_freq_value(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_auto_freq_value(pst_mac_vap, us_len, puc_param);
}
#endif

/*****************************************************************************
 �� �� ��  : wal_config_set_sta_pm_on
 ��������  : ��sta device �͹���
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��13��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_sta_pm_on(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    hmac_vap_stru                *pst_hmac_vap;
    mac_cfg_ps_open_stru         *pst_sta_pm_open;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "{wal_config_set_sta_pm_on::pst_mac_vap / puc_param null}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap    = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_PWR, "{wal_config_set_sta_pm_on::pst_hmac_vap null,vap state[%d].}",pst_mac_vap->en_vap_state);
        return OAL_ERR_CODE_PTR_NULL;
    }
    pst_sta_pm_open = (mac_cfg_ps_open_stru *)puc_param;

    /* ����ϲ�����dhcp�ɹ���ʱȡ����ʱ���͹��ĵĶ�ʱ�� */
    if((OAL_TRUE == pst_hmac_vap->st_ps_sw_timer.en_is_registerd) && (pst_sta_pm_open->uc_pm_enable > MAC_STA_PM_SWITCH_OFF))
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_hmac_vap->st_ps_sw_timer));
    }

    return hmac_config_set_sta_pm_on(pst_mac_vap, us_len, puc_param);
}

#endif

/*****************************************************************************
 �� �� ��  : wal_config_set_uapsd_para
 ��������  : ����sta uapsd�Ĳ���
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��5��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
OAL_STATIC oal_uint32 wal_config_set_uapsd_para(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param)))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    return hmac_config_set_uapsd_para(pst_mac_vap, us_len, puc_param);
}
#endif
/*****************************************************************************
 �� �� ��  : wal_config_mgmt_tx
 ��������  : ���͹���֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_mgmt_tx(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_wpas_mgmt_tx(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_query_station_stats
 ��������  : ��ѯstation����Ϣ
 �������  : mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��3��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_query_station_stats(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_query_station_info(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_query_rssi
 ��������  : ��ѯ�û���rssi
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��11��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_query_rssi(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_query_rssi(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_query_rate
 ��������  : ��ѯdmac�û���ǰ��tx rx phy rate
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��11��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_query_rate(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_query_rate(pst_mac_vap, us_len, puc_param);
}

#ifdef _PRE_WLAN_DFT_STAT
/*****************************************************************************
 �� �� ��  : wal_config_query_ani
 ��������  : ��ѯdmac vap�Ŀ����Ų���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��15��
    ��    ��   : heyinjun
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_query_ani(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_query_ani(pst_mac_vap, us_len, puc_param);
}
#endif

#ifdef _PRE_WLAN_FEATURE_HS20
/*****************************************************************************
 �� �� ��  : wal_config_set_qos_map
 ��������  : ����QoSMap����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��11��
    ��    ��   : w00346925
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_qos_map(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_qos_map(pst_mac_vap, us_len, puc_param);
}
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 �� �� ��  : wal_config_set_p2p_ps_ops
 ��������  : ����P2P OPS ����
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_p2p_ps_ops(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_p2p_ps_ops(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_set_p2p_ps_noa
 ��������  : ����P2P NOA ����
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_p2p_ps_noa(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_p2p_ps_noa(pst_mac_vap, us_len, puc_param);
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
OAL_STATIC oal_uint32 wal_config_cfg_vap_h2d(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_cfg_vap_h2d(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_host_dev_init
 ��������  : ��ʼ��host device_struc�ṹ�壬Ŀǰ�������µ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_host_dev_init(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_host_dev_init(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_host_dev_exit
 ��������  : ȥ��ʼ��host device_struc�ṹ�壬Ŀǰ�������µ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��26��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_host_dev_exit(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_host_dev_exit(pst_mac_vap);
}



oal_uint32 wal_send_cali_data(oal_net_device_stru *pst_net_dev)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)

    mac_vap_stru               *pst_mac_vap;
    oal_uint8                  *puc_param = OAL_PTR_NULL;

    mac_device_stru            *pst_mac_device;

    pst_mac_device      = mac_res_get_dev(0);
    if(NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_init_wlan_vap::pst_mac_device is null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->uc_cfg_vap_id);

    hmac_send_cali_data(pst_mac_vap, 0, puc_param);
#endif
    return OAL_SUCC;
}

#endif

/*****************************************************************************
 �� �� ��  : wal_config_set_max_user
 ��������  : ��������û���
 �������  : pst_net_dev: net device
             p_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_set_max_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_uint32          ul_max_user;

    ul_max_user = *((oal_uint32 *)puc_param);
    if((IS_P2P_GO(pst_mac_vap) && (ul_max_user > WLAN_P2P_GO_ASSOC_USER_MAX_NUM_SPEC))||
        (ul_max_user > WLAN_ASSOC_USER_MAX_NUM_SPEC))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_config_set_max_user:: AP/GO want to set the max_user_value[%d] more than the threshold[%d]!}\r\n",
                ul_max_user, (IS_P2P_GO(pst_mac_vap) ? WLAN_P2P_GO_ASSOC_USER_MAX_NUM_SPEC : WLAN_ASSOC_USER_MAX_NUM_SPEC));
        return OAL_FAIL;
    }
    return hmac_config_set_max_user(pst_mac_vap, us_len, ul_max_user);
}

#ifdef _PRE_WLAN_FEATURE_11R
/*****************************************************************************
 �� �� ��  : wal_config_set_ft_ies
 ��������  : ����ft ies
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��11��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_ft_ies(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_ft_ies(pst_mac_vap, us_len, puc_param);
}
#endif //_PRE_WLAN_FEATURE_11R

#ifdef _PRE_WLAN_RF_CALI
/*****************************************************************************
 �� �� ��  : wal_config_auto_cali
 ��������  : У׼�Զ���������ں���
 �������  : mac_vap_stru *pst_mac_vap,
             oal_uint16 us_len,
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : W00269675
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_auto_cali(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    hmac_config_auto_cali(pst_mac_vap, us_len, puc_param);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_config_auto_cali
 ��������  : У׼�Զ���������ں���
 �������  : mac_vap_stru *pst_mac_vap,
             oal_uint16 us_len,
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : W00269675
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_cali_vref(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    hmac_config_set_cali_vref(pst_mac_vap, us_len, puc_param);

    return OAL_SUCC;
}
#endif
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/*****************************************************************************
 �� �� ��  : wal_config_get_lauch_cap
 ��������  : ʵ�ʷ���������ѯ
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 us_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��27��,������
    ��    ��   : w00346925
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_config_get_lauch_cap(mac_vap_stru *pst_mac_vap, oal_uint16 *us_len, oal_uint8 *puc_param)
{
    return hmac_config_get_lauch_cap(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_linkloss_threshold(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_linkloss_threshold(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_all_log_level(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_all_log_level(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_d2h_hcc_assemble_cnt(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_d2h_hcc_assemble_cnt(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_chn_est_ctrl(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_chn_est_ctrl(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_power_ref(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_power_ref(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_pm_cfg_param(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_pm_cfg_param(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_cus_rf(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_cus_rf(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_cus_dts_cali(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_cus_dts_cali(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_set_cus_nvram_params(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_cus_nvram_params(pst_mac_vap, us_len, puc_param);
}
/*****************************************************************************
 �� �� ��  : wal_config_dev_customize_info
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
/* show dev customize info */
OAL_STATIC oal_uint32  wal_config_dev_customize_info(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_dev_customize_info(pst_mac_vap, us_len, puc_param);
}
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef _PRE_WLAN_FEATURE_HILINK
/*****************************************************************************
 �� �� ��  : wal_config_fbt_kick_user
 ��������  : hilink�����У��޳��û��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2016��01��19��
    ��    ��   : xiexiaming
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_fbt_kick_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_cfg_kick_user_param_stru   *pst_kick_user_param;
    oal_uint32                      ul_ret;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{wal_config_fbt_kick_user:: pst_mac_vap/puc_param is null ptr %d, %d!}\r\n", pst_mac_vap, puc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_kick_user_param = (mac_cfg_kick_user_param_stru *)puc_param;

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_config_fbt_kick_user::uc_rej_user[%d], uc_kick_user[%d], mac[%x%x]}\r\n",
                                pst_kick_user_param->uc_rej_user,
                                pst_kick_user_param->uc_kick_user,
                                pst_kick_user_param->auc_mac_addr[4],
                                pst_kick_user_param->auc_mac_addr[5]);

    /* ����rej���������н�ֹ�û����ӵĹ��� */
    ul_ret = hmac_config_fbt_rej_user(pst_mac_vap, us_len, puc_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_config_kick_user::hmac_fbt_add_disable_user failed[%d].}",ul_ret);
        return ul_ret;
    }

    /* ����ǹ㲥��ַ������kick=1�������kick user���޳����û� */
    if (OAL_FALSE == oal_is_broadcast_ether_addr(pst_kick_user_param->auc_mac_addr))
    {
        if (OAL_TRUE == pst_kick_user_param->uc_kick_user)
        {
            ul_ret = hmac_config_kick_user(pst_mac_vap, us_len, puc_param);
            if (OAL_SUCC != ul_ret)
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_config_fbt_kick_user::hmac_config_kick_user failed[%d].}",ul_ret);
            }
        }
    }

    return ul_ret;
}
/*****************************************************************************
 �� �� ��  : wal_config_set_okc_ie
 ��������  : AP ����okc ��ϢԪ�ص�VAP �ṹ��
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 *pus_len
             oal_uint8 *puc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��19��
    ��    ��   : xiexiaoming 00226265
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_config_set_okc_ie(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_set_okc_ie(pst_mac_vap, us_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_get_all_sta_info
 ��������  : AP ��ȡ�����ѹ���STA��Ϣ
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint16 *pus_len
             oal_uint8 *puc_param
 �������  : oal_uint32
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��19��
    ��    ��   : luolingzhi 00225940
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_config_get_all_sta_info(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_get_all_sta_info(pst_mac_vap, pus_len, puc_param);
}

/*****************************************************************************
 �� �� ��  : wal_config_fbt_start_scan
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/

OAL_STATIC oal_uint32 wal_config_fbt_start_scan(mac_vap_stru * pst_mac_vap, oal_uint16 us_len, oal_uint8 * puc_param)
{
    return hmac_config_fbt_start_scan(pst_mac_vap, us_len, puc_param);
}

#endif


/*****************************************************************************
 �� �� ��  : wal_config_vap_destroy
 ��������  : down����ɾ��vap
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��11��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_config_vap_destroy(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    hmac_vap_stru *pst_hmac_vap;
    pst_hmac_vap  = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    return hmac_vap_destroy(pst_hmac_vap);
}

#ifdef _PRE_WLAN_FEATURE_11K
OAL_STATIC oal_uint32  wal_config_send_neighbor_req(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    return hmac_config_send_neighbor_req(pst_mac_vap, us_len, puc_param);
}
#endif //_PRE_WLAN_FEATURE_11K

OAL_STATIC oal_uint32  wal_config_vendor_cmd_get_channel_list(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    return hmac_config_vendor_cmd_get_channel_list(pst_mac_vap, pus_len, puc_param);
}

/*lint -e19*/
oal_module_symbol(wal_drv_cfg_func_hook_init);
/*lint +e19*/
#ifdef _PRE_WLAN_FEATURE_HILINK
oal_module_symbol(wal_config_set_okc_ie);
oal_module_symbol(wal_config_fbt_kick_user);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

