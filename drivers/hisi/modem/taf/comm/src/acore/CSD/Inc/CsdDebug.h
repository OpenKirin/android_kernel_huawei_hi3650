

#ifndef __CSDDEBUG_H__
#define __CSDDEBUG_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
/* Added by l60609 for AP������Ŀ ��2012-08-30 Begin */
#include "product_config.h"
/* Added by l60609 for AP������Ŀ ��2012-08-30 End */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#if( FEATURE_ON == FEATURE_CSD )

/*****************************************************************************
  3 ö�ٶ���
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
 �ṹ��    : CSD_UL_STATUS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : CSDͳ����
  1.��    ��   : 2012��1��20��
    ��    ��   : w00199382
    �޸�����   : �����ļ�
*****************************************************************************/
typedef struct
{
    /*CSD����ͳ����Ϣ*/
    VOS_UINT32                          ulULRecvPktNum;                         /*CSD�����յ��İ���Ŀ*/
    VOS_UINT32                          ulULSaveBuffPktNum;                     /*CSD���л��������Ŀ*/
    VOS_UINT32                          ulULEnQueFail;                          /*CSD���ʧ�ܵĴ���*/
    VOS_UINT32                          ulULSendPktNum;                         /*CSD�������л��������Ŀ*/
    VOS_UINT32                          ulULQueNullNum;                         /*CSD������������ʱ�Ӷ����л�ȡ����ָ�����Ŀ*/
    VOS_UINT32                          ulULZcToImmFailNum;                     /*CSD������������sk_bufferͷת����IMMͷʧ�ܵİ���Ŀ*/
    VOS_UINT32                          ulULInsertDiccFailNum;                  /*CSD�����������ݲ���DICCͨ��ʧ�ܵİ���Ŀ*/

    /*CSD����ͳ����Ϣ*/
    VOS_UINT32                          ulDLRecvPktNum;                         /*CSD�����յ��İ���Ŀ*/
    VOS_UINT32                          ulDLSendPktNum;                         /*CSD���з��͵������İ���Ŀ*/
    VOS_UINT32                          ulDLSendFailNum;                        /*CSD���з���ʧ�ܰ�����Ŀ*/

}CSD_UL_STATUS_INFO_STRU;

/*****************************************************************************
  8 ȫ�ֱ�������
*****************************************************************************/
extern CSD_UL_STATUS_INFO_STRU          g_stCsdStatusInfo;

/*****************************************************************************
  10 �궨��
*****************************************************************************/

/*CSD����ͳ����Ϣ*/
#define CSD_DBG_UL_RECV_PKT_NUM(n)      (g_stCsdStatusInfo.ulULRecvPktNum       += (n))
#define CSD_DBG_UL_SAVE_BUFF_PKT_NUM(n) (g_stCsdStatusInfo.ulULSaveBuffPktNum   += (n))
#define CSD_DBG_UL_ENQUE_FAIL_NUM(n)    (g_stCsdStatusInfo.ulULEnQueFail        += (n))
#define CSD_DBG_UL_SEND_PKT_NUM(n)      (g_stCsdStatusInfo.ulULSendPktNum       += (n))
#define CSD_DBG_UL_QUENULL_NUM(n)       (g_stCsdStatusInfo.ulULQueNullNum       += (n))
#define CSD_DBG_UL_ZCTOIMM_FAIL_NUM(n)  (g_stCsdStatusInfo.ulULZcToImmFailNum   += (n))
#define CSD_DBG_UL_INSERT_FAIL_NUM(n)   (g_stCsdStatusInfo.ulULInsertDiccFailNum += (n))

/*CSD����ͳ����Ϣ*/
#define CSD_DBG_DL_RECV_PKT_NUM(n)      (g_stCsdStatusInfo.ulDLRecvPktNum       += (n))
#define CSD_DBG_DL_SEND_PKT_NUM(n)      (g_stCsdStatusInfo.ulDLSendPktNum       += (n))
#define CSD_DBG_DL_SEND_FAIL_NUM(n)     (g_stCsdStatusInfo.ulDLSendFailNum      += (n))



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

#endif /* end of CsdDebug.h */
