/*************************************************************************
*   ��Ȩ����(C) 1987-2004, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  BSP_DRV_IPC.h
*
*   ��    �� :  wangjing
*
*   ��    �� :  IPCģ���û��ӿ��ļ�
*
*   �޸ļ�¼ :  2011��4��11��  v1.00  wangjing  ����
*************************************************************************/

#ifndef _BSP_DRV_IPC_H_
#define _BSP_DRV_IPC_H_

#include <asm/io.h>
#include "drv_comm.h"

#include "mdrv_ipc_enum.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void __iomem *ipc_base;

#define SIZE_4K             (4096)
#define BSP_IPC_BASE_ADDR   (SOC_IPC_S_BASE_ADDR)
#define IPC_REG_SIZE        (SIZE_4K)

#define BSP_RegRd(uwAddr)                   (0)
#define BSP_RegWr(uwAddr, uwValue)

#define SOC_IPC_CPU_INT_EN_ADDR(base, i)              ((base) + (0x500+(0x10*(i))))
#define SOC_IPC_SEM_INT_MASK_ADDR(base, j)            ((base) + (0x604+(0x10*(j))))
#define SOC_IPC_CPU_INT_CLR_ADDR(base, i)             ((base) + (0x40C+(0x10*(i))))
#define IRQ_IPC0_S                                                          (252)
#define IRQ_IPC1_S                                                          (253)
#define SOC_IPC_CPU_INT_EN_ADDR(base, i)              ((base) + (0x500+(0x10*(i))))
#define SOC_IPC_CPU_INT_DIS_ADDR(base, i)             ((base) + (0x504+(0x10*(i))))
#define SOC_IPC_CPU_INT_STAT_ADDR(base, i)            ((base) + (0x408+(0x10*(i))))
#define SOC_IPC_CPU_RAW_INT_ADDR(base, i)             ((base) + (0x400+(0x10*(i))))
#define SOC_IPC_CPU_INT_MASK_ADDR(base, i)            ((base) + (0x404+(0x10*(i))))
#define SOC_IPC_SEM_INT_CLR_ADDR(base, j)             ((base) + (0x60C+(0x10*(j))))
#define SOC_IPC_HS_CTRL_ADDR(base, j, k)              ((base) + (0x800+(0x100*(j))+(0x8*(k))))
#define SOC_IPC_SEM_INT_STAT_ADDR(base, j)            ((base) + (0x608+(0x10*(j))))
#define SOC_IPC_S_BASE_ADDR                           (0xe0475000)

#define SOC_IPC_CPU_INT_MASK_DIS_ADDR(base, i)           SOC_IPC_CPU_INT_EN_ADDR(base, i)
#define SOC_IPC_CPU_INT_MASK_EN_ADDR(base, i)         SOC_IPC_CPU_INT_DIS_ADDR(base, i)


#define BSP_IPC_CPU_RAW_INT(i)      (SOC_IPC_CPU_RAW_INT_ADDR((BSP_U32)ipc_base, i))    /* CPU_i�����ж�ԭʼ�жϼĴ���     */
#define BSP_IPC_CPU_INT_MASK(i)     (SOC_IPC_CPU_INT_MASK_ADDR((BSP_U32)ipc_base, i))   /* CPU_i�����ж�����Ĵ���         */
#define BSP_IPC_CPU_INT_STAT(i)     (SOC_IPC_CPU_INT_STAT_ADDR((BSP_U32)ipc_base, i))   /* CPU_i���κ�Ŀ����ж�״̬�Ĵ��� */
#define BSP_IPC_CPU_INT_CLR(i)      (SOC_IPC_CPU_INT_CLR_ADDR((BSP_U32)ipc_base, i))    /* CPU_i�����ж�����Ĵ���         */
#define BSP_IPC_INT_MASK_EN(i)      (SOC_IPC_CPU_INT_MASK_EN_ADDR((BSP_U32)ipc_base, i))    /* CPU_i�����ж�ʹ��           */
#define BSP_IPC_INT_MASK_DIS(i)     (SOC_IPC_CPU_INT_MASK_DIS_ADDR((BSP_U32)ipc_base, i))   /* CPU_i�����ж�ȥʹ��         */

#define BSP_IPC_SEM_RAW_INT(j)      (SOC_IPC_SEM_RAW_INT_ADDR((BSP_U32)ipc_base, j))    /* CPU_j�ź����ͷ�ԭʼ�жϼĴ���   */
#define BSP_IPC_SEM_INT_MASK(j)     (SOC_IPC_SEM_INT_MASK_ADDR((BSP_U32)ipc_base, j))   /* CPU_j�ź����ͷ��ж�����Ĵ���   */
#define BSP_IPC_SEM_INT_STAT(j)     (SOC_IPC_SEM_INT_STAT_ADDR((BSP_U32)ipc_base, j))   /* CPU_j�ź����ͷ��ж�״̬�Ĵ���   */
#define BSP_IPC_SEM_INT_CLR(j)      (SOC_IPC_SEM_INT_CLR_ADDR((BSP_U32)ipc_base, j))    /* CPU_j�ź����ͷ��ж�����Ĵ���   */
#define BSP_IPC_HS_CTRL(j,k)        (SOC_IPC_HS_CTRL_ADDR((BSP_U32)ipc_base, j, k))     /* CPU_j�ź���k����Ĵ���      */
#define BSP_IPC_HS_STAT(j,k)        (SOC_IPC_HS_STAT_ADDR((BSP_U32)ipc_base, j, k))     /* CPU_j�ź���k״̬�Ĵ���      */

#define BSP_IPC_CPU_RAW_INT_ACPU    (BSP_IPC_CPU_RAW_INT((BSP_U32)IPC_CORE_ACPU))           /* ACPU�����ж�ԭʼ�жϼĴ���     */
#define BSP_IPC_CPU_INT_MASK_ACPU   (BSP_IPC_CPU_INT_MASK((BSP_U32)IPC_CORE_ACPU))          /* ACPU�����ж�����Ĵ���         */
#define BSP_IPC_CPU_INT_STAT_ACPU   (BSP_IPC_CPU_INT_STAT((BSP_U32)IPC_CORE_ACPU))          /* ACPU���κ�Ŀ����ж�״̬�Ĵ��� */
#define BSP_IPC_CPU_INT_CLR_ACPU    (BSP_IPC_CPU_INT_CLR((BSP_U32)IPC_CORE_ACPU))           /* ACPU�����ж�����Ĵ���         */
#define BSP_IPC_CPU_INT_MASK_EN_ACPU    (BSP_IPC_INT_MASK_EN((BSP_U32)IPC_CORE_ACPU))       /* ACPU�����ж�ʹ��               */
#define BSP_IPC_CPU_INT_MASK_DIS_ACPU   (BSP_IPC_INT_MASK_DIS((BSP_U32)IPC_CORE_ACPU))      /* ACPU�����ж�ȥʹ��             */

#define UCOM_COMM_UINT32_MAX                (0xffffffff)                          /*32bit�޷��������ֵ*/
#define BSP_IPC_MAX_INT_NUM                 (32)                                  /*  */
#define IPC_MASK                        0xFFFFFF0F       /*��������[4:7]bitλ*/

/*������Ҫд��ARM_paxb.h��*/
#define INT_LEV_IPC_CPU             (IRQ_IPC0_S)
#define INT_LEV_IPC_SEM             (IRQ_IPC1_S)

#define INT_VEC_IPC_SEM             IVEC_TO_INUM(INT_LEV_IPC_SEM)
#define INTSRC_NUM                  32

#define INT_VEC_IPC_CPU             IVEC_TO_INUM(INT_LEV_IPC_CPU)
#define IPC_CHECK_PARA(ulLvl) \
    do{\
        if(ulLvl >= INTSRC_NUM)\
        {\
            printk("Wrong para , line:%d\n", __LINE__);\
            return BSP_ERROR;\
        }\
    }while(0)

typedef struct tagIPC_DEV_S {
	BSP_BOOL            bInit;
} IPC_DEV_S;

typedef struct {
	VOIDFUNCPTR routine;
	BSP_U32 arg;
} BSP_IPC_ENTRY;

typedef struct tagIPC_DEBUG_E {
	BSP_U32 u32RecvIntCore;
	BSP_U32 u32IntHandleTimes[INTSRC_NUM];
	BSP_U32 u32IntSendTimes[INTSRC_NUM];
	BSP_U32 u32SemId;
	BSP_U32 u32SemTakeTimes[INTSRC_NUM];
	BSP_U32 u32SemGiveTimes[INTSRC_NUM];
} IPC_DEBUG_E;

BSP_S32 DRV_IPCIntInit(void);

BSP_S32 IPC_IntEnable (IPC_INT_LEV_E ulLvl);

BSP_S32 IPC_IntConnect  (IPC_INT_LEV_E ulLvl, VOIDFUNCPTR routine, BSP_U32 parameter);

BSP_S32 IPC_IntSend(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);

BSP_VOID IPC_SpinLock (BSP_U32 u32SignalNum);

BSP_VOID IPC_SpinUnLock (BSP_U32 u32SignalNum);
BSP_VOID IPC_SemGive_Ccore_All(BSP_VOID);

#ifdef __cplusplus
}
#endif

#endif /* end #define _BSP_IPC_H_*/

