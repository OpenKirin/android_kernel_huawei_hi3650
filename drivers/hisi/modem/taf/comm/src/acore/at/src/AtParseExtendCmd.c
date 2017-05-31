

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "AtCheckFunc.h"




/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e960*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_PARSEEXTENDCMD_C
/*lint +e960*/

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
/* AT��չ�����ʼ״̬״̬�� */
AT_SUB_STATE_STRU AT_E_CMD_NONE_STATE_TAB[]=
{
    /* �����ǰ״̬��ATCMD_T_STATE��atCheckCharPlus�ɹ��������AT_E_CMD_NAME_STATE */
    {    At_CheckCharPlus    ,    AT_E_CMD_NAME_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT��չ������״̬�� */
AT_SUB_STATE_STRU AT_E_CMD_NAME_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_E_CMD_NAME_STATE��atCheck_char�ɹ��������AT_E_CMD_NAME_STATE */
    {    At_CheckChar    ,    AT_E_CMD_NAME_STATE    },

    /* �����ǰ״̬��AT_E_CMD_NAME_STATE��atCheck_equ�ɹ��������AT_E_CMD_SET_STATE */
    {    At_CheckEqu    ,    AT_E_CMD_SET_STATE    },

    /* �����ǰ״̬��AT_E_CMD_NAME_STATE��atCheck_req�ɹ��������AT_E_CMD_READ_STATE */
    {    At_CheckReq    ,    AT_E_CMD_READ_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT��չ����Ⱥ�״̬�� */
AT_SUB_STATE_STRU AT_E_CMD_SET_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_E_CMD_SET_STATE��atCheck_req�ɹ��������AT_E_CMD_TEST_STATE */
    {    At_CheckReq    ,    AT_E_CMD_TEST_STATE    },

    /* �����ǰ״̬��AT_E_CMD_SET_STATE��atCheck_char�ɹ��������AT_E_CMD_PARA_STATE */
    {    At_CheckChar    ,    AT_E_CMD_PARA_STATE    },

    /* �����ǰ״̬��AT_E_CMD_SET_STATE��atCheck_colon�ɹ��������AT_E_CMD_COLON_STATE */
    {    atCheckComma    ,    AT_E_CMD_COLON_STATE    },

    /* �����ǰ״̬��AT_E_CMD_SET_STATE��atCheck_quot�ɹ��������AT_E_CMD_LEFT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_E_CMD_LEFT_QUOT_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT��չ�������״̬�� */
AT_SUB_STATE_STRU AT_E_CMD_PARA_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_E_CMD_PARA_STATE��atCheck_char�ɹ��������AT_E_CMD_PARA_STATE */
    {    At_CheckChar    ,    AT_E_CMD_PARA_STATE    },

    /* �����ǰ״̬��AT_E_CMD_PARA_STATE��atCheck_char�ɹ��������AT_E_CMD_PARA_STATE */
    {    atCheckblank    ,   AT_E_CMD_PARA_STATE    },

    /* �����ǰ״̬��AT_E_CMD_PARA_STATE��atCheckColon�ɹ��������AT_E_CMD_PARA_STATE */
    {    atCheckColon    ,   AT_E_CMD_PARA_STATE    },

    /* �����ǰ״̬��AT_E_CMD_PARA_STATE��atCheckComma�ɹ��������AT_E_CMD_COLON_STATE */
    {    atCheckComma    ,   AT_E_CMD_COLON_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT��չ�����״̬�� */
AT_SUB_STATE_STRU AT_E_CMD_COLON_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_E_CMD_COLON_STATE��atCheck_char�ɹ��������AT_E_CMD_PARA_STATE */
    {    At_CheckChar    ,    AT_E_CMD_PARA_STATE    },

    /* �����ǰ״̬��AT_E_CMD_COLON_STATE��atCheck_colon�ɹ��������AT_E_CMD_COLON_STATE */
    {    atCheckComma    ,    AT_E_CMD_COLON_STATE    },

    /* �����ǰ״̬��AT_E_CMD_COLON_STATE��atCheck_quot�ɹ��������AT_E_CMD_LEFT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_E_CMD_LEFT_QUOT_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT��չ����������״̬�� */
AT_SUB_STATE_STRU AT_E_CMD_LEFT_QUOT_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_E_CMD_LEFT_QUOT_STATE��atCheck_char�ɹ��������AT_E_CMD_LEFT_QUOT_STATE */
    {    At_CheckNoQuot    ,    AT_E_CMD_LEFT_QUOT_STATE    },

    /* �����ǰ״̬��AT_E_CMD_LEFT_QUOT_STATE��atCheck_quot�ɹ��������AT_E_CMD_RIGHT_QUOT_STATE */
    {    At_CheckQuot    ,    AT_E_CMD_RIGHT_QUOT_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT��չ����������״̬�� */
AT_SUB_STATE_STRU AT_E_CMD_RIGHT_QUOT_STATE_TAB[]=
{
    /* �����ǰ״̬��AT_E_CMD_RIGHT_QUOT_STATE��atCheck_colon�ɹ��������AT_E_CMD_COLON_STATE */
    {    atCheckComma    ,    AT_E_CMD_COLON_STATE    },

    /* �����ǰ״̬��AT_E_CMD_RIGHT_QUOT_STATE��atCheck_char�ɹ��������AT_E_CMD_RIGHT_QUOT_STATE */
    {    At_CheckChar     ,    AT_E_CMD_RIGHT_QUOT_STATE    },

    /* �����ǰ״̬��AT_E_CMD_RIGHT_QUOT_STATE��atCheck_quot�ɹ��������AT_E_CMD_RIGHT_QUOT_STATE */
    {    At_CheckQuot     ,    AT_E_CMD_RIGHT_QUOT_STATE    },

    /* ��״̬����� */
    {    NULL    ,    AT_BUTT_STATE    },
};

/* AT������״̬�� */
AT_MAIN_STATE_STRU AT_E_CMD_MAIN_STATE_TAB[] =
{
    /* �����ǰ״̬��AT_NONE_STATE�������AT_E_CMD_NONE_STATE_TAB��״̬�� */
    {    AT_NONE_STATE    ,    AT_E_CMD_NONE_STATE_TAB    },

    /* �����ǰ״̬��AT_E_CMD_NAME_STATE�������AT_E_CMD_NAME_STATE_TAB��״̬�� */
    {    AT_E_CMD_NAME_STATE    ,    AT_E_CMD_NAME_STATE_TAB    },

    /* �����ǰ״̬��AT_E_CMD_SET_STATE�������AT_E_CMD_SET_STATE_TAB��״̬�� */
    {    AT_E_CMD_SET_STATE    ,    AT_E_CMD_SET_STATE_TAB    },

    /* �����ǰ״̬��AT_E_CMD_PARA_STATE�������AT_E_CMD_PARA_STATE_TAB��״̬�� */
    {    AT_E_CMD_PARA_STATE    ,    AT_E_CMD_PARA_STATE_TAB    },

    /* �����ǰ״̬��AT_E_CMD_COLON_STATE�������AT_E_CMD_COLON_STATE_TAB��״̬�� */
    {    AT_E_CMD_COLON_STATE    ,    AT_E_CMD_COLON_STATE_TAB    },

    /* �����ǰ״̬��AT_E_CMD_LEFT_QUOT_STATE�������AT_E_CMD_LEFT_QUOT_STATE_TAB��״̬�� */
    {    AT_E_CMD_LEFT_QUOT_STATE    ,    AT_E_CMD_LEFT_QUOT_STATE_TAB    },

    /* �����ǰ״̬��AT_E_CMD_RIGHT_QUOT_STATE�������AT_E_CMD_RIGHT_QUOT_STATE_TAB��״̬�� */
    {    AT_E_CMD_RIGHT_QUOT_STATE    ,    AT_E_CMD_RIGHT_QUOT_STATE_TAB    },

    /* ��״̬����� */
    {    AT_BUTT_STATE    ,    NULL    },
};

/******************************************************************************
 ��������: atParseExtendCmd
 ��������: ����AT��չ�����ַ���,�ó�������,����,��������,�����������

 ����˵��:
   pData [in] ������ַ���
   usLen [in] �ַ����ĳ���

 �� �� ֵ:
    AT_SUCCESS: �ɹ�
    AT_ERROR: ʧ��

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2009-08-11]
 2.��    ��   : 2013��03��11��
   ��    ��   : l00198894
   �޸�����   : Body SAR��Ŀ

******************************************************************************/

VOS_UINT32 atParseExtendCmd( VOS_UINT8 * pData, VOS_UINT16 usLen)
{
    AT_STATE_TYPE_ENUM curr_state = AT_NONE_STATE;  /*  ���ó�ʼ״̬ */
    AT_STATE_TYPE_ENUM new_state = AT_NONE_STATE;   /*  ���ó�ʼ״̬ */
    VOS_UINT8 *pucCurrPtr = pData;                  /*  ָ��ǰ���ڴ�����ַ�*/
    VOS_UINT8 *pucCopyPtr = pData;                  /*  �������ݵ���ʼָ�� */
    VOS_UINT16 usLength = 0;                        /*  ��¼��ǰ�Ѿ�������ַ�����*/

    /* ���η����ַ����е�ÿ���ַ�*/
    while(usLength++ < usLen)                  /* ���αȽ�ÿ���ַ� */
    {
        curr_state = new_state;                 /* ��ǰ״̬����Ϊ��״̬*/

        /*  ���ݵ�ǰ������ַ��͵�ǰ״̬���õ���״̬*/
        new_state = atFindNextMainState(AT_E_CMD_MAIN_STATE_TAB,*pucCurrPtr,curr_state);

        switch(new_state)                       /* ״̬����*/
        {
        case AT_E_CMD_NAME_STATE:               /* ��չ������״̬*/
            if(curr_state != new_state)         /* ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                g_stATParseCmd.ucCmdFmtType = AT_EXTEND_CMD_TYPE;           /* ������������*/
                g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* ���������������*/

                pucCopyPtr = pucCurrPtr;            /* ׼��������չ����������*/
            }
            break;

        case AT_E_CMD_SET_STATE:                /* AT��չ����Ⱥ�״̬ */
            /* �洢��������ȫ�ֱ����� */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;  /* ���������������*/
            g_stATParseCmd.stCmdName.usCmdNameLen = (VOS_UINT16)(pucCurrPtr - pucCopyPtr);
            if(g_stATParseCmd.stCmdName.usCmdNameLen < sizeof(g_stATParseCmd.stCmdName.aucCmdName))
            {
                atRangeCopy(g_stATParseCmd.stCmdName.aucCmdName,pucCopyPtr,pucCurrPtr);
            }
            else
            {
                return AT_ERROR;                  /* ���ش��� */
            }
            break;

        case AT_E_CMD_PARA_STATE:               /* AT��չ�������״̬ */
        case AT_E_CMD_LEFT_QUOT_STATE:          /* AT��չ����������״̬ */
            if(curr_state != new_state)         /* ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                pucCopyPtr = pucCurrPtr;            /* ׼�����ղ�������*/
            }
            break;

        case AT_E_CMD_COLON_STATE:              /* AT��չ�����״̬ */
            if((curr_state != new_state) && (AT_E_CMD_SET_STATE != curr_state))         /* ��״̬���ֲ����ڵ�ǰ״̬*/
            {
                /* �洢������ȫ�ֱ����� */
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
                {
                    return AT_ERROR;
                }

            }
            else
            {
                /*������������,����������*/
                if(ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, 0))
                {
                    return AT_ERROR;
                }

            }
            break;

        case AT_E_CMD_READ_STATE:                   /* AT��չ�����ѯ����״̬ */

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

            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_READ_CMD;   /* ���������������*/

            break;

        case AT_E_CMD_TEST_STATE:                   /* AT��չ������Բ���״̬ */
            g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_TEST_CMD;   /* ���������������*/
            break;

        case AT_BUTT_STATE:                         /* ��Ч״̬ */
            return AT_ERROR;                      /* ���ش��� */

        default:
            break;
        }
        pucCurrPtr++;                                 /* ����������һ���ַ�*/
    }

    switch(new_state)                               /* ��������״̬�ж�*/
    {
    case AT_E_CMD_PARA_STATE:                       /* AT��չ�������״̬ */
    case AT_E_CMD_RIGHT_QUOT_STATE:                 /* AT��չ����������״̬ */

        /* �洢������ȫ�ֱ����� */
        if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, (VOS_UINT16)(pucCurrPtr - pucCopyPtr)))
        {
            return AT_ERROR;
        }

        break;

    case AT_E_CMD_NAME_STATE:                   /* AT��չ�����ѯ����״̬ */

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

        g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_CMD_NO_PARA;   /* ���������������*/

        break;

    case AT_E_CMD_COLON_STATE:                      /* AT�����������޲εĶ��� */

        if (ERR_MSP_SUCCESS != atfwParseSaveParam(pucCopyPtr, 0))
        {
            return AT_ERROR;
        }

        break;

    case AT_E_CMD_SET_STATE:                        /* AT��չ����Ⱥ�״̬ */
    case AT_E_CMD_TEST_STATE:                       /* AT��չ�����ѯ����״̬ */
    case AT_E_CMD_READ_STATE:                       /* AT��չ������Բ���״̬ */
        break;

    default:
        return AT_ERROR;                          /* ���ش���*/
    }
    return AT_SUCCESS;                              /*  ������ȷ*/
}

/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
/*****************************************************************************
 �� �� ��  : AT_ParseSetDockCmd
 ��������  : ��鵱ǰ�Ƿ�DOCK�������
             ����DOCK�������
             ��ȡ�������ƺͳ��ȣ������ַ����ͳ��ȵ�AT��ȫ�ֱ���
             �޸�ATģ���g_stATParseCmd.ucCmdOptType��gucAtCmdFmtType��gucAtParaIndex
 �������  : VOS_UINT8                          *pucData
             VOS_UINT16                          usLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32     AT_FAILURE ����DOCK��������
                            AT_SUCCESS   ��DOCK��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��9��26��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��2��25��
    ��    ��   : l60609
    �޸�����   : DSDA PHASE III
*****************************************************************************/
VOS_UINT32 AT_ParseSetDockCmd(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usLen
)
{
    VOS_INT8                            cRet;
    VOS_UINT16                          usCmdlen;
    VOS_UINT32                          ulPos;
    VOS_UINT8                          *pucDataPara = VOS_NULL_PTR;
    AT_PARSE_CMD_NAME_TYPE_STRU         stAtCmdName;

    PS_MEM_SET(&stAtCmdName, 0, sizeof(stAtCmdName));

    if (0 == usLen)
    {
        return AT_FAILURE;
    }

    pucDataPara = (VOS_UINT8*)PS_MEM_ALLOC(WUEPS_PID_AT, usLen);

    if (VOS_NULL_PTR == pucDataPara)
    {
        AT_ERR_LOG("AT_ParseSetDockCmd: pucDataPara Memory malloc failed!");
        return AT_FAILURE;
    }

    PS_MEM_CPY(pucDataPara, pucData, usLen);

    /* ȥ���ַ����е��˸�� */
    if (AT_FAILURE == At_ScanDelChar(pucDataPara, &usLen))
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }

    /* ��������ַ�������С��"AT^DOCK="����ֱ�ӷ���AT_FAILURE */
    usCmdlen = (VOS_UINT16)VOS_StrLen("AT^DOCK=");
    if (usLen < usCmdlen)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }

    /* AT����ͷ�ַ�ת��д */
    At_UpString(pucDataPara, usCmdlen);

    /* ��������ַ���ͷ������"AT^DOCK="ֱ�ӷ���AT_FAILURE */
    cRet = VOS_StrNiCmp((VOS_CHAR *)pucDataPara, "AT^DOCK=", usCmdlen);
    if (0 != cRet)
    {
        PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
        return AT_FAILURE;
    }

    /* ��ȡ����(����������ǰ׺AT)���Ƽ����� */
    ulPos = VOS_StrLen("AT");
    stAtCmdName.usCmdNameLen = (VOS_UINT16)VOS_StrLen("^DOCK");
    PS_MEM_CPY(stAtCmdName.aucCmdName,
               (pucDataPara + ulPos),
               stAtCmdName.usCmdNameLen);
    stAtCmdName.aucCmdName[stAtCmdName.usCmdNameLen] = '\0';
    ulPos += stAtCmdName.usCmdNameLen;

    ulPos += VOS_StrLen("=");

    /* ��ȡ����Ĳ����ַ��������� */
    gastAtParaList[0].usParaLen = usLen - (VOS_UINT16)ulPos;
    PS_MEM_CPY(gastAtParaList[0].aucPara,
               (pucDataPara + ulPos),
               gastAtParaList[0].usParaLen);

    /* �����������ͣ��������ͺͲ������� */
    gucAtParaIndex  = 1;
    g_stATParseCmd.ucCmdOptType = AT_CMD_OPT_SET_PARA_CMD;
    gucAtCmdFmtType = AT_EXTEND_CMD_TYPE;

    PS_MEM_FREE(WUEPS_PID_AT, pucDataPara);
    return AT_SUCCESS;
}
/* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


