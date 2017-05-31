
#ifndef __TAF_TAFM_REMOTE_H__
#define __TAF_TAFM_REMOTE_H__

#ifdef __cplusplus
extern "C" {
#endif
#pragma pack(4)
/*========================================================*/

#include "TafApi.h"

/*�궨�忪ʼ*/

/*����Client�Ĺ㲥ֵ*/
#define TAF_CLIENTID_BROADCAST          (0xFFFF)
#define MN_CLIENTID_INVALID             (0xFFFE)


/*CS����PS���֧�ֵ�RAB��Ŀ*/
#define  TAF_MAX_RABID                15


#define TAF_MSG_HEADER_LEN  6

#ifndef TAF_SUCCESS
#define TAF_SUCCESS    TAF_ERR_NO_ERROR     /*����ִ�гɹ�*/
#endif
#ifndef TAF_FAILURE
#define TAF_FAILURE    TAF_ERR_ERROR        /*����ִ��ʧ��*/
#endif

#define PS_INIT_NOT_START  0
#define PS_INIT_START      1
#define PS_INIT_FINISH     2

/*�궨�����*/

/*Զ��API��TAFM����ͨ��ʱʹ�õ���Ϣ����*/
/*********************************************************
1.��    ��   : 2012��12��10��
  ��    ��   : w00176964
  �޸�����   : ����ACINFO��������Ĳ�ѯ��Ϣ
2.��    ��   : 2013��05��06��
  ��    ��   : f62575
  �޸�����   : SS FDN&Call Control��Ŀ��ɾ��TAF_MSG_GETPWD_MSG������TAF_MSG_MMA_COPN_INFO_QUERY_REQ
**********************************************************/

typedef enum
{

    TAF_MSG_MMA_USIM_RESTRICTED_ACCESS, /*+CRSM*/


    TAF_MSG_PARA_READ,            /* ͨ�Ų�����ѯ*/

    /*�绰����*/
    TAF_MSG_MMA_PLMN_LIST,        /* ����PLMN��������չ����*/


    TAF_MSG_MMA_OP_PIN_REQ,       /* PIN��������*/
    TAF_MSG_MMA_ATTACH,           /* �������Ź���*/
    TAF_MSG_MMA_DETACH,           /* ����ȥ���Ź���*/


    TAF_MSG_MMA_ME_PERSONAL_REQ,   /* ������������ */

    /* Added by C00173809 for AT Project��2011-10-08,  Begin*/
    TAF_MSG_MMA_GET_CURRENT_ATTACH_STATUS,      /*�����ȡCS��PS��ע��״̬*/

    /* Deleted SSA��Ϣ */

    TAF_MSG_MMA_USIM_INFO,
    TAF_MSG_MMA_CPNN_INFO,

    /* Added by C00173809 for AT Project��2011-11-03,  Begin*/
    TAF_MSG_MMA_SET_PIN,
    /* Added by C00173809 for AT Project��2011-11-03,  End*/


    TAF_MSG_MMA_COPS_FORMAT_TYPE_SET_REQ,
    TAF_MSG_MMA_USIM_STUB_SET_REQ,
    TAF_MSG_MMA_REFRESH_STUB_SET_REQ,
    TAF_MSG_MMA_AUTO_RESEL_STUB_SET_REQ,

    TAF_MSG_BUTT
}TAF_MSG_TYPE;
typedef VOS_UINT16   TAF_MSG_TYPE_ENUM_U16;


/*TAF��������������Ϣ���Ͷ���*/
typedef enum
{
    TAF_SUB_MSG_PARA_SET,     /*ͨ�Ų�������*/
    TAF_SUB_MSG_PARA_READ,    /*ͨ�Ų�����ѯ*/
    TAF_SUB_MSG_BUTT
}TAF_PRIM_MSG_TYPE;


/*ȫ�ֱ������忪ʼ*/
/*Զ��API����ȫ�ֱ�������*/
/*APP/AT�ص�������¼��*/


/*ȫ�ֱ����������*/

/*API�����궨��*/
#define TAF_ENCODE_MSG_HEADER(ptr, MsgType, ClientId, Id, IeMask)  \
                         *ptr++ = MsgType;                         \
                         *ptr++ = (VOS_UINT8)((ClientId >> 8) & 0xFF); \
                         *ptr++ = (VOS_UINT8)(ClientId & 0xFF);        \
                         *ptr++ = Id;                              \
                         *ptr++ = (VOS_UINT8)((IeMask >> 8) & 0xFF);   \
                         *ptr++ = (VOS_UINT8)(IeMask & 0xFF)


/*TAF�Ƿ��Ѿ���Զ��ע���MUX�ص�����*/
#define TAF_REG_MUX_CALLBACK_NO    0   /*δע���MUX�ص�����*/
#define TAF_REG_MUX_CALLBACK_YES   1   /*��ע���MUX�ص�����*/

VOS_VOID   Taf_EventReportProc(VOS_UINT16 usMuxId, VOS_UINT8 *pData, VOS_UINT16 usLen, VOS_UINT8 ucRegTabIndex);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

/*========================================================*/
#ifdef __cplusplus
}
#endif
/******************************************************************************/

/*============================================================================*/
#endif          /* __TAF_REMOTE_H__ */
