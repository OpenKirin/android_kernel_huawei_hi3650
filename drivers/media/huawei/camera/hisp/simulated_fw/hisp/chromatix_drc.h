


#ifndef __CHROMATIC_DRC_H__
#define __CHROMATIC_DRC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

typedef struct _DRC_Calib_param
{
    // High bit
    // 1
    HI_U16 Rat_tabH_original[257];
    // 3
    HI_U16 Rat_tabH_lowcontrast[257];

    // Low bit
    // 1
    HI_U16 Rat_tabL_original[257];
    // 3
    HI_U16 Rat_tabL_pull[257];

    HI_U16 DRC_Alpha[17];
    HI_U16 LUT_w[17];

    HI_U16 len;
        HI_U16 weight_sub[4];
    HI_U16 weight_dam;

}DRC_Calib_param;


typedef struct _DRC_Calc_param
{
    HI_U16 OffsetThd[4][15];
    HI_U32 Histplat[4][32];

    //
    HI_U16 ROIFlag;
    HI_U16 AddFlag;
    HI_U32 ROIBuff[16];
    HI_U16 ROIThd[4][15];
    HI_U32 ROIPlat[4][32];
}DRC_Calc_param;


// DRC hw_stat Param
typedef struct _drc_hw_stat_param
{
    HI_U32 Avermatrix[16 * 16];            //10bit; 10.0
}drc_hw_stat_param;

// DRC fw_stat Param
typedef struct _drc_fw_stat_param
{
    HI_U16 Affinity;
    HI_U16 MN_dynamic[2];
    HI_U16 LocationMax[32];
    HI_U32 CosAngle[32];
}drc_fw_stat_param;




//DRC Module Calibrate or Set Parameters Summary
typedef struct _DRC_Sensor_Calib_Parameters_Struct{

    DRC_Calib_param drc_calib_p;
    DRC_Calc_param drc_Calc_p;

}DRC_Sensor_Calib_Parameters_Struct;


typedef struct _DRC_Meta_Data_Param_Struct{

    HI_U8 DRC_Rat_tabH[64];
    HI_U8 DRC_Rat_tabL[64];
    HI_U8 MN_dynamic[2];
    HI_U8 weight_init[2];
    HI_U8 weight_s[4];
    HI_U8 auReserved[10];

}DRC_Meta_Data_Param_Struct;

// DRC HW Param
typedef struct _drc_dynamic_out_struct
{

    // ToneMapping params
    short DRC_ra_tab[17];                   // 8bit
    short DRC_OffsetAlpha[17];      // 8bit
    short DRC_Rat_tabH[65];         // 10bit
    short DRC_Rat_tabL[65];             // 10bit

    // Avermatrix
    short Avermatrix_in[16*16];           //10bit; 10.0
    DRC_Meta_Data_Param_Struct meta_data_param;

} drc_dynamic_out_struct;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CHROMATIC_DRC_H__ */
