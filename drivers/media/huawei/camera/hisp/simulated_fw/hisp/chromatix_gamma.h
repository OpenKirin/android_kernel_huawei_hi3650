


#ifndef __CHROMATIX_GAMMA_H__
#define __CHROMATIX_GAMMA_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "algo_common.h"
#include "chromatix_ae.h"

#define GAMMA_CALIBRATION_GROUP      3
#define GAMMA_CALIBRATION_SIZE       257
#define GAMMA_REG_SIZE               33
#define MAX_TONE_MAP_SIZE            257

typedef struct _Gamma_Calib_param
{
    HI_U32 gamma_high[257];
    HI_U32 gamma_mid[257];
    HI_U32 gamma_low[257];

    // add
    HI_U16 len;

    //weight_high(Bright), weight_mid(Normal), weight_low(Dark);
    HI_U16 weight_high;
    HI_U16 weight_mid;
    HI_U16 weight_low;

    //weight_hist(Contrast);  weight_dam(Damping Para);
    HI_U16 weight_hist;
    HI_U16 weight_dam;

    //  Alpha Para
    HI_U16 AlphaPara;

}Gamma_Calib_param;


typedef struct _Gamma_CalHist_param
{
    HI_U32 HistPlat[32];
    HI_U16 HistStep[16];
}Gamma_CalHist_param;

typedef struct _Gamma_CalWight_param
{
    HI_U16 DynamicMThd;
    HI_U16 DynamicNThd;

    HI_U32 DeltaThd[16];

}Gamma_CalWight_param;

typedef struct _Gamma_Sensor_Calib_Parameters_Struct{

    Gamma_Calib_param gamma_calib_p;

    Gamma_CalHist_param CalHist_calib_p;

    Gamma_CalWight_param CalWight_calib_p;
}Gamma_Sensor_Calib_Parameters_Struct;

typedef struct _Gamma_Meta_Data_Param_Struct{

    HI_U32 gamma_hw[32];    // low 0-9bit N frame;10-19bit N-1 frame;20-29bit N-2 frame;
    HI_U8 gamma_weight[4];
    HI_U8 auReserved[10];

}Gamma_Meta_Data_Param_Struct;

// Gamma HW Param
typedef struct _Gamma_dynamic_out_struct
{

    // Gamma params
    unsigned int Gamma_out[GAMMA_CALIBRATION_SIZE];

    Gamma_Meta_Data_Param_Struct meta_data_param;

} Gamma_dynamic_out_struct;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __CHROMATIX_GAMMA_H__ */
