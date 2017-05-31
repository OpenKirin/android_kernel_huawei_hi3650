

#ifndef __TAFOAMINTERFACE_H__
#define __TAFOAMINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "v_msg.h"
#include "TafAppMma.h"
#include "MnMsgApi.h"
#include "MnClient.h"
#include "omnvinterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define SAR_ANTSTATE_IND                            0x1111

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
#define TAF_STK_CURC_RPT_CFG_MAX_SIZE               (8)
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

#define    COMM_LOG_PORT_USB                CPM_OM_PORT_TYPE_USB
#define    COMM_LOG_PORT_VCOM               CPM_OM_PORT_TYPE_VCOM

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
 ö����    : TAF_OAM_MSG_TYPE_ENUM
 �ṹ˵��  : TAF��OAM��Ϣ�ӿ�ö�٣���ϢIDλ��32λ������16λ��Ч
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����������������Ϣ:
                 TAF_STK_ENVELOPE_CNF
                 TAF_STK_SYS_INFO_IND
                 TAF_STK_SERVICE_STATUS_IND
  2.��    ��   : 2013��7��24��
    ��    ��   : z00161729
    �޸�����   : V9R1 STK�����޸�
*****************************************************************************/
enum TAF_OAM_MSG_TYPE_ENUM
{
    /* SPY/DIAG/OM -> MMA */
    OAM_MMA_PHONE_MODE_SET_REQ          = 0x00,                                 /* _H2ASN_MsgChoice MN_APP_PHONE_MODE_SET_REQ_STRU */
    OAM_MMA_PHONE_LOADDEFAULT_REQ       = 0x01,                                 /* _H2ASN_MsgChoice MN_APP_PHONE_LOADDEFAULT_REQ_STRU */

    /* Deleted by z00161729 for V9R1 STK����, 2013-7-24, begin */
    /* taf��stk������Ϣ��������NasStkInterface.h */
    /* Deleted by z00161729 for V9R1 STK����, 2013-7-24, end */

    /* TAF  -> OAM(VC) ����OAM�������˿ڣ�����ظ���Ϣ */
    TAF_OAM_SET_TRANS_PORT_REQ          = 0x0f,                                 /* _H2ASN_MsgChoice MN_APP_CS_SET_TRANS_PORT_MSG_STRU */

    /* Deleted by z00161729 for V9R1 STK����, 2013-7-24, begin */
    /* taf��stk������Ϣ��������NasStkInterface.h */
    /* Deleted by z00161729 for V9R1 STK����, 2013-7-24, end */

    /* PHONE -> SPY/DIAG/OM OAM_MMA_PHONE_MODE_SET_REQ�Ļظ���Ϣ */
    TAF_OAM_PHONE_EVENT_IND             = 0x11,                                 /* _H2ASN_MsgChoice MN_APP_PHONE_EVENT_INFO_STRU */

    /* PHONE -> SPY/DIAG/OM OAM_MMA_PHONE_LOADDEFAULT_REQ�Ļظ���Ϣ */
    TAF_OAM_PHONE_SET_CNF               = 0x12,                                 /* _H2ASN_MsgChoice MN_APP_PHONE_SET_CNF_STRU */

    TAF_STK_USSD_DCS_DECODE_HOOK        = 0xAAA0,                               /* _H2ASN_MsgChoice SSA_USSD_DCS_DECODE_HOOK_STRU */

    MMA_EVT_OM_SDT_CONNECTED_IND        = 0xAAAA,


    /* OAM->MMA, TRACE ������Ϣ */
    OAM_MMA_TRACE_CONFIG_REQ            = 0xAAAB,

    MMA_OAM_TRACE_CONFIG_CNF,

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-11, begin */
    TAF_OAM_UNSOLICITED_RPT_INFO_IND,                                       /* _H2ASN_MsgChoice TAF_OAM_UNSOLICITED_RPT_INFO_STRU */
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-11, end */

    /* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, begin */
    /* VC  -> OAM ����VCģ����Ҫ�Ҷϵ绰ʱ���쳣��� */
    TAF_OAM_LOG_END_CALL_REQ,                                               /* _H2ASN_MsgChoice TAF_OAM_LOG_END_CALL_REQ_STRU */
    /* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, end */

    /* TAF  -> OAM ��������״̬��Ϣ������ظ���Ϣ */
    TAF_OAM_EMERGENCY_CALL_STATUS_NOTIFY    = 0xBBB0,                               /* _H2ASN_MsgChoice TAF_OAM_EMERGENCY_CALL_STATUS_STRU */

    TAF_OAM_MSG_TYPE_BUTT
};
typedef VOS_UINT32 TAF_OAM_MSG_TYPE_ENUM_UINT32;

/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-5-2, begin */
/*****************************************************************************
 ö����    : TAF_STK_RPT_CMD_INDEX_ENUM
 �ṹ˵��  : �����ϱ�����ö��

  1.��    ��   : 2013��05��02��
    ��    ��   : z00161729
    �޸�����   : ����
*****************************************************************************/
enum TAF_STK_RPT_CMD_INDEX_ENUM
{
    TAF_STK_RPT_CMD_MODE                     = 0,
    TAF_STK_RPT_CMD_RSSI,
    TAF_STK_RPT_CMD_SRVST,
    TAF_STK_RPT_CMD_SIMST,
    TAF_STK_RPT_CMD_TIME,
    TAF_STK_RPT_CMD_SMMEMFULL,
    TAF_STK_RPT_CMD_CTZV,
    TAF_STK_RPT_CMD_DSFLOWRPT,
    TAF_STK_RPT_CMD_ORIG,
    TAF_STK_RPT_CMD_CONF,
    TAF_STK_RPT_CMD_CONN,
    TAF_STK_RPT_CMD_CEND,
    TAF_STK_RPT_CMD_STIN,
    TAF_STK_RPT_CMD_CERSSI,
    TAF_STK_RPT_CMD_ANLEVEL,
    TAF_STK_RPT_CMD_LWCLASH,
    TAF_STK_RPT_CMD_XLEMA,
    TAF_STK_RPT_CMD_ACINFO,
    TAF_STK_RPT_CMD_PLMN,
    TAF_STK_RPT_CMD_CALLSTATE,
    TAF_STK_RPT_CMD_CREG,
    TAF_STK_RPT_CMD_CUSD,
    TAF_STK_RPT_CMD_CSSI,
    TAF_STK_RPT_CMD_CSSU,
    TAF_STK_RPT_CMD_LWURC,
    TAF_STK_RPT_CMD_CUUS1I,
    TAF_STK_RPT_CMD_CUUS1U,
    TAF_STK_RPT_CMD_CGREG,
    TAF_STK_RPT_CMD_CEREG,
    TAF_STK_RPT_CMD_BUTT
};
typedef VOS_UINT8 TAF_STK_RPT_CMD_INDEX_ENUM_UINT8;
/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-5-2, end */


/*****************************************************************************
 �ṹ��    : TAF_APS_USER_CONN_STATUS_ENUM
 �ṹ˵��  : �Ƿ����û������PDP����
 1.��    ��   : 2012��03��13��
   ��    ��   : f00179208
   �޸�����   : ����
*****************************************************************************/
enum TAF_APS_USER_CONN_STATUS_ENUM
{
    TAF_APS_USER_CONN_EXIST,
    TAF_APS_USER_CONN_NOT_EXIST,
    TAF_APS_USER_CONN_BUTT
};
typedef VOS_UINT8 TAF_APS_USER_CONN_STATUS_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : TAF_OAM_SDT_CONNECT_STATUS_ENUM
 �ṹ˵��  : SDT������״̬
 1.��    ��   : 2012��04��20��
   ��    ��   : l00171473
   �޸�����   : ����
*****************************************************************************/
enum TAF_OAM_SDT_CONNECT_STATUS_ENUM
{
    TAF_OAM_SDT_CONNECT_STATUS_CONNECTED,                                       /* SDT�͵��������� */
    TAF_OAM_SDT_CONNECT_STATUS_DISCONNECTED,                                    /* SDT�͵���Ͽ����� */
    TAF_OAM_SDT_CONNECT_STATUS_BUTT
};
typedef VOS_UINT8 TAF_OAM_SDT_CONNECT_STATUS_ENUM_UINT8;

/*****************************************************************************
 �ṹ��    : TAF_OAM_PC_RECUR_CFG_ENUM
 �ṹ˵��  : �Ƿ���NAS��PC�ط���Ϣö��
 1.��    ��   : 2012��04��20��
   ��    ��   : l00171473
   �޸�����   : ����
*****************************************************************************/
enum TAF_OAM_PC_RECUR_CFG_ENUM
{
    TAF_OAM_PC_RECUR_CFG_ENABLE,                                                /* ʹ�ܷ���PC�ط���Ϣ */
    TAF_OAM_PC_RECUR_CFG_DISABLE,                                               /* ȥʹ�ܷ���PC�ط���Ϣ */
    TAF_OAM_PC_RECUR_CFG_BUTT
};
typedef VOS_UINT8 TAF_OAM_PC_RECUR_CFG_ENUM_UINT8;


/*****************************************************************************
 �ṹ��    : TAF_OAM_EMERGENCY_CALL_STATUS_ENUM
 �ṹ˵��  : ��������״̬ö��
 1.��    ��   : 2013��03��28��
   ��    ��   : l00198894
   �޸�����   : ����
*****************************************************************************/
enum TAF_OAM_EMERGENCY_CALL_STATUS_ENUM
{
    TAF_OAM_EMERGENCY_CALL_START,                                               /* ����������� */
    TAF_OAM_EMERGENCY_CALL_END,                                                 /* �������н��� */
    TAF_OAM_EMERGENCY_CALL_STATUS_BUTT
};
typedef VOS_UINT8 TAF_OAM_EMERGENCY_CALL_STATUS_ENUM_UINT8;

/*****************************************************************************
ö����    : OM_HSIC_PORT_STATUS_ENUM
ö��˵��  : OM�˿���HSIC����״̬

  1.��    ��   : 2012��4��4��
    ��    ��   : w00184875
    �޸�����   : V7R1C51 ����������Ŀ����
*****************************************************************************/
enum OM_HSIC_PORT_STATUS_ENUM
{
    OM_HSIC_PORT_STATUS_OFF      = 0,       /* HSIC��GU��OM��δ������ */
    OM_HSIC_PORT_STATUS_ON,                 /* HSIC��GU��OM���ѹ����� */
    OM_HSIC_PORT_STATUS_BUTT
};
typedef VOS_UINT32 OM_HSIC_PORT_STATUS_ENUM_UINT32;

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : MN_APP_CS_SET_TRANS_PORT_MSG_STRU
 �ṹ˵��  : VC��OM����Ϣ�ṹ, VC��OM����REQ��Ϣ

  1.��    ��   : 2011��10��17��
    ��    ��   : f00179209
    �޸�����   : ����, AT��ֲ��Ŀ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16                         usPrimId;                                /* ��Ϣ�� */
    VOS_UINT16                         usReserve;                               /* ���� */
    VOS_UINT32                         ulStatus;                                /* �������� */
    VOS_UINT32                         ulPort;                                  /* �˿ں� */
}MN_APP_CS_SET_TRANS_PORT_MSG_STRU;

/*****************************************************************************
 �ṹ��    : MN_APP_PHONE_MODE_SET_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : STK/SPY����MMA�ػ�����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
    TAF_PH_OP_MODE_STRU                 stPhOpMode;
} MN_APP_PHONE_MODE_SET_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MN_APP_PHONE_LOADDEFAULT_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : STK/SPY����MMA�ָ�������������
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    VOS_UINT8                           aucReserved1[1];
}MN_APP_PHONE_LOADDEFAULT_REQ_STRU;

/*****************************************************************************
 �ṹ��    : MN_APP_PHONE_EVENT_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHONE ����STK ҵ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    TAF_PHONE_EVENT_INFO_STRU           stPhoneEvent;
}MN_APP_PHONE_EVENT_INFO_STRU;

/*****************************************************************************
 �ṹ��    : MN_APP_PHONE_SET_CNF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : PHONE ����STK ҵ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           opID;
    TAF_PARA_TYPE                       ucParaType;
    TAF_PARA_SET_RESULT                 ucResult;
    VOS_UINT8                           aucReserved[3];
}MN_APP_PHONE_SET_CNF_STRU;

/* Deleted by z00161729 for V9R1 STK����, 2013-7-24, begin */

/* Deleted by z00161729 for V9R1 STK����, 2013-7-24, end */


/*****************************************************************************
 �ṹ��    : MN_APP_SAR_ANTENSTATUS_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : OAM����TAF��ANTEN�¼��ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_INT32                           lAntenStatus; /* ����״̬�ϱ���Taf */
} MN_APP_SAR_ANTENSTATUS_MSG_STRU;

/*****************************************************************************
 �ṹ��    : MN_APP_SAR_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����DSP��Reduction�¼��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                  ulSarType;      /* �ϱ��������� */
    VOS_INT32                   lAntenStatus;   /* ����״̬ */
    VOS_UINT32                  ulSarReduction; /* ��sar�ȼ� */
}MN_APP_SAR_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_OAM_TRACE_CFG_STRU
 �ṹ˵��  : OAM����TAF��TRACE ������Ϣ
 1.��    ��   : 2012��04��20��
   ��    ��   : l00171473
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    TAF_OAM_PC_RECUR_CFG_ENUM_UINT8     enPcRecurCfgFlg;
    VOS_UINT8                           aucRsv3[3];
}TAF_OAM_TRACE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : TAF_OAM_TRACE_CFG_IND_STRU
 �ṹ˵��  : OAM����TAF��TRACE ������Ϣ
 1.��    ��   : 2012��04��20��
   ��    ��   : l00171473
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;            /* ԭ��ID*/

    TAF_OAM_TRACE_CFG_STRU              stTraceCfg;         /* TRACE������Ϣ */
}TAF_OAM_TRACE_CFG_IND_STRU;


/* Deleted by z00161729 for V9R1 STK����, 2013-7-24, begin */

/* Deleted by z00161729 for V9R1 STK����, 2013-7-24, end */


/* Deleted SSA_USSD_DCS_DECODE_HOOK_STRU by f62575 for V9R1 STK����, 2013-6-26 */


/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-11, begin */
/*****************************************************************************
 �ṹ��    : TAF_OAM_UNSOLICITED_RPT_INFO_STRU
 �ṹ˵��  : �����ϱ�����ȫ�ֱ�����Ϣ��ά�ɲ�ṹ
 1.��    ��  : 2013��4��11��
   ��    ��  : z00161729
   �޸�����  : �½�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    VOS_UINT32                          ulRptCmdIndex;
    VOS_UINT8                           aucCurcRptCfg[TAF_STK_CURC_RPT_CFG_MAX_SIZE];
    VOS_UINT8                           aucUnsolicitedRptCfg[TAF_STK_CURC_RPT_CFG_MAX_SIZE];
 }TAF_OAM_UNSOLICITED_RPT_INFO_STRU;

/* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-11, end */

/*****************************************************************************
 �ṹ��    : TAF_OAM_EMERGENCY_CALL_STATUS_STRU
 �ṹ˵��  : ֪ͨOAM��������״̬�ṹ
 1.��    ��  : 2013��03��28��
   ��    ��  : l00198894
   �޸�����  : �½��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                  ulMsgId;
    TAF_OAM_EMERGENCY_CALL_STATUS_ENUM_UINT8    enEmergencyCallStatus;
    VOS_UINT8                                   aucReserved1[3];
}TAF_OAM_EMERGENCY_CALL_STATUS_STRU;

/* Deleted by z00161729 for V9R1 STK����, 2013-7-24, begin */

/* Deleted by z00161729 for V9R1 STK����, 2013-7-24, end */


/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, begin */
/*****************************************************************************
 �ṹ��    : TAF_OAM_LOG_END_CALL_REQ_STRU
 �ṹ˵��  : VCģ�鹴���쳣���ʱ��Ҫ�Ҷϵ绰�Ŀ�ά�ɲ���Ϣ
 1.��    ��  : 2013��07��20��
   ��    ��  : s00217060
   �޸�����  : �½��ṹ��
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                                              ulMsgId;
    VOS_UINT32                                              ulCause;
}TAF_OAM_LOG_END_CALL_REQ_STRU;

/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, end */

typedef VOS_INT (*pSockRecv)(VOS_UINT8 uPortNo, VOS_UINT8* pData, VOS_UINT16 uslength);

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern TAF_APS_USER_CONN_STATUS_ENUM_UINT8 TAF_APS_GetUserConnStatus(VOS_VOID);

extern VOS_VOID Spy_SarSendToDsp(MODEM_ID_ENUM_UINT16 enModemID, MN_APP_SAR_INFO_STRU *pstSpyToDsp);

extern VOS_UINT16 Spy_SarGetReduction(VOS_VOID);

/* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
/* Deleted SSA_GetDcsMsgCoding */
/* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

extern VOS_VOID SSA_UssdDcsHook(
    VOS_UINT32                          ulReceiverPid,
    VOS_UINT8                           ucDcs,
    MN_MSG_MSG_CODING_ENUM_U8           enMsgCoding
);

extern VOS_UINT32 PPM_LogPortSwitch(VOS_UINT32  ulPhyPort, VOS_BOOL ulEffect);

extern VOS_UINT32 PPM_QueryLogPort(VOS_UINT32  *pulLogPort);

extern OM_HSIC_PORT_STATUS_ENUM_UINT32 PPM_GetHsicPortStatus(VOS_VOID);

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

#endif /* end of TafOamInterface.h */

