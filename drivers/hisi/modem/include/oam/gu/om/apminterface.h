

/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: APMInterface.h                                                  */
/*                                                                           */
/*    Author: Jiang KaiBo                                                    */
/*            Xu Cheng                                                       */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2008-02                                                             */
/*                                                                           */
/* Description: process data of APM mailbox                                  */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date:                                                                  */
/*    Author:                                                                */
/*    Modification: Create this file                                         */
/*                                                                           */
/*                                                                           */
/*****************************************************************************/


#ifndef  _APM_INTERFACE_H
#define  _APM_INTERFACE_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#include "vos.h"
#include "phyoaminterface.h"

/*---------------------------------------------*
 * �����궨��                                  *
 *---------------------------------------------*/

/*����DSP NV��ش���*/
#define SHPA_TMR_LOAD_PHY_INTERVAL          5000

#define DSP_DATA_WRITE_OK                   0x5555AAAA
#define DSP_DATA_READ_OK                    0x5A5A5A5A

/*����DSP���*/
#define CPHY_DSP_LOAD_SUCCESS               0
#define CPHY_DSP_LOAD_FAILURE               1
#define CPHY_DSP_LOAD_TIMEOUT               2

/* �ȴ����ر�־λ��Ч */
#define SHPA_PROTECT_DELAY_COUNT            (30)

/* ��ֹдDSPԽ��ı����� */
#define COMM_EXT_DATA_MEM_PROTECT_BIT_1     0xAAAA
#define COMM_EXT_DATA_MEM_PROTECT_BIT_2     0x5555
#define COMM_EXT_DATA_MEM_PROTECT_BIT_3     0x5A5A
#define COMM_EXT_DATA_MEM_PROTECT_BIT_4     0x5A5A
#define COMM_EXT_DATA_MEM_PROTECT_BIT_5     0xA5A5
#define COMM_EXT_DATA_MEM_PROTECT_BIT_6     0xA5A5
#define COMM_EXT_DATA_MEM_PROTECT_BIT_7     0x5555
#define COMM_EXT_DATA_MEM_PROTECT_BIT_8     0xAAAA

#define SHPA_LDF_DELAY_TIME                 (340)   /* ������������ʱ��Ҫ�ӳٵ�ʱ�� 10ms,����NMI �����Ϸ���DTCM��ARM���� */

#define SHPA_LDF_DELAY_1S_TIME              (34)   /* ������������ʱ��Ҫ�ӳٵ�ʱ�� 1ms,����NMI �����Ϸ���DTCM��ARM���� */

#define SHPA_LDF_LOAD_PHY_DELAY_TIME        (400)   /* ����DSPʱ����DSP��Ҫ��ʱ��ʱ�� 400ms */

#ifdef  __LDF_FUNCTION__
#define SHPA_Ldf_Check()                    UPHY_MNTN_PhyLdfFileSaving()
#endif

enum DSP_CONFIG_ERROR_EUNM
{
    DSP_NVREAD_NOERROR = 0,
    DSP_BOOTINFO_MEMERR,
    DSP_NVREAD_LENERR,
    DSP_NVREAD_READNVERR,
    DSP_NVREAD_ALLOCMEMERR,
    DSP_NVREAD_TOTALLENERR,
    DSP_LOAD_STATIC_ERROR,
    DSP_GET_COMMON_INFO_ERROR,
    DSP_CONFIG_INFO_TOO_LONG,
    DSP_ACTIVE_TIME_OUT,
    DSP_CONFIG_ERROR_BUTT
};
typedef VOS_UINT32 DSP_CONFIG_ERROR_EUNM_UINT32;

enum APM_CFG_STATE_EUNM
{
    APM_INIT_STATE   = 0,
    APM_SENDED_MSG,
    APM_RECEIVED_MSG,
    APM_CFG_STATE_BUTT
};
typedef VOS_UINT32 APM_CFG_STATE_EUNM_UINT32;

/*****************************************************************************
 ö����    :DUALMODEM_SCENE_TYPE_ENUM_UINT16
 Э����  :
 ö��˵��  :ͨ�����CCPU DDR��Ƶͨ������
*****************************************************************************/
enum
{
   DUALMODEM_SCENCE_GSM,
   DUALMODEM_SCENCE_WCDMA,
   DUALMODEM_SCENCE_APS,
   DUALMODEM_SCENCE_TL,
   DUALMODEM_SCENCE_GUDRX,
   DUALMODEM_SCENCE_BUTT,
};
typedef VOS_UINT16 DUALMODEM_SCENE_TYPE_ENUM_UINT16;

typedef struct
{
    VOS_UINT32                      ulDspNVConfigAddr;          /*��DSP��ȡ�ĵ�ǰDSP NV�����öε�ַ*/
    VOS_UINT32                      ulDspNvTotalLen;            /*��Ҫ���ø�DSP��NV��ĳ���*/
    VOS_UINT16                      *pusNVData;                 /*����NV���ݵ��ڴ�ռ�*/
    DSP_CONFIG_ERROR_EUNM_UINT32    enErrorCode;                /*��ǰ����DSP����ԭ��ֵ*/
    APM_CFG_STATE_EUNM_UINT32       enActiveState;
    APM_CFG_STATE_EUNM_UINT32       enLoadState;
    VOS_UINT32                      ulActiveResult;
    VOS_UINT32                      ulLoadResult;
    VOS_UINT32                      ulActiveSmPResult;          /*�ȴ�Active�ź����Ľ��*/
    VOS_UINT32                      ulLoadSmPResult;            /*�ȴ�Load�ź����Ľ��*/
    VOS_UINT32                      ulGetNvLenErrId;            /*��ȡNV���ȴ����NV ID��*/
    VOS_UINT32                      ulGetNvErrId;               /*��ȡNV���ݴ����NV ID��*/
    /*��ز�����ʱ�����¼*/
    VOS_UINT32                      ulGetNvLenSlice;            /*��ȡNV���ݵ�ʱ���*/
    VOS_UINT32                      ulRecNVReqSlice;            /*�յ�DSP NV����ʱ���*/
    VOS_UINT32                      ulConfigNVSlice;            /*����dSP NV��ʱ��*/
    VOS_UINT32                      ulDSPActiveSlice;           /*Active DSP��ʱ���*/
    VOS_UINT32                      ulDSPActCnfSlice;           /*�յ�Active�ظ���ʱ���*/
    VOS_UINT32                      ulDSPLoadSlice;             /*Load DSP��ʱ���*/
    VOS_UINT32                      ulDSPLoadCnfSlice;          /*�յ�Load�ظ���ʱ���*/
}DSP_CONFIG_CTRL_STRU;

/*����OM��͸����Ϣ*/
typedef struct
{
    VOS_MSG_HEADER                       /* ����Ϣͷ���TOOL_ID��PS��PID,��֤��Ϣ��ת������Ӧ��PSģ�� */
    VOS_UINT16      usTransPrimId;       /* �̶���д0x5001*/
    VOS_UINT16      usReserve;
    VOS_UINT8       ucFuncType;          /*���ݲ�ѯ04,�տ���Ϣ�ϱ�:02*/
    VOS_UINT8       ucReserve;
    VOS_UINT16      usAppLength;         /*��һ���ֽڵ���β�ĳ���*/
    VOS_UINT32      ulSn;                /* �ϱ���Ϣ�����к� */
    VOS_UINT32      ulTimeStamp;         /*��Ϣ��ʱ������ǰ��SOC Tickֵ*/
    VOS_UINT16      usPrimId;            /* ԭ��ID*/
    VOS_UINT16      usToolsId;           /* ����ID */
    VOS_UINT8       aucData[4];
}PS_APM_OM_TRANS_IND_STRU;

typedef struct
{
    VOS_UINT16 *pusArray;
    VOS_UINT32 ulNum;
}APM_RF_NV_INFO_STRU;

typedef struct
{
    VOS_UINT32 ulDSPPowerDownState;
    VOS_UINT32 ulReserved[7];
}LDF_EXT_INFO_STRU;

/*---------------------------------------------*
 * ��������                                    *
 *---------------------------------------------*/

extern VOS_SEM g_aulShpaLoadPhySemaphor[MODEM_ID_BUTT];

extern VOS_SEM g_aulShpaActivePhySemaphor[MODEM_ID_BUTT];

extern VOS_UINT32 g_aulShpaCurSysId[MODEM_ID_BUTT];

extern DSP_CONFIG_CTRL_STRU g_astDspConfigCtrl[MODEM_ID_BUTT];

extern VOS_UINT16 SHPA_LoadPhy( PHY_OAM_SET_WORK_MODE_REQ_STRU  stSetWorkMode );

extern VOS_UINT32 APM_PIDInit( enum VOS_INIT_PHASE_DEFINE ip );

extern VOS_VOID SHPA_ActivateHw(VOS_VOID);

extern VOS_VOID SHPA_DeactivateHw(VOS_VOID);

extern VOS_UINT32 SHPA_ActiveDSP(VOS_RATMODE_ENUM_UINT32 enRatMode, MODEM_ID_ENUM_UINT16 enModemId);

extern VOS_UINT32 SHPA_ReadWTxPower( VOS_VOID);

extern VOS_UINT32 GHPA_GetRealFN(MODEM_ID_ENUM_UINT16 enModemID);

/*****************************************************************************
 �� �� ��  : DualModem_DDRQosUpdate
 ��������  : CCPUͨ�����DDR��Ƶ�ӿ�
 �������  : MODEM_ID_ENUM_UINT16 enModem                       ��ǰModem Id
             DUALMODEM_SCENE_TYPE_ENUM_UINT16   enSceneType     ͶƱͨ������
             VOS_UINT32 ulValue                                 DDRʵ��ͶƱƵ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��11��
    ��    ��   : s00207770
    �޸�����   : �����ɺ���

*****************************************************************************/
extern VOS_UINT32 DualModem_DDRQosUpdate(MODEM_ID_ENUM_UINT16 enModem, DUALMODEM_SCENE_TYPE_ENUM_UINT16 enSceneType,  VOS_UINT32 ulValue);

#ifdef  __LDF_FUNCTION__
VOS_UINT32 SHPA_Ldf_Hifi_Saving(VOS_VOID);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _APM_INTERFACE_H */

