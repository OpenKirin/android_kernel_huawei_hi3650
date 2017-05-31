

#include "AtCheckFunc.h"

#include "msp_errno.h"



/* AT�����ʼ��״̬�� */
AT_SUB_STATE_STRU AT_B_CMD_NONE_STATE_TAB[]=
{
    /* �����ǰ״̬��ATCMD_NONE_STATE��atCheckBasicCmdName�ɹ��������AT_B_CMD_NAME_STATE */
    {    atCheckBasicCmdName    ,    AT_B_CMD_NAME_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT����������״̬�� */
AT_SUB_STATE_STRU AT_B_CMD_NAME_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_B_CMD_NAME_STATE��atCheckBasicCmdName�ɹ��������AT_B_CMD_NAME_STATE */
    {    atCheckBasicCmdName    ,    AT_B_CMD_NAME_STATE    },

    /* �����ǰ״̬��AT_B_CMD_NAME_STATE��At_CheckDigit�ɹ��������AT_B_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_B_CMD_PARA_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT�����������״̬�� */
AT_SUB_STATE_STRU AT_B_CMD_PARA_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_B_CMD_NAME_STATE��At_CheckDigit�ɹ��������AT_B_CMD_PARA_STATE */
    {    At_CheckDigit    ,    AT_B_CMD_PARA_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};



/* AT����������״̬�� */
AT_MAIN_STATE_STRU AT_B_CMD_MAIN_STATE_TAB[] =
{
    /* �����ǰ״̬��AT_NONE_STATE�������AT_B_CMD_NONE_STATE_TAB��״̬�� */
    {    AT_NONE_STATE    ,    AT_B_CMD_NONE_STATE_TAB    },

    /* �����ǰ״̬��AT_B_CMD_NAME_STATE�������AT_B_CMD_NAME_STATE_TAB��״̬�� */
    {    AT_B_CMD_NAME_STATE    ,    AT_B_CMD_NAME_STATE_TAB    },

    /* �����ǰ״̬��AT_B_CMD_PARA_STATE�������AT_B_CMD_PARA_STATE_TAB��״̬�� */
    {    AT_B_CMD_PARA_STATE    ,    AT_B_CMD_PARA_STATE_TAB    },

    /* ��״̬����� */
    {    AT_BUTT_STATE    ,    NULL    },

};


/* AT�����ʼ��״̬�� */
AT_SUB_STATE_STRU AT_W_CMD_NAME_STATE_TAB[]=
{
    /* �����ǰ״̬��ATCMD_NONE_STATE��At_CheckBasicCmdName�ɹ��������AT_B_CMD_NAME_STATE */
    {    At_CheckChar0x26    ,    AT_W_CMD_F_STATE    },

    {    At_CheckCharE    ,    AT_W_CMD_PARA_STATE    },
    {    At_CheckCharI,        AT_W_CMD_PARA_STATE    },

    {    At_CheckCharV    ,    AT_W_CMD_PARA_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT����������״̬�� */
AT_SUB_STATE_STRU AT_W_CMD_PARA_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_B_CMD_NAME_STATE��At_CheckChar1�ɹ��������AT_W_CMD_NAME_STATE */
    {    At_CheckChar1    ,    AT_W_CMD_NAME_STATE    },

    /* �����ǰ״̬��AT_B_CMD_NAME_STATE��At_CheckChar0�ɹ��������AT_W_CMD_NAME_STATE */
    {    At_CheckChar0    ,    AT_W_CMD_NAME_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT����������״̬�� */
AT_SUB_STATE_STRU AT_W_CMD_0x26_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_B_CMD_NAME_STATE��At_CheckCharF�ɹ��������AT_W_CMD_NAME_STATE */
    {    At_CheckCharF    ,    AT_W_CMD_NAME_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};



/* AT����������״̬�� */
AT_MAIN_STATE_STRU AT_W_CMD_MAIN_STATE_TAB[] =
{
    /* �����ǰ״̬��AT_NONE_STATE�������AT_B_CMD_NONE_STATE_TAB��״̬�� */
    {    AT_NONE_STATE    ,    AT_W_CMD_NAME_STATE_TAB    },

    /* �����ǰ״̬��AT_NONE_STATE�������AT_B_CMD_NONE_STATE_TAB��״̬�� */
    {    AT_W_CMD_NAME_STATE    ,    AT_W_CMD_NAME_STATE_TAB    },

    /* �����ǰ״̬��AT_B_CMD_NAME_STATE�������AT_B_CMD_NAME_STATE_TAB��״̬�� */
    {    AT_W_CMD_PARA_STATE    ,    AT_W_CMD_PARA_STATE_TAB    },

    /* �����ǰ״̬��AT_B_CMD_NAME_STATE�������AT_B_CMD_NAME_STATE_TAB��״̬�� */
    {    AT_W_CMD_F_STATE    ,    AT_W_CMD_0x26_STATE_TAB    },

    /* ��״̬����� */
    {    AT_BUTT_STATE    ,    NULL    },

};

/******************************************************************************
 ��������: atParseBasicCmd
 ��������: ����AT���������ַ���,�ó�������,����,��������,�����������

 ����˵��:
   pData [in] ������ַ���
   usLen [in] �ַ����ĳ���

 �� �� ֵ:
    AT_SUCCESS: �ɹ�
    AT_FAILURE: ʧ��

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atParseBasicCmd(VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  ���ó�ʼ״̬ */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  ���ó�ʼ״̬ */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  ָ��ǰ���ڴ�����ַ�*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  �������ݵ���ʼָ�� */
    VOS_UINT16 usLength = 0;                        /*  ��¼��ǰ�Ѿ�������ַ�����*/

    if(AT_FAILURE == atCheckBasicCmdName(*pucCurrPtr))
    {
        return AT_ERROR;
    }

    /* ���η����ַ����е�ÿ���ַ�*/
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))                    /* ���αȽ�ÿ���ַ� */
    {
        curr_state = new_state;                 /*  ��ǰ״̬����Ϊ��״̬*/

        /*  ���ݵ�ǰ������ַ��͵�ǰ״̬���õ���״̬*/
        new_state = atFindNextMainState(AT_B_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch(new_state)                       /*  ״̬����*/
        {
        case AT_B_CMD_NAME_STATE:               /*  ����������״̬*/
            if(curr_state != new_state)         /*  ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;            /*  ������������*/
                g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /*  ���������������*/
                pucCopyPtr = pucCurrPtr;            /*  ׼�����ջ�������������*/
            }
            break;

        case AT_B_CMD_PARA_STATE:               /* AT�����������״̬ */
            if(curr_state != new_state)         /* ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                /* �洢��������ȫ�ֱ����� */
                g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
                if(g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
                {
                    atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                      /* ���ش��� */
                }

                g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;  /* ���������������*/
                pucCopyPtr = pucCurrPtr;                    /* ׼�����ղ���*/
            }
            break;

        default:
            return AT_FAILURE;                  /* ���ش��� */
        }
        pucCurrPtr++;                           /*  ����������һ���ַ�*/
    }

    switch(new_state)                           /*  ��������״̬�ж�*/
    {
    case AT_B_CMD_NAME_STATE:                   /*  ����������״̬*/

        /* �洢��������ȫ�ֱ����� */
        g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
        if(g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
        {
            atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
        }
        else
        {
            return AT_FAILURE;                  /* ���ش��� */
        }
        break;

    case AT_B_CMD_PARA_STATE:                   /*  ����������״̬*/
        /* �洢������ȫ�ֱ����� */
        if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_FAILURE;
        }

        break;

    default:                                    /* ��������״̬*/
        return AT_FAILURE;                      /* ���ش��� */
    }

    return AT_SUCCESS;                          /*  ������ȷ*/
}

/******************************************************************************
 ��������: atCheckCharWcmd
 ��������: �Ƚϡ�ƥ���ַ�&

 ����˵��:
   pData [in] ������ַ���
   usLen [in] �ַ����ĳ���

 �� �� ֵ:
    AT_SUCCESS: �ɹ�
    AT_FAILURE: ʧ��

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atCheckCharWcmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    VOS_UINT8 Char = *pData;

    if(usLen < 3)   /* Ϊ���д����ƣ��񲻶�����ʧ�ܣ� */
    {
        return AT_FAILURE;
    }

    if( ('d' != Char) && ('D' != Char) && ('h' != Char) && ('H' != Char) && ('a' != Char) && ('A' != Char))
    {
        return AT_SUCCESS;
    }
    else
    {
        return AT_FAILURE;
    }
}

/******************************************************************************
 ��������: atParseWCmd
 ��������: ����AT���������ַ���,�ó�������,����,��������,�����������

 ����˵��:
   pData [in] ������ַ���
   usLen [in] �ַ����ĳ���

 �� �� ֵ:
    AT_SUCCESS: �ɹ�
    AT_FAILURE: ʧ��

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2009-08-11]
******************************************************************************/

VOS_UINT32 atParseWCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  ���ó�ʼ״̬ */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  ���ó�ʼ״̬ */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  ָ��ǰ���ڴ�����ַ�*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  �������ݵ���ʼָ�� */
    VOS_UINT16 usLength = 0;                        /*  ��¼��ǰ�Ѿ�������ַ�����*/

    At_UpString(pData,usLen);

    /* ���η����ַ����е�ÿ���ַ�*/
    while( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))
    {
        curr_state = new_state;                 /*  ��ǰ״̬����Ϊ��״̬*/

        /*  ���ݵ�ǰ������ַ��͵�ǰ״̬���õ���״̬*/
        new_state = atFindNextMainState(AT_W_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        pucCopyPtr = pucCurrPtr;

        switch(new_state)                       /*  ״̬����*/
        {
        case AT_W_CMD_NAME_STATE:
            if(usLength > 1)
            {
                if('E' == *(pucCopyPtr-1))
                {
                    /* atSetCurClientEtype(*pucCopyPtr - '0'); */
                }
                else if('V' == *(pucCopyPtr-1))
                {
                    /* atSetCurClientVtype(*pucCopyPtr - '0'); */
                }
                else if('&' == *(pucCopyPtr-1))
                {
                    /* atSetFPara(EN_AT_FW_CLIENT_ID_ALL); */
                }
                else
                {

                }
            }
            break;                  /* ���ش��� */

        default:
            break;
        }
        pucCurrPtr++;                           /*  ����������һ���ַ�*/
    }

    switch(new_state)
    {
    case AT_W_CMD_NAME_STATE:
        return AT_OK;                          /*  ������ȷ*/

    default:
        return AT_ERROR;                          /* ���ش��� */
    }
}


