
#ifndef _CHROMATIX_AWB_H
#define _CHROMATIX_AWB_H
#include "algo_common.h"
#include "chromatix_cc.h"

#define AWBCALIBCOLORMAP_SIZE_W 75
#define AWBCALIBCOLORMAP_SIZE_H 60
#define AWBCOLORMAP_RG_START (awb_p->awb_calib_param->specialColorRgStart)  /*350*/
#define AWBCOLORMAP_BG_START (awb_p->awb_calib_param->specialColorBgStart)  /*250*/
//Note: this must be integer times of 2, to make it easy to find position on color map.
#define AWBCOLORMAP_GRID_WIDTH (awb_p->awb_calib_param->specialColorGridWidth) /*16*/

#define AWBPROBMAP_SIZE_W 75
#define AWBPROBMAP_SIZE_H 60
#define AWBPROBMAP_RG_RANGE_START (awb_p->awb_calib_param->probMapRgStart) /*328*/
#define AWBPROBMAP_BG_RANGE_START (awb_p->awb_calib_param->probMapBgStart) /*184*/

#define AWBPROBMAP_GRID_WIDTH (awb_p->awb_calib_param->probMapGridWidth) /*16*/


typedef HI_U8 AWBColorMapType[AWBCALIBCOLORMAP_SIZE_H][AWBCALIBCOLORMAP_SIZE_W] ;
/*!Two sets of parameters for indoor and outdoor, based on the EI value,
when brighter than outdoor EI, take outdoor info, when darker than indoor, take indoor config.
Take interpolation when EI is in the range [indoor_EI, outdoor_EI].
*/
typedef struct _AWB_special_color_offset{
    HI_U8 color_label;
    HI_U16 rg_factor;
    HI_U16 bg_factor;
    HI_U16 weight;
}AWB_SC_offset_struct;

#define AWB_NUM_SPECIAL_COLOR 4

//every color has indoor,outdoor scene mode.
//Note to have the same order with the Calibration tool.
typedef AWB_SC_offset_struct AWB_SC_offset_type[AWB_NUM_SPECIAL_COLOR][2];

typedef struct _AWB_colorMap_params{
    AWBColorMapType pColorMap;
    AWB_SC_offset_type offset;
}AWB_colorMap_params_struct;

//-------------------------------------------------------------
//Prob map
//--------------------------------------------------------------



typedef HI_U8 AWBPROBMAP_Matrix_type[AWBPROBMAP_SIZE_H][AWBPROBMAP_SIZE_W];

typedef struct _AWB_PROB_MAP_struct{
    AWBPROBMAP_Matrix_type outdoor;
    AWBPROBMAP_Matrix_type indoor;
    AWBPROBMAP_Matrix_type darkest;
}AWB_prob_map_struct;


//
typedef enum
{
    AWB_LIGHT_SUN_SHADE = 0,    //D75, or D80
    AWB_LIGHT_SUN_D65,            //D65,
    AWB_LIGHT_SUN_D50,            //D50
    AWB_LIGHT_SUN_SPECIAL,        //
    AWB_LIGHT_CANDLE,            //A,
    AWB_LIGHT_Hor,                //Horizon
    AWB_LIGHT_COOL_F,            //CWF
    AWB_LIGHT_WARM_F,            //TL84
    AWB_LIGHT_INDOOR_SPECIAL,    //
    MAX_AWB_REF_LIGHT,            //
    AWB_F_LIGHT,
    AWB_DAY_LIGHT,
    AWB_A_H_LIGHT,
    AWB_INVALID_LIGHT
}awb_light_type_enum;


#define N_CT_CAST_CCT 6
#define N_CT_CAST_BV 4
#define N_THRESH_PROB_BIN 16

typedef struct _light_thresh_prob{
    HI_U16    outdoor_prob[N_THRESH_PROB_BIN];
    HI_U16    indoor_prob[N_THRESH_PROB_BIN];
    HI_U16    darkest_prob[N_THRESH_PROB_BIN];
}light_thresh_prob;

typedef struct _awb_foliage_region_struct{
    HI_U16    GreenCenRG;
    HI_U16    GreenCenBG;
    HI_U16    GreenDistRGCoef;
    HI_U16    GreenDistBGCoef;
    HI_S16    GreenDistCrossCo;
    HI_U16  GreenDistThresh;
    HI_U16 GreenLumaMaxValu;
    HI_U16 GreenLumaMinValu;
}awb_foliage_region_struct;

typedef struct _awb_gray_region_struct{
    HI_S16  GrayZoneTopK;    //14bit; 1s3.10
    HI_S16    GrayZoneTopB;    //14bit; 1s3.10
    HI_S16    GrayZoneBottomK;//14bit; 1s3.10
    HI_S16    GrayZoneBottomB;//14bit; 1s3.10
    HI_S16    GrayZoneLeftK;    //14bit; 1s3.10
    HI_S16    GrayZoneLeftB;    //14bit; 1s3.10
    HI_S16    GrayZoneRightK;    //14bit; 1s3.10
    HI_S16    GrayZoneRightB;    //14bit; 1s3.10
    HI_U16  MinColorValue;    //12bit; 12.0
    HI_U16    MaxColorValue;    //12bit; 12.0
}awb_gray_region_struct;


typedef struct _light_thresh_type{
    HI_U16 outdoor_luma;
    HI_U16 indoor_luma;
    HI_U16 darkest_luma;
    HI_DOUBLE outdoor_prob_param;
    HI_DOUBLE indoor_prob_param;
    HI_DOUBLE darkest_prob_param;
}light_thresh_type;

typedef struct _light_weight_type{
    HI_U16 darkest_luma;
    HI_U16 brightest_luma;
    HI_U16 indoor_luma;
    HI_U16 outdoor_luma;
    HI_U16 mid_luma;
}light_weight_type;

typedef struct {
    struct_light_point        ref_light[MAX_AWB_REF_LIGHT];
    WB_gain_struct            otp_ref_gain;
    HI_U32                    dist_thresh;

    light_weight_type        light_weight[MAX_AWB_REF_LIGHT];
    HI_S32                        BvShift;

    HI_S32                        indoor_EI_value;
    HI_S32                        outdoor_EI_value;
    HI_S32                        minimum_EI_value;
    HI_S32                        maximum_EI_value;


    HI_S32                    Bv_ct_range_outdoor_high;
    HI_S32                    Bv_ct_range_outdoor_low;
    HI_S32                    Bv_ct_range_indoor_high;
    HI_S32                    Bv_ct_range_indoor_low;

    HI_U16                    outdoor_high_min_CT;
    HI_U16                    outdoor_high_max_CT;
    HI_U16                    outdoor_low_min_CT;
    HI_U16                    outdoor_low_max_CT;
    HI_U16                    indoor_high_min_CT;
    HI_U16                    indoor_high_max_CT;
    HI_U16                    indoor_low_min_CT;
    HI_U16                    indoor_low_max_CT;

    HI_S32                    green_scene_lowest_Bv_thresh;
    HI_S32                    green_scene_highest_Bv_thresh;
    HI_U32                    green_cen_to_calib_line_thresh;
    HI_U32                    green_ctrst_min;
    HI_U32                    green_ctrst_max;
    HI_U32                    outdoor_green_upper_thresh;
    HI_U32                    outdoor_green_lower_thresh;
    HI_U32                    green_shift_CCT_key[6];
    HI_S32                    green_shift_CCT_delta[6];

    struct_light_point        blue_sky_center;
    HI_U32                    blue_sky_min_luma;
    HI_U32                    sky_ctrst_thresh_strict;
    HI_U32                    sky_ctrst_thresh_easy;
    HI_U32                    sky_area_percent_thresh_strict;
    HI_U32                    sky_area_percent_thresh_easy;

    struct_light_point        skin_ref[MAX_AWB_REF_LIGHT];
    HI_S32                    skin_curve_coef[3];
    HI_S32                    skin_rg_conversion[2];
    HI_S32                    skin_bg_conversion[2];
    HI_U32        skin_dist_threshold;
    HI_U32        skin_valid_percent;
    HI_U32        maxWeightDecRatioForFaceColor;
    HI_U32        FaceUsingMode;

    HI_S32        green_line_coef[2];
    HI_S32        green_rg_conversion[2];
    HI_S32        green_bg_conversion[2];

    HI_FLOAT    rg2CCT_coef[4];
    HI_FLOAT    CCT2rg_coef[4];
    HI_FLOAT    rg_bg_2_x_coef[6];
    HI_FLOAT    rg_bg_2_y_coef[6];

    awb_gray_region_struct        gray_zone_line_kb;
    awb_gray_region_struct        all_color_line_kb;
    awb_foliage_region_struct     foliage_region_param;

    HI_U32        luma_range_threshold;
    HI_U32        luma_delta_threshold;
    HI_U32        wp_delta_threshold;
    HI_U32        BV_stable_range_threshold;
    HI_U32        BV_stable_range_ratio_threshold;

    HI_U32        luma_weight_max_value;
    HI_U32        Luma_weight_factor; //0~14, default: 9
    HI_U32        wp_num_weight_factor; //1~100, default: 10
    HI_U32        mass_center_weight_factor; //1~100, default: 1

    HI_U32          weight_for_pre_frame;
    HI_U32          weight_for_pre_LSC_wp;
    HI_U32          ACS_CCT_weight_range[2];
    HI_U32          ACS_CCT_weight_table[6];
    HI_U32          ACS_Bv_weight_table[6];
    HI_U32          ACS_valid_thresh;
    HI_U32          ACS_local_dir_thresh;
    HI_U32          ACS_steady_thresh;

    HI_U16               cast_CCT[N_CT_CAST_CCT];
    HI_DOUBLE        cast_vector[N_CT_CAST_CCT][N_CT_CAST_BV][3];
    HI_U16               off_locus_up_CT_range[N_CT_CAST_CCT];
    HI_DOUBLE        off_locus_up_shift_vector[N_CT_CAST_CCT][N_CT_CAST_BV][3];
    HI_U16               off_locus_down_CT_range[N_CT_CAST_CCT];
    HI_DOUBLE        off_locus_down_shift_vector[N_CT_CAST_CCT][N_CT_CAST_BV][3];
    HI_U32		specialColorRgStart;
    HI_U32		specialColorBgStart;
    HI_U32		specialColorGridWidth;
    HI_U32		probMapRgStart;
    HI_U32		probMapBgStart;
    HI_U32		probMapGridWidth;
    HI_S32		ReservedParams[2000];
    HI_U32              AWB_alg_version;

    AWB_colorMap_params_struct awb_calib_colorMap;
    AWB_prob_map_struct awb_prob_map_data;
}awb_calib_param_type;

typedef struct _AWB_reg_config_from_fw AWB_reg_config_from_fw;

typedef struct _AWB_running_input_struct awb_runing_input_struct;
typedef struct _awb_run_param_type awb_run_param_type;

#ifdef CODE_ON_PC_PLATFORM
/* 3A stat structure */
typedef struct awb_stat_c
{
    unsigned int ysumstat[1024];
    unsigned int rgsumstat[1024];
    unsigned int bgsumstat[1024];
    unsigned int ctrstsumstat[1024];
    unsigned int countsumstat[1024];
    unsigned int yavgsumstat[1024];
    int green_gravity_rg;
    int green_gravity_bg;
    unsigned int green_count;
    unsigned int r_hist[64];
    unsigned int g_hist[64];
    unsigned int b_hist[64];
} awb_stat_t;
#endif

HI_S32 awb_core_init(awb_runing_input_struct* awb_input, awb_run_param_type* awb_p, awb_calib_param_type* awb_calib_param);
HI_S32 awb_core_exec(awb_runing_input_struct* awb_input, awb_run_param_type* awb_p);
HI_S32 awb_core_prepare(awb_run_param_type* awb_p, awb_runing_input_struct* awb_input);
HI_S32 awb_core_deinit(awb_run_param_type* awb_p);
HI_S32 awb_core_set_stats_info(awb_run_param_type* awb_p, awb_runing_input_struct* awb_input,
            awb_stat_t* stat_info,  HI_U32 bIsGrayZone, face_pos_struct* face_pos);
HI_S32 awb_core_get_reg_config(awb_run_param_type* awb_p, AWB_reg_config_from_fw* ref_config, HI_U32 bIsGrayZone);
HI_S32 awb_core_set_user_CCT(awb_runing_input_struct* awb_input, awb_run_param_type* awb_p, HI_U32 CCT_value, HI_U32 CCT_shift);
HI_S32 awb_core_get_gain_for_flash(awb_run_param_type* awb_p, awb_runing_input_struct* awb_input,
            WB_gain_struct* wb_gain, struct_light_point* wp_for_cc);
HI_S32 awb_core_custom_region_awb(awb_runing_input_struct* awb_input, awb_run_param_type* awb_p, HI_U32 start_row,
            HI_U32 start_col, HI_U32 width, HI_U32 height, WB_gain_struct* wb_gain, struct_light_point* wp_for_cc);
								  
#endif
