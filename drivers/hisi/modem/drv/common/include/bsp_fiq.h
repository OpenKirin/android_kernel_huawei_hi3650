#ifndef _BSP_FIQ_H
#define _BSP_FIQ_H

#include <product_config.h>
#include <drv_comm.h>
#include <bsp_shared_ddr.h>
#include <bsp_slice.h>
#include <osl_bio.h>
#ifdef   __OS_RTOSCK__
#include <sre_exc.h>
#endif
#define SHM_FIQ_BASE_ADDR                              (SHM_OFFSET_CCORE_FIQ + (unsigned long)SHM_BASE_ADDR)
#define SHM_FIQ_BARRIER                	               (SHM_FIQ_BASE_ADDR)
#define SHM_FIQ_STATUS_ADDR                          (SHM_FIQ_BARRIER + (unsigned long)0x4)
#define SHM_FIQ_CLEAR_ADDR                             (SHM_FIQ_STATUS_ADDR + (unsigned long)0x4)
#define SHM_FIQ_CP_TIMER_ADDR                       (SHM_FIQ_CLEAR_ADDR + (unsigned long)0x4)
#define SHM_FIQ_TOTAL_SEND_CNT                    (SHM_FIQ_CP_TIMER_ADDR + (unsigned long)0x4)
#define SHM_FIQ_TOTAL_RECIVE_CNT                  (SHM_FIQ_TOTAL_SEND_CNT + (unsigned long)0x4)
#define SHM_FIQ_INFO_ADDR                               (SHM_FIQ_TOTAL_RECIVE_CNT + (unsigned long)0x4)

#define FIQ_TRIGGER_TAG                     		 (0xFFFFFFF0)

/*���ȼ��ߵ��ȴ������ȼ�����ԽСԽ��*/
typedef enum __fiq_num
{
	FIQ_RESET = 0,
	FIQ_DUMP,
	FIQ_MAX
}fiq_num;

enum fiq_handler_return_value
{
	FIQ_RETURN_RUNNING = 0,                       /*FIQ�����˳���ϵͳ��������*/
	FIQ_ENTER_LOOP_1_NO_RETRUN = 1      , /*FIQ�����˳���ϵͳ������ѭ��������ӦFIQ*/
	FIQ_ENTER_WFE_NO_RETRUN =  2            /*FIQ�����˳���ϵͳ����WFEѭ������ӦFIQ*/
};

typedef int (* FIQ_PROC_FUNC)(void *);

#ifdef   __OS_RTOSCK__
/**
 * @brief ����FIQ
 *
 * @par ����:
 * ע��FIQ������
 *
 * @attention
 * </ul>�����ε��ã������һ��ע��Ϊ׼
  * </ul>FIQֻ���Ӹ���A9�����߱�����������A9�µ糡���·���FIQ�ᷢ���쳣
 *�û�ע��Ĺ��ӷ���ֵ�����enum fiq_handler_return_value
 * 
 **/ 

int request_fiq(fiq_num fiq_num_t, FIQ_PROC_FUNC pfnHandler,void * uwArg);

/**
 * @brief ɾ������FIQ
 *
 * @par ����:
 *ȥ ע��FIQ������
 *
 * @attention
 * </ul>����һ�μ�ɾ��
 *
 * 
 **/ 
int free_fiq(fiq_num fiq_num_t);

/**
 * @brief ����FIQ
 *
 * @par ����:
 * FIQ������
 *
 * @attention
 * </ul>���쳣��������FIQ�����µ���
 *
 * 
 **/ 

 UINT32 fiq_handler(EXC_INFO_S *pstExcInfo);
#elif defined __KERNEL__
/**
 * @brief ����FIQ
 *
 * @par ����:
 * ����FIQ�ж�
 *
 * @attention
 * </ul>
  * </ul>FIQֻ���Ӹ���A9�����߱�����������A9�µ糡���·���FIQ�ᷢ���쳣
 * 
 **/

int bsp_send_cp_fiq(fiq_num fiq_num_t);
#endif
#endif

