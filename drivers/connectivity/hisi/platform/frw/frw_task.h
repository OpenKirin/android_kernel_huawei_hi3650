/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : frw_task.h
  �� �� ��   : ����
  ��    ��   : mayuan m00212148
  ��������   : 2012��10��22��
  ����޸�   :
  ��������   : frw_task.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��22��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __FRW_TASK_H__
#define __FRW_TASK_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_TASK_H


/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* �̵߳�����״̬ */
typedef enum
{
    FRW_TASK_STATE_IRQ_UNBIND = 0, /* �̴߳�����ͣ״̬ */
    FRW_TASK_STATE_IRQ_BIND,       /* �̴߳�������״̬ */

    FRW_TASK_BUTT
}frw_task_state_enum;

typedef oal_uint8 frw_task_state_enum_uint8;
/*****************************************************************************
  4 STRUCT����
*****************************************************************************/
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
typedef struct
{
    oal_task_stru               *pst_event_kthread;                              /*  task���� */
    oal_wait_queue_head_stru     frw_wq;                                         /* waitqueue */
    oal_uint8                    uc_task_state;                                  /* �߳�״̬��0��ͣ��1���� */
    oal_uint8                    auc_resv[3];
    oal_uint32                   ul_total_loop_cnt;
    oal_uint32                   ul_total_event_cnt;/*ͳ���߳̿�ת����*/
    oal_uint32                   ul_max_empty_count;
    oal_void                    (*p_event_handler_func)(oal_void* _pst_bind_cpu);/* kthread������ */
}frw_task_stru;

#elif (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_TASKLET)
typedef struct
{
    oal_tasklet_stru    st_event_tasklet;                    /* tasklet���� */
    oal_void           (*p_event_handler_func)(oal_uint);    /* tasklet������� */
}frw_task_stru;
#endif

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
extern frw_task_stru g_ast_event_task[];

/*****************************************************************************
  6 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  7 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern oal_uint32  frw_task_init(oal_void);
extern oal_void frw_task_exit(oal_void);
extern oal_void  frw_task_event_handler_register(oal_void (*p_func)(oal_uint));
extern oal_void frw_task_set_state(oal_uint32 ul_core_id, oal_uint8 uc_task_state);
extern oal_uint8 frw_task_get_state(oal_uint32 ul_core_id);
extern oal_void  frw_task_sched(oal_uint32 ul_core_id);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_task.h */
