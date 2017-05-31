#ifndef __SOC_BLPWM_INTERFACE_H__
#define __SOC_BLPWM_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_BLPWM_IN_CTRL_ADDR(base) ((base) + (0x000))
#define SOC_BLPWM_IN_DIV_ADDR(base) ((base) + (0x004))
#define SOC_BLPWM_IN_NUM_ADDR(base) ((base) + (0x008))
#define SOC_BLPWM_IN_NUM_BAK_ADDR(base) ((base) + (0x00C))
#define SOC_BLPWM_CNT_MAX_ADDR(base) ((base) + (0x010))
#define SOC_BLPWM_INTR_DIFF_ADDR(base) ((base) + (0x014))
#define SOC_BLPWM_INTR_CTRL_ADDR(base) ((base) + (0x018))
#define SOC_BLPWM_IN_INTR_ADDR(base) ((base) + (0x01C))
#define SOC_BLPWM_INTR_CLEAR_ADDR(base) ((base) + (0x020))
#define SOC_BLPWM_OUT_CTRL_ADDR(base) ((base) + (0x100))
#define SOC_BLPWM_OUT_DIV_ADDR(base) ((base) + (0x104))
#define SOC_BLPWM_OUT_CFG_ADDR(base) ((base) + (0x108))
#define SOC_BLPWM_GROUP0_CFG_ADDR(base) ((base) + (0x10C))
#define SOC_BLPWM_GROUP1_CFG_ADDR(base) ((base) + (0x110))
#define SOC_BLPWM_GROUP2_CFG_ADDR(base) ((base) + (0x114))
#define SOC_BLPWM_GROUP3_CFG_ADDR(base) ((base) + (0x118))
#define SOC_BLPWM_GROUP4_CFG_ADDR(base) ((base) + (0x11C))
#define SOC_BLPWM_GROUP5_CFG_ADDR(base) ((base) + (0x120))
#define SOC_BLPWM_GROUP6_CFG_ADDR(base) ((base) + (0x124))
#define SOC_BLPWM_GROUP7_CFG_ADDR(base) ((base) + (0x128))
#define SOC_BLPWM_OUT_STATUS_ADDR(base) ((base) + (0x130))
#define SOC_BLPWM_GROUP_STATUS_ADDR(base) ((base) + (0x134))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_enable : 1;
        unsigned int reserved_0 : 15;
        unsigned int input_reverse : 1;
        unsigned int reserved_1 : 15;
    } reg;
} SOC_BLPWM_IN_CTRL_UNION;
#endif
#define SOC_BLPWM_IN_CTRL_cnt_enable_START (0)
#define SOC_BLPWM_IN_CTRL_cnt_enable_END (0)
#define SOC_BLPWM_IN_CTRL_input_reverse_START (16)
#define SOC_BLPWM_IN_CTRL_input_reverse_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_div : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_BLPWM_IN_DIV_UNION;
#endif
#define SOC_BLPWM_IN_DIV_cnt_div_START (0)
#define SOC_BLPWM_IN_DIV_cnt_div_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_low : 16;
        unsigned int cnt_high : 16;
    } reg;
} SOC_BLPWM_IN_NUM_UNION;
#endif
#define SOC_BLPWM_IN_NUM_cnt_low_START (0)
#define SOC_BLPWM_IN_NUM_cnt_low_END (15)
#define SOC_BLPWM_IN_NUM_cnt_high_START (16)
#define SOC_BLPWM_IN_NUM_cnt_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_low_debug : 16;
        unsigned int cnt_high_debug : 16;
    } reg;
} SOC_BLPWM_IN_NUM_BAK_UNION;
#endif
#define SOC_BLPWM_IN_NUM_BAK_cnt_low_debug_START (0)
#define SOC_BLPWM_IN_NUM_BAK_cnt_low_debug_END (15)
#define SOC_BLPWM_IN_NUM_BAK_cnt_high_debug_START (16)
#define SOC_BLPWM_IN_NUM_BAK_cnt_high_debug_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_max : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_BLPWM_CNT_MAX_UNION;
#endif
#define SOC_BLPWM_CNT_MAX_cnt_max_START (0)
#define SOC_BLPWM_CNT_MAX_cnt_max_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_intr_diff : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_BLPWM_INTR_DIFF_UNION;
#endif
#define SOC_BLPWM_INTR_DIFF_cnt_intr_diff_START (0)
#define SOC_BLPWM_INTR_DIFF_cnt_intr_diff_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_intr_mask : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_BLPWM_INTR_CTRL_UNION;
#endif
#define SOC_BLPWM_INTR_CTRL_cnt_intr_mask_START (0)
#define SOC_BLPWM_INTR_CTRL_cnt_intr_mask_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_raw_intr : 1;
        unsigned int reserved_0 : 15;
        unsigned int cnt_intr : 1;
        unsigned int reserved_1 : 15;
    } reg;
} SOC_BLPWM_IN_INTR_UNION;
#endif
#define SOC_BLPWM_IN_INTR_cnt_raw_intr_START (0)
#define SOC_BLPWM_IN_INTR_cnt_raw_intr_END (0)
#define SOC_BLPWM_IN_INTR_cnt_intr_START (16)
#define SOC_BLPWM_IN_INTR_cnt_intr_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cnt_intr_clear : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_BLPWM_INTR_CLEAR_UNION;
#endif
#define SOC_BLPWM_INTR_CLEAR_cnt_intr_clear_START (0)
#define SOC_BLPWM_INTR_CLEAR_cnt_intr_clear_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gen_en : 1;
        unsigned int gen_mode : 1;
        unsigned int bypass_mode : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_BLPWM_OUT_CTRL_UNION;
#endif
#define SOC_BLPWM_OUT_CTRL_gen_en_START (0)
#define SOC_BLPWM_OUT_CTRL_gen_en_END (0)
#define SOC_BLPWM_OUT_CTRL_gen_mode_START (1)
#define SOC_BLPWM_OUT_CTRL_gen_mode_END (1)
#define SOC_BLPWM_OUT_CTRL_bypass_mode_START (2)
#define SOC_BLPWM_OUT_CTRL_bypass_mode_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gen_cnt_div : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_BLPWM_OUT_DIV_UNION;
#endif
#define SOC_BLPWM_OUT_DIV_gen_cnt_div_START (0)
#define SOC_BLPWM_OUT_DIV_gen_cnt_div_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int start_low : 16;
        unsigned int start_high : 16;
    } reg;
} SOC_BLPWM_OUT_CFG_UNION;
#endif
#define SOC_BLPWM_OUT_CFG_start_low_START (0)
#define SOC_BLPWM_OUT_CFG_start_low_END (15)
#define SOC_BLPWM_OUT_CFG_start_high_START (16)
#define SOC_BLPWM_OUT_CFG_start_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int group0_refresh_freq : 8;
        unsigned int group0_step_times : 8;
        unsigned int group0_step : 15;
        unsigned int group0_active : 1;
    } reg;
} SOC_BLPWM_GROUP0_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP0_CFG_group0_refresh_freq_START (0)
#define SOC_BLPWM_GROUP0_CFG_group0_refresh_freq_END (7)
#define SOC_BLPWM_GROUP0_CFG_group0_step_times_START (8)
#define SOC_BLPWM_GROUP0_CFG_group0_step_times_END (15)
#define SOC_BLPWM_GROUP0_CFG_group0_step_START (16)
#define SOC_BLPWM_GROUP0_CFG_group0_step_END (30)
#define SOC_BLPWM_GROUP0_CFG_group0_active_START (31)
#define SOC_BLPWM_GROUP0_CFG_group0_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int group1_refresh_freq : 8;
        unsigned int group1_step_times : 8;
        unsigned int group1_step : 15;
        unsigned int group1_active : 1;
    } reg;
} SOC_BLPWM_GROUP1_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP1_CFG_group1_refresh_freq_START (0)
#define SOC_BLPWM_GROUP1_CFG_group1_refresh_freq_END (7)
#define SOC_BLPWM_GROUP1_CFG_group1_step_times_START (8)
#define SOC_BLPWM_GROUP1_CFG_group1_step_times_END (15)
#define SOC_BLPWM_GROUP1_CFG_group1_step_START (16)
#define SOC_BLPWM_GROUP1_CFG_group1_step_END (30)
#define SOC_BLPWM_GROUP1_CFG_group1_active_START (31)
#define SOC_BLPWM_GROUP1_CFG_group1_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int group2_refresh_freq : 8;
        unsigned int group2_step_times : 8;
        unsigned int group2_step : 15;
        unsigned int group2_active : 1;
    } reg;
} SOC_BLPWM_GROUP2_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP2_CFG_group2_refresh_freq_START (0)
#define SOC_BLPWM_GROUP2_CFG_group2_refresh_freq_END (7)
#define SOC_BLPWM_GROUP2_CFG_group2_step_times_START (8)
#define SOC_BLPWM_GROUP2_CFG_group2_step_times_END (15)
#define SOC_BLPWM_GROUP2_CFG_group2_step_START (16)
#define SOC_BLPWM_GROUP2_CFG_group2_step_END (30)
#define SOC_BLPWM_GROUP2_CFG_group2_active_START (31)
#define SOC_BLPWM_GROUP2_CFG_group2_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int group3_refresh_freq : 8;
        unsigned int group3_step_times : 8;
        unsigned int group3_step : 15;
        unsigned int group3_active : 1;
    } reg;
} SOC_BLPWM_GROUP3_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP3_CFG_group3_refresh_freq_START (0)
#define SOC_BLPWM_GROUP3_CFG_group3_refresh_freq_END (7)
#define SOC_BLPWM_GROUP3_CFG_group3_step_times_START (8)
#define SOC_BLPWM_GROUP3_CFG_group3_step_times_END (15)
#define SOC_BLPWM_GROUP3_CFG_group3_step_START (16)
#define SOC_BLPWM_GROUP3_CFG_group3_step_END (30)
#define SOC_BLPWM_GROUP3_CFG_group3_active_START (31)
#define SOC_BLPWM_GROUP3_CFG_group3_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int group4_refresh_freq : 8;
        unsigned int group4_step_times : 8;
        unsigned int group4_step : 15;
        unsigned int group4_active : 1;
    } reg;
} SOC_BLPWM_GROUP4_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP4_CFG_group4_refresh_freq_START (0)
#define SOC_BLPWM_GROUP4_CFG_group4_refresh_freq_END (7)
#define SOC_BLPWM_GROUP4_CFG_group4_step_times_START (8)
#define SOC_BLPWM_GROUP4_CFG_group4_step_times_END (15)
#define SOC_BLPWM_GROUP4_CFG_group4_step_START (16)
#define SOC_BLPWM_GROUP4_CFG_group4_step_END (30)
#define SOC_BLPWM_GROUP4_CFG_group4_active_START (31)
#define SOC_BLPWM_GROUP4_CFG_group4_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int group5_refresh_freq : 8;
        unsigned int group5_step_times : 8;
        unsigned int group5_step : 15;
        unsigned int group5_active : 1;
    } reg;
} SOC_BLPWM_GROUP5_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP5_CFG_group5_refresh_freq_START (0)
#define SOC_BLPWM_GROUP5_CFG_group5_refresh_freq_END (7)
#define SOC_BLPWM_GROUP5_CFG_group5_step_times_START (8)
#define SOC_BLPWM_GROUP5_CFG_group5_step_times_END (15)
#define SOC_BLPWM_GROUP5_CFG_group5_step_START (16)
#define SOC_BLPWM_GROUP5_CFG_group5_step_END (30)
#define SOC_BLPWM_GROUP5_CFG_group5_active_START (31)
#define SOC_BLPWM_GROUP5_CFG_group5_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int group6_refresh_freq : 8;
        unsigned int group6_step_times : 8;
        unsigned int group6_step : 15;
        unsigned int group6_active : 1;
    } reg;
} SOC_BLPWM_GROUP6_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP6_CFG_group6_refresh_freq_START (0)
#define SOC_BLPWM_GROUP6_CFG_group6_refresh_freq_END (7)
#define SOC_BLPWM_GROUP6_CFG_group6_step_times_START (8)
#define SOC_BLPWM_GROUP6_CFG_group6_step_times_END (15)
#define SOC_BLPWM_GROUP6_CFG_group6_step_START (16)
#define SOC_BLPWM_GROUP6_CFG_group6_step_END (30)
#define SOC_BLPWM_GROUP6_CFG_group6_active_START (31)
#define SOC_BLPWM_GROUP6_CFG_group6_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int group7_refresh_freq : 8;
        unsigned int group7_step_times : 8;
        unsigned int group7_step : 15;
        unsigned int group7_active : 1;
    } reg;
} SOC_BLPWM_GROUP7_CFG_UNION;
#endif
#define SOC_BLPWM_GROUP7_CFG_group7_refresh_freq_START (0)
#define SOC_BLPWM_GROUP7_CFG_group7_refresh_freq_END (7)
#define SOC_BLPWM_GROUP7_CFG_group7_step_times_START (8)
#define SOC_BLPWM_GROUP7_CFG_group7_step_times_END (15)
#define SOC_BLPWM_GROUP7_CFG_group7_step_START (16)
#define SOC_BLPWM_GROUP7_CFG_group7_step_END (30)
#define SOC_BLPWM_GROUP7_CFG_group7_active_START (31)
#define SOC_BLPWM_GROUP7_CFG_group7_active_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gen_low : 16;
        unsigned int gen_high : 16;
    } reg;
} SOC_BLPWM_OUT_STATUS_UNION;
#endif
#define SOC_BLPWM_OUT_STATUS_gen_low_START (0)
#define SOC_BLPWM_OUT_STATUS_gen_low_END (15)
#define SOC_BLPWM_OUT_STATUS_gen_high_START (16)
#define SOC_BLPWM_OUT_STATUS_gen_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gen_num : 3;
        unsigned int reserved_0 : 13;
        unsigned int group_over : 1;
        unsigned int group_inprogress : 1;
        unsigned int reserved_1 : 14;
    } reg;
} SOC_BLPWM_GROUP_STATUS_UNION;
#endif
#define SOC_BLPWM_GROUP_STATUS_gen_num_START (0)
#define SOC_BLPWM_GROUP_STATUS_gen_num_END (2)
#define SOC_BLPWM_GROUP_STATUS_group_over_START (16)
#define SOC_BLPWM_GROUP_STATUS_group_over_END (16)
#define SOC_BLPWM_GROUP_STATUS_group_inprogress_START (17)
#define SOC_BLPWM_GROUP_STATUS_group_inprogress_END (17)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
