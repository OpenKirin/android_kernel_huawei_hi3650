/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_scan.c
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2014��11��26��
  ����޸�   :
  ��������   : ɨ��ģ�� hmac����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��26��
    ��    ��   : zhangheng
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
#include "oam_ext_if.h"
#include "mac_ie.h"
#include "mac_regdomain.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "hmac_fsm.h"
#include "hmac_sme_sta.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_scan.h"
#include "hmac_mgmt_sta.h"
#include "frw_ext_if.h"
#ifdef _PRE_SUPPORT_ACS
#include "dmac_acs.h"
#include "hmac_acs.h"
#endif
#include "hmac_chan_mgmt.h"
#include "hmac_p2p.h"
#ifdef _PRE_WLAN_FEATURE_DFS
#include "hmac_dfs.h"
#endif

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#ifdef _PRE_WLAN_FEATURE_ROAM
#include "hmac_roam_main.h"
#endif //_PRE_WLAN_FEATURE_ROAM

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_SCAN_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if defined(_PRE_WLAN_CHIP_TEST_ALG) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && defined(_PRE_DEBUG_MODE)
struct kobject     *g_scan_ct_sys_kobject = OAL_PTR_NULL;
#endif
oal_bool_enum_uint8 g_en_bgscan_enable_flag = OAL_TRUE;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
OAL_STATIC oal_bool_enum_uint8 hmac_parse_cipher_suit(mac_bss_dscr_stru *pst_bss_dscr, oal_uint8 uc_cipher_type,
                                                      oal_uint8 *puc_ie, oal_int32 l_len);
#endif

#if defined(_PRE_WLAN_CHIP_TEST_ALG) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && defined(_PRE_DEBUG_MODE)
OAL_STATIC oal_ssize_t  hmac_scan_ct_proc_read(oal_device_stru *dev, oal_device_attribute_stru *attr, char *buf);
OAL_STATIC OAL_DEVICE_ATTR(alg_test_result, OAL_S_IRUGO|OAL_S_IWUSR, hmac_scan_ct_proc_read, OAL_PTR_NULL);

/*****************************************************************************
 �� �� ��  : hmac_scan_ct_proc_read
 ��������  : scan ct proc read func
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��16��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_ssize_t hmac_scan_ct_proc_read(oal_device_stru *dev, oal_device_attribute_stru *attr, char *buf)

{
    hmac_device_stru                *pst_hmac_device;
    hmac_scan_record_stru           *pst_record;
    oal_int32                        l_len;

    /* ��ȡhmac device��ɨ�����м�¼ */
    pst_hmac_device = hmac_res_get_mac_dev(0);
    pst_record       = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt);

    l_len = OAL_SIZEOF(mac_scan_chan_stats_stru);

    oal_memcopy(buf, &(pst_record->ast_chan_results[0]), l_len);

    return l_len;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_ct_init
 ��������  : ����оƬ����proc�ļ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��19��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  hmac_scan_ct_init(oal_void)
{
    /* hi1102-cb add sys for 51/02 */
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    oal_int32           l_ret = OAL_SUCC;

    if(OAL_PTR_NULL == g_scan_ct_sys_kobject)
    {
        g_scan_ct_sys_kobject = kobject_create_and_add("scan_ct", OAL_PTR_NULL);
        l_ret = sysfs_create_file(g_scan_ct_sys_kobject, &dev_attr_alg_test_result.attr);
    }

    return l_ret;
#else
    return OAL_SUCC;
#endif
}

/*****************************************************************************
 �� �� ��  : hmac_scan_ct_exit
 ��������  : ɾ��оƬ����proc�ļ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��19��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_scan_ct_exit(oal_void)
{
    if(OAL_PTR_NULL != g_scan_ct_sys_kobject)
    {
        sysfs_remove_file(g_scan_ct_sys_kobject,&dev_attr_alg_test_result.attr);
        kobject_del(g_scan_ct_sys_kobject);
        g_scan_ct_sys_kobject = OAL_PTR_NULL;
    }
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_snprintf_hex
 ��������  : ��ӡ16��������
 �������  : puc_buf��ʾ�ڴ�ռ��ַ
             l_buf_size��ʾ�ڴ��С
             puc_data��ʾ����
             l_len��ʾ���ݴ�С
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��28��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 hmac_snprintf_hex(oal_uint8 *puc_buf, oal_int32 l_buf_size, oal_uint8 *puc_data, oal_int32 l_len)
{
    oal_int32       l_loop;
    oal_uint8      *puc_pos;
    oal_uint8      *puc_end;
    oal_int32       l_ret;

    if (l_buf_size <= 0)
    {
        return 0;
    }

    puc_pos = puc_buf;
    puc_end = puc_buf + l_buf_size;
    for (l_loop = 0; l_loop < l_len; l_loop++)
    {
        l_ret = OAL_SPRINTF((oal_int8 *)puc_pos, (oal_uint16)(puc_end - puc_pos), "%02x ", puc_data[l_loop]);
        if ((l_ret < 0) || (l_ret >= puc_end - puc_pos))
        {
            puc_buf[l_buf_size - 1] = '\0';
            return puc_pos - puc_buf;
        }

        puc_pos += l_ret;
    }

    puc_buf[l_buf_size - 1] = '\0';
    return puc_pos - puc_buf;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_print_scan_params
 ��������  : ��ӡɨ�赽��bss��Ϣ
 �������  : mac_scan_req_stru *pst_scan_params
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��28��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void hmac_scan_print_scan_params(mac_scan_req_stru *pst_scan_params, mac_vap_stru *pst_mac_vap)
{
    OAM_WARNING_LOG4(pst_scan_params->uc_vap_id, OAM_SF_SCAN, "hmac_scan_print_scan_params::Now Scan channel_num[%d] in [%d]ms with scan_func[0x%x], and ssid_num[%d]!",
                pst_scan_params->uc_channel_nums,
                pst_scan_params->us_scan_time,
                pst_scan_params->uc_scan_func,
                pst_scan_params->uc_ssid_num);

    OAM_WARNING_LOG3(pst_scan_params->uc_vap_id, OAM_SF_SCAN, "hmac_scan_print_scan_params::Scan param, p2p_scan[%d], max_scan_count_per_channel[%d], need back home_channel[%d]!",
            pst_scan_params->bit_is_p2p0_scan,
            pst_scan_params->uc_max_scan_count_per_channel,
            pst_scan_params->en_need_switch_back_home_channel);
    return;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_print_scanned_bss_info
 ��������  : ��ӡɨ�赽��bss��Ϣ
 �������  : oal_uint32 uc_device_id, device id
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��28��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_scan_print_scanned_bss_info(oal_uint8 uc_device_id)
{
    hmac_device_stru        *pst_hmac_device;
    hmac_bss_mgmt_stru      *pst_bss_mgmt;
    hmac_scanned_bss_info   *pst_scanned_bss;
    mac_bss_dscr_stru       *pst_bss_dscr;
    oal_dlist_head_stru     *pst_entry;
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    oal_uint8                   auc_sdt_parse_hdr[MAC_80211_FRAME_LEN];

    /* ��ȡhmac device */
    pst_hmac_device = hmac_res_get_mac_dev(uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{hmac_scan_print_scanned_bss_info::pst_hmac_device null.}");
        return;
    }

    /* ��ȡָ��ɨ�����Ĺ���ṹ���ַ */
    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);

    /* ��ȡ�� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ����ɨ�赽��bss��Ϣ */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);

        /* ����ʾ�����뵽��BSS֡ */
        if (OAL_TRUE == pst_scanned_bss->st_bss_dscr_info.en_new_scan_bss)
        {
            pst_scanned_bss->st_bss_dscr_info.en_new_scan_bss = OAL_FALSE;
            /*�ϱ�beacon��probe֡*/
            pst_frame_hdr  = (mac_ieee80211_frame_stru *)pst_bss_dscr->auc_mgmt_buff;

            /* ��beacon��duration�ֶ�(2�ֽ�)����Ϊrssi�Լ�channel,����SDT��ʾ */
            oal_memcopy((oal_uint8 *)auc_sdt_parse_hdr, (oal_uint8 *)pst_frame_hdr, MAC_80211_FRAME_LEN);
            auc_sdt_parse_hdr[2]  = (oal_uint8)pst_bss_dscr->c_rssi;
            auc_sdt_parse_hdr[3]  = pst_bss_dscr->st_channel.uc_chan_number;

            /* �ϱ�beacon֡����probe rsp֡ */
            /*lint -e416*/
            oam_report_80211_frame(BROADCAST_MACADDR,
                                   (oal_uint8 *)auc_sdt_parse_hdr,
                                   MAC_80211_FRAME_LEN,
                                   pst_bss_dscr->auc_mgmt_buff + MAC_80211_FRAME_LEN,
                                   (oal_uint16) pst_bss_dscr->ul_mgmt_len,
                                   OAM_OTA_FRAME_DIRECTION_TYPE_RX);
            /*lint +e416*/
        }
    }

    /* ����� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    return;
}


/*****************************************************************************
 �� �� ��  : hmac_scan_alloc_scanned_bss
 ��������  : �����ڴ棬�洢ɨ�赽��bss��Ϣ
 �������  : oal_uint32 ul_mgmt_len, �ϱ��Ĺ���֡�ĳ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/

OAL_STATIC hmac_scanned_bss_info *hmac_scan_alloc_scanned_bss(oal_uint32 ul_mgmt_len)
{
    hmac_scanned_bss_info    *pst_scanned_bss;

    /* �����ڴ棬�洢ɨ�赽��bss��Ϣ */
    pst_scanned_bss = oal_memalloc(OAL_SIZEOF(hmac_scanned_bss_info) + ul_mgmt_len - OAL_SIZEOF(pst_scanned_bss->st_bss_dscr_info.auc_mgmt_buff));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_scanned_bss))
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{hmac_scan_alloc_scanned_bss::alloc memory failed for storing scanned result.}");
        return OAL_PTR_NULL;
    }

    /* Ϊ������ڴ����� */
    OAL_MEMZERO(pst_scanned_bss, OAL_SIZEOF(hmac_scanned_bss_info) + ul_mgmt_len - OAL_SIZEOF(pst_scanned_bss->st_bss_dscr_info.auc_mgmt_buff));

    /* ��ʼ������ͷ�ڵ�ָ�� */
    oal_dlist_init_head(&(pst_scanned_bss->st_dlist_head));

     //pst_scanned_bss->st_bss_dscr_info.puc_mgmt_buff = (oal_uint8 *)pst_scanned_bss + OAL_SIZEOF(hmac_scanned_bss_info) - OAL_SIZEOF(pst_scanned_bss->st_bss_dscr_info.puc_mgmt_buff);

    return pst_scanned_bss;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_add_bss_to_list
 ��������  : ��ɨ�赽��bss��ӵ�����
 �������  : hmac_scanned_bss_info *pst_scanned_bss,        ����ӵ������ϵ�ɨ�赽��bss�ڵ�
             hmac_device_stru *pst_hmac_device,             hmac device�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_scan_add_bss_to_list(hmac_scanned_bss_info *pst_scanned_bss, hmac_device_stru *pst_hmac_device)
{
    hmac_bss_mgmt_stru  *pst_bss_mgmt;      /* ����ɨ�����Ľṹ�� */

    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);
    pst_scanned_bss->st_bss_dscr_info.en_new_scan_bss = OAL_TRUE;

    /* ������д����ǰ���� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ���ɨ�����������У�������ɨ�赽��bss���� */
    oal_dlist_add_tail(&(pst_scanned_bss->st_dlist_head), &(pst_bss_mgmt->st_bss_list_head));

    pst_bss_mgmt->ul_bss_num++;
    /* ���� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_del_bss_from_list
 ��������  : ��ɨ�赽��bss��ӵ�����
 �������  : hmac_scanned_bss_info *pst_scanned_bss,        ��ɾ����ɨ�赽��bss�ڵ�
             hmac_device_stru *pst_hmac_device,             hmac device�ṹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_scan_del_bss_from_list_nolock(hmac_scanned_bss_info *pst_scanned_bss, hmac_device_stru *pst_hmac_device)
{
    hmac_bss_mgmt_stru  *pst_bss_mgmt;      /* ����ɨ�����Ľṹ�� */

    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);

    /* ��������ɾ���ڵ㣬������ɨ�赽��bss���� */
    oal_dlist_delete_entry(&(pst_scanned_bss->st_dlist_head));

    pst_bss_mgmt->ul_bss_num--;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_clean_scan_record
 ��������  : ����ϴ�ɨ��������ص�ɨ���¼��Ϣ: ����ɨ�赽��bss��Ϣ�����ͷ��ڴ�ռ䡢�Լ�������Ϣ����
 �������  : hmac_scan_record_stru  *pst_scan_record
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_scan_clean_scan_record(hmac_scan_record_stru  *pst_scan_record)
{
    oal_dlist_head_stru             *pst_entry;
    hmac_scanned_bss_info           *pst_scanned_bss;
    hmac_bss_mgmt_stru              *pst_bss_mgmt;

    /* �����Ϸ��Լ�� */
    if (OAL_PTR_NULL == pst_scan_record)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_clean_scan_record::pst_scan_record is null.}");
        return;
    }

    /* 1.һ��Ҫ�����ɨ�赽��bss��Ϣ���ٽ������㴦�� */
    pst_bss_mgmt = &(pst_scan_record->st_bss_mgmt);

    /* ������д����ǰ���� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ��������ɾ��ɨ�赽��bss��Ϣ */
    while(OAL_FALSE == oal_dlist_is_empty(&(pst_bss_mgmt->st_bss_list_head)))
    {
        pst_entry       = oal_dlist_delete_head(&(pst_bss_mgmt->st_bss_list_head));
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);

        pst_bss_mgmt->ul_bss_num--;

        /* �ͷ�ɨ���������ڴ� */
        oal_free(pst_scanned_bss);
    }

    /* ������д����ǰ���� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    /* 2.������Ϣ���� */
    OAL_MEMZERO(pst_scan_record, OAL_SIZEOF(hmac_scan_record_stru));
    pst_scan_record->en_scan_rsp_status = MAC_SCAN_STATUS_BUTT;     /* ��ʼ��ɨ�����ʱ״̬��Ϊ��Чֵ */

    /* 3.���³�ʼ��bss������������� */
    pst_bss_mgmt = &(pst_scan_record->st_bss_mgmt);
    oal_dlist_init_head(&(pst_bss_mgmt->st_bss_list_head));
    oal_spin_lock_init(&(pst_bss_mgmt->st_lock));

    OAM_INFO_LOG0(0, OAM_SF_SCAN, "{hmac_scan_clean_scan_record::cleaned scan record success.}");

    return;
}


/*****************************************************************************
 �� �� ��  : hmac_is_connected_ap_bssid
 ��������  : �ж�����bssid�����Ƿ��ǹ�����AP��bssid,���ڲ��ϻ��Ѿ�������AP
 �������  : oal_uint8 uc_device_id,oal_uint8 auc_bssid[WLAN_MAC_ADDR_LEN]
 �������  : ��
 �� �� ֵ  : OAL_TRUE:��,OAL_FALSE:��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��5��
    ��    ��   : d00223710
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32 hmac_is_connected_ap_bssid(oal_uint8 uc_device_id, oal_uint8 auc_bssid[WLAN_MAC_ADDR_LEN])
{
    oal_uint8                    uc_vap_idx;
    mac_vap_stru                *pst_mac_vap;
    mac_device_stru             *pst_mac_device;

    pst_mac_device = mac_res_get_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_is_connected_ap_bssid::mac_res_get_dev return null.}");
        return OAL_FALSE;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
        {
            OAM_WARNING_LOG1(0, OAM_SF_P2P, "{hmac_is_connected_ap_bssid::mac_res_get_mac_vap fail! vap id is %d}",
                            pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if(IS_LEGACY_VAP(pst_mac_vap)
           && (MAC_VAP_STATE_UP == pst_mac_vap->en_vap_state))
        {
            if(0 == oal_memcmp(auc_bssid, pst_mac_vap->auc_bssid, WLAN_MAC_ADDR_LEN))
            {
                /* ���ϻ���ǰ������AP */
                OAM_INFO_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_is_connected_ap_bssid::connected AP bssid:%02X:XX:XX:XX:%02X:%02X}",
                                 auc_bssid[0], auc_bssid[4], auc_bssid[5]);

                return OAL_TRUE;
            }
        }

    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_clean_expire_scanned_bss
 ��������  : ����ɨ��������ʱ������ϴ�ɨ�����е��ڵ�bss��Ϣ
 �������  : hmac_scan_record_stru  *pst_scan_record
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��10��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void hmac_scan_clean_expire_scanned_bss(hmac_vap_stru *pst_hmac_vap, hmac_scan_record_stru  *pst_scan_record)
{
    oal_dlist_head_stru             *pst_entry;
    oal_dlist_head_stru             *pst_entry_tmp = OAL_PTR_NULL;
    hmac_bss_mgmt_stru              *pst_bss_mgmt;
    hmac_scanned_bss_info           *pst_scanned_bss;
    mac_bss_dscr_stru               *pst_bss_dscr;
    oal_uint32                       ul_curr_time_stamp;

    /* �����Ϸ��Լ�� */
    if (OAL_PTR_NULL == pst_scan_record)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_clean_expire_scanned_bss::scan record is null.}");
        return;
    }

    /* ����ɨ���bss����Ľṹ�� */
    pst_bss_mgmt = &(pst_scan_record->st_bss_mgmt);

    ul_curr_time_stamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    /* ������д����ǰ���� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ��������ɾ����һ��ɨ�����е��ڵ�bss��Ϣ */
    OAL_DLIST_SEARCH_FOR_EACH_SAFE(pst_entry, pst_entry_tmp, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);

        if (ul_curr_time_stamp - pst_bss_dscr->ul_timestamp < HMAC_SCAN_MAX_SCANNED_BSS_EXPIRE)
        {
            OAM_INFO_LOG0(0, OAM_SF_SCAN,
                             "{hmac_scan_clean_expire_scanned_bss::do not remove the BSS, because it has not expired.}");
            continue;
        }

        /* ���ϻ���ǰ���ڹ�����AP */
        if(hmac_is_connected_ap_bssid(pst_scan_record->uc_device_id, pst_bss_dscr->auc_bssid))
        {
            pst_bss_dscr->c_rssi = pst_hmac_vap->station_info.signal;
            continue;
        }

        /* ��������ɾ���ڵ㣬������ɨ�赽��bss���� */
        oal_dlist_delete_entry(&(pst_scanned_bss->st_dlist_head));
        pst_bss_mgmt->ul_bss_num--;

        /* �ͷŶ�Ӧ�ڴ� */
        oal_free(pst_scanned_bss);
    }

    /* ������д����ǰ���� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));
    return;
}


/*****************************************************************************
 �� �� ��  : hmac_scan_find_scanned_bss_dscr_by_index
 ��������  : ����bss index���Ҷ�Ӧ��bss dscr�ṹ��Ϣ
 �������  : oal_uint8  uc_device_id,        device id
             oal_uint32 ul_bss_index,        bss    index
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/

mac_bss_dscr_stru *hmac_scan_find_scanned_bss_dscr_by_index(oal_uint8  uc_device_id,
                                                                         oal_uint32 ul_bss_index)
{
    oal_dlist_head_stru             *pst_entry;
    hmac_scanned_bss_info           *pst_scanned_bss;
    hmac_device_stru                *pst_hmac_device;
    hmac_bss_mgmt_stru              *pst_bss_mgmt;
    oal_uint8                        ul_loop;

    /* ��ȡhmac device �ṹ */
    pst_hmac_device = hmac_res_get_mac_dev(uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_find_scanned_bss_by_index::pst_hmac_device is null.}");
        return OAL_PTR_NULL;
    }

    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);

    /* ������ɾ����ǰ���� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ������������ܹ�ɨ���bss�����������쳣 */
    if (ul_bss_index >= pst_bss_mgmt->ul_bss_num)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{hmac_scan_find_scanned_bss_by_index::no such bss in bss list!}");

        /* ���� */
        oal_spin_unlock(&(pst_bss_mgmt->st_lock));
        return OAL_PTR_NULL;
    }

    ul_loop = 0;
    /* �����������ض�Ӧindex��bss dscr��Ϣ */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);

        /* ��ͬ��bss index���� */
        if (ul_bss_index == ul_loop)
        {
            /* ���� */
            oal_spin_unlock(&(pst_bss_mgmt->st_lock));
            return &(pst_scanned_bss->st_bss_dscr_info);
        }

        ul_loop++;
    }
    /* ���� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    return OAL_PTR_NULL;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_find_scanned_bss_by_bssid
 ��������  : ������ͬ��bssid��bss�Ƿ���ֹ�
 �������  : oal_uint8 uc_device_id,        device id
             oal_uint8 *puc_bssid,          bssid��Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
hmac_scanned_bss_info *hmac_scan_find_scanned_bss_by_bssid(hmac_bss_mgmt_stru *pst_bss_mgmt, oal_uint8 *puc_bssid)
{
    oal_dlist_head_stru             *pst_entry;
    hmac_scanned_bss_info           *pst_scanned_bss;

    /* �������������������Ƿ��Ѿ�������ͬbssid��bss��Ϣ */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);

        /* ��ͬ��bssid��ַ */
        if (0 == oal_compare_mac_addr(pst_scanned_bss->st_bss_dscr_info.auc_bssid, puc_bssid))
        {
            return pst_scanned_bss;
        }
    }

    return OAL_PTR_NULL;
}


#if defined (_PRE_WLAN_FEATURE_WPA2)
/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_list_rsn
 ��������  : STA ���´� scan�� probe response ֡���յ���AP RSN��ȫ��Ϣ
 �������  : pst_bss_dscr
             puc_ie

 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��21��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_scan_update_bss_list_rsn(mac_bss_dscr_stru *pst_bss_dscr, oal_uint8 *puc_ie)
{
    oal_uint8                    uc_index               = 0;
    oal_uint16                   us_ver                 = 0;
    oal_int32                    l_ie_len_left         = 0;

    /*************************************************************************/
    /*                  RSN Element Format                                   */
    /* --------------------------------------------------------------------- */
    /* |Element ID | Length | Version | Group Cipher Suite | Pairwise Cipher */
    /* --------------------------------------------------------------------- */
    /* |     1     |    1   |    2    |         4          |       2         */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* Suite Count| Pairwise Cipher Suite List | AKM Suite Count | AKM Suite List */
    /* --------------------------------------------------------------------- */
    /*            |         4*m                |     2           |   4*n     */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* |RSN Capabilities|PMKID Count|PMKID List|Group Management Cipher Suite*/
    /* --------------------------------------------------------------------- */
    /* |        2       |    2      |   16 *s  |               4           | */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/


    /* RSN IE����,������Element ID �� Length�ֶ� */
    l_ie_len_left = puc_ie[1];

    /* ���� RSN IE �� IE ���� */
    uc_index += 2;

    /* ��ȡRSN �汾��,2���ֽ� */
    if(l_ie_len_left > 2)
    {
        us_ver = OAL_MAKE_WORD16(puc_ie[uc_index], puc_ie[uc_index + 1]);
        if (MAC_RSN_IE_VERSION != us_ver)
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_scan_update_bss_list_rsn::invalid us_ver[%d].}", us_ver);

            return OAL_FALSE;
        }

        /* ���� RSN �汾�ų���,2���ֽ� */
        uc_index += 2;
        l_ie_len_left -= 2;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_scan_update_bss_list_rsn::ie too short for version:%d.}", l_ie_len_left);
        return OAL_FALSE;
    }

    /* ���� RSNA */
    pst_bss_dscr->st_bss_sec_info.uc_bss_80211i_mode |= DMAC_RSNA_802_11I;

    return hmac_parse_cipher_suit(pst_bss_dscr, DMAC_RSNA_802_11I, puc_ie + uc_index, l_ie_len_left);
}
#endif

#if defined (_PRE_WLAN_FEATURE_WPA)
/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_list_wpa
 ��������  : STA ���´� scan�� probe response ֡���յ���AP WPA ��ȫ��Ϣ
 �������  : pst_bss_dscr
             puc_ie

 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��21��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_scan_update_bss_list_wpa(mac_bss_dscr_stru *pst_bss_dscr, oal_uint8 *puc_ie)
{
    oal_uint8                    uc_index               = 0;
    oal_uint16                   us_ver                 = 0;
    oal_int32                    l_ie_len_left          = 0;

    /*************************************************************************/
    /*                  WPA Element Format                                   */
    /* --------------------------------------------------------------------- */
    /* |Element ID | Length |    WPA OUI    |  Version |  Group Cipher Suite */
    /* --------------------------------------------------------------------- */
    /* |     1     |   1    |        4      |     2    |         4           */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* Pairwise Cipher |  Pairwise Cipher   |                 |              */
    /* Suite Count     |    Suite List      | AKM Suite Count |AKM Suite List*/
    /* --------------------------------------------------------------------- */
    /*        2        |          4*m       |         2       |     4*n      */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* WPA IE����,������Element ID �� Length�ֶ� */
    l_ie_len_left = puc_ie[1];
    /* ���WPA OUI(4 �ֽ�) */
    if(l_ie_len_left < 4)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_scan_update_bss_list_wpa::invalid WPA IE LEN:%d.}", l_ie_len_left);
        return OAL_FALSE;
    }
    /* ���� WPA OUI(4 �ֽ�)  */
    l_ie_len_left -= 4;

    /* ���� WPA IE(1 �ֽ�) ��IE ����(1 �ֽ�) ��WPA OUI(4 �ֽ�)  */
    uc_index = 2 + 4;

    /* ��ȡ�汾��,2���ֽ� */
    if(l_ie_len_left > 2)
    {
        us_ver = OAL_MAKE_WORD16(puc_ie[uc_index], puc_ie[uc_index + 1]);
        /* �Ա�WPA �汾��Ϣ */
        if (MAC_WPA_IE_VERSION != us_ver)
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_scan_update_bss_list_wpa::invalid WPA version[%d].}", us_ver);

            return OAL_FALSE;
        }

        /* ���� �汾�� ���� */
        uc_index += 2;
        l_ie_len_left -= 2;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_scan_update_bss_list_wpa::ie too short for version:%d.}", l_ie_len_left);
        return OAL_FALSE;
    }

    /* ���� WPA */
    pst_bss_dscr->st_bss_sec_info.uc_bss_80211i_mode |= DMAC_WPA_802_11I;

    return hmac_parse_cipher_suit(pst_bss_dscr, DMAC_WPA_802_11I, puc_ie + uc_index, l_ie_len_left);
}
#endif

#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)

/*****************************************************************************
 �� �� ��  : hmac_parse_cipher_suit
 ��������  : STA ���´� scan�� probe response ֡���յ���AP WPA ��ȫ��Ϣ
 �������  : pst_bss_dscr
             puc_ie
             ul_len
             �����ɵ����߱�֤�Ϸ�

 �������  : index
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��6��7��
    ��    ��   : d00223710
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_parse_cipher_suit(mac_bss_dscr_stru *pst_bss_dscr, oal_uint8 uc_cipher_type,
                                                      oal_uint8 *puc_ie, oal_int32 l_len)
{
    oal_uint8                    uc_index               = 0;
    oal_uint16                   us_temp                = 0;
    oal_uint16                   us_pcip_num            = 0;
    oal_uint16                   us_auth_num            = 0;
    oal_uint16                   us_suite_count         = 0;
    oal_int32                    l_ie_len_left          = l_len;

    oal_uint8                   *puc_oui                = OAL_PTR_NULL;
    oal_uint8                   *puc_pcip_policy        = OAL_PTR_NULL;
    oal_uint8                   *puc_grp_policy         = OAL_PTR_NULL;
    oal_uint8                   *puc_auth_policy        = OAL_PTR_NULL;
    mac_bss_80211i_info_stru    *pst_bss_80211i_info    = &(pst_bss_dscr->st_bss_sec_info);

    /*************************************************************************/
    /*                  WPA / RSN Element Format                             */
    /* --------------------------------------------------------------------- */
    /* |Group Cipher Suite | Pairwise Cipher Suite Count */
    /* --------------------------------------------------------------------- */
    /* |        4          |       2                     */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* | Pairwise Cipher Suite List | AKM Suite Count | AKM Suite List */
    /* --------------------------------------------------------------------- */
    /* |         4*m                |     2           |   4*n          */
    /* --------------------------------------------------------------------- */
    /* --------------------------------------------------------------------- */
    /* |RSN Capabilities|*/
    /* --------------------------------------------------------------------- */
    /* |        2       |*/
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /**����WPA/RSN������cipher suit**/
    /**puc_ieָ��Group Cipher Suite,l_lenָpuc_ie���� **/
    if(DMAC_WPA_802_11I == uc_cipher_type)
    {
        puc_oui = g_auc_wpa_oui;
        puc_grp_policy  = &(pst_bss_80211i_info->uc_wpa_grp_policy);
        puc_pcip_policy = pst_bss_80211i_info->auc_wpa_pairwise_policy;
        puc_auth_policy = pst_bss_80211i_info->auc_wpa_auth_policy;
    }
    else if(DMAC_RSNA_802_11I == uc_cipher_type)
    {
        puc_oui = g_auc_rsn_oui;
        puc_grp_policy  = &(pst_bss_80211i_info->uc_rsn_grp_policy);
        puc_pcip_policy =   pst_bss_80211i_info->auc_rsn_pairwise_policy;
        puc_auth_policy =   pst_bss_80211i_info->auc_rsn_auth_policy;
    }
    else
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::invalid OUI.}");
        return OAL_FALSE;
    }

    oal_memset(puc_pcip_policy, 0xFF, MAC_PAIRWISE_CIPHER_SUITES_NUM);
    oal_memset(puc_auth_policy, 0xFF, MAC_AUTHENTICATION_SUITE_NUM);

    /* ��ȡ�鲥��Կ�׼�,4���ֽ� */
    if(l_ie_len_left > 4)
    {
        if (0 != oal_memcmp(puc_oui, puc_ie + uc_index, MAC_OUI_LEN))
        {
            OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::invalid group OUI.}");
            return OAL_FALSE;
        }
        *puc_grp_policy = puc_ie[uc_index + MAC_OUI_LEN];

        /* �����鲥��Կ�׼����� */
        uc_index += 4;
        l_ie_len_left -= 4;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::ie too short group policy:%d.}", l_ie_len_left);
        return OAL_FALSE;
    }

    /* ��ȡ�ɶ���Կ�׼�����,����2���ֽڳ��� */
    if(l_ie_len_left > 2)
    {
        /* DTS2016060609164������׼��������ֽ��쳣Ϊ1��Ŀǰ�׼�������Ӧ����1���ֽڴ�С�������ǳ����쳣 */
        us_pcip_num = OAL_MAKE_WORD16(puc_ie[uc_index], puc_ie[uc_index+1]) & 0xFF;
        uc_index += 2;
        l_ie_len_left -= 2;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::ie too short for pairwise key mgmt:%d.}", l_ie_len_left);
        return OAL_FALSE;
    }

    /* ȷ�ϵ����׼������Ƿ���ʵ��ie������ƥ�� */
    if((0 == us_pcip_num) || (us_pcip_num > l_ie_len_left / 4))
    {
        OAM_WARNING_LOG2(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::ie count botch pairwise:%d,left:%d}",
                                           us_pcip_num, l_ie_len_left);
        return OAL_FALSE;
    }

    us_suite_count = 0;
    for (us_temp = 0; us_temp < us_pcip_num; us_temp++)
    {
        if (0 != oal_memcmp(puc_oui, puc_ie + uc_index, MAC_OUI_LEN))
        {
            OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::invalid pairwise OUI,ignore this ie.}");
            /* ���ڲ�ʶ��ĳɶ���Կ�׼������Ա��� */
            uc_index += 4;
            l_ie_len_left -= 4;
            continue;
        }
        if(us_suite_count < MAC_PAIRWISE_CIPHER_SUITES_NUM)
        {
            /* �ɶ���Կ�׼������������Ϊ2���������ټ������� */
            puc_pcip_policy[us_suite_count++] = puc_ie[uc_index + MAC_OUI_LEN];
        }
        else
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::us_suite_count reach max,ignore this ie,us_pcip_num:%d.}",
                             us_pcip_num);
        }

        uc_index += 4;
        l_ie_len_left -= 4;
    }


    /* ��ȡ��֤�׼�����,����2���ֽڳ��� */
    if(l_ie_len_left > 2)
    {
        /* DTS2016060609164������׼��������ֽ��쳣Ϊ1��Ŀǰ�׼�������Ӧ����1���ֽڴ�С�������ǳ����쳣 */
        us_auth_num = OAL_MAKE_WORD16(puc_ie[uc_index], puc_ie[uc_index+1]) & 0xFF;
        uc_index += 2;
        l_ie_len_left -= 2;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::ie too short for aka suite:%d.}", l_ie_len_left);
        return OAL_FALSE;
    }

    /* ȷ����֤�׼������Ƿ���ʵ��ie������ƥ�� */
    if((0 == us_auth_num) || (us_auth_num > l_ie_len_left / 4))
    {
        OAM_WARNING_LOG2(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::ie count botch aka:%d,left:%d}",
                                           us_auth_num, l_ie_len_left);
        return OAL_FALSE;
    }

    /* ��ȡ��֤���� */
    us_suite_count = 0;
    for (us_temp = 0; us_temp < us_auth_num; us_temp++)
    {
        if (0 != oal_memcmp(puc_oui, puc_ie + uc_index, MAC_OUI_LEN))
        {
            OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::invalid WPA auth OUI,ignore this ie.}");
            /* ���ڲ�ʶ���AKM�׼������Ա��� */
            uc_index += 4;
            l_ie_len_left -= 4;
            continue;
        }

        if(us_suite_count < WLAN_AUTHENTICATION_SUITES)
        {
            /* AKM�׼������������Ϊ2���������ټ������� */
            puc_auth_policy[us_suite_count++] = puc_ie[uc_index + MAC_OUI_LEN];
        }
        else
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_parse_cipher_suit::us_suite_count reach max,ignore this ie,us_auth_num:%d.}",
                             us_auth_num);
        }
        uc_index += 4;
        l_ie_len_left -= 4;
    }

    /* ��ȡ RSN ����,2���ֽ� */
    if(DMAC_RSNA_802_11I == uc_cipher_type)
    {
        if(l_ie_len_left >=2)
        {
            pst_bss_80211i_info->auc_rsn_cap[0] = *(puc_ie + uc_index++);
            pst_bss_80211i_info->auc_rsn_cap[1] = *(puc_ie + uc_index++);

            l_ie_len_left -= 2;
        }
        else
        {
            /* ������Ϣ����עʧ�����,������ʧ��,wpa_supplicant�ڽ���ʱҲ����ע,������������ */
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_scan_update_bss_list_rsn::ie too short for rsn cap:%d.}", l_ie_len_left);
        }
    }

    return OAL_TRUE;
}


/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_list_security
 ��������  : STA ���´� scan�� probe response ֡���յ���AP ��ȫ��Ϣ
 �������  : mac_bss_dscr_stru *pst_bss_dscr
             oal_uint8 *puc_frame_body
             oal_uint16 us_frame_len
             oal_uint16 us_offset
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��30��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void hmac_scan_update_bss_list_security(mac_bss_dscr_stru *pst_bss_dscr,
                                                                oal_uint8 *puc_frame_body,
                                                                oal_uint16 us_frame_len,
                                                                oal_uint16 us_offset)
{
    oal_uint8           *puc_ie;
    oal_bool_enum_uint8  en_ret;

    /* ��ȫ�����ϢԪ�� */
    /* ��յ�ǰ bss_info �ṹ�еİ�ȫ��Ϣ */
    oal_memset(&(pst_bss_dscr->st_bss_sec_info), 0xff, sizeof(mac_bss_80211i_info_stru));
    pst_bss_dscr->st_bss_sec_info.uc_bss_80211i_mode = 0;
    pst_bss_dscr->st_bss_sec_info.auc_rsn_cap[0]     = 0;
    pst_bss_dscr->st_bss_sec_info.auc_rsn_cap[1]     = 0;

#if defined (_PRE_WLAN_FEATURE_WPA2)
    //puc_ie = mac_get_rsn_ie(puc_frame_body, us_frame_len, us_offset);
    puc_ie = mac_find_ie(MAC_EID_RSN, puc_frame_body + us_offset, (oal_int32)(us_frame_len - us_offset));
    if (OAL_PTR_NULL != puc_ie)
    {
        /* ���´�beacon ���յ��� RSN ��ȫ�����Ϣ�� pst_bss_dscr �� */
        en_ret = hmac_scan_update_bss_list_rsn(pst_bss_dscr, puc_ie);
        if (OAL_FALSE == en_ret)
        {
            /* �����ȡRSN ��Ϣʧ�ܣ����ϱ�֡����Ϣ��SDT */
            oam_report_80211_frame(BROADCAST_MACADDR,
                                   puc_frame_body - MAC_80211_FRAME_LEN,
                                   MAC_80211_FRAME_LEN,
                                   puc_frame_body,
                                   us_frame_len + MAC_80211_FRAME_LEN,
                                   OAM_OTA_FRAME_DIRECTION_TYPE_RX);
        }
    }
#endif

#if defined (_PRE_WLAN_FEATURE_WPA)
    //puc_ie = mac_get_wpa_ie(puc_frame_body, us_frame_len, us_offset);
    puc_ie = mac_find_vendor_ie(MAC_WLAN_OUI_MICROSOFT, MAC_OUITYPE_WPA, puc_frame_body + us_offset, (oal_int32)(us_frame_len - us_offset));
    if (OAL_PTR_NULL != puc_ie)
    {
        /* ���´�beacon ���յ��� WPA ��ȫ�����Ϣ�� pst_bss_dscr �� */
        en_ret = hmac_scan_update_bss_list_wpa(pst_bss_dscr, puc_ie);
        if (OAL_FALSE == en_ret)
        {
            /* �����ȡ��ȫ��Ϣʧ�ܣ����ϱ�֡����Ϣ��SDT */
            oam_report_80211_frame(BROADCAST_MACADDR,
                                   puc_frame_body - MAC_80211_FRAME_LEN,
                                   MAC_80211_FRAME_LEN,
                                   puc_frame_body,
                                   us_frame_len + MAC_80211_FRAME_LEN,
                                   OAM_OTA_FRAME_DIRECTION_TYPE_RX);
        }
    }
#endif
}
#endif /* defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2) */

/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_list_wmm
 ��������  : ����wmm�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  hmac_scan_update_bss_list_wmm(mac_bss_dscr_stru   *pst_bss_dscr,
                                                                         oal_uint8           *puc_frame_body,
                                                                         oal_uint16           us_frame_len)
{
    oal_uint8  *puc_ie;

    pst_bss_dscr->uc_wmm_cap   = OAL_FALSE;
    pst_bss_dscr->uc_uapsd_cap = OAL_FALSE;

    if (us_frame_len <= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN))
    {
        OAM_WARNING_LOG1(0,OAM_SF_ASSOC,"{hmac_scan_update_bss_list_wmm::us_frame_len[%d]!}",us_frame_len);
        return;
    }

    us_frame_len   -= (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);
    puc_frame_body += (MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN);

    puc_ie = mac_get_wmm_ie(puc_frame_body, us_frame_len);
    if (OAL_PTR_NULL != puc_ie)
    {
         pst_bss_dscr->uc_wmm_cap = OAL_TRUE;

         /* --------------------------------------------------------------------------------- */
         /* WMM Information/Parameter Element Format                                          */
         /* ----------------------------------------------------------------------------------*/
         /* EID | IE LEN | OUI | OUIType | OUISubtype | Version | QoSInfo | OUISubtype based |*/
         /* --------------------------------------------------------------------------------- */
         /* 1   |   1    |  3  | 1       | 1          | 1       | 1       | ---------------- |*/
         /* --------------------------------------------------------------------------------- */
         /* puc_ie[1] IE len ������EID��LEN�ֶ�,��ȡQoSInfo��uc_ie_len�������7�ֽڳ��� */
         /* Check if Bit 7 is set indicating U-APSD capability */
         if ((puc_ie[1] >= 7)&&(puc_ie[8] & BIT7))  /* wmm ie�ĵ�8���ֽ���QoS info�ֽ� */
         {
            pst_bss_dscr->uc_uapsd_cap = OAL_TRUE;
         }
    }
    else
    {
        puc_ie = mac_find_ie(MAC_EID_HT_CAP, puc_frame_body, us_frame_len);
        if (OAL_PTR_NULL != puc_ie)
        {
            pst_bss_dscr->uc_wmm_cap = OAL_TRUE;
        }
    }
}

#ifdef _PRE_WLAN_FEATURE_11D
/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_list_country
 ��������  : ����country IE
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_scan_update_bss_list_country(mac_bss_dscr_stru   *pst_bss_dscr,
                                                                oal_uint8           *puc_frame_body,
                                                                oal_uint16           us_frame_len)
{
    oal_uint8 *puc_ie;
    oal_uint8  uc_offset;

    uc_offset = MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
    //puc_ie = mac_get_country_ie(puc_frame_body, us_frame_len);
    puc_ie = mac_find_ie(MAC_EID_COUNTRY, puc_frame_body + uc_offset, us_frame_len - uc_offset);

    /* �����벻����, ȫ�����Ϊ0 */
    if (OAL_PTR_NULL == puc_ie)
    {
        pst_bss_dscr->ac_country[0] = 0;
        pst_bss_dscr->ac_country[1] = 0;
        pst_bss_dscr->ac_country[2] = 0;

        return;
    }

    /* ���������2���ֽ�,IE LEN������ڵ���2 */
    if(puc_ie[1] >= 2)
    {
        pst_bss_dscr->ac_country[0] = (oal_int8)puc_ie[MAC_IE_HDR_LEN];
        pst_bss_dscr->ac_country[1] = (oal_int8)puc_ie[MAC_IE_HDR_LEN + 1];
        pst_bss_dscr->ac_country[2] = 0;
    }
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_list_11n
 ��������  : ����11n�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_scan_update_bss_list_11n(mac_bss_dscr_stru   *pst_bss_dscr,
                                                            oal_uint8           *puc_frame_body,
                                                            oal_uint16           us_frame_len,
                                                            oal_uint16           us_offset)
{
    oal_uint8               *puc_ie;
    mac_ht_opern_stru       *pst_ht_op;
    oal_uint8                uc_sec_chan_offset;
    wlan_bw_cap_enum_uint8   en_ht_cap_bw = WLAN_BW_CAP_20M;
    wlan_bw_cap_enum_uint8   en_ht_op_bw  = WLAN_BW_CAP_20M;

    /* 11n */
    puc_ie = mac_find_ie(MAC_EID_HT_CAP, puc_frame_body + us_offset, us_frame_len - us_offset);
    if ((OAL_PTR_NULL != puc_ie) && (puc_ie[1] >= 2))
    {
        /* puc_ie[2]��HT Capabilities Info�ĵ�1���ֽ� */
        pst_bss_dscr->en_ht_capable = OAL_TRUE;     /* ֧��ht */
        pst_bss_dscr->en_ht_ldpc = (puc_ie[2] & BIT0);           /* ֧��ldpc */
        en_ht_cap_bw = ((puc_ie[2] & BIT1) >> 1);                /* ȡ��֧�ֵĴ��� */
        pst_bss_dscr->en_ht_stbc = ((puc_ie[2] & BIT7) >> 7);
    }

    /* Ĭ��20M,���֡����δЯ��HT_OPERATION�����ֱ�Ӳ���Ĭ��ֵ */
    pst_bss_dscr->en_channel_bandwidth = WLAN_BAND_WIDTH_20M;

    puc_ie = mac_find_ie(MAC_EID_HT_OPERATION, puc_frame_body + us_offset, us_frame_len - us_offset);
    if ((OAL_PTR_NULL != puc_ie) && (puc_ie[1] >= 2))   //����ie�����쳣���
    {
        pst_ht_op  = (mac_ht_opern_stru *)(puc_ie + MAC_IE_HDR_LEN);

        /* ��ȡ���ŵ�ƫ�� */
        uc_sec_chan_offset = pst_ht_op->bit_secondary_chan_offset;

        /* ��ֹap��channel width=0, ��channel offset = 1����3 ��ʱ��channel widthΪ�� */
        /* ht cap 20/40 enabled && ht operation 40 enabled */
        if ((0 != pst_ht_op->bit_sta_chan_width) && (en_ht_cap_bw > WLAN_BW_CAP_20M)) //cap > 20M��ȡchannel bw
        {
            if (MAC_SCB == uc_sec_chan_offset)
            {
                pst_bss_dscr->en_channel_bandwidth =  WLAN_BAND_WIDTH_40MINUS;
                en_ht_op_bw = WLAN_BW_CAP_40M;
            }
            else if (MAC_SCA == uc_sec_chan_offset)
            {
                pst_bss_dscr->en_channel_bandwidth =  WLAN_BAND_WIDTH_40PLUS;
                en_ht_op_bw = WLAN_BW_CAP_40M;
            }
        }
    }

    /* ��AP��������ȡ������������Сֵ����ֹAP�쳣���ͳ��������������ݣ�������ݲ�ͨ */
    pst_bss_dscr->en_bw_cap = OAL_MIN(en_ht_cap_bw, en_ht_op_bw);

    puc_ie = mac_find_ie(MAC_EID_EXT_CAPS, puc_frame_body + us_offset, us_frame_len - us_offset);
    if ((OAL_PTR_NULL != puc_ie) && (puc_ie[1] >= 1))
    {
        /* Extract 20/40 BSS Coexistence Management Support */
        pst_bss_dscr->uc_coex_mgmt_supp = (puc_ie[2] & BIT0);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_list_11ac
 ��������  : ����11ac���bss��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��9��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_scan_update_bss_list_11ac(mac_bss_dscr_stru   *pst_bss_dscr,
                                                             oal_uint8           *puc_frame_body,
                                                             oal_uint16           us_frame_len,
                                                             oal_uint16           us_offset)
{
    oal_uint8   *puc_ie;
    oal_uint8    uc_vht_chan_width;
    oal_uint8    uc_chan_center_freq;
    oal_uint8    uc_supp_ch_width;

    //puc_ie = mac_get_vht_cap_ie(puc_frame_body, us_frame_len, us_offset);
    puc_ie = mac_find_ie(MAC_EID_VHT_CAP, puc_frame_body + us_offset, us_frame_len - us_offset);
    if ((OAL_PTR_NULL != puc_ie) && (puc_ie[1] >= MAC_VHT_CAP_IE_LEN))
    {
        pst_bss_dscr->en_vht_capable = OAL_TRUE;     /* ֧��vht */

        /* ��ȡSupported Channel Width Set */
        uc_supp_ch_width = ((puc_ie[2] & (BIT3|BIT2)) >> 2);

        if (0 == uc_supp_ch_width)
        {
            pst_bss_dscr->en_bw_cap = WLAN_BW_CAP_80M;   /* 80MHz */
        }
        else if (1 == uc_supp_ch_width)
        {
            pst_bss_dscr->en_bw_cap = WLAN_BW_CAP_160M;  /* 160MHz */
        }
    }

    //puc_ie = mac_get_vht_opern_ie(puc_frame_body, us_frame_len, us_offset);
    puc_ie = mac_find_ie(MAC_EID_VHT_OPERN, puc_frame_body + us_offset, us_frame_len - us_offset);
    if ((OAL_PTR_NULL != puc_ie) && (puc_ie[1] >= MAC_VHT_OPERN_LEN))
    {
        uc_vht_chan_width   = puc_ie[2];
        uc_chan_center_freq = puc_ie[3];

        /* ���´�����Ϣ */
        if (0 == uc_vht_chan_width)          /* 40MHz */
        {
            /* do nothing��en_channel_bandwidth�Ѿ���HT Operation IE�л�ȡ */
        }
        else if (1 == uc_vht_chan_width)     /* 80MHz */
        {
            switch (uc_chan_center_freq - pst_bss_dscr->st_channel.uc_chan_number)
            {
                case 6:
                /***********************************************************************
                | ��20 | ��20 | ��40       |
                              |
                              |����Ƶ���������20ƫ6���ŵ�
                ************************************************************************/
                    pst_bss_dscr->en_channel_bandwidth = WLAN_BAND_WIDTH_80PLUSPLUS;
                    break;

                case -2:
                /***********************************************************************
                | ��40        | ��20 | ��20 |
                              |
                              |����Ƶ���������20ƫ-2���ŵ�
                ************************************************************************/
                    pst_bss_dscr->en_channel_bandwidth = WLAN_BAND_WIDTH_80PLUSMINUS;
                    break;

                case 2:
                /***********************************************************************
                | ��20 | ��20 | ��40       |
                              |
                              |����Ƶ���������20ƫ2���ŵ�
                ************************************************************************/
                    pst_bss_dscr->en_channel_bandwidth = WLAN_BAND_WIDTH_80MINUSPLUS;
                    break;

                case -6:
                /***********************************************************************
                | ��40        | ��20 | ��20 |
                              |
                              |����Ƶ���������20ƫ-6���ŵ�
                ************************************************************************/
                    pst_bss_dscr->en_channel_bandwidth = WLAN_BAND_WIDTH_80MINUSMINUS;
                    break;

                default:
                    break;

            }
        }
        else
        {
            /* Unsupported Channel BandWidth */
        }
    }
}

/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_list_protocol
 ��������  : ����Э���� bss��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��25��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��21��
    ��    ��   : duankaiyong 00194999
    �޸�����   : ����11i ������Ϣ

*****************************************************************************/
OAL_INLINE OAL_STATIC oal_void  hmac_scan_update_bss_list_protocol(mac_bss_dscr_stru *pst_bss_dscr,
                                                                            oal_uint8         *puc_frame_body,
                                                                            oal_uint16         us_frame_len)
{
    oal_uint16  us_offset = MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;

    /*************************************************************************/
    /*                       Beacon Frame - Frame Body                       */
    /* ----------------------------------------------------------------------*/
    /* |Timestamp|BcnInt|CapInfo|SSID|SupRates|DSParamSet|TIM  |CountryElem |*/
    /* ----------------------------------------------------------------------*/
    /* |8        |2     |2      |2-34|3-10    |3         |6-256|8-256       |*/
    /* ----------------------------------------------------------------------*/
    /* |PowerConstraint |Quiet|TPC Report|ERP |RSN  |WMM |Extended Sup Rates|*/
    /* ----------------------------------------------------------------------*/
    /* |3               |8    |4         |3   |4-255|26  | 3-257            |*/
    /* ----------------------------------------------------------------------*/
    /* |BSS Load |HT Capabilities |HT Operation |Overlapping BSS Scan       |*/
    /* ----------------------------------------------------------------------*/
    /* |7        |28              |24           |16                         |*/
    /* ----------------------------------------------------------------------*/
    /* |Extended Capabilities |                                              */
    /* ----------------------------------------------------------------------*/
    /* |3-8                   |                                              */
    /*************************************************************************/

    /* wmm */
    hmac_scan_update_bss_list_wmm(pst_bss_dscr, puc_frame_body, us_frame_len);

#if defined(_PRE_WLAN_FEATURE_WPA) || defined(_PRE_WLAN_FEATURE_WPA2)
    /* 11i */
    hmac_scan_update_bss_list_security(pst_bss_dscr, puc_frame_body, us_frame_len, us_offset);
#endif

#ifdef _PRE_WLAN_FEATURE_11D
    /* 11d */
    hmac_scan_update_bss_list_country(pst_bss_dscr, puc_frame_body, us_frame_len);
#endif

    /* 11n */
    hmac_scan_update_bss_list_11n(pst_bss_dscr, puc_frame_body, us_frame_len, us_offset);

    /* 11ac */
    hmac_scan_update_bss_list_11ac(pst_bss_dscr,  puc_frame_body, us_frame_len, us_offset);

}

#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 �� �� ��  : hmac_check_bss_supp_rates
 ��������  : �������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��04��12��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8  hmac_scan_check_bss_supp_rates(mac_device_stru *pst_mac_dev,
                                                     oal_uint8 *puc_rate,
                                                     oal_uint8  uc_bss_rate_num,
                                                     oal_uint8 *puc_update_rate)
{
    mac_data_rate_stru            *pst_rates;
    oal_uint32                     i,j;
    oal_uint8                      uc_rate_num = 0;

    pst_rates   = mac_device_get_all_rates(pst_mac_dev);
    if(OAL_PTR_NULL != puc_rate)
    {
        for(i = 0; i < uc_bss_rate_num; i++)
        {
            for(j = 0; j < MAC_DATARATES_PHY_80211G_NUM; j++)
            {
                if (((pst_rates[j].uc_mac_rate & 0x7f) == (puc_rate[i] & 0x7f))
                    && (uc_rate_num < MAC_DATARATES_PHY_80211G_NUM))
                {
                    puc_update_rate[uc_rate_num] = puc_rate[i];
                    uc_rate_num++;
                    break;
                }
            }
        }
    }

    return uc_rate_num;
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_list_rates
 ��������  : ����ɨ�赽bss�����ʼ�
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
OAL_INLINE OAL_STATIC oal_uint32  hmac_scan_update_bss_list_rates(mac_bss_dscr_stru *pst_bss_dscr,
                                                                          oal_uint8         *puc_frame_body,
                                                                          oal_uint16         us_frame_len,
                                                                          mac_device_stru   *pst_mac_dev)
{
    oal_uint8   *puc_ie;
    oal_uint8    uc_num_rates    = 0;
    oal_uint8    uc_num_ex_rates = 0;
    oal_uint8    us_offset;
#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1151)
    oal_uint8    auc_rates[MAC_DATARATES_PHY_80211G_NUM];
#endif

    /* ����Beacon֡��fieldƫ���� */
    us_offset = MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;

    //puc_ie = mac_get_supported_rates_ie(puc_frame_body, us_frame_len,us_offset);
    puc_ie = mac_find_ie(MAC_EID_RATES, puc_frame_body + us_offset, us_frame_len - us_offset);
    if (OAL_PTR_NULL != puc_ie)
    {
#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1151)
        uc_num_rates = hmac_scan_check_bss_supp_rates(pst_mac_dev, puc_ie + MAC_IE_HDR_LEN, puc_ie[1], auc_rates);
#else
        uc_num_rates = puc_ie[1];
#endif
        /* DTS2015032407334 �ѶFIR304����AP 11gģʽ�����͵�֧�����ʼ�����Ϊ12��������Э��涨��Ϊ���Ӽ����ԣ��޸��жϷ�֧Ϊ12 */
        if (uc_num_rates > WLAN_MAX_SUPP_RATES)
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_scan_update_bss_list_rates::uc_num_rates=%d.}", uc_num_rates);
            uc_num_rates = WLAN_MAX_SUPP_RATES;
        }

#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1151)
        oal_memcopy(pst_bss_dscr->auc_supp_rates, auc_rates, uc_num_rates);
#else
        oal_memcopy(pst_bss_dscr->auc_supp_rates, puc_ie + MAC_IE_HDR_LEN, uc_num_rates);
#endif
        pst_bss_dscr->uc_num_supp_rates = uc_num_rates;
    }

    //puc_ie = mac_get_exsup_rates_ie(puc_frame_body, us_frame_len, us_offset);
    puc_ie = mac_find_ie(MAC_EID_XRATES, puc_frame_body + us_offset, us_frame_len - us_offset);
    if (OAL_PTR_NULL != puc_ie)
    {
#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1151)
        uc_num_ex_rates = hmac_scan_check_bss_supp_rates(pst_mac_dev, puc_ie + MAC_IE_HDR_LEN, puc_ie[1], auc_rates);
#else
        uc_num_ex_rates = puc_ie[1];
#endif

        if (uc_num_rates + uc_num_ex_rates > WLAN_MAX_SUPP_RATES) /* ����֧�����ʸ��� */
        {
            OAM_WARNING_LOG2(0, OAM_SF_SCAN,
                            "{hmac_scan_update_bss_list_rates::number of rates too large, uc_num_rates=%d, uc_num_ex_rates=%d.}",
                            uc_num_rates, uc_num_ex_rates);

            uc_num_ex_rates = WLAN_MAX_SUPP_RATES - uc_num_rates;
        }

        if (uc_num_ex_rates > 0)
        {
#if (_PRE_PRODUCT_ID != _PRE_PRODUCT_ID_HI1151)
            oal_memcopy(&(pst_bss_dscr->auc_supp_rates[uc_num_rates]), auc_rates, uc_num_ex_rates);
#else
            oal_memcopy(&(pst_bss_dscr->auc_supp_rates[uc_num_rates]), puc_ie + MAC_IE_HDR_LEN, (oal_uint32)uc_num_ex_rates);
#endif
        }
        pst_bss_dscr->uc_num_supp_rates += uc_num_ex_rates;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_scan_update_bss_dscr
 ��������  : ��������ɨ��ṹ��bss dscr�ṹ��
 �������  : hmac_scanned_bss_info   *pst_scanned_bss,
             dmac_tx_event_stru      *pst_dtx_event,
             oal_uint8                uc_device_id,
             oal_uint8                uc_vap_id
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��2��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_scan_update_bss_dscr(hmac_scanned_bss_info   *pst_scanned_bss,
                                                          dmac_tx_event_stru      *pst_dtx_event,
                                                          oal_uint8                uc_device_id,
                                                          oal_uint8                uc_vap_id)
{
    oal_netbuf_stru                      *pst_netbuf    = pst_dtx_event->pst_netbuf;
    mac_scanned_result_extend_info_stru  *pst_scan_result_extend_info;
    mac_device_stru                      *pst_mac_device;
    hmac_vap_stru                        *pst_hmac_vap;
    mac_ieee80211_frame_stru             *pst_frame_header;
    oal_uint8                            *puc_frame_body;
    mac_bss_dscr_stru                    *pst_bss_dscr;
    oal_uint8                            *puc_ssid;                 /* ָ��beacon֡�е�ssid */
    oal_uint8                            *puc_mgmt_frame;
    dmac_rx_ctl_stru                     *pst_rx_ctrl;
    oal_uint16                            us_netbuf_len = pst_dtx_event->us_frame_len;
    oal_uint16                            us_frame_len;
    oal_uint16                            us_frame_body_len;
    oal_uint16                            us_offset =  MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN + MAC_CAP_INFO_LEN;
    oal_uint8                             uc_ssid_len;
    oal_uint8                             uc_frame_channel;
#ifdef _PRE_WLAN_FEATURE_TXBF
    mac_11ntxbf_vendor_ie_stru           *pst_txbf_vendor_ie;
#endif

    /* ��ȡhmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_update_bss_dscr::pst_hmac_vap is null.}");
        return OAL_FAIL;
    }

    /* ��ȡmac device */
    pst_mac_device  = mac_res_get_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_update_bss_dscr::pst_mac_device is null.}");
        return OAL_FAIL;
    }

    /* ��ȡdevice�ϱ���ɨ������Ϣ����������µ�bss�����ṹ���� */
    us_frame_len   = us_netbuf_len - OAL_SIZEOF(mac_scanned_result_extend_info_stru);
    puc_mgmt_frame = (oal_uint8 *)OAL_NETBUF_DATA(pst_netbuf);
    pst_rx_ctrl    = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

    /* ָ��netbuf�е��ϱ���ɨ��������չ��Ϣ��λ�� */
    pst_scan_result_extend_info = (mac_scanned_result_extend_info_stru *)(puc_mgmt_frame + us_frame_len);

#if 0
    /* ����ά����Ϣ����ǰ�ŵ��š��ź�ǿ�ȡ��ϱ���netbuf���� */
    OAM_ERROR_LOG4(0, OAM_SF_SCAN,
                   "{hmac_scan_update_bss_dscr::rssi[%d], cb_rssi[%d], channel[%d], buf_len[%d].}",
                   pst_scan_result_extend_info->l_rssi,
                   (oal_int32)pst_rx_ctrl->st_rx_statistic.c_rssi_dbm,
                   (oal_int32)pst_rx_ctrl->st_rx_info.uc_channel_number,
                   (oal_int32)us_netbuf_len);
#endif

    /* ��ȡ����֡��֡ͷ��֡��ָ�� */
    pst_frame_header  = (mac_ieee80211_frame_stru *)puc_mgmt_frame;
    puc_frame_body    = (oal_uint8 *)(puc_mgmt_frame + MAC_80211_FRAME_LEN);
    us_frame_body_len = us_frame_len - MAC_80211_FRAME_LEN;

    /* ��ȡ����֡�е��ŵ� */
    uc_frame_channel = mac_ie_get_chan_num(puc_frame_body, us_frame_body_len, us_offset, pst_rx_ctrl->st_rx_info.uc_channel_number);

    /* ����bss��Ϣ */
    pst_bss_dscr = &(pst_scanned_bss->st_bss_dscr_info);

    /*****************************************************************************
        ����beacon/probe rsp֡����¼��pst_bss_dscr
    *****************************************************************************/
    /* ����������ssid */
    puc_ssid = mac_get_ssid(puc_frame_body, (oal_int32)us_frame_body_len, &uc_ssid_len);
    if ((OAL_PTR_NULL != puc_ssid) && (0 != uc_ssid_len))
    {
        /* �����ҵ���ssid���浽bss�����ṹ���� */
        oal_memcopy(pst_bss_dscr->ac_ssid, puc_ssid, uc_ssid_len);
        pst_bss_dscr->ac_ssid[uc_ssid_len] = '\0';
    }

    /* ����bssid */
    oal_set_mac_addr(pst_bss_dscr->auc_mac_addr, pst_frame_header->auc_address2);
    oal_set_mac_addr(pst_bss_dscr->auc_bssid, pst_frame_header->auc_address3);

    /* bss������Ϣ */
    pst_bss_dscr->en_bss_type = pst_scan_result_extend_info->en_bss_type;

    pst_bss_dscr->us_cap_info = *((oal_uint16 *)(puc_frame_body + MAC_TIME_STAMP_LEN + MAC_BEACON_INTERVAL_LEN));

    pst_bss_dscr->c_rssi      =  (oal_int8)pst_scan_result_extend_info->l_rssi;

    /* ����beacon������tim���� */
    pst_bss_dscr->us_beacon_period = mac_get_beacon_period(puc_frame_body);
    pst_bss_dscr->uc_dtim_period   = mac_get_dtim_period(puc_frame_body, us_frame_body_len);
    pst_bss_dscr->uc_dtim_cnt      = mac_get_dtim_cnt(puc_frame_body, us_frame_body_len);

    /* �ŵ� */
    pst_bss_dscr->st_channel.uc_chan_number = uc_frame_channel;
    pst_bss_dscr->st_channel.en_band        = mac_get_band_by_channel_num(uc_frame_channel);

    /* ��¼���ʼ� */
    hmac_scan_update_bss_list_rates(pst_bss_dscr, puc_frame_body, us_frame_body_len, pst_mac_device);

    /* Э���������ϢԪ�صĻ�ȡ */
    hmac_scan_update_bss_list_protocol(pst_bss_dscr, puc_frame_body, us_frame_body_len);
#ifdef _PRE_WLAN_FEATURE_TXBF
    pst_txbf_vendor_ie = (mac_11ntxbf_vendor_ie_stru *)mac_find_vendor_ie(MAC_HUAWEI_VENDER_IE, MAC_EID_11NTXBF, puc_frame_body + us_offset, (oal_int32)(us_frame_body_len - us_offset));
    if (OAL_PTR_NULL != pst_txbf_vendor_ie)
    {
        pst_bss_dscr->en_11ntxbf = (pst_txbf_vendor_ie->st_11ntxbf.bit_11ntxbf == 1) ? OAL_TRUE : OAL_FALSE;

    }
#endif

    /* ����ʱ��� */
    pst_bss_dscr->ul_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    pst_bss_dscr->ul_mgmt_len = us_frame_len;

    /* ��������֡���� */
    oal_memcopy((oal_uint8 *)pst_scanned_bss->st_bss_dscr_info.auc_mgmt_buff, puc_mgmt_frame, (oal_uint32)us_frame_len);

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_scan_need_update_old_scan_result
 ��������  : �Ƿ���Ҫ���¸���֮ǰɨ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��6��2��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_scan_need_update_old_scan_result(oal_uint8 uc_vap_id, hmac_scanned_bss_info *pst_new_bss, hmac_scanned_bss_info *pst_old_bss)
{
    if (('\0' == pst_new_bss->st_bss_dscr_info.ac_ssid[0]) &&
           ('\0' != pst_old_bss->st_bss_dscr_info.ac_ssid[0]))
    {
        /* ����SSID������������AP��Ϣ,��ssid��Ϊ�գ��˴�ͨ��BEACON֡ɨ�赽��AP��Ϣ,��SSIDΪ�գ��򲻽��и��� */
        OAM_WARNING_LOG3(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_need_update_old_scan_result::find hide ssid:%.2x:%.2x:%.2x,ignore this update.}",
                                pst_new_bss->st_bss_dscr_info.auc_bssid[3],
                                pst_new_bss->st_bss_dscr_info.auc_bssid[4],
                                pst_new_bss->st_bss_dscr_info.auc_bssid[5]);
        return OAL_FALSE;
    }


    /* DTS2016052803088 ���߼������һ��ɨ������г���beacon��probe rspʱ�Ĵ���
       ���֮ǰɨ����Ϊprobe rsp���˴�Ϊbeacon���򲻸��ǣ����򸲸� --start */
    if ((WLAN_PROBE_RSP == ((mac_ieee80211_frame_stru *)pst_old_bss->st_bss_dscr_info.auc_mgmt_buff)->st_frame_control.bit_sub_type)
        && (WLAN_BEACON == ((mac_ieee80211_frame_stru *)pst_new_bss->st_bss_dscr_info.auc_mgmt_buff)->st_frame_control.bit_sub_type)
        && (OAL_TRUE == pst_old_bss->st_bss_dscr_info.en_new_scan_bss))
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;

}
/*****************************************************************************
 �� �� ��  : hmac_scan_proc_scanned_bss
 ��������  : ����ÿ���ŵ���ɨ������host����д���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_scan_proc_scanned_bss(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru             *pst_event;
    frw_event_hdr_stru         *pst_event_hdr;
    hmac_vap_stru              *pst_hmac_vap;
    oal_netbuf_stru            *pst_bss_mgmt_netbuf;
    hmac_device_stru           *pst_hmac_device;
    dmac_tx_event_stru         *pst_dtx_event;
    hmac_scanned_bss_info      *pst_new_scanned_bss;
    hmac_scanned_bss_info      *pst_old_scanned_bss;
    oal_uint32                  ul_ret;
    oal_uint16                  us_mgmt_len;
    oal_uint8                   uc_vap_id;
    hmac_bss_mgmt_stru         *pst_bss_mgmt;
    oal_uint32                  ul_curr_time_stamp;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_proc_scanned_bss::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼�ͷ���¼��ṹ��ָ�� */
    pst_event           = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr       = &(pst_event->st_event_hdr);
    pst_dtx_event       = (dmac_tx_event_stru *)pst_event->auc_event_data;
    pst_bss_mgmt_netbuf = pst_dtx_event->pst_netbuf;

    pst_hmac_vap = mac_res_get_hmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_proc_scanned_bss::pst_hmac_vap null.}");

        /* �ͷ��ϱ���bss��Ϣ��beacon����probe rsp֡���ڴ� */
        oal_netbuf_free(pst_bss_mgmt_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡvap id */
    uc_vap_id = pst_hmac_vap->st_vap_base_info.uc_vap_id;

    /* ��ȡhmac device �ṹ */
    pst_hmac_device = hmac_res_get_mac_dev(pst_event_hdr->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scanned_bss::pst_hmac_device null.}");

        /* �ͷ��ϱ���bss��Ϣ��beacon����probe rsp֡���ڴ� */
        oal_netbuf_free(pst_bss_mgmt_netbuf);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��dmac�ϱ���netbuf���ݽ��н���������������ʾ */
    /***********************************************************************************************/
    /*            netbuf data����ϱ���ɨ�������ֶεķֲ�                                        */
    /* ------------------------------------------------------------------------------------------  */
    /* beacon/probe rsp body  |     ֡����渽���ֶ�(mac_scanned_result_extend_info_stru)          */
    /* -----------------------------------------------------------------------------------------   */
    /* �յ���beacon/rsp��body | rssi(4�ֽ�) | channel num(1�ֽ�)| band(1�ֽ�)|bss_tye(1�ֽ�)|���  */
    /* ------------------------------------------------------------------------------------------  */
    /*                                                                                             */
    /***********************************************************************************************/

    /* ����֡�ĳ��ȵ����ϱ���netbuf�ĳ��ȼ�ȥ�ϱ���ɨ��������չ�ֶεĳ��� */
    us_mgmt_len = pst_dtx_event->us_frame_len - OAL_SIZEOF(mac_scanned_result_extend_info_stru);

    /* ����洢ɨ�������ڴ� */
    pst_new_scanned_bss = hmac_scan_alloc_scanned_bss(us_mgmt_len);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_new_scanned_bss))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scanned_bss::alloc memory failed for storing scanned result.}");

        /* �ͷ��ϱ���bss��Ϣ��beacon����probe rsp֡���ڴ� */
        oal_netbuf_free(pst_bss_mgmt_netbuf);
        return OAL_PTR_NULL;
    }

    /* ��������ɨ������bss dscr�ṹ�� */
    ul_ret = hmac_scan_update_bss_dscr(pst_new_scanned_bss, pst_dtx_event, pst_event_hdr->uc_device_id, pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scanned_bss::hmac_scan_update_bss_dscr failed[%d].}", ul_ret);

        /* �ͷ��ϱ���bss��Ϣ��beacon����probe rsp֡���ڴ� */
        oal_netbuf_free(pst_bss_mgmt_netbuf);

        /* �ͷ�����Ĵ洢bss��Ϣ���ڴ� */
        oal_free(pst_new_scanned_bss);
        return ul_ret;
    }

    /* ��ȡ����ɨ���bss����Ľṹ�� */
    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);
    /* ������ɾ����ǰ���� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));
    /* �ж���ͬbssid��bss�Ƿ��Ѿ�ɨ�赽 */
    pst_old_scanned_bss = hmac_scan_find_scanned_bss_by_bssid(pst_bss_mgmt, pst_new_scanned_bss->st_bss_dscr_info.auc_bssid);
    if (OAL_PTR_NULL == pst_old_scanned_bss)
    {
        /* ���� */
        oal_spin_unlock(&(pst_bss_mgmt->st_lock));

        /*lint -e801*/
        goto add_bss;
        /*lint +e801*/
    }

    /* ����ϵ�ɨ���bss���ź�ǿ�ȴ��ڵ�ǰɨ�赽��bss���ź�ǿ�ȣ����µ�ǰɨ�赽���ź�ǿ��Ϊ��ǿ���ź�ǿ�� */
    if (pst_old_scanned_bss->st_bss_dscr_info.c_rssi > pst_new_scanned_bss->st_bss_dscr_info.c_rssi)
    {
        /* 1s�����ھͲ���֮ǰ��BSS�����RSSI��Ϣ������Ͳ����µ�RSSI��Ϣ */
        ul_curr_time_stamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
        if ((ul_curr_time_stamp - pst_old_scanned_bss->st_bss_dscr_info.ul_timestamp) < HMAC_SCAN_MAX_SCANNED_RSSI_EXPIRE)
        {
            OAM_INFO_LOG0(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scanned_bss::update signal strength value.}");
            pst_new_scanned_bss->st_bss_dscr_info.c_rssi = pst_old_scanned_bss->st_bss_dscr_info.c_rssi;
        }
    }

    if (OAL_FALSE == hmac_scan_need_update_old_scan_result(uc_vap_id, pst_new_scanned_bss, pst_old_scanned_bss))
    {
        pst_old_scanned_bss->st_bss_dscr_info.ul_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();
        pst_old_scanned_bss->st_bss_dscr_info.c_rssi = pst_new_scanned_bss->st_bss_dscr_info.c_rssi;

        /* ���� */
        oal_spin_unlock(&(pst_bss_mgmt->st_lock));

        /* �ͷ�����Ĵ洢bss��Ϣ���ڴ� */
        oal_free(pst_new_scanned_bss);

        /* �ͷ��ϱ���bss��Ϣ��beacon����probe rsp֡���ڴ� */
        oal_netbuf_free(pst_bss_mgmt_netbuf);

        return OAL_SUCC;
    }

    /* �������н�ԭ��ɨ�赽����ͬbssid��bss�ڵ�ɾ�� */
    hmac_scan_del_bss_from_list_nolock(pst_old_scanned_bss, pst_hmac_device);
    /* ���� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));
    /* �ͷ��ڴ� */
    oal_free(pst_old_scanned_bss);


add_bss:
    /* ��ɨ������ӵ������� */
    hmac_scan_add_bss_to_list(pst_new_scanned_bss, pst_hmac_device);

    /* �ͷ��ϱ���bss��Ϣ��beacon����probe rsp֡���ڴ� */
    oal_netbuf_free(pst_bss_mgmt_netbuf);


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_print_channel_statistics_info
 ��������  : ��ӡ�ŵ�ͳ����Ϣ
 �������  : hmac_scan_record_stru   *pst_scan_record��ɨ���¼
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��18��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_scan_print_channel_statistics_info(hmac_scan_record_stru   *pst_scan_record)
{
    mac_scan_chan_stats_stru    *pst_chan_stats = pst_scan_record->ast_chan_results;
    oal_uint8                    uc_vap_id = pst_scan_record->uc_vap_id;
    oal_uint8                    uc_idx = 0;

    /* ��Ȿ��ɨ���Ƿ������ŵ����������û��ֱ�ӷ��� */
    if (0 == pst_chan_stats[0].uc_stats_valid)
    {
        OAM_INFO_LOG0(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info:: curr scan don't enable channel measure.\n}");
        return;
    }

    /* ��ӡ�ŵ�������� */
    OAM_INFO_LOG0(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info:: The chan measure result: \n}");

    for (uc_idx = 0; uc_idx < pst_scan_record->uc_chan_numbers; uc_idx++)
    {
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Chan num      : %d\n}", pst_chan_stats[uc_idx].uc_channel_number);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Stats cnt     : %d\n}", pst_chan_stats[uc_idx].uc_stats_cnt);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Stats valid   : %d\n}", pst_chan_stats[uc_idx].uc_stats_valid);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Stats time us : %d\n}", pst_chan_stats[uc_idx].ul_total_stats_time_us);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Free time 20M : %d\n}", pst_chan_stats[uc_idx].ul_total_free_time_20M_us);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Free time 40M : %d\n}", pst_chan_stats[uc_idx].ul_total_free_time_40M_us);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Free time 80M : %d\n}", pst_chan_stats[uc_idx].ul_total_free_time_80M_us);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Send time     : %d\n}", pst_chan_stats[uc_idx].ul_total_send_time_us);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Recv time     : %d\n}", pst_chan_stats[uc_idx].ul_total_recv_time_us);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Free power cnt: %d\n}", pst_chan_stats[uc_idx].uc_free_power_cnt);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Free power 20M: %d\n}", (oal_int32)pst_chan_stats[uc_idx].s_free_power_stats_20M);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Free power 40M: %d\n}", (oal_int32)pst_chan_stats[uc_idx].s_free_power_stats_40M);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Free power 80M: %d\n}", (oal_int32)pst_chan_stats[uc_idx].s_free_power_stats_80M);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Radar detected: %d\n}", pst_chan_stats[uc_idx].uc_radar_detected);
        OAM_INFO_LOG1(uc_vap_id, OAM_SF_SCAN, "{hmac_scan_print_channel_statistics_info::Radar bw      : %d\n}", pst_chan_stats[uc_idx].uc_radar_bw);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_print_scan_record_info
 ��������  : ɨ����ɣ���ӡ���ά����Ϣ������ɨ��ִ��ʱ�䣬ɨ�践��״̬�룬ɨ�赽��bss��Ϣ��
 �������  : hmac_scan_record_stru   *pst_scan_record��ɨ���¼
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��18��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_scan_print_scan_record_info(hmac_vap_stru *pst_hmac_vap, hmac_scan_record_stru *pst_scan_record)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && (defined(_PRE_PRODUCT_ID_HI110X_HOST))
    oal_time_t_stru   st_timestamp_diff;

    /* ��ȡɨ����ʱ��� */
    st_timestamp_diff  = oal_ktime_sub(oal_ktime_get(), pst_scan_record->st_scan_start_time);

    /* �����ں˽ӿڣ���ӡ�˴�ɨ���ʱ */
    OAM_WARNING_LOG4(pst_scan_record->uc_vap_id, OAM_SF_SCAN,
                     "{hmac_scan_print_scan_record_info::scan comp, scan_status[%d],vap ch_num:%d, cookie[%x], duration time is: [%lu]ms.}",
                     pst_scan_record->en_scan_rsp_status,
                     pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number,
                     pst_scan_record->ull_cookie,
                     ktime_to_ms(st_timestamp_diff));
#endif

    /* ��ӡɨ�赽��bss��Ϣ */
    hmac_scan_print_scanned_bss_info(pst_scan_record->uc_device_id);

    /* �ŵ�������� */
    hmac_scan_print_channel_statistics_info(pst_scan_record);

    return;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_proc_scan_comp_event
 ��������  : DMACɨ������¼�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��25��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_scan_proc_scan_comp_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    hmac_vap_stru                      *pst_hmac_vap;
    hmac_device_stru                   *pst_hmac_device;
    mac_scan_rsp_stru                  *pst_d2h_scan_rsp_info;
    hmac_scan_stru                     *pst_scan_mgmt;
#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8                           auc_param[] = {"all"};
#endif
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_proc_scan_comp_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼�ͷ���¼��ṹ��ָ�� */
    pst_event     = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr = &(pst_event->st_event_hdr);

    /* ��ȡhmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_event_hdr->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_proc_scan_comp_event::pst_hmac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_d2h_scan_rsp_info = (mac_scan_rsp_stru *)(pst_event->auc_event_data);
    pst_scan_mgmt = &(pst_hmac_device->st_scan_mgmt);

    /* DTS2015110908011 ��ֹcompete�¼������ڴ����ɨ�費һ�� */
    if ((pst_event_hdr->uc_vap_id != pst_scan_mgmt->st_scan_record_mgmt.uc_vap_id) ||
        (pst_d2h_scan_rsp_info->ull_cookie != pst_scan_mgmt->st_scan_record_mgmt.ull_cookie))
    {
        OAM_WARNING_LOG4(pst_event_hdr->uc_vap_id, OAM_SF_SCAN,
                "{hmac_scan_proc_scan_comp_event::Report vap(%d) Scan_complete(cookie %d), but there have anoter vap(%d) scaning(cookie %d) !}",
                pst_event_hdr->uc_vap_id,
                pst_d2h_scan_rsp_info->ull_cookie,
                pst_scan_mgmt->st_scan_record_mgmt.uc_vap_id,
                pst_scan_mgmt->st_scan_record_mgmt.ull_cookie);
        return OAL_SUCC;
    }

    OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scan_comp_event::scan status:%d !}",
                     pst_d2h_scan_rsp_info->en_scan_rsp_status);

    /* ɾ��ɨ�賬ʱ������ʱ�� */
    if ((OAL_TRUE == pst_scan_mgmt->st_scan_timeout.en_is_registerd)
        && (MAC_SCAN_PNO != pst_d2h_scan_rsp_info->en_scan_rsp_status))
    {
        /* PNOû������ɨ�趨ʱ��,���ǵ�ȡ��PNOɨ��,�����·���ͨɨ��,PNOɨ������¼���������ͨɨ���Ӱ�� */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_scan_mgmt->st_scan_timeout));
    }

    /* ��ȡhmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scan_comp_event::pst_hmac_vap null.}");

        /* ���õ�ǰ���ڷ�ɨ��״̬ */
        pst_scan_mgmt->en_is_scanning = OAL_FALSE;
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ݵ�ǰɨ������ͺ͵�ǰvap��״̬�������л�vap��״̬�������ǰ��ɨ�裬����Ҫ�л�vap��״̬ */
    if ((WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode)
        && (MAC_SCAN_PNO != pst_d2h_scan_rsp_info->en_scan_rsp_status))
    {
        if (MAC_VAP_STATE_STA_WAIT_SCAN == pst_hmac_vap->st_vap_base_info.en_vap_state)
        {
            /* �ı�vap״̬��SCAN_COMP */
            hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_SCAN_COMP);
        }
        else if (MAC_VAP_STATE_UP == pst_hmac_vap->st_vap_base_info.en_vap_state)
        {
            /* ����ɨ��ʱ��Ҫ����֡���˵����� */
            hmac_set_rx_filter_value(&(pst_hmac_vap->st_vap_base_info));
        }
    }

    /* BEGIN:DTS2015072801307 1102 ��Ϊap ��40M ������ִ��ɨ�裬ɨ����ɺ�VAP ״̬�޸�Ϊɨ��ǰ��״̬ */
    if ((WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
        && (MAC_VAP_STATE_BUTT != pst_scan_mgmt->st_scan_record_mgmt.en_vap_last_state))
    {
        hmac_fsm_change_state(pst_hmac_vap, pst_scan_mgmt->st_scan_record_mgmt.en_vap_last_state);
        pst_scan_mgmt->st_scan_record_mgmt.en_vap_last_state = MAC_VAP_STATE_BUTT;
    }
    /* BEGIN:DTS2015072801307 1102 ��Ϊap ��40M ������ִ��ɨ�裬ɨ����ɺ�VAP ״̬�޸�Ϊɨ��ǰ��״̬ */

    /* ����device�ϱ���ɨ�������ϱ�sme */
    /* ��ɨ��ִ�����(ɨ��ִ�гɹ�������ʧ�ܵȷ��ؽ��)��¼��ɨ�����м�¼�ṹ���� */
    pst_scan_mgmt->st_scan_record_mgmt.en_scan_rsp_status = pst_d2h_scan_rsp_info->en_scan_rsp_status;
    pst_scan_mgmt->st_scan_record_mgmt.ull_cookie         = pst_d2h_scan_rsp_info->ull_cookie;

    // ɨ�迪ʼʱ�Ѿ������
#if 0
    /* �ϱ�ɨ����ǰ������µ��ڵ�ɨ��bss����ֹ�ϱ����ൽ�ڵ�bss */
    hmac_scan_clean_expire_scanned_bss(pst_hmac_vap, &(pst_scan_mgmt->st_scan_record_mgmt));
#endif

#if 0
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    if (2 >= pst_scan_mgmt->st_scan_record_mgmt.st_bss_mgmt.ul_bss_num)
    {
        OAM_WARNING_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_SCAN, "{scan completed, but bss num is too few!}");
        /* �·����������ȡ���мĴ��� */
        hmac_config_reg_info(&(pst_hmac_vap->st_vap_base_info), OAL_SIZEOF(auc_param), auc_param);
    }
#endif
#endif
    hmac_scan_print_scan_record_info(pst_hmac_vap, &(pst_scan_mgmt->st_scan_record_mgmt));

#ifdef _PRE_WLAN_FEATURE_ROAM
    /* STA����ɨ��ʱ����Ҫ��ǰʶ�����γ��� */
    if ((WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode) &&
        (MAC_VAP_STATE_UP == pst_hmac_vap->st_vap_base_info.en_vap_state))
    {
        hmac_roam_check_bkscan_result(pst_hmac_vap, &(pst_scan_mgmt->st_scan_record_mgmt));
    }
#endif //_PRE_WLAN_FEATURE_ROAM

    /* ���ɨ��ص�������Ϊ�գ�����ûص����� */
    if ((OAL_PTR_NULL != pst_scan_mgmt->st_scan_record_mgmt.p_fn_cb)
          && (MAC_SCAN_ABORT != pst_d2h_scan_rsp_info->en_scan_rsp_status))
    {
        /* ��ֹɨ��������ûص�,��ֹ��ֹɨ������������PNOɨ���Ӱ�� */
        pst_scan_mgmt->st_scan_record_mgmt.p_fn_cb(&(pst_scan_mgmt->st_scan_record_mgmt));
    }

    /* ���õ�ǰ���ڷ�ɨ��״̬ */
    if(MAC_SCAN_PNO != pst_d2h_scan_rsp_info->en_scan_rsp_status)
    {
        /* PNOɨ��û���ô�λΪOAL_TRUE,PNOɨ�����,����Ӱ�����ĳ���ɨ�� */
        pst_scan_mgmt->en_is_scanning = OAL_FALSE;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_scan_proc_scan_req_event_exception
 ��������  : �쳣ɨ������,���¼���wal �㣬ִ��ɨ�����
 �������  : pst_mac_device: ָ��device�ṹ��
             p_params: ����ɨ������Ĳ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��26��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_scan_proc_scan_req_event_exception(hmac_vap_stru *pst_hmac_vap, oal_void *p_params)
{
    frw_event_mem_stru         *pst_event_mem;
    frw_event_stru             *pst_event;
    hmac_scan_rsp_stru          st_scan_rsp;
    hmac_scan_rsp_stru         *pst_scan_rsp;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == p_params)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_mgmt_scan_req_exception::param null, %d %d.}", pst_hmac_vap, p_params);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��֧�ַ���ɨ���״̬������ɨ�� */
    OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_mgmt_scan_req_exception::vap state is=%x.}",
                     pst_hmac_vap->st_vap_base_info.en_vap_state);

    OAL_MEMZERO(&st_scan_rsp, OAL_SIZEOF(hmac_scan_rsp_stru));

    /* ��ɨ������¼���WAL, ִ��SCAN_DONE , �ͷ�ɨ�������ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(hmac_scan_rsp_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_mgmt_scan_req_exception::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    st_scan_rsp.uc_result_code = MAC_SCAN_REFUSED;
    st_scan_rsp.uc_num_dscr    = 0;

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       HMAC_HOST_CTX_EVENT_SUB_TYPE_SCAN_COMP_STA,
                       OAL_SIZEOF(hmac_scan_rsp_stru),
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    pst_scan_rsp = (hmac_scan_rsp_stru *)pst_event->auc_event_data;

    oal_memcopy(pst_scan_rsp, (oal_void *)(&st_scan_rsp), OAL_SIZEOF(hmac_scan_rsp_stru));

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_scan_set_sour_mac_addr_in_probe_req
 ��������  : ����probe req֡��Я����Դmac addr��������mac addr���Կ�������Я�����mac addr
 �������  : hmac_vap_stru        *pst_hmac_vap,
             oal_uint8            *puc_sour_mac_addr,
             oal_bool_enum_uint8   en_is_rand_mac_addr_scan
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��18��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_scan_set_sour_mac_addr_in_probe_req(hmac_vap_stru        *pst_hmac_vap,
                                                   oal_uint8            *puc_sour_mac_addr,
                                                   oal_bool_enum_uint8   en_is_rand_mac_addr_scan,
                                                   oal_bool_enum_uint8   en_is_p2p0_scan)
{
    mac_device_stru          *pst_mac_device = OAL_PTR_NULL;

    if((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == puc_sour_mac_addr))
    {
        OAM_ERROR_LOG2(0, OAM_SF_CFG, "{hmac_scan_set_sour_mac_addr_in_probe_req::param null,pst_hmac_vap:%p,puc_sour_mac_addr:%p.}",
                       pst_hmac_vap, puc_sour_mac_addr);
        return;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{hmac_scan_set_sour_mac_addr_in_probe_req::pst_mac_device is null.}");
        return;
    }

#ifdef _PRE_WLAN_FEATURE_P2P
    /* WLAN/P2P ��������£�p2p0 ��p2p-p2p0 cl ɨ��ʱ����Ҫʹ�ò�ͬ�豸 */
    if (OAL_TRUE == en_is_p2p0_scan)
    {
        oal_set_mac_addr(puc_sour_mac_addr, pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID);
    }
    else
#endif /* _PRE_WLAN_FEATURE_P2P */
    {
        /* ������mac addrɨ�����Կ����ҷ�P2P�������������mac addr��probe req֡�� */
        if ((OAL_TRUE == en_is_rand_mac_addr_scan) && (IS_LEGACY_VAP(&(pst_hmac_vap->st_vap_base_info)))
            && ((pst_mac_device->auc_mac_oui[0] != 0) || (pst_mac_device->auc_mac_oui[1] != 0) || (pst_mac_device->auc_mac_oui[2] != 0)))
        {
            /* Android ����wpsɨ���hilink���ӵĳ�����,��mac oui��0 */
            oal_random_ether_addr(puc_sour_mac_addr);
            puc_sour_mac_addr[0] = pst_mac_device->auc_mac_oui[0] & 0xfe;  /*��֤�ǵ���mac*/
            puc_sour_mac_addr[1] = pst_mac_device->auc_mac_oui[1];
            puc_sour_mac_addr[2] = pst_mac_device->auc_mac_oui[2];

            OAM_WARNING_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_scan_set_sour_mac_addr_in_probe_req::rand_mac_addr[%02X:XX:XX:%02X:%02X:%02X].}",
                                 puc_sour_mac_addr[0], puc_sour_mac_addr[3], puc_sour_mac_addr[4], puc_sour_mac_addr[5]);
        }
        else
        {
            /* ���õ�ַΪ�Լ���MAC��ַ */
            oal_set_mac_addr(puc_sour_mac_addr, pst_hmac_vap->st_vap_base_info.pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_update_scan_params
 ��������  : ����device�����е�vap״̬�Լ�������Ϣ������ɨ�����:
             ��������ɨ���ߵ�vap id��ɨ��ģʽ��ÿ�ŵ�ɨ�������probe req֡Я����Դmac addr
 �������  : hmac_vap_stru *pst_hmac_vap,
             mac_scan_req_stru *pst_scan_params,
             oal_bool_enum_uint8   en_is_random_mac_addr_scan,      �Ƿ�Ϊ���mac addrɨ��ı��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��4��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_scan_update_scan_params(hmac_vap_stru        *pst_hmac_vap,
                                                    mac_scan_req_stru    *pst_scan_params,
                                                    oal_bool_enum_uint8   en_is_random_mac_addr_scan)
{
    mac_device_stru             *pst_mac_device;
    mac_vap_stru                *pst_mac_vap_temp;
    oal_uint32                   ul_ret;
    wlan_vap_mode_enum_uint8     en_vap_mode;

    /* ��ȡmac device */
    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_device_id, OAM_SF_SCAN,
                         "{hmac_scan_update_scan_params::pst_mac_device null.}");
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    /* 1.��¼����ɨ���vap id��ɨ����� */
    pst_scan_params->uc_vap_id    = pst_hmac_vap->st_vap_base_info.uc_vap_id;
    pst_scan_params->en_scan_mode = WLAN_SCAN_MODE_FOREGROUND;
    pst_scan_params->en_need_switch_back_home_channel = OAL_FALSE;

    /* 2.�޸�ɨ��ģʽ���ŵ�ɨ�����: �����Ƿ����up״̬�µ�vap������ǣ����Ǳ���ɨ�裬������ǣ�����ǰ��ɨ�� */
    ul_ret = mac_device_find_up_vap(pst_mac_device, &pst_mac_vap_temp);
    if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_mac_vap_temp))
    {
        /* �ж�vap�����ͣ������sta��Ϊsta�ı���ɨ�裬�����ap������ap�ı���ɨ�裬�������͵�vap�ݲ�֧�ֱ���ɨ�� */
        en_vap_mode = pst_hmac_vap->st_vap_base_info.en_vap_mode;
        if (WLAN_VAP_MODE_BSS_STA == en_vap_mode)
        {
            /* �޸�ɨ�����Ϊsta�ı���ɨ�� */
            pst_scan_params->en_scan_mode = WLAN_SCAN_MODE_BACKGROUND_STA;
        }
        else if (WLAN_VAP_MODE_BSS_AP == en_vap_mode)
        {
            /* �޸�ɨ�����Ϊsta�ı���ɨ�� */
            pst_scan_params->en_scan_mode = WLAN_SCAN_MODE_BACKGROUND_AP;
        }
        else
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_scan_update_scan_params::vap mode[%d], not support bg scan.}", en_vap_mode);
            return OAL_FAIL;
        }
        pst_scan_params->en_need_switch_back_home_channel = OAL_TRUE;

        if (1 == mac_device_calc_up_vap_num(pst_mac_device) && !IS_LEGACY_VAP(pst_mac_vap_temp) && IS_LEGACY_VAP(&pst_hmac_vap->st_vap_base_info))
        {
            /* �޸�ɨ���ŵ����(2)�ͻع����ŵ�����ʱ��(60ms):�������P2P���ڹ���״̬��wlan����ȥ����״̬,wlan�����ɨ�� */
            pst_scan_params->uc_scan_channel_interval       = MAC_SCAN_CHANNEL_INTERVAL_PERFORMANCE;
            pst_scan_params->us_work_time_on_home_channel   = MAC_WORK_TIME_ON_HOME_CHANNEL_PERFORMANCE;

            if((pst_scan_params->us_scan_time > WLAN_DEFAULT_ACTIVE_SCAN_TIME)
               && (WLAN_SCAN_TYPE_ACTIVE == pst_scan_params->en_scan_type))
            {
                /* ָ��SSIDɨ�賬��3��,���޸�ÿ��ɨ��ʱ��Ϊ40ms(Ĭ����20ms) */
                /* P2P������wlanδ��������,���ǵ�ɨ��ʱ�����Ӷ�p2p wfd������Ӱ��,����ÿ�ŵ�ɨ�����Ϊ1��(Ĭ��Ϊ2��) */
                pst_scan_params->uc_max_scan_count_per_channel = 1;
            }
        }
        else
        {
            /* �������Ĭ��ɨ��6���ŵ���home�ŵ�����100ms */
            pst_scan_params->uc_scan_channel_interval       = MAC_SCAN_CHANNEL_INTERVAL_DEFAULT;
            pst_scan_params->us_work_time_on_home_channel   = MAC_WORK_TIME_ON_HOME_CHANNEL_DEFAULT;
        }
    }
    /* 3.���÷��͵�probe req֡��Դmac addr */
    pst_scan_params->en_is_random_mac_addr_scan = en_is_random_mac_addr_scan;
    hmac_scan_set_sour_mac_addr_in_probe_req(pst_hmac_vap, pst_scan_params->auc_sour_mac_addr,
                                             en_is_random_mac_addr_scan, pst_scan_params->bit_is_p2p0_scan);

    /* do foreground scan and switch back while requested by main proxysta */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (mac_vap_is_msta(&pst_hmac_vap->st_vap_base_info)
        && (pst_hmac_vap->st_vap_base_info.en_vap_state != MAC_VAP_STATE_UP))
    {
        pst_scan_params->en_need_switch_back_home_channel = OAL_TRUE;
        pst_scan_params->en_scan_mode = WLAN_SCAN_MODE_FOREGROUND;
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_check_is_dispatch_scan_req
 ��������  : ����Ƿ��ܹ�����ɨ�裬������ԣ����¼ɨ�������ߵ���Ϣ���������һ��ɨ����
 �������  : hmac_vap_stru       *pst_hmac_vap,
             hmac_device_stru    *pst_hmac_device
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��18��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_scan_check_can_enter_scan_state(mac_vap_stru    *pst_mac_vap)
{
    /* p2p�п��ܽ��м������������Ǻ�scan req�����ȼ�һ������˵��ϲ㷢�����ɨ������ʱ��ͳһ��ʹ������Ľӿ��ж� */
    return hmac_p2p_check_can_enter_state(pst_mac_vap, HMAC_FSM_INPUT_SCAN_REQ);
}

/*****************************************************************************
 �� �� ��  : hmac_scan_check_is_dispatch_scan_req
 ��������  : ����Ƿ��ܹ�����ɨ�裬������ԣ����¼ɨ�������ߵ���Ϣ���������һ��ɨ����
 �������  : hmac_vap_stru       *pst_hmac_vap,
             hmac_device_stru    *pst_hmac_device
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��18��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_scan_check_is_dispatch_scan_req(hmac_vap_stru       *pst_hmac_vap,
                                                            hmac_device_stru    *pst_hmac_device)
{
    oal_uint32  ul_ret;

    /* 1.�ȼ������vap��״̬�Ӷ��ж��Ƿ�ɽ���ɨ��״̬��ʹ��ɨ�辡��������������������� */
    ul_ret = hmac_scan_check_can_enter_scan_state(&(pst_hmac_vap->st_vap_base_info));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{hmac_scan_check_is_dispatch_scan_req::Because of err_code[%d], can't enter into scan state.}", ul_ret);
        return ul_ret;
    }

    /* 2.�жϵ�ǰɨ���Ƿ�����ִ�� */
    if (OAL_TRUE == pst_hmac_device->st_scan_mgmt.en_is_scanning)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_scan_check_is_dispatch_scan_req::the scan request is rejected.}");
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_ROAM
    /* 3.�жϵ�ǰ�Ƿ�����ִ������ */
    if (MAC_VAP_STATE_ROAMING == pst_hmac_vap->st_vap_base_info.en_vap_state)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_scan_check_is_dispatch_scan_req:: roam reject new scan.}");
        return OAL_FAIL;
    }
#endif //_PRE_WLAN_FEATURE_ROAM

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_proc_last_scan_record
 ��������  : ������һ�ε�ɨ���¼���ӿڷ�װ���Ӷ����ڿ���չ(δ������ʹ���ϻ������ж��Ƿ����)
 �������  : hmac_vap_stru       *pst_hmac_vap,
             hmac_device_stru    *pst_hmac_device
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hmac_scan_proc_last_scan_record(hmac_vap_stru       *pst_hmac_vap,
                                                              hmac_device_stru    *pst_hmac_device)
{
    /* �����proxysta�����ɨ���������ɨ���� */
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (mac_is_proxysta_enabled(pst_hmac_device->pst_device_base_info))
    {
        if (mac_vap_is_vsta(&pst_hmac_vap->st_vap_base_info))
        {
            /* proxysta do nothing */
            OAM_INFO_LOG0(0, OAM_SF_SCAN, "{hmac_scan_proc_scan_req_event:: proxysta don't need clean scan record.}");
            return;
        }
    }
#endif

    OAM_INFO_LOG0(0, OAM_SF_SCAN, "{hmac_scan_proc_scan_req_event:: start clean last scan record.}");

#if 0
    /* �����һ��ɨ���¼��Ϣ */
    hmac_scan_clean_scan_record(&(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt));
#else
    /* ����ɨ��������ʱ�������һ��ɨ�����й��ڵ�bss��Ϣ */
    hmac_scan_clean_expire_scanned_bss(pst_hmac_vap, &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt));
#endif

    return;
}


/*****************************************************************************
 �� �� ��  : hmac_scan_proc_scan_timeout_fn
 ��������  : host����ɨ������ʱ�䵽device�࣬��ֹ��˼�ͨ�š����¼����쳣�����host����ղ���
             ɨ����Ӧ�ĳ�ʱ�ص�������������ɨ��ģ���ڵĳ�ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��19��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_scan_proc_scan_timeout_fn(void *p_arg)
{
    hmac_device_stru                   *pst_hmac_device = (hmac_device_stru *)p_arg;
    hmac_vap_stru                      *pst_hmac_vap    = OAL_PTR_NULL;
    hmac_scan_record_stru              *pst_scan_record = OAL_PTR_NULL;
    oal_uint32                          ul_pedding_data = 0;

    /* ��ȡɨ���¼��Ϣ */
    pst_scan_record = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt);

    /* ��ȡhmac vap */
    pst_hmac_vap = mac_res_get_hmac_vap(pst_scan_record->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(pst_scan_record->uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scan_timeout_fn::pst_hmac_vap null.}");

        /* ɨ��״̬�ָ�Ϊδ��ִ�е�״̬ */
        pst_hmac_device->st_scan_mgmt.en_is_scanning = OAL_FALSE;
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���ݵ�ǰɨ������ͺ͵�ǰvap��״̬�������л�vap��״̬�������ǰ��ɨ�裬����Ҫ�л�vap��״̬ */
    if (WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        if (MAC_VAP_STATE_STA_WAIT_SCAN == pst_hmac_vap->st_vap_base_info.en_vap_state)
        {
            /* �ı�vap״̬��SCAN_COMP */
            hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_SCAN_COMP);
        }
        else if (MAC_VAP_STATE_UP == pst_hmac_vap->st_vap_base_info.en_vap_state)
        {
            /* ����ɨ��ʱ��Ҫ����֡���˵����� */
            hmac_set_rx_filter_value(&(pst_hmac_vap->st_vap_base_info));
        }
    }

    /* BEGIN:DTS2015072801307 1102 ��Ϊap ��40M ������ִ��ɨ�裬ɨ����ɺ�VAP ״̬�޸�Ϊɨ��ǰ��״̬ */
    if ((WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
        && (MAC_VAP_STATE_BUTT != pst_scan_record->en_vap_last_state))
    {
        hmac_fsm_change_state(pst_hmac_vap, pst_scan_record->en_vap_last_state);
        pst_scan_record->en_vap_last_state = MAC_VAP_STATE_BUTT;
    }
    /* END:DTS2015072801307 1102 ��Ϊap ��40M ������ִ��ɨ�裬ɨ����ɺ�VAP ״̬�޸�Ϊɨ��ǰ��״̬ */

    /* ����ɨ����Ӧ״̬Ϊ��ʱ */
    pst_scan_record->en_scan_rsp_status = MAC_SCAN_TIMEOUT;
    OAM_WARNING_LOG1(pst_scan_record->uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scan_timeout_fn::scan time out cookie [%x].}", pst_scan_record->ull_cookie);

    /* ���ɨ��ص�������Ϊ�գ�����ûص����� */
    if (OAL_PTR_NULL != pst_scan_record->p_fn_cb)
    {
        OAM_WARNING_LOG0(pst_scan_record->uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scan_timeout_fn::scan callback func proc.}");
        pst_scan_record->p_fn_cb(pst_scan_record);
    }

    /* DMAC ��ʱδ�ϱ�ɨ����ɣ�HMAC �·�ɨ��������ֹͣDMAC ɨ�� */
    hmac_config_scan_abort(&pst_hmac_vap->st_vap_base_info, OAL_SIZEOF(oal_uint32), (oal_uint8 *)&ul_pedding_data);

    /* ɨ��״̬�ָ�Ϊδ��ִ�е�״̬ */
    pst_hmac_device->st_scan_mgmt.en_is_scanning = OAL_FALSE;

    CHR_EXCEPTION(CHR_WIFI_DRV(CHR_WIFI_DRV_EVENT_SCAN,CHR_WIFI_DRV_ERROR_SCAN_TIMEOUT));

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : hmac_scan_proc_scan_req_event
 ��������  : ����ɨ������������
 �������  : pst_mac_device: ָ��device�ṹ��
             p_params: ����ɨ������Ĳ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��5��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_scan_proc_scan_req_event(hmac_vap_stru *pst_hmac_vap, oal_void *p_params)
{
    frw_event_mem_stru         *pst_event_mem;
    frw_event_stru             *pst_event;
    mac_scan_req_stru          *pst_h2d_scan_req_params;     /* hmac���͵�dmac��ɨ��������� */
    mac_scan_req_stru          *pst_scan_params;
    hmac_device_stru           *pst_hmac_device;
    hmac_scan_record_stru      *pst_scan_record;
    oal_uint32                  ul_scan_timeout;
    oal_uint32                  ul_ret;

    /* �����Ϸ��Լ�� */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == p_params)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_scan_proc_scan_req_event::param null, %p %p.}", pst_hmac_vap, p_params);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ɨ��ֹͣģ����� */
    if ((0 == g_en_bgscan_enable_flag) && (MAC_VAP_STATE_UP == pst_hmac_vap->st_vap_base_info.en_vap_state))
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "hmac_scan_proc_scan_req_event: g_en_bgscan_enable_flag= %d.", g_en_bgscan_enable_flag);
        return OAL_FAIL;
    }

    pst_scan_params = (mac_scan_req_stru *)p_params;

    /* �쳣�ж�: ɨ����ŵ�����Ϊ0 */
    if (0 == pst_scan_params->uc_channel_nums)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scan_req_event::channel_nums=0.}");
        return OAL_FAIL;
    }

    /* ��ȡhmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_scan_req_event::pst_hmac_device[%d] null.}",
                        pst_hmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    /* ���´˴�ɨ�������ɨ����� */
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    ul_ret = hmac_scan_update_scan_params(pst_hmac_vap, pst_scan_params, g_st_wlan_customize.uc_random_mac_addr_scan);
#else
    ul_ret = hmac_scan_update_scan_params(pst_hmac_vap, pst_scan_params, pst_hmac_device->st_scan_mgmt.en_is_random_mac_addr_scan);
#endif
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{hmac_scan_proc_scan_req_event::update scan mode failed, error[%d].}", ul_ret);
        return ul_ret;
    }

    /* ����Ƿ���Ϸ���ɨ���������������������ϣ�ֱ�ӷ��� */
    ul_ret = hmac_scan_check_is_dispatch_scan_req(pst_hmac_vap, pst_hmac_device);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{hmac_scan_proc_scan_req_event::Because of error[%d], can't dispatch scan req.}", ul_ret);
        return ul_ret;
    }

    /* ����ɨ��ģ�鴦��ɨ��״̬������ɨ�����󽫶��� */
    pst_hmac_device->st_scan_mgmt.en_is_scanning = OAL_TRUE;

    /* ������һ��ɨ���¼��Ŀǰֱ�������һ�ν��������������Ҫ�ϻ�ʱ�䴦�� */
    hmac_scan_proc_last_scan_record(pst_hmac_vap, pst_hmac_device);

    /* ��¼ɨ�跢���ߵ���Ϣ��ĳЩģ��ص�����ʹ�� */
    pst_scan_record = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt);
    pst_scan_record->uc_chip_id      = pst_hmac_device->pst_device_base_info->uc_chip_id;
    pst_scan_record->uc_device_id    = pst_hmac_device->pst_device_base_info->uc_device_id;
    pst_scan_record->uc_vap_id       = pst_scan_params->uc_vap_id;
    pst_scan_record->uc_chan_numbers = pst_scan_params->uc_channel_nums;
    pst_scan_record->p_fn_cb         = pst_scan_params->p_fn_cb;

    if (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{hmac_scan_proc_scan_req_event::save last en_vap_state:%d}", pst_hmac_vap->st_vap_base_info.en_vap_state);

        pst_scan_record->en_vap_last_state = pst_hmac_vap->st_vap_base_info.en_vap_state;
    }

    pst_scan_record->ull_cookie      = pst_scan_params->ull_cookie;

    /* ��¼ɨ�迪ʼʱ�� */
    pst_scan_record->st_scan_start_time = oal_ktime_get();

    /* ��ɨ�������¼���DMAC, �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(mac_scan_req_stru));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                       "{hmac_scan_proc_scan_req_event::alloc memory(%u) failed.}", OAL_SIZEOF(mac_scan_req_stru));

        /* �ָ�ɨ��״̬Ϊ������״̬ */
        pst_hmac_device->st_scan_mgmt.en_is_scanning = OAL_FALSE;
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �������ɨ���vap��ģʽΪsta�����ң������״̬Ϊ��up״̬���ҷ�p2p����״̬�����л���ɨ��״̬ */
    if ((WLAN_VAP_MODE_BSS_STA == pst_hmac_vap->st_vap_base_info.en_vap_mode) &&
        (MAC_SCAN_FUNC_P2P_LISTEN != pst_scan_params->uc_scan_func))
    {
        if (MAC_VAP_STATE_UP != pst_hmac_vap->st_vap_base_info.en_vap_state)
        {
            /* �л�vap��״̬ΪWAIT_SCAN״̬ */
            hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_STA_WAIT_SCAN);
        }
        else
        {
            /* ����ɨ��ʱ��Ҫ����֡���˵����� */
            pst_hmac_vap->st_vap_base_info.en_vap_state = MAC_VAP_STATE_STA_WAIT_SCAN;
            hmac_set_rx_filter_value(&(pst_hmac_vap->st_vap_base_info));
            pst_hmac_vap->st_vap_base_info.en_vap_state = MAC_VAP_STATE_UP;
        }
    }
    else if (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode)
    {
        mac_vap_state_enum_uint8 en_state_bak = pst_hmac_vap->st_vap_base_info.en_vap_state;
        pst_hmac_vap->st_vap_base_info.en_vap_state = MAC_VAP_STATE_AP_WAIT_START;
        hmac_set_rx_filter_value(&(pst_hmac_vap->st_vap_base_info));
        pst_hmac_vap->st_vap_base_info.en_vap_state = en_state_bak;
    }

    /* AP������ɨ�������⴦����hostapd�·�ɨ������ʱ��VAP������INIT״̬ */
    if ( (WLAN_VAP_MODE_BSS_AP == pst_hmac_vap->st_vap_base_info.en_vap_mode) &&
         (MAC_VAP_STATE_INIT == pst_hmac_vap->st_vap_base_info.en_vap_state) )
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
            "{hmac_scan_proc_scan_req_event::ap startup scan.}");
        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_AP_WAIT_START);
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCAN_REQ,
                       OAL_SIZEOF(mac_scan_req_stru),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    /* ֱ�Ӵ����ݣ����ζ��Ʒ�Ĳ��� */
    pst_h2d_scan_req_params = (mac_scan_req_stru *)(pst_event->auc_event_data);

    /* ����ɨ������������¼�data���� */
    oal_memcopy(pst_h2d_scan_req_params, pst_scan_params, OAL_SIZEOF(mac_scan_req_stru));

    /* ��ӡɨ�����������ʹ�� */
    /* �����P2P ���������������HMAC ɨ�賬ʱʱ��ΪP2P ����ʱ�� */
    if (MAC_SCAN_FUNC_P2P_LISTEN == pst_scan_params->uc_scan_func)
    {
        ul_scan_timeout = pst_scan_params->us_scan_time * 2;
    }
    else
    {
        ul_scan_timeout = WLAN_DEFAULT_MAX_TIME_PER_SCAN;
    }
    hmac_scan_print_scan_params(pst_h2d_scan_req_params, &pst_hmac_vap->st_vap_base_info);

    /* ����ɨ�豣����ʱ������ֹ���¼����˼�ͨ��ʧ�ܵ�����µ��쳣��������ʱ�������ĳ�ʱʱ��Ϊ4.5�� */
    FRW_TIMER_CREATE_TIMER(&(pst_hmac_device->st_scan_mgmt.st_scan_timeout),
                           hmac_scan_proc_scan_timeout_fn,
                           ul_scan_timeout,
                           pst_hmac_device,
                           OAL_FALSE,
                           OAM_MODULE_ID_HMAC,
                           pst_hmac_device->pst_device_base_info->ul_core_id);

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_proc_sched_scan_req_event
 ��������  : ����pno����ɨ����������
 �������  : pst_mac_device: ָ��device�ṹ��
             p_params: ����ɨ������Ĳ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_scan_proc_sched_scan_req_event(hmac_vap_stru *pst_hmac_vap, oal_void *p_params)
{
    frw_event_mem_stru         *pst_event_mem;
    frw_event_stru             *pst_event;
    hmac_device_stru           *pst_hmac_device;
    hmac_scan_record_stru      *pst_scan_record;
    mac_pno_scan_stru          *pst_pno_scan_params;
    oal_uint32                  ul_ret;

    /* �����Ϸ��Լ�� */
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_hmac_vap) || (OAL_PTR_NULL == p_params)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{hmac_scan_proc_sched_scan_req_event::param null, %p %p.}", pst_hmac_vap, p_params);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_pno_scan_params = (mac_pno_scan_stru *)p_params;

    /* �ж�PNO����ɨ���·��Ĺ��˵�ssid����С�ڵ���0 */
    if (pst_pno_scan_params->l_ssid_count <= 0)
    {
        OAM_WARNING_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_sched_scan_req_event::ssid_count <=0.}");
        return OAL_FAIL;
    }

    /* ��ȡhmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_sched_scan_req_event::pst_hmac_device[%d] null.}",
                        pst_hmac_vap->st_vap_base_info.uc_device_id);
        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    /* ����Ƿ���Ϸ���ɨ���������������������ϣ�ֱ�ӷ��� */
    ul_ret = hmac_scan_check_is_dispatch_scan_req(pst_hmac_vap, pst_hmac_device);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN,
                         "{hmac_scan_proc_sched_scan_req_event::Because of error[%d], can't dispatch scan req.}", ul_ret);
        return ul_ret;
    }

    /* �����һ�ε�ɨ���� */
    hmac_scan_proc_last_scan_record(pst_hmac_vap, pst_hmac_device);

    /* ��¼ɨ�跢���ߵ���Ϣ��ĳЩģ��ص�����ʹ�� */
    pst_scan_record = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt);
    pst_scan_record->uc_chip_id   = pst_hmac_device->pst_device_base_info->uc_chip_id;
    pst_scan_record->uc_device_id = pst_hmac_device->pst_device_base_info->uc_device_id;
    pst_scan_record->uc_vap_id    = pst_hmac_vap->st_vap_base_info.uc_vap_id;
    pst_scan_record->p_fn_cb      = pst_pno_scan_params->p_fn_cb;

    /* ��ɨ�������¼���DMAC, �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(pst_pno_scan_params));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_SCAN, "{hmac_scan_proc_sched_scan_req_event::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CTX,
                       DMAC_WLAN_CTX_EVENT_SUB_TYPE_SCHED_SCAN_REQ,
                       OAL_SIZEOF(pst_pno_scan_params),
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_hmac_vap->st_vap_base_info.uc_chip_id,
                       pst_hmac_vap->st_vap_base_info.uc_device_id,
                       pst_hmac_vap->st_vap_base_info.uc_vap_id);

    /* �¼�data����Я��PNOɨ��������� */
    oal_memcopy(frw_get_event_payload(pst_event_mem), (oal_uint8 *)&pst_pno_scan_params, OAL_SIZEOF(mac_pno_scan_stru *));

    /* �ַ��¼� */
    frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_process_chan_result_event
 ��������  : ����dmac�ϱ����ŵ�ɨ��������DMAC�ϱ����ŵ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_scan_process_chan_result_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    hmac_device_stru                   *pst_hmac_device;
    dmac_crx_chan_result_stru          *pst_chan_result_param;
    hmac_scan_record_stru              *pst_scan_record;
    oal_uint8                           uc_scan_idx;

    /* ��ȡ�¼���Ϣ */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_chan_result_param   = (dmac_crx_chan_result_stru *)(pst_event->auc_event_data);
    uc_scan_idx             = pst_chan_result_param->uc_scan_idx;

    /* ��ȡhmac device */
    pst_hmac_device = hmac_res_get_mac_dev(pst_event_hdr->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{hmac_scan_process_chan_result_event::pst_hmac_device is null.}");
        return OAL_FAIL;
    }

    pst_scan_record = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt);

    /* ����ϱ��������Ƿ�Ϸ� */
    if (uc_scan_idx >= pst_scan_record->uc_chan_numbers)
    {
        /* dmac�ϱ���ɨ����������Ҫɨ����ŵ����� */
        OAM_WARNING_LOG2(0, OAM_SF_SCAN,
                         "{hmac_scan_process_chan_result_event::result from dmac error! scan_idx[%d], chan_numbers[%d].}",
                         uc_scan_idx, pst_scan_record->uc_chan_numbers);

        return OAL_FAIL;
    }

    pst_scan_record->ast_chan_results[uc_scan_idx] = pst_chan_result_param->st_chan_result;

    return OAL_SUCC;
}
#ifdef _PRE_WLAN_FEATURE_11K
/*****************************************************************************
 �� �� ��  : hmac_scan_rrm_proc_save_bss
 ��������  : ��dmac�����ѱ���bss��chan num, bssid,
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��27��
    ��    ��   : yangguisen
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_scan_rrm_proc_save_bss(mac_vap_stru *pst_mac_vap, oal_uint8 uc_len, oal_uint8 *puc_param)
{
    oal_netbuf_stru                 *pst_action_table_bcn_rpt;
    oal_uint8                       *puc_data;
    mac_user_stru                   *pst_mac_user;
    oal_uint16                       us_index = 0;
    mac_meas_rpt_ie_stru            *pst_meas_rpt_ie;
    mac_bcn_rpt_stru                *pst_bcn_rpt;
    mac_tx_ctl_stru                 *pst_tx_ctl;
    mac_vap_rrm_trans_req_info_stru *pst_trans_req_info;
    oal_uint32                       ul_ret;
    hmac_device_stru                *pst_hmac_device;
    hmac_bss_mgmt_stru              *pst_bss_mgmt;
    oal_dlist_head_stru             *pst_entry;
    hmac_scanned_bss_info           *pst_scanned_bss;
    oal_uint8                        uc_bss_idx = 0;

    if (OAL_PTR_NULL == puc_param)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{hmac_scan_rrm_proc_save_bss::puc_param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_trans_req_info = (mac_vap_rrm_trans_req_info_stru *)puc_param;

    pst_action_table_bcn_rpt = (oal_netbuf_stru *)OAL_MEM_NETBUF_ALLOC(OAL_NORMAL_NETBUF, WLAN_MEM_NETBUF_SIZE2, OAL_NETBUF_PRIORITY_MID);
    if(OAL_PTR_NULL == pst_action_table_bcn_rpt)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ASSOC, "{hmac_scan_rrm_proc_save_bss::pst_action_table_bcn_rpt null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEMZERO(oal_netbuf_cb(pst_action_table_bcn_rpt), OAL_NETBUF_CB_SIZE());

    puc_data = (oal_uint8 *)OAL_NETBUF_HEADER(pst_action_table_bcn_rpt);

    /*************************************************************************/
    /*                        Management Frame Format                        */
    /* --------------------------------------------------------------------  */
    /* |Frame Control|Duration|DA|SA|BSSID|Sequence Control|Frame Body|FCS|  */
    /* --------------------------------------------------------------------  */
    /* | 2           |2       |6 |6 |6    |2               |0 - 2312  |4  |  */
    /* --------------------------------------------------------------------  */
    /*                                                                       */
    /*************************************************************************/

    /*************************************************************************/
    /*                Set the fields in the frame header                     */
    /*************************************************************************/

    /* All the fields of the Frame Control Field are set to zero. Only the   */
    /* Type/Subtype field is set.                                            */
    mac_hdr_set_frame_control(puc_data, WLAN_PROTOCOL_VERSION| WLAN_FC0_TYPE_MGT | WLAN_FC0_SUBTYPE_ACTION);

    /* duration */
    puc_data[2] = 0;
    puc_data[3] = 0;

    pst_mac_user = mac_res_get_mac_user(pst_mac_vap->uc_assoc_vap_id);
    if (OAL_PTR_NULL == pst_mac_user)
    {
        OAM_ERROR_LOG1(0, OAM_SF_TX, "{hmac_scan_rrm_proc_save_bss::pst_mac_user[%d] null.", pst_mac_vap->uc_assoc_vap_id);

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* DA is address of STA requesting association */
    oal_set_mac_addr(puc_data + 4, pst_mac_user->auc_user_mac_addr);

    /* SA is the dot11MACAddress */
    oal_set_mac_addr(puc_data + 10, pst_mac_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);

    oal_set_mac_addr(puc_data + 16, pst_mac_vap->auc_bssid);

    /* seq control */
    puc_data[22] = 0;
    puc_data[23] = 0;

    /*************************************************************************/
    /*                    Radio Measurement Report Frame - Frame Body        */
    /* --------------------------------------------------------------------- */
    /* |Category |Action |Dialog Token| Measurement Report Elements         |*/
    /* --------------------------------------------------------------------- */
    /* |1        |1      | 1          |  var                                 */
    /* --------------------------------------------------------------------- */
    /*                                                                       */
    /*************************************************************************/

    /* Initialize index and the frame data pointer */
    us_index = MAC_80211_FRAME_LEN;

    /* Category */
    puc_data[us_index++] = MAC_ACTION_CATEGORY_RADIO_MEASURMENT;

    /* Action */
    puc_data[us_index++] = MAC_RM_ACTION_RADIO_MEASUREMENT_REPORT;

    /* Dialog Token  */
    puc_data[us_index++]  = pst_trans_req_info->uc_action_dialog_token;

    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_scan_rrm_proc_save_bss::pst_hmac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ����ɨ���bss����Ľṹ�� */
    pst_bss_mgmt = &(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt.st_bss_mgmt);


    pst_meas_rpt_ie = (mac_meas_rpt_ie_stru *)(puc_data + us_index);

    /* ������ɾ����ǰ���� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        if (0 == oal_memcmp(pst_scanned_bss->st_bss_dscr_info.ac_ssid, pst_trans_req_info->auc_ssid, pst_trans_req_info->us_ssid_len))
        {
            /*************************************************************************/
            /*                   Measurement Report IE - Frame Body                  */
            /* --------------------------------------------------------------------- */
            /* |Element ID |Length |Meas Token| Meas Rpt Mode | Meas Type | Meas Rpt|*/
            /* --------------------------------------------------------------------- */
            /* |1          |1      | 1        |  1            | 1         | var      */
            /* --------------------------------------------------------------------- */
            /*                                                                       */
            /*************************************************************************/
            pst_meas_rpt_ie->uc_eid = MAC_EID_MEASREP;
            pst_meas_rpt_ie->uc_len = 3 + MAC_BEACON_RPT_FIX_LEN;
            pst_meas_rpt_ie->uc_token = pst_trans_req_info->uc_meas_token;
            OAL_MEMZERO(&(pst_meas_rpt_ie->st_rptmode), OAL_SIZEOF(mac_meas_rpt_mode_stru));
            pst_meas_rpt_ie->uc_rpttype = 5;

            pst_bcn_rpt = (mac_bcn_rpt_stru *)pst_meas_rpt_ie->auc_meas_rpt;
            OAL_MEMZERO(pst_bcn_rpt, OAL_SIZEOF(mac_bcn_rpt_stru));
            oal_memcopy(pst_bcn_rpt->auc_bssid, pst_scanned_bss->st_bss_dscr_info.auc_bssid, WLAN_MAC_ADDR_LEN);
            pst_bcn_rpt->uc_channum = pst_scanned_bss->st_bss_dscr_info.st_channel.uc_chan_number;
            pst_bcn_rpt->uc_optclass = pst_trans_req_info->uc_oper_class;
            pst_meas_rpt_ie = (mac_meas_rpt_ie_stru *)pst_bcn_rpt->auc_subelm;
            uc_bss_idx++;
        }
    }
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));
    pst_tx_ctl = (mac_tx_ctl_stru *)oal_netbuf_cb(pst_action_table_bcn_rpt);
    pst_tx_ctl->us_mpdu_len  = us_index + uc_bss_idx * (MAC_MEASUREMENT_RPT_FIX_LEN + MAC_BEACON_RPT_FIX_LEN);
    pst_tx_ctl->us_tx_user_idx  = 0xffff;                        /* ���������Ҫ��ȡuser�ṹ�� */

    oal_netbuf_put(pst_action_table_bcn_rpt, pst_tx_ctl->us_mpdu_len);

    ul_ret = hmac_tx_mgmt_send_event(pst_mac_vap, pst_action_table_bcn_rpt, pst_tx_ctl->us_mpdu_len);
    if (OAL_SUCC != ul_ret)
    {
        oal_netbuf_free(pst_action_table_bcn_rpt);
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_scan_rrm_proc_save_bss::hmac_tx_mgmt_send_event failed[%d].}", ul_ret);
    }

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_scan_init
 ��������  : ɨ��ģ���ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��14��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_scan_init(hmac_device_stru *pst_hmac_device)
{
    hmac_scan_stru      *pst_scan_mgmt;
    hmac_bss_mgmt_stru  *pst_bss_mgmt;

    /* ��ʼ��ɨ�����ṹ����Ϣ */
    pst_scan_mgmt = &(pst_hmac_device->st_scan_mgmt);
    OAL_MEMZERO(pst_scan_mgmt, OAL_SIZEOF(hmac_scan_stru));
    pst_scan_mgmt->en_is_scanning = OAL_FALSE;
    pst_scan_mgmt->st_scan_record_mgmt.en_vap_last_state = MAC_VAP_STATE_BUTT;

    /* ��ʼ��bss������������� */
    pst_bss_mgmt = &(pst_scan_mgmt->st_scan_record_mgmt.st_bss_mgmt);
    oal_dlist_init_head(&(pst_bss_mgmt->st_bss_list_head));
    oal_spin_lock_init(&(pst_bss_mgmt->st_lock));

    /* ��ʼ���ں��·�ɨ��request��Դ�� */
    oal_spin_lock_init(&(pst_scan_mgmt->st_scan_request_spinlock));

    /* ��ʼ�� st_wiphy_mgmt �ṹ */
    OAL_WAIT_QUEUE_INIT_HEAD(&(pst_scan_mgmt->st_wait_queue));

#if  defined(_PRE_WLAN_CHIP_TEST_ALG) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && defined(_PRE_DEBUG_MODE)
    hmac_scan_ct_init();
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_exit
 ��������  : hmacɨ��ģ���˳�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��14��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_scan_exit(hmac_device_stru *pst_hmac_device)
{
    hmac_scan_stru      *pst_scan_mgmt;

    /* ���ɨ���¼��Ϣ */
    hmac_scan_clean_scan_record(&(pst_hmac_device->st_scan_mgmt.st_scan_record_mgmt));

    /* ���ɨ�����ṹ����Ϣ */
    pst_scan_mgmt = &(pst_hmac_device->st_scan_mgmt);
    OAL_MEMZERO(pst_scan_mgmt, OAL_SIZEOF(hmac_scan_stru));
    pst_scan_mgmt->en_is_scanning = OAL_FALSE;

#if  defined(_PRE_WLAN_CHIP_TEST_ALG) && (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && defined(_PRE_DEBUG_MODE)
    hmac_scan_ct_exit();
#endif

    return;
}


#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : hmac_scan_test_cb
 ��������  : ɨ����ԵĻص�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��29��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_scan_test_cb(void *p_scan_record)
{
    hmac_scan_record_stru           *pst_scan_record;
    hmac_bss_mgmt_stru              *pst_bss_mgmt;
    mac_bss_dscr_stru               *pst_bss_dscr;
    hmac_scanned_bss_info           *pst_scanned_bss;
    oal_dlist_head_stru             *pst_entry;
    oal_time_us_stru                 st_curr_time;
    oal_uint8                        uc_idx;

    if (OAL_PTR_NULL == p_scan_record)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "pst_scan_record is null ptr.");
        return;
    }

    pst_scan_record = (hmac_scan_record_stru *)p_scan_record;

    /* ��ӡ�ŵ�������� */
    OAL_IO_PRINT("The chan measure result: \n");
    for (uc_idx = 0; uc_idx < pst_scan_record->uc_chan_numbers; uc_idx++)
    {
        OAL_IO_PRINT("[channel_result]Chan num      : %d\n", pst_scan_record->ast_chan_results[uc_idx].uc_channel_number);
        OAL_IO_PRINT("[channel_result]Stats cnt     : %d\n", pst_scan_record->ast_chan_results[uc_idx].uc_stats_cnt);
        OAL_IO_PRINT("[channel_result]Stats valid   : %d\n", pst_scan_record->ast_chan_results[uc_idx].uc_stats_valid);
        OAL_IO_PRINT("[channel_result]Stats time us : %d\n", pst_scan_record->ast_chan_results[uc_idx].ul_total_stats_time_us);
        OAL_IO_PRINT("[channel_result]Free time 20M : %d\n", pst_scan_record->ast_chan_results[uc_idx].ul_total_free_time_20M_us);
        OAL_IO_PRINT("[channel_result]Free time 40M : %d\n", pst_scan_record->ast_chan_results[uc_idx].ul_total_free_time_40M_us);
        OAL_IO_PRINT("[channel_result]Free time 80M : %d\n", pst_scan_record->ast_chan_results[uc_idx].ul_total_free_time_80M_us);
        OAL_IO_PRINT("[channel_result]Send time     : %d\n", pst_scan_record->ast_chan_results[uc_idx].ul_total_send_time_us);
        OAL_IO_PRINT("[channel_result]Recv time     : %d\n", pst_scan_record->ast_chan_results[uc_idx].ul_total_recv_time_us);
        OAL_IO_PRINT("[channel_result]Free power cnt: %d\n", pst_scan_record->ast_chan_results[uc_idx].uc_free_power_cnt);
        OAL_IO_PRINT("[channel_result]Free power 20M: %d\n", pst_scan_record->ast_chan_results[uc_idx].s_free_power_stats_20M);
        OAL_IO_PRINT("[channel_result]Free power 40M: %d\n", pst_scan_record->ast_chan_results[uc_idx].s_free_power_stats_40M);
        OAL_IO_PRINT("[channel_result]Free power 80M: %d\n", pst_scan_record->ast_chan_results[uc_idx].s_free_power_stats_80M);
        OAL_IO_PRINT("[channel_result]Radar detected: %d\n", pst_scan_record->ast_chan_results[uc_idx].uc_radar_detected);
        OAL_IO_PRINT("[channel_result]Radar bw      : %d\n\n", pst_scan_record->ast_chan_results[uc_idx].uc_radar_bw);
    }

    /* ��ӡBSS��� */
    OAL_IO_PRINT("The bss result: \n");

    /* ��ȡɨ�����Ĺ���ṹ��ַ */
    pst_bss_mgmt = &(pst_scan_record->st_bss_mgmt);

    /* ��ȡ�� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ����ɨ�赽��bss��Ϣ */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);
        if ((OAL_PTR_NULL == pst_bss_dscr) || (OAL_PTR_NULL == pst_bss_dscr->auc_mgmt_buff))
        {
            continue;
        }

        OAL_IO_PRINT("Chan num      : %d\n", pst_bss_dscr->st_channel.uc_chan_number);
        OAL_IO_PRINT("BSSID         : 0x%x:0x%x:0x%x:0x%x:0x%x:0x%x\n\n", pst_bss_dscr->auc_bssid[0],
                                                                          pst_bss_dscr->auc_bssid[1],
                                                                          pst_bss_dscr->auc_bssid[2],
                                                                          pst_bss_dscr->auc_bssid[3],
                                                                          pst_bss_dscr->auc_bssid[4],
                                                                          pst_bss_dscr->auc_bssid[5]);
    }

	/* �ͷ��� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    /* ��ӡ�˴�ɨ���ʱ */
    oal_time_get_stamp_us(&st_curr_time);
    OAL_IO_PRINT("Scan start time: %d %d\n", (oal_uint32)pst_scan_record->st_scan_start_timestamp.i_sec, (oal_uint32)pst_scan_record->st_scan_start_timestamp.i_usec);
    OAL_IO_PRINT("Scan end   time: %d %d\n\n", (oal_uint32)st_curr_time.i_sec, (oal_uint32)st_curr_time.i_usec);

    return;
}

/*****************************************************************************
 �� �� ��  : hmac_scan_test
 ��������  : ɨ��ģ����ԣ�ȫ�ŵ����������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��29��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_scan_test(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    mac_scan_req_stru   st_scan_req;
    oal_uint8           uc_chan_idx;
    oal_uint32          ul_ret;
    oal_uint8           uc_2g_chan_num = 0;
    oal_uint8           uc_5g_chan_num = 0;
    oal_uint8           uc_chan_number = 0;
    oal_int8            ac_param[15] = {0};
    oal_bool_enum_uint8 en_2g_all = OAL_FALSE;
    oal_bool_enum_uint8 en_5g_all = OAL_FALSE;
    mac_ioctl_scan_test_config_stru *pst_scan_test;
    hmac_vap_stru                   *pst_hmac_vap;

    pst_scan_test = (mac_ioctl_scan_test_config_stru *)puc_param;

    oal_memcopy(ac_param, pst_scan_test->ac_scan_type, sizeof(pst_scan_test->ac_scan_type));
    OAL_MEMZERO(&st_scan_req, OAL_SIZEOF(st_scan_req));

    if (0 == oal_strcmp("2g", ac_param))
    {
        en_2g_all = OAL_TRUE;
    }
    else if (0 == oal_strcmp("5g", ac_param))
    {
        en_5g_all = OAL_TRUE;
    }
    else if (0 == oal_strcmp("all", ac_param))
    {
        en_2g_all = OAL_TRUE;
        en_5g_all = OAL_TRUE;
    }
    else
    {
        /* ָ�������ŵ� */
        uc_chan_number = (oal_uint8)oal_atoi(ac_param);
    }

    if (en_2g_all)
    {
        /* 2Gȫ�ŵ� */
        for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_chan_idx++)
        {
            ul_ret = mac_is_channel_idx_valid(WLAN_BAND_2G, uc_chan_idx);
            if (OAL_SUCC == ul_ret)
            {
                mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_chan_idx, &uc_chan_number);

                st_scan_req.ast_channel_list[uc_2g_chan_num].uc_chan_number = uc_chan_number;
                st_scan_req.ast_channel_list[uc_2g_chan_num].en_band        = WLAN_BAND_2G;
                st_scan_req.ast_channel_list[uc_2g_chan_num].uc_idx         = uc_chan_idx;
                st_scan_req.ast_channel_list[uc_2g_chan_num].en_bandwidth   = pst_scan_test->en_bandwidth;
                st_scan_req.uc_channel_nums++;
                uc_2g_chan_num++;
            }
        }
    }

    if (en_5g_all)
    {
        /* 5Gȫ�ŵ� */
        for (uc_chan_idx = 0; uc_chan_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_chan_idx++)
        {
            ul_ret = mac_is_channel_idx_valid(WLAN_BAND_5G, uc_chan_idx);
            if (OAL_SUCC == ul_ret)
            {
                mac_get_channel_num_from_idx(WLAN_BAND_5G, uc_chan_idx, &uc_chan_number);

                st_scan_req.ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].uc_chan_number = uc_chan_number;
                st_scan_req.ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].en_band        = WLAN_BAND_5G;
                st_scan_req.ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].uc_idx         = uc_chan_idx;
                st_scan_req.ast_channel_list[uc_2g_chan_num + uc_5g_chan_num].en_bandwidth   = pst_scan_test->en_bandwidth;
                st_scan_req.uc_channel_nums++;
                uc_5g_chan_num++;
            }
        }
    }

    if (OAL_FALSE == en_2g_all && OAL_FALSE == en_5g_all)
    {
        if (uc_chan_number < 15)
        {
            ul_ret = mac_is_channel_num_valid(WLAN_BAND_2G, uc_chan_number);
            if (OAL_SUCC != ul_ret)
            {
                OAL_IO_PRINT("Invalid chan num: %d. return!\n", uc_chan_number);
                return OAL_FAIL;
            }
            st_scan_req.ast_channel_list[0].en_band        = WLAN_BAND_2G;
        }
        else
        {
            ul_ret = mac_is_channel_num_valid(WLAN_BAND_5G, uc_chan_number);
            if (OAL_SUCC != ul_ret)
            {
                OAL_IO_PRINT("Invalid chan num: %d. return!\n", uc_chan_number);
                return OAL_FAIL;
            }
            st_scan_req.ast_channel_list[0].en_band        = WLAN_BAND_5G;
        }

        st_scan_req.ast_channel_list[0].uc_chan_number = uc_chan_number;
        st_scan_req.ast_channel_list[0].en_bandwidth   = pst_scan_test->en_bandwidth;

        mac_get_channel_idx_from_num(st_scan_req.ast_channel_list[0].en_band,
                                     st_scan_req.ast_channel_list[0].uc_chan_number,
                                     &(st_scan_req.ast_channel_list[0].uc_idx));

        st_scan_req.uc_channel_nums                    = 1;
    }

    st_scan_req.en_bss_type  = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    st_scan_req.en_scan_type = WLAN_SCAN_TYPE_ACTIVE;
    st_scan_req.uc_bssid_num = 0;
    st_scan_req.uc_ssid_num  = 0;

    oal_set_mac_addr(st_scan_req.auc_bssid[0], BROADCAST_MACADDR);
    st_scan_req.uc_bssid_num = 1;

    st_scan_req.us_scan_time = WLAN_DEFAULT_ACTIVE_SCAN_TIME;
    st_scan_req.en_scan_mode = WLAN_SCAN_MODE_FOREGROUND;
    st_scan_req.uc_scan_func = MAC_SCAN_FUNC_ALL;

    st_scan_req.p_fn_cb = hmac_scan_test_cb;

    pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    hmac_scan_proc_scan_req_event(pst_hmac_vap, &st_scan_req);

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_bgscan_enable
 ��������  : ��ֹɨ��ģ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��31��
    ��    ��   : W00346925
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_uint32  hmac_bgscan_enable(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
    oal_bool_enum_uint8       *pen_bgscan_enable_flag;

    pen_bgscan_enable_flag =  (oal_bool_enum_uint8 *)puc_param;                 /*����ɨ��ֹͣʹ��λ*/

    /* ����ɨ��ֹͣ���� */
    if (*pen_bgscan_enable_flag)
    {
        g_en_bgscan_enable_flag = OAL_TRUE;
    }
    else
    {
        g_en_bgscan_enable_flag = OAL_FALSE;
    }

    OAM_WARNING_LOG1(0, OAM_SF_SCAN, "hmac_bgscan_enable: g_en_bgscan_enable_flag= %d.", g_en_bgscan_enable_flag);

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_DBAC
/*****************************************************************************
 �� �� ��  : hmac_scan_start_dbac
 ��������  : ��HMAC����DBAC
 �������  : mac_device_stru *pst_dev
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��29��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32   hmac_scan_start_dbac(mac_device_stru *pst_dev)
{
    oal_uint8   auc_cmd[32];
    oal_uint16  us_len;
    oal_uint32  ul_ret = OAL_FAIL;
    oal_uint8   uc_idx;
#define DBAC_START_STR     " dbac start"
#define DBAC_START_STR_LEN 11
    mac_vap_stru  *pst_mac_vap = OAL_PTR_NULL;

    mac_ioctl_alg_config_stru  *pst_alg_config = (mac_ioctl_alg_config_stru *)auc_cmd;

    oal_memcopy(auc_cmd + OAL_SIZEOF(mac_ioctl_alg_config_stru), (const oal_int8 *)DBAC_START_STR, 11);
    auc_cmd[OAL_SIZEOF(mac_ioctl_alg_config_stru) + DBAC_START_STR_LEN ] = 0;

    pst_alg_config->uc_argc = 2;
    pst_alg_config->auc_argv_offset[0] = 1;
    pst_alg_config->auc_argv_offset[1] = 6;

    for(uc_idx = 0; uc_idx < pst_dev->uc_vap_num; uc_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_dev->auc_vap_id[uc_idx]);
        if(OAL_PTR_NULL != pst_mac_vap &&
        WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            break;
        }
    }
    if(pst_mac_vap)
    {
        us_len = OAL_SIZEOF(mac_ioctl_alg_config_stru) + DBAC_START_STR_LEN + 1;
        ul_ret = hmac_config_send_event(pst_mac_vap, WLAN_CFGID_ALG, us_len, auc_cmd);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{hmac_config_alg::hmac_config_send_event failed[%d].}", ul_ret);
        }
        OAL_IO_PRINT("start dbac\n");
    }
    else
    {
        OAL_IO_PRINT("no vap found to start dbac\n");
    }

    return ul_ret;
}
#endif
/*****************************************************************************
 �� �� ��  : hmac_start_all_bss_of_device
 ��������  : ������Ӧdevice�����д���WAIT START״̬��VAP
 �������  : mac_device_stru *pst_dev
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��27��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_start_all_bss_of_device(hmac_device_stru *pst_hmac_dev)
{
    oal_uint8      uc_idx;
    hmac_vap_stru *pst_hmac_vap;
    mac_device_stru *pst_dev = pst_hmac_dev->pst_device_base_info;

    OAM_WARNING_LOG1(0, OAM_SF_ACS, "{hmac_start_all_bss_of_device:device id=%d}", pst_hmac_dev->pst_device_base_info->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dev))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_start_all_bss_of_device::pst_device_base_info null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for(uc_idx = 0; uc_idx < pst_dev->uc_vap_num; uc_idx++)
    {
        pst_hmac_vap = mac_res_get_hmac_vap(pst_dev->auc_vap_id[uc_idx]);
        if (!pst_hmac_vap)
        {
            OAM_WARNING_LOG2(0, OAM_SF_ACS, "hmac_start_all_bss_of_device:null ap, idx=%d id=%d", uc_idx, pst_dev->auc_vap_id[uc_idx]);
            continue;
        }

        if(OAL_PTR_NULL != pst_hmac_vap &&
            (MAC_VAP_STATE_AP_WAIT_START == pst_hmac_vap->st_vap_base_info.en_vap_state
#ifdef _PRE_WLAN_FEATURE_DBAC
            || (mac_is_dbac_enabled(pst_dev) && MAC_VAP_STATE_PAUSE== pst_hmac_vap->st_vap_base_info.en_vap_state)
#endif
            || MAC_VAP_STATE_UP == pst_hmac_vap->st_vap_base_info.en_vap_state))
        {
            if(OAL_SUCC == hmac_chan_start_bss(pst_hmac_vap, OAL_PTR_NULL, WLAN_PROTOCOL_BUTT))
            {
                OAM_WARNING_LOG4(0, OAM_SF_ACS, "start vap %d on ch=%d band=%d bw=%d\n",
                    pst_dev->auc_vap_id[uc_idx],
                    pst_hmac_vap->st_vap_base_info.st_channel.uc_chan_number,
                    pst_hmac_vap->st_vap_base_info.st_channel.en_band,
                    pst_hmac_vap->st_vap_base_info.st_channel.en_bandwidth);
            }
        }
        else
        {
            OAM_WARNING_LOG0(0, OAM_SF_ACS, "start vap error\n");
            continue;
        }
    }

#ifdef _PRE_WLAN_FEATURE_DBAC
    if (mac_is_dbac_enabled(pst_dev))
    {
        return hmac_scan_start_dbac(pst_dev);
    }
#endif

    return OAL_SUCC;
}

/* TBD �˺�������scanģ�����ƴ�׮�ڴˣ���ҪACS��д�˽ӿ� �ŵ�hmac_acs�ļ��� */
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : hmac_get_pri_sec_chan
 ��������  : ��ȡbss���������ŵ�
 �������  : hmac_scan_record_stru *pst_scan_record
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : w00269675
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_get_pri_sec_chan(mac_bss_dscr_stru *pst_bss_dscr, oal_uint32 *pul_pri_chan, oal_uint32 *pul_sec_chan)
{
    *pul_pri_chan = *pul_sec_chan = 0;

    *pul_pri_chan = pst_bss_dscr->st_channel.uc_chan_number;

    OAM_INFO_LOG1(0, OAM_SF_2040, "hmac_get_pri_sec_chan:pst_bss_dscr->st_channel.en_bandwidth = %d\n", pst_bss_dscr->en_channel_bandwidth);

    if (WLAN_BAND_WIDTH_40PLUS == pst_bss_dscr->en_channel_bandwidth)
    {
        *pul_sec_chan = *pul_pri_chan + 4;
    }
    else if (WLAN_BAND_WIDTH_40MINUS == pst_bss_dscr->en_channel_bandwidth)
    {
        *pul_sec_chan = *pul_pri_chan - 4;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_2040, "hmac_get_pri_sec_chan: pst_bss_dscr is not support 40Mhz, *pul_sec_chan = %d\n", *pul_sec_chan);
    }

    OAM_INFO_LOG2(0, OAM_SF_2040, "*pul_pri_chan = %d, *pul_sec_chan = %d\n\n", *pul_pri_chan, *pul_sec_chan);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_switch_pri_sec
 ��������  : �����������ŵ�
 �������  : hmac_scan_record_stru *pst_scan_record
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : w00269675
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void hmac_switch_pri_sec(mac_vap_stru *pst_mac_vap)
{
    if (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth)
    {
        pst_mac_vap->st_channel.uc_chan_number = pst_mac_vap->st_channel.uc_chan_number + 4;
        pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_40MINUS;
    }
    else if (WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth)
    {
        pst_mac_vap->st_channel.uc_chan_number = pst_mac_vap->st_channel.uc_chan_number - 4;
        pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_40PLUS;
    }
    else
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_switch_pri_sec:en_bandwidth = %d\n not need obss scan\n",
                        pst_mac_vap->st_channel.en_bandwidth);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_obss_check_40mhz_2g
 ��������  : ��2G 40MHz����������д��������������:
            1)  ��BSS�����š����ŵ����������е�20/40MHz BSS�����ŵ������ŵ���ͬ��
            2)  ���ŵ����������е�20MHz BSS�������ŵ���ͬ��
 �������  : hmac_scan_record_stru *pst_scan_record
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : w00269675
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_obss_check_40mhz_2g(mac_vap_stru *pst_mac_vap,
                                                            hmac_scan_record_stru *pst_scan_record)
{
    oal_uint32                  ul_pri_freq;
    oal_uint32                  ul_sec_freq;
    oal_uint32                  ul_affected_start;
    oal_uint32                  ul_affected_end;

    oal_uint32                  ul_pri;
    oal_uint32                  ul_sec;
    oal_uint32                  ul_sec_chan, ul_pri_chan;

    hmac_bss_mgmt_stru          *pst_bss_mgmt;
    mac_bss_dscr_stru           *pst_bss_dscr;
    hmac_scanned_bss_info       *pst_scanned_bss;
    oal_dlist_head_stru         *pst_entry;

    /* ��ȡ���ŵ������ŵ�����Ƶ�� */
    ul_pri_freq = (oal_int32)g_ast_freq_map_2g[pst_mac_vap->st_channel.uc_chan_number - 1].us_freq;//2412 + (pst_mac_vap->st_channel.uc_chan_number - 1) * 5;

    if (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth)
    {
        ul_sec_freq = ul_pri_freq + 20;
    }
    else if (WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth)
    {
        ul_sec_freq = ul_pri_freq - 20;
    }
    else
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_check_40mhz_2g:en_bandwidth = %d not need obss\n",
                        pst_mac_vap->st_channel.en_bandwidth);
        return OAL_TRUE;
    }

    /* 2.4G������,��ⷶΧ��40MHz��������Ƶ��Ϊ����,���Ҹ�25MHZ */
    ul_affected_start   = ((ul_pri_freq + ul_sec_freq) >> 1) - 25;
    ul_affected_end     = ((ul_pri_freq + ul_sec_freq) >> 1) + 25;

    OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_check_40mhz_2g:40 MHz affected channel range: [%d, %d] MHz",
                    ul_affected_start, ul_affected_end);

    /* ��ȡɨ�����Ĺ���ṹ��ַ */
    pst_bss_mgmt = &(pst_scan_record->st_bss_mgmt);

    /* ��ȡ�� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ����ɨ�赽��bss��Ϣ */
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);
        if (OAL_PTR_NULL == pst_bss_dscr)
        {
            OAM_WARNING_LOG0(0,OAM_SF_2040,"{hmac_obss_check_40mhz_2g::pst_bss_dscr is NULL}");
            continue;
        }

        ul_pri = (oal_int32)g_ast_freq_map_2g[pst_bss_dscr->st_channel.uc_chan_number - 1].us_freq;//2412 + (st_chan_result.uc_channel_number - 1) * 5;
        ul_sec = ul_pri;

        OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040, "pst_bss_dscr->st_channel.uc_chan_number = %d, ul_pri = %d\n",
                        pst_bss_dscr->st_channel.uc_chan_number, ul_pri);

        /* ��ȡɨ�赽��BSS���ŵ���Ƶ����Ϣ */
        hmac_get_pri_sec_chan(pst_bss_dscr, &ul_pri_chan, &ul_sec_chan);

        /* ��BSSΪ40MHz����,������ŵ�Ƶ�� */
        if (ul_sec_chan)
        {
            if (ul_sec_chan < ul_pri_chan)
                ul_sec = ul_pri - 20;
            else
                ul_sec = ul_pri + 20;
        }

        if ((ul_pri < ul_affected_start || ul_pri > ul_affected_end) &&
            (ul_sec < ul_affected_start || ul_sec > ul_affected_end))
            continue; /* not within affected channel range */

        /*  */
        if (ul_sec_chan)
        {
            if (ul_pri_freq != ul_pri || ul_sec_freq != ul_sec)
            {
                OAM_INFO_LOG4(0, OAM_SF_2040, "hmac_obss_check_40mhz_2g:40 MHz pri/sec <%d, %d >mismatch with BSS <%d, %d>\n",
                                ul_pri_freq, ul_sec_freq, ul_pri, ul_sec);
                /* ����� */
                oal_spin_unlock(&(pst_bss_mgmt->st_lock));
                return OAL_FALSE;
            }
        }
    }

    /* ����� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_obss_check_40mhz_5g
 ��������  : ��5G 40MHz����������д���:
            1)  ���APҪ��5GƵ���Ͻ���һ��20/40MHz BSS������5GƵ����һ�����е�20/40M BSSռ����ͬ�������ŵ��Ļ���
                ��һ��Ҫ��֤�½�����20/40MHz BSS�����ŵ��ʹ��ŵ������е�BSS�����ŵ��ʹ��ŵ���ƥ�䡣����Ѿ�����
                �������߸����20/40M BSS�������ǵ����ŵ�����ŵ�����ƥ�䣬��AP���Բ������Ƶ�ѡ�����κ�һ�����е�
                BSS��ƥ������ŵ�����ŵ�;
            2)  Э�齨��AP��Ҫ����һ�����ŵ������е�20MHz BSSռ�õ�20/40MHz BSS����������Э��Ҳ����AP��Ҫ������
                ��20/40MHz BSS�Ĵ��ŵ��Ͻ���һ��20MHz BSS��
 �������  : hmac_scan_record_stru *pst_scan_record
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��8��
    ��    ��   : w00269675
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 hmac_obss_check_40mhz_5g(mac_vap_stru *pst_mac_vap,
                                                            hmac_scan_record_stru *pst_scan_record)
{
    oal_uint32                  ul_pri_chan;
    oal_uint32                  ul_sec_chan;
    oal_uint32                  ul_pri_bss;
    oal_uint32                  ul_sec_bss;
    oal_uint32                  ul_bss_pri_chan;
    oal_uint32                  ul_bss_sec_chan;
    oal_uint8                   uc_match;
    hmac_bss_mgmt_stru          *pst_bss_mgmt;
    mac_bss_dscr_stru           *pst_bss_dscr;
    hmac_scanned_bss_info       *pst_scanned_bss;
    oal_dlist_head_stru         *pst_entry;

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_check_40mhz_5g:pst_mac_vap->st_channel.uc_chan_number = %d\n", pst_mac_vap->st_channel.uc_chan_number);

    /* ��ȡ���ŵ��ʹ��ŵ� */
    ul_pri_chan = pst_mac_vap->st_channel.uc_chan_number;
    if (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth)
    {
        ul_sec_chan = ul_pri_chan + 4;
    }
    else if (WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth)
    {
        ul_sec_chan = ul_pri_chan - 4;
    }
    else
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_check_40mhz_5g: en_bandwidth = %d not need obss scan",
                        pst_mac_vap->st_channel.en_bandwidth);
        return OAL_TRUE;
    }

    /* ��ȡɨ�����Ĺ���ṹ��ַ */
    pst_bss_mgmt = &(pst_scan_record->st_bss_mgmt);

    /* ��ȡ�� */
    oal_spin_lock(&(pst_bss_mgmt->st_lock));

    /* ���ڴ��ŵ���⵽Beacon, �������ŵ���û��, ����Ҫ���������ŵ� */
    ul_pri_bss = ul_sec_bss = 0;
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);

        if (OAL_PTR_NULL == pst_bss_dscr)
        {
            OAM_WARNING_LOG0(0,OAM_SF_2040,"{hmac_obss_check_40mhz_5g::pst_bss_dscr is NULL}");
            continue;
        }

        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_check_40mhz_5g:bss uc_channel_number = %d\n", pst_bss_dscr->st_channel.uc_chan_number);
        if (pst_bss_dscr->st_channel.uc_chan_number == ul_pri_chan)
            ul_pri_bss++;
        else if (pst_bss_dscr->st_channel.uc_chan_number == ul_sec_chan)
            ul_sec_bss++;
    }

    if (ul_sec_bss && !ul_pri_bss)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_check_40mhz_5g:Switch own primary and secondary channel \
                        to get secondary channel with no Beacons from other BSSes\n");

        hmac_switch_pri_sec(pst_mac_vap);

        /* �˴����ν������ֱ�ӷ��ؼ���, ��hostapd-2.4.0�汾�޸� */
		/* �ͷ��� */
        oal_spin_unlock(&(pst_bss_mgmt->st_lock));
	    return OAL_TRUE;
    }

    /*
     * Match PRI/SEC channel with any existing HT40 BSS on the same
     * channels that we are about to use (if already mixed order in
     * existing BSSes, use own preference).
     */
    uc_match = OAL_FALSE;
    OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
    {
        pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
        pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);
        if (OAL_PTR_NULL == pst_bss_dscr)
        {
            OAM_WARNING_LOG0(0,OAM_SF_2040,"{hmac_obss_check_40mhz_5g::pst_bss_dscr is NULL}");
            continue;
        }

        hmac_get_pri_sec_chan(pst_bss_dscr, &ul_bss_pri_chan, &ul_bss_sec_chan);
        if (ul_pri_chan == ul_bss_pri_chan &&
            ul_sec_chan == ul_bss_sec_chan) {
            uc_match = OAL_TRUE;
            break;
        }
    }

    if (!uc_match) {
        OAL_DLIST_SEARCH_FOR_EACH(pst_entry, &(pst_bss_mgmt->st_bss_list_head))
        {
            pst_scanned_bss = OAL_DLIST_GET_ENTRY(pst_entry, hmac_scanned_bss_info, st_dlist_head);
            pst_bss_dscr    = &(pst_scanned_bss->st_bss_dscr_info);
            if (OAL_PTR_NULL == pst_bss_dscr)
            {
                OAM_WARNING_LOG0(0,OAM_SF_2040,"{hmac_obss_check_40mhz_5g::pst_bss_dscr is NULL}");
                continue;
            }

            hmac_get_pri_sec_chan(pst_bss_dscr, &ul_bss_pri_chan, &ul_bss_sec_chan);

            if ((ul_pri_chan == ul_bss_sec_chan) && (ul_sec_chan == ul_bss_pri_chan))
            {
                OAM_INFO_LOG0(0, OAM_SF_2040, "hmac_obss_check_40mhz_5g:switch own primary and secondary channel due to BSS overlap with\n");

                hmac_switch_pri_sec(pst_mac_vap);
                break;
            }
        }
    }

    OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_check_40mhz_5g:After check, pst_mac_vap->st_channel.uc_chan_number = %d\n", pst_mac_vap->st_channel.uc_chan_number);

    /* ����� */
    oal_spin_unlock(&(pst_bss_mgmt->st_lock));

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : hmac_obss_init_scan_hook
 ��������  : ACSδʹ��ʱ��OBSS��Ҫ���н����ж�
 �������  : hmac_scan_record_stru   *pst_scan_record
             hmac_device_stru        *pst_dev
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��2��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_obss_init_scan_hook(hmac_scan_record_stru   *pst_scan_record,
                                     hmac_device_stru        *pst_dev)
{
    /*
    TODO: ACSδ���У���Ҫ����ɨ��������OBSS�������ж�
    1����ǰVAP���ŵ���ΪĿ���ŵ�
    2���ж�֮������Ҫ����VAP���ŵ��ʹ���
    */
    oal_uint8                           uc_idx;
    oal_bool_enum_uint8                 en_bandwidth_40MHz = OAL_FALSE;
    oal_bool_enum_uint8                 en_2g_first_vap_bandwidth_40MHz = OAL_FALSE;
    mac_vap_stru                        *pst_mac_vap;
    oal_uint8                           uc_2g_check_band = OAL_FALSE;
    oal_uint8                           uc_5g_check_band = OAL_FALSE;
    oal_uint8                           uc_5g_first_vap_chan_number = 0;
    wlan_channel_bandwidth_enum_uint8   en_5g_first_vap_bandwidth = WLAN_BAND_WIDTH_20M;

    OAM_WARNING_LOG0(0, OAM_SF_ACS, "hmac_obss_init_scan_hook run\n");

    /* ����ÿ��vap,����ŵ��ʹ��� */
    for(uc_idx = 0; uc_idx < pst_dev->pst_device_base_info->uc_vap_num; uc_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_dev->pst_device_base_info->auc_vap_id[uc_idx]);

        if (pst_mac_vap && WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_init_scan_hook:original channel=%d, bandwidth=%d.\n",
                pst_mac_vap->st_channel.uc_chan_number, pst_mac_vap->st_channel.en_bandwidth);

            if (WLAN_BAND_2G == pst_mac_vap->st_channel.en_band)
            {
                if (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth ||
                        WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth)
                {
                    /* ֻ����һ��vap������ĸ����һ��vap�Ĵ�����ŵ� */
                    if (OAL_FALSE == uc_2g_check_band)
                    {
                        /* 2G vap 20/40������ */
                        en_bandwidth_40MHz = hmac_obss_check_40mhz_2g(pst_mac_vap, pst_scan_record);

                        OAM_INFO_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_init_scan_hook:2.4G first vap, en_bandwidth_40MHz=%d\n", en_bandwidth_40MHz);
                        uc_2g_check_band = OAL_TRUE;
                        en_2g_first_vap_bandwidth_40MHz = en_bandwidth_40MHz;
                    }
                    else
                    {
                        /* ��һ��vap������֮��,������ͬƵ��vap�ŵ��ʹ��������һ�� */
                        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_init_scan_hook:follow bandwidth of first 2g vap.\n");
                        en_bandwidth_40MHz = en_2g_first_vap_bandwidth_40MHz;
                    }
                }

                /* ���ô��� */
                if (OAL_FALSE == en_bandwidth_40MHz)
                {
                    OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_init_scan_hook:cann't set 40MHz bandwidth,change to 20MHz.\n");
                    pst_mac_vap->st_channel.en_bandwidth = WLAN_BAND_WIDTH_20M;
                }
            }
            else if (WLAN_BAND_5G == pst_mac_vap->st_channel.en_band)
            {
                if (WLAN_BAND_WIDTH_40PLUS == pst_mac_vap->st_channel.en_bandwidth ||
                        WLAN_BAND_WIDTH_40MINUS == pst_mac_vap->st_channel.en_bandwidth)
                {
                    if (OAL_FALSE == uc_5g_check_band)
                    {
                        /* 5G vap 20/40������ */
                        en_bandwidth_40MHz = hmac_obss_check_40mhz_5g(pst_mac_vap, pst_scan_record);
                        uc_5g_check_band = OAL_TRUE;
                        uc_5g_first_vap_chan_number = pst_mac_vap->st_channel.uc_chan_number;
                        en_5g_first_vap_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
                    }
                    else
                    {
                        /* ��һ��vap������֮��,������ͬƵ��vap�ŵ��ʹ��������һ�� */
                        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_init_scan_hook:follow bandwidth of first 5g vap.\n");
                        pst_mac_vap->st_channel.uc_chan_number = uc_5g_first_vap_chan_number;
                        pst_mac_vap->st_channel.en_bandwidth = en_5g_first_vap_bandwidth;
                    }
                }
            }
            else
            {
                OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_init_scan_hook: en_band = %d not support!",
                            pst_mac_vap->st_channel.en_band);
                continue;
            }

            /* ��¼�ŵ��ʹ��� */
            pst_dev->ast_best_channel[pst_mac_vap->st_channel.en_band].uc_chan_number = pst_mac_vap->st_channel.uc_chan_number;
            pst_dev->ast_best_channel[pst_mac_vap->st_channel.en_band].en_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
            pst_dev->pst_device_base_info->uc_max_channel = pst_mac_vap->st_channel.uc_chan_number;
            pst_mac_vap->st_ch_switch_info.en_user_pref_bandwidth = pst_mac_vap->st_channel.en_bandwidth;
            OAM_INFO_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_2040, "hmac_obss_init_scan_hook:After adjust, channel=%d, bandwidth=%d.\n",
                            pst_mac_vap->st_channel.uc_chan_number, pst_mac_vap->st_channel.en_bandwidth);
        }
    }

    return OAL_SUCC;
}
#endif

#if defined(_PRE_SUPPORT_ACS) || defined(_PRE_WLAN_FEATURE_DFS) || defined(_PRE_WLAN_FEATURE_20_40_80_COEXIST)
/*****************************************************************************
 �� �� ��  : hmac_device_in_init_scan
 ��������  : ��ȡ����ɨ��״̬
 �������  : mac_device_stru *pst_mac_device

 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
             OAL_FALSE:��ʾ������ɨ��״̬
             OAL_TRUE: ��ʾ����ɨ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : w00269675
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_device_in_init_scan(mac_device_stru *pst_mac_device)
{
    hmac_device_stru    *pst_hmac_device = OAL_PTR_NULL;

    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_device->uc_device_id);

    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "hmac_res_get_mac_dev:pst_hmac_device is null\n");
        return OAL_FALSE;
    }
    else
    {
        return pst_hmac_device->en_in_init_scan;
    }

}

/*****************************************************************************
 �� �� ��  : hmac_need_init_scan
 ��������  : �жϵ��õ��Ƿ���Ҫ���г�ʼ�ŵ����
 �������  : mac_device_stru *pst_mac_device
             mac_try_init_scan_type en_type
 �������  : ��
 �� �� ֵ  : mac_need_init_scan_res_enum_uint8
             ��������:
             1������Ҫ����ɨ�裬�������̼�������
             2����Ҫ����ɨ�裬����Ҫ���Ͻ���
             3��ɨ������У�����Ҫ����ɨ�裬��������������Ҫ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
mac_need_init_scan_res_enum_uint8 hmac_need_init_scan(hmac_device_stru *pst_hmac_device, mac_vap_stru *pst_in_mac_vap, mac_try_init_scan_type en_type)
{
    mac_need_init_scan_res_enum_uint8 en_result = MAC_INIT_SCAN_NOT_NEED;
    mac_device_stru    *pst_mac_device = pst_hmac_device->pst_device_base_info;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_need_init_scan::pst_device_base_info null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    {
        mac_vap_stru *pst_main_sta = mac_find_main_proxysta(pst_mac_device);

        // proxystaģʽ�½�����������½��г�ʼ�ŵ�ѡ��
        // 1��main sta������
        // 2��main sta���ڣ�������״̬ΪINIT
        if (!(!pst_main_sta || (pst_main_sta && pst_main_sta->en_vap_state == MAC_VAP_STATE_INIT)))
        {
            return MAC_INIT_SCAN_NOT_NEED;
        }
    }
#endif
    if (pst_in_mac_vap->en_vap_mode != WLAN_VAP_MODE_BSS_AP && pst_in_mac_vap->en_vap_mode != WLAN_VAP_MODE_CONFIG)
    {
        return MAC_INIT_SCAN_NOT_NEED;
    }

#ifdef _PRE_WLAN_FEATURE_DBAC
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    if (mac_is_dbac_enabled(pst_mac_device) && en_type != MAC_TRY_INIT_SCAN_START_DBAC)
    {
        return MAC_INIT_SCAN_NOT_NEED;
    }
#endif
#endif

    if (MAC_TRY_INIT_SCAN_VAP_UP == en_type && !pst_hmac_device->en_start_via_priv)
    {
        return  MAC_INIT_SCAN_NOT_NEED;
    }

    if(pst_hmac_device->en_in_init_scan)
    {
        return MAC_TRY_INIT_SCAN_RESCAN == en_type ? MAC_INIT_SCAN_NOT_NEED : MAC_INIT_SCAN_IN_SCAN;
    }

#ifdef _PRE_SUPPORT_ACS
    en_result |=  ((mac_get_acs_switch(pst_mac_device) == MAC_ACS_SW_INIT
                  || mac_get_acs_switch(pst_mac_device) == MAC_ACS_SW_BOTH ? OAL_TRUE : OAL_FALSE));
    if (MAC_TRY_INIT_SCAN_RESCAN == en_type)
    {
        return en_result;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_DFS
    /*lint -e514*/
    en_result |= mac_dfs_get_dfs_enable(pst_mac_device) && mac_dfs_get_cac_enable(pst_hmac_device->pst_device_base_info);
    /*lint +e514*/

#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    en_result |= mac_get_2040bss_switch(pst_mac_device);
#endif


    return en_result;

}

/******************************************************************************
 �� �� ��  : hmac_init_scan_timeout
 ��������  : ���ճ�ʼ�ŵ���ʱ������ǿ����������VAP
 �������  : void *p_arg
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��27��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_init_scan_timeout(void *p_arg)
{
    hmac_device_stru *pst_dev = (hmac_device_stru *)p_arg;

    if (!pst_dev->en_init_scan)
    {
        return OAL_SUCC;
    }

    pst_dev->en_init_scan      = OAL_FALSE;
    pst_dev->en_in_init_scan   = OAL_FALSE;
    hmac_start_all_bss_of_device(pst_dev);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_init_scan_cancel_timer
 ��������  : ���ɨ�賬ʱ��ʱ��
 �������  : hmac_device_stru *pst_hmac_dev
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_init_scan_cancel_timer(hmac_device_stru *pst_hmac_dev)
{
    if (pst_hmac_dev && pst_hmac_dev->st_scan_mgmt.st_init_scan_timeout.en_is_enabled)
    {
        /* �رճ�ʱ��ʱ�� */
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_hmac_dev->st_scan_mgmt.st_init_scan_timeout);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_init_scan_cb
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��24��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_init_scan_cb(void *p_scan_record)
{
    hmac_scan_record_stru           *pst_scan_record = (hmac_scan_record_stru *)p_scan_record;
    oal_uint8                        uc_device_id    = pst_scan_record->uc_device_id;
    hmac_device_stru                 *pst_hmac_dev    = hmac_res_get_mac_dev(uc_device_id);
    mac_device_stru                  *pst_mac_dev;

    OAM_WARNING_LOG0(0, OAM_SF_ACS, "{hmac_init_scan_cb called}");

    if (OAL_PTR_NULL == pst_hmac_dev)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ACS, "{hmac_init_scan_cb:pst_hmac_dev=NULL, device_id=%d}", uc_device_id);
        return;
    }

    pst_mac_dev = pst_hmac_dev->pst_device_base_info;
    if (OAL_PTR_NULL == pst_hmac_dev || OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ACS, "{hmac_init_scan_cb:pst_mac_dev=NULL, device_id=%d}", uc_device_id);
        return;
    }

#ifdef _PRE_SUPPORT_ACS
    if (MAC_ACS_SW_INIT == mac_get_acs_switch(pst_mac_dev) || MAC_ACS_SW_BOTH == mac_get_acs_switch(pst_mac_dev))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ACS, "acs  enable, post and return\n");
        /* ��ACS�������У���ȴ�ACS APP������Ӧ��� */
        if(OAL_SUCC == hmac_acs_init_scan_hook(pst_scan_record, pst_hmac_dev))
        {
            return;
        }
    }
#endif

    OAM_WARNING_LOG0(0, OAM_SF_ACS, "acs not enable, cancel timer\n");
    /* ACSδִ�У���ʱ�������˽��� */
    hmac_init_scan_cancel_timer(pst_hmac_dev);

    /* ��ACSδִ�л���ִ��ʧ�ܣ�����ִ�к������� */
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    if (mac_get_2040bss_switch(pst_mac_dev))
    {
        hmac_obss_init_scan_hook(pst_scan_record, pst_hmac_dev);
    }
#endif

  OAM_WARNING_LOG3(0, OAM_SF_ACS, "<<< rsp=5:scan report ch=%d bss=%d init=%d\n", pst_scan_record->uc_chan_numbers,
                    pst_scan_record->st_bss_mgmt.ul_bss_num, pst_hmac_dev->en_init_scan);
#ifdef _PRE_WLAN_FEATURE_DFS
    if (mac_dfs_get_dfs_enable(pst_mac_dev))
    {
        /* ���ɹ���ʼ��CAC�����Ѿ���ʼCAC�����أ���CAC��ʱ��������VAP START */
        if(OAL_SUCC == hmac_dfs_init_scan_hook(pst_scan_record, pst_hmac_dev))
        {
            return;
        }
    }
#endif

    /* ACSδ���С�DFSδ���У�ֱ������BSS */
    hmac_init_scan_timeout(pst_hmac_dev);
}

/*****************************************************************************
 �� �� ��  : dmac_acs_do_scan
 ��������  : ���ղ�����APP��ɨ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_init_scan_do(hmac_device_stru *pst_hmac_dev, mac_vap_stru *pst_mac_vap, mac_init_scan_req_stru *pst_cmd)
{
    oal_uint8                           uc_idx, uc_cnt;
    mac_scan_req_stru                   st_scan_req;
    wlan_channel_band_enum_uint8        en_band;
    wlan_channel_bandwidth_enum_uint8   en_bandwidth;
    oal_uint32                          ul_ret = OAL_FAIL;
    hmac_vap_stru                      *pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);

    if(pst_hmac_vap == OAL_PTR_NULL)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ACS, "{hmac_init_scan_do:get hmac vap=NULL, vapid=%d}", pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }

    OAL_MEMZERO(&st_scan_req, OAL_SIZEOF(st_scan_req));
    st_scan_req.en_scan_mode  = pst_cmd->auc_arg[0];
    st_scan_req.en_scan_type  = pst_cmd->auc_arg[1];
    st_scan_req.uc_scan_func  = pst_cmd->auc_arg[2];
    st_scan_req.en_bss_type   = WLAN_MIB_DESIRED_BSSTYPE_INFRA;
    st_scan_req.uc_bssid_num  = 0;
    st_scan_req.uc_ssid_num   = 0;

    st_scan_req.uc_max_scan_count_per_channel           = 1;
    st_scan_req.uc_max_send_probe_req_count_per_channel = st_scan_req.en_scan_mode == WLAN_SCAN_MODE_FOREGROUND ? 2 : 1;

    st_scan_req.us_scan_time        = st_scan_req.en_scan_mode == WLAN_SCAN_MODE_FOREGROUND ? 120 : 30;
    st_scan_req.uc_probe_delay      = 0;
    st_scan_req.uc_vap_id           = pst_mac_vap->uc_vap_id; /* ��ʵ�Ǹ�device�µ�vap_id[0] */
    st_scan_req.p_fn_cb             = hmac_init_scan_cb;

    st_scan_req.uc_channel_nums     = 0;        /* �ŵ��б����ŵ��ĸ��� */
    uc_cnt = 0;
    for (uc_idx = 0; uc_idx < pst_cmd->ul_cmd_len; uc_idx += 2)
    {
        en_band      = pst_cmd->auc_data[uc_idx] & 0X0F;
        en_bandwidth = (pst_cmd->auc_data[uc_idx] >> 4) & 0x0F;
        if (OAL_SUCC != mac_is_channel_num_valid(en_band, pst_cmd->auc_data[uc_idx+1]))
        {
            OAM_WARNING_LOG3(0, OAM_SF_ACS, "{hmac_init_scan_do:invalid channel number, ch=%d, band=%d bw=%d}",
                                        pst_cmd->auc_data[uc_idx+1], en_band, en_bandwidth);
            OAL_IO_PRINT("{hmac_init_scan_do:invalid channel number, ch=%d, band=%d bw=%d}\n",
                                        pst_cmd->auc_data[uc_idx+1], en_band, en_bandwidth);

            continue;
        }

        st_scan_req.ast_channel_list[uc_cnt].uc_chan_number = pst_cmd->auc_data[uc_idx + 1];
        st_scan_req.ast_channel_list[uc_cnt].en_band        = en_band;
        st_scan_req.ast_channel_list[uc_cnt].en_bandwidth   = en_bandwidth;
        ul_ret = mac_get_channel_idx_from_num(st_scan_req.ast_channel_list[uc_cnt].en_band,
                                     st_scan_req.ast_channel_list[uc_cnt].uc_chan_number,
                                    &st_scan_req.ast_channel_list[uc_cnt].uc_idx);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG2(0, OAM_SF_ACS, "{hmac_init_scan_do:mac_get_channel_idx_from_num failed en_band:[%d],chan_number:[%d]}",
                st_scan_req.ast_channel_list[uc_cnt].en_band,st_scan_req.ast_channel_list[uc_cnt].uc_chan_number);
        }
        uc_cnt++;
    }

    OAL_IO_PRINT(">>> got=5:do scan mode=%d func=0x%x type=%d ch_cnt=%d\n",
        st_scan_req.en_scan_mode,
        st_scan_req.uc_scan_func,st_scan_req.en_scan_type, uc_cnt);

    if (uc_cnt != 0)
    {
        st_scan_req.uc_channel_nums = uc_cnt;

        /* ֱ�ӵ���ɨ��ģ��ɨ���������� */
        ul_ret = hmac_scan_proc_scan_req_event(pst_hmac_vap, &st_scan_req);
        if(OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "hmac_init_scan_do:hmac_scan_add_req failed, ret=%d", ul_ret);
        }
    }
    else
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "hmac_init_scan_do:no valid channel found, not scan");
    }

    return ul_ret;
}
/*****************************************************************************
 �� �� ��  : hmac_init_scan_skip_channel
 ��������  : ��ʼɨ��ʱ����������Ҫɨ����ŵ�
 �������  : hmac_device_stru              *pst_hmac_dev
             wlan_channel_band_enum_uint8   en_band
             oal_uint8                      uc_idx
 �������  : ��
 �� �� ֵ  : oal_bool_enum_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��13��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_init_scan_skip_channel(hmac_device_stru              *pst_hmac_dev,
                                                wlan_channel_band_enum_uint8   en_band,
                                                oal_uint8                      uc_idx)
{
    /* skip any illegal channel */
    if (OAL_SUCC != mac_is_channel_idx_valid(en_band, uc_idx))
    {
        return OAL_TRUE;
    }
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_dev->pst_device_base_info))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_init_scan_skip_channel::pst_device_base_info null!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* on 1151, scan all channels when dbac enabled */
#ifdef _PRE_WLAN_FEATURE_DBAC
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    if (mac_is_dbac_enabled(pst_hmac_dev->pst_device_base_info))
    {
        return OAL_FALSE;
    }
#endif
#endif

    if (pst_hmac_dev->pst_device_base_info
     && pst_hmac_dev->pst_device_base_info->en_max_band != en_band)
    {
        return  OAL_TRUE;
    }

    return OAL_FALSE;
}
/*****************************************************************************
 �� �� ��  : hmac_init_scan_process
 ��������  : HMAC�������еĳ�ʼ�ŵ�ɨ�躯��
 �������  : mac_device_stru *pst_mac_dev
             mac_vap_stru *pst_mac_vap
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��27��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_init_scan_process(hmac_device_stru *pst_hmac_dev, mac_vap_stru *pst_mac_vap, mac_scan_op_enum_uint8 en_op)
{
    oal_uint8         ast_buf[OAL_SIZEOF(mac_acs_cmd_stru) - 4 + WLAN_MAX_CHANNEL_NUM * 2];
    oal_uint8         uc_idx;
    oal_uint8        *puc_dat, uc_tot, uc_chan_num;
    oal_uint32        ul_ret;

    mac_init_scan_req_stru *pst_cmd = (mac_init_scan_req_stru *)ast_buf;

    puc_dat = pst_cmd->auc_data;

    pst_hmac_dev->en_init_scan    = (en_op ==  MAC_SCAN_OP_INIT_SCAN) ? OAL_TRUE : OAL_FALSE;
    pst_hmac_dev->en_in_init_scan = OAL_TRUE;

    pst_cmd->uc_cmd     = 5; //DMAC_ACS_CMD_DO_SCAN;
    pst_cmd->auc_arg[0] =   (en_op ==  MAC_SCAN_OP_FG_SCAN_ONLY
                          || en_op ==  MAC_SCAN_OP_INIT_SCAN) ? WLAN_SCAN_MODE_FOREGROUND : WLAN_SCAN_MODE_BACKGROUND_AP;

    pst_cmd->auc_arg[1] = WLAN_SCAN_TYPE_ACTIVE;
    pst_cmd->auc_arg[2] = MAC_SCAN_FUNC_MEAS | MAC_SCAN_FUNC_STATS | MAC_SCAN_FUNC_BSS;
    pst_cmd->ul_cmd_cnt = 0;

    uc_tot = 0;
    for (uc_idx = 0; uc_idx < MAC_CHANNEL_FREQ_2_BUTT; uc_idx++)
    {
        if(!hmac_init_scan_skip_channel(pst_hmac_dev, WLAN_BAND_2G, uc_idx))
        {
            mac_get_channel_num_from_idx(WLAN_BAND_2G, uc_idx, &uc_chan_num);
            *puc_dat++ = ((WLAN_BAND_WIDTH_20M) << 4) | WLAN_BAND_2G;
            *puc_dat++ = uc_chan_num;
             uc_tot++;
        }
    }
    for (uc_idx = 0; uc_idx < MAC_CHANNEL_FREQ_5_BUTT; uc_idx++)
    {
        if(!hmac_init_scan_skip_channel(pst_hmac_dev, WLAN_BAND_5G, uc_idx))
        {
            mac_get_channel_num_from_idx(WLAN_BAND_5G, uc_idx, &uc_chan_num);
            *puc_dat++ = ((WLAN_BAND_WIDTH_20M) << 4) | WLAN_BAND_5G;
            *puc_dat++ = uc_chan_num;
             uc_tot++;
        }
    }

    pst_cmd->ul_cmd_len = uc_tot * 2;

    /* best�ŵ����Ϊ0����start bss��Ϊ�Ϸ����ж����� */
    if(pst_hmac_dev->en_init_scan)
    {
        oal_memset(pst_hmac_dev->ast_best_channel, 0, OAL_SIZEOF(pst_hmac_dev->ast_best_channel));
    }

    /* ������ʱ��, ��ʱ��ǿ������BSS: ����ʱ�����ɨ��ʱ����APP����ʱ�� */
    {
        FRW_TIMER_CREATE_TIMER(&pst_hmac_dev->st_scan_mgmt.st_init_scan_timeout,
                               hmac_init_scan_timeout,
                               HMAC_INIT_SCAN_TIMEOUT_MS,
                               pst_hmac_dev,
                               OAL_FALSE,
                               OAM_MODULE_ID_HMAC,
                               pst_hmac_dev->pst_device_base_info->ul_core_id);
    }

    ul_ret = hmac_init_scan_do(pst_hmac_dev, pst_mac_vap, pst_cmd);
    if(OAL_SUCC != ul_ret)
    {
        pst_hmac_dev->en_init_scan    = OAL_FALSE;
        pst_hmac_dev->en_in_init_scan = OAL_FALSE;
    }

    return ul_ret;
}
/*****************************************************************************
 �� �� ��  : hmac_init_scan_try
 ��������  : ���Խ��г�ʼ�ŵ����
 �������  : mac_device_stru *pst_mac_device
             mac_vap_stru *pst_mac_vap
             oal_bool_enum_uint8 en_priv_called
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_init_scan_try(mac_device_stru *pst_mac_device, mac_vap_stru *pst_in_mac_vap, mac_try_init_scan_type en_type)
{
    oal_uint8        uc_idx;
    mac_vap_stru    *pst_mac_vap, *pst_mac_vap_scan = NULL;
    hmac_vap_stru   *pst_hmac_vap;
    oal_uint8        en_scan_type;
    hmac_device_stru*pst_hmac_device = hmac_res_get_mac_dev(pst_mac_device->uc_device_id);
    oal_bool_enum_uint8  en_need_do_init_scan = OAL_FALSE;

    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_init_scan_try:mac_res_get_hmac_vap failed. device_id:%d.}",pst_mac_device->uc_device_id);
        return OAL_FAIL;
    }
    en_scan_type = hmac_need_init_scan(pst_hmac_device, pst_in_mac_vap, en_type);
    if(en_scan_type == MAC_INIT_SCAN_NOT_NEED)
    {
        return OAL_FAIL;
    }
    else if(en_scan_type == MAC_INIT_SCAN_IN_SCAN)
    {
        OAL_IO_PRINT("just in init scan\n");

        mac_vap_init_rates(pst_in_mac_vap);
        pst_hmac_vap = mac_res_get_hmac_vap(pst_in_mac_vap->uc_vap_id);
        if (OAL_PTR_NULL == pst_hmac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_init_scan_try:mac_res_get_hmac_vap failed vap_id:%d.}",pst_in_mac_vap->uc_vap_id);
            return OAL_FAIL;
        }
        if (pst_hmac_vap->st_vap_base_info.en_vap_state == MAC_VAP_STATE_UP)
        {
            hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_AP_WAIT_START);
        }

        return OAL_SUCC;
    }
    else
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "hmac_init_scan_try: need init scan");
    }

    for (uc_idx = 0; uc_idx < pst_hmac_device->pst_device_base_info->uc_vap_num; uc_idx++)
    {
        pst_mac_vap = mac_res_get_mac_vap(pst_hmac_device->pst_device_base_info->auc_vap_id[uc_idx]);
        if (!pst_mac_vap)
        {
            continue;
        }

        if(WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            mac_vap_init_rates(pst_mac_vap);

            /* ǿ������AP��״̬��Ϊ WAIT_START����Ϊ��Ҫִ�г�ʼ�ŵ���� */
            pst_hmac_vap = mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
            if (OAL_PTR_NULL == pst_hmac_vap)
            {
                OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{hmac_init_scan_try::need init scan fail.vap_id = %u}",pst_mac_vap->uc_vap_id);
                continue;
            }
            switch (pst_hmac_vap->st_vap_base_info.en_vap_state)
            {
                case MAC_VAP_STATE_UP :
                case MAC_VAP_STATE_PAUSE : // dbac
                        hmac_fsm_change_state(pst_hmac_vap, MAC_VAP_STATE_AP_WAIT_START);
                        // no break here!
                case MAC_VAP_STATE_AP_WAIT_START :
                        en_need_do_init_scan = OAL_TRUE;
                        pst_mac_vap_scan = pst_mac_vap;
                        break;
                default :
                     break;
            }
        }
    }

    if (en_need_do_init_scan)
    {
        return hmac_init_scan_process(pst_hmac_device, pst_mac_vap_scan, MAC_SCAN_OP_INIT_SCAN);
    }

    return OAL_SUCC;
}

#endif
/*lint -e578*//*lint -e19*/
oal_module_symbol(hmac_scan_find_scanned_bss_dscr_by_index);
oal_module_symbol(hmac_scan_find_scanned_bss_by_bssid);
/*lint -e578*//*lint -e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

