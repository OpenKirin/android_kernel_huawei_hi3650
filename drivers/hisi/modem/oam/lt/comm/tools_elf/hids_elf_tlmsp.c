/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hids_elf_tlmsp.c
  �� �� ��   : ����
  ��    ��   : c00326366
  ��������   : 2015��11��13��
  ����޸�   :
  ��������   : ����ELF�ļ���HIDS���߽���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��11��13��
    ��    ��   : c00326366
    �޸�����   : �����ļ�

******************************************************************************/


#include "msp_diag_comm.h"
#include "lte_sleepflow.h"
#include "diag_msgbbp.h"
#include "diag_msgbsp.h"
#include "diag_msgmsp.h"
#include "diag_msgphy.h"
#include "diag_debug.h"
#include "diag_msgapplog.h"

void msp_main(void)
{
// ��Ϣ�ṹ������ʼ
    MSP_SLEEP_MNTN_MSG_STRU stSleepMsg;
    
    DIAG_MSG_MSP_CONN_STRU  stMspConn;
    
    DIAG_MSG_A_TRANS_C_STRU stMsgATransC;
    
    DIAG_BSP_MSG_A_TRANS_C_STRU  stBspMsgTrans;
    
    DIAG_BBP_MSG_A_TRANS_C_STRU  stBbpMsgTrans;
    
    DIAG_PHY_MSG_A_TRANS_C_STRU  stPhyMsgTrans;
    
#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
    DIAG_MSG_SOCP_VOTE_REQ_STRU  stMsgSocpVote;
    
    DIAG_MSG_SOCP_VOTE_WAKE_CNF_STRU stMsgSocpVoteCnf;
#endif
    
    DIAG_A_DEBUG_C_REQ_STRU      stADebugCReq;
    
    DIAG_BSP_NV_AUTH_STRU        stBspNvAuth;

    DIAG_MNTN_INFO_STRU          stMntnInfo;
    
    DIAG_LOST_INFO_STRU          stLostInfo;
	DIAG_APPLOG_CFG_REQ          stAppLog;
// ��Ϣ�ṹ��������
}

