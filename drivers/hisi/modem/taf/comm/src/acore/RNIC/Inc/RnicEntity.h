
#ifndef __RNIC_ENTITY_H__
#define __RNIC_ENTITY_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtRnicInterface.h"
#include "PsCommonDef.h"
#include "ImmInterface.h"
#include "AdsDeviceInterface.h"
#include "RnicLinuxInterface.h"
#include "RnicCtx.h"
#if (defined(CONFIG_BALONG_SPE) && (VOS_LINUX == VOS_OS_VER))
#include "mdrv_spe_wport.h"
#endif
#include "RnicDebug.h"
#include "RnicSndMsg.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*lint -e778 */
/*lint -e572 */
#ifndef VOS_NTOHL                   /* ��С�ֽ���ת��*/
#if VOS_BYTE_ORDER==VOS_BIG_ENDIAN
#define VOS_NTOHL(x)    (x)
#define VOS_HTONL(x)    (x)
#define VOS_NTOHS(x)    (x)
#define VOS_HTONS(x)    (x)
#else
#define VOS_NTOHL(x)    ((((x) & 0x000000ffU) << 24) | \
             (((x) & 0x0000ff00U) <<  8) | \
             (((x) & 0x00ff0000U) >>  8) | \
             (((x) & 0xff000000U) >> 24))

#define VOS_HTONL(x)    ((((x) & 0x000000ffU) << 24) | \
             (((x) & 0x0000ff00U) <<  8) | \
             (((x) & 0x00ff0000U) >>  8) | \
             (((x) & 0xff000000U) >> 24))

#define VOS_NTOHS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))

#define VOS_HTONS(x)    ((((x) & 0x00ff) << 8) | \
             (((x) & 0xff00) >> 8))
#endif  /* _BYTE_ORDER==_LITTLE_ENDIAN */
#endif
/*lint -e572 */
/*lint -e778 */

#define RNIC_NETIF_RX_NO_NI              (0)
#define RNIC_NETIF_RX_NI                 (1)

#if (defined(CONFIG_BALONG_SPE))
/* ����SPE�˿ڲ��� */
/*lint -emacro({717}, RNIC_SET_SPE_PORT_ATTR)*/
#define RNIC_SET_SPE_PORT_ATTR(pstAttr,pstNetDev,ulTdNum,ulRdNum)\
            do\
            {\
                ((spe_wport_attr_t *)(pstAttr))->is_bypass_mode = 0;\
                ((spe_wport_attr_t *)(pstAttr))->is_ipf_port    = 1;\
                ((spe_wport_attr_t *)(pstAttr))->net_dev        = (pstNetDev);\
                ((spe_wport_attr_t *)(pstAttr))->td_depth       = (ulTdNum);\
                ((spe_wport_attr_t *)(pstAttr))->rd_depth       = (ulRdNum);\
            } while(0)
#endif

#define RNIC_GET_MODEMID_FROM_EXRABID(ucExRabId) \
            (((VOS_UINT8)(ucExRabId) & (RNIC_RABID_TAKE_MODEM_1_MASK | RNIC_RABID_TAKE_MODEM_2_MASK)) >> 6)

#define RNIC_GET_RABID_FROM_EXRABID(ucExRabId) \
            ((VOS_UINT8)(ucExRabId) & RNIC_RABID_UNTAKE_MODEM_MASK)

#define RNIC_GET_RMNETID_FROM_EXPARAM(ulExParam)\
            ((VOS_UINT8)((ulExParam) & 0x000000FF))

#define RNIC_SET_NETIF_RX_TYPE(n)       (g_ucRnicNetifRxType = (n))
#define RNIC_GET_NETIF_RX_TYPE()        (g_ucRnicNetifRxType)

#define RNIC_SPE_CACHE_HDR_SIZE         (RNIC_MAC_HDR_LEN + RNIC_IPV4_HDR_LEN)

#if (defined(CONFIG_BALONG_SPE))
#define RNIC_SPE_MEM_CB(pstImmZc)       ((RNIC_SPE_MEM_CB_STRU *)&((pstImmZc)->dma))

/*lint -emacro({717}, RNIC_SPE_MEM_MAP)*/
#define RNIC_SPE_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == RNIC_IsSpeMem(pstImmZc))\
                {\
                    RNIC_SpeMemMapRequset(pstImmZc, ulLen);\
                }\
            } while(0)

/*lint -emacro({717}, RNIC_SPE_MEM_UNMAP)*/
#define RNIC_SPE_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_TRUE == RNIC_IsSpeMem(pstImmZc))\
                {\
                    RNIC_SpeMemUnmapRequset(pstImmZc, ulLen);\
                }\
            } while(0)
#else
#define RNIC_SPE_MEM_MAP(pstImmZc, ulLen)
#define RNIC_SPE_MEM_UNMAP(pstImmZc, ulLen)
#endif

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*********************************************
 ö����   :RNIC_RESULT_TYPE_ENUM
 ö��˵�� :RNIC��������ֵö������
 1.��    ��   : 2011��12��08��
   ��    ��   : f00179208
   �޸�����   : �½�
*********************************************/
enum RNIC_RESULT_TYPE_ENUM
{
    RNIC_OK             = 0,                                                    /* �������� */
    RNIC_NOTSTARTED     = 1,                                                    /* δ��ʼ */
    RNIC_INPROGRESS     = 2,                                                    /* ������ */
    RNIC_PERM           = 3,
    RNIC_NOENT          = 4,
    RNIC_IO             = 5,
    RNIC_NXIO           = 6,
    RNIC_NOMEM          = 7,                                                    /* δ���뵽�ڴ� */                                                    /* δ���뵽�ڴ� */
    RNIC_BUSY           = 8,                                                    /* RNIC�����豸æ */
    RNIC_NODEV          = 9,                                                    /* ���豸 */
    RNIC_INVAL          = 10,                                                   /* �Ƿ��豸 */
    RNIC_NOTSUPP        = 11,                                                   /* ������֧�� */
    RNIC_TIMEDOUT       = 12,                                                   /* ��ʱ */
    RNIC_SUSPENDED      = 13,                                                   /* ���� */
    RNIC_UNKNOWN        = 14,                                                   /* δ֪���� */
    RNIC_TEST_FAILED    = 15,                                                   /* ����ʧ�� */
    RNIC_STATE          = 16,                                                   /* ״̬���� */
    RNIC_STALLED        = 17,                                                   /* ʧ�� */
    RNIC_PARAM          = 18,                                                   /* �������� */
    RNIC_ABORTED        = 19,                                                   /* ����ȡ�� */
    RNIC_SHORT          = 20,                                                   /* ��Դ���� */
    RNIC_EXPIRED        = 21,                                                   /* ��� */

    RNIC_ADDR_INVALID   = 22,                                                   /* �޷������ַ */
    RNIC_OUT_RANGE      = 23,                                                   /* ������Ч��Χ�� */
    RNIC_PKT_TYPE_INVAL = 24,                                                   /* ��Чip���� */
    RNIC_ADDMAC_FAIL    = 25,                                                   /* ���macͷʧ�� */
    RNIC_RX_PKT_FAIL    = 26,                                                   /* �����ں˽ӿڽ�������ʧ�� */
    RNIC_ERROR          = 0xff,                                                 /* RNIC����ʧ�� */
    RNIC_BUTT
};
typedef VOS_INT32 RNIC_RESULT_TYPE_ENUM_INT32;

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
 �ṹ����  : RNIC_SPE_MEM_CB_STRU
 �ṹ˵��  : SPE MEM CB�ṹ
*****************************************************************************/
typedef struct
{
    dma_addr_t                          ulDmaAddr;

} RNIC_SPE_MEM_CB_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*lint -e762*/
extern int netif_rx(struct sk_buff *skb);
extern int netif_rx_ni(struct sk_buff *skb);
/*lint +e762*/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID RNIC_ProcVoWifiULData(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
);
#endif
VOS_VOID RNIC_SendULDataInPdpActive(
    IMM_ZC_STRU                        *pstImmZc,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt,
    VOS_UINT8                           ucRabId,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType
);
VOS_VOID RNIC_SendULIpv4Data(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
);
VOS_VOID RNIC_SendULIpv6Data(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
);

/* Modified by m00217266 for L-C��������Ŀ, 2014-01-06, Begin */
VOS_UINT32 RNIC_SendDlData(
    RNIC_RMNET_ID_ENUM_UINT8            enRmNetId,
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enPdpType
);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
VOS_UINT32 RNIC_RcvSdioDlData(
    VOS_UINT8                           ucPdnId,
    IMM_ZC_STRU                        *pstData
);
#endif

VOS_UINT32  RNIC_RcvAdsDlData(
    VOS_UINT8                           ucExRabid,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType,
    VOS_UINT32                          ucExParam
);
/* Modified by m00217266 for L-C��������Ŀ, 2014-01-06, End */

VOS_VOID RNIC_RcvInsideModemUlData(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
VOS_VOID RNIC_RcvOutsideModemUlData(
    struct sk_buff                     *pstSkb,
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt
);
#endif

VOS_UINT32 RNIC_NetRxData(
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType
);
VOS_VOID RNIC_ProcessTxDataByModemType(
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt,
    struct sk_buff                     *pstSkb
);
#if (defined(CONFIG_BALONG_SPE))
VOS_UINT32 RNIC_IsSpeMem(IMM_ZC_STRU *pstImmZc);
dma_addr_t RNIC_GetMemDma(IMM_ZC_STRU *pstImmZc);
VOS_VOID RNIC_SpeMemMapRequset(
    IMM_ZC_STRU                        *pstImmZc,
    VOS_UINT32                          ulLen
);
VOS_VOID RNIC_SpeMemUnmapRequset(
    IMM_ZC_STRU                        *pstImmZc,
    VOS_UINT32                          ulLen
);
VOS_VOID RNIC_SpeReadCB(VOS_INT32 lPort, struct sk_buff *pstSkb);
VOS_UINT32 RNIC_SpeRxData(
    RNIC_SPEC_CTX_STRU                 *pstNetCntxt,
    IMM_ZC_STRU                        *pstImmZc,
    ADS_PKT_TYPE_ENUM_UINT8             enPktType
);
VOS_VOID RNIC_SpeInit(VOS_VOID);
#endif



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
