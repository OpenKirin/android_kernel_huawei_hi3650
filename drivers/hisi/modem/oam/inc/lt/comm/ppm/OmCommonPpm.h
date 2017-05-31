


#ifndef __OM_COMMON_PPM_H__
#define __OM_COMMON_PPM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "omnvinterface.h"
#include "mdrv.h"
#include "SOCPInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

extern VOS_UINT32                          g_ulOmAcpuDbgFlag ;

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define USB_MAX_DATA_LEN            (60*1024)   /*USB���͵�������ݳ���*/

#define BIT_N(num)          (0x01 << (num))

#define OM_ACPU_RECV_USB        BIT_N(0)
#define OM_ACPU_DISPATCH_MSG    BIT_N(1)
#define OM_ACPU_SEND_SOCP       BIT_N(2)
#define OM_ACPU_SEND_USB        BIT_N(3)
#define OM_ACPU_USB_CB          BIT_N(4)
#define OM_ACPU_SEND_USB_IND    BIT_N(5)
#define OM_ACPU_ERRLOG_SEND     BIT_N(6)
#define OM_ACPU_ERRLOG_RCV      BIT_N(7)
#define OM_ACPU_ERRLOG_PRINT    BIT_N(8)
#define OM_ACPU_RECV_SOCKET     BIT_N(9)
#define OM_ACPU_SEND_SOCKET     BIT_N(10)

#define SOCP_SEND_DATA_PARA_CHECK(pstDebugInfo, ulDataLen, pucData) \
    if ((0 == ulDataLen)\
    || (VOS_NULL_PTR == pucData))\
    {\
        pstDebugInfo->ulUSBSendCBAbnormalNum++;\
        return;\
    }


#define OM_ACPU_DEBUG_CHANNEL_TRACE(enChanID, pucData, ulDataLen, ulSwitch) \
        if(VOS_FALSE != (g_ulOmAcpuDbgFlag&ulSwitch)) \
        { \
            VOS_UINT32 ulOmDbgIndex; \
            vos_printf("\n%s, channal ID: = %d, Data Len: = %d\n", __FUNCTION__, enChanID, ulDataLen); \
            for (ulOmDbgIndex = 0 ; ulOmDbgIndex < ulDataLen; ulOmDbgIndex++) \
            { \
                vos_printf("%02x ", *((VOS_UINT8*)pucData + ulOmDbgIndex)); \
            } \
            vos_printf("\r\n"); \
        }

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/
/* UDI�豸��� */
enum OM_PROT_HANDLE_ENUM
{
    OM_USB_IND_PORT_HANDLE      =   0,
    OM_USB_CFG_PORT_HANDLE      =   1,
    OM_USB_CBT_PORT_HANDLE      =   2,
    OM_HSIC_IND_PORT_HANDLE     =   3,
    OM_HSIC_CFG_PORT_HANDLE     =   4,
    OM_PORT_HANDLE_BUTT
};

typedef VOS_UINT32  OM_PROT_HANDLE_ENUM_UINT32;

enum OM_LOGIC_CHANNEL_ENUM
{
     OM_LOGIC_CHANNEL_CBT = 0,
     OM_LOGIC_CHANNEL_CNF,
     OM_LOGIC_CHANNEL_IND,
     OM_LOGIC_CHANNEL_BUTT
};

typedef VOS_UINT32     OM_LOGIC_CHANNEL_ENUM_UINT32;


/*****************************************************************************
  4 �ṹ�嶨��
*****************************************************************************/
/*****************************************************************************
 �ṹ��    : OM_PSEUDO_SYNC_STRU
 Э����  : ��
 �ṹ˵��  : OM���õ���DRV_UDI_IOCTL�첽�ӿڷ������ݣ�Ϊ�����DRV_UDI_WRITEͬ���ӿ�
             �������߼�һ�£����첽�ӿڵ���α��Ϊͬ���ӿ�

 �޸���ʷ      :
  1.��    ��   : 2014��5��25��
    ��    ��   : L00256032
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_SEM                             ulPseudoSyncSemId;   /* α��Ϊͬ���ӿ���ʹ�õ��ź��� */
    VOS_UINT8                          *pucAsyncCBData;      /* DRV_UDI_IOCTL�ӿ��첽���غ��������ָ�� */
    VOS_UINT32                          ulLen;               /* DRV_UDI_IOCTL�ӿ��첽���غ󷵻ص�ʵ�ʴ������ݳ��� */
    VOS_UINT32                          ulRsv;               /* Reserve */
}OM_PSEUDO_SYNC_STRU;

/*****************************************************************************
 �ṹ��    : PPM_PORT_CFG_INFO_STRU
 Э����  : ��
 �ṹ˵��  : PPM�˿��л�ͳ����Ϣ

 �޸���ʷ      :
  1.��    ��   : 2014��5��25��
    ��    ��   : h59254
    �޸�����   : V8R1 OM_Optimize��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPortTypeErr;
    VOS_UINT32                          ulSwitchFail;
    VOS_UINT32                          ulSwitchSucc;
    VOS_UINT32                          ulStartSlice;
    VOS_UINT32                          ulEndSlice;
}PPM_PORT_CFG_INFO_STRU;


/* ���ڼ�¼VCOM������Ϣ */
typedef struct
{
    VOS_UINT32                          ulVCOMSendSn;
    VOS_UINT32                          ulVCOMSendNum;
    VOS_UINT32                          ulVCOMSendLen;
    VOS_UINT32                          ulVCOMSendErrNum;
    VOS_UINT32                          ulVCOMSendErrLen;
    VOS_UINT32                          ulMaxTimeLen;           /* ����д�ӿڻ��ѵ����ʱ�� */

    VOS_UINT32                          ulVCOMRcvSn;
    VOS_UINT32                          ulVCOMRcvNum;
    VOS_UINT32                          ulVCOMRcvLen;
    VOS_UINT32                          ulVCOMRcvErrNum;
    VOS_UINT32                          ulVCOMRcvErrLen;
}OM_VCOM_DEBUG_INFO;



typedef struct
{
    VOS_UINT32                      ulUSBWriteNum1;
    VOS_UINT32                      ulUSBWriteNum2;
    VOS_UINT32                      ulUSBWriteCBNum;
    VOS_UINT32                      ulUSBWriteMaxTime;
    VOS_UINT32                      ulUSBINNum;
    VOS_UINT32                      ulUSBINTime;
    VOS_UINT32                      ulUSBOutNum;
    VOS_UINT32                      ulUSBOutTime;
    VOS_UINT32                      ulUSBStateErrNum;
    VOS_UINT32                      ulUSBStateErrTime;
    VOS_UINT32                      ulUSBWriteErrTime;
    VOS_UINT32                      ulUSBWriteErrNum;
    VOS_UINT32                      ulUSBWriteErrValue;
    VOS_UINT32                      ulUSBWriteErrLen;

    VOS_UINT32                      ulUSBOpenNum;
    VOS_UINT32                      ulUSBOpenSlice;
    VOS_UINT32                      ulUSBOpenOkNum;
    VOS_UINT32                      ulUSBOpenOkSlice;
    VOS_UINT32                      ulUSBOpenOk2Num;
    VOS_UINT32                      ulUSBOpenOk2Slice;
    VOS_UINT32                      ulUSBCloseNum;
    VOS_UINT32                      ulUSBCloseSlice;
    VOS_UINT32                      ulUSBCloseOkNum;
    VOS_UINT32                      ulUSBCloseOkSlice;

    VOS_UINT32                      ulUSBIndPseudoSyncFailNum;
    VOS_UINT32                      ulUSBIndPseudoSyncFailSlice;
    VOS_UINT32                      ulUSBCnfPseudoSyncFailNum;
    VOS_UINT32                      ulUSBCnfPseudoSyncFailSlice;
    VOS_UINT32                      ulUSBUdiHandleErr;
    VOS_UINT32                      ulUSBUdiHandleReadGetBufferErr;
    VOS_UINT32                      ulUSBUdiCommRcvNullPtrErr;
    VOS_UINT32                      ulUSBUdiHandleReadBufferFreeErr;
    VOS_UINT32                      ulUSBRcvPktNum;
    VOS_UINT32                      ulUSBRcvPktByte;

}OM_ACPU_PORT_INFO;

typedef struct
{
    VOS_UINT32                          ulSocpCBParaErrNum;
    VOS_UINT32                          ulUSBSendNum;
    VOS_UINT32                          ulUSBSendLen;
    VOS_UINT32                          ulUSBSendRealLen;
    VOS_UINT32                          ulUSBSendErrNum;
    VOS_UINT32                          ulUSBSendErrLen;
    VOS_UINT32                          ulUSBSendCBAbnormalNum;
    VOS_UINT32                          ulUSBSendCBAbnormalLen;

    VOS_UINT32                          ulOmGetVirtErr;
    VOS_UINT32                          ulOmGetVirtSendLen;
    VOS_UINT32                          ulOmDiscardNum;
    VOS_UINT32                          ulOmDiscardLen;
    VOS_UINT32                          ulSocpReadDoneErrNum;
    VOS_UINT32                          ulSocpReadDoneErrLen;
}OM_SOCP_CHANNEL_DEBUG_INFO;

/*���ڼ�¼��ǰOMͨ������Ϣ*/
typedef struct
{
    OM_SOCP_CHANNEL_DEBUG_INFO          stIndDebugInfo;
    OM_SOCP_CHANNEL_DEBUG_INFO          stCnfDebugInfo;
    OM_ACPU_PORT_INFO                   astPortInfo[OM_PORT_HANDLE_BUTT];
    VOS_UINT32                          ulInvaldChannel;
}OM_ACPU_DEBUG_INFO;

/*****************************************************************************
  4 ��������
*****************************************************************************/
#if((VOS_OS_VER == VOS_LINUX) || (VOS_OSA_CPU == OSA_CPU_ACPU))
extern VOS_UINT32 PPM_DisconnectGUPort(OM_LOGIC_CHANNEL_ENUM_UINT32 enChannel);

extern VOS_UINT32 PPM_DisconnectTLPort(VOS_VOID);

extern VOS_VOID   PPM_DisconnectAllPort(OM_LOGIC_CHANNEL_ENUM_UINT32 enChannel);

extern VOS_INT32  PPM_ReadPortData(CPM_PHY_PORT_ENUM_UINT32 enPhyPort, UDI_HANDLE UdiHandle, OM_PROT_HANDLE_ENUM_UINT32 enHandle);

extern VOS_VOID   PPM_PortWriteAsyCB(OM_PROT_HANDLE_ENUM_UINT32 enHandle, VOS_UINT8* pucData, VOS_INT lLen);

extern VOS_VOID   PPM_ReadPortDataInit(CPM_PHY_PORT_ENUM_UINT32        enPhyPort,
                                    OM_PROT_HANDLE_ENUM_UINT32          enHandle,
                                    VOS_VOID                            *pReadCB,
                                    VOS_VOID                            *pWriteCB,
                                    VOS_VOID                            *pStateCB);

extern VOS_UINT32 PPM_UdiRegCallBackFun(UDI_HANDLE enHandle, VOS_UINT32 ulCmdType, VOS_VOID* pFunc);

extern VOS_VOID   PPM_PortCloseProc(OM_PROT_HANDLE_ENUM_UINT32  enHandle, CPM_PHY_PORT_ENUM_UINT32 enPhyPort);

extern VOS_UINT32 PPM_PortSend(OM_PROT_HANDLE_ENUM_UINT32 enHandle, VOS_UINT8 *pucVirAddr, VOS_UINT8 *pucPhyAddr, VOS_UINT32 ulDataLen);

extern VOS_VOID   PPM_PortStatus(OM_PROT_HANDLE_ENUM_UINT32 enHandle, CPM_PHY_PORT_ENUM_UINT32 enPhyPort,ACM_EVT_E enPortState);

extern VOS_VOID   PPM_GetSendDataLen(SOCP_CODER_DST_ENUM_U32 enChanID, VOS_UINT32 ulDataLen, VOS_UINT32 *pulSendDataLen, CPM_PHY_PORT_ENUM_UINT32 *penPhyport);

extern VOS_UINT32 PPM_PortInit(VOS_VOID);

extern VOS_UINT32 PPM_InitPhyPort(VOS_VOID);
#endif

extern VOS_UINT32 PPM_UsbPortInit(VOS_VOID);

extern VOS_VOID   PPM_HsicPortInit(VOS_VOID);

extern VOS_VOID   PPM_VComPortInit(VOS_VOID);

extern VOS_UINT32 SCM_RlsDestBuf(VOS_UINT32 ulChanlID, VOS_UINT32 ulReadSize);

extern VOS_UINT8* SCM_CoderDestMemVirtToPhy(VOS_UINT32 ulDstChID, VOS_UINT8 *pucVirtAddr);

extern OM_PSEUDO_SYNC_STRU * PPM_ComPpmGetSyncInfo(VOS_VOID);
extern OM_ACPU_DEBUG_INFO * PPM_ComPpmGetDebugInfo(VOS_VOID);

/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
extern UDI_HANDLE                              g_astOMPortUDIHandle[OM_PORT_HANDLE_BUTT];

/* USB���ص�OM IND�˿��У�α��Ϊͬ���ӿ�ʹ�õ����ݽṹ�� */
extern OM_PSEUDO_SYNC_STRU                     g_stUsbIndPseudoSync;

/* USB���ص�OM CNF�˿��У�α��Ϊͬ���ӿ�ʹ�õ����ݽṹ�� */
extern OM_PSEUDO_SYNC_STRU                     g_stUsbCfgPseudoSync;

/*****************************************************************************
  6 OTHERS����
*****************************************************************************/




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

#endif /* end of OmCommonPpm.h*/

