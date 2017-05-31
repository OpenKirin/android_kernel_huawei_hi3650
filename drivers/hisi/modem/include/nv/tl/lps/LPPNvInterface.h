/******************************************************************************

    Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LPPNvInterface.h
  Description     : LPPNvInterface.h header file
  History           :

******************************************************************************/

#ifndef __LPPNVINTERFACE_H__
#define __LPPNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include  "vos.h"

#if (VOS_OS_VER != VOS_WIN32)
#include  "msp.h"
#endif
#pragma pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/

#define LNAS_GNSS_SUPPORT_LIST_NUM                      (2)
#define LNAS_GNSS_GEN_ASSIST_SUP_LIST_NUM               (3)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

/*****************************************************************************
 枚举名    : LPP_SBAS_ID_NV_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 动静态表类型
*****************************************************************************/

enum LNAS_SBAS_ID_NV_ENUM
{
    LNAS_SBAS_ID_WAAS     = 0,
    LNAS_SBAS_ID_EGNOS,
    LNAS_SBAS_ID_MSAS,
    LNAS_SBAS_ID_GAGAN,
    LNAS_SBAS_ID_BUTT
};
typedef VOS_UINT8 LNAS_SBAS_ID_NV_ENUM_UINT8;

/*****************************************************************************
 枚举名    : GNSS_METHOD_SUPPORTED_SIGNAL_GPS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 动静态表类型
*****************************************************************************/
typedef enum
{
    GNSS_METHOD_SIGNAL_GPS_L1           = 0,
    GNSS_METHOD_SIGNAL_GPS_L1C          = 1,
    GNSS_METHOD_SIGNAL_GPS_L2C          = 2,
    GNSS_METHOD_SIGNAL_GPS_L5           = 3,
    GNSS_METHOD_SIGNAL_GPS_BUTT,
} GNSS_METHOD_SUPPORTED_SIGNAL_GPS_ENUM;
/*****************************************************************************
 枚举名    : GNSS_METHOD_SUPPORTED_SIGNAL_SBAS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 动静态表类型
*****************************************************************************/
typedef enum
{
    GNSS_METHOD_SIGNAL_SBAS_L1          = 0,
    GNSS_METHOD_SIGNAL_SBAS_BUTT,
} GNSS_METHOD_SUPPORTED_SIGNAL_SBAS_ENUM;
/*****************************************************************************
 枚举名    : GNSS_METHOD_SUPPORTED_SIGNAL_QZSS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 动静态表类型
*****************************************************************************/
typedef enum
{
    GNSS_METHOD_SIGNAL_QZSS_L1          = 0,
    GNSS_METHOD_SIGNAL_QZSS_L1C         = 1,
    GNSS_METHOD_SIGNAL_QZSS_L2C         = 2,
    GNSS_METHOD_SIGNAL_QZSS_L5          = 3,
    GNSS_METHOD_SIGNAL_QZSS_BUTT,
} GNSS_METHOD_SUPPORTED_SIGNAL_QZSS_ENUM;
/*****************************************************************************
 枚举名    : GNSS_METHOD_SUPPORTED_SIGNAL_GLONASS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 动静态表类型
*****************************************************************************/
typedef enum
{
    GNSS_METHOD_SIGNAL_GLONASS_G1       = 0,
    GNSS_METHOD_SIGNAL_GLONASS_G2       = 1,
    GNSS_METHOD_SIGNAL_GLONASS_G3       = 2,
    GNSS_METHOD_SIGNAL_GLONASS_BUTT,
} GNSS_METHOD_SUPPORTED_SIGNAL_GLONASS_ENUM;
/*****************************************************************************
 枚举名    : GNSS_METHOD_SUPPORTED_SIGNAL_GALILEO_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 动静态表类型
*****************************************************************************/
typedef enum
{
    GNSS_METHOD_SIGNAL_GALILEO_E1       = 0,
    GNSS_METHOD_SIGNAL_GALILEO_E5A      = 1,
    GNSS_METHOD_SIGNAL_GALILEO_E5B      = 2,
    GNSS_METHOD_SIGNAL_GALILEO_E6       = 3,
    GNSS_METHOD_SIGNAL_GALILEO_E5AANDB  = 4,
    GNSS_METHOD_SIGNAL_GALILEO_BUTT,
} GNSS_METHOD_SUPPORTED_SIGNAL_GALILEO_ENUM;
/*****************************************************************************
 枚举名    : GNSS_METHOD_SUPPORTED_SIGNAL_BDS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 动静态表类型
*****************************************************************************/
typedef enum
{
    GNSS_METHOD_SIGNAL_BDS_B1I          = 0,
    GNSS_METHOD_SIGNAL_BDS_BUTT,
} GNSS_METHOD_SUPPORTED_SIGNAL_BDS_ENUM;

typedef VOS_UINT8   GNSS_METHOD_SUPPORTED_SIGNAL_ENUM_UINT8;
/*****************************************************************************
 枚举名    : GNSS_METHOD_SUPPORTED_SIGNAL_BDS_ENUM
 协议表格  :
 ASN.1描述 :
 枚举说明  : 动静态表类型
*****************************************************************************/
typedef enum
{
    LNAS_GNSS_METHOD_GPS                = 0,
    LNAS_GNSS_METHOD_SBAS               = 1,
    LNAS_GNSS_METHOD_QZSS               = 2,
    LNAS_GNSS_METHOD_GALILEO            = 3,
    LNAS_GNSS_METHOD_GLONASS            = 4,
    LNAS_GNSS_METHOD_BDS                = 5,
    LNAS_GNSS_METHOD_BUTT,
} GNSS_METHOD_SUPPORTED_ENUM;

typedef VOS_UINT8   GNSS_METHOD_SUPPORTED_ENUM_UINT8;



typedef struct
{
    VOS_UINT32                          bitOpGetGNSSCapByNV:1;          /* bit值为1，表示通过NV获取；为0表示通过MTA获取 */

    VOS_UINT32                          bitOpModemOrig:1;               /* bit值为1,表示允许modem发起位置信息请求，0表示不允许*/
    VOS_UINT32                          bitOpGpsSupFlag:1;               /* bit值为1，表示支持GPS测量，为0不支持GPS */
    VOS_UINT32                          bitOpPeriodProCtrlFlag:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;
}LNAS_LPP_NV_LONG_BIT_STRU0;

typedef struct
{
    VOS_UINT32                          bitOp1:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;
}LNAS_LPP_NV_LONG_BIT_STRU1;

typedef struct
{
    VOS_UINT32                          bitOp1:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;
}LNAS_LPP_NV_LONG_BIT_STRU2;

typedef struct
{
    VOS_UINT32                          bitOp1:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;
}LNAS_LPP_NV_LONG_BIT_STRU3;

typedef struct
{
    VOS_UINT32                          bitOp1:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;
}LNAS_LPP_NV_LONG_BIT_STRU4;

/*****************************************************************************
 结构名    : LNAS_ACCESS_TYPE_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP ACCESS TYPE 结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpAccessTypeExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucAccessTypesCnt;
    VOS_UINT8                           ucAccessTypes;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;


}LNAS_ACCESS_TYPE_NV_STRU;
/*****************************************************************************
 结构名    : LNAS_GNSS_ID_BITMAP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS ID bitmap 结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpGnssIDBitmapExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT16                          usGnssIdsCnt;
    VOS_UINT16                          usGNSSIDs;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;

}LNAS_GNSS_ID_BITMAP_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_REF_TIME_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS REFERENCE TIME SUPPORT
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpAssistSupListExt:1;
    VOS_UINT32                          bitOpFtaSup:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    LNAS_ACCESS_TYPE_NV_STRU            stFtaSupport;
    LNAS_GNSS_ID_BITMAP_NV_STRU         stGnssSystemTime;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
}LNAS_GNSS_REF_TIME_SUP_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_REF_LOC_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS REFERENCE location SUPPORT
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpGnssRefLocExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
}LNAS_GNSS_REF_LOC_SUP_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_IONO_MODEL_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS ionospheric model support
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpGnssIonoSupExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucIonoModel;
    VOS_UINT8                           ucIonoModelLen;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
}LNAS_GNSS_IONO_MODEL_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_EARTH_PARA_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS earth orientation parameters SUPPORT
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpGnssEarthParaSupExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
}LNAS_GNSS_EARTH_PARA_SUP_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_COM_ASSIST_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS COMMON ASSIST DATA SUPPORT NV结构体
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpComAssistSupListExt:1;
    VOS_UINT32                          bitOpRefTimeSup:1;
    VOS_UINT32                          bitOpRefLocSup:1;
    VOS_UINT32                          bitOpIonosphericModelSup:1;
    VOS_UINT32                          bitOpEarthOrientationParaSup:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    LNAS_GNSS_REF_TIME_SUP_NV_STRU      stRefTimeSup;
    LNAS_GNSS_REF_LOC_SUP_NV_STRU       stRefLocSup;
    LNAS_GNSS_IONO_MODEL_NV_STRU        stIonoModelSup;

    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;
    VOS_UINT8                           ucRsv9;
    VOS_UINT8                           ucRsv10;
    VOS_UINT8                           ucRsv11;
    VOS_UINT8                           ucRsv12;
    VOS_UINT8                           ucRsv13;
    VOS_UINT8                           ucRsv14;
    VOS_UINT8                           ucRsv15;
    VOS_UINT8                           ucRsv16;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT16                          usRsv5;
    VOS_UINT16                          usRsv6;
    VOS_UINT16                          usRsv7;
    VOS_UINT16                          usRsv8;
    VOS_UINT16                          usRsv9;
    VOS_UINT16                          usRsv10;
    VOS_UINT16                          usRsv11;
    VOS_UINT16                          usRsv12;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
    VOS_UINT32                          ulRsv3;
    VOS_UINT32                          ulRsv4;
    VOS_UINT32                          ulRsv5;
    VOS_UINT32                          ulRsv6;
    VOS_UINT32                          ulRsv7;
    VOS_UINT32                          ulRsv8;

}LNAS_GNSS_COM_ASSIST_SUP_NV_STRU;
/*****************************************************************************
 结构名    : LNAS_GNSS_GNSS_AND_SBAS_ID_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS ID AND SBAS ID 结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpGNSSIDExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    GNSS_METHOD_SUPPORTED_ENUM_UINT8    enGNSSID;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;

}LNAS_GNSS_ID_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_SBAS_ID_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS SBAS ID 结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpSBASIDExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    LNAS_SBAS_ID_NV_ENUM_UINT8          enSBASID;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;

}LNAS_GNSS_SBAS_ID_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_SIGNAL_IDS_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP SBAS ID 结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpSignalIDExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucSignalID;
    VOS_UINT8                           ucSignalIDCnt;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;


}LNAS_GNSS_SIGNAL_IDS_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_NAV_MODEL_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP navigation model support  结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpNavModelSupExt:1;
    VOS_UINT32                          bitOpClockModel:1;
    VOS_UINT32                          bitOpOrbitModel:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucClockModel;
    VOS_UINT8                           ucClockModelNum;
    VOS_UINT8                           ucOrbitModel;
    VOS_UINT8                           ucOrbitModelNum;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;

}LNAS_NAV_MODEL_SUP_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_ALMANAC_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP almanac support  结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpalmanacSupExt:1;
    VOS_UINT32                          bitOpAlmanac:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucAlmanacModel;
    VOS_UINT8                           ucAlmanacModelNum;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT32                          ulRsv1;

}LNAS_ALMANAC_SUP_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_REAL_TIME_INT_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP real time integrity support  结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpRealTimeIntSupExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;

}LNAS_REAL_TIME_INT_SUP_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_ACQ_ASSIST_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP data acquisition assistance support  结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpAcqAssistSupExt:1;
    VOS_UINT32                          bitOpConfidenceSupR10:1;
    VOS_UINT32                          bitOpDopplerUncertainExtSup:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucConfidenceSupR10;
    VOS_UINT8                           ucDopplerUncertainExtSupR10;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;

}LNAS_ACQ_ASSIST_SUP_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_GEN_SUP_ELEMENT_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS GENERIC ASSIST DATA SUPPORT ELEMENT NV结构体
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpAssistSupExt:1;
    VOS_UINT32                          bitOpSbasID:1;
    VOS_UINT32                          bitOpTimModelSup:1;
    VOS_UINT32                          bitOpDiffCorrectSup:1;
    VOS_UINT32                          bitOpNavModelSup:1;
    VOS_UINT32                          bitOpRealTimeSup:1;
    VOS_UINT32                          bitOpDataBitSup:1;
    VOS_UINT32                          bitOpAcqAssistSup:1;
    VOS_UINT32                          bitOpAlmanacSup:1;
    VOS_UINT32                          bitOpUtcModelSup:1;
    VOS_UINT32                          bitOpAuxInfoSup:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    LNAS_GNSS_ID_NV_STRU                stGnssID;
    LNAS_GNSS_SBAS_ID_NV_STRU           stGnssSbasID;
    LNAS_NAV_MODEL_SUP_NV_STRU          stNavModelSup;
    LNAS_ACQ_ASSIST_SUP_NV_STRU         stAcqAssistSup;
    LNAS_ALMANAC_SUP_NV_STRU            stAlamanacSup;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;
    VOS_UINT8                           ucRsv9;
    VOS_UINT8                           ucRsv10;
    VOS_UINT8                           ucRsv11;
    VOS_UINT8                           ucRsv12;
    VOS_UINT8                           ucRsv13;
    VOS_UINT8                           ucRsv14;
    VOS_UINT8                           ucRsv15;
    VOS_UINT8                           ucRsv16;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT16                          usRsv5;
    VOS_UINT16                          usRsv6;
    VOS_UINT16                          usRsv7;
    VOS_UINT16                          usRsv8;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
    VOS_UINT32                          ulRsv3;
    VOS_UINT32                          ulRsv4;
    VOS_UINT32                          ulRsv5;
    VOS_UINT32                          ulRsv6;
    VOS_UINT32                          ulRsv7;
    VOS_UINT32                          ulRsv8;
}LNAS_GNSS_GEN_SUP_ELEMENT_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_GEN_ASSIST_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS generic ASSIST DATA SUPPORT NV结构体
*****************************************************************************/

typedef struct
{

    VOS_UINT32                                  ulSupportElementNum;
    LNAS_GNSS_GEN_SUP_ELEMENT_NV_STRU           astGnssGenSupElementArray[LNAS_GNSS_GEN_ASSIST_SUP_LIST_NUM];

}LNAS_GNSS_GEN_ASSIST_SUP_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_ASSIST_SUP_LIST_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS assist data support NV结构体
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpAssistSupListExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    LNAS_GNSS_COM_ASSIST_SUP_NV_STRU    stGnssComAssistSup;
    LNAS_GNSS_GEN_ASSIST_SUP_NV_STRU    stGnssGenAssistSup;
}LNAS_GNSS_ASSIST_SUP_LIST_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_METHOD_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS Method 结构体
*****************************************************************************/

typedef struct
{
    VOS_UINT32                                               ulOpBitMsaSup      :1;
    VOS_UINT32                                               ulOpBitMsbSup      :1;
    VOS_UINT32                                               ulOpBitStdAlone    :1;
    VOS_UINT32                                               ulOpBitRsv1        :1;
    VOS_UINT32                                               ulOpBitRsv2        :1;
    VOS_UINT32                                               ulOpBitRsv3        :1;
    VOS_UINT32                                               ulOpBitRsv4        :1;
    VOS_UINT32                                               ulOpBitRsv5        :1;
    VOS_UINT32                                               ulOpBitRsv6        :1;
    VOS_UINT32                                               ulOpBitRsv7        :1;
    VOS_UINT32                                               ulOpBitRsv8        :1;
    VOS_UINT32                                               ulOpBitRsv9        :1;
    VOS_UINT32                                               ulOpBitRsv10       :1;
    VOS_UINT32                                               ulOpBitRsv11       :1;
    VOS_UINT32                                               ulOpBitRsv12       :1;
    VOS_UINT32                                               ulOpBitRsv13       :1;
    VOS_UINT32                                               ulOpBitRsv14       :1;
    VOS_UINT32                                               ulOpBitRsv15       :1;
    VOS_UINT32                                               ulOpBitRsv16       :1;
    VOS_UINT32                                               ulOpBitRsv17       :1;
    VOS_UINT32                                               ulOpBitRsv18       :1;
    VOS_UINT32                                               ulOpBitRsv19       :1;
    VOS_UINT32                                               ulOpBitRsv20       :1;
    VOS_UINT32                                               ulOpBitRsv21       :1;
    VOS_UINT32                                               ulOpBitRsv22       :1;
    VOS_UINT32                                               ulOpBitRsv23       :1;
    VOS_UINT32                                               ulOpBitRsv24       :1;
    VOS_UINT32                                               ulOpBitRsv25       :1;
    VOS_UINT32                                               ulOpBitRsv26       :1;
    VOS_UINT32                                               ulOpBitRsv27       :1;
    VOS_UINT32                                               ulOpBitRsv28       :1;
    VOS_UINT32                                               ulOpBitRsv29       :1;

    GNSS_METHOD_SUPPORTED_SIGNAL_ENUM_UINT8                  enSupportedSignal;
    VOS_UINT8                                                ucMsaFtaSup;
    VOS_UINT8                                                ucMsbFtaSup;
    VOS_UINT8                                                ucStdAloneFtaSup;
    VOS_BOOL                                                 bMsaVelocitySup;
    VOS_BOOL                                                 bMsbVelocitySup;
    VOS_BOOL                                                 bStdAloneVelocitySup;

}LNAS_GNSS_METHOD_SIGNAL_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_SIGNAL_ID_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS ID 结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpSignalIDExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucGnssSignalIDs;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;

}LNAS_GNSS_SIGNAL_ID_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_POSITIONING_MODE_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP POSITION MODE 结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpPositionModeExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_UINT8                           ucPosModeLen;
    VOS_UINT8                           ucPositioningModes;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
    VOS_UINT32                          ulRsv3;
    VOS_UINT32                          ulRsv4;


}LNAS_POSITIONING_MODE_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_FTA_MEAS_SUP_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP FTA MEAS SUP 结构
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpFtaMeasSupExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    LNAS_ACCESS_TYPE_NV_STRU            stAccessTypes;
    LNAS_POSITIONING_MODE_NV_STRU       stMode;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
    VOS_UINT32                          ulRsv3;
    VOS_UINT32                          ulRsv4;

}LNAS_GNSS_FTA_MEAS_SUP_NV_STRU;



/*****************************************************************************
 结构名    : LNAS_GNSS_SUPPORT_ELEMENT_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP SUPPORT ELEMENT
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpSupportElementExt:1;
    VOS_UINT32                          bitOpSbasID:1;
    VOS_UINT32                          bitOpFtaMeasSup:1;
    VOS_UINT32                          bitOpVelocityMeasSup:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    LNAS_GNSS_ID_NV_STRU                stGnssID;
    LNAS_POSITIONING_MODE_NV_STRU       stAgnssModes;
    LNAS_GNSS_SIGNAL_ID_NV_STRU         stGnssSignalIDs;
    LNAS_GNSS_FTA_MEAS_SUP_NV_STRU      stFtaMeasSup;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;
    VOS_UINT8                           ucRsv9;
    VOS_UINT8                           ucRsv10;
    VOS_UINT8                           ucRsv11;
    VOS_UINT8                           ucRsv12;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT16                          usRsv5;
    VOS_UINT16                          usRsv6;
    VOS_UINT16                          usRsv7;
    VOS_UINT16                          usRsv8;
    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
    VOS_UINT32                          ulRsv3;
    VOS_UINT32                          ulRsv4;
}LNAS_GNSS_SUPPORT_ELEMENT_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_METHOD_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS signal结构体
*****************************************************************************/

typedef struct
{
    VOS_UINT32                                  ulSupportElementNum;
    LNAS_GNSS_SUPPORT_ELEMENT_NV_STRU           astGnssSupportElementArray[LNAS_GNSS_SUPPORT_LIST_NUM];
}LNAS_GNSS_SUPPORT_LIST_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_LOC_COORDINATE_TYPE_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP location coordinate TYPE
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpLocCoordinateTypeExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_BOOL                            bEllipsoidPoint;
    VOS_BOOL                            bEllipsoidPointWithUncertaintyCircle;
    VOS_BOOL                            bEllipsoidPointWithUncertaintyEllipse;
    VOS_BOOL                            bPolygon;
    VOS_BOOL                            bEllipsoidPointWithAltitude;
    VOS_BOOL                            bEllipsoidPointWithAltitudeAndUncertaintyEllipsoid;
    VOS_BOOL                            bEllipsoidArc;
    VOS_BOOL                            bRsv1;
    VOS_BOOL                            bRsv2;
    VOS_BOOL                            bRsv3;
    VOS_BOOL                            bRsv4;
    VOS_BOOL                            bRsv5;
    VOS_BOOL                            bRsv6;
    VOS_BOOL                            bRsv7;
    VOS_BOOL                            bRsv8;

}LNAS_GNSS_LOC_COORDINATE_TYPE_NV_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_VELOCITY_TYPE_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS VELOCITY TYPE
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          bitOpVelocityTypeExt:1;
    VOS_UINT32                          bitOp2:1;
    VOS_UINT32                          bitOp3:1;
    VOS_UINT32                          bitOp4:1;
    VOS_UINT32                          bitOp5:1;
    VOS_UINT32                          bitOp6:1;
    VOS_UINT32                          bitOp7:1;
    VOS_UINT32                          bitOp8:1;
    VOS_UINT32                          bitOp9:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;

    VOS_BOOL                            bHorizontalVelocity;
    VOS_BOOL                            bHorizontalWithVerticalVelocity;
    VOS_BOOL                            bHorizontalVelocityWithUncertainty;
    VOS_BOOL                            bHorizontalWithVerticalVelocityAndUncertainty;
    VOS_BOOL                            bRsv1;
    VOS_BOOL                            bRsv2;
    VOS_BOOL                            bRsv3;
    VOS_BOOL                            bRsv4;
    VOS_BOOL                            bRsv5;
    VOS_BOOL                            bRsv6;
    VOS_BOOL                            bRsv7;
    VOS_BOOL                            bRsv8;

}LNAS_GNSS_VELOCITY_TYPE_STRU;

/*****************************************************************************
 结构名    : LNAS_GNSS_CAP_CFG_NV_STRU
 协议表格  :
 ASN.1描述 :
 结构说明  : LNAS LPP GNSS能力NV结构体
*****************************************************************************/

typedef struct
{
    VOS_UINT32                                  bitOpGNSSProvideCapExt  :1;
    VOS_UINT32                                  bitOpGNSSSupportList    :1;
    VOS_UINT32                                  bitOpAssistDataSupList  :1;
    VOS_UINT32                                  bitOpLocCoordinateTypes :1;
    VOS_UINT32                                  bitOpVelocityTypes      :1;
    VOS_UINT32                                  bitOp6:1;
    VOS_UINT32                                  bitOp7:1;
    VOS_UINT32                                  bitOp8:1;
    VOS_UINT32                                  bitOp9:1;
    VOS_UINT32                                  bitOp10:1;
    VOS_UINT32                                  bitOp11:1;
    VOS_UINT32                                  bitOp12:1;
    VOS_UINT32                                  bitOp13:1;
    VOS_UINT32                                  bitOp14:1;
    VOS_UINT32                                  bitOp15:1;
    VOS_UINT32                                  bitOp16:1;
    VOS_UINT32                                  bitOp17:1;
    VOS_UINT32                                  bitOp18:1;
    VOS_UINT32                                  bitOp19:1;
    VOS_UINT32                                  bitOp20:1;
    VOS_UINT32                                  bitOp21:1;
    VOS_UINT32                                  bitOp22:1;
    VOS_UINT32                                  bitOp23:1;
    VOS_UINT32                                  bitOp24:1;
    VOS_UINT32                                  bitOp25:1;
    VOS_UINT32                                  bitOp26:1;
    VOS_UINT32                                  bitOp27:1;
    VOS_UINT32                                  bitOp28:1;
    VOS_UINT32                                  bitOp29:1;
    VOS_UINT32                                  bitOp30:1;
    VOS_UINT32                                  bitOp31:1;
    VOS_UINT32                                  bitOp32:1;

    LNAS_LPP_NV_LONG_BIT_STRU1                  stBitRsv1;
    LNAS_LPP_NV_LONG_BIT_STRU2                  stBitRsv2;
    LNAS_LPP_NV_LONG_BIT_STRU3                  stBitRsv3;
    LNAS_LPP_NV_LONG_BIT_STRU4                  stBitRsv4;

    LNAS_GNSS_SUPPORT_LIST_NV_STRU              stGNSSSupList;
    LNAS_GNSS_ASSIST_SUP_LIST_NV_STRU           stGNSSAssistSupList;
    LNAS_GNSS_LOC_COORDINATE_TYPE_NV_STRU       stLocCoordinateType;
    LNAS_GNSS_VELOCITY_TYPE_STRU                stVelocityTypes;
    VOS_UINT8                                   ucRsv1;
    VOS_UINT8                                   ucRsv2;
    VOS_UINT8                                   ucRsv3;
    VOS_UINT8                                   ucRsv4;
    VOS_UINT8                                   ucRsv5;
    VOS_UINT8                                   ucRsv6;
    VOS_UINT8                                   ucRsv7;
    VOS_UINT8                                   ucRsv8;
    VOS_UINT8                                   ucRsv9;
    VOS_UINT8                                   ucRsv10;
    VOS_UINT8                                   ucRsv11;
    VOS_UINT8                                   ucRsv12;
    VOS_UINT8                                   ucRsv13;
    VOS_UINT8                                   ucRsv14;
    VOS_UINT8                                   ucRsv15;
    VOS_UINT8                                   ucRsv16;
    VOS_UINT8                                   ucRsv17;
    VOS_UINT8                                   ucRsv18;
    VOS_UINT8                                   ucRsv19;
    VOS_UINT8                                   ucRsv20;
    VOS_UINT8                                   ucRsv21;
    VOS_UINT8                                   ucRsv22;
    VOS_UINT8                                   ucRsv23;
    VOS_UINT8                                   ucRsv24;
    VOS_UINT8                                   ucRsv25;
    VOS_UINT8                                   ucRsv26;
    VOS_UINT8                                   ucRsv27;
    VOS_UINT8                                   ucRsv28;
    VOS_UINT8                                   ucRsv29;
    VOS_UINT8                                   ucRsv30;
    VOS_UINT8                                   ucRsv31;
    VOS_UINT8                                   ucRsv32;
    VOS_UINT8                                   ucRsv33;
    VOS_UINT8                                   ucRsv34;
    VOS_UINT8                                   ucRsv35;
    VOS_UINT8                                   ucRsv36;
    VOS_UINT8                                   ucRsv37;
    VOS_UINT8                                   ucRsv38;
    VOS_UINT8                                   ucRsv39;
    VOS_UINT8                                   ucRsv40;
    VOS_UINT8                                   ucRsv41;
    VOS_UINT8                                   ucRsv42;
    VOS_UINT8                                   ucRsv43;
    VOS_UINT8                                   ucRsv44;
    VOS_UINT8                                   ucRsv45;
    VOS_UINT8                                   ucRsv46;
    VOS_UINT8                                   ucRsv47;
    VOS_UINT8                                   ucRsv48;
    VOS_UINT8                                   ucRsv49;
    VOS_UINT8                                   ucRsv50;
    VOS_UINT8                                   ucRsv51;
    VOS_UINT8                                   ucRsv52;
    VOS_UINT8                                   ucRsv53;
    VOS_UINT8                                   ucRsv54;
    VOS_UINT8                                   ucRsv55;
    VOS_UINT8                                   ucRsv56;
    VOS_UINT8                                   ucRsv57;
    VOS_UINT8                                   ucRsv58;
    VOS_UINT8                                   ucRsv59;
    VOS_UINT8                                   ucRsv60;
    VOS_UINT8                                   ucRsv61;
    VOS_UINT8                                   ucRsv62;
    VOS_UINT8                                   ucRsv63;
    VOS_UINT8                                   ucRsv64;
    VOS_UINT8                                   ucRsv65;
    VOS_UINT8                                   ucRsv66;
    VOS_UINT8                                   ucRsv67;
    VOS_UINT8                                   ucRsv68;
    VOS_UINT8                                   ucRsv69;
    VOS_UINT8                                   ucRsv70;
    VOS_UINT8                                   ucRsv71;
    VOS_UINT8                                   ucRsv72;
    VOS_UINT8                                   ucRsv73;
    VOS_UINT8                                   ucRsv74;
    VOS_UINT8                                   ucRsv75;
    VOS_UINT8                                   ucRsv76;
    VOS_UINT8                                   ucRsv77;
    VOS_UINT8                                   ucRsv78;
    VOS_UINT8                                   ucRsv79;
    VOS_UINT8                                   ucRsv80;
    VOS_UINT8                                   ucRsv81;
    VOS_UINT8                                   ucRsv82;
    VOS_UINT8                                   ucRsv83;
    VOS_UINT8                                   ucRsv84;
    VOS_UINT8                                   ucRsv85;
    VOS_UINT8                                   ucRsv86;
    VOS_UINT8                                   ucRsv87;
    VOS_UINT8                                   ucRsv88;
    VOS_UINT8                                   ucRsv89;
    VOS_UINT8                                   ucRsv90;
    VOS_UINT8                                   ucRsv91;
    VOS_UINT8                                   ucRsv92;
    VOS_UINT8                                   ucRsv93;
    VOS_UINT8                                   ucRsv94;
    VOS_UINT8                                   ucRsv95;
    VOS_UINT8                                   ucRsv96;
    VOS_UINT8                                   ucRsv97;
    VOS_UINT8                                   ucRsv98;
    VOS_UINT8                                   ucRsv99;
    VOS_UINT8                                   ucRsv100;
    VOS_UINT16                                  usRsv1;
    VOS_UINT16                                  usRsv2;
    VOS_UINT16                                  usRsv3;
    VOS_UINT16                                  usRsv4;
    VOS_UINT16                                  usRsv5;
    VOS_UINT16                                  usRsv6;
    VOS_UINT16                                  usRsv7;
    VOS_UINT16                                  usRsv8;
    VOS_UINT16                                  usRsv9;
    VOS_UINT16                                  usRsv10;
    VOS_UINT16                                  usRsv11;
    VOS_UINT16                                  usRsv12;
    VOS_UINT16                                  usRsv13;
    VOS_UINT16                                  usRsv14;
    VOS_UINT16                                  usRsv15;
    VOS_UINT16                                  usRsv16;
    VOS_UINT16                                  usRsv17;
    VOS_UINT16                                  usRsv18;
    VOS_UINT16                                  usRsv19;
    VOS_UINT16                                  usRsv20;
    VOS_UINT16                                  usRsv21;
    VOS_UINT16                                  usRsv22;
    VOS_UINT16                                  usRsv23;
    VOS_UINT16                                  usRsv24;
    VOS_UINT16                                  usRsv25;
    VOS_UINT16                                  usRsv26;
    VOS_UINT16                                  usRsv27;
    VOS_UINT16                                  usRsv28;
    VOS_UINT16                                  usRsv29;
    VOS_UINT16                                  usRsv30;
    VOS_UINT16                                  usRsv31;
    VOS_UINT16                                  usRsv32;
    VOS_UINT16                                  usRsv33;
    VOS_UINT16                                  usRsv34;
    VOS_UINT16                                  usRsv35;
    VOS_UINT16                                  usRsv36;
    VOS_UINT16                                  usRsv37;
    VOS_UINT16                                  usRsv38;
    VOS_UINT16                                  usRsv39;
    VOS_UINT16                                  usRsv40;
    VOS_UINT32                                  ulRsv1;
    VOS_UINT32                                  ulRsv2;
    VOS_UINT32                                  ulRsv3;
    VOS_UINT32                                  ulRsv4;
    VOS_UINT32                                  ulRsv5;
    VOS_UINT32                                  ulRsv6;
    VOS_UINT32                                  ulRsv7;
    VOS_UINT32                                  ulRsv8;
    VOS_UINT32                                  ulRsv9;
    VOS_UINT32                                  ulRsv10;
    VOS_UINT32                                  ulRsv11;
    VOS_UINT32                                  ulRsv12;
    VOS_UINT32                                  ulRsv13;
    VOS_UINT32                                  ulRsv14;
    VOS_UINT32                                  ulRsv15;
    VOS_UINT32                                  ulRsv16;
    VOS_UINT32                                  ulRsv17;
    VOS_UINT32                                  ulRsv18;
    VOS_UINT32                                  ulRsv19;
    VOS_UINT32                                  ulRsv20;
}LNAS_GNSS_CAP_CFG_NV_STRU;

typedef struct
{
    LNAS_LPP_NV_LONG_BIT_STRU0          stLppNvLongBit;
    LNAS_GNSS_CAP_CFG_NV_STRU           stLppAgnssCapNV;
    VOS_UINT16                          usReTransTimerLen;  /*上行空口消息重传定时器时长，单位: ms*/
    VOS_UINT16                          usAttempeTransCnt;   /*上行消息尝试传输的总的次数*/
    VOS_UINT8                           ucLppLayerSwitch;
    VOS_UINT8                           ucLppLayerNorm;
    VOS_UINT8                           ucLppLayerInfo;
    VOS_UINT8                           ucLppLayerWarn;
    VOS_UINT8                           ucLppLayerErr;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;
    VOS_UINT8                           ucRsv9;
    VOS_UINT8                           ucRsv10;
    VOS_UINT8                           ucRsv11;
    VOS_UINT8                           ucRsv12;
    VOS_UINT8                           ucRsv13;
    VOS_UINT8                           ucRsv14;
    VOS_UINT8                           ucRsv15;
    VOS_UINT8                           ucRsv16;
    VOS_UINT8                           ucRsv17;
    VOS_UINT8                           ucRsv18;
    VOS_UINT8                           ucRsv19;
    VOS_UINT8                           ucRsv20;
    VOS_UINT8                           ucRsv21;
    VOS_UINT8                           ucRsv22;
    VOS_UINT8                           ucRsv23;
    VOS_UINT16                          usRsv0;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
    VOS_UINT16                          usRsv3;
    VOS_UINT16                          usRsv4;
    VOS_UINT16                          usRsv5;
    VOS_UINT16                          usRsv6;
    VOS_UINT16                          usRsv7;
    VOS_UINT16                          usRsv8;
    VOS_UINT16                          usRsv9;
    VOS_UINT16                          usRsv10;
    VOS_UINT16                          usRsv11;
    VOS_UINT16                          usRsv12;
    VOS_UINT16                          usRsv13;
    VOS_UINT16                          usRsv14;
    VOS_UINT16                          usRsv15;

    VOS_UINT32                          ulResponseTimeAllowance; /*response time 定时器余量，单位: ms*/

    VOS_UINT32                          ulRsv1;
    VOS_UINT32                          ulRsv2;
    VOS_UINT32                          ulRsv3;
    VOS_UINT32                          ulRsv4;
    VOS_UINT32                          ulRsv5;
    VOS_UINT32                          ulRsv6;
    VOS_UINT32                          ulRsv7;
    VOS_UINT32                          ulRsv8;
    VOS_UINT32                          ulRsv9;
    VOS_UINT32                          ulRsv10;
    VOS_UINT32                          ulRsv11;
    VOS_UINT32                          ulRsv12;
    VOS_UINT32                          ulRsv13;
}LNAS_LPP_NV_CONFIG_PARA_STRU;

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of PsNvInterface.h */

