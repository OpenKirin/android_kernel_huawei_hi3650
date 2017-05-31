
#ifndef _CHROMATIX_AE_H
#define _CHROMATIX_AE_H

#include "algo_common.h"

#define WEIGHT_MAT_HEIGHT        16
#define WEIGHT_MAT_WIDTH         16
#define WEIGHT_MAT_LENGTH        (WEIGHT_MAT_HEIGHT * WEIGHT_MAT_WIDTH) /* 16x16 */

#define N_LV_ZONE 10   //number of LV zone
#define N_CM_ZONE 5    //number of center mean zone
#define N_BR_ZONE 7    //number of bright ratio zone
#define N_DR_ZONE 2    //number of dark ratio zone
#define N_EV_ZONE 4    //number of EV zone
#define N_RW_ZONE 5    //number of range width zone
#define N_LR_ZONE 5    //number of luma ratio zone
#define N_CR_ZONE 4    //number of color ratio zone
#define N_LD_ZONE 5    // number of luma diff zone
#define N_FL_ZONE 6   //number of EV zone for face luma
#define N_TL_ZONE 6   //number of EV zone for touch luma

typedef struct _aec_touch_type
{
    HI_U32   touch_roi_enable;
    HI_FLOAT touch_roi_weight;
    HI_U32   aec_touch_target;
    HI_U32   LV_zone[N_TL_ZONE];
    HI_S32   touch_target_shift[N_TL_ZONE];
}aec_touch_type;
typedef struct _aec_face_type
{
    HI_U32   aec_face_enable;
    HI_FLOAT aec_max_face_weight;
    HI_FLOAT aec_min_face_weight;
    HI_FLOAT aec_max_face_ratio;
    HI_FLOAT aec_min_face_ratio;
    HI_U32   aec_face_target;
    HI_U32   LV_zone[N_FL_ZONE];
    HI_S32   face_target_shift[N_FL_ZONE];
    HI_U32   face_step;
    HI_FLOAT face_size_coeff;
    HI_U32   max_face_existed_num;
    HI_U32   max_face_disappear_num;
    HI_U32   face_in_center_enable;
}aec_face_type;
typedef struct _aec_tolerance_type{
    HI_U32  ae_tolerance1; //unstable to stable in SCENE_NORMAL
    HI_U32  ae_tolerance2; //stable to unstable in SCENE_NORMAL
    HI_U32  ae_tolerance3; //unstable to stable in SCENE_SINGLE_PEAK
    HI_U32  ae_tolerance4; //stable to unstable in SCENE_SINGLE_PEAK
} aec_tolerance_type;

typedef struct _aec_center_type{
    HI_U32  center_row_start;
    HI_U32  center_row_end;
    HI_U32  center_col_start;
    HI_U32  center_col_end;
} aec_center_type;

typedef struct {
    float default_max_bright_ratio;
    float default_min_bright_ratio;
    int default_bright_thd;
}ae_histogram_control;

typedef struct {
    float max_bright_percent;
    float min_bright_percent;
    float adj_min_ratio;
    int   bright_thd;
}ae_center_control;

typedef struct {
    int max_adjust_target;
}ae_histogram_under_control;

typedef struct {
    ae_histogram_control histogram_control;
    ae_center_control center_control;
    ae_histogram_under_control histogram_under_control;

    int target_luma_max;
    int target_luma_min;
}ae_matrix_calib;

typedef struct {
    int expo;
    int gain;
} expo_data_t;

typedef struct {
    int    face_flag;
    int    face_luma;
    float  face_weight;
    int    non_face_luma;
} aeParamForGamma_t;

/*****************************************************************************
                   AE Calibrate or Set Parameter Structure
*******************************************************************************/
typedef struct _ae_calibration_struct{
    HI_U32              ae_target;
    HI_U32              ois_ae_target;
    HI_U32              weight_matrix[WEIGHT_MAT_LENGTH];
    HI_U32              cwa_weight_matrix[WEIGHT_MAT_LENGTH];
    HI_FLOAT            bright_weight_mat[WEIGHT_MAT_LENGTH];
    HI_FLOAT            dark_weight_mat[WEIGHT_MAT_LENGTH];
    HI_U32              LV_zone[N_LV_ZONE];
    HI_S32              ae_target_shift[N_LV_ZONE];
    HI_U32              EV_zone[N_EV_ZONE];
    HI_FLOAT            iThresholdB[N_EV_ZONE];
    HI_FLOAT            iThresholdD[N_EV_ZONE];
    HI_U32              range_width_zone[N_RW_ZONE];
    HI_FLOAT            iThresholdC[N_RW_ZONE];
    HI_FLOAT            ratio_bright_zone[N_BR_ZONE];
    HI_U32              bright_target_adjust[N_BR_ZONE];
    HI_FLOAT            ratio_bright_compensation_zone[N_LR_ZONE];
    HI_U32              bright_compensation_zone[N_LR_ZONE];
    HI_FLOAT            ratio_dark_compensation_zone[N_DR_ZONE];
    HI_U32              dark_compensation_zone[N_DR_ZONE];
    HI_U32              CM_zone[N_CM_ZONE];
    HI_U32              lowrange_damping_ev;
    HI_U32              Luma_Diff_zone[N_LD_ZONE];
    HI_FLOAT            Step_zone[N_LD_ZONE];
    HI_FLOAT            spot_roi_weight;
    aec_touch_type      aec_touch;
    aec_face_type       aec_face;
    aec_tolerance_type  ae_tolerance;
    aec_center_type     aec_center_region;
    HI_U32              peak_thd_bit;
    HI_U32              sub_bright_pixel_thd_bit;
    HI_FLOAT            center_variance_thd;
    HI_U32              target_min_thd;
    HI_U32              luma_diff_thd;
    HI_U32              low_range_thd;
    HI_U32              center_luma_thd;
    HI_FLOAT            bright_ratio_thd;
    HI_U32              peak_width;

    HI_U8               sensor_type;
    HI_U32              aperture;   /* Fno = aperture / 100 */
    HI_U32              iso_calibration;
    HI_U8               expo_type;  /* 0:expo line, 1:macro second us */
    HI_U32              default_expo;
    HI_U32              default_gain;
    HI_U32              step;
    HI_U32              group_hold;
    HI_U32              min_preview_fps;
    HI_U32              min_gain;
    HI_U32              max_gain_capture;
    HI_U32              max_gain_h_video;
    HI_U32              max_gain_video;
    HI_U32              min_gain_profession_camera;
    HI_U32              max_gain_profession_camera;
    HI_U32              max_expo_capture;
    HI_FLOAT            cut_off_percentage;
    HI_S32              max_brightness;

    expo_data_t         expo_table_50Hz[20];
    expo_data_t         expo_table_60Hz[20];

    ae_matrix_calib     matrix_param;

    HI_S32              Reserved1[35];
    HI_FLOAT            Reserved2[19];
}ae_calibration_struct;

#endif
