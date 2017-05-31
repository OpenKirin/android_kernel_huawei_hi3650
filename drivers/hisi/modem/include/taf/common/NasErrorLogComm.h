

#ifndef __NAS_ERRORLOGCOMM_H__
#define __NAS_ERRORLOGCOMM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "errorlog.h"
#include "omerrorlog.h"
#include "errlog_cfg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_ERR_LOG_CTRL_LEVEL_NULL                     (0)                     /* ErrLog�ȼ�δ����*/
#define NAS_ERR_LOG_CTRL_LEVEL_CRITICAL                 (1)                     /* ErrLog�ȼ�Ϊ���� */
#define NAS_ERR_LOG_CTRL_LEVEL_MAJOR                    (2)                     /* ErrLog�ȼ�Ϊ��Ҫ */
#define NAS_ERR_LOG_CTRL_LEVEL_MINOR                    (3)                     /* ErrLog�ȼ�Ϊ��Ҫ */
#define NAS_ERR_LOG_CTRL_LEVEL_WARNING                  (4)                     /* ErrLog�ȼ�Ϊ��ʾ */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : NAS_ERR_LOG_CALL_EX_STATE_ENUM
 ö��˵��  : ����״̬
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_CALL_EX_STATE_ENUM
{
    NAS_ERR_LOG_CALL_S_ACTIVE,                                                  /* active */
    NAS_ERR_LOG_CALL_S_HELD,                                                    /* held */
    NAS_ERR_LOG_CALL_S_DIALING,                                                 /* dialing (MO call) */
    NAS_ERR_LOG_CALL_S_ALERTING,                                                /* alerting (MO call) */
    NAS_ERR_LOG_CALL_S_INCOMING,                                                /* incoming (MT call) */
    NAS_ERR_LOG_CALL_S_WAITING,                                                 /* waiting (MT call) */
    NAS_ERR_LOG_CALL_S_IDLE,                                                    /* idle */
    NAS_ERR_LOG_CALL_S_CCBS_WAITING_ACTIVE,                                     /* CCBS�ȴ�����̬ */
    NAS_ERR_LOG_CALL_S_CCBS_WAITING_RECALL,                                     /* CCBS�ȴ��غ�̬ */
    NAS_ERR_LOG_CALL_S_UNKNOWN,                                                 /* unknown state */
    NAS_ERR_LOG_CALL_S_MO_FDN_CHECK,                                            /* FDN check */
    NAS_ERR_LOG_CALL_S_MO_CALL_CONTROL_CHECK,                                   /* CALL CONTROL check */

    NAS_ERR_LOG_CALL_S_BUTT
};
typedef VOS_UINT8  NAS_ERR_LOG_CALL_STATE_ENUM_U8;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_ALM_REPORT_TYPE_ENUM
 ö��˵��  : err log�����ϱ�����
 1.��    ��   : 2013��07��06��
   ��    ��   : n00269697
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM
{
    NAS_ERR_LOG_FAULT_REPORT                                = 0x01,             /* �����ϱ� */
    NAS_ERR_LOG_ALARM_REPORT                                = 0x02,             /* �澯�ϱ� */

    NAS_ERR_LOG_REPORT_TYPE_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16;

/*****************************************************************************
 ö����    : NAS_ERR_LOG_ALM_TYPE_ENUM
 ö��˵��  : ���ϸ澯����
 1.��    ��   : 2013��08��27��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
enum NAS_ERR_LOG_ALM_TYPE_ENUM
{
    NAS_ERR_LOG_ALM_TYPE_COMMUNICATION    = 0x00,                               /* ͨ�� */
    NAS_ERR_LOG_ALM_TYPE_TRAFFIC_QUALITY  = 0x01,                               /* ҵ������ */
    NAS_ERR_LOG_ALM_TYPE_DEAL_WRONG       = 0x02,                               /* ������� */
    NAS_ERR_LOG_ALM_TYPE_DEVICE_FAILURE   = 0x03,                               /* �豸���� */
    NAS_ERR_LOG_ALM_TYPE_ENV_FAILURE      = 0x04,                               /* �������� */
    NAS_ERR_LOG_ALM_TYPE_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_ALM_TYPE_ENUM_U16;

/*****************************************************************************
ö����    :  NAS_ERR_LOG_OOS_CAUSE_ENUM
�ṹ˵��  :  �����޷����ԭ��ֵö��
1.��    ��   : 2015��08��13��
  ��    ��   : f00179208
  �޸�����   : ����
*****************************************************************************/
enum NAS_ERR_LOG_OOS_CAUSE_ENUM
{
    NAS_ERR_LOG_OOS_CAUSE_NULL                                           = 0x0,

    /* �û����õĳ��� */
    NAS_ERR_LOG_OOS_CAUSE_USER_SYSCFG                                    = 0x001,
    NAS_ERR_LOG_OOS_CAUSE_USER_LIST_SRCH                                 = 0x002,
    NAS_ERR_LOG_OOS_CAUSE_USER_SPEC_SRCH                                 = 0x003,
    NAS_ERR_LOG_OOS_CAUSE_USER_AUTO_SEL                                  = 0x004,
    NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON                                  = 0x005,
    NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF                                 = 0x006,
    NAS_ERR_LOG_OOS_CAUSE_USER_DETACH                                    = 0x007,

    /* ����㶪���ĳ��� */
    NAS_ERR_LOG_OOS_CAUSE_GAS_NORMAL_AREA_LOST                           = 0x100,
    NAS_ERR_LOG_OOS_CAUSE_WAS_NORMAL_AREA_LOST                           = 0x101,
    NAS_ERR_LOG_OOS_CAUSE_TAS_NORMAL_AREA_LOST                           = 0x102,
    NAS_ERR_LOG_OOS_CAUSE_LMM_NORMAL_AREA_LOST                           = 0x103,
    NAS_ERR_LOG_OOS_CAUSE_GAS_NO_RF_AREA_LOST                            = 0x104,
    NAS_ERR_LOG_OOS_CAUSE_WAS_NO_RF_AREA_LOST                            = 0x105,
    NAS_ERR_LOG_OOS_CAUSE_TAS_NO_RF_AREA_LOST                            = 0x106,
    NAS_ERR_LOG_OOS_CAUSE_LMM_NO_RF_AREA_LOST                            = 0x107,
    NAS_ERR_LOG_OOS_CAUSE_WAS_LIMITED_CAMP                               = 0x108,
    NAS_ERR_LOG_OOS_CAUSE_TAS_LIMITED_CAMP                               = 0x109,
    NAS_ERR_LOG_OOS_CAUSE_GAS_AC_INFO_CHANGE                             = 0x10a,
    NAS_ERR_LOG_OOS_CAUSE_WAS_AC_INFO_CHANGE                             = 0x10b,
    NAS_ERR_LOG_OOS_CAUSE_TAS_AC_INFO_CHANGE                             = 0x10c,

    /* ע��ʧ�ܵĳ��� */
    NAS_ERR_LOG_OOS_CAUSE_CS_REG_FAIL                                    = 0x200,
    NAS_ERR_LOG_OOS_CAUSE_PS_REG_FAIL                                    = 0x201,
    NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ATTACH_FAIL                    = 0x202,
    NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_TAU_FAIL                       = 0x203,
    NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ONLY_EPS_SUCC                  = 0x204,
    NAS_ERR_LOG_OOS_CAUSE_EPS_REG_ATTACH_FAIL                            = 0x205,
    NAS_ERR_LOG_OOS_CAUSE_EPS_REG_TAU_FAIL                               = 0x206,
    NAS_ERR_LOG_OOS_CAUSE_EPS_ONLY_ATTACH                                = 0x207,
    NAS_ERR_LOG_OOS_CAUSE_ATTACH_AUTH_REJ                                = 0x208,

    /* ���񱻾ܵĳ��� */
    NAS_ERR_LOG_OOS_CAUSE_CM_SERVICE_REJ                                 = 0x300,
    NAS_ERR_LOG_OOS_CAUSE_PS_SERVICE_REG_FAIL                            = 0x301,
    NAS_ERR_LOG_OOS_CAUSE_EPS_SERVICE_REQ_FAIL                           = 0x302,

    /* ����DETACH�ĳ��� */
    NAS_ERR_LOG_OOS_CAUSE_GUT_NW_DETACH                                  = 0x400,
    NAS_ERR_LOG_OOS_CAUSE_LTE_NW_DETACH                                  = 0x401,

    /* ����DETACH�ĳ��� */
    NAS_ERR_LOG_OOS_CAUSE_GUT_LOCAL_DETACH                               = 0x500,
    NAS_ERR_LOG_OOS_CAUSE_LTE_LOCAL_DETACH                               = 0x501,

    /* �ڲ������ĳ��� */
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP  = 0x600,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP  = 0x601,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP  = 0x602,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP = 0x603,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP         = 0x604,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP         = 0x605,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP         = 0x606,
    NAS_ERR_LOG_OOS_CAUSE_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP        = 0x607,
    NAS_ERR_LOG_OOS_CAUSE_HIGH_PRO_PLMN_SRCH_BACK_TO_ORIG_PLMN_FAIL      = 0x608,
    NAS_ERR_LOG_OOS_CAUSE_DISABLE_LTE                                    = 0x609,
    NAS_ERR_LOG_OOS_CAUSE_ENABLE_LTE                                     = 0x60a,

    NAS_ERR_LOG_OOS_CAUSE_BUTT                                           = 0xFFFFFFFF
};
typedef VOS_UINT32 NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32;

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
 �ṹ��    : NAS_ERR_LOG_APS_FSM_CTX_STRU
 �ṹ˵��  : ״̬��״̬�����ṹ
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFsmId;                                /* ��ǰ״̬����ʶ */
    VOS_UINT32                          ulState;                                /* ��ǰ״̬ */
}NAS_ERR_LOG_APS_FSM_CTX_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MNTN_APS_FSM_INFO_STRU
 �ṹ˵��  : APS״̬����Ϣ
 1.��    ��   : 2013��08��12��
   ��    ��   : f00179208
   �޸�����   : �½�
*****************************************************************************/
typedef struct
{
    NAS_ERR_LOG_APS_FSM_CTX_STRU        stMainFsm;                              /* ��״̬�� */
    NAS_ERR_LOG_APS_FSM_CTX_STRU        stSubFsm;                               /* ��״̬�� */
    VOS_UINT8                           ucPdpId;                                /* ��ǰ״̬������Ӧ��PDP ID */
    VOS_UINT8                           aucReserve[3];
}NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_ALM_LEVEL_STRU
 �ṹ˵��  : Alm ID��log�����Ӧ�Ľṹ��
 1.��    ��   : 2013��08��12��
   ��    ��   : s00190137
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_ALM_ID_ENUM_U16             enAlmID;        /* �쳣ģ��ID */
    VOS_UINT16                              usLogLevel;     /* �ϱ�log�ȼ� */
}NAS_ERR_LOG_ALM_LEVEL_STRU;

/*******************************************************************************
 �ṹ��    : NAS_ERR_LOG_ALM_REPORT_TYPE_STRU
 �ṹ˵��  : Alm ID�������ϱ����Ͷ�Ӧ�Ľṹ��
 1.��    ��   : 2015��07��06��
   ��    ��   : n00269697
   �޸�����   : �½�
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_ALM_ID_ENUM_U16                             enAlmID;            /* �쳣ģ��ID */
    NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16                 enReportType;       /* �ϱ�log�ȼ� */
}NAS_ERR_LOG_ALM_REPORT_TYPE_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


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

#endif /* end of NasErrorLogComm.h */


