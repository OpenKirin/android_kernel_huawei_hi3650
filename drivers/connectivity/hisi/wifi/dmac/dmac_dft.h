/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_dft.h
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2014��8��13��
  ����޸�   :
  ��������   : dmac_dft.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��8��13��
    ��    ��   : z00237171
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_DFT_H__
#define __DMAC_DFT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "mac_user.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "dmac_user.h"
#include "dmac_vap.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DFT_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
#define  DMAC_DFT_PHY_STAT_NODE_0_BASE           0   /* phyͳ�ƽڵ�0�Ļ�׼bit���Ĵ���PHY_STA_01_EN��bit0 */
#define  DMAC_DFT_PHY_STAT_NODE_1_BASE           16  /* phyͳ�ƽڵ�1�Ļ�׼bit���Ĵ���PHY_STA_01_EN��bit16 */
#define  DMAC_DFT_PHY_STAT_NODE_2_BASE           0   /* phyͳ�ƽڵ�2�Ļ�׼bit���Ĵ���PHY_STA_23_EN��bit0 */
#define  DMAC_DFT_PHY_STAT_NODE_3_BASE           16  /* phyͳ�ƽڵ�3�Ļ�׼bit���Ĵ���PHY_STA_23_EN��bit16 */
#define  DMAC_DFT_REPORT_TO_COLLECT_TIMES        100 /* �տڻ���������ϱ�����(2s)��ɼ�����(20ms)�ı�ֵ */
#define  DMAC_DFT_COLLECT_DBB_ENV_PARAM_TIMEOUT  20  /* �տڻ���������ɼ����ڣ�20ms */
#define  DMAC_DFT_REPORT_VAP_STAT_TIMEOUT        2000/* �ϱ�vap�������ͳ����Ϣ���� */
#define  DMAC_DFT_PHY_INTLAN_GAIN_NUM            8   /* ����LNA������Ŀ */
#define  DMAC_DFT_PHY_VGA_GAIN_NUM               32  /* VGA������Ŀ */
#define  DMAC_DFT_VAP_STAT_RATE_TO_KBPS          250 /* ���ʵ�λ��kbps��Ӧ�����ֽ�����������(2s)�ٳ���1000�ڳ���8(B/b) */
#define  DMAC_DFT_MAC_CHAN_STAT_PERIOD           20000 /* MAC�����ŵ�����ʱ��ͳ�����ڣ�20000us(20ms) */
#define  DMAC_DFT_PHY_CHAN_MEASUREMENT_PERIOD    10  /* PHY�����ŵ����й��ʲ��������ڣ�10ms */

#define  DMAC_DFT_MGMT_STAT_INCR(_member)     ((_member)++)
#define  DMAC_DFT_AP_BEACON_MISS_MAX_NUM(_idx, _val, _pul_val)  do {   \
         *_pul_val = ((0xFF << ((_idx) << 3)) & (_val)) >> ((_idx) << 3);  \
         }while(0)

#define  DMAC_DFT_REG_OTA_LEN              1024 /* �Ĵ���OTA�ϱ���������� */
#endif



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


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/* OTA�ϱ�����Ϣ�ṹ�嶨��(�����ڴ�أ�vap��user�����еȵ�)�����ṹ��ͳһ�����ڴ˴���Ŀ���Ǳ���ά�� */

/*****************************************************************************
  �ṹ��  : mem_subpool_dft_stru
  �ṹ˵��: ota�ϱ������ڴ�ؽṹ��
*****************************************************************************/
typedef struct
{
    oal_uint8             uc_sub_pool_id;     /* ���ڴ�ص�id */
    oal_uint8             auc_resv[3];
    oal_uint16            us_free_cnt;        /* �����ڴ�ؿ����ڴ���� */
    oal_uint16            us_total_cnt;       /* �����ڴ���ڴ������ */
} mem_subpool_dft_stru;

/* OTA�ϱ����ڴ��ʹ������Ľṹ�壬�˽ṹ����޸���Ҫ֪ͨSDT�����Ա����ͬ���޸ģ������������� */
typedef struct
{
    oal_uint8                  uc_pool_id;             /* ���ڴ�ص�pool id */
    oal_uint8                  uc_subpool_cnt;         /* ���ڴ��һ���ж������ڴ�� */
    oal_uint16                 us_max_byte_len;        /* ���ڴ�ؿɷ����ڴ����󳤶� */
    oal_uint16                 us_mem_used_cnt;        /* ���ڴ�������ڴ�� */
    oal_uint16                 us_mem_total_cnt;       /* ���ڴ��һ���ж����ڴ�� */

    /* ���ڴ�ص���Ϣ */
    mem_subpool_dft_stru       ast_subpool_table[WLAN_MEM_MAX_SUBPOOL_NUM];
}mem_pool_dft_stru;

/* OTA�ϱ���Ӳ����Ϣ�ṹ�壬�˽ṹ����޸���Ҫ֪ͨSDT�����Ա����ͬ���޸ģ������������� */
typedef struct
{
    oal_uint8                       uc_chip_id;
    oal_uint8                       uc_device_id;
    oal_uint8                       uc_mac_device_id;                           /* ����mac device id */
    hal_lpm_state_enum_uint8        uc_curr_state;                              /*��ǰоƬ�ĵ͹���״̬*/
    oal_uint32                      ul_core_id;

    hal_rx_dscr_queue_header_stru   ast_rx_dscr_queue[HAL_RX_QUEUE_NUM];
    hal_tx_dscr_queue_header_stru   ast_tx_dscr_queue[HAL_TX_QUEUE_NUM];

    hal_tx_dscr_queue_header_stru   ast_tx_dscr_queue_fake[HAL_TX_FAKE_QUEUE_NUM][HAL_TX_QUEUE_NUM];
} hal_device_dft_stru;

/* OTA�ϱ����û����еĽṹ�壬�˽ṹ����޸���Ҫ֪ͨSDT�����Ա����ͬ���޸ģ������������� */
typedef struct
{
    dmac_tid_stru                      ast_tx_tid_queue[WLAN_TID_MAX_NUM]; /* ����tid������� */

#ifdef _PRE_WLAN_FEATURE_UAPSD
    dmac_user_uapsd_stru               st_uapsd_stru;                      /* �û���U-APSD���ܽṹ*/
#endif
}dmac_user_queue_info_dft_stru;

/* OTA�ϱ���dmac vap�ṹ�壬�˽ṹ����޸���Ҫ֪ͨSDT�����Ա����ͬ���޸ģ������������� */
typedef struct
{
    /* ����Ԫ�ض�Ӧ��mac_vap_stru�ṹ��Ԫ�� */
    oal_uint8                        uc_vap_id;                                      /* vap ID   *//* ����Դ������ֵ */
    oal_uint8                        uc_device_id;                                   /* �豸ID   */
    oal_uint8                        uc_chip_id;                                     /* chip ID  */
    wlan_vap_mode_enum_uint8         en_vap_mode;                                    /* vapģʽ  */
    oal_uint32                       ul_core_id;
    oal_uint8                        auc_bssid[WLAN_MAC_ADDR_LEN];                   /* BSSID����MAC��ַ��MAC��ַ��mib�е�auc_dot11StationID  */
    mac_vap_state_enum_uint8         en_vap_state;                                   /* VAP״̬ */
    wlan_protocol_enum_uint8         en_protocol;                                    /* ������Э��ģʽ */
    mac_channel_stru                 st_channel;                                     /* vap���ڵ��ŵ� */
    oal_uint8                        bit_has_user_bw_limit   :   1;                  /* ��vap�Ƿ����user���� */
    oal_uint8                        bit_vap_bw_limit        :   1;                  /* ��vap�Ƿ������� */
    oal_uint8                        bit_resv                :   6;
    oal_uint8                        uc_tx_power;                                    /* ���书��, ��λdBm */
    wlan_p2p_mode_enum_uint8         en_p2p_mode;                                    /* 0:��P2P�豸; 1:P2P_GO; 2:P2P_Device; 3:P2P_CL */
    oal_uint8                        uc_p2p_gocl_hal_vap_id;                         /* p2p go / cl��hal vap id */
    oal_uint16                       us_user_nums;                                   /* VAP���ѹҽӵ��û����� */
    oal_uint16                       us_multi_user_idx;                              /* �鲥�û�ID */
    mac_cap_flag_stru                st_cap_flag;
    mac_protection_stru              st_protection;                                  /* �뱣����ر��� */

    /* ����Ԫ�ض�Ӧ��dmac_vap_stru�ṹ��Ԫ�� */
    dmac_vap_linkloss_stru           st_linkloss_info;                                  /* linkloss���������Ϣ */
    hal_tx_txop_alg_stru             st_tx_alg;                                         /* ��������֡���Ͳ��� */
    hal_tx_txop_alg_stru             st_tx_data_mcast;                                  /* �鲥����֡���� */
    hal_tx_txop_alg_stru             st_tx_data_bcast;                                  /* �㲥����֡����*/
    hal_tx_txop_alg_stru             ast_tx_mgmt_ucast[WLAN_BAND_BUTT];                 /* ��������֡����*/
    hal_tx_txop_alg_stru             ast_tx_mgmt_bmcast[WLAN_BAND_BUTT];                /* �鲥���㲥����֡����*/

    oal_uint8                        uc_ps_user_num;                                    /* ���ڽ���ģʽ���û�����Ŀ��APģʽ��Ч */
    oal_uint8                        uc_dtim_count;
    oal_uint8                        uc_uapsd_max_depth;                                /* U-APSD���ܶ��е�������*/
    oal_uint8                        uc_resv;
}dmac_vap_dft_stru;

/* OTA�ϱ���dmac user�ṹ�壬�˽ṹ����޸���Ҫ֪ͨSDT�����Ա����ͬ���޸ģ������������� */
typedef struct
{
    /* ����Ԫ�ض�Ӧ��mac_user_stru�ṹ��Ԫ�� */
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

    mac_rate_stru                           st_avail_op_rates;                      /* �û���VAP���õ�11a/b/g���ʽ��������㷨���� */
    mac_user_tx_param_stru                  st_user_tx_info;                        /* TX��ز��� */

    wlan_bw_cap_enum_uint8                  en_bandwidth_cap;                       /* �û�����������Ϣ */
    wlan_bw_cap_enum_uint8                  en_avail_bandwidth;                     /* �û���VAP������������,���㷨���� */
    wlan_bw_cap_enum_uint8                  en_cur_bandwidth;                       /* Ĭ��ֵ��en_avail_bandwidth��ͬ,���㷨�����޸� */
    mac_user_asoc_state_enum_uint8          en_user_asoc_state;                     /* �û�����״̬ */

    mac_user_cap_info_stru                  st_cap_info;                            /* user����������Ϣλ */
    mac_user_ht_hdl_stru                    st_ht_hdl;                              /* HT capability IE�� operation IE�Ľ�����Ϣ */
    mac_vht_hdl_stru                        st_vht_hdl;                             /* VHT capability IE�� operation IE�Ľ�����Ϣ */

    mac_key_mgmt_stru                       st_key_info;

    /* ����Ԫ�ض�Ӧ��dmac_user_stru�ṹ��Ԫ�� */
    hal_tx_txop_alg_stru                    st_tx_data_mcast;                   /* �鲥����֡������Ԥ��11kʹ�� */
    hal_tx_txop_alg_stru                    st_tx_data_bcast;                   /* �㲥����֡����, Ԥ��11kʹ�� */

    mac_user_uapsd_status_stru              st_uapsd_status;                    /* uapsd״̬ */
    oal_uint8                               uc_lut_index;                       /* user��Ӧ��Ӳ����������Ծ�û�id */
    oal_uint8                               uc_uapsd_flag;                      /* STA��U-APSD��ǰ�Ĵ���״̬ */
    oal_uint8                               uc_max_key_index;                   /* ���ptk index */
    oal_uint8                               uc_resv;

    dmac_user_rate_info_stru                st_user_rate_info;
}dmac_user_dft_stru;

#endif

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_void dmac_dft_report_dmac_vap_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_dmac_user_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_dmac_event_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_dmac_memory_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_mac_hardware_info(mac_vap_stru  *pst_mac_vap);
extern oal_void dmac_dft_report_dmac_queue_info(mac_vap_stru  *pst_mac_vap);

#endif

extern oal_uint32  dmac_dft_set_phy_stat_node(
                                    mac_device_stru *pst_device,
                                    oam_stats_phy_node_idx_stru *pst_phy_node_idx);
extern oal_uint32  dmac_dft_start_report_dbb_env(mac_vap_stru *pst_mac_vap);
extern oal_uint32  dmac_dft_stop_report_dbb_env(mac_vap_stru *pst_mac_vap);

extern oal_uint32  dmac_dft_start_report_vap_stat(mac_vap_stru *pst_mac_vap);
extern oal_uint32  dmac_dft_stop_report_vap_stat(mac_vap_stru *pst_mac_vap);
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_uint32  dmac_dft_clear_usr_queue_stat(dmac_user_stru  *pst_dmac_user);
extern oal_uint32  dmac_dft_report_usr_queue_stat(dmac_user_stru  *pst_dmac_user);
#endif
extern oal_void  dmac_dft_calcu_antenna_power(mac_device_stru *pst_macdev);
extern oal_uint32  dmac_dft_mgmt_stat_incr(
                                    mac_device_stru   *pst_mac_dev,
                                    oal_uint8   *puc_mac_hdr_addr,
                                    mac_dev_mgmt_stat_type_enum_uint8 en_type);
extern oal_uint32  dmac_dft_get_machw_stat_info(
                                    hal_to_dmac_device_stru   *pst_dev,
                                    oam_stats_machw_stat_stru *pst_machw_stat);
#ifdef _PRE_WLAN_FEATURE_STA_PM
extern oal_void dmac_mac_key_statis_info(dmac_vap_stru *pst_dmac_vap, mac_device_stru  *pst_device);
#endif
extern oal_void dmac_dft_report_all_para(dmac_vap_stru *pst_dmac_sta,oal_uint8 uc_ota_switch);
extern oal_void dmac_dft_print_mac_phy_rf(mac_device_stru *pst_mac_dev);

extern oal_void  dmac_dft_report_all_ota_state(mac_vap_stru *pst_mac_sta);

#endif

#ifdef _PRE_DEBUG_MODE

extern oal_uint32  dmac_dft_report_all_ampdu_stat(dmac_user_stru  *pst_dmac_user,
                                                   oal_uint8        uc_param);



extern oal_uint32  dmac_dft_report_ampdu_stat(dmac_tid_stru  *pst_tid,
                                                      oal_uint8      auc_macaddr[],
                                                      oal_uint8       uc_param);
#endif










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_dft.h */
