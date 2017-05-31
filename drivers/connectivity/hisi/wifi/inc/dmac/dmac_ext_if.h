/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_ext_if.h
  �� �� ��   : ����
  ��    ��   : ������
  ��������   : 2012��9��20��
  ����޸�   :
  ��������   : dmac���⹫���ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��20��
    ��    ��   : ������
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_EXT_IF_H__
#define __DMAC_EXT_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "oal_mm.h"
#include "oal_net.h"
#include "frw_ext_if.h"
#include "wal_ext_if.h"
#include "wlan_types.h"
#include "mac_frame.h"
#include "mac_device.h"
#include "mac_user.h"
#include "mac_vap.h"


#ifdef _PRE_WLAN_RF_110X_CALI_DPD
//#include "hmac_cali_dpd.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_EXT_IF_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if defined (_PRE_PRODUCT_ID_HI110X_HOST) || defined (_PRE_PRODUCT_ID_HI110X_DEV)
/* DTS2016071304201:�޸Ĵ���BA ��Ҫ�ȷ�10 ��֡�����P2P 6.1.12 ��֤��������ִ�л�ִ��ʱ�䳤��Э��ջ����ARP ֡ʹ����֤ʧ������ */
#define DMAC_UCAST_FRAME_TX_COMP_TIMES      10         /* ����BA�Ựǰ����Ҫ��������֡�ķ�������ж� */
#else
#define DMAC_UCAST_FRAME_TX_COMP_TIMES      5          /* ����BA�Ựǰ����Ҫ��������֡�ķ�������ж� */
#endif /* _PRE_PRODUCT_ID_HI110X_DEV */

#define DMAC_BA_SEQNO_MASK                  0x0FFF      /* max sequece number */
#define DMAC_BA_MAX_SEQNO_BY_TWO            2048
#define DMAC_BA_RX_ALLOW_MIN_SEQNO_BY_TWO   64
#define DMAC_BA_RX_ALLOW_MAX_SEQNO_BY_TWO   4032

#define DMAC_BA_GREATER_THAN_SEQHI          1
#define DMAC_BA_BETWEEN_SEQLO_SEQHI         2
#define DMAC_BA_AMSDU_BACK_SUPPORTED_FLAG   1           /* BA�Ự��AMSDU��֧�ֱ�ʶ */

#define DMAC_BA_DELBA_TIMEOUT               0
#define DMAC_BATX_WIN_STALL_THRESHOLD       6

#define MAC_TX_CTL_SIZE                     OAL_NETBUF_CB_SIZE()

#define DMAC_BA_SEQ_ADD(_seq1, _seq2)       (((_seq1) + (_seq2)) & DMAC_BA_SEQNO_MASK)
#define DMAC_BA_SEQ_SUB(_seq1, _seq2)       (((_seq1) - (_seq2)) & DMAC_BA_SEQNO_MASK)
#define DMAC_BA_SEQNO_ADD(_seq1, _seq2)     (((_seq1) + (_seq2)) & DMAC_BA_SEQNO_MASK)
#define DMAC_BA_SEQNO_SUB(_seq1, _seq2)     (((_seq1) - (_seq2)) & DMAC_BA_SEQNO_MASK)

#define DMAC_BA_BMP_SIZE                    64

#define DMAC_IS_BA_INFO_PRESENT(_flags)     (_flags & BIT0)

#define DMAC_INVALID_SIGNAL_DELTA      (30)
#define DMAC_RSSI_SIGNAL_MIN           (-103)    /*�ź�ǿ�ȼ�Сֵ */
#define DMAC_RSSI_SIGNAL_MAX           (5)       /*�ź�ǿ�ȼ���ֵ */
#define DMAC_INVALID_SIGNAL_INITIAL    (100)     /*�Ƿ���ʼ�źż���ֵ*/

#define DMAC_INVALID_BA_LUT_INDEX           HAL_MAX_BA_LUT_SIZE

#define DMAC_AMPDU_LUT_IDX_BMAP_LEN         ((HAL_MAX_AMPDU_LUT_SIZE >> 3) + 1) /* 255 / 8 + 1 */
#define DMAC_INVALID_AMPDU_LUT_INDEX        (0)

/* ����BA���ڼ�¼seq number����������������2���������� */
#define DMAC_TID_MAX_BUFS       128
/* ����BA���ڼ�¼seq number��bitmap��ʹ�õ����ͳ��� */
#define DMAC_TX_BUF_BITMAP_WORD_SIZE        32
/* ����BA���ڼ�¼seq number��bit map�ĳ��� */
#define DMAC_TX_BUF_BITMAP_WORDS \
    ((DMAC_TID_MAX_BUFS+DMAC_TX_BUF_BITMAP_WORD_SIZE-1) / DMAC_TX_BUF_BITMAP_WORD_SIZE)

/* ��ȫ���� :  bss_info �м�¼AP ������ʶ�� WPA or WPA2*/
#define DMAC_WPA_802_11I    BIT0
#define DMAC_RSNA_802_11I   BIT1

#define DMAC_TX_MAX_RISF_NUM    6
#define DMAC_TX_QUEUE_AGGR_DEPTH     2
#define DMAX_TX_QUEUE_SINGLE_DEPTH   2
#define DMAC_TX_QEUEU_MAX_PPDU_NUM   2
#define DMAC_TX_QUEUE_UAPSD_DEPTH    6
#define DMAC_TX_QUEUE_FAIL_CHECK_NUM    1000
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
#define DMAC_TID_STATS_INCR(_member, _cnt)      ((_member) += (_cnt))
#else
#define DMAC_TID_STATS_INCR(_member, _cnt)
#endif
#else
#define DMAC_TID_STATS_INCR(_member, _cnt)
#endif
#if (!defined(_PRE_PRODUCT_ID_HI110X_DEV))
#define MAX_TX_USER_IDX 0XFFFF
#else
#define MAX_TX_USER_IDX 0x000F
#endif

#define DMAC_PA_ERROR_OFFSET 3

#if (defined(_PRE_DEBUG_MODE) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE))
extern oal_uint32 g_ul_desc_addr[HAL_TX_QUEUE_BUTT];
#endif

extern mac_board_stru g_st_dmac_board;
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
  ö����  : dmac_tx_host_drx_subtype_enum_uint8
  Э����:
  ö��˵��: HOST DRX�¼������Ͷ���
*****************************************************************************/
/* WLAN_CRX�����Ͷ��� */
typedef enum
{
    DMAC_TX_HOST_DRX = 0,
    HMAC_TX_HOST_DRX = 1,

    DMAC_TX_HOST_DRX_BUTT
}dmac_tx_host_drx_subtype_enum;
typedef oal_uint8 dmac_tx_host_drx_subtype_enum_uint8;

/*****************************************************************************
  ö����  : dmac_tx_wlan_dtx_subtype_enum_uint8
  Э����:
  ö��˵��: WLAN DTX�¼������Ͷ���
*****************************************************************************/
typedef enum
{
    DMAC_TX_WLAN_DTX = 0,

    DMAC_TX_WLAN_DTX_BUTT
}dmac_tx_wlan_dtx_subtype_enum;
typedef oal_uint8 dmac_tx_wlan_dtx_subtype_enum_uint8;

/*****************************************************************************
  ö����  : dmac_wlan_ctx_event_sub_type_enum_uint8
  Э����:
  ö��˵��: WLAN CTX�¼������Ͷ���
*****************************************************************************/
typedef enum
{
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_ACTION = 0,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_ADD_USER,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_NOTIFY_ALG_ADD_USER,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_DEL_USER,

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_BA_SYNC,      /* �յ�wlan��Delba��addba rsp���ڵ�dmac��ͬ�� */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_PRIV_REQ,  /* 11N�Զ����������¼����� */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCAN_REQ,              /* ɨ������ */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCHED_SCAN_REQ,        /* PNO����ɨ������ */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_MGMT,      /* ����֡���� */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_RESET_PSM, /* �յ���֤���� �������󣬸�λ�û��Ľ���״̬ */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_SET_REG,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_JOIN_DTIM_TSF_REG,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_CONN_RESULT,       /* ������� */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_ASOC_WRITE_REG, /* AP�ദ�����ʱ���޸�SEQNUM_DUPDET_CTRL�Ĵ���*/

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_EDCA_REG,  /* STA�յ�beacon��assoc rspʱ������EDCA�Ĵ��� */
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_STA_SET_DEFAULT_VO_REG,/* ���AP����WMM�ģ���STA��ȥʹ��EDCA�Ĵ�����������VO�Ĵ��� */

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SWITCH_TO_NEW_CHAN,          /* �л������ŵ��¼� */
    DMAC_WALN_CTX_EVENT_SUB_TYPR_SELECT_CHAN,                 /* �����ŵ��¼� */
    DMAC_WALN_CTX_EVENT_SUB_TYPR_DISABLE_TX,                  /* ��ֹӲ������ */
    DMAC_WALN_CTX_EVENT_SUB_TYPR_ENABLE_TX,                   /* �ָ�Ӳ������ */
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_RESTART_NETWORK,             /* �л��ŵ��󣬻ָ�BSS������ */
#ifdef _PRE_WLAN_FEATURE_DFS
#ifdef _PRE_WLAN_FEATURE_OFFCHAN_CAC
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_OFF_CHAN,          /* �л���offchan��off-chan cac��� */
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_SWITCH_TO_HOME_CHAN,         /* �л�home chan */
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_DFS_TEST,
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_SMPS,
#endif

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_PSM_OPMODE_NOTIFY,       /* AP��opmode notify֡ʱ�жϽ�����Ϣ */
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_RX_FILTER,

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    DMAC_WLAN_CTX_EVENT_SUB_TYPR_EDCA_OPT,                /* edca�Ż���ҵ��ʶ��֪ͨ�¼� */
#endif
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_DPD_DATA_PROCESSED,
#endif
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_CALI_HMAC2DMAC,
    DMAC_WLAN_CTX_EVENT_SUB_TYPE_DSCR_OPT,

    DMAC_WLAN_CTX_EVENT_SUB_TYPE_BUTT
}dmac_wlan_ctx_event_sub_type_enum;
typedef oal_uint8 dmac_wlan_ctx_event_sub_type_enum_uint8;

/* DMACģ�� WLAN_DRX�����Ͷ��� */
typedef enum
{
    DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_AP,     /* APģʽ: DMAC WLAN DRX ���� */
    DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_STA,    /* STAģʽ: DMAC WLAN DRX ���� */
    DMAC_WLAN_DRX_EVENT_SUB_TYPE_TKIP_MIC_FAILE,/* DMAC tkip mic faile �ϱ���HMAC */

    DMAC_WLAN_DRX_EVENT_SUB_TYPE_BUTT
}dmac_wlan_drx_event_sub_type_enum;
typedef oal_uint8 dmac_wlan_drx_event_sub_type_enum_uint8;

/* DMACģ�� WLAN_CRX�����Ͷ��� */
typedef enum
{
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_INIT,      /* DMAC �� HMAC�ĳ�ʼ������ */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_RX,        /* DMAC WLAN CRX ���� */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_DELBA,     /* DMAC���������DELBA֡ */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_EVERY_SCAN_RESULT,  /* ɨ�赽һ��bss��Ϣ���ϱ���� */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP,          /* DMACɨ������ϱ���HMAC */
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_OBSS_SCAN_COMP,     /* DMAC OBSSɨ������ϱ���HMAC */
#endif
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_CHAN_RESULT,        /* �ϱ�һ���ŵ���ɨ���� */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_ACS_RESP,           /* DMAC ACS �ظ�Ӧ�ò�����ִ�н����HMAC */

#ifdef _PRE_WLAN_FEATURE_FLOWCTL
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_FLOWCTL_BACKP,     /* dmac��hmac���������Ʒ�ѹ��Ϣ */
#endif
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_DISASSOC,  /* DMAC�ϱ�ȥ�����¼���HMAC, HMAC��ɾ���û� */
    DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH,    /* DMAC�ϱ�ȥ��֤�¼���HMAC */

    DMAC_WLAN_CRX_EVENT_SUB_TYPR_CH_SWITCH_COMPLETE,   /* �ŵ��л�����¼� */
    DMAC_WLAN_CRX_EVENT_SUB_TYPR_DBAC,                 /* DBAC enable/disable�¼� */
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    DMAC_TO_HMAC_DPD_CALIBRATED_DATA_SEND,
#endif

    DMAC_WLAN_CRX_EVENT_SUB_TYPE_BUTT
}dmac_wlan_crx_event_sub_type_enum;
typedef oal_uint8 dmac_wlan_crx_event_sub_type_enum_uint8;

/* TBTT�¼������Ͷ��� */
typedef enum
{
    DMAC_TBTT_EVENT_SUB_TYPE,

    DMAC_TBTT_EVENT_SUB_TYPE_BUTT
}dmac_tbtt_event_sub_type_enum;
typedef oal_uint8 dmac_tbtt_event_sub_type_enum_uint8;

/* ����HOST��������¼� */
typedef enum
{
    DMAC_TO_HMAC_SYN_UP_REG_VAL = 1,//FRW_SDT_REG_EVENT_LOG_SYN_SUB_TYPE = 0
    DMAC_TO_HMAC_CREATE_BA,
    DMAC_TO_HMAC_DEL_BA,
    DMAC_TO_HMAC_SYN_CFG,
#ifdef _PRE_WLAN_CHIP_TEST_ALG
    DMAC_TO_HMAC_ALG_TEST,
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    DMAC_TO_HMAC_ALG_INFO_SYN,
    DMAC_TO_HMAC_VOICE_AGGR,
#endif

    DMAC_TO_HMAC_SYN_BUTT
}dmac_to_hmac_syn_type_enum;

/* MISC��ɢ�¼� */
typedef enum
{
    DMAC_MISC_SUB_TYPE_RADAR_DETECT,
    DMAC_MISC_SUB_TYPE_DISASOC,
    DMAC_MISC_SUB_TYPE_CALI_TO_HMAC,
    DMAC_MISC_SUB_TYPE_HMAC_TO_CALI,


#ifdef _PRE_WLAN_FEATURE_ROAM
    DMAC_MISC_SUB_TYPE_ROAM_TRIGGER,
#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_SUPPORT_ACS
    DMAC_MISC_SUB_TYPE_RESCAN,
#endif

    DMAC_MISC_SUB_TYPE_BUTT
}dmac_misc_sub_type_enum;

typedef enum{
    DMAC_DISASOC_MISC_LINKLOSS = 0,
    DMAC_DISASOC_MISC_KEEPALIVE = 1,
    DMAC_DISASOC_MISC_CHANNEL_MISMATCH = 2,
    DMAC_DISASOC_MISC_BUTT
}dmac_disasoc_misc_reason_enum;
typedef oal_uint16 dmac_disasoc_misc_reason_enum_uint16;


/* HMAC to DMACͬ������ */
typedef enum
{
    HMAC_TO_DMAC_SYN_INIT,
    HMAC_TO_DMAC_SYN_CREATE_CFG_VAP,
    HMAC_TO_DMAC_SYN_CFG,
    HMAC_TO_DMAC_SYN_ALG,
    HMAC_TO_DMAC_SYN_REG,

    HMAC_TO_DMAC_SYN_BUTT
}hmac_to_dmac_syn_type_enum;
typedef oal_uint8 hmac_to_dmac_syn_type_enum_uint8;

/* TXRX�����ص����ζ��� */
typedef enum
{
    DMAC_TXRX_PASS = 0,     /* �������� */
    DMAC_TXRX_DROP = 1,     /* ��Ҫ���� */
    DMAC_TXRX_SENT = 2,     /* �ѱ����� */
    DMAC_TXRX_BUFF = 3,     /* �ѱ����� */

    DMAC_TXRX_BUTT
}dmac_txrx_output_type_enum;
typedef oal_uint8 dmac_txrx_output_type_enum_uint8;


/* ����ѵ��״̬ */
typedef enum
{
    DMAC_USER_SMARTANT_NON_TRAINING        = 0,
    DMAC_USER_SMARTANT_NULLDATA_TRAINING   = 1,
    DMAC_USER_SMARTANT_DATA_TRAINING       = 2,

    DMAC_USER_SMARTANT_TRAINING_BUTT
}dmac_user_smartant_training_enum;
typedef oal_uint8 dmac_user_smartant_training_enum_uint8;

/* �㷨�ı���̽���־ (ע:����1102��ö��ֻ����ʹ��3bit�ռ�, �����Чö��ֵ���Ϊ7) */
typedef enum
{
    DMAC_USER_ALG_NON_PROBE                     = 0,    /* ��̽�ⱨ�� */
    DMAC_USER_ALG_TXBF_SOUNDING                 = 1,    /* TxBf sounding���� */
    DMAC_USER_ALG_AUOTRATE_PROBE                = 2,    /* Autorate̽�ⱨ�� */
    DMAC_USER_ALG_AGGR_PROBE                    = 3,    /* �ۺ�̽�ⱨ�� */
    DMAC_USER_ALG_TPC_PROBE                     = 4,    /* TPC̽�ⱨ�� */
    DMAC_USER_ALG_TX_MODE_PROBE                 = 5,    /* ����ģʽ̽�ⱨ��(TxBf, STBC, Chain) */
    DMAC_USER_ALG_SMARTANT_NULLDATA_PROBE       = 6,    /* ��������NullDataѵ������ */
    DMAC_USER_ALG_SMARTANT_DATA_PROBE           = 7,    /* ��������Dataѵ������ */

    DMAC_USER_ALG_PROBE_BUTT
}dmac_user_alg_probe_enum;
typedef oal_uint8 dmac_user_alg_probe_enum_uint8;

/* BA�Ự��״̬ö�� */
typedef enum
{
    DMAC_BA_INIT        = 0,    /* BA�Ựδ���� */
    DMAC_BA_INPROGRESS,         /* BA�Ự���������� */
    DMAC_BA_COMPLETE,           /* BA�Ự������� */
    DMAC_BA_HALTED,             /* BA�Ự������ͣ */
    DMAC_BA_FAILED,             /* BA�Ự����ʧ�� */

    DMAC_BA_BUTT
}dmac_ba_conn_status_enum;
typedef oal_uint8 dmac_ba_conn_status_enum_uint8;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* Type of Tx Descriptor status */
typedef enum
{
      DMAC_TX_INVALID   = 0,                /*��Ч*/
      DMAC_TX_SUCC,                         /*�ɹ�*/
      DMAC_TX_FAIL,                         /*����ʧ�ܣ������ش����ƣ�������Ӧ֡��ʱ��*/
      DMAC_TX_TIMEOUT,                      /*lifetime��ʱ��û���ͳ�ȥ��*/
      DMAC_TX_RTS_FAIL,                     /*RTS ����ʧ�ܣ������ش����ƣ�����cts��ʱ��*/
      DMAC_TX_NOT_COMPRASS_BA,              /*�յ���BA�Ƿ�ѹ����ȷ��*/
      DMAC_TX_TID_MISMATCH,                 /*�յ���BA��TID�뷢��ʱ��д���������е�TID��һ��*/
      DMAC_TX_KEY_SEARCH_FAIL,              /* Key search failed*/
      DMAC_TX_AMPDU_MISMATCH,               /*�������쳣*/
      DMAC_TX_PENDING,                      /*tx pending��mac���͹���֡������û�гɹ����ȴ��ش�*/
      DMAC_TX_FAIL_ACK_ERROR,               /*����ʧ�ܣ������ش����ƣ����յ�����Ӧ֡����*/
      DMAC_TX_RTS_FAIL_CTS_ERROR,           /*RTS����ʧ�ܣ������ش����ƣ����յ���CTS����*/
      DMAC_TX_FAIL_ABORT,                   /*����ʧ�ܣ���Ϊabort��*/
      DMAC_TX_FAIL_STATEMACHINE_PHY_ERROR,  /*MAC���͸�֡�쳣������״̬����ʱ��phy��ǰ������ԭ��*/
      DMAC_TX_SOFT_PSM_BACK,                /*������ܻ���*/
      DMAC_TX_SOFT_RESERVE,              /*reserved*/
} dmac_tx_dscr_status_enum;
#else
/* Type of Tx Descriptor status */
typedef enum
{
      DMAC_TX_INVALID   = 0,
      DMAC_TX_SUCC,
      DMAC_TX_FAIL,
      DMAC_TX_TIMEOUT,
      DMAC_TX_RTS_FAIL,
      DMAC_TX_NOT_COMPRASS_BA,
      DMAC_TX_TID_MISMATCH,
      DMAC_TX_KEY_SEARCH_FAIL,
      DMAC_TX_AMPDU_MISMATCH,
      DMAC_TX_PENDING,
      DMAC_TX_SOFT_PSM_BACK,    /*������ܻ���*/
      DMAC_TX_SOFT_RESET_BACK,  /*���RESET����*/
} dmac_tx_dscr_status_enum;
#endif
typedef oal_uint8 dmac_tx_dscr_status_enum_uint8;

typedef enum
{
    DMAC_TX_MODE_NORMAL  = 0,
    DMAC_TX_MODE_RIFS    = 1,
    DMAC_TX_MODE_AGGR    = 2,
    DMAC_TX_MODE_BUTT
}dmac_tx_mode_enum;
typedef oal_uint8 dmac_tx_mode_enum_uint8;

/* mib index���� */
typedef enum
{
    WLAN_MIB_INDEX_LSIG_TXOP_PROTECTION_OPTION_IMPLEMENTED,
    WLAN_MIB_INDEX_HT_GREENFIELD_OPTION_IMPLEMENTED,
    WLAN_MIB_INDEX_SPEC_MGMT_IMPLEMENT,
    WLAN_MIB_INDEX_FORTY_MHZ_OPERN_IMPLEMENT,
    WLAN_MIB_INDEX_2040_COEXT_MGMT_SUPPORT,
    WLAN_MIB_INDEX_FORTY_MHZ_INTOL,
    WLAN_MIB_INDEX_VHT_CHAN_WIDTH_OPTION_IMPLEMENT,
    WLAN_MIB_INDEX_MINIMUM_MPDU_STARTING_SPACING,

    WLAN_MIB_INDEX_OBSSSCAN_TRIGGER_INTERVAL, /*8*/
    WLAN_MIB_INDEX_OBSSSCAN_TRANSITION_DELAY_FACTOR,
    WLAN_MIB_INDEX_OBSSSCAN_PASSIVE_DWELL,
    WLAN_MIB_INDEX_OBSSSCAN_ACTIVE_DWELL,
    WLAN_MIB_INDEX_OBSSSCAN_PASSIVE_TOTAL_PER_CHANNEL,
    WLAN_MIB_INDEX_OBSSSCAN_ACTIVE_TOTAL_PER_CHANNEL,
    WLAN_MIB_INDEX_OBSSSCAN_ACTIVITY_THRESHOLD,/*14*/

    WLAN_MIB_INDEX_BUTT
}wlan_mib_index_enum;
typedef oal_uint16 wlan_mib_index_enum_uint16;

typedef enum
{
    DMAC_TID_PAUSE_RESUME_TYPE_BA   = 0,
    DMAC_TID_PAUSE_RESUME_TYPE_PS   = 1,
    DMAC_TID_PAUSE_RESUME_TYPE_BUTT
}dmac_tid_pause_type_enum;
typedef oal_uint8 dmac_tid_pause_type_enum_uint8;

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
/* DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP */
typedef struct
{
    dmac_disasoc_misc_reason_enum_uint16     en_disasoc_reason;
    oal_uint16                               us_user_idx;
}dmac_disasoc_misc_stru;

/* ����֡��ͳ����Ϣ */
typedef struct
{
    oal_uint32  ul_total_num;           /* ���� */
    oal_uint32  ul_self_fcs_correct;    /* �����Լ���FCS��ȷ�ĵ���֡ */
    oal_uint32  ul_other_fcs_correct;   /* ���Ƿ����Լ���FCS��ȷ�ĵ���֡ */
    oal_uint32  ul_total_fcs_error;     /* FCS���������֡ */
}dmac_rx_fcs_statistic;
#if (!defined(_PRE_PRODUCT_ID_HI110X_DEV))
/* ��������֡��FCS��ͳ����Ϣ */
extern dmac_rx_fcs_statistic g_ast_rx_fcs_statistic[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT];
#endif

typedef struct
{
    oal_uint8               uc_tid_num;                         /* ��Ҫ���͵�tid���к� */
    dmac_tx_mode_enum_uint8 en_tx_mode;                         /* ����tid�ķ���ģʽ */
    oal_uint8               uc_mpdu_num[DMAC_TX_QUEUE_AGGR_DEPTH];   /* ���ȵõ�����Ҫ���͵�mpdu���� */
    oal_uint16              us_user_idx;                        /* Ҫ���͵�tid����������user */
#ifdef _PRE_WLAN_FEATURE_DFR
    oal_bool_enum_uint8     en_ba_is_jamed;                     /* ��ǰBA���Ƿ����ı�־λ */
    oal_uint8               uc_resv;
#else
    oal_uint8               auc_resv[2];
#endif
}mac_tid_schedule_output_stru;

/* DMAC��HMACģ�鹲�õ�WLAN DRX�¼��ṹ�� */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* netbuf����һ��Ԫ�� */
    oal_uint16              us_netbuf_num;      /* netbuf����ĸ��� */
    oal_uint8               auc_resv[2];        /* �ֽڶ��� */
}dmac_wlan_drx_event_stru;

/* DMAC��HMACģ�鹲�õ�WLAN CRX�¼��ṹ�� */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* ָ�����֡��Ӧ��netbuf */
    oal_uint8              *puc_chtxt;          /* Shared Key��֤�õ�challenge text */
}dmac_wlan_crx_event_stru;

#ifdef _PRE_WLAN_FEATURE_BTCOEX
typedef struct
{
    oal_uint16 us_user_id;
    oal_uint16 us_ba_size;
    oal_uint8 uc_need_delba;
    oal_uint8 auc_resv[3];
}dmac_to_hmac_btcoex_rx_delba_trigger_event_stru;
#endif

typedef struct
{
    oal_uint16      us_user_index;
    oal_uint8       uc_tid;
    oal_uint8       uc_vap_id;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8       uc_cur_protocol;
    oal_uint8       auc_reserve[3];
#endif
}dmac_to_hmac_ctx_event_stru;


typedef struct
{
    oal_uint16      us_user_index;
    oal_uint8       uc_cur_bandwidth;
    oal_uint8       uc_cur_protocol;
}dmac_to_hmac_syn_info_event_stru;

typedef struct
{
    oal_uint8       uc_vap_id;
    oal_uint8       en_voice_aggr;              /* �Ƿ�֧��Voice�ۺ� */
    oal_uint8       auc_resv[2];
}dmac_to_hmac_voice_aggr_event_stru;

/*mic����*/
typedef struct
{
    oal_uint8                  auc_user_mac[WLAN_MAC_ADDR_LEN];
    oal_uint8                  auc_reserve[2];
    oal_nl80211_key_type       en_key_type;
    oal_int32                  l_key_id;
}dmac_to_hmac_mic_event_stru;

/*DMAC��HMACģ�鹲�õ�DTX�¼��ṹ�� */
typedef struct
{
    oal_netbuf_stru        *pst_netbuf;         /* netbuf����һ��Ԫ�� */
    oal_uint16              us_frame_len;
    oal_uint16              us_remain;
}dmac_tx_event_stru;

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
typedef struct
{
    oal_uint32        us_dpd_data[128]; /*dpd calibration data*/
    oal_uint16        us_data_len;       /*data length*/
}dpd_cali_data_stru;

#endif

typedef struct
{
    mac_channel_stru                     st_channel;
    mac_ch_switch_info_stru              st_ch_switch_info;

    oal_bool_enum_uint8                  en_switch_immediately; /* 1 - �����л�  0 - �ݲ��л�, �Ƴٵ�tbtt���л�*/
    oal_bool_enum_uint8                  en_check_cac;
    oal_uint8                            auc_resv[2];
}dmac_set_chan_stru;

typedef struct
{
    wlan_ch_switch_status_enum_uint8     en_ch_switch_status;      /* �ŵ��л�״̬ */
    oal_uint8                            uc_announced_channel;     /* ���ŵ��� */
    wlan_channel_bandwidth_enum_uint8    en_announced_bandwidth;   /* �´���ģʽ */
    oal_uint8                            uc_ch_switch_cnt;         /* �ŵ��л����� */
    oal_bool_enum_uint8                  en_csa_present_in_bcn;    /* Beacon֡���Ƿ����CSA IE */
    oal_uint8                            uc_csa_vap_cnt;           /* ��Ҫ����csa��vap���� */
    oal_uint8                            auc_reserve[2];
}dmac_set_ch_switch_info_stru;

/*
    (1)DMAC��HMACģ�鹲�õ�CTX������ACTION��Ӧ���¼��Ľṹ��
    (2)��DMAC�������DELBA֡ʱ��ʹ�øýṹ����HMACģ�����¼�
*/
 typedef struct
 {
    mac_category_enum_uint8     en_action_category;     /* ACTION֡������ */
    oal_uint8                   uc_action;              /* ��ͬACTION���µ���֡���� */
    oal_uint16                  us_user_idx;
    oal_uint16                  us_frame_len;           /* ֡���� */
    oal_uint8                   uc_hdr_len;             /* ֡ͷ���� */
    oal_uint8                   uc_tidno;               /* tidno������action֡ʹ�� */
    oal_uint8                   uc_initiator;           /* �����˷��� */

    /* ����Ϊ���յ�req֡������rsp֡����Ҫͬ����dmac������ */
    oal_uint8                       uc_status;              /* rsp֡�е�״̬ */
    oal_uint16                      us_baw_start;           /* ���ڿ�ʼ���к� */
    oal_uint16                      us_baw_size;            /* ���ڴ�С */
    oal_uint8                       uc_ampdu_max_num;       /* BA�Ự�µ����ۺϵ�AMPDU�ĸ��� */
    oal_bool_enum_uint8             en_amsdu_supp;          /* �Ƿ�֧��AMSDU */
    oal_uint16                      us_ba_timeout;          /* BA�Ự������ʱʱ�� */
    mac_back_variant_enum_uint8     en_back_var;            /* BA�Ự�ı��� */
    oal_uint8                       uc_dialog_token;        /* ADDBA����֡��dialog token */
    oal_uint8                       uc_ba_policy;           /* Immediate=1 Delayed=0 */
    oal_uint8                       uc_lut_index;           /* LUT���� */
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];    /* ����DELBA��DELTS����HMAC�û� */
#ifdef _PRE_WLAN_FEATURE_WMMAC
    oal_uint8                       uc_tsid;                /* TS���Action֡�е�tsidֵ */
    oal_uint8                       uc_ts_dialog_token;        /* ADDTS����֡��dialog token */
    oal_uint8                       uc_resv[2];
#endif
 }dmac_ctx_action_event_stru;

/* ����û��¼�payload�ṹ�� */
typedef struct
{
    oal_uint16  us_user_idx;     /* �û�index */
    oal_uint8   auc_user_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint16  us_sta_aid;
    oal_uint8   auc_bssid[WLAN_MAC_ADDR_LEN];

    mac_vht_hdl_stru          st_vht_hdl;
    mac_user_ht_hdl_stru      st_ht_hdl;
    mac_ap_type_enum_uint8    en_ap_type;

//    oal_uint8   bit_transmit_staggered_sounding_cap : 1,
//                bit_exp_comp_feedback               : 2,
//                bit_su_beamformer_cap               : 1,                       /* SU bfer������Ҫ��AP��֤��������1 */
//                bit_su_beamformee_cap               : 1,                       /* SU bfee������Ҫ��STA��֤��������1 */
//                bit_resv                            : 3;

 //   oal_uint8   bit_num_bf_ant_supported            : 3,                       /* SUʱ��������NDP��Nsts����С��1 */
 //               bit_num_sounding_dim                : 3,                       /* SUʱ����ʾNsts���ֵ����С��1 */
 //               bit_mu_beamformer_cap               : 1,                       /* ��֧�֣�set to 0 */
//                bit_mu_beamformee_cap               : 1;                       /* ��֧�֣�set to 0 */
}dmac_ctx_add_user_stru;

/* ɾ���û��¼��ṹ�� */
typedef dmac_ctx_add_user_stru dmac_ctx_del_user_stru;

/* ɨ�������¼�payload�ṹ�� */
typedef struct
{
    mac_scan_req_stru   *pst_scan_params;   /* ��ɨ���������ȥ */
}dmac_ctx_scan_req_stru;

typedef struct
{
    oal_uint8                   uc_scan_idx;
    oal_uint8                   auc_resv[3];
    mac_scan_chan_stats_stru    st_chan_result;
}dmac_crx_chan_result_stru;


/* Update join req ����д�Ĵ����Ľṹ�嶨�� */
typedef struct
{
    oal_uint8               auc_bssid[WLAN_MAC_ADDR_LEN];    /* �����AP��BSSID  */
    oal_uint16              us_beacon_period;
    mac_channel_stru        st_current_channel;              /* Ҫ�л����ŵ���Ϣ */
    oal_uint32              ul_beacon_filter;                /* ����beacon֡���˲���������ʶλ */
    oal_uint32              ul_non_frame_filter;              /* ����no_frame֡���˲���������ʶλ */
    oal_uint8               auc_ssid[WLAN_SSID_MAX_LEN];    /* �����AP��SSID  */
    oal_uint8               uc_dtim_period;                 /* dtim period      */
    oal_bool_enum_uint8     en_dot11FortyMHzOperationImplemented;         /* dot11FortyMHzOperationImplemented */
    oal_uint8               auc_resv;
}dmac_ctx_join_req_set_reg_stru;

/* wait joinд�Ĵ��������Ľṹ�嶨�� */
typedef struct
{
    oal_uint32              ul_dtim_period;                  /* dtim period */
    oal_uint32              ul_dtim_cnt;                     /* dtim count  */
    oal_uint8               auc_bssid[WLAN_MAC_ADDR_LEN];    /* �����AP��BSSID  */
    oal_uint16              us_tsf_bit0;                     /* tsf bit0  */
}dmac_ctx_set_dtim_tsf_reg_stru;

/* wait join miscд�Ĵ��������Ľṹ�嶨�� */
typedef struct
{
    oal_uint32              ul_beacon_filter;                /* ����beacon֡���˲���������ʶλ */
}dmac_ctx_join_misc_set_reg_stru;

/* wait joinд�Ĵ��������Ľṹ�嶨�� */
typedef struct
{
    oal_uint16             uc_user_index;                    /* user index */
    oal_uint8              auc_resv[2];
}dmac_ctx_asoc_set_reg_stru;

/* sta����edca�����Ĵ����Ľṹ�嶨�� */
typedef struct
{
    oal_uint8                            uc_vap_id;
    mac_wmm_set_param_type_enum_uint8    en_set_param_type;
    oal_uint16                           uc_user_index;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    wlan_mib_Dot11QAPEDCAEntry_stru      ast_wlan_mib_qap_edac[WLAN_WME_AC_BUTT];
#ifdef _PRE_WLAN_FEATURE_WMMAC
    mac_ts_info_stru                     st_ts_info[WLAN_WME_AC_BUTT];
#endif
#endif
}dmac_ctx_sta_asoc_set_edca_reg_stru;

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
/* ��ϵͳ��DMACģ����HMACģ�鹲�õĽ������̿�����Ϣ���ݽṹ����, ��hal_rx_ctl_stru�ṹ�屣��һ��*/
#pragma pack(push,1)
typedef struct
{
    /*word 0*/
    oal_uint8                   bit_vap_id            :5;
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;
    oal_uint8                   uc_msdu_in_buffer;
    oal_uint8                   bit_da_user_idx       :4;
    oal_uint8                   bit_ta_user_idx       :4;
    oal_uint8                   bit_mac_header_len    :6;   /* mac header֡ͷ���� */
    oal_uint8                   bit_is_beacon         :1;
    oal_uint8                   bit_reserved1         :1;
    /*word 1*/
    oal_uint16                  us_frame_len;               /* ֡ͷ��֡����ܳ��� */
    oal_uint8                   uc_mac_vap_id         :4;
    oal_uint8                   bit_buff_nums         :4; /* ÿ��MPDUռ�õ�buf�� */
    oal_uint8                   uc_channel_number;          /* ����֡���ŵ� */
    /*word 2*/
}mac_rx_ctl_stru;
#pragma pack(pop)

#else
/* DMACģ����HMACģ�鹲�õĽ������̿�����Ϣ���ݽṹ����, ��hal_rx_ctl_stru�ṹ�屣��һ��*/
typedef struct
{
    /*word 0*/
    oal_uint8                   bit_vap_id            :5;
    oal_uint8                   bit_amsdu_enable      :1;
    oal_uint8                   bit_is_first_buffer   :1;
    oal_uint8                   bit_is_fragmented     :1;
    oal_uint8                   uc_msdu_in_buffer;
    oal_uint8                   bit_buff_nums         :4;   /* ÿ��MPDUռ�õ�buf��Ŀ */
    oal_uint8                   bit_is_beacon         :1;
    oal_uint8                   bit_reserved1         :3;
    oal_uint8                   uc_mac_header_len;          /* mac header֡ͷ���� */
    /*word 1*/
    oal_uint16                  us_frame_len;               /* ֡ͷ��֡����ܳ��� */
    oal_uint16                  us_da_user_idx;             /* Ŀ�ĵ�ַ�û����� */
    /*word 2*/
    oal_uint32                 *pul_mac_hdr_start_addr;     /* ��Ӧ��֡��֡ͷ��ַ,�����ַ */
    /*word 3*/
    oal_uint16                  us_ta_user_idx;             /* ���Ͷ˵�ַ�û����� */
    oal_uint8                   uc_mac_vap_id;
    oal_uint8                   uc_channel_number;          /* ����֡���ŵ� */
}mac_rx_ctl_stru;
#endif
/* hmac to dmac����ͬ����Ϣ�ṹ */
typedef struct
{
    wlan_cfgid_enum_uint16              en_syn_id;      /* ͬ���¼�ID*/
    oal_uint16                          us_len;         /* �¼�payload���� */
    oal_uint8                           auc_msg_body[4];/* �¼�payload */
}hmac_to_dmac_cfg_msg_stru;

typedef hmac_to_dmac_cfg_msg_stru dmac_to_hmac_cfg_msg_stru;

/* HMAC��DMAC����ͬ������ */
typedef struct
{
    wlan_cfgid_enum_uint16      en_cfgid;
    oal_uint8                   auc_resv[2];
    oal_uint32                  (*p_set_func)(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
}dmac_config_syn_stru;

typedef dmac_config_syn_stru hmac_config_syn_stru;

#if 0
/* DMAC_WLAN_CRX_EVENT_SUB_TYPE_SCAN_COMP */
typedef struct
{
    oal_uint32      ul_bss_num;
    oal_void       *p_bss_list;
}dmac_wlan_crx_scan_comp_stru;
#endif

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
#pragma pack(push,1)
/* ��ϵͳcb�ֶ� ֻ��20�ֽڿ��ã����Խ�resv�ֶ��޸�Ϊ�����ֶΣ��������������ֽ�!!!!!!!!!!!!!!!!!!!!!!!!! */
struct  mac_tx_ctl
{
    /* �ó�Աֻ�ڵ�һ��netbuf����Ч */
    oal_uint8                               bit_mpdu_num                :7;          /* ampdu�а�����MPDU����,ʵ����������д��ֵΪ��ֵ-1 */
    /* ��ÿ��MPDU�ĵ�һ��NETBUF����Ч */
    oal_uint8                               bit_netbuf_num              :1;          /* ÿ��MPDUռ�õ�netbuf��Ŀ */

    oal_uint8                               bit_frame_header_length     :6;          //51�ĵ�ַ32 /* ��MPDU��802.11ͷ���� */
    oal_uint8                               en_is_first_msdu            :1;          /* �Ƿ��ǵ�һ����֡��OAL_FALSE���� OAL_TRUE�� */
    oal_uint8                               en_is_amsdu                 :1;          /* �Ƿ�AMSDU: OAL_FALSE���ǣ�OAL_TRUE�� */

    frw_event_type_enum_uint8               bit_en_event_type           :6;          /* ȡֵ:FRW_EVENT_TYPE_WLAN_DTX��FRW_EVENT_TYPE_HOST_DRX������:���ͷ�ʱ�������ڴ�ص�netbuf����ԭ��̬�� */
    oal_uint8                               bit_is_needretry            :1;
    oal_uint8                               bit_is_vipframe             :1;          /* ��֡�Ƿ���EAPOL֡��DHCP֡ */


    oal_uint8                               bit_tx_user_idx             :4;          /* dmac tx �� tx complete ���ݵ�user�ṹ�壬Ŀ���û���ַ */
    dmac_user_alg_probe_enum_uint8          en_is_probe_data            :3;          /* �Ƿ�̽��֡ */
    oal_uint8                               en_ismcast                  :1;          /* ��MPDU�ǵ������Ƕಥ:OAL_FALSE������OAL_TRUE�ಥ */

    oal_uint8                               bit_retried_num             :4;
    oal_uint8                               bit_need_rsp                :1;           /* WPAS send mgmt,need dmac response tx status */
    oal_uint8                               en_is_eapol                 :1;           /* ��֡�Ƿ���EAPOL֡ 1102����ȥ�� */
    oal_uint8                               en_is_get_from_ps_queue     :1;           /* ���������ã���ʶһ��MPDU�Ƿ�ӽ��ܶ�����ȡ������ */
    oal_uint8                               bit_is_eapol_key_ptk        :1;           /* 4 �����ֹ��������õ�����ԿEAPOL KEY ֡��ʶ */

    oal_uint8                               bit_tx_vap_index            :3;
    oal_uint8                               bit_mgmt_frame_id           :4;            /* wpas ���͹���֡��frame id */
    oal_uint8                               bit_roam_data               :1;

    wlan_wme_ac_type_enum_uint8             bit_ac                      :3;            /* ac */
    wlan_tx_ack_policy_enum_uint8           en_ack_policy               :3;            /* ACK ���� */
    oal_uint8                               bit_reserved3               :2;

    oal_uint8                               uc_alg_pktno;                              /* �㷨�õ����ֶΣ�Ψһ��ʾ�ñ��� */

    oal_uint8                               bit_tid                     :4;
    oal_uint8                               bit_tx_user_idx_bak         :4;

    oal_time_us_stru                        st_timestamp_us;                           /* ά��ʹ����TID����ʱ��ʱ��� */
    oal_uint16                              us_mpdu_bytes;                             /* mpdu�ֽ�����ά���ã�������ͷβ��������snap��������padding */

}__OAL_DECLARE_PACKED;
typedef struct mac_tx_ctl  mac_tx_ctl_stru;
/* DMACģ��������̿�����Ϣ�ṹ������ڶ�Ӧ��netbuf��CB�ֶ��У����ֵΪ48�ֽ�,
   ����޸ģ�һ��Ҫ֪ͨsdtͬ���޸ģ�����������д���!!!!!!!!!!!!!!!!!!!!!!!!!*/
typedef struct
{
    mac_rx_ctl_stru             st_rx_info;         /* hmac��Ҫ����dmac��������Ϣ */
    hal_rx_status_stru          st_rx_status;       /* ����������ͼ�֡����Ϣ */
    hal_rx_statistic_stru       st_rx_statistic;    /* ���������������ͳ����Ϣ */
}dmac_rx_ctl_stru;

#pragma pack(pop)
#else
/* netbuf�����ֶ�(CB)���ܳ���Ϊ48�ֽ� (Ŀǰ����42�ֽ�),����޸ģ�һ��Ҫ֪ͨsdt
   ͬ���޸ģ�����������д���!!!!!!!!!!!!!!!!!!!!!!!!! */
typedef struct
{
    /* �ó�Աֻ�ڵ�һ��netbuf����Ч */
    oal_uint8                               uc_mpdu_num;                /* ampdu�а�����MPDU����,ʵ����������д��ֵΪ��ֵ-1 */

    /* ��ÿ��MPDU�ĵ�һ��NETBUF����Ч */
    oal_uint8                               uc_netbuf_num;                              /* ÿ��MPDUռ�õ�netbuf��Ŀ */
    oal_uint16                              us_mpdu_len;                                /* ÿ��MPDU�ĳ��Ȳ�����mac header length */
    oal_uint8                               en_is_amsdu                 :1;             /* �Ƿ�AMSDU: OAL_FALSE���ǣ�OAL_TRUE�� */
    oal_uint8                               en_ismcast                  :1;             /* ��MPDU�ǵ������Ƕಥ:OAL_FALSE������OAL_TRUE�ಥ */
    oal_uint8                               en_is_eapol                 :1;             /* ��֡�Ƿ���EAPOL֡ */
    oal_uint8                               en_use_4_addr               :1;             /* �Ƿ�ʹ��4��ַ����WDS���Ծ��� */
    oal_uint8                               en_is_get_from_ps_queue     :1;             /* ���������ã���ʶһ��MPDU�Ƿ�ӽ��ܶ�����ȡ������ */
    oal_uint8                               uc_is_first_msdu            :1;             /* �Ƿ��ǵ�һ����֡��OAL_FALSE���� OAL_TRUE�� */
	oal_uint8                               en_need_pause_tid           :1;
    oal_uint8                               en_is_bar                   :1;
    oal_uint8                               uc_frame_header_length;                     /* ��MPDU��802.11ͷ���� */
    oal_uint8                               en_is_qosdata               :1;             /* ָʾ��֡�Ƿ���qos data */
    oal_uint8                               bit_80211_mac_head_type     :1;             /* 0: 802.11 macͷ����skb�У������������ڴ��ţ� 1: 802.11 macͷ��skb��*/
    oal_uint8                               bit_is_vipframe             :1;             /* ��֡�Ƿ���EAPOL֡��DHCP֡ */
    oal_uint8                               bit_is_needretry            :1;
    oal_uint8                               en_seq_ctrl_bypass          :1;             /* ��֡��SN�������ά����Ӳ����ֹά��(Ŀǰ�����ڷ�QOS��Ƭ֡ ) */
    oal_uint8                               bit_need_rsp                :1;             /* WPAS send mgmt,need dmac response tx status */
    oal_uint8                               bit_is_eapol_key_ptk        :1;             /* 4 �����ֹ��������õ�����ԿEAPOL KEY ֡��ʶ */
    oal_uint8                               bit_roam_data               :1;

    wlan_frame_type_enum_uint8              en_frame_type;                              /* ֡���ͣ�����֡������֡... */
    mac_ieee80211_frame_stru               *pst_frame_header;                           /* ��MPDU��֡ͷָ�� */


    wlan_wme_ac_type_enum_uint8             uc_ac;                                      /* ac */
    oal_uint8                               uc_tid;                                     /* tid */
    frw_event_type_enum_uint8               en_event_type;                              /* ȡֵ:FRW_EVENT_TYPE_WLAN_DTX��FRW_EVENT_TYPE_HOST_DRX������:���ͷ�ʱ�������ڴ�ص�netbuf����ԭ��̬�� */
    oal_uint8                               uc_event_sub_type;                          /* amsdu���¼��õ� */
    wlan_tx_ack_policy_enum_uint8           en_ack_policy;                              /* ACK ���� */
    oal_uint8                               uc_tx_vap_index;
    oal_uint16                              us_tx_user_idx;                             /* dmac tx �� tx complete ���ݵ�user�ṹ�壬Ŀ���û���ַ */
    oal_uint32                              ul_alg_pktno;                               /* �㷨�õ����ֶΣ�Ψһ��ʾ�ñ��� */
    oal_uint8                               uc_retried_num;
    dmac_user_alg_probe_enum_uint8          en_is_probe_data;                           /* �Ƿ���̽��֡ */
    oal_uint16                              us_seqnum;                                  /* ��¼��������seqnum*/
    hal_tx_dscr_stru                       *pst_bar_dscr;
#if (!defined(_PRE_PRODUCT_ID_HI110X_HOST))
    /*1102 host ���ô˱�����ռ�ռ�̫��,ARM64ʱCB������С!*/
    oal_time_us_stru                        st_timestamp_us;                            /* ��TID����ʱ��ʱ��� */
#endif
    oal_uint16                              us_eapol_ts;                                /* eapol֡ʱ��� */
    oal_uint16                              us_mpdu_bytes;                              /* mpdu�ֽ�����ά���ã�������ͷβ��������snap��������padding */
    oal_uint8                               bit_mgmt_frame_id           :4;             /* wpas ���͹���֡��frame id */
    oal_uint8                               bit_reserved2               :4;
}mac_tx_ctl_stru;

/* DMACģ��������̿�����Ϣ�ṹ������ڶ�Ӧ��netbuf��CB�ֶ��У����ֵΪ48�ֽ�,
   ����޸ģ�һ��Ҫ֪ͨsdtͬ���޸ģ�����������д���!!!!!!!!!!!!!!!!!!!!!!!!!*/
typedef struct
{
    mac_rx_ctl_stru             st_rx_info;         /* hmac��Ҫ����dmac��������Ϣ */
    hal_rx_status_stru          st_rx_status;       /* ����������ͼ�֡����Ϣ */
    hal_rx_statistic_stru       st_rx_statistic;    /* ���������������ͳ����Ϣ */
}dmac_rx_ctl_stru;

#endif


typedef struct
{
    oal_uint32      ul_best_rate_goodput_kbps;
    oal_uint32      ul_rate_kbps;           /* ���ʴ�С(��λ:kbps) */
    oal_uint8       uc_aggr_subfrm_size;    /* �ۺ���֡������ֵ */
    oal_uint8       uc_per;                 /* �����ʵ�PER(��λ:%) */
#ifdef _PRE_WLAN_DFT_STAT
    oal_uint8       uc_best_rate_per;       /* �������ʵ�PER(��λ:%) */
    oal_uint8       uc_resv[1];
#else
    oal_uint8       uc_resv[2];
#endif
}dmac_tx_normal_rate_stats_stru;

typedef struct
{
    oal_bool_enum_uint8                     in_use;                     /* ����BUF�Ƿ�ʹ�� */
    oal_uint8                               uc_num_buf;                 /* MPDU��Ӧ���������ĸ��� */
    oal_uint16                              us_seq_num;                 /* MPDU��Ӧ�����к� */
    oal_netbuf_head_stru                    st_netbuf_head;             /* MPDU��Ӧ���������׵�ַ */
    oal_uint32                              ul_rx_time;                 /* ���ı������ʱ��� */
} dmac_rx_buf_stru;


typedef struct
{
    oal_void                               *pst_ba;
    oal_uint8                               uc_tid;
    mac_delba_initiator_enum_uint8          en_direction;
    oal_uint16                              us_mac_user_idx;
    oal_uint8                               uc_vap_id;
    oal_uint16                              us_timeout_times;
    oal_uint8                               uc_resv[1];
}dmac_ba_alarm_stru;


/* һ��վ���µ�ÿһ��TID�µľۺϽ��յ�״̬��Ϣ */
typedef struct
{
    oal_uint16                      us_baw_start;         /* ��һ��δ�յ���MPDU�����к� */
    oal_bool_enum_uint8             en_is_ba;             /* Session Valid Flag */
    oal_uint8                       auc_resv[1];

    /* ����BA�Ự��ص���Ϣ */
    dmac_ba_conn_status_enum_uint8  en_ba_conn_status;    /* BA�Ự��״̬ */
    mac_back_variant_enum_uint8     en_back_var;          /* BA�Ự�ı��� */
    oal_uint8                       uc_ba_policy;         /* Immediate=1 Delayed=0 */
    oal_uint8                       uc_lut_index;         /* ���ն�Session H/w LUT Index */
    oal_uint8                      *puc_transmit_addr;    /* BA�Ự���Ͷ˵�ַ */
}dmac_ba_rx_stru;

typedef struct
{
    oal_uint8   uc_in_use;
    oal_uint8   uc_resv[1];
    oal_uint16  us_seq_num;
    oal_void*   p_tx_dscr;
}dmac_retry_queue_stru;

typedef struct
{
    oal_uint16                      us_baw_start;           /* ��һ��δȷ�ϵ�MPDU�����к� */
    oal_uint16                      us_last_seq_num;        /* ���һ�����͵�MPDU�����к� */
    oal_uint16                      us_baw_size;            /* Block_Ack�Ự��buffer size��С */
    oal_uint16                      us_baw_head;            /* bitmap�м�¼�ĵ�һ��δȷ�ϵİ���λ�� */
    oal_uint16                      us_baw_tail;            /* bitmap����һ��δʹ�õ�λ�� */
    oal_bool_enum_uint8             en_is_ba;               /* Session Valid Flag */
    dmac_ba_conn_status_enum_uint8  en_ba_conn_status;      /* BA�Ự��״̬ */
    mac_back_variant_enum_uint8     en_back_var;            /* BA�Ự�ı��� */
    oal_uint8                       uc_dialog_token;        /* ADDBA����֡��dialog token */
    oal_uint8                       uc_ba_policy;           /* Immediate=1 Delayed=0 */
    oal_bool_enum_uint8             en_amsdu_supp;          /* BLOCK ACK֧��AMSDU�ı�ʶ */
    oal_uint8                      *puc_dst_addr;           /* BA�Ự���ն˵�ַ */
    oal_uint16                      us_ba_timeout;          /* BA�Ự������ʱʱ�� */
    oal_uint8                       uc_ampdu_max_num;       /* BA�Ự�£��ܹ��ۺϵ�����mpdu�ĸ��� */
    oal_uint8                       uc_tx_ba_lut;
    oal_uint16                      us_mac_user_idx;
#ifdef _PRE_WLAN_FEATURE_DFR
    oal_uint16                      us_pre_baw_start;       /* ��¼ǰһ���ж�ba���Ƿ���ʱ��ssn */
    oal_uint16                      us_pre_last_seq_num;    /* ��¼ǰһ���ж�ba���Ƿ���ʱ��lsn */
    oal_uint16                      us_ba_jamed_cnt;        /* BA������ͳ�ƴ��� */
#else
    oal_uint8                       auc_resv[2];
#endif
    oal_uint32                      aul_tx_buf_bitmap[DMAC_TX_BUF_BITMAP_WORDS];
}dmac_ba_tx_stru;

/* 11n�µĲ�������Ҫ�ڹ���ʱ�������� */
typedef struct
{
    oal_uint8               uc_ampdu_max_num;
    oal_uint8               auc_reserve[1];
    oal_uint16              us_ampdu_max_size;
    oal_uint32              ul_ampdu_max_size_vht;
}dmac_ht_handle_stru;

#ifdef _PRE_WLAN_DFT_STAT
typedef struct
{
    /* ���ͳ�� */
    oal_uint32              ul_tid_enqueue_total_cnt;            /* �������Ŀͳ�� */
    oal_uint32              ul_tid_enqueue_ptr_null_cnt;         /* ��Ӻ�����ָ�����̵��¶���ͳ�� */
    oal_uint32              ul_tid_enqueue_full_cnt;             /* ���ʱ���������¶���ͳ�� */
    oal_uint32              ul_tid_enqueue_head_ptr_null_cnt;    /* �����������ӣ���ָ�����̶��� */
    oal_uint32              ul_tid_enqueue_head_full_cnt;        /* �����������ӣ�����������ͳ�� */

    /* ����ͳ�� */
    oal_uint32              ul_tid_dequeue_total_cnt;            /* ��������Ŀͳ�� */
    oal_uint32              ul_tid_dequeue_normal_cnt;           /* ��AMPDUʱ���Ӹ��� */
    oal_uint32              ul_tid_dequeue_ampdu_cnt;            /* AMPDU���Ӹ��� */

    /* ����ͳ�� */
    oal_uint32              ul_tid_video_dropped_cnt;            /* ��Ƶ������������tid�ó���ֱ��ɾ�� */
    oal_uint32              ul_tid_traffic_ctl_dropped_cnt;      /* ���ض�����������tid�ó���ֱ��ɾ�� */
    oal_uint32              ul_tid_txbuf_overflow_dropped_cnt;   /* ����ʱbuf������� */
    oal_uint32              ul_tid_dbac_reset_dropped_cnt;             /* dbac��λcase��Ϣ���� */

    /* �ش�ͳ�� */
    oal_uint32              ul_tid_retry_enqueue_cnt;            /* �ش��������Ŀͳ�� */
    oal_uint32              ul_tid_retry_dequeue_cnt;            /* �ش���������Ŀͳ�� */
}dmac_tid_stats_stru;
#endif

#ifdef _PRE_DEBUG_MODE
typedef oam_stats_ampdu_stat_stru dmac_tid_ampdu_stat_stru;
#endif


typedef struct
{
    oal_uint8               uc_tid;                 /* ͨ�ű�ʶ�� */
    oal_uint8               uc_is_paused;           /* TID����ͣ���� */
    oal_uint8               uc_num_dq;              /* ���Լӵ�ba���İ��ĸ��� */
    oal_uint8               uc_retry_num;           /* tid�������ش����ĵĸ��� */
    oal_uint16              us_mpdu_num;            /* MPDU���� */
    oal_uint16              us_user_idx;            /* ��ЧֵΪMAC_RES_MAC_USER_NUM */

    oal_uint32              ul_mpdu_avg_len;        /* mpdu����ƽ������ */
#ifdef _PRE_WLAN_FEATURE_TX_DSCR_OPT
    oal_dlist_head_stru     st_retry_q;             /* �ش��������� */
    oal_netbuf_head_stru    st_buff_head;           /* ���ͻ���������� */
#else
    oal_dlist_head_stru     st_hdr;                 /* tid�������ͷ */
#endif /* _PRE_WLAN_FEATURE_TX_DSCR_OPT */
    oal_void               *p_alg_priv;             /* TID�����㷨˽�нṹ�� */
    dmac_tx_normal_rate_stats_stru st_rate_stats;   /* �����㷨�ڷ��������ͳ�Ƴ�����Ϣ */
    dmac_ba_tx_stru        *pst_ba_tx_hdl;
    dmac_ba_rx_stru        *pst_ba_rx_hdl;
    dmac_ht_handle_stru     st_ht_tx_hdl;
    oal_uint8               uc_num_tx_ba;
    oal_uint8               uc_num_rx_ba;
    oal_uint8               uc_vap_id;
    dmac_tx_mode_enum_uint8 en_tx_mode;             /* ����ģʽ: rifs,aggr,normal���� */
    oal_bool_enum_uint8     en_is_delba_ing;        /* ��tid�Ƿ����ڷ�delba */
    oal_uint8               uc_rx_wrong_ampdu_num;  /* ��tidδ����BA�Ựʱ�յ��ľۺ���֡��(һ����DELBAʧ��) */
    oal_uint8               uc_resv[2];
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_DFT_STAT
    dmac_tid_stats_stru    *pst_tid_stats;           /* ��TID����ӡ����Ӱ�����������ͳ�� */
#endif
#endif
#ifdef _PRE_DEBUG_MODE
    dmac_tid_ampdu_stat_stru *pst_tid_ampdu_stat;    /* ampduҵ������ͳ����Ϣ */
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    oal_uint16             us_last_seq_frag_num;          /* �����ǰһ��QoS֡��seq + frag num */
    oal_uint8              auc_resv2[2];
#endif
}dmac_tid_stru;

/* ����MPDU��MSDU�Ĵ���״̬�Ľṹ��Ķ��� */
typedef struct
{
    oal_netbuf_stru        *pst_curr_netbuf;              /* ��ǰ�����netbufָ�� */
    oal_uint8              *puc_curr_netbuf_data;         /* ��ǰ�����netbuf��dataָ�� */
    oal_uint16              us_submsdu_offset;            /* ��ǰ�����submsdu��ƫ����,   */
    oal_uint8               uc_msdu_nums_in_netbuf;       /* ��ǰnetbuf�������ܵ�msdu��Ŀ */
    oal_uint8               uc_procd_msdu_in_netbuf;      /* ��ǰnetbuf���Ѵ����msdu��Ŀ */
    oal_uint8               uc_netbuf_nums_in_mpdu;       /* ��ǰMPDU���е��ܵ�netbuf����Ŀ */
    oal_uint8               uc_procd_netbuf_nums;         /* ��ǰMPDU���Ѵ����netbuf����Ŀ */
    oal_uint8               uc_procd_msdu_nums_in_mpdu;   /* ��ǰMPDU���Ѵ����MSDU��Ŀ */

    oal_uint8               uc_flag;
}dmac_msdu_proc_state_stru;

/* ÿһ��MSDU���������ݵĽṹ��Ķ��� */
typedef struct
{
    oal_uint8               auc_sa[WLAN_MAC_ADDR_LEN];      /* MSDU���͵�Դ��ַ */
    oal_uint8               auc_da[WLAN_MAC_ADDR_LEN];      /* MSDU���յ�Ŀ�ĵ�ַ */
    oal_uint8               auc_ta[WLAN_MAC_ADDR_LEN];      /* MSDU���յķ��͵�ַ */
    oal_uint8               uc_priority;
    oal_uint8               auc_resv[1];

    oal_netbuf_stru        *pst_netbuf;                     /* MSDU��Ӧ��netbufָ��(����ʹclone��netbuf) */
}dmac_msdu_stru;

/* ��λԭ���� */
typedef enum
{
    DMAC_RESET_REASON_SW_ERR = 0,
    DMAC_RESET_REASON_HW_ERR,
    DMAC_RESET_REASON_CONFIG,
    DMAC_RETST_REASON_OVER_TEMP,
    DMAC_RESET_REASON_TX_COMP_TIMEOUT,

    DMAC_RESET_REASON_BUTT
}dmac_reset_mac_submod_enum;
typedef oal_uint8 dmac_reset_mac_submod_enum_uint8;

typedef struct
{
    hal_reset_hw_type_enum_uint8     uc_reset_type;        /*��������0|1|2|3(all|phy|mac|debug)*/
    hal_reset_mac_submod_enum_uint8  uc_reset_mac_mod;
    dmac_reset_mac_submod_enum_uint8 en_reason;
    oal_uint8 uc_reset_phy_reg;
    oal_uint8 uc_reset_mac_reg;
    oal_uint8 uc_debug_type;                              /*debugʱ������2����Ϊ���ͣ�0|1|2(mac reg|phy reg|lut)*/
    oal_uint8 uc_reset_rf_reg;
    oal_uint8 auc_resv[1];
}dmac_reset_para_stru;

typedef struct
{
    oal_uint8 uc_reason;
    oal_uint8 uc_event;
    oal_uint8 auc_des_addr[WLAN_MAC_ADDR_LEN];
}dmac_diasoc_deauth_event;

#ifdef _PRE_DEBUG_MODE_USER_TRACK
/* �����������ͳ����Ϣ�ṹ�� */
typedef struct
{
    oal_uint32      ul_best_rate_kbps;          /* ͳ�������ڵ��������� */
    oal_uint16      us_best_rate_per;           /* ͳ�����������������µ�ƽ��per */
    oal_uint8       uc_best_rate_aggr_num;      /* ͳ���������������ʵ�aggr */
    oal_uint8       uc_resv;
}dmac_best_rate_traffic_stat_info_stru;

typedef struct
{
    dmac_best_rate_traffic_stat_info_stru    ast_best_rate_stat[WLAN_WME_AC_BUTT];
}dmac_best_rate_stat_info_stru;
#endif

#define DMAC_QUERY_EVENT_LEN  (48)   /*��Ϣ���ݵĳ��� */
typedef enum
{
    OAL_QUERY_STATION_INFO_EVENT      = 1,
    OAL_ATCMDSRV_DBB_NUM_INFO_EVENT   = 2,
    OAL_ATCMDSRV_FEM_PA_INFO_EVENT    = 3,
    OAL_ATCMDSRV_GET_RX_PKCG          = 4,
    OAL_ATCMDSRV_LTE_GPIO_CHECK       = 5,
    OAL_ATCMDSRV_GET_ANT              = 6,
#ifdef _PRE_WLAN_FEATURE_SMARTANT
    OAL_ATCMDSRV_GET_ANT_INFO         = 7,
    OAL_ATCMDSRV_DOUBLE_ANT_SW        = 8,
#endif
    OAL_QUERY_EVNET_BUTT
}oal_query_event_id_enum;

typedef struct
{
    oal_uint8        query_event;
    oal_uint8        auc_query_sta_addr[WLAN_MAC_ADDR_LEN];
}dmac_query_request_event;
typedef struct
{
    oal_uint8        query_event;
    oal_int8        reserve[DMAC_QUERY_EVENT_LEN];
}dmac_query_response_event;
typedef struct
{
    oal_uint32   ul_event_para;       /*��Ϣ���������*/
    oal_int16    s_always_rx_rssi;
    oal_uint8    uc_event_id;         /*��Ϣ��*/
    oal_uint8    uc_reserved;
}dmac_atcmdsrv_atcmd_response_event;

#ifdef _PRE_WLAN_FEATURE_SMARTANT
typedef struct
{
    oal_uint8       uc_event_id;                            /*��Ϣ��*/
    oal_uint8       uc_ant_type;                            //��ǰ�������ߣ�0ΪWIFI�����ߣ�1Ϊ�ּ�����
    oal_uint8       auc_rsv[2];
    oal_uint32      ul_last_ant_change_time_ms;                //�ϴ��л�����ʱ��
    oal_uint32      ul_ant_change_number;                   //�����л�����
    oal_uint32      ul_main_ant_time_s;                       //����WIFI������ʱ��
    oal_uint32      ul_aux_ant_time_s;                        //���ڴ�����(�ּ�����)ʱ��
    oal_uint32      ul_total_time_s;                        //WIFI����ʱ��
}dmac_atcmdsrv_ant_info_response_event;
#endif

typedef struct
{
    oal_uint8        query_event;
    oal_uint8 auc_query_sta_addr[WLAN_MAC_ADDR_LEN];/*sta mac��ַ*/
}dmac_query_station_info_request_event;
typedef struct
{
    oal_uint8    query_event; /*��Ϣ��*/
    oal_uint16   asoc_id;     /* Association ID of the STA*/
    oal_int32    ul_signal;             /*�ź�ǿ��*/
    oal_uint32   ul_rx_packets;     /* total packets received   */
    oal_uint32   ul_tx_packets;     /* total packets transmitted    */
    oal_uint32   ul_rx_bytes;       /* total bytes received     */
    oal_uint32   ul_tx_bytes;       /* total bytes transmitted  */
    oal_uint32   ul_tx_retries;      /*�����ش�����*/
    oal_uint32   ul_rx_dropped_misc;     /*����ʧ�ܴ���*/
    oal_uint32   ul_tx_failed;     /* ����ʧ�ܴ���  */
    oal_int16    s_free_power;  /*����*/
    mac_rate_info_stru st_txrate; /*vap��ǰ����*/
    station_info_extend_stru    st_station_info_extend;                    /*CHR2.0ʹ�õ�STAͳ����Ϣ*/
}dmac_query_station_info_response_event;

typedef struct
{
    oal_uint8   uc_p2p0_hal_vap_id;
    oal_uint8   uc_p2p_gocl_hal_vap_id;
    oal_uint8   uc_rsv[2];
}mac_add_vap_sync_data_stru;

typedef struct
{
    oal_uint32  ul_cycles;              /* ͳ�Ƽ��ʱ�������� */
    oal_uint32  ul_sw_tx_succ_num;     /* ���ͳ�Ʒ��ͳɹ�ppdu���� */
    oal_uint32  ul_sw_tx_fail_num;     /* ���ͳ�Ʒ���ʧ��ppdu���� */
    oal_uint32  ul_sw_rx_ampdu_succ_num;     /* ���ͳ�ƽ��ճɹ���ampdu���� */
    oal_uint32  ul_sw_rx_mpdu_succ_num;      /* ���ͳ�ƽ��ճɹ���mpdu���� */
    oal_uint32  ul_sw_rx_ppdu_fail_num;      /* ���ͳ�ƽ���ʧ�ܵ�ppdu���� */
    oal_uint32  ul_hw_rx_ampdu_fcs_fail_num;   /* Ӳ��ͳ�ƽ���ampdu fcsУ��ʧ�ܸ��� */
    oal_uint32  ul_hw_rx_mpdu_fcs_fail_num;    /* Ӳ��ͳ�ƽ���mpdu fcsУ��ʧ�ܸ��� */
}dmac_thruput_info_sync_stru;

typedef struct
{
    oal_uint32                   uc_dscr_status;
    oal_uint8                   mgmt_frame_id;
    oal_uint8                   uc_user_idx;
}dmac_crx_mgmt_tx_status_stru;

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
typedef struct
{
    oal_uint32           ul_chan_report_for_te_a;  /* Channel Bit Map to register TE-A */
    oal_bool_enum_uint8  en_te_b;                  /* 20/40M intolerant for TE-B */
}dmac_obss_te_a_b_stru;
#endif


#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
typedef enum
{
    DMAC_CONFIG_IPV4 = 0,                /* ����IPv4��ַ */
    DMAC_CONFIG_IPV6,                    /* ����IPv6��ַ */
    DMAC_CONFIG_BUTT
}dmac_ip_type;
typedef oal_uint8 dmac_ip_type_enum_uint8;

typedef enum
{
    DMAC_IP_ADDR_ADD = 0,                /* ����IP��ַ */
    DMAC_IP_ADDR_DEL,                    /* ɾ��IP��ַ */
    DMAC_IP_OPER_BUTT
}dmac_ip_oper;
typedef oal_uint8 dmac_ip_oper_enum_uint8;

typedef struct
{
    dmac_ip_type_enum_uint8           en_type;
    dmac_ip_oper_enum_uint8           en_oper;

    oal_uint8                         auc_resv[2];

    oal_uint8                         auc_ip_addr[OAL_IP_ADDR_MAX_SIZE];
}dmac_ip_addr_config_stru;
#endif


/* ����ִ�п���ö�� */
typedef enum
{
    DMAC_RX_FRAME_CTRL_GOON,        /* ������֡��Ҫ�������� */
    DMAC_RX_FRAME_CTRL_DROP,        /* ������֡��Ҫ���� */
    DMAC_RX_FRAME_CTRL_BA_BUF,      /* ������֡��BA�Ự���� */

    DMAC_RX_FRAME_CTRL_BUTT
}dmac_rx_frame_ctrl_enum;
typedef oal_uint8 dmac_rx_frame_ctrl_enum_uint8;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
#define HMAC_TO_DMAC_CFG_MSG_HDR_LEN  (OAL_SIZEOF(hmac_to_dmac_cfg_msg_stru) - 4)   /* ֻȡͷ�ĳ��ȣ�ȥ��4�ֽ�auc_msg_body���� */

#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
/* ��ϵͳcb�ֶ���Ϣ��ȡ */
#define MAC_GET_CB_MPDU_NUM(_pst_tx_ctrl)                   ((_pst_tx_ctrl)->bit_mpdu_num)
#define MAC_GET_CB_NETBUF_NUM(_pst_tx_ctrl)                 ((_pst_tx_ctrl)->bit_netbuf_num)
/* ��hccͷ�������mpdu len */
/*lint -e778*/
#define MAC_GET_CB_MPDU_LEN(_pst_tx_ctrl)                (((hcc_header_stru *)((oal_uint8 *)(_pst_tx_ctrl) - (OAL_SIZEOF(hcc_header_stru) + OAL_PAD_HDR_LEN)))->pay_len)
#define MAC_GET_CB_IS_MCAST(_pst_tx_ctrl)                ((_pst_tx_ctrl)->en_ismcast)
#define MAC_GET_CB_IS_EAPOL(_pst_tx_ctrl)                ((_pst_tx_ctrl)->en_is_eapol)
#define MAC_GET_CB_IS_FROM_PS_QUEUE(_pst_tx_ctrl)        ((_pst_tx_ctrl)->en_is_get_from_ps_queue)
#define MAC_GET_CB_IS_FIRST_MSDU(_pst_tx_ctrl)           ((_pst_tx_ctrl)->en_is_first_msdu)
#define MAC_GET_CB_FRAME_HEADER_LENGTH(_pst_tx_ctrl)     ((_pst_tx_ctrl)->bit_frame_header_length)
#define MAC_GET_CB_IS_VIPFRAME(_pst_tx_ctrl)             ((_pst_tx_ctrl)->bit_is_vipframe)
#define MAC_GET_CB_IS_NEEDRETRY(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_is_needretry)

#define MAC_GET_CB_FRAME_TYPE(_pst_tx_ctrl)   \
    (((mac_ieee80211_frame_stru *)((oal_uint8 *)_pst_tx_ctrl + OAL_MAX_CB_LEN))->st_frame_control.bit_type)
#define MAC_GET_CB_EN_FRAME_SUBTYPE(_pst_tx_ctrl)   \
    (((mac_ieee80211_qos_htc_frame_stru *)(_pst_tx_ctrl + 1))->st_frame_control.bit_sub_type)

#define MAC_GET_CB_EVENT_TYPE(_pst_tx_ctrl)              ((_pst_tx_ctrl)->bit_en_event_type)
#define MAC_GET_CB_TX_VAP_INDEX(_pst_tx_ctrl)            ((_pst_tx_ctrl)->bit_tx_vap_index)
#define MAC_GET_CB_TX_USER_IDX(_pst_tx_ctrl)             ((_pst_tx_ctrl)->bit_tx_user_idx)
#define MAC_GET_CB_ALG_PKTNO(_pst_tx_ctrl)               ((_pst_tx_ctrl)->uc_alg_pktno)
#define MAC_SET_CB_ALG_PKTNO(_pst_tx_ctrl, _pkt_no)      ((_pst_tx_ctrl)->uc_alg_pktno = (oal_uint8)_pkt_no)
#define MAC_GET_CB_RETRIED_NUM(_pst_tx_ctrl)             ((_pst_tx_ctrl)->bit_retried_num)
#define MAC_GET_CB_IS_PROBE_DATA(_pst_tx_ctrl)           ((_pst_tx_ctrl)->en_is_probe_data)

#define MAC_GET_CB_TIMESTAMP(_pst_tx_ctrl)                  ((_pst_tx_ctrl)->st_timestamp_us)
#define MAC_GET_CB_MPDU_BYTES(_pst_tx_ctrl)                 ((_pst_tx_ctrl)->us_mpdu_bytes)

/* DMACģ��������̿�����Ϣ�ṹ�����ϢԪ�ػ�ȡ */

/* 02 51 mac_rx_ctl_stru ��ͬԪ�ط�װ�ɺ� */
#define MAC_GET_RX_CB_DA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_da_user_idx)
#define MAC_GET_RX_CB_TA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_ta_user_idx)
#define MAC_GET_RX_CB_MAC_HEADER_LEN(_pst_rx_ctl)               ((_pst_rx_ctl)->bit_mac_header_len)
#define MAC_GET_RX_CB_FRAME_LEN(_pst_rx_ctl)                    ((_pst_rx_ctl)->us_frame_len)
#define MAC_GET_RX_PAYLOAD_ADDR(_pst_rx_ctl,_pst_buf)           (OAL_NETBUF_PAYLOAD(_pst_buf))
#define MAC_GET_RX_CB_HAL_VAP_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_vap_id)
#define MAC_GET_RX_CB_PAYLOAD_LEN(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_frame_len - (_pst_rx_ctl)->bit_mac_header_len)
#define MAC_INVALID_USER_INDEX                                   0xf
#else

/* ���Ϳ����ֶλ�ȡ */
#define MAC_GET_CB_MPDU_NUM(_pst_tx_ctrl)                       ((_pst_tx_ctrl)->uc_mpdu_num)
#define MAC_GET_CB_NETBUF_NUM(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->uc_netbuf_num)
#define MAC_GET_CB_MPDU_LEN(_pst_tx_ctrl)                       ((_pst_tx_ctrl)->us_mpdu_len)
#define MAC_GET_CB_IS_MCAST(_pst_tx_ctrl)                       ((_pst_tx_ctrl)->en_ismcast)
#define MAC_GET_CB_IS_EAPOL(_pst_tx_ctrl)                       ((_pst_tx_ctrl)->en_is_eapol)
#define MAC_GET_CB_IS_FROM_PS_QUEUE(_pst_tx_ctrl)               ((_pst_tx_ctrl)->en_is_get_from_ps_queue)
#define MAC_GET_CB_IS_FIRST_MSDU(_pst_tx_ctrl)                  ((_pst_tx_ctrl)->uc_is_first_msdu)
#define MAC_GET_CB_FRAME_HEADER_LENGTH(_pst_tx_ctrl)            ((_pst_tx_ctrl)->uc_frame_header_length)
#define MAC_GET_CB_IS_VIPFRAME(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->bit_is_vipframe)
#define MAC_GET_CB_IS_NEEDRETRY(_pst_tx_ctrl)                   ((_pst_tx_ctrl)->bit_is_needretry)

#define MAC_GET_CB_FRAME_TYPE(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->en_frame_type)

#define MAC_GET_CB_EVENT_TYPE(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->en_event_type)
#define MAC_GET_CB_TX_VAP_INDEX(_pst_tx_ctrl)                   ((_pst_tx_ctrl)->uc_tx_vap_index)
#define MAC_GET_CB_TX_USER_IDX(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->us_tx_user_idx)
#define MAC_GET_CB_ALG_PKTNO(_pst_tx_ctrl)                      ((_pst_tx_ctrl)->ul_alg_pktno)
#define MAC_SET_CB_ALG_PKTNO(_pst_tx_ctrl, _pkt_no)             ((_pst_tx_ctrl)->ul_alg_pktno = (oal_uint32)_pkt_no)
#define MAC_GET_CB_RETRIED_NUM(_pst_tx_ctrl)                    ((_pst_tx_ctrl)->uc_retried_num)
#define MAC_GET_CB_IS_PROBE_DATA(_pst_tx_ctrl)                  ((_pst_tx_ctrl)->en_is_probe_data)
#define MAC_GET_CB_TIMESTAMP(_pst_tx_ctrl)                      ((_pst_tx_ctrl)->st_timestamp_us)
#define MAC_GET_CB_MPDU_BYTES(_pst_tx_ctrl)                     ((_pst_tx_ctrl)->us_mpdu_bytes)

/* DMACģ��������̿�����Ϣ�ṹ�����ϢԪ�ػ�ȡ */

/* 02�У�51û�е��ֶ� */
#define MAC_GET_RX_CB_BIT_PROTOCOL_MODE(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_NSS_MCS_RATE(_pst_cb_ctrl)
#define MAC_GET_RX_CB_RSSI(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_RESPONSE_FLAG(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_VAP_INDEX(_pst_cb_ctrl)
#define MAC_GET_RX_ITRUP_SEQ_NUM(_pst_cb_ctrl)
#define MAC_GET_RX_CB_MAC_HDR_LEN(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_NUM_RX_BUFFERS(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_RECV_FLAGSS(_pst_cb_ctrl)
#define MAC_GET_RX_CB_NUM_MSDUS_IN_CUR_RX_BUFFER(_pst_cb_ctrl)
#define MAC_GET_RX_CB_BIT_CODE_BOOK(_pst_cb_ctrl)

/* 02 51 mac_rx_ctl_stru ��ͬԪ�ط�װ�ɺ� */
#define MAC_GET_RX_CB_DA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_da_user_idx)
#define MAC_GET_RX_CB_TA_USER_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_ta_user_idx)
#define MAC_GET_RX_CB_MAC_HEADER_LEN(_pst_rx_ctl)               ((_pst_rx_ctl)->uc_mac_header_len)
#define MAC_GET_RX_CB_FRAME_LEN(_pst_rx_ctl)                    ((_pst_rx_ctl)->us_frame_len)
#define MAC_GET_RX_PAYLOAD_ADDR(_pst_rx_ctl, _pst_buf) \
((oal_uint8 *)(mac_get_rx_cb_mac_hdr(_pst_rx_ctl)) + MAC_GET_RX_CB_MAC_HEADER_LEN(_pst_rx_ctl))
#define MAC_GET_RX_CB_HAL_VAP_IDX(_pst_rx_ctl)                  ((_pst_rx_ctl)->bit_vap_id)
#define MAC_GET_RX_CB_PAYLOAD_LEN(_pst_rx_ctl)                  ((_pst_rx_ctl)->us_frame_len - (_pst_rx_ctl)->uc_mac_header_len)
#define MAC_INVALID_USER_INDEX                                   0xffff

#endif

/*****************************************************************************
 �� �� ��  : dmac_board_get_instance
 ��������  : ��ȡDMAC board����
 �������  : ��
 �������  : DMAC board��������
 �� �� ֵ  : ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2012��11��16��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  dmac_board_get_instance(mac_board_stru **ppst_dmac_board)
{
    *ppst_dmac_board = &g_st_dmac_board;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_free_netbuf_list
 ��������  : �ӵ�ǰ��netbufָ�뿪ʼ���ͷź���n��netbufԪ��
 �������  : (1)ָ��netbuf����ͷ��ָ��
             (2)�ͷŵĸ���
 �������  : ������һ��Ҫ�����netbufָ��
 �� �� ֵ  : ������netbuf��ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��16��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_free_netbuf_list(
                oal_netbuf_head_stru       *pst_netbuf_hdr,
                oal_netbuf_stru           **pst_netbuf,
                oal_uint16                  us_nums)
{
    oal_netbuf_stru    *pst_netbuf_temp;
    oal_uint16          us_netbuf_num;
#ifdef _PRE_MEM_DEBUG_MODE
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
        oal_uint32 ul_return_addr      = __return_address();
#endif
#endif

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_netbuf_hdr) || (OAL_PTR_NULL == pst_netbuf)))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (us_netbuf_num = 0; us_netbuf_num < us_nums; us_netbuf_num++)
    {
        pst_netbuf_temp = oal_get_netbuf_next(*pst_netbuf);

        oal_netbuf_delete(*pst_netbuf, pst_netbuf_hdr);

        if(OAL_ERR_CODE_OAL_MEM_ALREADY_FREE==oal_netbuf_free(*pst_netbuf))
        {
           #ifdef _PRE_MEM_DEBUG_MODE
           #if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
            OAL_IO_PRINT("double free caller[%x]!\r\n",ul_return_addr);
           #endif
           #endif
        }

        *pst_netbuf = pst_netbuf_temp;
        if (pst_netbuf_hdr ==  (oal_netbuf_head_stru*)(*pst_netbuf))
        {
            break;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_get_cb_is_bar
 ��������  : �ж�ĳ��֡�Ƿ���bar
 �������  : pst_tx_ctrl CB
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_bar(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    mac_ieee80211_qos_htc_frame_stru   *pst_mac_naked_frame;

    pst_mac_naked_frame = (mac_ieee80211_qos_htc_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN);

    if ((WLAN_CONTROL      == pst_mac_naked_frame->st_frame_control.bit_type) &&
        (WLAN_BLOCKACK_REQ == pst_mac_naked_frame ->st_frame_control.bit_sub_type))
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
#else
    return pst_tx_ctrl->en_is_bar;

#endif
}

/*****************************************************************************
 �� �� ��  : mac_set_cb_is_bar
 ��������  : ����bar֡
 �������  : pst_tx_ctrl CB
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_bar(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_bar)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
   return;                                      //��ϵͳ������
#else
   pst_tx_ctrl->en_is_bar = uc_bar;
#endif
}

/*****************************************************************************
 �� �� ��  : mac_get_cb_is_qosdata
 ��������  : �ж�ĳ��֡�Ƿ���bar
 �������  : pst_tx_ctrl CB
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_qosdata(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    mac_ieee80211_qos_htc_frame_stru   *pst_mac_qos_htc_frame;
    oal_uint8                           ul_ret = OAL_FALSE;

    pst_mac_qos_htc_frame = (mac_ieee80211_qos_htc_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN);

    if (WLAN_DATA_BASICTYPE == pst_mac_qos_htc_frame->st_frame_control.bit_type)
    {
        if ((WLAN_QOS_DATA       == pst_mac_qos_htc_frame->st_frame_control.bit_sub_type) ||
            (WLAN_QOS_NULL_FRAME == pst_mac_qos_htc_frame->st_frame_control.bit_sub_type))
        {
            ul_ret = OAL_TRUE;
        }
    }

    return ul_ret;
#else
    return pst_tx_ctrl->en_is_qosdata;

#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_is_qosdata
 ��������  : �ж�ĳ��֡�Ƿ���bar
 �������  : pst_tx_ctrl CB
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��20��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_qosdata(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_is_qosdata)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return;
#else
    pst_tx_ctrl->en_is_qosdata = uc_en_is_qosdata;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_rx_cb_mac_hdr
 ��������  : ����macͷ��ֵ
 �������  : dmac_rx_ctl_stru *pst_cb_ctrl, oal_uint32 *pul_mac_hdr_start_addr
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl, oal_uint32 *pul_mac_hdr_start_addr)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return;
#else
    pst_cb_ctrl->pul_mac_hdr_start_addr = pul_mac_hdr_start_addr;

#endif
}
/*****************************************************************************
 �� �� ��  : mac_get_rx_cb_mac_hdr
 ��������  : ��ȡmacͷ��ֵ
 �������  : dmac_rx_ctl_stru *pst_cb_ctrl
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32 *mac_get_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return (oal_uint32 *)((oal_uint8 *)pst_cb_ctrl + OAL_MAX_CB_LEN);
#else
    return pst_cb_ctrl->pul_mac_hdr_start_addr;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_get_cb_tid
 ��������  : ��ȡtid��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_tid(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return pst_tx_ctrl->bit_tid;
#else
    return pst_tx_ctrl->uc_tid;
#endif
}

/*****************************************************************************
 �� �� ��  : mac_set_cb_tid
 ��������  : ����tid��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��21��
    ��    ��   : g00306640
    �޸�����   : �޸�ƫ�Ƶ�ַ��netbuf->data

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_tid(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_tid)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    pst_tx_ctrl->bit_tid = (uc_tid & 0x0F);
#else
    pst_tx_ctrl->uc_tid = uc_tid;

#endif
}

/*****************************************************************************
 �� �� ��  : mac_get_cb_is_amsdu
 ��������  : ��ȡamsdu��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_amsdu(mac_tx_ctl_stru *pst_tx_ctrl)
{
    return pst_tx_ctrl->en_is_amsdu;
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_is_amsdu
 ��������  : ����amsdu��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_amsdu(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_amsdu)
{
    pst_tx_ctrl->en_is_amsdu = uc_amsdu;
}
/*****************************************************************************
 �� �� ��  : mac_get_cb_ack_policy
 ��������  : ��ȡack_policy��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_ack_policy(mac_tx_ctl_stru *pst_tx_ctrl)
{
    return pst_tx_ctrl->en_ack_policy;
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_ack_policy
 ��������  : ����ack_policy��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_ack_policy(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_qc_ack_polocy)
{
    pst_tx_ctrl->en_ack_policy = uc_qc_ack_polocy;
}
/*****************************************************************************
 �� �� ��  : mac_get_cb_seqnum
 ��������  : ��ȡseqnum��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint16 mac_get_cb_seqnum(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return ((mac_ieee80211_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN))->bit_seq_num;
#else
    return pst_tx_ctrl->us_seqnum;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_ack_policy
 ��������  : ����ack_policy��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��6��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_seqnum(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint16 us_sc_seq_num)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
   ((mac_ieee80211_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN))->bit_seq_num = us_sc_seq_num;
#else
    pst_tx_ctrl->us_seqnum = us_sc_seq_num;
#endif
}

/*****************************************************************************
 �� �� ��  : mac_set_cb_sub_type
 ��������  : ����subtype��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_subtype
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��5��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_sub_type(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_subtype)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    (((mac_ieee80211_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN))->st_frame_control.bit_sub_type) = uc_subtype;

#else
    return;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_get_cb_ac
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_wme_ac_type_enum_uint8 mac_get_cb_ac(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    //oal_uint8   uc_tid = mac_get_cb_tid(pst_tx_ctrl);
    //return (WLAN_WME_TID_TO_AC(uc_tid));
    return pst_tx_ctrl->bit_ac;
#else
    return pst_tx_ctrl->uc_ac;

#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_ac
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_ac(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_wme_ac_type)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    pst_tx_ctrl->bit_ac = uc_wme_ac_type;
#else
    pst_tx_ctrl->uc_ac = uc_wme_ac_type;

#endif
}

/*****************************************************************************
 �� �� ��  : mac_get_cb_is_need_pause_tid
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE wlan_wme_ac_type_enum_uint8 mac_get_cb_is_need_pause_tid(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return OAL_FALSE;
#else
    return pst_tx_ctrl->en_need_pause_tid;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_en_need_pause_tid
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_need_pause_tid(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_need_pause_tid)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return;
#else
    pst_tx_ctrl->en_need_pause_tid = uc_en_need_pause_tid;
#endif
}

/*****************************************************************************
 �� �� ��  : mac_get_cb_is_need_pause_tid
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE mac_ieee80211_frame_stru *mac_get_cb_frame_hdr(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    mac_ieee80211_frame_stru *pst_frame_header;
    pst_frame_header = (mac_ieee80211_frame_stru *)((oal_uint8 *)pst_tx_ctrl + OAL_MAX_CB_LEN);
    return pst_frame_header;
#else
    return pst_tx_ctrl->pst_frame_header;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_is_need_pause_tid
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_frame_hdr(mac_tx_ctl_stru *pst_tx_ctrl, mac_ieee80211_frame_stru *pst_mac_hdr_addr)
{
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))
    return;
#else
    pst_tx_ctrl->pst_frame_header = pst_mac_hdr_addr;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_get_cb_is_need_pause_tid
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_use_4_addr(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return OAL_FALSE;
#else
    return pst_tx_ctrl->en_use_4_addr;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_is_need_pause_tid
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_use_4_addr(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_is_use_4_addr)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return;
#else
    pst_tx_ctrl->en_use_4_addr = uc_en_is_use_4_addr;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_get_cb_bar_dscr
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE hal_tx_dscr_stru *mac_get_cb_bar_dscr(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return OAL_PTR_NULL;
#else
    return pst_tx_ctrl->pst_bar_dscr;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_is_need_pause_tid
 ��������  : ����ac��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_bar_dscr(mac_tx_ctl_stru *pst_tx_ctrl, hal_tx_dscr_stru *pst_bar_dscr)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return;
#else
    pst_tx_ctrl->pst_bar_dscr = pst_bar_dscr;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_get_cb_80211_mac_head_type
 ��������  : ����bit_80211_mac_head_type��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_80211_mac_head_type(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return 1; //02��Ҫreturn 0 ���� 1?
#else
    return pst_tx_ctrl->bit_80211_mac_head_type;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_80211_mac_head_type
 ��������  : ����bit_80211_mac_head_type��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_80211_mac_head_type(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_80211_mac_head_type)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return;
#else
    pst_tx_ctrl->bit_80211_mac_head_type = uc_80211_mac_head_type;
#endif
}

/*****************************************************************************
 �� �� ��  : mac_get_cb_is_seq_ctrl_bypass
 ��������  : ��ȡen_seq_ctrl_bypass��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_is_seq_ctrl_bypass(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return mac_get_cb_is_qosdata(pst_tx_ctrl);
#else
    return pst_tx_ctrl->en_seq_ctrl_bypass;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_is_seq_ctrl_bypass
 ��������  : ����bit_80211_mac_head_type��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : L00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_is_seq_ctrl_bypass(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_seq_ctrl_bypass)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return;
#else
    pst_tx_ctrl->en_seq_ctrl_bypass = uc_en_seq_ctrl_bypass;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_get_cb_event_sub_type
 ��������  : ��ȡuc_event_sub_type��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl oal_uint8 uc_tid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 mac_get_cb_event_sub_type(mac_tx_ctl_stru *pst_tx_ctrl)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return 0;
#else
    return pst_tx_ctrl->uc_event_sub_type;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_set_cb_is_seq_ctrl_bypass
 ��������  : ����bit_80211_mac_head_type��ֵ
 �������  : mac_tx_ctl_stru *pst_tx_ctrl ,wlan_wme_ac_type_enum wlan_wme_ac_type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void mac_set_cb_event_sub_type(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_event_sub_type)
{
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    return;
#else
    pst_tx_ctrl->uc_event_sub_type = uc_en_event_sub_type;

#endif
}


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_int32  dmac_main_init(oal_void);
extern oal_void  dmac_main_exit(oal_void);
extern oal_void  dmac_alg_config_event_register(oal_uint32 p_func(frw_event_mem_stru *));
extern oal_void  dmac_alg_config_event_unregister(oal_void);
extern oal_uint32  dmac_tx_dump_get_switch(
                                    oam_user_track_frame_type_enum_uint8     en_frame_type,
                                    oal_uint8                               *pen_frame_switch,
                                    oal_uint8                               *pen_cb_switch,
                                    oal_uint8                               *pen_dscr_switch,
                                    mac_tx_ctl_stru                         *pst_tx_cb);
extern oal_uint32  dmac_tx_dump_get_user_macaddr(mac_tx_ctl_stru *pst_tx_cb,
                                             oal_uint8        auc_user_macaddr[]);

#ifdef _PRE_WLAN_PERFORM_STAT

/* ����ͳ��ģ�����ӿ� */

typedef enum
{
    DMAC_STAT_TX      = 0,      /* ��DMAC_STAT_PER_MAC_TOTAL��Ӧ */
    DMAC_STAT_RX      = 1,      /* ��DMAC_STAT_PER_BUFF_OVERFLOW��Ӧ */
    DMAC_STAT_BOTH    = 2,      /* ��DMAC_STAT_PER_BUFF_BE_SEIZED��Ӧ */

    DMAC_STAT_BUTT
}dmac_stat_direct;
typedef oal_uint8 dmac_stat_direct_enum_uint8;

typedef enum
{
    DMAC_STAT_PER_MAC_TOTAL             = 0,

    DMAC_STAT_PER_BUFF_OVERFLOW         = 1,
    DMAC_STAT_PER_BUFF_BE_SEIZED        = 2,
    DMAC_STAT_PER_DELAY_OVERTIME        = 3,
    DMAC_STAT_PER_SW_RETRY_AMPDU        = 4,
    DMAC_STAT_PER_SW_RETRY_SUB_AMPDU    = 5,
    DMAC_STAT_PER_SW_RETRY_MPDU         = 6,
    DMAC_STAT_PER_SW_RETRY_OVERFLOW     = 7,

    DMAC_STAT_PER_RTS_FAIL              = 8,
    DMAC_STAT_PER_HW_SW_FAIL            = 9,

    DMAC_STAT_PER_BUTT
}dmac_stat_per_reason;
typedef oal_uint8 dmac_stat_per_reason_enum_uint8;

typedef struct
{
    oam_module_id_enum_uint16      en_module_id;                    /* ��Ӧ��ģ��id */
    mac_stat_type_enum_uint8       en_stat_type;                    /* ͳ������ */
    oal_uint8                      uc_resv[1];

    oal_void                      *p_void;                          /* tid,user����vapָ�� */
    oal_uint32                     aul_stat_avg[DMAC_STAT_PER_BUTT];    /* ĳ�����ڵ�ͳ�ƽ�� */
}dmac_stat_param_stru;

/* ���ڲ�ģ����õ�ͳ�ƶ�ʱ�����ڴ�����ָ�� */
typedef oal_uint32  (*dmac_stat_timeout_func)(dmac_stat_param_stru *);

extern oal_uint32  dmac_stat_register(oam_module_id_enum_uint16         en_module_id,
                                        mac_stat_type_enum_uint8        en_stat_type,
                                        oal_void                       *p_void,
                                        dmac_stat_param_stru           *p_output_param,
                                        dmac_stat_timeout_func          p_func,
										oal_uint32						ul_core_id);

extern oal_uint32	dmac_stat_start(oam_module_id_enum_uint16      en_module_id,
                                     mac_stat_type_enum_uint8      en_stat_type,
                                     oal_uint16                    us_stat_period,
                                     oal_uint16                    us_stat_num,
                                     oal_void                      *p_void);

extern oal_uint32	dmac_stat_stop(oam_module_id_enum_uint16      en_module_id,
                                     mac_stat_type_enum_uint8     en_stat_type,
                                     oal_void                    *p_void);

extern oal_uint32	dmac_stat_unregister(oam_module_id_enum_uint16      en_module_id,
                                         mac_stat_type_enum_uint8       en_stat_type,
                                         oal_void                      *p_void);

#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_uint32  mac_user_check_txrx_protocol_change(
                                  mac_user_stru *pst_mac_user,
                                  oal_uint8      uc_present_mode,
                                  oam_user_info_change_type_enum_uint8  en_type);
#endif

#ifdef _PRE_WLAN_PERFORM_STAT
extern oal_uint32 dmac_stat_tid_per(mac_user_stru *pst_dmac_user,
                                    oal_uint8 uc_tidno,
                                    oal_uint16 us_mpdu_num,
                                    oal_uint16 us_err_mpdu_num,
                                    dmac_stat_per_reason_enum_uint8 en_per_reason);
#endif
extern oal_uint32  dmac_tid_pause(dmac_tid_stru *pst_tid, oal_uint8 uc_type);
extern oal_uint32  dmac_tid_resume(hal_to_dmac_device_stru *pst_hal_device, dmac_tid_stru *pst_tid, oal_uint8 uc_type);
extern oal_void mac_set_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl, oal_uint32 *pul_mac_hdr_start_addr);
extern oal_uint32 *mac_get_rx_cb_mac_hdr(mac_rx_ctl_stru *pst_cb_ctrl);
extern oal_uint8 mac_get_cb_is_bar(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_is_bar(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_bar);
extern oal_uint8 mac_get_cb_is_qosdata(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_qosdata(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8  uc_qos);
extern oal_void mac_set_cb_is_need_pause_tid(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_en_need_pause_tid);
extern oal_uint8 mac_get_cb_tid(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_tid(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_tid);
extern wlan_wme_ac_type_enum_uint8 mac_get_cb_ac(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_ac(mac_tx_ctl_stru *pst_tx_ctrl, oal_uint8 uc_wme_ac_type);
extern wlan_wme_ac_type_enum_uint8 mac_get_cb_need_pause_tid(mac_tx_ctl_stru *pst_tx_ctrl);
extern mac_ieee80211_frame_stru *mac_get_cb_frame_hdr(mac_tx_ctl_stru *pst_tx_ctrl);
extern oal_void mac_set_cb_frame_hdr(mac_tx_ctl_stru *pst_tx_ctrl, mac_ieee80211_frame_stru *pul_mac_hdr_addr);
#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
extern oal_uint32  dmac_config_set_qap_cwmin(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
#endif

#if (_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
extern oal_uint32 dmac_init_event_process(frw_event_mem_stru *pst_event_mem);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

#if 0
extern oal_uint32 dmac_init_event_create_cfg_vap(frw_event_mem_stru *pst_event_mem);
#else
extern oal_uint32 dmac_cfg_vap_init_event(frw_event_mem_stru *pst_event_mem);
#endif

#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_ext_if.h */
