#ifndef __SOC_DSS_SBL_INTERFACE_H__
#define __SOC_DSS_SBL_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_SBL_DATA_FORMAT_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_SBL_CONTROL_REG1_ADDR(base) ((base) + (0x0004))
#define SOC_DSS_SBL_HS_POS_L_ADDR(base) ((base) + (0x0008))
#define SOC_DSS_SBL_HS_POS_H_ADDR(base) ((base) + (0x000C))
#define SOC_DSS_SBL_FRAME_WIDTH_L_ADDR(base) ((base) + (0x0010))
#define SOC_DSS_SBL_FRAME_WIDTH_H_ADDR(base) ((base) + (0x00000014))
#define SOC_DSS_SBL_FRAME_HEIGHT_L_ADDR(base) ((base) + (0x0018))
#define SOC_DSS_SBL_FRAME_HEIGHT_H_ADDR(base) ((base) + (0x001C))
#define SOC_DSS_SBL_VS_POS_L_ADDR(base) ((base) + (0x0020))
#define SOC_DSS_SBL_VS_POS_H_ADDR(base) ((base) + (0x0024))
#define SOC_DSS_SBL_ENABLE_ADDR(base) ((base) + (0x0400))
#define SOC_DSS_SBL_STRENGTH_ADDR(base) ((base) + (0x0408))
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_ADDR(base) ((base) + (0x040C))
#define SOC_DSS_SBL_SLOPE_MAX_ADDR(base) ((base) + (0x0410))
#define SOC_DSS_SBL_SLOPE_MIN_ADDR(base) ((base) + (0x0414))
#define SOC_DSS_SBL_BLACK_LEVEL_L_ADDR(base) ((base) + (0x0418))
#define SOC_DSS_SBL_BLACK_LEVEL_H_ADDR(base) ((base) + (0x041C))
#define SOC_DSS_SBL_WHITE_LEVEL_L_ADDR(base) ((base) + (0x0420))
#define SOC_DSS_SBL_WHITE_LEVEL_H_ADDR(base) ((base) + (0x0424))
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_ADDR(base) ((base) + (0x0428))
#define SOC_DSS_SBL_DITHER_MODE_ADDR(base) ((base) + (0x042C))
#define SOC_DSS_SBL_CONFIG_BUFFER_MODE_ADDR(base) ((base) + (0x0430))
#define SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_ADDR(base) ((base) + (0x0434))
#define SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_ADDR(base) ((base) + (0x0480))
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_ADDR(base) ((base) + (0x0484))
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_ADDR(base) ((base) + (0x0488))
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_ADDR(base) ((base) + (0x04C0))
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_ADDR(base) ((base) + (0x04C4))
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_ADDR(base) ((base) + (0x04C8))
#define SOC_DSS_SBL_LOGO_LEFT_ADDR(base) ((base) + (0x0800))
#define SOC_DSS_SBL_LOGO_TOP_ADDR(base) ((base) + (0x0804))
#define SOC_DSS_SBL_APICAL_DITHER_ADDR(base) ((base) + (0x0840))
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_ADDR(base) ((base) + (0x0C00))
#define SOC_DSS_SBL_STRENGTH_MANUAL_ADDR(base) ((base) + (0x0C04))
#define SOC_DSS_SBL_DRC_IN_L_ADDR(base) ((base) + (0x0C08))
#define SOC_DSS_SBL_DRC_IN_H_ADDR(base) ((base) + (0x0C0C))
#define SOC_DSS_SBL_BACKLIGHT_L_ADDR(base) ((base) + (0x0C10))
#define SOC_DSS_SBL_BACKLIGHT_H_ADDR(base) ((base) + (0x0C14))
#define SOC_DSS_SBL_AMBIENT_LIGHT_L_ADDR(base) ((base) + (0x0C18))
#define SOC_DSS_SBL_AMBIENT_LIGHT_H_ADDR(base) ((base) + (0x0C1C))
#define SOC_DSS_SBL_START_CALC_ADDR(base) ((base) + (0x0C20))
#define SOC_DSS_SBL_STRENGTH_LIMIT_ADDR(base) ((base) + (0x0C24))
#define SOC_DSS_SBL_CALIBRATION_A_L_ADDR(base) ((base) + (0x0C28))
#define SOC_DSS_SBL_CALIBRATION_A_H_ADDR(base) ((base) + (0x0C2C))
#define SOC_DSS_SBL_CALIBRATION_B_L_ADDR(base) ((base) + (0x0C30))
#define SOC_DSS_SBL_CALIBRATION_B_H_ADDR(base) ((base) + (0x0C34))
#define SOC_DSS_SBL_CALIBRATION_C_L_ADDR(base) ((base) + (0x0C38))
#define SOC_DSS_SBL_CALIBRATION_C_H_ADDR(base) ((base) + (0x0C3C))
#define SOC_DSS_SBL_CALIBRATION_D_L_ADDR(base) ((base) + (0x0C40))
#define SOC_DSS_SBL_CALIBRATION_D_H_ADDR(base) ((base) + (0x0C44))
#define SOC_DSS_SBL_T_FILTER_CONTROL_ADDR(base) ((base) + (0x0C48))
#define SOC_DSS_SBL_BACKLIGHT_MIN_L_ADDR(base) ((base) + (0x0C4C))
#define SOC_DSS_SBL_BACKLIGHT_MIN_H_ADDR(base) ((base) + (0x0C50))
#define SOC_DSS_SBL_BACKLIGHT_MAX_L_ADDR(base) ((base) + (0x0C54))
#define SOC_DSS_SBL_BACKLIGHT_MAX_H_ADDR(base) ((base) + (0x0C58))
#define SOC_DSS_SBL_BACKLIGHT_SCALE_L_ADDR(base) ((base) + (0x0C5C))
#define SOC_DSS_SBL_BACKLIGHT_SCALE_H_ADDR(base) ((base) + (0x0C60))
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_ADDR(base) ((base) + (0x0C64))
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_ADDR(base) ((base) + (0x0C68))
#define SOC_DSS_SBL_FILTER_A_L_ADDR(base) ((base) + (0x0C6C))
#define SOC_DSS_SBL_FILTER_A_H_ADDR(base) ((base) + (0x0C70))
#define SOC_DSS_SBL_FILTER_B_ADDR(base) ((base) + (0x0C74))
#define SOC_DSS_SBL_STRENGTH_OUT_ADDR(base) ((base) + (0x0C80))
#define SOC_DSS_SBL_DRC_OUT_L_ADDR(base) ((base) + (0x0C84))
#define SOC_DSS_SBL_DRC_OUT_H_ADDR(base) ((base) + (0x0C88))
#define SOC_DSS_SBL_BACKLIGHT_OUT_L_ADDR(base) ((base) + (0x0C8C))
#define SOC_DSS_SBL_BACKLIGHT_OUT_H_ADDR(base) ((base) + (0x0C90))
#define SOC_DSS_SBL_CALC_DONE_ADDR(base) ((base) + (0x0C94))
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_ADDR(base) ((base) + (0x0F00))
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_ADDR(base) ((base) + (0x0F10))
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_ADDR(base) ((base) + (0x0F14))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_format : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_SBL_DATA_FORMAT_UNION;
#endif
#define SOC_DSS_SBL_DATA_FORMAT_data_format_START (0)
#define SOC_DSS_SBL_DATA_FORMAT_data_format_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int contrlo_reg1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_CONTROL_REG1_UNION;
#endif
#define SOC_DSS_SBL_CONTROL_REG1_contrlo_reg1_START (0)
#define SOC_DSS_SBL_CONTROL_REG1_contrlo_reg1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hs_pos_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_HS_POS_L_UNION;
#endif
#define SOC_DSS_SBL_HS_POS_L_hs_pos_l_START (0)
#define SOC_DSS_SBL_HS_POS_L_hs_pos_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hs_pos_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_HS_POS_H_UNION;
#endif
#define SOC_DSS_SBL_HS_POS_H_hs_pos_h_START (0)
#define SOC_DSS_SBL_HS_POS_H_hs_pos_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frame_width_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_FRAME_WIDTH_L_UNION;
#endif
#define SOC_DSS_SBL_FRAME_WIDTH_L_frame_width_l_START (0)
#define SOC_DSS_SBL_FRAME_WIDTH_L_frame_width_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frame_width_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_FRAME_WIDTH_H_UNION;
#endif
#define SOC_DSS_SBL_FRAME_WIDTH_H_frame_width_h_START (0)
#define SOC_DSS_SBL_FRAME_WIDTH_H_frame_width_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frame_height_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_FRAME_HEIGHT_L_UNION;
#endif
#define SOC_DSS_SBL_FRAME_HEIGHT_L_frame_height_l_START (0)
#define SOC_DSS_SBL_FRAME_HEIGHT_L_frame_height_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int frame_height_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_FRAME_HEIGHT_H_UNION;
#endif
#define SOC_DSS_SBL_FRAME_HEIGHT_H_frame_height_h_START (0)
#define SOC_DSS_SBL_FRAME_HEIGHT_H_frame_height_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vs_pos_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_VS_POS_L_UNION;
#endif
#define SOC_DSS_SBL_VS_POS_L_vs_pos_l_START (0)
#define SOC_DSS_SBL_VS_POS_L_vs_pos_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vs_pos_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_VS_POS_H_UNION;
#endif
#define SOC_DSS_SBL_VS_POS_H_vs_pos_h_START (0)
#define SOC_DSS_SBL_VS_POS_H_vs_pos_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enable : 1;
        unsigned int local_contrast : 2;
        unsigned int reserved_0 : 1;
        unsigned int color_correction : 1;
        unsigned int reserved_1 : 27;
    } reg;
} SOC_DSS_SBL_ENABLE_UNION;
#endif
#define SOC_DSS_SBL_ENABLE_enable_START (0)
#define SOC_DSS_SBL_ENABLE_enable_END (0)
#define SOC_DSS_SBL_ENABLE_local_contrast_START (1)
#define SOC_DSS_SBL_ENABLE_local_contrast_END (2)
#define SOC_DSS_SBL_ENABLE_color_correction_START (4)
#define SOC_DSS_SBL_ENABLE_color_correction_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int strength : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_STRENGTH_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_strength_START (0)
#define SOC_DSS_SBL_STRENGTH_strength_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int variance_space : 4;
        unsigned int variance_intensity : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_UNION;
#endif
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_space_START (0)
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_space_END (3)
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_intensity_START (4)
#define SOC_DSS_SBL_VARIANCE_INTENSITY_SPACE_variance_intensity_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int slope_max : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_SLOPE_MAX_UNION;
#endif
#define SOC_DSS_SBL_SLOPE_MAX_slope_max_START (0)
#define SOC_DSS_SBL_SLOPE_MAX_slope_max_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int slope_min : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_SLOPE_MIN_UNION;
#endif
#define SOC_DSS_SBL_SLOPE_MIN_slope_min_START (0)
#define SOC_DSS_SBL_SLOPE_MIN_slope_min_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int black_level_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BLACK_LEVEL_L_UNION;
#endif
#define SOC_DSS_SBL_BLACK_LEVEL_L_black_level_l_START (0)
#define SOC_DSS_SBL_BLACK_LEVEL_L_black_level_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int black_level_h : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_SBL_BLACK_LEVEL_H_UNION;
#endif
#define SOC_DSS_SBL_BLACK_LEVEL_H_black_level_h_START (0)
#define SOC_DSS_SBL_BLACK_LEVEL_H_black_level_h_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int white_level_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_WHITE_LEVEL_L_UNION;
#endif
#define SOC_DSS_SBL_WHITE_LEVEL_L_white_level_l_START (0)
#define SOC_DSS_SBL_WHITE_LEVEL_L_white_level_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int white_level_h : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_SBL_WHITE_LEVEL_H_UNION;
#endif
#define SOC_DSS_SBL_WHITE_LEVEL_H_white_level_h_START (0)
#define SOC_DSS_SBL_WHITE_LEVEL_H_white_level_h_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dark_amp_limit : 4;
        unsigned int bright_amp_limit : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_UNION;
#endif
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_dark_amp_limit_START (0)
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_dark_amp_limit_END (3)
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_bright_amp_limit_START (4)
#define SOC_DSS_SBL_BRIGHT_DARK_AMP_LIMIT_bright_amp_limit_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dither_mode : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_DSS_SBL_DITHER_MODE_UNION;
#endif
#define SOC_DSS_SBL_DITHER_MODE_dither_mode_START (0)
#define SOC_DSS_SBL_DITHER_MODE_dither_mode_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int config_buffer_mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_DSS_SBL_CONFIG_BUFFER_MODE_UNION;
#endif
#define SOC_DSS_SBL_CONFIG_BUFFER_MODE_config_buffer_mode_START (0)
#define SOC_DSS_SBL_CONFIG_BUFFER_MODE_config_buffer_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int config_buffer_global : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_UNION;
#endif
#define SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_config_buffer_global_START (0)
#define SOC_DSS_SBL_CONFIG_BUFFER_GLOBAL_config_buffer_global_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int asymmetry_lut_addr : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_UNION;
#endif
#define SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_asymmetry_lut_addr_START (0)
#define SOC_DSS_SBL_ASYMMETRY_LUT_ADDR_asymmetry_lut_addr_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int asymmetry_lut_write_data_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_UNION;
#endif
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_asymmetry_lut_write_data_l_START (0)
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_L_asymmetry_lut_write_data_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int asymmetry_lut_write_data_h : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_UNION;
#endif
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_asymmetry_lut_write_data_h_START (0)
#define SOC_DSS_SBL_ASYMMETRY_LUT_WRITE_DATA_H_asymmetry_lut_write_data_h_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int color_correction_lut_addr : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_UNION;
#endif
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_color_correction_lut_addr_START (0)
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_ADDR_color_correction_lut_addr_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int color_correction_lut_write_data_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_UNION;
#endif
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_color_correction_lut_write_data_l_START (0)
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_L_color_correction_lut_write_data_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int color_correction_lut_write_data_h : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_UNION;
#endif
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_color_correction_lut_write_data_h_START (0)
#define SOC_DSS_SBL_COLOR_CORRECTION_LUT_WRITE_DATA_H_color_correction_lut_write_data_h_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int logo_left : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_LOGO_LEFT_UNION;
#endif
#define SOC_DSS_SBL_LOGO_LEFT_logo_left_START (0)
#define SOC_DSS_SBL_LOGO_LEFT_logo_left_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int logo_top : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_LOGO_TOP_UNION;
#endif
#define SOC_DSS_SBL_LOGO_TOP_logo_top_START (0)
#define SOC_DSS_SBL_LOGO_TOP_logo_top_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enable_dither : 1;
        unsigned int shift_mode : 1;
        unsigned int dither_amount : 2;
        unsigned int reserved_0 : 3;
        unsigned int dither_bypass : 1;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_DSS_SBL_APICAL_DITHER_UNION;
#endif
#define SOC_DSS_SBL_APICAL_DITHER_enable_dither_START (0)
#define SOC_DSS_SBL_APICAL_DITHER_enable_dither_END (0)
#define SOC_DSS_SBL_APICAL_DITHER_shift_mode_START (1)
#define SOC_DSS_SBL_APICAL_DITHER_shift_mode_END (1)
#define SOC_DSS_SBL_APICAL_DITHER_dither_amount_START (2)
#define SOC_DSS_SBL_APICAL_DITHER_dither_amount_END (3)
#define SOC_DSS_SBL_APICAL_DITHER_dither_bypass_START (7)
#define SOC_DSS_SBL_APICAL_DITHER_dither_bypass_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_sel : 1;
        unsigned int drc_sel : 1;
        unsigned int strength_sel : 1;
        unsigned int reserved_0 : 4;
        unsigned int automatic_start_calc : 1;
        unsigned int reserved_1 : 24;
    } reg;
} SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_UNION;
#endif
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_backlight_sel_START (0)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_backlight_sel_END (0)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_drc_sel_START (1)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_drc_sel_END (1)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_strength_sel_START (2)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_strength_sel_END (2)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_automatic_start_calc_START (7)
#define SOC_DSS_SBL_AUTOMATIC_START_CALC_STRENGTH_DRC_BACKLIGHT_SEL_automatic_start_calc_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int strength_manual : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_STRENGTH_MANUAL_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_MANUAL_strength_manual_START (0)
#define SOC_DSS_SBL_STRENGTH_MANUAL_strength_manual_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int drc_in_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_DRC_IN_L_UNION;
#endif
#define SOC_DSS_SBL_DRC_IN_L_drc_in_l_START (0)
#define SOC_DSS_SBL_DRC_IN_L_drc_in_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int drc_in_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_DRC_IN_H_UNION;
#endif
#define SOC_DSS_SBL_DRC_IN_H_drc_in_h_START (0)
#define SOC_DSS_SBL_DRC_IN_H_drc_in_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_L_backlight_l_START (0)
#define SOC_DSS_SBL_BACKLIGHT_L_backlight_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_H_backlight_h_START (0)
#define SOC_DSS_SBL_BACKLIGHT_H_backlight_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ambient_light_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_L_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_L_ambient_light_l_START (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_L_ambient_light_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ambient_light_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_H_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_H_ambient_light_h_START (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_H_ambient_light_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int start_calc : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_SBL_START_CALC_UNION;
#endif
#define SOC_DSS_SBL_START_CALC_start_calc_START (0)
#define SOC_DSS_SBL_START_CALC_start_calc_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int strength_limit : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_STRENGTH_LIMIT_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_LIMIT_strength_limit_START (0)
#define SOC_DSS_SBL_STRENGTH_LIMIT_strength_limit_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int calibration_a_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_CALIBRATION_A_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_A_L_calibration_a_l_START (0)
#define SOC_DSS_SBL_CALIBRATION_A_L_calibration_a_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int calibration_a_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_CALIBRATION_A_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_A_H_calibration_a_h_START (0)
#define SOC_DSS_SBL_CALIBRATION_A_H_calibration_a_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int calibration_b_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_CALIBRATION_B_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_B_L_calibration_b_l_START (0)
#define SOC_DSS_SBL_CALIBRATION_B_L_calibration_b_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int calibration_b_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_CALIBRATION_B_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_B_H_calibration_b_h_START (0)
#define SOC_DSS_SBL_CALIBRATION_B_H_calibration_b_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int calibration_c_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_CALIBRATION_C_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_C_L_calibration_c_l_START (0)
#define SOC_DSS_SBL_CALIBRATION_C_L_calibration_c_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int calibration_c_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_CALIBRATION_C_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_C_H_calibration_c_h_START (0)
#define SOC_DSS_SBL_CALIBRATION_C_H_calibration_c_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int calibration_d_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_CALIBRATION_D_L_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_D_L_calibration_d_l_START (0)
#define SOC_DSS_SBL_CALIBRATION_D_L_calibration_d_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int calibration_d_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_CALIBRATION_D_H_UNION;
#endif
#define SOC_DSS_SBL_CALIBRATION_D_H_calibration_d_h_START (0)
#define SOC_DSS_SBL_CALIBRATION_D_H_calibration_d_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t_filter_control : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_T_FILTER_CONTROL_UNION;
#endif
#define SOC_DSS_SBL_T_FILTER_CONTROL_t_filter_control_START (0)
#define SOC_DSS_SBL_T_FILTER_CONTROL_t_filter_control_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_min_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MIN_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MIN_L_backlight_min_l_START (0)
#define SOC_DSS_SBL_BACKLIGHT_MIN_L_backlight_min_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_min_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MIN_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MIN_H_backlight_min_h_START (0)
#define SOC_DSS_SBL_BACKLIGHT_MIN_H_backlight_min_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_max_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MAX_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MAX_L_backlight_max_l_START (0)
#define SOC_DSS_SBL_BACKLIGHT_MAX_L_backlight_max_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_max_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_MAX_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_MAX_H_backlight_max_h_START (0)
#define SOC_DSS_SBL_BACKLIGHT_MAX_H_backlight_max_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_scale_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_SCALE_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_SCALE_L_backlight_scale_l_START (0)
#define SOC_DSS_SBL_BACKLIGHT_SCALE_L_backlight_scale_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_scale_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_SCALE_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_SCALE_H_backlight_scale_h_START (0)
#define SOC_DSS_SBL_BACKLIGHT_SCALE_H_backlight_scale_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ambient_light_min_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_ambient_light_min_l_START (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_L_ambient_light_min_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ambient_light_min_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_UNION;
#endif
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_ambient_light_min_h_START (0)
#define SOC_DSS_SBL_AMBIENT_LIGHT_MIN_H_ambient_light_min_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filter_a_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_FILTER_A_L_UNION;
#endif
#define SOC_DSS_SBL_FILTER_A_L_filter_a_l_START (0)
#define SOC_DSS_SBL_FILTER_A_L_filter_a_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filter_a_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_FILTER_A_H_UNION;
#endif
#define SOC_DSS_SBL_FILTER_A_H_filter_a_h_START (0)
#define SOC_DSS_SBL_FILTER_A_H_filter_a_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filter_b : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_FILTER_B_UNION;
#endif
#define SOC_DSS_SBL_FILTER_B_filter_b_START (0)
#define SOC_DSS_SBL_FILTER_B_filter_b_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int strength_out : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_STRENGTH_OUT_UNION;
#endif
#define SOC_DSS_SBL_STRENGTH_OUT_strength_out_START (0)
#define SOC_DSS_SBL_STRENGTH_OUT_strength_out_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int drc_out_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_DRC_OUT_L_UNION;
#endif
#define SOC_DSS_SBL_DRC_OUT_L_drc_out_l_START (0)
#define SOC_DSS_SBL_DRC_OUT_L_drc_out_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int drc_out_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_DRC_OUT_H_UNION;
#endif
#define SOC_DSS_SBL_DRC_OUT_H_drc_out_h_START (0)
#define SOC_DSS_SBL_DRC_OUT_H_drc_out_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_out_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_OUT_L_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_OUT_L_backlight_out_l_START (0)
#define SOC_DSS_SBL_BACKLIGHT_OUT_L_backlight_out_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int backlight_out_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_BACKLIGHT_OUT_H_UNION;
#endif
#define SOC_DSS_SBL_BACKLIGHT_OUT_H_backlight_out_h_START (0)
#define SOC_DSS_SBL_BACKLIGHT_OUT_H_backlight_out_h_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int calc_done : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_SBL_CALC_DONE_UNION;
#endif
#define SOC_DSS_SBL_CALC_DONE_calc_done_START (0)
#define SOC_DSS_SBL_CALC_DONE_calc_done_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int al_calib_lut_lut_addr : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_UNION;
#endif
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_al_calib_lut_lut_addr_START (0)
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_ADDR_al_calib_lut_lut_addr_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int al_calib_lut_lut_write_data_l : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_UNION;
#endif
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_al_calib_lut_lut_write_data_l_START (0)
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_L_al_calib_lut_lut_write_data_l_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int al_calib_lut_lut_write_data_h : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_UNION;
#endif
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_al_calib_lut_lut_write_data_h_START (0)
#define SOC_DSS_SBL_AL_CALIB_LUT_LUT_WRITE_DATA_H_al_calib_lut_lut_write_data_h_END (7)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
