


#ifndef __CHROMATIX_SHARPEN_H__
#define __CHROMATIX_SHARPEN_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define  SHARPEN_MAX_GROUP 16

typedef struct
{
    int x0;
    int x1;
    int y0_SharpAmt1;
    int y1_SharpAmt1;
    int y0_EdgeAmt;
    int y1_EdgeAmt;
    char  G3[3][3];
    unsigned char  HPFSel;
    unsigned char  SharpSel; //1-bit
    unsigned char  EdgeCmp;
    unsigned char  SharpThd1;
    unsigned short SharpThd1MulCoef;
    unsigned char  EdgeThd1;
    unsigned short EdgeThd1MulCoef;
    unsigned char  dir_scale; //3-bit
    unsigned char  ShootSel;  //2-bit
    unsigned char  OvershootAmt;
    unsigned char  UndershootAmt;
    unsigned char  LineDetEn;
    unsigned char  LineThd1;
    unsigned char  LineThd2;
} sharpen_param_t;

typedef struct
{
    //gain is the standard gain
    unsigned int gain;
    //setting data
    sharpen_param_t sharpen_params;
} sharpen_filter_t;

typedef struct
{
    int filter_num;
    sharpen_filter_t filter_data[SHARPEN_MAX_GROUP];
} sharpen_cfg_t;

typedef struct
{
    unsigned int manual; /*0 -AUTO 1-manual */
    sharpen_param_t sharpen_params;
} sharpen_cap_manual_param_t;

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __CHROMATIX_SHARPEN_H__ */
