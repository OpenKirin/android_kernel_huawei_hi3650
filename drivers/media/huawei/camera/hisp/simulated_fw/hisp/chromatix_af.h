

#ifndef CHROMATIX_AF_H_INCLUDED
#define CHROMATIX_AF_H_INCLUDED

typedef enum _FOCUS_RANGE_E{
    RANGE_NORMAL_MODE = 0,
    RANGE_INFINITY_MODE,
    RANGE_MACRO_MODE,
} FOCUS_RANGE_E;

typedef struct {
    unsigned int face_win_size_th;
    unsigned int face_size;
    float face_win_edge_th;
    int  face_size_normal;
    int  face_size_big;
} af_face_param_t;

typedef struct {
    unsigned int flat_low_th;
    unsigned int flat_th;
    unsigned int small_win_contrast_th[6];
} af_flat_param_t;

typedef struct {
    unsigned int caf_stat_compare_start_frame;
    unsigned int caf_stat_compare_end_frame;
    unsigned int caf_stat_compare_start_frame_low;
    unsigned int caf_stat_compare_end_frame_low;

    unsigned int sumback_len;
    unsigned int stable_len;
    unsigned int motion_len;
    unsigned int continuous_motion_th;
    float angle_th;
    float motion_th_slow;
    float motion_th_fast;
    float big_angle_motion_th;

    unsigned int af_low_light_th;
    unsigned int af_video_low_light_th;
    unsigned int af_very_low_light_th;
    unsigned int af_dark_screen_th;
    unsigned int af_wait_ae_lum_th;
    unsigned int af_wait_ae_frame;
    unsigned int af_night_th;
    unsigned int video_scene_triggers_stable_cnt;

    unsigned int gyro_enable;                //1:gyro enable
    unsigned int gsen_stable_len;            //
    unsigned int gdiff_hold_th;              //motion->hold th
    unsigned int gdiff_mean_motion_th;       //hold->motion mean xyz diff th
    unsigned int gdiff_compare_motion_th;    //hold->motion compare xyz diff th

    int gdiff_th;
    unsigned int caf_stat_ae_unstable_extra_frames;
    int CurrToCurrContrastStableTH;
    int MeanToCompHistTH[4];
    int CurrToOldHistTH[4];
} af_trigger_param_t;

typedef struct {
    float light_slope_up_th;
    float light_slope_down_th;
    float light_slope_lowest_th;
    float contrast_slope_up_th;
    float contrast_slope_down_th;
    float contrast_slope_lowest_th;
    float contrast_size_slope_th;
} af_point_light_param_t;

typedef struct {
    unsigned int zone_top_th;
    unsigned int zone_full_win_top_ratio_th;
    unsigned int zone_full_win_top_ratio_th_mod;
} af_macro_param_t;

typedef struct {
    unsigned int af_full_low_contrast;
    unsigned int max_contrast;
    float normal_slope_one_level;
    float normal_slope_two_level;
    float normal_slope_three_level;
    unsigned int curve_multi_peak_slope;
    unsigned int enlarge_point_num_down;
    unsigned int enlarge_point_num_up;
    unsigned int zone_up_percent_105;
    unsigned int zone_up_percent_95;
    unsigned int zone_contrast_lowest;
    int wait_i2c;                   //ms
    unsigned int feature_cfg;
} af_taf_param_t;

typedef struct {
    float x_dist_btwn_pri_cam_and_laser;
    float y_dist_btwn_pri_cam_and_laser;
    float z_dist_btwn_pri_cam_and_laser;
    float x_dist_btwn_laser_sent_and_rece;
    float y_dist_btwn_laser_sent_and_rece;
    float pri_cam_effective_fov_x;
    float pri_cam_effective_fov_y;
    float laser_fov;
    float dual_camera_dist;
    unsigned int laser_mid_confidence_in_moving;
    unsigned int laser_mid_confidence_in_scene_changing;
    unsigned int laser_mid_confidence;
    float laser_alpha;
    unsigned int laser_enable;
    unsigned int dcamera_enable;
    unsigned int dcamera_mode;
    unsigned int camera_is_block;
} af_laser_param_t;

typedef struct {
    int mmi7cm_offset;
    unsigned int mmi7cm_search_range;
    unsigned int mmi7cm_wait_frames;
} af_mmi7cm_param_t;
typedef struct {
    /* should be calibrated by focus at infinite distance */
    unsigned int offsetInit;
    /* should be calibrated by focus at an macro distance */
    unsigned int fullRange;

    /* should be calibrated by focus at infinite distance */
    unsigned int infiniteDistance;

    unsigned int normalDistanceEnd;
    unsigned int normalStep;
    unsigned int normalStrideRatio;/* 0x10 is 1:1, 0x18 is 1:1.5, 0x20 is 1:2 */

    unsigned int videoDistanceEnd;
    unsigned int videoStep;
    unsigned int videoStrideRatio;

    unsigned int strideOffset;

    unsigned int coarseStep;
    unsigned int fineStep;/* half of coarseStep */

    /* response time, in unit of ms */
    unsigned int motorResTime;
    /* delay time of each step in stride divide case */
    unsigned int motorDelayTime;
    unsigned int strideDivideOffset;
    /*0:Auto; 1:Infinite; 2:Macro*/
    FOCUS_RANGE_E moveRange;
    unsigned int wait_ms;

    /* fast snap shot offset. */
    unsigned int fast_snapshot_offset;
    /* assistant af */
    unsigned int gainth_high;
    unsigned int trigger_lum_ratio;
    unsigned int expo_value_threshold;

    int single_frame_optimise;
    int pdaf_enable;

    int close_loop;
    float curve_slope;
    float curve_pint_light_slope;
    int point_light_thr;
    int point_light_num_mix;
    int contrast_threshold_percent;
    int focus_param_stat_threshold_percent;
    int night_ae_gain;
    int night_iso_medium;
    int night_fps;
    int contrast_th_for_small_win;
    int focus_param_judge_base_low;
    int focus_param_judge_base_high;
    int focus_param_ultralow_contrast;
    int focus_param_low_contrast;
    int focus_param_judge_error_mindiff;
    int focus_param_judge_error_minsteps;
    int focus_param_judge_low_contrast;
    int code_offset;
    int code_bd;
    float sensor_efl;
    int stagnate_code;
    int af_inf_dist;
    int af_macro_dist;
    float f_number;
    float sensor_delta;                     //radius of confusion circle
    int use_poseoffset;                     // 0: not use poseoffset ; 1:use
    int poseoffset_direction;               //0:horizon ; 1:upward ; -1:downward
    int max_codebd;
    int fast_face_code_use;
    af_face_param_t face_param;
    af_flat_param_t flat_param;
    af_trigger_param_t trigger_param;
    af_point_light_param_t point_light_param;
    af_macro_param_t macro_param;
    af_taf_param_t   taf_param;
    af_laser_param_t laser_param;
    af_mmi7cm_param_t af_mmi7cm_param;
} vcm_information_t;

typedef struct _af_calib_t
{
    vcm_information_t vcm_info;
} af_calib_t;

#endif /*CHROMATIX_AF_H_INCLUDED*/



