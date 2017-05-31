/*************************************************************************
*   ��Ȩ����(C) 2008-2012, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  bsp_pdlock.h
*
*   ��    �� :  l00312158
*
*   ��    �� :  pdlockģ��Ե����ڽӿ�
*
*   �޸ļ�¼ :  2015��6��16��  v1.00  l00312158  ����
*************************************************************************/

#ifndef __BSP_PDLOCK_H__
#define __BSP_PDLOCK_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include "product_config.h"
#include "osl_types.h"
#include "drv_comm.h"


#ifdef CONFIG_PDLOCK
s32 bsp_pdlock_init_step1(void);
s32 bsp_pdlock_init_step2(void);
s32 bsp_pdlock_init(void);
#else
static s32 inline bsp_pdlock_init_step1(void)
{
    return BSP_OK;
}

static s32 inline bsp_pdlock_init_step2(void)
{
    return BSP_OK;
}

static s32 inline bsp_pdlock_init(void)
{
    return BSP_OK;
}

#endif

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __BSP_PDLOCK_H__ */
