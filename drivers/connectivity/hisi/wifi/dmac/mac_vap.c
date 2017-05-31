/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mac_vap.c
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��10��19��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
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
#include "oal_mem.h"
#include "wlan_spec.h"
#include "wlan_types.h"
#include "mac_vap.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"

#include "dmac_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_VAP_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_UAPSD
#if ((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT)
oal_uint8 g_uc_uapsd_cap = WLAN_FEATURE_UAPSD_IS_OPEN;
#else
oal_uint8 g_uc_uapsd_cap = OAL_FALSE;
#endif
#endif

/* WME��ʼ�������壬����OFDM��ʼ�� APģʽ ֵ������TGn 9 Appendix D: Default WMM AC Parameters */
/* DTS2015012001920:�޸�BE/BK��cwmin�Ĵ�С����4�޸�Ϊ3��
   DTS2015072908125 ֮ǰ�޸�Ӱ����֤4.2.23&4.2.7&4.2.8��ͬƵ�����ɿ����Ŷ�̬edca�����㷨ʵ��,������3�޸�Ϊ4*/
OAL_STATIC OAL_CONST mac_wme_param_stru g_ast_wmm_initial_params_ap[WLAN_WME_AC_BUTT] =
{
    /* BE */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          4,     6,     0,
    },

    /* BK */
    {
        /* AIFS, cwmin, cwmax, txop */
        7,          4,     10,    0,
    },

    /* VI */
    {
        /* AIFS, cwmin, cwmax, txop */
        1,          3,     4,     3008,
    },

    /* VO */
    {
        /* AIFS, cwmin, cwmax, txop */
        1,          2,     3,     1504,
    },
};

/* WMM��ʼ�������壬����OFDM��ʼ�� STAģʽ */
OAL_STATIC OAL_CONST mac_wme_param_stru g_ast_wmm_initial_params_sta[WLAN_WME_AC_BUTT] =
{
    /* BE */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          3,     10,     0,
    },

    /* BK */
    {
        /* AIFS, cwmin, cwmax, txop */
        7,          4,     10,     0,
    },


    /* VI */
    {
        /* AIFS, cwmin, cwmax, txop */
        2,          3,     4,     3008,
    },

    /* VO */
    {
        /* AIFS, cwmin, cwmax, txop */
        2,          2,     3,     1504,
    },
};

/* WMM��ʼ�������壬aput������bss��STA��ʹ�õ�EDCA���� */
OAL_STATIC OAL_CONST mac_wme_param_stru g_ast_wmm_initial_params_bss[WLAN_WME_AC_BUTT] =
{
    /* BE */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          4,     10,     0,
    },

    /* BK */
    {
        /* AIFS, cwmin, cwmax, txop */
        7,          4,     10,     0,
    },


    /* VI */
    {
        /* AIFS, cwmin, cwmax, txop */
        2,          3,     4,     3008,
    },

    /* VO */
    {
        /* AIFS, cwmin, cwmax, txop */
        2,          2,     3,     1504,
    },
};

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
/* ���û������ȼ�ʹ�õ�EDCA���� */
OAL_STATIC OAL_CONST mac_wme_param_stru g_ast_wmm_multi_user_multi_ac_params_ap[WLAN_WME_AC_BUTT] =
{
    /* BE */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          5,     10,     0,
    },

    /* BK */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          5,     10,     0,
    },


    /* VI */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          5,     10,     0,
    },

    /* VO */
    {
        /* AIFS, cwmin, cwmax, txop */
        3,          5,     10,     0,
    },
};
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : dmac_get_wmm_cfg
 ��������  : ��ȡap����sta ������ָ��
 �������  : en_vap_mode: en_vap_mode��ǰģʽ

 �������  :
 �� �� ֵ  : wmm����ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
mac_wme_param_stru  *mac_get_wmm_cfg(wlan_vap_mode_enum_uint8 en_vap_mode)
{
    /* �ο���֤�����ã�û�а���Э�����ã�WLAN_VAP_MODE_BUTT��ʾ��ap�㲥��sta��edca���� */
    if (WLAN_VAP_MODE_BUTT == en_vap_mode)
    {
        return (mac_wme_param_stru  *)g_ast_wmm_initial_params_bss;
    }
    else if(WLAN_VAP_MODE_BSS_AP == en_vap_mode)
    {
       return (mac_wme_param_stru  *)g_ast_wmm_initial_params_ap;
    }
    return (mac_wme_param_stru  *)g_ast_wmm_initial_params_sta;

}

#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
/*****************************************************************************
 �� �� ��  : mac_get_wmm_cfg_multi_user_multi_ac
 ��������  : ��ȡ���û������ȼ�ʱap������ָ��
 �������  : uc_traffic_type: ҵ������

 �������  :
 �� �� ֵ  : wmm����ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : k00347307
    �޸�����   : �����ɺ���

*****************************************************************************/
mac_wme_param_stru  *mac_get_wmm_cfg_multi_user_multi_ac(oal_traffic_type_enum_uint8 uc_traffic_type)
{
    /* ���û���ҵ�����Ͳ����²������������apģʽ�µ�Ĭ��ֵ */
    if (OAL_TRAFFIC_MULTI_USER_MULTI_AC == uc_traffic_type)
    {
        return (mac_wme_param_stru  *)g_ast_wmm_multi_user_multi_ac_params_ap;
    }

    return (mac_wme_param_stru  *)g_ast_wmm_initial_params_ap;

}
#endif

/*****************************************************************************
 �� �� ��  : mac_mib_set_station_id
 ��������  : ����StationIDֵ����mac��ַ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
             uc_len     : ��������
             pc_param   : ����
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_set_station_id(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_staion_id_param_stru   *pst_param;

    pst_param = (mac_cfg_staion_id_param_stru *)puc_param;

    oal_set_mac_addr(pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,pst_param->auc_station_id);

    return OAL_SUCC;
}
#if 0
/*****************************************************************************
 �� �� ��  : mac_mib_get_station_id
 ��������  : ����StationIDֵ����mac��ַ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
 �������  : puc_len : ���ز����ĳ���
             pc_param: ���ز���
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_get_station_id(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    mac_cfg_staion_id_param_stru   *pst_param;

    pst_param = (mac_cfg_staion_id_param_stru *)puc_param;

    oal_memcopy(pst_param->auc_station_id,
                pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID,
                WLAN_MAC_ADDR_LEN);

    *puc_len = OAL_SIZEOF(mac_cfg_staion_id_param_stru);

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : mac_mib_set_bss_type
 ��������  : ����bss type mibֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
             uc_len     : ��������
             pc_param   : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_set_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value = *((oal_int32 *)puc_param);

    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType = (oal_uint8)l_value;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_bss_type
 ��������  : ��ȡbss type mibֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
 �������  : puc_len : ���ز����ĳ���
             pc_param: ���ز���
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_get_bss_type(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    *((oal_int32 *)puc_param) = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType;
    *puc_len = OAL_SIZEOF(oal_int32);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_ssid
 ��������  : ����ssid mibֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
             uc_len     : ��������
             pc_param   : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_set_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    mac_cfg_ssid_param_stru    *pst_param;
    oal_uint8                   uc_ssid_len;
    oal_uint8                  *puc_mib_ssid;

    pst_param   = (mac_cfg_ssid_param_stru *)puc_param;
    uc_ssid_len = pst_param->uc_ssid_len;       /* ���Ȳ������ַ�����β'\0' */

    if (uc_ssid_len > WLAN_SSID_MAX_LEN - 1)
    {
        uc_ssid_len = WLAN_SSID_MAX_LEN - 1;
    }

    puc_mib_ssid = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID;

    oal_memcopy(puc_mib_ssid, pst_param->ac_ssid, uc_ssid_len);
    puc_mib_ssid[uc_ssid_len] = '\0';

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_ssid
 ��������  : ��ȡssid mibֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
 �������  : puc_len : ���ز����ĳ���
             pc_param: ���ز���
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_get_ssid(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    mac_cfg_ssid_param_stru *pst_param;
    oal_uint8                uc_ssid_len;
    oal_uint8               *puc_mib_ssid;

    puc_mib_ssid = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11DesiredSSID;
    uc_ssid_len  = (oal_uint8)OAL_STRLEN((oal_int8 *)puc_mib_ssid);

    pst_param = (mac_cfg_ssid_param_stru *)puc_param;

    pst_param->uc_ssid_len = uc_ssid_len;
    oal_memcopy(pst_param->ac_ssid, puc_mib_ssid, uc_ssid_len);

    *puc_len = OAL_SIZEOF(mac_cfg_ssid_param_stru);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_beacon_period
 ��������  : ����beacon interval��ֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
             uc_len     : ��������
             pc_param   : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_set_beacon_period(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_uint32       ul_value;

    ul_value     = *((oal_uint32 *)puc_param);

    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod = (oal_uint32)ul_value;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_beacon_period
 ��������  : ��ȡbeacon interval��ֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
 �������  : puc_len    : ���ز����ĳ���
             pc_param   : ���ز���
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_get_beacon_period(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    *((oal_uint32 *)puc_param) = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod;

    *puc_len = OAL_SIZEOF(oal_uint32);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : mac_mib_set_dtim_period
 ��������  : ����dtim period��ֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
             uc_len     : ��������
             pc_param   : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_set_dtim_period(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value     = *((oal_int32 *)puc_param);

    pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod = (oal_uint32)l_value;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_dtim_period
 ��������  : ��ȡdtim period��ֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
 �������  : puc_len    : ���ز����ĳ���
             pc_param   : ���ز���
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_get_dtim_period(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    *((oal_uint32 *)puc_param) = pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod;

    *puc_len = OAL_SIZEOF(oal_uint32);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_shpreamble
 ��������  : ����short preamble MIBֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
             uc_len     : ��������
             pc_param   : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_set_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value     = *((oal_int32 *)puc_param);

    if (0 != l_value)
    {
        mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, OAL_TRUE);
    }
    else
    {
        mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, OAL_FALSE);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_shpreamble
 ��������  : ��ȡshort preamble MIBֵ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_get_shpreamble(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_param)
{
    oal_int32       l_value;

    l_value = mac_mib_get_ShortPreambleOptionImplemented(pst_mac_vap);

    *((oal_int32 *)puc_param) = l_value;

    *puc_len = OAL_SIZEOF(l_value);

    return OAL_SUCC;

}
#if 0
/*****************************************************************************
 �� �� ��  : mac_mib_get_GroupReceivedFrameCount
 ��������  : ��ȡVAP�ѽ��յ����鲥֡����Ŀ
 �������  : (1)��Ҫ���õ�VAP��ָ��
             (2)��Ҫ���õ��ַ����ĳ���
 �������  : ���յ���amsdu�ĸ���
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_get_GroupReceivedFrameCount(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_len, oal_uint8 *puc_group_count)
{
    *((oal_uint32*)puc_group_count) = pst_mac_vap->pst_mib_info->st_wlan_mib_counters.ul_dot11GroupReceivedFrameCount;

    *puc_len = OAL_SIZEOF(oal_uint32);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_GroupReceivedFrameCount
 ��������  : ���ý��յ��ĵ��鲥֡����Ŀ
 �������  : (1)��Ҫ���õ�VAP��ָ��
             (2)��Ҫ���õ��ַ����ĳ���
             (3)���õ�ֵ
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��24��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_mib_set_GroupReceivedFrameCount(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_group_count)
{
    oal_uint32      ul_value;

    ul_value = *((oal_uint32 *)puc_group_count);

    pst_mac_vap->pst_mib_info->st_wlan_mib_counters.ul_dot11GroupReceivedFrameCount = ul_value;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : mac_mib_get_wpa_pairwise_cipher_suite
 ��������  : ��ȡʵ�ֵ�pairwise cipher suites����
 �������  : pst_mac_vap: ָ��vap
 �������  : puc_num    : ʵ�ֵ�pairwise cipher suites����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��16��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_mib_get_wpa_pairwise_cipher_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num)
{
    oal_uint8   uc_num = 0;
    oal_uint8   uc_loop;

    for (uc_loop = 0; uc_loop < WLAN_PAIRWISE_CIPHER_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_loop].en_dot11RSNAConfigPairwiseCipherActivated)
        {
            uc_num++;
        }
    }
    *puc_num = uc_num;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_wpa2_pairwise_cipher_suite
 ��������  : ��ȡʵ�ֵ�pairwise cipher suites����
 �������  : pst_mac_vap: ָ��vap
 �������  : puc_num    : ʵ�ֵ�pairwise cipher suites����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��16��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_mib_get_wpa2_pairwise_cipher_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num)
{
    oal_uint8   uc_num = 0;
    oal_uint8   uc_loop;

    for (uc_loop = 0; uc_loop < WLAN_PAIRWISE_CIPHER_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_loop].en_dot11RSNAConfigPairwiseCipherActivated)
        {
            uc_num++;
        }
    }

    *puc_num = uc_num;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_authentication_suite
 ��������  : ��ȡʵ�ֵ�authentication suites����
 �������  : pst_mac_vap: ָ��vap
 �������  : puc_num    : ʵ�ֵ�authentication suites����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��16��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_mib_get_authentication_suite(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_num)
{
    oal_uint8   uc_num = 0;
    oal_uint8   uc_loop;

    for (uc_loop = 0; uc_loop < WLAN_AUTHENTICATION_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_loop].en_dot11RSNAConfigAuthenticationSuiteActivated)
        {
            uc_num++;
        }
    }

    *puc_num = uc_num;
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_wpa2_pairwise_cipher_suite_value
 ��������  : ��ȡʵ�ֵ�pairwise cipher suites �����׼�ֵ
 �������  : pst_mac_vap        : ָ��vap
 �������  : puc_pairwise_value : ʵ�ֵ�pairwise cipher suites �����׼�ֵ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��22��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_mib_get_wpa2_pairwise_cipher_suite_value(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_pairwise_value)
{
    oal_uint8   uc_loop;
    oal_uint8   uc_pairwise_index = 0;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_pairwise_value))
    {
        MAC_ERR_VAR(0, "Error:NULL pointer.%x, %x", pst_mac_vap, puc_pairwise_value);
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{mac_mib_get_wpa2_pairwise_cipher_suite_value::param null, %d %d.}",  pst_mac_vap, puc_pairwise_value);

        return;
    }

    for (uc_loop = 0; uc_loop < WLAN_PAIRWISE_CIPHER_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_loop].en_dot11RSNAConfigPairwiseCipherActivated)
        {
            puc_pairwise_value[uc_pairwise_index++] = pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_loop].uc_dot11RSNAConfigPairwiseCipherImplemented;
        }
    }
}

/*****************************************************************************
 �� �� ��  : mac_mib_get_wpa_pairwise_cipher_suite_value
 ��������  : ��ȡʵ�ֵ�pairwise cipher suites �����׼�ֵ
 �������  : pst_mac_vap        : ָ��vap
 �������  : puc_pairwise_value : ʵ�ֵ�pairwise cipher suites �����׼�ֵ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��22��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_mib_get_wpa_pairwise_cipher_suite_value(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_pairwise_value)
{
    oal_uint8   uc_loop;
    oal_uint8   uc_pairwise_index = 0;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_pairwise_value))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_mib_get_wpa_pairwise_cipher_suite_value::param null.}");

        return;
    }

    for (uc_loop = 0; uc_loop < WLAN_PAIRWISE_CIPHER_SUITES; uc_loop++)
    {
        if (OAL_TRUE == pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_loop].en_dot11RSNAConfigPairwiseCipherActivated)
        {
            puc_pairwise_value[uc_pairwise_index++] = pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_loop].uc_dot11RSNAConfigPairwiseCipherImplemented;
        }
    }
}

#ifdef _PRE_WLAN_FEATURE_SMPS
/*****************************************************************************
 �� �� ��  : mac_mib_get_smps
 ��������  : ��ȡMIB�� en_dot11MIMOPowerSave ��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : en_dot11MIMOPowerSave
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���
*****************************************************************************/
wlan_mib_mimo_power_save_enum_uint8 mac_mib_get_smps(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MIMOPowerSave;
}

/*****************************************************************************
 �� �� ��  : mac_vap_get_smps_mode
 ��������  : ��ȡen_dot11MIMOPowerSave��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_get_smps_mode(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    if (OAL_TRUE != pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented)
    {
        /* ��HT�û�����֧��SMPS ���طǷ���ϢWLAN_MIB_MIMO_POWER_SAVE_BUTT */
        *puc_param = WLAN_MIB_MIMO_POWER_SAVE_BUTT;
        *pus_len   = OAL_SIZEOF(oal_uint8);
        return OAL_SUCC;
    }

    *puc_param = pst_mac_vap->pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MIMOPowerSave;

    *pus_len   = OAL_SIZEOF(oal_uint8);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_get_smps_en
 ��������  : ��ȡbit_smps��ֵ
 �������  : pst_mac_vap: MAC VAP�ṹ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��9��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_get_smps_en(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_len, oal_uint8 *puc_param)
{
    mac_device_stru   *pst_mac_device;

    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_SMPS, "{mac_vap_get_smps_en::pst_mac_device[%d] null.}", pst_mac_vap->uc_device_id);

        return OAL_ERR_CODE_PTR_NULL;
    }

    *puc_param = pst_mac_device->en_smps;

    *pus_len   = OAL_SIZEOF(oal_uint8);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_smps
 ��������  : ����vap��smps
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_smps(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_smps = uc_value;
}
#endif

#ifdef _PRE_WLAN_FEATURE_UAPSD
/*****************************************************************************
 �� �� ��  : mac_vap_set_uapsd_en
 ��������  : ����U-APSDʹ��
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
             uc_len     : ��������
             pc_param   : ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_uint32  mac_vap_set_uapsd_en(mac_vap_stru *pst_mac_vap, oal_uint8 uc_value)
{
    pst_mac_vap->st_cap_flag.bit_uapsd = (OAL_TRUE == uc_value)?1:0;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_get_uapsd_en
 ��������  : ��ȡbeacon interval��ֵ
 �������  : pst_mac_vap: ָ��mac vap�ṹ��
 �������  : puc_len    : ���ز����ĳ���
             pc_param   : ���ز���
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8  mac_vap_get_uapsd_en(mac_vap_stru *pst_mac_vap)
{

    return pst_mac_vap->st_cap_flag.bit_uapsd;
}

#endif


/*****************************************************************************
 �� �� ��  : mac_vap_user_exist
 ��������  : ���dmac list�ļ��
 �������  :
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��02��
    ��    ��   : c00221210
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��05��02��
    ��    ��   : g00260350
    �޸�����   : �޸ĺ�����������ֵ

*****************************************************************************/
oal_uint32 mac_vap_user_exist(oal_dlist_head_stru *pst_new, oal_dlist_head_stru *pst_head)
{
    oal_dlist_head_stru      *pst_user_list_head;
    oal_dlist_head_stru      *pst_member_entry;


    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_member_entry,pst_user_list_head,pst_head)
    {
        if(pst_new == pst_member_entry)
        {
            OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{oal_dlist_check_head:dmac user doule add.}");
            return OAL_SUCC;
        }
    }

    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : mac_vap_add_assoc_user
 ��������  : ���ӹ����û�����ȡhashֵ������hash����
 �������  : vap�����ڴ�ָ�룬�Լ�user����ָ��(user������Ҫ�ڵ��ô˺���ǰ���벢��ֵ)
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��
 ���ú���  : mac_vap_get_user_hash_value��oal_dlist_insert_elem_head
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_add_assoc_user(mac_vap_stru *pst_vap, oal_uint16 us_user_idx)
{
    mac_user_stru              *pst_user;
    mac_res_user_hash_stru     *pst_hash;
    oal_uint32                  ul_rslt;
    oal_uint16                  us_hash_idx;
    oal_dlist_head_stru        *pst_dlist_head;
    oal_uint                    ul_irq_save;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{mac_vap_add_assoc_user::pst_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_user = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_add_assoc_user::pst_user[%d] null.}", us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_user->us_user_hash_idx = MAC_CALCULATE_HASH_VALUE(pst_user->auc_user_mac_addr);

    /* ����hash�ṹ��: DMAC_offload ģʽ�� hmac��dmac���us_hash_idx���ܲ�һ�£����Ƕ�ҵ����Ӱ�죬
    ��indx��������־ÿһ��ʹ���е�hash��Ԫ����������hash�����û� */
    ul_rslt = mac_res_alloc_hash(&us_hash_idx);

    if (OAL_SUCC != ul_rslt)
    {
        OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_add_assoc_user::mac_res_alloc_hash failed[%d].}", ul_rslt);

        return ul_rslt;
    }

    pst_hash = mac_res_get_hash(us_hash_idx);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hash))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_add_assoc_user::pst_hash[%d] null.}", us_hash_idx);
        mac_res_free_hash(us_hash_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    if(OAL_SUCC == mac_vap_user_exist(&(pst_user->st_user_dlist), &(pst_vap->st_mac_user_list_head)))
    {
        mac_res_free_hash(us_hash_idx);
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_add_assoc_user::user[%d] already exist.}", us_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��¼HASH��Ӧ����Դ������ֵ */
    pst_hash->us_hash_res_idx = us_hash_idx;

    /* ��¼��Ӧ���û�����ֵ */
    pst_hash->us_user_idx = us_user_idx;

    pst_dlist_head = &(pst_vap->ast_user_hash[pst_user->us_user_hash_idx]);
#ifdef _PRE_WLAN_DFT_STAT
    (pst_vap->ul_hash_cnt)++;
#endif
    oal_dlist_add_head(&(pst_hash->st_entry), pst_dlist_head);

    /* ����˫�������ͷ */
    pst_dlist_head = &(pst_vap->st_mac_user_list_head);
    oal_dlist_add_head(&(pst_user->st_user_dlist), pst_dlist_head);
#ifdef _PRE_WLAN_DFT_STAT
    (pst_vap->ul_dlist_cnt)++;
#endif
    oal_spin_lock_irq_save(&pst_vap->st_cache_user_lock, &ul_irq_save);

    /* ����cache user */
    oal_set_mac_addr(pst_vap->auc_cache_user_mac_addr, pst_user->auc_user_mac_addr);
    pst_vap->us_cache_user_id = us_user_idx;

    oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);

    /* ��¼STAģʽ�µ���֮������VAP��id */
    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
    {
        mac_vap_set_assoc_id(pst_vap, (oal_uint8)us_user_idx);
    }

    /* vap�ѹ��� user����++ */
    pst_vap->us_user_nums++;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : mac_vap_del_user
 ��������  : ɾ���û������û���˫��������ɾ��������hash����ɾ��
 �������  : vap����ָ�룬�Լ�user����ָ��(user������Ҫ�ڵ��ô˺���ǰ�ҵ�,
             ���Ҵ˺����������ͷ�user�ڴ�,��ɾ���ߵ���USER_DESTORY�����ͷ��ڴ�)
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��
 ���ú���  : oal_dlist_rmv_elem
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_del_user(mac_vap_stru *pst_vap, oal_uint16 us_user_idx)
{
    mac_user_stru          *pst_user;
    mac_user_stru          *pst_user_temp;
    oal_dlist_head_stru    *pst_hash_head;
    oal_dlist_head_stru    *pst_entry;
    mac_res_user_hash_stru *pst_user_hash;
    oal_dlist_head_stru    *pst_dlist_tmp       = OAL_PTR_NULL;
    oal_uint32              ul_ret              = OAL_FAIL;
    oal_uint8               uc_txop_ps_user_cnt = 0;
    oal_uint                ul_irq_save;


    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ASSOC, "{mac_vap_del_user::pst_vap null,us_user_idx is %d}", us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }


    oal_spin_lock_irq_save(&pst_vap->st_cache_user_lock, &ul_irq_save);

    /* ��cache user id�Ա� , ��������cache user*/
    if (us_user_idx == pst_vap->us_cache_user_id)
    {
        oal_set_mac_addr_zero(pst_vap->auc_cache_user_mac_addr);
        /* DTS2015082603340 ����û���ɾ����cache id��mac addr��Ϊ0�����·�������ж��°벿���ɿ����ҵ���ɾ�����û� */
        pst_vap->us_cache_user_id = MAC_INVALID_USER_ID;
    }

    oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);

    pst_user = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_user))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_del_user::pst_user null,us_user_idx is %d}", us_user_idx);

        return OAL_ERR_CODE_PTR_NULL;
    }

    mac_user_set_asoc_state(pst_user, MAC_USER_STATE_BUTT);

    if(pst_user->us_user_hash_idx >= MAC_VAP_USER_HASH_MAX_VALUE)
    {
        /*ADD USER���ʧ�������ظ�ɾ��User�����ܽ���˷�֧��*/
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_del_user::hash idx invaild %u}", pst_user->us_user_hash_idx);
        return OAL_FAIL;
    }

    pst_hash_head = &(pst_vap->ast_user_hash[pst_user->us_user_hash_idx]);

    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_dlist_tmp, pst_hash_head)
    {
        pst_user_hash = (mac_res_user_hash_stru *)pst_entry;

        pst_user_temp = (mac_user_stru *)mac_res_get_mac_user((oal_uint8)(pst_user_hash->us_user_idx));

        if (OAL_PTR_NULL == pst_user_temp)
        {
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_del_user::pst_user_temp null,us_user_idx is %d}", us_user_idx);

            continue;
        }
        if (pst_user_temp->st_vht_hdl.bit_vht_txop_ps)
        {
            uc_txop_ps_user_cnt++;
        }

        if (!oal_compare_mac_addr(pst_user->auc_user_mac_addr, pst_user_temp->auc_user_mac_addr))
        {
            oal_dlist_delete_entry(pst_entry);

            /* ��˫�������в�� */
            oal_dlist_delete_entry(&(pst_user->st_user_dlist));

            mac_res_free_hash(pst_user_hash->us_hash_res_idx);
            ul_ret = OAL_SUCC;

#ifdef _PRE_WLAN_DFT_STAT
            (pst_vap->ul_hash_cnt)--;
            (pst_vap->ul_dlist_cnt)--;
#endif
            /* ��ʼ����Ӧ��Ա */
            pst_user->us_user_hash_idx = 0xffff;
            pst_user->us_assoc_id      = us_user_idx;
            pst_user->en_is_multi_user = OAL_FALSE;
            OAL_MEMZERO(pst_user->auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
            pst_user->uc_vap_id        = 0xff;
            pst_user->uc_device_id     = 0xff;
            pst_user->uc_chip_id       = 0xff;
            pst_user->en_user_asoc_state = MAC_USER_STATE_BUTT;
        }
    }

    if (0 == uc_txop_ps_user_cnt)
    {
        pst_vap->st_cap_flag.bit_txop_ps = OAL_FALSE;
    }

    if (OAL_SUCC == ul_ret)
    {
        /* vap�ѹ��� user����-- */
        if (pst_vap->us_user_nums)
        {
            pst_vap->us_user_nums--;
        }
        /* STAģʽ�½�������VAP��id��Ϊ�Ƿ�ֵ */
        if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
        {
            mac_vap_set_assoc_id(pst_vap, 0xff);
        }
        return OAL_SUCC;
    }

    OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_del_user::delete user failed,user idx is %d.}", us_user_idx);

    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : mac_vap_find_user_by_macaddr
 ��������  : ����user MAC��ַ����user����
 �������  : vap����ָ�룬�Լ�user MAC��ַ
 �������  : user����ָ��
 �� �� ֵ  : �ɹ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_find_user_by_macaddr( mac_vap_stru *pst_vap, oal_uint8 *puc_sta_mac_addr, oal_uint16 *pus_user_idx)
{
    mac_user_stru              *pst_mac_user;
    oal_uint32                  ul_user_hash_value;
    mac_res_user_hash_stru     *pst_hash;
    oal_dlist_head_stru        *pst_entry;
    oal_uint                    ul_irq_save;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_vap)
                  || (OAL_PTR_NULL == puc_sta_mac_addr)
                  || ((OAL_PTR_NULL == pus_user_idx))))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_vap_find_user_by_macaddr::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
    {
        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_vap->uc_assoc_vap_id);
        if (OAL_PTR_NULL == pst_mac_user)
        {
            return OAL_FAIL;
        }

        if (!oal_compare_mac_addr(pst_mac_user->auc_user_mac_addr, puc_sta_mac_addr))
        {
            *pus_user_idx = pst_vap->uc_assoc_vap_id;
            return (*pus_user_idx != (oal_uint16)MAC_INVALID_USER_ID) ? OAL_SUCC : OAL_FAIL;/* [false alarm]:����ֵΪ����ֵ0����1����Ӱ��*/
        }
        return OAL_FAIL;
    }

    oal_spin_lock_irq_save(&pst_vap->st_cache_user_lock, &ul_irq_save);
    /* ��cache user�Ա� , �����ֱ�ӷ���cache user id*/
    if (!oal_compare_mac_addr(pst_vap->auc_cache_user_mac_addr, puc_sta_mac_addr))
    {
        /* �û�ɾ����user macaddr��cache user macaddr��ַ��Ϊ0����ʵ�����û��Ѿ�ɾ������ʱuser id��Ч */
        *pus_user_idx = pst_vap->us_cache_user_id;
        oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);
        return (*pus_user_idx != (oal_uint16)MAC_INVALID_USER_ID) ? OAL_SUCC : OAL_FAIL;/* [false alarm]:����ֵΪ����ֵ0����1����Ӱ��*/
    }

    ul_user_hash_value = MAC_CALCULATE_HASH_VALUE(puc_sta_mac_addr);

    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_vap->ast_user_hash[ul_user_hash_value]))
    {
        pst_hash = (mac_res_user_hash_stru *)pst_entry;

        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_hash->us_user_idx);

        if (OAL_PTR_NULL == pst_mac_user)
        {
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_find_user_by_macaddr::pst_mac_user null.user idx %d}",pst_hash->us_user_idx);
            continue;
        }

        /* ��ͬ��MAC��ַ */
        if (!oal_compare_mac_addr(pst_mac_user->auc_user_mac_addr, puc_sta_mac_addr))
        {
            *pus_user_idx = pst_hash->us_user_idx;
            /*����cache user*/
            oal_set_mac_addr(pst_vap->auc_cache_user_mac_addr, pst_mac_user->auc_user_mac_addr);
            pst_vap->us_cache_user_id = pst_hash->us_user_idx;
            oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);
            return (*pus_user_idx != (oal_uint16)MAC_INVALID_USER_ID) ? OAL_SUCC : OAL_FAIL;/* [false alarm]:����ֵΪ����ֵ0����1����Ӱ��*/
        }
    }
    oal_spin_unlock_irq_restore(&pst_vap->st_cache_user_lock, &ul_irq_save);
    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : mac_device_find_user_by_macaddr
 ��������  : ����user MAC��ַ����user����
 �������  : vap����ָ�룬�Լ�user MAC��ַ
 �������  : user����ָ��
 �� �� ֵ  : �ɹ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_device_find_user_by_macaddr(
                mac_vap_stru        *pst_vap,
                oal_uint8           *puc_sta_mac_addr,
                oal_uint16          *pus_user_idx)
{
    mac_device_stru            *pst_device;
    mac_vap_stru               *pst_mac_vap;
    oal_uint8                   uc_vap_id;
    oal_uint8                   uc_vap_idx;
    oal_uint32                  ul_ret;

    /* ��ȡdevice */
    pst_device = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "mac_res_get_dev[%d] return null ", pst_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��device�µ�����vap���б��� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        uc_vap_id = pst_device->auc_vap_id[uc_vap_idx];

        /* ����vap����Ҫ���� */
        if (uc_vap_id == pst_device->uc_cfg_vap_id)
        {
            continue;
        }

        /* ��vap����Ҫ���� */
        if (uc_vap_id == pst_vap->uc_vap_id)
        {
            continue;
        }

        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(uc_vap_id);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            continue;
        }

        /* ֻ����APģʽ */
        if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
        {
            continue;
        }

        ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_sta_mac_addr, pus_user_idx);
        if (OAL_SUCC == ul_ret)
        {
            return OAL_SUCC;
        }
    }

    return OAL_FAIL;
}
#if 0
/*****************************************************************************
 �� �� ��  : mac_vap_update_user
 ��������  : ����user��Ϣ
 �������  : VAP�����user���ݽṹָ�룬���user���ݽṹ�е�������Ϣ�ڵ��ô˺���ǰ���Ѹ�ֵ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_update_user(mac_vap_stru *pst_vap, oal_uint32   ul_user_dix)
{
    /* ��OFFLOAD�����²���Ҫʵ�� */

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : mac_vap_init_wme_param
 ��������  : ��ʼ��wme����, ��sta֮���ģʽ
 �������  :
 �������  : pst_wme_param: wme����
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��13��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_init_wme_param(mac_vap_stru *pst_mac_vap)
{
    OAL_CONST mac_wme_param_stru   *pst_wmm_param;
    OAL_CONST mac_wme_param_stru   *pst_wmm_param_sta;
    oal_uint8                       uc_ac_type;

    pst_wmm_param = mac_get_wmm_cfg(pst_mac_vap->en_vap_mode);
    if(OAL_PTR_NULL == pst_wmm_param)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_ac_type = 0; uc_ac_type < WLAN_WME_AC_BUTT; uc_ac_type++)
    {
        /* VAP�����EDCA���� */
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableIndex   = uc_ac_type + 1;
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableAIFSN   = pst_wmm_param[uc_ac_type].ul_aifsn;
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableCWmin   = pst_wmm_param[uc_ac_type].ul_logcwmin;
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableCWmax   = pst_wmm_param[uc_ac_type].ul_logcwmax;
        pst_mac_vap->pst_mib_info->st_wlan_mib_qap_edac[uc_ac_type].ul_dot11QAPEDCATableTXOPLimit = pst_wmm_param[uc_ac_type].ul_txop_limit;
    }

    if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
    {
        /* APģʽʱ�㲥��STA��EDCA������ֻ��APģʽ��Ҫ��ʼ����ֵ��ʹ��WLAN_VAP_MODE_BUTT�� */
        pst_wmm_param_sta = mac_get_wmm_cfg(WLAN_VAP_MODE_BUTT);

        for (uc_ac_type = 0; uc_ac_type < WLAN_WME_AC_BUTT; uc_ac_type++)
        {
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableIndex     = uc_ac_type + 1;  /* ע: Э��涨ȡֵ1 2 3 4 */
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableAIFSN     = pst_wmm_param_sta[uc_ac_type].ul_aifsn;
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableCWmin     = pst_wmm_param_sta[uc_ac_type].ul_logcwmin;
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableCWmax     = pst_wmm_param_sta[uc_ac_type].ul_logcwmax;
            pst_mac_vap->pst_mib_info->ast_wlan_mib_edca[uc_ac_type].ul_dot11EDCATableTXOPLimit = pst_wmm_param_sta[uc_ac_type].ul_txop_limit;
        }
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : mac_mib_clear_rsna_auth_suite
 ��������  : ��� RSN��֤�׼�
 �������  :
 �������  : pst_mac_vap
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��08��14��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_mib_clear_rsna_auth_suite(mac_vap_stru *pst_mac_vap)
{
    oal_uint8   uc_index = 0;

    for (uc_index = 0; uc_index < WLAN_AUTHENTICATION_SUITES; uc_index++)
    {
        pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_FALSE;
        pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].uc_dot11RSNAConfigAuthenticationSuiteImplemented = 0xff;
        pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].ul_dot11RSNAConfigAuthenticationSuiteIndex       = uc_index;
    }
}

/*****************************************************************************
 �� �� ��  : mac_mib_set_rsna_auth_suite
 ��������  : ���� RSN��֤�׼���Ϣ
 �������  :
 �������  : pst_mac_vap��uc_auth_value
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��08��14��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_mib_set_rsna_auth_suite(mac_vap_stru *pst_mac_vap, oal_uint8 uc_auth_value)
{
    oal_uint8 uc_index;

    if ((WLAN_AUTH_SUITE_1X == uc_auth_value)
        || (WLAN_AUTH_SUITE_PSK == uc_auth_value))
    {
        uc_index = 0;
    }
    else if ((WLAN_AUTH_SUITE_1X_SHA256 == uc_auth_value)
        || (WLAN_AUTH_SUITE_PSK_SHA256 == uc_auth_value))
    {
        uc_index = 1;
    }
    else
    {
        MAC_ERR_VAR(pst_mac_vap->uc_vap_id, "ERROR! auth_value = %d", uc_auth_value);
        return;
    }

    pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].uc_dot11RSNAConfigAuthenticationSuiteImplemented = uc_auth_value;
    pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_index].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_TRUE;

}
#if 0
/*****************************************************************************
 �� �� ��  : mac_vap_get_user_wme_info
 ��������  : ��ȡ�����û���WME����
 �������  : pst_vap      : ָ��VAP�û���ָ��
             en_wme_type  : WMEö������
 �������  : ppst_wme_info: ָ��WME������ָ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_get_user_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info)
{
    if (OAL_PTR_NULL == pst_vap || OAL_PTR_NULL == pst_wme_info)
    {
        MAC_ERR_LOG(0, "mac_get_user_wme_info: input pointers are null!");
        OAM_ERROR_LOG0(0, OAM_SF_WMM, "{mac_vap_get_user_wme_info::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_wme_info->ul_aifsn = pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableAIFSN;
    pst_wme_info->ul_logcwmax = pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableCWmax;
    pst_wme_info->ul_logcwmin = pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableCWmin;
    pst_wme_info->ul_txop_limit = pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableTXOPLimit;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_user_wme_info
 ��������  : ���ù����û���WME����
 �������  : pst_vap      : ָ��VAP�û���ָ��
             en_wme_type  : WMEö������
             pst_wme_info : ָ��WME������ָ��
 �������  :
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��2��5��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_set_user_wme_info(
                mac_vap_stru               *pst_vap,
                wlan_wme_ac_type_enum_uint8 en_wme_type,
                mac_wme_param_stru         *pst_wme_info)
{
    if (OAL_PTR_NULL == pst_vap || OAL_PTR_NULL == pst_wme_info)
    {
        MAC_ERR_LOG(0, "mac_get_user_wme_info: input pointers are null!");
        OAM_ERROR_LOG0(0, OAM_SF_WMM, "{mac_vap_set_user_wme_info::param null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableAIFSN = pst_wme_info->ul_aifsn;
    pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableCWmax = pst_wme_info->ul_logcwmax;
    pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableCWmin = pst_wme_info->ul_logcwmin;
    pst_vap->pst_mib_info->ast_wlan_mib_edca[en_wme_type].ul_dot11EDCATableTXOPLimit = pst_wme_info->ul_txop_limit;

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : mac_vap_init_rsna_status
 ��������  : ��ʼ��11i mib��Ϣ��STA���ͳ����Ϣ
 �������  : pst_vap: ָ��VAP�û���ָ��
           : ul_idx :sta idx
 �������  :
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��29��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_vap_init_rsna_status(mac_vap_stru *pst_vap, oal_uint32 ul_idx)
{
    OAL_MEMZERO((oal_void *)(&pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[ul_idx]), OAL_SIZEOF(wlan_mib_Dot11RSNAStatsEntry_stru));
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[ul_idx].ul_dot11RSNAStatsIndex = ul_idx;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[ul_idx].ul_dot11RSNAStatsVersion = pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigVersion;
}

/*****************************************************************************
 �� �� ��  : mibset_RSNAStatsSTAAddress
 ��������  :
 �������  : pst_vap: ָ��VAP�û���ָ��
           : ul_idx :
 �������  :
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��29��
    ��    ��   : louyueyun
    �޸�����   : �����ɺ���

*****************************************************************************/
void mibset_RSNAStatsSTAAddress(oal_uint8 *puc_addr, mac_vap_stru *pst_vap, oal_uint16 us_idx)
{
    oal_memcopy((oal_void *)pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[us_idx].auc_dot11RSNAStatsSTAAddress,puc_addr, WLAN_MAC_ADDR_LEN);
}
void mibset_RSNAStatsSelectedPairwiseCipher(oal_uint8 inp, mac_vap_stru *pst_vap, oal_uint16 us_idx)
{
     pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[us_idx].uc_dot11RSNAStatsSelectedPairwiseCipher = inp;;
}
void mac_mib_set_RSNAAuthenticationSuiteSelected(mac_vap_stru *pst_vap, oal_uint8 uc_inp)
{
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteSelected = uc_inp;
}
void mac_mib_set_RSNAPairwiseCipherSelected(mac_vap_stru *pst_vap, oal_uint8 uc_inp)
{
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherSelected = uc_inp;
}

void mac_mib_set_RSNAConfigAuthenticationSuiteImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_inp, oal_uint8 uc_idx)
{
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_idx].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_TRUE;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_idx].uc_dot11RSNAConfigAuthenticationSuiteImplemented = uc_inp;
}

void mibset_RSNAClearWpaPairwiseCipherImplemented(mac_vap_stru *pst_vap)
{
    oal_uint8 uc_index;

    for (uc_index = 0; uc_index < WLAN_PAIRWISE_CIPHER_SUITES; uc_index++)
    {
        pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_index].uc_dot11RSNAConfigPairwiseCipherImplemented = 0xFF;
        pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_index].en_dot11RSNAConfigPairwiseCipherActivated   = OAL_FALSE;

    }
}


void mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_pairwise_value)
{
    oal_uint8 uc_index;

    if (WLAN_80211_CIPHER_SUITE_CCMP == uc_pairwise_value)
    {
        uc_index = 0;
    }
    else if (WLAN_80211_CIPHER_SUITE_TKIP == uc_pairwise_value)
    {
        uc_index = 1;
    }
    else
    {
        MAC_ERR_VAR(pst_vap->uc_vap_id, "mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented pairwise_value[%d]: ERROR!", uc_pairwise_value);
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented::invalid uc_pairwise_value[%d].}", uc_pairwise_value);

        return;
    }

    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_index].uc_dot11RSNAConfigPairwiseCipherImplemented = uc_pairwise_value;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[uc_index].en_dot11RSNAConfigPairwiseCipherActivated = OAL_TRUE;
}


void mibset_RSNAClearWpa2PairwiseCipherImplemented(mac_vap_stru *pst_vap)
{
    oal_uint8 uc_index;

    for (uc_index = 0; uc_index < WLAN_PAIRWISE_CIPHER_SUITES; uc_index++)
    {
        pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_index].uc_dot11RSNAConfigPairwiseCipherImplemented = 0xFF;
        pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_index].en_dot11RSNAConfigPairwiseCipherActivated   = OAL_FALSE;
    }
}


void mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(mac_vap_stru *pst_vap, oal_uint8 uc_pairwise_value)
{
    oal_uint8 uc_index;

    if (WLAN_80211_CIPHER_SUITE_CCMP == uc_pairwise_value)
    {
        uc_index = 0;
    }
    else if (WLAN_80211_CIPHER_SUITE_TKIP == uc_pairwise_value)
    {
        uc_index = 1;
    }
    else
    {
        MAC_ERR_VAR(pst_vap->uc_vap_id, "mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented pairwise_value[%d]: ERROR!", uc_pairwise_value);
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented::invalid pairwise_value[%d].}", uc_pairwise_value);

        return;
    }

    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_index].uc_dot11RSNAConfigPairwiseCipherImplemented = uc_pairwise_value;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[uc_index].en_dot11RSNAConfigPairwiseCipherActivated   = OAL_TRUE;
}
/*****************************************************************************
 �� �� ��  : mac_vap_init_mib_11n
 ��������  : ��ʼ��11n��mib
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��25��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_mib_11n(mac_vap_stru  *pst_mac_vap)
{
    wlan_mib_ieee802dot11_stru    *pst_mib_info;
    mac_device_stru               *pst_dev;

    pst_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_dev)
    {
        MAC_WARNING_LOG(pst_mac_vap->uc_vap_id, "mac_vap_init_mib_11n: pst_dev is null ptr");
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_mib_11n::pst_dev null.}");

        return;
    }

    pst_mib_info = pst_mac_vap->pst_mib_info;

    pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = OAL_FALSE;

    pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionImplemented         = OAL_TRUE;
    pst_mib_info->st_phy_ht.en_dot11LDPCCodingOptionActivated           = OAL_TRUE;  /* Ĭ��ldpc && stbc���ܴ򿪣�����STA��Э��Э�� */
    pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionActivated               = HT_TX_STBC_DEFAULT_VALUE;
    /* pst_mib_info->st_phy_ht.en_dot11FortyMHzOperationImplemented        = OAL_FALSE; */
    pst_mib_info->st_phy_ht.en_dot112GFortyMHzOperationImplemented      = !pst_mac_vap->st_cap_flag.bit_disable_2ght40;
    pst_mib_info->st_phy_ht.en_dot115GFortyMHzOperationImplemented      = OAL_TRUE;

    /* SMPS���Ժ겻����ʱĬ�Ͼ�ΪPOWER_SAVE_MIMO */
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MIMOPowerSave          = WLAN_MIB_MIMO_POWER_SAVE_MIMO;

    pst_mib_info->st_phy_ht.en_dot11HTGreenfieldOptionImplemented       = HT_GREEN_FILED_DEFAULT_VALUE;
    pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented    = OAL_TRUE;
    pst_mib_info->st_phy_ht.en_dot112GShortGIOptionInFortyImplemented   = !pst_mac_vap->st_cap_flag.bit_disable_2ght40;
    pst_mib_info->st_phy_ht.en_dot115GShortGIOptionInFortyImplemented   = OAL_TRUE;
    pst_mib_info->st_phy_ht.en_dot11TxSTBCOptionImplemented             = pst_dev->bit_tx_stbc;
    pst_mib_info->st_phy_ht.en_dot11RxSTBCOptionImplemented             = (pst_dev->bit_rx_stbc == 0) ? OAL_FALSE : OAL_TRUE;
    pst_mib_info->st_phy_ht.ul_dot11NumberOfSpatialStreamsImplemented   = 2;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MaxAMSDULength         = 0;
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV) || defined(_PRE_PRODUCT_ID_HI110X_HOST))
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11LsigTxopProtectionOptionImplemented = OAL_FALSE;
#else
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11LsigTxopProtectionOptionImplemented = OAL_TRUE;
#endif

    pst_mib_info->st_wlan_mib_ht_sta_cfg.ul_dot11MaxRxAMPDUFactor       = 3;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.ul_dot11MinimumMPDUStartSpacing= 5;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11PCOOptionImplemented   = OAL_FALSE;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.ul_dot11TransitionTime         = 3;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11MCSFeedbackOptionImplemented = OAL_FALSE;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11HTControlFieldSupported= OAL_FALSE;
    pst_mib_info->st_wlan_mib_ht_sta_cfg.en_dot11RDResponderOptionImplemented = OAL_FALSE;
#ifdef _PRE_WLAN_FEATURE_TXBF
    /* txbf������Ϣ ע:11n bfee����Ŀǰȫ��0���պ�����ʵ����Ի�Ϊ�豸����,C01���� */
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11TransmitStaggerSoundingOptionImplemented = pst_dev->bit_su_bfmer;
#else
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11TransmitStaggerSoundingOptionImplemented = 0;
#endif
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ReceiveStaggerSoundingOptionImplemented  = 0;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ReceiveNDPOptionImplemented      = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11TransmitNDPOptionImplemented       = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ImplicitTransmitBeamformingOptionImplemented = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.uc_dot11CalibrationOptionImplemented      = 0;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ExplicitCSITransmitBeamformingOptionImplemented  = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.en_dot11ExplicitNonCompressedBeamformingMatrixOptionImplemented = OAL_FALSE;
    pst_mib_info->st_wlan_mib_txbf_config.uc_dot11ExplicitTransmitBeamformingCSIFeedbackOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_txbf_config.uc_dot11ExplicitNonCompressedBeamformingFeedbackOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_txbf_config.uc_dot11ExplicitCompressedBeamformingFeedbackOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_txbf_config.ul_dot11NumberBeamFormingCSISupportAntenna              = 0;
    pst_mib_info->st_wlan_mib_txbf_config.ul_dot11NumberNonCompressedBeamformingMatrixSupportAntenna     = 0;
    pst_mib_info->st_wlan_mib_txbf_config.ul_dot11NumberCompressedBeamformingMatrixSupportAntenna        = 0;

    /* ����ѡ��������Ϣ */
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11AntennaSelectionOptionImplemented              = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11TransmitExplicitCSIFeedbackASOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11TransmitIndicesFeedbackASOptionImplemented     = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11ExplicitCSIFeedbackASOptionImplemented         = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11TransmitExplicitCSIFeedbackASOptionImplemented = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11ReceiveAntennaSelectionOptionImplemented       = 0;
    pst_mib_info->st_wlan_mib_phy_antenna.en_dot11TransmitSoundingPPDUOptionImplemented          = 0;

    /* obss��Ϣ */
    mac_mib_init_obss_scan(pst_mac_vap);

    /*Ĭ��ʹ��2040����*/
     mac_mib_init_2040(pst_mac_vap);
}

/*****************************************************************************
 �� �� ��  : mac_vap_init_11ac_mcs_singlenss
 ��������  : ��ʼ��11ac mib��mcs��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��26��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_11ac_mcs_singlenss(
                wlan_mib_ieee802dot11_stru          *pst_mib_info,
                wlan_channel_bandwidth_enum_uint8    en_bandwidth)
{
    mac_tx_max_mcs_map_stru         *pst_tx_max_mcs_map;
    mac_rx_max_mcs_map_stru         *pst_rx_max_mcs_map;

    /* ��ȡmibֵָ�� */
    pst_rx_max_mcs_map = (mac_tx_max_mcs_map_stru *)(&(pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTRxMCSMap));
    pst_tx_max_mcs_map = (mac_tx_max_mcs_map_stru *)(&(pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTTxMCSMap));

    /* 20MHz���������£�֧��MCS0-MCS8 */
    if (WLAN_BAND_WIDTH_20M == en_bandwidth)
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_20M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_20M_11AC;
    }

    /* 40MHz���������£�֧��MCS0-MCS9 */
    else if ((WLAN_BAND_WIDTH_40MINUS == en_bandwidth) || (WLAN_BAND_WIDTH_40PLUS == en_bandwidth))
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_40M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_40M_11AC;
    }

    /* 80MHz���������£�֧��MCS0-MCS9 */
    else if ((WLAN_BAND_WIDTH_80MINUSMINUS == en_bandwidth)
             || (WLAN_BAND_WIDTH_80MINUSPLUS == en_bandwidth)
             || (WLAN_BAND_WIDTH_80PLUSMINUS == en_bandwidth)
             || (WLAN_BAND_WIDTH_80PLUSPLUS == en_bandwidth))
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_80M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_SINGLE_NSS_80M_11AC;
    }
}

/*****************************************************************************
 �� �� ��  : mac_vap_init_11ac_mcs_doublenss
 ��������  : ��ʼ��11ac mib��mcs��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��26��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_11ac_mcs_doublenss(
                wlan_mib_ieee802dot11_stru          *pst_mib_info,
                wlan_channel_bandwidth_enum_uint8    en_bandwidth)
{
    mac_tx_max_mcs_map_stru         *pst_tx_max_mcs_map;
    mac_rx_max_mcs_map_stru         *pst_rx_max_mcs_map;

    /* ��ȡmibֵָ�� */
    pst_rx_max_mcs_map = (mac_tx_max_mcs_map_stru *)(&(pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTRxMCSMap));
    pst_tx_max_mcs_map = (mac_tx_max_mcs_map_stru *)(&(pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTTxMCSMap));

    /* 20MHz���������£�֧��MCS0-MCS8 */
    if (WLAN_BAND_WIDTH_20M == en_bandwidth)
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_rx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS8_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_20M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_20M_11AC;
    }

    /* 40MHz���������£�֧��MCS0-MCS9 */
    else if ((WLAN_BAND_WIDTH_40MINUS == en_bandwidth) || (WLAN_BAND_WIDTH_40PLUS == en_bandwidth))
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_rx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_40M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_40M_11AC;
    }

    /* 80MHz���������£�֧��MCS0-MCS9 */
    else if ((WLAN_BAND_WIDTH_80MINUSMINUS == en_bandwidth)
             || (WLAN_BAND_WIDTH_80MINUSPLUS== en_bandwidth)
             || (WLAN_BAND_WIDTH_80PLUSMINUS== en_bandwidth)
             || (WLAN_BAND_WIDTH_80PLUSPLUS== en_bandwidth))
    {
        pst_rx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_rx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_1ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_tx_max_mcs_map->us_max_mcs_2ss = MAC_MAX_SUP_MCS9_11AC_EACH_NSS;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTRxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_80M_11AC;
        pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTTxHighestDataRateSupported = MAC_MAX_RATE_DOUBLE_NSS_80M_11AC;
    }

}

/*****************************************************************************
 �� �� ��  : mac_vap_init_mib_11ac
 ��������  : ��ʼ��11ac mib��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_mib_11ac(mac_vap_stru  *pst_mac_vap)
{
    wlan_mib_ieee802dot11_stru      *pst_mib_info;
    mac_device_stru                 *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_mib_11ac::pst_mac_dev[%d] null.}", pst_mac_vap->uc_device_id);

        return;
    }

    pst_mib_info = pst_mac_vap->pst_mib_info;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented = OAL_TRUE;

    pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11MaxMPDULength                      = WLAN_MIB_VHT_MPDU_11454;
    pst_mib_info->st_wlan_mib_phy_vht.uc_dot11VHTChannelWidthOptionImplemented          = WLAN_MIB_VHT_SUPP_WIDTH_80;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTLDPCCodingOptionImplemented            = pst_mac_dev->bit_ldpc_coding;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented           = OAL_TRUE;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn160and80p80Implemented  = OAL_FALSE;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTTxSTBCOptionImplemented                = pst_mac_dev->bit_tx_stbc;
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTRxSTBCOptionImplemented                = (pst_mac_dev->bit_rx_stbc == 0) ? OAL_FALSE : OAL_TRUE;
    pst_mib_info->st_wlan_mib_vht_txbf_config.en_dot11VHTSUBeamformerOptionImplemented  = pst_mac_dev->bit_su_bfmer;
    pst_mib_info->st_wlan_mib_vht_txbf_config.en_dot11VHTSUBeamformeeOptionImplemented  = pst_mac_dev->bit_su_bfmee;

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_mib_info->st_wlan_mib_vht_txbf_config.ul_dot11VHTNumberSoundingDimensions       = pst_mac_dev->uc_tx_chain - 1;
#else
    pst_mib_info->st_wlan_mib_vht_txbf_config.ul_dot11VHTNumberSoundingDimensions       = 0;
#endif
    pst_mib_info->st_wlan_mib_vht_txbf_config.en_dot11VHTMUBeamformerOptionImplemented  = OAL_FALSE;
    pst_mib_info->st_wlan_mib_vht_txbf_config.en_dot11VHTMUBeamformeeOptionImplemented  = pst_mac_dev->bit_mu_bfmee;
    pst_mib_info->st_wlan_mib_vht_txbf_config.ul_dot11VHTBeamformeeNTxSupport           = 1;
#ifdef _PRE_WLAN_FEATURE_TXOPPS
    pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTTXOPPowerSaveOptionImplemented  = OAL_TRUE;
#endif
    pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTControlFieldSupported           = OAL_FALSE;
    pst_mib_info->st_wlan_mib_vht_sta_config.ul_dot11VHTMaxRxAMPDUFactor                = 7;            /* 2^(13+1)-1�ֽ� */
#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    pst_mib_info->st_wlan_mib_sta_config.en_dot11OperatingModeNotificationImplemented   = OAL_TRUE;
#endif
}
/*****************************************************************************
 �� �� ��  : mac_vap_init_mib_11i
 ��������  : ��ʼ��11i mib��Ϣ
 �������  : pst_vap ָ��VAP�û���ָ��
 �������  :
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��29��
    ��    ��   : kangguochang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_init_mib_11i(mac_vap_stru  *pst_vap)
{
    oal_uint8 uc_idx;

    /* Ԥ����֤����Ĭ��ΪFALSE����RSN CAP���ʱ��Ҫ�ж� */
    pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RSNAPreauthenticationImplemented = OAL_FALSE;

    /* WEP��WAPI���ܷ�ʽʱ��IBSS����Ҫȥʹ�� */
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated                   = OAL_FALSE;
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR                        = OAL_FALSE;
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC                        = OAL_FALSE;
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAPreauthenticationActivated  = OAL_FALSE;
    pst_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked                  = OAL_FALSE;

    /* Version��ϢΪ1 */
    /* see <80211-2012> chapter 8.4.2.27 RSN elemet  */
    /* RSN Version 1 is defined in this standard */
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigVersion = MAC_RSN_IE_VERSION;

    if (OAL_TRUE == pst_vap->st_cap_flag.bit_wpa2)
    {
        pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher = WLAN_80211_CIPHER_SUITE_CCMP;
    }

    if(OAL_TRUE == pst_vap->st_cap_flag.bit_wpa)
    {
        pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher = WLAN_80211_CIPHER_SUITE_TKIP;
    }

    if (WLAN_80211_CIPHER_SUITE_TKIP == pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher)
    {//WPA
        /* TKIP���ܷ�ʽ��GTK��bitλΪ256 */
        pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize = WLAN_TKIP_KEY_LEN * 8;
    }
    else if(WLAN_80211_CIPHER_SUITE_CCMP == pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher)
    {//WPA2
        /* CCMP���ܷ�ʽ��GTK��bitλΪ256 */
        pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigGroupCipherSize = WLAN_CCMP_KEY_LEN * 8;
    }

    /* ����ѡ���AKM Suite����, ��ʼ��ΪPSK */
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteSelected   = WLAN_AUTH_SUITE_PSK;

    /* ����ѡ���Pairwise Cipher����, CCMP */
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherSelected        = WLAN_80211_CIPHER_SUITE_CCMP;

    /* ����ѡ���Group Cipher����, ��ʼ��ΪPSK */
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherSelected = pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher;

    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAAuthenticationSuiteRequested  = 0;
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAPairwiseCipherRequested       = 0;
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAGroupCipherRequested          = 0;

    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNA4WayHandshakeFailures         = 0;

    /* wpa PairwiseCipher CCMP */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[0].ul_dot11RSNAConfigPairwiseCipherIndex            = 1;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[0].uc_dot11RSNAConfigPairwiseCipherImplemented      = WLAN_80211_CIPHER_SUITE_CCMP;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[0].ul_dot11RSNAConfigPairwiseCipherSizeImplemented  = WLAN_CCMP_KEY_LEN * 8;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[0].en_dot11RSNAConfigPairwiseCipherActivated        = OAL_FALSE;


    /* wpa PairwiseCipher TKIP */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[1].ul_dot11RSNAConfigPairwiseCipherIndex            = 2;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[1].uc_dot11RSNAConfigPairwiseCipherImplemented      = WLAN_80211_CIPHER_SUITE_TKIP;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[1].ul_dot11RSNAConfigPairwiseCipherSizeImplemented  = WLAN_TKIP_KEY_LEN * 8;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[1].en_dot11RSNAConfigPairwiseCipherActivated        = OAL_FALSE;

    /* wpa2 PairwiseCipher CCMP */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[0].ul_dot11RSNAConfigPairwiseCipherIndex            = 1;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[0].uc_dot11RSNAConfigPairwiseCipherImplemented      = WLAN_80211_CIPHER_SUITE_CCMP;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[0].ul_dot11RSNAConfigPairwiseCipherSizeImplemented  = WLAN_CCMP_KEY_LEN * 8;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[0].en_dot11RSNAConfigPairwiseCipherActivated        = OAL_FALSE;


    /* wpa2 PairwiseCipher TKIP */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[1].ul_dot11RSNAConfigPairwiseCipherIndex            = 2;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[1].uc_dot11RSNAConfigPairwiseCipherImplemented      = WLAN_80211_CIPHER_SUITE_TKIP;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[1].ul_dot11RSNAConfigPairwiseCipherSizeImplemented  = WLAN_TKIP_KEY_LEN * 8;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[1].en_dot11RSNAConfigPairwiseCipherActivated        = OAL_FALSE;

    /* AuthenticationSuite */
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[0].ul_dot11RSNAConfigAuthenticationSuiteIndex       = 1;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[0].uc_dot11RSNAConfigAuthenticationSuiteImplemented = WLAN_AUTH_SUITE_PSK;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[0].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_FALSE;

    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[1].ul_dot11RSNAConfigAuthenticationSuiteIndex       = 2;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[1].uc_dot11RSNAConfigAuthenticationSuiteImplemented = WLAN_AUTH_SUITE_PSK_SHA256;
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[1].en_dot11RSNAConfigAuthenticationSuiteActivated   = OAL_FALSE;



    /* ��ʼ���鲥�û���Ϣ */
    mac_vap_init_rsna_status(pst_vap, 0);
    oal_memset(pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[0].auc_dot11RSNAStatsSTAAddress, 0xFF, 6);
    pst_vap->pst_mib_info->ast_wlan_mib_rsna_status[0].uc_dot11RSNAStatsSelectedPairwiseCipher = pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.uc_dot11RSNAConfigGroupCipher;

    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigNumberOfPTKSAReplayCountersImplemented = 0;
    pst_vap->pst_mib_info->st_wlan_mib_rsna_cfg.ul_dot11RSNAConfigNumberOfGTKSAReplayCountersImplemented = 0;

    /* ��ʼ�������û���Ϣ */
    for(uc_idx = 1; uc_idx < (WLAN_ASSOC_USER_MAX_NUM_LIMIT + 1); uc_idx++)
    {
        mac_vap_init_rsna_status(pst_vap, uc_idx);
    }

}

#ifdef _PRE_WLAN_FEATURE_11K
OAL_STATIC oal_void  mac_vap_init_mib_11k(mac_vap_stru  *pst_vap)
{
    pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RadioMeasurementActivated = OAL_TRUE;

    pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RMBeaconActiveMeasurementActivated    = OAL_TRUE;
    pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RMBeaconPassiveMeasurementActivated   = OAL_TRUE;
    pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RMBeaconTableMeasurementActivated     = OAL_TRUE;
    pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RMLinkMeasurementActivated            = OAL_TRUE;
    //pst_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11RMNeighborReportActivated             = OAL_TRUE;

    pst_vap->pst_mib_info->st_wlan_mib_sta_config.ul_dot11RMMaxMeasurementDuration              = 1200; //1.2s
}
#endif
/*****************************************************************************
�� �� ��  : mac_vap_init_legacy_rates
��������  : ��ʼ��11a 11g����
�������  :
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_legacy_rates(mac_vap_stru *pst_vap,mac_data_rate_stru *pst_rates)
{
    oal_uint8                      uc_rate_index;
    oal_uint8                      uc_curr_rate_index = 0;
    mac_data_rate_stru            *puc_orig_rate;
    mac_data_rate_stru            *puc_curr_rate;
    oal_uint8                      uc_rates_num;

    /* ��ʼ�����ʼ� */
    uc_rates_num = MAC_DATARATES_PHY_80211G_NUM;

    /* ��ʼ�����ʸ������������ʸ������ǻ������ʸ��� */
    pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates = MAC_NUM_DR_802_11A;
    pst_vap->st_curr_sup_rates.uc_br_rate_num       = MAC_NUM_BR_802_11A;
    pst_vap->st_curr_sup_rates.uc_nbr_rate_num      = MAC_NUM_NBR_802_11A;
    pst_vap->st_curr_sup_rates.uc_min_rate          = 6;
    pst_vap->st_curr_sup_rates.uc_max_rate          = 24;

    /* �����ʿ�����VAP�ṹ���µ����ʼ��� */
    for (uc_rate_index = 0; uc_rate_index < uc_rates_num; uc_rate_index++)
    {
        puc_orig_rate = &pst_rates[uc_rate_index];
        puc_curr_rate = &(pst_vap->st_curr_sup_rates.st_rate.ast_rs_rates[uc_curr_rate_index]);

        /* Basic Rates */
        if ((puc_orig_rate->uc_mbps == 6)
            || (puc_orig_rate->uc_mbps == 12)
            || (puc_orig_rate->uc_mbps == 24))
        {
            oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));
            puc_curr_rate->uc_mac_rate |= 0x80;
            uc_curr_rate_index++;
        }

        /* Non-basic rates */
        else if ((puc_orig_rate->uc_mbps== 9)
                || (puc_orig_rate->uc_mbps == 18)
                || (puc_orig_rate->uc_mbps == 36)
                || (puc_orig_rate->uc_mbps == 48)
                || (puc_orig_rate->uc_mbps == 54))
        {
            oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));
            uc_curr_rate_index++;
        }

        if (uc_curr_rate_index == pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates)
        {
            break;
        }
    }
}

/*****************************************************************************
�� �� ��  : mac_vap_init_11b_rates
��������  : ��ʼ��11b����
�������  :
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11b_rates(mac_vap_stru *pst_vap,mac_data_rate_stru *pst_rates)
{
    oal_uint8                      uc_rate_index;
    oal_uint8                      uc_curr_rate_index = 0;
    mac_data_rate_stru            *puc_orig_rate;
    mac_data_rate_stru            *puc_curr_rate;
    oal_uint8                      uc_rates_num;

    /* ��ʼ�����ʼ� */
    uc_rates_num = MAC_DATARATES_PHY_80211G_NUM;

    /* ��ʼ�����ʸ������������ʸ������ǻ������ʸ��� */
    pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates = MAC_NUM_DR_802_11B;
    pst_vap->st_curr_sup_rates.uc_br_rate_num       = 0;
    pst_vap->st_curr_sup_rates.uc_nbr_rate_num      = MAC_NUM_NBR_802_11B;
    pst_vap->st_curr_sup_rates.uc_min_rate          = 1;
    pst_vap->st_curr_sup_rates.uc_max_rate          = 2;

    /* �����ʿ�����VAP�ṹ���µ����ʼ��� */
    for (uc_rate_index = 0; uc_rate_index < uc_rates_num; uc_rate_index++)
    {
        puc_orig_rate = &pst_rates[uc_rate_index];
        puc_curr_rate = &(pst_vap->st_curr_sup_rates.st_rate.ast_rs_rates[uc_curr_rate_index]);

        /*  Basic Rates  */
        if ((puc_orig_rate->uc_mbps == 1) || (puc_orig_rate->uc_mbps == 2)
           || ((WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode) && ((puc_orig_rate->uc_mbps == 5) || (puc_orig_rate->uc_mbps == 11))))
        {
            pst_vap->st_curr_sup_rates.uc_br_rate_num++;
            oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));
            puc_curr_rate->uc_mac_rate |= 0x80;
            uc_curr_rate_index++;
        }

        /* Non-basic rates */
        else if ((WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode)
                && ((puc_orig_rate->uc_mbps == 5) || (puc_orig_rate->uc_mbps == 11)))
        {
            oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));
            uc_curr_rate_index++;
        }
        else
        {
            continue;
        }

        if (uc_curr_rate_index == pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates)
        {
            break;
        }
    }
}

/*****************************************************************************
�� �� ��  : mac_vap_init_11g_mixed_one_rates
��������  : ��ʼ��11b����
�������  :
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11g_mixed_one_rates(mac_vap_stru *pst_vap,mac_data_rate_stru *pst_rates)
{
    oal_uint8                      uc_rate_index;
    mac_data_rate_stru            *puc_orig_rate;
    mac_data_rate_stru            *puc_curr_rate;
    oal_uint8                      uc_rates_num;

    /* ��ʼ�����ʼ� */
    uc_rates_num = MAC_DATARATES_PHY_80211G_NUM;

    /* ��ʼ�����ʸ������������ʸ������ǻ������ʸ��� */
    pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates = MAC_NUM_DR_802_11G_MIXED;
    pst_vap->st_curr_sup_rates.uc_br_rate_num       = MAC_NUM_BR_802_11G_MIXED_ONE;
    pst_vap->st_curr_sup_rates.uc_nbr_rate_num      = MAC_NUM_NBR_802_11G_MIXED_ONE;
    pst_vap->st_curr_sup_rates.uc_min_rate          = 1;
    pst_vap->st_curr_sup_rates.uc_max_rate          = 11;

    /* �����ʿ�����VAP�ṹ���µ����ʼ��� */
    for (uc_rate_index = 0; uc_rate_index < uc_rates_num; uc_rate_index++)
    {
        puc_orig_rate = &pst_rates[uc_rate_index];
        puc_curr_rate = &(pst_vap->st_curr_sup_rates.st_rate.ast_rs_rates[uc_rate_index]);

        oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));

        /* Basic Rates */
        if ((puc_orig_rate->uc_mbps== 1)
            || (puc_orig_rate->uc_mbps == 2)
            || (puc_orig_rate->uc_mbps == 5)
            || (puc_orig_rate->uc_mbps == 11))
        {
            puc_curr_rate->uc_mac_rate |= 0x80;
        }
    }
}

/*****************************************************************************
�� �� ��  : mac_vap_init_11g_mixed_two_rates
��������  : ��ʼ��11g mixed two����
�������  :
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11g_mixed_two_rates(mac_vap_stru *pst_vap,mac_data_rate_stru *pst_rates)
{
    oal_uint8                      uc_rate_index;
    mac_data_rate_stru            *puc_orig_rate;
    mac_data_rate_stru            *puc_curr_rate;
    oal_uint8                      uc_rates_num;

    /* ��ʼ�����ʼ� */
    uc_rates_num = MAC_DATARATES_PHY_80211G_NUM;

    /* ��ʼ�����ʸ������������ʸ������ǻ������ʸ��� */
    pst_vap->st_curr_sup_rates.st_rate.uc_rs_nrates = MAC_NUM_DR_802_11G_MIXED;
    pst_vap->st_curr_sup_rates.uc_br_rate_num       = MAC_NUM_BR_802_11G_MIXED_TWO;
    pst_vap->st_curr_sup_rates.uc_nbr_rate_num      = MAC_NUM_NBR_802_11G_MIXED_TWO;
    pst_vap->st_curr_sup_rates.uc_min_rate          = 1;
    pst_vap->st_curr_sup_rates.uc_max_rate          = 24;

    /* �����ʿ�����VAP�ṹ���µ����ʼ��� */
    for (uc_rate_index = 0; uc_rate_index < uc_rates_num; uc_rate_index++)
    {
        puc_orig_rate = &pst_rates[uc_rate_index];
        puc_curr_rate = &(pst_vap->st_curr_sup_rates.st_rate.ast_rs_rates[uc_rate_index]);

        oal_memcopy(puc_curr_rate,puc_orig_rate,sizeof(mac_data_rate_stru));

        /* Basic Rates */
        if ((puc_orig_rate->uc_mbps== 1)
            || (puc_orig_rate->uc_mbps == 2)
            || (puc_orig_rate->uc_mbps == 5)
            || (puc_orig_rate->uc_mbps == 11)
            || (puc_orig_rate->uc_mbps == 6)
            || (puc_orig_rate->uc_mbps == 12)
            || (puc_orig_rate->uc_mbps == 24))
        {
            puc_curr_rate->uc_mac_rate |= 0x80;
        }
    }
}

/*****************************************************************************
�� �� ��  : mac_vap_init_11n_rates
��������  : ��ʼ��11n����
�������  :
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11n_rates(mac_vap_stru *pst_mac_vap,mac_device_stru *pst_mac_dev)
{
    wlan_mib_ieee802dot11_stru    *pst_mib_info;

    pst_mib_info = pst_mac_vap->pst_mib_info;
    /* ��ʼ�����ʼ� */

    /* MCS���MIBֵ��ʼ�� */
    pst_mib_info->st_phy_ht.en_dot11TxMCSSetDefined              = OAL_TRUE;
    pst_mib_info->st_phy_ht.en_dot11TxRxMCSSetNotEqual           = OAL_FALSE;
    pst_mib_info->st_phy_ht.en_dot11TxUnequalModulationSupported = OAL_FALSE;

    /* ��MIBֵ��MCS MAP���� */
    OAL_MEMZERO(pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue, WLAN_HT_MCS_BITMASK_LEN);

    /* 1���ռ��� */
    if (WLAN_SINGLE_NSS == pst_mac_dev->en_nss_num)
    {
        pst_mib_info->st_phy_ht.ul_dot11TxMaximumNumberSpatialStreamsSupported = 1;
        pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[0] = 0xFF; /* ֧�� RX MCS 0-7��8λȫ��Ϊ1*/
        pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[0] = 0xFF; /* ֧�� TX MCS 0-7��8λȫ��Ϊ1*/

        pst_mib_info->st_phy_ht.ul_dot11HighestSupportedDataRate = MAC_MAX_RATE_SINGLE_NSS_20M_11N;

        if ((WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth) || (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth))
        {
            /* 40M ֧��MCS32 */
            pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[4] = (oal_uint8)0x01;  /* ֧�� RX MCS 32,���һλΪ1 */
            pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[4] = (oal_uint8)0x01;  /* ֧�� RX MCS 32,���һλΪ1 */
            pst_mib_info->st_phy_ht.ul_dot11HighestSupportedDataRate = MAC_MAX_RATE_SINGLE_NSS_40M_11N;
        }
    }

    /* 2���ռ��� */
    else if (WLAN_DOUBLE_NSS == pst_mac_dev->en_nss_num)
    {
        pst_mib_info->st_phy_ht.ul_dot11TxMaximumNumberSpatialStreamsSupported = 2;
        pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[0] = 0xFF;  /* ֧�� RX MCS 0-7��8λȫ��Ϊ1*/
        pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[1] = 0xFF;  /* ֧�� RX MCS 8-15��8λȫ��Ϊ1*/

        pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[0] = 0xFF;  /* ֧�� TX MCS 0-7��8λȫ��Ϊ1*/
        pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[1] = 0xFF;  /* ֧�� TX MCS 8-15��8λȫ��Ϊ1*/

        pst_mib_info->st_phy_ht.ul_dot11HighestSupportedDataRate = MAC_MAX_RATE_DOUBLE_NSS_20M_11N;

        if ((WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth) || (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth))
        {
            /* 40M ֧�ֵ��������Ϊ300M */
            pst_mib_info->st_supported_mcsrx.auc_dot11SupportedMCSRxValue[4] = (oal_uint8)0x01;  /* ֧�� RX MCS 32,���һλΪ1 */
            pst_mib_info->st_supported_mcstx.auc_dot11SupportedMCSTxValue[4] = (oal_uint8)0x01;  /* ֧�� RX MCS 32,���һλΪ1 */
            pst_mib_info->st_phy_ht.ul_dot11HighestSupportedDataRate = MAC_MAX_RATE_DOUBLE_NSS_40M_11N;
        }
    }
}

/*****************************************************************************
�� �� ��  : mac_vap_init_11ac_rates
��������  : ��ʼ��11n����
�������  :
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2013��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void mac_vap_init_11ac_rates(mac_vap_stru *pst_mac_vap,mac_device_stru *pst_mac_dev)
{
    wlan_mib_ieee802dot11_stru    *pst_mib_info;

    pst_mib_info = pst_mac_vap->pst_mib_info;

    /* �Ƚ�TX RX MCSMAP��ʼ��Ϊ���пռ�������֧�� 0xFFFF*/
    pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTRxMCSMap = 0xFFFF;
    pst_mib_info->st_wlan_mib_vht_sta_config.us_dot11VHTTxMCSMap = 0xFFFF;

    if (WLAN_SINGLE_NSS == pst_mac_dev->en_nss_num)
    {
        /* 1���ռ�������� */
        mac_vap_init_11ac_mcs_singlenss(pst_mib_info, pst_mac_vap->st_channel.en_bandwidth);
    }
    else if (WLAN_DOUBLE_NSS == pst_mac_dev->en_nss_num)
    {
        /* 2���ռ�������� */
        mac_vap_init_11ac_mcs_doublenss(pst_mib_info, pst_mac_vap->st_channel.en_bandwidth);
    }
    else
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_11ac_rates::invalid en_nss_num[%d].}", pst_mac_dev->en_nss_num);
    }
}

/*****************************************************************************
 �� �� ��  : mac_vap_init_p2p_rates
 ��������  : ��ʼ��p2p vap�����ʼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_init_p2p_rates(mac_vap_stru *pst_vap, wlan_protocol_enum_uint8 en_vap_protocol, mac_data_rate_stru  *pst_rates)
{
    mac_device_stru               *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_p2p_rates::pst_mac_dev[%d] null.}", pst_vap->uc_device_id);

        return;
    }

    mac_vap_init_legacy_rates(pst_vap, pst_rates);

    /* begin:DTS2015041102828 1102 ��listen channel��probe respons Я�����ʼ����ظ�IE.  */
    oal_memcopy(&pst_vap->ast_sta_sup_rates_ie[WLAN_BAND_5G], &pst_vap->st_curr_sup_rates, OAL_SIZEOF(pst_vap->st_curr_sup_rates));
    oal_memcopy(&pst_vap->ast_sta_sup_rates_ie[WLAN_BAND_2G], &pst_vap->st_curr_sup_rates, OAL_SIZEOF(pst_vap->st_curr_sup_rates));
    /* end:DTS2015041102828 1102 ��listen channel��probe respons Я�����ʼ����ظ�IE.  */

    if (WLAN_VHT_MODE == en_vap_protocol)
    {
        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
        mac_vap_init_11ac_rates(pst_vap, pst_mac_dev);
    }
    else
    {
        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
    }
}

oal_void mac_vap_init_rates_by_protocol(mac_vap_stru *pst_vap, wlan_protocol_enum_uint8 en_vap_protocol, mac_data_rate_stru *pst_rates)
{
    mac_device_stru *pst_mac_dev;

    pst_mac_dev = (mac_device_stru *)mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_rates_by_protocol::mac_res_get_dev fail.device_id:[%d].}", pst_vap->uc_device_id);
        return;
    }

    /* STAģʽĬ��Э��ģʽ��11ac����ʼ�����ʼ�Ϊ�������ʼ� */
#ifdef _PRE_WLAN_FEATURE_P2P
    if (!IS_LEGACY_VAP(pst_vap))
    {
        mac_vap_init_p2p_rates(pst_vap, en_vap_protocol, pst_rates);
        return;
    }
#endif
    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode && WLAN_VHT_MODE == en_vap_protocol)
    {
        /* ����STAȫ�ŵ�ɨ�� 5Gʱ ��д֧�����ʼ�ie */
        mac_vap_init_legacy_rates(pst_vap, pst_rates);
        oal_memcopy(&pst_vap->ast_sta_sup_rates_ie[WLAN_BAND_5G], &pst_vap->st_curr_sup_rates, OAL_SIZEOF(pst_vap->st_curr_sup_rates));

        /* ����STAȫ�ŵ�ɨ�� 2Gʱ ��д֧�����ʼ�ie */
        mac_vap_init_11g_mixed_one_rates(pst_vap, pst_rates);
        oal_memcopy(&pst_vap->ast_sta_sup_rates_ie[WLAN_BAND_2G], &pst_vap->st_curr_sup_rates, OAL_SIZEOF(pst_vap->st_curr_sup_rates));

        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
        mac_vap_init_11ac_rates(pst_vap, pst_mac_dev);
    }
    else if ((WLAN_VHT_ONLY_MODE == en_vap_protocol) || (WLAN_VHT_MODE == en_vap_protocol))
    {
#ifdef _PRE_WLAN_FEATURE_11AC2G
        if (WLAN_BAND_2G == pst_vap->st_channel.en_band)
        {
            mac_vap_init_11g_mixed_one_rates(pst_vap, pst_rates);
        }
        else
        {
            mac_vap_init_legacy_rates(pst_vap, pst_rates);
        }
#else
        mac_vap_init_legacy_rates(pst_vap, pst_rates);
#endif
        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
        mac_vap_init_11ac_rates(pst_vap, pst_mac_dev);
    }
    else if ((WLAN_HT_ONLY_MODE == en_vap_protocol) || (WLAN_HT_MODE == en_vap_protocol))
    {
        if (WLAN_BAND_5G == pst_vap->st_channel.en_band)
        {
            mac_vap_init_legacy_rates(pst_vap, pst_rates);
        }
        else if (WLAN_BAND_2G == pst_vap->st_channel.en_band)
        {
            mac_vap_init_11g_mixed_one_rates(pst_vap, pst_rates);
        }

        mac_vap_init_11n_rates(pst_vap, pst_mac_dev);
    }
    else if ((WLAN_LEGACY_11A_MODE == en_vap_protocol) || (WLAN_LEGACY_11G_MODE == en_vap_protocol))
    {
        mac_vap_init_legacy_rates(pst_vap, pst_rates);
    }
    else if (WLAN_LEGACY_11B_MODE == en_vap_protocol)
    {
        mac_vap_init_11b_rates(pst_vap, pst_rates);
    }
    else if (WLAN_MIXED_ONE_11G_MODE == en_vap_protocol)
    {
        mac_vap_init_11g_mixed_one_rates(pst_vap, pst_rates);
    }
    else if (WLAN_MIXED_TWO_11G_MODE == en_vap_protocol)
    {
        mac_vap_init_11g_mixed_two_rates(pst_vap, pst_rates);
    }
    else
    {
        /* ��ʱ������ */
    }
}

/*****************************************************************************
�� �� ��  : mac_vap_init_rates
��������  : ��ʼ�����ʼ�
�������  :
�������  :
�� �� ֵ  : ������
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2013��7��30��
   ��    ��   : zhangyu
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��11��6��
   ��    ��   : y00184180 yaorui
   �޸�����   : �޸Ĳ�ͬЭ��ģʽ���ʳ�ʼ��

*****************************************************************************/
oal_void mac_vap_init_rates(mac_vap_stru *pst_vap)
{
    mac_device_stru               *pst_mac_dev;
    wlan_protocol_enum_uint8       en_vap_protocol;
    mac_data_rate_stru            *pst_rates;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_rates::pst_mac_dev[%d] null.}", pst_vap->uc_device_id);

        return;
    }

    /* ��ʼ�����ʼ� */
    pst_rates   = mac_device_get_all_rates(pst_mac_dev);

    en_vap_protocol = pst_vap->en_protocol;

    mac_vap_init_rates_by_protocol(pst_vap, en_vap_protocol, pst_rates);

}

/*****************************************************************************
�� �� ��  : mac_sta_init_bss_rates
��������  : STA��ʼ�����ʼ�
�������  :
�������  :
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2015��5��30��
   ��    ��   : s00304087
   �޸�����   : �����ɺ���
*****************************************************************************/
oal_void mac_sta_init_bss_rates(mac_vap_stru *pst_vap, oal_void *pst_bss_dscr)
{
    mac_device_stru               *pst_mac_dev;
    wlan_protocol_enum_uint8       en_vap_protocol;
    mac_data_rate_stru            *pst_rates;
    oal_uint32                     i,j;
    mac_bss_dscr_stru             *pst_bss = (mac_bss_dscr_stru *)pst_bss_dscr;

    pst_mac_dev = mac_res_get_dev(pst_vap->uc_device_id);

    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init_rates::pst_mac_dev[%d] null.}", pst_vap->uc_device_id);

        return;
    }


    /* ��ʼ�����ʼ� */
    pst_rates   = mac_device_get_all_rates(pst_mac_dev);
    if(OAL_PTR_NULL != pst_bss)
    {
        for(i = 0; i < pst_bss->uc_num_supp_rates; i++)
        {
            for(j = 0; j < MAC_DATARATES_PHY_80211G_NUM; j++)
            {
                if((pst_rates[j].uc_mac_rate & 0x7f) == (pst_bss->auc_supp_rates[i] & 0x7f))
                {
                    pst_rates[j].uc_mac_rate = pst_bss->auc_supp_rates[i];
                    break;
                }
            }
        }
    }

    en_vap_protocol = pst_vap->en_protocol;

    mac_vap_init_rates_by_protocol(pst_vap, en_vap_protocol, pst_rates);
}

#if 0
#ifdef _PRE_WLAN_DFT_STAT
/*****************************************************************************
 �� �� ��  : mac_vap_dft_stat_init
 ��������  : ��ʼ��vap����ͳ�Ƶ���Դ
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
OAL_STATIC oal_uint32  mac_vap_dft_stat_init(mac_vap_stru *pst_vap)
{
    OAL_MEMZERO(&pst_vap->st_vap_dft, OAL_SIZEOF(mac_vap_dft_stru));

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : mac_vap_dft_stat_clear
 ��������  : ���vap����ͳ����Դ
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
oal_uint32  mac_vap_dft_stat_clear(mac_vap_stru *pst_vap)
{
    pst_vap->st_vap_dft.ul_flg = 0;

    if (OAL_TRUE == pst_vap->st_vap_dft.st_vap_dft_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_vap->st_vap_dft.st_vap_dft_timer);
    }

    if (OAL_PTR_NULL != pst_vap->st_vap_dft.pst_vap_dft_stats)
    {
        OAL_MEM_FREE(pst_vap->st_vap_dft.pst_vap_dft_stats, OAL_TRUE);
    }

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 �� �� ��  : mac_vap_set_tx_power
 ��������  : ����vap�ķ��͹���
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_tx_power(mac_vap_stru *pst_vap, oal_uint8 uc_tx_power)
{
    pst_vap->uc_tx_power = uc_tx_power;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_aid
 ��������  : ����vap��aid
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_aid(mac_vap_stru *pst_vap, oal_uint16 us_aid)
{
    pst_vap->us_sta_aid = us_aid;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_assoc_id
 ��������  : ����vap��assoc_vap_id �ò���ֻ��STA��Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_assoc_id(mac_vap_stru *pst_vap, oal_uint8 uc_assoc_vap_id)
{
    pst_vap->uc_assoc_vap_id = uc_assoc_vap_id;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_uapsd_cap
 ��������  : ����vap��assoc_vap_id �ò���ֻ��STA��Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_uapsd_cap(mac_vap_stru *pst_vap, oal_uint8 uc_uapsd_cap)
{
    pst_vap->uc_uapsd_cap = uc_uapsd_cap;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_p2p_mode
 ��������  : ����vap��p2pģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_p2p_mode(mac_vap_stru *pst_vap, wlan_p2p_mode_enum_uint8 en_p2p_mode)
{
    pst_vap->en_p2p_mode = en_p2p_mode;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_multi_user_idx
 ��������  : ����vap���鲥�û�id
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_multi_user_idx(mac_vap_stru *pst_vap, oal_uint16 us_multi_user_idx)
{
    pst_vap->us_multi_user_idx = us_multi_user_idx;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_rx_nss
 ��������  : ����vap�Ľ���nss
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_rx_nss(mac_vap_stru *pst_vap, oal_uint8 uc_rx_nss)
{
    pst_vap->en_vap_rx_nss = uc_rx_nss;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_al_tx_payload_flag
 ��������  : ����vap�ĳ���payload����
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_al_tx_payload_flag(mac_vap_stru *pst_vap, oal_uint8 uc_paylod)
{
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    pst_vap->bit_payload_flag = uc_paylod;
#endif
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_al_tx_flag
 ��������  : ����vap�ĳ���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_al_tx_flag(mac_vap_stru *pst_vap, oal_bool_enum_uint8 en_flag)
{
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    pst_vap->bit_al_tx_flag = en_flag;
#endif
}

/*****************************************************************************
 �� �� ��  : mac_set_al_tx_first_run
 ��������  : ����vap�ĳ���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_al_tx_first_run(mac_vap_stru *pst_vap, oal_bool_enum_uint8 en_flag)
{
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    pst_vap->bit_first_run = en_flag;
#endif
}

#ifdef _PRE_WLAN_FEATURE_STA_PM
/*****************************************************************************
 �� �� ��  : mac_vap_set_uapsd_para
 ��������  : ����vap��uapsd����
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_uapsd_para(mac_vap_stru *pst_mac_vap, mac_cfg_uapsd_sta_stru *pst_uapsd_info)
{
    oal_uint8                 uc_ac;

    pst_mac_vap->st_sta_uapsd_cfg.uc_max_sp_len = pst_uapsd_info->uc_max_sp_len;

    for (uc_ac = 0; uc_ac < WLAN_WME_AC_BUTT; uc_ac++)
    {
        pst_mac_vap->st_sta_uapsd_cfg.uc_delivery_enabled[uc_ac] = pst_uapsd_info->uc_delivery_enabled[uc_ac];
        pst_mac_vap->st_sta_uapsd_cfg.uc_trigger_enabled[uc_ac]  = pst_uapsd_info->uc_trigger_enabled[uc_ac];
    }

}
#endif

/*****************************************************************************
 �� �� ��  : mac_vap_set_wmm_params_update_count
 ��������  : ����vap��wmm update count
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_wmm_params_update_count(mac_vap_stru *pst_vap, oal_uint8 uc_update_count)
{
    pst_vap->uc_wmm_params_update_count = uc_update_count;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_rifs_tx_on
 ��������  : ����vap��wmm update count
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_rifs_tx_on(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_rifs_tx_on = uc_value;
}
#if 0
/*****************************************************************************
 �� �� ��  : mac_vap_set_tdls_prohibited
 ��������  : ����vap��tdls_prohibited
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_tdls_prohibited(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_tdls_prohibited = uc_value;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_tdls_channel_switch_prohibited
 ��������  : ����vap��tdls_channel_switch_prohibited
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_tdls_channel_switch_prohibited(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_tdls_channel_switch_prohibited = uc_value;
}
#endif
#ifdef _PRE_WLAN_FEATURE_VOWIFI
/*****************************************************************************
 �� �� ��  : mac_vap_vowifi_init
 ��������  : ��ʼ��dmac vowifi����Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : oal_int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��19��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void mac_vap_vowifi_init(mac_vap_stru *pst_mac_vap)
{
    if (WLAN_VAP_MODE_BSS_STA != pst_mac_vap->en_vap_mode)
    {
        return;
    }
    if (OAL_PTR_NULL == pst_mac_vap->pst_vowifi_cfg_param)
    {
        pst_mac_vap->pst_vowifi_cfg_param = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_vowifi_param_stru), OAL_TRUE);
        if (OAL_PTR_NULL == pst_mac_vap->pst_vowifi_cfg_param)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_VOWIFI, "{mac_vap_vowifi_init::pst_vowifi_cfg_param alloc null, size[%d].}", OAL_SIZEOF(mac_vowifi_param_stru));
            return ;
        }
    }
    OAL_MEMZERO(pst_mac_vap->pst_vowifi_cfg_param, OAL_SIZEOF(mac_vowifi_param_stru));
    pst_mac_vap->pst_vowifi_cfg_param->en_vowifi_mode         = MAC_VAP_VOWIFI_MODE_DEFAULT;
    pst_mac_vap->pst_vowifi_cfg_param->uc_trigger_count_thres = MAC_VAP_VOWIFI_TRIGGER_COUNT_DEFAULT;
    pst_mac_vap->pst_vowifi_cfg_param->us_rssi_period_ms      = MAC_VAP_VOWIFI_PERIOD_DEFAULT_MS;
    pst_mac_vap->pst_vowifi_cfg_param->c_rssi_high_thres      = MAC_VAP_VOWIFI_HIGH_THRES_DEFAULT;
    pst_mac_vap->pst_vowifi_cfg_param->c_rssi_low_thres       = MAC_VAP_VOWIFI_LOW_THRES_DEFAULT;

}
/*****************************************************************************
 �� �� ��  : mac_vap_vowifi_exit
 ��������  : ȥ��ʼ��dmac vowifi����Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : oal_int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��19��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void mac_vap_vowifi_exit(mac_vap_stru *pst_mac_vap)
{
    mac_vowifi_param_stru   *pst_vowifi_cfg_param;

    if (OAL_PTR_NULL == pst_mac_vap->pst_vowifi_cfg_param)
    {
        return;
    }

    pst_vowifi_cfg_param = pst_mac_vap->pst_vowifi_cfg_param;

    /*���ÿ����ͷ�*/
    pst_mac_vap->pst_vowifi_cfg_param = OAL_PTR_NULL;
    OAL_MEM_FREE(pst_vowifi_cfg_param, OAL_TRUE);
}
#endif /* #ifdef _PRE_WLAN_FEATURE_VOWIFI */

/*****************************************************************************
 �� �� ��  : mac_vap_set_11ac2g
 ��������  : ����vap��11ac2g
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_11ac2g(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_11ac2g = uc_value;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_hide_ssid
 ��������  : ����vap��hide ssid
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_hide_ssid(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_hide_ssid = uc_value;
}


/*****************************************************************************
 �� �� ��  : mac_vap_get_obss_scan
 ��������  : ��ȡvap��bit_peer_obss_scan
 �������  : mac_vap_stru *pst_vap
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��16��
    ��    ��   : d00223710
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 mac_vap_get_peer_obss_scan(mac_vap_stru *pst_vap)
{
    return pst_vap->st_cap_flag.bit_peer_obss_scan;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_obss_scan
 ��������  : ����vap��bit_peer_obss_scan
 �������  : mac_vap_stru *pst_vap, oal_uint8 uc_value
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��16��
    ��    ��   : d00223710
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_vap_set_peer_obss_scan(mac_vap_stru *pst_vap, oal_uint8 uc_value)
{
    pst_vap->st_cap_flag.bit_peer_obss_scan = uc_value;
}

/*****************************************************************************
 �� �� ��  : mac_get_p2p_mode
 ��������  : ��ȡVap��P2Pģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : mac_vap_stru *pst_vap
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
wlan_p2p_mode_enum_uint8  mac_get_p2p_mode(mac_vap_stru *pst_vap)
{
    return (pst_vap->en_p2p_mode);
}


/*****************************************************************************
 �� �� ��  : mac_p2p_dec_num
 ��������  : ɾ��P2P vap num�Ĺ��ܺ���
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��22��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_dec_p2p_num(mac_vap_stru *pst_vap)
{
    mac_device_stru               *pst_device;

    pst_device     = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_p2p_dec_num::pst_device[%d] null.}", pst_vap->uc_device_id);
        return;
    }

    if (IS_P2P_DEV(pst_vap))
    {
        pst_device->st_p2p_info.uc_p2p_device_num--;
    }
    else if (IS_P2P_GO(pst_vap) || IS_P2P_CL(pst_vap))
    {
        pst_device->st_p2p_info.uc_p2p_goclient_num--;
    }
}
/*****************************************************************************
 �� �� ��  : mac_inc_p2p_num
 ��������  : add p2p vapʱͬ������p2p�豸�ļ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_inc_p2p_num(mac_vap_stru *pst_vap)
{
    mac_device_stru               *pst_dev;

    pst_dev = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{hmac_inc_p2p_num::pst_dev[%d] null.}", pst_vap->uc_device_id);
        return;
    }

    if (IS_P2P_DEV(pst_vap))
    {
        /* device��sta������1 */
        pst_dev->st_p2p_info.uc_p2p_device_num++;
    }
    else if (IS_P2P_GO(pst_vap))
    {
        pst_dev->st_p2p_info.uc_p2p_goclient_num++;
    }
    else if (IS_P2P_CL(pst_vap))
    {
        pst_dev->st_p2p_info.uc_p2p_goclient_num++;
    }
}

/*****************************************************************************
�� �� ��  : mac_vap_save_app_ie
��������  : ���û�̬ IE ��Ϣ�������ں�̬��
�������  : mac_vap_stru *pst_mac_vap
          oal_net_dev_ioctl_data_stru *pst_ioctl_data
          enum WPS_IE_TYPE en_type
�������  : ��
�� �� ֵ  : OAL_STATIC oal_uint8*
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2015��4��28��
  ��    ��   : g00260350
  �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_save_app_ie(mac_vap_stru *pst_mac_vap, oal_app_ie_stru *pst_app_ie, en_app_ie_type_uint8 en_type)
{
    oal_uint8           *puc_ie = OAL_PTR_NULL;
    oal_uint32           ul_ie_len;
    oal_app_ie_stru      st_tmp_app_ie;

    OAL_MEMZERO(&st_tmp_app_ie, OAL_SIZEOF(st_tmp_app_ie));

    if (en_type >= OAL_APP_IE_NUM)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_save_app_ie::invalid en_type[%d].}", en_type);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    ul_ie_len = pst_app_ie->ul_ie_len;

    /* �������WPS ����Ϊ0�� ��ֱ���ͷ�VAP ����Դ */
    if (0 == ul_ie_len)
    {
        if (OAL_PTR_NULL != pst_mac_vap->ast_app_ie[en_type].puc_ie)
        {
            OAL_MEM_FREE(pst_mac_vap->ast_app_ie[en_type].puc_ie, OAL_TRUE);
        }

        pst_mac_vap->ast_app_ie[en_type].puc_ie         = OAL_PTR_NULL;
        pst_mac_vap->ast_app_ie[en_type].ul_ie_len      = 0;
        pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len  = 0;

        return OAL_SUCC;
    }

    /* �������͵�IE�Ƿ���Ҫ�����ڴ� */
    if ((pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len < ul_ie_len) || (NULL == pst_mac_vap->ast_app_ie[en_type].puc_ie))
    {
        /* ���������Ӧ�ó��֣�ά����Ҫ */
        if (NULL == pst_mac_vap->ast_app_ie[en_type].puc_ie && pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len != 0  )
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_app_ie::invalid len[%d].}",
                          pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len);
        }

        /* �����ǰ���ڴ�ռ�С������ϢԪ����Ҫ�ĳ��ȣ�����Ҫ���������ڴ� */
        puc_ie = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, (oal_uint16)(ul_ie_len), OAL_TRUE);
        if (OAL_PTR_NULL == puc_ie)
        {
            OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_app_ie::LOCAL_MEM_POOL is empty!,len[%d], en_type[%d].}",
                              pst_app_ie->ul_ie_len, en_type);
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        OAL_MEM_FREE(pst_mac_vap->ast_app_ie[en_type].puc_ie, OAL_TRUE);

        pst_mac_vap->ast_app_ie[en_type].puc_ie = puc_ie;
        pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len = ul_ie_len;
    }

    oal_memcopy((oal_void*)pst_mac_vap->ast_app_ie[en_type].puc_ie, (oal_void*)pst_app_ie->auc_ie, ul_ie_len);
    pst_mac_vap->ast_app_ie[en_type].ul_ie_len = ul_ie_len;

    return OAL_SUCC;
}
 /*****************************************************************************
 �� �� ��  : mac_vap_clear_app_ie
 ��������  : ��������ie
 �������  : mac_vap_stru *pst_mac_vap
           enum WPS_IE_TYPE en_type
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint8*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��4��28��
  ��    ��   : g00260350
  �޸�����   : �����ɺ���

 *****************************************************************************/
 oal_uint32 mac_vap_clear_app_ie(mac_vap_stru *pst_mac_vap, en_app_ie_type_uint8 en_type)
 {
     if (en_type < OAL_APP_IE_NUM)
     {
         if (OAL_PTR_NULL != pst_mac_vap->ast_app_ie[en_type].puc_ie)
         {
             OAL_MEM_FREE(pst_mac_vap->ast_app_ie[en_type].puc_ie, OAL_TRUE);
             pst_mac_vap->ast_app_ie[en_type].puc_ie    = OAL_PTR_NULL;
         }
         pst_mac_vap->ast_app_ie[en_type].ul_ie_len     = 0;
         pst_mac_vap->ast_app_ie[en_type].ul_ie_max_len = 0;
     }

     return OAL_SUCC;
 }

 oal_void mac_vap_free_mib(mac_vap_stru   *pst_vap)
{
    if(NULL == pst_vap)
        return;

    if (OAL_PTR_NULL != pst_vap->pst_mib_info)
    {
        wlan_mib_ieee802dot11_stru  *pst_mib_info = pst_vap->pst_mib_info;
        /*���ÿ����ͷ�*/
        pst_vap->pst_mib_info = OAL_PTR_NULL;
        OAL_MEM_FREE(pst_mib_info, OAL_TRUE);
    }
}

 /*****************************************************************************
 �� �� ��  : mac_vap_exit
 ��������  : mac vap exit
 �������  :
 �������  :
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_exit(mac_vap_stru *pst_vap)
{
    mac_device_stru               *pst_device;
    oal_uint8                      uc_index;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_vap_exit::pst_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_vap->uc_init_flag = MAC_VAP_INVAILD;

    /* �ͷ���hmac�йص��ڴ� */
    mac_vap_free_mib(pst_vap);
#ifdef _PRE_WLAN_FEATURE_VOWIFI
    /* �ͷ�vowifi����ڴ� */
    mac_vap_vowifi_exit(pst_vap);
#endif /* _PRE_WLAN_FEATURE_VOWIFI */
    /* �ͷ�WPS��ϢԪ���ڴ� */
    for (uc_index = 0; uc_index < OAL_APP_IE_NUM; uc_index++)
    {
        mac_vap_clear_app_ie(pst_vap, uc_index);
    }

    /* ҵ��vap��ɾ������device��ȥ�� */
    pst_device     = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_exit::pst_device[%d] null.}", pst_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ҵ��vap�Ѿ�ɾ������device��ȥ�� */
    for (uc_index = 0; uc_index < pst_device->uc_vap_num; uc_index++)
    {
        /* ��device���ҵ�vap id */
        if (pst_device->auc_vap_id[uc_index] == pst_vap->uc_vap_id)
        {
            /* ����������һ��vap��������һ��vap id�ƶ������λ�ã�ʹ�ø������ǽ��յ� */
            if(uc_index < (pst_device->uc_vap_num - 1))
            {
                pst_device->auc_vap_id[uc_index] = pst_device->auc_vap_id[pst_device->uc_vap_num - 1];
                break;
            }
        }
    }

    /* device�µ�vap������1 */
    pst_device->uc_vap_num--;
    /* �����������ɾ����vap id����֤��������Ԫ�ؾ�Ϊδɾ��vap */
    pst_device->auc_vap_id[pst_device->uc_vap_num] = 0;

    /* device��sta������1 */
    if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
    {
        pst_device->uc_sta_num--;
    }
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_dec_p2p_num(pst_vap);
#endif

    pst_vap->en_protocol  = WLAN_PROTOCOL_BUTT;

    /* ���1��vapɾ��ʱ�����device��������Ϣ */
    if (0 == pst_device->uc_vap_num)
    {
        pst_device->uc_max_channel   = 0;
        pst_device->en_max_band      = WLAN_BAND_BUTT;
        pst_device->en_max_bandwidth = WLAN_BAND_WIDTH_BUTT;
    }

    /* ɾ��֮��vap��״̬��λ�Ƿ� */
    mac_vap_state_change(pst_vap, MAC_VAP_STATE_BUTT);

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : mac_init_mib
 ��������  : mib��ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��29��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

  2.��    ��   : 2013��11��6��
    ��    ��   : y00184180 yaorui
    �޸�����   : ����HT only��VHT onlyЭ��ģʽ�ĳ�ʼ��

*****************************************************************************/
OAL_STATIC oal_void  mac_init_mib(mac_vap_stru *pst_mac_vap)
{
    wlan_mib_ieee802dot11_stru *pst_mib_info;
    oal_uint8 uc_idx;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_init_mib::pst_mac_vap null.}");

        return;
    }

    pst_mib_info = pst_mac_vap->pst_mib_info;

    /* ��������mibֵ��ʼ�� */
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11DTIMPeriod             = WLAN_DTIM_DEFAULT;
    pst_mib_info->st_wlan_mib_operation.ul_dot11RTSThreshold            = WLAN_RTS_MAX;
    pst_mib_info->st_wlan_mib_operation.ul_dot11FragmentationThreshold  = WLAN_FRAG_THRESHOLD_MAX;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11DesiredBSSType         = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11BeaconPeriod           = WLAN_BEACON_INTVAL_DEFAULT;


    mac_mib_set_ShortPreambleOptionImplemented(pst_mac_vap, WLAN_LEGACY_11B_MIB_SHORT_PREAMBLE);
    pst_mib_info->st_phy_hrdsss.en_dot11PBCCOptionImplemented           = OAL_FALSE;
    pst_mib_info->st_phy_hrdsss.en_dot11ChannelAgilityPresent           = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11MultiDomainCapabilityActivated = OAL_TRUE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11SpectrumManagementRequired = OAL_TRUE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11ExtendedChannelSwitchActivated = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11QosOptionImplemented   = OAL_TRUE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11APSDOptionImplemented  = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11QBSSLoadImplemented    = OAL_TRUE;
    pst_mib_info->st_phy_erp.en_dot11ShortSlotTimeOptionImplemented     = OAL_TRUE;
    pst_mib_info->st_phy_erp.en_dot11ShortSlotTimeOptionActivated       = OAL_TRUE; //11g �������� DTS2015012001920
    pst_mib_info->st_wlan_mib_sta_config.en_dot11RadioMeasurementActivated = OAL_FALSE;


    pst_mib_info->st_phy_erp.en_dot11DSSSOFDMOptionActivated            = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11ImmediateBlockAckOptionImplemented = OAL_TRUE;
    pst_mib_info->st_wlan_mib_sta_config.en_dot11DelayedBlockAckOptionImplemented   = OAL_FALSE;
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11AuthenticationResponseTimeOut = WLAN_AUTH_TIMEOUT;

    mac_mib_set_HtProtection(pst_mac_vap, WLAN_MIB_HT_NO_PROTECTION);
    mac_mib_set_RifsMode(pst_mac_vap, OAL_TRUE);
    mac_mib_set_NonGFEntitiesPresent(pst_mac_vap, OAL_FALSE);
    mac_mib_set_LsigTxopFullProtectionActivated(pst_mac_vap, OAL_TRUE);

    pst_mib_info->st_wlan_mib_operation.en_dot11DualCTSProtection       = OAL_FALSE;
    pst_mib_info->st_wlan_mib_operation.en_dot11PCOActivated            = OAL_FALSE;

    pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationResponseTimeOut = WLAN_ASSOC_TIMEOUT;
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryMaximumTimeout = WLAN_SA_QUERY_RETRY_TIME;
    pst_mib_info->st_wlan_mib_sta_config.ul_dot11AssociationSAQueryRetryTimeout   = WLAN_SA_QUERY_MAXIMUM_TIME;

    /* ��֤�㷨���ʼ�� */
    pst_mib_info->st_wlan_mib_auth_alg.uc_dot11AuthenticationAlgorithm = WLAN_WITP_AUTH_OPEN_SYSTEM;
    pst_mib_info->st_wlan_mib_auth_alg.en_dot11AuthenticationAlgorithmsActivated = OAL_FALSE;

    /* WEP ȱʡKey���ʼ�� */
    for(uc_idx = 0; uc_idx < WLAN_NUM_DOT11WEPDEFAULTKEYVALUE; uc_idx++)
    {
        oal_memset(pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue, 0, WLAN_MAX_WEP_STR_SIZE);
        /* ��С��ʼ��Ϊ WEP-40  */
        pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_idx].auc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET] = 40;
    }

    /*   WEP Kep ӳ����ʼ��    */
    oal_memset(pst_mib_info->st_wlan_mib_wep_key_map.auc_dot11WEPKeyMappingValue,
           0, WLAN_MAX_WEP_STR_SIZE);
    oal_memset(pst_mib_info->st_wlan_mib_wep_key_map.auc_dot11WEPKeyMappingAddress, 0,
           WLAN_MAC_ADDR_LEN);
    pst_mib_info->st_wlan_mib_wep_key_map.en_dot11WEPKeyMappingWEPOn = OAL_FALSE;

    /*    ���˽�б��ʼ��  */
    pst_mib_info->st_wlan_mib_privacy.en_dot11PrivacyInvoked                 = OAL_FALSE;
    pst_mib_info->st_wlan_mib_privacy.uc_dot11WEPDefaultKeyID                = 0;
    pst_mib_info->st_wlan_mib_privacy.en_dot11ExcludeUnencrypted             = OAL_TRUE;
    pst_mib_info->st_wlan_mib_privacy.ul_dot11WEPICVErrorCount               = 0;
    pst_mib_info->st_wlan_mib_privacy.ul_dot11WEPExcludedCount               = 0;

    /* ����wmm������ʼֵ */
    mac_vap_init_wme_param(pst_mac_vap);

    /* 11i */
    mac_vap_init_mib_11i(pst_mac_vap);

    /* Ĭ��11n 11acʹ�ܹرգ�����Э��ģʽʱ�� */
    mac_vap_init_mib_11n(pst_mac_vap);
    mac_vap_init_mib_11ac(pst_mac_vap);

    /* staut�͹���mib���ʼ�� */
    pst_mib_info->st_wlan_mib_sta_config.uc_dot11PowerManagementMode         = WLAN_MIB_PWR_MGMT_MODE_ACTIVE;

#ifdef _PRE_WLAN_FEATURE_11K
    /* 11k */
    mac_vap_init_mib_11k(pst_mac_vap);
#endif
}

/*****************************************************************************
 �� �� ��  : mac_vap_cap_init_legacy
 ��������  : legacyЭ���ʼ��vap����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  mac_vap_cap_init_legacy(mac_vap_stru *pst_mac_vap)
{
    pst_mac_vap->st_cap_flag.bit_rifs_tx_on = OAL_FALSE;
    pst_mac_vap->st_cap_flag.bit_smps       = WLAN_MIB_MIMO_POWER_SAVE_MIMO;
    return;
}

/*****************************************************************************
 �� �� ��  : mac_vap_cap_init_htvht
 ��������  : ht vhtЭ���ʼ��vap����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  mac_vap_cap_init_htvht(mac_vap_stru *pst_mac_vap)
{
    pst_mac_vap->st_cap_flag.bit_rifs_tx_on = OAL_FALSE;

#ifdef _PRE_WLAN_FEATURE_TXOPPS
    if(OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {   /*DTS2015061707970 �������*/
        OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_cap_init_htvht::pst_mib_info null,vap mode[%d] state[%d] user num[%d].}",
                                     pst_mac_vap->en_vap_mode ,pst_mac_vap->en_vap_state, pst_mac_vap->us_user_nums);
        return OAL_FAIL;
    }
    if (pst_mac_vap->en_protocol == WLAN_VHT_MODE ||
         pst_mac_vap->en_protocol == WLAN_VHT_ONLY_MODE)
    {
        pst_mac_vap->st_cap_flag.bit_txop_ps   = OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTTXOPPowerSaveOptionImplemented  = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_vht_sta_config.en_dot11VHTTXOPPowerSaveOptionImplemented  = OAL_FALSE;
        pst_mac_vap->st_cap_flag.bit_txop_ps    = OAL_FALSE;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_SMPS
    pst_mac_vap->st_cap_flag.bit_smps = mac_mib_get_smps(pst_mac_vap);
#else
    pst_mac_vap->st_cap_flag.bit_smps = WLAN_MIB_MIMO_POWER_SAVE_MIMO;
#endif

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : mac_vap_config_vht_ht_mib_by_protocol
 ��������  : ����VAP Э��ģʽ����ʼ��vap HT/VHT ��Ӧ MIB ����
 �������  : pst_mac_vap: ָ��vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
//l00311403TODO
oal_uint32 mac_vap_config_vht_ht_mib_by_protocol(mac_vap_stru *pst_mac_vap)
{

    if(OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {   /*DTS2015061707970 �������*/
        OAM_ERROR_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{mac_vap_config_vht_ht_mib_by_protocol::pst_mib_info null,vap mode[%d] state[%d] user num[%d].}",
                                     pst_mac_vap->en_vap_mode ,pst_mac_vap->en_vap_state, pst_mac_vap->us_user_nums);
        return OAL_FAIL;
    }
    /* ����Э��ģʽ���� HT/VHT mibֵ */
    if (WLAN_HT_MODE == pst_mac_vap->en_protocol || WLAN_HT_ONLY_MODE == pst_mac_vap->en_protocol)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = OAL_TRUE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented = OAL_FALSE;
    }
    else if (WLAN_VHT_MODE == pst_mac_vap->en_protocol || WLAN_VHT_ONLY_MODE == pst_mac_vap->en_protocol)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = OAL_TRUE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11HighThroughputOptionImplemented = OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.en_dot11VHTOptionImplemented = OAL_FALSE;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_init_rx_nss_by_protocol
 ��������  : ��ʼ��rx nss
 �������  : pst_mac_vap: ָ��vap
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��27��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_vap_init_rx_nss_by_protocol(mac_vap_stru *pst_mac_vap)
{
    wlan_protocol_enum_uint8 en_protocol;
    mac_device_stru         *pst_mac_device;

    en_protocol   = pst_mac_vap->en_protocol;

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_init_rx_nss_by_protocol::pst_mac_device[%d] null.}", pst_mac_vap->uc_device_id);
        return;
    }

    switch(en_protocol)
    {
        case WLAN_HT_MODE:
        case WLAN_VHT_MODE:
        case WLAN_HT_ONLY_MODE:
        case WLAN_VHT_ONLY_MODE:
        case WLAN_HT_11G_MODE:
             pst_mac_vap->en_vap_rx_nss  = WLAN_DOUBLE_NSS;
             break;
        case WLAN_PROTOCOL_BUTT:
             pst_mac_vap->en_vap_rx_nss  = WLAN_NSS_BUTT;
             return;

        default:
             pst_mac_vap->en_vap_rx_nss  = WLAN_SINGLE_NSS;
             break;
    }

    pst_mac_vap->en_vap_rx_nss = OAL_MIN(pst_mac_vap->en_vap_rx_nss, pst_mac_device->en_nss_num);
}

/*****************************************************************************
 �� �� ��  : mac_vap_init_by_protocol
 ��������  : ����Э���ʼ��vap��Ӧ����
 �������  : pst_mac_vap: ָ��vap
             en_protocol: Э��ö��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_vap_init_by_protocol(mac_vap_stru *pst_mac_vap, wlan_protocol_enum_uint8 en_protocol)
{
    pst_mac_vap->en_protocol          = en_protocol;

    if (en_protocol < WLAN_HT_MODE)
    {
        mac_vap_cap_init_legacy(pst_mac_vap);
    }
    else
    {
        if(OAL_SUCC != mac_vap_cap_init_htvht(pst_mac_vap))
        {
            return OAL_FAIL;
        }
    }

    /* ����Э��ģʽ����mibֵ */
    if(OAL_SUCC != mac_vap_config_vht_ht_mib_by_protocol(pst_mac_vap))
    {
        return OAL_FAIL;
    }

    /* ����Э����³�ʼ���ռ������� */
    mac_vap_init_rx_nss_by_protocol(pst_mac_vap);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_change_mib_by_bandwidth
 ��������  : ���ݴ������vap��mibֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��20��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_vap_change_mib_by_bandwidth(mac_vap_stru *pst_mac_vap, wlan_channel_bandwidth_enum_uint8 en_bandwidth)
{
    wlan_mib_ieee802dot11_stru *pst_mib_info;

    pst_mib_info = pst_mac_vap->pst_mib_info;

    if (OAL_PTR_NULL == pst_mib_info)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_change_mib_by_bandwidth::pst_mib_info null.}");

        return;
    }

    /* ����40Mʹ��mib, Ĭ��ʹ�� */
    mac_mib_set_FortyMHzOperationImplemented(pst_mac_vap, OAL_TRUE);

    /* ����short giʹ��mib, Ĭ��ȫʹ�ܣ����ݴ�����Ϣ���� */
    pst_mib_info->st_phy_ht.en_dot11ShortGIOptionInTwentyImplemented           = OAL_TRUE;
    mac_mib_set_ShortGIOptionInFortyImplemented(pst_mac_vap, OAL_TRUE);
    pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented  = OAL_TRUE;

    if (WLAN_BAND_WIDTH_20M == en_bandwidth)
    {
        mac_mib_set_FortyMHzOperationImplemented(pst_mac_vap, OAL_FALSE);
        mac_mib_set_ShortGIOptionInFortyImplemented(pst_mac_vap, OAL_FALSE);
        pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented  = OAL_FALSE;
    }
    else if (WLAN_BAND_WIDTH_20M < en_bandwidth && en_bandwidth < WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        pst_mib_info->st_wlan_mib_phy_vht.en_dot11VHTShortGIOptionIn80Implemented  = OAL_FALSE;
    }


}


#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
/*****************************************************************************
 �� �� ��  : hmac_proxy_init_vap
 ��������  : ��ʼ��proxy��������Ҫ�Ľṹ
 �������  : pst_mac_vap: mac_vapָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��6��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_err_code_enum_uint32 mac_proxy_init_vap(mac_vap_stru  *pst_mac_vap)
{
    pst_mac_vap->pst_vap_proxyarp = OAL_PTR_NULL;
    return OAL_SUCC;
}
#endif


/*****************************************************************************
 �� �� ��  : mac_vap_init
 ��������  : mac vap init
 �������  :
 �������  :
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : chenyan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_init(
                mac_vap_stru               *pst_vap,
                oal_uint8                   uc_chip_id,
                oal_uint8                   uc_device_id,
                oal_uint8                   uc_vap_id,
                mac_cfg_add_vap_param_stru *pst_param)
{
    oal_uint32                     ul_loop;
    wlan_mib_ieee802dot11_stru    *pst_mib_info;
    mac_device_stru               *pst_mac_device = mac_res_get_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_vap_init::pst_mac_device[%d] null!}", uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_vap->uc_chip_id     = uc_chip_id;
    pst_vap->uc_device_id   = uc_device_id;
    pst_vap->uc_vap_id      = uc_vap_id;
    pst_vap->en_vap_mode    = pst_param->en_vap_mode;
	pst_vap->ul_core_id     = pst_mac_device->ul_core_id;

    pst_vap->bit_has_user_bw_limit  = OAL_FALSE;
	pst_vap->bit_vap_bw_limit   = 0;
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_vap->bit_voice_aggr     = OAL_TRUE;
#else
	pst_vap->bit_voice_aggr     = OAL_FALSE;
#endif
    pst_vap->bit_one_tx_tcp_be  = OAL_FALSE;

    oal_set_mac_addr_zero(pst_vap->auc_bssid);

    for (ul_loop = 0; ul_loop < MAC_VAP_USER_HASH_MAX_VALUE; ul_loop++)
    {
        oal_dlist_init_head(&(pst_vap->ast_user_hash[ul_loop]));
    }

    /* cache user ����ʼ�� */
    oal_spin_lock_init(&pst_vap->st_cache_user_lock);

    oal_dlist_init_head(&pst_vap->st_mac_user_list_head);

    /* ��ʼ��֧��2.4G 11ac˽����ǿ */
#ifdef _PRE_WLAN_FEATURE_11AC2G
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    pst_vap->st_cap_flag.bit_11ac2g = pst_param->bit_11ac2g_enable;
#else
    pst_vap->st_cap_flag.bit_11ac2g = OAL_TRUE;
#endif
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    /* ���ݶ��ƻ�ˢ��2g ht40���� */
    pst_vap->st_cap_flag.bit_disable_2ght40 = pst_param->bit_disable_capab_2ght40;
#else
    pst_vap->st_cap_flag.bit_disable_2ght40 = OAL_FALSE;
#endif


    switch(pst_vap->en_vap_mode)
    {
        case WLAN_VAP_MODE_CONFIG :
            return OAL_SUCC;
        case WLAN_VAP_MODE_BSS_STA:
        case WLAN_VAP_MODE_BSS_AP:
            /* ����vap����Ĭ��ֵ */
            pst_vap->uc_assoc_vap_id = 0xff;
            pst_vap->uc_tx_power     = WLAN_MAX_TXPOWER;
            pst_vap->st_protection.en_protection_mode    = WLAN_PROT_NO;

            pst_vap->st_cap_flag.bit_dsss_cck_mode_40mhz = OAL_TRUE;

            /* ��ʼ�����Ա�ʶ */
            pst_vap->st_cap_flag.bit_uapsd      = WLAN_FEATURE_UAPSD_IS_OPEN;
       #ifdef _PRE_WLAN_FEATURE_UAPSD
       #if defined(_PRE_PRODUCT_ID_HI110X_HOST) || defined(_PRE_PRODUCT_ID_HI110X_DEV)
            if (WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode)
            {
                pst_vap->st_cap_flag.bit_uapsd      = g_uc_uapsd_cap;
            }
       #endif
       #endif
            /* ��ʼ��dpd���� */
            pst_vap->st_cap_flag.bit_dpd_enbale = OAL_TRUE;

            pst_vap->st_cap_flag.bit_dpd_done   = OAL_FALSE;
            /* ��ʼ��TDLS prohibited�ر� */
            pst_vap->st_cap_flag.bit_tdls_prohibited                = OAL_FALSE;
            /* ��ʼ��TDLS channel switch prohibited�ر� */
            pst_vap->st_cap_flag.bit_tdls_channel_switch_prohibited = OAL_FALSE;

            /* ��ʼ��KeepALive���� */
            pst_vap->st_cap_flag.bit_keepalive   = OAL_TRUE;
            /* ��ʼ����ȫ����ֵ */
            //pst_vap->uc_80211i_mode              = OAL_FALSE;
            pst_vap->st_cap_flag.bit_wpa         = OAL_FALSE;
            pst_vap->st_cap_flag.bit_wpa2        = OAL_FALSE;

            mac_vap_set_peer_obss_scan(pst_vap, OAL_FALSE);

            //OAL_MEMZERO(&(pst_vap->st_key_mgmt), sizeof(mac_key_mgmt_stru));

            /* ��ʼ��Э��ģʽ�����Ϊ�Ƿ�ֵ����ͨ�������������� */
            pst_vap->st_channel.en_band         = WLAN_BAND_BUTT;
            pst_vap->st_channel.en_bandwidth    = WLAN_BAND_WIDTH_BUTT;
            pst_vap->st_channel.uc_chan_number  = 0;
            pst_vap->en_protocol  = WLAN_PROTOCOL_BUTT;

            /*�����Զ���������*/
            pst_vap->st_protection.bit_auto_protection = OAL_SWITCH_ON;

            OAL_MEMZERO(pst_vap->ast_app_ie, OAL_SIZEOF(mac_app_ie_stru) * OAL_APP_IE_NUM);

            /*���ó�ʼ��rx nssֵ,֮��Э���ʼ�� */
            pst_vap->en_vap_rx_nss = WLAN_NSS_BUTT;

            /* ����VAP״̬Ϊ��ʼ״̬INIT */
            mac_vap_state_change(pst_vap, MAC_VAP_STATE_INIT);

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
            mac_proxy_init_vap(pst_vap);
#endif /* #ifdef _PRE_WLAN_FEATURE_PROXY_ARP */

/* ��mac vap�µ�uapsd��״̬,����״̬���в���������host device uapsd��Ϣ��ͬ�� */
#ifdef _PRE_WLAN_FEATURE_STA_PM
        OAL_MEMZERO(&(pst_vap->st_sta_uapsd_cfg),OAL_SIZEOF(mac_cfg_uapsd_sta_stru));
#endif/* #ifdef _PRE_WLAN_FEATURE_STA_PM */

#ifdef _PRE_WLAN_FEATURE_P2P
            //pst_vap->uc_p2p0_hal_vap_id     = 0xff;
            //pst_vap->uc_p2p_gocl_hal_vap_id = 0xff;
#endif  /* _PRE_WLAN_FEATURE_P2P */
            break;
        case WLAN_VAP_MODE_WDS:
            /* TBD ��ʼ��wds���Ա�ʶ */
            break;
        case WLAN_VAP_MODE_MONITOER :
            /* TBD */
            break;
        case WLAN_VAP_HW_TEST:
            /* TBD */
            break;
        default :
            OAM_WARNING_LOG1(uc_vap_id, OAM_SF_ANY, "{mac_vap_init::invalid vap mode[%d].}", pst_vap->en_vap_mode);

            return OAL_ERR_CODE_INVALID_CONFIG;
    }
    /* ����MIB�ڴ�ռ䣬����VAPû��MIB */
    if ((WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode) ||
        (WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode) ||
        (WLAN_VAP_MODE_WDS == pst_vap->en_vap_mode))
    {
        pst_vap->pst_mib_info = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_MIB, OAL_SIZEOF(wlan_mib_ieee802dot11_stru), OAL_TRUE);
        if (OAL_PTR_NULL == pst_vap->pst_mib_info)
        {
            OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_init::pst_mib_info alloc null, size[%d].}", OAL_SIZEOF(wlan_mib_ieee802dot11_stru));
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }

        pst_mib_info = pst_vap->pst_mib_info;
        OAL_MEMZERO(pst_mib_info, OAL_SIZEOF(wlan_mib_ieee802dot11_stru));

        /* ����mac��ַ */
        oal_set_mac_addr(pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID, pst_mac_device->auc_hw_addr);
        pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID[WLAN_MAC_ADDR_LEN - 1] += uc_vap_id;

        /* ��ʼ��mibֵ */
        mac_init_mib(pst_vap);
#ifdef _PRE_WLAN_FEATURE_VOWIFI
        if (WLAN_LEGACY_VAP_MODE == pst_param->en_p2p_mode)
        {
            mac_vap_vowifi_init(pst_vap);
        }
#endif /* _PRE_WLAN_FEATURE_VOWIFI */
#ifdef _PRE_WLAN_FEATURE_TXBF
        pst_vap->st_txbf_add_cap.bit_imbf_receive_cap  = 0;
        pst_vap->st_txbf_add_cap.bit_exp_comp_txbf_cap = OAL_TRUE;
        pst_vap->st_txbf_add_cap.bit_min_grouping      = 3;
        pst_vap->st_txbf_add_cap.bit_csi_bfee_max_rows = 1;
        pst_vap->st_txbf_add_cap.bit_channel_est_cap   = 1;
        pst_vap->bit_ap_11ntxbf                        = 0;
        pst_vap->st_cap_flag.bit_11ntxbf               = 1;
#endif

        /* sta������������� */
        if (WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode)
        {
            /* ��ʼ��staЭ��ģʽΪ11ac */
            switch(pst_mac_device->en_protocol_cap)
            {
                case WLAN_PROTOCOL_CAP_LEGACY:
                case WLAN_PROTOCOL_CAP_HT:
                     pst_vap->en_protocol                = WLAN_HT_MODE;
                     break;

                case WLAN_PROTOCOL_CAP_VHT:
                     pst_vap->en_protocol                = WLAN_VHT_MODE;
                     break;

                default:
                     OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_init::en_protocol_cap[%d] is not supportted.}", pst_mac_device->en_protocol_cap);
                     return OAL_ERR_CODE_CONFIG_UNSUPPORT;
            }

            switch(pst_mac_device->en_bandwidth_cap)
            {
                case WLAN_BW_CAP_20M:
                     pst_vap->st_channel.en_bandwidth    = WLAN_BAND_WIDTH_20M;
                     break;

                case WLAN_BW_CAP_40M:
                     pst_vap->st_channel.en_bandwidth    = WLAN_BAND_WIDTH_40MINUS;
                     break;

                case WLAN_BW_CAP_80M:
                case WLAN_BW_CAP_160M:
                     pst_vap->st_channel.en_bandwidth    = WLAN_BAND_WIDTH_80PLUSMINUS;
                     break;

                default:
                     OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_init::en_bandwidth_cap[%d] is not supportted.}", pst_mac_device->en_bandwidth_cap);
                     return OAL_ERR_CODE_CONFIG_UNSUPPORT;

            }

            switch(pst_mac_device->en_band_cap)
            {
                case WLAN_BAND_CAP_2G:
                     pst_vap->st_channel.en_band         = WLAN_BAND_2G;
                     break;

                case WLAN_BAND_CAP_5G:
                case WLAN_BAND_CAP_2G_5G:
                     pst_vap->st_channel.en_band         = WLAN_BAND_5G;
                     break;

                default:
                     OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_init::en_band_cap[%d] is not supportted.}", pst_mac_device->en_band_cap);
                     return OAL_ERR_CODE_CONFIG_UNSUPPORT;

            }

            if(OAL_SUCC != mac_vap_init_by_protocol(pst_vap, WLAN_VHT_MODE))
            {
                mac_vap_free_mib(pst_vap);
                return OAL_ERR_CODE_INVALID_CONFIG;
            }
            mac_vap_init_rates(pst_vap);
        }
    }

    pst_vap->uc_init_flag = MAC_VAP_VAILD;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_bssid
 ��������  : ����BSSID
 �������  : mac_vap_stru *pst_mac_vap,
             oal_uint8 *puc_bssid
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_set_bssid(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_bssid)
{
    oal_memcopy (pst_mac_vap->auc_bssid, puc_bssid, WLAN_MAC_ADDR_LEN);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_current_channel
 ��������  : ����mib��Ϣ�е�ǰ�ŵ�
 �������  : Ƶ��:wlan_channel_band_enum_uint8 en_band,
             �ŵ�:oal_uint8 uc_channel
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��4��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_set_current_channel(mac_vap_stru *pst_vap, wlan_channel_band_enum_uint8 en_band, oal_uint8 uc_channel)
{
    oal_uint8  uc_channel_idx = 0;
    oal_uint32 ul_ret;

    /* ����ŵ��� */
    ul_ret = mac_is_channel_num_valid(en_band, uc_channel);
    if(OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /* �����ŵ����ҵ������� */
    ul_ret = mac_get_channel_idx_from_num(en_band, uc_channel, &uc_channel_idx);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    pst_vap->st_channel.uc_chan_number = uc_channel;
    pst_vap->st_channel.en_band        = en_band;
    pst_vap->st_channel.uc_idx         = uc_channel_idx;

    pst_vap->pst_mib_info->st_wlan_mib_phy_dsss.ul_dot11CurrentChannel = uc_channel_idx;
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_get_curr_baserate
 ��������  : ��ȡĳ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��9��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8  mac_vap_get_curr_baserate(mac_vap_stru *pst_mac_ap,oal_uint8 uc_br_idx)
{
    oal_uint8          uc_loop;
    oal_uint8          uc_found_br_num = 0;
    oal_uint8          uc_rate_num;
    mac_rateset_stru  *pst_rate;

    if (OAL_PTR_NULL == pst_mac_ap)
    {
        return (oal_uint8)OAL_ERR_CODE_PTR_NULL;
    }
    pst_rate = &(pst_mac_ap->st_curr_sup_rates.st_rate);

    uc_rate_num = pst_rate->uc_rs_nrates;

    /* ����base rate ����¼���ҵ��ĸ����������ԱȽϲ����� */
    for (uc_loop = 0; uc_loop < uc_rate_num; uc_loop++)
    {
        if (0 != ((pst_rate->ast_rs_rates[uc_loop].uc_mac_rate) & 0x80))
        {
            if (uc_br_idx == uc_found_br_num)
            {
                return pst_rate->ast_rs_rates[uc_loop].uc_mac_rate;
            }

            uc_found_br_num++;
        }
    }

    /* δ�ҵ������ش��� */
    return OAL_FALSE;

}

/*****************************************************************************
 �� �� ��  : mac_vap_state_change_to_sdt
 ��������  : VAP״̬Ǩ���¼�����Ϣ��ʽ�ϱ�SDT
 �������  : en_vap_state:��Ҫ��Ϊ��״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��3��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_vap_state_change(mac_vap_stru *pst_mac_vap, mac_vap_state_enum_uint8 en_vap_state)
{
#if IS_HOST
    OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_state_change:from[%d]to[%d]}",pst_mac_vap->en_vap_state,en_vap_state);
#endif
    pst_mac_vap->en_vap_state = en_vap_state;
}

/*****************************************************************************
 �� �� ��  : mac_vap_check_bss_cap_info_phy_ap
 ��������  : ���������Ϣ����PHY��ص���Ϣ
 �������  : ��
 �������  : ��check_bss_capability_phy
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���
 �޸���ʷ      :
  1.��    ��   : 2013��12��6��
    ��    ��   : 00184180 yaorui
    �޸�����   : �޸ĺ�������ת��ΪAP��STA��������
*****************************************************************************/
oal_bool_enum_uint8  mac_vap_check_bss_cap_info_phy_ap(oal_uint16 us_cap_info,mac_vap_stru *pst_mac_vap)
{
    mac_cap_info_stru  *pst_cap_info = (mac_cap_info_stru *)(&us_cap_info);

    if (WLAN_BAND_2G != pst_mac_vap->st_channel.en_band)
    {
        return OAL_TRUE;
    }

    /* PBCC */
    if ((OAL_FALSE == pst_mac_vap->pst_mib_info->st_phy_hrdsss.en_dot11PBCCOptionImplemented) &&
       (1 == pst_cap_info->bit_pbcc))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_check_bss_cap_info_phy_ap::PBCC is different.}");
    }

    /* Channel Agility */
    if ((OAL_FALSE == pst_mac_vap->pst_mib_info->st_phy_hrdsss.en_dot11ChannelAgilityPresent) &&
       (1 == pst_cap_info->bit_channel_agility))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_check_bss_cap_info_phy_ap::Channel Agility is different.}");
    }

    /* DSSS-OFDM Capabilities */
    if ((OAL_FALSE == pst_mac_vap->pst_mib_info->st_phy_erp.en_dot11DSSSOFDMOptionActivated) &&
       (1 == pst_cap_info->bit_dsss_ofdm))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{mac_vap_check_bss_cap_info_phy_ap::DSSS-OFDM Capabilities is different.}");
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : mac_vap_get_bandwidth_cap
 ��������  : ��ȡvap�Ĵ���������Ϣ��ȡvap��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��26��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  mac_vap_get_bandwidth_cap(mac_vap_stru *pst_mac_vap, wlan_bw_cap_enum_uint8 *pen_cap)
{
    mac_channel_stru            *pst_channel;
    wlan_bw_cap_enum_uint8       en_band_cap = WLAN_BW_CAP_20M;

    pst_channel = &(pst_mac_vap->st_channel);

    if (WLAN_BAND_WIDTH_40PLUS == pst_channel->en_bandwidth || WLAN_BAND_WIDTH_40MINUS == pst_channel->en_bandwidth)
    {
        en_band_cap = WLAN_BW_CAP_40M;
    }
    else if (pst_channel->en_bandwidth >= WLAN_BAND_WIDTH_80PLUSPLUS)
    {
        en_band_cap = WLAN_BW_CAP_80M;
    }

    *pen_cap = en_band_cap;
}

oal_uint32 mac_dump_protection(mac_vap_stru *pst_mac_vap, oal_uint8* puc_param)
{
    mac_h2d_protection_stru     *pst_h2d_prot;
    mac_protection_stru         *pst_protection;

    if (OAL_PTR_NULL == puc_param)
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_h2d_prot = (mac_h2d_protection_stru *)puc_param;
    pst_protection = &pst_h2d_prot->st_protection;

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "\r\nul_sync_mask=0x%x us_user_idx=%d bit_barker_preamble_mode=%d en_dot11HTProtection=%d\r\n",
            pst_h2d_prot->ul_sync_mask, pst_h2d_prot->us_user_idx, pst_h2d_prot->st_user_cap_info.bit_barker_preamble_mode,
            pst_h2d_prot->en_dot11HTProtection);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "en_dot11RIFSMode=%d en_dot11LSIGTXOPFullProtectionActivated=%d en_dot11NonGFEntitiesPresent=%d en_protection_mode=%d\r\n",
            pst_h2d_prot->en_dot11RIFSMode, pst_h2d_prot->en_dot11LSIGTXOPFullProtectionActivated,
            pst_h2d_prot->en_dot11NonGFEntitiesPresent, pst_protection->en_protection_mode);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "uc_obss_non_erp_aging_cnt=%d uc_obss_non_ht_aging_cnt=%d bit_auto_protection=%d bit_obss_non_erp_present=%d\r\n",
            pst_protection->uc_obss_non_erp_aging_cnt, pst_protection->uc_obss_non_ht_aging_cnt,
            pst_protection->bit_auto_protection, pst_protection->bit_obss_non_erp_present);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "bit_obss_non_ht_present=%d bit_rts_cts_protect_mode=%d bit_lsig_txop_protect_mode=%d uc_sta_no_short_slot_num=%d\r\n",
            pst_protection->bit_obss_non_ht_present, pst_protection->bit_rts_cts_protect_mode,
            pst_protection->bit_lsig_txop_protect_mode, pst_protection->uc_sta_no_short_slot_num);
    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "uc_sta_no_short_preamble_num=%d uc_sta_non_erp_num=%d uc_sta_non_ht_num=%d uc_sta_non_gf_num=%d\r\n",
            pst_protection->uc_sta_no_short_preamble_num, pst_protection->uc_sta_non_erp_num,
            pst_protection->uc_sta_non_ht_num, pst_protection->uc_sta_non_gf_num);
    OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY,
            "uc_sta_20M_only_num=%d uc_sta_no_40dsss_cck_num=%d uc_sta_no_lsig_txop_num=%d\r\n",
            pst_protection->uc_sta_20M_only_num, pst_protection->uc_sta_no_40dsss_cck_num,
            pst_protection->uc_sta_no_lsig_txop_num);

    return OAL_SUCC;
}


#if 0
oal_void  mac_vap_set_p2p_channel(mac_vap_stru *pst_mac_vap, mac_channel_stru * pst_p2p_home_channel)
{
    /*
    TBD
    */
}
#endif
/*****************************************************************************
 �� �� ��  : mac_vap_get_user_protection_mode
 ��������  : ��ȡ����ģʽ����
 �������  : mac_vap_stru        : mac VAP�ṹ�壬 ����sta��Ϣ
             pst_mac_sta         : mac user�ṹ�壬 ����ap��Ϣ
 �������  : ��
 �� �� ֵ  : wlan_prot_mode_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
wlan_prot_mode_enum_uint8 mac_vap_get_user_protection_mode(mac_vap_stru *pst_mac_vap_sta, mac_user_stru *pst_mac_user)
{
    wlan_prot_mode_enum_uint8           en_protection_mode = WLAN_PROT_NO;

    if ((OAL_PTR_NULL == pst_mac_vap_sta) || (OAL_PTR_NULL == pst_mac_user))
    {
        return en_protection_mode;
    }

    /*��2GƵ���£����AP���͵�beacon֡ERP ie��Use Protection bit��Ϊ1���򽫱�����������ΪERP����*/
    if ((WLAN_BAND_2G == pst_mac_vap_sta->st_channel.en_band) && (OAL_TRUE == pst_mac_user->st_cap_info.bit_erp_use_protect))
    {
        en_protection_mode = WLAN_PROT_ERP;
    }

    /*���AP���͵�beacon֡ht operation ie��ht protection�ֶ�Ϊmixed��non-member���򽫱�����������ΪHT����*/
    else if ((WLAN_MIB_HT_NON_HT_MIXED == pst_mac_user->st_ht_hdl.bit_HT_protection)
              ||(WLAN_MIB_HT_NONMEMBER_PROTECTION == pst_mac_user->st_ht_hdl.bit_HT_protection))
    {
        en_protection_mode = WLAN_PROT_HT;
    }

    /*���AP���͵�beacon֡ht operation ie��non-gf sta present�ֶ�Ϊ1���򽫱�����������ΪGF����*/
    else if (OAL_TRUE == pst_mac_user->st_ht_hdl.bit_nongf_sta_present)
    {
        en_protection_mode = WLAN_PROT_GF;
    }

    /*ʣ�µ������������*/
    else
    {
        en_protection_mode = WLAN_PROT_NO;
    }

    return en_protection_mode;
}
/*****************************************************************************
 �� �� ��  : mac_protection_lsigtxop_check
 ��������  : ��ѯ�Ƿ����ʹ��lsigtxop����
 �������  : pst_mac_vap : mac vap�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : oal_bool_enum : 0: ������ʹ��lsig txop����
                             1: ����ʹ��lsig txop����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum mac_protection_lsigtxop_check(mac_vap_stru *pst_mac_vap)
{
    mac_user_stru  *pst_mac_user = OAL_PTR_NULL;

    /*�������11nվ�㣬��֧��lsigtxop����*/
    if ((WLAN_HT_MODE != pst_mac_vap->en_protocol)
        && (WLAN_HT_ONLY_MODE != pst_mac_vap->en_protocol)
        && (WLAN_HT_11G_MODE != pst_mac_vap->en_protocol))
    {
        return OAL_FALSE;
    }

    if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
    {
        pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(pst_mac_vap->uc_assoc_vap_id); /*user�������AP����Ϣ*/
        if ((OAL_PTR_NULL == pst_mac_user) || (OAL_FALSE == pst_mac_user->st_ht_hdl.bit_lsig_txop_protection_full_support))
        {
            return OAL_FALSE;
        }
        else
        {
            return OAL_TRUE;
        }
    }
    /*lint -e644*/
    /*BSS ������վ�㶼֧��Lsig txop protection, ��ʹ��Lsig txop protection���ƣ�����С, AP��STA���ò�ͬ���ж�*/
    if ((WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode) && (OAL_TRUE == mac_mib_get_LsigTxopFullProtectionActivated(pst_mac_vap)))
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
    /*lint +e644*/

}
/*****************************************************************************
 �� �� ��  : mac_protection_set_lsig_txop_mechanism
 ��������  : ����lsig txop���������Ƿ�����������Χ
 �������  : pst_hmac_vap : hmac vap�ṹ��ָ��
             en_flag      : 0:�ر�lsig txop��������   / 1: ��lsig txop��������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_protection_set_lsig_txop_mechanism(mac_vap_stru *pst_mac_vap, oal_switch_enum_uint8 en_flag)
{
    /*����֡/����֡����ʱ����Ҫ����bit_lsig_txop_protect_modeֵ��д�����������е�L-SIG TXOP enableλ*/
    pst_mac_vap->st_protection.bit_lsig_txop_protect_mode = en_flag;
    OAM_WARNING_LOG1(0,OAM_SF_PWR,"lzhqi mac_protection_set_lsig_txop_mechanism:on[%d]?",en_flag);
}
/*****************************************************************************
 �� �� ��  : mac_protection_set_rts_tx_param
 ��������  : ����rts ���Ͳ���,host,device����,
 �������  : pst_hmac_vap : hmac vap�ṹ��ָ��
             en_flag      : 0:�ر�lsig txop��������   / 1: ��lsig txop��������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_protection_set_rts_tx_param(mac_vap_stru *pst_mac_vap,oal_switch_enum_uint8 en_flag,
                                        wlan_prot_mode_enum_uint8 en_prot_mode,mac_cfg_rts_tx_param_stru *pst_rts_tx_param)
{
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_rts_tx_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ASSOC, "{mac_protection_set_rts_tx_param::param null,pst_mac_vap[%p] pst_rts_tx_param[%p]}",
                                     pst_mac_vap ,pst_rts_tx_param);
        return;
    }
    /*ֻ������erp����ʱ��RTS[0~2]���ʲ���Ϊ5.5Mpbs(11b), ����ʱ��Ϊ24Mpbs(leagcy ofdm) */
    if ((WLAN_PROT_ERP == en_prot_mode) && (OAL_SWITCH_ON == en_flag))
    {
        pst_rts_tx_param->en_band = WLAN_BAND_2G;

        /* RTS[0~2]��Ϊ5.5Mbps, RTS[3]��Ϊ1Mbps */
        pst_rts_tx_param->auc_protocol_mode[0]    = WLAN_11B_PHY_PROTOCOL_MODE;
        pst_rts_tx_param->auc_rate[0]             = WLAN_LONG_11b_5_HALF_M_BPS;
        pst_rts_tx_param->auc_protocol_mode[1]    = WLAN_11B_PHY_PROTOCOL_MODE;
        pst_rts_tx_param->auc_rate[1]             = WLAN_LONG_11b_5_HALF_M_BPS;
        pst_rts_tx_param->auc_protocol_mode[2]    = WLAN_11B_PHY_PROTOCOL_MODE;
        pst_rts_tx_param->auc_rate[2]             = WLAN_LONG_11b_5_HALF_M_BPS;
        pst_rts_tx_param->auc_protocol_mode[2]    = WLAN_11B_PHY_PROTOCOL_MODE;
        pst_rts_tx_param->auc_rate[2]             = WLAN_LONG_11b_5_HALF_M_BPS;
        pst_rts_tx_param->auc_protocol_mode[3]    = WLAN_11B_PHY_PROTOCOL_MODE;
        pst_rts_tx_param->auc_rate[3]             = WLAN_LONG_11b_1_M_BPS;
    }
    else
    {
        pst_rts_tx_param->en_band = pst_mac_vap->st_channel.en_band;

        /* RTS[0~2]��Ϊ24Mbps */
        pst_rts_tx_param->auc_protocol_mode[0]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
        pst_rts_tx_param->auc_rate[0]             = WLAN_LEGACY_OFDM_24M_BPS;
        pst_rts_tx_param->auc_protocol_mode[1]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
        pst_rts_tx_param->auc_rate[1]             = WLAN_LEGACY_OFDM_24M_BPS;
        pst_rts_tx_param->auc_protocol_mode[2]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
        pst_rts_tx_param->auc_rate[2]             = WLAN_LEGACY_OFDM_24M_BPS;

        /* 2G��RTS[3]��Ϊ1Mbps */
        if (WLAN_BAND_2G == pst_rts_tx_param->en_band)
        {
            pst_rts_tx_param->auc_protocol_mode[3]    = WLAN_11B_PHY_PROTOCOL_MODE;
            pst_rts_tx_param->auc_rate[3]             = WLAN_LONG_11b_1_M_BPS;
        }
        /* 5G��RTS[3]��Ϊ24Mbps */
        else
        {
            pst_rts_tx_param->auc_protocol_mode[3]    = WLAN_LEGACY_OFDM_PHY_PROTOCOL_MODE;
            pst_rts_tx_param->auc_rate[3]             = WLAN_LEGACY_OFDM_24M_BPS;
        }
    }
}
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
/*****************************************************************************
 �� �� ��  : mac_vap_init_pmf
 ��������  : ��ȡpmf����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 mac_vap_init_pmf(mac_vap_stru  *pst_mac_vap,
                                       mac_cfg80211_connect_security_stru *pst_mac_security_param)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap) || OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_security_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PMF,"mac_11w_init_privacy::Null input,pst_mac_vap[%d],security_param[%d]!!",
                        pst_mac_vap,pst_mac_security_param );
        return OAL_ERR_CODE_PTR_NULL;
    }
    if (OAL_TRUE != mac_mib_get_rsnaactivated(pst_mac_vap))
    {
        return OAL_TRUE;
    }
    switch(pst_mac_security_param->en_pmf_cap)
    {
        case MAC_PMF_DISABLED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_FALSE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_FALSE);
        }
        break;
        case MAC_PMF_ENABLED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_FALSE);
        }
        break;
        case MAC_PME_REQUIRED:
        {
            mac_mib_set_dot11RSNAMFPC(pst_mac_vap, OAL_TRUE);
            mac_mib_set_dot11RSNAMFPR(pst_mac_vap, OAL_TRUE);
        }
        break;
        default:
        {
            return OAL_FALSE;
        }
    }

    if (MAC_NL80211_MFP_REQUIRED == pst_mac_security_param->en_mgmt_proteced)
    {
        pst_mac_vap->en_user_pmf_cap = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->en_user_pmf_cap = OAL_FALSE;
    }

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 �� �� ��  : mac_vap_add_wep_key
 ��������  : add wep key�߼������¼���DMAC
 �������  : mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param
 �������  : oal_uint32
 �� �� ֵ  : 0:�ɹ�,����:ʧ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��5��12��
    ��    ��   : g00260350
    �޸�����   : wep��Կ�������鲥�û���

*****************************************************************************/
OAL_STATIC oal_uint32 mac_vap_add_wep_key(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_wep_key_param_stru          *pst_wep_addkey_params = OAL_PTR_NULL;
    mac_user_stru                   *pst_multi_user        = OAL_PTR_NULL;
    wlan_priv_key_param_stru        *pst_wep_key           = OAL_PTR_NULL;
    oal_uint32                       ul_cipher_type        = WLAN_CIPHER_SUITE_WEP40;
    oal_uint8                        uc_wep_cipher_type    = WLAN_80211_CIPHER_SUITE_WEP_40;

    pst_wep_addkey_params = (mac_wep_key_param_stru*)puc_param;

    /*wep ��Կ���Ϊ4��*/
    if(pst_wep_addkey_params->uc_key_index >= WLAN_MAX_WEP_KEY_COUNT)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    switch (pst_wep_addkey_params->uc_key_len)
    {
        case WLAN_WEP40_KEY_LEN:
            uc_wep_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_40;
            ul_cipher_type     = WLAN_CIPHER_SUITE_WEP40;
            break;
        case WLAN_WEP104_KEY_LEN:
            uc_wep_cipher_type = WLAN_80211_CIPHER_SUITE_WEP_104;
            ul_cipher_type     = WLAN_CIPHER_SUITE_WEP104;
            break;
        default:
            return OAL_ERR_CODE_SECURITY_KEY_LEN;
    }

    /* WEP��Կ��Ϣ��¼���鲥�û���*/
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
    /* ��ʼ��WEP�鲥�����׼� */
    mac_mib_set_RSNAGroupCipherSelected(pst_mac_vap, uc_wep_cipher_type);

    /*��ʼ���鲥�û��İ�ȫ��Ϣ*/
    if (pst_wep_addkey_params->en_default_key == OAL_TRUE)
    {
        pst_multi_user->st_key_info.en_cipher_type     = uc_wep_cipher_type;
        pst_multi_user->st_key_info.uc_default_index   = pst_wep_addkey_params->uc_key_index;
        pst_multi_user->st_key_info.uc_igtk_key_index  = 0xff;/* wepʱ����Ϊ��Ч */
        pst_multi_user->st_key_info.bit_gtk            = 0;
    }

    pst_wep_key   = &pst_multi_user->st_key_info.ast_key[pst_wep_addkey_params->uc_key_index];

    pst_wep_key->ul_cipher        = ul_cipher_type;
    pst_wep_key->ul_key_len       = (oal_uint32)pst_wep_addkey_params->uc_key_len;

    OAL_MEMZERO(pst_wep_key->auc_key, WLAN_WPA_KEY_LEN);
    oal_memcopy(pst_wep_key->auc_key, pst_wep_addkey_params->auc_wep_key, pst_wep_addkey_params->uc_key_len);

    /* TBD Ų��ȥ ��ʼ���鲥�û��ķ�����Ϣ */
    pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type      = pst_wep_addkey_params->uc_key_index + HAL_KEY_TYPE_PTK;
    pst_multi_user->st_user_tx_info.st_security.en_cipher_protocol_type = uc_wep_cipher_type;
    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
    //              "{mac_config_11i_add_wep_key::set multiuser ciphertype[%d] ok}", uc_wep_cipher_type);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_init_privacy
 ��������  : �����ں��·��Ĺ�����������ֵ������ص�mib ֵ
 �������  : mac_vap_stru                        *pst_mac_vap
             mac_cfg80211_connect_param_stru     *pst_mac_connect_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��26��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_init_privacy(mac_vap_stru *pst_mac_vap, mac_cfg80211_connect_security_stru *pst_mac_security_param)
{
    mac_wep_key_param_stru              st_wep_key = {0};
    mac_cfg80211_crypto_settings_stru  *pst_crypto;
    oal_uint8                           uc_loop = 0;
    oal_uint32                          ul_ret  = OAL_SUCC;

    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_FALSE);
#if defined (_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    /* ��ʼ�� RSNActive ΪFALSE */
    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_FALSE);
#endif
    /* ��������׼���Ϣ */
    mibset_RSNAClearWpaPairwiseCipherImplemented(pst_mac_vap);
    mibset_RSNAClearWpa2PairwiseCipherImplemented(pst_mac_vap);

    pst_mac_vap->st_cap_flag.bit_wpa  = OAL_FALSE;
    pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_FALSE;

    /* ������ */
    if (OAL_FALSE == pst_mac_security_param->en_privacy)
    {
        return OAL_SUCC;
    }

    /* WEP���� */
    if (0 != pst_mac_security_param->uc_wep_key_len)
    {
        st_wep_key.uc_key_len   = pst_mac_security_param->uc_wep_key_len;
        st_wep_key.uc_key_index = pst_mac_security_param->uc_wep_key_index;
        st_wep_key.en_default_key = OAL_TRUE;
        oal_memcopy(st_wep_key.auc_wep_key, pst_mac_security_param->auc_wep_key, WLAN_WEP104_KEY_LEN);
        ul_ret = mac_vap_add_wep_key(pst_mac_vap, OAL_SIZEOF(mac_wep_key_param_stru), (oal_uint8 *)&st_wep_key);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                           "{mac_11i_init_privacy::mac_config_11i_add_wep_key failed[%d].}", ul_ret);
        }
        return ul_ret;
    }

    /* WPA/WPA2���� */
    pst_crypto = &(pst_mac_security_param->st_crypto);

    if ((pst_crypto->n_ciphers_pairwise > WLAN_PAIRWISE_CIPHER_SUITES) ||
        (pst_crypto->n_akm_suites > WLAN_AUTHENTICATION_SUITES))
    {
        OAM_ERROR_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{mac_11i_init_privacy::cipher_num[%d] akm_num[%d] unexpected.}",
                       pst_crypto->n_ciphers_pairwise, pst_crypto->n_akm_suites);
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    /* ��ʼ��RSNA mib Ϊ TRUR */
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_TRUE);

    /* ��ʼ���鲥��Կ�׼� */
    mac_mib_set_rsnacfggroupcipher(pst_mac_vap, (oal_uint8)(pst_crypto->cipher_group));
    mac_mib_set_RSNAGroupCipherSelected(pst_mac_vap, (oal_uint8)(pst_crypto->cipher_group));

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    ul_ret = mac_vap_init_pmf(pst_mac_vap, pst_mac_security_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{mac_11i_init_privacy::mac_11w_init_privacy failed[%d].}", ul_ret);
        return ul_ret;
    }
#endif
    /* ��ʼ��������Կ�׼� */
    if (pst_crypto->wpa_versions == WITP_WPA_VERSION_1)
    {
        pst_mac_vap->st_cap_flag.bit_wpa = OAL_TRUE;
        for (uc_loop = 0; uc_loop < pst_crypto->n_ciphers_pairwise; uc_loop++)
        {
            mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(pst_mac_vap, pst_crypto->ciphers_pairwise[uc_loop]);
        }
    }
    else if (pst_crypto->wpa_versions == WITP_WPA_VERSION_2)
    {
        pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_TRUE;
        for (uc_loop = 0; uc_loop < pst_crypto->n_ciphers_pairwise; uc_loop++)
        {
            mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(pst_mac_vap, pst_crypto->ciphers_pairwise[uc_loop]);
        }
    }

    /* ��ʼ����֤�׼� */
    for (uc_loop = 0; uc_loop < pst_crypto->n_akm_suites; uc_loop++)
    {
        mac_mib_set_RSNAConfigAuthenticationSuiteImplemented(pst_mac_vap, pst_crypto->akm_suites[uc_loop], uc_loop);
    }

    OAM_INFO_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                  "{mac_11i_init_privacy::wpa_version[%d], group %d, n_pairwise %d, n_akm %d.}",
                  pst_crypto->wpa_versions,
                  pst_crypto->cipher_group,
                  pst_crypto->n_ciphers_pairwise,
                  pst_crypto->n_akm_suites);

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : mac_mib_set_wep
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void mac_mib_set_wep(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_id)
{
    /*��ʼ��wep���MIB��Ϣ*/
    if (OAL_PTR_NULL != pst_mac_vap->pst_mib_info)
    {
        oal_memset(pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_key_id].auc_dot11WEPDefaultKeyValue, 0, WLAN_MAX_WEP_STR_SIZE);
        pst_mac_vap->pst_mib_info->ast_wlan_mib_wep_dflt_key[uc_key_id].auc_dot11WEPDefaultKeyValue[WLAN_WEP_SIZE_OFFSET] = 40;
    }
}

/*****************************************************************************
 �� �� ��  : mac_check_auth_policy
 ��������  : �����֤��ʽ�Ƿ�ƥ��
 �������  : wlan_mib_ieee802dot11_stru *pst_mib_info
             oal_uint8 uc_policy
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8    OAL_TRUE:ƥ��ɹ�
                                    OAL_FALSE:ƥ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��31��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 mac_check_auth_policy(wlan_mib_ieee802dot11_stru *pst_mib_info,
                                                   oal_uint8 uc_policy)
{
    oal_uint8 uc_loop = 0;
    for (uc_loop = 0; uc_loop < MAC_AUTHENTICATION_SUITE_NUM; uc_loop++)
    {
        /* �����֤�׼��Ƿ�ʹ�ܺ�ƥ�� */
        if ((pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_loop].en_dot11RSNAConfigAuthenticationSuiteActivated == OAL_TRUE)
            && (pst_mib_info->ast_wlan_mib_rsna_cfg_auth_suite[uc_loop].uc_dot11RSNAConfigAuthenticationSuiteImplemented == uc_policy))
        {
            return OAL_TRUE;
        }
    }
    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : mac_get_user_by_addr
 ��������  : ����mac��ַ��ȡmac_userָ��
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
mac_user_stru  *mac_vap_get_user_by_addr(mac_vap_stru *pst_mac_vap, oal_uint8  *puc_mac_addr)
{
    oal_uint32              ul_ret;
    oal_uint16              us_user_idx   = 0xffff;
    mac_user_stru          *pst_mac_user = OAL_PTR_NULL;

    /*����mac addr�ҵ�sta����*/
    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, puc_mac_addr, &us_user_idx);
    if(OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_vap_get_user_by_addr::find_user_by_macaddr failed[%d].}", ul_ret);
        if(OAL_PTR_NULL != puc_mac_addr)
        {
            OAM_WARNING_LOG3(0, OAM_SF_ANY, "{mac_vap_get_user_by_addr::mac[%x:XX:XX:XX:%x:%x] cant be found!}",
                                    puc_mac_addr[0], puc_mac_addr[4], puc_mac_addr[5]);
        }
        return OAL_PTR_NULL;
    }

    /*����sta�����ҵ�user�ڴ�����*/
    pst_mac_user = (mac_user_stru *)mac_res_get_mac_user(us_user_idx);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_vap_get_user_by_addr::user ptr null.}");
    }

    return pst_mac_user;
}

/*****************************************************************************
 �� �� ��  : mac_vap_add_beacon
 ��������  : ��λ11X�˿�
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_add_beacon(mac_vap_stru *pst_mac_vap, mac_beacon_param_stru *pst_beacon_param)
{
    mac_user_stru                        *pst_multi_user;
    wlan_mib_dot11RSNAConfigEntry_stru   *pst_mib_rsna_cfg;
    oal_uint32                            ul_loop;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_beacon_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_vap_add_beacon::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���֮ǰ�ļ���������Ϣ */
    mibset_RSNAClearWpaPairwiseCipherImplemented(pst_mac_vap);
    mibset_RSNAClearWpa2PairwiseCipherImplemented(pst_mac_vap);
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_FALSE);
    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_FALSE);
    pst_mac_vap->st_cap_flag.bit_wpa  = OAL_FALSE;
    pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_FALSE;
    mac_mib_clear_rsna_auth_suite(pst_mac_vap);

    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR = OAL_FALSE;
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC = OAL_FALSE;

    /* ����鲥��Կ��Ϣ */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_add_beacon::pst_multi_user null [idx:%d] .}", pst_mac_vap->us_multi_user_idx);
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_beacon_param->en_privacy)
    {
        /* DTS2016052000621, ����鲥�û�������Ϣλ����vap down�ƶ����˴������vap down/up��STA����APUTʧ�����⡣ */
        /* ֻ�ڷǼ��ܳ�������������ܳ������������ø��� */
        mac_user_init_key(pst_multi_user);
        pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type = WLAN_KEY_TYPE_TX_GTK;
        return OAL_SUCC;
    }

    /* ʹ�ܼ��� */
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
    pst_mib_rsna_cfg = &pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg;

    if (0 == (pst_beacon_param->uc_crypto_mode & (WLAN_WPA_BIT | WLAN_WPA2_BIT)))
    {
        //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_11i_add_beacon::wep enabled");
        return OAL_SUCC;
    }

    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_TRUE);
    /* �����鲥�׼� */
    switch (pst_beacon_param->uc_group_crypto)
    {
        case WLAN_80211_CIPHER_SUITE_TKIP:
            pst_mib_rsna_cfg->ul_dot11RSNAConfigGroupCipherSize = WLAN_TKIP_KEY_LEN * 8;
            break;
        case WLAN_80211_CIPHER_SUITE_CCMP:
            pst_mib_rsna_cfg->ul_dot11RSNAConfigGroupCipherSize = WLAN_CCMP_KEY_LEN * 8;
            break;
        default:
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                           "{mac_vap_add_beacon::UNEXPECTED group_crypto[%d].}", pst_beacon_param->uc_group_crypto);
            return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }
    pst_mib_rsna_cfg->uc_dot11RSNAConfigGroupCipher     = pst_beacon_param->uc_group_crypto;

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
    //              "{mac_11i_add_beacon::WPA group [%d]}", pst_beacon_param->uc_group_crypto);

    /* ������֤�׼� */
    for(ul_loop = 0; ul_loop < MAC_AUTHENTICATION_SUITE_NUM; ul_loop++)
    {
        if (0xff == pst_beacon_param->auc_auth_type[ul_loop])
        {
            continue;
        }
        mac_mib_set_rsna_auth_suite(pst_mac_vap, pst_beacon_param->auc_auth_type[ul_loop]);
    }

    if (pst_beacon_param->uc_crypto_mode & WLAN_WPA_BIT)
    {
        pst_mac_vap->st_cap_flag.bit_wpa = OAL_TRUE;

        /* ����WPA������Կ�׼� */
        for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
        {
            if (0xff == pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop])
            {
                continue;
            }

            mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(pst_mac_vap, pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop]);
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented
                = (WLAN_80211_CIPHER_SUITE_CCMP == pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop])?(WLAN_CCMP_KEY_LEN * 8):(WLAN_TKIP_KEY_LEN * 8);

            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
            //              "{mac_11i_add_beacon::WPA pairwise [%d]}", pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
        }
    }

    if (pst_beacon_param->uc_crypto_mode & WLAN_WPA2_BIT)
    {
        pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_TRUE;

        /* ����WPA2������Կ�׼� */
        for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
        {
            /* DTS2015031010201 WIFI_SW: B130�汾��CI ��֤����SVN�ڵ�3399������汾��2.4G��ϼ����Ĵ�����ʧ��  */
            if (0xff == pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop])
            {
                continue;
            }

            mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(pst_mac_vap, pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented
                = (WLAN_80211_CIPHER_SUITE_CCMP == pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop])?(WLAN_CCMP_KEY_LEN * 8):(WLAN_TKIP_KEY_LEN * 8);

            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
            //              "{mac_11i_add_beacon::WPA2 pairwise [%d]}", pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
        }

        /* RSN ���� */
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR  = (pst_beacon_param->us_rsn_capability & BIT6) ? OAL_TRUE : OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC  = (pst_beacon_param->us_rsn_capability & BIT7) ? OAL_TRUE : OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAPreauthenticationActivated = pst_beacon_param->us_rsn_capability & BIT0;
        pst_mib_rsna_cfg->ul_dot11RSNAConfigNumberOfPTKSAReplayCountersImplemented = (pst_beacon_param->us_rsn_capability & 0x0C) >> 2;
        pst_mib_rsna_cfg->ul_dot11RSNAConfigNumberOfGTKSAReplayCountersImplemented = (pst_beacon_param->us_rsn_capability & 0x30) >> 4;

    }


    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : mac_user_add_key
 ��������  : ����en_key_type��������Ӧ�ĺ���������vap��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_add_key(mac_vap_stru *pst_mac_vap, mac_user_stru *pst_mac_user, oal_uint8 uc_key_id, mac_key_params_stru *pst_key)
{
    oal_uint32                            ul_ret;

    switch ((oal_uint8)pst_key->cipher)
    {
        case WLAN_80211_CIPHER_SUITE_WEP_40:
        case WLAN_80211_CIPHER_SUITE_WEP_104:
            /* ����mib */
            mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
            mac_mib_set_rsnaactivated(pst_mac_vap, OAL_FALSE);
            //TBD �����鲥��Կ�׼�Ӧ�÷���set default key
            mac_mib_set_rsnacfggroupcipher(pst_mac_vap, (oal_uint8)pst_key->cipher);
            ul_ret = mac_user_add_wep_key(pst_mac_user, uc_key_id, pst_key);
            break;
        case WLAN_80211_CIPHER_SUITE_TKIP:
        case WLAN_80211_CIPHER_SUITE_CCMP:
            ul_ret = mac_user_add_rsn_key(pst_mac_user, uc_key_id, pst_key);
            break;
        case WLAN_80211_CIPHER_SUITE_BIP:
            ul_ret = mac_user_add_bip_key(pst_mac_user, uc_key_id, pst_key);
            break;
        default:
            return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : mac_vap_get_default_key_id
 ��������  : ��ȡmac��������default_key_id
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��12��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 mac_vap_get_default_key_id(mac_vap_stru *pst_mac_vap)
{
    mac_user_stru                *pst_multi_user;
    oal_uint8                     uc_default_key_id;

    /* �������������鲥�û���Կ��Ϣ�в�����Կ */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        /* TBD ���ñ������ĵط���û�д��󷵻ش��� */
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{mac_vap_get_default_key_id::multi_user[%d] NULL}", pst_mac_vap->us_multi_user_idx);
        return 0;
    }

    if ((pst_multi_user->st_key_info.en_cipher_type != WLAN_80211_CIPHER_SUITE_WEP_40) &&
        (pst_multi_user->st_key_info.en_cipher_type != WLAN_80211_CIPHER_SUITE_WEP_104))
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA,
                       "{mac_vap_get_default_key_id::unexpectd cipher_type[%d]}", pst_multi_user->st_key_info.en_cipher_type);
        return 0;
    }
    uc_default_key_id = pst_multi_user->st_key_info.uc_default_index;
    if (uc_default_key_id >= WLAN_NUM_TK)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_WPA, "{mac_vap_get_default_key_id::unexpectd keyid[%d]}", uc_default_key_id);
        return 0;
    }
    return uc_default_key_id;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_default_key
 ��������  : ����hmac��������default_key
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_set_default_key(mac_vap_stru *pst_mac_vap, oal_uint8  uc_key_index)
{
    wlan_priv_key_param_stru     *pst_wep_key = OAL_PTR_NULL;
    mac_user_stru                *pst_multi_user;

    /* 1.1 �����wep ���ܣ���ֱ�ӷ��� */
    if (OAL_TRUE != mac_is_wep_enabled(pst_mac_vap))
    {
        return OAL_SUCC;
    }

    /* 2.1 �������������鲥�û���Կ��Ϣ�в�����Կ */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }
    pst_wep_key   = &pst_multi_user->st_key_info.ast_key[uc_key_index];

    if (pst_wep_key->ul_cipher != WLAN_CIPHER_SUITE_WEP40 &&
        pst_wep_key->ul_cipher != WLAN_CIPHER_SUITE_WEP104)
    {
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }

    /* 3.1 ������Կ���ͼ�default id */
    pst_multi_user->st_key_info.en_cipher_type     = (oal_uint8)(pst_wep_key->ul_cipher);
    pst_multi_user->st_key_info.uc_default_index   = uc_key_index;

    /* 4.1 ����mib���� */
    mac_set_wep_default_keyid(pst_mac_vap, uc_key_index);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_default_mgmt_key
 ��������  : ���ù���֡��Կ
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2014��11��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_set_default_mgmt_key(mac_vap_stru *pst_mac_vap, oal_uint8 uc_key_index)
{
    mac_user_stru                *pst_multi_user;

    /* ����֡������Ϣ�������鲥�û��� */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        return OAL_ERR_CODE_SECURITY_USER_INVAILD;
    }

    /* keyidУ�� */
    if (uc_key_index < WLAN_NUM_TK || uc_key_index > WLAN_MAX_IGTK_KEY_INDEX)
    {
        return OAL_ERR_CODE_SECURITY_KEY_ID;
    }

    if (WLAN_80211_CIPHER_SUITE_BIP != (oal_uint8)pst_multi_user->st_key_info.ast_key[uc_key_index].ul_cipher)
    {
        return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }


    /* ����IGTK��keyid */
    pst_multi_user->st_key_info.uc_igtk_key_index   = uc_key_index;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_user_init_security_port
 ��������  : ��ʼ��STA ��������£����ݹ��˵Ĳ�����
 �������  : pst_hmac_sta
             pst_hmac_user_ap
 �������  : ��
 �� �� ֵ  : mac_status_code_enum_uint16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��11��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
void mac_vap_init_user_security_port(mac_vap_stru  *pst_mac_vap,
                                        mac_user_stru *pst_mac_user)
{
    mac_user_set_port(pst_mac_user, OAL_TRUE);

    if (OAL_TRUE != pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAActivated)
    {
        return;
    }

    /* �Ƿ����WPA ��WPA2 ���ܷ�ʽ */
    if ((OAL_TRUE != pst_mac_vap->st_cap_flag.bit_wpa)
        && (OAL_TRUE != pst_mac_vap->st_cap_flag.bit_wpa2))
    {
        return;
    }

    /* STA��Ҫ����Ƿ����802.1X ��֤��ʽ */
    if ((WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode
        && OAL_TRUE == mac_check_auth_policy(pst_mac_vap->pst_mib_info, WLAN_AUTH_SUITE_1X))
        || (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode))
    {
        mac_user_set_port(pst_mac_user, OAL_FALSE);
    }

    /* DTS2015081201896:����û��Ѿ�����������Ҫ��ʼ���û���������Ϊ������ */
    //mac_user_init_key(pst_mac_user);
}

/*****************************************************************************
 �� �� ��  : mac_vap_set_beacon
 ��������  : ��λ11X�˿�
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��24��
    ��    ��   : zwx287476
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_set_beacon(mac_vap_stru *pst_mac_vap, mac_beacon_param_stru *pst_beacon_param)
{
    mac_user_stru                        *pst_multi_user;
    wlan_mib_dot11RSNAConfigEntry_stru   *pst_mib_rsna_cfg;
    oal_uint32                            ul_loop;

    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == pst_beacon_param))
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_vap_set_beacon::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���֮ǰ�ļ���������Ϣ */
    mibset_RSNAClearWpaPairwiseCipherImplemented(pst_mac_vap);
    mibset_RSNAClearWpa2PairwiseCipherImplemented(pst_mac_vap);
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_FALSE);
    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_FALSE);
    pst_mac_vap->st_cap_flag.bit_wpa  = OAL_FALSE;
    pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_FALSE;
    mac_mib_clear_rsna_auth_suite(pst_mac_vap);

    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR = OAL_FALSE;
    pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC = OAL_FALSE;

    /* ����鲥��Կ��Ϣ */
    pst_multi_user = mac_res_get_mac_user(pst_mac_vap->us_multi_user_idx);
    if (OAL_PTR_NULL == pst_multi_user)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_beacon::pst_multi_user null .}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_beacon_param->en_privacy)
    {
        /* DTS2016052000621, ����鲥�û�������Ϣλ����vap down�ƶ����˴������vap down/up��STA����APUTʧ�����⡣ */
        /* ֻ�ڷǼ��ܳ�������������ܳ������������ø��� */
        mac_user_init_key(pst_multi_user);
        pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type = WLAN_KEY_TYPE_TX_GTK;
        return OAL_SUCC;
    }

    /* ʹ�ܼ��� */
    mac_mib_set_privacyinvoked(pst_mac_vap, OAL_TRUE);
    pst_mib_rsna_cfg = &pst_mac_vap->pst_mib_info->st_wlan_mib_rsna_cfg;

    if (0 == (pst_beacon_param->uc_crypto_mode & (WLAN_WPA_BIT | WLAN_WPA2_BIT)))
    {
        //OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_beacon::wep enabled");
        return OAL_SUCC;
    }
    /* WEP����ʱ����addbeacon����֮ǰ���Ѿ�ͨ��add key��������Կ�� */
    //mac_user_init_key(pst_multi_user);
    //pst_multi_user->st_user_tx_info.st_security.en_cipher_key_type = WLAN_KEY_TYPE_TX_GTK;

    mac_mib_set_rsnaactivated(pst_mac_vap, OAL_TRUE);
    /* �����鲥�׼� */
    switch (pst_beacon_param->uc_group_crypto)
    {
        case WLAN_80211_CIPHER_SUITE_TKIP:
            pst_mib_rsna_cfg->ul_dot11RSNAConfigGroupCipherSize = WLAN_TKIP_KEY_LEN * 8;
            break;
        case WLAN_80211_CIPHER_SUITE_CCMP:
            pst_mib_rsna_cfg->ul_dot11RSNAConfigGroupCipherSize = WLAN_CCMP_KEY_LEN * 8;
            break;
        default:
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
                           "{mac_vap_set_beacon::UNEXPECTED group_crypto[%d].}", pst_beacon_param->uc_group_crypto);
            return OAL_ERR_CODE_SECURITY_CHIPER_TYPE;
    }
    pst_mib_rsna_cfg->uc_dot11RSNAConfigGroupCipher     = pst_beacon_param->uc_group_crypto;

    //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
    //              "{mac_vap_set_beacon::WPA group [%d]}", pst_beacon_param->uc_group_crypto);

    /* ������֤�׼� */
    for(ul_loop = 0; ul_loop < MAC_AUTHENTICATION_SUITE_NUM; ul_loop++)
    {
        if (0xff == pst_beacon_param->auc_auth_type[ul_loop])
        {
            continue;
        }
        mac_mib_set_rsna_auth_suite(pst_mac_vap, pst_beacon_param->auc_auth_type[ul_loop]);
    }

    if (pst_beacon_param->uc_crypto_mode & WLAN_WPA_BIT)
    {
        pst_mac_vap->st_cap_flag.bit_wpa = OAL_TRUE;

        /* ����WPA������Կ�׼� */
        for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
        {
            if (0xff == pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop])
            {
                continue;
            }

            mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented(pst_mac_vap, pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop]);
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented
                = (WLAN_80211_CIPHER_SUITE_CCMP == pst_beacon_param->auc_pairwise_crypto_wpa[ul_loop])?(WLAN_CCMP_KEY_LEN * 8):(WLAN_TKIP_KEY_LEN * 8);

            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
             //             "{mac_vap_set_beacon::WPA pairwise [%d]}", pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
        }
    }

    if (pst_beacon_param->uc_crypto_mode & WLAN_WPA2_BIT)
    {
        pst_mac_vap->st_cap_flag.bit_wpa2 = OAL_TRUE;

        /* ����WPA2������Կ�׼� */
        for(ul_loop = 0; ul_loop < MAC_PAIRWISE_CIPHER_SUITES_NUM; ul_loop++)
        {
            /* DTS2015031010201 WIFI_SW: B130�汾��CI ��֤����SVN�ڵ�3399������汾��2.4G��ϼ����Ĵ�����ʧ��  */
            if (0xff == pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop])
            {
                continue;
            }

            mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented(pst_mac_vap, pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
            pst_mac_vap->pst_mib_info->ast_wlan_mib_rsna_cfg_wpa2_pairwise_cipher[ul_loop].ul_dot11RSNAConfigPairwiseCipherSizeImplemented
                = (WLAN_80211_CIPHER_SUITE_CCMP == pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop])?(WLAN_CCMP_KEY_LEN * 8):(WLAN_TKIP_KEY_LEN * 8);

            //OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG,
            //              "{mac_vap_set_beacon::WPA2 pairwise [%d]}", pst_beacon_param->auc_pairwise_crypto_wpa2[ul_loop]);
        }

        /* RSN ���� */
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPR  = (pst_beacon_param->us_rsn_capability & BIT6) ? OAL_TRUE : OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAMFPC  = (pst_beacon_param->us_rsn_capability & BIT7) ? OAL_TRUE : OAL_FALSE;
        pst_mac_vap->pst_mib_info->st_wlan_mib_privacy.en_dot11RSNAPreauthenticationActivated = pst_beacon_param->us_rsn_capability & BIT0;
        pst_mib_rsna_cfg->ul_dot11RSNAConfigNumberOfPTKSAReplayCountersImplemented = (pst_beacon_param->us_rsn_capability & 0x0C) >> 2;
        pst_mib_rsna_cfg->ul_dot11RSNAConfigNumberOfGTKSAReplayCountersImplemented = (pst_beacon_param->us_rsn_capability & 0x30) >> 4;

    }


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_vap_get_mac_addr
 ��������  : ��ȡvap�� mac��ַ
 �������  : dmac_vap_stru *pst_dmac_vap
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8* mac_vap_get_mac_addr(mac_vap_stru *pst_mac_vap)
{
#ifdef _PRE_WLAN_FEATURE_P2P
    if (IS_P2P_DEV(pst_mac_vap))
    {
        /* ��ȡP2P DEV MAC ��ַ����ֵ��probe req ֡�� */
        return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID;
    }
    else
#endif /* _PRE_WLAN_FEATURE_P2P */
    {
        /* ���õ�ַ2Ϊ�Լ���MAC��ַ */
        return pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID;
    }
}
#ifdef _PRE_WLAN_FEATURE_11R
/*****************************************************************************
 �� �� ��  : mac_mib_init_ft_cfg
 ��������  : ��ʼ��Fast BSS Trisition��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��17��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_mib_init_ft_cfg(mac_vap_stru *pst_mac_vap, oal_uint8 *puc_mde)
{

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_mib_init_ft_cfg::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_mib_init_ft_cfg::pst_mib_info null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if ((OAL_PTR_NULL == puc_mde) || (puc_mde[0] != MAC_EID_MOBILITY_DOMAIN) || (puc_mde[1] != 3))
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated = OAL_FALSE;
        return OAL_SUCC;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated = OAL_TRUE;
    pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.auc_dot11FTMobilityDomainID[0] = puc_mde[2];
    pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.auc_dot11FTMobilityDomainID[1] = puc_mde[3];
    if (puc_mde[4] & 1)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FTOverDSActivated = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FTOverDSActivated = OAL_FALSE;
    }
    if (puc_mde[4] & 2)
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FTResourceRequestSupported = OAL_TRUE;
    }
    else
    {
        pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FTResourceRequestSupported = OAL_FALSE;
    }
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : mac_mib_get_md_id
 ��������  : ��ȡ��ǰ��md id
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��17��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_mib_get_md_id(mac_vap_stru *pst_mac_vap, oal_uint16 *pus_mdid)
{

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_mib_init_ft_cfg::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_mac_vap->pst_mib_info)
    {
        OAM_ERROR_LOG0(0, OAM_SF_WPA, "{mac_mib_init_ft_cfg::pst_mib_info null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_FALSE == pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated)
    {
        return OAL_FAIL;
    }

    pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.en_dot11FastBSSTransitionActivated = OAL_TRUE;

    *pus_mdid = *(oal_uint16*)(pst_mac_vap->pst_mib_info->st_wlan_mib_fast_bss_trans_cfg.auc_dot11FTMobilityDomainID);

    return OAL_SUCC;
}
#endif //_PRE_WLAN_FEATURE_11R


#ifdef _PRE_WLAN_FEATURE_VOWIFI
/*****************************************************************************
 �� �� ��  : mac_vap_set_vowifi_mode
 ��������  : ����VoWiFi mode
 �������  :
 �������  : ��
 �� �� ֵ  : oal_int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��19��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 mac_vap_set_vowifi_param(mac_vap_stru *pst_mac_vap, mac_vowifi_cmd_enum_uint8 en_vowifi_cfg_cmd, oal_uint8 uc_value)
{
    oal_int8 c_value;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_VOWIFI, "{mac_vap_set_vowifi_param::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    switch (en_vowifi_cfg_cmd)
    {
        case VOWIFI_SET_MODE:
        {
            /* �쳣ֵ */
            if (uc_value >= VOWIFI_MODE_BUTT)
            {
                OAM_ERROR_LOG1(0, OAM_SF_VOWIFI, "{mac_vap_set_vowifi_param::MODE Value[%d] error!}", uc_value);
                return OAL_ERR_CODE_VOWIFI_SET_INVALID;
            }

            /*  MODE
                0: disable report of rssi change
                1: enable report when rssi lower than threshold(vowifi_low_thres)
                2: enable report when rssi higher than threshold(vowifi_high_thres)
            */
            pst_mac_vap->pst_vowifi_cfg_param->en_vowifi_mode  = uc_value;
            pst_mac_vap->pst_vowifi_cfg_param->uc_cfg_cmd_cnt |= BIT0;
            break;
        }
        case VOWIFI_SET_PERIOD:
        {
            /* �쳣ֵ */
            if ((uc_value < MAC_VOWIFI_PERIOD_MIN)||(uc_value > MAC_VOWIFI_PERIOD_MAX))
            {
                OAM_ERROR_LOG1(0, OAM_SF_VOWIFI, "{mac_vap_set_vowifi_param::PERIOD Value[%d] error!}", uc_value);
                return OAL_ERR_CODE_VOWIFI_SET_INVALID;
            }

            /*��λms,��Χ��1s��30s��, the period of monitor the RSSI when host suspended */
            pst_mac_vap->pst_vowifi_cfg_param->us_rssi_period_ms = uc_value *  1000;
            pst_mac_vap->pst_vowifi_cfg_param->uc_cfg_cmd_cnt   |= BIT1;

            break;
        }
        case VOWIFI_SET_LOW_THRESHOLD:
        {
            c_value = (oal_int8)uc_value;
            /* �쳣ֵ */
            if ((c_value < MAC_VOWIFI_LOW_THRESHOLD_MIN)||(c_value > MAC_VOWIFI_LOW_THRESHOLD_MAX))
            {
                OAM_ERROR_LOG1(0, OAM_SF_VOWIFI, "{mac_vap_set_vowifi_param::LOW_THRESHOLD Value[%d] error!}", c_value);
                return OAL_ERR_CODE_VOWIFI_SET_INVALID;
            }

            /* [-1, -100],vowifi_low_thres */
            pst_mac_vap->pst_vowifi_cfg_param->c_rssi_low_thres  = c_value;
            pst_mac_vap->pst_vowifi_cfg_param->uc_cfg_cmd_cnt   |= BIT2;

            break;
        }
        case VOWIFI_SET_HIGH_THRESHOLD:
        {
            c_value = (oal_int8)uc_value;
            /* �쳣ֵ */
            if ((c_value < MAC_VOWIFI_HIGH_THRESHOLD_MIN)||(c_value > MAC_VOWIFI_HIGH_THRESHOLD_MAX))
            {
                OAM_ERROR_LOG1(0, OAM_SF_VOWIFI, "{mac_vap_set_vowifi_param::HIGH_THRESHOLD Value[%d] error!}", c_value);
                return OAL_ERR_CODE_VOWIFI_SET_INVALID;
            }

            /* [-1, -100],vowifi_high_thres */
            pst_mac_vap->pst_vowifi_cfg_param->c_rssi_high_thres = c_value;
            pst_mac_vap->pst_vowifi_cfg_param->uc_cfg_cmd_cnt   |= BIT3;

            break;
        }
        case VOWIFI_SET_TRIGGER_COUNT:
        {
            /* �쳣ֵ */
            if ((uc_value < MAC_VOWIFI_TRIGGER_COUNT_MIN)||(uc_value > MAC_VOWIFI_TRIGGER_COUNT_MAX))
            {
                OAM_ERROR_LOG1(0, OAM_SF_VOWIFI, "{mac_vap_set_vowifi_param::TRIGGER_COUNT Value[%d] error!}", uc_value);
                return OAL_ERR_CODE_VOWIFI_SET_INVALID;
            }

            /*��1��100��, the continuous counters of lower or higher than threshold which will trigger the report to host */
            pst_mac_vap->pst_vowifi_cfg_param->uc_trigger_count_thres = uc_value;
            pst_mac_vap->pst_vowifi_cfg_param->uc_cfg_cmd_cnt        |= BIT4;

            break;
        }
        default:
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{mac_vap_set_vowifi_param::invalid cmd = %d!!}", en_vowifi_cfg_cmd);

            break;
    }

    /* ���������ռ���ϣ���ʼ��vowifi����ϱ�״̬ */
    if (BIT0 & pst_mac_vap->pst_vowifi_cfg_param->uc_cfg_cmd_cnt)
    {
        pst_mac_vap->pst_vowifi_cfg_param->uc_cfg_cmd_cnt     = 0;
        pst_mac_vap->pst_vowifi_cfg_param->en_vowifi_reported = OAL_FALSE;
    }

    return OAL_SUCC;

}
#endif /* _PRE_WLAN_FEATURE_VOWIFI */

/*****************************************************************************
 �� �� ��  : mac_vap_protection_autoprot_is_enabled
 ��������  : ��ѯ�Զ����������Ƿ���
 �������  : pst_hmac_vap : hmac vap�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_FALSE: ����δ������ OAL_TRUE:  ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��18��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_switch_enum_uint8 mac_vap_protection_autoprot_is_enabled(mac_vap_stru *pst_mac_vap)
{
    return pst_mac_vap->st_protection.bit_auto_protection;
}

/*lint -e19*/
//oal_module_symbol(mac_vap_set_p2p_channel);
#ifdef _PRE_WLAN_FEATURE_UAPSD
oal_module_symbol(g_uc_uapsd_cap);
#endif
oal_module_symbol(mac_vap_set_bssid);
oal_module_symbol(mac_vap_set_current_channel);
oal_module_symbol(mac_vap_init_wme_param);
oal_module_symbol(mac_mib_set_station_id);
oal_module_symbol(mac_vap_state_change);
#if 0
oal_module_symbol(mac_mib_get_station_id);
#endif
oal_module_symbol(mac_mib_set_bss_type);
oal_module_symbol(mac_get_bss_type);
oal_module_symbol(mac_mib_set_ssid);
oal_module_symbol(mac_get_ssid);
oal_module_symbol(mac_mib_set_beacon_period);
oal_module_symbol(mac_get_beacon_period);
oal_module_symbol(mac_mib_set_dtim_period);
#ifdef _PRE_WLAN_FEATURE_UAPSD
oal_module_symbol(mac_vap_set_uapsd_en);
oal_module_symbol(mac_vap_get_uapsd_en);
#endif
#if 0
oal_module_symbol(mac_mib_get_GroupReceivedFrameCount);
oal_module_symbol(mac_mib_set_GroupReceivedFrameCount);
oal_module_symbol(mac_vap_get_user_wme_info);
oal_module_symbol(mac_vap_set_user_wme_info);
#endif
oal_module_symbol(mac_mib_set_shpreamble);
oal_module_symbol(mac_mib_get_shpreamble);
oal_module_symbol(mac_vap_add_assoc_user);
oal_module_symbol(mac_vap_del_user);
oal_module_symbol(mac_vap_init);
oal_module_symbol(mac_vap_exit);
oal_module_symbol(mac_init_mib);
oal_module_symbol(mac_mib_get_ssid);
oal_module_symbol(mac_mib_get_bss_type);
oal_module_symbol(mac_mib_get_beacon_period);
oal_module_symbol(mac_mib_get_dtim_period);
oal_module_symbol(mac_vap_init_rates);
oal_module_symbol(mac_vap_init_by_protocol);
oal_module_symbol(mac_mib_set_RSNAConfigWpaPairwiseCipherImplemented);
oal_module_symbol(mac_mib_set_RSNAConfigWpa2PairwiseCipherImplemented);
oal_module_symbol(mibset_RSNAClearWpaPairwiseCipherImplemented);
oal_module_symbol(mibset_RSNAClearWpa2PairwiseCipherImplemented);
oal_module_symbol(mac_vap_config_vht_ht_mib_by_protocol);
oal_module_symbol(mac_mib_set_RSNAAuthenticationSuiteSelected);
oal_module_symbol(mac_vap_check_bss_cap_info_phy_ap);
oal_module_symbol(mac_mib_set_RSNAConfigAuthenticationSuiteImplemented);
oal_module_symbol(mac_get_wmm_cfg);
#ifdef _PRE_WLAN_FEATURE_EDCA_MULTI_USER_MULTI_AC
oal_module_symbol(mac_get_wmm_cfg_multi_user_multi_ac);
#endif
oal_module_symbol(mac_vap_get_bandwidth_cap);
oal_module_symbol(mac_vap_change_mib_by_bandwidth);
oal_module_symbol(mac_vap_init_rx_nss_by_protocol);
oal_module_symbol(mac_mib_clear_rsna_auth_suite);
oal_module_symbol(mac_mib_set_rsna_auth_suite);
oal_module_symbol(mac_dump_protection);
oal_module_symbol(mac_vap_set_aid);
oal_module_symbol(mac_vap_set_al_tx_payload_flag);
oal_module_symbol(mac_vap_set_assoc_id);
oal_module_symbol(mac_vap_set_al_tx_flag);
oal_module_symbol(mac_vap_set_tx_power);
oal_module_symbol(mac_vap_set_uapsd_cap);
oal_module_symbol(mac_vap_set_al_tx_first_run);
oal_module_symbol(mac_vap_set_multi_user_idx);
oal_module_symbol(mac_vap_set_wmm_params_update_count);
oal_module_symbol(mac_vap_set_rifs_tx_on);
#if 0
oal_module_symbol(mac_vap_set_tdls_prohibited);
oal_module_symbol(mac_vap_set_tdls_channel_switch_prohibited);
#endif
oal_module_symbol(mac_vap_set_11ac2g);
oal_module_symbol(mac_vap_set_hide_ssid);
oal_module_symbol(mac_get_p2p_mode);
oal_module_symbol(mac_vap_get_peer_obss_scan);
oal_module_symbol(mac_vap_set_peer_obss_scan);
oal_module_symbol(mac_vap_clear_app_ie);
oal_module_symbol(mac_vap_save_app_ie);
oal_module_symbol(mac_vap_set_rx_nss);
oal_module_symbol(mac_vap_find_user_by_macaddr);
oal_module_symbol(mac_vap_get_curr_baserate);

oal_module_symbol(mac_sta_init_bss_rates);

#ifdef _PRE_WLAN_FEATURE_SMPS
oal_module_symbol(mac_mib_get_smps);
oal_module_symbol(mac_vap_get_smps_mode);
oal_module_symbol(mac_vap_get_smps_en);
oal_module_symbol(mac_vap_set_smps);
#endif

oal_module_symbol(mac_device_find_user_by_macaddr);

oal_module_symbol(mac_vap_init_privacy);

oal_module_symbol(mac_mib_set_wep);
oal_module_symbol(mac_check_auth_policy);
oal_module_symbol(mac_vap_get_user_by_addr);

oal_module_symbol(mac_vap_add_beacon);
oal_module_symbol(mac_vap_add_key);
oal_module_symbol(mac_vap_get_default_key_id);
oal_module_symbol(mac_vap_set_default_key);
oal_module_symbol(mac_vap_set_default_mgmt_key);
oal_module_symbol(mac_vap_init_user_security_port);
oal_module_symbol(mac_vap_set_beacon);
oal_module_symbol(mac_protection_lsigtxop_check);
oal_module_symbol(mac_protection_set_lsig_txop_mechanism);
oal_module_symbol(mac_vap_get_user_protection_mode);
oal_module_symbol(mac_vap_protection_autoprot_is_enabled);
oal_module_symbol(mac_protection_set_rts_tx_param);


#ifdef _PRE_WLAN_FEATURE_VOWIFI
oal_module_symbol(mac_vap_set_vowifi_param);
#endif /* _PRE_WLAN_FEATURE_VOWIFI */


/*lint +e19*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


