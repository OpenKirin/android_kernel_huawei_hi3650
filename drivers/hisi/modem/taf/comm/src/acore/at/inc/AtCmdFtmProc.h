

#ifndef __ATCMDFTMPROC_H__
#define __ATCMDFTMPROC_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtCtx.h"
#include "AtParse.h"

#include "AtMtaInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* LOG3.5�Ķ˿ڶ���: USB */
#define AT_LOG_PORT_USB                 (0)

/* LOG3.5�Ķ˿ڶ���: VCOM */
#define AT_LOG_PORT_VCOM                (1)

#define AT_JAM_DETECT_DEFAULT_METHOD                        (2)
#define AT_JAM_DETECT_DEFAULT_THRESHOLD                     (10)
#define AT_JAM_DETECT_DEFAULT_FREQ_NUM                      (30)

#define AT_NETMON_PLMN_STRING_MAX_LENGTH                    (10)
#define AT_NETMON_GSM_RX_QUALITY_INVALID_VALUE              (99)
#define AT_NETMON_GSM_RSSI_INVALID_VALUE                    (-500)
#define AT_NETMON_UTRAN_FDD_RSCP_INVALID_VALUE              (0)
#define AT_NETMON_UTRAN_FDD_RSSI_INVALID_VALUE              (0)
#define AT_NETMON_UTRAN_FDD_ECN0_INVALID_VALUE              (0)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


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

VOS_UINT32 At_SetLogPortPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_QryLogPortPara(VOS_UINT8 ucIndex);

VOS_UINT32 At_SetDpdtTestFlagPara(TAF_UINT8 ucIndex);
VOS_UINT32 At_SetDpdtPara(TAF_UINT8 ucIndex);
VOS_UINT32 At_SetQryDpdtPara(TAF_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaSetDpdtTestFlagCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvMtaSetDpdtValueCnf(VOS_VOID *pMsg);
VOS_UINT32 AT_RcvMtaQryDpdtValueCnf(VOS_VOID *pMsg);



VOS_UINT32 At_SetJamDetectPara(VOS_UINT8 ucIndex);
VOS_UINT32 At_QryJamDetectPara(VOS_UINT8 ucIndex);
VOS_UINT32 AT_RcvMtaSetJamDetectCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaJamDetectInd(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_SetRatFreqLock(VOS_UINT8 ucIndex);

VOS_UINT32 AT_QryRatFreqLock(VOS_UINT8 ucIndex);

VOS_UINT32 AT_RcvMtaSetRatFreqLockCnf(
    VOS_VOID                           *pMsg
);

VOS_UINT32 AT_RcvMtaSetGFreqLockCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_SetGFreqLock(VOS_UINT8 ucIndex);


VOS_UINT32 At_SetNetMonSCellPara(
    VOS_UINT8                           ucIndex
);
VOS_UINT32 At_SetNetMonNCellPara(
    VOS_UINT8                           ucIndex
);
VOS_UINT32 AT_RcvMtaSetNetMonSCellCnf(
    VOS_VOID                           *pMsg
);
VOS_UINT32 AT_RcvMtaSetNetMonNCellCnf(
    VOS_VOID                           *pMsg
);
VOS_VOID AT_NetMonFmtGsmSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
);
VOS_VOID AT_NetMonFmtUtranFddSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
);
VOS_VOID AT_NetMonFmtGsmNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
);
VOS_VOID AT_NetMonFmtUtranFddNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
);
VOS_VOID AT_NetMonFmtPlmnId(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc,
    VOS_CHAR                           *pstrPlmn,
    VOS_UINT16                         *pusLength
);

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
VOS_VOID AT_NetMonFmtUtranTddSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
);
VOS_VOID AT_NetMonFmtUtranTddNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16                          usInLen,
    VOS_UINT16                         *pusOutLen
);
#endif

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID AT_NetMonFmtEutranSCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstSCellInfo,
    VOS_UINT16                         *pusLength
);
VOS_VOID AT_NetMonFmtEutranNCellData(
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNCellInfo,
    VOS_UINT16 usInLen,VOS_UINT16      *pusOutLen
);
#endif

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

#endif /* end of AtCmdFtmProc.h */
