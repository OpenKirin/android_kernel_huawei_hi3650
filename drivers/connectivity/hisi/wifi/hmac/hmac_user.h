/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_user.h
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   : hmac_user.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __HMAC_USER_H__
#define __HMAC_USER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "mac_user.h"
#include "mac_resource.h"
#include "hmac_ext_if.h"
#include "dmac_ext_if.h"
#include "hmac_edca_opt.h"
#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "hmac_btcoex.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_USER_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define HMAC_ADDBA_EXCHANGE_ATTEMPTS        10  /* ��ͼ����ADDBA�Ự������������ */

#define HMAC_USER_IS_AMSDU_SUPPORT(_user, _tid)         (((_user)->uc_amsdu_supported) & (0x01 << ((_tid) & 0x07)))

#define HMAC_USER_SET_AMSDU_SUPPORT(_user, _tid)        (((_user)->uc_amsdu_supported) |= (0x01 << ((_tid) & 0x07)))

#define HMAC_USER_SET_AMSDU_NOT_SUPPORT(_user, _tid)    (((_user)->uc_amsdu_supported) &= (oal_uint8)(~(0x01 << ((_tid) & 0x07))))

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
#define MAX_JUDGE_CACHE_LENGTH      20  /* ҵ��ʶ��-�û���ʶ����г��� */
#define MAX_CONFIRMED_FLOW_NUM      2   /* ҵ��ʶ��-�û���ʶ��ҵ������ */
#endif

#define   HMAC_USER_STATS_PKT_INCR(_member, _cnt)            ((_member) += (_cnt))

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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
/* TID��Ӧ�ķ���BA�Ự��״̬ */
typedef struct
{
    dmac_ba_conn_status_enum_uint8  en_ba_status;       /* ��TID��Ӧ��BA�Ự��״̬ */
    oal_uint8                       uc_addba_attemps;   /* ��������BA�Ự�Ĵ��� */
    oal_uint8                       uc_dialog_token;    /* �������� */
    oal_bool_enum_uint8             en_ba_switch;
    frw_timeout_stru                st_addba_timer;
    dmac_ba_alarm_stru              st_alarm_data;
}hmac_ba_tx_stru;

typedef struct
{
    oal_bool_enum_uint8                     in_use;                     /* ����BUF�Ƿ�ʹ�� */
    oal_uint8                               uc_num_buf;                 /* MPDUռ�õ�netbuf(����������)���� */
    oal_uint16                              us_seq_num;                 /* MPDU��Ӧ�����к� */
    oal_netbuf_head_stru                    st_netbuf_head;             /* MPDU��Ӧ���������׵�ַ */
    oal_uint32                              ul_rx_time;                 /* ���ı������ʱ��� */
} hmac_rx_buf_stru;

typedef struct
{
    oal_void                               *pst_ba;
    oal_uint8                               uc_tid;
    mac_delba_initiator_enum_uint8          en_direction;
    oal_uint8                               uc_resv[1];
    oal_uint8                               uc_vap_id;
    oal_uint16                              us_mac_user_idx;
    oal_uint16                              us_timeout_times;

}hmac_ba_alarm_stru;

/*Hmac����ղ�BA�Ự��� */
typedef struct
{
    oal_uint16                      us_baw_start;               /* ��һ��δ�յ���MPDU�����к� */
    oal_uint16                      us_baw_end;                 /* ���һ�����Խ��յ�MPDU�����к� */
    oal_uint16                      us_baw_tail;                /* ĿǰRe-Order�����У��������к� */
    oal_uint16                      us_baw_size;                /* Block_Ack�Ự��buffer size��С */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_spin_lock_stru              st_ba_lock;                 /* 02����hcc�̺߳��¼��̲߳��� */
#endif

    oal_bool_enum_uint8             en_timer_triggered;         /* ��һ���ϱ��Ƿ�Ϊ��ʱ���ϱ� */
    oal_bool_enum_uint8             en_is_ba;                   /* Session Valid Flag */
    dmac_ba_conn_status_enum_uint8  en_ba_status;               /* ��TID��Ӧ��BA�Ự��״̬ */
    oal_uint8                       uc_mpdu_cnt;                /* ��ǰRe-Order�����У�MPDU����Ŀ */

    hmac_rx_buf_stru                ast_re_order_list[WLAN_AMPDU_RX_BUFFER_SIZE];  /* Re-Order���� */
    hmac_ba_alarm_stru              st_alarm_data;
    /* frw_timeout_stru                st_ba_timer; */

    /*����action֡���*/
    mac_back_variant_enum_uint8     en_back_var;        /* BA�Ự�ı��� */
    oal_uint8                       uc_dialog_token;    /* ADDBA����֡��dialog token */
    oal_uint8                       uc_ba_policy;       /* Immediate=1 Delayed=0 */
    oal_uint8                       uc_lut_index;       /* ���ն�Session H/w LUT Index */
    oal_uint16                      us_status_code;     /* ����״̬�� */
    oal_uint16                      us_ba_timeout;      /* BA�Ự������ʱʱ�� */
    oal_uint8                      *puc_transmit_addr;  /* BA�Ự���Ͷ˵�ַ */
    oal_bool_enum_uint8             en_amsdu_supp;      /* BLOCK ACK֧��AMSDU�ı�ʶ */
    oal_uint8                       auc_resv1[1];
    oal_uint16                      us_baw_head;        /* bitmap����ʼ���к� */
    oal_uint32                      aul_rx_buf_bitmap[2];
}hmac_ba_rx_stru;

/* user�ṹ�У�TID��Ӧ��BA��Ϣ�ı���ṹ */
typedef struct
{
    oal_uint8               uc_tid_no;
    oal_bool_enum_uint8     en_ampdu_start;             /* ��ʶ��tid�µ�AMPDU�Ƿ��Ѿ������� */
    oal_uint16              us_hmac_user_idx;
    hmac_ba_tx_stru         st_ba_tx_info;
    hmac_ba_rx_stru        *pst_ba_rx_info;             /* ���ڲ��ִ������ƣ��ⲿ���ڴ浽LocalMem������ */
    frw_timeout_stru        st_ba_timer;                /* ���������򻺳峬ʱ */
}hmac_tid_stru;
typedef struct
{
    oal_uint32  bit_short_preamble      : 1,        /* �Ƿ�֧��802.11b��ǰ���� 0=��֧�֣� 1=֧��*/
                bit_erp                 : 1,        /* AP����STA����ʹ��,ָʾuser�Ƿ���ERP������ 0=��֧�֣�1=֧��*/
                bit_short_slot_time     : 1,        /* ��ʱ϶: 0=��֧��, 1=֧�� */
                bit_11ac2g              : 1,
                bit_resv                : 28;
}hmac_user_cap_info_stru;

#ifdef _PRE_WLAN_FEATURE_WAPI
#define WAPI_KEY_LEN                    16
#define WAPI_PN_LEN                     16
#define HMAC_WAPI_MAX_KEYID             2


typedef struct
{
    oal_uint32 ulrx_mic_calc_fail;           /* ���ڲ���������mic������� */
    oal_uint32 ultx_ucast_drop;              /* ����Э��û����ɣ���֡drop�� */
    oal_uint32 ultx_wai;
    oal_uint32 ultx_port_valid;             /* Э����ɵ�����£����͵�֡���� */
    oal_uint32 ulrx_port_valid;             /* Э����ɵ�����£����յ�֡���� */
    oal_uint32 ulrx_idx_err;                /* ����idx������� */
    oal_uint32 ulrx_netbuff_len_err;        /* ����netbuff���ȴ��� */
    oal_uint32 ulrx_idx_update_err;         /* ��Կ���´��� */
    oal_uint32 ulrx_key_en_err;             /* ��Կû��ʹ�� */
    oal_uint32 ulrx_pn_odd_err;             /* PN��żУ����� */
    oal_uint32 ulrx_pn_replay_err;          /* PN�ط� */
    oal_uint32 ulrx_memalloc_err;           /* rx�ڴ�����ʧ�� */
    oal_uint32 ulrx_decrypt_ok;             /* ���ܳɹ��Ĵ��� */

    oal_uint32 ultx_memalloc_err;            /* �ڴ����ʧ�� */
    oal_uint32 ultx_mic_calc_fail;           /* ���ڲ���������mic������� */
    //oal_uint32 ultx_drop_wai;              /* wai֡drop�Ĵ��� */
    oal_uint32 ultx_encrypt_ok;              /* ���ܳɹ��Ĵ��� */
    oal_uint8  aucrx_pn[WAPI_PN_LEN];       /* ���ⷢ��ʱ����¼���շ���֡��PN,��pn����ʱ��ˢ�� */

}hmac_wapi_debug;

typedef struct
{
    oal_uint8   auc_wpi_ek[WAPI_KEY_LEN];
    oal_uint8   auc_wpi_ck[WAPI_KEY_LEN];
    oal_uint8   auc_pn_rx[WAPI_PN_LEN];
    oal_uint8   auc_pn_tx[WAPI_PN_LEN];
    oal_uint8   uc_key_en;
    oal_uint8   auc_rsv[3];
}hmac_wapi_key_stru;

typedef struct tag_hmac_wapi_stru
{
    oal_uint8              uc_port_valid;                       /* wapi���ƶ˿� */
    oal_uint8              uc_keyidx;
    oal_uint8              uc_keyupdate_flg;                    /* key���±�־ */
    oal_uint8              uc_pn_inc;                           /* pn����ֵ */

    hmac_wapi_key_stru     ast_wapi_key[HMAC_WAPI_MAX_KEYID];   /*keyed: 0~1 */

#ifdef _PRE_WAPI_DEBUG
    hmac_wapi_debug        st_debug;                            /* ά�� */
#endif

    oal_uint8               (*wapi_filter_frame)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru *pst_netbuff);
    oal_bool_enum_uint8     (*wapi_is_pn_odd)(oal_uint8 *puc_pn);     /* �ж�pn�Ƿ�Ϊ���� */
    oal_uint32              (*wapi_decrypt)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru *pst_netbuff);
    oal_uint32              (*wapi_encrypt)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_netbuf);
    oal_netbuf_stru        *(*wapi_netbuff_txhandle)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_netbuf);
    oal_netbuf_stru        *(*wapi_netbuff_rxhandle)(struct tag_hmac_wapi_stru *pst_wapi, oal_netbuf_stru  *pst_netbuf);
}hmac_wapi_stru;

#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
/* ҵ��ʶ��-��Ԫ��ṹ��: ����Ψһ�ر�ʶҵ���� */
typedef struct
{
    oal_uint32                          ul_sip;                         /* ip */
    oal_uint32                          ul_dip;

    oal_uint16                          us_sport;                       /* �˿� */
    oal_uint16                          us_dport;

    oal_uint32                          ul_proto;                       /* Э�� */

}hmac_tx_flow_info_stru;

/* ҵ��ʶ��-��ʶ����нṹ��: */
typedef struct
{
    hmac_tx_flow_info_stru              st_flow_info;

    oal_uint32                          ul_len;                        /* �������� */
    oal_uint8                           uc_flag;                       /* ��Чλ�����ڼ��� */

    oal_uint8                           uc_udp_flag;                   /* udp flagΪ1��ΪUDP֡ */
    oal_uint8                           uc_tcp_flag;                   /* tcp flagΪ1��ΪTCP֡ */

    oal_uint8                           uc_rtpver;                     /* RTP version */
    oal_uint32                          ul_rtpssrc;                    /* RTP SSRC */
    oal_uint32                          ul_payload_type;               /* RTP:���1bit����Ч�غ�����(PT)7bit */

}hmac_tx_judge_info_stru;

/* ҵ��ʶ��-��ʶ�������Ҫҵ��ṹ��: */
typedef struct
{
    hmac_tx_flow_info_stru              st_flow_info;

    oal_uint32                          ul_average_len;                /* ҵ������ƽ������ */
    oal_uint8                           uc_flag;                       /* ��Чλ */

    oal_uint8                           uc_udp_flag;                   /* udp flagΪ1��ΪUDP֡ */
    oal_uint8                           uc_tcp_flag;                   /* tcp flagΪ1��ΪTCP֡ */

    oal_uint8                           uc_rtpver;                     /* RTP version */
    oal_uint32                          ul_rtpssrc;                    /* RTP SSRC */
    oal_uint32                          ul_payload_type;               /* ���1bit����Ч�غ�����(PT)7bit */

    oal_uint32                          ul_wait_check_num;             /* ������б��д�ҵ������� */

}hmac_tx_major_flow_stru;

/* ҵ��ʶ��-�û���ʶ��ṹ��: */
typedef struct
{
    hmac_tx_flow_info_stru              st_cfm_flow_info;               /* ��ʶ��ҵ�����Ԫ����Ϣ */

    oal_uint32                          ul_last_jiffies;                /* ��¼��ʶ��ҵ�����������ʱ�� */
    oal_uint16                          us_cfm_tid;                     /* ��ʶ��ҵ��tid */

    oal_uint16                          us_cfm_flag;                        /* ��Чλ */

}hmac_tx_cfm_flow_stru;


/* ҵ��ʶ��-�û���ʶ��ҵ�����: */
typedef struct
{
    oal_uint32                          ul_jiffies_st;                                  /* ��¼��ʶ��ҵ����е���ʼʱ������������ʱ�� */
    oal_uint32                          ul_jiffies_end;
    oal_uint32                          ul_to_judge_num;                                /* �û���ʶ��ҵ����г��� */

    hmac_tx_judge_info_stru             ast_judge_cache[MAX_JUDGE_CACHE_LENGTH];     /* ��ʶ�������� */

}hmac_tx_judge_list_stru;
#endif

/* �����ýṹ���������һ��Ҫ����oal_memzero */
typedef struct
{
    /* ��ǰVAP������AP��STAģʽ�������ֶ�Ϊuser��STA��APʱ�����ֶΣ�������ֶ���ע��!!! */
    oal_uint8                       uc_is_wds;                                  /* �Ƿ���wds�û� */
    oal_uint8                       uc_amsdu_supported;                     /* ÿ��λ����ĳ��TID�Ƿ�֧��AMSDU */
    oal_uint16                      us_amsdu_maxsize;                           /* amsdu��󳤶� */
    hmac_amsdu_stru                 ast_hmac_amsdu[WLAN_WME_MAX_TID_NUM];       /* asmdu���� */
    hmac_tid_stru                   ast_tid_info[WLAN_TID_MAX_NUM];             /* ������TID��ص���Ϣ */
    oal_uint32                      aul_last_timestamp[WLAN_TID_MAX_NUM];       /* ʱ�������ʵ��5���������Ľ���BA */
    oal_uint8                       auc_ch_text[WLAN_CHTXT_SIZE];               /* WEP�õ���ս���� */
    frw_timeout_stru                st_mgmt_timer;                              /* ��֤�����ö�ʱ�� */
    frw_timeout_stru                st_defrag_timer;                            /* ȥ��Ƭ��ʱ��ʱ�� */
    oal_netbuf_stru                *pst_defrag_netbuf;
    oal_uint8                       auc_ba_flag[WLAN_TID_MAX_NUM];          /* �ñ�־��ʾ��TID�Ƿ���Խ���BA�Ự�����ڵ���5ʱ���Խ���BA�Ự���ñ�־���û���ʼ����ɾ��BA�Ựʱ���� */
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    mac_sa_query_stru               st_sa_query_info;                       /* sa query���̵Ŀ�����Ϣ */
#endif
    mac_rate_stru                   st_op_rates;                            /* user��ѡ���� AP�ౣ��STA���ʣ�STA�ౣ��AP���� */
    hmac_user_cap_info_stru         st_hmac_cap_info;                       /* hmac���û�������־λ */
    oal_uint32                      ul_rssi_last_timestamp;                 /* ��ȡuser rssi����ʱ���, 1s������һ��rssi */

    /* ��ǰVAP������APģʽ�������ֶ�Ϊuser��STAʱ�����ֶΣ�������ֶ���ע��!!! */
    oal_uint32                      ul_assoc_req_ie_len;
    oal_uint8                      *puc_assoc_req_ie_buff;
    oal_bool_enum_uint8             en_user_bw_limit;                       /* �����Ƿ������� */
    oal_uint8                       auc_resv1[3];

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    oal_uint32                      aaul_txrx_data_stat[WLAN_WME_AC_BUTT][WLAN_TXRX_DATA_BUTT];       /* ����/���� tcp/udp be,bk,vi,vo���� */
#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
    hmac_wapi_stru                  st_wapi;
#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
    oal_uint8                       uc_cfm_num;                                         /* �û��ѱ�ʶ��ҵ����� */
    oal_uint8                       auc_resv2[3];
    hmac_tx_cfm_flow_stru           ast_cfm_flow_list[MAX_CONFIRMED_FLOW_NUM];          /* ��ʶ��ҵ�� */
    hmac_tx_judge_list_stru         st_judge_list;                                      /* ��ʶ�������� */

    //oal_spin_lock_stru          st_lock;

#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    hmac_user_btcoex_stru          st_hmac_user_btcoex;
#endif

    /* ��ǰVAP������STAģʽ�������ֶ�Ϊuser��APʱ�����ֶΣ�������ֶ���ע��!!! */
    mac_user_stats_flag_stru        st_user_stats_flag;                      /*��user��staʱ��ָʾuser�Ƿ�ͳ�Ƶ���Ӧ��*/
    oal_uint32                      ul_rx_pkt_drop;                      /* �������ݰ�host�౻drop�ļ��� */

    oal_uint32                      ul_first_add_time;                          /* �û�����ʱ��ʱ�䣬����ͳ���û�����ʱ�� */

    /* dmac����ͬ����Ϣ */
    oal_int8                        c_rssi;
#ifdef _PRE_WLAN_DFT_STAT
    oal_uint8                       uc_cur_per;
    oal_uint8                       uc_bestrate_per;
	oal_uint8                       auc_resv3[1];
#endif
    oal_uint32                      ul_tx_rate;
    oal_uint32                      ul_tx_rate_min;
    oal_uint32                      ul_tx_rate_max;
    oal_uint32                      ul_rx_rate;
    oal_uint32                      ul_rx_rate_min;
    oal_uint32                      ul_rx_rate_max;

    /* ����������ܴ���HMAC USER�ṹ���ڵ����һ�� */
    mac_user_stru                   st_user_base_info;                          /* hmac user��dmac user�������� */

}hmac_user_stru;

/*SA Query ��ʱ��ʱ�� �� �����ʱ�� �ĳ�ʱ������νṹ*/
typedef struct
{
    mac_vap_stru     *pst_mac_vap;                  /* ����SA Query request��mac vap��Ϣ */
    hmac_user_stru   *pst_hmac_user;                /* Ŀ��user */
}hmac_maxtimeout_timer_stru;
typedef struct
{
    mac_vap_stru       *pst_mac_vap;                  /* ����SA Query request��mac vap��Ϣ */
    hmac_user_stru     *pst_hmac_user;                /* Ŀ��user */
    oal_bool_enum_uint8 en_is_protected;              /* SA Query����֡���ܵ�ʹ�ܿ��� */
    oal_uint16          us_trans_id;                  /* SA Query request֡��trans id */
}hmac_interval_timer_stru;

/* �洢AP��������֡��ie��Ϣ�������ϱ��ں� */
typedef struct
{
    oal_uint32                      ul_assoc_req_ie_len;
    oal_uint8                      *puc_assoc_req_ie_buff;
    oal_uint8                       auc_user_mac_addr[WLAN_MAC_ADDR_LEN];
}hmac_asoc_user_req_ie_stru;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hmac_user_ht_support
 ��������  : �Ƿ�ΪHT�û�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_TRUE�ǣ�OAL_FALSE����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��11��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_user_ht_support(hmac_user_stru *pst_hmac_user)
{
    if (OAL_TRUE == pst_hmac_user->st_user_base_info.st_ht_hdl.en_ht_capable)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_user_vht_support
 ��������  : �Ƿ�ΪVHT�û�
 �������  : hmac_user_stru *pst_hmac_user
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��12��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_user_vht_support(hmac_user_stru *pst_hmac_user)
{
    if (OAL_TRUE == pst_hmac_user->st_user_base_info.st_vht_hdl.en_vht_capable)
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_user_xht_support
 ��������  : �Ƿ�֧��ht/vht�ۺ�
 �������  : hmac_user_stru *pst_hmac_user
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��12��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_bool_enum_uint8 hmac_user_xht_support(hmac_user_stru *pst_hmac_user)
{
    if ((pst_hmac_user->st_user_base_info.en_cur_protocol_mode >= WLAN_HT_MODE)
        && (pst_hmac_user->st_user_base_info.en_cur_protocol_mode < WLAN_PROTOCOL_BUTT))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  hmac_user_alloc(oal_uint16 *pus_user_idx);
extern oal_uint32  hmac_user_free(oal_uint16 us_idx);
extern oal_uint32  hmac_user_init(hmac_user_stru *pst_hmac_user);
extern oal_uint32  hmac_user_set_avail_num_space_stream(mac_user_stru *pst_mac_user, wlan_nss_enum_uint8 en_vap_nss);
extern oal_uint32  hmac_user_del(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user);
extern oal_uint32  hmac_user_add(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mac_addr, oal_uint16 *pus_user_index);
extern oal_uint32  hmac_user_add_multi_user(mac_vap_stru *pst_mac_vap, oal_uint16 *us_user_index);
extern oal_uint32  hmac_user_del_multi_user(mac_vap_stru *pst_mac_vap);
extern oal_uint32 hmac_user_add_notify_alg(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx);
extern oal_uint32 hmac_update_user_last_active_time(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param);
extern oal_void hmac_tid_clear(mac_vap_stru *pst_mac_vap, hmac_user_stru *pst_hmac_user);
extern hmac_user_stru*  mac_res_get_hmac_user_alloc(oal_uint16 us_idx);
extern hmac_user_stru*  mac_res_get_hmac_user(oal_uint16 us_idx);
extern hmac_user_stru  *mac_vap_get_hmac_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr);


#ifdef _PRE_WLAN_FEATURE_WAPI
extern hmac_wapi_stru *hmac_user_get_wapi_ptr(mac_vap_stru *pst_mac_vap, oal_bool_enum_uint8 en_pairwise, oal_uint16 us_pairwise_idx);
extern oal_uint8  hmac_user_is_wapi_connected(oal_uint8 uc_device_id);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_user.h */
