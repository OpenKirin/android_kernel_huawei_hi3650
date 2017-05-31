#ifndef __SOC_PERFSTAT_INTERFACE_H__
#define __SOC_PERFSTAT_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_PERFSTAT_CLK_GATE_ADDR(base) ((base) + (0x00))
#define SOC_PERFSTAT_CMD_START_ADDR(base) ((base) + (0x04))
#define SOC_PERFSTAT_SAMPLE_CNT_REG_ADDR(base) ((base) + (0x08))
#define SOC_PERFSTAT_SAMPLE_NUM_REG_ADDR(base) ((base) + (0x0C))
#define SOC_PERFSTAT_SAMPLE_STOP_ADDR(base) ((base) + (0x10))
#define SOC_PERFSTAT_REAL_PORT_NUM_ADDR(base) ((base) + (0x14))
#define SOC_PERFSTAT_AXI_ADDR_MODE_ADDR(base) ((base) + (0x18))
#define SOC_PERFSTAT_SEQ_ADDR_ADDR(base) ((base) + (0x1C))
#define SOC_PERFSTAT_SEQ_ADDR_LEN_ADDR(base) ((base) + (0x20))
#define SOC_PERFSTAT_DESCRIPTOR_ADDR_ADDR(base) ((base) + (0x24))
#define SOC_PERFSTAT_LAST_DESC_ADDR_ADDR(base) ((base) + (0x28))
#define SOC_PERFSTAT_STAT_RST_CNT_ADDR(base) ((base) + (0x2C))
#define SOC_PERFSTAT_INT_EN_ADDR(base) ((base) + (0x30))
#define SOC_PERFSTAT_INT_CLR_ADDR(base) ((base) + (0x34))
#define SOC_PERFSTAT_RAW_INT_STAT_ADDR(base) ((base) + (0x38))
#define SOC_PERFSTAT_MASK_INT_STAT_ADDR(base) ((base) + (0x3C))
#define SOC_PERFSTAT_ALL_SAMPLE_NUM_ADDR(base) ((base) + (0x40))
#define SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_ADDR(base) ((base) + (0x44))
#define SOC_PERFSTAT_OVERTIME_CFG_CNT_ADDR(base) ((base) + (0x48))
#define SOC_PERFSTAT_DEBUG_FIFO_FULL_ADDR(base) ((base) + (0x4C))
#define SOC_PERFSTAT_DEBUG_MONITOR_ADDR(base) ((base) + (0x50))
#define SOC_PERFSTAT_MONITOR_RESET_ADDR(base) ((base) + (0x54))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int apb_clk_gate : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PERFSTAT_CLK_GATE_UNION;
#endif
#define SOC_PERFSTAT_CLK_GATE_apb_clk_gate_START (0)
#define SOC_PERFSTAT_CLK_GATE_apb_clk_gate_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cmd_start : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PERFSTAT_CMD_START_UNION;
#endif
#define SOC_PERFSTAT_CMD_START_cmd_start_START (0)
#define SOC_PERFSTAT_CMD_START_cmd_start_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_PERFSTAT_SAMPLE_CNT_REG_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_PERFSTAT_SAMPLE_NUM_REG_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sample_stop : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PERFSTAT_SAMPLE_STOP_UNION;
#endif
#define SOC_PERFSTAT_SAMPLE_STOP_sample_stop_START (0)
#define SOC_PERFSTAT_SAMPLE_STOP_sample_stop_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int real_port_num : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_PERFSTAT_REAL_PORT_NUM_UNION;
#endif
#define SOC_PERFSTAT_REAL_PORT_NUM_real_port_num_START (0)
#define SOC_PERFSTAT_REAL_PORT_NUM_real_port_num_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_addr_mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PERFSTAT_AXI_ADDR_MODE_UNION;
#endif
#define SOC_PERFSTAT_AXI_ADDR_MODE_axi_addr_mode_START (0)
#define SOC_PERFSTAT_AXI_ADDR_MODE_axi_addr_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_PERFSTAT_SEQ_ADDR_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_PERFSTAT_SEQ_ADDR_LEN_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_PERFSTAT_DESCRIPTOR_ADDR_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_PERFSTAT_LAST_DESC_ADDR_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stat_rst_cnt : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_PERFSTAT_STAT_RST_CNT_UNION;
#endif
#define SOC_PERFSTAT_STAT_RST_CNT_stat_rst_cnt_START (0)
#define SOC_PERFSTAT_STAT_RST_CNT_stat_rst_cnt_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sample_int_en : 1;
        unsigned int overtime_int_en : 1;
        unsigned int desc_int_en : 1;
        unsigned int desc_error_en : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_PERFSTAT_INT_EN_UNION;
#endif
#define SOC_PERFSTAT_INT_EN_sample_int_en_START (0)
#define SOC_PERFSTAT_INT_EN_sample_int_en_END (0)
#define SOC_PERFSTAT_INT_EN_overtime_int_en_START (1)
#define SOC_PERFSTAT_INT_EN_overtime_int_en_END (1)
#define SOC_PERFSTAT_INT_EN_desc_int_en_START (2)
#define SOC_PERFSTAT_INT_EN_desc_int_en_END (2)
#define SOC_PERFSTAT_INT_EN_desc_error_en_START (3)
#define SOC_PERFSTAT_INT_EN_desc_error_en_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sample_int_clr : 1;
        unsigned int overtime_int_clr : 1;
        unsigned int desc_int_clr : 1;
        unsigned int desc_error_clr : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_PERFSTAT_INT_CLR_UNION;
#endif
#define SOC_PERFSTAT_INT_CLR_sample_int_clr_START (0)
#define SOC_PERFSTAT_INT_CLR_sample_int_clr_END (0)
#define SOC_PERFSTAT_INT_CLR_overtime_int_clr_START (1)
#define SOC_PERFSTAT_INT_CLR_overtime_int_clr_END (1)
#define SOC_PERFSTAT_INT_CLR_desc_int_clr_START (2)
#define SOC_PERFSTAT_INT_CLR_desc_int_clr_END (2)
#define SOC_PERFSTAT_INT_CLR_desc_error_clr_START (3)
#define SOC_PERFSTAT_INT_CLR_desc_error_clr_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sample_raw_int_stat : 1;
        unsigned int overtime_int_stat : 1;
        unsigned int desc_raw_int_stat : 1;
        unsigned int desc_raw_error_stat : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_PERFSTAT_RAW_INT_STAT_UNION;
#endif
#define SOC_PERFSTAT_RAW_INT_STAT_sample_raw_int_stat_START (0)
#define SOC_PERFSTAT_RAW_INT_STAT_sample_raw_int_stat_END (0)
#define SOC_PERFSTAT_RAW_INT_STAT_overtime_int_stat_START (1)
#define SOC_PERFSTAT_RAW_INT_STAT_overtime_int_stat_END (1)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_int_stat_START (2)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_int_stat_END (2)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_error_stat_START (3)
#define SOC_PERFSTAT_RAW_INT_STAT_desc_raw_error_stat_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sample_mask_int_stat : 1;
        unsigned int overtime_int_stat : 1;
        unsigned int desc_mask_int_stat : 1;
        unsigned int desc_mask_error_stat : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_PERFSTAT_MASK_INT_STAT_UNION;
#endif
#define SOC_PERFSTAT_MASK_INT_STAT_sample_mask_int_stat_START (0)
#define SOC_PERFSTAT_MASK_INT_STAT_sample_mask_int_stat_END (0)
#define SOC_PERFSTAT_MASK_INT_STAT_overtime_int_stat_START (1)
#define SOC_PERFSTAT_MASK_INT_STAT_overtime_int_stat_END (1)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_int_stat_START (2)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_int_stat_END (2)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_error_stat_START (3)
#define SOC_PERFSTAT_MASK_INT_STAT_desc_mask_error_stat_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_PERFSTAT_ALL_SAMPLE_NUM_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_PERFSTAT_LAST_SAMPLE_AXI_ADDR_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_PERFSTAT_OVERTIME_CFG_CNT_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int debug_fifo_full : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PERFSTAT_DEBUG_FIFO_FULL_UNION;
#endif
#define SOC_PERFSTAT_DEBUG_FIFO_FULL_debug_fifo_full_START (0)
#define SOC_PERFSTAT_DEBUG_FIFO_FULL_debug_fifo_full_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int debug_monitor : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_PERFSTAT_DEBUG_MONITOR_UNION;
#endif
#define SOC_PERFSTAT_DEBUG_MONITOR_debug_monitor_START (0)
#define SOC_PERFSTAT_DEBUG_MONITOR_debug_monitor_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int monitor_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_PERFSTAT_MONITOR_RESET_UNION;
#endif
#define SOC_PERFSTAT_MONITOR_RESET_monitor_reset_START (0)
#define SOC_PERFSTAT_MONITOR_RESET_monitor_reset_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
