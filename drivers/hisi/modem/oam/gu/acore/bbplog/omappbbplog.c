

/******************************************************************************

                  ��Ȩ���� (C), 2001-2013, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : ombbplogapp.c
  �� �� ��      : ����
  ��    ��      : ���±� 00174725
  ��������      : 2012��11��16��
  ����޸�      :
  ��������      : BBP�������ά�ɲ���غ���ʵ��
  �����б�      :
  �޸���ʷ      :
  1.��    ��    : 2012��11��16��
    ��    ��    : ���±� 00174725
    �޸�����    : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "omprivate.h"
#include "ombbplog.h"
#include "phyoaminterface.h"
#include "pamappom.h"



/*lint -e767 �޸��ˣ����±� */
#define    THIS_FILE_ID        PS_FILE_ID_OM_APP_BBP_LOG_C
/*lint +e767 �޸��ˣ����±� */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* ��¼�ӵ����ȡ����DUMP�ڴ��ַ�ʹ�С */
BBP_DUMP_GET_FIX_DDR_ADDR               g_stBbpDumpFixDdr;

/*****************************************************************************
  3 �ⲿ��������
*****************************************************************************/


/*****************************************************************************
  4 ��Ϣ������ӳ���
*****************************************************************************/


/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : Om_AcpuQueryDumpMsgProc
 ��������  : CCpu��ѯDump��Ϣ��Ӧ����
 �������  : pMsg

 �������  : NA

 �� �� ֵ  : VOS_VOID

 �޸���ʷ      :
  1.��    ��   : 2014��10��08��
    ��    ��   : d00212987
    �޸�����   : BBP������Ŀ����
*****************************************************************************/
VOS_VOID Om_AcpuQueryDumpMsgProc(MsgBlock* pMsg)
{
    BBP_DUMP_MSG_STRU                  *pstBbpDumpMsg;
    VOS_UINT16                          usPrimId;

    usPrimId = *(VOS_UINT16*)(pMsg->aucValue);
    if (BBP_QUERY_DUMP_INFO_REQ == usPrimId)
    {
        /* ������Ϣ���͸�CCPU */
        pstBbpDumpMsg = (BBP_DUMP_MSG_STRU*)VOS_AllocMsg(ACPU_PID_PAM_OM,
                                sizeof(BBP_DUMP_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

        /* ������Ϣʧ�� */
        if (VOS_NULL_PTR == pstBbpDumpMsg)
        {
            return;
        }

        pstBbpDumpMsg->ulReceiverPid           = CCPU_PID_PAM_OM;
        pstBbpDumpMsg->usPrimId                = BBP_QUERY_DUMP_INFO_CNF;
        pstBbpDumpMsg->stDumpDdrInfo.ulPhyAddr = g_stBbpDumpFixDdr.ulPhyAddr;
        pstBbpDumpMsg->stDumpDdrInfo.ulPhySize = g_stBbpDumpFixDdr.ulPhySize;

        (VOS_VOID)VOS_SendMsg(ACPU_PID_PAM_OM, pstBbpDumpMsg);
    }

    return;
}

/*lint -save -e102 -e10 -e2 -e40 -e533 -e31 -e830 -e522 -e718 -e746 -e702 -e565  -e64 -e23 -e63 -e26 -e578 -e132 -e19 -e18 -e34 -e35 -e713*/
extern unsigned long simple_strtoul(const char *cp, char **endp, unsigned int base);

/*****************************************************************************
* �� �� ��  : Om_QueryDumpPhyAddr
*
* ��������  : �ڴ������׶ν�CMD LINE�е�DumpPhyAddr��ַ��������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
VOS_INT __init Om_QueryDumpPhyAddr(VOS_CHAR *pucChar)
{
    g_stBbpDumpFixDdr.ulPhyAddr = (VOS_UINT32)simple_strtoul(pucChar, VOS_NULL, VOS_NULL);

    /* �����ַ��32λ��ʵ��ַ������8�ֽڶ���� */
    if ((VOS_NULL != (g_stBbpDumpFixDdr.ulPhyAddr % 4))
        || (VOS_NULL == g_stBbpDumpFixDdr.ulPhyAddr))
    {
        g_stBbpDumpFixDdr.ulPhyAddr = VOS_NULL;
    }

    return 0;
}

early_param("mdmreglogbase", Om_QueryDumpPhyAddr);

/*****************************************************************************
* �� �� ��  : SocpLogTimeoutParse
*
* ��������  : �ڴ������׶ν�CMD LINE�е�TIMEOUT��С������������
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : ��
*****************************************************************************/
VOS_INT __init Om_QueryDumpPhySize(VOS_CHAR *pucChar)
{
    /* Buffer�Ĵ�С��ByteΪ��λ */
    g_stBbpDumpFixDdr.ulPhySize = (VOS_UINT32)simple_strtoul(pucChar, VOS_NULL, VOS_NULL);

    return 0;
}

early_param("mdmreglogsize", Om_QueryDumpPhySize);
/*lint -restore */

/*****************************************************************************
 �� �� ��  : Om_AcpuPhyMsgProc
 ��������  :
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��22��
    ��    ��   : s00207770
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  Om_AcpuPhyMsgProc( MsgBlock* pMsg )
{
    WPHY_OAM_QUERY_SAMPLE_REQ_STRU     *pstReqMsg;
    WPHY_OAM_QUERY_SAMPLE_CNF_STRU     *pstCnfMsg;

    pstReqMsg   = (WPHY_OAM_QUERY_SAMPLE_REQ_STRU*)pMsg;

    if (ID_OAM_WPHY_QUERY_SAMPLE_REQ == pstReqMsg->enMsgId)
    {
        pstCnfMsg   = (WPHY_OAM_QUERY_SAMPLE_CNF_STRU*)VOS_AllocMsg(ACPU_PID_PAM_OM, sizeof(WPHY_OAM_QUERY_SAMPLE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

        if (VOS_NULL_PTR == pstCnfMsg)
        {
            PS_LOG(ACPU_PID_PAM_OM, 0, PS_PRINT_ERROR,
                "Om_AcpuPhyMsgProc: Msg alloc Error.\n");
            return;
        }

        pstCnfMsg->ulReceiverPid    = pstReqMsg->ulSenderPid;
        pstCnfMsg->enMsgId          = ID_WPHY_OAM_QUERY_SAMPLE_CNF;

        if (VOS_NULL_PTR != g_stBbpDumpFixDdr.ulPhyAddr)
        {
            pstCnfMsg->esRslt       = VOS_TRUE;
            pstCnfMsg->ulPhyAddr    = g_stBbpDumpFixDdr.ulPhyAddr;
            pstCnfMsg->ulPhySize    = g_stBbpDumpFixDdr.ulPhySize;
        }
        else
        {
            pstCnfMsg->esRslt   = VOS_FALSE;
        }

        if (VOS_OK != VOS_SendMsg(ACPU_PID_PAM_OM, pstCnfMsg))
        {
            PS_LOG(ACPU_PID_PAM_OM, 0, PS_PRINT_ERROR,
                "Om_AcpuPhyMsgProc: Send Msg Error.\n");
        }

        return;
    }

    return;
}


