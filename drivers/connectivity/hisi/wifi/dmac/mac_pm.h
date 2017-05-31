/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mac_pm.h
  �� �� ��   : ����
  ��    ��   : zourong
  ��������   : 2014��8��18��
  ����޸�   :
  ��������   : mac_pm.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��8��18��
    ��    ��   : zourong
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __MAC_PM_H__
#define __MAC_PM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if defined(_PRE_WLAN_FEATURE_PM) || defined(_PRE_WLAN_FEATURE_STA_PM)
/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_PM_H
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MAC_FSM_MAX_NAME    32  /*״̬������󳤶�*/
#define MAC_FSM_MAX_STATES 100
#define MAC_FSM_MAX_EVENTS 100
#define MAC_FSM_STATE_NONE 255 /* invalid state */
#define MAC_FSM_EVENT_NONE 255 /* invalid event */

#define MAC_PM_ARBITER_MAX_REQUESTORS   16      /*�������ٲ�����Ŀ*/
#define MAC_PM_ARBITER_MAX_REQ_NAME     16      /*�����ٲ���������󳤶�*/
#define MAC_PWR_ARBITER_ID_INVALID      255     /* invalid arbiter id */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum {
    MAC_PWR_ARBITER_TYPE_INVALID = 0,  /*�Ƿ�����*/
    MAC_PWR_ARBITER_TYPE_AP,           /*AP����*/
    MAC_PWR_ARBITER_TYPE_STA,          /*STA����*/
    MAC_PWR_ARBITER_TYPE_P2P,          /*P2P����*/

    MAC_PWR_ARBITER_TYPE_BUTT
} mac_pm_arbiter_type_enum;

/*device��״̬ö�٣�VAP�Ľ���״̬��device�Ľ���״̬Ҫ��ӳ�䣬����AP����vap��sta����VAP
P2P����vap��״̬�������ж��壬���ͨ���ٲù�һ��device��״̬*/
typedef enum {
    DEV_PWR_STATE_WORK = 0,         /*����״̬*/
    DEV_PWR_STATE_DEEP_SLEEP,      /*��˯״̬*/
    DEV_PWR_STATE_WOW,             /*WOW״̬*/
    DEV_PWR_STATE_IDLE,            /*idle״̬�����û�����*/
    DEV_PWR_STATE_OFF,             /*�µ�״̬*/

    DEV_PWR_STATE_BUTT             /*���״̬*/
} device_pwr_state_enum;

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
typedef struct _mac_pwr_event_info{
    oal_uint32           ul_event_id;           /*eventö��ֵ,ÿ״̬���Լ�����*/
    const oal_int8      *auc_event_name;         /*event����*/
}mac_pwr_event_info;

/*״̬��Ϣ�ṹ����*/
typedef struct __mac_fsm_state_info{
    oal_uint32          state;                   /*״̬ID*/
    const oal_int8      *name;                   /*״̬��*/
    oal_void (*mac_fsm_entry)(oal_void *p_ctx);  /*���뱾״̬�Ĵ���ص�����ָ��*/
    oal_void (*mac_fsm_exit)(oal_void *p_ctx);   /*�˳���״̬�Ĵ���ص�����ָ��*/
                                                 /*��״̬�µ��¼�����ص�����ָ��*/
    oal_uint32 (*mac_fsm_event)(oal_void *p_ctx,oal_uint16 event,oal_uint16 event_data_len,oal_void *event_data);
} mac_fsm_state_info;

/*״̬���ṹ����*/
typedef struct  __mac_fsm {
    oal_uint8  uc_name[MAC_FSM_MAX_NAME];              /*״̬������ */
    oal_uint8  uc_cur_state;                           /*��ǰ״̬*/
    oal_uint8  uc_prev_state;                          /*ǰһ״̬������״̬�л��¼���״̬ */
    oal_uint8  uc_num_states;                          /*״̬����״̬����*/
    oal_uint8  uc_rsv[1];
    const mac_fsm_state_info *p_state_info;
    oal_void   *p_ctx;                                 /*�����ģ�ָ��״̬��ʵ��ӵ���ߣ�mac_pm_handler_stru* */
    oal_void   *p_oshandler;                           /*ownerָ�룬ָ��VAP����device,�ɾ����״̬������*/
    oal_uint16  us_last_event;                          /*�������¼�*/
    oal_uint8  uc_rsv1[2];
} mac_fsm_stru;

struct mac_pm_arbiter_requestor_info {
    oal_uint8                   auc_id_name[MAC_PM_ARBITER_MAX_REQ_NAME]; /* names of the requestors */
    mac_pm_arbiter_type_enum    en_arbiter_type;
} ;

typedef struct _mac_pm_arbiter_state_info{
    oal_uint32               ul_state;               /*stateö��ֵ,ÿ״̬���Լ�����*/
    const oal_int8          *auc_state_name;         /*state����*/
}mac_pm_arbiter_state_info;

typedef struct _mac_pm_arbiter_info {
    oal_uint32   ul_id_bitmap;                          /*�����requestor id bitmaps */
    oal_uint32   ul_state_bitmap[DEV_PWR_STATE_BUTT];   /*ÿ��״̬��Ӧһ��bitmap*/
    oal_uint8    uc_cur_state;                          /*��ǰdevice�ĵ͹���״̬*/
    oal_uint8    uc_prev_state;                         /*ǰһdevice�ĵ͹���״̬*/
    oal_uint8    uc_requestor_num;                      /*��ǰ�����ٲ��ߵ���Ŀ*/
    oal_uint8    uc_rsv;
    mac_pm_arbiter_state_info   *pst_state_info;
    struct mac_pm_arbiter_requestor_info requestor[MAC_PM_ARBITER_MAX_REQUESTORS];  /*ͶƱ�ߵ���Ϣ��ά����*/
}mac_pm_arbiter_stru;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern mac_fsm_stru*  mac_fsm_create(oal_void*                 p_oshandle,         /*״̬��owner��ָ�룬�Ե͹���״̬����ָ��VAP�ṹ*/
                                const oal_uint8          *p_name,             /*״̬��������*/
                                oal_void                 *p_ctx,              /*״̬��context*/
                                oal_uint8                 uc_init_state,      /*��ʼ״̬*/
                                const mac_fsm_state_info *p_state_info,       /*״̬��ʵ��ָ��*/
                                oal_uint8                 uc_num_states      /*��״̬����״̬����*/
);

extern oal_void mac_fsm_destroy(mac_fsm_stru* p_fsm);
extern oal_uint32 mac_fsm_trans_to_state(mac_fsm_stru* p_fsm,oal_uint8 uc_state);

extern oal_uint32 mac_fsm_event_dispatch(mac_fsm_stru* p_fsm ,oal_uint16 us_event,
                           oal_uint16 us_event_data_len, oal_void *p_event_data);

extern oal_uint32 mac_fsm_event_dispatch(mac_fsm_stru* p_fsm ,oal_uint16 us_event,
                           oal_uint16 us_event_data_len, oal_void *p_event_data);

extern oal_uint32 mac_pm_arbiter_init(mac_device_stru* pst_device);
extern oal_uint32 mac_pm_arbiter_destroy(mac_device_stru* pst_device);
extern oal_uint32 mac_pm_arbiter_alloc_id(mac_device_stru* pst_device, oal_uint8* pst_name,mac_pm_arbiter_type_enum en_arbiter_type);
extern oal_uint32 mac_pm_arbiter_free_id(mac_device_stru* pst_device, oal_uint32 ul_arbiter_id);
extern oal_void mac_pm_arbiter_to_state(mac_device_stru *pst_device, mac_vap_stru *pst_mac_vap, oal_uint32 ul_arbiter_id,
                                            oal_uint8  uc_state_from, oal_uint8  uc_state_to);
extern oal_uint32 mac_pm_set_hal_state(mac_device_stru *pst_device,mac_vap_stru *pst_mac_vap,oal_uint8 uc_state_to);


#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of hmac_fsm.h */
