
 
#ifndef __PSMUX_H__
#define __PSMUX_H__


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include    "TTFUtil.h"
#include    "AtMuxInterface.h"
#include    "mdrv.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MUX_DLCI_PAYLOAD_LEN_MAX        (1852)      /*����֡�����ݳ���*/

#define MUX_DLCI_ID_OFFSET              (1)         /* ��ǰDLCI�Ķ�����1��16, �����һ��1��ƫ���� */

#define MUX_FRAME_FLAG                  (0XF9)      /*Mux֡����ʼ�ͽ�����־��*/

#define MUX_CONTROL_UIH                 (0xEF)

#define MUX_FRAME_LEN_0                 (0)
#define MUX_FRAME_LEN_1                 (1)
#define MUX_FRAME_LEN_2                 (2)
#define MUX_FRAME_LEN_3                 (3)
#define MUX_FRAME_LEN_4                 (4)
#define MUX_FRAME_LEN_5                 (5)
#define MUX_FRAME_LEN_6                 (6)
#define MUX_FRAME_LEN_7                 (7)
#define MUX_FRAME_LEN_8                 (8)

#define MUX_FRAME_LEN_128               (128)


/* ��ȡADS����RAB INFO��ַ */
#define MUX_AT_UL_GET_DLCI_INFO_PTR(Dlci)           (&(g_stMuxAtUlDlciInfo[Dlci - MUX_DLCI_ID_OFFSET]))

/* ��ȡMUX�������ݻص�����ָ�� */
#define MUX_AT_UL_DLCI_GET_DATA_CALLBACK_FUNC(Dlci) (MUX_AT_UL_GET_DLCI_INFO_PTR(Dlci)->pRcvUlDlciDataFunc)

/*��ý���ʱ��֡����ز���*/
#define MUX_GET_UL_RX_STAT()                        (&g_stMuxUnframeState.ucUnframeState)
#define MUX_GET_UL_RX_BUFF()                        (g_stMuxUnframeState.pUnframeBuf)
#define MUX_GET_UL_RX_HEAD()                        (g_stMuxUnframeState.aucHeadBuff)
#define MUX_GET_UL_RX_LEN()                         (&g_stMuxUnframeState.usLeftInfoLen)

/*��ý��ջ���*/
#define MUX_GET_RX_Q_ADDR()                         (&(g_stMuxUlQue))


#define MUX_SET_116_BIT(a,b,c)     (VOS_UINT8)(((VOS_UINT8)((a) & 0x01)) \
                                    | ((VOS_UINT8)(((b) << 1) & 0x02)) \
                                    | ((VOS_UINT8)(((c) << 2) & 0xFC)))

#define MUX_GET_116_BIT(uc, b)      (b) = (VOS_UINT8)(((uc) & 0xFC)>>2);

#define MUX_SET_17_BIT(a,b)         (VOS_UINT8)(((VOS_UINT8)((a) & 0x01) ) \
                                    |(VOS_UINT8)(((b) << 1) & 0xFE))

#define MUX_GET_17_BIT(uc, a, b)    (a) = ((VOS_UINT8)(uc) & 0x01);\
                                    (b) = (VOS_UINT8)(((uc) & 0xFE)>>1);


/*����ͳ����Ϣ*/
#define  MUX_DBG_DL_SEND_SUCC_PKT_NUM(n)            (g_stMuxStaticInfo.ulSuccSendDlPacketNums += (n))
#define  MUX_DBG_DL_SEND_FAIL_PKT_NUM(n)            (g_stMuxStaticInfo.ulFailSendDlPacketNums += (n))
#define  MUX_DBG_DL_FREE_PKT_NUM(n)                 (g_stMuxStaticInfo.ulFreeDlPacketNums += (n))


/*����ͳ����Ϣ*/
#define  MUX_DBG_UL_SEND_SUCC_PKT_NUM(n)            (g_stMuxStaticInfo.ulSuccSendUlPacketNums += (n))
#define  MUX_DBG_UL_SEND_FAIL_PKT_NUM(n)            (g_stMuxStaticInfo.ulFailSendUlPacketNums += (n))
#define  MUX_DBG_UL_GET_SUCC_PKT_NUM(n)             (g_stMuxStaticInfo.ulSuccGetUlPacketNums += (n))
#define  MUX_DBG_UL_DISCARD_PKT_NUM(n)              (g_stMuxStaticInfo.ulDiscardUlPacketNums += (n))
#define  MUX_DBG_UL_CALLBACK_FAIL_NUM(n)            (g_stMuxStaticInfo.ulGetDataFailNums += (n))
#define  MUX_DBG_GET_INVALID_UDI_HANDLE_NUM(n)      (g_stMuxStaticInfo.ulInvalidUdiHandleNums += (n))


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* ��ά�ɲ�ʹ����Ϣ */
typedef enum
{
    ID_MUX_TRACE_UL_DATA                   = 0x1001,   /* �������ݹ��� */
    ID_MUX_TRACE_DL_DATA                   = 0x1002,   /* �������ݹ��� */
    ID_MUX_TRACE_TYPE_BUTT
}MUX_TRACE_MSG_TYPE_ENUM;
typedef VOS_UINT32 MUX_TRACE_MSG_TYPE_ENUM_UINT32;

/*��������״̬*/
typedef enum
{
    MUX_DLCI_UNFRAME_STATE_FNDING_F9        = 0,
    MUX_DLCI_UNFRAME_STATE_FNDING_ADDR,
    MUX_DLCI_UNFRAME_STATE_FNDING_CTRL,
    MUX_DLCI_UNFRAME_STATE_FNDING_LEN1,
    MUX_DLCI_UNFRAME_STATE_FNDING_LEN2,
    MUX_DLCI_UNFRAME_STATE_FNDING_INFO,
    MUX_DLCI_UNFRAME_STATE_FNDING_FCS,
    MUX_DLCI_UNFRAME_STATE_FNDING_EOF,
    MUX_DLCI_UNFRAME_STATE_FNDING_BUTT
}MUX_DLCI_UNFRAME_STATE_FNDING_ENUM;
typedef VOS_UINT8 MUX_DLCI_UNFRAME_STATE_FNDING_ENUM_UINT8;


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/*֡ͷ����ʽ*/
typedef struct
{
    VOS_UINT8               ucStartFlag;        /*0x9F*/
    VOS_UINT8               ucAddr;             /*bit:1,1,6 EA/CR/DLCI
                                                EA:�̶�Ϊ1��ʾΪ���һ���ֶ�
                                                CR:command or response �ظ�Ϊ���
                                                ��ʼ������дΪAPP:1 PS:0*/
    VOS_UINT8               ucControl;          /*֡����*/
    VOS_UINT8               ucLen1;             /*bit:1,7 EA/LEN
                                                EA:��ʾΪ���һ���ֶΣ�0��ʾ����һ���ֶ�*/
    VOS_UINT8               ucLen2;             /*���һ���ֽ��޷���ʾ���ȣ�
                                                ����ֶα�ʾ���ȵĵ��ֽ�*/
    VOS_UINT8               ucRsv[3];           /*����*/
} MUX_FRAME_HEAD;


/*Mux���ն�Ӧ״̬�ṹ*/
typedef struct
{
    VOS_UINT8               ucUnframeState;     /* ��֡״̬ */
    VOS_UINT8               aucHeadBuff[5];     /* �����������ͷ�������ݻ���*/
    VOS_UINT16              usLeftInfoLen;      /* δ���յ���Ϣ�򳤶� */
    TTF_MBUF_ST            *pUnframeBuf;        /* ����֡�Ļ��� */
} MUX_UNFRAME_STATE_ST;


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
�ṹ��    : MUX_AT_UL_DLCI_INFO_STRU
�ṹ˵��  : MUX����DLCI��Ϣ����

  1.��    ��   : 2011��8��10��
    ��    ��   : h00163499
    �޸�����   : ����MUX����DLCI��Ϣ����
*****************************************************************************/
typedef struct
{
    AT_MUX_DLCI_TYPE_ENUM_UINT8         enDlci;                                 /* ��·�� */
    VOS_UINT8                           aucRsv[3];                              /* ���� */
    RCV_UL_DLCI_DATA_FUNC               pRcvUlDlciDataFunc;                     /* ��Ӧ�����н��պ��� */
}MUX_AT_UL_DLCI_INFO_STRU;

/* ��¼�豸����Ϣ */
typedef struct
{
    UDI_DEVICE_ID_E               enUdiDevId;                     /* ����ʵ�ʺ�MUXһ��ʹ�õ��豸ID */
    UDI_HANDLE                  slUdiMuxAcmHdl;                 /* �豸��Ӧ�ľ�� */
    VOS_UINT32                  (*pMuxAcmUlRxFunc)(VOS_VOID);   /* �þ���ϱ�����ʱMUX���õĻص�����ָ�� */
}MUX_DEV_INFO_STRU;

typedef struct
{
    VOS_UINT32                  ulInvalidUdiHandleNums;         /* ��ȡ����UDI�������Ĵ��� */
    VOS_UINT32                  ulGetDataFailNums;              /* ����ص����ȡ�������ݵĴ��� */
    VOS_UINT32                  ulDiscardUlPacketNums;          /* ������Ϊ״̬���Ե�ԭ���������ݰ����� */
    VOS_UINT32                  ulSuccGetUlPacketNums;          /* ����Hsicͨ���ɹ���ȡ�����ݰ����� */
    VOS_UINT32                  ulFailSendUlPacketNums;         /* ������ATͨ������ʧ�ܵ����ݰ����� */
    VOS_UINT32                  ulSuccSendUlPacketNums;         /* ������ATͨ���ɹ����͵����ݰ�����*/
    VOS_UINT32                  ulFailSendDlPacketNums;         /* ���е��õ���ͨ������ʧ�ܵ����ݰ����� */
    VOS_UINT32                  ulSuccSendDlPacketNums;         /* ���е��õ���ͨ�����ͳɹ������ݰ����� */
    VOS_UINT32                  ulFreeDlPacketNums;             /* ���е��õ���ͨ���ͷųɹ������ݰ����� */
} MUX_DEV_STATIC_INFO_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 MUX_DlciDlUsbAcmFreeDataCB(VOS_UINT8 *pucBuf);
extern VOS_UINT32 MUX_DlciUlHsicFreeDataBuf(
    UDI_HANDLE                          ulUdiHdl,
    VOS_UINT8                          *pucBuf,
    VOS_UINT16                          usLen
);
extern VOS_UINT32 MUX_DlciDlDataProc (AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8* pucSendBuf,
    VOS_UINT16 *pusSendDataLen, VOS_UINT8* pucBuf, VOS_UINT16 usDataLen);

extern VOS_VOID MUX_TraceUlData(VOS_UINT32 ulDeviceId, VOS_UINT8 *pucBuf, VOS_UINT16 usLen);
extern VOS_VOID MUX_TraceDlData(AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci, VOS_UINT8 *pData, VOS_UINT16 usDataLen);
extern VOS_VOID MUX_StaticInfoInit( VOS_VOID );
extern VOS_UINT32 MUX_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip );
extern VOS_UINT32 MUX_AtMsgProc( const MsgBlock *pMsgBlock );

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

#endif /* end of PsHsic.h */

