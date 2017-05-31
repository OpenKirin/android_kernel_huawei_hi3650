/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_chip_test.h
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2012��9��18��
  ����޸�   :
  ��������   : dmac_chip_test.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��18��
    ��    ��   : z52447
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_CHIP_TEST_H__
#define __DMAC_CHIP_TEST_H__

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
#include "hal_ext_if.h"
#ifdef _PRE_WLAN_ALG_ENABLE
#include "alg_ext_if.h"
#endif
#include "dmac_ext_if.h"
#include "dmac_vap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_LPM_TEST_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
    DMAC_TEST_STUB_BEGIN  = 0,
    DMAC_TEST_STUB_END,

    DMAC_TEST_STUB_END_BUTT
}dmac_test_stub_opera_enum;
typedef oal_uint8 dmac_test_stub_opera_enum_uint8;

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
extern oal_void  dmac_test_lpm_txopps_set_partial_aid(dmac_vap_stru *pst_dmac_vap,dmac_user_stru *pst_dmac_user,dmac_test_stub_opera_enum_uint8 en_opera);
extern oal_uint32 dmac_test_lpm_send_probe_requst(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_positive,oal_uint8* puc_bssid);
extern oal_uint32 dmac_test_lpm_wow_prepare_probe_resp(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_test_lpm_wow_release_probe_resp(dmac_vap_stru *pst_dmac_vap);
extern oal_uint32 dmac_test_lpm_wow_prepare_null_data(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_test_lpm_wow_release_null_data(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_test_lpm_smps_set_rate(mac_tx_ctl_stru *pst_tx_ctl,hal_tx_txop_alg_stru *pst_txop_alg,dmac_test_stub_opera_enum_uint8 en_opera);
extern oal_void dmac_test_lpm_set_wow_en(oal_uint8 uc_en);
extern oal_uint8 dmac_test_lpm_get_wow_en(oal_void);
extern oal_void dmac_test_lpm_wow_debug(oal_void);
extern oal_uint32 dmac_test_lpm_send_nulldata(dmac_vap_stru *pst_dmac_vap,oal_uint8 uc_psm,oal_uint8* puc_da);
extern oal_void dmac_test_lpm_txopps_debug(oal_void);
extern oal_void dmac_test_lpm_txopps_rx_count(oal_uint16 us_pkt_len);
extern oal_void dmac_test_lpm_txopps_en(oal_uint8 uc_en);
extern oal_void dmac_test_always_tx(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr);
extern oal_void  dmac_test_dfx_set_tx_cnt(hal_tx_txop_alg_stru *pst_txop_alg);
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __HMAC_CHIP_TEST_H__ */
