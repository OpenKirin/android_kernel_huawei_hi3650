/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : GasNvInterface.h
  Description     : GasNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __GASNVINTERFACE_H__
#define __GASNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(2)
#else
#pragma pack(push, 2)
#endif

#include "vos.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/
#define NVIM_ULTRA_CLASSMARK_LEN                            (24)
#define NVIM_BAND_PWR_LEN                                   (8)
#define NVIM_CLASSMARK1_LEN                                 (2)
#define NVIM_CLASSMARK2_LEN                                 (4)
#define NVIM_CLASSMARK3_LEN                                 (16)
#define NVIM_CLASSMARK3_R8_LEN                              (36)
#define NVIM_GCF_ITEM_LEN                                   (80)
#define NVIM_GSM_BA_MAX_SIZE                                (33)
#define NVIM_EGPRS_RA_CAPABILITY_DATA_LEN                   (53)
#define NVIM_PREFER_GSM_PLMN_LIST_LEN                       (976)
#define NVIM_GSM_DEC_FAIL_ARFCN_LIST_LEN                    (120)
#define NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM                    (64)
#define NVIM_TDS_MAX_SUPPORT_BANDS_NUM                      (8)
#define NVIM_EUTRA_CAPA_COMM_INFO_SIZE                      (260)
#define NVIM_CBS_MID_LIST_LEN                               (2004)
#define NVIM_CBS_MID_RANGE_LIST_LEN                         (2004)
#define NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_CNT_MAX        (20)

#define NVIM_GAS_GSM_BAND_CUSTOMIZE_LIST_MAX_CNT            (80)

#define NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_PLMN_MAX_CNT        (10)
#define NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_MAX_CNT       (8)
#define NVIM_GSM_OPERATE_CUSTOMIZE_DESCRETE_FREQ_MAX_CNT    (16)

#if defined( __PS_WIN32_RECUR__ ) || defined (DMT)
#define MAX_CHR_ALARM_ID_NUM (20)
#endif

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum NVIM_TDS_FREQ_BAND_LIST_ENUM
{
    ID_NVIM_TDS_FREQ_BAND_A         = 0x01,         /* Ƶ�㷶Χ: 9504~9596  10054~10121 */
    ID_NVIM_TDS_FREQ_BAND_B         = 0x02,         /* Ƶ�㷶Χ: 9254~9546  9654~9946 */
    ID_NVIM_TDS_FREQ_BAND_C         = 0x04,         /* Ƶ�㷶Χ: 9554~9646 */
    ID_NVIM_TDS_FREQ_BAND_D         = 0x08,         /* Ƶ�㷶Χ: 12854~13096 */
    ID_NVIM_TDS_FREQ_BAND_E         = 0x10,         /* Ƶ�㷶Χ: 11504~11996 */
    ID_NVIM_TDS_FREQ_BAND_F         = 0x20,         /* Ƶ�㷶Χ: 9404~9596 */
    ID_NVIM_TDS_FREQ_BAND_BUTT
};
typedef VOS_UINT8  NVIM_TDS_FREQ_BAND_LIST_ENUM_UINT8;

/*****************************************************************************
 ö �� ��  : NVIM_BAND_IND
 ö��˵��  : NV��BANDָʾ
 �޸���ʷ  :
  1.��  ��   : 2015��9��14��
    ��  ��   : s00184266
    �޸����� : ������ö��

*****************************************************************************/
enum NVIM_BAND_IND_ENUM
{
    NVIM_BAND_IND_2                 = 0x2,          /* BAND2 */
    NVIM_BAND_IND_3                 = 0x3,          /* BAND3 */
    NVIM_BAND_IND_5                 = 0x5,          /* BAND5 */
    NVIM_BAND_IND_8                 = 0x8,          /* BAND8 */
    NVIM_BAND_IND_BUTT
};
typedef VOS_UINT8 NVIM_BAND_IND_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 �ṹ��    : NVIM_ULTRA_CLASSMARK_STRU
 �ṹ˵��  : en_NV_Item_Ultra_Classmark �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucUltraClassmark[NVIM_ULTRA_CLASSMARK_LEN];
}NVIM_ULTRA_CLASSMARK_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_MULTIRATE_FLAG_STRU
 �ṹ˵��  : en_NV_Item_Gas_MultiRateFlag �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMultiRateFlag;
    VOS_UINT8                           aucReserve[2];
}NVIM_GAS_MULTIRATE_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_BAND_PWR_STRU
 �ṹ˵��  : en_NV_Item_Band_Pwr �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucBandPwr[NVIM_BAND_PWR_LEN];
}NVIM_BAND_PWR_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_VGCS_FLAG_STRU
 �ṹ˵��  : en_NV_Item_Vgcs_Flag �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usVgcsFlag;
    VOS_UINT8                           aucReserve[2];
}NVIM_VGCS_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EGPRS_MULTI_SLOT_CLASS_STRU
 �ṹ˵��  : en_NV_Item_Egprs_Multi_Slot_Class �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEgprsMultiSlotClass;                  /* Range: [0,12] */
    VOS_UINT8                           aucReserve[2];
}NVIM_EGPRS_MULTI_SLOT_CLASS_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CLASSMARK1_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Classmark1 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark1[NVIM_CLASSMARK1_LEN];
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_CLASSMARK1_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CLASSMARK2_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Classmark2 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark2[NVIM_CLASSMARK2_LEN];
}NVIM_GSM_CLASSMARK2_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CLASSMARK3_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Classmark3 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGsmClassmark3[NVIM_CLASSMARK3_LEN];
}NVIM_GSM_CLASSMARK3_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_IND_FREQ_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Ind_Freq �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmIndFreq;
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_IND_FREQ_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GCF_ITEM_STRU
 �ṹ˵��  : en_NV_Item_GCF_Item �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucGcfItem[NVIM_GCF_ITEM_LEN];
}NVIM_GCF_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_G2W_RSSI_RSCP_OFFSET_STRU
 �ṹ˵��  : en_NV_Item_G2W_RSSI_RSCP_OFFSET �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usG2WRssiRscpOffset;
    VOS_UINT8                           aucReserve[2];
}NVIM_G2W_RSSI_RSCP_OFFSET_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_BA_COUNT_STRU
 �ṹ˵��  : en_NV_Item_GSM_Ba_Count �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmBaCount;
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_BA_COUNT_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_BA_LIST_STRU
 �ṹ˵��  : en_NV_Item_GSM_Ba_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    VOS_UINT16                          usArfcn[NVIM_GSM_BA_MAX_SIZE];
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_BA_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EGPRS_FLAG_STRU
 �ṹ˵��  : en_NV_Item_Egprs_Flag �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usEgprsFlag;
    VOS_UINT8                           aucReserve[2];
}NVIM_EGPRS_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EGPRS_RA_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_EgprsRaCapability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucEgprsRaCapabilityData[NVIM_EGPRS_RA_CAPABILITY_DATA_LEN];
    VOS_UINT8                           aucReserve[2];
}NVIM_EGPRS_RA_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PREFER_GSM_PLMN_COUNT_STRU
 �ṹ˵��  : en_NV_Item_Prefer_GSM_PLMN_Count �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPreferGsmPlmnCount;
    VOS_UINT8                           aucReserve[2];
}NVIM_PREFER_GSM_PLMN_COUNT_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PREFER_GSM_PLMN_LIST_STRU
 �ṹ˵��  : en_NV_Item_Prefer_GSM_PLMN_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausPreferGsmPlmnListData[NVIM_PREFER_GSM_PLMN_LIST_LEN];
}NVIM_PREFER_GSM_PLMN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_DEC_FAIL_ARFCN_COUNT_STRU
 �ṹ˵��  : en_NV_Item_GSM_DEC_FAIL_ARFCN_Count �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmDecFailArfcnCount;
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_DEC_FAIL_ARFCN_COUNT_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_DEC_FAIL_ARFCN_LIST_STRU
 �ṹ˵��  : en_NV_Item_GSM_DEC_FAIL_ARFCN_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmDecFailArfcnList[NVIM_GSM_DEC_FAIL_ARFCN_LIST_LEN];
}NVIM_GSM_DEC_FAIL_ARFCN_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PREFER_GSM_PLMN_SWITCH_STRU
 �ṹ˵��  : en_NV_Item_Prefer_GSM_PLMN_Switch �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usPreferGsmPlmnSwitch;
    VOS_UINT8                           aucReserve[2];
}NVIM_PREFER_GSM_PLMN_SWITCH_STRU;

/*****************************************************************************
 �� �� ��  : NVIM_PREFER_GSM_PLMN_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : ��ѡС�����ܶ���
 �޸���ʷ  :
  1.��  ��   : 2015��9��9��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAgingEnable;                          /* ��ѡС���ϻ���NVʹ�� */
    VOS_UINT8                           ucRsrv1;                                /* ����λ */
    VOS_UINT8                           ucRsrv2;                                /* ����λ */
    VOS_UINT8                           ucRsrv3;                                /* ����λ */
    VOS_INT16                           sDecFailedRssiThreshold;                /* ����ѡС���б���ɾ������ʧ�ܵ�RSSI���� */
    VOS_UINT16                          usRsrv1;                                /* ����λ */
    VOS_UINT16                          usRsrv2;                                /* ����λ */
    VOS_UINT16                          usRsrv3;                                /* ����λ */
    VOS_UINT32                          ulRsrv1;                                /* ����λ */
    VOS_UINT32                          ulRsrv2;                                /* ����λ */
}NVIM_PREFER_GSM_PLMN_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GERAN_FEATURE_PACKAGE1_STRU
 �ṹ˵��  : en_NV_Item_Geran_Feature_Package1 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGeranFeaturePackage1;                 /* Range: [0,1] */
    VOS_UINT8                           aucReserve[2];
}NVIM_GERAN_FEATURE_PACKAGE1_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_A5_STRU
 �ṹ˵��  : en_NV_Item_Gsm_A5 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmA5;                                /* Range: [0,7] */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_A5_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_LOW_COST_EDGE_FLAG_STRU
 �ṹ˵��  : en_NV_Item_LowCostEdge_Flag �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usLowCostEdgeFlag;                      /* Range: [0,1] */
    VOS_UINT8                           aucReserve[2];
}NVIM_LOW_COST_EDGE_FLAG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GPRS_ACTIVE_TIMER_LENGTH_STRU
 �ṹ˵��  : en_NV_Item_GPRS_ActiveTimerLength �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGprsActiveTimerLength;
}NVIM_GPRS_ACTIVE_TIMER_LENGTH_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GPRS_MULTI_SLOT_CLASS_STRU
 �ṹ˵��  : en_Nv_Item_Gprs_Multi_Slot_Class �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGprsMultiSlotClass;                   /* Range: [0,12] */
    VOS_UINT8                           aucReserve[2];
}NVIM_GPRS_MULTI_SLOT_CLASS_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_PLMN_SEARCH_ARFCN_MAX_NUM_STRU
 �ṹ˵��  : en_NV_Item_GSM_PLMN_SEARCH_ARFCN_MAX_NUM �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usGsmPlmnSearchArfcmMaxNum;             /* Range: [0x1,0x8C] */
    VOS_UINT8                           aucReserve[2];
}NVIM_GSM_PLMN_SEARCH_ARFCN_MAX_NUM_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GCBS_CONF_STRU
 �ṹ˵��  : en_Nv_Item_GCBS_Conf �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usECBCHSwitch;              /* Range: [0,1] */
    VOS_UINT16                                      usDrxSwitch;                /* Range: [0,1] */
    VOS_UINT32                                      ulGCBSActiveTimerLength;
}NVIM_GCBS_CONF_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_REPEATED_ACCH_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_Repeated_Acch_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usRepeatedAcchCapability;
    VOS_UINT8                                       aucReserve[2];
}NVIM_REPEATED_ACCH_CAPABILITY_STRU;


/*****************************************************************************
 �ṹ��    : NVIM_ES_IND_STRU
 �ṹ˵��  : en_NV_Item_ES_IND �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usEsInd;                    /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_ES_IND_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_GPRS_Extended_Dynamic_Allocation_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usGprsExtDynAllocCap;       /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_GPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EGPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_EGPRS_Extended_Dynamic_Allocation_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usEGprsExtDynAllocCap;      /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_EGPRS_EXTENDED_DYNAMIC_ALLOCATION_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_REVISION_LEVEL_INDICATOR_STRU
 �ṹ˵��  : en_NV_Item_Revision_Level_Indicator �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usRevLvlInd;                /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_REVISION_LEVEL_INDICATOR_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_REVISION_LEVEL_CUSTOMIZE_STRU
 �ṹ˵��  : en_NV_Item_GAS_Revision_Level_Customization �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucInterRatCustomizeFlag;       /* ��ϵͳ��ȡclassmark2�е�Revison level IE�������ƣ�
                                                                           0:��ϵͳ��ȡ���������ƣ�
                                                                           1:��ʾ������Ч����ϵͳ��ȡ����classmark2��Revison level�̶����R99���Ժ�汾
                                                                        */
    
    VOS_UINT8                            ucRsv1;                        /* ����λ1 */
    
    VOS_UINT8                            ucRsv2;                        /* ����λ2 */
    
    VOS_UINT8                            ucRsv3;                        /* ����λ3 */

}NVIM_GAS_REVISION_LEVEL_CUSTOMIZE_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_DOWNLINK_ADVANCED_RECEIVER_PERFORMANCE_STRU
 �ṹ˵��  : en_NV_Item_Downlink_Advanced_Receiver_Performance �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usDlAdvRcvPer;              /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_DOWNLINK_ADVANCED_RECEIVER_PERFORMANCE_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EXT_RLC_MAC_CTRL_MSG_SEGMENT_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_Ext_RLC_MAC_Ctrl_Msg_Segment_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usExtRlcMacCtrlMsgSegCap;   /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_EXT_RLC_MAC_CTRL_MSG_SEGMENT_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PS_HANDOVER_CAPABILITY_STRU
 �ṹ˵��  : en_NV_Item_PS_Handover_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPsHandoverCapability;     /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_PS_HANDOVER_CAPABILITY_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_WEAK_SIGNAL_THREHOLD_STRU
 �ṹ˵��  : en_NV_Item_GAS_Errorlog_Energy_Threshold �ṹ
*****************************************************************************/
typedef struct
{
    VOS_INT16                                       sWeakSignalThreshold;
    VOS_UINT8                                       aucReserve[2];
}NVIM_GAS_WEAK_SIGNAL_THREHOLD_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_MULTIRATE_CAP_STRU
 �ṹ˵��  : en_NV_Item_GSM_Multirate_Capability �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       ucGsmMultirateCap;
    VOS_UINT8                                       aucRsv[3];
}NVIM_GSM_MULTIRATE_CAP_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CLASSMARK3_R8_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Classmark3_R8 �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                                       aucGsmClassMark3Data[NVIM_CLASSMARK3_R8_LEN];
}NVIM_GSM_CLASSMARK3_R8_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usLteMeasSupportedFlg;      /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_EUTRA_MEAS_AND_REPORTING_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_PRI_BASED_RESEL_SUPPORT_FLG_STRU
 �ṹ˵��  : en_NV_Item_PRI_BASED_RESEL_SUPPORT_FLG �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usPriBasedReselSupportFlg;  /* Range: [0,1] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_PRI_BASED_RESEL_SUPPORT_FLG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE_STRU
 �ṹ˵��  : en_NV_Item_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                      usLteSupportInTransferMode; /* Range: [0,3] */
    VOS_UINT8                                       aucReserve[2];
}NVIM_GERAN_TO_EUTRA_SUPPORT_IN_TRANSFER_MODE_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU
 �ṹ˵��  : ��������һ�� LTE Ƶ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBandNo;
    VOS_UINT8                           ucDuplexModeFlg;
    VOS_UINT8                           aucReserve[2];
}NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU
 �ṹ˵��  : en_NV_Item_EUTRA_CAPA_COMM_INFO �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usBandCnt;
    VOS_UINT8                               aucReserved1[2];
    NVIM_UE_EUTRA_FREQ_BAND_INFO_STRU       astCandBands[NVIM_EUTRA_MAX_SUPPORT_BANDS_NUM];
}NVIM_UE_EUTRA_SUPPORT_FREQ_BAND_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU
 �ṹ˵��  : en_NV_Item_GAS_High_Multislot_Class �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usHighMultislotClassFlg;
    VOS_UINT16                              usHighMultislotClass;
}NVIM_GAS_HIGH_MULTISLOT_CLASS_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GPRS_NON_DRX_TIMER_LENGTH_STRU
 �ṹ˵��  : en_NV_Item_GPRS_Non_Drx_Timer_Length �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usNonDrxTimerLen;                   /* Range: [0,7] */
    VOS_UINT8                               aucReserve[2];
}NVIM_GPRS_NON_DRX_TIMER_LENGTH_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU
 �ṹ˵��  : en_NV_Item_UTRAN_TDD_FREQ_BAND �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               ucBandCnt;                          /* Range: [0,6] */
    VOS_UINT8                               aucReserved[3];
    VOS_UINT8                               aucBandNo[NVIM_TDS_MAX_SUPPORT_BANDS_NUM];
}NVIM_UE_TDS_SUPPORT_FREQ_BAND_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_QSEARCH_CUSTOMIZATION_STRU
 �ṹ˵��  : en_NV_Item_QSearch_Customization �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usQSearchCustomMode;
    VOS_UINT8                               aucReserve[2];
}NVIM_QSEARCH_CUSTOMIZATION_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_POOR_RXQUAL_THRESHOLD_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Poor_RxQual_ThresHold �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usRrPoorRxQualThresHold;
    VOS_UINT8                               aucReserve[2];
}NVIM_GSM_POOR_RXQUAL_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_CSFB_CUSTOMIZATION_STRU
 �ṹ˵��  : en_NV_Item_Csfb_Customization �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                              usCsfbCustomization;
    VOS_UINT8                               aucReserve[2];
}NVIM_CSFB_CUSTOMIZATION_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_CBS_MID_LIST_STRU
 �ṹ˵��  : en_NV_Item_CBS_MID_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucCbsMidList[NVIM_CBS_MID_LIST_LEN];
}NVIM_CBS_MID_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_CBS_MID_RANGE_LIST_STRU
 �ṹ˵��  : en_NV_Item_CBS_MID_Range_List �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                               aucCbsMidRangeList[NVIM_CBS_MID_RANGE_LIST_LEN];
}NVIM_CBS_MID_RANGE_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_AUTO_FR_LTE_MEAS_CONFIG_STRU
 �ṹ˵��  : GSM�����ض���LTE��LTEƵ���������
 �޸���ʷ  :
 1.��    ��    : 2013��08��05��
   ��    ��    : y00142674
   �޸�����    : �½��ṹ��, GSM�����ض���LTE
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucFrLteMeasFlag;                        /* �Ƿ���GSM�����ض���LTE��LTEƵ�������0: �ر�, 1: ������Ĭ��ֵΪ1 */
   VOS_UINT8                            ucMaxSavedMeasTimes;                    /* ��󱣴�Ĳ���������Ĭ��ֵΪ8����Χ:[0,8] */

   VOS_UINT8                            ucFrInvalidMeasFlag;                    /* �Ƿ����ò�������ж�GSM�����ض���LTE�Ƿ���Ч��0: �ر�, 1: ������Ĭ��ֵΪ1 */
   VOS_UINT8                            ucMaxInvalidMeasTimes;                  /* �����Ч���������������ж�Ƶ���Ƿ���Ч����������󱣴�Ĳ���������Ĭ��ֵΪ8����Χ:[0,8] */
}NVIM_GSM_AUTO_FR_LTE_MEAS_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_C1_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : C1׼��������
 �޸���ʷ  :
 1.��    ��    : 2014��01��17��
   ��    ��    : w00146666
   �޸�����    : �½��ṹ��, Ӧ����C1׼����
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucC1CustomizeSwitchFlag;          /* �Ƿ���·��C1���ƣ�0: �ر�, 1: ������Ĭ��ֵΪ0 */
   VOS_UINT8                            ucRxlevAccessMin;                 /* ����·��C1���ƺ󣬶��Ƶ���С�����ƽ�ȼ���Ĭ�ϵȼ�Ϊ8����Χ:[0,63] */
   VOS_UINT8                            ucC1ValueThreshold;               /* C1��ֵ */
   VOS_UINT8                            aucRsv[1];
}NVIM_GSM_C1_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_NFREQ_THRESHOLD_STRU
 �ṹ˵��  : en_NV_Item_Gsm_NFreq_Threshold �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucFirstNFreqThreshold;                 /* ��Ƶ���Ź������� */
    VOS_UINT8                            aucRsv[3];
}NVIM_GSM_NFREQ_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_W_NON_NCELL_MEAS_CTRL_STRU
 �ṹ˵��  : en_NV_Item_Gas_W_Non_NCell_Meas_Ctrl �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucIdleNonNCellMeasEnable;              /* ����̬���Ƿ��������������� */
    VOS_UINT8                            ucTransferNonNCellMeasEnable;          /* ����̬���Ƿ��������������� */
    VOS_INT16                            sRscpThreshold;                        /* ���������������� RSCP ���� */
    VOS_INT16                            sEcn0Threshold;                        /* ���������������� ECN0 ���� */
    VOS_INT16                            sRssiThreshold;                        /* ���������������� RSSI ���� */
}NVIM_GAS_W_NON_NCELL_MEAS_CTRL_STRU;
/*****************************************************************************
 �ṹ��    : NV_GSM_RF_UNAVAILABLE_CFG_STRU
 �ṹ˵��  : en_NV_Item_GSM_RF_UNAVAILABLE_CFG �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucStartSearchFlag;                      /* �Ƿ���������:,1:��; 0:�� */
    VOS_UINT8                           ucSearchTimerLen;                       /* �೤ʱ��������������λ:s */
    VOS_UINT8                           ucEnableScellSbFbFlag;                  /* �Ƿ���Ч����С��ͬ����1:�ǣ�0:�� */
    VOS_UINT8                           ucRsv;
}NV_GSM_RF_UNAVAILABLE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_CELL_INFO_RPT_CFG_STRU
 �ṹ˵��  : en_NV_Item_Gsm_Cell_Info_Rpt_Cfg �ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucCellInfoRptFlg;      /* �Ƿ������ϱ�: 0:������; 1:���� */
    VOS_UINT8                            aucRsv[1];             /* ����λ */
    VOS_UINT16                           usRptInterval;         /* �ϱ����ڳ���, ��λ: ms */
}NVIM_GSM_CELL_INFO_RPT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_INDIVIDUAL_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : en_NV_Item_Gas_Individual_Customize_Cfg �ṹ,�������÷Ǳ�����ⶨ����ص�����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAccFailNoPunishCfg;                   /* �Ƿ�ͷ��漴����ʧ�ܵ�С��:
                                                                                   bit0: 1: PSʧ�ܲ��ͷ�; 0: PSʧ�ܳͷ�
                                                                                   bit1: 1: CSʧ�ܲ��ͷ�; 0: CSʧ�ܳͷ� */
    VOS_INT8                            cFreqRxlevThreshold;                    /* ��ЧƵ����������,��Ҫ������������
                                                                                   ������ѡ Ŀ��С��ѡ��ʱҲ���õ� */

    VOS_UINT8                           ucAutoFrNonChanRelCase;                 /* û���յ� Channel Release ���쳣�������Ƿ����� FR:
                                                                                   bit0: 1: �����Ҷ�ʱ���� FR;
                                                                                         0: �����Ҷ�ʱ������FR
                                                                                   bit1: 1: ������·ʧ������FR;
                                                                                         0: ������·ʧ�ܲ�����FR
                                                                                   bit2: 1: ������·ʧЧ��������ǰ��Ҫ�ȳ��Ժ����ؽ�;
                                                                                         0: ������·ʧЧ��������ǰ����Ҫ�ȳ��Ժ����ؽ� */

    VOS_UINT8                           ucScellPrioFastEnableFlg;

    VOS_UINT8                           aucRsv[36];
}NVIM_GAS_INDIVIDUAL_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_MNTN_CONFIG_STRU
 �ṹ˵��  : GSM��ά�ɲ���ص�NV����
 �޸���ʷ  :
 1.��    ��    : 2014��07��03��
   ��    ��    : w00146666
   �޸�����    : �½��ṹ��
 2.��    ��    : 2015��10��26��
   ��    ��    : w00146666
   �޸�����    : �����ṹ����������α��վCHR�ϱ������ʱ���� NV���� 
 3.��    ��    : 2016��04��14��
   ��    ��    : w00146666
   �޸�����    : �����ṹ������GSM PA CHR��NV����(���������������Ӧ����, С���ź�ǿ�ȣ������ϱ������ʱ����)   
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usCsHoTimeAlarmThreshold;              /* CS�л�ʱ�䳤�����ޣ��������л�ʱ�䣬GAS�����ϱ��澯��Ϣ */

   VOS_UINT16                           usRptPseudBtsMinTimeInterval;          /* ����α��վCHR�ϱ������ʱ��������λ:���ӣ�Ĭ��ֵΪ30���� */   

   VOS_UINT16                           usRsv1;                                /* Ԥ��λ1��Ϊ�Ժ�KWKCԤ�� */

   VOS_UINT16                           usRptRaNoRspMinTimeInterval;           /* ���������������ӦCHR�ϱ������ʱ��������λ:���ӣ�Ĭ��ֵΪ30���� */   
   
   VOS_INT16                            sRaNoRspRssiThreshold;                 /* һ����Ч�������������Ӧ���������ޣ�������������GAS��¼һ����Ч�������������Ӧ,Ĭ��ֵΪ-85dBm */
   
   VOS_UINT8                            usRaNoRspAlarmTimesThreshold;          /* ���������������Ӧ�������ޣ������ô�����GAS�����ϱ��澯��Ϣ��Ĭ��ֵ��10�� */   

   VOS_UINT8                            ucRsv5;                                /* Ԥ��λ5��Ϊ�Ժ�KWKCԤ�� */      

   VOS_UINT32                           ulRsv6;                                /* Ԥ��λ6��Ϊ�Ժ�KWKCԤ�� */

   VOS_UINT32                           ulRsv7;                                /* Ԥ��λ7��Ϊ�Ժ�KWKCԤ�� */
}NVIM_GAS_MNTN_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN
 �ṹ˵��  : en_NV_Item_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN NV�ṹ ����û������
             �������ȼ��� UTRAN ��ѡ����ʱ, Ĭ�ϵ� UTRAN TDD Q_RXLMIN. ���ڻ���
             ���ȼ���ѡʱʹ��. ���� Ranking ��Ĭ����ѡ������ -90dB, ����Ҫ����
 �޸���ʷ  :
 1.��    ��    : 2014��12��20��
   ��    ��    : p00166345
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucTdsDefaultQRxlMin;            /* TDS Ĭ����ѡ����, ��λ: -1dB */

   VOS_UINT8                            aucRsv[3];                      /* ����λ */
}NVIM_GAS_UTRAN_TDD_DEFAULT_Q_RXLMIN;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_STRU
 �ṹ˵��  : C1�����Ż����������(Ŀǰ����L CSFB G������ʹ��)
 �޸���ʷ  : 
 1.��    ��    : 2015��02��06��
   ��    ��    : y00265681
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
}NVIM_GAS_PLMN_ID_STRU;

typedef struct
{
   VOS_UINT16                           usPlmnCnt;                          /* ��������PLMN���� */
   VOS_UINT16                           usRxlevAccessMin;                   /* ��������С�����Ƶ���С�����ƽ�ȼ�, Ĭ�ϵȼ�Ϊ8����Χ:[0,63]
                                                                               0ֵ��ʾ�������Ч, ��������ʹ�� NV9248 �� ucRxlevAccessMin ���ֵ */

   NVIM_GAS_PLMN_ID_STRU                astPlmn[NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_CNT_MAX];       /* Ԥ��λ��Ϊ�Ժ�KWKCԤ�� */
}NVIM_GAS_C1_CALC_OPT_PLMN_WHITE_LIST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_RAPID_HO_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : en_NV_Item_GSM_RAPID_HO_CUSTOMIZE_CFG �ṹ,GSM�����л����������������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitchFlag;                   /* ���Կ��� */
    VOS_UINT8                           ucBadQualityThreshold;          /* �ź������ж�����.������.��λ: �ٷ�֮һ */
    VOS_UINT16                          usAlpha;                        /* Alpha����. ��λ: 0.001 */
    VOS_UINT8                           ucBadQualityCntThreshold;       /* �ź�������ͳ������ */
    VOS_UINT8                           ucNCellRptAddValue;             /* �����ϱ�����ֵ */
    VOS_UINT8                           aucRsv[2];                      /* ����λ */
}NVIM_GSM_RAPID_HO_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_BAND_CUSTOMIZE_STRU
 �ṹ˵��  : GSM Ƶ�ζ��ƽṹ����
 �޸���ʷ  : 
 1.��    ��    : 2015-04-23
   ��    ��    : p00166345
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
    NVIM_GAS_PLMN_ID_STRU               stPlmn;
    VOS_UINT32                          ulBand;
}NVIM_GSM_BAND_CUSTOMIZE_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_GSM_BAND_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : en_NV_Item_GAS_GSM_BAND_CUSTOMIZE_CFG NV �ṹ����
 �޸���ʷ  : 
 1.��    ��    : 2015-04-23
   ��    ��    : p00166345
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
   VOS_UINT16                           usItemCnt;                  /* ��������� */
   VOS_UINT16                           usRestoreEnableMask;        /* ���ñ������ĳ���Э�鷶Χ��Ƶ����Ч���� */
   VOS_UINT32                           ulCustomizeBandEnableMask;  /* ���� Band ��Ч���� */
   NVIM_GSM_BAND_CUSTOMIZE_STRU         astCustomizeBand[NVIM_GAS_GSM_BAND_CUSTOMIZE_LIST_MAX_CNT];
}NVIM_GAS_GSM_BAND_CUSTOMIZE_CFG_STRU;

/* Added by y00142674 for ���������Ż�, 2015-04-30, begin */
/*****************************************************************************
 �ṹ��    : NVIM_GSM_SEARCH_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : en_NV_Item_GSM_SEARCH_CUSTOMIZE_CFG �ṹ��GSM���������������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRsv1;                                 /* ������������ָ���������Ƿ�ʹ����ʷƵ�� */
    VOS_UINT8                           ucRsv2;                                 /* ������GOos�������Ƿ�ʹ����ʷƵ�� */

    VOS_UINT8                           ucGeoHighUseStoreFlag;           /* ��������ȡ������Ϣ�����Ƿ�ʹ����ʷƵ�� */
    VOS_UINT8                           ucGeoHighRemoveStoreFlag;        /* ��������ȡ������Ϣ�����Ƿ��ڸ�����ɨƵ�׶�ɾ����ʷƵ�� */
    VOS_UINT8                           ucGeoNormalUseStoreFlag;         /* �Ǹ�������ȡ������Ϣ�����Ƿ�ʹ����ʷƵ�� */

    VOS_UINT8                           ucRmvDecFailSamePlmnFlag;        /* Ƶ�����ʧ�ܺ��Ƿ�ɾ��������ͬPLMN����ѡС�� */

    VOS_UINT8                           ucUpdateRssiBySi;                /* ����ϵͳ��Ϣ�����ź�ǿ�� */

    VOS_UINT8                           ucHistorySrchOperatorCustomizeCellCnt;  /* HISTORY������Ӫ�̶���Ƶ��ĸ�����Χ */

}NVIM_GSM_SEARCH_CUSTOMIZE_CFG_STRU;
/* Added by y00142674 for ���������Ż�, 2015-04-30, end */

/*****************************************************************************
 �ṹ��    : NVIM_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG_STRU
 �ṹ˵��  : en_NV_Item_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG NV �ṹ����
 �޸���ʷ  : 
 1.��    ��    : 2015-05-06
   ��    ��    : p00166345
   �޸�����    : �½��ṹ��
 2.��    ��    : 2015-07-15
   ��    ��    : y00142674
   �޸�����    : ��������ϵͳ��Ϣʹ�ܱ�־����Чʱ��

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucEnableFlg;                    /* �Ƿ���Ч */
    VOS_UINT8                           ucRefreshTimeLen;               /* ʹ����ʷϵͳ��Ϣפ������ǿ��ˢ��ϵͳ��Ϣ.
                                                                           ��λ:��. 0��ʾ��ǿ��ˢ�� */

    VOS_UINT16                          usValidTimeLen;                 /* ��Чʱ��, ��λ:���� */
    VOS_UINT32                          ulUsableMask;                   /* ����ָ������ʹ����ʷϵͳ��Ϣפ�������� */
    VOS_UINT8                           ucNcellEnableFlg;               /* ����ϵͳ��Ϣ�Ƿ���Ч */
    VOS_UINT8                           ucNcellValidTimeLen;            /* ��Чʱ��, ��λ:�� */
    VOS_UINT8                           ucRsv3;                         /* ����λ */
    VOS_UINT8                           ucRsv4;                         /* ����λ */
}NVIM_GAS_GSM_CELL_HISTORY_BCCH_SI_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_H_PRIO_CONDITION_FLAG_STRU
 �ṹ˵��  : H_PRIOʹ�ó����������� 
 �޸���ʷ  : 
 1.��    ��    : 2015��05��17��
   ��    ��    : w00146666
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucHPrioCustomizeFlag;   /* H_PRIOʹ�ó�����������, 0��ʾʹ��H_PRIO������������ϵͳС�������ȼ���
                                                                    1��ʾʹ��H_PRIO������ǰ����������ϵͳС�������ȼ��ȷ���С�����ȼ��� */
    
    VOS_UINT8                            ucRsv1;                 /* ����λ1 */
    
    VOS_UINT8                            ucRsv2;                 /* ����λ2 */
    
    VOS_UINT8                            ucRsv3;                 /* ����λ3 */
}NVIM_GAS_INTER_RAT_RESEL_H_PRIO_CUSTOMIZE_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_FAST_AREA_LOST_CFG_STRU
 �ṹ˵��  : en_NV_Item_GAS_FAST_AREA_LOST_CFG NV�ṹ
             ���ڶ��� RR �������ʧ�ܺ��Ƿ���ٸ� NAS �ϱ�����
 �޸���ʷ  : 
 1.��    ��    : 2015��05��15��
   ��    ��    : p00166345
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
   VOS_UINT8                            ucRrRaFailEnableFlg;        /* ��Ч��־ */

   VOS_UINT8                            ucRsv1;                     /* ����λ */
   VOS_UINT8                            ucRsv2;                     /* ����λ */
   VOS_UINT8                            ucRsv3;                     /* ����λ */
}NVIM_GAS_FAST_AREA_LOST_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_AUTO_FR_CFG_STRU
 �ṹ˵��  : en_NV_Item_GAS_AUTO_FR_CFG NV�ṹ
             ���������ھ��峡�����Ƿ������������ FR.
 �޸���ʷ  : 
 1.��    ��    : 2015-06-09
   ��    ��    : p00166345
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                            ucAutoFrInvalidMask;   /* ��Ч��־����bitֵ 0 ��ʾ���Է���, 1 ��ʾ��Ч�����Է��� */
                                                                /* bit0: CSFB ����, NAS��δ����ҵ���������������Ƿ���Է��� */
                                                                /* bit1: CSFB ����, NAS��δ����ҵ���������������Ƿ���Է��� */
                                                                /* bit2~bit8: ����λ */

    VOS_UINT8                            ucAutoFrNonCsfbFlg;       /* ��CSFB������, ҵ�����ʱ�Ƿ��������� */
    VOS_UINT8                            ucRsv2;                /* ����λ */
    VOS_UINT8                            ucRsv3;                /* ����λ */
}NVIM_GAS_AUTO_FR_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_INTER_RAT_RESEL_CFG_STRU
 �ṹ˵��  : en_NV_Item_GAS_INTER_RAT_RESEL_CFG NV�ṹ
             ����������ϵͳ��ѡ�������.
 �޸���ʷ  : 
 1.��    ��    : 2015-07-07
   ��    ��    : p00166345
   �޸�����    : �½��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPrioReselDisableMask; /* ���û������ȼ���������ѡ׼��ĳ���.���¸� bit ֵ1��ʾ����.0��ʾ������ */
                                                                /* ע: ����Ϊ0ʱ�Ƿ����û������ȼ����㷨����Э��� NV 9003��Լ�� */
                                                                /* bit0: LTE ģʽ��֧��, ��û��3G���ȼ������ĳ��� */
                                                                /* bit1: LTE ģʽ�� Disable, ��û��3G���ȼ������ĳ��� */
                                                                /* bit2~bit8: ����λ */

    VOS_UINT8                           ucRsv1;                 /* ����λ */
    VOS_UINT8                           ucRsv2;                 /* ����λ */
    VOS_UINT8                           ucRsv3;                 /* ����λ */
    VOS_UINT16                          usRsv4;                 /* ����λ */
    VOS_UINT16                          usRsv5;                 /* ����λ */
}NVIM_GAS_INTER_RAT_RESEL_CFG_STRU;

/* Added by p00166345 for DTS2015052601104(α��վʶ��), 2015-08-02, begin */
/*****************************************************************************
 Structure      : NVIM_GAS_PSEUD_BTS_IDENT_CUSTOMIZE_CFG_STRU
 Description    : α��վ�ж϶�����NV�ṹ
 Message origin :
 �޸���ʷ :
  1.��    ��    : 2015��07��29��
    ��    ��    : yangsicong
    �޸�����    : α��վʶ����Ŀ
*****************************************************************************/
typedef struct
{
    VOS_UINT16      usEnableBitmap;             /* ʶ���㷨�Ƿ�ʹ�� ��0=�ǣ�1=�� */
                                                    /* bit0: X2G REDIR�����Ƿ�ʹ��ʶ���㷨; */
                                                    /* bit1: X2G reselect�����Ƿ�ʹ��ʶ���㷨; */
                                                    /* bit2: X2G CCO�����Ƿ�ʹ��ʶ���㷨; */
                                                    /* bit3: GSM  SPEC��/GOOS�������Ƿ�ʹ��ʶ���㷨; */
                                                    /* bit4: GSM HISTORY��/GSM FAST�������Ƿ�ʹ��ʶ���㷨; */
                                                    /* bit5~bit15: Ԥ�� */
    VOS_UINT16      ucReserve1;                 /* �����ֶ� */
    VOS_UINT16      usFeatureSetEnableBitmap;   /* ʹ�ܵ�α��վ������BITMAP: bit (n)=1��ʾ��n������������Ч��; */
    VOS_UINT16      usReserve2;                 /* �����ֶ� */
    VOS_UINT16      usPseudBTSFeatureSet0;      /* ������0,ÿ��bit����һ������,��bitΪ1ʱ��ʾ���������������������:
                                                    bit0���� RX_ACCESS_MIN=0; 
                                                    bit1 ���� CCCH-CONF='001'ʱ,BS-AG-BLKS-RES=2; 
                                                    bit2 ���� ��֧��GPRS; 
                                                    bit3 ����CRO���� 60;
                                                    bit4 ����MCCΪ460;
                                                    bit5~bit15Ԥ�� */
    VOS_UINT16      usPseudBTSFeatureSet1;      /* �����ֶ�*/
    VOS_UINT16      usPseudBTSFeatureSet2;      /* �����ֶ�*/
    VOS_UINT16      usPseudBTSFeatureSet3;      /* �����ֶ�*/
    VOS_UINT16      usPseudBTSFeatureSet4;      /* �����ֶ�*/
    VOS_UINT16      usPseudBTSFeatureSet5;      /* �����ֶ�*/
    VOS_UINT16      usPseudBTSFeatureSet6;      /* �����ֶ�*/
    VOS_UINT16      usPseudBTSFeatureSet7;      /* �����ֶ�*/
} NVIM_GAS_PSEUD_BTS_IDENT_CUSTOMIZE_CFG_STRU;
/* Added by p00166345 for DTS2015052601104(α��վʶ��), 2015-08-02, end */

/*****************************************************************************
 �� �� ��  : NVIM_GAS_NETWORK_SEARCH_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : ������������NV
 �޸���ʷ  :
  1.��  ��   : 2015��9��14��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulHistoryFreqEnableBitmap;                          /* ��ʷƵ����������ʹ��bitλ */
    VOS_UINT32              ulOperateFreqEnableBitmap;                          /* ��Ӫ�̶���Ƶ����������ʹ��bitλ */
    VOS_UINT32              ulFullListEnableBitmap;                             /* ȫƵ����������ʹ��bitλ */
    VOS_UINT32              ulHistoryFilterSrchedFreqEnableBitmap;              /* ��ʷƵ���������̹���������Ƶ�㹦��ʹ�� bitλ */
    VOS_UINT32              ulOperateFilterSrchedFreqEnableBitmap;              /* ��Ӫ�̶���Ƶ���������̹���������Ƶ�㹦��ʹ�� bitλ */
    VOS_UINT32              ulFullListFilterSrchedFreqEnableBitmap;             /* ȫƵ��Ƶ���������̹���������Ƶ�㹦��ʹ�� bitλ */
    VOS_UINT32              ulIgnoreLowPrioJudgeEnableBitmap;                   /* �����ֵ����ȼ�����ʹ��bitλ */
    VOS_UINT32              ulCloudFreqEnableBitmap;                            /* �ƶ˶���Ƶ����������ʹ��bitλ */
    VOS_UINT32              ulHistoryFreqBandSrchEnableBitmap;                  /* ��ʷƵ������Ƶ����������ʹ��λ */
    VOS_UINT32              ulPresetFreqBandSrchEnableBitmap;                   /* Ԥ��Ƶ������Ƶ����������ʹ��λ */
    VOS_UINT32              ulCloudBandEnableBitmap;                            /* �ƶ˶���Ƶ����������ʹ��bitλ */
    VOS_UINT32              ulCloudFreqFilterSrchedFreqEnableBitmap;            /* �ƶ�Ƶ���������̹���������Ƶ�㹦��ʹ�� bitλ */
    VOS_UINT32              ulReserved1;                                        /* ����λ */
    VOS_UINT32              ulReserved2;                                        /* ����λ */
    VOS_UINT32              ulReserved3;                                        /* ����λ */
    VOS_UINT32              ulReserved4;                                        /* ����λ */
    VOS_UINT32              ulReserved5;                                        /* ����λ */
}NVIM_GSM_NETWORK_SEARCH_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 �� �� ��  : NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_STRU
 �ṹ˵��  : GSM��Ӫ�̶��Ƶ�Ƶ�㷶Χ�ṹ
 �޸���ʷ  :
  1.��  ��   : 2015��8��28��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreqBegin;                            /* ��ʼƵ�� */
    VOS_UINT16                          usFreqEnd;                              /* ��ֹƵ�� */
    NVIM_BAND_IND_ENUM_UINT8            enBand;                                 /* BANDָʾ */
    VOS_UINT8                           ucRsv1;                                 /* ����λ */
    VOS_UINT8                           ucRsv2;                                 /* ����λ */
    VOS_UINT8                           ucRsv3;                                 /* ����λ */
}NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_STRU;

/*****************************************************************************
 �� �� ��  : NVIM_GSM_OPERATE_CUSTOMIZE_DISCRETE_STRU
 �ṹ˵��  : GSM��Ӫ�̶��Ƶ�GSM��ɢƵ��ṹ
 �޸���ʷ  :
  1.��  ��   : 2015��9��1��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFreq;                                 /* Ƶ��� */
    NVIM_BAND_IND_ENUM_UINT8            enBand;                                 /* BANDָʾ */
    VOS_UINT8                           ucRsv1;                                 /* ����λ */
}NVIM_GSM_OPERATE_CUSTOMIZE_DISCRETE_STRU;

/*****************************************************************************
 �� �� ��  : NVIM_GSM_OPERATOR_CUSTOMIZE_PLMN_ITEM_STRU
 �ṹ˵��  : ��Ӫ�̶��Ƶ�GSMƵ���б���PLMN��BAND����ʼƵ�㡢��ֹƵ�㡢��ɢƵ��
 �޸���ʷ  :
  1.��  ��   : 2015��8��28��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    NVIM_GAS_PLMN_ID_STRU                       stPlmn;                         /* PLMN�ṹ */
    VOS_UINT8                                   ucRangeCnt;                     /* Ƶ�㷶Χ�ĸ�����������:NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_MAX_CNT */
    VOS_UINT8                                   ucDiscreteCnt;                  /* ��ɢƵ��ĸ�����������:NVIM_GSM_OPERATE_CUSTOMIZE_DESCRETE_FREQ_MAX_CNT */
    VOS_UINT8                                   ucRsv1;                         /* ����λ */
    VOS_UINT8                                   ucRsv2;                         /* ����λ */
    NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_STRU  astGsmOperateCustomFreqRange[NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_RANGE_MAX_CNT];
                                                                                /* Ƶ�㷶Χ�ṹ�б� */
    NVIM_GSM_OPERATE_CUSTOMIZE_DISCRETE_STRU    astGsmOperateCustomDiscrete[NVIM_GSM_OPERATE_CUSTOMIZE_DESCRETE_FREQ_MAX_CNT];
                                                                                /* ��ɢƵ��ṹ�б� */
    VOS_UINT8                                   ucRsv3;                         /* ����λ */
    VOS_UINT8                                   ucRsv4;                         /* ����λ */
    VOS_UINT16                                  usRsv1;                         /* ����λ */
    VOS_UINT32                                  ulRsv1;                         /* ����λ */
}NVIM_GSM_OPERATOR_CUSTOMIZE_PLMN_ITEM_STRU;

/*****************************************************************************
 �� �� ��  : NVIM_GSM_OPERATOR_CUSTOMIZE_FREQ_CFG_STRU
 �ṹ˵��  : ��Ӫ�̶��Ƶ�GSMƵ���б��NV�ṹ
 �޸���ʷ  :
  1.��  ��   : 2015��8��28��
    ��  ��   : s00184266
    �޸����� : �����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                                   ucPlmnCnt;                      /* ��Ӫ�̶��Ƶ�PLMN�б������������:NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_PLMN_MAX_CNT */
    VOS_UINT8                                   ucRsv1;                         /* ����λ */
    VOS_UINT8                                   ucRsv2;                         /* ����λ */
    VOS_UINT8                                   ucRsv3;                         /* ����λ */
    NVIM_GSM_OPERATOR_CUSTOMIZE_PLMN_ITEM_STRU  astGsmOperatorCustomPlmnItem[NVIM_GSM_OPERATE_CUSTOMIZE_FREQ_PLMN_MAX_CNT];   
                                                                                /* ���Ƶ�PLMN�б� */
}NVIM_GSM_OPERATOR_CUSTOMIZE_FREQ_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : en_NV_Item_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG �ṹ��GSM�������������������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWaitFirstUsableMask;          /* ����ָ���ȴ���һС�������� */
    VOS_UINT16                          usWaitFirstTimerLen;            /* �ȴ���һС����ʱ�����ȣ���λ:ms */

    VOS_INT16                           sSameLaiThreshold;              /* ����ѡ��ͬһ��LAIƵ���RSSI���� */
    VOS_UINT32                          ulSameLaiUsableMask;            /* ����ָ������ѡ��ͬһ��LAI������ */
    VOS_UINT16                          usSameLaiTimerLen;              /* �ȴ�ͬһ��LAIС����ʱ�����ȣ���λ:ms */
    VOS_UINT8                           ucStoreSameLaiFlag;             /* ��ʷƵ��׶��Ƿ�����ѡ��ͬһ��LAIƵ�� */
    VOS_UINT8                           ucFullSameLaiFlag;              /* ȫƵ�ν׶��Ƿ�����ѡ��ͬһ��LAIƵ�� */

    VOS_UINT32                          ulWithSiUsableMask;             /* ����ָ������ѡ���ϵͳ��Ϣ������ */
    VOS_UINT8                           ucStoreWithSiFlag;              /* ��ʷƵ��׶��Ƿ�����ѡ���ϵͳ��ϢƵ�� */
    VOS_UINT8                           ucFullWithSiFlag;               /* ȫƵ�ν׶��Ƿ�����ѡ���ϵͳ��ϢƵ�� */
    VOS_INT16                           sWithSiThreshold;               /* ����ѡ���ϵͳ��ϢƵ���RSSI���� */

    VOS_UINT8                           ucRmvUtranImpactFlg;            /* ɨƵ������Ƿ�ɾ��Utran����Ƶ�� */
    VOS_UINT8                           ucRmvPseudoNCell;               /* ɨƵ������Ƿ�ɾ����Ƶ����Ƶ�� */
    VOS_UINT8                           ucAutoAnycellCamp;              /* ָ����SUITABLEפ��ʧ�ܺ��Ƿ���������ANYCELLפ�� */
    VOS_UINT8                           ucMaxArfcnNum;                  /* �������������Ƶ����� */

    VOS_UINT8                           ucFirstTcIgnoreSi2Q;            /* ��һ��TC����ǰ�Ƿ����SI2Quater */
    VOS_UINT8                           ucRmvNoNeedCellFlg;             /* �׶������������Ƿ�ɾ���Ѿ�ȷ�����õ�С�� */
    VOS_UINT8                           ucRmvCellBetterThreshold;       /* �׶�����������ɾ������С��Ҫ���źű�õ����� */
    VOS_UINT8                           ucRsv6;                         /* ����λ */

    VOS_UINT16                          usRsv1;                         /* ����λ */
    VOS_UINT16                          usRsv2;                         /* ����λ */
    VOS_UINT16                          usRsv3;                         /* ����λ */
    VOS_UINT16                          usRsv4;                         /* ����λ */

    VOS_INT16                           sRmvCellLastRxlevThreshold;     /* �׶�����������ɾ������С��Ҫ��Ƶ���б����źŵ����� */
    VOS_INT16                           sRsv2;                          /* ����λ */
    VOS_INT16                           sRsv3;                          /* ����λ */
    VOS_INT16                           sRsv4;                          /* ����λ */

    VOS_UINT32                          ulRsv1;                         /* ����λ */
    VOS_UINT32                          ulRsv2;                         /* ����λ */
    VOS_UINT32                          ulRsv3;                         /* ����λ */
    VOS_UINT32                          ulRsv4;                         /* ����λ */

}NVIM_GSM_PARALLEL_SEARCH_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 �� �� ��  : NVIM_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST_STRU
 �ṹ˵��  : en_NV_Item_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST NV�ṹ
             L2G �ض��������,��������ָ��Ƶ��ʱʹ����ʷƵ����������
 �޸���ʷ  :
  1.��  ��   : 2015-10-16
    ��  ��   : p00166345
    �޸����� : �����ɽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCsfbEnableFlg;
    VOS_UINT8                           ucRedirEnableFlg;
    VOS_INT8                            cSpecArfcnPreferThreshold;
    VOS_UINT8                           ucHistoryArfcnRssiReduceValue;
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
}NVIM_GSM_ENABLE_HISTORY_ARFCN_WITH_SPEC_ARFCN_LST_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_RR_CONNECT_FAIL_PUNISH_CFG_STRU
 �ṹ˵��  : RR����ʧ�ܳͷ��Ŀ����Լ���������
 �޸���ʷ  :
  1.��  ��   : 2015��10��21��
    ��  ��   : w00146666
    �޸����� : �����ɽṹ
  2.��  ��   : 2015��12��4��
    ��  ��   : w00146666
    �޸����� : for DTS2015112600361, �����ź�ǿ�ȱ仯�ϻ���ʱ���ϻ�����
*****************************************************************************/
typedef struct
{
    /* ===============�ͷ�����������ص�NV������===================== */
    VOS_UINT8           ucCsAccFailPunishSwitchFlag;        /* �Ƿ���CS�������ʧ�ܳͷ����ƣ�0: �ر�, 1: ������Ĭ��ֵΪ1 */

    VOS_UINT8           ucPsAccFailPunishSwitchFlag;        /* �Ƿ���PS�������ʧ�ܳͷ����ƣ�0: �ر�, 1: ������Ĭ��ֵΪ0 */

    VOS_UINT8           ucRrConnFailOptimizeSwtichFlag;     /* �Ƿ�������ʧ���Ż����ƿ��أ�
                                                               0: �ر�, 1: ������Ĭ��ֵΪ1
                                                               �򿪸�NV���
                                                               1.
                                                               �������ʧ��һ�κ��С��ΪFORBIND���ȼ�С����
                                                               �������ʧ�ܳ���һ�����������ͷ����ƣ��ͷ������ڽ���Ϊ��С����BAR���ͷ�ʱ�䳬ʱ����Ϊ�ǵ����ȼ�С����

                                                               2.
                                                               N200ʧ�ܴ����ﵽһ������(NV������)��ִ�б�����ѡ��
                                                               N200ʧ�ܴﵽһ������(NV������), �����ͷ����ƣ��ͷ������ڽ���Ϊ��С����BAR���ͷ�ʱ�䳬ʱ����Ϊ�ǵ����ȼ�С����

                                                               3.
                                                               �����������ɹ��������С������Ϊ�������ʧ�ܼ����б����б���ɾ����С����
                                                               ���²�������ɹ��������С������ΪN200ʧ�ܼ����б����б���ɾ����С����                                                               

                                                               �رո�NV���FORBIND���ȼ�û�е����ͷ����ԣ�Ҳû��N200�ͷ�����
                                                               �������ʧ��һ�κ��С��ΪFORBIND���ȼ�С��������3�β���פ����
                                                               */

    /* ===============�������ʧ����ص�NV������===================== */
    VOS_UINT8           ucStartPunishRaFailTimesThreshold;     /* �ڸ�GSMС�����������ʧ�ܴ�������, �ﵽ�ô����Ը�С�������ͷ����� */

    VOS_UINT8           ucRssiOffset;                         /* ��ʷ�ź�ǿ�ȵ������ޣ�С���ź�ǿ���������޴ﵽ�����޽���С����Bar�б���ɾ�� */


    /* ===============N200��ص�NV������============================== */
    VOS_UINT8           ucN200FailPunishSwitchFlag;             /* �Ƿ���N200ʧ�ܳͷ����ƣ�0: �ر�, 1: ������Ĭ��ֵΪ1 */

    VOS_UINT8           ucStartReselN200FailTimesThreshold;     /* �ڸ�GSMС����N200ʧ�ܴ�������, �ﵽ�ô���������������ѡ */

    VOS_UINT8           ucStartPunishN200FailTimesThreshold;    /* �ڸ�GSMС����N200ʧ�ܴ�������, �ﵽ�ô����Ը�С�������ͷ����� */
    
    VOS_INT16           sN200FailRssiThreshold;                 /* �ڸ�GSMС����N200ʧ��RSSI���ޣ���λ:dBm  */

    /* ===============�ͷ�ʱ����ص�NV������============================== */
    VOS_UINT16          usInitialForbidTimeLen;                /* ����ʧ�ܵ�һ�εĳͷ�ʱ�䣬��λ:�� */

    VOS_UINT16          usMaxForbidTimeLen;                    /* ����ʧ�ܵ�С�������ͷ�ʱ������λ:�� */

    VOS_INT16           sRssiHighThresh;                      /* ��λ:dBm, ����ͷ��б��С������ź�ǿ�ȳ�����ֵ����С���ӳͷ��б����Ƴ����������ź�ǿ�ȱ仯 */

    VOS_UINT32          ulForbidCellMaxReServeTimeLen;        /* ForbidС���ڳͷ��б��е������ʱ������λ:�� */
    
    VOS_UINT32          ulRsv4;                              /* ����λ */
    VOS_UINT32          ulRsv5;                              /* ����λ */
    VOS_UINT32          ulRsv6;                              /* ����λ */
    VOS_UINT32          ulRsv7;                              /* ����λ */

}NVIM_GAS_RR_CONNECT_FAIL_PUNISH_CFG_STRU;


/*****************************************************************************
 �ṹ��    : NVIM_GSM_PING_PONG_HO_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : en_NV_Item_GSM_PING_PONG_HO_CUSTOMIZE_CFG �ṹ,GSM ƹ���л����������������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSwitchFlag;                   /* ���Կ��� */
    VOS_UINT8                           ucHoTimeThreshold;              /* ͳ�Ʒ�Χ�ڵ�С��ƽ��פ��ʱ������, �����Ƽ�30s */
    VOS_UINT8                           ucBadCellTimeScale;             /* ��С��ƽ��ʱ����������, ��λ: 0.1, �����Ƽ� 20 */
    VOS_UINT8                           ucGoodQualityThreshold;         /* �ź��������ж�����.������. ��λ: ǧ��֮һ, �����Ƽ�ֵΪ5 */
    VOS_UINT8                           ucGoodQualityCntThreshold;      /* �ź������õ�ͳ�ƴ�������, �����Ƽ�ֵ 3 */
    VOS_UINT8                           ucNCellRptReduceValue;          /* �Ż���Чʱ,�����ϱ�������, ��λ dB, �����Ƽ�ֵΪ20 */
    VOS_UINT8                           ucWatchHoTimes;                 /* �л�����, �����Ƽ�ֵΪ 4 */
    VOS_UINT8                           aucRsv1;                        /* ����λ */
    VOS_UINT16                          ausRsv1;
    VOS_UINT16                          ausRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT8                           aucRsv4;
    VOS_UINT8                           aucRsv5;
    VOS_UINT8                           aucRsv6;
}NVIM_GSM_PING_PONG_HO_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 �� �� ��  : NVIM_GSM_LTE_MEASURE_CFG_STRU
 �ṹ˵��  : GSM����LTE����NV
 �޸���ʷ  :
  1.��  ��   : 2015��12��7��
    ��  ��   : s00184266
    �޸����� : dts2015100803984,�����ɽṹ

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucDistLteAcsTypeEnable;         /* ʹ������LTE��ʽ���в����Ŀ��� */
    VOS_UINT8                           aucRsv1;                        /* ����λ */
    VOS_UINT8                           aucRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT16                          ausRsv1;
    VOS_UINT16                          ausRsv2;
}NVIM_GSM_LTE_MEASURE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG_STRU
 �ṹ˵��  : en_NV_Item_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG �ṹ,��GSM SUB���������ʽ���ALPHA�˲�, ���жϷ���С���Ƿ���Լ���פ�����������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSecRrPoorRxQualSubThresHold;  /* �ź������������ж�����, ����:ǧ��֮һ, ��ЧֵΪ0~1000, �Ƽ�ֵ: 80, ��������Ϊ8% */
    VOS_UINT16                          usSecRxQualSubAlpha;            /* Alpha����, ����:ǧ��֮һ, ��ЧֵΪ0~1000, �Ƽ�ֵ: 250, ��AlphaΪ0.25 */
    VOS_UINT16                          usSecConSubBerCntThresHold;     /* ����usSecConSubBerCntThresHold�������������ֵ, �ٿ���Poor����, �Ƽ�ֵ: 2, ���������� */
    VOS_UINT8                           ucRsv1;                         /* ����λ */
    VOS_UINT8                           ucRsv2;
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
}NVIM_GSM_SEC_RXQUAL_SUB_ALPHA_FILTERING_CFG_STRU;

#if defined( __PS_WIN32_RECUR__ ) || defined (DMT)
/*****************************************************************************
 �� �� ��  : NVIM_GAS_CHR_PC_CFG_STRU
 �ṹ˵��  : 
 �޸���ʷ  :
  1.��  ��   : 2015��12��28��
    ��  ��   : w00146666
    �޸����� : �����ɽṹ
*****************************************************************************/
typedef struct  
{
    VOS_UINT32  ulPermitedChrAlarmIdCount;

    VOS_UINT16  aucAlarmIds[MAX_CHR_ALARM_ID_NUM];
    
}NVIM_GAS_CHR_PC_CFG_STRU;
#endif

/*****************************************************************************
 �ṹ��    : NVIM_Item_GAS_SAME_LAI_PREFER_CFG_STRU
 �ṹ˵��  : en_NV_Item_GAS_SAME_LAI_PREFER_CFG �ṹ, ��������������ѡ����ͬ LAI С��
             ���������.
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucMtSwitchFlag;                 /* ���Կ��� */
    VOS_UINT8                           ucMoSwitchFlag;                 /* ���Կ��� */

    VOS_INT8                            cFirstLevelAddValue;           /* ��һ�����ȼ�����ͬ LAI С������ʱ����������ֵ */
    VOS_INT8                            cFirstLevelThreshold;          /* ��һ�����ȼ����� */

    VOS_INT8                            cSecLevelAddValue;             /* �ڶ������ȼ�����ͬ LAI С������ʱ����������ֵ */
    VOS_INT8                            cSecLevelThreshold;            /* �ڶ������ȼ����� */
    VOS_UINT16                          usValidTimeLen;                 /* ��Чʱ��, ��λ:���� */
    VOS_UINT8                           aucRsv1;                        /* ����λ */
	VOS_UINT8                           aucRsv2;                        /* ����λ */
    VOS_UINT8                           aucRsv3;                        /* ����λ */
    VOS_UINT8                           aucRsv4;                        /* ����λ */
}NVIM_Item_GAS_SAME_LAI_PREFER_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_HO_CUSTOMIZE_CFG_STRU
 �ṹ˵��  : en_NV_Item_GSM_HO_CUSTOMIZE_CFG �ṹ,GSM �л����������������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucChanModeRptIndication;        /* �����ŵ��л��л�����,�и� MM �ϱ� GAS_RR_CHAN_IND ��ʱ�� */
    VOS_UINT8                           aucRsv1;
    VOS_UINT16                          ausRsv1;
    VOS_UINT8                           aucRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT8                           aucRsv4;
    VOS_UINT8                           aucRsv5;
}NVIM_GSM_HO_CUSTOMIZE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GSM_PMR_CFG_STRU
 �ṹ˵��  : en_NV_Item_GSM_PMR_CFG �ṹ,GSM PMR��ض���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucNcReportPeriodIMin;           /* ����̬ PMR ������Сֵ */
    VOS_UINT8                           aucRsv1;
    VOS_UINT16                          ausRsv1;
    VOS_UINT8                           aucRsv2;
    VOS_UINT8                           aucRsv3;
    VOS_UINT8                           aucRsv4;
    VOS_UINT8                           aucRsv5;
}NVIM_GSM_PMR_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_GSM_ACTIVE_CELL_RESELECT_CFG_STRU
 �ṹ˵��  : en_NV_Item_GAS_GSM_CELL_RESELECT_CFG �ṹ, GAS ��G2G��ѡ�����������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucC2ReselPartialReadFlg;        /* ������ѡ�Ƿ���Ҫ���ֶ�
                                                                           1: ��Ҫ;
                                                                           0: ����Ҫ */
    VOS_UINT8                           ucRsv1;
    VOS_UINT16                          usHistorySi3ValidTimeLen;       /* פ���׶���ʷSI3��Чʱ��. ��λ: s */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;

    VOS_UINT8                           ucC2ReselPunishSwitchFlg;       /* ������ѡ�����ͷ������Ƿ���
                                                                           1: ����;
                                                                           0: �ر� */
    VOS_UINT8                           ucRsv6;
    VOS_INT16                           sScellRssiThreshold;            /* ����С������������ֵ����λ: dBm */
    VOS_UINT16                          usScellPchBerThreshold;         /* ����С��PCH������Alpha�˲���ֵ����λ: %��ǧ��֮һ���� */
    VOS_UINT16                          usScellPchBerAlpha;             /* ����С��PCH������Alpha�˲���Alpha���ӣ���λ: %��ǧ��֮һ���� */
    VOS_UINT16                          usForbiddenCellPunishTimeLen;   /* Forbidden С����ѡ�ͷ�ʱ����������ʱ������С���������λ: s */
    VOS_UINT16                          usForbiddenCellPunishStep;      /* ������С��Ϊ��С��ʱ�����������гͷ�����ֵ����λ: dBm */
    VOS_UINT8                           ucScellRaSuccStep;              /* ����С��RA�ɹ�һ�β���ֵ */
    VOS_UINT8                           ucScellRaFailStep;              /* ����С��RAʧ��һ�β���ֵ */
    VOS_UINT8                           ucRsv9;
    VOS_UINT8                           ucRsv10;  
    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
}NVIM_GAS_GSM_ACTIVE_CELL_RESELECT_CFG_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_GAS_GSM_PASSIVE_RESELECT_OPTIMIZE_CFG_STRU
 �ṹ˵��  : en_NV_Item_GAS_GSM_PASSIVE_RESELECT_OPTIMIZE_CFG �ṹ������ָ�ɱ����Ż���T3166/T3168��ʱ�Ż�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucImmAssRejOptSwitchFlg;            /* ���Կ��� */
    VOS_UINT8                           ucImmAssRejCntThreshold;            /* �������ָ�ɱ��ܴ��� */
    VOS_UINT8                           ucImmAssRejWaitIndThreshold;        /* �������ָ�ɱ���ʱ������λ: s */

    VOS_UINT8                           ucCcAbnormalRelCnt;                 /* ����ʧ�ܳ���������ʱ���𱻶���ѡ, 0xFF ��ʾ�رն�Ӧ���� */

    VOS_UINT8                           ucT3166T3168ExpiredOptSwitchFlg;    /* ���Կ��� */
    VOS_UINT8                           ucT3166T3168ExpiredCntThreshold;    /* T3166/T3168��ʱ�������ʱ���� */
    VOS_UINT16                          usT3166T3168ExpiredPunishTimeLen;   /* T3166/T3168��ʱ�ͷ���ʱ��ʱ������λ: ms */

    VOS_UINT8                           ucRsv1;                             /* ����λ */
    VOS_UINT8                           ucRsv2;
    VOS_UINT8                           ucRsv3;
    VOS_UINT8                           ucRsv4;
    VOS_UINT8                           ucRsv5;
    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;

    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usRsv2;
}NVIM_GAS_GSM_PASSIVE_RESELECT_OPTIMIZE_CFG_STRU;

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

#endif /* end of NasNvInterface.h */
