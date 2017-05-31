/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_workqueue.h
  �� �� ��   : ����
  ��    ��   : z00237171
  ��������   : 2014��1��29��
  ����޸�   :
  ��������   : oal_workqueue.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��1��29��
    ��    ��   : z00237171
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_LINUX_WORKQUEUE_H__
#define __OAL_LINUX_WORKQUEUE_H__

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
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/workqueue.h>

/*****************************************************************************
  2 STRUCT����
*****************************************************************************/
typedef struct workqueue_struct          oal_workqueue_stru;
typedef struct work_struct               oal_work_stru;
typedef struct delayed_work              oal_delayed_work;


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
#define OAL_INIT_WORK(_p_work, _p_func)            INIT_WORK(_p_work, _p_func)
#define OAL_INIT_DELAYED_WORK(_work,_func)         INIT_DELAYED_WORK(_work,_func)
#define OAL_CREATE_SINGLETHREAD_WORKQUEUE(_name)   create_singlethread_workqueue(_name)
#define oal_create_workqueue(name)      create_workqueue(name)

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : oal_create_singlethread_workqueue
 ��������  : ����һ�����̵߳Ĺ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��29��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_workqueue_stru*  oal_create_singlethread_workqueue(
                                                                    const oal_int8 *pc_workqueue_name)
{
    return create_singlethread_workqueue(pc_workqueue_name);
}

/*****************************************************************************
 �� �� ��  : oal_destroy_workqueue
 ��������  : ���ٹ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��29��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  oal_destroy_workqueue(oal_workqueue_stru   *pst_workqueue)
{
    destroy_workqueue(pst_workqueue);
}

/*****************************************************************************
 �� �� ��  : oal_queue_work
 ��������  : ���һ�����񵽹�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��29��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_queue_work(oal_workqueue_stru *pst_workqueue, oal_work_stru *pst_work)
{
    return queue_work(pst_workqueue, pst_work);
}

/**
 * queue_delayed_work - queue work on a workqueue after delay
 * @wq: workqueue to use
 * @dwork: delayable work to queue
 * @delay: number of jiffies to wait before queueing
 *
 * Equivalent to queue_delayed_work_on() but tries to use the local CPU.
 */
OAL_STATIC OAL_INLINE oal_int32  oal_queue_delayed_work(oal_workqueue_stru *pst_workqueue, oal_delayed_work *pst_work,oal_ulong delay)
{
    return queue_delayed_work(pst_workqueue, pst_work, delay);
}

/**
 * queue_delayed_work_on - queue work on specific CPU after delay
 * @cpu: CPU number to execute work on
 * @wq: workqueue to use
 * @dwork: work to queue
 * @delay: number of jiffies to wait before queueing
 *
 * Returns %false if @work was already on a queue, %true otherwise.  If
 * @delay is zero and @dwork is idle, it will be scheduled for immediate
 * */
OAL_STATIC OAL_INLINE oal_int32  oal_queue_delayed_work_on(oal_int32 cpu, oal_workqueue_stru *pst_workqueue, oal_delayed_work *pst_work,oal_ulong delay)
{
    return queue_delayed_work_on(cpu, pst_workqueue, pst_work, delay);
}

/*****************************************************************************
 �� �� ��  : oal_queue_delayed_system_work
 ��������  : queue work on system wq after delay
 �������  :  @dwork: delayable work to queue
              @delay: number of jiffies to wait before queueing
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��27��
    ��    ��   : z00262551
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_int32  oal_queue_delayed_system_work(oal_delayed_work *pst_work,oal_ulong delay)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 44))
    return queue_delayed_work(system_wq, pst_work, delay);
#else
    OAL_WARN_ON(1);
    return 1;
#endif
}

#define oal_work_is_busy(work) work_busy(work)

#define oal_cancel_delayed_work_sync(dwork) cancel_delayed_work_sync(dwork)

#define oal_cancel_work_sync(work)          cancel_work_sync(work)

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_workqueue.h */
