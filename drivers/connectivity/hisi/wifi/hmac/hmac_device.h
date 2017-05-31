/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_device.h
  �� �� ��   : ����
  ��    ��   : l00279018
  ��������   : 2015��1��31��
  ����޸�   :
  ��������   : hmac_device.c ��ͷ�ļ�������hmac device�ṹ�Ķ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __HMAC_DEVICE_H__
#define __HMAC_DEVICE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "wlan_spec.h"
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "mac_vap.h"
#include "hmac_vap.h"
#ifdef _PRE_WLAN_TCP_OPT
#include "hmac_tcp_opt_struc.h"
#include "oal_hcc_host_if.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_DEVICE_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifdef _PRE_WLAN_TCP_OPT
#define HCC_TRANS_THREAD_POLICY    SCHED_FIFO
#define HCC_TRANS_THERAD_PRIORITY       (10)
#define HCC_TRANS_THERAD_NICE           (-10)
#endif

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/* �洢ÿ��ɨ�赽��bss��Ϣ */
typedef struct
{
    oal_dlist_head_stru    st_dlist_head;	    /* ����ָ�� */
    //oal_spin_lock_stru     st_lock;             /* �� */
    mac_bss_dscr_stru      st_bss_dscr_info;	/* bss������Ϣ�������ϱ��Ĺ���֡ */
}hmac_scanned_bss_info;

/* �洢��hmac device�µ�ɨ����ά���Ľṹ�� */
typedef struct
{
    oal_spin_lock_stru  st_lock;
    oal_dlist_head_stru st_bss_list_head;
    oal_uint32          ul_bss_num;
}hmac_bss_mgmt_stru;


/* ɨ�����н����¼ */
typedef struct
{
    hmac_bss_mgmt_stru           st_bss_mgmt;                              /* �洢ɨ��BSS����Ĺ���ṹ */
    mac_scan_chan_stats_stru     ast_chan_results[WLAN_MAX_CHANNEL_NUM];   /* �ŵ�ͳ��/������� */
    oal_uint8                    uc_chan_numbers;                          /* �˴�ɨ���ܹ���Ҫɨ����ŵ����� */
    oal_uint8                    uc_device_id : 4;
    oal_uint8                    uc_chip_id   : 4;
    oal_uint8                    uc_vap_id;                                /* ����ִ��ɨ���vap id */
    mac_scan_status_enum_uint8   en_scan_rsp_status;                       /* ����ɨ����ɷ��ص�״̬�룬�ǳɹ����Ǳ��ܾ� */

    oal_time_us_stru             st_scan_start_timestamp;                  /* ɨ��ά��ʹ�� */
    mac_scan_cb_fn               p_fn_cb;                                  /* �˴�ɨ������Ļص�����ָ�� */

    oal_uint64                   ull_cookie;                               /* ����P2P ���������ϱ���cookie ֵ */
    mac_vap_state_enum_uint8     en_vap_last_state;                        /* ����VAP����ɨ��ǰ��״̬,AP/P2P GOģʽ��20/40Mɨ��ר�� */
    oal_time_t_stru              st_scan_start_time;                       /* ɨ����ʼʱ��� */
}hmac_scan_record_stru;


/* ɨ�������ؿ�����Ϣ */
typedef struct
{
    /* scan ��ؿ�����Ϣ */
    oal_bool_enum_uint8                    en_is_scanning;               /* host���ɨ�������Ƿ�����ִ�� */
    oal_bool_enum_uint8                    en_is_random_mac_addr_scan;   /* �Ƿ�Ϊ���mac addrɨ�裬Ĭ�Ϲر�(���ƻ��꿪���·���) */
    oal_bool_enum_uint8                    en_complete;                   /* �ں���ͨɨ�������Ƿ���ɱ�־ */
    oal_bool_enum_uint8                    en_sched_scan_complete;        /* ����ɨ���Ƿ��������б�� */

    oal_cfg80211_scan_request_stru        *pst_request;               /* �ں��·���ɨ������ṹ�� */
    oal_cfg80211_sched_scan_request_stru  *pst_sched_scan_req;        /* �ں��·��ĵ���ɨ������ṹ�� */

    oal_wait_queue_head_stru               st_wait_queue;
    oal_spin_lock_stru                     st_scan_request_spinlock;            /* �ں��·���request��Դ�� */

    frw_timeout_stru                       st_scan_timeout;            /* ɨ��ģ��host��ĳ�ʱ������ʹ�õĶ�ʱ�� */
#if defined(_PRE_SUPPORT_ACS) || defined(_PRE_WLAN_FEATURE_DFS) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
    frw_timeout_stru                       st_init_scan_timeout;
#endif
    hmac_scan_record_stru                  st_scan_record_mgmt;        /* ɨ�����м�¼������Ϣ������ɨ�����ͷ���ɨ���ߵ������Ϣ */
}hmac_scan_stru;

typedef struct
{

    frw_timeout_stru    st_rx_dscr_opt_timer;     /* rx_dscr������ʱ�� */
    oal_uint32          ul_rx_pkt_num;
    oal_uint32          ul_rx_pkt_opt_limit;
    oal_uint32          ul_rx_pkt_reset_limit;
    oal_bool_enum_uint8 en_dscr_opt_state;        /* TRUE��ʾ�ѵ��� */
    oal_bool_enum_uint8 en_dscr_opt_enable;
}hmac_rx_dscr_opt_stru;

/* hmac device�ṹ�壬��¼ֻ������hmac��device������Ϣ */
typedef struct
{
    hmac_scan_stru                      st_scan_mgmt;                           /* ɨ�����ṹ�� */
#if  defined(_PRE_WIFI_DMT ) || (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    oal_uint8                           uc_desired_bss_num;                         /* ɨ�赽��������bss���� */
    oal_uint8                           auc_resv[3];
    oal_uint8                           auc_desired_bss_idx[WLAN_MAX_SCAN_BSS_NUM]; /* ���������bss��bss list�е�λ�� */
#endif
    oal_uint32                          ul_p2p_intf_status;
    oal_wait_queue_head_stru            st_netif_change_event;
    mac_device_stru                    *pst_device_base_info;                   /* ָ�򹫹�����mac device */
#if defined(_PRE_SUPPORT_ACS) || defined(_PRE_WLAN_FEATURE_DFS) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
    oal_bool_enum_uint8                 en_init_scan      : 1;
    oal_bool_enum_uint8                 en_start_via_priv : 1;
    oal_bool_enum_uint8                 en_in_init_scan   : 1;
    oal_bool_enum_uint8                 en_rescan_idle    : 1;
	oal_uint8							uc_resv_bit		  : 4;
    oal_uint8                           auc_resvx[3];
    mac_channel_stru                    ast_best_channel[WLAN_BAND_BUTT];
#endif
#if defined(_PRE_SUPPORT_ACS)
    frw_timeout_stru                    st_rescan_timer;
    oal_uint32                          ul_rescan_timeout;  // ms
#endif
#ifdef _PRE_WLAN_TCP_OPT
    oal_bool_enum_uint8        sys_tcp_rx_ack_opt_enable;
    oal_bool_enum_uint8        sys_tcp_tx_ack_opt_enable;
    oal_uint8                  auc_resev[2];

#endif
    hmac_rx_dscr_opt_stru      st_rx_dscr_opt;
#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION))
#ifdef CONFIG_HAS_EARLYSUSPEND
        struct early_suspend            early_suspend;      //early_suspend֧��
#else
        struct notifier_block           pm_notifier;         //��ͨ�ں˽���֧��
#endif
        oal_spin_lock_stru              st_suspend_lock;
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hmac_device_btcoex_stru st_hmac_device_btcoex;
#endif
}hmac_device_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern oal_uint32  hmac_board_exit(mac_board_stru *pst_board);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32 hmac_config_host_dev_init(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
extern oal_uint32 hmac_config_host_dev_exit(mac_vap_stru *pst_mac_vap);
extern oal_uint32  hmac_board_init(mac_board_stru *pst_board);
#else
extern oal_uint32  hmac_board_init(oal_uint32 ul_chip_max_num, mac_chip_stru *pst_chip);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_device.h */
