/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mac_user.h
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   : mac_user.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __MAC_USER_H__
#define __MAC_USER_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "wlan_spec.h"
#include "wlan_types.h"
#include "wlan_mib.h"
#include "mac_frame.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_USER_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MAC_ACTIVE_USER_IDX_BMAP_LEN        ((WLAN_ACTIVE_USER_MAX_NUM >> 3) + 1)   /* ��Ծ�û�����λͼ */
#define MAC_INVALID_RA_LUT_IDX              WLAN_ACTIVE_USER_MAX_NUM                /* �����õ�RA LUT IDX */
#define MAC_USER_INIT_STREAM        1
#define MAC_INVALID_USER_ID         0xffff   /* ��Ч��user idx */

#define MAC_USER_FREED              0xff         /* USER��Դδ���� */
#define MAC_USER_ALLOCED            0x5a         /* USER�ѱ����� */

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
/* user tx�������Ӽܹ������ĵ���ó�Ա */
typedef struct
{
    wlan_security_txop_params_stru       st_security;
}mac_user_tx_param_stru;

typedef struct
{
    oal_uint8        uc_rs_nrates;                                 /* ���� */
    oal_uint8        auc_rs_rates[WLAN_RATE_MAXSIZE];              /* ���� */
}mac_rate_stru;


typedef struct
{
    oal_uint32  bit_spectrum_mgmt       : 1,        /* Ƶ�׹���: 0=��֧��, 1=֧�� */
                bit_qos                 : 1,        /* QOS: 0=��QOSվ��, 1=QOSվ�� */
                bit_barker_preamble_mode: 1,        /* ��STA����BSS��վ���Ƿ�֧��short preamble�� 0=֧�֣� 1=��֧�� */
                bit_apsd                : 1,        /* �Զ�����: 0=��֧��, 1=֧�� *//* Ŀǰbit_apsdֻ��дû�ж���wifi�������Լ�������WMM����IE����cap apsd���� ,�˴�Ԥ��Ϊ�������ܳ��ļ����������ṩ�ӿ� */
                bit_pmf_active          : 1,        /* ����֡����ʹ�ܿ���*/
                bit_erp_use_protect     : 1,        /* ��STA����AP�Ƿ�������ERP���� */
                bit_11ntxbf             : 1,
                bit_proxy_arp           : 1,
                bit_histream_cap        : 1,
                bit_resv                : 23;
}mac_user_cap_info_stru;

/* user��ht�����Ϣ */
typedef struct
{
    /* ht cap */
    oal_bool_enum_uint8 en_ht_capable;                                /* HT capable              */
    oal_uint8           uc_max_rx_ampdu_factor;                       /* Max AMPDU Rx Factor     */
    oal_uint8           uc_min_mpdu_start_spacing;                    /* Min AMPDU Start Spacing */
    oal_uint8           uc_htc_support;                               /* HTC ��֧��              */

    oal_uint16          bit_ldpc_coding_cap         : 1,              /* LDPC ���� capability    */
                        bit_supported_channel_width : 1,              /* STA ֧�ֵĴ���   0: 20Mhz, 1: 20/40Mhz  */
                        bit_sm_power_save           : 2,              /* SM ʡ��ģʽ             */
                        bit_ht_green_field          : 1,              /* ��Ұģʽ                */
                        bit_short_gi_20mhz          : 1,              /* 20M�¶̱������         */
                        bit_short_gi_40mhz          : 1,              /* 40M�¶̱������         */
                        bit_tx_stbc                 : 1,              /* Indicates support for the transmission of PPDUs using STBC */
                        bit_rx_stbc                 : 2,              /* ֧�� Rx STBC            */
                        bit_ht_delayed_block_ack    : 1,              /* Indicates support for HT-delayed Block Ack opera-tion. */
                        bit_max_amsdu_length        : 1,              /* Indicates maximum A-MSDU length. */
                        bit_dsss_cck_mode_40mhz     : 1,              /* 40M�� DSSS/CCK ģʽ     0:��ʹ�� 40M dsss/cck, 1: ʹ�� 40M dsss/cck */
                        bit_resv                    : 1,
                        bit_forty_mhz_intolerant    : 1,              /* Indicates whether APs receiving this information or reports of this informa-tion are required to prohibit 40 MHz transmissions */
                        bit_lsig_txop_protection    : 1;              /* ֧�� L-SIG TXOP ����    */

    oal_uint8           uc_rx_mcs_bitmask[WLAN_HT_MCS_BITMASK_LEN];   /* Rx MCS bitmask */

    /* ht operation, VAP��STA, user��AP���� */
    oal_uint8           uc_primary_channel;

    oal_uint8           bit_secondary_chan_offset             : 2,
                        bit_sta_chan_width                    : 1,
                        bit_rifs_mode                         : 1,
                        bit_HT_protection                     : 2,
                        bit_nongf_sta_present                 : 1,
                        bit_obss_nonht_sta_present            : 1;

    oal_uint8           bit_dual_beacon                       : 1,
                        bit_dual_cts_protection               : 1,
                        bit_secondary_beacon                  : 1,
                        bit_lsig_txop_protection_full_support : 1,
                        bit_pco_active                        : 1,
                        bit_pco_phase                         : 1,
                        bit_resv6                             : 2;

    oal_uint8           auc_resv[1];

    oal_uint8           auc_basic_mcs_set[16];

	oal_uint32          bit_imbf_receive_cap                :   1,  /*��ʽTxBf��������*/
                        bit_receive_staggered_sounding_cap  :   1,  /*���ս���̽��֡������*/
                        bit_transmit_staggered_sounding_cap :   1,  /*���ͽ���̽��֡������*/
                        bit_receive_ndp_cap                 :   1,  /*����NDP����*/
                        bit_transmit_ndp_cap                :   1,  /*����NDP����*/
                        bit_imbf_cap                        :   1,  /*��ʽTxBf����*/
                        bit_calibration                     :   2,  /*0=��֧�֣�1=վ�������CSI������ӦУ׼���󣬵����ܷ���У׼��2=������3=վ����Է���Ҳ������ӦУ׼����*/
                        bit_exp_csi_txbf_cap                :   1,  /*Ӧ��CSI��������TxBf������*/
                        bit_exp_noncomp_txbf_cap            :   1,  /*Ӧ�÷�ѹ���������TxBf������*/
                        bit_exp_comp_txbf_cap               :   1,  /*Ӧ��ѹ���������TxBf������*/
                        bit_exp_csi_feedback                :   2,  /*0=��֧�֣�1=�ӳٷ�����2=����������3=�ӳٺ���������*/
                        bit_exp_noncomp_feedback            :   2,  /*0=��֧�֣�1=�ӳٷ�����2=����������3=�ӳٺ���������*/
                        bit_exp_comp_feedback               :   2,  /*0=��֧�֣�1=�ӳٷ�����2=����������3=�ӳٺ���������*/
                        bit_min_grouping                    :   2,  /*0=�����飬1=1,2���飬2=1,4���飬3=1,2,4����*/
                        bit_csi_bfer_ant_number             :   2,  /*CSI����ʱ��bfee���֧�ֵ�beamformer��������0=1Tx����̽�⣬1=2Tx����̽�⣬2=3Tx����̽�⣬3=4Tx����̽��*/
                        bit_noncomp_bfer_ant_number         :   2,  /*��ѹ��������ʱ��bfee���֧�ֵ�beamformer��������0=1Tx����̽�⣬1=2Tx����̽�⣬2=3Tx����̽�⣬3=4Tx����̽��*/
                        bit_comp_bfer_ant_number            :   2,  /*ѹ��������ʱ��bfee���֧�ֵ�beamformer��������0=1Tx����̽�⣬1=2Tx����̽�⣬2=3Tx����̽�⣬3=4Tx����̽��*/
                        bit_csi_bfee_max_rows               :   2,  /*bfer֧�ֵ�����bfee��CSI��ʾ�������������*/
                        bit_channel_est_cap                 :   2,  /*�ŵ����Ƶ�������0=1��ʱ�������ε���*/
                        bit_reserved                        :   3;
}mac_user_ht_hdl_stru;

typedef struct
{
oal_uint16              us_max_mcs_1ss : 2,                             /* һ���ռ�����MCS���֧��MAP */
                        us_max_mcs_2ss : 2,                             /* һ���ռ�����MCS���֧��MAP */
                        us_max_mcs_3ss : 2,                             /* һ���ռ�����MCS���֧��MAP */
                        us_max_mcs_4ss : 2,                             /* һ���ռ�����MCS���֧��MAP */
                        us_max_mcs_5ss : 2,                             /* һ���ռ�����MCS���֧��MAP */
                        us_max_mcs_6ss : 2,                             /* һ���ռ�����MCS���֧��MAP */
                        us_max_mcs_7ss : 2,                             /* һ���ռ�����MCS���֧��MAP */
                        us_max_mcs_8ss : 2;                             /* һ���ռ�����MCS���֧��MAP */
}mac_max_mcs_map_stru;

typedef mac_max_mcs_map_stru mac_tx_max_mcs_map_stru;
typedef mac_max_mcs_map_stru mac_rx_max_mcs_map_stru;

typedef struct
{
    oal_uint16  us_max_mpdu_length;
    oal_uint16  us_basic_mcs_set;

    oal_uint32  bit_max_mpdu_length         : 2,
                bit_supported_channel_width : 2,
                bit_rx_ldpc                 : 1,
                bit_short_gi_80mhz          : 1,
                bit_short_gi_160mhz         : 1,
                bit_tx_stbc                 : 1,
                bit_rx_stbc                 : 3,
                bit_su_beamformer_cap       : 1,                       /* SU bfer������Ҫ��AP��֤��������1 */
                bit_su_beamformee_cap       : 1,                       /* SU bfee������Ҫ��STA��֤��������1 */
                bit_num_bf_ant_supported    : 3,                       /* SUʱ��������NDP��Nsts����С��1 */
                bit_num_sounding_dim        : 3,                       /* SUʱ����ʾNsts���ֵ����С��1 */
                bit_mu_beamformer_cap       : 1,                       /* ��֧�֣�set to 0 */
                bit_mu_beamformee_cap       : 1,                       /* ��֧�֣�set to 0 */
                bit_vht_txop_ps             : 1,
                bit_htc_vht_capable         : 1,
                bit_max_ampdu_len_exp       : 3,
                bit_vht_link_adaptation     : 2,
                bit_rx_ant_pattern          : 1,
                bit_tx_ant_pattern          : 1,
                bit_resv1                   : 2;                       /* ����vht Capabilities IE: VHT Capabilities Info field */

    mac_tx_max_mcs_map_stru     st_tx_max_mcs_map;
    mac_rx_max_mcs_map_stru     st_rx_max_mcs_map;

    oal_uint16  bit_rx_highest_rate : 13,
                bit_resv2           : 3;
    oal_uint16  bit_tx_highest_rate : 13,
                bit_resv3           : 3;                                /* ����vht Capabilities IE: VHT Supported MCS Set field */

    oal_bool_enum_uint8 en_vht_capable;                                /* VHT capable */

    /* vht operationֻ����ap��������� */
    oal_uint8           uc_channel_width;                              /* ����VHT Operation IE */
                                                                       /* uc_channel_width��ȡֵ��0 -- 20/40M, 1 -- 80M, 2 -- 160M */
    oal_uint8           uc_channel_center_freq_seg0;
    oal_uint8           uc_channel_center_freq_seg1;
} mac_vht_hdl_stru;

/* user�ṹ�壬��SA Query������Ϣ�ı���ṹ */
typedef struct
{
    oal_uint32          ul_sa_query_count;                          /* number of pending SA Query requests, 0 = no SA Query in progress */
    oal_uint32          ul_sa_query_start_time;                     /* sa_query ���̿�ʼʱ��,��λms */
    oal_uint16          us_sa_query_trans_id;                       /* trans id */
    oal_uint8           auc_resv[2];
    frw_timeout_stru    st_sa_query_interval_timer;                 /* SA Query �����ʱ�������dot11AssociationSAQueryRetryTimeout */
}mac_sa_query_stru;

typedef struct
{
    oal_uint8               uc_qos_info;                                /* ���������е�WMM IE��QOS info field */
    oal_uint8               uc_max_sp_len;                              /* ��qos info�ֶ�����ȡ����������񳤶�*/
    oal_uint8               auc_resv[2];
    oal_uint8               uc_ac_trigger_ena[WLAN_WME_AC_BUTT];    /* 4��AC��trigger���� */
    oal_uint8               uc_ac_delievy_ena[WLAN_WME_AC_BUTT];    /* 4��AC��delivery���� */
}mac_user_uapsd_status_stru;

/* �û���AP�Ĺ���״̬ö�� */
typedef enum
{
    MAC_USER_STATE_AUTH_COMPLETE   = 1,
    MAC_USER_STATE_AUTH_KEY_SEQ1   = 2,
    MAC_USER_STATE_ASSOC           = 3,

    MAC_USER_STATE_BUTT            = 4
}hmac_user_asoc_state_enum;
typedef oal_uint8 mac_user_asoc_state_enum_uint8;

/* 802.1X-port ״̬�ṹ��*/
/* 1X�˿�״̬˵��:                                                  */
/* 1) portvalid && keydone ���� TRUE: ��ʾ�˿ڴ��ںϷ�״̬          */
/* 2) portvalid == TRUE && keydone == FALSE:��ʾ�˿ڴ���δ֪״̬    */
/*                                     ��Կ��δ��Ч                 */
/* 3) portValid == FALSE && keydone== TRUE:��ʾ�˿ڴ��ڷǷ�״̬     */
/*                                      ��Կ��ȡʧ��                */
/* 4) portValid && keyDone are FALSE: ��ʾ�˿ڴ��ںϷ�״̬          */
/*                                          ��Կ��δ��Ч            */

typedef struct
{
    oal_bool_enum_uint8             keydone;                      /*�˿ںϷ����Ƿ��������*/
    oal_bool_enum_uint8             portvalid;                    /*�˿ںϷ��Ա�ʶ*/
    oal_uint8                       auc_resv0[2];
}mac_8021x_port_status_stru;


/*��AP�鿴STA�Ƿ�ͳ�Ƶ���Ӧ��*/
typedef struct
{
    oal_uint8             bit_no_short_slot_stats_flag     :1;      /*ָʾuser�Ƿ�ͳ�Ƶ�no short slot num��, 0��ʾδ��ͳ�ƣ� 1��ʾ�ѱ�ͳ��*/
    oal_uint8             bit_no_short_preamble_stats_flag :1;      /*ָʾuser�Ƿ�ͳ�Ƶ�no short preamble num��*/
    oal_uint8             bit_no_erp_stats_flag            :1;      /*ָʾuser�Ƿ�ͳ�Ƶ�no erp num��*/
    oal_uint8             bit_no_ht_stats_flag             :1;      /*ָʾuser�Ƿ�ͳ�Ƶ�no ht num��*/
    oal_uint8             bit_no_gf_stats_flag             :1;      /*ָʾuser�Ƿ�ͳ�Ƶ�no gf num��*/
    oal_uint8             bit_20M_only_stats_flag          :1;      /*ָʾuser�Ƿ�ͳ�Ƶ�no 20M only num��*/
    oal_uint8             bit_no_40dsss_stats_flag         :1;      /*ָʾuser�Ƿ�ͳ�Ƶ�no 40dsss num��*/
    oal_uint8             bit_no_lsig_txop_stats_flag      :1;      /*ָʾuser�Ƿ�ͳ�Ƶ�no lsig txop num��*/

    oal_uint8             auc_resv0[3];
}mac_user_stats_flag_stru;

#ifdef _PRE_DEBUG_MODE_USER_TRACK
typedef struct
{
    oal_bool_enum_uint8     en_tx_flg;
    oal_bool_enum_uint8     en_rx_flg;
    oal_uint8               uc_tx_protocol;
    oal_uint8               uc_rx_protocol;
}mac_user_track_txrx_protocol_stru;

typedef struct
{
    frw_timeout_stru        st_txrx_param_timer;/* �ϱ���ʱ�� */
}mac_user_track_ctx_stru;
#endif
/* AP��keepalive��Ŀ��ƽṹ�� */
typedef struct
{
    oal_uint8             uc_keepalive_count_ap;                  /* AP��ʱ��������������� */
    oal_uint8             uc_timer_to_keepalive_count;            /* ����aging timer/STAʡ��ģʽ��ʱ���Ѳ��ԣ���ʱ����keepalive֡�ļ�����*/
    oal_uint8             uc_delay_flag;                          /* ��־�û�����˯��״̬������������������֡������״̬ */

    oal_uint8             auc_resv[1];
}mac_user_keepalive;
/*��Կ����ṹ��*/
typedef struct
{
    wlan_ciper_protocol_type_enum_uint8     en_cipher_type;
    oal_uint8                               uc_default_index;                       /* Ĭ������ */
    oal_uint8                               uc_igtk_key_index;                      /* igtk���� */
    oal_uint8                               bit_gtk       :1,                       /* ָʾRX GTK�Ĳ�λ��02ʹ�� */
                                            bit_rsv       :7;
    wlan_priv_key_param_stru                ast_key[WLAN_NUM_TK + WLAN_NUM_IGTK];   /* key���� */
    oal_uint8                               uc_last_gtk_key_idx;                      /* igtk���� */
    oal_uint8                               auc_reserved[1];
}mac_key_mgmt_stru;

/* �ռ�����Ϣ�ṹ�� */
typedef struct
{
    oal_uint16            us_user_idx;
    oal_uint8             uc_avail_num_spatial_stream;            /* Tx��Rx֧��Nss�Ľ���,���㷨���� */
	oal_uint8             uc_num_spatial_stream;                  /* �û�֧�ֵĿռ������� */

}mac_user_nss_stru;

/* opmode��Ϣ�ṹ�� */
typedef struct
{
    oal_uint16              us_user_idx;
    oal_uint8               uc_avail_num_spatial_stream;            /* Tx��Rx֧��Nss�Ľ���,���㷨���� */
    oal_uint8               uc_avail_bf_num_spatial_stream;         /* �û�֧�ֵ�Beamforming�ռ������� */
    oal_uint8               uc_frame_type;
    wlan_bw_cap_enum_uint8  en_avail_bandwidth;                     /* �û���VAP������������,���㷨���� */
    wlan_bw_cap_enum_uint8  en_cur_bandwidth;                       /* Ĭ��ֵ��en_avail_bandwidth��ͬ,���㷨�����޸� */

    oal_uint8             auc_resv[1];
}mac_user_opmode_stru;

typedef struct mac_key_params_tag
{
    oal_uint8 auc_key[OAL_WPA_KEY_LEN];
    oal_uint8 auc_seq[OAL_WPA_SEQ_LEN];
    oal_int32  key_len;
    oal_int32  seq_len;
    oal_uint32 cipher;
}mac_key_params_stru;
#ifdef _PRE_WLAN_FEATURE_WMMAC
/* user�ṹ�У�ts��Ϣ�ı����� */
typedef struct mac_ts
{
    oal_uint32                           ul_medium_time;
    oal_uint8                            uc_tsid;
    oal_uint8                            uc_up;
    mac_wmmac_direction_enum_uint8       en_direction;
    mac_ts_conn_status_enum_uint8        en_ts_status;
    oal_uint8                            uc_ts_dialog_token;
    oal_uint8                            uc_vap_id;
    oal_uint16                           us_mac_user_idx;
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
    /*ÿ��ts�¶���Ҫ������ʱ�����˴����ŵ�hmac_user_stru*/
    frw_timeout_stru                     st_addts_timer;
#endif
}mac_ts_stru;
#endif


/* mac user�ṹ��, hmac_user_stru��dmac_user_stru�������� */
typedef struct
{
    /* ��ǰVAP������AP��STAģʽ�������ֶ�Ϊuser��STA��APʱ�����ֶΣ�������ֶ���ע��!!! */
    oal_dlist_head_stru                     st_user_dlist;                          /* ����hash˫�����е�˫������ */
    oal_uint16                              us_user_hash_idx;                       /* ����ֵ(����) */
    oal_uint8                               auc_user_mac_addr[WLAN_MAC_ADDR_LEN];   /* user��Ӧ��MAC��ַ */
    oal_uint16                              us_assoc_id;                            /* user��Ӧ��Դ������ֵ; userΪSTAʱ����ʾ���ڹ���֡�е�AID��ֵΪ�û�����Դ������ֵ1~32(Э��涨��ΧΪ1~2007)*/
    oal_bool_enum_uint8                     en_is_multi_user;
    oal_uint8                               uc_vap_id;                              /* vap ID */
    oal_uint8                               uc_device_id;                           /* �豸ID */
    oal_uint8                               uc_chip_id;                             /* оƬID */
    wlan_protocol_enum_uint8                en_protocol_mode;                       /* �û�����Э�� */
    wlan_protocol_enum_uint8                en_avail_protocol_mode;                 /* �û���VAPЭ��ģʽ����, ���㷨���� */
    wlan_protocol_enum_uint8                en_cur_protocol_mode;                   /* Ĭ��ֵ��en_avail_protocol_modeֵ��ͬ, ���㷨�����޸� */

    oal_uint8                               uc_avail_num_spatial_stream;            /* Tx��Rx֧��Nss�Ľ���,���㷨���� */
	oal_uint8                               uc_num_spatial_stream;                  /* �û�֧�ֵĿռ������� */
	oal_uint8                               uc_avail_bf_num_spatial_stream;         /* �û�֧�ֵ�Beamforming�ռ������� */
    oal_bool_enum_uint8                     en_port_valid;                          /* 802.1X�˿ںϷ��Ա�ʶ */
    oal_uint8                               uc_is_user_alloced;                     /* ��־��user��Դ�Ƿ��Ѿ������� */

    mac_rate_stru                           st_avail_op_rates;                      /* �û���VAP���õ�11a/b/g���ʽ��������㷨���� */
    mac_user_tx_param_stru                  st_user_tx_info;                        /* TX��ز��� */
    wlan_bw_cap_enum_uint8                  en_bandwidth_cap;                       /* �û�����������Ϣ */
    wlan_bw_cap_enum_uint8                  en_avail_bandwidth;                     /* �û���VAP������������,���㷨���� */
    wlan_bw_cap_enum_uint8                  en_cur_bandwidth;                       /* Ĭ��ֵ��en_avail_bandwidth��ͬ,���㷨�����޸� */

    mac_user_asoc_state_enum_uint8          en_user_asoc_state;                     /* �û�����״̬ */
#ifdef _PRE_WLAN_FEATURE_WMMAC
    mac_ts_stru                             st_ts_info[WLAN_WME_AC_BUTT];           /*����ts�����Ϣ��*/
#endif
    mac_user_cap_info_stru                  st_cap_info;                            /* user����������Ϣλ */
    mac_user_ht_hdl_stru                    st_ht_hdl;                              /* HT capability IE�� operation IE�Ľ�����Ϣ */
    mac_vht_hdl_stru                        st_vht_hdl;                             /* VHT capability IE�� operation IE�Ľ�����Ϣ */

    mac_key_mgmt_stru                       st_key_info;

#ifdef _PRE_WLAN_FEATURE_HILINK
    oal_uint32                              ul_max_phy_rate_kbps;                   /* ���û��������������� */
#endif
    /* ��ǰVAP������APģʽ�������ֶ�Ϊuser��STAʱ�����ֶΣ�������ֶ���ע��!!! */

    /* ��ǰVAP������STAģʽ�������ֶ�Ϊuser��APʱ�����ֶΣ�������ֶ���ע��!!! */
}mac_user_stru;

#ifdef _PRE_WLAN_FEATURE_UAPSD

#define MAC_USR_UAPSD_EN     0x01//U-APSDʹ��
#define MAC_USR_UAPSD_TRIG   0x02//U-APSD���Ա�trigger
#define MAC_USR_UAPSD_SP     0x04//u-APSD��һ��Service Period������

/*AC��trigge_en�����û���ǰ����trigger״̬��can be trigger*/
#define MAC_USR_UAPSD_AC_CAN_TIGGER(_ac,_dmac_usr) \
    (((_dmac_usr)->st_uapsd_status.uc_ac_trigger_ena[_ac])&&((_dmac_usr)->uc_uapsd_flag & MAC_USR_UAPSD_TRIG))

/*AC��delivery_en�����û���ǰ����trigger״̬,can be delivery*/
#define MAC_USR_UAPSD_AC_CAN_DELIVERY(_ac,_dmac_usr) \
    (((_dmac_usr)->st_uapsd_status.uc_ac_delievy_ena[_ac])&&((_dmac_usr)->uc_uapsd_flag & MAC_USR_UAPSD_TRIG))

#define MAC_USR_UAPSD_USE_TIM(_dmac_usr) \
    (MAC_USR_UAPSD_AC_CAN_DELIVERY(WLAN_WME_AC_BK, _dmac_usr) && \
        MAC_USR_UAPSD_AC_CAN_DELIVERY(WLAN_WME_AC_BE, _dmac_usr) && \
        MAC_USR_UAPSD_AC_CAN_DELIVERY(WLAN_WME_AC_VI, _dmac_usr) && \
        MAC_USR_UAPSD_AC_CAN_DELIVERY(WLAN_WME_AC_VO, _dmac_usr))
#endif

#define MAC_11I_ASSERT(_cond, _errcode) do{\
if(!(_cond))\
{\
    return _errcode;\
}\
}while(0);

#define MAC_11I_IS_PTK(en_macaddr_is_zero, en_pairwise)   ((OAL_TRUE != en_macaddr_is_zero) && (OAL_TRUE == en_pairwise))


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : mac_user_get_ra_lut_index
 ��������  : ��ȡ�û���Ӧ��ra lut index
 �������  : puc_index_table: ���ұ�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  mac_user_get_ra_lut_index(oal_uint8 *puc_index_table, oal_uint16 us_start, oal_uint16 us_stop)
{
    return oal_get_lut_index(puc_index_table,
                             WLAN_ACTIVE_USER_IDX_BMAP_LEN,
                             WLAN_ACTIVE_USER_MAX_NUM, us_start, us_stop);
}
/*****************************************************************************
 �� �� ��  : mac_user_del_ra_lut_index
 ��������  : ɾ���û���Ӧ��ra lut index
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  mac_user_del_ra_lut_index(oal_uint8 *puc_index_table, oal_uint8 uc_ra_lut_index)
{
    oal_del_lut_index(puc_index_table, uc_ra_lut_index);
}


/*****************************************************************************
  10 ��������
*****************************************************************************/

oal_uint32 mac_user_add_wep_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key);
oal_uint32 mac_user_add_rsn_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key);
oal_uint32 mac_user_add_bip_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_index, mac_key_params_stru *pst_key);

extern wlan_priv_key_param_stru *mac_user_get_key(mac_user_stru *pst_mac_user, oal_uint8 uc_key_id);

extern oal_uint32  mac_user_init(
                mac_user_stru  *pst_mac_user,
                oal_uint16      us_user_idx,
                oal_uint8      *puc_mac_addr,
                oal_uint8       uc_chip_id,
                oal_uint8       uc_device_id,
                oal_uint8       uc_vap_id);

extern oal_uint32 mac_user_set_port(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_port_valid);

extern oal_void mac_user_avail_bf_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value);
extern oal_void mac_user_set_avail_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value);
extern oal_void mac_user_set_num_spatial_stream(mac_user_stru *pst_mac_user, oal_uint8 uc_value);
extern oal_void mac_user_set_bandwidth_cap(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 en_bandwidth_value);
extern oal_void mac_user_set_bandwidth_info(mac_user_stru *pst_mac_user,
                                                    wlan_bw_cap_enum_uint8 en_avail_bandwidth,
                                                    wlan_bw_cap_enum_uint8 en_cur_bandwidth);
extern oal_void  mac_user_get_sta_cap_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 *pen_bandwidth_cap);
extern oal_void  mac_user_get_ap_opern_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 *pen_bandwidth_cap);
extern oal_uint32  mac_user_update_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8 en_bwcap);

#ifdef _PRE_DEBUG_MODE_USER_TRACK
extern oal_uint32  mac_user_change_info_event(
                                    oal_uint8  auc_user_macaddr[],
                                    oal_uint8  uc_vap_id,
                                    oal_uint32 ul_val_old,
                                    oal_uint32 ul_val_new,
                                    oam_module_id_enum_uint16 en_mod,
                                    oam_user_info_change_type_enum_uint8 en_type);
#endif
extern oal_void mac_user_set_assoc_id(mac_user_stru *pst_mac_user, oal_uint16 us_assoc_id);
extern oal_void mac_user_set_avail_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_avail_protocol_mode);
extern oal_void mac_user_set_cur_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_cur_protocol_mode);
extern oal_void mac_user_set_cur_bandwidth(mac_user_stru *pst_mac_user, wlan_bw_cap_enum_uint8  en_cur_bandwidth);
extern oal_void mac_user_set_protocol_mode(mac_user_stru *pst_mac_user, wlan_protocol_enum_uint8 en_protocol_mode);
extern oal_void mac_user_set_asoc_state(mac_user_stru *pst_mac_user, mac_user_asoc_state_enum_uint8 en_value);
extern oal_void mac_user_set_avail_op_rates(mac_user_stru *pst_mac_user, oal_uint8 uc_rs_nrates, oal_uint8 *puc_rs_rates);
extern oal_void mac_user_set_vht_hdl(mac_user_stru *pst_mac_user, mac_vht_hdl_stru *pst_vht_hdl);
extern oal_void mac_user_get_vht_hdl(mac_user_stru *pst_mac_user, mac_vht_hdl_stru *pst_ht_hdl);
extern oal_void mac_user_set_ht_hdl(mac_user_stru *pst_mac_user, mac_user_ht_hdl_stru *pst_ht_hdl);
extern oal_void mac_user_get_ht_hdl(mac_user_stru *pst_mac_user, mac_user_ht_hdl_stru *pst_ht_hdl);
extern oal_void mac_user_set_ht_capable(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_ht_capable);
#ifdef _PRE_WLAN_FEATURE_SMPS
extern oal_void mac_user_set_sm_power_save(mac_user_stru *pst_mac_user, oal_uint8 uc_sm_power_save);
#endif
extern oal_void mac_user_set_pmf_active(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_pmf_active);
extern oal_void mac_user_set_barker_preamble_mode(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_barker_preamble_mode);
extern oal_void mac_user_set_qos(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_qos_mode);
extern oal_void mac_user_set_spectrum_mgmt(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_spectrum_mgmt);
extern oal_void  mac_user_set_apsd(mac_user_stru *pst_mac_user, oal_bool_enum_uint8 en_apsd);

extern oal_uint32 mac_user_init_key(mac_user_stru *pst_mac_user);

extern oal_uint32 mac_user_set_key(mac_user_stru *pst_multiuser,
                                            wlan_cipher_key_type_enum_uint8 en_keytype,
                                            wlan_ciper_protocol_type_enum_uint8 en_ciphertype,
                                            oal_uint8       uc_keyid);

extern oal_uint32 mac_user_update_wep_key(mac_user_stru *pst_mac_usr, oal_uint16 us_multi_user_idx);
extern oal_bool_enum_uint8 mac_addr_is_zero(oal_uint8 *puc_mac);
extern oal_void*  mac_res_get_mac_user(oal_uint16 us_idx);



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of mac_user.h */
