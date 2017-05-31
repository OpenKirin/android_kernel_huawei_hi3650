/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : omnvinterace.hf
  �� �� ��      : ����
  ��    ��      : ���±�
  ��������      : 2013��5��15��
  ����޸�      :
  ��������      : ��ͷ�ļ�ΪOM��NV�ṹͷ�ļ�����Ҫ��������NV bin�ļ�
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2013��5��15��
    ��    ��    : j00174725
    �޸�����    : �����ļ�

******************************************************************************/


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#ifndef __OM_NV_INTERFACE_H__
#define __OM_NV_INTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif
/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ���Կ�������Ϣ */
#define USIMM_TEST_CARD_CFG_NUM                     (8)
#define USIMM_TEST_CARD_PLMN_LEN                    (3)
#define USIMM_CDMATEST_CARD_PLMN_LEN                (2)

/*�ϻ�������ĸ���*/
#define OM_AGING_TEST_NUM                           (20)

#define SYS_ZSP_LDF_NUM                             (64)

#define SYS_HIFI_LDF_NUM                            (64)


#define STK_TERMINAL_ND                             (0x1)
#define STK_TERMINAL_NK                             (0x2)
#define STK_TERMINAL_NA                             (0x4)
#define STK_TERMINAL_NS                             (0x8)
#define STK_TERMINAL_NL                             (0x10)

#define STK_SIM_PROFILE_DEFAULT                     {0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0x0F, 0x00, 0xDF, 0x7F, 0x03,\
                                                     0x00, 0x1F, 0xE2, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00}

#define STK_USIM_PROFILE_DEFAULT                    {0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0x00, 0xDF, 0xFF, 0x03,\
                                                     0x00, 0x1F, 0xE2, 0x00, 0x00, 0x00, 0xC3, 0xCB, 0x00, 0x00,\
                                                     0x00, 0x01, 0x00, 0x00, 0x91, 0x00, 0x00, 0x00, 0x00, 0x08}

#define VSIM_DH_PUBIIC_KEY                          (128)
#define VSIM_DH_PRIVATE_KEY                         (128)
#define VSIM_DH_AGREE_KEY                           (256)
#define VSIM_FILE_WRITE_COUNT                       (1)
#define VSIM_FILE_READ_COUNT                        (1)

#define VSIM_KEYLEN_MAX                             (128)                   /* ��Կ���Ȳ�����128�ֽ� */

#define VSIM_EF_LOCI_LEN                            (11)
#define VSIM_EF_PS_LOCI_LEN                         (14)
#define VSIM_EF_FPLMN_LEN                           (60)                    /* FPLMN����20����ʵ�� */

#define ESN_NV_DATA_LEN                             (8)
#define MEID_NV_DATA_LEN                            (8)

#define PESN_NV_DATA_LEN                            (4)
#define MEID_NV_DATA_LEN_NEW                        (7)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : SC_APSEC_DEFAULT_KEY_VER_ENUM
 ö��˵��  : ��ȫ�洢Ĭ��ֵ�汾ö��

  1.��    ��   : 2013��01��05��
    ��    ��   : l00198894
    �޸�����   : V7R1C50 ISDB��ȫ�洢��Ŀ����
*****************************************************************************/
enum SC_APSEC_DEFAULT_KEY_VER_ENUM
{
    SC_APSEC_DEFAULT_KEY_VER_TEST       =   0,              /* ���԰汾 */
    SC_APSEC_DEFAULT_KEY_VER_DCM        =   1,              /* Docomo�汾 */
    SC_APSEC_DEFAULT_KEY_VER_BUTT,
};
typedef VOS_UINT8 SC_APSEC_DEFAULT_KEY_VER_ENUM_UINT8;

enum OM_OUTPUT_PORT
{
    OM_OUTPUT_SHELL = 0,        /*�����ṩ��SHELLͨ��*/
    OM_OUTPUT_FS,               /*д�ļ�ϵͳ��ʽ*/
    OM_OUTPUT_SDT,              /*�����SDT��*/
    OM_OUTPUT_BUTT
};
typedef VOS_UINT32      OM_OUTPUT_PORT_ENUM_UINT32;

/*****************************************************************************
 ö����    : AT_PHY_PORT_ENUM
 ö��˵��  : ����˿ں�ö��ֵ
*****************************************************************************/
enum AT_PHY_PORT_ENUM
{
    AT_UART_PORT = 0,
    AT_PCUI_PORT,
    AT_CTRL_PORT,
    AT_HSUART_PORT,
    AT_PCUI2_PORT,
    AT_PORT_BUTT
};
typedef VOS_UINT32  AT_PHY_PORT_ENUM_UINT32;

enum
{
    CPM_IND_PORT = AT_PORT_BUTT,    /* OM�����ϱ��˿� */
    CPM_CFG_PORT,                   /* OM���ö˿� */
    CPM_SD_PORT,
    CPM_WIFI_OM_IND_PORT,           /* WIFI��OM�����ϱ��˿� */
    CPM_WIFI_OM_CFG_PORT,           /* WIFI��OM�����·��˿� */
    CPM_WIFI_AT_PORT,               /* WIFI��AT�˿� */
    CPM_HSIC_IND_PORT,
    CPM_HSIC_CFG_PORT,
    CPM_VCOM_IND_PORT,              /* VCOM��OM�����ϱ��ӿ� */
    CPM_VCOM_CFG_PORT,              /* VCOM��OM���ýӿ� */
    CPM_FS_PORT,
    CPM_PORT_BUTT
};
typedef VOS_UINT32  CPM_PHY_PORT_ENUM_UINT32;

enum
{
    CPM_OM_PORT_TYPE_USB,
    CPM_OM_PORT_TYPE_VCOM,
    CPM_OM_PORT_TYPE_WIFI,
    CPM_OM_PORT_TYPE_SD,
    CPM_OM_PORT_TYPE_FS,
    CPM_OM_PORT_TYPE_HSIC,
    CBP_OM_PORT_TYPE_BUTT
};
typedef VOS_UINT32 CPM_OM_PORT_ENUM_UINT32;



/*****************************************************************************
 ö����    : VSIM_ALGORITHM_TYPE_ENUM
 ö��˵��  : �ӽ����㷨

  1.��    ��   : 2013��08��27��
    ��    ��   : zhuli
    �޸�����   : V9R1 vSIM��Ŀ����
*****************************************************************************/
enum VSIM_ALGORITHM_TYPE_ENUM
{
    VSIM_ALGORITHM_NULL = 0,
    VSIM_ALGORITHM_AES  = 1,
    VSIM_ALGORITHM_3DES = 2,
    VSIM_ALGORITHM_BUTT
};
typedef VOS_UINT32 VSIM_ALGORITHM_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    : VSIM_ACTIVE_TYPE_ENUM
 ö��˵��  : ���⿨�Ƿ�ʹ��

  1.��    ��   : 2013��08��27��
    ��    ��   : zhuli
    �޸�����   : V9R1 vSIM��Ŀ����
*****************************************************************************/
enum VSIM_ACTIVE_TYPE_ENUM
{
    VSIM_VIRT_CARD_DEACTIVE = 0,
    VSIM_VIRT_CARD_ACTIVE   = 1,
    VSIM_ACTIVE_TYPE_BUTT
};
typedef VOS_UINT8 VSIM_ACTIVE_TYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : USIMM_CARD_STATUS_REG_TYPE_ENUM
 ö��˵��  : SIM��ע��ص�����������

  1.��    ��   : 2013��09��25��
    ��    ��   : h59254
    �޸�����   : V3R3 SIM���Ȳ岦��Ŀ����
*****************************************************************************/
enum USIMM_CARD_STATUS_REG_TYPE_ENUM
{
    USIMM_CARD_STATUS_REG_TYPE_E5       = 0,    /* ע��E5���͵Ŀ�״̬����ص����� */
    USIMM_CARD_STATUS_REG_TYPE_M2M      = 1,    /* ע��M2M���͵Ŀ�״̬����ص����� */
    USIMM_CARD_STATUS_REG_TYPE_BUTT
};

typedef VOS_UINT16 USIMM_CARD_STATUS_REG_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    : EVENT_RESEND_FLAG_ENUM
 ö��˵��  : �¼������ط����

  1.��    ��   : 2014��01��16��
    ��    ��   : zhuli
    �޸�����   : V9R1 C+L ��Ŀ����
*****************************************************************************/
enum EVENT_RESEND_FLAG_ENUM
{
    EVENT_RESEND_OFF        = 0,
    EVENT_RESEND_ON         = 1,
    EVENT_RESEND_FLAG_BUTT
};
typedef VOS_UINT8 EVENT_RESEND_FLAG_ENUM_UINT8;

/*****************************************************************************
 ö����    : ESN_MEID_FLAG_ENUM
 ö��˵��  : �¼������ط����

  1.��    ��   : 2014��07��3��
    ��    ��   : zhuli
    �޸�����   : V9R1 C+L ��Ŀ����
*****************************************************************************/
enum ESN_MEID_FLAG_ENUM
{
    ESN_MEID_DISABLE        = 0,
    ESN_ME_ENABLE_FLAG      = 1,
    MEID_ME_ENABLE_FLAG     = 2,
    ESN_MEID_ENABLE_BOTH    = 3,
    ESN_MEID_ENABLE_FLAG_BUTT
};
typedef VOS_UINT8 ESN_MEID_FLAG_ENUM_UINT8;


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
�ṹ��    : OM_PASSWORD_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 1

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPassword[16];
}OM_AUTH_PASSWORD_STRU;

/*****************************************************************************
�ṹ��    : OM_VERIFYCNT_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 2 �����ݻָ���

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usVerifyCnt;
}OM_VERIFYCNT_STRU;


/*****************************************************************************
�ṹ��    : OM_TTL_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 3

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                        ulTtl;
}OM_TTL_STRU;

/*****************************************************************************
�ṹ��    : OM_TTL_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 5

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usYear;
    VOS_UINT16                          usMonth;
    VOS_UINT16                          usDayOfWeek;
    VOS_UINT16                          usDay;
    VOS_UINT16                          usHour;
    VOS_UINT16                          usMinute;
    VOS_UINT16                          usSecond;
    VOS_UINT16                          usMilliSeconds;
}OM_CALIBRATED_TIME_STRU;

/*****************************************************************************
�ṹ��    : OM_SERIAL_NUM_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 6 SerialNumber

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucSerialNumber[20];
}OM_SERIAL_NUM_STRU;

/*****************************************************************************
�ṹ��    : OM_LOG_FILE_MAX_SIZE_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 8 LogFileMaxSize

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLogFileMaxSize;
}OM_LOG_FILE_MAX_SIZE_STRU;


/*****************************************************************************
�ṹ��    : OM_WATCHDOG_FLAG_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 9 WatchDogFlag

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWatchDogFlag; /*[0,1]*/
}OM_WATCHDOG_FLAG_STRU;

/*****************************************************************************
�ṹ��    : OM_KICKDOG_TIME_STRU
�ṹ˵��  :
��ӦNVID: 11 KickDog_Time

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulKickDogTime;
}OM_KICKDOG_TIME_STRU;

/*****************************************************************************
�ṹ��    : OM_SCHEDULE_WATCH_TIME_STRU
�ṹ˵��  :
��ӦNVID: 12 ScheduleWatchDog_Time

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulScheduleWatchDogTime;
}OM_SCHEDULE_WATCH_TIME_STRU;

/*****************************************************************************
�ṹ��    : OM_MONITORPARA_CTRL_STRU
�ṹ˵��  :
��ӦNVID:   MonitorParaCtrl

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTempOverCount;
    VOS_UINT8                           ucTempResumeCount;
    VOS_UINT8                           ucTempCloseCount;
    VOS_UINT8                           ucTempReserve;
    VOS_UINT32                          ulWaitTimer;
}OM_MONITORPARA_CTRL_STRU;

/*****************************************************************************
�ṹ��    : OM_USIM_TEMP_PROTECT_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 14 UsimTempProtect

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulProtectEnable;
    VOS_INT32                           lPmicCloseAdcThreshold;
    VOS_INT32                           lPmicAlarmAdcThreshold;
    VOS_INT32                           lPmicResumeAdcThreshold;
    OM_MONITORPARA_CTRL_STRU            stMonitorParaCtrl;
}OM_USIM_TEMP_PROTECT_STRU;


/*****************************************************************************
�ṹ��    : OM_RF_CONFIG_STRU
�ṹ˵��  :
��ӦNVID: 16 RfConfig

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    MODEM_ID_ENUM_UINT16                enModemID;
    VOS_UINT16                          usNetworkMode;  /*����ģʽ*/
    VOS_UINT16                          usBand;
    VOS_UINT16                          usSlotCnt;      /*ʱ϶��*/
    VOS_UINT16                          usChannel;
    VOS_UINT16                          usPower;        /*PA����*/
    VOS_UINT16                          usModType;      /*�������ģʽ*/
}OM_RF_CONFIG_STRU;


/*****************************************************************************
�ṹ��    : OM_AGINGTEST_TABLE_STRU
�ṹ˵��  : �ϻ����Զ�ӦNV��Ľṹ
��ӦNVID: 16 AgingTestTable

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIsEnable;     /*�Ƿ������ϻ����ԣ�VOS_YES/VOS_NO*/
    VOS_UINT32                          ulTimerLen;     /*��ʱ�����ȣ���λΪ����*/
    VOS_UINT32                          ulNumber;       /*ָʾ���������ĸ���*/
    OM_RF_CONFIG_STRU                   astOmRfConfig[OM_AGING_TEST_NUM];
}OM_AGING_TEST_NV_STRU;

/*****************************************************************************
�ṹ��    : OM_LIVE_TIME_CONTROL_STRU
�ṹ˵��  : ��������ʱ���¼����
��ӦNVID: 22 LiveTimeControl

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/

typedef struct
{
    VOS_UINT32                          ulEnable;
    VOS_UINT32                          ulCycle;
} OM_LIVE_TIME_CONTROL_STRU;


/*****************************************************************************
�ṹ��    : OM_LIVE_TIME_STRU
�ṹ˵��  : ��������ʱ��
��ӦNVID: 23 LiveTime

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLiveTime;
}OM_LIVE_TIME_STRU;

/*****************************************************************************
�ṹ��    : OM_SPY_QOSCNF_STRU
�ṹ˵��  :
��ӦNVID:  Spy QOSCNF

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDownLoadQos;
    VOS_UINT16                          usUpLoadQos;
}OM_SPY_QOSCNF_STRU;

/*****************************************************************************
�ṹ��    : OM_MONITOR_CPU_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 24 MonitorCPU

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSPYCPUEnable;
    VOS_UINT8                           ucCPUUpLimit;
    VOS_UINT8                           ucCPUDownLimit;
    VOS_UINT8                           ucSleepRunBase;
    VOS_UINT8                           ucSleepWFIBase;
    VOS_UINT8                           ucUpLimitTimeMax;
    VOS_UINT8                           ucDownLimitTimeMax;
    VOS_UINT8                           ucRepirValue;
    OM_SPY_QOSCNF_STRU                  astSpyQosCnf[2];
}OM_MONITOR_CPU_STRU;

/*****************************************************************************
�ṹ��    : OM_MAX_REG_CNT_GSM_STRU
�ṹ˵��  :
��ӦNVID: 28 Max_Reg_Cnt_in_GSM_Mode

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRegCnt;
}OM_MAX_REG_CNT_GSM_STRU;

/*****************************************************************************
�ṹ��    : OM_DFS_CONFIG_THRESHOLD_STRU
�ṹ˵��  :
��ӦNVID:  Threshold

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usUpLimite;
    VOS_UINT16                          usDownLimite;
}OM_DFS_CONFIG_THRESHOLD_STRU;

/*****************************************************************************
�ṹ��    : OM_DFS_CONFIG_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 29 DFS_Config

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulEnableFlag;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT16                          usUpTime;
    VOS_UINT16                          usDownTime;
    VOS_UINT32                          ulProfileNum;
    OM_DFS_CONFIG_THRESHOLD_STRU        astThreshold[20];
}OM_DFS_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : OM_SW_VER_FLAG_STRU
�ṹ˵��  :
��ӦNVID: 36 NV_SW_VER_Flag

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulNvSwVerFlag; /*[0,1]*/
}OM_SW_VER_FLAG_STRU;

/*****************************************************************************
�ṹ��    : OM_ERRORLOG_ENABLE_FLAG_STRU
�ṹ˵��  :
��ӦNVID: 37 NV_ERRORLOG_ENABLEFLAG

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulErrorLogEnable; /*[0,1]*/
}OM_ERRORLOG_ENABLE_FLAG_STRU;

/*****************************************************************************
�ṹ��    : OM_ERRORLOG_FLUSHBUFINTER_STRU
�ṹ˵��  :
��ӦNVID: 38 NV_ERRORLOG_FLUSHBUFINTERVALUE

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulErrorFlushInter;
}OM_ERRORLOG_FLUSHBUFINTER_STRU;

/*****************************************************************************
�ṹ��    : OM_ERRORLOG_RECORDPERIOD_STRU
�ṹ˵��  :
��ӦNVID: 39 NV_ERRORLOG_RECORDPERIOD

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulErrorRecord; /*[0,103680]*/
}OM_ERRORLOG_RECORDPERIOD_STRU;


/*****************************************************************************
�ṹ��    : OM_MONITOR_PARA_CTRL_STRU
�ṹ˵��  :
��ӦNVID: 40 MonitorParaCtrl

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucTempOverCount;     /*������ģʽ���¶����������澯���޻�͹������޵ļ��޴���*/
    VOS_UINT8                           ucTempRsumeCount;    /*�ڵ͹���ģʽ��澯ģʽ���¶��������ڸ澯�ŵļ��޴���*/
    VOS_UINT8                           ucTempCloseCount;    /*�ڽ���ģʽ���¶����������澯���޵ļ��޴���*/
    VOS_UINT8                           ucTempPowerOffCount; /*�����µ����޵ļ��޴���*/
    VOS_UINT32                          ulWaitTimer;         /*�ȴ���ʱ��ʱ��*/
}TEMP_PARA_CTRL_STRU;

/*****************************************************************************
�ṹ��    : OM_USIM_TEMP_PROTECT_NEW_STRU
�ṹ˵��  :
��ӦNVID: 40 UsimTempProtect_New

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIsEnable;           /*�Ƿ���Ҫ������������, 0Ϊ�رգ�1Ϊ����*/
    VOS_UINT32                          ulLocation;           /*ʹ��������¶���Ϊ�±������룬�ò���ֱ����Ϊ��ν������ĺ���,Ŀǰ��ȡֵ��Χ��0��6 */
    VOS_INT32                           lPowerOffThreshold;   /*�����µ�ģʽ������*/
    VOS_INT32                           lCloseAdcThreshold;   /*����͹���ģʽ���¶�����*/
    VOS_INT32                           lAlarmAdcThreshold;   /*��Ҫ���и����������¶�����*/
    VOS_INT32                           lResumeAdcThreshold;  /*�ָ�������ģʽ���¶�����*/
    VOS_INT32                           lSIMPowerOffThreshold;  /*E5��̬��SIM���±�������*/
    TEMP_PARA_CTRL_STRU                 stTempCtrlPara;
}SPY_TEMP_PROTECT_NV_STRU;

/*****************************************************************************
�ṹ��    : OM_WIFI_IPADDR_STRU
�ṹ˵��  :  ��ʱû��
��ӦNVID: 44 NV_WIFI_IPAddress

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucAddr[16];
}OM_WIFI_IPADDR_STRU;

/*****************************************************************************
�ṹ��    : CPM_CBT_PORT_ENUM_UINT32
�ṹ˵��  : CBT������˿ڳ���
��ӦNVID: 45 en_NV_Item_Om_Port_Type

  1.��    ��   : 2014��6��3��
    ��    ��   : h59254
    �޸�����   : ��ʼ����
*****************************************************************************/
enum
{
    CPM_CBT_PORT_USB,
    CPM_CBT_PORT_VCOM,
    CPM_CBT_PORT_SOCKET,
    CBP_CBT_PORT_BUTT
};
typedef VOS_UINT32 CPM_CBT_PORT_ENUM_UINT32;

/*****************************************************************************
�ṹ��    : OM_PORT_CFG_STRU
�ṹ˵��  :
��ӦNVID: 45 NV_OM_Port_Type

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    CPM_OM_PORT_ENUM_UINT32             enPortNum;         /* ����ͨ������ */
    CPM_CBT_PORT_ENUM_UINT32            enCbtPortNum;      /* У׼ͨ������ */
}OM_CHANNLE_PORT_CFG_STRU;

/*****************************************************************************
�ṹ��    : OM_PORT_CFG_STRU
�ṹ˵��  :
��ӦNVID: 46/47 NV_PsLog_Port_Type

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    OM_OUTPUT_PORT_ENUM_UINT32          enPortType;     /*�˿�����*/
    VOS_UINT32                          ulMaxFileSize;  /*�ļ���¼������С*/
}OM_PORT_CFG_STRU;

/*****************************************************************************
�ṹ��    : OM_M2_ENABLE_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 59 M2_ENABLE

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulM2Enable;
}OM_M2_ENABLE_STRU;

/*****************************************************************************
�ṹ��    : LOG_FILE_SAVE_CONFIG_STRU
�ṹ˵��  :
��ӦNVID: 117 LOG_FILE_SAVE_CONFIG

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulResult;       /* У׼��� */
    VOS_UINT32                          ulLogFileSize;  /* ����LOG�ļ���С */
}LOG_FILE_SAVE_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : USIMM_TERMINAL_CAPABILITY_STRU
�ṹ˵��  :
��ӦNVID: 130

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                                  ulIsEnable;
    VOS_UINT32                                  ulLen;
    VOS_UINT8                                   aucData[10];
    VOS_UINT16                                  usRsv;
}USIMM_TERMINAL_CAPABILITY_STRU;

/*****************************************************************************
�ṹ��    : OM_MANUFACTUREINFO_STRU
�ṹ˵��  :
��ӦNVID: 32768 ManufactureInfo

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucInfo[128];
}OM_MANUFACTUREINFO_STRU;


/*****************************************************************************
�ṹ��    : OM_MAC_ADDR_STRU
�ṹ˵��  :
��ӦNVID: 50014 NV_MACADDR

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMacAddr[32];
}OM_MAC_ADDR_STRU;


/*****************************************************************************
�ṹ��    : OM_BATTREY_TEMP_CFG_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 50016 NV_BatteryTemp_Cfg

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulIsEnable;
    VOS_INT32                           lCloseADCHold;
    VOS_UINT32                          ulTempOverMax;
}OM_BATTREY_TEMP_CFG_STRU;

/*****************************************************************************
�ṹ��    : OM_MEAN_THROUGHPUT_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 50031 MEAN_THROUGHPUT ���߶���

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucMeanThroughPut[2];
}OM_MEAN_THROUGHPUT_STRU;


/*****************************************************************************
�ṹ��    : OM_ISDB_DEFAULT_KEY_STRU
�ṹ˵��  :
��ӦNVID: 52006 ISDB_DEFAULT_KEY ���߶���

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    SC_APSEC_DEFAULT_KEY_VER_ENUM_UINT8 aenISDBKey[2];
}OM_ISDB_DEFAULT_KEY_STRU;


/*****************************************************************************
�ṹ��    : OM_SIM_ATR_FLAG_STRU
�ṹ˵��  :
��ӦNVID: 52007 SimAtrFlag  129

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                        ulSimAtrFlag;
}OM_SIM_ATR_FLAG_STRU;

/*****************************************************************************
�ṹ��    : OM_NV_CONFIG_STRU
�ṹ˵��  :
��ӦNVID: 120 NV_OAM_Config

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucOamConfig;
    VOS_UINT8                           aucRev[15];
}OM_NV_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : LDF_DUMP_DATA_INFO_STRU
�ṹ˵��  :
��ӦNVID:  LDF_DUMP_DATA_INFO_STRU

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataAddr;
    VOS_UINT32                          ulDataLen;
}LDF_DUMP_DATA_INFO_STRU;

/*****************************************************************************
�ṹ��    : ZSP_LDF_NV_CONFIG_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 122 NV_ZSP_LDF_CONFIG/NV_HIFI_LDF_CONFIG

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataNum;
    LDF_DUMP_DATA_INFO_STRU             astLDFData[SYS_ZSP_LDF_NUM];
}ZSP_LDF_NV_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : HIFI_LDF_NV_CONFIG_STRU
�ṹ˵��  : ��ʱû��
��ӦNVID: 123 NV_ZSP_LDF_CONFIG/NV_HIFI_LDF_CONFIG

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulDataNum;
    LDF_DUMP_DATA_INFO_STRU             astLDFData[SYS_HIFI_LDF_NUM];
}HIFI_LDF_NV_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : OM_PRI_THRESHOLD_STRU
�ṹ˵��  : ��û��
��ӦNVID: 127 NV_PRIORITY_THRESHOLD

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          ausNvMiddle[6];
    VOS_UINT16                          ausRev[2];
}OM_PRI_THRESHOLD_STRU;

/*****************************************************************************
�ṹ��    : USIMM_FEATURE_CFG_BIT_STRU
�ṹ˵��  : USIMMģ�鶨�����Խṹ

  1.��    ��   : 2012��6��25��
    ��    ��   : h59254
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAtt_flg               : 1;
    VOS_UINT32                          ulNFCFlg                : 1;
    VOS_UINT32                          ulAidLenCheckFlg        : 1;
    VOS_UINT32                          ulAuthCmdCheckFlg       : 1;
    VOS_UINT32                          ulCglaInsCheckFlg       : 1;
    VOS_UINT32                          ulCglaSelectCheckFlg    : 1;
    VOS_UINT32                          ulTmo_flg               : 1;
    VOS_UINT32                          ulImsiPolling           : 1;
    VOS_UINT32                          ulCglaGetRsp            : 1;
    VOS_UINT32                          ulAIDFCPSave            : 1;
    VOS_UINT32                          ulCUIMCheck             : 1;
    VOS_UINT32                          ulTimerOutInd           : 1;
    VOS_UINT32                          ulPKCS15                : 1;
    VOS_UINT32                          ulP2ActiveAID           : 1;
    VOS_UINT32                          ulWarningDataInd        : 1;

    VOS_UINT32                          bMeidPesnAPWriteEnable  : 1;  /* Meid Pesn�Ƿ���APд�룬Ĭ����modem����ʼ��д�� */
    VOS_UINT32                          ulADFActiveAll          : 1;

    /* ��CSIM APP�������Ҷ�ӦAID����,����ʼ����ICC��ʼ����������߶������Ƿ�����hisiĬ�Ϲر� */
    VOS_UINT32                          ulCsimAppAidCheck       : 1;

    /* ��ܳ�����ĳһ���ο�����CSIM��ʼ������д���ļ��󣬷���STATSU�������ͣ����60������ */
    VOS_UINT32                          ulCsimReselectFile      : 1;

    VOS_UINT32                          ulRsv                   : 13;
}USIMM_FEATURE_CFG_BIT_STRU;

/*****************************************************************************
�ṹ��    : USIMM_FEATURE_CFG_STRU
�ṹ˵��  : USIMMģ�鶨�����Կ��ƽṹ
��ӦNVID: 9090 UsimSupportFeatureCfg
˵��:       ����NV�����в�֧��λ������ṹֻ�ڴ�����ʹ��
            ����NV bin�ļ�ʱ����USIMM_FEATURE_CFG_NV_STRU
  1.��    ��   : 2012��6��25��
    ��    ��   : h59254
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    union
    {
        VOS_UINT32                      aulValue[1];
        USIMM_FEATURE_CFG_BIT_STRU      stFeatureCfg;
    }unCfg;
}USIMM_FEATURE_CFG_STRU;

/*****************************************************************************
�ṹ��    : USIMM_FEATURE_CFG_NV_STRU
�ṹ˵��  : USIMMģ�鶨�����Կ��ƽṹ
��ӦNVID: 9090 UsimSupportFeatureCfg
˵��:     ����޸�������ṹ����ͬʱ�޸�USIMM_FEATURE_CFG_STRU��
          ����NVת��ʱ��֧��λ������������������ṹ
  1.��    ��   : 2012��6��25��
    ��    ��   : h59254
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCfg;
}USIMM_FEATURE_CFG_NV_STRU;

/*****************************************************************************
�ṹ��    : STK_FEATURE_CFG_BIT_STRU
�ṹ˵��  : STKģ�鶨�����Խṹ

  1.��    ��   : 2012��6��25��
    ��    ��   : h59254
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulLociEventCmp          : 1;

    VOS_UINT32                          ulRsv                   :31;
}STK_FEATURE_CFG_BIT_STRU;

/*****************************************************************************
�ṹ��    : STK_FEATURE_CFG_STRU
�ṹ˵��  : USIMMģ�鶨�����Կ��ƽṹ
��ӦNVID: 4005 STKSupportFeatureCfg
˵��:       ����NV�����в�֧��λ������ṹֻ�ڴ�����ʹ��
            ����NV bin�ļ�ʱ����USIMM_FEATURE_CFG_NV_STRU
  1.��    ��   : 2012��6��25��
    ��    ��   : h59254
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    union
    {
        VOS_UINT32                    aulValue[1];
        STK_FEATURE_CFG_BIT_STRU      stFeatureCfg;
    }unCfg;
}STK_FEATURE_CFG_STRU;

/*****************************************************************************
�ṹ��    : STK_FEATURE_CFG_NV_STRU
�ṹ˵��  : STKģ�鶨�����Կ��ƽṹ
��ӦNVID: 4005 STKSupportFeatureCfg
˵��:     ����޸�������ṹ����ͬʱ�޸�USIMM_FEATURE_CFG_STRU��
          ����NVת��ʱ��֧��λ������������������ṹ
  1.��    ��   : 2012��6��25��
    ��    ��   : h59254
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCfg;
}STK_FEATURE_CFG_NV_STRU;

/*****************************************************************************
�ṹ��    : OM_USIM_NEED_FCP_STRU
�ṹ˵��  :
��ӦNVID: 9108 USIM_Status_Need_Fcp

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulUsimNeedFcp;
}OM_USIM_NEED_FCP_STRU;


/*****************************************************************************
�ṹ��    : OM_USIM_OP_FILE_CFG_STRU
�ṹ˵��  :
��ӦNVID: 9126/9127 UsimOpfileCfg/simOpfileCfg

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usOptionFileNum;
    VOS_UINT16                          ausOptionFileList[16];
    VOS_UINT16                          usReserved;
}OM_USIM_OP_FILE_CFG_STRU;

/*****************************************************************************
 �ṹ��    : USIMM_TEST_CARD_PLMN_ST
 �ṹ˵��  : USIMMģ����Կ�PLMN��Ϣ

  1.��    ��   : 2013��01��04��
    ��    ��   : h59254
    �޸�����   : ���ⵥ�޸������ӽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmn[USIMM_TEST_CARD_PLMN_LEN];
    VOS_UINT8                           ucRsv;
}USIMM_TEST_CARD_PLMN_ST;

/*****************************************************************************
 �ṹ��    : USIMM_TEST_CARD_PLMN_ST
 �ṹ˵��  : USIMMģ����Կ�PLMN��Ϣ

  1.��    ��   : 2013��01��04��
    ��    ��   : h59254
    �޸�����   : ���ⵥ�޸������ӽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmn[USIMM_CDMATEST_CARD_PLMN_LEN];
    VOS_UINT8                           ucRsv1;
    VOS_UINT8                           ucRsv2;
}USIMM_CDMATEST_CARD_PLMN_ST;

/*****************************************************************************
 �ṹ��    : USIMM_TEST_CARD_CFG_ST
 �ṹ˵��  : USIMMģ����Կ����ýṹ
��ӦNVID: 9129 TestCardCfg
  1.��    ��   : 2013��01��04��
    ��    ��   : h59254
    �޸�����   : ���ⵥ�޸������ӽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    USIMM_TEST_CARD_PLMN_ST             astPlmnList[USIMM_TEST_CARD_CFG_NUM];
}USIMM_TEST_CARD_CFG_ST;

/*****************************************************************************
 �ṹ��    : USIMM_CDMATEST_CARD_CFG_ST
 �ṹ˵��  : USIMMģ����Կ����ýṹ
 ��ӦNVID  : 4004 CdmaTestCardCfg
  1.��    ��   : 2013��01��04��
    ��    ��   : h59254
    �޸�����   : ���ⵥ�޸������ӽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulPlmnNum;
    USIMM_CDMATEST_CARD_PLMN_ST         astPlmnList[USIMM_TEST_CARD_CFG_NUM];
}USIMM_CDMATEST_CARD_CFG_ST;

/*****************************************************************************
�ṹ��    : OM_BBP_DUMP_ENABLE_STRU
�ṹ˵��  :
��ӦNVID: 9205 NV_BBP_DUMP_ENABLE

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                        ulEnable;
}OM_BBP_DUMP_ENABLE_STRU;


/*****************************************************************************
�ṹ��    : OM_FILE_EF6F62_STRU
�ṹ˵��  :
��ӦNVID: 6657 FILE_EF6F62

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[250];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F62_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F7B_STRU
�ṹ˵��  :
��ӦNVID: 6658 FILE_EF6F7B

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[12];
}OM_FILE_EF6F7B_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F60_STRU
�ṹ˵��  :
��ӦNVID: 6659 FILE_EF6F60

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[170];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F60_STRU;
/*****************************************************************************
�ṹ��    : OM_FILE_EF6F61_STRU
�ṹ˵��  :
��ӦNVID: 6660 FILE_EF6F61

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[250];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F61_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F31_STRU
�ṹ˵��  :
��ӦNVID: 6661 FILE_EF6F31

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[2];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F31_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6FAD_STRU
�ṹ˵��  :
��ӦNVID: 6662 FILE_EF6FAD

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[4];
}OM_FILE_EF6FAD_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F38_STRU
�ṹ˵��  :
��ӦNVID: 6663 FILE_EF6F38

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[8];
}OM_FILE_EF6F38_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F7E_STRU
�ṹ˵��  :
��ӦNVID: 6664 FILE_EF6F7E

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[12];
}OM_FILE_EF6F7E_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F73_STRU
�ṹ˵��  :
��ӦNVID:  6665 FILE_EF6F73

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[14];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F73_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F53_STRU
�ṹ˵��  :
��ӦNVID:  6666 FILE_EF6F53

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[12];
}OM_FILE_EF6F53_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F07_STRU
�ṹ˵��  :
��ӦNVID:  6667 FILE_EF6F07

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[10];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F07_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F08_STRU
�ṹ˵��  :
��ӦNVID:  6668 FILE_EF6F08

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[34];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F08_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F09_STRU
�ṹ˵��  :
��ӦNVID:  6669 FILE_EF6F09

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[34];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F09_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F20_STRU
�ṹ˵��  :
��ӦNVID:  6670 FILE_EF6F20

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[2];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F20_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F52_STRU
�ṹ˵��  :
��ӦNVID:  6671 FILE_EF6F52

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[8];
}OM_FILE_EF6F52_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF4F20_STRU
�ṹ˵��  :
��ӦNVID:  6672 FILE_EF4F20

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[10];
    VOS_UINT16                          usReserved;
}OM_FILE_EF4F20_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF4F52_STRU
�ṹ˵��  :
��ӦNVID:  6673 FILE_EF4F52

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[10];
    VOS_UINT16                          usReserved;
}OM_FILE_EF4F52_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6FB7_STRU
�ṹ˵��  :
��ӦNVID:  6674 FILE_EF6FB7

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[14];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6FB7_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F78_STRU
�ṹ˵��  :
��ӦNVID:  6675 FILE_EF6F78

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[2];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F78_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F5B_STRU
�ṹ˵��  :
��ӦNVID:  6676 FILE_EF6F5B

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[6];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F5B_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F5C_STRU
�ṹ˵��  :
��ӦNVID:  6677 FILE_EF6F5C

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[4];
}OM_FILE_EF6F5C_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6FC4_STRU
�ṹ˵��  :
��ӦNVID:  6678 FILE_EF6FC4

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[50];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6FC4_STRU;

/*****************************************************************************
�ṹ��    : OM_FILE_EF6F74_STRU
�ṹ˵��  :
��ӦNVID:  6679 FILE_EF6F74

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucContent[50];
    VOS_UINT16                          usReserved;
}OM_FILE_EF6F74_STRU;

/*****************************************************************************
�ṹ��    : SI_PB_CTRL_INFO_ST
�ṹ˵��  :
��ӦNVID: 8244 UsimPBCtrlInfo

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef VOS_UINT32 SI_PB_STORATE_TYPE;
typedef struct
{
    SI_PB_STORATE_TYPE                  enCurMaterial;
    VOS_UINT8                           aucPasswords[8];
    VOS_UINT16                          usUsed;
    VOS_UINT16                          usTotal;
    VOS_UINT8                           ucAnrMaxNum;        /*Balong֧�ֵ�ANR�����ֵ*/
    VOS_UINT8                           ucEmailFlag;        /*Balong֧��Email���*/
    VOS_UINT8                           ucSPBFlag;         /*���ϵ绰��֧�ֱ�ǣ�Ϊ1ʱ��ʾ֧��*/
    VOS_UINT8                           ucRsv;
}SI_PB_CTRL_INFO_ST;

/*****************************************************************************
�ṹ��    : USIMM_CMD_DEBUG_MODE_ST
�ṹ˵��  :
��ӦNVID: 8257 UsimDebugMode

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usFlag;
    VOS_UINT16                          usTimerValue;
}USIMM_CMD_DEBUG_MODE_ST;

/*****************************************************************************
�ṹ��    : USIMM_STK_CFG_STRU
�ṹ˵��  :
��ӦNVID: 8261 TerminalProfile_Set

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucProfileLen;
    VOS_UINT8                           aucProfile[47];
}USIMM_USIM_PROFILE_STRU;


typedef struct
{
    VOS_UINT8                           ucProfileLen;
    VOS_UINT8                           aucProfile[31];
}USIMM_SIM_PROFILE_STRU;

typedef struct
{
    VOS_UINT8                           ucFuncEnable;
    VOS_UINT8                           ucTimer;
    VOS_UINT8                           ucTerminalType;
    VOS_UINT8                           ucRsv;
    USIMM_USIM_PROFILE_STRU             stUsimProfile;
    USIMM_SIM_PROFILE_STRU              stSimProfile;
}USIMM_STK_CFG_STRU;

/*****************************************************************************
�ṹ��    : USIMM_USIMSUPIMS_STRU
�ṹ˵��  : USIM��֧��IMS

  1.��    ��   : 2013��9��6��
    ��    ��   : j00168360
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                           ulUsimSupImsEnable;
}USIMM_USIMSUPIMS_STRU;

/*****************************************************************************
�ṹ��    : SI_STK_MATCH_STRING_STRU
�ṹ˵��  :
��ӦNVID:

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usStrLen;
    VOS_UINT8                           aucMatchStr[22];
}SI_STK_MATCH_STRING_STRU;

/*****************************************************************************
�ṹ��    : USIMM_STK_CFG_STRU
�ṹ˵��  : �ִ��Dual IMSI �л������������NV�ṹ
��ӦNVID: 8318 StkDualIMSICtrl

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usDualIMSIEnable;      /* ��һ��ѡ���ITEM ID */
    VOS_UINT16                          usMatchStrCnt;
    SI_STK_MATCH_STRING_STRU            astMatchStr[3];
}SI_STK_IMSICHG_MATCH_STRU;

/*****************************************************************************
�ṹ��    : SI_STK_SMSIN_CTRL_STRU
�ṹ˵��  :
��ӦNVID: 8330 STK_SMSIND_CTRL

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulStkSmsindCtrl;
}SI_STK_SMSIN_CTRL_STRU;

/*****************************************************************************
�ṹ��    : OM_VIVO_STK_CODEC_STRU
�ṹ˵��  :
��ӦNVID: 8505 en_NV_Brazil_VIVO_STK_Codec_Correct

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulVivo;
}OM_VIVO_STK_CODEC_STRU;

/*****************************************************************************
�ṹ��    : NV_HUAWEI_DOUBLE_IMSI_CFG_I_STRU
�ṹ˵��  :
��ӦNVID: 50041 NV_HUAWEI_DOUBLE_IMSI_CFG_I

  1.��    ��   : 2013��5��16��
    ��    ��   : j00174725
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCfg;
    VOS_UINT8                           ucEnable;
}NV_HUAWEI_DOUBLE_IMSI_CFG_I_STRU;

/*****************************************************************************
�ṹ��    : NV_ID_WRITE_SLICE_RECORD_FLAG_STRU
�ṹ˵��  :
��ӦNVID: 52007 NV_ID_WRITE_SLICE_RECORD_FLAG

  1.��    ��   : 2013��7��11��
    ��    ��   : d00212987
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulRecordFlag;
}NV_ID_WRITE_SLICE_RECORD_FLAG_STRU;

/*****************************************************************************
�ṹ��    : NV_SOCP_SDLOG_CFG_STRU
�ṹ˵��  :
��ӦNVID:   NV_ID_SOCP_SDLOG_CFG

  1.��    ��   : 2013��7��11��
    ��    ��   : z00212940
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32 ulSocpDelayWriteFlg;/* SOCP�ӳ�д�빦��������� */
    VOS_UINT32 ulIndSocpLevel;     /* INDͨ��Ŀ��BUFFER����ˮ�� */
    VOS_UINT32 ulCfgSocpLevel;     /* CFGͨ��Ŀ��BUFFER����ˮ�� */
    VOS_UINT32 ulTimeOutValue;     /* SOCPĿ��BUFFER�ĳ�ʱʱ�� */
}NV_SOCP_SDLOG_CFG_STRU;

/*****************************************************************************
�ṹ��    : NV_ID_ERR_LOG_CTRL_INFO_STRU
�ṹ˵��  :
��ӦNVID: 133 NV_ID_ERR_LOG_CTRL_INFO

  1.��    ��   : 2013��8��27��
    ��    ��   : d00212987
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAlmStatus; /* �澯״̬,Ĭ��0:close;1:open  */
    VOS_UINT8                           ucAlmLevel;  /* ����&�澯����
                                                                Warning��0x04������ʾ��
                                                                Minor��0x03�����Ҫ
                                                                Major��0x02������Ҫ
                                                                Critical��0x01���������Ĭ�ϣ�
                                                              ˵����ֵΪ0x03�� 0x03/0x02/0x01���ϱ� */
    VOS_UINT8                          aucReportBitMap[2]; /* A0000000 00000DCB
                                                              A���������ϱ�����
                                                              B���������������Կ���
                                                              C�����������Թ��������ϱ�����
                                                              D����RATƵ���л������ϱ�����
                                                           */
}NV_ID_ERR_LOG_CTRL_INFO_STRU;

/*****************************************************************************
�ṹ��    : OM_ALARM_ID_DETAIL_STRU
�ṹ˵��  :
  1.��    ��   : 2013��8��27��
    ��    ��   : d00212987
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulAlarmid;        /* �澯��ʶ */
    VOS_UINT32                          ulAlarmidDetail;  /* �澯����ԣ�32bit��ÿ��bit����һ������ԣ�0����͸�������޹� */
}OM_ALARM_ID_DETAIL_STRU;

/*****************************************************************************
�ṹ��    : NV_ALARM_ID_RELATIONSHIP_STRU
�ṹ˵��  :
��ӦNVID: 134 NV_ALARM_ID_RELATIONSHIP

  1.��    ��   : 2013��8��27��
    ��    ��   : d00212987
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    OM_ALARM_ID_DETAIL_STRU          astOmAlarmidRelationship[40]; /* Ԥ��40�� */
}NV_ALARM_ID_RELATIONSHIP_STRU;

/*****************************************************************************
�ṹ��    : NV_ID_FTM_DETAIL_STRU
�ṹ˵��  :
��ӦNVID: 135 NV_ID_FTM_DETAIL

  1.��    ��   : 2013��8��27��
    ��    ��   : d00212987
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFTMDetail; /* ����ģʽ����ԣ�32bit��ÿ��bit����һ������ԣ�0����͸�������޹� */
}NV_ID_FTM_DETAIL_STRU;

/*****************************************************************************
 �ṹ��    : VSIM_KEYDATA_STRU
 Э����  : ��
 �ṹ˵��  : ��Կ���ݽṹ���������ȡ�����

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhuli
    �޸�����   : V9R1 vSIM��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulKeyLen;
    VOS_UINT8                           aucKey[VSIM_KEYLEN_MAX];
}VSIM_KEYDATA_STRU;

/*****************************************************************************
 �ṹ��    : VSIM_CARD_STATE_NV_STRU
 Э����  : ��
 �ṹ˵��  : ��״̬���ݽṹ

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhuli
    �޸�����   : V9R1 vSIM��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VSIM_ACTIVE_TYPE_ENUM_UINT8         enVsimState;
    VOS_UINT8                           aucRfu[3];
}VSIM_CARD_STATE_NV_STRU;

/*****************************************************************************
 �ṹ��    : VSIM_CARD_LOCI_FILE_NV_STRU
 Э����  : ��
 �ṹ˵��  : ��¼EF_LOCI�ļ�

 �޸���ʷ      :
  1.��    ��   : 2013��9��16��
    ��    ��   : H59524
    �޸�����   : V9R1 vSIM��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucEfloci[VSIM_EF_LOCI_LEN];
    VOS_UINT8                           ucRsv;
}VSIM_CARD_LOCI_FILE_NV_STRU;

/*****************************************************************************
 �ṹ��    : VSIM_CARD_PSLOCI_FILE_NV_STRU
 Э����  : ��
 �ṹ˵��  : ��¼PS_EF_LOCI�ļ�

 �޸���ʷ      :
  1.��    ��   : 2013��9��16��
    ��    ��   : H59524
    �޸�����   : V9R1 vSIM��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPsEfloci[VSIM_EF_PS_LOCI_LEN];
    VOS_UINT16                          usReserved;
}VSIM_CARD_PSLOCI_FILE_NV_STRU;

/*****************************************************************************
 �ṹ��    : VSIM_CARD_FPLMN_FILE_NV_STRU
 Э����  : ��
 �ṹ˵��  : ��¼EF_FPLMN�ļ�

 �޸���ʷ      :
  1.��    ��   : 2013��9��16��
    ��    ��   : H59524
    �޸�����   : V9R1 vSIM��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucFplmn[VSIM_EF_FPLMN_LEN];
}VSIM_CARD_FPLMN_FILE_NV_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_VSIM_HVSDH_NV_STRU
 Э����  : ��
 �ṹ˵��  : �洢��˽��Կ��NV���ݽṹ

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhuli
    �޸�����   : V9R1 vSIM��Ŀ�޸�
*****************************************************************************/
typedef struct
{
    VSIM_ALGORITHM_TYPE_ENUM_UINT32     enAlgorithm;
    VOS_UINT32                          ulDHLen;         /* DH�㷨�������ӵĳ��� */
    VSIM_KEYDATA_STRU                   stCPrivateKey;   /* �����˽Կ */
    VSIM_KEYDATA_STRU                   stCPublicKey;    /* ����⹫Կ */
    VSIM_KEYDATA_STRU                   stSPublicKey;    /* ��������Կ */
}NVIM_VSIM_HVSDH_NV_STRU;

/*****************************************************************************
�ṹ��    : NV_MODE_BASIC_PARA_STRU
�ṹ˵��  :
��ӦNVID:

  1.��    ��   : 2013��9��27��
    ��    ��   : g47350
    �޸�����   : ��ʼ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucABBSwitch;    /*��Ӧģʽʹ�õ�ABB����ͨ����0ΪABB CH0��1ΪABB CH1��2Ϊ��ǰģʽʹ��������ͨ��*/
    VOS_UINT8                           ucRFSwitch;     /*��Ӧģʽʹ�õ�RF����ͨ����0ΪRFʹ��mipi0����PA-Star�ϵ磻1ΪRFʹ��mipi1����PA-Star�ϵ磬����ʹ��Smart-Star��BUCK6���ϵ磬2Ϊ��ǰģʽʹ������RFIC*/
    VOS_UINT8                           ucTCXOSwitch;   /*��Ӧģʽʹ�õ�TCXO��0ΪTCXO0��1ΪTCXO */
    VOS_UINT8                           ucRsv1;
}NV_MODE_BASIC_PARA_STRU;

/*****************************************************************************
�ṹ��    : NV_GUMODE_CHAN_PARA_STRU
�ṹ˵��  :138 en_NV_Item_GUMODE_CHAN_PARA
��ӦNVID:

  1.��    ��   : 2013��9��27��
    ��    ��   : g47350
    �޸�����   : ��ʼ����
*****************************************************************************/

typedef struct
{
    NV_MODE_BASIC_PARA_STRU             astModeBasicParam[2];    /*��ͬ��ʽ��ͨ������*/
}NV_GUMODE_CHAN_PARA_STRU;


/*****************************************************************************
 �ṹ��    : NV_RECORD_BASE_BOARD_XML_STRU
 Э����  : ��
 �ṹ˵��  : 139 ��¼��Ʒϵ�еĹ���XML�ļ�ID

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : d00212987
    �޸�����   :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucXMLBaseBoardId[24]; /* ��¼base board xml ���� */
}NV_RECORD_BASE_BOARD_XML_STRU;


/*****************************************************************************
 �ṹ��    : NV_RECORD_CURRENT_BOARD_XML_STRU
 Э����  : ��
 �ṹ˵��  : 140 ��¼��Ʒϵ�еĵ�ǰXML�ļ�ID

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : d00212987
    �޸�����   :
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucXMLCurrentBoardId[24]; /* ��¼Currnet board xml ���� */
}NV_RECORD_CURRENT_BOARD_XML_STRU;

/*****************************************************************************
 �ṹ��    : NV_FLASH_LOG_RECORD_STRU
 Э����  : ��
 �ṹ˵��  : 143 ��¼FLASH����TRACE�ռ�����

 �޸���ʷ      :
  1.��    ��   : 2013��12��27��
    ��    ��   : s00207770
    �޸�����   :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulGULogFileSize;
    VOS_UINT32                          ulTLLogFileSize;
}NV_FLASH_LOG_RECORD_STRU;

/*****************************************************************************
 �ṹ��    : NVIM_USIM_CARD_STATUS_CB_TYPE_STRU
 �ṹ˵��  : SIM��ע��ص�����������NV�����ݽṹ

  1.��    ��   : 2013��09��25��
    ��    ��   : h59254
    �޸�����   : V3R3 SIM���Ȳ岦��Ŀ����
*****************************************************************************/
typedef struct
{
    USIMM_CARD_STATUS_REG_TYPE_ENUM_UINT16                  enType;
    VOS_UINT16                                              usReserved;
}NVIM_USIM_CARD_STATUS_CB_TYPE_STRU;

/*****************************************************************************
 �ṹ��    : NV_EVENT_RESEND_CFG_STRU
 Э����  : ��
 �ṹ˵��  : 145 C+Lģʽ������ʽ�Ŀ���NV

 �޸���ʷ      :
  1.��    ��   : 2014��1��15��
    ��    ��   : z00100318
    �޸�����   :
*****************************************************************************/
typedef struct
{
    EVENT_RESEND_FLAG_ENUM_UINT8            enResendFlag;   /*1������0�ر�*/
    VOS_UINT8                               ucRetryTime;    /*���Դ������������Ϊ0Ϊ���ط�*/
    VOS_UINT8                               ucTimerLen;     /*���ʱ�䣬��λΪ��, �������Ϊ0Ϊ���ط�*/
    VOS_UINT8                               ucRsv;
}NV_EVENT_RESEND_CFG_STRU;

/*****************************************************************************
 ö����    : USIMM_DL_T_MODE_ENUM
 �ṹ˵��  : ��֧��Tģʽö��

  1.��    ��   : 2013��10��21��
    ��    ��   : L00256032
    �޸�����   : V9R1 T=1��Ŀ����
*****************************************************************************/
enum USIMM_DL_T_MODE_ENUM
{
    USIMM_DL_T_MODE_T0        = 0,    /* ֧��T=0ģʽ */
    USIMM_DL_T_MODE_T1        = 1,    /* ֧��T=1ģʽ */
    USIMM_DL_T_MODE_BUTT
};
typedef VOS_UINT32      USIMM_DL_T_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_T1_ERR_DETECT_MODE_ENUM
 ö��˵��  : T=1��EDCģʽ
             ��ts_102221v110000p���й涨EDCΪ1�ֽڣ���ֻ֧��LRC��Ϊ�����Կ��ǣ�
              ����һ��NV��������ھ�����ѭts_102221�淶��ISO_IEC 7816-3�淶

  1.��    ��   : 2013��10��21��
    ��    ��   : L00256032
    �޸�����   : V9R1 T=1��Ŀ����
*****************************************************************************/
enum USIMM_T1_ERR_DETECT_MODE_ENUM
{
    USIMM_T1_ERR_DETECT_MODE_ISO_IEC_7816_3  = 0,           /* NVĬ��ֵ����ѭISO_IEC 7816-3 2006�淶��EDC����ATR�е�ָʾ��ȷ��(LRC��CRC) */
    USIMM_T1_ERR_DETECT_MODE_TS102221        = 1,           /* ��ѭTS_102221v110000p�淶��EDCֻʹ��LRC */

    USIMM_T1_ERR_DETECT_MODE_BUTT
};
typedef VOS_UINT32 USIMM_T1_ERR_DETECT_MODE_ENUM_UINT32;

/*****************************************************************************
 ö����    : USIMM_DL_T_MODE_ENUM
 �ṹ˵��  : ��֧��Tģʽö��

  1.��    ��   : 2013��10��21��
    ��    ��   : L00256032
    �޸�����   : V9R1 T=1��Ŀ����
*****************************************************************************/
enum USIMM_DL_T1_GCF_FLAG_ENUM
{
    USIMM_DL_T1_GCF_DISABLE       = 0,    /* ��ǰ����GCF���� */
    USIMM_DL_T1_GCF_ENABLE        = 1,    /* ��ǰGCF����ʹ�� */
    USIMM_DL_T1_GCF_BUTT
};
typedef VOS_UINT32      USIMM_DL_T1_GCF_FLAG_ENUM_UINT32;


/*****************************************************************************
�ṹ��    : NV_USIMM_T1_CTRL_STRU
�ṹ˵��  : en_NV_Item_Usimm_T1_Ctrl_PARA
��ӦNVID:

  1.��    ��   : 2013��10��21��
    ��    ��   : L00256032
    �޸�����   : V9R1 T=1��Ŀ����
*****************************************************************************/
typedef struct
{
    USIMM_DL_T_MODE_ENUM_UINT32                             enTMode;
    USIMM_T1_ERR_DETECT_MODE_ENUM_UINT32                    enEDM;
    USIMM_DL_T1_GCF_FLAG_ENUM_UINT32                        enGcfFlag;
    VOS_UINT32                                              ulDefaultIFSD;
    VOS_UINT32                                              aulRsv[2];
}NV_USIMM_T1_CTRL_PARA_STRU;

/*****************************************************************************
 �ṹ��    : NV_OM_CBT_LOG_ENABLE_STRU
 �ṹ˵��  : CBT LOG�Ƿ�������NV�����ݽṹ 146

  1.��    ��   : 2014��01��23��
    ��    ��   : d00212987
    �޸�����   : V9R1 CBT LOG��Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_BOOL                           bCBTLogEnable;
}NV_OM_CBT_LOG_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : NV_SLEEP_DRX_RESET_ENABLE_STRU
 �ṹ˵��  : SLEEP���������쳣�Ƿ�λNV�����ݽṹ 149

  1.��    ��   : 2014��03��13��
    ��    ��   : s00207770
    �޸�����   : V9R1��ά�ɲ�����
*****************************************************************************/
typedef struct
{
    VOS_BOOL                          bResetEnable;
}NV_SLEEP_DRX_RESET_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : NV_ESN_MEID_STRU
 �ṹ˵��  : NV_ESN_MEID_STRU 9283

  1.��    ��   : 2014��07��3��
    ��    ��   : zhuli
    �޸�����   : X��Ŀ����
*****************************************************************************/
typedef struct
{
    ESN_MEID_FLAG_ENUM_UINT8        enEsnMeIDFlag;
    VOS_UINT8                       ucRSv;
    VOS_UINT8                       aucEsn[ESN_NV_DATA_LEN];  /*Len+Data*/
    VOS_UINT8                       aucMeID[MEID_NV_DATA_LEN]; /*Len+Data*/
    VOS_UINT8                       aucRfu[6];
}NV_ESN_MEID_STRU;

/*****************************************************************************
 �ṹ��    : NV_DDR_ADJUST_ENABLE_STRU
 �ṹ˵��  : DDR��Ƶ����ʹ�ܱ�־λ

  1.��    ��   : 2014��11��13��
    ��    ��   : s00207770
    �޸�����   : V8R2��������
*****************************************************************************/
typedef struct
{
    VOS_BOOL                            bEnable;       /*ʹ�ܱ�־λ*/
    VOS_UINT32                          ulRsv;
}NV_DDR_ADJUST_ENABLE_STRU;

/*****************************************************************************
 �ṹ��    : NV_PESN_STRU
 �ṹ˵��  : NV_PESN_STRU 4002

  1.��    ��   : 2015��07��17��
    ��    ��   : z00316370
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       aucPEsn[PESN_NV_DATA_LEN];      /*Data*/
}NV_PESN_STRU;

/*****************************************************************************
 �ṹ��    : NV_MEID_STRU
 �ṹ˵��  : NV_MEID_STRU 4003

  1.��    ��   : 2015��07��17��
    ��    ��   : z00316370
    �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                       aucMeID[MEID_NV_DATA_LEN_NEW];  /*Data*/
    VOS_UINT8                       aucRsv[1];
}NV_MEID_STRU;

/*****************************************************************************
 ö����    : USIMM_NV_CARDAPP_ENUM
 ö��˵��  : USIMM������ö��

  1.��    ��   : 2015��03��23��
    ��    ��   : ganlan
    �޸�����   : V8R2 UICC MutliApp PhaseI��������
*****************************************************************************/
enum USIMM_NV_CARDAPP_ENUM
{
    USIMM_NV_GUTL_APP          = 0x00000000,
    USIMM_NV_IMS_APP           = 0x00000001,
    USIMM_NV_CDMA_APP          = 0x00000002,
    USIMM_NV_CARDAPP_BUTT      = 0x00000003
};
typedef VOS_UINT32 USIMM_NV_CARDAPP_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : USIMM_APP_PRIORITY_CONFIG_STRU
 �ṹ˵��  : USIMMӦ�ó�ʼ��˳������

  1.��    ��   : 2015��03��23��
    ��    ��   : ganlan
    �޸�����   : V8R2 UICC MutliApp PhaseI��������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucAppNum;
    VOS_UINT8                           aucRsv[3];
    USIMM_NV_CARDAPP_ENUM_UINT32        aenAppList[5];
}USIMM_APP_PRIORITY_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : NV_SLEEP_BBE16_CTRL_STRU
 �ṹ˵��  : BBE16���µ翪��

  1.��    ��   : 2015��10��29��
    ��    ��   : xushutao
    �޸�����   : Xģ�͹�����Ŀ����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSleepBBE16Switch;
}NV_SLEEP_BBE16_CTRL_STRU;

/*****************************************************************************
 ö����    : SC_PERS_PLATFORM_ENUM_UINT32
 ö��˵��  : SC Modem����ʽö��

  1.��    ��   : 2016��01��06��
    ��    ��   : d00212987
    �޸�����   : SC���Ӷ�CDMA��ʽ֧������
*****************************************************************************/
enum SC_PERS_PLATFORM_ENUM
{
    SC_PERS_PLATFORM_G,   /* �ǵ���ģʽ�������� */

    SC_PERS_PLATFORM_C,   /* ����ģʽ�������� */

    SC_PERS_PLATFORM_BUT,
};
typedef VOS_UINT32 SC_PERS_PLATFORM_ENUM_UINT32;

/*****************************************************************************
 �ṹ��    : SC_PERS_SUPPORT_PLATFORM_STRU
 �ṹ˵��  : SC Modem����֧�ֵ���ʽ

 1.��    ��   : 2016��01��06��
   ��    ��   : d00212987
   �޸�����   : SC���Ӷ�CDMA��ʽ֧������
*****************************************************************************/
typedef struct
{
    SC_PERS_PLATFORM_ENUM_UINT32        enScPersModem;
}SC_PERS_SUPPORT_PLATFORM_STRU;

/*****************************************************************************
 �ṹ��    : NV_SC_PERS_CTRL_STRU
 �ṹ˵��  : SC �����������ƿ������

  1.��    ��   : 2015��11��30��
    ��    ��   : d00212987
    �޸�����   : SC���Կ�������
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usImei0ReplaseImei2;
    VOS_UINT16                          usRsv;
}NV_SC_PERS_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : NV_XPDS_FEATURE_CONTROL_STRU
 �ṹ˵��  : xpds��������

 1.��    ��   : 2016��01��26��
   ��    ��   : d00212987
   �޸�����   : ����xpdsģ�����ò���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucSiWaitGpsPseudoCnfTimeLen;   /* NI���̵ȴ�GPSα����Ϣ�ظ�ʱ��:��λ�� */
    VOS_UINT8                   ucNiWaitGpsPseudoCnfTimeLen;   /* ��NI���̵ȴ�GPSα����Ϣ�ظ�ʱ��:��λ�� */
    VOS_UINT8                   ucWaitCasRefLocIndTimeLen;     /* �ȴ�CAS REF LOC IND��Ϣ��ʱʱ��:��λ�� */
    VOS_UINT8                   ucMsaMaxPilotCnt;              /* MSA�������Pilot��Ŀ */

    VOS_UINT8                   ucRsv[8];
}NV_XPDS_FEATURE_CONTROL_STRU;

/*****************************************************************************
 �ṹ��    : NV_ISIM_ENABLE_STRU
 �ṹ˵��  : ISIM�Ƿ�ʹ��NV

  1.��    ��   : 2016��03��11��
    ��    ��   : z00316370
    �޸�����   : PAM_USIM_IT5_ISIM ��������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucIsimEnableFlag;
    VOS_UINT8                           aucRsv[3];
}NV_ISIM_ENABLE_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of NasNvInterface.h */
