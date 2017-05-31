






#include "diag_msgps.h"
#include "diag_msgmsp.h"
#include "diag_debug.h"
#include "diag_acore_common.h"

#define    THIS_FILE_ID        MSP_FILE_ID_DIAG_MSGPS_C

DIAG_TRANS_HEADER_STRU g_stPSTransHead = {{VOS_NULL, VOS_NULL}, 0};


/*****************************************************************************
 Function Name   : diag_PsTransProcEntry
 Description     : �ú������ڴ����PS͸������
 Input           : VOS_UINT8* pstReq
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2015-06-14  Draft Enact

*****************************************************************************/
VOS_UINT32 diagPsTransProcEntry(DIAG_FRAME_INFO_STRU* pstReq)
{
    return diag_TransReqProcEntry(pstReq, &g_stPSTransHead);
}


/*****************************************************************************
 Function Name   : diag_PsMsgInit
 Description     : MSP ps���ֳ�ʼ��
 Input           : None
 Output          : None
 Return          : None
 History         :

*****************************************************************************/
VOS_VOID diag_PsMsgInit(VOS_VOID)
{
    VOS_UINT32 ulRet;

    /* �����ڵ㱣���ź��� Diag Trans Ps */
    ulRet = VOS_SmBCreate("DTP", 1, VOS_SEMA4_FIFO,&g_stPSTransHead.TransSem);
    if(VOS_OK != ulRet)
    {
        diag_printf("diag_PsMsgInit VOS_SmBCreate failed.\n");
    }

    /* ��ʼ���������� */
    blist_head_init(&g_stPSTransHead.TransHead);

    /*ע��message��Ϣ�ص�*/
    DIAG_MsgProcReg(DIAG_MSG_TYPE_PS,diagPsTransProcEntry);
}


/*****************************************************************************
 Function Name   : DIAG_ShowTransList
 Description     : ���Խӿڣ����ڲ鿴�������Ƿ��в����Ľڵ�
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.c00326366      2015-06-14  Draft Enact

*****************************************************************************/
VOS_VOID DIAG_ShowTransList(VOS_VOID)
{
    LIST_S* me = NULL;

    diag_printf("PS trans header 0x%p, 0x%p.\n", g_stPSTransHead.TransHead.next, g_stPSTransHead.TransHead.prev);

    /*����ź�������*/
    (VOS_VOID)VOS_SmP(g_stPSTransHead.TransSem,0);

    /* �������в���ÿ����������*/
    blist_for_each(me, &g_stPSTransHead.TransHead)
    {
        diag_printf("header 0x%p, 0x%p.\n", me->next, me->prev);
    }
    (VOS_VOID)VOS_SmV(g_stPSTransHead.TransSem);

    return ;
}



