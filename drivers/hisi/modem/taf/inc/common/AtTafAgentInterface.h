

#ifndef _ATTAFAGENTINTERFACE_H_
#define _ATTAFAGENTINTERFACE_H_

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafAgentInterface.h"

#pragma pack(4)

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_AGENT_FindCidForDial
 ��������  : ͨ��ͬ�����ƻ�ȡ���ڲ��ŵ�CID
 �������  : pCid    - CID
 �������  : ��
 �� �� ֵ  : VOS_OK  - �ɹ�
             VOS_ERR - ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 TAF_AGENT_FindCidForDial(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                          *pCid
);


/*****************************************************************************
 �� �� ��  : TAF_AGENT_SetPdpCidPara
 ��������  : ����ָ��CID�Ĳ���
 �������  : usClientId    - �ͻ���ID
             pstPdpPriPara - PDP�����Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_OK        - �ɹ�
             VOS_ERR       - ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 TAF_AGENT_SetPdpCidPara(
    MN_CLIENT_ID_T                      usClientId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
);


/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetPdpCidPara
 ��������  : ��ѯָ��CID�Ĳ���
 �������  : pstPdpPriPara - PDP�����Ĳ���
             ucCid         - CID
 �� �� ֵ  : VOS_OK        - �ɹ�
             VOS_ERR       - ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetPdpCidPara(
    TAF_PDP_PRIM_CONTEXT_STRU          *pstPdpPriPara,
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCid
);


/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetCallInfo
 ��������  : ��ȡͨ����Ϣͬ��API
 �������  : usClientId
             pucNumOfCalls
             pstCallInfos
 �������  : ��
 �� �� ֵ  : VOS_OK  - �ɹ�
             VOS_ERR - ʧ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetCallInfoReq(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                          *pucCallNum,
    TAFAGERNT_MN_CALL_INFO_STRU        *pstCallInfos
);


/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, begin */
VOS_UINT32 TAF_AGENT_GetSysMode(
    VOS_UINT16                                 usClientId,
    TAF_AGENT_SYS_MODE_STRU                   *pstSysMode
);
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, end */

extern VOS_VOID TAF_AGENT_ClearAllSem(VOS_VOID);

VOS_UINT32 TAF_AGENT_SetPdpCidQosPara(
    MN_CLIENT_ID_T                      usClientId,
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
);

VOS_UINT32 TAF_AGENT_GetPdpCidQosPara(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCid,
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara
);

VOS_UINT32 TAF_AGENT_GetAntState(
    VOS_UINT16                                 usClientId,
    VOS_UINT16                                *pusAntState
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

#endif

