

#ifndef __CSSNVINTERFACE_H__
#define __CSSNVINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "vos.h"


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  #pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define CSS_NV_MAX_COMM_BAND_NUM           (22)

/*ĿǰLRRCԤ��Ƶ��Ϊ16����������Ҳ��Ϊ16��
  WASԤ��Ƶ��9����������16��
  GASԤ��Ƶ��5�������8����Ԥ��Ƶ��0�������16��*/

#define CSS_NV_MAX_PREF_MNC_NUM            (45)
#define CSS_NV_MAX_PREF_ARFCN_NUM          (5)





/*****************************************************************************
  3 Massage Declare
*****************************************************************************/

/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
 �ṹ��     : CSS_BAND_PARA_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : ���õ�BAND���Լ���BAND��Ӧ�Ľ��뼼��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           bitOpLteSupport: 1;
    VOS_UINT8                           bitOpTdsSupport: 1;
    VOS_UINT8                           bitOpWcdmaSupport: 1;
    VOS_UINT8                           bitOpGsmSupport: 1;
    VOS_UINT8                           bitOpSpare: 4;

    VOS_UINT8                           ucBandInd;
    VOS_UINT8                           aucReserved[2];
} CSS_BAND_PARA_STRU;

/*****************************************************************************
 �ṹ��     : CSS_NV_COMM_BAND_CONFIG_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : ���õ�COMM BAND��Ϣʱ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandNum;
    VOS_UINT8                           aucRsv[3];
    CSS_BAND_PARA_STRU                  astBand[CSS_NV_MAX_COMM_BAND_NUM];
} CSS_NV_COMM_BAND_CONFIG_STRU;

/*****************************************************************************
 �ṹ��     : CSS_NV_RAT_RSSI_THRESHOLD_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : �����뼼����Ӧ�Ŀ�פ�������Լ�����������
*****************************************************************************/
typedef struct
{
    VOS_INT16                                   sGHighRssiThresHold;/* Gģ��Ӧ�ĸ���������ֵ */
    VOS_INT16                                   sGLowRssiThresHold;/* Gģ��Ӧ�Ŀ�פ����������ֵ */
    VOS_INT16                                   sWHighRssiThresHold;/* Wģ��Ӧ�ĸ���������ֵ */
    VOS_INT16                                   sWLowRssiThresHold;/* Wģ��Ӧ�Ŀ�פ����������ֵ */
    VOS_INT16                                   sLHighRssiThresHold;/* Lģ��Ӧ�ĸ���������ֵ */
    VOS_INT16                                   sLLowRssiThresHold;/* Lģ��Ӧ�Ŀ�פ����������ֵ */
} CSS_NV_RAT_RSSI_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��     : CSS_NV_CLOUD_STRATEGY_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : ��ͨ�ŵĲ����Ƿ�ʹ��
*****************************************************************************/
typedef struct
{

    VOS_UINT8                                     ucEnable;              /* ��ͨ�Ź����Ƿ�� */

    VOS_UINT8                                     ucCssPrefFreq;         /* ��ͨ�Ź��ܴ�ʱ��CSS��Ӫ��Ƶ���Ƿ���ƶ˻�ȡ */

    VOS_UINT8                                     ucLtePrefFreq;         /* ��ͨ�Ź��ܴ�ʱ��LTE��Ӫ��Ƶ���Ƿ���ƶ˻�ȡ */

    VOS_UINT8                                     ucWcdmaPrefFreq;       /* ��ͨ�Ź��ܴ�ʱ��WCDMA��Ӫ��Ƶ���Ƿ���ƶ˻�ȡ */

    VOS_UINT8                                     ucGsmPrefFreq;         /* ��ͨ�Ź��ܴ�ʱ��GSM��Ӫ��Ƶ���Ƿ���ƶ˻�ȡ */

    VOS_UINT8                                     ucLtePrefBand;         /* ��ͨ�Ź��ܴ�ʱ��LRRCԤ��band�Ƿ���ƶ˻�ȡ */

    VOS_UINT8                                     ucWcdmaPrefBand;       /* ��ͨ�Ź��ܴ�ʱ��WCDMAԤ��band�Ƿ���ƶ˻�ȡ */

    VOS_UINT8                                     ucGsmPrefBand;         /* ��ͨ�Ź��ܴ�ʱ��GSMԤ��band�Ƿ���ƶ˻�ȡ */

    VOS_UINT8                                     ucRsv1;
    VOS_UINT8                                     ucRsv2;
    VOS_UINT8                                     ucRsv3;
    VOS_UINT8                                     ucRsv4;
    VOS_UINT8                                     ucRsv5;
    VOS_UINT8                                     ucRsv6;
    VOS_UINT8                                     ucRsv7;
    VOS_UINT8                                     ucRsv8;
}CSS_NV_CLOUD_STRATEGY_STRU;


/*****************************************************************************
 �ṹ��     : CSS_NV_PREF_ARFCN_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : Ԥ��Ƶ��Ľṹ���������ɢ��Ƶ������ʱ��Ϊ�˽�ʡ�ռ䣬��ɶεĽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                    ulArfcnBegin;
    VOS_UINT32                                    ulArfcnEnd;
}CSS_NV_PREF_ARFCN_STRU;

/*****************************************************************************
 �ṹ��     : CSS_NV_PREF_MNC_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : Ԥ��MNC�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    bitMncDigit1: 4;/* MCC digit 1 */
    VOS_UINT16                                    bitMncDigit2: 4;/* MCC digit 2 */
    VOS_UINT16                                    bitMncDigit3: 4;/* MCC digit 3 */
    VOS_UINT16                                    bitRat      : 4;/* ��ʽ��0:GSM 1:WCDMA 2:LTE */

    VOS_UINT8                                     ucBandInd; /* BANDָʾ */
    VOS_UINT8                                     ucArfcnNum;/* Ԥ��Ƶ����� */
    CSS_NV_PREF_ARFCN_STRU                        astArfcn[CSS_NV_MAX_PREF_ARFCN_NUM];
}CSS_NV_PREF_MNC_STRU;


/*****************************************************************************
 �ṹ��     : CSS_NV_PREF_MCC_STRU
 Э����   :
 ASN.1����  :
 �ṹ˵��   : Ԥ��MCC�Ľṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                    bitMccDigit1: 4;/* MCC digit 1 */
    VOS_UINT16                                    bitMccDigit2: 4;/* MCC digit 2 */
    VOS_UINT16                                    bitMccDigit3: 4;/* MCC digit 3 */
    VOS_UINT16                                    bitSpare    : 4;
    VOS_UINT16                                    usMncNum;  /* MNC���� */
    CSS_NV_PREF_MNC_STRU                          astMnc[CSS_NV_MAX_PREF_MNC_NUM];
}CSS_NV_PREF_MCC_STRU;


/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/

/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of CssNvInterface.h */




