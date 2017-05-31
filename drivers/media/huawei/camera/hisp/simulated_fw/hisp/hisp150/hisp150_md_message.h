
#ifndef __HISP150_MD_MESSAGE_H__
#define __HISP150_MD_MESSAGE_H__

#include "hisp/hisp150/chromatix.h"

/*****************************************************************************
                  Histar_ISP Algo Extend_Cmd Message
*******************************************************************************/

#define MAX_SENSOR_INFO    (7)
#define MAX_EV_SEQUENCE_SUPPORTED  60 /* left+right max group is 60 */
#define CAP_EV_SEQUENCE_SUPPORTED  (20)
#define GAMMA_CURVE_NUM         129
#define CC_MATRIX_NUM           12
#define MAX_AF_EXIF_INFO_SIZE   800
#define MAX_AF_DATA_SIZE        256
#define MAX_LOG_SIZE            800
#define FACE_MAX_NUM            5
#define MAX_VCM_CODE_SIZE       18
#define LANDMARK_POINT          5
#define INVALID_THERMAL_METER   127
#define PIPELINE_COUNT          (2)
#define OIS_CALIB_DATA_LENGTH   92
#define OIS_DATA_MAX 10

typedef enum
{
    AWB_OFF=0,
    AWB_AUTO,
    INCANDESCENT,
    FLUORESCENT,
    WARM_FLUORESCENT,
    DAYLIGHT,
    CLOUDY_DAYLIGHT,
    TWILIGHT,
    SHADE
}subcmd_awb_mode_enum;// ?

// typedef enum{
//     NOT_USE_MANUAL_PARAM = 0,
//     USE_MANUAL_PARAM = 1,
//     BYPASS_PARAM = 2,
// }use_manual_param_e;//?

enum {
    CAMERA_PREVIEW = 0,
    CAMERA_CAPTURE,
    CAMERA_VIDEO,
    CAMERA_VIDEOSNAPSHOT,
    CAMERA_VIDEO_RECORDING,
};//?

enum {
    ISP_DDR_VOTE_NONE  = 0,
    ISP_DDR_VOTE_VBLANK_MIN,   //need ddr vote max to ensure isp capture sensor frame when vblank < 650us
    ISP_DDR_VOTE_VBLANK_UNDER, //need ddr vote to ensure performance when vblank at [2ms-3ms]
};//?
typedef struct _face_rect_t {
    unsigned int left;
    unsigned int top;
    unsigned int width;
    unsigned int height;
} face_rect_t;//?

typedef struct _face_win_info_t{
    face_rect_t face_area[FACE_MAX_NUM];
    unsigned short width;
    unsigned short height;
    unsigned char face_num;
    unsigned char index_max_face;
}face_win_info_t;//?

typedef struct _landmark_poit_t {
    int32_t x;
    int32_t y;
} landmark_point_t;//?

typedef struct _face_landmark_t {
    landmark_point_t left_eye[LANDMARK_POINT];
    landmark_point_t right_eye[LANDMARK_POINT];
    landmark_point_t mouth[LANDMARK_POINT];
} face_landmark_t;//?

typedef struct
{
    unsigned int rgain; //256 base
    unsigned int ggain; //256 base
    unsigned int bgain; //256 base
    unsigned int mode;  //0-auto;1-manual
} manualAwbParam;//?

typedef struct normal_capture_params_t {
    unsigned int flash_state;  //0-no flash;1-with flash
    unsigned int motion_state; //0-no motion detected;1-motion detected
    manualAwbParam awb;
} normal_capture_params_t;//?

typedef struct multidenoise_params_t {
    unsigned int double_iso;// only for single camera
    unsigned int frame_count[2];//0 for primary camera;1 for secondary
    unsigned int max_expo[2];//0 for primary camera;1 for secondary
    unsigned int max_iso[2];//0 for primary camera;1 for secondary
} multidenoise_params_t;

typedef struct manual_ae_params_t {
    unsigned short mode;
    unsigned int effect_immediately;
    unsigned int ae_count[2]; /* for 1 camera, only ae_count[0] is valid */

    union {
        struct {
            unsigned int max_expo;    /* unit: us */
            unsigned int expo[MAX_EV_SEQUENCE_SUPPORTED];
            unsigned short iso[MAX_EV_SEQUENCE_SUPPORTED];
        };
        struct {
            uint32_t binningRatio;
            multidenoise_params_t multidenoise;
        };
    };
} manual_ae_params_t;//?

typedef struct manual_cap_ae_params_t
{
    unsigned int max_expo;    /* unit: us */
    unsigned int ae_count[2]; /* for 1 camera, only ae_count[0] is valid */
    unsigned int expo[CAP_EV_SEQUENCE_SUPPORTED];
    unsigned short iso[CAP_EV_SEQUENCE_SUPPORTED];
    unsigned int effect_immediately;
} manual_cap_ae_params_t;

typedef struct bracket_ev_params_t {
    unsigned int ev_count[2]; /* for 1 camera, only ev_count[0] is valid */
    int ev[CAP_EV_SEQUENCE_SUPPORTED]; /* for example: 20 is +2, 1 is 0.1, -1 is -0.1 */
} bracket_ev_params_t;//?

typedef struct superzoom_params_t {
    rect2_info_t crop_region;
    int sharpen_level; /* level 0 is lowest, reserved */
    int denoise_level;  /* level 0 is lowest, reserved */
    int stride;
} superzoom_params_t;//?

typedef enum
{
    FLOW_INSTANCE_PREVIEW = 0,
    FLOW_INSTANCE_CAPTURE = 1,
    FLOW_INSTANCE_MAX,
} flow_instance_e;

typedef struct {
    uint32_t cam_id;
    unsigned int target_stream;   //bit offset: 1 means need stream config
    unsigned int on[FLOW_INSTANCE_MAX];   //0 - off  1- on
} algo_switch_t;

typedef struct {
    algo_switch_t algo_switch[PIPELINE_COUNT];
} subcmd_algo_switch_t;

typedef struct manual_focus_params_t {
    unsigned int vcm_code;
} manual_focus_params_t;

typedef struct otp_ae_params_t {
    unsigned int expo;
    unsigned int gain;
} otp_ae_params_t;

typedef struct _sequence_manual_focus_params_t {
    unsigned int vcm_count;//valid vcm code size
    int  vcm_code[MAX_VCM_CODE_SIZE];
} sequence_manual_focus_params_t;

typedef enum {
    MODE_NORMAL = 0,
    MODE_MANUAL,
    MODE_BRACKET,
    MODE_SUPERZOOM,
    MODE_MULTI_DENOISE,
    MODE_MANUAL_FOCUS,
    MODE_OTP,
    MODE_SEQUENCE_MANUAL_FOCUS,
    MODE_RESUME_SELECT,
} capture_mode_e;

/* crop_region_info_t */
typedef struct _crop_region_info_t
{
    unsigned int   x;
    unsigned int   y;
    unsigned int   width;
    unsigned int   height;
} crop_region_info_t;

typedef enum capture_stream_mode {
    STREAM_NORMAL,
    STREAM_LOSSLESS,
} capture_stream_mode_t;

typedef struct stream_resolution {
    unsigned int width;
    unsigned int height;
} stream_resolution_t;

typedef struct capture_stream_info {
    capture_stream_mode_t stream_mode;

    unsigned int cam_id;
    unsigned int stride;
    union {
        stream_resolution_t resolution;
        crop_region_info_t crop_region;
    };
} capture_stream_info_t;

typedef struct capture_streams {
    capture_stream_info_t info[PIPELINE_COUNT];
    unsigned int count;
} capture_streams_t;

typedef struct capture_params_t {
    unsigned int flow;//camera_flow_e
    unsigned int mode;//capture_mode_e
    capture_streams_t streams;

    union {
        normal_capture_params_t normal_params;
        manual_cap_ae_params_t manual_ae;
        bracket_ev_params_t bracket_ev;
        superzoom_params_t sz;
        multidenoise_params_t multidenoise;
        manual_focus_params_t manual_focus;
        otp_ae_params_t otp;
        sequence_manual_focus_params_t sequence_manual_focus;
    };

} capture_params_t;

typedef struct _af_trigger_t {
    unsigned char afTrigger;
    int afTriggerId;
} af_trigger_t;

typedef struct _ae_trigger_t {
    unsigned char aeTrigger;
    int aeTriggerId;
} ae_trigger_t;

typedef struct
{
    unsigned int flow;
    unsigned int value[2];
} ae_manual_t;

typedef struct
{
    unsigned int flow;//camera_flow_e
    int value[2];
} ae_expo_compensation_t;

typedef struct {
    unsigned int expo; //unit is us.
    unsigned short iso; //example: 50-ISO50
} aeParam;

typedef struct {
    unsigned int expo; //unit is us.
    unsigned short iso; //example: 50-ISO50
    unsigned int gain;//
    unsigned int bv;//
} aeExtParam;

typedef struct {
    unsigned int rgain; //256 base, 0x400 is 1x
    unsigned int ggain; //256 base
    unsigned int bgain; //256 base
} awbParam;

typedef struct {
    unsigned int module; //0-AE;1-AWB;2-AF;3-reserved
    union
    {
        aeParam  ae;
        awbParam awb;
    };
} resume3AParam;

typedef enum {
    AF_MMI_10CM = 0,
    AF_MMI_PDAF,
    AF_MMI_AFC,
    AF_MMI_DCC,
} af_mmi_mode_e;

typedef struct _af_mmi_debug_info_t {
    af_mmi_mode_e   type;
    unsigned int    sec;
    unsigned int    us;
    int             contrast[2];
    int             vcm_code;
} af_mmi_debug_info_t;

typedef struct _sensor_axis_triple {
    int x;
    int y;
    int z;
} sensor_axis_triple;

enum {
    SENSOR_GYR_DX  = 0,
    SENSOR_GYR_DY,
    SENSOR_GYR_DZ,
    SENSOR_GYR_MAX,
};

typedef struct _sensor_gyro_t {
    float data[SENSOR_GYR_MAX];
} sensor_gyro;

typedef struct _motionsensor_info {
    unsigned int                  gsensor_n;    //valid axis info count
    sensor_axis_triple            gsensor[MAX_SENSOR_INFO];
    unsigned int                  asensor_n;    //valid asensor info count
    sensor_axis_triple            asensor[MAX_SENSOR_INFO];
    unsigned int                  gyro_n;       //valid axis info count
    sensor_gyro                   gyro[MAX_SENSOR_INFO];
} motionsensor_info_t;

typedef struct
{
    unsigned int damping_weight;
    unsigned int luma_range_threshold;
    unsigned int luma_delta_threshold;
    unsigned int wp_delta_threshold;
    unsigned int BV_stable_range_threshold;
    unsigned int BV_stable_range_ratio_threshold;
} awbDampingParam;

typedef struct
{
    unsigned int gamma_type;
    unsigned int gamma_curve_pn;
    unsigned short gamma_curve[GAMMA_CURVE_NUM];
} gammaCurveParam;

typedef struct
{
    unsigned int ccmEn;   // CCM Enable
    unsigned int flareRmvEn;  // Flare Removal Enable
    unsigned int histEn;   // Hist Get Enable
    unsigned int ykptCstEn;  // YKpt Const Enable
    unsigned int ccmSatLmEn;  // CCM Sat Illum En
    unsigned int ccmAdtLmEn;  // CCM Adt Luma En
    unsigned int ccmSat;   // Chroma_Calib_CCM_Sat
    unsigned int sceSat;   // Chroma_Calib_SCE_Sat
} ccParam;

typedef struct
{
    unsigned int ct;
    unsigned int illuminance;
    unsigned short ccmatrix[CC_MATRIX_NUM];
} ccMatrixParam;

typedef struct
{
    int expo[2];
    int gain[2];
    int lum[2];
    unsigned int sat_cnt;
    unsigned int green_cnt;
    unsigned int blue_cnt;
    unsigned char color_info_buf[256];
} aeYuvStatInfo;

typedef struct
{
    unsigned int motion_lv;
    unsigned int motion_state;
} motion_info_t;

/*****************************************************************************
                  Histar_ISP 150 Metadata Struct
*******************************************************************************/
#define RDN_DEBUG_INFO_LENGTH       32
#define YUVDN_DEBUG_INFO_LENGTH     32
#define SHARPEN_DEBUG_INFO_LENGTH   32
#define CC_DEBUG_INFO_LENGTH        64
#define CE_DEBUG_INFO_LENGTH        32
#define GAMMA_DEBUG_INFO_LENGTH     144
#define DRC_DEBUG_INFO_LENGTH       152
#define AWB_DEBUG_INFO_LENGTH       800
#define AF_DEBUG_INFO_LENGTH        3604
#define FACE_MAX_NUM                5
#define LANDMARK_POINT              5
#define INVALID_THERMAL_METER       127
#define OIS_CALIB_DATA_LENGTH       92
#define AE_DEBUG_INFO_LENGTH        800
#define FLASH_DEBUG_INFO_LENGTH     64
#define ARSR_DEBUG_INFO_LENGTH      112
#define RAWNF_EXIF_INFO_LENGTH      32
#define PDAF_EXIF_INFO_LENGTH       560
#define MAX_CAM_NUM                 3
#define MAX_COP_CAM_CNT     2

typedef enum
{
    STAND_ALONE_MODE = 0,
    MASTER_SLAVE_MODE = 1,
    MAX_MODE_CAM,
}multi_cam_mode_e;

typedef struct _usecase_init_param_t
{
    multi_cam_mode_e multi_cam_mode;
    unsigned int master_cam_id;
    unsigned int slave_cam_id[MAX_COP_CAM_CNT - 1];
    unsigned int slave_cam_cnt;
}usecase_init_param_t;

/* common_info_md_t ,in hispv150 is com_md_t,
 * mono_mode <-->mono_mode
 */
typedef struct
{
    unsigned int raw_width;
    unsigned int raw_height;
    bayer_pattern_e raw_pattern;//bayer_pattern_e
    unsigned int mono_mode;//reuse bayer_pattern_e????
    int          reserved[11];
} common_info_md_t;

/* blc  metadata */
typedef struct
{
    char    module_name[16];//#&@_blc
    int       reserved[8];
} blc_md_t;

/* state 3A */
typedef struct _awb_md_zone_struct
{
    unsigned int      rg;
    unsigned int      bg;
    unsigned int      faceRatio_num; //merge face_area_ratio and num
    unsigned int      sum_y;
    unsigned int      ctrst;
    //unsigned char   face_area_ratio; //8     unsigned,Read only
} awb_md_zone_struct;

typedef struct _awb_stat_for_md
{
    awb_md_zone_struct awb_zone_info[AWB_BLOCK_NUM_H* AWB_BLOCK_NUM_V];
    unsigned int yavgsumstat[AWB_BLOCK_NUM_H* AWB_BLOCK_NUM_V];
    unsigned int green_gravity_rg;
    unsigned int green_gravity_bg;
    unsigned int green_count;
    unsigned int r_hist[AWB_HISTOGRAM_NUM];
    unsigned int g_hist[AWB_HISTOGRAM_NUM];
    unsigned int b_hist[AWB_HISTOGRAM_NUM];
} awb_stat_for_md_t;

typedef struct _stat3a_md
{
    char module_name[16];
    awb_stat_for_md_t awb_stat;
    unsigned char reserved[4];
    // ae_stat_t  ae_stat; //was defined in ref_io
    // af_stat_t  af_stat;
} stat3a_md_t;

/* for  dgamma_md_t
 * in hispv150 is dgamma_md_t*/
typedef struct _dgamma_md_t
{
    int data[96][3][4];
    int reserved[32];
} dgamma_info_t;

/* for  dpcc_md  */
typedef struct _dpcc_md_t
{
    int reserved[4];
} dpcc_info_t;

/* for  gcd_md_t   */
typedef struct _gcd_md_t
{
    unsigned int reserved[16];
} gcd_info_t;

/* for tnr_md   */
typedef struct _tnr_md_t
{
    char reserved[8];
} tnr_md_t;

/* for ae_md_t   */
typedef struct _ae_md_t
{
    exposure_param_struct exposure_param;
}ae_md_t;

typedef struct {
    /**** 4 bytes ****/
    unsigned char   target;
    unsigned char   non_smooth_target;
    unsigned char   imean_ref;
    unsigned char   cur_lum;

    unsigned char   avg_lum;
    unsigned char   schedule_case;
    unsigned char   metering_mode;
    unsigned char   target_state;

    short   LV;
    unsigned char   ae_stable;
    unsigned char   scene_stable;

    unsigned int    expo;

    unsigned short  ad_gain;
    short           scene_cmp;

    unsigned char   hist_under_value;
    unsigned char   hist_over_value;
    short           hist_cmp;

    short           hist_max_cmp;
    short           hist_min_cmp;

    unsigned char   hist_bright_zone_avg;
    char            hist_bright_zone_weight;
    unsigned char   face_lum;
    char            motion_state;

    char            expo_prefer;
    unsigned char   reserved_char[7];
} ae_algo_status;//40bytes

typedef struct {
    ae_algo_status  ae_algo_info[AE_DEBUG_QUEUE_CNT];  // 40 * 8 = 320bytes
    /*** 4 bytes ***/
    unsigned char   hist_over_thd;
    unsigned char   hist_under_thd;
    unsigned short  hist_over_cnt;

    unsigned short  hist_under_cnt;
    short           algo_stable_cmp;

    short           algo_final_cmp;
    unsigned char   over_sat_scene;
    unsigned char   over_sat_stable;

    unsigned short  over_sat_cnt;
    unsigned short  over_sat_value;

    unsigned short  over_sat_stable_value;
    unsigned char   blue_scene;
    unsigned char   blue_stable;

    unsigned short  blue_cnt;
    unsigned short  blue_value;

    unsigned short  blue_stable_value;
    unsigned char   green_scene;
    unsigned char   green_stable;

    unsigned short  green_cnt;
    unsigned short  green_value;

    unsigned short  green_stable_value;
    short           ap_algo_ev_cmp;

    short           metering_ev_cmp;
    short           otp_iso;

    short           otp_gain_g;
    short           min_iso;

    unsigned char   default_target;
    unsigned char   dynamic_lum;
    unsigned char   weight_lum;
    unsigned char   touch_on_face;

    int otp_iso_expo;

    short otp_iso_comp;
    short           otp_calib_target;

    unsigned short otp_sat_gain;
    short           diff_ev;
} ae_final_status;//380 bytes

typedef struct {
    unsigned short  face_frame_coeff;
    unsigned short  face_weigh;

    unsigned char   face_base_target;
    unsigned char   face_target;
    unsigned char   face_mean;
    unsigned char   non_face_mean;

    unsigned char   reserved_char[12];
} face_ae_report;//20 bytes

typedef struct {
    short           touch_weight;
    unsigned short  touch_roi_mean;

    unsigned short  touch_top_x;
    unsigned short  touch_top_y;

    unsigned short  touch_area_width;
    unsigned short  touch_area_height;

    unsigned char   touch_base_target;
    unsigned char   touch_target_shift;
    unsigned char   non_touch_mean;
    unsigned char   reserved_char[5];
} touch_ae_info;//20 bytes

typedef struct {
    ae_final_status ae_status;    //380 bytes
    unsigned char   ae_block_data[256]; //256 bytes
    face_ae_report  face_info;          //20 bytes
    touch_ae_info   touch_info;         //20 bytes

    short           flash_turn_on;
    unsigned short  ae_target_mean;
    unsigned short   meter_table_width;
    unsigned short   meter_table_height;

    unsigned char   face_ae;
    unsigned char   touch_ae;
    unsigned char   capture_type;
    unsigned char   reserved_char[13];
} ae_info;//800 bytes

/* for awb_md */
typedef enum _awb_converge_mode_e
{
    AWB_FAST_CONVERGE = 0,
    AWB_SLOW_CONVERGE,
} awb_converge_mode_e;


typedef struct
{
    unsigned int    green_ratio;
    int    g_cen_rg;
    int    g_cen_bg;
    unsigned int  to_gray_rg;
    unsigned int  to_gray_bg;
    unsigned int    to_gray_ct;
} green_info_t;

typedef struct _awb_exif_t
{
    HI_U8                   awb_md_pilot[8];//8
    HI_U16                    bAWB_manual;
    HI_S16                  BV_value;
    HI_U16                    nUniColorBlks;
    HI_U16                    nDeletedBlksByUniColor;//16
    struct_light_point      awb_otp_gain;
    struct_light_point        uniColorCenter;//24
    green_info_t        green_info;//48
    HI_U16                  skyF_sum_sky_points;
    HI_U16                  skyF_n_sky_line;
    HI_S32                    skyF_fit_blue_line_k;//56
    HI_U16                  skyF_mass_points_var;
    HI_U16                  skyF_avg_contrast;
    HI_S32                    skyF_fit_blue_line_b;//64
    HI_U16                  skyF_d_calib_blue_to_mass;
    HI_U16                  skyF_blue_sky_prob;
    HI_U16                  skyF_must_be_sky_prob;
    HI_U16                    n_gray_blocks;//72
    struct_light_point      rg_bg_before_any_shift;
    struct_light_point        mass_cloud_pt;//80
    HI_U16                    n_valid_blocks;
    HI_U16                    bDecWeightForNearFace;
    HI_U16                    mass_ratio;
    HI_U16                    isGoodDistHist;//88
    HI_U32                    wp_on_ref_line[AWB_EXIF_WEIGHTED_LINE_PTS];//208
    HI_U32                    weight_on_ref_line[AWB_EXIF_WEIGHTED_LINE_PTS];//328
    HI_U16                    CCT_range[2];
    HI_U32                    max_wp_of_light_center;//336
    struct_light_point        face_coarse_avg;
    struct_light_point       rg_bg_light_syn;//344
    HI_U16                    n_valid_skin_blks;
    HI_U16                    nCount_all_Skin_Pixels;
    HI_U16                    nPixel_high_for_face;
    HI_U16                    nPixel_low_for_face;//352
    HI_U16                    face_pixels_ratio;
    HI_S16                    face_dt1;
    HI_S16                    face_dt2;
    HI_U16                    face_ratio_before_unicolor;//360
    HI_U16                    face_ratio_after_unicolor;
    HI_U16                    face_ratio_after_sky;
    HI_U16                    face_final_ratio;
    HI_U16                    face_using_mode;//368
    HI_U16                    skin_rg_ratio;
    HI_U16                    skin_bg_ratio;
    HI_U16                    rg_from_skin;
    HI_U16                    bg_from_skin;//376
    HI_U16                    rg_final_after_skin;
    HI_U16                    bg_final_after_skin;
    HI_S16                    green_foliage_condition;
    HI_U16                    green_ctrst_w;//384
    HI_U16                    green_Bv_w;
    HI_U16                    green_ctrst_avg;
    HI_U16                    foliage_area_weight;
    HI_U16                    green_g_countL;//392
    HI_U16                    green_cwf_countL;
    HI_U16                    green_is_foliage;
    HI_S16                    green_foliage_decision;
    HI_U16                    green_weight_for_white;//400
    HI_U16                    rg_after_green_adjust;
    HI_U16                    bg_after_green_adjust;
    HI_U16                    colorchecke_dist;
    HI_U16                    colorchecke_weight;//408
    HI_U16                    colorchecke_move_rg;
    HI_U16                    colorchecke_move_bg;
    HI_S16                    no_wp_use_green;
    HI_S16                    no_wp_use_face;//416
    struct_light_point       no_wp_lsc_mass_wp;
    struct_light_point        must_be_blue_sky_final_rg_bg;//424
    HI_S16                    no_wp_possible_lsc;
    HI_S16                    no_wp_must_be_blue_sky;
    HI_S16                    use_last_wp_directly;
    HI_U16                    CCT_by_xy;//432
    HI_U16                    ACS_local_dir_count[3];
    HI_S16                    delta_UV_by_xy;//440
    HI_U16                    ACS_cct_luma_weight[3];
    HI_U16                    CCT_shift;//448
    HI_U16                    ACS_inner_result[3];
    HI_U16                    wp_off_locus_weight;//456
    struct_light_point        wp_after_CCT_shift;
    struct_light_point        wp_for_lsc;//464
    struct_light_point        wp_shift_on_ct_locus;
    struct_light_point       wp_shift_off_ct_locus;//472
    struct_light_point       wp_final_shift_vector;
    struct_light_point        wp_after_color_cast;//480
    HI_U16                    wp_up_down_locus;
    HI_U16                    locked_in_current_frame;
    HI_U16                    unlock_in_current_frame;
    HI_U16                    awb_is_locked;//488
    HI_U16                    history_A_cnt;
    HI_U16                    history_CWF_cnt;
    HI_U16                    history_Day_cnt;
    HI_U16                    history_expo_avg;//496
    HI_U16                    history_expo_range;
    HI_U16                    history_max_expo_delta;
    HI_U16                    history_max_luma_delta;
    HI_U16                    history_luma_range;//504
    struct_light_point        wp_after_history;
    HI_U16                    history_force_to_which_light;
    HI_U16                    final_light_type;//512
    HI_U16                    final_wb_gain[3];
    HI_U16                    force_light_type;//520
    HI_U16                  awb_stat_hist[AWB_EXIF_STAT_HIST_NUM];//788
    HI_U16                  reserved[2];//792bytes
} awb_exif_t;

typedef struct
{
    char module_name[16];//16
    WB_gain_struct     wb_gain_param;//24
    struct_light_point wp_before_shift;
    struct_light_point wp_for_lsc;//32
    struct_light_point wp_for_cc;
    struct_light_point wp_cast_vector;//40
    int             BV_value;
    unsigned int             current_time_sec;
    unsigned int             current_time_us;
    unsigned int             awb_state;//56
    unsigned int             awb_region[5];
    unsigned int             awb_mode;//80
    float                 rgbg_flash[2];//88
    unsigned short             CCT_value;
    unsigned short           reserved_short;
    unsigned int             reserved[247];
} awb_out_param_t;
/* for rawnf  */

typedef struct _rawnf_exif_t
{
    unsigned short gain_value;
    unsigned char  rdn_curve_idx;
    unsigned char  rdn_filter_idx;
    unsigned short rdn_curve_1stpoint;
    unsigned char  r_nlm_strength;
    unsigned char  g_nlm_strength;
    unsigned char  b_nlm_strength;
    unsigned char  blend_diff_scale;
    unsigned char  blend_min;
    unsigned char  blend_edge_low;
    unsigned char  lsc_slope;
    unsigned char  lsc_offset;
    unsigned char  Reserved_0;
    unsigned char  Reserved_1;
    unsigned char  Reserved_2;
    unsigned char  Reserved_3;
    unsigned char  Reserved_4;
    unsigned char  Reserved_5;
    unsigned char  Reserved_6;
    unsigned char  Reserved_7;
    unsigned char  Reserved_8;
    unsigned char  Reserved_9;
    unsigned char  Reserved_10;
    unsigned char  Reserved_11;
    unsigned char  Reserved_12;
    unsigned char  Reserved_13;
    unsigned char  Reserved_14;
    unsigned char  Reserved_15;
    unsigned char  Reserved_16;
    unsigned char  Reserved_17;
} rawnf_exif_t;//32 byte

typedef struct
{
    char module_name[16];
} rawnf_md_t;//do need exif?

/* for yuvnf_md_t   */
typedef struct _yuvnf_exif_t
{
    unsigned char yuvnf_idx;
    unsigned char nlm_symfilter_tag;
    unsigned short nlm_invsad;
    unsigned char nlm_offsad;
    unsigned char nlm_gain_maxoff;
    unsigned short blend_x0;//8
    unsigned short blend_x1;
    unsigned short blend_y0;
    unsigned short blend_y1;
    unsigned short sigma_U;//16
    unsigned short sigma_V;
    unsigned char nlm_edge_maxoff;
    unsigned char Reserved_0;//20
    unsigned char Reserved_1;
    unsigned char Reserved_2;
    unsigned char Reserved_3;
    unsigned char Reserved_4;
    unsigned char Reserved_5;
    unsigned char Reserved_6;
    unsigned char Reserved_7;
    unsigned char Reserved_8;//28
    unsigned char Reserved_9;
    unsigned char Reserved_10;
    unsigned char Reserved_11;
    unsigned char Reserved_12;//32
} yuvnf_exif_t;

typedef struct _yuvnf_md_t
{
    char                module_name[16];
}yuvnf_md_t;

/* FOR arsr_md_t */
typedef struct _arsr_exif_t
{
    unsigned int     sharpen_idx;
    unsigned int     skin_thres_low;
    unsigned int     skin_thres_high;
    unsigned int     shp_gain_var_low0;
    unsigned int     shp_gain_var_low1;
    unsigned int     shp_gain_var_high0;
    unsigned int     shp_gain_var_high1;
    unsigned int     edge_shp_gain_var_low0;
    unsigned int     edge_shp_gain_var_low1;
    unsigned int     edge_shp_gain_var_high0;
    unsigned int     edge_shp_gain_var_high1;
    unsigned int     linear_sh_ratio_low;
    unsigned int     linear_sh_ratio_high;
    unsigned int     sharp_level;
    unsigned int     sharp_coring;
    unsigned int     y0_sharp_amt1;
    unsigned int     y1_sharp_amt1;
    unsigned int     y0_edge_amt;
    unsigned int     y1_edge_amt;
    unsigned int Reserved_0;
    unsigned int Reserved_1;
    unsigned int Reserved_2;
    unsigned int Reserved_3;
    unsigned int Reserved_4;
    unsigned int Reserved_5;
    unsigned int Reserved_6;
    unsigned int Reserved_7;
    unsigned int Reserved_8;
}arsr_exif_t;// is write to exif ?

typedef struct _arsr_md_t
{
    char             module_name[16];//#&@_arsr
}arsr_md_t;

/* lsc_md_param_t */
typedef struct
{
    char module_name[16];//
} lsc_out_param_t;

/*  drc_md_param  */
typedef struct _drc_ref_out_t
{
     unsigned int           uniform_size;
     unsigned short         value_dyna_max;
     unsigned short         value_dyna_min; //8

     unsigned short         black_level;
     unsigned short         mean_value;
     unsigned short         variance_value;
     unsigned short         momentrd_value; //16

     unsigned short         brightness_lv;

     unsigned short         location_max[DRC_LOCATION_MAX]; //34
     unsigned int           cos_angle[DRC_COS_ANGLE];  //162

     unsigned short         drc_global_tone[DRC_GLOBAL_TONE];  //674
     int                    moment[DRC_MOMENT];  //706
     int                    reserved[DRC_REF_OUT_RESER];  //738 bytes
} drc_ref_out_t;

typedef struct _drc_reg_basic_t
{

    int             frame_width;      //13bit
    int             frame_height;     //13bit

    short           win_h;
    short           win_v;
    short           win_h_last;
    short           win_v_last;

    short           buff_win_h[DRC_BUFF_WIN];
    short           last_win_h_stripe;      //10bit    exp: Last bottom block width in stripe
    short           buff_win_v[DRC_BUFF_WIN];


    short           last_win_v_stripe;      //10bit

    short           first_block_num_h;      //5bit    exp: Top block number of the first pixel in stripe
    short           first_block_num_v;      //5bit
    short           block_num_h_stripe;   //5bit    exp: Horizontal block number in stripe
    short           block_num_v_stripe;   //5bit
    short           first_block_off_h;       //10bit  exp: The horizontal offset of the first pixel in current block in stripe
    short           first_block_off_v;       //10bit

    short           x_start_point;       //13bit   exp: Horizontal Startpoint of the stripe in the luma grid coordinates
    short           y_start_point;       //13bit

    short           modify_enable;


    short           hw_enable;

    short           num_h;     //5bit
    short           num_v;     //5bit

    short           rgb2yuv_matrix[DRC_RGB_YUV_MATRIX]; //
    int             reserved_x;
    int             reserved_y;
}drc_reg_basic_t;

typedef struct _drc_reg_dynamic_t
{
    short           drc_ra_tab[DRC_RA_TAB_SIZE];
    short           drc_offset_alpha[DRC_OFFSET_ALPHA_SIZE];
    short           drc_rat_tabh[DRC_CURVE_HW_SIZE];
    short           drc_rat_tabl[DRC_CURVE_HW_SIZE];

    short           avermatrix_in[DRC_BLOCK_SIZE * DRC_BLOCK_SIZE];         //10bit; 10.0   DRC Y_aver block info
} drc_reg_dynamic_t;

typedef struct _drc_exif_t
{
    unsigned char       drc_rat_tabh[DRC_EXIF_RAT_TAB];
    unsigned char       drc_rat_tabl[DRC_EXIF_RAT_TAB];
    unsigned char       value_dyna_max;
    unsigned char       value_dyna_min;

    unsigned char       weight_init_ctrs;
    unsigned char       weight_init_pull;

    unsigned char       weight_brig_hist;
    unsigned char       weight_dark_hist;
    unsigned char       weight_global_hist;
    unsigned char       weight_roi_hist;

    unsigned char       black_level;
    unsigned char       mean_value;
    unsigned char       variance_value;
    unsigned char       momentrd_value;

    unsigned short      reserved_a[DRC_EXIF_RESER_A];
    unsigned char       reserved_b[DRC_EXIF_RESER_B];
    unsigned char       reserved[6];
} drc_exif_t;

typedef struct
{
    char                module_name[16];
    drc_reg_basic_t     drc_reg_basic[MAX_STRIPE_NUM];
    drc_reg_dynamic_t   drc_reg_dynamic;
} drc_out_param_t;

/* cc_md_param_t */
typedef struct _cc_cct_illum_state_t{
    struct_light_point cct_info_vec[CC_LIGHT_NUM];
    unsigned int cct_illum_vec[CC_LIGHT_NUM];
    unsigned int ccm_illum_weight[CC_LIGHT_NUM][CHROMA_SEGM_NUM][CHROMA_COM_ILLUM_NUM];
}cc_cct_illum_state_t;

typedef struct _cc_ccm_com_state_t{
    struct_light_point cct_info_val;
    unsigned int ccm_com_num;
    unsigned int ccm_com_vec[CHROMA_COM_MAX_NUM];
    unsigned int ccm_com_weight[CHROMA_COM_MAX_NUM];
}cc_ccm_com_state_t;

typedef struct _cct_cluster_com_state_t{
    unsigned int cluster_com_num;
    unsigned int cluster_com_vec[CCT_CLUSTER_CUR_NUM];
    unsigned int cluster_com_weight[CCT_CLUSTER_CUR_NUM];
}cct_cluster_com_state_t;

typedef struct _cc_ref_out_t{
    cc_cct_illum_state_t cct_illum_state;
    cc_ccm_com_state_t ccm_com_state;
    cct_cluster_com_state_t cluster_com_state;
}cc_ref_out_t;

typedef struct _cc_reg_dynamic_t
{
    unsigned int    bcc_srcm_en;
    unsigned int    bpix_yconst;                //u1.0  switch for Pixel's Y keep constant
    unsigned int    pix_ycoef_val;             //u6.0  pixel's y coeffcient value
    unsigned int    bhigh_light_rec;
    unsigned int    chl_ofst_val;                //u10.0   channel maximum offset value
    unsigned int    chroma_exrange_clip;   //u8.0  range extend ratio adaptation for clip pixel
    short           color_correct_mat[CCM_MAT_NUM];
    unsigned short  exrange_max_ratio[HIGH_REC_PARAM_NUM]; // u8.0 range extend ratio for maximum value
    unsigned short  exrange_min_ratio[HIGH_REC_PARAM_NUM];  // u8.0 range extend ratio for minimum value
    unsigned short  clip_ycom_pos[HIGH_REC_PARAM_NUM];        //u8.0  y combination coeffcient for range positive add
    unsigned short  clip_ycom_neg[HIGH_REC_PARAM_NUM];       //u8.0 y combination coefficient for range negative sub
} cc_reg_dynamic_t;//426bytes

typedef struct _cc_exif_t{
    unsigned char   cc_flow_mode;
    unsigned char   ccm_com_vec[CHROMA_COM_MAX_NUM];
    unsigned char   ccm_com_num;
    unsigned char   cct_illum_vec[CHROMA_COM_MAX_NUM];//8
    unsigned short  sat_light_vec[CC_EXIF_SAT_NUM];//16
    unsigned short  ccm_com_weight[CHROMA_COM_MAX_NUM];//
    unsigned short  sat_illum_val;//24
    short                ccm_hw_mat[CCM_MAT_NUM];//42
    unsigned short  sat_ratio_val;//44
    unsigned short  reserved[2];//48
    unsigned short  cluster_com_weight[CCT_CLUSTER_MAX_NUM];//58
    unsigned char   cluster_com_num;
    unsigned char   cluster_com_vec[CCT_CLUSTER_MAX_NUM];//64bytes
} cc_exif_t;

typedef struct _cc_md_param_t
{
    char                module_name[16];
    cc_reg_dynamic_t cc_reg_dynamic[MAX_STRIPE_NUM];//for cpipe,same for stripe
    unsigned int     algo_comp_valid;
    char             reserved[4];
} cc_out_param_t;

/* for ce_md */
typedef struct _ce_ref_out_t{
    unsigned int            ce_stat_en;
    unsigned int            sce_skin_flag;
    unsigned int face_skin_flag;
    int                     skin_iter_val;
    unsigned int sat_max_vec[CE_SAT_HIST_MAX];
    char face_gridu_mat[FACE_GRID_SIZEH][FACE_GRID_SIZEW];
    char face_gridv_mat[FACE_GRID_SIZEH][FACE_GRID_SIZEW];
}ce_ref_out_t; // may be place in chromatix ce

typedef struct
{
    unsigned int    stat_sat_max[CE_SAT_HIST_MAX];
    unsigned int    stat_skin_hue_hist[CE_SKIN_HUE_HIST_MAX];
} stat_tab_ce_t;// may be place in chromatix ce

typedef struct _ce_reg_dynamic_t
{
    unsigned int        bget_stat_enable;            //u1.0bit
    unsigned int        bsce_enable;        //enable saturation color enhance or not: u1.0bit
    unsigned int        bgray_filter_enable;
    unsigned int        bface_valid; //Is face detection valid: u1.0bit
    unsigned int        face_pos_infor[FACE_POS_RECT];  //The position of the biggest face. LUx,LUy,RDx,RDy u13.0bit
    char                gain_along_hue[CHROMA_HUE_NUM];  //UV gain for every hue value. range:[0,2]/[-128,127] s8.0bit
    unsigned int        uv_gray_filter_thresh[GRAY_SEGM_NUM]; //UV Filter thresh value u8.0 bit
    unsigned int        uv_gray_filter_strength[GRAY_SEGM_NUM];   //UV gray filter strength: u5.0 bit
    unsigned int        uv_gray_thresh_recip[GRAY_SEGM_NUM];
}ce_reg_dynamic_t;// may be place in chromatix ce

typedef struct _ce_exif_t{
    unsigned short      sce_sat_vec[CE_EXIF_SAT_NUM];
    short               skin_hue_val;
    short               skin_iter_val;
    short               skin_rotate_hue;
    unsigned short      rotate_factor_val;
    unsigned int        roi_sum_val;
    unsigned int        hist_sum_val;
    unsigned char   ce_flow_mode;
    unsigned char   reserved[7];//32bytes
}ce_exif_t;

typedef struct _ce_md_param_t
{
    char                          module_name[16];
    ce_reg_dynamic_t      ce_reg_dynamic[MAX_STRIPE_NUM];
} ce_out_param_t;

/* for gamma_md_param */
typedef struct _tone_map_t
{
    float cuver_red[MAX_TONE_MAP_SIZE*2];
    float cuver_green[MAX_TONE_MAP_SIZE*2];
    float cuver_blue[MAX_TONE_MAP_SIZE*2];
    unsigned int count; // the number of RGB
    unsigned int reserved;//6176
} tone_map_t;

typedef struct _gamma_ref_out_t
{
    unsigned int tone_curve[TONE_CURVE_LEN];
}gamma_ref_out_t;

typedef struct _gamma_reg_dynamic_t
{
    unsigned int  gamma_out[GAMMA_CALIBRATION_SIZE];
    unsigned int  gamma_reg[GAMMA_CURVE_HW_SIZE * GAMMA_RGB_CHANNEL];
}gamma_reg_dynamic_t;//may be place in chromatxi gamma

typedef struct _gamma_exif_t
{
    unsigned int        gamma_hw[GAMMA_CURVE_HW_SIZE - 1];//128    // low 0-9bit N frame;10-19bit N-1 frame;20-29bit N-2 frame;
    unsigned char       weight_ctrs;
    unsigned char       weight_high;
    unsigned char       weight_mid;
    unsigned char       weight_low;
    unsigned short      reserved_a[GAMMA_EXIF_RESER_A];//136
    unsigned char       reserved_b[GAMMA_EXIF_RESER_B];//142
    unsigned char       reserved[2];//144bytes
} gamma_exif_t;

typedef struct
{
    char module_name[16];//16
    /* current algo calculated gamma curve */
    gamma_reg_dynamic_t gamma_reg_dynamic;//common for capture and preview,1480bytes
    tone_map_t tone_map;
} gamma_out_param_t;//7656

/* for lut3d_md_param_t */
typedef struct _lut3d_md_param_t
{
    unsigned int reserved[2]; //empty
} lut3d_md_param_t;

/* for af_md */
typedef struct {
    int camNum;
    int farNearFlag;        //1-far, 2-near
    int resultPrimary;
    int contrastPrimary;
    int resultAux;
    int contrastAux;
} mmi_7cm_result_t;

typedef struct
{
    int     msg_report;
    int     id;
    int     cmd;
    int     type;
    int     size;
    char    data[MAX_AF_DATA_SIZE];
} af_msg;

typedef struct {
    int     report;
    int     focus_stage;
    int     e_rel_type;
    int     is_single_frame_af;
    int     before_lens_move_time;
    int     lens_moving_time;
    int     after_lens_move_time;
    float   sensor_efl;
} af_md_detailed_info_t;

typedef struct _af_rect_info
{
    unsigned int left;
    unsigned int top;
    unsigned int width;
    unsigned int height;
} af_rect_info;

typedef struct _gsensor_data_t
{
    int x;
    int y;
    int z;
} gsensor_data_t;

typedef struct af_debug_info {
    int                            focus_report;
    int                            af_arithmetic;
    int                            err_in_af_set_stat_area;
    int                            err_in_af_get_stat_data;
    af_rect_info                   rect_before_adjust;
    af_rect_info                   rect_after_adjust;
    int                            enlarge_flag;
    af_rect_info                   rect_large;
    af_rect_info                   rect_large_adjust;
    int                            e_force_stage;
    int                            step_cnt_of_trip;
    int                            step_of_trip;
    int                            direction_of_trip;
    unsigned int                   vcm_offset_init;
    unsigned int                   vcm_full_range;
    int                            start_pos;
    int                            end_pos;
    unsigned int                   cur_pos_code;
    int                            cur_pos_contrast;
    unsigned int                   top_code;
    int                            top_contrast;
    int                            ae_gain;
    int                            iso;
    int                            expo_time;
    int                            fps;
    int                            af_real_type;
    int                            flow;
    gsensor_data_t                 gsensor;
    int                            mmitype;
    int                            point_light_flag;
    int                            zone_top;
    int                            full_top;
    int                            fine_search_using_zone_index;
    int                            normal_array_size;
    unsigned int                   focusCntFlag;
    af_rect_info                   dumpRect;
    int                            result;
    char                           log_info[MAX_LOG_SIZE];
} af_debug_info;

typedef struct {
    int             laserDistance;
    int             laserOverlap;
    int             laserStatus;
    int             laserResponse;
    int             laserConfidence;

    int             depth;
    int             depthConfidence;

    int             mixDepth;
    int             mixDepthConf;
    int             depthSuggestCode[2];

    int             shelter;
    int             flowNum;

    int             sceneUnstable;
    int             sceneTrigger;
    int             motionUnstable;
    int             motionTrigger;
    int             waitAeStable;
    int             aeExpoValue;

    int             reserved[13];
} af_display_info_t;

typedef struct
{
    unsigned char           af_ctrl_report;
    unsigned char           af_ctrl_state;
    unsigned char           af_ctrl_mode;
    int                     af_ctrl_trigger_id;
    int                     af_ctrl_region[5];
    int                     af_mmi_7cm_report;
    mmi_7cm_result_t        af_mmi_7cm_result;
    int                     af_mmi_pdaf_report;
    int                     pdaf_mmi_test_result;
    int                     af_mmi_dc_report;
    int                     dc_mmi_test_result;
    int                     dc_mmi_test_index;
    af_msg                  msg;
    unsigned int            af_ctrl_cur_code;
    unsigned int            af_ctrl_cur_virtual_code;
    signed long long        af_ctrl_focus_done_time;
    unsigned int            vcm_stable;
    unsigned int            hw_ipp_vcm_stable;
    int                     current_distance;
    af_md_detailed_info_t   af_detailed_info;
    af_debug_info           debug_info;
    af_display_info_t       display_info;
    unsigned long long int  contrast_value;
    int                     pointFlag;
    int                     af_mmi_report;
    int                     af_mmi_result;
    int                     af_mmi_index;
    int                     af_mmi_mode;
    int                     af_mmi_request;
    char                    af_sensor_temp;
    char                    af_driver_temp;
    //ST_EXIF_INFO            af_exif;
    char                    char_reserved[6];
    int                     reserved[460];
} af_md_t;

typedef struct _af_exif_t
{
}af_exif_t;


typedef struct _flash_exif_t
{ //total 64, should consider byte align.
    unsigned int preview_lum;
    unsigned int preview_gain;
    unsigned int preview_expo;
    unsigned int preflash_lum;
    unsigned int preflash_gain;
    unsigned int preflash_expo;
    unsigned int capture_lum; //cal capture lum;
    unsigned int ae_target; //capture_target_lum int hisi_cal_ratio_factor
    unsigned int ratio; //ratio_factor in flash_ctrl_date_t
    unsigned short preview_r;
    unsigned short preview_b;
    unsigned short preflash_r;
    unsigned short preflash_b;
    unsigned short otp_capture_r;
    unsigned short otp_capture_b;
    unsigned short capture_r; //set by ap
    unsigned short capture_b; //set by ap
    unsigned int flash_index; //set by ap
    unsigned char face_detect;
    unsigned char aureserved[7]; //add here.
} flash_exif_t;

//-------------------------old-------------------------------------------
typedef enum _preflash_state_e
{
    PREFLASH_NONE = 0,
    ASSISTANT_FLASH,
    PREFLASH,
    PREFLASH_DONE,
} preflash_state_e;

typedef enum {
    FLASH_OFF_MODE = 0,
    FLASH_PREFLASH_MODE,
    FLASH_TORCH_MODE,
    FLASH_CAPFLASH_MODE,
    FLASH_LCD_MODE,
    FLASH_MAX_MODE,
} flash_work_mode_e;

typedef struct _flash_info_t
{
    unsigned int flash_on;
    flash_work_mode_e flash_mode;
    int flash_level;
    preflash_state_e flash_state;
    awbParam  awb_param;
    awbParam awb_param_with_otp;
    aeExtParam ae_extparam;
    unsigned int vcm_code;
    unsigned int light_ratio;
} flash_info_t;
//---------------------------old---------------------------------
typedef struct _af_focus_done_time_t {
    int enable_flag;
    int vcm_stable_time;
} af_focus_done_time_t;

typedef struct _af_depth_rect_t {
    int enable_flag;
    af_rect_info depth_rect;
} af_depth_rect_t;

typedef struct _rpmsg_af_info_t {
    af_focus_done_time_t focus_done_time;
    af_depth_rect_t depth;
} rpmsg_af_info_t;
//------------------------------old-------------------------------

typedef struct
{
    unsigned char flash_state;
    unsigned char ae_state;
    unsigned char need_lcd_compension;
    unsigned char mmi_flash_test;
    int           ae_precapture_id;
    preflash_work_state preflash_state;
    unsigned char capflash_ae_effect;
    unsigned char resume_ae_doing;
    unsigned char flash_drop_frame;
    unsigned char ae_mode;
    unsigned char ae_precapture_trigger;
    unsigned char reserved_char[3];
    int           reserved[11];
} flash_md_t;

/* for pdaf */
typedef struct _pdaf_exif_t
{
    unsigned int pdaf_hsize;
    unsigned int pdaf_vsize;
    unsigned int pdaf_sat_thrd0;
    unsigned int pdaf_sat_thrd1;
    unsigned int pdaf_ihleft;
    unsigned int pdaf_ivtop;
    unsigned int pdaf_ihright;
    unsigned int pdaf_ivbottom;

    unsigned int pdaf_hpos[PP_NUM];
    unsigned int pdaf_vpos[PP_NUM];
    unsigned int pdaf_correction[PP_NUM];
    unsigned int pdaf_saturation[PP_NUM];

    unsigned int x_start_offset;
    unsigned int y_start_offset;
    unsigned int x_start_block;
    unsigned int y_start_block;
} pdaf_exif_t;

typedef struct _pdaf_md_t
{
    char         module_name[16];//#&@_pdaf
} pdaf_md_t;

/* for ois result */
typedef struct _ois_data_t
{
    short gyrox;
    short gyroy;
    short gyroz;
    short x_hall_position;
    short y_hall_position;
    short reserved[3];
} ois_data_t;

typedef struct _ois_info_t
{
    signed char ois_flag;
    signed char data_num;
    signed char waiting_time;
    signed char reserved[5];
    ois_data_t ois_data[OIS_DATA_MAX];
} ois_info_t;

typedef struct _ois_update_t
{
    ois_info_t driveric_data;
}ois_update_data_t;

typedef struct
{
    int aging_ack;
    int check_ack;
    int enable_ack;
    int            gryo_offset_calib_report;
    int mag_check_ack[4];
    int            x_gryo_offset;
    int            y_gryo_offset;
    int            gryo_offset_calib_result;
    int            hall_calib_report;
    unsigned char  hall_calib_data[OIS_CALIB_DATA_LENGTH];
    int            hall_calib_result;
    int            hall_check_report;
    int            hall_check_result;
    int            hall_data[2];
    ois_update_data_t   ois_data;
    int            state;
} ois_result_t;

/* monitor_t */
typedef struct
{
    unsigned int sensor_err_code;
    unsigned int vcm_err_code;
    unsigned int ois_err_code;
    unsigned int cam_id;
    signed int thermal_meter;
    unsigned int reserved[3];
} monitor_t;

/* laser_info_md_t */
typedef struct
{
    unsigned short RangeMilliMeter;
    unsigned short RangeDMaxMilliMeter;
    unsigned int   MeasurementTimeUsec;
    unsigned int   SignalRateRtnMegaCps;
    unsigned int   AmbientRateRtnMegaCps;
    unsigned short EffectiveSpadRtnCount;
    unsigned char  RangeStatus;
    unsigned char  RangeFractionalPart;
    unsigned int   SigmaLimitValue;
    unsigned int   SignalLimitValue;
    unsigned int   TimingBudget;
    unsigned int   Xtalk;
    unsigned int   RangeIgonreThreshold;
} laser_reg_t;

typedef struct
{
    laser_reg_t   regdata;
    unsigned int  err_code;
    unsigned int  status;
} laser_info_md_t;

/* auto cls */
#define AUTOCLS_CONTROL_POINT_NUM   (23*17)
#define ACS_RG_BG_TS_LUT_LEN 4096
#define ACS_RG_BG_TS_LUT_STEP_Q 8
#define ACS_RG_BG_TS_LUT_START 1
#define ACS_RG_BG_TS_LUT_END 4096

typedef struct _autocls_stat_t
{
    unsigned int    r_sum_stat[AUTOCLS_CONTROL_POINT_NUM];  // 23x17
    unsigned int    g_sum_stat[AUTOCLS_CONTROL_POINT_NUM];  // 23x17
    unsigned int    b_sum_stat[AUTOCLS_CONTROL_POINT_NUM];  // 23x17
} autocls_stat_t;
typedef struct _acs_rgbg_param_t{
    HI_U32 rg_param_mat[LSC_GRID_ROWS][LSC_GRID_COLS];
    HI_U32 bg_param_mat[LSC_GRID_ROWS][LSC_GRID_COLS];
}acs_rgbg_param_t;

/* -----------cap exif info -------------------*/
typedef struct _cap_exif_t
{
    char               ae_exif[AE_DEBUG_INFO_LENGTH];
    flash_exif_t     flash_exif;
    rawnf_exif_t     rawnf_exif;
    yuvnf_exif_t     yuvnf_exif;
    arsr_exif_t       arsr_exif;
    pdaf_exif_t       pdaf_exif;
    cc_exif_t           cc_exif;
    ce_exif_t           ce_exif;
    gamma_exif_t     gamma_exif;
    drc_exif_t         drc_exif;
    awb_exif_t         awb_exif;
    char                af_exif[AF_DEBUG_INFO_LENGTH];
} cap_exif_t;

typedef struct _warp_calibPara
{
    //Calibration at Object Distance
    float m_fObj_Dist;//mm

    //[Left(Main) Camera] --------------
    //Camera Parameters
    double m_efx_Main; //(pixel)
    double m_efy_Main; //(pixel)
    double m_eux_Main; //(pixel)
    double m_euy_Main; //(pixel)

    //Distortion Parameters
    double m_ek1_Main;
    double m_ek2_Main;
    double m_ep1_Main;
    double m_ep2_Main;
    double m_ek3_Main;

     //[Right(Sub) Camera] --------------
    //Camera Parameters
    double m_efx_Sub; //(pixel)
    double m_efy_Sub; //(pixel)
    double m_eux_Sub; //(pixel)
    double m_euy_Sub; //(pixel)

    //Distortion Parameters
    double m_ek1_Sub;
    double m_ek2_Sub;
    double m_ep1_Sub;
    double m_ep2_Sub;
    double m_ek3_Sub;

    //[Extrinsic Parameters] ----------------
    //Rotation Vector
    double eRx;
    double eRy;
    double eRz;

    //Translation Vector
    double eTx;// (mm)
    double eTy;// (mm)
    double eTz;// (mm)
}warp_calibPara_t;

typedef struct
{
    float warping_matrix[3*3];
    int input_w;
    int input_h;
    int in_stride;
    warp_calibPara_t calibpara;
    //int rectify_w;
    //int rectify_h;
    //float h_matrix[3*3];
} warp_md_t;

/* for global_ref_io_t */
typedef struct _sensor_io_t
{
    sensor_stream_mode_e    sensor_stream_mode;    //for pdaf
    int                     binning_ratio;        //for warp
}sensor_ref_io_t;

// fd ref_io
typedef struct _fd_ref_io_t
{
    unsigned int    face_num;
    fd_pos_t        face_fe[FD_MAX_NUM]; /* fd in actual image of sensor */
    fd_pos_t        face_be[FD_MAX_NUM]; //the face pos are the same in be and pe
}face_pos_md_t;

// stata 3a ref io
typedef struct _stat3a_ref_io_t
{
    unsigned int    block_num_v; //for awb
    unsigned int    block_num_h;  //for awb
    unsigned int    block_win_v[AWB_BLOCK_NUM_V];//for awb
    unsigned int    block_win_h[AWB_BLOCK_NUM_H];//for awb
    ae_stat_t       ae_stat;    //for ae, drc, gamma
    awb_stat_t      awb_stat;   //for drc, awb
    af_stat_t       af_stat;    // for af
    v2_af_stat_t    v2_af_stat; // for af  75
    unsigned char   reserved[4];
}stat3a_ref_io_t;

// flash ref_io
typedef struct _flash_ref_io_t
{
    unsigned int  flash_cct_weight;  //for cc,ce
    unsigned int  flash_scene_weight; //for cc,ce
    unsigned int  flash_state;//for cc, ce
    unsigned char flash_mode;
    unsigned char reserved[3];
}flash_ref_io_t;

typedef struct
{
    int     face_flag;
    int     face_luma;
    float   face_weight;
    int     non_face_luma;
} ae_face_ref_io_t;

//blc_ref_io
typedef struct _blc_ref_io_t
{
    unsigned short  blc_offset[4]; //for awb
}blc_ref_io_t;

// ae_ref_io
typedef struct _ae_ref_io_t
{
    unsigned int    gain;            //yuvnf,arsr,cc,ce,gcd,minilsc,lsc,rawnf,tnr,drc,gamma,awb
    unsigned int    expo;            //for cc,ce,drc,gamma,awb
    unsigned int    averagevalue;        //for cc,ce,drc, gamma,awb
    unsigned int    lum_max;        //for cc,ce
    unsigned int    cur_lum;            //for cc,ce,drc,gamma
    unsigned int    brightness_lv;        //for drc,gamma
    unsigned int    iso;            //for drc,gamma
    int             cur_smart_ae_expo_comp;//smart ae for drc,gamma
    unsigned int    expo_value;        //for drc,gamma
    unsigned int    tar_lum;            //for drc,gamma
    int             avr_diff_sum;       //for drc
    unsigned int    lum_matix_32bin[AWB_BLOCK_NUM_H][AWB_BLOCK_NUM_V];
}ae_ref_io_t;

typedef struct _af_ref_io_t
{
    unsigned int sof_irq_time;
    unsigned int stat3a_irq_time;
    unsigned int cur_code;
    unsigned int reserved;
}af_ref_io_t;

// awb_ref io
typedef struct _awb_ref_io_t
{
    ////////////////////////////////// for awb
    awb_light_type_enum        force_light_type;
    awb_converge_mode_e     awb_converge_mode;
    unsigned int            awb_run_count;
    unsigned int            ei_value;
    unsigned int            ae_again;
    unsigned int            b_init_without_stat;
    unsigned int            min_fps;
    unsigned int            subcmd_awb_ct;
    unsigned int            cct_shift;
    unsigned int            b_is_gray_zone;
    struct_light_point          wp_result;
    ////////////////////////////////end
    struct_light_point          awb_otp_gain;                //for awb
    WB_gain_struct               wb_gain_param;                //for awb_gain
    struct_light_point         wp_for_cc;                //for cc,ce
    struct_light_point         wp_for_lsc;//for lsc minilsc

    struct_light_point      calib_wb_lsc[LSC_GRID_LIGHT_NUM];    //for lsc,minilsc
    unsigned int            reserved;
    unsigned short          awb_blk_pos_x[ORI_AWB_BLOCK_COLS];    //for minilsc
    unsigned short          awb_blk_pos_y[ORI_AWB_BLOCK_ROWS];    // for minilsc
    float                   rgbg_flash[2];
    unsigned char*          fn;
}awb_ref_io_t;

// lsc_ref_io
typedef struct _lsc_ref_io_t
{
    //lsc exec output to gcd
    unsigned short    lsc_gain_256_to_gcd[DEM_NUM];
    //lsc exec output to yuvnf
    unsigned short    lsc_gain_53_to_yuvnf[YNR_NUM];
    unsigned char     reserved[6];
}lsc_ref_io_t;

// autolsc ref_io
typedef struct _autocls_ref_io_t
{
    autocls_stat_t    autocls_stat;    //for lsc
    acs_rgbg_param_t acs_rgbg_param;
    unsigned char     reserved[4];
}autocls_ref_io_t;

//cc_ref_io
typedef struct _cc_ref_io_t
{
    cc_ref_out_t      cc_ref_out;    //for 3dlut,cc
    short             ccm_res_vec[CCM_MAT_NUM]; //for rawnf
    unsigned char     reserved[2];
}cc_ref_io_t;

//cf_ref_io
typedef struct _ce_ref_io_t
{
    stat_tab_ce_t     ce_stat[MAX_STRIPE_NUM];    //for ce
    ce_ref_out_t      ce_ref_out;        //for 3dlut

    unsigned char     reserved[6];
}ce_ref_io_t;

//for nimi lsc ref_io
typedef struct _lsc_gain_intensity_t      // S
{
    unsigned int gain[LSC_NOISE_THR_NUM];               //gain threshold, 0x100 mean 1x gain
    unsigned int intensity[LSC_NOISE_THR_NUM];       //intensity, 100-25, 90 is 90%
}lsc_gain_intensity_t;

typedef struct _lsc_2d_grid      // S
{
    unsigned int r_gain[LSC_GRID_POINTS_SINGLE];//13bit    3.10
    unsigned int gr_gain[LSC_GRID_POINTS_SINGLE];//13bit    3.10
    unsigned int b_gain[LSC_GRID_POINTS_SINGLE];//13bit    3.10
    unsigned int gb_gain[LSC_GRID_POINTS_SINGLE];//13bit    3.10
}lsc_2d_grid_t;

typedef struct _mod_mrs_size_profile_t    // module middle result
{
    lsc_2d_grid_t LSC_MRS_3CTGain_Mat[MINILSC_GRID_LIGHT_NUM];
    unsigned int noise_control_profile_MRS[LSC_NOISE_THR_NUM][LSC_GRID_POINTS_SINGLE];
    unsigned int m_lscXSize_MRS[LSC_GRID_COLS - 1];
    unsigned int m_lscXGrad_MRS[LSC_GRID_COLS - 1];
    unsigned int m_lscYSize_MRS[LSC_GRID_ROWS - 1];
    unsigned int m_lscYGrad_MRS[LSC_GRID_ROWS - 1];
}mod_mrs_size_profile_t;

typedef struct _minilsc_to_lsc_t
{
    lsc_gain_intensity_t    gain_intensity;

    // hisp150_grid_info_t             grid_info;
	mod_mrs_size_profile_t MRS_Size_Profile_FromCalib;
    unsigned int                     calib_image_width;
    unsigned int                     calib_image_height;
} minilsc_to_lsc_t;

typedef struct _minilsc_to_autocls_t
{
    mod_mrs_size_profile_t mrs_size_profile_aft_sbin;
} minilsc_to_autocls_t;

typedef struct _hisp150_grid_info_t
{
    unsigned int blk_size_x[LSC_GRID_COLS - 1];
    unsigned int blk_size_y[LSC_GRID_ROWS - 1];
} hisp150_grid_info_t;

typedef struct _mrs_pos_idx_t
{
    unsigned int bas2crop_x_size[LSC_GRID_COLS-1];
    unsigned int bas2crop_y_size[LSC_GRID_ROWS-1];
    unsigned int back2front_x_pos[LSC_GRID_COLS];
    unsigned int back2front_y_pos[LSC_GRID_ROWS];
    unsigned int back2front_sect_y_idx[LSC_GRID_ROWS];
    unsigned int back2front_y2[LSC_GRID_ROWS];
    unsigned int back2front_sect_x_idx[LSC_GRID_COLS];
    unsigned int back2front_x2[LSC_GRID_COLS];
}mrs_pos_idx_t;

typedef struct _minilsc_ref_io_t
{
    //minilsc onsize output to awb
    unsigned short    awb_cs_calib3_matrix[MINILSC_GRID_LIGHT_NUM][MINILSC_GRID_CHAN_RGB][MINILSC_GRID_FOR_ACS_POINT];
    //minilsc exec output to awb
    unsigned short    gain_online_lsc[MINILSC_GRID_CHAN_RGB][MINILSC_GRID_FOR_ACS_POINT];
    //minilsc onsize output to lsc
    minilsc_to_lsc_t  minilsc_to_lsc;
    minilsc_to_autocls_t  minilsc_to_autocls;
}minilsc_ref_io_t;

// drc_ref_io
typedef struct _drc_ref_io_t
{
    drc_ref_out_t    drc_ref_out;    //for gamma
    unsigned char    reserved[6];
}drc_ref_io_t;

//gama_ref _io
typedef struct _gamma_ref_io_t
{
    gamma_ref_out_t  gamma_ref_out; //for next ae stat
    unsigned char    reserved[4];
}gamma_ref_io_t;

//crop_io_t
typedef struct _crop_io_t
{
    int     fe_crop1_start_h;    //crop before BAS
    int     fe_crop1_start_v;
    int     fe_crop1_end_h;
    int     fe_crop1_end_v;
    int     be_crop1_start_h;    //crop by FBCRAW
    int     be_crop1_start_v;
    int     be_crop1_end_h;
    int     be_crop1_end_v;
}crop_io_t;    //for warp

//base_io_t
typedef struct _bas_io_t
{
    float    bas_ratio_x;
    float    bas_ratio_y;
}bas_io_t;    //for warp

//warp_io_t
typedef struct _warp_io_t//
{
    int             no_calib;        // LDC correction switch
    unsigned int    i_offset_h;        //stripe start point
    unsigned int    i_offset_v;        //stripe start point
    unsigned int    inputwidth;
    unsigned int    inputheight;
    int             rectify_w;
    int             rectify_h;
    int             afCode;
    float           xoisPos;
    float           yoisPos;
    // float           h_matrix[3*3];
}warp_io_t;

typedef struct _dmap_io_t
{
    unsigned short dgen_data[DEPTH_DATA_SIZE];
    unsigned short dopt_data[DEPTH_DATA_SIZE];
    unsigned int dmap_width;
    unsigned int dmap_height;
    unsigned int dgen_bit_num;
    unsigned int dopt_bit_num;
    unsigned int dgen_status;
    unsigned int dopt_status;
}dmap_io_t;

typedef struct _laser_io_t
{
    laser_reg_t  laser_data;
}laser_io_t;

typedef struct _ach_io_t
{
    float ach_gain_coef_for_lsc[4 * LSC_GRID_COLS * LSC_GRID_ROWS];
}ach_io_t;

typedef struct _global_ref_io_t
{
    sensor_ref_io_t     sensor;    //for pdaf, warp
    face_pos_md_t         fd;    //for ce,awb
    stat3a_ref_io_t     stat3a;    //for drc,gamma
    flash_ref_io_t      flash;    //for cc£¬ce
    blc_ref_io_t        blc;    //for awb
    ae_ref_io_t         ae;    //for yuvnf,arsr,cc,ce,gcd,minlsc,drc,gamma,tnr
    af_ref_io_t         af;
    awb_ref_io_t        awb;    //for cc,ce,gcd,minilsc
    lsc_ref_io_t        lsc;    //for yuvnf,gcd
    ach_io_t            ach;    //for lsc
    autocls_ref_io_t    autocls;    //for lsc
    cc_ref_io_t         cc;    //for ce,3dlut
    ce_ref_io_t         ce;    //for ce,3dlut
    minilsc_ref_io_t    minilsc;    //for lsc, awb
    drc_ref_io_t        drc;    //for gamma
    gamma_ref_io_t      gamma;
    crop_io_t           crop;    //for warp
    bas_io_t            bas;    //for warp
    warp_io_t           warp;    //for warp
    laser_io_t          laser;
    ae_face_ref_io_t    ae_face;
    ois_update_data_t   ois;     //for warp
}global_ref_io_t;

/////////////////////////////////////////////
#ifndef AF_DIRECT_TRANS_BASE
#define AF_DIRECT_TRANS_BASE
typedef struct {
    signed char     finishCalibFlag;
    signed char     codeCnt;
    signed char     minTemp[2];
    signed char     maxTemp[2];
    unsigned short  minCode[2];
    unsigned short  maxCode[2];
    signed short    reserved[8];
} af_direct_trans_base_t;
#endif

#ifndef AF_OTP_CALIB_DATA
#define AF_OTP_CALIB_DATA
typedef struct {
    unsigned short  infCodeSum[2][5];
    unsigned short  infCodeCnt[2][5];
    signed short    reserved[10];
} af_otp_calib_data_t;
#endif

#ifndef AF_SELF_LEARN_DATA
#define AF_SELF_LEARN_DATA

/* ranslation gesture number */
#define AF_TRANS_GES_NUM                    (3)
/* translation temperature number */
#define AF_TRANS_TEMP_NUM                   (5)
/* dual translation code number */
#define AF_DUAL_TRANS_CODE_NUM              (6)
/* single translation distance number */
#define AF_SINGLE_TRANS_DIST_NUM            (5)

/* translation enum definition, gesture */
typedef enum
{
    AF_TRANS_GESTURE_UP    = 0,
    AF_TRANS_GESTURE_HOR,
    AF_TRANS_GESTURE_DOWN,
    AF_TRANS_GESTURE_MAX
} af_trans_data_gesture_e;

/* translation enum definition, temperature index */
typedef enum
{
    AF_TRANS_TEMP_BELOW15  = 0,
    AF_TRANS_TEMP_15TO35,
    AF_TRANS_TEMP_35TO45,
    AF_TRANS_TEMP_45TO50,
    AF_TRANS_TEMP_ABOVE50,
    AF_TRANS_TEMP_IDX_MAX
} af_trans_data_tempure_e;

/* translation enum definition, distance index */
typedef enum
{
    AF_TRANS_DIST_INF      = 0,
    AF_TRANS_DIST_100CM,
    AF_TRANS_DIST_35CM,
    AF_TRANS_DIST_15CM,
    AF_TRANS_DIST_7CM,
    AF_TRANS_DIST_IDX_MAX
} af_trans_data_dist_e;

/* dual camera pri-sec code maping data struct */
typedef struct _tag_af_dual_cam_code_mapping_table
{
    unsigned int            confidence: 2;
    unsigned int            cnt:        6;
    unsigned int            sec_code:   12;
    unsigned int            pri_code:   12;
} af_dual_cam_code_mapping_table_t;

typedef struct _tag_af_dual_cam_temp_mapping_table
{
    af_dual_cam_code_mapping_table_t dual_cam_code_mapping_table[AF_DUAL_TRANS_CODE_NUM];
} af_dual_cam_temp_mapping_table_t;

typedef struct _tag_af_dual_cam_gesture_mapping_table
{
    af_dual_cam_temp_mapping_table_t dual_cam_temp_mapping_table[AF_TRANS_TEMP_NUM];
} af_dual_cam_gesture_mapping_table_t;

typedef struct _tag_af_dual_cam_mapping_table
{
    af_dual_cam_gesture_mapping_table_t dual_cam_gesture_mapping_table[AF_TRANS_GES_NUM];
} af_dual_cam_mapping_table_t;

/* single camera dist-code map data struct */
typedef struct _tag_af_single_code_cam_mapping_table
{
    unsigned int            confidence: 2;
    unsigned int            cnt:        4;
    unsigned int            code:       10;
} af_single_cam_code_mapping_table_t;

typedef struct _tag_af_single_cam_temp_mapping_table
{
    af_single_cam_code_mapping_table_t single_cam_code_mapping_talbe[AF_SINGLE_TRANS_DIST_NUM];
} af_single_cam_temp_mapping_table_t;

typedef struct _tag_af_sinlge_cam_gesture_mapping_table
{
    af_single_cam_temp_mapping_table_t single_cam_temp_mapping_table[AF_TRANS_TEMP_NUM];
} af_single_cam_gesture_mapping_table_t;

typedef struct _tag_af_single_cam_mapping_table
{
    af_single_cam_gesture_mapping_table_t single_cam_gesture_mapping_table[AF_TRANS_GES_NUM];
} af_single_cam_mapping_table_t;

/* dual camera code mapping */
typedef struct _tag_af_dual_cam_mapping_param
{
    unsigned int                dual_data_protect;
    int                         dual_cam_init_flag;
    af_dual_cam_mapping_table_t dual_cam_mapping_table;
} af_dual_cam_mapping_param_t;

/*single camera distance between code*/
typedef struct _tag_af_single_camera_trans_param
{
    unsigned int                  single_data_protect;
    int                           single_cam_init_flag;
    af_single_cam_mapping_table_t single_cam_mapping_table;
} af_single_cam_mapping_param_t;

typedef enum
{
    AF_SINGLE_TRANS_MAIN = 0,
    AF_SINGLE_TRANS_AUX,
    AF_DUAL_TRANS,
    AF_SELF_LEARN_TYPE_MAX
} af_self_learn_type_e;

typedef struct _tag_af_self_learn_param
{
    af_self_learn_type_e type;
    union {
        af_single_cam_mapping_param_t af_single_trans;
        af_dual_cam_mapping_param_t   af_dual_trans;
    } data;
} af_self_learn_param_t;
#endif
///////////////////////////////////////////////////////////

/*** for LPD tool start
 * for austin and dallas compile
 * ***/
typedef struct _sensor_md_t
{
    char name[32];
    unsigned int pix_bits;
    unsigned int bayer;
    unsigned int blc;
    unsigned int resolution_w;
    unsigned int resolution_h;
} sensor_md_t;

typedef struct _size_md_t
{
    unsigned int preview_sum_size_w;
    unsigned int preview_sum_size_h;
    unsigned int be_preview_w;
    unsigned int be_preview_h;
} size_md_t;

typedef struct
{
    unsigned int x_value;
    unsigned int y_value;
} coordinate_info_t;

typedef struct
{
    coordinate_info_t d75;
    coordinate_info_t d65;
    coordinate_info_t d50;
    coordinate_info_t cwf1;
    coordinate_info_t cwf2;
    coordinate_info_t tl84;
    coordinate_info_t a_val;
    coordinate_info_t h_val;
    coordinate_info_t u30;
} illuminant_info_t;


typedef struct
{
    coordinate_info_t      current_wp;
    illuminant_info_t      standard_wp_list;
    unsigned int           wBvalue;
    sensor_md_t            sensor_md;
    size_md_t              size_md;
} lpd_param_t;
/*** for LPD tool end ***/

typedef struct
{
    common_info_md_t         common_info;
    blc_md_t                      blc_md;
    stat3a_md_t                  stat_3a;

    dgamma_info_t              dgamma_md;
    dpcc_info_t                  dpcc_md;
    gcd_info_t                    gcd_md;
    tnr_md_t                      tnr_md;
    ae_md_t                        ae_md;
    awb_out_param_t               awb_md;
    rawnf_md_t                  rawnf_md;
    yuvnf_md_t                  yuvnf_md;
    arsr_md_t                    arsr_md;
    lsc_out_param_t               lsc_md;
    drc_out_param_t               drc_md;
    cc_out_param_t                 cc_md;
    ce_out_param_t                 ce_md;
    gamma_out_param_t           gamma_md;

    lut3d_md_param_t            lut3d_md;//empty
    af_md_t                        af_md;
    flash_md_t                  flash_md;
    pdaf_md_t                    pdaf_md;
    sensor_otp_t              sensor_otp;//HAL2FW

    ois_result_t              ois_result;
    monitor_t             monitor_result;
    laser_info_md_t             laser_md;
    crop_region_info_t       crop_region;
    cap_exif_t                   exif_md;
    warp_md_t                    warp_md;
    global_ref_io_t           global_ref;
} buffer_md_t;


#ifndef MD_PARAM_SIZE
#define MD_PARAM_SIZE  ((sizeof(buffer_md_t))/sizeof(int32_t))
#endif

#endif /* __HISP_MD_MESSAGE_H__ */

