

/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : pamappom.h
  �� �� ��      : ����
  ��    ��      : H00300778
  ��������      : 2015��6��24��
  ����޸�      :
  ��������      : ��h�ļ�������pamappom.c��ͷ�ļ�
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2015��6��24��
    ��    ��    : H00300778
    �޸�����    : �����ļ�

******************************************************************************/


#ifndef __PAMAPPOM_H__
#define __PAMAPPOM_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "msp_diag_comm.h"
#include "mdrv.h"


/*****************************************************************************
  2 �궨��
******************************************************************************/
#define  OM_ICC_LOG_PATH                "/data/modemlog/Log/Icc-log"
#define  OM_ICC_UNITARY_LOG_PATH        "/modem_log/Log/Icc-log"

#define OM_ICC_BUFFER_SIZE              (16*1024)

#define OM_DRV_MAX_IO_COUNT             (8)        /*һ���ύ������ӿڵ������Ŀ*/

#define OM_ICC_CHANNEL_PRIORITY         (0)

#define OM_ICC_HANDSHAKE_TIME_MAX       (200000)

#define OM_LOG_FILE_MAX_SIZE            (0x40000)

/* AT<->AT�����δ����Ƶ�GuNasLogFilter.c */

#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
#define OSA_ICC_BUFFER_SIZE                                     (128*1024)
#else
#define OSA_ICC_BUFFER_SIZE                                     (64*1024)
#endif  /* ( FEATURE_MULTI_MODEM == FEATURE_ON ) */

/*******************************************************************************
  3 ö�ٶ���
*****************************************************************************/


enum OM_DATA_DESTINATION_ENUM
{
    OMRL_UART = 0,              /*������*/
    OMRL_USB,                   /*USBͨ��*/
    OMRL_FS,                    /*д�ļ�ϵͳ*/
    OMRL_WIFI,                  /*SOCKET WIFIͨ��*/
    OMRL_SD,                    /*дSD��*/
    OMRL_PORT_BUTT
};
typedef VOS_UINT16 OM_DATA_DESTINATION_ENUM_UIN16;
typedef VOS_UINT32 OM_DATA_DESTINATION_ENUM_UIN32;

enum OM_USB_PORT_ENUM
{
    OMRL_USB_OM = 1,            /*OM����˿�*/
    OMRL_USB_AT,                /*AT����˿�*/
    OMRL_USB_SHELL,             /*shell����˿�*/
    OMRL_USB_CONTROL = 5,
    OMRL_USB_BUTT
};
typedef VOS_UINT16 OM_USB_PORT_ENUM_UINT16;
typedef VOS_UINT32 OM_USB_PORT_ENUM_UINT32;

enum OM_ICC_CHANNEL_ENUM
{
    OM_OM_ICC_CHANNEL           = 0,    /*��ǰͨ�����ڴ���OM����*/
    OM_OSA_MSG_ICC_CHANNEL,             /*��ǰͨ�����ڴ���OSA����Ϣ����*/
    OM_ICC_CHANNEL_BUTT
};
typedef VOS_UINT32 OM_ICC_CHANNEL_ENUM_UINT32;

/*����ICCͨ��UDI��������Ƭ�ṹ*/
typedef struct
{
    VOS_UINT32                      enICCId;        /*������ĵ�ǰͨ����*/
    ICC_CHAN_ATTR_S                *pstICCAttr;     /*��ǰͨ������*/
}OM_ICC_UDI_CTRL_STRU;

typedef struct
{
   VOS_UINT16                       usSendPid;
   VOS_UINT16                       usRcvPid;
   VOS_UINT32                       ulMsgName;
   VOS_UINT32                       ulSliceStart;
   VOS_UINT32                       ulSliceEnd;
}OM_RECORD_INFO_STRU;

typedef struct
{
   VOS_UINT8                       *pucBuf;
   VOS_UINT32                       ulLen;
   VOS_UINT8                        aucRsv[4];
}OM_RECORD_BUF_STRU;

typedef struct
{
    VOS_MSG_HEADER
}OM_FILTER_MSG_HEAD_STRU;

/*****************************************************************************
  4 STRUCT����
*****************************************************************************/


/*****************************************************************************
  5 �ӿڶ���
*****************************************************************************/
extern VOS_UINT V_ICC_OSAMsg_CB(VOS_UINT ulChannelID,VOS_INT lLen);

extern VOS_UINT32 VOS_GetMsgName(VOS_UINT32 ulAddrress);

extern VOS_VOID Om_AcpuQueryDumpMsgProc(MsgBlock* pMsg);

extern VOS_VOID  Om_AcpuPhyMsgProc( MsgBlock* pMsg );

/* AT<->AT�����δ����Ƶ�GuNasLogFilter.c */

#if (VOS_WIN32 == VOS_OS_VER)
#define PS_LOG(ModulePID, SubMod, Level, String)\
        vos_printf("\r\n%s",   String)

#define PS_LOG1(ModulePID, SubMod, Level, String, Para1)\
        vos_printf("\r\n%s,para1=%d", String, Para1)

#define PS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)\
        vos_printf("\r\n%s,para1=%d,para2=%d", String, Para1, Para2)

#define PS_LOG3(ModulePID, SubMod, Level, String, Para1, Para2, Para3)\
        vos_printf("\r\n%s,para1=%d,para2=%d,para3=%d", String, Para1, Para3)

#define PS_LOG4(ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4)\
        vos_printf("\r\n%s,para1=%d,para2=%d,para3=%d,para4=%d", String, Para1, Para3, Para4)

#else
#define PS_LOG(ModulePID, SubMod, Level, String)

#define PS_LOG1(ModulePID, SubMod, Level, String, Para1)

#define PS_LOG2(ModulePID, SubMod, Level, String, Para1, Para2)

#define PS_LOG3(ModulePID, SubMod, Level, String, Para1, Para2, Para3)

#define PS_LOG4(ModulePID, SubMod, Level, String, Para1, Para2, Para3, Para4)

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __PAMAPPOM_H__ */
