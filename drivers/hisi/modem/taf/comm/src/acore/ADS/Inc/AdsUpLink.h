

#ifndef __ADSUPLINK_H__
#define __ADSUPLINK_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AdsIntraMsg.h"
#include "AdsCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/

/* ����BD��user field 1,�ڶ����ֽ�ΪModem id,��һ���ֽڵĸ�4λΪPktTpye,��һ���ֽڵĵ�4λΪRabId */
#define ADS_UL_BUILD_BD_USER_FIELD_1(Instance, RabId) \
        (((((VOS_UINT16)Instance) << 8) & 0xFF00) | ((ADS_UL_GET_QUEUE_PKT_TYPE(Instance, RabId) << 4) & 0xF0) | (RabId & 0x0F))

/* ��������ţ�Modem0��0��MODEM1��1��ʵ������ͬ */
#define ADS_UL_GET_BD_FC_HEAD(Instance)         (Instance)

/* ����������Ϣ:
           bit0:   int_en  �ж�ʹ��
           bit2:1  mode    ģʽ����
           bit3    rsv
           bit6:4  fc_head ��������� mfc_en������Ϊ1ʱ����Ч
           bit15:7 rsv */
#define ADS_UL_BUILD_BD_ATTRIBUTE(Flag, Mode, FcHead) ((Flag & 0x000F) | (Mode << 1 & 0x0006) | (FcHead << 4 &0x0070))

#define ADS_UL_SET_BD_ATTR_INT_FLAG(usAttr)            ((usAttr) = (usAttr) | 0x1)

#define ADS_UL_IPF_1XHRPD                   (IPF_1XHRPD_ULFC)

/*lint -emacro({717}, ADS_UL_SAVE_MODEMID_PKTTYEP_RABID_TO_IMM)*/
#define ADS_UL_SAVE_MODEMID_PKTTYEP_RABID_TO_IMM(pstImmZc, usModemId, ucPktType, ucRabId)\
            do\
            {\
                ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0] = (usModemId);\
                ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0] = ((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) << 8) | (ucPktType);\
                ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0] = ((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) << 8) | (ucRabId);\
            } while(0)

/*lint -emacro({717}, ADS_UL_SAVE_SLICE_TO_IMM)*/
#define ADS_UL_SAVE_SLICE_TO_IMM(pstImmZc, ulSlice)\
            do\
            {\
                ADS_IMM_MEM_CB(pstImmZc)->aulPriv[1] = (ulSlice);\
            } while(0)

/* ��IMM�л�ȡModemId */
#define ADS_UL_GET_MODEMID_FROM_IMM(pstImmZc)   ((VOS_UINT16)(((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) & 0xFFFF0000) >> 16))

/* ��IMM�л�ȡPktType */
#define ADS_UL_GET_PKTTYPE_FROM_IMM(pstImmZc)   ((VOS_UINT8)(((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) & 0x0000FF00) >> 8))

/* ��IMM�л�ȡRabId */
#define ADS_UL_GET_RABIID_FROM_IMM(pstImmZc)    ((VOS_UINT8)((ADS_IMM_MEM_CB(pstImmZc)->aulPriv[0]) & 0x000000FF))

/* ��IMM�л�ȡSlice */
#define ADS_UL_GET_SLICE_FROM_IMM(pstImmZc)     ((VOS_UINT32)ADS_IMM_MEM_CB(pstImmZc)->aulPriv[1])

/* �����ڴ�cache flush (map) */
/*lint -emacro({717}, ADS_IPF_UL_MEM_MAP)*/
#define ADS_IPF_UL_MEM_MAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_FALSE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemMapRequset(pstImmZc, ulLen, 1);\
                }\
            } while(0)

/* �����ڴ�cache flush (unmap) */
/*lint -emacro({717}, ADS_IPF_UL_MEM_UNMAP)*/
#define ADS_IPF_UL_MEM_UNMAP(pstImmZc, ulLen)\
            do\
            {\
                if (VOS_FALSE == ADS_IPF_IsSpeMem(pstImmZc))\
                {\
                    ADS_IPF_MemUnmapRequset(pstImmZc, ulLen, 1);\
                }\
            } while(0)


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID ADS_UL_ConfigBD(VOS_UINT32 ulBdNum);
IMM_ZC_STRU* ADS_UL_GetInstanceNextQueueNode(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                          *pucRabId,
    VOS_UINT8                          *puc1XorHrpdUlIpfFlag
);
IMM_ZC_STRU* ADS_UL_GetNextQueueNode(
    VOS_UINT8                          *pucRabId,
    VOS_UINT8                          *pucInstanceIndex,
    VOS_UINT8                          *puc1XorHrpdUlIpfFlag
);
VOS_VOID ADS_UL_ProcLinkData(VOS_VOID);
VOS_VOID ADS_UL_ProcMsg(MsgBlock* pMsg);
VOS_UINT32 ADS_UL_RcvTafMsg(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_RcvTafPdpStatusInd(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_ProcPdpStatusInd(
    ADS_PDP_STATUS_IND_STRU            *pstStatusInd
);
VOS_UINT32 ADS_UL_RcvCdsIpPacketMsg(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_RcvCdsMsg(MsgBlock *pMsg);
VOS_UINT32 ADS_UL_RcvTimerMsg(MsgBlock *pMsg);
VOS_VOID ADS_UL_SaveIpfSrcMem(const ADS_IPF_BD_BUFF_STRU *pstIpfUlBdBuff, VOS_UINT32 ulSaveNum);
VOS_VOID ADS_UL_FreeIpfSrcMem(VOS_VOID);
VOS_VOID ADS_UL_ClearIpfSrcMem(VOS_VOID);
VOS_UINT32 ADS_UL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
);
VOS_VOID ADS_UL_RcvTiDsFlowStatsExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
);
VOS_VOID ADS_UL_StartDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_StopDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
);
VOS_VOID ADS_UL_RcvTiDataStatExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
);
VOS_INT ADS_UL_CCpuResetCallback(
    DRV_RESET_CB_MOMENT_E               enParam,
    VOS_INT                             iUserData
);
VOS_VOID ADS_UL_RcvTiSendExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
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

#endif /* end of AdsUlProcData.h */
