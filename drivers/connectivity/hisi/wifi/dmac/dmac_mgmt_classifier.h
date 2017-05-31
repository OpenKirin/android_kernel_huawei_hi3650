/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_mgmt_classifier.h
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2012��12��18��
  ����޸�   :
  ��������   : dmac_mgmt_classifier.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��18��
    ��    ��   : t00231215
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_MGMT_CLASSIFIER_H__
#define __DMAC_MGMT_CLASSIFIER_H__

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
#include "hal_ext_if.h"
#include "dmac_user.h"

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#include "pm_extern.h"
#endif



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_CLASSIFIER_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)

#define DMAC_DEFAULT_STA_BEACON_WAIT_TIME     PM_DEFAULT_STA_BEACON_WAIT_TIME    //��λms
#define DMAC_DEFAULT_STA_INTER_TBTT_OFFSET    PM_DEFAULT_STA_INTER_TBTT_OFFSET  //��λus
#define DMAC_DEFAULT_EXT_TBTT_OFFSET          PM_DEFAULT_EXT_TBTT_OFFSET   //��λΪms

#define DMAC_BEACON_TIMEOUT_FIX_OFFSET        PM_BEACON_TIMEOUT_FIX_OFFSET
#else
#define DMAC_DEFAULT_STA_BEACON_WAIT_TIME     5    //��λms
#define DMAC_DEFAULT_STA_INTER_TBTT_OFFSET    500  //��λus
#define DMAC_DEFAULT_EXT_TBTT_OFFSET          6   //��λΪms

#define DMAC_BEACON_TIMEOUT_FIX_OFFSET        300

#endif
#define DMAC_DEFAULT_STA_BCN_TOUT_MAX_CNT     5

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
extern oal_uint32  dmac_rx_mgmt_classify(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                mac_vap_stru                   *pst_vap,
                oal_netbuf_stru                *pst_netbuf);
extern oal_uint32  dmac_rx_process_mgmt(
                frw_event_mem_stru             *pst_event_mem,
                frw_event_hdr_stru             *pst_event_hdr,
                hal_to_dmac_device_stru        *pst_hal_device,
                oal_netbuf_stru                *pst_netbuf);
extern oal_uint32  dmac_tx_process_action_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_rx_process_sync_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_rx_process_priv_req_event(frw_event_mem_stru *pst_event_mem);
#if 0
extern oal_uint32  dmac_tx_complete_security_ap(dmac_user_stru *pst_dmac_user, hal_tx_dscr_stru *pst_dscr, oal_netbuf_stru *pst_buf);
#endif
extern oal_uint32  dmac_tx_complete_mgmt_notify(hal_to_dmac_device_stru *pst_hal_device, dmac_user_stru *pst_dmac_user, hal_tx_dscr_stru *pst_dscr, oal_netbuf_stru *pst_buf);
extern oal_uint32  dmac_mgmt_tx_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_join_set_reg_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_join_set_dtim_reg_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  dmac_asoc_set_reg_event_process(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_FEATURE_SMPS
extern oal_uint32  dmac_set_smps_process(frw_event_mem_stru *pst_event_mem);
#endif
extern oal_uint32  dmac_mgmt_conn_result_event(frw_event_mem_stru *pst_event_mem);
extern oal_void  dmac_mgmt_connect_set_channel(
                mac_device_stru    *pst_mac_device,
                mac_vap_stru       *pst_up_vap,
                mac_channel_stru   *pst_channel);

extern oal_void  dmac_send_2040_coext_mgmt_frame_sta(mac_vap_stru *pst_mac_vap);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_mgmt_classifier.h */
