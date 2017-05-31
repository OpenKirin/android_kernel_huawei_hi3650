/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_schedule.h
  �� �� ��   : ����
  ��    ��   : t00231215
  ��������   : 2012��11��29��
  ����޸�   :
  ��������   : oal_types.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��11��29��
    ��    ��   : t00231215
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_SCHEDULE_H__
#define __OAL_SCHEDULE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "oal_types.h"
#include "oal_hardware.h"
#include "oal_mm.h"
#include "arch/oal_schedule.h"


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if (_PRE_CHIP_BITS_MIPS32 == _PRE_CHIP_BITS)
/* 32λ�Ĵ�����󳤶� */
#define OAL_TIME_US_MAX_LEN  (0xFFFFFFFF - 1)

#elif (_PRE_CHIP_BITS_MIPS64 == _PRE_CHIP_BITS)
/* 64λ�Ĵ�����󳤶� */
#define OAL_TIME_US_MAX_LEN  (0xFFFFFFFFFFFFFFFF - 1)

#endif

#define oal_sys_wdt_start(mode,msec)
#define oal_sys_wdt_start_int(msec)
#define oal_sys_wdt_start_noint(msec)
#define oal_sys_wdt_stop()
#define oal_sys_wdt_feed()

#define oal_sys_bus_idle()

typedef enum
{
    OAL_DFT_TRACE_OTHER = 0x0,
    OAL_DFT_TRACE_SUCC   ,
    OAL_DFT_TRACE_FAIL   ,/*> fail while dump the key_info to kernel*/
    OAL_DFT_TRACE_EXCEP  , /*exception*/
    OAL_DFT_TRACE_BUTT   ,
}oal_dft_type;

#ifdef _PRE_OAL_FEATURE_KEY_PROCESS_TRACE
#include "oal_list.h"
#include <linux/rtc.h>
typedef struct _oal_dft_trace_item_
{
    oal_list_entry_stru list;
    char* name;
    oal_uint16  dft_type;
    oal_uint16  trace_flag;/*add the the list*/
    oal_uint32  trace_count;
    struct timeval  first_timestamp;/*first keyinfo timestamp*/
    struct timeval  last_timestamp;/*last keyinfo timestamp*/
}oal_dft_trace_item;
//extern oal_spin_lock_stru;
extern oal_spin_lock_stru g_dft_head_lock;
extern oal_list_head_stru g_dft_head;
extern oal_int32 oal_dft_init(oal_void);
extern oal_void oal_dft_exit(oal_void);
extern oal_void oal_dft_print_error_key_info(oal_void);
extern oal_void oal_dft_print_all_key_info(oal_void);

/*�ؼ����̷���ʱ����¼���м�������������*/
#define DECLARE_DFT_TRACE_KEY_INFO(dname,dtype)\
        do\
        {\
            oal_ulong flags;\
            OAL_STATIC oal_dft_trace_item st_dft_item = {{0},NULL,0,0,0,{0},{0}};\
            oal_spin_lock_irq_save(&g_dft_head_lock, &flags);\
            if(!st_dft_item.trace_flag)\
            {\
                oal_list_add(&st_dft_item.list, &g_dft_head);\
                st_dft_item.name = dname;\
                st_dft_item.dft_type = dtype;\
                st_dft_item.trace_flag =1;\
            }\
            st_dft_item.trace_count++;\
            oal_spin_unlock_irq_restore(&g_dft_head_lock, &flags);\
            if((!st_dft_item.first_timestamp.tv_sec) && (!st_dft_item.first_timestamp.tv_usec))\
            {\
                do_gettimeofday(&st_dft_item.first_timestamp);\
            }\
            else\
            {\
                do_gettimeofday(&st_dft_item.last_timestamp);\
            }\
            if(OAL_UNLIKELY(dtype >= OAL_DFT_TRACE_FAIL))\
            {\
                printk(KERN_ERR "[E]key_info:%s happened[%u]!\n",dname,st_dft_item.trace_count);\
                oal_dft_print_error_key_info();\
            }\
        }while(0)
#else
#define DECLARE_DFT_TRACE_KEY_INFO(dname,dtype)
#endif

typedef struct _oal_wakelock_stru_
{
#ifdef CONFIG_WAKELOCK
    struct wake_lock        st_wakelock;        //wakelock��
    oal_spin_lock_stru      lock;    //wakelock������spinlock��
#endif
    oal_ulong               lock_count;         //����wakelock���Ĵ���
    oal_ulong			    locked_addr;/*the locked address*/
}oal_wakelock_stru;


/* ��ȡ��_ul_start��_ul_end��ʱ��� */
#define OAL_TIME_GET_RUNTIME(_ul_start, _ul_end) \
    (((_ul_start) > (_ul_end))?(OAL_TIME_CALC_RUNTIME((_ul_start), (_ul_end))):((_ul_end) - (_ul_start)))

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
  7 STRUCT����
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
#ifdef _PRE_CONFIG_HISI_CONN_SOFTWDFT
extern oal_int32 oal_softwdt_init(oal_void);
extern oal_void oal_softwdt_exit(oal_void);
#else
OAL_STATIC OAL_INLINE oal_int32 oal_softwdt_init(oal_void)
{
    return OAL_SUCC;
}
OAL_STATIC OAL_INLINE oal_void oal_softwdt_exit(oal_void)
{
    return;
}
#endif

OAL_STATIC OAL_INLINE oal_void oal_wake_lock_init(oal_wakelock_stru *pst_wakelock,char* name)
{
#ifdef CONFIG_WAKELOCK
    oal_memset((oal_void*)pst_wakelock,0,sizeof(oal_wakelock_stru));

    wake_lock_init(&pst_wakelock->st_wakelock, WAKE_LOCK_SUSPEND, name ? name:"wake_lock_null");
    oal_spin_lock_init(&pst_wakelock->lock);
    pst_wakelock->lock_count = 0;
    pst_wakelock->locked_addr = 0;
#endif
}

OAL_STATIC OAL_INLINE oal_void oal_wake_lock_exit(oal_wakelock_stru *pst_wakelock)
{
#ifdef CONFIG_WAKELOCK
    wake_lock_destroy(&pst_wakelock->st_wakelock);
#endif
}

OAL_STATIC OAL_INLINE void oal_wake_lock(oal_wakelock_stru *pst_wakelock)
{
#ifdef CONFIG_WAKELOCK
    oal_ulong ul_flags;

    oal_spin_lock_irq_save(&pst_wakelock->lock, &ul_flags);
    if(!pst_wakelock->lock_count)
    {
        wake_lock(&pst_wakelock->st_wakelock);
        pst_wakelock->locked_addr = (oal_ulong)_RET_IP_;
    }
    pst_wakelock->lock_count++;
    oal_spin_unlock_irq_restore(&pst_wakelock->lock, &ul_flags);
#endif
}

OAL_STATIC OAL_INLINE  void oal_wake_unlock(oal_wakelock_stru *pst_wakelock)
{
#ifdef CONFIG_WAKELOCK
    oal_ulong ul_flags;

    oal_spin_lock_irq_save(&pst_wakelock->lock, &ul_flags);
    if(pst_wakelock->lock_count)
    {
        pst_wakelock->lock_count--;
        if(!pst_wakelock->lock_count)
        {
            wake_unlock(&pst_wakelock->st_wakelock);
            pst_wakelock->locked_addr = (oal_ulong)0x0;
        }
    }
    oal_spin_unlock_irq_restore(&pst_wakelock->lock, &ul_flags);
#endif
}

OAL_STATIC OAL_INLINE oal_int32 oal_wakelock_active(oal_wakelock_stru *pst_wakelock)
{
#ifdef CONFIG_WAKELOCK
    return wake_lock_active(&pst_wakelock->st_wakelock);
#else
    return 0;
#endif
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_schedule.h */
