/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_test_main.h
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

#ifndef __DMAC_TEST_MAIN_H__
#define __DMAC_TEST_MAIN_H__

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
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TEST_MAIN_H

/*****************************************************************************
  2 �궨��
*****************************************************************************/
typedef oal_uint32 (* dmac_test_encap_frame)(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_buff, oal_uint8 *puc_param, oal_uint32 ul_param_len);

/* ����оƬ��֤����ǰ����鿪�� */
#ifdef _PRE_WLAN_CHIP_TEST
#define DMAC_CHIP_TEST_CALL(func_call) do{\
    if(0 != dmac_test_get_chip_test())\
    {\
        (func_call);\
    }\
}while(0);
#else
#define DMAC_CHIP_TEST_CALL(func_call)
#endif


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
typedef struct dmac_lpm_txopps_tx_stub
{
    oal_uint8                       uc_stub_on;            /*0:off, 1:on*/
    oal_uint8                       auc_rsv[1];
    oal_uint16                      us_partial_aid_real;     /*��ʵ��Partial AID*/
    oal_uint16                      us_begin_num;            /* ��n�����Ĵ�׮ */
    oal_uint16                      us_curr_num;             /* ��ǰ�ǵڼ����� */
}dmac_lpm_txopps_tx_stub_stru;

typedef struct dmac_lpm_smps_tx_stub
{
    oal_uint8                       uc_stub_type;            /*0:off, 1:����,2:˫��*/
    oal_uint8                       uc_rts_en;             /* ��һ�����Ƿ�RTS */
    oal_uint8                       auc_rsv[2];
    oal_uint32                      ul_rate_real[HAL_TX_RATE_MAX_NUM];         /*��ʵ������*/
}dmac_lpm_smps_tx_stub_stru;

/*****************************************************************************
�ṹ˵��:����Ϊ���Ե�������ṹ������ͳһ�������в������õ��ĸ��ֿ��ƿ��أ���������������
������Ҫ����������ӽṹ��Ա�����Ǳ���
*****************************************************************************/
typedef struct dmac_test_mng
{
   dmac_lpm_txopps_tx_stub_stru 
st_lpm_txop_stub;    /*TXOP PS���Կ��غ�׮ʹ������*/
   dmac_lpm_smps_tx_stub_stru    st_lpm_smps_stub;    /*SMPS ��׮ʹ�ܺ�����*/
   oal_uint32                    ul_wow_int_cnt;      /*wow�����жϴ���*/
   oal_uint8                     uc_wow_en;           /*wow����ʹ��*/
   oal_uint8                     uc_txop_ps_en;       /*txopps ����ʹ��*/
   oal_uint8                     us_txop_rx_cnt;      /*txopps �����н��յ��Ĳ��Ա��ĸ���*/

   frw_timeout_stru              st_sleep_timer;      /* ����Ĵ���˯�߶�ʱ�� */

   /* ����֡�������ԣ���֡ */
   dmac_test_encap_frame  ast_dmac_encap_frame[MAC_TEST_MAX_TYPE_NUM];
   oal_uint8              uc_software_retry;
   oal_uint8              uc_retry_test;
   /* add4ģʽ���� */
   oal_uint8              uc_add4_open;

   /* оƬ��֤�����ܿ��� */
   oal_uint8              uc_chip_test_open;

   /* ����оƬ��֤DFX���� */
   oal_switch_enum_uint8  en_cfg_tx_cnt;

   /* ����msdu_life_time ���� */
   oal_uint8              uc_lifetime_flag;             /* 0:��ʾoff��1��ʾon */
   oal_int16              s_ct_sch_lifetime_delay_ms;   /* ������tx_dscpʱ��offset */
   oal_uint32             ul_tx_mpdu_num;               /* ����mpdu���� */
   oal_uint32             ul_tx_succ_mpdu_num;          /* ���ͳɹ���mpdu����*/
   oal_uint32             ul_rx_mpdu_num;               /* ���յ�mpdu���� */

   /* ����txop���� */
   oal_uint8              uc_long_nav_flag;             /* long nav ���Թ��ܿ��� */
   oal_uint8              uc_long_nav_is_enabled;       /* long nav�Ƿ�ʹ�� */

   /* ����cca���� */
   oal_uint8              uc_cca_flag;                  /* cca���Թ��ܿ��� */
   oal_uint32             ul_cca_rx_sta_num;            /* cca���Խ��յ���STA���� */
   oal_uint32             ul_cca_rx_ap_num;             /* �������޲��Խ��յ���ap���� */
   oal_uint32             ul_mean_backoff;              /* ƽ���˱�ʱ�� */
}dmac_test_mng_stru;
/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
#ifdef _PRE_WLAN_CHIP_TEST
extern dmac_test_mng_stru  g_st_dmac_test_mng;
#endif

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_void     dmac_test_init(oal_void);
extern dmac_test_encap_frame *dmac_test_get_encap_frame(oal_void);
extern oal_uint32   dmac_test_encap_init(dmac_test_encap_frame *pst_encap_fun);
extern oal_void     dmac_test_set_software_retry(oal_uint8 * puc_param);
extern oal_void     dmac_test_open_addr4(oal_uint8 *puc_add4_open);
extern oal_void     dmac_test_set_addr4(hal_tx_dscr_stru * pst_tx_dscr);

extern oal_void     dmac_test_set_dscr_software_retry(hal_to_dmac_device_stru * pst_hal_device, hal_tx_dscr_stru * pst_tx_dscr);
extern oal_uint32   dmac_test_get_chip_test(oal_void);
extern oal_void     dmac_test_set_chip_test(oal_uint8 uc_chip_test_open);
extern oal_void dmac_test_lpm_wow_init(oal_void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __HMAC_CHIP_TEST_H__ */

