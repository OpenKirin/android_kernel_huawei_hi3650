#ifndef CHROMATIX_YUVNF_H_INCLUDED
#define CHROMATIX_YUVNF_H_INCLUDED

#define YUVNF_MAX_GROUP            16
//#define YUVNF_MAX_GROUP_UV          18

typedef struct yuv2dnr_param_y {
    unsigned int   bypass_symfilter;
    unsigned int   inv_sad;
    unsigned int   shift_sad;
    unsigned int   off_sad;

    unsigned int   gainMaxOff;
    unsigned int   edgeMaxoff;
    unsigned int   edgeTH;
    unsigned int   shift_textrue;
    unsigned int   blendLow;

    unsigned int   noiseScale;
    double           smoothW;
    unsigned int   edgeBlendLow;
    unsigned int   noEBlendLow;

    unsigned char pG3[2];
    unsigned char pG7[4];
    unsigned char pG9[5];

    unsigned int mult_gauss_en;
    unsigned int blend_x0;
    unsigned int blend_x1;
    unsigned int blend_y0;
    unsigned int blend_y1;

    unsigned int sigmaU_r;                  // range domain
    unsigned int sigmaV_r;
    unsigned int U_desaturation_TH;         // desaturation threshold, U 
    unsigned int V_desaturation_TH;         // desaturation threshold, V 
    unsigned int m_UV_impulsive_th;
}yuv2dnr_param;

typedef struct
{
    //gain is the standard gain
    unsigned int gain;
    //setting data
    yuv2dnr_param reg_filter;
}yuvnf_filter_t;
/*
typedef struct
{
    //gain is the standard gain
    unsigned int gain;
    //setting data
    yuv2dnr_param_uv reg_filter_uv;
} yuvnf_filter_uv_t;
*/
typedef struct
{
    int filter_num;
    yuvnf_filter_t filter_data[YUVNF_MAX_GROUP];
  //  yuvnf_filter_uv_t filter_data_uv[YUVNF_MAX_GROUP_UV];
} yuvnf_config_t;

typedef struct
{
    unsigned int manual[2]; /*0 -AUTO 1-manual */
    yuv2dnr_param  yuvnf_params[2];
} yuvnf_cap_manual_param_t;

#endif /*CHROMATIX_YUVNF_H_INCLUDED*/

