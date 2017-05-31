/******************************************************************************


        @(#)Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : ImsaNvInterface.h
    Description : Imsa NV 头文件
    History     :
      1.sunbing 00049683    2013-06-27  Draft Enact


******************************************************************************/

#ifndef __IMSANVINTERFACE_H__
#define __IMSANVINTERFACE_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/

#include    "vos.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    设置字节对齐方式
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#define IMSA_PASSWORD_LEN               (129)
#define IMSA_IMPI_LEN                   (129)
#define IMSA_IMPU_LEN                   (129)
#define IMSA_HOME_NET_DOMAIN_NAME_LEN   (129)

#define IMSA_IMS_MAX_REDIAL_CAUSE_NUM   (16)

#define IMSA_NV_IPV4_ADDR_LEN           (4)
#define IMSA_NV_IPV6_ADDR_LEN           (16)

#define IMSA_NV_PLMN_LIST_LEN           (128)
#define IMSA_NV_PLMN_LEN                (3)

#define IMSA_NV_MAX_TEMP_PDN_SINGLE_CAUSE_NUM   (35)
#define IMSA_NV_MAX_PERM_PDN_SINGLE_CAUSE_NUM   (11)
#define IMSA_NV_MAX_TEMP_REG_SINGLE_CAUSE_NUM   (55)
#define IMSA_NV_MAX_PERM_REG_SINGLE_CAUSE_NUM   (11)

#define IMSA_NV_MAX_NON_REG_SINGLE_CAUSE_NUM    (11)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
enum IMSA_PCSCF_DISCOVERY_POLICY_ENUM
{
    IMSA_PCSCF_DISCOVERY_POLICY_PCO           = 0,      /**< PCO方式获取P-CSCF */
    IMSA_PCSCF_DISCOVERY_POLICY_NV            = 1,      /**< NV配置P-CSCF */
    IMSA_PCSCF_DISCOVERY_POLICY_BUTT
};
typedef VOS_UINT8 IMSA_PCSCF_DISCOVERY_POLICY_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucWifiImsSupportFlag;    /**< WIFI IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUtranImsSupportFlag; /**< UNTRAN IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucLteImsSupportFlag;    /**< LTE IMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucWifiEmsSupportFlag;    /**< WIFI EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUtranEmsSupportFlag; /**< UNTRAN EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucLteEmsSupportFlag;    /**< LTE EMS使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucRoamingImsNotSupportFlag; /**< 漫游网络下不允许IMS注册使能项，VOS_TRUE:支持 VOS_FALSE:不支持 */
    VOS_UINT8                           aucReserved1;           /*保留字段*/
}IMSA_NV_IMS_RAT_SUPPORT_STRU;

/*jiaguocai for IMS support flag,begin 2016-10-11*/
typedef struct
{
    VOS_UINT8                           ucImsSupportFlag;    /**< IMS总开关,VOS_TRUE :IMS 总开关打开；VOS_FALSE:IMS总开关关闭，默认应该设置为VOS_TRUE*/
    VOS_UINT8                           aucReserved[3];
}IMSA_NV_IMS_CTRL_STRU;
/*jiaguocai for IMS support flag,end 2016-10-11*/



typedef struct
{
    VOS_UINT16                          usImsMinPort;           /* IMS端口号范围下限 */
    VOS_UINT16                          usImsMaxPort;           /* IMS端口号范围上限 */

}IMSA_NV_SIP_PORT_CONFIG_STRU;

typedef struct
{
    VOS_UINT8                           ucIsCallRedialSupportFlg;   /* 是否支持IMS域内重播功能，VOS_TRUE:支持；VOS_FALSE:不支持*/
    VOS_UINT8                           ucRedialCauseNum;           /* 重播原因值个数 */
    VOS_UINT8                           aucReserved1[2];
    VOS_UINT32                          ulCallRedialMaxTime;        /* IMS域内重播功能打开时，重播最大时长，单位毫秒 */
    VOS_UINT32                          ulCallRedialInterval;       /* IMS域内重播功能打开时，重拨间隔，单位毫秒 */
    VOS_UINT32                          ulCallRedialMaxNum;         /* IMS域内重播功能打开时，重播最大次数  */
    VOS_UINT16                          ausRedialCauseList[IMSA_IMS_MAX_REDIAL_CAUSE_NUM];       /* 重播原因值列表 */
}IMSA_NV_IMS_REDIAL_CFG_STRU;

typedef struct
{
    VOS_UINT8                           ucCMCCCustomDeregFlag;    /**< 中国移动定制需求, 条件满足时去注册使能项*/
    VOS_UINT8                           ucCMCCCustomTcallFlag;    /**< 中国移动定制需求, Tcall SilentRedial使能项*/
    VOS_UINT8                           ucCMCCCustomTqosFlag;     /**< 中国移动定制需求, Tqos SilentRedial使能项*/
    VOS_UINT8                           aucReserved[1];

    VOS_UINT32                          ulTcallTimerLen;            /**< 中国移动定制需求, Tcall timer定时器时长, 单位为ms*/
    VOS_UINT32                          ulTqosTimerLen;             /**< 中国移动定制需求, Tqos timer定时器时长, 单位为ms*/
} IMSA_NV_CMCC_CUSTOM_REQ_STRU;

typedef struct
{
    VOS_UINT8                           ucNoCardEmcCallSupportFlag;/**< 无卡紧急呼使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucUeRelMediaPdpFLag;    /**< UE主动释放媒体承载标识 */
    VOS_UINT8                           ucImsLocDeregSigPdpRelFlag;/**< IMS普通信令被动释放后本地IMS去注册标识 */
    VOS_UINT8                           ucRetryTimes;              /**< IMS注册失败再尝试注册次数，0为默认值，为无限次 */
    VOS_UINT32                          ulMaxTime;              /**< max time，单位为s */
    VOS_UINT32                          ulBaseTime;             /**< base time，单位为s */
    VOS_UINT32                          ulRegFailRetryIntervel; /**< 注册失败重试间隔，单位为s，0表示非固定间隔 */
    VOS_UINT32                          ulRegTimerLen;
    IMSA_NV_IMS_REDIAL_CFG_STRU         stImsRedialCfg;         /**< IMS域内重播配置 */
    IMSA_NV_CMCC_CUSTOM_REQ_STRU        stCMCCCustomReq;        /**< 中国移动定制需求 */
}IMSA_NV_IMSA_CONFIG_STRU;

/*****************************************************************************
结构名称    :IMSA_NV_VISP_WAKEUP_COMPENS_TIMER_CTRL_STRU
使用说明    :IMSA控制VISP唤醒定时器补偿流程的NV结构
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucVispWakeupCompenTimerFlag;   /* VISP定时器补偿特性方案控制开关 */
    VOS_UINT8                           ucVispWakeupCompenDrxNum;      /* VISP定时器补偿方案，定时器时长: 基准时间的倍数 */
    VOS_UINT8                           aucRsv1;
    VOS_UINT8                           aucRsv2;
}IMSA_NV_VISP_WAKEUP_COMPENS_TIMER_CTRL_STRU;


typedef struct
{
    VOS_UINT8                           ucVoiceCallOnImsSupportFlag;        /**< IMS语音使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucVideoCallOnImsSupportFlag;        /**< IMS视频使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSmsOnImsSupportFlag;              /**< IMS短信使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSrvccOnImsSupportFlag;            /**< IMS Srvcc使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSrvccMidCallOnImsSupportFlag;     /**< IMS SrvccMidCall使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSrvccAlertingOnImsSupportFlag;    /**< IMS SrvccAlerting使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSrvccPreAlertingOnImsSupportFlag; /**< IMS SrvccPreAlerting使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucSrvccTiFlag;                      /**< IMS SrvccPreAlerting,VOS_TRUE :0 R10版本,VOS_FALSE R11之后版本 */
}IMS_NV_IMS_CAP_STRU;


typedef struct
{
    VOS_UINT8                           ucUserInfoFlag;   /**< 0:从USIM读IMPI，IMPU,DOMAIN   1:从NV读取IMPI，IMPU,DOMAIN */
    VOS_UINT8                           ucAuthType;                         /**< IMS 鉴权方式  0:AKA  1:DIGIST 2:AKA_IPSEC */
    VOS_UINT8                           aucReserved[2];
    VOS_INT8                            acImpi[IMSA_IMPI_LEN]; /**< 默认49字节 */
    VOS_INT8                            acTImpu[IMSA_IMPU_LEN]; /**< 默认53字节 */
    VOS_INT8                            acHomeNetDomainName[IMSA_HOME_NET_DOMAIN_NAME_LEN]; /**< 默认33字节 */
    VOS_INT8                            aucPassWord[IMSA_PASSWORD_LEN];     /**< 鉴权方式为DIGIST时:设置密码 */
}IMSA_NV_IMS_CONFIG_STRU;

typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1; /**< 如果bitOpSecPcscfAddr为1，bitOpPrimPcscfAddr也必须为1*/
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimPcscfAddr[IMSA_NV_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[IMSA_NV_IPV4_ADDR_LEN];
} IMSA_NV_PDP_IPV4_PCSCF_STRU;

typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1; /**< 如果bitOpSecPcscfAddr为1，bitOpPrimPcscfAddr也必须为1*/
    VOS_UINT32                          bitOpSpare          : 30;

    VOS_UINT8                           aucPrimPcscfAddr[IMSA_NV_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[IMSA_NV_IPV6_ADDR_LEN];
} IMSA_NV_PDP_IPV6_PCSCF_STRU;


typedef struct
{
    IMSA_PCSCF_DISCOVERY_POLICY_ENUM_UINT8  enPcscfDiscoverPolicy;  /**< P-CSCF获取策略 */
    VOS_UINT8                               aucReserved[3];
    IMSA_NV_PDP_IPV4_PCSCF_STRU             stIpv4Pcscf;            /**< 承载IPv4 P-CSCF信息 */
    IMSA_NV_PDP_IPV6_PCSCF_STRU             stIpv6Pcscf;            /**< 承载IPv6 P-CSCF信息 */
}IMSA_NV_PCSCF_DISCOVERY_POLICY_STRU;

/*****************************************************************************
结构名称    :IMSA_NV_PLMN_ID_STRU中
使用说明    :
    MCC, Mobile country code (aucPlmnId[0], aucPlmnId[1] bits 1 to 4)
    MNC, Mobile network code (aucPlmnId[2], aucPlmnId[1] bits 5 to 8).

    The coding of this field is the responsibility of each administration but BCD
    coding shall be used. The MNC shall consist of 2 or 3 digits. For PCS 1900 for NA,
    Federal regulation mandates that a 3-digit MNC shall be used. However a network
    operator may decide to use only two digits in the MNC over the radio interface.
    In this case, bits 5 to 8 of octet 4 shall be coded as "1111". Mobile equipment
    shall accept MNC coded in such a way.

    ---------------------------------------------------------------------------
                 ||(BIT8)|(BIT7)|(BIT6)|(BIT5)|(BIT4)|(BIT3)|(BIT2)|(BIT1)
    ---------------------------------------------------------------------------
    aucPlmnId[0] ||    MCC digit 2            |           MCC digit 1
    ---------------------------------------------------------------------------
    aucPlmnId[1] ||    MNC digit 3            |           MCC digit 3
    ---------------------------------------------------------------------------
    aucPlmnId[2] ||    MNC digit 2            |           MNC digit 1
    ---------------------------------------------------------------------------
    e.g.
    PLMN 460 10 转为为 0x64 0xF0 0x01
    PLMN 123 01 转为为 0x21 0xF3 0x10
    PLMN 123 456转为为 0x21 0x63 0x54

*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucPlmnId[IMSA_NV_PLMN_LEN];
    VOS_UINT8                           ucRsv;
}IMSA_NV_PLMN_ID_STRU;

typedef struct
{
    VOS_UINT8                           ucEnableCardLockFlag;       /**< 是否打开锁卡功能，0关闭，1打开 */
    VOS_UINT8                           ucPlmnNum;                  /**< 支持的PLMN列表长度 */
    VOS_UINT8                           ucReserved1;
    VOS_UINT8                           ucReserved2;
    IMSA_NV_PLMN_ID_STRU                astPlmnList[IMSA_NV_PLMN_LIST_LEN]; /**< 支持的PLMN列表 */
}IMSA_NV_CARD_LOCK_STRU;

typedef struct
{
    VOS_UINT8                           ucSingleCauseNum;
    VOS_UINT8                           aucSingleCauseList[IMSA_NV_MAX_PERM_PDN_SINGLE_CAUSE_NUM];
}IMSA_NV_PDN_PERM_REJ_CAUSE_LIST_STRU;

typedef struct
{
    VOS_UINT8                           ucSingleCauseNum;
    VOS_UINT8                           aucSingleCauseList[IMSA_NV_MAX_TEMP_PDN_SINGLE_CAUSE_NUM];
}IMSA_NV_PDN_TEMP_REJ_CAUSE_LIST_STRU;


typedef struct
{
    VOS_UINT8                           ucSingleCauseNum;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          ausSingleCauseList[IMSA_NV_MAX_PERM_REG_SINGLE_CAUSE_NUM];
}IMSA_NV_REG_PERM_REJ_CAUSE_LIST_STRU;

typedef struct
{
    VOS_UINT8                           ucSingleCauseNum;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          ausSingleCauseList[IMSA_NV_MAX_TEMP_REG_SINGLE_CAUSE_NUM];
}IMSA_NV_REG_TEMP_REJ_CAUSE_LIST_STRU;

typedef struct
{
    VOS_UINT8                           ucSingleCauseNum;
    VOS_UINT8                           ucRsv;
    VOS_UINT16                          ausSingleCauseList[IMSA_NV_MAX_NON_REG_SINGLE_CAUSE_NUM];
}IMSA_NV_NON_REG_REJ_CAUSE_LIST_STRU;


typedef struct
{
    VOS_UINT32                          bitOpPdnTempForbFeatrueCtrl:1;     /* PDN临时被禁特性控制开关 */
    VOS_UINT32                          bitOpPdnPermForbFeatrueCtrl:1;     /* PDN永久被禁特性值控制开关 */
    VOS_UINT32                          bitOpRegTempForbFeatrueCtrl:1;     /* 注册临时被禁特性控制开关 */
    VOS_UINT32                          bitOpRegPermForbFeatrueCtrl:1;     /* 注册永久被禁特性值控制开关 */
    VOS_UINT32                          bitOpNonRegRejFeatrueCtrl  :1;     /* 注册永久被禁特性值控制开关 */
    VOS_UINT32                          bitOpACBFlag               :1;     /* ACB Enabled时CSFB功能开关 */
    VOS_UINT32                          bitOpReadSipUriFromIsimFlag:1;     /* 从ISIM中读取SIP URI功能开关 */
    VOS_UINT32                          bitOpAreaLostNotRelCall     :1;     /* GUL丢网后，需要挂断电话功能开关 */
    VOS_UINT32                          bitOpMediaLostNotRelCall    :1;     /* 媒体承载丢失后，主动挂断电话开关 */
    VOS_UINT32                          bitOpNonSrvccNotRelCall     :1;
    VOS_UINT32                          bitOpIgnoreMediaBearerQci   :1;     /* 语言电话忽略媒体承载QCI值 */

    VOS_UINT32                          bitOpUeSmsCapInitRegFlag    :1;     /* 网侧不支持IMS语音，UE支持IMS短信时，发起注册的开关 */
    VOS_UINT32                          bitOpNwDeactiveReReg        :1;     /* 网侧去激活UE后，是否需要重新发起注册的开关 */
    VOS_UINT32                          bitOpNwRejReReg             :1;     /* 网侧发送notify，携带rejext时，是否需要重新发起注册的开关*/
	VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOpPoweroffDisconnectPdnFlag:1;  /* 关机释放PDN控制开关 */
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;
}IMSA_COMM_NV_BIT_STRU;

typedef struct
{
    IMSA_NV_PDN_TEMP_REJ_CAUSE_LIST_STRU    stPdnTempRejCauseList;  /* PDN临时被拒原因值列表 */
    IMSA_NV_PDN_PERM_REJ_CAUSE_LIST_STRU    stPdnPermRejCauseList;  /* PDN永久被拒原因值列表 */
    IMSA_NV_REG_TEMP_REJ_CAUSE_LIST_STRU    stRegTempRejCauseList;  /* 注册临时被拒原因值列表 */
    IMSA_NV_REG_PERM_REJ_CAUSE_LIST_STRU    stRegPermRejCauseList;  /* 注册永久被拒原因值列表 */

    IMSA_NV_NON_REG_REJ_CAUSE_LIST_STRU     stNonRegRejCauseList;   /* 非注册被拒原因值列表 */

    IMSA_COMM_NV_BIT_STRU                   stImsaCtrlBit;          /* Bit位, 用于控制开关 */

    VOS_UINT8                           ucHifiDataControlFlag; /*是否支持HIFI限流：TRUE:支持；FALSE：不支持 */
    VOS_UINT8                           ucHifiDataNeedAckNum;  /*HIFI限流功能，需要每多少条回复一次ack */
    VOS_UINT8                           ucHifiDatMaxBufferNum; /*HIFI限流功能，IMSA缓存的消息数 */
    VOS_UINT8                           ucTempForbExpDelayTimeLen;/* PDN临时被拒定时器偏移时间 */

    VOS_UINT8                           ucUseRetryAfterAsDelayTimeFlag; /*是否不经过计算直接使用RetryAfter当做等待定时器时长*/
    VOS_UINT8                           ucWaitIpv6PrefixTimerLen;  /* 等待IPV6地址前缀定时器时长 */
    VOS_UINT8                           ucVoiceCapNotifyTimerLen;
    VOS_UINT8                           ucRsv5;

    VOS_UINT8                           ucRsv6;
    VOS_UINT8                           ucRsv7;
    VOS_UINT8                           ucRsv8;
    VOS_UINT8                           ucRsv9;

    VOS_UINT8                           ucRsv10;
    VOS_UINT8                           ucRsv11;
    VOS_UINT8                           ucRsv12;
    VOS_UINT8                           ucRsv13;

    VOS_UINT8                           ucRsv14;
    VOS_UINT8                           ucRsv15;
    VOS_UINT8                           ucRsv16;
    VOS_UINT8                           ucRsv17;

    VOS_UINT8                           ucRsv18;
    VOS_UINT8                           ucRsv19;
    VOS_UINT8                           ucRsv20;
    VOS_UINT8                           ucRsv21;

    VOS_UINT8                           ucRsv22;
    VOS_UINT8                           ucRsv23;
    VOS_UINT8                           ucRsv24;
    VOS_UINT8                           ucRsv25;

    VOS_UINT8                           ucRsv26;
    VOS_UINT8                           ucRsv27;
    VOS_UINT8                           ucRsv28;
    VOS_UINT8                           ucRsv29;

    VOS_UINT16                          usSmsTr1mTimerLen;
    VOS_UINT16                          usSmsTr2mTimerLen;

    VOS_UINT16                          usSmsTramTimerLen;
    VOS_UINT16                          usNormMediaLostRelCallTimerLen;

    VOS_UINT16                          usEmcMediaLostRelCallTimerLen;

    VOS_UINT16                          usVideoMediaLostMdyCallTimerLen;

    VOS_UINT16                          usNwDeactReRegTimerLen;
    VOS_UINT16                          usRsv8;

    VOS_UINT16                          usRsv9;
    VOS_UINT16                          usRsv10;

    VOS_UINT16                          usRsv11;
    VOS_UINT16                          usRsv12;

    VOS_UINT16                          usRsv13;
    VOS_UINT16                          usRsv14;

    VOS_UINT16                          usRsv15;
    VOS_UINT16                          usRsv16;

    VOS_UINT16                          usRsv17;
    VOS_UINT16                          usRsv18;

    VOS_UINT16                          usRsv19;
    VOS_UINT16                          usRsv20;

    VOS_UINT16                          usRsv21;
    VOS_UINT16                          usRsv22;

    VOS_UINT16                          usRsv23;
    VOS_UINT16                          usRsv24;

    VOS_UINT16                          usRsv25;
    VOS_UINT16                          usRsv26;

    VOS_UINT16                          usRsv27;
    VOS_UINT16                          usRsv28;

    VOS_UINT16                          usRsv29;
    VOS_UINT16                          usRsv30;

    VOS_UINT16                          usRsv31;
    VOS_UINT16                          usRsv32;

    VOS_UINT32                          ulPdnConnTimeThreshold;
    VOS_UINT32                          ulRegTimeThreshold;

    VOS_UINT32                          ulMtuLength;

    VOS_UINT32                          ulRsv4;

    VOS_UINT32                          ulRsv5;
    VOS_UINT32                          ulRsv6;

    VOS_UINT32                          ulRsv7;
    VOS_UINT32                          ulRsv8;

    VOS_UINT32                          ulRsv9;
    VOS_UINT32                          ulRsv10;

    VOS_UINT32                          ulRsv11;
    VOS_UINT32                          ulRsv12;

    VOS_UINT32                          ulRsv13;
    VOS_UINT32                          ulRsv14;

    VOS_UINT32                          ulRsv15;
    VOS_UINT32                          ulRsv16;

    VOS_UINT32                          ulRsv17;
    VOS_UINT32                          ulRsv18;

    VOS_UINT32                          ulRsv19;
    VOS_UINT32                          ulRsv20;

    VOS_UINT32                          ulRsv21;
    VOS_UINT32                          ulRsv22;

    VOS_UINT32                          ulRsv23;
    VOS_UINT32                          ulRsv24;
} IMSA_COMM_PARA_CONFIG_STRU;



typedef struct
{
    VOS_UINT32                          bitOpActCause0:1;                               /* WIFI_IMSA_PDN_ACT_RESULT_SUCCESS */
    VOS_UINT32                          bitOpActCause1ParamError:1;                     /* WIFI_IMSA_PDN_ACT_RESULT_PARAM_ERR */
    VOS_UINT32                          bitOpActCause2LinkLost:1;                       /* WIFI_IMSA_PDN_ACT_RESULT_LINKLOST */
    VOS_UINT32                          bitOpActCause3TimerOut:1;                       /* WIFI_IMSA_PDN_ACT_RESULT_TIMEOUT */
    VOS_UINT32                          bitOpActCause4MapconStateError:1;               /* WIFI_IMSA_PDN_ACT_RESULT_MAPCON_STATE_ERR */
    VOS_UINT32                          bitOpActCause5OtherFailure  :1;                 /* WIFI_IMSA_PDN_ACT_RESULT_OTHER_FAILURE */
    VOS_UINT32                          bitOpActCause6SimAuthNoResp:1;                  /* WIFI_IMSA_PDN_ACT_RESULT_SIM_AUTH_NO_RESP */
    VOS_UINT32                          bitOpActCause7AuthNetworkError     :1;          /*WIFI_IMSA_PDN_ACT_RESULT_AUTH_NETWORK_ERROR */
    VOS_UINT32                          bitOpActCause8ParseNetworkPayloadError  :1;     /* WIFI_IMSA_PDN_ACT_RESULT_PARSE_NETWORK_PAYLOAD_ERROR */
    VOS_UINT32                          bitOpActCause9AddSaApError     :1;              /*WIFI_IMSA_PDN_ACT_RESULT_ADD_SA_AP_ERROR */
    VOS_UINT32                          bitOpActCause10ClientPayloadError     :1;       /*WIFI_IMSA_PDN_ACT_RESULT_CLIENT_PAYLOAD_ERROR */
    VOS_UINT32                          bitOpActCause11MsgNetworkOvertimeError :1;      /* WIFI_IMSA_PDN_ACT_RESULT_MSG_NETWORK_OVERTIME_ERROR */
    VOS_UINT32                          bitOpActCause12EncAlgError    :1;               /* WIFI_IMSA_PDN_ACT_RESULT_ENC_ALG_ERROR */
    VOS_UINT32                          bitOpActCause13ApnIdError    :1;                /* WIFI_IMSA_PDN_ACT_RESULT_APN_ID_ERROR */
    VOS_UINT32                          bitOpActCause14NetworkAuthSimError   :1;        /* WIFI_IMSA_PDN_ACT_RESULT_NETWORK_AUTH_SIM_ERROR */
    VOS_UINT32                          bitOpActCause15StatusError       :1;            /* WIFI_IMSA_PDN_ACT_RESULT_STATUS_ERROR */
    VOS_UINT32                          bitOpActCause16SaInitError:1;                   /* WIFI_IMSA_PDN_ACT_RESULT_SA_INIT_ERROR */
    VOS_UINT32                          bitOpActCause17Non3gppAccessToEpcNotAllowed:1;  /* WIFI_IMSA_PDN_ACT_RESULT_NON_3GPP_ACCESS_TO_EPC_NOT_ALLOWED */
    VOS_UINT32                          bitOpActCause18UserUnknown:1;                   /* WIFI_IMSA_PDN_ACT_RESULT_USER_UNKNOWN */
    VOS_UINT32                          bitOpActCause19PlmnNotAllowed:1;                /* WIFI_IMSA_PDN_ACT_RESULT_PLMN_NOT_ALLOWED */
    VOS_UINT32                          bitOpActCause20AuthorizationRejected:1;         /* WIFI_IMSA_PDN_ACT_RESULT_AUTHORIZATION_REJECTED */
    VOS_UINT32                          bitOpActCause21RatTypeNotAllowed:1;             /* WIFI_IMSA_PDN_ACT_RESULT_RAT_TYPE_NOT_ALLOWED */
    VOS_UINT32                          bitOpActCause22NetworkFailure:1;                /* WIFI_IMSA_PDN_ACT_RESULT_NETWORK_FAILURE */
    VOS_UINT32                          bitOpActCause23NoApnSubscription:1;             /* WIFI_IMSA_PDN_ACT_RESULT_NO_APN_SUBSCRIPTION */
    VOS_UINT32                          bitOpActCause24PdnConnectionRejection:1;        /* WIFI_IMSA_PDN_ACT_RESULT_PDN_CONNECTION_REJECTION */
    VOS_UINT32                          bitOpActCause25PdnConnectionReached:1;          /* WIFI_IMSA_PDN_ACT_RESULT_CONNECTION_REACHED */
    VOS_UINT32                          bitOpActCause26ProtecleError:1;                 /* WIFI_IMSA_PDN_ACT_RESULT_PROTECLE_ERROR */
    VOS_UINT32                          bitOpActCause27:1;
    VOS_UINT32                          bitOpActCause28:1;
    VOS_UINT32                          bitOpActCause29:1;
    VOS_UINT32                          bitOpActCause30:1;
    VOS_UINT32                          bitOpActCause31:1;
}IMSA_WIFI_PDN_ACT_CAUSE_NV_BIT_STRU1;

typedef struct
{
    VOS_UINT32                          bitOpActCause32:1;
    VOS_UINT32                          bitOpActCause33:1;
    VOS_UINT32                          bitOpActCause34:1;     
    VOS_UINT32                          bitOpActCause35:1;    
    VOS_UINT32                          bitOpActCause36:1;   
    VOS_UINT32                          bitOpActCause37:1; 
    VOS_UINT32                          bitOpActCause38:1; 
    VOS_UINT32                          bitOpActCause39:1;    
    VOS_UINT32                          bitOpActCause40:1;  
    VOS_UINT32                          bitOpActCause41:1;   
    VOS_UINT32                          bitOpActCause42:1;
    VOS_UINT32                          bitOpActCause43:1;  
    VOS_UINT32                          bitOpActCause44:1; 
    VOS_UINT32                          bitOpActCause45:1; 
    VOS_UINT32                          bitOpActCause46:1; 
    VOS_UINT32                          bitOpActCause47:1;                    
    VOS_UINT32                          bitOpActCause48:1;              
    VOS_UINT32                          bitOpActCause49:1;           
    VOS_UINT32                          bitOpActCause50RoamForbid:1;                   /* WIFI_IMSA_PDN_ACT_RESULT_ROAM_FORBID */
    VOS_UINT32                          bitOpActCause51HifiStatusOvertime:1;           /* WIFI_IMSA_PDN_ACT_RESULT_HIFI_STATUS_OVERTIME */
    VOS_UINT32                          bitOpActCause52:1;
    VOS_UINT32                          bitOpActCause53:1; 
    VOS_UINT32                          bitOpActCause54:1; 
    VOS_UINT32                          bitOpActCause55:1; 
    VOS_UINT32                          bitOpActCause56:1; 
    VOS_UINT32                          bitOpActCause57:1; 
    VOS_UINT32                          bitOpActCause58:1;
    VOS_UINT32                          bitOpActCause59:1;
    VOS_UINT32                          bitOpActCause60:1;
    VOS_UINT32                          bitOpActCause61:1;
    VOS_UINT32                          bitOpActCause62:1;
    VOS_UINT32                          bitOpActCause63:1;
}IMSA_WIFI_PDN_ACT_CAUSE_NV_BIT_STRU2;


typedef struct
{
    VOS_UINT32                          bitOpActCause64:1;
    VOS_UINT32                          bitOpActCause65:1;
    VOS_UINT32                          bitOpActCause66:1;     
    VOS_UINT32                          bitOpActCause67:1;    
    VOS_UINT32                          bitOpActCause68:1;   
    VOS_UINT32                          bitOpActCause69:1; 
    VOS_UINT32                          bitOpActCause70:1; 
    VOS_UINT32                          bitOpActCause71:1;    
    VOS_UINT32                          bitOpActCause72:1;  
    VOS_UINT32                          bitOpActCause73:1;   
    VOS_UINT32                          bitOpActCause74:1;
    VOS_UINT32                          bitOpActCause75:1;  
    VOS_UINT32                          bitOpActCause76:1; 
    VOS_UINT32                          bitOpActCause77:1; 
    VOS_UINT32                          bitOpActCause78:1; 
    VOS_UINT32                          bitOpActCause79:1;                    
    VOS_UINT32                          bitOpActCause80:1;              
    VOS_UINT32                          bitOpActCause81:1;           
    VOS_UINT32                          bitOpActCause82:1; 
    VOS_UINT32                          bitOpActCause83:1; 
    VOS_UINT32                          bitOpActCause84:1;
    VOS_UINT32                          bitOpActCause85:1; 
    VOS_UINT32                          bitOpActCause86:1; 
    VOS_UINT32                          bitOpActCause87:1; 
    VOS_UINT32                          bitOpActCause88:1; 
    VOS_UINT32                          bitOpActCause89:1; 
    VOS_UINT32                          bitOpActCause90:1;
    VOS_UINT32                          bitOpActCause91:1;
    VOS_UINT32                          bitOpActCause92:1;
    VOS_UINT32                          bitOpActCause93:1;
    VOS_UINT32                          bitOpActCause94:1;
    VOS_UINT32                          bitOpActCause95:1;
}IMSA_WIFI_PDN_ACT_CAUSE_NV_BIT_STRU3;



typedef struct
{
    VOS_UINT32                          bitOpWifiPdnRejCauseFlag:1;        /* 指定WIFI PDN被拒异常原因值定制处理开关 */
    VOS_UINT32                          bitOpPermForbOrLongRetryFlag:1;     /* PDN永久被禁或者长时被拒开关: 0 永久被拒，1 长时被拒 */
    VOS_UINT32                          bitOp03:1;
    VOS_UINT32                          bitOp04:1;
    VOS_UINT32                          bitOp05:1; 
    VOS_UINT32                          bitOp06:1;
    VOS_UINT32                          bitOp07:1;
    VOS_UINT32                          bitOp08:1;
    VOS_UINT32                          bitOp09:1;
    VOS_UINT32                          bitOp10:1;
    VOS_UINT32                          bitOp11:1;
    VOS_UINT32                          bitOp12:1;
    VOS_UINT32                          bitOp13:1;
    VOS_UINT32                          bitOp14:1;
    VOS_UINT32                          bitOp15:1;
    VOS_UINT32                          bitOp16:1;
    VOS_UINT32                          bitOp17:1;
    VOS_UINT32                          bitOp18:1;
    VOS_UINT32                          bitOp19:1;
    VOS_UINT32                          bitOp20:1;
    VOS_UINT32                          bitOp21:1;
    VOS_UINT32                          bitOp22:1;
    VOS_UINT32                          bitOp23:1;
    VOS_UINT32                          bitOp24:1;
    VOS_UINT32                          bitOp25:1;
    VOS_UINT32                          bitOp26:1;
    VOS_UINT32                          bitOp27:1;
    VOS_UINT32                          bitOp28:1;
    VOS_UINT32                          bitOp29:1;
    VOS_UINT32                          bitOp30:1;
    VOS_UINT32                          bitOp31:1;
    VOS_UINT32                          bitOp32:1;
}IMSA_WIFI_COMM_NV_BIT_STRU;




typedef struct
{
    VOS_UINT8                           ucHoSupportInNonActSrvFlag;     /*是否支持非业务态切换：TRUE:支持；FALSE：不支持 */
    VOS_UINT8                           ucW2LHoInActSrvFlag;            /*是否支持业务态VoWifi -> VoLTE: TRUE:支持；FALSE：不支持 */
    VOS_UINT8                           ucL2WHoInActSrvFlag;            /*是否支持业务态VoLTE -> VoWifi: TRUE:支持；FALSE：不支持 */
    VOS_UINT8                           ucHoSupportInUnstableSrvFlag;   /*非业务稳态是否支持切换: TRUE:支持；FALSE：不支持 */

    VOS_UINT8                           ucL2WHoDelayInrSRVCCFlag;       /* rSRVCC延迟到VoWifi切换: TRUE:支持；FALSE：不支持 */
    VOS_UINT8                           ucInitShortTempForbTimerLen;    /* 初始短周期临时被拒Timer的时长，单位为秒 */
    VOS_UINT8                           ucMaxShortTempForbTimerLen;     /* 最大短周期临时被拒Timer的时长, 单位为分钟 */
    VOS_UINT8                           ucTimer3HoAliveLen;             /* 切换保护定时器时长,单位为秒,最长为60秒 */

    VOS_UINT8                           ucEmcApnOption;                 /* WIFI EMC使用APN: 0 IMS APN; 1 emergency APN */
    VOS_UINT8                           ucVolteCtrlVowifiFlag;          /**< 网络不支持VOLTE即不支持VOWIFI使能项,VOS_TRUE :支持，VOS_FALSE :不支持 */
    VOS_UINT8                           ucEmcW2LHoSupportFlag;          /* EMC是否支持切换：TRUE:支持；FALSE：不支持 */
    VOS_UINT8                           ucLongForbRetryTimerLen;        /* 长周期永久被拒Timer的时长, 单位为小时 */

    VOS_UINT8                           ucInitLongTempForbTimerLen;     /* 初始长周期临时被拒Timer的时长，单位为分钟 */
    VOS_UINT8                           ucMaxLongTempForbTimerLen;      /* 最大长周期临时被拒Timer的时长, 单位为小时 */
    VOS_UINT8                           ucShortTempForbMaxRetryTimes;   /* 临时被拒短周期最大重试次数 */
    VOS_UINT8                           ucLongTempForbMaxRetryTimes;    /* 临时被拒长周期最大重试次数 */

    VOS_UINT16                          usRsv1;
    VOS_UINT16                          usHoPcscfChangeCallContinueFlag;/* 切换过程中pcscf地址变更时，存在呼叫时，是否需要立即去注册标志，VOS_TRUE:延迟去注册，VOS_FALSE:立即去注册*/


    VOS_UINT16                          usLtePdnNoPcscfHoFailFlag; /* WiFI到LTE切换过程中，承载中不带pcscf地址判决是否切换成功过: 0 切换成功，1切换失败 */
    VOS_UINT16                          usRsv4;

    VOS_UINT16                          usRsv5;
    VOS_UINT16                          usRsv6;

    IMSA_WIFI_PDN_ACT_CAUSE_NV_BIT_STRU1                          ulPdnPermForbidCauseList1;
    IMSA_WIFI_PDN_ACT_CAUSE_NV_BIT_STRU2                          ulPdnPermForbidCauseList2;

    IMSA_WIFI_PDN_ACT_CAUSE_NV_BIT_STRU3                          ulPdnPermForbidCauseList3;
    IMSA_WIFI_PDN_ACT_CAUSE_NV_BIT_STRU1                          ulPdnDirectRetryCauseList1;
    
    IMSA_WIFI_PDN_ACT_CAUSE_NV_BIT_STRU2                          ulPdnDirectRetryCauseList2;
    IMSA_WIFI_PDN_ACT_CAUSE_NV_BIT_STRU3                          ulPdnDirectRetryCauseList3;
    
    IMSA_WIFI_COMM_NV_BIT_STRU                                    stImsaWifiCtrlBit;
    VOS_UINT32                          ulRsv8;

    VOS_UINT32                          ulRsv9;
    VOS_UINT32                          ulRsv10;

    VOS_UINT32                          ulRsv11;
    VOS_UINT32                          ulRsv12;
} IMSA_VOWIFI_PARA_CONFIG_STRU;



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

#endif /* end of ImsaNvInterface.h */




