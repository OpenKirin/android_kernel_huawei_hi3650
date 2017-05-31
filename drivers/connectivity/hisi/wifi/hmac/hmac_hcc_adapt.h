/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_hcc_adapt
  �� �� ��   : ����
  ��    ��   : h00217255
  ��������   : 2014��10��8��
  ����޸�   :
  ��������   : hmac_hcc_adapt.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��18��
    ��    ��   : ����
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __HMAC_HCC_ADAPT_H__
#define __HMAC_HCC_ADAPT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oam_ext_if.h"
#include "hmac_ext_if.h"
#include "dmac_ext_if.h"
#include "frw_ext_if.h"
#include "frw_event_main.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_HCC_ADAPT_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/

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

/*Hcc �¼�����*/
extern oal_uint32 hmac_hcc_rx_event_comm_adapt(frw_event_mem_stru *pst_hcc_event_mem);
extern frw_event_mem_stru * hmac_hcc_test_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);


/*Rx���䲿��*/
extern frw_event_mem_stru * hmac_rx_process_data_sta_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

extern frw_event_mem_stru *  hmac_rx_process_mgmt_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
extern frw_event_mem_stru * hmac_hcc_rx_convert_netbuf_to_event_default(frw_event_mem_stru *pst_hcc_event_mem);
/*Tx���䲿��*/

extern oal_uint32 hmac_proc_add_user_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_del_user_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_config_syn_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_config_syn_alg_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_tx_host_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_test_hcc_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_mgmt_ctx_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_set_edca_param_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_tx_process_action_event_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_scan_proc_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
extern oal_uint32   hmac_dpd_data_processed_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif
extern oal_uint32   hmac_send_cali_data_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_scan_proc_sched_scan_req_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_mgmt_update_user_qos_table_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_proc_join_set_dtim_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint32(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint16(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_hcc_tx_convert_event_to_netbuf_uint8(frw_event_mem_stru *pst_event_mem);
extern frw_event_mem_stru * hmac_rx_convert_netbuf_to_netbuf_default(frw_event_mem_stru * pst_hcc_event_mem);
extern oal_uint32 hmac_proc_join_set_reg_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_user_add_notify_alg_tx_adapt(frw_event_mem_stru *pst_event_mem);

extern oal_uint32 hmac_proc_rx_process_sync_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_chan_select_channel_mac_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern oal_uint32 hmac_chan_initiate_switch_to_new_channel_tx_adapt(frw_event_mem_stru *pst_event_mem);
extern frw_event_mem_stru * hmac_cali2hmac_misc_event_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);

#ifdef _PRE_WLAN_FEATRUE_FLOWCTL
extern frw_event_mem_stru* hmac_alg_flowctl_backp_rx_adapt(frw_event_mem_stru * pst_hcc_event_mem);
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
extern oal_uint32 hmac_edca_opt_stat_event_tx_adapt(frw_event_mem_stru *pst_event_mem);
#endif

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_main */

