/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : frw_event_sched.c
  �� �� ��   : ����
  ��    ��   : mayuan m00212148
  ��������   : 2012��10��16��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��16��
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
#include "oam_ext_if.h"
#include "frw_main.h"
#include "frw_event_main.h"
#include "frw_event_sched.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_SCHED_C


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ����ԭ������
*****************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : frw_event_sched_deactivate_queue_no_lock
 ��������  : �ӵ��ȶ���ɾ��һ���¼�����
 �������  : pst_sched_queue: ���ȶ���ָ��
             pst_event_queue: �¼�����ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :


 �޸���ʷ      :
  1.��    ��   : 2015��3��31��
    ��    ��   : gaolin daihu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_sched_deactivate_queue_no_lock(
                frw_event_sched_queue_stru         *pst_sched_queue,
                frw_event_queue_stru               *pst_event_queue)
{
    if (0 != pst_event_queue->st_queue.uc_element_cnt)
    {
        return OAL_SUCC;
    }

    /* ���µ��ȶ����ϵ���Ȩ�ؼ����� */
    pst_sched_queue->ul_total_weight_cnt -= pst_event_queue->uc_weight_cnt;

    /* ���¼����е�Ȩ�ؼ��������� */
    pst_event_queue->uc_weight_cnt = 0;

    /* mayuan debug */
    if ((oal_uint)&pst_event_queue->st_list == (oal_uint)&pst_sched_queue->st_head)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "frw_event_sched_deactivate_queue, delete header itself.");
        OAL_BUG_ON(1);
    }

    /* ���¼����дӵ���������ɾ�� */
    oal_dlist_delete_entry(&pst_event_queue->st_list);

    /* ���¼�������Ϊ����Ծ״̬ */
    pst_event_queue->en_state = FRW_EVENT_QUEUE_STATE_INACTIVE;


    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_sched_activate_queue_no_lock
 ��������  : ����ȶ������һ���µ��¼�����
 �������  : past_sched_queue: ���ȶ���ָ��
                          pst_event_queue : �¼�����ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��5��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��23��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : ��װΪ�������ӿڣ����ֽӿڶԳ��ԣ��������ӿڵ���
*****************************************************************************/
oal_uint32  frw_event_sched_activate_queue_no_lock(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue)
{
    /* ����¼������Ѿ��ڿ�ִ�ж�����(���ڼ���״̬)����ֱ�ӷ��سɹ� */
    if (FRW_EVENT_QUEUE_STATE_ACTIVE == pst_event_queue->en_state)
    {
        return OAL_SUCC;
    }

    /* ��Ϊ�¼����е�Ȩ�ؼ����� */
    pst_event_queue->uc_weight_cnt = pst_event_queue->uc_weight;

    /* ���µ��ȶ����ϵ���Ȩ�ؼ����� */
    pst_sched_queue->ul_total_weight_cnt += pst_event_queue->uc_weight_cnt;

    /* ���¼����м�����������ĩβ */
    oal_dlist_add_tail(&pst_event_queue->st_list, &pst_sched_queue->st_head);

    /* ���¼�������Ϊ����״̬ */
    pst_event_queue->en_state = FRW_EVENT_QUEUE_STATE_ACTIVE;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : frw_event_sched_pick_next_event_queue_wrr
 ��������  : �ӵ���������ѡ��һ����������¼�
 �������  : pst_sched_queue: ���ȶ���ָ��
 �������  : pst_sched_queue: ���ȶ���ָ��
 �� �� ֵ  : �ɹ�: �¼��ڴ�ָ��
             �쳣���ߵ��ȶ���Ϊ��: OAL_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/

oal_void* frw_event_sched_pick_next_event_queue_wrr(frw_event_sched_queue_stru *pst_sched_queue)
{
    oal_dlist_head_stru       *pst_list;
    frw_event_queue_stru   *pst_event_queue = OAL_PTR_NULL;
    oal_void                      *p_event = OAL_PTR_NULL;
    oal_uint                       ul_flag = 0;

    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

    /* ���������������� */
    OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_sched_queue->st_head)
    {
        pst_event_queue = OAL_DLIST_GET_ENTRY(pst_list, frw_event_queue_stru, st_list);

        /* ����¼����е�vap_stateΪ��ͣ����������������ѡ��һ���¼����� */
        if (FRW_VAP_STATE_PAUSE == pst_event_queue->en_vap_state)
        {
            continue;
        }

        /* ����¼����е�Ȩ�ؼ�����Ϊ0������ѡ��һ���¼����� */
        if (pst_event_queue->uc_weight_cnt == 0)
        {
            continue;
        }

        /* �����¼�����Ȩ�ؼ����� */
        pst_event_queue->uc_weight_cnt--;

        /* ���µ��ȶ��е���Ȩ�ؼ����� */
        pst_sched_queue->ul_total_weight_cnt--;

        /* ���¼�������ȡ��һ���¼� */
        p_event = frw_event_queue_dequeue(pst_event_queue);

        /* ����¼����б�գ���Ҫ����ӵ��ȶ�����ɾ���������¼�����״̬��Ϊ����Ծ(���ɱ�����) */
      //  if (0 == pst_event_queue->st_queue.uc_element_cnt)
        {
            frw_event_sched_deactivate_queue_no_lock(pst_sched_queue, pst_event_queue);
        }

        break;
    }

    /* ������ȶ��е���Ȩ�ؼ�����Ϊ0������Ҫ���õ��ȶ����ϸ����¼����е�Ȩ�ؼ����� */
    if (0 == pst_sched_queue->ul_total_weight_cnt)
    {
        frw_event_sched_reset_weight(pst_sched_queue);
    }

    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);
    return p_event;
}

/*****************************************************************************
 �� �� ��  : frw_event_sched_init
 ��������  : ��������ʼ��
 �������  : pst_sched_queue: ���ȶ���ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��5��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_sched_init(frw_event_sched_queue_stru *pst_sched_queue)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_sched_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_event_sched_init:: pointer is NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ʼ���� */
    oal_spin_lock_init(&pst_sched_queue->st_lock);

    /* ��ʼ�����ȶ�����Ȩ�ؼ����� */
    pst_sched_queue->ul_total_weight_cnt = 0;

    /* ��ʼ����������ͷ */
    oal_dlist_init_head(&pst_sched_queue->st_head);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : frw_event_queue_set
 ��������  : �����¼����в���
 �������  : pst_prio_queue: �¼�����ָ��
             us_weight     : ����Ȩ��
             en_policy     : ���е��Ȳ���
             en_state      : �¼�����״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��23��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void frw_event_queue_set(
                frw_event_queue_stru               *pst_event_queue,
                oal_uint8                           uc_weight,
                frw_sched_policy_enum_uint8         en_policy,
                frw_event_queue_state_enum_uint8    en_state)
{
    pst_event_queue->uc_weight     = uc_weight;
    pst_event_queue->uc_weight_cnt = 0;
    pst_event_queue->en_policy     = en_policy;
    pst_event_queue->en_state      = en_state;
    pst_event_queue->en_vap_state  = FRW_VAP_STATE_RESUME;
}

/*****************************************************************************
 �� �� ��  : frw_event_queue_init
 ��������  : �¼����г�ʼ��
 �������  : pst_event_queue: �¼�����ָ��
             us_weight      : ����Ȩ��
             en_policy      : ���е��Ȳ���
             en_state       : �¼�����״̬
             us_max_events  : ����¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_queue_init(
                frw_event_queue_stru               *pst_event_queue,
                oal_uint8                           uc_weight,
                frw_sched_policy_enum_uint8         en_policy,
                frw_event_queue_state_enum_uint8    en_state,
                oal_uint8                           uc_max_events)

{
    oal_uint32 ul_ret;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_event_queue_init:: pointer is NULL!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ʼ���� */
    oal_spin_lock_init(&pst_event_queue->st_lock);

    ul_ret = oal_queue_init(&pst_event_queue->st_queue, uc_max_events);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_event_queue_init:: OAL_QUEUE_INIT return != OAL_SUCC! %d}", ul_ret);
        frw_event_queue_set(pst_event_queue, 0, FRW_SCHED_POLICY_BUTT, FRW_EVENT_QUEUE_STATE_INACTIVE);

        return ul_ret;
    }

    frw_event_queue_set(pst_event_queue, uc_weight, en_policy, en_state);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_queue_destroy
 ��������  : �����¼�����
 �������  : pst_event_queue: �¼�����ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  frw_event_queue_destroy(frw_event_queue_stru *pst_event_queue)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_event_queue_destroy:: pointer is NULL!}");
        return;
    }

    oal_queue_destroy(&pst_event_queue->st_queue);

    frw_event_queue_set(pst_event_queue, 0, FRW_SCHED_POLICY_BUTT, FRW_EVENT_QUEUE_STATE_INACTIVE);
}

/*****************************************************************************
 �� �� ��  : frw_event_sched_deactivate_queue
 ��������  : �ӵ��ȶ���ɾ��һ���¼�����
 �������  : pst_sched_queue: ���ȶ���ָ��
             pst_event_queue: �¼�����ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��12��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_sched_deactivate_queue(
                frw_event_sched_queue_stru         *pst_sched_queue,
                frw_event_queue_stru               *pst_event_queue)
{

    oal_uint      ul_flag = 0;
    oal_uint32      ul_ret = OAL_SUCC;

    /* ���жϣ����� */
    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

    ul_ret = frw_event_sched_deactivate_queue_no_lock(pst_sched_queue, pst_event_queue);

    /* ���������ж� */
    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : frw_event_sched_activate_queue
 ��������  : ����ȶ������һ���µ��¼�����
 �������  : past_sched_queue: ���ȶ���ָ��
             pst_event_queue : �¼�����ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��5��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��23��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : ��װ���ò�����ʵ�֣����ֽӿڶԳ���
*****************************************************************************/
oal_uint32  frw_event_sched_activate_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue)
{
    oal_uint      ul_flag = 0;
    oal_uint32      ul_ret = OAL_SUCC;

    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

    ul_ret = frw_event_sched_activate_queue_no_lock(pst_sched_queue, pst_event_queue);

    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);

    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : frw_event_sched_activate_queue
 ��������  : ��ͣ���е���״̬
 �������  : past_sched_queue: ���ȶ���ָ��
             pst_event_queue : �¼�����ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��23��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_void  frw_event_sched_pause_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue)
{
    oal_uint      ul_flag = 0;

    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

     /* ��VAP��Ӧ�������¼�����vap_state����Ϊ��ͣ */
    pst_event_queue->en_vap_state = FRW_VAP_STATE_PAUSE;

    /* ���µ��ȶ��е���Ȩ�ؼ����� */
    if (FRW_EVENT_QUEUE_STATE_ACTIVE == pst_event_queue->en_state)
    {
         pst_sched_queue->ul_total_weight_cnt -= pst_event_queue->uc_weight_cnt;
    }

    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);
}

/*****************************************************************************
 �� �� ��  : frw_event_sched_resume_queue
 ��������  : �ָ����е���״̬
 �������  : past_sched_queue: ���ȶ���ָ��
             pst_event_queue : �¼�����ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��23��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���
*****************************************************************************/
oal_void  frw_event_sched_resume_queue(
                frw_event_sched_queue_stru   *pst_sched_queue,
                frw_event_queue_stru         *pst_event_queue)
{
    oal_uint      ul_flag = 0;

    oal_spin_lock_irq_save(&pst_sched_queue->st_lock, &ul_flag);

     /* ��VAP��Ӧ�������¼�����vap_state����Ϊ�ָ� */
    pst_event_queue->en_vap_state = FRW_VAP_STATE_RESUME;

    /* ���µ��ȶ��е���Ȩ�ؼ����� */
    if (FRW_EVENT_QUEUE_STATE_ACTIVE == pst_event_queue->en_state)
    {
         pst_sched_queue->ul_total_weight_cnt += pst_event_queue->uc_weight_cnt;
    }

    oal_spin_unlock_irq_restore(&pst_sched_queue->st_lock, &ul_flag);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

