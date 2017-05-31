/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_txopps.c
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2014��7��16��
  ����޸�   :
  ��������   : 11acЭ���TXOP PS������ؽṹ�����ʵ���ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��16��
    ��    ��   : z00237171
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_TXOPPS

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oam_ext_if.h"
#include "hal_ext_if.h"
#include "mac_resource.h"
#include "mac_device.h"
#include "dmac_txopps.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_TXOPPS_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_txopps_set_machw_en_sta
 ��������  : staģʽ������mac txop_psʹ�ܼĴ���������ʹ��λ��condition1��co-
             ndition2
 �������  : pst_mac_vap            : mac_vap�ṹ
             pst_txopps_machw_param : ����mac txop psʹ�ܼĴ��������ṹ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_txopps_set_machw_en_sta(
                                    mac_vap_stru *pst_mac_vap,
                                    dmac_txopps_machw_param_stru *pst_txopps_machw_param)
{
    mac_device_stru     *pst_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap || OAL_PTR_NULL == pst_txopps_machw_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_TXOP,
                       "{dmac_txopps_set_machw_en_sta::param is null,vap=[%d],machw_param=[%d]}.",
                       pst_mac_vap, pst_txopps_machw_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_TXOP,
                       "{dmac_txopps_set_machw_en_sta:: mac_device is null}.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    hal_set_txop_ps_enable(pst_device->pst_device_stru, pst_txopps_machw_param->en_machw_txopps_en);
    hal_set_txop_ps_condition1(pst_device->pst_device_stru, pst_txopps_machw_param->en_machw_txopps_condition1);
    hal_set_txop_ps_condition2(pst_device->pst_device_stru, pst_txopps_machw_param->en_machw_txopps_condition2);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_txopps_set_machw
 ��������  : ����vap����������mac txop psʹ�ܼĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��21��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_txopps_set_machw(mac_vap_stru *pst_mac_vap)
{
    dmac_txopps_machw_param_stru       st_txopps_machw_param;

    if (OAL_FALSE == pst_mac_vap->pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTTXOPPowerSaveOptionImplemented)
    {
        st_txopps_machw_param.en_machw_txopps_en = 0;
        st_txopps_machw_param.en_machw_txopps_condition1 = 0;
        st_txopps_machw_param.en_machw_txopps_condition2 = 0;
    }
    else
    {
        st_txopps_machw_param.en_machw_txopps_en = 1;
        st_txopps_machw_param.en_machw_txopps_condition1 = 1;
        st_txopps_machw_param.en_machw_txopps_condition2 = 1;
    }

    dmac_txopps_set_machw_en_sta(pst_mac_vap, &st_txopps_machw_param);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_txopps_set_en
 ��������  : ����11acģʽvap��txop psʹ�ܣ������apģʽֻҪ����mib����������
             ����staģʽ��Ҫ������Ӧ��mac�Ĵ���
 �������  : pst_mac_vap: mac_vap�ṹ
             en_switch  : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_txopps_set_en(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_switch)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TXOP, "{dmac_txopps_set_en:: vap is null!}.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (en_switch >= OAL_SWITCH_BUTT)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TXOP, "{dmac_txopps_set_en:: en_switch=[%d]}.", en_switch);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* ap��sta����Ҫ����mib��vap������ */
    //pst_mac_vap->st_cap_flag.bit_txop_ps = en_switch;
    pst_mac_vap->pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTTXOPPowerSaveOptionImplemented = en_switch;

    /* staģʽ����Ҫ����mac�Ĵ��� */
    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        dmac_txopps_set_machw(pst_mac_vap);
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_config_set_txop_ps_machw
 ��������  : ����mac txop psʹ�ܼĴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��16��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_config_set_txop_ps_machw(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{

    /* ֻ��sta��Ҫ���ã������ap��ֱ�ӷ��� */
    if (WLAN_VAP_MODE_BSS_STA != pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TXOP,
                         "{dmac_config_set_txop_ps_machw::vap mode is not sta-->mode is [%d]}.", pst_mac_vap->en_vap_mode);
        return OAL_SUCC;
    }

    /* �������11ac�ģ����漰txop ps��ֱ�ӷ��� */
    if ((WLAN_VHT_MODE != pst_mac_vap->en_protocol) && (WLAN_VHT_ONLY_MODE != pst_mac_vap->en_protocol))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_TXOP,
                         "{dmac_config_set_txop_ps_machw::vap is not 11ac, mode[%d].}", pst_mac_vap->en_protocol);
        return OAL_SUCC;
    }

    return dmac_txopps_set_machw_en_sta(pst_mac_vap, (dmac_txopps_machw_param_stru *)puc_param);
}


/*****************************************************************************
 �� �� ��  : dmac_txopps_init_machw_sta
 ��������  : STAģʽ��VAP��ʼ��ʱ����mac txop psʹ�ܼĴ��������֧����ʹ��λ
             ��condition1�Լ�condition2��Ϊ1
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��21��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_txopps_init_machw_sta(dmac_vap_stru *pst_dmac_vap)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_TXOP, "{dmac_txopps_init_machw_sta::dmac_vap is null!}.");
        return OAL_ERR_CODE_PTR_NULL;
    }

    dmac_txopps_set_machw(&pst_dmac_vap->st_vap_base_info);

    return OAL_SUCC;
}



/*****************************************************************************
 �� �� ��  : dmac_txopps_set_machw_partialaid_sta
 ��������  : sta��partial aidд�뵽mac�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��17��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_txopps_set_machw_partialaid_sta(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint16                           us_partial_aid;
    mac_device_stru                     *pst_mac_dev;
    mac_cfg_txop_sta_stru               *pst_txop_info;
    dmac_vap_stru                       *pst_dmac_vap;

    if (OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{dmac_txopps_set_machw_partialaid_sta::INPUT NULL PTR.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_txop_info = (mac_cfg_txop_sta_stru *)puc_param;
    us_partial_aid = pst_txop_info->us_partial_aid;

    /* ת��ΪDMAC VAP */
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    pst_mac_dev = (mac_device_stru *)mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_mac_dev) || (OAL_PTR_NULL == pst_dmac_vap)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_TXOP, "{dmac_txopps_set_machw_partialaid_sta::dmac_vap[0x%p],device[0X%p]}",pst_dmac_vap,pst_mac_dev);
        return OAL_ERR_CODE_PTR_NULL;
    }
    hal_set_txop_ps_partial_aid(pst_dmac_vap->pst_hal_vap, us_partial_aid);

    return OAL_SUCC;
}









#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

