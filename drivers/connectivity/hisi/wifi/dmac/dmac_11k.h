/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  ******************************************************************************
  �� �� ��   : dmac_11k.h
  �� �� ��   : ����
  ��    ��   : y00196452
  ��������   : 2016��5��4��
  ����޸�   :
  ��������   : 11k �ꡢö�ټ��ṹ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2016��5��4��
    ��    ��   : y00196452
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_11k_H__
#define __DMAC_11k_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_11K

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_mem.h"
#include "mac_vap.h"
#include "dmac_user.h"
#include "dmac_vap.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_11K_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  7 ��Ϣ����
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
extern oal_void  dmac_rrm_send_link_meas_rpt_action(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_rx_netbuf);
//extern oal_uint32 dmac_rrm_save_bss_info_event_process(frw_event_mem_stru *pst_event_mem);
extern oal_void dmac_rrm_proc_rm_request(dmac_vap_stru* pst_dmac_vap, oal_netbuf_stru *pst_netbuf);
extern oal_void dmac_rrm_encap_meas_rpt(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32 dmac_rrm_send_rm_rpt_action(dmac_vap_stru* pst_dmac_vap);
extern oal_uint32  dmac_send_sys_event(
                mac_vap_stru                     *pst_mac_vap,
                wlan_cfgid_enum_uint16            en_cfg_id,
                oal_uint16                        us_len,
                oal_uint8                        *puc_param);
extern oal_void dmac_rrm_get_link_req_info(dmac_vap_stru *pst_dmac_vap, oal_uint8 *puc_link_req_frame);
extern oal_uint32 dmac_rrm_start_scan_for_bcn_req(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_rrm_get_bcn_info_from_rx(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru  *pst_netbuf);
extern oal_uint32 dmac_rrm_handle_quiet(dmac_vap_stru  *pst_dmac_vap);
extern oal_uint32 dmac_rrm_proc_pwr_constraint(dmac_vap_stru  *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);
extern oal_uint32 dmac_rrm_parse_quiet(dmac_vap_stru  *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);
extern oal_uint32 dmac_rrm_fill_basic_rm_rpt_action(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_rrm_encap_and_send_bcn_rpt(dmac_vap_stru* pst_dmac_vap);
#endif //_PRE_WLAN_FEATURE_11K

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_11k.h */
