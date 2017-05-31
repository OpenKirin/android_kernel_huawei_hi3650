#ifndef CHROMATIX_YUVNF_3660_H_INCLUDED
#define CHROMATIX_YUVNF_3660_H_INCLUDED

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


typedef struct _yuvnf_reg_filter_t
{
    unsigned int   bypass_symfilter;
    unsigned int   inv_sad;
    unsigned int   shift_sad;
    unsigned int   off_sad;

    unsigned int   gain_max_off;
    unsigned int   edge_max_off;
    unsigned int   edge_th;
    unsigned int   shift_textrue;
    unsigned int   blend_low;

    unsigned int   noise_scale;
    double         smooth_w;
    unsigned int   edge_blend_low;
    unsigned int   no_eblend_low;

    unsigned char pg3[2];
    unsigned char pg7[4];
    unsigned char pg9[5];

    unsigned int mult_gauss_en;
    unsigned int blend_x0;
    unsigned int blend_x1;
    unsigned int blend_y0;
    unsigned int blend_y1;

    unsigned int sigma_u_r;                  // range domain
    unsigned int sigma_v_r;
    unsigned int u_desaturation_th;         // desaturation threshold, U
    unsigned int v_desaturation_th;         // desaturation threshold, V
    unsigned int m_uv_impulsive_th;
}yuvnf_reg_filter_t; //add for chicago

typedef struct _yuvnf_manual_cfg_t
{
    unsigned int use_manual;
    yuvnf_reg_filter_t yuvnf_reg_filter;
}yuvnf_manual_cfg_t; //add for chicago



#endif /*CHROMATIX_YUVNF_H_INCLUDED*/

