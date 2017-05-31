

#include "AtCheckFunc.h"

#include "msp_errno.h"



/* AT�����ʼ״̬�� */
AT_SUB_STATE_STRU AT_DM_CMD_NONE_STATE_TAB[]=
{
    /* �����ǰ״̬��ATCMD_NONE_STATE��atCheckCharD�ɹ��������AT_DM_CMD_NAME_STATE */
    {    At_CheckCharD    ,    AT_DM_CMD_NAME_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT DM����������״̬�� */
AT_SUB_STATE_STRU AT_DM_CMD_NAME_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_DM_CMD_NAME_STATE��At_CheckCharStar�ɹ��������AT_DM_CMD_STAR_STATE */
    {    At_CheckCharStar    ,    AT_DM_CMD_STAR_STATE    },

    /* �����ǰ״̬��AT_D_CMD_NAME_STATE��At_CheckCharWell�ɹ��������AT_DM_CMD_WELL_STATE */
    {    At_CheckCharWell    ,    AT_DM_CMD_WELL_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT DM�����ַ�״̬�� */
AT_SUB_STATE_STRU AT_DM_CMD_CHAR_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_DM_CMD_NAME_STATE��At_CheckCharStar�ɹ��������AT_DM_CMD_STAR_STATE */
    {    At_CheckCharStar    ,    AT_DM_CMD_STAR_STATE    },

    /* �����ǰ״̬��AT_DM_CMD_NAME_STATE��At_CheckCharStar�ɹ��������AT_DM_CMD_WELL_STATE */
    {    At_CheckCharWell    ,    AT_DM_CMD_WELL_STATE    },

    /* �����ǰ״̬��AT_DM_CMD_NAME_STATE��At_CheckCharStar�ɹ��������AT_DM_CMD_NUM_STATE */
    {    At_CheckDmChar    ,    AT_DM_CMD_NUM_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT������״̬�� */
AT_MAIN_STATE_STRU AT_DM_CMD_MAIN_STATE_TAB[] =
{
    /* �����ǰ״̬��AT_NONE_STATE�������AT_DM_CMD_NONE_STATE_TAB��״̬�� */
    {    AT_NONE_STATE    ,    AT_DM_CMD_NONE_STATE_TAB    },

    /* �����ǰ״̬��AT_DM_CMD_NAME_STATE�������AT_DM_CMD_NAME_STATE_TAB��״̬�� */
    {    AT_DM_CMD_NAME_STATE    ,    AT_DM_CMD_NAME_STATE_TAB    },

    /* �����ǰ״̬��AT_DM_CMD_NUM_STATE�������AT_DM_CMD_CHAR_STATE_TAB��״̬�� */
    {    AT_DM_CMD_NUM_STATE    ,    AT_DM_CMD_CHAR_STATE_TAB    },

    /* �����ǰ״̬��AT_DM_CMD_STAR_STATE�������AT_DM_CMD_CHAR_STATE_TAB��״̬�� */
    {    AT_DM_CMD_STAR_STATE    ,    AT_DM_CMD_CHAR_STATE_TAB    },

    /* �����ǰ״̬��AT_DM_CMD_WELL_STATE�������AT_DM_CMD_CHAR_STATE_TAB��״̬�� */
    {    AT_DM_CMD_WELL_STATE    ,    AT_DM_CMD_CHAR_STATE_TAB    },

    /* ��״̬����� */
    {    AT_BUTT_STATE    ,    NULL    },
};

/******************************************************************************
 ��������: atParseDMCmd
 ��������: ����AT�����ַ���,�ó�������,����,��������,�����������
              D*<GPRS_SC>[*[<called_address>][*[<L2P>][*[<cid>]]]]#
              D*<GPRS_SC_IP>[*<cid>[,<cid>]]#
              D**61*+1812555673*11*25#  ---  ���в���ҵ��,����������Ҫ����MMI�ӿ�
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

VOS_UINT32 atParseDMCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  ���ó�ʼ״̬ */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  ���ó�ʼ״̬ */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  ָ��ǰ���ڴ�����ַ�*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  �������ݵ���ʼָ�� */
    VOS_UINT16 usLength = 0;                        /*  ��¼��ǰ�Ѿ�������ַ�����*/

    /* ���η����ַ����е�ÿ���ַ�*/
    while ( (usLength++ < usLen) && (g_stATParseCmd.ucParaIndex < AT_MAX_PARA_NUMBER))       /* ���αȽ�ÿ���ַ� */
    {
        curr_state = new_state;                  /* ��ǰ״̬����Ϊ��״̬*/

        /* ���ݵ�ǰ������ַ��͵�ǰ״̬���õ���״̬*/
        new_state = atFindNextMainState(AT_DM_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch (new_state)                        /* ״̬����*/
        {
        case AT_DM_CMD_NAME_STATE:                /* AT DM����������״̬ */
            g_stATParseCmd.ucCmdFmtType = AT_BASIC_CMD_TYPE;     /* ������������*/
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* ���������������*/
            pucCopyPtr = pucCurrPtr;                 /* ׼������DM����������*/
            break;

        /* �п������ֳ��ȹ��磬����gucAtParaIndex���� */
        case AT_DM_CMD_NUM_STATE:                /* AT DM�����ַ�״̬ */
            if (curr_state != new_state)          /* ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                /* �洢������ȫ�ֱ����� */
                if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_FAILURE;
                }

                pucCopyPtr = pucCurrPtr;                /* ׼��������һ������*/
            }
            break;

        case AT_DM_CMD_WELL_STATE:                /* AT DM�����ַ�#״̬ */
        case AT_DM_CMD_STAR_STATE:                /* AT DM�����ַ�*״̬ */
            if (AT_DM_CMD_NAME_STATE == curr_state)
            {
                g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
                if (g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
                {
                    atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
                }
                else
                {
                    return AT_FAILURE;                  /* ���ش��� */
                }
                pucCopyPtr = pucCurrPtr;             /* ׼�����ղ���*/
            }
            else
            {
                /* �洢������ȫ�ֱ����� */
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_FAILURE;
                }

                pucCopyPtr = pucCurrPtr;                /* ׼��������һ������*/
            }
            break;

        default:
            return AT_FAILURE;                  /* ���ش��� */
        }

        pucCurrPtr++;                             /* ����������һ���ַ�*/
    }

    switch (new_state)                           /* ��������״̬�ж�*/
    {
    case AT_DM_CMD_WELL_STATE:                   /* AT DM�����ַ�#״̬ */
        break;

    default:
        return AT_FAILURE;                      /* ���ش���*/
    }
    
    return AT_SUCCESS;                          /* ������ȷ*/
}



