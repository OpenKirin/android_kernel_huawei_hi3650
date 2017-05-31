

#ifndef __ATCMDSUPSPROC_H__
#define __ATCMDSUPSPROC_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"
#include "TafSsaApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/
#define AT_PARA_NMEA_GPGSA              "$GPGSA"
#define AT_PARA_NMEA_GPGGA              "$GPGGA"
#define AT_PARA_NMEA_GPGSV              "$GPGSV"
#define AT_PARA_NMEA_GPRMC              "$GPRMC"
#define AT_PARA_NMEA_GPVTG              "$GPVTG"
#define AT_PARA_NMEA_GPGLL              "$GPGLL"
#define AT_PARA_NMEA_MAX_LEN            (41)
#define AT_PARA_NMEA_MIN_LEN            (6)

typedef VOS_VOID (*AT_SS_EVT_FUNC)(VOS_UINT8 ucIndex, VOS_VOID *pEvent);

/*****************************************************************************
  3 枚举定义
*****************************************************************************/


/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/
/*****************************************************************************
 结构名    : AT_SS_EVT_FUNC_TBL_STRU
 结构说明  : 补充业务事件处理函数表结构

  1.日    期   : 2015年10月19日
    作    者   : l00198894
    修改内容   : 新增结构体
*****************************************************************************/
/*lint -e958 -e959 64bit*/
typedef struct
{
    TAF_SSA_EVT_ID_ENUM_UINT32          enEvtId;
    AT_SS_EVT_FUNC                      pEvtFunc;
} AT_SS_EVT_FUNC_TBL_STRU;
/*lint +e958 +e959 64bit*/


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/
extern VOS_UINT32 AT_GetReturnCodeId(
        VOS_UINT32                          ulReturnCode,
        VOS_UINT32                         *pulIndex
    );

extern VOS_UINT32 AT_SetCmolrPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_RcvSsaSetLcsMolrCnf(
        VOS_UINT8                           ucIndex,
        VOS_VOID                           *pEvent
    );
extern VOS_UINT32 AT_QryCmolrPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_RcvSsaGetLcsMolrCnf(
        VOS_UINT8                           ucIndex,
        VOS_VOID                           *pEvent
    );
extern VOS_UINT32 AT_TestCmolrPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_RcvSsaLcsMolrNtf(
        VOS_UINT8                           ucIndex,
        VOS_VOID                           *pEvent
    );
extern VOS_UINT32 AT_SetCmolrePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_QryCmolrePara(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_SetCmtlrPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_RcvSsaSetLcsMtlrCnf(
        VOS_UINT8                           ucIndex,
        VOS_VOID                           *pEvent
    );
extern VOS_UINT32 AT_QryCmtlrPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_RcvSsaGetLcsMtlrCnf(
        VOS_UINT8                           ucIndex,
        VOS_VOID                           *pEvent
    );
extern VOS_VOID AT_RcvSsaLcsMtlrNtf(
        VOS_UINT8                           ucIndex,
        VOS_VOID                           *pEvent
    );
extern VOS_UINT32 AT_SetCmtlraPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_RcvSsaSetLcsMtlraCnf(
        VOS_UINT8                           ucIndex,
        VOS_VOID                           *pEvent
    );
extern VOS_UINT32 AT_QryCmtlraPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_RcvSsaGetLcsMtlraCnf(
        VOS_UINT8                           ucIndex,
        VOS_VOID                           *pEvent
    );
extern VOS_UINT32 AT_TestCmtlraPara(VOS_UINT8 ucIndex);
extern VOS_VOID AT_RcvTafSsaEvt(
        TAF_SSA_EVT_STRU                   *pstEvent
    );






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

#endif /* end of AtCmdSupsProc.h */

