

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "TafStdlib.h"
#include "MnErrorCode.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
#include "MnMsgApi.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */
#include "MnCallApi.h"



/*lint -e958*/

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_STD_LIB_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/
/* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
LOCAL VOS_UINT8 f_aucMsgAsciiSfxDefAlpha[TAF_STD_MAX_GSM7BITDEFALPHA_NUM] =
{
    '@',  163,   '$',  165,  232,  233,  249,  236,  242,  199,  0x0a, 216,  248,  0x0d, 197,  229,
    0xff, '_',   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 198,  230,  223,  201,
    ' ',  '!',   '"',  '#',  164,  '%',  '&',  0x27, '(',  ')',  '*',  '+',  ',',  '-',  '.',  '/',
    '0',  '1',   '2',  '3',  '4',  '5',  '6',  '7',  '8',  '9',  ':',  ';',  '<',  '=',  '>',  '?',
    161,  'A',   'B',  'C',  'D',  'E',  'F',  'G',  'H',  'I',  'J',  'K',  'L',  'M',  'N',  'O',
    'P',  'Q',   'R',  'S',  'T',  'U',  'V',  'W',  'X',  'Y',  'Z',  196,  214,  209,  220,  167,
    191,  'a',   'b',  'c',  'd',  'e',  'f',  'g',  'h',  'i',  'j',  'k',  'l',  'm',  'n',  'o',
    'p',  'q',   'r',  's',  't',  'u',  'v',  'w',  'x',  'y',  'z',  228,  246,  241,  252,  224
};
/* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */

/*lint -save -e958 */


/* ��1980�꿪ʼ��������Ϊ��λ��ÿ������� */
LOCAL VOS_UINT16 g_ausTafStdDaysElapsedOfALeapYearSetTab[] = {
  /* �� 0 (����) */  0,
  /* �� 1        */  366,
  /* �� 2        */  366+365,
  /* �� 3        */  366+365+365,
  /* ��Ԫ������  */  366+365+365+365
};

/* ƽ����ÿ�µ����� */
LOCAL VOS_UINT16 g_ausTafStdNormMonthTab[] = {
  /* ---    */ 0,
  /* һ��   */ 31,
  /* ����   */ 31+28,
  /* ����   */ 31+28+31,
  /* ����   */ 31+28+31+30,
  /* ����   */ 31+28+31+30+31,
  /* ����   */ 31+28+31+30+31+30,
  /* ����   */ 31+28+31+30+31+30+31,
  /* ����   */ 31+28+31+30+31+30+31+31,
  /* ����   */ 31+28+31+30+31+30+31+31+30,
  /* ʮ��   */ 31+28+31+30+31+30+31+31+30+31,
  /* ʮһ�� */ 31+28+31+30+31+30+31+31+30+31+30,
  /* ʮ���� */ 31+28+31+30+31+30+31+31+30+31+30+31
};

/* ������ÿ�µ����� */
LOCAL VOS_UINT16 g_ausTafStdLeapMonthTab[] = {
  /* ---    */ 0,
  /* һ��   */ 31,
  /* ����   */ 31+29,
  /* ����   */ 31+29+31,
  /* ����   */ 31+29+31+30,
  /* ����   */ 31+29+31+30+31,
  /* ����   */ 31+29+31+30+31+30,
  /* ����   */ 31+29+31+30+31+30+31,
  /* ����   */ 31+29+31+30+31+30+31+31,
  /* ����   */ 31+29+31+30+31+30+31+31+30,
  /* ʮ��   */ 31+29+31+30+31+30+31+31+30+31,
  /* ʮһ�� */ 31+29+31+30+31+30+31+31+30+31+30,
  /* ʮ���� */ 31+29+31+30+31+30+31+31+30+31+30+31
};


/*****************************************************************************
  6 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_STD_Itoa
 ��������  : ������ת��ΪASCII��, �����������ַ���
 �������  : VOS_UINT32                          ulDigit            - ��ת��ΪASCII�������
 �������  : VOS_CHAR                           *pcDigitStr         - ���������ַ���
             VOS_UINT32                         *pulDigitStrLength  - ���������ַ�������
 �� �� ֵ  : VOS_FALSE  - ת��ʧ��
             VOS_TRUE   - ת���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_STD_Itoa(
    VOS_UINT32                          ulDigit,
    VOS_CHAR                           *pcDigitStr,
    VOS_UINT32                         *pulDigitStrLength
)
{
    VOS_INT32                           lCharNum;

    lCharNum = sprintf(pcDigitStr, "%d", (VOS_INT)ulDigit);/*lint !e586*/

    *pulDigitStrLength = (VOS_UINT32)lCharNum;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_AsciiNum2HexString
 ��������  : ���16�����ַ���ת������
 �������  : pucSrc                          - ��ת��ΪASCII�������
 �������  : pucSrc                          - ת���������
 �� �� ֵ  : VOS_FALSE  - ת��ʧ��
             VOS_TRUE   - ת���ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT32 TAF_STD_AsciiNum2HexString(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                         *pusSrcLen
)
{
    VOS_UINT16                          usChkLen;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           ucLeft;
    VOS_UINT16                          usSrcLen;
    VOS_UINT8                          *pucDst = VOS_NULL_PTR;

    usChkLen        = 0;
    ucTmp           = 0;
    ucLeft          = 0;
    usSrcLen        = *pusSrcLen;
    pucDst          = pucSrc;

    /* ��������������ֽ��򷵻ش��� */
    if (0 != (usSrcLen % 2))
    {
        return VOS_FALSE;
    }

    while (usChkLen < usSrcLen)
    {
        /* the number is 0-9 */
        if(isdigit(pucSrc[usChkLen]))
        {
            ucLeft = pucSrc[usChkLen] - '0';
        }
        /* the number is a-f */
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') )
        {
            ucLeft = (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        /* the number is A-F */
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') )
        {
            ucLeft = (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return VOS_FALSE;
        }

        pucDst[ucTmp] = 0xf0 & (ucLeft << 4);
        usChkLen += 1;

        /* the number is 0-9 */
        if(isdigit(pucSrc[usChkLen]))
        {
            pucDst[ucTmp] |= pucSrc[usChkLen] - '0';
        }
        /* the number is a-f */
        else if( (pucSrc[usChkLen] >= 'a') && (pucSrc[usChkLen] <= 'f') )
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'a') + 0x0a;
        }
        /* the number is A-F */
        else if( (pucSrc[usChkLen] >= 'A') && (pucSrc[usChkLen] <= 'F') )
        {
            pucDst[ucTmp] |= (pucSrc[usChkLen] - 'A') + 0x0a;
        }
        else
        {
            return VOS_FALSE;
        }

        usChkLen += 1;
        ucTmp += 1;
    }

    *pusSrcLen = usSrcLen / 2;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_HexAlpha2AsciiString
 ��������  : ���16�����ַ���ת������
 �������  : pucSrc                          - ��ת��ΪASCII�������
             usSrcLen                        - ��ת��ΪASCII������ֳ���
 �������  : pucDst                          - ת�����ASCII��
 �� �� ֵ  : ת�����ASCII�볤��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��06��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16 TAF_STD_HexAlpha2AsciiString(
    VOS_UINT8                          *pucSrc,
    VOS_UINT16                          usSrcLen,
    VOS_UINT8                          *pucDst
)
{
    VOS_UINT16                          usLen;
    VOS_UINT16                          usChkLen;
    VOS_UINT8                           ucHigh;
    VOS_UINT8                           ucLow;
    VOS_UINT8                          *pucWrite = VOS_NULL_PTR;
    VOS_UINT8                          *pucRead = VOS_NULL_PTR;

    pucWrite = pucDst;
    pucRead  = pucSrc;
    usLen    = 0;
    usChkLen = 0;
    ucHigh   = 0;
    ucLow    = 0;

    /* ɨ�������ִ� */
    /*lint -e961*/
    while ( usChkLen++ < usSrcLen )
    {
        ucHigh = 0x0F & (*pucRead >> 4);
        ucLow  = 0x0F & *pucRead;

        usLen += 2;    /* ��¼���� */

        if (0x09 >= ucHigh)   /* 0-9 */
        {
            *pucWrite++ = ucHigh + 0x30;
        }
        else if (0x0A <= ucHigh)    /* A-F */
        {
            *pucWrite++ = ucHigh + 0x37;
        }
        else
        {

        }

        if (0x09 >= ucLow)   /* 0-9 */
        {
            *pucWrite++ = ucLow + 0x30;
        }
        else if (0x0A <= ucLow)    /* A-F */
        {
            *pucWrite++ = ucLow + 0x37;
        }
        else
        {

        }

        /* ��һ���ַ� */
        pucRead++;
    }
    /*lint +e961*/

    return usLen;
}

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
/* MN_UnPack7Bit��MnMsgDecode.c�Ƶ����ļ�������ΪTAF_STD_UnPack7Bit */
/* MN_Pack7Bit��MnMsgEncode.c�Ƶ����ļ�������ΪTAF_STD_Pack7Bit */

/*****************************************************************************
 �� �� ��  : TAF_STD_UnPack7Bit
 ��������  : ͬ������,��7bit���뷽ʽ���ַ�ת��Ϊ8bit�ַ�
 �������  : pucOrgChar            - ָ����Ҫת�����ַ�ָ��
             ulLen                 - ��Ҫת�����ַ����ȣ�7λλ�����
             ucFillBit             - ��Ҫ����Bit����
 �������  : pucUnPackedChar       - ָ��ת�����ָ��
             pulLen                - ָ��ת������ַ����ȣ�8λλ�����
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_UINT32  TAF_STD_UnPack7Bit(
    const VOS_UINT8                     *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                           *pucUnPackedChar
)
{
    /*����ֽڵ�ַ*/
    VOS_UINT32                          ulPos = 0;
     /*���λƫ��*/
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulLoop;

    if ((VOS_NULL_PTR == pucOrgChar)
     || (VOS_NULL_PTR == pucUnPackedChar))
    {
        return VOS_ERR;
    }

    /*����Э��23040 9.2.3.24 UDHL��UDH������Fill Bits��SM��ȥ��Fill Bits�����SM(Unit: Septet),���Ի��SM�а����ַ�����*/
    ulOffset = ucFillBit % 8;

    /*��һ�����Ƴ���ǰ��Ч��ƫ��λulOffset���õ��ַ��ĵ�(8 - ulOffset)λ��
      �ڶ�������(8 - ulOffset)С��7λ����Ҫ����һ��OCTET�л�ȡ��(7 - (8 - ulOffset))λ
      ����������ȡ��һ������Դ���±�(ulPos)����Ҫȥ��������λ(ƫ��λulOffset)*/
    for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
    {
        pucUnPackedChar[ulLoop] = (VOS_UINT8)(pucOrgChar[ulPos] >> ulOffset);
        if (ulOffset > 1)
        {
            /*lint -e701*/
            pucUnPackedChar[ulLoop] |= (VOS_UINT8)((pucOrgChar[ulPos + 1UL] << (8 - ulOffset)) & TAF_STD_7BIT_MASK);
            /*lint +e701*/
        }
        else
        {
            pucUnPackedChar[ulLoop] &= TAF_STD_7BIT_MASK;
        }

        ulPos   += (ulOffset + 7) / 8;
        ulOffset = (ulOffset + 7) % 8;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_Pack7Bit
 ��������  : ͬ������,���ַ�ת��Ϊ7bit���뷽ʽ
 �������  : pucOrgChar          - ָ����Ҫת�����ַ�ָ��
             ulLen               - ��Ҫת�����ַ����ȣ���λseptet ע��:����Ԫ�ؽ���7bit��Ч����Ȼռ��1OCTET���ڴ�ռ�
             ucFillBit           - ��Ҫ����Bit����
 �������  : pucPackedChar       - ָ��ת�����ָ��
             pulLen              - ָ��ת������ַ����ȣ���λoctet
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_UINT32  TAF_STD_Pack7Bit(
    const VOS_UINT8                     *pucOrgChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                           ucFillBit,
    VOS_UINT8                           *pucPackedChar,
    VOS_UINT32                          *pulLen
)
{
    /*����ֽڵ�ַ*/
    VOS_UINT32                          ulPos = 0;
    /*���λƫ��*/
    VOS_UINT32                          ulOffset;
    VOS_UINT32                          ulLoop;

    if ((VOS_NULL_PTR == pucOrgChar)
     || (VOS_NULL_PTR == pucPackedChar)
     || (VOS_NULL_PTR == pulLen))
    {
        return VOS_ERR;
    }

    *pulLen = (VOS_UINT32)((((ulLen * 7) + ucFillBit) + 7) / 8);

    ulOffset = ucFillBit % 8;

    /*bit 7   6   5   4   3   2   1   0 */
    /*    |digit1L|   |---ulOffset1---| */ /*����ulOffset1λ*/
    /*                |(0)  digit1H   | */ /*����(8-ulOffset1λ)*/
    /*    |-digit2L-  |   |-ulOffset2-| */ /*ƫ����Ϊ(8-1+ulOffset1)%8*/

    /*��һ�����ճ���ǰ�Ѿ�����ƫ��λulOffset����������Դ��ȡ��һ��OCTET����(8 - ulOffset)λ��
      �ڶ�������(8 - ulOffset)С��7λ����Ҫ����ǰ����Դ�ַ����¸�(7 - (8 - ulOffset))λ��䵽Ŀ�����ݵ���һ��OCTET��
      ����������ȡ��һ��Ŀ�����ݵ��±�(ulPos)���Ѿ���������λ(ƫ��λulOffset)*/
    for (ulLoop = 0; ulLoop < ulLen; ulLoop++)
    {
        if ((pucOrgChar[ulLoop] & (~TAF_STD_7BIT_MASK)) != 0)
        {
            return VOS_ERR;
        }

        pucPackedChar[ulPos] |= (VOS_UINT8)((VOS_UINT32)(pucOrgChar[ulLoop] & TAF_STD_7BIT_MASK) << ulOffset);
        if (ulOffset > 1)
        {
            pucPackedChar[ulPos + 1UL] = (VOS_UINT8)((pucOrgChar[ulLoop] & TAF_STD_7BIT_MASK) >> (8 - ulOffset));
        }

        ulPos   += (ulOffset + 7) / 8;
        ulOffset = (ulOffset + 7) % 8;
    }

    return VOS_OK;
}
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdNumberToAscii
 ��������  : ��BCD����ĺ���ת����Ascii����ĺ���
 �������  : pBcdNumber     - BCD����
             ucBcdLen       - BCD����ĳ���
 �������  : pcAsciiNumber  - ת���õ���ASCII����(��'\0'��β)
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertBcdNumberToAscii(
    const VOS_UINT8                    *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_CHAR                           *pcAsciiNumber
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pcAsciiNumber))
    {
        return MN_ERR_NULLPTR;
    }

    /*��������ַ�����ȥ����Ч��0XFF����*/
    while (ucBcdLen > 1)
    {
        if (0xFF == pucBcdNumber[ucBcdLen - 1])
        {
            ucBcdLen--;
        }
        else
        {
            break;
        }
    }

    /*�ж�pucBcdAddress��ָ����ַ��������һ���ֽڵĸ�λ�Ƿ�Ϊ1111��
    ����ǣ�˵������λ��Ϊ����������Ϊż��*/
    if ((pucBcdNumber[ucBcdLen - 1] & 0xF0) == 0xF0)
    {
        ucLen = (VOS_UINT8)((ucBcdLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucBcdLen * 2);
    }

    /*��������*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*�жϵ�ǰ�����������λ���뻹��ż��λ���룬��0��ʼ����ż��*/
        if (1 == (ucLoop % 2))
        {
            /*���������λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = ((pucBcdNumber[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*�����ż��λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = (pucBcdNumber[(ucLoop / 2)] & 0x0F);
        }

        /*������������ת����Ascii����ʽ*/
        ulRet = TAF_STD_ConvertBcdCodeToAscii(ucBcdCode, &(pcAsciiNumber[ucLoop]));
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }
    }

    pcAsciiNumber[ucLoop] = '\0';      /*�ַ���ĩβΪ0*/

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdCodeToAscii
 ��������  : ��BCD������ַ�ת����Ascii���ַ�
 �������  : ucBcdCode   - BCD������ַ�
 �������  : pcAsciiCode - ת���õ���ASCII���ַ�
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertBcdCodeToAscii(
    VOS_UINT8                           ucBcdCode,
    VOS_CHAR                           *pcAsciiCode
)
{
    VOS_CHAR                            cAsciiCode;

    if (VOS_NULL_PTR == pcAsciiCode)
    {
        return MN_ERR_NULLPTR;
    }

    if (ucBcdCode <= 0x09)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x30);
    }
    else if (0x0A == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x20);    /*�ַ�'*'*/
    }
    else if (0x0B == ucBcdCode)
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x18);    /*�ַ�'#'*/
    }
    else if ((0x0C == ucBcdCode)
          || (0x0D == ucBcdCode)
          || (0x0E == ucBcdCode))
    {
        cAsciiCode = (VOS_CHAR)(ucBcdCode + 0x55);    /*�ַ�'a', 'b', 'c'*/
    }
    else
    {
        return MN_ERR_INVALID_BCD;
    }

    *pcAsciiCode = cAsciiCode;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertAsciiNumberToBcd
 ��������  : ��Ascii����ĺ���ת����BCD����ĺ���
 �������  : pcAsciiNumber - ��'\0'��β��ASCII�ַ�����
 �������  : pucBcdNumber   - ת���õ���BCD����
             pucBcdLen      - ת���õ���BCD����ĳ���
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertAsciiNumberToBcd(
    const VOS_CHAR                     *pcAsciiNumber,
    VOS_UINT8                          *pucBcdNumber,
    VOS_UINT8                          *pucBcdLen
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pcAsciiNumber)
     || (VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pucBcdLen))
    {
        return MN_ERR_NULLPTR;
    }

    for (ucLoop = 0; pcAsciiNumber[ucLoop] != '\0'; ucLoop++)
    {
        ulRet = TAF_STD_ConvertAsciiCodeToBcd(pcAsciiNumber[ucLoop], &ucBcdCode);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        /*����ǰ��Ҫ����Ŀռ���0*/
        pucBcdNumber[(ucLoop / 2)] &= ((ucLoop % 2) == 1) ? 0x0F : 0xF0;

        /*������������Ӧ�Ŀռ�*/
        pucBcdNumber[(ucLoop / 2)] |= (((ucLoop % 2) == 1) ? ((ucBcdCode << 4) & 0xF0) : (ucBcdCode & 0x0F));
    }

    /*�������Ϊ�����������һ���ַ���Ҫ�� F */
    if (1 == (ucLoop % 2))
    {
        pucBcdNumber[(ucLoop / 2)] |= 0xF0;
    }

    *pucBcdLen = (ucLoop + 1) / 2;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertAsciiAddrToBcd
 ��������  : ͬ������,��MN_MSG_ASCII_ADDR_STRU���͵�ַת����MN_MSG_BCD_ADDR_STRU���͵�ַ
 �������  : pstAsciiAddr   - MN_MSG_ASCII_ADDR_STRU���͵�ַ
 �������  : pstBcdAddr     - MN_MSG_BCD_ADDR_STRU���͵�ַ
 �� �� ֵ  : MN_ERR_NO_ERRORת�������ɹ�������ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��13��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_STD_ConvertAsciiAddrToBcd(
    MN_MSG_ASCII_ADDR_STRU             *pstAsciiAddr,
    MN_MSG_BCD_ADDR_STRU               *pstBcdAddr
)
{
    VOS_UINT32 ulRet;

    if ((VOS_NULL_PTR == pstAsciiAddr)
     || (VOS_NULL_PTR == pstBcdAddr))
    {
        return MN_ERR_NULLPTR;
    }

    MN_GET_ADDRTYPE(pstBcdAddr->addrType,
                    pstAsciiAddr->enNumType,
                    pstAsciiAddr->enNumPlan);

    ulRet = TAF_STD_ConvertAsciiNumberToBcd((VOS_CHAR *)(pstAsciiAddr->aucAsciiNum),
                              pstBcdAddr->aucBcdNum,
                              &pstBcdAddr->ucBcdLen);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertAsciiCodeToBcd
 ��������  : ��Ascii���ַ�ת����BCD���ַ�
 �������  : ucAsciiCode  - ASCII�ַ�
 �������  : pucBcdCode   - ת���õ���BCD��
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertAsciiCodeToBcd(
    VOS_CHAR                            cAsciiCode,
    VOS_UINT8                          *pucBcdCode
)
{
    if (VOS_NULL_PTR == pucBcdCode)
    {
        return MN_ERR_NULLPTR;
    }

    if ((cAsciiCode >= '0')
     && (cAsciiCode <= '9'))
    {
        *pucBcdCode = (VOS_UINT8)(cAsciiCode - '0');
    }
    else if ('*' == cAsciiCode)
    {
        *pucBcdCode = 0x0a;
    }
    else if ('#' == cAsciiCode)
    {
        *pucBcdCode = 0x0b;
    }
    else if (('a' == cAsciiCode)
          || ('b' == cAsciiCode)
          || ('c' == cAsciiCode))
    {
        *pucBcdCode = (VOS_UINT8)((cAsciiCode - 'a') + 0x0c);
    }
    else
    {
        return MN_ERR_INVALID_ASCII;
    }

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertDeciDigitToBcd
 ��������  : ��ʮ��������ת����BCD��
 �������  : ucDeciDigit ʮ��������
             bReverseOrder TAF_TRUE����ת��,��BCD��ĸ�4BIT��Ӧʮ���Ƶĸ�λ;
                           TAF_FALSE˳��ת������BCD��ĸ�4BIT��Ӧʮ���Ƶ�ʮλ;
 �������  : ��
 �� �� ֵ  : ʮ��������ת���õ���BCD��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��15��
    ��    ��   : fuyingjun
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_STD_ConvertDeciDigitToBcd(
    VOS_UINT8                           ucDeciDigit,
    VOS_BOOL                            bReverseOrder
)
{
    VOS_UINT8 ucBcd;

    if (VOS_TRUE == bReverseOrder)
    {
        /*��4BIT�洢ʮ�������ĸ�λ*/
        ucBcd  = ucDeciDigit / 10;
        /*��4BIT�洢ʮ�������ĵ�λ*/
        ucBcd |= (ucDeciDigit % 10) << 4;
    }
    else
    {
        /*��4BIT�洢ʮ�������ĵ�λ*/
        ucBcd  = ucDeciDigit % 10;
        /*��4BIT�洢ʮ�������ĸ�λ*/
        ucBcd |= (VOS_UINT8)((ucDeciDigit / 10) << 4);
    }

    return ucBcd;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdToDeciDigit
 ��������  : ��BCD���������ת����ʮ��������
 �������  : ucBcdDigit BCD���������
             bReverseOrder MN_TRUE����ת��,��BCD��ĸ�4BIT��Ӧʮ���Ƶĸ�λ;
                           MN_FALSE˳��ת������BCD��ĸ�4BIT��Ӧʮ���Ƶ�ʮλ;
 �������  : pucDigit      ת����õ���ʮ��������
 �� �� ֵ  : BCD��ת���õ���ʮ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��15��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_STD_ConvertBcdToDeciDigit(
    VOS_UINT8                           ucBcdDigit,
    VOS_BOOL                            bReverseOrder,
    VOS_UINT8                          *pucDigit
)
{
    VOS_UINT8                           ucHigher;
    VOS_UINT8                           ucLower;
    VOS_UINT32                          ulRet;

    ucHigher = (ucBcdDigit >> 4) & 0x0f;
    ucLower  = ucBcdDigit & 0x0f;
    if ((ucHigher > 9) || (ucLower > 9))
    {
        ulRet = MN_ERR_INVALIDPARM;
    }
    else
    {
        ulRet = MN_ERR_NO_ERROR;
    }

    if (VOS_TRUE == bReverseOrder)
    {
        *pucDigit  = (VOS_UINT8)((VOS_UINT8)(ucLower * 10) + ucHigher);
    }
    else
    {
        *pucDigit  = (VOS_UINT8)((VOS_UINT8)ucHigher * 10) + ucLower;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertAsciiToDefAlpha
 ��������  : ͬ������,��ASCII���ֵת��Ϊ23038Э��涨��Default Alphabet
 �������  : pucAsciiChar          - ָ��ASCII���ָ��
             ulLen                 - ASCII�ַ��ĳ���
 �������  : pucDefAlpha           - ָ��Default Alphabet��ָ��
 �� �� ֵ  : VOS_UINT32:�������صĽ��,�ɹ��Լ�ʧ�ܵ�ԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��8��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertAsciiToDefAlpha(
    const VOS_UINT8                    *pucAsciiChar,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pucDefAlpha
)
{
    VOS_UINT8                           ucLoop1;
    VOS_UINT32                          ulLoop2;
    VOS_BOOL                            bMatched;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucAsciiChar)
     || (VOS_NULL_PTR == pucDefAlpha))
    {
        return MN_ERR_NULLPTR;
    }

    ulRet = MN_ERR_NO_ERROR;
    /*
    Ŀǰ�ο�����ƽ̨��֧��23038 6.2.1 GSM 7 bit Default Alphabet���д��ڵ��ַ�����
    ��֧����չ���е��ַ���
    ASCII����GSM 7 bit Default Alphabet�������ֵı�׼ASCII�����ת��ΪGSM 7 bit Default Alphabet��
    �����ܹ�������ַ��Ѳ���ͨ��������δ���ԣ�
    ASCII���������ַ�����{�����¼Ϊ00���ض�������@��������ʧ�ܣ�
    �����ܹ�������ַ��Ѳ���ͨ��������δ���ԣ�
    ��Ҫ�ο�����ƽ̨�Ĵ���
    */
    for (ulLoop2 = 0; ulLoop2 < ulLen; ulLoop2++)
    {
        bMatched = VOS_FALSE;
        /*7BIT convert into ASCII ,consider later!!!!!*/
        for (ucLoop1 = 0 ; ucLoop1 < TAF_STD_MAX_GSM7BITDEFALPHA_NUM ; ucLoop1++)
        {
            if (f_aucMsgAsciiSfxDefAlpha[ucLoop1] == (*pucAsciiChar))
            {
                *pucDefAlpha = ucLoop1;
                pucDefAlpha++;
                bMatched = VOS_TRUE;
                break;
            }
        }

        if (VOS_TRUE != bMatched)
        {
            ulRet = MN_ERR_INVALIDPARM;
        }

        pucAsciiChar++;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertDefAlphaToAscii
 ��������  : ͬ������,��23038Э��涨��Default Alphabetת��ΪASCII���ֵ
 �������  : pucDefAlpha    - ָ��Default Alphabet��ָ��
             ulDefAlphaLen  - Default Alphabet�ĳ���
 �������  : pucAsciiChar   - ָ��ASCII���ָ��
 			 pulAsciiCharLen- ָ��ASCII���ַ�������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��8��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2009-09-08
    ��    ��   : F62575
    �޸�����   : ���ⵥ��:����TE��MT���ַ�������ΪIRA�����ű�������Ϊ7BIT���룬���������ַ�@�ȶ������ݣ�д�뵽SIM���е����ݴ���
  3.��    ��   : 2009-09-24
    ��    ��   : F62575
    �޸�����   : ���ⵥ��AT2D14728:�ı���ʽ�б���ȡ�����쳣
  4.��    ��   : 2010��04��10��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��AT2D18035
                 дPDU���ŵ�SIM��,BALONG��TP-SCTS�ļ�����˲�һ�£�
  5.��    ��   : 2013��08��22��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��DTS2013081408291,�޷���ʾ���ַ�û����ʾΪ�ո�
*****************************************************************************/
VOS_VOID  TAF_STD_ConvertDefAlphaToAscii(
    const VOS_UINT8                     *pucDefAlpha,
    VOS_UINT32                          ulDefAlphaLen,
    VOS_UINT8                           *pucAsciiChar,
    VOS_UINT32                          *pulAsciiCharLen
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT8                           ucPos;
    VOS_UINT32                          ulValidLen = 0;

    if ((VOS_NULL_PTR == pucDefAlpha)
     || (VOS_NULL_PTR == pucAsciiChar))
    {
        return;
    }

    /*
    Ŀǰ�ο�����ƽ̨��֧��23038 6.2.1 GSM 7 bit Default Alphabet���д��ڵ��ַ�����
    ��֧����չ���е��ַ���
    ��ASCII�������ֵ�GSM 7 bit Default Alphabet����ת��Ϊ��׼ASCII�빩��ʾ�ã�
    ��չ�ַ����ת��Ϊ0XFE����ͬ�豸�϶�����˽�н��ͣ�
    �����Ǳ�׼�ַ�ת��Ϊ0XFF����ͬ�豸�϶�����˽�н��ͣ�
    ��Ҫ�ο�����ƽ̨�Ĵ���
    */
    for (ulLoop = 0; ulLoop < ulDefAlphaLen; ulLoop++)
    {
        ucPos           = TAF_STD_7BIT_MASK & pucDefAlpha[ulLoop];
        *pucAsciiChar   = f_aucMsgAsciiSfxDefAlpha[ucPos];
        if (TAF_STD_NOSTANDARD_ASCII_CODE == (*pucAsciiChar))
        {
            /* �Աȱ��,���޷���ʾ���ַ�ʹ�ÿո��滻 */
            (*pucAsciiChar) = ' ';
            pucAsciiChar++;
            ulValidLen++;
        }
        else if (TAF_STD_GSM_7BIT_EXTENSION_FLAG == (*pucAsciiChar) )
        {
            (*pucAsciiChar) = ' ';
            pucAsciiChar++;
            ulValidLen++;
        }
        else
        {
            pucAsciiChar++;
            ulValidLen++;
        }
    }

    if (ulValidLen < ulDefAlphaLen)
    {
        *pucAsciiChar = 0;
    }
    *pulAsciiCharLen = ulValidLen;

    return;
}

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdCodeToDtmf
 ��������  : ��BCD��ת����3GPP2Э���е�DTMF��ʽ����
 �������  : VOS_UINT8                           ucBcdCode
             VOS_UINT8                          *pucDtmfCode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��30��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertBcdCodeToDtmf(
    VOS_UINT8                           ucBcdCode,
    VOS_UINT8                          *pucDtmfCode
)
{
    VOS_UINT8                            ucDtmfCode;

    if (VOS_NULL_PTR == pucDtmfCode)
    {
        return MN_ERR_NULLPTR;
    }

    /*����'0' BCD:0x00, DTMF:0x0A*/
    /*�ַ�'*' BCD:0x0A, DTMF:0x0B*/
    /*�ַ�'#' BCD:0x0B, DTMF:0x0C*/

    if (ucBcdCode == 0x00)
    {
        ucDtmfCode = 0x0A;
    }
    else if (ucBcdCode <= 0x09)
    {
        ucDtmfCode = ucBcdCode;
    }
    else if (0x0A == ucBcdCode)         /*�ַ�'*'*/
    {
        ucDtmfCode = ucBcdCode + 1;
    }
    else if (0x0B == ucBcdCode)
    {
        ucDtmfCode = ucBcdCode + 1;     /*�ַ�'#'*/
    }
    else
    {
        return MN_ERR_INVALID_BCD;
    }

    *pucDtmfCode = ucDtmfCode;

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertBcdNumberToDtmf
 ��������  : ��BCD��ʽ�ı����ַ���ת��Ϊ3GPP2Э�鶨���DTMF��ʽ���ַ���
 �������  : const VOS_UINT8                    *pucBcdNumber
             VOS_UINT8                           ucBcdLen
             VOS_UINT8                          *pucDtmfNumber
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��30��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_STD_ConvertBcdNumberToDtmf(
    const VOS_UINT8                    *pucBcdNumber,
    VOS_UINT8                           ucBcdLen,
    VOS_UINT8                          *pucDtmfNumber
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBcdCode;
    VOS_UINT32                          ulRet;

    if ((VOS_NULL_PTR == pucBcdNumber)
     || (VOS_NULL_PTR == pucDtmfNumber))
    {
        return MN_ERR_NULLPTR;
    }

    /*��������ַ�����ȥ����Ч��0XFF����*/
    while (ucBcdLen > 1)
    {
        if (0xFF == pucBcdNumber[ucBcdLen - 1])
        {
            ucBcdLen--;
        }
        else
        {
            break;
        }
    }

    /*�ж�pucBcdAddress��ָ����ַ��������һ���ֽڵĸ�λ�Ƿ�Ϊ1111��
    ����ǣ�˵������λ��Ϊ����������Ϊż��*/
    if ((pucBcdNumber[ucBcdLen - 1] & 0xF0) == 0xF0)
    {
        ucLen = (VOS_UINT8)((ucBcdLen * 2) - 1);
    }
    else
    {
        ucLen = (VOS_UINT8)(ucBcdLen * 2);
    }

    /*��������*/
    for (ucLoop = 0; ucLoop < ucLen; ucLoop++)
    {
        /*�жϵ�ǰ�����������λ���뻹��ż��λ���룬��0��ʼ����ż��*/
        if (1 == (ucLoop % 2))
        {
            /*���������λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = ((pucBcdNumber[(ucLoop / 2)] >> 4) & 0x0F);
        }
        else
        {
            /*�����ż��λ���룬��ȡ��4λ��ֵ*/
            ucBcdCode = (pucBcdNumber[(ucLoop / 2)] & 0x0F);
        }

        /*������������ת����DTMF����ʽ*/
        ulRet = TAF_STD_ConvertBcdCodeToDtmf(ucBcdCode, pucDtmfNumber);
        if (MN_ERR_NO_ERROR != ulRet)
        {
            return ulRet;
        }

        pucDtmfNumber++;
    }

    return MN_ERR_NO_ERROR;
}



/*****************************************************************************
 �� �� ��  :TAF_STD_GetDaysOfLeapMonthTabAddr
 ��������  :��ȡ������µ�����
 �������  :��
 �������  :��
 �� �� ֵ  :����g_ausTafStdLeapMonthTab��ĵ�ַ��Ϣ
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT16* TAF_STD_GetDaysOfLeapMonthTabAddr(VOS_VOID)
{
    return g_ausTafStdLeapMonthTab;
}

/*****************************************************************************
 �� �� ��  :TAF_STD_GetDaysOfNormalMonthTabAddr
 ��������  :��ȡ��������µ�������ĵ�ַ
 �������  :��
 �������  :��
 �� �� ֵ  :����g_ausTafStdNormMonthTab��ĵ�ַ��Ϣ
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT16* TAF_STD_GetDaysOfNormalMonthTabAddr(VOS_VOID)
{
    return g_ausTafStdNormMonthTab;
}

/*****************************************************************************
 �� �� ��  :TAF_STD_GetDaysElapsedOfALeapYearSet
 ��������  :��ȡg_ausTafStdDaysElapsedOfALeapYearSetTab��ĵ�ַ��Ϣ
 �������  :��
 �������  :��
 �� �� ֵ  :����g_ausTafStdDaysElapsedOfALeapYearSetTab��ĵ�ַ��Ϣ
 ���ú���  :��

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT16* TAF_STD_GetDaysElapsedOfALeapYearSet(VOS_VOID)
{
    return g_ausTafStdDaysElapsedOfALeapYearSetTab;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_64Add32
 ��������  : һ��64λ��ֵ����һ��32λ��ֵ
 �������  :
             ulHighAddend --��������λ
             ulLowAddend  --��������λ
             ulAddFactor

 �������  :
             pulHighRslt  --�������λ
             pulLowRslt   --�������λ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : x00314862
    �޸�����   :
*****************************************************************************/
VOS_UINT32 TAF_STD_64Add32
(
    VOS_UINT32                          ulHighAddend,
    VOS_UINT32                          ulLowAddend,
    VOS_UINT32                          ulAddFactor,
    VOS_UINT32                         *pulHighRslt,
    VOS_UINT32                         *pulLowRslt
)
{
    if (0xFFFFFFFF - ulLowAddend >= ulAddFactor)
    {
        *pulLowRslt  = ulLowAddend + ulAddFactor;
        *pulHighRslt = ulHighAddend;
    }
    else
    {
        if (0xFFFFFFFF == ulHighAddend)
        {
            return VOS_ERR;
        }

        *pulHighRslt = ulHighAddend + 1;
        *pulLowRslt = ulAddFactor - (0xFFFFFFFF - ulLowAddend) - 1;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_64Sub32
 ��������  : һ��64λ��ֵ��ȥһ��32λ��ֵ
 �������  :
             ulHighMinuend  --��������λ
             ulLowMinuend   --��������λ
             ulAddFactor
 �������  :
             pulHighRslt    --�������λ
             pulLowRslt     --�������λ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : x00314862
    �޸�����   :
*****************************************************************************/
VOS_UINT32 TAF_STD_64Sub32
(
    VOS_UINT32                          ulHighMinuend,
    VOS_UINT32                          ulLowMinuend,
    VOS_UINT32                          ulSubFactor,
    VOS_UINT32                         *pulHighRslt,
    VOS_UINT32                         *pulLowRslt
)
{
    if(ulLowMinuend  >= ulSubFactor)
    {
        *pulHighRslt = ulHighMinuend;
        *pulLowRslt = ulLowMinuend - ulSubFactor;
    }
    else if (ulHighMinuend >= 1)
    {
        *pulHighRslt = ulHighMinuend - 1;
        *pulLowRslt  = ulLowMinuend + (0xFFFFFFFF - ulSubFactor) + 1;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertTimeFromSecsToTimeZone
 ��������  : �Ѵ�1980.1.6��ʼ������ת��Ϊ��Ӧ�������� ʱ����

 �������  : VOS_UINT32                          ulHighSystemTime,
             VOS_UINT32                          ulLowSystemTime,

 �������  : TAF_STD_TimeZoneType                 *pstUniversalTimeandLocalTimeZone
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : x00314862
    �޸�����   :
*****************************************************************************/
VOS_UINT32 TAF_STD_ConvertTimeFromSecsToTimeZone
(
    VOS_UINT32                          ulHighSystemTime,
    VOS_UINT32                          ulLowSystemTime,
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstUniversalTimeandLocalTimeZone
)
{
    VOS_UINT16                          i;
    VOS_UINT16                          usDays;
    VOS_UINT32                          ulQuadYyears;
    VOS_UINT16                         *pusMonthTable = VOS_NULL_PTR;
    VOS_UINT16                         *pusLeapMonthTable = VOS_NULL_PTR;
    VOS_UINT16                         *pusNormalMonthTable = VOS_NULL_PTR;
    VOS_UINT16                         *pusDaysElapsedTable = VOS_NULL_PTR;
    VOS_UINT32                          ulHighTmp;
    VOS_UINT32                          ulLowTmp;
    VOS_UINT32                          ulQuotientHigh;
    VOS_UINT32                          ulQuotientLow;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulRemainder;

    pusLeapMonthTable                 = TAF_STD_GetDaysOfLeapMonthTabAddr();

    pusNormalMonthTable               = TAF_STD_GetDaysOfNormalMonthTabAddr();

    pusDaysElapsedTable               = TAF_STD_GetDaysElapsedOfALeapYearSet();

    ulHighTmp      = 0;
    ulLowTmp       = 0;
    ulQuotientHigh = 0;
    ulQuotientLow  = 0;
    ulRemainder    = 0;
     /* ʱ�任��ɴ�1980.1.1 ��ʼ������ */
    ulResult = TAF_STD_64Add32(ulHighSystemTime, ulLowSystemTime, (VOS_UINT32)TAF_STD_TIME_ZONE_OFFSET_S, &ulHighTmp, &ulLowTmp);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }

     /* ����ϵͳʱ����������㵱ǰʱ������� */
    ulResult = VOS_64Div32(ulHighTmp, ulLowTmp, TAF_STD_SECONDS_PER_MINUTE, &ulQuotientHigh, &ulQuotientLow, &ulRemainder);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }
    pstUniversalTimeandLocalTimeZone->usSecond = (VOS_UINT16)ulRemainder;

    /* ����ϵͳʱ����������㵱ǰʱ��ķ����� */
    ulResult = VOS_64Div32(ulQuotientHigh, ulQuotientLow, TAF_STD_MINUTES_PER_HOUR, &ulHighTmp, &ulLowTmp, &ulRemainder);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }
    pstUniversalTimeandLocalTimeZone->usMinute = (VOS_UINT16)ulRemainder;

    /* ����ϵͳʱ����������㵱ǰʱ���Сʱ */
    ulResult = VOS_64Div32(ulHighTmp, ulLowTmp, TAF_STD_HOURS_PER_DAY, &ulQuotientHigh, &ulQuotientLow, &ulRemainder);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }
    pstUniversalTimeandLocalTimeZone->usHour = (VOS_UINT16)ulRemainder;

    /* ������1980��ʼ��ȥ�˶������� */
    ulResult = VOS_64Div32(ulQuotientHigh, ulQuotientLow, TAF_STD_TIME_ZONE_QUAD_YEAR, &ulHighTmp, &ulLowTmp, &ulRemainder);
    if ( VOS_OK != ulResult )
    {
        return VOS_ERR;
    }
    usDays = (VOS_UINT16)ulRemainder;

    ulQuadYyears = ulLowTmp;

    pstUniversalTimeandLocalTimeZone->usYear = (VOS_UINT16)(TAF_STD_TIME_ZONE_BASE_YEAR + (4 * ulQuadYyears));

    /* ���㵱ǰ�괦���ĸ������� */
    for ( i = 0; i < TAF_STD_DAYS_ELAPSED_OF_A_LEAP_YEAR_SET_TAB_COUNT - 1; i++ )
    {
        if (usDays < pusDaysElapsedTable[i + 1])
        {
            break;
        }
    }

    /* ��ȡ��ǰ���ȥ������ */
    usDays -= pusDaysElapsedTable[i];

    /* ��������һ�� */
    pstUniversalTimeandLocalTimeZone->usYear += (VOS_UINT16)i;

    /* ��������·ݺ���һ�� */

    /* ��ȡ�·ݱ� */
    pusMonthTable = (i == 0) ? pusLeapMonthTable : pusNormalMonthTable;

    /* �����·ݱ� */
    for ( i = 0; i < TAF_STD_NORMAL_MONTH_TAB_COUNT - 1; i++ )
    {
        if (usDays < pusMonthTable[i + 1])
        {
            break;
        }
    }

    /* �������ǰ����һ����.*/
    pstUniversalTimeandLocalTimeZone->usDay = usDays - pusMonthTable[i] + 1;

    /* ������·� */
    pstUniversalTimeandLocalTimeZone->usMonth = (VOS_UINT16)i + 1;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_STD_ConvertSystemTimeToHighLow
 ��������  : ��system timeͨ���ߵ�32������
 �������  : VOS_UINT8                          *pucSysTimeByte
             VOS_UINT32                         *pulHighSystemTime,
             VOS_UINT32                         *pulLowSystemTime

 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : x00314862
    �޸�����   :
*****************************************************************************/
VOS_VOID TAF_STD_ConvertSystemTimeToHighLow(
    VOS_UINT8                          *pucSysTimeByte,
    VOS_UINT32                         *pulHighSystemTime,
    VOS_UINT32                         *pulLowSystemTime
)
{
    VOS_UINT32                          ulTmp;
    VOS_UINT8                          *pucAddr = VOS_NULL_PTR;

    pucAddr = pucSysTimeByte + 1;

    ulTmp = *pucAddr++;
    ulTmp <<= 8;
    ulTmp |= *pucAddr++;
    ulTmp <<= 8;
    ulTmp |= *pucAddr++;
    ulTmp <<= 8;
    ulTmp |= *pucAddr;

    /* ȡsystemtime�ĸ���λ */
    *pulHighSystemTime = (VOS_UINT32)((pucSysTimeByte[0] & 0xF0) >> 4);

    /* ȡsystemtime�ĵ���λ */
    *pulLowSystemTime  = ((((VOS_UINT32)(((VOS_UINT32)(pucSysTimeByte[0] & 0x0F)) << 28)) & 0xF0000000)
                       | ((VOS_UINT32)(ulTmp >> 4) & 0x0FFFFFFF));

}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_TransformBcdMccToDeciDigit
 ��������  : ת��BCD��ʽ��MCCΪʮ����
 �������  : VOS_UINT32                          ulBcdMcc
 �������  : ��
 �� �� ֵ  : VOS_UINT16

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 TAF_STD_TransformBcdMccToDeciDigit(
    VOS_UINT32                          ulBcdMcc
)
{
    /*0x00 06 04 --> 460 */
    VOS_UINT16                          usMcc;

    usMcc = (ulBcdMcc & 0xff) * 100 + ((ulBcdMcc >> 8) & 0xff) * 10 + ((ulBcdMcc >> 16) & 0xff);

    if ( 1000 < usMcc )
    {
        usMcc = 0xffff;
    }

    return usMcc;
}
/*****************************************************************************
 �� �� ��  : TAF_STD_TransformBcdImsi1112ToDeciDigit
 ��������  : ת��IMSI11_12��ʽ��MCCΪʮ����
 �������  : VOS_UINT16                          usBcdImsi1112
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��7��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_STD_TransformBcdImsi1112ToDeciDigit(
    VOS_UINT16                          usBcdImsi1112
)
{
    /*0x03 00 --> 3 */
    VOS_UINT16                          usImsi1112;

    usImsi1112 = ((usBcdImsi1112 ) & 0xff) * 10 + ((usBcdImsi1112 >> 8) & 0xff);

    if ( 100 < usImsi1112 )
    {
        usImsi1112 = 0xffff;
    }

    return (VOS_UINT8)usImsi1112;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_TransformBcdMncToDeciDigit
 ��������  : ת��BCD��ʽ��MNCΪʮ����
 �������  : VOS_UINT16                         usBcdMcc
 �������  : ��
 �� �� ֵ  : VOS_UINT16

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 TAF_STD_TransformBcdMncToDeciDigit(
    VOS_UINT16                          usBcdMnc
)
{
    /*0x03 00 --> 03 */
    VOS_UINT16                          usMnc;

    usMnc = (usBcdMnc & 0xff) * 10 + ((usBcdMnc >> 8) & 0xff);

    if ( 100 < usMnc )
    {
        usMnc = 0xffff;
    }

    return usMnc;
}


/*****************************************************************************
 �� �� ��  : TAF_STD_TransformDeciDigitToBcdMcc
 ��������  : ʮ���Ƶ�MCCת��ΪBCD��ʽ
 �������  : VOS_UINT32                          ulDeciDigitMcc
 �������  : ��
 �� �� ֵ  : VOS_UINT32

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��28��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_STD_TransformDeciDigitToBcdMcc(
    VOS_UINT32                          ulDeciDigitMcc
)
{
    /*460 --->0x00 06 04 */
    VOS_UINT32                          ulBcdMcc;

    if (TAF_STD_INVALID_MCC != ulDeciDigitMcc)
    {
        ulBcdMcc  = (ulDeciDigitMcc % 1000) / 100;

        ulBcdMcc += (ulDeciDigitMcc % 10) << 16;

        ulBcdMcc += ((ulDeciDigitMcc % 100) / 10) << 8;

        return ulBcdMcc;
    }
    else
    {
        return TAF_STD_INVALID_MCC;
    }
}

/*lint -restore */

/*lint +e958*/



