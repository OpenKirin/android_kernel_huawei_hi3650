/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       :   product_nv_def.h
  Description     :   ����NV �ṹ�嶨��
  History         :
******************************************************************************/

#ifndef __PRODUCT_NV_DEF_H__
#define __PRODUCT_NV_DEF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define MAX_SINGLE_GUC_BAND_CHECK_NUM       28
#define MAX_SINGLE_TL_BAND_CHECK_NUM        12
#define MAX_NV_GUC_CHECK_ITEM_NUM           32
#define MAX_NV_TL_CHECK_ITEM_NUM            64

/*��ο��ṹ������*/
typedef struct
{
    int reserved;  /*note */
}PRODUCT_MODULE_STRU;

typedef struct
{
    u32 uwGucCrcResult;                     		/* GUc����NV��У���� */
    u32 uwTlCrcResult;                      		/* TL����NV��У���� */
    u32 uwGucM2CrcResult;                   		/* GUC����NV��У���� */
}NV_CRC_CHECK_RESULT_STRU;

typedef struct
{
    u16 uhwTransmitMode;                       		/* ָʾ����ķ���ģʽ */
    u16 uhwBand;                              		/* ָʾ�����BAND�� */
    u16 uhwEnable;                              	/* ָʾ�Ƿ���Ч */
    u16 uhwValidCount;                              	/* ָʾ��Ч���ݵĸ��� */
    u16 auhwNeedCheckID[MAX_SINGLE_GUC_BAND_CHECK_NUM]; /* ������Ҫ����NV_IDֵ */
}SINGLE_GUC_BAND_NV_ID_STRU;

typedef struct
{
    u16 uhwTransmitMode;                       		/* ָʾ����ķ���ģʽ */
    u16 uhwBand;                              		/* ָʾ�����BAND�� */
    u16 uhwEnable;                              	/* ָʾ�Ƿ���Ч */
    u16 uhwValidCount;                              	/* ָʾ��Ч���ݵĸ��� */
    u16 auhwNeedCheckID[MAX_SINGLE_TL_BAND_CHECK_NUM]; 	/* ������Ҫ����NV_IDֵ */
}SINGLE_TL_BAND_NV_ID_STRU;

typedef struct
{
    SINGLE_GUC_BAND_NV_ID_STRU astNVIDCheckItem[MAX_NV_GUC_CHECK_ITEM_NUM];  	/* ������Ҫ����NV_IDֵ */
}NV_GUC_CHECK_ITEM_STRU;

typedef struct
{
    SINGLE_TL_BAND_NV_ID_STRU astNVIDCheckItem[MAX_NV_TL_CHECK_ITEM_NUM];   	/* ������Ҫ����NV_IDֵ */
}NV_TL_CHECK_ITEM_STRU;


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif


