

#ifndef CHROMATIX_GCD_3660_H_INCLUDED
#define CHROMATIX_GCD_3660_H_INCLUDED

#define GCD_MAX_GROUP      16


typedef struct _gcd_reg_filter_t
{
    unsigned int geq_thr3;
    unsigned int dms_wei2;
    unsigned int fcr_wei1;
    unsigned int fcr_wei2;
    unsigned int fcr_cho;
    unsigned int cac_wei1;
    unsigned int cac_wei2;
    unsigned int low_thr;
    unsigned int base_blend_min; //8bit
    unsigned int edge_low_thld;  //8bit
    unsigned int edge_high_thld; //8bit
    unsigned int edge_div_shift; //5bit
    unsigned int sna_bypass;
    unsigned int flat_bl_bypass;
} gcd_reg_filter_t;

typedef struct
{
    //gain is the standard gain
    unsigned int gain;
    //setting data
    gcd_reg_filter_t reg_filter;
} gcd_filter_t;

typedef struct
{
    unsigned int filter_num;
    gcd_filter_t filter_data[GCD_MAX_GROUP];
} gcd_configure_t;

typedef struct
{
    unsigned int manual[2]; /*0 -AUTO 1-manual */
    gcd_reg_filter_t gcd_params[2];
} gcd_cap_manual_param_t;


typedef struct _gcd_manual_cfg_t
{
    unsigned int use_manual;
    gcd_reg_filter_t gcd_reg_filter;
}gcd_manual_cfg_t;

#endif /*CHROMATIX_GCD_H_INCLUDED*/
