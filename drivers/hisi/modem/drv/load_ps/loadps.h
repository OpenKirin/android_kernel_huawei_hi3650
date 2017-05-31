#ifndef __LOADPS_H__
#define __LOADPS_H__

#include <linux/semaphore.h>
#include <linux/wakelock.h>
#include "bsp_om.h"
#include "bsp_loadps.h"

/*loadpsģ��Ĵ�ӡ����*/
enum bsp_loadps_trace_level
{
    BSP_LOADPS_TRACE_INFO = 0,
    BSP_LOADPS_TRACE_WARNING,
    BSP_LOADPS_TRACE_ERROR
};

/* loadpsģ���״̬ */
enum bsp_loadps_init_enum
{
    EN_LOADPS_INIT_INVALID = 0,  /* δ��ʼ�� */
    EN_LOADPS_INIT_SUSPEND,		 /* A��suspend������ */
    EN_LOADPS_INIT_RESETING,     /* C������������ */
    EN_LOADPS_INIT_FINISH        /* ��ʼ������ */
};

/* ����״̬ */
enum bsp_loadps_state_en
{
    EN_LOADPS_IDLE = 0,      /* ������ */
    EN_LOADPS_DOING,         /* ���ڴ��� */
	EN_LOADPS_SUSPEND,         /* suspend״̬ */
    EN_LOADPS_DONE,           /* ������� */
    EN_LOADPS_NEEDSTOP        /* ����������λ��Ҫ��ֹ */
};

struct bsp_loadps_loadinfo_debug
{
    u32 ps_loadinfo_rat_mode;
    u32 ps_loadinfo_phy_loadaddress;
    u32 ps_loadinfo_total_size;
    u32 ps_loadinfo_result;

};
/*loadpsģ��ļ���ʱ��������ݽṹ*/
struct bsp_loadps_timestamp_debug
{
    u32 ps_callback_ms;
    u32 ps_task_wakeup_ms;
    u32 ps_load_image_success_ms;
    u32 ps_load_image_total_elapse_ms;

};
/* ������Ϣ */
struct bsp_loadps_main_stru
{
    enum bsp_loadps_init_enum  eInitFlag;
    struct task_struct      *taskid;
    loadps_msg              loadps_msg;
    struct semaphore        task_mutex;                /* �����ź��� */
    struct semaphore        suspend_mutex;                /* suspend�ź��� */
    struct wake_lock        wake_lock;
    u32                     opState;                /*����״̬*/
    /*��¼�����ؼ���ʱ�����Ϣ����Э��ջͬ�¶�λ�������ʱ��*/
    struct bsp_loadps_timestamp_debug timestamp_debug;
    struct bsp_loadps_loadinfo_debug  loadinfo_debug;
};

/*loadpsģ��Ķ�̬���Թ���*/
#define loadps_trace(trace_level, fmt, ...) do { \
        bsp_trace(trace_level, BSP_MODU_LOADPS,"loadps: " fmt "\n", ##__VA_ARGS__); \
} while (0)

#endif
