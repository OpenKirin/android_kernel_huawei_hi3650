
 
#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include <linux/sched.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/if.h>
#include <linux/kernel.h>
#include <linux/skbuff.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/wait.h>
#include <linux/types.h>
#include <linux/stat.h>
#include <linux/fcntl.h>
#include <linux/unistd.h>
#include <linux/signal.h>
#include <linux/time.h>

#include "mdrv.h"
#include "vos.h"
#include "TTFUtil.h"
#include "v_lib.h"

#if ((VOS_OS_VER == VOS_WIN32) || defined(__UT_CENTER__))
#include "Linuxstub.h"
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e534*/
/*lint -e767*/
#define    THIS_FILE_ID                    PS_FILE_ID_ACPU_VIEW_C
/*lint +e767*/


/******************************************************************************
   2 �ⲿ��������
******************************************************************************/
typedef unsigned int                ACPU_UINT32;
typedef signed int                  ACPU_INT32;
typedef unsigned short              ACPU_UINT16;
typedef int                         ACPU_INT;
typedef unsigned char               ACPU_UINT8;
typedef char                        ACPU_CHAR;
typedef void                        ACPU_VOID;
typedef ptrdiff_t                   ACPU_PTR;
typedef void (*FUNC_VOID)(void);

extern int task_switch_hook_add (FUNC_VOID switchHook);
extern void int_switch_hook_add(FUNC_VOID pHookFunc);
extern void int_switch_hook_delete(void);
/******************************************************************************
   3 ˽�ж���
******************************************************************************/
enum CPU_VIEW_TYPE_ENUM
{
    CPU_VIEW_TYPE_TASK      = 0,
    CPU_VIEW_TYPE_INT       = 1,
    CPU_VIEW_TYPE_POINT     = 2,
    CPU_VIEW_TYPE_SUB_INT   = 3,
    CPU_VIEW_TYPE_FUNC      = 4,

    CPU_VIEW_TYPE_BUTT
};

typedef unsigned int CPU_VIEW_TYPE_ENUM_UINT32;

enum CPU_VIEW_LEV_ENUM
{
    CPU_VIEW_LEV_EXIT           = 0,                        /* �˳���¼ */
    CPU_VIEW_LEV_ENTRY          = 1,                        /* �����¼ */

    CPU_VIEW_LEV_BUTT
};

typedef unsigned int CPU_VIEW_LEV_ENUM_UINT32;

enum CPU_VIEW_RECORD_MODE_ENUM
{
    CPU_VIEW_RECORD_MODE_CYCLE_NO           = 0,            /* ��ѭ��ģʽ */
    CPU_VIEW_RECORD_MODE_CYCLE_YES          = 1,            /* ѭ��ģʽ */

    CPU_VIEW_RECORD_MODE_BUTT
};

typedef unsigned int CPU_VIEW_RECORD_MODE_ENUM_UINT32;

enum CPU_VIEW_MEMORY_MODE_ENUM
{
    CPU_VIEW_MEMORY_MODE_DYNAMIC            = 0,            /* ��̬�����ڴ�ģʽ */
    CPU_VIEW_MEMORY_MODE_STATIC             = 1,            /* ��̬�����ڴ�ģʽ */

    CPU_VIEW_MEMORY_MODE_BUTT
};

typedef unsigned int CPU_VIEW_MEMORY_MODE_ENUM_UINT32;

enum CPU_VIEW_DUMP_GEN_MODE_ENUM
{
    CPU_VIEW_DUMP_GEN_MODE_FLASH            = 0,            /* CPUVIEW��¼dump�ļ�������flash��ģʽ */
    CPU_VIEW_DUMP_GEN_MODE_NETCARD          = 1,            /* CPUVIEW��¼dump�ļ�����������������ģʽ */

    CPU_VIEW_DUMP_GEN_MODE_BUTT
};

typedef unsigned int CPU_VIEW_DUMP_GEN_MODE_ENUM_UINT32;

enum CPU_VIEW_RECORD_OVERTURN_ENUM
{
    CPU_VIEW_RECORD_OVERTURN_NO             = 0,            /* CPUVIEW��¼û�з�ת */
    CPU_VIEW_RECORD_OVERTURN_YES            = 1,            /* CPUVIEW��¼������ת */

    CPU_VIEW_RECORD_OVERTURN_BUTT
};

typedef unsigned int CPU_VIEW_RECORD_OVERTURN_ENUM_UINT32;

#define CPU_MOD_GET(x, y)                       ((x) % (y))
#define CPU_MOD_ADD(x, y, z)                    (((x) + (y)) % (z))
#define CPU_MOD_SUB(x, y, z)                    ((((x) + (z)) - (y)) % (z))
#define CPU_MIN(x, y)                           (((x)<(y))?(x):(y))
#define CPU_MAX(x, y)                           (((x)>(y))?(x):(y))

/* ������̶��ڴ��CPU_VIEWʹ�ã��ʴ˴���Ҫ����ʱ�汾ʱ�޸ģ�
   ����һ�鵥�帴λ�����³�ʼ�����ڴ���ʱʹ�� */
#define CPU_VIEW_STATIC_MEM_ADDRESS_START       (0x0)
#define CPU_VIEW_STATIC_MEM_ADDRESS_END         (0x0)

/*max task number */
#define CPU_VIEW_MAX_TASK_NUMBER                (128)

/*max task name lenth */
#define CPU_VIEW_TASK_NAME_LENTH                (16)

#define CPU_VIEW_RECORD_DEFAULT_NUM             (20 * 1024)
#define CPU_VIEW_RECORD_MAX_NUM                 (20 * 1024)

#define CPU_VIEW_NO                             (0)
#define CPU_VIEW_YES                            (1)

/* ˽�нṹ�� */
typedef struct
{
    ACPU_UINT32      ulId;       /*����Id������INDEX���жϵ��жϺ�, ������ַ */
    ACPU_UINT8       ucType;
    ACPU_UINT8       ucLev;
    ACPU_UINT8       aucRsv[2];
    ACPU_UINT32      ulSlice;
    ACPU_UINT32      ulTick;
    ACPU_UINT32      ulPC;
    ACPU_UINT32      ulPara1;
} CPU_VIEW_STRU;

typedef struct
{
    ACPU_UINT32     ulPid;
    char            aucTaskName[CPU_VIEW_TASK_NAME_LENTH];
} CPU_TASK_NAME_STRU;

typedef struct
{
    ACPU_UINT32             ulCpuViewMode;      /* ��¼ģʽ��0:��ѭ��ģʽ 1:ѭ��ģʽ */
    ACPU_UINT32             ulCpuViewTraceCnt;  /* ��Ҫ��¼��CpuView��¼��Ŀ֮�� */

    ACPU_UINT32             ulCpuViewCnt;       /* ��ǰCpuView��¼��ָ�� */
    ACPU_UINT32             ulCpuViewOC;        /* ָ���Ƿ��Ѿ���ת */

    ACPU_UINT32             ulPointWatch;
    ACPU_UINT32             ulTaskWatch;
    ACPU_UINT32             ulFuncWatch;

    ACPU_UINT32             ulLastTaskId;
    ACPU_UINT32             ulDebugTaskId;      /* ��Ҫ�۲������ID��RR_FID,TaskId,stack begin,tcb address */

    ACPU_UINT32             ulTaskNumber;       /* ��ǰϵͳ��������� */
    CPU_TASK_NAME_STRU      astCpuTaskName[CPU_VIEW_MAX_TASK_NUMBER];   /* ����¼128������ */

    CPU_VIEW_STRU          *pstCpuView;         /* CpuView��¼�� */
} CPU_VIEW_CTRL_STRU;

/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
CPU_VIEW_CTRL_STRU     *g_pstAcpuViewCtrl           = NULL;
ACPU_UINT32             g_ulAcpuViewInitFlag        = CPU_VIEW_NO;
ACPU_UINT32             g_ulAcpuViewStartFlag       = CPU_VIEW_NO;
ACPU_UINT32             g_ulAcpuPointWatch          = CPU_VIEW_NO;
ACPU_UINT32             g_ulAcpuTaskWatch           = CPU_VIEW_NO;
ACPU_UINT32             g_ulAcpuFuncWatch           = CPU_VIEW_NO;
/*  ����Ŀǰlinux�ں˽�֧�������ϵͳע�������л��Ĺ��Ӻ�����û��ɾ�����ӵĽӿڣ�
    ������ȫ�ֱ�������ֹCPU_VIEW�ظ����ӹ��Ӻ��� */
ACPU_UINT32             g_ulAcpuTaskHookAddFlag     = CPU_VIEW_NO;

#define g_ulAcpuViewMode        (g_pstAcpuViewCtrl->ulCpuViewMode)
#define g_ulAcpuViewTraceCnt    (g_pstAcpuViewCtrl->ulCpuViewTraceCnt)
#define g_ulAcpuViewCnt         (g_pstAcpuViewCtrl->ulCpuViewCnt)
#define g_ulAcpuViewOC          (g_pstAcpuViewCtrl->ulCpuViewOC)
#define g_ulAcpuTaskNumber      (g_pstAcpuViewCtrl->ulTaskNumber)
#define g_pstAcpuView           (g_pstAcpuViewCtrl->pstCpuView)
#define g_astAcpuTaskName       (g_pstAcpuViewCtrl->astCpuTaskName)

/******************************************************************************
   5 �ڲ���������
******************************************************************************/
void AcpuView_End(void);

/******************************************************************************
   6 ����ʵ��
******************************************************************************/
/******************************************************************************
 Prototype      : CpuView_GetTaskName
 Description    : ��ȡ����ID��NAME�Ķ�Ӧ��ϵ
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_GetTaskName(void)
{
    struct task_struct                 *pTask;
    ACPU_UINT32                         ulTaskNum;

    PSACORE_MEM_SET(g_astAcpuTaskName, sizeof(CPU_TASK_NAME_STRU) * CPU_VIEW_MAX_TASK_NUMBER, 0, sizeof(CPU_TASK_NAME_STRU) * CPU_VIEW_MAX_TASK_NUMBER);

    /* ��¼Linux�е�һ���ں˽��̣�pidΪ0��������������ΪIdle */
    ulTaskNum = 0;
    g_astAcpuTaskName[ulTaskNum].ulPid = 0;
    (VOS_VOID)VOS_StrNCpy_s(g_astAcpuTaskName[ulTaskNum].aucTaskName, CPU_VIEW_MAX_TASK_NUMBER, "swapper", sizeof("swapper"));

    /* �����¼Linux���������� */
    ulTaskNum++;
    for (pTask = &init_task ; (pTask = next_task(pTask)) != &init_task ; )
    {
        if(ulTaskNum >= CPU_VIEW_MAX_TASK_NUMBER)
        {
            printk("Task Number Outof Range!\r\n");
            g_ulAcpuTaskNumber = CPU_VIEW_MAX_TASK_NUMBER;
            return;
        }

        g_astAcpuTaskName[ulTaskNum].ulPid = (ACPU_UINT32)pTask->pid;

        (VOS_VOID)VOS_StrNCpy_s(g_astAcpuTaskName[ulTaskNum].aucTaskName, (CPU_VIEW_TASK_NAME_LENTH - 1), pTask->comm, (CPU_VIEW_TASK_NAME_LENTH - 1));
        g_astAcpuTaskName[ulTaskNum].aucTaskName[CPU_VIEW_TASK_NAME_LENTH - 1]='\0';

        ulTaskNum++;
    }

    g_ulAcpuTaskNumber = ulTaskNum;

    return;
} /* CpuView_GetTaskName */

/******************************************************************************
 Prototype      : AcpuView_IsOverturn
 Description    : �ж��Ƿ��ּ�¼��ת
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2013-03-10
    Author      : g00178567
    Modification: Created function
******************************************************************************/
ACPU_UINT32 AcpuView_IsOverturn(void)
{
    if (g_ulAcpuViewTraceCnt == g_ulAcpuViewCnt)
    {
        g_ulAcpuViewOC = CPU_VIEW_RECORD_OVERTURN_YES;

        if (CPU_VIEW_RECORD_MODE_CYCLE_NO == g_ulAcpuViewMode)
        {
            return CPU_VIEW_YES;
        }
        else
        {
            g_ulAcpuViewCnt = 0;
        }
    }

    return CPU_VIEW_NO;
} /* AcpuView_IsOverturn */

/******************************************************************************
 Prototype      : CpuView_TaskSwitchHook
 Description    : �����л����Ӻ���
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_TaskSwitchHook(void *pOldTcb, void *pNewTcb)
{
    ACPU_UINT32          ulCurrentSlice = 0;

    if (CPU_VIEW_NO == g_ulAcpuTaskWatch)
    {
        return;
    }

    if (CPU_VIEW_YES == AcpuView_IsOverturn())
    {
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstAcpuView[g_ulAcpuViewCnt].ulId       = (ACPU_UINT32)((struct task_struct *)pOldTcb)->pid;
    g_pstAcpuView[g_ulAcpuViewCnt].ucType     = CPU_VIEW_TYPE_TASK;
    g_pstAcpuView[g_ulAcpuViewCnt].ucLev      = CPU_VIEW_LEV_EXIT;
    g_pstAcpuView[g_ulAcpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulTick     = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPC       = 0;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPara1    = 0;
    g_ulAcpuViewCnt++;

    if (CPU_VIEW_YES == AcpuView_IsOverturn())
    {
        return;
    }

    g_pstAcpuView[g_ulAcpuViewCnt].ulId       = (ACPU_UINT32)((struct task_struct *)pNewTcb)->pid;
    g_pstAcpuView[g_ulAcpuViewCnt].ucType     = CPU_VIEW_TYPE_TASK;
    g_pstAcpuView[g_ulAcpuViewCnt].ucLev      = CPU_VIEW_LEV_ENTRY;
    g_pstAcpuView[g_ulAcpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulTick     = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPC       = 0;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPara1    = 0;
    g_ulAcpuViewCnt++;

    return;
} /* CpuView_TaskSwitchHook */


/******************************************************************************
 Prototype      : CpuView_IntLevChgHook
 Description    : �ж��л����Ӻ���
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_IntLevChgHook(ACPU_UINT32 dir, ACPU_UINT32 oldVec, ACPU_UINT32 newVec)
{
    ACPU_UINT32          ulCurrentSlice = 0;

    if (CPU_VIEW_NO == g_ulAcpuTaskWatch)
    {
        return;
    }

    if (CPU_VIEW_YES == AcpuView_IsOverturn())
    {
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    /* �жϽ��� */
    if (0 == dir)
    {
        g_pstAcpuView[g_ulAcpuViewCnt].ucLev      = CPU_VIEW_LEV_ENTRY;
    }
    else /* �ж��˳� */
    {
        g_pstAcpuView[g_ulAcpuViewCnt].ucLev      = CPU_VIEW_LEV_EXIT;
    }
    g_pstAcpuView[g_ulAcpuViewCnt].ulId       = newVec;
    g_pstAcpuView[g_ulAcpuViewCnt].ucType     = CPU_VIEW_TYPE_INT;
    g_pstAcpuView[g_ulAcpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulTick     = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPC       = 0xFFFFFFFF;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPara1    = 0;
    g_ulAcpuViewCnt++;

    return;
} /* CpuView_IntLevChgHook */

/******************************************************************************
 Prototype      : CpuView_SetExtPoint
 Description    : �ڴ��������ù۲��ĺ���
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_SetPoint(ACPU_UINT32 ulId, ACPU_UINT8 ucLev, ACPU_UINT32 ulPara0, ACPU_UINT32 ulPara1)
{
    ACPU_UINT32  ulCurrentSlice = 0;

    if (CPU_VIEW_NO == g_ulAcpuPointWatch)
    {
        return;
    }

    if (CPU_VIEW_YES == AcpuView_IsOverturn())
    {
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstAcpuView[g_ulAcpuViewCnt].ulId       = ulId;
    g_pstAcpuView[g_ulAcpuViewCnt].ucType     = CPU_VIEW_TYPE_POINT;
    g_pstAcpuView[g_ulAcpuViewCnt].ucLev      = ucLev;
    g_pstAcpuView[g_ulAcpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulTick     = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPC       = ulPara0;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPara1    = ulPara1;
    g_ulAcpuViewCnt++;

    return;
} /* AcpuView_SetPoint */

#if (VOS_LINUX == VOS_OS_VER)
/******************************************************************************
 Prototype      : __cyg_profile_func_enter
 Description    : �������ù��Ӻ���
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void __cyg_profile_func_enter(void *this_fn, void *call_site)
{
    ACPU_UINT32  ulCurrentSlice = 0;

    if (CPU_VIEW_NO == g_ulAcpuFuncWatch)
    {
        return;
    }

    if (CPU_VIEW_YES == AcpuView_IsOverturn())
    {
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstAcpuView[g_ulAcpuViewCnt].ulId       = (ACPU_UINT32)this_fn;
    g_pstAcpuView[g_ulAcpuViewCnt].ucType     = CPU_VIEW_TYPE_FUNC;
    g_pstAcpuView[g_ulAcpuViewCnt].ucLev      = CPU_VIEW_LEV_ENTRY;
    g_pstAcpuView[g_ulAcpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulTick     = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPC       = (ACPU_UINT32)call_site;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPara1    = 0;
    g_ulAcpuViewCnt++;

    return;
} /* __cyg_profile_func_enter */


/******************************************************************************
 Prototype      : __cyg_profile_func_exit
 Description    : �����˳����Ӻ���
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void __cyg_profile_func_exit(void *this_fn, void *call_site)
{
    ACPU_UINT32  ulCurrentSlice = 0;

    if (CPU_VIEW_NO == g_ulAcpuFuncWatch)
    {
        return;
    }

    if (CPU_VIEW_YES == AcpuView_IsOverturn())
    {
        return;
    }

    /* get current time */
    ulCurrentSlice = mdrv_timer_get_hrt_timestamp();

    g_pstAcpuView[g_ulAcpuViewCnt].ulId       = (ACPU_UINT32)this_fn;
    g_pstAcpuView[g_ulAcpuViewCnt].ucType     = CPU_VIEW_TYPE_FUNC;
    g_pstAcpuView[g_ulAcpuViewCnt].ucLev      = CPU_VIEW_LEV_EXIT;
    g_pstAcpuView[g_ulAcpuViewCnt].ulSlice    = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulTick     = ulCurrentSlice;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPC       = (ACPU_UINT32)call_site;
    g_pstAcpuView[g_ulAcpuViewCnt].ulPara1    = 0;
    g_ulAcpuViewCnt++;

    return;
} /* __cyg_profile_func_exit */
#endif

/******************************************************************************
 Prototype      : CpuView_OpenPointWatch
 Description    : ����������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_OpenPointWatch(void)
{
    if (CPU_VIEW_NO == g_ulAcpuViewInitFlag)
    {
        printk("CpuView_OpenPointWatch, CpuView is not initialized!\r\n");
        return;
    }

    if (CPU_VIEW_YES == g_ulAcpuPointWatch)
    {
        printk("CpuView_OpenPointWatch, WatchPoint is already opened!\r\n");
        return;
    }

    g_ulAcpuPointWatch  = CPU_VIEW_YES;

    printk("WatchPoint open successfully!\r\n");

    return;
} /* CpuView_OpenPointWatch */

/******************************************************************************
 Prototype      : CpuView_ClosePointWatch
 Description    : �رղ�����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_ClosePointWatch(void)
{
    g_ulAcpuPointWatch = CPU_VIEW_NO;

    return;
} /* CpuView_ClosePointWatch */


/******************************************************************************
 Prototype      : CpuView_OpenTaskWatch
 Description    : �����������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_OpenTaskWatch(void)
{
    if (CPU_VIEW_NO == g_ulAcpuViewInitFlag)
    {
        printk("CpuView_OpenTaskWatch, CpuView is not initialized!\r\n");
        return;
    }

    if (CPU_VIEW_YES == g_ulAcpuTaskWatch)
    {
        printk("WatchTask is already opened!\r\n");
        return;
    }

    AcpuView_GetTaskName();

    if (CPU_VIEW_NO == g_ulAcpuTaskHookAddFlag)
    {
        /*�����ϵͳע�������Ӻ���*/
        if ( task_switch_hook_add((FUNC_VOID)AcpuView_TaskSwitchHook) )
        {
            printk("CpuView_OpenTaskWatch task_switch_hook_add fail!\r\n");
            return;
        }
        g_ulAcpuTaskHookAddFlag = CPU_VIEW_YES;
    }

    /*�����ϵͳע���жϹ��Ӻ���*/
    int_switch_hook_add((FUNC_VOID)AcpuView_IntLevChgHook);

    g_ulAcpuTaskWatch   = CPU_VIEW_YES;

    printk("WatchTask open successfully!\r\n");

    return;
} /* CpuView_OpenTaskWatch */

/******************************************************************************
 Prototype      : CpuView_CloseTaskWatch
 Description    : �ر��������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_CloseTaskWatch(void)
{
    if (CPU_VIEW_NO == g_ulAcpuTaskWatch)
    {
        return;
    }

    g_ulAcpuTaskWatch = CPU_VIEW_NO;

    int_switch_hook_delete();

    return;
} /* CpuView_CloseTaskWatch */


/******************************************************************************
 Prototype      : CpuView_OpenFuncWatch
 Description    : ������������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_OpenFuncWatch(void)
{
    if (CPU_VIEW_NO == g_ulAcpuViewInitFlag)
    {
        printk("CpuView_OpenFuncWatch, CpuView is not initialized!\r\n");
        return;
    }

    if (CPU_VIEW_YES == g_ulAcpuFuncWatch)
    {
        printk("CpuView_OpenFuncWatch is already opened!\r\n");
        return;
    }

    g_ulAcpuFuncWatch   = CPU_VIEW_YES;

    printk("FuncWatch open successfully!\r\n");

    return;
} /* CpuView_OpenFuncWatch */

/******************************************************************************
 Prototype      : CpuView_CloseFuncWatch
 Description    : �رպ�������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_CloseFuncWatch(void)
{
    g_ulAcpuFuncWatch = CPU_VIEW_NO;

    return;
} /* CpuView_CloseFuncWatch */

/******************************************************************************
 Prototype      : CpuView_Init
 Description    : CPU_VIEW��ʼ��
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_Init(ACPU_UINT32 ulRecordMode, ACPU_UINT32 ulRecordCnt)
{
    /* ulRecordMode ��¼CpuView���ڴ�ģʽ��
       0:��̬ģʽ;
       1:��̬ģʽ���ݲ�֧��
    */
    ACPU_UINT32     ulCpuViewTraceCnt;
#if 0
    ACPU_UINT32     ulCpuViewStaticBufferLenth;
#endif

    if (CPU_VIEW_YES == g_ulAcpuViewInitFlag)
    {
        printk("CpuView is already initialized!\r\n");
        return;
    }

    if (0 == ulRecordCnt)
    {
        ulCpuViewTraceCnt   = CPU_VIEW_RECORD_DEFAULT_NUM;
    }
    else if (CPU_VIEW_RECORD_MAX_NUM < ulRecordCnt)
    {
        ulCpuViewTraceCnt   = CPU_VIEW_RECORD_MAX_NUM;
    }
    else
    {
        ulCpuViewTraceCnt   = ulRecordCnt;
    }

    if (CPU_VIEW_MEMORY_MODE_DYNAMIC == ulRecordMode)
    {
        g_pstAcpuViewCtrl      = (CPU_VIEW_CTRL_STRU *)kmalloc( sizeof(CPU_VIEW_CTRL_STRU), GFP_KERNEL );
        if (NULL == g_pstAcpuViewCtrl)
        {
            g_ulAcpuViewInitFlag = CPU_VIEW_NO;
            printk("CpuView initialize failed!\r\n");

            return;
        }
        PSACORE_MEM_SET(g_pstAcpuViewCtrl, sizeof(CPU_VIEW_CTRL_STRU), 0, sizeof(CPU_VIEW_CTRL_STRU));

        g_pstAcpuViewCtrl->pstCpuView      = (CPU_VIEW_STRU *)kmalloc( sizeof(CPU_VIEW_STRU) * ulCpuViewTraceCnt, GFP_KERNEL );
        if (NULL == g_pstAcpuViewCtrl->pstCpuView)
        {
            g_ulAcpuViewInitFlag = CPU_VIEW_NO;
            printk("CpuView initialize failed!\r\n");

            return;
        }
        PSACORE_MEM_SET(g_pstAcpuViewCtrl->pstCpuView, sizeof(CPU_VIEW_STRU) * ulCpuViewTraceCnt, 0, sizeof(CPU_VIEW_STRU) * ulCpuViewTraceCnt);

        g_pstAcpuViewCtrl->ulCpuViewTraceCnt = ulCpuViewTraceCnt;
    }
    /* �ݲ�֧�־�̬�ڴ淽ʽ */
#if 0
    else if (CPU_VIEW_MEMORY_MODE_STATIC == ulRecordMode)
    {
        /*lint -e527 -e774*/
        ulCpuViewStaticBufferLenth = CPU_VIEW_STATIC_MEM_ADDRESS_END - CPU_VIEW_STATIC_MEM_ADDRESS_START;
        if (sizeof(CPU_VIEW_CTRL_STRU) > ulCpuViewStaticBufferLenth)
        {
            printk("CpuView_Init fail, no enough static buffer!\r\n");
            return;
        }
        /*lint +e527 +e774*/

        g_pstAcpuViewCtrl    = (CPU_VIEW_CTRL_STRU *)CPU_VIEW_STATIC_MEM_ADDRESS_START;

        PSACORE_MEM_SET(g_pstAcpuViewCtrl, sizeof(CPU_VIEW_CTRL_STRU), 0, sizeof(CPU_VIEW_CTRL_STRU));

        g_pstAcpuViewCtrl->ulCpuViewTraceCnt = (ulCpuViewStaticBufferLenth - sizeof(CPU_VIEW_CTRL_STRU))/(sizeof(CPU_VIEW_STRU));
        g_pstAcpuViewCtrl->pstCpuView        = (CPU_VIEW_STRU *)(g_pstAcpuViewCtrl + 1);
    }
#endif
    else
    {
        /* Ŀǰ��֧�ֶ�̬�ڴ�����ģʽ��ֱ�ӷ��� */
        printk("CpuView_Init Fail!Only Dynamic malloc is available!\r\n");
        return;
    }

    printk("CpuView initialize successfully!\r\n");

    g_ulAcpuViewInitFlag = CPU_VIEW_YES;

    return;
} /* CpuView_Init */

/******************************************************************************
 Prototype      : CpuView_Close
 Description    : CPU_VIEW���ܹر�
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_Close(void)
{
    if (CPU_VIEW_NO == g_ulAcpuViewInitFlag)
    {
        return;
    }

    if (CPU_VIEW_YES == g_ulAcpuViewStartFlag)
    {
        AcpuView_End();
    }

    kfree(g_pstAcpuViewCtrl->pstCpuView);
    g_pstAcpuViewCtrl->pstCpuView    = NULL;

    kfree(g_pstAcpuViewCtrl);
    g_pstAcpuViewCtrl    = NULL;

    g_ulAcpuViewInitFlag = CPU_VIEW_NO;

    return;
} /* CpuView_Close  */


/******************************************************************************
 Prototype      : CpuView_Start
 Description    : ����������жϼ��
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_Start(ACPU_UINT32 ulMode)
{
    if (CPU_VIEW_NO == g_ulAcpuViewInitFlag)
    {
        /* ����Ĭ��ֵ��ʼ�� */
        AcpuView_Init(CPU_VIEW_MEMORY_MODE_DYNAMIC, 0);
    }

    if (CPU_VIEW_YES == g_ulAcpuViewStartFlag)
    {
        printk("CpuView is already started!\r\n");
        return;
    }

    g_ulAcpuViewMode = ulMode;

    AcpuView_OpenPointWatch();
    AcpuView_OpenTaskWatch();
    AcpuView_OpenFuncWatch();

    g_ulAcpuViewCnt          = 0;
    g_ulAcpuViewOC           = CPU_VIEW_RECORD_OVERTURN_NO;

    g_ulAcpuViewStartFlag    = CPU_VIEW_YES;

    printk("CpuView Start......\r\n");

    return;
} /* CpuView_Start */


/******************************************************************************
 Prototype      : CpuView_End
 Description    : �ر������жϼ��
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_End(void)
{
    if (CPU_VIEW_NO == g_ulAcpuViewStartFlag)
    {
        printk("CpuView is not started!\r\n");
        return;
    }

    AcpuView_ClosePointWatch();
    AcpuView_CloseTaskWatch();
    AcpuView_CloseFuncWatch();

    g_ulAcpuViewStartFlag = CPU_VIEW_NO;

    return;
} /* CpuView_End */


/******************************************************************************
 Prototype      : CpuView_Restart
 Description    : �������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_Restart(void)
{
    if (CPU_VIEW_NO == g_ulAcpuViewStartFlag)
    {
        printk("CpuView is not started,please start first!\r\n");
        return;
    }

    g_ulAcpuPointWatch      = CPU_VIEW_YES;
    g_ulAcpuTaskWatch       = CPU_VIEW_YES;
    g_ulAcpuFuncWatch       = CPU_VIEW_YES;

    g_ulAcpuViewOC       = CPU_VIEW_RECORD_OVERTURN_NO;
    g_ulAcpuViewCnt      = 0;

    return;
} /* CpuView_Restart */

/******************************************************************************
 Prototype      : CpuView_Dump
 Description    : �������������ļ���
 Input          : ACPU_UINT32 ulDumpMode
                  0:�����FLASH
                  1:��������������豸(��ʱ��֧��)
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
/*lint -e522 -e550 -e830 -e960*/
void AcpuView_Dump(ACPU_UINT32 ulDumpMode)
{
    /* ulDumpMode ����CpuView�ļ�¼�ļ�ģʽ��
       0:�����FLASHģʽ;
       1:������������ݲ�֧��
    */
    ACPU_CHAR                               acDumpFileName[500];
    static ACPU_UINT8                       s_ucDumpFileNO = 0;
    int                                     fd = -1;
    mm_segment_t                            old_fs;
    ACPU_INT                                iRet;

    /* Acpu_Viewδ��ʼ��������Ĭ��ֵ���г�ʼ�� */
    if (CPU_VIEW_NO == g_ulAcpuViewInitFlag)
    {
        /* ����Ĭ��ֵ��ʼ�� */
        AcpuView_Init(CPU_VIEW_MEMORY_MODE_DYNAMIC, 0);

        /* ��ѭ��ģʽ */
        AcpuView_Start(CPU_VIEW_RECORD_MODE_CYCLE_NO);

        /* �ȴ�10s */
        msleep(10000);
    }

    /* Acpu_Viewδ��ʼ������Ĭ��ֵ��ʼ */
    if (CPU_VIEW_NO == g_ulAcpuViewStartFlag)
    {
        /* ��ѭ��ģʽ */
        AcpuView_Start(CPU_VIEW_RECORD_MODE_CYCLE_NO);

        /* �ȴ�10s */
        msleep(10000);
    }

    if ( (NULL == g_pstAcpuView)
        || ((0 == g_ulAcpuViewCnt) && (CPU_VIEW_RECORD_OVERTURN_NO == g_ulAcpuViewOC)) )
    {
        printk("AcpuView DumpTrace, No Trace need dump!\r\n");
        return;
    }

    AcpuView_End();

    printk("AcpuView Dump Trace Begin ............\r\n");

    old_fs = get_fs();

    /* �л��ļ�ϵͳ״̬ */
    set_fs(get_ds());

    if (CPU_VIEW_DUMP_GEN_MODE_FLASH == ulDumpMode)    /* �����FLASH */
    {
        printk("Dump to FLASH!\r\n");

        #if (FEATURE_ON == FEATURE_SKB_EXP)
        snprintf(acDumpFileName, strlen("/yaffs0/AcpuView255.dump"), "/yaffs0/AcpuView%d.dump", s_ucDumpFileNO);
        #else
        snprintf(acDumpFileName, strlen("/data/hisi_logs/ap_log/coredump/AcpuView255.dump"), "/data/hisi_logs/ap_log/coredump/AcpuView%d.dump", s_ucDumpFileNO);
        #endif

        printk("file name:%s\r\n", acDumpFileName);

        fd = sys_open(acDumpFileName, O_RDWR|O_CREAT, 0644);
        if (0 > fd)
        {
            printk("Open File Fail!Err:%d\r\n", fd);

            set_fs(old_fs);
            return;
        }
    }
    /* �ݲ�֧����������� */
#if 0
    else if (CPU_VIEW_DUMP_GEN_MODE_NETCARD == ulDumpMode)   /* ��������� */
    {
        printk("Dump to Host!\r\n");
        (VOS_VOID)VOS_sprintf_s(acDumpFileName, 500, "host:CpuView%d.dump", s_ucDumpFileNO);
        fd = sys_open(acDumpFileName, O_RDWR|O_CREAT, 0644);
        if (OK > fd)
        {
            printk("Open File Fail!Err:%d\r\n", fd);

            set_fs(old_fs);
            return;
        }
    }
#endif
    else
    {
        printk("Not support Dump file mode,Please check again!\r\n");
        set_fs(old_fs);
        return;
    }

    printk("Begin Write file ......");

    iRet = sys_write(fd, (const char *)g_pstAcpuViewCtrl, sizeof(CPU_VIEW_CTRL_STRU) );
    if (0 >  iRet)
    {
        printk("Write Control Info Fail!\r\n");
    }

    iRet = sys_write(fd, (const char *)g_pstAcpuView, sizeof(CPU_VIEW_STRU) * g_ulAcpuViewTraceCnt );
    if (0 >  iRet)
    {
        printk("Write Cpu View Fail!\r\n");
    }

    sys_close(fd);

    set_fs(old_fs);

    printk("......OK!\r\n");

    printk("AcpuView Dump Trace ok!\r\n");

    s_ucDumpFileNO++;

    return;
} /* CpuView_Dump */
/*lint +e522 +e550 +e830 +e960*/

/******************************************************************************
 Prototype      : CpuView_InfoPrint
 Description    : ��ӡCPU_VIEW��ʹ�õĵ�ַ
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g45205
    Modification: Created function
******************************************************************************/
void AcpuView_InfoPrint(void)
{
    if ((CPU_VIEW_NO == g_ulAcpuViewInitFlag) || (NULL == g_pstAcpuViewCtrl))
    {
        printk("CpuView is not initialized!\r\n");
        return;
    }

    printk( "CpuView Virt Base Addr=%zu\n", (ACPU_PTR)g_pstAcpuViewCtrl);

    printk("CpuView Virt Data Addr=%zu\r\n", ((ACPU_PTR)g_pstAcpuViewCtrl->pstCpuView));

    printk("CpuView Mode:%d\r\n", (ACPU_UINT16)g_pstAcpuViewCtrl->ulCpuViewMode);
    printk("CpuView TraceCnt:%d\r\n", (ACPU_UINT16)g_pstAcpuViewCtrl->ulCpuViewTraceCnt);
    printk("CpuView Cnt:%d\r\n", (ACPU_UINT16)g_pstAcpuViewCtrl->ulCpuViewCnt);
    printk("CpuView OC:%d\r\n", (ACPU_UINT16)g_pstAcpuViewCtrl->ulCpuViewOC);
    printk("CpuView TaskNumber:%d\r\n", (ACPU_UINT16)g_pstAcpuViewCtrl->ulTaskNumber);

    return;
}


/******************************************************************************
 Prototype      : CpuView_TaskPrint
 Description    : ��ӡA������
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2007-1-24
    Author      : g00178567
    Modification: Created function
******************************************************************************/
void AcpuView_TaskPrint(void)
{
    struct task_struct                 *pCurrenttaskId;
    struct task_struct                 *pTask;
    ACPU_UINT32                         ulTaskNum = 0;

    pCurrenttaskId = (struct task_struct *)current;
    printk("Current Task Name:%s, Id:0x%x\r\n", pCurrenttaskId->comm, pCurrenttaskId->pid);

    printk("Task list as follows:\r\n");
    printk("%-16s %-10s %-10s %-10s %-16s %-16s\r\n", "NAME", "PID", "POLICY", "STATUS", "DYNAMIC_PRIORI", "RT_PRIORI");
    for (pTask = &init_task ; (pTask = next_task(pTask)) != &init_task ; )
    {
        if(ulTaskNum >= CPU_VIEW_MAX_TASK_NUMBER)
        {
            printk("Total Task Number:%d\r\n", (ACPU_UINT16)CPU_VIEW_MAX_TASK_NUMBER);
            return;
        }

        printk("%-16s 0x%-8x 0x%-8x %-10d %-16d 0x%-14x\r\n", pTask->comm, pTask->pid, pTask->policy, (ACPU_UINT16)pTask->state, pTask->prio, pTask->rt_priority);

        ulTaskNum++;
    }

    printk("Total Task Number:%d\r\n", (ACPU_UINT16)ulTaskNum);

    return;
}

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif



