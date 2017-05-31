/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_vap.h
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   : dmac_vap.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_VAP_H__
#define __DMAC_VAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "hal_ext_if.h"
#include "mac_vap.h"
#include "dmac_user.h"
#include "dmac_ext_if.h"
#include "dmac_ap_pm.h"
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_VAP_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define DMAC_MAX_SW_RETRIES         10  /* ���ݱ����ش����� */
#define DMAC_MGMT_MAX_SW_RETRIES    3   /* �������ش����� */
#define DMAC_MAX_AMPDU_LENGTH_PERFOMANCE_COUNT    32   /* ���м��������ľۺϳ���*/
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#define BTCOEX_LINKLOSS_OCCUPIED_NUMBER (8)
#endif
#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)

#define IS_OPEN_PMF_REG(_pst_dmac_vap)  (0 != ((_pst_dmac_vap)->ul_user_pmf_status))
#endif

#define DMAC_IS_LINKLOSS(_pst_dmac_vap) ((_pst_dmac_vap->st_linkloss_info.us_link_loss) > (_pst_dmac_vap->st_linkloss_info.us_linkloss_threshold))

#define DMAC_MAX_TX_SUCCESSIVE_FAIL_PRINT_THRESHOLD_BTCOEX    (40)   /* ��������ʧ�ܵĴ�ӡRF�Ĵ�������*/
#define DMAC_MAX_TX_SUCCESSIVE_FAIL_PRINT_THRESHOLD    (20)   /* ��������ʧ�ܵĴ�ӡRF�Ĵ�������*/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* beacon֡����ö�� */
typedef enum
{
    DMAC_VAP_BEACON_BUFFER1,
    DMAC_VAP_BEACON_BUFFER2,

    DMAC_VAP_BEACON_BUFFER_BUTT
}dmac_vap_beacon_buffer_enum;
/* ���ղ�ͬ�ۺϳ��ȷ����������ö��ֵ*/
/*0:1~14 */
/*1:15~17 */
/*2:18~30 */
/*3:31~32 */
typedef enum
{
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_0,
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_1,
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_2,
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_3,
    DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_BUTT
}dmac_count_by_ampdu_length_enum;
/* ͳ�Ƶ�AMPDU������ֵö��ֵ*/
typedef enum
{
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_1 = 1,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_14 = 14,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_15 = 15,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_17 = 17,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_18 = 18,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_30 = 30,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_31 = 31,
    DMAC_AMPDU_LENGTH_COUNT_LEVEL_32 = 32
}dmac_count_by_ampdu_length_level_enum;

typedef oal_uint8 dmac_vap_beacon_buffer_enum_uint8;
#ifdef _PRE_WLAN_DFT_STAT
#define   DMAC_VAP_DFT_STATS_PKT_INCR(_member, _cnt)        ((_member) += (_cnt))
#define   DMAC_VAP_DFT_STATS_PKT_SET_ZERO(_member)        ((_member) = (0))
#else
#define   DMAC_VAP_DFT_STATS_PKT_INCR(_member, _cnt)
#define   DMAC_VAP_DFT_STATS_PKT_SET_ZERO(_member)
#endif
#define   DMAC_VAP_STATS_PKT_INCR(_member, _cnt)            ((_member) += (_cnt))


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
/* vap tx�������Ӽܹ������ĵ���ó�Ա */
typedef struct
{
    oal_uint16  us_rts_threshold;       /* rts��ֵ */
    oal_uint8   uc_mcast_rate;          /* �㲥���� */
    oal_uint8   auc_resv[1];            /* �ֽڶ��� */
}dmac_vap_tx_param_stru;

#ifdef _PRE_WLAN_FEATURE_ROAM

#define ROAM_TRIGGER_COUNT_THRESHOLD           (5)
#define ROAM_TRIGGER_RSSI_NE80_DB              (-80)
#define ROAM_TRIGGER_RSSI_NE75_DB              (-75)
#define ROAM_TRIGGER_RSSI_NE70_DB              (-70)
#define ROAM_TRIGGER_INTERVAL_10S              (10 * 1000)
#define ROAM_TRIGGER_INTERVAL_15S              (15 * 1000)
#define ROAM_TRIGGER_INTERVAL_20S              (20 * 1000)
#define ROAM_WPA_CONNECT_INTERVAL_TIME         (5 * 1000)    /* ��������������֮���ʱ������WIFI+ �ϲ��л�Ƶ�� */

typedef struct
{
    oal_int8    c_trigger_2G;           /* 2G���δ�������   */
    oal_int8    c_trigger_5G;           /* 5G���δ�������   */
    oal_uint8   auc_recv[2];
    oal_uint32  ul_cnt;                 /* ���δ���������       */
    oal_uint32  ul_time_stamp;          /* ���δ�����ʱ���     */
    oal_uint32  ul_ip_obtain_stamp;     /* �ϲ��ȡIP��ַʱ��� */
    oal_uint32  ul_ip_addr_obtained;    /* IP��ַ�Ƿ��ѻ�ȡ */
}dmac_vap_roam_trigger_stru;
#endif //_PRE_WLAN_FEATURE_ROAM

/*�޸Ĵ˽ṹ����Ҫͬ��֪ͨSDT�������ϱ��޷�����*/
typedef struct
{
    oal_int32    ul_signal;

    oal_uint32   ul_drv_rx_pkts;     /* �����������ݰ���Ŀ */
    oal_uint32   ul_hw_tx_pkts;      /* ��������ж��ϱ����ͳɹ��ĸ��� */
    oal_uint32   ul_drv_rx_bytes;    /* ���������ֽ�����������80211ͷβ */
    oal_uint32   ul_hw_tx_bytes;     /* ��������ж��ϱ����ͳɹ��ֽ��� */
    oal_uint32   ul_tx_retries;      /*�����ش�����*/
    oal_uint32   ul_rx_dropped_misc; /*����ʧ�ܴ���*/
    oal_uint32   ul_tx_failed;     /* ����ʧ�ܴ���������ͳ������֡ */
//    oal_rate_info_stru st_txrate; /*vap��ǰ����*/

    oal_int16    s_free_power;  /*����*/
    /*ά����Ҫ���ӽ϶��ά�⣬ʹ��ά��Ԥ��������*/
#ifdef _PRE_WLAN_DFT_STAT
    /***************************************************************************
                                ���հ�ͳ��
    ***************************************************************************/

    /* ���������������ش���(�������쳣��)���ͷ�����MPDU��ͳ�� */
    oal_uint32  ul_rx_ppdu_dropped;                             /* Ӳ���ϱ���vap_id�����ͷŵ�MPDU���� */

    /* ���ͳ�ƵĽ��յ�MPDU���������������Ӧ����MACӲ��ͳ��ֵ��ͬ */
    oal_uint32  ul_rx_mpdu_total_num;                           /* ���������ϱ���������д����MPDU�ܸ��� */

    /* MPDU������д���ʱ���������ͷ�MPDU����ͳ�� */
    oal_uint32  ul_rx_ta_check_dropped;                         /* ��鷢�Ͷ˵�ַ�쳣���ͷ�һ��MPDU */
    oal_uint32  ul_rx_key_search_fail_dropped;                  /*  */
    oal_uint32  ul_rx_tkip_mic_fail_dropped;                    /* ����������statusΪ tkip mic fail�ͷ�MPDU */
    oal_uint32  ul_rx_replay_fail_dropped;                      /* �طŹ������ͷ�һ��MPDU */
    oal_uint32  ul_rx_security_check_fail_dropped;              /* ���ܼ��ʧ��*/
    oal_uint32  ul_rx_alg_process_dropped;                      /* �㷨������ʧ�� */
    oal_uint32  ul_rx_null_frame_dropped;                       /* ���յ���֡�ͷ�(֮ǰ���������Ѿ�������д���) */
    oal_uint32  ul_rx_abnormal_dropped;                         /* �����쳣����ͷ�MPDU */
    oal_uint32  ul_rx_mgmt_mpdu_num_cnt;                         /* ���յ��Ĺ���֡�Ϳ���֡ͳ��*/
    oal_uint32  ul_rx_mgmt_abnormal_dropped;                    /* ���յ�����֡�����쳣������vap����devΪ�յ� */

    /***************************************************************************
                                ���Ͱ�ͳ��
    ***************************************************************************/
    oal_uint32  ul_drv_tx_pkts;     /* ����������Ŀ������Ӳ������Ŀ */
    oal_uint32  ul_drv_tx_bytes;    /* ���������ֽ���������80211ͷβ */
    /* �������̷����쳣�����ͷŵ����ݰ�ͳ�ƣ�MSDU���� */
    oal_uint32  ul_tx_abnormal_mpdu_dropped;                    /* �쳣����ͷ�MPDU������ָvap����userΪ�յ��쳣 */
    /* ��������з��ͳɹ���ʧ�ܵ����ݰ�ͳ�ƣ�MPDU���� */
    oal_uint32  ul_tx_mpdu_succ_num;                            /* ����MPDU�ܸ��� */
    oal_uint32  ul_tx_mpdu_fail_num;                            /* ����MPDUʧ�ܸ��� */
    oal_uint32  ul_tx_ampdu_succ_num;                           /* ���ͳɹ���AMPDU�ܸ��� */
    oal_uint32  ul_tx_mpdu_in_ampdu;                            /* ����AMPDU��MPDU�����ܸ��� */
    oal_uint32  ul_tx_ampdu_fail_num;                           /* ����AMPDUʧ�ܸ��� */
    oal_uint32  ul_tx_mpdu_fail_in_ampdu;                       /* ����AMPDU��MPDU����ʧ�ܸ��� */
    oal_uint32  aul_tx_count_per_apmpdu_length[DMAC_COUNT_BY_AMPDU_LENGTH_INDEX_BUTT];/*��Բ�ͬ�ۺϳ��ȵ�֡ͳ�Ʒ��͵ĸ���*/
    oal_uint32  ul_tx_cts_fail;                                  /*����rtsʧ�ܵ�ͳ��*/
    oal_uint8  uc_tx_successive_mpdu_fail_num;                  /*��������ʧ�ܵ�ͳ��*/
    oal_uint8  uc_reserve[3];                                   /*�����ֽ�*/
#endif
}dmac_vap_query_stats_stru;

typedef oal_uint8 dmac_linkloss_status_enum_uint8;


typedef struct
{
    oal_uint32                        ul_old_dot11BeaconPeriod;     /* ��¼beacon���ڣ���ֹ���ڸı�linkloss������׼ȷ */
    oal_uint16                        us_linkloss_threshold;       /*  LinkLoss����  */
    oal_uint16                        us_link_loss;                /*  LinkLoss������ */
    oal_bool_enum_uint8               en_old_bt_on;                 /* ��¼bt���صľ�״̬�����bt�����Ƿ��б仯 */
    oal_bool_enum_uint8               en_old_dbac_runing;         /* ��¼dbac���صľ�״̬�����dbac�����Ƿ��б仯 */
    oal_bool_enum_uint8               en_old_far_distance;        /* ��¼Զ�����ľ�״̬��Զ��Ϊtrue*/
    oal_uint8                         uc_linkloss_times;            /* ��¼linkloss��ǰ����ֵ����������ı�������ӳbeacon�����ڱ��� */
}dmac_vap_linkloss_stru;


#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
#define DMAC_MAX_IPV4_ENTRIES         8
#define DMAC_MAX_IPV6_ENTRIES         8
typedef struct
{
    oal_uint8                         auc_ip_addr[OAL_IPV4_ADDR_SIZE];
}dmac_vap_ipv4_addr_stru;

typedef struct
{
    oal_uint8                         auc_ip_addr[OAL_IPV6_ADDR_SIZE];
}dmac_vap_ipv6_addr_stru;

typedef struct
{
    dmac_vap_ipv4_addr_stru           ast_ipv4_entry[DMAC_MAX_IPV4_ENTRIES];
    dmac_vap_ipv6_addr_stru           ast_ipv6_entry[DMAC_MAX_IPV6_ENTRIES];
}dmac_vap_ip_entries_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
typedef struct
{
    oal_uint16  aus_last_qos_seq_num[WLAN_TID_MAX_NUM];         /* ��¼��Proxy STA����Ľ�������Root Ap��ǰһ��QoS֡��seq num */
    oal_uint16  us_non_qos_seq_num;                             /* ��¼��Proxy STA����Ľ�������Root Ap��ǰһ����QOS֡��seq num */
    oal_uint8   uc_lut_idx;
    oal_uint8   auc_resv[1];
} dmac_vap_psta_stru;
#define dmac_vap_psta_lut_idx(vap)   ((vap)->st_psta.uc_lut_idx)
#endif

#ifdef _PRE_WLAN_FEATURE_11K
typedef struct mac_rrm_info_tag
{
    mac_action_rm_rpt_stru              *pst_rm_rpt_action;
    mac_meas_rpt_ie_stru                *pst_meas_rpt_ie;           /* Measurement Report IE Addr */
    mac_bcn_rpt_stru                    *pst_bcn_rpt_item;          /* Beacon Report Addr */
    oal_netbuf_stru                     *pst_rm_rpt_mgmt_buf;       /* Report Frame Addr for Transfer */
    mac_scan_req_stru                   *pst_scan_req;

    oal_uint8                            uc_quiet_count;
    oal_uint8                            uc_quiet_period;
    oal_mac_quiet_state_uint8            en_quiet_state;
    oal_uint8                            uc_link_dialog_token;

    oal_uint8                            uc_ori_max_reg_pwr;
    oal_uint8                            uc_local_pwr_constraint;
    oal_uint8                            uc_ori_max_pwr_flush_flag;
    oal_uint8                            uc_rsv;

    oal_int8                             c_link_tx_pwr_used;
    oal_int8                             c_link_max_tx_pwr;
    oal_uint8                            auc_act_meas_start_time[8];
    oal_uint16                           us_quiet_duration;

    oal_uint16                           us_quiet_offset;
    oal_uint16                           us_rm_rpt_action_len;      /* Report Frame Length for Transfer */

    oal_dlist_head_stru                  st_meas_rpt_list;
    mac_bcn_req_info_stru                st_bcn_req_info;
    frw_timeout_stru                     st_quiet_timer;    /* quiet��ʱ����ÿ�ν���quietʱ������quiet duration��ʱ�����˳�quiet */
    frw_timeout_stru                     st_offset_timer;   /* ���һ��tbtt�жϿ�ʼʱ����offset��ʱ����offsetʱ���ʱ�������quiet��������quiet��ʱ�� */
}mac_rrm_info_stru;

#endif //_PRE_WLAN_FEATURE_11K

#ifdef _PRE_WLAN_FEATURE_VOWIFI
typedef struct
{
    oal_uint8           uc_rssi_trigger_cnt;        /* ͳ���ź����������������޵Ĵ��� ��1��100��*/
    oal_uint8           auc_resv[3];
    oal_uint64          ull_rssi_timestamp_ms;     /* ʱ�����ms���� */
    oal_uint64          ull_arp_timestamp_ms;      /* arp req device��̽��ʧ��(tx 5s�����κ����ݽ���) */

    oal_uint32   ul_arp_rx_succ_pkts;  /* TX arp_reqʱ�̼�¼�ĵ�ʱrx_succ_pktsֵ */
    oal_uint32   ul_tx_failed;         /* ����ʧ�����ն����Ĵ���������ͳ������֡  */
    oal_uint32   ul_tx_total;          /* �����ܼƣ�����ͳ������֡  */

}mac_vowifi_status_stru;

#endif /* _PRE_WLAN_FEATURE_VOWIFI */

/* dmac vap */
typedef struct dmac_vap_tag
{
    mac_vap_stru                     st_vap_base_info;                                  /* ����VAP��Ϣ */

    oal_uint32                       ul_active_id_bitmap;                               /* ��Ծuser��bitmap */

    oal_uint8                       *pauc_beacon_buffer[DMAC_VAP_BEACON_BUFFER_BUTT];   /* VAP�¹�����beacon֡ */
    oal_uint8                        uc_beacon_idx;                                     /* ��ǰ����Ӳ��beacon֡����ֵ */
    oal_uint8                        uc_tim_offset_in_beacon;
    oal_uint16                       us_beacon_len;                                     /* beacon֡�ĳ��� */

    hal_to_dmac_vap_stru            *pst_hal_vap;                                       /* hal vap�ṹ */
    hal_to_dmac_device_stru         *pst_hal_device;                                    /* hal device�ṹ��������λ�ȡ */

    dmac_vap_linkloss_stru           st_linkloss_info;                                  /* linkloss���������Ϣ */
    oal_bool_enum_uint8              en_is_host_vap;                                    /* TRUE:��VAP��FALSE:��VAP */
    oal_uint8                        uc_default_ant_bitmap;                             /* Ĭ���������bitmap, ������д���������� */

    oal_uint8                        uc_sw_retry_limit;
    oal_uint8                        en_multi_user_multi_ac_flag;			    /* ���û������ȼ�ʱ�Ƿ�ʹ��ӵ������*/

    oal_traffic_type_enum_uint8      uc_traffic_type;                           /* ҵ�����ͣ��Ƿ��ж��û������ȼ� */

    oal_uint8                        uc_sta_pm_open_by_host;                /* sta �͹���״̬: HOST���Ƿ���˵͹��� */
    oal_uint8                        uc_cfg_pm_mode;                            /* �ֶ�������ĵ͹���ģʽ */
    oal_uint8                        uc_sta_pm_close_status;                    /* sta �͹���״̬, �������ģ��ĵ͹��Ŀ�����Ϣ */

    /* �ش��������� */
    oal_uint8                        uc_vap_tx_chain;                                   /* Ĭ��ʹ�õķ���ͨ������������֡����ʼ��ʹ�ã�ҵ������TXCS�㷨��д���������ݹ���֡������ʼ��ֵ��д */
    oal_uint16                       us_del_timeout;                                    /* �೤ʱ�䳬ʱɾ��ba�Ự �����0��ɾ�� */
    oal_uint8                        bit_bw_cmd:1;                                      /* �Ƿ�ʹ���������ݴ�������� 0:No  1:Yes */
    oal_uint8                        bit_beacon_timeout_times:7;                           /* sta�ȴ�beacon��ʱ���� */
    hal_tx_txop_alg_stru             st_tx_alg;                                         /* ��������֡���Ͳ��� */

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
    hal_tx_txop_alg_stru             st_tx_alg_vht;                                     /* VHT��������֡���Ͳ��� */
    hal_tx_txop_alg_stru             st_tx_alg_ht;                                      /* HT��������֡���Ͳ��� */
    hal_tx_txop_alg_stru             st_tx_alg_11ag;                                    /* 11a/g��������֡���Ͳ��� */
    hal_tx_txop_alg_stru             st_tx_alg_11b;                                     /* 11b��������֡���Ͳ��� */

    union
    {
        oal_uint8                    uc_mode_param_valid;                               /* �Ƿ�������ض�ģʽ�ĵ�������֡����������Ч(0=��, ����0=��) */
        struct{
            oal_uint8                bit_vht_param_vaild  : 1;                          /* VHT��������֡���������Ƿ���Ч(0=����Ч, 1=��Ч) */
            oal_uint8                bit_ht_param_vaild   : 1;                          /* HT��������֡���������Ƿ���Ч(0=����Ч, 1=��Ч) */
            oal_uint8                bit_11ag_param_vaild : 1;                          /* 11a/g��������֡���������Ƿ���Ч(0=����Ч, 1=��Ч) */
            oal_uint8                bit_11b_param_vaild  : 1;                          /* 11b��������֡���������Ƿ���Ч(0=����Ч, 1=��Ч) */
            oal_uint8                bit_reserve          : 4;
        }st_spec_mode;
    }un_mode_valid;
    oal_uint8                        auc_resv1[3];
#endif

    hal_tx_txop_alg_stru             st_tx_data_mcast;                                  /* �鲥����֡���� */
    hal_tx_txop_alg_stru             st_tx_data_bcast;                                  /* �㲥����֡����*/
    hal_tx_txop_alg_stru             ast_tx_mgmt_ucast[WLAN_BAND_BUTT];                  /* ��������֡����*/
    hal_tx_txop_alg_stru             ast_tx_mgmt_bmcast[WLAN_BAND_BUTT];                 /* �鲥���㲥����֡����*/

    oal_void                        *p_alg_priv;                                        /* VAP�����㷨˽�нṹ�� */

    oal_uint8                       *puc_tim_bitmap;                                    /* ���ر����tim_bitmap��APģʽ��Ч */
    oal_uint8                        uc_tim_bitmap_len;
    oal_uint8                        uc_ps_user_num;                                    /* ���ڽ���ģʽ���û�����Ŀ��APģʽ��Ч */
    oal_uint8                        uc_dtim_count;
    oal_uint8                        uc_uapsd_max_depth;                                /* U-APSD���ܶ��е�������*/
    oal_bool_enum_uint8              en_beacon_chain_active;                            /* beacon�Ƿ�˫·��������, 0-�ر�, 1-���� */
    oal_bool_enum_uint8              en_dtim_ctrl_bit0;                                 /* ���ڱ�ʾDTIM Control�ֶεı���0�Ƿ���1�� */
#if defined(_PRE_WLAN_FEATURE_PM) || defined(_PRE_WLAN_FEATURE_STA_PM)
    oal_netbuf_stru                 *pst_wow_probe_resp;                                /* wowʹ��ʱ,׼����probe response֡*/
    oal_netbuf_stru                 *pst_wow_null_data;                                 /* wowʹ��ʱ,׼����null data֡,STAģʽʱ����*/
    oal_uint16                       us_wow_probe_resp_len;

#ifdef _PRE_WLAN_FEATURE_11K
    oal_uint8                        bit_bcn_table_switch: 1;
    oal_uint8                        bit_11k_enable      : 1;
    oal_uint8                        bit_11v_enable      : 1;
    oal_uint8                        bit_rsv1            : 5;
#else
    oal_uint8                        auc_resv2[1];
#endif

#ifdef _PRE_WLAN_FEATURE_11R
    oal_uint8                        bit_11r_enable      : 1;
    oal_uint8                        bit_rsv2            : 7;
#else
    oal_uint8                        auc_resv3[1];
#endif

#else

#ifdef _PRE_WLAN_FEATURE_11K
    oal_uint8                        bit_bcn_table_switch: 1;
    oal_uint8                        bit_11k_enable      : 1;
    oal_uint8                        bit_11v_enable      : 1;
    oal_uint8                        bit_rsv3            : 5;

#else
    oal_uint8                        auc_resv4[11];
#endif
#ifdef _PRE_WLAN_FEATURE_11R
    oal_uint8                        bit_11r_enable      : 1;
    oal_uint8                        bit_rsv4            : 7;
#else
    oal_uint8                        auc_resv5[1];
#endif

#endif
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    dmac_vap_psta_stru               st_psta;
#endif

    oal_uint32                       ul_obss_scan_timer_remain;                  /* 02���ʱ����ʱ65s, OBSSɨ�趨ʱ������Ϊ�����ӣ�ͨ����������ʵ�ִ�ʱ��*/
    oal_uint8                        uc_obss_scan_timer_started;
    oal_uint8                        uc_bcn_tout_max_cnt;                      /* beacon�����ղ������˯�ߴ��� */

#ifdef _PRE_WLAN_FEATURE_STA_PM
    oal_uint8                       uc_null_frm_ofdm_succ_cnt;
    oal_uint8                       uc_null_frm_cnt;
#else
    oal_uint8                       uac_resv5[2];
#endif  /* _PRE_WLAN_FEATURE_STA_PM */

    oal_bool_enum_uint8              en_bfee_actived;
    oal_bool_enum_uint8              en_bfer_actived;
    oal_bool_enum_uint8              en_mu_bfee_actived;
    oal_bool_enum_uint8              en_txstbc_actived;
    oal_uint8                        uc_ps_poll_pending;
    #ifdef _PRE_WLAN_FEATURE_TSF_SYNC
    oal_uint8                        uc_beacon_miss_cnt;                /* beacon miss ���� */
    #else
    oal_uint8                        uac_resv4[1];
    #endif
#if(_PRE_WLAN_FEATURE_PMF == _PRE_PMF_HW_CCMP_BIP)
    oal_uint32                       ul_user_pmf_status;                 /* ��¼��vap��user pmfʹ�ܵ������������Ӳ��vap�Ƿ�򿪼ӽ��ܿ��� */
#endif

#if defined (_PRE_WLAN_FEATURE_PM) || defined(_PRE_WLAN_FEATURE_STA_PM)
    oal_void*                        pst_pm_handler;  //ap��sta���ã���ʱ��ǿת������ṹ��
#endif
    /*ͳ����Ϣ+��Ϣ�ϱ������ֶΣ��޸�����ֶΣ������޸�SDT���ܽ�����ȷ*/
    dmac_vap_query_stats_stru        st_query_stats;
    /* ��������ʹ�� */
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    oal_uint8                        uc_protocol_rate_dscr;                          /* ������������Э��������λ���ֵ�����ڳ���ģʽ�¸���֡�� */
    oal_uint8                        uc_bw_flag;                                     /* ������������40M��־ */
    oal_uint8                        uc_short_gi;                                    /* short gi�Ƿ�ʹ�� */
#endif
    hal_to_dmac_vap_stru            *pst_p2p0_hal_vap;                               /* p2p0 hal vap�ṹ */
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_cfg_p2p_noa_param_stru         st_p2p_noa_param;
    mac_cfg_p2p_ops_param_stru         st_p2p_ops_param;
#endif

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    oal_switch_enum_uint8             en_arp_offload_switch;         /* ARP offload�Ŀ��� */
    oal_uint8                         auc_resv9[3];
    dmac_vap_ip_entries_stru         *pst_ip_addr_info;              /* Host��IPv4��IPv6��ַ */
#endif

#ifdef _PRE_WLAN_FEATURE_TSF_SYNC
    oal_uint16                          us_sync_tsf_value;
    oal_uint64                          ul_old_beacon_timestamp;
#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
    dmac_vap_roam_trigger_stru          st_roam_trigger;
#endif  //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_11K
    mac_rrm_info_stru                  *pst_rrm_info;
#endif //_PRE_WLAN_FEATURE_11K
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_vap_btcoex_stru            st_dmac_vap_btcoex;
#endif


#ifdef _PRE_WLAN_FEATURE_VOWIFI
    //mac_vowifi_status_stru              st_vowifi_status;
    mac_vowifi_status_stru              *pst_vowifi_status;
#endif /* _PRE_WLAN_FEATURE_VOWIFI */

    oal_uint16                       us_ext_tbtt_offset;            /* �ⲿtbtt offset����ֵ*/
    oal_uint16                       us_in_tbtt_offset;             /* �ڲ�tbtt offset����ֵ*/
    oal_uint16                       us_beacon_timeout;             /* beacon timeout����ֵ*/
	oal_uint8                  	     uc_psm_dtim_period;		    /* ʵ�ʲ��õ�dtim period*/
	oal_uint8                  	     uc_psm_auto_dtim_cnt;		    /* �Զ�dtim�ļ�����*/
	oal_uint16                  	 us_psm_listen_interval;		/* ʵ�ʲ��õ�listen_interval*/

	oal_bool_enum_uint8              en_non_erp_exist;              /* staģʽ�£��Ƿ���non_erp station */
}dmac_vap_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_vap_get_bss_type
 ��������  : ��ȡVAP���ͣ�ָ���Ƿ�Ϊ�գ��������ж�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VAP����
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_vap_mode_enum_uint8  dmac_vap_get_bss_type(mac_vap_stru *pst_vap)
{
    return pst_vap->en_vap_mode;
}

/*****************************************************************************
 �� �� ��  : dmac_vap_linkloss_zero
 ��������  :  ��linkloss��������0
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
OAL_STATIC OAL_INLINE oal_void dmac_vap_linkloss_clean(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_vap_btcoex_occupied_stru *pst_dmac_vap_btcoex_occupied;
#endif

    pst_dmac_vap->st_linkloss_info.us_link_loss = 0;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
    pst_dmac_vap_btcoex_occupied = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied);
    pst_dmac_vap_btcoex_occupied->uc_linkloss_index = 1;
    pst_dmac_vap_btcoex_occupied->uc_linkloss_occupied_times = 0;
#endif

}
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/*****************************************************************************
 �� �� ��  : dmac_psta_init_vap
 ��������  :  init psta
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��14��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_psta_init_vap(dmac_vap_stru *pst_dmac_vap)
{
    OAL_MEMZERO(&pst_dmac_vap->st_psta, OAL_SIZEOF(pst_dmac_vap->st_psta));
}
/*****************************************************************************
 �� �� ��  : dmac_psta_update_lut_range
 ��������  : ����dev��ʹ��״̬��vap��ģʽ������lut��Χ
 �������  : mac_device_stru *pst_device
 �������  : *us_start, *us_stop
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��14��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE  oal_void  dmac_psta_update_lut_range(mac_device_stru *pst_dev, dmac_vap_stru *pst_dmac_vap, oal_uint16 *us_start, oal_uint16 *us_stop)
{
    mac_vap_stru *pst_vap = &pst_dmac_vap->st_vap_base_info;

    if (mac_is_proxysta_enabled(pst_dev))
    {
        if(mac_vap_is_vsta(pst_vap))
        {
            *us_start = dmac_vap_psta_lut_idx(pst_dmac_vap);
            *us_stop  = dmac_vap_psta_lut_idx(pst_dmac_vap) + 1; // 32 is not valid for proxysta
        }
        else
        {
            *us_start = 0;
            *us_stop  = HAL_PROXYSTA_MAX_BA_LUT_SIZE; // hardware spec
        }
    }
    // else do nothing
}

#endif


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  dmac_vap_init(
                       dmac_vap_stru              *pst_vap,
                       oal_uint8                   uc_chip_id,
                       oal_uint8                   uc_device_id,
                       oal_uint8                   uc_vap_id,
                       mac_cfg_add_vap_param_stru *pst_param);
extern oal_uint32  dmac_vap_init_tx_frame_params(dmac_vap_stru *pst_dmac_vap, oal_bool_enum_uint8  en_mgmt_rate_init_flag);
extern oal_uint32  dmac_vap_init_tx_ucast_data_frame(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32  dmac_vap_sta_reset(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32  mac_vap_pause_tx(mac_vap_stru *pst_vap);
extern oal_uint32  mac_vap_resume_tx(mac_vap_stru *pst_vap);
extern oal_void  dmac_vap_pause_tx(mac_vap_stru *pst_mac_vap);

extern oal_void  dmac_vap_pause_tx_by_chl(mac_device_stru *pst_device, mac_channel_stru *pst_src_chl);
extern oal_void  dmac_vap_resume_tx_by_chl(mac_device_stru *pst_device, mac_channel_stru *pst_dst_channel);
extern oal_void  dmac_vap_update_bi_from_hw(mac_vap_stru *pst_mac_vap);
extern oal_void  dmac_vap_init_tx_data_ucast(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_protocol_mode, oal_uint8 uc_legacy_rate);
extern oal_uint32  dmac_vap_is_in_p2p_listen(mac_vap_stru *pst_mac_vap);
extern oal_void  dmac_vap_linkloss_init(dmac_vap_stru *pst_dmac_vap);
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)

#ifdef _PRE_WLAN_FEATURE_VOWIFI
extern void dmac_vap_vowifi_init(dmac_vap_stru *pst_dmac_vap);
extern void dmac_vap_vowifi_exit(dmac_vap_stru *pst_dmac_vap);
#endif /* _PRE_WLAN_FEATURE_VOWIFI */

extern oal_void  dmac_one_packet_send_null_data(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_ps);
#endif

#ifdef _PRE_WLAN_SW_CTRL_RSP
extern oal_void dmac_vap_update_rsp_frm_rate(oal_uint8 uc_vap_id, oal_uint8 uc_protocol_mode, oal_uint8 uc_bandwidth, oal_uint8 uc_ref_rate);
#endif /* */

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
extern oal_uint32 dmac_ie_proc_opmode_notify(mac_user_stru *pst_mac_user, mac_vap_stru *pst_mac_vap, mac_opmode_notify_stru *pst_opmode_notify);
extern oal_uint32 dmac_check_opmode_notify(mac_vap_stru *pst_mac_vap,oal_uint8 *puc_payload,oal_uint32 ul_msg_len,
                                                        mac_user_stru  *pst_mac_user);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_vap.h */
