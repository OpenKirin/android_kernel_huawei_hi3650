/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_psm_ap.h
  �� �� ��   : ����
  ��    ��   : k53369
  ��������   : 2012��11��21��
  ����޸�   :
  ��������   : dmac_psm_ap.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��21��
    ��    ��   : k53369
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_PSM_AP_H__
#define __DMAC_PSM_AP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_vap.h"
#include "dmac_vap.h"
#include "dmac_user.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MAX_MPDU_NUM_IN_PS_QUEUE    128

#define DMAC_PSM_CHANGE_USER_PS_STATE(_bit_ps, _en_val)  ((_bit_ps) = (_en_val))

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
extern oal_uint32  dmac_psm_resv_ps_poll(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user);
extern oal_void dmac_psm_set_local_bitmap(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_uint8 uc_bitmap_flg);
#if 0
extern oal_uint8 dmac_psm_get_local_bitmap(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user);
extern oal_uint8 dmac_psm_get_bitmap_offset(dmac_vap_stru *pst_dmac_vap);
extern oal_uint8 dmac_psm_get_bitmap_len(dmac_vap_stru *pst_dmac_vap);
#endif
extern oal_uint32 dmac_psm_send_null_data(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_bool_enum_uint8 en_ps);
extern oal_uint32 dmac_psm_user_ps_structure_init(dmac_user_stru *pst_dmac_user);
extern oal_uint32  dmac_psm_user_ps_structure_destroy(dmac_user_stru *pst_dmac_user);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_void dmac_psm_delete_ps_queue_head(dmac_user_stru *pst_dmac_user,oal_uint32 ul_psm_delete_num);
#endif
extern oal_void dmac_psm_clear_ps_queue(dmac_user_stru *pst_dmac_user);
extern oal_void dmac_psm_queue_flush(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user);
extern oal_uint32 dmac_psm_enqueue(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf);
extern oal_uint32  dmac_psm_flush_txq_to_tid(mac_device_stru *pst_mac_device,dmac_vap_stru  *pst_dmac_vap,dmac_user_stru *pst_dmac_user);
extern oal_uint8 dmac_psm_pkt_need_buff(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf);
extern oal_void dmac_psm_rx_process(dmac_vap_stru *pst_dmac_vap, dmac_user_stru *pst_dmac_user, oal_netbuf_stru *pst_net_buf);
extern oal_uint32  dmac_psm_reset(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_psm_tx_set_more_data(dmac_user_stru *pst_dmac_user,
                                               mac_tx_ctl_stru *pst_tx_cb);
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_uint32  dmac_psm_enable_user_to_psm_back(dmac_vap_stru *pst_dmac_vap, mac_device_stru *pst_mac_device, dmac_user_stru *pst_dmac_user);
oal_uint32  dmac_psm_disable_user_to_psm_back(mac_device_stru *pst_mac_device,dmac_user_stru *pst_dmac_user);
//oal_uint32  dmac_psm_flush_txq_to_psm(dmac_vap_stru  *pst_dmac_vap, dmac_user_stru *pst_dmac_user);
#endif
#endif
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
extern oal_uint32 dmac_psm_opmode_notify_process(frw_event_mem_stru *pst_event_mem);
#endif

extern oal_void  dmac_change_null_data_rate(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,oal_uint8 *uc_protocol_mode,oal_uint8 *uc_legacy_rate);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_psm_ap.h */
