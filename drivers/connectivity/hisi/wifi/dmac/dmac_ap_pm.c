/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Dmac_PM.c
  �� �� ��   : ����
  ��    ��   : Zourong
  ��������   : 2013��6��18��
  ����޸�   :
  ��������   : ȫ�־�̬״̬����ά������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��18��
    ��    ��   : Zourong
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef _PRE_WLAN_FEATURE_PM
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "mac_device.h"
#include "mac_resource.h"
#include "mac_pm.h"
#include "dmac_ap_pm.h"
#include "dmac_vap.h"
#include "frw_timer.h"
#include "dmac_green_ap.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_AP_PM_C

OAL_STATIC oal_void ap_power_state_work_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_work_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_work_event(oal_void *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);

OAL_STATIC oal_void ap_power_state_deep_sleep_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_deep_sleep_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_deep_sleep_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);

OAL_STATIC oal_void ap_power_state_wow_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_wow_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_wow_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);

OAL_STATIC oal_void ap_power_state_idle_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_idle_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_idle_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);


OAL_STATIC oal_void ap_power_state_off_entry(oal_void *p_ctx);
OAL_STATIC oal_void ap_power_state_off_exit(oal_void *p_ctx);
OAL_STATIC oal_uint32 ap_power_state_off_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data);

OAL_STATIC oal_uint32 dmac_pm_ap_inactive_timer(oal_void* pst_arg);
OAL_STATIC oal_void dmac_pm_state_trans(mac_pm_handler_stru* pst_handler,oal_uint8 uc_state);

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* ȫ��״̬�������� */
mac_fsm_state_info  g_ap_power_fsm_info[] = {
    {
          PWR_SAVE_STATE_WORK,
          "WORK",
          ap_power_state_work_entry,
          ap_power_state_work_exit,
          ap_power_state_work_event,
    },
    {
          PWR_SAVE_STATE_DEEP_SLEEP,
          "DEEP_SLEEP",
          ap_power_state_deep_sleep_entry,
          ap_power_state_deep_sleep_exit,
          ap_power_state_deep_sleep_event,
    },
    {
          PWR_SAVE_STATE_WOW,
          "WOW",
          ap_power_state_wow_entry,
          ap_power_state_wow_exit,
          ap_power_state_wow_event,
    },
    {
          PWR_SAVE_STATE_IDLE,
          "IDLE",
          ap_power_state_idle_entry,
          ap_power_state_idle_exit,
          ap_power_state_idle_event,
    },
    {
          PWR_SAVE_STATE_OFF,
          "OFF",
          ap_power_state_off_entry,
          ap_power_state_off_exit,
          ap_power_state_off_event,
    }
};

/*VAP״̬��device״̬��ӳ���*/
oal_uint8 g_pm_state_map[PWR_SAVE_STATE_BUTT] =
{
    DEV_PWR_STATE_WORK,          //->PWR_SAVE_STATE_WORK = 0,         /*����״̬*/
    DEV_PWR_STATE_DEEP_SLEEP,    //->PWR_SAVE_STATE_DEEP_SLEEP,      /*��˯״̬*/
    DEV_PWR_STATE_WOW,           //->PWR_SAVE_STATE_WOW,             /*WOW״̬*/
    DEV_PWR_STATE_IDLE,         //->PWR_SAVE_STATE_IDLE,            /*idle״̬�����û�����*/
    DEV_PWR_STATE_OFF            //->PWR_SAVE_STATE_OFF,
};

#define DMAC_VAP2DEV_PM_STATE(_uc_state) (g_pm_state_map[_uc_state])

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : ap_power_state_work_entry
 ��������  : work״̬��entry�ӿ�
 �������  : p_ctx:״̬�������ģ��Խ���״̬����˵Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_work_entry(oal_void *p_ctx)
{
    mac_pm_handler_stru*    pst_pm_handler = (mac_pm_handler_stru*)p_ctx;
    oal_uint32              ul_core_id;

    ul_core_id = OAL_GET_CORE_ID();
    //dmac_vap_stru *pst_dmac_vap = (dmac_vap_stru *)(pst_pm_handler->p_mac_fsm->p_oshandler);


    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return ;
    }

    pst_pm_handler->ul_user_check_count = 0;
    pst_pm_handler->ul_inactive_time    = 0;
    if((pst_pm_handler->bit_pwr_siso_en)||(pst_pm_handler->bit_pwr_wow_en))
    {
        if (OAL_FALSE == pst_pm_handler->st_inactive_timer.en_is_registerd)
        {
            FRW_TIMER_CREATE_TIMER(&pst_pm_handler->st_inactive_timer,
                                   dmac_pm_ap_inactive_timer,
                                   AP_PWR_DEFAULT_USR_CHECK_TIME,      /* 1000ms����һ�� */
                                   (oal_void*)pst_pm_handler,
                                   OAL_TRUE,
                                   OAM_MODULE_ID_DMAC,
                                   ul_core_id);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_work_exit
 ��������  : work״̬��exit�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_work_exit(oal_void *p_ctx)
{
    mac_pm_handler_stru *pst_pm_handler = (mac_pm_handler_stru*)p_ctx;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return;
    }
    else if (OAL_TRUE == pst_pm_handler->st_inactive_timer.en_is_registerd)
    {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&pst_pm_handler->st_inactive_timer);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_work_event
 ��������  : work״̬��event�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
             us_event:�������¼�
             us_event_data_len:�¼���Я�������ݳ���
             p_event_data:�¼���Я�����¼���Ӧ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_work_event(oal_void   *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    mac_pm_handler_stru*    pst_pm_handler = (mac_pm_handler_stru*)p_ctx;

#ifdef _PRE_WLAN_FEATURE_GREEN_AP
    mac_fsm_stru        *pst_fsm;
    mac_device_stru     *pst_device;
    dmac_vap_stru       *pst_dmac_vap;
#endif

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return OAL_FAIL;
    }

    switch(us_event)
    {
        case AP_PWR_EVENT_INACTIVE:
        case AP_PWR_EVENT_NO_USR:
            if(pst_pm_handler->bit_pwr_wow_en)
            {
                frw_timer_stop();

#ifdef _PRE_WLAN_FEATURE_GREEN_AP
                pst_fsm      = pst_pm_handler->p_mac_fsm;
                pst_dmac_vap = (dmac_vap_stru *)(pst_fsm->p_oshandler);
                pst_device   =  mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);

                dmac_green_ap_suspend(pst_device);
#endif
                dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_WOW);
            }
            else
            {
                dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_IDLE);
            }
        break;
        case AP_PWR_EVENT_USR_ASSOC:
            pst_pm_handler->ul_user_check_count = 0;
        break;
        case AP_PWR_EVENT_WIFI_DISABLE:
            dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_DEEP_SLEEP);
            break;
        default:

        /* OAM��־�в���ʹ��%s*/
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "{fsm in state %d do not process event %d }",
                    pst_pm_handler->p_mac_fsm->p_state_info[pst_pm_handler->p_mac_fsm->uc_cur_state].state,us_event);
        break;

    }
    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : ap_power_state_deep_sleep_entry
 ��������  : deep_sleep״̬��entry�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_deep_sleep_entry(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_deep_sleep_exit
 ��������  : deep_sleep״̬��exit�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_deep_sleep_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_deep_sleep_event
 ��������  : deep_sleep״̬��event�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
             us_event:�������¼�
             us_event_data_len:�¼���Я�������ݳ���
             p_event_data:�¼���Я�����¼���Ӧ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_deep_sleep_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    mac_pm_handler_stru*    pst_pm_handler = (mac_pm_handler_stru*)p_ctx;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return OAL_FAIL;
    }

    switch(us_event)
    {
        case AP_PWR_EVENT_WIFI_ENABLE:
            dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_WORK);
        break;
        default:
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "{fsm in state %d do not process event %d }",
                    pst_pm_handler->p_mac_fsm->p_state_info[pst_pm_handler->p_mac_fsm->uc_cur_state].state,us_event);
        break;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_wow_entry
 ��������  : wow״̬��entry�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_wow_entry(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_wow_exit
 ��������  : wow״̬��exit�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_wow_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_wow_event
 ��������  : wow״̬��event�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_wow_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    mac_pm_handler_stru*    pst_pm_handler = (mac_pm_handler_stru*)p_ctx;

#ifdef _PRE_WLAN_FEATURE_GREEN_AP
    mac_fsm_stru        *pst_fsm;
    mac_device_stru     *pst_device;
    dmac_vap_stru       *pst_dmac_vap;
#endif

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return OAL_FAIL;
    }

    switch(us_event)
    {
        /*
            ����һ:�����Ƿ���������¼�ʹvap��wow����
            AP_PWR_EVENT_USR_ASSOC:�û�����ʱ����vap��wow�л���work�����¼�����Ӳ��û�н��뵽wow�������ĳһ��VAP����wow�ĳ�����
                                   �Ż���:��ǰ�ǽ������е�vap����Ҫ�Ż�ֻ����һ��VAP
            AP_PWR_EVENT_WOW_WAKE:CPU�жϽ��ѣ��������е�VAP
            ��Ҫ�����¼�:CPUû�н���˯�ߣ�wifi˯�ߣ������ϲ��������·�ʱ������WIFI���¼�
        */

        /* �����: PCIE��λRECONFIG�ľ������� */

        case AP_PWR_EVENT_USR_ASSOC:
        case AP_PWR_EVENT_WOW_WAKE:
            if(pst_pm_handler->bit_pwr_wow_en)
            {
                dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_WORK);
                frw_timer_restart();

#ifdef _PRE_WLAN_FEATURE_GREEN_AP
                pst_fsm      = pst_pm_handler->p_mac_fsm;
                pst_dmac_vap = (dmac_vap_stru *)(pst_fsm->p_oshandler);
                pst_device   =  mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);
                dmac_green_ap_resume(pst_device);
#endif
            }
            break;

        default:

        /* OAM��־�в���ʹ��%s*/
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "{fsm in state %d do not process event %d }",
                    pst_pm_handler->p_mac_fsm->p_state_info[pst_pm_handler->p_mac_fsm->uc_cur_state].state,us_event);
        break;
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_idle_entry
 ��������  : idle״̬��entry�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_idle_entry(oal_void *p_ctx)
{
    /*IDLE״̬��:
    VAP�������beacon���ڵ�1s,���͹��ʵ���������ʽ�12db��
    device������hal��ر�1·���շ���ͨ·(��mac_pm_set_hal_state)������PCIE L1-S�͹��ģ�mem-prechargre��soc�����Զ��ſ�*/

    /* ����beacon period, ԭ��ÿVAP���裬��ΪԼ��device��VAP��beaconֵһ��������mac_pm_set_hal_state��ʵ��*/

    /*���书�ʵ�����tbtt�жϴ�����*/

    /*device�͹���������mac_pm_set_hal_state�����*/

    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_idle_exit
 ��������  : idle״̬��exit�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_idle_exit(oal_void *p_ctx)
{

    return;

}

/*****************************************************************************
 �� �� ��  : ap_power_state_idle_event
 ��������  : idle״̬��event�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
             us_event:�������¼�
             us_event_data_len:�¼���Я�������ݳ���
             p_event_data:�¼���Я�����¼���Ӧ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_idle_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    mac_pm_handler_stru*    pst_pm_handler = (mac_pm_handler_stru*)p_ctx;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return OAL_FAIL;
    }

    switch(us_event)
    {
        case AP_PWR_EVENT_USR_ASSOC:
            dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_WORK);
        break;
        case AP_PWR_EVENT_WIFI_DISABLE:
            dmac_pm_state_trans(pst_pm_handler, PWR_SAVE_STATE_DEEP_SLEEP);
            break;
        default:
            /* OAM��־�в���ʹ��%s*/
        OAM_WARNING_LOG2(0, OAM_SF_PWR, "{fsm in state %d do not process event %d }",
                    pst_pm_handler->p_mac_fsm->p_state_info[pst_pm_handler->p_mac_fsm->uc_cur_state].state,us_event);
        break;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_off_entry
 ��������  : off״̬��entry�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_off_entry(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_off_exit
 ��������  : off״̬��exit�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void ap_power_state_off_exit(oal_void *p_ctx)
{
    return;
}

/*****************************************************************************
 �� �� ��  : ap_power_state_off_event
 ��������  : off״̬��event�ӿ�
 �������  : p_ctx:״̬�������ģ�����״̬��Ϊpm_handler
             us_event:�������¼�
             us_event_data_len:�¼���Я�������ݳ���
             p_event_data:�¼���Я�����¼���Ӧ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 ap_power_state_off_event(oal_void      *p_ctx,
                                                        oal_uint16    us_event,
                                                        oal_uint16    us_event_data_len,
                                                        oal_void      *p_event_data)
{
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : ap_pm_wow_wake_event
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��31��
    ��    ��   : huxiaotong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  ap_pm_wow_host_wake_event(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru         *pst_event;
    mac_pm_handler_stru    *pst_pm_handler;
    mac_fsm_stru           *pst_fsm;
    mac_device_stru        *pst_mac_device;
    dmac_vap_stru          *pst_dmac_vap;
    oal_uint8               uc_vap_idx;

    pst_event               = (frw_event_stru *)pst_event_mem->puc_data;

    pst_mac_device = mac_res_get_dev(pst_event->st_event_hdr.uc_device_id);
    if(OAL_PTR_NULL == pst_mac_device)
    {
        return OAL_FAIL;
    }

    /* ѭ��divice�µ�����vap��������VAP��ΪWORK״̬ */
    for (uc_vap_idx = 0; uc_vap_idx < pst_mac_device->uc_vap_num; uc_vap_idx++)
    {

        pst_dmac_vap =  mac_res_get_dmac_vap(pst_mac_device->auc_vap_id[uc_vap_idx]);
        if (OAL_PTR_NULL == pst_dmac_vap)
        {
            OAM_WARNING_LOG0(pst_mac_device->auc_vap_id[uc_vap_idx], OAM_SF_CFG, "{ap_pm_wow_host_wake_event::pst_dmac_vap null.");
            return OAL_ERR_CODE_PTR_NULL;
        }

        /* ap/sta��wow������������ */
        if (WLAN_VAP_MODE_BSS_AP != pst_dmac_vap->st_vap_base_info.en_vap_mode)
        {
            continue;
        }

        pst_pm_handler = pst_dmac_vap->pst_pm_handler;

        pst_fsm = pst_pm_handler->p_mac_fsm;
        mac_fsm_event_dispatch(pst_fsm,
                                AP_PWR_EVENT_WOW_WAKE,
                                0, OAL_PTR_NULL);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_pm_post_event
 ��������  : ����״̬�����¼�����ӿ�,����״̬����״̬�л����¼�������������frw���¼��ַ�����������pm���ڲ��¼�
 �������  : pst_event_mem: frw���¼��ṹָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��17��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 dmac_pm_post_event(oal_void* pst_oshandler, oal_uint16 us_type, oal_uint16 us_datalen, oal_uint8* pst_data)
{
    mac_pm_handler_stru  *pst_handler;
    mac_fsm_stru         *pst_fsm;
    oal_uint32            ul_ret;
    dmac_vap_stru*        pst_dmac_vap = (dmac_vap_stru*)pst_oshandler;

    if(pst_dmac_vap == OAL_PTR_NULL)
    {
        return OAL_FAIL;
    }
    pst_handler = pst_dmac_vap->pst_pm_handler;
    if(pst_handler == OAL_PTR_NULL)
    {
        return OAL_FAIL;
    }

    pst_fsm = pst_handler->p_mac_fsm;
    ul_ret = mac_fsm_event_dispatch(pst_fsm,us_type,us_datalen,pst_data);

    return ul_ret;

}

/*****************************************************************************
 �� �� ��  : dmac_pm_state_trans
 ��������  : PM����״̬����״̬�л��ӿ�
 �������  : pst_handler:pm handlerָ��
             uc_state:�л�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/

OAL_STATIC oal_void dmac_pm_state_trans(mac_pm_handler_stru* pst_handler,oal_uint8 uc_state)
{
    mac_fsm_stru    *pst_fsm = pst_handler->p_mac_fsm;
    mac_device_stru *pst_mac_dev;
    dmac_vap_stru   *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru*)(pst_fsm->p_oshandler);
    pst_mac_dev  =  mac_res_get_dev(pst_dmac_vap->st_vap_base_info.uc_device_id);

    if(uc_state>=PWR_SAVE_STATE_BUTT)
    {
        /* OAM��־�в���ʹ��%s*/
        OAM_ERROR_LOG1(pst_mac_dev->uc_cfg_vap_id, OAM_SF_PWR, "hmac_pm_state_trans:invalid state %d",uc_state);
        return;
    }

    mac_fsm_trans_to_state(pst_fsm, uc_state);

    /*��fsm��״̬�Ѿ��л��ˣ���arbiterͶƱ*/
    mac_pm_arbiter_to_state(pst_mac_dev, &(pst_dmac_vap->st_vap_base_info), pst_handler->ul_pwr_arbiter_id,
                            DMAC_VAP2DEV_PM_STATE(pst_fsm->uc_prev_state),
                            DMAC_VAP2DEV_PM_STATE(pst_fsm->uc_cur_state));

    return;

}

/*****************************************************************************
 �� �� ��  : dmac_pm_ap_inactive_timer
 ��������  : AP����VAP����inactive��ʱ����ʱ������
 �������  : p_fsm:״̬��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/

OAL_STATIC oal_uint32 dmac_pm_ap_inactive_timer(oal_void* pst_arg)
{
    mac_pm_handler_stru *pst_pm_handler = (mac_pm_handler_stru*)pst_arg;
    mac_fsm_stru        *pst_fsm;
    dmac_vap_stru       *pst_dmac_vap;

    pst_dmac_vap = (dmac_vap_stru*)(pst_pm_handler->p_mac_fsm->p_oshandler);
    if((0 == pst_dmac_vap->st_vap_base_info.us_user_nums) &&
       (AP_PWR_MAX_USR_CHECK_COUNT <= pst_pm_handler->ul_user_check_count))
    {
        pst_fsm = pst_pm_handler->p_mac_fsm;
        mac_fsm_event_dispatch(pst_fsm,
                                AP_PWR_EVENT_NO_USR,
                                0, OAL_PTR_NULL);
    }
    else if(0 == pst_dmac_vap->st_vap_base_info.us_user_nums)
    {
       pst_pm_handler->ul_user_check_count++;
    }
    else
    {
        /*TBD:VAP������⣬�Ƿ��Ծ*/
    }

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : dmac_pm_ap_attach
 ��������  : AP����VAP����pm handler
 �������  : p_fsm:״̬��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
mac_pm_handler_stru * dmac_pm_ap_attach(oal_void* pst_oshandler)
{
    mac_pm_handler_stru *p_handler = OAL_PTR_NULL;
    mac_device_stru     *p_device;
    dmac_vap_stru       *p_dmac_vap = (dmac_vap_stru*)pst_oshandler;
    oal_uint8            auc_fsm_name[6] = {0};


    if(OAL_PTR_NULL!=p_dmac_vap->pst_pm_handler)
    {
        return p_dmac_vap->pst_pm_handler;
    }

    p_device = mac_res_get_dev(p_dmac_vap->st_vap_base_info.uc_device_id);
    if (OAL_PTR_NULL == p_device)
    {
        OAM_ERROR_LOG1(p_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_ap_pm_attach: vap state[%d]!",
                       p_dmac_vap->st_vap_base_info.en_vap_state);
        return OAL_PTR_NULL;
    }

#ifdef _PRE_WLAN_FEATURE_DBAC
    /* dbacʹ�ܣ�������wow */
    if (mac_is_dbac_enabled(p_device))
    {
        OAM_INFO_LOG0(p_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "dmac_pm_ap_attach:dbac is enable!");
        return p_dmac_vap->pst_pm_handler;
    }
#endif

    p_handler = (mac_pm_handler_stru*)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL,OAL_SIZEOF(mac_pm_handler_stru),OAL_TRUE);
    if(OAL_PTR_NULL == p_handler)
    {
        OAM_ERROR_LOG0(p_dmac_vap->st_vap_base_info.uc_vap_id, OAM_SF_PWR, "{dmac_ap_pm_attach:malloc memory for pm handler fail!");
        return OAL_PTR_NULL;
    }

    OAL_MEMZERO(p_handler, OAL_SIZEOF(mac_pm_handler_stru));

    p_handler->bit_pwr_sleep_en     = 0;
    p_handler->bit_pwr_siso_en      = OAL_TRUE;
#if (_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_E5)
    p_handler->bit_pwr_wow_en       = OAL_TRUE;
#else
    p_handler->bit_pwr_wow_en       = OAL_FALSE;
#endif
    p_handler->ul_inactive_time     = 0;
    p_handler->ul_user_check_count  = 0;
    p_handler->ul_max_inactive_time = AP_PWR_DEFAULT_INACTIVE_TIME;
    p_handler->ul_idle_beacon_txpower   = 0xf2;

    /* ׼��һ��Ψһ��fsmname */
    auc_fsm_name[0] = (oal_uint8)p_dmac_vap->st_vap_base_info.ul_core_id;
    auc_fsm_name[1] = p_dmac_vap->st_vap_base_info.uc_chip_id;
    auc_fsm_name[2] = p_dmac_vap->st_vap_base_info.uc_device_id;
    auc_fsm_name[3] = p_dmac_vap->st_vap_base_info.uc_vap_id;
    auc_fsm_name[4] = p_dmac_vap->st_vap_base_info.en_vap_mode;
    auc_fsm_name[5] = 0;

    p_handler->p_mac_fsm = mac_fsm_create((oal_void*)p_dmac_vap,
                                          auc_fsm_name,
                                          p_handler,
                                          PWR_SAVE_STATE_WORK,
                                          g_ap_power_fsm_info,
                                          OAL_SIZEOF(g_ap_power_fsm_info)/OAL_SIZEOF(mac_fsm_state_info)
                                          );

    p_handler->ul_pwr_arbiter_id    = mac_pm_arbiter_alloc_id(p_device,p_handler->p_mac_fsm->uc_name,MAC_PWR_ARBITER_TYPE_AP);

    p_dmac_vap->pst_pm_handler = p_handler;

    return  p_dmac_vap->pst_pm_handler;

}

/*****************************************************************************
 �� �� ��  : dmac_pm_ap_deattach
 ��������  : AP����VAP����pm handler
 �������  : p_fsm:״̬��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void dmac_pm_ap_deattach(oal_void* pst_oshandler)
{
    mac_pm_handler_stru *p_handler = OAL_PTR_NULL;
    mac_device_stru     *p_device;
    dmac_vap_stru       *p_dmac_vap = (dmac_vap_stru*)pst_oshandler;

    p_handler = p_dmac_vap->pst_pm_handler;
    if(!p_handler)
    {
        return;
    }

    /*�����л���work״̬*/
    dmac_pm_state_trans(p_handler, PWR_SAVE_STATE_WORK);

    if (OAL_TRUE == p_handler->st_inactive_timer.en_is_registerd)
     {
        FRW_TIMER_IMMEDIATE_DESTROY_TIMER(&p_handler->st_inactive_timer);
     }

    if(p_handler->p_mac_fsm)
    {
        mac_fsm_destroy(p_handler->p_mac_fsm);
    }

    p_device = mac_res_get_dev(p_dmac_vap->st_vap_base_info.uc_device_id);

    mac_pm_arbiter_free_id(p_device,p_handler->ul_pwr_arbiter_id);

    OAL_MEM_FREE(p_handler,OAL_TRUE);

    p_dmac_vap->pst_pm_handler = OAL_PTR_NULL;

    return;

}

/*****************************************************************************
 �� �� ��  : dmac_pm_current_state
 ��������  : PM����״̬���ĵ�ǰ״̬
 �������  : pst_handler:pm handlerָ��
             uc_state:�л�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��18��
    ��    ��   : zourong
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_uint8 dmac_pm_vap_current_state(oal_void* pst_oshandler)
{
    mac_pm_handler_stru     *pst_pm_handler = ((dmac_vap_stru*)pst_oshandler)->pst_pm_handler;
    mac_fsm_stru            *pst_fsm ;

    if(OAL_PTR_NULL == pst_pm_handler)
    {
        return PWR_SAVE_STATE_BUTT;
    }

    pst_fsm = pst_pm_handler->p_mac_fsm;
    if(OAL_PTR_NULL == pst_fsm)
    {
        return PWR_SAVE_STATE_BUTT;
    }

    return pst_fsm->uc_cur_state;

}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

