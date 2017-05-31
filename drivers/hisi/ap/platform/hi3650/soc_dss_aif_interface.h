#ifndef __SOC_DSS_AIF_INTERFACE_H__
#define __SOC_DSS_AIF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_0_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_AIF_AIF_CH_CTL_1_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_AIF_AIF_CH_CTL_2_ADDR(base) ((base) + (0x0040))
#define SOC_DSS_AIF_AIF_CH_CTL_3_ADDR(base) ((base) + (0x0060))
#define SOC_DSS_AIF_AIF_CH_CTL_4_ADDR(base) ((base) + (0x0080))
#define SOC_DSS_AIF_AIF_CH_CTL_5_ADDR(base) ((base) + (0x00a0))
#define SOC_DSS_AIF_AIF_CH_CTL_6_ADDR(base) ((base) + (0x00c0))
#define SOC_DSS_AIF_AIF_CH_CTL_7_ADDR(base) ((base) + (0x00e0))
#define SOC_DSS_AIF_AIF_CH_CTL_8_ADDR(base) ((base) + (0x0100))
#define SOC_DSS_AIF_AIF_CH_CTL_9_ADDR(base) ((base) + (0x0120))
#define SOC_DSS_AIF_AIF_CH_CTL_10_ADDR(base) ((base) + (0x0140))
#define SOC_DSS_AIF_AXI0_RID_MSK0_ADDR(base) ((base) + (0x0800))
#define SOC_DSS_AIF_AXI0_RID_MSK1_ADDR(base) ((base) + (0x0804))
#define SOC_DSS_AIF_AXI0_WID_MSK_ADDR(base) ((base) + (0x0808))
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_ADDR(base) ((base) + (0x080c))
#define SOC_DSS_AIF_AXI1_RID_MSK0_ADDR(base) ((base) + (0x0810))
#define SOC_DSS_AIF_AXI1_RID_MSK1_ADDR(base) ((base) + (0x0814))
#define SOC_DSS_AIF_AXI1_WID_MSK_ADDR(base) ((base) + (0x0818))
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_ADDR(base) ((base) + (0x081c))
#define SOC_DSS_AIF_AIF_CLK_SEL0_ADDR(base) ((base) + (0x0820))
#define SOC_DSS_AIF_AIF_CLK_SEL1_ADDR(base) ((base) + (0x0824))
#define SOC_DSS_AIF_AIF_CLK_EN0_ADDR(base) ((base) + (0x0828))
#define SOC_DSS_AIF_AIF_CLK_EN1_ADDR(base) ((base) + (0x082c))
#define SOC_DSS_AIF_MONITOR_CTRL_ADDR(base) ((base) + (0x0830))
#define SOC_DSS_AIF_MONITOR_TIMER_INI_ADDR(base) ((base) + (0x0834))
#define SOC_DSS_AIF_DEBUG_BUF_BASE_ADDR(base) ((base) + (0x0838))
#define SOC_DSS_AIF_DEBUG_CTRL_ADDR(base) ((base) + (0x083C))
#define SOC_DSS_AIF_AIF_SHADOW_READ_ADDR(base) ((base) + (0x0840))
#define SOC_DSS_AIF_AIF_MEM_CTRL_ADDR(base) ((base) + (0x0844))
#define SOC_DSS_AIF_AXI_REC_A_m_ADDR(base,m) ((base) + (0x0880+0x10*(m)))
#define SOC_DSS_AIF_AXI_REC_B_m_ADDR(base,m) ((base) + (0x0884+0x10*(m)))
#define SOC_DSS_AIF_AXI_REC_C_m_ADDR(base,m) ((base) + (0x0888+0x10*(m)))
#define SOC_DSS_AIF_AXI_REC_D_m_ADDR(base,m) ((base) + (0x088C+0x10*(m)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int max_cmd : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int credit_lth : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_0_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_0_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_0_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cmd_START (1)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cmd_END (3)
#define SOC_DSS_AIF_AIF_CH_CTL_0_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_0_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_0_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_step_END (22)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_lth_START (23)
#define SOC_DSS_AIF_AIF_CH_CTL_0_credit_lth_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int reserved_0 : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved_1 : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int reserved_2 : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_1_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_1_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_1_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_1_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_1_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_1_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_1_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_1_credit_step_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int max_cmd : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int credit_lth : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_2_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_2_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_2_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cmd_START (1)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cmd_END (3)
#define SOC_DSS_AIF_AIF_CH_CTL_2_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_2_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_2_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_step_END (22)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_lth_START (23)
#define SOC_DSS_AIF_AIF_CH_CTL_2_credit_lth_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int max_cmd : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int credit_lth : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_3_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_3_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_3_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cmd_START (1)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cmd_END (3)
#define SOC_DSS_AIF_AIF_CH_CTL_3_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_3_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_3_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_step_END (22)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_lth_START (23)
#define SOC_DSS_AIF_AIF_CH_CTL_3_credit_lth_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int max_cmd : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int credit_lth : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_4_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_4_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_4_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cmd_START (1)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cmd_END (3)
#define SOC_DSS_AIF_AIF_CH_CTL_4_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_4_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_4_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_step_END (22)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_lth_START (23)
#define SOC_DSS_AIF_AIF_CH_CTL_4_credit_lth_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int max_cmd : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int credit_lth : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_5_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_5_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_5_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cmd_START (1)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cmd_END (3)
#define SOC_DSS_AIF_AIF_CH_CTL_5_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_5_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_5_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_step_END (22)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_lth_START (23)
#define SOC_DSS_AIF_AIF_CH_CTL_5_credit_lth_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int reserved_0 : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved_1 : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int reserved_2 : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_6_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_6_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_6_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_6_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_6_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_6_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_6_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_6_credit_step_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int reserved_0 : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved_1 : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int reserved_2 : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_7_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_7_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_7_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_7_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_7_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_7_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_7_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_7_credit_step_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int max_cmd : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int credit_lth : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_8_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_8_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_8_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cmd_START (1)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cmd_END (3)
#define SOC_DSS_AIF_AIF_CH_CTL_8_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_8_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_8_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_step_END (22)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_lth_START (23)
#define SOC_DSS_AIF_AIF_CH_CTL_8_credit_lth_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int max_cmd : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int credit_lth : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_9_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_9_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_9_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cmd_START (1)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cmd_END (3)
#define SOC_DSS_AIF_AIF_CH_CTL_9_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_9_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_9_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_step_END (22)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_lth_START (23)
#define SOC_DSS_AIF_AIF_CH_CTL_9_credit_lth_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_sel : 1;
        unsigned int reserved_0 : 3;
        unsigned int mid : 4;
        unsigned int credit_mode : 2;
        unsigned int reserved_1 : 1;
        unsigned int credit_en : 1;
        unsigned int max_cont : 4;
        unsigned int credit_step : 7;
        unsigned int reserved_2 : 9;
    } reg;
} SOC_DSS_AIF_AIF_CH_CTL_10_UNION;
#endif
#define SOC_DSS_AIF_AIF_CH_CTL_10_axi_sel_START (0)
#define SOC_DSS_AIF_AIF_CH_CTL_10_axi_sel_END (0)
#define SOC_DSS_AIF_AIF_CH_CTL_10_mid_START (4)
#define SOC_DSS_AIF_AIF_CH_CTL_10_mid_END (7)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_mode_START (8)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_mode_END (9)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_en_START (11)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_en_END (11)
#define SOC_DSS_AIF_AIF_CH_CTL_10_max_cont_START (12)
#define SOC_DSS_AIF_AIF_CH_CTL_10_max_cont_END (15)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_step_START (16)
#define SOC_DSS_AIF_AIF_CH_CTL_10_credit_step_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi0_rid_msk0 : 32;
    } reg;
} SOC_DSS_AIF_AXI0_RID_MSK0_UNION;
#endif
#define SOC_DSS_AIF_AXI0_RID_MSK0_axi0_rid_msk0_START (0)
#define SOC_DSS_AIF_AXI0_RID_MSK0_axi0_rid_msk0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi0_rid_msk1 : 32;
    } reg;
} SOC_DSS_AIF_AXI0_RID_MSK1_UNION;
#endif
#define SOC_DSS_AIF_AXI0_RID_MSK1_axi0_rid_msk1_START (0)
#define SOC_DSS_AIF_AXI0_RID_MSK1_axi0_rid_msk1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi0_wid_msk : 32;
    } reg;
} SOC_DSS_AIF_AXI0_WID_MSK_UNION;
#endif
#define SOC_DSS_AIF_AXI0_WID_MSK_axi0_wid_msk_START (0)
#define SOC_DSS_AIF_AXI0_WID_MSK_axi0_wid_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi0_rd_qos_map : 8;
        unsigned int axi0_wr_qos_map : 8;
        unsigned int axi0_rd_prs_map : 8;
        unsigned int axi0_wr_prs_map : 8;
    } reg;
} SOC_DSS_AIF_AXI0_R_QOS_MAP_UNION;
#endif
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_qos_map_START (0)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_qos_map_END (7)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_qos_map_START (8)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_qos_map_END (15)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_prs_map_START (16)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_rd_prs_map_END (23)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_prs_map_START (24)
#define SOC_DSS_AIF_AXI0_R_QOS_MAP_axi0_wr_prs_map_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi1_rid_msk0 : 32;
    } reg;
} SOC_DSS_AIF_AXI1_RID_MSK0_UNION;
#endif
#define SOC_DSS_AIF_AXI1_RID_MSK0_axi1_rid_msk0_START (0)
#define SOC_DSS_AIF_AXI1_RID_MSK0_axi1_rid_msk0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi1_rid_msk1 : 32;
    } reg;
} SOC_DSS_AIF_AXI1_RID_MSK1_UNION;
#endif
#define SOC_DSS_AIF_AXI1_RID_MSK1_axi1_rid_msk1_START (0)
#define SOC_DSS_AIF_AXI1_RID_MSK1_axi1_rid_msk1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi1_wid_msk : 32;
    } reg;
} SOC_DSS_AIF_AXI1_WID_MSK_UNION;
#endif
#define SOC_DSS_AIF_AXI1_WID_MSK_axi1_wid_msk_START (0)
#define SOC_DSS_AIF_AXI1_WID_MSK_axi1_wid_msk_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi1_rd_qos_map : 8;
        unsigned int axi1_wr_qos_map : 8;
        unsigned int axi1_rd_prs_map : 8;
        unsigned int axi1_wr_prs_map : 8;
    } reg;
} SOC_DSS_AIF_AXI1_R_QOS_MAP_UNION;
#endif
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_qos_map_START (0)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_qos_map_END (7)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_qos_map_START (8)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_qos_map_END (15)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_prs_map_START (16)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_rd_prs_map_END (23)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_prs_map_START (24)
#define SOC_DSS_AIF_AXI1_R_QOS_MAP_axi1_wr_prs_map_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aif_clk_sel0 : 32;
    } reg;
} SOC_DSS_AIF_AIF_CLK_SEL0_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_SEL0_aif_clk_sel0_START (0)
#define SOC_DSS_AIF_AIF_CLK_SEL0_aif_clk_sel0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aif_clk_sel1 : 32;
    } reg;
} SOC_DSS_AIF_AIF_CLK_SEL1_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_SEL1_aif_clk_sel1_START (0)
#define SOC_DSS_AIF_AIF_CLK_SEL1_aif_clk_sel1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aif_clk_en0 : 32;
    } reg;
} SOC_DSS_AIF_AIF_CLK_EN0_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_EN0_aif_clk_en0_START (0)
#define SOC_DSS_AIF_AIF_CLK_EN0_aif_clk_en0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aif_clk_en1 : 32;
    } reg;
} SOC_DSS_AIF_AIF_CLK_EN1_UNION;
#endif
#define SOC_DSS_AIF_AIF_CLK_EN1_aif_clk_en1_START (0)
#define SOC_DSS_AIF_AIF_CLK_EN1_aif_clk_en1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int monitor_run : 1;
        unsigned int reserved_0 : 3;
        unsigned int monitor_streamid : 4;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_DSS_AIF_MONITOR_CTRL_UNION;
#endif
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_run_START (0)
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_run_END (0)
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_streamid_START (4)
#define SOC_DSS_AIF_MONITOR_CTRL_monitor_streamid_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int monitor_ini : 32;
    } reg;
} SOC_DSS_AIF_MONITOR_TIMER_INI_UNION;
#endif
#define SOC_DSS_AIF_MONITOR_TIMER_INI_monitor_ini_START (0)
#define SOC_DSS_AIF_MONITOR_TIMER_INI_monitor_ini_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 4;
        unsigned int debug_base : 28;
    } reg;
} SOC_DSS_AIF_DEBUG_BUF_BASE_UNION;
#endif
#define SOC_DSS_AIF_DEBUG_BUF_BASE_debug_base_START (4)
#define SOC_DSS_AIF_DEBUG_BUF_BASE_debug_base_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int debug_en : 1;
        unsigned int reserved : 15;
        unsigned int debug_depth : 16;
    } reg;
} SOC_DSS_AIF_DEBUG_CTRL_UNION;
#endif
#define SOC_DSS_AIF_DEBUG_CTRL_debug_en_START (0)
#define SOC_DSS_AIF_DEBUG_CTRL_debug_en_END (0)
#define SOC_DSS_AIF_DEBUG_CTRL_debug_depth_START (16)
#define SOC_DSS_AIF_DEBUG_CTRL_debug_depth_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aif_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_AIF_AIF_SHADOW_READ_UNION;
#endif
#define SOC_DSS_AIF_AIF_SHADOW_READ_aif_rd_shadow_START (0)
#define SOC_DSS_AIF_AIF_SHADOW_READ_aif_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mem_ctrl : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_DSS_AIF_AIF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_AIF_AIF_MEM_CTRL_mem_ctrl_START (0)
#define SOC_DSS_AIF_AIF_MEM_CTRL_mem_ctrl_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int length : 3;
        unsigned int rw : 1;
        unsigned int addr : 28;
    } reg;
} SOC_DSS_AIF_AXI_REC_A_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_A_m_length_START (0)
#define SOC_DSS_AIF_AXI_REC_A_m_length_END (2)
#define SOC_DSS_AIF_AXI_REC_A_m_rw_START (3)
#define SOC_DSS_AIF_AXI_REC_A_m_rw_END (3)
#define SOC_DSS_AIF_AXI_REC_A_m_addr_START (4)
#define SOC_DSS_AIF_AXI_REC_A_m_addr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id : 16;
        unsigned int prs : 2;
        unsigned int qos : 2;
        unsigned int user : 4;
        unsigned int prot : 3;
        unsigned int reserved : 1;
        unsigned int response : 2;
        unsigned int rec_axi_sel : 1;
        unsigned int recd_vld : 1;
    } reg;
} SOC_DSS_AIF_AXI_REC_B_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_B_m_id_START (0)
#define SOC_DSS_AIF_AXI_REC_B_m_id_END (15)
#define SOC_DSS_AIF_AXI_REC_B_m_prs_START (16)
#define SOC_DSS_AIF_AXI_REC_B_m_prs_END (17)
#define SOC_DSS_AIF_AXI_REC_B_m_qos_START (18)
#define SOC_DSS_AIF_AXI_REC_B_m_qos_END (19)
#define SOC_DSS_AIF_AXI_REC_B_m_user_START (20)
#define SOC_DSS_AIF_AXI_REC_B_m_user_END (23)
#define SOC_DSS_AIF_AXI_REC_B_m_prot_START (24)
#define SOC_DSS_AIF_AXI_REC_B_m_prot_END (26)
#define SOC_DSS_AIF_AXI_REC_B_m_response_START (28)
#define SOC_DSS_AIF_AXI_REC_B_m_response_END (29)
#define SOC_DSS_AIF_AXI_REC_B_m_rec_axi_sel_START (30)
#define SOC_DSS_AIF_AXI_REC_B_m_rec_axi_sel_END (30)
#define SOC_DSS_AIF_AXI_REC_B_m_recd_vld_START (31)
#define SOC_DSS_AIF_AXI_REC_B_m_recd_vld_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_rec_begin : 32;
    } reg;
} SOC_DSS_AIF_AXI_REC_C_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_C_m_axi_rec_begin_START (0)
#define SOC_DSS_AIF_AXI_REC_C_m_axi_rec_begin_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int axi_rec_end : 32;
    } reg;
} SOC_DSS_AIF_AXI_REC_D_m_UNION;
#endif
#define SOC_DSS_AIF_AXI_REC_D_m_axi_rec_end_START (0)
#define SOC_DSS_AIF_AXI_REC_D_m_axi_rec_end_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
