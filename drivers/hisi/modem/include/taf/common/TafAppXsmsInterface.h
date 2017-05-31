

#ifndef _TAF_APP_XSMS_INTERFACE_H_
#define _TAF_APP_XSMS_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafTypeDef.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define TAF_XSMS_ADDRESS_MAX            36         /* Ril�·��ĵ�ַ��󳤶� */
#define TAF_XSMS_SUBADDRESS_MAX         36         /* Ril�·����ӵ�ַ��󳤶� */
#define TAF_XSMS_BEARER_DATA_MAX        255        /* Ril�·���USER DATA��󳤶� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : TAF_XSMS_DIGITMODE_ENUM_UINT8
 ö��˵��  : ��ַ��digit mode
*****************************************************************************/
enum TAF_XSMS_DIGITMODE_ENUM
{
    TAF_XSMS_DIGIT_MODE_4_BIT = 0,     /* DTMF digits */
    TAF_XSMS_DIGIT_MODE_8_BIT = 1,
    TAF_XSMS_DIGIT_MODE_BUTT  = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_DIGITMODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_NUMBERMODE_ENUM_UINT8
 ö��˵��  : ��ַ��number mode
*****************************************************************************/
enum TAF_XSMS_NUMBERMODE_ENUM
{
    TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK = 0,
    TAF_XSMS_NUMBER_MODE_DATA_NETWORK     = 1,
    TAF_XSMS_NUMBER_MODE_BUFF             = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_NUMBERMODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_NUMBERTYPE_ENUM_UINT8
 ö��˵��  : ��ַ��number type
*****************************************************************************/
enum TAF_XSMS_NUMBERTYPE_ENUM
{
    TAF_XSMS_NUMBER_TYPE_UNKNOWN                   = 0,
   /* INTERNATIONAL is used when number mode is not data network address.
    * DATA_IP is used when the number mode is data network address
    */
    TAF_XSMS_NUMBER_TYPE_INTERNATIONAL_OR_DATA_IP  = 1,
   /* NATIONAL is used when the number mode is not data network address.
    * INTERNET_MAIL is used when the number mode is data network address.
    * For INTERNET_MAIL, in the address data "digits", each byte contains
    * an ASCII character. Examples are "x@y.com,a@b.com - ref TIA/EIA-637A 3.4.3.3
    */
    TAF_XSMS_NUMBER_TYPE_NATIONAL_OR_INTERNET_MAIL = 2,
    TAF_XSMS_NUMBER_TYPE_NETWORK                   = 3,
    TAF_XSMS_NUMBER_TYPE_SUBSCRIBER                = 4,
    /* GSM SMS: address value is GSM 7-bit chars */
    TAF_XSMS_NUMBER_TYPE_ALPHANUMERIC              = 5,
    TAF_XSMS_NUMBER_TYPE_ABBREVIATED               = 6,
    TAF_XSMS_NUMBER_TYPE_RESERVED_7                = 7,
    TAF_XSMS_NUMBER_TYPE_BUFF                      = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_NUMBERTYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_NUMBERPLAN_ENUM_UINT8
 ö��˵��  : ��ַ��number plan
*****************************************************************************/
enum TAF_XSMS_NUMBERPLAN_ENUM
{
    TAF_XSMS_NUMBER_PLAN_UNKNOWN     = 0,
    TAF_XSMS_NUMBER_PLAN_TELEPHONY   = 1,      /* CCITT E.164 and E.163, including ISDN plan */
    TAF_XSMS_NUMBER_PLAN_RESERVED_2  = 2,
    TAF_XSMS_NUMBER_PLAN_DATA        = 3,      /* CCITT X.121 */
    TAF_XSMS_NUMBER_PLAN_TELEX       = 4,      /* CCITT F.69 */
    TAF_XSMS_NUMBER_PLAN_RESERVED_5  = 5,
    TAF_XSMS_NUMBER_PLAN_RESERVED_6  = 6,
    TAF_XSMS_NUMBER_PLAN_RESERVED_7  = 7,
    TAF_XSMS_NUMBER_PLAN_RESERVED_8  = 8,
    TAF_XSMS_NUMBER_PLAN_PRIVATE     = 9,
    TAF_XSMS_NUMBER_PLAN_RESERVED_10 = 10,
    TAF_XSMS_NUMBER_PLAN_RESERVED_11 = 11,
    TAF_XSMS_NUMBER_PLAN_RESERVED_12 = 12,
    TAF_XSMS_NUMBER_PLAN_RESERVED_13 = 13,
    TAF_XSMS_NUMBER_PLAN_RESERVED_14 = 14,
    TAF_XSMS_NUMBER_PLAN_RESERVED_15 = 15,
    TAF_XSMS_NUMBER_PLAN_BUFF        = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_NUMBERPLAN_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_SUBADDR_TYPE_ENUM_UINT8
 ö��˵��  : �ӵ�ַ����
*****************************************************************************/
enum TAF_XSMS_SUBADDR_TYPE_ENUM
{
    TAF_XSMS_SUBADDRESS_TYPE_NSAP           = 0,    /* CCITT X.213 or ISO 8348 AD2 */
    TAF_XSMS_SUBADDRESS_TYPE_USER_SPECIFIED = 1,    /* e.g. X.25 */
    TAF_XSMS_SUBADDRESS_TYPE_MAX32          = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_SUBADDR_TYPE_ENUM_UINT8;


/*****************************************************************************
 ö����    : TAF_XSMS_STATUS_ENUM_UINT8
 ö��˵��  : ����״̬
*****************************************************************************/
/* ���ֵ��GU�Ķ�����һ������UIM����Ķ��岻�������� */
enum TAF_XSMS_STATUS_ENUM
{
    TAF_XSMS_STATUS_REC_UNREAD         = 0,
    TAF_XSMS_STATUS_REC_READ           = 1,
    TAF_XSMS_STATUS_STO_UNSEND         = 2,
    TAF_XSMS_STATUS_STO_SEND           = 3,
    TAF_XSMS_STATUS_BUTT               = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_SEND_OPTION_ENUM8
 ö��˵��  : SMS���ŷ������ͣ�������Ⱥ��
*****************************************************************************/
enum TAF_XSMS_SEND_OPTION_ENUM
{
    TAF_XSMS_SEND_OPTION_SINGLE        = 0,
    TAF_XSMS_SEND_OPTION_MULTI         = 1,
    TAF_XSMS_SEND_OPTION_BUTT          = 0xFF,
};

typedef VOS_UINT8  TAF_XSMS_SEND_OPTION_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_AP_MEM_FULL_ENUM8
 ö��˵��  : SMS���ŷ������ͣ�������Ⱥ��
*****************************************************************************/
enum TAF_XSMS_AP_MEM_FULL_ENUM
{
    TAF_XSMS_AP_MEM_FULL             = 0,
    TAF_XSMS_AP_MEM_NOT_FULL         = 1,
    TAF_XSMS_AP_MEM_BUTT,
};

typedef VOS_UINT8  TAF_XSMS_AP_MEM_FULL_ENUM_UINT8;


/*****************************************************************************
 ö����    : TAF_XSMS_APP_MSG_TYPE_ENUM32
 ö��˵��  : SMS��APPC����Ϣ����
*****************************************************************************/
enum TAF_XSMS_APP_MSG_TYPE_ENUM
{
    TAF_XSMS_APP_MSG_TYPE_INIT_IND         = 0,
    TAF_XSMS_APP_MSG_TYPE_SEND_REQ         = 1,
    TAF_XSMS_APP_MSG_TYPE_SEND_CNF         = 2,
    TAF_XSMS_APP_MSG_TYPE_WRITE_REQ        = 3,
    TAF_XSMS_APP_MSG_TYPE_WRITE_CNF        = 4,
    TAF_XSMS_APP_MSG_TYPE_DELETE_REQ       = 5,
    TAF_XSMS_APP_MSG_TYPE_DELETE_CNF       = 6,
    TAF_XSMS_APP_MSG_TYPE_SEND_SUCC_IND    = 7,
    TAF_XSMS_APP_MSG_TYPE_SEND_FAIL_IND    = 8,
    TAF_XSMS_APP_MSG_TYPE_RCV_IND          = 9,
    TAF_XSMS_APP_MSG_TYPE_UIM_FULL_IND     = 10,
    TAF_XSMS_APP_MSG_TYPE_UIM_MEM_SET_REQ  = 11,
    TAF_XSMS_APP_MSG_TYPE_UIM_MEM_FULL_CNF = 12,

    TAF_XSMS_APP_MSG_TYPE_BUTT
};

typedef VOS_UINT32  TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32;

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
 �ṹ��    :TAF_XSMS_ADDR_STRU
 �ṹ˵��  :Ril�·��ĵ�ַ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    /* Indicates 4-bit or 8-bit */
    TAF_XSMS_DIGITMODE_ENUM_UINT8       enDigitMode;
    /* Used only when digitMode is 8-bit */
    TAF_XSMS_NUMBERMODE_ENUM_UINT8      enNumberMode;
    /* Used only when digitMode is 8-bit.
     * To specify an international address, use the following:
     * digitMode = TAF_XSMS_DIGIT_MODE_8_BIT
     * numberMode = TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK
     * numberType = TAF_XSMS_NUMBER_TYPE_INTERNATIONAL_OR_DATA_IP
     * numberPlan = TAF_XSMS_NUMBER_PLAN_TELEPHONY
     * numberOfDigits = number of digits
     * digits = ASCII digits, e.g. '1', '2', '3'3, '4', and '5'
     */
    TAF_XSMS_NUMBERTYPE_ENUM_UINT8      enNumberType;
    /* Used only when digitMode is 8-bit */
    TAF_XSMS_NUMBERPLAN_ENUM_UINT8      enNumberPlan;
    VOS_UINT32                          ulNumberOfDigits;
    VOS_UINT8                           aucDigits[TAF_XSMS_ADDRESS_MAX];
}TAF_XSMS_ADDR_STRU;

/*****************************************************************************
 �ṹ��    :TAF_XSMS_SUB_ADDR_STRU
 �ṹ˵��  :Ril�·����ӵ�ַ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    TAF_XSMS_SUBADDR_TYPE_ENUM_UINT8    enSubAddrType;
    /* 1 means the last byte's lower 4 bits should be ignored */
    VOS_UINT8                           ucOdd;
    VOS_UINT8                           ucNumberOfDigits;
    VOS_UINT8                           ucRsv;
    /* Each byte respresents a 8-bit digit of subaddress data */
    VOS_UINT8                           aucDigits[TAF_XSMS_SUBADDRESS_MAX];
}TAF_XSMS_SUB_ADDR_STRU;

/*****************************************************************************
 �ṹ��    :TAF_XSMS_MESSAGE_STRU
 �ṹ˵��  :Ril�·���Xģ�������ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTeleserviceID;
    VOS_BOOL                            bIsServicePresent;
    VOS_UINT32                          ulServiceCategory;
    TAF_XSMS_ADDR_STRU                  stAddr;
    TAF_XSMS_SUB_ADDR_STRU              stSubAddr;
    VOS_UINT32                          ulBearerDataLen;
    VOS_UINT8                           aucBearerData[TAF_XSMS_BEARER_DATA_MAX + 1];
}TAF_XSMS_MESSAGE_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_APP_MSG_REQ_STRU
 �ṹ˵��  : ����APP�ķ��Ͷ���������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MN_CLIENT_ID_T                      usClientId;     /* Client ID */
    MN_OPERATION_ID_T                   ucOpId;         /* Operation ID */
    TAF_XSMS_SEND_OPTION_ENUM_UINT8     enSndOption;    /* ������Ⱥ�� */
    TAF_XSMS_MESSAGE_STRU               st1XSms;
}TAF_XSMS_SEND_MSG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_APP_MSG_SET_AP_MEM_FULL_REQ_STRU
 �ṹ˵��  : ����APP�ķ��Ͷ���������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MN_CLIENT_ID_T                      usClientId;         /* Client ID */
    MN_OPERATION_ID_T                   ucOpId;             /* Operation ID */
    TAF_XSMS_AP_MEM_FULL_ENUM_UINT8     enApMemFullFlag;
}TAF_XSMS_APP_MSG_SET_AP_MEM_FULL_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_APP_MSG_REQ_STRU
 �ṹ˵��  : ����APP�ĸ��¶���������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MN_CLIENT_ID_T                      usClientId;   /* Client ID */
    MN_OPERATION_ID_T                   ucOpId;       /* Operation ID */
    TAF_XSMS_STATUS_ENUM_UINT8          enSmsStatus;
    TAF_XSMS_MESSAGE_STRU               st1XSms;
}TAF_XSMS_WRITE_MSG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_DELETE_MSG_REQ_STRU
 �ṹ˵��  : ����APP��ɾ������������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    MN_CLIENT_ID_T                      usClientId;   /* Client ID */
    MN_OPERATION_ID_T                   ucOpId;       /* Operation ID */
    VOS_UINT8                           ucIndex;
}TAF_XSMS_DELETE_MSG_REQ_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_INIT_IND_STRU
 �ṹ˵��  : XSMS��AT�ϱ��ĳ�ʼ������¼��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTotalNum;   /* �ܼ�¼�� */
}TAF_XSMS_INIT_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_WRITE_CNF_STRU
 �ṹ˵��  : XSMS��AT�ϱ���д������¼��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIndex;    /* ����д��ɹ�ʱ������ֵ����1��ʼ */
}TAF_XSMS_WRITE_CNF_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_SEND_SUCC_IND_STRU
 �ṹ˵��  : XSMS��AT�ϱ��Ķ��ŷ��ͳɹ��¼��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMr;       /* ���ض��ŷ��ͳɹ�ʱ��MESSAGE ID */
}TAF_XSMS_SEND_SUCC_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_SEND_SUCC_IND_STRU
 �ṹ˵��  : XSMS��AT�ϱ��Ķ��ŷ���ʧ���¼��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCourseCode;   /* ���ض��ŷ���ʧ��ʱ��Course Code */
}TAF_XSMS_SEND_FAIL_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_RCV_IND_STRU
 �ṹ˵��  : XSMS��AT�ϱ��Ķ��Ž����¼��ṹ
*****************************************************************************/
typedef struct
{
    TAF_XSMS_MESSAGE_STRU              stRcvMsg;       /* ���յ��Ķ���PDU��ʽ */
}TAF_XSMS_RCV_IND_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_AT_EVENT_INFO_STRU
 �ṹ˵��  : XSMS��AT�ϱ����¼��ṹ
*****************************************************************************/
typedef struct
{
    MN_CLIENT_ID_T                      usClientId;
    MN_OPERATION_ID_T                   ucOpId;
    VOS_UINT8                           ucRsv;
    VOS_UINT32                          ulError;
    union
    {
        TAF_XSMS_INIT_IND_STRU          stInitInd;
        TAF_XSMS_WRITE_CNF_STRU         stWriteCnf;
        TAF_XSMS_SEND_SUCC_IND_STRU     stSndSuccInd;
        TAF_XSMS_SEND_FAIL_IND_STRU     stSndFailInd;
        TAF_XSMS_RCV_IND_STRU           stRcvInd;
    }XSmsEvent;
}TAF_XSMS_APP_AT_EVENT_INFO_STRU;


/*****************************************************************************
 �ṹ��    : TAF_XSMS_AT_CNF_STRU
 �ṹ˵��  : XSMS��AT�ϱ�����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_XSMS_APP_MSG_TYPE_ENUM_UINT32   enEventType;
    TAF_XSMS_APP_AT_EVENT_INFO_STRU     stXsmsAtEvent;
}TAF_XSMS_APP_AT_CNF_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 TAF_XSMS_SendSmsReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_XSMS_SEND_OPTION_ENUM_UINT8     enSndOption,
    VOS_UINT8                          *pucData);

extern VOS_UINT32  TAF_XSMS_SetXsmsApMemFullReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucApMemFullFlag);

extern VOS_UINT32 TAF_XSMS_WriteSmsReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    TAF_XSMS_STATUS_ENUM_UINT8          enStatus,
    VOS_UINT8                          *pucData);

extern VOS_UINT32 TAF_XSMS_DeleteSmsReq(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT8                           ucIndex);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

