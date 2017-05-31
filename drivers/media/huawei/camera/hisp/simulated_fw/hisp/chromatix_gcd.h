

#ifndef CHROMATIX_GCD_H_INCLUDED
#define CHROMATIX_GCD_H_INCLUDED

#define GCD_MAX_GROUP      16

typedef struct
{
    unsigned int geq_thr3;
    unsigned int dms_wei2;
    unsigned int fcr_wei1;
    unsigned int fcr_wei2;
    unsigned int fcr_cho;
    unsigned int cac_wei1;
    unsigned int cac_wei2;
    unsigned int low_thr;
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

#endif /*CHROMATIX_GCD_H_INCLUDED*/
