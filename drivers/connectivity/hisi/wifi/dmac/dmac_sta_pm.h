/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_sta_pm.h
  �� �� ��   : ����
  ��    ��   : l00280485
  ��������   : 2014��11��25��
  ����޸�   :
  ��������   : dmac_sta_pm.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��25��
    ��    ��   : l00280485
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __DMAC_STS_PM_H__
#define __DMAC_STS_PM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_STA_PM
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_device.h"
#include "mac_frame.h"
#include "mac_pm.h"
#include "dmac_vap.h"
#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_STA_PM_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define WLAN_NBBY      8
//#define WLAN_TIM_ISSET(a,i) ((a)[(i)/WLAN_NBBY] & (1<<((i)%WLAN_NBBY)))
#define WLAN_TIM_ISSET(a,i) ((a)[(i)>>3] & (1<<((i)&0x7)))
#define LISTEN_INTERVAL_TO_DITM_TIMES   4
#define MIN_ACTIVITY_TIME_OUT 20000   /* 500 ms */
#define MAX_ACTIVITY_TIME_OUT 20000 /* 10 sec */
#define WLAN_PS_KEEPALIVE_MAX_NUM   300 /* 300 DTIM1 interval*/
#define WLAN_MAX_NULL_SENT_NUM      10  /* NULL֡����ش����� */
#define STA_GET_PM_STATE(_pst_handler)    ((_pst_handler)->p_mac_fsm->uc_cur_state)/* ��ȡ��ǰ״̬����״̬ */
#define DMAC_TIMER_DOZE_TRANS_FAIL_NUM        10
#define DMAC_STATE_DOZE_TRANS_FAIL_NUM        2          //����N����dozeʧ�����ά��
#define DMAC_BEACON_DOZE_TRANS_FAIL_NUM       2
#define DMAC_BEACON_TIMEOUT_MAX_TIME          1000 //�ղ���beacon���˯��ʱ��,��λms
#define DMAC_RECE_MCAST_TIMEOUT               20   //���չ㲥�鲥֡��ʱ--û�յ�

#if defined(_PRE_DEBUG_MODE)
#define DMAC_STA_UAPSD_STATS_INCR(_member)    ((_member)++)
#define DMAC_STA_PSM_STATS_INCR(_member)      ((_member)++)
#elif defined(_PRE_PSM_DEBUG_MODE)
#define DMAC_STA_PSM_STATS_INCR(_member)    ((_member)++)
#define DMAC_STA_UAPSD_STATS_INCR(_member)
#else
#define DMAC_STA_UAPSD_STATS_INCR(_member)
#define DMAC_STA_PSM_STATS_INCR(_member)
#endif
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* TIM processing result */
typedef enum
{
    DMAC_TIM_IS_SET  = 1,
    DMAC_DTIM_IS_SET = 2,

    DMAC_TIM_PROC_BUTT
} dmac_tim_proc_enum;

typedef enum {
    STA_PWR_SAVE_STATE_ACTIVE = 0,         /* active״̬ */
    STA_PWR_SAVE_STATE_DOZE,               /* doze״̬ */
    STA_PWR_SAVE_STATE_AWAKE,              /* wake״̬*/

    STA_PWR_SAVE_STATE_BUTT                /*���״̬*/
} sta_pwr_save_state_info;

typedef enum {
    STA_PWR_EVENT_TX_DATA = 0,              /* DOZE״̬�µķ����¼� */
    STA_PWR_EVENT_TBTT,                     /* DOZE״̬�µ�TBTT�¼� */
    STA_PWR_EVENT_FORCE_AWAKE,              /* DOZE״̬�º�tbtt���ѻ�û����,�ֶ�ǿ�ƻ��� */
    STA_PWR_EVENT_RX_UCAST,                 /* AWAKE״̬�½��յ���  */
    STA_PWR_EVENT_LAST_MCAST = 4,           /* AWAKE״̬�����һ���鲥/�㲥 */
    STA_PWR_EVENT_TIM,                      /* AWAKE״̬�µ�TIM�¼� */
    STA_PWR_EVENT_DTIM,                     /* AWAKE״̬�µ�DTIM�¼� */
    STA_PWR_EVENT_NORMAL_SLEEP,
    STA_PWR_EVENT_BEACON_TIMEOUT  = 8,      /* AWAKE״̬��˯���¼� */
    STA_PWR_EVENT_SEND_NULL_SUCCESS,        /* ����״̬�¶���NULL֡���ͳɹ��¼� */
    STA_PWR_EVENT_TIMEOUT,                  /* ACTIVE/AWAKE״̬�³�ʱ�¼� */
    STA_PWR_EVENT_KEEPALIVE,                /* ACTIVE״̬�·ǽ���ģʽ��keepalive�¼� */
    STA_PWR_EVENT_NO_POWERSAVE = 12,        /* DOZE/AWAKE״̬�·ǽ���ģʽ */
    STA_PWR_EVENT_P2P_SLEEP,                /* P2P SLEEP */
    STA_PWR_EVENT_P2P_AWAKE,                /* P2P AWAKE */
    STA_PWR_EVENT_DETATCH,                  /* ���ٵ͹���״̬���¼� */
    STA_PWR_EVENT_DEASSOCIATE,              /* ȥ����*/
    STA_PWR_EVENT_TX_MGMT,                  /* ���͹���֡����ǰ�� */
    STA_PWR_EVENT_TX_COMPLETE,              /* ��������¼� */
    STA_PWR_EVENT_BUTT
}sta_pwr_save_event;


typedef enum _PM_DEBUG_MSG_TYPE_{
    PM_MSG_WAKE_TO_ACTIVE = 0,
    PM_MSG_WAKE_TO_DOZE,
    PM_MSG_ACTIVE_TO_DOZE,
    PM_MSG_TBTT_CNT, /* tbtt count */
    PM_MSG_PSM_BEACON_CNT,
    PM_MSG_BEACON_TIMEOUT_CNT,
    PM_MSG_PROCESS_DOZE_CNT,
    PM_MSG_BCN_TOUT_SLEEP,
    PM_MSG_DEEP_DOZE_CNT = 8,
    PM_MSG_LIGHT_DOZE_CNT,
    PM_MSG_LAST_DTIM_SLEEP,
    PM_MSG_SCAN_DIS_ALLOW_SLEEP,
    PM_MSG_DBAC_DIS_ALLOW_SLEEP,
    PM_MSG_FREQ_DIS_ALLOW_SLEEP,
    PM_MSG_BCNTIMOUT_DIS_ALLOW_SLEEP,
    PM_MSG_HOST_AWAKE,
    PM_MSG_DTIM_AWAKE,
    PM_MSG_TIM_AWAKE,
    /* ��ʱ��ʱ������ */
    PM_MSG_PSM_TIMEOUT_PM_OFF  = 18,
    PM_MSG_PSM_TIMEOUT_QUEUE_NO_EMPTY,
    PM_MSG_PSM_RESTART_A,
    PM_MSG_PSM_RESTART_B,
    PM_MSG_PSM_RESTART_C,
    PM_MSG_PSM_TIMEOUT_PKT_CNT  =23,
    PM_MSG_PSM_RESTART_P2P_PAUSE,
    PM_MSG_PSM_P2P_SLEEP,
    PM_MSG_PSM_P2P_AWAKE,
    PM_MSG_PSM_P2P_PS,
    PM_MSG_NULL_NOT_SLEEP,
    PM_MSG_DTIM_TMOUT_SLEEP,
    PM_MSG_COUNT = 30
}PM_DEBUG_MSG_TYPE;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern    oal_uint32   g_lightsleep_fe_awake_cnt;
extern    oal_uint32   g_deepsleep_fe_awake_cnt;
/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    oal_uint8    en_active_null_wait : 1; /* STA����NULL֡��AP��ʾ����ACTIVE ״̬ */
    oal_uint8    en_doze_null_wait  :1;   /* STA����NULL֡��AP��ʾ����doze״̬*/
} dmac_vap_null_wait_stru;

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    oal_uint32 ul_wmmpssta_tacdl;       /* Trigger enabled Downlink traffic exception.          */
    oal_uint32 ul_wmmpssta_dacul;        /* Delivery enabled Uplink traffic exception.             */
    oal_uint32 ul_wmmpssta_spsw;        /* Wait for service period start.                       */
    oal_uint32 ul_wmmpssta_sps;         /* Service period start                                 */
    oal_uint32 ul_wmmpssta_spe;         /* Service period end                                   */
    oal_uint32 ul_wmmpssta_trigsp;      /* Trigger service period                               */
    oal_uint32 ul_wmmpssta_trspnr;      /* Trigger service period is not required               */
}dmac_wmmps_info_stru;

#elif defined(_PRE_PSM_DEBUG_MODE)

#endif

typedef enum
{
    STA_PS_DEEP_SLEEP   = 0,
    STA_PS_LIGHT_SLEEP  = 1
}ps_mode_state_enum;

typedef  enum
{
    DMAC_SP_NOT_IN_PROGRESS         = 0,
    DMAC_SP_WAIT_START              = 1,
    DMAC_SP_IN_PROGRESS             = 2,
    DMAC_SP_UAPSD_STAT_BUTT
}dmac_uapsd_sp_stat_sta_enum;

/* STA ��pm����ṹ����*/
typedef struct _mac_sta_pm_handler
{
    mac_fsm_stru                    *p_mac_fsm;                                 /*����״̬��*/
    frw_timeout_stru                st_inactive_timer;                          /* ��ʱ�� */
    frw_timeout_stru                st_mcast_timer;                             /* ���չ㲥�鲥��ʱ��ʱ�� */

    oal_uint32                      ul_tx_rx_activity_cnt;                      /* ACTIVEͳ��ֵ���ɳ�ʱ����DOZE��λ */
    oal_uint32                      ul_activity_timeout;                        /* ˯�߳�ʱ��ʱ����ʱʱ�� */
    oal_uint32                      ul_ps_keepalive_cnt;                        /* STA�����״̬��keepalive����ͳ�ƽ���beacon��*/
    oal_uint32                      ul_ps_keepalive_max_num;                    /* STA�����״̬��keepalive����������beacon�� */

    oal_uint8                       uc_vap_ps_mode;                             /*  sta��ǰʡ��ģʽ */

    oal_uint8                       en_beacon_frame_wait            :1;         /* ��ʾ����beacon֡ */
    oal_uint8                       en_more_data_expected           :1;         /* ��ʾAP���и���Ļ���֡ */
    oal_uint8                       en_send_null_delay              :1;         /* �ӳٷ���NULL֡���� */
    oal_uint8                       en_ps_deep_sleep                :1;         /* �Ƿ���doze�µ���˯ */
    oal_uint8                       en_direct_change_to_active      :1;         /* FASTģʽ��ֱ�ӻ��ѵ����ݰ���active״̬ */
    oal_uint8                       en_hw_ps_enable                 :1;         /* ����ȫϵͳ�͹���/Э��ջ�͹��� */
    oal_uint8                       en_ps_back_active_pause         :1;         /* ps back �ӳٷ��ͻ���null֡ */
    oal_uint8                       en_ps_back_doze_pause           :1;         /* ps back �ӳٷ���˯��null֡ */

    oal_uint8                       uc_timer_fail_doze_trans_cnt;               /* ��ʱ�����ڷ�null��dozeʧ�ܴ��� */
    oal_uint8                       uc_state_fail_doze_trans_cnt;               /* ��dozeʱ,��������������ʧ�ܼ��� */

    oal_uint8                       uc_beacon_fail_doze_trans_cnt;              /* ��beacon ͶƱ˯��ȴȴ�޷�˯��ȥ�ļ��� */
    oal_uint8                       uc_doze_event;                              /* ��¼��״̬���¼����� */
    oal_uint8                       uc_awake_event;
    oal_uint8                       uc_active_event;

#ifdef _PRE_WLAN_FEATURE_STA_UAPSD
    oal_uint8                       uc_eosp_timeout_cnt;                        /* uapsdʡ����TBTT������ */
    oal_uint8                       uc_uaspd_sp_status;                         /* UAPSD��״̬ */
#endif
    oal_uint8                       uc_doze_null_retran_cnt;
    oal_uint8                       uc_active_null_retran_cnt;

    dmac_vap_null_wait_stru         st_null_wait;                               /* STA����NULL֡�л�״̬ʱ����״̬NULL֡�ȴ�״̬�Ľṹ��*/
#ifdef _PRE_DEBUG_MODE
    dmac_wmmps_info_stru            st_wmmps_info;                              /* STA��uapsd��ά����Ϣ */
#endif
    oal_uint32                      aul_pmDebugCount[PM_MSG_COUNT];
    oal_uint32                      ul_psm_pkt_cnt;
    oal_uint8                       uc_psm_timer_restart_cnt;                   /* ����˯�߶�ʱ����count */
    oal_uint8                       uc_can_sta_sleep;                           /* Э�������е�doze,�Ƿ���ͶƱ˯�� */
    oal_uint16                      us_mcast_timeout;                           /* ���չ㲥�鲥��ʱ����ʱʱ�� */
} mac_sta_pm_handler_stru;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_void dmac_pm_sta_state_trans(mac_sta_pm_handler_stru* pst_handler,oal_uint8 uc_state, oal_uint16 us_event);
extern oal_uint32 dmac_pm_sta_post_event(oal_void* pst_oshandler, oal_uint16 us_type, oal_uint16 us_datalen, oal_uint8* pst_data);
extern mac_sta_pm_handler_stru * dmac_pm_sta_attach(oal_void* pst_oshandler);
extern oal_void dmac_pm_sta_detach(oal_void* pst_oshandler);
extern oal_void dmac_sta_initialize_psm_globals(mac_sta_pm_handler_stru *p_handler);
extern oal_void dmac_pm_enable_front_end(mac_device_stru   *pst_mac_device, oal_uint8 uc_enable_paldo);
extern oal_void dmac_pm_key_info_dump(dmac_vap_stru  *pst_dmac_vap);
extern oal_void dmac_pm_change_to_active_state(dmac_vap_stru *pst_dmac_vap,mac_sta_pm_handler_stru *pst_pm_handler,oal_uint8 uc_event);

#endif /* _PRE_WLAN_FEATURE_STA_PM*/
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of dmac_sts_pm.h */
