/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_dft.c
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2014��8��13��
  ����޸�   :
  ��������   : ά�⹦����ض����ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��8��13��
    ��    ��   : z00237171
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_net.h"
#include "oam_ext_if.h"
#include "hal_ext_if.h"
#include "hal_witp_pa_reg.h"
#include "hal_witp_phy_reg.h"
#include "mac_resource.h"
#include "dmac_dft.h"
#include "dmac_ext_if.h"
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
#include "hal_phy_reg.h"
#include "hal_mac_reg.h"
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#include "oal_mem.h"
#include "frw_event_main.h"
#include "pm_extern.h"
#ifdef _PRE_WLAN_FEATURE_STA_PM
#include "dmac_sta_pm.h"
#endif
#endif
#include "dmac_config.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_DFT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT

/* PHY����LNA�����뵵λ�Ķ�Ӧ��,��λ��1dB, ��ʵֵ��С�����������˳�100������һ��ֵ0Ϊ��Чֵ */
OAL_STATIC oal_int32   g_al_intlna_gain[DMAC_DFT_PHY_INTLAN_GAIN_NUM] =
{0, -310, 290, 890, 1490, 2090, 2690, 3290};

/* PHY VGA�����뵵λ�Ķ�Ӧ����λ��1dB, ����100���� */
OAL_STATIC oal_int32   g_al_vga_gain[DMAC_DFT_PHY_VGA_GAIN_NUM] =
{0, 100, 200, 300, 400, 500, 600, 700, 800, 900,
1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900,
2000, 2100, 2200, 2300, 2400, 2500, 2600, -500, -400, -300,
-200, -100};

#endif
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_dft_set_phy_stat_node
 ��������  : ����phy��ͳ�ƽڵ㣬phy��16��ͳ�ƽڵ㣬����ÿ��ֻ��4�����Թ���
             ����Ҫָ�������Ľڵ��idx,����phy�Ĵ���
 �������  : oam_stats_phy_node_idx_stru: ����phy��ǰʹ�ܵ�ͳ�ƽڵ�idx�Ľṹָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��13��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_set_phy_stat_node(
                                    mac_device_stru *pst_device,
                                    oam_stats_phy_node_idx_stru *pst_phy_node_idx)
{
    hal_dft_set_phy_stat_node(pst_device->pst_device_stru,pst_phy_node_idx);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_adc_pin
 ��������  : ��ȡphy ADC�ڹ���, ������С��������100����ת����������������ʾ��
             ת����С��.���ڴӼĴ����ж�ȡ������ֵ��λ��0.25dB����˻�Ҫ����4
             ����
 �������  : ul_adc_pin_code_rpt:PHY bank2 ADC_PIN_CODE_RPT�Ĵ�����ֵ,
                                 AGC ADC�ڹ����������λֵ�ϱ�
 �������  : pl_adc_pin:phy ADC�ڹ���
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_adc_pin(oal_uint32 ul_adc_pin_code_rpt,
                                                  oal_int32 *pl_adc_pin)
{
    oal_int32       l_adc_pin_phy;       /* ��phy�Ĵ����ж�ȡ������adc�ڹ���ֵ����ʱ��λ��0.25dB */

    /* ul_adc_pin_code_rpt�ĵ�9bitֵ��ADC�ڹ��ʣ��з���������λ0.25dB,���ݷ���λ
       ��ȷ����ʵֵ
    */
    if (BIT8 != (BIT8 & ul_adc_pin_code_rpt))
    {
        /* ������ֱ��ת��Ϊ��λΪ1dB��ֵ,Ȼ�����100��֤����������������� */
        *pl_adc_pin = (ul_adc_pin_code_rpt & 0x1FF) * 100 / 4;
    }
    else
    {

        l_adc_pin_phy = (oal_int32)ul_adc_pin_code_rpt;
        /*lint -e701*//*lint -e702*/
        l_adc_pin_phy = (oal_int32)(l_adc_pin_phy << 23);
        l_adc_pin_phy = (oal_int32)(l_adc_pin_phy >> 23);
        /*lint +e701*//*lint +e702*/
        *pl_adc_pin = l_adc_pin_phy * 100 / 4;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_extlna_gain
 ��������  : ��ȡ����LNA����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_extlna_gain(mac_device_stru *pst_macdev,
                                                      oal_uint32 ul_adc_pin_code_rpt,
                                                      oal_int32 *pl_extlna_gain)
{
    oal_uint32          ul_extlna_gain0_cfg = 0;
    oal_uint32          ul_extlna_gain1_cfg = 0;
    oal_int32           l_extlna_gain0_cfg;
    oal_int32           l_extlna_gain1_cfg;
    oal_uint8           uc_lna_code_out_3;
    oal_int32           l_extlna_gain;

    /* ��ȡ����LNAΪ0��1ʱ���� */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_EXTLNA_GAIN0_CFG_REG, &ul_extlna_gain0_cfg);
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_EXTLNA_GAIN1_CFG_REG, &ul_extlna_gain1_cfg);
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_PHY_EXTLNA_GAIN0_CFG_REG, &ul_extlna_gain0_cfg);
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_PHY_EXTLNA_GAIN1_CFG_REG, &ul_extlna_gain1_cfg);
#endif
    /*lint -e701*//*lint -e702*/
    /* ��������LNAΪ0ʱ������ֵ */
    l_extlna_gain0_cfg = (oal_int32)(ul_extlna_gain0_cfg);
    l_extlna_gain0_cfg = (oal_int32)(l_extlna_gain0_cfg << 22);
    l_extlna_gain0_cfg = (oal_int32)(l_extlna_gain0_cfg >> 22);

    /* ��������LNAΪ1ʱ������ֵ */
    l_extlna_gain1_cfg = (oal_int32)(ul_extlna_gain1_cfg);
    l_extlna_gain1_cfg = (oal_int32)(l_extlna_gain1_cfg << 22);
    l_extlna_gain1_cfg = (oal_int32)(l_extlna_gain1_cfg >> 22);
    /*lint +e701*//*lint +e702*/
    /* ��ȡ����LNA��λֵ */
    uc_lna_code_out_3 = (ul_adc_pin_code_rpt & BIT15) >> 15;

    /* ��������LNA���� */
    l_extlna_gain = (uc_lna_code_out_3 == 0) ? l_extlna_gain0_cfg : l_extlna_gain1_cfg;

    *pl_extlna_gain = l_extlna_gain * 100 / 4;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_intlna_gain
 ��������  : ��ȡ����LNA����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_intlna_gain(oal_uint32 ul_adc_pin_code_rpt,
                                                      oal_int32 *pl_intlna_gain)
{
    oal_uint8       uc_lna_code_out_0_2;

    /* ��ȡ����LNA��λֵ������������LNA���� */
    uc_lna_code_out_0_2 = (ul_adc_pin_code_rpt & (BIT12 | BIT13 | BIT14)) >> 12;

    if (0 == uc_lna_code_out_0_2 || DMAC_DFT_PHY_INTLAN_GAIN_NUM <= uc_lna_code_out_0_2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dft_get_intlna_gain:: lna_code_out[2:0] val=[%d] invalid.}",
                         uc_lna_code_out_0_2);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    *pl_intlna_gain = g_al_intlna_gain[uc_lna_code_out_0_2];

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_vga_gain
 ��������  : �����ȡvga����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_vga_gain(oal_uint32 ul_adc_pin_code_rpt,
                                                   oal_int32 *pl_vga_gain)
{
    oal_uint8       uc_vga_coude_out_0_4;

    /* ��ȡVGA��λֵ��������VGA���� */
    uc_vga_coude_out_0_4 = (ul_adc_pin_code_rpt & (BIT16 | BIT17 | BIT18 | BIT19 | BIT20)) >> 16;

    if (DMAC_DFT_PHY_VGA_GAIN_NUM <= uc_vga_coude_out_0_4)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dft_get_vga_gain:: vga_coude_out[4:0] val=[%d] invalid.}",
                         uc_vga_coude_out_0_4);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    *pl_vga_gain = g_al_vga_gain[uc_vga_coude_out_0_4];

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_reference0
 ��������  : ��ȡ�������߿ڹ��ʲο�ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_reference0(mac_device_stru *pst_macdev,
                                                     oal_int32 *pl_reference0)
{
    oal_uint32      ul_cfg_power0_ref = 0;
    oal_int32       l_cfg_power0_ref;

    /* ����������߿ڹ��ʼ���ο�ֵ */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_POWER0_REF_REG, &ul_cfg_power0_ref);
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_PHY_POWER0_REF_REG, &ul_cfg_power0_ref);
#endif
    /*lint -e701*//*lint -e702*/
    l_cfg_power0_ref = (oal_int32)ul_cfg_power0_ref;
    l_cfg_power0_ref = (oal_int32)(l_cfg_power0_ref << 24);
    l_cfg_power0_ref = (oal_int32)(l_cfg_power0_ref >> 24);
    /*lint +e701*//*lint +e702*/
    *pl_reference0 = l_cfg_power0_ref * 100 / 4;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_calcu_antenna_power
 ��������  : tbtt�жϵ�����ʱ�򣬼������߿ڹ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��29��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_dft_calcu_antenna_power(mac_device_stru *pst_macdev)
{
    oal_uint32          ul_adc_pin_code_rpt;       /* PHY bank2 ADC_PIN_CODE_RPT�Ĵ�����ֵ */
    oal_int32           l_adc_pin = 0;
    oal_int32           l_extlna_gain = 0;             /* ����LNA���� */
    oal_int32           l_intlna_gain = 0;             /* ����LNA���� */
    oal_int32           l_vga_gain = 0;                /* VGA���� */
    oal_int32           l_reference0 = 0;              /* �������߿ڹ��ʼ���ο�ֵ */

    /* phy�ṩ�ĵ�����㹫ʽ: adc_pin - (extlna_gain + intlna_gain + vga_gain + reference_0)*/

    /* ��ȡPHY AGC ADC�ڹ����������λֵ */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_ADC_PIN_CODE_RPT_REG, &ul_adc_pin_code_rpt);
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_PHY_ADC_PIN_CODE_RPT_REG, &ul_adc_pin_code_rpt);
#endif

    /* ��ȡADC�ڹ��� */
    dmac_dft_get_adc_pin(ul_adc_pin_code_rpt, &l_adc_pin);

    /* ��ȡ����LNA���� */
    dmac_dft_get_extlna_gain(pst_macdev, ul_adc_pin_code_rpt, &l_extlna_gain);

    /* ��ȡ����LNA���� */
    dmac_dft_get_intlna_gain(ul_adc_pin_code_rpt, &l_intlna_gain);

    /* ��ȡVGA���� */
    dmac_dft_get_vga_gain(ul_adc_pin_code_rpt, &l_vga_gain);

    /* ��ȡ�������߿ڹ��ʼ���ο�ֵ */
    dmac_dft_get_reference0(pst_macdev, &l_reference0);

    /* �浽device�£���ά���ȡ */
    pst_macdev->st_dbb_env_param_ctx.s_ant_power = (oal_int16)(l_adc_pin - (l_extlna_gain + l_intlna_gain + l_vga_gain + l_reference0));
}


/*****************************************************************************
 �� �� ��  : dmac_dft_get_antenna_power
 ��������  : ��ȡ���߿ڹ���,���㷽���ο�<<Hi1151 V100 DFT������˵����>>
             "3.5.7.3	DBB PHY���߿ڹ����ϱ�"
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_get_antenna_power(mac_device_stru *pst_macdev,
                                                          oal_int32 *pl_antenna_power)
{
    *pl_antenna_power = (oal_int32)pst_macdev->st_dbb_env_param_ctx.s_ant_power;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_chan_stat_result
 ��������  : ��ȡmac��phy�ŵ������Ľ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��3��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_chan_stat_result(
                                    mac_device_stru  *pst_macdev,
                                    oam_stats_dbb_env_param_stru  *pst_dbb_env_param)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    oal_uint32       ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_CH_LOAD_STAT_PERIOD_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_stats_period_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_PRIMARY_20M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri20_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_PRIMARY_40M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri40_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_PRIMARY_80M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri80_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_rx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_TX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_tx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_FREE_ACCUM_WIN_REG, &ul_reg_value);
    pst_dbb_env_param->uc_phy_ch_estimate_time_ms = (oal_uint8)(ul_reg_value & 0xF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_PRI20_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri20_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_PRI40_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri40_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_PHY_PRI80_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri80_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
    oal_uint32       ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_CH_LOAD_STAT_PERIOD_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_stats_period_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_PRIMARY_20M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri20_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_PRIMARY_40M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri40_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_PRIMARY_80M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri80_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_RX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_rx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_TX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_tx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_PHY_FREE_ACCUM_WIN_REG, &ul_reg_value);
    pst_dbb_env_param->uc_phy_ch_estimate_time_ms = (oal_uint8)(ul_reg_value & 0xF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_PHY_PRI20_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri20_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_PHY_PRI40_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri40_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_PHY_PRI80_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri80_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_dbb_env_param
 ��������  : ��ȡͳ�����ݣ��ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_report_dbb_env_param(mac_device_stru *pst_macdev)
{
    oam_stats_dbb_env_param_stru        st_dbb_env_param;
    oal_uint32                          ul_beacon_miss_num;
    oal_uint8                           uc_loop;
    oal_uint32                          ul_clear_reg_val = 0;

    OAL_MEMZERO(&st_dbb_env_param, OAL_SIZEOF(oam_stats_dbb_env_param_stru));

    /* ��ȡ���յ��Ǳ�����ַ��֡��������λ��: ��/s */
    st_dbb_env_param.ul_non_directed_frame_num = (pst_macdev->st_dbb_env_param_ctx.ul_non_directed_frame_num
                                               * DMAC_DFT_REPORT_TO_COLLECT_TIMES) >> 1;
    /* ���㳬ʱ�����ͷǱ�����ַ֡���� */
    pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt = 0;
    pst_macdev->st_dbb_env_param_ctx.ul_non_directed_frame_num = 0;

    /* ��ȡÿһ��ap beacon miss������ */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_BEACON_MISS_NUM_REG, &ul_beacon_miss_num);
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_BEACON_MISS_MAX_NUM_REG, &ul_beacon_miss_num);
#endif
    for (uc_loop = 0; uc_loop < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_loop++)
    {
        DMAC_DFT_AP_BEACON_MISS_MAX_NUM(uc_loop, ul_beacon_miss_num, &st_dbb_env_param.aul_beacon_miss_max_num[uc_loop]);
    }

    /* ����macͳ��ap beacon miss������ */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_COUNTER_CLEAR_REG, &ul_clear_reg_val);
    hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_COUNTER_CLEAR_REG, ul_clear_reg_val | BIT23);
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_COUNTER_CLEAR_REG, &ul_clear_reg_val);
    hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_COUNTER_CLEAR_REG, ul_clear_reg_val | BIT23);
#endif

    /* ��ȡMAC PHY�����ŵ���� */
    dmac_dft_get_chan_stat_result(pst_macdev, &st_dbb_env_param);

    /* �ϱ����� */
    return oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)&st_dbb_env_param,(oal_uint16)OAL_SIZEOF(oam_stats_dbb_env_param_stru), OAM_OTA_TYPE_DBB_ENV_PARAM);

}


/*****************************************************************************
 �� �� ��  : dmac_dft_collect_dbb_env_param_timeout
 ��������  : �տڻ���ά������ɼ���ʱ����ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_collect_dbb_env_param_timeout(oal_void *p_arg)
{
    mac_device_stru         *pst_macdev;
    oal_uint32               ul_reg_tmp_val;

    pst_macdev = (mac_device_stru *)p_arg;

    /* ���ӳ�ʱ�����ļ��� */
    pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt++;

    /* ��������ǵ�98�γ�ʱ��֪ͨDBB MAC��ʼͳ��CCA�����ʣ�DBB PHY��ʼͳ���ŵ����й��� */
    if (DMAC_DFT_REPORT_TO_COLLECT_TIMES - 2 == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* ����DBB MACͳ������,20ms */
        hal_set_ch_statics_period(pst_macdev->pst_device_stru, DMAC_DFT_MAC_CHAN_STAT_PERIOD);

        /* ����DBB PHYͳ������ */
        hal_set_ch_measurement_period(pst_macdev->pst_device_stru, DMAC_DFT_PHY_CHAN_MEASUREMENT_PERIOD);

        /* ʹ��DBB MAC��DBB PHY��ʼͳ�� */
        hal_enable_ch_statics(pst_macdev->pst_device_stru, 1);

        return OAL_SUCC;
    }
    /* ��������ǵ�99�γ�ʱ����ʼ�ռ�һ������(20ms)����(���յ��Ǳ�����ַ��֡����) */
    else if (DMAC_DFT_REPORT_TO_COLLECT_TIMES - 1 == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* ����mac�����ˣ�����20ms */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_FRAMEFILT_REG, ul_reg_tmp_val & (~(BIT11 | BIT13)));
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_RX_FRAMEFILT_REG, ul_reg_tmp_val & (~(BIT11 | BIT13)));
#endif

        return OAL_SUCC;
    }
    else if (DMAC_DFT_REPORT_TO_COLLECT_TIMES == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* ����mac���� */
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)HI1102_MAC_RX_FRAMEFILT_REG, ul_reg_tmp_val | (BIT11 | BIT13));
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)HI1103_MAC_RX_FRAMEFILT_REG, ul_reg_tmp_val | (BIT11 | BIT13));
#endif

        return dmac_dft_report_dbb_env_param(pst_macdev);
    }
    else
    {
        return OAL_SUCC;
    }
}


/*****************************************************************************
 �� �� ��  : dmac_dft_start_report_dbb_env
 ��������  : ��ʼ�ϱ��տڻ�����ά�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_start_report_dbb_env(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_param::vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_param::device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �����ɼ�ά�������ʱ������ʱ����ʱ100�ε�ʱ���ϱ�ά����� */
    FRW_TIMER_CREATE_TIMER(&pst_device->st_dbb_env_param_ctx.st_collect_period_timer,
                           dmac_dft_collect_dbb_env_param_timeout,
                           DMAC_DFT_COLLECT_DBB_ENV_PARAM_TIMEOUT,
                           (oal_void *)pst_device,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           pst_device->ul_core_id);

    pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg = OAL_TRUE;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_stop_report_dbb_env
 ��������  : ֹͣ�ϱ��տڻ������ά�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_stop_report_dbb_env(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_stop_report_param::vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = (mac_device_stru *)mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_stop_report_param::device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ɾ����ʱ�� */
    if (OAL_TRUE == pst_device->st_dbb_env_param_ctx.st_collect_period_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_device->st_dbb_env_param_ctx.st_collect_period_timer);
    }

    /* ��������� */
    pst_device->st_dbb_env_param_ctx.uc_collect_period_cnt = 0;
    pst_device->st_dbb_env_param_ctx.s_ant_power           = 0;
    pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg = 0;
    pst_device->st_dbb_env_param_ctx.ul_non_directed_frame_num = 0;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_dft_mgmt_stat_incr
 ��������  : ����֡ͳ�Ƽ�����1
 �������  : puc_mac_hdr_addr: ֡ͷ��ַ
             en_type         : ͳ������(λ��:���ͣ�������ɣ�����)
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��1��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_mgmt_stat_incr(
                                    mac_device_stru   *pst_mac_dev,
                                    oal_uint8   *puc_mac_hdr_addr,
                                    mac_dev_mgmt_stat_type_enum_uint8 en_type)
{
    oal_uint8           uc_subtype;

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_mac_hdr_addr || OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::param is null. puc_mac_hdr_addr = [%d],\
                       mac_dev = [%d]}", puc_mac_hdr_addr, pst_mac_dev);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_DEV_MGMT_STAT_TYPE_BUTT <= en_type)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::en_type exceeds! en_type = [%d].}", en_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (WLAN_MANAGEMENT == mac_frame_get_type_value(puc_mac_hdr_addr))
    {
        uc_subtype = mac_frame_get_subtype_value(puc_mac_hdr_addr);
        if (uc_subtype >= WLAN_MGMT_SUBTYPE_BUTT)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::uc_subtype exceeds! uc_subtype = [%d].}",
                           uc_subtype);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }

        switch (en_type)
        {
            case MAC_DEV_MGMT_STAT_TYPE_TX:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_tx_mgmt_soft[uc_subtype]);
            break;

            case MAC_DEV_MGMT_STAT_TYPE_RX:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_rx_mgmt[uc_subtype]);
            break;

            case MAC_DEV_MGMT_STAT_TYPE_TX_COMPLETE:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_tx_mgmt_hardware[uc_subtype]);
            break;

            default:
            break;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_machw_stat_info
 ��������  : ��mac�Ĵ�����ȡ�շ�����Ŀͳ��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_get_machw_stat_info(
                                    hal_to_dmac_device_stru   *pst_dev,
                                    oam_stats_machw_stat_stru *pst_machw_stat)
{
#if 0
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev || OAL_PTR_NULL == pst_machw_stat))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_get_machw_stat_info:: pst_dev = [%d], \
                       pst_machw_stat = [%d]}", pst_dev, pst_machw_stat);
        return OAL_ERR_CODE_PTR_NULL;
    }
    hal_dft_get_machw_stat_info(pst_dev,pst_machw_stat);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_print_all_Para
 ��������  : ��־��ʽ�ϱ�ά����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_dft_print_mac_phy_rf(mac_device_stru *pst_mac_dev)
{
    /* ��ӡmacά����Ϣ���ϱ��Ĵ���������*/
    hal_dft_print_machw_stat(pst_mac_dev->pst_device_stru);

    /* ��ӡphyά����Ϣ���ϱ��Ĵ���������*/
    hal_dft_print_phyhw_stat(pst_mac_dev->pst_device_stru);

    /* ��ӡrfά����Ϣ���ϱ��Ĵ���������*/
    hal_dft_print_rfhw_stat(pst_mac_dev->pst_device_stru);
}
#ifdef _PRE_WLAN_FEATURE_STA_PM
/*****************************************************************************
 �� �� ��  : dmac_mac_key_statis_info
 ��������  : mac�ؼ�ͳ����Ϣ
 �������  : pst_dmac_vap,pst_device
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��16��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_mac_key_statis_info(dmac_vap_stru *pst_dmac_vap, mac_device_stru  *pst_device)
{
    hal_mac_key_statis_info_stru      st_mac_key_statis_info;

    if ((WLAN_VAP_MODE_BSS_AP == pst_dmac_vap->st_vap_base_info.en_vap_mode) || (IS_P2P_DEV(&pst_dmac_vap->st_vap_base_info)))
    {
        return;
    }

    hal_get_mac_statistics_data(pst_device->pst_device_stru, &st_mac_key_statis_info);
    st_mac_key_statis_info.ul_tkipccmp_rep_fail_cnt += pst_device->st_mac_key_statis_info.ul_tkipccmp_rep_fail_cnt;
    st_mac_key_statis_info.ul_tx_mpdu_cnt += pst_device->st_mac_key_statis_info.ul_tx_mpdu_cnt;
    st_mac_key_statis_info.ul_rx_passed_mpdu_cnt += pst_device->st_mac_key_statis_info.ul_rx_passed_mpdu_cnt;
    st_mac_key_statis_info.ul_rx_failed_mpdu_cnt += pst_device->st_mac_key_statis_info.ul_rx_failed_mpdu_cnt;
    st_mac_key_statis_info.ul_rx_tkipccmp_mic_fail_cnt += pst_device->st_mac_key_statis_info.ul_rx_tkipccmp_mic_fail_cnt;
    st_mac_key_statis_info.ul_key_search_fail_cnt += pst_device->st_mac_key_statis_info.ul_key_search_fail_cnt;
    st_mac_key_statis_info.ul_phy_rx_dotb_ok_frm_cnt += pst_device->st_mac_key_statis_info.ul_phy_rx_dotb_ok_frm_cnt;
    st_mac_key_statis_info.ul_phy_rx_htvht_ok_frm_cnt += pst_device->st_mac_key_statis_info.ul_phy_rx_htvht_ok_frm_cnt;
    st_mac_key_statis_info.ul_phy_rx_lega_ok_frm_cnt += pst_device->st_mac_key_statis_info.ul_phy_rx_lega_ok_frm_cnt;
    st_mac_key_statis_info.ul_phy_rx_dotb_err_frm_cnt += pst_device->st_mac_key_statis_info.ul_phy_rx_dotb_err_frm_cnt;
    st_mac_key_statis_info.ul_phy_rx_htvht_err_frm_cnt += pst_device->st_mac_key_statis_info.ul_phy_rx_htvht_err_frm_cnt;
    st_mac_key_statis_info.ul_phy_rx_lega_err_frm_cnt += pst_device->st_mac_key_statis_info.ul_phy_rx_lega_err_frm_cnt;

    OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_mac_key_statis_info::tx_mpdu_cnt:[%d],rx_passed_mpdu_cnt[%d],rx_failed_mpdu_cnt[%d],tkipccmp_rep_fail_cnt:[%d],rx_mic_fail_cnt[%d],key_search_fail_cnt[%d].}",6,
                st_mac_key_statis_info.ul_tx_mpdu_cnt,st_mac_key_statis_info.ul_rx_passed_mpdu_cnt,st_mac_key_statis_info.ul_rx_failed_mpdu_cnt,st_mac_key_statis_info.ul_tkipccmp_rep_fail_cnt,st_mac_key_statis_info.ul_rx_tkipccmp_mic_fail_cnt,st_mac_key_statis_info.ul_key_search_fail_cnt);

    OAM_WARNING_LOG_ALTER(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_mac_key_statis_info::phy rx status, rx_dotb_ok_frm_cnt:[%d],rx_htvht_ok_frm_cnt[%d],rx_lega_ok_frm_cnt:[%d],rx_dotb_err_frm_cnt[%d],rx_htvht_err_frm_cnt[%d],rx_lega_err_frm_cnt[%d].}",6,
                st_mac_key_statis_info.ul_phy_rx_dotb_ok_frm_cnt,st_mac_key_statis_info.ul_phy_rx_htvht_ok_frm_cnt,
                st_mac_key_statis_info.ul_phy_rx_lega_ok_frm_cnt,st_mac_key_statis_info.ul_phy_rx_dotb_err_frm_cnt,
                st_mac_key_statis_info.ul_phy_rx_htvht_err_frm_cnt,st_mac_key_statis_info.ul_phy_rx_lega_err_frm_cnt);
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_dft_print_all_Para
 ��������  : ��־��ʽ�ϱ�ά����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��8��
    ��    ��   : z00285102
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_dft_print_all_para(dmac_vap_stru *pst_dmac_sta, oal_bool_enum_uint8 en_all_info)
{
    mac_device_stru                 *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(pst_dmac_sta->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_dmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{dmac_dft_report_all_ota_state::dev is null!}");
        return;
    }

    /*��ӡ��ǰ���ź�״����link_loss����*/
#ifdef _PRE_WLAN_FEATURE_BTCOEX
    OAM_WARNING_LOG2(pst_dmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "now linkloss:bt state is bt_on/off =%d, linkloss_old_bt_on/off =%d",
        pst_dmac_sta->pst_hal_device->st_btcoex_btble_status.un_bt_status.st_bt_status.bit_bt_on,
        pst_dmac_sta->st_linkloss_info.en_old_bt_on);
#endif
    OAM_WARNING_LOG4(pst_dmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "signal = %d,dbac_runing = %d, link_loss_cnt =%d, linkloss_threshold = %d",
        pst_dmac_sta->st_query_stats.ul_signal,
        pst_mac_dev->en_dbac_running,
        pst_dmac_sta->st_linkloss_info.us_link_loss,
        pst_dmac_sta->st_linkloss_info.us_linkloss_threshold);

    /*��ӡ��ǰac������Ϣ*/
    OAM_WARNING_LOG_ALTER(pst_dmac_sta->st_vap_base_info.uc_vap_id, OAM_SF_TX, "{mpdu num:total = %d, be = %d, bk = %d, vi = %d, vo = %d}",
                     5,
                     pst_mac_dev->us_total_mpdu_num,
                     pst_mac_dev->aus_ac_mpdu_num[WLAN_WME_AC_BE],
                     pst_mac_dev->aus_ac_mpdu_num[WLAN_WME_AC_BK],
                     pst_mac_dev->aus_ac_mpdu_num[WLAN_WME_AC_VI],
                     pst_mac_dev->aus_ac_mpdu_num[WLAN_WME_AC_VO]);


#ifdef _PRE_WLAN_FEATURE_STA_PM
    /* mac���ͽ��չؼ���Ϣ��ӡ */
    dmac_mac_key_statis_info(pst_dmac_sta,pst_mac_dev);
#endif


    if (OAL_FALSE == en_all_info)
    {
        return;
    }

#ifdef _PRE_WLAN_FEATURE_STA_PM

    /* Э��Ĺؼ����� */
    dmac_pm_key_info_dump(pst_dmac_sta);

    /* ƽ̨��˯�߼���*/
    PM_WLAN_DumpSleepCnt();
#endif


    /*linkloss��ӡmacά����Ϣ���ϱ��Ĵ���������*/
    hal_dft_print_machw_stat(pst_mac_dev->pst_device_stru);

    /*linkloss��ӡphyά����Ϣ���ϱ��Ĵ���������*/
    hal_dft_print_phyhw_stat(pst_mac_dev->pst_device_stru);

    /*linkloss��ӡrfά����Ϣ���ϱ��Ĵ���������*/
    hal_dft_print_rfhw_stat(pst_mac_dev->pst_device_stru);
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_all_ota_state
 ��������  : ͨ��OTA�ϱ�ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��8��
    ��    ��   : z00285102
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_dft_report_all_ota_state(mac_vap_stru *pst_mac_sta)
{
    mac_device_stru                 *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(pst_mac_sta->uc_device_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG0(pst_mac_sta->uc_vap_id, OAM_SF_ANY, "{dmac_dft_report_all_ota_state::dev is null!}");
        return;
    }

    hal_dft_report_all_reg_state(pst_mac_dev->pst_device_stru);
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_all_para
 ��������  : �쳣�ϱ�ά����Ϣ,������־��ӡ��OTA�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��8��
    ��    ��   : z00285102
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_dft_report_all_para(dmac_vap_stru *pst_dmac_sta,oal_uint8 uc_ota_switch)
{

    /*��ӡά����Ϣ*/
    dmac_dft_print_all_para(pst_dmac_sta, (oal_bool_enum_uint8 )uc_ota_switch);
    /*OTA�ϱ�ά����Ϣ*/
    if(OAL_TRUE == uc_ota_switch)
    {
        dmac_dft_report_all_ota_state(&pst_dmac_sta->st_vap_base_info);
    }
}

//oal_module_symbol(dmac_dft_report_all_para);

/*****************************************************************************
 �� �� ��  : dmac_dft_set_simple_vap_info
 ��������  : ����OTA�ϱ���vap�ṹ����Ϣ
 �������  : dmac_vap_dft_stru *pst_dmac_vap_dft, mac_vap_stru  *pst_mac_vap
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_dft_set_simple_vap_info(dmac_vap_dft_stru *pst_dmac_vap_dft, mac_vap_stru  *pst_mac_vap)
{
    dmac_vap_stru       *pst_dmac_vap;

    if ((OAL_PTR_NULL == pst_dmac_vap_dft) || (OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_set_simple_vap_info:: input params is invalid, [%p] [%p]!}",
                       pst_dmac_vap_dft, pst_mac_vap);
        return;
    }

    /* ��ȡdmac vap */
    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_set_simple_vap_info:: dmac vap[%d] is null!}",
                       pst_mac_vap->uc_vap_id);
        return;
    }

    OAL_MEMZERO(pst_dmac_vap_dft, OAL_SIZEOF(dmac_vap_dft_stru));

    /* dmac_vap_dft_stru�ṹ�帳ֵ */
    /* ���¸�ֵ��mac_vap_stru�ṹ����ȡֵ */
    pst_dmac_vap_dft->uc_vap_id    = pst_mac_vap->uc_vap_id;
    pst_dmac_vap_dft->uc_device_id = pst_mac_vap->uc_device_id;
    pst_dmac_vap_dft->uc_chip_id   = pst_mac_vap->uc_vap_id;
    pst_dmac_vap_dft->en_vap_mode  = pst_mac_vap->en_vap_mode;
    pst_dmac_vap_dft->en_vap_state = pst_mac_vap->en_vap_state;
    pst_dmac_vap_dft->en_protocol  = pst_mac_vap->en_protocol;
    pst_dmac_vap_dft->bit_has_user_bw_limit  = pst_mac_vap->bit_has_user_bw_limit;
    pst_dmac_vap_dft->bit_vap_bw_limit       = pst_mac_vap->bit_vap_bw_limit;
    pst_dmac_vap_dft->uc_tx_power            = pst_mac_vap->uc_tx_power;
    pst_dmac_vap_dft->en_p2p_mode            = pst_mac_vap->en_p2p_mode;
    pst_dmac_vap_dft->uc_p2p_gocl_hal_vap_id = pst_mac_vap->uc_p2p_gocl_hal_vap_id;
    pst_dmac_vap_dft->us_user_nums           = pst_mac_vap->us_user_nums;
    pst_dmac_vap_dft->us_multi_user_idx      = pst_mac_vap->us_multi_user_idx;

    oal_memcopy(pst_dmac_vap_dft->auc_bssid, pst_mac_vap->auc_bssid, WLAN_MAC_ADDR_LEN);
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_channel,
                (oal_uint8 *)&pst_mac_vap->st_channel, OAL_SIZEOF(mac_channel_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_cap_flag,
                (oal_uint8 *)&pst_mac_vap->st_cap_flag, OAL_SIZEOF(mac_cap_flag_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_protection,
                (oal_uint8 *)&pst_mac_vap->st_protection, OAL_SIZEOF(mac_protection_stru));

    /* ���¸�ֵ��dmac_vap_stru�ṹ����ȡֵ */
    pst_dmac_vap_dft->uc_ps_user_num     = pst_dmac_vap->uc_ps_user_num;
    pst_dmac_vap_dft->uc_dtim_count      = pst_dmac_vap->uc_dtim_count;
    pst_dmac_vap_dft->uc_uapsd_max_depth = pst_dmac_vap->uc_uapsd_max_depth;

    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_linkloss_info,
                (oal_uint8 *)&pst_dmac_vap->st_linkloss_info, OAL_SIZEOF(dmac_vap_linkloss_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_tx_alg,
                (oal_uint8 *)&pst_dmac_vap->st_tx_alg, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_tx_data_mcast,
                (oal_uint8 *)&pst_dmac_vap->st_tx_data_mcast, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->st_tx_data_bcast,
                (oal_uint8 *)&pst_dmac_vap->st_tx_data_bcast, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->ast_tx_mgmt_ucast,
                (oal_uint8 *)&pst_dmac_vap->ast_tx_mgmt_ucast, OAL_SIZEOF(hal_tx_txop_alg_stru) * WLAN_BAND_BUTT);
    oal_memcopy((oal_uint8 *)&pst_dmac_vap_dft->ast_tx_mgmt_bmcast,
                (oal_uint8 *)&pst_dmac_vap->ast_tx_mgmt_bmcast, OAL_SIZEOF(hal_tx_txop_alg_stru) * WLAN_BAND_BUTT);

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_dmac_vap_info
 ��������  : OTA�ϱ�dmac vap�ṹ����Ϣ
 �������  : mac_vap_stru  *pst_mac_vap
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_dft_report_dmac_vap_info(mac_vap_stru  *pst_mac_vap)
{
    dmac_vap_dft_stru   st_dmac_vap_dft;

    /* ota�ϱ���dmac_vap_dft_stru�ṹ�帳ֵ */
    dmac_dft_set_simple_vap_info(&st_dmac_vap_dft, pst_mac_vap);

    /* �ϱ�dmac vap��Ϣ */
    oam_report_dft_params(BROADCAST_MACADDR,
                          (oal_uint8 *)&st_dmac_vap_dft,
                          (oal_uint16)OAL_SIZEOF(dmac_vap_dft_stru),
                          OAM_OTA_TYPE_DMAC_VAP);

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_set_simple_user_info
 ��������  : ����OTA�ϱ���dmac user�ṹ����Ϣ
 �������  : dmac_user_dft_stru *pst_dmac_user_dft, dmac_user_stru  *pst_dmac_user
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_dft_set_simple_user_info(dmac_user_dft_stru *pst_dmac_user_dft, dmac_user_stru  *pst_dmac_user)
{
    mac_user_stru       *pst_mac_user;

    if ((OAL_PTR_NULL == pst_dmac_user_dft) || (OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_set_simple_user_info:: input params is invalid, [%p] [%p]!}",
                       pst_dmac_user_dft, pst_dmac_user);
        return;
    }

    OAL_MEMZERO(pst_dmac_user_dft, OAL_SIZEOF(dmac_user_dft_stru));

    /* dmac_user_dft_stru�ṹ�帳ֵ */
    /* ���¸�ֵ��mac_user_stru�ṹ����ȡֵ */
    pst_mac_user = &pst_dmac_user->st_user_base_info;
    pst_dmac_user_dft->us_assoc_id      = pst_mac_user->us_assoc_id;
    pst_dmac_user_dft->uc_device_id     = pst_mac_user->uc_device_id;
    pst_dmac_user_dft->en_is_multi_user = pst_mac_user->en_is_multi_user;
    pst_dmac_user_dft->uc_vap_id        = pst_mac_user->uc_vap_id;
    pst_dmac_user_dft->uc_chip_id       = pst_mac_user->uc_chip_id;
    pst_dmac_user_dft->en_protocol_mode            = pst_mac_user->en_protocol_mode;
    pst_dmac_user_dft->en_avail_protocol_mode      = pst_mac_user->en_avail_protocol_mode;
    pst_dmac_user_dft->en_cur_protocol_mode        = pst_mac_user->en_cur_protocol_mode;
    pst_dmac_user_dft->uc_avail_num_spatial_stream = pst_mac_user->uc_avail_num_spatial_stream;
    pst_dmac_user_dft->uc_num_spatial_stream       = pst_mac_user->uc_num_spatial_stream;
    pst_dmac_user_dft->uc_avail_bf_num_spatial_stream = pst_mac_user->uc_avail_bf_num_spatial_stream;
    pst_dmac_user_dft->en_port_valid      = pst_mac_user->en_port_valid;
    pst_dmac_user_dft->en_bandwidth_cap   = pst_mac_user->en_bandwidth_cap;
    pst_dmac_user_dft->en_avail_bandwidth = pst_mac_user->en_avail_bandwidth;
    pst_dmac_user_dft->en_cur_bandwidth   = pst_mac_user->en_cur_bandwidth;
    pst_dmac_user_dft->en_user_asoc_state = pst_mac_user->en_user_asoc_state;

    oal_memcopy(pst_dmac_user_dft->auc_user_mac_addr, pst_mac_user->auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_avail_op_rates,
                (oal_uint8 *)&pst_mac_user->st_avail_op_rates, OAL_SIZEOF(mac_rate_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_user_tx_info,
                (oal_uint8 *)&pst_mac_user->st_user_tx_info, OAL_SIZEOF(mac_user_tx_param_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_cap_info,
                (oal_uint8 *)&pst_mac_user->st_cap_info, OAL_SIZEOF(mac_user_cap_info_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_ht_hdl,
                (oal_uint8 *)&pst_mac_user->st_ht_hdl, OAL_SIZEOF(mac_user_ht_hdl_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_vht_hdl,
                (oal_uint8 *)&pst_mac_user->st_vht_hdl, OAL_SIZEOF(mac_vht_hdl_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_key_info,
                (oal_uint8 *)&pst_mac_user->st_key_info, OAL_SIZEOF(mac_key_mgmt_stru));

    /* ���¸�ֵ��dmac_user_stru�ṹ����ȡֵ */
    pst_dmac_user_dft->uc_lut_index     = pst_dmac_user->uc_lut_index;
    pst_dmac_user_dft->uc_uapsd_flag    = pst_dmac_user->uc_uapsd_flag;
    pst_dmac_user_dft->uc_max_key_index = pst_dmac_user->uc_max_key_index;

    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_tx_data_mcast,
                (oal_uint8 *)&pst_dmac_user->st_tx_data_mcast, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_tx_data_bcast,
                (oal_uint8 *)&pst_dmac_user->st_tx_data_bcast, OAL_SIZEOF(hal_tx_txop_alg_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_uapsd_status,
                (oal_uint8 *)&pst_dmac_user->st_uapsd_status, OAL_SIZEOF(mac_user_uapsd_status_stru));
    oal_memcopy((oal_uint8 *)&pst_dmac_user_dft->st_user_rate_info,
                (oal_uint8 *)&pst_dmac_user->st_user_rate_info, OAL_SIZEOF(dmac_user_rate_info_stru));

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_dmac_user_info
 ��������  : OTA�ϱ�dmac user�ṹ����Ϣ
 �������  : mac_vap_stru  *pst_mac_vap
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_dft_report_dmac_user_info(mac_vap_stru  *pst_mac_vap)
{
    oal_dlist_head_stru     *pst_entry;
    dmac_user_stru          *pst_dmac_user;
    dmac_user_dft_stru       st_dmac_user_dft;

    /* ����vap�������û� */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
    {
        pst_dmac_user = (dmac_user_stru *)pst_entry;

        /* ota�ϱ���dmac_user_dft_stru�ṹ�帳ֵ */
        dmac_dft_set_simple_user_info(&st_dmac_user_dft, pst_dmac_user);

        oam_report_dft_params(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                              (oal_uint8 *)&st_dmac_user_dft,
                              (oal_uint16)OAL_SIZEOF(dmac_user_dft_stru),
                              OAM_OTA_TYPE_DMAC_USER);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_dmac_event_info
 ��������  : OTA�ϱ�dmac�¼���Ϣ
 �������  : mac_vap_stru  *pst_mac_vap
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_dft_report_dmac_event_info(mac_vap_stru  *pst_mac_vap)
{
    frw_event_mgmt_stru    *pst_event_mgmt;
    frw_event_queue_stru    ast_event_queue[WLAN_FRW_MAX_NUM_CORES * FRW_EVENT_MAX_NUM_QUEUES];
    oal_uint32              ul_core_id;

    /* ����ÿ���˵�ÿ��vap��Ӧ���¼����� */
    for(ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        /* ���ݺ��ҵ���Ӧ�ĺ��ϵ��¼�����ṹ�� */
        pst_event_mgmt = &g_ast_event_manager[ul_core_id];

        oal_memcopy((oal_uint8 *)(&ast_event_queue[ul_core_id * FRW_EVENT_MAX_NUM_QUEUES]),
                    (oal_uint8 *)pst_event_mgmt->st_event_queue, OAL_SIZEOF(pst_event_mgmt->st_event_queue));
    }

    /* �ϱ���ǰ���ڵ������¼�������Ϣ */
    oam_report_dft_params(BROADCAST_MACADDR,
                          (oal_uint8 *)ast_event_queue,
                          (oal_uint16)OAL_SIZEOF(ast_event_queue),
                          OAM_OTA_TYPE_EVENT_QUEUE);

    return;
}

extern oal_netbuf_pool_stru g_st_netbuf_pool;
/*****************************************************************************
 �� �� ��  : dmac_dft_report_dmac_memory_info
 ��������  : OTA�ϱ�dmac�¼���Ϣ
 �������  : mac_vap_stru  *pst_mac_vap
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_dft_report_dmac_memory_info(mac_vap_stru  *pst_mac_vap)
{
    mem_pool_dft_stru          ast_mem_poop_dft_info[OAL_MEM_POOL_ID_BUTT];
    mem_pool_dft_stru         *pst_mem_poop_dft;
    mem_subpool_dft_stru      *pst_mem_subpool_dft;
    oal_mem_pool_stru         *pst_mem_pool;
    oal_mem_subpool_stru      *pst_mem_subpool;
    oal_netbuf_pool_stru      *pst_netbuf_pool;
    oal_netbuf_subpool_stru   *pst_netbuf_subpool;
    oal_uint32                 ul_pool_id = 0;
    oal_uint32                 ul_sub_pool_id = 0;
    oal_uint32                 ul_sub_pool_cnt = 0;

    /* OTA�ϱ��ڴ�ʹ���������Ϣ���� */
    OAL_MEMZERO(ast_mem_poop_dft_info, OAL_SIZEOF(ast_mem_poop_dft_info));

    oal_irq_disable();

    for(ul_pool_id = 0; ul_pool_id < OAL_MEM_POOL_ID_NETBUF; ul_pool_id++)
    {
        /* ��ȡ�ڴ�� */
        pst_mem_pool = oal_mem_get_pool((oal_uint8)ul_pool_id);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mem_pool))
        {
            oal_irq_enable();
            return;
        }

        /* ���ڴ�ص�ʹ��������и�ֵ�������ϱ� */
        pst_mem_poop_dft = &(ast_mem_poop_dft_info[ul_pool_id]);
        pst_mem_poop_dft->uc_pool_id = (oal_uint8)ul_pool_id;
        pst_mem_poop_dft->uc_subpool_cnt   = pst_mem_pool->uc_subpool_cnt;
        pst_mem_poop_dft->us_max_byte_len  = pst_mem_pool->us_max_byte_len;
        pst_mem_poop_dft->us_mem_total_cnt = pst_mem_pool->us_mem_total_cnt;
        pst_mem_poop_dft->us_mem_used_cnt  = pst_mem_pool->us_mem_used_cnt;

        /* ��ȡ��ǰ�ڴ�ص��ӳظ��� */
        ul_sub_pool_cnt = (oal_uint32)pst_mem_poop_dft->uc_subpool_cnt;
        for (ul_sub_pool_id = 0; ul_sub_pool_id < ul_sub_pool_cnt; ul_sub_pool_id++)
        {
            pst_mem_subpool = &(pst_mem_pool->ast_subpool_table[ul_sub_pool_id]);

            /* �����ڴ�ص����ڴ�ص�ʹ��������и�ֵ�������ϱ� */
            pst_mem_subpool_dft = &(pst_mem_poop_dft->ast_subpool_table[ul_sub_pool_id]);
            pst_mem_subpool_dft->uc_sub_pool_id = (oal_uint8)ul_sub_pool_id;
            pst_mem_subpool_dft->us_total_cnt   = pst_mem_subpool->us_total_cnt;
            pst_mem_subpool_dft->us_free_cnt    = pst_mem_subpool->us_free_cnt;
        }

    }

    /* nebuf�ڴ��ʹ�������ֵ�������ϱ� */
    pst_netbuf_pool = &g_st_netbuf_pool;

    pst_mem_poop_dft = &(ast_mem_poop_dft_info[OAL_MEM_POOL_ID_NETBUF]);
    pst_mem_poop_dft->uc_pool_id       = OAL_MEM_POOL_ID_NETBUF;
    pst_mem_poop_dft->us_max_byte_len  = pst_netbuf_pool->us_max_byte_len;
    pst_mem_poop_dft->us_mem_total_cnt = pst_netbuf_pool->us_mem_total_cnt;
    pst_mem_poop_dft->us_mem_used_cnt  = pst_netbuf_pool->us_mem_used_cnt;

    ul_sub_pool_cnt = pst_netbuf_pool->uc_subpool_cnt;
    for (ul_sub_pool_id = 0; ul_sub_pool_id < ul_sub_pool_cnt; ul_sub_pool_id++)
    {
        pst_netbuf_subpool = &(pst_netbuf_pool->ast_subpool_table[ul_sub_pool_id]);

        /* netbuf�ڴ��ӳص�ʹ��������и�ֵ�������ϱ� */
        pst_mem_subpool_dft = &(pst_mem_poop_dft->ast_subpool_table[ul_sub_pool_id]);
        pst_mem_subpool_dft->uc_sub_pool_id = (oal_uint8)ul_sub_pool_id;
        pst_mem_subpool_dft->us_total_cnt   = pst_netbuf_subpool->us_total_cnt;
        pst_mem_subpool_dft->us_free_cnt    = pst_netbuf_subpool->us_free_cnt;
    }

    oal_irq_enable();

    /* �ϱ���ǰ�ڴ�ص�ʹ����� */
    oam_report_dft_params(BROADCAST_MACADDR,
                          (oal_uint8 *)ast_mem_poop_dft_info,
                          (oal_uint16)OAL_SIZEOF(ast_mem_poop_dft_info),
                          OAM_OTA_TYPE_MEMPOOL);

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_mac_hardware_info
 ��������  : OTA�ϱ�macӲ�������Ϣ
 �������  : mac_vap_stru  *pst_mac_vap
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_dft_report_mac_hardware_info(mac_vap_stru  *pst_mac_vap)
{
    hal_device_dft_stru          st_hal_device_info;
    mac_device_stru             *pst_mac_device;
    hal_to_dmac_device_stru     *pst_hal_to_dmac_device;
    oal_uint32                   ul_fake_id = 0;

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY,
                         "{dmac_dft_report_mac_hardware_info:: mac device[%d] is null!}", pst_mac_vap->uc_device_id);
        return;
    }

    pst_hal_to_dmac_device = pst_mac_device->pst_device_stru;

    /* OTA�ϱ�hal device��Ϣ���� */
    OAL_MEMZERO(&st_hal_device_info, OAL_SIZEOF(hal_device_dft_stru));

    /* �ϱ�Ӳ����Ϣ��ֵ */
    st_hal_device_info.uc_chip_id       = pst_hal_to_dmac_device->uc_chip_id;
    st_hal_device_info.uc_device_id     = pst_hal_to_dmac_device->uc_device_id;
    st_hal_device_info.uc_mac_device_id = pst_hal_to_dmac_device->uc_mac_device_id;
    st_hal_device_info.uc_curr_state    = pst_hal_to_dmac_device->uc_curr_state;
    st_hal_device_info.ul_core_id       = pst_hal_to_dmac_device->ul_core_id;

    /* �������͡����ա���ٶ����е���Ϣ������ota�ϱ� */
    oal_memcopy((oal_uint8 *)(st_hal_device_info.ast_rx_dscr_queue),
                (oal_uint8 *)pst_hal_to_dmac_device->ast_rx_dscr_queue, OAL_SIZEOF(st_hal_device_info.ast_rx_dscr_queue));
    oal_memcopy((oal_uint8 *)(st_hal_device_info.ast_tx_dscr_queue),
                (oal_uint8 *)pst_hal_to_dmac_device->ast_tx_dscr_queue, OAL_SIZEOF(st_hal_device_info.ast_tx_dscr_queue));

    /* ������ٶ����е����� */
    for (ul_fake_id = 0; ul_fake_id < HAL_TX_FAKE_QUEUE_NUM; ul_fake_id++)
    {
        oal_memcopy((oal_uint8 *)(st_hal_device_info.ast_tx_dscr_queue_fake[ul_fake_id]),
                    (oal_uint8 *)pst_hal_to_dmac_device->ast_tx_dscr_queue_fake[ul_fake_id],
                    OAL_SIZEOF(hal_tx_dscr_queue_header_stru) * HAL_TX_QUEUE_NUM);
    }

    /* �ϱ���ǰmacӲ�������Ϣ����Ҫ����Ӳ�����͡����ն��С���ٶ�����Ϣ */
    oam_report_dft_params(BROADCAST_MACADDR,
                          (oal_uint8 *)(&st_hal_device_info),
                          (oal_uint16)OAL_SIZEOF(st_hal_device_info),
                          OAM_OTA_TYPE_HARDWARE_INFO);

    return;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_dmac_queue_info
 ��������  : OTA�ϱ����������Ϣ(TID���У�ʡ����б�����Ϣ)
 �������  : mac_vap_stru  *pst_mac_vap
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_dft_report_dmac_queue_info(mac_vap_stru  *pst_mac_vap)
{
    oal_dlist_head_stru                    *pst_entry;
    dmac_user_stru                         *pst_dmac_user;
    dmac_user_queue_info_dft_stru           st_queue_info;

    /* ����vap�������û� */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_mac_vap->st_mac_user_list_head))
    {
        pst_dmac_user = (dmac_user_stru *)pst_entry;

        oal_memcopy((oal_uint8 *)st_queue_info.ast_tx_tid_queue,
                    (oal_uint8 *)pst_dmac_user->ast_tx_tid_queue, OAL_SIZEOF(st_queue_info.ast_tx_tid_queue));

        #ifdef _PRE_WLAN_FEATURE_UAPSD
        oal_memcopy((oal_uint8 *)&st_queue_info.st_uapsd_stru,
                    (oal_uint8 *)&pst_dmac_user->st_uapsd_stru, OAL_SIZEOF(st_queue_info.st_uapsd_stru));
        #endif

        oam_report_dft_params(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                              (oal_uint8 *)&st_queue_info,
                              (oal_uint16)OAL_SIZEOF(st_queue_info),
                              OAM_OTA_TYPE_USER_QUEUE_INFO);
    }

    return;
}

#else
/*****************************************************************************
 �� �� ��  : dmac_dft_set_phy_stat_node
 ��������  : ����phy��ͳ�ƽڵ㣬phy��16��ͳ�ƽڵ㣬����ÿ��ֻ��4�����Թ���
             ����Ҫָ�������Ľڵ��idx,����phy�Ĵ���
 �������  : oam_stats_phy_node_idx_stru: ����phy��ǰʹ�ܵ�ͳ�ƽڵ�idx�Ľṹָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��13��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_set_phy_stat_node(
                                    mac_device_stru *pst_device,
                                    oam_stats_phy_node_idx_stru *pst_phy_node_idx)
{
    oal_uint8           uc_loop;
    oal_uint32          ul_phy_stat_node0_en;
    oal_uint32          ul_phy_stat_node1_en;
    oal_uint32          ul_phy_stat_node2_en;
    oal_uint32          ul_phy_stat_node3_en;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device || OAL_PTR_NULL == pst_phy_node_idx))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_phy_stat_node_init::param is null!}.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_loop = 0; uc_loop < OAM_PHY_STAT_NODE_ENABLED_MAX_NUM; uc_loop++)
    {
        pst_phy_node_idx->auc_node_idx[uc_loop]--;
    }

    /* ����ʹ��֮ǰ���Ȱ�֮ǰ��ͳ��ֵ���㣬��������Ч��ʼ��ͳ��ֵ�������� */
    hal_reg_write(pst_device->pst_device_stru, (oal_uint32)WITP_PHY_STAT_CLR_REG, 0xFFFFFFFF);

    /* ����phy��4��ͳ��ʹ�ܽڵ���Ҫ����ֵ */
    ul_phy_stat_node0_en = BIT0 << (DMAC_DFT_PHY_STAT_NODE_0_BASE + pst_phy_node_idx->auc_node_idx[0]);
    ul_phy_stat_node1_en = BIT0 << (DMAC_DFT_PHY_STAT_NODE_1_BASE + pst_phy_node_idx->auc_node_idx[1]);
    ul_phy_stat_node2_en = BIT0 << (DMAC_DFT_PHY_STAT_NODE_2_BASE + pst_phy_node_idx->auc_node_idx[2]);
    ul_phy_stat_node3_en = BIT0 << (DMAC_DFT_PHY_STAT_NODE_3_BASE + pst_phy_node_idx->auc_node_idx[3]);

    /* ����phyͳ��ʹ�ܽڵ�0��1 */
    hal_reg_write(pst_device->pst_device_stru,
                  (oal_uint32)WITP_PHY_PHY_STA_01_EN_REG,
                  ul_phy_stat_node0_en | ul_phy_stat_node1_en);

    /* ����phyͳ��ʹ�ܽڵ�2��3 */
    hal_reg_write(pst_device->pst_device_stru,
                  (oal_uint32)WITP_PHY_PHY_STA_23_EN_REG,
                  ul_phy_stat_node2_en | ul_phy_stat_node3_en);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_adc_pin
 ��������  : ��ȡphy ADC�ڹ���, ������С��������100����ת����������������ʾ��
             ת����С��.���ڴӼĴ����ж�ȡ������ֵ��λ��0.25dB����˻�Ҫ����4
             ����
 �������  : ul_adc_pin_code_rpt:PHY bank2 ADC_PIN_CODE_RPT�Ĵ�����ֵ,
                                 AGC ADC�ڹ����������λֵ�ϱ�
 �������  : pl_adc_pin:phy ADC�ڹ���
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��25��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_adc_pin(oal_uint32 ul_adc_pin_code_rpt,
                                                  oal_int32 *pl_adc_pin)
{
    oal_int32       l_adc_pin_phy;       /* ��phy�Ĵ����ж�ȡ������adc�ڹ���ֵ����ʱ��λ��0.25dB */

    /* ul_adc_pin_code_rpt�ĵ�9bitֵ��ADC�ڹ��ʣ��з���������λ0.25dB,���ݷ���λ
       ��ȷ����ʵֵ
    */
    if (BIT8 != (BIT8 & ul_adc_pin_code_rpt))
    {
        /* ������ֱ��ת��Ϊ��λΪ1dB��ֵ,Ȼ�����100��֤����������������� */
        *pl_adc_pin = (ul_adc_pin_code_rpt & 0x1FF) * 100 / 4;
    }
    else
    {
         /*lint -e701*//*lint -e702*/ /* ע�͵��з�������λ���� */
        l_adc_pin_phy = (oal_int32)ul_adc_pin_code_rpt;
        l_adc_pin_phy = (oal_int32)(l_adc_pin_phy << 23);
        l_adc_pin_phy = (oal_int32)(l_adc_pin_phy >> 23);
        /*lint +e701*//*lint +e702*/

        *pl_adc_pin = l_adc_pin_phy * 100 / 4;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_extlna_gain
 ��������  : ��ȡ����LNA����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_extlna_gain(mac_device_stru *pst_macdev,
                                                      oal_uint32 ul_adc_pin_code_rpt,
                                                      oal_int32 *pl_extlna_gain)
{
    oal_uint32          ul_extlna_gain0_cfg = 0;
    oal_uint32          ul_extlna_gain1_cfg = 0;
    oal_int32           l_extlna_gain0_cfg;
    oal_int32           l_extlna_gain1_cfg;
    oal_uint8           uc_lna_code_out_3;
    oal_int32           l_extlna_gain;

    /* ��ȡ����LNAΪ0��1ʱ���� */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_EXTLNA_GAIN0_CFG_REG, &ul_extlna_gain0_cfg);
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_EXTLNA_GAIN1_CFG_REG, &ul_extlna_gain1_cfg);

    /*lint -e701*//*lint -e702*/
    /* ��������LNAΪ0ʱ������ֵ */
    l_extlna_gain0_cfg = (oal_int32)(ul_extlna_gain0_cfg);
    l_extlna_gain0_cfg = (oal_int32)(l_extlna_gain0_cfg << 22);
    l_extlna_gain0_cfg = (oal_int32)(l_extlna_gain0_cfg >> 22);

    /* ��������LNAΪ1ʱ������ֵ */
    l_extlna_gain1_cfg = (oal_int32)(ul_extlna_gain1_cfg);
    l_extlna_gain1_cfg = (oal_int32)(l_extlna_gain1_cfg << 22);
    l_extlna_gain1_cfg = (oal_int32)(l_extlna_gain1_cfg >> 22);
    /*lint +e701*//*lint +e702*/

    /* ��ȡ����LNA��λֵ */
    uc_lna_code_out_3 = (ul_adc_pin_code_rpt & BIT15) >> 15;

    /* ��������LNA���� */
    l_extlna_gain = (uc_lna_code_out_3 == 0) ? l_extlna_gain0_cfg : l_extlna_gain1_cfg;

    *pl_extlna_gain = l_extlna_gain * 100 / 4;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_intlna_gain
 ��������  : ��ȡ����LNA����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_intlna_gain(oal_uint32 ul_adc_pin_code_rpt,
                                                      oal_int32 *pl_intlna_gain)
{
    oal_uint8       uc_lna_code_out_0_2;

    /* ��ȡ����LNA��λֵ������������LNA���� */
    uc_lna_code_out_0_2 = (ul_adc_pin_code_rpt & (BIT12 | BIT13 | BIT14)) >> 12;

    if (0 == uc_lna_code_out_0_2 || DMAC_DFT_PHY_INTLAN_GAIN_NUM <= uc_lna_code_out_0_2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dft_get_intlna_gain:: lna_code_out[2:0] val=[%d] invalid.}",
                         uc_lna_code_out_0_2);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    *pl_intlna_gain = g_al_intlna_gain[uc_lna_code_out_0_2];

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_vga_gain
 ��������  : �����ȡvga����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_vga_gain(oal_uint32 ul_adc_pin_code_rpt,
                                                   oal_int32 *pl_vga_gain)
{
    oal_uint8       uc_vga_coude_out_0_4;

    /* ��ȡVGA��λֵ��������VGA���� */
    uc_vga_coude_out_0_4 = (ul_adc_pin_code_rpt & (BIT16 | BIT17 | BIT18 | BIT19 | BIT20)) >> 16;

    if (DMAC_DFT_PHY_VGA_GAIN_NUM <= uc_vga_coude_out_0_4)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{dmac_dft_get_vga_gain:: vga_coude_out[4:0] val=[%d] invalid.}",
                         uc_vga_coude_out_0_4);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    *pl_vga_gain = g_al_vga_gain[uc_vga_coude_out_0_4];

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_reference0
 ��������  : ��ȡ�������߿ڹ��ʲο�ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��26��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_reference0(mac_device_stru *pst_macdev,
                                                     oal_int32 *pl_reference0)
{
    oal_uint32      ul_cfg_power0_ref = 0;
    oal_int32       l_cfg_power0_ref;

    /* ����������߿ڹ��ʼ���ο�ֵ */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_POWER0_REF_REG, &ul_cfg_power0_ref);

    /*lint -e701*//*lint -e702*/
    l_cfg_power0_ref = (oal_int32)ul_cfg_power0_ref;
    l_cfg_power0_ref = (oal_int32)(l_cfg_power0_ref << 24);
    l_cfg_power0_ref = (oal_int32)(l_cfg_power0_ref >> 24);
    /*lint +e701*//*lint +e702*/

    *pl_reference0 = l_cfg_power0_ref * 100 / 4;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_calcu_antenna_power
 ��������  : tbtt�жϵ�����ʱ�򣬼������߿ڹ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��29��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_dft_calcu_antenna_power(mac_device_stru *pst_macdev)
{
    oal_uint32          ul_adc_pin_code_rpt;       /* PHY bank2 ADC_PIN_CODE_RPT�Ĵ�����ֵ */
    oal_int32           l_adc_pin = 0;
    oal_int32           l_extlna_gain = 0;             /* ����LNA���� */
    oal_int32           l_intlna_gain = 0;             /* ����LNA���� */
    oal_int32           l_vga_gain = 0;                /* VGA���� */
    oal_int32           l_reference0 = 0;              /* �������߿ڹ��ʼ���ο�ֵ */

    /* phy�ṩ�ĵ�����㹫ʽ: adc_pin - (extlna_gain + intlna_gain + vga_gain + reference_0)*/

    /* ��ȡPHY AGC ADC�ڹ����������λֵ */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_ADC_PIN_CODE_RPT, &ul_adc_pin_code_rpt);

    /* ��ȡADC�ڹ��� */
    dmac_dft_get_adc_pin(ul_adc_pin_code_rpt, &l_adc_pin);

    /* ��ȡ����LNA���� */
    dmac_dft_get_extlna_gain(pst_macdev, ul_adc_pin_code_rpt, &l_extlna_gain);

    /* ��ȡ����LNA���� */
    dmac_dft_get_intlna_gain(ul_adc_pin_code_rpt, &l_intlna_gain);

    /* ��ȡVGA���� */
    dmac_dft_get_vga_gain(ul_adc_pin_code_rpt, &l_vga_gain);

    /* ��ȡ�������߿ڹ��ʼ���ο�ֵ */
    dmac_dft_get_reference0(pst_macdev, &l_reference0);

    /* �浽device�£���ά���ȡ */
    pst_macdev->st_dbb_env_param_ctx.s_ant_power = (oal_int16)(l_adc_pin - (l_extlna_gain + l_intlna_gain + l_vga_gain + l_reference0));
}


/*****************************************************************************
 �� �� ��  : dmac_dft_get_antenna_power
 ��������  : ��ȡ���߿ڹ���,���㷽���ο�<<Hi1151 V100 DFT������˵����>>
             "3.5.7.3	DBB PHY���߿ڹ����ϱ�"
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_get_antenna_power(mac_device_stru *pst_macdev,
                                                          oal_int32 *pl_antenna_power)
{
    *pl_antenna_power = (oal_int32)pst_macdev->st_dbb_env_param_ctx.s_ant_power;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_chan_stat_result
 ��������  : ��ȡmac��phy�ŵ������Ľ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��3��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_get_chan_stat_result(
                                    mac_device_stru  *pst_macdev,
                                    oam_stats_dbb_env_param_stru  *pst_dbb_env_param)
{
    oal_uint32       ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_CH_LOAD_STAT_PERIOD_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_stats_period_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_PRIMARY_20M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri20_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_PRIMARY_40M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri40_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_PRIMARY_80M_IDLE_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_pri80_free_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_rx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_TX_PROGRESS_COUNT_REG, &ul_reg_value);
    pst_dbb_env_param->us_mac_ch_tx_time_us = (oal_uint16)ul_reg_value;

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_FREE_ACCUM_WIN_REG, &ul_reg_value);
    pst_dbb_env_param->uc_phy_ch_estimate_time_ms = (oal_uint8)(ul_reg_value & 0xF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_PRI20_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri20_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_PRI40_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri40_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PHY_PRI80_IDLE_PWR_REG, &ul_reg_value);
    pst_dbb_env_param->c_phy_pri80_idle_power_dBm = (oal_int8)(ul_reg_value & 0xFF);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_dbb_env_param
 ��������  : ��ȡͳ�����ݣ��ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_report_dbb_env_param(mac_device_stru *pst_macdev)
{
    oam_stats_dbb_env_param_stru        st_dbb_env_param;
    oal_uint32                          ul_beacon_miss_num;
    oal_uint8                           uc_loop;
    oal_uint32                          ul_clear_reg_val = 0;

    OAL_MEMZERO(&st_dbb_env_param, OAL_SIZEOF(oam_stats_dbb_env_param_stru));

    /* ��ȡ���յ��Ǳ�����ַ��֡��������λ��: ��/s */
    st_dbb_env_param.ul_non_directed_frame_num = (pst_macdev->st_dbb_env_param_ctx.ul_non_directed_frame_num
                                               * DMAC_DFT_REPORT_TO_COLLECT_TIMES) >> 1;
    /* ���㳬ʱ�����ͷǱ�����ַ֡���� */
    pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt = 0;
    pst_macdev->st_dbb_env_param_ctx.ul_non_directed_frame_num = 0;

    /* ��ȡÿһ��ap beacon miss������ */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_BEACON_MISS_NUM_REG, &ul_beacon_miss_num);
    for (uc_loop = 0; uc_loop < WLAN_SERVICE_AP_MAX_NUM_PER_DEVICE; uc_loop++)
    {
        DMAC_DFT_AP_BEACON_MISS_MAX_NUM(uc_loop, ul_beacon_miss_num, &st_dbb_env_param.aul_beacon_miss_max_num[uc_loop]);
    }

    /* ����macͳ��ap beacon miss������ */
    hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_COUNTER_CLEAR_REG, &ul_clear_reg_val);
    hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_COUNTER_CLEAR_REG, ul_clear_reg_val | BIT23);

    /* ��ȡMAC PHY�����ŵ���� */
    dmac_dft_get_chan_stat_result(pst_macdev, &st_dbb_env_param);

    /* �ϱ����� */
    return oam_report_dft_params(BROADCAST_MACADDR, (oal_uint8 *)&st_dbb_env_param,(oal_uint16)OAL_SIZEOF(oam_stats_dbb_env_param_stru), OAM_OTA_TYPE_DBB_ENV_PARAM);

}


/*****************************************************************************
 �� �� ��  : dmac_dft_collect_dbb_env_param_timeout
 ��������  : �տڻ���ά������ɼ���ʱ����ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_collect_dbb_env_param_timeout(oal_void *p_arg)
{
    mac_device_stru         *pst_macdev;
    oal_uint32               ul_reg_tmp_val;

    pst_macdev = (mac_device_stru *)p_arg;

    /* ���ӳ�ʱ�����ļ��� */
    pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt++;

    /* ��������ǵ�98�γ�ʱ��֪ͨDBB MAC��ʼͳ��CCA�����ʣ�DBB PHY��ʼͳ���ŵ����й��� */
    if (DMAC_DFT_REPORT_TO_COLLECT_TIMES - 2 == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* ����DBB MACͳ������,20ms */
        hal_set_ch_statics_period(pst_macdev->pst_device_stru, DMAC_DFT_MAC_CHAN_STAT_PERIOD);

        /* ����DBB PHYͳ������ */
        hal_set_ch_measurement_period(pst_macdev->pst_device_stru, DMAC_DFT_PHY_CHAN_MEASUREMENT_PERIOD);

        /* ʹ��DBB MAC��DBB PHY��ʼͳ�� */
        hal_enable_ch_statics(pst_macdev->pst_device_stru, 1);

        return OAL_SUCC;
    }
    /* ��������ǵ�99�γ�ʱ����ʼ�ռ�һ������(20ms)����(���յ��Ǳ�����ַ��֡����) */
    else if (DMAC_DFT_REPORT_TO_COLLECT_TIMES - 1 == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* ����mac�����ˣ�����20ms */
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_FRAMEFILT_REG, ul_reg_tmp_val & (~(BIT11 | BIT13)));

        return OAL_SUCC;
    }
    else if (DMAC_DFT_REPORT_TO_COLLECT_TIMES == pst_macdev->st_dbb_env_param_ctx.uc_collect_period_cnt)
    {
        /* ����mac���� */
        hal_reg_info(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_FRAMEFILT_REG, &ul_reg_tmp_val);
        hal_reg_write(pst_macdev->pst_device_stru, (oal_uint32)WITP_PA_RX_FRAMEFILT_REG, ul_reg_tmp_val | (BIT11 | BIT13));

        return dmac_dft_report_dbb_env_param(pst_macdev);
    }
    else
    {
        return OAL_SUCC;
    }
}


/*****************************************************************************
 �� �� ��  : dmac_dft_start_report_dbb_env
 ��������  : ��ʼ�ϱ��տڻ�����ά�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_start_report_dbb_env(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_device;

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_param::device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �����ɼ�ά�������ʱ������ʱ����ʱ100�ε�ʱ���ϱ�ά����� */
    FRW_TIMER_CREATE_TIMER(&pst_device->st_dbb_env_param_ctx.st_collect_period_timer,
                           dmac_dft_collect_dbb_env_param_timeout,
                           DMAC_DFT_COLLECT_DBB_ENV_PARAM_TIMEOUT,
                           (oal_void *)pst_device,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           pst_device->ul_core_id);

    pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg = OAL_TRUE;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_stop_report_dbb_env
 ��������  : ֹͣ�ϱ��տڻ������ά�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_stop_report_dbb_env(mac_vap_stru *pst_mac_vap)
{
    mac_device_stru *pst_device;

    pst_device = (mac_device_stru *)mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_stop_report_param::device is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ɾ����ʱ�� */
    if (OAL_TRUE == pst_device->st_dbb_env_param_ctx.st_collect_period_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_device->st_dbb_env_param_ctx.st_collect_period_timer);
    }

    /* ��������� */
    pst_device->st_dbb_env_param_ctx.uc_collect_period_cnt = 0;
    pst_device->st_dbb_env_param_ctx.s_ant_power           = 0;
    pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg = 0;
    pst_device->st_dbb_env_param_ctx.ul_non_directed_frame_num = 0;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_clear_usr_queue_stat
 ��������  : �����û�����ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_clear_usr_queue_stat(dmac_user_stru  *pst_dmac_user)
{
    oal_uint8    uc_tid_no;

    /* ������ܶ���ͳ����Ϣ */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user->st_ps_structure.pst_psm_stats
        || OAL_PTR_NULL == pst_dmac_user->st_uapsd_stru.pst_uapsd_statis))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_clear_usr_queue_stat::ps stats is null! psm=[%d],uapsd=[%d].}",
                       (oal_uint32)pst_dmac_user->st_ps_structure.pst_psm_stats,
                       (oal_uint32)pst_dmac_user->st_uapsd_stru.pst_uapsd_statis);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(pst_dmac_user->st_ps_structure.pst_psm_stats, OAL_SIZEOF(dmac_user_psm_stats_stru));
    OAL_MEMZERO(pst_dmac_user->st_uapsd_stru.pst_uapsd_statis, OAL_SIZEOF(dmac_usr_uapsd_statis_stru));

    /* ����tid����ͳ����Ϣ */
    for (uc_tid_no = 0; uc_tid_no < WLAN_TID_MAX_NUM; uc_tid_no++)
    {
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user->ast_tx_tid_queue[uc_tid_no].pst_tid_stats))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_clear_usr_queue_stat::pst_tid_stats is null.tid_no=[%d].}",
                           uc_tid_no);
            return OAL_ERR_CODE_PTR_NULL;
        }

        OAL_MEMZERO(pst_dmac_user->ast_tx_tid_queue[uc_tid_no].pst_tid_stats, OAL_SIZEOF(dmac_tid_stats_stru));
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_usr_queue_stat
 ��������  : �ϱ��û�����ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_report_usr_queue_stat(dmac_user_stru  *pst_dmac_user)
{
    oam_stats_usr_queue_stat_stru       st_usr_queue_stats;
    oal_uint8                           uc_tid_no;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user->st_ps_structure.pst_psm_stats
        || OAL_PTR_NULL == pst_dmac_user->st_uapsd_stru.pst_uapsd_statis))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_report_usr_queue_stat::ps stats is null! psm=[%d],uapsd=[%d].}",
                       (oal_uint32)pst_dmac_user->st_ps_structure.pst_psm_stats,
                       (oal_uint32)pst_dmac_user->st_uapsd_stru.pst_uapsd_statis);
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(&st_usr_queue_stats, OAL_SIZEOF(oam_stats_usr_queue_stat_stru));

    /* ��ȡ�û�uapsd�����µ�ͳ����Ϣ */
    oal_memcopy(st_usr_queue_stats.aul_uapsd_stat,
                pst_dmac_user->st_uapsd_stru.pst_uapsd_statis,
                OAL_SIZEOF(oal_uint32) * OAM_UAPSD_STAT_CNT);

    /* ��ȡ�û�psm�����µ�ͳ����Ϣ */
    oal_memcopy(st_usr_queue_stats.aul_psm_stat,
                pst_dmac_user->st_ps_structure.pst_psm_stats,
                OAL_SIZEOF(oal_uint32) * OAM_PSM_STAT_CNT);

    /* ��ȡ�û�tid�����µ�ͳ����Ϣ */
    for (uc_tid_no = 0; uc_tid_no < WLAN_TID_MAX_NUM; uc_tid_no++)
    {
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user->ast_tx_tid_queue[uc_tid_no].pst_tid_stats))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_report_usr_queue_stat::tid_stats is null! tid_no=[%d].}", uc_tid_no);
            return OAL_ERR_CODE_PTR_NULL;
        }
        oal_memcopy(&st_usr_queue_stats.aul_tid_stat[uc_tid_no][0],
                    pst_dmac_user->ast_tx_tid_queue[uc_tid_no].pst_tid_stats,
                    OAL_SIZEOF(oal_uint32) * OAM_TID_STAT_CNT);
    }

    return oam_report_dft_params(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                                 (oal_uint8 *)&st_usr_queue_stats,
                                 (oal_uint16)OAL_SIZEOF(oam_stats_usr_queue_stat_stru),
                                 OAM_OTA_TYPE_USR_QUEUE_STAT);
}

/*****************************************************************************
 �� �� ��  : dmac_dft_mgmt_stat_incr
 ��������  : ����֡ͳ�Ƽ�����1
 �������  : puc_mac_hdr_addr: ֡ͷ��ַ
             en_type         : ͳ������(λ��:���ͣ�������ɣ�����)
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��1��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_mgmt_stat_incr(
                                    mac_device_stru   *pst_mac_dev,
                                    oal_uint8   *puc_mac_hdr_addr,
                                    mac_dev_mgmt_stat_type_enum_uint8 en_type)
{
    oal_uint8           uc_subtype;

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_mac_hdr_addr || OAL_PTR_NULL == pst_mac_dev))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::param is null. puc_mac_hdr_addr = [%d],\
                       mac_dev = [%d]}", puc_mac_hdr_addr, pst_mac_dev);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAC_DEV_MGMT_STAT_TYPE_BUTT <= en_type)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::en_type exceeds! en_type = [%d].}", en_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    if (WLAN_MANAGEMENT == mac_frame_get_type_value(puc_mac_hdr_addr))
    {
        uc_subtype = mac_frame_get_subtype_value(puc_mac_hdr_addr);
        if (uc_subtype >= WLAN_MGMT_SUBTYPE_BUTT)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_dft_mgmt_stat_incr::uc_subtype exceeds! uc_subtype = [%d].}",
                           uc_subtype);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }

        switch (en_type)
        {
            case MAC_DEV_MGMT_STAT_TYPE_TX:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_tx_mgmt_soft[uc_subtype]);
            break;

            case MAC_DEV_MGMT_STAT_TYPE_RX:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_rx_mgmt[uc_subtype]);
            break;

            case MAC_DEV_MGMT_STAT_TYPE_TX_COMPLETE:
                DMAC_DFT_MGMT_STAT_INCR(pst_mac_dev->st_mgmt_stat.aul_tx_mgmt_hardware[uc_subtype]);
            break;

            default:
            break;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_get_machw_stat_info
 ��������  : ��mac�Ĵ�����ȡ�շ�����Ŀͳ��ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��4��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_get_machw_stat_info(
                                    hal_to_dmac_device_stru   *pst_dev,
                                    oam_stats_machw_stat_stru *pst_machw_stat)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev || OAL_PTR_NULL == pst_machw_stat))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{dmac_dft_get_machw_stat_info:: pst_dev = [%d], \
                       pst_machw_stat = [%d]}", pst_dev, pst_machw_stat);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ζ�ȡMAC ���շ�����Ŀͳ�ƼĴ��� */
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_AMPDU_COUNT_REG, &pst_machw_stat->ul_machw_rx_ampdu_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PASSED_MPDU_IN_AMPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_passed_mpdu_in_ampdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_FAILED_MPDU_IN_AMPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_failed_mpdu_in_ampdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_OCTECTS_IN_AMPDU_REG, &pst_machw_stat->ul_machw_rx_octects_in_ampdu);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_DELIMIT_FAIL_COUNT_REG, &pst_machw_stat->ul_machw_rx_delimit_fail_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_DUP_MPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_dup_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PASSED_MPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_passed_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_FAILED_MPDU_CNT_REG, &pst_machw_stat->ul_machw_rx_failed_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_BCN_CNT_REG, &pst_machw_stat->ul_machw_rx_bcn_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PHY_ERR_MAC_PASSED_CNT_REG, &pst_machw_stat->ul_machw_rx_phy_err_mac_passed_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PHY_LONGER_ERR_CNT_REG, &pst_machw_stat->ul_machw_rx_phy_longer_err_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_PHY_SHORTER_ERR_CNT_REG, &pst_machw_stat->ul_machw_rx_phy_shorter_err_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_RX_FILTERED_CNT_REG, &pst_machw_stat->ul_machw_rx_filtered_cnt);

    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_HI_PRI_MPDU_CNT_REG, &pst_machw_stat->ul_machw_tx_hi_pri_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_NORMAL_PRI_MPDU_CNT_REG, &pst_machw_stat->ul_machw_tx_normal_pri_mpdu_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_AMPDU_COUNT_REG, &pst_machw_stat->ul_machw_tx_ampdu_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_MPDU_INAMPDU_COUNT_REG, &pst_machw_stat->ul_machw_tx_mpdu_inampdu_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_OCTECTS_IN_AMPDU_REG, &pst_machw_stat->ul_machw_tx_octects_in_ampdu);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_TX_BCN_COUNT_REG, &pst_machw_stat->ul_machw_tx_bcn_count);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_NORMAL_PRI_RETRY_CNT_REG, &pst_machw_stat->ul_machw_tx_normal_pri_retry_cnt);
    hal_reg_info(pst_dev, (oal_uint32)WITP_PA_HI_PRI_RETRY_CNT_REG, &pst_machw_stat->ul_machw_tx_hi_pri_retry_cnt);

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_dft_report_all_ota_state
 ��������  : ͨ��OTA�ϱ�ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��8��
    ��    ��   : z00285102
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_dft_report_all_ota_state(mac_vap_stru *pst_mac_sta)
{
}

oal_void dmac_dft_report_all_para(dmac_vap_stru *pst_dmac_sta,oal_uint8 uc_ota_switch)
{
    /* TBD */
}

#endif
#if 0
/*****************************************************************************
 �� �� ��  : dmac_dft_report_vap_stat
 ��������  : �����ϱ�vap����ͳ����Ϣ��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_dft_report_vap_stat(oal_void *p_arg)
{
    mac_vap_stru            *pst_mac_vap;
    oam_stats_vap_stat_stru  st_vap_dft_stats;
    oal_uint8                auc_user_macaddr[WLAN_MAC_ADDR_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

    pst_mac_vap = (mac_vap_stru  *)p_arg;

    OAL_MEMZERO(&st_vap_dft_stats, OAL_SIZEOF(oam_stats_vap_stat_stru));

    /* ��ֹͣͳ�� */
    pst_mac_vap->st_vap_dft.ul_flg = OAL_FALSE;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap->st_vap_dft.pst_vap_dft_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_report_vap_stat:: vap_dft_stats is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(&st_vap_dft_stats,
                pst_mac_vap->st_vap_dft.pst_vap_dft_stats,
                OAL_SIZEOF(mac_vap_dft_stats_stru));
    OAL_MEMZERO(pst_mac_vap->st_vap_dft.pst_vap_dft_stats, OAL_SIZEOF(mac_vap_dft_stats_stru));

    /* ����5��ƽ������,��λ�� kbps���ϱ�������2s */
    st_vap_dft_stats.ul_lan_tx_rate = st_vap_dft_stats.ul_lan_tx_bytes / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;
    st_vap_dft_stats.ul_drv_tx_rate = st_vap_dft_stats.ul_drv_tx_bytes / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;
    st_vap_dft_stats.ul_hw_tx_rate  = st_vap_dft_stats.ul_hw_tx_bytes  / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;
    st_vap_dft_stats.ul_drv_rx_rate = st_vap_dft_stats.ul_drv_rx_bytes / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;
    st_vap_dft_stats.ul_lan_rx_rate = st_vap_dft_stats.ul_lan_rx_bytes / DMAC_DFT_VAP_STAT_RATE_TO_KBPS;

    pst_mac_vap->st_vap_dft.ul_flg = OAL_TRUE;

    return oam_report_dft_params(auc_user_macaddr, (oal_uint8 *)&st_vap_dft_stats, OAM_OTA_TYPE_VAP_STAT);
}


/*****************************************************************************
 �� �� ��  : dmac_dft_start_report_vap_stat
 ��������  : ��ʼͳ��vap����ͳ����Ϣ����������ʱ�������ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_start_report_vap_stat(mac_vap_stru *pst_mac_vap)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_vap_stat::vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ñ�־λ��ҵ�����̿�ʼͳ�� */
    pst_mac_vap->st_vap_dft.ul_flg = 1;

    /* �����ڴ� */
    pst_mac_vap->st_vap_dft.pst_vap_dft_stats = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,
                                                              OAL_SIZEOF(mac_vap_dft_stats_stru),
                                                              OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap->st_vap_dft.pst_vap_dft_stats))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_vap_stat::alloc fail.}");
        pst_mac_vap->st_vap_dft.ul_flg = 0;

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }
    OAL_MEMZERO(pst_mac_vap->st_vap_dft.pst_vap_dft_stats, OAL_SIZEOF(mac_vap_dft_stats_stru));

    /* ���������ϱ���ʱ�� */
    FRW_TIMER_CREATE_TIMER(&pst_mac_vap->st_vap_dft.st_vap_dft_timer,
                           dmac_dft_report_vap_stat,
                           DMAC_DFT_REPORT_VAP_STAT_TIMEOUT,
                           (oal_void *)pst_mac_vap,
                           OAL_TRUE,
                           OAM_MODULE_ID_DMAC,
                           pst_mac_vap->ul_core_id);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_stop_report_vap_stat
 ��������  : ֹͣ�ϱ�vap����ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_stop_report_vap_stat(mac_vap_stru *pst_mac_vap)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_start_report_vap_stat::vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    return mac_vap_dft_stat_clear(pst_mac_vap);
}
#endif
#endif
#ifdef  _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : dmac_dft_report_all_ampdu_stat
 ��������  : �ϱ���������ĳһ���û�����tid��ampduҵ������ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��27��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_report_all_ampdu_stat(dmac_user_stru  *pst_dmac_user,
                                                   oal_uint8        uc_param)
{
    oal_uint8                  uc_tid_no;
    dmac_tid_stru             *pst_tid;
    oam_stats_ampdu_stat_stru  st_ampdu_stat;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_user))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_report_all_ampdu_stat::dmac_user is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == uc_param)
    {
        for (uc_tid_no = 0; uc_tid_no < WLAN_TID_MAX_NUM; uc_tid_no++)
        {
            pst_tid = &pst_dmac_user->ast_tx_tid_queue[uc_tid_no];

            if (OAL_LIKELY(OAL_PTR_NULL != pst_tid->pst_tid_ampdu_stat))
            {
                OAL_MEMZERO(&st_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));
                oal_memcopy(&st_ampdu_stat, pst_tid->pst_tid_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));

                oam_report_dft_params(pst_dmac_user->st_user_base_info.auc_user_mac_addr,
                                      (oal_uint8 *)&st_ampdu_stat,
                                      (oal_uint16)OAL_SIZEOF(oam_stats_ampdu_stat_stru),
                                      OAM_OTA_TYPE_AMPDU_STAT);
            }

        }
    }
    else
    {
        for (uc_tid_no = 0; uc_tid_no < WLAN_TID_MAX_NUM; uc_tid_no++)
        {
            pst_tid = &pst_dmac_user->ast_tx_tid_queue[uc_tid_no];

            if (OAL_LIKELY(OAL_PTR_NULL != pst_tid->pst_tid_ampdu_stat))
            {
                OAL_MEMZERO(pst_tid->pst_tid_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));
            }

        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_dft_report_ampdu_stat
 ��������  : �ϱ���ȡ����ĳһ��tid��ampduҵ������ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��27��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_dft_report_ampdu_stat(dmac_tid_stru  *pst_tid,
                                               oal_uint8      auc_macaddr[],
                                               oal_uint8      uc_param)
{
    oam_stats_ampdu_stat_stru  st_ampdu_stat;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_tid))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_dft_report_ampdu_stat::pst_tid is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_TRUE == uc_param)
    {
        if (OAL_LIKELY(OAL_PTR_NULL != pst_tid->pst_tid_ampdu_stat))
        {
            OAL_MEMZERO(&st_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));
            oal_memcopy(&st_ampdu_stat, pst_tid->pst_tid_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));

            oam_report_dft_params(auc_macaddr,
                                  (oal_uint8 *)&st_ampdu_stat,
                                  (oal_uint16)OAL_SIZEOF(oam_stats_ampdu_stat_stru),
                                  OAM_OTA_TYPE_AMPDU_STAT);
        }


    }
    else
    {
        if (OAL_LIKELY(OAL_PTR_NULL != pst_tid->pst_tid_ampdu_stat))
        {
            OAL_MEMZERO(pst_tid->pst_tid_ampdu_stat, OAL_SIZEOF(oam_stats_ampdu_stat_stru));
        }
    }

    return OAL_SUCC;
}

#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

