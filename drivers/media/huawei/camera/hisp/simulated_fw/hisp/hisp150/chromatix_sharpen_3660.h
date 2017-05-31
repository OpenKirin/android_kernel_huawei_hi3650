

#ifndef __CHROMATIX_SHARPEN_3660_H__
#define __CHROMATIX_SHARPEN_3660_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define  SHARPEN_MAX_GROUP 16

typedef struct
{
    int x0;
    int x1;
    int y0_SharpAmt1;
    int y1_SharpAmt1;
    int y0_EdgeAmt;
    int y1_EdgeAmt;
    char  G3[3][3];
    unsigned char  HPFSel;
    unsigned char  EdgeCmp;
    unsigned char  SharpThd1;
    unsigned short SharpThd1MulCoef;
    unsigned char  EdgeThd1;
    unsigned short EdgeThd1MulCoef;
    unsigned char  OvershootAmt;
    unsigned char  UndershootAmt;
    unsigned char  LineDetEn;
    unsigned char  LineThd1;
    unsigned char  LineThd2;
} sharpen_param_t;

typedef struct
{
    //gain is the standard gain
    unsigned int gain;
    //setting data
    sharpen_param_t sharpen_params;
} sharpen_filter_t;

typedef struct
{
    int filter_num;
    sharpen_filter_t filter_data[SHARPEN_MAX_GROUP];
} sharpen_cfg_t;

typedef struct
{
    unsigned int manual[2]; /*0 -AUTO 1-manual */
    sharpen_param_t sharpen_params[2];
} sharpen_cap_manual_param_t;

typedef struct _arsr_reg_filter_t
{
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
} arsr_reg_filter_t;//add for chicago

typedef struct _sharpen_t
{
    arsr_reg_filter_t    arsr_reg_filter;

    unsigned int    texture_analysis_en;
    unsigned int    di_intpl_en;
    unsigned int    no_intpl_en;
    unsigned int    sharpen_en;
    unsigned int    shoot_detect_en;
    unsigned int    skin_ctrl_en;

    unsigned int    y_expect_value;
    unsigned int    u_expect_value;
    unsigned int    v_expect_value;
    int             shoot_grad_sub_thr_low;
    int             shoot_grad_sub_thr_high;
    unsigned int    shoot_grad_alpha;
    unsigned int    intpl_shoot_ctrl;

    unsigned int    diff_low;
    unsigned int    diff_high;

    unsigned int    shp_to_cut_high0;
    unsigned int    shp_to_cut_high1;
    unsigned int    blend_sh_shoot_ctrl;
    unsigned int    sharp_shoot_ctrl_low;
    unsigned int    sharp_shoot_ctrl_high;
    unsigned int    y0_sharp_amt1;
    unsigned int    y1_sharp_amt1;
    unsigned int    y0_edge_amt;
    unsigned int    y1_edge_amt;

    int             center_y;
    int             center_x;
    unsigned int    shiftn;
    unsigned int    arsr_offset_thd;
    unsigned int    arsr_slope;
    unsigned int    arsr_offset_max;
} sharpen_t;

typedef struct _sharpen_manual_cfg_t
{
    unsigned int use_manual;
    sharpen_t sharpenCfg;
}sharpen_manual_cfg_t;//add for chicago

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CHROMATIX_SHARPEN_H__ */
