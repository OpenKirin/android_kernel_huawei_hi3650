


#ifndef CHROMATIX_FLASH_H_INCLUDED
#define CHROMATIX_FLASH_H_INCLUDED

typedef struct {
unsigned short r_gain;
unsigned short gr_gain;
unsigned short gb_gain;
unsigned short b_gain;
} flash_awb_gain_t;

typedef struct _flash_calib_t
{
    /* aec step */
    unsigned char aec_slow_step; //slow_step

    /* assistant af */
    unsigned int gainth_high;

    /* flash capture */
    unsigned int lowlight_th;
    unsigned int default_target_y;
    unsigned char trigger_lum_ratio;

    unsigned int test_max_cnt;

    unsigned int preflash_capflash_gap;
    unsigned int lastcapflash_nowpreflash_sleep;

    unsigned int expo_value_threshold;

    /* front awb */
    flash_awb_gain_t preset_awb;
} flash_calib_t;

#endif /*CHROMATIX_AF_H_INCLUDED*/
