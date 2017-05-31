

#ifndef __CHROMATIX_CE_H__
#define __CHROMATIX_CE_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "algo_common.h"
#include "chromatix_cc.h"

#define MCE_LIGHT_NUM          3
#define MCE_GRID_SIZEH        17
#define MCE_GRID_SIZEW        17
#define MCE_CLUSTER_MAX_NUM    5
#define MCE_CLUSTER_ITEM_MAX   4

/*****************************************************************************
                         CE Calibrate or Set Parameter Structure
*******************************************************************************/
//Sub Function Enable of CC Module Set Parameters
typedef struct _CE_SubFunc_Enable_Struct{
    HI_BOOL CE_Frame_En;
    HI_BOOL CE_SCE_En;
    HI_BOOL SCE_Face_En;
    HI_BOOL SCE_Statis_En;
    HI_BOOL CE_MCE_En;
    HI_BOOL CE_Gray_Filter_En;
}CE_SubFunc_Enable_Struct;

//SCE of CE Module Calibration Parameters
typedef struct _CE_SCE_Light_Struct{
    HI_U8 sce_cct_mat[CHROMA_TYPE_NUM][256];
    HI_U8 sat_light_vec[CHROMA_TYPE_NUM];
}CE_SCE_Light_Struct;

typedef struct _CE_MCE_CLUSTER_Struct{
    HI_U8 cluster_mem_num;
    HI_U8 cluster_mem_vec[MCE_CLUSTER_ITEM_MAX];
}CE_MCE_CLUSTER_Struct;

//MCE of CE Module Calibration Parameters
typedef struct _CE_MCE_CLUSTER_Light_Struct{
    CE_MCE_CLUSTER_Struct mce_cluster_info;
    HI_S8 mce_gridu_mat[CHROMA_TYPE_NUM][MCE_GRID_SIZEH][MCE_GRID_SIZEW];
    HI_S8 mce_gridv_mat[CHROMA_TYPE_NUM][MCE_GRID_SIZEH][MCE_GRID_SIZEW];
    struct_light_point cct_info_vec[CHROMA_TYPE_NUM];
}CE_MCE_CLUSTER_Light_Struct;

//Gray Filter/De-saturation Set Parameters
typedef struct _CE_Gray_Filter_Struct{
    HI_U32 CE_ExpGain_NorDum;
    HI_U32 CE_ExpGain_DumLow;
    HI_U32 CE_ExpGain_LowDark;
    unsigned char UVgrayFilterThreshInit_Normal[9];
    unsigned char UVgrayFilterThreshInit_DumLow[9];
    unsigned char UVgrayFilterThreshInit_Dark[9];
    unsigned char UVgrayFilterStrengthInit_Normal[9];
    unsigned char UVgrayFilterStrengthInit_DumLow[9];
    unsigned char UVgrayFilterStrengthInit_Dark[9];
}CE_Gray_Filter_Struct;

//Skin Saturation Set Parameters
typedef struct _CE_Skin_Sat_Struct{
    HI_U8 HueStatDSFactor;
    HI_U8 skin_max_sat;
    HI_U8 lip_max_sat;
    HI_U16 Hist_SumMin_Thr;  //U0.10B
    HI_U16 Hist_AreaPos_Thr;  //U0.10B
    HI_U16 Hist_AreaNeg_Thr;
    HI_U16 Hue_Rotate_Factor[MCE_LIGHT_NUM];  //U0.10B
    HI_U16 Skin_Hue_Iter[MCE_LIGHT_NUM];
    HI_S16 Skin_CCT_Hue[MCE_LIGHT_NUM*2];
    HI_S16 Skin_DefPos_Hue[MCE_LIGHT_NUM*2];
    HI_S16 Skin_DefNeg_Hue[MCE_LIGHT_NUM*2];
    HI_U16 Hue_Range_Pos[MCE_LIGHT_NUM*2]; //0.8B
    HI_U16 hue_Range_Neg[MCE_LIGHT_NUM*2];
    HI_U8 Hue_DifInner_Factor[MCE_LIGHT_NUM*2];  //U0.8B
    HI_U8 Hue_DifPos_Factor[MCE_LIGHT_NUM*2];
    HI_U8 Hue_DifNeg_Factor[MCE_LIGHT_NUM*2];
}CE_Skin_Sat_Struct;

typedef struct _CE_Illum_ADT_Struct{
    HI_U8  mceStrength;
}CE_Illum_ADT_Struct;

//CE Module Calibrate or Set Parameters Summary
typedef struct _CE_Sensor_Calib_Parameters_Struct{
    CE_SubFunc_Enable_Struct CE_SubFunc_Set_Enable;
    CE_SCE_Light_Struct CE_SCE_Calib_Param[CC_LIGHT_NUM];
    CE_MCE_CLUSTER_Light_Struct CE_MCE_Calib_Param[MCE_LIGHT_NUM];
    CE_Gray_Filter_Struct CE_Gray_Filter_Set_Param;
    CE_Skin_Sat_Struct CE_Skin_Sat_Param;
    CE_Illum_ADT_Struct CE_Illum_Adt_Param;
    HI_U16 CE_SCE_Iterate[3];
    HI_U16 CE_MCE_Iterate[3];
}CE_Sensor_Calib_Parameters_Struct;

typedef struct _CE_HWReg_Dynamic_Param_struct{
    unsigned int bIsFaceValid; //Is face detection valid: u1.0bit
    HI_U16 facePos[4];  //The position of the biggest face. LUx,LUy,RDx,RDy u13.0bit
    HI_S8  gainAlongHue[256];  //UV gain for every hue value. range:[0,2]/[-128,127] s8.0bit
    HI_U8  mceStrength;       //MCE strength affected by current ISO. range:[0,32], u0.6bit
    HI_U8  gridInfo[128][5]; //u8.0bit
    HI_U8  gridFlag[256];    //u8.0bit
    HI_U8  UVgrayFilterThresh[9]; //UV Filter thresh value u8.0 bit
    HI_U8  UVgrayFilterStrength[9];   //UV gray filter strength: u5.0 bit
    HI_U16  UVgrayThreshRecip[9];   //Filter threshold reciprocal for division operation. u0.15 bit
}CE_HWReg_Dynamic_Param_struct;

typedef struct _CE_Stat_struct{
    HI_U8  pMaxSaturation[256];  //u8.0bit
    HI_U16 pHistH[64];           //u12.0bit.
} CE_Stat_struct;

typedef struct _CE_Meta_Data_Param_Struct{
	HI_U8   ce_preview_flag;
	HI_U8   mce_com_num;
	HI_U8   mce_com_vec[3];
	HI_U8   mce_illum_vec[3];
	HI_U16  mce_com_weight[3];
	HI_U16  sce_sat_vec[4];
	HI_S16  skin_hue_val;
	HI_S16  skin_iter_val;
	HI_S16  skin_rotate_hue;
	HI_U16  rotate_factor_val;
	HI_U32  ROI_Sum_Val;
	HI_U32  Hist_Sum_Val;
}CE_Meta_Data_Param_Struct;

typedef struct _CE_Ref_Out_Param_struct{
    HI_BOOL CE_Stat_En;
    HI_BOOL SCE_Skin_Flag;
	HI_BOOL MCE_Skin_Flag;
	HI_S8 skin_iter_val;
    HI_U8 Sat_Max_Vec[256];
    HI_S8 Face_GridU_Mat[MCE_GRID_SIZEH][MCE_GRID_SIZEW];
    HI_S8 Face_GridV_Mat[MCE_GRID_SIZEH][MCE_GRID_SIZEW];
	CE_Meta_Data_Param_Struct meta_data_param;
}CE_Ref_Out_Param_struct;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __ALGO_PARAM_CE_H__ */
