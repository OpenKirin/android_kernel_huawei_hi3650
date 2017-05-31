/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : frw_event_main.c
  �� �� ��   : ����
  ��    ��   : mayuan m00212148
  ��������   : 2012��10��12��
  ����޸�   :
  ��������   : �¼��������ӿ�(��IPC�ӿڡ���ҵ��ӿ�)ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��12��
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
#include "frw_task.h"
#include "frw_main.h"
#include "frw_event_sched.h"
#include "frw_event_main.h"
#include "hal_ext_if.h"
#include "oal_kernel_file.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_MAIN_C



/*****************************************************************************
  2 STRUCT����
*****************************************************************************/
/*****************************************************************************
  �ṹ��  : frw_event_cfg_stru
  �ṹ˵��: �¼�����������Ϣ�ṹ��
*****************************************************************************/
typedef struct
{
    oal_uint8                      uc_weight;        /* ����Ȩ�� */
    oal_uint8                      uc_max_events;    /* �����������ɵ�����¼����� */
    frw_sched_policy_enum_uint8    en_policy;        /* �����������Ȳ���(�����ȼ�����ͨ���ȼ�) */
    oal_uint8                      auc_resv;
}frw_event_cfg_stru;



/*****************************************************************************
  �ṹ��  : frw_event_ipc_register_stru
  �ṹ˵��: IPCģ��ע��ṹ��
*****************************************************************************/
typedef struct
{
    oal_uint32 (*p_frw_event_deploy_pipeline_func)(frw_event_mem_stru *pst_event_mem, oal_uint8 *puc_deploy_result);
    oal_uint32 (*p_frw_ipc_event_queue_full_func)(oal_void);
    oal_uint32 (*p_frw_ipc_event_queue_empty_func)(oal_void);
}frw_event_ipc_register_stru;



/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
/******************************************************************************
    �¼�����������Ϣȫ�ֱ���
*******************************************************************************/
OAL_STATIC frw_event_cfg_stru g_ast_event_queue_cfg_table[] = WLAN_FRW_EVENT_CFG_TABLE;

/******************************************************************************
    �¼�����ʵ��
*******************************************************************************/
frw_event_mgmt_stru g_ast_event_manager[WLAN_FRW_MAX_NUM_CORES];

/******************************************************************************
    �¼���ȫ�ֱ���
*******************************************************************************/
frw_event_table_item_stru g_ast_event_table[FRW_EVENT_TABLE_MAX_ITEMS];

/******************************************************************************
    IPCע�����ʵ��
*******************************************************************************/
OAL_STATIC frw_event_ipc_register_stru g_st_ipc_register;

#ifdef _PRE_DEBUG_MODE
frw_event_track_time_stru g_ast_event_time_track[FRW_RX_EVENT_TRACK_NUM];
oal_uint32                g_ul_rx_event_idx = 0;
oal_bool_enum_uint8       g_en_event_track_switch = OAL_TRUE;
oal_uint32                g_ul_schedule_idx = 0;
oal_uint32                g_aul_schedule_time[FRW_RX_EVENT_TRACK_NUM] = {0};
#endif

#ifdef _PRE_OAL_FEATURE_TASK_NEST_LOCK
/*smp os use the task lock to protect the event process*/
oal_task_lock_stru  g_frw_event_task_lock;
oal_module_symbol(g_frw_event_task_lock);
#endif

#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
#ifdef _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
OAL_STATIC oal_int32 frw_trace_print_event_item(frw_event_trace_item_stru* pst_event_trace, char* buf, oal_int32 buf_len)
{
    oal_int32 ret = 0;
    oal_ulong rem_nsec;
    oal_uint64  timestamp = pst_event_trace->timestamp;

    rem_nsec = do_div(timestamp, 1000000000);
    ret +=  snprintf(buf + ret , buf_len - ret, "%u,%u,%u,%u,%5lu.%06lu\n",
                        pst_event_trace->st_event_seg.uc_vap_id,
                        pst_event_trace->st_event_seg.en_pipeline,
                        pst_event_trace->st_event_seg.en_type,
                        pst_event_trace->st_event_seg.uc_sub_type,
                        (oal_ulong)timestamp,
                        rem_nsec/1000);
    return ret;
}
#endif

#if defined(_PRE_FRW_TIMER_BIND_CPU) && defined(CONFIG_NR_CPUS)
extern oal_uint32 g_ul_frw_timer_cpu_count[];
#endif

OAL_STATIC oal_int32 frw_print_panic_stat(oal_void* data, char* buf, oal_int32 buf_len)
{
    oal_int32 ret = 0;
    oal_uint32    ul_core_id;
    oal_uint32 i;

    OAL_REFERENCE(data);
#ifdef _PRE_OAL_FEATURE_TASK_NEST_LOCK
    if(g_frw_event_task_lock.claimer)
        ret +=  snprintf(buf + ret , buf_len - ret, "frw task lock claimer:%s\n",g_frw_event_task_lock.claimer->comm);
#endif
#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        ret +=  snprintf(buf + ret , buf_len - ret, "last pc:%s,line:%d\n",
                                    g_ast_event_manager[ul_core_id].pst_frw_trace->pst_func_name,
                                    g_ast_event_manager[ul_core_id].pst_frw_trace->line_num);
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
        ret +=  snprintf(buf + ret, buf_len - ret, "task thread total cnt:%u,event cnt:%u,empty max count:%u\n",
                                        g_ast_event_task[ul_core_id].ul_total_loop_cnt,
                                        g_ast_event_task[ul_core_id].ul_total_event_cnt,
                                        g_ast_event_task[ul_core_id].ul_max_empty_count);
#endif

        ret +=  snprintf(buf + ret , buf_len - ret, "frw event trace buff:\n");

#if defined(_PRE_FRW_TIMER_BIND_CPU) && defined(CONFIG_NR_CPUS)
        do{
            oal_uint32 cpu_id;
            for(cpu_id = 0; cpu_id < CONFIG_NR_CPUS; cpu_id++)
            {
                if(g_ul_frw_timer_cpu_count[cpu_id])
                {
                    ret +=  snprintf(buf + ret , buf_len - ret, "[cpu:%u]count:%u\n",cpu_id, g_ul_frw_timer_cpu_count[cpu_id]);
                }
            }
        }while(0);
#endif

        if(1 == g_ast_event_manager[ul_core_id].pst_frw_trace->ul_over_flag)
        {
            /*overturn*/
            for(i = g_ast_event_manager[ul_core_id].pst_frw_trace->ul_current_pos; i < CONFIG_FRW_MAX_TRACE_EVENT_NUMS;i++)
            {
                ret += frw_trace_print_event_item(&g_ast_event_manager[ul_core_id].pst_frw_trace->st_trace_item[i],buf + ret, buf_len - ret);
            }
        }

        i = 0;
        for(i = 0; i < g_ast_event_manager[ul_core_id].pst_frw_trace->ul_current_pos; i++)
        {
            ret += frw_trace_print_event_item(&g_ast_event_manager[ul_core_id].pst_frw_trace->st_trace_item[i], buf + ret,buf_len - ret);
        }

    }
#else
    OAL_REFERENCE(i);
    OAL_REFERENCE(ul_core_id);
    OAL_REFERENCE(ret);
#endif
    return ret;
}
OAL_STATIC DECLARE_WIFI_PANIC_STRU(frw_panic_stat,frw_print_panic_stat);
#endif

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : frw_event_init_event_queue
 ��������  : ��ʼ���¼�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_event_init_event_queue(oal_void)
{
    oal_uint32    ul_core_id;
    oal_uint16    us_qid;
    oal_uint32    ul_ret;

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        /* ѭ����ʼ���¼����� */
        for (us_qid = 0; us_qid < FRW_EVENT_MAX_NUM_QUEUES; us_qid++)
        {
            ul_ret = frw_event_queue_init(&g_ast_event_manager[ul_core_id].st_event_queue[us_qid],
                              g_ast_event_queue_cfg_table[us_qid].uc_weight,
                              g_ast_event_queue_cfg_table[us_qid].en_policy,
                              FRW_EVENT_QUEUE_STATE_INACTIVE,
                              g_ast_event_queue_cfg_table[us_qid].uc_max_events);

            if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
            {
                OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_event_init_event_queue, frw_event_queue_init return != OAL_SUCC!%d}", ul_ret);
                return ul_ret;
            }
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_lookup_process_entry
 ��������  : �����¼����ͣ��������Լ��ֶκţ��ҵ���Ӧ�¼�������
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
OAL_STATIC OAL_INLINE oal_uint32  _frw_event_lookup_process_entry_(frw_event_mem_stru *pst_event_mem, frw_event_hdr_stru *pst_event_hrd)
{
    oal_uint8                    uc_index;
    oal_uint8                    uc_sub_type;
    frw_event_table_item_stru   *pst_frw_event_table;
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    frw_event_mem_stru          *pst_tmp_event_mem;
    oal_uint32                   ul_ret = 0;
#if (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    oal_bool_enum                b_is_rx_adapt = OAL_FALSE;
#endif
#endif

    uc_sub_type = pst_event_hrd->uc_sub_type;

#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE))

    /*UT�����´�׮ʵ�ֲ���*/
    if (FRW_EVENT_PIPELINE_STAGE_2 == pst_event_hrd->en_pipeline)
    {
        pst_event_hrd->en_pipeline = FRW_EVENT_PIPELINE_STAGE_1;
        b_is_rx_adapt = OAL_TRUE;
    }
#endif

    /* �����¼����ͼ��ֶκż����¼������� */
    uc_index = (oal_uint8)((pst_event_hrd->en_type << 1) | (pst_event_hrd->en_pipeline & 0x01));
    if (OAL_UNLIKELY(uc_index >= FRW_EVENT_TABLE_MAX_ITEMS))
    {
        OAM_ERROR_LOG3(0, OAM_SF_FRW, "{frw_event_lookup_process_entry::array overflow! type[0x%x], sub_type[0x%x], pipeline[0x%x]}",
                       pst_event_hrd->en_type, uc_sub_type, pst_event_hrd->en_pipeline);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) && (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE))
    if (OAL_TRUE == b_is_rx_adapt)
    {
        pst_event_hrd->en_pipeline = FRW_EVENT_PIPELINE_STAGE_2;
    }
#endif

    /* �Ȱ�ȫ�ֱ�����ɾֲ����� */
    pst_frw_event_table = &g_ast_event_table[uc_index];

    if (OAL_PTR_NULL == pst_frw_event_table->pst_sub_table)
    {
        OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_event_lookup_process_entry::pst_sub_table is NULL! sub_type[0x%x], index[0x%x].}",
                       uc_sub_type, uc_index);

        /* ��ӡ��ǰ�¼��ڴ�Ĳ������� */
        oal_print_hex_dump(pst_event_mem->puc_data, (oal_int32)(FRW_EVENT_HDR_LEN + 20), 32, "current event mem info:");

        /* ��ӡ��ǰ�¼��ڴ��ǰ64�ֽ����� */
        oal_print_hex_dump(pst_event_mem->puc_data + 64, 64, 32, "64bytes mem info in front of this mem:");

        return OAL_ERR_CODE_PTR_NULL;
    }

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC != _PRE_MULTI_CORE_MODE)
    if (OAL_PTR_NULL == pst_frw_event_table->pst_sub_table[uc_sub_type].p_func)
    {
        OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_event_lookup_process_entry::pst_sub_table.p_func is NULL! sub_type[0x%x], index[0x%x].}",
                       uc_sub_type, uc_index);
        return OAL_ERR_CODE_PTR_NULL;
    }
    #if (_PRE_TEST_MODE_UT == _PRE_TEST_MODE)
    pst_frw_event_table->pst_sub_table[uc_sub_type].p_func(pst_event_mem);
    return OAL_SUCC;
    #else
    /* pipeline=1�����¼�������Ҫ���ӷ���ֵ��ͬʱfrw_event_dispatch_event����ʱҲҪ���ӷ���ֵ�жϣ�����ȷ���� */
    return pst_frw_event_table->pst_sub_table[uc_sub_type].p_func(pst_event_mem);
    #endif
#else /* 1102 */
    /*For pipeline 0 type*/
    if (0 == pst_event_hrd->en_pipeline)
    {
        if (OAL_PTR_NULL != pst_frw_event_table->pst_sub_table[uc_sub_type].p_func)
        {
            pst_frw_event_table->pst_sub_table[uc_sub_type].p_func(pst_event_mem);
            return OAL_SUCC;
        }
        else
        {
            OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_event_lookup_process_entry::pst_sub_table.p_func is NULL! sub_type[0x%x], index[0x%x], pipeline=0.}",
                           uc_sub_type, uc_index);
            return OAL_ERR_CODE_PTR_NULL;
        }
    }

    /*For pipeline 1 type*/
#if (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT))
    //��51�����ϴ�׮ʵ��tx adapt��rx adapt�Ĳ��ԣ������ô���ɾ��
    if ((OAL_PTR_NULL == pst_frw_event_table->pst_sub_table[uc_sub_type].p_tx_adapt_func)
            && (OAL_PTR_NULL == pst_frw_event_table->pst_sub_table[uc_sub_type].p_rx_adapt_func))
    {
        if (OAL_PTR_NULL == pst_frw_event_table->pst_sub_table[uc_sub_type].p_func)
        {
            OAM_ERROR_LOG4(0, OAM_SF_FRW, "{frw_event_lookup_process_entry::sub type pointer is NULL! sub_type[%d], index[%d].en_type[%d],en_pipeline[%d]}",
                           uc_sub_type, uc_index, pst_event_hrd->en_type, pst_event_hrd->en_pipeline);
            return OAL_ERR_CODE_PTR_NULL;
        }

        pst_frw_event_table->pst_sub_table[uc_sub_type].p_func(pst_event_mem);

        return OAL_SUCC;

    }

    if (1 == pst_event_hrd->en_pipeline)
    {
        if (OAL_SUCC != pst_frw_event_table->pst_sub_table[uc_sub_type].p_tx_adapt_func(pst_event_mem))
        {
            return OAL_ERR_CODE_ALLOC_MEM_FAIL;
        }
    }
    else if (2 == pst_event_hrd->en_pipeline)
    {
        /*rx adapt first*/
        pst_tmp_event_mem = pst_frw_event_table->pst_sub_table[uc_sub_type].p_rx_adapt_func(pst_event_mem);
        if ((OAL_PTR_NULL != pst_tmp_event_mem) && (OAL_PTR_NULL != pst_frw_event_table->pst_sub_table[uc_sub_type].p_func))
        {
            /*then call action frame*/
            pst_frw_event_table->pst_sub_table[uc_sub_type].p_func(pst_tmp_event_mem);
            FRW_EVENT_FREE(pst_tmp_event_mem);
        }
        else
        {
            OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_event_lookup_process_entry::rx adapt prcocess failed! sub_type[0x%x], index[0x%x].}",
                          uc_sub_type, uc_index);
            if(OAL_PTR_NULL != pst_tmp_event_mem)
            {
                FRW_EVENT_FREE(pst_tmp_event_mem);
            }
            return OAL_ERR_CODE_PTR_NULL;
        }
    }

#else // (((_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)) && (_PRE_TEST_MODE == _PRE_TEST_MODE_UT))
    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_frw_event_table->pst_sub_table[uc_sub_type].p_tx_adapt_func)
            && (OAL_PTR_NULL == pst_frw_event_table->pst_sub_table[uc_sub_type].p_rx_adapt_func)))
    {
        OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_event_lookup_process_entry::tx and rx adapt pointer all NULL! sub_type[0x%x], index[0x%x].}",
                       uc_sub_type, uc_index);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /*For tx adapt*/
    if (OAL_PTR_NULL != pst_frw_event_table->pst_sub_table[uc_sub_type].p_tx_adapt_func)
    {
        ul_ret = pst_frw_event_table->pst_sub_table[uc_sub_type].p_tx_adapt_func(pst_event_mem);
        if (OAL_SUCC != ul_ret)
        {
            OAM_ERROR_LOG3(0, OAM_SF_FRW, "{_frw_event_lookup_process_entry_::tx adapt process failed!sub_type[0x%x],index[0x%x],ret[%d].}",
                           uc_sub_type, uc_index, ul_ret);
            return ul_ret;
        }

        return OAL_SUCC;
    }

    /*For rx adapt*/
    if (OAL_PTR_NULL != pst_frw_event_table->pst_sub_table[uc_sub_type].p_rx_adapt_func)
    {
        /*rx adapt first*/
        pst_tmp_event_mem = pst_frw_event_table->pst_sub_table[uc_sub_type].p_rx_adapt_func(pst_event_mem);
        if ((OAL_PTR_NULL != pst_tmp_event_mem) && (OAL_PTR_NULL != pst_frw_event_table->pst_sub_table[uc_sub_type].p_func))
        {
            /*then call action frame*/
            pst_frw_event_table->pst_sub_table[uc_sub_type].p_func(pst_tmp_event_mem);
            FRW_EVENT_FREE(pst_tmp_event_mem);
        }
        else
        {
            OAM_ERROR_LOG4(0, OAM_SF_FRW, "{frw_event_lookup_process_entry::rx adapt process failed! sub_type[0x%x], index[0x%x].[%d][%d]}",
                           uc_sub_type, uc_index,pst_tmp_event_mem,pst_frw_event_table->pst_sub_table[uc_sub_type].p_func);

            if(OAL_PTR_NULL != pst_tmp_event_mem)
            {
                FRW_EVENT_FREE(pst_tmp_event_mem);
            }
            return OAL_ERR_CODE_PTR_NULL;
        }
    }

#endif
    return OAL_SUCC;
#endif
}

oal_uint32  frw_event_lookup_process_entry(frw_event_mem_stru *pst_event_mem, frw_event_hdr_stru *pst_event_hrd)
{
    oal_uint32 ul_ret;
    ul_ret = _frw_event_lookup_process_entry_(pst_event_mem,pst_event_hrd);
    return ul_ret;
}


/*****************************************************************************
 �� �� ��  : frw_event_destroy_event_queue
 ��������  : �����¼�����
 �������  : ul_core_id: �˺�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  frw_event_destroy_event_queue(oal_uint32 ul_core_id)
{
    oal_uint16    us_qid;

    /* ѭ�������¼����� */
    for (us_qid = 0; us_qid < FRW_EVENT_MAX_NUM_QUEUES; us_qid++)
    {
        frw_event_queue_destroy(&g_ast_event_manager[ul_core_id].st_event_queue[us_qid]);
    }
}

/*****************************************************************************
 �� �� ��  : frw_event_init_sched
 ��������  : ��ʼ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_event_init_sched(oal_void)
{
    oal_uint32    ul_core_id;
    oal_uint16    us_qid;
    oal_uint32    ul_ret;

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        /* ѭ����ʼ�������� */
        for (us_qid = 0; us_qid < FRW_SCHED_POLICY_BUTT; us_qid++)
        {
            ul_ret = frw_event_sched_init(&g_ast_event_manager[ul_core_id].st_sched_queue[us_qid]);

            if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
            {
                OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_event_init_sched, frw_event_sched_init return != OAL_SUCC!%d}", ul_ret);
                return ul_ret;
            }
        }
    }

    return OAL_SUCC;
}

#ifdef _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
/*****************************************************************************
 �� �� ��  : frw_event_trace_init
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32 frw_event_trace_init(oal_void)
{
    oal_uint32    ul_core_id;
    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {

        g_ast_event_manager[ul_core_id].pst_frw_trace = (frw_event_trace_stru*)vmalloc(OAL_SIZEOF(frw_event_trace_stru));
        if(NULL == g_ast_event_manager[ul_core_id].pst_frw_trace)
        {
            OAL_IO_PRINT("frw_event_init_sched coreid:%u, alloc frw event trace %u bytes failed! \n",
                          ul_core_id,
                          (oal_uint32)OAL_SIZEOF(frw_event_trace_stru));
            return OAL_ERR_CODE_PTR_NULL;
        }
        oal_memset((oal_void*)g_ast_event_manager[ul_core_id].pst_frw_trace,0,OAL_SIZEOF(frw_event_trace_stru));
    }
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_trace_exit
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   :
    ��    ��   :
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void frw_event_trace_exit(oal_void)
{
    oal_uint32    ul_core_id;
    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        if(NULL != g_ast_event_manager[ul_core_id].pst_frw_trace)
        {
            vfree(g_ast_event_manager[ul_core_id].pst_frw_trace);
            g_ast_event_manager[ul_core_id].pst_frw_trace = NULL;
        }
    }
}
#endif

/*****************************************************************************
 �� �� ��  : frw_event_dispatch_event
 ��������  : �¼��ַ��ӿ�(�ַ��¼����˼�ͨѶ���¼����С����߲��Ѱ����Ӧ�¼�������)
 �������  : pst_event_mem: ָ���¼��ڴ���ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��12��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_dispatch_event(frw_event_mem_stru *pst_event_mem)
{
#if (_PRE_MULTI_CORE_MODE_PIPELINE_AMP == _PRE_MULTI_CORE_MODE)
    frw_event_deploy_enum_uint8    en_deploy;
    oal_uint32                     ul_ret;
#endif
#if defined(_PRE_MEM_DEBUG_MODE) || defined(_PRE_DEBUG_MODE)
    oal_uint32                     ul_dog_tag;
#endif

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_event_mem))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_event_dispatch_event: pst_event_mem is null ptr!}");
        return OAL_ERR_CODE_PTR_NULL;
    }


    /* �쳣: �ڴ�дԽ�� */
#if defined(_PRE_MEM_DEBUG_MODE) || defined(_PRE_DEBUG_MODE)
    ul_dog_tag = (*((oal_uint32 *)(pst_event_mem->puc_origin_data + pst_event_mem->us_len - OAL_DOG_TAG_SIZE)));
    if (OAL_DOG_TAG != ul_dog_tag)
    {
        OAL_IO_PRINT("[line = %d], frw_event_dispatch_event, ul_dog_tag changed is [%d]\r\n", __LINE__, ul_dog_tag);

        return OAL_ERR_CODE_OAL_MEM_DOG_TAG;
    }
#endif

#ifdef _PRE_DEBUG_MODE
    frw_event_report(pst_event_mem);
#endif

#if (_PRE_MULTI_CORE_MODE_PIPELINE_AMP == _PRE_MULTI_CORE_MODE)
    /* ���û�п����˼�ͨ�ţ�������¼��ֶκŴ����¼�(��ӻ���ִ����Ӧ�Ĵ�����) */
    if (OAL_PTR_NULL == st_ipc_register.p_frw_event_deploy_pipeline_func)
    {
        return frw_event_process(pst_event_mem);
    }

    ul_ret = st_ipc_register.p_frw_event_deploy_pipeline_func(pst_event_mem, &en_deploy);
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_event_dispatch_event, p_frw_event_deploy_pipeline_func return != OAL_SUCC!%d}", ul_ret);
        return ul_ret;
    }

    /* ���Ϊ�˼�ͨ�ţ���ֱ�ӷ��سɹ������򣬸����¼��ֶκŴ����¼� */
    if (FRW_EVENT_DEPLOY_IPC == en_deploy)
    {
        return OAL_SUCC;
    }
#endif

    return frw_event_process(pst_event_mem);
}

#if defined(_PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT) && defined(_PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT)
OAL_STATIC ssize_t  frw_get_event_trace(struct device *dev, struct device_attribute *attr, char* buf)
{
    int ret = 0;

    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);
    ret += frw_print_panic_stat(NULL,buf,PAGE_SIZE - ret);
    return ret;
}
OAL_STATIC DEVICE_ATTR(event_trace, S_IRUGO, frw_get_event_trace, NULL);


OAL_STATIC struct attribute *frw_sysfs_entries[] = {
        &dev_attr_event_trace.attr,
        NULL
};

OAL_STATIC struct attribute_group frw_attribute_group = {
        .name = "frw",
        .attrs = frw_sysfs_entries,
};

OAL_STATIC oal_int32 frw_sysfs_entry_init(oal_void)
{
    oal_int32       ret = OAL_SUCC;
    oal_kobject*     pst_root_object = NULL;
    pst_root_object = oal_get_sysfs_root_object();
    if(NULL == pst_root_object)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{frw_sysfs_entry_init::get sysfs root object failed!}");
        return -OAL_EFAIL;
    }


    ret = sysfs_create_group(pst_root_object, &frw_attribute_group);
    if (ret)
    {
        OAM_ERROR_LOG0(0,OAM_SF_ANY,"{frw_sysfs_entry_init::sysfs create group failed!}");
        return ret;
    }
    return OAL_SUCC;
}

OAL_STATIC oal_int32 frw_sysfs_entry_exit(oal_void)
{
    oal_kobject*     pst_root_object = NULL;
    pst_root_object = oal_get_sysfs_root_object();
    if(NULL != pst_root_object)
    {
        sysfs_remove_group(pst_root_object, &frw_attribute_group);
    }

    return OAL_SUCC;
}
#endif

/*****************************************************************************
 �� �� ��  : frw_event_init
 ��������  : �¼�����ģ���ʼ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��12��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 frw_event_init(oal_void)
{
    oal_uint32    ul_ret;

    OAL_MEMZERO(&g_st_ipc_register, OAL_SIZEOF(g_st_ipc_register));
#ifdef _PRE_DEBUG_MODE

    OAL_MEMZERO(&g_ast_event_time_track, FRW_RX_EVENT_TRACK_NUM * OAL_SIZEOF(frw_event_track_time_stru));
#endif

#ifdef _PRE_OAL_FEATURE_TASK_NEST_LOCK
    oal_smp_task_lock_init(&g_frw_event_task_lock);
#endif

    /* ��ʼ���¼����� */
    ul_ret = frw_event_init_event_queue();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_event_init, frw_event_init_event_queue != OAL_SUCC!%d}", ul_ret);
        return ul_ret;
    }

    /* ��ʼ�������� */
    ul_ret = frw_event_init_sched();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "frw_event_init, frw_event_init_sched != OAL_SUCC!%d", ul_ret);
        return ul_ret;
    }

#ifdef _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
    ul_ret = frw_event_trace_init();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "frw_event_init, frw_event_trace_init != OAL_SUCC!%d", ul_ret);
        return ul_ret;
    }
#endif

#ifdef _PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT
    hwifi_panic_log_register(&frw_panic_stat,NULL);
#endif

    frw_task_event_handler_register(frw_event_process_all_event);

#if defined(_PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT) && defined(_PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT)
    frw_sysfs_entry_init();
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_exit
 ��������  : �¼�����ģ��ж�ؽӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��12��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_exit(oal_void)
{
    oal_uint32    ul_core_id;
#if defined(_PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT) && defined(_PRE_CONFIG_HISI_PANIC_DUMP_SUPPORT)
    frw_sysfs_entry_exit();
#endif

#ifdef _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
    frw_event_trace_exit();
#endif

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        /* �����¼����� */
        frw_event_destroy_event_queue(ul_core_id);
    }

    return OAL_SUCC;
}

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_void frw_event_sub_rx_adapt_table_init(frw_event_sub_table_item_stru *pst_sub_table, oal_uint32 ul_table_nums,
                                                frw_event_mem_stru *(*p_rx_adapt_func)(frw_event_mem_stru *))
{
    oal_uint32 i;
    frw_event_sub_table_item_stru* pst_curr_table;
    for(i = 0; i < ul_table_nums; i++)
    {
        pst_curr_table = pst_sub_table +i;
        pst_curr_table->p_rx_adapt_func = p_rx_adapt_func;
    }
}
#endif

/*****************************************************************************
 �� �� ��  : frw_event_queue_enqueue
 ��������  : ���¼��ڴ������Ӧ���¼�����
 �������  : pst_event_mem: ָ���¼��ڴ���ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��23��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_queue_enqueue(frw_event_queue_stru *pst_event_queue, frw_event_mem_stru *pst_event_mem)
{
    oal_uint32                  ul_ret;
    oal_uint                     ul_irq_flag;

    oal_spin_lock_irq_save(&pst_event_queue->st_lock, &ul_irq_flag);
    ul_ret = oal_queue_enqueue(&pst_event_queue->st_queue, (void *)pst_event_mem);
    oal_spin_unlock_irq_restore(&pst_event_queue->st_lock, &ul_irq_flag);
    return ul_ret;
}

/*****************************************************************************
 �� �� ��  : frw_event_queue_dequeue
 ��������  : �¼��ڴ����
 �������  : pst_event_queue: �¼�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��23��
    ��    ��   : wangjianchang wWX278082
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_mem_stru *frw_event_queue_dequeue(frw_event_queue_stru *pst_event_queue)
{
    frw_event_mem_stru *pst_event_mem;
    oal_uint                    ul_irq_flag;

    oal_spin_lock_irq_save(&pst_event_queue->st_lock, &ul_irq_flag);
    pst_event_mem = (frw_event_mem_stru *)oal_queue_dequeue(&pst_event_queue->st_queue);
    oal_spin_unlock_irq_restore(&pst_event_queue->st_lock, &ul_irq_flag);
    return pst_event_mem;
}

/*****************************************************************************
 �� �� ��  : frw_event_post_event
 ��������  : ���¼��ڴ������Ӧ���¼�����
 �������  : pst_event_mem: ָ���¼��ڴ���ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��5��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_post_event(frw_event_mem_stru *pst_event_mem,oal_uint32 ul_core_id)
{
    oal_uint16                   us_qid;
    frw_event_mgmt_stru         *pst_event_mgmt;
    frw_event_queue_stru        *pst_event_queue;
    oal_uint32                   ul_ret;
    frw_event_hdr_stru          *pst_event_hdr;
    frw_event_sched_queue_stru  *pst_sched_queue;


    /* ��ȡ�¼�����ID */
    ul_ret = frw_event_to_qid(pst_event_mem, &us_qid);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_event_post_event, frw_event_to_qid return != OAL_SUCC!%d}", ul_ret);
        return ul_ret;
    }

    if (OAL_UNLIKELY(ul_core_id >= WLAN_FRW_MAX_NUM_CORES))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "{frw_event_post_event, array overflow!%d}", ul_core_id);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /* ���ݺ˺� + ����ID���ҵ���Ӧ���¼����� */
    pst_event_mgmt  = &g_ast_event_manager[ul_core_id];

    pst_event_queue = &pst_event_mgmt->st_event_queue[us_qid];

    /* ���policy */
    if (OAL_UNLIKELY(pst_event_queue->en_policy >= FRW_SCHED_POLICY_BUTT))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "{frw_event_post_event, array overflow!%d}", pst_event_queue->en_policy);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    /* ��ȡ���ȶ��� */
    pst_sched_queue = &pst_event_mgmt->st_sched_queue[pst_event_queue->en_policy];


    /* �¼��ڴ����ü�����1 */
#ifdef _PRE_DEBUG_MODE
    /* �쳣: ���ڴ���ϵĹ����û�����Ϊ���ֵ */
    if (OAL_UNLIKELY((oal_uint16)(pst_event_mem->uc_user_cnt + 1) > WLAN_MEM_MAX_USERS_NUM))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{pst_event_mem->uc_user_cnt is too large.%d}", pst_event_mem->uc_user_cnt);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }
#endif
    /* ��ȡ�����ã���ֹenqueue��ȡ������֮�䱻�ͷ� */
    pst_event_mem->uc_user_cnt++;

    /* �¼���� */
    ul_ret = frw_event_queue_enqueue(pst_event_queue, pst_event_mem);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        pst_event_hdr = (frw_event_hdr_stru *)(pst_event_mem->puc_data);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
        OAM_WARNING_LOG4(0, OAM_SF_FRW, "frw_event_post_event:: enqueue fail. core %d, type %d, sub type %d, pipeline %d ",
                                      ul_core_id,
                                      pst_event_hdr->en_type,
                                      pst_event_hdr->uc_sub_type,
                                      pst_event_hdr->en_pipeline);

        OAM_WARNING_LOG4(0, OAM_SF_FRW, "event info: type: %d, sub type: %d, pipeline: %d,max num:%d",
                        pst_event_hdr->en_type,
                        pst_event_hdr->uc_sub_type,
                        pst_event_hdr->en_pipeline,
                        pst_event_queue->st_queue.uc_max_elements);
#else
        OAM_ERROR_LOG4(0, OAM_SF_FRW, "frw_event_post_event:: enqueue fail. core %d, type %d, sub type %d, pipeline %d ",
                                      ul_core_id,
                                      pst_event_hdr->en_type,
                                      pst_event_hdr->uc_sub_type,
                                      pst_event_hdr->en_pipeline);

        OAM_ERROR_LOG4(0, OAM_SF_FRW, "event info: type: %d, sub type: %d, pipeline: %d,max num:%d",
                        pst_event_hdr->en_type,
                        pst_event_hdr->uc_sub_type,
                        pst_event_hdr->en_pipeline,
                        pst_event_queue->st_queue.uc_max_elements);
#endif
        /* �ͷ��¼��ڴ����� */
        FRW_EVENT_FREE(pst_event_mem);

        return ul_ret;
    }

    /*�˴����ܷ��أ����Ȳ��Զ���Ҫ�������������.*/

    /* �����������Ȳ��ԣ����¼����м���ɵ��ȶ��� */
    ul_ret = frw_event_sched_activate_queue(pst_sched_queue, pst_event_queue);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "{frw_event_post_event, frw_event_sched_activate_queue return != OAL_SUCC! %d}", ul_ret);
        return ul_ret;
    }

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    #ifdef _PRE_DEBUG_MODE
        #if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_TASKLET)
        if (OAL_TRUE == g_en_event_track_switch)
        {
            if (!oal_task_is_scheduled(&g_ast_event_task[ul_core_id].st_event_tasklet))
            {
                g_aul_schedule_time[g_ul_schedule_idx] = oal_5115timer_get_10ns();
            }
        }
        #endif
    #endif
#endif

    frw_task_sched(ul_core_id);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_table_register
 ��������  : ע����Ӧ�¼���Ӧ���¼�������
 �������  : en_type:       �¼�����
             en_pipeline:   �¼��ֶκ�
             pst_sub_table: �¼��ӱ�ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��12��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  frw_event_table_register(
                frw_event_type_enum_uint8      en_type,
                frw_event_pipeline_enum        en_pipeline,
                frw_event_sub_table_item_stru *pst_sub_table)
{
    oal_uint8    uc_index;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_sub_table))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_event_table_register: pst_sub_table is null ptr!}");
        return;
    }

    /* �����¼����ͼ��ֶκż����¼������� */
    uc_index = (oal_uint8)((en_type << 1) | (en_pipeline & 0x01));

    if (OAL_UNLIKELY(uc_index >= FRW_EVENT_TABLE_MAX_ITEMS))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "{frw_event_table_register, array overflow! %d}", uc_index);
        return;
    }

    g_ast_event_table[uc_index].pst_sub_table = pst_sub_table;
}

/*****************************************************************************
 �� �� ��  : frw_event_deploy_register
 ��������  : ��event deployģ��ע���¼�����ӿ�
 �������  : p_func: �¼�����ӿ�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  frw_event_deploy_register(oal_uint32 (*p_func)(frw_event_mem_stru *pst_event_mem, frw_event_deploy_enum_uint8 *pen_deploy_result))
{
    g_st_ipc_register.p_frw_event_deploy_pipeline_func = p_func;
}

/*****************************************************************************
 �� �� ��  : frw_event_ipc_event_queue_full_register
 ��������  : ��IPCģ��ע��˼��ж�Ƶ�ȹ���ӿ�
 �������  : p_func: �˼��ж�Ƶ�ȹ���ӿ�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  frw_event_ipc_event_queue_full_register(oal_uint32 (*p_func)(oal_void))
{
    g_st_ipc_register.p_frw_ipc_event_queue_full_func = p_func;
}

/*****************************************************************************
 �� �� ��  : frw_event_ipc_event_queue_empty_register
 ��������  : ��IPCģ��ע��˼��ж�Ƶ�ȹ���ӿ�
 �������  : p_func: �˼��ж�Ƶ�ȹ���ӿ�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��13��
    ��    ��   : mayuan m00212148
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  frw_event_ipc_event_queue_empty_register(oal_uint32 (*p_func)(oal_void))
{
    g_st_ipc_register.p_frw_ipc_event_queue_empty_func = p_func;
}


/*****************************************************************************
 �� �� ��  : frw_event_process_all_event
 ��������  : �����¼������е������¼�
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
oal_void  frw_event_process_all_event(oal_uint ui_data)
{
    oal_uint32                     ul_core_id;
    frw_event_mem_stru            *pst_event_mem;
    frw_event_sched_queue_stru    *pst_sched_queue;
    frw_event_hdr_stru            *pst_event_hrd;
#if 0
    oal_uint32                     ul_debug = 0;
#endif

#ifdef _PRE_DEBUG_MODE
    oal_uint32                     ul_timestamp_start;
    oal_uint32                     ul_timestamp_end;
    oal_uint32                     ul_event_index;

    if (OAL_TRUE == g_en_event_track_switch)
    {
        ul_timestamp_end = oal_5115timer_get_10ns();
        g_aul_schedule_time[g_ul_schedule_idx] = g_aul_schedule_time[g_ul_schedule_idx] - ul_timestamp_end;
        OAL_INCR(g_ul_schedule_idx, FRW_RX_EVENT_TRACK_NUM);
    }

#endif

    /* ��ȡ�˺� */
    ul_core_id = OAL_GET_CORE_ID();


    if (OAL_UNLIKELY(ul_core_id >= WLAN_FRW_MAX_NUM_CORES))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "{frw_event_process_all_event, array overflow! %d}", ul_core_id);
        return;
    }

    pst_sched_queue = g_ast_event_manager[ul_core_id].st_sched_queue;

    /* �����¼�����ģ�飬ѡ��һ���¼� */
    pst_event_mem = (frw_event_mem_stru *)frw_event_schedule(pst_sched_queue);

#ifdef _PRE_DEBUG_MODE

    if (OAL_TRUE == g_en_event_track_switch)
    {
        OAL_INCR(g_ul_rx_event_idx, FRW_RX_EVENT_TRACK_NUM);
        g_ast_event_time_track[g_ul_rx_event_idx].ul_event_cnt = 0;
    }

#endif

    while (OAL_PTR_NULL != pst_event_mem)
    {

        /* ��ȡ�¼�ͷ�ṹ */
        pst_event_hrd  = (frw_event_hdr_stru *)pst_event_mem->puc_data;
#ifdef _PRE_DEBUG_MODE
        ul_timestamp_start = oal_5115timer_get_10ns();
#endif

        #if 0
            if(pst_event_mem->ul_alloc_file_id[0]!=OAM_FILE_ID_FRW_TIMER_C&&
               pst_event_mem->ul_alloc_line_num[0]!=1473)//tbtt
            {
                ul_debug = 1;
                if(ul_debug)
                    OAL_IO_PRINT("CPU %d process event: user_cnt: %u, pool_id: %u, subpool_id: %u, len: %u, "
                                 "alloc_core_id = %u, alloc_file_id: %u, alloc_line_num: %u, alloc_time_stamp: %u, "
                                 "trace_file_id: %u, trace_line_num: %u, trace_time_stamp: %u.\n",
                                 ul_core_id,
                                 pst_event_mem->uc_user_cnt,
                                 pst_event_mem->en_pool_id,
                                 pst_event_mem->uc_subpool_id,
                                 pst_event_mem->us_len,
                                 pst_event_mem->ul_alloc_core_id[0],
                                 pst_event_mem->ul_alloc_file_id[0],
                                 pst_event_mem->ul_alloc_line_num[0],
                                 pst_event_mem->ul_alloc_time_stamp[0],
                                 pst_event_mem->ul_trace_file_id,
                                 pst_event_mem->ul_trace_line_num,
                                 pst_event_mem->ul_trace_time_stamp);
             }
             else
             {
                ul_debug = 0;
             }
        #endif

#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
        /*trace the event serial*/
        frw_event_trace(pst_event_mem, ul_core_id);
#endif
        /* �����¼��ҵ���Ӧ���¼������� */
        frw_event_task_lock();
        frw_event_lookup_process_entry(pst_event_mem, pst_event_hrd);
        frw_event_task_unlock();

#ifdef _PRE_DEBUG_MODE
        if (OAL_TRUE == g_en_event_track_switch)
        {
            ul_timestamp_end = oal_5115timer_get_10ns();
            ul_event_index = g_ast_event_time_track[g_ul_rx_event_idx].ul_event_cnt;
            if (FRW_EVENT_TRACK_NUM > ul_event_index)
            {
                g_ast_event_time_track[g_ul_rx_event_idx].aul_event_time[ul_event_index]    = ul_timestamp_start - ul_timestamp_end;
                g_ast_event_time_track[g_ul_rx_event_idx].us_event_type[ul_event_index]     = pst_event_hrd->en_type;
                g_ast_event_time_track[g_ul_rx_event_idx].us_event_sub_type[ul_event_index] = pst_event_hrd->uc_sub_type;
            }
            g_ast_event_time_track[g_ul_rx_event_idx].ul_event_cnt++;

        }

#endif
        /* �ͷ��¼��ڴ� */
        FRW_EVENT_FREE(pst_event_mem);
#if (_PRE_FRW_FEATURE_PROCCESS_ENTITY_TYPE == _PRE_FRW_FEATURE_PROCCESS_ENTITY_THREAD)
        if(OAL_LIKELY(ul_core_id < WLAN_FRW_MAX_NUM_CORES))
        {
            g_ast_event_task[ul_core_id].ul_total_event_cnt++;
        }
#endif

#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
        frw_event_last_pc_trace(__FUNCTION__,__LINE__, ul_core_id);
#endif

        /* �����¼�����ģ�飬ѡ��һ���¼� */
        pst_event_mem = (frw_event_mem_stru *)frw_event_schedule(pst_sched_queue);
    }

#ifdef  _PRE_FRW_EVENT_PROCESS_TRACE_DEBUG
        frw_event_last_pc_trace(__FUNCTION__,__LINE__, ul_core_id);
#endif
}

/*****************************************************************************
 �� �� ��  : frw_event_flush_event_queue
 ��������  : ���ĳ���¼������е������¼�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��21��
    ��    ��   : zourong 52447
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_flush_event_queue(frw_event_type_enum_uint8 uc_event_type)
{
    oal_uint32              ul_core_id;
    oal_uint16              us_qid;
    oal_uint8               uc_vap_id;
    frw_event_mgmt_stru    *pst_event_mgmt;
    frw_event_queue_stru   *pst_event_queue;
    frw_event_mem_stru     *pst_event_mem;
    frw_event_hdr_stru     *pst_event_hrd;
    oal_uint32              ul_event_succ = 0;;

    /* ����ÿ���˵�ÿ��vap��Ӧ���¼����� */
    for(ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        for(uc_vap_id = 0; uc_vap_id < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vap_id++)
        {
            us_qid = uc_vap_id * FRW_EVENT_TYPE_BUTT + uc_event_type;

            /* ���ݺ˺� + ����ID���ҵ���Ӧ���¼����� */
            pst_event_mgmt  = &g_ast_event_manager[ul_core_id];
            pst_event_queue = &pst_event_mgmt->st_event_queue[us_qid];

            /*flush���е�event*/
            while( 0 != pst_event_queue->st_queue.uc_element_cnt)
            {
                pst_event_mem = (frw_event_mem_stru *)frw_event_queue_dequeue(pst_event_queue);
                if (OAL_PTR_NULL == pst_event_mem)
                {
                    continue;
                }

                /* ��ȡ�¼�ͷ�ṹ */
                pst_event_hrd = (frw_event_hdr_stru *)pst_event_mem->puc_data;

                /* �����¼��ҵ���Ӧ���¼������� */
                frw_event_lookup_process_entry(pst_event_mem, pst_event_hrd);

                /* �ͷ��¼��ڴ� */
                FRW_EVENT_FREE(pst_event_mem);

                ul_event_succ++;
            }
#if 1
            /* ����¼����б�գ���Ҫ����ӵ��ȶ�����ɾ���������¼�����״̬��Ϊ����Ծ(���ɱ�����) */
            if (0 == pst_event_queue->st_queue.uc_element_cnt)
            {
                frw_event_sched_deactivate_queue(&g_ast_event_manager[ul_core_id].st_sched_queue[pst_event_queue->en_policy], pst_event_queue);
            }
#endif
        }
    }

    return ul_event_succ;
}

/*****************************************************************************
 �� �� ��  : frw_dump_event
 ��������  : ��ӡ�¼�
 �������  : puc_event: �¼��ṹ���׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��5��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  frw_event_dump_event(oal_uint8 *puc_event)
{
    frw_event_stru       *pst_event = (frw_event_stru *)puc_event;
    frw_event_hdr_stru   *pst_event_hdr   = &pst_event->st_event_hdr;
    oal_uint8            *puc_payload     = pst_event->auc_event_data;
    oal_uint32            ul_event_length = pst_event_hdr->us_length - FRW_EVENT_HDR_LEN;
    oal_uint32            ul_loop;

    OAL_IO_PRINT("==================event==================\n");
    OAL_IO_PRINT("type     : [%02X]\n", pst_event_hdr->en_type);
    OAL_IO_PRINT("sub type : [%02X]\n", pst_event_hdr->uc_sub_type);
    OAL_IO_PRINT("length   : [%X]\n", pst_event_hdr->us_length);
    OAL_IO_PRINT("pipeline : [%02X]\n", pst_event_hdr->en_pipeline);
    OAL_IO_PRINT("chip id  : [%02X]\n", pst_event_hdr->uc_chip_id);
    OAL_IO_PRINT("device id: [%02X]\n", pst_event_hdr->uc_device_id);
    OAL_IO_PRINT("vap id   : [%02X]\n", pst_event_hdr->uc_vap_id);

    OAL_IO_PRINT("payload: \n");

    for (ul_loop = 0; ul_loop < ul_event_length; ul_loop += 4)
    {
        OAL_IO_PRINT("%02X %02X %02X %02X\n", puc_payload[ul_loop], puc_payload[ul_loop+1],
                      puc_payload[ul_loop+2], puc_payload[ul_loop+3]);
    }
}

/*****************************************************************************
 �� �� ��  : frw_get_event_info_from_event_queue
 ��������  : ���¼������л�ȡÿһ���¼����¼�ͷ��Ϣ
 �������  : pst_event_queue: �¼�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  frw_event_get_info_from_event_queue(frw_event_queue_stru *pst_event_queue)
{
    frw_event_stru              *pst_event;
    oal_queue_stru              *pst_queue;
    frw_event_mem_stru          *pst_event_mem;
    oal_uint8                    uc_loop;
    oam_event_queue_info_stru    st_event_queue_info;

    pst_queue = &pst_event_queue->st_queue;

    OAL_MEMZERO(&st_event_queue_info, OAL_SIZEOF(oam_event_queue_info_stru));
    st_event_queue_info.uc_event_num_in_queue = pst_queue->uc_element_cnt;

    for (uc_loop = 0; uc_loop < pst_queue->uc_element_cnt; uc_loop++)
    {

        pst_event_mem = (frw_event_mem_stru *)pst_queue->pul_buf[uc_loop];
        pst_event     = (frw_event_stru *)pst_event_mem->puc_data;

        #ifdef _PRE_DEBUG_MODE
            OAL_IO_PRINT("frw event info:vap %d user_cnt: %u, pool_id: %u, subpool_id: %u, len: %u, "
                         "alloc_core_id = %u, alloc_file_id: %u, alloc_line_num: %u, alloc_time_stamp: %u, "
                         "trace_file_id: %u, trace_line_num: %u, trace_time_stamp: %u.\n",
                         pst_event->st_event_hdr.uc_vap_id,
                         pst_event_mem->uc_user_cnt,
                         pst_event_mem->en_pool_id,
                         pst_event_mem->uc_subpool_id,
                         pst_event_mem->us_len,
                         pst_event_mem->ul_alloc_core_id[0],
                         pst_event_mem->ul_alloc_file_id[0],
                         pst_event_mem->ul_alloc_line_num[0],
                         pst_event_mem->ul_alloc_time_stamp[0],
                         pst_event_mem->ul_trace_file_id,
                         pst_event_mem->ul_trace_line_num,
                         pst_event_mem->ul_trace_time_stamp);
       #else
           OAL_IO_PRINT("frw event info:vap %d,type = %d,subtype=%d,pipe=%d, user_cnt: %u, pool_id: %u, subpool_id: %u, len: %u.\n",
                        pst_event->st_event_hdr.uc_vap_id,
                        pst_event->st_event_hdr.en_type,
                        pst_event->st_event_hdr.uc_sub_type,
                        pst_event->st_event_hdr.en_pipeline,
                        pst_event_mem->uc_user_cnt,
                        pst_event_mem->en_pool_id,
                        pst_event_mem->uc_subpool_id,
                        pst_event_mem->us_len);
       #endif

    #if  0
        /* ��ȡ�¼�ͷ��Ϣ����д��Ҫ�ϱ���SDT�Ľṹ���� */
        st_event_queue_info.ast_event_hdr_info[uc_loop].en_pipeline  = pst_event->st_event_hdr.en_pipeline;
        st_event_queue_info.ast_event_hdr_info[uc_loop].uc_sub_type  = pst_event->st_event_hdr.uc_sub_type;
        st_event_queue_info.ast_event_hdr_info[uc_loop].us_length    = pst_event->st_event_hdr.us_length;
        st_event_queue_info.ast_event_hdr_info[uc_loop].uc_chip_id   = pst_event->st_event_hdr.uc_chip_id;
        st_event_queue_info.ast_event_hdr_info[uc_loop].uc_device_id = pst_event->st_event_hdr.uc_device_id;
        st_event_queue_info.ast_event_hdr_info[uc_loop].uc_vap_id    = pst_event->st_event_hdr.uc_vap_id;
        st_event_queue_info.ast_event_hdr_info[uc_loop].en_type      = pst_event->st_event_hdr.en_type;
    #endif
    }

   // oam_stats_report_event_queue_info_to_sdt((oal_uint8 *)&st_event_queue_info,
    //                                          (oal_uint16)OAL_SIZEOF(oam_event_queue_info_stru));

}


/*****************************************************************************
 �� �� ��  : frw_event_queue_info
 ��������  : ���¼������е��¼������Լ�ÿ���¼����¼�ͷ��Ϣ�ϱ�.
             �ӵ��ȶ����ҵ�ÿһ�������¼����¼����У�Ȼ���ȡ�¼��������õ�ÿһ��
             �¼����¼�ͷ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : z00237171
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_queue_info(oal_void)
{
    oal_uint32                      ul_core_id;
    oal_uint16                      us_qid;
    frw_event_sched_queue_stru     *pst_sched_queue;
    frw_event_queue_stru           *pst_event_queue;
    frw_event_mgmt_stru            *pst_event_mgmt;
    oal_dlist_head_stru            *pst_dlist;

    /* ��ȡ�˺� */
    ul_core_id = OAL_GET_CORE_ID();
    OAL_IO_PRINT("frw_event_queue_info get core id is %d.\n", ul_core_id);

    for (ul_core_id = 0; ul_core_id < WLAN_FRW_MAX_NUM_CORES; ul_core_id++)
    {
        OAL_IO_PRINT("-------------frw_event_queue_info core id is %d--------------.\n", ul_core_id);
        for (us_qid = 0; us_qid < FRW_EVENT_MAX_NUM_QUEUES; us_qid++)
        {
            pst_event_queue = &g_ast_event_manager[ul_core_id].st_event_queue[us_qid];
            if(0!=pst_event_queue->st_queue.uc_element_cnt)
            {
                OAL_IO_PRINT("qid %d,state %d, event num %d,weigt_cnt %d,head idx %d,tail idx %d,prev=0x%p,next=0x%p\n",
                              us_qid,pst_event_queue->en_state,pst_event_queue->st_queue.uc_element_cnt,
                              pst_event_queue->uc_weight,pst_event_queue->st_queue.uc_head_index,pst_event_queue->st_queue.uc_tail_index,
                              pst_event_queue->st_list.pst_prev,pst_event_queue->st_list.pst_next);
                frw_event_get_info_from_event_queue(pst_event_queue);
            }

        }
         /* ���ݺ˺ţ��ҵ���Ӧ���¼�����ṹ�� */
        pst_event_mgmt  = &g_ast_event_manager[ul_core_id];

    /* ������ȡ���ȶ��� */
    for (us_qid = 0; us_qid < FRW_SCHED_POLICY_BUTT; us_qid++)
    {
        /* ��ȡ�¼�����ṹ���еĵ��ȶ��� */
        pst_sched_queue = &pst_event_mgmt->st_sched_queue[us_qid];

        /* ��ȡ���ȶ�����ÿ���¼����е�ÿ���¼�����Ϣ */
        if (!oal_dlist_is_empty(&pst_sched_queue->st_head))
        {
            /* ��ȡ���ȶ����е�ÿһ���¼����� */
            OAL_DLIST_SEARCH_FOR_EACH(pst_dlist, &pst_sched_queue->st_head)
            {
                pst_event_queue = OAL_DLIST_GET_ENTRY(pst_dlist, frw_event_queue_stru, st_list);

                    /* ��ȡ������ÿһ���¼����¼�ͷ��Ϣ */
                    frw_event_get_info_from_event_queue(pst_event_queue);
                }
            }
            else
            {
                OAL_IO_PRINT("Schedule queue %d empty\n",us_qid);
            }
        }
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_vap_pause_event
 ��������  : �����ض�VAP�������¼����е�VAP״̬Ϊ��ͣ��ֹͣ���ȣ�����������
 �������  : uc_vap_id: VAP IDֵ
 �������  : ��
 �� �� ֵ  : OAL_SUCC����OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��23��
    ��    ��   : daihu 00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void frw_event_vap_pause_event(oal_uint8 uc_vap_id)
{
    oal_uint32                    ul_core_id;
    oal_uint16                    us_qid;
    frw_event_mgmt_stru          *pst_event_mgmt;
    frw_event_queue_stru         *pst_event_queue;
    frw_event_sched_queue_stru   *pst_sched_queue;

    ul_core_id = OAL_GET_CORE_ID();
    if (OAL_UNLIKELY(ul_core_id >= WLAN_FRW_MAX_NUM_CORES))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "{frw_event_process_all_event, array overflow!%d}", ul_core_id);
        return;
    }

    /* ���ݺ˺ţ��ҵ���Ӧ���¼����� */
    pst_event_mgmt = &g_ast_event_manager[ul_core_id];

    /* ���ݶ���ID���ҵ���Ӧ��VAP�ĵ�һ���¼����� */
    pst_event_queue = &pst_event_mgmt->st_event_queue[uc_vap_id * FRW_EVENT_TYPE_BUTT];

    /* ����¼������Ѿ���pause�Ļ���ֱ�ӷ��أ���Ȼѭ���е��ȶ�����Ȩ�ػ��ظ���ȥ�¼����е�Ȩ�� */
    if(FRW_VAP_STATE_PAUSE == pst_event_queue->en_vap_state)
    {
        return;
    }

    for (us_qid = 0; us_qid < FRW_EVENT_TYPE_BUTT; us_qid++)
    {
        /* ���ݶ���ID���ҵ���Ӧ���¼����� */
        pst_event_queue = &pst_event_mgmt->st_event_queue[uc_vap_id * FRW_EVENT_TYPE_BUTT + us_qid];
        pst_sched_queue = &g_ast_event_manager[ul_core_id].st_sched_queue[pst_event_queue->en_policy];

        frw_event_sched_pause_queue(pst_sched_queue, pst_event_queue);
    }
}


/*****************************************************************************
 �� �� ��  : frw_event_vap_resume_event
 ��������  : �����ض�VAP�������¼����е�VAP״̬Ϊ�ָ����ɵ���
 �������  : uc_vap_id: VAP IDֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��23��
    ��    ��   : daihu 00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void frw_event_vap_resume_event(oal_uint8 uc_vap_id)
{
    oal_uint32                    ul_core_id;
    oal_uint16                    us_qid;
    frw_event_mgmt_stru          *pst_event_mgmt;
    frw_event_queue_stru         *pst_event_queue;
    frw_event_sched_queue_stru   *pst_sched_queue;

    ul_core_id = OAL_GET_CORE_ID();
    if (OAL_UNLIKELY(ul_core_id >= WLAN_FRW_MAX_NUM_CORES))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "{frw_event_process_all_event, array overflow!%d}", ul_core_id);
        return;
    }

    /* ���ݺ˺ţ��ҵ���Ӧ���¼����� */
    pst_event_mgmt = &g_ast_event_manager[ul_core_id];

    /* ���ݶ���ID���ҵ���Ӧ��VAP�ĵ�һ���¼����� */
    pst_event_queue = &pst_event_mgmt->st_event_queue[uc_vap_id * FRW_EVENT_TYPE_BUTT];

    /* ����¼������Ѿ���resume�Ļ���ֱ�ӷ��أ���Ȼѭ���е��ȶ�����Ȩ�ػ��ظ���ȥ�¼����е�Ȩ�� */
    if(FRW_VAP_STATE_RESUME == pst_event_queue->en_vap_state)
    {
        return;
    }

    for (us_qid = 0; us_qid < FRW_EVENT_TYPE_BUTT; us_qid++)
    {
        /* ���ݶ���ID���ҵ���Ӧ���¼����� */
        pst_event_queue = &pst_event_mgmt->st_event_queue[uc_vap_id * FRW_EVENT_TYPE_BUTT + us_qid];
        pst_sched_queue = &g_ast_event_manager[ul_core_id].st_sched_queue[pst_event_queue->en_policy];

        frw_event_sched_resume_queue(pst_sched_queue, pst_event_queue);
    }

    /* �����߳� */
    frw_task_sched(ul_core_id);

}


/*****************************************************************************
 �� �� ��  : frw_event_vap_flush_event
 ��������  : ��ˢָ��VAP��ָ���¼����͵������¼���ͬʱ����ָ���Ƕ�����Щ�¼�����ȫ������
 �������  : uc_vap_id:     VAP IDֵ
             en_event_type: �¼�����
             en_drop:       �¼�����(1)���ߴ���(0)
 �������  : ��
 �� �� ֵ  : OAL_SUCC��OAL_FAIL������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��23��
    ��    ��   : daihu 00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_vap_flush_event(oal_uint8           uc_vap_id,
                                      frw_event_type_enum_uint8 en_event_type,
                                      oal_bool_enum_uint8       en_drop)
{
    oal_uint32              ul_core_id;
    oal_uint16              us_qid;
    frw_event_mgmt_stru    *pst_event_mgmt;
    frw_event_queue_stru   *pst_event_queue;
    frw_event_mem_stru     *pst_event_mem;
    frw_event_hdr_stru     *pst_event_hrd;

    /* ��ȡ�˺� */
    ul_core_id = OAL_GET_CORE_ID();
    if(OAL_UNLIKELY(ul_core_id >= WLAN_FRW_MAX_NUM_CORES))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "{frw_event_vap_flush_event, array overflow!%d}", ul_core_id);
        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    if (en_event_type == FRW_EVENT_TYPE_WLAN_TX_COMP)
    {
        uc_vap_id = 0;
    }

    us_qid = uc_vap_id * FRW_EVENT_TYPE_BUTT + en_event_type;

    /* ���ݺ˺� + ����ID���ҵ���Ӧ���¼����� */
    pst_event_mgmt  = &g_ast_event_manager[ul_core_id];
    pst_event_queue = &pst_event_mgmt->st_event_queue[us_qid];

    /* ����¼����б���Ϊ�գ�û���¼������ڵ��ȶ��У����ش��� */
    if (0 == pst_event_queue->st_queue.uc_element_cnt)
    {
        return OAL_FAIL;
    }

    /* flush���е�event */
    while(0 != pst_event_queue->st_queue.uc_element_cnt)
    {
        pst_event_mem = (frw_event_mem_stru *)frw_event_queue_dequeue(pst_event_queue);
        if (OAL_PTR_NULL == pst_event_mem)
        {
            return OAL_ERR_CODE_PTR_NULL;
        }


        /* �����¼�������ֱ���ͷ��¼��ڴ�������¼� */
        if(0 == en_drop)
        {
            /* ��ȡ�¼�ͷ�ṹ */
            pst_event_hrd = (frw_event_hdr_stru *)pst_event_mem->puc_data;

            /* �����¼��ҵ���Ӧ���¼������� */
            frw_event_lookup_process_entry(pst_event_mem, pst_event_hrd);
        }

        /* �ͷ��¼��ڴ� */
        FRW_EVENT_FREE(pst_event_mem);
    }

    /* ���¼������Ѿ���գ���Ҫ����ӵ��ȶ�����ɾ���������¼�����״̬��Ϊ����Ծ(���ɱ�����) */
    if(0 == pst_event_queue->st_queue.uc_element_cnt)
    {
        frw_event_sched_deactivate_queue(&g_ast_event_manager[ul_core_id].st_sched_queue[pst_event_queue->en_policy], pst_event_queue);
    }
    else
    {
        OAM_ERROR_LOG1(uc_vap_id, OAM_SF_FRW, "{flush vap event failed, left!=0: type=%d}", en_event_type);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_get_sched_queue
 ��������  : ����VAP��ͣ���ָ��ͳ�ˢ��������IT���ԣ���ȡfrw_event_main.c�ж����ȫ���¼��ĵ��ȶ���
 �������  : ul_core_id: �˺�
             en_policy:  ���Ȳ���
 �������  : ��
 �� �� ֵ  : ���ȶ���ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��28��
    ��    ��   : daihu 00262548
    �޸�����   : �����ɺ���

*****************************************************************************/
frw_event_sched_queue_stru* frw_event_get_sched_queue(oal_uint32 ul_core_id, frw_sched_policy_enum_uint8 en_policy)
{
    if (OAL_UNLIKELY((ul_core_id >= WLAN_FRW_MAX_NUM_CORES) || (en_policy >= FRW_SCHED_POLICY_BUTT)))
    {
        return OAL_PTR_NULL;
    }

    return &(g_ast_event_manager[ul_core_id].st_sched_queue[en_policy]);
}

/*****************************************************************************
 �� �� ��  : frw_is_event_queue_empty
 ��������  : �ж�����VAP��Ӧ���¼������Ƿ�Ϊ��
 �������  : uc_event_type: �¼�����
 �������  : ��
 �� �� ֵ  : OAL_TRUE:  ��
             OAL_FALSE: ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��19��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8  frw_is_event_queue_empty(frw_event_type_enum_uint8 uc_event_type)
{
    oal_uint32              ul_core_id;
    oal_uint8               uc_vap_id;
    oal_uint16              us_qid;
    frw_event_mgmt_stru    *pst_event_mgmt;
    frw_event_queue_stru   *pst_event_queue;

    /* ��ȡ�˺� */
    ul_core_id = OAL_GET_CORE_ID();
    if(OAL_UNLIKELY(ul_core_id >= WLAN_FRW_MAX_NUM_CORES))
    {
        OAM_ERROR_LOG1(0, OAM_SF_FRW, "{frw_event_post_event, core id = %d overflow!}", ul_core_id);

        return OAL_ERR_CODE_ARRAY_OVERFLOW;
    }

    pst_event_mgmt = &g_ast_event_manager[ul_core_id];

    /* �����ú���ÿ��VAP��Ӧ���¼����У� */
    for (uc_vap_id = 0; uc_vap_id < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; uc_vap_id++)
    {
        us_qid = uc_vap_id * FRW_EVENT_TYPE_BUTT + uc_event_type;

        /* ���ݺ˺� + ����ID���ҵ���Ӧ���¼����� */
        pst_event_queue = &pst_event_mgmt->st_event_queue[us_qid];

        if (0 != pst_event_queue->st_queue.uc_element_cnt)
        {
            return OAL_FALSE;
        }
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : frw_is_vap_event_queue_empty
 ��������  : ���ݺ�id���¼����ͣ��ж�vap�¼������Ƿ��
 �������  : ul_core_id: ��id; event_type:  �¼�ID;
 �������  :
 �� �� ֵ  : OAL_TRUE ������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��25��
    ��    ��   : lingxuemeng 00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_bool_enum_uint8  frw_is_vap_event_queue_empty(oal_uint32 ul_core_id, oal_uint8 uc_vap_id, oal_uint8 event_type)
{
    frw_event_mgmt_stru         *pst_event_mgmt;
    frw_event_queue_stru        *pst_event_queue;
    oal_uint16                   us_qid = 0;

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)||(_PRE_OS_VERSION_WIN32_RAW == _PRE_OS_VERSION)
    us_qid  = (oal_uint16)event_type;
#else
    us_qid  = (oal_uint16)(uc_vap_id * FRW_EVENT_TYPE_BUTT + event_type);
#endif

    /* ���ݺ˺� + ����ID���ҵ���Ӧ���¼����� */
    pst_event_mgmt = &g_ast_event_manager[ul_core_id];

    pst_event_queue = &pst_event_mgmt->st_event_queue[us_qid];

    if(0 != pst_event_queue->st_queue.uc_element_cnt)
    {
        return OAL_FALSE;
    }

    return OAL_TRUE;
}

/*****************************************************************************
 �� �� ��  : frw_sched_queue_is_empty
 ��������  : �ж��Ƿ����¼���Ҫ����
 �������  : ��id
 �������  : ��
 �� �� ֵ  : OAL_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : lingxuemeng 00324381
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint8 frw_task_thread_condition_check(oal_uint32 ul_core_id)
{
    /* ����OAL_TRUE
        1.���ȶ��зǿ�
        2.���ȶ������з�pause�Ķ���
    */
    oal_uint8                     sched_policy;
    oal_uint                      ul_irq_flag = 0;
    oal_dlist_head_stru           *pst_list;
    frw_event_sched_queue_stru    *pst_sched_queue;
    frw_event_queue_stru          *pst_event_queue = OAL_PTR_NULL;

    pst_sched_queue = g_ast_event_manager[ul_core_id].st_sched_queue;

    for(sched_policy = 0; sched_policy < FRW_SCHED_POLICY_BUTT; sched_policy++)
    {
        oal_spin_lock_irq_save(&pst_sched_queue[sched_policy].st_lock, &ul_irq_flag);
        /* ���������������� */
        OAL_DLIST_SEARCH_FOR_EACH(pst_list, &pst_sched_queue[sched_policy].st_head)
        {
            pst_event_queue = OAL_DLIST_GET_ENTRY(pst_list, frw_event_queue_stru, st_list);
            if(0 == pst_event_queue->st_queue.uc_element_cnt)
            {
                continue;
            }

            /* ����¼����е�vap_stateΪ��ͣ����������������ѡ��һ���¼����� */
            if (FRW_VAP_STATE_PAUSE == pst_event_queue->en_vap_state)
            {
                continue;
            }
            /*�ҵ��¼����зǿ�*/
            oal_spin_unlock_irq_restore(&pst_sched_queue[sched_policy].st_lock, &ul_irq_flag);
            return OAL_TRUE;
        }
        oal_spin_unlock_irq_restore(&pst_sched_queue[sched_policy].st_lock, &ul_irq_flag);
    }
    /*�շ���OAL_FALSE*/
    return OAL_FALSE;
}

/*lint -e578*//*lint -e19*/
oal_module_symbol(frw_event_alloc);
oal_module_symbol(frw_event_free);
oal_module_symbol(frw_event_dispatch_event);
oal_module_symbol(frw_event_post_event);
oal_module_symbol(frw_event_table_register);
oal_module_symbol(frw_event_dump_event);
oal_module_symbol(frw_event_process_all_event);
oal_module_symbol(frw_event_flush_event_queue);
oal_module_symbol(frw_event_queue_info);
oal_module_symbol(frw_event_get_info_from_event_queue);
oal_module_symbol(frw_event_vap_pause_event);
oal_module_symbol(frw_event_vap_resume_event);
oal_module_symbol(frw_event_vap_flush_event);
oal_module_symbol(frw_event_get_sched_queue);

oal_module_symbol(frw_is_event_queue_empty);
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
oal_module_symbol(frw_event_sub_rx_adapt_table_init);
#endif
#ifdef _PRE_DEBUG_MODE
oal_module_symbol(g_ast_event_time_track);
oal_module_symbol(g_ul_rx_event_idx);
oal_module_symbol(g_en_event_track_switch);
oal_module_symbol(g_ul_schedule_idx);
oal_module_symbol(g_aul_schedule_time);
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

