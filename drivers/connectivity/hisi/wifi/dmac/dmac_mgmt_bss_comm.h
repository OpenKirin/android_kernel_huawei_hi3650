/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_mgmt_bss_comm.h
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2013��4��9��
  ����޸�   :
  ��������   : dmac_mgmt_bss_comm.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��4��9��
    ��    ��   : huxiaotong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_MGMT_BSS_COMM_H__
#define __DMAC_MGMT_BSS_COMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "wlan_spec.h"
#include "hal_ext_if.h"
#include "dmac_ext_if.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_MGMT_BSS_COMM_H
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
extern oal_uint16  dmac_ba_encap_blockack_req(
                       dmac_vap_stru     *pst_dmac_vap,
                       oal_netbuf_stru   *pst_netbuf,
                       dmac_ba_tx_stru   *pst_ba_tx_hdl,
                       oal_uint8          uc_tid);
extern oal_uint32  dmac_mgmt_delba(
                       dmac_vap_stru          *pst_dmac_vap,
                       dmac_user_stru         *pst_dmac_user,
                       oal_uint8               uc_tid,
                       oal_uint8               uc_initiator,
                       oal_uint8               uc_reason);
extern oal_uint32  dmac_mgmt_rx_addba_rsp(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_crx_action_event);
extern oal_uint32  dmac_mgmt_rx_delba(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_crx_action_event);
extern oal_uint32  dmac_mgmt_tx_addba_req(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_ctx_action_event,
                       oal_netbuf_stru                *pst_net_buff);
extern oal_uint32  dmac_mgmt_tx_addba_rsp(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_ctx_action_event,
                       oal_netbuf_stru                *pst_net_buff);
extern oal_uint32  dmac_mgmt_tx_delba(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       dmac_ctx_action_event_stru     *pst_ctx_action_event,
                       oal_netbuf_stru                *pst_net_buff);
extern oal_uint32  dmac_mgmt_rx_ampdu_start(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       mac_priv_req_args_stru         *pst_crx_req_args);
extern oal_uint32  dmac_mgmt_rx_ampdu_end(
                       mac_device_stru                *pst_device,
                       dmac_vap_stru                  *pst_dmac_vap,
                       mac_priv_req_args_stru         *pst_crx_req_args);
extern oal_uint32  dmac_mgmt_scan_timeout(dmac_vap_stru *pst_dmac_vap, oal_void *p_param);

extern oal_uint32  dmac_mgmt_switch_channel(mac_device_stru *pst_mac_device, mac_channel_stru *pst_channel, oal_uint8 en_clear_fifo);

/* Channel Switch ��ط�װ���� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_uint32  dmac_mgmt_encap_csa_action(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_buffer, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw);
#else
extern oal_uint32  dmac_mgmt_encap_csa_action(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_buffer, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw);
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
extern oal_uint32  dmac_mgmt_encap_ext_csa_action(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_buffer, oal_uint8 uc_opert_class, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw);
#endif
extern oal_uint32  dmac_mgmt_send_csa_action(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_channel, oal_uint8 uc_csa_cnt, wlan_channel_bandwidth_enum_uint8 en_bw);

extern oal_uint32  dmac_mgmt_scan_vap_down(mac_vap_stru *pst_mac_vap);
extern oal_void  dmac_set_cap_info_field(oal_void *pst_vap, oal_uint8 *puc_buffer);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_mgmt_bss_comm.h */
