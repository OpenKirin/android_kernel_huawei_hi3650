/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : wal_linux_netlink_acs.c
  �� �� ��   : ����
  ��    ��   : w00196298
  ��������   : 2013��12��13��
  ����޸�   :
  ��������   : WAL NETLINK ACS�ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��12��13��
    ��    ��   : w00196298
    �޸�����   : �����ļ�

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_SUPPORT_ACS

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "wal_main.h"
#include "oam_linux_netlink.h"
#include "wal_config_acs.h"
#include "wal_ext_if.h"
#include "mac_vap.h"
#include "mac_resource.h"
#include "mac_device.h"
#include "hmac_ext_if.h"
#include "dmac_acs.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_WAL_CONFIG_ACS_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern oal_void  oam_netlink_ops_register(oam_nl_cmd_enum_uint8 en_type, oal_uint32 (*p_func)(oal_uint8 *puc_data, oal_uint32 ul_len));
extern oal_void  oam_netlink_ops_unregister(oam_nl_cmd_enum_uint8 en_type);
extern oal_int32  oam_netlink_kernel_send(oal_uint8 *puc_data, oal_uint32 ul_data_len, oam_nl_cmd_enum_uint8 en_type);

frw_timeout_stru g_st_acs_timer;


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : wal_acs_netlink_recv
 ��������  : ��WAL���ACS������պ����ҽ����ں�NETLINK�������
 �������  :
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��13��
    ��    ��   : wangshanbo
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_acs_netlink_recv(oal_uint8 *puc_data, oal_uint32 ul_len)
{
    oal_uint32        ul_device_num;
    oal_uint32        ul_ret;
    mac_device_stru  *pst_mac_dev;
    mac_vap_stru     *pst_mac_vap;
    mac_acs_cmd_stru *pst_acs_cmd_hdr;

    pst_acs_cmd_hdr = (mac_acs_cmd_stru *)puc_data;

    /* ������DEVICE�㲥һ�� */
    for (ul_device_num = 0; ul_device_num < MAC_RES_MAX_DEV_NUM; ul_device_num++)
    {
        pst_mac_dev = mac_res_get_dev(ul_device_num);

        /* �豸������ */
        if (OAL_PTR_NULL == pst_mac_dev)
        {
            continue;
        }

        /* �豸δ��ʼ�� */
        if (OAL_FALSE == pst_mac_dev->en_device_state)
        {
            continue;
        }

        /* ACSδʹ�� */
        if (OAL_PTR_NULL == pst_mac_dev->pst_acs)
        {
            continue;
        }

        // note:����û���κ�ҵ��VAP���������ղ���Ӧ�ò������
        pst_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_dev->auc_vap_id[0]);
        if (OAL_PTR_NULL == pst_mac_vap)
        {
            continue;
        }

        ul_ret = hmac_config_set_acs_cmd(pst_mac_vap, (oal_uint16)ul_len, puc_data);
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG3(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{wal_acs_netlink_recv::app send cmd failed:cmd=%d seq=%d dev=%d}\r\n",
                    pst_acs_cmd_hdr->uc_cmd, pst_acs_cmd_hdr->ul_cmd_cnt, ul_device_num);
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_acs_response_event_handler
 ��������  : ��������HMAC��ACS��Ӧ�¼�����ͨ��NETLINKת����APP
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��17��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_acs_response_event_handler(frw_event_mem_stru *pst_event_mem)
{
    mac_acs_response_hdr_stru *pst_acs_resp_hdr;
    frw_event_stru            *pst_event;

    pst_event        = (frw_event_stru *)pst_event_mem->puc_data;
    pst_acs_resp_hdr = (mac_acs_response_hdr_stru *)pst_event->auc_event_data;

    if (pst_acs_resp_hdr->uc_cmd == DMAC_ACS_CMD_DO_SCAN)
    {
        oal_uint32  puc_real_dat = *(oal_uint32 *)(pst_acs_resp_hdr + 1);

        pst_acs_resp_hdr = (mac_acs_response_hdr_stru *)puc_real_dat;
        oam_netlink_kernel_send((oal_uint8 *)pst_acs_resp_hdr, pst_acs_resp_hdr->ul_len, OAM_NL_CMD_ACS);
        OAL_MEM_FREE((oal_void *)puc_real_dat, OAL_TRUE);
    }
    else
    {
        oam_netlink_kernel_send((oal_uint8 *)pst_acs_resp_hdr, pst_acs_resp_hdr->ul_len, OAM_NL_CMD_ACS);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_acs_timer_handler
 ��������  : WAL ACS�Ĳ��Զ�ʱ�����ڴ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��18��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_acs_timer_handler(void *p_arg)
{
    oal_uint8   auc_buf[8];
    oal_uint32  ul_len = 4;

    OAL_MEMZERO(auc_buf, 4);
    auc_buf[0] = 2;  /* ACS PING COMMAND */

    wal_acs_netlink_recv(auc_buf, ul_len);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_linux_netlink_acs_init
 ��������  : ACS��WAL��ĳ�ʼ��������NETLINK���ӵĹҽ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��16��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_acs_init(oal_void)
{
    oam_netlink_ops_register(OAM_NL_CMD_ACS, wal_acs_netlink_recv);
    /* ����ʹ�� */
#if 0
    FRW_TIMER_CREATE_TIMER(&g_st_acs_timer,
                           wal_acs_timer_handler,
                           2000,                    /* 2000ms����һ�� */
                           OAL_PTR_NULL,            /* ���贫����� */
                           OAL_TRUE,                /* ���ڵ��� */
                           OAM_MODULE_ID_WAL);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_acs_exit
 ��������  : ACS��WAL����˳������������ͷ���Դ
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��16��
    ��    ��   : w00196298
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wal_acs_exit(oal_void)
{
    oam_netlink_ops_unregister(OAM_NL_CMD_ACS);

    return OAL_SUCC;
}

#endif /* #ifdef _PRE_SUPPORT_ACS */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
