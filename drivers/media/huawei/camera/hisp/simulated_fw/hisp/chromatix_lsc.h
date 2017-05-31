

//FIXME: need UNIFY the interface
#ifdef DALLAS_CAMERA
#include "chromatix_lsc_6250.h"
#endif

#ifndef __CHROMATIX_LSC_H__
#define __CHROMATIX_LSC_H__

#include "algo_common.h"

/* macro definition */
#define LSC_GRID_LIGHT_NUM           3
#define LSC_NOISE_THR_NUM            4 // decay num

#define LSC_GRID_COLS                23
#define LSC_GRID_COLS_DUAL           43
#define LSC_GRID_ROWS                17
#define LSC_GRID_POINTS_SINGLE       (LSC_GRID_COLS * LSC_GRID_ROWS)
#define LSC_GRID_POINTS_DUAL         (LSC_GRID_COLS_DUAL * LSC_GRID_ROWS)
#define LSC_GRID_FOR_ACS_X_N         32 //position number of awb block in y direction
#define LSC_GRID_FOR_ACS_Y_N         32 //position number of awb block in y direction
#define LSC_GRID_FOR_ACS_POINT       (LSC_GRID_FOR_ACS_X_N * LSC_GRID_FOR_ACS_Y_N)

#define YNR_NUM                      53 // gain for YUV2DNR 
#define DEM_NUM                      256 // gain for demosaic

#define DISTRICT_NUM 12
#define  LSC_GRID_CHAN_RGB            3

/* 41*17 */

/*****************************************************************************
                   LSC Calibrateor Set Parameter Structure
*******************************************************************************/



typedef struct _LSC_2d_grid_multi       // 43*17:
{
    int r_gain[LSC_GRID_POINTS_DUAL];  //13bit 3.10
    int gr_gain[LSC_GRID_POINTS_DUAL]; //13bit 3.10
    int b_gain[LSC_GRID_POINTS_DUAL];  //13bit 3.10
    int gb_gain[LSC_GRID_POINTS_DUAL]; //13bit 3.10
} LSC_2d_grid_struct_multi;

typedef struct _LSC_2d_grid
{
    int r_gain[LSC_GRID_POINTS_SINGLE];  //13bit 3.10
    int gr_gain[LSC_GRID_POINTS_SINGLE]; //13bit 3.10
    int b_gain[LSC_GRID_POINTS_SINGLE];  //13bit 3.10
    int gb_gain[LSC_GRID_POINTS_SINGLE]; //13bit 3.10
} LSC_2d_grid_struct;

typedef struct _LSC_gain_intensity_struct
{
    unsigned int gain[LSC_NOISE_THR_NUM];      //gain threshold, 0x100 mean 1x gain
    unsigned int intensity[LSC_NOISE_THR_NUM]; //intensity, 100-25, 90 is 90%
} LSC_gain_intensity_struct;

typedef struct
{
    unsigned int rg;
    unsigned int bg;
} awb_ratio_t;

typedef struct _grid_info_t
{
    int blk_size_x_dual[LSC_GRID_COLS_DUAL-1];
    int blk_size_x_stripe1[LSC_GRID_COLS-1];// for 4160*3120 H6_overlap 112
    int blk_size_x_stripe2[LSC_GRID_COLS-1];// for 4160*3120 H6_overlap 112
    // 4160 3120 single
    int blk_size_x[LSC_GRID_COLS-1];// for 4160*3120
    int blk_size_y[LSC_GRID_ROWS-1];// for 4160*3120

} grid_info_t;


typedef struct
{
    int calib_image_W;
    int calib_image_H;
    int overlap_n_col_grid;
    grid_info_t g_grid_info;
    struct_light_point wb_lsc[LSC_GRID_LIGHT_NUM];
    //lsc gain and intensity threshold
    LSC_gain_intensity_struct gain_intensity;
    LSC_2d_grid_struct lsc_otp_info[DISTRICT_NUM];
    LSC_2d_grid_struct lsc_ct_comp[LSC_GRID_LIGHT_NUM];
    int noise_control_profile_calib[LSC_NOISE_THR_NUM][LSC_GRID_POINTS_SINGLE];
} lsc_configure_t;

/*****************************************************************************
                   LSC LPD or Set Parameter Structure
*******************************************************************************/


typedef struct
{
    /* enable */
    int enable;

    /* manual mode */
    int manual_mode;

    /* set manual gain */
    unsigned int gain;

    /* manual awb */
    awb_ratio_t awb_gain;

    /* report current apply intensity */
    unsigned int intensity;
} lsc_lpd_param_t;

/***************************************************************************
                   LSC Run State Information Structure
***************************************************************************/
typedef struct _LSC_Output_struct{
    HI_U8 is_reliable;
    /* gain 256 for GCD, 53-radius for YUVNF */
    unsigned short lsc_gain_256_for_dem[DEM_NUM];
    unsigned short lsc_gain_53_radius[YNR_NUM];

    /* output to awb, three light source, three pipeline for every light source */
    HI_U16 AWB_CS_calib3_matrix[LSC_GRID_LIGHT_NUM][LSC_GRID_CHAN_RGB][LSC_GRID_FOR_ACS_POINT];
    /* output to awb, current light source, three pipeline only one current light source */
    HI_U16 gain_online_lsc[LSC_GRID_CHAN_RGB][LSC_GRID_FOR_ACS_POINT];
} LSC_Dynamic_Ref_Out_Param_struct;

/* lsc hw config */
typedef struct
{
    int m_lscParamBayer[4][LSC_GRID_POINTS_SINGLE];

    int m_lscXGrad[LSC_GRID_COLS - 1];
    int m_lscYGrad[LSC_GRID_ROWS - 1];
    int m_lscXSize[LSC_GRID_COLS - 1];
    int m_lscYSize[LSC_GRID_ROWS - 1];
} LSC_reg_hw_struct;

#define MINILSC_RAD_NUM 128
typedef struct MiniLSC_reg_hw_struct //_LSC_2d_grid_fp
{
    unsigned short shiftn;
    unsigned short m_lscParam_mini[4][MINILSC_RAD_NUM];
    int CenterX;
    int CenterY;
} MiniLSC_reg_hw_struct; //LSC_2d_grid_struct_fp;

#endif /* __CHROMATIX_LSC_H__ */

