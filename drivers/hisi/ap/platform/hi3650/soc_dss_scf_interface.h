#ifndef __SOC_DSS_SCF_INTERFACE_H__
#define __SOC_DSS_SCF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_SCF_SCF_H_V_ORDER_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_ADDR(base) ((base) + (0x0014))
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_SCF_SCF_EN_HSCL_ADDR(base) ((base) + (0x001C))
#define SOC_DSS_SCF_SCF_EN_VSCL_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_SCF_SCF_ACC_HSCL_ADDR(base) ((base) + (0x0024))
#define SOC_DSS_SCF_SCF_ACC_HSCL1_ADDR(base) ((base) + (0x0028))
#define SOC_DSS_SCF_SCF_INC_HSCL_ADDR(base) ((base) + (0x0034))
#define SOC_DSS_SCF_SCF_ACC_VSCL_ADDR(base) ((base) + (0x0038))
#define SOC_DSS_SCF_SCF_ACC_VSCL1_ADDR(base) ((base) + (0x003C))
#define SOC_DSS_SCF_SCF_INC_VSCL_ADDR(base) ((base) + (0x0048))
#define SOC_DSS_SCF_SCF_EN_NONLINEAR_ADDR(base) ((base) + (0x004C))
#define SOC_DSS_SCF_SCF_EN_MMP_ADDR(base) ((base) + (0x007C))
#define SOC_DSS_SCF_SCF_DB_H0_ADDR(base) ((base) + (0x0080))
#define SOC_DSS_SCF_SCF_DB_H1_ADDR(base) ((base) + (0x0084))
#define SOC_DSS_SCF_SCF_DB_V0_ADDR(base) ((base) + (0x0088))
#define SOC_DSS_SCF_SCF_DB_V1_ADDR(base) ((base) + (0x008C))
#define SOC_DSS_SCF_SCF_LB_MEM_CTRL_ADDR(base) ((base) + (0x0090))
#define SOC_DSS_SCF_SCF_RD_SHADOW_ADDR(base) ((base) + (0x00F0))
#define SOC_DSS_SCF_SCF_CLK_SEL_ADDR(base) ((base) + (0x00F8))
#define SOC_DSS_SCF_SCF_CLK_EN_ADDR(base) ((base) + (0x00FC))
#define SOC_DSS_SCF_REG_DEFAULT_ADDR(base) ((base) + (0x00F4))
#define SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_ADDR(base) ((base) + (0x1000))
#define SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_ADDR(base) ((base) + (0x3000))
#define SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_ADDR(base) ((base) + (0x3800))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_hscl_str : 1;
        unsigned int scf_en_hscl_str_a : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_SCF_SCF_EN_HSCL_STR_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_START (0)
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_END (0)
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_a_START (1)
#define SOC_DSS_SCF_SCF_EN_HSCL_STR_scf_en_hscl_str_a_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_vscl_str : 1;
        unsigned int scf_en_vscl_str_a : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_SCF_SCF_EN_VSCL_STR_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_START (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_END (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_a_START (1)
#define SOC_DSS_SCF_SCF_EN_VSCL_STR_scf_en_vscl_str_a_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_h_v_order : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_SCF_SCF_H_V_ORDER_UNION;
#endif
#define SOC_DSS_SCF_SCF_H_V_ORDER_scf_h_v_order_START (0)
#define SOC_DSS_SCF_SCF_H_V_ORDER_scf_h_v_order_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_input_height : 13;
        unsigned int reserved_0 : 3;
        unsigned int scf_input_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_START (0)
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_height_END (12)
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_START (16)
#define SOC_DSS_SCF_SCF_INPUT_WIDTH_HEIGHT_scf_input_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_output_height : 13;
        unsigned int reserved_0 : 3;
        unsigned int scf_output_width : 13;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_UNION;
#endif
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_START (0)
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_height_END (12)
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_START (16)
#define SOC_DSS_SCF_SCF_OUTPUT_WIDTH_HEIGHT_scf_output_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_hcoef_mem_ctrl : 4;
        unsigned int scf_vcoef_mem_ctrl : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SCF_SCF_COEF_MEM_CTRL_UNION;
#endif
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_START (0)
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_hcoef_mem_ctrl_END (3)
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_START (4)
#define SOC_DSS_SCF_SCF_COEF_MEM_CTRL_scf_vcoef_mem_ctrl_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_hscl_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_SCF_SCF_EN_HSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_HSCL_scf_en_hscl_en_START (0)
#define SOC_DSS_SCF_SCF_EN_HSCL_scf_en_hscl_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_vscl_en : 1;
        unsigned int scf_out_buffer_en : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_SCF_SCF_EN_VSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_en_vscl_en_START (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_en_vscl_en_END (0)
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_out_buffer_en_START (1)
#define SOC_DSS_SCF_SCF_EN_VSCL_scf_out_buffer_en_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_acc_hscl : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_SCF_SCF_ACC_HSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_HSCL_scf_acc_hscl_START (0)
#define SOC_DSS_SCF_SCF_ACC_HSCL_scf_acc_hscl_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_acc_hscl1 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_SCF_SCF_ACC_HSCL1_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_HSCL1_scf_acc_hscl1_START (0)
#define SOC_DSS_SCF_SCF_ACC_HSCL1_scf_acc_hscl1_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_inc_hscl : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_SCF_SCF_INC_HSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_INC_HSCL_scf_inc_hscl_START (0)
#define SOC_DSS_SCF_SCF_INC_HSCL_scf_inc_hscl_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_acc_vscl : 30;
        unsigned int reserved : 2;
    } reg;
} SOC_DSS_SCF_SCF_ACC_VSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_VSCL_scf_acc_vscl_START (0)
#define SOC_DSS_SCF_SCF_ACC_VSCL_scf_acc_vscl_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_acc_vscl1 : 19;
        unsigned int reserved : 13;
    } reg;
} SOC_DSS_SCF_SCF_ACC_VSCL1_UNION;
#endif
#define SOC_DSS_SCF_SCF_ACC_VSCL1_scf_acc_vscl1_START (0)
#define SOC_DSS_SCF_SCF_ACC_VSCL1_scf_acc_vscl1_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_inc_vscl : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_SCF_SCF_INC_VSCL_UNION;
#endif
#define SOC_DSS_SCF_SCF_INC_VSCL_scf_inc_vscl_START (0)
#define SOC_DSS_SCF_SCF_INC_VSCL_scf_inc_vscl_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_sw_rst : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_SCF_SCF_EN_NONLINEAR_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_NONLINEAR_scf_sw_rst_START (0)
#define SOC_DSS_SCF_SCF_EN_NONLINEAR_scf_sw_rst_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_en_mmp : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_SCF_SCF_EN_MMP_UNION;
#endif
#define SOC_DSS_SCF_SCF_EN_MMP_scf_en_mmp_START (0)
#define SOC_DSS_SCF_SCF_EN_MMP_scf_en_mmp_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_debug_h0 : 32;
    } reg;
} SOC_DSS_SCF_SCF_DB_H0_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_H0_scf_debug_h0_START (0)
#define SOC_DSS_SCF_SCF_DB_H0_scf_debug_h0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_debug_h1 : 32;
    } reg;
} SOC_DSS_SCF_SCF_DB_H1_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_H1_scf_debug_h1_START (0)
#define SOC_DSS_SCF_SCF_DB_H1_scf_debug_h1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_debug_v0 : 32;
    } reg;
} SOC_DSS_SCF_SCF_DB_V0_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_V0_scf_debug_v0_START (0)
#define SOC_DSS_SCF_SCF_DB_V0_scf_debug_v0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_debug_v1 : 32;
    } reg;
} SOC_DSS_SCF_SCF_DB_V1_UNION;
#endif
#define SOC_DSS_SCF_SCF_DB_V1_scf_debug_v1_START (0)
#define SOC_DSS_SCF_SCF_DB_V1_scf_debug_v1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_lb_mem_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_SCF_SCF_LB_MEM_CTRL_UNION;
#endif
#define SOC_DSS_SCF_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_START (0)
#define SOC_DSS_SCF_SCF_LB_MEM_CTRL_scf_lb_mem_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_rd_shadow : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_SCF_SCF_RD_SHADOW_UNION;
#endif
#define SOC_DSS_SCF_SCF_RD_SHADOW_scf_rd_shadow_START (0)
#define SOC_DSS_SCF_SCF_RD_SHADOW_scf_rd_shadow_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_clk_sel : 32;
    } reg;
} SOC_DSS_SCF_SCF_CLK_SEL_UNION;
#endif
#define SOC_DSS_SCF_SCF_CLK_SEL_scf_clk_sel_START (0)
#define SOC_DSS_SCF_SCF_CLK_SEL_scf_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_clk_en : 32;
    } reg;
} SOC_DSS_SCF_SCF_CLK_EN_UNION;
#endif
#define SOC_DSS_SCF_SCF_CLK_EN_scf_clk_en_START (0)
#define SOC_DSS_SCF_SCF_CLK_EN_scf_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_SCF_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_SCF_REG_DEFAULT_reg_default_START (0)
#define SOC_DSS_SCF_REG_DEFAULT_reg_default_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_video_6tap_coef : 32;
    } reg;
} SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_UNION;
#endif
#define SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_scf_video_6tap_coef_START (0)
#define SOC_DSS_SCF_V0_SCF_VIDEO_6TAP_COEF_scf_video_6tap_coef_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_video_5tap_coef : 32;
    } reg;
} SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_UNION;
#endif
#define SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_scf_video_5tap_coef_START (0)
#define SOC_DSS_SCF_V0_SCF_VIDEO_5TAP_COEF_scf_video_5tap_coef_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int scf_video_4tap_coef : 32;
    } reg;
} SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_UNION;
#endif
#define SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_scf_video_4tap_coef_START (0)
#define SOC_DSS_SCF_V0_SCF_VIDEO_4TAP_COEF_scf_video_4tap_coef_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
