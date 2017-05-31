

#ifndef __AT_COMMON_H__
#define __AT_COMMON_H__

#include "vos.h"


#ifdef __cplusplus
extern "C"
{
#endif

extern VOS_VOID* At_HeapAllocD(VOS_UINT32 ulSize);
extern VOS_VOID At_HeapFreeD(VOS_VOID *pAddr);

#define AT_MALLOC(ulSize)          At_HeapAllocD(ulSize)
#define AT_FREE(pAddr)             At_HeapFreeD(pAddr)


#define AT_DISABLE_CSIM                       (0)

typedef struct
{
    VOS_UINT32 ulEnableCSIM;
}NVIM_ENALBE_CSIM_STRU;


typedef struct
{
    VOS_UINT16      ucIndex;        /* ATͨ��ID */
    VOS_UINT16      aucRsv;
    VOS_UINT32      ulMsgId;        /* ԭ��ID */
    VOS_UINT16      aucData[4];     /* ԭ������ */
}TDS_AT_PS_MSG_INFO_STRU;


/*****************************************************************************
 Prototype       : TDS_PsAppSendMsg
 Description     : PS����APP�Ľӿڣ����ڴ�DSP����TDSά��ԭ��(ATʵ�֣�PS����)
 Input           : VOS_UINT32 ulLen ��Ϣ����(���ݳ��Ȳ�����48�ֽ�)
                   TDS_AT_PS_MSG_INFO_STRU * pstTdsAppPsMsg ��Ϣ����
 Output          : None.
 Return Value    : �ɹ�:0,ʧ��:����ֵ
 History         : ---
 *****************************************************************************/
extern VOS_UINT32 TDS_PsAtSendMsg(VOS_UINT32 ulLen, TDS_AT_PS_MSG_INFO_STRU * pstTdsAppPsMsg);
#ifdef __cplusplus
}
#endif


#endif /*__MSP_AT_H__*/

