/******************************************************************************

  Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : TtfNvInterface.h
  Description     : TtfNvInterface.h header file
  History         :

******************************************************************************/

#ifndef __TTFNVINTERFACE_H__
#define __TTFNVINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"

/*****************************************************************************
  2 Macro
*****************************************************************************/

#define TTF_MEM_MAX_POOL_NUM                (5)
#define TTF_MEM_MAX_CLUSTER_NUM             (8)

#define FC_UL_RATE_MAX_LEV                  (11)
#define TTF_MEM_POOL_NV_NUM                 (TTF_MEM_MAX_POOL_NUM + 1)
#define FC_ACPU_DRV_ASSEM_NV_LEV            (4)

#define BASTET_HPRTODCH_SUPPORT             (0x01)
#define BASTET_CHNL_LPM_SUPPORT             (0x02)

#define NV_PLATFORM_MAX_RAT_NUM             (7)               /* ���뼼�����ֵ */

#define NV_PLATFORM_MAX_MODEM_NUM           (8)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/

enum FC_MEM_THRESHOLD_LEV_ENUM
{
    FC_MEM_THRESHOLD_LEV_1              = 0,
    FC_MEM_THRESHOLD_LEV_2,
    FC_MEM_THRESHOLD_LEV_3,
    FC_MEM_THRESHOLD_LEV_4,
    FC_MEM_THRESHOLD_LEV_5,
    FC_MEM_THRESHOLD_LEV_6,
    FC_MEM_THRESHOLD_LEV_7,
    FC_MEM_THRESHOLD_LEV_8,
    FC_MEM_THRESHOLD_LEV_BUTT           = 8
};
typedef VOS_UINT32  FC_MEM_THRESHOLD_LEV_ENUM_UINT32;

enum FC_ACPU_DRV_ASSEM_LEV_ENUM
{
    FC_ACPU_DRV_ASSEM_LEV_1             = 0,
    FC_ACPU_DRV_ASSEM_LEV_2,
    FC_ACPU_DRV_ASSEM_LEV_3,
    FC_ACPU_DRV_ASSEM_LEV_4,
    FC_ACPU_DRV_ASSEM_LEV_5             = 4,
    FC_ACPU_DRV_ASSEM_LEV_BUTT          = 5
};
typedef VOS_UINT32  FC_ACPU_DRV_ASSEM_LEV_ENUM_UINT32;

enum RATIO_RESET_TYPE_ENUM
{
    TTF_NODE_RESET_TYPE                 = 0,
    PS_QNODE_RESET_TYPE                 = 1,
    RATIO_RESET_TYPE_BUTT               = 2
};
typedef VOS_UINT32  RATIO_RESET_TYPE_ENUM_UINT32;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
/*****************************************************************************
*                                                                            *
*                           ����������Ϣ�ṹ                                 *
*                                                                            *
******************************************************************************/

/*****************************************************************************
 �ṹ��    : TTF_MEM_POOL_CFG_NV_STRU
 �ṹ˵��  : TTF_MEM_POOL_CFG_NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                      ucClusterCnt;
    VOS_UINT8                      aucReserved[1];
    VOS_UINT16                     ausBlkSize[TTF_MEM_MAX_CLUSTER_NUM];         /* �������Ĵ�С */
    VOS_UINT16                     ausBlkCnt[TTF_MEM_MAX_CLUSTER_NUM];          /* �������� */
}TTF_MEM_POOL_CFG_NV_STRU;

/*****************************************************************************
 �ṹ��    : TTF_MEM_SOLUTION_CFG_NV_STRU
 �ṹ˵��  : TTF_MEM_SOLUTION_CFG��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucPoolCnt;
    VOS_UINT8                           ucPoolMask;                             /* ��Ӧ�ڴ���Ƿ���Ч����λ��bit����ʾ��1- ��Ч�� 0- ����Ч*/
    TTF_MEM_POOL_CFG_NV_STRU            astTtfMemPoolCfgInfo[TTF_MEM_POOL_NV_NUM];
    VOS_UINT8                           aucReserve[2];
}TTF_MEM_SOLUTION_CFG_NV_STRU;

/*****************************************************************************
 �ṹ��    : FC_CFG_CPU_STRU
 �ṹ˵��  : FC_CFG_CPU�ṹ,CPU���ص����޺�����ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulCpuOverLoadVal;                       /*Range:[0,100]*//* CPU�������� */
    VOS_UINT32                          ulCpuUnderLoadVal;                      /*Range:[0,100]*//* CPU����������� */
    VOS_UINT32                          ulSmoothTimerLen;                       /*Range:[2,1000]*//* CPU����ƽ����������λ:CPU������� */
    VOS_UINT32                          ulStopAttemptTimerLen;                  /* CPU����R�ӿ����غ������ж�ʱ��ϳ���������ʱ����������ǰ�������λ: ���룬0��ʾ��ʹ�� */
    VOS_UINT32                          ulUmUlRateThreshold;                    /* �տ������������ޣ����ڴ����ޣ���Ϊ�����������CPU���ظߣ���Ҫ���� */
    VOS_UINT32                          ulUmDlRateThreshold;                    /* �տ������������ޣ����ڴ����ޣ���Ϊ�����������CPU���ظߣ���Ҫ���� */
    VOS_UINT32                          ulRmRateThreshold;                      /* E5��̬�£� WIFI/USB��ڴ��������ޣ� ���ڴ����ޣ���Ϊ�����������CPU���ظߣ���Ҫ���أ���λbps */
} FC_CFG_CPU_STRU;

/*****************************************************************************
 �ṹ��    : FC_CFG_MEM_THRESHOLD_STRU
 �ṹ˵��  : FC_CFG_MEM_THRESHOLD�ṹ,MEM���ص����޺�����ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetThreshold;                         /* ������������ ��λ�ֽ� */
    VOS_UINT32                          ulStopThreshold;                        /* ֹͣ�������� ��λ�ֽ� */
} FC_CFG_MEM_THRESHOLD_STRU;

/*****************************************************************************
 �ṹ��    : FC_CFG_MEM_THRESHOLD_CST_STRU
 �ṹ˵��  : FC_CFG_MEM_THRESHOLD_CST�ṹ,MEM���ص����޺�����ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulSetThreshold;                         /*Range:[0,4096]*//* ������������ ��λ�ֽ� */
    VOS_UINT32                          ulStopThreshold;                        /*Range:[0,4096]*//* ֹͣ�������� ��λ�ֽ� */
} FC_CFG_MEM_THRESHOLD_CST_STRU;


/*****************************************************************************
 �ṹ��    : FC_CFG_UM_UL_RATE_STRU
 �ṹ˵��  : FC_CFG_UM_UL_RATE�ṹ,�տ��������ʵ�λ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucRateCnt;                              /*Range:[0,11]*//* �������ʵ�λ���������֧��11����λ���ã��������ȼ����ΪFC_PRI_9������ʹ�õ�λʱֻ��ǰ9����Ч */
    VOS_UINT8                           aucRsv[1];
    VOS_UINT16                          ausRate[FC_UL_RATE_MAX_LEV];            /* �����������ƣ�ȡֵ��Χ[0,65535]����λbps */
} FC_CFG_UM_UL_RATE_STRU;

/*****************************************************************************
 �ṹ��    : FC_CFG_NV_STRU
 �ṹ˵��  : FC_CFG_NV��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFcEnbaleMask;                         /* ����ʹ�ܱ�ʶ */
    FC_CFG_CPU_STRU                     stFcCfgCpuA;                            /* A��CPU�������� */
    VOS_UINT32                          ulFcCfgMemThresholdCnt;                 /*Range:[0,8]*/
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgMem[FC_MEM_THRESHOLD_LEV_BUTT];  /* A���ڴ��������� */
    FC_CFG_MEM_THRESHOLD_CST_STRU       stFcCfgCst;                             /* CSDҵ���������� */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgGprsMemSize;                     /* Gģ�ڴ������������� */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgGprsMemCnt;                      /* Gģ�ڴ������������ */
    FC_CFG_CPU_STRU                     stFcCfgCpuC;                            /* C��CPU�������� */
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForCpu;                  /* C��CPU�����������ʵ�λ���� */
    FC_CFG_UM_UL_RATE_STRU              stFcCfgUmUlRateForTmp;                  /* C���¶��������������ʵ�λ���� */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgCdmaMemSize;                     /* Xģ�ڴ������������� */
    FC_CFG_MEM_THRESHOLD_STRU           stFcCfgCdmaMemCnt;                      /* Xģ�ڴ������������ */
} FC_CFG_NV_STRU;

/*****************************************************************************
 �ṹ��    : CPULOAD_CFG_STRU
 �ṹ˵��  : CPULOAD_CFG��Ӧ��NV�ṹ,CPU���ص����޺�����ֵ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulMonitorTimerLen;
} CPULOAD_CFG_STRU;

typedef struct
{
    VOS_UINT8                          ucHostOutTimeout;    /* PC�������ʱ�� */
    VOS_UINT8                          ucEthTxMinNum;       /* UE��������������� */
    VOS_UINT8                          ucEthTxTimeout;      /* UE�����������ʱ�� */
    VOS_UINT8                          ucEthRxMinNum;       /* UE��������������� */
    VOS_UINT8                          ucEthRxTimeout;      /* UE�����������ʱ�� */
    VOS_UINT8                          ucCdsGuDlThres;
    VOS_UINT8                          aucRsv[2];
}FC_DRV_ASSEM_PARA_STRU;

typedef struct
{
    VOS_UINT32                          ulCpuLoad;
    FC_DRV_ASSEM_PARA_STRU              stDrvAssemPara;
}FC_CPU_DRV_ASSEM_PARA_STRU;

/*****************************************************************************
 �ṹ��    : FC_CPU_DRV_ASSEM_PARA_NV_STRU
 �ṹ˵��  : FC_CPU_DRV_ASSEM��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                              ucEnableMask;
    VOS_UINT8                              ucSmoothCntUpLev;
    VOS_UINT8                              ucSmoothCntDownLev;
    VOS_UINT8                              ucRsv;
    FC_CPU_DRV_ASSEM_PARA_STRU             stCpuDrvAssemPara[FC_ACPU_DRV_ASSEM_NV_LEV];
}FC_CPU_DRV_ASSEM_PARA_NV_STRU;

/*****************************************************************************
 �ṹ��    : WTTF_MACDL_WATERMARK_LEVEL_STRU
 �ṹ˵��  : WTTF_MACDL_BBMST_WATER_LEVEL��Ӧ��NV�ṹ,BBP�����ж�ˮ�ߵȼ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWaterLevelOne;                        /* ˮ�߽��1 */
    VOS_UINT32                          ulWaterLevelTwo;                        /* ˮ�߽��2 */
    VOS_UINT32                          ulWaterLevelThree;                      /* ˮ�߽��3 */
    VOS_UINT32                          ulWaterLevelFour;                       /* ˮ�߽��4,Ԥ�� */
} WTTF_MACDL_WATERMARK_LEVEL_STRU;

/*****************************************************************************
 �ṹ��    : WTTF_MACDL_BBPMST_TB_HEAD_STRU
 �ṹ˵��  : WTTF_MACDL_BBMST_TB_HEAD��Ӧ��NV�ṹ,BBP�����ж�ˮ�ߵȼ��ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTBHeadNum;                /* TBͷ������� */
    VOS_UINT32                          ulTBHeadReserved;           /* TBͷ����Ԥ����TB������Ԥ��3֡��V9R1 30�飬V3R3 15��  */
} WTTF_MACDL_BBPMST_TB_HEAD_STRU;

/*****************************************************************************
 �ṹ��    : WTTF_SRB_NOT_SEND_THRESHOLD_STRU
 �ṹ˵��  : WTTF_SRB_NOT_SEND_THRESHOLD_STRU��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulWttfSrbNotSendThreshold;                /* SRB�����Ͳ������������ */
} WTTF_SRB_NOT_SEND_THRESHOLD_STRU;


/*****************************************************************************
 �ṹ��    : NF_EXT_NV_STRU
 �ṹ˵��  : NETFILTER_HOOK_MASK��Ӧ��NV�ṹ,���ù������NV�Ԥ��5���������:
             ulNvValue1~ulNvValue5, ÿ������ȡֵ��ΧΪ0-FFFFFFFF,
             ��������λΪ1����������λ��Ӧ�Ĺ��Ӻ������ܻᱻע�ᵽ�ں���
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulNetfilterPara1;
    VOS_UINT32          ulNetfilterPara2;
    VOS_UINT32          ulNetfilterPara3;
    VOS_UINT32          ulNetfilterPara4;
    VOS_UINT32          ulNetfilterPara5;
}NF_EXT_NV_STRU;

/*****************************************************************************
 �ṹ��    : EXT_TEBS_FLAG_NV_STRU
 �ṹ˵��  : NV_Ext_Tebs_Flag��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulExtTebsFlag;
}EXT_TEBS_FLAG_NV_STRU;

/*****************************************************************************
 �ṹ��    : TCP_ACK_DELETE_FLG_NV_STRU
 �ṹ˵��  : NV_TCP_ACK_Delete_Flg��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTcpAckDeleteFlg;
}TCP_ACK_DELETE_FLG_NV_STRU;

/*****************************************************************************
 �ṹ��    : HUAWEI_IRAN_OPEN_PAGE_I_NV_STRU
 �ṹ˵��  : HUAWEI_IRAN_OPEN_PAGE_I_NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usHuaweiIranOpenPageI;      /*Range:[0,1]*/
    VOS_UINT8           aucReserve[2];
}HUAWEI_IRAN_OPEN_PAGE_I_NV_STRU;

/*****************************************************************************
 �ṹ��    : GCF_TYPE_CONTENT_NV_STRU
 �ṹ˵��  : GCFTypeContent��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulGcfTypeContent;
}GCF_TYPE_CONTENT_NV_STRU;

/*****************************************************************************
 �ṹ��    : W_RF8960_BER_TEST_NV_STRU
 �ṹ˵��  : W_RF8960_BER_Test��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulRlc8960RFBerTestFlag;
}W_RF8960_BER_TEST_NV_STRU;

/*****************************************************************************
 �ṹ��    : LAPDM_RAND_BIT_NV_STRU
 �ṹ˵��  : LAPDM_RAND_BIT��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16          usLapdmRandBit;         /*Range:[0,1]*/
    VOS_UINT8           aucReserve[2];
}LAPDM_RAND_BIT_NV_STRU;

/*****************************************************************************
 �ṹ��    : CBS_W_DRX_SWITCH_NV_STRU
 �ṹ˵��  : CBS_W_DRX_Switch��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulCbsWDrxSwitch;
}CBS_W_DRX_SWITCH_NV_STRU;

/*****************************************************************************
 �ṹ��    : CBS_W_WAIT_NEW_CBS_MSG_TIMER_NV_STRU
 �ṹ˵��  : CBS_W_WaitNewCBSMsgTimer��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulCbsWWaitNewCbsMsgTimer;
}CBS_W_WAIT_NEW_CBS_MSG_TIMER_NV_STRU;

/*****************************************************************************
 �ṹ��    : CBS_W_WAIT_SHED_MSG_TIMER_NV_STRU
 �ṹ˵��  : CBS_W_WaitShedMsgTimer��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulCbsWWaitShedMsgTimer;
}CBS_W_WAIT_SHED_MSG_TIMER_NV_STRU;

/*****************************************************************************
 �ṹ��    : FC_QOS_STRU
 �ṹ˵��  : FC_QOS_STRU ��׮ʹ�ýṹ,Ŀǰ�������Ѿ���ʹ�ã�Ϊ�˱���NV�ṹ���仯
*****************************************************************************/

typedef struct
{
    VOS_UINT32          ulULKBitRate;
    VOS_UINT32          ulDLKBitRate;
}FC_QOS_STRU;

/*****************************************************************************
 �ṹ��    : CPU_FLOW_CTRL_CONFIG_NV_STRU
 �ṹ˵��  : CPU_FLOW_CTRL_CONFIG_STRU��Ӧ��NV�ṹ���ѷ�������׮�ṩ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulFuncMask;
    VOS_UINT32          ulCpuOverLoadVal;
    VOS_UINT32          ulCpuUnderLoadVal;
    FC_QOS_STRU         astQos1[2];
    FC_QOS_STRU         astQos2[2];
    FC_QOS_STRU         stUmtsEhsUlLimitForDlHighRate;
    FC_QOS_STRU         stUmtsHslULimitForDlHighRate;
    FC_QOS_STRU         stUlLimitForDlLowRate;
    VOS_UINT32          ulRItfDlkBitRate;
    VOS_UINT32          ulRItfRate;
    VOS_UINT32          ulWaitQosTimeLen;
    VOS_UINT32          ulSmoothTimerLen;
    VOS_UINT32          ulRItfSetTimerLen;
    VOS_UINT32          ulCpuFlowCtrlEnable;
    VOS_UINT32          aulRsv[2];
}CPU_FLOW_CTRL_CONFIG_NV_STRU;

/*****************************************************************************
 �ṹ��    : R_ITF_FLOW_CTRL_CONFIG_STRU
 �ṹ˵��  : R_ITF_FLOW_CTRL_CONFIG_STRU��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32              ulRateDismatchUsbEnable;
    VOS_UINT32              ulRateDismatchWifiEnable;
} R_ITF_FLOW_CTRL_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : TFC_POWER_FUN_ENABLE_NV_STRU
 �ṹ˵��  : TFC_POWER_FUN_ENABLE��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulTfcPowerFunEnable;
}TFC_POWER_FUN_ENABLE_NV_STRU;

/*****************************************************************************
�ṹ��    : PPP_CONFIG_MRU_TYPE_NV_STRU
�ṹ˵��  : PPP_CONFIG_MRU_Type��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                           usPppConfigType;   /*Range:[296,1500]*/
    VOS_UINT8                            aucReserve[2];
}PPP_CONFIG_MRU_TYPE_NV_STRU;

/*****************************************************************************
 �ṹ��    : FC_CDS_DL_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����CDS���ж����������ýṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulDiscardThres;         /* CDS���ж��ж������� */
    VOS_UINT32          ulDiscardRate;          /* ������ */
} FC_CDS_DL_CONFIG_STRU;

/*****************************************************************************
 �ṹ��    : QOS_FC_CONFIG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����QOS�������ýṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32          ulPktCntLimit;              /* ����QoS���ذ��� */
    VOS_UINT32          ulTimerLen;                 /* ����QoS����ʱ�� */
    VOS_UINT32          ulRandomDiscardRate;        /* ��������� */
    VOS_UINT32          ulDiscardRate;              /* ������ */
    VOS_UINT32          ulWarningThres;             /* ������ֵ�������뱣���ĳ�����ȫ����Ϊ����״̬ */
    VOS_UINT32          ulDiscardThres;             /* ������ֵ���ӵ����ȼ����ؿ�ʼ�ó���Ϊ����״̬ */
    VOS_UINT32          ulRandomDiscardThres;       /* ���������ֵ���ӵ����ȼ����ؿ�ʼ�ó���Ϊ�������״̬ */
    VOS_UINT32          ulRestoreThres;             /* �ָ���ֵ���Ӹ����ȼ����ؿ�ʼ�𽥻ָ��������� */
} QOS_FC_CONFIG_STRU;

typedef struct
{
    VOS_UINT32              ulFcEnableMask;         /* ���ؿ��� */
                                                    /* bit0 QoS�����Ƿ�ʹ�� */
                                                    /* bit1 ������ȼ������Ƿ����� */
                                                    /* bit2 CDS���������Ƿ�ʹ�� */
                                                    /* bit3 ������ȼ������Ƿ񲻶��� */
    QOS_FC_CONFIG_STRU      stQosFcConfig;
    FC_CDS_DL_CONFIG_STRU   stFcCdsDlConfig;
}FLOWCTRL_CDS_CONFIG_STRU;

/*****************************************************************************
�ṹ��    : BMC_CBS_MSG_READ_NV_STRU
�ṹ˵��  : BMC_CBS_MSG_READ_NV_STRU��Ӧ��NV�ṹ
*****************************************************************************/

typedef struct
{
    VOS_UINT8               ucDisableReadAdvised;       /*Range:[0,1]*//*��������Ϣ����Ϣ��������Ϊadvisedʱ����ӦDRX��������Ϣ�Ƿ���ܣ� PS_FALSEΪ�����ܣ�PS_TRUEΪ����*/
    VOS_UINT8               ucDisableReadOptional;      /*Range:[0,1]*//*��������Ϣ����Ϣ��������Ϊoptionalʱ����ӦDRX��������Ϣ�Ƿ���ܣ�PS_FALSEΪ�����ܣ�PS_TRUEΪ����*/
    VOS_UINT8               ucDisableRepetitionMsg;     /*Range:[0,1]*//*��������Ϣ����Ϣ��������ΪRepetition msgʱ����ӦDRX��������Ϣ�Ƿ���ܣ�PS_FALSEΪ�����ܣ�PS_TRUEΪ����*/
    VOS_UINT8               ucDisableOldMsg;            /*Range:[0,1]*//*��������Ϣ����Ϣ��������Ϊold msgʱ����ӦDRX��������Ϣ�Ƿ���ܣ�PS_FALSEΪ�����ܣ�PS_TRUEΪ����*/
}BMC_CBS_MSG_READ_NV_STRU;


/*****************************************************************************
�ṹ��    : NV_MODEM_RF_SHARE_CFG_STRU
�ṹ˵��  : NV_MODEM_RF_SHARE_CFG��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usSupportFlag;      /*Range:[0,2]*//* �ֱ��ʾ��֧��DSDS,֧��DSDS1.0,֧��DSDS2.0 */
    VOS_UINT16                          usGSMRFID;          /* GSM����ģʽRFID��Ϣ */
    VOS_UINT16                          usWCDMARFID;        /* WCDMA����ģʽRFID��Ϣ */
    VOS_UINT16                          usTDSRFID;          /* TD-SCDMA����ģʽRFID��Ϣ */
    VOS_UINT16                          usLTERFID;          /* LTE����ģʽRFID��Ϣ */
    VOS_UINT16                          usCDMARFID;         /* CMDA����ģʽRFID��Ϣ */
    VOS_UINT16                          usEVDORFID;         /* CDMA EVDO����ģʽRFID��Ϣ */
    VOS_UINT16                          usReserved;
} NV_MODEM_RF_SHARE_CFG_STRU;


/*****************************************************************************
�ṹ��    : NV_MODEM_RF_SHARE_CFG_EX_STRU
�ṹ˵��  : NV_MODEM_RF_SHARE_CFG_EX_STRU��Ӧ��NV�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulProfileTypeId;     /* ��ȡen_NV_Item_TRI_MODE_FEM_PROFILE_ID��ȡulProfileId,
                                                               ��Ӧ��ȡ������������һ������ */
    NV_MODEM_RF_SHARE_CFG_STRU          astNvModemRfShareCfg[8];
}NV_MODEM_RF_SHARE_CFG_EX_STRU;

/*****************************************************************************
�ṹ��    : PLATFORM_RAT_TYPE_ENUM
�ṹ˵��  : ���뼼��

  1.��    ��   : 2015��4��27��
    ��    ��   : g00260269
    �޸�����   : ����
*******************************************************************************/
enum NV_PLATFORM_RAT_TYPE_ENUM
{
    NV_PLATFORM_RAT_GSM,                                                       /*GSM���뼼�� */
    NV_PLATFORM_RAT_WCDMA,                                                     /* WCDMA���뼼�� */
    NV_PLATFORM_RAT_LTE,                                                       /* LTE���뼼�� */
    NV_PLATFORM_RAT_TDS,                                                       /* TDS���뼼�� */
    NV_PLATFORM_RAT_1X,                                                        /* CDMA-1X���뼼�� */
    NV_PLATFORM_RAT_EVDO,                                                      /* CDMA-EV_DO���뼼�� */

    NV_PLATFORM_RAT_BUTT
};
typedef VOS_UINT16 NV_PLATFORM_RAT_TYPE_ENUM_UINT16;

/*****************************************************************************
�ṹ��    : NV_PLATAFORM_RAT_CAPABILITY_STRU
�ṹ˵��  : ƽ̨֧�ֵĽ��뼼��

  1.��    ��   : 2015��4��27��
    ��    ��   : g00260269
    �޸�����   : ����
*******************************************************************************/
typedef struct
{
    VOS_UINT16                           usRatNum;                          /* ���뼼������Ŀ*/
    NV_PLATFORM_RAT_TYPE_ENUM_UINT16     aenRatList[NV_PLATFORM_MAX_RAT_NUM];  /* ���뼼�� */
}NV_PLATAFORM_RAT_CAPABILITY_STRU;

/*****************************************************************************
�ṹ��    : BASTET_SUPPORT_FLG_STRU
�ṹ˵��  : BASTET_SUPPORT_FLG_STRU�ṹ
  1.��    ��   : 2014��11��22��
    ��    ��   : z00128442
    �޸�����   : ����bastet����nv
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucActiveFlg;        /* �Ƿ񼤻�� */
    VOS_UINT8                           ucHookFlg;          /* Bastet����ģʽ */
    VOS_UINT8                           aucSubFun[2];
}BASTET_SUPPORT_FLG_STRU;

/*****************************************************************************
�ṹ��    : NV_CTTF_BOOL_ENUM_UINT8
�ṹ˵��  :

  1.��    ��   : 2015��9��9��
    ��    ��   : c00309867
    �޸�����   : ����
*******************************************************************************/
enum NV_CTTF_BOOL_ENUM
{
    NV_CTTF_BOOL_FALSE,                /* ����Ϊ�� */
    NV_CTTF_BOOL_TRUE,               /* ����Ϊ�� */
    NV_CTTF_BOOL_BUTT
};
typedef VOS_UINT8 NV_CTTF_BOOL_ENUM_UINT8;

/*****************************************************************************
�ṹ��    : NV_SUPPORT_PROBE_INIT_ADJ_CFG_STRU
�ṹ˵��  : NV_SUPPORT_PROBE_INIT_ADJ_CFG_STRU�ṹ
  1.��    ��   : 2015��9��0��
    ��    ��   : c00309867
    �޸�����   : ����nv
*****************************************************************************/
typedef struct
{
    NV_CTTF_BOOL_ENUM_UINT8             enSupportFlg;                   /* �Ƿ�֧��ͨ��NV������cProbeInitialAdjust��NV_CTTF_BOOL_TRUE:��֧�֣�NV_CTTF_BOOL_TRUE֧��*/
    VOS_INT8                            cProbeInitialAdjust;            /* cProbeInitialAdjust��ֵ */
    VOS_UINT8                           aucSubFun[2];
}NV_CTTF_PROBE_INIT_POWER_CTRL_STRU;


/*****************************************************************************
�ṹ��    : TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU
�ṹ˵��  : TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU�ṹ
  1.��    ��   : 2015��08��29��
    ��    ��   : w00316385
    �޸�����   : ��������nv
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          usMru;                  /* PPP֡�����յ�Ԫ���� */
    VOS_UINT8                           ucReserved;
    VOS_UINT8                           ucCaveEnable;           /* PPP�����ȨCAVE�㷨���أ�0��֧�֣�1֧�� */
    VOS_UINT32                          ulPppInactTimerLen;     /* MAX PPP Inactive Timerʱ������λs */
}TTF_PPPC_NVIM_CONFIG_OPTIONS_STRU;

/*****************************************************************************
�ṹ��    : NV_HRPD_RF_ALLOC_SWITCH_MASK_STRU
�ṹ˵��  : NV_HRPD_RF_ALLOC_SWITCH_MASK_STRU�ṹ
            ulHrpdRfAllocSwitchMask ÿ��bitΪ1��ʾʹ�ܣ�0��ʾ��ʹ��
            bit 0:signaling alloc rf
            bit 1:ppp in access auth alloc rf
  1.��    ��   : 2016��3��14��
    ��    ��   : t00359887
    �޸�����   : ����nv
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulHrpdRfAllocSwitchMask;
}NV_HRPD_RF_ALLOC_SWITCH_MASK_STRU;


/*****************************************************************************
�ṹ��    : NV_TTF_NODE_RESET_CTRL_STRU
�ṹ˵��  : NV_TTF_NODE_RESET_CTRL_STRU�ṹ
  1.��    ��   : 2016��01��26��
    ��    ��   : m00314743
    �޸�����   : ����nv
*****************************************************************************/
typedef struct
{
    NV_CTTF_BOOL_ENUM_UINT8             enResetEnable;                  /* TTF_Node������λʱ�� */
    VOS_UINT8                           ucFailPercent;             /* ����ʧ�ܱ������ޣ��ﵽʱ������λ */
    VOS_UINT16                          usTotalStat;               /* �ڵ�����ͳ���ܴ��� */
}NV_RATIO_RESET_CTRL_STRU;

/*****************************************************************************
�ṹ��    : NV_NODE_RESET_CTRL_STRU
�ṹ˵��  : NV_NODE_RESET_CTRL_STRU�ṹ
  1.��    ��   : 2016��01��26��
    ��    ��   : m00314743
    �޸�����   : ����nv
*****************************************************************************/
typedef struct
{
    NV_RATIO_RESET_CTRL_STRU                  astNvResetCtrl[RATIO_RESET_TYPE_BUTT];
}NV_NODE_RESET_CTRL_STRU;

/*****************************************************************************
 �ṹ��    : TTF_CICOM_IP_ENT_NVIM_STRU
 �ṹ˵��  : TTF_CICOM_IP_ENT_NVIM_STRU��Ӧ��NV�ṹ,CIOCM����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                          ucCicomIPNumber;         /* CIOCM���� */
    VOS_UINT8                          aucRsv[3];

    VOS_UINT8                          aucModemIdToCicomIndex[NV_PLATFORM_MAX_MODEM_NUM];   /* �����±�ΪModem id,��ֵ�����Ӧʹ�õ�CIOCM Index��0~ucCicomIPNumber-1 */
}TTF_CICOM_IP_ENT_NVIM_STRU;

/*****************************************************************************
�ṹ��    : NV_NODE_RESET_CTRL_STRU
�ṹ˵��  : NV_NODE_RESET_CTRL_STRU�ṹ
  1.��    ��   : 2016��02��20��
    ��    ��   : m00314743
    �޸�����   : ����nv
*****************************************************************************/
typedef struct
{
    NV_CTTF_BOOL_ENUM_UINT8             enTpeEnable;             /* TPEʹ�� */
    VOS_UINT8                           ucCorrectPercent;        /* ��������:����ʱ���ٵȰٷֱȵ�ʱ�� */
    VOS_UINT8                           aucReserved[2];
}NV_TTF_TPE_CTRL_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/
















#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TtfNvInterface.h */
