/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_rx_data.c
  �� �� ��   : ����
  ��    ��   : huxiaotong
  ��������   : 2012��11��20��
  ����޸�   :
  ��������   : DMACģ�����֡�Ĺ������������Լ�����֡�Ĳ������������Դ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��20��
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
#include "oal_net.h"
#include "oam_ext_if.h"
#include "oam_main.h"

#include "wlan_spec.h"
#include "wlan_mib.h"

#include "mac_frame.h"
#include "mac_data.h"

#ifdef _PRE_WLAN_DFT_REG
#include "hal_witp_debug.h"
#endif
#include "hal_ext_if.h"
#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE
#include "hal_device.h"
#endif
#include "dmac_device.h"
#include "dmac_resource.h"
#include "dmac_mgmt_classifier.h"
#include "dmac_blockack.h"
#include "dmac_rx_data.h"
#include "dmac_stat.h"
#include "dmac_ext_if.h"

#ifdef _PRE_WLAN_CHIP_TEST
#include "dmac_test_main.h"
#include "dmac_test_sch.h"
#endif
#include "dmac_reset.h"

#ifdef _PRE_WLAN_FEATURE_BTCOEX
#include "dmac_btcoex.h"
#endif

#include "oal_profiling.h"

#include "dmac_dfx.h"
#include "dmac_auto_adjust_freq.h"

#ifdef _PRE_WLAN_SW_CTRL_RSP
#include "dmac_vap.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RX_DATA_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#define MAX_ERR_INFO_LEN 50 /*ָʾ��ӡ�Ĵ�����Ϣ��󳤶�*/

OAL_STATIC oal_uint32 ul_deauth_flow_control_ms = 0;
#define DEAUTH_INTERVAL_MIN 300 /*���Ĺ��˹����У�����ȥ��֤����С��� 300ms*/

#if (!defined(_PRE_PRODUCT_ID_HI110X_DEV))
/* ����֡��FCS��ͳ����Ϣ */
dmac_rx_fcs_statistic g_ast_rx_fcs_statistic[WLAN_VAP_SUPPORT_MAX_NUM_LIMIT] =
{
    {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}
};
#endif

#ifdef _PRE_WLAN_FEATURE_BTCOEX
extern oal_uint32 gul_rx_window_offset;
#endif

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
oal_uint32  dmac_rx_send_event(
                dmac_vap_stru                           *pst_dmac_vap,
                dmac_wlan_crx_event_sub_type_enum_uint8  en_event,
                oal_uint8                               *puc_param,
                oal_uint32                               ul_len);


/*****************************************************************************
 �� �� ��  : dmac_null_fn
 ��������  : �պ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��18��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_null_fn(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    return;
}


/*****************************************************************************
 �� �� ��  : dmac_rx_vap_stat
 ��������  : ͳ�ƽ��յ���msdu�������ֽ������ֽ���������80211ͷ��������snapͷ
             ��������padding
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��21��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifdef _PRE_WLAN_DFT_STAT
OAL_STATIC oal_uint32  dmac_rx_vap_stat(dmac_vap_stru *pst_dmac_vap,
                                            oal_netbuf_head_stru *pst_netbuf_hdr,
                                            oal_netbuf_stru     *pst_buf,
                                            dmac_rx_ctl_stru *pst_rx_cb)
{
    oal_uint32          *pul_mac_hdr;
    oal_uint8            uc_buf_nums;
    oal_netbuf_stru     *pst_buf_next;
    oal_uint8            uc_msdu_nums_in_mpdu = 0;
    oal_uint16           us_bytes;
    mac_rx_ctl_stru     *pst_rx_info = &(pst_rx_cb->st_rx_info);
    mac_ieee80211_frame_stru  *pst_frame_hdr;

    pul_mac_hdr = mac_get_rx_cb_mac_hdr(pst_rx_info);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pul_mac_hdr))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_vap_stat::mac_hdr is null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_frame_hdr  = (mac_ieee80211_frame_stru *)(mac_get_rx_cb_mac_hdr(pst_rx_info));

    if (!pst_rx_info->bit_amsdu_enable)
    {
        /* ��mpduֻ��һ��msdu���ֽ���Ӧ��ȥ��snap���� */
        if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
        {
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_pkts,  1);
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_bytes,
                                    pst_rx_cb->st_rx_info.us_frame_len - pst_rx_cb->st_rx_info.bit_mac_header_len - SNAP_LLC_FRAME_LEN);
#else
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_bytes,
                                    pst_rx_cb->st_rx_info.us_frame_len - pst_rx_cb->st_rx_info.uc_mac_header_len - SNAP_LLC_FRAME_LEN);

#endif
        }
    }
    /* �����mpdu������amsdu����Ҫ��ȡsub_msdu������ÿһ��sub_msdu���ֽ��� */
    else
    {

        for (uc_buf_nums = 0; uc_buf_nums < pst_rx_cb->st_rx_info.bit_buff_nums; uc_buf_nums++)
        {
            pst_buf_next = oal_get_netbuf_next(pst_buf);

            /* ����mpdu��msdu����Ŀ */
            uc_msdu_nums_in_mpdu += pst_rx_cb->st_rx_info.uc_msdu_in_buffer;

            pst_buf = pst_buf_next;
            if ((oal_netbuf_head_stru *)pst_buf == pst_netbuf_hdr)
            {
                break;
            }
            pst_rx_cb = (dmac_rx_ctl_stru *)OAL_NETBUF_CB(pst_buf);
        }
        if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
        {
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_pkts, uc_msdu_nums_in_mpdu);
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
            /* �����mpdu���ֽ���Ŀ������sub_msdt�ֽ���֮�ͣ�������snap��������padding��ע�����һ��sub_msduû��padding */
            us_bytes = pst_rx_cb->st_rx_info.us_frame_len - pst_rx_cb->st_rx_info.bit_mac_header_len
                     - SNAP_LLC_FRAME_LEN * uc_msdu_nums_in_mpdu;
#else
            /* �����mpdu���ֽ���Ŀ������sub_msdt�ֽ���֮�ͣ�������snap��������padding��ע�����һ��sub_msduû��padding */
            us_bytes = pst_rx_cb->st_rx_info.us_frame_len - pst_rx_cb->st_rx_info.uc_mac_header_len
                     - SNAP_LLC_FRAME_LEN * uc_msdu_nums_in_mpdu;

#endif
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_drv_rx_bytes, us_bytes);
        }

    }

    return OAL_SUCC;
}
#endif

 /*****************************************************************************
 �� �� ��  : dmac_rx_check_mgmt_replay_failure
 ��������  : ����Ƿ��ǹ���֡���طŹ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��23��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8  dmac_rx_check_mgmt_replay_failure(dmac_rx_ctl_stru  *pst_cb_ctrl)
{
    mac_ieee80211_frame_stru  *pst_frame_hdr;

    /* ��ȡ802.11ͷָ�� */
    pst_frame_hdr  = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info));

    if (MAC_IEEE80211_FTYPE_MGMT != pst_frame_hdr->st_frame_control.bit_type)
    {
        return OAL_TRUE;
    }

    switch (pst_cb_ctrl->st_rx_status.bit_dscr_status)
    {
        case HAL_RX_CCMP_REPLAY_FAILURE:
        case HAL_RX_TKIP_REPLAY_FAILURE:
        case HAL_RX_BIP_REPLAY_FAILURE:
        {
            return OAL_TRUE;
        }
        default:
        {
            return OAL_FALSE;
        }
    }
}

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif

/*****************************************************************************
 �� �� ��  : hal_rx_update_dscr_queue
 ��������  : �ú������ж��ϱ���������������������������ժ��,���ҽ������������е�
             ��Ϣ�ŵ���Ӧ��netbuf��cb�ֶ��У���netbuf��������黹������
 �������  : (1)���յĶ��е�ͷָ��
             (2)���յĶ��к�
             (3)���յ��ĵ�һ���������ĵ�ַ(����������׵�ַ)
             (4)hal�ṩ��dmac��device��ָ��
             (5)ָ��netbufͷ��ָ��
             (6)�������ĸ���
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_rx_update_dscr_queue(
                hal_to_dmac_device_stru            *pst_device,
                hal_hw_rx_dscr_info_stru           *pst_rx_dscr_info,
                oal_netbuf_head_stru               *pst_netbuf_header,
                oal_uint16                         *pus_pre_dscr_num)
{
    hal_rx_dscr_queue_header_stru  *pst_rx_dscr_queue;
    dmac_rx_ctl_stru               *pst_cb_ctrl;                    /* ��дnetbuf��cb�ֶ�ʹ�� */
    oal_netbuf_stru                *pst_netbuf = OAL_PTR_NULL;      /* ָ��ÿһ����������Ӧ��netbuf */
    oal_uint32                     *pul_curr_dscr;                  /* ���ڴ���������� */
    oal_uint32                     *pul_next_dscr;                  /* ��һ����Ҫ����������� */
    hal_rx_dscr_stru               *pst_hal_to_dmac_dscr;           /* HAL��DMAC�ṩ�Ķ����������ṹ */
    oal_bool_enum_uint8             en_last_int_flag = OAL_FALSE;   /* ����ϱ����жϵı�ʶ OAL_TRUE ����ʼ�������ж�*/
    oal_uint16                      us_dscr_num = pst_rx_dscr_info->us_dscr_num;
    hal_rx_dscr_queue_id_enum_uint8 en_queue_num = pst_rx_dscr_info->uc_queue_id;
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))
    oal_uint8                       *puc_mac_hdr_addr;
    oal_uint8                       *puc_tail;
    oal_uint16                      us_frame_len;
#endif
    oal_uint8                       uc_sub_type;
    oam_sdt_print_beacon_rxdscr_type_enum_uint8           en_beacon_switch;
    oal_uint32                      ul_rx_dscr_len;
    oal_switch_enum_uint8           en_rx_dscr_switch;

    pst_rx_dscr_queue = &(pst_device->ast_rx_dscr_queue[pst_rx_dscr_info->uc_queue_id]);

    pul_curr_dscr = pst_rx_dscr_queue->pul_element_head;

#ifdef _PRE_DEBUG_MODE
    if (pul_curr_dscr != pst_rx_dscr_info->pul_base_dscr)
    {
        pst_device->ul_rx_irq_loss_cnt++;
        OAM_WARNING_LOG1(0, OAM_SF_RX, "{dmac_rx_update_dscr_queue::Losed interrupt[%d].", pst_device->ul_rx_irq_loss_cnt);
    }
#endif

    en_rx_dscr_switch = oam_ota_get_rx_dscr_switch();
    while(OAL_PTR_NULL != pul_curr_dscr)
    {
        /* �ж��Ƿ��Ѿ���ʼ�����жϴ��� */
        if (pul_curr_dscr == pst_rx_dscr_info->pul_base_dscr)
        {
            en_last_int_flag = OAL_TRUE;
        }

        /* ��ȡ��������Ӧ��netbuf */
        hal_rx_get_netbuffer_addr_dscr(pst_device, pul_curr_dscr, &pst_netbuf);

        pst_cb_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

        /* ��ȡ���������ֶ���Ϣ��������ӵ�netbuf��cb�ֶ��� */
        dmac_rx_get_dscr_info(pst_device, pul_curr_dscr, pst_cb_ctrl);

#ifdef _PRE_WLAN_CACHE_COHERENT_SUPPORT
        /* ��Ч��cache�����¶�ȡnetbuf������ */
        oal_dma_map_single(NULL, pst_netbuf->data, pst_cb_ctrl->st_rx_info.us_frame_len, OAL_FROM_DEVICE);
#endif

        /* ��cb�е��ŵ��Ž��и�ֵ */
        pst_cb_ctrl->st_rx_info.uc_channel_number = pst_rx_dscr_info->uc_channel_num;
        /* �����beacon֡�Ľ���������������Ҫ���ݿ�������ϱ� */

        if (OAL_SWITCH_ON == en_rx_dscr_switch)
        {
            uc_sub_type = mac_get_frame_sub_type((oal_uint8 *)mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info)));
            en_beacon_switch = oam_ota_get_beacon_switch();
            hal_rx_get_size_dscr(pst_device, &ul_rx_dscr_len);
            if ((WLAN_FC0_SUBTYPE_BEACON != uc_sub_type)
                || (OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_RXDSCR == en_beacon_switch)
                || (OAM_SDT_PRINT_BEACON_RXDSCR_TYPE_BOTH == en_beacon_switch))
            {
                oam_report_dscr(BROADCAST_MACADDR, (oal_uint8 *)pul_curr_dscr, (oal_uint16)ul_rx_dscr_len, OAM_OTA_TYPE_RX_DSCR);
            }
        }

        if (HAL_RX_NEW == pst_cb_ctrl->st_rx_status.bit_dscr_status)
        {
//#if(_PRE_PRODUCT_ID_HI1102_DEV == _PRE_PRODUCT_ID)
            /*2015/5/9�ѽ��1102 RX NEW ����! z00262551*/
            //OAL_IO_PRINT("RX_NEW!!\r\n");
//#endif
            if (OAL_TRUE == en_last_int_flag)
            {
                /* Ӳ��RX_NEW */
                OAM_ERROR_LOG4(0, OAM_SF_RX, "{dmac_rx_update_dscr_queue::RX_NEW HARDWARE!phy addr=0x%08x,base phy addr=0x%08x,cnt=%d,q=%d.}",
                               OAL_DSCR_VIRT_TO_PHY(HAL_RX_DSCR_GET_REAL_ADDR(pul_curr_dscr)),
                               OAL_DSCR_VIRT_TO_PHY(HAL_RX_DSCR_GET_REAL_ADDR(pst_rx_dscr_info->pul_base_dscr)), us_dscr_num, en_queue_num);
            }
            else
            {
                /* ���RX_NEW */
                OAM_ERROR_LOG4(0, OAM_SF_RX, "{dmac_rx_update_dscr_queue::RX_NEW SOFTWARE!phy addr=0x%08x,base phy addr=0x%08x,cnt=%d,q=%d.}",
                               OAL_DSCR_VIRT_TO_PHY(HAL_RX_DSCR_GET_REAL_ADDR(pul_curr_dscr)),
                               OAL_DSCR_VIRT_TO_PHY(HAL_RX_DSCR_GET_REAL_ADDR(pst_rx_dscr_info->pul_base_dscr)), us_dscr_num, en_queue_num);
#if(defined(_PRE_PRODUCT_ID_HI110X_DEV))
                //return OAL_FAIL;
#else
                return OAL_FAIL;
#endif
            }
#if 0
            pst_hal_to_dmac_dscr = (hal_rx_dscr_stru *)pul_curr_dscr;
            if(NULL != pst_hal_to_dmac_dscr->pul_next_rx_dscr)
                pul_next_dscr = HAL_RX_DSCR_GET_SW_ADDR(oal_get_virt_addr(pst_hal_to_dmac_dscr->pul_next_rx_dscr));
            else
                pul_next_dscr = NULL;
            hal_rx_sync_invalid_dscr(pst_device, pul_curr_dscr, en_queue_num);
            pul_curr_dscr = pul_next_dscr;
            continue;
#endif
        }

#if(defined(_PRE_PRODUCT_ID_HI110X_DEV))
        puc_mac_hdr_addr = oal_netbuf_header(pst_netbuf);
        oal_netbuf_set_len(pst_netbuf, pst_cb_ctrl->st_rx_info.us_frame_len);

        us_frame_len = pst_cb_ctrl->st_rx_info.us_frame_len;
        if (us_frame_len < WLAN_LARGE_NETBUF_SIZE)
        {
            puc_tail = puc_mac_hdr_addr + us_frame_len;
        }
        else
        {
            puc_tail = puc_mac_hdr_addr + WLAN_LARGE_NETBUF_SIZE;
        }
        oal_set_netbuf_tail(pst_netbuf, puc_tail);
#else
        oal_netbuf_trim(pst_netbuf, OAL_NETBUF_LEN(pst_netbuf));
    #ifdef _PRE_WLAN_HW_TEST
        if (HAL_ALWAYS_RX_RESERVED == pst_device->bit_al_rx_flag)          /* ���� */
        {
            if(pst_cb_ctrl->st_rx_info.us_frame_len < HAL_AL_RX_FRAME_LEN)
            {
                oal_netbuf_put(pst_netbuf, pst_cb_ctrl->st_rx_info.us_frame_len);
            }
            else
            {
                oal_netbuf_put(pst_netbuf, HAL_AL_RX_FRAME_LEN);
            }
        }
        else
    #endif
        {
            /* DTS2015060301543,֡������1600ʱ��buf������1600������buf�������֡����ȥ1600 */
            if(pst_cb_ctrl->st_rx_info.us_frame_len < WLAN_LARGE_NETBUF_SIZE)
            {
                oal_netbuf_put(pst_netbuf, pst_cb_ctrl->st_rx_info.us_frame_len);
            }
            else
            {
                oal_netbuf_put(pst_netbuf, WLAN_LARGE_NETBUF_SIZE);
            }
        }
        /*OAL_NETBUF_LEN(pst_netbuf)  = pst_cb_ctrl->st_rx_info.us_frame_len;
        OAL_NETBUF_TAIL(pst_netbuf) = (pst_cb_ctrl->st_rx_info.us_frame_len < WLAN_LARGE_NETBUF_SIZE)
                                       ? (oal_netbuf_data(pst_netbuf) + pst_cb_ctrl->st_rx_info.us_frame_len)
                                       : (oal_netbuf_data(pst_netbuf) + WLAN_LARGE_NETBUF_SIZE);*/
#endif
        /* ���뵽netbuf�������� */
        oal_netbuf_add_to_list_tail(pst_netbuf, pst_netbuf_header);

        /* �����һ����Ҫ����������� */
        pst_hal_to_dmac_dscr = (hal_rx_dscr_stru *)pul_curr_dscr;

        if(NULL != pst_hal_to_dmac_dscr->pul_next_rx_dscr)
        {
            pul_next_dscr = HAL_RX_DSCR_GET_SW_ADDR((oal_uint32*)OAL_DSCR_PHY_TO_VIRT((oal_uint)(pst_hal_to_dmac_dscr->pul_next_rx_dscr)));
        }
        else
        {
            pul_next_dscr = HAL_RX_DSCR_GET_SW_ADDR(pst_hal_to_dmac_dscr->pul_next_rx_dscr);
        }

        if (OAL_TRUE == en_last_int_flag)
        {
            us_dscr_num = OAL_SUB(us_dscr_num, 1);
        }
        else
        {
            (*pus_pre_dscr_num)++;    /* �Ǳ����жϵ��������ĸ�������1 */
        }

        /* 51 ��ʱȡ���ù켣׷��DEBUG */
#if (_PRE_PRODUCT_ID_HI1151 != _PRE_PRODUCT_ID)
    #ifdef _PRE_DEBUG_MODE
        /* ��¼�°벿����������켣 */
        if (OAL_FALSE == pst_device->ul_track_stop_flag)
        {
            pst_device->ul_dpart_save_idx++;
        }

        if (pst_device->ul_dpart_save_idx >= HAL_DOWM_PART_RX_TRACK_MEM)
        {
            pst_device->ul_dpart_save_idx = 0;
        }

        OAL_MEMZERO(&pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx], OAL_SIZEOF(hal_rx_dpart_track_stru));
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_phy_addr = OAL_VIRT_TO_PHY_ADDR(HAL_RX_DSCR_GET_REAL_ADDR(pul_curr_dscr));
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].uc_status   = pst_cb_ctrl->st_rx_status.bit_dscr_status;
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].uc_q        = en_queue_num;
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_timestamp= pul_curr_dscr[HAL_DEBUG_RX_DSCR_LINE];
        pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_irq_cnt  = pst_device->ul_irq_cnt;
        oal_get_cpu_stat(&pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].st_cpu_state);
    #endif
#endif

        OAL_MEM_TRACE(pul_curr_dscr, OAL_FALSE);
        /* �黹������ */
        hal_rx_free_dscr_list(pst_device, en_queue_num, pul_curr_dscr);

        /* �ж��Ƿ������ */
        if (0 == us_dscr_num)
        {
            break;
        }

        pul_curr_dscr = pul_next_dscr;
    }

    return OAL_SUCC;
}
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
/******************************************************************************
 �� �� ��  : dmac_rx_mpdu_filter_duplicate_frame_proxysta
 ��������  : proxysta�ķǾۺ�֡�ظ�֡���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��28��
    ��    ��   : y00184180
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_mpdu_filter_duplicate_frame_proxysta(
                mac_vap_stru               *pst_mac_vap,
                mac_ieee80211_frame_stru   *pst_frame_hdr,
                dmac_rx_ctl_stru           *pst_cb_ctrl)
{
    oal_uint8               uc_tid;
    oal_uint16              us_seq_num;
    oal_bool_enum_uint8     en_is_4addr;
    oal_uint8               uc_is_tods;
    oal_uint8               uc_is_from_ds;
    dmac_vap_stru          *pst_dmac_vap;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (!pst_dmac_vap)
    {
        OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                         "{dmac_rx_mpdu_filter_duplicate_frame_proxysta::null dmac vap, id=%d}",
                         pst_mac_vap->uc_vap_id);
        return OAL_FAIL;
    }
    us_seq_num = mac_get_seq_num((oal_uint8 *)pst_frame_hdr);

    /* �����ĵ�ַ�����ȡ���ĵ�tid */
    uc_is_tods    = mac_hdr_get_to_ds((oal_uint8 *)pst_frame_hdr);
    uc_is_from_ds = mac_hdr_get_from_ds((oal_uint8 *)pst_frame_hdr);
    en_is_4addr   = uc_is_tods && uc_is_from_ds;

    if (0 == pst_frame_hdr->st_frame_control.bit_retry)
    {
        if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
        {
            pst_dmac_vap->st_psta.us_non_qos_seq_num   = us_seq_num;

        }
        else
        {
            uc_tid = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

            pst_dmac_vap->st_psta.aus_last_qos_seq_num[uc_tid] = us_seq_num;
        }

        return OAL_SUCC;
    }

    /* �жϸ�֡�ǲ���qos֡ */
    if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
    {
        if (us_seq_num == pst_dmac_vap->st_psta.us_non_qos_seq_num)
        {
            OAM_WARNING_LOG1(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                             "{dmac_rx_mpdu_filter_duplicate_frame_proxysta::non qos duplicate frame[%d]}",
                             us_seq_num);

            return OAL_FAIL;
        }

        pst_dmac_vap->st_psta.us_non_qos_seq_num = us_seq_num;

        return OAL_SUCC;
    }

    uc_tid = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

    /* qos���� */
    if (us_seq_num == pst_dmac_vap->st_psta.aus_last_qos_seq_num[uc_tid])
    {
        OAM_WARNING_LOG2(pst_mac_vap->uc_vap_id, OAM_SF_RX,
                         "{dmac_rx_mpdu_filter_duplicate_frame_proxysta::tid is[%d],qos duplicate frame[%d]. }",
                         uc_tid,
                         us_seq_num);

        return OAL_FAIL;
    }
    else
    {
        pst_dmac_vap->st_psta.aus_last_qos_seq_num[uc_tid] = us_seq_num;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_rx_data_user_is_null
 ��������  : �յ�����֡�Ҳ����û�ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��29��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_rx_data_user_is_null(mac_vap_stru *pst_mac_vap, mac_ieee80211_frame_stru *pst_frame_hdr)
{
    dmac_vap_stru           *pst_dmac_vap;
    oal_uint32               ul_cur_tick_ms;
    dmac_diasoc_deauth_event st_deauth_evt;

    pst_dmac_vap = mac_res_get_dmac_vap(pst_mac_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG0(pst_mac_vap->uc_vap_id,OAM_SF_PWR,"{dmac_rx_data_user_is_null::mac_res_get_dmac_vap fail}");
        return;
    }

    OAM_STAT_VAP_INCR(pst_mac_vap->uc_vap_id, rx_ta_check_dropped, 1);
    DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ta_check_dropped, 1);

    ul_cur_tick_ms = (oal_uint32)OAL_TIME_GET_STAMP_MS();
    if (ul_cur_tick_ms < ul_deauth_flow_control_ms + DEAUTH_INTERVAL_MIN)
    {
        return;
    }

    ul_deauth_flow_control_ms = ul_cur_tick_ms;

    oal_memcopy(st_deauth_evt.auc_des_addr, pst_frame_hdr->auc_address2, WLAN_MAC_ADDR_LEN);
    st_deauth_evt.uc_reason = MAC_NOT_AUTHED;
    st_deauth_evt.uc_event  = DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH;

    OAM_WARNING_LOG4(pst_mac_vap->uc_vap_id, OAM_SF_RX, "dmac_rx_data_user_is_null: ta: %02X:XX:XX:%02X:%02X:%02X. post sending deauth event to hmac",
                        pst_frame_hdr->auc_address2[0],
                        pst_frame_hdr->auc_address2[3],
                        pst_frame_hdr->auc_address2[4],
                        pst_frame_hdr->auc_address2[5]);

    dmac_rx_send_event(pst_dmac_vap, DMAC_WLAN_CRX_EVENT_SUB_TYPE_DEAUTH, (oal_uint8 *)&st_deauth_evt, OAL_SIZEOF(st_deauth_evt));
}

/*****************************************************************************
 �� �� ��  : dmac_rx_filter_frame_sta
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��13��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
#endif

oal_uint32  dmac_rx_filter_frame_sta(
                mac_vap_stru           *pst_vap,
                dmac_rx_ctl_stru       *pst_cb_ctrl,
                dmac_user_stru             *pst_dmac_user)
{
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    oal_uint32                  ul_ret = OAL_SUCC;
    oal_uint8                  *puc_addr         = OAL_PTR_NULL;

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    mac_device_stru            *pst_dev = mac_res_get_dev(pst_vap->uc_device_id);

    if (!pst_dev)
    {
        return OAL_FAIL;
    }
#endif
    /* ��ȡ�û���֡��Ϣ */
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info));

    if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
    {
        if (OAL_PTR_NULL == pst_dmac_user)
        {
            /* ����OAL_FAIL ��ʾ����֡��Ҫ���� */
            dmac_rx_data_user_is_null(pst_vap, pst_frame_hdr);

            return OAL_FAIL;
        }
        else
        {
            mac_get_transmit_addr(pst_frame_hdr, &puc_addr);
            /* TA���ǷǱ�BSS������֡�����ϱ���ֱ�ӷ���ʧ�ܣ������ͷ��ڴ棬�������ֱ�ӷ��� */
            if (OAL_MEMCMP(pst_dmac_user->st_user_base_info.auc_user_mac_addr, puc_addr, 6))
            {
                return OAL_FAIL;
            }
        }
#ifdef _PRE_WLAN_FEATURE_PROXYSTA
        if (mac_is_proxysta_enabled(pst_dev))
        {
            /* ��AMPDU�ظ�֡���� */
            if (OAL_FALSE == pst_cb_ctrl->st_rx_status.bit_AMPDU)
            {
                 if (mac_vap_is_vsta(pst_vap)) // FIXME:
                 {
                    ul_ret = dmac_rx_mpdu_filter_duplicate_frame_proxysta(pst_vap, pst_frame_hdr, pst_cb_ctrl);
                    if(OAL_SUCC != ul_ret)
                    {
                        return ul_ret;
                    }
                 }
            }
        }
#endif

    #ifdef _PRE_WLAN_FEATURE_AMPDU
        ul_ret = dmac_ba_filter_serv(pst_vap, pst_dmac_user, pst_cb_ctrl, pst_frame_hdr);
    #endif


        /* �����û���RSSIͳ����Ϣ */
        if (OAL_PTR_NULL != pst_dmac_user)
        {
            pst_dmac_user->c_rx_rssi = wlan_rssi_lpf(pst_dmac_user->c_rx_rssi,
                                                                   pst_cb_ctrl->st_rx_statistic.c_rssi_dbm);
        }
    }

    /* ����rx��11nЭ����ص�mib */
    dmac_rx_update_mib_11n(pst_vap, pst_cb_ctrl);

    return ul_ret;
}
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif
#endif

/*****************************************************************************
 �� �� ��  : dmac_mgmt_send_event
 ��������  : DMAC���¼�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��14��
    ��    ��   : z00260280
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_send_event(
                dmac_vap_stru         *pst_dmac_vap,
                dmac_wlan_crx_event_sub_type_enum_uint8 en_event,
                oal_uint8                 *puc_param,
                oal_uint32             ul_len)
{
    frw_event_mem_stru             *pst_event_mem;      /* �����¼����ص��ڴ�ָ�� */
    frw_event_stru                 *pst_hmac_to_dmac_ctx_event;

    pst_event_mem = FRW_EVENT_ALLOC((oal_uint16)ul_len);
    if (OAL_PTR_NULL == pst_event_mem)
    {
        OAM_ERROR_LOG0(pst_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_RX, "{dmac_rx_send_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����¼�ָ�� */
    pst_hmac_to_dmac_ctx_event = (frw_event_stru *)pst_event_mem->puc_data;

    /* ��д�¼�ͷ */
    FRW_EVENT_HDR_INIT(&(pst_hmac_to_dmac_ctx_event->st_event_hdr),
                       FRW_EVENT_TYPE_WLAN_CRX,
                       en_event,
                       (oal_uint16)ul_len,
                       FRW_EVENT_PIPELINE_STAGE_1,
                       pst_dmac_vap->st_vap_base_info.uc_chip_id,
                       pst_dmac_vap->st_vap_base_info.uc_device_id,
                       pst_dmac_vap->st_vap_base_info.uc_vap_id);

    oal_memcopy(pst_hmac_to_dmac_ctx_event->auc_event_data,
                puc_param, ul_len);
    /* �ַ� */
    frw_event_dispatch_event(pst_event_mem);

    /* �ͷ��¼��ڴ� */
    FRW_EVENT_FREE(pst_event_mem);

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_rx_mpdu_filter_duplicate_frame
 ��������  : �Ǿۺ�֡�ظ�֡���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��15��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_mpdu_filter_duplicate_frame(
                dmac_user_stru             *pst_dmac_user,
                mac_ieee80211_frame_stru   *pst_frame_hdr,
                dmac_rx_ctl_stru           *pst_cb_ctrl)
{
    oal_uint8               uc_tid;
    oal_uint16              us_seq_num;
    oal_uint16              us_seq_frag_num;
    oal_bool_enum_uint8     en_is_4addr;
    oal_uint8               uc_is_tods;
    oal_uint8               uc_is_from_ds;

    us_seq_num = mac_get_seq_num((oal_uint8 *)pst_frame_hdr);

    us_seq_frag_num = ((oal_uint16)(pst_frame_hdr->bit_seq_num) << 4) | pst_frame_hdr->bit_frag_num;

    /* �����ĵ�ַ�����ȡ���ĵ�tid */
    uc_is_tods    = mac_hdr_get_to_ds((oal_uint8 *)pst_frame_hdr);
    uc_is_from_ds = mac_hdr_get_from_ds((oal_uint8 *)pst_frame_hdr);
    en_is_4addr   = uc_is_tods && uc_is_from_ds;

    if (0 == pst_frame_hdr->st_frame_control.bit_retry)
    {
        if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
        {
            pst_dmac_user->us_non_qos_seq_frag_num = us_seq_frag_num;
        }
        else
        {
            uc_tid = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

            pst_dmac_user->ast_tx_tid_queue[uc_tid].us_last_seq_frag_num = us_seq_frag_num;
        }

        return OAL_SUCC;
    }

    /* �жϸ�֡�ǲ���qos֡ */
    if ((WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA) != ((oal_uint8 *)pst_frame_hdr)[0])
    {
        if (us_seq_frag_num == pst_dmac_user->us_non_qos_seq_frag_num)
        {
            OAM_WARNING_LOG2(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_RX,
                             "{dmac_rx_ucast_filter_duplicate_frame::non qos duplicate frame[%d], seq_num with frag_num [%d]}",
                             us_seq_num, us_seq_frag_num);

            return OAL_FAIL;
        }

        pst_dmac_user->us_non_qos_seq_frag_num = us_seq_frag_num;

        return OAL_SUCC;
    }

    uc_tid = mac_get_tid_value((oal_uint8 *)pst_frame_hdr, en_is_4addr);

    /* qos���� */
    if (us_seq_frag_num == pst_dmac_user->ast_tx_tid_queue[uc_tid].us_last_seq_frag_num)
    {
        OAM_WARNING_LOG3(pst_dmac_user->st_user_base_info.uc_vap_id, OAM_SF_RX,
                         "{dmac_rx_ucast_filter_duplicate_frame::tid is[%d],qos duplicate frame[%d], seq_num with frag num [%d].}",
                         uc_tid, us_seq_num, us_seq_frag_num);

        return OAL_FAIL;
    }
    else
    {
        pst_dmac_user->ast_tx_tid_queue[uc_tid].us_last_seq_frag_num = us_seq_frag_num;
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_rx_filter_frame_ap
 ��������  : APģʽ�£���MPDU��֡ͷ��Ϣ����
 �������  : (1)ָ���Ӧvap��ָ��
             (2)ָ����տ�����Ϣ�Ľṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_FAIL:  ������Ҫ��������
             OAL_SUCC:  ��������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_rx_filter_frame_ap(
                mac_vap_stru           *pst_vap,
                dmac_rx_ctl_stru       *pst_cb_ctrl)
{
    mac_ieee80211_frame_stru   *pst_frame_hdr;
    dmac_user_stru             *pst_dmac_user;
    oal_uint32                  ul_ret = OAL_SUCC;
    dmac_diasoc_deauth_event    st_disasoc_evt;
    oal_uint32                  ul_len = 0;
    dmac_vap_stru              *pst_dmac_vap;
    oal_uint32                  ul_cur_tick_ms = 0;

    /* ��ȡ�û���֡��Ϣ */
    pst_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(MAC_GET_RX_CB_TA_USER_IDX(&(pst_cb_ctrl->st_rx_info)));
    pst_frame_hdr = (mac_ieee80211_frame_stru *)(mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info)));
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);

    if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
    {
        if (OAL_PTR_NULL == pst_dmac_user)  /* �û������� */
        {
            /* ����OAL_FAIL ��ʾ����֡��Ҫ���� */
            dmac_rx_data_user_is_null(pst_vap, pst_frame_hdr);

            return OAL_FAIL;
        }

        if(MAC_USER_STATE_ASSOC != pst_dmac_user->st_user_base_info.en_user_asoc_state)/* �û�δ���� */
        {
            /* ����OAL_FAIL ��ʾ����֡��Ҫ���� */
            OAM_WARNING_LOG2(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_frame_ap::status is not assoc,user index:%d,en_user_asoc_state:%d}",
                             pst_dmac_user->st_user_base_info.us_assoc_id,
                             pst_dmac_user->st_user_base_info.en_user_asoc_state);

            OAM_WARNING_LOG4(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_filter_frame_ap::user mac:%02X:XX:XX:%02X:%02X:%02X}",
                             pst_dmac_user->st_user_base_info.auc_user_mac_addr[0],
                             pst_dmac_user->st_user_base_info.auc_user_mac_addr[3],
                             pst_dmac_user->st_user_base_info.auc_user_mac_addr[4],
                             pst_dmac_user->st_user_base_info.auc_user_mac_addr[5]);

            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_ta_check_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ta_check_dropped, 1);

            ul_cur_tick_ms = (oal_uint32)OAL_TIME_GET_STAMP_MS();
            if (ul_cur_tick_ms < ul_deauth_flow_control_ms + DEAUTH_INTERVAL_MIN)
            {
                return OAL_FAIL;
            }

            ul_deauth_flow_control_ms = ul_cur_tick_ms;
            oal_memcopy(st_disasoc_evt.auc_des_addr, pst_frame_hdr->auc_address2, WLAN_MAC_ADDR_LEN);
            st_disasoc_evt.uc_reason = MAC_NOT_ASSOCED;
            st_disasoc_evt.uc_event  = DMAC_WLAN_CRX_EVENT_SUB_TYPE_DISASSOC;
            ul_len = OAL_SIZEOF(st_disasoc_evt);

            dmac_rx_send_event(pst_dmac_vap, DMAC_WLAN_CRX_EVENT_SUB_TYPE_DISASSOC, (oal_uint8 *)&st_disasoc_evt, ul_len);
            return OAL_FAIL;
        }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        /* ��AMPDU�ظ�֡���� */
        if (OAL_FALSE == pst_cb_ctrl->st_rx_status.bit_AMPDU)
        {
            ul_ret = dmac_rx_mpdu_filter_duplicate_frame(pst_dmac_user, pst_frame_hdr, pst_cb_ctrl);
            if(OAL_SUCC != ul_ret)
            {
                return ul_ret;
            }
        }
#endif

    #ifdef _PRE_WLAN_FEATURE_AMPDU
        ul_ret = dmac_ba_filter_serv(pst_vap, pst_dmac_user, pst_cb_ctrl, pst_frame_hdr);
    #endif

        /* �����û���RSSIͳ����Ϣ */
        pst_dmac_user->c_rx_rssi = wlan_rssi_lpf(pst_dmac_user->c_rx_rssi,
                                                 pst_cb_ctrl->st_rx_statistic.c_rssi_dbm);
    }
    else
    {

    }

    /* ����rx��11nЭ����ص�mib */
    dmac_rx_update_mib_11n(pst_vap, pst_cb_ctrl);

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : dmac_rx_get_vap
 ��������  : ��ȡÿһ��MPDU�Ķ�Ӧ��VAP
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��31��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_rx_get_vap(hal_to_dmac_device_stru *pst_hal_device, oal_uint8 uc_hal_vap_id, oal_uint8 uc_rx_queue_id, mac_vap_stru **pst_vap)
{
    hal_to_dmac_vap_stru       *pst_hal_vap  = OAL_PTR_NULL;
    oal_uint8                   uc_mac_vap_id;

#if (defined _PRE_WLAN_FEATURE_DBAC) || (defined _PRE_WLAN_FEATURE_PROXYSTA) || (defined _PRE_WLAN_DFT_STAT)
    mac_device_stru            *pst_device;

    pst_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_get_vap::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }
#endif

#ifdef _PRE_WLAN_DFT_STAT
    if ((WLAN_HAL_OTHER_BSS_UCAST_ID == uc_hal_vap_id)
        && (OAL_TRUE == pst_device->st_dbb_env_param_ctx.en_non_directed_frame_stat_flg))
    {
        pst_device->st_dbb_env_param_ctx.ul_non_directed_frame_num++;
    }
#endif

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if (mac_is_proxysta_enabled(pst_device))
    {
        /* �������Proxy STA���ԣ���hal_vap_id�ĺϷ���ΧΪ0~4,16~31 */
        if (uc_hal_vap_id > WLAN_PROXY_STA_END_ID)
        {
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }
    else
#endif
    {
        if (uc_hal_vap_id > WLAN_HAL_OHTER_BSS_ID)
        {
            return OAL_ERR_CODE_ARRAY_OVERFLOW;
        }
    }

#ifdef _PRE_WLAN_FEATURE_PROXYSTA
    if ((mac_is_proxysta_enabled(pst_device) && ((uc_hal_vap_id < WLAN_HAL_OHTER_BSS_ID)||((uc_hal_vap_id >= WLAN_PROXY_STA_START_ID) && (uc_hal_vap_id <= WLAN_PROXY_STA_END_ID))))
        || (!mac_is_proxysta_enabled(pst_device) && (uc_hal_vap_id < WLAN_HAL_OHTER_BSS_ID)))
#else
    if (uc_hal_vap_id < WLAN_HAL_OHTER_BSS_ID)
#endif
     /* ͨ��hal�ӿڻ�ȡmac��vap id */
    {
        hal_get_hal_vap(pst_hal_device, uc_hal_vap_id, &pst_hal_vap);
        if (OAL_PTR_NULL == pst_hal_vap)
        {
            *pst_vap = OAL_PTR_NULL;
            return OAL_ERR_CODE_PTR_NULL;
        }

        uc_mac_vap_id = pst_hal_vap->uc_mac_vap_id;
    }
    else    /* �㲥֡ʹ������vap���в��� */
    {
        uc_mac_vap_id = 0;

        /* ����BSS�Ĺ㲥����ֱ֡�ӹ��˵� */
        if (HAL_RX_DSCR_NORMAL_PRI_QUEUE == uc_rx_queue_id)
        {
            OAM_WARNING_LOG0(0, OAM_SF_PROXYSTA, "{dmac_rx_get_vap::broadcast packets from other bss, should be filtered}");
            return OAL_FAIL;
        }
    }

    *pst_vap = (mac_vap_stru *)mac_res_get_dmac_vap(uc_mac_vap_id);
    if (OAL_PTR_NULL == *pst_vap)
    {
        OAM_ERROR_LOG0(uc_mac_vap_id, OAM_SF_RX, "{dmac_rx_get_vap::pst_vap null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

#ifdef _PRE_WLAN_HW_TEST
    if (HAL_ALWAYS_RX_DISABLE == pst_hal_device->bit_al_rx_flag)
#endif
    {
        /* ����֡����£��ж�VAP�Ƿ��Ѿ�UP */
        if (((*pst_vap)->en_vap_state != MAC_VAP_STATE_UP) && (HAL_RX_DSCR_NORMAL_PRI_QUEUE == uc_rx_queue_id))
        {
            if ((*pst_vap)->en_vap_state == MAC_VAP_STATE_PAUSE
            #ifdef _PRE_WLAN_FEATURE_ROAM
                || (*pst_vap)->en_vap_state == MAC_VAP_STATE_ROAMING
            #endif //_PRE_WLAN_FEATURE_ROAM
                )
            {
                return OAL_SUCC;
            }

            OAM_WARNING_LOG2(uc_mac_vap_id, OAM_SF_RX, "{dmac_rx_get_vap::the vap is not up! en_dscr_queue_id=%d en_vap_state=%d.",
                             uc_rx_queue_id, (*pst_vap)->en_vap_state);
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)

            /* ����ͳ�� */
            (*pst_vap)->st_vap_stats.ul_rx_vap_non_up_dropped++;
#endif
            return OAL_FAIL;
        }
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_rx_process_dscr
 ��������  : �ú���������������ͬ����ժ����Ҫ����������������ں���
 �������  : (1)ָ����ն���ָ��
             (2)�����Ķ��к���
             (3)������Ϣ�ṹ��ָ��
             (4)hal�ṩ��dmac��device��ָ��
             (5)ָ�򷢸�hmac��netbuf��ָ��
 �������  : ��������Ŀ
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif

OAL_STATIC oal_uint32  dmac_rx_get_dscr_list(
                hal_to_dmac_device_stru        *pst_device,
                hal_hw_rx_dscr_info_stru       *pst_rx_isr_info,
                frw_event_stru                 *pst_event,
                oal_netbuf_head_stru           *pst_netbuf_header)
{
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    mac_vap_stru           *pst_vap;
#endif
    oal_uint8               uc_vap_id;
    oal_uint8               uc_rx_dscr_status;      /* ���յ���������״̬ */
    oal_netbuf_stru        *pst_netbuf;
    oal_uint16              us_pre_dscr_num = 0;    /* �����쳣�ж�δ������������ĸ��� */
    oal_uint32              ul_ret;

    hal_wlan_rx_event_stru *pst_wlan_rx_event = (hal_wlan_rx_event_stru *)(pst_event->auc_event_data);
    uc_vap_id = pst_event->st_event_hdr.uc_vap_id;

    /* ���ж��ϱ��������������ӽ��ն�����ժ�� */
    ul_ret = dmac_rx_update_dscr_queue(pst_device, pst_rx_isr_info, pst_netbuf_header, &us_pre_dscr_num);
    if (OAL_SUCC != ul_ret)
    {
        /* DTS2015042305849,�������RX NEWʱ������Ҫ��֤pst_wlan_rx_event��num������buf��������buf����һ�£�����uc_pre_dscr_num��Ϊus_pre_dscr_num */
#if(defined(_PRE_PRODUCT_ID_HI110X_DEV))
        //pst_wlan_rx_event->us_dscr_num += us_pre_dscr_num;
#else
        pst_wlan_rx_event->us_dscr_num += us_pre_dscr_num;
#endif
        OAM_WARNING_LOG1(uc_vap_id, OAM_SF_RX, "{dmac_rx_get_dscr_list::dmac_rx_update_dscr_queue failed[%d].", ul_ret);
        return OAL_FAIL;
    }

    if(oal_netbuf_list_empty(pst_netbuf_header))
    {
        if(pst_rx_isr_info->us_dscr_num)
        {
            OAL_IO_PRINT("[ERROR]did not found netbuf but us_dscr_num is %d\r\n", pst_rx_isr_info->us_dscr_num);
        }
        return OAL_SUCC;
    }

    /* �����쳣�������ĸ������ø�������dmac_rx_update_dscr_queue�����н���ͳ�� */
    pst_wlan_rx_event->us_dscr_num += us_pre_dscr_num;

    /* ��ȡ���յ��ĵ�һ����������״̬ */
    uc_rx_dscr_status = ((dmac_rx_ctl_stru *)(oal_netbuf_cb(oal_netbuf_peek(pst_netbuf_header))))->st_rx_status.bit_dscr_status;

    /* �������쳣:���������������쳣 */
    if (OAL_UNLIKELY(HAL_RX_NEW == uc_rx_dscr_status))
    {
        OAM_WARNING_LOG0(uc_vap_id, OAM_SF_RX, "{dmac_rx_get_dscr_list::the rx_state of the base dscr is HAL_RX_NEW.}");

        pst_netbuf = oal_netbuf_peek(pst_netbuf_header);
        dmac_rx_free_netbuf_list(pst_netbuf_header, &pst_netbuf, pst_wlan_rx_event->us_dscr_num);
#if(_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
        pst_vap = (mac_vap_stru *)mac_res_get_dmac_vap(uc_vap_id);
        if (OAL_PTR_NULL != pst_vap)
        {
           /* ����ͳ�� */
            pst_vap->st_vap_stats.ul_rx_first_dscr_excp_dropped += pst_wlan_rx_event->us_dscr_num;
        }
#endif
        return OAL_FAIL;
    }

    return OAL_SUCC;
}
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

/*****************************************************************************
 �� �� ��  : dmac_rx_process_data_event
 ��������  : DMACģ���£�������յ�֡���¼�����ں�������������֡������֡
             �������������
 �������  : ָ���¼��ṹ���ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
#endif

oal_void  dmac_rx_process_data_mgmt_event(frw_event_mem_stru *pst_event_mem,
                                       oal_netbuf_head_stru  *pst_netbuf_header,
                                       mac_vap_stru          *pst_vap,
                                       oal_netbuf_stru       *pst_netbuf)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    hal_wlan_rx_event_stru             *pst_wlan_rx_event;
    hal_to_dmac_device_stru            *pst_device;
    dmac_wlan_drx_event_stru           *pst_wlan_rx;
    oal_uint32                          ul_rslt;
    oal_netbuf_stru                    *pst_first_buf = OAL_PTR_NULL;
    dmac_vap_stru                      *pst_dmac_vap;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_vap))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_mgmt_event::pst_vap null.}");

        pst_first_buf = oal_netbuf_peek(pst_netbuf_header);

        /* �쳣 �ͷ���Դ */
        dmac_rx_free_netbuf_list(pst_netbuf_header, &pst_first_buf, (oal_uint16)oal_netbuf_get_buf_num(pst_netbuf_header));

        return;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    /* ��ȡ�¼�ͷ���¼��ṹ��ָ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_wlan_rx_event       = (hal_wlan_rx_event_stru *)(pst_event->auc_event_data);
    pst_device              = pst_wlan_rx_event->pst_hal_device;

    /* DMAC�׵�HMAC��VAP ID�ı������VAP��ID */
    pst_event_hdr->uc_vap_id = pst_vap->uc_vap_id;

    /* ����֡���� */
    if (FRW_EVENT_TYPE_WLAN_DRX == pst_event_hdr->en_type)
    {
        //if (0 == pst_vap->uc_vap_id || WLAN_VAP_MAX_NUM_PER_DEVICE_LIMIT < pst_vap->uc_vap_id)
        /* ˫оƬ�£�0��1��������vap id�����������Ҫ����ҵ��vap ��ʵid���������vap mac numֵ�����ж� */
        if (WLAN_SERVICE_VAP_START_ID_PER_BOARD > pst_vap->uc_vap_id || WLAN_VAP_SUPPORT_MAX_NUM_LIMIT < pst_vap->uc_vap_id)
        {
            OAM_ERROR_LOG1(0, OAM_SF_RX, "{dmac_rx_process_data_mgmt_event::pst_event_mem vap[%d].}", pst_vap->uc_vap_id);
        }

        /* �����һ��NETBUF�ÿ� */
        oal_set_netbuf_next((oal_netbuf_tail(pst_netbuf_header)), OAL_PTR_NULL);

        if (WLAN_VAP_MODE_BSS_AP == dmac_vap_get_bss_type(pst_vap))
        {
            /* APģʽ���̳��¼��������޸��¼�ͷ */
            FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_AP);
        }
        else if (WLAN_VAP_MODE_BSS_STA== dmac_vap_get_bss_type(pst_vap))
        {
            /* STAģʽ���̳��¼��������޸��¼�ͷ */
            FRW_EVENT_HDR_MODIFY_PIPELINE_AND_SUBTYPE(pst_event_hdr, DMAC_WLAN_DRX_EVENT_SUB_TYPE_RX_STA);
        }

        dmac_vap_linkloss_clean(pst_dmac_vap);

        pst_wlan_rx = (dmac_wlan_drx_event_stru *)(pst_event->auc_event_data);
        pst_wlan_rx->pst_netbuf    = oal_netbuf_peek(pst_netbuf_header);
        pst_wlan_rx->us_netbuf_num = (oal_uint16)oal_netbuf_get_buf_num(pst_netbuf_header);

        //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dispatch to hmac.}\r\n");
        /* ����ppsͳ�� */
        dmac_auto_freq_pps_count(pst_wlan_rx->us_netbuf_num);
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PREPARE_EVENT);

        /* �ַ��¼� */
        ul_rslt = frw_event_dispatch_event(pst_event_mem);
        if(ul_rslt != OAL_SUCC)
        {
             OAM_ERROR_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_mgmt_event::frw_event_dispatch_event fail[%d].}", ul_rslt);
             dmac_rx_free_netbuf_list(pst_netbuf_header, &pst_first_buf, (oal_uint16)oal_netbuf_get_buf_num(pst_netbuf_header));
        }


        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_END);
#ifdef _PRE_WLAN_PROFLING_MIPS
        oal_profiling_stop_rx_save();
#endif
    }
    else    /* ����֡�Ĵ��� */
    {
        /* �˴�while����:�������֡���ж� */
        while (OAL_FALSE == oal_netbuf_list_empty(pst_netbuf_header))
        {
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_mgmt_mpdu_num_cnt, 1);
            pst_netbuf = oal_netbuf_delist(pst_netbuf_header);
            if (OAL_PTR_NULL == pst_netbuf)
            {
                OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_mgmt_event::pst_netbuf null.}");
                return;
            }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);
#endif
            /* ���ù���֡�ӿ� */
            ul_rslt = dmac_rx_process_mgmt(pst_event_mem, pst_event_hdr, pst_device, pst_netbuf);
            if (ul_rslt != OAL_SUCC)
            {
//                OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dmac_rx_process_mgmt failed[%d].", ul_rslt);
                OAL_IO_PRINT("\r\n dmac_rx_process_data_event::dmac_rx_process_mgmt failed[%d].\r\n", ul_rslt);
                oal_netbuf_free(pst_netbuf);
                DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_mgmt_abnormal_dropped, 1);
            }
        }
    }

}
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif
#endif

/*****************************************************************************
 �� �� ��  : dmac_rx_compare_frame_type_and_rx_queue
 ��������  : �Ƚ�֡��������ն��к�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��22��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_compare_frametype_and_rxq(
                oal_uint8                           uc_frametype,
                hal_rx_dscr_queue_id_enum_uint8     en_q,
                dmac_rx_ctl_stru                   *pst_cb_ctrl,
                oal_netbuf_stru                    *pst_curr_netbuf)
#else
OAL_STATIC OAL_INLINE oal_uint32  dmac_rx_compare_frametype_and_rxq(
                oal_uint8                           uc_frametype,
                hal_rx_dscr_queue_id_enum_uint8     en_q)
#endif
{
#ifdef _PRE_WLAN_DFT_DUMP_FRAME
    oal_uint8                    *puc_payload;
    mac_ieee80211_frame_stru     *pst_frame_hdr;
#endif

    /* ����֡ �ϱ��Ķ����Ǹ����ȼ����У��쳣 */
    if (WLAN_FC0_TYPE_DATA == uc_frametype && HAL_RX_DSCR_HIGH_PRI_QUEUE == en_q)
    {
        OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_compare_frametype_and_rxq::data frame, but hi rx q.}");
    }
    else if (WLAN_FC0_TYPE_DATA != uc_frametype && HAL_RX_DSCR_NORMAL_PRI_QUEUE == en_q)
    {
        OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_compare_frametype_and_rxq::mgmt frame, but normal rx q.}");
    }
    else
    {
        return OAL_SUCC;
    }

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
    puc_payload = MAC_GET_RX_PAYLOAD_ADDR(&(pst_cb_ctrl->st_rx_info), pst_curr_netbuf);
    pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info));

    if (OAL_SWITCH_ON == oam_report_data_get_global_switch(OAM_OTA_FRAME_DIRECTION_TYPE_TX))
    {
        oam_report_80211_frame(BROADCAST_MACADDR,
                               (oal_uint8 *)(pst_frame_hdr),
                               MAC_GET_RX_CB_MAC_HEADER_LEN(&(pst_cb_ctrl->st_rx_info)),
                               puc_payload,
                               pst_cb_ctrl->st_rx_info.us_frame_len,
                               OAM_OTA_FRAME_DIRECTION_TYPE_TX);

        if (OAL_SUCC != oam_report_netbuf_cb(BROADCAST_MACADDR, (oal_uint8 *)pst_cb_ctrl, OAM_OTA_TYPE_RX_DMAC_CB))
        {
            OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_compare_frametype_and_rxq::oam_report_netbuf_cb return err: 0x%x.}\r\n");
            return OAL_FAIL;
        }
    }
#endif

    return OAL_FAIL;
}


#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_check_vip_frame
 ��������  : �ж� rx �ؼ�֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��20��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_bool_enum_uint8 dmac_check_arp_req_owner(oal_netbuf_stru *pst_netbuf, oal_uint8 uc_vap_id, oal_uint8 uc_data_type)
{
#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    dmac_vap_stru         *pst_dmac_vap;
    mac_llc_snap_stru     *pst_rx_snap;
    oal_eth_arphdr_stru   *pst_rx_arp_hdr;
#endif

    /*DTS2016012000293 ����APת���� arpˢ�����࣬���˳��Լ���arp */
    if (uc_data_type != MAC_DATA_ARP_REQ)
    {
        return OAL_FALSE;
    }

#ifdef _PRE_WLAN_FEATURE_ARP_OFFLOAD
    pst_rx_snap = (mac_llc_snap_stru *)oal_netbuf_payload(pst_netbuf);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_rx_snap))
    {
        OAM_ERROR_LOG0(uc_vap_id, OAM_SF_RX, "{dmac_check_arp_req_owner::Get netbuf snap payload failed.}");
        return OAL_FALSE;
    }

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_RX, "{dmac_check_arp_req_owner::pst_dmac_vap[%d] null.}", uc_vap_id);
        return OAL_FALSE;
    }

    pst_rx_arp_hdr = (oal_eth_arphdr_stru *)(pst_rx_snap + 1);
    return dmac_ao_is_ipv4_addr_owner(pst_dmac_vap, pst_rx_arp_hdr->auc_ar_tip);
#else
    /* dmac��δ����IP��ַ�������ж�arp֡�Ƿ������Լ� */
    return OAL_FALSE;
#endif
}
#endif /*(_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)*/

#ifdef _PRE_WLAN_FEATURE_HILINK
/*****************************************************************************
 �� �� ��  : dmac_fbt_scan_rx_process_frame
 ��������  : FBT�����ʼɨ��
 �������  : pst_hmac_vap: HMAC VAP
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��22��
    ��    ��   : luolingzhi 00225940
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_uint32  dmac_fbt_scan_rx_process_frame(hal_to_dmac_device_stru *pst_hal_device, dmac_rx_ctl_stru *pst_cb_ctrl)
{
    mac_ieee80211_frame_stru           *pst_frame_hdr;
    oal_uint8                          *puc_transmit_addr;
    oal_uint8                          *puc_dest_addr;
    oal_uint8                          *puc_bssid_addr;
    oal_uint8                           uc_user_index;
    oal_uint8                           uc_rssi_index;
    mac_fbt_scan_mgmt_stru             *pst_fbt_scan_mgmt;
    mac_fbt_scan_result_stru           *pst_fbt_scan_result;
    mac_device_stru                    *pst_mac_device;
    oal_uint8                           auc_bssid[WLAN_MAC_ADDR_LEN];  /* sta������ap mac��ַ */

    /* ��ȡdevcie����ʵ�� */
    pst_mac_device = mac_res_get_dev(pst_hal_device->uc_mac_device_id);
    if (OAL_PTR_NULL == pst_mac_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_fbt_scan_rx_process_frame::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    if (OAL_PTR_NULL == pst_cb_ctrl)
    {
        OAM_ERROR_LOG0(pst_mac_device->uc_device_id, OAM_SF_RX, "{dmac_fbt_scan_rx_process_frame::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }


    /* ���fbt scan����û�п�����ֱ�ӷ��� */
    if (OAL_FALSE == pst_mac_device->st_fbt_scan_mgmt.uc_fbt_scan_enable)
    {
        return OAL_FAIL;
    }

    /* ��ȡ802.11ͷָ�롢���Ͷ˵�ַ */
    pst_frame_hdr     = (mac_ieee80211_frame_stru *)(mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info)));
    puc_transmit_addr = pst_frame_hdr->auc_address2;
    puc_dest_addr     = pst_frame_hdr->auc_address1;

    if (ETHER_IS_MULTICAST(puc_transmit_addr))
    {
        return OAL_FAIL;
    }

    if (OAL_TRUE == ETHER_IS_MULTICAST(puc_dest_addr))
    {
        return OAL_FAIL;
    }

    /* ��ȡmac vapʵ���е�fbt����ʵ�� */
    pst_fbt_scan_mgmt = &(pst_mac_device->st_fbt_scan_mgmt);

    /* �����sta����FBT scan�û������б��ڣ�Ҳֱ�ӷ��أ���������*/
    for (uc_user_index = 0; uc_user_index < HMAC_FBT_MAX_USER_NUM; uc_user_index++)
    {
        if (OAL_FALSE == (pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_index].uc_is_used))
        {
            continue;
        }

        if (OAL_SUCC == oal_compare_mac_addr(pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_index].auc_user_mac_addr, puc_transmit_addr))
        {
            break;
        }
    }

    if (HMAC_FBT_MAX_USER_NUM == uc_user_index)
    {
        return OAL_SUCC;
    }

    OAM_INFO_LOG4(pst_mac_device->uc_device_id, OAM_SF_HILINK, "{dmac_fbt_scan_rx_process_frame::uc_user_index = %d,puc_transmit_addr MAC[%x:%x:%x].}",
                                  uc_user_index,
                                  *(puc_transmit_addr+3),
                                  *(puc_transmit_addr+4),
                                  *(puc_transmit_addr+5));


    /* �ҵ���¼��sta FBT scan�����¼ʵ�� */
    pst_fbt_scan_result = &(pst_fbt_scan_mgmt->ast_fbt_scan_user_list[uc_user_index]);

    /* ��ȡ��sta��bssid */
    mac_get_bssid((oal_uint8 *)pst_frame_hdr, auc_bssid);
    puc_bssid_addr = auc_bssid;

    /*��¼��sta��rssi������Ľ���ʱ����Ȳ���������ǵ�һ���ҵ���������
      ��uc_scan_state״̬�޸�Ϊfound���������ŵ���bssid��rssi������ʱ����������Ӽ�����
      ����������Ѿ�����found״̬�������rssi��ʱ�����������������ŵ���bssid�����б䶯��Ҳ���²���ʾ��*/
    if (OAL_FALSE == pst_fbt_scan_result->uc_is_found)
    {
        pst_fbt_scan_result->uc_is_found = OAL_TRUE;
    }
    else
    {
        if (pst_fbt_scan_result->uc_user_channel != pst_cb_ctrl->st_rx_info.uc_channel_number)
        {
            OAM_WARNING_LOG2(pst_mac_device->uc_device_id, OAM_SF_HILINK, "{dmac_fbt_scan_rx_process_frame::user is in found-state, channel change frome [%d] to [%d].}",
                                  pst_fbt_scan_result->uc_user_channel,
                                  pst_cb_ctrl->st_rx_info.uc_channel_number);
        }

        if (0 != oal_memcmp(pst_fbt_scan_result->auc_user_bssid, puc_bssid_addr, WLAN_MAC_ADDR_LEN))
        {
            OAM_WARNING_LOG4(pst_mac_device->uc_device_id, OAM_SF_HILINK, "{dmac_fbt_scan_rx_process_frame::user is in found-state, bssid change frome [%x:%x] to [%x:%x].}",
                                  pst_fbt_scan_result->auc_user_bssid[4],
                                  pst_fbt_scan_result->auc_user_bssid[5],
                                  auc_bssid[4],
                                  auc_bssid[5]);
        }
    }

    /* �����û����ŵ��ź�bssid */
    pst_fbt_scan_result->uc_user_channel = pst_cb_ctrl->st_rx_info.uc_channel_number;
    oal_memcopy(pst_fbt_scan_result->auc_user_bssid, puc_bssid_addr, WLAN_MAC_ADDR_LEN);

    /* �����û���RSSIͳ����Ϣ */
    pst_fbt_scan_result->c_rssi = wlan_rssi_lpf(pst_fbt_scan_result->c_rssi,
                                         pst_cb_ctrl->st_rx_statistic.c_rssi_dbm);
    pst_fbt_scan_result->ul_rssi_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    pst_fbt_scan_result->ul_total_pkt_cnt++;

    OAM_INFO_LOG4(pst_mac_device->uc_device_id, OAM_SF_HILINK, "{dmac_fbt_scan_rx_process_frame::chan = %d,frame bssid MAC[%x:%x:%x].}",
                                                    pst_cb_ctrl->st_rx_info.uc_channel_number,
                                                    *(puc_bssid_addr+3),
                                                    *(puc_bssid_addr+4),
                                                    *(puc_bssid_addr+5));

    OAM_INFO_LOG4(pst_mac_device->uc_device_id, OAM_SF_HILINK, "{dmac_fbt_scan_rx_process_frame::new rssi = %d pkt_cnt=%d bssid[%x:%x].}",
                                                    pst_cb_ctrl->st_rx_statistic.c_rssi_dbm,
                                                    pst_fbt_scan_result->ul_total_pkt_cnt,
                                                    pst_fbt_scan_result->auc_user_bssid[4],
                                                    pst_fbt_scan_result->auc_user_bssid[5]);
    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_rx_process_data_event
 ��������  : DMACģ���£�������յ�֡���¼�����ں�������������֡������֡
 �������  : ָ���¼��ṹ���ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��ԭ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
#endif

#ifdef _PRE_WLAN_SW_CTRL_RSP
/*****************************************************************************
 �� �� ��  : dmac_rx_set_rsp_rate_by_mgmt
 ��������  : ���ݽ��չ���֡����������Ӧ֡���ʣ�2.4G-->1M, 5G-->6M
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��1��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_rx_set_rsp_rate_by_mgmt(dmac_rx_ctl_stru    *pst_cb_ctrl)
{
    mac_vap_stru                    *pst_mac_vap = OAL_PTR_NULL;
    dmac_device_stru                *pst_dmac_dev = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_cb_ctrl)
    {
        OAM_WARNING_LOG0(0, OAM_SF_RX, "{pst_cb_ctrl is NULL, fail to set rsp frm datarate}");
        return;
    }

    pst_mac_vap = mac_res_get_mac_vap(pst_cb_ctrl->st_rx_info.uc_mac_vap_id);
    if (OAL_PTR_NULL == pst_mac_vap)
    {
        OAM_WARNING_LOG1(0, OAM_SF_RX, "{pst_mac_vap is NULL, fail to set rsp frm datarate, vap id[%d]}", pst_cb_ctrl->st_rx_info.uc_mac_vap_id);
        return;
    }

    pst_dmac_dev = dmac_res_get_mac_dev(pst_mac_vap->uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_dev)
    {
        OAM_WARNING_LOG1(0, OAM_SF_RX, "{pst_dmac_dev is NULL, fail to set rsp frm datarate, dev id[%d]}", pst_mac_vap->uc_device_id);
        return;
    }

    hal_cfg_rsp_dyn_bw(OAL_TRUE, pst_dmac_dev->en_usr_bw_mode);
    if (WLAN_PHY_RATE_6M != pst_dmac_dev->uc_rsp_frm_rate_val)
    {
        pst_dmac_dev->uc_rsp_frm_rate_val = WLAN_PHY_RATE_6M;
        hal_set_rsp_rate((oal_uint32)pst_dmac_dev->uc_rsp_frm_rate_val);
    }
}

/*****************************************************************************
 �� �� ��  : dmac_rx_set_rsp_rate
 ��������  : ���ݽ���֡����������Ӧ֡���ʣ�2.4G-->1M, 5G-->6M
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��1��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_rx_set_rsp_rate(oal_uint8 uc_device_id, dmac_rx_ctl_stru    *pst_cb_ctrl, frw_event_type_enum_uint8 en_type)
{
    dmac_device_stru                   *pst_dmac_dev = OAL_PTR_NULL;

    if (OAL_PTR_NULL == pst_cb_ctrl)
    {
        return;
    }

    pst_dmac_dev = dmac_res_get_mac_dev(uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_dev)
    {
        OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_rx_set_rsp_rate::pst_dmac_dev null.dev id [%d]}", uc_device_id);
        return;
    }

    /* �����˶�̬����ʱ�����ݽ����������ʵ�����Ӧ֡���� */
    if (OAL_TRUE == pst_dmac_dev->en_state_in_sw_ctrl_mode)
    {
        if (FRW_EVENT_TYPE_WLAN_DRX == en_type)
        {
            dmac_vap_update_rsp_frm_rate(pst_cb_ctrl->st_rx_info.uc_mac_vap_id,
                                        pst_cb_ctrl->st_rx_statistic.un_nss_rate.st_vht_nss_mcs.bit_protocol_mode,
                                        pst_cb_ctrl->st_rx_statistic.uc_bandwidth,
                                        pst_cb_ctrl->st_rx_statistic.un_nss_rate.st_vht_nss_mcs.bit_vht_mcs);
        }
        else if (FRW_EVENT_TYPE_WLAN_CRX == en_type)
        {
            dmac_rx_set_rsp_rate_by_mgmt(pst_cb_ctrl);
        }
    }
}

#endif

oal_uint32  dmac_rx_process_data_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    frw_event_hdr_stru                 *pst_event_hdr;
    hal_wlan_rx_event_stru             *pst_wlan_rx_event;
    hal_to_dmac_device_stru            *pst_device;
    oal_uint16                          us_dscr_num;                    /* �洢�ж����������������� */
    oal_netbuf_head_stru                st_netbuf_header;               /* �洢����HMACģ��sk_buf�����headerָ�� */
    oal_netbuf_stru                    *pst_curr_netbuf;                /* �洢���ڴ����SK_BUF */
    dmac_rx_ctl_stru                   *pst_cb_ctrl;                    /* ָ��SK_BUF��cb�ֶε�ָ�� */
    mac_vap_stru                       *pst_vap          = OAL_PTR_NULL;
    oal_uint8                           uc_vap_id        = 0xFF;        /* ���汾�δ����VAP ID */
    dmac_rx_frame_ctrl_enum_uint8       en_frame_ctrl    = DMAC_RX_FRAME_CTRL_BUTT;
    oal_uint32                          ul_netbuf_index;
    oal_netbuf_stru                    *pst_netbuf = OAL_PTR_NULL;
    hal_rx_dscr_queue_id_enum_uint8     en_dscr_queue_id;
    oal_uint32                          ul_rslt;
    oal_uint8                           uc_frame_type;
    oal_dlist_head_stru                *pst_rx_isr_list;
    hal_hw_rx_dscr_info_stru           *pst_rx_isr_info;
    mac_ieee80211_frame_stru           *pst_frame_hdr;
    dmac_vap_stru                      *pst_dmac_vap;
    oal_uint8                           uc_data_type;
    mac_rx_ctl_stru                     *pst_rx_info;
#ifdef _PRE_WLAN_FEATURE_DBAC
    mac_device_stru                    *pst_mac_device;
#endif

    /* 51 ��ʱȡ���ù켣׷��DEBUG, wwx293928 */
#if (_PRE_PRODUCT_ID_HI1151 != _PRE_PRODUCT_ID)
#ifdef _PRE_DEBUG_MODE
    oal_uint32                          ul_profingling_time1;
    oal_uint32                          ul_profingling_time2;

    ul_profingling_time1 = oal_5115timer_get_10ns();
#endif
#endif

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_DMAC_START);
    //OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_START);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼�ͷ���¼��ṹ��ָ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_event_hdr           = &(pst_event->st_event_hdr);
    pst_wlan_rx_event       = (hal_wlan_rx_event_stru *)(pst_event->auc_event_data);
    pst_device              = pst_wlan_rx_event->pst_hal_device;

    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_event::pst_device null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*����ģʽ����, ����Ӱ��51���� */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#ifdef _PRE_WLAN_FEATURE_ALWAYS_TX
    if((HAL_ALWAYS_RX_DISABLE != pst_device->bit_al_rx_flag))
    {
        OAM_WARNING_LOG0(0, OAM_SF_RX, "{dmac_rx_process_data_event:: always rx data process already done in isr.}");
        return OAL_SUCC;
    }
#endif
#endif

    /* ��ȡ���������¼�RX QUEUE ID */
    en_dscr_queue_id = (FRW_EVENT_TYPE_WLAN_DRX == pst_event_hdr->en_type) ? HAL_RX_DSCR_NORMAL_PRI_QUEUE : HAL_RX_DSCR_HIGH_PRI_QUEUE;

    /* ��ʼ��netbuf�����ͷ */
    oal_netbuf_list_head_init(&st_netbuf_header);

    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_event_hdr->uc_vap_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
    {
        OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::pst_dmac_vap null.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����֡ʹ���������������ƹ�Ҳ��� */
    if (FRW_EVENT_TYPE_WLAN_DRX == pst_event_hdr->en_type)
    {

        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_START);

        pst_wlan_rx_event->us_dscr_num = 0;

        /*�л�Ping-pong����ʱ��Ҫ��סMac rx�ж�*/
        dmac_rx_pingpong_list_lock(pst_device);
        /* ��ȡ��Ҫ��������� */
        pst_rx_isr_list = &(pst_device->ast_rx_isr_info_list[pst_device->uc_current_rx_list_index]);

        /* �������洢�����ж���Ϣ������ */
        pst_device->uc_current_rx_list_index = (pst_device->uc_current_rx_list_index + 1) & HAL_HW_MAX_RX_DSCR_LIST_IDX;

        dmac_rx_pingpong_list_unlock(pst_device);
        while (!oal_dlist_is_empty(pst_rx_isr_list))
        {
            pst_rx_isr_info = (hal_hw_rx_dscr_info_stru *)oal_dlist_delete_head(pst_rx_isr_list);

            /* ���±����ж���Ҫ���������������Ϣ */
            //pst_wlan_rx_event->pul_base_dscr = pst_rx_isr_info->pul_base_dscr;
            pst_wlan_rx_event->us_dscr_num  += pst_rx_isr_info->us_dscr_num;
            OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_GET_INTR_INFO_FROM_LIST);

            /* ����Ҫ�������������������������ժȡ���������ҽ��������黹������������ */
            ul_rslt = dmac_rx_get_dscr_list(pst_device,
                                            pst_rx_isr_info,
                                            pst_event,
                                            &st_netbuf_header);
            OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_GET_DSCR_AND_RET_BACK);

            /* �ͷű����������Ľڵ���Ϣ */
            hal_free_rx_isr_info(pst_device, pst_rx_isr_info);

            if (oal_netbuf_list_empty(&st_netbuf_header) && (OAL_SUCC != ul_rslt))
            {
                /* �ͷ������������ڵ���Ϣ */
                hal_free_rx_isr_list(pst_device, pst_rx_isr_list);
                OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_ppdu_dropped, 1);
                DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ppdu_dropped, 1);

                return ul_rslt;
            }
        }
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_INTR_LIST_OVER);

    }
    else
    {
        hal_hw_rx_dscr_info_stru    st_rx_isr_info;
        st_rx_isr_info.uc_queue_id    = en_dscr_queue_id;
        st_rx_isr_info.uc_channel_num = pst_wlan_rx_event->uc_channel_num;
        st_rx_isr_info.us_dscr_num    = pst_wlan_rx_event->us_dscr_num;
        st_rx_isr_info.pul_base_dscr  = pst_wlan_rx_event->pul_base_dscr;

        /* ����Ҫ�������������������������ժȡ���������ҽ��������黹������������ */
        ul_rslt = dmac_rx_get_dscr_list(pst_device, &st_rx_isr_info, pst_event, &st_netbuf_header);
        if (oal_netbuf_list_empty(&st_netbuf_header) && (OAL_SUCC != ul_rslt))
        {
            OAM_ERROR_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dmac_rx_get_dscr_list failed[%d].}", ul_rslt);

            OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_ppdu_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ppdu_dropped, 1);
            return ul_rslt;
        }
    }

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_DMAC_GET_CB_LIST);
    //OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_GET_CB_LIST);

    /* ���½��յ��������ĸ�������dmac_rx_get_dscr_list�����У��жԶ��жϵĴ��� */
    us_dscr_num = pst_wlan_rx_event->us_dscr_num;

    /* ѭ������ÿһ��MPDU */
    while (0 != us_dscr_num)
    {
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_START);
        pst_curr_netbuf = oal_netbuf_peek(&st_netbuf_header);
        if (OAL_PTR_NULL == pst_curr_netbuf)
        {
            OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::pst_curr_netbuf null.}");

            OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_abnormal_cnt, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);
            break;
        }

        OAL_MEM_NETBUF_TRACE(pst_curr_netbuf, OAL_TRUE);

        /* ��ȡÿһ��MPDU�Ŀ�����Ϣ */
        pst_cb_ctrl = (dmac_rx_ctl_stru*)oal_netbuf_cb(pst_curr_netbuf);

        pst_rx_info = &(pst_cb_ctrl->st_rx_info);

#ifdef _PRE_WLAN_SW_CTRL_RSP
        dmac_rx_set_rsp_rate(pst_device->uc_device_id, pst_cb_ctrl, pst_event_hdr->en_type);
#endif /* _PRE_WLAN_SW_CTRL_RSP */

        /* Ӳ���ϱ���NUM RX buffers for current MPDU����0���쳣���� */
        if (0 == pst_rx_info->bit_buff_nums)
        {
            /* �ͷź������е�netbuf */
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, us_dscr_num);
            OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_abnormal_cnt, 1);

            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);

            OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event:: 0 == pst_cb_ctrl->st_rx_info.bit_buff_nums");
            break;
        }

        /* Ӳ���ϱ���RX Frame Length���ȵ��쳣���� */
        if (OAL_FALSE == pst_rx_info->bit_amsdu_enable)
        {
        #ifdef _PRE_WLAN_HW_TEST
            /* ����������������Ϊ��� */
            if (HAL_ALWAYS_RX_RESERVED == pst_device->bit_al_rx_flag)
            {
                if (pst_rx_info->us_frame_len > HAL_AL_RX_FRAME_LEN)
                {
                    /* �ͷŵ�ǰMPDU���ڴ� */
                    us_dscr_num -= pst_cb_ctrl->st_rx_info.bit_buff_nums;
                    OAM_ERROR_LOG2(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::non_amsdu mpdu \
                                   too long! mpdu_len=[%d], mpdu_len_limit=[%d].}", pst_rx_info->us_frame_len,
                                   HAL_AL_RX_FRAME_LEN);

                    dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
                    DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);

                    continue;
                }
            }
            else
        #endif
            {
                if (pst_rx_info->us_frame_len > WLAN_MAX_NETBUF_SIZE)
                {
                    /* �ͷŵ�ǰMPDU���ڴ� */
                    us_dscr_num -= pst_cb_ctrl->st_rx_info.bit_buff_nums;
                    OAM_ERROR_LOG2(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::non_amsdu mpdu \
                                   too long! mpdu_len=[%d], mpdu_len_limit=[%d].}", pst_rx_info->us_frame_len,
                                   WLAN_MAX_NETBUF_SIZE);

                    dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
                    DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);

                    continue;
                }
            }
        }

    #ifdef _PRE_WLAN_HW_TEST
        if (HAL_ALWAYS_RX_DISABLE == pst_device->bit_al_rx_flag)
    #endif
        {
            /* FCS�����֡ Ӳ������Ľ��������������壬��һʱ��drop */
            if (HAL_RX_FCS_ERROR == pst_cb_ctrl->st_rx_status.bit_dscr_status)
            {
                /* �ͷŵ�ǰMPDU���ڴ� */
                us_dscr_num -= pst_rx_info->bit_buff_nums;
                OAM_ERROR_LOG0(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event:: HAL_RX_FCS_ERROR == pst_cb_ctrl->st_rx_status.bit_dscr_status");
                dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);

                continue;
            }
        }

        pst_frame_hdr = (mac_ieee80211_frame_stru *)mac_get_rx_cb_mac_hdr(pst_rx_info);
        uc_frame_type = mac_get_frame_type((oal_uint8 *)pst_frame_hdr);

#ifdef _PRE_WLAN_DFT_DUMP_FRAME
        ul_rslt = dmac_rx_compare_frametype_and_rxq(uc_frame_type, en_dscr_queue_id, pst_cb_ctrl, pst_curr_netbuf);
#else
        ul_rslt = dmac_rx_compare_frametype_and_rxq(uc_frame_type, en_dscr_queue_id);
#endif
        if (OAL_SUCC != ul_rslt)
        {
            /* �ͷŵ�ǰMPDU���ڴ� */
            us_dscr_num -= pst_rx_info->bit_buff_nums;
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event:: dmac_rx_compare_frametype_and_rxq fail[%u]", ul_rslt);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);
            continue;
        }
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_FRAME_RXQ);

        /* �����յ���MPDU�쳣 */
        ul_rslt = dmac_rx_filter_mpdu(pst_cb_ctrl, us_dscr_num);
        if (OAL_SUCC != ul_rslt)
        {
            OAM_WARNING_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dmac_rx_filter_mpdu failed[%d].", ul_rslt);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, us_dscr_num);

            /* �ͷź������е�netbuf */
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, us_dscr_num);
            OAM_STAT_VAP_INCR(pst_event_hdr->uc_vap_id, rx_abnormal_cnt, 1);

            break;
        }
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_CB_CHECK);

    #ifdef _PRE_WLAN_CHIP_TEST_ALG
        dmac_alg_rx_event_notify(uc_vap_id, pst_curr_netbuf, pst_cb_ctrl);
    #endif
        /* �˴���vap idΪhal���vap id */
        uc_vap_id = pst_rx_info->bit_vap_id;

#ifdef _PRE_WLAN_FEATURE_HILINK
        if (WLAN_HAL_OTHER_BSS_UCAST_ID == uc_vap_id)
        {
            dmac_fbt_scan_rx_process_frame(pst_device, pst_cb_ctrl);
        }
#endif
        ul_rslt = dmac_rx_get_vap(pst_device, uc_vap_id, en_dscr_queue_id, &pst_vap);
        if (OAL_SUCC != ul_rslt)
        {
            //OAM_INFO_LOG1(pst_event_hdr->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_data_event::dmac_rx_get_vap ul_rslt=%d.}", ul_rslt);

            /* �ͷŵ�ǰMPDUռ�õ�netbuf */
            us_dscr_num -= pst_rx_info->bit_buff_nums;
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
            OAM_STAT_VAP_INCR(0, rx_abnormal_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_abnormal_dropped, 1);
            continue;
        }

        if (WLAN_DATA_BASICTYPE == mac_frame_get_type_value((oal_uint8 *)pst_frame_hdr) &&
             WLAN_NULL_FRAME    != mac_frame_get_subtype_value((oal_uint8 *)pst_frame_hdr))
        {

            /* ά�⣬���һ���ؼ�֡��ӡ. DBAC�����±���յ�VIP֡ */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
            uc_data_type = mac_get_data_type_from_80211(pst_curr_netbuf, pst_rx_info->uc_mac_header_len);
            if(MAC_DATA_DHCP == uc_data_type || MAC_DATA_EAPOL == uc_data_type) /* 51 arp̫֡����������ˢ����ӡ��wapi֡��ʱ������ */
#else
            uc_data_type = mac_get_data_type(pst_curr_netbuf);
            if(((uc_data_type <= MAC_DATA_VIP) && (uc_data_type != MAC_DATA_ARP_REQ)) ||
            (OAL_TRUE == dmac_check_arp_req_owner(pst_curr_netbuf, pst_vap->uc_vap_id, uc_data_type)))  /* arp_req���Ϊת��֡������������־ˢ�� */
#endif
            {
                OAM_WARNING_LOG4(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_rx_process_data_event::rx datatype=%u, len=%u}[0:dhcp 1:arp_req 2:arp_rsp 3:eapol] from XX:XX:XX:XX:%x:%x",uc_data_type, pst_cb_ctrl->st_rx_info.us_frame_len, pst_frame_hdr->auc_address2[4], pst_frame_hdr->auc_address2[5]);
                if((MAC_DATA_EAPOL == uc_data_type) && (OAL_EAPOL_TYPE_KEY == mac_get_eapol_type(pst_curr_netbuf)))
                {
                    /*lint -e666*/
                    OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_rx_process_data_event::rx eapol, info is %x }", OAL_NET2HOST_SHORT(mac_get_eapol_keyinfo(pst_curr_netbuf)));
                    /*lint +e666*/
                }
            }
#ifdef _PRE_WLAN_FEATURE_DBAC
            pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
            if( pst_mac_device != OAL_PTR_NULL)
            {
#if defined(_PRE_WLAN_FEATURE_DBAC) && defined(_PRE_PRODUCT_ID_HI110X_DEV)
                /* VIP֡�Ż���Ҫ�����STAģʽ��1151 DBAC����Ҫ */
                if (mac_is_dbac_running(pst_mac_device) &&
                    (pst_device->uc_current_chan_number == pst_vap->st_channel.uc_chan_number) &&
                    (MAC_DATA_DHCP == uc_data_type || MAC_DATA_EAPOL == uc_data_type))
                {
                    pst_mac_device->en_dbac_has_vip_frame = OAL_TRUE;
                }
#endif
            } // ( pst_mac_device != OAL_PTR_NULL)
#endif // _PRE_WLAN_FEATURE_DBAC
#ifdef _PRE_WLAN_FEATURE_BTCOEX
            dmac_btcoex_release_rx_prot(pst_vap, uc_data_type);
#endif
        }

        /* ��¼��cb�� */
        pst_rx_info->uc_mac_vap_id = pst_vap->uc_vap_id;
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_GET_VAP_ID);

#ifdef _PRE_WLAN_DFT_DUMP_FRAME

        /* DTS2015072003017ά�⣬������Ӳ��Beacon Interval�Ĵ���ֵΪ0��Ӳ������Beacon֡���ֵΪ0 */
        /* �������Beacon֡�е�Beacon Interval��Ϊ0ʱ��һ��ERROR�� ���ⵥ�رպ��ɾ����ά�� */
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
        {
            oal_uint8   uc_sub_type;
            oal_uint8  *puc_frame_body;
            oal_uint16 *pus_bi;

            uc_sub_type = mac_get_frame_sub_type((oal_uint8 *)mac_get_rx_cb_mac_hdr(pst_rx_info));
            puc_frame_body = oal_netbuf_payload(pst_curr_netbuf);
            pus_bi = (oal_uint16 *)(puc_frame_body + 8); /* ƫ��8�ֽ�tsf����beacon interval */

            if ((WLAN_FC0_SUBTYPE_BEACON == uc_sub_type || WLAN_FC0_SUBTYPE_PROBE_RSP == uc_sub_type)
                 && (0 == *pus_bi))
            {
                OAM_WARNING_LOG1(0, OAM_SF_ANY, "dmac_rx_set_rsp_rate::rx beacon/probe rsp Beacon Interval:%d", *pus_bi);
            }
        }
#else /* APģʽ�´˴����յ��ܶ಻�����Լ��Ĺ㲥֡��02����֡ά�ⲻ���ڴ˴� */
        /* �ϱ�֡��֡��Ӧ��CB�ֶε�SDT */
        if ((FRW_EVENT_TYPE_WLAN_DRX != pst_event_hdr->en_type)||
            (OAL_SWITCH_ON == oam_report_data_get_global_switch(OAM_OTA_FRAME_DIRECTION_TYPE_RX)))
        {
            if (pst_cb_ctrl->st_rx_status.bit_dscr_status == HAL_RX_SUCCESS)
            {
                mac_rx_report_80211_frame((oal_uint8 *)pst_vap, (oal_uint8 *)(pst_rx_info), pst_curr_netbuf, OAM_OTA_TYPE_RX_DMAC_CB);
            }
        }
#endif /* #if defined(_PRE_PRODUCT_ID_HI110X_DEV) */
#endif /* #ifdef _PRE_WLAN_DFT_DUMP_FRAME */

        /* �ŵ�����λ��ͳ�� */
        //dmac_rx_vap_stat(pst_vap, &st_netbuf_header, pst_curr_netbuf, pst_cb_ctrl);

        en_frame_ctrl = dmac_rx_process_frame(pst_vap, pst_cb_ctrl, pst_curr_netbuf, &st_netbuf_header);

        if (DMAC_RX_FRAME_CTRL_DROP == en_frame_ctrl)
        {
            /* �ͷŵ�ǰMPDU���ڴ� */
            us_dscr_num -= pst_rx_info->bit_buff_nums;
            dmac_rx_free_netbuf_list(&st_netbuf_header, &pst_curr_netbuf, pst_rx_info->bit_buff_nums);
            DMAC_VAP_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_dropped_misc, 1);
            continue;
        }
        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_OVER);

#ifdef _PRE_WLAN_PERFORM_STAT
        /* ���½�������ͳ���� */
        dmac_stat_rx_thrpt(pst_event_hdr, pst_vap, pst_cb_ctrl);
#endif
#ifdef _PRE_WLAN_FEATURE_BTCOEX
        if ((WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
            && (OAL_TRUE == pst_cb_ctrl->st_rx_status.bit_AMPDU))
        {
            dmac_btcoex_bt_low_rate_process(pst_vap, pst_device);
        }
        if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
        {
            dmac_btcoex_sco_rx_rate_process(pst_vap, pst_device);
        }
#endif

#ifdef _PRE_WLAN_CHIP_TEST

        DMAC_CHIP_TEST_CALL(dmac_test_sch_stat_rx_mpdu_num(pst_event_hdr, pst_vap, pst_cb_ctrl));

        DMAC_CHIP_TEST_CALL(dmac_test_sch_stat_rx_sta_num(pst_event_hdr, pst_vap, pst_cb_ctrl));

#endif

        /* ����֡�Ӷ���ͷժ�������뵽����β������HMAC���� */
        for (ul_netbuf_index = pst_rx_info->bit_buff_nums; ul_netbuf_index > 0; ul_netbuf_index--)
        {
            pst_netbuf = oal_netbuf_delist(&st_netbuf_header);

            OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_FALSE);
            oal_netbuf_add_to_list_tail(pst_netbuf, &st_netbuf_header);
        }

        /* ����δ������������ĸ��� */
        us_dscr_num     -= pst_rx_info->bit_buff_nums;

        /* ͳ�ƽ��յ�MPDU���� */
        dmac_rx_update_aggr_mib(pst_vap, 1);

        OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_MAKE_NETBUF_LIST);
    }

    //OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_DMAC_HANDLE_MPDU);
    //OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_MPDU);

    if (OAL_FALSE == oal_netbuf_list_empty(&st_netbuf_header))
    {
        dmac_rx_process_data_mgmt_event(pst_event_mem, &st_netbuf_header, pst_vap, pst_netbuf);
    }

    OAM_PROFILING_RX_STATISTIC(OAM_PROFILING_FUNC_RX_DMAC_END);
    //OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_END);

    /* 51 ��ʱȡ���ù켣׷��DEBUG */
#if (_PRE_PRODUCT_ID_HI1151 != _PRE_PRODUCT_ID)
#ifdef _PRE_DEBUG_MODE
    ul_profingling_time2 = oal_5115timer_get_10ns();

    pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_arrive_time = ul_profingling_time1;
    pst_device->ast_dpart_track[pst_device->ul_dpart_save_idx].ul_handle_time = ul_profingling_time1 - ul_profingling_time2;
#endif
#endif
    return OAL_SUCC;
}

#ifndef _PRE_WLAN_PROFLING_MIPS
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif
#endif

#if 0
/*****************************************************************************
 �� �� ��  : dmac_error_irq_resume_dscr_queue
 ��������  : �����������д�NULL״̬�ָ�������״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��27��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void dmac_error_irq_resume_dscr_queue(
                hal_error_irq_event_stru           *pst_error_irq_event,
                hal_rx_dscr_queue_id_enum_uint8     en_queue_num)
{
    hal_to_dmac_device_stru            *pst_hal_device;
    oal_uint16                          us_netbuf_free_cnt;     /* netbuf�ڴ�صĿ���netbuf����Ŀ */
    oal_uint16                          us_dscr_free_cnt;       /* �����������ڴ���п��е��������ĸ��� */
    oal_uint16                          us_actual_free_cnt;     /* ����netbuf��dscr�Ľ�С��ֵ */
    oal_uint16                          us_curr_dscr_num;       /* ��ǰ���������ĸ��� */
    oal_uint16                          us_target_num;          /* ʵ�ʿ��Բ�����������ĸ��� */

    pst_hal_device = pst_error_irq_event->pst_hal_device;

    /* ��ͣӲ�� */
    hal_set_machw_tx_suspend(pst_hal_device);

    /* disable PHY and PA */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    oal_mem_get_free_count(OAL_MEM_POOL_ID_NETBUF, 1, &us_netbuf_free_cnt);     /* 1����ڶ����ӳ� */
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
    oal_mem_get_free_count(OAL_MEM_POOL_ID_TX_DSCR_1, 0, &us_dscr_free_cnt);  /* 0�����һ���ӳ� */
#else
    oal_mem_get_free_count(OAL_MEM_POOL_ID_SHARED_DSCR, 0, &us_dscr_free_cnt);  /* 0�����һ���ӳ� */
#endif
    /* ��ȡ�ڴ����Ŀ��и��� */
    us_actual_free_cnt = (us_netbuf_free_cnt > us_dscr_free_cnt) ? us_dscr_free_cnt : us_netbuf_free_cnt;
    if (0 == us_actual_free_cnt)    /* �޿�ʹ�ÿռ� */
    {
        return;
    }

    /* ��ȡ�ܲ�����������ĸ��� */
    us_curr_dscr_num = pst_hal_device->ast_rx_dscr_queue[en_queue_num].us_element_cnt;

    if ((us_actual_free_cnt + us_curr_dscr_num) < HAL_NORMAL_RX_MAX_BUFFS)
    {
        us_target_num = us_actual_free_cnt;
    }
    else
    {
        us_target_num = HAL_NORMAL_RX_MAX_BUFFS - us_curr_dscr_num;
    }

    /* ��������������������� */
    while (0 != us_target_num)
    {
        hal_rx_add_dscr(pst_hal_device, en_queue_num);
        us_target_num--;
    }

    /* enable PHY and PA */
    hal_enable_machw_phy_and_pa(pst_hal_device);

    /* �ָ�Ӳ�� */
    hal_set_machw_tx_resume(pst_hal_device);
}
#endif
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
/*****************************************************************************
 �� �� ��  : dmac_rx_resume_dscr_queue
 ��������  : ����qemty��1102��Ҫ��������������������ԭ�ж��еĺ��棬
             ͬʱ���������������ĵ�һ���Ҹ�mac
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_rx_resume_dscr_queue(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    hal_to_dmac_device_stru        *pst_hal_device;
    frw_event_type_enum_uint8       en_event_type;
    hal_rx_dscr_queue_id_enum_uint8 en_queue_num;
    oal_uint32                      ul_event_succ;
    hal_rx_dscr_queue_header_stru  *pst_rx_dscr_queue;

    pst_hal_device = pst_mac_dev->pst_device_stru;
    if (OAL_PTR_NULL ==  pst_hal_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::pst_hal_device null.}");
        return;
    }

    /* 1.1 ��ȡ��Ҫ�ָ��Ķ��к� */
    en_queue_num = (oal_uint8)ul_param;
    if (en_queue_num >= HAL_RX_QUEUE_NUM)
    {
        OAM_ERROR_LOG1(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::en_queue_num[%d] error.}", en_queue_num);
        return;
    }

    /* 2.1 diable MAC/PHY */
    /*hal_disable_machw_phy_and_pa(pst_hal_device);*/

    /* 3.1 ��ս��ղ����¼� */
    en_event_type = (HAL_RX_DSCR_HIGH_PRI_QUEUE == en_queue_num) ? FRW_EVENT_TYPE_WLAN_CRX : FRW_EVENT_TYPE_WLAN_DRX;
    /* TBD Ŀǰ1102�Ĺ���֡�п��ܱ�mac������ͨ���ȼ��������ϱ������������Ҫ�����������¼�����֮ǰ������Ĺ��˲�����
           �ⲿ���߼���ʱû��ʵ�֣�Ϊ�˷�ֹ4.1����ʱ��headָ�뻹���¼������У����������Ҫ����ͨ���ȼ��¼����м�
           �����ȼ��¼����ж�flush�� */
    ul_event_succ = frw_event_flush_event_queue(en_event_type);

    /* 4.1 ���������������¹Ҹ�mac���������������Ϊ�գ���Ҫ�������� */
    pst_rx_dscr_queue = &(pst_hal_device->ast_rx_dscr_queue[en_queue_num]);
    oal_irq_disable();
    hal_rx_add_dscr(pst_hal_device, en_queue_num, 1);
    /*�ϰ벿���������������üĴ�����ͳһ��Q-EMPTYʱ�������ã���֤Ψһ,���ù����п��Բ���PA*/
    if(0 != pst_rx_dscr_queue->us_element_cnt)
    {
        if(OAL_TRUE != hal_set_machw_rx_buff_addr_sync(pst_hal_device,
                                (oal_uint32)pst_rx_dscr_queue->pul_element_head,
                                en_queue_num))
        {
            /* DTS2015071600780 ����յ���֡��Ӳ�������Ѿ����ߴӶ����ش��󣬲������⡣*/
            OAM_WARNING_LOG1(0, OAM_SF_RX,"[ERROR]Q-EMPTY[%d] but machw reg still not zero!\r\n",en_queue_num);
        }
    }
    else
    {
        OAM_WARNING_LOG1(0, OAM_SF_RX, "{Q-EMPTY[%d] and did not catch any buffs!}",en_queue_num);
    }
    oal_irq_enable();

    OAM_INFO_LOG3(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue[%d]::OK [%u] flushed & [%u] left.}",
                   en_queue_num, ul_event_succ, pst_rx_dscr_queue->us_element_cnt);

    /* 5.1 enable MAC/PHY */
    /*hal_enable_machw_phy_and_pa(pst_hal_device);*/

}
#if 0
/*****************************************************************************
 �� �� ��  : dmac_rx_resume_dscr_queue_all
 ��������  : ����qemty��1102��Ҫ��������������������ԭ�ж��еĺ��棬
             ͬʱ���������������ĵ�һ���Ҹ�mac
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : g00260350
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  dmac_rx_resume_dscr_queue_all(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    dmac_rx_resume_dscr_queue(pst_mac_dev, 0);
    dmac_rx_resume_dscr_queue(pst_mac_dev, 1);
    dmac_rx_resume_dscr_queue(pst_mac_dev, 2);
}
#endif
#else
/*****************************************************************************
 �� �� ��  : dmac_rx_resume_dscr_queue
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��14��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_rx_resume_dscr_queue(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    hal_to_dmac_device_stru        *pst_hal_device;
    hal_rx_dscr_queue_header_stru  *pst_rx_dscr_queue;
    dmac_rx_ctl_stru               *pst_cb_ctrl;                    /* ��дnetbuf��cb�ֶ�ʹ�� */
    oal_netbuf_stru                *pst_netbuf = OAL_PTR_NULL;      /* ָ��ÿһ����������Ӧ��netbuf */
    oal_uint32                     *pul_curr_dscr;                  /* ���ڴ���������� */
    oal_uint32                     *pul_next_dscr;
    hal_rx_dscr_stru               *pst_hal_to_dmac_dscr;
    oal_uint32                      ul_dscr_idx;
    frw_event_type_enum_uint8       en_event_type;
    hal_rx_dscr_queue_id_enum_uint8 en_queue_num;
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV) || defined(_PRE_PRODUCT_ID_HI110X_HOST))
    oal_uint16                      aus_dscr_num[HAL_RX_DSCR_QUEUE_ID_BUTT] = {HAL_NORMAL_RX_MAX_BUFFS, HAL_HIGH_RX_MAX_BUFFS, HAL_SMALL_RX_MAX_BUFFS};
#else
    oal_uint16                      aus_dscr_num[HAL_RX_DSCR_QUEUE_ID_BUTT] = {HAL_NORMAL_RX_MAX_BUFFS, HAL_HIGH_RX_MAX_BUFFS};
#endif
    oal_uint                        ul_irq_flag;
#if 0
    if (0 == pst_mac_dev->uc_resume_qempty_flag)
    {
        /* qempty flag����Ϊ0ʱ����ʹ��qempty�ָ� */
        return;
    }
#endif
    pst_hal_device = pst_mac_dev->pst_device_stru;

    /* ��ȡ��Ҫ�ָ��Ķ��к� */
    en_queue_num = (oal_uint8)ul_param;
    if (en_queue_num >= HAL_RX_QUEUE_NUM)
    {
        OAM_ERROR_LOG1(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::en_queue_num[%d] error.}", en_queue_num);
        return;
    }

    /* diable MAC/PHY */
    hal_disable_machw_phy_and_pa(pst_hal_device);

    /* ��������¼� */
    en_event_type = (HAL_RX_DSCR_NORMAL_PRI_QUEUE == en_queue_num) ? FRW_EVENT_TYPE_WLAN_DRX : FRW_EVENT_TYPE_WLAN_CRX;
    frw_event_flush_event_queue(en_event_type);

    /* ���ն��лָ� */
    pst_rx_dscr_queue = &(pst_hal_device->ast_rx_dscr_queue[en_queue_num]);
    if (OAL_PTR_NULL ==  pst_rx_dscr_queue)
    {
        OAM_ERROR_LOG0(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::pst_rx_dscr_queue null.}");
        return;
    }
    pul_curr_dscr = pst_rx_dscr_queue->pul_element_head;

    oal_irq_disable();
    for (ul_dscr_idx = 0; ul_dscr_idx < aus_dscr_num[en_queue_num]; ul_dscr_idx++)
    {
        if (OAL_PTR_NULL == pul_curr_dscr)
        {
            OAM_ERROR_LOG2(0, OAM_SF_RX, "{dmac_rx_resume_dscr_queue::pul_curr_dscr null, ul_dscr_idx=%d en_queue_num=%d.}",
                           ul_dscr_idx, en_queue_num);
            oal_irq_enable();
            return;
        }

        /* �����һ����Ҫ����������� */
        pst_hal_to_dmac_dscr = (hal_rx_dscr_stru *)pul_curr_dscr;
        if (NULL != pst_hal_to_dmac_dscr->pul_next_rx_dscr)
        {
            pul_next_dscr = HAL_RX_DSCR_GET_SW_ADDR((oal_uint32 *)OAL_DSCR_PHY_TO_VIRT((oal_uint)(pst_hal_to_dmac_dscr->pul_next_rx_dscr)));
        }
        else
        {
            pul_next_dscr = HAL_RX_DSCR_GET_SW_ADDR(pst_hal_to_dmac_dscr->pul_next_rx_dscr);
        }

        /* ��ȡ��������Ӧ��netbuf */
        hal_rx_get_netbuffer_addr_dscr(pst_hal_device, pul_curr_dscr, &pst_netbuf);

        pst_cb_ctrl = (dmac_rx_ctl_stru *)oal_netbuf_cb(pst_netbuf);

        /* ��ȡ���������ֶ���Ϣ��������ӵ�netbuf��cb�ֶ��� */
        dmac_rx_get_dscr_info(pst_hal_device, pul_curr_dscr, pst_cb_ctrl);

        if (HAL_RX_NEW == pst_cb_ctrl->st_rx_status.bit_dscr_status)
        {
            pul_curr_dscr = pul_next_dscr;

            continue;
        }

        hal_rx_sync_invalid_dscr(pst_hal_device, pul_curr_dscr, en_queue_num);

        pul_curr_dscr = pul_next_dscr;
    }
    oal_irq_enable();

    /* �������������¹Ҹ�MAC */
    hal_set_machw_rx_buff_addr(pst_hal_device, (oal_uint32)(pst_rx_dscr_queue->pul_element_head), en_queue_num);

    /* DTS2015122607368,ʹ��MACǰ��Ӹ�λ��������ֹMAC�쳣���� */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_MPP);

    hal_reset_phy_machw(pst_hal_device, HAL_RESET_HW_TYPE_MAC, 0, 0, 0);

    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_MPP);

    /* enable MAC/PHY */
    hal_enable_machw_phy_and_pa(pst_hal_device);

    return;
}

#if 0
OAL_STATIC oal_void  dmac_rx_resume_dscr_queue_all(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    return;
}
#endif
#endif
/*****************************************************************************
 �� �� ��  : dmac_log_txq_overrun
 ��������  : ��¼MAC�ϱ����Ͷ�����ʱ����־��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_log_txq_overrun(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    oal_uint32                     ul_tx_q_status;
    hal_tx_dscr_queue_header_stru *pst_tx_queue;
    oal_uint32                     ul_value;
    hal_tx_queue_type_enum_uint8   en_queue;
    hal_tx_dscr_stru              *pst_dscr;
    oal_dlist_head_stru           *pst_pos;
    hal_to_dmac_device_stru       *pst_hal_device;
    oal_uint32                     ul_act_ppdu_cnt = 0;
    oal_uint32                     ul_rec_ppdu_cnt = 0;

    en_queue = (hal_tx_queue_type_enum_uint8)ul_param;

    if (OAL_PTR_NULL == pst_device || en_queue >= HAL_TX_QUEUE_BUTT)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_log_txq_overrun::invalid param.}");

        return;
    }

    pst_hal_device = pst_device->pst_device_stru;
    pst_tx_queue = &pst_hal_device->ast_tx_dscr_queue[en_queue];

    hal_get_tx_q_status(pst_hal_device, &ul_tx_q_status, en_queue);
    hal_get_all_tx_q_status(pst_hal_device, &ul_value);
    ul_rec_ppdu_cnt = pst_tx_queue->uc_ppdu_cnt;

    OAL_DLIST_SEARCH_FOR_EACH(pst_pos, &(pst_tx_queue->st_header))
    {
        pst_dscr = OAL_DLIST_GET_ENTRY(pst_pos, hal_tx_dscr_stru, st_entry);
        if(OAL_PTR_NULL != pst_dscr)
        {
            if (OAL_TRUE == pst_dscr->bit_is_first)
            {
                ul_act_ppdu_cnt++;
            }
            oam_report_dscr(BROADCAST_MACADDR, (oal_uint8*)pst_dscr, WLAN_MEM_SHARED_TX_DSCR_SIZE1, OAM_OTA_TYPE_TX_DSCR);
        }
    }

    OAM_ERROR_LOG4(0, OAM_SF_TX, "{dmac_log_txq_overrun::sw act ppdu_cnt=%d, sw record ppdu_cnt=%d, ul_tx_q_status=%d, ul_value=%d.}",
                   ul_act_ppdu_cnt, ul_rec_ppdu_cnt, ul_tx_q_status, ul_value);
}


OAL_STATIC oal_void dmac_dump_all_tx_dscr(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    oal_uint32                       ul_qnum;
    hal_tx_dscr_stru                *pst_dscr;
    oal_dlist_head_stru             *pst_pos;
    hal_to_dmac_device_stru         *pst_hal_device = pst_device->pst_device_stru;

    for(ul_qnum = 0; ul_qnum < HAL_TX_QUEUE_NUM; ul_qnum++)
    {
        OAM_WARNING_LOG2(0, OAM_SF_ANY, "{dmac_dump_all_tx_dscr::tx dscr dump. qnum[%d],ppducnt[%d]}",
                                        ul_qnum, pst_hal_device->ast_tx_dscr_queue[ul_qnum].uc_ppdu_cnt);

        OAL_DLIST_SEARCH_FOR_EACH(pst_pos, &(pst_hal_device->ast_tx_dscr_queue[ul_qnum].st_header))
        {
            pst_dscr   = OAL_DLIST_GET_ENTRY(pst_pos, hal_tx_dscr_stru, st_entry);

            if(OAL_PTR_NULL != pst_dscr)
            {
                oam_report_dscr(BROADCAST_MACADDR,
                            (oal_uint8*)pst_dscr,
                            WLAN_MEM_SHARED_TX_DSCR_SIZE1,
                            OAM_OTA_TYPE_TX_DSCR);
            }
        }
    }
}
/*****************************************************************************
 �� �� ��  : dmac_log_txq_overrun
 ��������  : ��¼MAC�ϱ����Ͷ�����ʱ����־��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��15��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_proc_rxbuf_too_small_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    pst_device->ul_rx_buf_too_small_show_counter++;
}
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 �� �� ��  : dmac_proc_para_cfg_error
 ��������  : ��¼����mac������־��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : d00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  dmac_proc_rx_fsm_st_timeout_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    pst_device->ul_rx_fsm_st_timeout_show_counter++;
}
OAL_STATIC oal_void  dmac_proc_tx_fsm_st_timeout_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    pst_device->ul_tx_fsm_st_timeout_show_counter++;
}
OAL_STATIC oal_void  dmac_proc_beacon_miss_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    pst_device->ul_beacon_miss_show_counter++;
}
OAL_STATIC oal_void dmac_tx_dataflow_break_error(mac_device_stru *pst_device, oal_uint32 ul_param)
{
    hal_to_dmac_device_stru *pst_hal_device = pst_device->pst_device_stru;
    mac_tx_dataflow_brk_bypass_struc *pst_brk_bypass = &(pst_device->st_dataflow_brk_bypass);
    oal_uint32 ul_tx_comp_cnt = 0;

    /* ÿ��128��DataFlow Break�Ĵ����жϣ��ȶԵ�ǰ�ķ�������жϸ�����֮ǰ��¼�ķ�������жϸ��� */
    if(0 != ((++pst_brk_bypass->ul_tx_dataflow_brk_cnt) & ((1 << 7) - 1)))
    {
        return;
    }

    hal_get_irq_stat(pst_hal_device, (oal_uint8 *)&ul_tx_comp_cnt, sizeof(ul_tx_comp_cnt), HAL_IRQ_TX_COMP_CNT);
    if(pst_brk_bypass->ul_last_tx_complete_isr_cnt == ul_tx_comp_cnt)
    {
        dmac_reset_para_stru            st_reset_param;

        OAM_INFO_LOG1(0, OAM_SF_TX, "{dmac_tx_dataflow_break_error::No TX Complete irq between 128 dataflow break, CurTxCompCnt: %d", ul_tx_comp_cnt);

        /* �������ۺϸ��� */
        if(OAL_TRUE == pst_brk_bypass->en_brk_limit_aggr_enable)
        {
            OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dataflow_break_error::Bypass Fail, CurTxCompCnt: %d", ul_tx_comp_cnt);
        }
        else
        {
            pst_brk_bypass->en_brk_limit_aggr_enable = OAL_TRUE;
            OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_tx_dataflow_break_error::Enable DataFlowBreak limit, CurTxCompCnt: %d", ul_tx_comp_cnt);
        }

        /* ��ʼ��Mac�߼� */
        OAL_MEMZERO(&st_reset_param, sizeof(st_reset_param));
        st_reset_param.uc_reset_type = HAL_RESET_HW_TYPE_MAC;
        dmac_reset_hw(pst_device, (oal_uint8 *)&st_reset_param);
    }

    /* ������ؼ����� */
    pst_brk_bypass->ul_last_tx_complete_isr_cnt = ul_tx_comp_cnt;
}
#endif
#if 0
/*****************************************************************************
 �� �� ��  : dmac_check_txq
 ��������  : ���Ӳ�������е�����֡,����ж��ж�,������������
 �������  : pst_dmac_vap
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��14��
    ��    ��   : wangweigang
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_check_txq(mac_device_stru *pst_mac_dev, oal_uint32 ul_param)
{
    oal_uint8                uc_q_idx           = 0;
    hal_tx_dscr_stru        *pst_tx_dscr_first  = OAL_PTR_NULL;
    hal_to_dmac_device_stru *pst_hal_device     = OAL_PTR_NULL;
    oal_uint32               ul_txq_ptr_status  = 0;
    oal_uint32               ul_txq_reg_dscr    = 0;
    oal_uint32               ul_reg_addr        = 0;
    oal_uint32               ul_ret             = OAL_SUCC;
    oal_uint32               ul_time_start;
    oal_uint32               ul_time_end;
    oal_uint32               ul_time_delay;

    pst_hal_device = pst_mac_dev->pst_device_stru;

    for (uc_q_idx = 0; uc_q_idx <= HAL_TX_QUEUE_VI; uc_q_idx++)
    {
        /* ����÷��Ͷ���û������,�����һ������ */
        if (pst_hal_device->ast_tx_dscr_queue[uc_q_idx].uc_ppdu_cnt == 0)
        {
            continue;
        }

        /* ��ʱ2ms,�ȴ�MACˢ�¼Ĵ���֮���ٶ�ȡ */
        ul_time_start = oal_5115timer_get_10ns();
        do
        {
            ul_time_end = oal_5115timer_get_10ns();
            if (ul_time_end < ul_time_start)
            {
                ul_time_delay = ul_time_start - ul_time_end;
            }
            else
            {
                ul_time_delay = ul_time_start + (0xFFFFFFFF - ul_time_end);
            }
        } while (ul_time_delay < MAX_DELAY_TIME);

        ul_reg_addr = (oal_uint32)(WITP_PA_AC_BK_FIRST_FRM_PTR_STATUS_REG + (uc_q_idx * 8));
        hal_reg_info(pst_hal_device, ul_reg_addr, &ul_txq_ptr_status);
        ul_txq_reg_dscr = (oal_uint32)OAL_PHY_TO_VIRT_ADDR(ul_txq_ptr_status);

        /* ȡ���ö����еĵ�һ�������� */
        pst_tx_dscr_first  = (hal_tx_dscr_stru *)OAL_DLIST_GET_ENTRY(pst_hal_device->ast_tx_dscr_queue[uc_q_idx].st_header.pst_next, hal_tx_dscr_stru, st_entry);
        /* ������ж��ˣ������ppdu */
        if (OAL_UNLIKELY((oal_uint32)pst_tx_dscr_first != ul_txq_reg_dscr))
        {
            OAM_WARNING_LOG2(0, OAM_SF_TX, "{dmac_check_txq::MAC loss tx complete irq, q_num[%d], dscr_addr[0x%x]}", pst_tx_dscr_first->uc_q_num, pst_tx_dscr_first);
            ul_ret = dmac_tx_complete_buff(pst_hal_device, pst_tx_dscr_first);
            if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
            {
                OAM_WARNING_LOG1(0, OAM_SF_TX, "{dmac_check_txq::dmac_tx_complete failed[%d].", ul_ret);
            }
        }
    }
}
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 �� �� ��  : dmac_soc_error_msg_report
 ��������  : soc������־�ϱ�
 �������  : oal_uint8 uc_vap_id
             hal_mac_error_type_enum_uint8 en_error_id
 �������  : ��
 �� �� ֵ  : OAL_STATIC oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��27��,���ڶ�
    ��    ��   : y00201072
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_soc_error_msg_report(oal_uint8 uc_vap_id, hal_mac_error_type_enum_uint8 en_error_id)
{
    switch (en_error_id)
    {
        case HAL_SOC_ERROR_BUCK_OCP:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_BUCK_OCP}\r\n");
            break;

        case HAL_SOC_ERROR_BUCK_SCP:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_BUCK_SCP}\r\n");
            break;

        case HAL_SOC_ERROR_OCP_RFLDO1:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_OCP_RFLDO1}\r\n");
            break;

        case HAL_SOC_ERROR_OCP_RFLDO2:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_OCP_RFLDO2}\r\n");
            break;

        case HAL_SOC_ERROR_OCP_CLDO:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_OCP_CLDO}\r\n");
            break;

        case HAL_SOC_ERROR_RF_OVER_TEMP:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_RF_OVER_TEMP}\r\n");
            break;

        case HAL_SOC_ERROR_CMU_UNLOCK:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_CMU_UNLOCK}\r\n");
            break;

        case HAL_SOC_ERROR_PCIE_SLV_ERR:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::HAL_SOC_ERROR_PCIE_SLV_ERR}\r\n");
            break;

        default:
            OAM_ERROR_LOG0(uc_vap_id, OAM_SF_ANY, "{dmac_soc_error_msg_report::unknown soc error.}\r\n");
            break;
    }

    return OAL_SUCC;
}
#endif
#if 0
/*****************************************************************************
 �� �� ��  : dmac_handle_mac_error_immediately
 ��������  : MAC�����жϴ�����(��������)
 �������  : pst_mac_device: MAC DEVICE�ṹ��ָ��
             en_error_id   : MAC�����ж����ͣ�ע��˴�ö��ֵ������ж�״̬�Ĵ�����λһһ��Ӧ
 �������  : ��
 �� �� ֵ  : OAL_SUCC������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  dmac_handle_reset_mac_error_immediately(
                mac_device_stru                 *pst_mac_device,
                hal_mac_error_type_enum_uint8    en_error_id)
{
    hal_to_dmac_device_stru   *pst_hal_device;
    dmac_reset_para_stru       st_reset_param;

    if (OAL_UNLIKELY(en_error_id >= HAL_MAC_ERROR_TYPE_BUTT))
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_hal_device = pst_mac_device->pst_device_stru;

    /* ��λ: ��������쳣ͳ�ƣ����¿�ʼ���� */
    OAL_MEMZERO(pst_hal_device->st_dfr_err_opern, OAL_SIZEOF(pst_hal_device->st_dfr_err_opern));

    /*��λMAC + PHY���߼�*/
    st_reset_param.uc_reset_type    = HAL_RESET_HW_TYPE_ALL;
    st_reset_param.uc_reset_mac_mod = HAL_RESET_MAC_ALL;
    st_reset_param.uc_reset_mac_reg = OAL_FALSE;
    st_reset_param.uc_reset_phy_reg = OAL_FALSE;

    dmac_reset_hw(pst_mac_device, (oal_uint8 *)&st_reset_param);

    return OAL_SUCC;
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : dmac_set_agc_lock_channel
 ��������  : wavetest�������ܲ��Գ������趨AGC��ͨ��
 �������  : pst_vap:mac vapָ��

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��02��
    ��    ��   : ywx282918
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_set_agc_lock_channel(
            mac_vap_stru        *pst_vap,
            dmac_rx_ctl_stru    *pst_cb_ctrl)
{
    mac_device_stru           *pst_mac_device = OAL_PTR_NULL;
    dmac_vap_stru             *pst_dmac_vap = OAL_PTR_NULL;
    hal_to_dmac_device_stru   *pst_hal_device = OAL_PTR_NULL;

    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {
        return;
    }

    if (pst_mac_device->en_is_wavetest)
    {
        /* Wavetest���ܲ��Գ�����,�趨AGC�̶���ͨ��0  */
        if (pst_mac_device->uc_lock_channel == 0x00)
        {
            return;
        }
        else
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_vap->uc_vap_id);
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
            {
                return;
            }

            pst_hal_device = pst_dmac_vap->pst_hal_device;
            hal_reg_write(pst_hal_device, 0x20038d40, 0x00);

            pst_mac_device->uc_lock_channel = 0x00;
        }
    }
    else
    {
        /* ��Wavetest���ܲ��Գ�����,�趨AGC��ͨ��Ϊ����Ӧ */
        if (pst_mac_device->uc_lock_channel == 0x02)
        {
            return;
        }
        else
        {
            pst_dmac_vap = mac_res_get_dmac_vap(pst_vap->uc_vap_id);
            if (OAL_UNLIKELY(OAL_PTR_NULL == pst_dmac_vap))
            {
                return;
            }

            pst_hal_device = pst_dmac_vap->pst_hal_device;
            hal_reg_write(pst_hal_device, 0x20038d40, 0x02);

            pst_mac_device->uc_lock_channel = 0x02;
        }
    }
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_mac_error_process_event
 ��������  : ���մ����жϴ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���
 �޸���ʷ      :
  1.��    ��   : 2014��10��22��
    ��    ��   : zhangyu 00241943
    �޸�����   : 1102����Ĵ�������������Ҫ�ϱ����������룬�����Ϊһ��uint64������֮����д������
                 ul_error2_irq_state:1151�������дΪ0��1102��дERR2_INTR_STATUS_REG��ȡֵ

*****************************************************************************/
oal_uint32  dmac_mac_error_process_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru                     *pst_event;
    hal_error_irq_event_stru           *pst_error_irq_event;
    hal_error_state_stru                st_error_state;
    hal_to_dmac_device_stru            *pst_hal_device;
    mac_device_stru                    *pst_device;
    oal_uint32                          ul_error1_irq_state = 0;
    oal_uint32                          ul_error2_irq_state = 0;
    hal_mac_error_type_enum_uint8       en_error_id = 0;
    oal_uint8                           uc_show_error_mask[] = {
                                        HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL,
                                    #if defined(_PRE_PRODUCT_ID_HI110X_DEV)
                                        HAL_MAC_ERROR_UNEXPECTED_RX_Q_EMPTY,
                                        HAL_MAC_ERROR_UNEXPECTED_HIRX_Q_EMPTY,
                                        HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR,
                                    #endif
                                        HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND};
    oal_uint32                          ul_error_mask = 0;
    oal_uint8                           uc_err_mask_idx;
    oal_uint8                           uc_status_idx    = 0;
    oal_uint32                          ul_err_code      = 0;

#ifdef _PRE_WLAN_FEATURE_DFR
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    dmac_device_stru                   *pst_dmac_dev;
#endif
#endif

    dmac_error_proc_stru                st_err_proc_func[HAL_MAC_ERROR_TYPE_BUTT] =
    {
      {dmac_dump_all_tx_dscr,0},
      {dmac_proc_rxbuf_too_small_error,0},
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
      {dmac_tx_dataflow_break_error,0},
      {dmac_proc_rx_fsm_st_timeout_error,0},{dmac_proc_tx_fsm_st_timeout_error,0},
#else
      {dmac_dump_all_tx_dscr,0},  /* HAL_MAC_ERROR_TX_DATAFLOW_BREAK */
      {dmac_null_fn,0},{dmac_null_fn,0},
#endif
      {dmac_null_fn,0},{dmac_null_fn,0},
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},  /* HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND �� HAL_MAC_ERROR_HIRX_INTR_FIFO_OVERRUN*/
      {dmac_rx_resume_dscr_queue, 0},    /* HAL_MAC_ERROR_UNEXPECTED_RX_Q_EMPTY */
      {dmac_rx_resume_dscr_queue, 1},    /* HAL_MAC_ERROR_UNEXPECTED_HIRX_Q_EMPTY */
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_BK},  /* HAL_MAC_ERROR_TX_ACBK_Q_OVERRUN */
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_BE},  /* HAL_MAC_ERROR_TX_ACBE_Q_OVERRUN */
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_VI},  /* HAL_MAC_ERROR_TX_ACVI_Q_OVERRUN */
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_VO},  /* HAL_MAC_ERROR_TX_ACVO_Q_OVERRUN */
      {dmac_log_txq_overrun, (oal_uint32)HAL_TX_QUEUE_HI},  /* HAL_MAC_ERROR_TX_HIPRI_Q_OVERRUN */
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
      {dmac_proc_beacon_miss_error,0},
#else
      {dmac_null_fn,0},
#endif
      {dmac_null_fn,0},
#if 0
      {dmac_rx_resume_dscr_queue_all,0},  /* HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR 29 */
#else
      /*do nothing��DTS2015042800155,z00262551*/
      {dmac_null_fn,0}, /* HAL_MAC_ERROR_UNEXPECTED_RX_DESC_ADDR 29 */
#endif
      {dmac_null_fn,0},
      {dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},{dmac_null_fn,0},
      {dmac_null_fn,0},{dmac_null_fn,0},
      {dmac_rx_resume_dscr_queue,2}, /* HAL_MAC_ERROR_RX_SMALL_Q_EMPTY */
      {dmac_dump_all_tx_dscr,0},{dmac_dump_all_tx_dscr,0},{dmac_null_fn,0}   /* OTHER */
    };

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::null param.}\r\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼�ͷ���¼��ṹ��ָ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_error_irq_event     = (hal_error_irq_event_stru *)(pst_event->auc_event_data);
    pst_hal_device          = pst_error_irq_event->pst_hal_device;
    ul_error1_irq_state = pst_error_irq_event->st_error_state.ul_error1_val;
    ul_error2_irq_state = pst_error_irq_event->st_error_state.ul_error2_val;;

#ifdef _PRE_WLAN_DFT_REG
    if (OAL_SUCC == hi1151_debug_refresh_reg(pst_hal_device, OAM_REG_EVT_RX))
    {
        hi1151_debug_frw_evt(pst_hal_device);
    }
#endif

    pst_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG1(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::mac_res_get_dev return null. device_id=[%d]}\r\n",
                       pst_event->st_event_hdr.uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }


#ifdef _PRE_WLAN_FEATURE_DFR
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    pst_dmac_dev = dmac_res_get_mac_dev(pst_device->uc_device_id);
    if (OAL_PTR_NULL == pst_dmac_dev)
    {
        OAM_ERROR_LOG1(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::dmac_res_get_mac_dev return null. device_id=[%d]}\r\n",
                       pst_device->uc_device_id);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ����pcie err���� */
    pst_dmac_dev->ul_pcie_err_cnt += oal_pci_check_clear_error_nonfatal(pst_hal_device->uc_chip_id);
#endif
#endif

    /* �ϱ���HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL �� HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT �� HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND �����жϣ����ô�ӡdevice id */
    if((ul_error1_irq_state & (~(1 << HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL | 1 << HAL_MAC_ERROR_MATRIX_CALC_TIMEOUT | 1 << HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND))) || ul_error2_irq_state)
    {
        OAM_WARNING_LOG3(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::chip id=[%d], error1 state=[0x%08x], erro2 state=[0x%08x]\r\n",
            pst_event->st_event_hdr.uc_chip_id, ul_error1_irq_state, ul_error2_irq_state);
    }

    for (uc_status_idx = 0; uc_status_idx < 2; uc_status_idx++)
    {
        if (uc_status_idx == 0)
        {
            ul_err_code = ul_error1_irq_state;
            en_error_id = 0;
        }
        else
        {
            ul_err_code = ul_error2_irq_state;
            en_error_id = HAL_MAC_ERROR_TX_ACBE_BACKOFF_TIMEOUT;
        }

        while (ul_err_code)
        {
            if (HAL_MAC_ERROR_TYPE_BUTT <= en_error_id)
            {
                OAM_WARNING_LOG2(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::error type[%d], ul_err_code = [%d].}\r\n",
                                en_error_id, ul_err_code);
                ul_err_code = 0;

                break;
            }

            if (0 == (ul_err_code & BIT0))
            {
                en_error_id++;
                ul_err_code = ul_err_code >> 1;
                continue;
            }

            st_err_proc_func[en_error_id].p_func(pst_device, (st_err_proc_func[en_error_id].ul_param));

#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
            if((en_error_id == HAL_MAC_ERROR_BEACON_MISS) ||(en_error_id == HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT)||(en_error_id == HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT))
            {
                if((en_error_id == HAL_MAC_ERROR_BEACON_MISS)&&((pst_device->ul_beacon_miss_show_counter <= 50) || (pst_device->ul_beacon_miss_show_counter % 100 == 0)))
                {
                    hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
                    /* BEACON MISSά�� */
                    hal_get_beacon_miss_status(pst_device->pst_device_stru);
                }
                else if((en_error_id == HAL_MAC_ERROR_RX_FSM_ST_TIMEOUT)&&((pst_device->ul_rx_fsm_st_timeout_show_counter <= 50) || (pst_device->ul_rx_fsm_st_timeout_show_counter % 100 == 0)))
                {
                    hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
                }
                else if((en_error_id == HAL_MAC_ERROR_TX_FSM_ST_TIMEOUT)&&((pst_device->ul_tx_fsm_st_timeout_show_counter <= 50) || (pst_device->ul_tx_fsm_st_timeout_show_counter % 100 == 0)))
                {
                    hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
                }
            }
            else
            {
                hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
            }
#else
            hal_mac_error_msg_report(pst_device->pst_device_stru, en_error_id);
    #ifdef _PRE_WLAN_FEATURE_BTCOEX
            if (HAL_MAC_ERROR_BEACON_MISS == en_error_id)
            {
                mac_vap_stru *pst_mac_vap;
                dmac_vap_stru *pst_dmac_vap;

                dmac_btcoex_get_legacy_ap(pst_device, &pst_mac_vap);
                if (OAL_PTR_NULL != pst_mac_vap)
                {
                    oal_uint8 *puc_beacon_miss;
                    pst_dmac_vap = (dmac_vap_stru *)pst_mac_vap;
                    puc_beacon_miss = &(pst_dmac_vap->st_dmac_vap_btcoex.st_dmac_vap_btcoex_occupied.uc_ap_beacon_miss);
                    /* ÿ�ϱ�5��Beacon miss(��Ӧ30��beacon֡��ʧ)�����һ��ȫ���Ĵ��� */
                    (*puc_beacon_miss)++;
                    if (0 == ((*puc_beacon_miss) % 4))
                    {
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1102_DEV)
                        hi1102_dft_report_all_reg_state(pst_device->pst_device_stru);
#endif
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1103_DEV)
                        hi1103_dft_report_all_reg_state(pst_device->pst_device_stru);
#endif
                    }
                    OAM_WARNING_LOG1(0, OAM_SF_ANY, "{hi1102_mac_error_msg_report::HAL_MAC_ERROR_BEACON_MISS, beacon miss: %d}\r\n", *puc_beacon_miss);

                }

            }
    #endif
#endif

            if (dmac_mac_error_overload(pst_device, en_error_id))
            {
                 /*�������̫���ʱ�򣬲��������ϱ�����˲���Ҫunmask��bit,��tbtt�ж���ͳһ��0xffffffff unmaskȫ������*/
                 if ((en_error_id == HAL_MAC_ERROR_RXBUFF_LEN_TOO_SMALL)
                   ||(en_error_id == HAL_MAC_ERROR_BA_ENTRY_NOT_FOUND))
                 {
                     OAM_WARNING_LOG1(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::error type[%d] overload.}\r\n", en_error_id);
                     ul_error1_irq_state &= ~((oal_uint32)1 << en_error_id);
                 }
                 else
                 {
                     OAM_ERROR_LOG1(0, OAM_SF_IRQ, "{dmac_mac_error_process_event::error type[%d] overload.}\r\n", en_error_id);
                     if (en_error_id <= HAL_MAC_ERROR_RESERVED_31)
                     {
                         ul_error1_irq_state &= ~((oal_uint32)1 << en_error_id);
                     }
                     else
                     {
                         ul_error2_irq_state &= ~((oal_uint32)1 << (en_error_id - HAL_MAC_ERROR_TX_ACBE_BACKOFF_TIMEOUT));
                     }
                 }
            }

            /* ���mac �����Ƿ���Ҫ�����λ */
            dmac_dfr_process_mac_error(pst_device, en_error_id, ul_error1_irq_state, ul_error2_irq_state);

            en_error_id++;
            ul_err_code = ul_err_code >> 1;
        }
    }

    /*���㲻��Ҫ��ӡpcie�������͵����λͼ*/
    for (uc_err_mask_idx = 0; uc_err_mask_idx < OAL_SIZEOF(uc_show_error_mask) / OAL_SIZEOF(oal_uint8); uc_err_mask_idx++)
    {
        ul_error_mask |= 1 << uc_show_error_mask[uc_err_mask_idx];
    }
    st_error_state.ul_error1_val = 0xFFFFFFFF;
    st_error_state.ul_error2_val = 0xFFFFFFFF;

    /* ���ڷ�MASK��Errorʱ�Ŵ�ӡpcie״̬ */
    if ((ul_error1_irq_state & ~(ul_error_mask)) || (ul_error2_irq_state))
    {
        hal_show_fsm_info(pst_device->pst_device_stru);
    }

    /* ���ж� */
    hal_clear_mac_error_int_status(pst_hal_device, &st_error_state);

    /* ���ж�״̬ */
    hal_clear_mac_int_status(pst_hal_device, (1 << DMAC_PA_ERROR_OFFSET));

    /* unmask error stauts */

    st_error_state.ul_error1_val = ul_error1_irq_state;
    st_error_state.ul_error2_val = ul_error2_irq_state & 0xffffffdf;
    hal_unmask_mac_error_init_status(pst_hal_device, &st_error_state);

    /* unmask mac stauts */
    hal_unmask_mac_init_status(pst_hal_device, (1 << DMAC_PA_ERROR_OFFSET));

    return OAL_SUCC;
}
#if (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
/*****************************************************************************
 �� �� ��  : dmac_soc_error_process_event
 ��������  : ����soc�����ж�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��1��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_soc_error_process_event(frw_event_mem_stru *pst_event_mem)
{
    dmac_reset_para_stru                st_reset;
    frw_event_stru                     *pst_event;
    hal_error_irq_event_stru           *pst_error_irq_event;
    mac_device_stru                    *pst_device;
    hal_soc_error_type_enum_uint8       en_error_id = 0;
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_soc_error_process_event::pst_event_mem null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�¼�ͷ���¼��ṹ��ָ�� */
    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;
    pst_error_irq_event     = (hal_error_irq_event_stru *)(pst_event->auc_event_data);

    pst_device= mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if (OAL_PTR_NULL == pst_device)
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{dmac_soc_error_process_event::pst_device null.}");

        return OAL_ERR_CODE_PTR_NULL;
    }

    /*��ȡfsm״̬����Ϣ*/
    hal_show_fsm_info(pst_device->pst_device_stru);

    for (en_error_id = 0; en_error_id < HAL_SOC_ERROR_TYPE_BUTT; en_error_id++)
    {
        if (pst_error_irq_event->st_error_state.ul_error1_val & (1 << en_error_id))
        {
            dmac_soc_error_msg_report(0, en_error_id);
        }
    }

    /*��λMAC+PHY���߼�*/
    st_reset.uc_reset_type = HAL_RESET_HW_TYPE_ALL;
    st_reset.uc_reset_mac_mod = HAL_RESET_MAC_ALL;
    st_reset.uc_reset_mac_reg = OAL_FALSE;
    st_reset.uc_reset_phy_reg = OAL_FALSE;

    dmac_reset_hw(pst_device, (oal_uint8*)&st_reset);
    hal_en_soc_intr(pst_device->pst_device_stru);

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : dmac_rx_process_frame
 ��������  : ����ÿһ��֡�Ĳ����ĺ���,��Ҫ��Խ��������е�֡�ĸ��ֹ��˴���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��29��
    ��    ��   : g00260350
    �޸�����   : mic������������������ֻ��Ҫ�ϱ���host
  3.��    ��   : 2014��05��23��
    ��    ��   : z00273164
    �޸�����   : ����CCMP�طŹ���

*****************************************************************************/
/*lint -e801*/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif

dmac_rx_frame_ctrl_enum_uint8  dmac_rx_process_frame(
                mac_vap_stru                   *pst_vap,
                dmac_rx_ctl_stru               *pst_cb_ctrl,
                oal_netbuf_stru                *pst_netbuf,
                oal_netbuf_head_stru           *pst_netbuf_header)
                //dmac_rx_frame_ctrl_enum_uint8  *pen_frame_ctrl)
{
    mac_ieee80211_frame_stru           *pst_frame_hdr;
    oal_uint8                          *puc_transmit_addr;
    oal_uint8                          *puc_dest_addr;
    dmac_user_stru                     *pst_ta_dmac_user = OAL_PTR_NULL;
    oal_uint16                          us_user_idx      = 0xffff;
    oal_nl80211_key_type                en_key_type;
    oal_uint32                          ul_ret;
    oal_uint16                          us_dscr_status;
#ifdef _PRE_WLAN_HW_TEST
    mac_device_stru                    *pst_mac_device = OAL_PTR_NULL;
#endif

#ifdef _PRE_WLAN_DFT_STAT
    dmac_vap_stru               *pst_dmac_vap;
    pst_dmac_vap = (dmac_vap_stru *)mac_res_get_dmac_vap(pst_vap->uc_vap_id);
    if (OAL_PTR_NULL == pst_dmac_vap)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "mac_res_get_dmac_vap::pst_dmac_vap null. vap_id[%u]",pst_vap->uc_vap_id);
        goto rx_pkt_drop;
    }
#endif
    /* ͳ��VAP������յ���MPDU���� */
    OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_mpdu_total_num, 1);
    DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_mpdu_total_num, 1);

    /* ��ȡ802.11ͷָ�롢���Ͷ˵�ַ */
    pst_frame_hdr     = (mac_ieee80211_frame_stru *)(mac_get_rx_cb_mac_hdr(&(pst_cb_ctrl->st_rx_info)));
    puc_transmit_addr = pst_frame_hdr->auc_address2;
    puc_dest_addr     = pst_frame_hdr->auc_address1;

    dmac_rx_record_tid(pst_vap, pst_frame_hdr);

    /* ���Ͷ˵�ַΪ�㲥֡��ֱ�Ӷ��� */
    if (ETHER_IS_MULTICAST(puc_transmit_addr))
    {
        //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::the transmit addr is multicast.}");

// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;
        goto rx_pkt_drop;
    }

    us_dscr_status = pst_cb_ctrl->st_rx_status.bit_dscr_status;

    /* VAP ID Ϊ0�������֡����������BSS�Ĺ㲥����֡ */
    if (0 == pst_vap->uc_vap_id)
    {
        //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "this frame is bcast frame from other bss. exit func dmac_rx_process_frame");

        if ((HAL_RX_SUCCESS != us_dscr_status)
             || (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type))
        {
            //OAM_INFO_LOG2(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::dscr_status[%d]type[%d]", us_dscr_status, pst_frame_hdr->st_frame_control.bit_type);
            goto rx_pkt_drop;
        }

        return DMAC_RX_FRAME_CTRL_BUTT;
    }

    /* �Ե���֡���й��� ���Ƿ����ҵ�֡��ֱ�ӹ��˵� */
    if (OAL_FALSE == ETHER_IS_MULTICAST(puc_dest_addr))
    {
#ifdef _PRE_WLAN_FEATURE_P2P
        /* DTS2015022702328 ��Ҫ�ȶ�P2P0��MAC��ַ��WLAN��MAC��ַ */
        ul_ret = oal_compare_mac_addr(puc_dest_addr, pst_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID)
                    && oal_compare_mac_addr(puc_dest_addr, pst_vap->pst_mib_info->st_wlan_mib_sta_config.auc_p2p0_dot11StationID);
#else
        ul_ret = oal_compare_mac_addr(puc_dest_addr, pst_vap->pst_mib_info->st_wlan_mib_sta_config.auc_dot11StationID);
#endif  /* _PRE_WLAN_FEATURE_P2P */
        if (0 != ul_ret)
        {
            goto rx_pkt_drop;
        }
    }
    OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_ADDR_VAP);

    if (WLAN_VAP_MODE_BSS_STA == dmac_vap_get_bss_type(pst_vap))
    {
        us_user_idx = pst_vap->uc_assoc_vap_id;
    }
    else if(WLAN_VAP_MODE_BSS_AP == dmac_vap_get_bss_type(pst_vap))
    {
        /* ��ȡ���Ͷ˵��û�ָ�룬���浽cb�ֶ��У�uapd���ܹ���ʱ���õ� */
        ul_ret = mac_vap_find_user_by_macaddr(pst_vap, puc_transmit_addr, &us_user_idx);
        if (OAL_ERR_CODE_PTR_NULL == ul_ret)
        {
            //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::mac_vap_find_user_by_macaddr return null.}");
            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_ta_check_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_ta_check_dropped, 1);

// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;
            goto rx_pkt_drop;
        }
    }
    pst_ta_dmac_user = (dmac_user_stru *)mac_res_get_dmac_user(us_user_idx);

    if (OAL_PTR_NULL != pst_ta_dmac_user)
    {
        /* �����û�ʱ��� */
        pst_ta_dmac_user->ul_last_active_timestamp = (oal_uint32)OAL_TIME_GET_STAMP_MS();

    #ifdef _PRE_DEBUG_MODE_USER_TRACK
        /* ������Դ��û���֡Э��ģʽ�Ƿ�ı䣬����ı������ϱ� */
        dmac_user_check_txrx_protocol_change(pst_ta_dmac_user,
                                        HAL_GET_DATA_PROTOCOL_MODE(*((oal_uint8 *)&(pst_cb_ctrl->st_rx_statistic.un_nss_rate))),
                                        OAM_USER_INFO_CHANGE_TYPE_RX_PROTOCOL);
    #endif

        /*��Ϣ�ϱ�ͳ�ƣ��ṩ��linux�ں�PKT����*/
        if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
        {
            DMAC_USER_STATS_PKT_INCR(pst_ta_dmac_user->st_query_stats.ul_drv_rx_pkts, 1);
#if defined(_PRE_PRODUCT_ID_HI110X_DEV)
            DMAC_USER_STATS_PKT_INCR(pst_ta_dmac_user->st_query_stats.ul_drv_rx_bytes,
                                    pst_cb_ctrl->st_rx_info.us_frame_len - pst_cb_ctrl->st_rx_info.bit_mac_header_len - SNAP_LLC_FRAME_LEN);
#else
            DMAC_USER_STATS_PKT_INCR(pst_ta_dmac_user->st_query_stats.ul_drv_rx_bytes,
                                    pst_cb_ctrl->st_rx_info.us_frame_len - pst_cb_ctrl->st_rx_info.uc_mac_header_len - SNAP_LLC_FRAME_LEN);
#endif
        }


    }

#ifdef _PRE_WLAN_HW_TEST
    pst_mac_device = mac_res_get_dev(pst_vap->uc_device_id);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_mac_device))
    {

        goto rx_pkt_drop;
    }
    /* ���ջ��߸����� */
    if (HAL_ALWAYS_RX_RESERVED == pst_mac_device->pst_device_stru->bit_al_rx_flag)
    {
        /* phy���ܲ���ͳ����� */
        dmac_rx_fcs_statistic_info(pst_frame_hdr, pst_vap, pst_cb_ctrl);
        OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_phy_perform_dropped, 1);

        /* ���ڵ�ǰ��������ٶȽ�������ʱֱ���ͷţ����� */
// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;

        goto rx_pkt_drop;
    }
#endif

    /*OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::bit_dscr_status=%d. }", pst_cb_ctrl->st_rx_status.bit_dscr_status);*/

    if (HAL_RX_SUCCESS != us_dscr_status)
    {
        /* ����������statusΪkey search failʱ���쳣���� */
        if (HAL_RX_KEY_SEARCH_FAILURE == us_dscr_status)
        {
            dmac_user_key_search_fail_handler(pst_ta_dmac_user);
// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;

            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_key_search_fail_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_key_search_fail_dropped, 1);

            goto rx_pkt_drop;
        }

        /* ����������statusΪ tkip mic faile ʱ���쳣���� */
        if (HAL_RX_TKIP_MIC_FAILURE == us_dscr_status)
        {
            /*�ж���Կ����,peerkey �ݲ�����*/
            en_key_type = ETHER_IS_MULTICAST(puc_dest_addr) ? NL80211_KEYTYPE_GROUP : NL80211_KEYTYPE_PAIRWISE;
            dmac_11i_tkip_mic_failure_handler(pst_vap, puc_transmit_addr, en_key_type);
            //OAM_INFO_LOG0(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::bit_dscr_status=HAL_RX_TKIP_MIC_FAILURE.");

// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;

            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_tkip_mic_fail_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_tkip_mic_fail_dropped, 1);
            goto rx_pkt_drop;
        }

        if (OAL_TRUE != dmac_rx_check_mgmt_replay_failure(pst_cb_ctrl))
        {
            /*DTS2013122406910  Ӳ���ϱ����طŴ��������Ҫ��ʱ��ܣ���Ӳ��������ٷſ�*/
            /* if ((HAL_RX_TKIP_REPLAY_FAILURE != pst_cb_ctrl->st_rx_status.bit_dscr_status) && (HAL_RX_CCMP_REPLAY_FAILURE != pst_cb_ctrl->st_rx_status.bit_dscr_status)) */
            OAM_WARNING_LOG1(pst_vap->uc_vap_id, OAM_SF_ANY, "{dmac_rx_process_frame::bit_dscr_status=%d.}", us_dscr_status);
// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;

            OAM_STAT_VAP_INCR(pst_vap->uc_vap_id, rx_replay_fail_dropped, 1);
            DMAC_VAP_DFT_STATS_PKT_INCR(pst_dmac_vap->st_query_stats.ul_rx_replay_fail_dropped, 1);
            goto rx_pkt_drop;
        }
    }

    /* ��ȡ���û�index�������cb�ֶ��У���������ʹ��(dmac_rx_filter_frame) */
    MAC_GET_RX_CB_TA_USER_IDX(&(pst_cb_ctrl->st_rx_info)) = (oal_uint8)us_user_idx;

    if (OAL_PTR_NULL != pst_ta_dmac_user)
    {
        OAM_STAT_USER_INCR(us_user_idx, rx_mpdu_num, 1);

        /*��Ϣ�ϱ�ͳ�ƣ��ṩ��linux�ں�PKT����*/
        if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
        {
#if (!defined(_PRE_PRODUCT_ID_HI110X_DEV))
            OAM_STAT_USER_INCR(us_user_idx, rx_mpdu_bytes,
                                pst_cb_ctrl->st_rx_info.us_frame_len - pst_cb_ctrl->st_rx_info.uc_mac_header_len - SNAP_LLC_FRAME_LEN);
#endif
        }
    }

    OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_DSCR_SEC);
    /* ����һ:��Է��Ͷ˵�ַ����(��������״̬��AMPDU���ԡ����ܴ���) */
    ul_ret = dmac_rx_filter_frame(pst_vap, pst_cb_ctrl, pst_ta_dmac_user);
    if (OAL_SUCC != ul_ret)        /* �����쳣 */
    {
        //OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::dmac_rx_filter_frame failed[%d].}", ul_ret);
        goto rx_pkt_drop;
    }
    OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_CIPHER_AMPDU);

    if (WLAN_DATA_BASICTYPE == pst_frame_hdr->st_frame_control.bit_type)
    {
        /* AGC��ͨ���趨  */
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
        dmac_set_agc_lock_channel(pst_vap, pst_cb_ctrl);
#endif

        ul_ret = dmac_rx_process_data_frame(pst_vap, pst_cb_ctrl, pst_netbuf);

        OAL_MEM_NETBUF_TRACE(pst_netbuf, OAL_TRUE);
        if (OAL_SUCC != ul_ret)
        {
// *pen_frame_ctrl = DMAC_RX_FRAME_CTRL_DROP;
            //OAM_INFO_LOG1(pst_vap->uc_vap_id, OAM_SF_RX, "{dmac_rx_process_frame::dmac_rx_process_data_frame failed[%d].}", ul_ret);
            goto rx_pkt_drop;
        }
    }



#ifdef _PRE_WLAN_DFT_STAT
    dmac_rx_vap_stat(pst_dmac_vap, pst_netbuf_header, pst_netbuf, pst_cb_ctrl);
#endif
    OAL_MIPS_RX_STATISTIC(DMAC_PROFILING_FUNC_RX_DMAC_HANDLE_PER_MPDU_FILTER_ALG_PSM_NULL);

    return DMAC_RX_FRAME_CTRL_BUTT;

rx_pkt_drop:
    /* ��֡���� */
    if (OAL_PTR_NULL != pst_ta_dmac_user)
    {
        /*��Ϣ�ϱ�ͳ�ƣ��ṩ��linux�ں�PKT����*/
        DMAC_USER_STATS_PKT_INCR(pst_ta_dmac_user->st_query_stats.ul_rx_dropped_misc,1);
    }

    return DMAC_RX_FRAME_CTRL_DROP;
}
/*lint +e801*/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif

#if 0
/*****************************************************************************
 �� �� ��  : dmac_start_stat_rssi
 ��������  : ��ʼͳ��ƽ��rssi�ӿ�
 �������  : pst_user : Userָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��17��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_start_stat_rssi(dmac_user_stru *pst_dmac_user)
{
    pst_dmac_user->st_user_rate_info.en_dmac_rssi_stat_flag = OAL_TRUE;

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : dmac_get_stat_rssi
 ��������  : ��ȡͳ��ƽ��rssi�ӿ�
 �������  : pst_dmac_user : dmac userָ��
 �������  : pc_tx_rssi:ƽ��ACK rssi
             pc_rx_rssi:ƽ������rssi
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��17��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_get_stat_rssi(dmac_user_stru *pst_dmac_user, oal_int8 *pc_tx_rssi, oal_int8 *pc_rx_rssi)
{
    dmac_user_rate_info_stru   *pst_user_info;

    pst_user_info = &pst_dmac_user->st_user_rate_info;

    /* ��ȡƽ��ACK RSSI */
    if (0 != pst_user_info->st_dmac_rssi_stat_info.us_tx_rssi_stat_count)
    {
        *pc_tx_rssi = (oal_int8)(pst_user_info->st_dmac_rssi_stat_info.l_tx_rssi / pst_user_info->st_dmac_rssi_stat_info.us_tx_rssi_stat_count);
    }

    /* ��ȡƽ������ RSSI */
    if (0 != pst_user_info->st_dmac_rssi_stat_info.us_rx_rssi_stat_count)
    {
        *pc_rx_rssi = (oal_int8)(pst_user_info->st_dmac_rssi_stat_info.l_rx_rssi / pst_user_info->st_dmac_rssi_stat_info.us_rx_rssi_stat_count);
    }

    /* ���ͳ����Ϣ */
    OAL_MEMZERO(&pst_user_info->st_dmac_rssi_stat_info, OAL_SIZEOF(dmac_rssi_stat_info_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_stop_stat_rssi
 ��������  : ֹͣͳ��ƽ��rssi�ӿ�
 �������  : pst_dmac_user : dmac userָ��
 �������  :
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��17��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_stop_stat_rssi(dmac_user_stru *pst_dmac_user)
{
    pst_dmac_user->st_user_rate_info.en_dmac_rssi_stat_flag = OAL_FALSE;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_start_stat_rate
 ��������  : ��ʼͳ��ƽ�����ʽӿ�
 �������  : pst_user : Userָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��17��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_start_stat_rate(dmac_user_stru *pst_dmac_user)
{
    pst_dmac_user->st_user_rate_info.en_dmac_rate_stat_flag = OAL_TRUE;

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : dmac_get_stat_rate
 ��������  : ��ȡͳ��ƽ�����ʽӿ�
 �������  : pst_mac_user : Userָ��
 �������  : pul_tx_rate:ƽ����������
             pul_rx_rate:ƽ����������
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��17��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_get_stat_rate(dmac_user_stru *pst_dmac_user, oal_uint32 *pul_tx_rate, oal_uint32 *pul_rx_rate)
{
    dmac_user_rate_info_stru   *pst_user_info;

    pst_user_info = &pst_dmac_user->st_user_rate_info;

    /* ��ȡƽ���������� */
    if (0 != pst_user_info->st_dmac_rate_stat_info.us_tx_rate_stat_count)
    {
        *pul_tx_rate = (oal_uint32)(pst_user_info->st_dmac_rate_stat_info.ul_tx_rate / pst_user_info->st_dmac_rate_stat_info.us_tx_rate_stat_count);
    }

    /* ��ȡƽ���������� */
    if (0 != pst_user_info->st_dmac_rate_stat_info.us_rx_rate_stat_count)
    {
        *pul_rx_rate = (oal_uint32)(pst_user_info->st_dmac_rate_stat_info.ul_rx_rate / pst_user_info->st_dmac_rate_stat_info.us_rx_rate_stat_count);
    }

    /* ���ͳ����Ϣ */
    OAL_MEMZERO(&pst_user_info->st_dmac_rate_stat_info, OAL_SIZEOF(dmac_rate_stat_info_stru));

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 �� �� ��  : dmac_stop_stat_rate
 ��������  : ֹͣͳ��ƽ�����ʽӿ�
 �������  : pst_mac_user : Userָ��
 �������  :
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��17��
    ��    ��   : g00306640
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_stop_stat_rate(dmac_user_stru *pst_dmac_user)
{
    dmac_user_rate_info_stru   *pst_user_info;
    pst_user_info = &pst_dmac_user->st_user_rate_info;

    if (OAL_TRUE == pst_user_info->en_dmac_rate_stat_flag)
    {
        pst_user_info->en_dmac_rate_stat_flag = OAL_FALSE;
        /* ���ͳ����Ϣ */
        OAL_MEMZERO(&pst_user_info->st_dmac_rate_stat_info, OAL_SIZEOF(dmac_rate_stat_info_stru));
    }
    return OAL_SUCC;
}
#endif

/*lint -e19*/
oal_module_symbol(dmac_rx_process_data_event);
#if (!defined(_PRE_PRODUCT_ID_HI110X_DEV))
oal_module_symbol(g_ast_rx_fcs_statistic);     /* add for phy(2) */
#endif
/*lint +e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

