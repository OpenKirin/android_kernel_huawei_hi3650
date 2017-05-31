

#ifndef CHROMATIX_H_INCLUDED
#define CHROMATIX_H_INCLUDED
//FIXME: need UNIFY the interface
#include "algo_common_3660.h"
#include "../chromatix_lsc.h"
#include "chromatix_rawnf_3660.h"
#include "chromatix_sharpen_3660.h"
#include "chromatix_cc_3660.h"
#include "../chromatix_drc.h"
#include "../chromatix_gamma.h"
#include "../chromatix_tnr.h"
#include "chromatix_yuvnf_3660.h"
#include "../chromatix_stat3a.h"
#include "../chromatix_af.h"
#include "chromatix_awb_3660.h"
#include "../chromatix_ce.h"
#include "chromatix_gcd_3660.h"
#include "../chromatix_ae.h"
#include "../chromatix_flash.h"

typedef struct
{
    unsigned int a_fixed;
    unsigned int b_fixed;
    unsigned int c_fixed;
    unsigned int d_fixed;
} blc_level_t;

typedef struct
{
    unsigned int gain;
    unsigned int expo;
    unsigned int values[24]; /* 0x0-0x5c 24 regs */
} dpcc_element_t;

//todo
typedef struct
{
    DRC_Sensor_Calib_Parameters_Struct drc_calib;
} drc_configure_t;

typedef struct
{
    Gamma_Sensor_Calib_Parameters_Struct gamma_calib;
} gamma_configure_t;

/* maximum is 16 groups, but maybe less in fact */
#define DPCC_CALIBRATION_GROUP    16

typedef struct
{
  ae_calibration_struct ae_calib;
}ae_config_param_t;

#define DGAMMA_OUT_SIZE      96
#define DGAMMA_OUT_CHANNEL   3
#ifdef DALLAS_CAMERA
#define CORE_FLOW_NUM   3
#else
#define CORE_FLOW_NUM   4
#endif

typedef struct
{
    CC_Sensor_Calib_Parameters_Struct cc_calib;
}cc_config_t;

typedef struct
{
    CE_Sensor_Calib_Parameters_Struct ce_calib;
} ce_config_t;

typedef struct {
    //FE
    blc_level_t blc;
    unsigned int dgamma[CORE_FLOW_NUM][DGAMMA_OUT_SIZE * DGAMMA_OUT_CHANNEL]; // gamma, 96x3, R/G/B
    lsc_configure_t lsc[CORE_FLOW_NUM];
    dpcc_element_t dpcc[CORE_FLOW_NUM][DPCC_CALIBRATION_GROUP];
    ae_config_param_t ae;
    rawnf_config_t rawnf[CORE_FLOW_NUM];
//    stat3a_config_t stat3a;
    af_calib_t    af_calib;
    awb_calib_param_type    awb_calib;
    flash_calib_t flash_calib;

    //BE
    //gcd
    gcd_configure_t gcd[CORE_FLOW_NUM];

    drc_configure_t drc[CORE_FLOW_NUM]; //todo

    //yuv domain
    gamma_configure_t gamma[CORE_FLOW_NUM];

    //sharpen
    sharpen_cfg_t sharpen[CORE_FLOW_NUM]; //reg:0x00-0x1c

    //cc
    cc_config_t cc[CORE_FLOW_NUM];

    /* yuvnf user config */
    yuvnf_config_t yuvnf[CORE_FLOW_NUM];

    /* ce */
    ce_config_t ce[CORE_FLOW_NUM];
	//tnr
    tnr_config_t tnr;
} chromatix_params;

typedef struct _dynamic_cal_data
{
    unsigned int module_mask;
    chromatix_params  chr_params;
}dynamic_cal_data_t;

typedef enum {
    TUNING_FLAG_AUTO = 0,
    TUNING_FLAG_MANUAL = 1,
    TUNING_FLAG_BYPASS = 2,
} tuning_manual_flag_t;

typedef enum
{
    NOT_USE_MANUAL_PARAM = 0,
    USE_MANUAL_PARAM = 1,
} use_manual_param_e;

typedef struct _hisp150_capture_tuning_rawnf_params_t {
    rawnf_manual_cfg_t rawnfs[2];
}hisp150_capture_tuning_rawnf_params_t;

typedef struct _config_capture_tuning_yuvnf_params_t {
    yuvnf_manual_cfg_t  yuvnfs[2];
}hisp150_capture_tuning_yuvnf_params_t;

typedef struct _hisp150_capture_tuning_gcd_params_t {
    gcd_manual_cfg_t  gcds[2];
}hisp150_capture_tuning_gcd_params_t;

typedef struct _hisp150_capture_tuning_sharpen_params_t {
    sharpen_manual_cfg_t  sharpens[2];
}hisp150_capture_tuning_sharpen_params_t;

#endif /*CHROMATIX_H_INCLUDED*/

