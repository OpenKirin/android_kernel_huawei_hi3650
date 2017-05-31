#ifndef __SOC_ISP_DEBUG_INTERFACE_H__
#define __SOC_ISP_DEBUG_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_ADDR(base) ((base) + (0x0))
#define SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_ADDR(base) ((base) + (0x04))
#define SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_ADDR(base) ((base) + (0x10))
#define SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_ADDR(base) ((base) + (0x14))
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_ADDR(base) ((base) + (0x18))
#define SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_ADDR(base) ((base) + (0x1C))
#define SOC_ISP_DEBUG_DBG_TOP_WPTR_ADDR(base) ((base) + (0x20))
#define SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_ADDR(base) ((base) + (0x40))
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_ADDR(base) ((base) + (0x44))
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_0_ADDR(base) ((base) + (0x4C))
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_1_ADDR(base) ((base) + (0x50))
#define SOC_ISP_DEBUG_DBG_BUS_CFG_ADDR(base) ((base) + (0x60))
#define SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_ADDR(base) ((base) + (0x64))
#define SOC_ISP_DEBUG_DBG_BUS_32K_MASK_ADDR(base) ((base) + (0x68))
#define SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_ADDR(base) ((base) + (0x6C))
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_ADDR(base) ((base) + (0x70))
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_ADDR(base) ((base) + (0x74))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_top_proc_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int dbg_top_stop_mod : 1;
        unsigned int reserved_1 : 3;
        unsigned int reserved_2 : 24;
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_dbg_top_proc_enable_START (0)
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_dbg_top_proc_enable_END (0)
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_dbg_top_stop_mod_START (4)
#define SOC_ISP_DEBUG_DBG_TOP_PROC_CFG_dbg_top_stop_mod_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_top_stop_timeout : 32;
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_dbg_top_stop_timeout_START (0)
#define SOC_ISP_DEBUG_DBG_TOP_PROC_TIMEOUT_dbg_top_stop_timeout_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int dbg_top_buf_baddr : 28;
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_dbg_top_buf_baddr_START (4)
#define SOC_ISP_DEBUG_DBG_TOP_BUF_ADDR_dbg_top_buf_baddr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_top_subframe_num : 11;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_dbg_top_subframe_num_START (0)
#define SOC_ISP_DEBUG_DBG_TOP_SUBFRAME_NUM_dbg_top_subframe_num_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_top_buf_line_stride : 10;
        unsigned int reserved_0 : 6;
        unsigned int dbg_top_buf_line_wrap : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_dbg_top_buf_line_stride_START (0)
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_dbg_top_buf_line_stride_END (9)
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_dbg_top_buf_line_wrap_START (16)
#define SOC_ISP_DEBUG_DBG_TOP_BUF_LINE_dbg_top_buf_line_wrap_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_top_refresh_ptr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_dbg_top_refresh_ptr_START (0)
#define SOC_ISP_DEBUG_DBG_TOP_REFRESH_WPTR_dbg_top_refresh_ptr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_top_wptr : 32;
    } reg;
} SOC_ISP_DEBUG_DBG_TOP_WPTR_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_TOP_WPTR_dbg_top_wptr_START (0)
#define SOC_ISP_DEBUG_DBG_TOP_WPTR_dbg_top_wptr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_irq_timeout : 32;
    } reg;
} SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_dbg_irq_timeout_START (0)
#define SOC_ISP_DEBUG_DBG_IRQ_STOP_TIMER_dbg_irq_timeout_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_irq_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int dbg_irq_stop_mod : 1;
        unsigned int reserved_1 : 3;
        unsigned int dbg_irq_start_mod : 1;
        unsigned int reserved_2 : 7;
        unsigned int dbg_irq_start_trig_idx : 6;
        unsigned int reserved_3 : 10;
    } reg;
} SOC_ISP_DEBUG_DBG_IRQ_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_enable_START (0)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_enable_END (0)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_stop_mod_START (4)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_stop_mod_END (4)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_start_mod_START (8)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_start_mod_END (8)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_start_trig_idx_START (16)
#define SOC_ISP_DEBUG_DBG_IRQ_CFG_dbg_irq_start_trig_idx_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_irq_mask0 : 32;
    } reg;
} SOC_ISP_DEBUG_DBG_IRQ_MASK_0_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_0_dbg_irq_mask0_START (0)
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_0_dbg_irq_mask0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_irq_mask1 : 32;
    } reg;
} SOC_ISP_DEBUG_DBG_IRQ_MASK_1_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_1_dbg_irq_mask1_START (0)
#define SOC_ISP_DEBUG_DBG_IRQ_MASK_1_dbg_irq_mask1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_bus_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int dbg_bus_stop_mod : 1;
        unsigned int reserved_1 : 3;
        unsigned int dbg_bus_mask_mod : 1;
        unsigned int reserved_2 : 3;
        unsigned int dbg_bus_info_mask : 2;
        unsigned int reserved_3 : 2;
        unsigned int reserved_4 : 16;
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_enable_START (0)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_enable_END (0)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_stop_mod_START (4)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_stop_mod_END (4)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_mask_mod_START (8)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_mask_mod_END (8)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_info_mask_START (12)
#define SOC_ISP_DEBUG_DBG_BUS_CFG_dbg_bus_info_mask_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_bus_timeout : 32;
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_dbg_bus_timeout_START (0)
#define SOC_ISP_DEBUG_DBG_BUS_STOP_TIMER_dbg_bus_timeout_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_bus_addr_32k_mask : 32;
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_32K_MASK_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_32K_MASK_dbg_bus_addr_32k_mask_START (0)
#define SOC_ISP_DEBUG_DBG_BUS_32K_MASK_dbg_bus_addr_32k_mask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_bus_addr_single_mask : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_dbg_bus_addr_single_mask_START (0)
#define SOC_ISP_DEBUG_DBG_BUS_SINGLE_MASK_dbg_bus_addr_single_mask_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_statis_ch0 : 5;
        unsigned int reserved_0 : 3;
        unsigned int dbg_statis_ch1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int dbg_statis_ch2 : 5;
        unsigned int reserved_2 : 3;
        unsigned int dbg_statis_ch3 : 5;
        unsigned int reserved_3 : 3;
    } reg;
} SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch0_START (0)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch0_END (4)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch1_START (8)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch1_END (12)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch2_START (16)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch2_END (20)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch3_START (24)
#define SOC_ISP_DEBUG_DBG_STATIS_MAP_CFG_dbg_statis_ch3_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dbg_statis_enable_ch0 : 1;
        unsigned int reserved_0 : 3;
        unsigned int dbg_statis_enable_ch1 : 1;
        unsigned int reserved_1 : 3;
        unsigned int dbg_statis_enable_ch2 : 1;
        unsigned int reserved_2 : 3;
        unsigned int dbg_statis_enable_ch3 : 1;
        unsigned int reserved_3 : 3;
        unsigned int reserved_4 : 16;
    } reg;
} SOC_ISP_DEBUG_DBG_STATIS_CFG_UNION;
#endif
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch0_START (0)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch0_END (0)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch1_START (4)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch1_END (4)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch2_START (8)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch2_END (8)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch3_START (12)
#define SOC_ISP_DEBUG_DBG_STATIS_CFG_dbg_statis_enable_ch3_END (12)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
