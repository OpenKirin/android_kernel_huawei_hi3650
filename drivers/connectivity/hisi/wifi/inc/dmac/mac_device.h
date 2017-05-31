/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mac_device.h
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   : mac_device.c ��ͷ�ļ�������board��chip��device�ṹ�Ķ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __MAC_DEVICE_H__
#define __MAC_DEVICE_H__

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
#include "mac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_DEVICE_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MAC_NET_DEVICE_NAME_LENGTH          16

#define MAC_DATARATES_PHY_80211G_NUM        12

#define DMAC_BA_LUT_IDX_BMAP_LEN            ((HAL_MAX_BA_LUT_SIZE + 7) >> 3)
#define DMAC_TX_BA_LUT_BMAP_LEN             ((HAL_MAX_AMPDU_LUT_SIZE + 7) >> 3)

/* �쳣��ʱ�ϱ�ʱ�� */
#define MAC_EXCEPTION_TIME_OUT              10000

/* DMAC SCANNER ɨ��ģʽ */
#define MAC_SCAN_FUNC_MEAS           0x1
#define MAC_SCAN_FUNC_STATS          0x2
#define MAC_SCAN_FUNC_RADAR          0x4
#define MAC_SCAN_FUNC_BSS            0x8
#define MAC_SCAN_FUNC_P2P_LISTEN     0x10
#define MAC_SCAN_FUNC_ALL            (MAC_SCAN_FUNC_MEAS | MAC_SCAN_FUNC_STATS | MAC_SCAN_FUNC_RADAR | MAC_SCAN_FUNC_BSS)

#define MAC_ERR_LOG(_uc_vap_id, _puc_string)
#define MAC_ERR_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define MAC_ERR_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define MAC_ERR_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define MAC_ERR_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define MAC_ERR_VAR(_uc_vap_id, _c_fmt, ...)

#define MAC_WARNING_LOG(_uc_vap_id, _puc_string)
#define MAC_WARNING_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define MAC_WARNING_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define MAC_WARNING_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define MAC_WARNING_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define MAC_WARNING_VAR(_uc_vap_id, _c_fmt, ...)

#define MAC_INFO_LOG(_uc_vap_id, _puc_string)
#define MAC_INFO_LOG1(_uc_vap_id, _puc_string, _l_para1)
#define MAC_INFO_LOG2(_uc_vap_id, _puc_string, _l_para1, _l_para2)
#define MAC_INFO_LOG3(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3)
#define MAC_INFO_LOG4(_uc_vap_id, _puc_string, _l_para1, _l_para2, _l_para3, _l_para4)
#define MAC_INFO_VAR(_uc_vap_id, _c_fmt, ...)

#ifdef _PRE_WLAN_DFT_EVENT
#define MAC_EVENT_STATE_CHANGE(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)    oam_event_report(_puc_macaddr, _uc_vap_id, OAM_MODULE_ID_MAC, en_event_type, _puc_string)
#else
#define MAC_EVENT_STATE_CHANGE(_puc_macaddr, _uc_vap_id, en_event_type, _puc_string)    ((void)_puc_string)
#endif

/* ��ȡ�豸���㷨˽�нṹ�� */
#define MAC_DEV_ALG_PRIV(_pst_dev)                  ((_pst_dev)->p_alg_priv)

/*��λ״̬*/
#define MAC_DEV_RESET_IN_PROGRESS(_pst_device,uc_value)    ((_pst_device)->uc_device_reset_in_progress = uc_value)
#define MAC_DEV_IS_RESET_IN_PROGRESS(_pst_device)          ((_pst_device)->uc_device_reset_in_progress)

#define MAC_DFS_RADAR_WAIT_TIME_MS    60000

#define MAC_DEV_MAX_40M_INTOL_USER_BITMAP_LEN 4

#ifdef _PRE_WLAN_FEATURE_HILINK
#define HMAC_FBT_MAX_USER_NUM   32

#define FBT_DEFAULT_SCAN_CHANNEL            (0)     /* Ĭ������FBT scan channelΪhome�ŵ�*/
#define FBT_DEFAULT_SCAN_INTERVAL           (200)   /* Ĭ������FBT scan interval 200ms */
#define FBT_DEFAULT_SCAN_REPORT_PERIOD      (1000)  /* Ĭ������δ�����û������ϱ�����1000ms -- ��Ҫ�޸�Ϊ200ms */
#endif

#define MAC_SCAN_CHANNEL_INTERVAL_DEFAULT               6           /* ���6���ŵ����лع����ŵ�����һ��ʱ�� */
#define MAC_WORK_TIME_ON_HOME_CHANNEL_DEFAULT           100         /* ����ɨ��ʱ�����ع����ŵ�������ʱ�� */
#define MAC_SCAN_CHANNEL_INTERVAL_PERFORMANCE           2           /* ���2���ŵ����лع����ŵ�����һ��ʱ�� */
#define MAC_WORK_TIME_ON_HOME_CHANNEL_PERFORMANCE       60          /* WLANδ������P2P���������ع����ŵ�������ʱ�� */

#define MAC_FCS_DBAC_IGNORE           0   /* ����DBAC���� */
#define MAC_FCS_DBAC_NEED_CLOSE       1   /* DBAC��Ҫ�ر� */
#define MAC_FCS_DBAC_NEED_OPEN        2   /* DBAC��Ҫ���� */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* SDT����ģʽö�� */
typedef enum
{
    MAC_SDT_MODE_WRITE = 0,
    MAC_SDT_MODE_READ,

    MAC_SDT_MODE_BUTT
}mac_sdt_rw_mode_enum;
typedef oal_uint8 mac_sdt_rw_mode_enum_uint8;

typedef enum
{
    MAC_CH_TYPE_NONE      = 0,
    MAC_CH_TYPE_PRIMARY   = 1,
    MAC_CH_TYPE_SECONDARY = 2,
}mac_ch_type_enum;
typedef oal_uint8 mac_ch_type_enum_uint8;

typedef enum
{
    MAC_SCAN_OP_INIT_SCAN,
    MAC_SCAN_OP_FG_SCAN_ONLY,
    MAC_SCAN_OP_BG_SCAN_ONLY,

    MAC_SCAN_OP_BUTT
}mac_scan_op_enum;
typedef oal_uint8 mac_scan_op_enum_uint8;

typedef enum
{
    MAC_CHAN_NOT_SUPPORT = 0,        /* ������֧�ָ��ŵ� */
    MAC_CHAN_AVAILABLE_ALWAYS,       /* �ŵ�һֱ����ʹ�� */
    MAC_CHAN_AVAILABLE_TO_OPERATE,   /* �������(CAC, etc...)�󣬸��ŵ�����ʹ�� */
    MAC_CHAN_DFS_REQUIRED,           /* ���ŵ���Ҫ�����״��� */
    MAC_CHAN_BLOCK_DUE_TO_RADAR,     /* ���ڼ�⵽�״ﵼ�¸��ŵ���Ĳ����� */

    MAC_CHAN_STATUS_BUTT
}mac_chan_status_enum;
typedef oal_uint8 mac_chan_status_enum_uint8;

#ifdef _PRE_WLAN_DFT_STAT
typedef enum
{
    MAC_DEV_MGMT_STAT_TYPE_TX = 0,
    MAC_DEV_MGMT_STAT_TYPE_RX,
    MAC_DEV_MGMT_STAT_TYPE_TX_COMPLETE,

    MAC_DEV_MGMT_STAT_TYPE_BUTT
}mac_dev_mgmt_stat_type_enum;
typedef oal_uint8 mac_dev_mgmt_stat_type_enum_uint8;
#endif

/* device resetͬ��������ö�� */
typedef enum
{
    MAC_RESET_SWITCH_SET_TYPE,
    MAC_RESET_SWITCH_GET_TYPE,
    MAC_RESET_STATUS_GET_TYPE,
    MAC_RESET_STATUS_SET_TYPE,
    MAC_RESET_SWITCH_SYS_TYPE = MAC_RESET_SWITCH_SET_TYPE,
    MAC_RESET_STATUS_SYS_TYPE = MAC_RESET_STATUS_SET_TYPE,

    MAC_RESET_SYS_TYPE_BUTT
}mac_reset_sys_type_enum;
typedef oal_uint8 mac_reset_sys_type_enum_uint8;

typedef enum
{
    MAC_TRY_INIT_SCAN_VAP_UP,
    MAC_TRY_INIT_SCAN_SET_CHANNEL,
    MAC_TRY_INIT_SCAN_START_DBAC,
    MAC_TRY_INIT_SCAN_RESCAN,

    MAC_TRY_INIT_SCAN_BUTT
}mac_try_init_scan_type;
typedef oal_uint8 mac_try_init_scan_type_enum_uint8;

typedef enum
{
    MAC_INIT_SCAN_NOT_NEED,
    MAC_INIT_SCAN_NEED,
    MAC_INIT_SCAN_IN_SCAN,

}mac_need_init_scan_res;
typedef oal_uint8 mac_need_init_scan_res_enum_uint8;

/* ɨ��״̬��ͨ���жϵ�ǰɨ���״̬���ж϶��ɨ������Ĵ�������Լ��ϱ�ɨ�����Ĳ��� */
typedef enum
{
    MAC_SCAN_STATE_IDLE,
    MAC_SCAN_STATE_RUNNING,

    MAC_SCAN_STATE_BUTT
}mac_scan_state_enum;
typedef oal_uint8 mac_scan_state_enum_uint8;

#define     MAC_FCS_MAX_CHL_NUM    2
#define     MAC_FCS_TIMEOUT_JIFFY  2
#define     MAC_FCS_DEFAULT_PROTECT_TIME_OUT    5120    /* us */
#define     MAC_FCS_DEFAULT_PROTECT_TIME_OUT2   1024    /* us */
#define     MAC_ONE_PACKET_TIME_OUT             1000
#define     MAC_FCS_CTS_MAX_DURATION            32767   /* us */

/*
 self CTS
+-------+-----------+----------------+
|frame  | duration  |      RA        |     len=10
|control|           |                |
+-------+-----------+----------------+

null data
+-------+-----------+---+---+---+--------+
|frame  | duration  |A1 |A2 |A3 |Seq Ctl | len=24
|control|           |   |   |   |        |
+-------+-----------+---+---+---+--------+

*/

typedef enum
{
    MAC_FCS_NOTIFY_TYPE_SWITCH_AWAY    = 0,
    MAC_FCS_NOTIFY_TYPE_SWITCH_BACK,

    MAC_FCS_NOTIFY_TYPE_BUTT
}mac_fcs_notify_type_enum;
typedef oal_uint8 mac_fcs_notify_type_enum_uint8;

typedef struct
{
    mac_channel_stru                st_dst_chl;
    mac_channel_stru                st_src_chl;
    hal_one_packet_cfg_stru         st_one_packet_cfg;
    oal_uint8                       uc_src_fake_q_id;   /* ԭ�ŵ���Ӧ��ٶ���id ȡֵ��Χ 0 1 */
    oal_uint8                       uc_dst_fake_q_id;   /* Ŀ���ŵ���Ӧ��ٶ���id ȡֵ��Χ 0 1 */
    oal_uint16                      us_hot_cnt;

    mac_channel_stru                st_src_chl2;
    hal_one_packet_cfg_stru         st_one_packet_cfg2;
}mac_fcs_cfg_stru;

typedef enum
{
    MAC_FCS_HOOK_ID_DBAC,
    MAC_FCS_HOOK_ID_ACS,

    MAC_FCS_HOOK_ID_BUTT
}mac_fcs_hook_id_enum;
typedef oal_uint8   mac_fcs_hook_id_enum_uint8;

typedef struct
{
    mac_fcs_notify_type_enum_uint8  uc_notify_type;
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_resv[1];
    mac_fcs_cfg_stru                st_fcs_cfg;
}mac_fcs_event_stru;

typedef void (* mac_fcs_notify_func)(const mac_fcs_event_stru*);

typedef struct
{
    mac_fcs_notify_func    p_func;
}mac_fcs_notify_node_stru;

typedef struct
{
    mac_fcs_notify_node_stru   ast_notify_nodes[MAC_FCS_HOOK_ID_BUTT];
}mac_fcs_notify_chain_stru;

typedef enum
{
    MAC_FCS_STATE_STANDBY        = 0,  // free to use
    MAC_FCS_STATE_REQUESTED,           // requested by other module, but not in switching
    MAC_FCS_STATE_IN_PROGESS,          // in switching

    MAC_FCS_STATE_BUTT
}mac_fcs_state_enum;
typedef oal_uint8 mac_fcs_state_enum_uint8;

typedef enum
{
    MAC_FCS_SUCCESS = 0,
    MAC_FCS_ERR_NULL_PTR,
    MAC_FCS_ERR_INVALID_CFG,
    MAC_FCS_ERR_BUSY,
    MAC_FCS_ERR_UNKNOWN_ERR,
}mac_fcs_err_enum;
typedef oal_uint8   mac_fcs_err_enum_uint8;

typedef struct
{
    oal_uint32  ul_offset_addr;
    oal_uint32  ul_value[MAC_FCS_MAX_CHL_NUM];
}mac_fcs_reg_record_stru;

typedef struct tag_mac_fcs_mgr_stru
{
    volatile oal_bool_enum_uint8    en_fcs_done;
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_fcs_cnt;
    oal_spin_lock_stru              st_lock;
    mac_fcs_state_enum_uint8        en_fcs_state;
    oal_uint8                       uc_resv[3];
    mac_fcs_cfg_stru               *pst_fcs_cfg;
    mac_fcs_notify_chain_stru       ast_notify_chain[MAC_FCS_NOTIFY_TYPE_BUTT];
}mac_fcs_mgr_stru;

#define MAC_FCS_VERIFY_MAX_ITEMS    1
typedef enum
{
    // isr
    MAC_FCS_STAGE_INTR_START,
    MAC_FCS_STAGE_INTR_POST_EVENT,
    MAC_FCS_STAGE_INTR_DONE,

    // event
    MAC_FCS_STAGE_EVENT_START,
    MAC_FCS_STAGE_PAUSE_VAP,
    MAC_FCS_STAGE_ONE_PKT_START,
    MAC_FCS_STAGE_ONE_PKT_INTR,
    MAC_FCS_STAGE_ONE_PKT_DONE,
    MAC_FCS_STAGE_RESET_HW_START,
    MAC_FCS_STAGE_RESET_HW_DONE,
    MAC_FCS_STAGE_RESUME_VAP,
    MAC_FCS_STAGE_EVENT_DONE,

    MAC_FCS_STAGE_COUNT
}mac_fcs_stage_enum;
typedef mac_fcs_stage_enum mac_fcs_stage_enum_uint8;

typedef struct
{
    oal_bool_enum_uint8         en_enable;
    oal_uint8                   auc_resv[3];
    oal_uint32                  ul_item_cnt;
    oal_uint32                  aul_timestamp[MAC_FCS_VERIFY_MAX_ITEMS][MAC_FCS_STAGE_COUNT];
}mac_fcs_verify_stat_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* �ϱ��ؼ���Ϣ��flags�����Ϣ����Ӧ���λΪ1������ϱ���Ӧ��Ϣ */
typedef enum
{
	MAC_REPORT_INFO_FLAGS_HARDWARE_INFO          = BIT(0),
	MAC_REPORT_INFO_FLAGS_QUEUE_INFO			 = BIT(1),
	MAC_REPORT_INFO_FLAGS_MEMORY_INFO	         = BIT(2),
	MAC_REPORT_INFO_FLAGS_EVENT_INFO             = BIT(3),
	MAC_REPORT_INFO_FLAGS_VAP_INFO	             = BIT(4),
	MAC_REPORT_INFO_FLAGS_USER_INFO	             = BIT(5),
	MAC_REPORT_INFO_FLAGS_TXRX_PACKET_STATISTICS = BIT(6),
	MAC_REPORT_INFO_FLAGS_BUTT			         = BIT(7),
}mac_report_info_flags;
#endif

#ifdef _PRE_WLAN_FEATURE_HILINK
/* ��������FBT SCAN������ģʽ:�رպͿ���ɨ��ģʽ */
typedef enum
{
    HMAC_FBT_SCAN_CLOSE     = 0,
    HMAC_FBT_SCAN_OPEN      = 1,

    HMAC_FBT_SCAN_BUTT
}hmac_fbt_scan_enum;
typedef oal_uint8 hmac_fbt_scan_enum_uint8;

/* ���������Աʹ��״��*/
typedef enum
{
    HMAC_FBT_SCAN_USER_NOT_USED = 0, /*0��ʾδʹ��*/
    HMAC_FBT_SCAN_USER_IS_USED  = 1, /*1��ʾ��ʹ�ò�д��MAC��ַ*/

    HMAC_FBT_SCAN_USER_BUTT
}hmac_fbt_scan_user_used_state;
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
/* device reset�¼�ͬ���ṹ�� */
typedef struct
{
    mac_reset_sys_type_enum_uint8  en_reset_sys_type;  /* ��λͬ������ */
    oal_uint8                      uc_value;           /* ͬ����Ϣֵ */
    oal_uint8                      uc_resv[2];
}mac_reset_sys_stru;

typedef void (*mac_scan_cb_fn)(void *p_scan_record);

typedef struct
{
    oal_uint16                    us_num_networks;
    mac_ch_type_enum_uint8        en_ch_type;
#ifdef _PRE_WLAN_FEATURE_DFS
    mac_chan_status_enum_uint8    en_ch_status;
#else
    oal_uint8                     auc_resv[1];
#endif
}mac_ap_ch_info_stru;

typedef struct
{
    oal_uint16    us_num_networks;    /* ��¼��ǰ�ŵ���ɨ�赽��BSS���� */
    oal_uint8     auc_resv[2];
    oal_uint8     auc_bssid_array[WLAN_MAX_SCAN_BSS_PER_CH][WLAN_MAC_ADDR_LEN];  /* ��¼��ǰ�ŵ���ɨ�赽������BSSID */
}mac_bss_id_list_stru;

#define MAX_PNO_SSID_COUNT          16
#define MAX_PNO_REPEAT_TIMES        4
#define PNO_SCHED_SCAN_INTERVAL     (60 * 1000)

/* PNOɨ����Ϣ�ṹ�� */
typedef struct
{
    oal_uint8           auc_ssid[WLAN_SSID_MAX_LEN];
    oal_bool_enum_uint8 en_scan_ssid;
    oal_uint8           auc_resv[2];
}pno_match_ssid_stru;

typedef struct
{
    pno_match_ssid_stru   ast_match_ssid_set[MAX_PNO_SSID_COUNT];
    oal_int32             l_ssid_count;                           /* �·�����Ҫƥ���ssid���ĸ��� */
    oal_int32             l_rssi_thold;                           /* ���ϱ���rssi���� */
    oal_uint32            ul_pno_scan_interval;                   /* pnoɨ���� */
    oal_uint8             auc_sour_mac_addr[WLAN_MAC_ADDR_LEN];   /* probe req֡��Я���ķ��Ͷ˵�ַ */
    oal_uint8             uc_pno_scan_repeat;                     /* pnoɨ���ظ����� */
    oal_bool_enum_uint8   en_is_random_mac_addr_scan;             /* �Ƿ����mac */

    mac_scan_cb_fn        p_fn_cb;                                /* ����ָ������������˼�ͨ�ų����� */
}mac_pno_scan_stru;

/* PNO����ɨ�����ṹ�� */
typedef struct
{
    mac_pno_scan_stru       st_pno_sched_scan_params;             /* pno����ɨ������Ĳ��� */
    //frw_timeout_stru        st_pno_sched_scan_timer;              /* pno����ɨ�趨ʱ�� */
    oal_void               *p_pno_sched_scan_timer;               /* pno����ɨ��rtcʱ�Ӷ�ʱ�����˶�ʱ����ʱ���ܹ�����˯�ߵ�device */
    oal_uint8               uc_curr_pno_sched_scan_times;         /* ��ǰpno����ɨ����� */
    oal_bool_enum_uint8     en_is_found_match_ssid;               /* �Ƿ�ɨ�赽��ƥ���ssid */
    oal_uint8               auc_resv[2];
}mac_pno_sched_scan_mgmt_stru;


typedef struct
{
    oal_uint8  auc_ssid[WLAN_SSID_MAX_LEN];
    oal_uint8  auc_resv[3];
}mac_ssid_stru;

/* ɨ������ṹ�� */
typedef struct
{
    wlan_mib_desired_bsstype_enum_uint8 en_bss_type;            /* Ҫɨ���bss���� */
    wlan_scan_type_enum_uint8           en_scan_type;           /* ����/���� */
    oal_uint8                           uc_bssid_num;           /* ����ɨ���bssid���� */
    oal_uint8                           uc_ssid_num;            /* ����ɨ���ssid���� */

    oal_uint8                           auc_sour_mac_addr[WLAN_MAC_ADDR_LEN];       /* probe req֡��Я���ķ��Ͷ˵�ַ */
    oal_uint8                           uc_p2p0_listen_channel;
    oal_bool_enum_uint8                 en_working_in_home_chan;

    oal_uint8                           auc_bssid[WLAN_SCAN_REQ_MAX_BSSID][WLAN_MAC_ADDR_LEN];  /* ������bssid */
    mac_ssid_stru                       ast_mac_ssid_set[WLAN_SCAN_REQ_MAX_SSID];               /* ������ssid */

    oal_uint8                           uc_max_scan_count_per_channel;                          /* ÿ���ŵ���ɨ����� */
    oal_uint8                           uc_max_send_probe_req_count_per_channel;                /* ÿ���ŵ�����ɨ������֡�ĸ�����Ĭ��Ϊ1 */
    oal_uint8                           auc_resv[2];

    oal_bool_enum_uint8                 en_need_switch_back_home_channel;       /* ����ɨ��ʱ��ɨ����һ���ŵ����ж��Ƿ���Ҫ�лع����ŵ����� */
    oal_uint8                           uc_scan_channel_interval;               /* ���n���ŵ����лع����ŵ�����һ��ʱ�� */
    oal_uint16                          us_work_time_on_home_channel;           /* ����ɨ��ʱ�����ع����ŵ�������ʱ�� */

    oal_uint8                           uc_last_channel_band;
    oal_uint8                           bit_is_p2p0_scan : 1;   /* �Ƿ�Ϊp2p0 ����ɨ�� */
    oal_uint8                           bit_rsv          : 7;   /* ����λ */
    oal_bool_enum_uint8                 en_is_random_mac_addr_scan;                             /* �Ƿ������mac addrɨ�� */
    oal_bool_enum_uint8                 en_abort_scan_flag;     /* ��ֹɨ�� */

    mac_channel_stru                    ast_channel_list[WLAN_MAX_CHANNEL_NUM];

    oal_uint8                           uc_channel_nums;        /* �ŵ��б����ŵ��ĸ��� */
    oal_uint8                           uc_probe_delay;         /* ����ɨ�跢probe request֮֡ǰ�ĵȴ�ʱ�� */
    oal_uint16                          us_scan_time;           /* ɨ����ĳһ�ŵ�ͣ����ʱ���ɨ�����, ms��������10�������� */

    wlan_scan_mode_enum_uint8           en_scan_mode;                   /* ɨ��ģʽ:ǰ��ɨ�� or ����ɨ�� */
    oal_uint8                           uc_curr_channel_scan_count;     /* ��¼��ǰ�ŵ���ɨ���������һ�η��͹㲥ssid��probe req֡�����淢��ָ��ssid��probe req֡ */
    oal_uint8                           uc_scan_func;                   /* DMAC SCANNER ɨ��ģʽ */
    oal_uint8                           uc_vap_id;                      /* �·�ɨ�������vap id */
    oal_uint64                          ull_cookie;             /* P2P �����·���cookie ֵ */


    /* ��Ҫ:�ص�����ָ��:����ָ������������˼�ͨ�ų����� */
    mac_scan_cb_fn                      p_fn_cb;
}mac_scan_req_stru;

/* ��ӡ���ձ��ĵ�rssi��Ϣ�ĵ��Կ�����صĽṹ�� */
typedef struct
{
    oal_uint32     ul_rssi_debug_switch;        /* ��ӡ���ձ��ĵ�rssi��Ϣ�ĵ��Կ��� */
    oal_uint32     ul_rx_comp_isr_interval;     /* ������ٸ���������жϴ�ӡһ��rssi��Ϣ */
    oal_uint32     ul_curr_rx_comp_isr_count;   /* һ�ּ���ڣ���������жϵĲ������� */
}mac_rssi_debug_switch_stru;

/* ACS ����ظ���ʽ */
typedef struct
{
    oal_uint8  uc_cmd;
    oal_uint8  uc_chip_id;
    oal_uint8  uc_device_id;
    oal_uint8  uc_resv;

    oal_uint32 ul_len;      /* �ܳ��ȣ���������ǰ4���ֽ� */
    oal_uint32 ul_cmd_cnt;  /* ����ļ��� */
}mac_acs_response_hdr_stru;

typedef struct
{
    oal_uint8   uc_cmd;
    oal_uint8   auc_arg[3];
    oal_uint32  ul_cmd_cnt;  /* ����ļ��� */
    oal_uint32  ul_cmd_len;  /* �ܳ��ȣ���ָauc_data��ʵ�ʸ��س��� */
    oal_uint8   auc_data[4];
}mac_acs_cmd_stru;

typedef mac_acs_cmd_stru    mac_init_scan_req_stru;

typedef enum
{
    MAC_ACS_RSN_INIT,
    MAC_ACS_RSN_LONG_TX_BUF,
    MAC_ACS_RSN_LARGE_PER,
    MAC_ACS_RSN_MWO_DECT,
    MAC_ACS_RSN_RADAR_DECT,

    MAC_ACS_RSN_BUTT
}mac_acs_rsn_enum;
typedef oal_uint8 mac_acs_rsn_enum_uint8;

typedef enum
{
    MAC_ACS_SW_NONE = 0x0,
    MAC_ACS_SW_INIT = 0x1,
    MAC_ACS_SW_DYNA = 0x2,
    MAC_ACS_SW_BOTH = 0x3,

    MAC_ACS_SW_BUTT
}en_mac_acs_sw_enum;
typedef oal_uint8 en_mac_acs_sw_enum_uint8;

typedef enum
{
    MAC_ACS_SET_CH_DNYA = 0x0,
    MAC_ACS_SET_CH_INIT = 0x1,

    MAC_ACS_SET_CH_BUTT
}en_mac_acs_set_ch_enum;
typedef oal_uint8 en_mac_acs_set_ch_enum_uint8;

typedef struct
{
    oal_bool_enum_uint8               en_sw_when_connected_enable : 1;
    oal_bool_enum_uint8               en_drop_dfs_channel_enable  : 1;
    oal_bool_enum_uint8               en_lte_coex_enable          : 1;
    en_mac_acs_sw_enum_uint8          en_acs_switch               : 5;
}mac_acs_switch_stru;

/* DMAC SCAN �ŵ�ɨ��BSS��ϢժҪ�ṹ */
typedef struct
{

    oal_int8                            c_rssi;             /* bss���ź�ǿ�� */
    oal_uint8                           uc_channel_number;  /* �ŵ��� */
    oal_uint8                           auc_bssid[WLAN_MAC_ADDR_LEN];

    /* 11n, 11ac��Ϣ */
    oal_bool_enum_uint8                 en_ht_capable;             /* �Ƿ�֧��ht */
    oal_bool_enum_uint8                 en_vht_capable;            /* �Ƿ�֧��vht */
    wlan_bw_cap_enum_uint8              en_bw_cap;                 /* ֧�ֵĴ��� 0-20M 1-40M */
    wlan_channel_bandwidth_enum_uint8   en_channel_bandwidth;      /* �ŵ��������� */
}mac_scan_bss_stats_stru;

/* DMAC SCAN �ŵ�ͳ�Ʋ�������ṹ�� */
typedef struct
{
    oal_uint8   uc_channel_number;      /* �ŵ��� */
    oal_uint8   uc_stats_valid;
    oal_uint8   uc_stats_cnt;           /* �ŵ���æ��ͳ�ƴ��� */
    oal_uint8   uc_free_power_cnt;      /* �ŵ����й��� */

    oal_uint8   uc_bandwidth_mode;
    oal_uint8   auc_resv[1];
    oal_int16   s_free_power_stats_20M;
    oal_int16   s_free_power_stats_40M;
    oal_int16   s_free_power_stats_80M;

    oal_uint32  ul_total_stats_time_us;
    oal_uint32  ul_total_free_time_20M_us;
    oal_uint32  ul_total_free_time_40M_us;
    oal_uint32  ul_total_free_time_80M_us;
    oal_uint32  ul_total_send_time_us;
    oal_uint32  ul_total_recv_time_us;

    oal_uint8   uc_radar_detected;  // FIXME: feed value
    oal_uint8   uc_radar_bw;
    oal_uint8   uc_radar_type;
    oal_uint8   uc_radar_freq_offset;
}mac_scan_chan_stats_stru;

typedef struct
{
    oal_int8                            c_rssi;             /* bss���ź�ǿ�� */
    oal_uint8                           uc_channel_number;  /* �ŵ��� */

    oal_bool_enum_uint8                 en_ht_capable   : 1;             /* �Ƿ�֧��ht */
    oal_bool_enum_uint8                 en_vht_capable  : 1;            /* �Ƿ�֧��vht */
    wlan_bw_cap_enum_uint8              en_bw_cap       : 3;            /* ֧�ֵĴ��� 0-20M 1-40M */
    wlan_channel_bandwidth_enum_uint8   en_channel_bandwidth : 3;      /* �ŵ��������� */
}mac_scan_bss_stats_simple_stru;

typedef struct
{
    oal_uint32  us_total_stats_time_ms  : 9;  // max 512 ms
    oal_uint32  uc_bandwidth_mode       : 3;
    oal_uint32  uc_radar_detected       : 1;  // FIXME: feed
    oal_uint32  uc_dfs_check_needed     : 1;
    oal_uint32  uc_radar_bw             : 3;
    oal_uint32  uc_radar_type           : 4;
    oal_uint32  uc_radar_freq_offset    : 3;
    oal_uint8   uc_channel_number;      /* �ŵ��� */

    oal_int8    s_free_power_20M;           // dBm
    oal_int8    s_free_power_40M;
    oal_int8    s_free_power_80M;
    oal_uint8   uc_free_time_20M_rate;      // percent, 255 scaled
    oal_uint8   uc_free_time_40M_rate;
    oal_uint8   uc_free_time_80M_rate;
    oal_uint8   uc_total_send_time_rate;    // percent, 255 scaled
    oal_uint8   uc_total_recv_time_rate;
}mac_scan_chan_stats_simple_stru;

/* DMAC SCAN �ص��¼��ṹ�� */
typedef struct
{
    oal_uint8                   uc_nchans;      /* �ŵ�����       */
    oal_uint8                   uc_nbss;        /* BSS���� */
    oal_uint8                   uc_scan_func;   /* ɨ�������Ĺ��� */

    oal_uint8                   uc_need_rank    : 1; // kernel write, app read
    oal_uint8                   uc_obss_on      : 1;
    oal_uint8                   uc_dfs_on       : 1;
    oal_uint8                   uc_dbac_on      : 1;
    oal_uint8                   uc_chip_id      : 2;
    oal_uint8                   uc_device_id    : 2;

}mac_scan_event_stru;


#ifdef _PRE_WLAN_FEATURE_DFS
typedef struct
{
    oal_bool_enum_uint8    en_dfs_switch;                               /* DFSʹ�ܿ��� bit0:dfsʹ��,bit1:��ʾAP��ΪDFS������ʱ������wait_start */
    oal_bool_enum_uint8    en_cac_switch;
    oal_bool_enum_uint8    en_offchan_cac_switch;
    oal_uint8              uc_debug_level;                              /* bit0:��ӡ�״��ҵ��bit1:��ӡ�״���ҵ�� */
    oal_uint8              uc_offchan_flag;                             /* bit0:0��ʾhomechan,1��ʾoffchan; bit1:0��ʾ��ͨ,1��ʾoffchancac */
    oal_uint8              uc_offchan_num;
    oal_uint8              uc_timer_cnt;
    oal_uint8              uc_timer_end_cnt;
    oal_uint8              uc_cts_duration;
    oal_uint8              uc_dmac_channel_flag;                        /* dmac���ڱ�ʾ��ǰ�ŵ�off or home */
    oal_uint8              auc_res[2];
    oal_uint32             ul_dfs_cac_outof_5600_to_5650_time_ms;       /* CAC���ʱ����5600MHz ~ 5650MHzƵ���⣬Ĭ��60�� */
    oal_uint32             ul_dfs_cac_in_5600_to_5650_time_ms;          /* CAC���ʱ����5600MHz ~ 5650MHzƵ���ڣ�Ĭ��10���� */
    oal_uint32             ul_off_chan_cac_outof_5600_to_5650_time_ms;  /* Off-Channel CAC���ʱ����5600MHz ~ 5650MHzƵ���⣬Ĭ��6���� */
    oal_uint32             ul_off_chan_cac_in_5600_to_5650_time_ms;     /* Off-Channel CAC���ʱ����5600MHz ~ 5650MHzƵ���ڣ�Ĭ��60���� */
    oal_uint16             us_dfs_off_chan_cac_opern_chan_dwell_time;   /* Off-channel CAC�ڹ����ŵ���פ��ʱ�� */
    oal_uint16             us_dfs_off_chan_cac_off_chan_dwell_time;     /* Off-channel CAC��Off-Channel�ŵ���פ��ʱ�� */
    oal_uint32             ul_radar_detected_timestamp;
}mac_dfs_info_stru;

typedef struct
{
    oal_uint8             uc_chan_idx;        /* �ŵ����� */
    oal_uint8             uc_device_id;       /* device id */
    oal_uint8             auc_resv[2];
    frw_timeout_stru      st_dfs_nol_timer;   /* NOL�ڵ㶨ʱ�� */
    oal_dlist_head_stru   st_entry;           /* NOL���� */
}mac_dfs_nol_node_stru;

typedef struct
{
    frw_timeout_stru      st_dfs_cac_timer;                   /* CAC��ʱ�� */
    frw_timeout_stru      st_dfs_off_chan_cac_timer;          /* Off-Channel CAC��ʱ�� */
    frw_timeout_stru      st_dfs_chan_dwell_timer;            /* �ŵ�פ����ʱ������ʱ�����ڣ�������ŵ� */
    frw_timeout_stru      st_dfs_radar_timer;
    mac_dfs_info_stru     st_dfs_info;
    oal_dlist_head_stru   st_dfs_nol;
}mac_dfs_core_stru;
#endif

/* bss��ȫ�����Ϣ�ṹ�� */
typedef struct
{
    oal_uint8                    uc_bss_80211i_mode;                                      /*ָʾ��ǰAP�İ�ȫ��ʽ��WPA��WPA2��BIT0: WPA; BIT1:WPA2 */
    oal_uint8                    uc_rsn_grp_policy;                                       /*���ڴ��WPA2��ʽ�£�AP���鲥�����׼���Ϣ*/
    oal_uint8                    auc_rsn_pairwise_policy[MAC_PAIRWISE_CIPHER_SUITES_NUM]; /*���ڴ��WPA2��ʽ�£�AP�ĵ��������׼���Ϣ*/
    oal_uint8                    auc_rsn_auth_policy[MAC_AUTHENTICATION_SUITE_NUM];        /*���ڴ��WPA2��ʽ�£�AP����֤�׼���Ϣ*/
    oal_uint8                    auc_rsn_cap[2];                                          /*���ڱ���RSN������Ϣ��ֱ�Ӵ�֡������copy����*/
    oal_uint8                    auc_wpa_pairwise_policy[MAC_PAIRWISE_CIPHER_SUITES_NUM]; /*���ڴ��WPA��ʽ�£�AP�ĵ��������׼���Ϣ*/
    oal_uint8                    auc_wpa_auth_policy[MAC_AUTHENTICATION_SUITE_NUM];        /*���ڴ��WPA��ʽ�£�AP����֤�׼���Ϣ*/
    oal_uint8                    uc_wpa_grp_policy;                                       /*���ڴ��WPA��ʽ�£�AP���鲥�����׼���Ϣ*/
    oal_uint8                    uc_grp_policy_match;                                     /*���ڴ��ƥ����鲥�׼�*/
    oal_uint8                    uc_pairwise_policy_match;                                /*���ڴ��ƥ��ĵ����׼�*/
    oal_uint8                    uc_auth_policy_match;                                    /*���ڴ��ƥ�����֤�׼�*/
}mac_bss_80211i_info_stru;


/* ɨ������¼�����״̬�� */
typedef enum
{
    MAC_SCAN_SUCCESS = 0,       /* ɨ��ɹ� */
    MAC_SCAN_PNO     = 1,       /* pnoɨ����� */
    MAC_SCAN_TIMEOUT = 2,       /* ɨ�賬ʱ */
    MAC_SCAN_REFUSED = 3,       /* ɨ�豻�ܾ� */
    MAC_SCAN_ABORT   = 4,       /* ��ֹɨ�� */
    MAC_SCAN_STATUS_BUTT,       /* ��Ч״̬�룬��ʼ��ʱʹ�ô�״̬�� */
}mac_scan_status_enum;
typedef oal_uint8   mac_scan_status_enum_uint8;

/* ɨ���� */
typedef struct
{
    mac_scan_status_enum_uint8  en_scan_rsp_status;
    oal_uint8                   auc_resv[3];
    oal_uint64                  ull_cookie;
}mac_scan_rsp_stru;


/* ɨ�赽��BSS�����ṹ�� */
typedef struct
{
    /* ������Ϣ */
    wlan_mib_desired_bsstype_enum_uint8 en_bss_type;                        /* bss�������� */
    oal_uint8                           uc_dtim_period;                     /* dtime���� */
    oal_uint8                           uc_dtim_cnt;                        /* dtime cnt */
    oal_bool_enum_uint8                 en_11ntxbf;                         /* 11n txbf */
    oal_bool_enum_uint8                 en_new_scan_bss;                    /* �Ƿ�����ɨ�赽��BSS */
    oal_uint8                           auc_resv1[1];
    oal_int8                            c_rssi;                             /* bss���ź�ǿ�� */
    oal_int8                            ac_ssid[WLAN_SSID_MAX_LEN];         /* ����ssid */
    oal_uint16                          us_beacon_period;                   /* beacon���� */
    oal_uint16                          us_cap_info;                        /* ����������Ϣ */
    oal_uint8                           auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* ���������� mac��ַ��bssid��ͬ */
    oal_uint8                           auc_bssid[WLAN_MAC_ADDR_LEN];       /* ����bssid */
    mac_channel_stru                    st_channel;                         /* bss���ڵ��ŵ� */
    oal_uint8                           uc_wmm_cap;                         /* �Ƿ�֧��wmm */
    oal_uint8                           uc_uapsd_cap;                       /* �Ƿ�֧��uapsd */
    oal_bool_enum_uint8                 en_desired;                         /* ��־λ����bss�Ƿ��������� */
    oal_uint8                           uc_num_supp_rates;                  /* ֧�ֵ����ʼ����� */
    oal_uint8                           auc_supp_rates[WLAN_MAX_SUPP_RATES];/* ֧�ֵ����ʼ� */

#ifdef _PRE_WLAN_FEATURE_11D
    oal_int8                            ac_country[WLAN_COUNTRY_STR_LEN];   /* �����ַ��� */
    oal_uint8                           auc_resv2[1];
#endif

    /* ��ȫ��ص���Ϣ */
    mac_bss_80211i_info_stru            st_bss_sec_info;                    /*���ڱ���STAģʽ�£�ɨ�赽��AP��ȫ�����Ϣ*/

    /* 11n 11ac��Ϣ */
    oal_bool_enum_uint8                 en_ht_capable;                      /* �Ƿ�֧��ht */
    oal_bool_enum_uint8                 en_vht_capable;                     /* �Ƿ�֧��vht */
    wlan_bw_cap_enum_uint8              en_bw_cap;                          /* ֧�ֵĴ��� 0-20M 1-40M */
    wlan_channel_bandwidth_enum_uint8   en_channel_bandwidth;               /* �ŵ����� */
    oal_uint8                           uc_coex_mgmt_supp;                  /* �Ƿ�֧�ֹ������ */
    oal_bool_enum_uint8                 en_ht_ldpc;                         /* �Ƿ�֧��ldpc */
    oal_bool_enum_uint8                 en_ht_stbc;                         /* �Ƿ�֧��stbc */
    oal_uint8                           uc_wapi;
    oal_uint32                          ul_timestamp;                       /* ���´�bss��ʱ��� */

    /* ����֡��Ϣ */
    oal_uint32                          ul_mgmt_len;                        /* ����֡�ĳ��� */
    oal_uint8                           auc_mgmt_buff[4];                   /* ��¼beacon֡��probe rsp֡ */
    //oal_uint8                          *puc_mgmt_buff;                      /* ��¼beacon֡��probe rsp֡ */
}mac_bss_dscr_stru;

#ifdef _PRE_WLAN_DFT_STAT
/* ����֡ͳ����Ϣ */
typedef struct
{
    /* ���չ���֡ͳ�� */
    oal_uint32          aul_rx_mgmt[WLAN_MGMT_SUBTYPE_BUTT];

    /* �ҵ�Ӳ�����еĹ���֡ͳ�� */
    oal_uint32          aul_tx_mgmt_soft[WLAN_MGMT_SUBTYPE_BUTT];

    /* ������ɵĹ���֡ͳ�� */
    oal_uint32          aul_tx_mgmt_hardware[WLAN_MGMT_SUBTYPE_BUTT];
}mac_device_mgmt_statistic_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
typedef struct
{
    oal_bool_enum_uint8             en_psta_enable;
    oal_uint8                       uc_proxysta_cnt;                                        /* ����proxy sta�ĸ���(������main ProxySTA) */
    oal_uint8                       auc_resv[2];
}mac_device_psta_stru;

#define mac_dev_xsta_num(dev) ((dev)->st_psta.uc_proxysta_cnt)
#define mac_is_proxysta_enabled(pst_dev) ((pst_dev)->st_psta.en_psta_enable)
#endif


#ifdef _PRE_WLAN_DFT_STAT
/* �ϱ��տڻ�����ά������Ŀ��ƽṹ */
typedef struct
{
    oal_uint32                          ul_non_directed_frame_num;             /* ���յ��Ǳ���֡����Ŀ */
    oal_uint8                           uc_collect_period_cnt;                 /* �ɼ����ڵĴ���������100����ϱ�������Ȼ���������¿�ʼ */
    oal_bool_enum_uint8                 en_non_directed_frame_stat_flg;        /* �Ƿ�ͳ�ƷǱ�����ַ֡�����ı�־ */
    oal_int16                           s_ant_power;                           /* ���߿ڹ��� */
    frw_timeout_stru                    st_collect_period_timer;               /* �ɼ����ڶ�ʱ�� */
}mac_device_dbb_env_param_ctx_stru;
#endif

typedef enum
{
    MAC_DFR_TIMER_STEP_1 = 0,
    MAC_DFR_TIMER_STEP_2 = 1,

}mac_dfr_timer_step_enum;
typedef oal_uint8 mac_dfr_timer_step_enum_uint8;

typedef struct
{
    oal_uint32                         ul_tx_seqnum;                           /* ���һ��tx�ϱ���SN�� */
    oal_uint16                         us_seqnum_used_times;                   /* ���ʹ����ul_tx_seqnum�Ĵ��� */
    oal_uint16                         us_incr_constant;                       /* ά����Qos ��Ƭ֡�ĵ������� */
}mac_tx_seqnum_struc;

typedef struct
{
    oal_uint8                           uc_p2p_device_num;                      /* ��ǰdevice�µ�P2P_DEVICE���� */
    oal_uint8                           uc_p2p_goclient_num;                    /* ��ǰdevice�µ�P2P_CL/P2P_GO���� */
    oal_uint8                           uc_p2p0_vap_idx;                        /* P2P ���泡���£�P2P_DEV(p2p0) ָ�� */
    mac_vap_state_enum_uint8            en_last_vap_state;                      /* P2P0/P2P_CL ����VAP �ṹ�����������±���VAP �������ǰ��״̬ */
    oal_uint8                           uc_resv[2];                             /* ���� */
    oal_uint8                           en_roc_need_switch;                     /* remain on channel����Ҫ�л�ԭ�ŵ�*/
    oal_uint8                           en_p2p_ps_pause;                        /* P2P �����Ƿ���pause״̬*/
    oal_net_device_stru                *pst_p2p_net_device;                     /* P2P ���泡������net_device(p2p0) ָ�� */
    oal_uint64                          ull_send_action_id;                     /* P2P action id/cookie */
    oal_uint64                          ull_last_roc_id;
    oal_ieee80211_channel_stru          st_listen_channel;
    oal_nl80211_channel_type            en_listen_channel_type;
    oal_net_device_stru                *pst_primary_net_device;                 /* P2P ���泡������net_device(wlan0) ָ�� */
}mac_p2p_info_stru;

/* DTS2015100700205,�������������������ܷ���: ����DataFlow Breakʱ���Ӱ������ */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
typedef struct
{
    oal_bool_enum_uint8                 en_brk_limit_aggr_enable;
    oal_uint8                           uc_resv[3];
    oal_uint32                          ul_tx_dataflow_brk_cnt;
    oal_uint32                          ul_last_tx_complete_isr_cnt;
}mac_tx_dataflow_brk_bypass_struc;
#endif

/* ��Ļ״̬ */
typedef enum
{
    MAC_SCREEN_OFF = 0,
    MAC_SCREEN_ON  = 1,
}mac_screen_state_enum;

#ifdef _PRE_WLAN_FEATURE_HILINK
/* ��¼δ���������û�������� */
typedef struct
{
    oal_uint8   uc_is_used;                 /* ���û��Ƿ�ʹ�� */
    oal_uint8   uc_user_channel;            /* ������ǰ�������ŵ� */
    oal_uint8   auc_user_bssid[6];          /* ���������ĵ�ǰAP��bssid */
    oal_uint8   auc_user_mac_addr[6];       /* ��ǰ������MAC��ַ */
    oal_int8    c_rssi;                     /* ��ǰ�������ź�ǿ�� */
    oal_uint8   uc_is_found;                /* 0-û���ҵ���������1-�ҵ������� */
    oal_uint32  ul_rssi_timestamp;          /* ���յ���֡��ʱ��� */
    oal_uint32  ul_total_pkt_cnt;           /* ���յ���STA���ܰ���Ŀ */
}mac_fbt_scan_result_stru;


/* ��¼δ�����û�������Ϣ�Ľṹ�� */
typedef struct
{
    oal_uint8  uc_fbt_scan_enable;              /* ����δ�����û��������Կ��� */
    oal_uint8  uc_scan_channel;                 /* ���������ŵ���Ĭ��Ϊ0����ʾ��ǰ�ŵ� */
    oal_uint32 ul_scan_interval;                /* ����δ�����û�ÿ���ŵ�������ʱ������λΪ���� */
    oal_uint32 ul_scan_report_period;           /* ���������ϱ����� */
    mac_fbt_scan_result_stru ast_fbt_scan_user_list[HMAC_FBT_MAX_USER_NUM]; /* ��¼32���û������������Ϣ */
    frw_timeout_stru st_timer;                  /* ����δ�����û�ʹ�õĶ�ʱ�� */
}mac_fbt_scan_mgmt_stru;

/* �����л�����ָ���û� fbt_monitor_specified_sta�������ڴ���mac��ַ*/
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8               auc_resv[2];
}mac_fbt_scan_sta_addr_stru;

typedef struct
{
    unsigned char   mac[WLAN_MAC_ADDR_LEN];                     /* ��Ҫ������sta��mac��ַ */
    oal_uint32      ul_channel;                                 /* ��Ҫ�������ŵ��� */
    oal_uint32      ul_interval;                                /* ��Ҫ����ʱ�� */
    oal_uint8       en_is_on;                                   /* �Ƿ������� */
}mac_cfg_fbt_scan_params_stru;

#endif
/* device�ṹ�� */
typedef struct
{
    oal_uint32                          ul_core_id;
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    oal_uint8                           auc_vap_id[WLAN_REPEATER_SERVICE_VAP_MAX_NUM_PER_DEVICE];   /* device�µ�ҵ��vap���˴�ֻ��¼VAP ID */
#else
    oal_uint8                           auc_vap_id[WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE];   /* device�µ�ҵ��vap���˴�ֻ��¼VAP ID */
#endif
    oal_uint8                           uc_cfg_vap_id;                          /* ����vap ID */
    oal_uint8                           uc_device_id;                           /* оƬID */
    oal_uint8                           uc_chip_id;                             /* �豸ID */
    oal_uint8                           uc_device_reset_in_progress;            /* ��λ������*/

    oal_bool_enum_uint8                 en_device_state;                        /* ��ʶ�Ƿ��Ѿ������䣬(OAL_TRUE��ʼ����ɣ�OAL_FALSEδ��ʼ�� ) */
    oal_uint8                           uc_vap_num;                             /* ��ǰdevice�µ�ҵ��VAP����(AP+STA) */
    oal_uint8                           uc_sta_num;                             /* ��ǰdevice�µ�STA���� */
/* begin: P2P */
    mac_p2p_info_stru                   st_p2p_info;                            /* P2P �����Ϣ */
/* end: P2P */

    oal_uint8                           auc_hw_addr[WLAN_MAC_ADDR_LEN];         /* ��eeprom��flash��õ�mac��ַ��ko����ʱ����hal�ӿڸ�ֵ */
    /* device������� */
    oal_uint8                           uc_max_channel;                         /* ������VAP���ŵ��ţ�����VAP����ֵ�������ֵì�ܣ����ڷ�DBACʱʹ�� */
    wlan_channel_band_enum_uint8        en_max_band;                            /* ������VAP��Ƶ�Σ�����VAP����ֵ�������ֵì�ܣ����ڷ�DBACʱʹ�� */

    wlan_channel_bandwidth_enum_uint8   en_max_bandwidth;                       /* ������VAP���������ֵ������VAP����ֵ�������ֵì�ܣ����ڷ�DBACʱʹ�� */
    oal_uint8                           uc_tx_chain;                            /* ����ͨ�� */
    oal_uint8                           uc_rx_chain;                            /* ����ͨ�� */
    wlan_nss_enum_uint8                 en_nss_num;                             /* Nss �ռ������� */

    oal_bool_enum_uint8                 en_wmm;                                 /* wmmʹ�ܿ��� */
    wlan_tidno_enum_uint8               en_tid;
    oal_uint8                           en_reset_switch;                        /* �Ƿ�ʹ�ܸ�λ����*/
    oal_uint8                           uc_csa_vap_cnt;                        /* ÿ��running AP����һ��CSA֡���ü�����1���������APֹͣ��ǰӲ�����ͣ�׼����ʼ�л��ŵ� */

    hal_to_dmac_device_stru            *pst_device_stru;                        /* Ӳmac�ṹָ�룬HAL�ṩ�������߼�������device�Ķ�Ӧ */

    oal_uint32                          ul_beacon_interval;                     /*device����beacon interval,device������VAPԼ��Ϊͬһֵ*/
    oal_uint32                          ul_duty_ratio;                          /* ռ�ձ�ͳ�� */
    oal_uint32                          ul_duty_ratio_lp;                       /*����͹���ǰ����ռ�ձ�*/
    oal_uint32                          ul_rx_nondir_duty_lp;                   /*����͹���ǰ����non-direct����ռ�ձ�*/
    oal_uint32                          ul_rx_dir_duty_lp;                      /*����͹���ǰ����direct����ռ�ձ�*/

    oal_int16                           s_upc_amend;                            /* UPC����ֵ */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_bool_enum_uint8                 en_is_wavetest;                         /* wavetest�û�ʶ�� 1:��  0:����    */
    oal_uint8                           uc_lock_channel;                        /* AGC��ͨ�� 0:��ͨ��0  1:��ͨ��1   2:����Ӧ  */
    oal_uint8                           auc_rev[2];
#endif

    /* device���� */
    wlan_protocol_cap_enum_uint8        en_protocol_cap;                        /* Э������ */
    wlan_band_cap_enum_uint8            en_band_cap;                            /* Ƶ������ */
    wlan_bw_cap_enum_uint8              en_bandwidth_cap;                       /* �������� */
    oal_uint8                           bit_ldpc_coding : 1,                    /* �Ƿ�֧�ֽ���LDPC����İ� */
                                        bit_tx_stbc     : 1,                    /* �Ƿ�֧������2x1 STBC���� */
                                        bit_rx_stbc     : 3,                    /* �Ƿ�֧��stbc���� */
                                        bit_su_bfmer    : 1,                    /* �Ƿ�֧�ֵ��û�beamformer */
                                        bit_su_bfmee    : 1,                    /* �Ƿ�֧�ֵ��û�beamformee */
                                        bit_mu_bfmee    : 1;                    /* �Ƿ�֧�ֶ��û�beamformee */


    oal_uint16                          us_device_reset_num;                    /* ��λ�Ĵ���ͳ��*/
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_device_psta_stru                st_psta;
#endif

    mac_data_rate_stru                  st_mac_rates_11g[MAC_DATARATES_PHY_80211G_NUM];  /* 11g���� */

    mac_pno_sched_scan_mgmt_stru       *pst_pno_sched_scan_mgmt;                    /* pno����ɨ�����ṹ��ָ�룬�ڴ涯̬���룬�Ӷ���ʡ�ڴ� */
    mac_scan_req_stru                   st_scan_params;                             /* ����һ�ε�ɨ�������Ϣ */
    frw_timeout_stru                    st_scan_timer;                              /* ɨ�趨ʱ�������л��ŵ� */
    frw_timeout_stru                    st_obss_scan_timer;                         /* obssɨ�趨ʱ����ѭ����ʱ�� */
    mac_channel_stru                    st_p2p_vap_channel;                     /* p2p listenʱ��¼p2p���ŵ�������p2p listen������ָ� */

    oal_uint8                           uc_active_user_cnt;                     /* ��Ծ�û��� */
    oal_uint8                           uc_asoc_user_cnt;                       /* �����û��� */
    oal_bool_enum_uint8                 en_2040bss_switch;                      /* 20/40 bss��⿪�� */
    oal_uint8                           uc_in_suspend;
#ifdef _PRE_WLAN_FEATURE_11K
    //frw_timeout_stru                    st_backoff_meas_timer;
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS
    oal_uint8                           auc_resv18[2];
    oal_bool_enum_uint8                 en_smps;                                /* Device SMPSʹ�ܱ�ʶ */
    oal_uint8                           uc_dev_smps_mode;                       /* Device SMPS���� */
#endif


#ifdef _PRE_SUPPORT_ACS
    /* DMAC ACS���� */
    oal_void                           *pst_acs;
    mac_acs_switch_stru                 st_acs_switch;
#endif

    /* linux�ں��е�device������Ϣ */
    oal_wiphy_stru                     *pst_wiphy;                             /* ���ڴ�ź�VAP��ص�wiphy�豸��Ϣ����AP/STAģʽ�¾�Ҫʹ�ã����Զ��VAP��Ӧһ��wiphy */

    oal_uint8                           uc_mac_vap_id;                         /* ��vap����ʱ������˯��ǰ��mac vap id */
    mac_bss_id_list_stru                st_bss_id_list;                        /* ��ǰ�ŵ��µ�ɨ���� */

    oal_bool_enum_uint8                 en_dbac_enabled;
    oal_bool_enum_uint8                 en_dbac_running;                       /* DBAC�Ƿ������� */
    oal_bool_enum_uint8                 en_dbac_has_vip_frame;                 /* ���DBAC����ʱ�յ��˹ؼ�֡ */
    oal_uint8                           uc_arpoffload_switch;
    oal_uint8                           uc_wapi;
    oal_uint8                           uc_reserve;
    oal_bool_enum_uint8                 en_is_random_mac_addr_scan;            /* ���macɨ�迪��,��hmac�·� */
    oal_uint8                           auc_mac_oui[WLAN_RANDOM_MAC_OUI_LEN];  /* ���mac��ַOUI,��Android�·� */
    oal_uint8                           auc_rsv[2];

#ifdef _PRE_WLAN_FEATURE_DFS
    mac_dfs_core_stru                   st_dfs;
#endif

#ifdef _PRE_WLAN_FEATURE_HILINK
    mac_fbt_scan_mgmt_stru             st_fbt_scan_mgmt;                        /* ����δ�����û�������Ϣ�Ľṹ�� */
#endif
    /*���Device�ĳ�Ա�����ƶ���dmac_device*/
#if IS_DEVICE
    oal_uint8                           auc_resv12[2];
    oal_uint16                          us_total_mpdu_num;                      /* device������TID���ܹ���mpdu_num���� */
    oal_uint16                          aus_ac_mpdu_num[WLAN_WME_AC_BUTT];      /* device�¸���AC��Ӧ��mpdu_num�� */
    oal_uint16                          aus_vap_mpdu_num[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];      /* ͳ�Ƹ���vap��Ӧ��mpdu_num�� */

    oal_void                           *p_alg_priv;                             /* �㷨˽�нṹ�� */

    oal_uint16                          us_dfs_timeout;
    oal_uint32                          ul_rx_buf_too_small_show_counter;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    oal_uint32                          ul_beacon_miss_show_counter;
    oal_uint32                          ul_rx_fsm_st_timeout_show_counter;
    oal_uint32                          ul_tx_fsm_st_timeout_show_counter;
    oal_uint16                          us_user_nums_max;
    oal_uint8                           auc_resv26[2];
    oal_uint32                          ul_pcie_reg110_timeout_counter;
    oal_uint32                          ul_pcie_read_counter;

    /* DTS2015100700205,�������������������ܷ��� */
    mac_tx_dataflow_brk_bypass_struc    st_dataflow_brk_bypass;
#endif
    oal_uint32                          ul_first_timestamp;                         /*��¼����ͳ�Ƶ�һ��ʱ���*/

    oal_uint8                           auc_tx_ba_index_table[DMAC_TX_BA_LUT_BMAP_LEN];      /* ���Ͷ�LUT�� */

    /* ɨ����س�Ա���� */
    oal_uint32                          ul_scan_timestamp;                      /* ��¼����һ��ɨ�迪ʼ��ʱ�� */
    oal_uint8                           uc_scan_chan_idx;                       /* ��ǰɨ���ŵ����� */
    mac_scan_state_enum_uint8           en_curr_scan_state;                     /* ��ǰɨ��״̬�����ݴ�״̬����obssɨ���host���·���ɨ�������Լ�ɨ�������ϱ����� */

    oal_uint8                           uc_resume_qempty_flag;                  /* ʹ�ָܻ�qempty��ʶ, Ĭ�ϲ�ʹ�� */
    oal_uint8                           uc_scan_count;

    mac_channel_stru                    st_home_channel;                        /* ��¼�����ŵ� ���л�ʱʹ�� */
    mac_fcs_cfg_stru                    st_fcs_cfg;                             /* �������ŵ��ṹ�� */

    mac_scan_chan_stats_stru            st_chan_result;                         /* dmacɨ��ʱ һ���ŵ����ŵ�������¼ */

    oal_uint8                           auc_original_mac_addr[WLAN_MAC_ADDR_LEN]; /* ɨ�迪ʼǰ����ԭʼ��MAC��ַ */
    oal_uint8                           uc_scan_ap_num_in_2p4;
    oal_bool_enum_uint8                 en_scan_curr_chan_find_bss_flag;        /* ���ŵ�ɨ���Ƿ�ɨ�赽BSS */

#ifdef _PRE_WLAN_DFT_REG
    frw_timeout_stru                    st_reg_prd_timer;                       /* ��ȡ�Ĵ������ڶ�ʱ�� */
#endif

    /* �û���س�Ա���� */
    frw_timeout_stru                    st_active_user_timer;                   /* �û���Ծ��ʱ�� */

    oal_uint8                           auc_ra_lut_index_table[WLAN_ACTIVE_USER_IDX_BMAP_LEN];  /* lut��λͼ */

#ifdef _PRE_WLAN_DFT_STAT
    /* ����֡ͳ����Ϣ */
    mac_device_mgmt_statistic_stru      st_mgmt_stat;
    mac_device_dbb_env_param_ctx_stru   st_dbb_env_param_ctx;                  /* �ϱ��տڻ�����ά������Ŀ��ƽṹ */
#endif
    mac_fcs_mgr_stru                    st_fcs_mgr;

    oal_uint8                           uc_csa_cnt;                            /* ÿ��AP����һ��CSA֡���ü�����1��AP�л����ŵ��󣬸ü������� */

    oal_bool_enum_uint8                 en_txop_enable;                        /* �����޾ۺ�ʱ����TXOPģʽ */
    oal_uint8                           uc_tx_ba_num;                  /* ���ͷ���BA�Ự���� */
    oal_uint8                           auc_resv[1];


    frw_timeout_stru                    st_keepalive_timer;                     /* keepalive��ʱ�� */

#ifdef _PRE_DEBUG_MODE
    frw_timeout_stru                    st_exception_report_timer;
#endif
    oal_uint32                          aul_mac_err_cnt[HAL_MAC_ERROR_TYPE_BUTT];   /*mac ���������*/

#ifdef _PRE_WLAN_FEATURE_PM
    oal_void*                           pst_pm_arbiter;                        /*device�ṹ���½����ٲù���ṹ*/
    oal_bool_enum_uint8                 en_pm_enable;                          /*PM���幦�ܿ����رտ���*/
    oal_uint8                           auc_resv7[3];
#endif

#ifdef _PRE_WLAN_FEATURE_GREEN_AP
    oal_void                            *pst_green_ap_mgr;                     /*device�ṹ�µ�green ap���Խṹ��*/
#endif

#ifdef _PRE_WLAN_REALTIME_CALI
    frw_timeout_stru                    st_realtime_cali_timer;                    /* ʵʱУ׼��ʱ��ʱ��*/
#endif
#endif /* IS_DEVICE */

    /*���Host�ĳ�Ա�����ƶ���hmac_device*/
#if IS_HOST
#ifndef _PRE_WLAN_FEATURE_AMPDU_VAP
    oal_uint8                           uc_rx_ba_session_num;                   /* ��device�£�rx BA�Ự����Ŀ */
    oal_uint8                           uc_tx_ba_session_num;                   /* ��device�£�tx BA�Ự����Ŀ */
    oal_uint8                           auc_resv11[2];
#endif
    oal_bool_enum_uint8                 en_vap_classify;                        /* �Ƿ�ʹ�ܻ���vap��ҵ����� */
    oal_uint8                           auc_resv14[3];

    oal_uint8                           auc_rx_ba_lut_idx_table[DMAC_BA_LUT_IDX_BMAP_LEN];   /* ���ն�LUT�� */

    frw_timeout_stru                    st_obss_aging_timer;                    /* OBSS�����ϻ���ʱ�� */

#ifdef _PRE_WLAN_FEATURE_SMPS
    oal_uint8                           uc_no_smps_user_cnt;                    /* ��֧��SMPS���û���  */
    oal_uint8                           auc_resv17[3];
#endif
    mac_ap_ch_info_stru                 st_ap_channel_list[MAC_MAX_SUPP_CHANNEL];
    oal_uint8                           uc_ap_chan_idx;                        /* ��ǰɨ���ŵ����� */
    oal_uint8                           auc_resv21[3];

    oal_bool_enum_uint8                 en_40MHz_intol_bit_recd;
    oal_uint8                           auc_resv4[3];
#endif /* IS_HOST */
#ifdef _PRE_WLAN_FEATURE_STA_PM
    hal_mac_key_statis_info_stru      st_mac_key_statis_info;                   /* mac�ؼ�ͳ����Ϣ */
#endif

#ifdef _PRE_WLAN_RF_CALI
     oal_work_stru                       auto_cali_work;
#endif
}mac_device_stru;

#pragma pack(push,1)
/* �ϱ���ɨ��������չ��Ϣ�������ϱ�host��Ĺ���֡netbuf�ĺ��� */
typedef struct
{
    oal_int32                           l_rssi;                     /* �ź�ǿ�� */
    wlan_mib_desired_bsstype_enum_uint8 en_bss_type;                /* ɨ�赽��bss���� */
    oal_uint8                           auc_resv[3];                /* Ԥ���ֶ� */
}mac_scanned_result_extend_info_stru;
#pragma pack(pop)

/* chip�ṹ�� */
typedef struct
{
    oal_uint8                   auc_device_id[WLAN_DEVICE_MAX_NUM_PER_CHIP];    /* CHIP�¹ҵ�DEV������¼��Ӧ��ID����ֵ */
    oal_uint8                   uc_device_nums;                                 /* chip��device����Ŀ */
    oal_uint8                   uc_chip_id;                                     /* оƬID */
    oal_bool_enum_uint8         en_chip_state;                                  /* ��ʶ�Ƿ��ѳ�ʼ����OAL_TRUE��ʼ����ɣ�OAL_FALSEδ��ʼ�� */
    oal_uint32                  ul_chip_ver;                                    /* оƬ�汾 */
    hal_to_dmac_chip_stru       *pst_chip_stru;                                 /* Ӳmac�ṹָ�룬HAL�ṩ�������߼�������chip�Ķ�Ӧ */

}mac_chip_stru;

/* board�ṹ�� */
typedef struct
{
    mac_chip_stru               ast_chip[WLAN_CHIP_MAX_NUM_PER_BOARD];              /* board�ҽӵ�оƬ */
    oal_uint8                   uc_chip_id_bitmap;                                  /* ��ʶchip�Ƿ񱻷����λͼ */
    oal_uint8                   auc_resv[3];                                        /* �ֽڶ��� */
}mac_board_stru;

typedef struct
{
    mac_device_stru                    *pst_mac_device;
}mac_wiphy_priv_stru;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
    /* ���߼��в��뿴���� */
#ifdef _PRE_WLAN_FEATURE_DBAC
#define MAC_DBAC_ENABLE(_pst_device) (_pst_device->en_dbac_enabled == OAL_TRUE)
#else
#define MAC_DBAC_ENABLE(_pst_device) (OAL_FALSE)
#endif
#ifdef _PRE_WLAN_FEATURE_WMMAC
extern oal_bool_enum_uint8 g_en_wmmac_switch;
#endif

/*****************************************************************************
 �� �� ��  : mac_is_dbac_enabled
 ��������  : �ж϶�Ӧdevice��dbac�����Ƿ�ʹ��
 �������  : mac_device_stru *pst_device
 �������  : ��
 �� �� ֵ  : OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��8��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8 mac_is_dbac_enabled(mac_device_stru *pst_device)
{
    return  pst_device->en_dbac_enabled;
}

/*****************************************************************************
 �� �� ��  : mac_is_dbac_running
 ��������  : �ж϶�Ӧdevice��dbac�����Ƿ�������
 �������  : mac_device_stru *pst_device
 �������  : ��
 �� �� ֵ  : OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��8��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8 mac_is_dbac_running(mac_device_stru *pst_device)
{
    if (OAL_FALSE == pst_device->en_dbac_enabled)
    {
        return OAL_FALSE;
    }

    return  pst_device->en_dbac_running;
}

#ifdef _PRE_WLAN_FEATURE_DBAC
/*****************************************************************************
 �� �� ��  : mac_need_enqueue_tid_for_dbac
 ��������  : ����֡�Ƿ���Ҫ��tid����
 �������  : mac_device_stru *pst_device
             mac_vap_stru *pst_vap
 �������  : ��
 �� �� ֵ  : OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��8��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8 mac_need_enqueue_tid_for_dbac(mac_device_stru *pst_device, mac_vap_stru *pst_vap)
{
    return  (OAL_TRUE == pst_device->en_dbac_enabled) && (MAC_VAP_STATE_PAUSE == pst_vap->en_vap_state) ? OAL_TRUE : OAL_FALSE;
}
#endif
#ifdef _PRE_SUPPORT_ACS
/*****************************************************************************
 �� �� ��  : mac_get_acs_switch
 ��������  : ��ȡACS����״̬
 �������  : mac_device_stru *pst_mac_device
 �������  : ��
 �� �� ֵ  : OAL_STATIC  OAL_INLINE  en_mac_acs_sw_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE  en_mac_acs_sw_enum_uint8 mac_get_acs_switch(mac_device_stru *pst_mac_device)
{
    if (pst_mac_device->pst_acs == OAL_PTR_NULL)
    {
        return MAC_ACS_SW_NONE;
    }

    return pst_mac_device->st_acs_switch.en_acs_switch;
}
/*****************************************************************************
 �� �� ��  : mac_set_acs_switch
 ��������  : ����ACS����״̬
 �������  : mac_device_stru *pst_mac_device
             en_mac_acs_sw_enum_uint8 en_switch
 �������  : ��
 �� �� ֵ  : OAL_STATIC  OAL_INLINE  oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE  oal_void mac_set_acs_switch(mac_device_stru *pst_mac_device, en_mac_acs_sw_enum_uint8 en_switch)
{
    if (pst_mac_device->pst_acs == OAL_PTR_NULL)
    {
        return;
    }

    pst_mac_device->st_acs_switch.en_acs_switch = en_switch;
}
#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8 mac_get_2040bss_switch(mac_device_stru *pst_mac_device)
{
    return pst_mac_device->en_2040bss_switch;
}
OAL_STATIC  OAL_INLINE  oal_void mac_set_2040bss_switch(mac_device_stru *pst_mac_device, oal_bool_enum_uint8 en_switch)
{
    pst_mac_device->en_2040bss_switch = en_switch;
}
#endif

#if IS_DEVICE
OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8 mac_device_is_scaning(mac_device_stru *pst_mac_device)
{
    return (pst_mac_device->en_curr_scan_state == MAC_SCAN_STATE_RUNNING)?OAL_TRUE:OAL_FALSE;
}

OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8 mac_device_is_listening(mac_device_stru *pst_mac_device)
{
    return ((pst_mac_device->en_curr_scan_state == MAC_SCAN_STATE_RUNNING)
            && (pst_mac_device->st_scan_params.uc_scan_func & MAC_SCAN_FUNC_P2P_LISTEN))?OAL_TRUE:OAL_FALSE;
}
#endif /* IS_DEVICE */

/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
  10.1 �����ṹ���ʼ����ɾ��
*****************************************************************************/
extern oal_uint32  mac_device_init(mac_device_stru *pst_mac_device, oal_uint32 ul_chip_ver, oal_uint8 chip_id, oal_uint8 uc_device_id);
extern oal_uint32  mac_chip_init(mac_chip_stru *pst_chip, oal_uint8 uc_chip_id);
extern oal_uint32  mac_board_init(mac_board_stru *pst_board);

extern oal_uint32  mac_device_exit(mac_device_stru *pst_device);
extern oal_uint32  mac_chip_exit(mac_board_stru *pst_board, mac_chip_stru *pst_chip);
extern oal_uint32  mac_board_exit(mac_board_stru *pst_board);


/*****************************************************************************
  10.2 ������Ա���ʲ���
*****************************************************************************/
extern oal_void mac_device_set_vap_id(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap,  oal_uint8 uc_vap_idx, wlan_vap_mode_enum_uint8 en_vap_mode, wlan_p2p_mode_enum_uint8 en_p2p_mode, oal_uint8 is_add_vap);
extern oal_void mac_device_set_dfr_reset(mac_device_stru *pst_mac_device, oal_uint8 uc_device_reset_in_progress);
extern oal_void mac_device_set_state(mac_device_stru *pst_mac_device, oal_uint8 en_device_state);

extern oal_void mac_device_set_channel(mac_device_stru *pst_mac_device, mac_cfg_channel_param_stru * pst_channel_param);
extern oal_void mac_device_get_channel(mac_device_stru *pst_mac_device, mac_cfg_channel_param_stru * pst_channel_param);

extern oal_void mac_device_set_txchain(mac_device_stru *pst_mac_device, oal_uint8 uc_tx_chain);
extern oal_void mac_device_set_rxchain(mac_device_stru *pst_mac_device, oal_uint8 uc_rx_chain);
extern oal_void mac_device_set_beacon_interval(mac_device_stru *pst_mac_device, oal_uint32 ul_beacon_interval);
extern oal_void mac_device_inc_active_user(mac_device_stru *pst_mac_device);

extern oal_void mac_device_dec_active_user(mac_device_stru *pst_mac_device);
#if 0
extern oal_void mac_device_inc_assoc_user(mac_device_stru *pst_mac_device);
extern oal_void mac_device_dec_assoc_user(mac_device_stru *pst_mac_device);
extern oal_void mac_device_set_dfs(mac_device_stru *pst_mac_device, oal_bool_enum_uint8 en_dfs_switch, oal_uint8 uc_debug_level);
#endif
extern oal_void * mac_device_get_all_rates(mac_device_stru *pst_dev);
#ifdef _PRE_WLAN_FEATURE_HILINK
extern oal_uint32  mac_device_clear_fbt_scan_list(mac_device_stru *pst_mac_dev, oal_uint8 *puc_param);
extern oal_uint32  mac_device_set_fbt_scan_sta(mac_device_stru *pst_mac_dev, mac_fbt_scan_sta_addr_stru *pst_fbt_scan_sta);
extern oal_uint32  mac_device_set_fbt_scan_interval(mac_device_stru *pst_mac_dev, oal_uint32 ul_scan_interval);
extern oal_uint32  mac_device_set_fbt_scan_channel(mac_device_stru *pst_mac_dev, oal_uint8 uc_fbt_scan_channel);
extern oal_uint32  mac_device_set_fbt_scan_report_period(mac_device_stru *pst_mac_dev, oal_uint32 ul_fbt_scan_report_period);
extern oal_uint32  mac_device_set_fbt_scan_enable(mac_device_stru *pst_mac_device, oal_uint8 uc_cfg_fbt_scan_enable);
#endif


/*****************************************************************************
  10.3 ���������
*****************************************************************************/
#if 0
#ifdef _PRE_WLAN_FEATURE_DBAC
extern oal_uint32  mac_dbac_update_chl_config(mac_device_stru *pst_mac_device, mac_channel_stru *pst_chl);
#endif
#endif

extern oal_uint32  mac_device_find_up_vap(mac_device_stru *pst_mac_device, mac_vap_stru **ppst_mac_vap);
extern mac_vap_stru * mac_device_find_another_up_vap(mac_device_stru *pst_mac_device, oal_uint8 uc_vap_id_self);
extern oal_uint32  mac_device_find_up_ap(mac_device_stru *pst_mac_device, mac_vap_stru **ppst_mac_vap);
extern oal_uint32  mac_device_calc_up_vap_num(mac_device_stru *pst_mac_device);
extern oal_uint32 mac_device_calc_work_vap_num(mac_device_stru *pst_mac_device);
extern oal_uint32  mac_device_find_up_p2p_go(mac_device_stru *pst_mac_device, mac_vap_stru **ppst_mac_vap);
extern oal_uint32  mac_device_find_2up_vap(
                mac_device_stru *pst_mac_device,
                mac_vap_stru   **ppst_mac_vap1,
                mac_vap_stru   **ppst_mac_vap2);
extern oal_uint32  mac_fcs_dbac_state_check(mac_device_stru *pst_mac_device);
extern oal_uint32  mac_device_find_up_sta(mac_device_stru *pst_mac_device, mac_vap_stru **ppst_mac_vap);

extern oal_uint32  mac_device_is_p2p_connected(mac_device_stru *pst_mac_device);
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
extern mac_vap_stru *mac_find_main_proxysta(mac_device_stru *pst_mac_device);
#endif
/*****************************************************************************
  10.4 ���Ƴ�
*****************************************************************************/

/*****************************************************************************
  11 inline��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : mac_is_hide_ssid
 ��������  : �Ƿ�Ϊ����ssid
 �������  : oal_uint8 *puc_ssid_ie,    ssid_ie������
             oal_uint8 uc_ssid_len,     ssid�ĳ���
 �������  : ��
 �� �� ֵ  : OAL_TRUE : ��
             OAL_FALSE: ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��11��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_is_hide_ssid(oal_uint8 *puc_ssid_ie, oal_uint8 uc_ssid_len)
{
    return ((OAL_PTR_NULL == puc_ssid_ie) || (0 == uc_ssid_len) || ('\0' == puc_ssid_ie[0]));
}

/*****************************************************************************
 �� �� ��  : mac_device_is_auto_chan_sel_enabled
 ��������  : �Ƿ����Զ��ŵ�ѡ��
 �������  : pst_mac_device: MAC DEVICE�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_TRUE : ����
             OAL_FALSE: û�п���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��29��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_device_is_auto_chan_sel_enabled(mac_device_stru *pst_mac_device)
{
    /* BSS����ʱ������û�û�������ŵ�����Ĭ��Ϊ�����Զ��ŵ�ѡ�� */
    if (0 == pst_mac_device->uc_max_channel)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}


#ifdef _PRE_WLAN_FEATURE_DFS
/*****************************************************************************
 �� �� ��  : mac_dfs_set_cac_enable
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
OAL_STATIC OAL_INLINE oal_void  mac_dfs_set_cac_enable(mac_device_stru *pst_mac_device, oal_bool_enum_uint8 en_val)
{
    pst_mac_device->st_dfs.st_dfs_info.en_cac_switch = en_val;
}

/*****************************************************************************
 �� �� ��  : mac_dfs_set_offchan_cac_enable
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��27��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_dfs_set_offchan_cac_enable(mac_device_stru *pst_mac_device, oal_bool_enum_uint8 en_val)
{
    pst_mac_device->st_dfs.st_dfs_info.en_offchan_cac_switch = en_val;
}

/*****************************************************************************
 �� �� ��  : mac_dfs_get_offchan_cac_enable
 ��������  : ETSI��׼�״���Ҫoff-channel cac���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��2��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_dfs_get_offchan_cac_enable(mac_device_stru *pst_mac_device)
{
    mac_regdomain_info_stru   *pst_rd_info;

    mac_get_regdomain_info(&pst_rd_info);
    if(MAC_DFS_DOMAIN_ETSI == pst_rd_info->en_dfs_domain)
    {
        return pst_mac_device->st_dfs.st_dfs_info.en_offchan_cac_switch;
    }

    return OAL_FALSE;
}


/*****************************************************************************
 �� �� ��  : mac_dfs_set_offchan_cac_enable
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��27��
    ��    ��   : sunxiaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_dfs_set_offchan_number(mac_device_stru *pst_mac_device, oal_uint32 ul_val)
{
    pst_mac_device->st_dfs.st_dfs_info.uc_offchan_num = ul_val;
}


/*****************************************************************************
 �� �� ��  : mac_dfs_get_cac_enable
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
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_dfs_get_cac_enable(mac_device_stru *pst_mac_device)
{
    return pst_mac_device->st_dfs.st_dfs_info.en_cac_switch;
}

/*****************************************************************************
 �� �� ��  : mac_dfs_set_dfs_enable
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
OAL_STATIC OAL_INLINE oal_void  mac_dfs_set_dfs_enable(mac_device_stru *pst_mac_device, oal_bool_enum_uint8 en_val)
{
    pst_mac_device->st_dfs.st_dfs_info.en_dfs_switch = en_val;

    /* ��� ����״���ʹ�� �رգ���ر�CAC��� */
    if (OAL_FALSE == en_val)
    {
        pst_mac_device->st_dfs.st_dfs_info.en_cac_switch = OAL_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : mac_dfs_get_dfs_enable
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_dfs_get_dfs_enable(mac_device_stru *pst_mac_device)
{
    if (WLAN_BAND_5G == pst_mac_device->en_max_band)
    {
        return pst_mac_device->st_dfs.st_dfs_info.en_dfs_switch;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : mac_dfs_set_debug_level
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
OAL_STATIC OAL_INLINE oal_void  mac_dfs_set_debug_level(mac_device_stru *pst_mac_device, oal_uint8 uc_debug_lev)
{
    pst_mac_device->st_dfs.st_dfs_info.uc_debug_level = uc_debug_lev;
}

/*****************************************************************************
 �� �� ��  : mac_dfs_get_debug_level
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
OAL_STATIC OAL_INLINE oal_uint8  mac_dfs_get_debug_level(mac_device_stru *pst_mac_device)
{
    return pst_mac_device->st_dfs.st_dfs_info.uc_debug_level;
}
#endif

extern  oal_uint32  mac_fcs_init(mac_fcs_mgr_stru *pst_fcs_mgr,
                                  oal_uint8        uc_chip_id,
                                  oal_uint8        uc_device_id);

extern  mac_fcs_err_enum_uint8  mac_fcs_request(mac_fcs_mgr_stru           *pst_fcs_mgr,
                                                mac_fcs_state_enum_uint8   *puc_state,
                                                mac_fcs_cfg_stru           *pst_fcs_cfg);

extern  void    mac_fcs_release(mac_fcs_mgr_stru *pst_fcs_mgr);

extern  mac_fcs_err_enum_uint8    mac_fcs_start(mac_fcs_mgr_stru *pst_fcs_mgr,
                                                mac_fcs_cfg_stru *pst_fcs_cfg,
                                                hal_one_packet_status_stru *pst_status,
                                                oal_uint8 uc_fake_tx_q_id);
extern mac_fcs_err_enum_uint8    mac_fcs_start_enhanced(
                mac_fcs_mgr_stru            *pst_fcs_mgr,
                mac_fcs_cfg_stru            *pst_fcs_cfg);
extern oal_void mac_fcs_send_one_packet_start(mac_fcs_mgr_stru *pst_fcs_mgr,
                                       hal_one_packet_cfg_stru *pst_one_packet_cfg,
                                       hal_to_dmac_device_stru *pst_device,
                                    hal_one_packet_status_stru *pst_status,
                                           oal_bool_enum_uint8  en_ps);
extern  oal_uint32 mac_fcs_notify_chain_register (mac_fcs_mgr_stru              *pst_fcs_mgr,
                                                  mac_fcs_notify_type_enum_uint8 uc_notify_type,
                                                  mac_fcs_hook_id_enum_uint8     en_hook_id,
                                                  mac_fcs_notify_func            p_func);

extern  oal_uint32  mac_fcs_notify(mac_fcs_mgr_stru               *pst_fcs_mgr,
                                   mac_fcs_notify_type_enum_uint8  uc_notify_type);

extern  oal_uint32 mac_fcs_notify_chain_unregister(mac_fcs_mgr_stru              *pst_fcs_mgr,
                                                   mac_fcs_notify_type_enum_uint8 uc_notify_type,
                                                   mac_fcs_hook_id_enum_uint8     en_hook_id);

extern  oal_uint32  mac_fcs_notify_chain_destroy(mac_fcs_mgr_stru *pst_fcs_mgr);

extern oal_uint32  mac_fcs_get_prot_mode(mac_vap_stru *pst_src_vap);
extern oal_uint32  mac_fcs_get_prot_datarate(mac_vap_stru *pst_src_vap);
extern oal_void  mac_fcs_prepare_one_packet_cfg(
                mac_vap_stru                *pst_mac_vap,
                hal_one_packet_cfg_stru     *pst_one_packet_cfg,
                oal_uint16                   us_protect_time);

/*****************************************************************************
 �� �� ��  : mac_fcs_is_same_channel
 ��������  : �ж��Ƿ�Ϊ��ͬ�ŵ�
 �������  : mac_channel_stru *pst_channel_dst
             mac_channel_stru *pst_channel_src
 �������  : ��
 �� �� ֵ  : OAL_STATIC  OAL_INLINE  oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��10��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 mac_fcs_is_same_channel(mac_channel_stru *pst_channel_dst,
                                                                  mac_channel_stru *pst_channel_src)
{
    return  pst_channel_dst->uc_chan_number == pst_channel_src->uc_chan_number ? OAL_TRUE : OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : mac_fcs_get_protect_type
 ��������  : ����VAPģʽ��ȡ����֡����
 �������  : pst_mac_vap: vap
 �������  : ��
 �� �� ֵ  : OAL_STATIC  OAL_INLINE  mac_fcs_protect_type_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��10��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE  hal_fcs_protect_type_enum_uint8 mac_fcs_get_protect_type(
                        mac_vap_stru *pst_mac_vap)
{
    hal_fcs_protect_type_enum_uint8 en_protect_type;

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        en_protect_type = HAL_FCS_PROTECT_TYPE_SELF_CTS;
    }
    else if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        en_protect_type = HAL_FCS_PROTECT_TYPE_NULL_DATA;
    }
    else
    {
        en_protect_type = HAL_FCS_PROTECT_TYPE_NONE;
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    if (WLAN_P2P_GO_MODE == pst_mac_vap->en_p2p_mode)
    {
        en_protect_type = HAL_FCS_PROTECT_TYPE_NONE;
    }
#endif

    return en_protect_type;
}

/*****************************************************************************
 �� �� ��  : mac_fcs_get_protect_cnt
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  OAL_INLINE oal_uint8  mac_fcs_get_protect_cnt(mac_vap_stru *pst_mac_vap)
{
    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        return HAL_FCS_PROTECT_CNT_1;
    }

    return HAL_FCS_PROTECT_CNT_3;
}

#if (_PRE_TEST_MODE_BOARD_ST == _PRE_TEST_MODE)
extern  oal_void mac_fcs_verify_init(oal_void);
extern  oal_void mac_fcs_verify_start(oal_void);
extern  oal_void mac_fcs_verify_timestamp(mac_fcs_stage_enum_uint8 en_stage);
extern  oal_void mac_fcs_verify_stop(oal_void);

#else
#define          mac_fcs_verify_init()
#define          mac_fcs_verify_start()
#define          mac_fcs_verify_timestamp(a)
#define          mac_fcs_verify_stop()
#endif  // _PRE_DEBUG_MODE

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_device.h */
