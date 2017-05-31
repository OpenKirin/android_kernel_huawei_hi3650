

#ifndef __ATCMDSIMROC_H__
#define __ATCMDSIMPROC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"
#include "ATCmdProc.h"
#include "TafNvInterface.h"
#include "siapppih.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : AT_CARDAPP_ENUM
 ö��˵��  : ��Ӧ�����ȼ�
  1.��    ��   : 2015��06��13��
    ��    ��   : h00300778
    �޸�����   : V8R2 UICC MutliApp PhaseIV��������
*****************************************************************************/
enum AT_CARDAPP_ENUM
{
    AT_PREFER_APP_CDMA          = 0x00000000,
    AT_PREFER_APP_GUTL          = 0x00000001,
    AT_PREFER_APP_BUTT          = 0x00000002,
};
typedef TAF_UINT32 AT_CARDAPP_ENUM_UINT32;

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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 At_Base16Decode(VOS_CHAR *pcData, VOS_UINT32 ulDataLen, VOS_UINT8* pucDst);
extern VOS_UINT16 At_Hex2Base16(VOS_UINT32 MaxLength,VOS_CHAR *headaddr,VOS_CHAR *pucDst,VOS_UINT8 *pucSrc,VOS_UINT16 usSrcLen);

extern VOS_UINT32 At_SetHvsstPara(
    VOS_UINT8                           ucIndex
);
extern VOS_UINT32 At_QryHvsstPara(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT16 At_HvsstQueryCnf(
    VOS_UINT8                           ucIndex,
    SI_PIH_EVENT_INFO_STRU             *pstEvent);

extern VOS_UINT32 At_SetSciChgPara(
    VOS_UINT8                           ucIndex
);
extern VOS_UINT32 At_QrySciChgPara(
    VOS_UINT8                           ucIndex
);

extern VOS_UINT16 At_SciCfgQueryCnf(
    VOS_UINT8                           ucIndex,
    SI_PIH_EVENT_INFO_STRU             *pstEvent);

#if (FEATURE_ON == FEATURE_VSIM)
extern VOS_UINT32 At_SetHvsDHPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryHvsDHPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestHvsDHPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryHvsContPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_DealRSFWVsim(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_SetHvpDHPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_TestHvpDHPara(VOS_UINT8 ucIndex);
extern VOS_UINT16 At_HvsContQueryCnf(SI_PIH_EVENT_INFO_STRU *pstEvent);
extern VOS_UINT16 AT_HvsDHQueryCnf(SI_PIH_EVENT_INFO_STRU *pstEvent);
extern VOS_UINT32 At_SetHvteePara(
    VOS_UINT8                               ucIndex
);
extern VOS_UINT32 At_TestHvteePara(
    VOS_UINT8                           ucIndex
);
extern VOS_UINT32 At_QryHvCheckCardPara(
    VOS_UINT8                           ucIndex
);
#endif

extern VOS_UINT16 AT_UiccAuthCnf(TAF_UINT8 ucIndex,SI_PIH_EVENT_INFO_STRU *pstEvent);
extern VOS_UINT16 AT_UiccAccessFileCnf(TAF_UINT8 ucIndex,SI_PIH_EVENT_INFO_STRU *pstEvent);

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
extern VOS_UINT32 At_SetCrlaPara(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_QryCardSession(VOS_UINT8 ucIndex);
extern TAF_UINT32 At_SetPrfAppPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryPrfAppPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_TestPrfAppPara(TAF_UINT8 ucIndex);

extern TAF_UINT32 At_SetUiccPrfAppPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_QryUiccPrfAppPara(TAF_UINT8 ucIndex);
extern TAF_UINT32 At_TestUiccPrfAppPara(TAF_UINT8 ucIndex);

extern TAF_UINT32 At_SetCCimiPara(TAF_UINT8 ucIndex);

extern TAF_UINT16 At_CardErrorInfoInd(
    TAF_UINT8                           ucIndex,
    SI_PIH_EVENT_INFO_STRU             *pstEvent);

extern TAF_UINT16 At_CardIccidInfoInd(
    TAF_UINT8                           ucIndex,
    SI_PIH_EVENT_INFO_STRU             *pstEvent
);

#endif

TAF_UINT16 At_SimHotPlugStatusInd(
    TAF_UINT8                           ucIndex,
    SI_PIH_EVENT_INFO_STRU             *pstEvent
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

#endif /* end of AtCmdSimProc.h */
