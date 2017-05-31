


#ifndef __HISP_MD_MESSAGE_H__
#define __HISP_MD_MESSAGE_H__

#include "hisp/chromatix.h"

/*****************************************************************************
                  Histar_ISP Algo Extend_Cmd Message
*******************************************************************************/

#define MAX_SENSOR_INFO    (7)
#define MAX_EV_SEQUENCE_SUPPORTED  60 /* left+right max group is 60 */
#define CAP_EV_SEQUENCE_SUPPORTED  (20)
#define GAMMA_CURVE_NUM      129
#define CC_MATRIX_NUM      12
#define MAX_VCM_CODE_SIZE       18

// Exif debug info macro defination start

//warning if change this please sync with "JpegEncoderExif.h"
#define AE_DEBUG_INFO_LENGTH        800
#define FLASH_DEBUG_INFO_LENGTH     64
#define RDN_DEBUG_INFO_LENGTH       32
#define YUVDN_DEBUG_INFO_LENGTH     32
#define SHARPEN_DEBUG_INFO_LENGTH   32
#define CC_DEBUG_INFO_LENGTH        52
#define CE_DEBUG_INFO_LENGTH        52
#define GAMMA_DEBUG_INFO_LENGTH     148
#define DRC_DEBUG_INFO_LENGTH       148
#define AWB_DEBUG_INFO_LENGTH       800
#define AF_DEBUG_INFO_LENGTH        3604
// Exif debug info macro defination start
#define FACE_MAX_NUM                5
#define LANDMARK_POINT              5
#define INVALID_THERMAL_METER       127
#define PIPELINE_COUNT              (2)
#define MAX_CAM_NUM                 3

#define OIS_CALIB_DATA_LENGTH       92

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
}subcmd_awb_mode_enum;

typedef enum{
    NOT_USE_MANUAL_PARAM = 0,
    USE_MANUAL_PARAM = 1,
    BYPASS_PARAM = 2,
}use_manual_param_e;

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

typedef enum {
    MODE_SINGLE_CAMERA = 0,
    MODE_DUAL_CAMERA,
} camera_mode_e;

enum {
    CAMERA_PREVIEW = 0,
    CAMERA_CAPTURE,
    CAMERA_VIDEO,
    CAMERA_VIDEOSNAPSHOT,
    CAMERA_VIDEO_RECORDING,
};

enum {
    ISP_DDR_VOTE_NONE  = 0,
    ISP_DDR_VOTE_VBLANK_MIN,//need ddr vote max to ensure isp capture sensor frame when vblank < 650us
    ISP_DDR_VOTE_VBLANK_UNDER, //need ddr vote to ensure performance when vblank at [2ms-3ms]
};

typedef struct _face_rect_t {
    unsigned int left;
    unsigned int top;
    unsigned int width;
    unsigned int height;
} face_rect_t;

typedef struct _face_win_info_t{
    face_rect_t face_area[FACE_MAX_NUM];
    unsigned short width;
    unsigned short height;
    unsigned char face_number;
    unsigned char index_max_face;
} face_win_info_t;

typedef struct _landmark_poit_t {
    int32_t x;
    int32_t y;
} landmark_point_t;

typedef struct _face_landmark_t {
    landmark_point_t left_eye[LANDMARK_POINT];
    landmark_point_t right_eye[LANDMARK_POINT];
    landmark_point_t mouth[LANDMARK_POINT];
} face_landmark_t;

typedef struct
{
    unsigned int rgain; //256 base
    unsigned int ggain; //256 base
    unsigned int bgain; //256 base
    unsigned int mode;  //0-auto;1-manual
} manualAwbParam;

typedef struct normal_capture_params_t {
    unsigned int flash_state;  //0-no flash;1-with flash
    unsigned int motion_state; //0-no motion detected;1-motion detected
    manualAwbParam awb;
} normal_capture_params_t;

typedef struct manual_ae_params_t {
    unsigned int max_expo;    /* unit: us */
    unsigned int ae_count[2]; /* for 1 camera, only ae_count[0] is valid */
    unsigned int expo[MAX_EV_SEQUENCE_SUPPORTED];
    unsigned short iso[MAX_EV_SEQUENCE_SUPPORTED];
    unsigned int effect_immediately;
} manual_ae_params_t;

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
} bracket_ev_params_t;

typedef struct superzoom_params_t {
    rect2_info_t crop_region;
    int sharpen_level; /* level 0 is lowest, reserved */
    int denoise_level;  /* level 0 is lowest, reserved */
    int stride;
} superzoom_params_t;

typedef struct multidenoise_params_t {
    unsigned int double_iso;// only for single camera
    unsigned int frame_count[2];//0 for primary camera;1 for secondary
    unsigned int max_expo[2];//0 for primary camera;1 for secondary
    unsigned int max_iso[2];//0 for primary camera;1 for secondary
} multidenoise_params_t;

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

typedef enum
{
    STAND_ALONE_MODE  = 0,
    MASTER_SLAVE_MODE = 1,
    MAX_MODE_CAM,
}multi_cam_mode_e;

typedef struct _usecase_init_param_t
{
    multi_cam_mode_e multi_cam_mode;
    unsigned int master_cam_id;
    unsigned int slave_cam_id;
}usecase_init_param_t;


typedef struct capture_params_t {
    /* 0-single camera;1-dual camera */
    unsigned int flow;
    unsigned int mode;
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

/* compute awb value in custom defined region */
typedef struct _awb_adjust_area_t{
    unsigned int left;
    unsigned int top;
    unsigned int width;
    unsigned int height;
} awb_adjust_area_t;

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

typedef struct _af_rect_info {
    unsigned int left;
    unsigned int top;
    unsigned int width;
    unsigned int height;
} af_rect_info;

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

typedef enum {
    AF_MMI_10CM = 0,
    AF_MMI_PDAF,
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
    unsigned int motion_lv;
    unsigned int motion_state;
} motion_info_t;

/*****************************************************************************
                  Histar_ISP Raw Metadata Struct
*******************************************************************************/

#define MAX_LOG_SIZE            800

typedef struct
{
    unsigned short raw_width;
    unsigned short raw_height;
} raw_size_t;

typedef struct
{
    unsigned short a_fixed;
    unsigned short b_fixed;
    unsigned short c_fixed;
    unsigned short d_fixed;
} blc_md_t;

typedef struct _awb_md_zone_struct
{
    unsigned int      rg;
    unsigned int      bg;
    unsigned int      faceRatio_num; //merge faceAreaRatio and num
    unsigned int      sumY;
    unsigned int      ctrst;
    //unsigned char   faceAreaRatio; //8     unsigned, Read only
} awb_md_zone_struct;

typedef struct _awb_stat_for_md
{
    awb_md_zone_struct awb_zone_info[AWB_BLOCK_NUM_H * AWB_BLOCK_NUM_V];
    unsigned int yavgsumstat[AWB_BLOCK_NUM_H * AWB_BLOCK_NUM_V];
    unsigned int green_gravity_rg;
    unsigned int green_gravity_bg;
    unsigned int green_count;
    unsigned int r_hist[AWB_HISTOGRAM_NUM];
    unsigned int g_hist[AWB_HISTOGRAM_NUM];
    unsigned int b_hist[AWB_HISTOGRAM_NUM];
} awb_stat_for_md_t;

typedef struct _stat3a_md
{
    awb_stat_for_md_t awb_stat;
    ae_stat_t  ae_stat;
    af_stat_t  af_stat;
} stat3a_md_t;

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
    WB_gain_struct     wb_gain_param;
    struct_light_point wp_before_shift;
    struct_light_point wp_for_lsc;
    struct_light_point wp_for_cc;
    HI_U16             CCT_value;
    struct_light_point wp_cast_vector;
    HI_S32             BV_value;
    HI_U32             current_time_sec;
    HI_U32             current_time_us;
    float              rgbg_flash[2];
    HI_U32             awb_mode;
    HI_U32             awb_state;
} awb_out_param_t;

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


#define MAX_AF_DATA_SIZE 256
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

typedef struct {
    int camNum;
    int farNearFlag;        //1-far, 2-near
    int resultPrimary;
    int contrastPrimary;
    int resultAux;
    int contrastAux;
} mmi_7cm_result_t;

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
    unsigned int            af_ctrl_cur_code;
    unsigned int            af_ctrl_cur_virtual_code;
    signed long long        af_ctrl_focus_done_time;
    unsigned int            vcm_stable;
    unsigned int            hw_ipp_vcm_stable;
    int                     af_mmi_7cm_report;
    mmi_7cm_result_t        af_mmi_7cm_result;
    int                     af_mmi_pdaf_report;
    int                     pdaf_mmi_test_result;
    int                     af_mmi_dc_report;
    int                     dc_mmi_test_result;
    int                     dc_mmi_test_index;
    int                     af_mmi_report;
    int                     af_mmi_result;
    int                     af_mmi_index;
    int                     af_mmi_mode;
    int                     af_mmi_request;
    af_md_detailed_info_t   af_detailed_info;
    af_display_info_t       display_info;
    af_debug_info           debug_info;
    af_msg                  msg;
    unsigned long long int  contrast_value;
    unsigned long long int  aux_contrast_value;
    int                     pointFlag;
    char                    af_sensor_temp;
    char                    af_driver_temp;
    char                    char_reserved[2];
} af_md_t;

typedef struct
{
    unsigned char flash_state;
    unsigned char ae_state;
    int           ae_precapture_id;
    unsigned char need_lcd_compension;
    unsigned char mmi_flash_test;
    preflash_work_state preflash_state;
    unsigned char capflash_ae_effect;
    unsigned char resume_ae_doing;
    unsigned char flash_drop_frame;
    unsigned char ae_precapture_trigger;
} flash_md_t;

typedef struct
{
    unsigned int face_num;
    fd_pos_t face_vga[FD_MAX_NUM];
    fd_pos_t face_preview[FD_MAX_NUM];
    fd_pos_t face_fe[FD_MAX_NUM];      /* fd in actual image of sensor */
    fd_pos_t face_be[FD_MAX_NUM];
    fd_pos_t face_sensor[FD_MAX_NUM];  /* fd in active pixel of sensor */
} face_pos_md_t;

typedef struct
{
    unsigned short RangeMilliMeter;
    unsigned char  RangeFractionalPart;
    unsigned short RangeDMaxMilliMeter;
    unsigned int   MeasurementTimeUsec;
    unsigned int   SignalRateRtnMegaCps;
    unsigned int   AmbientRateRtnMegaCps;
    unsigned short EffectiveSpadRtnCount;
    unsigned char  RangeStatus;
    unsigned int   SigmaLimitValue;
    unsigned int   SignalLimitValue;
    unsigned int   TimingBudget;
    unsigned int   Xtalk;
    unsigned int   RangeIgonreThreshold;
} laser_reg_t;

typedef struct
{
    laser_reg_t regdata;
    unsigned int err_code;
} laser_info_md_t;

typedef struct
{
    char           aging_ack;
    char           check_ack;
    char           enable_ack;
    int            mag_check_ack[4];
    int            gryo_offset_calib_report;
    int            x_gryo_offset;
    int            y_gryo_offset;
    int            gryo_offset_calib_result;
    int            hall_calib_report;
    unsigned char  hall_calib_data[OIS_CALIB_DATA_LENGTH];
    int            hall_calib_result;
    int            hall_check_report;
    int            hall_check_result;
    int            hall_data[2];
} ois_result_t;

typedef struct
{
    unsigned int sensor_err_code;
    unsigned int vcm_err_code;
    unsigned int ois_err_code;
    unsigned int cam_id;
    signed int thermal_meter;
    unsigned int reserved[3];
} monitor_t;

typedef struct
{
    /* gain 256 for GCD, 53-radius for YUVNF */
    unsigned short lsc_gain_256_for_dem[DEM_NUM];
    unsigned short lsc_gain_53_radius[YNR_NUM];
    LSC_reg_hw_struct reg_hw[PIPE_MAX];
} lsc_out_param_t;

typedef struct
{
    unsigned int manual_flag;
} rawnf_md_t;

typedef struct
{
    drc_dynamic_out_struct drc_dynamic_out[PIPE_MAX];
    drc_hw_stat_param drc_hw_state[PIPE_MAX];
    drc_fw_stat_param drc_fw_out_stat;
} drc_out_param_t;

typedef struct _tonemap
{
    unsigned int count; // the numer of RGB
    float cuver_red[MAX_TONE_MAP_SIZE*2];
    float cuver_green[MAX_TONE_MAP_SIZE*2];
    float cuver_blue[MAX_TONE_MAP_SIZE*2];
} tone_map_t;

typedef struct
{
    /* current algo calculated gamma curve */
    Gamma_dynamic_out_struct gamma_dynamic_out;
    unsigned int gamma_reg_in[GAMMA_REG_SIZE * GAMMA_CALIBRATION_GROUP];
    aeParamForGamma_t  ae_for_gamma;
    face_pos_struct   face_pos;
    tone_map_t tone_map;
} gamma_out_param_t;

typedef struct
{
    CC_HWReg_Dynamic_Param_struct cc_dynamic_reg_hw[PIPE_MAX];
    CC_reg_out_struct cc_hist[PIPE_MAX];
    CE_Stat_struct ce_hist[PIPE_MAX];
    CC_Ref_Out_Param_struct cc_fw_out;
} cc_out_param_t;

typedef struct
{
    CE_HWReg_Dynamic_Param_struct ce_dynamic_reg_hw[PIPE_MAX];
    CE_Stat_struct ce_hist[PIPE_MAX];
    CE_Ref_Out_Param_struct ce_fw_out;
    face_pos_struct face_pos_info;
} ce_out_param_t;

/*** for LPD tool start ***/
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
    coordinate_info_t      current_wp;
    illuminant_info_t      standard_wp_list;
    unsigned int           wbValue;
    sensor_md_t            sensor_md;
    size_md_t              size_md;
} lpd_param_t;
/*** for LPD tool end ***/

typedef struct _crop_region_info_t
{
    unsigned int   x;
    unsigned int   y;
    unsigned int   width;
    unsigned int   height;
} crop_region_info_t;

#define MAIN_AUX_CAMERA_NUM   2
typedef struct
{
    char ae_debug_info[AE_DEBUG_INFO_LENGTH];
    char flash_debug_info[FLASH_DEBUG_INFO_LENGTH];
    char rdn_debug_info[RDN_DEBUG_INFO_LENGTH];
    char yuvdn_debug_info[YUVDN_DEBUG_INFO_LENGTH];
    char sharpen_debug_info[SHARPEN_DEBUG_INFO_LENGTH];
    char cc_debug_info[CC_DEBUG_INFO_LENGTH];
    char ce_debug_info[CE_DEBUG_INFO_LENGTH];
    char gamma_debug_info[GAMMA_DEBUG_INFO_LENGTH];
    char drc_debug_info[DRC_DEBUG_INFO_LENGTH];
    char awb_debug_info[AWB_DEBUG_INFO_LENGTH];
    char af_debug_info[AF_DEBUG_INFO_LENGTH];
} capture_debug_info;

typedef struct
{
    raw_size_t              raw_size_info; //reserved
    bayer_pattern_e         raw_pattern;
    blc_md_t                blc_md[MAIN_AUX_CAMERA_NUM];
    stat3a_md_t             stat_3a[MAIN_AUX_CAMERA_NUM];
    exposure_param_struct   ae_md;
    awb_out_param_t         awb_md[MAIN_AUX_CAMERA_NUM];
    rawnf_md_t              rawnf_md[MAIN_AUX_CAMERA_NUM];
    lsc_out_param_t         lsc_md[MAIN_AUX_CAMERA_NUM];
    drc_out_param_t         drc_md[MAIN_AUX_CAMERA_NUM];
    cc_out_param_t          cc_md[MAIN_AUX_CAMERA_NUM];
    ce_out_param_t          ce_md[MAIN_AUX_CAMERA_NUM];
    gamma_out_param_t       gamma_md[MAIN_AUX_CAMERA_NUM];
    af_md_t                 af_md;
    flash_md_t              flash_md;
    face_pos_md_t           face_pos;
    sensor_otp_t            sensor_otp; //HAL2FW
    ois_result_t            ois_result;
    monitor_t               monitor_result[MAIN_AUX_CAMERA_NUM];
    lpd_param_t             lpd_md;
    laser_info_md_t         laser_md;
    capture_debug_info      extend_exif;
    crop_region_info_t      crop_region;
} buffer_md_t;

#ifndef MD_PARAM_SIZE
#define MD_PARAM_SIZE  ((sizeof(buffer_md_t))/sizeof(int32_t))
#endif

#endif /* __HISP_MD_MESSAGE_H__ */
