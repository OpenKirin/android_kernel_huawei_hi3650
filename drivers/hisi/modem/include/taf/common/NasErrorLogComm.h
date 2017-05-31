

#ifndef __NAS_ERRORLOGCOMM_H__
#define __NAS_ERRORLOGCOMM_H__

/*****************************************************************************
  1 其他头文件包含
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
  2 宏定义
*****************************************************************************/
#define NAS_ERR_LOG_CTRL_LEVEL_NULL                     (0)                     /* ErrLog等级未定义*/
#define NAS_ERR_LOG_CTRL_LEVEL_CRITICAL                 (1)                     /* ErrLog等级为紧急 */
#define NAS_ERR_LOG_CTRL_LEVEL_MAJOR                    (2)                     /* ErrLog等级为重要 */
#define NAS_ERR_LOG_CTRL_LEVEL_MINOR                    (3)                     /* ErrLog等级为次要 */
#define NAS_ERR_LOG_CTRL_LEVEL_WARNING                  (4)                     /* ErrLog等级为提示 */


/*****************************************************************************
  3 枚举定义
*****************************************************************************/

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_CALL_EX_STATE_ENUM
 枚举说明  : 呼叫状态
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
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
    NAS_ERR_LOG_CALL_S_CCBS_WAITING_ACTIVE,                                     /* CCBS等待激活态 */
    NAS_ERR_LOG_CALL_S_CCBS_WAITING_RECALL,                                     /* CCBS等待回呼态 */
    NAS_ERR_LOG_CALL_S_UNKNOWN,                                                 /* unknown state */
    NAS_ERR_LOG_CALL_S_MO_FDN_CHECK,                                            /* FDN check */
    NAS_ERR_LOG_CALL_S_MO_CALL_CONTROL_CHECK,                                   /* CALL CONTROL check */

    NAS_ERR_LOG_CALL_S_BUTT
};
typedef VOS_UINT8  NAS_ERR_LOG_CALL_STATE_ENUM_U8;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_ALM_REPORT_TYPE_ENUM
 枚举说明  : err log主动上报类型
 1.日    期   : 2013年07月06日
   作    者   : n00269697
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM
{
    NAS_ERR_LOG_FAULT_REPORT                                = 0x01,             /* 故障上报 */
    NAS_ERR_LOG_ALARM_REPORT                                = 0x02,             /* 告警上报 */

    NAS_ERR_LOG_REPORT_TYPE_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16;

/*****************************************************************************
 枚举名    : NAS_ERR_LOG_ALM_TYPE_ENUM
 枚举说明  : 故障告警类型
 1.日    期   : 2013年08月27日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
enum NAS_ERR_LOG_ALM_TYPE_ENUM
{
    NAS_ERR_LOG_ALM_TYPE_COMMUNICATION    = 0x00,                               /* 通信 */
    NAS_ERR_LOG_ALM_TYPE_TRAFFIC_QUALITY  = 0x01,                               /* 业务质量 */
    NAS_ERR_LOG_ALM_TYPE_DEAL_WRONG       = 0x02,                               /* 处理出错 */
    NAS_ERR_LOG_ALM_TYPE_DEVICE_FAILURE   = 0x03,                               /* 设备故障 */
    NAS_ERR_LOG_ALM_TYPE_ENV_FAILURE      = 0x04,                               /* 环境故障 */
    NAS_ERR_LOG_ALM_TYPE_BUTT
};
typedef VOS_UINT16  NAS_ERR_LOG_ALM_TYPE_ENUM_U16;

/*****************************************************************************
枚举名    :  NAS_ERR_LOG_OOS_CAUSE_ENUM
结构说明  :  导致无服务的原因值枚举
1.日    期   : 2015年08月13日
  作    者   : f00179208
  修改内容   : 新增
*****************************************************************************/
enum NAS_ERR_LOG_OOS_CAUSE_ENUM
{
    NAS_ERR_LOG_OOS_CAUSE_NULL                                           = 0x0,

    /* 用户配置的场景 */
    NAS_ERR_LOG_OOS_CAUSE_USER_SYSCFG                                    = 0x001,
    NAS_ERR_LOG_OOS_CAUSE_USER_LIST_SRCH                                 = 0x002,
    NAS_ERR_LOG_OOS_CAUSE_USER_SPEC_SRCH                                 = 0x003,
    NAS_ERR_LOG_OOS_CAUSE_USER_AUTO_SEL                                  = 0x004,
    NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON                                  = 0x005,
    NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF                                 = 0x006,
    NAS_ERR_LOG_OOS_CAUSE_USER_DETACH                                    = 0x007,

    /* 接入层丢网的场景 */
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

    /* 注册失败的场景 */
    NAS_ERR_LOG_OOS_CAUSE_CS_REG_FAIL                                    = 0x200,
    NAS_ERR_LOG_OOS_CAUSE_PS_REG_FAIL                                    = 0x201,
    NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ATTACH_FAIL                    = 0x202,
    NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_TAU_FAIL                       = 0x203,
    NAS_ERR_LOG_OOS_CAUSE_COMBINE_EPS_REG_ONLY_EPS_SUCC                  = 0x204,
    NAS_ERR_LOG_OOS_CAUSE_EPS_REG_ATTACH_FAIL                            = 0x205,
    NAS_ERR_LOG_OOS_CAUSE_EPS_REG_TAU_FAIL                               = 0x206,
    NAS_ERR_LOG_OOS_CAUSE_EPS_ONLY_ATTACH                                = 0x207,
    NAS_ERR_LOG_OOS_CAUSE_ATTACH_AUTH_REJ                                = 0x208,

    /* 服务被拒的场景 */
    NAS_ERR_LOG_OOS_CAUSE_CM_SERVICE_REJ                                 = 0x300,
    NAS_ERR_LOG_OOS_CAUSE_PS_SERVICE_REG_FAIL                            = 0x301,
    NAS_ERR_LOG_OOS_CAUSE_EPS_SERVICE_REQ_FAIL                           = 0x302,

    /* 网络DETACH的场景 */
    NAS_ERR_LOG_OOS_CAUSE_GUT_NW_DETACH                                  = 0x400,
    NAS_ERR_LOG_OOS_CAUSE_LTE_NW_DETACH                                  = 0x401,

    /* 本地DETACH的场景 */
    NAS_ERR_LOG_OOS_CAUSE_GUT_LOCAL_DETACH                               = 0x500,
    NAS_ERR_LOG_OOS_CAUSE_LTE_LOCAL_DETACH                               = 0x501,

    /* 内部触发的场景 */
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
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/


/*****************************************************************************
 结构名    : NAS_ERR_LOG_APS_FSM_CTX_STRU
 结构说明  : 状态机状态描述结构
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulFsmId;                                /* 当前状态机标识 */
    VOS_UINT32                          ulState;                                /* 当前状态 */
}NAS_ERR_LOG_APS_FSM_CTX_STRU;

/*****************************************************************************
 结构名    : NAS_MNTN_APS_FSM_INFO_STRU
 结构说明  : APS状态机信息
 1.日    期   : 2013年08月12日
   作    者   : f00179208
   修改内容   : 新建
*****************************************************************************/
typedef struct
{
    NAS_ERR_LOG_APS_FSM_CTX_STRU        stMainFsm;                              /* 主状态机 */
    NAS_ERR_LOG_APS_FSM_CTX_STRU        stSubFsm;                               /* 子状态机 */
    VOS_UINT8                           ucPdpId;                                /* 当前状态机所对应的PDP ID */
    VOS_UINT8                           aucReserve[3];
}NAS_ERR_LOG_APS_PDP_ENTITY_FSM_INFO_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_ALM_LEVEL_STRU
 结构说明  : Alm ID与log级别对应的结构体
 1.日    期   : 2013年08月12日
   作    者   : s00190137
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_ALM_ID_ENUM_U16             enAlmID;        /* 异常模块ID */
    VOS_UINT16                              usLogLevel;     /* 上报log等级 */
}NAS_ERR_LOG_ALM_LEVEL_STRU;

/*******************************************************************************
 结构名    : NAS_ERR_LOG_ALM_REPORT_TYPE_STRU
 结构说明  : Alm ID与主动上报类型对应的结构体
 1.日    期   : 2015年07月06日
   作    者   : n00269697
   修改内容   : 新建
*******************************************************************************/
typedef struct
{
    NAS_ERR_LOG_ALM_ID_ENUM_U16                             enAlmID;            /* 异常模块ID */
    NAS_ERR_LOG_UNSOLI_REPORT_TYPE_ENUM_U16                 enReportType;       /* 上报log等级 */
}NAS_ERR_LOG_ALM_REPORT_TYPE_STRU;


/*****************************************************************************
  8 UNION定义
*****************************************************************************/


/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
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


