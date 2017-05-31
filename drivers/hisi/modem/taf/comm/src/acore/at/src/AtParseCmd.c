

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "ATCmdProc.h"
#include "AtCheckFunc.h"
#include "AtParseCmd.h"
#include "at_common.h"




/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 -e960 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_AT_PARSECMD_C
/*lint +e767 +e960 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
   3 ��������������
*****************************************************************************/

/*****************************************************************************
   4 ����ʵ��
*****************************************************************************/

/******************************************************************************
 ��������: atFindNextSubState
 ��������: ���������ַ�,����ƥ��ָ����״̬���ÿһ����жϺ���,����ɹ�,
           �򷵻ض�Ӧ����״̬

 ����˵��:
   pSubStateTab [in] ָʾ��ƥ�����״̬��
   ucInputChar [in] ָʾ��ƥ����ַ�

 �� �� ֵ:
    ����ƥ�����״̬

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2009-08-11]
******************************************************************************/
AT_STATE_TYPE_ENUM atFindNextSubState( AT_SUB_STATE_STRU *pSubStateTab,VOS_UINT8 ucInputChar)
{
    VOS_UINT16 usTabIndex = 0;                            /* ��״̬������ */

    /* ���αȽ���״̬��ÿһ��ֱ������ */
    while(AT_BUTT_STATE != pSubStateTab[usTabIndex].next_state)
    {
        if( AT_SUCCESS == pSubStateTab[usTabIndex].pFuncName(ucInputChar))    /* �ж������ַ��Ƿ�ƥ�� */
        {
            return pSubStateTab[usTabIndex].next_state;     /* ����ƥ�����״̬ */
        }
        usTabIndex++;                                               /* ��״̬���������� */
    }
    return AT_BUTT_STATE;
}

/******************************************************************************
 ��������: atFindNextMainState
 ��������: ��������״̬,����ƥ��ָ����״̬��ÿһ���״̬,����ɹ�,��
           �ض�Ӧ����״̬��,�ٸ��������ַ�����״̬��ó���һ����״̬

 ����˵��:
   pMainStateTab [in] ָʾ��ƥ�����״̬��
   ucInputChar [in] ָʾ��ƥ����ַ�
   InputState [in] ����״̬

 �� �� ֵ:
    ���ƥ��ɹ�������atFindNextSubState�������
    ���ƥ��ʧ�ܣ�����AT_BUTT_STATE

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2009-08-11]
******************************************************************************/
AT_STATE_TYPE_ENUM atFindNextMainState(AT_MAIN_STATE_STRU *pMainStateTab,
    VOS_UINT8 ucInputChar,  AT_STATE_TYPE_ENUM InputState)
{
    VOS_UINT16 usTabIndex = 0;                            /* ��״̬������ */

    /* ���αȽ���״̬��ÿһ��ֱ������ */
    while(AT_BUTT_STATE != pMainStateTab[usTabIndex].curr_state)
    {
        if( InputState == pMainStateTab[usTabIndex].curr_state)    /* �ж�����״̬�Ƿ�ƥ�� */
        {
            /* ���״̬ƥ��,����������ַ�Ѱ����һ����״̬ */
            return atFindNextSubState(pMainStateTab[usTabIndex].pSubStateTab,ucInputChar);
        }
        usTabIndex++;
    }
    return AT_BUTT_STATE;
}


/*****************************************************************************
 Prototype      : At_Auc2ul
 Description    : ���ַ���ת���޷�������ֵ
 Input          : nptr ---ָʾ��ת���ִ��Ŀ�ʼ��ַ
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_Auc2ul(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_UINT32 *pRtn)
{
    TAF_UINT32 c     = 0;         /* current Char */
    TAF_UINT32 total = 0;         /* current total */
    TAF_UINT8 Length = 0;         /* current Length */

    c = (TAF_UINT32)*nptr++;

    while(Length++ < usLen)
    {
        if((c >= '0') && (c <= '9'))                /* �ַ���� */
        {
            /* 0xFFFFFFFF = 4294967295 */
            if(((total == 429496729) && (c > '5')) || (total > 429496729))
            {
                return AT_FAILURE;
            }
            total = (10 * total) + (c - '0');        /* accumulate digit */
            c = (TAF_UINT32)(TAF_UINT8)*nptr++;    /* get next Char */
        }
        else
        {
            return AT_FAILURE;
        }
    }

    *pRtn = total;   /* return result, negated if necessary */
    return AT_SUCCESS;
}
/*****************************************************************************
 Prototype      : At_String2Hex
 Description    : ����ַ���ת16����������
 Input          : nptr --- �ַ���
 Output         :
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_String2Hex(TAF_UINT8 *nptr,TAF_UINT16 usLen,TAF_UINT32 *pRtn)
{
    TAF_UINT32 c     = 0;         /* current Char */
    TAF_UINT32 total = 0;         /* current total */
    TAF_UINT8 Length = 0;         /* current Length */

    c = (TAF_UINT32)*nptr++;

    while(Length++ < usLen)
    {
        if( (c  >= '0') && (c  <= '9') )
        {
            c  = c  - '0';
        }
        else if( (c  >= 'a') && (c  <= 'f') )
        {
            c  = (c  - 'a') + 10;
        }
        else if( (c  >= 'A') && (c  <= 'F') )
        {
            c  = (c  - 'A') + 10;
        }
        else
        {
            return AT_FAILURE;
        }

        if(total > 0x0FFFFFFF)              /* ������ת */
        {
            return AT_FAILURE;
        }
        else
        {
            total = (total << 4) + c;              /* accumulate digit */
            c = (TAF_UINT32)(TAF_UINT8)*nptr++;    /* get next Char */
        }
    }

    *pRtn = total;   /* return result, negated if necessary */
    return AT_SUCCESS;
}
/*****************************************************************************
 Prototype      : At_RangeToU32
 Description    : ���ַ����е�ĳһ��ת���޷�������ֵ,pBegainָʾ��ʼ��ַ,pucEnd
                  ʾ������ַ
 Input          : pucBegain --- ָʾ��ת���ִ��Ŀ�ʼ��ַ
                  pucEnd    --- ָʾ��ת���ִ��Ŀ�ʼ��ַ
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_RangeToU32(TAF_UINT8 * pucBegain, TAF_UINT8 * pucEnd)
{
    TAF_UINT32 c;                                   /* current Char */
    TAF_UINT32 total = 0;                           /* current total */

    /* ���������� */
    if(pucBegain >= pucEnd)
    {
        return total;
    }

    /* �ӵ�һ���ַ���ʼ */
    c = (TAF_UINT32)*pucBegain;

    /* �����ۼ�*10���,ֱ������ */
    while( (pucBegain != pucEnd) && ( (c >= '0') && (c <= '9') ))
    {
        total = (10 * total) + (c - '0');             /* accumulate digit */
        pucBegain++;                                /* ע�⣬�����ڸ�ֵ֮ǰ��λ�����򣬱���ֵ���� */
        c = (TAF_UINT32)(TAF_UINT8)*pucBegain;      /* get next Char */

        if(total >= 0x19999998)                     /* �������0x19999998��ֱ�ӷ��أ�����ת */
        {
            return total;
        }
    }

    return total;
}
/*****************************************************************************
 Prototype      : At_RangeCopy
 Description    : ���ַ����е�ĳһ�ο�����ָ����ַ,pDstָʾĿ�ĵ�ַ,pucBegain
                  ָʾ��ʼ��ַ,pEndָʾ������ַ
 Input          : pucDst    --- Ŀ�ĵ�ַ
                  pucBegain --- ��ת���ִ��Ŀ�ʼ��ַ
                  pucEnd    --- ��ת���ִ��Ľ�����ַ
 Output         : ---
 Return Value   : ---
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
*****************************************************************************/
TAF_VOID At_RangeCopy(TAF_UINT8 *pucDst,TAF_UINT8 * pucBegain, TAF_UINT8 * pucEnd)
{
    /* ���ο�����Ŀ�ĵ�ַ,ֱ������ */
    while(pucBegain < pucEnd)
    {
        *pucDst++ = *pucBegain++;
    }
}
/*****************************************************************************
 Prototype      : At_UpString
 Description    : �ַ�����дת��
 Input          : pData --- Ŀ�ĵ�ַ
                  usLen --- ����
 Output         : ---
 Return Value   : AT_SUCCESS --- �ɹ�
                  AT_FAILURE --- ʧ��
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2005-04-19
    Author      : ---
    Modification: Created function
  2.��    �� : 2007-03-27
    ��    �� : h59254
    �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
*****************************************************************************/
TAF_UINT32 At_UpString(TAF_UINT8 *pData,TAF_UINT16 usLen)
{
    TAF_UINT8  *pTmp  = pData;                 /* current Char */
    TAF_UINT16 ChkLen = 0;

    if(0 == usLen)
    {
        return AT_FAILURE;
    }

    while(ChkLen++ < usLen)
    {
        if ( (*pTmp >= 'a') && (*pTmp <= 'z'))
        {
            *pTmp = *pTmp - 0x20;
        }
        pTmp++;
    }
    return AT_SUCCESS;
}


/******************************************************************************
 ��������: atRangeToU32
 ��������: ���ַ����е�ĳһ��ת���޷�������ֵ

 ����˵��:
   pucBegain [in/out] ָʾ��ת���ִ��Ŀ�ʼ��ַ
   pucEnd [in/out] ָʾ��ת���ִ��Ŀ�ʼ��ַ

 �� �� ֵ:
    ����ת����������ֵ

 ��    ��: �޾�ǿ/00064416 [2009-08-11]
******************************************************************************/
VOS_UINT32 atRangeToU32( VOS_UINT8 *pucBegain, VOS_UINT8 *pucEnd)
{
    VOS_UINT32 total = 0;                           /* current total */
    VOS_UINT32 ulRst;

    /* ���������� */
    if(pucBegain >= pucEnd)
    {
        return total;
    }

    ulRst = atAuc2ul(pucBegain, (VOS_UINT16)(pucEnd - pucBegain), &total);

    if(AT_SUCCESS != ulRst)
    {
        total = 0;
    }

    return total;
}

/******************************************************************************
 ��������: atRangeCopy
 ��������: ���ַ����е�ĳһ�ο�����ָ����ַ

 ����˵��:
   pucDst [in/out] Ŀ�ĵ�ַ
   pucBegain [in/out] ��ת���ִ��Ŀ�ʼ��ַ
   pucEnd [in/out] ��ת���ִ��Ľ�����ַ

 �� �� ֵ:
    TODO: ...

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: �޾�ǿ/00064416 [2009-08-11]
******************************************************************************/
VOS_VOID atRangeCopy( VOS_UINT8 *pucDst, VOS_UINT8 * pucBegain, VOS_UINT8 * pucEnd)
{
    /* ���ο�����Ŀ�ĵ�ַ,ֱ������ */
    while(pucBegain < pucEnd)
    {
        *pucDst++ = *pucBegain++;
    }
}

/******************************************************************************
 ��������: ��ʮ�������ַ���ת���޷�������ֵ

 ����˵��:
   nptr [in/out] ������ַ�������ָ��
   usLen [in] ������ַ�������
   pRtn [in/out] ���ַ���ת����������ֵ

 �� �� ֵ:
    AT_FAILURE: �����ַ������з������ַ�������ֵ���
    AT_SUCCESS: �ɹ�
******************************************************************************/
static VOS_UINT32 auc2ulHex( VOS_UINT8 *nptr, VOS_UINT16 usLen,  VOS_UINT32 *pRtn)
{
    VOS_UINT8 c         = 0;         /* current Char */
    VOS_UINT32 total    = 0;         /* current total */
    VOS_UINT16 usLength = 2;         /* current Length */
    VOS_UINT8 *pcTmp    = nptr + 2;  /* ��0x��ʼ�Ƚ� */

    /* ����ָ���ɵ����߱�֤��ΪNULL, �ô������ж� */

    c = *pcTmp++;

    while(usLength++ < usLen)
    {
        /* 0xFFFFFFFF */
        if(total > 0xFFFFFFF)
        {
            return AT_FAILURE;
        }

        /* �ַ���� */
        if(isdigit(c))
        {
            total = AT_CHECK_BASE_HEX * total + (c - '0');        /* accumulate digit */
            c = *pcTmp++;    /* get next Char */
        }
        else if('A' <= c && 'F' >= c)
        {
            total = AT_CHECK_BASE_HEX * total + (c - 'A' + 10);        /* accumulate digit */
            c = *pcTmp++;    /* get next Char */
        }
        else if('a' <= c && 'f' >= c)
        {
            total = AT_CHECK_BASE_HEX * total + (c - 'a' + 10);        /* accumulate digit */
            c = *pcTmp++;    /* get next Char */
        }
        else
        {
            return AT_FAILURE;
        }
    }

    *pRtn = total;   /* return result, negated if necessary */

    return AT_SUCCESS;
}

/******************************************************************************
 ��������: ��ʮ�����ַ���ת���޷�������ֵ

 ����˵��:
   nptr [in/out] ������ַ�������ָ��
   usLen [in] ������ַ�������
   pRtn [in/out] ���ַ���ת����������ֵ

 �� �� ֵ:
    AT_FAILURE: �����ַ������з������ַ�������ֵ���
    AT_SUCCESS: �ɹ�
******************************************************************************/
static VOS_UINT32 auc2ulDec( VOS_UINT8 *nptr, VOS_UINT16 usLen,  VOS_UINT32 *pRtn)
{
    VOS_UINT32 c        = 0;         /* current Char */
    VOS_UINT32 total    = 0;         /* current total */
    VOS_UINT16 usLength = 0;         /* current Length */
    VOS_UINT8 *pcTmp    = nptr;      /* ��0x��ʼ�Ƚ� */

    /* ����ָ���ɵ����߱�֤��ΪNULL, �ô������ж� */

    c = (VOS_UINT32)*pcTmp++;

    while(usLength++ < usLen)
    {
        /* �ַ���� */
        if(isdigit(c))
        {
            /* 0xFFFFFFFF = 4294967295 */
            if(((total == 429496729) && (c > '5')) || (total > 429496729))
            {
                return AT_FAILURE;
            }

            total = AT_CHECK_BASE_DEC * total + (c - '0');        /* accumulate digit */
            c = (VOS_UINT32)(VOS_UINT8)*pcTmp++;    /* get next Char */
        }
        else
        {
            return AT_FAILURE;
        }
    }

    *pRtn = total;   /* return result, negated if necessary */

    return AT_SUCCESS;
}

/******************************************************************************
 ��������: ���ַ���ת���޷�������ֵ

 ����˵��:
   nptr [in/out] ������ַ�������ָ��
   usLen [in] ������ַ�������
   pRtn [in/out] ���ַ���ת����������ֵ

 �� �� ֵ:
    AT_FAILURE: �����ַ������з������ַ�������ֵ���
    AT_SUCCESS: �ɹ�
******************************************************************************/
VOS_UINT32 atAuc2ul( VOS_UINT8 *nptr,VOS_UINT16 usLen, VOS_UINT32 *pRtn)
{
    /* ����ú���ǰ�����в����ѽ��м�飬��֤��ΪNULL */

    if(NULL == nptr || 0 == usLen || NULL == pRtn)
    {
        return AT_FAILURE;
    }

    if('0' == *nptr)
    {
        if(2 < usLen && (('x' == *(nptr + 1)) || ('X' == *(nptr + 1))))
        {
            return auc2ulHex(nptr, usLen, pRtn);
        }
        else
        {
        }
    }

    return auc2ulDec(nptr, usLen, pRtn);
}

/*****************************************************************************
 Prototype      : At_ul2Auc
 Description    : ���޷�������ֵת���ַ���
 Input          : ulValue ---ָʾ��ת���޷�������ֵ
                  usLen   ---ָʾת������ַ����ĳ���
 Output         : pRtn    ---ָʾת������ַ���(��֤���ǿ�ָ��)
 Return Value   : 
 Calls          : ---
 Called By      : ---

 History        : ---
  1.Date        : 2015-05-22
    Author      : w00316404
    Modification: Created function
*****************************************************************************/
VOS_VOID At_ul2Auc(VOS_UINT32 ulValue,TAF_UINT16 usLen,VOS_UINT8 *pRtn)
{
    VOS_UINT32                          ulTempValue;
        
    if (0 == usLen)
    {
        return;
    }

    while(0 != ulValue)
    {
        ulTempValue = ulValue % 10;
        ulValue /=10;
        *(pRtn + usLen - 1) = '0' + (VOS_UINT8)ulTempValue;
        usLen--;
    }

    if (0 == usLen)
    {
        return;
    }

    while(0 < usLen)
    {
        *(pRtn + usLen - 1) = '0';
        usLen--;
    }
    
    return;
}

/*****************************************************************************
 �� �� ��  : At_HeapAllocD
 ��������  : AT�ڴ����
 �������  : VOS_UINT32 ulSize
 �������  : ��
 �� �� ֵ  : VOS_VOID*

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID* At_HeapAllocD(VOS_UINT32 ulSize)
{
    VOS_VOID* ret = NULL;

    if((ulSize == 0) || (ulSize > (1024*1024)))
    {
        return NULL;
    }

    ret = (VOS_VOID *)kmalloc(ulSize, GFP_KERNEL);

    return ret;
}

/*****************************************************************************
 �� �� ��  : At_HeapFreeD
 ��������  : AT�ͷ��ڴ�
 �������  : VOS_VOID *pAddr
 �������  : ��
 �� �� ֵ  : VOS_VOID

 �޸���ʷ      :
  1.��    ��   : 2012��10��19��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID At_HeapFreeD(VOS_VOID *pAddr)
{
    if(pAddr == NULL)
    {
        return ;
    }

    kfree(pAddr);

    return;
}

