#ifndef __SOC_ISP_BE_INTERFACE_H__
#define __SOC_ISP_BE_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_BE_FCLK_EN_BE_ADDR(base) ((base) + (0x0))
#define SOC_ISP_BE_CONTROL_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_BE_CROP_H_2_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_BE_CROP_V_2_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_BE_RGB2YUV_COEFF_0_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_BE_RGB2YUV_COEFF_1_ADDR(base) ((base) + (0x0034))
#define SOC_ISP_BE_RGB2YUV_COEFF_2_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_BE_RGB2YUV_COEFF_3_ADDR(base) ((base) + (0x003C))
#define SOC_ISP_BE_RGB2YUV_COEFF_4_ADDR(base) ((base) + (0x0040))
#define SOC_ISP_BE_RGB2YUV_COEFF_5_ADDR(base) ((base) + (0x0044))
#define SOC_ISP_BE_RGB2YUV_COEFF_6_ADDR(base) ((base) + (0x0048))
#define SOC_ISP_BE_RGB2YUV_COEFF_7_ADDR(base) ((base) + (0x004C))
#define SOC_ISP_BE_RGB2YUV_COEFF_8_ADDR(base) ((base) + (0x0050))
#define SOC_ISP_BE_YUV2RGB_COEFF_0_ADDR(base) ((base) + (0x0060))
#define SOC_ISP_BE_YUV2RGB_COEFF_1_ADDR(base) ((base) + (0x0064))
#define SOC_ISP_BE_YUV2RGB_COEFF_2_ADDR(base) ((base) + (0x0068))
#define SOC_ISP_BE_YUV2RGB_COEFF_3_ADDR(base) ((base) + (0x006C))
#define SOC_ISP_BE_YUV2RGB_COEFF_4_ADDR(base) ((base) + (0x0070))
#define SOC_ISP_BE_YUV2RGB_COEFF_5_ADDR(base) ((base) + (0x0074))
#define SOC_ISP_BE_YUV2RGB_COEFF_6_ADDR(base) ((base) + (0x0078))
#define SOC_ISP_BE_YUV2RGB_COEFF_7_ADDR(base) ((base) + (0x007C))
#define SOC_ISP_BE_YUV2RGB_COEFF_8_ADDR(base) ((base) + (0x0080))
#define SOC_ISP_BE_PTREG_ADDR(base) ((base) + (0x0090))
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_ADDR(base) ((base) + (0x00A0))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fclk_en_be : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_BE_FCLK_EN_BE_UNION;
#endif
#define SOC_ISP_BE_FCLK_EN_BE_fclk_en_be_START (0)
#define SOC_ISP_BE_FCLK_EN_BE_fclk_en_be_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bayer_pat_be : 2;
        unsigned int ccir_seq : 2;
        unsigned int conv_422 : 2;
        unsigned int awb_enable : 1;
        unsigned int uvup_ccir_seq : 2;
        unsigned int uvup_422_cosited : 1;
        unsigned int uvup_enable : 1;
        unsigned int select_ispbe_input_src : 1;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_BE_CONTROL_UNION;
#endif
#define SOC_ISP_BE_CONTROL_bayer_pat_be_START (0)
#define SOC_ISP_BE_CONTROL_bayer_pat_be_END (1)
#define SOC_ISP_BE_CONTROL_ccir_seq_START (2)
#define SOC_ISP_BE_CONTROL_ccir_seq_END (3)
#define SOC_ISP_BE_CONTROL_conv_422_START (4)
#define SOC_ISP_BE_CONTROL_conv_422_END (5)
#define SOC_ISP_BE_CONTROL_awb_enable_START (6)
#define SOC_ISP_BE_CONTROL_awb_enable_END (6)
#define SOC_ISP_BE_CONTROL_uvup_ccir_seq_START (7)
#define SOC_ISP_BE_CONTROL_uvup_ccir_seq_END (8)
#define SOC_ISP_BE_CONTROL_uvup_422_cosited_START (9)
#define SOC_ISP_BE_CONTROL_uvup_422_cosited_END (9)
#define SOC_ISP_BE_CONTROL_uvup_enable_START (10)
#define SOC_ISP_BE_CONTROL_uvup_enable_END (10)
#define SOC_ISP_BE_CONTROL_select_ispbe_input_src_START (11)
#define SOC_ISP_BE_CONTROL_select_ispbe_input_src_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ihleft : 13;
        unsigned int reserved_0: 3;
        unsigned int ihright : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_BE_CROP_H_2_UNION;
#endif
#define SOC_ISP_BE_CROP_H_2_ihleft_START (0)
#define SOC_ISP_BE_CROP_H_2_ihleft_END (12)
#define SOC_ISP_BE_CROP_H_2_ihright_START (16)
#define SOC_ISP_BE_CROP_H_2_ihright_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ivtop : 13;
        unsigned int reserved_0: 3;
        unsigned int ivbottom : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_BE_CROP_V_2_UNION;
#endif
#define SOC_ISP_BE_CROP_V_2_ivtop_START (0)
#define SOC_ISP_BE_CROP_V_2_ivtop_END (12)
#define SOC_ISP_BE_CROP_V_2_ivbottom_START (16)
#define SOC_ISP_BE_CROP_V_2_ivbottom_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int y_r : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_0_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_0_y_r_START (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_0_y_r_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int y_g : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_1_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_1_y_g_START (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_1_y_g_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int y_b : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_2_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_2_y_b_START (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_2_y_b_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int u_r : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_3_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_3_u_r_START (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_3_u_r_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int u_g : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_4_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_4_u_g_START (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_4_u_g_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int u_b : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_5_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_5_u_b_START (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_5_u_b_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_r : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_6_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_6_v_r_START (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_6_v_r_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_g : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_7_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_7_v_g_START (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_7_v_g_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_b : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_RGB2YUV_COEFF_8_UNION;
#endif
#define SOC_ISP_BE_RGB2YUV_COEFF_8_v_b_START (0)
#define SOC_ISP_BE_RGB2YUV_COEFF_8_v_b_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r_y : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_0_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_0_r_y_START (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_0_r_y_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r_u : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_1_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_1_r_u_START (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_1_r_u_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int r_v : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_2_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_2_r_v_START (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_2_r_v_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g_y : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_3_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_3_g_y_START (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_3_g_y_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g_u : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_4_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_4_g_u_START (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_4_g_u_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g_v : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_5_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_5_g_v_START (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_5_g_v_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int b_y : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_6_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_6_b_y_START (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_6_b_y_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int b_u : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_7_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_7_b_u_START (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_7_b_u_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int b_v : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_ISP_BE_YUV2RGB_COEFF_8_UNION;
#endif
#define SOC_ISP_BE_YUV2RGB_COEFF_8_b_v_START (0)
#define SOC_ISP_BE_YUV2RGB_COEFF_8_b_v_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ratio : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_ISP_BE_PTREG_UNION;
#endif
#define SOC_ISP_BE_PTREG_ratio_START (0)
#define SOC_ISP_BE_PTREG_ratio_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int force_clk_on_0 : 1;
        unsigned int force_clk_on_1 : 1;
        unsigned int force_clk_on_2 : 1;
        unsigned int force_clk_on_3 : 1;
        unsigned int force_clk_on_4 : 1;
        unsigned int force_clk_on_5 : 1;
        unsigned int force_clk_on_6 : 1;
        unsigned int force_clk_on_7 : 1;
        unsigned int force_clk_on_8 : 1;
        unsigned int force_clk_on_9 : 1;
        unsigned int force_clk_on_10 : 1;
        unsigned int force_clk_on_11 : 1;
        unsigned int force_clk_on_12 : 1;
        unsigned int force_clk_on_13 : 1;
        unsigned int reserved : 18;
    } reg;
} SOC_ISP_BE_FORCE_CLK_ON_CFG_UNION;
#endif
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_0_START (0)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_0_END (0)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_1_START (1)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_1_END (1)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_2_START (2)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_2_END (2)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_3_START (3)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_3_END (3)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_4_START (4)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_4_END (4)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_5_START (5)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_5_END (5)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_6_START (6)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_6_END (6)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_7_START (7)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_7_END (7)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_8_START (8)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_8_END (8)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_9_START (9)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_9_END (9)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_10_START (10)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_10_END (10)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_11_START (11)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_11_END (11)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_12_START (12)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_12_END (12)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_13_START (13)
#define SOC_ISP_BE_FORCE_CLK_ON_CFG_force_clk_on_13_END (13)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
