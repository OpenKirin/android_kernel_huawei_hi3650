#ifndef CHROMATIX_TNR_H_INCLUDED
#define CHROMATIX_TNR_H_INCLUDED

#define TNR_MAX_GROUP            16

typedef struct tnr_calib_param {

	unsigned int ltb[17];

	unsigned int alpha_thd; 
	unsigned int motion_thd;
	int          motion_slope; 
	unsigned int local_offset_max;
	unsigned int weight_slope;
	unsigned int  global_thd;

	unsigned int mtb[30];
	unsigned int mtbuv[30];

} tnr_calib_param;

typedef struct
{
    //gain is the standard gain
    unsigned int gain;
    //setting data
    tnr_calib_param reg_filter;
}tnr_filter_t;

typedef struct
{
    int filter_num;
    tnr_filter_t filter_data[TNR_MAX_GROUP];
} tnr_config_t;

#endif /*CHROMATIX_TNR_H_INCLUDED*/

