#ifndef __SOC_ISP_RAWNF_INTERFACE_H__
#define __SOC_ISP_RAWNF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_RAWNF_ISP_DPF_MODE_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_ADDR(base,Range16) ((base) + (0x0010+0x4*(Range16)))
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_ADDR(base) ((base) + (0x0054))
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_ADDR(base) ((base) + (0x0058))
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_ADDR(base) ((base) + (0x005C))
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_ADDR(base) ((base) + (0x0060))
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_ADDR(base) ((base) + (0x0064))
#define SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_ADDR(base) ((base) + (0x0068))
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_ADDR(base) ((base) + (0x006C))
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_ADDR(base) ((base) + (0x0070))
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_ADDR(base) ((base) + (0x0074))
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_ADDR(base) ((base) + (0x0078))
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_ADDR(base) ((base) + (0x007C))
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_ADDR(base) ((base) + (0x0080))
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_ADDR(base) ((base) + (0x0084))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpf_enable : 1;
        unsigned int b_filter_off : 1;
        unsigned int gb_filter_off : 1;
        unsigned int gr_filter_off : 1;
        unsigned int r_filter_off : 1;
        unsigned int nll_segmentation : 1;
        unsigned int awb_gain_comp : 1;
        unsigned int lsc_gain_comp : 1;
        unsigned int lsc_gain_offset_enable : 1;
        unsigned int dpf_filt_method : 1;
        unsigned int gauss_blend_enable : 1;
        unsigned int orgn_blend_enable : 1;
        unsigned int power_en : 1;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_MODE_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_MODE_dpf_enable_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_dpf_enable_END (0)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_b_filter_off_START (1)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_b_filter_off_END (1)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gb_filter_off_START (2)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gb_filter_off_END (2)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gr_filter_off_START (3)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gr_filter_off_END (3)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_r_filter_off_START (4)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_r_filter_off_END (4)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_nll_segmentation_START (5)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_nll_segmentation_END (5)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_awb_gain_comp_START (6)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_awb_gain_comp_END (6)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_lsc_gain_comp_START (7)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_lsc_gain_comp_END (7)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_lsc_gain_offset_enable_START (8)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_lsc_gain_offset_enable_END (8)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_dpf_filt_method_START (9)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_dpf_filt_method_END (9)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gauss_blend_enable_START (10)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_gauss_blend_enable_END (10)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_orgn_blend_enable_START (11)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_orgn_blend_enable_END (11)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_power_en_START (12)
#define SOC_ISP_RAWNF_ISP_DPF_MODE_power_en_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inv_weight_r : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_inv_weight_r_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_R_inv_weight_r_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inv_weight_g : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_inv_weight_g_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_G_inv_weight_g_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inv_weight_b : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_inv_weight_b_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_STRENGTH_B_inv_weight_b_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nll_coeff : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_nll_coeff_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_NLL_COEFF_nll_coeff_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpf_nf_gain_r : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_dpf_nf_gain_r_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_R_dpf_nf_gain_r_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpf_nf_gain_gr : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_dpf_nf_gain_gr_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GR_dpf_nf_gain_gr_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpf_nf_gain_gb : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_dpf_nf_gain_gb_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_GB_dpf_nf_gain_gb_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dpf_nf_gain_b : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_dpf_nf_gain_b_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_NF_GAIN_B_dpf_nf_gain_b_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int thr_en : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_N_MODE_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_en_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_en_END (0)
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_thr_en_START (1)
#define SOC_ISP_RAWNF_ISP_DPF_N_MODE_thr_en_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thr : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_thr_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_GBGR_THR_thr_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lsc_gain_offset_slope : 6;
        unsigned int reserved_0 : 2;
        unsigned int max_lsc_gain_offset : 6;
        unsigned int reserved_1 : 2;
        unsigned int lsc_offset_scale : 6;
        unsigned int reserved_2 : 10;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_lsc_gain_offset_slope_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_lsc_gain_offset_slope_END (5)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_max_lsc_gain_offset_START (8)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_max_lsc_gain_offset_END (13)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_lsc_offset_scale_START (16)
#define SOC_ISP_RAWNF_ISP_DPF_GAIN_DENOISE_lsc_offset_scale_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int luma_offset_thld : 8;
        unsigned int luma_offset_slope : 8;
        unsigned int luma_offset_max : 8;
        unsigned int reserved : 8;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_LUMA_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_thld_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_thld_END (7)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_slope_START (8)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_slope_END (15)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_max_START (16)
#define SOC_ISP_RAWNF_ISP_DPF_LUMA_luma_offset_max_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int base_blend_min : 8;
        unsigned int diff_scale : 6;
        unsigned int reserved_0 : 2;
        unsigned int edge_scale : 9;
        unsigned int reserved_1 : 7;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_BLEND_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_base_blend_min_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_base_blend_min_END (7)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_diff_scale_START (8)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_diff_scale_END (13)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_edge_scale_START (16)
#define SOC_ISP_RAWNF_ISP_DPF_BLEND_edge_scale_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rb_gauss_coef_0 : 6;
        unsigned int rb_gauss_coef_1 : 6;
        unsigned int rb_gauss_coef_2 : 6;
        unsigned int reserved : 14;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_0_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_0_END (5)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_1_START (6)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_1_END (11)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_2_START (12)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_RB_rb_gauss_coef_2_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int g_gauss_coef_0 : 6;
        unsigned int g_gauss_coef_1 : 6;
        unsigned int g_gauss_coef_2 : 6;
        unsigned int reserved : 14;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_0_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_0_END (5)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_1_START (6)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_1_END (11)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_2_START (12)
#define SOC_ISP_RAWNF_ISP_DPF_GAUSS_G_g_gauss_coef_2_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int edge_low_thld : 8;
        unsigned int edge_high_thld : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_edge_low_thld_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_edge_low_thld_END (7)
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_edge_high_thld_START (8)
#define SOC_ISP_RAWNF_ISP_DPF_EDGE_THLD_edge_high_thld_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int diff_low_thd : 14;
        unsigned int reserved_0 : 2;
        unsigned int diff_high_thd : 14;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_UNION;
#endif
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_diff_low_thd_START (0)
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_diff_low_thd_END (13)
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_diff_high_thd_START (16)
#define SOC_ISP_RAWNF_ISP_DPF_DIFF_THLD_diff_high_thd_END (29)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
