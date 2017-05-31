/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wal_linux_event.c
  �� �� ��   : ����
  ��    ��   : y00184180
  ��������   : 2013��8��26��
  ����޸�   :
  ��������   : linux�������Ľӿں�������װ��Ϣ�����¼������������մ��������������¼���������Ϣ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��8��26��
    ��    ��   : y00184180
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
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "wal_linux_ioctl.h"
#include "wal_main.h"
#include "wal_config.h"




#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_EVENT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : wal_cfg80211_start_req
 ��������  : ��wal���¼�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��4��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 wal_cfg80211_start_req(oal_net_device_stru    *pst_net_dev,
                                void                        *ps_param,
                                oal_uint16                   us_len,
                                wlan_cfgid_enum_uint16       en_wid,
                                oal_bool_enum_uint8          en_need_rsp)
{
    wal_msg_write_stru              st_write_msg;
    wal_msg_stru                   *pst_rsp_msg = OAL_PTR_NULL;
    oal_uint32                      ul_err_code;
    oal_int32                       l_ret;

    if (OAL_PTR_NULL == ps_param )
    {
         OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_req::param is null!}\r\n");
         return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д msg ��Ϣͷ*/
    st_write_msg.en_wid = en_wid;
    st_write_msg.us_len = us_len;

    /* ��д msg ��Ϣ�� */
    if(WAL_MSG_WRITE_MAX_LEN < us_len)
    {
        OAM_ERROR_LOG2(0, OAM_SF_SCAN, "{wal_cfg80211_start_req::us_len %d > WAL_MSG_WRITE_MAX_LEN %d err!}\r\n", us_len, WAL_MSG_WRITE_MAX_LEN);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }
    oal_memcopy(st_write_msg.auc_value, ps_param, us_len);

    /***************************************************************************
           ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                           WAL_MSG_TYPE_WRITE,
                           WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                           (oal_uint8 *)&st_write_msg,
                           en_need_rsp,
                           en_need_rsp ? &pst_rsp_msg : OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_cfg80211_start_req::wal_send_cfg_event return err code %d!}\r\n", l_ret);
        return l_ret;
    }

    if(en_need_rsp && (OAL_PTR_NULL != pst_rsp_msg))
    {
        /* ��ȡ���صĴ����� */
        ul_err_code = wal_check_and_release_msg_resp(pst_rsp_msg);
        if(OAL_SUCC != ul_err_code)
        {
            OAM_WARNING_LOG1(0, OAM_SF_SCAN, "{wal_cfg80211_start_req::wal_send_cfg_event return err code:[%u]}",
                           ul_err_code);
            return -OAL_EFAIL;
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_cfg80211_start_scan
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��30��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��1��4��
    ��    ��   : z00260280
    �޸�����   : �ع�

*****************************************************************************/
oal_uint32  wal_cfg80211_start_scan(oal_net_device_stru *pst_net_dev, mac_cfg80211_scan_param_stru *pst_scan_param)
{
    mac_cfg80211_scan_param_stru    *pst_mac_cfg80211_scan_param;
    oal_uint32                       ul_ret = 0;

    if (OAL_PTR_NULL == pst_scan_param)
    {
         OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_scan::scan failed, null ptr, pst_scan_param = null.}\r\n");
         return OAL_ERR_CODE_PTR_NULL;
    }

    /* �˴�����hmac���ͷ� */
    pst_mac_cfg80211_scan_param = (mac_cfg80211_scan_param_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_cfg80211_scan_param_stru), OAL_FALSE);
    if (NULL == pst_mac_cfg80211_scan_param)
    {
        OAM_ERROR_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_scan::scan failed, alloc scan param memory failed!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(pst_mac_cfg80211_scan_param, pst_scan_param, OAL_SIZEOF(mac_cfg80211_scan_param_stru));

    /* TBD gong: 1.������ָ���ָ��, 2.sizeofָ��  */
    ul_ret = (oal_uint32)wal_cfg80211_start_req(pst_net_dev, &pst_mac_cfg80211_scan_param,
                                    OAL_SIZEOF(pst_mac_cfg80211_scan_param), WLAN_CFGID_CFG80211_START_SCAN, OAL_FALSE);
    if(OAL_SUCC != ul_ret)
    {
        /* �·�ɨ��ʧ�ܣ��ͷ� */
        OAL_MEM_FREE(pst_mac_cfg80211_scan_param, OAL_FALSE);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_cfg80211_start_sched_scan
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_cfg80211_start_sched_scan(oal_net_device_stru *pst_net_dev, mac_pno_scan_stru *pst_pno_scan_info)
{
    mac_pno_scan_stru      *pst_pno_scan_params;
    oal_uint32              ul_ret = 0;
    /* ����pno����ɨ��������˴�����hmac���ͷ� */
    pst_pno_scan_params = (mac_pno_scan_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(mac_pno_scan_stru), OAL_FALSE);
    if (OAL_PTR_NULL == pst_pno_scan_params)
    {
        OAM_WARNING_LOG0(0, OAM_SF_SCAN, "{wal_cfg80211_start_sched_scan::alloc pno scan param memory failed!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    oal_memcopy(pst_pno_scan_params, pst_pno_scan_info, OAL_SIZEOF(mac_pno_scan_stru));

    ul_ret = (oal_uint32)wal_cfg80211_start_req(pst_net_dev, &pst_pno_scan_params,
                                    OAL_SIZEOF(pst_pno_scan_params), WLAN_CFGID_CFG80211_START_SCHED_SCAN, OAL_TRUE);

    if(OAL_SUCC != ul_ret)
    {
        OAL_MEM_FREE(pst_pno_scan_params, OAL_FALSE);
        return ul_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_cfg80211_start_connect
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��30��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  wal_cfg80211_start_connect(oal_net_device_stru *pst_net_dev, mac_cfg80211_connect_param_stru *pst_mac_cfg80211_connect_param)
{
    return wal_cfg80211_start_req(pst_net_dev,
                pst_mac_cfg80211_connect_param,
                OAL_SIZEOF(mac_cfg80211_connect_param_stru),
                WLAN_CFGID_CFG80211_START_CONNECT,
                OAL_TRUE);
}

/*****************************************************************************
 �� �� ��  : wal_cfg80211_start_disconnect
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��30��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  wal_cfg80211_start_disconnect(oal_net_device_stru *pst_net_dev, mac_cfg_kick_user_param_stru *pst_disconnect_param)
{
    /* ע�� ������Ϣδ���������ֱ�ӷ��أ�����WPA_SUPPLICANT�����·���Ϣ����������ȵ�����ʱ���쳣���ѣ����º����·�����Ϣ����Ϊ����ʧ�ܣ�
       Ŀǰ��ȥ�����¼��޸�Ϊ�ȴ���Ϣ������������ϱ������һ�������OAL_FALSE��ΪOAL_TRUE */
    return wal_cfg80211_start_req(pst_net_dev, pst_disconnect_param, OAL_SIZEOF(mac_cfg_kick_user_param_stru), WLAN_CFGID_KICK_USER, OAL_TRUE);
}
#ifdef _PRE_WLAN_FEATURE_HILINK
/*****************************************************************************
 �� �� ��  : wal_cfg80211_fbt_kick_user
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2016��01��19��
    ��    ��   : x00226265
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_int32  wal_cfg80211_fbt_kick_user(oal_net_device_stru *pst_net_dev, mac_cfg_kick_user_param_stru *pst_disconnect_param)
{
    return wal_cfg80211_start_req(pst_net_dev, pst_disconnect_param, OAL_SIZEOF(mac_cfg_kick_user_param_stru), WLAN_CFGID_FBT_KICK_USER, OAL_TRUE);
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

