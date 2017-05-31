

#ifndef  TAF_CDMA_PLUS_TRANSLATE_H
#define  TAF_CDMA_PLUS_TRANSLATE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_INTER_PREFIX_CODE_MAX_LEN                           (8)

#define TAF_CODE_ENTITY_HRADER_MAX_LEN                          (8)

#define TAF_DIAL_PREFIX_CODE_MAX_LEN                            (4)
#define TAF_COUNTRY_CODE_MAX_LEN                                (8)
#define TAF_PLUS_DIGIT_LEN                                      (1)
#define TAF_MT_MAX_BCD_NUM_LEN                                  (20)
#define TAF_MT_MAX_ASCII_NUM_LEN                                (40)
#define TAF_MO_MAX_BCD_NUM_LEN                                  (32)
#define TAF_MO_MAX_ASCII_NUM_LEN                                (64) 
#define TAF_COUNTRY_LIST_LEN                                    (sizeof(g_astTafCountryList)/sizeof(TAF_COUNTRY_DIAL_CODE_INFO)) 

#define TAF_INVALID_SID                                         (-1)

#define TAF_MCORE_INVALID_MCC                                    (0xFFFFFFFF)        /* MCC����Чֵ */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_PLUS_TRANSLATE_CALL_TYPE_ENUM
 �ṹ˵��  : �Ӻ�ת��ʱ��������
  1.��    ��   : 2015��1��4��
    ��    ��   : c00299063
    �޸�����   : ����
*****************************************************************************/
enum TAF_PLUS_TRANSLATE_DIAL_TYPE_ENUM
{
    TAF_PLUS_TRANSLATE_DIAL_TYPE_VOICE,
    TAF_PLUS_TRANSLATE_DIAL_TYPE_SMS,
    TAF_PLUS_TRANSLATE_DIAL_TYPE_BUTT
};
typedef VOS_UINT8 TAF_PLUS_TRANSLATE_DIAL_TYPE_ENUM_U8;

enum TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM
{
    TAF_PLUS_TRANSLATE_NUM_INTERNATIONAL = 0x91,
    TAF_PLUS_TRANSLATE_NUM_NATIONAL      = 0xa1,
};
typedef VOS_UINT8 TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : TAF_COUNTRY_DIAL_CODE_INFO
 �ṹ˵��  : �����б���Ϣ
  1.��    ��   : 2015��1��4��
    ��    ��   : c00299063
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                         usSidRangeStart;                                      /*SID ��Χ��ʼֵ */
    VOS_UINT16                         usSidRangeEnd;                                        /*SID ��Χ����ֵ */
    VOS_UINT16                         usCc;                                                 /*country code */
    VOS_UINT16                         usMcc;                                                /*mobile country code */
    VOS_INT8                           acInterPrefixCode[TAF_INTER_PREFIX_CODE_MAX_LEN];
    VOS_INT8                           acNumEntityHeader[TAF_CODE_ENTITY_HRADER_MAX_LEN];      /*ͨ�����к����ͷ�� exp: 13... ,15...,*/
    VOS_INT8                           acDialPrefixCode[TAF_DIAL_PREFIX_CODE_MAX_LEN];
    VOS_UINT8                          ucNetworkSupportPlusFlg;                              /*��ǰ�����Ƿ�֧��"+"�Ŵ���*/
    VOS_INT8                           aucReserve[3];
}TAF_COUNTRY_DIAL_CODE_INFO;



/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
TAF_COUNTRY_DIAL_CODE_INFO* TAF_GetCountryListAddr(
    VOS_VOID
);

VOS_INT32 TAF_ConvertHomeMccToSidRange(
    VOS_UINT16                          usHomeMcc
);

VOS_UINT16 TAF_GetMccOfCountryList(
    VOS_UINT16                         Index
);

VOS_UINT16 TAF_GetCcOfCountryList(
    VOS_UINT16                         Index
);

VOS_UINT8* TAF_GetIpcOfCountryList(
    VOS_UINT16                         Index
);

VOS_UINT8* TAF_GetDpcOfCountryList(
    VOS_UINT16                         Index
);

VOS_UINT8* TAF_GetNehOfCountryList(
    VOS_UINT16                         Index
);

VOS_UINT8 TAF_GetNehLenOfCountryList(
    VOS_UINT16                         Index
);

VOS_UINT8 TAF_GetIpcLenOfCountryList(
    VOS_UINT16                         Index
);

VOS_UINT8 TAF_GetDpcLenOfCountryList(
    VOS_UINT16                         Index
);

VOS_UINT8 TAF_GetCcLenOfCountryList(
    VOS_UINT16                         Index
);

VOS_VOID TAF_GetInfoInCountryList(
    VOS_INT32                           lSid,
    VOS_UINT16                         *pusMccFirstMatchEntryIndex,
    VOS_UINT16                         *pusMccMatchEntryNum
);

VOS_UINT32 TAF_ConvertASCIINumToUint(
    VOS_UINT8                           ucstartDigit,
    VOS_UINT8                           ucDigitsLen,
    VOS_UINT8                          *pucASCIINum
);

VOS_VOID TAF_InsertDigitsInNumHeader(
    VOS_UINT8                          *pstInsertDigits,
    VOS_UINT8                           ucInsertDigitsLen,
    VOS_UINT8                          *pucASCIINum,
    VOS_UINT8                          *pstNumLen
);

VOS_VOID TAF_SkipDigitsOfNumHeader(
    VOS_UINT8                          *pucASCIINum,
    VOS_UINT8                          *pucNumLen,
    VOS_UINT8                           ucSkipDigitsLen
);

VOS_UINT8 TAF_IsNumEntityHeaderInCountryList(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT16                          usMccMatchEntryNum,
    VOS_UINT8                          *pucASCIINum
);

VOS_UINT8 TAF_IsIpcAndCcInCountryList(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT8                          *pucASCIINum
);

VOS_UINT8 TAF_IsCcInCountryList(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT8                          *pucASCIINum
);

VOS_UINT8 TAF_TranslatePlusToNationalNum(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT16                          usMccMatchEntryNum,
    VOS_UINT8                          *pucCurASCIINum,
    VOS_UINT8                          *pucCurNumLen
);

VOS_VOID TAF_TranslatePlusToInternationalNum(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT16                          usMccMatchEntryNum,
    VOS_UINT8                          *pucCurASCIINum,
    VOS_UINT8                          *pucCurNumLen,
    TAF_PLUS_TRANSLATE_DIAL_TYPE_ENUM_U8                    enDialType
);

VOS_VOID TAF_TranslatePlusToNum(
    VOS_INT32                                               lSid,
    TAF_PLUS_TRANSLATE_DIAL_TYPE_ENUM_U8                    enDialType,
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                    *penNumType,
    VOS_UINT8                                              *pucASCIINum,
    VOS_UINT8                                              *pucNumLen
);

VOS_UINT8 TAF_IsIpcInCountryList(
    VOS_UINT16                          usMccFirstMatchEntryIndex,
    VOS_UINT8                          *pucASCIINum
);

VOS_UINT8 TAF_TranslateInternationalNumToPlus(
    VOS_UINT16                                              usMccFirstMatchEntryIndex,
    VOS_UINT8                                              *pucASCIINum,
    VOS_UINT8                                              *pucNumLen,
    TAF_PLUS_TRANSLATE_DIAL_TYPE_ENUM_U8                    enDialType
);

VOS_UINT8 TAF_TranslateNationalNumToPlus(
    VOS_UINT16                                              usMccFirstMatchEntryIndex,
    VOS_UINT8                                              *pucASCIINum,
    VOS_UINT8                                              *pucNumLen,
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                    *penNumType
);

VOS_VOID TAF_TranslateNumToPlus(
    VOS_INT32                                               lSid,
    TAF_PLUS_TRANSLATE_DIAL_TYPE_ENUM_U8                    enDialType,
    TAF_PLUS_TRANSLATE_NUM_TYPE_ENUM_U8                    *penNumType,
    VOS_UINT8                                              *pucASCIINum,
    VOS_UINT8                                              *pucNumLen
);

VOS_UINT32 TAF_QueryMccWithSid(
    VOS_INT32       lSid
);

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#pragma pack(4)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* TAF_CDMA_PLUS_TRANSLATE_H */


