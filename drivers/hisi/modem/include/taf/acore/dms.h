

#ifndef __DMS_H__
#define __DMS_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "mdrv.h"
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define DMS_LOG_STATIC_BUF_NUM          (16)
#define DMS_LOG_STATIC_ONE_BUF_SIZE     (5120)

#define NVE_AT_SERVER_INDEX             (294)
#define NVE_READ_OPERATE                (1)
#define NVE_WRITE_OPERATE               (0)

/* ͨ���Ͽ�����֪ͨ����
 */
#define DMS_DISNNECT                    (0)
#define DMS_CONNECT                     (1)

#define DMS_VCOM_OM_CHAN_CTRL           (DMS_OM_CHAN_LTE_CTRL)
#define DMS_VCOM_OM_CHAN_DATA           (DMS_OM_CHAN_LTE_DATA)
#define DMS_VCOM_OM_CHAN_BUTT           (DMS_OM_CHAN_BUTT)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/* ���µ�ö��ֵ��������޸�*/
typedef enum
{
    DMS_PHY_BEAR_BEGIN                 = 0,
    DMS_PHY_BEAR_RESERVE1,
    DMS_PHY_BEAR_RESERVE2,
    DMS_PHY_BEAR_RESERVE3,
    DMS_PHY_BEAR_RESERVE4,
    DMS_PHY_BEAR_RESERVE5,
    DMS_PHY_BEAR_RESERVE6,
    DMS_PHY_BEAR_RESERVE7,
    DMS_PHY_BEAR_USB_PCUI,
    DMS_PHY_BEAR_USB_CTRL,
    DMS_PHY_BEAR_USB_PCUI2,
    DMS_PHY_BEAR_USB_NCM,
    DMS_PHY_BEAR_LAST
} DMS_PHY_BEAR_ENUM;

typedef enum
{
    DMS_CHANNEL_DIAG                    = 0,                /* channel identifier, DIAG */
    DMS_CHANNEL_AT,                                         /* channel identifier, AT */
    DMS_CHANNEL_GU,
    DMS_CHANNEL_LAST
} DMS_LOGIC_CHAN_ENUM;

typedef enum
{
    STATIC_BUF_STA_IDLE                 = 0,
    STATIC_BUF_STA_BUSY,
    STATIC_BUF_STA_BUTT
} DMS_BUF_STATUS_ENUM;

typedef enum
{
    DMS_BUF_TYP_DYMIC                   = 0,
    DMS_BUF_TYP_STATIC,
    DMS_BUF_TYP_BUTT
} DMS_BUF_TYP_ENUM;

enum PDP_STATUS_ENUM
{
    PDP_STATUS_DEACT                    = 0,
    PDP_STATUS_ACT                      = 1,
    PDP_STATUS_BUTT
};
typedef VOS_UINT32 PDP_STATUS_ENUM_UINT32;

/*****************************************************************************
 ö������: DMS_CHAN_EVT_ENUM
 ö��˵��: ͨ���¼�ö��
*****************************************************************************/
enum DMS_CHAN_EVT_ENUM
{
    DMS_CHAN_EVT_CLOSE                  = 0,
    DMS_CHAN_EVT_OPEN,

    DMS_CHAN_EVT_BUTT
};
typedef VOS_UINT32 DMS_CHAN_EVT_ENUM_UINT32;

/*****************************************************************************
 ö������: DMS_OM_CHAN_ENUM
 ö��˵��: ͨ������ö��
*****************************************************************************/
enum DMS_OM_CHAN_ENUM
{
    DMS_OM_CHAN_LTE_CTRL                = 0,
    DMS_OM_CHAN_LTE_DATA,
    DMS_OM_CHAN_GU_DATA,

    DMS_OM_CHAN_BUTT
};
typedef VOS_UINT32 DMS_OM_CHAN_ENUM_UINT32;


/*****************************************************************************
  4 STRUCT����
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulCalledNum;  /* ���ô���������Ϣ����,���߱����ú����Ƿ񱻵��� */

    VOS_UINT32                          ulRserved1;   /* ������λ�û�������,HAL_DIAG_SYS_DEBUG_ENUM���� */

    VOS_UINT32                          ulRserved2;   /* �������⺬���������,HAL_DIAG_SYS_DEBUG_ENUM���� */

    VOS_UINT32                          ulRserved3;   /* �������⺬���������,HAL_DIAG_SYS_DEBUG_ENUM���� */

    VOS_UINT32                          ulRtcTime;    /* �������ִ�й���ʱ�� */
} DMS_DEBUG_INFO_TBL_STRU;


typedef struct
{
    VOS_INT32                           lOperatRet;         /* 0:��ȡ�ɹ�  -1:��ȡʧ�� */
    VOS_UINT32                          ulNvValue;          /* 0:��atserver 1:��atserver */
} DMS_DEBUG_AT_SERV_NV_STRU;


typedef struct
{
    VOS_UINT8                          *pcuBuf;
    DMS_BUF_STATUS_ENUM                 enBusy;
    VOS_UINT8                           aucReserved[4];
} DMS_BUF_STA_STRU;


typedef struct
{
    DMS_BUF_TYP_ENUM                    enBufType;
    VOS_UINT8                           aucReserved[4];
    DMS_BUF_STA_STRU                    stBufSta[DMS_LOG_STATIC_BUF_NUM];
} DMS_STATIC_BUF_STRU;


/* PDP״̬�ϱ�����ʹ�õĽṹ�� */
typedef struct
{
    VOS_UINT32                       ulSpeed;             /* �����ٶȣ���λbps */
    PDP_STATUS_ENUM_UINT32           enActiveSatus;       /* ��������0Ϊ�ɹ�������Ϊʧ�� */
} NAS_PRO_STRU;


typedef VOS_UINT32 (*DMS_READ_DATA_PFN)(DMS_PHY_BEAR_ENUM enPhyBear, VOS_UINT8 * pDataBuf, VOS_UINT32 ulLen);

typedef VOS_VOID (*DMS_CONNECT_STA_PFN)(VOS_UINT8 flag);

typedef int (*USB_NAS_BRK)(void);

typedef int (*USB_NAS_AT_CMD_RECV)(unsigned char *pBuff, unsigned short usLen);

/* ��ȡ��ǰ����ģʽCDMA/WCDMA */
typedef unsigned long (*USB_NAS_GET_WWAN_MODE)(void);

typedef int  (*pComRecv)(unsigned char  uPortNo, unsigned char* pData, unsigned short uslength);
/*****************************************************************************
  5 UNION����
*****************************************************************************/


/*****************************************************************************
  6 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  7 ��������
*****************************************************************************/

#define DMS_COM_STATUS_CALLBACK_REGI(uPortNo,pCallback)   NULL

extern VOS_INT32 DMS_ACMRecvFuncReg(pComRecv pCallback);
#define DMS_COM_RCV_CALLBACK_REGI(uPortNo,pCallback)\
            DMS_ACMRecvFuncReg(pCallback)

extern int DMS_NcmExtFuncReg(USBNdisStusChgFunc connectBrk, USB_NAS_AT_CMD_RECV atCmdRcv);
#define DMS_USB_NAS_REGFUNC(brkFunc, atRecvFunc, getWWANMode)\
            DMS_NcmExtFuncReg(brkFunc, atRecvFunc)

extern VOS_INT32 DMS_WriteData(DMS_PHY_BEAR_ENUM enPhyBear, VOS_UINT8 *pucData, VOS_UINT16 usLen);
#define DMS_COM_SEND(uPortNo,pData,uslength)\
            DMS_WriteData(uPortNo,pData,uslength)

extern VOS_INT32 DMS_NcmStatusChangeReg(NAS_PRO_STRU * pPdpStru);
#define DMS_USB_NAS_STATUS_CHANGE(pPdpStru)\
            DMS_NcmStatusChangeReg(pPdpStru)

extern VOS_VOID  Dms_FreeStaticBuf( VOS_UINT8 * buf);
extern VOS_UINT8* Dms_GetStaticBuf(VOS_UINT32 ulLen);
extern VOS_BOOL Dms_IsStaticBuf(VOS_UINT8 *buf);
extern VOS_VOID Dms_StaticBufInit(VOS_VOID);
extern VOS_VOID DMS_NcmProcCbReg(USBNdisStusChgFunc connectBrk,USB_NAS_AT_CMD_RECV atCmdRcv);
extern UDI_HANDLE DMS_GetPortHandle(DMS_PHY_BEAR_ENUM enPhyBear);
extern VOS_UINT32 DMS_VcomPcuiOpen(VOS_VOID);
extern VOS_UINT32 DMS_VcomCtrlOpen(VOS_VOID);
extern VOS_UINT32 DMS_VcomPcui2Open(VOS_VOID);
extern VOS_UINT32 DMS_VcomPcuiClose(VOS_VOID);
extern VOS_UINT32 DMS_VcomCtrlClose(VOS_VOID);
extern VOS_UINT32 DMS_VcomPcui2Close(VOS_VOID);
extern VOS_VOID DMS_VcomPcuiEvtCB(ACM_EVT_E enEvt);
extern VOS_VOID DMS_VcomCtrlEvtCB(ACM_EVT_E enEvt);
extern VOS_VOID DMS_VcomPcui2EvtCB(ACM_EVT_E enEvt);
extern VOS_VOID DMS_VcomPcuiReadCB(VOS_VOID);
extern VOS_VOID DMS_VcomCtrlReadCB(VOS_VOID);
extern VOS_VOID DMS_VcomPcui2ReadCB(VOS_VOID);
extern VOS_VOID DMS_VcomPcuiWrtCB(VOS_CHAR *pcVirAddr, VOS_CHAR *pcPhyAddr, VOS_INT lDoneSize);
extern VOS_VOID DMS_VcomCtrlWrtCB(VOS_CHAR *pcVirAddr, VOS_CHAR *pcPhyAddr, VOS_INT lDoneSize);
extern VOS_VOID DMS_VcomPcui2WrtCB(VOS_CHAR *pcVirAddr, VOS_CHAR *pcPhyAddr, VOS_INT lDoneSize);
extern VOS_VOID DMS_UsbPortReadCB(DMS_PHY_BEAR_ENUM enPhyBear);
extern VOS_VOID DMS_UsbPortWrtCB(DMS_PHY_BEAR_ENUM enPhyBear, VOS_CHAR * pcVirAddr, VOS_CHAR * pcPhyAddr, VOS_INT lDoneSize);
extern VOS_VOID DMS_UsbPortEvtCB(DMS_PHY_BEAR_ENUM enPhyBear, ACM_EVT_E enEvt);

extern VOS_UINT32 DMS_NcmOpen(VOS_VOID);
extern VOS_UINT32 DMS_NcmClose(VOS_VOID);
extern VOS_UINT32 DMS_NcmSendData(VOS_UINT8 *pData, VOS_UINT32 ulLen);
extern VOS_UINT32 DMS_VcomWriteAsync(DMS_PHY_BEAR_ENUM enPhyBear ,VOS_UINT8 *pucDataBuf, VOS_UINT32 ulLen);
extern DMS_CONNECT_STA_PFN DMS_GetConnStaFun(VOS_VOID);
extern VOS_VOID DMS_UsbDisableCB(VOS_VOID);
extern VOS_VOID DMS_UsbEnableCB(VOS_VOID);
extern DMS_READ_DATA_PFN DMS_GetDataReadFun(VOS_VOID);
extern VOS_VOID DMS_SetConnStaCB(DMS_CONNECT_STA_PFN pfnReg);

/*****************************************************************************
 �� �� ��  : DMS_GetHsicPortStatus
 ��������  : ��ȡHSIC�ڴ�״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0-δ��״̬;1-��״̬
 ****************************************************************************/
extern VOS_UINT32 DMS_GetHsicPortStatus(VOS_VOID);

extern VOS_VOID DMS_SetNdisChanStatus(ACM_EVT_E enStatus);


typedef VOS_UINT32 (*DMS_OM_CHAN_DATA_READ_CB_FUNC)(DMS_OM_CHAN_ENUM_UINT32 enChan, VOS_UINT8 *pucData, VOS_UINT32 ulLength);
typedef VOS_VOID (*DMS_OM_CHAN_EVENT_CB_FUNC)(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_CHAN_EVT_ENUM_UINT32 enEvt);

/*****************************************************************************
 �� �� ��  : DMS_RegOmChanDataReadCB
 ��������  : ע��OMͨ�����ݽ��ջص�
 �������  : enChan --- �߼�ͨ��
             pFunc  --- ����ָ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanDataReadCB(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_OM_CHAN_DATA_READ_CB_FUNC pFunc);


/*****************************************************************************
 �� �� ��  : DMS_RegOmChanEventCB
 ��������  : ע��OMͨ���¼����ջص�
 �������  : enChan --- �߼�ͨ��
             pFunc  --- ����ָ��
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
*****************************************************************************/
VOS_UINT32 DMS_RegOmChanEventCB(DMS_OM_CHAN_ENUM_UINT32 enChan, DMS_OM_CHAN_EVENT_CB_FUNC pFunc);


/*****************************************************************************
 �� �� ��  : DMS_WriteOmData
 ��������  : дOMͨ������
 �������  : enChan   --- �߼�ͨ��
             pucData  --- ���ݵ�ַ
             ulLength --- ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_ERR/VOS_OK
*****************************************************************************/
VOS_UINT32 DMS_WriteOmData(DMS_OM_CHAN_ENUM_UINT32 enChan, VOS_UINT8 *pucData, VOS_UINT32 ulLength);

VOS_VOID DMS_SetModemStatus(MODEM_ID_ENUM_UINT16 enModemId);
VOS_UINT8 DMS_GetModemStatus(MODEM_ID_ENUM_UINT16 enModemId);
VOS_VOID DMS_InitModemStatus(VOS_VOID);

/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /*__DMS_H__*/

