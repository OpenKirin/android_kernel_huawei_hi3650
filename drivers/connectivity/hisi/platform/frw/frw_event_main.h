/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : frw_event_main.h
  �� �� ��   : ����
  ��    ��   : mayuan m00212148
  ��������   : 2012��10��12��
  ����޸�   :
  ��������   : frw_event_main.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��12��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __FRW_EVENT_MAIN_H__
#define __FRW_EVENT_MAIN_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "oam_ext_if.h"
#include "frw_ext_if.h"
#include "frw_main.h"
#include "frw_event_sched.h"
#include "wlan_types.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_MAIN_H


/*****************************************************************************
  2 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
  ö����  : frw_event_deploy_enum_uint8
  Э����:
  ö��˵��: �¼���������
*****************************************************************************/
typedef enum
{
    FRW_EVENT_DEPLOY_NON_IPC  = 0,    /* �Ǻ˼�ͨ�� */
    FRW_EVENT_DEPLOY_IPC,             /* �˼�ͨѶ */

    FRW_EVENT_DEPLOY_BUTT
}frw_event_deploy_enum;
typedef oal_uint8 frw_event_deploy_enum_uint8;

/*****************************************************************************
  8 �궨��
*****************************************************************************/
/* �¼���������� */
/* һ�����͵��¼���Ӧ������������¼���Ĵ�СΪ�¼����͵�2�� */
#define FRW_EVENT_TABLE_MAX_ITEMS    (FRW_EVENT_TYPE_BUTT * 2)

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
typedef struct _frw_event_segment_stru_
{
    frw_event_type_enum_uint8        en_type;         /* �¼����� */
    oal_uint8                        uc_sub_type;     /* �¼������� */
    frw_event_pipeline_enum_uint8    en_pipeline;     /* �¼��ֶκ� */
    oal_uint8                        uc_vap_id;       /* VAP ID */
}frw_event_segment_stru;

typedef struct _frw_event_trace_item_stru_
{
    frw_event_segment_stru st_event_seg;
    oal_uint64  timestamp;
}frw_event_trace_item_stru;

#define CONFIG_FRW_MAX_TRACE_EVENT_NUMS (50)
typedef struct _frw_event_trace_stru_
{
    frw_event_trace_item_stru st_trace_item[CONFIG_FRW_MAX_TRACE_EVENT_NUMS];
    oal_uint32  ul_current_pos;
    oal_uint32  ul_over_flag;
    const char*       pst_func_name;
    oal_int32   line_num;
    //oal_void*   pst_last_ip;/*last pc address*/
}frw_event_trace_stru;
#endif
/*****************************************************************************
  �ṹ��  : frw_event_mgmt_stru
  �ṹ˵��: �¼�����ṹ��
*****************************************************************************/
typedef struct _frw_event_mgmt_stru_
{
    frw_event_queue_stru          st_event_queue[FRW_EVENT_MAX_NUM_QUEUES];    /* �¼����� */
    frw_event_sched_queue_stru    st_sched_queue[FRW_SCHED_POLICY_BUTT];         /* �ɵ��ȶ��� */
#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
    frw_event_trace_stru          *pst_frw_trace;
#endif
}frw_event_mgmt_stru;
extern frw_event_table_item_stru g_ast_event_table[FRW_EVENT_TABLE_MAX_ITEMS];

extern frw_event_mgmt_stru g_ast_event_manager[WLAN_FRW_MAX_NUM_CORES];

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_uint32  frw_event_init(oal_void);
extern oal_uint32  frw_event_exit(oal_void);
extern oal_uint32  frw_event_queue_enqueue(frw_event_queue_stru *pst_event_queue, frw_event_mem_stru *pst_event_mem);
extern frw_event_mem_stru *frw_event_queue_dequeue(frw_event_queue_stru *pst_event_queue);
extern oal_uint32  frw_event_post_event(frw_event_mem_stru *pst_event_mem, oal_uint32 ul_core_id);
extern oal_void  frw_event_deploy_register(oal_uint32 (*p_func)(frw_event_mem_stru *pst_event_mem, oal_uint8 *puc_deploy_result));
extern oal_void  frw_event_ipc_event_queue_full_register(oal_uint32 (*p_func)(oal_void));
extern oal_void  frw_event_ipc_event_queue_empty_register(oal_uint32 (*p_func)(oal_void));
extern frw_event_sched_queue_stru* frw_event_get_sched_queue(oal_uint32 ul_core_id, frw_sched_policy_enum_uint8 en_policy);
extern oal_void  frw_event_vap_pause_event(oal_uint8 uc_vap_id);
extern oal_void  frw_event_vap_resume_event(oal_uint8 uc_vap_id);
extern oal_uint32  frw_event_vap_flush_event(oal_uint8 uc_vap_id, frw_event_type_enum_uint8 en_event_type, oal_bool_enum_uint8 en_drop);
extern oal_uint32  frw_event_lookup_process_entry(frw_event_mem_stru *pst_event_mem, frw_event_hdr_stru *pst_event_hrd);
extern oal_uint32  frw_event_queue_info(oal_void);


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : frw_event_to_queue_id
 ��������  : �����¼����ݻ�ȡ��Ӧ���¼�����ID
 �������  : pst_event_mem: ָ���¼��ڴ���ָ��
 �������  : pus_qid      : ����ID
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��5��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  frw_event_to_qid(frw_event_mem_stru *pst_event_mem, oal_uint16 *pus_qid)
{
    oal_uint16            us_qid;
    frw_event_hdr_stru   *pst_event_hrd;

    /* ��ȡ�¼�ͷ�ṹ */
    pst_event_hrd = (frw_event_hdr_stru *)pst_event_mem->puc_data;

    us_qid        = pst_event_hrd->uc_vap_id * FRW_EVENT_TYPE_BUTT + pst_event_hrd->en_type;

  /*
    us_qid = (pst_event_hrd->uc_chip_id * (WLAN_DEVICE_MAX_NUM_PER_CHIP * WLAN_VAP_MAX_NUM_PER_DEVICE) +
              pst_event_hrd->uc_device_id * (WLAN_VAP_MAX_NUM_PER_DEVICE) + pst_event_hrd->uc_vap_id) *
              FRW_EVENT_TYPE_BUTT + pst_event_hrd->en_type;
  */

    /* �쳣: ����ID�������ֵ */
    if ((us_qid >= FRW_EVENT_MAX_NUM_QUEUES))
    {
        OAM_ERROR_LOG4(0, OAM_SF_FRW, "{frw_event_to_qid, array overflow! us_qid[%d], vap_id[%d], en_type[%d], sub_type[%d]}",
                                        us_qid, pst_event_hrd->uc_vap_id, pst_event_hrd->en_type, pst_event_hrd->uc_sub_type);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    *pus_qid = us_qid;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_report
 ��������  : ��WiTP�ڴ����֮����¼��ϱ�SDT
 �������  : pst_event_mem: ָ���¼��ڴ���ָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��3��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void  frw_event_report(frw_event_mem_stru *pst_event_mem)
{
    frw_event_stru      *pst_event;
    oal_uint8            auc_event[OAM_EVENT_INFO_MAX_LEN] = {0};
    pst_event = (frw_event_stru *)pst_event_mem->puc_data;


    /* �����¼�ͷ */
    oal_memcopy((oal_void *)auc_event, (const oal_void *)&pst_event->st_event_hdr, OAL_SIZEOF(frw_event_hdr_stru));

    FRW_EVENT_INTERNAL(BROADCAST_MACADDR, 0, OAM_EVENT_INTERNAL, auc_event);
}

/*****************************************************************************
 �� �� ��  : frw_event_process
 ��������  : �����¼��ֶκţ������¼�
 �������  : pst_event_mem: ָ���¼��ڴ���ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  frw_event_process(frw_event_mem_stru *pst_event_mem)
{
    frw_event_hdr_stru   *pst_event_hrd;
    oal_uint32            ul_core_id;

    /* ��ȡ�¼�ͷ�ṹ */
    pst_event_hrd  = (frw_event_hdr_stru *)pst_event_mem->puc_data;

    if (OAL_UNLIKELY(pst_event_hrd->en_pipeline >= FRW_EVENT_PIPELINE_STAGE_BUTT))
    {
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /* ���piplelineΪ0�����¼���ӡ�����
       �����¼����ͣ��������Լ��ֶκţ�ִ����Ӧ���¼������� */
    if (FRW_EVENT_PIPELINE_STAGE_0 == pst_event_hrd->en_pipeline)
    {
        ul_core_id = OAL_GET_CORE_ID();
        return frw_event_post_event(pst_event_mem, ul_core_id);
    }

    return frw_event_lookup_process_entry(pst_event_mem, pst_event_hrd);
}

#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
OAL_STATIC OAL_INLINE oal_void frw_event_last_pc_trace(const char* pst_func_name,oal_int32 line_num, oal_uint32 ul_core_id)
{
    OAL_BUG_ON(ul_core_id > WLAN_FRW_MAX_NUM_CORES);
    g_ast_event_manager[ul_core_id].pst_frw_trace->pst_func_name = pst_func_name;
    g_ast_event_manager[ul_core_id].pst_frw_trace->line_num = line_num;
}

OAL_STATIC OAL_INLINE oal_void frw_event_trace(frw_event_mem_stru *pst_event_mem, oal_uint32 ul_core_id)
{
    oal_uint32 ul_pos;
    frw_event_trace_item_stru *pst_trace_item;
    frw_event_hdr_stru        *pst_event_hdr;

    pst_event_hdr           = frw_get_event_hdr(pst_event_mem);
    ul_pos = g_ast_event_manager[ul_core_id].pst_frw_trace->ul_current_pos;

    OAL_BUG_ON(ul_pos > CONFIG_FRW_MAX_TRACE_EVENT_NUMS);
    OAL_BUG_ON(ul_core_id > WLAN_FRW_MAX_NUM_CORES);

    pst_trace_item = &(g_ast_event_manager[ul_core_id].pst_frw_trace->st_trace_item[ul_pos]);
    pst_trace_item->timestamp = local_clock();
    pst_trace_item->st_event_seg.en_type = pst_event_hdr->en_type;
    pst_trace_item->st_event_seg.uc_sub_type = pst_event_hdr->uc_sub_type;
    pst_trace_item->st_event_seg.uc_vap_id = pst_event_hdr->uc_vap_id;
    pst_trace_item->st_event_seg.en_pipeline = pst_event_hdr->en_pipeline;

    if((++ul_pos) >= CONFIG_FRW_MAX_TRACE_EVENT_NUMS)
    {
        g_ast_event_manager[ul_core_id].pst_frw_trace->ul_current_pos = 0;
        g_ast_event_manager[ul_core_id].pst_frw_trace->ul_over_flag = 1;
    }
    else
    {
        g_ast_event_manager[ul_core_id].pst_frw_trace->ul_current_pos++;
    }
}
#endif

#ifdef _PRE_OAL_FEATURE_TASK_NEST_LOCK
extern oal_task_lock_stru  g_frw_event_task_lock;
#define frw_event_task_lock()   do{oal_smp_task_lock(&g_frw_event_task_lock);}while(0)
#define frw_event_task_unlock()   do{oal_smp_task_unlock(&g_frw_event_task_lock);}while(0)
#else
#define frw_event_task_lock()   do{}while(0)
#define frw_event_task_unlock()   do{}while(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_event_main.h */
