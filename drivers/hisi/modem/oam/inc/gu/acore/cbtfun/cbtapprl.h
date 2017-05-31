

/******************************************************************************

                  ��Ȩ���� (C), 2015-2025, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Cbtapprl.h
  �� �� ��   : ����
  ��    ��   : x00263027
  ��������   : 2015��3��2��
  ����޸�   :
  ��������   : Cbtapprl.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��2��
    ��    ��   : x00263027
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CBT_APPRL_H__
#define __CBT_APPRL_H__

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "cbtrl.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif





extern VOS_UINT32                       g_ulCbtAcpuDbgFlag;


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define CBT_MSG_FIRST_BYTE                  (0x07)
#define BIT_LEFTMOVE_N(num)                 (0x01 <<( num))
#define CBT_ACPU_VCOM_CB                    BIT_LEFTMOVE_N(0)
#define CBT_ACPU_DISPATCH_MSG               BIT_LEFTMOVE_N(1)
#define CBT_ACPU_USB_CB                     BIT_LEFTMOVE_N(2)
/* datatype �ֶγ��� */
#define CBT_RL_DATATYPE_LEN                 (0x1)
#define CBT_HDLC_FCS_LEN                    (2)           /* HDLC֡��FCSδת��ʱ�ĳ���(��λ: Byte) */
#define CBT_HDLC_BUF_MAX_LEN                (CBT_MSG_SEGMENT_LEN + CBT_RL_DATATYPE_LEN + CBT_HDLC_FCS_LEN)

/*ֵΪCBT_READ_NV_IND_STRU�ṹ���У�sizeof(ulErrorCode) + sizeof(ulNvId) + sizeof(ulCount)*/
#define CBT_READ_NV_HEAD_SIZE               (12)
#define CBT_WRITE_NV_HEAD_SIZE              (8)
/*����ΪNVID��ֵ+NVID������ռ�ڴ泤��*/
#define CBT_NV_ITEM_SIZE                    (4)
#define CBT_IND_RESULT_SIZE                 (4)
#define CBT_EST_IND_CHIP_ID_SIZE            (4)
#define CBT_EST_IND_RSV_LEN                 (252)


#define CBT_END_FRAME                       (1)
/*#define SEG_MAX_LEN                         (4*1024)*/
/*#define MAXSEGMENT                          (16)*/
/*��������󳤶�*/
#define CBT_TOTAL_MSG_MAX_LEN               (20*1024)/*(SEG_MAX_LEN + (SEG_MAX_LEN-CBT_MSG_HEADER_LENGTH)*(MAXSEGMENT-1))*/

#define OM_CBT_SEND_DATA_REQ                (0x030d)



#define CBT_ACPU_DEBUG_TRACE(pucData, ulDataLen, ulSwitch) \
    if(VOS_FALSE != (g_ulCbtAcpuDbgFlag&ulSwitch)) \
    { \
        VOS_UINT32 ulOmDbgIndex; \
        vos_printf("\n%s, Data Len: = %d\n", __FUNCTION__, ulDataLen); \
        for (ulOmDbgIndex = 0 ; ulOmDbgIndex < ulDataLen; ulOmDbgIndex++) \
        { \
            vos_printf("%02x ", *((VOS_UINT8*)pucData + ulOmDbgIndex)); \
        } \
        vos_printf("\r\n"); \
    } \


/*OM<->APP : Restablish link*/
#define APP_OM_ESTABLISH_REQ                      0x80b1
#define OM_APP_ESTABLISH_CNF                      0x80b2

/*OM<->APP : Release link*/
#define APP_OM_RELEASE_REQ                        0x80b3
#define OM_APP_RELEASE_CNF                        0x80b4

#define APP_OM_READ_NV_REQ                        0x8021

#define OM_APP_READ_NV_IND                        0x8022

#define APP_OM_WRITE_NV_REQ                       0x8023
#define OM_APP_WRITE_NV_CNF                       0x8024


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT32 ulResult;                            /*����ִ�н��*/
    VOS_UINT32 ulChipId;
    VOS_UINT8  ausReserve[CBT_EST_IND_RSV_LEN];
}CBT_ESTABLISH_IND_STRU;

typedef struct
{
    VOS_UINT32 ulCount;             /*Ҫ��ȡ��NV�����*/
    VOS_UINT16 ausNvItemId[2];      /*Ҫ��ȡ��NV��ID���飬���и���ΪulCount*/
}CBT_READ_NV_REQ_STRU;

typedef struct
{
    VOS_UINT32 ulErrorCode;        /*����ִ�н��*/
    VOS_UINT32 ulErrNvId;          /*���س��ִ����NVID*/
    VOS_UINT32 ulCount;            /*���ص�NV�����*/
    VOS_UINT16 ausNVItemData[2];   /*����NVIDֵ��NVID���ݵĳ��ȡ�NVID������*/
}CBT_READ_NV_IND_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHead;
    VOS_UINT16                  usMsgId;      /* ��ϢID */
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;

    VOS_UINT32                  ulErrorCode;        /*����ִ�н��*/
    VOS_UINT32                  ulErrNvId;          /*���س��ִ����NVID*/
    VOS_UINT32                  ulCount;            /*���ص�NV�����*/
}CBT_READ_NV_CNF_STRU;

typedef struct
{
    VOS_UINT32 ulCount;             /*Ҫд���NV�����*/
    VOS_UINT16 ausNvItemData[2];    /*����NVIDֵ��NVID���ݵĳ��ȡ�NVID������*/
}CBT_WRITE_NV_REQ_STRU;

typedef struct
{
    CBT_MSG_HEAD_STRU           stMsgHead;
    VOS_UINT16                  usMsgId;      /* ��ϢID */
    CBT_COMPONENT_MODE_STRU     stCompMode;
    VOS_UINT32                  ulMsgLength;

    VOS_UINT32                  ulErrorCode;        /*����ִ�н��*/
    VOS_UINT32                  ulErrNvId;          /*���س��ִ����NVID*/
}CBT_WRITE_NV_CNF_STRU;

/*****************************************************************************
�ṹ��    : OMRL_CBT_HDLC_ENCODE_MEM_CTRL
�ṹ˵��  : OMRL CBTУ׼ͨ��HDLC����������Ϣ�ṹ(uncache)
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          *pucBuf;         /* ָ�򻺳��������׵�ַ */
    VOS_UINT8                          *pucRealBuf;     /* ָ�򻺳���ʵ�׵�ַ */
    VOS_UINT32                          ulBufSize;      /* ���滺�����ܴ�С */
    VOS_UINT32                          ulRsv;          /* Reserve */
}CBT_HDLC_ENCODE_MEM_CTRL;

/*****************************************************************************
�ṹ��    : OM_ACPU_ICC_SEND_FAIL_STRU
�ṹ˵��  : ACPU ICCͨ������ʧ�ܵĿ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulICCOmSendErrNum;      /*��ǰ���͵Ĵ����¼*/
    VOS_UINT32                          ulICCOmSendErrLen;      /*��ǰ���͵Ĵ�������Ϣ����*/
    VOS_UINT32                          ulICCOmSendErrSlice;    /*��ǰ���͵Ĵ�����Ϣ���һ�����ݵ�ʱ��*/
}CBT_ACPU_ICC_SEND_FAIL_STRU;

/*****************************************************************************
�ṹ��    : OM_ACPU_ICC_SEND_SUC_STRU
�ṹ˵��  : ACPU ICCͨ���ɹ����͵Ŀ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulICCOmSendMsgNum;      /*��ǰ���͵�����Ϣ��*/
    VOS_UINT32                          ulICCOmSendLen;         /*��ǰ���͵�����Ϣ����*/
    VOS_UINT32                          ulICCOmSendSlice;       /*��ǰ���͵����һ�����ݵ�ʱ��*/
}CBT_ACPU_ICC_SEND_SUC_STRU;

/*****************************************************************************
�ṹ��    : OM_MAINTENANCE_INFO_STRU
�ṹ˵��  : OMģ���ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataLen; /* ���ջ������ݳ��� */
    VOS_UINT32                          ulNum;     /* ���ջ������ݴ��� */
}CBT_MAINTENANCE_INFO_STRU;

/*****************************************************************************
�ṹ��    : OM_ACPU_PC_UE_RELEASE_INFO_STRU
�ṹ˵��  : OMģ�����������Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRlsAp2Modem;     /* AP��Modem�л� */
    VOS_UINT32                          ulRlsModem2Ap;     /* Modem��AP�л� */
    VOS_UINT32                          ulRlsDrvSuspend;   /* DRV���� */
    VOS_UINT32                          ulRlsPortClose;    /* �˿ڹر� */
    VOS_UINT32                          ulRlsPortSwitch;   /* �˿��л� */
    VOS_UINT32                          ulSlice;           /* ���һ���յ�������ʱ�� */
}CBT_ACPU_PC_UE_RELEASE_INFO_STRU;

/*****************************************************************************
�ṹ��    : CBT_ACPU_PC_UE_FAIL_STRU
�ṹ˵��  : CBTģ���쳣���տ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    CBT_MAINTENANCE_INFO_STRU           stLostData;         /* ��¼���������� */
    VOS_UINT32                          ulFrameDecapErr;    /* ��¼������֡����Ĵ��� */

    VOS_UINT16                          usPacketLenErr;     /* ��¼����������С��OM_USB_FRAME_LEN����Ĵ��� */
    VOS_UINT16                          usLenTooShortErr;   /* ��¼�������ݳ���С�ڷֶ�ͷ�Ĵ������ */
    VOS_UINT16                          usSegLenErr;        /* ��¼�����γ��ȴ������ */
    VOS_UINT16                          usSegNumErr;        /* ��¼��������Ŀ������� */

    VOS_UINT16                          usDatatypeErr;      /* ��¼����datatype�ֶδ������ */
    VOS_UINT16                          usMsgTooLongErr;    /* ��¼�����������Ϣ����8K�Ĵ������ */
    VOS_UINT16                          usCpuIdErr;         /* ��¼����CPU id������� */
    VOS_UINT16                          usNoMemErr;         /* ��¼�����ռ䲻��Ĵ������ */

    VOS_UINT16                          usDataHeadErr;      /* ��¼��������֡ͷ��������� */
    VOS_UINT16                          usMsgLenErr;        /* ��¼������Ϣ���ȴ������ */
    VOS_UINT16                          usMsgSnErr;         /* ��¼������Ϣ��Ŵ������ */
    VOS_UINT16                          usTransIdErr;       /* ��¼����TransId ��Ŵ������ */
    VOS_UINT16                          usPacketLostErr;    /* ��¼��������ʧ�Ĵ������ */
    VOS_UINT16                          usTimeStampErr;     /* ��¼������ʱ����Ĵ������ */

    VOS_UINT16                          usLinkDataLenErr;   /* ��¼��·��Ϣ���ȴ���Ĵ��� */
    VOS_UINT16                          usLinkStatusErr;    /* ��¼��·�ر�ʱ�յ���Ϣ���Ĵ��� */
    VOS_UINT16                          usAllocMsg;         /* ��¼��Ϣ����ʧ�ܵĴ��� */
    VOS_UINT16                          usRcv;

    CBT_ACPU_ICC_SEND_FAIL_STRU          stICCSendFailInfo;  /* ��¼ACPU�ɹ����͵�ICC���� */
}CBT_ACPU_PC_UE_FAIL_STRU;

/*****************************************************************************
�ṹ��    : CBT_ACPU_PC_UE_SUC_STRU
�ṹ˵��  : CBTģ���������տ�ά�ɲ���Ϣ��¼�ṹ
*****************************************************************************/
typedef struct
{
    CBT_MAINTENANCE_INFO_STRU            stTotalData;       /* ��¼���յ��������� */
    CBT_MAINTENANCE_INFO_STRU            stHdlcDecapData;
    CBT_MAINTENANCE_INFO_STRU            stLinkData;        /* ��¼�յ�����·���� */
    CBT_MAINTENANCE_INFO_STRU            stCcpuData;        /* ��¼����CCPU������ */
    CBT_MAINTENANCE_INFO_STRU            stAcpuData;        /* ��¼����ACPU������ */
    CBT_ACPU_ICC_SEND_SUC_STRU           stICCSendSUCInfo;  /* ��¼ACPU�ɹ����͵�ICC���� */
    CBT_MAINTENANCE_INFO_STRU            stRlsData;         /* ��¼���߷��͵�Release���� */
    CBT_ACPU_PC_UE_RELEASE_INFO_STRU     stRlsInfo;         /* ��¼Release��Ϣ */
}CBT_ACPU_PC_UE_SUC_STRU;

/*****************************************************************************
�ṹ��    : CBTRL_MSG_COMBINE_INFO_STRU
�ṹ˵��  : CBTRLģ����������Ҫ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTotalSegNum;      /* �ܵķֶ��� */
    VOS_UINT8                           ucExpectedSegSn;    /* ��������������õ�����Ϣ����� */
    VOS_UINT16                          usRsv;

    VOS_UINT32                          ulTransId;
    VOS_UINT32                          ulTimeStampL;
    VOS_UINT16                          usTimeStampH;
    VOS_UINT16                          usRsv2;

    VOS_UINT32                          ulTotalMsgLen;      /* ����������������Ϣ�ܵĳ��� */
    VOS_UINT32                          ulMoveLen;          /* ���������ÿ����һ��Ϣ�����ƫ�� */
    MsgBlock *                          pstWholeMsg;        /*ָ�����������������Ϣ��*/
}CBT_MSG_COMBINE_INFO_STRU;

/*****************************************************************************
�ṹ��    : CBTRL_RCV_CHAN_CTRL_INFO_STRU
�ṹ˵��  : CBTRLģ��ͨ��������Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCbtSwitchOnOff;
    CBT_MSG_COMBINE_INFO_STRU           stMsgCombineInfo;

    CBT_ACPU_PC_UE_FAIL_STRU            stPcToUeErrRecord;
    CBT_ACPU_PC_UE_SUC_STRU             stPcToUeSucRecord;
}CBT_RCV_CHAN_CTRL_INFO_STRU;


/*****************************************************************************
  ��������
*****************************************************************************/
VOS_UINT32 CBT_AcpuInit(VOS_VOID);
VOS_UINT32 CBT_AcpuSendData(CBT_UNIFORM_MSG_STRU * pstMsg, VOS_UINT16 usMsgLen);

VOS_VOID CBT_AcpuSendResultChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMOde,
                            VOS_UINT16 usReturnPrimId, VOS_UINT32 ulResult);
VOS_VOID CBT_AcpuSendContentChannel(CBT_MODEM_SSID_STRU stModemSsid, CBT_COMPONENT_MODE_STRU stCompMOde,
                             VOS_UINT16 usReturnPrimId, CBT_UNIFORM_MSG_STRU * pstCbtToPcMsg);
VOS_VOID CBT_AcpuOpenLog(VOS_UINT32 ulFlag);



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif
