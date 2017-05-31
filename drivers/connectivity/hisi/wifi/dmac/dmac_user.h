/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_user.h
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   : dmac_user.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_USER_H__
#define __DMAC_USER_H__

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
#include "mac_user.h"
#include "dmac_tid.h"
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_USER_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/


#ifdef _PRE_WLAN_DFT_STAT
#define DMAC_UAPSD_STATS_INCR(_member)    ((_member)++)
#define DMAC_PSM_STATS_INCR(_member)      ((_member)++)
#else
#define DMAC_UAPSD_STATS_INCR(_member)
#define DMAC_PSM_STATS_INCR(_member)
#endif
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))
#define   DMAC_USER_STATS_PKT_INCR(_member, _cnt)            ((_member) += (_cnt))
#else
#define   DMAC_USER_STATS_PKT_INCR(_member, _cnt)
#endif


#define DMAC_COMPATIBILITY_PKT_NUM_LIMIT 2000

#define DMAC_GET_USER_SUPPORT_VHT(_pst_user)    \
        ((1 == (_pst_user)->st_vht_hdl.en_vht_capable)? OAL_TRUE : OAL_FALSE)

#define DMAC_GET_USER_SUPPORT_HT(_pst_user)    \
        ((1 == (_pst_user)->st_ht_hdl.en_ht_capable)? OAL_TRUE : OAL_FALSE)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
    DMAC_USER_PS_STATE_ACTIVE   = 0,
    DMAC_USER_PS_STATE_DOZE     = 1,

    DMAC_USER_PS_STATE_BUTT
}dmac_user_ps_state_enum;
typedef oal_uint8 dmac_user_ps_state_enum_uint8;

typedef enum
{
    DMAC_USER_STATE_PS,
    DMAC_USER_STATE_ACTIVE,

    DMAC_USER_STATE_BUTT
}dmac_user_state_enum;
typedef oal_uint8 dmac_user_state_enum_uint8;

typedef enum {
    PSM_QUEUE_TYPE_NORMAL,
    PSM_QUEUE_TYPE_IMPORTANT,

    PSM_QUEUE_TYPE_BUTT
}psm_queue_type_enum;
typedef oal_uint8 psm_queue_type_enum_uint8;

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

typedef struct
{
    oal_uint32  ul_uapsd_tx_enqueue_count;              /*dmac_uapsd_tx_enqueue���ô���*/
    oal_uint32  ul_uapsd_tx_dequeue_count;              /* ����֡����ͳ�� */
    oal_uint32  ul_uapsd_tx_enqueue_free_count;         /*��ӹ�����MPDU���ͷŵĴ�����һ�ο����ͷŶ��MPDU*/
    oal_uint32  ul_uapsd_rx_trigger_in_sp;              /*trigger��鷢�ִ���SP�еĴ���*/
    oal_uint32  ul_uapsd_rx_trigger_state_trans;        /*trigger����з�����Ҫ״̬ת���Ĵ���*/
    oal_uint32  ul_uapsd_rx_trigger_dup_seq;            /*trigger֡���ظ�֡�ĸ���*/
    oal_uint32  ul_uapsd_send_qosnull;                  /*����Ϊ�գ�����qos null data�ĸ���*/
    oal_uint32  ul_uapsd_send_extra_qosnull;            /*���һ��Ϊ����֡�����Ͷ���qosnull�ĸ���*/
    oal_uint32  ul_uapsd_process_queue_error;           /*���д�������г���Ĵ���*/
    oal_uint32  ul_uapsd_flush_queue_error;             /*flush���д�������г���Ĵ���*/
    oal_uint32  ul_uapsd_send_qosnull_fail;             /* ����qosnullʧ�ܴ��� */
}dmac_usr_uapsd_statis_stru;

typedef struct
{
    oal_uint32  ul_psm_enqueue_succ_cnt;                  /* psm���гɹ����֡���� */
    oal_uint32  ul_psm_enqueue_fail_cnt;                  /* psm�������ʧ�ܱ��ͷŵ�֡���� */
    oal_uint32  ul_psm_dequeue_fail_cnt;                  /* psm���г���ʧ�ܵ�֡���� */
    oal_uint32  ul_psm_dequeue_succ_cnt;                  /* psm���г��ӳɹ���֡���� */
    oal_uint32  ul_psm_send_data_fail_cnt;                /* psm���г��ӵ�����֡����ʧ�ܸ��� */
    oal_uint32  ul_psm_send_mgmt_fail_cnt;                /* psm���г��ӵĹ���֡����ʧ�ܸ��� */
    oal_uint32  ul_psm_send_null_fail_cnt;                /* AP����null dataʧ�ܵĴ��� */
    oal_uint32  ul_psm_resv_pspoll_send_null;             /* AP�յ��û���pspoll�����Ƕ�����û�л���֡�Ĵ��� */
    oal_uint32  ul_psm_rsp_pspoll_succ_cnt;               /* AP�յ��û���pspoll�����ͻ���֡�ɹ��Ĵ��� */
    oal_uint32  ul_psm_rsp_pspoll_fail_cnt;               /* AP�յ��û���pspoll�����ͻ���֡ʧ�ܵĴ��� */
}dmac_user_psm_stats_stru;


typedef struct
{
    oal_spin_lock_stru          st_lock_uapsd;                      /*uapsd������*/
    oal_netbuf_head_stru        st_uapsd_queue_head;                /*uapsd���ܶ���ͷ*/
    oal_atomic                  uc_mpdu_num;                        /*��ǰ���ܶ������mpdu����*/
    oal_uint16                  us_uapsd_trigseq[WLAN_WME_AC_BUTT]; /*���һ��trigger֡��sequence*/
    dmac_usr_uapsd_statis_stru *pst_uapsd_statis;                  /*������ͳ��ά����Ϣ*/
}dmac_user_uapsd_stru;

typedef struct
{
    oal_spin_lock_stru          st_lock_ps;                   /* �Զ��к�ul_mpdu_num����ʱ��Ҫ���� */
    oal_netbuf_head_stru        st_ps_queue_head;             /* �û����ܻ������ͷ */
    oal_atomic                  uc_mpdu_num;                  /* �û����ܻ���������Ѵ��ڵ�mpdu���� */
    oal_bool_enum_uint8         en_is_pspoll_rsp_processing;  /* TURE:��ǰ��pspoll���ڴ���FALSE:��ǰû��pspoll���ڴ���*/
    oal_uint8                   uc_ps_time_count;
    oal_uint8                   auc_resv[2];
    dmac_user_psm_stats_stru   *pst_psm_stats;
}dmac_user_ps_stru;
typedef struct
{
    oal_int32    ul_signal;
    oal_uint32   ul_drv_rx_pkts;      /* ��������(Ӳ���ϱ�������rx���������ɹ���֡)��Ŀ������ͳ������֡ */
    oal_uint32   ul_hw_tx_pkts;      /* ��������ж��ϱ����ͳɹ��ĸ��� ������ͳ������֡ */
    oal_uint32   ul_drv_rx_bytes;    /* ���������ֽ�����������80211ͷβ */
    oal_uint32   ul_hw_tx_bytes;     /* ��������ж��ϱ����ͳɹ��ֽ��� */
    oal_uint32   ul_tx_retries;      /*�����ش�����*/
    oal_uint32   ul_rx_dropped_misc; /*����ʧ��(����������֡)����*/
    oal_uint32   ul_tx_failed;      /* ����ʧ�����ն����Ĵ���������ͳ������֡  */

    oal_uint32   ul_hw_tx_failed;   /* ��������ж��ϱ�����ʧ�ܵĸ���������ͳ������֡ */
    oal_uint32   ul_tx_total;       /* �����ܼƣ�����ͳ������֡  */

}dmac_user_query_stats_stru;

/* ���ƽ��rssiͳ����Ϣ�ṹ�� */
typedef struct
{
    oal_int32       l_tx_rssi;                  /* ��¼ACK RSSI���ۼ�ֵ */
    oal_int32       l_rx_rssi;                  /* ��¼����RSSI���ۼ�ֵ */
    oal_uint16      us_tx_rssi_stat_count;      /* ����ƽ��rssiͳ�Ƶķ�����Ŀ */
    oal_uint16      us_rx_rssi_stat_count;      /* ����ƽ��rssiͳ�Ƶķ�����Ŀ */
}dmac_rssi_stat_info_stru;

/* ���ƽ������ͳ����Ϣ�ṹ�� */
typedef struct
{
    oal_uint32      ul_tx_rate;                 /* ��¼�������ʵ��ۼ�ֵ */
    oal_uint32      ul_rx_rate;                 /* ��¼�������ʵ��ۼ�ֵ */
    oal_uint16      us_tx_rate_stat_count;      /* ����ƽ��rateͳ�Ƶķ�����Ŀ */
    oal_uint16      us_rx_rate_stat_count;      /* ����ƽ��rateͳ�Ƶķ�����Ŀ */
}dmac_rate_stat_info_stru;

typedef struct
{
    /* �û�������Ϣ */
    wlan_protocol_enum_uint8 en_protocol;                        /* Э��ģʽ */
    hal_channel_assemble_enum_uint8 en_bandwidth;                       /* �������� */

    /* �㷨�õ��ĸ�����־λ */
    oal_bool_enum_uint8 en_dmac_rssi_stat_flag;             /* �Ƿ����ƽ��rssiͳ�� */
    oal_bool_enum_uint8 en_dmac_rate_stat_flag;             /* �Ƿ����ƽ������ͳ�� */

    dmac_rssi_stat_info_stru st_dmac_rssi_stat_info;             /* ���ƽ��rssiͳ����Ϣ�ṹ��ָ�� */
    dmac_rate_stat_info_stru st_dmac_rate_stat_info;             /* ���ƽ������ͳ����Ϣ�ṹ��ָ�� */
}dmac_user_rate_info_stru;


typedef struct
{
    /* ����������ܴ���DMAC USER�ṹ���ڵĵ�һ�� */
    mac_user_stru                               st_user_base_info;                  /* hmac user��dmac user�������� */

    /* ��ǰVAP������AP��STAģʽ�������ֶ�Ϊuser��STA��APʱ�����ֶΣ�������ֶ���ע��!!! */
    oal_uint8                                   uc_lut_index;                       /* user��Ӧ��Ӳ����������Ծ�û�id */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint8                                   auc_resv;
    oal_uint16                                  us_non_qos_seq_frag_num;                 /* ��¼���û���QOS֡��seq+frag num*/
#else
    oal_uint8                                   auc_res[3];
#endif
    oal_uint8                                   auc_txchain_mask[WLAN_NSS_BUTT];    /* ÿ�ֿռ����¶�Ӧ��TX CHAIN MASK */
    dmac_tid_stru                               ast_tx_tid_queue[WLAN_TID_MAX_NUM]; /* ����tid������� */
    oal_void                                   *p_alg_priv;                         /* �û������㷨˽�нṹ�� */
    oal_uint16                                  us_partial_aid;
    oal_uint8                                   uc_groupid;
    oal_int8                                    c_rx_rssi;                              /* �û�����RSSIͳ���� */
    oal_uint16                                  aus_txseqs_frag[WLAN_TID_MAX_NUM];      /* ��Ƭ���ĵ�seq num */
    oal_uint16                                  aus_txseqs[WLAN_TID_MAX_NUM];           /* ����tid��Ӧ��seq num */

    /* ��ǰVAP������APģʽ�������ֶ�Ϊuser��STAʱ�����ֶΣ�������ֶ���ע��!!! */
    oal_uint8                                   bit_ps_mode     : 1,                /* ap�������û�����ģʽ��PSM�� */
                                                bit_active_user : 1,                /* �Ƿ��Ծ�û����û������� */
                                                bit_forbid_rts  : 1,                /* �Ƿ�ǿ�ƽ���RTS(�ڿ���RTS���ڼ���������ʱ����RTS) */
                                                bit_resv        : 5;

    oal_bool_enum_uint8                         en_vip_flag;                        /* ֻ�㷨�����ã�ͨ�������������ã�TRUE: VIP�û�, FALSE: ��VIP�û� */
    dmac_user_smartant_training_enum_uint8      en_smartant_training;               /* ��������ѵ��״̬  */
    oal_bool_enum_uint8                         en_delete_ba_flag;                  /* ɾ��ba��־��ֻ�㷨ͨ���ӿ��޸ģ�autorate��Э��ģʽʱ��Ϊtrue */

    dmac_tx_normal_rate_stats_stru              st_smartant_rate_stats;             /* ���������ڷ�������е�ͳ����Ϣ */
    dmac_user_ps_stru                           st_ps_structure;                    /* �û��Ľ��ܽṹ,�����û����鲥�û�������*/

#ifdef _PRE_WLAN_FEATURE_UAPSD
    dmac_user_uapsd_stru                        st_uapsd_stru;                      /* �û���U-APSD���ܽṹ*/
#endif

    hal_tx_txop_alg_stru                        st_tx_data_mcast;                    /* �鲥����֡������Ԥ��11kʹ�� */
    hal_tx_txop_alg_stru                        st_tx_data_bcast;                    /* �㲥����֡����, Ԥ��11kʹ�� */
    /*�����Ϣ�ϱ��ֶ�*/
    dmac_user_query_stats_stru                  st_query_stats;
    mac_user_uapsd_status_stru                  st_uapsd_status;                        /* uapsd״̬ */
    oal_uint8                                   uc_uapsd_flag;                          /* STA��U-APSD��ǰ�Ĵ���״̬ */
    oal_uint8                                   uc_max_key_index;                       /* ���ptk index */
    oal_uint8                                   uc_resv2[2];
    oal_uint32                                  ul_last_active_timestamp;               /* user����Ծʱ��ʱ�����user�ϻ��ͻ�Ծ�û��滻ʹ��(ʹ��OAL�ṩ��ʱ���������ֵ) */
    oal_uint32                                  ul_rx_rate;                             /* ͳ���ã�ͳ�ƵĽ���֡���ʣ����Զ˵ķ������� ��λkbps */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint32                                  ul_tx_minrate;                          /* һ��ʱ���ڵ���С���� */
    oal_uint32                                  ul_tx_maxrate;                          /* һ��ʱ���ڵ�������� */
    oal_uint32                                  ul_rx_rate_min;                         /* ͳ���ã��û�����С�������� */
    oal_uint32                                  ul_rx_rate_max;                         /* ͳ���ã��û������������� */
#endif
    dmac_user_rate_info_stru                    st_user_rate_info;

#ifdef _PRE_DEBUG_MODE_USER_TRACK
    mac_user_track_txrx_protocol_stru           st_txrx_protocol;                       /* ������һ���շ�֡��ʹ�õ�Э��ģʽ��������α仯�ˣ����ϱ�sdt */
    mac_user_track_ctx_stru                     st_user_track_ctx;
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    dmac_user_btcoex_stru                       st_dmac_user_btcoex_stru;
#endif
    /* ��ǰVAP������STAģʽ�������ֶ�Ϊuser��APʱ�����ֶΣ�������ֶ���ע��!!! */
}dmac_user_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
#ifdef _PRE_DEBUG_MODE_USER_TRACK

extern oal_uint32  dmac_user_check_txrx_protocol_change(dmac_user_stru *pst_dmac_user,
                                                                      oal_uint8      uc_present_mode,
                                                                      oam_user_info_change_type_enum_uint8  en_type);
#endif
extern oal_uint32  dmac_user_del_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx);
extern oal_uint32  dmac_user_add(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_user_add_notify_alg(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_user_del(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_user_add_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 us_multi_user_idx);
extern oal_void    dmac_user_key_search_fail_handler(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_tx_inactive_user_handler(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_pause(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_resume(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_active(dmac_user_stru * pst_dmac_user);
extern oal_uint32  dmac_user_inactive(dmac_user_stru * pst_dmac_user);
extern oal_void dmac_user_init_slottime(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
#ifdef _PRE_WLAN_SW_CTRL_RSP
extern oal_bool_enum_uint8 dmac_user_check_rsp_soft_ctl(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user);
extern oal_uint32 dmac_user_update_sw_ctrl_rsp(mac_vap_stru *pst_mac_vap, mac_user_stru  *pst_mac_user);
#endif
extern oal_uint32  dmac_user_set_groupid_partial_aid(mac_vap_stru  *pst_mac_vap,
                                             dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_user_get_tid_by_num(mac_user_stru *pst_mac_user, oal_uint8 uc_tid_num, dmac_tid_stru **ppst_tid_queue);

#ifdef _PRE_WLAN_FEATURE_SMPS
extern oal_uint8  dmac_user_get_smps_mode(mac_vap_stru  *pst_mac_vap, mac_user_stru *pst_mac_user);
#endif
oal_uint32  dmac_user_keepalive_timer(void *p_arg);
extern  oal_void dmac_ap_pause_all_user(mac_vap_stru *pst_mac_vap);
extern  oal_void dmac_ap_resume_all_user(mac_vap_stru *pst_mac_vap);
extern  oal_void dmac_rx_compatibility_show_stat(dmac_user_stru *pst_dmac_user);
extern oal_uint32 dmac_user_alloc(oal_uint16 us_user_idx);
extern oal_uint32 dmac_user_free(oal_uint16 us_user_idx);
extern void*  mac_res_get_dmac_user(oal_uint16 us_idx);
extern void*  mac_res_get_dmac_user_alloc(oal_uint16 us_idx);
oal_bool_enum_uint8 dmac_psm_is_psm_empty(dmac_user_stru *pst_dmac_user);
oal_bool_enum_uint8 dmac_psm_is_uapsd_empty(dmac_user_stru  *pst_dmac_user);
oal_bool_enum_uint8 dmac_psm_is_tid_empty(dmac_user_stru  *pst_dmac_user);
oal_uint32 dmac_psm_tid_mpdu_num(dmac_user_stru  *pst_dmac_user);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_void dmac_user_ps_queue_overrun_notify(mac_vap_stru *pst_mac_vap);
oal_uint32 dmac_psm_overrun_throw_half(dmac_user_stru  *pst_dmac_user,oal_uint32 ul_mpdu_num_sum);
#endif
extern oal_void  dmac_tid_tx_queue_exit(dmac_user_stru *pst_dmac_user);
extern dmac_user_stru  *mac_vap_get_dmac_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr);
#ifdef _PRE_WLAN_FEATURE_HILINK
extern oal_void dmac_user_notify_best_rate(dmac_user_stru *pst_dmac_user, oal_uint32 ul_best_rate_kbps);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_user.h */
