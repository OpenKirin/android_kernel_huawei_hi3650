/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_roam_alg.c
  �� �� ��   : ����
  ��    ��   : guyanjie 00260350
  ��������   : 2015��3��18��
  ����޸�   :
  ��������   : ����ģ���㷨ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��18��
    ��    ��   : guyanjie 00260350
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oam_ext_if.h"
#include "mac_ie.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "hmac_fsm.h"
#include "hmac_sme_sta.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_scan.h"
#include "hmac_roam_main.h"
#include "hmac_roam_connect.h"
#include "hmac_roam_alg.h"
#include "hmac_mgmt_sta.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_ROAM_ALG_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
hmac_roam_rssi_capacity_stru   gst_rssi_table_11a_ofdm[ROAM_RSSI_LEVEL] = {
    {-75,               29300},
    {-82,               17300},
    {-90,               5400}
};
hmac_roam_rssi_capacity_stru   gst_rssi_table_11b[ROAM_RSSI_LEVEL] = {
    {-88,               8100},
    {-92,               4900},
    {-94,               900}

};
hmac_roam_rssi_capacity_stru   gst_rssi_table_11g_ofdm[ROAM_RSSI_LEVEL] = {
    {-75,               29300},
    {-82,               17300},
    {-90,               5400}
};
hmac_roam_rssi_capacity_stru   gst_rssi_table_ht20_ofdm[ROAM_RSSI_LEVEL] = {
    {-72,               58800},
    {-80,               35300},
    {-90,               5800}
};
hmac_roam_rssi_capacity_stru   gst_rssi_table_ht40_ofdm[ROAM_RSSI_LEVEL] = {
    {-75,               128100},
    {-77,               70500},
    {-87,               11600}
};
hmac_roam_rssi_capacity_stru   gst_rssi_table_vht80_ofdm[ROAM_RSSI_LEVEL] = {
    {-72,               256200},
    {-74,               141000},
    {-84,               23200}
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hmac_roam_alg_init
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_roam_alg_init(hmac_roam_info_stru *pst_roam_info, oal_int8 c_current_rssi)
{
    hmac_roam_alg_stru         *pst_roam_alg;

    if (pst_roam_info == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_alg_init::param null.}");
        return;
    }
    /*lint -e571*/
    OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{hmac_roam_alg_init c_current_rssi = %d.}", c_current_rssi);
    /*lint +e571*/

    pst_roam_alg = &(pst_roam_info->st_alg);
    if (c_current_rssi == ROAM_RSSI_LINKLOSS_TYPE)
    {
        pst_roam_info->st_static.ul_trigger_linkloss_cnt++;
    }
    else
    {
        pst_roam_info->st_static.ul_trigger_rssi_cnt++;
    }

    pst_roam_alg->ul_max_capacity       = 0;
    pst_roam_alg->pst_max_capacity_bss  = OAL_PTR_NULL;
    pst_roam_alg->c_current_rssi        = c_current_rssi;
    pst_roam_alg->c_max_rssi            = 0;
    pst_roam_alg->uc_another_bss_scaned = 0;
    /* �״ι���ʱ��ʼ�� pst_roam_alg->uc_invalid_scan_cnt   = 0x0; */
    pst_roam_alg->pst_max_rssi_bss      = OAL_PTR_NULL;

    return;
}

/*****************************************************************************
 �� �� ��  : hmac_roam_alg_get_delta_rssi
 ��������  : ����rssi����
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int8 hmac_roam_alg_adjust_rssi_increase(hmac_roam_info_stru *pst_roam_info, mac_bss_dscr_stru *pst_bss_dscr)
{
    oal_int8  c_current_rssi;
    oal_int8  c_target_rssi;
    oal_uint8 uc_delta_rssi;

    if (WLAN_BAND_5G == pst_bss_dscr->st_channel.en_band)
    {
        uc_delta_rssi = pst_roam_info->st_config.uc_delta_rssi_5G;
    }
    else
    {
        uc_delta_rssi = pst_roam_info->st_config.uc_delta_rssi_2G;
    }

    c_current_rssi = pst_roam_info->st_alg.c_current_rssi;
    c_target_rssi  = pst_bss_dscr->c_rssi;

    if(uc_delta_rssi < ROAM_RSSI_DIFF_4_DB)
    {
        uc_delta_rssi = ROAM_RSSI_DIFF_4_DB;
    }

    if (c_current_rssi >= ROAM_RSSI_NE70_DB)
    {
        return (c_target_rssi - c_current_rssi - (oal_int8)uc_delta_rssi);
    }

    if (uc_delta_rssi >= ROAM_RSSI_DIFF_4_DB + 2)
    {
        /* ����2DB��4DB*/
        uc_delta_rssi -= 2;
    }

    if (c_current_rssi >= ROAM_RSSI_NE75_DB)
    {
        return (c_target_rssi - c_current_rssi - (oal_int8)uc_delta_rssi);
    }

    if (uc_delta_rssi >= ROAM_RSSI_DIFF_4_DB + 2)
    {
        /* ����2DB��4DB*/
        uc_delta_rssi -= 2;
    }

    if (c_current_rssi >= ROAM_RSSI_NE80_DB)
    {
        return (c_target_rssi - c_current_rssi - (oal_int8)uc_delta_rssi);
    }

    return (c_target_rssi - c_current_rssi - ROAM_RSSI_DIFF_4_DB);
}

/*****************************************************************************
 �� �� ��  : hmac_roam_alg_add_list
 ��������  : ��bssid��ӵ��б���
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_roam_alg_add_bsslist(hmac_roam_bss_list_stru *pst_roam_bss_list, oal_uint8 *puc_bssid, roam_blacklist_type_enum_uint8 list_type)
{
    hmac_roam_bss_info_stru    *pst_cur_bss;
    hmac_roam_bss_info_stru    *pst_oldest_bss;
    hmac_roam_bss_info_stru    *pst_zero_bss;
    oal_uint8                   auc_mac_zero[WLAN_MAC_ADDR_LEN] = {0};
    oal_uint32                  ul_current_index;
    oal_uint32                  ul_now;
    oal_uint32                  ul_timeout;

    pst_oldest_bss = OAL_PTR_NULL;
    pst_zero_bss   = OAL_PTR_NULL;
    ul_now = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    for (ul_current_index = 0; ul_current_index < ROAM_LIST_MAX; ul_current_index++)
    {
        pst_cur_bss = &pst_roam_bss_list->ast_bss[ul_current_index];
        ul_timeout = (oal_uint32)pst_cur_bss->ul_timeout;
        if (0 == oal_compare_mac_addr(pst_cur_bss->auc_bssid, puc_bssid))
        {
            /* ���Ȳ����Ѵ��ڵļ�¼�����������ʱ����ʱ������������count */

            if (OAL_TIME_GET_RUNTIME(pst_cur_bss->ul_time_stamp, ul_now) > ul_timeout)
            {
                pst_cur_bss->ul_time_stamp = ul_now;
                pst_cur_bss->us_count      = 1;
            }
            else
            {
                pst_cur_bss->us_count++;
                if(pst_cur_bss->us_count == pst_cur_bss->us_count_limit)
                {
                    pst_cur_bss->ul_time_stamp = ul_now;
                }
            }
            return OAL_SUCC;
        }

        /* ��¼��һ���ռ�¼ */
        if (OAL_PTR_NULL != pst_zero_bss)
        {
            continue;
        }

        if (0 == oal_compare_mac_addr(pst_cur_bss->auc_bssid, auc_mac_zero))
        {
            pst_zero_bss = pst_cur_bss;
            continue;
        }

        /* ��¼һ���ǿ����ϼ�¼ */
        if (OAL_PTR_NULL == pst_oldest_bss)
        {
            pst_oldest_bss = pst_cur_bss;
        }
        else
        {
            if (OAL_TIME_GET_RUNTIME(pst_cur_bss->ul_time_stamp, ul_now) >
                OAL_TIME_GET_RUNTIME(pst_oldest_bss->ul_time_stamp, ul_now))
            {
                pst_oldest_bss = pst_cur_bss;
            }
        }
    }

    if (OAL_PTR_NULL == pst_zero_bss)
    {
        pst_zero_bss = pst_oldest_bss;
    }

    if (OAL_PTR_NULL != pst_zero_bss)
    {
        oal_set_mac_addr(pst_zero_bss->auc_bssid, puc_bssid);
        pst_zero_bss->ul_time_stamp = ul_now;
        pst_zero_bss->us_count      = 1;
        return OAL_SUCC;
    }
    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : hmac_roam_find_in_blacklist
 ��������  : ����б����Ƿ���ڸ�bssid
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_roam_alg_find_in_bsslist(hmac_roam_bss_list_stru *pst_roam_bss_list, oal_uint8 *puc_bssid)
{
    hmac_roam_bss_info_stru    *pst_cur_bss;
    oal_uint32                  ul_current_index;
    oal_uint32                  ul_now;
    oal_uint32                  ul_timeout;
    oal_uint32                  ul_delta_time;
    oal_uint16                  us_count_limit;

    ul_now         = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    for (ul_current_index = 0; ul_current_index < ROAM_LIST_MAX; ul_current_index++)
    {
        pst_cur_bss = &pst_roam_bss_list->ast_bss[ul_current_index];
        ul_timeout     = pst_cur_bss->ul_timeout;
        us_count_limit =  pst_cur_bss->us_count_limit;

        if (0 == oal_compare_mac_addr(pst_cur_bss->auc_bssid, puc_bssid))
        {
            /* ����ڳ�ʱʱ���ڳ���count_limit�����ϼ�¼ */
            ul_delta_time = OAL_TIME_GET_RUNTIME(pst_cur_bss->ul_time_stamp, ul_now);
            if ((ul_delta_time <= ul_timeout) &&
                (pst_cur_bss->us_count >= us_count_limit))
            {
                return OAL_TRUE;
            }
            return OAL_FALSE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_roam_alg_add_blacklist
 ��������  : ��bssid��ӵ��������б���
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_roam_alg_add_blacklist(hmac_roam_info_stru *pst_roam_info, oal_uint8 *puc_bssid, roam_blacklist_type_enum_uint8 list_type)
{
    oal_uint32      ul_ret;
    if ((pst_roam_info == OAL_PTR_NULL) || (puc_bssid == OAL_PTR_NULL))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_roam_alg_add_bsslist(&pst_roam_info->st_alg.st_blacklist, puc_bssid, list_type);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_alg_add_blacklist::hmac_roam_alg_add_list failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_roam_find_in_blacklist
 ��������  : ���������б����Ƿ���ڸ�bssid
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_roam_alg_find_in_blacklist(hmac_roam_info_stru *pst_roam_info, oal_uint8 *puc_bssid)
{
    if ((pst_roam_info == OAL_PTR_NULL) || (puc_bssid == OAL_PTR_NULL))
    {
        return OAL_FALSE;
    }

    return hmac_roam_alg_find_in_bsslist(&pst_roam_info->st_alg.st_blacklist, puc_bssid);
}


/*****************************************************************************
 �� �� ��  : hmac_roam_add_bss_history
 ��������  : ��bssid��ӵ���ʷ��ѡAP�б���
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_roam_alg_add_history(hmac_roam_info_stru *pst_roam_info, oal_uint8 *puc_bssid)
{
    oal_uint32      ul_ret;

    if ((pst_roam_info == OAL_PTR_NULL) || (puc_bssid == OAL_PTR_NULL))
    {
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = hmac_roam_alg_add_bsslist(&pst_roam_info->st_alg.st_history, puc_bssid, ROAM_BLACKLIST_TYPE_NORMAL_AP);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ROAM, "{hmac_roam_alg_add_history::hmac_roam_alg_add_list failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_roam_find_in_blacklist
 ��������  : �����ʷ��ѡ�б����Ƿ���ڸ�bssid
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_roam_alg_find_in_history(hmac_roam_info_stru *pst_roam_info, oal_uint8 *puc_bssid)
{
    if ((pst_roam_info == OAL_PTR_NULL) || (puc_bssid == OAL_PTR_NULL))
    {
        return OAL_FALSE;
    }

    return hmac_roam_alg_find_in_bsslist(&pst_roam_info->st_alg.st_history, puc_bssid);
}

/*****************************************************************************
 �� �� ��  : hmac_roam_alg_scan_channel_init
 ��������  : chu
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_roam_alg_scan_channel_init(hmac_roam_info_stru *pst_roam_info, mac_scan_req_stru *pst_scan_params)
{
    oal_uint32         ul_ret;
    oal_uint8          uc_chan_idx;
    oal_uint8          uc_chan_number;

    if ((pst_roam_info == OAL_PTR_NULL) || (pst_scan_params == OAL_PTR_NULL))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_alg_scan_channel_init::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_scan_params->uc_channel_nums  = 0;
    if (pst_roam_info->st_config.uc_scan_band & ROAM_BAND_2G_BIT)
    {
        switch (pst_roam_info->st_config.uc_scan_orthogonal)
        {
            case ROAM_SCAN_CHANNEL_ORG_1:
            {
                pst_scan_params->ast_channel_list[0].uc_chan_number = 1;
                pst_scan_params->ast_channel_list[0].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[0].uc_idx         = 0;

                pst_scan_params->ast_channel_list[1].uc_chan_number = 6;
                pst_scan_params->ast_channel_list[1].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[1].uc_idx         = 5;

                pst_scan_params->ast_channel_list[2].uc_chan_number = 11;
                pst_scan_params->ast_channel_list[2].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[2].uc_idx         = 10;

                pst_scan_params->uc_channel_nums = 3;
                break;
            }
            case ROAM_SCAN_CHANNEL_ORG_3:
            {
                pst_scan_params->ast_channel_list[0].uc_chan_number = 1;
                pst_scan_params->ast_channel_list[0].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[0].uc_idx         = 0;

                pst_scan_params->ast_channel_list[1].uc_chan_number = 5;
                pst_scan_params->ast_channel_list[1].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[1].uc_idx         = 4;

                pst_scan_params->ast_channel_list[2].uc_chan_number = 7;
                pst_scan_params->ast_channel_list[2].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[2].uc_idx         = 6;

                pst_scan_params->ast_channel_list[3].uc_chan_number = 13;
                pst_scan_params->ast_channel_list[3].en_band        = WLAN_BAND_2G;
                pst_scan_params->ast_channel_list[3].uc_idx         = 12;

                pst_scan_params->uc_channel_nums = 4;
                break;
            }
            default:
            {
                for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_chan_idx++)
                {
                    ul_ret = mac_is_channel_idx_valid(WLAN_BAND_2G, uc_chan_idx);
                    if (OAL_SUCC != ul_ret)
                    {
                        continue;
                    }
                    mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_chan_idx, &uc_chan_number);
                    pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].uc_chan_number = uc_chan_number;
                    pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].en_band        = WLAN_BAND_2G;
                    pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].uc_idx         = uc_chan_idx;
                    pst_scan_params->uc_channel_nums++;
                }
                break;
            }
        }
    }

    if (pst_roam_info->st_config.uc_scan_band & ROAM_BAND_5G_BIT)
    {
        for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_chan_idx++)
        {
            ul_ret = mac_is_channel_idx_valid(WLAN_BAND_5G, uc_chan_idx);
            if (OAL_SUCC != ul_ret)
            {
                continue;
            }
            mac_get_channel_num_from_idx(WLAN_BAND_5G, uc_chan_idx, &uc_chan_number);
            pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].uc_chan_number = uc_chan_number;
            pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].en_band        = WLAN_BAND_5G;
            pst_scan_params->ast_channel_list[pst_scan_params->uc_channel_nums].uc_idx         = uc_chan_idx;
            pst_scan_params->uc_channel_nums++;
        }
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_roam_alg_get_capacity_by_rssi
 ��������  : chu
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_roam_alg_get_capacity_by_rssi(wlan_protocol_enum_uint8 en_protocol, wlan_bw_cap_enum_uint8 en_bw_cap, oal_int8 c_rssi)
{
    hmac_roam_rssi_capacity_stru   *pst_rssi_table = OAL_PTR_NULL;
    oal_uint8                       uc_index;

    switch (en_protocol)
    {
        case WLAN_LEGACY_11A_MODE:
           pst_rssi_table = gst_rssi_table_11a_ofdm;
           break;

        case WLAN_LEGACY_11B_MODE:
            pst_rssi_table = gst_rssi_table_11b;
            break;

        case WLAN_LEGACY_11G_MODE:
        case WLAN_MIXED_ONE_11G_MODE:
        case WLAN_MIXED_TWO_11G_MODE:
            pst_rssi_table = gst_rssi_table_11g_ofdm;
            break;

        case WLAN_HT_MODE:
        case WLAN_VHT_MODE:
            if (en_bw_cap == WLAN_BW_CAP_20M)
            {
                pst_rssi_table = gst_rssi_table_ht20_ofdm;
            }
            else if (en_bw_cap == WLAN_BW_CAP_40M)
            {
                pst_rssi_table = gst_rssi_table_ht40_ofdm;
            }
            else
            {
                pst_rssi_table = gst_rssi_table_vht80_ofdm;
            }
            break;

        default:
            break;
    }

    if (OAL_PTR_NULL == pst_rssi_table)
    {
        return 0;
    }

    for(uc_index = 0; uc_index < ROAM_RSSI_LEVEL; uc_index++)
    {
        if (c_rssi >= pst_rssi_table[uc_index].c_rssi)
        {
            return pst_rssi_table[uc_index].ul_capacity_kbps;
        }
    }

    return 0;
}
/*****************************************************************************
 �� �� ��  : hmac_roam_alg_calc_avail_channel_capacity
 ��������  : chu
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��8��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_roam_alg_calc_avail_channel_capacity(mac_bss_dscr_stru *pst_bss_dscr)
{
    oal_uint32                 ul_capacity = 0;
    oal_uint32                 ul_avail_channel_capacity = 0;
    oal_uint32                 ul_ret;
    oal_uint8                  uc_channel_utilization = 0;
    oal_uint8                 *puc_obss_ie;
    oal_uint8                  uc_ie_offset;
    wlan_protocol_enum_uint8   en_protocol;

    ul_ret = hmac_sta_get_user_protocol(pst_bss_dscr, &en_protocol);
    if (OAL_SUCC != ul_ret)
    {
        return 0;
    }
    /***************************************************************************
        ------------------------------------------------------------------------
        |EID |Len |StationCount |ChannelUtilization |AvailableAdmissionCapacity|
        ------------------------------------------------------------------------
        |1   |1   |2            |1                  |2                         |
        ------------------------------------------------------------------------
        ***************************************************************************/
    /*lint -e416*/
    uc_ie_offset = MAC_80211_FRAME_LEN + MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
    puc_obss_ie = mac_find_ie(MAC_EID_QBSS_LOAD, (oal_uint8 *)(pst_bss_dscr->auc_mgmt_buff + uc_ie_offset), (oal_int32)(pst_bss_dscr->ul_mgmt_len - uc_ie_offset));
    /*lint +e416*/
    /* ����Ҫ����ChannelUtilization���������Ϊ3 */
    if (puc_obss_ie && (puc_obss_ie[1] >= 3))
    {
        uc_channel_utilization = *(puc_obss_ie + 4);
    }

    ul_capacity = hmac_roam_alg_get_capacity_by_rssi(en_protocol, pst_bss_dscr->en_bw_cap, pst_bss_dscr->c_rssi);

    ul_avail_channel_capacity = ul_capacity * (255 - uc_channel_utilization) / 255 / ROAM_CONCURRENT_USER_NUMBER;

    return ul_avail_channel_capacity;
}
/*****************************************************************************
 �� �� ��  : hmac_roam_alg_bss_in_ess
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��25��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_roam_alg_bss_in_ess(hmac_roam_info_stru *pst_roam_info, mac_bss_dscr_stru *pst_bss_dscr)
{
    hmac_vap_stru              *pst_hmac_vap;
    mac_vap_stru               *pst_mac_vap;
    hmac_roam_alg_stru         *pst_roam_alg;
    mac_cfg_ssid_param_stru     st_cfg_ssid;
    oal_uint8                   uc_stru_len;

    if ((OAL_PTR_NULL == pst_roam_info) || (OAL_PTR_NULL == pst_bss_dscr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_alg_bss_in_ess::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    mac_mib_get_ssid(pst_mac_vap, &uc_stru_len, (oal_uint8 *)(&st_cfg_ssid));

    if ((OAL_STRLEN(pst_bss_dscr->ac_ssid) != st_cfg_ssid.uc_ssid_len) ||
        (0 != oal_memcmp(st_cfg_ssid.ac_ssid, pst_bss_dscr->ac_ssid, st_cfg_ssid.uc_ssid_len)))
    {
        return OAL_SUCC;
    }
    pst_roam_alg = &(pst_roam_info->st_alg);

    /* �Ƿ�ɨ�赽�˵�ǰ������ bss, ����λ�������� */
    if (0 != oal_compare_mac_addr(pst_mac_vap->auc_bssid, pst_bss_dscr->auc_bssid))
    {
        pst_roam_alg->uc_another_bss_scaned = 1;
        hmac_roam_ignore_rssi_trigger(pst_hmac_vap, OAL_FALSE);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_roam_alg_bss_check
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��18��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_roam_alg_bss_check(hmac_roam_info_stru *pst_roam_info, mac_bss_dscr_stru *pst_bss_dscr)
{
    hmac_vap_stru              *pst_hmac_vap;
    mac_vap_stru               *pst_mac_vap;
    hmac_roam_alg_stru         *pst_roam_alg;
    mac_cap_info_stru          *pst_cap_info;
    oal_uint8                  *puc_pmkid;
    mac_cfg_ssid_param_stru     st_cfg_ssid;
    oal_uint32                  ul_ret;
    oal_uint32                  ul_avail_channel_capacity;
    oal_uint8                   uc_stru_len;
    oal_int8                    c_delta_rssi;
    oal_int8                    c_tmp_rssi;

    if ((OAL_PTR_NULL == pst_roam_info) || (OAL_PTR_NULL == pst_bss_dscr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ROAM, "{hmac_roam_alg_bss_check::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_ERR_CODE_ROAM_INVALID_VAP;
    }

    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);
    mac_mib_get_ssid(pst_mac_vap, &uc_stru_len, (oal_uint8 *)(&st_cfg_ssid));

    if ((OAL_STRLEN(pst_bss_dscr->ac_ssid) != st_cfg_ssid.uc_ssid_len) ||
        (0 != oal_memcmp(st_cfg_ssid.ac_ssid, pst_bss_dscr->ac_ssid, st_cfg_ssid.uc_ssid_len)))
    {
        return OAL_SUCC;
    }
    pst_roam_alg = &(pst_roam_info->st_alg);

    /* ��ѡHMAC_SCAN_MAX_VALID_SCANNED_BSS_EXPIREʱ�����ڵ���Чbss */
    if (oal_time_after((oal_uint32)OAL_TIME_GET_STAMP_MS(),(pst_bss_dscr->ul_timestamp + HMAC_SCAN_MAX_VALID_SCANNED_BSS_EXPIRE)))
    {
        return OAL_SUCC;
    }

    /* �������� */
    ul_ret = hmac_roam_alg_find_in_blacklist(pst_roam_info, pst_bss_dscr->auc_bssid);
    if (OAL_TRUE == ul_ret)
    {
        OAM_WARNING_LOG3(0, OAM_SF_ROAM,"{hmac_roam_alg_bss_check:: [%02X:XX:XX:XX:%02X:%02X] in blacklist!}",
                         pst_bss_dscr->auc_bssid[0], pst_bss_dscr->auc_bssid[4], pst_bss_dscr->auc_bssid[5]);
        return OAL_SUCC;
    }

    /* �ų���ǰbss��rssiֵ���㣬�����Ѿ�������dmac�ϱ���rssi */
    if (0 == oal_compare_mac_addr(pst_mac_vap->auc_bssid, pst_bss_dscr->auc_bssid))
    {
        return OAL_SUCC;
    }

    /*  wep��bssֱ�ӹ��˵� */
    pst_cap_info = (mac_cap_info_stru *)&pst_bss_dscr->us_cap_info;
    if ((0 == pst_bss_dscr->st_bss_sec_info.uc_bss_80211i_mode) &&
        (0 != pst_cap_info->bit_privacy))
    {
        return OAL_SUCC;
    }

    /*  open���ܷ�ʽ��wpa/wpa2ֱ�ӹ��˵� */
    /*lint -e731*/
    if ((0 == pst_cap_info->bit_privacy) != (OAL_TRUE != mac_mib_get_privacyinvoked(&pst_hmac_vap->st_vap_base_info)))
    {
        return OAL_SUCC;
    }
    /*lint +e731*/

    /* c_current_rssiΪ0ʱ����ʾlinkloss�ϱ��Ĵ���������Ҫ����rssi���� */
    c_delta_rssi = hmac_roam_alg_adjust_rssi_increase(pst_roam_info, pst_bss_dscr);
    if (c_delta_rssi <= 0)
    {
        return OAL_SUCC;
    }


    ul_avail_channel_capacity = hmac_roam_alg_calc_avail_channel_capacity(pst_bss_dscr);
    if ((0 != ul_avail_channel_capacity) &&
        ((OAL_PTR_NULL == pst_roam_alg->pst_max_capacity_bss) ||
        (ul_avail_channel_capacity > pst_roam_alg->ul_max_capacity)))
    {
	    //��ʱ����������
        //pst_roam_alg->ul_max_capacity      = ul_avail_channel_capacity;
        //pst_roam_alg->pst_max_capacity_bss = pst_bss_dscr;
    }

    c_tmp_rssi = pst_bss_dscr->c_rssi;
    /* �����Ѵ���pmk�����bss���мӷִ��� */
    puc_pmkid = hmac_vap_get_pmksa(pst_hmac_vap, pst_bss_dscr->auc_bssid);
    if (OAL_PTR_NULL != puc_pmkid)
    {
        c_tmp_rssi += ROAM_RSSI_DIFF_4_DB;
    }

    if ((OAL_PTR_NULL == pst_roam_alg->pst_max_rssi_bss) ||
        (c_tmp_rssi > pst_roam_alg->c_max_rssi))
    {
        pst_roam_alg->c_max_rssi        = c_tmp_rssi;
        pst_roam_alg->pst_max_rssi_bss  = pst_bss_dscr;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_roam_alg_need_to_stop_roam_trigger
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_roam_alg_need_to_stop_roam_trigger(hmac_roam_info_stru *pst_roam_info)
{
    hmac_vap_stru              *pst_hmac_vap;
    hmac_roam_alg_stru         *pst_roam_alg;

    if (OAL_PTR_NULL == pst_roam_info)
    {
         return OAL_FALSE;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_FALSE;
    }


    pst_roam_alg  = &(pst_roam_info->st_alg);

    if (pst_roam_alg->uc_another_bss_scaned)
    {
        pst_roam_alg->uc_invalid_scan_cnt = 0xff;
        return OAL_FALSE;
    }

    if (pst_roam_alg->uc_invalid_scan_cnt == 0xff)
    {
        return OAL_FALSE;
    }

    if (pst_roam_alg->uc_invalid_scan_cnt++ > 4)
    {
        pst_roam_alg->uc_invalid_scan_cnt = 0xff;
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_roam_alg_bss_check
 ��������  :
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
mac_bss_dscr_stru *hmac_roam_alg_select_bss(hmac_roam_info_stru *pst_roam_info)
{
    hmac_vap_stru              *pst_hmac_vap;
    mac_vap_stru               *pst_mac_vap;
    mac_bss_dscr_stru          *pst_bss_dscr;
    hmac_roam_alg_stru         *pst_roam_alg;
    oal_int8                    c_delta_rssi;

    if (OAL_PTR_NULL == pst_roam_info)
    {
         return OAL_PTR_NULL;
    }

    pst_hmac_vap = pst_roam_info->pst_hmac_vap;
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        return OAL_PTR_NULL;
    }

    pst_mac_vap   = &(pst_hmac_vap->st_vap_base_info);

    pst_roam_alg = &(pst_roam_info->st_alg);

    /* ȡ����� rssi �� bss */
    pst_bss_dscr = pst_roam_alg->pst_max_rssi_bss;

    if ((OAL_PTR_NULL != pst_roam_alg->pst_max_capacity_bss) && (pst_roam_alg->ul_max_capacity >= ROAM_THROUGHPUT_THRESHOLD))
    {
        /* ȡ����� capacity �� bss*/
        pst_bss_dscr = pst_roam_alg->pst_max_capacity_bss;
    }

    if(OAL_PTR_NULL == pst_bss_dscr)
    {
        /* should not be here */
        return OAL_PTR_NULL;
    }

    /* ���˵�ǰ������ bss */
    if (0 == oal_compare_mac_addr(pst_mac_vap->auc_bssid, pst_bss_dscr->auc_bssid))
    {
        return OAL_PTR_NULL;
    }

    /* rssi���洦�� */
    c_delta_rssi = hmac_roam_alg_adjust_rssi_increase(pst_roam_info, pst_bss_dscr);
    if (c_delta_rssi <= 0)
    {
        return OAL_PTR_NULL;
    }

    return pst_bss_dscr;
}

#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

