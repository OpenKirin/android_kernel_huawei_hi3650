
#define    THIS_FILE_ID        PS_FILE_ID_TAF_AGENT_C


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafAgent.h"
#include "TafAgentCtx.h"
#include "TafAgentLog.h"
#include "TafAgentInterface.h"
#include "TafAgentOamInterface.h"


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern VOS_UINT32 AT_GetDestPid(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT32                          ulRcvPid
);

/*****************************************************************************
3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_AGENT_PidInit
 ��������  : TAF AGENT PID�ĳ�ʼ����������PID����OM FID֮�¡�
 �������  : enum VOS_INIT_PHASE_DEFINE enPhase
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��22��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���/PS�ں���Ŀ
*****************************************************************************/
VOS_UINT32 TAF_AGENT_PidInit(enum VOS_INIT_PHASE_DEFINE enPhase)
{
    switch ( enPhase )
    {
        case VOS_IP_INITIAL:
            return Taf_Agent_InitCtx();

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_IsValidMsg
 ��������  : �ж��Ƿ�����Ч����Ϣ
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��22��
    ��    ��   : C00173809
    �޸�����   : �����ɺ���/PS�ں���Ŀ

  2.��    ��   : 2012��12��24��
    ��    ��   : L60609
    �޸�����   : DSDA Phase II
  3.��    ��   : 2013��4��16��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2015��6��25��
    ��    ��   : l00198894
    �޸�����   : TSTS
*****************************************************************************/
VOS_UINT32 TAF_AGENT_IsValidMsg(MsgBlock* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader;

    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_IsValidMsg: Msg is invalid!");
        return VOS_ERR;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-16, begin */
    if ((I0_WUEPS_PID_TAF == pstMsgHeader->ulSenderPid)
     || (I1_WUEPS_PID_TAF == pstMsgHeader->ulSenderPid)
     || (I2_WUEPS_PID_TAF == pstMsgHeader->ulSenderPid)
     || (I0_UEPS_PID_MTA  == pstMsgHeader->ulSenderPid)
     || (I1_UEPS_PID_MTA  == pstMsgHeader->ulSenderPid)
     || (I2_UEPS_PID_MTA  == pstMsgHeader->ulSenderPid))
    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-16, end */
    {

        if ((ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF <= pstMsgHeader->ulMsgName)
         && (ID_TAFAGENT_MSG_ID_ENUM_BUTT > pstMsgHeader->ulMsgName))
        {
            return VOS_OK;
        }
    }

   return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_ClearAllSem
 ��������  : ������е��ź���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��04��17��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���/C�˵�����λ��Ŀ
*****************************************************************************/
VOS_VOID TAF_AGENT_ClearAllSem(VOS_VOID)
{
    /* ��������Ĵ��� */
    if (VOS_TRUE == TAF_AGENT_GET_ACPU_CNF_SEM_LOCK_FLG())
    {
        VOS_SmV(TAF_AGENT_GetTafAcpuCnfSem());
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_ProcMsg
 ��������  : TAF AGENT����Ϣ������
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��22��
    ��    ��   : C00173809
    �޸�����   : �����ɺ���/PS�ں���Ŀ

  2.��    ��   : 2012��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012071607302: TAF���ͬ��APIʵ���Ż�, ��ֹ�쳣���ֺ�,
                 ����API����ʧЧ

  3.��    ��   : 2016��5��16��
    ��    ��   : w00316404
    �޸�����   : DTS2016051400354: ��ӿ�ά�ɲ���Ϣ
*****************************************************************************/
VOS_VOID TAF_AGENT_ProcMsg(MsgBlock* pstMsg)
{
    VOS_UINT8                          *pucMsg;
    VOS_UINT32                          ulResult;

    ulResult    = VOS_OK;

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "ENTER TAF_AGENT_ProcMsg!");

    if (VOS_OK == TAF_AGENT_IsValidMsg(pstMsg))
    {
        TAFAGENT_NORMAL_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_ProcMsg: Msg Name is %d\n", ((MSG_HEADER_STRU *)pstMsg)->ulMsgName);

        if (VOS_FALSE == TAF_AGENT_GET_ACPU_CNF_SEM_LOCK_FLG())
        {
            TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_ProcMsg: SemLockedFlg is False!");
            return;
        }

        /* �ж���Ϣ�Ƿ��ͷ� */
        if (VOS_NULL_PTR == TAF_AGENT_GetTafAcpuCnfMsg())
        {
            TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_ProcMsg: TafAcpuCnfMsg is VOS_NULL_PTR!");

            /* ���ݻظ���Ϣ */
            pucMsg = TAF_AGENT_SaveMsg((VOS_UINT8*)pstMsg,pstMsg->ulLength);

            TAF_AGENT_SetTafAcpuCnfMsg(pucMsg);

            TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

            /* �ͷ��ź�����ʹ�õ���API����������� */
            ulResult = VOS_SmV(TAF_AGENT_GetTafAcpuCnfSem());

            TAFAGENT_NORMAL_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_ProcMsg: VOS_SmV result is %x\n", ulResult);
        }
    }

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "EXIT TAF_AGENT_ProcMsg!");

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_FindCidForDial
 ��������  : ͨ��ͬ�����ƻ�ȡ���ڲ��ŵ�CID
 �������  :
 �������  : VOS_VOID
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : c00173809
    �޸�����   : PS�ں���Ŀ,����ͬ����Ϣ

  2.��    ��   : 2012��7��4��
    ��    ��   : A00165503
    �޸�����   : DTS2012042102488: TAF AGENTģ�����������Ϣ, ���ڶ�λ���API
                 ����ʧ������

  3.��    ��   : 2012��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012071607302: TAF���ͬ��APIʵ���Ż�, ��ֹ�쳣���ֺ�,
                 ����API����ʧЧ

  4.��    ��   : 2012��7��26��
    ��    ��   : A00165503
    �޸�����   : DTS2012072505555: TAF���ͬ��APIʵ���Ż�, ������ϢΪ�ձ���

  5.��    ��   : 2012��12��21��
    ��    ��   : l00227485
    �޸�����   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 TAF_AGENT_FindCidForDial(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                          *pCid
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU    *pstCnf;
    TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU    *pstMsg;

    ulResult                = VOS_ERR;

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "ENTER TAF_AGENT_FindCidForDial!");

    /* ���ͬ���ź��������������������ν���ȴ����У����ͬ���ź���δ�������ź�����*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_FindCidForDial: Lock Mutex SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* ������Ϣ */
    pstMsg = (TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                                    sizeof(TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ_STRU: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->enMsgId                     = ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_REQ;

    /* ��������Ϣ���͸�CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_FindCidForDial: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();


    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ�CCPU�Ļظ����ź��������� */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_FindCidForDial: Lock Binary SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU*)TAF_AGENT_GetTafAcpuCnfMsg();

    if (VOS_NULL_PTR == pstCnf)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_FindCidForDial: Msg Cnf is VOS_NULL_PTR!");

        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        *pCid       = pstCnf->ucCid;
        ulResult    = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "EXIT TAF_AGENT_FindCidForDial!");

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_SetPdpCidPara
 ��������  : ����ָ��CID�Ĳ���
 �������  : MN_CLIENT_ID_T                      usClientId,
             TAF_PS_DIAL_PARA_STRU              *pstPdpPriPara
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : c00173809
    �޸�����   : PS�ں���Ŀ,�ṩ���ͬ��API

  2.��    ��   : 2012��7��4��
    ��    ��   : A00165503
    �޸�����   : DTS2012042102488: TAF AGENTģ�����������Ϣ, ���ڶ�λ���API
                 ����ʧ������

  3.��    ��   : 2012��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012071607302: TAF���ͬ��APIʵ���Ż�, ��ֹ�쳣���ֺ�,
                 ����API����ʧЧ

  4.��    ��   : 2012��7��26��
    ��    ��   : A00165503
    �޸�����   : DTS2012072505555: TAF���ͬ��APIʵ���Ż�, ������ϢΪ�ձ���

  5.��    ��   : 2012��12��21��
    ��    ��   : l00227485
    �޸�����   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 TAF_AGENT_SetPdpCidPara(
    MN_CLIENT_ID_T                      usClientId,
    TAF_PDP_PRIM_CONTEXT_EXT_STRU      *pstPdpPrimContextExt
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_SET_CID_PARA_CNF_STRU         *pstCnf;
    TAFAGENT_APS_SET_CID_PARA_REQ_STRU         *pstMsg;

    ulResult                = VOS_ERR;

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "ENTER TAF_AGENT_SetPdpCidPara!");

    /* ���ͬ���ź��������������������ν���ȴ����У����ͬ���ź���δ�������ź�����*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidPara: Lock Mutex SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* ������Ϣ */
    pstMsg = (TAFAGENT_APS_SET_CID_PARA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_APS_SET_CID_PARA_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidPara: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->enMsgId                     = ID_TAFAGENT_APS_SET_CID_PARA_REQ;

    pstMsg->ulClientID                  = usClientId;

    PS_MEM_CPY((VOS_VOID*)&(pstMsg->stPdpPrimContextExt),(VOS_VOID*)pstPdpPrimContextExt,sizeof(TAF_PDP_PRIM_CONTEXT_EXT_STRU));

    /* ��������Ϣ���͸�CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidPara: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ�CCPU�Ļظ����ź��������� */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidPara: Lock Binary SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_SET_CID_PARA_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidPara: Msg Cnf is VOS_NULL_PTR!");

        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_SET_CID_PARA_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "EXIT TAF_AGENT_SetPdpCidPara!");

    return ulResult;

}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetPdpCidPara
 ��������  : ��ѯָ��CID�Ĳ���
 �������  : TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpPriPara,
             VOS_UINT8                           ucCid
 �������  : TAF_PDP_PRIM_CONTEXT_STRU                   *pstPdpPriPara
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��18��
    ��    ��   : c00173809
    �޸�����   : PS�ں���Ŀ,�ṩ���ͬ��API

  2.��    ��   : 2012��7��4��
    ��    ��   : A00165503
    �޸�����   : DTS2012042102488: TAF AGENTģ�����������Ϣ, ���ڶ�λ���API
                 ����ʧ������

  3.��    ��   : 2012��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012071607302: TAF���ͬ��APIʵ���Ż�, ��ֹ�쳣���ֺ�,
                 ����API����ʧЧ

  4.��    ��   : 2012��7��26��
    ��    ��   : A00165503
    �޸�����   : DTS2012072505555: TAF���ͬ��APIʵ���Ż�, ������ϢΪ�ձ���

  5.��    ��   : 2012��12��21��
    ��    ��   : l00227485
    �޸�����   : DSDA PhaseII
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetPdpCidPara(
    TAF_PDP_PRIM_CONTEXT_STRU          *pstPdpPriPara,
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCid
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_GET_CID_PARA_CNF_STRU         *pstCnf;
    TAFAGENT_APS_GET_CID_PARA_REQ_STRU         *pstMsg;

    ulResult                = VOS_ERR;

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "ENTER TAF_AGENT_GetPdpCidPara!");

    /* ���ͬ���ź��������������������ν���ȴ����У����ͬ���ź���δ�������ź�����*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidPara: Lock Mutex SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* ������Ϣ */
    pstMsg = (TAFAGENT_APS_GET_CID_PARA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_APS_GET_CID_PARA_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidPara: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->enMsgId                     = ID_TAFAGENT_APS_GET_CID_PARA_REQ;

    pstMsg->ucCid                       = ucCid;

    /* ��������Ϣ���͸�CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidPara: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ�CCPU�Ļظ����ź��������� */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidPara: Lock Binary SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_GET_CID_PARA_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidPara: Msg Cnf is VOS_NULL_PTR!");

        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_GET_CID_PARA_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        PS_MEM_CPY((VOS_VOID*)pstPdpPriPara,(VOS_VOID*)&(pstCnf->stCidInfo),sizeof(TAF_PDP_PRIM_CONTEXT_STRU));
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "EXIT TAF_AGENT_GetPdpCidPara!");

    return ulResult;

}


/*****************************************************************************
 �� �� ��  : TAF_AGENT_SetPdpCidQosPara
 ��������  : ����ָ��CID��QOS����
 �������  : MN_CLIENT_ID_T                      usClientId,
             TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��06��29��
    ��    ��   : l60609
    �޸�����   : DTS2013062201514:��������QOS����ͬ���ӿ�

*****************************************************************************/
VOS_UINT32 TAF_AGENT_SetPdpCidQosPara(
    MN_CLIENT_ID_T                      usClientId,
    TAF_PS_PDP_QOS_SET_PARA_STRU       *pstQosPara
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU     *pstCnf;
    TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU     *pstMsg;

    ulResult                = VOS_ERR;

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "ENTER TAF_AGENT_SetPdpCidQosPara!");

    /* ���ͬ���ź��������������������ν���ȴ����У����ͬ���ź���δ�������ź�����*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidQosPara: Lock Mutex SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* ������Ϣ */
    pstMsg = (TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidQosPara: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->ulMsgId                     = ID_TAFAGENT_APS_SET_CID_QOS_PARA_REQ;

    pstMsg->usClientId                  = usClientId;

    PS_MEM_CPY((VOS_VOID*)&(pstMsg->stQosPara), (VOS_VOID*)pstQosPara, sizeof(TAF_PS_PDP_QOS_SET_PARA_STRU));

    /* ��������Ϣ���͸�CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidQosPara: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ�CCPU�Ļظ����ź��������� */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidQosPara: Lock Binary SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_SetPdpCidQosPara: Msg Cnf is VOS_NULL_PTR!");

        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_SET_CID_QOS_PARA_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "EXIT TAF_AGENT_SetPdpCidQosPara!");

    return ulResult;

}

/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetPdpCidQosPara
 ��������  : ��ѯָ��CID�Ĳ���
 �������  : MN_CLIENT_ID_T                      usClientId,
             VOS_UINT8                           ucCid
 �������  : TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara
 ���ú���  :
 ��������  :

 �޸���ʷ      :
   1.��    ��   : 2013��06��29��
     ��    ��   : l60609
     �޸�����   : DTS2013062201514:��������QOS����ͬ���ӿ�
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetPdpCidQosPara(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                           ucCid,
    TAF_PS_PDP_QOS_QUERY_PARA_STRU     *pstQosPara
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU     *pstCnf;
    TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU     *pstMsg;

    ulResult                = VOS_ERR;

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "ENTER TAF_AGENT_GetPdpCidQosPara!");

    /* ���ͬ���ź��������������������ν���ȴ����У����ͬ���ź���δ�������ź�����*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidQosPara: Lock Mutex SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* ������Ϣ */
    pstMsg = (TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidQosPara: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_WUEPS_PID_TAF);
    pstMsg->ulMsgId                     = ID_TAFAGENT_APS_GET_CID_QOS_PARA_REQ;
    pstMsg->ucCid                       = ucCid;

    /* ��������Ϣ���͸�CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidQosPara: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ�CCPU�Ļظ����ź��������� */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidQosPara: Lock Binary SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetPdpCidQosPara: Msg Cnf is VOS_NULL_PTR!");

        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_APS_GET_CID_QOS_PARA_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        PS_MEM_CPY((VOS_VOID*)pstQosPara, (VOS_VOID*)&(pstCnf->stQosPara), sizeof(TAF_PS_PDP_QOS_QUERY_PARA_STRU));
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "EXIT TAF_AGENT_GetPdpCidQosPara!");

    return ulResult;

}


/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetCallInfo
 ��������  : ��ȡͨ����Ϣͬ��api
 �������  : MN_CLIENT_ID_T                      usClientId
             VOS_UINT8                           *pucNumOfCalls
             MN_CALL_INFO_STRU                   *pstCallInfos
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��27��
    ��    ��   : w00199382
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��7��4��
    ��    ��   : A00165503
    �޸�����   : DTS2012042102488: TAF AGENTģ�����������Ϣ, ���ڶ�λ���API
                 ����ʧ������

  3.��    ��   : 2012��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012071607302: TAF���ͬ��APIʵ���Ż�, ��ֹ�쳣���ֺ�,
                 ����API����ʧЧ

  4.��    ��   : 2012��7��26��
    ��    ��   : A00165503
    �޸�����   : DTS2012072505555: TAF���ͬ��APIʵ���Ż�, ������ϢΪ�ձ���

  5.��    ��   : 2013��3��13��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetCallInfoReq(
    MN_CLIENT_ID_T                      usClientId,
    VOS_UINT8                          *pucCallNum,
    TAFAGERNT_MN_CALL_INFO_STRU        *pstCallInfos
)
{
    TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *pstCnf;
    VOS_UINT32                          ulResult;

    ulResult = VOS_ERR;

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "ENTER TAF_AGENT_GetCallInfoReq!");

    /* ���ͬ���ź��������������������ν���ȴ����У����ͬ���ź���δ�������ź�����*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetCallInfoReq: Lock Mutex SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* �����첽Ӧ������ */
    ulResult = MN_CALL_SendAppRequest(ID_TAFAGENT_MN_GET_CALL_INFO_REQ,
                                      usClientId, 0, 0,
                                      VOS_NULL_PTR);
    if (MN_ERR_NO_ERROR != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetCallInfoReq: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ�CCPU�Ļظ����ź��������� */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetCallInfoReq: Lock Binary SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }


    ulResult      = VOS_ERR;
    pstCnf      = (TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetCallInfoReq: Msg Cnf is VOS_NULL_PTR!");

        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }


    if (ID_TAFAGENT_MN_GET_CALL_INFO_CNF == pstCnf->enMsgId)
    {
        PS_MEM_CPY((VOS_VOID*)pstCallInfos,
                   (VOS_VOID*)(pstCnf->stCallInfo),
                   sizeof(TAFAGERNT_MN_CALL_INFO_STRU) * MN_CALL_MAX_NUM);

        *pucCallNum = pstCnf->ucNumOfCalls;

        ulResult      = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "EXIT TAF_AGENT_GetCallInfoReq!");

    return ulResult;
}

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, begin */
/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetSysMode
 ��������  : ��ȡϵͳģʽ
 �������  : AT_SYS_MODE_STRU                   *pstSysMode
 �������  : AT_SYS_MODE_STRU                   *pstSysMode
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��2��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetSysMode(
    VOS_UINT16                                 usClientId,
    TAF_AGENT_SYS_MODE_STRU                   *pstSysMode
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_MTA_GET_SYSMODE_CNF_STRU          *pstCnf = VOS_NULL_PTR;
    TAFAGENT_MTA_GET_SYSMODE_REQ_STRU          *pstMsg = VOS_NULL_PTR;

    ulResult                = VOS_ERR;

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "ENTER TAF_AGENT_GetSysMode!");

    /* ���ͬ���ź��������������������ν���ȴ����У����ͬ���ź���δ�������ź�����*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetSysMode: Lock Mutex SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* ������Ϣ */
    pstMsg = (TAFAGENT_MTA_GET_SYSMODE_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_MTA_GET_SYSMODE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetSysMode: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_UEPS_PID_MTA);

    pstMsg->enMsgId                     = ID_TAFAGENT_MTA_GET_SYSMODE_REQ;

    /* ��������Ϣ���͸�CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetSysMode: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ�CCPU�Ļظ����ź��������� */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetSysMode: Lock Binary SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);
        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);
        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_MTA_GET_SYSMODE_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetSysMode: Msg Cnf is VOS_NULL_PTR!");

        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_MTA_GET_SYSMODE_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRet))
    {
        pstSysMode->enRatType       = pstCnf->stSysMode.enRatType;
        pstSysMode->enSysSubMode    = pstCnf->stSysMode.enSysSubMode;
        ulResult = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "EXIT TAF_AGENT_GetSysMode!");

    return ulResult;
}
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, end */

/*****************************************************************************
 �� �� ��  : TAF_AGENT_GetAntState
 ��������  : ��ȡ����״̬
 �������  : VOS_UINT16                   usClientId
 �������  : VOS_UINT16                  *pusAntState
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��2��
    ��    ��   : z60575
    �޸�����   : ��ȡ����״̬
*****************************************************************************/
VOS_UINT32 TAF_AGENT_GetAntState(
    VOS_UINT16                                 usClientId,
    VOS_UINT16                                *pusAntState
)
{
    VOS_UINT32                                  ulResult;
    TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU        *pstCnf = VOS_NULL_PTR;
    TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU        *pstMsg = VOS_NULL_PTR;

    ulResult = VOS_ERR;

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "ENTER TAF_AGENT_GetAntState!");

    /* ���ͬ���ź��������������������ν���ȴ����У����ͬ���ź���δ�������ź�����*/
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuSyncSem(), 0);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetAntState: Lock Mutex SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_MUTEX_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_MUTEX_SEM_FAIL_NUM(1);
        return VOS_ERR;
    }

    /* ������Ϣ */
    pstMsg = (TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(ACPU_PID_TAFAGENT,
                                                                               sizeof(TAFAGENT_MTA_GET_ANT_STATE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetAntState: Malloc Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    /* ��д��Ϣͷ */
    pstMsg->ulReceiverPid               = AT_GetDestPid(usClientId, I0_UEPS_PID_MTA);
    pstMsg->enMsgId                     = ID_TAFAGENT_MTA_GET_ANT_STATE_REQ;

    /* ��������Ϣ���͸�CCPU */
    ulResult = PS_SEND_MSG(ACPU_PID_TAFAGENT, pstMsg);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetAntState: Send Msg Failed!");

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    TAF_AGENT_SetTafAcpuCnfMsg(VOS_NULL_PTR);

    TAF_AGENT_ClearMsg();

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_TRUE);

    /* �ȴ��ظ��ź�����ʼΪ��״̬���ȴ�CCPU�Ļظ����ź��������� */
    ulResult = VOS_SmP(TAF_AGENT_GetTafAcpuCnfSem(), PS_SYNC_CNF_TIMEOUT_LEN);
    if (VOS_OK != ulResult)
    {
        TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "TAF_AGENT_GetAntState: Lock Binary SEM Failed! VOS_SmP result is %x\n", ulResult);
        TAF_AGENT_DBG_SAVE_LAST_BIN_SEM_ERR_RSLT(ulResult);
        TAF_AGENT_DBG_LOCK_BINARY_SEM_FAIL_NUM(1);
        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);
        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    ulResult    = VOS_ERR;
    pstCnf      = (TAFAGENT_MTA_GET_ANT_STATE_CNF_STRU*)(TAF_AGENT_GetTafAcpuCnfMsg());

    if (VOS_NULL_PTR == pstCnf)
    {
        TAFAGENT_ERROR_LOG(ACPU_PID_TAFAGENT, "TAF_AGENT_GetAntState: Msg Cnf is VOS_NULL_PTR!");

        TAF_AGENT_DBG_SYNC_MSG_IS_NULL_NUM(1);

        TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

        VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

        return VOS_ERR;
    }

    if ((ID_TAFAGENT_MTA_GET_ANT_STATE_CNF == pstCnf->enMsgId)
     && (VOS_OK == pstCnf->ulRslt))
    {
        *pusAntState    = pstCnf->usAntState;
        ulResult        = VOS_OK;
    }
    else
    {
        TAF_AGENT_DBG_SYNC_MSG_NOT_MATCH_NUM(1);
    }

    TAF_AGENT_SET_ACPU_CNF_SEM_LOCK_FLG(VOS_FALSE);

    VOS_SmV(TAF_AGENT_GetTafAcpuSyncSem());

    TAFAGENT_NORMAL_LOG(ACPU_PID_TAFAGENT, "EXIT TAF_AGENT_GetAntState!");

    return ulResult;
}


/*****************************************************************************
 �� �� ��  : TAF_AGENT_FidInit
 ��������  : TAF AGENT FID�ĳ�ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE enPhase
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��02��17��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2013021700415,TAFAGENT������һ��FID
*****************************************************************************/
VOS_UINT32 TAF_AGENT_FidInit (enum VOS_INIT_PHASE_DEFINE enPhase)
{
    VOS_UINT32                          ulRslt;

    switch(enPhase)
    {
        case VOS_IP_LOAD_CONFIG:

            /* ����ģ��ע��PID */
            ulRslt = VOS_RegisterPIDInfo(ACPU_PID_TAFAGENT,
                                        (Init_Fun_Type)TAF_AGENT_PidInit,
                                        (Msg_Fun_Type)TAF_AGENT_ProcMsg);
            if( VOS_OK != ulRslt )
            {
                TAFAGENT_ERROR_LOG1(ACPU_PID_TAFAGENT, "reg ACPU_PID_TAFAGENT VOS_RegisterPIDInfo FAIL! ulRslt: %d\n", ulRslt);

                return VOS_ERR;
            }

            ulRslt = VOS_RegisterTaskPrio(ACPU_FID_TAFAGENT, TAF_AGENT_TASK_PRIORITY);
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

        default:
            break;
    }

    return VOS_OK;
}    /* TAF_AGENT_FidInit */


