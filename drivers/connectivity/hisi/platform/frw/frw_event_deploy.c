/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : frw_event_deploy.c
  �� �� ��   : ����
  ��    ��   : c00178899
  ��������   : 2012��10��16��
  ����޸�   :
  ��������   : �¼������Լ��˼�ͨ����ģ�飬��������ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��16��
    ��    ��   : c00178899
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
#include "frw_event_deploy.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_DEPLOY_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* ipcȫ�ֽṹ��:ÿ����һ��,AMP����µ�ǰֻ����˫�˳��� */
OAL_STATIC frw_ipc_node_stru         g_st_ipc_node[FRW_IPC_CORE_TYPE_BUTT];

/* ���˷��͸��Ӻ˵���Ϣ���� */
OAL_STATIC frw_ipc_msg_queue_stru    g_st_queue_master_to_slave;

/* �Ӻ˷��͸����˵���Ϣ���� */
OAL_STATIC frw_ipc_msg_queue_stru    g_st_queue_slave_to_master;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/* IPC�ӿ� */
OAL_STATIC oal_uint32  frw_ipc_init(oal_void);
OAL_STATIC oal_uint32  frw_ipc_init_master(frw_ipc_node_stru *pst_ipc_node);
OAL_STATIC oal_uint32  frw_ipc_init_slave(frw_ipc_node_stru *pst_ipc_node);
OAL_STATIC oal_uint32  frw_ipc_exit(oal_void);
OAL_STATIC oal_void  frw_ipc_recv(frw_ipc_msg_mem_stru *pst_ipc_mem_msg);
OAL_STATIC oal_uint32  frw_ipc_send(frw_ipc_msg_mem_stru *pst_ipc_mem_msg);
OAL_STATIC oal_uint32  frw_ipc_send_connect_request(oal_void);
OAL_STATIC oal_uint32  frw_ipc_send_connect_response(oal_void);
OAL_STATIC oal_uint32  frw_ipc_send_inter_msg(oal_uint8 uc_msg_type, oal_uint8 *puc_data, oal_uint8 us_len);
OAL_STATIC oal_void  frw_ipc_tx_complete(frw_ipc_msg_mem_stru *pst_msg);
OAL_STATIC oal_uint32  frw_ipc_event_queue_full(oal_void);
OAL_STATIC oal_uint32  frw_ipc_event_queue_empty(oal_void);

/* �¼�����ӿ� */
OAL_STATIC oal_uint32  frw_event_deploy_pipeline(oal_mem_stru *pst_mem_event, frw_event_deploy_enum_uint8 *en_deploy_result);

/*****************************************************************************
 �� �� ��  : frw_ipc_recv
 ��������  : ��Ϣ���մ����������ж������Ļ��������ܼ���
 �������  : pst_ipc_mem_msg: ��Ϣ�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC: �ɹ�; ����: ʧ��
 ���ú���  : �ɽ����жϴ���ص�
 ��������  : IPCģ���ڲ���������

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  frw_ipc_recv(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    frw_ipc_msg_header_stru     *pst_header;    /* ��Ϣͷ���ṹ�� */
    frw_ipc_core_type_enum_uint8 en_type;       /* CPU����: ���˻�Ӻ� */

    /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_mem_msg))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_recv::OAL_PTR_NULL == pst_ipc_mem_msg}\r\n");
        return;
    }

    /* ��ȡ��Ϣͷ��, ��IPC����ʱ�Ѿ�Ų��puc_dataָ�룬�˴���ָ����ָ��IPCͷ */
    pst_header = (frw_ipc_msg_header_stru *)(pst_ipc_mem_msg->puc_data);

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_header
        || pst_header->uc_target_cpuid > FRW_IPC_CORE_NUM_BUTT
        || pst_header->uc_msg_type > FRW_IPC_MSG_TYPE_BUTT))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{pst_header is incorrect.}");
        return;
    }

    /* ��ȡ��ǰ�ں���Ϣ */
    en_type = frw_ipc_get_core_type();

    /* �ж�seq number�Ƿ���ȷ */
    if (OAL_LIKELY(g_st_ipc_node[en_type].us_seq_num_rx_expect == pst_header->us_seq_number))
    {
        g_st_ipc_node[en_type].us_seq_num_rx_expect++;  /* �ñ���ֻ���������д */
    }
    else if(g_st_ipc_node[en_type].us_seq_num_rx_expect < pst_header->us_seq_number)
    {
        /* �����´��յ���ƥ��� */
        g_st_ipc_node[en_type].us_seq_num_rx_expect = pst_header->us_seq_number + 1;

    #ifdef _PRE_DEBUG_MODE
        /* ��־���澯 */
        frw_ipc_log_recv_alarm(&g_st_ipc_node[en_type].st_log,
                               (pst_header->us_seq_number - g_st_ipc_node[en_type].us_seq_num_rx_expect));
    #endif
    }
    else
    {
        /* ˵������Ҷ����� */
        /* �����´��յ���ƥ��� */
        g_st_ipc_node[en_type].us_seq_num_rx_expect = pst_header->us_seq_number + 1;
    #ifdef _PRE_DEBUG_MODE
        /* ��־���澯���������㹫ʽ: ��ǰ���к�+���к����ֵ-���к�����ֵ+1 */
        frw_ipc_log_recv_alarm(&g_st_ipc_node[en_type].st_log,
                               (pst_header->us_seq_number + FRW_IPC_MAX_SEQ_NUMBER - g_st_ipc_node[en_type].us_seq_num_rx_expect + 1));
    #endif
    }

#ifdef _PRE_DEBUG_MODE
    /* ������־ */
    frw_ipc_log_recv(&g_st_ipc_node[en_type].st_log,
                     pst_header->us_seq_number,
                     pst_header->uc_target_cpuid,
                     pst_header->uc_msg_type);
#endif

    switch (pst_header->uc_msg_type)
    {
        case FRW_IPC_MSG_TYPE_EVENT:

            /* ��IPC����ʱ��ƫ�Ƶ�IPCͷ��λ�ã�����������Ҫ��ƫ�Ƶ��¼��ṹ��λ�� */
            pst_ipc_mem_msg->puc_data += FRW_IPC_MSG_HEADER_LENGTH;

            /* �¼�ֱ����Ӳ��� */
            frw_event_post_event(pst_ipc_mem_msg,OAL_GET_CORE_ID());

            break;

        case FRW_IPC_MSG_TYPE_TX_INT_ENABLE:
            /* �޸ķ���״̬���Ʊ�ʶ��ԭ�Ӳ��� */
            g_st_ipc_node[en_type].en_tx_int_ctl = FRW_IPC_TX_CTRL_ENABLED;

            break;

        case FRW_IPC_MSG_TYPE_TX_INT_DISENABLE:
            /* �޸ķ���״̬���Ʊ�ʶ��ԭ�Ӳ��� */
            g_st_ipc_node[en_type].en_tx_int_ctl = FRW_IPC_TX_CTRL_DISABLED;

            break;

        case FRW_IPC_MSG_TYPE_CONNECT_REQUEST:
            /* ����������Ӧ */
            frw_ipc_send_connect_response();

            break;

        case FRW_IPC_MSG_TYPE_CONNECT_RESPONSE:
            /* �޸�״̬��ԭ�Ӳ��� */
            g_st_ipc_node[en_type].en_states = FRW_IPC_CORE_STATE_CONNECTED;

            break;

        case FRW_IPC_MSG_TYPE_CONFIG_REQUEST:
        case FRW_IPC_MSG_TYPE_CONFIG_RESPONSE:
        case FRW_IPC_MSG_TYPE_ERROR_NOTICE:
        case FRW_IPC_MSG_TYPE_RESET_REQUEST:
        case FRW_IPC_MSG_TYPE_RESET_RESPONSE:
        case FRW_IPC_MSG_TYPE_OPEN_OAM:
        case FRW_IPC_MSG_TYPE_CLOSE_OAM:
        case FRW_IPC_MSG_TYPE_EXIT_REQUEST:
        case FRW_IPC_MSG_TYPE_EXIT_RESPONSE:
        default:

            break;
    }

    /* �ͷ���Ϣ */
    FRW_EVENT_FREE(pst_ipc_mem_msg);
}

/*****************************************************************************
 �� �� ��  : frw_ipc_send
 ��������  : ����ӿ�, ���ͺ˼���Ϣ, ��Ϣ����Ϊ�¼�, ���øú���������ͷ��ڴ�
 �������  : pst_ipc_mem_msg: ��Ϣ�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC: �ɹ�; ����: ʧ��
 ���ú���  : �ⲿģ�����������¼�
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_send(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    oal_uint32                   ul_ret;
    frw_ipc_msg_header_stru     *pst_header;        /* ��Ϣͷ���ṹ�� */
    frw_ipc_msg_queue_stru      *pst_msg_queue;     /* ��Ϣ���� */
    frw_ipc_core_type_enum_uint8 en_type;           /* CPU����: ���˻�Ӻ� */



    /* ��ȡ��ǰ�ں���Ϣ */
    en_type = frw_ipc_get_core_type();
    FRW_IPC_GET_MSG_QUEUE(pst_msg_queue, en_type);

    /* ��鵱ǰIPCģ��״̬*/
    if (FRW_IPC_CORE_STATE_CONNECTED != g_st_ipc_node[en_type].en_states)
    {
        OAM_WARNING_LOG2(0, OAM_SF_FRW, "{frw_ipc_send::FRW_IPC_CORE_STATE_CONNECTED != g_st_ipc_node[en_type].en_states. en_type:%d, en_states:%d}\r\n", en_type, g_st_ipc_node[en_type].en_states);
        return OAL_FAIL;
    }

    /* ��ȡIPCͷ�� */
    pst_header = (frw_ipc_msg_header_stru *)frw_ipc_get_header(pst_ipc_mem_msg);

    /* �˼���Ϣͷ����� */
    pst_header->us_seq_number   = g_st_ipc_node[en_type].us_seq_num_tx_expect;
    pst_header->uc_target_cpuid = g_st_ipc_node[en_type].en_target_cpuid;
    pst_header->uc_msg_type     = FRW_IPC_MSG_TYPE_EVENT;

    /* ���ͺ˼���Ϣ */
    ul_ret = frw_ipc_msg_queue_send(pst_msg_queue,
                                    pst_ipc_mem_msg,
                                    g_st_ipc_node[en_type].en_tx_int_ctl,
                                    g_st_ipc_node[en_type].en_target_cpuid);

    if (OAL_UNLIKELY(OAL_ERR_CODE_IPC_QUEUE_FULL == ul_ret))
    {
    #ifdef _PRE_DEBUG_MODE
        frw_ipc_log_send_alarm(&g_st_ipc_node[en_type].st_log);
    #endif
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send::frw_ipc_msg_queue_send return err code: %d}", OAL_ERR_CODE_IPC_QUEUE_FULL);
        return ul_ret;
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send::frw_ipc_msg_queue_send return err code:%d}", ul_ret);
        return ul_ret;
    }

    /* �������к� */
    g_st_ipc_node[en_type].us_seq_num_tx_expect++;

    /* �����¼��ṹ�����ü��� */
    pst_ipc_mem_msg->uc_user_cnt++;

#ifdef _PRE_DEBUG_MODE
    /* ������־ */
    frw_ipc_log_send(&g_st_ipc_node[en_type].st_log,
                     pst_header->us_seq_number,
                     pst_header->uc_target_cpuid,
                     pst_header->uc_msg_type);
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_tx_complete_handler
 ��������  : ��������жϴ�����OFFLOAD����²��ã�OFFLOAD�������Ҫ��
 �������  : pst_msg:��Ϣ�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC: �ɹ�; ����: ʧ��
 ���ú���  : �ɷ�������жϴ���ص�
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  frw_ipc_tx_complete(frw_ipc_msg_mem_stru *pst_msg)
{
    /* TBD */
}

/*****************************************************************************
 �� �� ��  : frw_ipc_init
 ��������  : ����ӿڣ�IPCģ���ʼ����OFFLOAD�������CPU�������˵��øú���
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC���ɹ���������ʧ��
 ���ú���  : �ⲿ�����ʼ����ģ��
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��16��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_init(oal_void)
{
    oal_uint32   ul_ret;

    if(FRW_IPC_CORE_TYPE_MASTER == frw_ipc_get_core_type())
    {
        ul_ret = frw_ipc_init_master(&g_st_ipc_node[FRW_IPC_CORE_TYPE_MASTER]);
    }
    else
    {
        ul_ret = frw_ipc_init_slave(&g_st_ipc_node[FRW_IPC_CORE_TYPE_SLAVE]);
    }

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw ipc init fail.}");
        return ul_ret;
    }

    /* �������� */
    ul_ret = frw_ipc_send_connect_request();
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw ipc connect fail.}");
        return ul_ret;
    }

    /* �����º���ע�ᵽ�¼�����ģ���� */
    frw_event_ipc_event_queue_full_register(frw_ipc_event_queue_full);
    frw_event_ipc_event_queue_empty_register(frw_ipc_event_queue_empty);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_init_master
 ��������  : ����IPCģ���ʼ����OFFLOAD�������CPU��WIFI�����øú���
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC���ɹ���������ʧ��
 ���ú���  : IPC��ʼ��
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��16��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_init_master(frw_ipc_node_stru *pst_ipc_node)
{
    oal_uint32 ul_ret;

    /* ȫ�ֽṹ���ʼ�� */
    pst_ipc_node->en_cpuid             = FRW_IPC_CORE_ID_MASTER;
    pst_ipc_node->en_target_cpuid      = FRW_IPC_CORE_ID_SLAVE;
    pst_ipc_node->en_cpu_type          = FRW_IPC_CORE_TYPE_MASTER;
    pst_ipc_node->us_seq_num_rx_expect = 0;
    pst_ipc_node->us_seq_num_tx_expect = 0;
    pst_ipc_node->en_states            = FRW_IPC_CORE_STATE_INIT;
    pst_ipc_node->en_tx_int_ctl        = FRW_IPC_TX_CTRL_ENABLED;

    /* ���������Ϣ���г�ʼ�� */
    /* ���Ͷ��г�ʼ�� */
    ul_ret = frw_ipc_msg_queue_init(&g_st_queue_master_to_slave,
                                    FRW_IPC_MASTER_TO_SLAVE_QUEUE_MAX_NUM);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_msg_queue_init g_st_queue_master_to_slave return err code:%d}", ul_ret);
        return ul_ret;
    }

    /* ���ն��г�ʼ�� */
    ul_ret = frw_ipc_msg_queue_init(&g_st_queue_slave_to_master,
                                    FRW_IPC_SLAVE_TO_MASTER_QUEUE_MAX_NUM);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW,  "{frw_ipc_init_master:: frw_ipc_msg_queue_init g_st_queue_slave_to_master return err code:%d}", ul_ret);
        return ul_ret;
    }

    /* �ж�ע�� */
    pst_ipc_node->st_irq_dev.p_irq_intr_func    = frw_ipc_msg_queue_recv;
    pst_ipc_node->st_irq_dev.ul_irq             = OAL_IRQ_NUM;
    pst_ipc_node->st_irq_dev.l_irq_type         = OAL_SA_SHIRQ;
    pst_ipc_node->st_irq_dev.pc_name            = "ipc";
    pst_ipc_node->st_irq_dev.p_drv_arg          = (void *)&g_st_queue_slave_to_master;

    if (OAL_UNLIKELY(0 != oal_irq_setup(&pst_ipc_node->st_irq_dev)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_setup_irq:: oal_irq_setup fail!}");
        return OAL_FAIL;
    }

    /* �ص�����ע�� */
    pst_ipc_node->st_ipc_msg_callback.p_rx_complete_func = frw_ipc_recv;
    pst_ipc_node->st_ipc_msg_callback.p_tx_complete_func = frw_ipc_tx_complete;
    ul_ret = frw_ipc_msg_queue_register_callback(&pst_ipc_node->st_ipc_msg_callback);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_msg_queue_register_callback return err code:%d}", ul_ret);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    /* ��־��ʼ�� */
    ul_ret = frw_ipc_log_init(&pst_ipc_node->st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_master: frw_ipc_log_init return err code:%d}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;

}


/*****************************************************************************
 �� �� ��  : frw_ipc_init_slave
 ��������  : �Ӻ�IPCģ���ʼ��: OFFLOAD����²���Ҫ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC���ɹ���������ʧ��
 ���ú���  : IPC��ʼ��
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��16��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_init_slave(frw_ipc_node_stru *pst_ipc_node)
{
    oal_uint32 ul_ret;

    /* ȫ�ֽṹ���ʼ�� */
    pst_ipc_node->en_cpuid             = (oal_uint8)OAL_GET_CORE_ID();
    pst_ipc_node->en_target_cpuid      = FRW_IPC_CORE_ID_MASTER;
    pst_ipc_node->en_cpu_type          = FRW_IPC_CORE_TYPE_SLAVE;
    pst_ipc_node->us_seq_num_rx_expect = 0;
    pst_ipc_node->us_seq_num_tx_expect = 0;
    pst_ipc_node->en_states            = FRW_IPC_CORE_STATE_INIT;
    pst_ipc_node->en_tx_int_ctl        = FRW_IPC_TX_CTRL_ENABLED;

    /* �ж�ע�� */
    pst_ipc_node->st_irq_dev.p_irq_intr_func    = frw_ipc_msg_queue_recv;
    pst_ipc_node->st_irq_dev.ul_irq             = OAL_IRQ_NUM;
    pst_ipc_node->st_irq_dev.l_irq_type         = OAL_SA_SHIRQ;
    pst_ipc_node->st_irq_dev.pc_name            = "ipc";
    pst_ipc_node->st_irq_dev.p_drv_arg          = (void *)&g_st_queue_master_to_slave;

    if (OAL_UNLIKELY(0 != oal_irq_setup(&pst_ipc_node->st_irq_dev)))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw_ipc_msg_queue_setup_irq: oal_irq_setup fail!}");
        return OAL_FAIL;
    }

    /* �ص�����ע�� */
    pst_ipc_node->st_ipc_msg_callback.p_rx_complete_func = frw_ipc_recv;
    pst_ipc_node->st_ipc_msg_callback.p_tx_complete_func = frw_ipc_tx_complete;
    ul_ret = frw_ipc_msg_queue_register_callback(&pst_ipc_node->st_ipc_msg_callback);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_slave:: frw_ipc_msg_queue_register_callback return err code:%d}", ul_ret);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    /* ��־��ʼ�� */
    ul_ret = frw_ipc_log_init(&pst_ipc_node->st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_init_slave: frw_ipc_log_init return err code:%d}", ul_ret);
        return ul_ret;
    }
#endif

    return OAL_SUCC;

}

/*****************************************************************************
 �� �� ��  : frw_ipc_exit
 ��������  : �������ͷ���Դ
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC���˳���Ӧ����ɹ����������˳���Ӧ����ʧ��
 ���ú���  : IPC�ڲ�����
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_exit(oal_void)
{
    oal_uint32 ul_ret;
    frw_ipc_core_type_enum_uint8  en_type;       /* CPU����: ���˻�Ӻ� */

    /* ��ȡ��ǰ�ں���Ϣ */
    en_type = frw_ipc_get_core_type();

    /* �޸�IPCģ��״̬ */
    g_st_ipc_node[en_type].en_states = FRW_IPC_CORE_STATE_EXIT;

    /* ע���˼��ж� */
    oal_irq_free(&g_st_ipc_node[en_type].st_irq_dev);

    /* �ͷ���Ϣ���� */
    if (FRW_IPC_CORE_ID_MASTER == en_type) /* ���� */
    {
        /* ���Ͷ���ע�� */
        ul_ret = frw_ipc_msg_queue_destroy(&g_st_queue_master_to_slave);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_exit: frw_ipc_msg_queue_destroy g_st_queue_master_to_slave return err code:%d}", ul_ret);
            return ul_ret;
        }

        /* ���ն���ע�� */
        ul_ret = frw_ipc_msg_queue_destroy(&g_st_queue_slave_to_master);
        if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
        {
            OAM_WARNING_LOG1(0, OAM_SF_FRW, "frw_ipc_exit:: frw_ipc_msg_queue_destroy g_st_queue_slave_to_master return err code:%d", ul_ret);
            return ul_ret;
        }
    }

#ifdef _PRE_DEBUG_MODE
    /* ��ӡ��־��Ϣ */
    frw_ipc_log_tx_print(&g_st_ipc_node[en_type].st_log);
    frw_ipc_log_rx_print(&g_st_ipc_node[en_type].st_log);

    /* �˳���־ģ�� */
    ul_ret = frw_ipc_log_exit(&g_st_ipc_node[en_type].st_log);
    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        return ul_ret;
    }
#endif

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_send_connect_request
 ��������  : �����첽��ʽ�������ӣ��ú���ֻ������������
             ���жϷ��������н��մ���������Ӧ�����ı�IPC״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC��������������ɹ���������������������ʧ��
 ���ú���  : IPC�ڲ�����
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_send_connect_request(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_CONNECT_REQUEST,
                                    OAL_PTR_NULL,
                                    0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send_connect_request: frw_ipc_send_inter_msg return %d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_send_connect_response
 ��������  : �������ж������ģ������첽��ʽ�������ӣ��ú���ֻ����������Ӧ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC��������������ɹ���������������������ʧ��
 ���ú���  : IPC�ڲ�����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_send_connect_response(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_CONNECT_RESPONSE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_send_connect_response: frw_ipc_send_inter_msg return %d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_inter_msg_send
 ��������  : ���ͺ˼�ͨ���ڲ���Ϣ
 �������  : uc_msg_type: �ڲ���Ϣ����
             puc_data: ��Ҫ���͵�����
             us_len: ���ݳ���
 �������  : ��
 �� �� ֵ  : OAL_SUCC�����ͳɹ���OAL_FAIL������ʧ��
 ���ú���  : IPC�ڲ�����
 ��������  : �����¼������ӿ�

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_send_inter_msg(oal_uint8  uc_msg_type,
                                                       oal_uint8 *puc_data,
                                                       oal_uint8  us_len)
{
    oal_uint32                   ul_ret;
    frw_ipc_msg_mem_stru        *pst_msg_mem_stru;  /* ��Ϣ�ڴ�� */
    frw_ipc_inter_msg_stru      *pst_ipc_msg;       /* ��Ϣ�ṹ�� */
    frw_ipc_msg_queue_stru      *pst_msg_queue;     /* ��Ϣ���� */
    frw_ipc_core_type_enum_uint8 en_type;           /* CPU����: ���˻�Ӻ� */
    oal_uint8                    ul_length;

    /* ��ȡ��ǰ�ں���Ϣ */
    en_type = frw_ipc_get_core_type();
    FRW_IPC_GET_MSG_QUEUE(pst_msg_queue, en_type);

    /* ����˼��ڲ���Ϣ�ڴ� */
    ul_length = OAL_SIZEOF(frw_ipc_inter_msg_stru) - 4 + us_len;
    pst_msg_mem_stru = FRW_EVENT_ALLOC(ul_length);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_msg_mem_stru))
    {
        OAM_ERROR_LOG0(0, OAM_SF_FRW, "{frw_ipc_send_inter_msg: FRW_EVENT_ALLOC fail!}");
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��ȡ��Ϣ��ַ */
    pst_ipc_msg = (frw_ipc_inter_msg_stru *)frw_ipc_get_header(pst_msg_mem_stru);

    /* �����Ϣͷ */
    pst_ipc_msg->st_ipc_hdr.us_seq_number   = g_st_ipc_node[en_type].us_seq_num_tx_expect;
    pst_ipc_msg->st_ipc_hdr.uc_target_cpuid = g_st_ipc_node[en_type].en_target_cpuid;
    pst_ipc_msg->st_ipc_hdr.uc_msg_type     = uc_msg_type;
    pst_ipc_msg->ul_length                  = us_len;

    /* ������� */
    if (us_len > 0)
    {
        oal_memcopy((oal_void *)pst_ipc_msg->auc_data, (oal_void *)puc_data, us_len);
    }

    /* �����ڲ���Ϣ */
    ul_ret = frw_ipc_msg_queue_send(pst_msg_queue,
                                    pst_msg_mem_stru,
                                    g_st_ipc_node[en_type].en_tx_int_ctl,
                                    g_st_ipc_node[en_type].en_target_cpuid);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{send inter msg fail.}");
        FRW_EVENT_FREE(pst_msg_mem_stru);
        return ul_ret;
    }

#ifdef _PRE_DEBUG_MODE
    /* ������־ */
    frw_ipc_log_send(&g_st_ipc_node[en_type].st_log,
                      g_st_ipc_node[en_type].us_seq_num_tx_expect,
                      g_st_ipc_node[en_type].en_target_cpuid,
                      uc_msg_type);
#endif

    /* �������к� */
    g_st_ipc_node[en_type].us_seq_num_tx_expect++;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_reset
 ��������  : IPCģ�鸴λ
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC���ɹ���������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899

*****************************************************************************/
oal_uint32  frw_ipc_reset(oal_void)
{
    /* TBD */
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_pkt_dispatch
 ��������  : ��˱��ķַ��������
 �������  : buf-����֡�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC���ɹ���������ʧ��
 ���ú���  : ע��ҽ��ڱ��Ľ�����ڴ�
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_smp_dispatch(oal_void *buf)
{
    /* TBD */

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_pkt_ordering
 ��������  : ���ı�����
 �������  : buf-����֡�ṹ��ָ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC���ɹ���������ʧ��
 ���ú���  : ע��ҽ��ڱ��ķ��ͳ��ڴ�
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_ipc_smp_ordering(oal_void *buf)
{
    /* TBD */

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_event_queue_full
 ��������  : ���¼�����ģ�鷢�ֶ��и���ĳ����ֵʱ�����øýӿ�֪ͨ�Է��ں�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC���ɹ���������ʧ��
 ���ú���  : �¼�����ģ��
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_event_queue_full(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_TX_INT_DISENABLE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_event_queue_full: frw_ipc_send_inter_msg return err code:%d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_event_queue_empty
 ��������  : ���¼�����ģ�鷢�ֶ��е���ĳ����ֵʱ�����øýӿ�֪ͨ�Է��ں�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC���ɹ���������ʧ��
 ���ú���  : �¼�����ģ��
 ��������  : �ڲ�����

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_ipc_event_queue_empty(oal_void)
{
    oal_uint32    ul_ret;

    ul_ret = frw_ipc_send_inter_msg(FRW_IPC_MSG_TYPE_TX_INT_ENABLE, OAL_PTR_NULL, 0);

    if (OAL_UNLIKELY(OAL_SUCC != ul_ret))
    {
        OAM_WARNING_LOG1(0, OAM_SF_FRW, "{frw_ipc_event_queue_empty: frw_ipc_send_inter_msg return err code:%d}", ul_ret);
        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_deploy_init
 ��������  : ����ӿڣ��¼�����ģ���ʼ���ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC-�ɹ�; ����-ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_deploy_init(oal_void)
{
    oal_uint32 ul_ret;

    ul_ret = frw_ipc_init();
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw event deploy init fail.}");
        return ul_ret;
    }

    /* TBD */

    /* �¼�����ģ�����ݽṹ��ʼ�� */

    /* ���ּ�����¼������վ��ⲿ��ʽ���г�ʼ�� */

    /* �����, �����HMAC DMAC PIPELINE��ʽ����ע��frw_event_deploy_pipeline */

    /* �����, ����ǰ���CHIP,DEVICE,VAP��ʽ����ע��frw_event_deploy_owner */

    frw_event_deploy_register(frw_event_deploy_pipeline);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : frw_event_deploy_exit
 ��������  : ����ӿڣ��¼�����ģ���˳��ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC-�ɹ�; ����-ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_deploy_exit(oal_void)
{
    oal_uint32 ul_ret;

    ul_ret = frw_ipc_exit();
    if (OAL_SUCC != ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_FRW, "{frw event deploy exit fail.}");
        return ul_ret;
    }

    /* TBD */

    /* �¼�����ģ�����ݽṹж�� */

    /* �����¼�����ģ��ӿڣ�ע���¼�����ӿں��� */

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : frw_event_deploy_pipeline
 ��������  : �ڲ��������¼�����ӿڣ��ҽӵ��¼�����ģ���У�����PIPELINE����
 �������  : pst_mem_event: �¼��ڴ��ָ��
 �������  : en_deploy: FRW_EVENT_DEPLOY_IPC-���¼���ҪIPC
                        FRW_EVENT_DEPLOY_POST-���¼���Ҫ�����
 �� �� ֵ  : OAL_SUCC-�ɹ�; ����-ʧ��
 ���ú���  : �¼��ַ�����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  frw_event_deploy_pipeline(frw_ipc_msg_mem_stru *pst_ipc_mem_msg,
                                              frw_event_deploy_enum_uint8 *en_deploy_result)
{
    frw_event_hdr_stru *pst_event_hdr;

    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_ipc_mem_msg) || (OAL_PTR_NULL == en_deploy_result))
    {
        OAM_ERROR_LOG2(0, OAM_SF_FRW, "{frw_event_deploy_pipeline: pst_ipc_mem_msg/en_deploy_result null ptr err:%d, %d}", pst_ipc_mem_msg, en_deploy_result);
        return OAL_ERR_CODE_PTR_NULL;
    }

    pst_event_hdr = (frw_event_hdr_stru *)pst_ipc_mem_msg->puc_data;

    if (FRW_EVENT_PIPELINE_STAGE_0 == pst_event_hdr->en_pipeline)
    {
        (*en_deploy_result) = FRW_EVENT_DEPLOY_NON_IPC;
    }
    else
    {
        (*en_deploy_result) = FRW_EVENT_DEPLOY_IPC;

        frw_ipc_send(pst_ipc_mem_msg);
    }

    return OAL_SUCC;
}

#if 0
/*****************************************************************************
 �� �� ��  : frw_event_deploy_owner
 ��������  : �ڲ��������¼�����ӿڣ��ҽӵ��¼�����ģ���У�����CHIP, DEVICE, VAP����
 �������  : pst_mem_event: �¼��ڴ��ָ��
 �������  : en_deploy: FRW_EVENT_DEPLOY_IPC-���¼���ҪIPC
                        FRW_EVENT_DEPLOY_POST-���¼���Ҫ�����
 �� �� ֵ  : OAL_SUCC-�ɹ�; ����-ʧ��
 ���ú���  : �¼��ַ�����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_deploy_owner(frw_ipc_msg_mem_stru *pst_ipc_mem_msg,
                                            frw_event_deploy_enum_uint8 *en_deploy_result)
{
    if ((OAL_PTR_NULL == pst_ipc_mem_msg) || (OAL_PTR_NULL == en_deploy_result))
    {
        FRW_ERR_LOG2(0, "frw_event_deploy_owner: pst_ipc_mem_msg/en_deploy_result null ptr err:", pst_ipc_mem_msg, en_deploy_result);
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* TBD */

    /* 1. ��ȡ�¼�payload�е�chip id, device id��vap id */

    /* 2. ��ȡ��ǰVAP���¼�������ԣ������ݲ��Խ��в��� */

    /* 3. ����ͳ����������CHIP, DEVICE, VAP�ֱ����ͳ�� */

    (*en_deploy_result) = FRW_EVENT_DEPLOY_IPC;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_deploy_set_affinity_device
 ��������  : ����ӿڣ�chip�׺�����
 �������  : uc_device_id-�豸ID
             ul_core_mask-CPU����
 �������  : ��
 �� �� ֵ  : OAL_SUCC-�ɹ�; ����-ʧ��
 ���ú���  : device����ʱ����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_deploy_set_affinity_device(oal_uint8 uc_device_id,
                                                            oal_cpumask ul_core_mask)
{
    /* TBD */

    /* 1. ��鵱ǰ��device��������ʽ����������chip�Ĳ���ʽ�Ƿ��ͻ: */
    /* ���chip�Ĳ��𲻴��ڣ����ʾ����ͻ,������2��; */
    /* ���chip��coremask����device������coremask���Ͳ���ͻ,������2��; �����ͻ������ʧ�� */

    /* 2. ��鵱ǰ��device��������ʽ����������vap�Ĳ���ʽ�Ƿ��ͻ:*/
    /* �������vap�Ĳ��𲻴��ڣ����ʾ����ͻ,������3��; */
    /* ���device������coremask������������ĳ��vap��coremask���ͳ�ͻ������ʧ��;����������3��; */

    /* 3. ����ͻ�����յ�ǰ�����Ĳ���ʽ���� */
    /* �����device���»�����û�в����VAP����ͳһ����device�����Ĳ���ʽ���в��� */

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_deploy_set_affinity_vap
 ��������  : ����ӿڣ�chip�׺�����
 �������  : uc_vap_id-vap ID
             ul_core_mask-CPU����
 �������  : ��
 �� �� ֵ  : OAL_SUCC-�ɹ�; ����-ʧ��
 ���ú���  : VAP����ʱ����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_deploy_set_affinity_vap(oal_uint8 uc_vap_id,
                                                        oal_cpumask ul_core_mask)
{
    /* TBD */

    /* 1. ��鵱ǰ��vap��������ʽ����������device�Ĳ���ʽ�Ƿ��ͻ: */
    /* ���device�Ĳ��𲻴��ڣ����ʾ����ͻ��������2��; */
    /* ���device��coremask����vap������coremask���Ͳ���ͻ��������3��; �����ͻ������ʧ�� */

    /* 2. ��鵱ǰ��vap��������ʽ����������chip�Ĳ���ʽ�Ƿ��ͻ: */
    /* ���chip�Ĳ��𲻴��ڣ����ʾ����ͻ��������3��; */
    /* ���chip��coremask����vap������coremask���Ͳ���ͻ��������3��; �����ͻ������ʧ�� */

    /* 3. ����ͻ�����յ�ǰ�����Ĳ���ʽ���� */

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : frw_event_deploy_set_affinity_chip
 ��������  : ����ӿڣ�chip�׺�����
 �������  : uc_chip_id-chip id
             ul_core_mask-CPU����
 �������  : ��
 �� �� ֵ  : OAL_SUCC-�ɹ�; ����-ʧ��
 ���ú���  : CHIP����ʱ����
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��18��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  frw_event_deploy_set_affinity_chip(oal_uint8 uc_chip_id,
                                                         oal_cpumask ul_core_mask)
{
    /* TBD */

    /* 1. ��鵱ǰ��chip��������ʽ����������device�Ĳ���ʽ�Ƿ��ͻ:*/
    /* �������device�Ĳ��𲻴��ڣ����ʾ����ͻ��������2��; */
    /* ���chip������coremask������������ĳ��device��coremask���ͳ�ͻ������ʧ��; ����������3�� */

    /* 2. ��鵱ǰ��chip��������ʽ����������vap�Ĳ���ʽ�Ƿ��ͻ:*/
    /* �������vap�Ĳ��𲻴��ڣ����ʾ����ͻ��������3��; */
    /* ���chip������coremask������������ĳ��vap��coremask���ͳ�ͻ������ʧ�ܣ�����ִ�е�3�� */

    /* 3. ����ͻ�����յ�ǰ�����Ĳ���ʽ����: */
    /* �����CHIP���»�����û�в����DEVICE��VAP����ͳһ����CHIP�����Ĳ���ʽ���в��� */

    return OAL_SUCC;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

