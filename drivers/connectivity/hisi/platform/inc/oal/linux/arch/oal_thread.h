/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_thread.h
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2014��1��29��
  ����޸�   :
  ��������   : oal_thread.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��13��
    ��    ��   : z00274374
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_LINUX_THREAD_H__
#define __OAL_LINUX_THREAD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include <asm/atomic.h>
#include <linux/spinlock.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/jiffies.h>
#include <linux/time.h>
#include <asm/param.h>
#include <linux/timer.h>
#include <linux/sched.h>
#include <linux/kthread.h>

/*****************************************************************************
  2 STRUCT����
*****************************************************************************/
typedef struct task_struct          oal_task_stru;

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
  7 �궨��
*****************************************************************************/
#define oal_kthread_create        kthread_create
#define oal_kthread_bind          kthread_bind
#define oal_kthread_stop          kthread_stop
#define oal_kthread_run           kthread_run
#define oal_kthread_should_stop   kthread_should_stop
#define oal_schedule              schedule
#define oal_wake_up_process       wake_up_process
#define oal_set_current_state     set_current_state
#define oal_cond_resched          cond_resched

#if ((_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_5610EVB)\
    ||(_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_5610DMB)\
    ||(_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_VSPM310DMB)\
    ||(_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_WS835DMB))
#define oal_sched_setscheduler sched_setscheduler_export
#elif(_PRE_CONFIG_TARGET_PRODUCT == _PRE_TARGET_PRODUCT_TYPE_1102COMMON)
#define oal_sched_setscheduler sched_setscheduler
#endif
#define oal_set_user_nice          set_user_nice

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
