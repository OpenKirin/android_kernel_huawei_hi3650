/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : frw_task.c
  �� �� ��   : ����
  ��    ��   : mayuan m00212148
  ��������   : 2012��10��22��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��22��
    ��    ��   : mayuan m00212148
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
#include "platform_spec.h"
#include "frw_main.h"
#include "frw_event_main.h"
#include "frw_task.h"
#include "hal_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_TASK_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/******************************************************************************
    �¼�����ȫ�ֱ���
*******************************************************************************/
frw_task_stru g_ast_event_task[WLAN_FRW_MAX_NUM_CORES];

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)

/*****************************************************************************
 �� �� ��  : frw_set_thread_property
 ��������  : �����̲߳�������
 �������  : p: ��ǰ�߳�; policy: ���Ȳ���; param:
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : lingxuemeng 00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC void frw_set_thread_property(oal_task_stru *p, int policy, struct sched_param *param, long nice)
{
    OAL_BUG_ON(!p);
    OAL_BUG_ON(!param);

    if(oal_sched_setscheduler(p, policy, param))
    {
        OAL_IO_PRINT("[Error]set scheduler failed! %d\n", policy);
    }

    if(policy != SCHED_FIFO && policy != SCHED_RR)
    {
        OAL_IO_PRINT("set thread scheduler nice %ld\n", nice);
        oal_set_user_nice(p, nice);
    }

}

/*****************************************************************************
 �� �� ��  : frw_task_thread
 ��������  : frw �ں��߳�������
 �������  : ��id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : lingxuemeng 00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32 frw_task_thread(oal_void* ul_bind_cpu)
{
    oal_int32       ret = 0;
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
    oal_uint32 ul_empty_count = 0;
#endif

    allow_signal(SIGTERM);

    for (;;)
    {
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
        oal_uint32 ul_event_count;
#endif
        if (oal_kthread_should_stop())
        {
            break;
        }

        /*stateΪTASK_INTERRUPTIBLE��condition���������߳�������ֱ�������ѽ���waitqueue*/
        /*lint -e730*/
#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
        frw_event_last_pc_trace(__FUNCTION__,__LINE__, (oal_uint32)(oal_ulong)ul_bind_cpu);
#endif
        ret = OAL_WAIT_EVENT_INTERRUPTIBLE(g_ast_event_task[(oal_uint)ul_bind_cpu].frw_wq,  OAL_TRUE == frw_task_thread_condition_check((oal_uint)ul_bind_cpu));
        /*lint +e730*/
        if(OAL_UNLIKELY(-ERESTARTSYS == ret))
        {
            OAL_IO_PRINT("wifi task %s was interrupted by a signal\n", oal_get_current_task_name());
            break;
        }
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
        g_ast_event_task[(oal_uint)ul_bind_cpu].ul_total_loop_cnt++;

        ul_event_count = g_ast_event_task[(oal_uint)ul_bind_cpu].ul_total_event_cnt;
#endif
        frw_event_process_all_event((oal_uint)ul_bind_cpu);
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
        if(ul_event_count == g_ast_event_task[(oal_uint)ul_bind_cpu].ul_total_event_cnt)
        {
            /*��ת*/
            ul_empty_count++;
            if(ul_empty_count == 10000)
            {
                DECLARE_DFT_TRACE_KEY_INFO("frw_sched_too_much", OAL_DFT_TRACE_EXCEP);
            }
        }
        else
        {
            if(ul_empty_count > g_ast_event_task[(oal_uint)ul_bind_cpu].ul_max_empty_count)
            {
                g_ast_event_task[(oal_uint)ul_bind_cpu].ul_max_empty_count = ul_empty_count;
            }
            ul_empty_count = 0;
        }
#endif
#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
        frw_event_last_pc_trace(__FUNCTION__,__LINE__, (oal_uint32)(oal_ulong)ul_bind_cpu);
#endif
    }

    return 0;
}

/*****************************************************************************
 �� �� ��  : frw_task_init_kthread
 ��������  : kthread��ʼ���ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : lingxuemeng 00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_task_init(oal_void)
{
    oal_uint       ul_core_id;
    oal_task_stru   *pst_task;
    struct sched_param param = { 0 };

    OAL_MEMZERO(g_ast_event_task, OAL_SIZEOF(g_ast_event_task));

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        OAL_WAIT_QUEUE_INIT_HEAD(&g_ast_event_task[ul_core_id].frw_wq);

        pst_task = oal_kthread_create(frw_task_thread,(oal_void*)ul_core_id,"hisi_frw/%lu", ul_core_id);
        if (IS_ERR_OR_NULL(pst_task)) {
            return OAL_FAIL;
        }

        oal_kthread_bind(pst_task, ul_core_id);

        g_ast_event_task[ul_core_id].pst_event_kthread = pst_task;
        g_ast_event_task[ul_core_id].uc_task_state     = FRW_TASK_STATE_IRQ_UNBIND;

        param.sched_priority = 1;
        frw_set_thread_property(pst_task, SCHED_FIFO, &param, 0);

        oal_wake_up_process(g_ast_event_task[ul_core_id].pst_event_kthread);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_thread_exit
 ��������  : �߳��˳�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : lingxuemeng 00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void frw_task_exit(oal_void)
{
    oal_uint32       ul_core_id;

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        if (g_ast_event_task[ul_core_id].pst_event_kthread)
        {
            oal_kthread_stop(g_ast_event_task[ul_core_id].pst_event_kthread);
            g_ast_event_task[ul_core_id].pst_event_kthread = OAL_PTR_NULL;
        }
    }
}

/*****************************************************************************
 �� �� ��  : frw_task_event_handler_register
 ��������  : ���ⲿģ��ע��tasklet��������ִ�еĺ���
 �������  : p_func: ��Ҫ��ִ�еĺ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : lingxuemeng 00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  frw_task_event_handler_register(oal_void (*p_func)(oal_uint))
{

}

/*****************************************************************************
 �� �� ��  : frw_task_sched
 ��������  : ����eventʱ�䴦���̣߳���wake_event_interruptible��Ӧ
 �������  : ul_core_id: ��id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : lingxuemeng 00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void frw_task_sched(oal_uint32 ul_core_id)
{
    OAL_WAIT_QUEUE_WAKE_UP_INTERRUPT(&g_ast_event_task[ul_core_id].frw_wq);
}

/*****************************************************************************
 �� �� ��  : frw_task_set_state
 ��������  : �����ں��̵߳İ�״̬
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : zhoukaichun
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void frw_task_set_state(oal_uint32 ul_core_id, oal_uint8 uc_task_state)
{
    g_ast_event_task[ul_core_id].uc_task_state = uc_task_state;
}
/*****************************************************************************
 �� �� ��  : frw_task_get_state
 ��������  : ��ȡ�ں��̵߳İ�״̬
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��10��
    ��    ��   : zhoukaichun
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 frw_task_get_state(oal_uint32 ul_core_id)
{
    return g_ast_event_task[ul_core_id].uc_task_state;
}

#elif (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_TASKLET)

/*****************************************************************************
 �� �� ��  : frw_task_init
 ��������  : tasklet��ʼ���ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_task_init(oal_void)
{
    oal_uint32 ul_core_id;

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        oal_task_init(&g_ast_event_task[ul_core_id].st_event_tasklet, g_ast_event_task[ul_core_id].p_event_handler_func, 0);
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_task_exit
 ��������  : task �˳�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��29��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void frw_task_exit(oal_void)
{
    oal_uint32       ul_core_id;

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        oal_task_kill(&g_ast_event_task[ul_core_id].st_event_tasklet);
    }
}

/*****************************************************************************
 �� �� ��  : frw_task_event_handler_register
 ��������  : ���ⲿģ��ע��tasklet��������ִ�еĺ���
 �������  : p_func: ��Ҫ��ִ�еĺ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  frw_task_event_handler_register(oal_void (*p_func)(oal_uint))
{
    oal_uint32 ul_core_id;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_func))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_task_event_handler_register:: p_func is null ptr}");
        return;
    }

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        g_ast_event_task[ul_core_id].p_event_handler_func = p_func;
    }
}

/*****************************************************************************
 �� �� ��  : frw_remote_task_receive
 ��������  : ��tasklet����ִ�У���IPI�жϵ���ִ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��17��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void frw_remote_task_receive(void *info)
{
    oal_tasklet_stru *pst_task = (oal_tasklet_stru *)info;
    oal_task_sched(pst_task);
}

/*****************************************************************************
 �� �� ��  : frw_task_sched_on_cpu
 ��������  : ʹ��IPI�жϣ�����Ŀ��core�ϵ�taskletִ�д����¼�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��17��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void frw_task_sched_on_cpu(oal_tasklet_stru *pst_task, oal_uint32 ul_core_id)
{
    oal_smp_call_function_single(ul_core_id, frw_remote_task_receive, (void *)pst_task, 0);
}

/*****************************************************************************
 �� �� ��  : frw_task_sched
 ��������  : task���Ƚӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void frw_task_sched(oal_uint32 ul_core_id)
{
    oal_uint32 ul_this_cpu = OAL_GET_CORE_ID();

    if (oal_task_is_scheduled(&g_ast_event_task[ul_core_id].st_event_tasklet))
    {
        return;
    }

    if (ul_this_cpu == ul_core_id)
    {
        oal_task_sched(&g_ast_event_task[ul_core_id].st_event_tasklet);
    }
    else
    {
        frw_task_sched_on_cpu(&g_ast_event_task[ul_core_id].st_event_tasklet, ul_core_id);
    }
}

/*****************************************************************************
 �� �� ��  : frw_task_set_state
 ��������  : ����tasklet��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��17��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void frw_task_set_state(oal_uint32 ul_core_id, oal_uint8 uc_task_state)
{
}

/*****************************************************************************
 �� �� ��  : frw_task_get_state
 ��������  : ��ȡtasklet��״̬��taskletһֱ��˰�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��17��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 frw_task_get_state(oal_uint32 ul_core_id)
{
	return FRW_TASK_STATE_IRQ_BIND;
}

#endif

#ifdef _PRE_WLAN_FEATURE_SMP_SUPPORT
oal_module_symbol(frw_task_set_state);
oal_module_symbol(frw_task_get_state);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

