/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mac_vap.h
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   : mac_vap.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __MAC_VAP_H__
#define __MAC_VAP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_mib.h"
#include "mac_user.h"
#include "oam_ext_if.h"
#include "mac_regdomain.h"
#include "hal_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_VAP_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MAC_NUM_DR_802_11A              8    /* 11A 5gģʽʱ����������(DR)���� */
#define MAC_NUM_BR_802_11A              3    /* 11A 5gģʽʱ�Ļ�������(BR)���� */
#define MAC_NUM_NBR_802_11A             5    /* 11A 5gģʽʱ�ķǻ�������(NBR)���� */

#define MAC_NUM_DR_802_11B              4    /* 11B 2.4Gģʽʱ����������(DR)���� */
#define MAC_NUM_BR_802_11B              2    /* 11B 2.4Gģʽʱ����������(BR)���� */
#define MAC_NUM_NBR_802_11B             2    /* 11B 2.4Gģʽʱ����������(NBR)���� */

#define MAC_NUM_DR_802_11G              8    /* 11G 2.4Gģʽʱ����������(DR)���� */
#define MAC_NUM_BR_802_11G              3    /* 11G 2.4Gģʽʱ�Ļ�������(BR)���� */
#define MAC_NUM_NBR_802_11G             5    /* 11G 2.4Gģʽʱ�ķǻ�������(NBR)���� */

#define MAC_NUM_DR_802_11G_MIXED        12   /* 11G ���ģʽʱ����������(DR)���� */
#define MAC_NUM_BR_802_11G_MIXED_ONE    4    /* 11G ���1ģʽʱ�Ļ�������(BR)���� */
#define MAC_NUM_NBR_802_11G_MIXED_ONE   8    /* 11G ���1ģʽʱ�ķǻ�������(NBR)���� */

#define MAC_NUM_BR_802_11G_MIXED_TWO    7    /* 11G ���2ģʽʱ�Ļ�������(BR)���� */
#define MAC_NUM_NBR_802_11G_MIXED_TWO   5    /* 11G ���2ģʽʱ�ķǻ�������(NBR)���� */

/* 11N MCS��ص����� */
#if 0
#define MAC_MAX_RATE_SINGLE_NSS_20M_11N 72  /* 1���ռ���20MHz���������*/
#define MAC_MAX_RATE_SINGLE_NSS_40M_11N 150 /* 1���ռ���40MHz���������*/
#define MAC_MAX_RATE_DOUBLE_NSS_20M_11N 144 /* 1���ռ���80MHz���������*/
#define MAC_MAX_RATE_DOUBLE_NSS_40M_11N 300 /* 2���ռ���20MHz���������*/
#endif

#define MAC_MAX_RATE_SINGLE_NSS_20M_11N 0  /* 1���ռ���20MHz���������*/
#define MAC_MAX_RATE_SINGLE_NSS_40M_11N 0 /* 1���ռ���40MHz���������*/
#define MAC_MAX_RATE_DOUBLE_NSS_20M_11N 0 /* 1���ռ���80MHz���������*/
#define MAC_MAX_RATE_DOUBLE_NSS_40M_11N 0 /* 2���ռ���20MHz���������*/

/* 11AC MCS��ص����� */
#define MAC_MAX_SUP_MCS7_11AC_EACH_NSS   0   /* 11AC���ռ���֧�ֵ����MCS��ţ�֧��0-7*/
#define MAC_MAX_SUP_MCS8_11AC_EACH_NSS   1   /* 11AC���ռ���֧�ֵ����MCS��ţ�֧��0-8*/
#define MAC_MAX_SUP_MCS9_11AC_EACH_NSS   2   /* 11AC���ռ���֧�ֵ����MCS��ţ�֧��0-9*/
#define MAC_MAX_UNSUP_MCS_11AC_EACH_NSS  3   /* 11AC���ռ���֧�ֵ����MCS��ţ���֧��n���ռ���*/

#define MAC_MAX_RATE_SINGLE_NSS_20M_11AC 86  /* 1���ռ���20MHz���������*/
#define MAC_MAX_RATE_SINGLE_NSS_40M_11AC 200 /* 1���ռ���40MHz���������*/
#define MAC_MAX_RATE_SINGLE_NSS_80M_11AC 433 /* 1���ռ���80MHz���������*/
#define MAC_MAX_RATE_DOUBLE_NSS_20M_11AC 173 /* 2���ռ���20MHz���������*/
#define MAC_MAX_RATE_DOUBLE_NSS_40M_11AC 400 /* 2���ռ���40MHz���������*/
#define MAC_MAX_RATE_DOUBLE_NSS_80M_11AC 866 /* 2���ռ���80MHz���������*/


#define MAC_VAP_USER_HASH_INVALID_VALUE      0xFFFFFFFF                         /* HSAH�Ƿ�ֵ */
#define MAC_VAP_USER_HASH_MAX_VALUE         (WLAN_ASSOC_USER_MAX_NUM_LIMIT * 2)       /* 2Ϊ��չ���� */

#define MAC_VAP_CAP_ENABLE                   1
#define MAC_VAP_CAP_DISABLE                  0

#define MAC_VAP_FEATURE_ENABLE               1
#define MAC_VAP_FEATRUE_DISABLE              0

#define MAC_CALCULATE_HASH_VALUE(_puc_mac_addr)     \
    ((_puc_mac_addr[0] + _puc_mac_addr[1]           \
    + _puc_mac_addr[2] + _puc_mac_addr[3]           \
    + _puc_mac_addr[4] + _puc_mac_addr[5])          \
    & (MAC_VAP_USER_HASH_MAX_VALUE - 1))

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define MAC_VAP_PROXY_STA_HASH_MAX_VALUE     16       /* Ӳ������Ϊ16~31�����16��,��ʵ��ഴ��15��proxy sta */
#define MAC_PROXYSTA_CALCULATE_HASH_VALUE(_puc_mac_addr)     \
    ((_puc_mac_addr)[ETHER_ADDR_LEN - 1] & (MAC_VAP_PROXY_STA_HASH_MAX_VALUE - 1))
#endif

#define IS_AP(_pst_mac_vap)  (WLAN_VAP_MODE_BSS_AP  == (_pst_mac_vap)->en_vap_mode)
#define IS_STA(_pst_mac_vap) (WLAN_VAP_MODE_BSS_STA == (_pst_mac_vap)->en_vap_mode)

#define IS_P2P_DEV(_pst_mac_vap)    (WLAN_P2P_DEV_MODE    == (_pst_mac_vap)->en_p2p_mode)
#define IS_P2P_GO(_pst_mac_vap)     (WLAN_P2P_GO_MODE     == (_pst_mac_vap)->en_p2p_mode)
#define IS_P2P_CL(_pst_mac_vap)     (WLAN_P2P_CL_MODE     == (_pst_mac_vap)->en_p2p_mode)
#define IS_LEGACY_VAP(_pst_mac_vap) (WLAN_LEGACY_VAP_MODE == (_pst_mac_vap)->en_p2p_mode)

#define CIPHER_IS_WEP(cipher) ((WLAN_CIPHER_SUITE_WEP40 == cipher)||(WLAN_CIPHER_SUITE_WEP104 == cipher))

#ifdef _PRE_WLAN_DFT_STAT
#define   MAC_VAP_STATS_PKT_INCR(_member, _cnt)            ((_member) += (_cnt))
#define   MAC_VAP_STATS_BYTE_INCR(_member, _cnt)           ((_member) += (_cnt))
#endif

#define MAC_DATA_CONTAINER_HEADER_LEN 4
#define MAC_DATA_CONTAINER_MAX_LEN    512
#define MAC_DATA_CONTAINER_MIN_LEN    8  /*����Ҫ����1���¼�*/
#define MAC_DATA_HEADER_LEN           4

#define MAC_SEND_TWO_DEAUTH_FLAG    0xf000

#define MAC_DBB_SCALING_2G_RATE_NUM 12                /*2G rate���ʵĸ���*/
#define MAC_DBB_SCALING_5G_RATE_NUM 8                /*2G rate���ʵĸ���*/
#define MAC_DBB_SCALING_2G_RATE_OFFSET 0                /*2G Rate dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_2G_HT20_MCS_OFFSET 12                /*2G HT20 dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_2G_HT40_MCS_OFFSET 20                /*2G HT40 dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_2G_HT40_MCS32_OFFSET 61                /*2G HT40 mcs32 dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_5G_RATE_OFFSET 28                /*5G Rate dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_5G_HT20_MCS_OFFSET 40                /*5G HT20 dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_5G_HT20_MCS8_OFFSET 36                /*5G HT20 mcs8 dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_5G_HT40_MCS_OFFSET 48                /*5G HT40 dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_5G_HT40_MCS32_OFFSET 60                /*5G HT40 mcs32 dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_5G_HT80_MCS_OFFSET 66                /*5G HT80 dbb scaling ����ƫ��ֵ*/
#define MAC_DBB_SCALING_5G_HT80_MCS0_DELTA_OFFSET 2                /*5G HT80 mcs0/1 dbb scaling ����ƫ��ֵ����ֵ*/
#define MAC_DBB_SCALING_CFG_BITS 8                /*dbb scaling���üĴ���λ��*/
#define MAC_DBB_SCALING_FIX_POINT_BITS 8                /*dbb scaling ���㻯�Ŵ��� 256 (8 bits)*/
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#define MAC_NUM_2G_BAND 3   /* 2g band�� */
#define MAC_NUM_5G_BAND 7   /* 5g band�� */
#endif
#ifdef _PRE_WLAN_FEATURE_VOWIFI
/* VoWiFi��ز����ĺ궨�� */
#define MAC_VOWIFI_PERIOD_MIN   1   /* ��λs */
#define MAC_VOWIFI_PERIOD_MAX   30  /* ��λs */
#define MAC_VOWIFI_TRIGGER_COUNT_MIN   1
#define MAC_VOWIFI_TRIGGER_COUNT_MAX   100
#define MAC_VOWIFI_LOW_THRESHOLD_MIN   -100
#define MAC_VOWIFI_LOW_THRESHOLD_MAX   -1
#define MAC_VOWIFI_HIGH_THRESHOLD_MIN   -100
#define MAC_VOWIFI_HIGH_THRESHOLD_MAX   -1

#define MAC_VAP_VOWIFI_MODE_DEFAULT    VOWIFI_DISABLE_REPORT
#define MAC_VAP_VOWIFI_TRIGGER_COUNT_DEFAULT   5
#define MAC_VAP_VOWIFI_PERIOD_DEFAULT_MS       1000  /* ��λms */
#define MAC_VAP_VOWIFI_HIGH_THRES_DEFAULT      -65
#define MAC_VAP_VOWIFI_LOW_THRES_DEFAULT       -80

#endif

#ifdef _PRE_WLAN_FEATURE_11K
#define MAC_11K_SUPPORT_AP_CHAN_RPT_NUM 8
#define MAC_MEASUREMENT_RPT_FIX_LEN     5
#define MAC_BEACON_RPT_FIX_LEN          26
#define MAC_MAX_RPT_DETAIL_LEN          224   /*255 - 26(bcn fix) - 3(Meas rpt fix) - 2(subid 1)*/
#endif

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* VAP״̬����AP STA����һ��״̬ö�� */
typedef enum
{
    /* ap sta����״̬ */
    MAC_VAP_STATE_INIT               = 0,
    MAC_VAP_STATE_UP                 = 1,       /* VAP UP */
    MAC_VAP_STATE_PAUSE              = 2,       /* pause , for ap &sta */

    /* ap ����״̬ */
    MAC_VAP_STATE_AP_WAIT_START      = 3,

    /* sta����״̬ */
    MAC_VAP_STATE_STA_FAKE_UP        = 4,
    MAC_VAP_STATE_STA_WAIT_SCAN      = 5,
    MAC_VAP_STATE_STA_SCAN_COMP      = 6,
    MAC_VAP_STATE_STA_JOIN_COMP      = 7,
    MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2 = 8,
    MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4 = 9,
    MAC_VAP_STATE_STA_AUTH_COMP      = 10,
    MAC_VAP_STATE_STA_WAIT_ASOC      = 11,
    MAC_VAP_STATE_STA_OBSS_SCAN      = 12,
    MAC_VAP_STATE_STA_BG_SCAN        = 13,
    MAC_VAP_STATE_STA_LISTEN         = 14,/* p2p0 ���� */
#ifdef _PRE_WLAN_FEATURE_ROAM
    MAC_VAP_STATE_ROAMING            = 15,/* ���� */
#endif //_PRE_WLAN_FEATURE_ROAM
    MAC_VAP_STATE_BUTT,
}mac_vap_state_enum;
typedef oal_uint8  mac_vap_state_enum_uint8;

/* оƬ��֤������֡/����֡���� */
typedef enum
{

    MAC_TEST_MGMT_BCST   =  0,/* ��beacon�㲥����֡ */
    MAC_TEST_MGMT_MCST  =   1,/* ��beacon�鲥����֡ */
    MAC_TEST_ATIM_UCST =    2,/* ����ATIM֡ */
    MAC_TEST_UCST =         3,/* ��������֡ */
    MAC_TEST_CTL_BCST =     4,/* �㲥����֡ */
    MAC_TEST_CTL_MCST =     5,/* �鲥����֡ */
    MAC_TEST_CTL_UCST =     6,/* ��������֡ */
    MAC_TEST_ACK_UCST =     7,/* ACK����֡ */
    MAC_TEST_CTS_UCST =     8,/* CTS����֡ */
    MAC_TEST_RTS_UCST =     9,/* RTS����֡ */
    MAC_TEST_BA_UCST =      10,/* BA����֡ */
    MAC_TEST_CF_END_UCST =  11,/* CF-End����֡ */
    MAC_TEST_TA_RA_EUQAL =  12,/* RA,TA��ͬ֡ */
    MAC_TEST_MAX_TYPE_NUM
}mac_test_frame_type;
typedef oal_uint8 mac_test_frame_type_enum_uint8;



typedef enum
{
    MAC_VAP_CONFIG_UCAST_DATA  = 0,
    MAC_VAP_CONFIG_MCAST_DATA,
    MAC_VAP_CONFIG_BCAST_DATA,
    MAC_VAP_CONFIG_UCAST_MGMT_2G,
    MAC_VAP_CONFIG_UCAST_MGMT_5G,
    MAC_VAP_CONFIG_MBCAST_MGMT_2G,
    MAC_VAP_CONFIG_MBCAST_MGMT_5G,

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
    MAC_VAP_CONFIG_MODE_UCAST_DATA,                                 /* ����Э�����õ�������֡��������ʼö�� */
    MAC_VAP_CONFIG_VHT_UCAST_DATA = MAC_VAP_CONFIG_MODE_UCAST_DATA, /* ���11ac�û����õ�������֡���� */
    MAC_VAP_CONFIG_HT_UCAST_DATA,                                   /* ���11n�û����õ�������֡���� */
    MAC_VAP_CONFIG_11AG_UCAST_DATA,                                 /* ���11a/11g�û����õ�������֡���� */
    MAC_VAP_CONFIG_11B_UCAST_DATA,                                  /* ���11b�û����õ�������֡���� */
#endif

    MAC_VAP_CONFIG_BUTT,
} mac_vap_config_dscr_frame_type_enum;
typedef oal_uint8 mac_vap_config_dscr_frame_type_uint8;



typedef enum
{
    /* ҵ������㷨���ò���,����ӵ���Ӧ��START��END֮�� */
    MAC_ALG_CFG_SCHEDULE_START,

    MAC_ALG_CFG_SCHEDULE_VI_CTRL_ENA,
    MAC_ALG_CFG_SCHEDULE_BEBK_MIN_BW_ENA,
    MAC_ALG_CFG_SCHEDULE_MVAP_SCH_ENA,
    MAC_ALG_CFG_FLOWCTRL_ENABLE_FLAG,
    MAC_ALG_CFG_SCHEDULE_VI_SCH_LIMIT,
    MAC_ALG_CFG_SCHEDULE_VO_SCH_LIMIT,
    MAC_ALG_CFG_SCHEDULE_VI_DROP_LIMIT,
    MAC_ALG_CFG_SCHEDULE_VI_MSDU_LIFE_MS,
    MAC_ALG_CFG_SCHEDULE_VO_MSDU_LIFE_MS,
    MAC_ALG_CFG_SCHEDULE_BE_MSDU_LIFE_MS,
    MAC_ALG_CFG_SCHEDULE_BK_MSDU_LIFE_MS,
    MAC_ALG_CFG_SCHEDULE_VI_LOW_DELAY_MS,
    MAC_ALG_CFG_SCHEDULE_VI_HIGH_DELAY_MS,
    MAC_ALG_CFG_SCHEDULE_VI_CTRL_MS,
    MAC_ALG_CFG_SCHEDULE_SCH_CYCLE_MS,
    MAC_ALG_CFG_SCHEDULE_TRAFFIC_CTRL_CYCLE,
    MAC_ALG_CFG_SCHEDULE_CIR_NVIP_KBPS,
    MAC_ALG_CFG_SCHEDULE_CIR_NVIP_KBPS_BE,
    MAC_ALG_CFG_SCHEDULE_CIR_NVIP_KBPS_BK,
    MAC_ALG_CFG_SCHEDULE_CIR_VIP_KBPS,
    MAC_ALG_CFG_SCHEDULE_CIR_VIP_KBPS_BE,
    MAC_ALG_CFG_SCHEDULE_CIR_VIP_KBPS_BK,
    MAC_ALG_CFG_SCHEDULE_CIR_VAP_KBPS,
    MAC_ALG_CFG_SCHEDULE_SM_TRAIN_DELAY,
    MAC_ALG_CFG_VIDEO_DROP_PKT_LIMIT,
    MAC_ALG_CFG_SCHEDULE_LOG_START,
    MAC_ALG_CFG_SCHEDULE_VAP_SCH_PRIO,

    MAC_ALG_CFG_SCHEDULE_LOG_END,

    MAC_ALG_CFG_SCHEDULE_END,

    /* AUTORATE�㷨���ò���������ӵ���Ӧ��START��END֮��*/
    MAC_ALG_CFG_AUTORATE_START,

    MAC_ALG_CFG_AUTORATE_ENABLE,
    MAC_ALG_CFG_AUTORATE_USE_LOWEST_RATE,
    MAC_ALG_CFG_AUTORATE_SHORT_STAT_NUM,
    MAC_ALG_CFG_AUTORATE_SHORT_STAT_SHIFT,
    MAC_ALG_CFG_AUTORATE_LONG_STAT_NUM,
    MAC_ALG_CFG_AUTORATE_LONG_STAT_SHIFT,
    MAC_ALG_CFG_AUTORATE_MIN_PROBE_INTVL_PKTNUM,
    MAC_ALG_CFG_AUTORATE_MAX_PROBE_INTVL_PKTNUM,
    MAC_ALG_CFG_AUTORATE_PROBE_INTVL_KEEP_TIMES,
    MAC_ALG_CFG_AUTORATE_DELTA_GOODPUT_RATIO,
    MAC_ALG_CFG_AUTORATE_VI_PROBE_PER_LIMIT,
    MAC_ALG_CFG_AUTORATE_VO_PROBE_PER_LIMIT,
    MAC_ALG_CFG_AUTORATE_AMPDU_DURATION,
    MAC_ALG_CFG_AUTORATE_MCS0_CONT_LOSS_NUM,
    MAC_ALG_CFG_AUTORATE_UP_PROTOCOL_DIFF_RSSI,
    MAC_ALG_CFG_AUTORATE_RTS_MODE,
    MAC_ALG_CFG_AUTORATE_LEGACY_1ST_LOSS_RATIO_TH,
    MAC_ALG_CFG_AUTORATE_HT_VHT_1ST_LOSS_RATIO_TH,
    MAC_ALG_CFG_AUTORATE_LOG_ENABLE,
    MAC_ALG_CFG_AUTORATE_VO_RATE_LIMIT,
    MAC_ALG_CFG_AUTORATE_JUDGE_FADING_PER_TH,
    MAC_ALG_CFG_AUTORATE_AGGR_OPT,
    MAC_ALG_CFG_AUTORATE_AGGR_PROBE_INTVL_NUM,
    MAC_ALG_CFG_AUTORATE_AGGR_STAT_SHIFT,
    MAC_ALG_CFG_AUTORATE_DBAC_AGGR_TIME,
    MAC_ALG_CFG_AUTORATE_DBG_VI_STATUS,
    MAC_ALG_CFG_AUTORATE_DBG_AGGR_LOG,
    MAC_ALG_CFG_AUTORATE_AGGR_NON_PROBE_PCK_NUM,
    MAC_ALG_CFG_AUTORATE_AGGR_MIN_AGGR_TIME_IDX,
    MAC_ALG_CFG_AUTORATE_MAX_AGGR_NUM,
    MAC_ALG_CFG_AUTORATE_LIMIT_1MPDU_PER_TH,
    MAC_ALG_CFG_AUTORATE_BTCOEX_PROBE_ENABLE,
    MAC_ALG_CFG_AUTORATE_BTCOEX_AGGR_ENABLE,
    MAC_ALG_CFG_AUTORATE_COEX_STAT_INTVL,
    MAC_ALG_CFG_AUTORATE_COEX_LOW_ABORT_TH,
    MAC_ALG_CFG_AUTORATE_COEX_HIGH_ABORT_TH,
    MAC_ALG_CFG_AUTORATE_COEX_AGRR_NUM_ONE_TH,
    MAC_ALG_CFG_AUTORATE_DYNAMIC_BW_ENABLE,
    MAC_ALG_CFG_AUTORATE_THRPT_WAVE_OPT,
    MAC_ALG_CFG_AUTORATE_GOODPUT_DIFF_TH,
    MAC_ALG_CFG_AUTORATE_PER_WORSE_TH,
    MAC_ALG_CFG_AUTORATE_RX_CTS_NO_BA_NUM,
    MAL_ALG_CFG_AUTORATE_VOICE_AGGR,
    MAC_ALG_CFG_AUTORATE_FAST_SMOOTH_SHIFT,
    MAC_ALG_CFG_AUTORATE_FAST_SMOOTH_AGGR_NUM,
    MAC_ALG_CFG_AUTORATE_SGI_PUNISH_PER,
    MAC_ALG_CFG_AUTORATE_SGI_PUNISH_NUM,

    MAC_ALG_CFG_AUTORATE_END,

    /*AUTORATE�㷨��־���ò���������ӵ���Ӧ��START��END֮�� */
    MAC_ALG_CFG_AUTORATE_LOG_START,

    MAC_ALG_CFG_AUTORATE_STAT_LOG_START,
    MAC_ALG_CFG_AUTORATE_SELECTION_LOG_START,
    MAC_ALG_CFG_AUTORATE_FIX_RATE_LOG_START,
    MAC_ALG_CFG_AUTORATE_STAT_LOG_WRITE,
    MAC_ALG_CFG_AUTORATE_SELECTION_LOG_WRITE,
    MAC_ALG_CFG_AUTORATE_FIX_RATE_LOG_WRITE,
    MAC_ALG_CFG_AUTORATE_AGGR_STAT_LOG_START,
    MAC_ALG_CFG_AUTORATE_AGGR_STAT_LOG_WRITE,

    MAC_ALG_CFG_AUTORATE_LOG_END,

    /*AUTORATE�㷨ϵͳ�����������ӵ���Ӧ��START��END֮�� */
    MAC_ALG_CFG_AUTORATE_TEST_START,

    MAC_ALG_CFG_AUTORATE_DISPLAY_RATE_SET,
    MAC_ALG_CFG_AUTORATE_CONFIG_FIX_RATE,
    MAC_ALG_CFG_AUTORATE_CYCLE_RATE,
    MAC_ALG_CFG_AUTORATE_DISPLAY_RX_RATE,

    MAC_ALG_CFG_AUTORATE_TEST_END,

    /* SMARTANT�㷨���ò����� ����ӵ���Ӧ��START��END֮��*/
    MAC_ALG_CFG_SMARTANT_START,

    MAC_ALG_CFG_SMARTANT_ENABLE,
    MAC_ALG_CFG_SMARTANT_CERTAIN_ANT,
    MAC_ALG_CFG_SMARTANT_TRAINING_PACKET_NUMBER,
    MAC_ALG_CFG_SMARTANT_CHANGE_ANT,
    MAC_ALG_CFG_SMARTANT_START_TRAIN,
    MAC_ALG_CFG_SMARTANT_SET_TRAINING_PACKET_NUMBER,
    MAC_ALG_CFG_SMARTANT_SET_LEAST_PACKET_NUMBER,
    MAC_ALG_CFG_SMARTANT_SET_ANT_CHANGE_INTERVAL,
    MAC_ALG_CFG_SMARTANT_SET_USER_CHANGE_INTERVAL,
    MAC_ALG_CFG_SMARTANT_SET_PERIOD_MAX_FACTOR,
    MAC_ALG_CFG_SMARTANT_SET_ANT_CHANGE_FREQ,
    MAC_ALG_CFG_SMARTANT_SET_ANT_CHANGE_THRESHOLD,

    MAC_ALG_CFG_SMARTANT_END,
    /* TXBF�㷨���ò���������ӵ���Ӧ��START��END֮��*/
    MAC_ALG_CFG_TXBF_START,
    MAC_ALG_CFG_TXBF_MASTER_SWITCH,
    MAC_ALG_CFG_TXBF_TXMODE_ENABLE,
    MAC_ALG_CFG_TXBF_TXBFER_ENABLE,
    MAC_ALG_CFG_TXBF_TXBFEE_ENABLE,
    MAC_ALG_CFG_TXBF_11N_BFEE_ENABLE,
    MAC_ALG_CFG_TXBF_TXSTBC_ENABLE,
    MAC_ALG_CFG_TXBF_RXSTBC_ENABLE,
    MAC_ALG_CFG_TXBF_2G_BFER_ENABLE,
    MAC_ALG_CFG_TXBF_2NSS_BFER_ENABLE,
    MAC_ALG_CFG_TXBF_FIX_MODE,
    MAC_ALG_CFG_TXBF_FIX_SOUNDING,
    MAC_ALG_CFG_TXBF_PROBE_INT,
    MAC_ALG_CFG_TXBF_REMOVE_WORST,
    MAC_ALG_CFG_TXBF_STABLE_NUM,
    MAC_ALG_CFG_TXBF_PROBE_COUNT,
    MAC_ALG_CFG_TXBF_LOG_ENABLE,
    MAC_ALG_CFG_TXBF_END,
    /* TXBF LOG���ò���������ӵ���Ӧ��START��END֮��*/
    MAC_ALG_CFG_TXBF_LOG_START,
    MAC_ALG_CFG_TXBF_RECORD_LOG_START,
    MAC_ALG_CFG_TXBF_LOG_OUTPUT,
    MAC_ALG_CFG_TXBF_LOG_END,

    /* �������㷨���ò���������ӵ���Ӧ��START��END֮�� */
    MAC_ALG_CFG_ANTI_INTF_START,

    MAC_ALG_CFG_ANTI_INTF_IMM_ENABLE,
    MAC_ALG_CFG_ANTI_INTF_UNLOCK_ENABLE,
    MAC_ALG_CFG_ANTI_INTF_RSSI_STAT_CYCLE,
    MAC_ALG_CFG_ANTI_INTF_UNLOCK_CYCLE,
    MAC_ALG_CFG_ANTI_INTF_UNLOCK_DUR_TIME,
    MAC_ALG_CFG_ANTI_INTF_NAV_IMM_ENABLE,
    MAC_ALG_CFG_ANTI_INTF_GOODPUT_FALL_TH,
    MAC_ALG_CFG_ANTI_INTF_KEEP_CYC_MAX_NUM,
    MAC_ALG_CFG_ANTI_INTF_KEEP_CYC_MIN_NUM,
    MAC_ALG_CFG_ANTI_INTF_TX_TIME_FALL_TH,
    MAC_ALG_CFG_ANTI_INTF_PER_PROBE_EN,
    MAC_ALG_CFG_ANTI_INTF_PER_FALL_TH,
    MAC_ALG_CFG_ANTI_INTF_GOODPUT_JITTER_TH,
    MAC_ALG_CFG_ANTI_INTF_DEBUG_MODE,

    MAC_ALG_CFG_ANTI_INTF_END,

    /* EDCA�Ż��㷨���ò���������ӵ���Ӧ��START��END֮�� */
    MAC_ALG_CFG_EDCA_OPT_START,

    MAC_ALG_CFG_EDCA_OPT_CO_CH_DET_CYCLE,
    MAC_ALG_CFG_EDCA_OPT_AP_EN_MODE,
    MAC_ALG_CFG_EDCA_OPT_STA_EN,
    MAC_ALG_CFG_EDCA_OPT_STA_WEIGHT,
    MAC_ALG_CFG_EDCA_OPT_NONDIR_TH,
    MAC_ALG_CFG_EDCA_OPT_TH_UDP,
    MAC_ALG_CFG_EDCA_OPT_TH_TCP,
    MAC_ALG_CFG_EDCA_OPT_DEBUG_MODE,
    MAC_ALG_CFG_EDCA_OPT_FE_PORT_OPT,
    MAC_ALG_CFG_EDCA_OPT_FE_PORT_DBG,
    MAC_ALG_CFG_EDCA_OPT_MPDU_DEC_RATIO_TH,
    MAC_ALG_CFG_EDCA_OPT_DEFAULT_CW_MPDU_TH,

    MAC_ALG_CFG_EDCA_OPT_END,

    /* CCA�Ż��㷨���ò���������ӵ���Ӧ��START��END֮�� */
    MAC_ALG_CFG_CCA_OPT_START,

    MAC_ALG_CFG_CCA_OPT_ALG_EN_MODE,
    MAC_ALG_CFG_CCA_OPT_DEBUG_MODE,
    MAC_ALG_CFG_CCA_OPT_SET_T1_COUNTER_TIME,
    MAC_ALG_CFG_CCA_OPT_SET_T2_COUNTER_TIME,
    MAC_ALG_CFG_CCA_OPT_SET_ILDE_CNT_TH,
    MAC_ALG_CFG_CCA_OPT_SET_DUTY_CYC_TH,
    MAC_ALG_CFG_CCA_OPT_SET_AVEG_RSSI_TH,
    MAC_ALG_CFG_CCA_OPT_SET_CHN_SCAN_CYC,
    MAC_ALG_CFG_CCA_OPT_SET_SYNC_ERR_TH,
    MAC_ALG_CFG_CCA_OPT_SET_CCA_TH_DEBUG,
    MAC_ALG_CFG_CCA_OPT_LOG,
    MAC_ALG_CFG_CCA_OPT_SET_COLLISION_RATIO_TH,
    MAC_ALG_CFG_CCA_OPT_SET_GOODPUT_LOSS_TH,
    MAC_ALG_CFG_CCA_OPT_SET_MAX_INTVL_NUM,
    MAC_ALG_CFG_CCA_OPT_NON_INTF_CYCLE_NUM_TH,
    MAC_ALG_CFG_CCA_OPT_NON_INTF_DUTY_CYC_TH,
    MAC_ALG_CFG_CCA_OPT_END,

    /*CCA OPT�㷨��־���ò���������ӵ���Ӧ��START��END֮�� */
    MAC_ALG_CFG_CCA_OPT_LOG_START,
    MAC_ALG_CFG_CCA_OPT_STAT_LOG_START,
    MAC_ALG_CFG_CCA_OPT_STAT_LOG_WRITE,
    MAC_ALG_CFG_CCA_OPT_LOG_END,

    /* TPC�㷨���ò���, ����ӵ���Ӧ��START��END֮��*/
    MAC_ALG_CFG_TPC_START,

    MAC_ALG_CFG_TPC_MODE,
    MAC_ALG_CFG_TPC_DEBUG,
    MAC_ALG_CFG_TPC_POWER_LEVEL,
    MAC_ALG_CFG_TPC_LOG,
    MAC_ALG_CFG_TPC_MANAGEMENT_MCAST_FRM_POWER_LEVEL,
    MAC_ALG_CFG_TPC_CONTROL_FRM_POWER_LEVEL,
    MAC_ALG_CFG_TPC_OVER_TMP_TH,
    MAC_ALG_CFG_TPC_DPD_ENABLE_RATE,
    MAC_ALG_CFG_TPC_TARGET_RATE_11B,
    MAC_ALG_CFG_TPC_TARGET_RATE_11AG,
    MAC_ALG_CFG_TPC_TARGET_RATE_HT20,
    MAC_ALG_CFG_TPC_TARGET_RATE_HT40,
    MAC_ALG_CFG_TPC_TARGET_RATE_VHT20,
    MAC_ALG_CFG_TPC_TARGET_RATE_VHT40,
    MAC_ALG_CFG_TPC_TARGET_RATE_VHT80,
    MAC_ALG_CFG_TPC_SHOW_LOG_INFO,
    MAC_ALG_CFG_TPC_NO_MARGIN_POW,
    MAC_ALG_CFG_TPC_POWER_AMEND,

    MAC_ALG_CFG_TPC_END,

    /*TPC�㷨��־���ò���������ӵ���Ӧ��START��END֮�� */
    MAC_ALG_CFG_TPC_LOG_START,

    MAC_ALG_CFG_TPC_STAT_LOG_START,
    MAC_ALG_CFG_TPC_STAT_LOG_WRITE,
    MAC_ALG_CFG_TPC_PER_PKT_LOG_START,
    MAC_ALG_CFG_TPC_PER_PKT_LOG_WRITE,
    MAC_ALG_CFG_TPC_GET_FRAME_POW,
    MAC_ALG_CFG_TPC_RESET_STAT,
    MAC_ALG_CFG_TPC_RESET_PKT,

    MAC_ALG_CFG_TPC_LOG_END,

    MAC_ALG_CFG_BUTT
}mac_alg_cfg_enum;
typedef oal_uint8 mac_alg_cfg_enum_uint8;

typedef enum            /* hi1102-cb */
{
    SHORTGI_20_CFG_ENUM,
    SHORTGI_40_CFG_ENUM,
    SHORTGI_80_CFG_ENUM,
    SHORTGI_BUTT_CFG
}short_gi_cfg_type;

typedef enum
{
    MAC_SET_BEACON  = 0,
    MAC_ADD_BEACON  = 1,

    MAC_BEACON_OPERATION_BUTT
}mac_beacon_operation_type ;
typedef oal_uint8 mac_beacon_operation_type_uint8;

typedef enum
{
    MAC_WMM_SET_PARAM_TYPE_DEFAULT,
    MAC_WMM_SET_PARAM_TYPE_UPDATE_EDCA,

    MAC_WMM_SET_PARAM_TYPE_BUTT
}mac_wmm_set_param_type_enum;
typedef oal_uint8 mac_wmm_set_param_type_enum_uint8;


#define MAC_VAP_AP_STATE_BUTT       (MAC_VAP_STATE_AP_WAIT_START + 1)
#define MAC_VAP_STA_STATE_BUTT      MAC_VAP_STATE_BUTT

#define H2D_SYNC_MASK_BARK_PREAMBLE (1<<1)
#define H2D_SYNC_MASK_MIB           (1<<2)
#define H2D_SYNC_MASK_PROT          (1<<3)
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
enum
{
    FREQ_IDLE                          = 0,

    FREQ_MIDIUM                            = 1,

    FREQ_HIGHER                            = 2,

    FREQ_HIGHEST                           = 3,

    FREQ_BUTT                           = 4
};
typedef oal_uint8 oal_device_freq_type_enum_uint8;
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
/* channel�ṹ�� */
typedef struct
{
    oal_uint8                           uc_chan_number;     /* ��20MHz�ŵ��� */
    wlan_channel_band_enum_uint8        en_band;            /* Ƶ�� */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;       /* ����ģʽ */
    oal_uint8                           uc_idx;             /* �ŵ������� */
}mac_channel_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
typedef struct                          /* hi1102-cb */
{
    oal_uint8                           uc_shortgi_type;    /* shortgi 20/40/80     */
    oal_uint8                           uc_enable;          /* 1:enable; 0:disable  */
    oal_uint8                           auc_resv[2];
}shortgi_cfg_stru;
#endif
#define SHORTGI_CFG_STRU_LEN            4

typedef struct
{
    oal_uint8                            uc_announced_channel;     /* ���ŵ��� */
    wlan_channel_bandwidth_enum_uint8    en_announced_bandwidth;   /* �´���ģʽ */
    oal_uint8                            uc_ch_switch_cnt;         /* �ŵ��л����� */
    wlan_ch_switch_status_enum_uint8     en_ch_switch_status;      /* �ŵ��л�״̬ */
    wlan_bw_switch_status_enum_uint8     en_bw_switch_status;      /* �����л�״̬ */
    oal_bool_enum_uint8                  en_csa_present_in_bcn;    /* Beacon֡���Ƿ����CSA IE */

    oal_uint8                            uc_start_chan_idx;
    oal_uint8                            uc_end_chan_idx;
    wlan_channel_bandwidth_enum_uint8    en_user_pref_bandwidth;

    /* VAPΪSTAʱ�����г�Ա
     *
     *  ---|--------|--------------------|-----------------|-----------
     *     0        3                    0                 0
     *     X        A                    B                 C
     *
     *  sta���ŵ��л���ͨ����ͼ�������, ����Ϊ�л���������
     *  X->A A֮ǰΪδ���������ŵ��л�ʱ,�л�������Ϊ0
     *  ��A->Bʱ���Ϊsta�ȴ��л�״̬: en_waiting_to_shift_channelΪtrue
     *  ��B->CΪsta�ŵ��л���,���ȴ�ap��beacon״̬: en_waiting_for_apΪtrue
     *  C-> Ϊsta�յ���ap��beacon����׼�ŵ��л�����
     *
     *  A��ͨ�����յ�csa ie(beacon/action...), B��ͨ��Ϊtbtt�ж����л���������Ϊ
     *  0����csa ie�м�����Ϊ0��C����Ϊ�յ�beacon
     *
     *  ��A->C�Ĺ����У�������ظ��յ���csa ie�����ŵ��л�����
     *
     */
    //oal_bool_enum_uint8                  en_bw_change;             /* STA�Ƿ���Ҫ���д����л� */
    //oal_bool_enum_uint8                  en_waiting_for_ap;
    oal_uint8                            uc_new_channel;           /* ���Կ��Ǹ�����ϲ� */
    wlan_channel_bandwidth_enum_uint8    en_new_bandwidth;         /* ���Կ��Ǹ�����ϲ� */
    oal_uint8                            uc_new_ch_swt_cnt;        /* ���Կ��Ǹ�����ϲ� */
    oal_bool_enum_uint8                  en_waiting_to_shift_channel;  /* �ȴ��л��ŵ� */
    oal_bool_enum_uint8                  en_channel_swt_cnt_zero;

    oal_bool_enum_uint8                  en_te_b;
    oal_uint8                            bit_wait_bw_change : 4 ;        /* �յ�action֡,�ȴ��л����� */
    oal_uint8                            bit_bad_ap         : 4 ;        /* ����ʶ���ap����beacon��csa�������ŵ� */
    oal_uint8                            uc_ch_swt_start_cnt;            /* ap��һ�η��͵��л����� */
    oal_uint8                            uc_csa_rsv_cnt;                 /* ap csa ���������ļ��� */
    oal_uint8                            uc_resv[2];
    oal_uint32                           ul_chan_report_for_te_a;
}mac_ch_switch_info_stru;

typedef struct
{
    oal_uint8   uc_mac_rate; /* MAC��Ӧ���� */
    oal_uint8   uc_phy_rate; /* PHY��Ӧ���� */
    oal_uint8   uc_mbps;     /* ���� */
    oal_uint8   auc_resv[1];
}mac_data_rate_stru;

#if 0
/* add by z00241943 2014.6.13 ���ӹ���ģʽ֪ͨ��Ϣ�ṹ��,�����������������ʹ�ó������ټ��������Ĵ��룬��ʱ���� */
typedef struct
{
    oal_bool_enum_uint8  en_include_opmode_notify_ie;     /* Beacon����������֡���Ƿ����opmode_notify IE */
    oal_bool_enum_uint8  en_bf_rx_nss_change;             /* Beamforming��Rx Nss�ı� */
    oal_uint8            uc_include_ie_count;             /* Beacon����������֡�а���opmode_notify IE���� */
    oal_uint8            auc_resv[1];
}mac_opmode_notify_info_stru;

#endif

typedef struct
{
    oal_uint8           uc_rs_nrates;   /* ���ʸ��� */
    oal_uint8           auc_resv[3];
    mac_data_rate_stru  ast_rs_rates[WLAN_RATE_MAXSIZE];
}mac_rateset_stru;

typedef struct
{
    oal_uint8         uc_br_rate_num;   /* �������ʸ��� */
    oal_uint8         uc_nbr_rate_num;  /* �ǻ������ʸ��� */
    oal_uint8         uc_max_rate;      /* ���������� */
    oal_uint8         uc_min_rate;      /* ��С�������� */
    mac_rateset_stru  st_rate;
}mac_curr_rateset_stru;

/* wme���� */
typedef struct
{
    oal_uint32    ul_aifsn;          /* AIFSN parameters */
    oal_uint32    ul_logcwmin;       /* cwmin in exponential form, ��λ2^n -1 slot */
    oal_uint32    ul_logcwmax;       /* cwmax in exponential form, ��λ2^n -1 slot */
    oal_uint32    ul_txop_limit;     /* txopLimit, us */
}mac_wme_param_stru;

/* MAC vap�������Ա�ʶ */
typedef struct
{
    oal_uint32  bit_uapsd                          : 1,
                bit_txop_ps                        : 1,
                bit_wpa                            : 1,
                bit_wpa2                           : 1,
                bit_dsss_cck_mode_40mhz            : 1,                 /* �Ƿ�������40M��ʹ��DSSS/CCK, 1-����, 0-������ */
                bit_rifs_tx_on                     : 1,
                bit_tdls_prohibited                : 1,                 /* tdlsȫ�ֽ��ÿ��أ� 0-���ر�, 1-�ر� */
                bit_tdls_channel_switch_prohibited : 1,                 /* tdls�ŵ��л�ȫ�ֽ��ÿ��أ� 0-���ر�, 1-�ر� */
                bit_hide_ssid                      : 1,                 /* AP��������ssid,  0-�ر�, 1-����*/
                bit_wps                            : 1,                 /* AP WPS����:0-�ر�, 1-���� */
                bit_11ac2g                         : 1,                 /* 2.4G�µ�11ac:0-�ر�, 1-���� */
                bit_keepalive                      : 1,                 /* vap KeepAlive���ܿ���: 0-�ر�, 1-����*/
                bit_smps                           : 2,                 /* vap ��ǰSMPS���� */
                bit_dpd_enbale                     : 1,                 /* dpd�Ƿ��� */
                bit_dpd_done                       : 1,                 /* dpd�Ƿ���� */
                bit_11ntxbf                        : 1,                 /* 11n txbf���� */
                bit_disable_2ght40                 : 1,                 /* 2ght40��ֹλ��1-��ֹ��0-����ֹ */
                bit_peer_obss_scan                 : 1,                 /* �Զ�֧��obss scan����: 0-��֧��, 1-֧�� */
                bit_resv                           : 13;
}mac_cap_flag_stru;

/* VAP�շ���ͳ�� */
typedef struct
{
    /* net_device��ͳ����Ϣ, net_deviceͳ�ƾ�����̫���ı��� */
    oal_uint32  ul_rx_packets_to_lan;               /* �������̵�LAN�İ��� */
    oal_uint32  ul_rx_bytes_to_lan;                 /* �������̵�LAN���ֽ��� */
    oal_uint32  ul_rx_dropped_packets;              /* ���������ж����İ��� */
    oal_uint32  ul_rx_vap_non_up_dropped;           /* vapû��up�����İ��ĸ��� */
    oal_uint32  ul_rx_dscr_error_dropped;           /* �������������İ��ĸ��� */
    oal_uint32  ul_rx_first_dscr_excp_dropped;      /* �������װ��쳣�����İ��ĸ��� */
    oal_uint32  ul_rx_alg_filter_dropped;           /* �㷨���˶����İ��ĸ��� */
    oal_uint32  ul_rx_feature_ap_dropped;           /* AP����֡���˶������� */
    oal_uint32  ul_rx_null_frame_dropped;           /* �յ�NULL֡����Ŀ */
    oal_uint32  ul_rx_transmit_addr_checked_dropped;/* ���Ͷ˵�ַ����ʧ�ܶ��� */
    oal_uint32  ul_rx_dest_addr_checked_dropped;    /* Ŀ�ĵ�ַ����ʧ�ܶ��� */
    oal_uint32  ul_rx_multicast_dropped;            /* �鲥֡ʧ��(netbuf copyʧ��)���� */

    oal_uint32  ul_tx_packets_from_lan;             /* ��������LAN�����İ��� */
    oal_uint32  ul_tx_bytes_from_lan;               /* ��������LAN�������ֽ��� */
    oal_uint32  ul_tx_dropped_packets;              /* ���������ж����İ��� */

    /* ��������ͳ����Ϣ */

}mac_vap_stats_stru;
#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY
/* ������ */
typedef struct
{
    oal_uint8                       auc_mac_addr[OAL_MAC_ADDR_LEN];       /* mac��ַ          */
    oal_uint8                       auc_reserved[2];                      /* �ֽڶ���         */
    oal_uint32                      ul_cfg_time;                          /* �����������ʱ�� */
    oal_uint32                      ul_aging_time;                        /* �ϻ�ʱ��         */
    oal_uint32                      ul_drop_counter;                      /* ���Ķ���ͳ��     */
} mac_blacklist_stru;

/* �Զ������� */
typedef struct
{
    oal_uint8                       auc_mac_addr[OAL_MAC_ADDR_LEN];       /* mac��ַ  */
    oal_uint8                       auc_reserved[2];                      /* �ֽڶ��� */
    oal_uint32                      ul_cfg_time;                          /* ��ʼʱ�� */
    oal_uint32                      ul_asso_counter;                      /* �������� */
} mac_autoblacklist_stru;

/* �Զ���������Ϣ */
typedef struct
{
    oal_uint8                       uc_enabled;                             /* ʹ�ܱ�־ 0:δʹ��  1:ʹ�� */
    oal_uint8                       list_num;                               /* �ж��ٸ��Զ�������        */
    oal_uint8                       auc_reserved[2];                        /* �ֽڶ���                  */
    oal_uint32                      ul_threshold;                           /* ����                      */
    oal_uint32                      ul_reset_time;                          /* ����ʱ��                  */
    oal_uint32                      ul_aging_time;                          /* �ϻ�ʱ��                  */
    mac_autoblacklist_stru          ast_autoblack_list[WLAN_BLACKLIST_MAX]; /* �Զ���������              */
} mac_autoblacklist_info_stru;


/* �ڰ�������Ϣ */
typedef struct
{
    oal_uint8                          uc_mode;                                  /* �ڰ�����ģʽ   */
    oal_uint8                          uc_list_num;                              /* ������         */
    oal_uint8                          auc_reserved[2];                          /* �ֽڶ���       */
    mac_autoblacklist_info_stru        st_autoblacklist_info;                    /* �Զ���������Ϣ */
    mac_blacklist_stru                 ast_black_list[WLAN_BLACKLIST_MAX];       /* ��Ч�ڰ������� */
} mac_blacklist_info_stru;

/* ������Ϣ */
typedef struct
{
    oal_uint8                           uc_type;                                  /* ��������   */
    oal_uint8                           uc_mode;                                  /* ����ģʽbit0���㲥���� bit1���鲥���� bit2����������   */
    oal_uint8                           uc_forward;                               /* forwarding��ʽ */
    oal_uint8                           auc_reserved[1];                          /* �ֽڶ���       */
    oal_uint32                          ul_counter_bcast;                         /* �㲥��������� */
    oal_uint32                          ul_counter_mcast;                         /* �鲥��������� */
    oal_uint32                          ul_counter_ucast;                         /* ������������� */
} mac_isolation_info_stru;
#endif  /* _PRE_WLAN_FEATURE_CUSTOM_SECURITY */
typedef struct
{
    oal_uint16                          us_user_idx;
    wlan_protocol_enum_uint8            en_avail_protocol_mode; /* �û�Э��ģʽ */
    wlan_protocol_enum_uint8            en_cur_protocol_mode;
    wlan_protocol_enum_uint8            en_protocol_mode;
    oal_uint8                           auc_resv[3];
}mac_h2d_user_protocol_stru;

typedef struct
{
    oal_uint16                          us_user_idx;
    oal_uint8                           uc_arg1;
    oal_uint8                           uc_arg2;

    /* Э��ģʽ��Ϣ */
    wlan_protocol_enum_uint8            en_cur_protocol_mode;
    wlan_protocol_enum_uint8            en_protocol_mode;
    oal_uint8                           en_avail_protocol_mode; /* �û���VAPЭ��ģʽ����, ���㷨���� */

    wlan_bw_cap_enum_uint8              en_bandwidth_cap;       /* �û�����������Ϣ */
    wlan_bw_cap_enum_uint8              en_avail_bandwidth;     /* �û���VAP������������,���㷨���� */
    wlan_bw_cap_enum_uint8              en_cur_bandwidth;       /* Ĭ��ֵ��en_avail_bandwidth��ͬ,���㷨�����޸� */

    oal_bool_enum_uint8                 en_user_pmf;
    mac_user_asoc_state_enum_uint8      en_user_asoc_state;     /* �û�����״̬ */
}mac_h2d_usr_info_stru;


typedef struct
{
    mac_user_cap_info_stru              st_user_cap_info;                   /* �û�������Ϣ */
    oal_uint16                          us_user_idx;
    oal_uint8                           auc_resv[2];
}mac_h2d_usr_cap_stru;


/* ���ⵥDTS2015033104278: hamc��dmacͬ�����ʼ�����Ϣʱ��
   ʹ�õĽṹ���С�������¼��ڴ�Ĵ�С�������¼�ͬ���п���ʧ�ܡ�
   ��������ṹ��mac_h2d_user_rate_info_stru,��֤mac_h2d_usr_info_stru���������� */
typedef struct
{
    oal_uint16                          us_user_idx;

    /* vht���ʼ���Ϣ */
    mac_vht_hdl_stru                    st_vht_hdl;

    /* ht���ʼ���Ϣ */
    mac_user_ht_hdl_stru                 st_ht_hdl;

    /* legacy���ʼ���Ϣ */
    oal_uint8                           uc_avail_rs_nrates;
    oal_uint8                           auc_avail_rs_rates[WLAN_RATE_MAXSIZE];

    wlan_protocol_enum_uint8            en_protocol_mode;                            /* �û�Э��ģʽ */
}mac_h2d_usr_rate_info_stru;


typedef struct
{
    oal_uint16                         us_sta_aid;
    oal_uint8                          uc_uapsd_cap;
    oal_uint8                          auc_resv[1];
}mac_h2d_vap_info_stru;

typedef struct
{
    oal_uint16                          us_user_idx;
    wlan_protocol_enum_uint8            en_avail_protocol_mode; /* �û�Э��ģʽ */
    wlan_bw_cap_enum_uint8              en_bandwidth_cap;       /* �û�����������Ϣ */
    wlan_bw_cap_enum_uint8              en_avail_bandwidth;     /* �û���VAP������������,���㷨���� */
    wlan_bw_cap_enum_uint8              en_cur_bandwidth;       /* Ĭ��ֵ��en_avail_bandwidth��ͬ,���㷨�����޸� */
    oal_uint8                           auc_rsv[2];
}mac_h2d_user_bandwidth_stru;

typedef struct
{
    mac_channel_stru                    st_channel;
    oal_uint16                          us_user_idx;
    wlan_bw_cap_enum_uint8              en_bandwidth_cap;       /* �û�����������Ϣ */
    wlan_bw_cap_enum_uint8              en_avail_bandwidth;     /* �û���VAP������������,���㷨���� */
    wlan_bw_cap_enum_uint8              en_cur_bandwidth;       /* Ĭ��ֵ��en_avail_bandwidth��ͬ,���㷨�����޸� */
    oal_uint8                           auc_rsv[3];
}mac_d2h_syn_info_stru;

typedef struct
{
    oal_uint16                          us_user_idx;
    mac_user_asoc_state_enum_uint8      en_asoc_state;
    oal_uint8                           uc_rsv[1];
}mac_h2d_user_asoc_state_stru;


typedef struct
{
    oal_uint8 auc_addr[WLAN_MAC_ADDR_LEN];
    oal_uint8 auc_pmkid[WLAN_PMKID_LEN];
    oal_uint8 auc_resv0[2];
} mac_pmkid_info_stu;

typedef struct
{
    oal_uint8       uc_num_elems;
    oal_uint8       auc_resv0[3];
    mac_pmkid_info_stu ast_elem[WLAN_PMKID_CACHE_SIZE];
} mac_pmkid_cache_stru;

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
enum
{
    FREQ_SET_MODE                        = 0,
    /* sync ini data */
    FREQ_SYNC_DATA                       = 1,
    /* for device debug */
    FREQ_SET_FREQ                        = 2,
    FREQ_GET_FREQ                        = 4,
    FREQ_SET_BUTT
};
typedef oal_uint8 oal_freq_sync_enum_uint8;

typedef struct {
    oal_uint32  ul_speed_level;    /*����������*/
    oal_uint32  ul_cpu_freq_level;  /*CPUƵ��level*/
} device_level_stru;

typedef struct
{
    oal_uint8                uc_set_type;
    oal_uint8                uc_set_freq;
    oal_uint8                uc_device_freq_enable;
    oal_uint8                uc_resv;
    device_level_stru        st_device_data[4];
}config_device_freq_h2d_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_TXBF
typedef struct
{
    oal_uint8   bit_imbf_receive_cap            :   1,  /*��ʽTxBf��������*/
                bit_exp_comp_txbf_cap           :   1, /*Ӧ��ѹ���������TxBf������*/
                bit_min_grouping                :   2,  /*0=�����飬1=1,2���飬2=1,4���飬3=1,2,4����*/
                bit_csi_bfee_max_rows           :   2,  /*bfer֧�ֵ�����bfee��CSI��ʾ�������������*/
                bit_channel_est_cap             :   2;  /*�ŵ����Ƶ�������0=1��ʱ�������ε���*/
    oal_uint8   auc_resv0[3];
}mac_vap_txbf_add_stru;
#endif

typedef struct
{
    /*word 0*/
    wlan_prot_mode_enum_uint8           en_protection_mode;                              /* ����ģʽ */
    oal_uint8                           uc_obss_non_erp_aging_cnt;                       /*ָʾOBSS��non erp վ����ϻ�ʱ��*/
    oal_uint8                           uc_obss_non_ht_aging_cnt;                        /*ָʾOBSS��non ht վ����ϻ�ʱ��*/
    oal_uint8                           bit_auto_protection        : 1;                  /*ָʾ���������Ƿ�����OAL_SWITCH_ON �򿪣� OAL_SWITCH_OFF �ر�*/
    oal_uint8                           bit_obss_non_erp_present   : 1;                  /*ָʾobss���Ƿ����non ERP��վ��*/
    oal_uint8                           bit_obss_non_ht_present    : 1;                  /*ָʾobss���Ƿ����non HT��վ��*/
    oal_uint8                           bit_rts_cts_protect_mode   : 1;                  /*ָrts_cts ���������Ƿ��, OAL_SWITCH_ON �򿪣� OAL_SWITCH_OFF �ر�*/
    oal_uint8                           bit_lsig_txop_protect_mode : 1;                  /*ָʾL-SIG protect�Ƿ��, OAL_SWITCH_ON �򿪣� OAL_SWITCH_OFF �ر�*/
    oal_uint8                           bit_reserved               : 3;

    /*word 1*/
    oal_uint8                           uc_sta_no_short_slot_num;                       /* ��֧��short slot��STA����*/
    oal_uint8                           uc_sta_no_short_preamble_num;                   /* ��֧��short preamble��STA����*/
    oal_uint8                           uc_sta_non_erp_num;                             /* ��֧��ERP��STA����*/
    oal_uint8                           uc_sta_non_ht_num;                              /* ��֧��HT��STA���� */
    /*word 2*/
    oal_uint8                           uc_sta_non_gf_num;                              /* ֧��ERP/HT,��֧��GF��STA���� */
    oal_uint8                           uc_sta_20M_only_num;                            /* ֻ֧��20M Ƶ�ε�STA����*/
    oal_uint8                           uc_sta_no_40dsss_cck_num;                       /* ����40M DSSS-CCK STA����  */
    oal_uint8                           uc_sta_no_lsig_txop_num;                        /* ��֧��L-SIG TXOP Protection STA���� */
} mac_protection_stru;

/*����ͬ��������صĲ���*/
typedef struct
{
    oal_uint32             ul_sync_mask;

    mac_user_cap_info_stru st_user_cap_info;
    oal_uint16             us_user_idx;
    oal_uint8              auc_resv[2];

    wlan_mib_ht_protection_enum_uint8   en_dot11HTProtection;
    oal_bool_enum_uint8 en_dot11RIFSMode;
    oal_bool_enum_uint8 en_dot11LSIGTXOPFullProtectionActivated;
    oal_bool_enum_uint8 en_dot11NonGFEntitiesPresent;

    mac_protection_stru st_protection;
}mac_h2d_protection_stru;

typedef struct
{
    oal_uint8                          *puc_ie;                                         /* APP ��ϢԪ�� */
    oal_uint32                          ul_ie_len;                                      /* APP ��ϢԪ�س��� */
    oal_uint32                          ul_ie_max_len;                                  /* APP ��ϢԪ����󳤶� */
} mac_app_ie_stru;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
typedef enum
{
    PSTA_MODE_NONE = 0,
    PSTA_MODE_MSTA,
    PSTA_MODE_VSTA,
    PSTA_MODE_PBSS,
}psta_mode_enum;
typedef oal_uint8 psta_mode_enum_uint8;

typedef struct
{
    psta_mode_enum_uint8      en_psta_mode;
    oal_uint8                 auc_res[3];
}mac_vap_psta_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    mac_ether_header_stru               st_eth_hdr;
    oal_uint8                           auc_rsv[2];
    oal_uint16                          us_proxy_num; /* ��¼�����֡������ */
    oal_uint16                          us_type;
    oal_err_code_enum_uint32            en_rst;
}mac_vap_proxyarp_debug_stru;
#endif

typedef struct
{
    oal_dlist_head_stru                 ast_ipv4_head[MAC_VAP_USER_HASH_MAX_VALUE];
    oal_dlist_head_stru                 ast_ipv6_head[MAC_VAP_USER_HASH_MAX_VALUE];
    oal_bool_enum_uint8                 en_is_proxyarp;
    oal_uint8                           uc_ipv4_num;        /* ��¼ipv4������ */
    oal_uint8                           uc_ipv6_num;        /* ��¼ipv6������ */
    oal_bool_enum_uint8                 en_2wlan;

#ifdef _PRE_DEBUG_MODE
    /* ����ʹ��,����¼MAC_VAP_USER_HASH_MAX_VALUE����¼ */
    oal_uint16                          us_idx_cur; /* ѭ��ָ��ǰ��¼��λ�� */
    oal_uint8                           auc_rsv[2];
    mac_vap_proxyarp_debug_stru         ast_vap_proxyarp_dbg[MAC_VAP_USER_HASH_MAX_VALUE];
#endif
}mac_vap_proxyarp_stru;
#endif


/* Э����� ��Ӧcfgid: WLAN_CFGID_MODE */
typedef struct
{
    wlan_protocol_enum_uint8            en_protocol;    /* Э�� */
    wlan_channel_band_enum_uint8        en_band;        /* Ƶ�� */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;   /* ���� */
    oal_uint8                           en_channel_idx; /* ��20M�ŵ��� */
}mac_cfg_mode_param_stru;

#ifdef _PRE_WLAN_DFT_STAT
typedef oam_stats_vap_stat_stru mac_vap_dft_stats_stru;

typedef struct
{
    mac_vap_dft_stats_stru             *pst_vap_dft_stats;
    frw_timeout_stru                    st_vap_dft_timer;
    oal_uint32                          ul_flg;             /* ��ʼͳ�Ʊ�־ */


}mac_vap_dft_stru;
#endif

typedef struct
{
    oal_uint8    flags;
    oal_uint8    mcs;
    oal_uint16   legacy;
    oal_uint8    nss;
    oal_uint8    bw;
    oal_uint8    rsv[3];
} mac_rate_info_stru;

typedef enum mac_rate_info_flags {
    MAC_RATE_INFO_FLAGS_MCS             = BIT(0),
    MAC_RATE_INFO_FLAGS_VHT_MCS         = BIT(1),
    MAC_RATE_INFO_FLAGS_40_MHZ_WIDTH    = BIT(2),
    MAC_RATE_INFO_FLAGS_80_MHZ_WIDTH    = BIT(3),
    MAC_RATE_INFO_FLAGS_80P80_MHZ_WIDTH = BIT(4),
    MAC_RATE_INFO_FLAGS_160_MHZ_WIDTH   = BIT(5),
    MAC_RATE_INFO_FLAGS_SHORT_GI        = BIT(6),
    MAC_RATE_INFO_FLAGS_60G             = BIT(7),
} mac_rate_info_flags;


#ifdef _PRE_WLAN_FEATURE_STA_PM
/* STA UAPSD �������� */
typedef	 struct
{
	oal_uint8		uc_max_sp_len;
	oal_uint8		uc_delivery_enabled[WLAN_WME_AC_BUTT];
	oal_uint8	    uc_trigger_enabled[WLAN_WME_AC_BUTT];
}mac_cfg_uapsd_sta_stru;

/* Power save modes specified by the user */
typedef enum
{
    NO_POWERSAVE     = 0,
    MIN_FAST_PS      = 1,
    MAX_FAST_PS      = 2,
    MIN_PSPOLL_PS    = 3,
    MAX_PSPOLL_PS    = 4,
    NUM_PS_MODE      = 5
} ps_user_mode_enum;

#endif

#ifdef _PRE_WLAN_FEATURE_TXOPPS
/* STA txopps aidͬ�� */
typedef	 struct
{
    oal_uint16                           us_partial_aid;
    oal_uint8                            en_protocol;
    oal_uint8                            uc_resv;
}mac_cfg_txop_sta_stru;
#endif

#ifdef _PRE_WLAN_FEATURE_VOWIFI
/* vowifi��������������������� */
typedef enum
{
    VOWIFI_SET_MODE = 0,
    VOWIFI_GET_MODE,
    VOWIFI_SET_PERIOD,
    VOWIFI_GET_PERIOD,
    VOWIFI_SET_LOW_THRESHOLD,
    VOWIFI_GET_LOW_THRESHOLD,
    VOWIFI_SET_HIGH_THRESHOLD,
    VOWIFI_GET_HIGH_THRESHOLD,
    VOWIFI_SET_TRIGGER_COUNT,
    VOWIFI_GET_TRIGGER_COUNT,
    VOWIFI_SET_IS_SUPPORT,

    VOWIFI_CMD_BUTT
}mac_vowifi_cmd_enum;
typedef oal_uint8 mac_vowifi_cmd_enum_uint8;

/* vowifi��������������������ṹ�� */
typedef struct
{
    mac_vowifi_cmd_enum_uint8   en_vowifi_cfg_cmd; /* �������� */
    oal_uint8                   uc_value;          /* ����ֵ */
    oal_uint8                   auc_resv[2];
}mac_cfg_vowifi_stru;


/* VoWiFi�ź��������� �� ���ò����ṹ�� */
typedef enum
{
    VOWIFI_DISABLE_REPORT   = 0,
    VOWIFI_LOW_THRES_REPORT,
    VOWIFI_HIGH_THRES_REPORT,

    VOWIFI_MODE_BUTT
} mac_vowifi_mode;
typedef oal_uint8 mac_vowifi_mode_enum_uint8;

typedef struct
{
/*  MODE
	0: disable report of rssi change
	1: enable report when rssi lower than threshold(vowifi_low_thres)
	2: enable report when rssi higher than threshold(vowifi_high_thres)
*/
    mac_vowifi_mode_enum_uint8  en_vowifi_mode;
    oal_uint8                   uc_trigger_count_thres;   /*��1��100��, the continuous counters of lower or higher than threshold which will trigger the report to host */
    oal_int8                    c_rssi_low_thres;         /* [-1, -100],vowifi_low_thres */
    oal_int8                    c_rssi_high_thres;        /* [-1, -100],vowifi_high_thres */
    oal_uint16                  us_rssi_period_ms;        /* ��λms, ��Χ��1s��30s��, the period of monitor the RSSI when host suspended */

    oal_bool_enum_uint8         en_vowifi_reported;       /* ���vowifi�Ƿ��ϱ���һ��"״̬�л�����"���������ϱ� */
    oal_uint8                   uc_cfg_cmd_cnt;           /* �ϲ��·�������vowifi�����Ĵ���ͳ�ƣ����ڱ���Ƿ����ײ������·���ȫ����ֹ�·��������̺�vowifi�����ϱ������ص� */
}mac_vowifi_param_stru;

#endif /* _PRE_WLAN_FEATURE_VOWIFI */

#define MAC_VAP_INVAILD    (0x0) /*0Ϊvap��Ч*/
#define MAC_VAP_VAILD      (0x2b)

/* VAP�����ݽṹ */
typedef struct
{
    /* VAPΪAP����STA���г�Ա */
    /* word0~word1 */
    oal_uint8                           uc_vap_id;                                      /* vap ID   *//* ����Դ������ֵ */
    oal_uint8                           uc_device_id;                                   /* �豸ID   */
    oal_uint8                           uc_chip_id;                                     /* chip ID  */
    wlan_vap_mode_enum_uint8            en_vap_mode;                                    /* vapģʽ  */
    oal_uint32                          ul_core_id;

    /* word2~word3 */
    oal_uint8                           auc_bssid[WLAN_MAC_ADDR_LEN];                   /* BSSID����MAC��ַ��MAC��ַ��mib�е�auc_dot11StationID  */
    mac_vap_state_enum_uint8            en_vap_state;                                   /* VAP״̬ */
    wlan_protocol_enum_uint8            en_protocol;                                    /* ������Э��ģʽ */

    /* word4~word5 */
    mac_channel_stru                    st_channel;                                     /* vap���ڵ��ŵ� */
    mac_ch_switch_info_stru             st_ch_switch_info;

    /* word6 */
    oal_uint8                           bit_has_user_bw_limit   :   1;                  /* ��vap�Ƿ����user���� */
    oal_uint8                           bit_vap_bw_limit        :   1;                  /* ��vap�Ƿ������� */
    oal_uint8                           bit_voice_aggr          :   1;                  /* ��vap�Ƿ����VOҵ��֧�־ۺ� */
    oal_uint8                           bit_one_tx_tcp_be       :   1;                  /* ��vap�Ƿ�ֻ��1·����TCP BEҵ�� */
    oal_uint8                           bit_resv                :   4;

    oal_uint8                           uc_tx_power;                                    /* ���书��, ��λdBm */
    oal_uint8                           uc_channel_utilization;                         /* ��ǰ�ŵ������� */
    oal_uint8                           uc_wmm_params_update_count;                     /* ��ʼΪ0��APģʽ�£�ÿ����һ��wmm�������������1,��beacon֡��assoc rsp�л���д��4bit�����ܳ���15��STAģʽ�½���֡���������ֵ */

    /* word7 */
    oal_uint16                          us_user_nums;                                   /* VAP���ѹҽӵ��û����� */
    oal_uint16                          us_multi_user_idx;                              /* �鲥�û�ID */
    oal_uint8                           auc_cache_user_mac_addr[WLAN_MAC_ADDR_LEN];     /* cache user��Ӧ��MAC��ַ */
    oal_uint16                          us_cache_user_id;                               /* cache user��Ӧ��userID*/
    oal_dlist_head_stru                 ast_user_hash[MAC_VAP_USER_HASH_MAX_VALUE];     /* hash����,ʹ��HASH�ṹ�ڵ�DLIST */
    oal_dlist_head_stru                 st_mac_user_list_head;                          /* �����û��ڵ�˫������,ʹ��USER�ṹ�ڵ�DLIST */

    /* word8 */
    wlan_nss_enum_uint8                 en_vap_rx_nss;                                  /* vap�Ľ��տռ������� */

    /* word9 ���ӵ�SPE �˿ں�,һ��VAP��Ӧһ���˿ں� */
#if (defined(CONFIG_BALONG_SPE) && defined(_PRE_WLAN_SPE_SUPPORT))
    oal_uint32                          ul_spe_portnum;                                 /* ���ڱ���netdev��ʼ����spe�˿� */
#endif

    /*vapΪ��̬��Դ�����VAP��û�б����롣,
      DMAC OFFLOADģʽVAP��ɾ������˻����֡*/
    oal_uint8                           uc_init_flag;
    oal_uint8                           auc_resv1[2];

    /* ������� */
    /*�ṹ����Ҫ��֤4�ֽڶ���*/
    //mac_key_mgmt_stru                   st_key_mgmt;                                    /*���ڱ�������ptk gtk����Կ��Ϣ����AP/STAģʽ�¾���Ҫʹ��*/

    mac_cap_flag_stru                   st_cap_flag;                                    /* vap�������Ա�ʶ */
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    mac_vap_stats_stru                  st_vap_stats;                                   /* VAP�շ���ͳ�� */
#endif
    wlan_mib_ieee802dot11_stru         *pst_mib_info;                                   /* mib��Ϣ(��ʱ����vapʱ������ֱ�ӽ�ָ��ֵΪNULL����ʡ�ռ�)  */

    mac_curr_rateset_stru               st_curr_sup_rates;                              /* ��ǰ֧�ֵ����ʼ� */
    mac_curr_rateset_stru               ast_sta_sup_rates_ie[WLAN_BAND_BUTT];           /* ֻ��staȫ�ŵ�ɨ��ʱʹ�ã�������д֧�ֵ����ʼ�ie����2.4��5G */


#ifdef _PRE_WLAN_DFT_STAT
    /* user ����ά�� */
    oal_uint32          ul_dlist_cnt;     /* dlsitͳ�� */
    oal_uint32          ul_hash_cnt;     /* hash����ͳ�� */
#if 0
    mac_vap_dft_stru                    st_vap_dft;                                     /* vap����ͳ����Ϣ��ά���� */
#endif

#endif

#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_vap_txbf_add_stru               st_txbf_add_cap;
#endif

    /* VAPΪAP����STA���г�Ա �������*/


    /* VAPΪAP���г�Ա�� ���忪ʼ*/
    mac_protection_stru                 st_protection;                                   /*�뱣����ر���*/
    mac_app_ie_stru                     ast_app_ie[OAL_APP_IE_NUM];
    /* VAPΪAP�ض���Ա�� �������*/

    /* VAPΪSTA���г�Ա�� ���忪ʼ*/

    oal_uint16                          us_sta_aid;                                     /* VAPΪSTAģʽʱ����AP�����STA��AID(����Ӧ֡��ȡ),ȡֵ��Χ1~2007; VAPΪAPģʽʱ�����ô˳�Ա���� */
    oal_uint8                           uc_assoc_vap_id;                                /* VAPΪSTAģʽʱ����user(ap)����Դ��������VAPΪAPģʽʱ�����ô˳�Ա���� */
    oal_uint8                           uc_wmm_cap;                                     /* ������STA������AP�Ƿ�֧��wmm������Ϣ */

    oal_uint8                           uc_uapsd_cap;                                   /* ������STA������AP�Ƿ�֧��uapsd������Ϣ */
    oal_uint16                          us_assoc_user_cap_info;                         /* staҪ�������û���������Ϣ */
    oal_uint8                           bit_ap_11ntxbf              : 1,                /* staҪ�������û���11n txbf������Ϣ */
                                        bit_resv7                   : 7;
    /* VAPΪSTA�ض���Ա�� �������*/

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_vap_psta_stru                   st_psta;                                /* Proxy STA ������ؽṹ�� */
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
    mac_vap_proxyarp_stru              *pst_vap_proxyarp;
#endif

//#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    /* ��������ʹ�� */
    oal_uint8                           bit_al_tx_flag  :1;                             /* ������־ */
    oal_uint8                           bit_payload_flag:2;                             /* payload����:0:ȫ0  1:ȫ1  2:random */
    oal_uint8                           bit_first_run:1;                                /* �����ر��ٴδ򿪱�־ */
    oal_uint8                           bit_reserved:4;
    //oal_uint8                           auc_resv5[3];
//#endif

//#ifdef _PRE_WLAN_FEATURE_P2P
    wlan_p2p_mode_enum_uint8            en_p2p_mode;                                    /* 0:��P2P�豸; 1:P2P_GO; 2:P2P_Device; 3:P2P_CL */
    oal_uint8                           uc_p2p_gocl_hal_vap_id;                         /* p2p go / cl��hal vap id */
    oal_uint8                           uc_p2p_listen_channel;                          /* P2P Listen channel */
    //oal_uint8                           auc_resv6[1];
//#endif    /* _PRE_WLAN_FEATURE_P2P */

#ifdef _PRE_WLAN_FEATURE_STA_PM
    mac_cfg_uapsd_sta_stru				st_sta_uapsd_cfg;     /* UAPSD��������Ϣ */
#endif

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    oal_bool_enum_uint8                 en_user_pmf_cap;      /* STA����δ����userǰ���洢Ŀ��user��pmfʹ����Ϣ */
#endif

    oal_spin_lock_stru                  st_cache_user_lock;                        /* cache_user lock */
#ifdef _PRE_WLAN_FEATURE_VOWIFI
    mac_vowifi_param_stru               *pst_vowifi_cfg_param;  /* �ϲ��·���"VoWiFi�ź���������"�����ṹ�� */
#endif /* _PRE_WLAN_FEATURE_VOWIFI */
}mac_vap_stru;

/* cfg id��Ӧ��get set���� */
typedef struct
{
    wlan_cfgid_enum_uint16          en_cfgid;
    oal_uint8                       auc_resv[2];    /* �ֽڶ��� */
    oal_uint32                      (*p_get_func)(mac_vap_stru *pst_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
    oal_uint32                      (*p_set_func)(mac_vap_stru *pst_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
}mac_cfgid_stru;


/* cfg id��Ӧ�Ĳ����ṹ�� */
/* ����VAP�����ṹ��, ��Ӧcfgid: WLAN_CFGID_ADD_VAP */
typedef struct
{
    wlan_vap_mode_enum_uint8  en_vap_mode;
    oal_uint8                 uc_cfg_vap_indx;
    oal_uint16                us_muti_user_id;          /* ���vap ��Ӧ��muti user index */

    oal_uint8                 uc_vap_id;                /* ��Ҫ��ӵ�vap id */
    wlan_p2p_mode_enum_uint8  en_p2p_mode;              /* 0:��P2P�豸; 1:P2P_GO; 2:P2P_Device; 3:P2P_CL */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    psta_mode_enum_uint8      en_psta_mode;
    oal_uint8                 uc_rep_id;
#else
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    oal_uint8                 bit_11ac2g_enable         :1;
    oal_uint8                 bit_disable_capab_2ght40  :1;
    oal_uint8                 bit_reserve               :6;
    oal_uint8                 auc_resv0[1];
#else
    oal_uint8                 auc_resv0[2];
#endif
#endif
#ifdef _PRE_WLAN_FEATURE_UAPSD
    oal_uint8                 bit_uapsd_enable    :1;
    oal_uint8                 bit_reserve1        :7;
    oal_uint8                 auc_resv1[3];
#endif
    oal_net_device_stru      *pst_net_dev;
}mac_cfg_add_vap_param_stru;

typedef mac_cfg_add_vap_param_stru mac_cfg_del_vap_param_stru;

/* ����VAP�����ṹ�� ��Ӧcfgid: WLAN_CFGID_START_VAP */
typedef struct
{
    oal_bool_enum_uint8         en_mgmt_rate_init_flag;              /* start vapʱ�򣬹���֡�����Ƿ���Ҫ��ʼ�� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8            uc_protocol;
    oal_uint8            uc_band;
    oal_uint8            uc_bandwidth;
#else
    oal_uint8            auc_resv1[3];
#endif
#ifdef _PRE_WLAN_FEATURE_P2P
    wlan_p2p_mode_enum_uint8   en_p2p_mode;
    oal_uint8                  auc_resv2[3];
#endif
    oal_net_device_stru       *pst_net_dev;     /* �˳�Ա����Host(WAL&HMAC)ʹ�ã�Device��(DMAC&ALG&HAL��)��ʹ�� */
}mac_cfg_start_vap_param_stru;
typedef mac_cfg_start_vap_param_stru mac_cfg_down_vap_param_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* CFG VAP h2d */
typedef struct
{
    oal_net_device_stru        *pst_net_dev;
}mac_cfg_vap_h2d_stru;
#endif


/* ����mac��ַ���� ��Ӧcfgid: WLAN_CFGID_STATION_ID */
typedef struct
{
    oal_uint8                   auc_station_id[WLAN_MAC_ADDR_LEN];
    wlan_p2p_mode_enum_uint8    en_p2p_mode;
    oal_uint8                   auc_resv[1];
}mac_cfg_staion_id_param_stru;

/* SSID���� ��Ӧcfgid: WLAN_CFGID_SSID */
typedef struct
{
    oal_uint8   uc_ssid_len;
    oal_uint8   auc_resv[2];
    oal_int8    ac_ssid[WLAN_SSID_MAX_LEN];
}mac_cfg_ssid_param_stru;

/* HOSTAPD ���ù���Ƶ�Σ��ŵ��ʹ������ */
typedef struct
{
    wlan_channel_band_enum_uint8        en_band;        /* Ƶ�� */
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;   /* ���� */
    oal_uint8                           uc_channel;     /* �ŵ���� */
    oal_uint8                           auc_resv[1];    /* ����λ */
}mac_cfg_channel_param_stru;

/* HOSTAPD ����wiphy �����豸��Ϣ������RTS ����ֵ����Ƭ��������ֵ */
typedef struct
{
    oal_uint8  uc_frag_threshold_changed;
    oal_uint8  uc_rts_threshold_changed;
    oal_uint8  uc_rsv[2];
    oal_uint32 ul_frag_threshold;
    oal_uint32 ul_rts_threshold;
}mac_cfg_wiphy_param_stru;

/* HOSTAPD ���� Beacon ��Ϣ */
typedef struct
{
    oal_int32                l_interval;                            /* beacon interval */
    oal_int32                l_dtim_period;                         /* DTIM period     */
    oal_bool_enum_uint8      en_privacy;
    oal_uint8                uc_crypto_mode;                              /* WPA/WPA2 */
    oal_uint8                uc_group_crypto;                             /* �鲥��Կ���� */
    oal_bool_enum_uint8      uc_hidden_ssid;
    oal_uint8                auc_auth_type[MAC_AUTHENTICATION_SUITE_NUM];  /* akm ���� */
    oal_uint8                auc_pairwise_crypto_wpa[MAC_PAIRWISE_CIPHER_SUITES_NUM];
    oal_uint8                auc_pairwise_crypto_wpa2[MAC_PAIRWISE_CIPHER_SUITES_NUM];
    oal_uint16               us_rsn_capability;
    oal_bool_enum_uint8      en_shortgi_20;
    oal_bool_enum_uint8      en_shortgi_40;
    oal_bool_enum_uint8      en_shortgi_80;
    wlan_protocol_enum_uint8 en_protocol;

    oal_uint8                       uc_smps_mode;
    mac_beacon_operation_type_uint8 en_operation_type;
    oal_uint8                auc_resv1[2];
}mac_beacon_param_stru;


/* ����logģ�鿪�ص������������ */
typedef struct
{
    oam_module_id_enum_uint16           en_mod_id;      /* ��Ӧ��ģ��id */
    oal_bool_enum_uint8                 en_switch;      /* ��Ӧ�Ŀ������� */
    oal_uint8                           auc_resv[1];
}mac_cfg_log_module_param_stru;

/* �û���ص������������ */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_bool_enum_uint8     en_ht_cap;                          /* ht���� */
    oal_uint8               auc_resv[3];
    oal_uint16              us_user_idx;                        /* �û����� */
}mac_cfg_add_user_param_stru;

typedef mac_cfg_add_user_param_stru mac_cfg_del_user_param_stru;

/* ����֡��FCSͳ����Ϣ */
typedef struct
{
    oal_uint32  ul_data_op;         /* ���ݲ���ģʽ:<0>����,<1>��� */
    oal_uint32  ul_print_info;      /* ��ӡ��������:<0>�������� <1>��֡�� <2>self fcs correct, <3>other fcs correct, <4>fcs error  */
}mac_cfg_rx_fcs_info_stru;

/* �޳��û������������ */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint16              us_reason_code;                     /* ȥ���� reason code */
#ifdef _PRE_WLAN_FEATURE_HILINK
    oal_uint8               uc_rej_user;                        /* ��ֹsta���� */
    oal_uint8               uc_kick_user;                       /* ����:����/��ֹ���� */
    oal_uint8               auc_rsv[2];
#endif
}mac_cfg_kick_user_param_stru;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/* ����Proxy STA OMA����������� */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* Proxy STA OMA��ַ */
    oal_uint8               auc_resv[2];
}mac_cfg_set_oma_param_stru;

#endif

/* ��ͣtid����������� */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8               uc_tid;
    oal_uint8               uc_is_paused;
}mac_cfg_pause_tid_param_stru;

/* �����û��Ƿ�Ϊvip */
typedef struct
{
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8               uc_vip_flag;
}mac_cfg_user_vip_param_stru;

/* ��ͣtid����������� */
typedef struct
{
    oal_uint8               uc_aggr_tx_on;
    oal_uint8               uc_tid;
    oal_uint16              us_packet_len;
}mac_cfg_ampdu_tx_on_param_stru;

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
/* ����hostĳ�����е�ÿ�ε��ȱ��ĸ�����low_waterline, high_waterline */
typedef struct
{
    oal_uint8               uc_queue_type;
    oal_uint8               auc_resv[1];
    oal_uint16              us_burst_limit;
    oal_uint16              us_low_waterline;
    oal_uint16              us_high_waterline;
}mac_cfg_flowctl_param_stru;
#endif

/* ʹ��qempty���� */
typedef struct
{
    oal_uint8   uc_is_on;
    oal_uint8   auc_resv[3];
}mac_cfg_resume_qempty_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/* ʹ��rx intr fifo���� */
typedef struct
{
    oal_uint8   uc_is_on;
    oal_uint8   auc_resv[3];
}mac_cfg_resume_rx_intr_fifo_stru;
#endif

/* ����mpdu/ampdu�������  */
typedef struct
{
    oal_uint8               uc_tid;
    oal_uint8               uc_packet_num;
    oal_uint16              us_packet_len;
    oal_uint8               auc_ra_mac[OAL_MAC_ADDR_LEN];
}mac_cfg_mpdu_ampdu_tx_param_stru;
/* AMPDU��ص������������ */
typedef struct
{
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* �û���MAC ADDR */
    oal_uint8                       uc_tidno;                           /* ��Ӧ��tid�� */
    oal_uint8                       auc_reserve[1];                      /* ȷ�ϲ��� */
}mac_cfg_ampdu_start_param_stru;

typedef mac_cfg_ampdu_start_param_stru mac_cfg_ampdu_end_param_stru;

/* BA�Ự��ص������������ */
typedef struct
{
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* �û���MAC ADDR */
    oal_uint8                       uc_tidno;                           /* ��Ӧ��tid�� */
    mac_ba_policy_enum_uint8        en_ba_policy;                       /* BAȷ�ϲ��� */
    oal_uint16                      us_buff_size;                       /* BA���ڵĴ�С */
    oal_uint16                      us_timeout;                         /* BA�Ự�ĳ�ʱʱ�� */
}mac_cfg_addba_req_param_stru;

typedef struct
{
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* �û���MAC ADDR */
    oal_uint8                       uc_tidno;                           /* ��Ӧ��tid�� */
    mac_delba_initiator_enum_uint8  en_direction;                       /* ɾ��ba�Ự�ķ���� */
    oal_uint8                       auc_reserve[1];                     /* ɾ��ԭ�� */
}mac_cfg_delba_req_param_stru;

#ifdef _PRE_WLAN_FEATURE_WMMAC
/*TSPEC��ص������������*/
typedef struct
{
    mac_ts_info_stru  ts_info;
    oal_uint8         uc_rsvd;
    oal_uint16        us_norminal_msdu_size;
    oal_uint16        us_max_msdu_size;
    oal_uint32        ul_min_data_rate;
    oal_uint32        ul_mean_data_rate;
    oal_uint32        ul_peak_data_rate;
    oal_uint32        ul_min_phy_rate;
    oal_uint16        us_surplus_bw;
    oal_uint16        us_medium_time;
}mac_cfg_wmm_tspec_stru_param_stru;
#endif


typedef struct
{
    oal_uint8                           auc_mac_addr[6];
    oal_uint8                           uc_amsdu_max_num;   /* amsdu������ */
    oal_uint8                           auc_reserve[3];
    oal_uint16                          us_amsdu_max_size;  /* amsdu��󳤶� */

}mac_cfg_amsdu_start_param_stru;

/* �����û����ò��� */
typedef struct
{
    oal_uint8                               uc_function_index;
    oal_uint8                               auc_reserve[2];
    mac_vap_config_dscr_frame_type_uint8    en_type;       /* ���õ�֡���� */
    oal_int32                               l_value;
}mac_cfg_set_dscr_param_stru;

typedef struct
{
    mac_vap_stru                *pst_mac_vap;
    oal_int8                     pc_param[4];      /* ��ѯ��������Ϣ */
}mac_cfg_event_stru;

/* non-HTЭ��ģʽ���������ýṹ�� */
typedef struct
{
    wlan_legacy_rate_value_enum_uint8       en_rate;            /* ����ֵ */
    wlan_phy_protocol_enum_uint8            en_protocol_mode;   /* ��Ӧ��Э�� */
    oal_uint8                               auc_reserve[2];     /* ���� */
}mac_cfg_non_ht_rate_stru;

/* ���÷����������ڲ�Ԫ�ؽṹ�� */
typedef enum
{
    RF_PAYLOAD_ALL_ZERO = 0,
    RF_PAYLOAD_ALL_ONE,
    RF_PAYLOAD_RAND,
    RF_PAYLOAD_BUTT
}mac_rf_payload_enum;
typedef oal_uint8 mac_rf_payload_enum_uint8;

typedef struct
{
    oal_uint8                        uc_param;      /* ��ѯ��������Ϣ */
    wlan_phy_protocol_enum_uint8     en_protocol_mode;
    mac_rf_payload_enum_uint8        en_payload_flag;
    wlan_tx_ack_policy_enum_uint8    en_ack_policy;
    oal_uint32                       ul_payload_len;
}mac_cfg_tx_comp_stru;

typedef struct
{
    oal_uint8                   uc_offset_addr_a;
    oal_uint8                   uc_offset_addr_b;
    oal_uint16                  us_delta_gain;
}mac_cfg_dbb_scaling_stru;


/* Ƶƫ���������ʽ */
typedef struct
{
    oal_uint16                  us_idx;             /* ȫ����������ֵ */
    oal_uint16                  us_chn;             /* �����ŵ� */
    oal_int16                   as_corr_data[8];     /* У������ */
}mac_cfg_freq_skew_stru;

/* wfa edca�������� */
typedef struct
{
    oal_bool_enum_uint8             en_switch;      /* ���� */
    wlan_wme_ac_type_enum_uint8     en_ac;          /* AC */
    oal_uint16                      us_val;         /* ���� */
}mac_edca_cfg_stru;

/* PPM���������ʽ */
typedef struct
{
    oal_int8                     c_ppm_val;         /* PPM��ֵ */
    oal_uint8                    uc_clock_freq;     /* ʱ��Ƶ�� */
    oal_uint8                    uc_resv[1];
}mac_cfg_adjust_ppm_stru;

typedef struct
{
    oal_uint8                    uc_pcie_pm_level;  /* pcie�͹��ļ���,0->normal;1->L0S;2->L1;3->L1PM;4->L1s */
    oal_uint8                    uc_resv[3];
}mac_cfg_pcie_pm_level_stru;

/* �û���Ϣ��ص������������ */
typedef struct
{
    oal_uint16              us_user_idx;                        /* �û����� */
    oal_uint8               auc_reserve[2];

}mac_cfg_user_info_param_stru;

/* ��������������ṹ�� */
typedef struct
{
    oal_void *p_mac_regdom;

}mac_cfg_country_stru;

/* ����������͹������� */
typedef struct
{
    oal_uint8 uc_pwr;
    oal_uint8 en_exceed_reg;
    oal_uint8 auc_resv[2];
}mac_cfg_regdomain_max_pwr_stru;


/* ��ȡ��ǰ������������ַ���������ṹ�� */
typedef struct
{
    oal_int8    ac_country[3];
    oal_uint8   auc_resv[1];
}mac_cfg_get_country_stru;

/* query��Ϣ��ʽ:2�ֽ�WID x N */
typedef struct
{
    wlan_tidno_enum_uint8  en_tid;
    oal_uint8              uc_resv[3];
}mac_cfg_get_tid_stru;

typedef struct
{
    oal_uint16          us_user_id;
    oal_int8            c_rssi;
    oal_uint8           auc_resv[1];
}mac_cfg_query_rssi_stru;

#ifdef _PRE_WLAN_DFT_STAT
typedef struct
{
    oal_uint8           uc_device_distance;
    oal_uint8           uc_intf_state_cca;
    oal_uint8           uc_intf_state_co;
    oal_uint8           auc_resv[1];
}mac_cfg_query_ani_stru;
#endif

typedef struct
{
    oal_uint16          us_user_id;
#ifdef _PRE_WLAN_DFT_STAT
    oal_uint8           uc_cur_per;
    oal_uint8           uc_bestrate_per;
#else
    oal_uint8           auc_resv[2];
#endif
    oal_uint32          ul_tx_rate;         /* ��ǰ�������� */
    oal_uint32          ul_tx_rate_min;     /* һ��ʱ������С�������� */
    oal_uint32          ul_tx_rate_max;     /* һ��ʱ������������� */
    oal_uint32          ul_rx_rate;         /* ��ǰ�������� */
    oal_uint32          ul_rx_rate_min;     /* һ��ʱ������С�������� */
    oal_uint32          ul_rx_rate_max;     /* һ��ʱ�������������� */
}mac_cfg_query_rate_stru;

#ifdef _PRE_WLAN_RF_CALI
/* ����У׼���� */
typedef struct
{
    oal_uint8               uc_chain_idx;        /* ͨ�� */
    oal_uint8               uc_band_idx;         /* subband */
    oal_uint16              us_vref_value;       /* vrefֵ */
}mac_cfg_set_cali_vref_stru;
#endif

/* ����Ϊ�����ں����ò���ת��Ϊ�����ڲ������·��Ľṹ��*/

/* �����ں����õ�ɨ��������·���������ɨ����� */
typedef struct
{
    oal_ssids_stru              st_ssids[WLAN_SCAN_REQ_MAX_SSID];
    oal_int32                   l_ssid_num;

    const oal_uint8            *puc_ie;
    oal_uint32                  ul_ie_len;

    oal_scan_enum_uint8         en_scan_type;
    oal_uint8                   uc_num_channels_2G;
    oal_uint8                   uc_num_channels_5G;
    oal_uint8                   auc_arry[1];

    oal_uint32                  *pul_channels_2G;
    oal_uint32                  *pul_channels_5G;

    /* WLAN/P2P ��������£�p2p0 ��p2p-p2p0 cl ɨ��ʱ����Ҫʹ�ò�ͬ�豸������bit_is_p2p0_scan������ */
    oal_uint8                    bit_is_p2p0_scan : 1;   /* �Ƿ�Ϊp2p0 ����ɨ�� */
    oal_uint8                    bit_rsv          : 7;   /* ����λ */
    oal_uint8                    auc_rsv[3];             /* ����λ */
}mac_cfg80211_scan_param_stru;


typedef struct
{
    mac_cfg80211_scan_param_stru  *pst_mac_cfg80211_scan_param;
}mac_cfg80211_scan_param_pst_stru;

/* �����ں����õ�connect�������·���������connect���� */
typedef struct
{
    oal_uint8               wpa_versions;
    oal_uint8               cipher_group;
    oal_uint8               n_ciphers_pairwise;
    oal_uint8               ciphers_pairwise[OAL_NL80211_MAX_NR_CIPHER_SUITES];
    oal_uint8               n_akm_suites;
    oal_uint8               akm_suites[OAL_NL80211_MAX_NR_AKM_SUITES];

    oal_bool_enum_uint8     control_port;
}mac_cfg80211_crypto_settings_stru;

/**
 * enum nl80211_mfp - Management frame protection state
 * @NL80211_MFP_NO: Management frame protection not used
 * @NL80211_MFP_REQUIRED: Management frame protection required
 */

typedef enum
{
	MAC_NL80211_MFP_NO,
	MAC_NL80211_MFP_REQUIRED,

    MAC_NL80211_MFP_BUTT
}mac_nl80211_mfp_enum;
typedef oal_uint8 mac_nl80211_mfp_enum_uint8;



typedef struct
{
    oal_uint8                           uc_channel;              /* ap�����ŵ���ţ�eg 1,2,11,36,40... */
    oal_uint8                           uc_ssid_len;            /* SSID ���� */
    mac_nl80211_mfp_enum_uint8          en_mfp;
    oal_uint8                           uc_wapi;

    oal_uint8                          *puc_ie;
    oal_uint8                          *puc_ssid;               /* ����������AP SSID  */
    oal_uint8                          *puc_bssid;              /* ����������AP BSSID  */

    oal_bool_enum_uint8                 en_privacy;             /* �Ƿ���ܱ�־ */
    oal_nl80211_auth_type_enum_uint8    en_auth_type;           /* ��֤���ͣ�OPEN or SHARE-KEY */

    oal_uint8                           uc_wep_key_len;         /* WEP KEY���� */
    oal_uint8                           uc_wep_key_index;       /* WEP KEY���� */
    OAL_CONST oal_uint8                *puc_wep_key;            /* WEP KEY��Կ */

    mac_cfg80211_crypto_settings_stru   st_crypto;              /* ��Կ�׼���Ϣ */
    oal_uint32                          ul_ie_len;
}mac_cfg80211_connect_param_stru;

typedef struct
{
    oal_bool_enum_uint8                 en_privacy;             /* �Ƿ���ܱ�־ */
    oal_nl80211_auth_type_enum_uint8    en_auth_type;           /* ��֤���ͣ�OPEN or SHARE-KEY */
    oal_uint8                           uc_wep_key_len;         /* WEP KEY���� */
    oal_uint8                           uc_wep_key_index;       /* WEP KEY���� */
    oal_uint8                           auc_wep_key[WLAN_WEP104_KEY_LEN];            /* WEP KEY��Կ */
    mac_nl80211_mfp_enum_uint8          en_mgmt_proteced;       /* ��������pmf�Ƿ�ʹ�� */
    wlan_pmf_cap_status_uint8           en_pmf_cap;             /* �豸pmf���� */
    oal_bool_enum_uint8                 en_wps_enable;

    mac_cfg80211_crypto_settings_stru   st_crypto;              /* ��Կ�׼���Ϣ */
#ifdef _PRE_WLAN_FEATURE_11R
    oal_uint8                           auc_mde[8];             /* MD IE��Ϣ */
#endif //_PRE_WLAN_FEATURE_11R
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_int8                            c_rssi;                 /* ����AP��RSSI��Ϣ */
    oal_uint8                           auc_rsv[3];
#endif /* _PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE */
}mac_cfg80211_connect_security_stru;


#ifdef _PRE_WLAN_FEATURE_11R
#define MAC_MAX_FTE_LEN              257

typedef struct
{
    oal_uint16            us_mdid;                   /* Mobile Domain ID */
    oal_uint16            us_len;                    /* FTE �ĳ��� */
    oal_uint8             auc_ie[MAC_MAX_FTE_LEN];
}mac_cfg80211_ft_ies_stru;

typedef struct
{
    oal_cfg80211_bss_stru            *pst_bss;
    const oal_uint8                  *puc_ie;
    oal_uint8                         uc_ie_len;
    oal_nl80211_auth_type_enum_uint8  en_auth_type;
    const oal_uint8                  *puc_key;
    oal_uint8                         uc_key_len;
    oal_uint8                         uc_key_idx;
}mac_cfg80211_auth_req_stru;

#endif //_PRE_WLAN_FEATURE_11R

typedef struct
{

    oal_uint8       auc_mac_addr[OAL_MAC_ADDR_LEN];
    oal_uint8       auc_rsv[2];
}mac_cfg80211_init_port_stru;

/* �����ں����õ�disconnect�������·���������disconnect���� */
typedef struct mac_cfg80211_disconnect_param_tag
{
    oal_uint16              us_reason_code; /* disconnect reason code */
    oal_uint16              us_aid;

    oal_uint8               uc_type;
    oal_uint8               auc_arry[3];
}mac_cfg80211_disconnect_param_stru;



#ifdef _PRE_WLAN_CHIP_TEST


typedef enum
{
   MAC_LPM_SOC_BUS_GATING       = 0,
   MAC_LPM_SOC_PCIE_RD_BYPASS   = 1,
   MAC_LPM_SOC_MEM_PRECHARGE    = 2,
   MAC_LPM_SOC_PCIE_L0_S        = 3,
   MAC_LPM_SOC_PCIE_L1_0        = 4,
   MAC_LPM_SOC_AUTOCG_ALL       = 5,
   MAC_LPM_SOC_ADC_FREQ         = 6,

   MAC_LPM_SOC_SET_BUTT
}mac_lpm_soc_set_enum;
typedef oal_uint8   mac_lpm_soc_set_enum_uint8;


typedef struct mac_cfg_lpm_soc_set_tag
{
    mac_lpm_soc_set_enum_uint8      en_mode;
    oal_uint8                       uc_on_off;
    oal_uint8                       uc_pcie_idle;
    oal_uint8                       auc_rsv[1];
}mac_cfg_lpm_soc_set_stru;


typedef enum
{
   MAC_LPM_STATE_SOFT_SLEEP  = 0,
   MAC_LPM_STATE_GPIO_SLEEP  = 1,
   MAC_LPM_STATE_WORK        = 2,

   MAC_LPM_STATE_BUTT
}mac_lpm_state_enum;
typedef oal_uint8   mac_lpm_state_enum_uint8;

typedef struct mac_cfg_lpm_sleep_para_tag
{
    mac_lpm_state_enum_uint8         uc_pm_switch;  /*˯�߻��ѿ���*/
    oal_uint8                        uc_rsv;
    oal_uint16                       us_sleep_ms;   /*˯��ʱ�䣬����*/

}mac_cfg_lpm_sleep_para_stru;




typedef struct mac_cfg_lpm_psm_param_tag
{
    oal_uint8   uc_psm_on;
    oal_uint8   uc_psm_wakeup_mode;
    oal_uint8   auc_rsv[2];
    oal_uint16  us_psm_listen_interval;
    oal_uint16  us_psm_tbtt_offset;

}mac_cfg_lpm_psm_param_stru;

typedef struct mac_cfg_lpm_smps_stub
{
    oal_uint8                       uc_stub_type;   /*0:off, 1:������2:˫��*/
    oal_uint8                       uc_rts_en;    /*�Ƿ�RTS*/
}mac_cfg_lpm_smps_stub_stru;


typedef struct mac_cfg_lpm_txopps_set_tag
{
    oal_uint8                       uc_txop_ps_on;
    oal_uint8                       uc_conditon1;
    oal_uint8                       uc_conditon2;
    oal_uint8                       auc_rsv[1];
}mac_cfg_lpm_txopps_set_stru;

typedef struct mac_cfg_lpm_txopps_tx_stub
{
    oal_uint8                       uc_stub_on;   /*0:off, 1:on*/
    oal_uint8                       auc_rsv[1];
    oal_uint16                      us_begin_num;  /* ��n�����Ĵ�׮ */
}mac_cfg_lpm_txopps_tx_stub_stru;

typedef struct mac_cfg_lpm_wow_en
{
    oal_uint8                       uc_en;              /*0:off, 1:on*/
    oal_uint8                       uc_null_wake;       /*1:null data wakeup*/
}mac_cfg_lpm_wow_en_stru;

typedef struct mac_cfg_lpm_tx_data_tag
{
    oal_uint16  us_num;
    oal_uint16  us_len;
    oal_uint8   uc_ac;
    oal_uint8   uc_positive;                          /*0:����probe request��1:���� */
    oal_uint8   uc_psm;                               /*0:psm=0,1:psm=1*/
    oal_uint8   uc_rsv[1];
    oal_uint8   auc_da[WLAN_MAC_ADDR_LEN];            /*����probe requestʱ������Ϊָ��BSSID*/
    //oal_uint8   auc_sa[WLAN_MAC_ADDR_LEN];
}mac_cfg_lpm_tx_data_stru;

typedef struct
{
    oal_uint16  us_user_idx;
    oal_uint8   uc_is_remove;
    oal_uint8   auc_resv[1];
}mac_cfg_remove_lut_stru;


typedef struct
{
    oal_uint8                               auc_mac_ra[WLAN_MAC_ADDR_LEN];
    oal_uint8                               uc_pkt_num;
    mac_test_frame_type_enum_uint8          en_frame_type;
}mac_cfg_send_frame_param_stru;

typedef struct
{
    oal_uint32                               ul_mac_ctrl;
    oal_uint32                               ul_rf_ctrl;
}mac_cfg_coex_ctrl_param_stru;

#endif
typedef struct
{
    oal_uint8                               auc_mac_da[WLAN_MAC_ADDR_LEN];
    oal_uint8                               uc_category;
    oal_uint8                               auc_resv[1];
}mac_cfg_send_action_param_stru;

#ifdef _PRE_WLAN_FEATURE_SMPS
typedef struct
{
    oal_uint8    uc_smps_mode;
    oal_uint8    auc_rsv[1];
    oal_uint16   us_user_idx;
}mac_cfg_smps_mode_stru;
#endif

typedef struct
{
    oal_int32   l_is_psm;                           /* �Ƿ������� */
    oal_int32   l_is_qos;                           /* �Ƿ�qosnull */
    oal_int32   l_tidno;                            /* tid�� */
}mac_cfg_tx_nulldata_stru;

/* ������̫��������Ҫ�Ĳ��� */
typedef struct
{
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction;
    oal_switch_enum_uint8   en_switch;
    oal_uint8               auc_user_macaddr[WLAN_MAC_ADDR_LEN];
}mac_cfg_eth_switch_param_stru;

/* ����80211����֡������Ҫ�Ĳ��� */
typedef struct
{
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction;
    oam_user_track_frame_type_enum_uint8    en_frame_type;
    oal_switch_enum_uint8                   en_frame_switch;
    oal_switch_enum_uint8                   en_cb_switch;
    oal_switch_enum_uint8                   en_dscr_switch;
    oal_uint8                               auc_resv[1];
    oal_uint8                               auc_user_macaddr[WLAN_MAC_ADDR_LEN];
}mac_cfg_80211_ucast_switch_stru;
#ifdef _PRE_DEBUG_MODE_USER_TRACK
/* ��ȡ�û��շ�����������Ҫ�Ĳ����ṹ */
typedef struct
{
    oal_uint8                               auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oam_user_txrx_param_type_enum_uint8     en_type;
    oal_switch_enum_uint8                   en_switch;
    oal_uint32                              ul_period;
}mac_cfg_report_txrx_param_stru;
#endif
#ifdef _PRE_WLAN_FEATURE_TXOPPS
/* �������mac txoppsʹ�ܼĴ�����Ҫ���������� */
typedef struct
{
    oal_switch_enum_uint8 en_machw_txopps_en;               /* sta�Ƿ�ʹ��txopps */
    oal_switch_enum_uint8 en_machw_txopps_condition1;       /* txopps����1 */
    oal_switch_enum_uint8 en_machw_txopps_condition2;       /* txopps����2 */
    oal_uint8             auc_resv[1];
}mac_txopps_machw_param_stru;
#endif
/* ����80211�鲥\�㲥֡������Ҫ�Ĳ��� */
typedef struct
{
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction;
    oam_user_track_frame_type_enum_uint8    en_frame_type;
    oal_switch_enum_uint8                   en_frame_switch;
    oal_switch_enum_uint8                   en_cb_switch;
    oal_switch_enum_uint8                   en_dscr_switch;
    oal_uint8                               auc_resv[3];
}mac_cfg_80211_mcast_switch_stru;

/* ����probe request��probe response������Ҫ�Ĳ��� */
typedef struct
{
    oam_ota_frame_direction_type_enum_uint8 en_frame_direction;
    oal_switch_enum_uint8                   en_frame_switch;
    oal_switch_enum_uint8                   en_cb_switch;
    oal_switch_enum_uint8                   en_dscr_switch;
}mac_cfg_probe_switch_stru;

/* ��ȡmpdu��Ŀ��Ҫ�Ĳ��� */
typedef struct
{
    oal_uint8                   auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                   auc_resv[2];
}mac_cfg_get_mpdu_num_stru;

#ifdef _PRE_WLAN_DFT_STAT
typedef struct
{
    oal_uint8                   auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                   uc_param;
    oal_uint8                   uc_resv;
}mac_cfg_usr_queue_param_stru;
#endif

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    oal_uint8                   auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                   uc_param;
    oal_uint8                   uc_tid_no;
}mac_cfg_ampdu_stat_stru;
#endif

typedef struct
{
    oal_uint8                   uc_aggr_num_switch; /* ���ƾۺϸ������� */
    oal_uint8                   uc_aggr_num;        /* �ۺϸ��� */
    oal_uint8                   auc_resv[2];
}mac_cfg_aggr_num_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
typedef struct
{
    oal_uint8                   uc_mmss_val;        /* ��С֡��� */
    oal_uint8                   auc_resv[3];
}mac_cfg_ampdu_mmss_stru;
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
typedef struct
{
    oal_uint16                  us_pll_int;         /* ������Ƶϵ�� */
    oal_uint16                  us_pll_frac;        /* С����Ƶϵ�� */
}mac_cfg_freq_adjust_stru;
#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK
typedef struct
{
    oal_uint8                   auc_user_macaddr[WLAN_MAC_ADDR_LEN];
    oal_uint8                   uc_param;
    oal_uint8                   uc_resv;
}mac_cfg_usr_thrput_stru;

#endif

typedef struct
{
    oal_uint32  ul_coext_info;
    oal_uint32  ul_channel_report;
}mac_cfg_set_2040_coexist_stru;

typedef struct
{
    oal_uint32   ul_mib_idx;
    oal_uint32   ul_mib_value;
}mac_cfg_set_mib_stru;

typedef struct
{
    oal_uint8  uc_bypass_type;
    oal_uint8  uc_value;
    oal_uint8  auc_resv[2];
}mac_cfg_set_thruput_bypass_stru;

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
typedef struct
{
    oal_uint8  uc_cmd_type;
    oal_uint8  uc_value;
    oal_uint8  auc_resv[2];
}mac_cfg_set_auto_freq_stru;
#endif
typedef struct
{
    oal_uint8  uc_performance_log_switch_type;
    oal_uint8  uc_value;
    oal_uint8  auc_resv[2];
}mac_cfg_set_performance_log_switch_stru;

typedef struct
{
    oal_uint32   ul_timeout;
    oal_uint8    uc_is_period;
    oal_uint8    uc_stop_start;
    oal_uint8    auc_resv[2];
}mac_cfg_test_timer_stru;

typedef struct
{
    oal_uint16   us_user_idx;
    oal_uint16   us_rx_pn;
}mac_cfg_set_rx_pn_stru;

typedef struct
{
    oal_uint32   ul_frag_threshold;
}mac_cfg_frag_threshold_stru;

typedef struct
{
    oal_uint32   ul_rts_threshold;
}mac_cfg_rts_threshold_stru;

typedef struct
{
    /* software_retryֵ */
    oal_uint8   uc_software_retry;
    /* �Ƿ�ȡtest���õ�ֵ��Ϊ0��Ϊ������������ */
    oal_uint8   uc_retry_test;

    oal_uint8   uc_pad[2];
}mac_cfg_set_soft_retry_stru;


typedef struct
{
    oal_bool_enum_uint8 en_default_key;
    oal_uint8           uc_key_index;
    oal_uint8           uc_key_len;
    oal_uint8           auc_wep_key[WLAN_WEP104_KEY_LEN];
} mac_wep_key_param_stru;



typedef struct mac_pmksa_tag
{
    oal_uint8 auc_bssid[OAL_MAC_ADDR_LEN];
    oal_uint8 auc_pmkid[OAL_PMKID_LEN];

}mac_pmksa_stru;

typedef struct
{
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_pairwise;
    oal_uint8                auc_mac_addr[OAL_MAC_ADDR_LEN];
    mac_key_params_stru      st_key;
}mac_addkey_param_stru;


typedef struct
{
    oal_int32  key_len;
    oal_uint8 auc_key[OAL_WPA_KEY_LEN];
}mac_key_stru;

typedef struct
{
    oal_int32  seq_len;
    oal_uint8 auc_seq[OAL_WPA_SEQ_LEN];
}mac_seq_stru;


typedef struct
{
    //oal_net_device_stru     *pst_netdev;
    oal_uint8                  uc_key_index;
    oal_bool_enum_uint8        en_pairwise;
    //oal_uint8                auc_resv1[2];
    oal_uint8                  auc_mac_addr[OAL_MAC_ADDR_LEN];
    //oal_uint8                  uc_usridx;       /*  */
    oal_uint8                  cipher;
    //oal_uint8                  uc_type;        /* 1-key 2-seq */
    oal_uint8                  auc_rsv[3];
    mac_key_stru               st_key;
    mac_seq_stru               st_seq;
}mac_addkey_hmac2dmac_param_stru;

typedef struct
{
    oal_net_device_stru     *pst_netdev;
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_pairwise;
    oal_uint8                auc_resv1[2];
    oal_uint8               *puc_mac_addr;
    oal_void                *cookie;
    oal_void               (*callback)(oal_void *cookie, oal_key_params_stru *key_param);
}mac_getkey_param_stru;

typedef struct
{
    //oal_net_device_stru     *pst_netdev;
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_pairwise;
    //oal_uint8                auc_resv1[2];
    oal_uint8                auc_mac_addr[OAL_MAC_ADDR_LEN];
}mac_removekey_param_stru;

typedef struct
{
    //oal_net_device_stru     *pst_netdev;
    oal_uint8                uc_key_index;
    oal_bool_enum_uint8      en_unicast;
    oal_bool_enum_uint8      en_multicast;
    oal_uint8                auc_resv1[1];
}mac_setdefaultkey_param_stru;

typedef struct
{
    oal_uint32  ul_dfs_mode;
    oal_int32   al_para[3];
}mac_cfg_dfs_param_stru;

typedef struct
{
    oal_uint8  uc_total_channel_num;
    oal_uint8  auc_channel_number[15];
}mac_cfg_dfs_auth_channel_stru;


typedef struct
{
    oal_uint    ul_addr;
    oal_uint32  ul_len;
}mac_cfg_dump_memory_stru;

#ifdef _PRE_WLAN_PERFORM_STAT
/* ͳ�������� */
typedef enum
{
    MAC_STAT_TYPE_TID_DELAY,
    MAC_STAT_TYPE_TID_PER,
    MAC_STAT_TYPE_TID_THRPT,
    MAC_STAT_TYPE_USER_THRPT,
    MAC_STAT_TYPE_VAP_THRPT,

    MAC_STAT_TYPE_BUTT
}mac_stat_type_enum;
typedef oal_uint8    mac_stat_type_enum_uint8;

typedef struct
{
    mac_stat_type_enum_uint8    en_stat_type;                       /* ͳ������ */
    oal_uint8                   uc_vap_id;                          /* vap id */
    oal_uint8                   auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8                   uc_tidno;                           /* tidno */
    oal_uint16                  us_stat_period;                     /* ͳ������ */
    oal_uint16                  us_stat_num;                        /* ͳ�ƴ��� */
}mac_cfg_stat_param_stru;

typedef struct
{
    mac_stat_type_enum_uint8    en_stat_type;                       /* ͳ������ */
    oal_uint8                   uc_vap_id;                          /* vap id */
    oal_uint8                   auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8                   uc_tidno;                           /* tidno */
}mac_cfg_display_param_stru;

/* ͳ��tid */
typedef struct
{
    oal_uint8               uc_vap_id;                          /* vap id */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8               uc_tidno;                           /* tidno */
    oal_uint16              us_stat_period;                     /* ͳ������ */
    oal_uint32              ul_stat_num;                        /* ͳ�ƴ��� */
}mac_ioctl_stat_param_stru;

#endif


#ifdef _PRE_WLAN_FEATURE_FLOWCTL

typedef enum
{
    MAC_LINUX_SUBQ_BE = 0,    /* best effort */
    MAC_LINUX_SUBQ_BK = 1,    /* background */
    MAC_LINUX_SUBQ_VI = 2,    /* video */
    MAC_LINUX_SUBQ_VO = 3,    /* voice */

    MAC_LINUX_SUBQ_BUTT
}MAC_linux_subq_type_enum;
typedef oal_uint8 mac_linux_subq_type_enum;

#define MAC_TOS_TO_SUBQ(_tos) (      \
        (((_tos) == 0) || ((_tos) == 3)) ? MAC_LINUX_SUBQ_BE : \
        (((_tos) == 1) || ((_tos) == 2)) ? MAC_LINUX_SUBQ_BK : \
        (((_tos) == 4) || ((_tos) == 5)) ? MAC_LINUX_SUBQ_VI : \
        MAC_LINUX_SUBQ_VO)

typedef struct
{
    oal_uint16                      us_assoc_id;
    oal_uint8                       uc_vap_id;
    oal_uint8                       uc_tidno;
    oal_uint8                       uc_is_stop;
    oal_uint8                       uc_resv[3];
}mac_ioctl_queue_backp_stru;

#endif


/* �㷨����ö�٣�����ֵ */
typedef struct
{
    mac_alg_cfg_enum_uint8              en_alg_cfg;     /* ��������ö�� */
    oal_uint8                           uc_resv[3];     /* �ֽڶ��� */
    oal_uint32                          ul_value;       /* ���ò���ֵ */
}mac_ioctl_alg_param_stru;

/* AUTORATE LOG �㷨����ö�٣�����ֵ */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;     /* ��������ö�� */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8               uc_ac_no;                           /* AC���� */
    oal_uint8               auc_resv[2];
    oal_uint16              us_value;                           /*���ò���ֵ */
}mac_ioctl_alg_ar_log_param_stru;

/* AUTORATE ������ص�������� */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;                         /* ��������ö�� */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8               auc_resv[1];
    oal_uint16              us_value;                           /* ������� */
}mac_ioctl_alg_ar_test_param_stru;

/* TXMODE LOG �㷨����ö�٣�����ֵ */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;     /* ��������ö�� */
    oal_uint8               uc_ac_no;                           /* AC���� */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8               auc_resv1[2];
    oal_uint16              us_value;                           /*���ò���ֵ */
}mac_ioctl_alg_txbf_log_param_stru;
/* �㷨��������ӿ� */
typedef struct
{
    oal_uint8       uc_argc;
    oal_uint8       auc_argv_offset[DMAC_ALG_CONFIG_MAX_ARG];
}mac_ioctl_alg_config_stru;

/* TPC LOG �㷨����ö�٣�����ֵ */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;                         /* ��������ö�� */
    oal_uint8               auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* MAC��ַ */
    oal_uint8               uc_ac_no;                           /* AC���� */
    oal_uint16              us_value;                           /* ���ò���ֵ */
    oal_int8               *pc_frame_name;                      /* ��ȡ�ض�֡����ʹ�øñ��� */
}mac_ioctl_alg_tpc_log_param_stru;

/* cca opt LOG �㷨����ö�٣�����ֵ */
typedef struct
{
    mac_alg_cfg_enum_uint8  en_alg_cfg;                         /* ��������ö�� */
    oal_uint16              us_value;                           /* ͳ����ʱ�� */
    oal_uint8               auc_resv;
}mac_ioctl_alg_cca_opt_log_param_stru;

#ifdef _PRE_DEBUG_MODE
/* ɨ��������� */
typedef struct
{
    oal_int8                            ac_scan_type[15];
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;
}mac_ioctl_scan_test_config_stru;
#endif

/*RTS ���Ͳ���*/
typedef struct
{
    wlan_legacy_rate_value_enum_uint8   auc_rate[HAL_TX_RATE_MAX_NUM];           /*�������ʣ���λmpbs*/
    wlan_phy_protocol_enum_uint8        auc_protocol_mode[HAL_TX_RATE_MAX_NUM] ; /*Э��ģʽ, ȡֵ�μ�wlan_phy_protocol_enum_uint8*/
    wlan_channel_band_enum_uint8        en_band;
    oal_uint8                           auc_recv[3];
}mac_cfg_rts_tx_param_stru;

/* �鲥ת���� ���Ͳ��� */
typedef struct
{
    oal_uint8 uc_m2u_mcast_mode;
    oal_uint8 uc_m2u_snoop_on;
}mac_cfg_m2u_snoop_on_param_stru;


/* ���鲥ת���������� */
typedef struct
{
    oal_uint32 ul_deny_group_addr;
}mac_add_m2u_deny_table_stru;

/* ����鲥ת���������� */
typedef struct
{
    oal_uint8 uc_m2u_clear_deny_table;
    oal_uint8 uc_m2u_show_deny_table;
}mac_clg_m2u_deny_table_stru;


/* print snoop table*/
typedef struct
{
    oal_uint8 uc_m2u_show_snoop_table;
}mac_show_m2u_snoop_table_stru;

/* add snoop table*/
typedef struct
{
    oal_uint8 uc_m2u_add_snoop_table;
}mac_add_m2u_snoop_table_stru;

typedef struct
{
    oal_bool_enum_uint8 en_proxyarp;
    oal_uint8           auc_rsv[3];
}mac_proxyarp_en_stru;

typedef struct
{
    oal_uint8                     auc_bssid[WLAN_MAC_ADDR_LEN];
    oal_uint8                     auc_resv0[2];
    oal_uint8                     auc_pmkid[WLAN_PMKID_LEN];
}mac_cfg_pmksa_param_stru;

typedef struct
{
    oal_uint64                          ull_cookie;
    oal_uint32                          ul_listen_duration;         /* ����ʱ��   */
    oal_uint8                           uc_listen_channel;          /* �������ŵ� */
    wlan_channel_bandwidth_enum_uint8   en_listen_channel_type;     /* �����ŵ����� */
    oal_uint8                           uc_home_channel;            /* �����������ص��ŵ� */
    wlan_channel_bandwidth_enum_uint8   en_home_channel_type;       /* �����������������ŵ����� */
    mac_vap_state_enum_uint8            en_last_vap_state;          /* P2P0��P2P_CL ����VAP �ṹ������������ǰVAP ��״̬�����ڼ�������ʱ�ָ���״̬ */
    wlan_channel_band_enum_uint8        en_band;
    oal_ieee80211_channel_stru          st_listen_channel;

}mac_remain_on_channel_param_stru;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
typedef struct
{
    oal_uint8    uc_pool_id;
}mac_device_pool_id_stru;
#endif

/* WPAS ����֡���ͽṹ */
typedef struct
{
    oal_int32               channel;
    oal_uint8               mgmt_frame_id;
    oal_uint8               uc_rsv;
    oal_uint16              us_len;
    OAL_CONST oal_uint8    *puc_frame;
} mac_mgmt_frame_stru;

/* STA PS ���Ͳ��� */
#ifdef _PRE_WLAN_FEATURE_STA_PM
typedef struct
{
    oal_uint8   uc_vap_ps_mode;

}mac_cfg_ps_mode_param_stru;

typedef struct
{
    oal_uint16   us_beacon_timeout;
    oal_uint16   us_tbtt_offset;
    oal_uint16   us_ext_tbtt_offset;
	oal_uint16   us_dtim3_on;
}mac_cfg_ps_param_stru;

#ifdef _PRE_PSM_DEBUG_MODE
typedef struct
{
    oal_uint8   uc_psm_info_enable      :2;  //����psm��ͳ��ά�����
    oal_uint8   uc_psm_debug_mode       :2;  //����psm��debug��ӡģʽ
    oal_uint8   uc_psm_resd             :4;
}mac_cfg_ps_info_stru;
#endif

#endif
typedef struct
{
    oal_uint8   uc_show_ip_addr                 :4;  //show ip addr
    oal_uint8   uc_show_arpoffload_info         :4;	 //show arpoffload ά��
}mac_cfg_arpoffload_info_stru;

typedef struct
{
    oal_uint8   uc_in_suspend; //������
    oal_uint8   uc_arpoffload_switch; // arpoffload����
}mac_cfg_suspend_stru;

typedef enum {
    MAC_STA_PM_SWITCH_OFF         = 0,        /* �رյ͹��� */
    MAC_STA_PM_SWITCH_ON          = 1,        /* �򿪵͹��� */
    MAC_STA_PM_MANUAL_MODE_ON     = 2,        /* �����ֶ�sta pm mode */
    MAC_STA_PM_MANUAL_MODE_OFF    = 3,        /* �ر��ֶ�sta pm mode */
    MAC_STA_PM_SWITCH_BUTT,                   /* ������� */
}mac_pm_switch_enum;
typedef oal_uint8 mac_pm_switch_enum_uint8;

typedef enum {
    MAC_STA_PM_CTRL_TYPE_HOST   = 0,        /* �͹��Ŀ������� HOST  */
    MAC_STA_PM_CTRL_TYPE_DBAC   = 1,        /* �͹��Ŀ������� DBAC  */
    MAC_STA_PM_CTRL_TYPE_ROAM   = 2,        /* �͹��Ŀ������� ROAM  */
    MAC_STA_PM_CTRL_TYPE_CMD    = 3,        /* �͹��Ŀ������� CMD   */
    MAC_STA_PM_CTRL_TYPE_BUTT,              /* ������ͣ�ӦС�� 8  */
}mac_pm_ctrl_type_enum;
typedef oal_uint8 mac_pm_ctrl_type_enum_uint8;

typedef struct
{
    mac_pm_ctrl_type_enum_uint8     uc_pm_ctrl_type;       /*mac_pm_ctrl_type_enum*/
    mac_pm_switch_enum_uint8        uc_pm_enable;          /*mac_pm_switch_enum*/
}mac_cfg_ps_open_stru;

/* P2P OPS �������ò��� */
typedef struct
{
    oal_uint8       en_ops_ctrl;
    oal_uint8       uc_ct_window;
    oal_uint8       en_pause_ops;
    oal_uint8       auc_rsv[1];
}mac_cfg_p2p_ops_param_stru;

/* P2P NOA�������ò��� */
typedef struct
{
    oal_uint32      ul_start_time;
    oal_uint32      ul_duration;
    oal_uint32      ul_interval;
    oal_uint8       uc_count;
    oal_uint8       auc_rsv[3];
}mac_cfg_p2p_noa_param_stru;

/* P2P ���ܿ������� */
typedef struct
{
    oal_uint8       uc_p2p_statistics_ctrl;/* 0:���P2P ͳ��ֵ�� 1:��ӡ���ͳ��ֵ */
    oal_uint8       auc_rsv[3];

}mac_cfg_p2p_stat_param_stru;

#ifdef _PRE_WLAN_FEATURE_ROAM
typedef enum
{
    WPAS_CONNECT_STATE_INIT            = 0,
    WPAS_CONNECT_STATE_START           = 1,
    WPAS_CONNECT_STATE_ASSOCIATED      = 2,
    WPAS_CONNECT_STATE_HANDSHAKED      = 3,
    WPAS_CONNECT_STATE_IPADDR_OBTAINED   = 4,
    WPAS_CONNECT_STATE_IPADDR_REMOVED    = 5,
    WPAS_CONNECT_STATE_BUTT
}wpas_connect_state_enum;
typedef oal_uint32 wpas_connect_state_enum_uint32;
/* roam trigger ���ݽṹ�� */
typedef struct
{
    oal_int8                      c_trigger_2G;
    oal_int8                      c_trigger_5G;
    oal_uint8                     auc_resv[2];
}mac_roam_trigger_stru;

/* roam hmac ͬ�� dmac���ݽṹ�� */
typedef struct
{
    oal_uint16                      us_sta_aid;
    oal_uint16                      us_pad;
    mac_channel_stru                st_channel;
    mac_user_cap_info_stru          st_cap_info;
    mac_key_mgmt_stru               st_key_info;
    mac_user_tx_param_stru          st_user_tx_info;
    oal_uint32                      ul_back_to_old;
}mac_h2d_roam_sync_stru;
#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/* ���ƻ� linkloss�������ò��� */
typedef struct
{
    oal_uint8                   uc_linkloss_threshold_wlan_near;
    oal_uint8                   uc_linkloss_threshold_wlan_far;
    oal_uint8                   uc_linkloss_threshold_p2p;
    oal_uint8                   auc_resv[1];
}mac_cfg_linkloss_threshold;
/* ���ƻ� power ref 2g 5g���ò��� */
typedef struct
{
    oal_uint32                  ul_power_ref_5g;
}mac_cfg_power_ref;
/* customize rf cfg struct */
typedef struct
{
    oal_int8                    c_rf_gain_db_mult4;      /*�ⲿPA/LNA bypassʱ������(����0.25dB)*/
    oal_int8                    c_rf_gain_db_mult10;     /*�ⲿPA/LNA bypassʱ������(����0.1dB)*/
}mac_cfg_gain_db_per_band;
typedef struct
{
    /* 2g */
    mac_cfg_gain_db_per_band    ac_gain_db_2g[MAC_NUM_2G_BAND];
    /* 5g */
    mac_cfg_gain_db_per_band    ac_gain_db_5g[MAC_NUM_5G_BAND];

    oal_uint16                  us_lna_on2off_time_ns_5g;           /* LNA����LNA�ص�ʱ��(ns) */
    oal_uint16                  us_lna_off2on_time_ns_5g;           /* LNA�ص�LNA����ʱ��(ns) */

    oal_int8                    c_rf_line_rx_gain_db_5g;            /* �ⲿLNA bypassʱ������(dB) */
    oal_int8                    c_lna_gain_db_5g;                   /* �ⲿLNA����(dB) */
    oal_int8                    c_rf_line_tx_gain_db_5g;            /* �ⲿLNA bypassʱ������(dB) */
    oal_uint8                   uc_ext_switch_isexist_5g;           /* �Ƿ�ʹ���ⲿswitch */

    oal_uint8                   uc_ext_pa_isexist_5g;               /* �Ƿ�ʹ���ⲿpa */
    oal_uint8                   uc_ext_lna_isexist_5g;              /* �Ƿ�ʹ���ⲿlna */
    oal_uint8                   uc_far_dist_pow_gain_switch;        /* ��Զ���빦�����濪�� */
    oal_uint8                   uc_far_dist_dsss_scale_promote_switch;   /* ��Զ��11b 1m 2m dbb scale����ʹ�ܿ��� */
}mac_cfg_customize_rf;
typedef struct
{
    oal_uint16                  us_tx_ratio;                        /* txռ�ձ� */
    oal_uint16                  us_tx_pwr_comp_val;                 /* ���书�ʲ���ֵ */
}mac_tx_ratio_vs_pwr_stru;

/* ���ƻ�TXռ�ձ�&�¶Ȳ������书�ʵĲ��� */
typedef struct
{
    mac_tx_ratio_vs_pwr_stru    ast_txratio2pwr[3];                 /* 3��ռ�ձȷֱ��Ӧ���ʲ���ֵ */
    oal_uint32                  ul_more_pwr;                        /* �����¶ȶ��ⲹ���ķ��书�� */
}mac_cfg_customize_tx_pwr_comp_stru;
/* ���ƻ� ʱ�����ò��� */
typedef struct
{
    oal_uint32                  ul_rtc_clk_freq;
    oal_uint8                   uc_clk_type;
    oal_uint8                   auc_resv[3];
}st_pm_cfg_param;
/* RF�Ĵ������ƻ��ṹ�� */
typedef struct
{
    oal_uint16                 us_rf_reg117;
    oal_uint16                 us_rf_reg123;
    oal_uint16                 us_rf_reg124;
    oal_uint16                 us_rf_reg125;
    oal_uint16                 us_rf_reg126;
    oal_uint8                  auc_resv[2];
}mac_cus_dts_rf_reg;
/* FCC��֤ �����ṹ�� */
typedef struct
{
    oal_uint8       uc_index;           /* �±��ʾƫ�� */
    oal_uint8       uc_max_txpower;     /* ����͹��� */
    oal_uint8       uc_dbb_scale;       /* dbb scale */
    oal_uint8       uc_resv;
}mac_cus_band_edge_limit_stru;
/* ���ƻ� У׼���ò��� */
typedef struct
{
    /* dts */
    oal_int16                  aus_cali_txpwr_pa_dc_ref_2g_val[13];        /* txpwr���ŵ�refֵ */
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band1;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band2;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band3;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band4;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band5;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band6;
    oal_int16                  us_cali_txpwr_pa_dc_ref_5g_val_band7;
    oal_int8                   uc_band_5g_enable;
    oal_uint8                  uc_tone_amp_grade;
    oal_int8                   auc_resv_wifi_cali[2];
    /* bt tmp */
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band1;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band2;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band3;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band4;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band5;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band6;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band7;
    oal_uint16                  us_cali_bt_txpwr_pa_ref_band8;
    oal_uint16                  us_cali_bt_txpwr_numb;
    oal_uint16                  us_cali_bt_txpwr_pa_fre1;
    oal_uint16                  us_cali_bt_txpwr_pa_fre2;
    oal_uint16                  us_cali_bt_txpwr_pa_fre3;
    oal_uint16                  us_cali_bt_txpwr_pa_fre4;
    oal_uint16                  us_cali_bt_txpwr_pa_fre5;
    oal_uint16                  us_cali_bt_txpwr_pa_fre6;
    oal_uint16                  us_cali_bt_txpwr_pa_fre7;
    oal_uint16                  us_cali_bt_txpwr_pa_fre8;
    oal_uint8                   uc_bt_tone_amp_grade;
    oal_uint8                   auc_resv_bt_cali[1];
}mac_cus_dts_cali_stru;
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */



#ifdef _PRE_WLAN_FEATURE_UAPSD
extern oal_uint8 g_uc_uapsd_cap;
#endif

/* 1102 wiphy Vendor CMD���� ��Ӧcfgid: WLAN_CFGID_VENDOR_CMD */
typedef struct mac_vendor_cmd_channel_list_info
{
    oal_uint8 uc_channel_num_2g;
    oal_uint8 uc_channel_num_5g;
    oal_uint8 auc_channel_list_2g[MAC_CHANNEL_FREQ_2_BUTT];
    oal_uint8 auc_channel_list_5g[MAC_CHANNEL_FREQ_5_BUTT];
}mac_vendor_cmd_channel_list_stru;

/*CHR2.0ʹ�õ�STAͳ����Ϣ*/
typedef  struct
{
    oal_uint8                        uc_distance;                               /*�㷨��tpc���룬��Ӧdmac_alg_tpc_user_distance_enum*/
    oal_uint8                        uc_cca_intr;                               /*�㷨��cca_intr���ţ���Ӧalg_cca_opt_intf_enum*/
    oal_uint8                        auc_reserve[2];
    oal_uint32                       ul_bcn_cnt;                                /*�յ���beacon����*/
    oal_uint32                       ul_bcn_tout_cnt;                           /*beacon��ʧ�ļ���*/
}station_info_extend_stru;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
//extern oal_void mac_vap_set_p2p_channel(mac_vap_stru *pst_mac_vap, mac_channel_stru * pst_p2p_home_channel);

/*****************************************************************************
 �� �� ��  : mac_get_excludeunencrypted
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_get_excludeunencrypted(mac_vap_stru *pst_mac_vap)
{
  return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11ExcludeUnencrypted;
}

/*****************************************************************************
 �� �� ��  : mac_get_PrivacyInvoked
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_get_rsnacfggroupcipher(mac_vap_stru *pst_mac_vap)
{
  return pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher;
}

OAL_STATIC OAL_INLINE oal_void mac_mib_set_rsnacfggroupcipher(mac_vap_stru *pst_mac_vap, oal_uint8 uc_group_cipher)
{
  pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher = uc_group_cipher;
}
OAL_STATIC OAL_INLINE oal_void mac_mib_set_RSNAGroupCipherSelected(mac_vap_stru *pst_mac_vap, oal_uint8 uc_group_cipher_selected)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherSelected = uc_group_cipher_selected;
}

OAL_STATIC OAL_INLINE oal_void mac_mib_set_RSNAConfigGroupCipherSize(oal_uint32 ul_group_cipher_size,mac_vap_stru *pst_mac_vap)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize = ul_group_cipher_size;
}

OAL_STATIC OAL_INLINE oal_uint32 mac_get_RSNAConfigGroupCipherSize(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize;
}

void mac_mib_set_RSNAConfigAuthenticationSuiteImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_inp, oal_uint8 uc_idx);
void mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_pairwise_value);
void mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_pairwise_value);

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
#define mac_vap_is_msta(vap) ((vap)->st_psta.en_psta_mode == PSTA_MODE_MSTA)
#define mac_vap_is_vsta(vap) ((vap)->st_psta.en_psta_mode == PSTA_MODE_VSTA)
#define mac_vap_is_pbss(vap) ((vap)->st_psta.en_psta_mode == PSTA_MODE_PBSS)

#define mac_param_is_msta(param) ((param)->en_psta_mode == PSTA_MODE_MSTA)
#define mac_param_is_vsta(param) ((param)->en_psta_mode == PSTA_MODE_VSTA)
#define mac_param_is_pbss(param) ((param)->en_psta_mode == PSTA_MODE_PBSS)

/*****************************************************************************
 �� �� ��  : mac_psta_init_vap
 ��������  : init psta
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��15��
    ��    ��   : gaolin g00196511
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE  oal_uint32 mac_psta_init_vap(mac_vap_stru *pst_mac_vap, mac_cfg_add_vap_param_stru *pst_param)
{
    /* init role for any vap */
    pst_mac_vap->st_psta.en_psta_mode = pst_param->en_psta_mode;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : mac_mib_get_PrivacyInvoked
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_privacyinvoked(mac_vap_stru *pst_mac_vap)
{
  return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_PrivacyInvoked
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_privacyinvoked(mac_vap_stru *pst_mac_vap,oal_bool_enum_uint8 en_privacyinvoked)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked = en_privacyinvoked;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_rsnaactivated
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_rsnaactivated(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_rsnaactivated
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_rsnaactivated(mac_vap_stru *pst_mac_vap,oal_bool_enum_uint8 en_rsnaactivated)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated = en_rsnaactivated;
}

/*****************************************************************************
 �� �� ��  : mac_is_wep_enabled
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_is_wep_enabled(mac_vap_stru *pst_mac_vap)
{
    if(OAL_PTR_NULL == pst_mac_vap)
    {
        return OAL_FALSE;
    }

    if ((mac_mib_get_privacyinvoked(pst_mac_vap) == OAL_FALSE)||(mac_mib_get_rsnaactivated(pst_mac_vap) == OAL_TRUE))
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : mac_is_wep_allowed
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_is_wep_allowed(mac_vap_stru *pst_mac_vap)
{
    oal_uint8 uc_grp_policy ;

    if (mac_mib_get_rsnaactivated(pst_mac_vap) == OAL_TRUE)
    {
        uc_grp_policy = mac_get_rsnacfggroupcipher(pst_mac_vap);
        if ((WLAN_80211_CIPHER_SUITE_WEP_40 == uc_grp_policy)||(WLAN_80211_CIPHER_SUITE_WEP_104 == uc_grp_policy))
        {
            return OAL_TRUE;
        }

        return OAL_FALSE;
    }
    else
    {
        return mac_is_wep_enabled(pst_mac_vap);
    }
}

/*****************************************************************************
 �� �� ��  : mac_set_WEPDefaultKeyID
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_set_wep_default_keyid(mac_vap_stru *pst_mac_vap,oal_uint8 uc_default_key_id)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.uc_dot11WEPDefaultKeyID = uc_default_key_id;
}

/*****************************************************************************
 �� �� ��  : mac_get_WEPDefaultKeyID
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��28��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_get_wep_default_keyid(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.uc_dot11WEPDefaultKeyID);
}

/*****************************************************************************
 �� �� ��  : mac_get_WEPDefaultKeySize
 ��������  : ��ȡĬ����Կ�Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��28��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_get_wep_default_keysize(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[mac_get_wep_default_keyid(pst_mac_vap)].auc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET]);
}

/*****************************************************************************
 �� �� ��  : mac_get_wep_keysize
 ��������  : ��ȡָ�����кŵ�wep key��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_get_wep_keysize(mac_vap_stru *pst_mac_vap, oal_uint8 uc_idx)
{
    return (pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET]);
}

/*****************************************************************************
 �� �� ��  : mac_get_wep_default_keyvalue
 ��������  : ��ȡĬ��wep key��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8*  mac_get_wep_default_keyvalue(mac_vap_stru *pst_mac_vap)
{
    return (&pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[mac_get_wep_default_keyid(pst_mac_vap)].auc_dot11WEPDefaultKeyValue[WLAN_WEP_KEY_VALUE_OFFSET]);
}

/*****************************************************************************
 �� �� ��  : mset_wep_key_value
 ��������  : ��һ����Կд��mib����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_set_wep_key_value(mac_vap_stru *pst_mac_vap, oal_uint8 uc_idx, OAL_CONST oal_uint8 *puc_key, oal_uint8 uc_size)
{
    oal_uint8 *puc_dot11WEPDefaultKeyValue;

    puc_dot11WEPDefaultKeyValue = pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue;
    puc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET] = uc_size;

    switch(uc_size)
    {
        case 40:
            uc_size = 5;
            break;
        case 104:
            uc_size = 13;
            break;
        default:
            uc_size = 5;
            break;
    }

    oal_memcopy(&puc_dot11WEPDefaultKeyValue[WLAN_WEP_KEY_VALUE_OFFSET], puc_key, uc_size);
}

/*****************************************************************************
 �� �� ��  : mac_get_wep_key_value
 ��������  : ��ȡwep key��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��24��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8*  mac_get_wep_key_value(mac_vap_stru *pst_mac_vap, oal_uint8 uc_idx)
{
    return (&pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue[WLAN_WEP_KEY_VALUE_OFFSET]);
}

/*****************************************************************************
 �� �� ��  : mac_get_wep_type
 ��������  : ��ȡwep type��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��18��
    ��    ��   : l00218984
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_ciper_protocol_type_enum_uint8 mac_get_wep_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_id)
{
    wlan_ciper_protocol_type_enum_uint8 en_cipher_type = WLAN_80211_CIPHER_SUITE_NO_ENCRYP;

    switch(mac_get_wep_keysize(pst_mac_vap,uc_key_id))
    {
        case 40:
            en_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_40;
            break;
        case 104:
            en_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_104;
            break;
		default:
			en_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_40;
			break;
    }
    return en_cipher_type;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_DeauthenticateReason
 ��������  : ��¼ȥ��֤ԭ��
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
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_DeauthenticateReason(mac_vap_stru *pst_mac_vap, oal_uint16 us_err_code)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DeauthenticateReason = (oal_uint32)us_err_code;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_DeauthenticateStation
 ��������  : ��¼ȥ��֤վ���ַ
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
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_DeauthenticateStation(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da)
{
    oal_memcopy(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DeauthenticateStation, puc_da, 6);
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_DeauthenticateStation
 ��������  : ��¼��֤ʧ�ܵ�STA��ַ
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
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_AuthenticateFailStation(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da)
{
    oal_memcopy(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11AuthenticateFailStation, puc_da, 6);
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_DeauthenticateReason
 ��������  : ��¼��֤ʧ��ԭ��
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
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_AuthenticateFailStatus(mac_vap_stru *pst_mac_vap, oal_uint16 us_err_code)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AuthenticateFailStatus = (oal_uint32)us_err_code;
}


/*****************************************************************************
 �� �� ��  : mac_mib_set_DisassocStation
 ��������  : ��¼ȥ������ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_DisassocStation(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_da)
{
    oal_memcopy(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DisassociateStation, puc_da, 6);
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_DisassocReason
 ��������  : ��¼ȥ����ԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_DisassocReason(mac_vap_stru *pst_mac_vap, oal_uint16 us_err_code)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DisassociateReason = (oal_uint32)us_err_code;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_StationID
 ��������  : ��ȡMIB�� dot11StationID ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : MAC��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 *mac_mib_get_StationID(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_StationID
 ��������  : ����MIB�� dot11StationID ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             puc_sta_id : MAC��ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��20��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_StationID(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_sta_id)
{
    oal_set_mac_addr(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID, puc_sta_id);
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_OBSSScanPassiveDwell
 ��������  : ��ȡMIB�� dot11OBSSScanPassiveDwell ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11OBSSScanPassiveDwell
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanPassiveDwell(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveDwell;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_OBSSScanPassiveDwell
 ��������  : ����MIB�� dot11OBSSScanPassiveDwell ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             ul_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanPassiveDwell(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveDwell = ul_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_OBSSScanActiveDwell
 ��������  : ��ȡMIB�� dot11OBSSScanActiveDwell ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11OBSSScanActiveDwell
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanActiveDwell(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveDwell;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_OBSSScanActiveDwell
 ��������  : ����MIB�� dot11OBSSScanActiveDwell ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             ul_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanActiveDwell(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveDwell = ul_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_BSSWidthTriggerScanInterval
 ��������  : ��ȡMIB�� dot11BSSWidthTriggerScanInterval ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11BSSWidthTriggerScanInterval
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_BSSWidthTriggerScanInterval(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthTriggerScanInterval;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_BSSWidthTriggerScanInterval
 ��������  : ����MIB�� dot11BSSWidthTriggerScanInterval ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             ul_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_BSSWidthTriggerScanInterval(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthTriggerScanInterval = ul_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_OBSSScanPassiveTotalPerChannel
 ��������  : ��ȡMIB�� dot11OBSSScanPassiveTotalPerChannel ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11OBSSScanPassiveTotalPerChannel
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanPassiveTotalPerChannel(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveTotalPerChannel;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_OBSSScanPassiveTotalPerChannel
 ��������  : ����MIB�� dot11OBSSScanPassiveTotalPerChannel ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             ul_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanPassiveTotalPerChannel(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanPassiveTotalPerChannel = ul_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_OBSSScanActiveTotalPerChannel
 ��������  : ��ȡMIB�� dot11OBSSScanActiveTotalPerChannel ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11OBSSScanActiveTotalPerChannel
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanActiveTotalPerChannel(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveTotalPerChannel;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_OBSSScanActiveTotalPerChannel
 ��������  : ����MIB�� dot11OBSSScanActiveTotalPerChannel ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             ul_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanActiveTotalPerChannel(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActiveTotalPerChannel = ul_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_BSSWidthChannelTransitionDelayFactor
 ��������  : ��ȡMIB�� dot11BSSWidthChannelTransitionDelayFactor ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11BSSWidthChannelTransitionDelayFactor
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_BSSWidthChannelTransitionDelayFactor(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthChannelTransitionDelayFactor;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_BSSWidthChannelTransitionDelayFactor
 ��������  : ����MIB�� dot11BSSWidthChannelTransitionDelayFactor ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             ul_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_BSSWidthChannelTransitionDelayFactor(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11BSSWidthChannelTransitionDelayFactor = ul_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_OBSSScanActivityThreshold
 ��������  : ��ȡMIB�� dot11OBSSScanActivityThreshold ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11OBSSScanActivityThreshold
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  mac_mib_get_OBSSScanActivityThreshold(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActivityThreshold;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_OBSSScanActivityThreshold
 ��������  : ����MIB�� dot11OBSSScanActivityThreshold ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             ul_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OBSSScanActivityThreshold(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11OBSSScanActivityThreshold = ul_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_HighThroughputOptionImplemented
 ��������  : ��ȡMIB�� dot11HighThroughputOptionImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11HighThroughputOptionImplemented
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_HighThroughputOptionImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_HighThroughputOptionImplemented
 ��������  : ����MIB�� dot11HighThroughputOptionImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             en_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_HighThroughputOptionImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = en_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_VHTOptionImplemented
 ��������  : ��ȡMIB�� dot11VHTOptionImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11VHTOptionImplemented
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��13��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_VHTOptionImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_VHTChannelWidthOptionImplemented
 ��������  : ��ȡMIB�� dot11VHTChannelWidthOptionImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11VHTChannelWidthOptionImplemented
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_mib_get_VHTChannelWidthOptionImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_phy_vht.uc_dot11VHTChannelWidthOptionImplemented;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_dot11FortyMHzOperationImplemented
 ��������  : ��ȡMIB�� dot11FortyMHzOperationImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11FortyMHzOperationImplemented
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_FortyMHzOperationImplemented(mac_vap_stru *pst_mac_vap)
{
    return (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band) ?
            pst_mac_vap->pst_mib_info->st_phy_ht.en_dot112GFortyMHzOperationImplemented :
            pst_mac_vap->pst_mib_info->st_phy_ht.en_dot115GFortyMHzOperationImplemented;/* [false alarm]:����ֵ��oal_bool_enum_uint8 �ͺ�������һ��*/
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_dot11FortyMHzOperationImplemented
 ��������  : ����MIB�� dot11FortyMHzOperationImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             en_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_FortyMHzOperationImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
    {
        pst_mac_vap->pst_mib_info->st_phy_ht.en_dot112GFortyMHzOperationImplemented = en_val;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_phy_ht.en_dot115GFortyMHzOperationImplemented = en_val;
    }
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_SpectrumManagementImplemented
 ��������  : ��ȡMIB�� dot11SpectrumManagementImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11SpectrumManagementImplemented
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_SpectrumManagementImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementImplemented;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_SpectrumManagementImplemented
 ��������  : ����MIB�� dot11SpectrumManagementImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             en_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_SpectrumManagementImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementImplemented = en_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_FortyMHzIntolerant
 ��������  : ��ȡMIB�� dot11FortyMHzIntolerant ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11FortyMHzIntolerant
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_FortyMHzIntolerant(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11FortyMHzIntolerant;
}



/*****************************************************************************
 �� �� ��  : mac_mib_set_FortyMHzIntolerant
 ��������  : ����MIB�� dot11FortyMHzIntolerant ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             en_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_FortyMHzIntolerant(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11FortyMHzIntolerant = en_val;
}


/*****************************************************************************
 �� �� ��  : mac_mib_get_2040BSSCoexistenceManagementSupport
 ��������  : ��ȡMIB�� dot112040BSSCoexistenceManagementSupport ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot112040BSSCoexistenceManagementSupport
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_2040BSSCoexistenceManagementSupport(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot112040BSSCoexistenceManagementSupport;
}
 /*****************************************************************************
 �� �� ��  : mac_mib_get_dot11RSNAActivated
 ��������  : ��ȡMIB�� dot11RSNAActivated ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11RSNAActivated
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_dot11RSNAActivated(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_dot11RSNAProtectedManagementFramesActivated
 ��������  : ��ȡMIB�� dot11RSNAProtectedManagementFramesActivated ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11RSNAProtectedManagementFramesActivated
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_dot11RSNAProtectedManagementFramesActivated(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RSNAProtectedManagementFramesActivated;
}
/*****************************************************************************
 �� �� ��  : mac_mib_get_dot11RSNAMFPC
 ��������  : ��ȡMIB�� dot11RSNAMFPC ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11RSNAMFPC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_dot11RSNAMFPC(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC;
}
/*****************************************************************************
 �� �� ��  : mac_mib_get_dot11RSNAMFPR
 ��������  : ��ȡMIB�� dot11RSNAMFPR ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11RSNAMFPR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_dot11RSNAMFPR(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR;
}
/*****************************************************************************
 �� �� ��  : mac_mib_set_dot11RSNAActivated
 ��������  : ����MIB�� dot11RSNAActivated ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11RSNAActivated(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated = ul_val;
}
/*****************************************************************************
 �� �� ��  : mac_mib_set_dot11RSNAProtectedManagementFramesActivated
 ��������  : ����MIB�� dot11RSNAProtectedManagementFramesActivated ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11RSNAProtectedManagementFramesActivated(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RSNAProtectedManagementFramesActivated = ul_val;
}
/*****************************************************************************
 �� �� ��  : mac_mib_set_dot11RSNAMFPC
 ��������  : ����MIB�� dot11RSNAMFPC ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11RSNAMFPC(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 ul_val)
{
   pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC = ul_val;
}
/*****************************************************************************
 �� �� ��  : mac_mib_set_dot11RSNAMFPR
 ��������  : ����MIB�� dot11RSNAMFPR��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11RSNAMFPR(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR = ul_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_dot11AssociationSAQueryMaximumTimeout
 ��������  : ��ȡMIB�� dot11AssociationSAQueryMaximumTimeout ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11AssociationSAQueryMaximumTimeout
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 mac_mib_get_dot11AssociationSAQueryMaximumTimeout(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryMaximumTimeout;
}
/*****************************************************************************
 �� �� ��  : mac_mib_get_dot11AssociationSAQueryRetryTimeout
 ��������  : ��ȡMIB�� dot11AssociationSAQueryRetryTimeout ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11AssociationSAQueryRetryTimeout
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 mac_mib_get_dot11AssociationSAQueryRetryTimeout(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryRetryTimeout;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_dot11AssociationSAQueryMaximumTimeout
 ��������  : ����MIB�� dot11AssociationSAQueryMaximumTimeout ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11AssociationSAQueryMaximumTimeout(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryMaximumTimeout = ul_val;
}
/*****************************************************************************
 �� �� ��  : mac_mib_set_dot11AssociationSAQueryRetryTimeout
��������  : ����MIB�� dot11AssociationSAQueryRetryTimeout ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

�޸���ʷ      :
  1.��    ��   : 2014��4��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_dot11AssociationSAQueryRetryTimeout(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryRetryTimeout = ul_val;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_mib_set_2040BSSCoexistenceManagementSupport
 ��������  : ����MIB�� dot112040BSSCoexistenceManagementSupport ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             en_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_2040BSSCoexistenceManagementSupport(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot112040BSSCoexistenceManagementSupport = en_val;
}
/*****************************************************************************
 �� �� ��  : mac_mib_get_dot11dtimperiod
 ��������  : ��ȡMIB�� ul_dot11DTIMPeriod ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 mac_mib_get_dot11dtimperiod(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod;
}

/*****************************************************************************
 �� �� ��  : mac_mib_init_2040
 ��������  : ��ʼ��֧��2040����
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11FortyMHzIntolerant
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : zhangzhiming
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_init_2040(mac_vap_stru *pst_mac_vap)
{
    mac_mib_set_FortyMHzIntolerant(pst_mac_vap, OAL_FALSE);
    mac_mib_set_SpectrumManagementImplemented(pst_mac_vap, OAL_TRUE);
    mac_mib_set_2040BSSCoexistenceManagementSupport(pst_mac_vap, OAL_TRUE);
}

/*****************************************************************************
 �� �� ��  : mac_mib_init_obss_scan
 ��������  : ��ʼ��OBSS SCAN ����
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��14��
    ��    ��   : d00223710
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_init_obss_scan(mac_vap_stru *pst_mac_vap)
{
    mac_mib_set_OBSSScanPassiveDwell(pst_mac_vap, 20);
    mac_mib_set_OBSSScanActiveDwell(pst_mac_vap, 10);
    mac_mib_set_BSSWidthTriggerScanInterval(pst_mac_vap, 300);
    mac_mib_set_OBSSScanPassiveTotalPerChannel(pst_mac_vap, 200);
    mac_mib_set_OBSSScanActiveTotalPerChannel(pst_mac_vap, 20);
    mac_mib_set_BSSWidthChannelTransitionDelayFactor(pst_mac_vap, 5);
    mac_mib_set_OBSSScanActivityThreshold(pst_mac_vap, 25);
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_dot11dtimperiod
 ��������  : ����MIB�� ul_dot11DTIMPeriod ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             ul_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_dot11dtimperiod(mac_vap_stru *pst_mac_vap, oal_uint32 ul_val)
{
    if (ul_val != 0)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod = ul_val;
    }
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_powermanagementmode
 ��������  : ��ȡMIB�� ul_dot11DTIMPeriod ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 mac_mib_get_powermanagementmode(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.uc_dot11PowerManagementMode;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_powermanagementmode
 ��������  : ����MIB�� ul_dot11DTIMPeriod ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             ul_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��26��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_powermanagementmode(mac_vap_stru *pst_mac_vap, oal_uint8 uc_val)
{
    if (uc_val != 0)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.uc_dot11PowerManagementMode = uc_val;
    }
}

#if defined _PRE_WLAN_FEATURE_OPMODE_NOTIFY || (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
/*****************************************************************************
 �� �� ��  : mac_mib_get_OperatingModeNotificationImplemented
 ��������  : ��ȡMIB�� dot11OperatingModeNotificationImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : dot11OperatingModeNotificationImplemented
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8  mac_mib_get_OperatingModeNotificationImplemented(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11OperatingModeNotificationImplemented;
}
/*****************************************************************************
 �� �� ��  : mac_mib_set_OperatingModeNotificationImplemented
 ��������  : ����MIB�� dot11OperatingModeNotificationImplemented ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
             en_val     : ��Ҫ���õ�ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_mib_set_OperatingModeNotificationImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11OperatingModeNotificationImplemented = en_val;
}
#endif


/*****************************************************************************
 �� �� ��  : mac_mib_get_LsigTxopFullProtectionActivated
 ��������  : ��ȡLsigTxopFullProtectionActivatedֵ
 �������  : pst_mac_vap  :  mac vap�ṹ��
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 mac_mib_get_LsigTxopFullProtectionActivated(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11LSIGTXOPFullProtectionActivated);
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_LsigTxopFullProtectionActivated
 ��������  : ����LsigTxopFullProtectionActivatedֵ
 �������  : pst_mac_vap                            :  mac vap�ṹ��
             en_lsig_txop_full_protection_activated :  ��Ҫ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_LsigTxopFullProtectionActivated(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_lsig_txop_full_protection_activated)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11LSIGTXOPFullProtectionActivated = en_lsig_txop_full_protection_activated;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_NonGFEntitiesPresent
 ��������  : ��ȡNonGFEntitiesPresentֵ
 �������  : pst_mac_vap  :  mac vap�ṹ��
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 mac_mib_get_NonGFEntitiesPresent(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11NonGFEntitiesPresent);
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_NonGFEntitiesPresent
 ��������  : ����NonGFEntitiesPresentֵ
 �������  : pst_mac_vap                :  mac vap�ṹ��
             en_non_gf_entities_present :  ��Ҫ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_NonGFEntitiesPresent(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_non_gf_entities_present)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11NonGFEntitiesPresent = en_non_gf_entities_present;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_RifsMode
 ��������  : ��ȡRIFSModeֵ
 �������  : pst_mac_vap  :  mac vap�ṹ��
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 mac_mib_get_RifsMode(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11RIFSMode);
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_RifsMode
 ��������  : ����RIFSModeֵ
 �������  : pst_mac_vap             :  mac vap�ṹ��
             en_rifs_mode            :  ��Ҫ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_RifsMode(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_rifs_mode)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11RIFSMode = en_rifs_mode;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_HtProtection
 ��������  : ��ȡhtProtectionֵ
 �������  : pst_mac_vap  :  mac vap�ṹ��
 �������  : ��
 �� �� ֵ  : wlan_mib_ht_protection_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_mib_ht_protection_enum_uint8 mac_mib_get_HtProtection(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11HTProtection);
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_HtProtection
 ��������  : ����htProtectionֵ
 �������  : pst_mac_vap                 :  mac vap�ṹ��
             en_ht_protection            :  ��Ҫ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_HtProtection(mac_vap_stru *pst_mac_vap, wlan_mib_ht_protection_enum_uint8 en_ht_protection)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.en_dot11HTProtection = en_ht_protection;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_ShortPreambleOptionImplemented
 ��������  : ��ȡShortPreambleOptionImplementedֵ
 �������  : pst_mac_vap  :  mac vap�ṹ��
 �������  : ��
 �� �� ֵ  : wlan_11b_preamble_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_11b_mib_preamble_enum_uint8 mac_mib_get_ShortPreambleOptionImplemented(mac_vap_stru *pst_mac_vap)
{
    return (pst_mac_vap->pst_mib_info->st_phy_hrdsss.en_dot11ShortPreambleOptionImplemented);
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_ShortPreambleOptionImplemented
 ��������  : ����ShortPreambleOptionImplementedֵ
 �������  : pst_mac_vap                 :  mac vap�ṹ��
             en_preamble                 :  ��Ҫ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_ShortPreambleOptionImplemented(mac_vap_stru *pst_mac_vap, wlan_11b_mib_preamble_enum_uint8 en_preamble)
{
    pst_mac_vap->pst_mib_info->st_phy_hrdsss.en_dot11ShortPreambleOptionImplemented = en_preamble;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_SpectrumManagementRequired
 ��������  : ����en_dot11SpectrumManagementRequiredֵ
 �������  : pst_mac_vap            :  mac vap�ṹ��
             en_val                 :  ��Ҫ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��16��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_SpectrumManagementRequired(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementRequired = en_val;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_ShortGIOptionInFortyImplemented
 ��������  : ��ȡen_dot11ShortGIOptionInFortyImplementedֵ
 �������  : pst_mac_vap            :  mac vap�ṹ��
             en_val                 :  ��Ҫ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��16��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 mac_mib_get_ShortGIOptionInFortyImplemented(mac_vap_stru *pst_mac_vap)
{
    return (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band) ?
            pst_mac_vap->pst_mib_info->st_phy_ht.en_dot112GShortGIOptionInFortyImplemented :
            pst_mac_vap->pst_mib_info->st_phy_ht.en_dot115GShortGIOptionInFortyImplemented;/* [false alarm]:����ֵ��oal_bool_enum_uint8 �ͺ�������һ��*/
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_ShortGIOptionInFortyImplemented
 ��������  : ����en_dot11ShortGIOptionInFortyImplementedֵ
 �������  : pst_mac_vap            :  mac vap�ṹ��
             en_val                 :  ��Ҫ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��16��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_ShortGIOptionInFortyImplemented(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_val)
{
    if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
    {
        pst_mac_vap->pst_mib_info->st_phy_ht.en_dot112GShortGIOptionInFortyImplemented = en_val;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_phy_ht.en_dot115GShortGIOptionInFortyImplemented = en_val;
    }
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_frag_threshold
 ��������  : ���÷�Ƭ����ֵ
 �������  : pst_mac_vap                 :  mac vap�ṹ��
             ul_frag_threshold           :  ��Ƭ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��18��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_frag_threshold(mac_vap_stru *pst_mac_vap, oal_uint32 ul_frag_threshold)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11FragmentationThreshold = ul_frag_threshold;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_rts_threshold
 ��������  : ����RTS����ֵ
 �������  : pst_mac_vap                 :  mac vap�ṹ��
             ul_rts_threshold            :  RTS ����ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��18��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_mib_set_rts_threshold(mac_vap_stru *pst_mac_vap, oal_uint32 ul_rts_threshold)
{
    pst_mac_vap->pst_mib_info->st_wlan_mib_operation.ul_dot11RTSThreshold = ul_rts_threshold;
}

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32 mac_vap_init(
                    mac_vap_stru               *pst_vap,
                    oal_uint8                   uc_chip_id,
                    oal_uint8                   uc_device_id,
                    oal_uint8                   uc_vap_id,
                    mac_cfg_add_vap_param_stru *pst_param);
extern oal_void mac_vap_init_rates(mac_vap_stru *pst_vap);
extern oal_void mac_sta_init_bss_rates(mac_vap_stru *pst_vap, oal_void *pst_bss_dscr);
extern oal_void mac_vap_init_rates_by_protocol(mac_vap_stru *pst_vap, wlan_protocol_enum_uint8 en_vap_protocol, mac_data_rate_stru *pst_rates);
extern oal_uint32 mac_vap_exit(mac_vap_stru *pst_vap);
extern oal_uint32  mac_vap_del_user(mac_vap_stru *pst_vap, oal_uint16 us_user_idx);
extern oal_uint32  mac_vap_find_user_by_macaddr(
                mac_vap_stru        *pst_vap,
                oal_uint8           *puc_sta_mac_addr,
                oal_uint16          *pus_user_idx);

extern oal_uint32  mac_device_find_user_by_macaddr(
                mac_vap_stru        *pst_vap,
                oal_uint8           *puc_sta_mac_addr,
                oal_uint16          *pus_user_idx);

#if 0
extern oal_uint32  mac_vap_update_user(mac_vap_stru *pst_vap, oal_uint32   ul_user_dix);
#endif
extern oal_uint32  mac_vap_add_assoc_user(mac_vap_stru *pst_vap, oal_uint16 us_user_idx);


/*****************************************************************************
    mib��������
*****************************************************************************/
extern oal_uint32  mac_mib_get_beacon_period(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_get_dtim_period(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_get_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
#if 0
extern oal_uint32  mac_mib_get_GroupReceivedFrameCount(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_group_count);
#endif
extern oal_uint32  mac_mib_get_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
#if 0
extern oal_uint32  mac_mib_get_station_id(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  mac_mib_set_beacon_period(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_set_dtim_period(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_set_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#if 0
extern oal_uint32  mac_mib_set_GroupReceivedFrameCount(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_group_count);
#endif
extern oal_uint32  mac_mib_set_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_set_station_id(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
oal_void  mac_mib_clear_rsna_auth_suite(mac_vap_stru *pst_mac_vap);
oal_void  mac_mib_set_rsna_auth_suite(mac_vap_stru *pst_mac_vap, oal_uint8 uc_auth_value);
oal_void  mac_mib_get_authentication_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num);
oal_void  mac_mib_get_wpa_pairwise_cipher_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num);
oal_void  mac_mib_get_wpa2_pairwise_cipher_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num);
oal_void  mac_mib_get_wpa_pairwise_cipher_suite_value(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_pairwise_value);
oal_void  mac_mib_get_wpa2_pairwise_cipher_suite_value(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_pairwise_value);


#if 0
extern oal_uint32  mac_vap_get_user_wme_info(
                       mac_vap_stru               *pst_vap,
                       wlan_wme_ac_type_enum_uint8 en_wme_type,
                       mac_wme_param_stru         *pst_wme_info);
extern oal_uint32  mac_vap_set_user_wme_info(
                       mac_vap_stru               *pst_vap,
                       wlan_wme_ac_type_enum_uint8 en_wme_type,
                       mac_wme_param_stru         *pst_wme_info);
#endif
extern oal_uint32  mac_mib_get_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param);
extern oal_uint32  mac_mib_set_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_uint32 mac_vap_set_bssid(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_bssid);
extern oal_uint32 mac_vap_set_current_channel(mac_vap_stru *pst_vap,wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel);
extern oal_uint8  mac_vap_get_curr_baserate(mac_vap_stru *pst_mac_ap,oal_uint8 uc_br_idx);
extern oal_void  mac_vap_init_rsna_status(mac_vap_stru *pst_vap, oal_uint32 ul_idx);
extern void mibset_RSNAStatsSTAAddress(oal_uint8 *puckey, mac_vap_stru *pst_vap, oal_uint16 us_idx);
extern void mibset_RSNAStatsSelectedPairwiseCipher(oal_uint8 inp, mac_vap_stru *pst_vap, oal_uint16 us_idx);
extern void mac_mib_set_RSNAAuthenticationSuiteSelected(mac_vap_stru *pst_vap, oal_uint8 inp);
extern void mac_mib_set_RSNAPairwiseCipherSelected(mac_vap_stru *pst_vap, oal_uint8 inp);
extern void mibset_RSNAClearWpaPairwiseCipherImplemented(mac_vap_stru *pst_vap);
extern void mibset_RSNAClearWpa2PairwiseCipherImplemented(mac_vap_stru *pst_vap);
extern oal_void  mac_vap_state_change(mac_vap_stru *pst_mac_vap, mac_vap_state_enum_uint8 en_vap_state);
extern oal_uint32 mac_vap_config_vht_ht_mib_by_protocol(mac_vap_stru *pst_mac_vap);
extern oal_uint32 mac_vap_init_wme_param(mac_vap_stru *pst_mac_vap);

#ifdef _PRE_WLAN_FEATURE_SMPS
extern wlan_mib_mimo_power_save_enum_uint8 mac_mib_get_smps(mac_vap_stru *pst_mac_vap);
extern oal_uint32 mac_vap_get_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_uint32 mac_vap_get_smps_en(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param);
extern oal_void mac_vap_set_smps(mac_vap_stru *pst_vap, oal_uint8 uc_value);
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD
extern oal_uint32  mac_vap_set_uapsd_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_value);
extern oal_uint8  mac_vap_get_uapsd_en(mac_vap_stru *pst_mac_vap);
#endif
extern oal_uint32  mac_vap_init_by_protocol(mac_vap_stru *pst_mac_vap, wlan_protocol_enum_uint8 en_protocol);

extern  oal_bool_enum_uint8 mac_vap_check_bss_cap_info_phy_ap(oal_uint16 us_cap_info,mac_vap_stru *pst_mac_vap);
extern  mac_wme_param_stru  *mac_get_wmm_cfg(wlan_vap_mode_enum_uint8 en_vap_mode);
#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
extern  mac_wme_param_stru  *mac_get_wmm_cfg_multi_user_multi_ac(oal_traffic_type_enum_uint8 en_vap_mode);
#endif
extern oal_void  mac_vap_get_bandwidth_cap(mac_vap_stru *pst_mac_vap, wlan_bw_cap_enum_uint8 *pen_cap);
extern oal_void  mac_vap_change_mib_by_bandwidth(mac_vap_stru *pst_mac_vap, wlan_channel_bandwidth_enum_uint8 en_bandwidth);

extern oal_void  mac_vap_init_rx_nss_by_protocol(mac_vap_stru *pst_mac_vap);
#if 0
#ifdef _PRE_WLAN_DFT_STAT
extern oal_uint32  mac_vap_dft_stat_clear(mac_vap_stru *pst_vap);
#endif
#endif
extern oal_void mac_dec_p2p_num(mac_vap_stru *pst_vap);
extern oal_void mac_inc_p2p_num(mac_vap_stru *pst_vap);
extern oal_void mac_vap_set_p2p_mode(mac_vap_stru *pst_vap, wlan_p2p_mode_enum_uint8 en_p2p_mode);
extern wlan_p2p_mode_enum_uint8 mac_get_p2p_mode(mac_vap_stru *pst_vap);
extern oal_void mac_vap_set_aid(mac_vap_stru *pst_vap, oal_uint16 us_aid);
extern oal_void mac_vap_set_uapsd_cap(mac_vap_stru *pst_vap, oal_uint8 uc_uapsd_cap);
extern oal_void mac_vap_set_assoc_id(mac_vap_stru *pst_vap, oal_uint8 uc_assoc_vap_id);
extern oal_void mac_vap_set_tx_power(mac_vap_stru *pst_vap, oal_uint8 uc_tx_power);
extern oal_void mac_vap_set_al_tx_flag(mac_vap_stru *pst_vap, oal_bool_enum_uint8 en_flag);
extern oal_void mac_vap_set_al_tx_first_run(mac_vap_stru *pst_vap, oal_bool_enum_uint8 en_flag);
extern oal_void mac_vap_set_al_tx_payload_flag(mac_vap_stru *pst_vap, oal_uint8 uc_paylod);
extern oal_uint32 mac_dump_protection(mac_vap_stru *pst_mac_vap, oal_uint8* puc_param);
extern oal_void mac_vap_set_multi_user_idx(mac_vap_stru *pst_vap, oal_uint16 us_multi_user_idx);
#ifdef _PRE_WLAN_FEATURE_STA_PM
extern oal_void mac_vap_set_uapsd_para(mac_vap_stru *pst_mac_vap, mac_cfg_uapsd_sta_stru *pst_uapsd_info);
#endif
extern oal_void mac_vap_set_wmm_params_update_count(mac_vap_stru *pst_vap, oal_uint8 uc_update_count);
extern oal_void mac_vap_set_rifs_tx_on(mac_vap_stru *pst_vap, oal_uint8 uc_value);
#if 0
extern oal_void mac_vap_set_tdls_prohibited(mac_vap_stru *pst_vap, oal_uint8 uc_value);
extern oal_void mac_vap_set_tdls_channel_switch_prohibited(mac_vap_stru *pst_vap, oal_uint8 uc_value);
#endif
extern oal_void mac_vap_set_11ac2g(mac_vap_stru *pst_vap, oal_uint8 uc_value);
extern oal_void mac_vap_set_hide_ssid(mac_vap_stru *pst_vap, oal_uint8 uc_value);
extern oal_uint8 mac_vap_get_peer_obss_scan(mac_vap_stru *pst_vap);
extern oal_void mac_vap_set_peer_obss_scan(mac_vap_stru *pst_vap, oal_uint8 uc_value);
extern oal_uint32 mac_vap_clear_app_ie(mac_vap_stru *pst_mac_vap, en_app_ie_type_uint8 en_type);
extern oal_uint32 mac_vap_save_app_ie(mac_vap_stru *pst_mac_vap, oal_app_ie_stru *pst_app_ie, en_app_ie_type_uint8 en_type);
extern oal_void mac_vap_set_rx_nss(mac_vap_stru *pst_vap, oal_uint8 uc_rx_nss);

extern oal_uint32 mac_vap_init_privacy(mac_vap_stru                        *pst_mac_vap,
                                                mac_cfg80211_connect_security_stru     *pst_mac_security_param);

extern oal_void mac_mib_set_wep(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_id);
extern oal_bool_enum_uint8 mac_check_auth_policy(wlan_mib_ieee802dot11_stru *pst_mib_info,
                                            oal_uint8 uc_policy);
extern mac_user_stru  *mac_vap_get_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr);
extern oal_uint32 mac_vap_add_beacon(mac_vap_stru * pst_mac_vap, mac_beacon_param_stru * pst_beacon_param);
extern oal_uint32 mac_vap_add_key(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 uc_key_id, mac_key_params_stru *pst_key);
extern oal_uint8 mac_vap_get_default_key_id(mac_vap_stru *pst_mac_vap);
extern oal_uint32 mac_vap_set_default_key(mac_vap_stru *pst_mac_vap, oal_uint8  uc_key_index);
extern oal_uint32 mac_vap_set_default_mgmt_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index);
extern void mac_vap_init_user_security_port(mac_vap_stru  *pst_mac_vap,
                                        mac_user_stru *pst_mac_user);
extern oal_uint32 mac_vap_set_beacon(mac_vap_stru * pst_mac_vap, mac_beacon_param_stru * pst_beacon_param);
extern oal_uint8* mac_vap_get_mac_addr(mac_vap_stru *pst_mac_vap);
#ifdef _PRE_WLAN_FEATURE_11R
extern oal_uint32 mac_mib_init_ft_cfg(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mde);
extern oal_uint32 mac_mib_get_md_id(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_mdid);
#if 0
extern oal_uint32 mac_vap_set_pmksa(mac_vap_stru *pst_mac_vap, mac_pmksa_stru *pst_mac_pmksa);
extern oal_uint32 mac_vap_del_pmksa(mac_vap_stru *pst_mac_vap, mac_pmksa_stru *pst_mac_pmksa);
extern oal_uint32 mac_vap_flush_pmksa(mac_vap_stru *pst_mac_vap);
extern mac_pmkid_info_stu *mac_vap_get_pmksa(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_bssid);
#endif
#endif //_PRE_WLAN_FEATURE_11R
extern oal_switch_enum_uint8 mac_vap_protection_autoprot_is_enabled(mac_vap_stru *pst_mac_vap);
extern wlan_prot_mode_enum_uint8 mac_vap_get_user_protection_mode(mac_vap_stru *pst_mac_vap_sta, mac_user_stru *pst_mac_user);
extern oal_void mac_protection_set_rts_tx_param(mac_vap_stru *pst_mac_vap,oal_switch_enum_uint8 en_flag,
                                        wlan_prot_mode_enum_uint8 en_prot_mode,mac_cfg_rts_tx_param_stru *pst_rts_tx_param);

extern oal_bool_enum mac_protection_lsigtxop_check(mac_vap_stru *pst_mac_vap);
extern oal_void mac_protection_set_lsig_txop_mechanism(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_flag);

#ifdef _PRE_WLAN_FEATURE_VOWIFI
extern oal_uint32 mac_vap_set_vowifi_param(mac_vap_stru *pst_mac_vap, mac_vowifi_cmd_enum_uint8 en_vowifi_cfg_cmd, oal_uint8 uc_value);
#endif /* _PRE_WLAN_FEATURE_VOWIFI */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_vap.h */
