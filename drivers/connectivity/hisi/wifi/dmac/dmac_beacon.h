/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_beacon.h
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2013��3��29��
  ����޸�   :
  ��������   : dmac_beacon.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��3��29��
    ��    ��   : zhangheng
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_BEACON_H__
#define __DMAC_BEACON_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oam_ext_if.h"
#include "dmac_vap.h"
#include "mac_resource.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_BEACON_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define DMAC_WMM_QOS_PARAMS_HDR_LEN 8
#define DMAC_MAX_WAIT_BEACON_TIMES      5

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
/* beacon֡��Ҫ���µ���ϢԪ��ƫ���� */
typedef struct
{
    oal_uint16   us_cap_offset;
    oal_uint16   us_bss_load_offset;
    oal_uint16   us_wmm_offset;
    oal_uint16   us_ht_cap_offset;
    oal_uint16   us_ht_operation_offset;
    oal_uint16   us_erp_offset;
    oal_uint16   us_pwr_constrain_offset;
    oal_uint16   us_tpc_report_offset;
    oal_uint16   us_tim_offset;
    oal_uint8    uc_wmm_update_flag;
    oal_uint8    auc_resv[1];
}dmac_beacon_ie_offset_stru;

/* ������beacon���� */
typedef struct
{
    oal_uint8 uc_test_type;
    oal_uint8 uc_test_flag;
    oal_uint8 uc_host_sleep;
    oal_uint8 uc_opmode_in_beacon;
    oal_uint8 uc_opmode;
    oal_uint8 uc_csa_in_beacon;
    oal_uint8 uc_announced_channel;
    oal_uint8 uc_switch_cnt;
}dmac_beacon_test_stru;

/* wlanԶ������/p2p linkloss���� */
typedef struct
{
    oal_uint16  us_linkloss_threshold_wlan_near;
    oal_uint16  us_linkloss_threshold_wlan_far;
    oal_uint16  us_linkloss_threshold_p2p;
    oal_uint8   auc_resv[2];
}dmac_beacon_linkloss_stru;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  dmac_beacon_alloc(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32  dmac_beacon_free(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32  dmac_tbtt_event_handler(frw_event_mem_stru *pst_event_mem);
extern oal_void dmac_set_tim_ie(oal_void *pst_vap, oal_uint8 *puc_buffer, oal_uint8 *puc_ie_len);
#ifdef _PRE_WLAN_FEATURE_P2P
extern oal_uint32  dmac_beacon_set_p2p_noa(
                mac_vap_stru           *pst_mac_vap,
                oal_uint32              ul_start_tsf,
                oal_uint32              ul_duration,
                oal_uint32              ul_interval,
                oal_uint8               uc_count);
#endif
extern oal_uint32  dmac_sta_up_rx_beacon(
                dmac_vap_stru   *pst_dmac_vap,
                oal_netbuf_stru *pst_netbuf,
                oal_uint8       *pen_go_on);
extern oal_uint32  dmac_encap_beacon(
                dmac_vap_stru               *pst_dmac_vap,
                oal_uint8                   *puc_beacon_buf,
                oal_uint16                  *pus_beacon_len);

extern oal_void dmac_get_tsf_from_bcn(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);
extern oal_bool_enum_uint8 dmac_sta_host_is_sleep(void);
#ifdef _PRE_WLAN_FEATURE_ROAM
extern oal_uint32 dmac_sta_roam_trigger_init(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32 dmac_sta_roam_trigger_check(dmac_vap_stru *pst_dmac_vap);
#endif //_PRE_WLAN_FEATURE_ROAM
extern void dmac_sta_beacon_offload_test(mac_vap_stru *pst_mac_vap, oal_uint8 *uc_host_sleep);
extern oal_uint32  dmac_beacon_timeout_event_hander(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_send_disasoc_misc_event(mac_vap_stru *pst_mac_vap, oal_uint16 us_user_idx, oal_uint16 us_disasoc_reason);
extern oal_void dmac_sta_set_protection_mode(dmac_vap_stru *pst_dmac_vap,wlan_prot_mode_enum_uint8 en_protection_mode);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_beacon.h */
