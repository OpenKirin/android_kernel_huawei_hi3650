

#include "AtCheckFunc.h"

#include "msp_errno.h"



/* AT S�����ʼ״̬�� */
AT_SUB_STATE_STRU AT_S_CMD_NONE_STATE_TAB[]=
{
    /* �����ǰ״̬��ATCMD_NONE_STATE��atCheckCharS�ɹ��������AT_S_CMD_NAME_STATE */
    {    At_CheckCharS    ,    AT_S_CMD_NAME_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT S������״̬�� */
AT_SUB_STATE_STRU AT_S_CMD_NAME_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_S_CMD_NAME_STATE��atCheck_num�ɹ��������AT_S_CMD_NAME_STATE */
    {    At_CheckDigit    ,    AT_S_CMD_NAME_STATE    },

    /* �����ǰ״̬��AT_S_CMD_NAME_STATE��atCheck_equ�ɹ��������AT_S_CMD_SET_STATE */
    {    At_CheckEqu    ,    AT_S_CMD_SET_STATE    },

    /* �����ǰ״̬��AT_S_CMD_NAME_STATE��atCheck_req�ɹ��������AT_S_CMD_READ_STATE */
    {    At_CheckReq    ,    AT_S_CMD_READ_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};


/* AT S��������״̬�� */
AT_SUB_STATE_STRU AT_S_CMD_SET_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_S_CMD_SET_STATE��atCheck_num�ɹ��������AT_S_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_S_CMD_PARA_STATE    },

    /* �����ǰ״̬��AT_S_CMD_SET_STATE��atCheck_req�ɹ��������AT_S_CMD_TEST_STATE */
    {    At_CheckReq    ,    AT_S_CMD_TEST_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT S�������״̬�� */
AT_SUB_STATE_STRU AT_S_CMD_PARA_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_S_CMD_PARA_STATE��atCheck_num�ɹ��������AT_S_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_S_CMD_PARA_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};


/* AT S������״̬�� */
AT_MAIN_STATE_STRU AT_S_CMD_MAIN_STATE_TAB[] =
{
    /* �����ǰ״̬��AT_NONE_STATE�������AT_S_CMD_NONE_STATE_TAB��״̬�� */
    {    AT_NONE_STATE    ,    AT_S_CMD_NONE_STATE_TAB    },

    /* �����ǰ״̬��ATCMD_B_CMD_STATE�������AT_S_CMD_NAME_STATE_TAB��״̬�� */
    {    AT_S_CMD_NAME_STATE    ,    AT_S_CMD_NAME_STATE_TAB    },

    /* �����ǰ״̬��AT_S_CMD_SET_STATE�������AT_S_CMD_SET_STATE_TAB��״̬�� */
    {    AT_S_CMD_SET_STATE    ,    AT_S_CMD_SET_STATE_TAB    },

    /* �����ǰ״̬��AT_S_CMD_PARA_STATE�������AT_S_CMD_PARA_STATE_TAB��״̬�� */
    {    AT_S_CMD_PARA_STATE    ,    AT_S_CMD_PARA_STATE_TAB    },

    /* ��״̬����� */
    {    AT_BUTT_STATE    ,    NULL    },
};

/******************************************************************************
 ��������: atParseSCmd
 ��������: ����AT�����ַ���,�ó�������,����,��������,�����������

 ����˵��:
   pData [in] ������ַ���
   usLen [in] �ַ����ĳ���

 �� �� ֵ:
    AT_SUCCESS: �ɹ�
    AT_ERROR: ʧ��

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atParseSCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  ���ó�ʼ״̬ */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  ���ó�ʼ״̬ */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  ָ��ǰ���ڴ�����ַ�*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  �������ݵ���ʼָ�� */
    VOS_UINT16 usLength = 0;                        /*  ��¼��ǰ�Ѿ�������ַ�����*/

    /* ���η����ַ����е�ÿ���ַ� */
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))                      /* ���αȽ�ÿ���ַ� */
    {
        curr_state = new_state;                     /*  ��ǰ״̬����Ϊ��״̬*/

        /*  ���ݵ�ǰ������ַ��͵�ǰ״̬���õ���״̬*/
        new_state = atFindNextMainState(AT_S_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch (new_state)                        /*  ״̬����*/
        {
        case AT_S_CMD_NAME_STATE:                /*  S������״̬*/
            if (curr_state != new_state)          /*  ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;         /*  ������������*/
                g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /*  ���������������*/
                pucCopyPtr = pucCurrPtr;             /*  ׼������S������*/
            }
            break;

        case AT_S_CMD_SET_STATE:                 /* AT S����Ⱥ�״̬ */

            /* �洢��������ȫ�ֱ����� */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;  /* ���������������*/

            g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
            if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
            {
                atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_ERROR;                  /* ���ش��� */
            }
            break;

        case AT_S_CMD_PARA_STATE:               /* AT S�������״̬ */
            if (curr_state != new_state)         /* ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                pucCopyPtr = pucCurrPtr;            /* ׼������ S����������*/
            }
            break;

        case AT_S_CMD_READ_STATE:                  /* AT S�����ѯ����״̬ */

            /* �洢��������ȫ�ֱ����� */
            g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
            if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
            {
                atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_ERROR;                  /* ���ش��� */
            }

            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;  /* ���������������*/

            break;

        case AT_S_CMD_TEST_STATE:                  /* AT S������Բ���״̬ */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;  /* ���������������*/
            break;

        default:
            return AT_ERROR;                  /* ���ش��� */
        }
        pucCurrPtr++;                             /*  ����������һ���ַ�*/
    }

    switch(new_state)                           /*  ��������״̬�ж�*/
    {
    case AT_S_CMD_PARA_STATE:                   /* AT S�������״̬ */

        /* �洢������ȫ�ֱ����� */
        if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_ERROR;
        }

        break;

    case AT_S_CMD_NAME_STATE:                   /* AT S����״̬*/
        /* �洢��������ȫ�ֱ����� */
        g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
        if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
        {
            atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
        }
        else
        {
            return AT_ERROR;                  /* ���ش��� */
        }
        break;

    case AT_S_CMD_SET_STATE:                         /* ��Ч״̬ */
    case AT_S_CMD_READ_STATE:                         /* ��ʼ״̬ */
    case AT_S_CMD_TEST_STATE:                         /* ��ʼ״̬ */
        break;

    default:
        return AT_ERROR;                  /* ���ش��� */
    }
    return AT_SUCCESS;                          /*  ������ȷ*/
}



