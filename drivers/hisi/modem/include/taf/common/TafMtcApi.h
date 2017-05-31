
#ifndef _TAF_MTC_API_H_
#define _TAF_MTC_API_H_


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "PsTypeDef.h"
#include "TafApi.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_MTC_MSG_ID_BASE             (0x1000)                               /* MTC �ṩ����ϢID����, ��0x1001��ʼ����ҪΪ�˱�����������Ϣ�غ� */

#define MTC_NONE_CS_VALUE                (0x00)                                /* �޵绰 */
#define MTC_GU_CS_VALUE                  (MTC_SET_BIT(MTC_CS_TYPE_GU))          /* GU�绰 */
#define MTC_IMS_CS_VALUE                 (MTC_SET_BIT(MTC_CS_TYPE_IMS))         /* IMS�绰 */
#define MTC_CDMA_CS_VALUE                (MTC_SET_BIT(MTC_CS_TYPE_CDMA))        /* CDMA�绰 */

#define MTC_CS_TYPE_ALL_VALUE            (MTC_GU_CS_VALUE | MTC_IMS_CS_VALUE | MTC_CDMA_CS_VALUE)

#define MTC_NONE_PS_VALUE                (0x00)
#define MTC_GU_PS_VALUE                  (MTC_SET_BIT(MTC_PS_TYPE_GU))
#define MTC_LTE_PS_VALUE                 (MTC_SET_BIT(MTC_PS_TYPE_LTE))
#define MTC_CDMA_PS_VALUE                (MTC_SET_BIT(MTC_PS_TYPE_CDMA))
#define MTC_PS_TYPE_ALL_VALUE            (MTC_GU_PS_VALUE | MTC_LTE_PS_VALUE | MTC_CDMA_PS_VALUE)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö������: TAF_MTC_MSG_ID_ENUM
 ö��˵��: MTC�ڲ���ϢID

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : ����ö��
*****************************************************************************/
enum TAF_MTC_MSG_ID_ENUM
{
    /* ���CDMA����״̬ */
    ID_MSG_MTC_CDMA_CONN_STATE_IND      = TAF_MTC_MSG_ID_BASE + 0x0001,        /* _H2ASN_MsgChoice  TAF_MTC_CDMA_STATE_IND_STRU */
    ID_MSG_MTC_MODEM_SERVICE_CONN_STATE_IND,                                    /* _H2ASN_MsgChoice  TAF_MTC_MODEM_CONN_STATUS_IND_STRU */
    ID_MSG_MTC_USIMM_STATE_IND,                                                 /* _H2ASN_MsgChoice  TAF_MTC_USIMM_STATUS_IND_STRU */
    ID_MSG_MTC_BEGIN_SESSION_IND,                                               /* _H2ASN_MsgChoice  MTC_BEGIN_SESSION_IND_STRU */
    ID_MSG_MTC_END_SESSION_IND,                                                 /* _H2ASN_MsgChoice  MTC_END_SESSION_IND_STRU */

    ID_MSG_MTC_POWER_SAVE_IND,                                                  /* _H2ASN_MsgChoice  MTC_POWER_SAVE_IND_STRU */

    ID_MSG_MTC_BUTT
};
typedef VOS_UINT32 TAF_MTC_MSG_ID_ENUM_UINT32;

/*****************************************************************************
ö����    : TAF_MTC_SRV_CONN_STATE_ENUM
�ṹ˵��  : ҵ������״̬ö�ٶ���

  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : ����ö��
*****************************************************************************/
enum TAF_MTC_SRV_CONN_STATE_ENUM
{
    TAF_MTC_SRV_NO_EXIST                = 0,                                    /* ������ */
    TAF_MTC_SRV_EXIST,                                                          /* ������ */

    TAF_MTC_SRV_CONN_STATE_BUTT
};
typedef VOS_UINT8 TAF_MTC_SRV_CONN_STATE_ENUM_UINT8;

/*****************************************************************************
ö����    : TAF_MTC_POWER_STATE_ENUM
�ṹ˵��  : ����״̬ö�ٶ���

  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : ����ö��
*****************************************************************************/
enum TAF_MTC_POWER_STATE_ENUM
{
    TAF_MTC_POWER_OFF                  = 0,                                     /* �ػ� */
    TAF_MTC_POWER_ON,                                                           /* ���� */

    TAF_MTC_POWER_STATE_BUTT
};
typedef VOS_UINT8 TAF_MTC_POWER_STATE_ENUM_UINT8;

/*****************************************************************************
ö����    : TAF_MTC_USIMM_CARD_SERVIC_ENUM
�ṹ˵��  : ��״̬

  1.��    ��   : 2014��06��16��
    ��    ��   : ���±�/j00174725
    �޸�����   : ����ö��
*****************************************************************************/

enum TAF_MTC_USIMM_CARD_SERVIC_ENUM
{
    TAF_MTC_USIMM_CARD_SERVIC_ABSENT        =0,                                 /* �޿� */
    TAF_MTC_USIMM_CARD_SERVIC_UNAVAILABLE   =1,                                 /* �п�,���񲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_SIM_PIN       =2,                                 /* SIM����������PIN��ԭ�򲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_SIM_PUK       =3,                                 /* SIM����������PUK��ԭ�򲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_NET_LCOK      =4,                                 /* SIM������������������ԭ�򲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_IMSI_LCOK     =5,                                 /* SIM����������IMSI����ԭ�򲻿��� */
    TAF_MTC_USIMM_CARD_SERVIC_AVAILABLE     =6,                                 /* ������� */

    TAF_MTC_USIMM_CARD_SERVIC_BUTT
};
typedef VOS_UINT16      TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16;

/*****************************************************************************
ö����    : TAF_MTC_CDMA_USIMM_CARD_ENUM
�ṹ˵��  : ��״̬

  1.��    ��   : 2014��06��16��
    ��    ��   : ���±�/j00174725
    �޸�����   : ����ö��
*****************************************************************************/

enum TAF_MTC_CDMA_USIMM_CARD_ENUM
{
    TAF_MTC_CDMA_USIMM_CARD_UNVALID        =0,                                  /* �޿� */
    TAF_MTC_CDMA_USIMM_CARD_VALID,                                              /* ������� */

    TAF_MTC_CDMA_USIMM_CARD_BUTT
};
typedef VOS_UINT8  TAF_MTC_CDMA_USIMM_CARD_ENUM_UINT8;

/*****************************************************************************
 ö����    : MTC_SESSION_TYPE_ENUM_UINT8
 ö��˵��  : SESSION����
 1.��    ��   : 2015��09��04��
   ��    ��   : j00174725
   �޸�����   : �½�

   ˵��:���ö��������ʱ��ע�ⲻҪ����32���������¼��Խ��
*****************************************************************************/
enum MTC_SESSION_TYPE_ENUM
{
    MTC_SESSION_TYPE_CS_MO_NORMAL_CALL  = 0,
    MTC_SESSION_TYPE_CS_MO_EMERGENCY_CALL,
    MTC_SESSION_TYPE_CS_MO_SS,
    MTC_SESSION_TYPE_CS_MO_SMS,
    MTC_SESSION_TYPE_CS_MT_NORMAL_CALL,
    MTC_SESSION_TYPE_CS_MT_EMERGENCY_CALLBACK,                                  /* ������eCall�Ļغ����� */
    MTC_SESSION_TYPE_CS_MT_SS,
    MTC_SESSION_TYPE_CS_MT_SMS,
    MTC_SESSION_TYPE_CS_LAU,
    MTC_SESSION_TYPE_CS_DETACH,
    MTC_SESSION_TYPE_CS_MO_NORMAL_CSFB,
    MTC_SESSION_TYPE_CS_MO_EMERGENCY_CSFB,
    MTC_SESSION_TYPE_CS_MT_CSFB,
    MTC_SESSION_TYPE_CS_LOOP_BACK,                                              /* ����ģʽ */

    MTC_SESSION_TYPE_TAU_COMBINED,                                           /* ����TAU */

    MTC_SESSION_TYPE_TAU_ONLY_EPS,                                              /* PS ONLY TAU */
    MTC_SESSION_TYPE_TAU_PERIODIC,                                              /* ������TAU */

    MTC_SESSION_TYPE_CS_BUTT,                                                   /* ���ö��֮ǰΪCS������� */

    MTC_SESSION_TYPE_PS_CONVERSAT_CALL,
    MTC_SESSION_TYPE_PS_STREAM_CALL,
    MTC_SESSION_TYPE_PS_INTERACT_CALL,
    MTC_SESSION_TYPE_PS_BACKGROUND_CALL,
    MTC_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL,
    MTC_SESSION_TYPE_PS_MO_SMS,
    MTC_SESSION_TYPE_PS_MT_SMS,
    MTC_SESSION_TYPE_PS_ATTACH,
    MTC_SESSION_TYPE_PS_RAU,
    MTC_SESSION_TYPE_PS_DETACH,
    MTC_SESSION_TYPE_1X_PS_CALL,                                                /* 1X�ϱ���PSҵ�� */

    MTC_SESSION_TYPE_BUTT                                                       /* ��MTC_SESSION_TYPE_CS_BUTT�����ö��ΪPS������� */
};
typedef VOS_UINT8 MTC_SESSION_TYPE_ENUM_UINT8;                                  /* ���ö��������ʱ��ע�ⲻҪ����32���������¼��Խ�� */

/*****************************************************************************
ö����    : MTC_CS_TYPE_ENUM
�ṹ˵��  : CSҵ������ö�ٶ���

  1.��    ��   : 2015��09��19��
    ��    ��   : j00174725
    �޸�����   : ����ö��
*****************************************************************************/
enum MTC_CS_TYPE_ENUM
{
    MTC_CS_TYPE_GU                      = 0x00,                                 /* GU�绰 */
    MTC_CS_TYPE_IMS,                                                            /* IMS�绰 */
    MTC_CS_TYPE_CDMA,                                                           /* CDMA�绰 */

    MTC_CS_TYPE_BUTT
};
typedef VOS_UINT8 MTC_CS_TYPE_ENUM_UINT8;

/*****************************************************************************
ö����    : MTC_PS_TYPE_ENUM
�ṹ˵��  : PSҵ������ö�ٶ���

  1.��    ��   : 2015��10��10��
    ��    ��   : j00174725
    �޸�����   : ����ö��

  2.��    ��   : 2015��11��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
enum MTC_PS_TYPE_ENUM
{
    MTC_PS_TYPE_GU                      = 0x00,                                /* PS */
    MTC_PS_TYPE_LTE,                                                           /* EPS */
    MTC_PS_TYPE_CDMA,                                                          /* CDMA */

    MTC_PS_TYPE_BUTT
};
typedef VOS_UINT8 MTC_PS_TYPE_ENUM_UINT8;

/*****************************************************************************
ö����    : TAF_MTC_POWER_SAVE_ENUM
�ṹ˵��  : Power Save״̬ö�ٶ���

  1.��    ��   : 2016��03��30��
    ��    ��   : j00174725
    �޸�����   : ����ö��
*****************************************************************************/
enum TAF_MTC_POWER_SAVE_ENUM
{
    TAF_MTC_POWER_SAVE                  = 0,                                    /* ����power save */
    TAF_MTC_POWER_SAVE_EXIT,                                                    /* �˳�power save */

    TAF_MTC_POWER_SAVE_BUTT
};
typedef VOS_UINT8 TAF_MTC_POWER_SAVE_ENUM_UINT8;


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
/*******************************************************************************
 �ṹ��    : TAF_MTC_CDMA_STATE_INFO_STRU
 �ṹ˵��  : CDMS״̬�ṹ��

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8       enCsConnSt;                         /* CS����״̬ */
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8       enPsConnSt;                         /* PS����״̬ */
    TAF_MTC_POWER_STATE_ENUM_UINT8          enPowerState;                       /* ���ػ�״̬ */
    VOS_UINT8                               ucReserved1[1];
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmState;                       /* ��״̬ */
    VOS_UINT8                               aucReserved2[2];
}TAF_MTC_CDMA_STATE_INFO_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MTC_CDMA_STATE_IND_STRU
 �ṹ˵��  : ID_MSG_MTC_CDMA_CONN_STATUS����Ϣ�ṹ

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_CDMA_STATE_INFO_STRU        stCdmaState;
}TAF_MTC_CDMA_STATE_IND_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MTC_SRV_CONN_STATE_INFO_STRU
 �ṹ˵��  : ID_MMA_MTC_CONN_STATUS_INFO_IND����Ϣ��Ϣ��Ԫ�ṹ

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPsSrv      : 1;
    VOS_UINT32                          bitOpCsSrv      : 1;
    VOS_UINT32                          bitOpEpsSrv     : 1;
    VOS_UINT32                          bitSpare        : 29;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enEpsSrvConnState;
    VOS_UINT8                           aucReserved[1];
}TAF_MTC_SRV_CONN_STATE_INFO_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MTC_MODEM_CONN_STATUS_IND_STRU
 �ṹ˵��  : ID_MMA_MTC_CONN_STATUS_INFO_IND����Ϣ�ṹ

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_SRV_CONN_STATE_INFO_STRU    stModemConnStateInfo;
}TAF_MTC_MODEM_CONN_STATUS_IND_STRU;

/*******************************************************************************
 �ṹ��    : TAF_MTC_USIMM_STATUS_IND_STRU
 �ṹ˵��  : ID_MMA_MTC_CONN_STATUS_INFO_IND����Ϣ�ṹ

 1.��    ��   : 2014��06��16��
   ��    ��   : j00174725
   �޸�����   : K3V3 ��ģ����������
*******************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                           stCtrl;
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimState;       /* Usim��״̬ */
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enCsimState;       /* Csim��״̬ */
}TAF_MTC_USIMM_STATUS_IND_STRU;

/*****************************************************************************
 �ṹ��    : MTC_BEGIN_SESSION_IND_STRU
 �ṹ˵��  : SESSION��ʼָʾ
 1.��    ��   : 2015��9��4��
   ��    ��   : j00174725
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType;
    VOS_UINT8                           aucReserved[3];
}MTC_BEGIN_SESSION_IND_STRU;

/*****************************************************************************
 �ṹ��    : MTC_END_SESSION_IND_STRU
 �ṹ˵��  : SESSION��ָֹʾ
 1.��    ��   : 2015��09��04��
   ��    ��   : j00174725
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    PS_BOOL_ENUM_UINT8                  enCsRelAll;
    PS_BOOL_ENUM_UINT8                  enPsRelAll;
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType;
    VOS_UINT8                           ucReserved;
}MTC_END_SESSION_IND_STRU;

/*****************************************************************************
 �ṹ��    : MTC_POWER_SAVE_IND_STRU
 �ṹ˵��  : POWER SAVEָʾ
 1.��    ��   : 2016��3��30��
   ��    ��   : j00174725
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    TAF_CTRL_STRU                       stCtrl;
    TAF_MTC_POWER_SAVE_ENUM_UINT8       enPowerSaveStatus;
    VOS_UINT8                           aucReserved[3];
}MTC_POWER_SAVE_IND_STRU;




/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    TAF_MTC_MSG_ID_ENUM_UINT32          ulMsgId;                                /*_H2ASN_MsgChoice_Export TAF_MTC_MSG_ID_ENUM_UINT32*/
    VOS_UINT8                           aucMsgBlock[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          TAF_MTC_MSG_ID_ENUM_UINT32
    ****************************************************************************/
}TAF_MTC_MSG_REQ;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    TAF_MTC_MSG_REQ                     stMsgReq;
}TafMtcApi_MSG;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MTC_SndMsg
 ��������  : ����MTC��Ϣ
 �������  : VOS_UINT32                          ulTaskId
             VOS_UINT32                          ulMsgId
             VOS_VOID                           *pData
             VOS_UINT32                          ulLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MTC_SndMsg(
    VOS_UINT32                          ulTaskId,
    VOS_UINT32                          ulMsgId,
    VOS_VOID                           *pData,
    VOS_UINT32                          ulLength
);

/*****************************************************************************
 �� �� ��  : MTC_SetCdmaServiceConnStateInfo
 ��������  : �����ⲿCDMA Modem������״̬(PS&CS)
 �������  : pstCtrl                    - ����ͷ
             pstCdmsStatus              - ״̬��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_OK                     - ������Ϣ�ɹ�
             VOS_ERR                    - ������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MTC_SetCdmaServiceConnStateInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_CDMA_STATE_INFO_STRU       *pstCdmsState
);

/*****************************************************************************
 �� �� ��  : MTC_SetModemServiceConnState
 ��������  : ����modem״̬��Ϣ
 �������  : ulModuleId      ģ��ID
             pstModemConnSt  ״̬��Ϣָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_UINT32 MTC_SetModemServiceConnState(
    TAF_CTRL_STRU                      *pstCtrl,
    TAF_MTC_SRV_CONN_STATE_INFO_STRU   *pstModemConnSt
);

/*****************************************************************************
 �� �� ��  : MTC_SetModemUsimmState
 ��������  : ���ÿ�״̬��Ϣ
 �������  : pstCtrl         ��Ϣ����ͷ
             pstModemConnSt  ״̬��Ϣָ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������

  2.��    ��   : 2015��10��21��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_UINT32 MTC_SetModemUsimmState(
    TAF_CTRL_STRU                           *pstCtrl,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enUsimState,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16    enCsimState
);

VOS_VOID MTC_SetBeginSessionInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);

VOS_VOID MTC_SetEndSessionInfo(
    TAF_CTRL_STRU                      *pstCtrl,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
);

VOS_VOID MTC_SetPowerSaveInfo(
    VOS_UINT32                          ulSndpid,
    TAF_MTC_POWER_SAVE_ENUM_UINT8       enPowerSaveStatus
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

#endif

