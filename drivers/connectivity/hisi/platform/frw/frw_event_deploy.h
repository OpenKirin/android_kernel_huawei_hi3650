/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : frw_event_deploy.h
  �� �� ��   : ����
  ��    ��   : c00178899
  ��������   : 2012��10��16��
  ����޸�   :
  ��������   : frw_event_deploy.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��10��16��
    ��    ��   : c00178899
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __FRW_EVENT_DEPLOY_H__
#define __FRW_EVENT_DEPLOY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "frw_event_main.h"
#include "frw_ipc_msgqueue.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_FRW_EVENT_DEPLOY_H

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
typedef enum
{
    FRW_IPC_CORE_ID_MASTER   = 0,
    FRW_IPC_CORE_ID_SLAVE    = 1,

    FRW_IPC_CORE_NUM_BUTT
}frw_ipc_core_id_enum;
typedef oal_uint8 frw_ipc_core_id_enum_uint8;

typedef enum
{
    FRW_IPC_CORE_TYPE_MASTER   = 0,
    FRW_IPC_CORE_TYPE_SLAVE    = 1,

    FRW_IPC_CORE_TYPE_BUTT
}frw_ipc_core_type_enum;
typedef oal_uint8 frw_ipc_core_type_enum_uint8;

/* ״̬���壬�ж������Ŀ��ܸ��ģ������Ҫԭ�ӱ��� */
typedef enum
{
    FRW_IPC_CORE_STATE_INIT      = 0,
    FRW_IPC_CORE_STATE_CONNECTED = 1,
    FRW_IPC_CORE_STATE_RESET     = 2,
    FRW_IPC_CORE_STATE_EXIT      = 3,

    FRW_IPC_CORE_STATE_BUTT
}frw_ipc_core_state_enum;
typedef OAL_VOLATILE oal_uint8 frw_ipc_core_state_enum_uint8;

typedef enum
{
    FRW_IPC_MSG_TYPE_EVENT            = 0,  /* �ⲿ�¼� */
    FRW_IPC_MSG_TYPE_CONNECT_REQUEST  = 1,  /* IPC�������� */
    FRW_IPC_MSG_TYPE_CONNECT_RESPONSE = 2,  /* IPC������Ӧ */
    FRW_IPC_MSG_TYPE_CONFIG_REQUEST   = 3,  /* IPC�������� */
    FRW_IPC_MSG_TYPE_CONFIG_RESPONSE  = 4,  /* IPC������Ӧ */
    FRW_IPC_MSG_TYPE_ERROR_NOTICE     = 5,  /* IPC�쳣֪ͨ */
    FRW_IPC_MSG_TYPE_RESET_REQUEST    = 6,  /* IPC��λ���� */
    FRW_IPC_MSG_TYPE_RESET_RESPONSE   = 7,  /* IPC��λ��Ӧ */
    FRW_IPC_MSG_TYPE_OPEN_OAM         = 8,  /* IPC��ά�� */
    FRW_IPC_MSG_TYPE_CLOSE_OAM        = 9,  /* IPC�ر�ά�� */
    FRW_IPC_MSG_TYPE_EXIT_REQUEST     = 10, /* IPCж������ */
    FRW_IPC_MSG_TYPE_EXIT_RESPONSE    = 11, /* IPCж����Ӧ*/
    FRW_IPC_MSG_TYPE_TX_INT_ENABLE    = 12, /* IPC TX�жϿ��� */
    FRW_IPC_MSG_TYPE_TX_INT_DISENABLE = 13, /* IPC TX�жϹر� */

    FRW_IPC_MSG_TYPE_BUTT
}frw_ipc_msg_type_enum;
typedef oal_uint8 frw_ipc_msg_type_enum_uint8;

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ������к����� */
#define FRW_IPC_MAX_SEQ_NUMBER   (0xFFFF)

/* ��ȡ��Ϣ���� */
#define FRW_IPC_GET_MSG_QUEUE(_queue, _type)     (_queue = (FRW_IPC_CORE_TYPE_MASTER == _type) ? \
                                                           &g_st_queue_master_to_slave : \
                                                           &g_st_queue_slave_to_master)

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/* IPC�ڲ���Ϣ�ṹ�� */
typedef struct
{
    frw_ipc_msg_header_stru st_ipc_hdr;
    oal_uint8               auc_resv[2];
    oal_uint16              ul_length;   /* ���ݳ��� */
    oal_uint8               auc_data[4];
}frw_ipc_inter_msg_stru;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    frw_ipc_core_id_enum_uint8      en_cpuid;                       /* ����cpuid */
    frw_ipc_core_id_enum_uint8      en_target_cpuid;                /* Ŀ���ں�cpuid */
    frw_ipc_core_state_enum_uint8   en_states;                      /* �ڵ㵱ǰ״̬: ��ʼ��, ����, ��λ, �رյ�״̬ */
    frw_ipc_tx_ctrl_enum_uint8      en_tx_int_ctl;                  /* TX�жϿ��� */
    frw_ipc_core_type_enum_uint8    en_cpu_type;                    /* ��ǰCPU���ͣ������˻�Ӻ� */
    oal_uint8                       uc_resv[3];                     /* ���� */
    oal_uint16                      us_seq_num_rx_expect;           /* ������Ϣ�����к�,��ʼֵΪ0,�����һ���������յ����к� */
    oal_uint16                      us_seq_num_tx_expect;           /* ������Ϣ�����к�,��ʼֵΪ0,�����һ���������͵����к� */
    frw_ipc_msg_callback_stru       st_ipc_msg_callback;            /* �ص������� */
    oal_irq_dev_stru                st_irq_dev;                     /* �жϽṹ�� */
#ifdef _PRE_DEBUG_MODE
    frw_ipc_log_stru                st_log;                         /* ��־�ṹ�� */
#endif
}frw_ipc_node_stru;


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
 �� �� ��  : frw_ipc_get_core_type
 ��������  : ��ȡCPU����
 �������  : ��
 �������  : ��
 �� �� ֵ  : CPU����: master or slave
 ���ú���  : ��ģ��������Ҫ��ȡ��ǰCPU���͵Ĳ���
 ��������  : OAL���ȡCPUID�ĺ���

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE frw_ipc_core_type_enum frw_ipc_get_core_type(oal_void)
{
    if (FRW_IPC_CORE_ID_MASTER == OAL_GET_CORE_ID())
    {
        return FRW_IPC_CORE_TYPE_MASTER;
    }

    return FRW_IPC_CORE_TYPE_SLAVE;
}

/*****************************************************************************
 �� �� ��  : frw_ipc_get_header
 ��������  : ��ȡIPCͷ
 �������  : pst_ipc_mem_msg �� �¼��ڴ���ַ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��17��
    ��    ��   : c00178899
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint8 *frw_ipc_get_header(frw_ipc_msg_mem_stru *pst_ipc_mem_msg)
{
    pst_ipc_mem_msg->puc_data -= FRW_IPC_MSG_HEADER_LENGTH;
    return pst_ipc_mem_msg->puc_data;
}

extern oal_uint32  frw_event_deploy_init(oal_void);
extern oal_uint32  frw_event_deploy_exit(oal_void);


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of frw_event_deploy.h */
