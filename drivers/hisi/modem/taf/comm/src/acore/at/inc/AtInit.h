

#ifndef __ATINIT_H__
#define __ATINIT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtCtx.h"
#include "AtInputProc.h"
#if (VOS_LINUX == VOS_OS_VER)
#if (defined(CONFIG_BALONG_SPE))
#include "mdrv_spe_wport.h"
#endif /* CONFIG_BALONG_SPE */
#else
#include "Linuxstub.h"
#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��ʱ϶�ȼ����궨�� */
#define AT_GAS_GRR_MULTISLOT_CLASS_MAX  (12)

#if (defined(CONFIG_BALONG_SPE))
/* ����SPE�˿ڲ��� */
/*lint -emacro({717}, AT_SET_SPE_PORT_ATTR_BYPASS_MODE)*/
#define AT_SET_SPE_PORT_ATTR_BYPASS_MODE(pstAttr,pstNetDev,ulTdNum,ulRdNum)\
            do\
            {\
                ((spe_wport_attr_t *)(pstAttr))->is_bypass_mode = 1;\
                ((spe_wport_attr_t *)(pstAttr))->is_ipf_port    = 1;\
                ((spe_wport_attr_t *)(pstAttr))->net_dev        = (pstNetDev);\
                ((spe_wport_attr_t *)(pstAttr))->td_depth       = (ulTdNum);\
                ((spe_wport_attr_t *)(pstAttr))->rd_depth       = (ulRdNum);\
            } while(0)
#endif


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
 ö����    : AT_GAS_HIGH_MULTISLOT_CLASS_ENUM
 ö��˵��  : High multislot class�ȼ�
 �޸���ʷ  :
 1.��    ��    : 2011��12��13��
   ��    ��    : C00173809
   �޸�����    : �½�ö������, for V7R1 GTL PhaseI
*****************************************************************************/
enum AT_GAS_HIGH_MULTISLOT_CLASS_ENUM
{
    AT_GAS_HIGH_MULTISLOT_CLASS_0,
    AT_GAS_HIGH_MULTISLOT_CLASS_1,
    AT_GAS_HIGH_MULTISLOT_CLASS_2,
    AT_GAS_HIGH_MULTISLOT_CLASS_3,

    AT_GAS_HIGH_MULTISLOT_CLASS_BUTT
};
typedef VOS_UINT8 AT_GAS_HIGH_MULTISLOT_CLASS_ENUM_UINT8;


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
 �ṹ��    : AT_NV_UE_CAPABILITY_STRU
 Э����  : ��
 �ṹ˵��  : �洢��NV�е�UE������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           aucReserved1[11];                       /* �����Ժ���չ */
    VOS_UINT8                           ucAsRelIndicator;                       /* Access Stratum Release Indicator             */

    VOS_UINT8                           ucHSDSCHSupport;                        /* �Ƿ�֧��enHSDSCHSupport�ı�־                */
    VOS_UINT8                           ucHSDSCHPhyCategory;                    /* ֧��HS-DSCH���������ͱ�־                  */

    VOS_UINT8                           ucMacEhsSupport;
    VOS_UINT8                           ucHSDSCHPhyCategoryExt;
    VOS_UINT8                           ucMultiCellSupport;                     /* �Ƿ�֧�� Multi cell support,���֧��MultiCell,Ex2���� */
    VOS_UINT8                           ucHSDSCHPhyCategoryExt2;                /* HS-DSCH physical layer category extension 2 */

    VOS_UINT8                           aucReserved2[17];                       /* �����Ժ���չ */

    VOS_UINT8                           ucHSDSCHPhyCategoryExt3;                /* HS-DSCH physical layer category extension 3 */
    VOS_UINT8                           ucDcMimoSupport;                        /* �Ƿ�֧��DC+MIMO */

    VOS_UINT8                           aucReserved3[3];                        /* �����Ժ���չ */

} AT_NV_UE_CAPABILITY_STRU;

/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-10, begin */
/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-10, end */


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID AT_ReadPlatformNV(VOS_VOID);
extern VOS_VOID AT_ReadClientConfigNV(VOS_VOID);

extern VOS_VOID AT_GetCpmsMtMem(
           MODEM_ID_ENUM_UINT16                enModemId,
           MN_MSG_MEM_STORE_ENUM_U8           *penSmMemStore
       );
extern AT_CGSMS_SEND_DOMAIN_ENUM_U8 AT_SendDomainNvimToProto(
    VOS_UINT32                           ulNvimSendDomain
    );
extern VOS_VOID AT_ReadSmsSendDomainNV(VOS_VOID);
extern VOS_VOID AT_ReadSmsMeStorageInfoNV(VOS_VOID);
extern VOS_VOID AT_ReadSmsClass0TailorNV(VOS_VOID);
extern VOS_VOID AT_ReadSmsNV(VOS_VOID);

/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */
/* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */

extern VOS_VOID  AT_ReadRoamCapaNV(VOS_VOID);
extern VOS_VOID AT_ReadSmsFilterCfgNv( VOS_VOID );
extern VOS_VOID  AT_ReadSystemAppConfigNV(VOS_VOID);

extern VOS_VOID AT_ReadAtDislogPwdNV(VOS_VOID);
extern VOS_VOID AT_ReadAtRightPasswordNV(VOS_VOID);
extern VOS_VOID AT_ReadAtDissdPwdNV(VOS_VOID);
extern VOS_VOID AT_ReadNotSupportRetValueNV(VOS_VOID);
extern VOS_VOID AT_ReadE5NV(VOS_VOID);

extern VOS_UINT32 AT_IsAbortCmdCharValid(
    VOS_UINT8                          *pucAbortCmdChar,
    VOS_UINT32                          ulLen
    );
extern VOS_VOID AT_ReadAbortCmdParaNV(VOS_VOID);

extern VOS_VOID AT_ReadSysNV(VOS_VOID);

extern VOS_VOID AT_ReadCellSignReportCfgNV( VOS_VOID );

extern VOS_VOID AT_ReadPppDialErrCodeNV( VOS_VOID );
extern VOS_VOID AT_ReadReportRegActFlgNV( VOS_VOID );
extern VOS_VOID AT_ReadCregAndCgregCiFourByteRptNV( VOS_VOID );
#if (FEATURE_ON == FEATURE_IPV6)
extern VOS_VOID AT_ReadIpv6CapabilityNV( VOS_VOID );
extern VOS_VOID AT_ReadIpv6AddrTestModeCfgNV(VOS_VOID);
#endif
extern VOS_VOID AT_ReadDialConnectDisplayRateNV(VOS_VOID);

extern VOS_VOID  AT_ReadPsNV(VOS_VOID);
extern VOS_VOID  AT_ReadCsNV(VOS_VOID);

#if (FEATURE_ON == FEATURE_LTE)
extern VOS_VOID AT_ReadLTENV(VOS_VOID);
#endif

extern VOS_UINT32 AT_ValidateWasCategory(
           AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
       );
extern VOS_UINT32 AT_ValidateWasCategoryExt(
           AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
       );
extern VOS_UINT32 AT_ValidateWasCategoryExt2(
           AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
       );
extern VOS_UINT32 AT_ValidateWasCategoryExt3(
           AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
       );
extern VOS_UINT8 AT_GetWasDefaultCategory(
    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
    );
extern VOS_UINT8 AT_CalcWasCategory(
                                    AT_NV_UE_CAPABILITY_STRU           *pstUeCapability
                                    );

extern VOS_VOID AT_ReadWasCapabilityNV(VOS_VOID);
extern VOS_VOID AT_ReadGasCapabilityNV(VOS_VOID);

extern VOS_UINT32  AT_ReadPhyNV(VOS_VOID);
extern VOS_VOID AT_ReadAgpsNv(VOS_VOID);
extern VOS_VOID  AT_ReadNV(VOS_VOID);

extern VOS_VOID AT_InitDeviceCmd(VOS_VOID);

extern VOS_VOID AT_UsbSwitchGwMode(VOS_VOID);
extern VOS_VOID AT_InitPort(VOS_VOID);
extern VOS_VOID AT_InitStk(VOS_VOID);
extern VOS_VOID AT_InitPara(VOS_VOID);

#if (defined(CONFIG_BALONG_SPE))
VOS_VOID AT_SpeInit(VOS_VOID);
#endif

extern VOS_UINT32  At_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase);

VOS_VOID AT_ReadSsNV( VOS_VOID );

VOS_VOID AT_ReadUartCfgNV(VOS_VOID);

VOS_VOID AT_UsbEnableCB(VOS_VOID);

VOS_VOID AT_UsbDisableCB(VOS_VOID);

VOS_VOID AT_HsicEnableCB(VOS_VOID);

VOS_VOID AT_HsicDisableCB(VOS_VOID);

VOS_VOID AT_ReadPortBuffCfgNV(VOS_VOID);


VOS_VOID AT_WriteCcpuResetRecordNvim(VOS_UINT8 ucCcpuResetFlag);


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

#endif /* end of AtInit.h */

