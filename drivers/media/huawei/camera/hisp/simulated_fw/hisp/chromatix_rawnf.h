

//FIXME: need UNIFY the interface
#ifdef DALLAS_CAMERA
#include "chromatix_rawnf_6250.h"
#endif

#ifndef CHROMATIX_RAWNF_H_INCLUDED
#define CHROMATIX_RAWNF_H_INCLUDED

#define RAWNF_MAX_GROUP      16
#define RAWNF_NLL_SIZE       17

typedef struct
{
    //gain is the real gain of the raw by calibration tool
    unsigned int gain;
    //calibration data, ISP_DPF_NLL_COEFF, reg 0x10-0x50
    unsigned int data[RAWNF_NLL_SIZE];
} rawnf_calibration_t;

typedef struct
{
    // channel weight
    unsigned int isp_dpf_strength_r; //reg 0x4
    unsigned int isp_dpf_strength_g; //reg 0x8
    unsigned int isp_dpf_strength_b; //reg 0xc

    //guass filter control
    unsigned int rb_gauss_coef_0; //ISP_DPF_GAUSS_RB 0x78[5:0]
    unsigned int rb_gauss_coef_1; //ISP_DPF_GAUSS_RB 0x78[11:6]
    unsigned int rb_gauss_coef_2; //ISP_DPF_GAUSS_RB 0x78[17:12]
    unsigned int g_gauss_coef_0;  //ISP_DPF_GAUSS_G 0x7c[5:0]
    unsigned int g_gauss_coef_1;  //ISP_DPF_GAUSS_G 0x7c[11:6]
    unsigned int g_gauss_coef_2;  //ISP_DPF_GAUSS_G 0x7c[17:12]

    unsigned int diff_scale; //ISP_DPF_BLEND 0x74[13:8]
    unsigned int base_blend_min; //ISP_DPF_BLEND 0x74[7:0]
    unsigned int edge_high_thld; //ISP_DPF_EDGE_THLD 0x80[15:8]
    unsigned int edge_low_thld; //ISP_DPF_EDGE_THLD 0x80[7:0]
    unsigned int diff_high_thd; //ISP_DPF_DIFF_THLD 0x84[19:16]
    unsigned int diff_low_thd; //ISP_DPF_DIFF_THLD 0x84[13:0]
    unsigned int orgn_blend_enable; //ISP_DPF_MODE 0x00[11]

    unsigned int lsc_gain_offset_enable; //ISP_DPF_MODE 0x00[8]
    unsigned int lsc_gain_offset_slope; //ISP_DPF_GAIN_DENOISE 0x6c[5:0]
    unsigned int max_lsc_gain_offset; //ISP_DPF_GAIN_DENOISE 0x6c[13:8]
} rawnf_reg_filter_t;

typedef struct
{
    //gain is the standard gain
    unsigned int gain;
    //setting data
    rawnf_reg_filter_t reg_filter;
} rawnf_filter_t;

typedef struct
{
    unsigned int cali_num;
    rawnf_calibration_t cali_data[RAWNF_MAX_GROUP];

    unsigned int filter_num;
    rawnf_filter_t filter_data[RAWNF_MAX_GROUP];
} rawnf_config_t;

typedef struct {
    unsigned char RDN_curve_idx;
    unsigned char RDN_filter_idx;
    unsigned char Reserved_0;
    unsigned char Reserved_1;
    unsigned char Reserved_2;
    unsigned char Reserved_3;
    unsigned char Reserved_4;
    unsigned char Reserved_5;
} RDN_DEBUG_INFO;

typedef struct {
    unsigned int reg_nll[RAWNF_NLL_SIZE];
    rawnf_reg_filter_t reg_filter;
} rawnf_reg_out_struct;

typedef struct
{
    unsigned int manual[2]; /*0 -AUTO 1-manual */
    rawnf_reg_out_struct rawnf_params[2];
} rawnf_cap_manual_param_t;

#endif /*CHROMATIX_RAWNF_H_INCLUDED*/
