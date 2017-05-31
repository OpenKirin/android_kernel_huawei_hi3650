/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_mgmt_sta.h
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2013��6��18��
  ����޸�   :
  ��������   : hmac_mgmt_sta.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��18��
    ��    ��   : zhangheng
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __HMAC_MGMT_STA_H__
#define __HMAC_MGMT_STA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "hmac_vap.h"
#include "hmac_mgmt_bss_comm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_MGMT_STA_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define HMAC_WMM_QOS_PARAMS_HDR_LEN        8
#define HMAC_WMM_QOSINFO_AND_RESV_LEN      2
#define HMAC_WMM_AC_PARAMS_RECORD_LEN      4
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

/* ����������� */
typedef struct
{
    mac_bss_dscr_stru   st_bss_dscr;            /* Ҫ�����bss���� */
    oal_uint16          us_join_timeout;        /* ���볬ʱ */
    oal_uint16          us_probe_delay;
}hmac_join_req_stru;

/* ��֤������� */
typedef struct
{
    oal_uint16                  us_timeout;
    oal_uint8                   auc_resv[2];
}hmac_auth_req_stru;

/* ����������� */
typedef struct
{
    oal_uint16                  us_assoc_timeout;
    oal_uint8                   auc_resv[2];
}hmac_asoc_req_stru;

/* ������ */
typedef struct
{
    hmac_mgmt_status_enum_uint8 en_result_code;
    oal_uint8                   auc_resv[3];
}hmac_join_rsp_stru;

/* ��֤��� */
typedef struct
{
    oal_uint8                   auc_peer_sta_addr[6];   /* mesh��peer station�ĵ�ַ */
    oal_uint16                  us_status_code;         /* ��֤��� */
}hmac_auth_rsp_stru;

/* ȥ����ԭ�� */
typedef struct
{
    hmac_mgmt_status_enum_uint8  en_disasoc_reason_code;
    oal_uint8                    auc_resv[3];
}hmac_disasoc_rsp_stru;

typedef struct
{
    hmac_mgmt_status_enum_uint8  en_result_code;
    oal_uint8                    auc_resv[3];
}hmac_ap_start_rsp_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  hmac_sta_wait_join(hmac_vap_stru *pst_sta, oal_void *pst_msg);
//extern oal_uint32  hmac_sta_wait_join_rx(hmac_vap_stru *pst_sta, oal_void *pst_msg);
extern oal_uint32  hmac_sta_wait_auth(hmac_vap_stru *pst_sta, oal_void *pst_msg);
extern oal_uint32  hmac_sta_wait_asoc(hmac_vap_stru *pst_sta, oal_void *pst_msg);
extern oal_uint32  hmac_sta_wait_asoc_rx(hmac_vap_stru *pst_sta, oal_void *pst_msg);
extern oal_uint32  hmac_sta_wait_auth_seq2_rx(hmac_vap_stru *pst_sta, oal_void *pst_msg);
extern oal_uint32  hmac_sta_wait_auth_seq4_rx(hmac_vap_stru *pst_sta, oal_void *p_msg);
extern oal_uint32  hmac_sta_auth_timeout(hmac_vap_stru *pst_hmac_sta, oal_void *p_param);
//extern oal_uint32  hmac_sta_wait_join_misc(hmac_vap_stru *pst_sta, oal_void *pst_msg);
//extern oal_uint32  hmac_sta_wait_join_timeout(hmac_vap_stru *pst_sta, oal_void *pst_msg);
extern oal_uint32  hmac_sta_up_rx_mgmt(hmac_vap_stru *pst_hmac_vap_sta, oal_void *p_param);
extern oal_uint32  hmac_sta_wait_asoc_timeout(hmac_vap_stru *pst_hmac_sta, oal_void *p_param);
extern oal_void    hmac_sta_handle_disassoc_rsp(hmac_vap_stru *pst_hmac_vap, oal_uint16 us_disasoc_reason_code);
/* TBD : create new hmac_p2p.c */
extern oal_uint32  hmac_p2p_remain_on_channel(hmac_vap_stru *pst_hmac_vap_sta, oal_void *p_param);
extern oal_uint32  hmac_p2p_listen_timeout(hmac_vap_stru *pst_hmac_vap_sta, oal_void *p_param);

#if defined(_PRE_WLAN_FEATURE_HS20) || defined(_PRE_WLAN_FEATURE_P2P) || defined(_PRE_WLAN_FEATURE_HILINK)
extern oal_uint32  hmac_sta_not_up_rx_mgmt(hmac_vap_stru *pst_hmac_vap_sta, oal_void *p_param);
#endif

extern wlan_channel_bandwidth_enum_uint8 hmac_sta_get_band(wlan_bw_cap_enum_uint8 en_dev_cap, wlan_channel_bandwidth_enum_uint8 en_bss_cap);
extern oal_uint32 hmac_sta_get_user_protocol(mac_bss_dscr_stru *pst_bss_dscr, wlan_protocol_enum_uint8  *pen_protocol_mode);
oal_void hmac_sta_update_wmm_info(hmac_vap_stru *pst_hmac_vap, mac_user_stru *pst_mac_user, oal_uint8 *puc_wmm_ie);
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
oal_void  hmac_update_join_req_params_2040(mac_vap_stru *pst_mac_vap, mac_bss_dscr_stru *pst_bss_dscr);
#endif
extern oal_uint32  hmac_sta_up_update_edca_params_machw(hmac_vap_stru  *pst_hmac_sta, mac_wmm_set_param_type_enum_uint8 en_wmm_set_param_type);
extern oal_uint32  hmac_sta_set_txopps_partial_aid(mac_vap_stru *pst_mac_vap);
extern oal_void hmac_sta_up_update_edca_params(
                    oal_uint8               *puc_payload,
                    oal_uint16               us_msg_len,
                    oal_uint16               us_info_elem_offset,
                    hmac_vap_stru           *pst_hmac_sta,
                    oal_uint8                uc_frame_sub_type,
                    hmac_user_stru          *pst_hmac_user);
extern oal_bool_enum_uint8  hmac_is_support_11grate(oal_uint8 *puc_rates, oal_uint8 uc_rate_num);
extern oal_bool_enum_uint8  hmac_is_support_11brate(oal_uint8 *puc_rates, oal_uint8 uc_rate_num);
extern oal_uint32 hmac_process_assoc_rsp(hmac_vap_stru *pst_hmac_sta, hmac_user_stru *pst_hmac_user, oal_uint8 *puc_mac_hdr, oal_uint8 *puc_payload, oal_uint16 us_msg_len);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_mgmt_sta.h */
