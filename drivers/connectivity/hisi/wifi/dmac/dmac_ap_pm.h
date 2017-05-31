/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_ap_pm.h
  �� �� ��   : ����
  ��    ��   : zourong
  ��������   : 2014��8��18��
  ����޸�   :
  ��������   : dmac_pm.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��8��18��
    ��    ��   : zourong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_AP_PM_H__
#define __DMAC_AP_PM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PM
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_device.h"
#include "frw_ext_if.h"
#include "mac_pm.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_AP_PM_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define AP_PWR_DEFAULT_INACTIVE_TIME    10                      /*Ĭ��inactiveʱ�� minute*/
#define AP_PWR_DEFAULT_USR_CHECK_TIME   5000                    /*����Ƿ����û��ڽ���Ķ�ʱ��ʱ�� ms*/
#define AP_PWR_MAX_USR_CHECK_COUNT      30000/AP_PWR_DEFAULT_USR_CHECK_TIME          /*30s�����û������л�״̬*/



/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum {
    PWR_SAVE_STATE_WORK = 0,         /*����״̬*/
    PWR_SAVE_STATE_DEEP_SLEEP,      /*��˯״̬*/
    PWR_SAVE_STATE_WOW,             /*WOW״̬*/
    PWR_SAVE_STATE_IDLE,            /*idle״̬�����û�����*/
    PWR_SAVE_STATE_OFF,             /*�µ�״̬*/

    PWR_SAVE_STATE_BUTT             /*���״̬*/
} ap_pwr_save_state_info;

typedef enum {
    AP_PWR_EVENT_POWER_OFF = 0,     /*�µ��¼�*/
    AP_PWR_EVENT_POWER_ON,          /*�ϵ��¼�*/
    AP_PWR_EVENT_WIFI_ENABLE,       /*ʹ��wifi*/
    AP_PWR_EVENT_WIFI_DISABLE,      /*ȥʹ��wifi*/
    AP_PWR_EVENT_NO_USR,            /*���û�����*/
    AP_PWR_EVENT_USR_ASSOC,         /*�û������¼�*/
    AP_PWR_EVENT_INACTIVE,          /*VAP����Ծ*/
    AP_PWR_EVENT_ACTIVE,            /*VAP����*/
    AP_PWR_EVENT_WOW_WAKE,          /* GPIO����WOW */

    AP_PWR_EVENT_BUTT
}ap_pwr_save_event;


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
/*pm����ṹ����*/
typedef struct _mac_pm_handler{
    mac_fsm_stru         *p_mac_fsm;               /*����״̬��*/
    oal_uint32           ul_pwr_arbiter_id;        /*arbiter id*/
    oal_uint32           bit_pwr_sleep_en:1,       /*�Զ�˯��ʹ��*/
                         bit_pwr_wow_en:1,         /*wow����ʹ��*/
                         bit_pwr_siso_en:1,        /*�Զ���ͨ��ģʽʹ��,��û���û����������ϵ�ʱ�л�*/
                         bit_rsv:29;
   oal_uint32            ul_max_inactive_time;    /*work̬����󲻻�Ծʱ��*/
   oal_uint32            ul_inactive_time;        /*��������Ծʱ��*/
   oal_uint32            ul_user_check_count;     /*���û�������*/
   oal_uint32            ul_idle_beacon_txpower;   /*idle̬��beaocn txpower*/
   frw_timeout_stru      st_inactive_timer;       /*��Ծ��ⶨʱ��,ͬʱ����Ϊ�Ƿ����û��ļ�鶨ʱ��*/
} mac_pm_handler_stru;


typedef struct
{
    oal_uint16                       us_type;         /* �¼����� */
    oal_uint16                       us_data_len;     /* �¼�Я�����ݳ��� */
    oal_uint32                       ul_data[1];      /* ���ݳ���С�ڵ���4�ֽڣ�ֱ�ӳ�������,����4�ֽڣ���һ��ָ�����ݵ�ָ�� */
}mac_pm_event_stru;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern mac_pm_handler_stru* dmac_pm_ap_attach(oal_void* pst_oshandler);
extern oal_void dmac_pm_ap_deattach(oal_void* pst_oshandler);
extern oal_uint32 dmac_pm_post_event(oal_void* pst_oshandler, oal_uint16 us_type, oal_uint16 us_datalen, oal_uint8* pst_data);
extern oal_uint8 dmac_pm_vap_current_state(oal_void* pst_oshandler);
extern oal_uint32  ap_pm_wow_host_wake_event(frw_event_mem_stru *pst_event_mem);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_fsm.h */
