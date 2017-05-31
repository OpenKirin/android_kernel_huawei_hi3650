

//FIXME: need UNIFY the interface
#ifdef DALLAS_CAMERA
#include "algo_common_6250.h"
#endif

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

#define PIPE_MAX               2

#define AF_WINDOW_NUM          9
#define AF_HIST_NUM            32

#define AWB_BLOCK_NUM_H        32
#define AWB_BLOCK_NUM_V        32
#define AWB_HISTOGRAM_NUM      64

#define AE_BLOCK_NUM_H          (AWB_BLOCK_NUM_H/2)
#define AE_BLOCK_NUM_V          (AWB_BLOCK_NUM_V/2)
#define AE_LUM_HISTOGRAM_SIZE   256
#define AE_2BIN_HISTOGRAM_SIZE  (2 * AE_BLOCK_NUM_H * AE_BLOCK_NUM_V)
#define AE_ROI_HISTOGRAM_SIZE   (32 * 9)

#define FD_MAX_NUM              10
#define LSC_OTP_SIZE            (23 * 17 * 4 * 14 / 8)
#define LSC_OTP_SIZE_MONO        685

#define AUTO_PDAF_WINDOW_H   (16)
#define AUTO_PDAF_WINDOW_V   (12)
#define PDAF_HEADER_SIZE     (4)
#define PDAF_HEIGHT          (1)
#define PDAF_DATA_SIZE       ((AUTO_PDAF_WINDOW_H * AUTO_PDAF_WINDOW_V * 4 + PDAF_HEADER_SIZE) * 2)
#define PDAF_DATA_NUM        (16)

#define PDAF_CORRECT_MAP        352     /* Shield Pixel Correction Map */
#define PDAF_DEFOCUS_COEF       384     /* Defocus Conversion Coefficient */
#define PDAF_HW_SLOPE_DATA      768     /* Huawei Phase Detection Slope Data */
#define PDAF_OTP_SIZE           (PDAF_CORRECT_MAP + PDAF_DEFOCUS_COEF + PDAF_HW_SLOPE_DATA)

#define MAX_OTP_SIZE            (0x3948) /*expand 0x37e2-0x3878 for sfr data*/

typedef enum {
    LSC_GRID_LIGHT_D65 = 0,
    LSC_GRID_LIGHT_A,
    LSC_GRID_LIGHT_FLU,
    LSC_GRID_LIGHT_NUM
} LSC_light_enum;

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

typedef enum {
    BAYER_RGGB = 0,
    BAYER_GRBG,
    BAYER_GBRG,
    BAYER_BGGR,
} bayer_pattern_e;

typedef enum{
    PREFLASH_IDLE = 0,
    PREFLASH_TODO,
    PREFLASH_DOING,
    PREFLASH_CLOSE,
    PREFLASH_CANCEL,
} preflash_work_state;

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

/* AWB gain: 0x400 is 1x gain */
typedef struct
{
    HI_U16 R_gain;  //unsigned 12bit, u2.10
    HI_U16 Gr_gain; //unsigned 12bit, u2.10
    HI_U16 B_gain;  //unsigned 12bit, u2.10
    HI_U16 Gb_gain; //unsigned 12bit, u2.10
} WB_gain_struct;

typedef struct
{
    HI_U16 rg_val; /* 0x400 is 1x */
    HI_U16 bg_val;
} struct_light_point;

/* 3A stat structure */
typedef struct awb_stat_c
{
    unsigned int ysumstat[AWB_BLOCK_NUM_H * AWB_BLOCK_NUM_V];
    unsigned int rgsumstat[AWB_BLOCK_NUM_H * AWB_BLOCK_NUM_V];
    unsigned int bgsumstat[AWB_BLOCK_NUM_H * AWB_BLOCK_NUM_V];
    unsigned int ctrstsumstat[AWB_BLOCK_NUM_H * AWB_BLOCK_NUM_V];
    unsigned int countsumstat[AWB_BLOCK_NUM_H * AWB_BLOCK_NUM_V];
    unsigned int yavgsumstat[AWB_BLOCK_NUM_H * AWB_BLOCK_NUM_V];
    unsigned int green_gravity_rg;
    unsigned int green_gravity_bg;
    unsigned int green_count;
    unsigned int r_hist[AWB_HISTOGRAM_NUM];
    unsigned int g_hist[AWB_HISTOGRAM_NUM];
    unsigned int b_hist[AWB_HISTOGRAM_NUM];
} awb_stat_t;

typedef struct ae_stat_c
{
    unsigned int luminance_histogram[AE_LUM_HISTOGRAM_SIZE];
    unsigned int block_2bin_hist[AE_2BIN_HISTOGRAM_SIZE];
    unsigned int roi_hist_matrix[AE_ROI_HISTOGRAM_SIZE];
} ae_stat_t;

typedef struct af_stat_c
{
    unsigned long long int fv[AF_WINDOW_NUM];
    unsigned int yv[AF_WINDOW_NUM];
    unsigned int g_hist[AF_HIST_NUM];
    unsigned int b_hist[AF_HIST_NUM];
} af_stat_t;

typedef struct hw3a_stat_c
{
    awb_stat_t awb_stat;
    ae_stat_t  ae_stat;
    af_stat_t  af_stat;
} stat3a_t;

typedef struct exposure_param_struct
{
    unsigned int stable;
    unsigned int aux_stable;
    int banding_type;
    unsigned int ae_lock;
    int expo_comp;
    int fps_range[2]; //[min_fps, max_fps]
    int ae_area[5];

    unsigned int expo[2];
    unsigned int gain[2];
    unsigned int iso[2];
    unsigned int expo_value[2];
    unsigned int fps[2];
    unsigned int fi[2];

    unsigned int curr_lum[2];
    unsigned int aver_lum[2];
    unsigned int roi_lum[2];
    unsigned int target_lum[2];
    unsigned int EI_value[2];

    int sae_expo_comp[2];

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
    ALTEK_MODULE_AL6610_OV8865 = 2,
    ALTEK_MODULE_MAX_SIZE,
}CAMERA_MODULE_TYPE;


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
            unsigned char otp_awb_cal_flag;   /* 0x00 means platform calibration, 0xFF means sensor self calibration*/
            unsigned char otp_lsc_cal_flag;   /* 0x00 means sensor use LSC OTP data, 0xFF means platform use LSC OTP data*/
        };
        unsigned char info[MAX_OTP_SIZE];
    };
    unsigned char fuseid[30];
} sensor_otp_t;

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

typedef struct
{
    unsigned int center_x;
    unsigned int center_y;
    unsigned int size;
    unsigned int confidence;
    unsigned int face_rotation;
    unsigned int face_angle;
} fd_pos_t;

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
