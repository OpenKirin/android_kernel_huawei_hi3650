

#ifndef _ATCHECKFUNC_H_
#define _ATCHECKFUNC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "AtParse.h"
#include "PsCommonDef.h"
#include "AtMntn.h"

/* Moved from AtGnainterface.h by ��ӳ��/f62575 for AT Project, 2011/11/13, begin */
#define AT_GNA_E5_MAC_ADDR_LEN_BETWEEN_COLONS   (2)                             /* MAC��ַ��ð��֮����ַ�����*/
#define AT_GNA_E5_MAC_ADDR_COLON_NUM            (5)                             /* MAC��ַ��ð�ŵĸ���*/
#define AT_MAC_ADDR_LEN                         (32)                            /* MAC��ַ���� AT_GNA_E5_MAC_ADDR_LEN ->AT_MAC_ADDR_LEN */
/* Moved from AtGnainterface.h by ��ӳ��/f62575 for AT Project, 2011/11/13, end */
#define AT_CDATA_DIAL_777_LEN                   (4)

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)
/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/* ģ���������士HEADER */

/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
TAF_UINT32 At_CheckSemicolon( TAF_UINT8 Char );
TAF_UINT32 At_CheckDialNum( TAF_UINT8 Char );
TAF_UINT32 At_CheckDmChar( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharStar( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharWell( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharRightArrow( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharG( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharI( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharS( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharD( TAF_UINT8 Char );
TAF_UINT32 At_CheckBasicCmdName( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharA( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharT( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharPlus( TAF_UINT8 Char );
TAF_UINT32 At_CheckLeftBracket( TAF_UINT8 Char );
TAF_UINT32 At_CheckRightBracket( TAF_UINT8 Char );
TAF_UINT32 At_CheckDigit( TAF_UINT8 Char );
TAF_UINT32 At_CheckLetter( TAF_UINT8 Char );
TAF_UINT32 At_CheckUpLetter( TAF_UINT8 Char );
TAF_UINT32 At_CheckChar( TAF_UINT8 Char );
TAF_UINT32 At_CheckAlpha( TAF_UINT8 Char );
TAF_UINT32 At_CheckColon( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharSub( TAF_UINT8 Char );
TAF_UINT32 At_CheckQuot( TAF_UINT8 Char );
TAF_UINT32 At_CheckHorizontalLine( TAF_UINT8 Char );
TAF_UINT32 At_CheckEqu( TAF_UINT8 Char );
TAF_UINT32 At_CheckReq( TAF_UINT8 Char );
TAF_UINT32 At_CheckNoQuot( TAF_UINT8 Char );
TAF_UINT32 At_CheckHorizontalLinePara( AT_PARSE_PARA_TYPE_STRU *pPara);
TAF_UINT32 At_CheckHexStrWithoutQuotationPara( AT_PARSE_PARA_TYPE_STRU *pPara);
TAF_UINT32 At_CheckNumPara( AT_PARSE_PARA_TYPE_STRU *pPara);
TAF_UINT32 At_CheckCharPara( AT_PARSE_PARA_TYPE_STRU *pPara);
TAF_UINT32 At_CheckNumString( TAF_UINT8 *pData,TAF_UINT16 usLen );
TAF_UINT32 At_CheckNumCharString( TAF_UINT8 *pData,TAF_UINT16 usLen );
TAF_UINT32 At_CheckMmiString( TAF_UINT8 *pData,TAF_UINT16 usLen );
TAF_UINT32 At_CheckChar0x26( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharE( TAF_UINT8 Char );
TAF_UINT32 At_CheckChar1( TAF_UINT8 Char );
TAF_UINT32 At_CheckChar0( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharV( TAF_UINT8 Char );
TAF_UINT32 At_CheckCharF( TAF_UINT8 Char );

TAF_UINT32 At_CheckRightArrowStr( TAF_UINT8 *pData,TAF_UINT16 usLen );

VOS_UINT32 AT_CheckDateFormat(
    VOS_UINT8                           *pucDateStr,
    VOS_UINT32                          ulDateStrLen
);

VOS_UINT32  AT_GetDate(
    VOS_UINT8                           *pucDateStr,
    VOS_UINT32                          ulDateStrLen,
    AT_DATE_STRU                        *pstDate
);

VOS_UINT32  AT_CheckDate(
    AT_DATE_STRU                        *pstDate
);
VOS_UINT32  At_GetParaCnt(
    VOS_UINT8                           *pucData,
    VOS_UINT16                          usLen
);

VOS_UINT32 At_CheckAndParsePara(
    AT_PARSE_PARA_TYPE_STRU             *pstAtPara,
    VOS_UINT8                           *pucBegain,
    VOS_UINT8                           *pucEnd
);

VOS_UINT32 AT_CheckStrStartWith(
    VOS_UINT8                          *pucLineStr,
    VOS_UINT8                          *pucPefixStr
);

/* �Ƚϡ�ƥ����������� */
VOS_UINT32 atCheckBasicCmdName( VOS_UINT8 Char );

/* �Ƚϡ�ƥ��ո� */
VOS_UINT32 atCheckblank( VOS_UINT8 Char );

/* �Ƚϡ�ƥ�䶺�� */
VOS_UINT32 atCheckComma( VOS_UINT8 Char );

/* �Ƚϡ�ƥ��ð�� */
VOS_UINT32 atCheckColon( VOS_UINT8 Char );

VOS_UINT32 atCheckChar0x2f( VOS_UINT8 Char );

/* �Ƚϡ�ƥ���ַ�+ */
VOS_UINT32 atCheckCharPlus( VOS_UINT8 Char );

VOS_UINT32 atCheckChar( VOS_UINT8 Char );

VOS_UINT32 atCheckEqu( VOS_UINT8 Char );

VOS_UINT32 atCheckReq( VOS_UINT8 Char );

VOS_UINT32 atCheckQuot( VOS_UINT8 Char );

VOS_UINT32 atCheckNoQuot( VOS_UINT8 Char );



/* �Ƚϡ�ƥ���ַ������� */
VOS_UINT32 At_CheckStringPara( AT_PARSE_PARA_TYPE_STRU *pPara);

/* �Ƚϡ�ƥ����ֵ���͵Ĳ��� */
VOS_UINT32 atCheckNumPara( AT_PARSE_PARA_TYPE_STRU *pPara);

/* �Ƚϡ�ƥ���ַ���Χ���͵Ĳ��� */
VOS_UINT32 atCheckCharPara( AT_PARSE_PARA_TYPE_STRU *pPara);

/* �Ƚϡ�ƥ������ */
VOS_UINT32 atCheckNumString( VOS_UINT8 *pData,VOS_UINT16 usLen );

/* �ж��ַ������Ƿ���"*"��"#" */
VOS_UINT32 atCheckMmiString( VOS_UINT8 *pData,VOS_UINT16 usLen );

/* �ж��ַ������Ƿ���">" */
VOS_UINT32 atCheckRightArrowStr( VOS_UINT8 *pData,VOS_UINT16 usLen );


/******************************************************************************
 ��������: �Ƚϡ�ƥ����˫���Ű����ַ�������

 ����˵��:
   pPara [in/out] ������ַ���

 �� �� ֵ: AT_SUCCESS --- �ַ�������β���� "
           AT_FAILURE --- �ַ�������β��ȫ�� "
******************************************************************************/
extern VOS_UINT32 atCheckNoQuotStringPara(AT_PARSE_PARA_TYPE_STRU *pPara);


/******************************************************************************
 ��������: �Ƚϡ�ƥ����˫���Ű�����ĸ��ʼ

 ����˵��:
   Char [in] ������ַ�

 �� �� ֵ: AT_SUCCESS --- �ɹ�
           AT_FAILURE --- ʧ��
******************************************************************************/
extern VOS_UINT32 atNoQuotLetter(VOS_UINT8 Char);


/******************************************************************************
 ��������: �Ƚϡ�ƥ��ʮ������(0x��0X)

 ����˵��:
   Char [in] ������ַ�

 �� �� ֵ: AT_SUCCESS --- �ɹ�
           AT_FAILURE --- ʧ��
******************************************************************************/
extern VOS_UINT32 atCheckHex(VOS_UINT8 Char);


/******************************************************************************
 ��������: �Ƚϡ�ƥ��ʮ����������

 ����˵��:
   Char [in] ������ַ�

 �� �� ֵ: AT_SUCCESS --- �ɹ�
           AT_FAILURE --- ʧ��
******************************************************************************/
extern VOS_UINT32 atCheckHexNum(VOS_UINT8 Char);

extern VOS_UINT32 atfwParseSaveParam(VOS_UINT8* pStringBuf, VOS_UINT16 usLen);

extern VOS_UINT32 AT_SaveCdataDialParam(
    VOS_UINT8                          *pStringBuf,
    VOS_UINT16                          usLen
);



#if ((TAF_OS_VER == TAF_WIN32) || (TAF_OS_VER == TAF_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


#endif /* __AT_CHECK_FUNC_H__ */
