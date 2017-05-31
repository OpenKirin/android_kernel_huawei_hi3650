/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_tx_complete.h
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2012��12��13��
  ����޸�   :
  ��������   : dmac_tx_complete.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��13��
    ��    ��   : t00231215
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_TX_COMPLETE_H__
#define __DMAC_TX_COMPLETE_H__

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
#include "mac_device.h"
#include "mac_vap.h"
#include "dmac_ext_if.h"
#include "dmac_user.h"
#include "dmac_vap.h"
#include "dmac_tx_bss_comm.h"
#include "dmac_stat.h"
#include "dmac_main.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TX_COMPLETE_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#ifdef _PRE_WLAN_INIT_PTK_TX_PN
#define DMAC_MAX_RA_LUT_INDEX   32
#define WLAN_CHIP_MAX_NUM       2
#endif
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern oal_uint8 g_uc_aggr_num_switch;     /* �������AMPDU�ۺϸ������� */
extern oal_uint8 g_uc_max_aggr_num;     /* �������AMPDU�ۺϸ��� */


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
#ifdef _PRE_WLAN_INIT_PTK_TX_PN
typedef struct
{
    oal_uint8   uc_pn_peer_idx;     /* �Զ�peer����,0~31 */
    oal_uint32  ul_pn_msb;          /* ����������pnֵ�ĸ�32λ */
    oal_uint32  ul_pn_lsb;          /* ����������pnֵ�ĵ�32λ */
}dmac_tx_dscr_pn_stru;

typedef struct
{
    oal_uint32  ul_pn_msb;          /* ����������pnֵ�ĸ�32λ */
    oal_uint32  ul_pn_lsb;          /* ����������pnֵ�ĵ�32λ */
    oal_uint32  ul_phy_mode_one;    /* ����������phy mode�ֶ� */
    oal_uint16  us_seq_num;    /* ����������seq num */
    hal_tx_dscr_ctrl_one_param st_tx_dscr_one; /* �����������е�ctrl one param�ֶ� */
}dmac_tx_dscr_mac_phy_param_stru;
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
extern oal_uint32  dmac_tx_complete_event_handler(frw_event_mem_stru *pst_event_mem);
extern oal_void dmac_tx_reset_flush(hal_to_dmac_device_stru *pst_device);
extern oal_uint32  dmac_tx_complete_schedule(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_ac_num);
#if 0
extern oal_void  dmac_tx_delete_dscr(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_delete_dscr);
#endif
extern oal_uint32  dmac_tx_complete_buff(hal_to_dmac_device_stru *pst_hal_device, hal_tx_dscr_stru *pst_dscr);
extern oal_uint32  dmac_mgmt_tx_complete(mac_vap_stru *pst_mac_vap, oal_uint8 mgmt_frame_id, oal_uint32 uc_dscr_status, oal_uint8 uc_user_idx);
extern oal_void  dmac_tx_complete_free_dscr(hal_tx_dscr_stru *pst_dscr);
extern oal_void  dmac_tx_complete_free_dscr_list(hal_tx_dscr_stru *pst_dscr, oal_uint8 uc_dscr_num);
extern oal_void  dmac_tx_delete_ba(dmac_user_stru *pst_dmac_user);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_tx_complete.h */
