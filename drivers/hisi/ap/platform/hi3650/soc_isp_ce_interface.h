#ifndef __SOC_ISP_CE_INTERFACE_H__
#define __SOC_ISP_CE_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_CE_CFG_ADDR(base) ((base) + (0x0))
#define SOC_ISP_CE_FACE_POSITION_LU_ADDR(base) ((base) + (0x4))
#define SOC_ISP_CE_FACE_POSITION_RD_ADDR(base) ((base) + (0x8))
#define SOC_ISP_CE_UV_GRAY_FILTER_ADDR(base,Range9) ((base) + (0x40+0x4*(Range9)))
#define SOC_ISP_CE_GAIN_ALONG_HUE_CFG_ADDR(base) ((base) + (0xFC))
#define SOC_ISP_CE_GAIN_ALONG_HUE0_ADDR(base,Range256) ((base) + (0x100+0x4*(Range256)))
#define SOC_ISP_CE_GAIN_ALONG_HUE1_ADDR(base,Range256) ((base) + (0x500+0x4*(Range256)))
#define SOC_ISP_CE_GRID_FLAG_ADDR(base,Range256) ((base) + (0x900+0x4*(Range256)))
#define SOC_ISP_CE_GRID_INFO_0_ADDR(base,Range128) ((base) + (0xD00+0x8*(Range128)))
#define SOC_ISP_CE_GRID_INFO_1_ADDR(base,Range128) ((base) + (0xD04+0x8*(Range128)))
#define SOC_ISP_CE_STAT_SATURATION_ADDR(base,Range256) ((base) + (0x1100+0x4*(Range256)))
#define SOC_ISP_CE_STAT_HISTH_ADDR(base,Range64) ((base) + (0x1500+0x4*(Range64)))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 16;
        unsigned int hue_stat_ds_factor : 4;
        unsigned int mce_strength : 6;
        unsigned int reserved_1 : 1;
        unsigned int get_stat : 1;
        unsigned int enable_sce : 1;
        unsigned int enable_mce : 1;
        unsigned int is_face_valid : 1;
        unsigned int modify_frame : 1;
    } reg;
} SOC_ISP_CE_CFG_UNION;
#endif
#define SOC_ISP_CE_CFG_hue_stat_ds_factor_START (16)
#define SOC_ISP_CE_CFG_hue_stat_ds_factor_END (19)
#define SOC_ISP_CE_CFG_mce_strength_START (20)
#define SOC_ISP_CE_CFG_mce_strength_END (25)
#define SOC_ISP_CE_CFG_get_stat_START (27)
#define SOC_ISP_CE_CFG_get_stat_END (27)
#define SOC_ISP_CE_CFG_enable_sce_START (28)
#define SOC_ISP_CE_CFG_enable_sce_END (28)
#define SOC_ISP_CE_CFG_enable_mce_START (29)
#define SOC_ISP_CE_CFG_enable_mce_END (29)
#define SOC_ISP_CE_CFG_is_face_valid_START (30)
#define SOC_ISP_CE_CFG_is_face_valid_END (30)
#define SOC_ISP_CE_CFG_modify_frame_START (31)
#define SOC_ISP_CE_CFG_modify_frame_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lu_x : 13;
        unsigned int reserved_0: 3;
        unsigned int lu_y : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_CE_FACE_POSITION_LU_UNION;
#endif
#define SOC_ISP_CE_FACE_POSITION_LU_lu_x_START (0)
#define SOC_ISP_CE_FACE_POSITION_LU_lu_x_END (12)
#define SOC_ISP_CE_FACE_POSITION_LU_lu_y_START (16)
#define SOC_ISP_CE_FACE_POSITION_LU_lu_y_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_x : 13;
        unsigned int reserved_0: 3;
        unsigned int rd_y : 13;
        unsigned int reserved_1: 3;
    } reg;
} SOC_ISP_CE_FACE_POSITION_RD_UNION;
#endif
#define SOC_ISP_CE_FACE_POSITION_RD_rd_x_START (0)
#define SOC_ISP_CE_FACE_POSITION_RD_rd_x_END (12)
#define SOC_ISP_CE_FACE_POSITION_RD_rd_y_START (16)
#define SOC_ISP_CE_FACE_POSITION_RD_rd_y_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int strength : 5;
        unsigned int reserved_0 : 3;
        unsigned int threshold : 8;
        unsigned int threshold_recip : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_ISP_CE_UV_GRAY_FILTER_UNION;
#endif
#define SOC_ISP_CE_UV_GRAY_FILTER_strength_START (0)
#define SOC_ISP_CE_UV_GRAY_FILTER_strength_END (4)
#define SOC_ISP_CE_UV_GRAY_FILTER_threshold_START (8)
#define SOC_ISP_CE_UV_GRAY_FILTER_threshold_END (15)
#define SOC_ISP_CE_UV_GRAY_FILTER_threshold_recip_START (16)
#define SOC_ISP_CE_UV_GRAY_FILTER_threshold_recip_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int active : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_CE_GAIN_ALONG_HUE_CFG_UNION;
#endif
#define SOC_ISP_CE_GAIN_ALONG_HUE_CFG_active_START (0)
#define SOC_ISP_CE_GAIN_ALONG_HUE_CFG_active_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gain_along_hue0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_CE_GAIN_ALONG_HUE0_UNION;
#endif
#define SOC_ISP_CE_GAIN_ALONG_HUE0_gain_along_hue0_START (0)
#define SOC_ISP_CE_GAIN_ALONG_HUE0_gain_along_hue0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gain_along_hue1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_CE_GAIN_ALONG_HUE1_UNION;
#endif
#define SOC_ISP_CE_GAIN_ALONG_HUE1_gain_along_hue1_START (0)
#define SOC_ISP_CE_GAIN_ALONG_HUE1_gain_along_hue1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int grid_flag : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_CE_GRID_FLAG_UNION;
#endif
#define SOC_ISP_CE_GRID_FLAG_grid_flag_START (0)
#define SOC_ISP_CE_GRID_FLAG_grid_flag_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int grid_info_0 : 8;
        unsigned int grid_info_1 : 8;
        unsigned int grid_info_2 : 8;
        unsigned int grid_info_3 : 8;
    } reg;
} SOC_ISP_CE_GRID_INFO_0_UNION;
#endif
#define SOC_ISP_CE_GRID_INFO_0_grid_info_0_START (0)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_0_END (7)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_1_START (8)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_1_END (15)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_2_START (16)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_2_END (23)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_3_START (24)
#define SOC_ISP_CE_GRID_INFO_0_grid_info_3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int grid_info_4 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_CE_GRID_INFO_1_UNION;
#endif
#define SOC_ISP_CE_GRID_INFO_1_grid_info_4_START (0)
#define SOC_ISP_CE_GRID_INFO_1_grid_info_4_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int max_saturation : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ISP_CE_STAT_SATURATION_UNION;
#endif
#define SOC_ISP_CE_STAT_SATURATION_max_saturation_START (0)
#define SOC_ISP_CE_STAT_SATURATION_max_saturation_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hist_h : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_ISP_CE_STAT_HISTH_UNION;
#endif
#define SOC_ISP_CE_STAT_HISTH_hist_h_START (0)
#define SOC_ISP_CE_STAT_HISTH_hist_h_END (11)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
