/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_device.c
  �� �� ��   : ����
  ��    ��   : l00279018
  ��������   : 2015��1��31��
  ����޸�   :
  ��������   : hmac device��Ӧ��������ʵ�ֵ�Դ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��1��31��
    ��    ��   : l00279018
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
#include "frw_ext_if.h"
#include "hal_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_regdomain.h"
#include "mac_vap.h"

#include "dmac_reset.h"

#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_vap.h"
#include "hmac_rx_filter.h"

#include "hmac_chan_mgmt.h"
#include "hmac_dfs.h"
#ifdef _PRE_WLAN_CHIP_TEST
#include "hmac_test_main.h"
#endif

#include "hmac_data_acq.h"
#include "hmac_rx_filter.h"

#include "hmac_hcc_adapt.h"

#include "hmac_dfs.h"
#include "hmac_config.h"
#include "hmac_resource.h"
#include "hmac_device.h"
#include "hmac_scan.h"
#include "hmac_rx_data.h"
#include "hmac_hcc_adapt.h"
#include "hmac_dfx.h"
#include "hmac_protection.h"

#ifdef _PRE_WLAN_TCP_OPT
#include "mac_data.h"
#include "hmac_tcp_opt_struc.h"
#include "hmac_tcp_opt.h"
#endif

#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) &&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION))
#include <linux/fb.h>
#include <linux/list.h>
#include "plat_pm_wlan.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_DEVICE_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
oal_uint32 band_5g_enabled = OAL_TRUE;
/*lint -e578*//*lint -e19*/
oal_module_symbol(band_5g_enabled);
oal_module_license("GPL");
/*lint +e578*//*lint +e19*/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : hmac_device_exit
 ��������  : ȥ��ʼ��hmac device�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��31��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_device_exit(mac_board_stru *pst_board, mac_chip_stru *pst_chip, hmac_device_stru *pst_hmac_device)
{
    mac_device_stru   *pst_device;
    oal_uint32         ul_ret;
    oal_uint32                    ul_return;
    hmac_vap_stru                *pst_vap;
    mac_cfg_down_vap_param_stru   st_down_vap;
    oal_uint8                     uc_vap_idx;

    if (OAL_PTR_NULL == pst_hmac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_exit::pst_hmac_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ɨ��ģ��ȥ��ʼ�� */
    hmac_scan_exit(pst_hmac_device);

#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    hmac_pkt_mem_opt_exit(pst_hmac_device);
#endif

    pst_device = pst_hmac_device->pst_device_base_info;
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_exit::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ������ȥע�� */
#if ((_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE))
#ifdef CONFIG_HAS_EARLYSUSPEND
    unregister_early_suspend(&pst_hmac_device->early_suspend);
#else
    fb_unregister_client(&pst_hmac_device->pm_notifier);
#endif
#endif

    /* ��������vap��ʼ����HMAC������������VAPж��Ҳ��HMAC�� */
    uc_vap_idx = pst_device->uc_cfg_vap_id;
    pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(uc_vap_idx);

    if (OAL_PTR_NULL == pst_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_exit::pst_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

     /* ȡ��OBSS�����ϻ���ʱ�� */
    if (OAL_TRUE == pst_device->st_obss_aging_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&(pst_device->st_obss_aging_timer));
    }

    ul_return = hmac_config_del_vap(&pst_vap->st_vap_base_info,
                                 OAL_SIZEOF(mac_cfg_down_vap_param_stru),
                                 (oal_uint8 *)&st_down_vap);
    if (ul_return != OAL_SUCC)
    {
        OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_device_exit::hmac_config_del_vap failed[%d].}",ul_return);
        return ul_return;
    }

    for (uc_vap_idx = 0; uc_vap_idx < pst_device->uc_vap_num; uc_vap_idx++)
    {
        /* ��ȡ���ұ�һλΪ1��λ������ֵ��Ϊvap�������±� */
        pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_device_exit::mac_res_get_hmac_vap failed vap_idx[%u].}",uc_vap_idx);
            continue;
        }

        ul_return  = hmac_vap_destroy(pst_vap);
        if (OAL_SUCC != ul_return)
        {
            OAM_WARNING_LOG1(pst_vap->st_vap_base_info.uc_vap_id, OAM_SF_ANY, "{hmac_device_exit::hmac_vap_destroy failed[%d].}",ul_return);
            return ul_return;
        }
        pst_device->auc_vap_id[uc_vap_idx] = 0;
    }

    /*�ͷŹ����ṹ�� �Լ� ��Ӧ��������*/
#if 0
    ul_ret = pst_board->p_device_destroy_fun(pst_device);
#else
    ul_ret = mac_device_exit(pst_device);
#endif
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{mac_chip_exit::p_device_destroy_fun failed[%d].}", ul_ret);

        return ul_ret;
    }
    /* ָ�����mac device��ָ��Ϊ�� */
    pst_hmac_device->pst_device_base_info = OAL_PTR_NULL;

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 �� �� ��  : hmac_device_exit
 ��������  : ж��device�Ĳ�������(����֮ǰ���Ѵ�chip��ɾ��)
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_device_exit(mac_device_stru *pst_device)
{
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_device_exit::func enter.}");

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_device))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_exit::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_device->uc_vap_num = 0;
    pst_device->uc_sta_num = 0;
    pst_device->st_p2p_info.uc_p2p_device_num   = 0;
    pst_device->st_p2p_info.uc_p2p_goclient_num = 0;
    mac_res_free_dev(pst_device->uc_device_id);

#if 0
    pst_device->en_device_state = OAL_FALSE;
#else
    mac_device_set_state(pst_device, OAL_FALSE);
#endif

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_device_exit::func out.}");

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : hmac_chip_exit
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_chip_exit(mac_board_stru *pst_board, mac_chip_stru *pst_chip)
{
    hmac_device_stru  *pst_hmac_device;
    oal_uint32         ul_ret;
    oal_uint8          uc_device;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_chip || OAL_PTR_NULL == pst_board))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_chip_exit::param null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (uc_device = 0; uc_device < pst_chip->uc_device_nums; uc_device++)
    {
         pst_hmac_device = hmac_res_get_mac_dev(pst_chip->auc_device_id[uc_device]);

         /* ��Ų��λ�� �ͷ���Դ */
         hmac_res_free_mac_dev(pst_chip->auc_device_id[uc_device]);

         ul_ret = hmac_device_exit(pst_board, pst_chip, pst_hmac_device);
         if (OAL_SUCC != ul_ret)
         {
             OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_chip_exit::hmac_device_exit failed[%d].}", ul_ret);
             return ul_ret;
         }
    }

    ul_ret = mac_chip_exit(pst_board, pst_chip);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_chip_exit::mac_chip_exit failed[%d].}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_board_exit
 ��������  : �ͷ�ȫ�ֱ��������Ľṹ��
 �������  : board����ָ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��9��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_board_exit(mac_board_stru *pst_board)
{
    oal_uint8        uc_chip_idx;
    oal_uint32       ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_board))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_board_exit::pst_board null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    while (0 != pst_board->uc_chip_id_bitmap)
    {
        /* ��ȡ���ұ�һλΪ1��λ������ֵ��Ϊchip�������±� */
        uc_chip_idx = oal_bit_find_first_bit_one_byte(pst_board->uc_chip_id_bitmap);
        if (OAL_UNLIKELY(uc_chip_idx >= WLAN_CHIP_MAX_NUM_PER_BOARD))
        {
            OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_board_exit::invalid uc_chip_idx[%d] uc_chip_id_bitmap=%d.}",
                           uc_chip_idx, pst_board->uc_chip_id_bitmap);
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }

        ul_ret = hmac_chip_exit(pst_board, &(pst_board->ast_chip[uc_chip_idx]));
        if (OAL_SUCC != ul_ret)
        {
            OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hmac_board_exit::mac_chip_exit failed[%d].}", ul_ret);
            return ul_ret;
        }

        /* �����Ӧ��bitmapλ */
        oal_bit_clear_bit_one_byte(&pst_board->uc_chip_id_bitmap, uc_chip_idx);
    }

    /*�������ֵĳ�ʼ��*/
    mac_board_exit(pst_board);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_cfg_vap_init
 ��������  : ����VAP��ʼ��
 �������  : uc_dev_id: �豸id
 �������  :

 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 hmac_cfg_vap_init(mac_device_stru *pst_device)
{
    oal_int8             ac_vap_netdev_name[MAC_NET_DEVICE_NAME_LENGTH];
    oal_uint32           ul_ret;
    hmac_vap_stru       *pst_vap;

    /* ��ʼ�������У�ֻ��ʼ������vap������vap��Ҫͨ��������� */
    /*lint -e413*/
    ul_ret = mac_res_alloc_hmac_vap(&pst_device->uc_cfg_vap_id,
                                       OAL_OFFSET_OF(hmac_vap_stru, st_vap_base_info));
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::mac_res_alloc_hmac_vap failed[%d].}",ul_ret);
        return ul_ret;
    }
    /*lint +e413*/

    pst_vap = (hmac_vap_stru *)mac_res_get_hmac_vap(pst_device->uc_cfg_vap_id);
    if (OAL_PTR_NULL == pst_vap)
    {
        OAM_WARNING_LOG0(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::pst_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��hmac_vap_stru�ṹ���ʼ����ֵΪ0 */
    OAL_MEMZERO(pst_vap, OAL_SIZEOF(hmac_vap_stru));

{
    mac_cfg_add_vap_param_stru  st_param = {0};       /* ��������VAP�����ṹ�� */
    st_param.en_vap_mode = WLAN_VAP_MODE_CONFIG;
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
    st_param.bit_11ac2g_enable = OAL_TRUE;
    st_param.bit_disable_capab_2ght40 = OAL_FALSE;
#endif
    ul_ret = hmac_vap_init(pst_vap,
                               pst_device->uc_chip_id,
                               pst_device->uc_device_id,
                               pst_device->uc_cfg_vap_id,
                               &st_param);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::hmac_vap_init failed[%d].}",ul_ret);
        return ul_ret;
    }
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    /*��ʱdmacδ�ϵ磬֡�����޷��·�*/
#else
    /* ����֡���˼Ĵ��� */
    hmac_set_rx_filter_value(&pst_vap->st_vap_base_info);
#endif

    /* ����vap��id�Ǵ�0��ʼ��ŵģ�������chipʱ����Ӧ��������vap�����Ϊ0,1 */
    OAL_SPRINTF(ac_vap_netdev_name, MAC_NET_DEVICE_NAME_LENGTH, "Hisilicon%d", pst_device->uc_cfg_vap_id);

    ul_ret = hmac_vap_creat_netdev(pst_vap, ac_vap_netdev_name, (oal_int8 *)(pst_device->auc_hw_addr));
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(pst_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_cfg_vap_init::hmac_vap_creat_netdev failed[%d].}",ul_ret);
        return ul_ret;
    }

    /* ����OBSS�����ϻ���ʱ�� */
    hmac_protection_start_timer(pst_vap);

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
extern oal_bool_enum g_wlan_pm_switch;
/*****************************************************************************
 �� �� ��  : hmac_do_suspend_action
 ��������  : ����
 �������  : hmac device
 �������  :

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��16��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_do_suspend_action(hmac_device_stru    *pst_hmac_device, oal_uint8  uc_in_suspend)
{
    mac_device_stru         *pst_mac_device;
    oal_uint32               ul_ret;
    mac_vap_stru            *pst_cfg_mac_vap;
    mac_cfg_suspend_stru     st_suspend;
    oal_uint32               ul_is_wlan_poweron = OAL_TRUE;

    pst_mac_device = pst_hmac_device->pst_device_base_info;

    oal_spin_lock(&pst_hmac_device->st_suspend_lock);

    pst_mac_device->uc_in_suspend   = uc_in_suspend;

    pst_cfg_mac_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->uc_cfg_vap_id);
    if (OAL_PTR_NULL == pst_cfg_mac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_device->uc_cfg_vap_id, OAM_SF_ANY, "{hmac_do_suspend_action::pst_vap null.}");
        oal_spin_unlock(&pst_hmac_device->st_suspend_lock);
        return ;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)&&(_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    ul_is_wlan_poweron = wlan_pm_is_poweron();
#endif

    /* ����host�͹��Ĳ���device���ϵ����Ҫ��������״̬ͬ����device */
    if (g_wlan_pm_switch && ul_is_wlan_poweron)
    {
        st_suspend.uc_in_suspend        = uc_in_suspend;

        if ((OAL_TRUE == uc_in_suspend)
#ifdef _PRE_WLAN_FEATURE_WAPI
        && (OAL_TRUE != pst_hmac_device->pst_device_base_info->uc_wapi)
#endif
            )
        {
            pst_hmac_device->pst_device_base_info->uc_arpoffload_switch = OAL_TRUE;
            st_suspend.uc_arpoffload_switch = OAL_TRUE;
        }
        else
        {
            pst_hmac_device->pst_device_base_info->uc_arpoffload_switch = OAL_FALSE;
            st_suspend.uc_arpoffload_switch = OAL_FALSE;
        }
        hmac_wake_lock();
        /***************************************************************************
            ���¼���DMAC��, ͬ����Ļ����״̬��DMAC
        ***************************************************************************/
        ul_ret = hmac_config_send_event(pst_cfg_mac_vap, WLAN_CFGID_SUSPEND_ACTION_SYN, OAL_SIZEOF(mac_cfg_suspend_stru), (oal_uint8 *)&st_suspend);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_CFG, "{hmac_suspend_action::hmac_config_send_event failed[%d]}",ul_ret);
        }
        hmac_wake_unlock();
    }
    oal_spin_unlock(&pst_hmac_device->st_suspend_lock);
}

#ifdef CONFIG_HAS_EARLYSUSPEND
/*****************************************************************************
 �� �� ��  : hmac_early_suspend
 ��������  : ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_early_suspend(struct early_suspend *early_sup)
{
    hmac_device_stru    *pst_hmac_device;

    pst_hmac_device = OAL_CONTAINER_OF(early_sup, hmac_device_stru, early_suspend);
    hmac_do_suspend_action(pst_hmac_device,OAL_TRUE);
}

/*****************************************************************************
 �� �� ��  : hmac_late_resume
 ��������  : ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void hmac_late_resume(struct early_suspend *early_sup)
{
    hmac_device_stru    *pst_hmac_device;

    pst_hmac_device = OAL_CONTAINER_OF(early_sup,hmac_device_stru, early_suspend);
    hmac_do_suspend_action(pst_hmac_device,OAL_FALSE);
}
#else
/*****************************************************************************
 �� �� ��  : hmac_fb_notify
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
int hmac_fb_notify(struct notifier_block *nb,
                 unsigned long action, void *data)
{
    struct fb_event     *fb_event = data;
    int                 *blank = NULL;
    hmac_device_stru    *pst_hmac_device;

    /*struct fb_event *event = data;*/
    pst_hmac_device = OAL_CONTAINER_OF(nb,hmac_device_stru, pm_notifier);

    blank = fb_event->data;

    switch(*blank){
    case FB_BLANK_UNBLANK:
        /*resume device*/
        switch(action) {
        case FB_EARLY_EVENT_BLANK:
            hmac_do_suspend_action(pst_hmac_device,OAL_FALSE);
             break;
        case FB_EVENT_BLANK:
            break;
        default:
            break;
        }
        break;
    case FB_BLANK_VSYNC_SUSPEND:
    case FB_BLANK_HSYNC_SUSPEND:
    case FB_BLANK_NORMAL:
    case FB_BLANK_POWERDOWN:
    default:
        /*suspend device*/
        switch(action) {
        case FB_EARLY_EVENT_BLANK:
            hmac_do_suspend_action(pst_hmac_device,OAL_TRUE);
            break;
        case FB_EVENT_BLANK:
            break;
        default:
            break;
        }
        break;
    }

    return NOTIFY_OK;
}
#endif
#endif
/*****************************************************************************
 �� �� ��  : hma_send_evt2wal
 ��������  : hmac���¼���wal
 �������  : pst_event_mem: �¼��ṹ��
 �������  :

 �� �� ֵ  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��15��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_send_evt2wal(mac_vap_stru *pst_mac_vap, oal_uint8 uc_evtid, oal_uint8 *puc_evt, oal_uint32 ul_evt_len)
{
    frw_event_mem_stru         *pst_event_mem;
    frw_event_stru             *pst_event;
    oal_uint32                  ul_ret;

    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)ul_evt_len);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_SCAN, "{hmac_mgmt_scan_req_exception::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                       FRW_EVENT_TYPE_HOST_CTX,
                       uc_evtid,
                       (oal_uint16)ul_evt_len,
                       FRW_EVENT_PIPELINE_STAGE_0,
                       pst_mac_vap->uc_chip_id,
                       pst_mac_vap->uc_device_id,
                       pst_mac_vap->uc_vap_id);

    oal_memcopy((oal_void *)pst_event->auc_event_data, (oal_void *)puc_evt, ul_evt_len);

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    FRW_EVENT_FREE(pst_event_mem);
    return ul_ret;
}
/*****************************************************************************
 �� �� ��  : hmac_pwr_device_init
 ��������  : ���µ�������host device_stru�ĳ�ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��23��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_config_host_dev_init(mac_vap_stru *pst_mac_vap, oal_uint16 us_len, oal_uint8 *puc_param)
{
#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    mac_device_stru     *pst_mac_device;
    oal_uint32           ul_loop = 0;
#endif
#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    hmac_device_stru    *pst_hmac_device;
#endif

    if(OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init:: pst_mac_device NULL pointer!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_device_init:: pst_mac_device[%d] NULL pointer!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (ul_loop = 0; ul_loop < MAC_MAX_SUPP_CHANNEL; ul_loop++)
    {
        pst_mac_device->st_ap_channel_list[ul_loop].us_num_networks = 0;
        pst_mac_device->st_ap_channel_list[ul_loop].en_ch_type      = MAC_CH_TYPE_NONE;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_config_host_dev_init::pst_hmac_device[%] null!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }
    hmac_pkt_mem_opt_init(pst_hmac_device);
#endif

    /* TBD �������µ�ʱ����Ҫ��ʼ����hmac_device_stru�µ���Ϣ */

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_config_host_dev_exit
 ��������  : �µ�������host device_stru��ȥ��ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��26��
    ��    ��   : s00304087
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_config_host_dev_exit(mac_vap_stru *pst_mac_vap)
{
#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    hmac_device_stru *pst_hmac_device = hmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_config_host_dev_exit::pst_hmac_device[%] null!}", pst_mac_vap->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    hmac_pkt_mem_opt_exit(pst_hmac_device);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_device_init
 ��������  : ��ʼ��hmac device�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_device_init(oal_uint8 *puc_device_id, mac_chip_stru *pst_chip)
{
    oal_uint8            uc_dev_id;
    mac_device_stru     *pst_mac_device;
    hmac_device_stru    *pst_hmac_device;
    oal_uint32           ul_ret;
    oal_uint32           ul_loop = 0;

    /*���빫��mac device�ṹ��*/
    ul_ret = mac_res_alloc_hmac_dev(&uc_dev_id);
    if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_device_init::mac_res_alloc_dmac_dev failed[%d].}", ul_ret);

        return OAL_FAIL;
    }

    /* ��ȡmac device�ṹ��ָ�� */
    pst_mac_device = mac_res_get_dev(uc_dev_id);

    if (OAL_PTR_NULL == pst_mac_device)
    {
       OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init::pst_device null.}");

       return OAL_ERR_CODE_PTR_NULL;
    }

    ul_ret = mac_device_init(pst_mac_device, pst_chip->ul_chip_ver, pst_chip->uc_chip_id, uc_dev_id);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_device_init::mac_device_init failed[%d], chip_ver[0x%x].}", ul_ret, pst_chip->ul_chip_ver);

        mac_res_free_dev(uc_dev_id);
        return ul_ret;
    }

    /* ����hmac device��Դ */
    if(OAL_UNLIKELY(hmac_res_alloc_mac_dev(uc_dev_id) != OAL_SUCC))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init::hmac_res_alloc_mac_dev failed.}");
        return OAL_FAIL;
    }

    /* ��ȡhmac device����������ز�����ֵ */
    pst_hmac_device = hmac_res_get_mac_dev(uc_dev_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_device_init::pst_hmac_device[%] null!}", uc_dev_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ṹ���ʼ�� */
    OAL_MEMZERO(pst_hmac_device, OAL_SIZEOF(hmac_device_stru));

    pst_hmac_device->pst_device_base_info = pst_mac_device;

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    oal_spin_lock_init(&pst_hmac_device->st_suspend_lock);
#ifdef CONFIG_HAS_EARLYSUSPEND
    pst_hmac_device->early_suspend.level = EARLY_SUSPEND_LEVEL_BLANK_SCREEN + 20;
    pst_hmac_device->early_suspend.suspend = hmac_early_suspend;
    pst_hmac_device->early_suspend.resume  = hmac_late_resume;
    register_early_suspend(&pst_hmac_device->early_suspend);
#else
    pst_hmac_device->pm_notifier.notifier_call = hmac_fb_notify;
    fb_register_client(&pst_hmac_device->pm_notifier);
#endif
#endif

    /* ɨ��ģ���ʼ�� */
    hmac_scan_init(pst_hmac_device);

#ifdef _PRE_WLAN_FEATURE_PKT_MEM_OPT
    hmac_pkt_mem_opt_init(pst_hmac_device);
#endif

    /* ��ʼ��P2P �ȴ����� */
    OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_device->st_netif_change_event));
#ifdef _PRE_WLAN_TCP_OPT
        pst_hmac_device->sys_tcp_tx_ack_opt_enable = DEFAULT_TX_TCP_ACK_OPT_ENABLE;
        pst_hmac_device->sys_tcp_rx_ack_opt_enable = DEFAULT_RX_TCP_ACK_OPT_ENABLE;

#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    for (ul_loop = 0; ul_loop < MAC_MAX_SUPP_CHANNEL; ul_loop++)
    {
    pst_mac_device->st_ap_channel_list[ul_loop].us_num_networks = 0;
    pst_mac_device->st_ap_channel_list[ul_loop].en_ch_type      = MAC_CH_TYPE_NONE;
    }
#endif

    /* ��ʼ��device�µ�rx tx BA�Ự��Ŀ */
#ifndef _PRE_WLAN_FEATURE_AMPDU_VAP
    pst_mac_device->uc_rx_ba_session_num = 0;
    pst_mac_device->uc_tx_ba_session_num = 0;
#endif
    /* ���θ�ֵ��CHIP����Ҫ�����device id */
    *puc_device_id = uc_dev_id;

    /* ����vap��ʼ��*/
    ul_ret = hmac_cfg_vap_init(pst_mac_device);
    if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_cfg_vap_init failed[%d].}", ul_ret);
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_DFS
    hmac_dfs_init(pst_mac_device);
#endif

#if 0
    /* dev��Ϣ��ʼ�����֮��֪ͨwalע��cfg80211�ӿڣ��˴�ֻ��offloadʱ��Ҫ�˻��� */
    pst_mac_vap = (mac_vap_stru  *)mac_res_get_mac_vap(pst_mac_device->uc_cfg_vap_id);
    hmac_send_evt2wal(pst_mac_vap, HMAC_HOST_CTX_EVENT_SUB_TYPE_INIT, OAL_PTR_NULL, 0);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_chip_init
 ��������  : chip�����ʼ������
 �������  : chip����ָ�롢chip id
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��ԭ��
 ���ú���  : mac_device_init
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_chip_init(mac_chip_stru *pst_chip, oal_uint8 uc_chip_id)
{
    oal_uint8  uc_device;
    oal_uint32 ul_ret;
    oal_uint8  uc_device_max;

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_chip_init::func enter.}");

    mac_chip_init(pst_chip, uc_chip_id);

    pst_chip->uc_chip_id = uc_chip_id;

    /* CHIP���ýӿ� oal_get_chip_version*/
    pst_chip->ul_chip_ver = oal_chip_get_version();

    /* OAL�ӿڻ�ȡ֧��device���� */
    uc_device_max = oal_chip_get_device_num(pst_chip->ul_chip_ver);

    for (uc_device = 0; uc_device < uc_device_max; uc_device++)
    {
        /* hmac device�ṹ��ʼ�� */
        ul_ret = hmac_device_init(&pst_chip->auc_device_id[uc_device], pst_chip);

        if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_device_init failed[%d].}", ul_ret);
            return OAL_FAIL;
        }
    }

    /* ����device���� */
    pst_chip->uc_device_nums        = uc_device_max;

    /* ��ʼ������ٽ�state��ΪTRUE */
    pst_chip->en_chip_state         = OAL_TRUE;

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_chip_init::func out.}");

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_board_init
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��8��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_board_init(mac_board_stru *pst_board)
{
    oal_uint8               uc_chip;
    oal_uint32              ul_ret;
	oal_uint32              ul_chip_max_num;

    OAL_MEMZERO(pst_board, OAL_SIZEOF(mac_board_stru));

    mac_board_init(pst_board);

    /* chip֧�ֵ��������PCIe���ߴ����ṩ; */
    ul_chip_max_num = oal_bus_get_chip_num();

    for (uc_chip = 0; uc_chip < ul_chip_max_num; uc_chip++)
    {
        ul_ret = hmac_chip_init(&pst_board->ast_chip[uc_chip], uc_chip);
        if (OAL_SUCC != ul_ret)
        {
             OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_init_event_process::hmac_chip_init failed[%d], uc_chip_id[%d].}", ul_ret, uc_chip);
             return OAL_FAIL;
        }

        oal_bit_set_bit_one_byte(&pst_board->uc_chip_id_bitmap, uc_chip);
    }
    return OAL_SUCC;
}
#else
/*****************************************************************************
 �� �� ��  : hmac_device_init
 ��������  : ��ʼ��hmac device�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��31��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_device_init(oal_uint8  uc_device_id, mac_chip_stru *pst_dst_chip)
{
    mac_device_stru     *pst_mac_device;
    hmac_device_stru    *pst_hmac_device;
    oal_uint32           ul_ret;
    oal_uint32           ul_loop = 0;

    if(OAL_UNLIKELY(mac_res_alloc_hmac_dev(uc_device_id) != OAL_SUCC))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init::mac_res_alloc_hmac_dev failed.}");
        return OAL_FAIL;
    }

    /* ��ȡmac device�ṹ��ָ�� */
    pst_mac_device = mac_res_get_dev(uc_device_id);

    ul_ret = mac_device_init(pst_mac_device, pst_dst_chip->ul_chip_ver, pst_dst_chip->uc_chip_id, uc_device_id);
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{hmac_device_init::mac_device_init failed[%d], chip_ver[0x%x].}", ul_ret, pst_dst_chip->ul_chip_ver);

        mac_res_free_dev(uc_device_id);
        return ul_ret;
    }

    /* ����hmac device��Դ */
    if(OAL_UNLIKELY(hmac_res_alloc_mac_dev(uc_device_id) != OAL_SUCC))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_device_init::hmac_res_alloc_mac_dev failed.}");
        return OAL_FAIL;
    }

    /* ��ȡhmac device����������ز�����ֵ */
    pst_hmac_device = hmac_res_get_mac_dev(uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_hmac_device))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_device_init::pst_hmac_device[%d] null!}", uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* �ṹ���ʼ�� */
    OAL_MEMZERO(pst_hmac_device, OAL_SIZEOF(hmac_device_stru));

    pst_hmac_device->pst_device_base_info = pst_mac_device;

    /* ɨ��ģ���ʼ�� */
    hmac_scan_init(pst_hmac_device);

    /* ��ʼ��P2P �ȴ����� */
	OAL_WAIT_QUEUE_INIT_HEAD(&(pst_hmac_device->st_netif_change_event));
#ifdef _PRE_WLAN_TCP_OPT
    pst_hmac_device->sys_tcp_tx_ack_opt_enable = DEFAULT_TX_TCP_ACK_OPT_ENABLE;
    pst_hmac_device->sys_tcp_rx_ack_opt_enable = DEFAULT_RX_TCP_ACK_OPT_ENABLE;

#endif

#ifdef _PRE_WLAN_FEATURE_20_40_80_COEXIST
    for (ul_loop = 0; ul_loop < MAC_MAX_SUPP_CHANNEL; ul_loop++)
    {
        pst_mac_device->st_ap_channel_list[ul_loop].us_num_networks = 0;
        pst_mac_device->st_ap_channel_list[ul_loop].en_ch_type      = MAC_CH_TYPE_NONE;
    }
#endif

#ifndef _PRE_WLAN_FEATURE_AMPDU_VAP
    /* ��ʼ��device�µ�rx tx BA�Ự��Ŀ */
    pst_mac_device->uc_rx_ba_session_num = 0;
    pst_mac_device->uc_tx_ba_session_num = 0;
#endif
    /* ����vap��ʼ��*/
    ul_ret = hmac_cfg_vap_init(pst_mac_device);
    if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_cfg_vap_init failed[%d].}", ul_ret);
        return OAL_FAIL;
    }

#ifdef _PRE_WLAN_FEATURE_DFS
    hmac_dfs_init(pst_mac_device);
#endif

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : hmac_chip_init
 ��������  : chip�����ʼ������
 �������  : chip����ָ�롢chip id
 �������  : ��
 �� �� ֵ  : �ɹ���ʧ��ԭ��
 ���ú���  : mac_device_init
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hmac_chip_init(
                mac_chip_stru *pst_dst_chip,
                mac_chip_stru *pst_src_chip,
                oal_uint8      uc_chip_id)
{
    oal_uint8  uc_device;
    oal_uint32 ul_ret;
    oal_uint8  uc_dev_id;


    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_chip_init::func enter.}");

    mac_chip_init(pst_dst_chip, pst_src_chip->uc_chip_id);

    pst_dst_chip->uc_chip_id = pst_src_chip->uc_chip_id;

    pst_dst_chip->ul_chip_ver = pst_src_chip->ul_chip_ver;

    pst_dst_chip->uc_device_nums = pst_src_chip->uc_device_nums;

    for (uc_device = 0; uc_device < pst_dst_chip->uc_device_nums; uc_device++)
    {
        uc_dev_id = pst_src_chip->auc_device_id[uc_device];

        pst_dst_chip->auc_device_id[uc_device] = uc_dev_id;

        /* hmac device�ṹ��ʼ�� */
        ul_ret = hmac_device_init(uc_dev_id, pst_dst_chip);
        if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_device_init failed[%d].}", ul_ret);
            return OAL_FAIL;
        }

#if 0
        /* ����vap��ʼ����HMAC�� */
        ul_ret = hmac_cfg_vap_init(mac_res_get_dev(uc_dev_id));
        if(OAL_UNLIKELY(ul_ret != OAL_SUCC))
        {
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_chip_init::hmac_cfg_vap_init failed[%d].}", ul_ret);
            return OAL_FAIL;
        }
#endif /*mac��������ɾ�����߼�*/
    }
    /* ��ʼ������ٽ�state��ΪTRUE */
    pst_dst_chip->en_chip_state = OAL_TRUE;

    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_chip_init::func out.}");

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_board_init
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��8��
    ��    ��   : ��� 64406
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_board_init(oal_uint32 ul_chip_max_num, mac_chip_stru *pst_chip)
{
    oal_uint8              uc_chip;
    oal_uint32             ul_ret;

    OAL_MEMZERO(&g_st_hmac_board, OAL_SIZEOF(mac_board_stru));

    mac_board_init(&g_st_hmac_board);

    for (uc_chip = 0; uc_chip < ul_chip_max_num; uc_chip++)
    {
        ul_ret = hmac_chip_init(&g_st_hmac_board.ast_chip[uc_chip], pst_chip + uc_chip, uc_chip);
        if (OAL_SUCC != ul_ret)
        {
             OAM_WARNING_LOG2(0, OAM_SF_ANY, "{hmac_init_event_process::hmac_chip_init failed[%d], uc_chip_id[%d].}", ul_ret, uc_chip);
             return OAL_FAIL;
        }
        oal_bit_set_bit_one_byte(&g_st_hmac_board.uc_chip_id_bitmap, uc_chip);
    }
    return OAL_SUCC;
}
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

