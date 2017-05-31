
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_fbt_main.c
  �� �� ��   : ����
  ��    ��   : luolingzhi
  ��������   : 2015��12��21��
  ����޸�   :
  ��������   : fbt����ʵ��Դ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��12��21��
    ��    ��   : luolingzhi
    �޸�����   : �����ļ�

  2.��    ��   : 2016��1��6��
    ��    ��   : xiexiaoming
    �޸�����   : ����fbt��ֹ���ӹ���

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_HILINK

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "hmac_fbt_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_FBT_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : hmac_config_fbt_set_mode
 ��������  : ���ÿ����л���ģʽ
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             us_len     : ��������
             puc_param  : ����ָ�� 1��ʾ������0��ʾ�ر�
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��21��
    ��    ��   : luolingzhi 00225940
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_config_fbt_set_mode(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{

    hmac_fbt_mgmt_stru      *pst_hmac_fbt_mgmt;
    hmac_vap_stru           *pst_hmac_vap;
    oal_uint8               uc_fbt_cfg_mode = 0;
    oal_uint8               uc_user_index = 0;


    /* ��μ�� */
    if ((OAL_PTR_NULL == pst_mac_vap) || (OAL_PTR_NULL == puc_param))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_device_id, OAM_SF_HILINK, "{hmac_config_fbt_set_mode::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_device_id, OAM_SF_HILINK, "{hmac_config_fbt_set_mode::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (HMAC_FBT_MODE_AC < (*puc_param))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_device_id, OAM_SF_HILINK, "{hmac_config_fbt_set_mode::invalid uc_fbt_cfg_mode=%d.}", uc_fbt_cfg_mode);
        return OAL_FAIL;
    }

    /* ��ȡ�û��·���Ҫ���õ�fbt����ʵ���еĲ��� */
    uc_fbt_cfg_mode = *puc_param;

    /* ��ȡhmac vapʵ���е�fbt����ʵ�� */
    pst_hmac_fbt_mgmt = &(pst_hmac_vap->st_fbt_mgmt);


    /* ���Ҫ���õ�ģʽ��fbg����ʵ���е�ģʽһ�£�
       ��������ֱ�ӷ��أ���������ʾ��Ϣ��*/
    if (uc_fbt_cfg_mode == pst_hmac_fbt_mgmt->uc_fbt_mode)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_device_id, OAM_SF_HILINK, "{hmac_config_fbt_set_mode::uc_fbt_cfg_mode eq pst_hmac_fbt_mgmt->uc_fbt_mode,return.}");
        return OAL_SUCC;
    }

    /* �ر�FBTģʽ��Ҫ����ֹ�����б��������㣻 */
    if (uc_fbt_cfg_mode == HMAC_FBT_MODE_CLOSE)
    {
        for (uc_user_index = 0; uc_user_index < HMAC_FBT_MAX_USER_NUM; uc_user_index++)
        {
            oal_memset(pst_hmac_fbt_mgmt->ast_fbt_disable_connect_user_list + uc_user_index, 0, OAL_SIZEOF(hmac_fbt_disable_user_info_stru));
        }
        pst_hmac_fbt_mgmt->uc_disabled_user_cnt = 0;

    }

    /* ��¼���õ�fbtģʽ��fbt����ʵ���� */
    pst_hmac_fbt_mgmt->uc_fbt_mode = uc_fbt_cfg_mode;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_fbt_scan_report_timeout
 ��������  : �����ǹ����û��ϱ�����
 �������  : hmac_vap_stru *pst_hmac_vap
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��21��
    ��    ��   : luolingzhi 00225940
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_fbt_scan_report_timeout(oal_void *p_arg)
{
    mac_fbt_scan_mgmt_stru     *pst_fbt_scan_mgmt;
    mac_fbt_scan_result_stru   *pst_fbt_scan_result;
    oal_uint8                   uc_user_idx;
    mac_device_stru            *pst_mac_device;
    hmac_fbt_notify_stru        st_fbt_notify;
    hmac_fbt_notify_stru       *pst_fbt_notify;
    hmac_vap_stru              *pst_hmac_vap;

    /* ��μ�� */
    if (OAL_PTR_NULL == p_arg)
    {
        OAM_WARNING_LOG0(0, OAM_SF_HILINK, "{hmac_fbt_scan_report_timeout::p_arg null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)p_arg;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HILINK, "{hmac_fbt_scan_report_timeout::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �Ȼ�ȡdevice id */
    pst_mac_device  = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HILINK, "{hmac_fbt_scan_report_timeout::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡmac deviceʵ���е�fbt scan����ʵ�� */
    pst_fbt_scan_mgmt = &(pst_mac_device->st_fbt_scan_mgmt);

    /* ���û�п���FBT scan ���ܣ���������ֱ�ӷ��� */
    if(HMAC_FBT_SCAN_CLOSE == pst_fbt_scan_mgmt->uc_fbt_scan_enable)
    {
        return OAL_SUCC;
    }

    /* ��� FBT scan�����б��������û���û�д����꣬��������Ĵ��� */
    for (uc_user_idx = 0; uc_user_idx < HMAC_FBT_MAX_USER_NUM; uc_user_idx++)   // HMAC_FBT_MAX_USER_NUM 3 for test
    {
        /* �ҵ�FBT scan��������ʵ�壬��ʼ��FBT scan�����������i=0 */
        pst_fbt_scan_result = &(pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx]);

        if (OAL_TRUE == pst_fbt_scan_result->uc_is_found)
        {
            /* ����ϱ��ṹ�� */
            pst_fbt_notify = &st_fbt_notify;
            oal_memcopy(pst_fbt_notify->auc_user_bssid, pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].auc_user_bssid, WLAN_MAC_ADDR_LEN);
            pst_fbt_notify->uc_user_channel = pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].uc_user_channel;
            pst_fbt_notify->uc_user_rssi = (pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].c_rssi + HMAC_FBT_RSSI_ADJUST_VALUE);
            pst_fbt_notify->en_fbt_notify_type = HMAC_FBT_STA_FOUND;
            oal_memcopy(pst_fbt_notify->auc_user_mac_addr, pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].auc_user_mac_addr, WLAN_MAC_ADDR_LEN);
            pst_fbt_notify->ul_rssi_timestamp = pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].ul_rssi_timestamp;;

            /* �����ϱ��ӿ��ϱ� */
            hmac_fbt_notify(pst_hmac_vap, pst_fbt_notify);
            OAM_INFO_LOG4(pst_mac_device->uc_device_id, OAM_SF_HILINK, "{hmac_fbt_scan_report_timeout::uc_user_idx=%d MAC:0x%x:0x%x:0x%x is found!}",
                                        uc_user_idx,
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].auc_user_mac_addr[3],
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].auc_user_mac_addr[4],
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].auc_user_mac_addr[5]);

            OAM_INFO_LOG4(pst_mac_device->uc_device_id, OAM_SF_HILINK, "{hmac_fbt_scan_report_timeout::bssid MAC:0x%x:0x%x:0x%x:0x%x.}",
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].auc_user_bssid[2],
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].auc_user_bssid[3],
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].auc_user_bssid[4],
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].auc_user_bssid[5]);

            OAM_INFO_LOG4(pst_mac_device->uc_device_id, OAM_SF_HILINK, "{hmac_fbt_scan_report_timeout::channel =%d,c_rssi=%d,ul_rssi_timestamp=%d,ul_total_pkt_cnt=%d.}",
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].uc_user_channel,
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].c_rssi,
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].ul_rssi_timestamp,
                                        pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_idx].ul_total_pkt_cnt);

        }

    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_fbt_start_scan_report_timer
 ��������  : ����FBT�������ǹ����û��Ķ�ʱ�����ö�ʱ��������ʱ�ϱ��ѹ����û��������
 �������  : mac_vap_stru *pst_mac_vap
             oal_uint32 ul_period:�������ö�ʱ��������
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��21��
    ��    ��   : luolingzhi 00225940
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_fbt_start_scan_report_timer(mac_vap_stru *pst_mac_vap, oal_uint32 ul_period)
{
    mac_fbt_scan_mgmt_stru     *pst_fbt_scan_mgmt;
    hmac_vap_stru               *pst_hmac_vap;
    mac_device_stru            *pst_mac_device;

    /* ��μ�� */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_HILINK, "{hmac_fbt_start_monitor_timer::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_hmac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_HILINK, "{hmac_fbt_start_monitor_timer::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HILINK, "{hmac_fbt_start_scan_report_timer::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡmac deviceʵ���е�fbt scan����ʵ�� */
    pst_fbt_scan_mgmt = &(pst_mac_device->st_fbt_scan_mgmt);


    /* ����FBT scan����ϱ���ʱ��*/
    FRW_TIMER_CREATE_TIMER(&pst_fbt_scan_mgmt->st_timer,
                           hmac_fbt_scan_report_timeout,
                           ul_period,
                           pst_hmac_vap,
                           OAL_TRUE,
                           OAM_MODULE_ID_HMAC,
                           pst_mac_vap->ul_core_id);
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_fbt_stop_scan_report_timer
 ��������  : ֹͣFBT�������ǹ����û��Ķ�ʱ��
 �������  : mac_vap_stru *pst_mac_vap
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��21��
    ��    ��   : luolingzhi 00225940
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_fbt_stop_scan_report_timer(mac_vap_stru *pst_mac_vap)
{
    mac_fbt_scan_mgmt_stru     *pst_fbt_scan_mgmt;
    frw_timeout_stru           *pst_timer;
    mac_device_stru            *pst_mac_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HILINK, "{hmac_fbt_stop_scan_report_timer: pst_mac_vap is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HILINK, "{hmac_fbt_stop_scan_report_timer::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡmac vapʵ���е�fbt scan����ʵ�� */
    pst_fbt_scan_mgmt = &(pst_mac_device->st_fbt_scan_mgmt);

    pst_timer = &(pst_fbt_scan_mgmt->st_timer);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_timer))
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_HILINK, "hmac_fbt_stop_scan_report_timer::pst_timer is NULL");
        return OAL_FAIL;
    }

    FRW_TIMER_DESTROY_TIMER(pst_timer);

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : hmac_fbt_start_scan
 ��������  : ���ÿ����л�����δ�����û����ܿ���
 �������  : pst_mac_vap: MAC VAP�ṹ��ָ��
             us_len     : ��������
             puc_param  : ����ָ�� 1��ʾ������0��ʾ�ر�
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��25��
    ��    ��   : luolingzhi 00225940
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_fbt_start_scan(mac_vap_stru *pst_mac_vap)
{

    mac_fbt_scan_mgmt_stru     *pst_fbt_scan_mgmt;
    oal_uint8                   uc_user_index = 0;
    mac_device_stru            *pst_mac_device;

    /* ��μ�� */
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_device_id, OAM_SF_HILINK, "{hmac_fbt_start_scan::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡmac vapʵ���е�fbt scan����ʵ�� */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    pst_fbt_scan_mgmt = &(pst_mac_device->st_fbt_scan_mgmt);


    /* ������ò����ǿ���fbtģʽ����Ҫ�����ϱ�����������ʱ����ע��ص�������
       �����ǹر�fbtģʽ���رն�ʱ����*/
    if (HMAC_FBT_SCAN_OPEN == pst_fbt_scan_mgmt->uc_fbt_scan_enable)
    {
        hmac_fbt_start_scan_report_timer(pst_mac_vap, pst_fbt_scan_mgmt->ul_scan_report_period);
    }
    else
    {
        hmac_fbt_stop_scan_report_timer(pst_mac_vap);

        /* �ر�FBT scanģʽ��Ҫ�������б����㣻*/
        for (uc_user_index = 0; uc_user_index < HMAC_FBT_MAX_USER_NUM; uc_user_index++)
        {
            oal_memset(pst_fbt_scan_mgmt->ast_fbt_scan_user_list + uc_user_index, 0, OAL_SIZEOF(mac_fbt_scan_result_stru));
        }

        /* �ָ�Ĭ��ֵ */
        pst_fbt_scan_mgmt->uc_scan_channel = FBT_DEFAULT_SCAN_CHANNEL;
        pst_fbt_scan_mgmt->ul_scan_interval = FBT_DEFAULT_SCAN_INTERVAL;
        pst_fbt_scan_mgmt->ul_scan_report_period = FBT_DEFAULT_SCAN_REPORT_PERIOD;

    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_fbt_init
 ��������  : ��ʼ��FBT�ĸ��ֲ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��24��
    ��    ��   : luolingzhi 00225940
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_fbt_init(hmac_vap_stru *pst_hmac_vap)
{
    hmac_fbt_mgmt_stru         *pst_hmac_fbt_mgmt;
    mac_fbt_scan_mgmt_stru     *pst_fbt_scan_mgmt;
    mac_device_stru            *pst_mac_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HILINK, "{hmac_fbt_init::pst_hmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_hmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HILINK, "{hmac_fbt_init::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡhmac vapʵ���е�fbt����ʵ�� */
    pst_hmac_fbt_mgmt = &(pst_hmac_vap->st_fbt_mgmt);

    /* ��vap�����fbt����ʵ�����㣬Ȼ���ʼ���л�����ֵΪ-40dbm��fbt����Ϊ�رգ�
    ����ѹ����û���ʱ��Ϊ5s */
    oal_memset(pst_hmac_fbt_mgmt, 0, OAL_SIZEOF(hmac_fbt_mgmt_stru));

    /* Ĭ�Ͽ���hilink fbtģʽ����ͨ������hipriv.sh "wlan0 fbt_set_mode 0|1"���� */
    pst_hmac_fbt_mgmt->uc_fbt_mode = HMAC_FBT_MODE_AC;

    /* ��ȡmac vapʵ���е�fbt scan����ʵ�� */
    pst_fbt_scan_mgmt = &(pst_mac_device->st_fbt_scan_mgmt);

    /* ��vap�����fbt scan����ʵ�����㣬Ȼ��������Ĭ��ֵ  */
    oal_memset(pst_fbt_scan_mgmt, 0, OAL_SIZEOF(mac_fbt_scan_mgmt_stru));
    pst_fbt_scan_mgmt->uc_fbt_scan_enable = HMAC_FBT_SCAN_CLOSE;
    pst_fbt_scan_mgmt->uc_scan_channel = FBT_DEFAULT_SCAN_CHANNEL;
    pst_fbt_scan_mgmt->ul_scan_interval = FBT_DEFAULT_SCAN_INTERVAL;
    pst_fbt_scan_mgmt->ul_scan_report_period = FBT_DEFAULT_SCAN_REPORT_PERIOD;

    return OAL_SUCC;
}



/*****************************************************************************
 �� �� ��  : hmac_fbt_notify
 ��������  :
 �������  : pst_dev_fbt_mgmt            :Fbt���ܹ���ʵ��
             pst_notify                  :Ҫ�ϱ�����Ϣ
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��18��
    ��    ��   : x00226265
    �޸�����   : �����ļ�
  2.��    ��   : 2016��1��20��
    ��    ��   : l00225940
    �޸�����   : hilink�����޸�

*****************************************************************************/

oal_uint32  hmac_fbt_notify(hmac_vap_stru *pst_hmac_vap, hmac_fbt_notify_stru *pst_hmac_fbt_notify)
{

    oal_station_info_stru       st_station_info;
    oal_uint32                  ul_ret;
    oal_net_device_stru        *pst_net_device;
    oal_uint8                   auc_user_addr[WLAN_MAC_ADDR_LEN];

    /* �ж���Σ���Ϊ�գ���ʾ��Ϣ�������� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_vap || OAL_PTR_NULL == pst_hmac_fbt_notify))
    {
        OAM_ERROR_LOG0(0, OAM_SF_HILINK, "{hmac_fbt_notify::null param.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡnet_device*/
    pst_net_device = hmac_vap_get_net_device(pst_hmac_vap->st_vap_base_info.uc_vap_id);
    if (OAL_PTR_NULL == pst_net_device)
    {
        OAM_ERROR_LOG0(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_HILINK, "{hmac_fbt_notify::get net device ptr is null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(auc_user_addr, (oal_uint8 *)pst_hmac_fbt_notify->auc_user_mac_addr, WLAN_MAC_ADDR_LEN);

    /* ����oal_cfg80211_new_sta�ϱ���hostapd��ע����hostapd���յĵط���ϢҪת��EVENT_DETECT_STA_FRAME */
    oal_memset(&st_station_info, 0, OAL_SIZEOF(oal_station_info_stru));

    st_station_info.signal = pst_hmac_fbt_notify->uc_user_rssi;
    st_station_info.filled |=  STATION_INFO_SIGNAL;

    st_station_info.inactive_time = pst_hmac_fbt_notify->ul_rssi_timestamp;
    st_station_info.filled |=  STATION_INFO_INACTIVE_TIME;

    /* �����ں˽ӿڣ��ϱ�STA������� */
    ul_ret = oal_cfg80211_fbt_notify_find_sta(pst_net_device, auc_user_addr, &st_station_info, GFP_ATOMIC);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_HILINK, "{hmac_fbt_notify::oal_cfg80211_fbt_notify_find_sta fail[%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    OAM_INFO_LOG4(pst_hmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_HILINK, "{hmac_fbt_notify::mac[%x:**:**:%x:%x:%x] OK!}\r\n",
                                                                        auc_user_addr[0],
                                                                        auc_user_addr[3],
                                                                        auc_user_addr[4],
                                                                        auc_user_addr[5]);

    return OAL_SUCC;

}





oal_module_symbol(hmac_config_fbt_set_mode);
oal_module_symbol(hmac_fbt_start_scan);

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


