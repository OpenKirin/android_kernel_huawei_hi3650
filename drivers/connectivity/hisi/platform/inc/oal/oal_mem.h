/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_mem.h
  �� �� ��   : ����
  ��    ��   : zhangheng
  ��������   : 2012��9��19��
  ����޸�   :
  ��������   : oal_mem.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��19��
    ��    ��   : zhangheng
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_MEM_H__
#define __OAL_MEM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "platform_spec.h"
#include "oal_cache.h"
#include "oal_list.h"
#include "oal_schedule.h"
#include "oal_net.h"
#include "oal_util.h"
#include "arch/oal_mem.h"

#if ((_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE) && (_PRE_OS_VERSION == _PRE_OS_VERSION_LINUX))
#include <linux/kallsyms.h>
#endif
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define OAL_MEM_NETBUF_ALLOC(_uc_out_subpool_id,_us_len,_uc_netbuf_priority) \
    oal_netbuf_alloc(_us_len,0, WLAN_MEM_NETBUF_ALIGN)
#ifdef _PRE_DEBUG_MODE
#define OAL_MEM_NETBUF_TRACE(_pst_netbuf, _uc_lock)
#else
#define OAL_MEM_NETBUF_TRACE(_pst_netbuf, _uc_lock)
#endif

/*Local Mem ���нӿڵ� _uc_lock ����������Ч 2016/8/18*/
/* ��netbuf�ڴ����������ڴ�صĶ����ṩ�ӿ� host��device���ýӿ� */
#define OAL_MEM_ALLOC(_en_pool_id, _us_len, _uc_lock) \
    oal_mem_alloc(THIS_FILE_ID, __LINE__, _en_pool_id, _us_len, _uc_lock)
#define OAL_MEM_FREE(_p_data, _uc_lock) \
    oal_mem_free(THIS_FILE_ID, __LINE__, _p_data, _uc_lock)

#define OAL_MEM_FREE_ARRAY(_p_data, _num) \
    oal_mem_free_array(THIS_FILE_ID, __LINE__, _p_data, _num)

#define OAL_MEM_INCR_USER(_pst_mem, _uc_lock) \
    oal_mem_incr_user(THIS_FILE_ID, __LINE__, _pst_mem, _uc_lock)

#define OAL_MEM_ALLOC_ENHANCED(_en_pool_id, _us_len, _uc_lock) \
    oal_mem_alloc_enhanced(THIS_FILE_ID, __LINE__, _en_pool_id, _us_len, _uc_lock)

#define OAL_MEM_FREE_ENHANCED(_pst_mem, _uc_lock) \
    oal_mem_free_enhanced(THIS_FILE_ID, __LINE__, _pst_mem, _uc_lock)

/* host����ڴ���Ϣ�ӿ� */
#define OAL_MEM_INFO_PRINT(_pool_id)

#ifdef _PRE_DEBUG_MODE
#define OAL_MEM_TRACE(_p_data, _uc_lock) \
    oal_mem_trace(THIS_FILE_ID, __LINE__, _p_data, _uc_lock)

#define OAL_MEM_TRACE_ENHANCED(_pst_mem, _uc_lock) \
    oal_mem_trace_enhanced(THIS_FILE_ID, __LINE__, _pst_mem, _uc_lock)
#else
#define OAL_MEM_TRACE(_p_data, _uc_lock)
#define OAL_MEM_TRACE_ENHANCED(_pst_mem, _uc_lock)
#endif

/* ����enhanced���͵�����ӿ����ͷŽӿڣ�ÿһ���ڴ�鶼����һ��4�ֽڵ�ͷ���� */
/* ����ָ���ڴ�����ṹ��oal_mem_struc�������ڴ��Ľṹ������ʾ��           */
/*                                                                           */
/* +-------------------+------------------------------------------+---------+ */
/* | oal_mem_stru addr |                    payload               | dog tag | */
/* +-------------------+------------------------------------------+---------+ */
/* |      4/8 byte       |                                          | 4 byte  | */
/* +-------------------+------------------------------------------+---------+ */
#define OAL_DOG_TAG    0x5b3a293e    /* ���ƣ����ڼ���ڴ�Խ�� */

#ifdef _PRE_DEBUG_MODE
#ifdef CONFIG_ARM64
#define OAL_DOG_TAG_SIZE             8   /* ���ƴ�С(8�ֽ�) */
#else
#define OAL_DOG_TAG_SIZE             4   /* ���ƴ�С(4�ֽ�) */
#endif
#define OAL_NETBUF_MAINTAINS_SIZE    24  /* alloc_file_id(4B) + alloc_line_num(4B) + alloc_timestamp(4B) + */
                                         /* trace_file_id(4B) + trace_line_num(4B) + trace_timestamp(4B)   */
#else
#define OAL_DOG_TAG_SIZE             0
#define OAL_NETBUF_MAINTAINS_SIZE    0
#endif

#define OAL_NETBUF_DEFAULT_HEADROOM  256 /*����netbufʱ��Ĭ�ϵ�headroom*/
#define OAL_MAX_TX_DSCR_CNT_IN_LIST  100
#define OAL_TX_DSCR_ITEM_NUM         200
#define OAL_TX_DSCR_RCD_TAIL_CNT     20

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
#if(_PRE_OS_VERSION == _PRE_OS_VERSION_LINUX)
#define OAL_MEM_SPRINT_SYMBOL_SIZE    KSYM_SYMBOL_LEN
#else
#define OAL_MEM_SPRINT_SYMBOL_SIZE    1
#endif
#endif
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
  ö����  : oal_mem_pool_id_enum_uint8
  Э����:
  ö��˵��: HOST���ڴ��ID
*****************************************************************************/
typedef enum
{
    OAL_MEM_POOL_ID_EVENT = 0,              /* �¼��ڴ�� */
    OAL_MEM_POOL_ID_SHARED_DATA_PKT,        /* ��������֡�ڴ�� */
    OAL_MEM_POOL_ID_SHARED_MGMT_PKT,        /* �������֡�ڴ�� */
    OAL_MEM_POOL_ID_LOCAL,                  /* ���ر����ڴ��  */
    OAL_MEM_POOL_ID_MIB,                    /* MIB�ڴ�� */
    OAL_MEM_POOL_ID_SHARED_DSCR,            /* �����������ڴ�� */

    //OAL_MEM_POOL_ID_NETBUF,                 /* netbuf�ڴ�� */
    OAL_MEM_POOL_ID_SDT_NETBUF,             /* SDT netbuf�ڴ�� */

    OAL_MEM_POOL_ID_BUTT
}oal_mem_pool_id_enum;
typedef oal_uint8 oal_mem_pool_id_enum_uint8;
/*****************************************************************************
  ö����  : oal_netbuf_priority_enum_uint8
  Э����:
  ö��˵��: netbuf���ȼ�
*****************************************************************************/
typedef enum
{
    OAL_NETBUF_PRIORITY_LOW     = 0,  //������ȼ�,���ܿ������
    OAL_NETBUF_PRIORITY_MID     = 1,  //�м����ȼ������Կ�����룬�����������������NƬ
    OAL_NETBUF_PRIORITY_HIGH    = 2,  //������ȼ������Կ�����룬�ҿ��������������NƬ

    OAL_NETBUF_PRIORITY_BUTT
}oal_netbuf_priority_enum;
typedef oal_uint8 oal_netbuf_priority_enum_uint8;

/*****************************************************************************
  ö����  : oal_netbuf_id_enum_uint8
  Э����:
  ö��˵��: �����ṩnetbuf�ڴ��ID
*****************************************************************************/
typedef enum
{
    OAL_NORMAL_NETBUF = 0,                /* ������֡����֡�ڴ�� */
    OAL_MGMT_NETBUF   = 1,                /* ����֡�ڴ�� */
    OAL_OAM_NETBUF    = 2,                /* SDT�ڴ�� */

    OAL_NETBUF_POOL_ID_BUTT
}oal_netbuf_id_enum;
typedef oal_uint8 oal_netbuf_id_enum_uint8;

#define OAL_MEM_POOL_ID_ALG_LOCAL  OAL_MEM_POOL_ID_LOCAL
#define OAL_MEM_POOL_ID_HI_LOCAL   OAL_MEM_POOL_ID_LOCAL

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
  7 STRUCT����
*****************************************************************************/
typedef struct
{
    oal_uint32  (* p_mempool_info_func)(oal_uint8 en_pool_id,
                                        oal_uint16 us_mem_total_cnt,
                                        oal_uint16 us_mem_used_cnt,
                                        oal_uint8  uc_subpool_id,
                                        oal_uint16 us_total_cnt,
                                        oal_uint16 us_free_cnt);
    oal_uint32  (* p_memblock_info_func)(oal_uint8 *puc_origin_data,
                                         oal_uint8                   uc_user_cnt,
                                         oal_mem_pool_id_enum_uint8  en_pool_id,
                                         oal_uint8                   uc_subpool_id,
                                         oal_uint16                  us_len,
                                         oal_uint32                  ul_alloc_file_id,
                                         oal_uint32                  ul_alloc_line_num);

}oal_mempool_info_to_sdt_stru;

/*****************************************************************************
  �ṹ��  : oal_mem_netbuf_info_stru
  �ṹ˵��: netbuf�ڴ��ά��ṹ��
*****************************************************************************/
typedef struct
{
    oal_uint32   ul_dog_tag;            /* ���ƣ������ڴ�дԽ���� */
    oal_uint32   ul_alloc_file_id;      /* ����netbuf�ڴ�ʱ���ļ�ID */
    oal_uint32   ul_alloc_line_num;     /* ����netbuf�ڴ�ʱ���к� */
    oal_uint32   ul_alloc_time_stamp;   /* ����netbuf�ڴ�ʱ��ʱ��� */
    oal_uint32   ul_trace_file_id;      /* netbuf�ڴ��ڹؼ�·���ϵ��ļ�ID */
    oal_uint32   ul_trace_line_num;     /* netbuf�ڴ��ڹؼ�·���ϵ��к� */
    oal_uint32   ul_trace_time_stamp;   /* netbuf�ڴ��ڹؼ�·���ϵ�ʱ��� */
}oal_mem_netbuf_info_stru;

/*****************************************************************************
  �ṹ��  : oal_mem_stru
  �ṹ˵��: �ڴ��ṹ��
*****************************************************************************/
struct oal_mem_stru_tag
{
    oal_uint8                  *puc_data;                                   /* ������ݵ�ָ�� */
    oal_uint8                  *puc_origin_data;                            /* ��¼���ݵ�ԭʼָ�� */
#if 0
    oal_uint8                   uc_user_cnt;                                /* ���뱾�ڴ����û����� */
    oal_mem_state_enum_uint8    en_mem_state_flag;                          /* �ڴ��״̬ */
    oal_mem_pool_id_enum_uint8  en_pool_id;                                 /* ���ڴ�������һ���ڴ�� */
    oal_uint8                   uc_subpool_id;                              /* ���ڴ���������һ�����ڴ�� */
    oal_uint16                  us_len;                                     /* �ڴ��ĳ��� */
    oal_uint8                   auc_resv[2];
    oal_dlist_head_stru         st_list;
#endif
    oal_uint16                  us_len;                                     /* �ڴ��ĳ��� */
    oal_uint8                   uc_user_cnt       :4;                       /* ���뱾�ڴ����û����� */
    oal_mem_state_enum_uint8    en_mem_state_flag :4;                       /* �ڴ��״̬ */
    oal_mem_pool_id_enum_uint8  en_pool_id        :4;                       /* ���ڴ�������һ���ڴ�� */
    oal_uint8                   uc_subpool_id     :4;                       /* ���ڴ���������һ�����ڴ�� */

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
    oal_ulong                  ul_return_addr;                              /* alloc�ڴ�ĺ�����ַ ���� */
#endif


    /* �ڴ������Ϣ */
#ifdef _PRE_DEBUG_MODE
    oal_uint32                  ul_alloc_core_id[WLAN_MEM_MAX_USERS_NUM];    /* �����ڴ�ʱ���ں�ID */
    oal_uint32                  ul_alloc_file_id[WLAN_MEM_MAX_USERS_NUM];    /* �����ڴ�ʱ���ļ�ID */
    oal_uint32                  ul_alloc_line_num[WLAN_MEM_MAX_USERS_NUM];   /* �����ڴ�ʱ���к� */
    oal_uint32                  ul_alloc_time_stamp[WLAN_MEM_MAX_USERS_NUM]; /* �����ڴ�ʱ��ʱ��� */
    oal_uint32                  ul_trace_file_id;                            /* �ڴ��ڹؼ�·���ϵ��ļ�ID */
    oal_uint32                  ul_trace_line_num;                           /* �ڴ��ڹؼ�·���ϵ��к� */
    oal_uint32                  ul_trace_time_stamp;                         /* �ڴ��ڹؼ�·���ϵ�ʱ��� */
#endif
}oal_cacheline_aligned;
typedef struct oal_mem_stru_tag  oal_mem_stru;


/*****************************************************************************
  �ṹ��  : oal_mem_subpool_stru
  �ṹ˵��: ���ڴ�ؽṹ��
*****************************************************************************/
typedef struct
{
    oal_spin_lock_stru    st_spinlock;
    oal_uint16            us_len;             /* �����ڴ�ص��ڴ�鳤�� */
    oal_uint16            us_free_cnt;        /* �����ڴ�ؿ����ڴ���� */

    /* ��¼oal_mem_stru�����ڴ��������ջ��Ԫ�أ�������Ϊoal_mem_struָ�� */
    void                **ppst_free_stack;

    oal_uint16            us_total_cnt;       /* �����ڴ���ڴ������ */
    oal_uint8             auc_resv[2];
} oal_mem_subpool_stru;

/*****************************************************************************
  �ṹ��  : oal_mem_pool_stru
  �ṹ˵��: �ڴ�ؽṹ��
*****************************************************************************/
typedef struct
{
    oal_uint16              us_max_byte_len;        /* ���ڴ�ؿɷ����ڴ����󳤶� */
    oal_uint8               uc_subpool_cnt;         /* ���ڴ��һ���ж������ڴ�� */
    oal_uint8               uc_resv;
    /* ���ڴ������������ */
    oal_mem_subpool_stru    ast_subpool_table[WLAN_MEM_MAX_SUBPOOL_NUM];

    oal_uint16              us_mem_used_cnt;        /* ���ڴ�������ڴ�� */
    oal_uint16              us_mem_total_cnt;       /* ���ڴ��һ���ж����ڴ�� */
    oal_mem_stru           *pst_mem_start_addr;
}oal_mem_pool_stru;

/*****************************************************************************
  �ṹ��  : oal_mem_subpool_cfg_stru
  �ṹ˵��: ���ڴ�����ýṹ��
*****************************************************************************/
typedef struct
{
    oal_uint16  us_size;    /* �����ڴ���ڴ���С */
    oal_uint16  us_cnt;     /* �����ڴ���ڴ����� */
}oal_mem_subpool_cfg_stru;

/*****************************************************************************
  �ṹ��  : oal_mem_pool_cfg_stru
  �ṹ˵��: �ڴ�����ýṹ��
*****************************************************************************/
typedef struct
{
    oal_mem_pool_id_enum_uint8          en_pool_id;      /* �ڴ��ID */
    oal_uint8                           uc_subpool_cnt;  /* ���ڴ�����ڴ�ظ��� */

    oal_uint8                           auc_resv[2];

    /* ָ��ÿһ���ڴ�ؾ���������Ϣ */
    oal_mem_subpool_cfg_stru  *pst_subpool_cfg_info;
}oal_mem_pool_cfg_stru;

#ifdef _PRE_DEBUG_MODE
typedef struct
{
    oal_uint    ul_released_addr;
    oal_uint32  ul_release_file_id;
    oal_uint32  ul_release_line_num;
    oal_uint32  ul_release_ts;
    oal_uint32  ul_tx_dscr_in_up_intr;          /*�ϰ벿�������������ַ*/
    oal_uint32  ul_up_intr_ts;                  /*�ϰ벿�����ʱ��*/
    oal_uint32  ul_tx_dscr_in_dn_intr;          /*�°벿�������������ַ*/
    oal_uint32  ul_dn_intr_ts;                  /*�°벿�����ʱ��*/
    oal_uint32  ul_tx_dscr_in_q[OAL_MAX_TX_DSCR_CNT_IN_LIST];//���dev���Ͷ����е�������ַ
    oal_uint8   uc_mpdu_num;                    /*mpdu��Ŀ*/
    oal_uint8   uc_q_num;                       /*����*/
    oal_uint16  bit_dscr_is_overflow  : 1;      /*ul_tx_dscr_in_q�����¼�����������־*/
    oal_uint16  bit_resv              : 15;
}oal_mempool_tx_dscr_info;

typedef struct
{
    oal_uint     ul_tx_dscr_addr[WLAN_MEM_SHARED_TX_DSCR_CNT1 + WLAN_MEM_SHARED_TX_DSCR_CNT2];
    oal_mempool_tx_dscr_info ast_tx_dscr_info[OAL_TX_DSCR_ITEM_NUM];
    oal_uint16   us_tx_dscr_cnt;
    oal_uint16   us_released_tx_dscr_cnt;   /*ָʾ�����������ͷ�ͳ�Ƶ�λ��*/
    oal_uint16   us_tx_dscr_cnt_up;         /*ָʾ�ϰ벿������ͳ�Ƶ�λ��*/
    oal_uint16   us_tx_dscr_cnt_dn;         /*ָʾ�ϰ벿������ͳ�Ƶ�λ��*/
    oal_uint16   us_rcd_rls_stop_flag;
    oal_uint16   us_rsv;
}oal_mempool_tx_dscr_addr;
#endif


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/
extern oal_void* oal_mem_alloc(
                       oal_uint32                    ul_file_id,
                       oal_uint32                    ul_line_num,
                       oal_mem_pool_id_enum_uint8    en_pool_id,
                       oal_uint16                    us_len,
                       oal_uint8                     uc_lock);
extern oal_uint32  oal_mem_free(oal_uint32 ul_file_id, oal_uint32 ul_line_num, oal_void *pst_mem, oal_uint8 uc_lock);

extern oal_uint32  oal_mem_free_array(
                oal_uint32    ul_file_id,
                oal_uint32    ul_line_num,
                oal_void     *p_data,
                oal_uint8     uc_mem_num);

extern oal_mem_stru* oal_mem_alloc_enhanced(
                oal_uint32                    ul_file_id,
                oal_uint32                    ul_line_num,
                oal_mem_pool_id_enum_uint8    en_pool_id,
                oal_uint16                    us_len,
                oal_uint8                     uc_lock);
extern oal_uint32  oal_mem_free_enhanced(oal_uint32 ul_file_id, oal_uint32 ul_line_num, oal_mem_stru *p_data, oal_uint8 uc_lock);
extern oal_uint32  oal_mem_init_pool(oal_void);
extern oal_uint32  oal_mem_exit(oal_void);
extern oal_uint32  oal_mem_incr_user(
                       oal_uint32      ul_file_id,
                       oal_uint32      ul_line_num,
                       oal_mem_stru   *pst_mem,
                       oal_uint8       uc_lock);
extern oal_void  oal_mem_info(oal_mem_pool_id_enum_uint8 en_pool_id);
extern oal_void  oal_mem_leak(oal_mem_pool_id_enum_uint8 en_pool_id);

extern oal_void  oal_mem_start_stat(oal_void);
extern oal_uint32  oal_mem_end_stat(oal_void);

extern oal_uint32  oal_mem_trace_enhanced(oal_uint32      ul_file_id,
                                          oal_uint32      ul_line_num,
                                          oal_mem_stru   *pst_mem,
                                          oal_uint8       uc_lock);
extern oal_uint32  oal_mem_trace(oal_uint32    ul_file_id,
                                 oal_uint32    ul_line_num,
                                 oal_void     *p_data,
                                 oal_uint8     uc_lock);

#ifdef _PRE_DEBUG_MODE
extern oal_mempool_tx_dscr_addr* oal_mem_get_tx_dscr_addr(oal_void);
extern oal_void oal_mem_stop_rcd_rls(oal_void);
extern oal_uint16 oal_mem_get_stop_flag(oal_void);
#endif
/* device ����ϵͳ�� host��ĺ������ */
extern oal_mem_pool_stru* oal_mem_get_pool(oal_mem_pool_id_enum_uint8 en_pool_id);

extern oal_mem_pool_cfg_stru* oal_mem_get_pool_cfg_table(oal_mem_pool_id_enum_uint8 en_pool_id);
extern oal_netbuf_stru* oal_mem_sdt_netbuf_alloc(oal_uint16 us_len, oal_uint8 uc_lock);
extern oal_uint32  oal_mem_sdt_netbuf_free(oal_netbuf_stru *pst_netbuf, oal_uint8 uc_lock);
extern oal_netbuf_stru* oal_netbuf_duplicate(oal_netbuf_stru* pst_src_netbuf,
											oal_uint8 uc_out_subpool_id,
											oal_uint32 ul_add_head_room,
											oal_uint32 ul_add_tail_room);

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_void oal_mem_print_normal_pool_info(oal_mem_pool_id_enum_uint8 en_pool_id);
extern oal_void oal_mem_print_pool_info(oal_void);
extern oal_ulong oal_get_func_return_address(oal_void);
extern oal_void oal_mem_print_funcname(oal_ulong func_addr);
#endif

#define oal_netbuf_duplicate_normal(pst_src_netbuf,ul_add_head_room,ul_add_tail_room) \
                    oal_netbuf_duplicate(pst_src_netbuf,OAL_NORMAL_NETBUF,ul_add_head_room,ul_add_tail_room)

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_mm.h */

