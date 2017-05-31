/******************************************************************************

                  ��Ȩ���� (C), 2001-2022, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wal_linux_ioctl_debug.c
  �� �� ��   : ����
  ��    ��   : z00262551
  ��������   : 2016��4��8��
  ����޸�   :
  ��������   : linux ioctl���õ�������
  �����б�   :
  �޸���ʷ   :

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#ifdef _PRE_WLAN_CFGID_DEBUG

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oal_profiling.h"
#include "oal_kernel_file.h"
#include "oal_cfg80211.h"

#include "oam_ext_if.h"
#include "frw_ext_if.h"

#include "wlan_spec.h"
#include "wlan_types.h"

#include "mac_vap.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "mac_ie.h"

#include "hmac_ext_if.h"
#include "hmac_chan_mgmt.h"

#include "wal_main.h"
#include "wal_ext_if.h"
#include "wal_config.h"
#include "wal_regdb.h"
#include "wal_linux_scan.h"
#include "wal_linux_ioctl.h"
#include "wal_linux_bridge.h"
#include "wal_linux_flowctl.h"
#include "wal_linux_atcmdsrv.h"
#include "wal_linux_event.h"
#include "hmac_resource.h"
#include "hmac_p2p.h"

#ifdef _PRE_WLAN_FEATURE_P2P
#include "wal_linux_cfg80211.h"
#endif

#include "wal_dfx.h"


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#include "oal_hcc_host_if.h"
#include "plat_cali.h"
#endif

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <linux/notifier.h>
#include <linux/inetdevice.h>
#include <net/addrconf.h>
#endif
#include "hmac_arp_offload.h"
#endif


#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
#include "hmac_auto_adjust_freq.h"
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
#include "hmac_roam_main.h"
#endif //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hisi_customize_wifi.h"
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */

#include "dmac_alg_if.h"
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "plat_pm_wlan.h"
#endif
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_LINUX_IOCTL_DEBUG_C
#define MAX_PRIV_CMD_SIZE   4096

/*****************************************************************************
  2 �ṹ�嶨��
*****************************************************************************/
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_DFR
extern  hmac_dfr_info_stru    g_st_dfr_info;
#endif //_PRE_WLAN_FEATURE_DFR
extern OAL_CONST oal_int8 * pauc_tx_dscr_param_name[];
extern OAL_CONST wal_ioctl_alg_cfg_stru g_ast_alg_cfg_map[];
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : wal_hipriv_global_log_switch
 ��������  : ����ȫ����־����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��19��,����һ
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_global_log_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_int32                   l_switch_val;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;

    /* ��ȡ����״ֵ̬ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_global_log_switch::error code[%d]}\r\n", ul_ret);
        return ul_ret;
    }

    if ((0 != oal_strcmp("0", ac_name)) && (0 != oal_strcmp("1", ac_name)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_global_log_switch::invalid switch value}\r\n");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    l_switch_val = oal_atoi(ac_name);

    return oam_log_set_global_switch((oal_switch_enum_uint8)l_switch_val);
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_vap_log_switch
 ��������  : ����VAP������־����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��3��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_vap_log_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    mac_vap_stru               *pst_mac_vap;
    oal_int32                   l_switch_val;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;

    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_vap_log_switch::null pointer.}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ����״ֵ̬ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_vap_log_switch::error code[%d]}\r\n", ul_ret);
        return ul_ret;
    }

    if ((0 != oal_strcmp("0", ac_name)) && (0 != oal_strcmp("1", ac_name)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_vap_log_switch::invalid switch value}\r\n");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    l_switch_val = oal_atoi(ac_name);

    return oam_log_set_vap_switch(pst_mac_vap->uc_vap_id, (oal_switch_enum_uint8)l_switch_val);
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_feature_log_level
 ��������  : ����INFO��־���𿪹�����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��20��,���ڶ�
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_feature_log_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    mac_vap_stru                       *pst_mac_vap;
    oam_feature_enum_uint8              en_feature_id;
    oal_uint8                           uc_switch_vl;
    oal_uint32                          ul_off_set;
    oal_int8                            ac_param[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                          ul_ret;
    oam_log_level_enum_uint8            en_log_lvl;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        wal_msg_write_stru          st_write_msg;
#endif

    /* OAM logģ��Ŀ��ص�����: hipriv "Hisilicon0[vapx] feature_log_switch {feature_name} {0/1}"
       1-2(error��warning)������־��vap����Ϊά�ȣ�
    */

    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_feature_log_switch::null pointer.}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�������� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* �ṩ�������İ�����Ϣ */
    if ('?' == ac_param[0])
    {
        OAL_IO_PRINT("please input abbr feature name. \r\n");
        oam_show_feature_list();
        return OAL_SUCC;
    }

    /* ��ȡ����ID */
    ul_ret = oam_get_feature_id((oal_uint8 *)ac_param, &en_feature_id);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_feature_log_switch::invalid feature name}\r\n");
        return ul_ret;
    }

    /* ��ȡ����ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* ��ȡINFO���𿪹�״̬ */
    if ((0 != oal_strcmp("0", ac_param)) && (0 != oal_strcmp("1", ac_param)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_feature_log_switch::invalid switch value}\r\n");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }
    uc_switch_vl = (oal_uint8)oal_atoi(ac_param);

     /* �ر�INFO��־����ʱ���ָ���Ĭ�ϵ���־���� */
    en_log_lvl = (OAL_SWITCH_ON == uc_switch_vl) ? OAM_LOG_LEVEL_INFO : OAM_LOG_DEFAULT_LEVEL;
    ul_ret = oam_log_set_feature_level(pst_mac_vap->uc_vap_id, en_feature_id, en_log_lvl) ;

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_FEATURE_LOG, OAL_SIZEOF(oal_int32));
    *((oal_uint16 *)(st_write_msg.auc_value)) = ((en_feature_id<<8) | en_log_lvl);
    ul_ret |= (oal_uint32)wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_feature_log_switch::return err code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
#endif

    return ul_ret;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_log_ratelimit
 ��������  : printk���ز�������
             ֧�ֿ��� ��ʱʱ���������Ĳ�������
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��21��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_log_ratelimit(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oam_ratelimit_stru                  st_ratelimit;
    oam_ratelimit_type_enum_uint8       en_ratelimit_type;
    oal_uint32                          ul_off_set;
    oal_int8                            ac_param[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                          ul_ret;

    /* OAM log printk������������: hipriv "Hisilicon0[vapx] {log_ratelimit} {printk(0)/sdt(1)}{switch(0/1)} {interval} {burst}" */

    st_ratelimit.en_ratelimit_switch    = OAL_SWITCH_OFF;
    st_ratelimit.ul_interval            = OAM_RATELIMIT_DEFAULT_INTERVAL;
    st_ratelimit.ul_burst               = OAM_RATELIMIT_DEFAULT_BURST;

    /* ��ȡ�������� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
    pc_param += ul_off_set;

    en_ratelimit_type =  (oam_ratelimit_type_enum_uint8)oal_atoi(ac_param);

    /* ��ȡ����״̬ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
    pc_param += ul_off_set;

    st_ratelimit.en_ratelimit_switch =  (oal_switch_enum_uint8)oal_atoi(ac_param);

    if (OAL_SWITCH_ON == st_ratelimit.en_ratelimit_switch)
    {
        /* ��ȡintervalֵ */
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
        pc_param += ul_off_set;

        st_ratelimit.ul_interval = (oal_uint32)oal_atoi(ac_param);

        /* ��ȡburstֵ */
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
        pc_param += ul_off_set;

        st_ratelimit.ul_burst = (oal_uint32)oal_atoi(ac_param);
    }

    return oam_log_set_ratelimit_param(en_ratelimit_type, &st_ratelimit);
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : wal_hipriv_log_lowpower
 ��������  : sdt log�͹���ģʽ����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��21��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_log_lowpower(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    /* OAM eventģ��Ŀ��ص�����: hipriv "Hisilicon0 log_pm 0 | 1"
        �˴���������"1"��"0"����ac_name
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_log_lowpower::wal_get_cmd_one_arg return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����eventģ����в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_log_lowpower::the log switch command is error [%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_LOG_PM, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_event_switch::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_pm_switch
 ��������  : �͹���ȫ��ʹ��
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��21��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_pm_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    /* OAM eventģ��Ŀ��ص�����: hipriv "Hisilicon0 wal_hipriv_pm_switch 0 | 1"
        �˴���������"1"��"0"����ac_name
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pm_switch::wal_get_cmd_one_arg return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����eventģ����в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pm_switch::the log switch command is error [%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_PM_SWITCH, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pm_switch::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_ucast_data_dscr_param
 ��������  : ����������������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��31��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_ucast_data_dscr_param(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    mac_cfg_set_dscr_param_stru     *pst_set_dscr_param;
    wal_dscr_param_enum_uint8        en_param_index;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_DSCR, OAL_SIZEOF(mac_cfg_set_dscr_param_stru));

    /* ��������������������� */
    pst_set_dscr_param = (mac_cfg_set_dscr_param_stru *)(st_write_msg.auc_value);

    /* ��ȡ�������ֶ����������ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ucast_data_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* ������������һ���ֶ� */
    for (en_param_index = 0; en_param_index < WAL_DSCR_PARAM_BUTT; en_param_index++)
    {
        if(!oal_strcmp(pauc_tx_dscr_param_name[en_param_index], ac_arg))
        {
            break;
        }
    }

    /* ��������Ƿ��� */
    if (WAL_DSCR_PARAM_BUTT == en_param_index)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_ucast_data_dscr_param::no such param for tx dscr!}\r\n");
        return OAL_FAIL;
    }

    pst_set_dscr_param->uc_function_index = en_param_index;

    /* ����Ҫ����Ϊ����ֵ */
    pst_set_dscr_param->l_value = oal_strtol(pc_param, OAL_PTR_NULL, 0);

    /* ��������֡���������� tpye = MAC_VAP_CONFIG_UCAST_DATA */
    pst_set_dscr_param->en_type = MAC_VAP_CONFIG_UCAST_DATA;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_set_dscr_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ucast_data_dscr_param::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : wal_hipriv_set_bcast_data_dscr_param
 ��������  : ����������������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : 00184180 yaorui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_bcast_data_dscr_param(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    mac_cfg_set_dscr_param_stru     *pst_set_dscr_param;
    wal_dscr_param_enum_uint8        en_param_index;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_DSCR, OAL_SIZEOF(mac_cfg_set_dscr_param_stru));

    /* ��������������������� */
    pst_set_dscr_param = (mac_cfg_set_dscr_param_stru *)(st_write_msg.auc_value);

    /* ��ȡ�������ֶ����������ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_bcast_data_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* ������������һ���ֶ� */
    for (en_param_index = 0; en_param_index < WAL_DSCR_PARAM_BUTT; en_param_index++)
    {
        if(!oal_strcmp(pauc_tx_dscr_param_name[en_param_index], ac_arg))
        {
            break;
        }
    }

    /* ��������Ƿ��� */
    if (WAL_DSCR_PARAM_BUTT == en_param_index)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_bcast_data_dscr_param::no such param for tx dscr!}\r\n");
        return OAL_FAIL;
    }

    pst_set_dscr_param->uc_function_index = en_param_index;

    /* ����Ҫ����Ϊ����ֵ */
    pst_set_dscr_param->l_value = oal_strtol(pc_param, OAL_PTR_NULL, 0);

    /* �㲥����֡���������� tpye = MAC_VAP_CONFIG_BCAST_DATA */
    pst_set_dscr_param->en_type = MAC_VAP_CONFIG_BCAST_DATA;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_set_dscr_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_bcast_data_dscr_param::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_ucast_mgmt_dscr_param
 ��������  : ���õ�������֡������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : 00184180 yaorui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_ucast_mgmt_dscr_param(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    mac_cfg_set_dscr_param_stru     *pst_set_dscr_param;
    wal_dscr_param_enum_uint8        en_param_index;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                        uc_band;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_DSCR, OAL_SIZEOF(mac_cfg_set_dscr_param_stru));

    /* ��������������������� */
    pst_set_dscr_param = (mac_cfg_set_dscr_param_stru *)(st_write_msg.auc_value);

    /***************************************************************************
             sh hipriv.sh "vap0 set_ucast_mgmt data0 2 8389137"
    ***************************************************************************/
    /* ����data0 */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ucast_mgmt_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* ������������һ���ֶ� */
    for (en_param_index = 0; en_param_index < WAL_DSCR_PARAM_BUTT; en_param_index++)
    {
        if(!oal_strcmp(pauc_tx_dscr_param_name[en_param_index], ac_arg))
        {
            break;
        }
    }

    /* ��������Ƿ��� */
    if (WAL_DSCR_PARAM_BUTT == en_param_index)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_ucast_mgmt_dscr_param::no such param for tx dscr!}\r\n");
        return OAL_FAIL;
    }

    pst_set_dscr_param->uc_function_index = en_param_index;

    /* ����Ҫ����Ϊ�ĸ�Ƶ�εĵ�������֡ 2G or 5G*/
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ucast_mgmt_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    uc_band = (oal_uint8)oal_atoi(ac_arg);

    /* ��������֡���������� tpye = MAC_VAP_CONFIG_UCAST_MGMT 2Ϊ2G,����Ϊ5G  */
    if (WLAN_BAND_2G == uc_band)
    {
        pst_set_dscr_param->en_type = MAC_VAP_CONFIG_UCAST_MGMT_2G;
    }
    else
    {
        pst_set_dscr_param->en_type = MAC_VAP_CONFIG_UCAST_MGMT_5G;
    }

    /* ����Ҫ����Ϊ�������� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ucast_mgmt_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    pst_set_dscr_param->l_value = oal_strtol(ac_arg, OAL_PTR_NULL, 0);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_set_dscr_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ucast_mgmt_dscr_param::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_mbcast_mgmt_dscr_param
 ��������  : �����鲥���㲥����֡������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��22��
    ��    ��   : 00184180 yaorui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_mbcast_mgmt_dscr_param(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    mac_cfg_set_dscr_param_stru     *pst_set_dscr_param;
    wal_dscr_param_enum_uint8        en_param_index;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                        uc_band;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_DSCR, OAL_SIZEOF(mac_cfg_set_dscr_param_stru));

    /* ��������������������� */
    pst_set_dscr_param = (mac_cfg_set_dscr_param_stru *)(st_write_msg.auc_value);

    /***************************************************************************
             sh hipriv.sh "vap0 set_mcast_mgmt data0 5 8389137"
    ***************************************************************************/
    /* ����data0 */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mbcast_mgmt_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* ������������һ���ֶ� */
    for (en_param_index = 0; en_param_index < WAL_DSCR_PARAM_BUTT; en_param_index++)
    {
        if(!oal_strcmp(pauc_tx_dscr_param_name[en_param_index], ac_arg))
        {
            break;
        }
    }

    /* ��������Ƿ��� */
    if (WAL_DSCR_PARAM_BUTT == en_param_index)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_mbcast_mgmt_dscr_param::no such param for tx dscr!}\r\n");
        return OAL_FAIL;
    }

    pst_set_dscr_param->uc_function_index = en_param_index;

    /* ����Ҫ����Ϊ�ĸ�Ƶ�εĵ�������֡ 2G or 5G*/
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mbcast_mgmt_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    uc_band = (oal_uint8)oal_atoi(ac_arg);

    /* ��������֡���������� tpye = MAC_VAP_CONFIG_UCAST_MGMT 2Ϊ2G,����Ϊ5G  */
    if (WLAN_BAND_2G == uc_band)
    {
        pst_set_dscr_param->en_type = MAC_VAP_CONFIG_MBCAST_MGMT_2G;
    }
    else
    {
        pst_set_dscr_param->en_type = MAC_VAP_CONFIG_MBCAST_MGMT_5G;
    }

    /* ����Ҫ����Ϊ�������� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mbcast_mgmt_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    pst_set_dscr_param->l_value = oal_strtol(ac_arg, OAL_PTR_NULL, 0);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_set_dscr_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mbcast_mgmt_dscr_param::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

#ifdef _PRE_WLAN_FEATURE_11D
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_rd_by_ie_switch
 ��������  :�����Ƿ���ݻ�ȡ�Ĺ���ap�Ĺ���������Լ��Ĺ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��17��
    ��    ��   : zhangxiang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_hipriv_set_rd_by_ie_switch(oal_net_device_stru *pst_net_dev,oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_switch_enum_uint8           *pst_set_rd_by_ie_switch;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_switch_enum_uint8            en_rd_by_ie_switch = OAL_SWITCH_OFF;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_RD_IE_SWITCH, OAL_SIZEOF(oal_switch_enum_uint8));

    /* ��������������������� */
    pst_set_rd_by_ie_switch = (oal_switch_enum_uint8 *)(st_write_msg.auc_value);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rd_by_ie_switch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    en_rd_by_ie_switch = (oal_uint8)oal_atoi(ac_name);
    *pst_set_rd_by_ie_switch = en_rd_by_ie_switch;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_switch_enum_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rd_by_ie_switch::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_nss
 ��������  : ���ÿռ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��3��12��
     ��    ��   : y00196452
     �޸�����   : �����ɺ���


*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_nss(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
#ifdef _PRE_WLAN_CHIP_TEST
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    mac_cfg_tx_comp_stru             *pst_set_nss_param;
    oal_int32                        l_nss;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                        l_idx = 0;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_NSS, OAL_SIZEOF(mac_cfg_tx_comp_stru));

    /* ��������������������� */
    pst_set_nss_param = (mac_cfg_tx_comp_stru *)(st_write_msg.auc_value);

    /* ��ȡ����ֵ�ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_nss::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��������Ϸ��Լ�� */
    while ('\0' != ac_arg[l_idx])
    {

        if (isdigit(ac_arg[l_idx]))
        {
            l_idx++;
            continue;
        }
        else
        {
            l_idx++;
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_nss::input illegal!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    /* ����Ҫ����Ϊ����ֵ */
    l_nss = oal_atoi(ac_arg);

    if (l_nss < WAL_HIPRIV_NSS_MIN || l_nss > WAL_HIPRIV_NSS_MAX)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_nss::input val out of range [%d]!}\r\n", l_nss);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    pst_set_nss_param->uc_param = (oal_uint8)(l_nss - 1);
    pst_set_nss_param->en_protocol_mode = WLAN_VHT_PHY_PROTOCOL_MODE;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_tx_comp_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_nss::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_rfch
 ��������  : ����ͨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_rfch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
#ifdef _PRE_WLAN_CHIP_TEST
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    mac_cfg_tx_comp_stru             *pst_set_rfch_param;
    oal_uint8                        uc_ch;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int8                         c_ch_idx;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_RFCH, OAL_SIZEOF(mac_cfg_tx_comp_stru));

    /* ��������������������� */
    pst_set_rfch_param = (mac_cfg_tx_comp_stru *)(st_write_msg.auc_value);

    /* ��ȡ����ֵ�ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rfch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ����Ҫ����Ϊ����ֵ */
    uc_ch = 0;
    for (c_ch_idx = 0; c_ch_idx < WAL_HIPRIV_CH_NUM; c_ch_idx++)
    {
        if ('0' == ac_arg[c_ch_idx])
        {
            continue;
        }
        else if ('1' == ac_arg[c_ch_idx])
        {
            uc_ch += (oal_uint8)(1 << (WAL_HIPRIV_CH_NUM - c_ch_idx - 1));
        }
        /* ���������з�01���֣�����������4λ���쳣 */
        else
        {
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_rfch::input err!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    /* �������������λ���쳣 */
    if ('\0' != ac_arg[c_ch_idx])
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_rfch::input err!}\r\n");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    pst_set_rfch_param->uc_param = uc_ch;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_tx_comp_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
    wal_hipriv_wait_rsp(pst_net_dev, pc_param);
#endif

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rfch::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }
#endif
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_always_tx
 ��������  : ���ݳ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_always_tx(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
#if defined (_PRE_WLAN_CHIP_TEST) || defined (_PRE_WLAN_FEATURE_ALWAYS_TX)
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    mac_cfg_tx_comp_stru             *pst_set_bcast_param;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_switch_enum_uint8            en_tx_flag;
    wlan_tx_ack_policy_enum_uint8    en_ack_policy;
    mac_rf_payload_enum_uint8        en_payload_flag;
    oal_uint32                       ul_len;
    mac_vap_stru                    *pst_mac_vap;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_ALWAYS_TX, OAL_SIZEOF(mac_cfg_tx_comp_stru));

    /* ��������������������� */
    pst_set_bcast_param = (mac_cfg_tx_comp_stru *)(st_write_msg.auc_value);

    /* ��ȡ����ģʽ���ر�־ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_tx::get tx_flag return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    en_tx_flag = (oal_uint8)oal_atoi(ac_arg);

    if (en_tx_flag > HAL_ALWAYS_TX_RF)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_always_tx::input should be 0 or 1.}\r\n");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    pst_set_bcast_param->uc_param = en_tx_flag;

    /* ��ȡack_policy���� */
    pc_param = pc_param + ul_off_set;
    ul_ret   = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_tx::get tx_flag return err_code [%d]!}\r\n", ul_ret);
        //return ul_ret;
    }

    if (!oal_strcmp(ac_arg, ""))
    {
        pst_mac_vap = (mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev);
        if (OAL_UNLIKELY(OAL_PTR_NULL  == pst_mac_vap))
        {
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_always_tx::Get mac vap failed.}");
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_set_bcast_param->en_ack_policy = 1;
        pst_set_bcast_param->en_payload_flag = 2;
        pst_set_bcast_param->ul_payload_len = 4000;
    }
    else
    {
    en_ack_policy = (wlan_tx_ack_policy_enum_uint8)oal_atoi(ac_arg);
    if (en_ack_policy >= WLAN_TX_NO_EXPLICIT_ACK)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_tx::ack policy flag err[%d]!}\r\n", en_ack_policy);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }
    pst_set_bcast_param->en_ack_policy = en_ack_policy;

    /* ��ȡpayload_flag���� */
    pc_param = pc_param + ul_off_set;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_tx::wal_get_cmd_one_arg return err_code [%u]!}\r\n", ul_ret);
        return ul_ret;
    }
    en_payload_flag = (mac_rf_payload_enum_uint8)oal_atoi(ac_arg);
    if (en_payload_flag >= RF_PAYLOAD_BUTT)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_tx::payload flag err[%d]!}\r\n", en_payload_flag);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }
    pst_set_bcast_param->en_payload_flag = en_payload_flag;

    /* ��ȡlen���� */
    pc_param = pc_param + ul_off_set;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_tx::wal_get_cmd_one_arg return err_code [%u]!}\r\n", ul_ret);
        return ul_ret;
    }
    ul_len = (oal_uint32)oal_atoi(ac_arg);
    if (ul_len >= 65535)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_tx::len [%u] overflow!}\r\n", ul_len);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }
    pst_set_bcast_param->ul_payload_len = ul_len;
    }

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_tx_comp_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
    wal_hipriv_wait_rsp(pst_net_dev, pc_param);
#endif

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_tx::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_get_thruput
 ��������  : ��ȡоƬ��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��28��
    ��    ��   : �ܺ���
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_thruput(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                        uc_stage;
    oal_int32                        l_idx = 0;

    /* ��ȡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_thruput::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��������Ϸ��Լ�� */
    while ('\0' != ac_arg[l_idx])
    {
        if (isdigit(ac_arg[l_idx]))
        {
            l_idx++;
            continue;
        }
        else
        {
            l_idx++;
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_get_thruput::input illegal!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    /* ���������ֵ�ַ���ת��Ϊ���� */
    uc_stage = (oal_uint8)oal_atoi(ac_arg);

    *(oal_uint8 *)(st_write_msg.auc_value) = uc_stage;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_THRUPUT, OAL_SIZEOF(oal_uint8));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_thruput::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_freq_skew
 ��������  : ����Ƶ�ʾ�ƫ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��24��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_freq_skew(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int8                    ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint16                  us_len;
    oal_uint16                  i;
    oal_uint32                  ul_ret;
    oal_uint32                  ul_off_set;
    mac_cfg_freq_skew_stru      *pst_freq_skew;

    /*             �����ʽ: hipriv "Hisilicon0 set_freq_skew <>"
     * <idx chn T0Int20M T0Frac20M T1Int20M T1Frac20M T0Int40M T0Frac40M T1Int40M T1Frac40M>
     */
    pst_freq_skew = (mac_cfg_freq_skew_stru*)st_write_msg.auc_value;

    /* ����ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_freq_skew::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pst_freq_skew->us_idx = (oal_uint16)oal_atoi(ac_arg);

    /* �ŵ� */
    pc_param += ul_off_set;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_freq_skew::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pst_freq_skew->us_chn = (oal_uint16)oal_atoi(ac_arg);

    /* ��ȡ8��У������ */
    for (i = 0; i < WAL_HIPRIV_FREQ_SKEW_ARG_NUM; i++)
    {
        pc_param += ul_off_set;
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_freq_skew::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
            return ul_ret;
        }
        pst_freq_skew->as_corr_data[i] = (oal_int16)oal_atoi(ac_arg);
    }

    us_len = OAL_SIZEOF(mac_cfg_freq_skew_stru);
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_FREQ_SKEW, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_freq_skew::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_adjust_ppm
 ��������  : ����ppm
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��9��
    ��    ��   : pwx287475
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_adjust_ppm(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int8                    ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint16                  us_len;
    oal_uint32                  ul_ret;
    oal_uint32                  ul_off_set;
    mac_cfg_adjust_ppm_stru     *pst_adjust_ppm;

    /* �����ʽ: hipriv "Hisilicon0 adjust_ppm ppm band clock" */
    pst_adjust_ppm = (mac_cfg_adjust_ppm_stru*)st_write_msg.auc_value;

    /* ppm */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_adjust_ppm::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    if ('-' == ac_arg[0])
    {
        pst_adjust_ppm->c_ppm_val = -(oal_int8)oal_atoi(ac_arg+1);
    }
    else
    {
        pst_adjust_ppm->c_ppm_val = (oal_int8)oal_atoi(ac_arg);
    }


    /* clock */
    pc_param += ul_off_set;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        /* �˲��������ã�����Ĭ��ʱ�����ã�5G 26M 2G 40M */
        pst_adjust_ppm->uc_clock_freq = 0;
    }
    else
    {
        pst_adjust_ppm->uc_clock_freq = (oal_uint8)oal_atoi(ac_arg);
    }

    us_len = OAL_SIZEOF(mac_cfg_adjust_ppm_stru);
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ADJUST_PPM, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_adjust_ppm::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_event_switch
 ��������  : event��ӡ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��5��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_event_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    /* OAM eventģ��Ŀ��ص�����: hipriv "Hisilicon0 event_switch 0 | 1"
        �˴���������"1"��"0"����ac_name
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_event_switch::wal_get_cmd_one_arg return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����eventģ����в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_event_switch::the log switch command is error [%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_EVENT_SWITCH, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_event_switch::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_RF_110X_CALI_DPD
OAL_STATIC oal_uint32 wal_hipriv_start_dpd(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                  st_write_msg;
    oal_int32                           l_ret;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_START_DPD, OAL_SIZEOF(wal_specific_event_type_param_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(wal_specific_event_type_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_ota_beacon_switch
 ��������  : �����Ƿ��ϱ�beacon֡�Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��7��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_ota_beacon_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                  st_write_msg;
    oal_int32                           l_param;
    oal_uint32                          ul_off_set = 0;
    oal_int8                            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_int32                           l_ret;
    oal_uint32                          ul_ret;

    /* OAM otaģ��Ŀ��ص�����: hipriv "Hisilicon0 ota_beacon_switch 0 | 1"
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_ota_beacon_switch::wal_get_cmd_one_arg fails!}\r\n");
        return ul_ret;
    }
    l_param = oal_atoi((const oal_int8 *)ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_OTA_BEACON_SWITCH, OAL_SIZEOF(oal_uint32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_param;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ota_beacon_switch::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_ota_rx_dscr_switch
 ��������  : �����Ƿ��ϱ�rx�������Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��19��
    ��    ��   : z00285102
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_ota_rx_dscr_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                  st_write_msg;
    oal_int32                           l_param;
    oal_uint32                          ul_off_set = 0;
    oal_int8                            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_int32                           l_ret;
    oal_uint32                          ul_ret;

    /* OAM otaģ��Ŀ��ص�����: hipriv "Hisilicon0 ota_rx_dscr_switch 0 | 1"
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_ota_rx_dscr_switch::wal_get_cmd_one_arg fails!}\r\n");
        return ul_ret;
    }

    /* �������� */
    ul_ret = wal_get_cmd_one_arg(pc_param + ul_off_set, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_ota_rx_dscr_switch::wal_get_cmd_one_arg fails!}\r\n");
        return ul_ret;
    }
    l_param = oal_atoi((const oal_int8 *)ac_name);


    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_OTA_RX_DSCR_SWITCH, OAL_SIZEOF(oal_uint32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_param;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ota_rx_dscr_switch::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_ether_switch
 ��������  : ������̫���ϱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��23��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_ether_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                       l_ret;
    oal_uint32                      ul_ret;
    mac_cfg_eth_switch_param_stru   st_eth_switch_param;

    /* "vap0 ether_switch user_macaddr oam_ota_frame_direction_type_enum(֡����) 0|1(����)" */
    OAL_MEMZERO(&st_eth_switch_param, OAL_SIZEOF(mac_cfg_eth_switch_param_stru));

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, st_eth_switch_param.auc_user_macaddr, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ether_switch::wal_hipriv_get_mac_addr return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* ��ȡ��̫��֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ether_switch::wal_get_cmd_one_arg return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_eth_switch_param.en_frame_direction = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ether_switch::wal_get_cmd_one_arg return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    st_eth_switch_param.en_switch = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ETH_SWITCH, OAL_SIZEOF(st_eth_switch_param));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value,
                (const oal_void *)&st_eth_switch_param,
                OAL_SIZEOF(st_eth_switch_param));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_eth_switch_param),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ether_switch::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_80211_ucast_switch
 ��������  : ����80211����֡�ϱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��24��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_80211_ucast_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                       l_ret;
    oal_uint32                      ul_ret;
    mac_cfg_80211_ucast_switch_stru st_80211_ucast_switch;

    /* sh hipriv.sh "vap0 80211_uc_switch user_macaddr 0|1(֡����tx|rx) 0|1(֡����:����֡|����֡)
                                                       0|1(֡���ݿ���) 0|1(CB����) 0|1(����������)"
    */
    OAL_MEMZERO(&st_80211_ucast_switch, OAL_SIZEOF(mac_cfg_80211_ucast_switch_stru));

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, st_80211_ucast_switch.auc_user_macaddr, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_ucast_switch::wal_hipriv_get_mac_addr return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* ��ȡ80211֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_ucast_switch::get 80211 ucast frame direction return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_frame_direction = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_ucast_switch::get ucast frame type return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_frame_type = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡���ݴ�ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_ucast_switch::get ucast frame content switch  return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_frame_switch = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡CB�ֶδ�ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_ucast_switch::get ucast frame cb switch return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_cb_switch = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ��������ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_ucast_switch::get ucast frame dscr switch return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_dscr_switch = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_80211_UCAST_SWITCH, OAL_SIZEOF(st_80211_ucast_switch));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value,
                (const oal_void *)&st_80211_ucast_switch,
                OAL_SIZEOF(st_80211_ucast_switch));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_80211_ucast_switch),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_ucast_switch::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_TXOPPS
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_txop_ps_machw
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
OAL_STATIC oal_uint32  wal_hipriv_set_txop_ps_machw(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                       l_ret;
    oal_uint32                      ul_ret;
    mac_txopps_machw_param_stru     st_txopps_machw_param = {0};

    /* sh hipriv.sh "stavap_name txopps_hw_en 0|1(txop_ps_en) 0|1(condition1) 0|1(condition2)" */

    /* ��ȡtxop psʹ�ܿ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_TXOP, "{wal_hipriv_set_txop_ps_machw::get machw txop_ps en return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_txopps_machw_param.en_machw_txopps_en = (oal_switch_enum_uint8)oal_atoi(ac_name);

    /* ��ȡtxop ps condition1ʹ�ܿ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_TXOP, "{wal_hipriv_set_txop_ps_machw::get machw txop_ps condition1 return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_txopps_machw_param.en_machw_txopps_condition1= (oal_switch_enum_uint8)oal_atoi(ac_name);

    /* ��ȡtxop ps condition2ʹ�ܿ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_TXOP, "{wal_hipriv_set_txop_ps_machw::get machw txop_ps condition2 return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_txopps_machw_param.en_machw_txopps_condition2 = (oal_switch_enum_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TXOP_PS_MACHW, OAL_SIZEOF(st_txopps_machw_param));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value,
                (const oal_void *)&st_txopps_machw_param,
                OAL_SIZEOF(st_txopps_machw_param));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_txopps_machw_param),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_TXOP, "{wal_hipriv_set_txop_ps_machw::return err code[%d]!}\r\n", ul_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_80211_mcast_switch
 ��������  : ����80211�鲥֡�ϱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��24��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_80211_mcast_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                       l_ret;
    oal_uint32                      ul_ret;
    mac_cfg_80211_mcast_switch_stru st_80211_mcast_switch = {0};

    OAL_MEMZERO((oal_uint8*)&st_write_msg, OAL_SIZEOF(st_write_msg));
    /* sh hipriv.sh "Hisilicon0 80211_mc_switch 0|1(֡����tx|rx) 0|1(֡����:����֡|����֡)
                                                0|1(֡���ݿ���) 0|1(CB����) 0|1(����������)"
    */

    /* ��ȡ80211֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_mcast_switch::get 80211 mcast frame direction return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_mcast_switch.en_frame_direction = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_mcast_switch::get mcast frame type return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_mcast_switch.en_frame_type = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡���ݴ�ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_mcast_switch::get mcast frame content switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_mcast_switch.en_frame_switch = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡CB�ֶδ�ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_mcast_switch::get mcast frame cb switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_mcast_switch.en_cb_switch = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ��������ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_mcast_switch::get mcast frame dscr switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_mcast_switch.en_dscr_switch = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_80211_MCAST_SWITCH, OAL_SIZEOF(st_80211_mcast_switch));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value,
                (const oal_void *)&st_80211_mcast_switch,
                OAL_SIZEOF(st_80211_mcast_switch));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_80211_mcast_switch),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_mcast_switch::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_all_80211_ucast
 ��������  : ���������û���80211����֡�ϱ����أ��˿��������Ժ������û��ϱ�����
             ��ͬ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��24��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_all_80211_ucast(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    mac_cfg_80211_ucast_switch_stru st_80211_ucast_switch;
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;


    /* sh hipriv.sh "Hisilicon0 80211_uc_all 0|1(֡����tx|rx) 0|1(֡����:����֡|����֡)
                                             0|1(֡���ݿ���) 0|1(CB����) 0|1(����������)"
    */

    OAL_MEMZERO(&st_80211_ucast_switch, OAL_SIZEOF(mac_cfg_80211_ucast_switch_stru));

    /* ��ȡ80211֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_all_80211_ucast::get 80211 ucast frame direction return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_frame_direction = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_all_80211_ucast::get ucast frame type return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_frame_type = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡���ݴ�ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_all_80211_ucast::get ucast frame content switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_frame_switch = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡CB�ֶδ�ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_all_80211_ucast::get ucast frame cb switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_cb_switch = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ��������ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_all_80211_ucast::get ucast frame dscr switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_80211_ucast_switch.en_dscr_switch = (oal_uint8)oal_atoi(ac_name);


    /* ���ù㲥mac��ַ */
    oal_memcopy(st_80211_ucast_switch.auc_user_macaddr, BROADCAST_MACADDR, WLAN_MAC_ADDR_LEN);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_80211_UCAST_SWITCH, OAL_SIZEOF(st_80211_ucast_switch));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value,
                (const oal_void *)&st_80211_ucast_switch,
                OAL_SIZEOF(st_80211_ucast_switch));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_80211_ucast_switch),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_all_ucast_switch::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_all_ether_switch
 ��������  : ���������û�����̫��֡�ϱ����أ��˿��������Ժ������û��ϱ�����
             ��ͬ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��24��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_all_ether_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_uint8                       uc_user_num;
    oal_uint8                       uc_frame_direction;
    oal_uint8                       uc_switch;

    /* sh hipriv.sh "Hisilicon0 ether_all 0|1(֡����tx|rx) 0|1(����)" */

    /* ��ȡ��̫��֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_all_ether_switch::get eth frame direction return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    uc_frame_direction = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_all_ether_switch::get eth type return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    uc_switch = (oal_uint8)oal_atoi(ac_name);

    /* ���ÿ��� */
    for (uc_user_num = 0; uc_user_num < WLAN_ACTIVE_USER_MAX_NUM + WLAN_MAX_MULTI_USER_NUM_SPEC; uc_user_num++)
    {
        oam_report_eth_frame_set_switch(uc_user_num, uc_switch, uc_frame_direction);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_dhcp_arp_switch
 ��������  : ���÷��͹㲥dhcp��arp����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��27��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_dhcp_arp_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint8                       uc_switch;

    /* sh hipriv.sh "Hisilicon0 dhcp_arp_switch 0|1(����)" */

    /* ��ȡ֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_dhcp_arp_switch::get switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    uc_switch = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_DHCP_ARP, OAL_SIZEOF(oal_uint32));
    *((oal_int32 *)(st_write_msg.auc_value)) = (oal_uint32)uc_switch;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_dhcp_arp_switch::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : wal_hipriv_report_vap_info
 ��������  : �����·��Ķ�Ӧ���λ���ϱ���Ӧ��vap��Ϣ
 �������  : oal_net_device_stru *pst_net_dev,
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��20��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_report_vap_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_uint32                      ul_flag_value;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;

    /* sh hipriv.sh "wlan0 report_vap_info  flags_value" */

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_vap_info::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    ul_flag_value = (oal_uint32)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_REPORT_VAP_INFO, OAL_SIZEOF(ul_flag_value));

    /* ��д��Ϣ�壬���� */
    *(oal_uint32 *)(st_write_msg.auc_value) = ul_flag_value;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(ul_flag_value),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_vap_info::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_rssi_switch
 ��������  : ���ô�ӡ���ձ��ĵ�rssi�Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��6��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_rssi_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    mac_rssi_debug_switch_stru      st_rssi_switch;
    oal_int32                       l_ret;
    oal_uint32                      ul_ret;

    /* sh hipriv.sh "Hisilicon0 rssi_switch  0|1(�ر�|��) N(ÿ��N�����Ĵ�ӡһ��)" */

    OAL_MEMZERO(&st_rssi_switch, OAL_SIZEOF(st_rssi_switch));

    /* ��ȡ֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rssi_switch::get rssi switch on, return err_code[%d]!}", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_rssi_switch.ul_rssi_debug_switch = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡���ݴ�ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rssi_switch::get rx comp isr interval switch info, return err_code[%d]!}", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_rssi_switch.ul_rx_comp_isr_interval = (oal_uint8)oal_atoi(ac_name);

    OAM_INFO_LOG2(0, OAM_SF_ANY, "{wal_hipriv_set_rssi_switch::rssi_switch: %d, interval: %d.}",
                  st_rssi_switch.ul_rssi_debug_switch, st_rssi_switch.ul_rx_comp_isr_interval);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_RSSI_SWITCH, OAL_SIZEOF(st_rssi_switch));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value,
                (const oal_void *)&st_rssi_switch,
                OAL_SIZEOF(st_rssi_switch));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_rssi_switch),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rssi_switch::return err code[%d]!}", ul_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_probe_switch
 ��������  : ����probe request��probe response�ϱ��Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��30��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_probe_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                       l_ret;
    oal_uint32                      ul_ret;
    mac_cfg_probe_switch_stru       st_probe_switch;

    /* sh hipriv.sh "Hisilicon0 probe_switch 0|1(֡����tx|rx) 0|1(֡���ݿ���)
                                             0|1(CB����) 0|1(����������)"
    */

    /* ��ȡ֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_probe_switch::get probe direction return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_probe_switch.en_frame_direction = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡���ݴ�ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_probe_switch::get probe frame content switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_probe_switch.en_frame_switch = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ֡CB�ֶδ�ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_probe_switch::get probe frame cb switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_probe_switch.en_cb_switch = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ��������ӡ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_probe_switch::get probe frame dscr switch return err_code[%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    st_probe_switch.en_dscr_switch = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PROBE_SWITCH, OAL_SIZEOF(st_probe_switch));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value,
                (const oal_void *)&st_probe_switch,
                OAL_SIZEOF(st_probe_switch));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_probe_switch),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_80211_ucast_switch::return err code[%d]!}\r\n", ul_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_get_mpdu_num
 ��������  : ��ȡdevice��ÿһ��tid�µ�ǰmpdu��Ŀ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��17��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_mpdu_num(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int32                       l_ret;
    oal_uint32                      ul_ret;
    mac_cfg_get_mpdu_num_stru       st_param;

    /* sh hipriv.sh "vap_name mpdu_num user_macaddr" */

    OAL_MEMZERO(&st_param, OAL_SIZEOF(mac_cfg_get_mpdu_num_stru));

    /* ��ȡ�û�mac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, st_param.auc_user_macaddr, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_MPDU_NUM, OAL_SIZEOF(st_param));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value,
                (const oal_void *)&st_param,
                OAL_SIZEOF(st_param));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_param),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_all_ota
 ��������  : ���������û�֡�ϱ������п��أ������1�����ϱ���������֡��֡���ݣ�
             cb�ֶΣ��������������0����ʲô�����ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��17��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

  1.��    ��   : 2015��1��23��
    ��    ��   : w00316376
    �޸�����   : �������¼���wal�㴦��

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_all_ota(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                       l_param;
    wal_msg_write_stru              st_write_msg;

    /* ��ȡ���� sh hipriv.sh "Hisilicon0 set_all_ota 0|1"*/
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    l_param = oal_atoi((const oal_int8 *)ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_ALL_OTA, OAL_SIZEOF(oal_uint32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_param;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_all_ota::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_oam_output
 ��������  : ����oamģ������λ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��3��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_oam_output(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;
    oal_int32                   l_ret;

    /* OAM logģ��Ŀ��ص�����: hipriv "Hisilicon0 log_level 0~3"
        �˴���������"1"��"0"����ac_name
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_oam_output::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����logģ����в�ͬ������ ȡֵ:oam_output_type_enum_uint8 */
    l_tmp = oal_atoi(ac_name);
    if (l_tmp >= OAM_OUTPUT_TYPE_BUTT)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_oam_output::output type invalid [%d]!}\r\n", l_tmp);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_OAM_OUTPUT_TYPE,  OAL_SIZEOF(oal_int32));
    /* ��������������� */
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_oam_output::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_ampdu_start
 ��������  : ����ampdu��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_ampdu_start(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                 st_write_msg;
    oal_uint32                         ul_off_set;
    oal_int8                           ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                         ul_ret;
    oal_int32                          l_ret;
    mac_cfg_ampdu_start_param_stru    *pst_ampdu_start_param;
    mac_cfg_ampdu_start_param_stru     st_ampdu_start_param;  /* ��ʱ�����ȡ��use����Ϣ */
    oal_uint32                         ul_get_addr_idx;

    /*
        ����AMPDU��������������: hipriv "Hisilicon0  ampdu_start xx xx xx xx xx xx(mac��ַ) tidno ack_policy"
    */

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_start::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    OAL_MEMZERO((oal_uint8*)&st_ampdu_start_param, OAL_SIZEOF(st_ampdu_start_param));
    oal_strtoaddr(ac_name, st_ampdu_start_param.auc_mac_addr);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡtid */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_start::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    if (OAL_STRLEN(ac_name) > 2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_start::the ampdu start command is erro [%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    st_ampdu_start_param.uc_tidno = (oal_uint8)oal_atoi(ac_name);
    if (st_ampdu_start_param.uc_tidno >= WLAN_TID_MAX_NUM)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_start::the ampdu start command is error! uc_tidno is  [%d]!}\r\n", st_ampdu_start_param.uc_tidno);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_AMPDU_START, OAL_SIZEOF(mac_cfg_ampdu_start_param_stru));

    /* ��������������� */
    pst_ampdu_start_param = (mac_cfg_ampdu_start_param_stru *)(st_write_msg.auc_value);
    for (ul_get_addr_idx = 0; ul_get_addr_idx < WLAN_MAC_ADDR_LEN; ul_get_addr_idx++)
    {
        pst_ampdu_start_param->auc_mac_addr[ul_get_addr_idx] = st_ampdu_start_param.auc_mac_addr[ul_get_addr_idx];
    }

    pst_ampdu_start_param->uc_tidno = st_ampdu_start_param.uc_tidno;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_ampdu_start_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_start::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_auto_ba_switch
 ��������  : �����Զ�BA�Ự�Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��20��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_auto_ba_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    /* �����Զ���ʼBA�Ự�Ŀ���:hipriv "vap0  auto_ba 0 | 1" ���������ĳһ��VAP */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_auto_ba_switch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����AUTO BA���в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_auto_ba_switch::the auto ba switch command is error[%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_AUTO_BA_SWITCH, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_auto_ba_switch::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_profiling_switch
 ��������  : �����Զ�BA�Ự�Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��20��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_profiling_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    /* �����Զ���ʼBA�Ự�Ŀ���:hipriv "vap0  profiling 0 | 1" ���������ĳһ��VAP */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_profiling_switch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����AUTO BA���в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_profiling_switch::the profiling switch command is error[%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PROFILING_SWITCH, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_profiling_switch::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_addba_req
 ��������  : ����BA�Ự�ĵ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_addba_req(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_addba_req_param_stru   *pst_addba_req_param;
    mac_cfg_addba_req_param_stru    st_addba_req_param;     /* ��ʱ�����ȡ��addba req����Ϣ */
    oal_uint32                      ul_get_addr_idx;

    /*
        ����AMPDU�رյ���������:
        hipriv "Hisilicon0 addba_req xx xx xx xx xx xx(mac��ַ) tidno ba_policy buffsize timeout"
    */

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addba_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    OAL_MEMZERO((oal_uint8*)&st_addba_req_param, OAL_SIZEOF(st_addba_req_param));
    oal_strtoaddr(ac_name, st_addba_req_param.auc_mac_addr);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡtid */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addba_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    if (OAL_STRLEN(ac_name) > 2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addba_req::the addba req command is error[%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    st_addba_req_param.uc_tidno = (oal_uint8)oal_atoi(ac_name);
    if (st_addba_req_param.uc_tidno >= WLAN_TID_MAX_NUM)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addba_req::the addba req command is error!uc_tidno is [%d]!}\r\n", st_addba_req_param.uc_tidno);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    pc_param = pc_param + ul_off_set;

    /* ��ȡba_policy */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addba_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    st_addba_req_param.en_ba_policy = (oal_uint8)oal_atoi(ac_name);
    if (MAC_BA_POLICY_IMMEDIATE != st_addba_req_param.en_ba_policy)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addba_req::the ba policy is not correct! ba_policy is[%d]!}\r\n", st_addba_req_param.en_ba_policy);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    pc_param = pc_param + ul_off_set;

    /* ��ȡbuffsize */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addba_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    st_addba_req_param.us_buff_size = (oal_uint16)oal_atoi(ac_name);

    pc_param = pc_param + ul_off_set;

    /* ��ȡtimeoutʱ�� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addba_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    st_addba_req_param.us_timeout = (oal_uint16)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ADDBA_REQ, OAL_SIZEOF(mac_cfg_addba_req_param_stru));

    /* ��������������� */
    pst_addba_req_param = (mac_cfg_addba_req_param_stru *)(st_write_msg.auc_value);
    for (ul_get_addr_idx = 0; ul_get_addr_idx < WLAN_MAC_ADDR_LEN; ul_get_addr_idx++)
    {
        pst_addba_req_param->auc_mac_addr[ul_get_addr_idx] = st_addba_req_param.auc_mac_addr[ul_get_addr_idx];
    }

    pst_addba_req_param->uc_tidno     = st_addba_req_param.uc_tidno;
    pst_addba_req_param->en_ba_policy = st_addba_req_param.en_ba_policy;
    pst_addba_req_param->us_buff_size = st_addba_req_param.us_buff_size;
    pst_addba_req_param->us_timeout   = st_addba_req_param.us_timeout;


    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_addba_req_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addba_req::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_delba_req
 ��������  : ɾ��BA�Ự�ĵ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��7��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_delba_req(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_delba_req_param_stru   *pst_delba_req_param;
    mac_cfg_delba_req_param_stru    st_delba_req_param;     /* ��ʱ�����ȡ��addba req����Ϣ */
    oal_uint32                      ul_get_addr_idx;

    /*
        ����AMPDU�رյ���������:
        hipriv "Hisilicon0 delba_req xx xx xx xx xx xx(mac��ַ) tidno direction reason_code"
    */

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delba_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    OAL_MEMZERO((oal_uint8*)&st_delba_req_param, OAL_SIZEOF(st_delba_req_param));
    oal_strtoaddr(ac_name, st_delba_req_param.auc_mac_addr);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡtid */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delba_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    if (OAL_STRLEN(ac_name) > 2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delba_req::the delba_req req command is error[%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    st_delba_req_param.uc_tidno = (oal_uint8)oal_atoi(ac_name);
    if (st_delba_req_param.uc_tidno >= WLAN_TID_MAX_NUM)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delba_req::the delba_req req command is error! uc_tidno is[%d]!}\r\n", st_delba_req_param.uc_tidno);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    pc_param = pc_param + ul_off_set;

    /* ��ȡdirection */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delba_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    st_delba_req_param.en_direction = (oal_uint8)oal_atoi(ac_name);
    if (st_delba_req_param.en_direction >= MAC_BUTT_DELBA)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delba_req::the direction is not correct! direction is[%d]!}\r\n", st_delba_req_param.en_direction);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DELBA_REQ, OAL_SIZEOF(mac_cfg_delba_req_param_stru));

    /* ��������������� */
    pst_delba_req_param = (mac_cfg_delba_req_param_stru *)(st_write_msg.auc_value);
    for (ul_get_addr_idx = 0; ul_get_addr_idx < WLAN_MAC_ADDR_LEN; ul_get_addr_idx++)
    {
        pst_delba_req_param->auc_mac_addr[ul_get_addr_idx] = st_delba_req_param.auc_mac_addr[ul_get_addr_idx];
    }

    pst_delba_req_param->uc_tidno       = st_delba_req_param.uc_tidno;
    pst_delba_req_param->en_direction   = st_delba_req_param.en_direction;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_delba_req_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delba_req::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_WMMAC
/*****************************************************************************
 �� �� ��  : wal_hipriv_addts_req
 ��������  : ����ADDTS REQ�ĵ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��9��13��
    ��    ��   : l00357925
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_addts_req(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                   st_write_msg;
    oal_uint32                           ul_off_set;
    oal_int8                             ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                           ul_ret;
    oal_int32                            l_ret;
    mac_cfg_wmm_tspec_stru_param_stru    *pst_addts_req_param;
    mac_cfg_wmm_tspec_stru_param_stru    st_addts_req_param;     /* ��ʱ�����ȡ��addts req����Ϣ */

    /*
    ���÷���ADDTS REQ��������:
    hipriv "vap0 addts_req tid direction psb up nominal_msdu_size maximum_data_rate
            minimum_data_rate mean_data_rate peak_data_rate minimum_phy_rate surplus_bandwidth_allowance"
   */

 /***********************************************************************************************
 TSPEC�ֶ�:
          --------------------------------------------------------------------------------------
          |TS Info|Nominal MSDU Size|Max MSDU Size|Min Serv Itvl|Max Serv Itvl|
          ---------------------------------------------------------------------------------------
 Octets:  | 3     |  2              |   2         |4            |4            |
          ---------------------------------------------------------------------------------------
          | Inactivity Itvl | Suspension Itvl | Serv Start Time |Min Data Rate | Mean Data Rate |
          ---------------------------------------------------------------------------------------
 Octets:  |4                | 4               | 4               |4             |  4             |
          ---------------------------------------------------------------------------------------
          |Peak Data Rate|Burst Size|Delay Bound|Min PHY Rate|Surplus BW Allowance  |Medium Time|
          ---------------------------------------------------------------------------------------
 Octets:  |4             |4         | 4         | 4          |  2                   |2          |
          ---------------------------------------------------------------------------------------

 TS info�ֶ�:
          ---------------------------------------------------------------------------------------
          |Reserved |TSID |Direction |1 |0 |Reserved |PSB |UP |Reserved |Reserved |Reserved |
          ---------------------------------------------------------------------------------------
   Bits:  |1        |4    |2         |  2  |1        |1   |3  |2        |1        |7        |
          ----------------------------------------------------------------------------------------

 ***********************************************************************************************/

    /* ��ȡtid��ȡֵ��Χ0~7 */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    if (OAL_STRLEN(ac_name) > 2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::the addba req command is error[%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    st_addts_req_param.ts_info.bit_tsid= (oal_uint16)oal_atoi(ac_name);
    if (WLAN_TID_MAX_NUM <= st_addts_req_param.ts_info.bit_tsid)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::the addts req command is error!uc_tidno is [%d]!}\r\n", st_addts_req_param.ts_info.bit_tsid);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    pc_param = pc_param + ul_off_set;

    /* ��ȡdirection 00:uplink 01:downlink 10:reserved 11:Bi-directional */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    st_addts_req_param.ts_info.bit_direction= (oal_uint16)oal_atoi(ac_name);
    if (MAC_WMMAC_DIRECTION_RESERVED == st_addts_req_param.ts_info.bit_direction)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::the direction is not correct! direction is[%d]!}\r\n", st_addts_req_param.ts_info.bit_direction);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    pc_param = pc_param + ul_off_set;

    /* ��ȡPSB��1��ʾU-APSD��0��ʾlegacy */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    st_addts_req_param.ts_info.bit_apsd= (oal_uint16)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡUP */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    st_addts_req_param.ts_info.bit_user_prio= (oal_uint16)oal_atoi(ac_name);

    pc_param = pc_param + ul_off_set;

    /* ��ȡNominal MSDU Size ,��һλΪ1 */
    /*
        ------------
        |fixed|size|
        ------------
 bits:  |1    |15  |
        ------------
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    st_addts_req_param.us_norminal_msdu_size = (oal_uint16)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡmaximum MSDU size */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    st_addts_req_param.us_max_msdu_size = (oal_uint16)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;


    /* ��ȡminimum data rate */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    st_addts_req_param.ul_min_data_rate = (oal_uint32)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡmean data rate */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    st_addts_req_param.ul_mean_data_rate = (oal_uint32)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡpeak data rate */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    st_addts_req_param.ul_peak_data_rate = (oal_uint32)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡminimum PHY Rate */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    st_addts_req_param.ul_min_phy_rate = (oal_uint32)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡsurplus bandwidth allowance */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    st_addts_req_param.us_surplus_bw = (oal_uint16)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ADDTS_REQ, OAL_SIZEOF(mac_cfg_wmm_tspec_stru_param_stru));

    /* ��������������� */
    pst_addts_req_param = (mac_cfg_wmm_tspec_stru_param_stru *)(st_write_msg.auc_value);

    pst_addts_req_param->ts_info.bit_tsid        = st_addts_req_param.ts_info.bit_tsid;
    pst_addts_req_param->ts_info.bit_direction   = st_addts_req_param.ts_info.bit_direction;
    pst_addts_req_param->ts_info.bit_apsd        = st_addts_req_param.ts_info.bit_apsd;
    pst_addts_req_param->ts_info.bit_user_prio   = st_addts_req_param.ts_info.bit_user_prio;
    pst_addts_req_param->us_norminal_msdu_size   = st_addts_req_param.us_norminal_msdu_size;
    pst_addts_req_param->us_max_msdu_size        = st_addts_req_param.us_max_msdu_size;
    pst_addts_req_param->ul_min_data_rate        = st_addts_req_param.ul_min_data_rate;
    pst_addts_req_param->ul_mean_data_rate       = st_addts_req_param.ul_mean_data_rate;
    pst_addts_req_param->ul_peak_data_rate       = st_addts_req_param.ul_peak_data_rate;
    pst_addts_req_param->ul_min_phy_rate         = st_addts_req_param.ul_min_phy_rate;
    pst_addts_req_param->us_surplus_bw           = st_addts_req_param.us_surplus_bw;


    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_wmm_tspec_stru_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_addts_req::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_delts
 ��������  : ����DELTS�ĵ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��9��13��
    ��    ��   : l00357925
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_delts(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                   st_write_msg;
    oal_uint32                           ul_off_set;
    oal_int8                             ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                           ul_ret;
    oal_int32                            l_ret;
    mac_cfg_wmm_tspec_stru_param_stru   *pst_delts_param;
    mac_cfg_wmm_tspec_stru_param_stru    st_delts_param;

    /* ����ɾ��TS����������: hipriv "Hisilicon0 delts tidno" */

    /* ��ȡtsid */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delts::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    st_delts_param.ts_info.bit_tsid = (oal_uint8)oal_atoi(ac_name);
    if (st_delts_param.ts_info.bit_tsid >= WLAN_TID_MAX_NUM)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delts::the delts command is error! tsid is[%d]!}\r\n", st_delts_param.ts_info.bit_tsid);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DELTS, OAL_SIZEOF(mac_cfg_wmm_tspec_stru_param_stru));

    /* ��������������� */
    pst_delts_param = (mac_cfg_wmm_tspec_stru_param_stru *)(st_write_msg.auc_value);
    OAL_MEMZERO(pst_delts_param, OAL_SIZEOF(mac_cfg_wmm_tspec_stru_param_stru));

    pst_delts_param->ts_info.bit_tsid      = st_delts_param.ts_info.bit_tsid;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_wmm_tspec_stru_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delts::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_wmmac_switch
 ��������  : ����WMMAC�Ŀ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��9��13��
    ��    ��   : l00357925
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_wmmac_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                   st_write_msg;
    oal_uint32                           ul_off_set;
    oal_int8                             ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                           ul_ret;
    oal_int32                            l_ret;
    oal_uint8                            uc_wmmac_switch;

    /* ����ɾ��TS����������: hipriv "Hisilicon0 wmmac_switch 1/0" */

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delts::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    uc_wmmac_switch = (oal_uint8)oal_atoi(ac_name);
    if (uc_wmmac_switch != OAL_FALSE)
    {
        uc_wmmac_switch = OAL_TRUE;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    /* ��������������� */
    OAL_MEMZERO(st_write_msg.auc_value, OAL_SIZEOF(oal_uint8));
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_wmmac_switch;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_WMMAC_SWITCH, OAL_SIZEOF(oal_uint8));
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_delts::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_reassoc_req
 ��������  : ���÷����ع�������֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��9��24��
    ��    ��   : l00357925
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_reassoc_req(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
        ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_REASSOC_REQ, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_reassoc_req::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


#endif
/*****************************************************************************
 �� �� ��  : wal_hipriv_mem_info
 ��������  : ��ӡִ���ڴ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_mem_info(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    oal_int8                     auc_token[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_mem_pool_id_enum_uint8   en_pool_id;
    oal_uint32                   ul_off_set;
    oal_uint32                   ul_ret;

    /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_cfg_net_dev) || OAL_UNLIKELY(OAL_PTR_NULL == pc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_mem_info::pst_net_dev or pc_param null ptr error [%d] [%d]!}\r\n", pst_cfg_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�ڴ��ID */
    ul_ret = wal_get_cmd_one_arg(pc_param, auc_token, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_mem_info::wal_get_cmd_one_arg return error code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    en_pool_id = (oal_mem_pool_id_enum_uint8)oal_atoi(auc_token);

    /* ��ӡ�ڴ����Ϣ */
    oal_mem_info(en_pool_id);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_mem_leak
 ��������  : ���ָ���ڴ��й©�ڴ��(hipriv "Hisilicon0 memleak poolid")
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��29��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_mem_leak(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    oal_int8                     auc_token[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_mem_pool_id_enum_uint8   en_pool_id;
    oal_uint32                   ul_off_set;
    oal_uint32                   ul_ret;

    /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_cfg_net_dev) || OAL_UNLIKELY(OAL_PTR_NULL == pc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_mem_leak::pst_net_dev or pc_param null ptr error [%d] [%d]!}\r\n", pst_cfg_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�ڴ��ID */
    ul_ret = wal_get_cmd_one_arg(pc_param, auc_token, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_mem_leak::wal_get_cmd_one_arg return error code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    en_pool_id = (oal_mem_pool_id_enum_uint8)oal_atoi(auc_token);
    if (en_pool_id > OAL_MEM_POOL_ID_SDT_NETBUF)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_mem_leak::mem pool id exceeds,en_pool_id[%d]!}\r\n", en_pool_id);
        return OAL_SUCC;
    }

    /* ����ڴ��й©�ڴ�� */
    oal_mem_leak(en_pool_id);

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : wal_hipriv_mem_leak
 ��������  : ���ָ���ڴ��й©�ڴ��(hipriv "Hisilicon0 memleak poolid")
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_device_mem_leak(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                st_write_msg;
    oal_uint32                        ul_off_set;
    oal_int8                          ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                        ul_ret;
    oal_int32                         l_ret;
    oal_uint8                         uc_pool_id;
    mac_device_pool_id_stru          *pst_pool_id_param;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_device_mem_leak::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_pool_id = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DEVICE_MEM_LEAK, OAL_SIZEOF(mac_device_pool_id_stru));

    /* ��������������� */
    pst_pool_id_param = (mac_device_pool_id_stru *)(st_write_msg.auc_value);
    pst_pool_id_param->uc_pool_id   = uc_pool_id;

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_device_pool_id_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_PWR, "{wal_hipriv_device_mem_leak::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_memory_info
 ��������  : ���host����device���ڴ��ʹ��״��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��23��
    ��    ��   : l00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_memory_info(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    oal_uint32                        ul_off_set;
    oal_int8                          ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                        ul_ret;
    wal_msg_write_stru                st_write_msg;
    oal_int32                         l_ret;
    oal_uint8                         uc_pool_id;
    mac_device_pool_id_stru          *pst_pool_id_param;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_memory_info::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    if(0 == (oal_strcmp("host", ac_name)))
    {
        oal_mem_print_pool_info();
    }
    else if(0 == (oal_strcmp("device", ac_name)))
    {
        hcc_print_device_mem_info();
    }
    else
    {
        uc_pool_id = (oal_uint8)oal_atoi(ac_name);
        /***************************************************************************
                                 ���¼���wal�㴦��
        ***************************************************************************/
        WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DEVICE_MEM_INFO, OAL_SIZEOF(mac_device_pool_id_stru));

        /* ��������������� */
        pst_pool_id_param = (mac_device_pool_id_stru *)(st_write_msg.auc_value);
        pst_pool_id_param->uc_pool_id   = uc_pool_id;

        l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                                   WAL_MSG_TYPE_WRITE,
                                   WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_device_pool_id_stru),
                                   (oal_uint8 *)&st_write_msg,
                                   OAL_FALSE,
                                   OAL_PTR_NULL);

        if (OAL_UNLIKELY(OAL_SUCC != l_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_PWR, "{wal_hipriv_memory_info::return err code [%d]!}\r\n", l_ret);
            return (oal_uint32)l_ret;
        }

    }

    return OAL_SUCC;
}

#endif


/*****************************************************************************
 �� �� ��  : wal_get_dbb_scaling_index
 ��������  : ��ȡdbb scaling��Ӧ������ֵ

 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��11��
    ��    ��   : liuweiqiang
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_int8  wal_get_dbb_scaling_index(oal_uint8 uc_band,
                                                                    oal_uint8 uc_bw,
                                                                    oal_int8 *pc_mcs_type,
                                                                    oal_int8 *pc_mcs_value)
{
    oal_int8                *pc_end;
    oal_bool_enum_uint8     en_mcs_found = OAL_FALSE;
    oal_int8               *rate_table[MAC_DBB_SCALING_2G_RATE_NUM] = {"1","2","5.5","11","6","9","12","18","24","36","48","54"};
    oal_uint8               uc_scaling_offset = 0;
    oal_uint8               uc_mcs_index = 0;

    if (0 == uc_band)
    {//2g band
        if (0 == oal_strcmp(pc_mcs_type, "rate"))
        {//rate xxx
            uc_scaling_offset = MAC_DBB_SCALING_2G_RATE_OFFSET;
            for (uc_mcs_index = 0; uc_mcs_index < MAC_DBB_SCALING_2G_RATE_NUM; uc_mcs_index++)
            {
                if (0 == oal_strcmp(pc_mcs_value, rate_table[uc_mcs_index]))
                {
                    en_mcs_found = OAL_TRUE;
                    break;
                }
            }
            if (en_mcs_found) {
                uc_scaling_offset += uc_mcs_index;
            }
        }
        else if (0 == oal_strcmp(pc_mcs_type, "mcs"))
        {//mcs xxx
            if (20 == uc_bw)
            {//HT20
                uc_scaling_offset = MAC_DBB_SCALING_2G_HT20_MCS_OFFSET;
            }
            else if (40 == uc_bw)
            {//HT40
                uc_scaling_offset = MAC_DBB_SCALING_2G_HT40_MCS_OFFSET;
            }
            else
            {
                OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_dbb_scaling_amend:: 2G uc_bw out of range.");
                return -1;
            }
            uc_mcs_index = (oal_uint8)oal_strtol(pc_mcs_value, &pc_end, 10);
            if (uc_mcs_index <= 7)
            {
                en_mcs_found = OAL_TRUE;
                uc_scaling_offset += uc_mcs_index;
            }
            if ((40 == uc_bw) && (uc_mcs_index == 32))
            {//2.4G mcs32
                en_mcs_found = OAL_TRUE;
                uc_scaling_offset = MAC_DBB_SCALING_2G_HT40_MCS32_OFFSET;
            }
        }
    }
    else
    {//5g band
        if (0 == oal_strcmp(pc_mcs_type, "rate"))
        {//rate xxx
            uc_scaling_offset = MAC_DBB_SCALING_5G_RATE_OFFSET;
            for (uc_mcs_index = 0; uc_mcs_index < MAC_DBB_SCALING_5G_RATE_NUM; uc_mcs_index++)
            {
                if (0 == oal_strcmp(pc_mcs_value, rate_table[uc_mcs_index+4]))
                {
                    en_mcs_found = OAL_TRUE;
                    break;
                }
            }
            if (en_mcs_found) {
                uc_scaling_offset += uc_mcs_index;
            }
        }
        else if (0 == oal_strcmp(pc_mcs_type, "mcs"))
        {//mcs
            uc_mcs_index = (oal_uint8)oal_strtol(pc_mcs_value, &pc_end, 10);
            if (20 == uc_bw)
            {//HT20
                uc_scaling_offset = MAC_DBB_SCALING_5G_HT20_MCS_OFFSET;
                if (uc_mcs_index <= 7)
                {//HT20 mcs0~7
                    en_mcs_found = OAL_TRUE;
                    uc_scaling_offset += uc_mcs_index;
                }
                else if (uc_mcs_index == 8)
                {// HT20 mcs8
                    en_mcs_found = OAL_TRUE;
                    uc_scaling_offset = MAC_DBB_SCALING_5G_HT20_MCS8_OFFSET;
                }
            }
            else if (40 == uc_bw)
            {//HT40
                uc_scaling_offset = MAC_DBB_SCALING_5G_HT40_MCS_OFFSET;
                if (uc_mcs_index <= 9)
                {//HT20 mcs0~9
                    en_mcs_found = OAL_TRUE;
                    uc_scaling_offset += uc_mcs_index;
                }
                else if (uc_mcs_index == 32)
                {//5G mcs32
                    en_mcs_found = OAL_TRUE;
                    uc_scaling_offset = MAC_DBB_SCALING_5G_HT40_MCS32_OFFSET;
                }
            }
            else
            {
                OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_dbb_scaling_amend:: 5G mcs uc_bw out of range.");
                return -1;
            }
        }
        else if (0 == oal_strcmp(pc_mcs_type, "mcsac"))
        {//mcsac
            uc_mcs_index = (oal_uint8)oal_strtol(pc_mcs_value, &pc_end, 10);
            if (80 == uc_bw)
            {
                uc_scaling_offset = MAC_DBB_SCALING_5G_HT80_MCS_OFFSET;
                if (uc_mcs_index <= 9)
                {//HT20 mcs0~7
                    en_mcs_found = OAL_TRUE;
                    uc_scaling_offset += uc_mcs_index;
                }
                if ((uc_mcs_index == 0) || (uc_mcs_index == 1))
                {
                    uc_scaling_offset -= MAC_DBB_SCALING_5G_HT80_MCS0_DELTA_OFFSET;
                }
            }
            else
            {
                OAM_WARNING_LOG0(0, OAM_SF_CFG, "{dmac_config_dbb_scaling_amend:: 5G mcsac uc_bw out of range.");
                return -1;
            }
        }
    }
    if (en_mcs_found)
    {
        return (oal_int8)uc_scaling_offset;
    }
    return -1;
}


/*****************************************************************************
 �� �� ��  : wal_dbb_scaling_amend_calc
 ��������  : ͨ���޸�dbb scaling �Ĵ���ֵ�޸�TX Power

 �������  : sh hipriv.sh "wlan0 dbb_scaling_amend band 0 bw 20 mcs 0 287"
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��11��
    ��    ��   : liuweiqiang
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  wal_dbb_scaling_amend_calc(oal_int8 *pc_param, mac_cfg_dbb_scaling_stru *pst_dbb_scaling)
{
    oal_int8                *pc_token;
    oal_int8                *pc_end;
    oal_int8                *pc_ctx;
    oal_int8                *pc_sep = " ";
    oal_int8                *pc_mcs_type;
    oal_int8                *pc_mcs_value;
    oal_uint8               uc_band;
    oal_uint8               uc_bw;
    oal_int8                uc_scaling_offset;
    oal_uint16              us_delta_gain = (1 << MAC_DBB_SCALING_FIX_POINT_BITS);
    oal_uint8               uc_offset_addr_a = 0;
    oal_uint8               uc_offset_addr_b = 0;

    if (NULL == pc_param)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: param1 NULL!.");
        return OAL_FAIL;
    }

    /* ��ȡband�ַ��� */
    pc_token = oal_strtok(pc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: param2 NULL!.");
        return OAL_FAIL;
    }
    if (0 != oal_strcmp(pc_token, "band"))
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: band not match.");
        return OAL_FAIL;
    }

    /* ��ȡbandֵ*/
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: param3 NULL!.");
        return OAL_FAIL;
    }
    uc_band = (oal_uint8)oal_strtol(pc_token, &pc_end, 10);
    if ((0 != uc_band) && (1 != uc_band))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: band = %d, value out of range.", uc_band);
        return OAL_FAIL;
    }

    /* ��ȡbw�ַ��� */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: param4 NULL!.");
        return OAL_FAIL;
    }
    //OAM_WARNING_LOG2(0, OAM_SF_CFG, "{dmac_config_dbb_scaling_amend:: bw: %c%c.", pc_token[0], pc_token[1]);
    if (0 != oal_strcmp(pc_token, "bw"))
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: bw not match.");
        return OAL_FAIL;
    }

    /* ��ȡbwֵ*/
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: param5 NULL!.");
        return OAL_FAIL;
    }
    uc_bw = (oal_uint8)oal_strtol(pc_token, &pc_end, 10);
    if ((20 != uc_bw) && (40 != uc_bw) && (80 != uc_bw))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: bw = %d, value out of range.", uc_bw);
        return OAL_FAIL;
    }

    /* ��ȡrate/mcs/mcsac�ַ��� */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: param6 NULL!.");
        return OAL_FAIL;
    }
    pc_mcs_type = pc_token;
    if ((0 != oal_strcmp(pc_token, "rate"))
        && (0 != oal_strcmp(pc_token, "mcs"))
        && (0 != oal_strcmp(pc_token, "mcsac")))
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: rate/mcs/mcsac not match.");
        return OAL_FAIL;
    }

    /* ��ȡrate/mcs/mcsacֵ*/
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: param7 NULL!.");
        return OAL_FAIL;
    }
    pc_mcs_value = pc_token;

    /*��������ֵ*/
    //OAM_WARNING_LOG2(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: uc_band = %d, uc_bw = %d \r\n", uc_band, uc_bw);
    uc_scaling_offset = wal_get_dbb_scaling_index(uc_band, uc_bw, pc_mcs_type, pc_mcs_value);
    /*lint -e571*/
    OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc::  uc_scaling_offset = %d.", uc_scaling_offset);
    /*lint +e571*/

    if (uc_scaling_offset == -1)
    {
        return OAL_FAIL;
    }

    /* ��ȡdelta_gainֵ*/
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_dbb_scaling_amend_calc:: param8 NULL!.");
        return OAL_FAIL;
    }
    us_delta_gain = (oal_uint16)oal_strtol(pc_token, &pc_end, 10);

    uc_offset_addr_a = (oal_uint8)uc_scaling_offset;
    uc_offset_addr_a = (uc_offset_addr_a >> 2);
    uc_offset_addr_b = (uc_scaling_offset < (uc_offset_addr_a << 2))?0:((oal_uint8)(uc_scaling_offset - (uc_offset_addr_a << 2)));
    //uc_offset_addr_b = (oal_uint8)(uc_scaling_offset - (uc_offset_addr_a << 2));

    pst_dbb_scaling->uc_offset_addr_a = uc_offset_addr_a;
    pst_dbb_scaling->uc_offset_addr_b = uc_offset_addr_b;
    pst_dbb_scaling->us_delta_gain = us_delta_gain;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_dbb_scaling_amend
 ��������  : ����dbb scalingֵ: hipriv "wlan0 dbb_scaling_amend <param name> <value>"
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��9��
    ��    ��   : liuweiqiang
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dbb_scaling_amend(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;
    mac_cfg_dbb_scaling_stru        st_dbb_scaling;

    if (OAL_SUCC != wal_dbb_scaling_amend_calc(pc_param, &st_dbb_scaling))
    {
        return OAL_FAIL;
    }
    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(mac_cfg_dbb_scaling_stru);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DBB_SCALING_AMEND, us_len);

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value,
                (const oal_void *)&st_dbb_scaling,
                us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_reg_info::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_chain_beacon_switch
 ��������  : ����beacon֡�ķ��Ͳ���(0��ʾ�ر�˫·�������ͣ�1��ʾ����)
 �������  : pst_net_dev : net_device
             pc_param    : ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��13��
    ��    ��   : daihu 00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_beacon_chain_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_net_dev) || (OAL_PTR_NULL == pc_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_beacon_chain_switch::pst_net_dev or pc_param null ptr error %d, %d!}\r\n",  pst_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* beaconͨ��(0/1)�л����ص�����: hipriv "vap0 beacon_chain_switch 0 | 1"
        �˴���������"1"��"0"����ac_name
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_beacon_chain_switch::wal_get_cmd_one_arg return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ������ò�ͬ��ͨ�� */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_beacon_chain_switch::the beacon chain switch command is error %d!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
        ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_BEACON_CHAIN_SWITCH, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_beacon_chain_switch::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_2040_channel_switch_prohibited
 ��������  : ����20/40�����Ƿ��ֹ�ŵ��л�
 �������  : pst_net_dev : net_device
             pc_param    : ����
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��18��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_2040_channel_switch_prohibited(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint8                       uc_csp;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_2040_channel_switch_prohibited::wal_get_cmd_one_arg return err_code %d!}\r\n", ul_ret);
         return ul_ret;
    }

    if (0 == (oal_strcmp("0", ac_name)))
    {
        uc_csp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        uc_csp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_2040_channel_switch_prohibited::the channel_switch_prohibited switch command is error %d!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_2040_CHASWI_PROHI, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = uc_csp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_2040_channel_switch_prohibited::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_FortyMHzIntolerant
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_FortyMHzIntolerant(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint8                       uc_csp;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_FortyMHzIntolerant::wal_get_cmd_one_arg return err_code %d!}\r\n", ul_ret);
         return ul_ret;
    }

    if (0 == (oal_strcmp("0", ac_name)))
    {
        uc_csp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        uc_csp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_FortyMHzIntolerant::the 2040_intolerant command is error %d!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_2040_INTOLERANT, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = uc_csp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_FortyMHzIntolerant::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
/*****************************************************************************
 �� �� ��  : wal_hipriv_get_lauch_cap
 ��������  : ��ȡ������������
 �������  : pst_net_dev: net device
 �������  : pc_extra   : ��ȡ���ķ�������
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��27��
    ��    ��   : w00346925
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_lauch_cap(oal_net_device_stru *pst_net_dev,oal_int8 *pc_param)
{
    wal_msg_query_stru           st_query_msg;
    oal_int32                    l_ret;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    st_query_msg.en_wid = WLAN_CFGID_LAUCH_CAP;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_QUERY,
                               WAL_MSG_WID_LENGTH ,
                               (oal_uint8 *)&st_query_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
       OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_lauch_cap::wal_alloc_cfg_event return err code %d!}\n", l_ret);
       return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_dev_customize_info
 ��������  : show device customize info
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC �� ʧ�ܴ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��22��
    ��    ��   : h00349274
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dev_customize_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
        ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SHOW_DEV_CUSTOMIZE_INFOS, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dev_customize_info::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_txpower
 ��������  : ����Ŀ�깦��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��26��
    ��    ��   : f00290085
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_txpower(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_ret;
    oal_int32                   l_pwer;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_val[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;
    oal_int32                   l_idx = 0;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_val, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_txpower::wal_get_cmd_one_arg vap name return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��������Ϸ��Լ�� */
    while ('\0' != ac_val[l_idx])
    {
        if (isdigit(ac_val[l_idx]))
        {
            l_idx++;
            continue;
        }
        else
        {
            l_idx++;
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_txpower::input illegal!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    l_pwer = oal_atoi(ac_val);

    if (l_pwer > WLAN_MAX_TXPOWER || l_pwer < 0)   /* �����쳣: �������ƴ���1W */
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_txpower::invalid argument!}");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TX_POWER, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_pwer;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);
#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
    wal_hipriv_wait_rsp(pst_net_dev, pc_param);
#endif

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_txpower::return err code %d!}", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
/*****************************************************************************
 �� �� ��  : wal_ioctl_set_beacon_interval
 ��������  : ����beacon interval
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��20��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_ioctl_set_beacon_interval(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_beacon_interval;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_beacon_interval[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;
    oal_int32                   l_ret;

    /* �豸��up״̬���������ã�������down */
    if (0 != (OAL_IFF_RUNNING & OAL_NETDEVICE_FLAGS(pst_net_dev)))
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{wal_ioctl_set_beacon_interval::device is busy, please down it firs %d!}\r\n", OAL_NETDEVICE_FLAGS(pst_net_dev));
        return -OAL_EBUSY;
    }

    /* pc_paramָ���´�����net_device��name, ����ȡ����ŵ�ac_name�� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_beacon_interval, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_ioctl_set_beacon_interval::wal_get_cmd_one_arg vap name return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }

    l_beacon_interval = oal_atoi(ac_beacon_interval);
    OAM_INFO_LOG1(0, OAM_SF_ANY, "{wal_ioctl_set_beacon_interval::l_beacon_interval = %d!}\r\n", l_beacon_interval);

    /***************************************************************************
        ���¼���wal�㴦��
    ***************************************************************************/
    /* ��д��Ϣ */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_BEACON_INTERVAL, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_beacon_interval;

    /* ������Ϣ */
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_ioctl_set_beacon_interval::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_start_vap
 ��������  : ˽��up�������ifconfig up��3sta����ʱ��������sta�޷�up�����ô�����up
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��6��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_start_vap(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    OAM_ERROR_LOG0(0, OAM_SF_CFG, "DEBUG:: priv start enter.");
    wal_netdev_open(pst_net_dev);
    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_amsdu_start
 ��������  : ���������������amsdu����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_amsdu_start(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    mac_cfg_amsdu_start_param_stru  *pst_amsdu_start_param;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    /* ��д��Ϣ */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_AMSDU_START, OAL_SIZEOF(mac_cfg_amsdu_start_param_stru));

    /* ��������������������� */
    pst_amsdu_start_param = (mac_cfg_amsdu_start_param_stru *)(st_write_msg.auc_value);

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_amsdu_start::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, pst_amsdu_start_param->auc_mac_addr);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_amsdu_start::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    pst_amsdu_start_param->uc_amsdu_max_num     = (oal_uint8)oal_atoi(ac_name);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_amsdu_start::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    pst_amsdu_start_param->us_amsdu_max_size    = (oal_uint16)oal_atoi(ac_name);

    /* ������Ϣ */
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_amsdu_start_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_amsdu_start::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_list_ap
 ��������  : ��ӡSTAɨ�赽��AP�б�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_list_ap(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LIST_AP, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_list_ap::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_list_sta
 ��������  : ��ӡAP�������STA��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��22��
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_list_sta(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LIST_STA, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_list_sta::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_list_channel
 ��������  : ��ʾ�豸֧�ֵ��ŵ��б�
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : oal_uint32  OAL_STATIC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_list_channel(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LIST_CHAN, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_list_channel::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_regdomain_pwr_priv
 ��������  : ���ù���������͹���
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_set_regdomain_pwr_priv(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;
    oal_int32                   l_ret = OAL_SUCC;
    oal_uint32                  ul_pwr;
    wal_msg_write_stru          st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "wal_hipriv_set_regdomain_pwr, get arg return err %d", ul_ret);
        return ul_ret;
    }

    ul_pwr = (oal_uint32)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_REGDOMAIN_PWR, OAL_SIZEOF(oal_int32));

    ((mac_cfg_regdomain_max_pwr_stru *)st_write_msg.auc_value)->uc_pwr        = (oal_uint8)ul_pwr;
    ((mac_cfg_regdomain_max_pwr_stru *)st_write_msg.auc_value)->en_exceed_reg = OAL_TRUE;

    l_ret = wal_send_cfg_event(pst_net_dev,
                       WAL_MSG_TYPE_WRITE,
                       WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                       (oal_uint8 *)&st_write_msg,
                       OAL_FALSE,
                       OAL_PTR_NULL);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(0,OAM_SF_CFG,"{wal_hipriv_set_regdomain_pwr::wal_send_cfg_event fail.return err code %d}",l_ret);
    }

    return (oal_uint32)l_ret;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_start_scan
 ��������  : ����sta��ʼɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_start_scan(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;
#ifdef _PRE_WLAN_FEATURE_P2P
    oal_uint8                    uc_is_p2p0_scan;
#endif  /* _PRE_WLAN_FEATURE_P2P */

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_START_SCAN, OAL_SIZEOF(oal_int32));

#ifdef _PRE_WLAN_FEATURE_P2P
    uc_is_p2p0_scan = (oal_memcmp(pst_net_dev->name, "p2p0", OAL_STRLEN("p2p0")) == 0)?1:0;
    //uc_is_p2p0_scan = (pst_net_dev->ieee80211_ptr->iftype == NL80211_IFTYPE_P2P_DEVICE)?1:0;
    st_write_msg.auc_value[0] = uc_is_p2p0_scan;
#endif  /* _PRE_WLAN_FEATURE_P2P */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_start_scan::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_start_scan
 ��������  : ����sta��ʼɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_start_join(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_int32                        l_ret;
    oal_uint32                       ul_ret;
    oal_uint32                       ul_off_set;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_START_JOIN, OAL_SIZEOF(oal_int32));

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_start_join::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Ҫ����AP�ı�Ÿ��Ƶ��¼�msg�У�AP��������ֵ�ASSCI�룬������4���ֽ� */
    oal_memcopy((oal_int8 *)st_write_msg.auc_value, (oal_int8 *)ac_name, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_start_join::return err codereturn err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_start_deauth
 ��������  : ����ȥ��֤
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_start_deauth(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_START_DEAUTH, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_start_deauth::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_start_deauth
 ��������  : ����sta��ʼɨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dump_timer(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DUMP_TIEMR, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_timer::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_kick_user
 ��������  : ɾ��1���û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_kick_user(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_kick_user_param_stru   *pst_kick_user_param;
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN] = {0,0,0,0,0,0};

    /* ȥ����1���û������� hipriv "vap0 kick_user xx:xx:xx:xx:xx:xx" */

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_kick_user::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, auc_mac_addr);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_KICK_USER, OAL_SIZEOF(mac_cfg_kick_user_param_stru));

    /* ��������������� */
    pst_kick_user_param = (mac_cfg_kick_user_param_stru *)(st_write_msg.auc_value);
    oal_set_mac_addr(pst_kick_user_param->auc_mac_addr, auc_mac_addr);

    /* ��дȥ����reason code */
    pst_kick_user_param->us_reason_code = MAC_UNSPEC_REASON;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_kick_user_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_kick_user::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_pause_tid
 ��������  : ɾ��1���û�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_pause_tid(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_pause_tid_param_stru   *pst_pause_tid_param;
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN] = {0,0,0,0,0,0};
    oal_uint8                       uc_tid;
    /* ȥ����1���û������� hipriv "vap0 kick_user xx xx xx xx xx xx" */

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pause_tid::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, auc_mac_addr);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pause_tid::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_tid = (oal_uint8)oal_atoi(ac_name);

    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PAUSE_TID, OAL_SIZEOF(mac_cfg_pause_tid_param_stru));

    /* ��������������� */
    pst_pause_tid_param = (mac_cfg_pause_tid_param_stru *)(st_write_msg.auc_value);
    oal_set_mac_addr(pst_pause_tid_param->auc_mac_addr, auc_mac_addr);
    pst_pause_tid_param->uc_tid = uc_tid;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pause_tid::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    pst_pause_tid_param->uc_is_paused = (oal_uint8)oal_atoi(ac_name);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_pause_tid_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pause_tid::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
/*****************************************************************************
 �� �� ��  : wal_hipriv_get_hipkt_stat
 ��������  : ��ȡ�����ȼ����ĵ�ͳ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_hipkt_stat(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru  st_write_msg;
    oal_int32        l_ret           = OAL_SUCC;

    // sh hipriv.sh "wlan0 get_hipkt_stat"

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_HIPKT_STAT, OAL_SIZEOF(oal_uint8));

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_hipkt_stat:: return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_flowctl_param
 ��������  : ����be,bk,vi,vo��ÿ�ε��ȱ��ĸ�����lowwater_line, high_waterline
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��24��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_flowctl_param(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru  st_write_msg;
    oal_uint32       ul_ret          = OAL_SUCC;
    oal_uint32       ul_off_set      = 0;
    oal_int32        l_ret           = OAL_SUCC;
    oal_int8         ac_param[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    mac_cfg_flowctl_param_stru st_flowctl_param;
    mac_cfg_flowctl_param_stru *pst_param;

    // sh hipriv.sh "Hisilicon0 set_flowctl_param 0/1/2/3 20 20 40"
    // 0/1/2/3 �ֱ����be,bk,vi,vo

    /* ��ȡ�������Ͳ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_flowctl_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    st_flowctl_param.uc_queue_type = (oal_uint8)oal_atoi(ac_param);

    /* ���ö��ж�Ӧ��ÿ�ε��ȱ��ĸ��� */
    pc_param += ul_off_set;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_flowctl_param::wal_get_cmd_one_arg burst_limit return err_code %d!}\r\n", ul_ret);
        return (oal_uint32)ul_ret;
    }
    st_flowctl_param.us_burst_limit = (oal_uint16)oal_atoi(ac_param);

    /* ���ö��ж�Ӧ������low_waterline */
    pc_param += ul_off_set;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_flowctl_param::wal_get_cmd_one_arg low_waterline return err_code %d!}\r\n", ul_ret);
        return (oal_uint32)ul_ret;
    }
    st_flowctl_param.us_low_waterline= (oal_uint16)oal_atoi(ac_param);


    /* ���ö��ж�Ӧ������high_waterline */
    pc_param += ul_off_set;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_flowctl_param::wal_get_cmd_one_arg high_waterline return err_code %d!}\r\n", ul_ret);
        return (oal_uint32)ul_ret;
    }
    st_flowctl_param.us_high_waterline = (oal_uint16)oal_atoi(ac_param);

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_FLOWCTL_PARAM, OAL_SIZEOF(mac_cfg_flowctl_param_stru));
    pst_param = (mac_cfg_flowctl_param_stru *)(st_write_msg.auc_value);

    pst_param->uc_queue_type = st_flowctl_param.uc_queue_type;
    pst_param->us_burst_limit= st_flowctl_param.us_burst_limit;
    pst_param->us_low_waterline = st_flowctl_param.us_low_waterline;
    pst_param->us_high_waterline = st_flowctl_param.us_high_waterline;


    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_flowctl_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_flowctl_param:: return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_get_flowctl_stat
 ��������  : ��ȡ�������״̬��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��24��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_flowctl_stat(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru  st_write_msg;
    oal_int32        l_ret           = OAL_SUCC;

    // sh hipriv.sh "Hisilicon0 get_flowctl_stat"

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_FLOWCTL_STAT, OAL_SIZEOF(oal_uint8));

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_flowctl_stat:: return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_auto_ba_switch
 ��������  : ������ر�amsdu ampdu���Ϸ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��20��
    ��    ��   : tanghuichao
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_ampdu_amsdu_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    /* �����Զ���ʼBA�Ự�Ŀ���:hipriv "vap0  auto_ba 0 | 1" ���������ĳһ��VAP */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_amsdu_switch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����AUTO BA���в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_amsdu_switch::the auto ba switch command is error[%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_AMSDU_AMPDU_SWITCH, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_amsdu_switch::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_event_queue_info
 ��������  : ��ѯ�¼����е���Ϣ���ϱ���SDT
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_event_queue_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return frw_event_queue_info();
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_user_vip
 ��������  : �����û���vip flag;
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��22��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_user_vip(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_user_vip_param_stru    *pst_user_vip_param;
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN] = {0};
    oal_uint8                       uc_vip_flag;

    /* �����û�Ϊvip�û�: 0 �����VIP�û���1����VIP�û�
       sh hipriv.sh "vap0 set_user_vip xx xx xx xx xx xx 0|1" */

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_user_vip::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, auc_mac_addr);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_user_vip::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_vip_flag = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_USER_VIP, OAL_SIZEOF(mac_cfg_pause_tid_param_stru));

    /* ��������������� */
    pst_user_vip_param = (mac_cfg_user_vip_param_stru *)(st_write_msg.auc_value);
    oal_set_mac_addr(pst_user_vip_param->auc_mac_addr, auc_mac_addr);
    pst_user_vip_param->uc_vip_flag = uc_vip_flag;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_user_vip_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_user_vip::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_set_vap_host
 ��������  : ����vap��host flag;
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��22��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_vap_host(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint8                       uc_host_flag;

    /* ����vap��host flag: 0 ����guest vap, 1����host vap
       sh hipriv.sh "vap0 set_host 0|1" */

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_vap_host::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_host_flag = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_VAP_HOST, OAL_SIZEOF(oal_uint8));

    /* ��������������� */
    *((oal_uint8 *)(st_write_msg.auc_value)) = uc_host_flag;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_vap_host::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_send_bar
 ��������  : ָ���û�ָ��tid ����bar
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_send_bar(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_pause_tid_param_stru   *pst_pause_tid_param;
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN] = {0,0,0,0,0,0};
    oal_uint8                       uc_tid;

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_bar::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, auc_mac_addr);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_bar::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_tid = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SEND_BAR, OAL_SIZEOF(mac_cfg_pause_tid_param_stru));

    /* ��������������� */
    pst_pause_tid_param = (mac_cfg_pause_tid_param_stru *)(st_write_msg.auc_value);
    oal_set_mac_addr(pst_pause_tid_param->auc_mac_addr, auc_mac_addr);
    pst_pause_tid_param->uc_tid = uc_tid;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_pause_tid_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_bar::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_ampdu_tx_on
 ��������  : ������ر�ampdu���͹���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_amsdu_tx_on(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_ampdu_tx_on_param_stru *pst_aggr_tx_on_param;
    oal_uint8                       uc_aggr_tx_on;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_amsdu_tx_on::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_aggr_tx_on = (oal_uint8)oal_atoi(ac_name);


    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_AMSDU_TX_ON, OAL_SIZEOF(mac_cfg_ampdu_tx_on_param_stru));

    /* ��������������� */
    pst_aggr_tx_on_param = (mac_cfg_ampdu_tx_on_param_stru *)(st_write_msg.auc_value);
    pst_aggr_tx_on_param->uc_aggr_tx_on = uc_aggr_tx_on;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_ampdu_tx_on_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_amsdu_tx_on::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_frag_threshold
 ��������  : ���÷�Ƭ������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_frag_threshold(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                       ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    mac_cfg_frag_threshold_stru    *pst_threshold;
    oal_uint32                      ul_threshold = 0;

    /* ��ȡ��Ƭ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_frag_threshold::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    ul_threshold = (oal_uint16)oal_atoi(ac_name);
    pc_param += ul_off_set;

    if ((WLAN_FRAG_THRESHOLD_MIN > ul_threshold) ||
        (WLAN_FRAG_THRESHOLD_MAX < ul_threshold))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_frag_threshold::ul_threshold value error [%d]!}\r\n", ul_threshold);
        return OAL_FAIL;
    }

    pst_threshold = (mac_cfg_frag_threshold_stru *)(st_write_msg.auc_value);
    pst_threshold->ul_frag_threshold = ul_threshold;

    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(mac_cfg_frag_threshold_stru);
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FRAG_THRESHOLD_REG, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_frag_threshold::return err code [%d]!}\r\n", l_cfg_rst);
        return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_wmm_switch
 ��������  : ���������/�ر�WMM
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_wmm_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_open_wmm = 0;

    /* ��ȡ�趨��ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_wmm_switch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    uc_open_wmm = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_off_set;


    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_open_wmm;
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_WMM_SWITCH, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_wmm_switch::return err code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_hide_ssid
 ��������  : ���������/�ر�����ssid
 �������  : pst_net_dev:net dev
             pc_param:����ssid����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_hide_ssid(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_hide_ssid = 0;

    /* ��ȡ�趨��ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_hide_ssid::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    uc_hide_ssid = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_off_set;


    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_hide_ssid;
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_HIDE_SSID, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_hide_ssid::return err code [%d]!}\r\n", l_cfg_rst);
        return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_ampdu_tx_on
 ��������  : ������ر�ampdu���͹���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_ampdu_tx_on(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_ampdu_tx_on_param_stru *pst_aggr_tx_on_param;
    oal_uint8                       uc_aggr_tx_on;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_tx_on::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_aggr_tx_on = (oal_uint8)oal_atoi(ac_name);


    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_AMPDU_TX_ON, OAL_SIZEOF(mac_cfg_ampdu_tx_on_param_stru));

    /* ��������������� */
    pst_aggr_tx_on_param = (mac_cfg_ampdu_tx_on_param_stru *)(st_write_msg.auc_value);
    pst_aggr_tx_on_param->uc_aggr_tx_on = uc_aggr_tx_on;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_ampdu_tx_on_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ampdu_tx_on::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_ampdu_tx_on
 ��������  : ������ر�ampdu���͹���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_txbf_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_ampdu_tx_on_param_stru *pst_aggr_tx_on_param;
    oal_uint8                       uc_aggr_tx_on;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_txbf_switch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_aggr_tx_on = (oal_uint8)oal_atoi(ac_name);


    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TXBF_SWITCH, OAL_SIZEOF(mac_cfg_ampdu_tx_on_param_stru));

    /* ��������������� */
    pst_aggr_tx_on_param = (mac_cfg_ampdu_tx_on_param_stru *)(st_write_msg.auc_value);
    pst_aggr_tx_on_param->uc_aggr_tx_on = uc_aggr_tx_on;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_ampdu_tx_on_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_txbf_switch::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_reset_device
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_reset_device(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_RESET_HW,us_len );

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_reset_device::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_reset_operate
 ��������  : ���ø�λ���ص�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
    ��    ��   : zhangyu 00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_reset_operate(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);


    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_RESET_HW_OPERATE, us_len);

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_reset_operate::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_UAPSD
/*****************************************************************************
 �� �� ��  : wal_hipriv_uapsd_debug
 ��������  : uapsdά������
 �������  : WLAN_CFGID_UAPSD_DEBUG
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_uapsd_debug(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_UAPSD_DEBUG,us_len );

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_uapsd_debug::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_DFT_STAT
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_phy_stat_en
 ��������  : ����phyͳ��ʹ�ܽڵ�ı��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��13��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_phy_stat_en(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oam_stats_phy_node_idx_stru     st_phy_stat_node_idx;
    oal_uint8                       uc_loop;

    /* sh hipriv.sh "Hisilicon0 phy_stat_en idx1 idx2 idx3 idx4" */
    for (uc_loop = 0; uc_loop < OAM_PHY_STAT_NODE_ENABLED_MAX_NUM; uc_loop++)
    {
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
             OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_phy_stat_en::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
             return ul_ret;
        }

        st_phy_stat_node_idx.auc_node_idx[uc_loop] = (oal_uint8)oal_atoi(ac_name);

        /* �������Ƿ�Ϸ���������Χ��1~16 */
        if (st_phy_stat_node_idx.auc_node_idx[uc_loop] < OAM_PHY_STAT_ITEM_MIN_IDX
            || st_phy_stat_node_idx.auc_node_idx[uc_loop] > OAM_PHY_STAT_ITEM_MAX_IDX)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY,
                             "{wal_hipriv_set_phy_stat_en::stat_item_idx invalid! should between 1 and 16!}.",
                             st_phy_stat_node_idx.auc_node_idx[uc_loop]);
            return OAL_ERR_CODE_INVALID_CONFIG;
        }

        pc_param += ul_off_set;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PHY_STAT_EN, OAL_SIZEOF(st_phy_stat_node_idx));

    /* ��д��Ϣ�壬���� */
    oal_memcopy(st_write_msg.auc_value, &st_phy_stat_node_idx, OAL_SIZEOF(st_phy_stat_node_idx));

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_phy_stat_node_idx),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_phy_stat_en::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_dbb_env_param
 ��������  : �ϱ�����ֹͣ�ϱ��տڻ������ά�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��15��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dbb_env_param(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint8                       uc_param;

    /* sh hipriv.sh "Hisilicon0 dbb_env_param 0|1" */

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dbb_env_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_param = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DBB_ENV_PARAM, OAL_SIZEOF(uc_param));

    /* ��д��Ϣ�壬���� */
    st_write_msg.auc_value[0] = uc_param;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(uc_param),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dbb_env_param::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_usr_queue_stat
 ��������  : �ϱ����������û�����ͳ����Ϣ������tid���У����ܶ���
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
OAL_STATIC oal_uint32  wal_hipriv_usr_queue_stat(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_usr_queue_param_stru    st_usr_queue_param;

    /* sh hipriv.sh "vap_name usr_queue_stat XX:XX:XX:XX:XX:XX 0|1" */
    OAL_MEMZERO((oal_uint8*)&st_write_msg, OAL_SIZEOF(st_write_msg));
    OAL_MEMZERO((oal_uint8*)&st_usr_queue_param, OAL_SIZEOF(st_usr_queue_param));

    /* ��ȡ�û�mac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, st_usr_queue_param.auc_user_macaddr, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_usr_queue_stat::wal_hipriv_get_mac_addr return [%d].}", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_usr_queue_stat::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    st_usr_queue_param.uc_param = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_USR_QUEUE_STAT, OAL_SIZEOF(st_usr_queue_param));

    /* ��д��Ϣ�壬���� */
    oal_memcopy(st_write_msg.auc_value, &st_usr_queue_param, OAL_SIZEOF(st_usr_queue_param));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_usr_queue_param),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_usr_queue_stat::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_report_vap_stat
 ��������  : �ϱ�����ֹͣ�ϱ�vap����ͳ����Ϣ
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
OAL_STATIC oal_uint32  wal_hipriv_report_vap_stat(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint8                       uc_param;

    /* sh hipriv.sh "vap_name vap _stat  0|1" */

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_vap_stat::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_param = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_VAP_STAT, OAL_SIZEOF(uc_param));

    /* ��д��Ϣ�壬���� */
    st_write_msg.auc_value[0] = uc_param;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(uc_param),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_vap_stat::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_report_all_stat
 ��������  : �ϱ�������������ά��ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��20��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_report_all_stat(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    /* sh hipriv.sh "Hisilicon0 reprt_all_stat type(phy/machw/mgmt/irq/all)  0|1" */
    /* ��ȡrepot���� */
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));
    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';
    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);
    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ALL_STAT, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_all_stat::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_ampdu_aggr_num
 ��������  : ���þۺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��29��
    ��    ��   : h00212953
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_ampdu_aggr_num(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru       st_write_msg;
    oal_uint32               ul_off_set;
    oal_int8                 ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    mac_cfg_aggr_num_stru    st_aggr_num_ctl = {0};
    oal_uint32               ul_ret;
    oal_int32                l_ret;

    OAL_MEMZERO((oal_uint8*)&st_write_msg, OAL_SIZEOF(st_write_msg));
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ampdu_aggr_num::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param += ul_off_set;

    st_aggr_num_ctl.uc_aggr_num_switch = (oal_uint8)oal_atoi(ac_name);
    if (0 == st_aggr_num_ctl.uc_aggr_num_switch)
    {
        /* ��ָ���ۺϸ���ʱ���ۺϸ����ָ�Ϊ0 */
        st_aggr_num_ctl.uc_aggr_num = 0;
    }
    else
    {
        /* ��ȡ�ۺϸ��� */
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ampdu_aggr_num::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
            return ul_ret;
        }

        st_aggr_num_ctl.uc_aggr_num = (oal_uint8)oal_atoi(ac_name);

        /* �����ۺ���������ж� */
        if (st_aggr_num_ctl.uc_aggr_num > WLAN_AMPDU_TX_MAX_NUM)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ampdu_aggr_num::exceed max aggr num [%d]!}\r\n", st_aggr_num_ctl.uc_aggr_num);
            return ul_ret;
        }
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_AGGR_NUM, OAL_SIZEOF(st_aggr_num_ctl));

    /* ��д��Ϣ�壬���� */
    oal_memcopy(st_write_msg.auc_value, &st_aggr_num_ctl, OAL_SIZEOF(st_aggr_num_ctl));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_aggr_num_ctl),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ampdu_aggr_num::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_stbc_ldpc_cap
 ��������  : ����AP��STBC����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��14��
    ��    ��   : W00269675
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_stbc_cap(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_value;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_cfg_net_dev) || (OAL_PTR_NULL == pc_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_set_stbc_cap::pst_cfg_net_dev or pc_param null ptr error %d, %d!}\r\n", pst_cfg_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* STBC���ÿ��ص�����: hipriv "vap0 set_stbc_cap 0 | 1"
            �˴���������"1"��"0"����ac_name
    */

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_stbc_cap::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�������TDLS���ÿ��� */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        ul_value = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        ul_value = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_stbc_cap::the set stbc command is error %d!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_STBC_CAP, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_value;

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_stbc_cap::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_ldpc_cap
 ��������  : ����AP��LDPC����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��14��
    ��    ��   : W00269675
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_ldpc_cap(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_value;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_cfg_net_dev) || (OAL_PTR_NULL == pc_param)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_set_ldpc_cap::pst_cfg_net_dev or pc_param null ptr error %d, %d!}\r\n", pst_cfg_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* LDPC���ÿ��ص�����: hipriv "vap0 set_ldpc_cap 0 | 1"
            �˴���������"1"��"0"����ac_name
    */

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ldpc_cap::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�������TDLS���ÿ��� */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        ul_value = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        ul_value = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ldpc_cap::the set ldpc command is error %d!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_LDPC_CAP, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_value;

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ldpc_cap::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_dump_rx_dscr
 ��������  : dump��������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��2��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_hipriv_dump_rx_dscr(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_value;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_rx_dscr::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    ul_value = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DUMP_RX_DSCR, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_value;

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_rx_dscr::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_dump_tx_dscr
 ��������  : dump����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��4��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dump_tx_dscr(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_value;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_tx_dscr::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    ul_value = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DUMP_TX_DSCR, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_value;

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_tx_dscr::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_dump_memory
 ��������  : dump�ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��4��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dump_memory(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_addr[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int8                        ac_len[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_len;
    oal_uint32                      ul_addr;
    mac_cfg_dump_memory_stru       *pst_cfg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_addr, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_memory::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    pc_param += ul_off_set;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_len, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_memory::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    /* ��ַ�ַ���ת��16λ��ַ */
    ul_addr = (oal_uint32)oal_strtol(ac_addr, 0, 16);
    ul_len  = (oal_uint32)oal_atoi(ac_len);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DUMP_MEMORY, OAL_SIZEOF(mac_cfg_dump_memory_stru));

    /* ��������������� */

    pst_cfg = (mac_cfg_dump_memory_stru *)(st_write_msg.auc_value);

    pst_cfg->ul_addr = ul_addr;
    pst_cfg->ul_len  = ul_len;

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_dump_memory_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_memory::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_show_tx_dscr_addr
 ��������  : ��ӡ���з�����������ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��10��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_show_tx_dscr_addr(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
#ifdef _PRE_DEBUG_MODE
    oal_uint32                   ul_mem_idx;
    oal_uint16                   us_tx_dscr_idx;
    oal_mempool_tx_dscr_addr     *pst_tx_dscr_addr;

    /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_cfg_net_dev) || OAL_UNLIKELY(OAL_PTR_NULL == pc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_show_tx_dscr_addr::pst_net_dev or pc_param null ptr error [%d] [%d]!}\r\n", pst_cfg_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_tx_dscr_addr = oal_mem_get_tx_dscr_addr();
    if (OAL_PTR_NULL == pst_tx_dscr_addr)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_show_tx_dscr_addr::pst_tx_dscr_addr is NULL!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_IO_PRINT("Allocated addr\n");
    for (ul_mem_idx = 0; ul_mem_idx < pst_tx_dscr_addr->us_tx_dscr_cnt; ul_mem_idx++)
    {
        OAL_IO_PRINT("[%d]0x%x\t", ul_mem_idx, (oal_uint32)pst_tx_dscr_addr->ul_tx_dscr_addr[ul_mem_idx]);
    }
    OAL_IO_PRINT("\n");

    OAL_IO_PRINT("Released addr\n");
    for (ul_mem_idx = 0; ul_mem_idx < OAL_TX_DSCR_ITEM_NUM; ul_mem_idx++)
    {
        if (0 != pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_released_addr)
        {
            OAL_IO_PRINT("Addr:0x%x\tFileId:%d\tLineNum:%d\tTimeStamp:%u\n",
                        (oal_uint32)pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_released_addr,
                        pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_release_file_id,
                        pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_release_line_num,
                        pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_release_ts);
        }
    }

    OAL_IO_PRINT("Tx complete int:\n");
    for (ul_mem_idx = 0; ul_mem_idx < OAL_TX_DSCR_ITEM_NUM; ul_mem_idx++)
    {
        if (0 != pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_tx_dscr_in_up_intr)
        {
            OAL_IO_PRINT("Up tx addr:0x%x\tts:%u  |  Dn tx addr:0x%x\tts:%u\n",
                        pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_tx_dscr_in_up_intr,
                        pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_up_intr_ts,
                        pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_tx_dscr_in_dn_intr,
                        pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_dn_intr_ts);
            OAL_IO_PRINT("tx dscr in q[%d] mpdu_num[%d]:", pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].uc_q_num,
                                                            pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].uc_mpdu_num);
            for (us_tx_dscr_idx = 0; 0 != pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_tx_dscr_in_q[us_tx_dscr_idx] && us_tx_dscr_idx < OAL_MAX_TX_DSCR_CNT_IN_LIST; us_tx_dscr_idx++)
            {
                OAL_IO_PRINT("0x%x\t", pst_tx_dscr_addr->ast_tx_dscr_info[ul_mem_idx].ul_tx_dscr_in_q[us_tx_dscr_idx]);
            }
            OAL_IO_PRINT("\n-------------------------------------------\n");
        }
    }
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_dump_ba_bitmap
 ��������  : ��ӡ����ba��bitmap
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��21��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dump_ba_bitmap(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_mpdu_ampdu_tx_param_stru *pst_aggr_tx_on_param;
    oal_uint8                       uc_tid;
    oal_uint8                       auc_ra_addr[WLAN_MAC_ADDR_LEN] = {0};

    /* ��ȡtid */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_ba_bitmap::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    uc_tid = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡMAC��ַ�ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_ba_bitmap::get mac err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    /* ��ַ�ַ���ת��ַ���� */
    oal_strtoaddr(ac_name, auc_ra_addr);
    pc_param += ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DUMP_BA_BITMAP, OAL_SIZEOF(mac_cfg_mpdu_ampdu_tx_param_stru));

    /* ��������������� */
    pst_aggr_tx_on_param = (mac_cfg_mpdu_ampdu_tx_param_stru *)(st_write_msg.auc_value);
    pst_aggr_tx_on_param->uc_tid        = uc_tid;
    oal_set_mac_addr(pst_aggr_tx_on_param->auc_ra_mac, auc_ra_addr);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_mpdu_ampdu_tx_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_ba_bitmap::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_packet_xmit
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��6��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_packet_xmit(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_mpdu_ampdu_tx_param_stru *pst_aggr_tx_on_param;
    oal_uint8                       uc_packet_num;
    oal_uint8                       uc_tid;
    oal_uint16                      uc_packet_len;
    oal_uint8                       auc_ra_addr[WLAN_MAC_ADDR_LEN] = {0};

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    uc_tid = (oal_uint8)oal_atoi(ac_name);
    if(uc_tid >= WLAN_TID_MAX_NUM)
    {
         return OAL_FAIL;
    }
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    uc_packet_num = (oal_uint8)oal_atoi(ac_name);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    uc_packet_len = (oal_uint16)oal_atoi(ac_name);
    if(uc_packet_len < 30)
    {
        return OAL_FAIL;
    }
    pc_param += ul_off_set;

    /* ��ȡMAC��ַ�ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::get mac err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    /* ��ַ�ַ���ת��ַ���� */
    oal_strtoaddr(ac_name, auc_ra_addr);
    pc_param += ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PACKET_XMIT, OAL_SIZEOF(mac_cfg_mpdu_ampdu_tx_param_stru));

    /* ��������������� */
    pst_aggr_tx_on_param = (mac_cfg_mpdu_ampdu_tx_param_stru *)(st_write_msg.auc_value);
    pst_aggr_tx_on_param->uc_packet_num = uc_packet_num;
    pst_aggr_tx_on_param->uc_tid        = uc_tid;
    pst_aggr_tx_on_param->us_packet_len = uc_packet_len;
    oal_set_mac_addr(pst_aggr_tx_on_param->auc_ra_mac, auc_ra_addr);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_mpdu_ampdu_tx_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
OAL_STATIC oal_uint32  wal_hipriv_alg(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru  st_write_msg;  //FIXME : st_write_msg can only carry bytes less than 48
    oal_int32           l_ret;
    oal_uint32          ul_off_set;
    oal_int8            ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int8           *pc_tmp = (oal_int8 *)pc_param;
    oal_uint16          us_config_len;
    oal_uint16          us_param_len;

    mac_ioctl_alg_config_stru   st_alg_config;

    st_alg_config.uc_argc = 0;
    while(OAL_SUCC == wal_get_cmd_one_arg(pc_tmp, ac_arg, &ul_off_set))
    {
        st_alg_config.auc_argv_offset[st_alg_config.uc_argc] = (oal_uint8)((oal_uint8)(pc_tmp - pc_param) + (oal_uint8)ul_off_set - (oal_uint8)OAL_STRLEN(ac_arg));
        pc_tmp += ul_off_set;
        st_alg_config.uc_argc++;

        if(st_alg_config.uc_argc > DMAC_ALG_CONFIG_MAX_ARG)
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_alg::wal_hipriv_alg error, argc too big [%d]!}\r\n", st_alg_config.uc_argc);
            return OAL_FAIL;
        }
    }

    if(0 == st_alg_config.uc_argc)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_alg::argc=0!}\r\n");
        return OAL_FAIL;
    }

    us_param_len = (oal_uint16)OAL_STRLEN(pc_param);
    if(us_param_len > WAL_MSG_WRITE_MAX_LEN - 1 - OAL_SIZEOF(mac_ioctl_alg_config_stru) )
    {
        return OAL_FAIL;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    us_config_len = OAL_SIZEOF(mac_ioctl_alg_config_stru) + us_param_len+ 1;
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ALG, us_config_len);
    oal_memcopy(st_write_msg.auc_value, &st_alg_config, OAL_SIZEOF(mac_ioctl_alg_config_stru));
    oal_memcopy(st_write_msg.auc_value + OAL_SIZEOF(mac_ioctl_alg_config_stru), pc_param, us_param_len + 1);
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + us_config_len,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_alg::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_show_stat_info
 ��������  : ��ȡ����ά��ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��18��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_show_stat_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||defined(_PRE_PRODUCT_ID_HI110X_HOST)

    oam_stats_report_info_to_sdt(OAM_OTA_TYPE_DEV_STAT_INFO);
    oam_stats_report_info_to_sdt(OAM_OTA_TYPE_VAP_STAT_INFO);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_show_vap_pkt_stat
 ��������  : ��ȡĳһ��vap���շ���ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��10��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_show_vap_pkt_stat(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;

    /***************************************************************************
                                 ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_VAP_PKT_STAT, OAL_SIZEOF(oal_uint32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_vap_pkt_stat::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_cca_opt_log
 ��������  : cca_opt�㷨��־��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

        (1)ͳ�Ƶ���������: hipriv.sh "vap0 alg_tpc_log tpc_stat_log 11:22:33:44:55:66  2 500"
           ���������ĳһ��USER

 �޸���ʷ      :
  1.��    ��   : 2015��8��31��
    ��    ��   : liuming 00222214
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_cca_opt_log(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)

{
    wal_msg_write_stru                      st_write_msg;
    oal_uint32                              ul_off_set;
    oal_int8                                ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                              ul_ret;
    mac_ioctl_alg_cca_opt_log_param_stru    *pst_alg_cca_opt_log_param = OAL_PTR_NULL;
    wal_ioctl_alg_cfg_stru                  st_alg_cfg;
    oal_uint8                               uc_map_index = 0;
    oal_int32                               l_ret;
    //oal_bool_enum_uint8                     en_stop_flag = OAL_FALSE;

    pst_alg_cca_opt_log_param = (mac_ioctl_alg_cca_opt_log_param_stru *)(st_write_msg.auc_value);

    /* ��ȡ���ò������� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_cca_opt_log::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param = pc_param + ul_off_set;

    /* Ѱ��ƥ������� */
    st_alg_cfg = g_ast_alg_cfg_map[0];
    while(OAL_PTR_NULL != st_alg_cfg.pc_name)
    {
        if (0 == oal_strcmp(st_alg_cfg.pc_name, ac_name))
        {
            break;
        }
        st_alg_cfg = g_ast_alg_cfg_map[++uc_map_index];
    }

    /* û���ҵ���Ӧ������򱨴� */
    if( OAL_PTR_NULL == st_alg_cfg.pc_name)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_cca_opt_log::invalid alg_cfg command!}\r\n");
        return OAL_FAIL;
    }

    /* ��¼�����Ӧ��ö��ֵ */
    pst_alg_cca_opt_log_param->en_alg_cfg = g_ast_alg_cfg_map[uc_map_index].en_alg_cfg;

    /* ���ֻ�ȡ�ض�֡���ʺ�ͳ����־�����:��ȡ����ֻ���ȡ֡���� */
    if (MAC_ALG_CFG_CCA_OPT_STAT_LOG_START == pst_alg_cca_opt_log_param->en_alg_cfg)
    {
        /* ��ȡ���ò������� */
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_cca_opt_log::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
            return ul_ret;
        }

        /* ��¼���� */
        pst_alg_cca_opt_log_param->us_value = (oal_uint16)oal_atoi(ac_name);
        //en_stop_flag = OAL_TRUE;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ALG_PARAM, OAL_SIZEOF(mac_ioctl_alg_cca_opt_log_param_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_ioctl_alg_cca_opt_log_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_clear_stat_info
 ��������  : �����е�ͳ����Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��18��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_clear_stat_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||defined(_PRE_PRODUCT_ID_HI110X_HOST)
    oam_stats_clear_stat_info();
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_user_stat_info
 ��������  : �ϱ�ĳһ��user��ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��24��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_user_stat_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)||defined(_PRE_PRODUCT_ID_HI110X_HOST)

    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;

    /* sh hipriv.sh "Hisilicon0 usr_stat_info usr_id" */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_user_stat_info::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    l_tmp = oal_atoi(ac_name);
    if ((l_tmp < 0) || (l_tmp >= WLAN_ACTIVE_USER_MAX_NUM))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_user_stat_info::user id invalid [%d]!}\r\n", l_tmp);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    oam_stats_report_usr_info((oal_uint16)l_tmp);
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_show_irq_info
 ��������  : ��ӡ�����жϴ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_timer_start(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint8                       uc_timer_switch;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_timer_start::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);

         return ul_ret;
    }

    uc_timer_switch = (oal_uint8)oal_atoi(ac_name);
    if (uc_timer_switch >= 2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_timer_start::invalid choicee [%d]!}\r\n", uc_timer_switch);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TIMER_START, OAL_SIZEOF(oal_uint8));

    /* ��������������� */
    *((oal_uint8 *)(st_write_msg.auc_value)) = uc_timer_switch;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_timer_start::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_show_irq_info
 ��������  : ��ӡ�����жϴ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_show_profiling(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
#ifdef _PRE_PROFILING_MODE

    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_value;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_profiling::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);

         return ul_ret;
    }

    ul_value = (oal_uint32)oal_atoi(ac_name);
    if (ul_value >= OAM_PROFILING_BUTT)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_profiling::invalid choicee [%d]!}\r\n", ul_value);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SHOW_PROFILING, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_value;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_profiling::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

#endif

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_DFT_STAT
/*****************************************************************************
 �� �� ��  : wal_hipriv_clear_vap_stat_info
 ��������  : ��VAP��ͳ����Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��23��
    ��    ��   : heyinjun
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_clear_vap_stat_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint8                   uc_vap_id;

    uc_vap_id = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;
    oam_stats_clear_vap_stat_info(uc_vap_id);

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_DFR
/*****************************************************************************
 �� �� ��  : wal_hipriv_test_dfr_start
 ��������  : ���Դ�׮����dfr����
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
OAL_STATIC oal_uint32 wal_hipriv_test_dfr_start(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                       ul_cfg_rst;
    oal_wireless_dev_stru           *pst_wdev;
    mac_wiphy_priv_stru             *pst_wiphy_priv;
    mac_device_stru                 *pst_mac_device;

    pst_wdev = OAL_NETDEVICE_WDEV(pst_net_dev);
    if(OAL_PTR_NULL == pst_wdev)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_test_dfr_start::pst_wdev is null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_wiphy_priv  = (mac_wiphy_priv_stru *)oal_wiphy_priv(pst_wdev->wiphy);
    pst_mac_device  = pst_wiphy_priv->pst_mac_device;
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_test_dfr_start::pst_mac_device is null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }
    g_st_dfr_info.bit_device_reset_enable       = OAL_TRUE;
    g_st_dfr_info.bit_device_reset_process_flag = OAL_FALSE;

    ul_cfg_rst = wal_dfr_excp_rx(pst_mac_device->uc_device_id, 0);


    if (OAL_UNLIKELY(OAL_SUCC != ul_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_test_dfr_start::wal_send_cfg_event return err_code [%d]!}\r\n", ul_cfg_rst);
      return ul_cfg_rst;
    }
    return OAL_SUCC;
}

#endif //_PRE_WLAN_FEATURE_DFR

/*****************************************************************************
 �� �� ��  : wal_hipriv_ar_log
 ��������  : autorate�㷨��־��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

        �����㷨����������: hipriv "vap0 alg_ar_log ar_stat_log 11:22:33:44:55:66  2 500"
        ���������ĳһ��USER

 �޸���ʷ      :
  1.��    ��   : 2013��10��25��
    ��    ��   : j00196483
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_ar_log(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                      st_write_msg;
    oal_uint32                              ul_off_set;
    oal_int8                                ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                              ul_ret;
    mac_ioctl_alg_ar_log_param_stru         *pst_alg_ar_log_param = OAL_PTR_NULL;
    wal_ioctl_alg_cfg_stru                  st_alg_cfg;
    oal_uint8                               uc_map_index = 0;
    oal_int32                               l_ret;
    oal_bool_enum_uint8                     en_stop_flag = OAL_FALSE;

    pst_alg_ar_log_param = (mac_ioctl_alg_ar_log_param_stru *)(st_write_msg.auc_value);

    /* ��ȡ���ò������� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ar_log::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;

    /* Ѱ��ƥ������� */
    st_alg_cfg = g_ast_alg_cfg_map[0];
    while(OAL_PTR_NULL != st_alg_cfg.pc_name)
    {
        if (0 == oal_strcmp(st_alg_cfg.pc_name, ac_name))
        {
            break;
        }
        st_alg_cfg = g_ast_alg_cfg_map[++uc_map_index];
    }

    /* û���ҵ���Ӧ������򱨴� */
    if( OAL_PTR_NULL == st_alg_cfg.pc_name)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_ar_log::invalid alg_cfg command!}\r\n");
        return OAL_FAIL;
    }

    /* ��¼�����Ӧ��ö��ֵ */
    pst_alg_ar_log_param->en_alg_cfg = g_ast_alg_cfg_map[uc_map_index].en_alg_cfg;

    ul_ret = wal_hipriv_get_mac_addr(pc_param, pst_alg_ar_log_param->auc_mac_addr, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_ar_log::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    pc_param += ul_off_set;

    while ((' ' == *pc_param) || ('\0' == *pc_param))
    {
        if ('\0' == *pc_param)
        {
            en_stop_flag = OAL_TRUE;
            break;
        }
        ++ pc_param;
    }

    /* ��ȡҵ������ֵ */
    if (OAL_TRUE != en_stop_flag)
    {
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
             OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ar_log::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
             return ul_ret;
        }

        pst_alg_ar_log_param->uc_ac_no = (oal_uint8)oal_atoi(ac_name);
        pc_param = pc_param + ul_off_set;

        en_stop_flag = OAL_FALSE;
        while ((' ' == *pc_param) || ('\0' == *pc_param))
        {
            if ('\0' == *pc_param)
            {
                en_stop_flag = OAL_TRUE;
                break;
            }
            ++ pc_param;
        }

        if (OAL_TRUE != en_stop_flag)
        {
            /* ��ȡ��������ֵ */
            ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
            if (OAL_SUCC != ul_ret)
            {
                 OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ar_log::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
                 return ul_ret;
            }

            /* ��¼��������ֵ */
            pst_alg_ar_log_param->us_value = (oal_uint16)oal_atoi(ac_name);
        }
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ALG_PARAM, OAL_SIZEOF(mac_ioctl_alg_ar_log_param_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_ioctl_alg_ar_log_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
/*****************************************************************************
 �� �� ��  : wal_hipriv_txbf_log
 ��������  : txbf�㷨��־��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
        �����㷨����������: hipriv "vap0 alg_txbf_log txmode_log_record 11:22:33:44:55:66 2000"
        ���������ĳһ��USER
 �޸���ʷ      :
  1.��    ��   : 2014��12��25��
    ��    ��   : x00226265
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_txbf_log(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                      st_write_msg;
    oal_uint32                              ul_off_set;
    oal_int8                                ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                              ul_ret;
    mac_ioctl_alg_txbf_log_param_stru      *pst_alg_txbf_log_param = OAL_PTR_NULL;
    wal_ioctl_alg_cfg_stru                  st_alg_cfg;
    oal_uint8                               uc_map_index = 0;
    oal_int32                               l_ret;
    oal_bool_enum_uint8                     en_stop_flag = OAL_FALSE;
    pst_alg_txbf_log_param = (mac_ioctl_alg_txbf_log_param_stru *)(st_write_msg.auc_value);
    /* ��ȡ���ò������� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_txbf_log::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    /* Ѱ��ƥ������� */
    st_alg_cfg = g_ast_alg_cfg_map[0];
    while(OAL_PTR_NULL != st_alg_cfg.pc_name)
    {
        if (0 == oal_strcmp(st_alg_cfg.pc_name, ac_name))
        {
            break;
        }
        st_alg_cfg = g_ast_alg_cfg_map[++uc_map_index];
    }
    /* û���ҵ���Ӧ������򱨴� */
    if( OAL_PTR_NULL == st_alg_cfg.pc_name)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_ar_log::invalid alg_cfg command!}\r\n");
        return OAL_FAIL;
    }
    /* ��¼�����Ӧ��ö��ֵ */
    pst_alg_txbf_log_param->en_alg_cfg = g_ast_alg_cfg_map[uc_map_index].en_alg_cfg;
    ul_ret = wal_hipriv_get_mac_addr(pc_param, pst_alg_txbf_log_param->auc_mac_addr, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_txbf_log::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    pc_param += ul_off_set;
    while ((' ' == *pc_param))
    {
        ++ pc_param;
        if ('\0' == *pc_param)
        {
            en_stop_flag = OAL_TRUE;
            break;
        }
    }
    /* ��ȡ��������ֵ */
    if (OAL_TRUE != en_stop_flag)
    {
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
             OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_txbf_log::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
             return ul_ret;
        }

        pst_alg_txbf_log_param->uc_ac_no = (oal_uint8)oal_atoi(ac_name);
        pc_param = pc_param + ul_off_set;

        en_stop_flag = OAL_FALSE;
        while ((' ' == *pc_param) || ('\0' == *pc_param))
        {
            if ('\0' == *pc_param)
            {
                en_stop_flag = OAL_TRUE;
                break;
            }
            ++ pc_param;
        }

        if (OAL_TRUE != en_stop_flag)
        {
            /* ��ȡ��������ֵ */
            ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
            if (OAL_SUCC != ul_ret)
            {
                 OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_txbf_log::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
                 return ul_ret;
            }

            /* ��¼��������ֵ */
            pst_alg_txbf_log_param->us_value = (oal_uint16)oal_atoi(ac_name);
        }
    }
    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ALG_PARAM, OAL_SIZEOF(mac_ioctl_alg_txbf_log_param_stru));
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_ioctl_alg_txbf_log_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        return (oal_uint32)l_ret;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_ar_test
 ��������  : autorate�㷨������������:
             hipriv "vap0 alg_ar_test cycle_rate 11:22:33:44:55:66 1"
             ���������ĳһ��USER
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

        �����㷨����������: hipriv "vap0 alg_ar_test cycle_rate 11:22:33:44:55:66 1"
        ���������ĳһ��USER

 �޸���ʷ      :
  1.��    ��   : 2013��11��14��
    ��    ��   : liwenjun 68207
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_ar_test(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                      st_write_msg;
    oal_uint32                              ul_offset;
    oal_int8                                ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                              ul_ret;
    mac_ioctl_alg_ar_test_param_stru       *pst_alg_ar_test_param = OAL_PTR_NULL;
    wal_ioctl_alg_cfg_stru                  st_alg_cfg;
    oal_uint8                               uc_map_index = 0;
    oal_int32                               l_ret;

    pst_alg_ar_test_param = (mac_ioctl_alg_ar_test_param_stru *)(st_write_msg.auc_value);

    /* ��ȡ���ò������� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_offset);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ar_test::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_offset;

    /* Ѱ��ƥ������� */
    st_alg_cfg = g_ast_alg_cfg_map[0];
    while(OAL_PTR_NULL != st_alg_cfg.pc_name)
    {
        if (0 == oal_strcmp(st_alg_cfg.pc_name, ac_name))
        {
            break;
        }
        st_alg_cfg = g_ast_alg_cfg_map[++uc_map_index];
    }

    /* û���ҵ���Ӧ������򱨴� */
    if( OAL_PTR_NULL == st_alg_cfg.pc_name)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_ar_test::invalid alg_cfg command!}\r\n");
        return OAL_FAIL;
    }

    /* ��¼�����Ӧ��ö��ֵ */
    pst_alg_ar_test_param->en_alg_cfg = g_ast_alg_cfg_map[uc_map_index].en_alg_cfg;


    ul_ret = wal_hipriv_get_mac_addr(pc_param, pst_alg_ar_test_param->auc_mac_addr, &ul_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_ar_test::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    pc_param += ul_offset;

    /* ��ȡ��������ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_offset);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_ar_test::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    /* ��¼��������ֵ */
    pst_alg_ar_test_param->us_value = (oal_uint16)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ALG_PARAM, OAL_SIZEOF(mac_ioctl_alg_ar_test_param_stru));
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_ioctl_alg_ar_test_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_edca_opt_weight_sta
 ��������  : ����sta��edca����Ȩ�أ�Ȩ��ȡֵΪ0-3,3��ʾ��ȫ����beacon���е�����0��ʾ������ֵ��edca����(��ʱ����������ǿ)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_edca_opt_weight_sta(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru  st_write_msg;
    oal_uint8           uc_weight       = 0;
    oal_uint8          *puc_value       = 0;
    oal_uint32          ul_ret          = OAL_SUCC;
    oal_int32           l_ret           = OAL_SUCC;
    oal_uint32          ul_off_set      = 0;
    mac_vap_stru       *pst_mac_vap     = OAL_PTR_NULL;
    oal_int8            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    // sh hipriv.sh "vap0 set_edca_weight_sta 1"

    /* ��ȡmac_vap */
    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);
    if (WLAN_VAP_MODE_BSS_STA != pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG0(0, OAM_SF_EDCA, "{wal_hipriv_set_edca_opt_cycle_ap:: only AP_MODE support}");
        return OAL_FAIL;
    }

    /* ��ȡ����ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_EDCA, "{wal_hipriv_set_edca_opt_cycle_ap::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /*lint -e734*/
    uc_weight = (oal_uint32)oal_atoi(ac_name);
   /*lint +e734*/
    /* ���Ȩ��Ϊ3 */
    if (uc_weight > 3)
    {
        OAM_WARNING_LOG1(0, OAM_SF_EDCA, "wal_hipriv_set_edca_opt_weight_sta: valid value is between 0 and %d", 3);
        return OAL_FAIL;
    }

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_EDCA_OPT_WEIGHT_STA, OAL_SIZEOF(oal_uint8));
    puc_value = (oal_uint8 *)(st_write_msg.auc_value);
    *puc_value = uc_weight;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_EDCA, "{wal_hipriv_set_edca_opt_weight_sta:: return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_set_edca_opt_switch_ap
 ��������  : ָ���򿪻��߹ر�ap��edca�Ż�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_edca_opt_switch_ap(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru  st_write_msg;
    oal_uint8        uc_flag         = 0;
    oal_uint8       *puc_value       = 0;
    oal_uint32       ul_ret          = OAL_SUCC;
    oal_uint32       ul_off_set      = 0;
    oal_int32        l_ret           = OAL_SUCC;
    mac_vap_stru    *pst_mac_vap     = OAL_PTR_NULL;
    oal_int8         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    // sh hipriv.sh "vap0 set_edca_switch_ap 1/0"

    /* ��ȡmac_vap */
    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);
    if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
    {
       OAM_WARNING_LOG0(0, OAM_SF_EDCA, "{wal_hipriv_set_edca_opt_cycle_ap:: only AP_MODE support}");
       return OAL_FAIL;
    }

    /* ��ȡ���ò��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_EDCA, "{wal_hipriv_set_edca_opt_cycle_ap::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_flag = (oal_uint8)oal_atoi(ac_name);

    /* �Ƿ����ò��� */
    if (uc_flag > 1)
    {
        OAM_WARNING_LOG0(0, OAM_SF_EDCA, "wal_hipriv_set_edca_opt_cycle_ap, invalid config, should be 0 or 1");
        return OAL_SUCC;
    }

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_EDCA_OPT_SWITCH_AP, OAL_SIZEOF(oal_uint8));
    puc_value = (oal_uint8 *)(st_write_msg.auc_value);
    *puc_value = uc_flag;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_EDCA, "{wal_hipriv_set_edca_opt_switch_ap:: return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_edca_opt_cycle_ap
 ��������  : ����edca��������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_edca_opt_cycle_ap(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru  st_write_msg;
    oal_uint32       ul_cycle_ms     = 0;
    oal_uint32      *pul_value       = 0;
    oal_uint32       ul_ret          = OAL_SUCC;
    oal_int32        l_ret           = OAL_SUCC;
    oal_uint32       ul_off_set      = 0;
    mac_vap_stru    *pst_mac_vap     = OAL_PTR_NULL;
    oal_int8         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    // sh hipriv.sh "vap0 set_edca_cycle_ap 200"

    /* ��ȡmac_vap */
    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);
    if (WLAN_VAP_MODE_BSS_AP != pst_mac_vap->en_vap_mode)
    {
        OAM_WARNING_LOG0(0, OAM_SF_EDCA, "{wal_hipriv_set_edca_opt_cycle_ap:: only AP_MODE support}");
        return OAL_FAIL;
    }

    /* ��ȡ����ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_EDCA, "{wal_hipriv_set_edca_opt_cycle_ap::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    ul_cycle_ms = (oal_uint32)oal_atoi(ac_name);

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_EDCA_OPT_CYCLE_AP, OAL_SIZEOF(oal_uint32));
    pul_value = (oal_uint32 *)(st_write_msg.auc_value);
    *pul_value = ul_cycle_ms;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_EDCA, "{wal_hipriv_set_edca_opt_cycle_ap:: return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_default_key
 ��������  : ����Ĭ��key
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :
            sh hipriv.sh "vap0 set_default_key x(key_index) 0|1(en_unicast) 0|1(multicast)"
 �޸���ʷ      :
  1.��    ��   : 2015��1��15��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_set_default_key(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    mac_setdefaultkey_param_stru  st_payload_params  = {0};
    oal_uint32                     ul_off_set;
    oal_int8                       ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                      l_ret;
    oal_uint32                     ul_ret;
    wal_msg_write_stru             st_write_msg;

    /*1.1 ��μ��*/
    if ((OAL_PTR_NULL == pst_net_dev)|| (OAL_PTR_NULL == pc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_set_default_key::Param Check ERROR,pst_netdev, pst_params %d, %d!}\r\n",pst_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* ��ȡkey_index*/
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{wal_hipriv_test_add_key::wal_get_cmd_one_arg fail.err code[%u]}",ul_ret);
        return ul_ret;
    }
    st_payload_params.uc_key_index = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡen_unicast*/
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{wal_hipriv_test_add_key::wal_get_cmd_one_arg fail.err code[%u]}",ul_ret);
        return ul_ret;
    }
    st_payload_params.en_unicast = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡmulticast*/
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{wal_hipriv_test_add_key::wal_get_cmd_one_arg fail.err code[%u]}",ul_ret);
        return ul_ret;
    }
    st_payload_params.en_multicast = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;


    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    /*3.2 ��д msg ��Ϣ�� */
    oal_memcopy(st_write_msg.auc_value, &st_payload_params, OAL_SIZEOF(mac_setdefaultkey_param_stru));
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DEFAULT_KEY, OAL_SIZEOF(mac_setdefaultkey_param_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_setdefaultkey_param_stru),
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_default_key::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
      return (oal_uint32)l_ret;
    }
    return OAL_SUCC;


}

/*****************************************************************************
 �� �� ��  : wal_hipriv_test_add_key
 ��������  : оƬ���Խӿڣ�add key
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_test_add_key(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru             st_write_msg;
    mac_addkey_param_stru          st_payload_params;
    oal_int8                       ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                      l_ret;
    oal_uint32                     ul_ret;
    oal_uint32                     ul_off_set;
    oal_uint8                      auc_key[OAL_WPA_KEY_LEN] = {0};
    oal_int8                      *pc_key;
    oal_uint32                     ul_char_index;
    oal_uint16                     us_len;
    wal_msg_stru                  *pst_rsp_msg;

    /*1.1 ��μ��*/
    if ((OAL_PTR_NULL == pst_net_dev)|| (OAL_PTR_NULL == pc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_test_add_key::Param Check ERROR,pst_netdev, pst_params %d, %d!}\r\n",pst_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }
    /*xxx(cipher) xx(en_pairwise) xx(key_len) xxx(key_index) xxxx:xx:xx:xx:xx:xx...(key С��32�ֽ�) xx:xx:xx:xx:xx:xx(Ŀ�ĵ�ַ)  */

    oal_memset(&st_payload_params, 0, OAL_SIZEOF(st_payload_params));
    oal_memset(&st_payload_params.st_key, 0, OAL_SIZEOF(mac_key_params_stru));
    st_payload_params.st_key.seq_len = 6;
    OAL_MEMZERO(st_payload_params.auc_mac_addr, WLAN_MAC_ADDR_LEN);

    /* ��ȡcipher*/
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{wal_hipriv_test_add_key::wal_get_cmd_one_arg fail.err code[%u]}",ul_ret);
        return ul_ret;
    }
    st_payload_params.st_key.cipher = (oal_uint32)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;


    /* ��ȡen_pairwise*/
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{wal_hipriv_test_add_key::wal_get_cmd_one_arg fail.err code[%u]}",ul_ret);
        return ul_ret;
    }
    st_payload_params.en_pairwise = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡkey_len */
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{wal_hipriv_test_add_key::wal_get_cmd_one_arg fail.err code[%u]}",ul_ret);
        return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    st_payload_params.st_key.key_len = (oal_uint8)oal_atoi(ac_name);
    if ((st_payload_params.st_key.key_len > OAL_WPA_KEY_LEN) || (st_payload_params.st_key.key_len < 0) )
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_test_add_key::Param Check ERROR! key_len[%x]  }\r\n",
                      (oal_int32)st_payload_params.st_key.key_len);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* ��ȡkey_index */
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{wal_hipriv_test_add_key::wal_get_cmd_one_arg fail.err code[%u]}",ul_ret);
        return ul_ret;
    }
    st_payload_params.uc_key_index = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡkey */
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{wal_hipriv_test_add_key::wal_get_cmd_one_arg fail.err code[%u]}",ul_ret);
        return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    pc_key = ac_name;
    /* 16����ת�� */
    for (ul_char_index = 0; ul_char_index < ul_off_set; ul_char_index++)
    {
        if ('-' == *pc_key)
        {
            pc_key++;
            if (0 != ul_char_index)
            {
                ul_char_index--;
            }

            continue;
        }

        auc_key[ul_char_index/2] = (oal_uint8)(auc_key[ul_char_index/2] * 16 * (ul_char_index % 2) + oal_strtohex(pc_key));
        pc_key++;
    }
    oal_memcopy(st_payload_params.st_key.auc_key, auc_key, (oal_uint32)st_payload_params.st_key.key_len);


    /* ��ȡĿ�ĵ�ַ */
    OAL_MEMZERO(ac_name, WAL_HIPRIV_CMD_NAME_MAX_LEN);
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0,OAM_SF_ANY,"{wal_hipriv_test_add_key::wal_get_cmd_one_arg fail.err code[%u]}",ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, st_payload_params.auc_mac_addr);
    pc_param = pc_param + ul_off_set;

    OAM_INFO_LOG3(0, OAM_SF_ANY, "{wal_hipriv_test_add_key::key_len:%d, seq_len:%d, cipher:0x%08x!}\r\n",
                  st_payload_params.st_key.key_len, st_payload_params.st_key.seq_len, st_payload_params.st_key.cipher);


    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    /*3.2 ��д msg ��Ϣ�� */
    us_len = (oal_uint32)OAL_SIZEOF(mac_addkey_param_stru);
    oal_memcopy((oal_int8*)st_write_msg.auc_value, (oal_int8*)&st_payload_params, (oal_uint32)us_len);
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ADD_KEY, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_TRUE,
                             &pst_rsp_msg);

    if (OAL_SUCC != wal_check_and_release_msg_resp(pst_rsp_msg))
    {
        OAM_WARNING_LOG0(0,OAM_SF_ANY,"wal_hipriv_test_add_key::wal_check_and_release_msg_resp fail");
    }

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_enable_pmf::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
      return (oal_uint32)l_ret;
    }
    return OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : wal_hipriv_set_mib
 ��������  :  ����VAP mib
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��27��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_mib(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint32                      ul_mib_idx = 0;
    oal_uint32                      ul_mib_value = 0;
    mac_cfg_set_mib_stru           *pst_set_mib;

    /* ��ȡ�趨mib���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mib::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    ul_mib_idx = (oal_uint32)oal_atoi(ac_name);

    /* ��ȡ�趨�� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mib::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return (oal_uint32)ul_ret;
    }
    pc_param += ul_off_set;
    ul_mib_value = (oal_uint32)oal_atoi(ac_name);

    pst_set_mib = (mac_cfg_set_mib_stru *)(st_write_msg.auc_value);
    pst_set_mib->ul_mib_idx   = ul_mib_idx;
    pst_set_mib->ul_mib_value = ul_mib_value;
    us_len = OAL_SIZEOF(mac_cfg_set_mib_stru);
    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_MIB, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mib::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
        return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_get_mib
 ��������  : ��ȡVAP mib
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��27��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_mib(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint32                      ul_mib_idx = 0;

    /* ��ȡmib���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_mib::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    ul_mib_idx = (oal_uint32)oal_atoi(ac_name);

    us_len = OAL_SIZEOF(oal_uint32);
    *(oal_uint32 *)(st_write_msg.auc_value) = ul_mib_idx;
    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_MIB, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_mib::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_thruput_bypass
 ��������  : ����thruput_bypassά���
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��15��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_thruput_bypass(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_ret;
    oal_int32                        l_cfg_rst;
    oal_uint16                       us_len;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_off_set = 0;
    oal_uint8                        uc_bypass_type = 0;
    oal_uint8                        uc_value = 0;
    mac_cfg_set_thruput_bypass_stru *pst_set_bypass;

    /* ��ȡ�趨mib���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_thruput_bypass::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    uc_bypass_type = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ�趨�� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_thruput_bypass::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return (oal_uint32)ul_ret;
    }
    pc_param += ul_off_set;
    uc_value = (oal_uint8)oal_atoi(ac_name);

    pst_set_bypass = (mac_cfg_set_thruput_bypass_stru *)(st_write_msg.auc_value);
    pst_set_bypass->uc_bypass_type   = uc_bypass_type;
    pst_set_bypass->uc_value = uc_value;
    us_len = OAL_SIZEOF(mac_cfg_set_thruput_bypass_stru);
    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_THRUPUT_BYPASS, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_thruput_bypass::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
        return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_thruput_bypass
 ��������  : ����thruput_bypassά���
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��15��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
OAL_STATIC oal_uint32  wal_hipriv_set_auto_freq(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_ret;
    oal_int32                        l_cfg_rst;
    oal_uint16                       us_len;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_off_set = 0;
    oal_uint8                        uc_cmd_type = 0;
    oal_uint8                        uc_value = 0;
    mac_cfg_set_auto_freq_stru *pst_set_auto_freq;

    /* ��ȡ�趨mib���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_thruput_bypass::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    uc_cmd_type = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ�趨�� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_thruput_bypass::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return (oal_uint32)ul_ret;
    }
    pc_param += ul_off_set;
    uc_value = (oal_uint8)oal_atoi(ac_name);

    pst_set_auto_freq = (mac_cfg_set_auto_freq_stru*)(st_write_msg.auc_value);
    pst_set_auto_freq->uc_cmd_type   = uc_cmd_type;
    pst_set_auto_freq->uc_value = uc_value;
    us_len = OAL_SIZEOF(mac_cfg_set_thruput_bypass_stru);
    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_AUTO_FREQ_ENABLE, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_thruput_bypass::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
        return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_DFT_STAT
/*****************************************************************************
 �� �� ��  : wal_hipriv_performance_log_switch
 ��������  : �������ܴ�ӡ���ƿ���
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��15��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_performance_log_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_ret;
    oal_int32                        l_cfg_rst;
    oal_uint16                       us_len;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_off_set = 0;
    oal_uint8                        uc_performance_switch_type = 0;
    oal_uint8                        uc_value = 0;
    mac_cfg_set_performance_log_switch_stru *pst_set_performance_log_switch;

    /* ��ȡ�趨mib���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_performance_log_switch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    uc_performance_switch_type = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡ�趨�� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_performance_log_switch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return (oal_uint32)ul_ret;
    }
    pc_param += ul_off_set;
    uc_value = (oal_uint8)oal_atoi(ac_name);

    pst_set_performance_log_switch = (mac_cfg_set_performance_log_switch_stru *)(st_write_msg.auc_value);
    pst_set_performance_log_switch->uc_performance_log_switch_type   = uc_performance_switch_type;
    pst_set_performance_log_switch->uc_value = uc_value;
    us_len = OAL_SIZEOF(mac_cfg_set_performance_log_switch_stru);
    OAM_WARNING_LOG2(0, OAM_SF_ANY, "{wal_hipriv_performance_log_switch::uc_performance_switch_type = %d, uc_value = %d!}\r\n", uc_performance_switch_type,uc_value);
    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_PERFORMANCE_LOG_SWITCH, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_performance_log_switch::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
        return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_auto_protection
 ��������  : ���ñ���ģʽ����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��27��
    ��    ��   : c00260463
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_auto_protection(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint32                      ul_auto_protection_flag = 0;

    /* ��ȡmib���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_auto_protection::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    ul_auto_protection_flag = (oal_uint32)oal_atoi(ac_name);

    us_len = OAL_SIZEOF(oal_uint32);
    *(oal_uint32 *)(st_write_msg.auc_value) = ul_auto_protection_flag;
    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_AUTO_PROTECTION, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_auto_protection::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_WAPI
/*****************************************************************************
 �� �� ��  : wal_hipriv_show_wapi_info
 ��������  : ��ʾwapi�ĵ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WAPI_DEBUG
OAL_STATIC oal_uint32  wal_hipriv_show_wapi_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    mac_vap_stru                    *pst_mac_vap;
    wal_msg_write_stru               st_write_msg;
    oal_int32                        l_ret;
    mac_cfg_user_info_param_stru    *pst_user_info_param;
    oal_uint8                        auc_mac_addr[6] = {0};    /* ��ʱ�����ȡ��use��mac��ַ��Ϣ */
    oal_uint8                        uc_char_index;
    oal_uint16                       us_user_idx;
    //OAL_IO_PRINT("wal_hipriv_show_wapi_info::enter\r\n");
    /* ȥ���ַ����Ŀո� */
    pc_param++;

    /* ��ȡmac��ַ,16����ת�� */
    for (uc_char_index = 0; uc_char_index < 12; uc_char_index++)
    {
        if (':' == *pc_param)
        {
            pc_param++;
            if (0 != uc_char_index)
            {
                uc_char_index--;
            }

            continue;
        }

        auc_mac_addr[uc_char_index/2] =
        (oal_uint8)(auc_mac_addr[uc_char_index/2] * 16 * (uc_char_index % 2) +
                                        oal_strtohex(pc_param));
        pc_param++;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_WAPI_INFO, OAL_SIZEOF(mac_cfg_user_info_param_stru));

    /* ����mac��ַ���û� */
    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);

    l_ret = (oal_int32)mac_vap_find_user_by_macaddr(pst_mac_vap, auc_mac_addr, &us_user_idx);
    if (OAL_SUCC != l_ret)
    {
        //OAL_IO_PRINT("wal_hipriv_show_wapi_info::no such user\r\n");
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_user_info::no such user!}\r\n");
        return OAL_FAIL;
    }

    /* ��������������� */
    pst_user_info_param              = (mac_cfg_user_info_param_stru *)(st_write_msg.auc_value);
    pst_user_info_param->us_user_idx = us_user_idx;
    //OAL_IO_PRINT("wal_hipriv_show_wapi_info::us_user_idx %u\r\n", us_user_idx);

    OAM_WARNING_LOG1(0, OAM_SF_ANY, "wal_hipriv_show_wapi_info::us_user_idx %u", us_user_idx);
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_user_info_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_hipriv_user_info::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif /* #ifdef WAPI_DEBUG_MODE */

#endif /* #ifdef _PRE_WLAN_FEATURE_WAPI */


/*****************************************************************************
 �� �� ��  : wal_hipriv_send_2040_coext
 ��������  : ����20/40�������֡
 �������  : pst_net_dev:
             pc_param:
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��25��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_send_2040_coext(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint32                      ul_ret;
    oal_uint32                      ul_off_set = 0;
    mac_cfg_set_2040_coexist_stru   *pst_2040_coexist;

    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    pst_2040_coexist = (mac_cfg_set_2040_coexist_stru*)st_write_msg.auc_value;
    /* ��ȡmib���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_2040_coext::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    pst_2040_coexist->ul_coext_info = (oal_uint32)oal_atoi(ac_name);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_2040_coext::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    pst_2040_coexist->ul_channel_report = (oal_uint32)oal_atoi(ac_name);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SEND_2040_COEXT,
                    OAL_SIZEOF(mac_cfg_set_2040_coexist_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_set_2040_coexist_stru),
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_2040_coext::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
      return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_2040_coext_info
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��10��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_2040_coext_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    if (OAL_UNLIKELY(WAL_MSG_WRITE_MAX_LEN <= OAL_STRLEN(pc_param)))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_2040_coext_info:: pc_param overlength is %d}\n", OAL_STRLEN(pc_param));
        oal_print_hex_dump((oal_uint8 *)pc_param, WAL_MSG_WRITE_MAX_LEN, 32, "wal_hipriv_2040_coext_info: param is overlong:");
        return OAL_FAIL;
    }

    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_2040_COEXT_INFO, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_2040_coext_info::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
      return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_get_version
 ��������  : ��ȡ�汾
 �������  : pst_net_dev:
             pc_param:
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��25��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_version(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_VERSION, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_version::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
      return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_opmode_notify
 ��������  : ���ù���ģʽ֪ͨ����
 �������  : pst_net_dev: net deviceָ��
             pc_param: ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��12��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_opmode_notify(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;
    oal_uint32                      ul_ret = OAL_SUCC;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_value = 0;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_opmode_notify::wal_get_cmd_one_arg fails!}\r\n");
        return ul_ret;
    }

    pc_param += ul_off_set;
    uc_value = (oal_uint8)oal_atoi((const oal_int8 *)ac_name);

    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_value;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_OPMODE_NOTIFY, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_set_opmode_notify::wal_hipriv_reset_device return err code = [%d].}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_get_user_nssbw
 ��������  : ��������û�����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��5��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_user_nssbw(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_add_user_param_stru    *pst_add_user_param;
    mac_cfg_add_user_param_stru     st_add_user_param;  /* ��ʱ�����ȡ��use����Ϣ */
    oal_uint32                      ul_get_addr_idx;

    /* ��ȡ�û�����Ϳռ�����Ϣ: hipriv "vap0 add_user xx xx xx xx xx xx(mac��ַ)" */
    OAL_MEMZERO((oal_void *)&st_add_user_param, OAL_SIZEOF(mac_cfg_add_user_param_stru));
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_add_user::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, st_add_user_param.auc_mac_addr);

    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    /* ��������������� */
    pst_add_user_param = (mac_cfg_add_user_param_stru *)(st_write_msg.auc_value);
    for (ul_get_addr_idx = 0; ul_get_addr_idx < WLAN_MAC_ADDR_LEN; ul_get_addr_idx++)
    {
        pst_add_user_param->auc_mac_addr[ul_get_addr_idx] = st_add_user_param.auc_mac_addr[ul_get_addr_idx];
    }

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_USER_RSSBW, OAL_SIZEOF(mac_cfg_add_user_param_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_add_user_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_add_user::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_vap_nss
 ��������  : ����VAP�Ŀռ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��6��27��
     ��    ��   : z00241943
     �޸�����   : �����ɺ���


*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_vap_nss(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;
    oal_uint32                      ul_ret = OAL_SUCC;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_vap_nss = 0;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_vap_nss::wal_get_cmd_one_arg fails!}\r\n");
        return ul_ret;
    }

    pc_param += ul_off_set;
    uc_vap_nss = (oal_uint8)oal_atoi((const oal_int8 *)ac_name);

    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_vap_nss;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_VAP_NSS, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                              WAL_MSG_TYPE_WRITE,
                              WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                              (oal_uint8 *)&st_write_msg,
                              OAL_FALSE,
                              OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_set_vap_nss::wal_hipriv_reset_device return err code = [%d].}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY

/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_blacklist_add(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;
    oal_uint32                      ul_ret = OAL_SUCC;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                      ul_off_set = 0;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_blacklist_add:wal_get_cmd_one_arg fail!}\r\n");
        return ul_ret;
    }
    OAL_MEMZERO((oal_uint8*)&st_write_msg, OAL_SIZEOF(st_write_msg));

    oal_strtoaddr(ac_name, st_write_msg.auc_value); /* ���ַ� ac_name ת�������� mac_add[6] */

    us_len = OAL_MAC_ADDR_LEN; /* OAL_SIZEOF(oal_uint8); */

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ADD_BLACK_LIST, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                              WAL_MSG_TYPE_WRITE,
                              WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                              (oal_uint8 *)&st_write_msg,
                              OAL_FALSE,
                              OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_blacklist_add:wal_send_cfg_event return[%d].}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_blacklist_del(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;
    oal_uint32                      ul_ret = OAL_SUCC;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                      ul_off_set = 0;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_blacklist_add:wal_get_cmd_one_arg fail!}\r\n");
        return ul_ret;
    }
    OAL_MEMZERO((oal_uint8*)&st_write_msg, OAL_SIZEOF(st_write_msg));

    oal_strtoaddr(ac_name, st_write_msg.auc_value); /* ���ַ� ac_name ת�������� mac_add[6] */

    us_len = OAL_MAC_ADDR_LEN; /* OAL_SIZEOF(oal_uint8); */

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DEL_BLACK_LIST, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                              WAL_MSG_TYPE_WRITE,
                              WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                              (oal_uint8 *)&st_write_msg,
                              OAL_FALSE,
                              OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_blacklist_add:wal_send_cfg_event return[%d].}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_blacklist_mode(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_BLACKLIST_MODE);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_blacklist_show(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_BLACKLIST_SHOW);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_abl_on(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_AUTOBLACKLIST_ON);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_abl_aging(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_AUTOBLACKLIST_AGING);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_abl_threshold(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_AUTOBLACKLIST_THRESHOLD);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_abl_reset(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_AUTOBLACKLIST_RESET);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_isolation_mode(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_ISOLATION_MODE);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_isolation_type(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_ISOLATION_TYPE);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_isolation_fwd(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_ISOLATION_FORWARD);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_isolation_clear(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_ISOLATION_CLEAR);
}
/*****************************************************************************
 �� �� ��  :
 ��������  :
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2014��7��29��
     ��    ��   : chenchongbao
     �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_isolation_show(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    return wal_hipriv_send_cfg_uint32_data(pst_net_dev,pc_param,WLAN_CFGID_ISOLATION_SHOW);
}
#endif  /* _PRE_WLAN_FEATURE_CUSTOM_SECURITY */

/*****************************************************************************
 �� �� ��  : wal_hipriv_vap_classify_en
 ��������  : �Ƿ�ʹ�ܻ���vap�������๦��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_vap_classify_en(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_val = 0xff;
    wal_msg_write_stru              st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC == ul_ret)
    {
        ul_val = (oal_uint32)oal_atoi(ac_name);
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_VAP_CLASSIFY_EN, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_val;

    l_ret = wal_send_cfg_event(pst_net_dev,
                       WAL_MSG_TYPE_WRITE,
                       WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                       (oal_uint8 *)&st_write_msg,
                       OAL_FALSE,
                       OAL_PTR_NULL);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::wal_send_cfg_event fail.return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_vap_classify_tid
 ��������  : ����vap�����ȼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_vap_classify_tid(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_val = 0xff;
    wal_msg_write_stru              st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC == ul_ret)
    {
        ul_val = (oal_uint32)oal_atoi(ac_name);
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_VAP_CLASSIFY_TID, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_val;

    l_ret = wal_send_cfg_event(pst_net_dev,
                       WAL_MSG_TYPE_WRITE,
                       WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                       (oal_uint8 *)&st_write_msg,
                       OAL_FALSE,
                       OAL_PTR_NULL);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::wal_send_cfg_event fail.return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#ifdef _PRE_WLAN_FEATURE_STA_PM
/*****************************************************************************
 �� �� ��  : wal_hipriv_sta_psm_param
 ��������  : ˽������,sta psm��listen interval / tbtt offset
 �������  : pst_cfg_net_dev: net_device
             pc_param: ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��16��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_sta_psm_param(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                  st_write_msg;
    oal_uint32                          ul_off_set;
    oal_int8                            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                          ul_ret;
    oal_int32                           l_ret;
    oal_uint16                          us_beacon_timeout;
    oal_uint16                          us_tbtt_offset;
    oal_uint16                          us_ext_tbtt_offset;
    oal_uint16                          us_dtim3_on;
    mac_cfg_ps_param_stru               *pst_ps_para;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_sta_psm_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    us_beacon_timeout = (oal_uint16)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_sta_psm_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    us_tbtt_offset = (oal_uint16)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_sta_psm_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    us_ext_tbtt_offset = (oal_uint16)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_sta_psm_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    us_dtim3_on = (oal_uint16)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_PSM_PARAM, OAL_SIZEOF(mac_cfg_ps_param_stru));

    /* ��������������� */
    pst_ps_para = (mac_cfg_ps_param_stru *)(st_write_msg.auc_value);
    pst_ps_para->us_beacon_timeout      = us_beacon_timeout;
    pst_ps_para->us_tbtt_offset         = us_tbtt_offset;
    pst_ps_para->us_ext_tbtt_offset     = us_ext_tbtt_offset;
    pst_ps_para->us_dtim3_on            = us_dtim3_on;

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_ps_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_PWR, "{wal_hipriv_sta_psm_param::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_psm_open
 ��������  : ˽������,sta psm��listen interval / tbtt offset
 �������  : pst_cfg_net_dev: net_device
             pc_param: ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��3��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_sta_pm_on(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                  st_write_msg;
    oal_uint32                          ul_off_set;
    oal_int8                            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                          ul_ret;
    oal_int32                           l_ret;
    oal_uint8                           uc_sta_pm_open;
    mac_cfg_ps_open_stru               *pst_sta_pm_open;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_sta_pm_open::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_sta_pm_open = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_STA_PM_ON, OAL_SIZEOF(mac_cfg_ps_open_stru));

    /* ��������������� */
    pst_sta_pm_open = (mac_cfg_ps_open_stru *)(st_write_msg.auc_value);
    /* MAC_STA_PM_SWITCH_ON / MAC_STA_PM_SWITCH_OFF */
    pst_sta_pm_open->uc_pm_enable      = uc_sta_pm_open;
    pst_sta_pm_open->uc_pm_ctrl_type   = MAC_STA_PM_CTRL_TYPE_HOST;

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_ps_open_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_PWR, "{wal_hipriv_sta_pm_open::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 �� �� ��  : wal_hipriv_p2p_test
 ��������  : P2P ��������
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_p2p_test(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_p2p_test::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param   += ul_off_set;

    /* ��Խ������Ĳ�ͬ�����logģ����в�ͬ������ */
    if (0 == (oal_strcmp("del_intf", ac_name)))
    {
        oal_uint32              ul_del_intf = 0;
        mac_vap_stru           *pst_mac_vap;
        hmac_device_stru       *pst_hmac_device;

        /* ��ȡ���� */
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_p2p_test::wal_get_cmd_one_arg 1 return err_code [%d]!}\r\n", ul_ret);
            return ul_ret;
        }
        pc_param   += ul_off_set;
        if (0 == (oal_strcmp("0", ac_name)))
        {
            ul_del_intf = 0;
        }
        else if (0 == (oal_strcmp("1", ac_name)))
        {
            ul_del_intf = 1;
        }
        else
        {
            OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_hipriv_p2p_test ::wrong parm.ul_del_intf\r\n}");
            return OAL_FAIL;
        }

        pst_mac_vap     = OAL_NET_DEV_PRIV(pst_net_dev);
        pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
        if (pst_hmac_device == OAL_PTR_NULL)
        {
            OAM_ERROR_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_P2P,
                        "{wal_hipriv_p2p_test::pst_hmac_device is null !device_id[%d]}",
                        pst_mac_vap->uc_device_id);
            return OAL_FAIL;
        }

        if (ul_del_intf == 1)
        {
            hmac_set_p2p_status(&pst_hmac_device->ul_p2p_intf_status, P2P_STATUS_IF_DELETING);
        }
        else
        {
            hmac_clr_p2p_status(&pst_hmac_device->ul_p2p_intf_status, P2P_STATUS_IF_DELETING);
        }

        OAM_WARNING_LOG2(0, OAM_SF_CFG, "{wal_hipriv_p2p_test ::ctrl[%d], len:%d!}\r\n",
                        ul_del_intf, pst_hmac_device->ul_p2p_intf_status);

        OAL_SMP_MB();
        OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(&pst_hmac_device->st_netif_change_event);

    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_p2p_test::the log switch command is error [%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    #if 0
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_p2p_test::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }
    #endif

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_TCP_OPT
/*****************************************************************************
 �� �� ��  : wal_hipriv_get_tcp_ack_stream_info
 ��������  : ��ѯTCP ACK����ͳ��ֵ
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��19��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_tcp_ack_stream_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;


    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_TCP_ACK_STREAM_INFO, OAL_SIZEOF(oal_uint32));


    l_ret = wal_send_cfg_event(pst_net_dev,
                       WAL_MSG_TYPE_WRITE,
                       WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                       (oal_uint8 *)&st_write_msg,
                       OAL_FALSE,
                       OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_arpoffload_info::wal_send_cfg_event fail.return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_tcp_tx_ack_opt_enable
 ��������  :  ���÷���TCP ACK�Ż�ʹ��
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��19��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_tcp_tx_ack_opt_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_val = 0xff;
    wal_msg_write_stru              st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_tcp_tx_ack_opt_enable::wal_get_cmd_one_arg vap name return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }

    pc_param += ul_off_set;

    ul_val = (oal_uint32)oal_atoi((const oal_int8 *)ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TX_TCP_ACK_OPT_ENALBE, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_val;

    l_ret = wal_send_cfg_event(pst_net_dev,
                       WAL_MSG_TYPE_WRITE,
                       WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                       (oal_uint8 *)&st_write_msg,
                       OAL_FALSE,
                       OAL_PTR_NULL);

    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_arpoffload_info::wal_send_cfg_event fail.return err code [%ud]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_tcp_rx_ack_opt_enable
 ��������  :  ���ý���TCP ACK�Ż�ʹ��
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��19��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_tcp_rx_ack_opt_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_val = 0xff;
    wal_msg_write_stru              st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_tcp_rx_ack_opt_enable::wal_get_cmd_one_arg vap name return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    ul_val = (oal_uint32)oal_atoi((const oal_int8 *)ac_name);


    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_RX_TCP_ACK_OPT_ENALBE, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_val;

    l_ret = wal_send_cfg_event(pst_net_dev,
                       WAL_MSG_TYPE_WRITE,
                       WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                       (oal_uint8 *)&st_write_msg,
                       OAL_FALSE,
                       OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_arpoffload_info::wal_send_cfg_event fail.return err code [%d]!}\r\n", l_ret);
         return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_hipriv_tcp_tx_ack_limit
 ��������  :  ���÷���TCP ACK�Ż�ʹ��
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��19��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_tcp_tx_ack_limit(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_val = 0xff;
    wal_msg_write_stru              st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_tcp_tx_ack_limit::wal_get_cmd_one_arg vap name return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    ul_val = (oal_uint32)oal_atoi((const oal_int8 *)ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TX_TCP_ACK_OPT_LIMIT, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_val;

    l_ret = wal_send_cfg_event(pst_net_dev,
                       WAL_MSG_TYPE_WRITE,
                       WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                       (oal_uint8 *)&st_write_msg,
                       OAL_FALSE,
                       OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_arpoffload_info::wal_send_cfg_event fail.return err code [%d]!}\r\n", l_ret);
         return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_hipriv_tcp_rx_ack_limit
 ��������  :  ���ý���TCP ACK�Ż�ʹ��
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��19��
    ��    ��   : z00185449
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_tcp_rx_ack_limit(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_val = 0xff;
    wal_msg_write_stru              st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_tcp_tx_ack_limit::wal_get_cmd_one_arg vap name return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    ul_val = (oal_uint32)oal_atoi((const oal_int8 *)ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_RX_TCP_ACK_OPT_LIMIT, OAL_SIZEOF(oal_uint32));

    /* ��������������� */
    *((oal_uint32 *)(st_write_msg.auc_value)) = ul_val;

    l_ret = wal_send_cfg_event(pst_net_dev,
                       WAL_MSG_TYPE_WRITE,
                       WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                       (oal_uint8 *)&st_write_msg,
                       OAL_FALSE,
                       OAL_PTR_NULL);
    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_arpoffload_info::wal_send_cfg_event fail.return err code [%d]!}\r\n", l_ret);
         return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
/*****************************************************************************
 �� �� ��  : wal_hipriv_enable_2040bss
 ��������  : ����20/40 bss����Ƿ�ʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��31��
    ��    ��   : w00249967
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_enable_2040bss(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret = OAL_SUCC;
    oal_uint8                       uc_2040bss_switch;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_enable_2040bss::wal_get_cmd_one_arg return err_code %d!}\r\n", ul_ret);
         return ul_ret;
    }

    if ((0 != oal_strcmp("0", ac_name)) && (0 != oal_strcmp("1", ac_name)))
    {
        OAM_ERROR_LOG0(0, OAM_SF_CFG, "{wal_hipriv_enable_2040bss::invalid parameter.}\r\n");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    uc_2040bss_switch = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_2040BSS_ENABLE, OAL_SIZEOF(oal_uint8));
    *((oal_uint8 *)(st_write_msg.auc_value)) = uc_2040bss_switch;  /* ��������������� */

    ul_ret = (oal_uint32)wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_enable_2040bss::return err code %d!}\r\n", ul_ret);
    }

    return ul_ret;
}
#endif /* _PRE_WLAN_FEATURE_20_40_80_COEXIST */

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_txrx_chain
 ��������  : �����շ�ͨ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : w00269675
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_txrx_chain(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;
    oal_uint32                      ul_ret = OAL_SUCC;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_chain = 0;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_txrx_chain::wal_get_cmd_one_arg fails!}\r\n");
        return ul_ret;
    }

    pc_param += ul_off_set;
    uc_chain = (oal_uint8)oal_atoi((const oal_int8 *)ac_name);

    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_chain;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_TXRX_CHAIN, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                              WAL_MSG_TYPE_WRITE,
                              WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                              (oal_uint8 *)&st_write_msg,
                              OAL_FALSE,
                              OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_set_txrx_chain::wal_hipriv_reset_device return err code = [%d].}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_tx_classify_switch
 ��������  : ָ���򿪻��߹ر�ҵ��ʶ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��23��
    ��    ��   : wanghao(w00357635)
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_tx_classify_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru  st_write_msg;
    oal_uint8        uc_flag         = 0;
    oal_uint8       *puc_value       = 0;
    oal_uint32       ul_ret          = OAL_SUCC;
    oal_uint32       ul_off_set      = 0;
    oal_int32        l_ret           = OAL_SUCC;
    oal_int8         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    // sh hipriv.sh "p2p-p2p0-0 set_tx_classify_switch 1/0"

    /* ��ȡ���ò��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_EDCA, "{wal_hipriv_set_tx_classify_switch::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_flag = (oal_uint8)oal_atoi(ac_name);
    /* �Ƿ����ò��� */
    if (uc_flag > 1)
    {
        OAM_WARNING_LOG0(0, OAM_SF_EDCA, "wal_hipriv_set_tx_classify_switch::invalid config, should be 0 or 1");
        return OAL_SUCC;
    }

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TX_CLASSIFY_LAN_TO_WLAN_SWITCH, OAL_SIZEOF(oal_uint8));
    puc_value = (oal_uint8 *)(st_write_msg.auc_value);
    *puc_value = uc_flag;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_EDCA, "{wal_hipriv_set_tx_classify_switch:: return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif  /* _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */

/*****************************************************************************
 �� �� ��  : wal_hipriv_wifi_enable
 ��������  : ˽�����ʹ��/ȥʹ��wifi
 �������  : pst_cfg_net_dev: net_device
             pc_param: ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��10��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_PM
OAL_STATIC oal_uint32  wal_hipriv_wifi_enable(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    /* OAM logģ��Ŀ��ص�����: hipriv "Hisilicon0 enable 0 | 1"
        �˴���������"1"��"0"����ac_name
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_wifi_enable::wal_get_cmd_one_arg return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����logģ����в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
       OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_wifi_enable::command param is error!}\r\n");
       return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_WIFI_EN, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_wifi_enable::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_pm_info
 ��������  : ˽�����PM״̬����Ϣά�����
 �������  : pst_cfg_net_dev: net_device
             pc_param: ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��10��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/

OAL_STATIC oal_uint32  wal_hipriv_pm_info(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
        ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PM_INFO, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pm_info::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_pm_enable
 ��������  : ˽�����PM���ܹرտ���
 �������  : pst_cfg_net_dev: net_device
             pc_param: ����
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��10��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_pm_enable(oal_net_device_stru *pst_cfg_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;


    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_wifi_enable::wal_get_cmd_one_arg return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����logģ����в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
       OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_wifi_enable::command param is error!}\r\n");
       return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PM_EN, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_cfg_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pm_enable::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
#endif

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
 �� �� ��  : wal_hipriv_beacon_offload_test
 ��������  : �ֶ�����host sleep, �����ڲ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��3��
    ��    ��   : l00311403
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_beacon_offload_test(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_int8                            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    wal_msg_write_stru                  st_write_msg;
    oal_uint8                           *uc_param;
    oal_uint32                          ul_off_set = 0;
    oal_int32                           l_ret;
    oal_uint32                          ul_ret;
    oal_uint8                           i;

    uc_param = (oal_uint8*)st_write_msg.auc_value;

    /* hipriv "Hisilicon0 beacon_offload_test param0 param1 param2 param3", */
    for (i=0; i<4; i++)
    {
        pc_param += ul_off_set;
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_beacon_offload_test::wal_get_cmd_one_arg param[%d] fails!}", i);
            return ul_ret;
        }
        *uc_param = (oal_uint8)oal_atoi((const oal_int8 *)ac_name);
        uc_param++;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_BEACON_OFFLOAD_TEST, OAL_SIZEOF(wal_specific_event_type_param_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 �� �� ��  : wal_hipriv_pci_reg_write
 ��������  : дpci�Ĵ���ֵ(hipriv "Hisilicon0 pciregwrite 0/1(�ĸ�оƬ) addr(16����) val(16����)")
 �������  : pst_net_dev: net_device
             pc_param   : �������������
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : daihu 00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_hipriv_pci_reg_write(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_bus_chip_stru   *pst_bus_chip = OAL_PTR_NULL;
    oal_int8            *pc_token;
    oal_int8            *pc_end;
    oal_int8            *pc_ctx;
    oal_int8            *pc_sep = " ";
    oal_int32            ul_addr;
    oal_uint32           ul_val = 0;
    oal_uint8            uc_pci_device_id = 0;

    /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_net_dev || OAL_PTR_NULL == pc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_pci_reg_write::pst_net_dev or pc_param null ptr error [%d] [%d]!}\r\n", pst_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡоƬID */
    pc_token = oal_strtok((oal_int8 *)pc_param, pc_sep, &pc_ctx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pci_reg_write::pci_device_id null ptr error [%d]!}\r\n", pc_token);
        return OAL_FAIL;
    }
    uc_pci_device_id = (oal_uint8)oal_strtol(pc_token, &pc_end, 10);

    /* ��ȡ�Ĵ�����ַ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pci_reg_write::pul_addr null ptr errorr [%d]!}\r\n", pc_token);
        return OAL_FAIL;
    }

    ul_addr = (oal_int32)oal_strtol(pc_token, &pc_end, 16);

    /* ��ȡ��Ҫд���ֵ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pci_reg_write::ul_val null ptr error [%d]!}\r\n", pc_token);
        return OAL_FAIL;
    }

    ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    /* OAL_IO_PRINT("pci_reg_write: addr = 0x%x, val = 0x%x.\n", ul_addr, ul_val); */
    //OAL_SPRINTF(ac_buf, OAL_SIZEOF(ac_buf), "pci_reg_write: addr = 0x%08x, val = 0x%08x.\n", ul_addr, ul_val);
    //oam_print(ac_buf);

    oal_bus_get_chip_instance(&pst_bus_chip, uc_pci_device_id);
    if(OAL_PTR_NULL == pst_bus_chip)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_pci_reg_write::pst_bus_chip is null.}\r\n");
        return OAL_FAIL;
    }

    oal_pci_write_config_dword(pst_bus_chip->pst_pci_device, ul_addr, ul_val);

    OAL_IO_PRINT("pci_reg_write succ: addr = 0x%x, val = 0x%x.\n", ul_addr, ul_val);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_pci_reg_read
 ��������  : ��pci�Ĵ���ֵ(hipriv "Hisilicon0 pciregread 0/1(�ĸ�оƬ) addr(16����)")
 �������  : pst_net_dev: net_device
             pc_param   : �������������
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : daihu 00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_hipriv_pci_reg_read(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_bus_chip_stru   *pst_bus_chip = OAL_PTR_NULL;
    oal_int8       *pc_token;
    oal_int8       *pc_end;
    oal_int8       *pc_ctx;
    oal_int8       *pc_sep = " ";
    oal_int32       ul_addr;
    oal_uint32      ul_val = 0;
    oal_uint8       uc_pci_device_id = 0;

    /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_net_dev || OAL_PTR_NULL == pc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_pci_reg_read::pst_net_dev or pc_param null ptr error [%d] [%d]!}\r\n", pst_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡоƬID */
    pc_token = oal_strtok((oal_int8 *)pc_param, pc_sep, &pc_ctx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pci_reg_read::pci_device_id null ptr error [%d]!}\r\n", pc_token);
        return OAL_FAIL;
    }
    /* ��ȡ�Ǹ�оƬ��pcie */
    uc_pci_device_id = (oal_uint8)oal_strtol(pc_token, &pc_end, 10);

    /* ��ȡ�Ĵ�����ַ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pci_reg_read::ul_addr null ptr error [%d]!}\r\n", pc_token);
        return OAL_FAIL;
    }

    ul_addr = (oal_int32)oal_strtol(pc_token, &pc_end, 16);

    oal_bus_get_chip_instance(&pst_bus_chip, uc_pci_device_id);
    if(OAL_PTR_NULL == pst_bus_chip)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pci_reg_read::pst_bus_chip is null��uc_pci_device_id[0].}\r\n", uc_pci_device_id);
        return OAL_FAIL;
    }

    oal_pci_read_config_dword(pst_bus_chip->pst_pci_device, ul_addr, &ul_val);

    //OAL_SPRINTF(ac_buf, OAL_SIZEOF(ac_buf), "pci_reg_read: addr=0x%08x, val=0x%08x.\n", ul_addr, ul_val);
    //oam_print(ac_buf);
    OAL_IO_PRINT("pci_reg_read succ:addr = 0x%x, val = 0x%x\n", ul_addr, ul_val);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_5115_reg_write
 ��������  : д5115���sys/pcie�Ĵ���
             ����:sh hipriv.sh "Hisilicon0 regw5115 sys|pcie 0/1(�����pcie�Ļ�Ҫ�����ĸ�оƬ) <addr>(�Ĵ�����ַ) <val>(д���4�ֽ�ֵ)"
             sys������оƬ��ֻ��һ��5115����5610оƬ���������0��1��һ��
 �������  : pst_net_dev: net_device
             pc_param   : �������������
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��4��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_hipriv_5115_reg_write(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_bus_chip_stru   *pst_bus_chip = OAL_PTR_NULL;
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_uint8             uc_pci_device_id = 0;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    oal_uint32            ul_val = 0;
    oal_uint              ul_flag;
#endif

    struct wal_reg_write_stru
    {
        oal_int8     *pc_reg_type;
        oal_uint32    ul_addr;
        oal_uint32    ul_val;
    }st_reg_write = {0};

    /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_net_dev || OAL_PTR_NULL == pc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_5115_reg_write::pst_net_dev or pc_param null ptr error [%d] [%d]!}\r\n", pst_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡоƬID */
    pc_token = oal_strtok((oal_int8 *)pc_param, pc_sep, &pc_ctx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_5115_reg_write::pci_device_id null ptr error [%d]!}\r\n", pc_token);
        return OAL_FAIL;
    }
    uc_pci_device_id = (oal_uint8)oal_strtol(pc_token, &pc_end, 10);

      /* ������� */
    /*lint -e960*/
    if ((0 != oal_strcmp(pc_token, "0")) && (0 != oal_strcmp(pc_token, "1")))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_5115_reg_write::err pci_device_id!}\r\n");
        return OAL_FAIL;
    }

    /* ��ȡҪ��ȡ�ļĴ������� */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (OAL_PTR_NULL == pc_token)
    {
        return OAL_FAIL;
    }

      /* ������� */
    if ((0 != oal_strcmp(pc_token, "sys")) && (0 != oal_strcmp(pc_token, "pcie")))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_5115_reg_write::err reg typer!}\r\n");
        return OAL_FAIL;
    }
    /*lint +e960*/
    st_reg_write.pc_reg_type = pc_token;

    /* ��ȡ�Ĵ�����ַ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (OAL_PTR_NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_reg_write.ul_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    /* ��ȡ��Ҫд���ֵ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (OAL_PTR_NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_reg_write.ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    //OAL_IO_PRINT("write 5115/5610 reg, addr = 0x%x, val = 0x%x.\n", st_reg_write.ul_addr, st_reg_write.ul_val);
    //OAL_SPRINTF(ac_buf, OAL_SIZEOF(ac_buf), "write 5115/5610 reg, addr = 0x%08x, val = 0x%08x.\n", st_reg_write.ul_addr, st_reg_write.ul_val);
    //oam_print(ac_buf);

    oal_bus_get_chip_instance(&pst_bus_chip, uc_pci_device_id);
    if(OAL_PTR_NULL == pst_bus_chip)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_5115_reg_write::pst_bus_chip is null.}\r\n");
        return OAL_FAIL;
    }

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if ((0 == oal_strcmp(st_reg_write.pc_reg_type, "sys")))   /* sys ctl */
    {
        oal_writel(st_reg_write.ul_val, g_pst_5115_sys_ctl + (st_reg_write.ul_addr - OAL_PCIE_SYS_BASE_PHYS));
    }
    else   /* chip id 0 */
    {
        oal_irq_save(&ul_flag, OAL_5115IRQ_WH5RW);

        if(0 == uc_pci_device_id)
        {
            /* ���ù���ģʽ��дcpu�� */
            ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_W_PCIE0);
            ul_val |= BIT21;
            oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_W_PCIE0);

            oal_writel(st_reg_write.ul_val, pst_bus_chip->p_pci_dbi_base + (st_reg_write.ul_addr - OAL_DBI_BASE_ADDR_0));

            /* ���ù���ģʽ���ָ�дwifi�� */
            ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_W_PCIE0);
            ul_val &= (~BIT21);
            oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_W_PCIE0);
        }
        else
/* chip id 1 */
        {
            /* ���ù���ģʽ��дcpu�� */
            ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_W_PCIE1);
            ul_val |= BIT21;
            oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_W_PCIE1);

            oal_writel(st_reg_write.ul_val, pst_bus_chip->p_pci_dbi_base + (st_reg_write.ul_addr - OAL_DBI_BASE_ADDR_1));

            /* ���ù���ģʽ���ָ�дwifi�� */
            ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_W_PCIE1);
            ul_val &= (~BIT21);
            oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_W_PCIE1);
        }

        oal_irq_restore(&ul_flag, OAL_5115IRQ_WH5RW);
    }
#endif

    OAL_IO_PRINT("write 5115/5610 reg succ, addr = 0x%x, val = 0x%x.\n", st_reg_write.ul_addr, st_reg_write.ul_val);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_5115_reg_read
 ��������  : ��5115���sys/pcie�Ĵ���
             ����:sh hipriv.sh "Hisilicon0 regw5115 sys|pcie 0/1(�����pcie�Ļ�Ҫ�����ĸ�оƬ) <addr>(�Ĵ�����ַ) <val>(д���4�ֽ�ֵ)"
             sys������оƬ��ֻ��һ��5115����5610оƬ���������0��1��һ��
 �������  : pst_net_dev: net_device
             pc_param   : �������������
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��4��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_hipriv_5115_reg_read(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_bus_chip_stru   *pst_bus_chip = OAL_PTR_NULL;
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";
    oal_uint8            uc_pci_device_id = 0;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        oal_uint32            ul_val = 0;
        oal_uint              ul_flag;
#endif

    struct wal_reg_info_stru
    {
        oal_int8     *pc_reg_type;
        oal_uint32    ul_addr;
        oal_uint32    ul_val;
    }st_reg_info = {0};

     /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_net_dev || OAL_PTR_NULL == pc_param))
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{wal_hipriv_5115_reg_read::pst_net_dev or pc_param null ptr error [%d] [%d]!}\r\n", pst_net_dev, pc_param);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡоƬID */
    pc_token = oal_strtok((oal_int8 *)pc_param, pc_sep, &pc_ctx);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_token))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_5115_reg_write::pci_device_id null ptr error [%d]!}\r\n", pc_token);
        return OAL_FAIL;
    }
    uc_pci_device_id = (oal_uint8)oal_strtol(pc_token, &pc_end, 10);

      /* ������� */
    /*lint -e960*/
    if ((0 != oal_strcmp(pc_token, "0")) && (0 != oal_strcmp(pc_token, "1")))
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_5115_reg_write::err pci_device_id!}\r\n");
        return OAL_FAIL;
    }

    /* ��ȡҪ��ȡ�ļĴ������� */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (OAL_PTR_NULL == pc_token)
    {
        return OAL_FAIL;
    }

    /* ������� */
    if ((0 != oal_strcmp(pc_token, "sys")) && (0 != oal_strcmp(pc_token, "pcie")))
    {
        return OAL_FAIL;
    }
    /*lint +e960*/

    st_reg_info.pc_reg_type = pc_token;

    /* ��ȡ��ַ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (OAL_PTR_NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_reg_info.ul_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    oal_bus_get_chip_instance(&pst_bus_chip, uc_pci_device_id);
    if(OAL_PTR_NULL == pst_bus_chip)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_5115_reg_write::pst_bus_chip is null.}\r\n");
        return OAL_FAIL;
    }

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if ((0 == oal_strcmp(st_reg_info.pc_reg_type, "sys")))   /* sys ctl */
    {
        st_reg_info.ul_val = oal_readl(g_pst_5115_sys_ctl + (st_reg_info.ul_addr - OAL_PCIE_SYS_BASE_PHYS));
    }
    else   /* pcie0 */
    {
        oal_irq_save(&ul_flag, OAL_5115IRQ_WH5RR);

        if(0 == uc_pci_device_id)
        {
            /* ���ù���ģʽ����cpu�� */
            ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_R_PCIE0);
            ul_val |= BIT21;
            oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_R_PCIE0);

            st_reg_info.ul_val = oal_readl(pst_bus_chip->p_pci_dbi_base + (st_reg_info.ul_addr - OAL_DBI_BASE_ADDR_0));

            /* ���ù���ģʽ���ָ���wifi�� */
            ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_R_PCIE0);
            ul_val &= (~BIT21);
            oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_R_PCIE0);
        }
        else
        {
            /* ���ù���ģʽ����cpu�� */
            ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_R_PCIE1);
            ul_val |= BIT21;
            oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_R_PCIE1);

            st_reg_info.ul_val = oal_readl(pst_bus_chip->p_pci_dbi_base + (st_reg_info.ul_addr - OAL_DBI_BASE_ADDR_1));

            /* ���ù���ģʽ���ָ���wifi�� */
            ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_R_PCIE1);
            ul_val &= (~BIT21);
            oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_R_PCIE1);
        }

        oal_irq_restore(&ul_flag, OAL_5115IRQ_WH5RR);
    }
#endif

    //OAL_SPRINTF(ac_buf, OAL_SIZEOF(ac_buf), "read 5115/5610 reg, addr = 0x%08x, val = 0x%08x.\n", st_reg_info.ul_addr, st_reg_info.ul_val);
    //oam_print(ac_buf);
    OAL_IO_PRINT("read 5115 reg succ, addr = 0x%x, val = 0x%x.\n", st_reg_info.ul_addr, st_reg_info.ul_val);

    return OAL_SUCC;
}
#endif /* #ifdef _PRE_WLAN_CHIP_TEST */

#endif

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#ifdef _PRE_WLAN_FEATURE_DFR

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : wal_hipriv_dfr_enable
 ��������  : �Ƿ�ʹ��dfr����
 �������  : pst_net_dev: net_device
             pc_param   : �������������
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��9��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dfr_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;
    oal_uint32                   ul_ret;
    oal_uint32                   ul_off_set;
    oal_int8                     ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                   *uc_enable_flag;
    oal_uint8                   *puc_value;

    /* hipriv "Hisilicon0 dfr_enable 1" */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pause_tid::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_enable_flag = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGIG_DFR_ENABLE, OAL_SIZEOF(oal_uint8));

    puc_value = (oal_uint8 *)(st_write_msg.auc_value);
    *puc_value = uc_enable_flag;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dfr_enable::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_trig_pcie_reset
 ��������  : ����pcie��λ
 �������  : pst_net_dev: net_device
             pc_param   : �������������
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��30��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_trig_pcie_reset(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TRIG_PCIE_RESET, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_trig_pcie_reset::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_trig_loss_tx_comp
 ��������  : ����pcie��λ��ʧ��������ж�
 �������  : pst_net_dev: net_device
             pc_param   : �������������
 �������  : ��
 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��30��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���
*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_trig_loss_tx_comp(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;
    oal_uint32                   ul_ret;
    oal_uint32                   ul_off_set;
    oal_int8                     ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                   ul_loss_cnt;
    oal_uint32                  *pul_value;

    /* hipriv "Hisilicon0 loss_tx_comp 1" */

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_pause_tid::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    ul_loss_cnt = (oal_uint32)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_TRIG_LOSS_TX_COMP, OAL_SIZEOF(oal_int32));

    pul_value = (oal_uint32 *)(st_write_msg.auc_value);
    *pul_value = ul_loss_cnt;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_trig_loss_tx_comp::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
#endif
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_max_user_num_each_device
 ��������  :  ���ø��豸�����û�����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��20��
    ��    ��   : wwx293929
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_max_user_num_each_device(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    mac_vap_stru             *pst_mac_vap;
    mac_device_stru         *pst_mac_device;
    oal_uint32                  ul_ret;
    oal_uint32                  ul_off_set;
    oal_int8                      ac_param[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint16                  us_user_val;

    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);
    if(OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_max_user_num_each_device::pst_mac_vap is null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }
    /* ��ȡdevice */
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_CFG, "{wal_hipriv_max_user_num_each_device::pst_mac_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_param, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_max_user_num_each_device::error code[%d]}\r\n", ul_ret);
        return ul_ret;
    }

    us_user_val = (oal_uint16)oal_atoi(ac_param);
    if (us_user_val > WLAN_ASSOC_USER_MAX_NUM_SPEC)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_max_user_num_each_device::uc_user_val[%d].}", us_user_val);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    pst_mac_device->us_user_nums_max = us_user_val;
    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_mode_ucast_data_dscr_param
 ��������  : ���ָ��Э��ģʽ���õ�������֡����������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��1��
    ��    ��   : l00330043
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_mode_ucast_data_dscr_param(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    mac_cfg_set_dscr_param_stru     *pst_set_dscr_param;
    wal_dscr_param_enum_uint8        en_param_index;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_DSCR, OAL_SIZEOF(mac_cfg_set_dscr_param_stru));

    /* ��������������������� */
    pst_set_dscr_param = (mac_cfg_set_dscr_param_stru *)(st_write_msg.auc_value);

    /* ��ȡ�������ֶ����������ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mode_ucast_data_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* �������õ�Э��ģʽ */
    if (!oal_strcmp("11ac", ac_arg))
    {
        pst_set_dscr_param->en_type = MAC_VAP_CONFIG_VHT_UCAST_DATA;
    }
    else if (!oal_strcmp("11n", ac_arg))
    {
        pst_set_dscr_param->en_type = MAC_VAP_CONFIG_HT_UCAST_DATA;
    }
    else if (!oal_strcmp("11ag", ac_arg))
    {
        pst_set_dscr_param->en_type = MAC_VAP_CONFIG_11AG_UCAST_DATA;
    }
    else if (!oal_strcmp("11b", ac_arg))
    {
        pst_set_dscr_param->en_type = MAC_VAP_CONFIG_11B_UCAST_DATA;
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_mode_ucast_data_dscr_param:: no such param for protocol_mode!}\r\n");
        return OAL_FAIL;
    }

    /* ��ȡ�������ֶ����������ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mode_ucast_data_dscr_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    /* ������������һ���ֶ� */
    for (en_param_index = 0; en_param_index < WAL_DSCR_PARAM_BUTT; en_param_index++)
    {
        if(!oal_strcmp(pauc_tx_dscr_param_name[en_param_index], ac_arg))
        {
            break;
        }
    }

    /* ��������Ƿ��� */
    if (WAL_DSCR_PARAM_BUTT == en_param_index)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_mode_ucast_data_dscr_param::no such param for tx dscr!}\r\n");
        return OAL_FAIL;
    }

    pst_set_dscr_param->uc_function_index = en_param_index;

    /* ����Ҫ����Ϊ����ֵ */
    pst_set_dscr_param->l_value = oal_strtol(pc_param, OAL_PTR_NULL, 0);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_set_dscr_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mode_ucast_data_dscr_param::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
#endif

#ifdef _PRE_DEBUG_MODE_USER_TRACK
/*****************************************************************************
 �� �� ��  : wal_hipriv_report_thrput_stat
 ��������  : �ϱ�����ֹͣ�ϱ�Ӱ��userʵʱ���µĲ���ͳ����Ϣ
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
OAL_STATIC oal_uint32  wal_hipriv_report_thrput_stat(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_usr_thrput_stru         st_usr_thrput;

    /* sh hipriv.sh "vap_name thrput_stat  XX:XX:XX:XX:XX;XX 0|1" */

    /* ��ȡ�û�mac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, st_usr_thrput.auc_user_macaddr, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_thrput_stat::wal_hipriv_get_mac_addr return [%d].}", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_thrput_stat::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    st_usr_thrput.uc_param = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_USR_THRPUT_STAT, OAL_SIZEOF(st_usr_thrput));

    /* ��д��Ϣ�壬���� */
    oal_memcopy(st_write_msg.auc_value, &st_usr_thrput, OAL_SIZEOF(st_usr_thrput));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_usr_thrput),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_thrput_stat::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#endif

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_rxch
 ��������  : ���ý���ͨ��
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��14��
    ��    ��   : pwx287475
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_set_rxch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_int8                         c_ch_idx = 0;
    oal_uint8                        uc_rxch = 0;
    oal_uint32                       ul_off_set = 0;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    wal_msg_write_stru               st_write_msg;

    /* ��ȡ����ͨ������ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_rx::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ����Ҫ����Ϊ����ֵ */
    uc_rxch = 0;
    for (c_ch_idx = 0; c_ch_idx < WAL_HIPRIV_CH_NUM; c_ch_idx++)
    {
        if ('0' == ac_arg[c_ch_idx])
        {
            continue;
        }
        else if ('1' == ac_arg[c_ch_idx])
        {
            uc_rxch += (oal_uint8)(1 << (WAL_HIPRIV_CH_NUM - c_ch_idx - 1));
        }
        /* ���������з�01���֣�����������4λ���쳣 */
        else
        {
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_rfch::input err!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    /* �������������λ���쳣 */
    if ('\0' != ac_arg[c_ch_idx])
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_rfch::input err!}\r\n");
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    *(oal_uint8 *)(st_write_msg.auc_value) = uc_rxch;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_RXCH, OAL_SIZEOF(oal_uint8));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
    wal_hipriv_wait_rsp(pst_net_dev, pc_param);
#endif

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_always_rx::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_dync_txpower
 ��������  : ��̬����У׼����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015/9/14
    ��    ��   : pwx287475
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dync_txpower(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                        uc_dync_power_flag;
    oal_int32                        l_idx = 0;

    /* ��ȡ��̬����У׼���ر�־ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dync_txpower::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��������Ϸ��Լ�� */
    while ('\0' != ac_arg[l_idx])
    {
        if (isdigit(ac_arg[l_idx]))
        {
            l_idx++;
            continue;
        }
        else
        {
            l_idx++;
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_dync_txpower::input illegal!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    /* ���������ֵ�ַ���ת��Ϊ���� */
    uc_dync_power_flag = (oal_uint8)oal_atoi(ac_arg);

    *(oal_uint8 *)(st_write_msg.auc_value) = uc_dync_power_flag;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DYNC_TXPOWER, OAL_SIZEOF(oal_uint8));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dync_txpower::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_report_ampdu_stat
 ��������  : �ϱ����������û�ĳһ��tid��ampduҵ������ͳ��
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
OAL_STATIC oal_uint32  wal_hipriv_report_ampdu_stat(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_ampdu_stat_stru         st_ampdu_param;

    /* sh hipriv.sh "vap_name ampdu_stat XX:XX:XX:XX:XX:XX tid_no 0|1" */

    /* ��ȡ�û�mac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, st_ampdu_param.auc_user_macaddr, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_ampdu_stat::wal_hipriv_get_mac_addr return [%d].}", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_ampdu_stat::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param += ul_off_set;

    st_ampdu_param.uc_tid_no = (oal_uint8)oal_atoi(ac_name);
    if (st_ampdu_param.uc_tid_no > WLAN_TID_MAX_NUM)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_ampdu_stat::input tid_no invalid. tid_no = [%d]!}\r\n", st_ampdu_param.uc_tid_no);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_ampdu_stat::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    st_ampdu_param.uc_param = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_REPORT_AMPDU_STAT, OAL_SIZEOF(st_ampdu_param));

    /* ��д��Ϣ�壬���� */
    oal_memcopy(st_write_msg.auc_value, &st_ampdu_param, OAL_SIZEOF(st_ampdu_param));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_ampdu_param),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_report_ampdu_stat::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_get_tx_comp_cnt
 ��������  : ͳ�Ʒ�������жϵĸ���;
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��18��,������
    ��    ��   : x00189397
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_tx_comp_cnt(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32      ul_ret          = OAL_SUCC;
    oal_uint32      ul_off_set      = 0;
    oal_uint8       uc_stat_flag    = 0;
    oal_int8        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    mac_vap_stru    *pst_mac_vap;

    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);
    if(NULL == pst_mac_vap)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_get_tx_comp_cnt::pst_mac_vap is null!}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ͳ�Ʒ�������ж��Ƿ�ʧ(�رվۺ�) sh hipriv.sh "Hisilicon0 tx_comp_cnt 0|1",
       0��ʾ����ͳ�ƴ����� 1��ʾ��ʾͳ�ƴ�����������",
    */

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_get_tx_comp_cnt::wal_get_cmd_one_arg fails!}\r\n");
        return ul_ret;
    }
    uc_stat_flag = (oal_uint8)oal_atoi((const oal_int8 *)ac_name);

    if( 0 == uc_stat_flag)
    {
        g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_data_num            = 0;
        g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_mgnt_num            = 0;
        g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_total_num  = 0;
        g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_uh1_num    = 0;
        g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_uh2_num    = 0;
        g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_bh1_num    = 0;
        g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_bh2_num    = 0;
        g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_bh3_num    = 0;

    }
    else
    {
        OAL_IO_PRINT("ul_tx_data_num = %d\n", g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_data_num);
        OAL_IO_PRINT("ul_tx_mgnt_num = %d\n", g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_mgnt_num);
        OAL_IO_PRINT("ul_tx_complete_total_num = %d\n", g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_total_num);
        OAL_IO_PRINT("ul_tx_complete_uh1_num = %d\n", g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_uh1_num);
        OAL_IO_PRINT("ul_tx_complete_uh2_num = %d\n", g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_uh2_num);
        OAL_IO_PRINT("ul_tx_complete_bh1_num = %d\n", g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_bh1_num);
        OAL_IO_PRINT("ul_tx_complete_bh2_num = %d\n", g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_bh2_num);
        OAL_IO_PRINT("ul_tx_complete_bh3_num = %d\n", g_ast_tx_complete_stat[pst_mac_vap->uc_device_id].ul_tx_complete_bh3_num);
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_debug_switch
 ��������  :  ����ά��������Ϳ���
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��,������
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_debug_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                          ul_off_set = 0;
    oal_uint8                           uc_debug_type = 0;
    oal_int8                            ac_debug_type[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                          ul_ret;
    oal_uint8                           uc_idx;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_debug_type, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAL_IO_PRINT("Error:wal_hipriv_set_debug_switch[%d] wal_get_cmd_one_arg return error code[%d]! \n", __LINE__, ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;

    if (ac_debug_type[0] == '?')
    {
        OAL_IO_PRINT("debug_switch <debug_type> <switch_state> \n");
        OAL_IO_PRINT("               0      0/1     -- when set register echo read value \n");
        return OAL_SUCC;
    }

    uc_debug_type = (oal_uint8)oal_atoi((const oal_int8 *)ac_debug_type);
    if (uc_debug_type >= MAX_DEBUG_TYPE_NUM)
    {
        OAL_IO_PRINT("Info: <debug_type> should be less than %d. \n", MAX_DEBUG_TYPE_NUM);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_debug_type, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAL_IO_PRINT("Error:wal_hipriv_set_debug_switch[%d] wal_get_cmd_one_arg return error code[%d]! \n", __LINE__, ul_ret);
        return ul_ret;
    }

    g_aul_debug_feature_switch[uc_debug_type] = (oal_uint32)oal_atoi((const oal_int8 *)ac_debug_type);
    if ((g_aul_debug_feature_switch[uc_debug_type] != OAL_SWITCH_ON) && (g_aul_debug_feature_switch[uc_debug_type] != OAL_SWITCH_OFF))
    {
        OAL_IO_PRINT("Error:switch_value must be 0 or 1. \n");
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    OAL_IO_PRINT("<debug_type>   <switch_value> \n");
    for (uc_idx = 0; uc_idx < MAX_DEBUG_TYPE_NUM; uc_idx++)
    {
        OAL_IO_PRINT("  %d          %d \n", uc_idx, g_aul_debug_feature_switch[uc_idx]);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_rx_filter_val
 ��������  : ��ȡ֡����������Ϣ
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��,������
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_rx_filter_val(oal_int8                **pc_param,
                                                hmac_cfg_rx_filter_stru *pst_rx_filter_val)
{
    oal_uint32                          ul_off_set = 0;
    oal_int8                            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                          ul_ret;

    ul_ret = wal_get_cmd_one_arg(*pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_rx_filter_val::wal_get_cmd_one_arg return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }

    *pc_param += ul_off_set;

    pst_rx_filter_val->uc_dev_mode = (oal_uint8)oal_atoi((const oal_int8 *)ac_name);
    if (pst_rx_filter_val->uc_dev_mode > 1)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{wal_hipriv_rx_filter_val::st_rx_filter_val.uc_dev_mode is exceed.[%d]}\r\n", pst_rx_filter_val->uc_dev_mode);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    ul_ret = wal_get_cmd_one_arg(*pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_rx_filter_val::wal_get_cmd_one_arg return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    *pc_param += ul_off_set;

    pst_rx_filter_val->uc_vap_mode = (oal_uint8)oal_atoi((const oal_int8 *)ac_name);

    if (pst_rx_filter_val->uc_vap_mode >= WLAN_VAP_MODE_BUTT)
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{wal_hipriv_rx_filter_val::uc_dev_mode is exceed! uc_dev_mode = [%d].}\r\n", pst_rx_filter_val->uc_vap_mode);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    ul_ret = wal_get_cmd_one_arg(*pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rx_filter_val::wal_get_cmd_one_arg return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }
    *pc_param += ul_off_set;
    pst_rx_filter_val->uc_vap_status = (oal_uint8)oal_atoi((const oal_int8 *)ac_name);

    if (pst_rx_filter_val->uc_vap_status >= MAC_VAP_STATE_BUTT)
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "{wal_hipriv_rx_filter_val::uc_dev_mode is exceed! uc_dev_mode = [%d].}\r\n", pst_rx_filter_val->uc_vap_status);
        return OAL_ERR_CODE_CONFIG_EXCEED_SPEC;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_rx_filter_val
 ��������  : ����ĳһ״̬��֡��������ֵ
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��,������
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_rx_filter_val(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                          ul_ret;
    oal_int32                           l_ret;
    hmac_cfg_rx_filter_stru             st_rx_filter_val = {0};
    wal_msg_write_stru                  st_write_msg;
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";

    ul_ret = wal_hipriv_rx_filter_val(&pc_param, &st_rx_filter_val);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rx_filter_val::wal_hipriv_rx_filter_val return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }

    /* 0--дĳһVAP״̬��֡����ֵ */
    st_rx_filter_val.uc_write_read = 0;

    /* ��ȡ��Ҫд���ֵ */
    pc_token = oal_strtok(pc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_rx_filter_val::pc_token is null}\r\n");
        return OAL_FAIL;
    }

    st_rx_filter_val.ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);


    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_RX_FILTER_VAL, OAL_SIZEOF(hmac_cfg_rx_filter_stru));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value, &st_rx_filter_val, OAL_SIZEOF(hmac_cfg_rx_filter_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(hmac_cfg_rx_filter_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rx_filter_val::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_get_rx_filter_val
 ��������  : ����ĳһ״̬��֡��������ֵ
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��,������
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_rx_filter_val(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                          ul_ret;
    oal_int32                           l_ret;
    hmac_cfg_rx_filter_stru             st_rx_filter_val = {0};
    wal_msg_write_stru                  st_write_msg;

    ul_ret = wal_hipriv_rx_filter_val(&pc_param, &st_rx_filter_val);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rx_filter_val::wal_hipriv_rx_filter_val return err_code[%d]}\r\n", ul_ret);
        return ul_ret;
    }

    /* 1--��ĳһVAP״̬��֡����ֵ */
    st_rx_filter_val.uc_write_read = 1;
    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_RX_FILTER_VAL, OAL_SIZEOF(hmac_cfg_rx_filter_stru));

    /* ��������������� */
    oal_memcopy(st_write_msg.auc_value, &st_rx_filter_val, OAL_SIZEOF(hmac_cfg_rx_filter_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(hmac_cfg_rx_filter_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rx_filter_val::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_rx_filter_val
 ��������  : ����ĳһ״̬��֡��������ֵ
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��,������
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_rx_filter_en(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;
    oal_uint32                      ul_ret = OAL_SUCC;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_rx_filter_en = 0;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_vap_nss::wal_get_cmd_one_arg fails!}\r\n");
        return ul_ret;
    }

    pc_param += ul_off_set;
    uc_rx_filter_en = (oal_uint8)oal_atoi((const oal_int8 *)ac_name);

    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_rx_filter_en;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_RX_FILTER_EN, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                              WAL_MSG_TYPE_WRITE,
                              WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                              (oal_uint8 *)&st_write_msg,
                              OAL_FALSE,
                              OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_set_rx_filter_en::wal_hipriv_reset_device return err code = [%d].}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_rx_filter_val
 ��������  : ����ĳһ״̬��֡��������ֵ
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��,������
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_rx_filter_en(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_RX_FILTER_EN, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_version::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_scan_test
 ��������  : ɨ���������
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
OAL_STATIC oal_uint32  wal_hipriv_scan_test(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[15];
    oal_int8                        ac_scan_type[15];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint8                       uc_bandwidth;
    wal_msg_write_stru              st_write_msg;
    mac_ioctl_scan_test_config_stru *pst_scan_test;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_scan_type, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "wal_hipriv_scan_test: get first arg fail.");
        return OAL_FAIL;
    }

    pc_param = pc_param + ul_off_set;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_CFG, "wal_hipriv_scan_test: get second arg fail.");
        return OAL_FAIL;
    }
    uc_bandwidth = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                            ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SCAN_TEST, OAL_SIZEOF(mac_ioctl_scan_test_config_stru));

    /* ��������������� */
    pst_scan_test = (mac_ioctl_scan_test_config_stru *)(st_write_msg.auc_value);
    oal_memcopy(pst_scan_test->ac_scan_type, ac_scan_type, sizeof(ac_scan_type));
    pst_scan_test->en_bandwidth = uc_bandwidth;

    l_ret = wal_send_cfg_event(pst_net_dev,
                      WAL_MSG_TYPE_WRITE,
                      WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_ioctl_scan_test_config_stru),
                      (oal_uint8 *)&st_write_msg,
                      OAL_FALSE,
                      OAL_PTR_NULL);
    if (OAL_SUCC != l_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::wal_send_cfg_event fail.return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : wal_hipriv_freq_adjust
 ��������  : Ƶƫ������������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��29��
    ��    ��   : h00212953
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_freq_adjust(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_int8                       *pc_token;
    oal_int8                       *pc_end;
    oal_int8                       *pc_ctx;
    oal_int8                       *pc_sep = " ";
    mac_cfg_freq_adjust_stru        st_freq_adjust_ctl;

    /* ��ȡ������Ƶ */
    pc_token = oal_strtok(pc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_freq_adjust_ctl.us_pll_int = (oal_uint16)oal_strtol(pc_token, &pc_end, 16);

    /* ��ȡС����Ƶ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_freq_adjust_ctl.us_pll_frac = (oal_uint16)oal_strtol(pc_token, &pc_end, 16);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FREQ_ADJUST, OAL_SIZEOF(st_freq_adjust_ctl));

    /* ��д��Ϣ�壬���� */
    oal_memcopy(st_write_msg.auc_value, &st_freq_adjust_ctl, OAL_SIZEOF(st_freq_adjust_ctl));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_freq_adjust_ctl),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_freq_adjust::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_SUPPORT_ACS
/*****************************************************************************
 �� �� ��  : wal_hipriv_acs
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��22��
    ��    ��   : gaolin
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_acs(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru    st_write_msg;
    oal_uint16            us_len;
    oal_int32             l_ret;

    if (OAL_UNLIKELY(WAL_MSG_WRITE_MAX_LEN <= OAL_STRLEN(pc_param)))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_acs:: pc_param overlength is %d}\n", OAL_STRLEN(pc_param));
        oal_print_hex_dump((oal_uint8 *)pc_param, WAL_MSG_WRITE_MAX_LEN, 32, "wal_hipriv_acs: param is overlong:");
        return OAL_FAIL;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ACS_CONFIG, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_acs::return err code [%d]!}\r\n", l_ret);

        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_PERFORM_STAT
/*****************************************************************************
 �� �� ��  : wal_hipriv_stat_tid_thrpt
 ��������  : ͳ��ָ��tid��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_stat_tid_thrpt(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_total_offset = 0;
    mac_cfg_stat_param_stru        *pst_stat_param;

    /* vap0 stat_tid_thrpt xx xx xx xx xx xx(mac��ַ) tid_num stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_STAT, OAL_SIZEOF(mac_cfg_stat_param_stru));
    pst_stat_param = (mac_cfg_stat_param_stru *)(st_write_msg.auc_value);

    pst_stat_param->en_stat_type    = MAC_STAT_TYPE_TID_THRPT;
    pst_stat_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, auc_mac_addr, &ul_total_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_thrpt::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    oal_set_mac_addr(pst_stat_param->auc_mac_addr, auc_mac_addr);

    /* ��ȡtidno */
    pc_param = pc_param + ul_total_offset;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_thrpt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    pst_stat_param->uc_tidno = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡͳ������ */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_thrpt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pst_stat_param->us_stat_period = (oal_uint16)oal_atoi(ac_name);

    /* ��ȡͳ�ƴ��� */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_thrpt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pst_stat_param->us_stat_num = (oal_uint16)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_stat_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_thrpt::wal_hipriv_stat_tid_thrpt return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_stat_user_thrpt
 ��������  : ͳ��ָ���û���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_stat_user_thrpt(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_total_offset = 0;
    mac_cfg_stat_param_stru        *pst_stat_param;

    /* vap0 stat_user_thrpt xx xx xx xx xx xx(mac��ַ) stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_STAT, OAL_SIZEOF(mac_cfg_stat_param_stru));
    pst_stat_param = (mac_cfg_stat_param_stru *)(st_write_msg.auc_value);

    pst_stat_param->en_stat_type    = MAC_STAT_TYPE_USER_THRPT;
    pst_stat_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, auc_mac_addr, &ul_total_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_stat_user_thrpt::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    oal_set_mac_addr(pst_stat_param->auc_mac_addr, auc_mac_addr);

    /* ��ȡͳ������ */
    pc_param = pc_param + ul_total_offset;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_user_thrpt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pst_stat_param->us_stat_period = (oal_uint16)oal_atoi(ac_name);

    /* ��ȡͳ�ƴ��� */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_user_thrpt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pst_stat_param->us_stat_num = (oal_uint16)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_stat_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_user_thrpt::wal_hipriv_stat_tid_thrpt return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_stat_vap_thrpt
 ��������  : ͳ��ָ���û���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_stat_vap_thrpt(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_stat_param_stru        *pst_stat_param;

    /* vap0 stat_vap_thrpt stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_STAT, OAL_SIZEOF(mac_cfg_stat_param_stru));
    pst_stat_param = (mac_cfg_stat_param_stru *)(st_write_msg.auc_value);

    pst_stat_param->en_stat_type    = MAC_STAT_TYPE_VAP_THRPT;
    pst_stat_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /* ��ȡͳ������ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_vap_thrpt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pst_stat_param->us_stat_period = (oal_uint16)oal_atoi(ac_name);

    /* ��ȡͳ�ƴ��� */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_vap_thrpt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pst_stat_param->us_stat_num = (oal_uint16)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_stat_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_vap_thrpt::wal_hipriv_stat_tid_thrpt return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_stat_tid_per
 ��������  : ͳ��ָ��tid��per
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_stat_tid_per(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_stat_param_stru        *pst_stat_param;
    oal_uint32                      ul_total_offset = 0;

    /* vap0 stat_tid_per xx xx xx xx xx xx(mac��ַ) tid_num stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_STAT, OAL_SIZEOF(mac_cfg_stat_param_stru));
    pst_stat_param = (mac_cfg_stat_param_stru *)(st_write_msg.auc_value);

    pst_stat_param->en_stat_type    = MAC_STAT_TYPE_TID_PER;
    pst_stat_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, auc_mac_addr, &ul_total_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_per::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    oal_set_mac_addr(pst_stat_param->auc_mac_addr, auc_mac_addr);

    /* ��ȡtidno */
    pc_param = pc_param + ul_total_offset;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_per::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    pst_stat_param->uc_tidno = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡͳ������ */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_per::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pst_stat_param->us_stat_period = (oal_uint16)oal_atoi(ac_name);

    /* ��ȡͳ�ƴ��� */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_per::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pst_stat_param->us_stat_num = (oal_uint16)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_stat_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_per::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_stat_tid_delay
 ��������  : ͳ��ָ��tid��delay
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_stat_tid_delay(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_stat_param_stru        *pst_stat_param;
    oal_uint32                      ul_total_offset = 0;

    /* vap0 stat_tid_delay xx xx xx xx xx xx(mac��ַ) tid_num stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_STAT, OAL_SIZEOF(mac_cfg_stat_param_stru));
    pst_stat_param = (mac_cfg_stat_param_stru *)(st_write_msg.auc_value);

    pst_stat_param->en_stat_type    = MAC_STAT_TYPE_TID_DELAY;
    pst_stat_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, auc_mac_addr, &ul_total_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_delay::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    oal_set_mac_addr(pst_stat_param->auc_mac_addr, auc_mac_addr);

    /* ��ȡtidno */
    pc_param = pc_param + ul_total_offset;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_delay::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    pst_stat_param->uc_tidno = (oal_uint8)oal_atoi(ac_name);

    /* ��ȡͳ������ */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_delay::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pst_stat_param->us_stat_period = (oal_uint16)oal_atoi(ac_name);

    /* ��ȡͳ�ƴ��� */
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_delay::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pst_stat_param->us_stat_num = (oal_uint16)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_stat_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_stat_tid_delay::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_display_tid_thrpt
 ��������  : ͳ��ָ��tid��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_display_tid_thrpt(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_display_param_stru     *pst_display_param;
    oal_uint32                      ul_total_offset = 0;

    /* vap0 stat_tid_thrpt xx xx xx xx xx xx(mac��ַ) tid_num stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_DISPLAY, OAL_SIZEOF(mac_cfg_display_param_stru));
    pst_display_param = (mac_cfg_display_param_stru *)(st_write_msg.auc_value);

    pst_display_param->en_stat_type    = MAC_STAT_TYPE_TID_THRPT;
    pst_display_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, auc_mac_addr, &ul_total_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_display_tid_thrpt::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    oal_set_mac_addr(pst_display_param->auc_mac_addr, auc_mac_addr);

    /* ��ȡtidno */
    pc_param = pc_param + ul_total_offset;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_display_tid_thrpt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    pst_display_param->uc_tidno = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_display_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_display_tid_thrpt::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_display_user_thrpt
 ��������  : ͳ��ָ���û���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_display_user_thrpt(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_display_param_stru     *pst_display_param;
    oal_uint32                      ul_total_offset = 0;

    /* vap0 stat_user_thrpt xx xx xx xx xx xx(mac��ַ) stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_DISPLAY, OAL_SIZEOF(mac_cfg_display_param_stru));
    pst_display_param = (mac_cfg_display_param_stru *)(st_write_msg.auc_value);

    pst_display_param->en_stat_type    = MAC_STAT_TYPE_USER_THRPT;
    pst_display_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, auc_mac_addr, &ul_total_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_display_user_thrpt::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    oal_set_mac_addr(pst_display_param->auc_mac_addr, auc_mac_addr);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_display_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_display_user_thrpt::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_display_vap_thrpt
 ��������  : ͳ��ָ���û���������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_display_vap_thrpt(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    mac_cfg_display_param_stru     *pst_display_param;

    /* vap0 stat_vap_thrpt stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_DISPLAY, OAL_SIZEOF(mac_cfg_display_param_stru));
    pst_display_param = (mac_cfg_display_param_stru *)(st_write_msg.auc_value);

    pst_display_param->en_stat_type    = MAC_STAT_TYPE_VAP_THRPT;
    pst_display_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_display_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_display_vap_thrpt::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_display_tid_per
 ��������  : ͳ��ָ��tid��per
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_display_tid_per(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_display_param_stru     *pst_display_param;
    oal_uint32                      ul_total_offset = 0;

    /* vap0 stat_tid_per xx xx xx xx xx xx(mac��ַ) tid_num stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_DISPLAY, OAL_SIZEOF(mac_cfg_display_param_stru));
    pst_display_param = (mac_cfg_display_param_stru *)(st_write_msg.auc_value);

    pst_display_param->en_stat_type    = MAC_STAT_TYPE_TID_PER;
    pst_display_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, auc_mac_addr, &ul_total_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_display_tid_per::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    oal_set_mac_addr(pst_display_param->auc_mac_addr, auc_mac_addr);

    /* ��ȡtidno */
    pc_param = pc_param + ul_total_offset;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_display_tid_per::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    pst_display_param->uc_tidno = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_display_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_display_tid_per::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_display_tid_delay
 ��������  : ͳ��ָ��tid��delay
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��14��
    ��    ��   : xiechunhui
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_display_tid_delay(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_display_param_stru     *pst_display_param;
    oal_uint32                      ul_total_offset = 0;

    /* vap0 stat_tid_delay xx xx xx xx xx xx(mac��ַ) tid_num stat_period(ͳ������ms) stat_num(ͳ�ƴ���) */

    /* �����¼��ڴ� */
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PFM_DISPLAY, OAL_SIZEOF(mac_cfg_display_param_stru));
    pst_display_param = (mac_cfg_display_param_stru *)(st_write_msg.auc_value);

    pst_display_param->en_stat_type    = MAC_STAT_TYPE_TID_DELAY;
    pst_display_param->uc_vap_id       = ((mac_vap_stru *)OAL_NET_DEV_PRIV(pst_net_dev))->uc_vap_id;

    /* ��ȡmac��ַ */
    ul_ret = wal_hipriv_get_mac_addr(pc_param, auc_mac_addr, &ul_total_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_display_tid_delay::wal_hipriv_get_mac_addr failed!}\r\n");
        return ul_ret;
    }
    oal_set_mac_addr(pst_display_param->auc_mac_addr, auc_mac_addr);

    /* ��ȡtidno */
    pc_param = pc_param + ul_total_offset;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_display_tid_delay::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    pst_display_param->uc_tidno = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_display_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_display_tid_delay::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_DAQ
/*****************************************************************************
 �� �� ��  : wal_hipriv_data_acq
 ��������  :  ����ά��������Ϳ���
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��,������
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_data_acq(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    while (' ' == *pc_param)
    {
        ++pc_param;
    }
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DATA_ACQ, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
       OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_data_acq::return err code[%d]!}\r\n", l_ret);
      return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_CHIP_TEST
/*****************************************************************************
 �� �� ��  : wal_hipriv_lpm_soc_mode
 ��������  : �����������SOC�ĵ͹��Ĺ��ܿ�����ر�
       hipriv "Hisilicon0 lpm_soc_mode 0|1|2|3|4(����gating|PCIE RD BY PASS|mem precharge|PCIE L0-S|PCIE L1-0) 0|1(disable|enable)"
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_lpm_soc_mode(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    mac_cfg_lpm_soc_set_stru       *pst_set_para;
    oal_uint32                      ul_off_set = 0;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];


    /* SOC���ܲ���ģʽ����, hipriv "Hisilicon0 lpm_soc_mode 0|1|2|3|4(����gating|PCIE RD BY PASS|mem precharge|PCIE L0-S|PCIE L1-0)
                        0|1(disable|enable) pcie_idle(PCIE�͹��Ŀ���ʱ��1~7us) "*/

    pst_set_para = (mac_cfg_lpm_soc_set_stru*)(st_write_msg.auc_value);
    /* ��������������� */
    OAL_MEMZERO(ac_name, WAL_HIPRIV_CMD_NAME_MAX_LEN);

    /* ��ȡ����ģʽ*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_set_para->en_mode= (mac_lpm_soc_set_enum_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡ�������ǹر�*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_set_para->uc_on_off = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡPCIE����ʱ������*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_set_para->uc_pcie_idle = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LPM_SOC_MODE,OAL_SIZEOF(mac_cfg_lpm_soc_set_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_lpm_soc_set_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_soc_mode::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_lpm_chip_state
 ��������  : �����������оƬ˯�߻���оƬ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_lpm_chip_state(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set;
    mac_cfg_lpm_sleep_para_stru     *pst_set_para;

    pst_set_para = (mac_cfg_lpm_sleep_para_stru*)(st_write_msg.auc_value);
    /* ��������������� */
    OAL_MEMZERO(ac_name, WAL_HIPRIV_CMD_NAME_MAX_LEN);

    wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    pst_set_para->uc_pm_switch = (mac_lpm_state_enum_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡ��ʱ˯�߲���*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_set_para->us_sleep_ms = (oal_uint16)oal_atoi(ac_name);


    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LPM_CHIP_STATE,OAL_SIZEOF(mac_cfg_lpm_sleep_para_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_lpm_sleep_para_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_chip_state::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_lpm_psm_param
 ��������  : ���ܲ����Ĵ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_lpm_psm_param(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    mac_cfg_lpm_psm_param_stru     *pst_psm_para;
    oal_uint32                      ul_off_set = 0;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];


    /* psm���ܼĴ�������, hipriv "Hisilicon0 lpm_psm_param 0|1(ps off|ps on) 0|1(DTIM|listen intval) xxx(listen intervalֵ) xxx(TBTT offset)"*/

    pst_psm_para = (mac_cfg_lpm_psm_param_stru*)(st_write_msg.auc_value);
    /* ��������������� */
    OAL_MEMZERO(ac_name, WAL_HIPRIV_CMD_NAME_MAX_LEN);

    /* ��ȡ�����Ƿ���*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_psm_para->uc_psm_on = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;


    /* ��ȡ��DTIM���ѻ���listen interval���� */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_psm_para->uc_psm_wakeup_mode = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡlisten interval��ֵ */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_psm_para->us_psm_listen_interval = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡTBTT�ж���ǰ����ֵ */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_psm_para->us_psm_tbtt_offset = (oal_uint8)oal_atoi(ac_name);
    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LPM_PSM_PARAM,OAL_SIZEOF(mac_cfg_lpm_psm_param_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_lpm_psm_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_psm_param::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_lpm_smps_mode
 ��������  : �����������SMPS����ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_lpm_smps_mode(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set;
    oal_uint8                       uc_smps_mode;

    wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);

    uc_smps_mode = (oal_uint8)oal_atoi(ac_name);
    if (uc_smps_mode >= 3)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_smps_mode::invalid choice [%d]!}\r\n", uc_smps_mode);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }
    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    /* ��������������� */
    *((oal_uint8 *)(st_write_msg.auc_value)) = uc_smps_mode;

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LPM_SMPS_MODE,OAL_SIZEOF(oal_uint8));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_smps_mode::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_lpm_smps_stub
 ��������  : ���������׮����AP�෢��ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_lpm_smps_stub(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    mac_cfg_lpm_smps_stub_stru     *pst_smps_stub;
    oal_uint32                      ul_off_set = 0;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    /*smps ap������׮, hipriv "vap0 lpm_smps_stub 0|1|2(off|����|˫��) 0|1(�Ƿ�RTS)*/
    /*��������������� */
    pst_smps_stub = (mac_cfg_lpm_smps_stub_stru*)(st_write_msg.auc_value);
    OAL_MEMZERO(ac_name, WAL_HIPRIV_CMD_NAME_MAX_LEN);

    /* ��ȡ׮����*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_smps_stub->uc_stub_type = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* RTS */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_smps_stub->uc_rts_en= (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LPM_SMPS_STUB,OAL_SIZEOF(mac_cfg_lpm_smps_stub_stru) );

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_lpm_smps_stub_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_smps_stub::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_lpm_txopps_set
 ��������  : �����������TXOP PS����ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_lpm_txopps_set(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    mac_cfg_lpm_txopps_set_stru    *pst_txopps_set;
    oal_uint32                      ul_off_set = 0;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];


    /* txop ps���ܼĴ�������, hipriv "Hisilicon0 lpm_txopps_set 0|1(off|on|debug) 0|1(contion1 off|on) 0|1(condition2 off|on)"*/
    /* ��������������� */
    pst_txopps_set = (mac_cfg_lpm_txopps_set_stru*)(st_write_msg.auc_value);
    OAL_MEMZERO(ac_name, WAL_HIPRIV_CMD_NAME_MAX_LEN);

    /* ��ȡ�����Ƿ���*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_txopps_set->uc_txop_ps_on = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;


    /* ��ȡcondition1 */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_txopps_set->uc_conditon1 = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡcondition2*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_txopps_set->uc_conditon2 = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LPM_TXOP_PS_SET,OAL_SIZEOF(mac_cfg_lpm_txopps_set_stru) );

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_lpm_txopps_set_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_txopps_set::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_lpm_txopps_tx_stub
 ��������  : ����TXOP PS����ģʽ�Ĵ�׮���������÷��͵�n������ʱ���Դ���ĵ�ַ���ߴ����Partial AID����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_lpm_txopps_tx_stub(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                  st_write_msg;
    oal_int32                           l_ret;
    mac_cfg_lpm_txopps_tx_stub_stru    *pst_txopps_tx_stub;
    oal_uint32                          ul_off_set = 0;
    oal_int8                            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    /* txop ps�������Դ�׮����, hipriv "vap0 lpm_txopps_tx_stub 0|1(off|on) xxx(�ڼ�������׮)"*/
    /* ��������������� */
    pst_txopps_tx_stub = (mac_cfg_lpm_txopps_tx_stub_stru*)(st_write_msg.auc_value);
    OAL_MEMZERO(ac_name, WAL_HIPRIV_CMD_NAME_MAX_LEN);

    /* ��ȡ׮����*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_txopps_tx_stub->uc_stub_on = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /* ��ȡ�ڼ������Ĵ�׮ */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_txopps_tx_stub->us_begin_num = (oal_uint8)oal_atoi(ac_name);
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;


    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LPM_TXOP_TX_STUB,OAL_SIZEOF(mac_cfg_lpm_txopps_tx_stub_stru) );

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_lpm_txopps_tx_stub_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_txopps_tx_stub::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_lpm_tx_data
 ��������  : ָ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_lpm_tx_data(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    mac_cfg_lpm_tx_data_stru       *pst_lpm_tx_data;
    oal_uint32                      ul_off_set = 0;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    /* ���Է���, hipriv "vap0 lpm_tx_data xxx(����) xxx(����) xx:xx:xx:xx:xx:xx(Ŀ��mac) xxx(AC����)"*/
    pst_lpm_tx_data = (mac_cfg_lpm_tx_data_stru*)(st_write_msg.auc_value);
    OAL_MEMZERO(ac_name, WAL_HIPRIV_CMD_NAME_MAX_LEN);

    /* ��ȡ��������*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_lpm_tx_data->us_num= (oal_uint16)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡ�������� */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_lpm_tx_data->us_len = (oal_uint16)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡĿ�ĵ�ַ */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    oal_strtoaddr(ac_name, pst_lpm_tx_data->auc_da);
    pc_param = pc_param + ul_off_set;

    /* ��ȡ����AC���� */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_lpm_tx_data->uc_ac = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;
    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LPM_TX_DATA,OAL_SIZEOF(mac_cfg_lpm_tx_data_stru) );

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_lpm_tx_data_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_tx_data::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_lpm_tx_probe_request
 ��������  : ָ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z52447
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_lpm_tx_probe_request(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    mac_cfg_lpm_tx_data_stru       *pst_lpm_tx_data;
    oal_uint32                      ul_off_set = 0;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    /* ���Է���, hipriv "vap0 lpm_tx_probe_request 0|1(����|����) xx:xx:xx:xx:xx:xx(����ģʽ��BSSID)"*/
    pst_lpm_tx_data = (mac_cfg_lpm_tx_data_stru*)(st_write_msg.auc_value);
    OAL_MEMZERO(ac_name, WAL_HIPRIV_CMD_NAME_MAX_LEN);

    /* ��ȡ����or����probe request*/
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    pst_lpm_tx_data->uc_positive = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /* ��ȡbssid */
    wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    oal_strtoaddr(ac_name, pst_lpm_tx_data->auc_da);
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_LPM_TX_PROBE_REQUEST,OAL_SIZEOF(mac_cfg_lpm_tx_data_stru) );

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_lpm_tx_data_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_lpm_tx_probe_request::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_remove_user_lut
 ��������  : ɾ���ظ��û�lut��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��24��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_hipriv_remove_user_lut(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    mac_cfg_remove_lut_stru        *pst_param;          /* ���︴��ɾ���û���������Ľṹ�� */
    oal_uint32                      ul_off_set = 0;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN] = {0,0,0,0,0,0};
    mac_vap_stru                   *pst_mac_vap;
    oal_uint16                      us_user_idx;


    /* ɾ���ָ��û�lut��, hipriv "vap0 remove_lut xx:xx:xx:xx:xx:xx(mac��ַ) 0|1(�ָ�/ɾ��)" */
    pst_param = (mac_cfg_remove_lut_stru *)(st_write_msg.auc_value);

    /* ��ȡMAC��ַ�ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_remove_user_lut::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
    }

    /* ��ַ�ַ���ת��ַ���� */
    oal_strtoaddr(ac_name, auc_mac_addr);

    /* ��ȡ �ָ�/ɾ�� ��ʶ */
    pc_param += ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_remove_user_lut::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    pst_param->uc_is_remove = (oal_uint8)oal_atoi(ac_name);

    /* ����mac��ַ���û� */
    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);

    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, auc_mac_addr, &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_remove_user_lut::no such user!}\r\n");

        return ul_ret;
    }

    pst_param->us_user_idx = us_user_idx;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_REMOVE_LUT, OAL_SIZEOF(mac_cfg_kick_user_param_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_kick_user_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_hipriv_remove_user_lut::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_send_frame
 ��������  : ָ��֡���ͣ�ָ��RA,ָ��BSSID�����Ϳ���֡���߹���֡
 �������  : dev, param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��21��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_send_frame(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                  st_write_msg;
    oal_uint32                          ul_offset;
    oal_int8                            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                          ul_ret;
    mac_cfg_send_frame_param_stru      *pst_test_send_frame;
    oal_uint8                           auc_mac_addr[WLAN_MAC_ADDR_LEN];

    mac_test_frame_type_enum_uint8      en_frame_type;
    oal_uint8                           uc_pkt_num = 0;

    /* ��ȡ֡���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_offset);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_frame::get frame type err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    en_frame_type = (mac_test_frame_type_enum_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_offset;

    /* ��ȡ֡��Ŀ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_offset);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_frame::get frame num err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    uc_pkt_num = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_offset;

    /* ��ȡMAC��ַ�ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_offset);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_frame::get mac err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    /* ��ַ�ַ���ת��ַ���� */
    oal_strtoaddr(ac_name, auc_mac_addr);
    pc_param += ul_offset;

    /***************************************************************************
                                 ���¼���dmac�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SEND_FRAME, OAL_SIZEOF(mac_cfg_send_frame_param_stru));

    /* ��������������� */
    pst_test_send_frame = (mac_cfg_send_frame_param_stru *)(st_write_msg.auc_value);
    oal_set_mac_addr(pst_test_send_frame->auc_mac_ra, auc_mac_addr);
    pst_test_send_frame->en_frame_type = en_frame_type;
    pst_test_send_frame->uc_pkt_num = uc_pkt_num;

    ul_ret = (oal_uint32)wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_send_frame_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_frame::wal_send_cfg_event return err_code [%d]!}\r\n", ul_ret);
        return (oal_uint32)ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_rx_pn
 ��������  : ����RX_PN_LUT_CONFIG�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_rx_pn(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                       ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       auc_mac_addr[OAL_MAC_ADDR_LEN];
    mac_vap_stru                   *pst_mac_vap;
    oal_uint16                      us_user_idx;
    mac_cfg_set_rx_pn_stru         *pst_rx_pn;
    oal_uint16                      us_pn = 0;
    /* ��ȡMAC��ַ�ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rx_pn::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��ַ�ַ���ת��ַ���� */
    oal_strtoaddr(ac_name, auc_mac_addr);
    pc_param += ul_off_set;

    /* ��ȡpn�� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_rx_pn::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    us_pn = (oal_uint16)oal_atoi(ac_name);
    pc_param += ul_off_set;

    /* ����mac��ַ���û� */
    pst_mac_vap = OAL_NET_DEV_PRIV(pst_net_dev);
    ul_ret = mac_vap_find_user_by_macaddr(pst_mac_vap, auc_mac_addr, &us_user_idx);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_set_rx_pn::no such user!}\r\n");

        return ul_ret;
    }

    pst_rx_pn = (mac_cfg_set_rx_pn_stru *)(st_write_msg.auc_value);
    pst_rx_pn->us_rx_pn = us_pn;
    pst_rx_pn->us_user_idx = us_user_idx;
    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(mac_cfg_set_rx_pn_stru);
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_RX_PN_REG, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_hipriv_set_rx_pn::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_soft_retry
 ��������  : ����Software Retry������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_soft_retry(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_software_retry = 0;
    oal_uint8                       uc_retry_test = 0;
    mac_cfg_set_soft_retry_stru    *pst_soft_retry;
    /* �Ƿ�Ϊtest�����ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_soft_retry::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    uc_retry_test = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_off_set;

    /* ��ȡ�趨��ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_soft_retry::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    uc_software_retry = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_off_set;

    pst_soft_retry = (mac_cfg_set_soft_retry_stru *)(st_write_msg.auc_value);
    pst_soft_retry->uc_retry_test = uc_retry_test;
    pst_soft_retry->uc_software_retry = uc_software_retry;
    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(mac_cfg_set_soft_retry_stru);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_SOFT_RETRY, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_soft_retry::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_open_addr4
 ��������  : ��ͷ����4��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_open_addr4(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_open_addr4 = 0;

    /* ��ȡ�趨��ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_open_addr4::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    uc_open_addr4 = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_off_set;


    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_open_addr4;
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_OPEN_ADDR4, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_open_addr4::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_open_wmm_test
 ��������  : ���������/�ر�WMM
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_open_wmm_test(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_open_wmm = 0;

    /* ��ȡ�趨��ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_open_wmm_test::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    uc_open_wmm = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_off_set;


    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_open_wmm;
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_OPEN_WMM_TEST, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_open_wmm_test::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_chip_test_open
 ��������  : ��оƬ��֤����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_chip_test_open(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_chip_test_open = 0;

    /* ��ȡ�趨��ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_chip_test_open::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    uc_chip_test_open = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_off_set;


    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_chip_test_open;
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_CHIP_TEST_OPEN, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_chip_test_open::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_coex
 ��������  : ���ù��濪��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��4��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_coex(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint32                      ul_mac_ctrl = 0;
    oal_uint32                      ul_rf_ctrl  = 0;
    mac_cfg_coex_ctrl_param_stru   *pst_coex_ctrl;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_coex::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    ul_mac_ctrl = (oal_uint32)oal_atoi(ac_name);
    pc_param   += ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_coex::wal_get_cmd_2nd_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    ul_rf_ctrl = (oal_uint32)oal_atoi(ac_name);
    pc_param  += ul_off_set;


    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/

    pst_coex_ctrl = (mac_cfg_coex_ctrl_param_stru *)(st_write_msg.auc_value);
    pst_coex_ctrl->ul_mac_ctrl = ul_mac_ctrl;
    pst_coex_ctrl->ul_rf_ctrl  = ul_rf_ctrl;

    us_len = OAL_SIZEOF(mac_cfg_coex_ctrl_param_stru);
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_COEX, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_coex::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_dfx
 ��������  : ����DFX���Կ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��3��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_dfx(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_dfx::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����logģ����в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_dfx::the log switch command is error [%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DFX_SWITCH, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_dfx::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
/*****************************************************************************
 �� �� ��  : wal_hipriv_test_enable_pmf
 ��������  : chip test ǿ��ʹ��pmf
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2015��1��13��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_enable_pmf(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{

    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;

    oal_int32                       l_cfg_rst;
    oal_uint16                      us_len;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    oal_uint8                       uc_chip_test_open = 0;

    /* ��ȡ�趨��ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_enable_pmf::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    uc_chip_test_open = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_off_set;

    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    us_len = OAL_SIZEOF(oal_uint8);
    *(oal_uint8 *)(st_write_msg.auc_value) = uc_chip_test_open;
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PMF_ENABLE, us_len);

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_enable_pmf::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : wal_hipriv_test_send_action
 ��������  : ���������action֡
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC  oal_uint32 wal_hipriv_test_send_action(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_ret;
    oal_int32                       l_cfg_rst;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_off_set = 0;
    mac_cfg_send_action_param_stru  st_action_param;

    OAL_MEMZERO(&st_action_param, OAL_SIZEOF(mac_cfg_send_action_param_stru));

    /* ��ȡuc_category�趨��ֵ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_test_send_action::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    st_action_param.uc_category = (oal_uint8)oal_atoi(ac_name);
    pc_param += ul_off_set;

    /* ��ȡĿ�ĵ�ַ */
    ul_ret = wal_get_cmd_one_arg((oal_int8*)pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_test_send_action::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, st_action_param.auc_mac_da);
    pc_param = pc_param + ul_off_set;
    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, &st_action_param, OAL_SIZEOF(mac_cfg_send_action_param_stru));
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SEND_ACTION, OAL_SIZEOF(mac_cfg_send_action_param_stru));

    l_cfg_rst = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_send_action_param_stru),
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_cfg_rst))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_test_send_action::wal_send_cfg_event return err_code [%d]!}\r\n", l_cfg_rst);
      return (oal_uint32)l_cfg_rst;
    }

    return OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : wal_hipriv_send_pspoll
 ��������  : sta��ps-poll
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_send_pspoll(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SEND_PSPOLL, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_pspoll::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_send_nulldata
 ��������  : sta��nulldata
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_send_nulldata(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru           st_write_msg;
    oal_int32                    l_ret;
    mac_cfg_tx_nulldata_stru    *pst_tx_nulldata;
    oal_uint32                   ul_off_set = 0;
    oal_int8                     ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN] = {0};
    oal_uint32                   ul_ret;

    pst_tx_nulldata = (mac_cfg_tx_nulldata_stru *)st_write_msg.auc_value;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_nulldata::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    pst_tx_nulldata->l_is_psm = oal_atoi((const oal_int8 *)ac_name);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_nulldata::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    pst_tx_nulldata->l_is_qos = oal_atoi((const oal_int8 *)ac_name);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_nulldata::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param += ul_off_set;
    pst_tx_nulldata->l_tidno = oal_atoi((const oal_int8 *)ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SEND_NULLDATA, OAL_SIZEOF(mac_cfg_tx_nulldata_stru));
    oal_memcopy((oal_void *)st_write_msg.auc_value,
                (const oal_void *)pst_tx_nulldata,
                OAL_SIZEOF(mac_cfg_tx_nulldata_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_tx_nulldata_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_nulldata::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_show_mgmt_stat
 ��������  : ��ӡ����֡ͳ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��10��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_clear_all_stat(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;

    /***************************************************************************
                                 ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_CLEAR_ALL_STAT, OAL_SIZEOF(oal_uint32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_clear_all_stat::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_parse_ops_param
 ��������  : �����ַ�����CT WINDOW ����
 �������  : oal_int8 *pc_param
             mac_cfg_p2p_ops_param_stru *pst_p2p_ops_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32   wal_parse_ops_param(oal_int8 *pc_param, mac_cfg_p2p_ops_param_stru *pst_p2p_ops_param)
{
    oal_uint32                  ul_ret;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_off_set;
    oal_int32                   l_ct_window;

    /* ������һ���������Ƿ�ʹ��OPS ���� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_parse_ops_param::wal_get_cmd_one_arg 1 return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param   += ul_off_set;

    if (0 == (oal_strcmp("0", ac_name)))
    {
        pst_p2p_ops_param->en_ops_ctrl  = OAL_FALSE;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        pst_p2p_ops_param->en_ops_ctrl = OAL_TRUE;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_parse_ops_param::the log switch command[%c] is error!}",(oal_uint8)ac_name[0]);
        OAL_IO_PRINT("{wal_parse_ops_param::the log switch command is error [%6s....]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /* �����ڶ���������OPS ����CT Window */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    OAL_IO_PRINT("wal_parse_ops_param:ct window %s\r\n", ac_name);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_parse_ops_param::wal_get_cmd_one_arg 2 return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    l_ct_window = oal_atoi(ac_name);
    if (l_ct_window < 0 || l_ct_window > 255)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_parse_ops_param::ct window out off range [%d]!}\r\n", l_ct_window);
        return OAL_FAIL;
    }
    else
    {
        pst_p2p_ops_param->uc_ct_window = (oal_uint8)l_ct_window;
    }

    return OAL_SUCC;
}


#ifdef  _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 �� �� ��  : wal_parse_noa_param
 ��������  : �����ַ�����NOA ����
 �������  : oal_int8 *pc_param
             mac_cfg_p2p_noa_param_stru *pst_p2p_noa_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32   wal_parse_noa_param(oal_int8 *pc_param, mac_cfg_p2p_noa_param_stru *pst_p2p_noa_param)
{
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_off_set;
    oal_int32                   l_count;
    oal_uint32                  ul_ret;


    /* ������һ��������start_time */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_parse_noa_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param   += ul_off_set;

    pst_p2p_noa_param->ul_start_time = (oal_uint32)oal_atoi(ac_name);

    /* �����ڶ���������dulration */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_parse_noa_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param   += ul_off_set;

    pst_p2p_noa_param->ul_duration = (oal_uint32)oal_atoi(ac_name);

    /* ����������������interval */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_parse_noa_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param   += ul_off_set;

    pst_p2p_noa_param->ul_interval = (oal_uint32)oal_atoi(ac_name);

    /* �������ĸ�������count */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_parse_noa_param::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param   += ul_off_set;

    l_count = oal_atoi(ac_name);

    if (l_count < 0 || l_count > 255)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_parse_ops_param::ct window out off range [%d]!}\r\n", l_count);
        return OAL_FAIL;
    }
    else
    {
        pst_p2p_noa_param->uc_count  = (oal_uint8)l_count;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_set_p2p_ps
 ��������  : оƬ��֤������P2P ���ܼĴ���
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_p2p_ps(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    mac_cfg_p2p_ops_param_stru  st_p2p_ops_param;
    mac_cfg_p2p_noa_param_stru  st_p2p_noa_param;
    mac_cfg_p2p_stat_param_stru st_p2p_stat_param;
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;
    oal_uint16                  us_len;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_set_p2p_ps::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    pc_param   += ul_off_set;

    /* ��Խ������Ĳ�ͬ�����logģ����в�ͬ������ */
    if (0 == (oal_strcmp("ops", ac_name)))
    {
        /* ����P2P OPS ���ܲ��� */
        ul_ret = wal_parse_ops_param(pc_param, &st_p2p_ops_param);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
        OAM_INFO_LOG2(0, OAM_SF_CFG, "{wal_hipriv_set_p2p_ps ops::ctrl[%d], ct_window[%d]!}\r\n",
                        st_p2p_ops_param.en_ops_ctrl,
                        st_p2p_ops_param.uc_ct_window);
        us_len = OAL_SIZEOF(mac_cfg_p2p_ops_param_stru);
        WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_P2P_PS_OPS, OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
        oal_memcopy(st_write_msg.auc_value, &st_p2p_ops_param, OAL_SIZEOF(mac_cfg_p2p_ops_param_stru));
    }
    else if (0 == (oal_strcmp("noa", ac_name)))
    {
        /* ����P2P NOA ���ܲ��� */
        ul_ret = wal_parse_noa_param(pc_param, &st_p2p_noa_param);
        if (OAL_SUCC != ul_ret)
        {
            return ul_ret;
        }
        OAM_INFO_LOG4(0, OAM_SF_CFG, "{wal_hipriv_set_p2p_ps noa::start_time[%d], duration[%d], interval[%d], count[%d]!}\r\n",
                        st_p2p_noa_param.ul_start_time,
                        st_p2p_noa_param.ul_duration,
                        st_p2p_noa_param.ul_interval,
                        st_p2p_noa_param.uc_count);
        us_len = OAL_SIZEOF(mac_cfg_p2p_noa_param_stru);
        WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_P2P_PS_NOA, OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));
        oal_memcopy(st_write_msg.auc_value, &st_p2p_noa_param, OAL_SIZEOF(mac_cfg_p2p_noa_param_stru));
    }
    else if (0 == (oal_strcmp("statistics", ac_name)))
    {
        /* ��ȡP2P����ͳ�� */
        /* �����������鿴����ͳ�� */
        ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_parse_ops_param::wal_get_cmd_one_arg 1 return err_code [%d]!}\r\n", ul_ret);
            return ul_ret;
        }
        pc_param   += ul_off_set;
        if (0 == (oal_strcmp("0", ac_name)))
        {
            st_p2p_stat_param.uc_p2p_statistics_ctrl = 0;
        }
        else if (0 == (oal_strcmp("1", ac_name)))
        {
            st_p2p_stat_param.uc_p2p_statistics_ctrl = 1;
        }
        else
        {
            OAM_WARNING_LOG0(0, OAM_SF_CFG, "{wal_hipriv_set_p2p_ps statistics::wrong parm\r\n}");
            return OAL_FAIL;
        }

        us_len = OAL_SIZEOF(mac_cfg_p2p_stat_param_stru);
        WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_P2P_PS_STAT, us_len);
        oal_memcopy(st_write_msg.auc_value, &st_p2p_stat_param, us_len);
        OAM_INFO_LOG2(0, OAM_SF_CFG, "{wal_hipriv_set_p2p_ps statistics::ctrl[%d], len:%d!}\r\n",
                        st_p2p_stat_param.uc_p2p_statistics_ctrl, us_len);
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_p2p_ps::the log switch command is error [%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_p2p_ps::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_oma
 ��������  : ����Proxy STA��oma��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��23��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_oma(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_set_oma_param_stru     *pst_set_oma_param;
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];

    /* ����Proxy STA ��OMA��ַ���� sh hipriv.sh "vap0 set_vma xx xx xx xx xx xx" */

    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_PROXYSTA, "{wal_hipriv_set_oma::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, auc_mac_addr);

    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_OMA, OAL_SIZEOF(mac_cfg_set_oma_param_stru));

    /* ��������������� */
    pst_set_oma_param = (mac_cfg_set_oma_param_stru *)(st_write_msg.auc_value);
    oal_set_mac_addr(pst_set_oma_param->auc_mac_addr, auc_mac_addr);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_set_oma_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_oma::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_proxysta_switch
 ��������  : ����proxystaģ��ʹ�ܿ��أ�1������0�ر�
 �������  : oal_net_device_stru *pst_net_dev,
             oal_int8 *pc_param,
 �������  : ��
 �� �� ֵ  : OAL_SUCC, ���ÿ��سɹ�
             Others,   ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��15��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_proxysta_switch(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    /* proxystaģ��Ŀ��ص�����: hipriv "Hisilicon0 proxysta_switch 0 | 1"
        �˴���������"1"��"0"����ac_name
    */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }

    /* ��Խ������Ĳ�ͬ�����proxystaģ����в�ͬ������ */
    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PROXYSTA_SWITCH, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#endif

#ifdef _PRE_WLAN_DFT_REG
/*****************************************************************************
 �� �� ��  : wal_hipriv_dump_reg
 ��������  : ������Ҫ�鿴�ļĴ������� ����Ϊphy/mac/soc/abb/rf +
 �������  : pst_net_dev�� pc_param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��23��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dump_reg(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oam_reg_type_enum_uint8         en_reg_type = 0;
    oal_uint32                      ul_reg_subtype = 0;
    oal_uint8                       uc_flag = 0;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;


    if ((0 != oal_strcmp(ac_name, "soc"))
    && (0 != oal_strcmp(ac_name, "mac"))
    && (0 != oal_strcmp(ac_name, "phy"))
    && (0 != oal_strcmp(ac_name, "abb"))
    && (0 != oal_strcmp(ac_name, "rf")))
    {
        return OAL_FAIL;
    }

    if (0 == oal_strcmp(ac_name, "soc"))
    {
        en_reg_type = OAM_REG_SOC;
    }
    if (0 == oal_strcmp(ac_name, "mac"))
    {
        en_reg_type = OAM_REG_MAC;
    }
    if (0 == oal_strcmp(ac_name, "phy"))
    {
        en_reg_type = OAM_REG_PHY;
    }
    if (0 == oal_strcmp(ac_name, "abb"))
    {
        en_reg_type = OAM_REG_ABB;
    }
    if (0 == oal_strcmp(ac_name, "rf"))
    {
        en_reg_type = OAM_REG_RF;
    }

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    ul_reg_subtype = (oal_uint32)oal_atoi(ac_name);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    uc_flag = (oal_uint8)oal_atoi(ac_name);

    oam_reg_set_flag(en_reg_type, ul_reg_subtype, uc_flag);
    OAL_IO_PRINT("dump reg: regtype %u, subtype %u,uc flag %u\n",
                        en_reg_type,
                        ul_reg_subtype,
                        uc_flag);
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_hipriv_dump_reg_evt
 ��������  : ������Ҫ�鿴�ļĴ������� ����Ϊtbtt/rx/tx/prd + cnt
 �������  : pst_net_dev�� pc_param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��23��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dump_reg_evt(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oam_reg_evt_enum_uint32         en_evt_type = 0;
    oal_uint32                      ul_tick = 0;
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    /* ��ȡ�¼����� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg_evt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;


    if ((0 != oal_strcmp(ac_name, "tbtt"))
    && (0 != oal_strcmp(ac_name, "rx"))
    && (0 != oal_strcmp(ac_name, "tx"))
    && (0 != oal_strcmp(ac_name, "prd"))
    && (0 != oal_strcmp(ac_name, "usr"))
    && (0 != oal_strcmp(ac_name, "all"))
    && (0 != oal_strcmp(ac_name, "err")))
    {
        return OAL_FAIL;
    }

    if (0 == oal_strcmp(ac_name, "tbtt"))
    {
        en_evt_type = OAM_REG_EVT_TBTT;
    }
    if (0 == oal_strcmp(ac_name, "rx"))
    {
        en_evt_type = OAM_REG_EVT_RX;
    }
    if (0 == oal_strcmp(ac_name, "tx"))
    {
        en_evt_type = OAM_REG_EVT_TX;
    }
    if (0 == oal_strcmp(ac_name, "prd"))
    {
        en_evt_type = OAM_REG_EVT_PRD;
    }
    if (0 == oal_strcmp(ac_name, "usr"))
    {
        en_evt_type = OAM_REG_EVT_USR;
    }
    if (0 == oal_strcmp(ac_name, "err"))
    {
        en_evt_type = OAM_REG_EVT_ERR;
    }
    if (0 == oal_strcmp(ac_name, "all"))
    {
        en_evt_type = OAM_REG_EVT_BUTT;
    }

    /* ��ȡtick */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg_evt::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    ul_tick = (oal_uint32)oal_atoi(ac_name);

    oam_reg_set_evt(en_evt_type, ul_tick);

    if(OAM_REG_EVT_USR != en_evt_type)
    {
        return OAL_SUCC;
    }

    /***************************************************************************
                             ���¼���wal�㴥������ˢ�º��ϱ�
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_DUMP_REG, 0);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg_evt::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_dump_reg_addr
 ��������  : ���ݼĴ����ĵ�ַ���üĴ����Ŀ���
 �������  : pst_net_dev�� pc_param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��23��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dump_reg_addr(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oam_reg_type_enum_uint8         en_reg_type = 0;
    oal_uint8                       uc_flag = 0;
    oal_uint32                      ul_addr_start = 0;
    oal_uint32                      ul_addr_end = 0;
    oal_int8                       *pc_end;
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg_addr::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    /* ƫ�ƣ�ȡ��һ������ */
    pc_param = pc_param + ul_off_set;

    if ((0 != oal_strcmp(ac_name, "soc"))
    && (0 != oal_strcmp(ac_name, "mac"))
    && (0 != oal_strcmp(ac_name, "phy"))
    && (0 != oal_strcmp(ac_name, "abb"))
    && (0 != oal_strcmp(ac_name, "rf")))
    {
        return OAL_FAIL;
    }

    if (0 == oal_strcmp(ac_name, "soc"))
    {
        en_reg_type = OAM_REG_SOC;
    }
    if (0 == oal_strcmp(ac_name, "mac"))
    {
        en_reg_type = OAM_REG_MAC;
    }
    if (0 == oal_strcmp(ac_name, "phy"))
    {
        en_reg_type = OAM_REG_PHY;
    }
    if (0 == oal_strcmp(ac_name, "abb"))
    {
        en_reg_type = OAM_REG_ABB;
    }
    if (0 == oal_strcmp(ac_name, "rf"))
    {
        en_reg_type = OAM_REG_RF;
    }

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg_addr::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    //ul_addr_start = (oal_uint32)oal_atoi(ac_name);
    ul_addr_start = (oal_uint32)oal_strtol(ac_name, &pc_end, 16);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg_addr::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    //ul_addr_end = (oal_uint32)oal_atoi(ac_name);
    ul_addr_end = (oal_uint32)oal_strtol(ac_name, &pc_end, 16);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_dump_reg_addr::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    uc_flag = (oal_uint8)oal_atoi(ac_name);

    if((ul_addr_start % 4)
        || (ul_addr_end % 4)
        || (ul_addr_start > ul_addr_end))
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{wal_hipriv_dump_reg_addr::start %u, end %u Err [%d] [%d]!}\r\n", ul_addr_start, ul_addr_end);
        return OAL_FAIL;
    }
    oam_reg_set_flag_addr(en_reg_type, ul_addr_start, ul_addr_end, uc_flag);
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_dump_reg_info
 ��������  : �鿴�Ĵ�����ȡ������Ϣ
 �������  : pst_net_dev�� pc_param
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��23��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_dump_reg_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oam_reg_info();
    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_MCAST
/*****************************************************************************
 �� �� ��  : wal_hipriv_m2u_snoop_on
 ��������  : ������ر��鲥ת��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��11��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_m2u_snoop_on(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_uint8                        uc_m2u_snoop_on;
    oal_uint8                        uc_m2u_mcast_mode;
    mac_cfg_m2u_snoop_on_param_stru *pst_m2u_snoop_on_param;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_m2u_snoop_on::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_m2u_snoop_on = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_m2u_snoop_on::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_m2u_mcast_mode = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_M2U_SNOOP_ON, OAL_SIZEOF(mac_cfg_m2u_snoop_on_param_stru));

    /* ��������������� */
    pst_m2u_snoop_on_param = (mac_cfg_m2u_snoop_on_param_stru *)(st_write_msg.auc_value);
    pst_m2u_snoop_on_param->uc_m2u_snoop_on   = uc_m2u_snoop_on;
    pst_m2u_snoop_on_param->uc_m2u_mcast_mode = uc_m2u_mcast_mode;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_m2u_snoop_on_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_M2U, "{wal_hipriv_m2u_snoop_on::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_m2u_add_deny_table
 ��������  : �����鲥
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��11��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_m2u_add_deny_table(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_uint32                       ul_deny_group_addr;
    mac_add_m2u_deny_table_stru     *pst_m2u_deny_table_param;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_m2u_add_deny_table::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    ul_deny_group_addr = oal_in_aton((oal_uint8 *)ac_name);

    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_ADD_M2U_DENY_TABLE, OAL_SIZEOF(mac_add_m2u_deny_table_stru));

    /* ��������������� */
    pst_m2u_deny_table_param = (mac_add_m2u_deny_table_stru *)(st_write_msg.auc_value);
    pst_m2u_deny_table_param->ul_deny_group_addr = ul_deny_group_addr;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_add_m2u_deny_table_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_M2U, "{wal_hipriv_m2u_add_deny_table::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_m2u_cfg_deny_table
 ��������  : ����鲥�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��28��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_m2u_cfg_deny_table(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_uint8                        uc_m2u_clear_deny_table;
    oal_uint8                        uc_m2u_show_deny_table;
    mac_clg_m2u_deny_table_stru     *pst_m2u_deny_table_param;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_m2u_cfg_deny_table::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_m2u_clear_deny_table = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_m2u_cfg_deny_table::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_m2u_show_deny_table = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_M2U_DENY_TABLE, OAL_SIZEOF(mac_clg_m2u_deny_table_stru));

    /* ��������������� */
    pst_m2u_deny_table_param = (mac_clg_m2u_deny_table_stru *)(st_write_msg.auc_value);
    pst_m2u_deny_table_param->uc_m2u_clear_deny_table   = uc_m2u_clear_deny_table;
    pst_m2u_deny_table_param->uc_m2u_show_deny_table    = uc_m2u_show_deny_table;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_clg_m2u_deny_table_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_M2U, "{wal_hipriv_m2u_snoop_on::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : wal_hipriv_m2u_show_snoop_table
 ��������  : show snoop table
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��28��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_m2u_show_snoop_table(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_uint8                        uc_m2u_show_snoop_table;
    mac_show_m2u_snoop_table_stru   *pst_m2u_show_snoop_table_param;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_m2u_cfg_deny_table::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_m2u_show_snoop_table = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_SHOW_M2U_SNOOP_TABLE, OAL_SIZEOF(mac_show_m2u_snoop_table_stru));

    /* ��������������� */
    pst_m2u_show_snoop_table_param = (mac_show_m2u_snoop_table_stru *)(st_write_msg.auc_value);
    pst_m2u_show_snoop_table_param->uc_m2u_show_snoop_table   = uc_m2u_show_snoop_table;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_show_m2u_snoop_table_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_M2U, "{wal_hipriv_m2u_snoop_on::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_hipriv_igmp_packet_xmit
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_igmp_packet_xmit(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_cfg_mpdu_ampdu_tx_param_stru *pst_aggr_tx_on_param;
    oal_uint8                       uc_packet_num;
    oal_uint8                       uc_tid;
    oal_uint16                      uc_packet_len;
    oal_uint8                       auc_ra_addr[WLAN_MAC_ADDR_LEN];

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_M2U, "{wal_hipriv_packet_xmit::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    uc_tid = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param = pc_param + ul_off_set;
    uc_packet_num = (oal_uint8)oal_atoi(ac_name);

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_M2U, "{wal_hipriv_packet_xmit::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    uc_packet_len = (oal_uint16)oal_atoi(ac_name);
    pc_param += ul_off_set;

    /* ��ȡMAC��ַ�ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_M2U, "{wal_hipriv_packet_xmit::get mac err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    /* ��ַ�ַ���ת��ַ���� */
    oal_strtoaddr(ac_name, auc_ra_addr);
    pc_param += ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_IGMP_PACKET_XMIT, OAL_SIZEOF(mac_cfg_mpdu_ampdu_tx_param_stru));

    /* ��������������� */
    pst_aggr_tx_on_param = (mac_cfg_mpdu_ampdu_tx_param_stru *)(st_write_msg.auc_value);
    pst_aggr_tx_on_param->uc_packet_num = uc_packet_num;
    pst_aggr_tx_on_param->uc_tid        = uc_tid;
    pst_aggr_tx_on_param->us_packet_len = uc_packet_len;
    oal_set_mac_addr(pst_aggr_tx_on_param->auc_ra_mac, auc_ra_addr);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_mpdu_ampdu_tx_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_packet_xmit::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
/*****************************************************************************
 �� �� ��  : wal_hipriv_proxyarp_on
 ��������  : ������ر�proxyarp����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_proxyarp_on(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_bool_enum_uint8              en_proxyarp_on;
    mac_proxyarp_en_stru            *pst_proxyarp_on_param;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_proxyarp_on::get cmd  err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    en_proxyarp_on = (oal_uint8)oal_atoi(ac_name);
    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PROXYARP_EN, OAL_SIZEOF(mac_proxyarp_en_stru));

    /* ��������������� */
    pst_proxyarp_on_param = (mac_proxyarp_en_stru *)(st_write_msg.auc_value);
    pst_proxyarp_on_param->en_proxyarp = en_proxyarp_on;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_proxyarp_en_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_proxyarp_on::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_proxyarp_info
 ��������  : ��ӡproxyarp������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��8��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_DEBUG_MODE
OAL_STATIC oal_uint32  wal_hipriv_proxyarp_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_int32                        l_ret;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_PROXYARP_INFO, OAL_SIZEOF(mac_cfg_m2u_snoop_on_param_stru));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH,
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_proxyarp_info::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif /* #ifdef _PRE_DEBUG_MODE */

#endif /* #ifdef _PRE_WLAN_FEATURE_PROXY_ARP */

#ifdef _PRE_WLAN_FEATURE_SMPS
#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : wal_hipriv_get_smps_info
 ��������  :  ����ά��������Ϳ���
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��,������
    ��    ��   : z00241943
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_smps_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_SMPS_INFO, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_smps_info::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif
#endif

#ifdef _PRE_WLAN_PROFLING_MIPS
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_mips
 ��������  :
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_mips(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                       l_mips_type;
    oal_int32                       l_switch;
    wal_msg_write_stru              st_write_msg;
    oal_mips_type_param_stru       *pst_mips_type_param;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
    l_mips_type = oal_atoi((const oal_int8 *)ac_name);

    ul_ret = wal_get_cmd_one_arg(pc_param + ul_off_set, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
    l_switch = oal_atoi((const oal_int8 *)ac_name);


    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SET_MIPS, OAL_SIZEOF(oal_mips_type_param_stru));
    pst_mips_type_param = (oal_mips_type_param_stru *)st_write_msg.auc_value;
    pst_mips_type_param->l_mips_type = l_mips_type;
    pst_mips_type_param->l_switch    = l_switch;


    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_mips_type_param_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_mips::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_show_mips
 ��������  :
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_show_mips(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                       l_mips_type;
    wal_msg_write_stru              st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        return ul_ret;
    }
    l_mips_type = oal_atoi((const oal_int8 *)ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SHOW_MIPS, OAL_SIZEOF(oal_uint32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_mips_type;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_mips::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : wal_hipriv_resume_rx_intr_fifo
 ��������  : ʹ��rx intr fifo����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_resume_rx_intr_fifo(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru                  st_write_msg;
    oal_uint32                          ul_off_set;
    oal_int8                            ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                          ul_ret;
    oal_int32                           l_ret;
    mac_cfg_resume_rx_intr_fifo_stru   *pst_param;
    oal_uint8                           uc_is_on;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_resume_rx_intr_fifo::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_is_on = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_RESUME_RX_INTR_FIFO, OAL_SIZEOF(mac_cfg_resume_rx_intr_fifo_stru));

    /* ��������������� */
    pst_param = (mac_cfg_resume_rx_intr_fifo_stru *)(st_write_msg.auc_value);
    pst_param->uc_is_on = uc_is_on;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_resume_rx_intr_fifo_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_resume_rx_intr_fifo::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : wal_hipriv_set_ampdu_mmss
 ��������  : ����AMPDU��mmss�ֶ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_set_ampdu_mmss(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru       st_write_msg;
    oal_uint32               ul_off_set;
    oal_int8                 ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    mac_cfg_ampdu_mmss_stru  st_ampdu_mmss_cfg;
    oal_uint32               ul_ret;
    oal_int32                l_ret;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ampdu_mmss::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }
    pc_param += ul_off_set;

    st_ampdu_mmss_cfg.uc_mmss_val = (oal_uint8)oal_atoi(ac_name);
    if (st_ampdu_mmss_cfg.uc_mmss_val > 7)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ampdu_mmss::mmss invilid [%d]!}\r\n", st_ampdu_mmss_cfg.uc_mmss_val);
        OAL_IO_PRINT("{wal_hipriv_set_ampdu_mmss::mmss invilid [%d]!}\r\n", st_ampdu_mmss_cfg.uc_mmss_val);

        return OAL_FAIL;
    }

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_AMPDU_MMSS, OAL_SIZEOF(st_ampdu_mmss_cfg));

    /* ��д��Ϣ�壬���� */
    oal_memcopy(st_write_msg.auc_value, &st_ampdu_mmss_cfg, OAL_SIZEOF(st_ampdu_mmss_cfg));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(st_ampdu_mmss_cfg),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_set_ampdu_mmss::wal_send_cfg_event return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
/*****************************************************************************
 �� �� ��  : wal_hipriv_arp_offload_enable
 ��������  : �������/�ر�ARP offload����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_hipriv_arp_offload_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                     ul_ret;
    oal_int32                      l_ret;
    oal_uint32                     ul_off_set;
    oal_switch_enum_uint8          en_switch;
    oal_int8                       ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    wal_msg_write_stru             st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_CFG, "wal_hipriv_arp_offload_enable return err_code: %d", ul_ret);
        return ul_ret;
    }
    en_switch = (oal_switch_enum_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ENABLE_ARP_OFFLOAD, OAL_SIZEOF(oal_switch_enum_uint8));
    *(oal_switch_enum_uint8 *)(st_write_msg.auc_value) = en_switch;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_switch_enum_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_CFG, "{wal_hipriv_arp_offload_enable::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_show_arpoffload_info
 ��������  : ��ʾDevice���¼��IP��ַ
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��10��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_hipriv_show_arpoffload_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_int8                         ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_uint8                        uc_show_ip_addr;
    oal_uint8                        uc_show_arpoffload_info;
    mac_cfg_arpoffload_info_stru     *pst_arpoffload_info;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
         OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_arpoffload_info::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
         return ul_ret;
    }

    uc_show_ip_addr = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_show_arpoffload_info::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    uc_show_arpoffload_info = (oal_uint8)oal_atoi(ac_name);
    pc_param = pc_param + ul_off_set;

    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SHOW_ARPOFFLOAD_INFO, OAL_SIZEOF(mac_cfg_arpoffload_info_stru));

    /* ��������������� */
    pst_arpoffload_info = (mac_cfg_arpoffload_info_stru *)(st_write_msg.auc_value);
    pst_arpoffload_info->uc_show_ip_addr            = uc_show_ip_addr;
    pst_arpoffload_info->uc_show_arpoffload_info    = uc_show_arpoffload_info;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_cfg_arpoffload_info_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_PWR, "{wal_hipriv_show_arpoffload_info::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }
    return OAL_SUCC;
}
#endif

#ifdef _PRE_WLAN_FEATURE_ROAM
/*****************************************************************************
 �� �� ��  : wal_hipriv_roam_enable
 ��������  : �������/�ر����ι���
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��11��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_roam_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                 ul_ret;
    oal_int32                  l_ret;
    oal_uint32                 ul_off_set;
    oal_bool_enum_uint8        en_enable;
    oal_int8                   ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    wal_msg_write_stru         st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "roam enable type return err_code [%d]", ul_ret);
        return ul_ret;
    }
    en_enable = (oal_bool_enum_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ROAM_ENABLE, OAL_SIZEOF(oal_uint32));
    *((oal_bool_enum_uint8 *)(st_write_msg.auc_value)) = en_enable;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_bool_enum_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_roam_enable::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_hipriv_roam_org
 ��������  : ��������Ƶ��
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��11��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_roam_org(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                 ul_ret;
    oal_int32                  l_ret;
    oal_uint32                 ul_off_set;
    oal_uint8                  uc_org;
    oal_int8                   ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    wal_msg_write_stru         st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "roam org type return err_code[%d]", ul_ret);
        return ul_ret;
    }
    uc_org = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ROAM_ORG, OAL_SIZEOF(oal_uint32));
    *((oal_uint8 *)(st_write_msg.auc_value)) = uc_org;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_bool_enum_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{wal_hipriv_roam_org::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_hipriv_roam_band
 ��������  : ��������Ƶ��
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��11��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_roam_band(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_uint32                 ul_ret;
    oal_int32                  l_ret;
    oal_uint32                 ul_off_set;
    oal_uint8                  uc_band;
    oal_int8                   ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    wal_msg_write_stru         st_write_msg;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "roam band type return err_code[%d]", ul_ret);
        return ul_ret;
    }
    uc_band = (oal_uint8)oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ROAM_BAND, OAL_SIZEOF(oal_uint32));
    *((oal_uint8 *)(st_write_msg.auc_value)) = uc_band;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_bool_enum_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{wal_hipriv_roam_band::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_hipriv_roam_start
 ��������  : �����ʼ����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��11��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_roam_start(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_int32                  l_ret;
    oal_uint32                 ul_ret;
    oal_bool_enum_uint8        en_enable;
    wal_msg_write_stru         st_write_msg;

    oal_uint32                 ul_off_set;
    oal_uint8                  uc_param;
    oal_int8                   ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_ERR_CODE_PTR_NULL == ul_ret)
    {
        /* Ĭ��ɨ��+���� */
        en_enable = OAL_FALSE;
    }
    else if (OAL_SUCC == ul_ret)
    {
        /* ָ������ʱ���Ƿ����ɨ����� */
        uc_param  = (oal_uint8)oal_atoi(ac_name);
        en_enable = (uc_param > 0 ) ? OAL_TRUE : OAL_FALSE;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{wal_hipriv_roam_start::roam_start cfg_cmd error[%d]}", ul_ret);
        return ul_ret;
    }
    OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{wal_hipriv_roam_start::roam_start no scan[%d],1:no_scan}", en_enable);
    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ROAM_START, OAL_SIZEOF(oal_uint32));
    *((oal_bool_enum_uint8 *)(st_write_msg.auc_value)) = en_enable;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_bool_enum_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{wal_hipriv_roam_enable::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_roam_info
 ��������  : �����ʼ����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��11��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 wal_hipriv_roam_info(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    oal_int32                  l_ret;
    oal_bool_enum_uint8        en_enable;
    wal_msg_write_stru         st_write_msg;

    en_enable = 1;

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_ROAM_INFO, OAL_SIZEOF(oal_uint32));
    *((oal_bool_enum_uint8 *)(st_write_msg.auc_value)) = en_enable;

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_bool_enum_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ROAM, "{wal_hipriv_roam_enable::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
#endif //_PRE_WLAN_FEATURE_ROAM

#ifdef _PRE_WLAN_FEATURE_HILINK_DEBUG
/*****************************************************************************
 �� �� ��  : wal_hipriv_fbt_set_mode
 ��������  : ���ÿ����л�fbtģʽ
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_fbt_set_mode(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_set_mode::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_set_mode::the value is invalid[%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FBT_SET_MODE, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_set_mode::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
/*****************************************************************************
 �� �� ��  : wal_hipriv_fbt_scan_list_clear
 ��������  : ���ɨ���б�
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��16��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_fbt_scan_list_clear(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;


    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FBT_SCAN_LIST_CLEAR, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_monitor_list_clear::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_hipriv_fbt_scan_specified_sta
 ��������  : ����ָ���û�
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��17��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_fbt_scan_specified_sta(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_uint32                      ul_off_set;
    oal_int8                        ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                      ul_ret;
    oal_int32                       l_ret;
    mac_fbt_scan_sta_addr_stru    *pst_specified_sta_param;
    oal_uint8                       auc_mac_addr[WLAN_MAC_ADDR_LEN];


    /* ��ȡmac��ַ */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_HILINK, "{wal_hipriv_fbt_monitor_specified_sta::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }
    oal_strtoaddr(ac_name, auc_mac_addr);
    /***************************************************************************
                             ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FBT_SCAN_SPECIFIED_STA, OAL_SIZEOF(mac_fbt_scan_sta_addr_stru));

    /* ��������������� */
    pst_specified_sta_param = (mac_fbt_scan_sta_addr_stru *)(st_write_msg.auc_value);
    oal_set_mac_addr(pst_specified_sta_param->auc_mac_addr, auc_mac_addr);

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(mac_fbt_scan_sta_addr_stru),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_monitor_specified_sta::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wal_hipriv_fbt_start_scan
 ��������  : ��������
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��17��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_fbt_start_scan(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;


    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FBT_START_SCAN, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_monitor_list_clear::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}
/*****************************************************************************
 �� �� ��  : wal_hipriv_fbt_print_scan_list
 ��������  : ��ӡ�����б�
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��17��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_fbt_print_scan_list(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;


    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FBT_PRINT_SCAN_LIST, OAL_SIZEOF(oal_int32));

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_print_monitor_list::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }
    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_fbt_scan_enable
 ��������  : ���ÿ����л�����ģʽ����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_fbt_scan_enable(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_enable::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    if (0 == (oal_strcmp("0", ac_name)))
    {
        l_tmp = 0;
    }
    else if (0 == (oal_strcmp("1", ac_name)))
    {
        l_tmp = 1;
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_enable::the value is invalid[%d]!}\r\n", ac_name);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FBT_SCAN_ENABLE, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_enable::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : wal_hipriv_fbt_scan_interval
 ��������  : ���ÿ����л�����ʱ��
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_fbt_scan_interval(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;
    oal_int32                   l_idx = 0;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_interval::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��������Ϸ��Լ�� */
    while ('\0' != ac_name[l_idx])
    {
        if (isdigit(ac_name[l_idx]))
        {
            l_idx++;
            continue;
        }
        else
        {
            l_idx++;
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_interval::input illegal!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    l_tmp =oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FBT_SCAN_INTERVAL, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_interval::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_fbt_scan_channel
 ��������  : ���ÿ����л������ŵ�
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_fbt_scan_channel(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;
    oal_int32                   l_idx = 0;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_channel::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��������Ϸ��Լ�� */
    while ('\0' != ac_name[l_idx])
    {
        if (isdigit(ac_name[l_idx]))
        {
            l_idx++;
            continue;
        }
        else
        {
            l_idx++;
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_channel::input illegal!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    l_tmp =oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FBT_SCAN_CHANNEL, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_channel::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wal_hipriv_fbt_scan_report_period
 ��������  : ���ÿ����л������ϱ�����
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : w00355005
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_fbt_scan_report_period(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_tmp;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_name[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                   l_ret;
    oal_uint32                  ul_ret;
    oal_int32                   l_idx = 0;

    ul_ret = wal_get_cmd_one_arg(pc_param, ac_name, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_report_period::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��������Ϸ��Լ�� */
    while ('\0' != ac_name[l_idx])
    {
        if (isdigit(ac_name[l_idx]))
        {
            l_idx++;
            continue;
        }
        else
        {
            l_idx++;
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_report_period::input illegal!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    l_tmp =oal_atoi(ac_name);

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_FBT_SCAN_REPORT_PERIOD, OAL_SIZEOF(oal_int32));
    *((oal_int32 *)(st_write_msg.auc_value)) = l_tmp;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_int32),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_fbt_scan_report_period::return err code[%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;

}

#endif

#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
/*****************************************************************************
 �� �� ��  : wal_hipriv_chip_check
 ��������  : оƬ�Լ쿪��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : f00290085
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_chip_check(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru          st_write_msg;
    oal_int32                   l_ret;
    oal_uint32                  ul_off_set;
    oal_int8                    ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_uint32                  ul_ret;
    oal_int32                   l_idx = 0;
    oal_switch_enum_uint8       en_chip_check_flag;

    /* ��ȡоƬ�Լ쿪�ز��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_chip_check::wal_get_cmd_one_arg vap name return err_code %d!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��������Ϸ��Լ�� */
    while ('\0' != ac_arg[l_idx])
    {
        if (isdigit(ac_arg[l_idx]))
        {
            l_idx++;
            continue;
        }
        else
        {
            l_idx++;
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_chip_check::input illegal!}");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    en_chip_check_flag = (oal_uint8)oal_atoi(ac_arg);

    /***************************************************************************
                                    ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_CHIP_CHECK_SWITCH, OAL_SIZEOF(oal_uint8));
    *((oal_uint8 *)(st_write_msg.auc_value)) = en_chip_check_flag;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    wal_hipriv_wait_rsp(pst_net_dev, pc_param);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_chip_check::return err code %d!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_send_cw_signal
 ��������  : ���͵����ź�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��6��
    ��    ��   : l00222214
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_send_cw_signal(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru               st_write_msg;
    oal_uint32                       ul_off_set;
    oal_uint32                       ul_ret;
    oal_int32                        l_ret;
    oal_uint8                        uc_param;
    oal_int8                         ac_arg[WAL_HIPRIV_CMD_NAME_MAX_LEN];
    oal_int32                        l_idx = 0;

    /* ��ȡ����ֵ�ַ��� */
    ul_ret = wal_get_cmd_one_arg(pc_param, ac_arg, &ul_off_set);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_cw_signal::wal_get_cmd_one_arg return err_code [%d]!}\r\n", ul_ret);
        return ul_ret;
    }

    /* ��������Ϸ��Լ�� */
    while ('\0' != ac_arg[l_idx])
    {
        if (isdigit(ac_arg[l_idx]))
        {
            l_idx++;
            continue;
        }
        else
        {
            l_idx++;
            OAM_WARNING_LOG0(0, OAM_SF_ANY, "{wal_hipriv_send_cw_signal::input illegal!}\r\n");
            return OAL_ERR_CODE_INVALID_CONFIG;
        }
    }

    /* ����Ҫ����Ϊ����ֵ */
    uc_param = (oal_uint8)oal_atoi(ac_arg);

    if (uc_param > 2)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_cw_signal::input val out of range [%d]!}\r\n", uc_param);
        return OAL_ERR_CODE_INVALID_CONFIG;
    }

    /***************************************************************************
                                ���¼���wal�㴦��
    ***************************************************************************/
    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_SEND_CW_SIGNAL, OAL_SIZEOF(oal_uint8));
    *((oal_uint8 *)(st_write_msg.auc_value)) = uc_param;  /* ��������������� */

    l_ret = wal_send_cfg_event(pst_net_dev,
                               WAL_MSG_TYPE_WRITE,
                               WAL_MSG_WRITE_MSG_HDR_LENGTH + OAL_SIZEOF(oal_uint8),
                               (oal_uint8 *)&st_write_msg,
                               OAL_FALSE,
                               OAL_PTR_NULL);

    wal_hipriv_wait_rsp(pst_net_dev, pc_param);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_send_cw_signal::return err code [%d]!}\r\n", l_ret);
        return (oal_uint32)l_ret;
    }
//#endif  /* _PRE_WLAN_CHIP_TEST */
    return OAL_SUCC;
}

#endif

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : wal_hipriv_get_all_reg_value
 ��������  : wal_hipriv_get_all_reg_value
 �������  : oal_net_device_stru *pst_net_dev
             oal_int8 *pc_param
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��1��
    ��    ��   : z00285102
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  wal_hipriv_get_all_reg_value(oal_net_device_stru *pst_net_dev, oal_int8 *pc_param)
{
    wal_msg_write_stru              st_write_msg;
    oal_int32                       l_ret;
    oal_uint16                      us_len;

    /***************************************************************************
                              ���¼���wal�㴦��
    ***************************************************************************/
    oal_memcopy(st_write_msg.auc_value, pc_param, OAL_STRLEN(pc_param));

    st_write_msg.auc_value[OAL_STRLEN(pc_param)] = '\0';

    us_len = (oal_uint16)(OAL_STRLEN(pc_param) + 1);

    WAL_WRITE_MSG_HDR_INIT(&st_write_msg, WLAN_CFGID_GET_ALL_REG_VALUE, us_len);

    l_ret = wal_send_cfg_event(pst_net_dev,
                             WAL_MSG_TYPE_WRITE,
                             WAL_MSG_WRITE_MSG_HDR_LENGTH + us_len,
                             (oal_uint8 *)&st_write_msg,
                             OAL_FALSE,
                             OAL_PTR_NULL);

    if (OAL_UNLIKELY(OAL_SUCC != l_ret))
    {
      OAM_WARNING_LOG1(0, OAM_SF_ANY, "{wal_hipriv_get_all_reg_value::wal_send_cfg_event return err_code [%d]!}\r\n", l_ret);
      return (oal_uint32)l_ret;
    }

    return OAL_SUCC;
}

#endif

OAL_CONST wal_hipriv_cmd_entry_stru  g_ast_hipriv_cmd_debug[] =
{
    /***********************��������***********************/
#ifdef _PRE_WLAN_FEATURE_PM
    {"pm_info",                 wal_hipriv_pm_info},                /* ����͹���PM��Ϣ hipriv "Hisilicon0 pm_info"*/
    {"pm_enable",               wal_hipriv_pm_enable},                /* ����͹���PM��Ϣ hipriv "Hisilicon0 pm_enable 0|1"*/
    {"enable",                  wal_hipriv_wifi_enable},            /* ������ر�wifi: hipriv "Hisilicon0 enable 0|1" */
#endif
    {"destroy",                 wal_hipriv_del_vap},                /* ɾ��vap˽������Ϊ: hipriv "vap0 destroy" */

    {"global_log_switch",       wal_hipriv_global_log_switch},      /* ȫ����־����:  hipriv "Hisilicon0 global_log_switch 0 | 1*/
    {"log_switch",              wal_hipriv_vap_log_switch},         /* VAP�������־����: hipriv "Hisilicon0{VAPx} log_switch 0 | 1"��������������е�VAP */
    {"feature_log_switch",      wal_hipriv_feature_log_switch},     /* ���Ե�INFO������־���� hipriv "VAPX feature_name {0/1}"   */
    {"log_ratelimit",           wal_hipriv_log_ratelimit},          /* ���Ե�INFO������־���� hipriv "Hisilicon0 log_ratelimit {type} {switch} {interval} {burst}"   */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {"log_pm",                  wal_hipriv_log_lowpower},           /* log�͹���ģʽ: hipriv "Hisilicon0 log_pm 0 | 1"��log pmģʽ���� */
    {"pm_switch",               wal_hipriv_pm_switch},              /* log�͹���ģʽ: hipriv "Hisilicon0 pm_switch 0 | 1"��log pmģʽ���� */
#endif
    {"event_switch",            wal_hipriv_event_switch},           /* OAM eventģ��Ŀ��ص�����: hipriv "Hisilicon0 event_switch 0 | 1"��������������е�VAP */
#if 0
    {"ota_switch",              wal_hipriv_ota_switch},             /* ����ĳһ�־����ota���Ϳ���: hipriv "Hisilicon0 ota_switch ota_type(oam_ota_type_enum_uint8) 0 | 1"��������������е�VAP */
#endif
#ifdef _PRE_WLAN_RF_110X_CALI_DPD
    {"start_dpd",               wal_hipriv_start_dpd},                /*Start DPD Calibration*/
#endif
#ifdef _PRE_WLAN_CHIP_TEST
    {"beacon_offload_test",     wal_hipriv_beacon_offload_test},    /* �ֶ�����host sleep״̬�������ڲ���: hipriv "Hisilicon0 host_sleep 0 | 1" */
#endif
    {"ota_beacon_on",           wal_hipriv_ota_beacon_switch},      /* �����Ƿ��ϱ�beacon֡����: hipriv "Hisilicon0 ota_beacon_switch 0 | 1"��������������е�VAP */
    {"ota_switch",              wal_hipriv_ota_rx_dscr_switch},  /* �����Ƿ��ϱ�����������֡����: hipriv "Hisilicon0 ota_rx_dscr_switch 0 | 1"��������������е�VAP */
    {"oam_output",              wal_hipriv_oam_output},             /* ����oamģ�����Ϣ��ӡλ������:hipriv "Hisilicon0 oam_output 0~4 (oam_output_type_enum_uint8)"��������������е�VAP */
    {"ampdu_start",             wal_hipriv_ampdu_start},            /* ����AMPDU��������������: hipriv "vap0  ampdu_start xx xx xx xx xx xx(mac��ַ) tidno" ���������ĳһ��VAP */
    {"auto_ba",                 wal_hipriv_auto_ba_switch},         /* �����Զ���ʼBA�Ự�Ŀ���:hipriv "vap0  auto_ba 0 | 1" ���������ĳһ��VAP */
    {"profiling",               wal_hipriv_profiling_switch},       /* �������ܲ��ԵĿ���:hipriv "vap0  profiling 0 | 1" ���������ĳһ��VAP */
    {"addba_req",               wal_hipriv_addba_req},              /* ���ý���BA�Ự����������:hipriv "vap0 addba_req xx xx xx xx xx xx(mac��ַ) tidno ba_policy buffsize timeout" ���������ĳһ��VAP */
    {"delba_req",               wal_hipriv_delba_req},              /* ����ɾ��BA�Ự����������: hipriv "vap0 delba_req xx xx xx xx xx xx(mac��ַ) tidno direction" ���������ĳһ��VAP */
#ifdef _PRE_WLAN_FEATURE_WMMAC
    {"addts_req",               wal_hipriv_addts_req},              /* ���ý���TS��������ADDTS REQ����������:hipriv "vap0 addts_req tid direction apsd up nominal_msdu_size max_msdu_size
                                                                       minimum_data_rate mean_data_rate peak_data_rate minimum_phy_rate surplus_bandwidth_allowance" ���������ĳһ��VAP */
    {"delts",                   wal_hipriv_delts},                  /* ����ɾ��TS��������DELTS����������: hipriv "vap0 tidno" ���������ĳһ��VAP */
    {"reassoc_req",             wal_hipriv_reassoc_req},            /*  �����ع�������֡: hipriv "vap0 reassoc_req"*/
    {"wmmac_switch",            wal_hipriv_wmmac_switch},           /* ����WMMAC���أ���������: hipriv "vap0 wmmac 1/0" ����Device */
#endif
    {"meminfo",                 wal_hipriv_mem_info},               /* ��ӡ�ڴ����Ϣ: hipriv "Hisilicon0 meminfo poolid" */
    {"memleak",                 wal_hipriv_mem_leak},               /* ��ӡ�ڴ����Ϣ: hipriv "Hisilicon0 memleak poolid" */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {"devicememleak",           wal_hipriv_device_mem_leak},         /* ��ӡ�ڴ����Ϣ: hipriv "Hisilicon0 devicememleak poolid" */
    {"memoryinfo",              wal_hipriv_memory_info},             /* ��ӡ�ڴ����Ϣ: hipriv "Hisilicon0 memoryinfo host/device" */
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
#ifdef _PRE_WLAN_CHIP_TEST
    {"pciregwrite",             wal_hipriv_pci_reg_write},          /* дpci�ڲ��Ĵ���ֵ: hipriv "Hisilicon0 pciregwrite <chip id>(оƬID, ��PCIE���) <addr>(�Ĵ�����ַ) <val>(д���4�ֽ�ֵ)" */
    {"pciregread",              wal_hipriv_pci_reg_read},           /* ��pci�ڲ��Ĵ���ֵ: hipriv "Hisilicon0 pciregread <chip id>(оƬID, ��PCIE���) <addr>(�Ĵ�����ַ)" */
    {"regw5115",                wal_hipriv_5115_reg_write},         /* д5115��sys ctl or pci�Ĵ���: hipriv "Hisilicon0 regw5115 <chip id>(оƬID, ��PCIE���) sys|pcie <addr>(�Ĵ�����ַ) <val>(д���4�ֽ�ֵ)" */
    {"regr5115",                wal_hipriv_5115_reg_read},          /* ��5115��sys ctl or pci�Ĵ���: hipriv "Hisilicon0 regr5115 <chip id>(оƬID, ��PCIE���) sys|pcie <addr>(�Ĵ�����ַ) */
#endif /* #ifdef _PRE_WLAN_CHIP_TEST */
#ifdef _PRE_WLAN_FEATURE_DFR
#ifdef _PRE_DEBUG_MODE
    {"dfr_enable",              wal_hipriv_dfr_enable},             /* ʹ��dfr���� hipriv "Hisilicon0 dfr_enable 0|1" */
	{"loss_tx_comp",            wal_hipriv_trig_loss_tx_comp},      /* ������ʧ��������ж�,1��ʾ������ʧ��������ж������� hipriv "Hisilicon0 loss_tx_comp 1" */
    {"pcie_reset",              wal_hipriv_trig_pcie_reset},        /* ����pcie�쳣�ж� pcie reset: hipriv "Hisilicon0 pcie_reset" */
#endif
#endif
    {"max_user_num",            wal_hipriv_max_user_num_each_device},  /* ���ø��豸�����û�����: hipriv "Hisilicon0|1 max_user_num num"��0<=num<=32 */
#endif
    {"dbb_scaling_amend",       wal_hipriv_dbb_scaling_amend}, /*����dbb scalingֵ: hipriv "wlan0 dbb_scaling_amend <param name> <value>" */

    {"beacon_chain_switch",     wal_hipriv_beacon_chain_switch},    /* ����beacon֡���Ͳ�����������: hipriv "vap0 beacon_chain_switch 0/1" Ŀǰ��ȡ���ǵ�ͨ��ģʽ(ʹ��ͨ��0)��0��ʾ�ر�˫·�������ͣ�1��ʾ���������������ĳһ��VAP */
#if 0
    {"tdls_prohi",              wal_hipriv_tdls_prohibited},                       /* ����tdls prohibited������������: hipriv "vap0  tdls_prohi 0/1" 0��ʾ�����ã�1��ʾ���� */
    {"tdls_chaswi_prohi",       wal_hipriv_tdls_channel_switch_prohibited},        /* ����tdls channel switch prohibited������������: hipriv "vap0 tdls_chaswi_prohi 0/1" 0��ʾ�����ã�1��ʾ���� */
#endif
    {"2040_ch_swt_prohi",       wal_hipriv_2040_channel_switch_prohibited},        /* ����20/40�����Ƿ��ֹ�ŵ��л�: hipriv "vap0 2040_ch_swt_prohi 0|1" 0��ʾ����ֹ��1��ʾ���� */
    {"2040_intolerant",         wal_hipriv_set_FortyMHzIntolerant},                /* ����40MHz������λ: hipriv "vap0 2040_intolerant 0|1" 0��ʾ����������40MHz��1��ʾ��������40MHz */

    {"set_ucast_data", wal_hipriv_set_ucast_data_dscr_param},    /* ��ӡ��������Ϣ: hipriv "vap0 set_ucast_data <param name> <value>" */
    {"set_bcast_data", wal_hipriv_set_bcast_data_dscr_param},    /* ��ӡ��������Ϣ: hipriv "vap0 set_bcast_data <param name> <value>" */
    {"set_ucast_mgmt", wal_hipriv_set_ucast_mgmt_dscr_param},    /* ��ӡ��������Ϣ: hipriv "vap0 set_ucast_mgmt <param name> <value>" */
    {"set_mbcast_mgmt",wal_hipriv_set_mbcast_mgmt_dscr_param},   /* ��ӡ��������Ϣ: hipriv "vap0 set_mbcast_mgmt <param name> <value>" */
#ifdef _PRE_WLAN_FEATURE_WEB_CFG_FIXED_RATE
    {"set_mode_ucast_data",     wal_hipriv_set_mode_ucast_data_dscr_param},         /* ����ָ��ģʽ��������֡������: hipriv "vap0 set_mode_ucast_data <protocol_mode> <param name> <value>" */
#endif
    {"nss",                     wal_hipriv_set_nss  },               /* ����HTģʽ�µĿռ�������:   hipriv "vap0 nss   <value>" */
    {"txch",                    wal_hipriv_set_rfch },               /* ���÷���ͨ��:               hipriv "vap0 rfch  <value>" */
    {"al_tx",                   wal_hipriv_always_tx},               /* ���ó���ģʽ:               hipriv "vap0 al_tx <value: 0/1/2> <ack policy: 0/1> <payload> <len>" value:0:�رգ�1:RF��2:�ۺϡ�ack policy: 0:normal��1:no ack��*/
    {"get_thruput",             wal_hipriv_get_thruput},             /* ��ȡоƬ������������        hipriv "vap0 get_thruput >" */
#ifdef _PRE_DEBUG_MODE
    {"rxch",                    wal_hipriv_set_rxch},                /* ���ó��ս���ͨ��            hipriv "vap0 rxch <value:0001/0010/0011>" */
    {"dync_txpower",            wal_hipriv_dync_txpower},            /* ���ö�̬����У׼����         hipriv "Hisilicon0 dync_txpower 0/1" 0:�ر� 1:�� */
#endif
    {"set_freq_skew",           wal_hipriv_set_freq_skew},          /* ����Ƶƫ����                 hipriv "Hisilicon0 set_freq_skew
                                                                     * <idx chn T0Int20M T0Frac20M T1Int20M T1Frac20M T0Int40M T0Frac40M T1Int40M T1Frac40M>" */
    {"adjust_ppm",              wal_hipriv_adjust_ppm},             /* ����ppm         hipriv "Hisilicon0 adjust_ppm ppm clock" */
    {"amsdu_start",             wal_hipriv_amsdu_start},            /* ��ӡ�Ĵ�����Ϣ: hipriv "vap0 amsdu_start xx xx xx xx xx xx(mac��ַ10����oal_atoi) <max num> <max size> " */
    {"list_ap",                 wal_hipriv_list_ap},                /* ��ӡSTAɨ�赽��AP�б�: hipriv "sta0 list_ap" */
    {"list_sta",                wal_hipriv_list_sta},               /* ��ӡAP������STA�б�: hipriv "sta0 list_sta" */
    {"start_scan",              wal_hipriv_start_scan},             /* ����staɨ��: hipriv "sta0 start_scan" */
    {"start_join",              wal_hipriv_start_join},             /* ����sta���벢��֤����: hipriv "sta0 start_join 1" 1��ʾɨ�赽��AP��deviceд�����±��*/
    {"start_deauth",            wal_hipriv_start_deauth},           /* ����staȥ��֤: hipriv "vap0 start_deauth" */
    {"dump_timer",              wal_hipriv_dump_timer},             /* ��ӡ����timer��ά����Ϣ hipriv "vap0 dump_timer" */
    {"kick_user",               wal_hipriv_kick_user},              /* ɾ��1���û� hipriv "vap0 kick_user xx xx xx xx xx xx(mac��ַ)" */
    {"pause_tid",               wal_hipriv_pause_tid},              /* ��ָͣ���û���ָ��tid hipriv "vap0 pause_tid xx xx xx xx xx xx(mac��ַ) tid_num 0\1" */
    {"set_user_vip",            wal_hipriv_set_user_vip},           /* ����ĳ���û�ΪVIP���߷�VIP��sh hipriv.sh "vap0 set_user_vip xx xx xx xx xx xx(mac��ַ) 0\1" */
    {"set_vap_host",            wal_hipriv_set_vap_host},           /* ����ĳ��vapΪhost����guest vap: sh hipriv.sh "vap0 st_vap_host 0\1" */
    {"ampdu_tx_on",             wal_hipriv_ampdu_tx_on},            /* ������ر�ampdu���͹��� hipriv "vap0 ampdu_tx_on 0\1" */
    {"amsdu_tx_on",             wal_hipriv_amsdu_tx_on},            /* ������ر�ampdu���͹��� hipriv "vap0 amsdu_tx_on 0\1" */
    {"send_bar",                wal_hipriv_send_bar},               /* ָ��tid����bar hipriv "vap0 send_bar A6C758662817(mac��ַ) tid_num" */

    {"packet_xmit",             wal_hipriv_packet_xmit},            /* ��Ŀ��STA/AP��������֡: hipriv "vap0 packet_xmit (tid_no) (���ĸ���) (���ĳ���) (RA MAC)" */
    {"dump_ba_bitmap",          wal_hipriv_dump_ba_bitmap},         /* ��ӡ����ba��bitmap hipriv "vap0 dump_ba_bitmap (tid_no) (RA)" */
    {"wifi_stat_info",          wal_hipriv_show_stat_info},         /* ��ȡ����ά��ͳ����Ϣ: hipriv "Hisilicon0 wifi_stat_info" */
    {"vap_pkt_stat",            wal_hipriv_show_vap_pkt_stat},      /* ��ȡĳһ��vap�µ��շ���ͳ����Ϣ: sh hipriv.sh "vap_name vap_pkt_stat" */
    {"clear_stat_info",         wal_hipriv_clear_stat_info},        /* ��������ά��ͳ����Ϣ: hipriv "Hisilicon0 clear_stat_info" */
    {"usr_stat_info",           wal_hipriv_user_stat_info},         /* �ϱ�ĳ��user�µ�ά��ͳ����Ϣ: sh hipriv.sh "Hisilicon0 usr_stat_info usr_id" */
    {"timer_start",             wal_hipriv_timer_start},            /* ����5115Ӳ����ʱ��: hipriv "Hisilicon0 timer_start 0/1" */
    {"show_profiling",          wal_hipriv_show_profiling},         /* ����5115Ӳ����ʱ��: hipriv "Hisilicon0 show_profiling 0/1/2 (0��rx 1��tx 2��chipstart)" */
    {"ampdu_amsdu",             wal_hipriv_ampdu_amsdu_switch},     /* ����amsdu ampdu���ϾۺϹ��ܵĿ���:hipriv "vap0  ampdu_amsdu 0 | 1" ���������ĳһ��VAP */
   // {"reset_hw",                wal_hipriv_reset_device},           /* ��λӲ��phy&mac: hipriv "Hisilicon0 reset_hw 0|1|2|3(all|phy|mac|debug) 0|1(reset phy reg) 0|1(reset mac reg) */
    {"reset_hw",                wal_hipriv_reset_device},           /* ��λӲ��phy&mac: hipriv "Hisilicon0 reset_hw 0|1|2|3|4|5|6|8|9|10|11
                                                                                                                    (all|phy|mac|debug|mac_tsf|mac_cripto|mac_non_cripto|phy_AGC|phy_HT_optional|phy_VHT_optional|phy_dadar )
                                                                                                                    0|1(reset phy reg) 0|1(reset mac reg) */
    {"reset_operate",           wal_hipriv_reset_operate},          /* ��λӲ��phy&mac: hipriv "Hisilicon0 reset_hw 0|1|2|3(all|phy|mac|debug) 0|1(reset phy reg) 0|1(reset mac reg) */
    {"dump_rx_dscr",            wal_hipriv_dump_rx_dscr},           /* dump�����������������У�hipriv "Hisilicon0 dump_rx_dscr 0|1", 0:�����ȼ����� 1:��ͨ���ȼ�����  */
    {"dump_tx_dscr",            wal_hipriv_dump_tx_dscr},           /* dump�����������������У�hipriv "Hisilicon0 dump_tx_dscr value", valueȡֵ0~3����AC���Ͷ��У�4�������֡ */
    {"dump_memory",             wal_hipriv_dump_memory},            /* dump�ڴ棬 hipriv "Hisilicon0 dump_memory 0xabcd len" */
    {"show_tx_dscr_addr",       wal_hipriv_show_tx_dscr_addr},      /* ��ӡ�ڴ�������з�����������ַ hipriv "Hisilicon0 show_tx_dscr_addr" */
    {"list_channel",            wal_hipriv_list_channel},           /* ֧���ŵ��б� hipriv "Hisilicon0 list_channel" */
    {"set_regdomain_pwr_p",     wal_hipriv_set_regdomain_pwr_priv}, /* ���ù���������͹���(����ͻ�ƹ����������)��hipriv "Hisilicon0 set_regdomain_pwr_priv 20",��λdBm */
    {"event_queue",             wal_hipriv_event_queue_info},       /* ��ӡ�¼�������Ϣ������ӡ��ÿһ���ǿ��¼��������¼��ĸ������Լ�ÿһ���¼�ͷ��Ϣ, hipriv "Hisilicon0 event_queue" */
    {"frag_threshold",          wal_hipriv_frag_threshold},         /* ���÷�Ƭ���޵���������: hipriv "vap0 frag_threshold (len)" ���������ĳһ��VAP */
    {"wmm_switch",              wal_hipriv_wmm_switch},             /* ��̬�������߹ر�wmm hipriv "vap0 wmm_switch 0|1"(0��ʹ�ܣ�1ʹ��)  */
    {"hide_ssid",               wal_hipriv_hide_ssid},              /*  ����ssid���ܿ������߹ر� wmm hipriv "Hisilicon0 hide_ssid 0|1"(0��ʹ�ܣ�1ʹ��)  */
    {"ether_switch",            wal_hipriv_set_ether_switch},       /* ������̫��֡�ϱ��Ŀ��أ�sh hipriv.sh "vap0 ether_switch user_macaddr oam_ota_frame_direction_type_enum(֡����) 0|1(����)" */
    {"80211_uc_switch",         wal_hipriv_set_80211_ucast_switch}, /* ����80211����֡�ϱ��Ŀ��أ�sh hipriv.sh "vap0 80211_uc_switch user_macaddr 0|1(֡����tx|rx) 0|1(֡����:����֡|����֡) 0|1(֡���ݿ���) 0|1(CB����) 0|1(����������)" */
    {"80211_mc_switch",         wal_hipriv_set_80211_mcast_switch}, /* ����80211�鲥\�㲥֡�ϱ��Ŀ��أ�sh hipriv.sh "Hisilicon0 80211_mc_switch 0|1(֡����tx|rx) 0|1(֡����:����֡|����֡) 0|1(֡���ݿ���) 0|1(CB����) 0|1(����������)" */
    {"probe_switch",            wal_hipriv_set_probe_switch},       /* ����probe req��rsp�ϱ��Ŀ��أ�sh hipriv.sh "Hisilicon0 probe_switch 0|1(֡����tx|rx) 0|1(֡���ݿ���) 0|1(CB����) 0|1(����������)" */
    {"rssi_switch",             wal_hipriv_set_rssi_switch},        /* ���ô�ӡ���ձ���rssi��Ϣ�Ŀ��أ�sh hipriv.sh "Hisilicon0 rssi_switch 0|1(��|�ر�) N(���N��֡��ӡ)" */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    {"report_vap_info",         wal_hipriv_report_vap_info},        /* ���ݱ��λ�ϱ�vap�Ķ�Ӧ��Ϣ sh hipriv.sh "wlan0 report_vap_info 1" */
#endif
    {"mpdu_num",                wal_hipriv_get_mpdu_num},           /* ��ȡdevice�º�ÿһ��tid�µ�ǰmpdu������sh hipriv.sh "vap_name mpdu_num user_macaddr" */
    {"set_all_ota",             wal_hipriv_set_all_ota},            /* ��������ota�ϱ������Ϊ1������������֡��cb���������������Ϊ0��ʲô��������sh hipriv.sh "Hisilicon0 set_all_ota 0|1" */
    {"80211_uc_all",            wal_hipriv_set_all_80211_ucast},    /* ���������û��ĵ������أ�sh hipriv.sh "Hisilicon0 80211_uc_all 0|1(֡����tx|rx) 0|1(֡����:����֡|����֡) 0|1(֡���ݿ���) 0|1(CB����) 0|1(����������)" */
    {"ether_all",               wal_hipriv_set_all_ether_switch},   /* ���������û�����̫�����أ�sh hipriv.sh "Hisilicon0 ether_all 0|1(֡����tx|rx) 0|1(����)" */
    {"dhcp_arp_switch",         wal_hipriv_set_dhcp_arp_switch},    /* ���÷��͹㲥arp��dhcp���أ�sh hipriv.sh "Hisilicon0 dhcp_arp_switch 0|1(����)" */
#ifdef _PRE_DEBUG_MODE_USER_TRACK
    {"thrput_stat",             wal_hipriv_report_thrput_stat},     /* �ϱ�����ֹͣ�ϱ���Ӧuserʵʱ����ͳ����Ϣ: sh hipriv.sh "vap_name thrput_stat  XX:XX:XX:XX:XX;XX 0|1" */
#endif
#ifdef _PRE_WLAN_DFT_STAT
    {"clear_vap_stat_info",     wal_hipriv_clear_vap_stat_info},    /* ����ָ��VAP��ͳ����Ϣ: hipriv "vap_name clear_vap_stat_info" */
#endif
#ifdef _PRE_WLAN_FEATURE_TXOPPS
    {"txopps_hw_en",            wal_hipriv_set_txop_ps_machw},      /* ����mac txop psʹ�ܼĴ�����sh hipriv.sh "stavap_name txopps_hw_en 0|1(txop_ps_en) 0|1(condition1) 0|1(condition2)" */
#endif
#ifdef _PRE_WLAN_FEATURE_UAPSD
    {"uapsd_debug",             wal_hipriv_uapsd_debug},            /* uapsdά����Ϣ��sh hipriv "vap0 uapsd_debug 0|1|2(���û�|all user|���ͳ�Ƽ�����) xx:xx:xx:xx:xx:xx(mac��ַ)" */
#endif
#ifdef _PRE_WLAN_DFT_STAT
    {"phy_stat_en",             wal_hipriv_set_phy_stat_en},        /* ����phyͳ��ʹ�ܽڵ��ţ�һ�ο�������4����������Χ1~16��sh hipriv.sh "Hisilicon0 phy_stat_en idx1 idx2 idx3 idx4" */

    {"dbb_env_param",           wal_hipriv_dbb_env_param},          /* �ϱ�����ֹͣ�ϱ��տڻ����������Ϣ: sh hipriv.sh "Hisilicon0 dbb_env_param 0|1" */
    {"usr_queue_stat",          wal_hipriv_usr_queue_stat},         /* �ϱ����������û�����ͳ����Ϣ: sh hipriv.sh "vap_name usr_queue_stat XX:XX:XX:XX:XX:XX 0|1" */
    {"vap_stat",                wal_hipriv_report_vap_stat},        /* �ϱ�����ֹͣ�ϱ�vap����ͳ����Ϣ: sh hipriv.sh "vap_name vap _stat  0|1" */
    {"reprt_all_stat",          wal_hipriv_report_all_stat},        /* �ϱ�������������ά��ͳ����Ϣ: sh hipriv.sh "Hisilicon0 reprt_all_stat type(phy/machw/mgmt/irq/all)  0|1" */
#endif
#ifdef _PRE_DEBUG_MODE
    {"ampdu_stat",             wal_hipriv_report_ampdu_stat},      /* �ϱ���������ampduά��ͳ����Ϣ: sh hipriv.sh "vap_name ampdu_stat XX:XX:XX:XX:XX:XX tid_no 0|1" */
#endif

    {"ampdu_aggr_num",          wal_hipriv_set_ampdu_aggr_num},     /* ����AMPDU�ۺϸ���: sh hipriv.sh "Hisilicon0 ampdu_aggr_num aggr_num_switch aggr_num" ,aggr_num_switch��0ʱ��aggr_num��Ч */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    {"freq_adjust",             wal_hipriv_freq_adjust},            /* Ƶƫ������������: sh hipriv.sh "Hisilicon0 freq_adjust pll_int pll_frac" ,pll_int������Ƶϵ����pll_fracС����Ƶϵ�� */
#endif

    {"set_stbc_cap",            wal_hipriv_set_stbc_cap},           /* ����STBC���� */
    {"set_ldpc_cap",            wal_hipriv_set_ldpc_cap},           /* ����LDPC���� */
#ifdef _PRE_WLAN_FEATURE_STA_PM
    {"set_psm_para",            wal_hipriv_sta_psm_param},          /* sh hipriv.sh 'wlan0 set_psm_para 100 40 */
    {"set_sta_pm_on",           wal_hipriv_sta_pm_on},            /* sh hipriv.sh 'wlan0 set_sta_pm_on xx xx xx xx */
#endif

#ifdef _PRE_WLAN_CHIP_TEST
    {"lpm_chip_state",          wal_hipriv_lpm_chip_state},         /* ˯�߻���оƬ, hipriv "Hisilicon0 lpm_chip_state 0|1|2(0:soft sleep��1:gpio sleep,2:work)" */
    {"lpm_soc_mode",            wal_hipriv_lpm_soc_mode},           /* ˯�߻���оƬ, hipriv "Hisilicon0 lpm_soc_mode 0|1|2|3|4(����gating|PCIE RD BY PASS|mem precharge|PCIE L0-S|PCIE L1-0) 0|1(disable|enable)" */
    {"lpm_psm_param",           wal_hipriv_lpm_psm_param},          /* psm���ܼĴ�������, hipriv "Hisilicon0 lpm_psm_param 0|1|2(ps off|ps on|debug) 0|1(DTIM|listen intval) xxx(listen intervalֵ) xxx(TBTT offset)"*/
    {"lpm_smps_mode",           wal_hipriv_lpm_smps_mode},          /* smps����ģʽ����, hipriv "Hisilicon0 lpm_smps_mode 0|1|2(off|static|dynamic)"*/
    {"lpm_smps_stub",           wal_hipriv_lpm_smps_stub},          /* smps ap������׮, hipriv "vap0 lpm_smps_stub 0|1|2(off|����|˫��) 0|1(�Ƿ�RTS)"*/
    {"lpm_txopps_set",          wal_hipriv_lpm_txopps_set},         /* txop ps����ģʽ����, hipriv "Hisilicon0 lpm_txopps_set 0|1(off|on|debug) 0|1(contion1 off|on) 0|1(condition2 off|on)"*/
    {"lpm_txopps_tx_stub",      wal_hipriv_lpm_txopps_tx_stub},     /* txop ps�������Դ�׮����, hipriv "vap0 lpm_txopps_tx_stub 0|1|2(off|address|partial AID) xxx(�ڼ�������׮)"*/
    {"lpm_tx_data",             wal_hipriv_lpm_tx_data},            /* ���Է���, hipriv "vap0 lpm_tx_data xxx(����) xxx(����) xx:xx:xx:xx:xx:xx(Ŀ��mac) xxx(AC����)"*/
    {"lpm_tx_probe_req",        wal_hipriv_lpm_tx_probe_request},   /* ���Է���, hipriv "vap0 lpm_tx_probe_req 0|1(����|����) xx:xx:xx:xx:xx:xx(����ģʽ��BSSID)"*/
    {"remove_lut",              wal_hipriv_remove_user_lut},        /* ɾ���ָ��û�lut��, hipriv "vap0 remove_lut xx:xx:xx:xx:xx:xx(mac��ַ 16����) 0|1(�ָ�/ɾ��)" */
    {"send_frame",              wal_hipriv_send_frame},               /* ָ��tid����bar hipriv "vap0 send_frame (type) (num) (Ŀ��mac)" */
    {"set_rx_pn",               wal_hipriv_set_rx_pn},               /* ����RX_PN_LUT_CONFIG�Ĵ��� */
    {"set_sft_retry",           wal_hipriv_set_soft_retry},           /* ����software_retry ������ hipriv "Hisilicon0 set_sft_retry 0|1(0��ʹ�ܣ�1ʹ��)"  */
    {"open_addr4",              wal_hipriv_open_addr4},             /* ����macͷ����4��ַ hipriv "Hisilicon0 open_addr4 0|1(0��ʹ�ܣ�1ʹ��)  */
    {"open_wmm_test",           wal_hipriv_open_wmm_test},         /* ����оƬ��֤���� hipriv "Hisilicon0 open_wmm_test 0|1|2|3  ()  */
    {"chip_test",               wal_hipriv_chip_test_open},         /* ����оƬ��֤���� hipriv "Hisilicon0 chip_test 0|1(0��ʹ�ܣ�1ʹ��)  */
    {"coex_ctrl",               wal_hipriv_set_coex},               /* ���ù�����ƿ��� hipriv "Hisilicon0 coex_ctrl xxx(mac ctrlֵ) xxx(rf ctrlֵ))  */
    {"dfx_en",                  wal_hipriv_set_dfx},                /* ����DFX���Կ��� sh hipriv.sh "Hisilicon0 dfx_en 0|1  */
    {"clear_all_stat",          wal_hipriv_clear_all_stat},         /* ����жϺ͹���֡ͳ����Ϣ hipriv "Hisilicon0 clear_all_stat" */

#if (_PRE_WLAN_FEATURE_PMF != _PRE_PMF_NOT_SUPPORT)
    {"enable_pmf",              wal_hipriv_enable_pmf},     /* ����chip test��ǿ��ʹ��pmf���� (���ڹ���֮��)��sh hipriv.sh "vap0 enable_pmf 0|1|2(0��ʹ�ܣ�1 enable, 2ǿ��)  */
#endif
    {"send_action",             wal_hipriv_test_send_action},     /* ����action֡�ӿ� sh hipriv.sh "vap0 send_action XX(category) xx:xx:xx:xx:xx:xx(Ŀ�ĵ�ַ 16����) " */
    {"send_pspoll",             wal_hipriv_send_pspoll},            /* sta��ps-poll��ap��sh hipriv "vap0 send_pspoll" */
    {"send_nulldata",           wal_hipriv_send_nulldata},          /* sta��null data��ap��֪ͨ����״̬��sh hipriv "vap0 send_nulldata 0|1(�Ƿ�������) 0|1(�Ƿ�qosnull) tid_no" */
#endif /* #ifdef _PRE_WLAN_CHIP_TEST */
    {"set_default_key",         wal_hipriv_set_default_key},     /* ����chip test��ǿ��ʹ��pmf���� (���ڹ���֮��)��sh hipriv.sh "vap0 set_default_key x(key_index) 0|1(en_unicast) 0|1(multicast)"  */
    {"add_key",                 wal_hipriv_test_add_key},         /* chip test����add key������˽����������ӿڪ�
                          sh hipriv.sh "xxx(cipher) xx(en_pairwise) xx(key_len) xxx(key_index) xxxx:xx:xx:xx:xx:xx...(key С��32�ֽ�) xx:xx:xx:xx:xx:xx(Ŀ�ĵ�ַ)  */


#ifdef _PRE_WLAN_FEATURE_DFR
    {"dfr_start",              wal_hipriv_test_dfr_start},  /* dfr���ܴ�׮�����ӿڪ�sh hipriv.sh "vap0 dfr_start 0(dfr�ӹ���:0-device�쳣��λ )"*/
#endif //_PRE_WLAN_FEATURE_DFR
    /* �㷨��ص����� */
    {"alg_ar_log",              wal_hipriv_ar_log},                 /* autorate�㷨��־��������:*/
    {"alg_ar_test",             wal_hipriv_ar_test},                /* autorate�㷨ϵͳ�������� */
    {"alg",                     wal_hipriv_alg},                    /* alg */
    {"alg_txbf_switch",         wal_hipriv_txbf_switch},            /* ������ر�tx beamforming���� hipriv "vap0 alg_txbf_switch 0|1" */
    {"alg_txbf_log",            wal_hipriv_txbf_log},                 /* autorate�㷨��־��������:*/
    {"alg_cca_opt_log",         wal_hipriv_cca_opt_log},                /* cca�㷨��־��������:*/
#ifdef _PRE_SUPPORT_ACS
    {"acs",                     wal_hipriv_acs},
#endif

#ifdef _PRE_WLAN_PERFORM_STAT
    /* ����ͳ������ */
    {"stat_tid_thrpt",          wal_hipriv_stat_tid_thrpt},        /* ͳ��ָ��tid��������: hipriv "vap0 stat_tid_thrpt xx xx xx xx xx xx(mac��ַ) tid_num stat_period(ͳ������ms) stat_num(ͳ�ƴ���)" */
    {"stat_user_thrpt",         wal_hipriv_stat_user_thrpt},       /* ͳ��ָ��user��������: hipriv "vap0 stat_user_thrpt xx xx xx xx xx xx(mac��ַ) stat_period(ͳ������ms) stat_num(ͳ�ƴ���)" */
    {"stat_vap_thrpt",          wal_hipriv_stat_vap_thrpt},        /* ͳ��ָ��tid��������: hipriv "vap0 stat_vap_thrpt stat_period(ͳ������ms) stat_num(ͳ�ƴ���)" */
    {"stat_tid_per",            wal_hipriv_stat_tid_per},          /* ͳ��ָ��tid��per: hipriv "vap0 stat_tid_per xx xx xx xx xx xx(mac��ַ) tid_num stat_period(ͳ������ms) stat_num(ͳ�ƴ���)" */
    {"stat_tid_delay",          wal_hipriv_stat_tid_delay},        /* ͳ��ָ��tid��delay: hipriv "vap0 stat_tid_delay xx xx xx xx xx xx(mac��ַ) tid_num stat_period(ͳ������ms) stat_num(ͳ�ƴ���)" */

    /* ������ʾ���� */
    {"dspl_tid_thrpt",          wal_hipriv_display_tid_thrpt},      /* ͳ��ָ��tid��������: hipriv "vap0 dspl_tid_thrpt xx xx xx xx xx xx(mac��ַ)" */
    {"dspl_user_thrpt",         wal_hipriv_display_user_thrpt},     /* ͳ��ָ��user��������: hipriv "vap0 dspl_user_thrpt xx xx xx xx xx xx(mac��ַ)" */
    {"dspl_vap_thrpt",          wal_hipriv_display_vap_thrpt},      /* ͳ��ָ��tid��������: hipriv "vap0 dspl_vap_thrpt" */
    {"dspl_tid_per",            wal_hipriv_display_tid_per},        /* ͳ��ָ��tid��per: hipriv "vap0 dspl_tid_per xx xx xx xx xx xx(mac��ַ) tid_num" */
    {"dspl_tid_delay",          wal_hipriv_display_tid_delay},      /* ͳ��ָ��tid��delay: hipriv "vap0 dspl_tid_delay xx xx xx xx xx xx(mac��ַ) tid_num" */
#endif

#ifdef _PRE_WLAN_FEATURE_EDCA_OPT_AP
    {"set_edca_weight_sta",        wal_hipriv_set_edca_opt_weight_sta},       /* STA edca��������Ȩ�� */
    {"set_edca_switch_ap",         wal_hipriv_set_edca_opt_switch_ap},        /* �Ƿ���edca�Ż����� */
    {"set_edca_cycle_ap",          wal_hipriv_set_edca_opt_cycle_ap},         /* ����edca�������������� */
#endif

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    {"get_hipkt_stat",             wal_hipriv_get_hipkt_stat},                /* ��ȡ�����ȼ����ĵ�ͳ����� */
    {"set_flowctl_param",          wal_hipriv_set_flowctl_param},             /* ����������ز��� */
    {"get_flowctl_stat",           wal_hipriv_get_flowctl_stat},              /* ��ȡ�������״̬��Ϣ */
#endif

#ifdef _PRE_DEBUG_MODE
    /* ά������:����ĳ��ֵ��ĳ������*/
    {"debug_switch",            wal_hipriv_set_debug_switch},        /* ����ĳһ�־����debug���Ϳ���: hipriv "Hisilicon0 debug_switch debug_type debug_value"������������豸�������ʹ�� */
    {"tx_comp_cnt",             wal_hipriv_get_tx_comp_cnt},         /* ͳ�Ʒ�������ж��Ƿ�ʧ(�رվۺ�) hipriv "Hisilicon0 tx_comp_cnt 0|1", 0��ʾ����ͳ�ƴ����� 1��ʾ��ʾͳ�ƴ����������� */
    {"set_rx_filter_val",       wal_hipriv_set_rx_filter_val},       /* ���ý���֡���˸�״̬�µ�����ֵ:hipriv "Hisilicon0 set_rx_filter_val 0-Normal/1-Repeater mode status value" */
    {"get_rx_filter_val",       wal_hipriv_get_rx_filter_val},       /* ���ý���֡���˸�״̬�µ�����ֵ:hipriv "Hisilicon0 get_rx_filter_val 0-Normal/1-Repeater mode status" */
    {"set_rx_filter_en",        wal_hipriv_set_rx_filter_en},        /* ��ȡ����֡���˸�״̬�µ�����ֵ:hipriv "Hisilicon0 set_rx_filter_en 0-��/1-�ر� */
    {"get_rx_filter_en",        wal_hipriv_get_rx_filter_en},        /* ��ȡ����֡���˸�״̬�µ�����ֵ:hipriv "Hisilicon0 get_rx_filter_en */
    {"get_all_regs",            wal_hipriv_get_all_reg_value},               /* ��ȡ���мĴ�����ֵ: hipriv "Hisilicon0 get_all_regs" */
#endif

    {"set_mib",                 wal_hipriv_set_mib},                   /* ����VAP mibֵ */
    {"get_mib",                 wal_hipriv_get_mib},                   /* ��ȡVAP mibֵ */
    {"thruput_bypass",          wal_hipriv_set_thruput_bypass},        /* ����thruput bypassά��� */
    {"auto_protection",         wal_hipriv_set_auto_protection},       /* �����Զ��������� */

    /* ����ά����� */
    {"send_2040_coext",         wal_hipriv_send_2040_coext},           /* ����20/40�������֡: hipriv "Hisilicon0 send_2040_coext coext_info chan_report" */
    {"2040_coext_info",         wal_hipriv_2040_coext_info},           /* ��ӡvap������20/40���������Ϣ: hipriv "vap0 2040_coext_info" */
    {"get_version",             wal_hipriv_get_version},               /* ��ȡ����汾: hipriv "vap0 get_version" */

#ifdef _PRE_WLAN_FEATURE_DAQ
    {"data_acq",                wal_hipriv_data_acq},                  /* ��ȡ����汾: hipriv "Hisilicon0 data_acq 0/1/2/3/4 (length num depth) (channel mode data_th bit) (2) () ()" */
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    {"set_oma",                 wal_hipriv_set_oma},                   /* ����Proxy STA��oma��ַ" */
    {"proxysta_switch",         wal_hipriv_proxysta_switch},           /* proxystaģ��Ŀ��ص�����: hipriv "Hisilicon0 proxysta_switch 0 | 1"��������������е�VAP */
#endif

#ifdef _PRE_WLAN_FEATURE_OPMODE_NOTIFY
    {"set_opmode_notify",       wal_hipriv_set_opmode_notify},         /* ����VAP����ģʽ֪ͨ: hipriv "vap0 set_opmode_notify 0/1"  0-��֧��; 1-֧�� */
    {"get_user_nssbw",          wal_hipriv_get_user_nssbw},                   /* ��������û�����������: hipriv "vap0 get_user_nssbw xx xx xx xx xx xx(mac��ַ) "  ���������ĳһ��VAP */
#endif

#ifdef _PRE_WLAN_DFT_REG
    {"dump_reg",                 wal_hipriv_dump_reg},                 /* ������Ҫ��ȡ�ļĴ�����hipriv "Hisilicon0 dump_reg phy/mac/soc/abb/rf (subtype-����) (flag 0/1)"*/
    {"dump_reg_evt",             wal_hipriv_dump_reg_evt},             /* ���ô����Ĵ�����ȡ���¼����¼�������hipriv "Hisilicon0 dump_reg_evt tx/rx/tbtt/prd (tick-����)"*/
    {"dump_reg_addr",            wal_hipriv_dump_reg_addr},            /* ��ʾ�Ĵ�����ȡ��ص�����Ϣ */

    {"dump_reg_info",            wal_hipriv_dump_reg_info},            /* ��ʾ�Ĵ�����ȡ��ص�����Ϣ */
#endif

    {"set_vap_nss",              wal_hipriv_set_vap_nss},               /* ����VAP�Ŀռ�������:hipriv "vap0 set_vap_nss <value>" */

#ifdef _PRE_WLAN_FEATURE_CUSTOM_SECURITY

    {"blacklist_add",           wal_hipriv_blacklist_add},          /* 1 */
    {"blacklist_del",           wal_hipriv_blacklist_del},          /* 2 */
    {"blacklist_mode",          wal_hipriv_set_blacklist_mode},     /* 3 */
    {"blacklist_show",          wal_hipriv_blacklist_show},         /* 4 wal_config_blacklist_show */
    {"abl_on",                  wal_hipriv_set_abl_on},             /* 5 */
    {"abl_aging",               wal_hipriv_set_abl_aging},          /* 6 */
    {"abl_threshold",           wal_hipriv_set_abl_threshold},      /* 7 */
    {"abl_reset",               wal_hipriv_set_abl_reset},          /* 8 wal_config_set_autoblacklist_reset_time */
    {"isolation_mode",          wal_hipriv_set_isolation_mode},     /* 9 */
    {"isolation_type",          wal_hipriv_set_isolation_type},     /* 10 */
    {"isolation_fwd",           wal_hipriv_set_isolation_fwd},      /* 11 */
    {"isolation_clear",         wal_hipriv_set_isolation_clear},    /* 12 wal_config_set_isolation_clear */
    {"isolation_show",          wal_hipriv_set_isolation_show},     /* 13 wal_config_isolation_show */

#endif
#ifdef _PRE_WLAN_FEATURE_MCAST
    {"m2u_snoop_on",            wal_hipriv_m2u_snoop_on},           /* ������ر�snoop���ع��� hipriv "vap0 m2u_snoop_on 0\1" */
    {"m2u_add_deny_table",      wal_hipriv_m2u_add_deny_table},         /* �����鲥������� hipriv "vap0 m2u_add_deny_table 224.1.1.1" */
    {"m2u_cfg_deny_table",      wal_hipriv_m2u_cfg_deny_table},         /* �����鲥������� hipriv "vap0 m2u_cfg_deny_table 1 0" */
    {"m2u_prt_sn_table",        wal_hipriv_m2u_show_snoop_table},       /* ��ӡ�鲥�� hipriv "vap0 m2u_show_snoop_table 1" */
    {"m2u_igmp_pkt_xmit",       wal_hipriv_igmp_packet_xmit},           /* ��Ŀ��STA/AP��������֡: hipriv "vap0 m2u_igmp_pkt_xmit (tid_no) (���ĸ���) (���ĳ���) (RA MAC)" */
#endif

#ifdef _PRE_WLAN_FEATURE_PROXY_ARP
    {"proxyarp_on",            wal_hipriv_proxyarp_on},           /* ?????proxyarp???? hipriv "vap0 proxyarp_on 0\1" */
#ifdef _PRE_DEBUG_MODE
    {"proxyarp_info",          wal_hipriv_proxyarp_info},         /* ??proxyarp???? hipriv "vap0 proxyarp_info 0\1" */
#endif /* #ifdef _PRE_DEBUG_MODE */
#endif/* #ifdef _PRE_WLAN_FEATURE_PROXY_ARP */

#ifdef _PRE_WLAN_FEATURE_SMPS
#ifdef _PRE_DEBUG_MODE
    {"smps_info",              wal_hipriv_get_smps_info},         /* ??proxyarp???? hipriv "vap0 smps_info 0\1" */
#endif /* #ifdef _PRE_DEBUG_MODE */
#endif/* #ifdef _PRE_WLAN_FEATURE_SMPS */

    {"vap_classify_en",         wal_hipriv_vap_classify_en},        /* device������������ ���û���vap��ҵ������Ƿ�ʹ�� hipriv "Hisilicon0 vap_classify_en 0/1" */
    {"vap_classify_tid",        wal_hipriv_vap_classify_tid},       /* ����vap�����ȼ� hipriv "vap0 classify_tid 0~7" */

#ifdef _PRE_DEBUG_MODE
    {"scan_test",               wal_hipriv_scan_test},              /* ɨ��ģ��������� hipriv "Hisilicon0 scan_test param1 param2" param1ȡֵ'2g' '5g' 'all' 1~14, 36~196; param2ȡֵ��Ӧwlan_channel_bandwidth_enum_uint8 */
#endif
#ifdef _PRE_WLAN_PROFLING_MIPS
    {"set_mips",             wal_hipriv_set_mips},            /* ����ĳ���̵�MIPSͳ�ƿ��أ�sh hipriv.sh "Hisilicon0 set_mips wal_mips_param_enum 0|1" */
    {"show_mips",            wal_hipriv_show_mips},           /* ��ӡĳ���̵�MIPSͳ�ƽ����sh hipriv.sh "Hisilicon0 show_mips wal_mips_param_enum" */
#endif
    {"txpower",         wal_hipriv_set_txpower},                 /* ��������͹��� */
#if  (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    {"essid",           wal_ioctl_set_essid},                   /* ����AP ssid */
    {"bintval",         wal_ioctl_set_beacon_interval},         /* ����AP beacon ���� */
    {"up",              wal_hipriv_start_vap},
#endif /* (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44)) */

#ifdef _PRE_WLAN_FEATURE_11D
    {"set_rd_by_ie_switch",      wal_hipriv_set_rd_by_ie_switch},   /*�����Ƿ���ݹ���ap���¹�������Ϣ hipriv "Hisilicon0 set_rd_by_ie_switch 0/1"*/
#endif
#ifdef  _PRE_WLAN_FEATURE_P2P
#ifdef _PRE_WLAN_CHIP_TEST
    {"p2p_ps",                  wal_hipriv_set_p2p_ps},         /* ����P2P ���� sh hipriv.sh "vap0 p2p_ps noa/ops params */
#endif /* #ifdef _PRE_WLAN_CHIP_TEST */
                                                                /* sh hipriv.sh "vap0 p2p_ps ops 0/1(0��ʹ�ܣ�1ʹ��) [0~255] ����OPS ������ct_window ���� */
                                                                /* sh hipriv.sh "vap0 p2p_ps noa start_time duration interval count ����NOA ���ܲ��� */
                                                                /* sh hipriv.sh "vap0 p2p_ps statistics 0/1(0 ���ͳ�ƣ�1�鿴ͳ��) P2P �ж�ͳ�� */
    {"p2p_test",                wal_hipriv_p2p_test},
#endif  /* _PRE_WLAN_FEATURE_P2P */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    {"resume_rx_intr_fifo",     wal_hipriv_resume_rx_intr_fifo},    /* ʹ�ָܻ�rx intr fifo���Ĭ�ϲ����� hipriv "Hisilicon0 resume_rxintr_fifo 0|1" 1ʹ�� */
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    {"ampdu_mmss",              wal_hipriv_set_ampdu_mmss},         /* ����AMPDU MMSS : sh hipriv.sh "vap0 ampdu_mmss 0~7" */
#endif

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    {"arp_offload_enable",      wal_hipriv_arp_offload_enable},    /* ARP/ND�������ƺ͹㲥/�鲥���˿���:sh hipriv.sh "wlan0 arp_offload_enable  0/1(0�رգ�1��)" */
    {"show_arpoffload_info",    wal_hipriv_show_arpoffload_info},          /* ��ʾDevice���¼��IP��ַ:sh hipriv.sh "wlan0 show_ip_addr" */
#endif

#ifdef _PRE_WLAN_TCP_OPT
    {"get_tcp_ack_stream_info",                  wal_hipriv_get_tcp_ack_stream_info},         /* ��ʾTCP ACK ����ͳ��ֵ sh hipriv.sh "vap0 get_tx_ack_stream_info*/
    {"tcp_tx_ack_opt_enable",                  wal_hipriv_tcp_tx_ack_opt_enable},         /*���÷���TCP ACK�Ż�ʹ��  sh hipriv.sh "vap0 tcp_tx_ack_opt_enable 0 | 1*/
    {"tcp_rx_ack_opt_enable",                  wal_hipriv_tcp_rx_ack_opt_enable},         /* ���ý���TCP ACK�Ż�ʹ�� sh hipriv.sh "vap0 tcp_rx_ack_opt_enable 0 | 1*/
    {"tcp_tx_ack_opt_limit",                  wal_hipriv_tcp_tx_ack_limit},         /* ���÷���TCP ACK LIMIT sh hipriv.sh "vap0 tcp_tx_ack_opt_limit X*/
    {"tcp_rx_ack_opt_limit",                  wal_hipriv_tcp_rx_ack_limit},         /* ���ý���TCP ACKLIMIT  sh hipriv.sh "vap0 tcp_tx_ack_opt_limit X*/

#endif

#ifdef _PRE_WLAN_FEATURE_WAPI
#ifdef _PRE_WAPI_DEBUG
    {"wapi_info",                             wal_hipriv_show_wapi_info},   /*wapi hipriv "vap0 wal_hipriv_show_wapi_info "*/
#endif /* #ifdef _PRE_DEBUG_MODE */
#endif /* #ifdef _PRE_WLAN_FEATURE_WAPI */


#ifdef _PRE_WLAN_DFT_STAT
    {"performance_log_debug",          wal_hipriv_performance_log_switch},        /* �������ܴ�ӡ���ƿ��� sh hipriv.sh "wlan0 performance_log_debug X Y,*/
                                                                                                                                                        /*����X�Ǵ�ӡ�㣬��oal_performance_log_switch_enum���壬Y��ʹ�ܿ���,0�رգ�1�򿪡�*/                                                                                                                                                        /*X=255ʱ���������еĴ�ӡ����*/
                                                                                                                                                        /*ʹ��˵��:                                                     */
                                                                                                                                                        /*sh hipriv.sh "wlan0 performance_log_debug 0 0 :�رվۺϴ�ӡ   */
                                                                                                                                                        /*sh hipriv.sh "wlan0 performance_log_debug 0 1 :�򿪾ۺϴ�ӡ   */
                                                                                                                                                        /*sh hipriv.sh "wlan0 performance_log_debug 1 0 :��ӡ����ͳ��   */
                                                                                                                                                        /*sh hipriv.sh "wlan0 performance_log_debug 1 1 :�ۺ�ͳ����0    */
                                                                                                                                                        /*sh hipriv.sh "wlan0 performance_log_debug 255 0 :������п��ƿ���*/
                                                                                                                                                        /*sh hipriv.sh "wlan0 performance_log_debug 255 1 :�������п��ƿ���*/

#endif
#ifdef _PRE_WLAN_FEATURE_ROAM
    {"roam_enable",      wal_hipriv_roam_enable},   /* �������ο��� */
    {"roam_org",         wal_hipriv_roam_org},      /* ������������ */
    {"roam_band",        wal_hipriv_roam_band},     /* ��������Ƶ�� */
    {"roam_start",       wal_hipriv_roam_start},    /* ���β�������  hipriv "vap0 roam_start 0|1" 0���߲���ȱʧ��ʾɨ��+����, 1��ʾ����ǰ��ɨ�� */
    {"roam_info",        wal_hipriv_roam_info},     /* ������Ϣ��ӡ */
#endif  //_PRE_WLAN_FEATURE_ROAM
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    {"2040bss_enable",   wal_hipriv_enable_2040bss}, /* ����20/40 bssʹ��: hipriv "Hisilicon0 2040bss_enable 0|1" 0��ʾ20/40 bss�жϹرգ�1��ʾʹ�� */
#endif
#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    {"auto_freq",   wal_hipriv_set_auto_freq}, /* �����Զ���Ƶʹ��: hipriv "wlan0 auto_freq 0 0" �ڶ�������0��ʾ�رգ�1��ʾʹ�� */
#endif
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    {"customize_info",   wal_hipriv_dev_customize_info},            /* ��ӡdevice�ඨ�ƻ���Ϣ */
    {"get_lauch_cap",            wal_hipriv_get_lauch_cap},        /*��ѯ������������ sh hipriv.sh "Hisilicon0 get_lauch_cap"*/
#endif /* #ifdef _PRE_PLAT_FEATURE_CUSTOMIZE */
#ifdef _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN
    {"set_tx_classify_switch",        wal_hipriv_set_tx_classify_switch},       /* ����ҵ��ʶ���ܿ���: sh hipriv.sh "p2p-p2p0-0 set_tx_classify_switch 1/0"(1�򿪣�0�رգ�����Ĭ�Ͽ���) */
#endif  /* _PRE_WLAN_FEATURE_TX_CLASSIFY_LAN_TO_WLAN */

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    {"set_txrx_chain",   wal_hipriv_set_txrx_chain}, /* �����շ�ͨ��: hipriv "wlan0 set_txrx_chain 0/1/2" �ڶ������� 0:ͨ��0, 1:ͨ��1, 2:˫ͨ�� */
#endif

#ifdef _PRE_WLAN_FEATURE_HILINK_DEBUG
    {"fbt_set_mode",                   wal_hipriv_fbt_set_mode},              /*FBT ģʽ����hipriv.sh "wlan0 fbt_set_mode 0|1"*/
    {"fbt_scan_list_clear",            wal_hipriv_fbt_scan_list_clear},       /*���ɨ���б�hipriv.sh "wlan0 fbt_scan_list_clear"*/
    {"fbt_scan_specified_sta",         wal_hipriv_fbt_scan_specified_sta},    /*����ָ���û�hipriv.sh "wlan0 fbt_scan_specified_sta aa:bb:cc:dd:ee:ff"*/
    {"fbt_start_scan",                 wal_hipriv_fbt_start_scan},            /*��������hipriv.sh "wlan0 fbt_start_scan"*/
    {"fbt_print_scan_list",            wal_hipriv_fbt_print_scan_list},       /*��ӡ�����б�hipriv.sh "wlan0 fbt_print_scan_list"*/
    {"fbt_scan_enable",                wal_hipriv_fbt_scan_enable},           /*FBT ������������hipriv.sh "wlan0 fbt_scan_enable 0|1"*/
    {"fbt_scan_interval",              wal_hipriv_fbt_scan_interval},         /*FBT ����ʱ������hipriv.sh "wlan0 fbt_scan_interval [0,*]"*/
    {"fbt_scan_channel",               wal_hipriv_fbt_scan_channel},          /*FBT �����ŵ�����hipriv.sh "wlan0 fbt_scan_channel ** "*/
    {"fbt_scan_report_period",         wal_hipriv_fbt_scan_report_period},    /*FBT �����ϱ���������hipriv.sh "wlan0 fbt_scan_report_period [0,*]"*/
#endif

#ifdef _PRE_WLAN_FEATURE_EQUIPMENT_TEST
    {"chip_check",      wal_hipriv_chip_check},                  /* оƬ�Լ� */
    {"cfg_cw_signal",   wal_hipriv_send_cw_signal},               /* ���͵����ź�:         hipriv "wlan0 cfg_cw_signal   <value>" */
#endif
};

oal_uint32 wal_hipriv_get_debug_cmd_size(oal_void)
{
    return OAL_ARRAY_SIZE(g_ast_hipriv_cmd_debug);
}

#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

