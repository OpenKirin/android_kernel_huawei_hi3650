

/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : OmApi.h
  �� �� ��   : ����
  ��    ��   : ���� 47350
  ��������   : 2011��9��29��
  ����޸�   :
  ��������   : OM����ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��1��7��
    ��    ��   : ���� 47350
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OMAPI_H__
#define __OMAPI_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "phyoaminterface.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum SPY_DATA_DOWNGRADE_RESULT_ENUM
{
    SPY_DATA_DOWNGRADE_CONTINUE              = 0,
    SPY_DATA_DOWNGRADE_FINISH                = 1,
    SPY_DATA_DOWNGRADE_RESULT_BUTT
};
typedef VOS_UINT32 SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32;

enum SPY_DATA_UPGRADE_RESULT_ENUM
{
    SPY_DATA_UPGRADE_CONTINUE              = 0,
    SPY_DATA_UPGRADE_FINISH                = 1,
    SPY_DATA_UPGRADE_RESULT_BUTT
};
typedef VOS_UINT32 SPY_DATA_UPGRADE_RESULT_ENUM_UINT32;

enum SPY_TEMPROTECT_SWITCH_STATE_ENUM
{
    SPY_TEMPROTECT_SWITCH_OFF              = 0,
    SPY_TEMPROTECT_SWITCH_ON               = 1,
    SPY_TEMPROTECT_SWITCHT_BUTT
};
typedef VOS_UINT32 SPY_TEMPROTECT_SWITCH_STATE_ENUM_UINT32;


/*****************************************************************************
 ö����    : TEMPPRT_AT_MSG_ID_ENUM
 �ṹ˵��  : SPY��AT��Ϣ�ӿ�ö��
*****************************************************************************/
enum TEMPPRT_AT_MSG_ID_ENUM
{
    /* SPY -> AT */
    ID_TEMPPRT_AT_EVENT_IND = 0 ,   /* _H2ASN_MsgChoice TEMP_PROTECT_EVENT_AT_IND_STRU */

    ID_TEMPPRT_STATUS_AT_EVENT_IND, /* _H2ASN_MsgChoice TEMP_PROTECT_EVENT_AT_IND_STRU */

    ID_TEMPPRT_AT_MSG_ID_BUTT

};
typedef VOS_UINT32 TEMPPRT_AT_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : SLEEP_SYSTEM_STATE_ENUM
 ö��˵��  : ϵͳ״̬

  1.��    ��   : 2012��07��31��
    ��    ��   : g47350
    �޸�����   : V900R001 MSP��ֺͿ�ά�ɲ���Ŀ����
*****************************************************************************/
enum SLEEP_SYSTEM_STATE_ENUM
{
    SLEEP_NORMAL_STATE = 0,                             /* ����״̬ */
    SLEEP_MASTER_TEMP_LP_STATE,                         /* ��ģ�͹���״̬(��̬) */
    SLEEP_MASTER_LP_STATE,                              /* ��ģ�͹���״̬ */
    SLEEP_TEMP_NORMAL_STATE,                            /* ����״̬(��̬) */
    SLEEP_SLAVE_LP_STATE,                               /* ��ģ�͹���״̬ */
    SLEEP_STATE_BUTT
};
typedef VOS_UINT32 SLEEP_SYSTEM_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����    : SLEEP_BBE16_SYSTEM_STATE_ENUM
 ö��˵��  : ϵͳ״̬

  1.��    ��   : 2015��08��27��
    ��    ��   : s00207770
    �޸�����   : Cģ�͹�������
*****************************************************************************/
enum SLEEP_BBE16_SYSTEM_STATE_ENUM
{
    SLEEP_BBE16_NORMAL_STATE = 0,                       /* ����״̬ */
    SLEEP_BBE16_MASTER_HALT_STATE,                      /* ��ģHALT״̬ */
    SLEEP_BBE16_MASTER_LP_STATE,                        /* ��ģ�͹���״̬ */
    SLEEP_BBE16_MASTER_WAKE_STATE,                      /* ��ģ����״̬ */
    SLEEP_BBE16_MASTER_TEMP_NORMAL_STATE,               /* ��ģ����״̬(��̬) */
    SLEEP_BBE16_SLAVE_HALT_STATE,                       /* ��ģHALT״̬ */
    SLEEP_BBE16_SLAVE_LP_STATE,                         /* ��ģ�͹���״̬ */
    SLEEP_BBE16_SLAVE_WAKE_STATE,                       /* ��ģ����״̬ */
    SLEEP_BBE16_SLAVE_TEMP_NORMAL_STATE,                /* ��ģ����״̬(��̬) */
    SLEEP_BBE16_STATE_BUTT
};
typedef VOS_UINT32 SLEEP_BBE16_SYSTEM_STATE_ENUM_UINT32;

/*****************************************************************************
 ö����    :SLEEP_MSG_ID_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  :SLEEP��ϢIDö��
*****************************************************************************/
enum SLEEP_MSG_ID_ENUM
{
    ID_SLEEP_NOTIFY_STATUS_IND = 0,                         /* �����ģ�͹��ģ�֪ͨע��PID */

    ID_SLEEP_MSG_ID_BUTT
};
typedef VOS_UINT32 SLEEP_MSG_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    :SLEEP_LOWPOWER_STATE_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  :�͹��Ŀ���״̬
*****************************************************************************/
enum SLEEP_LOWPOWER_STATE_ENUM
{
    SLEEP_LOWPOWER_STATE_OFF = 0,
    SLEEP_LOWPOWER_STATE_ON,
    SLEEP_LOWPOWER_STATE_BUTT
};
typedef VOS_UINT32 SLEEP_LOWPOWER_STATE_ENUM_UINT32;

enum OM_PCV_CHANNEL_EUNM
{
    OM_PCV_CHANNEL_OPEN = 0,
    OM_PCV_CHANNEL_CLOSE,
    OM_PCV_CHANNEL_SWITCH,
    OM_PCV_CHANNEL_BUTT
};

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
typedef SPY_DATA_DOWNGRADE_RESULT_ENUM_UINT32 (*SPY_DOWNGRADE_PROC_FUNC)(VOS_VOID);
typedef SPY_DATA_UPGRADE_RESULT_ENUM_UINT32 (*SPY_UPGRADE_PROC_FUNC)(VOS_VOID);
typedef VOS_VOID (*SPY_RESTORE_PROC_FUNC)(VOS_VOID);

/*****************************************************************************
 �ṹ��    : TEMP_PROTECT_EVENT_AT_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : SPY��AT�ϱ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                  ulMsgId;
    VOS_UINT32                  ulTempProtectEvent;
    VOS_UINT32                  ulTempProtectParam;
} TEMP_PROTECT_EVENT_AT_IND_STRU;

/*****************************************************************************
 �ṹ��    : SLEEP_NOTIFY_STATUS_MSG_STRU
 Э����  : ��
 �ṹ˵��  : SLEEP�����ģ�͹��ģ���ע��PID����״̬֪ͨ

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : L00256032
    �޸�����   : V8R1 LowPower&NV_Expand��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                          /* ulSenderPid: WUEPS_PID_SLEEP */
    SLEEP_MSG_ID_ENUM_UINT32            enMsgId;
    VOS_RATMODE_ENUM_UINT32             enRatMode;
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enState;            /* Ŀǰ�̶���дSLEEP_SLAVE_LP_STATE */
    SLEEP_LOWPOWER_STATE_ENUM_UINT32    enLPState;
} SLEEP_NOTIFY_STATUS_MSG_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_VOID Spy_DownGradeRegister(SPY_DOWNGRADE_PROC_FUNC pFnDowngradeProcFunc);

extern VOS_VOID Spy_UpGradeRegister(SPY_UPGRADE_PROC_FUNC pFnUpgradeProcFunc);

extern VOS_VOID Spy_RestoreRegister(SPY_RESTORE_PROC_FUNC pFnRestoreProcFunc);

extern VOS_VOID GUSLEEP_MasterAwakeSlave(VOS_VOID);

extern VOS_VOID TLSLEEP_MasterAwakeSlave(VOS_VOID);

extern VOS_UINT32 SLEEP_NotifyStateReg(VOS_UINT32 ulRcvPid, VOS_RATMODE_ENUM_UINT32 enRatMode);

extern VOS_UINT32 SLEEP_NotifyStateUnreg(VOS_UINT32 ulRcvPid);

extern VOS_VOID OM_SetDrxTimerWakeSrcAllVote(MODEM_ID_ENUM_UINT16 enModem);

extern VOS_VOID OM_SetDrxTimerWakeSrc(MODEM_ID_ENUM_UINT16 enModem, VOS_RATMODE_ENUM_UINT32 enMode);

extern VOS_VOID OM_DelDrxTimerWakeSrc(MODEM_ID_ENUM_UINT16 enModem, VOS_RATMODE_ENUM_UINT32 enMode);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of OmApi.h */
