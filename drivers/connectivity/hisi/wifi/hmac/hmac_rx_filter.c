/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hmac_rx_filter.c
  �� �� ��   : ����
  ��    ��   : z00241943
  ��������   : 2014��7��14��
  ����޸�   :
  ��������   : ֡���˴����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��14��
    ��    ��   : z00241943
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
#include "wlan_spec.h"
#include "wlan_types.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "dmac_ext_if.h"
#include "hmac_rx_filter.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HMAC_RX_FILTER_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
oal_bool_enum_uint8 g_en_rx_filter_enable;
oal_uint32 g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BUTT][MAC_VAP_STATE_BUTT];
oal_uint32 g_ast_multi_staup_sta_rx_filter[MAC_VAP_STA_STATE_BUTT];
oal_uint32 g_ast_multi_staup_ap_rx_filter[MAC_VAP_AP_STATE_BUTT];
oal_uint32 g_ast_multi_apup_sta_rx_filter[MAC_VAP_STA_STATE_BUTT];

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hmac_find_is_sta_up
 ��������  : �����Ƿ����Ѿ�UP��STA
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_find_is_sta_up(mac_device_stru *pst_mac_device)
{
    mac_vap_stru                  *pst_vap;
    oal_uint8                      uc_vap_idx;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_find_is_sta_up::pst_mac_vap null,vap_idx=%d.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if ((WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode) && (MAC_VAP_STATE_UP == pst_vap->en_vap_state))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_find_is_ap_up
 ��������  : �����Ƿ����Ѿ�UP��AP
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8 hmac_find_is_ap_up(mac_device_stru *pst_mac_device)
{
    mac_vap_stru                  *pst_vap;
    oal_uint8                      uc_vap_idx;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_find_is_ap_up::pst_mac_vap null,vap_idx=%d.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if ((MAC_VAP_STATE_INIT != pst_vap->en_vap_state) && (WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode))
        {
            return OAL_TRUE;
        }
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : hmac_calc_up_ap_num
 ��������  : ���㲻����inti״̬��VAP����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_calc_up_ap_num(mac_device_stru *pst_mac_device)
{
    mac_vap_stru                  *pst_vap;
    oal_uint8                      uc_vap_idx;
    oal_uint8                      ul_up_ap_num = 0;

    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {
        pst_vap = (mac_vap_stru *)mac_res_get_mac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_vap)
        {
            OAM_ERROR_LOG1(0, OAM_SF_SCAN, "{hmac_calc_up_ap_num::pst_mac_vap null,vap_idx=%d.}",
                           pst_mac_device->auc_vap_id[uc_vap_idx]);
            continue;
        }

        if ((MAC_VAP_STATE_INIT != pst_vap->en_vap_state) && (WLAN_VAP_MODE_BSS_AP == pst_vap->en_vap_mode))
        {
            ul_up_ap_num++;
        }
        else if ((WLAN_VAP_MODE_BSS_STA == pst_vap->en_vap_mode) && (MAC_VAP_STATE_UP == pst_vap->en_vap_state))
        {
            ul_up_ap_num++;
        }
    }

    return ul_up_ap_num;
}

/*****************************************************************************
 �� �� ��  : hmac_find_up_vap
 ��������  : �ҵ�up vap (���ȼ�:AP > STA)
 �������  : pst_mac_device
 �������  : ppst_mac_vap
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��15��
    ��    ��   : xiaoyuren
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_find_up_vap(mac_device_stru *pst_mac_device, mac_vap_stru **ppst_mac_vap)
{
    oal_uint32                     ul_ret;
    mac_vap_stru                  *pst_vap_up;     /* ����UP״̬��VAP */

    /* find up VAP */
    ul_ret = mac_device_find_up_vap(pst_mac_device, &pst_vap_up);
    if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
    {
        *ppst_mac_vap = pst_vap_up;
        /* find up AP */
        ul_ret = mac_device_find_up_ap(pst_mac_device, &pst_vap_up);
        if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
        {
            *ppst_mac_vap = pst_vap_up;
        }

        return OAL_SUCC;
    }
    else
    {
        *ppst_mac_vap = OAL_PTR_NULL;
        return OAL_FALSE;
    }
}

#if 0
/*****************************************************************************
 �� �� ��  : hmac_set_rx_filter_value
 ��������  : AP����յ���ӦSTA�Ĺ���������Ϣ
             ���޶�Ϊdmac_set_rx_filter_value
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��16��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_set_rx_filter_value(mac_vap_stru *pst_mac_vap)
{

#ifndef _PRE_WLAN_PHY_PERFORMANCE
    mac_device_stru                        *pst_mac_device;
    frw_event_mem_stru                     *pst_event_mem;
    frw_event_stru                         *pst_event;
    oal_uint32                              ul_ret;
    oal_uint32                              ul_rx_filter_val;
#ifdef _PRE_WLAN_FEATURE_P2P
    mac_vap_stru                           *pst_vap_up;     /* ����UP״̬��VAP */
#endif

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_HW_TEST
    /* ��Ϊ���գ�ֱ�ӷ��� */
    if (HAL_ALWAYS_RX_RESERVED == pst_mac_device->pst_device_stru->bit_al_rx_flag)
    {
        return OAL_SUCC;
    }
#endif

    if (OAL_FALSE == g_en_rx_filter_enable)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::g_en_rx_filter_enable is false.}");
        return OAL_SUCC;
    }


    if ((MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state) || (MAC_VAP_STATE_AP_PAUSE == pst_mac_vap->en_vap_state))
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::not need change rx filter!}");
        return OAL_SUCC;
    }

    /* ֻ��1��VAP STA/AP */
    if ((1 == pst_mac_device->uc_vap_num) || (WLAN_VAP_MODE_CONFIG == pst_mac_vap->en_vap_mode))
    {
        ul_rx_filter_val = g_ast_normal_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
    }
    else if ((1 < pst_mac_device->uc_vap_num) && (0 == pst_mac_device->uc_sta_num))
    {
        /* �����ʱ��AP������Down��״̬������Ҫ�����κ�ֵ��ֱ�ӷ��� */
        if ((0 != hmac_calc_up_ap_num(pst_mac_device)) && (MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state))
        {
            return OAL_SUCC;
        }

        ul_rx_filter_val = g_ast_normal_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
    }
#ifdef _PRE_WLAN_FEATURE_P2P
    /* ��STA��������� */
    else if ((1 < pst_mac_device->uc_vap_num) && (pst_mac_device->uc_vap_num == pst_mac_device->uc_sta_num))
    {
        /* DTS2015032507646 �����ʱ��STA������Down��״̬������Ҫ�����κ�ֵ��ֱ�ӷ��� */
        /* DTS2015033003804 �����VAP����£�����һ����down����������STA beacon miss���� */
        if ((0 != hmac_calc_up_ap_num(pst_mac_device))
            && ((MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state)
                || (MAC_VAP_STATE_STA_FAKE_UP == pst_mac_vap->en_vap_state)
                || (MAC_VAP_STATE_STA_SCAN_COMP == pst_mac_vap->en_vap_state)))
        {
            /*����up vap. ���ȼ�: AP > STA*/
            ul_ret = hmac_find_up_vap(pst_mac_device, &pst_vap_up);
            if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
            {
                /* ���������up vap,������vap״̬ΪMAC_VAP_STATE_INIT,MAC_VAP_STATE_STA_FAKE_UP,
                   MAC_VAP_STATE_STA_SCAN_COMP��rx filter, ���õ�ǰup VAP��rx filter, ���ȼ���AP > STA */
                ul_rx_filter_val = g_ast_p2p_mode_rx_filter[pst_vap_up->en_vap_mode][MAC_VAP_STATE_UP];
            }
            else
            {
                return OAL_SUCC;
            }
        }
        else
        {
            /* WLAN/P2P_DEV/P2P_GO ��WLAN/P2P_DEV/P2P_CL ������� */
            ul_rx_filter_val = g_ast_p2p_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
        }
    }
    /* ��AP��STA������������� */
    else if ((1 < pst_mac_device->uc_vap_num) && (0 != pst_mac_device->uc_sta_num)
              && (pst_mac_device->uc_vap_num > pst_mac_device->uc_sta_num))
    {
        /* DTS2015032507646 �����ʱ��STA������Down��״̬������Ҫ�����κ�ֵ��ֱ�ӷ��� */
        /* DTS2015033003804 �����VAP����£�����һ����down����������STA beacon miss���� */
        if ((0 != hmac_calc_up_ap_num(pst_mac_device))
            && ((MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state)
                || (MAC_VAP_STATE_STA_FAKE_UP == pst_mac_vap->en_vap_state)
                || (MAC_VAP_STATE_STA_SCAN_COMP == pst_mac_vap->en_vap_state)))
        {
            /*����up vap. ���ȼ�: AP > STA*/
            ul_ret = hmac_find_up_vap(pst_mac_device, &pst_vap_up);
            if ((OAL_SUCC == ul_ret) && (OAL_PTR_NULL != pst_vap_up))
            {
                /* ���������up vap,������vap״̬ΪMAC_VAP_STATE_INIT,MAC_VAP_STATE_STA_FAKE_UP,
                   MAC_VAP_STATE_STA_SCAN_COMP��rx filter, ���õ�ǰup VAP��rx filter, ���ȼ���AP > STA */
                ul_rx_filter_val = g_ast_p2p_mode_rx_filter[pst_vap_up->en_vap_mode][MAC_VAP_STATE_UP];
            }
            else
            {
                return OAL_SUCC;
            }
        }
        else
        {
            /* WLAN/P2P_DEV/P2P_GO �������,����ɨ��׶���Ҫ�յ�����BSS�ĵ�������֡��
               ���������SCAN״̬�±���ʹ��STA״̬�µ�����ֵ������ʹ��AP UP״̬������ֵ */
            if ((pst_mac_vap->en_vap_state == MAC_VAP_STATE_STA_WAIT_SCAN)
               || (pst_mac_vap->en_vap_state == MAC_VAP_STATE_STA_OBSS_SCAN)
               || (pst_mac_vap->en_vap_state == MAC_VAP_STATE_STA_BG_SCAN))
            {
                ul_rx_filter_val = g_ast_p2p_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
            }
            else
            {
                ul_rx_filter_val = g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_UP];
            }

        }
    }
#endif /* _PRE_WLAN_FEATURE_P2P */
    else
    {
        ul_rx_filter_val = g_ast_repeater_mode_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
    }

     /* ���¼���DMAC, �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(oal_uint32));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_RX_FILTER,
                    OAL_SIZEOF(oal_uint32),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

    /* �������� */
    oal_memcopy(pst_event->auc_event_data, (oal_void *)&ul_rx_filter_val, OAL_SIZEOF(oal_uint32));

    /* liuming add test code */
    OAM_INFO_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::start dispatch.}");

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_FAIL;
    }

    FRW_EVENT_FREE(pst_event_mem);

#endif

    return OAL_SUCC;
}

#endif

/*****************************************************************************
 �� �� ��  : hmac_set_rx_filter_value
 ��������  : AP����յ���ӦSTA�Ĺ���������Ϣ
             ���޶�Ϊdmac_set_rx_filter_value
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��16��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 hmac_set_rx_filter_value(mac_vap_stru *pst_mac_vap)
{
#ifndef _PRE_WLAN_PHY_PERFORMANCE
    mac_device_stru                        *pst_mac_device;
    frw_event_mem_stru                     *pst_event_mem;
    frw_event_stru                         *pst_event;
    oal_uint32                              ul_ret;
    oal_uint32                              ul_rx_filter_val;

    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_mac_device = mac_res_get_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_mac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_HW_TEST
    /* ��Ϊ���գ�ֱ�ӷ��� */
    if (HAL_ALWAYS_RX_RESERVED == pst_mac_device->pst_device_stru->bit_al_rx_flag)
    {
        return OAL_SUCC;
    }
#endif

    if (OAL_FALSE == g_en_rx_filter_enable)
    {
        OAM_INFO_LOG0(pst_mac_vap->uc_vap_id, OAM_SF_ANY, "{hmac_set_rx_filter_value::g_en_rx_filter_enable is false.}");
        return OAL_SUCC;
    }

    if (MAC_VAP_STATE_PAUSE == pst_mac_vap->en_vap_state)
    {
        return OAL_SUCC;
    }

    if (hmac_find_is_ap_up(pst_mac_device)) /* ��VAPģʽ��AP�Ѿ�UP*/
    {
        if ((MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state)
            || (MAC_VAP_STATE_STA_FAKE_UP == pst_mac_vap->en_vap_state))
        {
            return OAL_SUCC;
        }

        if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            if (hmac_find_is_sta_up(pst_mac_device) && pst_mac_vap->en_vap_state < MAC_VAP_AP_STATE_BUTT)
            {
                ul_rx_filter_val = g_ast_multi_staup_ap_rx_filter[pst_mac_vap->en_vap_state];
            }
            else
            {
                ul_rx_filter_val = g_ast_single_vap_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
            }
        }
        else
        {
            /* ��VAPģʽ��STA����(��STA�Ѿ�up��û��STA up������£�����APģʽ��ʹ�ø�����) */
            ul_rx_filter_val = g_ast_multi_apup_sta_rx_filter[pst_mac_vap->en_vap_state];
        }
    }
    else if (hmac_find_is_sta_up(pst_mac_device)) /* ��VAPģʽ��STA�Ѿ�UP*/
    {
        /* ��VAPģʽ��STA����(��STA�Ѿ�up��û��STA up������£�����APģʽ��ʹ�ø�����) */
        if ((MAC_VAP_STATE_INIT == pst_mac_vap->en_vap_state) || (MAC_VAP_STATE_STA_FAKE_UP == pst_mac_vap->en_vap_state))
        {
            return OAL_SUCC;
        }
        /* STA�Ѿ�UP��״̬�£�STA������ */
        if (WLAN_VAP_MODE_BSS_STA == pst_mac_vap->en_vap_mode)
        {
            ul_rx_filter_val = g_ast_multi_staup_sta_rx_filter[pst_mac_vap->en_vap_state];
        }
        else if (WLAN_VAP_MODE_BSS_AP == pst_mac_vap->en_vap_mode)
        {
            ul_rx_filter_val = g_ast_multi_staup_ap_rx_filter[pst_mac_vap->en_vap_state];
        }
        else
        {
            return OAL_SUCC;
        }
    }
    else
    {
        /* û���κ��豸����UP״̬������VAP���� */
        ul_rx_filter_val = g_ast_single_vap_rx_filter[pst_mac_vap->en_vap_mode][pst_mac_vap->en_vap_state];
    }

     /* ���¼���DMAC, �����¼��ڴ� */
    pst_event_mem = FRW_EVENT_ALLOC(OAL_SIZEOF(oal_uint32));
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{hmac_set_rx_filter_value::pst_event_mem null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��д�¼� */
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;

    FRW_EVENT_HDR_INIT(&(pst_event->st_event_hdr),
                    FRW_EVENT_TYPE_WLAN_CTX,
                    DMAC_WLAN_CTX_EVENT_SUB_TYPE_SET_RX_FILTER,
                    OAL_SIZEOF(oal_uint32),
                    FRW_EVENT_PIPELINE_STAGE_1,
                    pst_mac_vap->uc_chip_id,
                    pst_mac_vap->uc_device_id,
                    pst_mac_vap->uc_vap_id);

#ifdef _PRE_WLAN_FEATURE_HILINK
    /* ���hilink fbt scan���ؿ�������Ҫ����������BSS������֡�����hilink fbt
       scan���عرգ�����Ҫ���д�������BSS ��������֡����Ϊbit 11��0--����BSS
       ��������֡�����ˣ�1--����BSS ��������֡���� */
    if (OAL_TRUE == pst_mac_device->st_fbt_scan_mgmt.uc_fbt_scan_enable)
    {
        ul_rx_filter_val &= ~0x800;
    }
#endif
    /* �������� */
    oal_memcopy(pst_event->auc_event_data, (oal_void *)&ul_rx_filter_val, OAL_SIZEOF(oal_uint32));

    /* �ַ��¼� */
    ul_ret = frw_event_dispatch_event(pst_event_mem);
    if (OAL_SUCC != ul_ret)
    {
        FRW_EVENT_FREE(pst_event_mem);
        return OAL_FAIL;
    }

    FRW_EVENT_FREE(pst_event_mem);

#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_rx_filter_init_normal
 ��������  : ֡���˸�״ֵ̬��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_filter_init_single_vap(oal_void)
{
    oal_uint32  ul_state;
    oal_uint32  ul_vap_mode;

    /*       DTS2015102202934    ���� FCS ERROR ����            */
    for (ul_vap_mode = WLAN_VAP_MODE_CONFIG; ul_vap_mode < WLAN_VAP_MODE_BUTT; ul_vap_mode++)
    {
        for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
        {
            g_ast_single_vap_rx_filter[ul_vap_mode][ul_state] = (1<<21);
        }
    }

    /*            WLAN_VAP_MODE_CONFIG, ����ģʽ                */
    /* +---------------------------+--------------------------+ */
    /* | FSM State                 | RX FILTER VALUE          | */
    /* +---------------------------+--------------------------+ */
    /* | All states                | 0x37BDEEFA               | */
    /* +---------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_CONFIG][ul_state] = 0x37B9EEFA;
    }

    /* WLAN_VAP_MODE_BSS_STA          BSS STAģʽ                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0x37BDEEFA               | */
    /* | MAC_VAP_STATE_UP                 | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_STA_FAKE_UP        | 0x37BDEEFA               | */
    /* | MAC_VAP_STATE_STA_WAIT_SCAN      | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_SCAN_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_JOIN      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_JOIN_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2 | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4 | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_AUTH_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_ASOC      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_OBSS_SCAN      | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_BG_SCAN        | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_LISTEN         | 0x33A9EECA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = (1<<21);
    }

    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_INIT]             = 0xF7B9EEFA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_FAKE_UP]      = 0xF7B9EEFA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_UP]               = 0x73B9EADA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_PAUSE]            = 0x73B9EADA;

    for (ul_state = MAC_VAP_STATE_STA_SCAN_COMP; ul_state <= MAC_VAP_STATE_STA_WAIT_ASOC; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = 0x73B9EADA;
    }

    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_WAIT_SCAN]    = 0x37B9CECA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_OBSS_SCAN]    = 0x37B9CEEA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_BG_SCAN]      = 0x37B9CEEA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_LISTEN]       = 0x33A9EECA;

#ifdef _PRE_WLAN_FEATURE_ROAM
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_ROAMING]          = 0x73B9EADA;
#endif

    /* WLAN_VAP_MODE_BSS_AP                BSS APģʽ                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0xF7B9EEFA               | */
    /* | MAC_VAP_STATE_UP                 | 0x73B9EAEA               | */
    /* | MAC_VAP_STATE_PAUSE              | 0x73B9EAEA               | */
    /* | MAC_VAP_STATE_AP_WAIT_START      | 0x73B9EAEA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][ul_state] = (1<<21);
    }

    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_INIT]             = 0xF7B9EEFA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_UP]               = 0x73B9EAEA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_PAUSE]            = 0x73B9EAEA;
    g_ast_single_vap_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_AP_WAIT_START]    = 0x73B9CAEA;

    /* WLAN_VAP_MODE_MONITOER                ����ģʽ                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | all status                       | 0x1                      | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_single_vap_rx_filter[WLAN_VAP_MODE_MONITOER][ul_state] = 0x1 | (1<<21);
    }
}

/*****************************************************************************
 �� �� ��  : hmac_rx_filter_init_normal
 ��������  : ֡���˸�״ֵ̬��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_filter_init_multi_vap(oal_uint32 ul_proxysta_enabled)
{
    oal_uint32  ul_state;

    /*       DTS2015102202934    ���� FCS ERROR ����            */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
    {
        g_ast_multi_staup_sta_rx_filter[ul_state] = (1<<21);
        g_ast_multi_apup_sta_rx_filter[ul_state] = (1<<21);
    }
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_AP_STATE_BUTT; ul_state++)
    {
        g_ast_multi_staup_ap_rx_filter[ul_state] = (1<<21);
    }

/*
   proxystaģʽ���ظ�֡���˲��ܿ�����Ϊ51оƬ���⣬�Ѿ���¼��оƬʹ��
   ����֡���˼Ĵ������úͷ�proxystaһ�£�����ֱ�Ӹ��ü��ɣ���ΪӲ���ظ�֡���ز���Ч��51Ŀǰ���
   ʵ�ֵ��ظ�֡�����Ѿ�����PROXYSTA�������
   �������ʵ�ʲ�Ʒ������Ҫ�ϱ��ض�֡��ʱ���������Լ����������á���������������λ������������������ķ�ʽֻ��if 0��
*/
#if 0
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if(ul_proxysta_enabled)
    {
        /* Proxy ARPģʽ�²��ܹ����ظ�֡ */
        /*  ��STAģʽ    WLAN_VAP_MODE_BSS_STA          BSS STAģʽ        */
        /* +----------------------------------+--------------------------+ */
        /* ��AP UPʱ,STA���ó���:  WLAN_VAP_MODE_BSS_STA   BSS STAģʽ     */
        /* +----------------------------------+--------------------------+ */
        /* | FSM State                        | RX FILTER VALUE          | */
        /* +----------------------------------+--------------------------+ */
        /* | ALL STATE                        | 0x33ADEACA               | */
        /* +----------------------------------+--------------------------+ */
        for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
        {
            g_ast_multi_staup_sta_rx_filter[ul_state] = 0x33ADEACA;
            g_ast_multi_apup_sta_rx_filter[ul_state] = 0x33ADEACA;
        }

        /* WLAN_VAP_MODE_BSS_STA               BSS APģʽ                  */
        /* +----------------------------------+--------------------------+ */
        /* | FSM State                        | RX FILTER VALUE          | */
        /* +----------------------------------+--------------------------+ */
        /* | MAC_VAP_STATE_INIT               | 0x37BDEADA               | */
        /* | MAC_VAP_STATE_UP                 | 0x37BDEACA               | */
        /* | MAC_VAP_STATE_PAUSE              | 0                        | */
        /* | MAC_VAP_STATE_AP_WAIT_START      | 0x37BDEADA               | */
        /* | MAC_VAP_STATE_AP_PAUSE           | 0                        | */
        /* +----------------------------------+--------------------------+ */
        for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_AP_STATE_BUTT; ul_state++)
        {
            g_ast_multi_staup_ap_rx_filter[ul_state] = (1<<21);
        }

        g_ast_multi_staup_ap_rx_filter[MAC_VAP_STATE_INIT]             = 0x33B9EADA;
        g_ast_multi_staup_ap_rx_filter[MAC_VAP_STATE_UP]               = 0x33B9EACA;
        g_ast_multi_staup_ap_rx_filter[MAC_VAP_STATE_AP_WAIT_START]    = 0x33B9EACA;
    }
    else
#endif
#endif
    {
        /*  ��STAģʽ    WLAN_VAP_MODE_BSS_STA          BSS STAģʽ        */
        /* +----------------------------------+--------------------------+ */
        /* | FSM State                        | RX FILTER VALUE          | */
        /* +----------------------------------+--------------------------+ */
        /* | MAC_VAP_STATE_STA_WAIT_SCAN      | 0x33B9CACA               | */
        /* | MAC_VAP_STATE_STA_OBSS_SCAN      | 0x33B9CACA               | */
        /* | MAC_VAP_STATE_STA_BG_SCAN        | 0x33B9CACA               | */
        /* | MAC_VAP_STATE_STA_LISTEN         | 0x33A9EACA               | */
        /* | ALL OTHER STATE                  | 0x73B9EADA               | */
        /* +----------------------------------+--------------------------+ */
        for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
        {
            g_ast_multi_staup_sta_rx_filter[ul_state] = 0x73B9EADA;
        }

        g_ast_multi_staup_sta_rx_filter[MAC_VAP_STATE_STA_WAIT_SCAN]    = 0x33B9CACA;
        g_ast_multi_staup_sta_rx_filter[MAC_VAP_STATE_STA_OBSS_SCAN]    = 0x33B9CACA;
        g_ast_multi_staup_sta_rx_filter[MAC_VAP_STATE_STA_BG_SCAN]      = 0x33B9CACA;
        g_ast_multi_staup_sta_rx_filter[MAC_VAP_STATE_STA_LISTEN]       = 0x33A9EACA;


        /* ��AP UPʱ,STA���ó���:  WLAN_VAP_MODE_BSS_STA   BSS STAģʽ     */
        /* +----------------------------------+--------------------------+ */
        /* | FSM State                        | RX FILTER VALUE          | */
        /* +----------------------------------+--------------------------+ */
        /* | MAC_VAP_STATE_INIT               | ����ԭ��ֵ������         | */
        /* | MAC_VAP_STATE_UP                 | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_STA_FAKE_UP        | ����ԭ��ֵ������         | */
        /* | MAC_VAP_STATE_STA_WAIT_SCAN      | 0x33B9CACA               | */
        /* | MAC_VAP_STATE_STA_SCAN_COMP      | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_STA_WAIT_JOIN      | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_STA_JOIN_COMP      | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2 | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4 | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_STA_AUTH_COMP      | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_STA_WAIT_ASOC      | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_STA_OBSS_SCAN      | 0x33B9CACA               | */
        /* | MAC_VAP_STATE_STA_BG_SCAN        | 0x33B9CACA               | */
        /* | MAC_VAP_STATE_STA_LISTEN         | 0x33A9EACA               | */
        /* +----------------------------------+--------------------------+ */
        for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STA_STATE_BUTT; ul_state++)
        {
            g_ast_multi_apup_sta_rx_filter[ul_state] = (1<<21);
        }
        g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_STA_WAIT_SCAN] = 0x33B9CACA;
        g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_STA_OBSS_SCAN] = 0x33B9CACA;
        g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_STA_BG_SCAN]   = 0x33B9CACA;
        g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_STA_LISTEN]    = 0x33A9EACA;
        g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_UP]            = 0x73B9EACA;
#ifdef _PRE_WLAN_FEATURE_ROAM
        g_ast_multi_apup_sta_rx_filter[MAC_VAP_STATE_ROAMING]       = 0x73B9EACA;
#endif
        for (ul_state = MAC_VAP_STATE_STA_SCAN_COMP; ul_state <= MAC_VAP_STATE_STA_WAIT_ASOC; ul_state++)
        {
            g_ast_multi_apup_sta_rx_filter[ul_state] = 0x73B9EACA;
        }

        /* ��STA UPʱ,AP���ó���:  WLAN_VAP_MODE_BSS_AP    BSS APģʽ      */
        /* +----------------------------------+--------------------------+ */
        /* | FSM State                        | RX FILTER VALUE          | */
        /* +----------------------------------+--------------------------+ */
        /* | MAC_VAP_STATE_INIT               | ����ԭ��ֵ������         | */
        /* | MAC_VAP_STATE_UP                 | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_PAUSE              | 0x73B9EACA               | */
        /* | MAC_VAP_STATE_AP_WAIT_START      | 0x73B9EACA               | */
        /* +----------------------------------+--------------------------+ */
        for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_AP_STATE_BUTT; ul_state++)
        {
            g_ast_multi_staup_ap_rx_filter[ul_state] = 0x73B9EACA;
        }

        g_ast_multi_staup_ap_rx_filter[MAC_VAP_STATE_INIT] = (1<<21);
    }
}

#if 0
/*****************************************************************************
 �� �� ��  : hmac_rx_filter_init_repeater
 ��������  : ֡���˸�״ֵ̬��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_filter_init_repeater(oal_void)
{
    oal_uint32  ul_state;

    /* WLAN_VAP_MODE_CONFIG,         ����ģʽ */
    /*                                                          */
    /* +---------------------------+--------------------------+ */
    /* | FSM State                 | RX FILTER VALUE          | */
    /* +---------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT        | 0x37BDEEFA               | */
    /* | All other states          | 0                        | */
    /* +---------------------------+--------------------------+ */
    for (ul_state = 0; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_CONFIG][ul_state] = 0;
    }

    g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_CONFIG][MAC_VAP_STATE_INIT] = 0x37B9EEFA;

    /* WLAN_VAP_MODE_BSS_STA               BSS STAģʽ(Proxy STA)      */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | all status                       | 0x37ADEACA               | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = 0x33ADEACA;
    }

    /* WLAN_VAP_MODE_BSS_STA               BSS APģʽ                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_UP                 | 0x37BDEACA               | */
    /* | MAC_VAP_STATE_PAUSE              | 0                        | */
    /* | MAC_VAP_STATE_AP_WAIT_START      | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_AP_PAUSE           | 0                        | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][ul_state] = 0;
    }

    g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_INIT]             = 0x33B9EADA;
    g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_UP]               = 0x33B9EACA;
    g_ast_repeater_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_AP_WAIT_START]    = 0x33B9EACA;
}

#ifdef _PRE_WLAN_FEATURE_P2P
/*****************************************************************************
 �� �� ��  : hmac_rx_filter_init_p2p
 ��������  : ֡���˸�״ֵ̬��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��29��
    ��    ��   : duankaiyong 00194999
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_filter_init_p2p(oal_void)
{
    oal_uint32  ul_state;

    /* WLAN_VAP_MODE_CONFIG,         ����ģʽ */
    /*                                                          */
    /* +---------------------------+--------------------------+ */
    /* | FSM State                 | RX FILTER VALUE          | */
    /* +---------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT        | 0x37BDEEFA               | */
    /* | All other states          | 0                        | */
    /* +---------------------------+--------------------------+ */
    for (ul_state = 0; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_CONFIG][ul_state] = 0;
    }

    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_CONFIG][MAC_VAP_STATE_INIT] = 0x37B9EEFA;

    /* WLAN_VAP_MODE_BSS_STA               BSS STAģʽ                 */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0x37BDEEFA               | */
    /* | MAC_VAP_STATE_UP                 | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_STA_FAKE_UP        | 0x37BDEEFA               | */
    /* | MAC_VAP_STATE_STA_WAIT_SCAN      | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_SCAN_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_JOIN      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_JOIN_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ2 | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_AUTH_SEQ4 | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_AUTH_COMP      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_WAIT_ASOC      | 0x37BDEEDA               | */
    /* | MAC_VAP_STATE_STA_OBSS_SCAN      | 0x37BDCEEA               | */
    /* | MAC_VAP_STATE_STA_BG_SCAN        | 0x37BDCEEA               | */
    /* +----------------------------------+--------------------------+ */

    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = 0x33ADEEDA;//33BDEECA
    }

    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_INIT]             = 0x37B9EEFA;/* init ״̬������֡ */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_UP]               = 0x33B9EEDA;/* up ״̬�����ձ�bss beacon����������bss beacon */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_FAKE_UP]      = 0x37B9EEFA;/* fake up״̬������֡ */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_WAIT_SCAN]    = 0x37B9CEEA;/* scan ״̬��������beacon֡ */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_LISTEN]       = 0x33ADEECA;/* listen ״̬��������bss �鲥����֡(probe req) */

    for (ul_state = MAC_VAP_STATE_STA_SCAN_COMP; ul_state <= MAC_VAP_STATE_STA_AUTH_COMP; ul_state++)
    {
        g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][ul_state] = 0x37B9EEDA;
    }

    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_WAIT_ASOC] = 0x33B9EEDA;/* �ȴ�����״̬�����ձ�bss beacon����������bss beacon */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_OBSS_SCAN] = 0x37B9CEEA;
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_STA][MAC_VAP_STATE_STA_BG_SCAN]   = 0x37B9CEEA;

    /* WLAN_VAP_MODE_BSS_AP                BSS APģʽ                  */
    /* +----------------------------------+--------------------------+ */
    /* | FSM State                        | RX FILTER VALUE          | */
    /* +----------------------------------+--------------------------+ */
    /* | MAC_VAP_STATE_INIT               | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_UP                 | 0x37BDEACA               | */
    /* | MAC_VAP_STATE_PAUSE              | 0                        | */
    /* | MAC_VAP_STATE_AP_WAIT_START      | 0x37BDEADA               | */
    /* | MAC_VAP_STATE_AP_PAUSE           | 0                        | */
    /* +----------------------------------+--------------------------+ */
    for (ul_state = MAC_VAP_STATE_INIT; ul_state < MAC_VAP_STATE_BUTT; ul_state++)
    {
        g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][ul_state] = 0;
    }

    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_INIT]             = 0x33B9EADA;/* init ״̬����������bss beacon */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_UP]               = 0x33B9EACA;/* UP ״̬TKIP MIC�����֡�������ˣ���ԿѰ��ʧ�ܲ����ˣ�direct����֡����CF_END,BA��RTS,CTS,ACK�������ˣ���bss �鲥֡������ */
    g_ast_p2p_mode_rx_filter[WLAN_VAP_MODE_BSS_AP][MAC_VAP_STATE_AP_WAIT_START]    = 0x33B9EACA;/* UP ״̬TKIP MIC�����֡�������ˣ���ԿѰ��ʧ�ܲ����ˣ�direct����֡����CF_END,BA��RTS,CTS,ACK�������ˣ���bss �鲥֡������ */
}
#endif
#endif
/*****************************************************************************
 �� �� ��  : hmac_rx_filter_init
 ��������  : ֡���˸�״ֵ̬��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_filter_init(oal_void)
{
    g_en_rx_filter_enable = OAL_TRUE;

    /* Normalģʽ֡����ֵ��ʼ�� */
    hmac_rx_filter_init_single_vap();
    hmac_rx_filter_init_multi_vap(OAL_FALSE);

#if 0
    /* Repeaterģʽ֡����ֵ��ʼ�� */
    hmac_rx_filter_init_repeater();

#ifdef _PRE_WLAN_FEATURE_P2P
    /* P2P ģʽ֡����ֵ��ʼ�� */
    hmac_rx_filter_init_p2p();
#endif
#endif
}

/*****************************************************************************
 �� �� ��  : hmac_rx_filter_exit
 ��������  : ֡�����˳�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��14��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_rx_filter_exit(oal_void)
{
    g_en_rx_filter_enable = OAL_FALSE;
}

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : hmac_set_rx_filter_en
 ��������  : hmac����֡����ʹ�ܿ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_set_rx_filter_en(oal_uint8 uc_rx_filter_en)
{
    g_en_rx_filter_enable = uc_rx_filter_en;
}

/*****************************************************************************
 �� �� ��  : hmac_get_rx_filter_en
 ��������  : hmac��ȡ֡����ʹ�ܿ���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hmac_get_rx_filter_en(oal_void)
{
    oal_int8      ac_tmp_buff[200];
    oal_int8     *pac_string[] = {"close", "open", "error"};

    OAL_SPRINTF(ac_tmp_buff, OAL_SIZEOF(ac_tmp_buff), "rx filer function is : %s.\n", pac_string[g_en_rx_filter_enable]);
    oam_print(ac_tmp_buff);
}

/*****************************************************************************
 �� �� ��  : hmac_set_status_rx_filter_val
 ��������  : ����ָ��״̬��֡����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_set_status_rx_filter_val(oal_uint uc_dev_mode, oal_uint uc_vap_mode, oal_uint uc_vap_status, oal_uint32 uc_val)
{
    switch(uc_dev_mode)
    {
        case 0:
            g_ast_single_vap_rx_filter[uc_vap_mode][uc_vap_status] = uc_val;
            break;

        case 1:
            g_ast_multi_staup_sta_rx_filter[uc_vap_status] = uc_val;
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_set_status_rx_filter_val::uc_dev_mode is exceed.[%d]}", uc_dev_mode);
            return OAL_FAIL;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hmac_get_status_rx_filter_val
 ��������  : ��ȡָ��״̬��֡����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hmac_get_status_rx_filter_val(oal_uint uc_dev_mode, oal_uint uc_vap_mode, oal_uint uc_vap_status)
{
    oal_uint32    uc_val = 0;
    oal_int8      ac_tmp_buff[200];
    oal_int8     *pac_vapmode2string[]   = {"CONFIG", "STA", "AP", "WDS", "MONITOER", "TEST", "error"};
    oal_int8     *pac_vapstatus2string[] = {"INIT", "UP", "PAUSE", "WAIT_START", "AP_PAUSE",
                                            "FAKE_UP", "WAIT_SCAN", "SCAN_COMP", "WAIT_JOIN", "JOIN_COMP", "WAIT_AUTH_SEQ2",
                                            "WAIT_AUTH_SEQ4", "AUTH_COMP", "STA_WAIT_ASOC", "STA_OBSS_SCAN", "STA_BG_SCAN", "error"};
    switch(uc_dev_mode)
    {
        case 0:
            uc_val = g_ast_single_vap_rx_filter[uc_vap_mode][uc_vap_status];
            break;

        case 1:
            uc_val = g_ast_multi_staup_sta_rx_filter[uc_vap_status];
            break;

        default:
            OAM_ERROR_LOG1(0, OAM_SF_ANY, "{hmac_get_status_rx_filter_val::uc_dev_mode is exceed.[%d]}", uc_dev_mode);
            return OAL_FAIL;
    }

    OAL_SPRINTF(ac_tmp_buff, OAL_SIZEOF(ac_tmp_buff), "The %s when it is %s status. \r\nThe rx filter value is 0x%08x.\r\n",
                pac_vapmode2string[uc_vap_mode], pac_vapstatus2string[uc_vap_status], uc_val);

    oam_print(ac_tmp_buff);

    return OAL_SUCC;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

