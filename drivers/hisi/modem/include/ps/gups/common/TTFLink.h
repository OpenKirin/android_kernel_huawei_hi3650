

#ifndef __TTF_LINK_H_
#define __TTF_LINK_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/******************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "PsLib.h"
#include "TtfLinkInterface.h"

/*lint -e830*/
/******************************************************************************
  2 �궨��
******************************************************************************/
#define TTF_LINK_CNT(pLink)           ((pLink)->ulCnt)

#define TTF_LINK_INIT_NODE(pstNode)     \
{\
    (pstNode)->pPrev    = VOS_NULL_PTR; \
    (pstNode)->pNext    = VOS_NULL_PTR; \
}


/******************************************************************************
  3 ö�ٶ���
******************************************************************************/


/******************************************************************************
  4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
  5 ��Ϣͷ����
******************************************************************************/


/******************************************************************************
  6 ��Ϣ����
******************************************************************************/


/******************************************************************************
  7 STRUCT����
******************************************************************************/
#pragma pack(4)


/*======================================================*/
/*
����ͷstHeadҲ��һ���ڵ�
stHead.pNext���������ͷָ��
stHead.pPrev���������βָ��
����ĵ�һ��Ԫ�ص�pPrevʼ��ָ������ͷ
��������һ��Ԫ�ص�pNextҲʼ��ָ������ͷ
*/
/*=======================================================*/
typedef struct
{
    TTF_NODE_ST             stHead;
    VOS_UINT32              ulCnt;
} TTF_LINK_ST;

/*=============  ���ζ��нṹ��    ======================*/

typedef struct
{
    VOS_VOID*              *ppNode;     /* ���ݴ洢���洢ָ���������ݵ�ָ������ */
    VOS_UINT32              ulFront;    /* ��ͷָ��:ָ����Ƕ�ͷλ��,ȡ������ʱ����ͷȡģ++ */
    VOS_UINT32              ulRear;     /* ��βָ��:ָ�������һ������ӵ�λ�ã�д������ʱ����βȡģ++ */
    VOS_UINT32              ulMaxSize;  /* ���п��ٵ�Ԫ�ظ��� =Ԫ��ʵ�ʸ���+1 (��һ��Ԫ�����������ζ����������ǿ� ) */
}TTF_RING_Q_ST;
/*=======================================================*/

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


/******************************************************************************
  8 UNION����
******************************************************************************/


/******************************************************************************
  9 OTHERS����
******************************************************************************/
/* ע��: ʹ���߱��뱣֤pLink�ǿգ�������Ҫʹ�ú��� */
#define TTF_LINK_IS_EMPTY(pLink) (0 == (pLink)->ulCnt)
#define TTF_LINK_IS_NOT_EMPTY(pLink) (0 != (pLink)->ulCnt)

#define TTF_LINK_INIT(pLink)    \
{   \
    (pLink)->stHead.pNext = &((pLink)->stHead); \
    (pLink)->stHead.pPrev = &((pLink)->stHead); \
    (pLink)->ulCnt        = 0;  \
}

#define TTF_LINK_INSERT_TAIL(pLink, pInsert) \
{   \
    (pInsert)->pNext              = (TTF_NODE_ST *)(&((pLink)->stHead));  \
    (pInsert)->pPrev              = (pLink)->stHead.pPrev;  \
    (pLink)->stHead.pPrev->pNext  = (pInsert);  \
    (pLink)->stHead.pPrev         = (pInsert);  \
    (pLink)->ulCnt++; \
}

#define TTF_LINK_PEEK_HEAD(pLink, pNode, PtrType) \
{   \
    if ( 0 == (pLink)->ulCnt )    \
    {   \
        (pNode) = (PtrType)VOS_NULL_PTR;   \
    }   \
    else    \
    {   \
        (pNode) = (PtrType)((pLink)->stHead.pNext);    \
    }   \
}

#define TTF_LINK_REMOVE_NODE(pLink, pRemoveNode) \
{   \
    (pRemoveNode)->pNext->pPrev = (pRemoveNode)->pPrev; \
    (pRemoveNode)->pPrev->pNext = (pRemoveNode)->pNext; \
    (pRemoveNode)->pPrev        = VOS_NULL_PTR; \
    (pRemoveNode)->pNext        = VOS_NULL_PTR; \
    (pLink)->ulCnt--;   \
}

extern VOS_VOID     TTF_LinkInit(VOS_UINT32 ulPid, TTF_LINK_ST *pLink);
extern VOS_VOID     TTF_NodeInit(TTF_NODE_ST *pNode);
extern VOS_VOID     TTF_LinkFree(VOS_UINT32 ulPid, TTF_LINK_ST *pLink);
extern VOS_UINT32   TTF_LinkCheckNodeInLink(VOS_UINT32 ulPid, TTF_LINK_ST *pLink, TTF_NODE_ST *pCurr);

#ifdef _lint
/*
  ����L2���ڴ������ƣ�����������һ���ڴ棬ֻҪ������뵽�����У������ߵ������Ѿ�����ˣ�
  ���ڴ����ͷŻ���ͳһ�Ļ��ƽ��д���ԭ�����߲��ٸ����ͷš�Ŀǰ����PCLINTʱ������һЩ
  �ڴ�й©��澯����L2���ڴ�����������ʵ��޸ģ�����ӦPCLINT�ļ�鴦��
*/
#ifdef  TTF_LinkInsertHead
#undef  TTF_LinkInsertHead
#endif
#define TTF_LinkInsertHead(ulPid, pLink, pInsert)           /*lint -e155 */{(VOS_VOID)(pLink); free(pInsert);}/*lint +e155 */

#ifdef  TTF_LinkInsertTail
#undef  TTF_LinkInsertTail
#endif
#define TTF_LinkInsertTail(ulPid, pLink, pInsert)           /*lint -e155 */{(VOS_VOID)(pLink); free(pInsert);}/*lint +e155 */

#ifdef  TTF_LinkInsertNext
#undef  TTF_LinkInsertNext
#endif
#define TTF_LinkInsertNext(ulPid, pLink, pCurr, pInsert)    /*lint -e155 */{(VOS_VOID)(pLink); (VOS_VOID)(pCurr); free(pInsert);}/*lint +e155 */
#else
extern VOS_UINT32   TTF_LinkInsertHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert);
extern VOS_UINT32   TTF_LinkInsertPrev(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pCurr, TTF_NODE_ST *pInsert);
extern VOS_UINT32   TTF_LinkInsertNext(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pCurr, TTF_NODE_ST *pInsert);
extern VOS_UINT32   TTF_LinkInsertTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert);
#endif

extern VOS_UINT32   TTF_LinkSafeInsertTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pInsert, VOS_UINT32 *pulNonEmptyEvent);
extern TTF_NODE_ST* TTF_LinkSafeRemoveHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, VOS_UINT32 *pulRemainCnt);

extern VOS_VOID     TTF_LinkRemoveNode(VOS_UINT32 ulPid, TTF_LINK_ST * pLink, TTF_NODE_ST *pRemoveNode);
extern TTF_NODE_ST* TTF_LinkRemoveTail(VOS_UINT32 ulPid, TTF_LINK_ST * pLink);

extern VOS_UINT32   TTF_LinkPeekNext(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink,
                                     TTF_NODE_ST *pCurr, TTF_NODE_ST **ppCurrNext);
extern VOS_UINT32   TTF_LinkPeekPrev(VOS_UINT32 ulPid, TTF_LINK_ST * pLink,
                                     TTF_NODE_ST *pCurr, TTF_NODE_ST **ppCurrPrev);
extern TTF_NODE_ST* TTF_LinkPeekTail(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink);
extern VOS_UINT32   TTF_LinkStick(VOS_UINT32 ulPid, TTF_LINK_ST *pLink1,
                                  TTF_LINK_ST *pLink2);
extern TTF_NODE_ST* TTF_LinkRemoveHead(VOS_UINT32 ulPid, TTF_LINK_ST * pLink);
extern VOS_UINT32   TTF_LinkCnt(VOS_UINT32 ulPid, const TTF_LINK_ST *pLink);
extern VOS_UINT32   TTF_LinkIsEmpty(VOS_UINT32 ulPid, const TTF_LINK_ST *pLink);
extern TTF_NODE_ST* TTF_LinkPeekHead(VOS_UINT32 ulPid, const TTF_LINK_ST * pLink);

extern VOS_UINT32   TTF_RING_Q_Init(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_UINT32 ulMaxSize );
/*Linux add begin������� 00178567 */
extern VOS_UINT32  TTF_RING_Q_InitAndNodeAddrSet(VOS_UINT32 ulPid,
                                                                TTF_RING_Q_ST *pstRingQ,
                                                                VOS_VOID **ppNode,
                                                                VOS_VOID *pQueueNode,
                                                                VOS_UINT32 ulBlkSize,
                                                                VOS_UINT32 ulMaxSize );
extern VOS_UINT32  TTF_RING_Q_NodeAddrInit(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_VOID **ppNodeAddr,VOS_UINT32 ulNodeCnt,VOS_UINT8 ucSize);
/*Linux add end������� 00178567 */
extern VOS_UINT32   TTF_RING_Q_NodeAddrSet(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ, VOS_VOID **ppNodeAddr,VOS_UINT32 ulNodeCnt);
extern VOS_VOID*    TTF_RING_Q_Front(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_VOID*    TTF_RING_Q_Rear(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_In(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ );
extern VOS_VOID*    TTF_RING_Q_Out(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_IsFull(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_IsEmpty(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_GetCnt(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_Flush(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
extern VOS_UINT32   TTF_RING_Q_Free(VOS_UINT32 ulPid, TTF_RING_Q_ST *pstRingQ);
/*lint +e830*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* TTFLINK.h */

