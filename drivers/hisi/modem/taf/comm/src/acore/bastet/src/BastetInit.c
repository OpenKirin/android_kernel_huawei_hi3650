
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "BastetInit.h"



/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_BST_INIT_C
/*lint +e767*/

RECV_MSG_PROC pRecvMsgProc = NULL;

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID BASTET_CommRegRecvCallBack(RECV_MSG_PROC pFunc)
{
    pRecvMsgProc = pFunc;
}

/*****************************************************************************
 �� �� ��  : BASTET_CommPidInit
 ��������  : BASTET��Ϣ����PID��ʼ��
 �������  : enum VOS_INIT_PHASE_DEFINE enPhase
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��14��
    ��    ��   : ����/00188486
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 BASTET_CommPidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_LOAD_CONFIG:
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : BASTET_CommProcMsg
 ��������  : BASTET��Ϣ����
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��14��
    ��    ��   : ����/00188486
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID BASTET_CommProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    if (NULL != pRecvMsgProc)
    {
        pRecvMsgProc(pMsg);
    }
}

/*****************************************************************************
 �� �� ��  : BASTET_CommFidInit
 ��������  : BASTET���������ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE ip
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��14��
    ��    ��   : ����/00188486
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 BASTET_CommFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:

            /* ����PID��ʼ�� */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_BASTET_COMM,
                                         (Init_Fun_Type)BASTET_CommPidInit,
                                         (Msg_Fun_Type)BASTET_CommProcMsg);

            if (VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }
            /* �������ȼ� */
            ulRslt = VOS_RegisterTaskPrio(ACPU_FID_BASTET_COMM, VOS_PRIORITY_P4);
            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }
            break;

        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;
    }

    return VOS_OK;
}

