/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_uapsd_sta.h
  �� �� ��   : ����
  ��    ��   : l00280485
  ��������   : 2014��12��19��
  ����޸�   :
  ��������   : dmac_uapsd_sta.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��19��
    ��    ��   : l00280485
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_UAPSD_STA_H__
#define __DMAC_UAPSD_STA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "dmac_ext_if.h"
#include "dmac_sta_pm.h"
#include "dmac_tx_bss_comm.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_UAPSD_STA_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* TAG-ITTIAM����������� */
#define DMAC_STA_EOSP_TIMEOUT_CNT   2      /* 2 TBTTS */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_is_uapsd_capable
 ��������  : ���Զ�ap�Ƿ���UAPSD���� && �Ƿ�staut����UAPSD����
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_uapsd_capable(dmac_vap_stru *pst_dmac_vap)
{
    /* ap֧�ֲ���sta֧�ֲŽ�uapsd�Ĵ����߼� */
    if ((pst_dmac_vap->st_vap_base_info.uc_uapsd_cap) && (pst_dmac_vap->st_vap_base_info.st_sta_uapsd_cfg.uc_max_sp_len != 0))
    {
        return OAL_TRUE;
    }

    return OAL_FALSE;
}

/*****************************************************************************
 �� �� ��  : dmac_is_delivery_enabled
 ��������  : ĳ��ac�Ƿ�delivery enabled
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_delivery_enabled(dmac_vap_stru *pst_dmac_vap,  oal_uint8  uc_tid)
{
    oal_uint8                uc_ac;
    mac_cfg_uapsd_sta_stru   st_uapsd_cfg_sta;

    uc_ac = WLAN_WME_TID_TO_AC(uc_tid);
    st_uapsd_cfg_sta = pst_dmac_vap->st_vap_base_info.st_sta_uapsd_cfg;
    return st_uapsd_cfg_sta.uc_delivery_enabled[uc_ac];
}
/*****************************************************************************
 �� �� ��  : dmac_is_trigger_enabled
 ��������  : ĳ��ac�Ƿ�trigger enabled
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_trigger_enabled(dmac_vap_stru *pst_dmac_vap, oal_uint8  uc_tid)
{
    oal_uint8                uc_ac;
    mac_cfg_uapsd_sta_stru   st_uapsd_cfg_sta;

    uc_ac = WLAN_WME_TID_TO_AC(uc_tid);
    st_uapsd_cfg_sta = pst_dmac_vap->st_vap_base_info.st_sta_uapsd_cfg;
    return st_uapsd_cfg_sta.uc_trigger_enabled[uc_ac];
}
/*****************************************************************************
 �� �� ��  : dmac_is_trigger_frame
 ��������  : ���ĳ��֡�Ƿ��� WMM PS trigger frame
 �������  :
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE  oal_uint8 dmac_is_trigger_frame(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf, oal_uint8  uc_tid)
{
    mac_ieee80211_frame_stru            *pst_mac_header;
    oal_uint8                            uc_subtype;

    pst_mac_header = (mac_ieee80211_frame_stru *)oal_netbuf_header(pst_netbuf);
    uc_subtype = mac_get_frame_sub_type((oal_uint8 *)pst_mac_header);

    /* A trigger frame is a QoS Data or QoS Null frame from a WMM STA in     */
    /* power save mode associated with an AC the WMM STA has configured to   */
    /* be a trigger-enabled AC.                                              */
    if((uc_subtype == (WLAN_FC0_SUBTYPE_QOS | WLAN_FC0_TYPE_DATA)) || (uc_subtype == (WLAN_FC0_SUBTYPE_QOS_NULL | WLAN_FC0_TYPE_DATA)))
    {
        if(dmac_is_trigger_enabled(pst_dmac_vap, uc_tid) == OAL_TRUE)
        {
            return OAL_TRUE;
        }
    }
    return OAL_FALSE;
}
/*****************************************************************************
 �� �� ��  : dmac_get_eosp
 ��������  : ����ĳ��QOS֡���EOSP BIT.
 �������  : pst_buf:netbuf�ṹ��
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��20��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8  dmac_get_eosp(oal_netbuf_stru *pst_buf)
{
    mac_ieee80211_qos_frame_stru *pst_qos_frame_hdr;

    pst_qos_frame_hdr = (mac_ieee80211_qos_frame_stru *)OAL_NETBUF_HEADER(pst_buf);
    return pst_qos_frame_hdr->bit_qc_eosp;

}
/*****************************************************************************
 �� �� ��  : dmac_get_eosp
 ��������  : ���uapsd service period �Ƿ� in progress
 �������  : pst_mac_sta_pm_handle:STA PM�ṹ��
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��20��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_uapsd_sp_not_in_progress(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    if(DMAC_SP_NOT_IN_PROGRESS == pst_mac_sta_pm_handle->uc_uaspd_sp_status)
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
}
/*****************************************************************************
 �� �� ��  : dmac_get_eosp
 ��������  : ���uapsd service period �Ƿ� WAIT START
 �������  : pst_mac_sta_pm_handle:STA PM�ṹ��
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��20��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_uapsd_sp_wait_in_progress(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    if(pst_mac_sta_pm_handle->uc_uaspd_sp_status == DMAC_SP_WAIT_START)
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : dmac_wait_uapsd_sp_start
 ��������  : This function waits for a UAPSD service period to start. Note that the
             service period will be started only after successful transmission of the
             trigger frame. In case the trigger frame is timed out the STA will try to
             retransmit a trigger frame. Also if it is already waiting for a service
             period to start or if a service period is in progress no wait is required
             and hence the flag is not set.
 �������  : pst_mac_sta_pm_handle:STA PM�ṹ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��20��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_wait_uapsd_sp_start(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    if(DMAC_SP_NOT_IN_PROGRESS == pst_mac_sta_pm_handle->uc_uaspd_sp_status)
    {
       pst_mac_sta_pm_handle->uc_uaspd_sp_status  = DMAC_SP_WAIT_START;
    }

    DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_spsw);
}
/*****************************************************************************
�� �� ��  : dmac_start_uapsd_sp
��������  : This function starts a UAPSD service period
�������  : pst_mac_sta_pm_handle:STA PM�ṹ��
�������  : ��
�� �� ֵ  : oal_void
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2014��12��20��
   ��    ��   : l00280485
   �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_start_uapsd_sp(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    pst_mac_sta_pm_handle->uc_uaspd_sp_status  = DMAC_SP_IN_PROGRESS;

    DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_sps);
}
/*****************************************************************************
�� �� ��  : dmac_start_uapsd_sp
��������  : This function stops a UAPSD service period
�������  : pst_mac_sta_pm_handle:STA PM�ṹ��
�������  : ��
�� �� ֵ  : oal_void
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2014��12��20��
   ��    ��   : l00280485
   �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_stop_uapsd_sp(mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle)
{
    pst_mac_sta_pm_handle->uc_uaspd_sp_status  = DMAC_SP_NOT_IN_PROGRESS;

    DMAC_STA_UAPSD_STATS_INCR(pst_mac_sta_pm_handle->st_wmmps_info.ul_wmmpssta_spe);
}

/*****************************************************************************
�� �� ��  : dmac_start_uapsd_sp
��������  : returns the highest priority which is trigger enabled
�������  : pst_dmac_vap:dmac vap �ṹ��
�������  : ��
�� �� ֵ  : oal_uint8
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2014��12��20��
   ��    ��   : l00280485
   �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_get_highest_trigger_enabled_priority(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_FEATURE_WLAN_STA_UAPSD
    oal_uint8 uc_tid = WLAN_TID_MAX_NUM;

    /* Check for highest priority trigger enabled AC */
    if(dmac_is_trigger_enabled(pst_dmac_vap, WLAN_TIDNO_VOICE) == OAL_TRUE)
    {
        uc_tid = WLAN_TIDNO_VOICE;
    }
    else if(dmac_is_trigger_enabled(pst_dmac_vap, WLAN_TIDNO_VIDEO) == OAL_TRUE)
    {
        uc_tid = WLAN_TIDNO_VIDEO;
    }
    else if(dmac_is_trigger_enabled(pst_dmac_vap, WLAN_TIDNO_BEST_EFFORT) == OAL_TRUE)
    {
        uc_tid = WLAN_TIDNO_BEST_EFFORT;
    }
    else if (dmac_is_trigger_enabled(pst_dmac_vap, WLAN_TIDNO_BACKGROUND) == OAL_TRUE)
    {
        uc_tid = WLAN_TIDNO_BACKGROUND;
    }

    return uc_tid;
#else
    return WLAN_TIDNO_VOICE;
#endif /* _PRE_FEATURE_WLAN_STA_UAPSD */
}
/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_void  dmac_uapsd_rx_process_data_sta(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);

extern oal_uint8 dmac_uapsd_tx_process_data_sta(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl);

extern oal_void  dmac_uapsd_process_tx_complete_sta(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_dscr_status, oal_netbuf_stru *pst_netbuf);

extern oal_void dmac_uapsd_trigger_sp_sta(dmac_vap_stru *pst_dmac_vap);

#endif /* _RE_WLAN_FEATURE_STA_UAPSD */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_uapsd_sta.h */
