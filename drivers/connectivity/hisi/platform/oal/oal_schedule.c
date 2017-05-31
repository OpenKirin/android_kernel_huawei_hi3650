/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_schedule.c
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2012��11��29��
  ����޸�   :
  ��������   : �������ԭ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��29��
    ��    ��   : t00231215
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
#include "oal_schedule.h"

#ifdef _PRE_WIFI_DMT
#include "dmt_stub.h"
#endif

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
/*****************************************************************************
 �� �� ��  : oal_timer_init
 ��������  : ��ʼ����ʱ��
 �������  : pst_timer: ��ʱ���ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oal_timer_init(oal_timer_list_stru *pst_timer, oal_uint32 ul_delay, oal_timer_func p_func, oal_uint ui_arg)
{
}

/*****************************************************************************
 �� �� ��  : oal_timer_delete
 ��������  : ɾ����ʱ��
 �������  : pst_timer: ��ʱ���ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  oal_timer_delete(oal_timer_list_stru *pst_timer)
{

    return 0;
}

/*****************************************************************************
 �� �� ��  : oal_timer_delete_sync
 ��������  : ͬ��ɾ����ʱ�������ڶ��
 �������  : pst_timer: ��ʱ���ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  oal_timer_delete_sync(oal_timer_list_stru *pst_timer)
{

    return 0;
}

/*****************************************************************************
 �� �� ��  : oal_timer_add
 ��������  : ���ʱ��
 �������  : pst_timer: ��ʱ���ṹ��ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oal_timer_add(oal_timer_list_stru *pst_timer)
{
}

/*****************************************************************************
 �� �� ��  : oal_timer_start
 ��������  : ������ʱ��
 �������  : pst_timer: �ṹ��ָ��
             ui_expires: ����������¼�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  oal_timer_start(oal_timer_list_stru *pst_timer, oal_uint ui_expires)
{

#ifdef  _PRE_WIFI_DMT
	DmtStub_StartTimer(MGMT_TIMER, ui_expires);  /*15ms �Ķ�ʱ���񣬴���frw_timer_timeout_proc_event */
#endif

    return OAL_SUCC;
}

#endif

#ifdef _PRE_OAL_FEATURE_TASK_NEST_LOCK
oal_void _oal_smp_task_lock_(oal_task_lock_stru* pst_lock,oal_ulong  claim_addr)
{
	DECLARE_WAITQUEUE(wait, current);

	oal_ulong flags;

	//might_sleep();/*called task must can sleep*/

	if(OAL_WARN_ON(in_interrupt() || in_atomic()))
	{
		DECLARE_DFT_TRACE_KEY_INFO("smp_task_lock_sched_warn", OAL_DFT_TRACE_EXCEP);
	    return;
	}

	add_wait_queue(&pst_lock->wq, &wait);
	oal_spin_lock_irq_save(&pst_lock->lock, &flags);
	while (1) {
		set_current_state(TASK_UNINTERRUPTIBLE);
		if (!pst_lock->claimed || pst_lock->claimer == current)
			break;
		oal_spin_unlock_irq_restore(&pst_lock->lock, &flags);
		schedule();
		oal_spin_lock_irq_save(&pst_lock->lock, &flags);
	}
	set_current_state(TASK_RUNNING);

	pst_lock->claimed = 1;
	pst_lock->claimer = current;
	pst_lock->claim_cnt++;

	oal_spin_unlock_irq_restore(&pst_lock->lock, &flags);
	remove_wait_queue(&pst_lock->wq, &wait);
}
oal_module_symbol(_oal_smp_task_lock_);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

