
#ifndef _AT_MNTN_H_
#define _AT_MNTN_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "TafTypeDef.h"
#include "mdrv.h"
#include "AtInternalMsg.h"
#include "MnClient.h"
/* Added by wx270776 for OM�ں�, 2015-7-24, begin */
#include "msp_diag_comm.h"
/* Added by wx270776 for OM�ں�, 2015-7-24, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* 1.1: OM_GreenChannel�ĵڶ�������usPrimId�Ķ���*/
#define     AT_OM_GREEN_CHANNEL_PS      (0xC001)                                /* PS��� */

/* ��װ��ά�ɲ��¼���Ϣͷ */
#define AT_MNTN_CFG_MSG_HDR(pstMsg, enEventId, ulEventLen)\
            (pstMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            (pstMsg)->ulSenderPid     = WUEPS_PID_AT;\
            (pstMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            (pstMsg)->ulReceiverPid   = WUEPS_PID_AT;\
            (pstMsg)->ulLength        = (ulEventLen);\
            (pstMsg)->enMsgId         = (enEventId)


/* C�˵�����λͳ����Ϣ */
#define AT_DBG_SET_SEM_INIT_FLAG(flag)              (g_stAtStatsInfo.stCCpuResetStatsInfo.ulSemInitFlg = (flag))
#define AT_DBG_SAVE_BINARY_SEM_ID(sem_id)           (g_stAtStatsInfo.stCCpuResetStatsInfo.hBinarySemId = (sem_id))
#define AT_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)        (g_stAtStatsInfo.stCCpuResetStatsInfo.ulCreateBinarySemFailNum += (n))
#define AT_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)          (g_stAtStatsInfo.stCCpuResetStatsInfo.ulLockBinarySemFailNum += (n))
#define AT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)     (g_stAtStatsInfo.stCCpuResetStatsInfo.ulLastBinarySemErrRslt = (rslt))
#define AT_DBG_SAVE_CCPU_RESET_BEFORE_NUM(n)        (g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetBeforeNum += (n))
#define AT_DBG_SAVE_CCPU_RESET_AFTER_NUM(n)         (g_stAtStatsInfo.stCCpuResetStatsInfo.ulResetAfterNum += (n))
#define AT_DBG_SAVE_HIFI_RESET_NUM(n)               (g_stAtStatsInfo.stCCpuResetStatsInfo.ulHifiResetNum += (n))

/* MODEM����ͳ����Ϣ */
#define AT_MODEM_DBG_UL_DATA_READ_CB_NUM(n)         (g_stAtStatsInfo.stModemStats.ulUlDataReadCBNum += (n))
#define AT_MODEM_DBG_UL_GET_RD_FAIL_NUM(n)          (g_stAtStatsInfo.stModemStats.ulUlGetRDFailNum += (n))
#define AT_MODEM_DBG_UL_GET_RD_SUCC_NUM(n)          (g_stAtStatsInfo.stModemStats.ulUlGetRDSuccNum += (n))
#define AT_MODEM_DBG_UL_INVALID_RD_NUM(n)           (g_stAtStatsInfo.stModemStats.ulUlInvalidRDNum += (n))
#define AT_MODEM_DBG_UL_RETURN_BUFF_SUCC_NUM(n)     (g_stAtStatsInfo.stModemStats.ulUlReturnBuffSuccNum += (n))
#define AT_MODEM_DBG_UL_RETURN_BUFF_FAIL_NUM(n)     (g_stAtStatsInfo.stModemStats.ulUlReturnBuffFailNum += (n))

/* MODEM��������ͳ����Ϣ */
#define AT_MODEM_DBG_DL_WRITE_ASYNC_SUCC_NUM(n)     (g_stAtStatsInfo.stModemStats.ulDlWriteAsyncSuccNum += (n))
#define AT_MODEM_DBG_DL_WRITE_ASYNC_FAIL_NUM(n)     (g_stAtStatsInfo.stModemStats.ulDlWriteAsyncFailNum += (n))
#define AT_MODEM_DBG_DL_FREE_BUFF_NUM(n)            (g_stAtStatsInfo.stModemStats.ulDlFreeBuffNum += (n))

/* HSUART NV��дͳ����Ϣ */
#define AT_HSUART_DBG_NV_READ_ERR(n)                (g_stAtStatsInfo.stHsUartStats.ucReadNvFailNum += (n))
#define AT_HSUART_DBG_NV_WRITE_ERR(n)               (g_stAtStatsInfo.stHsUartStats.ucWriteNvFailNum += (n))
#define AT_HSUART_DBG_NV_BAUDRATE_ERR(n)            (g_stAtStatsInfo.stHsUartStats.ucBaudRateERR += (n))
#define AT_HSUART_DBG_NV_FORMAT_ERR(n)              (g_stAtStatsInfo.stHsUartStats.ucFormatERR += (n))

/* HSUART IOCTLͳ����Ϣ */
#define AT_HSUART_DBG_IOCTL_SET_READ_CB_ERR(n)      (g_stAtStatsInfo.stHsUartStats.ucSetReadCbERR += (n))
#define AT_HSUART_DBG_IOCTL_RELLOC_READ_BUFF_ERR(n) (g_stAtStatsInfo.stHsUartStats.ucRellocReadBuffERR += (n))
#define AT_HSUART_DBG_IOCTL_SET_FREE_CB_ERR(n)      (g_stAtStatsInfo.stHsUartStats.ucSetFreeBuffCbERR += (n))
#define AT_HSUART_DBG_IOCTL_SET_MSC_READ_CB_ERR(n)  (g_stAtStatsInfo.stHsUartStats.ucSetMscReadCbERR += (n))
#define AT_HSUART_DBG_IOCTL_SET_SWITCH_CB_ERR(n)    (g_stAtStatsInfo.stHsUartStats.ucSetSwitchCmdCbERR += (n))
#define AT_HSUART_DBG_IOCTL_SET_WATER_CB_ERR(n)     (g_stAtStatsInfo.stHsUartStats.ucSetWaterCbERR += (n))
#define AT_HSUART_DBG_IOCTL_SET_BAUD_FAIL_NUM(n)    (g_stAtStatsInfo.stHsUartStats.ulSetBaudRateFailNum += (n))
#define AT_HSUART_DBG_IOCTL_SET_WLEN_FAIL_NUM(n)    (g_stAtStatsInfo.stHsUartStats.ulSetWlenFailNum += (n))
#define AT_HSUART_DBG_IOCTL_SET_STP_FAIL_NUM(n)     (g_stAtStatsInfo.stHsUartStats.ulSetStpFailNum += (n))
#define AT_HSUART_DBG_IOCTL_SET_PARITY_FAIL_NUM(n)  (g_stAtStatsInfo.stHsUartStats.ulSetParityFailNum += (n))
#define AT_HSUART_DBG_IOCTL_MSC_READ_CB_NUM(n)      (g_stAtStatsInfo.stHsUartStats.ulMscReadCBNum += (n))
#define AT_HSUART_DBG_IOCTL_MSC_WRITE_SUCC_NUM(n)   (g_stAtStatsInfo.stHsUartStats.ulMscWriteSuccNum += (n))
#define AT_HSUART_DBG_IOCTL_MSC_WRITE_FAIL_NUM(n)   (g_stAtStatsInfo.stHsUartStats.ulMscWriteFailNum += (n))
#define AT_HSUART_DBG_IOCTL_SWITCH_CB_NUM(n)        (g_stAtStatsInfo.stHsUartStats.ulSwitchCmdCBNum += (n))
#define AT_HSUART_DBG_IOCTL_CFG_FC_SUCC_NUM(n)      (g_stAtStatsInfo.stHsUartStats.ulCfgFlowCtrlSuccNum += (n))
#define AT_HSUART_DBG_IOCTL_CFG_FC_FAIL_NUM(n)      (g_stAtStatsInfo.stHsUartStats.ulCfgFlowCtrlFailNum += (n))
#define AT_HSUART_DBG_IOCTL_CLEAR_BUFF_SUCC_NUM(n)  (g_stAtStatsInfo.stHsUartStats.ulClearBuffSuccNum += (n))
#define AT_HSUART_DBG_IOCTL_CLEAR_BUFF_FAIL_NUM(n)  (g_stAtStatsInfo.stHsUartStats.ulClearBuffFailNum += (n))

/* HSUART��������ͳ����Ϣ */
#define AT_HSUART_DBG_UL_DATA_READ_CB_NUM(n)        (g_stAtStatsInfo.stHsUartStats.ulUlDataReadCBNum += (n))
#define AT_HSUART_DBG_UL_GET_RD_SUCC_NUM(n)         (g_stAtStatsInfo.stHsUartStats.ulUlGetRDSuccNum += (n))
#define AT_HSUART_DBG_UL_GET_RD_FAIL_NUM(n)         (g_stAtStatsInfo.stHsUartStats.ulUlGetRDFailNum += (n))
#define AT_HSUART_DBG_UL_INVALID_RD_NUM(n)          (g_stAtStatsInfo.stHsUartStats.ulUlInvalidRDNum += (n))
#define AT_HSUART_DBG_UL_INVALID_CMD_DATA_NUM(n)    (g_stAtStatsInfo.stHsUartStats.ulUlRcvInvalidCmdNum += (n))
#define AT_HSUART_DBG_UL_VALID_CMD_DATA_NUM(n)      (g_stAtStatsInfo.stHsUartStats.ulUlValidCmdNum += (n))
#define AT_HSUART_DBG_UL_PPP_DATA_NUM(n)            (g_stAtStatsInfo.stHsUartStats.ulUlPppDataNum += (n))
#define AT_HSUART_DBG_UL_IP_DATA_NUM(n)             (g_stAtStatsInfo.stHsUartStats.ulUlIpDataNum += (n))
#define AT_HSUART_DBG_UL_OM_DATA_NUM(n)             (g_stAtStatsInfo.stHsUartStats.ulUlOmDataNum += (n))
#define AT_HSUART_DBG_UL_DIAG_DATA_NUM(n)           (g_stAtStatsInfo.stHsUartStats.ulUlDiagDataNum += (n))
#define AT_HSUART_DBG_UL_INVALID_DATA_NUM(n)        (g_stAtStatsInfo.stHsUartStats.ulUlInvalidModeDataNum += (n))
#define AT_HSUART_DBG_UL_RETURN_BUFF_SUCC_NUM(n)    (g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffSuccNum += (n))
#define AT_HSUART_DBG_UL_RETURN_BUFF_FAIL_NUM(n)    (g_stAtStatsInfo.stHsUartStats.ulUlReturnBuffFailNum += (n))

/* HSUART��������ͳ����Ϣ */
#define AT_HSUART_DBG_DL_WRITE_ASYNC_SUCC_NUM(n)    (g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncSuccNum += (n))
#define AT_HSUART_DBG_DL_WRITE_ASYNC_FAIL_NUM(n)    (g_stAtStatsInfo.stHsUartStats.ulDlWriteAsyncFailNum += (n))
#define AT_HSUART_DBG_DL_WRITE_SYNC_SUCC_NUM(n)     (g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccNum += (n))
#define AT_HSUART_DBG_DL_WRITE_SYNC_FAIL_NUM(n)     (g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailNum += (n))
#define AT_HSUART_DBG_DL_WRITE_SYNC_SUCC_LEN(n)     (g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncSuccLen += (n))
#define AT_HSUART_DBG_DL_WRITE_SYNC_FAIL_LEN(n)     (g_stAtStatsInfo.stHsUartStats.ulDlWriteSyncFailLen += (n))
#define AT_HSUART_DBG_DL_FREE_BUFF_NUM(n)           (g_stAtStatsInfo.stHsUartStats.ulDlFreeBuffNum += (n))

/* AT��¼Msg�������� */
#define AT_MNTN_MSG_RECORD_MAX_NUM                  (100)


/* Added by wx270776 for OM�ں�, 2015-7-24, begin */
#define   TAF_LOG(Mod, SubMod, Level, String) \
          (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, "%s \r\n", (String) )

#define   TAF_LOG1(Mod, SubMod, Level, String, Para1) \
          (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, "%s, %d \r\n", (String), (VOS_INT32)(Para1) )

#define   TAF_LOG2(Mod, SubMod, Level, String, Para1, Para2) \
          (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, "%s, %d, %d \r\n", (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2) )

#define   TAF_LOG3(Mod, SubMod, Level, String, Para1, Para2, Para3) \
          (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, "%s, %d, %d, %d \r\n", (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3) )

#define   TAF_LOG4(Mod, SubMod, Level, String, Para1, Para2, Para3, Para4) \
          (VOS_VOID)DIAG_LogReport( DIAG_GEN_LOG_MODULE(VOS_GetModemIDFromPid(Mod), DIAG_MODE_UMTS, (Level)), \
                          (Mod), __FILE__, __LINE__, "%s, %d, %d, %d, %d \r\n", (String), (VOS_INT32)(Para1), (VOS_INT32)(Para2), (VOS_INT32)(Para3), (VOS_INT32)(Para4) )
/* Added by wx270776 for OM�ں�, 2015-7-24, end */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 �ṹ����: AT_FC_DEVICE_TYPE_ENUM
 �ṹ˵��: �����豸����
*****************************************************************************/
enum AT_FC_DEVICE_TYPE_ENUM
{
    AT_FC_DEVICE_TYPE_MODEM             = 0x00,             /* MODEM */
    AT_FC_DEVICE_TYPE_NCM               = 0x01,             /* NCM */
    AT_FC_DEVICE_TYPE_RMNET             = 0x02,             /* RMNET */
    AT_FC_DEVICE_TYPE_HSUART            = 0x03,             /* HSUART */

    AT_FC_DEVICE_TYPE_BUTT
};
typedef VOS_UINT32 AT_FC_DEVICE_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: AT_FC_POINT_TYPE_ENUM
 �ṹ˵��: ���ص�����
*****************************************************************************/
enum AT_FC_POINT_TYPE_ENUM
{
    AT_FC_POINT_TYPE_MODEM_PS           = 0x00,             /* MODEM PS */
    AT_FC_POINT_TYPE_MODEM_VP           = 0x01,             /* MODEM VP */
    AT_FC_POINT_TYPE_NDIS               = 0x02,             /* NCM */
    AT_FC_POINT_TYPE_RMNET              = 0x03,             /* RMNET */
    AT_FC_POINT_TYPE_HSIC               = 0x04,             /* HSIC */

    AT_FC_POINT_TYPE_BUTT
};
typedef VOS_UINT32 AT_FC_POINT_TYPE_ENUM_UINT32;

/*****************************************************************************
 �ṹ����: AT_OM_GREENCHANNEL_ERR_ENUM_UINT32
 �ṹ˵��: OM_GreenChannel�ĵ����������ɴ�һЩ��ά�ɲ���Ϣ��
           Ϊ����߶�λЧ�ʣ���psһЩ���� ������������ö�ٶ���

  1.��    ��   : 2011��10��17��
    ��    ��   : s62952
    �޸�����   : �����ļ�
*****************************************************************************/
enum AT_OM_GREENCHANNEL_ERR_ENUM
{
    AT_OM_GREENCHANNEL_PS_CID_NOT_DEFINE = 0,
    AT_OM_GREENCHANNEL_PS_CREATE_PPP_REQ_ERR,
    AT_OM_GREENCHANNEL_PS_CREATE_RAW_DATA_PPP_REQ_ERR,
    AT_OM_GREENCHANNEL_PS_IP_TYPE_DIAL_FAIL,
    AT_OM_GREENCHANNEL_PS_PPP_TYPE_DIAL_FAIL,
    AT_OM_GREENCHANNEL_PS_DEACTIVE_PDP_ERR_EVT,
    AT_OM_GREENCHANNEL_PS_ACTIVE_PDP_REJ,
    AT_OM_GREENCHANNEL_PS_MODIFY_PDP_REJ,
    AT_OM_GREENCHANNEL_PS_NET_ORIG_DEACTIVE_IND,

    AT_OM_GREENCHANNEL_ERR_BUTT
};
typedef VOS_UINT32 AT_OM_GREENCHANNEL_ERR_ENUM_UINT32;


/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : AT_MNTN_MSC_STRU
 �ṹ˵��  : �ܽ��źŽṹ

  1.��    ��   : 2011��10��17��
    ��    ��   : s62952
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    AT_INTER_MSG_ID_ENUM_UINT32         enMsgId;            /* ��Ϣ����     */  /* _H2ASN_Skip */
    VOS_UINT32                          ulPortId;           /* �˿�ID */
    AT_DCE_MSC_STRU                     stDceMscInfo;       /* �ܽ��ź���Ϣ */

} AT_MNTN_MSC_STRU;

/*****************************************************************************
 �ṹ��    : AT_MNTN_FLOW_CTRL_STRU
 �ṹ˵��  : ���ؿ�ά�ɲ�ṹ

  1.��    ��   : 2011��10��17��
    ��    ��   : s62952
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    AT_INTER_MSG_ID_ENUM_UINT32         enMsgId;            /* ��Ϣ����     */  /* _H2ASN_Skip */
    VOS_UINT32                          ulPortId;           /* �˿�ID */
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enDevice;

} AT_MNTN_FLOW_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : AT_MNTN_FC_POINT_STRU
 �ṹ˵��  : ���ص��ά�ɲ�ṹ

  1.��    ��   : 2013��11��12��
    ��    ��   : A00165503
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    AT_INTER_MSG_ID_ENUM_UINT32         enMsgId;            /* ��Ϣ����     */  /* _H2ASN_Skip */
    VOS_UINT32                          ulPortId;           /* �˿�ID */
    AT_FC_POINT_TYPE_ENUM_UINT32        enPoint;

} AT_MNTN_FC_POINT_STRU;

/*****************************************************************************
 �ṹ��    : AT_RPT_PORT_STRU
 �ṹ˵��  : �����ϱ��˿ڽṹ

  1.��    ��   : 2014��8��1��
    ��    ��   : n00269697
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_CLIENT_TAB_INDEX_UINT8           enAtClientTabIndex;
    VOS_UINT8                           ucReportFlg;                            /* �ö˿��Ƿ����������ϱ���VOS_TRUEΪ����VOS_FALSEΪ������Ĭ������ */
    MODEM_ID_ENUM_UINT16                enModemId;                              /* �ö˿������ĸ�modem */
} AT_RPT_PORT_STRU;

/*****************************************************************************
 �ṹ��    : AT_MNTN_RPTPORT_STRU
 �ṹ˵��  : �����ϱ��˿ڿ�ά�ɲ�ṹ

  1.��    ��   : 2014��8��1��
    ��    ��   : n00269697
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                                              /* _H2ASN_Skip */
    AT_INTER_MSG_ID_ENUM_UINT32         enMsgId;
    AT_RPT_PORT_STRU                    astAtRptPort[AT_MAX_CLIENT_NUM];
} AT_MNTN_RPTPORT_STRU;

/*****************************************************************************
 �ṹ��    : AT_MNTN_MODEM_STATS_STRU
 �ṹ˵��  : MODEM�豸ͳ����Ϣ�ṹ

  1.��    ��   : 2011��10��17��
    ��    ��   : s62952
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    /* ����ͳ����Ϣ */
    VOS_UINT32                          ulUlDataReadCBNum;
    VOS_UINT32                          ulUlGetRDSuccNum;
    VOS_UINT32                          ulUlGetRDFailNum;
    VOS_UINT32                          ulUlInvalidRDNum;
    VOS_UINT32                          ulUlReturnBuffSuccNum;
    VOS_UINT32                          ulUlReturnBuffFailNum;

    /* ����ͳ����Ϣ */
    VOS_UINT32                          ulDlWriteAsyncSuccNum;
    VOS_UINT32                          ulDlWriteAsyncFailNum;
    VOS_UINT32                          ulDlFreeBuffNum;
    VOS_UINT32                          ulReserved;
} AT_MNTN_MODEM_STATS_STRU;

/*****************************************************************************
 �ṹ��    : AT_MNTN_HSUART_STATS_STRU
 �ṹ˵��  : ��¼UART�Ŀ�ά�ɲ���Ϣ

  1.��    ��   : 2013��09��21��
    ��    ��   : j00174725
    �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    /* NV��ȡͳ����Ϣ */
    VOS_UINT8                           ucReadNvFailNum;
    VOS_UINT8                           ucWriteNvFailNum;
    VOS_UINT8                           ucBaudRateERR;
    VOS_UINT8                           ucFormatERR;

    /* IOCTRLͳ����Ϣ */
    VOS_UINT8                           ucSetReadCbERR;
    VOS_UINT8                           ucRellocReadBuffERR;
    VOS_UINT8                           ucSetFreeBuffCbERR;
    VOS_UINT8                           ucSetMscReadCbERR;
    VOS_UINT8                           ucSetSwitchCmdCbERR;
    VOS_UINT8                           ucSetWaterCbERR;
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT8                           ulSetBaudRateFailNum;
    VOS_UINT8                           ulSetWlenFailNum;
    VOS_UINT8                           ulSetStpFailNum;
    VOS_UINT8                           ulSetParityFailNum;
    VOS_UINT8                           aucReserved2[4];
    VOS_UINT32                          ulMscReadCBNum;
    VOS_UINT32                          ulMscWriteSuccNum;
    VOS_UINT32                          ulMscWriteFailNum;
    VOS_UINT32                          ulSwitchCmdCBNum;
    VOS_UINT32                          ulCfgFlowCtrlSuccNum;
    VOS_UINT32                          ulCfgFlowCtrlFailNum;
    VOS_UINT32                          ulClearBuffSuccNum;
    VOS_UINT32                          ulClearBuffFailNum;

    /* ����ͳ����Ϣ */
    VOS_UINT32                          ulUlDataReadCBNum;
    VOS_UINT32                          ulUlGetRDSuccNum;
    VOS_UINT32                          ulUlGetRDFailNum;
    VOS_UINT32                          ulUlInvalidRDNum;
    VOS_UINT32                          ulUlRcvInvalidCmdNum;
    VOS_UINT32                          ulUlValidCmdNum;
    VOS_UINT32                          ulUlIpDataNum;
    VOS_UINT32                          ulUlPppDataNum;
    VOS_UINT32                          ulUlRcvCsdDataNum;
    VOS_UINT32                          ulUlOmDataNum;
    VOS_UINT32                          ulUlDiagDataNum;
    VOS_UINT32                          ulUlInvalidModeDataNum;
    VOS_UINT32                          ulUlReturnBuffSuccNum;
    VOS_UINT32                          ulUlReturnBuffFailNum;

    /* ����ͳ����Ϣ */
    VOS_UINT32                          ulDlWriteAsyncSuccNum;
    VOS_UINT32                          ulDlWriteAsyncFailNum;
    VOS_UINT32                          ulDlWriteSyncSuccNum;
    VOS_UINT32                          ulDlWriteSyncFailNum;
    VOS_UINT32                          ulDlWriteSyncSuccLen;
    VOS_UINT32                          ulDlWriteSyncFailLen;
    VOS_UINT32                          ulDlFreeBuffNum;

} AT_MNTN_HSUART_STATS_STRU;

/*****************************************************************************
 �ṹ��    : AT_DEBUG_INFO_STRU
 �ṹ˵��  : Debug��Ϣ

  1.��    ��   :
    ��    ��   : z00220246
    �޸�����   : �����ṹ

  2.��    ��   : 2015��5��27��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPcuiCtrlConcurrentFlg;                /* PCUI��CTRL�ڲ�����־ */
    VOS_UINT8                           ucPcuiPsCallFlg;                        /* PCUI��ģ��NDISDUP���ű�־ */
    VOS_UINT8                           ucPcuiUserId;                           /* PCUI��ģ���ĸ��˿ڲ��� */
    VOS_UINT8                           ucCtrlPsCallFlg;                        /* CTRL��ģ��NDISDUP���ű�־ */
    VOS_UINT8                           ucCtrlUserId;                           /* CTRL��ģ���ĸ��˿ڲ��� */
    VOS_UINT8                           ucPcui2PsCallFlg;                       /* PCUI2��ģ��NDISDUP���ű�־ */
    VOS_UINT8                           ucPcui2UserId;                          /* PCUI2��ģ���ĸ��˿ڲ��� */
    VOS_UINT8                           ucUnCheckApPortFlg;
}AT_DEBUG_INFO_STRU;

/*****************************************************************************
 �ṹ��    : AT_RESET_MNTN_INFO_STRU
 Э����  :
 �ṹ˵��  : RESET��Ϣ
 1.��    ��   :
   ��    ��   : f00179208
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    /* ��λ�ź�����Ϣ */
    VOS_SEM                 hBinarySemId;                                       /* �������ź���ID */
    VOS_UINT32              ulSemInitFlg;                                       /* ��ʼ����ʶ, VOS_TRUE: �ɹ�; VOS_FALSE: ʧ�� */
    VOS_UINT32              ulCreateBinarySemFailNum;                           /* �����������ź���ʧ�ܴ��� */
    VOS_UINT32              ulLockBinarySemFailNum;                             /* ���������ź���ʧ�ܴ��� */
    VOS_UINT32              ulLastBinarySemErrRslt;                             /* ���һ�����������ź���ʧ�ܽ�� */
    VOS_UINT32              ulResetBeforeNum;                                   /* C�˸�λǰ�Ĵ��� */
    VOS_UINT32              ulResetAfterNum;                                    /* C�˸�λ��Ĵ��� */
    VOS_UINT32              ulHifiResetNum;                                     /* HIFI��λ�Ĵ��� */
    VOS_UINT32              ulReserved;
}AT_RESET_STATS_INFO_STRU;

/*****************************************************************************
 �ṹ��    : AT_MNTN_STATS_STRU
 �ṹ˵��  : ��¼ATģ��Ŀ�ά�ɲ���Ϣ
*****************************************************************************/
typedef struct
{
    AT_RESET_STATS_INFO_STRU            stCCpuResetStatsInfo;
    AT_MNTN_MODEM_STATS_STRU            stModemStats;
    AT_MNTN_HSUART_STATS_STRU           stHsUartStats;

} AT_MNTN_STATS_STRU;

/*****************************************************************************
 �ṹ��    : AT_MNTN_MSG_RECORD_STRU
 Э����  :
 �ṹ˵��  : ��¼����ATģ���ÿ����Ϣ��Pid�Լ���ϢId
 1.��    ��   : 2014��09��04��
   ��    ��   : g00261581
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSendPid;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulSliceStart;
    VOS_UINT32                          ulSliceEnd;
} AT_MNTN_MSG_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : AT_MNTN_MSG_RECORD_INFO_STRU
 Э����  :
 �ṹ˵��  : ��¼����ATģ�����Ϣ��Ϣ
 1.��    ��   : 2014��09��04��
   ��    ��   : g00261581
   �޸�����   : �����ṹ
*****************************************************************************/
typedef struct
{
    AT_MNTN_MSG_RECORD_STRU             astAtMntnMsgRecord[AT_MNTN_MSG_RECORD_MAX_NUM];
    VOS_UINT32                          ulCurrentIndex;
} AT_MNTN_MSG_RECORD_INFO_STRU;

/*****************************************************************************
  7 OTHERS����
*****************************************************************************/

/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    AT_INTER_MSG_ID_ENUM_UINT32         enMsgId;                                /* _H2ASN_MsgChoice_Export AT_INTER_MSG_ID_ENUM_UINT32 */
    VOS_UINT8                           aucMsg[4];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          AT_INTER_MSG_ID_ENUM_UINT32
    ****************************************************************************/
} AT_MNTN_MSG_DATA;
/* _H2ASN_Length UINT32 */

typedef struct
{
    VOS_MSG_HEADER
    AT_MNTN_MSG_DATA                    stMsgData;
} AtMntn_MSG;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/
extern AT_MNTN_STATS_STRU               g_stAtStatsInfo;
extern AT_DEBUG_INFO_STRU               g_stAtDebugInfo;


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_UINT8 AT_GetPcuiCtrlConcurrentFlag(VOS_VOID);
VOS_UINT8 AT_GetPcuiPsCallFlag(VOS_VOID);

VOS_UINT8 AT_GetPcuiUsertId(VOS_VOID);
VOS_UINT8 AT_GetCtrlPsCallFlag(VOS_VOID);
VOS_UINT8 AT_GetCtrlUserId(VOS_VOID);
VOS_UINT8 AT_GetPcui2PsCallFlag(VOS_VOID);
VOS_UINT8 AT_GetPcui2UserId(VOS_VOID);
VOS_VOID AT_MNTN_TraceRPTPORT(VOS_VOID);
VOS_VOID AT_SetUnCheckApPortFlg(
    VOS_UINT8                           ucFlag
);
VOS_UINT8 AT_GetUnCheckApPortFlg(VOS_VOID);

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceInputMsc
 ��������  : �ܽ��ź������ά�ɲ�
 �������  : ucIndex   - �˿�����
             pstDceMsc - �ܽ��ź���Ϣ(�����߱�֤�ǿ�)
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceInputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
);


/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceOutputMsc
 ��������  : �ܽ��ź������ά�ɲ�
 �������  : ucIndex   - �˿�����
             pstDceMsc - �ܽ��ź���Ϣ(�����߱�֤�ǿ�)
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceOutputMsc(
    VOS_UINT8                           ucIndex,
    AT_DCE_MSC_STRU                    *pstDceMsc
);

/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceStartFlowCtrl
 ��������  : �������ؿ�ά�ɲ�
 �������  : ucIndex    - �˿�����
             enFcDevive - �����豸
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceStartFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
);


/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceStopFlowCtrl
 ��������  : ֹͣ���ؿ�ά�ɲ�
 �������  : ucIndex    - �˿�����
             enFcDevive - �����豸
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceStopFlowCtrl(
    VOS_UINT8                           ucIndex,
    AT_FC_DEVICE_TYPE_ENUM_UINT32       enFcDevive
);


/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceRegFcPoint
 ��������  : ע�����ص��ά�ɲ�
 �������  : ucIndex   - �˿�����
             enFcPoint - ���ص�
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceRegFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
);


/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceDeregFcPoint
 ��������  : ȥע�����ص��ά�ɲ�
 �������  : ucIndex   - �˿�����
             enFcPoint - ���ص�
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceDeregFcPoint(
    VOS_UINT8                           ucIndex,
    AT_FC_POINT_TYPE_ENUM_UINT32        enFcPoint
);


/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceCmdResult
 ��������  : AT����ظ���ά�ɲ�
 �������  : ucIndex   - �˿�����
             pucData   - ��������
             usDataLen - ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceCmdResult(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
);


/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceCmdBuffer
 ��������  : ���������ά�ɲ�
 �������  : ucIndex   - �˿�����
             pucData   - ��������
             usDataLen - ���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceCmdBuffer(
    VOS_UINT8                           ucIndex,
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen
);


/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceContextData
 ��������  : ��AT�ⲿ��������ΪSDT��Ϣ���ͳ�ȥ���Ա��ڻط�ʱͨ��׮������ԭ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceContextData(VOS_VOID);


/*****************************************************************************
 �� �� ��  : AT_MNTN_TraceClientData
 ��������  : ����ATģ��Ŀͻ��˿�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_MNTN_TraceClientData(VOS_VOID);


/*****************************************************************************
 �� �� ��  : AT_InitHsUartStats
 ��������  : ��ʼ��UART��ά�ɲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_InitHsUartStats(VOS_VOID);


/*****************************************************************************
 �� �� ��  : AT_MODEM_Help
 ��������  : ��ʼ��UART��ά�ɲ���Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
*****************************************************************************/
VOS_VOID AT_InitModemStats(VOS_VOID);

VOS_VOID AT_SetPcuiCtrlConcurrentFlag(VOS_UINT8 ucFlag);

VOS_VOID AT_ShowClientCtxInfo(VOS_VOID);

VOS_VOID AT_RecordAtMsgInfo(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulSliceStart,
    VOS_UINT32                          ulSliceEnd
);

VOS_VOID AT_InitMntnCtx(VOS_VOID);

VOS_VOID AT_SetPcuiPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
);
VOS_VOID AT_SetCtrlPsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
);
VOS_VOID AT_SetPcui2PsCallFlag(
    VOS_UINT8                           ucFlag,
    VOS_UINT8                           ucIndex
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

