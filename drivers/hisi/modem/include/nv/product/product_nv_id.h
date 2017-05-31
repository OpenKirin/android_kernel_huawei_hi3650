/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       :   product_nv_id.h
  Description     :   productNV IDö�ٶ���
  History         :

******************************************************************************/

#ifndef __PRODUCT_NV_ID_H__
#define __PRODUCT_NV_ID_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*
 *  NV ID ����Ӱ���С��������
 */

typedef enum
{
    NV_ID_CRC_CHECK_RESULT  = 0xc350,
    NV_ID_GUC_CHECK_ITEM    = 0xc351,
    NV_ID_TL_CHECK_ITEM     = 0xc352,
    NV_ID_GUC_M2_CHECK_ITEM = 0xc353,
    NV_ID_PRODUCT_END       = 0xcb1f
}NV_ID_PRODUCT_ENUM;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


