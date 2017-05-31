

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#include <linux/module.h>   /* kernel module definitions */
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/platform_device.h>
#include <linux/kobject.h>
#include <linux/irq.h>
#include <linux/wakelock.h>
#include <linux/mmc/sdio.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/host.h>
#include <linux/gpio.h>

#include "oal_sdio.h"
#include "oal_sdio_comm.h"
#include "oal_sdio_host_if.h"

#include "plat_type.h"
//#include "plat_debug.h"
#include "plat_pm_wlan.h"
#include "plat_pm.h"

#include "oal_hcc_host_if.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_PLAT_PM_WLAN_C


/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
struct wlan_pm_s* gpst_wlan_pm_info = OAL_PTR_NULL;

wlan_pm_callback_stru     gst_wlan_pm_callback =
{
    .wlan_pm_wakeup_dev  = wlan_pm_wakeup_dev,
    .wlan_pm_state_get   = wlan_pm_state_get,
    .wlan_pm_wakeup_host = wlan_pm_wakeup_host,
    .wlan_pm_feed_wdg    = wlan_pm_feed_wdg,
    .wlan_pm_wakeup_dev_ack    = wlan_pm_wakeup_dev_ack,

};
oal_bool_enum g_wlan_pm_switch = 1;

EXPORT_SYMBOL_GPL(g_wlan_pm_switch);

oal_uint32 auto_freq_enable = 1;
module_param(auto_freq_enable, uint, S_IRUGO | S_IWUSR);

extern  int32 wlan_power_on(void);
extern  int32 wlan_power_off(void);
void wlan_pm_wakeup_work(oal_work_stru *pst_worker);
void wlan_pm_sleep_work(oal_work_stru *pst_worker);
void wlan_pm_freq_adjust_work(oal_work_stru *pst_worker);

void wlan_pm_wdg_timeout(struct wlan_pm_s *pm_data);

int32 wlan_pm_wakeup_done_callback(void *data);
int32 wlan_pm_close_done_callback(void *data);
int32 wlan_pm_open_bcpu_done_callback(void *data);
int32 wlan_pm_close_bcpu_done_callback(void *data);
int32 wlan_pm_halt_bcpu_done_callback(void *data);


int32 wlan_pm_stop_wdg(struct wlan_pm_s *pst_wlan_pm_info);
oal_int wlan_pm_work_submit(struct wlan_pm_s    *pst_wlan_pm, oal_work_stru* pst_worker);
void wlan_pm_info_clean(void);

extern oal_atomic g_wakeup_dev_wait_ack;
/*****************************************************************************
 �� �� ��  : wlan_pm_get_drv
 ��������  : ��ȡȫ��wlan�ṹ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
struct wlan_pm_s*  wlan_pm_get_drv(oal_void)
{
    return gpst_wlan_pm_info;
}

EXPORT_SYMBOL_GPL(wlan_pm_get_drv);

/*****************************************************************************
 �� �� ��  : wlan_pm_set_device_ready
 ��������  : ���ܵ�deviceready���źţ�����host�� device ready״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  wlan_pm_set_device_ready(oal_void* data)
{
    struct wlan_pm_s    *pst_wlan_pm = (struct wlan_pm_s*)data;

    OAL_COMPLETE(&pst_wlan_pm->st_device_ready);
    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : wlan_pm_init_device_ready
 ��������  : ��ʼ��host�� device ready״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void wlan_pm_init_device_ready(struct wlan_pm_s    *pst_wlan_pm)
{
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_device_ready);
}
/*****************************************************************************
 �� �� ��  : wlan_pm_wait_device_ready
 ��������  : �ȴ�host�� device ready״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wlan_pm_wait_device_ready(struct wlan_pm_s    *pst_wlan_pm)
{
    /* �ȴ�host�°벿��ʼ����� */
    return oal_wait_for_completion_timeout(&pst_wlan_pm->st_device_ready, (oal_uint32)OAL_MSECS_TO_JIFFIES(HOST_WAIT_BOTTOM_INIT_TIMEOUT));
}

/*****************************************************************************
 �� �� ��  : wlan_pm_sleep_request
 ��������  : ����sleep �����device
 �������  : ��
 �������  : ��
 �� �� ֵ  : SUCC/FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : z00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 wlan_pm_sleep_request(struct wlan_pm_s    *pst_wlan_pm)
{
    return oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_SLEEP_REQ);


}
/*****************************************************************************
 �� �� ��  : wlan_pm_allow_sleep_callback
 ��������  : deviceӦ��allow_sleep��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_int32 wlan_pm_allow_sleep_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    //PS_PRINT_INFO("wlan_pm_allow_sleep_callback !\n");

    pst_wlan_pm->ul_sleep_stage = SLEEP_ALLOW_RCV;
    OAL_COMPLETE(&pst_wlan_pm->st_sleep_request_ack);

    return SUCCESS;

}
/*****************************************************************************
 �� �� ��  : wlan_pm_disallow_sleep_callback
 ��������  : deviceӦ��allow_sleep��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_int32 wlan_pm_disallow_sleep_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    //PS_PRINT_INFO("wlan_pm_disallow_sleep_callback !\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_disallow_sleep_callback !\n");

    pst_wlan_pm->ul_sleep_stage = SLEEP_DISALLOW_RCV;
    OAL_COMPLETE(&pst_wlan_pm->st_sleep_request_ack);


    return SUCCESS;

}


/*****************************************************************************
 �� �� ��  : wlan_pm_init
 ��������  : WLAN PM��ʼ���ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
struct wlan_pm_s*  wlan_pm_init(oal_void)
{
    struct wlan_pm_s*   pst_wlan_pm;
    BOARD_INFO *        pst_board = get_board_info();

    if(OAL_PTR_NULL == pst_board)
    {
        return OAL_PTR_NULL;
    }

    pst_wlan_pm = kzalloc(sizeof(struct wlan_pm_s), GFP_KERNEL);
    if (NULL == pst_wlan_pm)
    {
        OAL_IO_PRINT("[plat_pm]no mem to allocate wlan_pm_data\n");
        return OAL_PTR_NULL;
    }

    oal_memset(pst_wlan_pm, 0, sizeof(struct wlan_pm_s));

    pst_wlan_pm->pst_sdio                  = oal_get_sdio_default_handler();
    pst_wlan_pm->pst_sdio->pst_pm_callback = &gst_wlan_pm_callback;

    pst_wlan_pm->ul_wlan_pm_enable          = OAL_FALSE;
    pst_wlan_pm->ul_apmode_allow_pm_flag    = OAL_TRUE;  /* Ĭ�������µ� */

    /*work queue��ʼ��*/
    pst_wlan_pm->pst_pm_wq = oal_create_singlethread_workqueue("wlan_pm_wq");
    if (!pst_wlan_pm->pst_pm_wq)
    {
        OAL_IO_PRINT("[plat_pm]Failed to create wlan_pm_wq!");
        kfree(pst_wlan_pm);
        return OAL_PTR_NULL;
    }
    /*register wakeup and sleep work*/
    OAL_INIT_WORK(&pst_wlan_pm->st_wakeup_work, wlan_pm_wakeup_work);
    OAL_INIT_WORK(&pst_wlan_pm->st_sleep_work,  wlan_pm_sleep_work);
    OAL_INIT_WORK(&pst_wlan_pm->st_freq_adjust_work,  wlan_pm_freq_adjust_work);

    /*��ʼ��оƬ�Լ�work*/
    OAL_INIT_WORK(&pst_wlan_pm->st_ram_reg_test_work,  wlan_device_mem_check_work);

    /*sleep timer��ʼ��*/
    init_timer(&pst_wlan_pm->st_watchdog_timer);
    pst_wlan_pm->st_watchdog_timer.data        = (unsigned long)pst_wlan_pm;
    pst_wlan_pm->st_watchdog_timer.function    = (void *)wlan_pm_wdg_timeout;
    pst_wlan_pm->ul_wdg_timeout_cnt            = WLAN_SLEEP_DEFAULT_CHECK_CNT;
    pst_wlan_pm->ul_wdg_timeout_curr_cnt       = 0;
    pst_wlan_pm->ul_packet_cnt                 = 0;

    pst_wlan_pm->ul_wlan_power_state           = POWER_STATE_SHUTDOWN;
    pst_wlan_pm->ul_wlan_dev_state             = HOST_ALLOW_TO_SLEEP;
    pst_wlan_pm->ul_sleep_stage                = SLEEP_STAGE_INIT;

    pst_wlan_pm->st_wifi_srv_handler.p_wifi_srv_get_pm_pause_func = OAL_PTR_NULL;

    gpst_wlan_pm_info = pst_wlan_pm;

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_open_bcpu_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_bcpu_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_device_ready);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_wakeup_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_sleep_request_ack);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_halt_bcpu_done);

    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_WLAN_READY,wlan_pm_set_device_ready,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_WAKEUP_SUCC,wlan_pm_wakeup_done_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_ALLOW_SLEEP,wlan_pm_allow_sleep_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_DISALLOW_SLEEP,wlan_pm_disallow_sleep_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_POWEROFF_ACK,wlan_pm_close_done_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_OPEN_BCPU_ACK,wlan_pm_open_bcpu_done_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_CLOSE_BCPU_ACK,wlan_pm_close_bcpu_done_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_HALT_BCPU,wlan_pm_halt_bcpu_done_callback,pst_wlan_pm);

   // pst_wlan_pm->pst_sdio->gpio_int_count = 0;
    pst_wlan_pm->pst_sdio->data_int_count = 0;
    pst_wlan_pm->pst_sdio->wakeup_int_count = 0;

#ifndef CONFIG_WAKELOCK
#error "CONFIG_WAKELOCK is not defined!!!\n"
#endif

    OAL_IO_PRINT("[plat_pm]wlan_pm_init ok!");
    return  pst_wlan_pm;
}

/*****************************************************************************
 �� �� ��  : wlan_pm_exit
 ��������  : WLAN pm�˳��ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint  wlan_pm_exit(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_SUCC;
    }

    wlan_pm_stop_wdg(pst_wlan_pm);

    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WAKEUP_SUCC);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WLAN_READY);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_ALLOW_SLEEP);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_DISALLOW_SLEEP);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_POWEROFF_ACK);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_OPEN_BCPU_ACK);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_CLOSE_BCPU_ACK);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_HALT_BCPU);

    kfree(pst_wlan_pm);

    gpst_wlan_pm_info = OAL_PTR_NULL;

    OAL_IO_PRINT("[plat_pm]wlan_pm_exit ok!");


    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wlan_pm_is_poweron
 ��������  : wifi�Ƿ��ϵ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wlan_pm_is_poweron(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    //struct pm_drv_data  *pm_data = pm_get_drvdata();

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FALSE;
    }
    //mutex_lock(&pm_data->host_mutex);

    if(POWER_STATE_OPEN == pst_wlan_pm->ul_wlan_power_state)
    {
        //mutex_unlock(&pm_data->host_mutex);
        return OAL_TRUE;
    }
    else
    {
        //mutex_unlock(&pm_data->host_mutex);
        return OAL_FALSE;
    }
}
EXPORT_SYMBOL_GPL(wlan_pm_is_poweron);

/*****************************************************************************
 �� �� ��  : wlan_pm_get_wifi_srv_handler
 ��������  : ��ȡ�ص�handlerָ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
struct wifi_srv_callback_handler* wlan_pm_get_wifi_srv_handler(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FALSE;
    }

    return &pst_wlan_pm->st_wifi_srv_handler;
}
EXPORT_SYMBOL_GPL(wlan_pm_get_wifi_srv_handler);

/*****************************************************************************
 �� �� ��  : wlan_pm_open
 ��������  : open wifi,���bfgxû�п���,�ϵ�,���������WCPU
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 wlan_pm_open(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    struct pm_drv_data *pm_data = pm_get_drvdata();

    //OAL_IO_PRINT("wlan_pm_open caller[%pF]\n",(void*)_RET_IP_);

    if ((NULL == pm_data)||(OAL_PTR_NULL == pst_wlan_pm))
    {
        OAM_ERROR_LOG2(0, OAM_SF_PWR, "wlan_pm_open::pm_data[%p] or pst_wlan_pm[%p] is NULL!", pm_data, pst_wlan_pm);
        return OAL_FAIL;
    }

    mutex_lock(&pm_data->host_mutex);

    if(POWER_STATE_OPEN == pst_wlan_pm->ul_wlan_power_state)
    {
        mutex_unlock(&pm_data->host_mutex);
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_open::aleady opened");
        return OAL_ERR_CODE_ALREADY_OPEN;
    }

    if(!pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count)
    {
        /*make sure open only lock once*/
        oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_open::get wakelock %lu!",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    pst_wlan_pm->ul_open_cnt++;

    if(OAL_SUCC != wlan_power_on())
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "wlan_pm_open::wlan_power_on fail!");
        pst_wlan_pm->ul_wlan_power_state = POWER_STATE_SHUTDOWN;
		oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
		mutex_unlock(&pm_data->host_mutex);
		DECLARE_DFT_TRACE_KEY_INFO("wlan_power_on_fail",OAL_DFT_TRACE_FAIL);
        return OAL_FAIL;
    }

#ifdef _PRE_PLAT_FEATURE_CUSTOMIZE

        wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);

        if(OAL_PTR_NULL == g_pst_custom_process_func.p_custom_cali_func)
        {
            OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_open::NO g_pst_custom_process_func registered");
            mutex_unlock(&pm_data->host_mutex);
            return OAL_FAIL;
        }

        /* ���У׼�·��ɹ���ȴ�device ready�����������wifi */
        if (OAL_SUCC == g_pst_custom_process_func.p_custom_cali_func())
        {
            if(0 == wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
            {
                DECLARE_DFT_TRACE_KEY_INFO("wlan_wait_custom_cali_fail", OAL_DFT_TRACE_FAIL);

                OAM_ERROR_LOG1(0,OAM_SF_PWR, "wlan_pm_open::wlan_pm_wait_custom_cali timeout %d !!!!!!", HOST_WAIT_BOTTOM_INIT_TIMEOUT);

                mutex_unlock(&pm_data->host_mutex);
                if(OAL_TRUE == oal_trigger_sdio_exception(oal_get_sdio_default_handler(), OAL_TRUE))
                {
                    OAL_IO_PRINT("dump device mem when cali custom failed!\n");
                }
                return OAL_FAIL;
            }
        }
#endif

    OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_open::wlan_pm_open SUCC!!");
    DECLARE_DFT_TRACE_KEY_INFO("wlan_open_succ",OAL_DFT_TRACE_SUCC);

    wlan_pm_enable();

    frw_timer_sys_start();

    /*��timeoutֵ�ָ�ΪĬ��ֵ����������ʱ��*/
    wlan_pm_set_timeout(WLAN_SLEEP_DEFAULT_CHECK_CNT);

    mutex_unlock(&pm_data->host_mutex);

    return OAL_SUCC;

}
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV) || defined(_PRE_PRODUCT_ID_HI110X_HOST))
oal_int32           ram_reg_test_result = OAL_SUCC;
unsigned long long  ram_reg_test_time = 0;

oal_int32 wlan_device_mem_check(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAL_BUG_ON(!pst_wlan_pm);
    ram_reg_test_result = OAL_SUCC;
    ram_reg_test_time = 0;
    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);

    if(0!=wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_ram_reg_test_work))
    {
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"st_ram_reg_test_work submit work fail !\n");
    }

    return OAL_SUCC;

}
oal_int32 wlan_device_mem_check_result(unsigned long long *time)
{
    *time = ram_reg_test_time;
    return ram_reg_test_result;
}
oal_void wlan_device_mem_check_work(oal_work_stru *pst_worker)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    mutex_lock(&pm_data->host_mutex);

    ram_reg_test_result = device_mem_check(&ram_reg_test_time);

    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);

    mutex_unlock(&pm_data->host_mutex);
}
EXPORT_SYMBOL_GPL(wlan_device_mem_check);
EXPORT_SYMBOL_GPL(wlan_device_mem_check_result);


#endif

EXPORT_SYMBOL_GPL(wlan_pm_open);

/*****************************************************************************
 �� �� ��  : wlan_pm_close
 ��������  : close wifi,���bfgxû�п�,�µ磬�����������WCPU
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
extern int isAsic(void);
oal_uint32 wlan_pm_close(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    struct pm_drv_data *pm_data = pm_get_drvdata();

    //OAL_IO_PRINT("wlan_pm_close caller[%pF]\n",(void*)_RET_IP_);

    if (NULL == pm_data)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "wlan_pm_close,pm_data is NULL!");
        return OAL_FAIL;
    }

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

    if(!pst_wlan_pm->ul_apmode_allow_pm_flag)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_close,AP mode,do not shutdown power.");
        return OAL_SUCC;
    }

    OAL_IO_PRINT("[plat_pm]wlan_pm_close start!!\n");

    mutex_lock(&pm_data->host_mutex);

    if (!isAsic())
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close is FPGA,do not close wifi!\n");
        mutex_unlock(&pm_data->host_mutex);
        return OAL_SUCC;
    }

    pst_wlan_pm->ul_close_cnt++;

    if(POWER_STATE_SHUTDOWN == pst_wlan_pm->ul_wlan_power_state)
    {
        mutex_unlock(&pm_data->host_mutex);
        return OAL_ERR_CODE_ALREADY_CLOSE;
    }



    wlan_pm_disable();

    wlan_pm_stop_wdg(pst_wlan_pm);

    wlan_pm_info_clean();

    /*mask rx sdio data interrupt*/
    oal_sdio_func1_int_mask(pst_wlan_pm->pst_sdio, HISDIO_FUNC1_INT_DREADY);

    if(OAL_SUCC!=wlan_power_off())
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_power_off FAIL!\n");
        mutex_unlock(&pm_data->host_mutex);
        DECLARE_DFT_TRACE_KEY_INFO("wlan_power_off_fail",OAL_DFT_TRACE_FAIL);
        return OAL_FAIL;
    }

    frw_timer_sys_stop();

    pst_wlan_pm->ul_wlan_power_state = POWER_STATE_SHUTDOWN;

    /*unmask rx sdio data interrupt*/
    oal_sdio_func1_int_unmask(pst_wlan_pm->pst_sdio, HISDIO_FUNC1_INT_DREADY);

    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);

    OAM_WARNING_LOG1(0,OAM_SF_PWR,"wlan_pm_close release wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    oal_sdio_wakelocks_release_detect(pst_wlan_pm->pst_sdio);

    mutex_unlock(&pm_data->host_mutex);

    hcc_dev_flowctrl_on(hcc_get_default_handler(), 0);

    OAM_WARNING_LOG0(0,OAM_SF_PWR,"wlan_pm_close succ!\n");
    DECLARE_DFT_TRACE_KEY_INFO("wlan_close_succ",OAL_DFT_TRACE_SUCC);
    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_close);

/*****************************************************************************
 �� �� ��  : wlan_pm_enable
 ��������  : ʹ��wlanƽ̨�͹���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wlan_pm_enable(oal_void)
{

    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(!g_wlan_pm_switch)
    {
        return OAL_SUCC;
    }

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_TRUE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_enable already enabled!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_SUCC;
    }

    pst_wlan_pm->ul_wlan_pm_enable = OAL_TRUE;


#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
     if(OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_set_lock_mod_func)
     {
           g_pst_alg_process_func.p_auto_freq_set_lock_mod_func(OAL_TRUE);
     }
     else
     {
         OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_wdg_timeout:NO p_auto_freq_set_lock_mod_func registered");
     }
#endif

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_enable SUCC!");

    return OAL_SUCC;
}
EXPORT_SYMBOL_GPL(wlan_pm_enable);

/*****************************************************************************
 �� �� ��  : wlan_pm_disable
 ��������  : ȥʹ��wlanƽ̨�͹���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 wlan_pm_disable_check_wakeup(oal_int32 flag)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_disable already disabled!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_SUCC;
    }

    if(OAL_TRUE == flag)
    {
         if (OAL_SUCC != wlan_pm_wakeup_dev())
         {
             OAM_WARNING_LOG0(0, OAM_SF_PWR,"pm wake up dev fail!");
         }
    }

    pst_wlan_pm->ul_wlan_pm_enable = OAL_FALSE;


#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
     if(OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_set_lock_mod_func)
     {
           g_pst_alg_process_func.p_auto_freq_set_lock_mod_func(OAL_FALSE);
     }
     else
     {
         OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_wdg_timeout:NO p_auto_freq_set_lock_mod_func registered");

     }
#endif

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    oal_cancel_work_sync(&pst_wlan_pm->st_wakeup_work);
    oal_cancel_work_sync(&pst_wlan_pm->st_sleep_work);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_disable SUCC!");

    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_disable_check_wakeup);

oal_uint32 wlan_pm_disable(oal_void)
{
    return wlan_pm_disable_check_wakeup(OAL_TRUE);
}
EXPORT_SYMBOL_GPL(wlan_pm_disable);

/*****************************************************************************
 �� �� ��  : wlan_pm_init_dev
 ��������  : ��ʼ��device��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint wlan_pm_init_dev(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint             ul_flag;
    oal_int              ret;


    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_init_dev!\n");

    oal_spin_lock_irq_save(&pst_wlan_pm->pst_sdio->st_pm_state_lock,&ul_flag);

    pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;

    oal_spin_unlock_irq_restore(&pst_wlan_pm->pst_sdio->st_pm_state_lock,&ul_flag);


    /* wait for sdio wakeup */
    ret = down_timeout(&sdio_wake_sema, 6*HZ);
    if (-ETIME == ret)
    {
        //PS_PRINT_ERR("sdio controller is not ready!");
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        return OAL_FAIL;
    }
    up(&sdio_wake_sema);

     /* set sdio register */
    return (oal_uint)oal_sdio_wakeup_dev(pst_wlan_pm->pst_sdio);

}



/*****************************************************************************
 �� �� ��  : wlan_pm_wakeup_dev
 ��������  : ����device
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint wlan_pm_wakeup_dev(oal_void)
{
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    //oal_uint             flags;
    oal_int32              ret;
    oal_uint8              uc_retry;
	oal_uint8              uc_wakeup_retry = 0;
    static oal_uint8       uc_wakeup_err_count = 0;

    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

    if(OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        return OAL_SUCC;
    }

    if(HOST_DISALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
    {
      return OAL_SUCC;
    }

wakeup_again:

    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_wakeup_done);

    /* wait for sdio wakeup */
    ret = down_timeout(&sdio_wake_sema, 6*HZ);
    if (-ETIME == ret)
    {
        pst_wlan_pm->ul_wakeup_fail_wait_sdio++;
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"sdio controller is not ready!");
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        goto wakeup_fail;
    }
    up(&sdio_wake_sema);

     /* set sdio register */
    oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_FALSE);
   // oal_spin_lock_irq_save(&pst_wlan_pm->pst_sdio->st_irq_lock, &flags);

    ret = oal_sdio_wakeup_dev(pst_wlan_pm->pst_sdio);
    OAL_IO_PRINT("wifi wakeup cmd send,wakelock cnt %lu\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    if(OAL_SUCC != ret)
    {
        DECLARE_DFT_TRACE_KEY_INFO("wifi wakeup cmd send fail",OAL_DFT_TRACE_FAIL);
        for(uc_retry = 0;uc_retry<WLAN_SDIO_MSG_RETRY_NUM;uc_retry++)
        {
            msleep(10);
            ret = oal_sdio_wakeup_dev(pst_wlan_pm->pst_sdio);
            if(OAL_SUCC == ret)
            {
                break;
            }
            OAM_ERROR_LOG2(0, OAM_SF_PWR,"oal_sdio_wakeup_dev retry %d ret = %d",uc_retry,ret);
            DECLARE_DFT_TRACE_KEY_INFO("wifi wakeup cmd send retry fail",OAL_DFT_TRACE_FAIL);
        }

        /*after max retry still fail,log error*/
        if(OAL_SUCC != ret)
        {
            pst_wlan_pm->ul_wakeup_fail_set_reg++;
            OAM_ERROR_LOG1(0, OAM_SF_PWR,"oal_sdio_wakeup_dev Fail ret = %d",ret);
            DECLARE_DFT_TRACE_KEY_INFO("oal_sdio_wakeup_dev final fail",OAL_DFT_TRACE_EXCEP);
            oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);
            oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
            goto wakeup_fail;
        }

    }

    oal_atomic_set(&g_wakeup_dev_wait_ack,1);

    pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;
    oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);

    up(&pst_wlan_pm->pst_sdio->gpio_rx_sema);

    ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_wakeup_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_WAKUP_MSG_WAIT_TIMEOUT));
    if(0 == ul_ret)
    {

        if(DISALLOW_TO_SLEEP_VALUE == oal_sdio_get_sleep_state(pst_wlan_pm->pst_sdio))
        {
            pst_wlan_pm->ul_wakeup_fail_timeout++;
            OAM_WARNING_LOG0(0, OAM_SF_PWR,"oal_sdio_wakeup_dev SUCC to set 0xf0 = 0");
            oal_sdio_sleep_dev(pst_wlan_pm->pst_sdio);
            pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;
            oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
            if(0==uc_wakeup_retry)
            {
                OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_dev wait device complete fail,wait time %d ms!,try again",WLAN_WAKUP_MSG_WAIT_TIMEOUT);
                uc_wakeup_retry++;
                goto wakeup_again;
            }
            else
            {
                OAM_ERROR_LOG2(0, OAM_SF_PWR,"wlan_pm_wakeup_dev [%d]wait device complete fail,wait time %d ms!",uc_wakeup_err_count,WLAN_WAKUP_MSG_WAIT_TIMEOUT);
                goto wakeup_fail;
            }
        }
        else
        {
            pst_wlan_pm->ul_wakeup_fail_set_reg++;
            OAM_ERROR_LOG0(0, OAM_SF_PWR,"oal_sdio_wakeup_dev Fail to set 0xf0 = 0");
            pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;
            oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
            goto wakeup_fail;
        }
    }

    pst_wlan_pm->ul_wakeup_succ++;
    DECLARE_DFT_TRACE_KEY_INFO("wlan_wakeup_succ",OAL_DFT_TRACE_SUCC);
    //PS_PRINT_INFO("wlan_pm_wakeup_dev succ, wakelock cnt %d!\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);

    pst_wlan_pm->ul_wdg_timeout_curr_cnt = 0;
    pst_wlan_pm->ul_packet_cnt           = 0;

    wlan_pm_feed_wdg();
    uc_wakeup_err_count = 0;

    usleep_range(500,510);

    return OAL_SUCC;
wakeup_fail:
    DECLARE_DFT_TRACE_KEY_INFO("wlan_wakeup_fail",OAL_DFT_TRACE_FAIL);
    uc_wakeup_err_count++;

    /* pm����ʧ�ܳ������ޣ�����dfr���� */
    if (WLAN_WAKEUP_FAIL_MAX_TIMES < uc_wakeup_err_count)
    {
        OAM_ERROR_LOG1(0, OAM_SF_PWR,"Now ready to enter DFR process after [%d]times wlan_wakeup_fail!", uc_wakeup_err_count);
        uc_wakeup_err_count = 0;
        oal_sdio_exception_submit(oal_get_sdio_default_handler(), WIFI_WAKEUP_FAIL);
        //wifi_exception_work_submit(TIMER_TIMEOUT);
    }
    CHR_EXCEPTION(CHR_WIFI_DRV(CHR_WIFI_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_WAKEUP_DEV));

    return OAL_FAIL;

}

oal_void wlan_pm_wakeup_dev_ack(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm;

    if(oal_atomic_read(&g_wakeup_dev_wait_ack))
    {
        pst_wlan_pm = wlan_pm_get_drv();

        if (OAL_PTR_NULL == pst_wlan_pm)
        {
            return ;
        }

        pst_wlan_pm->ul_wakeup_dev_ack++;

        OAL_COMPLETE(&pst_wlan_pm->st_wakeup_done);


        oal_atomic_set(&g_wakeup_dev_wait_ack,0);
    }

    return;

}

/*****************************************************************************
 �� �� ��  : wlan_pm_open_bcpu
 ��������  : ����BCPU
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint  wlan_pm_open_bcpu(oal_void)
{
#define RETRY_TIMES (3)
    oal_uint32           i;
    oal_int32            ret = OAL_FAIL;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint32           ul_ret;

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

     /*ͨ��sdio��������⸴λBCPU*/
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"sdio open BCPU");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    for (i = 0; i < RETRY_TIMES; i++)
    {
        ret = wlan_pm_wakeup_dev();
        if (OAL_SUCC == ret)
        {
            break;
        }
    }

    if(OAL_SUCC != ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_dev fail!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_FAIL;
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_dev succ, retry times [%d]", i);

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_open_bcpu_done);

    ul_ret = oal_sdio_send_msg(pst_wlan_pm->pst_sdio, H2D_MSG_RESET_BCPU);
    if(OAL_SUCC == ul_ret)
    {
        /*�ȴ�deviceִ������*/
        up(&pst_wlan_pm->pst_sdio->gpio_rx_sema);
        ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_open_bcpu_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_OPEN_BCPU_WAIT_TIMEOUT));
        if(0 == ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_open_bcpu wait device ACK timeout !");
            hcc_tx_transfer_unlock(hcc_get_default_handler());
            return OAL_FAIL;
        }

        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return  OAL_SUCC;
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"fail to send H2D_MSG_RESET_BCPU");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return  OAL_FAIL;
    }
}

/*****************************************************************************
 �� �� ��  : wlan_pm_wakeup_host
 ��������  : device����host
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint wlan_pm_wakeup_host(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAL_BUG_ON(!pst_wlan_pm);

    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    OAM_INFO_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_host get wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    if(0!=wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_wakeup_work))
    {
        pst_wlan_pm->ul_wakeup_fail_submit_work++;
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_host submit work fail, release wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
    }
    else
    {
        pst_wlan_pm->ul_wakeup_succ_work_submit++;
    }

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : wlan_pm_work_submit
 ��������  : �ύһ��kernel work
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_int wlan_pm_work_submit(struct wlan_pm_s    *pst_wlan_pm, oal_work_stru* pst_worker)
{
    oal_int  i_ret    = 0;

    if(work_busy(pst_worker))
    {
        /*If comm worker is processing,
          we need't submit again*/
        i_ret = -OAL_EBUSY;
        goto done;
    }
    else
    {
        OAM_INFO_LOG1(0, OAM_SF_PWR,"WiFi %pF Worker Submit\n",(void*)pst_worker->func);
        if(false==queue_work(pst_wlan_pm->pst_pm_wq, pst_worker))
        {
           i_ret = -OAL_EFAIL;
        }
    }
done:
    return i_ret;
}

/*****************************************************************************
 �� �� ��  : wlan_pm_wakeup_work
 ��������  : device����host work
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
void wlan_pm_wakeup_work(oal_work_stru *pst_worker)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint l_ret;

    OAM_INFO_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_work start!\n");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    l_ret = wlan_pm_wakeup_dev();
    if(OAL_UNLIKELY(OAL_SUCC!=l_ret))
    {
        DECLARE_DFT_TRACE_KEY_INFO("wlan_wakeup_fail",OAL_DFT_TRACE_FAIL);
    }

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    /*match for the work submit*/
    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
    DECLARE_DFT_TRACE_KEY_INFO("wlan_d2h_wakeup_succ",OAL_DFT_TRACE_SUCC);
    OAM_INFO_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_work release wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    return;

}

/*****************************************************************************
 �� �� ��  : wlan_pm_wakeup_done_callback
 ��������  : deviceӦ��wakeup succ��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

int32 wlan_pm_wakeup_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_INFO_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_done_callback !");

	pst_wlan_pm->ul_wakeup_done_callback++;

	wlan_pm_wakeup_dev_ack();

    return SUCCESS;

}

/*****************************************************************************
 �� �� ��  : wlan_pm_close_done_callback
 ��������  : deviceӦ��poweroff ack��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

int32 wlan_pm_close_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close_done_callback !");

    /*�ر�RXͨ������ֹSDIO RX thread��������SDIO*/
    oal_disable_sdio_state(oal_get_sdio_default_handler(), OAL_SDIO_RX);

    pst_wlan_pm->ul_close_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_close_done);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"complete H2D_MSG_PM_WLAN_OFF done!");

    return SUCCESS;

}

/*****************************************************************************
 �� �� ��  : wlan_pm_open_bcpu_done_callback
 ��������  : deviceӦ��open bcpu ack��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

int32 wlan_pm_open_bcpu_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_open_bcpu_done_callback !");

    pst_wlan_pm->ul_open_bcpu_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_open_bcpu_done);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"complete H2D_MSG_RESET_BCPU done!");

    return SUCCESS;
}

/*****************************************************************************
 �� �� ��  : wlan_pm_close_bcpu_done_callback
 ��������  : deviceӦ��open bcpu ack��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

int32 wlan_pm_close_bcpu_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close_bcpu_done_callback !");

    pst_wlan_pm->ul_close_bcpu_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_close_bcpu_done);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"complete H2D_MSG_PM_BCPU_OFF done!");

    return SUCCESS;
}

/*****************************************************************************
 �� �� ��  : wlan_pm_halt_bcpu_done_callback
 ��������  : deviceӦ��open bcpu ack��Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

int32 wlan_pm_halt_bcpu_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_halt_bcpu_done_callback !");

    OAL_COMPLETE(&pst_wlan_pm->st_halt_bcpu_done);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"complete wlan_pm_halt_bcpu_done_callback done!");

    return SUCCESS;
}

/*****************************************************************************
 �� �� ��  : wlan_pm_sleep_work
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
void wlan_pm_sleep_work(oal_work_stru *pst_worker)
{
   struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
   //oal_uint             flags;
   oal_int32           l_ret;
   oal_uint32           ul_ret;
   oal_uint8            uc_retry;
   oal_uint32           ul_wifi_pause_pm = OAL_FALSE;
   static oal_uint8     uc_fail_sleep_count = 0;


   hcc_tx_transfer_lock(hcc_get_default_handler());

   if(OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
   {
        wlan_pm_feed_wdg();
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return ;
   }

   /*Э��ջ�ص���ȡ�Ƿ�pause�͹���*/
   if(pst_wlan_pm->st_wifi_srv_handler.p_wifi_srv_get_pm_pause_func)
   {
       ul_wifi_pause_pm = pst_wlan_pm->st_wifi_srv_handler.p_wifi_srv_get_pm_pause_func();
   }

   if(OAL_TRUE == ul_wifi_pause_pm)
   {
        wlan_pm_feed_wdg();
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return ;
   }

   if(HOST_ALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
   {
     //PS_PRINT_INFO("wakeuped,need not do again!\n");
     wlan_pm_feed_wdg();
     hcc_tx_transfer_unlock(hcc_get_default_handler());
     return ;
   }

   pst_wlan_pm->ul_sleep_stage = SLEEP_REQ_SND;

   OAL_INIT_COMPLETION(&pst_wlan_pm->st_sleep_request_ack);

   l_ret = wlan_pm_sleep_request(pst_wlan_pm);
   if(OAL_SUCC != l_ret)
   {
      pst_wlan_pm->ul_sleep_fail_request++;
      OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_sleep_request fail !\n");
      goto fail_sleep;
   }

   //PS_PRINT_INFO(WLAN_PM_MODULE"wlan_pm_sleep_request SUCC!\n");
   up(&pst_wlan_pm->pst_sdio->gpio_rx_sema);

   ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_sleep_request_ack, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_SLEEP_MSG_WAIT_TIMEOUT));
   if(0 == ul_ret)
   {
       pst_wlan_pm->ul_sleep_fail_wait_timeout++;
       OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_sleep_work wait completion fail !\n");
       goto fail_sleep;
   }

   if(SLEEP_ALLOW_RCV == pst_wlan_pm->ul_sleep_stage)
   {

       oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_FALSE);

       pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;

       l_ret = oal_sdio_sleep_dev(pst_wlan_pm->pst_sdio);
       OAL_IO_PRINT("wifi sleep cmd send ,wakelock cnt %lu\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
       if(OAL_SUCC!=l_ret)
       {
            for(uc_retry = 0;uc_retry<WLAN_SDIO_MSG_RETRY_NUM;uc_retry++)
            {
                msleep(10);
                l_ret = oal_sdio_sleep_dev(pst_wlan_pm->pst_sdio);
                if(OAL_SUCC == l_ret)
                {
                    break;
                }
                OAM_ERROR_LOG2(0, OAM_SF_PWR,"oal_sdio_sleep_dev retry %d ret = %d",uc_retry,l_ret);
            }

            /*after max retry still fail,log error*/
           if(OAL_SUCC!=l_ret)
           {
                pst_wlan_pm->ul_sleep_fail_set_reg++;
                DECLARE_DFT_TRACE_KEY_INFO("wlan_sleep_cmd_fail",OAL_DFT_TRACE_FAIL);
                OAM_ERROR_LOG1(0, OAM_SF_PWR,"oal_sdio_sleep_dev Fail ret = %d\r\n",l_ret);
                pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;
                oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);
                goto fail_sleep;
           }

       }

       oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);
   }
   else
   {

       pst_wlan_pm->ul_sleep_fail_forbid++;
       OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_sleep_work device forbid sleep %ld\n",pst_wlan_pm->ul_sleep_stage);
       DECLARE_DFT_TRACE_KEY_INFO("wlan_forbid_sleep",OAL_DFT_TRACE_SUCC);
       goto sleep_forbid;
   }

   pst_wlan_pm->ul_sleep_stage = SLEEP_CMD_SND;

   hcc_tx_transfer_unlock(hcc_get_default_handler());
   oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);

   DECLARE_DFT_TRACE_KEY_INFO("wlan_sleep_ok",OAL_DFT_TRACE_SUCC);
   pst_wlan_pm->ul_sleep_succ++;
   if(0!=pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count)
   {
      OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_sleep_work release wakelock %lu!\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
   }

   uc_fail_sleep_count = 0;

   return;

fail_sleep:

    uc_fail_sleep_count++;
    wlan_pm_feed_wdg();
    hcc_tx_transfer_unlock(hcc_get_default_handler());

    /* pm����ʧ�ܳ������ޣ�����dfr���� */
    if (WLAN_WAKEUP_FAIL_MAX_TIMES < uc_fail_sleep_count)
    {
        OAM_ERROR_LOG1(0, OAM_SF_PWR,"Now ready to enter DFR process after [%d]times wlan_sleep_fail!", uc_fail_sleep_count);
        uc_fail_sleep_count = 0;
        wlan_pm_stop_wdg(pst_wlan_pm);
        oal_sdio_exception_submit(oal_get_sdio_default_handler(), WIFI_WAKEUP_FAIL);
        //wifi_exception_work_submit(TIMER_TIMEOUT);
    }
    CHR_EXCEPTION(CHR_WIFI_DRV(CHR_WIFI_DRV_EVENT_PLAT, CHR_PLAT_DRV_ERROR_WAKEUP_DEV));
    return;

sleep_forbid:

    uc_fail_sleep_count = 0;
    wlan_pm_feed_wdg();
    hcc_tx_transfer_unlock(hcc_get_default_handler());
    return ;

}

void wlan_pm_freq_adjust_work(oal_work_stru *pst_worker)
{

    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();


    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return ;
    }

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    if(OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_adjust_to_level_func)
    {
       g_pst_alg_process_func.p_auto_freq_adjust_to_level_func();
    }
    else
    {
      OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_freq_adjust_work:NO p_auto_freq_adjust_to_level_func registered");
    }
#endif

    hcc_tx_transfer_unlock(hcc_get_default_handler());

}

/*****************************************************************************
 �� �� ��  : wlan_pm_state_get
 ��������  : ��ȡpm��sleep״̬
 �������  :
 �������  :
 �� �� ֵ  : 1:allow to sleep; 0:disallow to sleep
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_uint wlan_pm_state_get(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    return pst_wlan_pm->ul_wlan_dev_state;
}

/*****************************************************************************
 �� �� ��  : wlan_pm_state_set
 ��������  : ��ȡpm��sleep״̬
 �������  :
 �������  :
 �� �� ֵ  : 1:allow to sleep; 0:disallow to sleep
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_void wlan_pm_state_set(struct wlan_pm_s  *pst_wlan_pm,oal_uint ul_state)
{

    pst_wlan_pm->ul_wlan_dev_state = ul_state;

}
/*****************************************************************************
 �� �� ��  : wlan_pm_set_timeout
 ��������  : ˯�߶�ʱ����ʱʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  wlan_pm_set_timeout(oal_uint32 ul_timeout)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return ;
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_set_timeout[%d]",ul_timeout);

    pst_wlan_pm ->ul_wdg_timeout_cnt = ul_timeout;

    pst_wlan_pm->ul_wdg_timeout_curr_cnt = 0;

    pst_wlan_pm->ul_packet_cnt = 0;

    wlan_pm_feed_wdg();

}
EXPORT_SYMBOL_GPL(wlan_pm_set_timeout);
/*****************************************************************************
 �� �� ��  : wlan_pm_feed_wdg
 ��������  : ����50ms˯�߶�ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  wlan_pm_feed_wdg(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    pst_wlan_pm->ul_sleep_feed_wdg_cnt++;
    mod_timer(&pst_wlan_pm->st_watchdog_timer, jiffies + msecs_to_jiffies(WLAN_SLEEP_TIMER_PERIOD));
}


/*****************************************************************************
 �� �� ��  : wlan_pm_stop_wdg
 ��������  : ֹͣ50ms˯�߶�ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

int32 wlan_pm_stop_wdg(struct wlan_pm_s *pst_wlan_pm_info)
{
    OAL_IO_PRINT("wlan_pm_stop_wdg \r\n");

    pst_wlan_pm_info->ul_wdg_timeout_curr_cnt = 0;
    pst_wlan_pm_info->ul_packet_cnt = 0;

    if(in_interrupt())
    {
        return del_timer(&pst_wlan_pm_info->st_watchdog_timer);
    }
    else
    {
        return del_timer_sync(&pst_wlan_pm_info->st_watchdog_timer);
    }

}


/*****************************************************************************
 �� �� ��  : wlan_pm_wdg_timeout
 ��������  : 50ms˯�߶�ʱ����ʱ�����ύһ��sleep work
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

void wlan_pm_wdg_timeout(struct wlan_pm_s *pm_data)
{


    //OAL_IO_PRINT("wlan_pm_wdg_timeout.... \r\n");

    if(NULL == pm_data)
    {
        return;
    }

#ifdef _PRE_WLAN_FEATURE_AUTO_FREQ
    if(OAL_PTR_NULL != g_pst_alg_process_func.p_auto_freq_process_func)
    {
        pm_data->ul_packet_cnt += g_pst_alg_process_func.p_auto_freq_process_func();
    }
    else
    {
        OAM_ERROR_LOG0(0,OAM_SF_PWR, "wlan_pm_wdg_timeout:NO p_auto_freq_process_func registered");
        goto restart_timer;
    }
#endif

    /*�͵�Ƶ����һ��timer���͹��Ĺر�ʱtimer����ͣ*/
    if(pm_data->ul_wlan_pm_enable)
    {
		if(0 == pm_data->ul_packet_cnt)
		{
			pm_data->ul_wdg_timeout_curr_cnt++;
			if((pm_data->ul_wdg_timeout_curr_cnt == pm_data->ul_wdg_timeout_cnt))
			{
                if(0 != wlan_pm_work_submit(pm_data, &pm_data->st_sleep_work))
                {
                    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_sleep_work submit fail,work is running !\n");
                }
                else
                {
                    /*�ύ��sleep work�󣬶�ʱ���������������ظ��ύsleep work*/
                    pm_data->ul_sleep_work_submit++;
                    return;
                }

			}
		}
		else
		{
			//OAL_IO_PRINT("wlan_pm_wdg_timeout %d have packet %d.... \r\n",pm_data->ul_wdg_timeout_curr_cnt,pm_data->ul_packet_cnt);
			pm_data->ul_wdg_timeout_curr_cnt = 0;
        	pm_data->ul_packet_cnt           = 0;
		}

    }
    else
    {
        pm_data->ul_packet_cnt = 0;
    }

restart_timer:
    //OAL_IO_PRINT("wlan_pm_feed_wdg.... \r\n");
    wlan_pm_feed_wdg();


    return;

}

/*****************************************************************************
 �� �� ��  : wlan_pm_adjust_feq
 ��������  : �ύһ��work������host��device��CPU��DDRƵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ʼ������ֵ���ɹ���ʧ��ԭ��
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_uint wlan_pm_adjust_feq(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(!auto_freq_enable)
        return OAL_SUCC;

    OAL_BUG_ON(!pst_wlan_pm);

    if(0!=wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_freq_adjust_work))
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_adjust_feq submit work fail !\n");
    }

    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_adjust_feq);

/*****************************************************************************
 �� �� ��  : wlan_pm_poweroff_cmd
 ��������  : ����Ϣ��device��wifi device�ر�wifiϵͳ��Դ���ȴ�bcpu�����µ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 wlan_pm_poweroff_cmd(oal_void)
{
    oal_int32            ret;
    //oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"Send H2D_MSG_PM_WLAN_OFF cmd");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_SUCC != wlan_pm_wakeup_dev())
    {
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_FAIL;
    }


    ret =  oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_PM_WLAN_OFF);
    if(OAL_SUCC == ret)
    {
        /*�ȴ�deviceִ������*/
        msleep(20);
        if(0==board_get_wlan_wkup_gpio_val())
        {
            OAM_ERROR_LOG1(0, OAM_SF_PWR,"wlan_pm_poweroff_cmd  wait device ACK timeout && GPIO_LEVEL[%d] !",board_get_wlan_wkup_gpio_val());

#ifdef PLATFORM_DEBUG_ENABLE
            debug_uart_read_wifi_mem(OAL_FALSE);
#endif
            hcc_tx_transfer_unlock(hcc_get_default_handler());

            return OAL_FAIL;
        }

    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"fail to send H2D_MSG_PM_WLAN_OFF");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return  OAL_FAIL;
    }

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    return OAL_SUCC;


}

/*****************************************************************************
 �� �� ��  : wlan_pm_shutdown_bcpu_cmd
 ��������  : ����Ϣ��device��wifi device�ر�BCPU
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 wlan_pm_shutdown_bcpu_cmd(oal_void)
{
#define RETRY_TIMES (3)
    oal_uint32           i;
    oal_int32            ret = OAL_FAIL;
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"Send H2D_MSG_PM_BCPU_OFF cmd");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    for (i = 0; i < RETRY_TIMES; i++)
    {
        ret = wlan_pm_wakeup_dev();
        if (OAL_SUCC == ret)
        {
            break;
        }
    }

    if(OAL_SUCC != ret)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_dev fail!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_FAIL;
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_dev succ, retry times [%d]", i);

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_bcpu_done);

    ret =  oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_PM_BCPU_OFF);
    if(OAL_SUCC == ret)
    {
        /*�ȴ�deviceִ������*/
        ul_ret = oal_wait_for_completion_timeout(&pst_wlan_pm->st_close_bcpu_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_POWEROFF_ACK_WAIT_TIMEOUT));
        if(0 == ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_shutdown_bcpu_cmd wait device ACK timeout !");
            hcc_tx_transfer_unlock(hcc_get_default_handler());
            return OAL_FAIL;
        }
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"fail to send H2D_MSG_PM_BCPU_OFF");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return  OAL_FAIL;
    }

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wlan_pm_dump_info
 ��������  : debug, ����Ϣ��device���������ά����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

void wlan_pm_dump_host_info(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(NULL == pst_wlan_pm)
    {
        return;
    }

    OAL_IO_PRINT("----------wlan_pm_dump_host_info begin-----------\n");
    OAL_IO_PRINT("power on:%ld, enable:%ld,g_wlan_pm_switch:%d\n",pst_wlan_pm->ul_wlan_power_state,pst_wlan_pm->ul_wlan_pm_enable,g_wlan_pm_switch);
    OAL_IO_PRINT("dev state:%ld, sleep stage:%ld\n",pst_wlan_pm->ul_wlan_dev_state,pst_wlan_pm->ul_sleep_stage);
    OAL_IO_PRINT("open:%d,close:%d\n",pst_wlan_pm->ul_open_cnt,pst_wlan_pm->ul_close_cnt);
    OAL_IO_PRINT("sdio suspend:%d,sdio resume:%d\n",pst_wlan_pm->pst_sdio->ul_sdio_suspend,pst_wlan_pm->pst_sdio->ul_sdio_resume);
    OAL_IO_PRINT("gpio_intr[no.%lu]:%llu\n",pst_wlan_pm->pst_sdio->ul_wlan_irq,pst_wlan_pm->pst_sdio->gpio_int_count);
    OAL_IO_PRINT("data_intr:%llu\n",pst_wlan_pm->pst_sdio->data_int_count);
    OAL_IO_PRINT("wakeup_intr:%llu\n",pst_wlan_pm->pst_sdio->wakeup_int_count);
    OAL_IO_PRINT("D2H_MSG_WAKEUP_SUCC:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_WAKEUP_SUCC].count);
    OAL_IO_PRINT("D2H_MSG_ALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_ALLOW_SLEEP].count);
    OAL_IO_PRINT("D2H_MSG_DISALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_DISALLOW_SLEEP].count);


    OAL_IO_PRINT("wakeup_dev_wait_ack:%d\n",oal_atomic_read(&g_wakeup_dev_wait_ack));
    OAL_IO_PRINT("wakeup_succ:%d\n",pst_wlan_pm->ul_wakeup_succ);
    OAL_IO_PRINT("wakeup_dev_ack:%d\n",pst_wlan_pm->ul_wakeup_dev_ack);
    OAL_IO_PRINT("wakeup_done_callback:%d\n",pst_wlan_pm->ul_wakeup_done_callback);
    OAL_IO_PRINT("wakeup_succ_work_submit:%d\n",pst_wlan_pm->ul_wakeup_succ_work_submit);
    OAL_IO_PRINT("wakeup_fail_wait_sdio:%d\n",pst_wlan_pm->ul_wakeup_fail_wait_sdio);
    OAL_IO_PRINT("wakeup_fail_timeout:%d\n",pst_wlan_pm->ul_wakeup_fail_timeout);
    OAL_IO_PRINT("wakeup_fail_set_reg:%d\n",pst_wlan_pm->ul_wakeup_fail_set_reg);
    OAL_IO_PRINT("wakeup_fail_submit_work:%d\n",pst_wlan_pm->ul_wakeup_fail_submit_work);
    OAL_IO_PRINT("sleep_succ:%d\n",pst_wlan_pm->ul_sleep_succ);
    OAL_IO_PRINT("sleep feed wdg:%d\n",pst_wlan_pm->ul_sleep_feed_wdg_cnt);
    OAL_IO_PRINT("sleep_fail_request:%d\n",pst_wlan_pm->ul_sleep_fail_request);
    OAL_IO_PRINT("sleep_fail_set_reg:%d\n",pst_wlan_pm->ul_sleep_fail_set_reg);
    OAL_IO_PRINT("sleep_fail_wait_timeout:%d\n",pst_wlan_pm->ul_sleep_fail_wait_timeout);
    OAL_IO_PRINT("sleep_fail_forbid:%d\n",pst_wlan_pm->ul_sleep_fail_forbid);
    OAL_IO_PRINT("sleep_work_submit:%d\n",pst_wlan_pm->ul_sleep_work_submit);
    OAL_IO_PRINT("wklock_cnt:%lu\n \n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
    OAL_IO_PRINT("----------wlan_pm_dump_host_info end-----------\n");

}

/*****************************************************************************
 �� �� ��  : wlan_pm_host_info_print
 ��������  : catά��ڵ����host�͹���ͳ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  : ��
 ��������  : ��

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : zourong 00274374
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_int32 wlan_pm_host_info_print(struct wlan_pm_s *pst_wlan_pm,char* buf,oal_int32 buf_len)
{
    oal_int32 ret = 0;

    ret += snprintf(buf + ret , buf_len - ret,"----------wlan_pm_host_info_print begin-----------\n");
    ret += snprintf(buf + ret , buf_len - ret,"power on:%ld, enable:%ld,g_wlan_pm_switch:%d\n",pst_wlan_pm->ul_wlan_power_state,pst_wlan_pm->ul_wlan_pm_enable,g_wlan_pm_switch);
    ret += snprintf(buf + ret , buf_len - ret,"dev state:%ld, sleep stage:%ld\n",pst_wlan_pm->ul_wlan_dev_state,pst_wlan_pm->ul_sleep_stage);
    ret += snprintf(buf + ret , buf_len - ret,"open:%d,close:%d\n",pst_wlan_pm->ul_open_cnt,pst_wlan_pm->ul_close_cnt);
    ret += snprintf(buf + ret , buf_len - ret,"sdio suspend:%d,sdio resume:%d\n",pst_wlan_pm->pst_sdio->ul_sdio_suspend,pst_wlan_pm->pst_sdio->ul_sdio_resume);
    ret += snprintf(buf + ret , buf_len - ret,"gpio_intr[no.%lu]:%llu\n",pst_wlan_pm->pst_sdio->ul_wlan_irq,pst_wlan_pm->pst_sdio->gpio_int_count);
    ret += snprintf(buf + ret , buf_len - ret,"data_intr:%llu\n",pst_wlan_pm->pst_sdio->data_int_count);
    ret += snprintf(buf + ret , buf_len - ret,"wakeup_intr:%llu\n",pst_wlan_pm->pst_sdio->wakeup_int_count);
    ret += snprintf(buf + ret , buf_len - ret,"D2H_MSG_WAKEUP_SUCC:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_WAKEUP_SUCC].count);
    ret += snprintf(buf + ret , buf_len - ret,"D2H_MSG_ALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_ALLOW_SLEEP].count);
    ret += snprintf(buf + ret , buf_len - ret,"D2H_MSG_DISALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_DISALLOW_SLEEP].count);


    ret += snprintf(buf + ret , buf_len - ret,"wakeup_dev_wait_ack:%d\n",oal_atomic_read(&g_wakeup_dev_wait_ack));
    ret += snprintf(buf + ret , buf_len - ret,"wakeup_succ:%d\n",pst_wlan_pm->ul_wakeup_succ);
    ret += snprintf(buf + ret , buf_len - ret,"wakeup_dev_ack:%d\n",pst_wlan_pm->ul_wakeup_dev_ack);
    ret += snprintf(buf + ret , buf_len - ret,"wakeup_done_callback:%d\n",pst_wlan_pm->ul_wakeup_done_callback);
    ret += snprintf(buf + ret , buf_len - ret,"wakeup_succ_work_submit:%d\n",pst_wlan_pm->ul_wakeup_succ_work_submit);
    ret += snprintf(buf + ret , buf_len - ret,"wakeup_fail_wait_sdio:%d\n",pst_wlan_pm->ul_wakeup_fail_wait_sdio);
    ret += snprintf(buf + ret , buf_len - ret,"wakeup_fail_timeout:%d\n",pst_wlan_pm->ul_wakeup_fail_timeout);
    ret += snprintf(buf + ret , buf_len - ret,"wakeup_fail_set_reg:%d\n",pst_wlan_pm->ul_wakeup_fail_set_reg);
    ret += snprintf(buf + ret , buf_len - ret,"wakeup_fail_submit_work:%d\n",pst_wlan_pm->ul_wakeup_fail_submit_work);
    ret += snprintf(buf + ret , buf_len - ret,"sleep_succ:%d\n",pst_wlan_pm->ul_sleep_succ);
    ret += snprintf(buf + ret , buf_len - ret,"sleep feed wdg:%d\n",pst_wlan_pm->ul_sleep_feed_wdg_cnt);
    ret += snprintf(buf + ret , buf_len - ret,"sleep_fail_request:%d\n",pst_wlan_pm->ul_sleep_fail_request);
    ret += snprintf(buf + ret , buf_len - ret,"sleep_fail_set_reg:%d\n",pst_wlan_pm->ul_sleep_fail_set_reg);
    ret += snprintf(buf + ret , buf_len - ret,"sleep_fail_wait_timeout:%d\n",pst_wlan_pm->ul_sleep_fail_wait_timeout);
    ret += snprintf(buf + ret , buf_len - ret,"sleep_fail_forbid:%d\n",pst_wlan_pm->ul_sleep_fail_forbid);
    ret += snprintf(buf + ret , buf_len - ret,"sleep_work_submit:%d\n",pst_wlan_pm->ul_sleep_work_submit);
    ret += snprintf(buf + ret , buf_len - ret,"wklock_cnt:%lu\n \n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);
    ret += snprintf(buf + ret , buf_len - ret,"----------wlan_pm_host_info_print end-----------\n");

    return ret;
}

void wlan_pm_dump_device_info(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_PM_DEBUG);
}


void wlan_pm_info_clean(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

   // pst_wlan_pm->pst_sdio->gpio_int_count   = 0;
    pst_wlan_pm->pst_sdio->data_int_count   = 0;
    pst_wlan_pm->pst_sdio->wakeup_int_count = 0;

    pst_wlan_pm->pst_sdio->msg[D2H_MSG_WAKEUP_SUCC].count = 0;
    pst_wlan_pm->pst_sdio->msg[D2H_MSG_ALLOW_SLEEP].count = 0;
    pst_wlan_pm->pst_sdio->msg[D2H_MSG_DISALLOW_SLEEP].count = 0;
    pst_wlan_pm->pst_sdio->ul_sdio_suspend               = 0;
    pst_wlan_pm->pst_sdio->ul_sdio_resume                = 0;

    pst_wlan_pm->ul_wakeup_succ = 0;
	pst_wlan_pm->ul_wakeup_dev_ack = 0;
    pst_wlan_pm->ul_wakeup_done_callback = 0;
    pst_wlan_pm->ul_wakeup_succ_work_submit = 0;
    pst_wlan_pm->ul_wakeup_fail_wait_sdio = 0;
    pst_wlan_pm->ul_wakeup_fail_timeout = 0;
    pst_wlan_pm->ul_wakeup_fail_set_reg = 0;
    pst_wlan_pm->ul_wakeup_fail_submit_work = 0;

    pst_wlan_pm->ul_sleep_succ = 0;
    pst_wlan_pm->ul_sleep_feed_wdg_cnt = 0;
    pst_wlan_pm->ul_wakeup_done_callback = 0;
    pst_wlan_pm->ul_sleep_fail_set_reg = 0;
    pst_wlan_pm->ul_sleep_fail_wait_timeout = 0;
    pst_wlan_pm->ul_sleep_fail_forbid = 0;
    pst_wlan_pm->ul_sleep_work_submit = 0;


    return;

}


oal_void wlan_pm_debug_sleep(void)
{
   struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_sleep_dev(pst_wlan_pm->pst_sdio);

    pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;

    return  ;
}

oal_void wlan_pm_debug_wakeup(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_wakeup_dev(pst_wlan_pm->pst_sdio);

    pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;

    return  ;
}

oal_void wlan_pm_debug_wake_lock(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    OAL_IO_PRINT("wlan_pm_debug_wake_lock:wklock_cnt = %lu\r\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    return  ;
}

oal_void wlan_pm_debug_wake_unlock(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
    OAL_IO_PRINT("wlan_pm_debug_wake_unlock:wklock_cnt = %lu\r\n",pst_wlan_pm->pst_sdio->st_sdio_wakelock.lock_count);

    return  ;
}



