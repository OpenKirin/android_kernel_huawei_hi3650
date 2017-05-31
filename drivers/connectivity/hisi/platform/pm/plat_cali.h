/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : plat_cali.h
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   : plat_cali.cͷ�ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2015��7��16��
    ��    ��   : z00299054
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __PLAT_CALI_H__
#define __PLAT_CALI_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "oal_types.h"
#include "oal_util.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define OAL_2G_CHANNEL_NUM         (13)
#define OAL_5G_20M_CHANNEL_NUM     (7)
#define OAL_5G_80M_CHANNEL_NUM     (7)
#define OAL_5G_CHANNEL_NUM         (OAL_5G_20M_CHANNEL_NUM + OAL_5G_80M_CHANNEL_NUM)
#define OAL_5G_DEVICE_CHANNEL_NUM  (7)
#define OAL_CALI_HCC_BUF_NUM       (3)
#define OAL_CALI_HCC_BUF_SIZE      (1500)
#define OAL_BT_RF_FEQ_NUM          (79)            /* total Rf frequency number */
#define OAL_BT_CHANNEL_NUM         (8)            /* total Rf frequency number */
#define OAL_BT_POWER_CALI_CHANNEL_NUM         (3)

#define WIFI_2_4G_ONLY              (0x2424)
#define SYS_EXCEP_REBOOT            (0xC7C7)
#define OAL_CALI_PARAM_ADDITION_LEN (8)
#define OAL_5G_IQ_CALI_TONE_NUM         (8)

#define CHECK_5G_ENABLE             "band_5g_enable"

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
extern oal_uint8 g_uc_netdev_is_open;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

typedef struct
{
    oal_uint16  us_analog_rxdc_cmp;
    oal_uint16  us_digital_rxdc_cmp_i;
    oal_uint16  us_digital_rxdc_cmp_q;
    oal_uint8   auc_reserve[2];
}oal_rx_dc_comp_val_stru;

typedef struct
{
    oal_uint8   upc_ppa_cmp;
    oal_int8    ac_atx_pwr_cmp;
    oal_uint8   dtx_pwr_cmp;
    oal_uint8   auc_reserve[1];
}oal_2G_tx_power_comp_val_stru;

typedef struct
{
    oal_uint8   upc_ppa_cmp;
    oal_uint8   upc_mx_cmp;
    oal_int8    ac_atx_pwr_cmp;
    oal_uint8   dtx_pwr_cmp;
}oal_5G_tx_power_comp_val_stru;

typedef struct
{
    oal_uint16  us_txdc_cmp_i;
    oal_uint16  us_txdc_cmp_q;
}oal_txdc_comp_val_stru;

typedef struct
{
    oal_uint8   uc_ppf_val;
    oal_uint8   auc_reserve[3];
}oal_ppf_comp_val_stru;

typedef struct
{
    oal_uint16   us_txiq_cmp_p;
    oal_uint16   us_txiq_cmp_e;
}oal_txiq_comp_val_stru;

typedef struct
{
    oal_uint32  ul_rxiq_cmp_u1;
    oal_uint32  ul_rxiq_cmp_u2;
    oal_uint32  ul_rxiq_cmp_alpha;
    oal_uint32  ul_rxiq_cmp_beta;
}oal_new_rxiq_comp_val_stru;


typedef struct
{
    oal_uint32  aul_alpha_reg_val[OAL_5G_IQ_CALI_TONE_NUM];
    oal_uint32  aul_beta_reg_val[OAL_5G_IQ_CALI_TONE_NUM];
    oal_uint32  aul_alpha0_reg_val[OAL_5G_IQ_CALI_TONE_NUM];
    oal_uint32  aul_beta0_reg_val[OAL_5G_IQ_CALI_TONE_NUM];
}oal_new_txiq_comp_val_stru;

typedef struct
{
    oal_rx_dc_comp_val_stru        g_st_cali_rx_dc_cmp_2G;
    oal_2G_tx_power_comp_val_stru  g_st_cali_tx_power_cmp_2G;
    oal_txdc_comp_val_stru         g_st_txdc_cmp_val;
    oal_txiq_comp_val_stru         g_st_txiq_cmp_val_2G;
}oal_2Gcali_param_stru;

typedef struct
{
    oal_rx_dc_comp_val_stru        g_st_cali_rx_dc_cmp_5G;
    oal_5G_tx_power_comp_val_stru  g_st_cali_tx_power_cmp_5G;
    oal_ppf_comp_val_stru          g_st_ppf_cmp_val;
    oal_txdc_comp_val_stru         g_st_txdc_cmp_val;
    oal_txiq_comp_val_stru         g_st_txiq_cmp_val_5G;
}oal_5Gcali_param_stru;

typedef struct
{
    oal_2Gcali_param_stru st_2Gcali_param[OAL_2G_CHANNEL_NUM];
    oal_5Gcali_param_stru st_5Gcali_param[OAL_5G_CHANNEL_NUM];
}oal_wifi_cali_param_stru;

typedef struct
{
    oal_uint16 us_bt_rx_dc_comp;
    oal_uint8  auc_reserve0[2];
    oal_uint8  auc_upc_ppa_cmp[OAL_BT_POWER_CALI_CHANNEL_NUM];
    oal_uint8  auc_reserve1[1];
    oal_int8   ac_atx_pwr_cmp[OAL_BT_POWER_CALI_CHANNEL_NUM];
    oal_uint8  auc_reserve2[1];
    oal_uint8  auc_bt_pll_tx_comp[OAL_BT_RF_FEQ_NUM];
    oal_uint8  auc_reserve3[1];
    oal_uint8  auc_bt_pll_rx_comp[OAL_BT_RF_FEQ_NUM];
    oal_uint8  auc_reserve4[1];
    oal_uint32   uc_cali_flag;
    oal_uint16  us_txdc_cmp_i;
    oal_uint16  us_txdc_cmp_q;
    oal_uint16  us_txdc_cmp_iq_p;
    oal_uint16  us_txdc_cmp_iq_e;
    oal_int8   ac_bt_atx_pwr_cmp[OAL_BT_CHANNEL_NUM];
    oal_int8   ac_bt_atx_pwr_fre[OAL_BT_CHANNEL_NUM];
    oal_uint16  ac_bt_pwr_fre_num;
    oal_uint8  auc_reserve5[2];
}oal_bt_cali_comp_stru;

typedef struct
{
    oal_uint16  ul_cali_time;
    oal_uint16  bit_temperature     : 3,
                uc_5g_chan_idx1     : 5,
                uc_5g_chan_idx2     : 5,
                en_update_bt        : 4;
}oal_update_cali_channel_stru;

typedef struct
{
    oal_uint8              g_uc_rc_cmp_code;
    oal_uint8              g_uc_r_cmp_code;
    oal_uint8              g_uc_c_cmp_code;
    oal_bool_enum_uint8    en_save_all;
    oal_bt_cali_comp_stru  st_bt_cali_comp;
}oal_bfgn_cali_param_stru;

typedef struct
{
    oal_uint32                   ul_dog_tag;
    oal_2Gcali_param_stru        ast_2Gcali_param[OAL_2G_CHANNEL_NUM];
    oal_5Gcali_param_stru        ast_5Gcali_param[OAL_5G_CHANNEL_NUM];
    oal_ppf_comp_val_stru        st_165chan_ppf_comp;
    oal_update_cali_channel_stru st_cali_update_info;
    oal_uint32                   ul_check_hw_status;

#ifdef _PRE_WLAN_NEW_IQ
    oal_new_rxiq_comp_val_stru   ast_new_rxiq_cmp_val_5G[OAL_5G_80M_CHANNEL_NUM];

    oal_new_txiq_comp_val_stru   ast_new_txiq_cmp_val_5G[OAL_5G_80M_CHANNEL_NUM];
#endif
    oal_bfgn_cali_param_stru     st_bfgn_cali_data;

}oal_cali_param_stru;

typedef struct
{
    oal_uint32 ul_wifi_2_4g_only;
    oal_uint32 ul_excep_reboot;
    oal_uint32 ul_reserve[OAL_CALI_PARAM_ADDITION_LEN];
}oal_cali_param_addition_stru;


/*****************************************************************************
  8 UNION����
*****************************************************************************/
#define OAL_WIFI_CALI_DATA_DOWNLOAD_LEN (OAL_SIZEOF(oal_cali_param_stru) - 4 - OAL_SIZEOF(oal_bfgn_cali_param_stru) + 4)
#define OAL_WIFI_CALI_DATA_UPLOAD_LEN (OAL_SIZEOF(oal_cali_param_stru) - 4)


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_int32 get_cali_count(oal_uint32 *count);
extern oal_int32 get_bfgx_cali_data(oal_uint8 *buf, oal_uint32 *len, oal_uint32 buf_len);
extern void *get_cali_data_buf_addr(void);
extern oal_int32 cali_data_buf_malloc(void);
extern void  cali_data_buf_free(void);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of plat_cali.h */










