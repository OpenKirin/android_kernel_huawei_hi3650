/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : frw_ipc_msgqueue.c
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2012��10��16��
  ����޸�   :
  ��������   : IPCģ����Ϣ������ش�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��16��
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
#include "frw_main.h"
#include "frw_ipc_msgqueue.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_IPC_MSGQUEUE_C
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
OAL_STATIC frw_ipc_msg_callback_stru gst_ipc_msg_callback;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : frw_ipc_msg_queue_init
 ��������  : ��Ϣ���г�ʼ�����ڴ����
 �������  : pst_msg_queue: ��Ϣ���нṹ��ָ��
             ul_queue_len: ��Ϣ���г���
 �������  : ��
 �� �� ֵ  : �ɹ�����OAL_SUCC��
             ��μ��Ϊ��ָ��: OAL_ERR_CODE_PTR_NULL
             �ڴ����ʧ��: OAL_ERR_CODE_ALLOC_MEM_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_init(frw_ipc_msg_queue_stru *pst_msg_queue, oal_uint32 ul_queue_len)
{
    oal_uint16 us_queue_size = 0;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_msg_queue))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_init:: pst_msg_queue is null ptr!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* Ϊ������Ϣ���з����ڴ� */
    us_queue_size               = (oal_uint16)(OAL_SIZEOF(frw_ipc_msg_dscr_stru) * ul_queue_len);
    pst_msg_queue->pst_dscr     = (frw_ipc_msg_dscr_stru *)OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, us_queue_size, OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_msg_queue->pst_dscr))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_init:: pst_msg_queue->pst_dscr is null ptr!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* �ṹ�������ʼ�� */
    pst_msg_queue->ul_head      = 0;
    pst_msg_queue->ul_tail      = 0;
    pst_msg_queue->ul_max_num  = ul_queue_len;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_msg_queue_destroy
 ��������  : �ͷ���Ϣ�����ڴ�ռ�
 �������  : pst_msg_queue: ��Ϣ���нṹ��ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�OAL_SUCC
             ��μ��Ϊ��ָ��: OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_destroy(frw_ipc_msg_queue_stru *pst_msg_queue)
{
    /* ��μ�� */

    if (OAL_PTR_NULL == pst_msg_queue->pst_dscr)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_destroy:: pst_msg_queue->pst_dscr is null ptr}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_MEM_FREE(pst_msg_queue->pst_dscr, OAL_TRUE);

    pst_msg_queue->pst_dscr = OAL_PTR_NULL;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_msg_queue_recv
 ��������  : ��Ϣ���պ��������˼䷢�������ж�ʱ������ú˼��жϴ���������
             �жϴ����жϴ�����������ipc_msg_queue_recv������Ϣ���ú�
             ���������ж������ġ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�OAL_SUCC
             ʧ�ܷ��ػص������Ĵ�����Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_recv(oal_void *p_arg)
{
    frw_ipc_msg_queue_stru  *pst_ipc_rx_msg_queue;
    oal_uint32              ul_head             = 0;

    if (OAL_UNLIKELY(OAL_PTR_NULL == p_arg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_recv:: p_arg is null ptr!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_ipc_rx_msg_queue = (frw_ipc_msg_queue_stru *)(((oal_irq_dev_stru *)p_arg)->p_drv_arg);
    if (OAL_UNLIKELY(OAL_PTR_NULL == gst_ipc_msg_callback.p_rx_complete_func))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_recv:: gst_ipc_msg_callback.p_rx_complete_func is null ptr!}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ���в��� */
    do
    {
        ul_head = (pst_ipc_rx_msg_queue->ul_head);
        FRW_IPC_RING_RX_INCR(pst_ipc_rx_msg_queue->ul_head);

        /* �ص�ipc_recv() */
        gst_ipc_msg_callback.p_rx_complete_func(pst_ipc_rx_msg_queue->pst_dscr[ul_head].pst_msg_mem);

    }while (!FRW_IPC_RING_EMPTY(pst_ipc_rx_msg_queue->ul_head, pst_ipc_rx_msg_queue->ul_tail));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_msg_queue_send(ipc_node *node, oal_netbuf_t *buf);
 ��������  : �˼���Ϣ���Ͳ�����
 �������  : pst_ipc_tx_msg_queue: ������Ϣ���нṹ��ָ��
             pst_msg_input: �˼�ͨѶ��Ϣ��ַ
             uc_flags: �Ƿ�������жϵı�־
             uc_cpuid: ����Ŀ���ID
 �������  : ������: OAL_FAIL
             �ɹ�: OAL_SUCC
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��16��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_send(frw_ipc_msg_queue_stru *pst_ipc_tx_msg_queue, frw_ipc_msg_mem_stru *pst_msg_input, oal_uint8 uc_flags, oal_uint8 uc_cpuid)
{
    oal_uint32  ul_tail = 0;

    if (OAL_UNLIKELY((OAL_PTR_NULL == pst_ipc_tx_msg_queue) || OAL_PTR_NULL == pst_msg_input))
    {
        OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_ipc_msg_queue_send: pst_ipc_tx_msg_queue/pst_msg_input is null ptr: %d %d}", pst_ipc_tx_msg_queue, pst_msg_input);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD �� */

    /* �ж϶����Ƿ��� */
    if (OAL_UNLIKELY(FRW_IPC_RING_FULL(pst_ipc_tx_msg_queue->ul_head,
                      pst_ipc_tx_msg_queue->ul_tail,
                      pst_ipc_tx_msg_queue->ul_max_num)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_send:: FRW_IPC_RING_FULL OAL_ERR_CODE_IPC_QUEUE_FULL.}");
        return OAL_ERR_CODE_IPC_QUEUE_FULL;
    }

    ul_tail = pst_ipc_tx_msg_queue->ul_tail;
    FRW_IPC_RING_TX_INCR(pst_ipc_tx_msg_queue->ul_tail);

    pst_ipc_tx_msg_queue->pst_dscr[ul_tail].pst_msg_mem = pst_msg_input;

    /* Ŀ������Ϊ����������Ŀ���Ӳ���ж� */
    if (FRW_IPC_TX_CTRL_ENABLED == uc_flags)
    {
        oal_irq_trigger(uc_cpuid);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_msg_handler_register
 ��������  : ��������ע��
 �������  : p_ipc_msg_handler: �������ӽṹ��ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�OAL_SUCC
             ��μ��Ϊ��ָ��: OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_msg_queue_register_callback(frw_ipc_msg_callback_stru *p_ipc_msg_handler)
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == p_ipc_msg_handler))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_register_callback:: p_ipc_msg_handler is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    gst_ipc_msg_callback.p_rx_complete_func = p_ipc_msg_handler->p_rx_complete_func;
    gst_ipc_msg_callback.p_tx_complete_func = p_ipc_msg_handler->p_tx_complete_func;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_log_exit
 ��������  : ά��ģ���˳�
 �������  : pst_log: ά����Ϣ�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_log_exit(frw_ipc_log_stru *pst_log)
{
    /* TBD */
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_log_init
 ��������  : ά��ģ���ʼ��
 �������  : pst_log: ά����Ϣ�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����OAL_SUCC��ʧ�ܷ���OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_log_init(frw_ipc_log_stru *pst_log)
{
    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_init:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD */
    pst_log->ul_stats_assert        = 0;
    pst_log->ul_stats_send_lost     = 0;
    pst_log->ul_stats_recv_lost     = 0;
    pst_log->ul_stats_recv          = 0;
    pst_log->ul_stats_send          = 0;
    pst_log->ul_tx_index            = 0;
    pst_log->ul_rx_index            = 0;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_log_alarm
 ��������  : �˼�ͨ�Ž��ն����澯
 �������  : pst_log: ά����Ϣ�ṹ��ָ��
             ul_lost: ��������
 �������  : ��
 �� �� ֵ  : �ɹ�����OAL_SUCC��ʧ�ܷ���OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_log_recv_alarm(frw_ipc_log_stru *pst_log, oal_uint32 ul_lost)
{
    oal_int32 l_lost, l_assert = 0;

    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_recv_alarm:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_log->ul_stats_recv_lost += ul_lost;    /* ���������� */
    pst_log->ul_stats_assert++;              /* �澯�������� */

    l_lost      = (oal_int32)pst_log->ul_stats_recv_lost;
    l_assert    = (oal_int32)pst_log->ul_stats_assert;

    FRW_IPC_LOST_WARNING_LOG2(0, "The number of rx lost package respectively are ", l_lost, l_assert);
    OAM_WARNING_LOG2(0, OAM_SF_FRW, "{frw_ipc_log_recv_alarm::The number of rx lost package respectively are  %d %d}", l_lost, l_assert);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_log_send_alarm
 ��������  : �˼�ͨ�ŷ��Ͷ����澯
 �������  : pst_log: ά����Ϣ�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����OAL_SUCC��ʧ�ܷ���OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_log_send_alarm(frw_ipc_log_stru *pst_log)
{
    oal_int32 l_lost;

    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_send_alarm:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_log->ul_stats_send_lost++;
    pst_log->ul_stats_assert++;         /* �澯�������� */

    l_lost = (oal_int32)pst_log->ul_stats_send_lost;

    FRW_IPC_LOST_WARNING_LOG1(0, "The number of tx lost package respectively are ", l_lost);
    OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_log_send_alarm::the number of tx lost packets are %d. }\r\n", l_lost);
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_log_send
 ��������  : ͳ�Ʒ�����Ϣ
 �������  : pst_log: ά����Ϣ�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����OAL_SUCC��ʧ�ܷ���OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_log_send(frw_ipc_log_stru *pst_log, oal_uint16 us_seq_num, oal_uint8 uc_target_cpuid, oal_uint8 uc_msg_type)
{
    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_send:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAX_LOG_RECORD != pst_log->ul_tx_index)
    {
        pst_log->ul_stats_send++;
        pst_log->st_tx_stats_record[pst_log->ul_tx_index].us_seq_num      = us_seq_num;
        pst_log->st_tx_stats_record[pst_log->ul_tx_index].uc_target_cpuid = uc_target_cpuid;
        pst_log->st_tx_stats_record[pst_log->ul_tx_index].uc_msg_type     = uc_msg_type;
        pst_log->st_tx_stats_record[pst_log->ul_tx_index].l_time_stamp    = OAL_TIME_GET_STAMP_MS();
        pst_log->ul_tx_index++;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_log_recv
 ��������  : ͳ�ƽ�����Ϣ
 �������  : pst_log: ά����Ϣ�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����OAL_SUCC��ʧ�ܷ���OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_log_recv(frw_ipc_log_stru *pst_log, oal_uint16 us_seq_num, oal_uint8 uc_target_cpuid, oal_uint8 uc_msg_type)
{
    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_recv:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    if (MAX_LOG_RECORD != pst_log->ul_rx_index)
    {
        pst_log->ul_stats_recv++;
        pst_log->st_rx_stats_record[pst_log->ul_rx_index].us_seq_num      = us_seq_num;
        pst_log->st_rx_stats_record[pst_log->ul_rx_index].uc_target_cpuid = uc_target_cpuid;
        pst_log->st_rx_stats_record[pst_log->ul_rx_index].uc_msg_type     = uc_msg_type;
        pst_log->st_rx_stats_record[pst_log->ul_rx_index].l_time_stamp    = OAL_TIME_GET_STAMP_MS();
        pst_log->ul_rx_index++;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_log_print
 ��������  : ����¼�ڷ�����־�����е���־��ӡ
 �������  : pst_log: ��־��Ϣ�ṹ��
 �������  : ��
 �� �� ֵ  : �ɹ�����OAL_SUCC��ʧ�ܷ���OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_log_tx_print(frw_ipc_log_stru *pst_log)
{
    oal_uint16 us_log_index = 0;

    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_tx_print:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    for (us_log_index = 0; us_log_index < pst_log->ul_tx_index; us_log_index++)
    {
        FRW_IPC_LOG_INFO_PRINT4(0, "SEND SEQUENCE NUMBER:  TARGET CPUID:  MESSAGE TYPE: TIME STAMP: ",
                          (oal_int32)pst_log->st_tx_stats_record[us_log_index].us_seq_num,
                          (oal_int32)pst_log->st_tx_stats_record[us_log_index].uc_target_cpuid,
                          (oal_int32)pst_log->st_tx_stats_record[us_log_index].uc_msg_type,
                          (oal_int32)pst_log->st_tx_stats_record[us_log_index].l_time_stamp);
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_log_rx_print
 ��������  : ����¼�ڽ�����־�����е���־��Ϣ��ӡ
 �������  : pst_log: ��־��Ϣ�ṹ��
 �������  : ��
 �� �� ֵ  : �ɹ�����OAL_SUCC��ʧ�ܷ���OAL_ERR_CODE_PTR_NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��22��
    ��    ��   : t00231215
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_log_rx_print(frw_ipc_log_stru *pst_log)
{
    oal_uint16 us_log_index = 0;

    if (OAL_PTR_NULL == pst_log)
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_log_rx_print:: pst_log is null ptr.}");
        return OAL_ERR_CODE_PTR_NULL;
    }

    FRW_IPC_LOG_INFO_PRINT1(0, "times of recieve:", (oal_int32)pst_log->ul_stats_recv);

    for (us_log_index = 0; us_log_index < pst_log->ul_rx_index; us_log_index++)
    {
        FRW_IPC_LOG_INFO_PRINT4(0, "RECEIVE SEQUENCE NUMBER: TARGET CPUID: MESSAGE TYPE:  TIME STAMP:",
                          (oal_int32)pst_log->st_rx_stats_record[us_log_index].us_seq_num,
                          (oal_int32)pst_log->st_rx_stats_record[us_log_index].uc_target_cpuid,
                          (oal_int32)pst_log->st_rx_stats_record[us_log_index].uc_msg_type,
                          (oal_int32)pst_log->st_rx_stats_record[us_log_index].l_time_stamp);
    }

    return OAL_SUCC;
}










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

