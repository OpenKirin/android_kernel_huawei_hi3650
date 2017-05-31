/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CasNvInterface.h
  �� �� ��   : ����
  ��    ��   : w00287212
  ��������   : 2015��3��24��
  ����޸�   :
  ��������   : CasNvInterface.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��24��
    ��    ��   : w00287212
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CASNVINTERFACE_H__
#define __CASNVINTERFACE_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CAS_1X_MAX_RLP_BLOB_LEN                     (15)
#define CAS_1X_MAX_SCH_MO_NUM                       (4)                         /* MS֧�ֵ�SCH��������ʵ�MO���� */
#define CAS_1X_FCH_DCCH_MAX_MO                      (3)
#define CAS_1X_MAX_SUPPORT_SCH_NUM                  (1)
#define NV_ITEM_CAS_1X_TERMINAL_INFO_SIZE           (16)
#define NV_ITEM_CAS_1X_CAPA_INFO_SIZE               (28)
#define NV_ITEM_CAS_1X_RATE_FEATURE_CAPA_INFO_SIZE  (20)
#define NV_ITEM_CAS_1X_CHANNEL_CFG_CAPA_INFO_SIZE   (52)
#define NV_ITEM_CAS_1X_MO_CAPA_SIZE                 (32)
#define NV_ITEM_CAS_1X_RC_PREF_SIZE                 (4)
#define NV_ITEM_CAS_1X_ENCRYPT_CAPA_SIZE            (4)
#define NV_ITEM_CAS_1X_CELL_THRESHOLD_SIZE          (16)
#define NV_ITEM_CAS_1X_IMSI_TYPE_INFO_SIZE          (4)
#define NV_ITEM_CAS_1X_PROTOCOL_OPTIMIZE_SIZE       (8)
#define NV_ITEM_CAS_1X_TIMER_LEN_SIZE               (16)
#define NV_ITEM_CAS_1X_TCH_MEAS_FILTER_INFO_SIZE    (8)         /* ��ӦNV_Item_CAS_1X_NVIM_TCH_MEAS_FILTER */

#define NV_ITEM_CPORC_1X_FILTER_COEF_SIZE           (36)        /* ��ӦNV_ITEM_CPROC_1X_FILTER_COEF */
#define NV_ITEM_CPROC_1X_OPTIMIZE_SWITCH_SIZE       (24)
#define NV_Item_CPROC_1X_NVIM_SM_MPS_THRESHOLD_SIZE (32)
#define NV_ITEM_CPORC_1X_TAS_PARA_SIZE              (40)        /* ��ӦCPROC_1X_NVIM_TAS_CTRL_STRU */
#define NV_ITEM_CPROC_HRPD_OPTIMIZE_SWITCH_SIZE     (32)


#define NV_ITEM_CAS_HRPD_AT_REV_SIZE                    (4)
#define NV_ITEM_CDMA_SUPPORT_BANDCLASS_MASK_SIZE        (4)
#define NV_ITEM_CAS_HRPD_CELL_THRESHOLD_SIZE            (4)
#define NV_ITEM_CAS_HRPD_SUSPEND_TIMER_SIZE             (4)
#define NV_ITEM_CAS_HRPD_CONNCLOSE_TO_1X_SWITCH_SIZE    (4)
#define NV_ITEM_CAS_HRPD_C2L_PARA_SIZE                  (8)
#define NV_ITEM_CAS_HRPD_IDLE_HO_PARA_SIZE              (8)
#define NV_ITEM_CAS_HRPD_CFG_PARA_SIZE                  (8)
#define NV_ITEM_CAS_HRPD_TIMER_SIZE                     (16)
#define NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_VALUE_SIZE    (1950)  /* NV��ʵ���С */
#define NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_PART1_SIZE    (1972)  /* ��һ��NV�ṹ���ܴ�С */
#define NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_PART2_SIZE    (1964)  /* �ڶ���NV�ṹ���ܴ�С */
#define NV_ITEM_CAS_HRPD_SWITCH_PARA_SIZE               (8)
#define NV_ITEM_CAS_HRPD_STRENGTH_FILTER_RATIO_SIZE     (4)
#define NV_ITEM_CAS_HRPD_INTERFREQ_MEAS_THRESHOLD_SIZE  (4)
#define NV_ITEM_CAS_HRPD_EUTRA_CELL_RESEL_CTR_INFO_SIZE (8)
#define NV_ITEM_CPROC_RM_NVIM_1X_OCCUPY_INFO_SIZE       (4)
#define NV_ITEM_CPROC_HRPD_NVIM_PILOT_SEARCH_CTRL_SIZE  (8)


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

/** ****************************************************************************
 * Name        : CAS_1X_FCH_FRAME_SIZE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CAS_1X_FCH_FRAME_SIZE_ENUM
{
    CAS_1X_FCH_FRAME_SIZE_20MS        = 0x0000,
    CAS_1X_FCH_FRAME_SIZE_5MS_20MS    = 0x0001,
    CAS_1X_FCH_FRAME_SIZE_BUTT        = 0x0002
};
typedef VOS_UINT16 CAS_1X_FCH_FRAME_SIZE_ENUM_UINT16;

/** ****************************************************************************
 * Name        : CAS_1X_DCCH_FRAME_SIZE_ENUM_UINT16
 *
 * Description :
 *******************************************************************************/
enum CAS_1X_DCCH_FRAME_SIZE_ENUM
{
    CAS_1X_DCCH_FRAME_SIZE_20MS       = 0x0001,
    CAS_1X_DCCH_FRAME_SIZE_5MS        = 0x0002,
    CAS_1X_DCCH_FRAME_SIZE_5MS_20MS   = 0x0003,
    CAS_1X_DCCH_FRAME_SIZE_BUTT       = 0x0004
};
typedef VOS_UINT16 CAS_1X_DCCH_FRAME_SIZE_ENUM_UINT16;

/*****************************************************************************
 ö����    :CPROC_1X_NVIM_TAS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :0��ʾ��֧��TAS��1��ʾ֧��TAS
*****************************************************************************/
enum CPROC_1X_NVIM_TAS_ENUM
{
    CPROC_1X_NVIM_TAS_DISABLE                = 0,                                /* ��֧��TAS */                                                           /* ���н�����DPCH */
    CPROC_1X_NVIM_TAS_ENABLE                 = 1,                                /* ֧��TAS */                                                             /* ���д���RACH */
    CPROC_1X_NVIM_TAS_BUTT
};
typedef VOS_UINT16 CPROC_1X_NVIM_TAS_ENUM_UINT16;

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_RC_PREF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : RC PREF���� 3500
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucForRcPref;                            /* FOR_RC_PREF */
    VOS_UINT8                           ucRevRcPref;                            /* REV_RC_PREF */
    VOS_UINT8                           aucReserve[2];
}CAS_1X_NVIM_RC_PREF_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_MEID_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MEIDһ��56��bit
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMeidLow;                              /* Low 32 bit of MEID */
    VOS_UINT32                          ulMeidHigh;                             /* High 24 bit of MEID */
}CAS_1X_MEID_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_TERMINAL_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ֻ������Ϣ , not handle it now 3501
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserve[12];                         /* ESN �� MEID �ĽṹŲ�����ṹ */

    VOS_UINT8                           ucMobMfgCode;                           /* Manufacturer code */
    VOS_UINT8                           ucMobModel;                             /* Model number */
    VOS_UINT16                          usMobFirmRev;                           /* Firmware revision number */
} CAS_1X_NVIM_TERMINAL_INFO_STRU;                                        /* modify as CAS_1X_NVIM_TERMINAL_INFO_STRU */

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_CELL_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���������Ϣ�ṹ 3502
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sPilotSrchRssiThreshold;                /* PILOT����������ʹ�÷���ѡƵ���RSSI��������� */
    VOS_INT16                           sPrefChanPilotSrchRssiThreshold;        /* PILOT����������ʹ����ѡƵ���RSSI��������� */
    VOS_INT8                            cNbrSetStrengthOffset;                  /* ��ʽ�е������ؾ� */
    VOS_INT8                            cRemainSetStrengthOffset;               /* ��ʽ�е�ʣ�༯�ؾ� */
    VOS_INT16                           sDiffStrengthK;                         /* ��ʽ�е�����ϵ�� */
    VOS_INT8                            cDropThresh;                            /* ������Ƶ���� ��λ:db Ĭ��ֵΪ:-14db  */
    VOS_UINT8                           ucIdleHoMinThresh;                      /* idle̬�л��������, ʣ�༯С����������2�����˴�����Ϊ�������� ��λ:1/8dB Ĭ��ֵΪ:8 */
    VOS_UINT16                          ulTCandCellLen;                         /* �л��б�Ԫ�صĶ�ʱ��ʱ�� ��λ:ms Ĭ��ֵΪ1000 */
    VOS_UINT8                           ucWeakThreshold;                        /* �����źű����������ޣ���λ: �Σ�Ĭ��ֵΪ1�� */
    VOS_UINT8                           aucReserve[3];
} CAS_1X_NVIM_CELL_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_ENCRYPT_CAPA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ֻ�����������Ϣ 3503
*****************************************************************************/
typedef struct
{
    /* wanglingping:add ucEncryptAlgSupport to this struct */
    VOS_UINT8                           ucEncryptAlgSupport;                    /* Encryption algorithms supported */
    VOS_UINT8                           ucSigEncryptSpt;                        /* Signaling Encryption supported indicator */
    VOS_UINT8                           ucUiEncryptSpt;                         /* User information Encryption supported indicator */
    VOS_UINT8                           aucReserve[1];
} CAS_1X_NVIM_ENCRYPT_CAPA_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_FCH_CFG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FCH�ŵ�����
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enFchSupport;                           /* Fundamental Channel supported indicator */
    VOS_UINT8                           ucReserve;
    CAS_1X_FCH_FRAME_SIZE_ENUM_UINT16   enFchFrameSize;                         /* Fundamental Channel Frame Size capability indicator */
    VOS_UINT16                          usFwdFchRc;                             /* Fwd Rc,UE֧�ֵ���������RC,Ҳ��FCH�ŵ�֧�ֵ�����RC */
    VOS_UINT16                          usRevFchRc;                             /* Rev Rc UE֧�ֵ���������RC,Ҳ��FCH�ŵ�֧�ֵ�����RC */
} CAS_1X_FCH_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_DCCH_CFG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DCCH�ŵ�����
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                      enDcchSupport;                      /* Dedicated Control Channel supported indicator */
    VOS_UINT8                               ucReserve;
    CAS_1X_DCCH_FRAME_SIZE_ENUM_UINT16      enDcchFrameSize;                    /* Dedicated Control Channel Frame Size capability */
    VOS_UINT16                              usDcchFwdRc;                        /* DCCH֧�ֵ�����RC */
    VOS_UINT16                              usDcchRevRc;                        /* DCCH֧�ֵ�����RC */
} CAS_1X_DCCH_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_SCH_REC_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  SCH����������Ϣ
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enTurboSpt;                             /* Turbo Coding supported indicator */
    VOS_UINT8                           ucMaxTurboBlockSize;                    /* maximum Turbo Coding block size */
    PS_BOOL_ENUM_UINT8                  enConvSpt;                              /* Convolutional Coding supported indicator */
    VOS_UINT8                           ucMaxConvBlockSize;                     /* maximum Convolutional Coding block size */
    PS_BOOL_ENUM_UINT8                  enFrame40Spt;                           /* 40ms frame indicator */
    PS_BOOL_ENUM_UINT8                  enFrame80Spt;                           /* 80ms frame indicator */
    VOS_UINT8                           ucMaxRate;                              /* Maximum forward supplemental channels rate */
    VOS_UINT8                           ucReserve;
} CAS_1X_SCH_REC_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_SCH_CFG_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SCH�ŵ�����
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enForSchSupport;                                /* Forward Supplemental Channel supported indicator */
    VOS_UINT8                           ucReserve1;
    VOS_UINT16                          usForSchRcMap;                                  /* Forward Supplemental Channel Radio Configuration capability */
    VOS_UINT8                           ucForSchNum;                                    /* Number of Forward Supplemental Channels */
    VOS_UINT8                           aucReserve2[3];
    CAS_1X_SCH_REC_INFO_STRU            astForSchRecInfo[CAS_1X_MAX_SUPPORT_SCH_NUM];   /* ����SCH REC INFO */

    PS_BOOL_ENUM_UINT8                  enRevSchSupport;                                /* Reverse Supplemental Channel supported indicator */
    VOS_UINT8                           ucReserve3;
    VOS_UINT16                          usRevSchRcMap;                                  /* Reverse Supplemental Channel Radio Configuration capability */
    VOS_UINT8                           ucRevSchNum;                                    /* Number of Reverse Supplemental Channels */
    VOS_UINT8                           aucReserve4[3];
    CAS_1X_SCH_REC_INFO_STRU            astRevSchRecInfo[CAS_1X_MAX_SUPPORT_SCH_NUM];   /* ����SCH REC INFO */
} CAS_1X_SCH_CFG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_CHANNEL_CFG_CAPA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  �ŵ�֧�ֵ����� add a nv id 3504
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enOtdSupport;                           /* OTD supported indcator */
    PS_BOOL_ENUM_UINT8                  enStsSupport;                           /* STS supported indicator */
    PS_BOOL_ENUM_UINT8                  en3XCchSupport;                         /* 3X Common Channel supported */
    VOS_UINT8                           ucReserve;
    CAS_1X_FCH_CFG_INFO_STRU            stFchCfgInfo;                           /* fch ������Ϣ */
    CAS_1X_DCCH_CFG_INFO_STRU           stDcchCfgInfo;                          /* dcch ������Ϣ */
    CAS_1X_SCH_CFG_INFO_STRU            stSchCfgInfo;                           /* sch ������Ϣ */
} CAS_1X_NVIM_CHANNEL_CFG_CAPA_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_FLEX_SPT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  flex֧������
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enFlexSupport;                          /* Flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFFchFlexSpt;                          /* Forward Fundamental channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enRFchFlexSpt;                          /* Reverse Fundamental channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFDcchFlexSpt;                         /* Forward Dedicated Control channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enRDcchFlexSpt;                         /* Reverse Dedicated Control channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFSchFlexSpt;                          /* Forward Supplemental channel flexible rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enRSchFlexSpt;                          /* Reverse Supplemental channel flexible rate feature supported indicator */
    VOS_UINT8                           ucReserve;
} CAS_1X_FLEX_SPT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_VAR_SPT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : variable rate feature֧������
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enVarSupport;                           /* Variable rate feature supported indicator */
    PS_BOOL_ENUM_UINT8                  enFSchVarSpt;                           /* Forward Supplemental Channel Variable Rate supported indicator */
    PS_BOOL_ENUM_UINT8                  enRSchVarSpt;                           /* Reverse Supplemental Channel Variable Rate supported indicator */
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usMaxSumNumBitsC;                       /* Maximum sum of number of bits corresponding to Convolutional rates in the variable rate set */
    VOS_UINT16                          usMaxSumNumBitsT;                       /* Maximum sum of number of bits corresponding to Turbo Code rates in the variable rate set */
} CAS_1X_VAR_SPT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_CAPA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  capability infomation 3505
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMobPRev;                              /* MOB_P_REV: UE֧�ֵ�Э��汾 */
    PS_BOOL_ENUM_UINT8                  enPacketDataServSupp;                   /* MS supports packet data service */
    PS_BOOL_ENUM_UINT8                  enDeviceInfoMsgSupp;                    /* MS supports the  Device Information Message on the r-csch */
    VOS_UINT8                           ucReserve;
    PS_BOOL_ENUM_UINT8                  enSyncIdReportCapa;                     /* ��ʶMS�Ƿ�֧���ϱ�SYNC ID */

    PS_BOOL_ENUM_UINT8                  enAccessEntryHo;                        /* Access Entry Handoff Support */
    PS_BOOL_ENUM_UINT8                  enAccessProbeHo;                        /* Access Probe Handoff Support */
    PS_BOOL_ENUM_UINT8                  enAnalogSearch;                         /* Analog Search Support */
    PS_BOOL_ENUM_UINT8                  enHoppingBeacon;                        /* Hopping Beacon Support */
    PS_BOOL_ENUM_UINT8                  enMahHo;                                /* Mobile Assisted Hard Handoff Support */
    PS_BOOL_ENUM_UINT8                  enPuf;                                  /* Location Power Up Function Support */
    PS_BOOL_ENUM_UINT8                  enAnalog553A;                           /* Analog Support */
    PS_BOOL_ENUM_UINT8                  enQpchSupport;                          /* QPCH�Ƿ�֧�ֵı�� */
    PS_BOOL_ENUM_UINT8                  enBroadCastSupport;                     /* BC�Ƿ�֧�ֵı�� */

    PS_BOOL_ENUM_UINT8                  enSlottedClass;                         /* Slotted Class, scm��5λ */
    PS_BOOL_ENUM_UINT8                  enSlottedTimer;                         /* Slotted Timer Support */
    PS_BOOL_ENUM_UINT8                  enChsSupport;                           /* Control Hold Mode supported indicator */
    VOS_UINT8                           ucGatingRateSet;                        /* Set of supported Reverse Pilot gating rates */
    PS_BOOL_ENUM_UINT8                  enExtCapIncluded;                       /* Extended Capabilities Included indicator */
    PS_BOOL_ENUM_UINT8                  enMabo;                                 /* Mobile Assisted Burst Operation capability indicator */
    PS_BOOL_ENUM_UINT8                  enSdb;                                  /* Short Data Burst supported indicator */

    VOS_UINT8                           ucCdmaSptOpMode;                        /* UE֧�ֵĲ���ģʽ */
    VOS_UINT8                           ucMinPwrCntlStep;                       /* Minimum power control step size */
    PS_BOOL_ENUM_UINT8                  enRevFchGating;                         /* REV_FCH_GATING_REQ */
    VOS_UINT8                           ucGeoLoc;                               /* Geo-location */

    PS_BOOL_ENUM_UINT8                  enTransMode;                            /* Transmission, scm��2λ  */
    PS_BOOL_ENUM_UINT8                  enSupportMeid;                          /* Meid support, scm��4λ */
    PS_BOOL_ENUM_UINT8                  enDualmode;                             /* Dual mode, scm��6λ */
} CAS_1X_NVIM_CAPA_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_RATE_FEATURE_CAPA_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  rate feature capability infomation 3506
*****************************************************************************/
typedef struct
{
    CAS_1X_FLEX_SPT_INFO_STRU           stFlexSptInfo;                          /* flex info ֧������ */
    CAS_1X_VAR_SPT_INFO_STRU            stVarSptInfo;                           /* VAR֧������ */
    PS_BOOL_ENUM_UINT8                  enCsSupport;                            /* Concurrent Services supported indicator */
    PS_BOOL_ENUM_UINT8                  enFSchLtuTabSpt;                        /* Forward Supplemental Channel Downloadable LTU tables supported indicator */
    PS_BOOL_ENUM_UINT8                  enRSchLtuTabSpt;                        /* Reverse Supplemental Channel Downloadable LTU tables supported indicator */
    VOS_UINT8                           aucReserve2[1];
} CAS_1X_NVIM_RATE_FEATURE_CAPA_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_SCH_MO_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  SCH֧�ֵ�MO
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausMoForSch[CAS_1X_MAX_SCH_MO_NUM];
    VOS_UINT16                          ausMoRevSch[CAS_1X_MAX_SCH_MO_NUM];
} CAS_1X_SCH_MO_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_FCH_DCCH_MO_LIST_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : FCH DCCH MO����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMoNum;
    VOS_UINT16                          ausMoList[CAS_1X_FCH_DCCH_MAX_MO];
} CAS_1X_FCH_DCCH_MO_LIST_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_MO_CAPA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MO���� 3507
*****************************************************************************/
typedef struct
{
    CAS_1X_FCH_DCCH_MO_LIST_STRU        stFwdMo;                                /* Fwd Mo,FCH��DCCH֧�ֵ�����MO */
    CAS_1X_FCH_DCCH_MO_LIST_STRU        stRevMo;                                /* Rev Mo,FCH��DCCH֧�ֵ�����MO */
    CAS_1X_SCH_MO_INFO_STRU             stSchMoInfo;                            /* sch��֧�ֵ�MO */
}CAS_1X_NVIM_MO_CAPA_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_IMSI_TYPE_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Imsi_T programmed��־ 3508
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enProgrammedImsiT;                      /* IMSI_T programmed or not*/
    VOS_UINT8                           aucReserve[3];
}CAS_1X_NVIM_IMSI_TYPE_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_PROTOCOL_OPTIMIZE_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Э���Ż�ѡ�� 3509
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSaveSystemInfo;                       /* �Ƿ񻺴�ϵͳ��Ϣ��Ĭ��ֵΪTRUE, Ĭ�ϻ��� */
    VOS_UINT8                           ucTaddDelta;                            /* Tadd����ϵ�� ��λ:0.5db Ĭ��ֵΪ0 */
    VOS_UINT8                           ucTdropDelta;                           /* Tdrop����ϵ�� ��λ:0.5db Ĭ��ֵΪ0 */
    VOS_UINT8                           ucTSysReselLen;                         /* ϵͳ��ѡ��ʱ��ʱ��ʱ�� ��λ: s Ĭ��ֵΪ16, 0��ʾ��ʹ����ʱ��ʱ�� */
    VOS_UINT16                          usRschApplyTime;                        /* ��ǰ����RSCHʱ�䣬Ĭ��Ϊ400ms */
    VOS_UINT16                          usTOhmMsgRcvLen;                        /* ��ǰ����С��ϵͳ��Ϣ���յĶ�ʱ��ʱ�� ��λ:s Ĭ��ֵΪ600 */
}CAS_1X_NVIM_PROTOCOL_OPTIMIZE_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_TIMER_LENGTH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CASά����NV����Ķ�ʱ��ʱ��,SRLTE���Կ�������, 3514
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWaitCprocRfIndTimerLen;               /* SRLTE:ʱ϶ģʽ���յ�NO_RF_IND,��CPROC��RF_IND�Ķ�ʱ��ʱ�� */
    VOS_UINT8                           ucWaitSrlteSysSyncTimerAddLen;          /* SRLTE:���������ж�ʱ���ӳ��ĳ��� */
    VOS_UINT8                           aucReserve[14];
}CAS_1X_NVIM_TIMER_LENGTH_STRU;

/*****************************************************************************
 �ṹ��    : CAS_1X_NVIM_TCH_MEAS_FILTER_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DTS2016030805560, TCH̬�˲�NV, 3515
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enTchMeasFilterSw;                      /* TCH̬�˲����� */

    VOS_UINT8                           ucMfOldFactor;                          /* TCH������ֵ���˲����� */
    VOS_UINT8                           ucMfNewFactor;                          /* TCH������ֵ���˲����� */

    VOS_UINT8                           ucMfLowThod;                            /* TCH�˲�������, ��λ 1db, ���ϲ���ֵ֮��С�ڵ��ڴ�����ʱ�˲� */
    VOS_UINT8                           ucMfHighThod;                           /* TCH�˲�������, ��λ 1db, ���ϲ���ֵ֮����ڴ�����ʱ�˲� */

    VOS_INT8                            sCandSetMeasReportThod;                 /* ��ѡ�����ϱ�PSMM������, ��λ 1db, ��ѡ���в���ֵ���ڴ�����ֵʱ�ϱ�PSMM */

    VOS_UINT8                           ucNghbrExtraExccedTime;                 /* TCH����������������Ҫ�������޴������Ŵ����ϱ� */
    VOS_UINT8                           ucCandExtraExccedTime;                  /* TCH��ѡ������������Ҫ�������޴������Ŵ����ϱ� */

} CAS_1X_NVIM_TCH_MEAS_FILTER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_1X_NVIM_FILTER_COEF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPROC �˲�ϵ��,CAS ά��
*****************************************************************************/
typedef struct
{
    /* SF continuous */
    VOS_UINT16                          usSfContMpsAlphaEc;
    VOS_UINT16                          usSfContMpsAlphaEcIo;

    VOS_UINT16                          usSfContMeasAlphaEc;
    VOS_UINT16                          usSfContMeasAlphaEcIo;

    /* CF TCH */
    VOS_UINT16                          usCfContTchAlphaEc;
    VOS_UINT16                          usCfContTchAlphaEcIo;

    /* SF DRX */
    VOS_UINT16                          usSfDrxMpsOsAlphaEc;
    VOS_UINT16                          usSfDrxMpsOsAlphaEcIo;

    VOS_UINT16                          usSfDrxMpsContAlphaEc;
    VOS_UINT16                          usSfDrxMpsContAlphaEcIo;

    VOS_UINT16                          usSfDrxMeasAlphaEc;
    VOS_UINT16                          usSfDrxMeasAlphaEcIo;

    /* CF DRX */
    VOS_UINT16                          usCfDrxMeasAlphaEc;
    VOS_UINT16                          usCfDrxMeasAlphaEcIo;

    /* ilde continuous(reserve) */
    VOS_UINT16                          usSfContIdleMpsAlphaEc;
    VOS_UINT16                          usSfContIdleMpsAlphaEcIo;

    VOS_UINT16                          usSfContIdleMeasAlphaEc;
    VOS_UINT16                          usSfContIdleMeasAlphaEcIo;

}CPROC_1X_NVIM_FILTER_COEF_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_1X_NVIM_PILOT_SEARCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Pilot search ����
*****************************************************************************/
typedef struct
{
    VOS_INT16                           shwVaildPilotThres;                     /* �����׶��жϵ�Ƶ�Ƿ���Ч�����ޡ����ݵ�ƵMPS������ECNO�����жϣ������ƵECNO���ڴ����ޣ�
                                                                                   ��Ϊ�õ�Ƶ��Ч���ڸõ�Ƶ�½�SYNC��������ڴ����ޣ�����2��MPS��ƽ��ֵ�жϵ�Ƶ�Ƿ���Ч */
    VOS_INT16                           shwVaildPilotAverageThres;              /* �����׶ε�Ƶƽ��ECNO���ж����ޡ������Ƶ�ĵ���MPS ECNO��������Ч���ޣ��Ե�Ƶ����MPS ���֣�
                                                                                   �����Ƶ��ƽ��ECNO ���ڴ����ޣ���Ϊ��Ƶ��Ч��������Ϊ�˵�Ƶ��Ч                     */
    VOS_UINT16                          uhwMaxPNNumDoMps;                       /* �����׶�MPS��������λ������MPS��������λ����ȡ��ֵ��PILOT SEARCH IND�ϱ���PNPhase Num �еĽ�Сֵ */
    VOS_UINT16                          uhwMaxMpsLoopsTime;                     /* �����׶�MPS���������������������λ����MPS����ECNO��������Ч���ޣ����������λ������ֵ��������� */
    VOS_UINT16                          uhwMaxPSTimeIfNoPnPhaseNum;             /* ��Ƶ��PILOT SEARCH ��������*/
    VOS_UINT16                          usReserve1;
}CPROC_1X_NVIM_PILOT_SEARCH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_1X_NVIM_OPTIMIZE_SWITCH_STRU
 Э����  : C.S0005 Table D-2.
 ASN.1���� :
 �ṹ˵��  : CPROC 1X �Ż�����, 3511
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucN2mHuaweiConfigValue;                /*N2m�Զ�������ֵ*/
    VOS_UINT8                               ucN3mHuaweiConfigValue;                /*N3m�Զ�������ֵ*/
    CPROC_1X_NVIM_PILOT_SEARCH_PARA_STRU    stPsPara;
    VOS_UINT8                               enTimeInterruptResetFlag;              /*Wake up time is inconsistent with BBP.
                                                                                     1 Reset.
                                                                                     0 send error ind to cas. Expected release all from Cas*/
    VOS_UINT8                               aucReserved[9];
}CPROC_1X_NVIM_OPTIMIZE_SWITCH_STRU;
/*****************************************************************************
 �ṹ��    : CPROC_1X_MPS_REF_PN_THRESHOLD_STRU��
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Threshold for refrence PN change.
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sRemoveOldRefPNThreshold;   /* Threshold for changing to a new reference */
    VOS_UINT16                          usNewRefPNThreshold;        /* Threshold above reference EcNo before changing reference */
    VOS_UINT16                          usNewRefPNCount;            /* Number of times above threshold berfore changing reference */
    VOS_UINT16                          usReserved;
}CPROC_1X_MPS_REF_PN_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : CPROC_1X_CF_MEAS_THRESHOLD_STRU��
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Threshold for CF measurement.
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sCfMeasSignalLevelThreshold;        /* Threshold for idle cf start measurement */
    VOS_INT16                           sCfMeasEmergencyModeThreshold;      /* Threshold for idle cf emergency search mode */
}CPROC_1X_CF_MEAS_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : CPROC_1X_NVIM_SM_MPS_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Threshold for mps.
*****************************************************************************/
typedef struct
{
    CPROC_1X_MPS_REF_PN_THRESHOLD_STRU  stCproc1xMpsRefPNThreshold; /* Threshold for refrence PN change. */
    CPROC_1X_CF_MEAS_THRESHOLD_STRU     stCproc1xCfMeasThreshold;   /* Threshold for idle cf measurement */
    VOS_UINT16                          usReserved[10];
}CPROC_1X_NVIM_SM_MPS_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_1X_NVIM_DM_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : Threshold for DM.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDiversitySwitch;
    VOS_UINT8                           ucIdleCrcInitCounter;
    VOS_UINT16                          usSimCardTemperature;
    VOS_INT16                           shwIdleMeasRscpOn;
    VOS_INT16                           shwIdleMeasRscpOff;
    VOS_INT16                           shwIdleMeasEcN0On;
    VOS_INT16                           shwIdleMeasEcN0Off;
    VOS_UINT8                           ucTchFerOnCounter;
    VOS_UINT8                           ucTchFerOffCounter;
    VOS_UINT8                           ucTchFerOnWinSize;
    VOS_UINT8                           ucTchFerOffWinSize;
}CPROC_1X_NVIM_DM_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_1X_NVIM_TAS_SEARCHING_STATE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 1X TAS���������������������ֵ
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGoodRssiThres;                   /* ���ں��ź�RSSI����ֵ(��λΪ0.125dbm) */
    VOS_UINT16                              usReserve1;
}CPROC_1X_NVIM_TAS_SEARCHING_STATE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_1X_NVIM_TAS_PHY_STATE_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 1X TAS�����״̬�ϱ���������ֵ��
             ����Xģר�ã��������Ǹ��ã����û���nv����Խ��Խ��
*****************************************************************************/
typedef struct
{
    VOS_INT16                               shwGoodRscpThres;                   /* ���ں��ź�RSCP����ֵ(��λΪ0.125dbm)������GU */
    VOS_INT16                               shwPoorRscpThres;                   /* ���ڲ��ź�RSCP����ֵ(��λΪ0.125dbm)������GU */
    VOS_INT16                               shwGoodEcIoThres;                   /* ���ں��ź�EcIo����ֵ(��λΪ0.125db)��Xģר�� */
    VOS_INT16                               shwPoorEcIoThres;                   /* ���ڲ��ź�EcIo����ֵ(��λΪ0.125db)��Xģר�ã��������Ǹ��ã����û���nv����Խ��Խ�� */
    VOS_UINT16                              uhwSFailNum;                        /* S׼������ʧ�ܴ���������GU */
    VOS_UINT16                              uhwSPassNum;                        /* S׼�������ɹ�����������GU */
}CPROC_1X_NVIM_TAS_PHY_STATE_PARA_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_1X_NVIM_TAS_BLIND_MEAS_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TASä�в����Ŀ��Ʋ�����
             ����Xģר�ã��������Ǹ��ã����û���nv����Խ��Խ��
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              uhwStateOneTime;                    /* �׶�һ�Ƚ�ʱ�� */
    VOS_INT16                               shwWorstRscpValue;                  /* ���RSCP�ź�����ֵ */
    VOS_INT16                               shwWorseRscpValue;                  /* �ϲ�RSCP�ź�����ֵ */
    VOS_UINT16                              uhwDeltaRscpValue;                  /* ���յ����ź�ǿ���½��о����� */
    VOS_UINT16                              uhwStateTwoTime;                    /* �׶ζ��Ƚ�ʱ�� */
    VOS_UINT16                              uhwDeltaRscpValuetest;              /* �����ֶ� */
    VOS_UINT16                              auhwFrozenTime[4];                  /* �����л����ᱣ��ʱ��, Ta Tb Tc Td */
}CPROC_1X_NVIM_TAS_BLIND_MEAS_STRU;



/*****************************************************************************
 �ṹ��    : CPROC_1X_NVIM_TAS_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 1x TAS�㷨���Ʋ���
*****************************************************************************/
typedef struct
{
    CPROC_1X_NVIM_TAS_ENUM_UINT16               enCproc1xTasSupprot;                /* �Ƿ�֧��TAS��BBIT֮����GU���� */
    VOS_UINT16                                  uwReserve;
    CPROC_1X_NVIM_TAS_SEARCHING_STATE_PARA_STRU stTasSearchingStatePara;            /* TAS������صĿ��Ʋ��� */
    CPROC_1X_NVIM_TAS_PHY_STATE_PARA_STRU       stTasPhyStatePara;                  /* �����״̬�ϱ��������� */
    CPROC_1X_NVIM_TAS_BLIND_MEAS_STRU           stTasBlindCtrl;                     /* TASä�в����Ŀ��Ʋ��� */
}CPROC_1X_NVIM_TAS_CTRL_STRU;


/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_REV_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : EVDO�ն˰汾��Ϣ 3600
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enSuppOnlyDo0;                          /* �Ƿ�ֻ֧��DO0�汾 */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithMfpa;                      /* �Ƿ�֧��DOA�汾��Ӧ������ֻ֧��MFPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaWithEmfpa;                     /* �Ƿ�֧��DOA�汾��Ӧ������֧��MFPA��EMPA */
    PS_BOOL_ENUM_UINT8                  enSuppDoaEhrpd;                         /* �Ƿ�֧��eHRPD */
}CAS_HRPD_NVIM_REV_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_CDMA_NVIM_SUPPORT_BANDCLASS_MASK_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �ն�֧�ֵ�Ƶ����������  3601
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSupportBandclassMask;               /* �ն�֧�ֵ�Ƶ���������룬ÿbit��ʾ�Ƿ�֧�ֶ�Ӧ��Ƶ������������0x00000001��ʾֻ֧��Ƶ��0 */
}CAS_CDMA_NVIM_SUPPORT_BANDCLASS_MASK_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_CELL_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : �������������Ϣ�ṹ  3602
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sPilotSrchRssiThreshold;                /* PILOT����������ʹ�÷���ѡƵ���RSSI��������� */
    VOS_INT16                           sPrefChanPilotSrchRssiThreshold;        /* PILOT����������ʹ����ѡƵ���RSSI��������� */
}CAS_HRPD_NVIM_CELL_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_SUSPEND_TIMER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʱ��ʱ�� 3603
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usConnSuspendTimerLength;             /* AT�������ģʽʱ������ʱ����ʱ������λΪms */
    VOS_UINT8                           aucReserve[2];
}CAS_HRPD_NVIM_SUSPEND_TIMER_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_CONNCLOSE_TO_1X_SWITCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DO��1x�л�����    3604
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enDO21XSwitch;                        /* ��HRPD����̬����ֵ����sStrengthThresholdTo1xʱ���Ƿ�Ͽ�HRPD���� */
    VOS_UINT8                           ucReserve;
    VOS_INT16                           sStrengthThresholdTo1x;               /* ����̬ʱ�������ֵ������ޣ����ڸ����ޣ�EVDO�����������ӹرգ��л���1x */
}CAS_HRPD_NVIM_CONNCLOSE_TO_1X_SWITCH_STRU;



/*****************************************************************************
 �ṹ��    : CAS_HRPD_C2L_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HRPD��LTE��ѡ��صĲ���  3605
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLteReselectTimerLen;                /* EVDO��LTE����ѡʱ�� */
    VOS_INT16                           sHrpdQualityThreshold;                /* Hrpd Quality Threshold value, CL������ʹ�ã�DO�ܽ���ҵ���ŵ������� */
    PS_BOOL_ENUM_UINT8                  enSortEUTRAFreqByOhmOrder;            /* �Ƿ����otherRatNeighbor list��Ϣ�е�Ƶ��˳�򣬶�Ҫ��ѡ��Ƶ��������� */
    VOS_UINT8                           ucReserve;
}CAS_HRPD_NVIM_C2L_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_IDLE_HO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HRPD�汾��Ϣ   3606
*****************************************************************************/
typedef struct
{
    VOS_INT8                            cIdleHoOffset;                          /* idle ho ����f */
    VOS_INT8                            cIdleHoStrengthK;                       /* idle ho ����k */
    VOS_INT8                            cIdleHoThresh;                          /* idle ho ����y */
    VOS_UINT8                           ucReserve;
    VOS_UINT16                          usTimeLength;                           /* ���ʱ��,��λms */
    VOS_INT8                            ucReserve1;
    VOS_INT8                            ucReserve2;
}CAS_HRPD_NVIM_IDLE_HO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_CFG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HRPD����Э����ز���  3607
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHscpAnPhaseTimerLength;             /* ����Э��ATЭ�̽׶εı�����ʱ��ʱ�� */
    VOS_UINT8                           ucCfgMsgSendTimes;                    /* ����Э�̹����У�ConfigurationRequest��Ϣ�ķ��ʹ�����Ĭ��ֵΪ1 */
    VOS_UINT8                           ucKeyResponseTimeout;                 /* KeyResponse��Ϣ�е�Timeout�ֶΣ���λΪ�� */
    VOS_UINT8                           ucSuppItatProtocol;                   /* eAT�����ʼ����Э��ʱ���Ƿ�Я��Irat��Э�������� */
    VOS_UINT8                           ucReserve;
}CAS_HRPD_NVIM_CFG_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_TIMER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  :  HRPD Timer��NV����  3608
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usConnectCloseDelayTimerLength;         /* �ȴ�ConnectionClose��Ϣ����ʱ������λΪms */
    VOS_UINT16                          usWaitRfOccupyResApplyCnfTimerLength;   /* �ڶ��������еȴ�RF��Դ������Ӧʱ������λ:ms */
    VOS_UINT16                          usWaitCprocNoRfIndTimerLength;          /* Cproc�ϱ�NO_RF_IND��ȴ�RF_INDʱ������λ:ms */
    VOS_UINT16                          usWaitInitSrchRfResApplycnfTimerLength; /* �����������еȴ�RF��Դ����ʱ������λ:ms */
    VOS_UINT16                          usMonitorInterFreqMeasTimerLength;      /* ��Ƶ������ض�ʱ��ʱ������λ:ms */
    VOS_UINT16                          usInterFreqOutFromCanSetTimerLength;    /* ��Ƶ�����Ӻ�ѡ�����޳���ʱ��ʱ������λ:ms */
    VOS_UINT16                          usTcaProtectRFTimerLength;              /* �յ����н�����Ϣ��DataCnf�󱣻���Ƶ��Դ��ʱ������λ:ms */
    VOS_UINT16                          usReserve7;
}CAS_HRPD_NVIM_TIMER_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_SESSION_CFG_DATA_PART1_STRU
 Э����  :
 ASN.1���� : ÿ��NV���洢1.95K�ֽڣ�����Э�����ԱȽ϶࣬
             ������������NV�洢����Э�����ԣ��˽ṹΪ��һ����NV
 �ṹ˵��  : HRPD ����Э����ɺ������б� NV����  3609
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enPersonalityTblListValid;              /* Personality�б��Ƿ���Ч */
    PS_BOOL_ENUM_UINT8                  enPart2Valid;                           /* �ڶ�����NV�Ƿ�洢Personality */
    VOS_UINT16                          usPersonalityNum;                       /* ��ǰ��ЧPersonality������ */
    VOS_UINT16                          usPersonalityIdx;                       /* ��ǰ��ʹ�õ�Personality���±� */
    VOS_UINT16                          usSessionToken;
    VOS_UINT16                          usPart1Length;                          /* ��һ������Ч���ݳ��� */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT16                          usReserve3;
    VOS_UINT16                          usReserve4;
    VOS_UINT16                          usReserve5;
    VOS_UINT16                          usReserve6;
    VOS_UINT8                           aucPart1Value[NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_VALUE_SIZE];  /* ����ʵ�� */
}CAS_HRPD_NVIM_SESSION_CFG_DATA_PART1_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_SESSION_CFG_DATA_PART2_STRU
 Э����  :
 ASN.1���� : ÿ��NV���洢1.95K�ֽڣ�����Э�����ԱȽ϶࣬
             ������������NV�洢����Э�����ԣ��˽ṹΪ�ڶ�����NV
 �ṹ˵��  : HRPD ����Э����ɺ������б� NV����  3610
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPart2Length;                          /* �ڶ�������Ч���ݳ��� */
    VOS_UINT16                          usReserve1;
    VOS_UINT16                          usReserve2;
    VOS_UINT16                          usReserve3;
    VOS_UINT16                          usReserve4;
    VOS_UINT16                          usReserve5;
    VOS_UINT16                          usReserve6;
    VOS_UINT8                           aucPart2Value[NV_ITEM_CAS_HRPD_SESSION_CFG_DATA_VALUE_SIZE];/* ����ʵ�� */
}CAS_HRPD_NVIM_SESSION_CFG_DATA_PART2_STRU;


/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_SWITCH_PARA_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HRPD���ز���    3611
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enInterFreqMeasThresJudgeSwitch;        /* ��Ƶ���������Ƿ��ж����޿��� 0:��ʾ���عرգ���ʱ�ڿ���̬������̬��ֻҪ����Ƶ���������·��������ò⣬
                                                                                   1:��ʾ���ش򿪣���ʱ�ڿ���̬������Ƶ������������̬�������ѡ�������ڼ�������Ƶ����������
                                                                                   ����ͺ�ѡ���е�ͬƵƵ������ֵ��С��-5db������ʱ����������Ƶ��������������Ƶ*/
    PS_BOOL_ENUM_UINT8                  enSlotModeSwitch;                       /* ʱ϶ģʽ���أ�1��ʾ���ش� */
    PS_BOOL_ENUM_UINT8                  enScpDeactiveInitOhmSwitch;             /* SCPȥ�����ʼ��OHM���أ�1��ʾ���ش� */
    PS_BOOL_ENUM_UINT8                  enConnOpenSndRuSwitch;                  /* ���ӽ����ϱ�RU���أ�1��ʾ���ش� */
    PS_BOOL_ENUM_UINT8                  enIdleHoFromCndAndNbrSwitch;            /* ����̬�л��Ӻ�ѡ�������ڼ�ѡ��Ŀ��أ�1��ʾ���ش� */
    VOS_INT8                            cDynamicThreshAdjustValue;              /* ��̬���޵���������0.125dbΪ��λ��Ĭ��ֵΪ12 */
    VOS_UINT8                           ucReserve6;
    VOS_UINT8                           ucReserve7;
}CAS_HRPD_NVIM_SWITCH_PARA_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_STRENGTH_FILTER_RATIO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : HRPD����ֵ�˲�ϵ�� 3612
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIdleOldStrengthFilterRatio;           /* ����̬������ֵ�˲�ϵ�� */
    VOS_UINT8                           ucIdleNewStrengthFilterRatio;           /* ����̬������ֵ�˲�ϵ�� */
    VOS_UINT8                           ucConnOldStrengthFilterRatio;           /* ����̬������ֵ�˲�ϵ�� */
    VOS_UINT8                           ucConnNewStrengthFilterRatio;           /* ����̬������ֵ�˲�ϵ�� */
}CAS_HRPD_NVIM_STRENGTH_FILTER_RATIO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_INTERFREQ_MEAS_THRESHOLD_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��Ƶ������ͣ���� 3613 for DTS2016022304697
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sInterFreqMeasLowThreshold;             /* ��Ƶ���������ޣ�����ͬƵС���������ڵ����ޣ�������Ƶ��������λ:1/8db */
    VOS_INT16                           sInterFreqMeasHighThreshold;            /* ��Ƶ���������ޣ�����ͬƵС���������ڸ����ޣ���ֹͣ��Ƶ��������λ:1/8db */
}CAS_HRPD_NVIM_INTERFREQ_MEAS_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_EUTRA_CELL_RESEL_CTR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : C2L��ѡ��ض��Ʋ��������ڽ��3G��4G��ʽ֮��ƽ���л������� 3614
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucJudgeL2CReselOrRedirTimeLen;           /* �ڸö�ʱ���涨ʱ�����ж��Ƿ���L2C��ѡ���ض��� */
    VOS_UINT8                          ucL2CReselOrRedirMaxNum;                 /* ����ΪucJudgeL2CReselOrRedirTimeLenʱ���ڴ�Lģ��ѡ���ض���Cģ�������� */
    VOS_UINT8                          ucC2LReselPenalTimeLen;                  /* C2L��ѡ�ͷ���ʱ��ʱ�� */
    VOS_UINT8                          ucC2LReselOffset;                        /* ���ͷ���ʱ������ʱ��C2L��ѡƫ�ò��� */
    VOS_UINT8                          ucReserve1;
    VOS_UINT8                          ucReserve2;
    VOS_UINT8                          ucReserve3;
    VOS_UINT8                          ucReserve4;
}CAS_HRPD_NVIM_EUTRA_CELL_RESEL_CTR_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CAS_HRPD_NVIM_CHR_REPORT_CTR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CHR���ԣ������ϱ��Ŀ�����Ϣ 3615
*****************************************************************************/
typedef struct
{
    PS_BOOL_ENUM_UINT8                  enRcvTcaFailRptFlag;                    /* �ղ���TCA�Ƿ���Ҫ�����ϱ���ǣ�TRUE �ϱ���FALSE ���ϱ� */
    VOS_UINT8                           ucReserve1;
    VOS_UINT8                           ucReserve2;
    VOS_UINT8                           ucReserve3;
}CAS_HRPD_NVIM_CHR_REPORT_CTR_INFO_STRU;


/* CPROC_HRPD start here */

/*****************************************************************************
 �ṹ��    : CPROC_HRPD_NVIM_PILOT_SEARCH_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : cproc hrpd����������ز��� 3671 for DTS2016022502918
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucQuickFlag;                            /**< 0----normal  1-----quick mode, only for evdo only */
    VOS_UINT8                           ucReserved1;
    VOS_UINT16                          usReserved2[3];
}CPROC_HRPD_NVIM_PILOT_SEARCH_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_RM_NVIM_1X_OCCUPY_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : 1x�ɷ���ռ���� 3672 for DTS2016030805442
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          us1xOccupyFlag;                         /* 1X�ɷ񱻱���ռ���� 0:��ʾ���ɱ���ռ 1:��ʾ���Ա���ռ */
    VOS_UINT8                           ucReserve[2];
}CPROC_RM_NVIM_1X_OCCUPY_INFO_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_HRPD_NVIM_OPTIMIZE_SWITCH_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPROC HRPD �Ż�����, 3673
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               enTimeInterruptResetFlag;               /*Wake up time is inconsistent with BBP.
                                                                                     1 Reset.
                                                                                     0 send error ind to cas. Expected release all from Cas*/

    VOS_UINT8                               aucReserved[31];
}CPROC_HRPD_NVIM_OPTIMIZE_SWITCH_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_HRPD_NVIM_TCH_HO_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPROC_HRPD���ڿ���tch�л��Ŀ��Ʋ��� 3674 for DTS2016031405459
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLevel1CreditEcn0filterThresh;         /* ���С�������С��Ecn0Filter�Ƚ�һ�����ޣ�����0.125DB��Ĭ��ֵΪ0.5db*8 */
    VOS_UINT8                           ucLevel1CreditTimeThresh;               /* һ���������������л��Ĵ�����Ĭ��Ϊ4�� */
    VOS_UINT8                           ucLevel2CreditEcn0filterThresh;         /* ���С�������С��Ecn0Filter�Ƚ϶������ޣ�����0.125DB��Ĭ��ֵΪ1db*8 */
    VOS_UINT8                           ucLevel2CreditTimeThresh;               /* �����������������л��Ĵ�����Ĭ��Ϊ2�� */
    VOS_UINT8                           ucCreditCalcPeriod;                     /* �����С�������С�������Ƚϵ����ڣ���1slotΪ��λ��
                                                                                   Ĭ��Ϊ16slot,��ÿ��16slot����һ��С���Ƿ�����һ����������� */
    VOS_UINT8                           ucScunlockHoDelay;                      /* ����С��unlock��������HO��ʱ������1slotΪ��λ��Ĭ��Ϊ64slot */
    VOS_UINT8                           ucDrcHoRelativeEcn0filterThresh;        /* ����С��unlock����������л���С��ʱ����ڵ�ǰ����С����ECN0FILTER���ޣ�����0.125db��Ĭ��Ϊ 6db*8 */
    VOS_UINT8                           ucHoDrclockedTimeTh;                    /* �л�ʱdrclock����С�������� */
}CPROC_HRPD_NVIM_TCH_HO_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_HRPD_NVIM_1X_PAGING_FAIL_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPROC_RM���ڿ���1X��ΪHRPD����ʧ��֪ͨHRPD�Ƿ�ʹ�ܱ��� 3675 for DTS2016022201365
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDeprotectHrpdFor1xPaging;             /* 1x����Ѱ��ʧ������£�֪ͨHRPD����������Ĺ��ܿ��� */
    VOS_UINT8                           uc1xPagingFailMaxCnt128;                /* 1xʱ϶��������Ϊ1.28sʱ���������paging fail�ﵽMAXCNT��֪ͨHRPD�������� */
    VOS_UINT8                           uc1xPagingFailMaxCnt256;                /* 1xʱ϶��������Ϊ2.56sʱ���������paging fail�ﵽMAXCNT��֪ͨHRPD�������� */
    VOS_UINT8                           uc1xPagingFailMaxCnt512;                /* 1xʱ϶��������Ϊ5.12sʱ���������paging fail�ﵽMAXCNT��֪ͨHRPD�������� */
}CPROC_HRPD_NVIM_1X_PAGING_FAIL_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : CPROC_HRPD_NVIM_MEASURENT_CTRL_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CPROC_HRPD������صĲ������� 3676 for DTS2016032105464
*****************************************************************************/
typedef struct
{
    VOS_INT16                           sThAddIc;                               /* ecn0_filter ����IC��������ޣ�0.125dbΪ��λ��Ĭ��ֵ( -12 * 8 ) */
    VOS_INT16                           sThDeleteIc;                            /* ecn0_filter ICС��ɾ����������ޣ�0.125dbΪ��λ��Ĭ��ֵ( -15 * 8 )*/
    VOS_INT16                           sThAbsAddIc;                            /* ecn0 ����IC�ľ������ޣ�0.125dbΪ��λ��Ĭ��ֵ( -14 * 8 ) */
    VOS_INT16                           sThAbsDelIc;                            /* ecn0 ɾ��IC�ľ������ޣ�0.125dbΪ��λ��Ĭ��ֵ( -18 * 8 ) */
    VOS_INT16                           sThReplaceIc1;                          /* ecn0_filter ICС���滻���������1��0.125dbΪ��λ��Ĭ��ֵ( 3 * 8 ) */
    VOS_INT16                           sThReplaceIc2;                          /* ecn0_filter ICС���滻���������2��0.125dbΪ��λ��Ĭ��ֵ( 3 * 8 ) */
    VOS_INT16                           sThAgeIc2;                              /* ICС���滻����2����Ĵ��� Ĭ��ֵ( 3 ) */
    VOS_UINT8                           ucMaxIcNum;                             /* ICС���������� Ĭ��ֵ( 3 ) */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usNsfPeriodInSlot;                      /* ��Ƶ�������ڣ�Ĭ��Ϊ576����slotΪ��λ */
    VOS_UINT16                          usReserved1;
    VOS_UINT16                          usReserved2;
    VOS_UINT16                          usReserved3;
}CPROC_HRPD_NVIM_MEASURENT_CTRL_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
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

#endif /* end of CasNvInterface.h */


