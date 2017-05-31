

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#ifndef _TAFAGENT_CTX_H_
#define _TAFAGENT_CTX_H_


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAFAGENT_APS_MAX_MSG_LEN       (512)

#define TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(locked)         (g_stTafAgentCtx.ulAcpuCnfSemLockedFlg = (locked))
#define TAF_AGENT_GET_ACPU_CNF_SEM_LOCK_FLG()               (g_stTafAgentCtx.ulAcpuCnfSemLockedFlg)

#define TAF_AGENT_DBG_SAVE_MUTEX_SEM_ID(sem_id)             (g_stTafAgentStats.ulMutexSemId = (sem_id))
#define TAF_AGENT_DBG_SAVE_BINARY_SEM_ID(sem_id)            (g_stTafAgentStats.ulBinarySemId = (sem_id))
#define TAF_AGENT_DBG_CREATE_MUTEX_SEM_FAIL_NUM(n)          (g_stTafAgentStats.ulCreateMutexSemFailNum += (n))
#define TAF_AGENT_DBG_CREATE_BINARY_SEM_FAIL_NUM(n)         (g_stTafAgentStats.ulCreateBinarySemFailNum += (n))
#define TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(n)            (g_stTafAgentStats.ulLockMutexSemFailNum += (n))
#define TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(n)           (g_stTafAgentStats.ulLockBinarySemFailNum += (n))
#define TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(rslt)    (g_stTafAgentStats.ulLastMutexSemErrRslt = (rslt))
#define TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(rslt)      (g_stTafAgentStats.ulLastBinarySemErrRslt = (rslt))
#define TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(n)               (g_stTafAgentStats.ulSyncMsgIsNullNum += (n))
#define TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(n)             (g_stTafAgentStats.ulSyncMsgNotMatchNum += (n))


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
�ṹ��    : TAFAGENT_CTX_STRU
�ṹ˵��  : TAFAGENT��������
  1.��    ��   : 2012��01��02��
    ��    ��   : C00173809
    �޸�����   : �����ṹ

  2.��    ��   : 2012��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012071607302: TAF���ͬ��APIʵ���Ż�, ��ֹ�쳣���ֺ�,
                 ����API����ʧЧ
*****************************************************************************/
typedef struct
{
    /* �����ź���������ͬ��PS��ͬ��API�Ļ������,��ʼֵΪ����״̬(0xFFFFFFFF) */
    VOS_SEM                             hTafAcpuSyncSem;

    /* �������ź����������ȴ����ؽ���� */
    VOS_SEM                             hTafAcpuCnfSem;

    /* ��ʼ����ʶ, VOS_TRUE: �ɹ�; VOS_FALSE: ʧ�� */
    VOS_UINT32                          ulInitFlg;

    /* �������ź���״̬ */
    VOS_UINT32                          ulAcpuCnfSemLockedFlg;

    /* ����PS��ͬ��API�ظ���Ϣ��ָ�� */
    VOS_UINT8                          *pucTafAcpuCnfMsg;

    VOS_UINT8                           aucMsg[TAFAGENT_APS_MAX_MSG_LEN];
}TAFAGENT_CTX_STRU;

/*****************************************************************************
 �ṹ��    : TAF_AGENT_STATS_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : TAFAGENTͳ����Ϣ
  1.��    ��   : 2012��7��3��
    ��    ��   : A00165503
    �޸�����   : �����ṹ

  2.��    ��   : 2012��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012071607302: TAF���ͬ��APIʵ���Ż�, ��ֹ�쳣���ֺ�,
                 ����API����ʧЧ
*****************************************************************************/
typedef struct
{
    VOS_SEM                             ulMutexSemId;               /* �����ź���ID */
    VOS_SEM                             ulBinarySemId;              /* �������ź���ID */
    VOS_UINT32                          ulCreateMutexSemFailNum;    /* ���������ź���ʧ�ܴ��� */
    VOS_UINT32                          ulCreateBinarySemFailNum;   /* �����������ź���ʧ�ܴ��� */
    VOS_UINT32                          ulLockMutexSemFailNum;      /* �������ź���ʧ�ܴ��� */
    VOS_UINT32                          ulLockBinarySemFailNum;     /* ���������ź���ʧ�ܴ��� */
    VOS_UINT32                          ulLastMutexSemErrRslt;      /* ���һ���������ź���ʧ�ܽ�� */
    VOS_UINT32                          ulLastBinarySemErrRslt;     /* ���һ�����������ź���ʧ�ܽ�� */
    VOS_UINT32                          ulSyncMsgIsNullNum;         /* ͬ����ϢΪ�մ��� */
    VOS_UINT32                          ulSyncMsgNotMatchNum;       /* ͬ����Ϣ��ƥ����� */

} TAF_AGENT_STATS_INFO_STRU;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

extern TAF_AGENT_STATS_INFO_STRU        g_stTafAgentStats;

extern TAFAGENT_CTX_STRU                g_stTafAgentCtx;


/*****************************************************************************
  10 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : Taf_Agent_InitCtx
 ��������  : ��ʼ��Taf Agentȫ�ֱ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_UINT32 Taf_Agent_InitCtx(VOS_VOID);

/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetTafAcpuSyncSem
 ��������  : ��ȡSYNC�ź���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_SEM
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_SEM TAF_AGENT_GetTafAcpuSyncSem(VOS_VOID);

/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetTafAcpuCnfSem
 ��������  : ��ȡCnf�ź���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_SEM TAF_AGENT_GetTafAcpuCnfSem(VOS_VOID);

/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetTafAcpuCnfMsg
 ��������  : ��ȡ��Ϣ��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : MsgBlock*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_UINT8* TAF_AGENT_GetTafAcpuCnfMsg(VOS_VOID);

/*****************************************************************************
 �� �� ��  : TAF_AGENT_SetTafAcpuCnfMsg
 ��������  : ������Ϣ��ַ
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_VOID TAF_AGENT_SetTafAcpuCnfMsg(VOS_UINT8* pMsg);

/*****************************************************************************
 �� �� ��  : TAF_AGENT_ClearMsg
 ��������  : �����Ϣ����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_VOID TAF_AGENT_ClearMsg(VOS_VOID);

/*****************************************************************************
 �� �� ��  : TAF_AGENT_SaveMsg
 ��������  : ������Ϣ����
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��7��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
*****************************************************************************/
extern VOS_UINT8* TAF_AGENT_SaveMsg(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen
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

