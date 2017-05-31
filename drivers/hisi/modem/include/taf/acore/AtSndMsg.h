
#ifndef _AT_SND_MSG_H_
#define _AT_SND_MSG_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "AtRabmInterface.h"
#include "AtMnInterface.h"
#include "AtCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  1 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/


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
�ṹ��    : AT_IMS_CTRL_MSG_STRU
�ṹ˵��  : ATת��MAPCON��IMSA֮�����Ϣ
1.��    ��  : 2015��10��28��
  ��    ��  : n00269697
  �޸�����  :
*****************************************************************************/
typedef struct {
    VOS_UINT32                          ulMsgLen;                               /* message length */
    VOS_UINT8                           ucMsgContext[4];                        /* message context */
} AT_IMS_CTRL_MSG_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/*****************************************************************************
  10 ��������
*****************************************************************************/
VOS_UINT32  AT_FillAndSndAppReqMsg(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                            *pPara,
    VOS_UINT32                          ulParaLen,
    VOS_UINT32                          ulRcvPid
);

VOS_UINT32 AT_SndSetFastDorm (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    AT_RABM_FASTDORM_PARA_STRU         *pstFastDormPara
);
VOS_UINT32 AT_SndQryFastDorm (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

VOS_UINT32  AT_FillAppReqMsgHeader(
    MN_APP_REQ_MSG_STRU                *pMsg,
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    VOS_UINT16                          usMsgType,
    VOS_UINT32                          ulRcvPid
 );

VOS_UINT32 At_SndReleaseRrcReq (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
VOS_UINT32 AT_SndSetVoicePrefer (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT32                          ulVoicePreferApStatus
);
VOS_UINT32 AT_SndQryVoicePrefer (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
);
#endif

VOS_UINT32 AT_FillAndSndCSIMAMsg(VOS_UINT16 usClinetID,VOS_UINT32 ulModemStatus);
#if (FEATURE_ON == FEATURE_IMS)
VOS_UINT32 AT_SndImsaImsCtrlMsg (
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    AT_IMS_CTRL_MSG_STRU               *pstAtImsaMsgPara
);
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

#endif /* end of AtSndMsg.h */
