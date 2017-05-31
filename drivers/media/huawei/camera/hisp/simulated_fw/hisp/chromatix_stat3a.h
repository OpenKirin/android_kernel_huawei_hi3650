


#ifndef CHROMATIX_STAT3A_H_INCLUDED
#define CHROMATIX_STAT3A_H_INCLUDED

typedef struct
{
    int af_grad_sel;
    int af_square_en;
    int af_fdog_dog;
    int af_thld_en;
    int af_thld;
    int af_x_v_coef[5];
    int af_x_h_coef[5];
    int af_y_v_coef[5];
    int af_y_h_coef[5];
    int ae_underexposure_thld;
    int ae_overexposure_thld;
    int awb_color_value_min;
    int awb_color_value_max;
    int awb_grayzone_top_b;
    int awb_grayzone_top_k;
    int awb_grayzone_bottom_b;
    int awb_grayzone_bottom_k;
    int awb_grayzone_left_b;
    int awb_grayzone_left_k;
    int awb_grayzone_right_b;
    int awb_grayzone_right_k;
} stat3a_config_t;



#endif /*CHROMATIX_STAT3A_H_INCLUDED*/



