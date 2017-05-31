

/************************************************************************
  Copyright   : 2013-2015, Huawei Tech. Co., Ltd.
  File name   : csimagent.h
  Author      : l00256032
  Version     : V900R001
  Date        : 2013-12-19
  Description : L+C��SIM����Ŀͷ�ļ���ض���---
  History     :
   1.Date:2013-12-19
     Author: L47619
     Modification:create

************************************************************************/

#ifndef __CSIMAGENT_H__
#define __CSIMAGENT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "UsimPsInterface.h"
#include "siapppih.h"
#include "usimmbase.h"
#include "siappstk.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/* ��CBP�ԽӵĽӿڣ���ǿ��Ҫ�����ֽڶ��� */
#pragma pack(1)

#if (FEATURE_ON == FEATURE_UE_UICC_MULTI_APP_SUPPORT)
/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define UIM_ERR_TIMEOUT                   (4)
#define STK_PROACTIVE_DATA_LEN            (256)
#define CSIMA_CBP_MSG_DATA_RSV            (4)
#define CSIMA_CARD_CHANEL_NULL            (0xFF)

/* CSIMA LOG�� */
#define CSIMA_INFO_LOG(string)            PS_LOG(WUEPS_PID_CSIMA, 0, PS_PRINT_INFO,   string)
#define CSIMA_NORMAL_LOG(string)          PS_LOG(WUEPS_PID_CSIMA, 0, PS_PRINT_NORMAL, string)
#define CSIMA_WARNING_LOG(string)         PS_LOG(WUEPS_PID_CSIMA, 0, PS_PRINT_WARNING,string)
#define CSIMA_ERROR_LOG(string)           PS_LOG(WUEPS_PID_CSIMA, 0, PS_PRINT_ERROR,  string)

#define CSIMA_INFO1_LOG(string, para1)    PS_LOG1(WUEPS_PID_CSIMA, 0, PS_PRINT_INFO,   string, para1)
#define CSIMA_NORMAL1_LOG(string, para1)  PS_LOG1(WUEPS_PID_CSIMA, 0, PS_PRINT_NORMAL, string, para1)
#define CSIMA_WARNING1_LOG(string, para1) PS_LOG1(WUEPS_PID_CSIMA, 0, PS_PRINT_WARNING,string, para1)
#define CSIMA_ERROR1_LOG(string, para1)   PS_LOG1(WUEPS_PID_CSIMA, 0, PS_PRINT_ERROR,  string, para1)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*****************************************************************************
 ö����    :CSIMA_ICC_MODE_ENUM
 �ṹ˵��  :CSIMA ��ǰ��Ӧ��ģʽö�ٶ���
*****************************************************************************/
enum CSIMA_ICC_MODE_ENUM
{
    CSIMA_ICC_MODE                      = 0x00,
    CSIMA_UICC_MODE                     = 0x01,
    CSIMA_ICC_MODE_BUTT
};
typedef VOS_UINT32     CSIMA_ICC_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    :CSIMA_CBP_CARD_TYPE_ENUM
 �ṹ˵��  :CSIMA��CBP�俨���Ͷ���,ʵ����дʱ��BIT��
*****************************************************************************/
enum CSIMA_CBP_CARD_TYPE_ENUM
{
    CSIMA_CBP_CARD_NONE                 = 0x00,
    CSIMA_CBP_UIM_CARD                  = 0x01,
    CSIMA_CBP_SIM_CARD                  = 0x02,
    CSIMA_CBP_UICC_CARD                 = 0x04,
    CSIMA_CBP_CSIM_CARD                 = 0x10,
    CSIMA_CBP_USIM_CARD                 = 0x20,
    CSIMA_CBP_ISIM_CARD                 = 0x40,
    CSIMA_CBP_UNKNOWN_CARD              = 0x80,
    CSIMA_CBP_CARD_TYPE_BUTT
};
typedef VOS_UINT16     CSIMA_CBP_CARD_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    :CSIMA_CBP_UICC_MSGID_ENUM
 �ṹ˵��  :CSIMA��CBP����UICC��ϢIDö��
*****************************************************************************/
enum CSIMA_CBP_UICC_MSGID_ENUM
{
    CSIMA_CBP_UICC_CTPDU_MSG            = 0x00, /* ����CSIMӦ��������Ϣ */
    CSIMA_CBP_UICC_RTPDU_MSG            = 0x01, /* ����CSIMӦ�ûظ���Ϣ */
    CSIMA_CBP_UICC_RST_REQ_MSG          = 0x02, /* RESET���� */
    CSIMA_CBP_UICC_STATUS_IND_MSG       = 0x03, /* ��״̬�ϱ� */
    CSIMA_CBP_UICC_PROACTIVE_CMD_MSG    = 0x04, /* ���������ϱ� */
    CSIMA_CBP_UICC_TERMINALRESPONSE_MSG = 0x05, /* ��������ִ�н�� */
    CSIMA_CBP_UICC_RESACC_REQ_MSG       = 0x07, /* ���޷���USIMӦ��������Ϣ */
    CSIMA_CBP_UICC_RESACC_RSP_MSG       = 0x08, /* ���޷���USIMӦ�ûظ���Ϣ */
    CSIMA_CBP_UICC_HANDSHAKE_MSG        = 0xee, /* VIA��BALONG���ִ��� */
    CSIMA_CBP_UICC_MSGID_BUTT
};
typedef VOS_UINT32     CSIMA_CBP_UICC_MSGID_ENUM_UINT32;

/*****************************************************************************
 ö����    :CSIMA_CBP_CARD_STATUS_ENUM
 �ṹ˵��  :CSIMA��CBP�ϱ��Ŀ�״̬ö��
*****************************************************************************/
enum CSIMA_CBP_CARD_STATUS_ENUM
{
    CSIMA_CBP_CARD_NOT_READY            = 0x00, /* ��ʼ��ʧ���ϱ� */
    CSIMA_CBP_CARD_ERROR,                       /* ��ʱ����Ҫ */
    CSIMA_CBP_CARD_REPLACED,                    /* ��ʱ����Ҫ */
    CSIMA_CBP_CARD_READY,                       /* ��ʼ���ɹ��ϱ� */
    CSIMA_CBP_CARD_BOOTUP,                      /* ��ʼ��δ��ɻ�ȴ�PINУ�� */
    CSIMA_CBP_CARD_LINK_FAILURE,                /* ��ʱ����Ҫ */
    CSIMA_CBP_CARD_STATUS_BUTT
};
typedef VOS_UINT16     CSIMA_CBP_CARD_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    :CSIMA_ICC_MODE_ENUM
 �ṹ˵��  :CSIMA ��ǰ��Ӧ��ģʽö�ٶ���
*****************************************************************************/
enum CSIMA_EVENTLIST_RESEND_ENUM
{
    CSIMA_EVENTLIST_RESEND_INIT           = 0x00,
    CSIMA_EVENTLIST_NEED_RESEND           = 0x01,
    CSIMA_EVENTLIST_RESENT                = 0X02,
    CSIMA_EVENTLIST_BUTT
};
typedef VOS_UINT32     CSIMA_EVENTLIST_RESEND_ENUM_UINT32;

/*****************************************************************************
  4 �ṹ�嶨��
*****************************************************************************/
/*****************************************************************************
 �ṹ��    :CSIMA_CBP_MSG_STRU
 �ṹ˵��  :CSIMA��CBP������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                               ulIPCMsgId;                     /* ��ϢID */
}CSIMA_CBP_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_STATUS_IND_MSG_STRU
 �ṹ˵��  :CSIMA��CBP�ϱ���״̬�ṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    CSIMA_CBP_CARD_STATUS_ENUM_UINT16       enStatus;                       /* ��״̬ */
    VOS_UINT16                              usCardType;                     /* �����ͣ���Ӧ�õ������bit��ʾ����Ӧ������,����ֶ���status readyʱ����Ϊ������ */
    VOS_UINT8                               ucCSIMChanNum;                  /* CSIMͨ���� */
    VOS_UINT8                               ucUSIMChanNum;                  /* USIMͨ���� */
    VOS_UINT8                               ucISIMChanNum;                  /* ISIMͨ���ţ���֧�֣���0xff */
    VOS_UINT8                               aucCSIMAID[USIMM_AID_LEN_MAX];  /* CSIM AID */
    VOS_UINT8                               aucUSIMAID[USIMM_AID_LEN_MAX];  /* USIM AID */
    VOS_UINT8                               aucISIMAID[USIMM_AID_LEN_MAX];  /* ISIM AID,��֧�֣���0xff */
    VOS_UINT32                              ulWWT;                          /* work waiting time,��ʱ����Ҫ����0 */
    VOS_UINT8                               ucATRLen;                       /* ATR���ȣ���ʱ����Ҫ����0 */
    VOS_UINT8                               aucATR[1];                      /* ATR���ݣ���ʱ����Ҫ�����һ���ֽ�0 */
}CSIMA_CBP_STATUS_IND_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_CTPDU_MSG_STRU
 �ṹ˵��  :CBP����CSIMӦ���������ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT8                               aucCTPDUHdr[USIMM_APDU_HEADLEN];/* CTPDUͷ */
    VOS_UINT8                               ucChanNum;                      /* ͨ���� */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ���� */
}CSIMA_CBP_CTPDU_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_RTPDU_MSG_STRU
 �ṹ˵��  :CBP����CSIMӦ�ûظ����ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT16                              usSWStatus;                     /* SW1�ڵ�λ��SW2�ڸ�λ */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ���� */
}CSIMA_CBP_RTPDU_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_PROACTIVE_CMD_MSG_STRU
 �ṹ˵��  :CSIMA��CBP���͵���������ṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[STK_PROACTIVE_DATA_LEN];/* ���� */
}CSIMA_CBP_PROACTIVE_CMD_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_TERMINALRESPONSE_MSG_STRU
 �ṹ˵��  :CBP�ظ���CSIMA����������ִ�н�����ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ���� */
}CSIMA_CBP_TERMINALRESPONSE_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_RESACC_REQ_MSG_STRU
 �ṹ˵��  :CBP����USIMӦ�����ļ��������ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT8                               ucChanNum;                      /* ͨ���� */
    VOS_UINT8                               ucCmd;                          /* �������� */
    VOS_UINT16                              usFileId;                       /* �ļ�ID����λ��ǰ��λ�ں� */
    VOS_UINT8                               ucP1;                           /* P1���� */
    VOS_UINT8                               ucP2;                           /* P2���� */
    VOS_UINT8                               ucP3;                           /* P3���� */
    VOS_UINT8                               ucLen;                          /* aucData�������ݳ��ȣ�������·������ */
    VOS_UINT16                              usPathLen;                      /* ·������ */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ����+·����·�����Ѱ����ļ�ID */
}CSIMA_CBP_RESACC_REQ_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_RESACC_RSP_MSG_STRU
 �ṹ˵��  :CBP����USIMӦ�����ļ��ظ����ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT16                              usSWStatus;                     /* SW1�ڵ�λ��SW2�ڸ�λ */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ���� */
}CSIMA_CBP_RESACC_RSP_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_STK_PROACTIVE_CMD_MSG_STRU
 �ṹ˵��  :STK��CSIMA���������������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT32                              ulLen;
    VOS_UINT8                               aucProactiveCmd[STK_PROACTIVE_DATA_LEN];
}CSIMA_STK_PROACTIVE_CMD_MSG_STRU;

/*****************************************************************************
 �ṹ��    : CSIMA_CARDINFO_STRU
 �ṹ˵��  : CSIMAģ�鱣��USIM����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enPhyType;
}CSIMA_CARDINFO_STRU;


/*****************************************************************************
  4 ��������
*****************************************************************************/
extern VOS_UINT32 CSIMA_SendTerminalResponse(VOS_UINT8 ucLen, VOS_UINT8 *pucRsp);

extern VOS_UINT32 CSIMA_SendInitCardReqMsg(USIMM_CMDTYPE_REQ_ENUM_UINT32 enMsgName);

extern VOS_UINT32 CSIMA_SendActiveCardReqMsg(VOS_VOID);

extern VOS_UINT32 CSIMA_SendTPDUReqMsg(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_SENDPARA_ENUM_UINT32          enSendPara,
    USIMM_TPDU_DATA_STRU               *pstTpduData
);

extern VOS_UINT32 CSIMA_CBP_HandshakeReqMsg(VOS_VOID);

extern VOS_UINT32  CSIMA_UiccResAccReqMsg(CSIMA_CBP_RESACC_REQ_MSG_STRU *pstMsg);

extern VOS_VOID CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_STATUS_ENUM_UINT16 enCardStatus);

extern VOS_VOID CSIMA_FirstCardStatusInd(USIMM_CARDSTATUS_IND_STRU *pstMsg);

extern VOS_VOID CSIMA_CardStatusInd(USIMM_CARDSTATUS_IND_STRU *pstMsg);

extern VOS_UINT32 CSIMA_SendTPDUOnChan(CSIMA_CBP_CTPDU_MSG_STRU *pstCtpduMsg);

extern VOS_UINT32 CSIMA_PidInit(enum VOS_INIT_PHASE_DEFINE ip);

extern VOS_VOID CSIMA_PidMsgProc(CSIMA_CBP_MSG_STRU *pstMsg);

extern VOS_UINT32 CSIMA_Init(VOS_VOID);

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 OTHERS����
*****************************************************************************/

#else

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define UIM_ERR_TIMEOUT                   (4)
#define STK_PROACTIVE_DATA_LEN            (256)
#define CSIMA_CBP_MSG_DATA_RSV            (4)
#define CSIMA_CARD_CHANEL_NULL            (0xFF)

/* CSIMA LOG�� */
#define CSIMA_INFO_LOG(string)            PS_LOG(WUEPS_PID_CSIMA, 0, PS_PRINT_INFO,   string)
#define CSIMA_NORMAL_LOG(string)          PS_LOG(WUEPS_PID_CSIMA, 0, PS_PRINT_NORMAL, string)
#define CSIMA_WARNING_LOG(string)         PS_LOG(WUEPS_PID_CSIMA, 0, PS_PRINT_WARNING,string)
#define CSIMA_ERROR_LOG(string)           PS_LOG(WUEPS_PID_CSIMA, 0, PS_PRINT_ERROR,  string)

#define CSIMA_INFO1_LOG(string, para1)    PS_LOG1(WUEPS_PID_CSIMA, 0, PS_PRINT_INFO,   string, para1)
#define CSIMA_NORMAL1_LOG(string, para1)  PS_LOG1(WUEPS_PID_CSIMA, 0, PS_PRINT_NORMAL, string, para1)
#define CSIMA_WARNING1_LOG(string, para1) PS_LOG1(WUEPS_PID_CSIMA, 0, PS_PRINT_WARNING,string, para1)
#define CSIMA_ERROR1_LOG(string, para1)   PS_LOG1(WUEPS_PID_CSIMA, 0, PS_PRINT_ERROR,  string, para1)

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/*****************************************************************************
 ö����    :CSIMA_ICC_MODE_ENUM
 �ṹ˵��  :CSIMA ��ǰ��Ӧ��ģʽö�ٶ���
*****************************************************************************/
enum CSIMA_ICC_MODE_ENUM
{
    CSIMA_ICC_MODE                      = 0x00,
    CSIMA_UICC_MODE                     = 0x01,
    CSIMA_ICC_MODE_BUTT
};
typedef VOS_UINT32     CSIMA_ICC_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    :CSIMA_CBP_CARD_TYPE_ENUM
 �ṹ˵��  :CSIMA��CBP�俨���Ͷ���,ʵ����дʱ��BIT��
*****************************************************************************/
enum CSIMA_CBP_CARD_TYPE_ENUM
{
    CSIMA_CBP_UIM_CARD                  = 0x01,
    CSIMA_CBP_SIM_CARD                  = 0x02,
    CSIMA_CBP_UICC_CARD                 = 0x04,
    CSIMA_CBP_CSIM_CARD                 = 0x10,
    CSIMA_CBP_USIM_CARD                 = 0x20,
    CSIMA_CBP_ISIM_CARD                 = 0x40,
    CSIMA_CBP_UNKNOWN_CARD              = 0x80,
    CSIMA_CBP_CARD_TYPE_BUTT
};
typedef VOS_UINT16     CSIMA_CBP_CARD_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    :CSIMA_CBP_UICC_MSGID_ENUM
 �ṹ˵��  :CSIMA��CBP����UICC��ϢIDö��
*****************************************************************************/
enum CSIMA_CBP_UICC_MSGID_ENUM
{
    CSIMA_CBP_UICC_CTPDU_MSG            = 0x00, /* ����CSIMӦ��������Ϣ */
    CSIMA_CBP_UICC_RTPDU_MSG            = 0x01, /* ����CSIMӦ�ûظ���Ϣ */
    CSIMA_CBP_UICC_RST_REQ_MSG          = 0x02, /* RESET���� */
    CSIMA_CBP_UICC_STATUS_IND_MSG       = 0x03, /* ��״̬�ϱ� */
    CSIMA_CBP_UICC_PROACTIVE_CMD_MSG    = 0x04, /* ���������ϱ� */
    CSIMA_CBP_UICC_TERMINALRESPONSE_MSG = 0x05, /* ��������ִ�н�� */
    CSIMA_CBP_UICC_RESACC_REQ_MSG       = 0x07, /* ���޷���USIMӦ��������Ϣ */
    CSIMA_CBP_UICC_RESACC_RSP_MSG       = 0x08, /* ���޷���USIMӦ�ûظ���Ϣ */
    CSIMA_CBP_UICC_HANDSHAKE_MSG        = 0xee, /* VIA��BALONG���ִ��� */
    CSIMA_CBP_UICC_MSGID_BUTT
};
typedef VOS_UINT32     CSIMA_CBP_UICC_MSGID_ENUM_UINT32;

/*****************************************************************************
 ö����    :CSIMA_CBP_CARD_STATUS_ENUM
 �ṹ˵��  :CSIMA��CBP�ϱ��Ŀ�״̬ö��
*****************************************************************************/
enum CSIMA_CBP_CARD_STATUS_ENUM
{
    CSIMA_CBP_CARD_NOT_READY            = 0x00, /* ��ʼ��ʧ���ϱ� */
    CSIMA_CBP_CARD_ERROR,                       /* ��ʱ����Ҫ */
    CSIMA_CBP_CARD_REPLACED,                    /* ��ʱ����Ҫ */
    CSIMA_CBP_CARD_READY,                       /* ��ʼ���ɹ��ϱ� */
    CSIMA_CBP_CARD_BOOTUP,                      /* ��ʼ��δ��ɻ�ȴ�PINУ�� */
    CSIMA_CBP_CARD_LINK_FAILURE,                /* ��ʱ����Ҫ */
    CSIMA_CBP_CARD_STATUS_BUTT
};
typedef VOS_UINT16     CSIMA_CBP_CARD_STATUS_ENUM_UINT16;

/*****************************************************************************
 ö����    :CSIMA_ICC_MODE_ENUM
 �ṹ˵��  :CSIMA ��ǰ��Ӧ��ģʽö�ٶ���
*****************************************************************************/
enum CSIMA_EVENTLIST_RESEND_ENUM
{
    CSIMA_EVENTLIST_RESEND_INIT           = 0x00,
    CSIMA_EVENTLIST_NEED_RESEND           = 0x01,
    CSIMA_EVENTLIST_RESENT                = 0X02,
    CSIMA_EVENTLIST_BUTT
};
typedef VOS_UINT32     CSIMA_EVENTLIST_RESEND_ENUM_UINT32;

/*****************************************************************************
  4 �ṹ�嶨��
*****************************************************************************/
/*****************************************************************************
 �ṹ��    :CSIMA_CBP_MSG_STRU
 �ṹ˵��  :CSIMA��CBP������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                               ulIPCMsgId;                     /* ��ϢID */
}CSIMA_CBP_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_STATUS_IND_MSG_STRU
 �ṹ˵��  :CSIMA��CBP�ϱ���״̬�ṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    CSIMA_CBP_CARD_STATUS_ENUM_UINT16       enStatus;                       /* ��״̬ */
    VOS_UINT16                              usCardType;                     /* �����ͣ���Ӧ�õ������bit��ʾ����Ӧ������,����ֶ���status readyʱ����Ϊ������ */
    VOS_UINT8                               ucCSIMChanNum;                  /* CSIMͨ���� */
    VOS_UINT8                               ucUSIMChanNum;                  /* USIMͨ���� */
    VOS_UINT8                               ucISIMChanNum;                  /* ISIMͨ���ţ���֧�֣���0xff */
    VOS_UINT8                               aucCSIMAID[USIMM_AID_LEN_MAX];  /* CSIM AID */
    VOS_UINT8                               aucUSIMAID[USIMM_AID_LEN_MAX];  /* USIM AID */
    VOS_UINT8                               aucISIMAID[USIMM_AID_LEN_MAX];  /* ISIM AID,��֧�֣���0xff */
    VOS_UINT32                              ulWWT;                          /* work waiting time,��ʱ����Ҫ����0 */
    VOS_UINT8                               ucATRLen;                       /* ATR���ȣ���ʱ����Ҫ����0 */
    VOS_UINT8                               aucATR[1];                      /* ATR���ݣ���ʱ����Ҫ�����һ���ֽ�0 */
}CSIMA_CBP_STATUS_IND_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_CTPDU_MSG_STRU
 �ṹ˵��  :CBP����CSIMӦ���������ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT8                               aucCTPDUHdr[USIMM_APDU_HEADLEN];/* CTPDUͷ */
    VOS_UINT8                               ucChanNum;                      /* ͨ���� */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ���� */
}CSIMA_CBP_CTPDU_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_RTPDU_MSG_STRU
 �ṹ˵��  :CBP����CSIMӦ�ûظ����ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT16                              usSWStatus;                     /* SW1�ڵ�λ��SW2�ڸ�λ */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ���� */
}CSIMA_CBP_RTPDU_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_PROACTIVE_CMD_MSG_STRU
 �ṹ˵��  :CSIMA��CBP���͵���������ṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[STK_PROACTIVE_DATA_LEN];/* ���� */
}CSIMA_CBP_PROACTIVE_CMD_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_TERMINALRESPONSE_MSG_STRU
 �ṹ˵��  :CBP�ظ���CSIMA����������ִ�н�����ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ���� */
}CSIMA_CBP_TERMINALRESPONSE_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_RESACC_REQ_MSG_STRU
 �ṹ˵��  :CBP����USIMӦ�����ļ��������ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT8                               ucChanNum;                      /* ͨ���� */
    VOS_UINT8                               ucCmd;                          /* �������� */
    VOS_UINT16                              usFileId;                       /* �ļ�ID����λ��ǰ��λ�ں� */
    VOS_UINT8                               ucP1;                           /* P1���� */
    VOS_UINT8                               ucP2;                           /* P2���� */
    VOS_UINT8                               ucP3;                           /* P3���� */
    VOS_UINT8                               ucLen;                          /* aucData�������ݳ��ȣ�������·������ */
    VOS_UINT16                              usPathLen;                      /* ·������ */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ����+·����·�����Ѱ����ļ�ID */
}CSIMA_CBP_RESACC_REQ_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_CBP_RESACC_RSP_MSG_STRU
 �ṹ˵��  :CBP����USIMӦ�����ļ��ظ����ݽṹ
*****************************************************************************/
typedef struct
{
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT16                              usSWStatus;                     /* SW1�ڵ�λ��SW2�ڸ�λ */
    VOS_UINT16                              usDataLen;                      /* ���ݳ��� */
    VOS_UINT8                               aucData[CSIMA_CBP_MSG_DATA_RSV];/* ���� */
}CSIMA_CBP_RESACC_RSP_MSG_STRU;

/*****************************************************************************
 �ṹ��    :CSIMA_STK_PROACTIVE_CMD_MSG_STRU
 �ṹ˵��  :STK��CSIMA���������������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    CSIMA_CBP_UICC_MSGID_ENUM_UINT32        enIPCMsgId;                     /* ��ϢID */
    VOS_UINT32                              ulLen;
    VOS_UINT8                               aucProactiveCmd[STK_PROACTIVE_DATA_LEN];
}CSIMA_STK_PROACTIVE_CMD_MSG_STRU;

/*****************************************************************************
 �ṹ��    : CSIMA_CARDINFO_STRU
 �ṹ˵��  : CSIMAģ�鱣��USIM����Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    USIMM_PHYCARD_TYPE_ENUM_UINT32      enPhyType;
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType;
    USIMM_CARD_SERVIC_ENUM_UINT32       enSvcStatus;
}CSIMA_CARDINFO_STRU;


/*****************************************************************************
  4 ��������
*****************************************************************************/

extern VOS_VOID CSIMA_DataHook(VOS_UINT32 ulLength, VOS_UINT8 *pucData);

extern VOS_UINT32 CSIMA_SendTerminalResponse(VOS_UINT8 ucLen, VOS_UINT8 *pucRsp);

extern VOS_UINT32 CSIMA_SendOpenChannelReqMsg(VOS_UINT32 ulAIDLen, VOS_UINT8 *pucADFName);

extern VOS_UINT32 CSIMA_SendInitCardReqMsg(USIMM_CMDTYPE_REQ_ENUM_UINT32 enMsgName);

extern VOS_UINT32 CSIMA_SendActiveCardReqMsg(VOS_VOID);

extern VOS_UINT32 CSIMA_SendTPDUReqMsg(
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    USIMM_SENDPARA_ENUM_UINT32          enSendPara,
    USIMM_TPDU_DATA_STRU               *pstTpduData
);

extern VOS_UINT32 CSIMA_SendTPDUCnfMsg(USIMM_SENDTPDUDATA_CNF_STRU *pstMsg);

extern VOS_VOID CSIMA_OpenCSIMOnLogicChannel(VOS_UINT32 ulAIDLen, VOS_UINT8 *pucAID);

extern VOS_VOID CSIMA_OpenCSIMOnBaseChannel(VOS_UINT32 ulAIDLen, VOS_UINT8 *pucAID);

extern VOS_UINT32 CSIMA_CBP_HandshakeReqMsg(VOS_VOID);

extern VOS_UINT32  CSIMA_UiccResAccReqMsg(CSIMA_CBP_RESACC_REQ_MSG_STRU *pstMsg);

extern VOS_VOID CSIMA_SelectDFCdma(VOS_VOID);

extern VOS_VOID CSIMA_CardStatusMsgSend(CSIMA_CBP_CARD_STATUS_ENUM_UINT16 enCardStatus, CSIMA_CBP_CARD_TYPE_ENUM_UINT16   enCardType);

extern VOS_VOID CSIMA_FirstCardStatusInd(USIMM_CARDSTATUS_IND_STRU *pstMsg);

extern VOS_VOID CSIMA_CardStatusInd(USIMM_CARDSTATUS_IND_STRU *pstMsg);

extern VOS_UINT32 CSIMA_SendTPDUOnBaseChan(CSIMA_CBP_CTPDU_MSG_STRU *pstCtpduMsg);

extern VOS_UINT32 CSIMA_PidInit(enum VOS_INIT_PHASE_DEFINE ip);

extern VOS_VOID CSIMA_PidMsgProc(CSIMA_CBP_MSG_STRU *pstMsg);

extern VOS_UINT32 CSIMA_Init(VOS_VOID);

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  6 OTHERS����
*****************************************************************************/

#endif

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

#endif /* end of csimagent.h*/

