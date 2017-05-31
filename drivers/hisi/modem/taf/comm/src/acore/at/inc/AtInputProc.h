
#ifndef _AT_INPUT_PROC_H_
#define _AT_INPUT_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#include "ImmInterface.h"
#include "mdrv.h"
#include "ATCmdProc.h"
#include "product_config.h"
#include "TafOamInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*Begin - yaochaoqun - 2009-4-2 - for new PNP*/
#define  SCSI_CMD_LEN                       (31)
/*End - yaochaoqun - 2009-4-2 - for new PNP*/

/* ���������ش����� */
#define AT_NDIS_MAX_RESEND_TIMES            (60)

/* Modified by s62952 for AT Project��2011-10-17,  Begin*/
/*AT���ݳ�ʼ����*/
#define AT_INIT_DATA_LEN                    (0)
/* Modified by s62952 for AT Project��2011-10-17,  end*/

#define AT_MODEM_UL_DATA_BUFF_SIZE      (1536)
#define AT_MODEM_UL_DATA_BUFF_NUM       (16)

#define AT_UART_UL_DATA_BUFF_SIZE       (1536)
#define AT_UART_UL_DATA_BUFF_NUM        (16)

/* HSIC ATͨ����������Э��ջ�������ݵ����л����� */
#define AT_HSIC_UL_DATA_BUFF_SIZE       (5*1024)
#define AT_HSIC_UL_DATA_BUFF_NUM        (2)

/* ����RI�ܽŵ�ƽ���ƶ�ʱ������ */
#define AT_SET_VOICE_RI_TMR_NAME(ulTmrName)\
            (ulTmrName)  = AT_VOICE_RI_TIMER;\
            (ulTmrName) |= AT_INTERNAL_PROCESS_TYPE

/* ����RI�ܽŵ�ƽ���ƶ�ʱ������ */
#define AT_SET_VOICE_RI_TMR_PARAM(ulTmrParam, ucIndex, ucCallId)\
            ((ulTmrParam) = ((ucCallId) << 8) | (ucIndex))

/* ������RI�ܽŵ�ƽ���ƶ�ʱ����ʱ��Ϣ�л�ȡCALLID */
#define AT_GET_VOICE_RI_CALLID_FROM_TMR_PARAM(ulTmrParam)\
            ((VOS_UINT8)(((ulTmrParam) & 0x0000FF00) >> 8))

/* ������RI�ܽŵ�ƽ���ƶ�ʱ����ʱ��Ϣ�л�ȡ�˿�ID */
#define AT_GET_VOICE_RI_CLIENTID_FROM_TMR_PARAM(ulTmrParam)\
            ((VOS_UINT8)((ulTmrParam) & 0x000000FF))

/* �¶���RI�ܽŵ�ƽ���ƶ�ʱ������ */
#define AT_SET_SMS_RI_TMR_NAME(ulTmrName)\
            (ulTmrName)  = AT_SMS_RI_TIMER;\
            (ulTmrName) |= AT_INTERNAL_PROCESS_TYPE

/* �¶���RI�ܽŵ�ƽ���ƶ�ʱ������ */
#define AT_SET_SMS_RI_TMR_PARAM(ulTmrParam, ucIndex)\
            ((ulTmrParam) = (ucIndex))

/* ���¶���RI�ܽŵ�ƽ���ƶ�ʱ����ʱ��Ϣ�л�ȡ�˿�ID */
#define AT_GET_SMS_RI_CLIENTID_FROM_TMR_PARAM(ulTmrParam)\
            ((VOS_UINT8)((ulTmrParam) & 0x000000FF))

/* UART�˿�����֡��ʽӳ���ָ��ʹ�С */
#define AT_UART_GET_FORMAT_TBL_PTR()    (g_astAtUartFormatTab)
#define AT_UART_GET_FORMAT_TBL_SIZE()   (AT_ARRAY_SIZE(g_astAtUartFormatTab))


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 �ṹ����: AT_MEM_SOURCE_TYPE_ENUM
 Э����:
 �ṹ˵��: MODEM�豸�ڴ���Դ����
 1.��    ��   : 2011��10��17��
  ��    ��   : s62952
  �޸�����   : �����ļ�
*****************************************************************************/
enum AT_MEM_SOURCE_TYPE_ENUM
{
    AT_MEM_SOURCE_UDI_UL_BUF,                                                   /*MODEM�豸buffer�ڴ�*/
    AT_MEM_SOURCE_UDI_DL_BUF,                                                   /*ʹ�õ�DDR�ڴ�*/

    AT_MEM_SOURCE_TYPE_BUTT
};
typedef VOS_UINT32 AT_MEM_SOURCE_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
extern  VOS_UINT32  g_ATNdisSendSem;

/*USB NCM��UDI���*/
extern UDI_HANDLE                              g_ulAtUdiNdisHdl;

/* UDI��� */
extern UDI_HANDLE                              g_alAtUdiHandle[AT_CLIENT_BUTT];


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
 �ṹ��    : AT_HSIC_CONTEXT_STRU
 �ṹ˵��  : AP-MODEM����3��HSIC ATͨ�����ýṹ����������ATͨ����ͳһ��������
 1.��    ��   : 2012��02��20��
   ��    ��   : L47619
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    UDI_DEVICE_ID_E         enAcmChannelId;   /* ĿǰHSIC ATͨ�����õ�HSIC ACMͨ��IDΪ:
                                                                UDI_ACM_HSIC_ACM0_ID
                                                                UDI_ACM_HSIC_ACM2_ID
                                                                UDI_ACM_HSIC_ACM4_ID */


    AT_HSIC_REPORT_TYPE_ENUM_UINT32 enRptType;        /* ָ��HSIC ATͨ���Ƿ�����AT���������ϱ���
                                                                ��^APRPTPORTSEL��������ʹ�ã��ϵ�ʱĬ��ΪAT_HSIC_REPORT_ON*/

    VOS_VOID                       *pReadDataCB;      /* ע�������Ľӿڣ����ڻ�ȡ�����͸�Э��ջ��AT���� */

    VOS_VOID                       *pFreeDlDataCB;    /* ע�������Ľӿڣ����ڵ����ͷ�Э��ջ���͸�����������ڴ� */

    UDI_HANDLE                      lHdlId;           /* HSIC AT��ACMͨ����� */

    AT_CLIENT_ID_ENUM_UINT16        enAtClientId;     /* HSIC ATͨ������Ӧ��AT CLIENT ID*/

    AT_CLIENT_TAB_INDEX_UINT8       ucAtClientTabIdx; /* HSIC��ʹ�õ�gastAtClientTab��index���� */

    AT_USER_TYPE                    ucHsicUser;       /* HSIC ATͨ������Ӧ��AT USER type */

    AT_PORT_NO                      ucHsicPort;       /* HSIC ATͨ������Ӧ��AT PORT NO */

    VOS_UINT8                       aucReserved[7];
}AT_HSIC_CONTEXT_STRU;


/* Added by j00174725 for V3R3 Cut Out Memory��2013-11-07,  Begin */
#if (FEATURE_ON == FEATURE_AT_HSIC)
extern AT_HSIC_CONTEXT_STRU                    g_astAtHsicCtx[];
#endif
/* Added by j00174725 for V3R3 Cut Out Memory��2013-11-07,  End */


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
 �� �� ��  : AT_SendDataToModem
 ��������  : ���з������ݸ�modem��
 �������  : pucDataBuf   ----    ���������������ڴ�ָ��
             usLen        ----    ���ݳ���
 �������  :
 �� �� ֵ  : AT_SUCCESS ----      �ɹ���
             AT_FAILURE ----      ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��22��
    ��    ��   : sunshaohua
    �޸�����   : �����ɺ���

*****************************************************************************/
extern VOS_INT OM_RcvDiagCmdFromPC(VOS_UINT8 ucPortNo, VOS_UINT8 *pData, VOS_UINT16 uslength);
/* Modified by L60609 for AT Project��2011-10-20,  Begin*/
#if (VOS_WIN32 == VOS_OS_VER)
extern VOS_INT32 Sock_RecvCallbackRegister(VOS_UINT8 ucPortNo, pSockRecv pCallback);
#endif
/* Modified by L60609 for AT Project��2011-10-20,  End*/

extern int  App_VcomRecvCallbackRegister(unsigned char  uPortNo, pComRecv pCallback);
extern VOS_INT32 AT_AppComEst(VOS_VOID);
extern VOS_INT32 AT_AppSockComEst(VOS_UINT8 ucPortNo);
extern VOS_UINT32 AT_CheckAppUser(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_CheckNdisUser(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_CheckMuxDlci(AT_MUX_DLCI_TYPE_ENUM_UINT8 enDlci);
extern VOS_UINT32 AT_CheckMuxUser(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_CheckModemUser(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_CheckHsUartUser(VOS_UINT8 ucIndex);
extern VOS_UINT32 AT_CheckUserType(
    VOS_UINT8                               ucIndex,
    AT_USER_TYPE                            enUserType
);

extern VOS_VOID AT_CleanAtChdataCfg(
           VOS_UINT16                          usClientId,
           VOS_UINT8                           ucCid
       );
extern VOS_VOID AT_CloseUsbNdis(VOS_VOID);
extern VOS_UINT32 At_CmdStreamPreProc(VOS_UINT8 ucIndex,VOS_UINT8* pData, VOS_UINT16 usLen);
extern VOS_UINT32  AT_CsdDataModeRcvModemMsc(
           VOS_UINT8                           ucIndex
       );
extern TAF_UINT32 At_DataStreamPreProc (TAF_UINT8 ucIndex,TAF_UINT8 DataMode,TAF_UINT8* pData, TAF_UINT16 usLen);
extern VOS_VOID AT_VcomCmdStreamEcho(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen
       );
extern VOS_VOID AT_GetAtMsgStruMsgLength(
           VOS_UINT32                          ulInfoLength,
           VOS_UINT32                         *pulMsgLength
       );
extern VOS_UINT32 AT_GetMuxDlciFromClientIdx(
           VOS_UINT8                           ucIndex,
           AT_MUX_DLCI_TYPE_ENUM_UINT8        *penDlci
       );
extern VOS_UINT8 AT_GetMuxSupportFlg(VOS_VOID);
extern VOS_VOID AT_GetUserTypeFromIndex(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pucUserType
       );
extern VOS_VOID AT_InitFcMap(VOS_VOID);
extern VOS_VOID AT_InitUartLink(VOS_UINT8 ucIndex);
extern VOS_UINT32  AT_IpDataModeRcvModemMsc(
           VOS_UINT8                           ucIndex,
           AT_DCE_MSC_STRU                     *pMscStru
       );
extern VOS_UINT32 AT_IsConcurrentPorts(
           VOS_UINT8                           ucIndexOne,
           VOS_UINT8                           ucIndexTwo
       );
extern VOS_UINT32 AT_IsHsicOrMuxUser(VOS_UINT8 ucIndex);
extern VOS_VOID AT_MemSingleCopy(
           VOS_UINT8                          *pucDest,
           VOS_UINT8                          *pucSrc,
           VOS_UINT32                          ulLen
       );
extern VOS_VOID AT_ModemSetCtlStatus(
           VOS_UINT8                           ucIndex,
           AT_DCE_MSC_STRU                    *pMscStru
       );
extern VOS_UINT32 At_OmDataProc (
           VOS_UINT8                           ucPortNo,
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen
       );
extern VOS_VOID AT_OpenUsbNdis(VOS_VOID);
extern VOS_UINT32  AT_PppDataModeRcvModemMsc(
           VOS_UINT8                           ucIndex,
           AT_DCE_MSC_STRU                     *pMscStru
       );
extern VOS_INT AT_RcvFromAppCom(
           VOS_UINT8                           ucVcomId,
           VOS_UINT8                          *pData,
           VOS_UINT16                          uslength
       );
extern VOS_INT AT_RcvFromAppSock(
           VOS_UINT8                           ucPortNo,
           VOS_UINT8                          *pData,
           VOS_UINT16                          uslength
       );
extern VOS_INT AT_RcvFromNdisCom(
           VOS_UINT8                           *pucData,
           VOS_UINT16                          uslength
       );
extern VOS_INT AT_RcvFromSock(
           VOS_UINT8                          *pData,
           VOS_UINT32                         uslength
       );
extern VOS_INT At_RcvFromUsbCom(
           VOS_UINT8                           ucPortNo,
           VOS_UINT8                          *pData,
           VOS_UINT16                          uslength
       );
extern VOS_VOID AT_MuxCmdStreamEcho(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen
       );
extern TAF_UINT32 At_SendCmdMsg (TAF_UINT8 ucIndex,TAF_UINT8* pData, TAF_UINT16 usLen,TAF_UINT8 ucType);
extern VOS_UINT32 AT_SendCtrlDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLength
       );
extern VOS_UINT32 AT_SendDataToModem(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucDataBuf,
    VOS_UINT16                          usLen
   );
extern VOS_UINT32 AT_SendDiagCmdFromOm(
           VOS_UINT8                           ucPortNo,
           VOS_UINT8                           ucType,
           VOS_UINT8                          *pData,
           VOS_UINT16                          uslength
       );
extern VOS_UINT32 AT_SendMuxResultData(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen
       );
extern VOS_UINT32 AT_SendMuxSelResultData(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pData,
           VOS_UINT16                          usLen
       );
extern VOS_UINT32 AT_SendPcuiDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLength
       );

extern VOS_UINT32 AT_SendCsdZcDataToModem(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstDataBuf
);
extern VOS_VOID AT_SetAtChdataCidActStatus(
           VOS_UINT16                          usClientId,
           VOS_UINT8                           ucCid,
           VOS_UINT32                          ulIsCidAct
       );
extern VOS_UINT32 AT_SetModemStatus(
           VOS_UINT8                           ucIndex,
           AT_DCE_MSC_STRU                    *pstMsc
       );
extern VOS_VOID AT_SetMuxSupportFlg(VOS_UINT8 ucMuxSupportFlg);
extern VOS_VOID  AT_SndDipcPdpActInd(
           VOS_UINT16                          usClientId,
           VOS_UINT8                           ucCid,
           VOS_UINT8                           ucRabId
       );
extern VOS_VOID  AT_SndDipcPdpDeactInd(
           VOS_UINT8                           ucRabId
       );
extern VOS_INT32 AT_SockComEst(VOS_UINT8 ucPortNo);
extern VOS_VOID AT_StopFlowCtrl(VOS_UINT8 ucIndex);
extern VOS_UINT32 At_UsbCtrEst(VOS_UINT8 ucPortNo);
extern VOS_UINT32 At_UsbGetWwanMode(VOS_VOID);
extern VOS_VOID AT_UsbModemClose(VOS_VOID);
extern VOS_UINT32 At_ModemDataInd(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                           ucDlci,
           IMM_ZC_STRU                        *pstData
       );
extern VOS_VOID AT_UsbModemEnableCB( PS_BOOL_ENUM_UINT8 ucEnable );
VOS_UINT32 At_ModemEst (
    VOS_UINT8                           ucIndex,
    AT_CLIENT_ID_ENUM_UINT16            usClientId,
    VOS_UINT8                           ucPortNo
);
extern VOS_VOID AT_ModemeEnableCB(
    VOS_UINT8                           ucIndex,
    PS_BOOL_ENUM_UINT8                  ucEnable
);

extern VOS_VOID AT_ModemFreeDlDataBuf(
    IMM_ZC_STRU                        *pstBuf
);
extern VOS_UINT32 AT_ModemFreeUlDataBuf(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU *pstBuf
);
extern VOS_UINT32 AT_ModemGetUlDataBuf(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                       **ppstBuf
);
extern VOS_VOID AT_UsbModemInit( VOS_VOID );
extern VOS_UINT32 AT_ModemInitUlDataBuf(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulEachBuffSize,
    VOS_UINT32                          ulTotalBuffNum
);
extern VOS_UINT32 At_ModemMscInd (
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucDlci,
    AT_DCE_MSC_STRU                    *pMscStru
);
extern VOS_VOID AT_UsbModemReadDataCB( VOS_VOID );
extern VOS_VOID AT_UsbModemReadMscCB( AT_DCE_MSC_STRU *pstRcvedMsc );
extern VOS_UINT32 AT_ModemStatusPreProc (VOS_UINT8 ucIndex, AT_DCE_MSC_STRU *pMscStru);
extern VOS_UINT32 AT_ModemWriteData(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstBuf
);
extern VOS_UINT32 AT_UsbNdisEst(VOS_VOID);
extern VOS_UINT32 At_UsbPcuiEst(VOS_UINT8 ucPortNo);
extern VOS_UINT32 At_UsbPcui2Est(VOS_UINT8 ucPortNo);
extern VOS_UINT32 AT_IsApPort(VOS_UINT8 ucIndex);

VOS_VOID AT_UsbNcmConnStatusChgCB(NCM_IOCTL_CONNECT_STUS_E enStatus, VOS_VOID *pBuffer);

VOS_VOID AT_MODEM_ProcDtrChange(VOS_UINT8 ucIndex, AT_DCE_MSC_STRU *pstDceMsc);
VOS_UINT32 AT_MODEM_WriteMscCmd(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
);
VOS_UINT32 AT_MODEM_StartFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);
VOS_UINT32 AT_MODEM_StopFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);

VOS_UINT32 AT_UART_GetUlDataBuff(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                         **ppucData,
    VOS_UINT32                         *pulLen
);
VOS_UINT32 AT_UART_WriteDataSync(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT32                          ulLen
);
VOS_UINT32 AT_UART_SendDlData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);
VOS_UINT32 AT_UART_SendRawDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLen
);
VOS_VOID AT_UART_UlDataReadCB(VOS_VOID);
VOS_VOID AT_UART_InitLink(VOS_UINT8 ucIndex);
VOS_VOID AT_UART_InitPort(VOS_VOID);

#if (FEATURE_ON == FEATURE_AT_HSUART)
VOS_UINT32 AT_HSUART_IsBaudRateValid(AT_UART_BAUDRATE_ENUM_UINT32 enBaudRate);
VOS_UINT32 AT_HSUART_IsFormatValid(AT_UART_FORMAT_ENUM_UINT8 enFormat);
VOS_UINT32 AT_HSUART_IsParityValid(AT_UART_PARITY_ENUM_UINT8 enParity);
VOS_UINT32 AT_HSUART_ValidateFlowCtrlParam(
    AT_UART_FC_DCE_BY_DTE_ENUM_UINT8    enFcDceByDte,
    AT_UART_FC_DTE_BY_DCE_ENUM_UINT8    enFcDteByDce
);
VOS_UINT32 AT_HSUART_ValidateCharFrameParam(
    AT_UART_FORMAT_ENUM_UINT8           enFormat,
    AT_UART_PARITY_ENUM_UINT8           enParity
);
AT_UART_FORMAT_PARAM_STRU *AT_HSUART_GetFormatParam(
    AT_UART_FORMAT_ENUM_UINT8           enFormat
);
VOS_UINT32 AT_HSUART_GetUdiValueByDataLen(
    AT_UART_DATA_LEN_ENUM_UINT8         enDataLen,
    VOS_UINT32                         *pulUdiValue
);
VOS_UINT32 AT_HSUART_GetUdiValueByStopLen(
    AT_UART_STOP_LEN_ENUM_UINT8         enStopLen,
    VOS_UINT32                         *pulUdiValue
);
VOS_UINT32 AT_HSUART_GetUdiValueByParity(
    AT_UART_PARITY_ENUM_UINT8           enParity,
    VOS_UINT32                         *pulUdiValue
);

VOS_UINT32 AT_HSUART_WriteMscCmd(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
);

VOS_UINT32 AT_HSUART_FreeUlDataBuff(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstImmZc
);
VOS_VOID AT_HSUART_FreeDlDataBuff(IMM_ZC_STRU *pstImmZc);
VOS_UINT32 AT_HSUART_ClearDataBuff(VOS_UINT8 ucIndex);
VOS_UINT32 AT_HSUART_GetUlDataBuff(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                       **pstImmZc,
    VOS_UINT32                         *pulLen
);
VOS_UINT32 AT_HSUART_WriteDataAsync(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstImmZc
);
VOS_UINT32 AT_HSUART_SendDlData(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
);
VOS_VOID AT_HSUART_ProcUlData(
    VOS_UINT8                           ucIndex,
    IMM_ZC_STRU                        *pstImmZc
);

VOS_UINT32 AT_HSUART_ProcDtrChange(VOS_UINT8 ucIndex, AT_DCE_MSC_STRU *pMscStru);
VOS_UINT32 AT_HSUART_ProcDtrCtrlMode(VOS_VOID);

VOS_UINT32 AT_HSUART_StartFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);
VOS_UINT32 AT_HSUART_StopFlowCtrl(
    VOS_UINT32                          ulParam1,
    VOS_UINT32                          ulParam2
);

VOS_UINT32 AT_HSUART_SendRawDataFromOm(
    VOS_UINT8                          *pucVirAddr,
    VOS_UINT8                          *pucPhyAddr,
    VOS_UINT32                          ulLen
);

VOS_VOID AT_HSUART_UlDataReadCB( VOS_VOID );
VOS_VOID AT_HSUART_MscReadCB(AT_DCE_MSC_STRU *pstDceMsc);
VOS_VOID AT_HSUART_SwitchCmdDetectCB(VOS_VOID);
VOS_VOID AT_HSUART_WaterDetectCB(water_level enLevel);
VOS_UINT32 AT_HSUART_InitPort(VOS_VOID);
VOS_UINT32 AT_HSUART_ConfigFlowCtrl(
    VOS_UINT8                           ucIndex,
    VOS_UINT32                          ulRtsFlag,
    VOS_UINT32                          ulCtsFlag
);

VOS_UINT32 AT_HSUART_ConfigCharFrame(
    VOS_UINT8                           ucIndex,
    AT_UART_FORMAT_ENUM_UINT8           enFormat,
    AT_UART_PARITY_ENUM_UINT8           enParity
);

VOS_UINT32 AT_HSUART_ConfigBaudRate(
    VOS_UINT8                           ucIndex,
    AT_UART_BAUDRATE_ENUM_UINT32        enBaudRate
);

VOS_VOID AT_HSUART_InitLink(VOS_UINT8 ucIndex);
VOS_VOID AT_HSUART_RegCallbackFunc(VOS_UINT8 ucIndex);
#endif

AT_IO_LEVEL_ENUM_UINT8 AT_GetIoLevel(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                           ucIoCtrl
);
VOS_VOID AT_CtrlDCD(
    VOS_UINT8                           ucIndex,
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel
);
VOS_VOID AT_CtrlDSR(
    VOS_UINT8                           ucIndex,
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel
);
VOS_VOID AT_CtrlCTS(
    VOS_UINT8                           ucIndex,
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel
);
VOS_VOID AT_CtrlRI(
    VOS_UINT8                           ucIndex,
    AT_IO_LEVEL_ENUM_UINT8              enIoLevel
);

#if (FEATURE_ON == FEATURE_AT_HSUART)
VOS_UINT32 AT_IsSmsRingingTe(VOS_VOID);
VOS_VOID AT_SmsRingOn(VOS_VOID);
VOS_VOID AT_SmsRingOff(VOS_VOID);
VOS_VOID AT_SmsStartRingTe(VOS_UINT32 ulNewSmsFlg);
VOS_VOID AT_SmsStopRingTe(VOS_VOID);
VOS_VOID AT_RcvTiSmsRiExpired(REL_TIMER_MSG *pstTmrMsg);
VOS_UINT32 AT_IsVoiceRingingTe(VOS_VOID);
AT_UART_RI_STATUS_ENUM_UINT8 AT_GetRiStatusByCallId(VOS_UINT8 ucCallId);
VOS_VOID AT_VoiceRingOn(VOS_UINT8 ucCallId);
VOS_VOID AT_VoiceRingOff(VOS_UINT8 ucCallId);
VOS_VOID AT_VoiceStartRingTe(VOS_UINT8 ucCallId);
VOS_VOID AT_VoiceStopRingTe(VOS_UINT8 ucCallId);
VOS_VOID AT_RcvTiVoiceRiExpired(REL_TIMER_MSG *pstTmrMsg);
#endif

VOS_VOID AT_ProcFormatResultMsc(VOS_UINT8 ucIndex, VOS_UINT32 ulReturnCode);


/* Added by j00174725 for V3R3 Cut Out Memory��2013-11-07,  Begin */
#if (FEATURE_ON == FEATURE_AT_HSIC)
extern VOS_VOID AT_HsicFourFreeDlDataBuf(VOS_UINT8 *pucBuf);
extern VOS_VOID AT_HsicFourReadDataCB( VOS_VOID );
extern VOS_UINT32 AT_HsicEst ( VOS_UINT8   ucHsicAtCtxId );
extern VOS_UINT32 AT_HsicFreeUlDataBuf(
           UDI_HANDLE                          ulUdiHdl,
           VOS_UINT8                          *pucBuf,
           VOS_UINT32                          ulLen
       );
extern VOS_UINT32 AT_HsicGetUlDataBuf(
           UDI_HANDLE                           ulUdiHdl,
           VOS_UINT8                          **ppucBuf,
           VOS_UINT32                          *pulLen
       );
extern VOS_UINT32 AT_HsicInit( VOS_VOID );
extern VOS_UINT32 AT_HsicInitUlDataBuf(
           UDI_HANDLE                          ulUdiHdl,
           VOS_UINT32                          ulEachBuffSize,
           VOS_UINT32                          ulTotalBuffNum
       );
extern VOS_VOID AT_HsicOneFreeDlDataBuf(VOS_UINT8 *pucBuf);
extern VOS_VOID AT_HsicOneReadDataCB( VOS_VOID );
extern VOS_VOID AT_HsicThreeFreeDlDataBuf(VOS_UINT8 *pucBuf);
extern VOS_VOID AT_HsicThreeReadDataCB( VOS_VOID );
extern VOS_VOID AT_HsicTwoFreeDlDataBuf(VOS_UINT8 *pucBuf);
extern VOS_VOID AT_HsicTwoReadDataCB( VOS_VOID );
extern VOS_UINT32 AT_HsicWriteData(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pucBuf,
           VOS_UINT32                          ulLen
       );
extern VOS_VOID AT_InitMuxCtx(VOS_VOID);
extern VOS_UINT32 AT_MuxEst(VOS_UINT8 ucMuxAtCtxId);
extern VOS_VOID AT_MuxInit(VOS_VOID);
extern VOS_UINT32 AT_MuxReadDataCB(
           AT_MUX_DLCI_TYPE_ENUM_UINT8         enDlci,
           VOS_UINT8                          *pData,
           VOS_UINT16                          usDataLen
       );
extern VOS_UINT32 AT_SendDataToHsic(
           VOS_UINT8                           ucIndex,
           VOS_UINT8                          *pucDataBuf,
           VOS_UINT16                          usLen
       );
extern VOS_VOID AT_HsicModemInit( VOS_VOID );
extern VOS_VOID AT_HsicModemClose(VOS_VOID);
extern VOS_VOID AT_HsicModemEnableCB(VOS_UINT8 ucEnable);
extern VOS_VOID AT_HsicModemReadDataCB( VOS_VOID );
extern VOS_VOID AT_HsicModemReadMscCB(AT_DCE_MSC_STRU *pstRcvedMsc);
#endif
/* Added by j00174725 for V3R3 Cut Out Memory��2013-11-07,  End */

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

#endif /* end of AtInputProc */

