

/******************************************************************************
 */
/* PROJECT   :
 */
/* SUBSYSTEM :
 */
/* MODULE    :
 */
/* OWNER     :
 */
/******************************************************************************
 */


/******************************************************************************
 */
/*����AT����CheckList(chenpeng/00173035 2010-12-17):
 */
/*
 */
/*
 */
/* �������checklist:
 */
/*   1��AT���������Ƿ���ȷ
 */
/*      typedef VOS_UINT8 AT_CMD_OPT_TYPE;
 */
/*      #define AT_CMD_OPT_SET_CMD_NO_PARA     0
 */
/*      #define AT_CMD_OPT_SET_PARA_CMD        1
 */
/*      #define AT_CMD_OPT_READ_CMD            2
 */
/*      #define AT_CMD_OPT_TEST_CMD            3
 */
/*      #define AT_CMD_OPT_BUTT                4
 */
/*
 */
/*   2�����������Ƿ����Ҫ��
 */
/*      gucAtParaIndex
 */
/*
 */
/*   3��ÿ�������ĳ����Ƿ���ȷ���Ƿ�Ϊ0
 */
/*      gastAtParaList[0].usParaLen
 */
/*      gastAtParaList[1].usParaLen
 */
/*
 */
/*   4��ÿ������ȡֵ��Լ��(ȡֵ��Χ��������������������)�Ƿ�����
 */
/*      ע:����ȡֵԼ��Ӧ�÷��ھ���������ģ�鱣֤���˴���͸������
 */
/*      gastAtParaList[0].ulParaValue
 */
/*      gastAtParaList[1].ulParaValue
 */
/******************************************************************************
 */
/*lint -save -e537 -e734 -e813 -e958 -e718 -e746*/
/*#include <stdlib.h>
 */
/*#include "at_common.h"
 */
#include "osm.h"
#include "gen_msg.h"

#include "at_lte_common.h"
#include "ATCmdProc.h"

/*����У׼ c00173035  start in 2010-12-14*/

/******************************************************************************
 */
/* ��������:  �����û����룬���������б���ʼ����Ӧ�Ľṹ
 */
/*
 */
/* ����˵��:
 */
/*   pPara     [in] ...
 */
/*   ulListLen [in] ...
 */
/*   pausList  [out] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/*
 */
/* ʹ��Լ��:
 */
/*    1��ֻ����ʮ���������ַ�����Ϊ����
 */
/*    2��0��Ϊ���ֿ�ͷ���Լ��ո��������������checklist�������²�������
 */
/*
 */
/* �ַ�������Checklist:
 */
/*    1������ַ����ܳ����Ƿ�Ϸ�
 */
/*    2������Ƿ��з��ڴ��ַ�(�ո����������)
 */
/*    3������ַ����������Ĳ���ȡֵ�Ƿ����Ҫ�󣬰��������ַ������Ȳ��ܳ���5��
 */
/*       �������� 000000123 �����ַǷ�����
 */
/*    4������ַ����������Ĳ��������Ƿ���û������һ��
 */
/******************************************************************************
 */
VOS_UINT32 initParaListS16( AT_PARSE_PARA_TYPE_STRU *pPara, VOS_UINT16 ulListLen, VOS_INT16* pausList)
{
    VOS_UINT16 ulTmp;
    VOS_UINT8 *pParaData    = pPara->aucPara;
    VOS_UINT8  ucDigitNum   = 0;     /* ��¼�����ַ����������ܳ���5
 */
    VOS_INT16 usDigitValue = 0;     /* ��¼������ֵ��С�����ܳ���65535
 */
    VOS_UINT16 usTmpListNum = 0;     /* ��¼�������������ָ��������ܳ���16
 */
    VOS_BOOL bDigit      = FALSE; /* �Ƿ�������
 */
	VOS_BOOL bNegative   = FALSE; /* �Ƿ���
 */
    VOS_UINT32 ulRst        = ERR_MSP_SUCCESS;

    if ((NULL == pPara) ||(pPara->usParaLen > 2048))
    {
        /* 1������ַ����ܳ����Ƿ�Ϸ�
 */
        return ERR_MSP_INVALID_PARAMETER;
    }

    for(ulTmp = 0 ; ulTmp < pPara->usParaLen ; ulTmp++)
    {
        VOS_UINT8 ucChr = *pParaData;

        if(isdigit(ucChr))
        {
            /* ��һ���ֽ�Ϊ���ֻ���ǰ���пո�
 */
            if(!bDigit)
            {
                bDigit = TRUE;
                ucDigitNum = 0;
                usDigitValue = 0;

                /* 4������ַ����������Ĳ��������Ƿ���û������һ��
 */
                if(++usTmpListNum > ulListLen)
                {
                    ulRst = ERR_MSP_INVALID_PARAMETER;
                    break;
                }
            }

            /* 3������ַ����������Ĳ���ȡֵ�Ƿ����Ҫ�󣬰��������ַ������Ȳ��ܳ���5��
 */
            if((++ucDigitNum > 5) ||((32767-usDigitValue*10) < (ucChr - 0x30)))
            {
                ulRst = ERR_MSP_INVALID_PARAMETER;
                break;
            }

            usDigitValue = (VOS_INT16)(usDigitValue*10+(ucChr-0x30));

			pausList[usTmpListNum-1] = (VOS_INT16)((bNegative == FALSE)?(usDigitValue):(usDigitValue*(-1)));
        }
        else if(isspace(ucChr))
        {
			/* ����'-'���ŵ��쳣����
 */
			if(!bDigit && bNegative)
			{
				break;
			}

            bDigit = FALSE;
			bNegative = FALSE;

			pParaData++;
			continue;
        }
        else if(('-' == ucChr) && !bDigit && !bNegative)
        {
			bNegative = TRUE;

			pParaData++;
			continue;
		}
        else
        {
            /* 2������Ƿ��з��ڴ��ַ�(�ո����������)
 */
            ulRst = ERR_MSP_INVALID_PARAMETER;
            break;
        }
        pParaData++;
    }

    /* 4��ǿ�Ƽ��:����ַ����������Ĳ��������Ƿ���û������һ��
 */
    if(usTmpListNum != ulListLen)
    {
        ulRst = ERR_MSP_INVALID_PARAMETER;
    }

    return ulRst;
}




/******************************************************************************
 */
/* ��������:  �����û����룬���������б���ʼ����Ӧ�Ľṹ
 */
/*
 */
/* ����˵��:
 */
/*   pPara     [in] ...
 */
/*   ulListLen [in] ...
 */
/*   pausList  [out] ...
 */
/*                ...
 */
/*
 */
/* �� �� ֵ:
 */
/*    TODO: ...
 */
/*
 */
/* ʹ��Լ��:
 */
/*    1��ֻ����ʮ���������ַ�����Ϊ����
 */
/*    2��0��Ϊ���ֿ�ͷ���Լ��ո��������������checklist�������²�������
 */
/*
 */
/* �ַ�������Checklist:
 */
/*    1������ַ����ܳ����Ƿ�Ϸ�
 */
/*    2������Ƿ��з��ڴ��ַ�(�ո����������)
 */
/*    3������ַ����������Ĳ���ȡֵ�Ƿ����Ҫ�󣬰��������ַ������Ȳ��ܳ���5��
 */
/*       �������� 000000123 �����ַǷ�����
 */
/*    4������ַ����������Ĳ��������Ƿ���û������һ��
 */
/******************************************************************************
 */
VOS_UINT32 initParaListU16( AT_PARSE_PARA_TYPE_STRU *pPara, VOS_UINT16 ulListLen, VOS_UINT16* pausList)
{
    VOS_UINT16 ulTmp;
    VOS_UINT8 *pParaData    = pPara->aucPara;
    VOS_UINT8  ucDigitNum   = 0;  /* ��¼�����ַ����������ܳ���5
 */
    VOS_UINT16 usDigitValue = 0;  /* ��¼������ֵ��С�����ܳ���65535
 */
    VOS_UINT16 usTmpListNum = 0;  /* ��¼�������������ָ��������ܳ���16
 */
    VOS_BOOL bDigit      = FALSE;
    VOS_UINT32 ulRst        = ERR_MSP_SUCCESS;

    if ((NULL == pPara) ||(pPara->usParaLen > 2048))
    {
        /* 1������ַ����ܳ����Ƿ�Ϸ�
 */
        return ERR_MSP_INVALID_PARAMETER;
    }

    for(ulTmp = 0 ; ulTmp < pPara->usParaLen ; ulTmp++)
    {
        VOS_UINT8 ucChr = *pParaData;

        if(isdigit(ucChr))
        {
            /* ��һ���ֽ�Ϊ���ֻ���ǰ���пո�
 */
            if(!bDigit)
            {
                bDigit = TRUE;
                ucDigitNum = 0;
                usDigitValue = 0;

                /* 4������ַ����������Ĳ��������Ƿ���û������һ��
 */
                if(++usTmpListNum > ulListLen)
                {
                    ulRst = ERR_MSP_INVALID_PARAMETER;
                    break;
                }
            }

            /* 3������ַ����������Ĳ���ȡֵ�Ƿ����Ҫ�󣬰��������ַ������Ȳ��ܳ���5��
 */
            if((++ucDigitNum > 5) ||((65535-usDigitValue*10) < (ucChr - 0x30)))
            {
                ulRst = ERR_MSP_INVALID_PARAMETER;
                break;
            }

            usDigitValue = (VOS_UINT16)(usDigitValue*10+(ucChr-0x30));
            pausList[usTmpListNum-1] = usDigitValue;
        }
        else if(isspace(ucChr))
        {
            bDigit = FALSE;

			pParaData++;
			continue;
        }
        else
        {
            /* 2������Ƿ��з��ڴ��ַ�(�ո����������)
 */
            ulRst = ERR_MSP_INVALID_PARAMETER;
            break;
        }
        pParaData++;
    }

    /* 4��ǿ�Ƽ��:����ַ����������Ĳ��������Ƿ���û������һ��
 */
    if(usTmpListNum != ulListLen)
    {
        ulRst = ERR_MSP_INVALID_PARAMETER;
    }

    return ulRst;
}


/*����У׼ c00173035  end in 2010-12-14*/

/*lint -restore*/


