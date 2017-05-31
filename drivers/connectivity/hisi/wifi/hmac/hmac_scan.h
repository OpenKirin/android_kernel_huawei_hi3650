/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_scan.h
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2014��11��26��
  ����޸�   :
  ��������   : hmac_scan.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��26��
    ��    ��   : zhangheng
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __HMAC_SCAN_H__
#define __HMAC_SCAN_H__

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
#include "hmac_vap.h"
#include "mac_device.h"
#include "hmac_device.h"



#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_SCAN_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* ɨ�赽��bss���ϻ�ʱ�䣬С�ڴ�ֵ���·���ɨ������ʱ����ɾ����bss��Ϣ */
#define HMAC_SCAN_MAX_SCANNED_BSS_EXPIRE         25000   /* 25000 milliseconds */

/* ɨ��������Ч�Ըߵ�ʱ�䷶Χ������������Ŀ�����ѡ�Ȳ��� */
#define HMAC_SCAN_MAX_VALID_SCANNED_BSS_EXPIRE   3000    /* 3000 milliseconds */

/* ɨ�赽��bss��rssi�ϻ�ʱ�� */
#define HMAC_SCAN_MAX_SCANNED_RSSI_EXPIRE        1000    /* 1000 milliseconds */

#define HMAC_INIT_SCAN_TIMEOUT_MS   10000
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
/* HMAC SCAN����ӿ� */
extern oal_void hmac_scan_print_scanned_bss_info(oal_uint8 uc_device_id);

extern mac_bss_dscr_stru *hmac_scan_find_scanned_bss_dscr_by_index(oal_uint8  uc_device_id,
                                                                                oal_uint32 ul_bss_index);
extern hmac_scanned_bss_info *hmac_scan_find_scanned_bss_by_bssid(hmac_bss_mgmt_stru *pst_bss_mgmt, oal_uint8 *puc_bssid);
extern oal_uint32 hmac_scan_proc_scanned_bss(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  hmac_scan_proc_scan_comp_event(frw_event_mem_stru *pst_event_mem);
extern oal_uint32  hmac_scan_proc_scan_req_event_exception(hmac_vap_stru *pst_hmac_vap, oal_void *p_params);
extern oal_uint32  hmac_scan_proc_scan_req_event(hmac_vap_stru *pst_hmac_vap, oal_void *p_params);
extern oal_uint32  hmac_scan_proc_sched_scan_req_event(hmac_vap_stru *pst_hmac_vap, oal_void *p_params);
extern oal_void    hmac_scan_init(hmac_device_stru *pst_hmac_device);
extern oal_void    hmac_scan_exit(hmac_device_stru *pst_hmac_device);
extern oal_uint32  hmac_scan_process_chan_result_event(frw_event_mem_stru *pst_event_mem);
#ifdef _PRE_DEBUG_MODE
extern oal_uint32  hmac_scan_test(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#endif
extern oal_uint32  hmac_bgscan_enable(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param);
#if defined(_PRE_SUPPORT_ACS) || defined(_PRE_WLAN_FEATURE_DFS) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
extern oal_uint32 hmac_init_scan_process(hmac_device_stru *pst_mac_dev, mac_vap_stru *pst_mac_vap, mac_scan_op_enum_uint8 en_op_type);
extern oal_uint32 hmac_init_scan_try(mac_device_stru *pst_mac_device, mac_vap_stru *pst_mac_vap, mac_try_init_scan_type en_type);
extern oal_uint32 hmac_init_scan_cancel_timer(hmac_device_stru *pst_hmac_dev);
extern oal_bool_enum_uint8 hmac_device_in_init_scan(mac_device_stru *pst_mac_device);
#endif
extern oal_uint32 hmac_start_all_bss_of_device(hmac_device_stru *pst_dev);
extern oal_void  hmac_scan_set_sour_mac_addr_in_probe_req(hmac_vap_stru        *pst_hmac_vap,
                                                              oal_uint8            *puc_sour_mac_addr,
                                                              oal_bool_enum_uint8   en_is_rand_mac_addr_scan,
                                                              oal_bool_enum_uint8   en_is_p2p0_scan);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_scan.h */
