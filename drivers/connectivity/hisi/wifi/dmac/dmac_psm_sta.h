/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_psm_sta.h
  �� �� ��   : ����
  ��    ��   : l00280485
  ��������   : 2014��11��25��
  ����޸�   :
  ��������   : dmac_psm_sta.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��25��
    ��    ��   : l00280485
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_PSM_STA_H__
#define __DMAC_PSM_STA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
#include "dmac_uapsd_sta.h"
#else
#include "dmac_sta_pm.h"
#include "dmac_ext_if.h"
#include "dmac_tx_bss_comm.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_PSM_STA_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define DMAC_DEFAULT_DTIM_LISTEN_DIFF 4        // DTIM LISTEN INTERVAL �Ƚ��м���
#define DMAC_DEFAULT_LISTEN_INTERVAL  2        // Ĭ��listen interval

/* ��һ����ʱTIMEOUT * CNT �������100ms�����򶪰��ʸ�,����� */
#define DMAC_PSM_TIMER_IDLE_TIMEOUT     50
#define DMAC_PSM_TIMER_MIDIUM_TIMEOUT   100
#define DMAC_PSM_TIMER_BUSY_TIMEOUT     200
#define DMAC_PSM_TIMER_IDLE_CNT         4
#define DMAC_PSM_TIMER_MIDIUM_CNT       2
#define DMAC_PSM_TIMER_BUSY_CNT         2


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern oal_uint32 g_device_wlan_pm_timeout;
extern oal_uint32 g_pm_timer_restart_cnt;
extern oal_uint8  g_uc_max_powersave;

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
struct dmac_tim_ie {
    oal_uint8 uc_tim_ie;               /* MAC_EID_TIM */
    oal_uint8 uc_tim_len;
    oal_uint8 uc_dtim_count;           /* DTIM count */
    oal_uint8 uc_dtim_period;          /* DTIM period */
    oal_uint8 uc_tim_bitctl;           /* bitmap control */
    oal_uint8 auc_tim_bitmap[1];        /* variable-length bitmap */
}__OAL_DECLARE_PACKED;
typedef struct dmac_tim_ie dmac_tim_ie_stru;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : dmac_psm_sta_incr_activity_cnt
 ��������  : activity_cnt++
 �������  : pst_sta_pm_handle:״̬���ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_psm_sta_incr_activity_cnt(mac_sta_pm_handler_stru *pst_sta_pm_handle)
{
    pst_sta_pm_handle->ul_tx_rx_activity_cnt++;
}
/*****************************************************************************
 �� �� ��  : dmac_psm_get_more_data_sta
 ��������  : ����Ƿ���moredata
 �������  : pst_sta_pm_handle:״̬���ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_psm_get_more_data_sta(mac_ieee80211_frame_stru *pst_frame_hdr)
{
    return (oal_uint8)(pst_frame_hdr->st_frame_control.bit_more_data);

}
/*****************************************************************************
 �� �� ��  : dmac_psm_sta_reset_activity_cnt
 ��������  : reset activity cnt
 �������  : pst_sta_pm_handle:״̬���ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_psm_sta_reset_activity_cnt(mac_sta_pm_handler_stru *pst_sta_pm_handle)
{
    pst_sta_pm_handle->ul_tx_rx_activity_cnt = 0;
}
/*****************************************************************************
 �� �� ��  : dmac_psm_sta_is_activity_cnt_zero
 ��������  : �ж� activity cnt �Ƿ�Ϊ0
 �������  : pst_sta_pm_handle:״̬���ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_psm_sta_is_activity_cnt_zero(mac_sta_pm_handler_stru *pst_sta_pm_handle)
{
    if (0 == pst_sta_pm_handle->ul_tx_rx_activity_cnt)
    {
      return OAL_TRUE;
    }
    return OAL_FALSE;
}
/*****************************************************************************
 �� �� ��  : dmac_is_legacy_ac_present
 ��������  : sta���ж������Ƿ��д�ͳ��ac
 �������  : pst_dmac_vap:dmac_vap �ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_legacy_ac_present(dmac_vap_stru *pst_dmac_vap)
{
    oal_uint8               uc_ac;
    mac_cfg_uapsd_sta_stru  st_uapsd_cfg_sta;

    st_uapsd_cfg_sta = pst_dmac_vap->st_vap_base_info.st_sta_uapsd_cfg;

    for(uc_ac = 0; uc_ac < WLAN_WME_AC_BUTT; uc_ac++)
    {
        if((st_uapsd_cfg_sta.uc_trigger_enabled[uc_ac] == 0) &&
           (st_uapsd_cfg_sta.uc_delivery_enabled[uc_ac] == 0))
           return OAL_TRUE;
    }

    return OAL_FALSE;
}


/*****************************************************************************
 �� �� ��  : dmac_is_any_legacy_ac_present
 ��������  : checks if any legacy AC is present for the STA
 �������  : pst_dmac_vap:dmac_vap �ṹ�� pst_netbuf:netbuf�ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��20��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_any_legacy_ac_present(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if(OAL_TRUE == dmac_is_uapsd_capable(pst_dmac_vap))
    {
        return dmac_is_legacy_ac_present(pst_dmac_vap);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */

    return OAL_TRUE;
}

/* This function checks if a PS Poll Response is pending */
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_ps_poll_rsp_pending(dmac_vap_stru *pst_dmac_vap)
{
    return pst_dmac_vap->uc_ps_poll_pending;
}

/* This function sets the PS Poll Response pending flag */
OAL_STATIC OAL_INLINE oal_void dmac_set_ps_poll_rsp_pending(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_val)
{
    pst_dmac_vap->uc_ps_poll_pending = uc_val;
}

/*****************************************************************************
 �� �� ��  : dmac_process_rx_process_data_sta_prot
 ��������  : ��������Э�鴦�����֡(uapsd p2p���ܵ�)
 �������  : pst_dmac_vap:dmac_vap �ṹ�� pst_netbuf:netbuf�ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��20��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_process_rx_process_data_sta_prot(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_buf)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if (OAL_TRUE == dmac_is_uapsd_capable(pst_dmac_vap))
    {
        dmac_uapsd_rx_process_data_sta(pst_dmac_vap, pst_buf);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */

#ifdef _PRE_WLAN_FEATURE_P2P
    dmac_set_ps_poll_rsp_pending(pst_dmac_vap, OAL_FALSE);
#endif

}
/*****************************************************************************
 �� �� ��  : dmac_psm_process_tx_process_data_sta_prot
 ��������  : ��������Э�鴦����֡(uapsd p2p���ܵ�)
 �������  : pst_dmac_vap:dmac_vap �ṹ�� pst_tx_ctl:tx cb�ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��20��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_psm_process_tx_process_data_sta_prot(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if (OAL_TRUE == dmac_is_uapsd_capable(pst_dmac_vap))
    {
        return dmac_uapsd_tx_process_data_sta(pst_dmac_vap, pst_tx_ctl);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */

    return STA_PWR_SAVE_STATE_ACTIVE;
}
/*****************************************************************************
 �� �� ��  : dmac_psm_process_tx_complete_sta_prot
 ��������  : ��������Э�鴦��������ж�(uapsd p2p���ܵ�)
 �������  : pst_dmac_vap:dmac_vap �ṹ�� pst_tx_ctl:tx cb�ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��20��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_psm_process_tx_complete_sta_prot(dmac_vap_stru *pst_dmac_vap, oal_uint8  uc_dscr_status, oal_netbuf_stru *pst_netbuf)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if(OAL_TRUE == dmac_is_uapsd_capable(pst_dmac_vap))
    {
        dmac_uapsd_process_tx_complete_sta(pst_dmac_vap, uc_dscr_status, pst_netbuf);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */
}
/*****************************************************************************
 �� �� ��  : dmac_psm_process_tx_complete_sta_prot
 ��������  : handles TIM set event for STA mode based on the protocol
 �������  : pst_dmac_vap:dmac_vap �ṹ�� pst_tx_ctl:tx cb�ṹ��
 �������  : OAL_TRUE/OAL_FALSE
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��20��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_psm_process_tim_set_sta_prot(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    if(OAL_TRUE == dmac_is_uapsd_capable(pst_dmac_vap))
    {
        dmac_uapsd_trigger_sp_sta(pst_dmac_vap);
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */
}
/*****************************************************************************
 �� �� ��  : dmac_is_sta_fast_ps_enabled
 ��������  : �Ƿ���fast ps ����ģʽ
 �������  : pst_dmac_vap dmac_vap �ṹ��
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��19��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 dmac_is_sta_fast_ps_enabled(mac_sta_pm_handler_stru  *pst_sta_pm_handle)
{
    if((oal_uint8)(pst_sta_pm_handle->uc_vap_ps_mode)  >= (oal_uint8)MIN_PSPOLL_PS)
    {
        return OAL_FALSE;
    }
    else
    {
        return OAL_TRUE;
    }
}
/*****************************************************************************
 �� �� ��  : dmac_can_sta_doze_prot
 ��������  : This function checks if the STA can doze based on the protocol defined
 �������  : pst_dmac_vap dmac_vap �ṹ��
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE  oal_uint8 dmac_can_sta_doze_prot(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    mac_sta_pm_handler_stru  *pst_mac_sta_pm_handle;

    pst_mac_sta_pm_handle = (mac_sta_pm_handler_stru *)(pst_dmac_vap->pst_pm_handler);

    /* If the AP is UAPSD capable and UAPSD service period is in progress    */
    /* or STA is waiting for UAPSD service period to start the STA cannot go */
    /* to doze mode.                                                         */
    if(OAL_TRUE == dmac_is_uapsd_capable(pst_dmac_vap))
    {
        if (OAL_FALSE == dmac_is_uapsd_sp_not_in_progress(pst_mac_sta_pm_handle))
        {
            return OAL_FALSE;
        }
    }
#endif /* _PRE_WLAN_FEATURE_STA_UAPSD */
    return OAL_TRUE;
}
/*****************************************************************************
 �� �� ��  : dmac_send_ps_poll_to_AP_prot
 ��������  : Set the P2P PS Poll pending flag whenever a PS-Poll frame is sent to AP
 �������  : pst_dmac_vap dmac_vap �ṹ��
 �������  : ��
 �� �� ֵ  : oal_uint8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��1��
    ��    ��   : l00280485
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void dmac_send_ps_poll_to_ap_prot(dmac_vap_stru *pst_dmac_vap)
{
#ifdef _PRE_WLAN_FEATURE_P2P
    dmac_set_ps_poll_rsp_pending(pst_dmac_vap, OAL_TRUE);
#endif /* #if  defined(_PRE_WLAN_FEATURE_P2P)*/
}


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_void dmac_psm_tx_set_power_mgmt_bit(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl);

extern oal_void dmac_psm_tx_complete_sta(dmac_vap_stru *pst_dmac_vap, hal_tx_dscr_stru  *pst_dscr, oal_netbuf_stru *pst_netbuf);

extern oal_void dmac_psm_process_tbtt_sta(dmac_vap_stru *pst_dmac_vap,mac_device_stru  *pst_mac_device);

extern oal_void  dmac_psm_rx_process_data_sta(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_buf);

extern oal_uint8 dmac_psm_tx_process_data_sta(dmac_vap_stru *pst_dmac_vap, mac_tx_ctl_stru *pst_tx_ctl);
extern oal_void dmac_psm_max_powersave_enable(mac_device_stru *pst_mac_device);
extern oal_void dmac_psm_update_dtime_period(mac_vap_stru *pst_mac_vap, oal_uint8 uc_mib_dtim_period,oal_uint32 ul_beacon_period);
extern oal_void dmac_psm_update_keepalive(dmac_vap_stru *pst_dmac_vap);

extern oal_uint32 dmac_send_null_frame_to_ap(dmac_vap_stru *pst_dmac_vap, oal_uint8  uc_psm, oal_bool_enum_uint8 en_qos);
extern oal_uint32 dmac_send_pspoll_to_ap(dmac_vap_stru *pst_dmac_vap);

extern oal_void dmac_psm_start_activity_timer(dmac_vap_stru *pst_dmac_vap, mac_sta_pm_handler_stru *pst_sta_pm_handle);
extern oal_uint32 dmac_psm_is_tim_dtim_set(dmac_vap_stru *pst_dmac_vap, oal_uint8* puc_tim_elm);
extern oal_void dmac_psm_process_tim_elm(dmac_vap_stru *pst_dmac_vap, oal_netbuf_stru *pst_netbuf);
extern oal_void  dmac_psm_recover_ps_abb_state(oal_void);
extern oal_uint32 dmac_psm_alarm_callback(void *p_arg);
extern oal_uint8  dmac_psm_get_state(dmac_vap_stru* pst_dmac_vap);
extern oal_uint8  dmac_psm_is_tid_queues_empty(dmac_vap_stru  *pst_dmac_vap);
extern oal_uint32 dmac_psm_process_fast_ps_state_change(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_psm);
extern oal_void dmac_psm_init_null_frm_cnt(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_psm_inc_null_frm_ofdm_succ(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_psm_dec_null_frm_ofdm_succ(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_psm_inc_null_frm(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_psm_dec_null_frm(dmac_vap_stru *pst_dmac_vap);
extern oal_void dmac_psm_sync_dtim_count(dmac_vap_stru *pst_dmac_vap, oal_uint8 uc_dtim_count);

#endif/*_PRE_WLAN_FEATURE_STA_PM*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_psm_sta.h */
