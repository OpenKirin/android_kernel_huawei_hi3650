/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wal_dfx.c
  �� �� ��   : ����
  ��    ��   : z00273164
  ��������   : 2015��10��16��
  ����޸�   :
  ��������   : wal��dfx��ع����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��16��
    ��    ��   : z00273164
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
#include "wlan_types.h"
#include "wal_dfx.h"
#include "oal_net.h"
#include "oal_cfg80211.h"
#include "oal_ext_if.h"
#include "frw_ext_if.h"
#include "dmac_ext_if.h"
#include "hmac_ext_if.h"
#include "hmac_device.h"
#include "hmac_resource.h"
#include "hmac_ext_if.h"
#include "hmac_vap.h"
#include "hmac_p2p.h"
#include "wal_ext_if.h"
#include "wal_linux_cfg80211.h"
#include "wal_linux_scan.h"
#include "wal_linux_event.h"
#include "wal_ext_if.h"
#include "wal_config.h"
#include "wal_regdb.h"
#include "wal_linux_ioctl.h"

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_pm_wlan.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_DFX_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_DFR

#define DFR_WAIT_PLAT_FINISH_TIME   (25000) /* �ȴ�ƽ̨���dfr�����ĵȴ�ʱ�� */

oal_int8 *g_auc_dfr_error_type[] = {   \
            "AP",    \
            "STA",   \
            "P2P0",  \
            "GO",  \
            "CLIENT",  \
            "DFR UNKOWN ERR TYPE!!"};

/* ��ö��Ϊg_auc_dfr_error_type�ַ�����indx���� */
typedef enum
{
    DFR_ERR_TYPE_AP = 0,
    DFR_ERR_TYPE_STA,
    DFR_ERR_TYPE_P2P,
    DFR_ERR_TYPE_GO,
    DFR_ERR_TYPE_CLIENT,

    DFR_ERR_TYPE_BUTT
} wal_dfr_error_type;
typedef oal_uint8 wal_dfr_error_type_enum_uint8;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
extern struct st_exception_info *g_pst_exception_info;
#else
struct st_exception_info
{
    /* wifi�쳣���� */
    oal_work_stru               wifi_excp_worker;
    oal_workqueue_stru         *wifi_exception_workqueue;
	oal_work_stru               wifi_excp_recovery_worker;
    oal_uint32                  wifi_excp_type;
}g_st_exception_info;
struct st_exception_info *g_pst_exception_info = &g_st_exception_info;

struct st_wifi_dfr_callback
{
    void  (*wifi_recovery_complete)(void);
    void  (*notify_wifi_to_recovery)(void);
};
#endif

struct st_wifi_dfr_callback *g_st_wifi_callback;

oal_void wal_dfr_init_param(oal_void);

extern hmac_dfr_info_stru g_st_dfr_info;

#endif //_PRE_WLAN_FEATURE_DFR
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#ifdef _PRE_WLAN_FEATURE_DFR
/*****************************************************************************
 �� �� ��  : hmac_dfr_kick_all_user
 ��������  : �޳�vap����������û�������vap���⣩
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32  wal_dfr_kick_all_user(hmac_vap_stru *pst_hmac_vap)
{
    wal_msg_write_stru              st_write_msg;
    wal_msg_stru                   *pst_rsp_msg = OAL_PTR_NULL;
    oal_uint32                      ul_err_code;
    oal_int32                       l_ret;
    mac_cfg_kick_user_param_stru   *pst_kick_user_param;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_KICK_USER, OAL_SIZEOF(mac_cfg_kick_user_param_stru));

    /* ��������������� */
    pst_kick_user_param = (mac_cfg_kick_user_param_stru *)(st_write_msg.auc_value);
    oal_set_mac_addr(pst_kick_user_param->auc_mac_addr, BROADCAST_MACADDR);

    /* ��дȥ����reason code */
    pst_kick_user_param->us_reason_code = MAC_UNSPEC_REASON;
    if (OAL_PTR_NULL == pst_hmac_vap->pst_net_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_dfr_kick_all_user::pst_net_device is null!}");
        return OAL_SUCC;
    }

    l_ret = wal_send_cfg_event(pst_hmac_vap->pst_net_device,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_kick_user_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_TRUE,
                               &pst_rsp_msg);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_dfr_kick_all_user::return err code [%d]!}\r\n", l_ret);
        return l_ret;
    }


    /* ��������Ϣ */
    ul_err_code = wal_check_and_release_msg_resp(pst_rsp_msg);
    if(OAL_SUCC != ul_err_code)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_dfr_kick_all_user::hmac start vap fail,err code[%u]!}\r\n", ul_err_code);
        return -OAL_EINVAL;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : hmac_process_p2p_excp
 ��������  : p2pģʽ���쳣����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_process_p2p_excp(hmac_vap_stru *pst_hmac_vap)
{
    mac_vap_stru     *pst_mac_vap;
    hmac_device_stru *pst_hmac_dev;

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                     "{hmac_process_sta_excp::Now begin P2P exception recovery program,del user[num:%d] when P2P state is P2P0[%d]/CL[%d]/GO[%d] .}",
                     pst_mac_vap->us_user_nums,
                     IS_P2P_DEV(pst_mac_vap),
                     IS_P2P_CL(pst_mac_vap),
                     IS_P2P_GO(pst_mac_vap));

    /* ɾ���û� */
    wal_dfr_kick_all_user(pst_hmac_vap);

    /* APģʽ����STAģʽ */
    if (IS_AP(pst_mac_vap))
    {
        /* vap��Ϣ��ʼ�� */
        //hmac_dfr_reinit_ap(pst_hmac_vap);
    }
    else if (IS_STA(pst_mac_vap))
    {
        pst_hmac_dev = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
        if (OAL_PTR_NULL == pst_hmac_dev)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                             "{hmac_process_p2p_excp::pst_hmac_device is null, dev_id[%d].}",
                             pst_mac_vap->uc_device_id);

            return OAL_ERR_CODE_MAC_DEVICE_NULL;
        }
        /* ɾ��ɨ����Ϣ�б�ֹͣɨ�� */
        if (pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id == pst_mac_vap->uc_vap_id)
        {
            pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.p_fn_cb = OAL_PTR_NULL;
            pst_hmac_dev->st_scan_mgmt.en_is_scanning = OAL_FALSE;
        }
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_process_ap_excp
 ��������  : apģʽ�µ��쳣����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_process_ap_excp(hmac_vap_stru *pst_hmac_vap)
{
    mac_vap_stru     *pst_mac_vap;

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                     "{hmac_process_sta_excp::Now begin AP exception recovery program, when AP have [%d] USERs.}",
                     pst_mac_vap->us_user_nums);

    /* ɾ���û� */
    wal_dfr_kick_all_user(pst_hmac_vap);
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : hmac_process_sta_excp
 ��������  : staģʽ�µ��쳣����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_process_sta_excp(hmac_vap_stru *pst_hmac_vap)
{
    mac_vap_stru     *pst_mac_vap;
    hmac_device_stru *pst_hmac_dev;

    pst_mac_vap = &(pst_hmac_vap->st_vap_base_info);
    pst_hmac_dev = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_hmac_dev)
    {
        OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                         "{hmac_process_sta_excp::pst_hmac_device is null, dev_id[%d].}",
                         pst_mac_vap->uc_device_id);

        return OAL_ERR_CODE_MAC_DEVICE_NULL;
    }

    OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_DFR,
                     "{hmac_process_sta_excp::Now begin sta exception recovery program, when sta have [%d] users.}",
                     pst_mac_vap->us_user_nums);

    /* ����״̬���ϱ�����ʧ�ܣ�ɾ���û� */
    wal_dfr_kick_all_user(pst_hmac_vap);

    /* ɾ��ɨ����Ϣ�б�ֹͣɨ�� */
    if (pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.uc_vap_id == pst_mac_vap->uc_vap_id)
    {
        pst_hmac_dev->st_scan_mgmt.st_scan_record_mgmt.p_fn_cb = OAL_PTR_NULL;
        pst_hmac_dev->st_scan_mgmt.en_is_scanning = OAL_FALSE;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_dfr_destroy_vap
 ��������  : dfr������ɾ��vap
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��16��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32  wal_dfr_destroy_vap(oal_net_device_stru *pst_netdev)
{
    wal_msg_write_stru           st_write_msg;
    wal_msg_stru                *pst_rsp_msg = OAL_PTR_NULL;
    oal_uint32                  ul_err_code;

    oal_int32                    l_ret;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DESTROY_VAP, OAL_SIZEOF(oal_int32));
    l_ret = wal_send_cfg_event(pst_netdev,
                        WAL_MSG_TYPE_WRITE,
                        WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                        (oal_uint8 *)&st_write_msg,
                         OAL_TRUE,
                        &pst_rsp_msg);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAL_IO_PRINT("DFR DESTROY_VAP[name:%s] fail, return[%d]!", pst_netdev->name, l_ret);
        OAM_WARNING_LOG2(0, OAM_SF_DFR, "{wal_dfr_excp_process::DESTROY_VAP return err code [%d], iftype[%d]!}\r\n",
                        l_ret,
                        pst_netdev->ieee80211_ptr->iftype);

        return l_ret;
    }

    /* ��ȡ���صĴ����� */
    ul_err_code = wal_check_and_release_msg_resp(pst_rsp_msg);
    if(OAL_SUCC != ul_err_code)
    {
        OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_process::hmac add vap fail, err code[%u]!}\r\n", ul_err_code);
        return l_ret;
    }

    OAL_NET_DEV_PRIV(pst_netdev) = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_dfr_recovery_env
 ��������  : �쳣�ָ����� �ָ�����vap�����ϱ��쳣��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��15��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_dfr_recovery_env(void)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint32                    ul_ret;
    oal_int32                     l_ret;
    oal_net_device_stru          *pst_netdev;
    wal_dfr_error_type_enum_uint8 en_err_type = DFR_ERR_TYPE_BUTT;
    oal_uint32                    ul_timeleft;
    oal_wireless_dev_stru        *pst_wireless_dev;


    CHR_EXCEPTION(CHR_WIFI_DRV(CHR_WIFI_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_RECV_LASTWORD));
    if (OAL_TRUE != g_st_dfr_info.bit_ready_to_recovery_flag)
    {
        return OAL_SUCC;
    }

    ul_timeleft = oal_wait_for_completion_timeout(&g_st_dfr_info.st_plat_process_comp, OAL_MSECS_TO_JIFFIES(DFR_WAIT_PLAT_FINISH_TIME));
    if (!ul_timeleft)
    {
        OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_excp_process:wait dev reset timeout[%d]", DFR_WAIT_PLAT_FINISH_TIME);
        //return OAL_FAIL;
    }


    OAM_WARNING_LOG1(0, OAM_SF_ANY, "wal_dfr_recovery_env: get plat_process_comp signal after[%u]ms!", (oal_uint32)(DFR_WAIT_PLAT_FINISH_TIME - ul_timeleft));

    /* �ָ�vap, �ϱ��쳣���ϲ� */
    for (; g_st_dfr_info.ul_netdev_num > 0; g_st_dfr_info.ul_netdev_num--)
    {
        ul_ret = OAL_SUCC;
        pst_netdev = (oal_net_device_stru *)g_st_dfr_info.past_netdev[g_st_dfr_info.ul_netdev_num - 1];

        if (NL80211_IFTYPE_AP == pst_netdev->ieee80211_ptr->iftype)
        {

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
            wal_custom_cali();
            hwifi_config_init_force();
#endif
            l_ret = wal_cfg_vap_h2d_event(pst_netdev);
            if(OAL_SUCC != l_ret)
            {
                OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_recovery_env:DFR Device cfg_vap creat false[%d]!", l_ret);
                wal_dfr_init_param();
                return OAL_FAIL;
            }

            /* host device_stru��ʼ��*/
            l_ret = wal_host_dev_init(pst_netdev);
            if(OAL_SUCC != l_ret)
            {
                OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_recovery_env::DFR wal_host_dev_init FAIL %d ", l_ret);
            }

            ul_ret = wal_setup_ap(pst_netdev);
            en_err_type = DFR_ERR_TYPE_AP;


        }
        else if ((NL80211_IFTYPE_STATION == pst_netdev->ieee80211_ptr->iftype)||
                (NL80211_IFTYPE_P2P_DEVICE == pst_netdev->ieee80211_ptr->iftype))
        {
            l_ret = wal_netdev_open(pst_netdev);
            en_err_type = (!OAL_STRCMP(pst_netdev->name , "p2p0"))? DFR_ERR_TYPE_P2P : DFR_ERR_TYPE_STA;
        }
        else
        {
            pst_wireless_dev = OAL_NETDEVICE_WDEV(pst_netdev);

            /* ȥע��netdev */
            oal_net_unregister_netdev(pst_netdev);
            OAL_MEM_FREE(pst_wireless_dev, OAL_TRUE);

            continue;
        }

        if (OAL_UNLIKELY(OAL_SUCC != l_ret) || OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAL_IO_PRINT("DFR BOOT_VAP[name:%s] fail! error_code[%d]", pst_netdev->name, ((oal_uint8)l_ret | ul_ret));
            OAM_WARNING_LOG2(0, OAM_SF_ANY, "{wal_dfr_excep_process:: Boot vap Failure, vap_iftype[%d], error_code[%d]!}\r\n",
                            pst_netdev->ieee80211_ptr->iftype,
                            ((oal_uint8)l_ret | ul_ret));
            continue;
        }

        //��Ҫ�ָ�ɨ��ô???
        oal_net_device_open(pst_netdev);

        /* �ϱ��쳣 */
        oal_cfg80211_rx_exception(pst_netdev,
                                (oal_uint8 *)g_auc_dfr_error_type[en_err_type],
                                OAL_STRLEN(g_auc_dfr_error_type[en_err_type]));

    }
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    wlan_pm_enable();
#endif

    g_st_dfr_info.bit_device_reset_process_flag = OAL_FALSE;
    g_st_dfr_info.bit_ready_to_recovery_flag    = OAL_FALSE;

#endif

    return OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : wal_dfr_excp_process
 ��������  : device�쳣��wal��Ĵ������̣���������ɾ��vap����device��������
             �ָ��������´���host&device��vap
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��11��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
extern oal_int32 plat_exception_handler(oal_uint32 subsys_type, oal_uint32 thread_type, oal_uint32 exception_type);
oal_uint32  wal_dfr_excp_process(mac_device_stru *pst_mac_device, oal_uint32 ul_exception_type)
{
    hmac_vap_stru               *pst_hmac_vap;
    mac_vap_stru                *pst_mac_vap;
    oal_uint8                    uc_vap_idx;
    oal_int32                    l_ret;

    oal_net_device_stru          *pst_netdev = OAL_PTR_NULL;
    oal_net_device_stru          *pst_p2p0_netdev = OAL_PTR_NULL;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ASSOC, "{wal_dfr_excp_process::pst_mac_device is null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    //wlan_pm_disable();
    wlan_pm_disable_check_wakeup(OAL_FALSE);
#endif
    OAL_MEMZERO((oal_uint8 *)(g_st_dfr_info.past_netdev), OAL_SIZEOF(g_st_dfr_info.past_netdev[0]) * (WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT + 1));

    for (uc_vap_idx = pst_mac_device->uc_vap_num, g_st_dfr_info.ul_netdev_num = 0; uc_vap_idx > 0; uc_vap_idx--)
    {
        /* ��ȡ���ұ�һλΪ1��λ������ֵ��Ϊvap�������±� */
        pst_hmac_vap    = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx-1]);
        if (OAL_PTR_NULL == pst_hmac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_process::mac_res_get_hmac_vap fail!vap_idx = %u}\r",pst_mac_device->auc_vap_id[uc_vap_idx-1]);
            continue;
        }
        pst_mac_vap     = &(pst_hmac_vap->st_vap_base_info);
        pst_netdev      = pst_hmac_vap->pst_net_device;

#ifdef _PRE_WLAN_FEATURE_P2P
        if (IS_P2P_DEV(pst_mac_vap))
        {
            pst_netdev = pst_hmac_vap->pst_p2p0_net_device;
        }
        else if (IS_P2P_CL(pst_mac_vap))
        {
            pst_p2p0_netdev = pst_hmac_vap->pst_p2p0_net_device;
            if (OAL_PTR_NULL != pst_p2p0_netdev)
            {
                g_st_dfr_info.past_netdev[g_st_dfr_info.ul_netdev_num]  = (oal_uint32 *)pst_p2p0_netdev;
                g_st_dfr_info.ul_netdev_num ++;
            }
        }
#endif
        if (OAL_PTR_NULL == pst_netdev)
        {
            OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_process::pst_netdev NULL pointer !vap_idx = %u}\r",pst_mac_device->auc_vap_id[uc_vap_idx-1]);
            continue;
        }
        else if (OAL_PTR_NULL == pst_netdev->ieee80211_ptr)
        {
            OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_process::ieee80211_ptr NULL pointer !vap_idx = %u}\r",pst_mac_device->auc_vap_id[uc_vap_idx-1]);
            continue;
        }

        g_st_dfr_info.past_netdev[g_st_dfr_info.ul_netdev_num]  = (oal_uint32 *)pst_netdev;
        g_st_dfr_info.ul_netdev_num ++;

        OAM_WARNING_LOG4(0 , OAM_SF_DFR, "wal_dfr_excp_process:vap_iftype [%d], vap_id[%d], vap_idx[%d], vap_mode_idx[%d]",
                    pst_netdev->ieee80211_ptr->iftype,
                    pst_mac_vap->uc_vap_id,
                    uc_vap_idx,
                    g_st_dfr_info.ul_netdev_num);

        /* DTS2016091805471 drf�쳣������Ҫ�ϱ�������ͨɨ���PNOɨ�� */
        wal_force_scan_complete(pst_netdev, OAL_TRUE);
        wal_stop_sched_scan(pst_netdev);

        oal_net_device_close(pst_netdev);
        l_ret = wal_dfr_destroy_vap(pst_netdev);
        if (OAL_UNLIKELY(OAL_SUCC != l_ret))
        {
            continue;
        }

        if (OAL_PTR_NULL != pst_p2p0_netdev)
        {
            l_ret = wal_dfr_destroy_vap(pst_p2p0_netdev);
            if (OAL_UNLIKELY(OAL_SUCC != l_ret))
            {
                OAM_WARNING_LOG0(0, OAM_SF_DFR, "{wal_dfr_excp_process::DESTROY_P2P0 return err code [%d]!}\r\n");
                oal_net_unregister_netdev(pst_netdev);
                continue;
            }
            pst_p2p0_netdev = OAL_PTR_NULL;
        }

    }

    /* device close& open */
    OAL_INIT_COMPLETION(&g_st_dfr_info.st_plat_process_comp);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    plat_exception_handler(0, 0, ul_exception_type);
#endif

    //��ʼdfr�ָ�����: wal_dfr_recovery_env();
    g_st_dfr_info.bit_ready_to_recovery_flag = OAL_TRUE;
    oal_queue_work(g_pst_exception_info->wifi_exception_workqueue, &g_pst_exception_info->wifi_excp_recovery_worker);

    return OAL_SUCC;

}
/*****************************************************************************
 �� �� ��  : wal_dfr_signal_complete
 ��������  : dfr device�쳣�ָ� ƽ̨������ɻص��ӿ�(device�����ܽţ�����patch)
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void wal_dfr_signal_complete(oal_void)
{
    OAL_COMPLETE(&g_st_dfr_info.st_plat_process_comp);
}


/*****************************************************************************
 �� �� ��  : wal_dfr_excp_rx
 ��������  : device�쳣��������ڣ�Ŀǰ����device������SDIO��дʧ�ܵ��쳣
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��23��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_dfr_excp_rx(oal_uint8 uc_device_id, oal_uint32 ul_exception_type)
{
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_uint8                     uc_vap_idx;
    hmac_vap_stru                *pst_hmac_vap;
    mac_vap_stru                 *pst_mac_vap;
    mac_device_stru              *pst_mac_dev;

    pst_mac_dev = mac_res_get_dev(uc_device_id);
    if (OAL_PTR_NULL == pst_mac_dev)
    {
        OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_excp_rx:ERROR dev_ID[%d] in DFR process!", uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*  �쳣��λ�����Ƿ��� */
    if ((!g_st_dfr_info.bit_device_reset_enable) || g_st_dfr_info.bit_device_reset_process_flag)
    {
        return OAL_SUCC;
    }

    /* log���ڽ����쳣�������� */
    OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_rx:: Enter the exception processing, type[%d].}", ul_exception_type);

    g_st_dfr_info.bit_device_reset_process_flag = OAL_TRUE;
    g_st_dfr_info.bit_user_disconnect_flag      = OAL_TRUE;

    /* ����ÿ��vapģʽ�����쳣���� */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_dev->uc_vap_num; uc_vap_idx++)
    {

        /* ��ȡ���ұ�һλΪ1��λ������ֵ��Ϊvap�������±� */
        pst_hmac_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_mac_dev->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_hmac_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_DFR, "{wal_dfr_excp_rx::mac_res_get_hmac_vap fail!vap_idx = %u}\r",pst_mac_dev->auc_vap_id[uc_vap_idx]);
            continue;
        }

        pst_mac_vap  = &(pst_hmac_vap->st_vap_base_info);
        if (!IS_LEGACY_VAP(pst_mac_vap))
        {
            wal_process_p2p_excp(pst_hmac_vap);
        }
        else if (IS_AP(pst_mac_vap))
        {
            wal_process_ap_excp(pst_hmac_vap);
        }
        else if (IS_STA(pst_mac_vap))
        {
            wal_process_sta_excp(pst_hmac_vap);
        }
        else
        {
            continue;
        }

    }
    return wal_dfr_excp_process(pst_mac_dev, ul_exception_type);
#else
    return OAL_SUCC;
#endif
}
/*****************************************************************************
 �� �� ��  : wal_dfr_get_excp_type
 ��������  : ���excp�Ĵ�������
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_dfr_get_excp_type(oal_void)
{
    return g_pst_exception_info->wifi_excp_type;
}

/*****************************************************************************
 �� �� ��  : wal_dfr_excp_work
 ��������  : excep_worker������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
void  wal_dfr_excp_work(oal_work_stru *work)
{
    oal_uint32 ul_exception_type;
    oal_uint8  uc_device_id;

    ul_exception_type = wal_dfr_get_excp_type();

    /* �ݲ�֧�ֶ�chip����device */
    if ((1 != WLAN_CHIP_DBSC_DEVICE_NUM) || (1 != WLAN_CHIP_MAX_NUM_PER_BOARD))
    {
        OAM_ERROR_LOG2(0, OAM_SF_DFR, "DFR Can not support muti_chip[%d] or muti_device[%d].\n",
                        WLAN_CHIP_MAX_NUM_PER_BOARD, WLAN_CHIP_DBSC_DEVICE_NUM);
        return;
    }
    uc_device_id = 0;

    wal_dfr_excp_rx(uc_device_id, ul_exception_type);

}
void  wal_dfr_bfgx_excp(void)
{
    wal_dfr_excp_work(NULL);
}
void  wal_dfr_recovery_work(oal_work_stru *work)
{
    wal_dfr_recovery_env();
}
/*****************************************************************************
 �� �� ��  : wal_init_dfr_param
 ��������  : ��ʼ��dfr����ز���
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��4��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void wal_dfr_init_param(oal_void)
{
    OAL_MEMZERO((oal_uint8 *)&g_st_dfr_info, OAL_SIZEOF(hmac_dfr_info_stru));

    g_st_dfr_info.bit_device_reset_enable        = OAL_TRUE;
    g_st_dfr_info.bit_hw_reset_enable            = OAL_FALSE;
    g_st_dfr_info.bit_soft_watchdog_enable       = OAL_FALSE;
    g_st_dfr_info.bit_device_reset_process_flag  = OAL_FALSE;
    g_st_dfr_info.bit_ready_to_recovery_flag     = OAL_FALSE;
    g_st_dfr_info.bit_user_disconnect_flag       = OAL_FALSE;
    g_st_dfr_info.ul_excp_type                   = 0xffffffff;

}

/*****************************************************************************
 �� �� ��  : wal_init_dev_excp_handler
 ��������  : ��ʼ��device�쳣�ĸ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��24��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_dfr_excp_init_handler(oal_void)
{
    hmac_device_stru     *pst_hmac_dev;
    struct st_wifi_dfr_callback *pst_wifi_callback = OAL_PTR_NULL;

    pst_hmac_dev = hmac_res_get_mac_dev(0);
    if (OAL_PTR_NULL == pst_hmac_dev)
    {
        OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_init_dev_excp_handler:ERROR hmac dev_ID[%d] in DFR process!", 0);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ʼ��dfr���� */
    wal_dfr_init_param();

    /* �ҽӵ��ù��� */
    if (OAL_PTR_NULL != g_pst_exception_info)
    {
        OAL_INIT_WORK(&g_pst_exception_info->wifi_excp_worker, wal_dfr_excp_work);
        OAL_INIT_WORK(&g_pst_exception_info->wifi_excp_recovery_worker, wal_dfr_recovery_work);
        g_pst_exception_info->wifi_exception_workqueue= OAL_CREATE_SINGLETHREAD_WORKQUEUE("wifi_exception_queue");
    }

    pst_wifi_callback = (struct st_wifi_dfr_callback *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, OAL_SIZEOF(struct st_wifi_dfr_callback), OAL_TRUE);
    if (OAL_PTR_NULL == pst_wifi_callback)
    {
        OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_init_dev_excp_handler:can not alloc mem,size[%d]!", OAL_SIZEOF(struct st_wifi_dfr_callback));
        g_st_wifi_callback = OAL_PTR_NULL;
        return OAL_ERR_CODE_PTR_NULL;
    }
    g_st_wifi_callback = pst_wifi_callback;
    pst_wifi_callback->wifi_recovery_complete = wal_dfr_signal_complete;
    pst_wifi_callback->notify_wifi_to_recovery = wal_dfr_bfgx_excp;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    plat_wifi_exception_rst_register(pst_wifi_callback);
#endif

    OAM_WARNING_LOG0(0, OAM_SF_DFR, "DFR wal_init_dev_excp_handler init ok.\n");
    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_dfr_excp_exit_handler
 ��������  :  �˳�dfr netlink
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��29��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void wal_dfr_excp_exit_handler(oal_void)
{
    hmac_device_stru     *pst_hmac_dev;

    pst_hmac_dev = hmac_res_get_mac_dev(0);
    if (OAL_PTR_NULL == pst_hmac_dev)
    {
        OAM_ERROR_LOG1(0 , OAM_SF_DFR, "wal_dfr_excp_exit_handler:ERROR dev_ID[%d] in DFR process!", 0);
        return;
    }

    if (OAL_PTR_NULL != g_pst_exception_info)
    {
        oal_cancel_work_sync(&g_pst_exception_info->wifi_excp_worker);
        oal_cancel_work_sync(&g_pst_exception_info->wifi_excp_recovery_worker);
        oal_destroy_workqueue(g_pst_exception_info->wifi_exception_workqueue);
    }
    OAL_MEM_FREE(g_st_wifi_callback, OAL_TRUE);

    OAM_WARNING_LOG0(0, OAM_SF_DFR, "wal_dfr_excp_exit_handler::DFR dev_excp_handler remove ok.");

}
#else
oal_uint32 wal_dfr_excp_rx(oal_uint8 uc_device_id, oal_uint32 ul_exception_type)
{
    return OAL_SUCC;
}

#endif //_PRE_WLAN_FEATURE_DFR


oal_uint32 wal_dfx_init(oal_void)
{
    oal_uint32      l_ret = OAL_SUCC;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_DFR
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    //genKernel_init();
    l_ret = init_dev_excp_handler();
    if (OAL_SUCC != l_ret)
    {
        return l_ret;
    }
#endif
    l_ret = wal_dfr_excp_init_handler();
#endif //_PRE_WLAN_FEATURE_DFR
#endif

    return l_ret;
}

oal_void wal_dfx_exit(oal_void)
{

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_DFR
    wal_dfr_excp_exit_handler();

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    //genKernel_exit();
    deinit_dev_excp_handler();
#endif
#endif //_PRE_WLAN_FEATURE_DFR
#endif

}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

