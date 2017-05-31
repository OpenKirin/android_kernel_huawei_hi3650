

//FIXME: need UNIFY the interface
#ifndef ALGO_COMMON_H_INCLUDED
#define ALGO_COMMON_H_INCLUDED
typedef unsigned char         HI_U8;
typedef unsigned short        HI_U16;
typedef unsigned int          HI_U32;
typedef float                 HI_FLOAT;
typedef signed char           HI_S8;
typedef short                 HI_S16;
typedef int                   HI_S32;
typedef void                  HI_VOID;
typedef char*                 HI_PCHAR;
typedef unsigned long long    HI_U64;
typedef long long             HI_S64;
typedef double                HI_DOUBLE;

typedef enum
{
    HI_FALSE    = 0,
    HI_TRUE     = 1,
} HI_BOOL;

//for ref_io
#define DEPTH_DATA_SIZE 960*540
// for ref_io end
#define  PP_NUM  32
// add for drc
#define     DRC_LOCATION_MAX         8
#define     DRC_GLOBAL_TONE          256
#define     DRC_COS_ANGLE            32
#define     DRC_MOMENT               8
#define     DRC_REF_OUT_RESER        8
#define     DRC_BUFF_WIN             3
#define     DRC_RGB_YUV_MATRIX       3
#define     DRC_RA_TAB_SIZE          17
#define     DRC_OFFSET_ALPHA_SIZE    17
#define     DRC_CURVE_HW_SIZE        65
#define     DRC_BLOCK_SIZE           16
#define     DRC_EXIF_RAT_TAB         64
#define     DRC_EXIF_RESER_A         2
#define     DRC_EXIF_RESER_B         2
//---------------need to confirm----------

#define MAX_STRIPE_NUM         8
//add for cc 
#define     CHROMA_ILLUM_NUM            3
#define     CHROMA_TYPE_NUM             (CHROMA_ILLUM_NUM+1)
#define     CHROMA_SEGM_NUM             (CHROMA_TYPE_NUM+1)
#define     CHROMA_COM_MAX_NUM          3
#define     CHROMA_COM_ILLUM_NUM        2
#define     CCT_CLUSTER_CUR_NUM         3
#define     CCM_MAT_NUM                 9
#define     HIGH_REC_PARAM_NUM          48
#define     CC_EXIF_SAT_NUM             4
#define     CCT_CLUSTER_MAX_NUM         5
//add for  cei
#define CE_SAT_HIST_MAX                 256
#define FACE_GRID_SIZEH                 17
#define CE_SKIN_HUE_HIST_MAX            64
#define FACE_POS_RECT                   4
#define FACE_GRID_SIZEW                 17
#define CHROMA_HUE_NUM                  256
#define GRAY_SEGM_NUM                   9
#define CE_EXIF_SAT_NUM                 4
// add for gamma
#define TONE_CURVE_LEN          65
#define GAMMA_CALIBRATION_SIZE  257
#define GAMMA_CURVE_HW_SIZE     33
#define GAMMA_RGB_CHANNEL       3
#define GAMMA_EXIF_RESER_A      2
#define GAMMA_EXIF_RESER_B      6
#define MAX_TONE_MAP_SIZE       257
//for awb
#define AWB_EXIF_STAT_HIST_NUM  134
#define AWB_EXIF_WEIGHTED_LINE_PTS 30
#define AWB_BLOCK_NUM_H        32
#define AWB_BLOCK_NUM_V        32
#define AWB_HISTOGRAM_NUM      256
#define ORI_AWB_BLOCK_ROWS 32
#define ORI_AWB_BLOCK_COLS 32
// add for ae
#define AE_DEBUG_QUEUE_CNT          8
// #error
#define AE_BLOCK_NUM_H          (AWB_BLOCK_NUM_H/2)
#define AE_BLOCK_NUM_V          (AWB_BLOCK_NUM_V/2)
#define AE_ROI_NUM              9
#define AE_LUM_HISTOGRAM_SIZE   256
#define AE_4BIN_HISTOGRAM_SIZE  (4 * AE_BLOCK_NUM_H * AE_BLOCK_NUM_V)
#define AE_ROI_HISTOGRAM_SIZE   (32 * 9)
// add for af
#define MAX_LOG_SIZE            800
#define MAX_AF_DATA_SIZE 256
#define AF_DEBUG_INFO_LENGTH        3604
#define AF_WINDOW_NUM          9
#define AF_HIST_NUM            32
// ADD FOR MINILSC
#define LSC_NOISE_THR_NUM            4                  // decay num
#define LSC_GRID_COLS                23
#define LSC_GRID_ROWS                17
#define LSC_GRID_POINTS_SINGLE       (LSC_GRID_COLS * LSC_GRID_ROWS)
#define MINILSC_GRID_LIGHT_NUM       3
#define MINILSC_GRID_CHAN_RGB        3                  //channel : R G B
#define MINILSC_GRID_FOR_ACS_X_N     32                 //position number of awb block in y direction
#define MINILSC_GRID_FOR_ACS_Y_N     32                 //position number of awb block in y direction
#define MINILSC_GRID_FOR_ACS_POINT   (MINILSC_GRID_FOR_ACS_X_N * MINILSC_GRID_FOR_ACS_Y_N)
//for common_info
#define LSC_OTP_SIZE            (23 * 17 * 4 * 14 / 8)
#define PDAF_OTP_SIZE           (PDAF_CORRECT_MAP + PDAF_DEFOCUS_COEF + PDAF_HW_SLOPE_DATA)
#define MAX_OTP_SIZE            (0x6E2D)
#define PDAF_CORRECT_MAP        352     /* Shield Pixel Correction Map */
#define PDAF_DEFOCUS_COEF       384     /* Defocus Conversion Coefficient */
#define PDAF_HW_SLOPE_DATA      768     /* Huawei Phase Detection Slope Data */
//for fd
#define FD_MAX_NUM              10

#define PIPE_MAX               2

typedef enum
{
    BLC_SHIFT=0,
    DGAMMA_SHIFT,
    LSC_SHIFT,
    DPCC_SHIFT,

    AE_SHIFT,
    RAWNF_SHIFT,
    AF_SHIFT,
    AWB_SHIFT,

    GCD_SHIFT,
    DRC_SHIFT,
    GAMMA_SHIFT,
    SHARPEN_SHIFT,

    CC_SHIFT,
    YUVNF_SHIFT,
    CE_SHIFT,
    MAX_SHIFT,
}ALGO_SHIFT;

/*-------------------------------------------------------------------
 *----------------HISTART ISP METADATA STRUCT------------------------
 * ---------------------------------------------------------------- */

/* common_info_md */
typedef enum {
    BAYER_RGGB = 0,
    BAYER_GRBG,
    BAYER_GBRG,
    BAYER_BGGR,
} bayer_pattern_e;

typedef struct
{
    union {
        struct {
            char module_id[5];
            char iso[2];            /* ISO(High, Low)*/
            char awb[6];            /* Gain_R(High,Low), Gain_G(High, Low), Gain_B(High,Low),*/
            char lsc[LSC_OTP_SIZE]; /* LSC Gain For Grid */
            char bpt[1351];         /* Bad pixel info */
            char af[10];
            char pdaf[PDAF_OTP_SIZE];
            char close_loop[6];
            char ois[12];
            char checksum[1];
        };
        unsigned char info[MAX_OTP_SIZE];
    };
    unsigned char otp_awb_cal_flag;   /* 0x00 means platform calibration, 0xFF means sensor self calibration*/
    unsigned char otp_lsc_cal_flag;   /* 0x00 means sensor use LSC OTP data, 0xFF means platform use LSC OTP data*/
    unsigned char fuseid[30];
} sensor_otp_t;

/* 3A stat structure */
typedef struct _awb_stat_t
{
    unsigned int y_sum_stat[AWB_BLOCK_NUM_H* AWB_BLOCK_NUM_V];
    unsigned int rg_sum_stat[AWB_BLOCK_NUM_H* AWB_BLOCK_NUM_V];
    unsigned int bg_sum_stat[AWB_BLOCK_NUM_H* AWB_BLOCK_NUM_V];
    unsigned int ctrst_sum_stat[AWB_BLOCK_NUM_H* AWB_BLOCK_NUM_V];
    unsigned int count_sum_stat[AWB_BLOCK_NUM_H* AWB_BLOCK_NUM_V];
    unsigned int y_avg_sum_stat[AWB_BLOCK_NUM_H* AWB_BLOCK_NUM_V];
    unsigned int green_gravity_rg;
    unsigned int green_gravity_bg;
    unsigned int green_count;
    unsigned int r_hist[AWB_HISTOGRAM_NUM];
    unsigned int g_hist[AWB_HISTOGRAM_NUM];
    unsigned int b_hist[AWB_HISTOGRAM_NUM];
} awb_stat_t;

typedef struct _ae_stat_t
{
    unsigned int roi_brightness[AE_ROI_NUM];
    unsigned int luma_hist[AE_LUM_HISTOGRAM_SIZE];
    unsigned int block_4bin_hist[AE_4BIN_HISTOGRAM_SIZE];
    unsigned int roi_hist_matrix[AE_ROI_HISTOGRAM_SIZE];
} ae_stat_t;

typedef struct _af_stat_t
{
    unsigned long long int  focus_val[AF_WINDOW_NUM];
    unsigned int            y_accu_val[AF_WINDOW_NUM];
    unsigned int            counter[AF_WINDOW_NUM];
    unsigned int            gradient_hist[AF_HIST_NUM];
    unsigned int            brightness_hist[AF_HIST_NUM];
} af_stat_t;

typedef struct _v2_af_stat_t
{
    unsigned long long int  focus_val[AF_WINDOW_NUM*3];
    unsigned long long int  y_accu_val[AF_WINDOW_NUM];
    unsigned int            counter[AF_WINDOW_NUM*3];
    unsigned int            gradient_hist[AF_HIST_NUM*3];
    unsigned int            brightness_hist[AF_HIST_NUM];
} v2_af_stat_t;//908bytes

typedef struct hw3a_stat_c
{
    awb_stat_t awb_stat;
    ae_stat_t  ae_stat;
    af_stat_t  af_stat;
} stat3a_t;

/* AWB , gain: 0x400 is 1x gain */
typedef struct wb_gain_t
{
    HI_U16 R_gain;  //unsigned 12bit, u2.10
    HI_U16 Gr_gain; //unsigned 12bit, u2.10
    HI_U16 B_gain;  //unsigned 12bit, u2.10
    HI_U16 Gb_gain; //unsigned 12bit, u2.10
} WB_gain_struct;

typedef struct light_point_t  
{
    HI_U16 rg_val; /* 0x400 is 1x */
    HI_U16 bg_val;
} struct_light_point;

/* for lsc */
typedef enum
{
    LSC_GRID_LIGHT_D65 = 0,
    LSC_GRID_LIGHT_A,
    LSC_GRID_LIGHT_FLU,
    LSC_GRID_LIGHT_NUM
} LSC_light_enum;

/* for flash_md */
typedef enum preflash_work_state_e{
    PREFLASH_IDLE = 0,
    PREFLASH_TODO,
    PREFLASH_DOING,
    PREFLASH_CLOSE,
    PREFLASH_CANCEL,
} preflash_work_state;

/* for fd */
typedef struct
{
    unsigned int left_top_x;
    unsigned int left_top_y;
    unsigned int width;
    unsigned int height ;
    unsigned int confidence;
    unsigned int face_rotation;
    unsigned int face_angle;
} fd_pos_t;

/* ref_io_sensor */
typedef enum
{
    CONTINUE_MODE,
    BINNING_MODE_HALF, // 1/2 binning mode,
    BINNING_MODE_QUATER, // 1/4 binning mode
} sensor_stream_mode_e;


//end--------------------------


typedef enum
{
    CAMERA_ID_BACK_MAIN = 0,
    CAMERA_ID_FRONT,
    CAMERA_ID_BACK_AUX,
    CAMERA_INDEX_MAX,
} camera_index_e;

typedef enum
{
    CAMERA_FLOW_MAIN = 0,
    CAMERA_FLOW_AUX,
    CAMERA_FLOW_DUAL,
} dual_camera_flow;

typedef enum
{
    CAMERA_INSTANCE_MAIN = 0,
    CAMERA_INSTANCE_AUX,
    CAMERA_INSTANCE_MAX,
} camera_instance_e;

typedef enum
{
    CAMERA_MODE_SINGLE = 0,
    CAMERA_MODE_DUAL,
} dual_mode_e;

typedef enum
{
    ISP_PIPE1 = 0,
    ISP_PIPE2,
    ISP_PIPE_MAX,
} isp_pipe_e;

/* Multi Stripe Param */
typedef struct _MultiStripe_param_struct
{
    HI_U8 NumStripe;      // support 2,3,4

    HI_U16 Startpoint[4];
    HI_U16 Endpoint[4];

    HI_U16 KhLeft[4];     //OverlapWinH
    HI_U16 KhRight[4];    //OverlapWinH

    HI_U16 StripeWinH[4];

    HI_U16 FullWidth;
    HI_U16 FullHeight;
} MultiStripe_param_struct;

typedef struct exposure_param_struct
{
    unsigned int stable;
    unsigned int aux_stable;
    int banding_type;
    unsigned int ae_lock;
    int expo_comp;
    int fps_range[2]; //[min_fps, max_fps]
    int ae_area[5];

    unsigned int expo;
    unsigned int gain;
    unsigned int iso;
    unsigned int expo_value;
    unsigned int fps;
    unsigned int fi;

    unsigned int curr_lum;
    unsigned int aver_lum;
    unsigned int roi_lum;
    unsigned int target_lum;
    unsigned int EI_value;

    int sae_expo_comp;
    unsigned int line_expo_us;
    unsigned int cur_vts;

    int expo_max;
    int expo_min;
    int gain_max;
    int gain_min;
    unsigned int lum_max;
    unsigned int lum_min;
    int report_ev_diff;
    unsigned int aux_ae_effect;
    int basic_fi;
    unsigned int basic_vts;
    unsigned int scale_ratio;
    unsigned int raw_height;
    unsigned int raw_width;
} exposure_param_struct;

typedef enum
{
    ALTEK_MODULE_AL6045_IMX214 = 0,
    ALTEK_MODULE_AL6010_IMX278 = 1,
    ALTEK_MODULE_MAX_SIZE,
}CAMERA_MODULE_TYPE;

typedef struct
{
    union {
        struct {
            char iso0[2];            /* ISO(High, Low) main*/
            char iso1[2];            /* ISO(High, Low) aux*/
            char awb0[6];            /* Gain_R(High,Low), Gain_G(High, Low), Gain_B(High,Low),*/
            char awb1[6];            /* Gain_R(High,Low), Gain_G(High, Low), Gain_B(High,Low),*/
        };
        unsigned char info[MAX_OTP_SIZE];
    };
} otp_exif_info_t;

typedef struct _flash_dynamic_ctrl_t
{
    unsigned int flash_mode;
    unsigned int flash_cc_weight;
    unsigned int flash_cold_weight;
}flash_dynamic_ctrl_t;

typedef struct {
    unsigned char nFaces;
    //facePos: x, y, width, height
    unsigned int posArray[FD_MAX_NUM *4];
    unsigned int confidence[FD_MAX_NUM];
    unsigned int angle[FD_MAX_NUM];
    unsigned int rotation[FD_MAX_NUM];
} face_pos_struct;

typedef struct rect_info_t {
    unsigned int left;
    unsigned int top;
    unsigned int right;
    unsigned int bottom;
    unsigned int weight; //reserved, for face, it is "confidence"
} rect_info_t;

typedef struct rect2_info_t {
    unsigned int left;
    unsigned int top;
    unsigned int width;
    unsigned int height;
} rect2_info_t;

#endif /*ALGO_COMMON_H_INCLUDED*/
