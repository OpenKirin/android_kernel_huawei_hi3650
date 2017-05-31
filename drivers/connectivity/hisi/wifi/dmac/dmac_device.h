/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_device.h
  �� �� ��   : ����
  ��    ��   : ��� 64406
  ��������   : 2015��5��7��
  ����޸�   :
  ��������   : dmac_main.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��7��
    ��    ��   : ��� 64406
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_DEVICE_H__
#define __DMAC_DEVICE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "mac_device.h"
#include "dmac_alg_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DEVICE_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MAX_MAC_ERR_IN_TBTT 5   /*ÿһ��tbtt��϶������ֵ���������*/

#define DMAC_COMPATIBILITY_RATE_LIMIT_TABLE \
  { /* ����       11A  11B  11G  MIXED_ONE_11G  MIXED_TWO_11G  HT       VHT      HT_ONLY   VHT_ONLY   HT_11G  (Kbp/s)*/  \
    /* 20M  */ {   0,   0,   0,   0,             0,            60000,   70000,   60000,    70000,     60000}, \
    /* 40M  */ {   0,   0,   0,   0,             0,            80000,   100000,  80000,    100000,    80000}, \
    /* 80M  */ {   0,   0,   0,   0,             0,            0,       0,       0,        0,         0}, \
    /* 160M */ {   0,   0,   0,   0,             0,            0,       0,       0,        0,         0}, \
  }


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
/* Dmac device�ṹ�壬��¼ֻ������Dmac��device������Ϣ */
/* �豸����״̬ */
typedef struct
{
    dmac_alg_tpc_user_distance_enum_uint8           en_dmac_device_distance_enum;
    dmac_alg_cca_opt_intf_mode_enum_uint8           en_cca_intf_state;
    oal_bool_enum_uint8                             en_co_intf_state;
    oal_uint8                                       uc_resv[1];
} dmac_alg_stat_stru;

typedef struct
{
    oal_uint32              ul_rx_rate;
    oal_uint16              us_rx_rate_stat_count;
    oal_bool_enum_uint8     en_compatibility_enable;
    oal_bool_enum_uint8     en_compatibility_stat;
    oal_uint32              aul_compatibility_rate_limit[WLAN_BW_CAP_BUTT][WLAN_PROTOCOL_BUTT];
} dmac_compatibility_stat_stru;


/* dmac device�ṹ�壬��¼ֻ������dmac��device������Ϣ */
typedef struct
{
    mac_device_stru                    *pst_device_base_info;                   /* ָ�򹫹�����mac device */
#ifdef _PRE_WLAN_FEATURE_DFR
    oal_bool_enum_uint8                 en_dfr_hw_reset_enable;                 //device��hw reset��ʹ�ܿ���
    oal_uint8                           auc_rev[3];
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    frw_timeout_stru                    st_pcie_err_timer;                      /* ���pcie err_nonfatal ��ʱ�� */
    oal_uint32                          ul_pcie_err_cnt;                        /* pcie err���� */
#endif
#endif //_PRE_WLAN_DFT_STAT
#ifdef _PRE_WLAN_SW_CTRL_RSP
    oal_uint8                           uc_rsp_frm_rate_val;
    oal_bool_enum_uint8                 en_state_in_sw_ctrl_mode;
    hal_channel_assemble_enum_uint8     en_usr_bw_mode;
    oal_uint8                           auc_rsv[1];
#endif
    dmac_alg_stat_stru                  st_dmac_alg_stat;
    dmac_compatibility_stat_stru        st_dmac_compatibility_stat;
}dmac_device_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : dmac_fcs_get_mgr_stru
 ��������  : ��ȡָ��device��fcs mgr
 �������  : mac_device_stru *pst_device
 �������  : ��
 �� �� ֵ  : OAL_STATIC OAL_INLINE mac_fcs_mgr_stru *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE mac_fcs_mgr_stru* dmac_fcs_get_mgr_stru(mac_device_stru *pst_device)
{
#if IS_DEVICE
    return  &pst_device->st_fcs_mgr;
#else
    return OAL_PTR_NULL;
#endif
}


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern  oal_uint32 dmac_device_exception_report_timeout_fn(oal_void *p_arg);

/*****************************************************************************
  10.1 �����ṹ���ʼ����ɾ��
*****************************************************************************/

extern oal_uint32  dmac_board_exit(mac_board_stru *pst_board);
extern oal_uint32  dmac_board_init(mac_board_stru *pst_board);

/*****************************************************************************
  10.2 ������Ա���ʲ���
*****************************************************************************/
extern oal_uint32  dmac_mac_error_overload(mac_device_stru *pst_mac_device, hal_mac_error_type_enum_uint8 en_error_id);
extern oal_void  dmac_mac_error_cnt_clr(mac_device_stru *pst_mac_device);
extern oal_void  dmac_mac_error_cnt_inc(mac_device_stru *pst_mac_device, oal_uint8 uc_mac_int_bit);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_device.h */
