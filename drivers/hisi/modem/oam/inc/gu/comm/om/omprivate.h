

/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Omprivate.h
  �� �� ��   : ����
  ��    ��           : ����47350
  ��������   : 2008��5��3��
  ����޸�   :
  ��������   : ��ͷ�ļ�ΪOM��ͷ�ļ�����Ҫ�ṩ��OMģ���ڲ�ʹ��
  �����б�   :
  �޸���ʷ   :
  1.��    �� : 2008��5��3��
    ��    �� : ����47350
    �޸����� : �����ļ�

******************************************************************************/
#ifndef _OM_PRIVATE_H_
#define _OM_PRIVATE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "product_config.h"
#include "cpm.h"
#include "SOCPInterface.h"
#include "NVIM_Interface.h"

#if (VOS_WIN32 != VOS_OS_VER)
#include "mdrv_om_common.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*Used to control sequence number mutex.*/
#define OM_PV_TIMEOUT                             5000

/*���ڻ�ȡ��2Bit��Modem ID ��ֵ*/
#define OM_GET_FUNCID_MODEMINFO(ucFuncID)           ((ucFuncID>>6)&0x3)
#define OM_ADD_FUNCID_MODEMINFO(ucFuncID, ucModemID)(ucFuncID|((ucModemID<<6)&0xc0))

#define OAM_ICC_RECORD_MAX_NUM           (1024)

#define OAM_ICC_RECORD_MAX_FILE          (20)

#define OM_ICC_MAX_NAME_LEN              (40)

#define PAM_VOS_QUEREY_PID_INFO_REQ      (0x5aa5)
#define PAM_VOS_QUEREY_PID_INFO_CNF      (0xa55a)

#define PAM_LOG_PARTH                    "/modem_log/PAM"
#define PAM_FILE_EXIST                   (0)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*Query PA attribute*/
enum
{
    OM_W_PA_TEMP = 1,
    OM_G_PA_TEMP,
    OM_W_PLL_LOCK,
    OM_G_PLL_LOCK,
    OM_W_HKADC,
    OM_G_HKADC,
    OM_W_BBP_PLL_LOCK,
    OM_G_BBP_PLL_LOCK,
    OM_DSP_PLL_LOCK,
    OM_ARM_PLL_LOCK,
    OM_SIM_TEMP,
    OM_TCM_STATUS,
    OM_SDMMC_STATUS,
    OM_BATTER_VOLT,
    OM_BATTER_TEMP,
    OM_OLED_TEMP,
    OM_DCXO_TEMP,
    OM_DCXO_TEMP_LT,
    OM_OLED_BUTT
};

typedef enum
{
    OM_FILE_TIMER = 1,     /*����ָʾ�����ļ�ʱ�����ĳ�ʱ��ʱ��*/
    OM_ICC_TIMER,
    OM_BUFF_TIMER,
    OM_ERRLOG_TIMER,
    OM_CONNECT_INFO_TIMER,
    OM_CLTINFO_TIMER,

    OM_FILE_TIMER_BUTT
}OM_TIMER_NAME_ENUM;

/* the definition of error number which results in reboot ,created by xucheng*/

enum
{
    LOG_FROM_PS_LOG = 0,        /* ps_log �����log */
    LOG_FROM_PRINTF,             /* printf �����log */
    LOG_FROM_OM,                /* om �����log     */
    LOG_SOURCE_BUTT
};

/* the definition of error number which results in reboot ,created by xucheng*/

enum
{
    OAM_PROTECTION_LOAD_DSP         = 0x20000000,
    OAM_PROTECTION_DSP_Init         = 0x20000001,
    OAM_UL_AHB_PARTITION_ERR        = 0x20000002,
    OAM_UL_AHB_LENGTH_ERR           = 0x20000003,
    OAM_DL_R99_AHB_HEAD_ERR         = 0x20000004,
    OAM_UL_R99_AHB_HEAD_ERR         = 0x20000005,
    OAM_DL_PP_AHB_HEAD_ERR          = 0x20000006,
    OAM_UL_PP_AHB_HEAD_ERR          = 0x20000007,
    OAM_DL_NPP_AHB_HEAD_ERR         = 0x20000008,
    OAM_UL_NPP_AHB_HEAD_ERR         = 0x20000009,
    OAM_PARA_CHECK_ERR              = 0x2000000a,
    DRV_CACHEMALLOC_ERR             = 0x2000000b,
    OAM_PROTECTION_DSP_SHARE        = 0x2000000c,
    OAM_USB_SEND_ERROR              = 0x2000000d,
    OAM_LOAD_DSP_BUFFER_ERR         = 0x2000000e,

    DRX_REPORT_ERROR                = 0x2000000f,
    DRX_REPORT_BBP_POWERDOWN_ERROR  = 0x20000010,
    DRX_REPORT_BBP_READ_ERROR       = 0x20000011,
    DRX_ACTIVATEHW_ERROR            = 0x20000012,
    DRX_REPORT_HANDSHAKE_ABNORMAL   = 0x20000013,
    DRX_PHY_PROTECT_ERROR           = 0x20000014,
    DRX_FULLNET_SET_ERROR           = 0x20000015,
    DRX_SLAVE_WAKE_IPC_ERROR        = 0x20000016,

    SPY_FLOWCTRL_POWEROFF           = 0x20002000,
    CBT_CSDR_DDR_BASE_ADDR_INVALID  = 0x20002001,
    CBT_CSDR_DTCM_BASE_ADDR_INVALID = 0x20002002,

    DRV_SOCP_ERROR_START                = 0x20000050,
    DRV_SOCP_ERROR_END                  = 0x20000060,
    OAM_REG_REPORT_ERROR_END            = 0x20000070,
    OAM_PC_LENGTH_TOO_BIG               = 0x20000080,

    HPA_2GFRAME_ISR_NOT_INTERRUPT_CALL  = 0x20000090,
    HPA_3GFRAME_ISR_NOT_INTERRUPT_CALL  = 0x20000092,

    OAM_PROTECTION_ID_BUTT              = 0x2fffffff
};

/* OM ��event���� */
enum
{
    OAM_EVENT_TIMER        = 5,
    OAM_DEGUG_EVENT_ID1    = 6,
    OAM_DEGUG_EVENT_ID2    = 7,
    OAM_DEGUG_EVENT_ID3    = 8,
    OAM_DEGUG_EVENT_ID4    = 9,
    OAM_EVENT_CONNECT_INFO = 10,

    /* �´ζ���� 100 ��ʼ���� ֮ǰ�ı�ʹ�� */
    OAM_DEGUG_EVENT_ID100  = 100,

    OAM_EVENT_BUTT
};

/* ����DRV_CACHEDMAM_ALLOC��������ռ�ʧ�ܣ�ֱ�Ӹ�λ */
#define OM_DRV_CACHEDMAM_ALLOC_ERROR()\
    mdrv_om_system_error(DRV_CACHEMALLOC_ERR, (VOS_INT)THIS_FILE_ID, (VOS_INT)__LINE__, VOS_NULL_PTR, 0)


typedef enum
{
    OM_SOCPVOTE_CALLBEGIN   = 0,
    OM_SOCPVOTE_CALLEND     = 1,
    OM_SOCPVOTE_SENDSLEEPMSG= 2,
    OM_SOCPVOTE_SENDWAKEMSG = 3,
    OM_SOCPVOTE_WARNNING    = 4,
    OM_SOCPVOTE_ERROR       = 5,
    OM_SOCPVOTE_FATAL       = 6,
    OM_SOCPVOTE_INFO_BUTT
}OM_SOCPVOTEINFO_ENUM;
typedef VOS_UINT32  OM_SOCPVOTEINFO_ENUM_UINT32;

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
/*��ѯPA���Խṹ��*/
typedef struct
{
    VOS_UINT16        usQueryType;
    VOS_INT16         sQueryResult;
}OM_PA_ITEM_STRU;

typedef struct
{
    VOS_UINT32        ulResult;
    OM_PA_ITEM_STRU   aPaItem[1];
}OM_APP_PA_ATTRIBUTE_STRU;

typedef struct
{
    VOS_UINT16              usSysMode;
    VOS_UINT8               ucNvEnable                  :1;
    VOS_UINT8               ucRficChannel               :4;  /* RFICͨ�� */
    VOS_UINT8               ucRficChannelFlag           :3;  /* RFICͨ��ʹ�ܱ�־, 0 ��ʹ��, 1 ʹ�� */
    VOS_UINT8               ucFtmMode                   :1;
    VOS_UINT8               ucRsv2                      :7;
}OM_LMT_MSG_STRU;

typedef struct
{
    VOS_UINT16              usSysMode;
    VOS_UINT16              usRsv;
}OM_ACTIVE_PHY_STRU;

typedef struct
{
    VOS_UINT16                          usSendPid;
    VOS_UINT16                          usRecvPid;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulSlice;
    VOS_UINT32                          ulReserved;
}OM_ICC_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16           usPrimId;
    VOS_UINT16           usReserved;
}PAM_VOS_QUEREY_PID_INFO_REQ_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT16           usPrimId;
    VOS_UINT16           usLen;
    VOS_UINT8            aucValue[4];
}PAM_VOS_QUEREY_PID_INFO_CNF_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_UINT32 WuepsAgingPidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID   Aging_MsgProc(MsgBlock* pMsg);
extern VOS_UINT32 WuepsRegPidInit(enum VOS_INIT_PHASE_DEFINE ip);
extern VOS_VOID   Reg_MsgProc(MsgBlock *pRcvMsg);
extern VOS_INT    OM_RuningPsStateCheckCb(VOS_VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif

