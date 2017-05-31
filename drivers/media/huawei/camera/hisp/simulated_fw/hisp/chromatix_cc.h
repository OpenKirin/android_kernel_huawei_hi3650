

#ifndef __CHROMATIX_CC_H__
#define __CHROMATIX_CC_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "algo_common.h"

#define CHROMA_ILLUM_NUM  3
#define CHROMA_TYPE_NUM   (CHROMA_ILLUM_NUM+1)
#define CHROMA_SEGM_NUM   (CHROMA_TYPE_NUM+1)
#define CHROMA_COM_MAX_NUM  3

typedef enum {
    CC_LIGHT_D75 = 0,
    CC_LIGHT_D65,
    CC_LIGHT_D50,
    CC_LIGHT_TL84,
    CC_LIGHT_CWF,
    CC_LIGHT_A,
    CC_LIGHT_H,
    CC_LIGHT_NUM
}CC_light_enum;

typedef enum{
    CC_FLU_LIGHT_NUM
}CC_Flu_Light_Enum;

/*****************************************************************************
                   CC Calibrate or Set Parameter Structure
*******************************************************************************/
//Sub Function Enable of CC Module Set Parameters
typedef struct _CC_SubFunc_Enable_Struct{
    HI_BOOL CC_Frame_En;
    HI_BOOL CC_CCM_En;
    HI_BOOL CCM_Adt_Luma_En;
    HI_BOOL CCM_Sat_Illum_En;
    HI_BOOL CCY_Kpt_Const_En;
    HI_BOOL CC_Hist_Statis_En;
    HI_BOOL CC_DeFlare_En;
}CC_SubFunc_Enable_Struct;

//CCM and CCT of CC Module Calibration Parameters
typedef struct _CC_Mat_Light_Struct{
    HI_S16 mat_cct_vec[CHROMA_TYPE_NUM][12];
    struct_light_point cct_info_vec[CHROMA_TYPE_NUM];
    HI_S32 bv_light_vec[CHROMA_TYPE_NUM];
    HI_S32 gain_light_vec[CHROMA_TYPE_NUM];
    HI_S32 sat_light_vec[CHROMA_TYPE_NUM];
}CC_Mat_Light_Struct;

//CCM Adaptation with Pixel's Y of CC Module Set Parameters
typedef struct _CCM_Adt_Luma_Struct{
    HI_U32 CC_Exp_Gain_NorDum_Thr;
    HI_U32 CC_Exp_Gain_DumLow_Thr;
    HI_U32 CC_Exp_Gain_LowDark_Thr;
    HI_U16 CC_Mat_Low_Adt_Normal[3];
    HI_U16 CC_Mat_Low_Adt_DumLow[3];
    //HI_U16 CC_Mat_Low_Adt_Low[3];
    HI_U16 CC_Mat_Low_Adt_Dark[3];
    HI_U16 CC_Mat_High_Adt_Normal[3];
}CCM_Adt_Luma_Struct;

//CCM Saturation with Illumination of CC Module Set Parameters
typedef struct _CCM_Sat_Illum_Struct{
    unsigned int CCM_Exp_Gain_Dummy;
    unsigned int CCM_Exp_Gain_Low;
    unsigned int CCM_Exp_Gain_Dark;
    unsigned int CCM_Sat_Factor_Low;
    unsigned int CCM_Sat_Factor_Dark;
}CCM_Sat_Illum_Struct;

//CCM Saturation with Ratio of Statistical Mean and Target Mean in AE Module
typedef struct _CCM_Sat_AERatio_struct
{
    //Normal Median Low Dark
    HI_U32 AE_Ratio_Vec[4];
    HI_U16 Sat_Val_Vec[4];
}CCM_Sat_AERatio_struct;

//Pixel's Y Keep Constant with Illumination of CC Module Set Parameters
typedef struct _CCY_Const_Illum_Struct{
    HI_U16 CCY_ExpGain_Dummy;
    HI_U16 CCY_ExpGain_Dark;
}CCY_Const_Illum_Struct;

//Flare Removal of CC Module Set Parameters
typedef struct _CC_Flare_Removal_Struct{
    HI_U16 downSampleFactorX;
    HI_U16 downSampleFactorY;
    HI_U16 rgb2y_r_coef;
    HI_U16 rgb2y_g_coef;
    HI_U16 rgb2y_b_coef;
    HI_U32 Flare_EXP_EI_THR;
    HI_U32 Flare_EXP_AVGY_THR;
    HI_U32 Flare_AWB_GAIN_THR;
    HI_U16 Hist_Step_Base;
    HI_U16 HIST_STEP_MAX;
    HI_U16 FLARE_MAX_THR;
    HI_U32 FLARE_HIST_AREA;
    HI_U8  flare_iter_val1; //flare offset iterative update for unstable
    HI_U8 flare_iter_val2; //flare offset iterative update for stable
}CC_Flare_Removal_Struct;

//CC Module Calibrate or Set Parameters Summary
typedef struct _CC_Sensor_Calib_Parameters_Struct{
    CC_SubFunc_Enable_Struct CC_SubFunc_Set_Enable;
    CC_Mat_Light_Struct CC_Mat_Calib_Param[CC_LIGHT_NUM];
    CCM_Adt_Luma_Struct CCM_Adt_Luma_Set_Param;
    CCM_Sat_Illum_Struct  CCM_Sat_Illum_Set_Param;
    CCM_Sat_AERatio_struct CCM_Sat_AERatio_Set_Param;
    CCY_Const_Illum_Struct CCY_Const_Illum_Set_Param;
    CC_Flare_Removal_Struct CC_Flare_Removal_Set_Param;
	HI_U16 CC_CCM_Iterate[3];
}CC_Sensor_Calib_Parameters_Struct;


/***************************************************************************
                   CC Run State Information Structure
***************************************************************************/
typedef struct _CHROMA_CALIB_STATE_Struct{
    HI_BOOL Chroma_Calib_EN;
    HI_BOOL Chroma_Flu_Calib_En;
    HI_BOOL Flash_Mode_En;
    HI_U32 Chroma_Calib_CT_Index;
    HI_U32 Chroma_Calib_Illum_Index;
    HI_U32 Chroma_Calib_CCM_Sat;
    HI_U32 Chroma_Calib_SCE_Sat;
    HI_U32 Flash_CC_Weight;
    HI_U32 Flash_Cold_Weight;
}CHROMA_CALIB_STATE_Struct;

typedef struct _CC_CCT_ILLUM_STATE_Struct{
    struct_light_point cct_info_vec[CC_LIGHT_NUM];
    HI_U8 cct_illum_vec[CC_LIGHT_NUM];
    HI_U16 ccm_illum_weight[CC_LIGHT_NUM][CHROMA_SEGM_NUM][2];
}CC_CCT_ILLUM_STATE_Struct;

typedef struct _CC_CCM_COM_STATE_Struct{
    struct_light_point cct_info_val;
    HI_U8 ccm_com_num;
    HI_U8 ccm_com_vec[CHROMA_COM_MAX_NUM];
    HI_U16 ccm_com_weight[CHROMA_COM_MAX_NUM];
}CC_CCM_COM_STATE_Struct;

typedef struct _CC_ChlHist_Stat_Struct{
    HI_U8 chl_rgb_mode; //0-R; 1-G; 2-B
    HI_U32 chl_hist_vec[64];
}CC_ChlHist_Stat_Struct;

typedef struct _CC_Meta_Data_Param_Struct{
    HI_U8 cc_preview_flag;
    HI_U8 ccm_com_num;
    HI_U8 ccm_com_vec[3];
    HI_U8 cct_illum_vec[3];
    HI_U16 ccm_com_weight[3];
    HI_S16 CCM_HW_MAT[9];
    HI_U16 sat_light_vec[4];
    HI_U16 sat_illum_val;
    HI_U16 sat_ratio_val;
}CC_Meta_Data_Param_Struct;

typedef struct _CC_Ref_Out_Param_struct{
    CHROMA_CALIB_STATE_Struct chroma_calib_state;
    CC_CCT_ILLUM_STATE_Struct cct_illum_state;
    CC_CCM_COM_STATE_Struct ccm_com_state;
    CC_ChlHist_Stat_Struct chl_hist_stat;
    CC_Meta_Data_Param_Struct meta_data_param;
}CC_Ref_Out_Param_struct;

typedef struct _CC_reg_out_struct{
    HI_U32 hist_flare[64];          //u20.0 histogram.
}CC_reg_out_struct;

typedef struct _CC_HWReg_Dynamic_Param_struct
{
    HI_S16 colorCorrectMat[12];     //1s3.10,  color matrix[0~8]
                                                   //1s13.0,  color matrix[9~11] for offset
    HI_U16 brightThresh[3];         //u12.0, Bright pixel desaturation threshold.
    HI_U16 darkThresh[3];           //u12.0, Dark pixel desaturation threshold.
    HI_U16 histMinValue;            //u14.0, Base min value for histogram.
    HI_U16 histShiftBit;            //u4.0,  Shift pixel value to get sparse histogram.
    HI_U32 CC_darkCoefKab;          //u0.15, reciprocal for dark weight coeficient between AB.
    HI_U32 CC_darkCoefKbc;          //u0.15, reciprocal for dark weight coeficient between BC.
    HI_U32 CC_brightCoefKbc;        //u0.15, reciprocal for bright weight coeficient between AB
    HI_U32 CC_brightCoefKab;        //u0.15, reciprocal for bright weight coeficient between BC
    HI_U8  bPixYConst;                //u1.0  switch for Pixel's Y keep constant
    HI_U16 pix_ycoef_val;           //u6.0  pixel's y coeffcient value
}CC_HWReg_Dynamic_Param_struct;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ALGO_PARAM_CC_H__ */
