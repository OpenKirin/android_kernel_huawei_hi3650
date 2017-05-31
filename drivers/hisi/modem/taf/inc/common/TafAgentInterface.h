

#ifndef _TAFAGENTAPSINTERFACE_H_
#define _TAFAGENTAPSINTERFACE_H_

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "AtMnInterface.h"
#include "TafApsApi.h"
#include "MnCallApi.h"
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, begin */
#include "TafAppMma.h"
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, end */

#pragma pack(4)


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  4 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
ö����    : TAFAGENT_MSG_ID_ENUM
�ṹ˵��  : CDS��ADS��֮�����Ϣ

  1.��    ��   : 2011��12��22��
    ��    ��   : ��־��/c00173809
    �޸�����   : ����TAFAGENT��APS֮�����Ϣ
  2.��    ��   : 2011��12��26��
    ��    ��   : w00199382
    �޸�����   : ����TAFAGENT��MN֮�����Ϣ
*****************************************************************************/
enum TAFAGENT_MSG_ID_ENUM
{

    /* TAFAGENT->APS ��ѯCID������Ϣ */
    ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ   = 0x1000,                           /* _H2ASN_MsgChoice TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU */

    /* TAFAGENT->APS ����CID�Ĳ���������Ϣ */
    ID_TAFAGENT_APS_SET_CID_PARA_REQ        = 0x1001,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_PARA_REQ_STRU */

    /* TAFAGENT->APS ��ȡCID�Ĳ���������Ϣ */
    ID_TAFAGENT_APS_GET_CID_PARA_REQ        = 0x1002,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_PARA_REQ_STRU */

    /* TAFAGENT->APS ����CID��QOS����������Ϣ */
    ID_TAFAGENT_APS_SET_CID_QOS_PARA_REQ    = 0x1003,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU */

    /* TAFAGENT->APS ��ȡCID��QOS����������Ϣ */
    ID_TAFAGENT_APS_GET_CID_QOS_PARA_REQ    = 0x1004,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU */

    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
    ID_TAFAGENT_MTA_GET_SYSMODE_REQ         = 0x1005,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_SYSMODE_REQ_STRU */
    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

    ID_TAFAGENT_MTA_GET_ANT_STATE_REQ       = 0x1006,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU */


    /* APS->TAFAGENT ��ѯCID�ظ���Ϣ */
    ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF   = 0x2000,                           /* _H2ASN_MsgChoice TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU */

    /* APS->TAFAGENT ����CID�Ĳ����ظ���Ϣ */
    ID_TAFAGENT_APS_SET_CID_PARA_CNF        = 0x2001,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_PARA_CNF_STRU */

    /* APS->TAFAGENT ��ȡCID�Ĳ����ظ���Ϣ */
    ID_TAFAGENT_APS_GET_CID_PARA_CNF        = 0x2002,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_PARA_CNF_STRU */

    /* APS->TAFAGENT ����CID��QOS�����ظ���Ϣ */
    ID_TAFAGENT_APS_SET_CID_QOS_PARA_CNF    = 0x2003,                           /* _H2ASN_MsgChoice TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU */

    /* APS->TAFAGENT ��ȡCID��QOS�����ظ���Ϣ */
    ID_TAFAGENT_APS_GET_CID_QOS_PARA_CNF    = 0x2004,                           /* _H2ASN_MsgChoice TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU */

    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
    /* TAFAGENT->MTA  ��ȡϵͳģʽ��Ϣ�ظ���Ϣ*/
    ID_TAFAGENT_MTA_GET_SYSMODE_CNF         = 0x2005,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_SYSMODE_CNF_STRU */
    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

    /* TAFAGENT->MN  ��ȡͨ����Ϣ�ظ���Ϣ*/
    ID_TAFAGENT_MN_GET_CALL_INFO_CNF        = 0x2006,                           /* _H2ASN_MsgChoice TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU */



    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
    /* MTA->TAFAGENT  ��ȡ����״̬�ظ���Ϣ*/
    ID_TAFAGENT_MTA_GET_ANT_STATE_CNF       = 0x2007,                           /* _H2ASN_MsgChoice TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU */
    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

    ID_TAFAGENT_MSG_ID_ENUM_BUTT
};
typedef VOS_UINT32  TAFAGENT_MSG_ID_ENUM_UINT32;


/*****************************************************************************
  5 �ṹ����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_SET_CID_PARA_REQ_STRU
 �ṹ˵��  : ID_MSG_TAF_PS_SET_CID_PARA_REQ��Ϣ�ṹ, ����CID ����
 1.��    ��   : 2011��12��19��
   ��    ��   : C00173809
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulClientID;                             /* CLIENT ID */
    TAF_PDP_PRIM_CONTEXT_EXT_STRU       stPdpPrimContextExt;                    /* CID���� */
} TAFAGENT_APS_SET_CID_PARA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_QUERY_ERROR_CODE_REQ_STRU
 �ṹ˵��  : ID_TAFAGENT_APS_QUERY_ERROR_CODE_REQ��Ϣ�ṹ,
 1.��    ��   : 2011��12��19��
   ��    ��   : C00173809
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

} TAFAGENT_APS_QUERY_ERROR_CODE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_CLEAR_ERROR_CODE_REQ_STRU
 �ṹ˵��  : ID_TAFAGENT_APS_CLEAR_ERROR_CODE_REQ��Ϣ�ṹ,
 1.��    ��   : 2011��12��19��
   ��    ��   : C00173809
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

} TAFAGENT_APS_CLEAR_ERROR_CODE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_GET_CID_PARA_REQ_STRU
 �ṹ˵��  : ID_TAFAGENT_APS_GET_CID_PARA_REQ��Ϣ�ṹ,
 1.��    ��   : 2011��12��19��
   ��    ��   : C00173809
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucCid;                                  /* Ҫ��ȡ������CID */

    VOS_UINT8                           aucReserved[3];
} TAFAGENT_APS_GET_CID_PARA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU
 �ṹ˵��  : ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ��Ϣ�ṹ,
 1.��    ��   : 2011��12��19��
   ��    ��   : C00173809
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

} TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU;

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
/*****************************************************************************
 �ṹ��    : TAFAGENT_MTA_GET_SYSMODE_REQ_STRU
 �ṹ˵��  : ID_TAFAGENT_MTA_GET_SYSMODE_REQ��Ϣ�ṹ,
 1.��    ��   : 2013��3��25��
   ��    ��   : s00217060
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */
} TAFAGENT_MTA_GET_SYSMODE_REQ_STRU;
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, begin */
/* Deleted by Y00213812 for VoLTE_PhaseI ��Ŀ, 2013-07-08, end */

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_CLEAR_ERROR_CODE_CNF_STRU
 �ṹ˵��  : ID_EVT_TAF_PS_CLEAR_ERROR_CODE_CNF��Ϣ�ṹ,
 1.��    ��   : 2011��12��18��
   ��    ��   : c00173809
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ���ؽ�� */
} TAFAGENT_APS_CLEAR_ERROR_CODE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_GET_CID_PARA_CNF_STRU
 �ṹ˵��  : ID_EVT_TAF_PS_GET_CID_PARA_CNF��Ϣ�ṹ, ��ȡָ��CID�Ĳ���
 1.��    ��   : 2011��12��18��
   ��    ��   : c00173809
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ���ؽ�� */
    TAF_PDP_PRIM_CONTEXT_STRU           stCidInfo;                     /* ��ѯ��ȡָ��CID�Ĳ��� */
} TAFAGENT_APS_GET_CID_PARA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_SET_CID_PARA_CNF_STRU
 �ṹ˵��  : ID_EVT_TAF_PS_SET_CID_PARA_CNF��Ϣ�ṹ,
 1.��    ��   : 2011��12��18��
   ��    ��   : c00173809
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ���ؽ�� */
} TAFAGENT_APS_SET_CID_PARA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU
 �ṹ˵��  : ID_EVT_TAF_PS_FIND_CID_FOR_DIAL_CNF��Ϣ�ṹ, ��ȡCID�ظ��ṹ
 1.��    ��   : 2011��12��18��
   ��    ��   : c00173809
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ���ؽ�� */
    VOS_UINT8                           ucCid;                                  /* Ҫ��ѯ��CID */
    VOS_UINT8                           aucReserved[3];                         /* ����λ */
} TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGERNT_TAF_GET_CALL_INFO_STRU
 �ṹ˵��  : ��ȡͨ����Ϣ�Ľṹ
 1.��    ��   : 2011��12��18��
   ��    ��   : w00199382
   �޸�����   : �����ṹ
*****************************************************************************/

typedef struct
{
    MN_CALL_ID_T                        callId;                                 /* ��������ͨ���ĸ��� */
    MN_CALL_TYPE_ENUM_U8                enCallType;                             /* ͨ������*/
    MN_CALL_STATE_ENUM_U8               enCallState;                            /* ͨ��״̬*/
    VOS_UINT8                           aucReserved[1];                         /* ����λ */
}TAFAGERNT_MN_CALL_INFO_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU
 �ṹ˵��  : ID_TAFAGENT_MN_GET_CALL_INFO_CNF��Ϣ�ṹ, ��ȡ�ظ��ṹ
 1.��    ��   : 2011��12��18��
   ��    ��   : w00199382
   �޸�����   : �����ṹ
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucNumOfCalls;                           /* ��������ͨ���ĸ��� */
    VOS_UINT8                           aucReserved[3];                         /* ����λ */
    TAFAGERNT_MN_CALL_INFO_STRU         stCallInfo[MN_CALL_MAX_NUM];            /*���غ�����Ϣ*/
}TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU;

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, begin */
/*****************************************************************************
 �ṹ��    : TAF_SYS_MODE_STRU
 �ṹ˵��  : ��¼��ǰϵͳģʽ, ����:
             (1) RAT Type ���뼼��
             (2) Sub Mode ϵͳ��ģʽ
*****************************************************************************/
typedef struct
{
    TAF_SYS_MODE_ENUM_UINT8             enRatType;           /* ���뼼��   */
    TAF_SYS_SUBMODE_ENUM_UINT8          enSysSubMode;        /* ϵͳ��ģʽ */
    VOS_UINT8                           aucReserve[2];
} TAF_AGENT_SYS_MODE_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_MTA_GET_SYSMODE_CNF_STRU
 �ṹ˵��  : ID_TAFAGENT_MTA_GET_SYSMODE_CNF��Ϣ�ṹ, ��ȡ�ظ��ṹ
 1.��    ��   : 2013��03��26��
   ��    ��   : s00217060
   �޸�����   : �����ṹ
*****************************************************************************/

typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */
    VOS_UINT32                          ulRet;                                  /* �ظ���� */
    TAF_AGENT_SYS_MODE_STRU             stSysMode;                              /* ϵͳģʽ���������뼼����ϵͳ��ģʽ */
}TAFAGENT_MTA_GET_SYSMODE_CNF_STRU;
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-3-25, end */

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU
 �ṹ˵��  : ID_MSG_TAF_PS_SET_CID_QOS_PARA_REQ��Ϣ�ṹ, ����CID ����
 1.��    ��   : 2013��06��29��
   ��    ��   : L60609
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */

    VOS_UINT16                          usClientId;                             /* CLIENT ID */

    VOS_UINT8                           ucRsv1[2];

    TAF_PS_PDP_QOS_SET_PARA_STRU        stQosPara;
} TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU
 �ṹ˵��  : ID_TAFAGENT_APS_GET_CID_QOS_PARA_REQ��Ϣ�ṹ,
 1.��    ��   : 2013��06��29��
   ��    ��   : L60609
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    VOS_UINT32                          ulMsgId;                                /* _H2ASN_Skip */

    VOS_UINT8                           ucCid;                                  /* Ҫ��ȡ������CID */

    VOS_UINT8                           ucRsv1[3];
} TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU
 �ṹ˵��  : ID_EVT_TAF_PS_SET_CID_QOS_PARA_CNF��Ϣ�ṹ,
 1.��    ��   : 2013��06��29��
   ��    ��   : L60609
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ���ؽ�� */
} TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU
 �ṹ˵��  : ID_EVT_TAF_PS_GET_CID_QOS_PARA_CNF��Ϣ�ṹ, ��ȡָ��CID�Ĳ���
 1.��    ��   : 2013��06��29��
   ��    ��   : L60609
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRet;                                  /* ���ؽ�� */

    TAF_PS_PDP_QOS_QUERY_PARA_STRU      stQosPara;

} TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU;



/*****************************************************************************
 �ṹ��    : TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU
 �ṹ˵��  : ID_TAFAGENT_MTA_GET_ANT_STATE_REQ��Ϣ�ṹ,
 1.��    ��   : 2013��8��2��
   ��    ��   : z60575
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */
} TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU
 �ṹ˵��  : ID_TAFAGENT_MTA_GET_ANT_STATE_CNF��Ϣ�ṹ, ��ȡָ��CID�Ĳ���
 1.��    ��   : 2013��06��29��
   ��    ��   : L60609
   �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    TAFAGENT_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_Skip */

    VOS_UINT32                          ulRslt;
    VOS_UINT16                          usAntState;                             /* ����״̬ */
    VOS_UINT8                           aucReserved1[2];

} TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU;
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    TAFAGENT_MSG_ID_ENUM_UINT32         ulMsgId;                                /*_H2ASN_MsgChoice_Export TAFAGENT_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAFAGENT_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_AGENT_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_AGENT_MSG_DATA                  stMsgData;
}TafAgentInterface_MSG;


/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

