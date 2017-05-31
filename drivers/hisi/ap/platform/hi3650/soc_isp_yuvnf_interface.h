#ifndef __SOC_ISP_YUVNF_INTERFACE_H__
#define __SOC_ISP_YUVNF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_YUVNF_YUVNF_CONFIG_ADDR(base) ((base) + (0x0000))
#define SOC_ISP_YUVNF_SAD_INFO_ADDR(base) ((base) + (0x0004))
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_ADDR(base) ((base) + (0x0008))
#define SOC_ISP_YUVNF_SHIFT_TEXTRUE_ADDR(base) ((base) + (0x000C))
#define SOC_ISP_YUVNF_M_UV_TH_ADDR(base) ((base) + (0x0014))
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_ADDR(base) ((base) + (0x0018))
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_ADDR(base) ((base) + (0x0020))
#define SOC_ISP_YUVNF_XY_CENTER_ADDR(base) ((base) + (0x0024))
#define SOC_ISP_YUVNF_IMAGE_SIZE_ADDR(base) ((base) + (0x0028))
#define SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_ADDR(base) ((base) + (0x0030))
#define SOC_ISP_YUVNF_PGAUSSIANLUT_ADDR(base) ((base) + (0x034))
#define SOC_ISP_YUVNF_SHIFTN_ADDR(base) ((base) + (0x0038))
#define SOC_ISP_YUVNF_WEIGHT_LOW_ADDR(base) ((base) + (0x003c))
#define SOC_ISP_YUVNF_WEIGHT_HIGH_ADDR(base) ((base) + (0x0040))
#define SOC_ISP_YUVNF_BLEND_X_ADDR(base) ((base) + (0x0044))
#define SOC_ISP_YUVNF_BLEND_Y_ADDR(base) ((base) + (0x0048))
#define SOC_ISP_YUVNF_PGAUSSLUT_3_ADDR(base) ((base) + (0x004c))
#define SOC_ISP_YUVNF_PGAUSSLUT_7_ADDR(base) ((base) + (0x0050))
#define SOC_ISP_YUVNF_PGAUSSLUT_9_ADDR(base) ((base) + (0x0054))
#define SOC_ISP_YUVNF_BLENDLOW_ADDR(base) ((base) + (0x0058))
#define SOC_ISP_YUVNF_PGAINLSC_0_ADDR(base,Range53) ((base) + (0x0100+0x4*(Range53)))
#define SOC_ISP_YUVNF_PGAINLSC_1_ADDR(base,Range53) ((base) + (0x0300+0x4*(Range53)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int full_bypass : 1;
        unsigned int y_bypass : 1;
        unsigned int mult_gauss_en : 1;
        unsigned int bypass_symfilter : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_YUVNF_YUVNF_CONFIG_UNION;
#endif
#define SOC_ISP_YUVNF_YUVNF_CONFIG_full_bypass_START (0)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_full_bypass_END (0)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_y_bypass_START (1)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_y_bypass_END (1)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_mult_gauss_en_START (2)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_mult_gauss_en_END (2)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_bypass_symfilter_START (3)
#define SOC_ISP_YUVNF_YUVNF_CONFIG_bypass_symfilter_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int off_sad : 8;
        unsigned int shift_sad : 2;
        unsigned int reserved_0: 6;
        unsigned int inv_sad : 11;
        unsigned int reserved_1: 5;
    } reg;
} SOC_ISP_YUVNF_SAD_INFO_UNION;
#endif
#define SOC_ISP_YUVNF_SAD_INFO_off_sad_START (0)
#define SOC_ISP_YUVNF_SAD_INFO_off_sad_END (7)
#define SOC_ISP_YUVNF_SAD_INFO_shift_sad_START (8)
#define SOC_ISP_YUVNF_SAD_INFO_shift_sad_END (9)
#define SOC_ISP_YUVNF_SAD_INFO_inv_sad_START (16)
#define SOC_ISP_YUVNF_SAD_INFO_inv_sad_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int edgeth : 8;
        unsigned int edgemaxoff : 6;
        unsigned int reserved_0 : 2;
        unsigned int gainmaxoff : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_UNION;
#endif
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_edgeth_START (0)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_edgeth_END (7)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_edgemaxoff_START (8)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_edgemaxoff_END (13)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_gainmaxoff_START (16)
#define SOC_ISP_YUVNF_NOISE_REDUC_STRENGH_gainmaxoff_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shift_textrue : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_ISP_YUVNF_SHIFT_TEXTRUE_UNION;
#endif
#define SOC_ISP_YUVNF_SHIFT_TEXTRUE_shift_textrue_START (0)
#define SOC_ISP_YUVNF_SHIFT_TEXTRUE_shift_textrue_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int uv_impulsive_th : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_YUVNF_M_UV_TH_UNION;
#endif
#define SOC_ISP_YUVNF_M_UV_TH_uv_impulsive_th_START (0)
#define SOC_ISP_YUVNF_M_UV_TH_uv_impulsive_th_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int v_desaturation_th : 4;
        unsigned int u_desaturation_th : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_YUVNF_UV_DESATURATION_TH_UNION;
#endif
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_v_desaturation_th_START (0)
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_v_desaturation_th_END (3)
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_u_desaturation_th_START (4)
#define SOC_ISP_YUVNF_UV_DESATURATION_TH_u_desaturation_th_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int noeblendlow : 8;
        unsigned int edgeblendlow : 8;
        unsigned int noisescale : 7;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_UNION;
#endif
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_noeblendlow_START (0)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_noeblendlow_END (7)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_edgeblendlow_START (8)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_edgeblendlow_END (15)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_noisescale_START (16)
#define SOC_ISP_YUVNF_RECOVER_STRENGH_PARAM_noisescale_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int x_center : 13;
        unsigned int reserved_0: 3;
        unsigned int reserved_1: 16;
    } reg;
} SOC_ISP_YUVNF_XY_CENTER_UNION;
#endif
#define SOC_ISP_YUVNF_XY_CENTER_x_center_START (0)
#define SOC_ISP_YUVNF_XY_CENTER_x_center_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int height : 13;
        unsigned int reserved_0: 3;
        unsigned int width : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_YUVNF_IMAGE_SIZE_UNION;
#endif
#define SOC_ISP_YUVNF_IMAGE_SIZE_height_START (0)
#define SOC_ISP_YUVNF_IMAGE_SIZE_height_END (12)
#define SOC_ISP_YUVNF_IMAGE_SIZE_width_START (16)
#define SOC_ISP_YUVNF_IMAGE_SIZE_width_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pgain_table_active : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_UNION;
#endif
#define SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_pgain_table_active_START (0)
#define SOC_ISP_YUVNF_PGAIN_TABLE_ACTIVE_pgain_table_active_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pgaussianlut_0 : 7;
        unsigned int reserved_0 : 1;
        unsigned int pgaussianlut_1 : 7;
        unsigned int reserved_1 : 1;
        unsigned int pgaussianlut_2 : 7;
        unsigned int reserved_2 : 9;
    } reg;
} SOC_ISP_YUVNF_PGAUSSIANLUT_UNION;
#endif
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_0_START (0)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_0_END (6)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_1_START (8)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_1_END (14)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_2_START (16)
#define SOC_ISP_YUVNF_PGAUSSIANLUT_pgaussianlut_2_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shiftn : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_ISP_YUVNF_SHIFTN_UNION;
#endif
#define SOC_ISP_YUVNF_SHIFTN_shiftn_START (0)
#define SOC_ISP_YUVNF_SHIFTN_shiftn_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int weight_low_v : 8;
        unsigned int weight_low_u : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_YUVNF_WEIGHT_LOW_UNION;
#endif
#define SOC_ISP_YUVNF_WEIGHT_LOW_weight_low_v_START (0)
#define SOC_ISP_YUVNF_WEIGHT_LOW_weight_low_v_END (7)
#define SOC_ISP_YUVNF_WEIGHT_LOW_weight_low_u_START (8)
#define SOC_ISP_YUVNF_WEIGHT_LOW_weight_low_u_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int weight_high_v : 8;
        unsigned int weight_high_u : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_YUVNF_WEIGHT_HIGH_UNION;
#endif
#define SOC_ISP_YUVNF_WEIGHT_HIGH_weight_high_v_START (0)
#define SOC_ISP_YUVNF_WEIGHT_HIGH_weight_high_v_END (7)
#define SOC_ISP_YUVNF_WEIGHT_HIGH_weight_high_u_START (8)
#define SOC_ISP_YUVNF_WEIGHT_HIGH_weight_high_u_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int blend_x0 : 8;
        unsigned int blend_x1 : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_YUVNF_BLEND_X_UNION;
#endif
#define SOC_ISP_YUVNF_BLEND_X_blend_x0_START (0)
#define SOC_ISP_YUVNF_BLEND_X_blend_x0_END (7)
#define SOC_ISP_YUVNF_BLEND_X_blend_x1_START (8)
#define SOC_ISP_YUVNF_BLEND_X_blend_x1_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int blend_y0 : 8;
        unsigned int blend_y1 : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_YUVNF_BLEND_Y_UNION;
#endif
#define SOC_ISP_YUVNF_BLEND_Y_blend_y0_START (0)
#define SOC_ISP_YUVNF_BLEND_Y_blend_y0_END (7)
#define SOC_ISP_YUVNF_BLEND_Y_blend_y1_START (8)
#define SOC_ISP_YUVNF_BLEND_Y_blend_y1_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pg3lut_0 : 7;
        unsigned int reserved_0: 1;
        unsigned int pg3lut_1 : 7;
        unsigned int reserved_1: 1;
        unsigned int pg9lut_4 : 7;
        unsigned int reserved_2: 9;
    } reg;
} SOC_ISP_YUVNF_PGAUSSLUT_3_UNION;
#endif
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg3lut_0_START (0)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg3lut_0_END (6)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg3lut_1_START (8)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg3lut_1_END (14)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg9lut_4_START (16)
#define SOC_ISP_YUVNF_PGAUSSLUT_3_pg9lut_4_END (22)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pg7lut_0 : 7;
        unsigned int reserved_0: 1;
        unsigned int pg7lut_1 : 7;
        unsigned int reserved_1: 1;
        unsigned int pg7lut_2 : 7;
        unsigned int reserved_2: 1;
        unsigned int pg7lut_3 : 7;
        unsigned int reserved_3: 1;
    } reg;
} SOC_ISP_YUVNF_PGAUSSLUT_7_UNION;
#endif
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_0_START (0)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_0_END (6)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_1_START (8)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_1_END (14)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_2_START (16)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_2_END (22)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_3_START (24)
#define SOC_ISP_YUVNF_PGAUSSLUT_7_pg7lut_3_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pg9lut_0 : 7;
        unsigned int reserved_0: 1;
        unsigned int pg9lut_1 : 7;
        unsigned int reserved_1: 1;
        unsigned int pg9lut_2 : 7;
        unsigned int reserved_2: 1;
        unsigned int pg9lut_3 : 7;
        unsigned int reserved_3: 1;
    } reg;
} SOC_ISP_YUVNF_PGAUSSLUT_9_UNION;
#endif
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_0_START (0)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_0_END (6)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_1_START (8)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_1_END (14)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_2_START (16)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_2_END (22)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_3_START (24)
#define SOC_ISP_YUVNF_PGAUSSLUT_9_pg9lut_3_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int blendlow : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_ISP_YUVNF_BLENDLOW_UNION;
#endif
#define SOC_ISP_YUVNF_BLENDLOW_blendlow_START (0)
#define SOC_ISP_YUVNF_BLENDLOW_blendlow_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pgainlsc : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_YUVNF_PGAINLSC_0_UNION;
#endif
#define SOC_ISP_YUVNF_PGAINLSC_0_pgainlsc_START (0)
#define SOC_ISP_YUVNF_PGAINLSC_0_pgainlsc_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pgainlsc : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_ISP_YUVNF_PGAINLSC_1_UNION;
#endif
#define SOC_ISP_YUVNF_PGAINLSC_1_pgainlsc_START (0)
#define SOC_ISP_YUVNF_PGAINLSC_1_pgainlsc_END (12)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
