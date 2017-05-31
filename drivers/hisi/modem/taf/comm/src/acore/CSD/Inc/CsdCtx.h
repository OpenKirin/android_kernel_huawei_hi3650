

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#ifndef _CSD_CTX_H_
#define _CSD_CTX_H_


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsCommonDef.h"
#include "PsLogdef.h"
#include "ImmInterface.h"
#include "DiccInterface.h"
#include "AtCsdInterface.h"
#include "CsdLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



#pragma pack(4)

#if( FEATURE_ON == FEATURE_CSD )


/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*Ĭ��sliceֵ��ulTxSlice��ʼ��ʱʹ��*/
#define CSD_DEFAULT_TX_SLICE    (0)

/*The count number of the semaphore that create*/
#define CSD_SEMAPHORE_INIT_CNT  (0)
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
  2 ȫ�ֱ�������
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
�ṹ��    : CSD_CTX_STRU
�ṹ˵��  : CSD��������

  1.��    ��   : 2011��12��6��
    ��    ��   : w00199382
    �޸�����   : �����ṹ
  2.��    ��   : 2013��05��28��
    ��    ��   : f00179208
    �޸�����   : V3R3 PPP PROJECT
*****************************************************************************/

typedef struct
{
    VOS_SEM                             hULdataSem;                             /*���������ź���*/
    VOS_SEM                             hDLdataSem;                             /*���������ź���*/
    VOS_UINT32                          ulLastDICCIsrSlice;                     /*��¼DICC�ж�SLICE*/
    AT_CSD_CALL_TYPE_STATE_ENUM_UINT16  enCallState;                            /*��¼��ǰͨ��״̬*/
    VOS_UINT8                           ucAtClientIndex;                        /* AT Client Index */
    VOS_UINT8                           aucReserved[1];
    IMM_ZC_HEAD_STRU                   *pstULQueue;                             /*���л������*/
    VOS_SPINLOCK                        stSpinLock;
}CSD_CTX_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

/*****************************************************************************
  10 ��������
*****************************************************************************/

AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 CSD_GetCallState(VOS_VOID);
VOS_SEM CSD_GetDownLinkDataSem(VOS_VOID);
VOS_UINT32 CSD_GetLastTxSlice(VOS_VOID);
VOS_SEM CSD_GetUpLinkDataSem(VOS_VOID);
VOS_UINT32 CSD_InitCtx(VOS_VOID);
VOS_UINT32 CSD_InitSem(VOS_VOID);
VOS_VOID CSD_SetCallState(AT_CSD_CALL_TYPE_STATE_ENUM_UINT16 enCallState);
VOS_VOID CSD_SetCurrTxSlice(VOS_UINT32 ulCurrSlice);
VOS_UINT32 CSD_UL_FreeQueue(IMM_ZC_HEAD_STRU *pstQueue);
IMM_ZC_HEAD_STRU *CSD_UL_GetQueue(VOS_VOID);
VOS_VOID CSD_UL_SetQueue(IMM_ZC_HEAD_STRU *pstULQueue);
VOS_UINT32 CSD_UL_InsertQueueTail(
    IMM_ZC_HEAD_STRU                    *pstQueueHead,
    IMM_ZC_STRU                         *pData
);
IMM_ZC_STRU  *CSD_UL_GetQueueFrontNode(IMM_ZC_HEAD_STRU *pstQueue);

VOS_UINT8 CSD_UL_GetAtClientIndex(VOS_VOID);
VOS_VOID CSD_UL_SetAtClientIndex(VOS_UINT8 ucIndex);

#endif /*FEATURE_ON == FEATURE_CSD*/

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

