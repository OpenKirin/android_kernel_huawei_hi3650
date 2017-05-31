#ifndef __SOC_ISP_IE_INTERFACE_H__
#define __SOC_ISP_IE_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_IE_IE_CRTL_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_IE_IE_COLOR_SEL_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_IE_IE_MAT_1_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_IE_IE_MAT_2_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_IE_IE_MAT_3_ADDR(base) ((base) + (0x0010))
#define SOC_ISP_IE_IE_MAT_4_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_IE_IE_MAT_5_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_IE_IE_TINT_ADDR(base) ((base) + (0x001C))
#define SOC_ISP_IE_IE_CTRL_SHD_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_IE_IE_SHARPEN_ADDR(base) ((base) + (0x0024))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass_mode : 1;
        unsigned int effect_mode : 3;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_IE_IE_CRTL_UNION;
#endif
#define SOC_ISP_IE_IE_CRTL_bypass_mode_START (0)
#define SOC_ISP_IE_IE_CRTL_bypass_mode_END (0)
#define SOC_ISP_IE_IE_CRTL_effect_mode_START (1)
#define SOC_ISP_IE_IE_CRTL_effect_mode_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int color_selection : 3;
        unsigned int reserved_0 : 5;
        unsigned int color_threshold : 8;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_ISP_IE_IE_COLOR_SEL_UNION;
#endif
#define SOC_ISP_IE_IE_COLOR_SEL_color_selection_START (0)
#define SOC_ISP_IE_IE_COLOR_SEL_color_selection_END (2)
#define SOC_ISP_IE_IE_COLOR_SEL_color_threshold_START (8)
#define SOC_ISP_IE_IE_COLOR_SEL_color_threshold_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emb_coef_11 : 3;
        unsigned int emb_coef_11_en : 1;
        unsigned int emb_coef_12 : 3;
        unsigned int emb_coef_12_en : 1;
        unsigned int emb_coef_13 : 3;
        unsigned int emb_coef_13_en : 1;
        unsigned int emb_coef_21 : 3;
        unsigned int emb_coef_21_en : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_IE_IE_MAT_1_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_1_emb_coef_11_START (0)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_11_END (2)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_11_en_START (3)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_11_en_END (3)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_12_START (4)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_12_END (6)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_12_en_START (7)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_12_en_END (7)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_13_START (8)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_13_END (10)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_13_en_START (11)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_13_en_END (11)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_21_START (12)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_21_END (14)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_21_en_START (15)
#define SOC_ISP_IE_IE_MAT_1_emb_coef_21_en_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emb_coef_22 : 3;
        unsigned int emb_coef_22_en : 1;
        unsigned int emb_coef_23 : 3;
        unsigned int emb_coef_23_en : 1;
        unsigned int emb_coef_31 : 3;
        unsigned int emb_coef_31_en : 1;
        unsigned int emb_coef_32 : 3;
        unsigned int emb_coef_32_en : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_IE_IE_MAT_2_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_2_emb_coef_22_START (0)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_22_END (2)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_22_en_START (3)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_22_en_END (3)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_23_START (4)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_23_END (6)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_23_en_START (7)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_23_en_END (7)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_31_START (8)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_31_END (10)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_31_en_START (11)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_31_en_END (11)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_32_START (12)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_32_END (14)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_32_en_START (15)
#define SOC_ISP_IE_IE_MAT_2_emb_coef_32_en_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int emb_coef_33 : 3;
        unsigned int emb_coef_33_en : 1;
        unsigned int sket_coef_11 : 3;
        unsigned int sket_coef_11_en : 1;
        unsigned int sket_coef_12 : 3;
        unsigned int sket_coef_12_en : 1;
        unsigned int sket_coef_13 : 3;
        unsigned int sket_coef_13_en : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_IE_IE_MAT_3_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_3_emb_coef_33_START (0)
#define SOC_ISP_IE_IE_MAT_3_emb_coef_33_END (2)
#define SOC_ISP_IE_IE_MAT_3_emb_coef_33_en_START (3)
#define SOC_ISP_IE_IE_MAT_3_emb_coef_33_en_END (3)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_11_START (4)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_11_END (6)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_11_en_START (7)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_11_en_END (7)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_12_START (8)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_12_END (10)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_12_en_START (11)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_12_en_END (11)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_13_START (12)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_13_END (14)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_13_en_START (15)
#define SOC_ISP_IE_IE_MAT_3_sket_coef_13_en_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sket_coef_21 : 3;
        unsigned int sket_coef_21_en : 1;
        unsigned int sket_coef_22 : 3;
        unsigned int sket_coef_22_en : 1;
        unsigned int sket_coef_23 : 3;
        unsigned int sket_coef_23_en : 1;
        unsigned int sket_coef_31 : 3;
        unsigned int sket_coef_31_en : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_IE_IE_MAT_4_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_4_sket_coef_21_START (0)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_21_END (2)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_21_en_START (3)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_21_en_END (3)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_22_START (4)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_22_END (6)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_22_en_START (7)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_22_en_END (7)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_23_START (8)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_23_END (10)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_23_en_START (11)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_23_en_END (11)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_31_START (12)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_31_END (14)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_31_en_START (15)
#define SOC_ISP_IE_IE_MAT_4_sket_coef_31_en_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sket_coef_32 : 3;
        unsigned int sket_coef_32_en : 1;
        unsigned int sket_coef_33 : 3;
        unsigned int sket_coef_33_en : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_IE_IE_MAT_5_UNION;
#endif
#define SOC_ISP_IE_IE_MAT_5_sket_coef_32_START (0)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_32_END (2)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_32_en_START (3)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_32_en_END (3)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_33_START (4)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_33_END (6)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_33_en_START (7)
#define SOC_ISP_IE_IE_MAT_5_sket_coef_33_en_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inc_cb : 8;
        unsigned int inc_cr : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_IE_IE_TINT_UNION;
#endif
#define SOC_ISP_IE_IE_TINT_inc_cb_START (0)
#define SOC_ISP_IE_IE_TINT_inc_cb_END (7)
#define SOC_ISP_IE_IE_TINT_inc_cr_START (8)
#define SOC_ISP_IE_IE_TINT_inc_cr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int effect_mode_shd : 3;
        unsigned int reserved_1 : 28;
    } reg;
} SOC_ISP_IE_IE_CTRL_SHD_UNION;
#endif
#define SOC_ISP_IE_IE_CTRL_SHD_effect_mode_shd_START (1)
#define SOC_ISP_IE_IE_CTRL_SHD_effect_mode_shd_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coring_thr : 8;
        unsigned int sharp_factor : 6;
        unsigned int reserved : 18;
    } reg;
} SOC_ISP_IE_IE_SHARPEN_UNION;
#endif
#define SOC_ISP_IE_IE_SHARPEN_coring_thr_START (0)
#define SOC_ISP_IE_IE_SHARPEN_coring_thr_END (7)
#define SOC_ISP_IE_IE_SHARPEN_sharp_factor_START (8)
#define SOC_ISP_IE_IE_SHARPEN_sharp_factor_END (13)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
