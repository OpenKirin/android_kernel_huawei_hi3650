

/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : UsimmApi.c
  Author       : zhuli
  Version      : V100R002
  Date         : 2008-5-15
  Description  : ��C�ļ�������---��ɻ������ݴ���ģ��ʵ��
  Function List:
  History      :
 ************************************************************************/

#include "si_pb.h"
#include "TafTypeDef.h"
#include "UsimPsInterface.h"
#include "NVIM_Interface.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID PS_FILE_ID_PB_DATA_C
/*lint +e767*/


/*****************************************************************************
�� �� ��  :SI_PB_FindPBOffset

��������  :�����ڻ����ж�λ�绰�����б��е�ƫ��

�������  :enPBType:�����ѯ�ĵ绰������

�������  :pucOffset:�����ѯ�ĵ绰��ƫ��

�� �� ֵ  :VOS_OK:��ѯ�ɹ�
           VOS_ERR:��ѯʧ��

���ú���  :��

��������  :

�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   : z00100318
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_FindPBOffset(SI_PB_TYPE_ENUM_UINT32  enPBType, VOS_UINT8 *pucOffset)
{
    VOS_UINT8 i;

    for(i=0; i<SI_PB_MAX_NUMBER; i++)
    {
        if(gastPBContent[i].enPBType == enPBType)   /*��ǰ�Ĳ�ѯ����һ��*/
        {
            PB_INFO_LOG("SI_PB_FindPBOffset Info: Locate the PhoneBook Accurately");

            *pucOffset = i;

            return VOS_OK;
        }
    }

    PB_ERROR_LOG("SI_PB_FindPBOffset Error: The PhoneBook Info is Not Exist");

    return VOS_ERR;             /*��ǰδ�ҵ�ƫ��*/
}


/*****************************************************************************
�� �� ��  :SI_PB_LocateRecord

��������  :��λ��ǰ���ʵĵ绰���ڻ����е�λ��

�������  :enPBType:�����ѯ�ĵ绰������
           usIndex1:���ʵĵ绰���ķ�Χ��ʼ��ַ
           usIndex2:���ʵĵ绰���ķ�Χ������ַ

�������  :pucNumber:�绰���������б��е�ƫ��
           pucContent:�绰���������ݵ���ʵ��ַ

�� �� ֵ  :VOS_OK:��ѯ�ɹ�
           VOS_ERR:��ѯʧ��

���ú���  :SI_PB_FindPBOffset

��������  :

�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   : z00100318
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_LocateRecord(SI_PB_TYPE_ENUM_UINT32  enPBType, VOS_UINT16 usIndex1, VOS_UINT16 usIndex2, VOS_UINT8 *pucNumber)
{
    VOS_UINT8   ucPBOffset;
    VOS_UINT32 ulResult;

    ulResult = SI_PB_FindPBOffset(enPBType, &ucPBOffset);    /*���Ȳ�ѯ��ǰ�Ļ���λ��*/

    if(VOS_ERR == ulResult)
    {
        PB_WARNING_LOG("SI_PB_LocateRecord: Locate PhoneBook Error");

        return TAF_ERR_UNSPECIFIED_ERROR;
    }

    if(PB_NOT_INITIALISED == gastPBContent[ucPBOffset].enInitialState)   /*��ǰ�ĵ绰��û�г�ʼ�����*/
    {
        PB_ERROR_LOG("SI_PB_LocateRecord:The PhoneBook is Not Initializtion");

        return TAF_ERR_SIM_BUSY;
    }

    if(PB_FILE_NOT_EXIST == gastPBContent[ucPBOffset].enInitialState)   /*��ǰ�ĵ绰��û�г�ʼ�����*/
    {
        PB_ERROR_LOG("SI_PB_LocateRecord:The PhoneBook is Not Initializtion");

        return TAF_ERR_FILE_NOT_EXIST;
    }

    if((usIndex1 > gastPBContent[ucPBOffset].usTotalNum)
        || (usIndex2 > gastPBContent[ucPBOffset].usTotalNum)
        || (usIndex1 > usIndex2))/*��ǰ�������Ѿ�������Χ*/
    {
        PB_WARNING_LOG("SI_PB_LocateRecord: The Index is Not in The Range of PhoneBook");

        return TAF_ERR_PB_WRONG_INDEX;
    }

    *pucNumber = ucPBOffset;        /*���ص�ǰ�ĵ绰������ƫ��*/

    return VOS_OK;
}

/*****************************************************************************
�� �� ��  :SI_PB_CountADNRecordNum

��������  :���㻺�������Ŷ�Ӧ�ĵ绰���ļ���ID�ͼ�¼��

�������  :usIndex:������

�������  :pusFileId:��Ӧ�ĵ绰���ļ�
           pucRecordNum:��Ӧ�ĵ绰����¼��

�� �� ֵ  :VOS_OK:��ѯ�ɹ�
           VOS_ERR:��ѯʧ��

���ú���  :��

��������  :

�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   : z00100318
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CountADNRecordNum(VOS_UINT16 usIndex, VOS_UINT16 *pusFileId, VOS_UINT8 *pucRecordNum)
{
    VOS_UINT8 i;
    VOS_UINT16 usTemp = 0;

    for(i=0; i<SI_PB_ADNMAX; i++)   /*���ݵ�ǰ��ADN�б�����ѭ��*/
    {
        if((usTemp < usIndex)&&(usIndex <= (gstPBCtrlInfo.astADNInfo[i].ucRecordNum + usTemp)))/*���������ļ��ķ�Χ��*/
        {
            *pusFileId = gstPBCtrlInfo.astADNInfo[i].usFileID;  /*���ص�ǰ���ļ�ID*/
            *pucRecordNum = (VOS_UINT8)(usIndex - usTemp);/*���ص�ǰ�ļ�¼��*/

            return VOS_OK;
        }
        else
        {
            usTemp += gstPBCtrlInfo.astADNInfo[i].ucRecordNum;  /*�������ۼ�*/
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
�� �� ��  : SI_PB_GetXDNFileID
��������  : ����XDN�绰�����ͷ��ض�Ӧ�绰����FID
�������  : ulStorage:XDN�㻰������
�������  : pusFileId:�绰����Ӧ��FID
�� �� ֵ  : VOS_OK
            VOS_ERR
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2008��10��15��
    ��    ��   : z00100318
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_GetXDNFileID(VOS_UINT32 ulStorage, VOS_UINT16 *pusFileId)
{
    VOS_UINT32 ulResult = VOS_OK;

    switch(ulStorage)
    {
        case SI_PB_STORAGE_ON:
            *pusFileId = EFMSISDN;
            break;
        case SI_PB_STORAGE_FD:
            *pusFileId = EFFDN;
            break;
        case SI_PB_STORAGE_BD:
            *pusFileId = EFBDN;
            break;
        default:
            ulResult = VOS_ERR;
    }

    return ulResult;
}

/*****************************************************************************
�� �� ��  :SI_PB_BcdToAscii

��������  :BCD��ת����Ascii��

�������  :ucBcdNumLen:ת���ĺ��볤��
           pucBcdNum:ת���ĺ�������

�������  :pucAsciiNum:ת���Ľ��

�� �� ֵ  :��

���ú���  :��

��������  :

�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   : z00100318
    �޸�����   : Creat
2. ��    ��   : 2011��08��04��
    ��    ��   : w00184875
    �޸�����   : DTS2011080203533

*****************************************************************************/
VOS_VOID SI_PB_BcdToAscii(VOS_UINT8 ucBcdNumLen,VOS_UINT8 *pucBcdNum, VOS_UINT8 *pucAsciiNum, VOS_UINT8 *pucLen)
{

    VOS_UINT8       ucTmp;
    VOS_UINT8       ucLen = 0;
    VOS_UINT8       ucFirstNumber;
    VOS_UINT8       ucSecondNumber;

    for (ucTmp = 0; ucTmp < ucBcdNumLen; ucTmp++)
    {

        if(0xFF == pucBcdNum[ucTmp])
        {
            break;
        }

        ucFirstNumber  = (VOS_UINT8)(pucBcdNum[ucTmp] & 0x0F); /*ȡ���߰��ֽ�*/

        ucSecondNumber = (VOS_UINT8)((pucBcdNum[ucTmp] >> 4) & 0x0F);/*ȡ���Ͱ��ֽ�*/

        if(ucFirstNumber <= 9)  /*ת������*/
        {
            *pucAsciiNum = ucFirstNumber + 0x30;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0A == ucFirstNumber)   /*ת��*�ַ�*/
        {
            *pucAsciiNum = 0x2a;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0B == ucFirstNumber)   /*ת��#�ַ�*/
        {
            *pucAsciiNum = 0x23;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0C == ucFirstNumber)   /*ת��'P'�ַ�*/
        {
            *pucAsciiNum = 0x50;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0D == ucFirstNumber)   /*ת��'?'�ַ�*/
        {
            *pucAsciiNum = 0x3F;

            pucAsciiNum++;

            ucLen++;
        }
        else                                    /*ת����ĸ*/
        {
            *pucAsciiNum = ucFirstNumber + 0x57;

            pucAsciiNum++;

            ucLen++;
        }

        if(0x0F == ucSecondNumber)
        {
            break;
        }
        if(ucSecondNumber <= 9)
        {
            *pucAsciiNum = ucSecondNumber + 0x30;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0A == ucSecondNumber)
        {
            *pucAsciiNum = 0x2a;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0B == ucSecondNumber)
        {
            *pucAsciiNum = 0x23;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0C == ucSecondNumber)   /*ת��'P'�ַ�*/
        {
            *pucAsciiNum = 0x50;

            pucAsciiNum++;

            ucLen++;
        }
        else if(0x0D == ucSecondNumber)   /*ת��'?'�ַ�*/
        {
            *pucAsciiNum = 0x3F;

            pucAsciiNum++;

            ucLen++;
        }
        else
        {
            *pucAsciiNum = ucSecondNumber + 0x57;

            pucAsciiNum++;

            ucLen++;
        }
    }

    *pucLen = ucLen;

    return;
}

/*****************************************************************************
�� �� ��  :SI_PB_TransPBName

��������  :�����绰������

�������  :ucNameMax �������ȵ����ֵ
           pucName ��������

�������  :pAlphaType ת����������������
           pNameLen ת������������

�� �� ֵ  :VOS_OK �����ɹ�
           VOS_ERR ����ʧ��

���ú���  :��

��������  :

�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   : z00100318
    �޸�����   : Creat

*****************************************************************************/
VOS_VOID SI_PB_DecodePBName(VOS_UINT8 ucNameMax, VOS_UINT8 *pucName,
                                        VOS_UINT32 *pAlphaType, VOS_UINT8 *pNameLen)
{
    VOS_UINT8 i = 0;

    /* ������UCS2 80 */
    if (SI_PB_ALPHATAG_TYPE_UCS2_80 == pucName[0])
    {
        *pAlphaType = pucName[0];

        ucNameMax--;
        for(i=0;i<(ucNameMax-(ucNameMax%2));i+=2)   /*������ǰ����������*/
        {
            if((pucName[i+1] == 0xFF)&&(pucName[i+2] == 0xFF))
            {
                break;
            }
        }

        *pNameLen = i;      /*�������ȷ���*/

        return;
    }

    /* ������UCS2 81 */
    if (SI_PB_ALPHATAG_TYPE_UCS2_81 == pucName[0])
    {
        *pAlphaType = pucName[0];

        if(pucName[1] > (ucNameMax - 3))/* �����ǰ������Ϣ������󳤶ȣ���ֱ�ӽ׽ض� */
        {
           i = ucNameMax -1;
        }
        else
        {
           i = pucName[1] + 2;     /*���㵱ǰ��������*/
        }

        *pNameLen = i;      /*�������ȷ���*/

        return;
    }

    /* ������UCS2 82 */
    if (SI_PB_ALPHATAG_TYPE_UCS2_82 == pucName[0])
    {
        *pAlphaType = pucName[0];

        if(pucName[1] > (ucNameMax - 4))/* �����ǰ������Ϣ������󳤶ȣ���ֱ�ӽ׽ض� */
        {
           i = ucNameMax -1;
        }
        else
        {
           i = pucName[1] + 3;     /*���㵱ǰ��������*/
        }

        *pNameLen = i;      /*�������ȷ���*/

        return;
    }


    /* ������GSM��ʽ�洢 */
    *pAlphaType = SI_PB_ALPHATAG_TYPE_GSM;

    for (i = 0; i < ucNameMax; i++)         /*������ǰ����������*/
    {
        if (0xFF == pucName[i])
        {
            break;
        }
    }

    *pNameLen = i;      /*�������ȷ���*/

    return;
}

/*****************************************************************************
�� �� ��  :SI_PB_TransPBFromate

��������  :ת����ǰ��һ���绰������Ϊָ�������ݽṹ

�������  :pstPBContent ת���ĵ绰��������Ϣ
           ucIndex ת���ĵ绰����������/��¼��
           pContent ת���ĵ绰������

�������  :pstRecord ת���ĵ绰�����ݽṹ

�� �� ֵ  :VOS_OK �����ɹ�
           VOS_ERR ����ʧ��

���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   : z00100318
    �޸�����   : Creat

*****************************************************************************/
VOS_VOID SI_PB_TransPBFromate(SI_PB_CONTENT_STRU *pstPBContent, VOS_UINT16 usIndex, VOS_UINT8 *pContent, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32 ulResult;
    VOS_UINT32 ulExtInfoNum;
    VOS_UINT8  ucExtRecord;
    VOS_UINT8  aucPhoneNumber[20] = {0};
    VOS_UINT8  *pucExtContent;
    VOS_UINT8  ucExtNumLen;
    VOS_UINT8  ucXdnNumLen;

    ulResult = SI_PB_CheckContentValidity(pstPBContent, pContent);/*��鵱ǰ�������Ƿ���Ч*/

    if(ulResult != VOS_OK)
    {
        pstRecord->ValidFlag = SI_PB_CONTENT_INVALID;     /*��ǵ�ǰ��������Ч*/

        /*ȫ��Ϊ0*/
    }
    else
    {
        pstRecord->ValidFlag = SI_PB_CONTENT_VALID;/*��ǵ�ǰ��������Ч*/

        SI_PB_DecodePBName(pstPBContent->ucNameLen, pContent,
                            &pstRecord->AlphaTagType,&pstRecord->ucAlphaTagLength);

        if(pstRecord->ucAlphaTagLength != 0x00)         /*��ǰ������Ϊ��*/
        {
            if(pstRecord->AlphaTagType == SI_PB_ALPHATAG_TYPE_GSM)  /*����Ӣ��������ͷ��ʼ*/
            {
                /*lint -e534*/
                VOS_MemCpy_s(pstRecord->AlphaTag, pstRecord->ucAlphaTagLength, pContent, pstRecord->ucAlphaTagLength);
                /*lint +e534*/
            }
            else                                                                                        /*�������������ӵڶ����ֽڿ�ʼ*/
            {
                /*ucs2���룬�����ӳ����ֶο�ʼ*/
                /*lint -e534*/
                VOS_MemCpy_s(pstRecord->AlphaTag, pstRecord->ucAlphaTagLength, pContent+1, pstRecord->ucAlphaTagLength);
                /*lint +e534*/
            }
        }

        if ((pContent[pstPBContent->ucNameLen+1] == 0xFF)
            && (pContent[pstPBContent->ucNameLen] == 0x0))
        {
            pstRecord->NumberType   =  PB_NUMBER_TYPE_NORMAL;
        }
        else
        {
            pstRecord->NumberType   =  pContent[pstPBContent->ucNameLen+1];
        }

        ucExtRecord = ((PB_BDN == pstPBContent->enPBType)?\
                        pContent[pstPBContent->ucRecordLen-2]:\
                        pContent[pstPBContent->ucRecordLen-1]);

        ulExtInfoNum  = pstPBContent->ulExtInfoNum;
        pucExtContent = gastEXTContent[ulExtInfoNum].pExtContent;

        ucExtRecord = ((VOS_NULL_PTR == pucExtContent) ? 0xFF : (ucExtRecord));

        if(pContent[pstPBContent->ucNameLen] < 2)           /*��ǰ����Ϊ��*/
        {
            pstRecord->NumberLength = 0;
        }
        else if((0xFF != ucExtRecord)&&(0 != ucExtRecord)&&(VOS_NULL_PTR != pucExtContent)
                &&(ucExtRecord <= gastEXTContent[ulExtInfoNum].usExtTotalNum))
        {
            pucExtContent += (ucExtRecord - 1) * SI_PB_EXT_LEN;
            ucExtNumLen   = (*(pucExtContent + 1) > (SI_PB_NUM_LEN/2))?
                            (SI_PB_NUM_LEN/2) : *(pucExtContent + 1);

            /*lint -e534*/
            VOS_MemCpy_s(aucPhoneNumber, SI_PB_NUM_LEN/2, pContent+(pstPBContent->ucNameLen+2), SI_PB_NUM_LEN/2 );
            VOS_MemCpy_s(aucPhoneNumber + (SI_PB_NUM_LEN/2), SI_PB_NUM_LEN/2, pucExtContent + 2, SI_PB_NUM_LEN/2 );
            /*lint +e534*/

            SI_PB_BcdToAscii((VOS_UINT8)(ucExtNumLen + (SI_PB_NUM_LEN/2)), aucPhoneNumber,
                                pstRecord->Number, &pstRecord->NumberLength);
        }
        else                                                                                /*������������ݿ�ʼ*/
        {
            ucXdnNumLen = ((pContent[pstPBContent->ucNameLen]-1) > (SI_PB_NUM_LEN/2))?
                           (SI_PB_NUM_LEN/2) : (pContent[pstPBContent->ucNameLen]-1);

            SI_PB_BcdToAscii(ucXdnNumLen, &pContent[pstPBContent->ucNameLen+2],
                            pstRecord->Number, &pstRecord->NumberLength);
        }
    }

    pstRecord->Index = usIndex;

    return ;
}

/*****************************************************************************
�� �� ��  :SI_PB_MemSet

��������  :ˢ���ڴ�ΪFF

�������  :ucLen: ˢ�µ��ڴ泤��
           pucMem:ˢ�µ��ڴ��ַ

�������  :��

�� �� ֵ  :��

���ú���  :��

��������  :��

�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   : z00100318
    �޸�����   : Creat

*****************************************************************************/
VOS_VOID SI_PB_MemSet(VOS_UINT8 ucLen, VOS_UINT8 ucValue,VOS_UINT8 *pucMem)
{
    VOS_UINT8 i;

    for(i=0; i<ucLen; i++)
    {
        pucMem[i] = ucValue;
    }

    return;
}

/*****************************************************************************
�� �� ��  :SI_PB_GetBitFromBuf
��������  :�������л�ȡָ��Bitλ��ֵ��
�������  :ucDataBuf:   ��������
           ulBitNo:     Bit�ţ���1��ʼ
�������  :��
�� �� ֵ  : 1:��Ч��0:��Ч
���ú���  :��
�޶���¼  :
1. ��    ��   : 2009��5��19��
    ��    ��   : m00128685
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_GetBitFromBuf(VOS_UINT8 *pucDataBuf, VOS_UINT32 ulBitNo)
{
    VOS_UINT32  ulOffset;
    VOS_UINT8   ucBit;

    if(VOS_NULL_PTR == pucDataBuf)
    {
        PB_ERROR_LOG("SI_PB_GetBitFromBuf: Input Null Ptr");

        return VOS_FALSE;
    }

    ulOffset = (ulBitNo - 1)/ 8;

    ucBit    = (VOS_UINT8)((ulBitNo - 1)%8);

    return (pucDataBuf[ulOffset]>>ucBit)&0x1;
}

/*****************************************************************************
�� �� ��  :SI_PB_CheckEccValidity
��������  :���ECC�����Ƿ�Ϊ��
�������  :pstPBContent:��ǰ�绰���Ļ�����Ϣ
           pContent:�绰������
�������  :��
�� �� ֵ  :VOS_OK:��ѯ�ɹ�
           VOS_ERR:��ѯʧ��
���ú���  :��
��������  :
�޶���¼  :
1. ��    ��   : 2009��12��5��
   ��    ��   : z00100318
   �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_CheckEccValidity(VOS_UINT8 *pContent)
{
    if (VOS_NULL_PTR == pContent)
    {
        PB_ERROR_LOG("SI_PB_CheckEccValidity: Input NULL PTR");

        return VOS_ERR;
    }

    if( 0xFF == pContent[0])
    {
        PB_INFO_LOG("SI_PB_CheckEccValidity: The ECC is Empty");

        return VOS_ERR;
    }
    else
    {
        PB_INFO_LOG("SI_PB_CheckEccValidity: The ECC is Not Empty");

        return VOS_OK;
    }
}

/*****************************************************************************
�� �� ��  :SI_PB_CheckContentValidity

��������  :�򵥼�鵱ǰ�ĵ绰�������Ƿ�Ϊ��

�������  :pstPBContent:��ǰ�绰���Ļ�����Ϣ
           pContent:�绰������

�������  :��

�� �� ֵ  :VOS_OK:��ѯ�ɹ�
           VOS_ERR:��ѯʧ��

���ú���  :��

��������  :

�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   : z00100318
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CheckContentValidity(SI_PB_CONTENT_STRU *pstPBContent, VOS_UINT8 *pContent)
{
    if ((VOS_NULL_PTR == pContent)||(VOS_NULL_PTR == pstPBContent))
    {
        PB_ERROR_LOG("SI_PB_CheckContentValidity: Input NULL PTR");

        return VOS_ERR;
    }

    if(((pContent[pstPBContent->ucNameLen] == 0)||(pContent[pstPBContent->ucNameLen] == 0xFF))
        &&(pContent[0] == 0xFF))/*��������ͺ����Ƿ�Ϊ��*/
    {
        PB_INFO_LOG("SI_PB_CheckContentValidity: The PhoneBook Content is Empty");

        return VOS_ERR;
    }
    else
    {
        PB_INFO_LOG("SI_PB_CheckContentValidity: The PhoneBook Content is Not Empty");

        return VOS_OK;
    }
}

/*****************************************************************************
�� �� ��  :SI_PB_CheckANRValidity

��������  :�򵥼�鵱ǰ�ĵ绰�������Ƿ�Ϊ��

�������  :pstPBContent:��ǰ�绰���Ļ�����Ϣ
           pContent:�绰������

�������  :��

�� �� ֵ  :VOS_OK:��ѯ�ɹ�
           VOS_ERR:��ѯʧ��

���ú���  :��

��������  :

�޶���¼  :
1. ��    ��   : 2007��10��15��
    ��    ��   : m00128685
    �޸�����   : Creat

*****************************************************************************/
VOS_UINT32 SI_PB_CheckANRValidity(VOS_UINT8 *pContent)
{
    if (VOS_NULL_PTR == pContent)
    {
        PB_ERROR_LOG("SI_PB_CheckANRValidity: Input NULL PTR");

        return VOS_ERR;
    }

    if((0xFF == pContent[0])||(0xFF == pContent[1])||(0 == pContent[1]))/*�������Ƿ�Ϊ��*/
    {
        PB_INFO_LOG("SI_PB_CheckANRValidity: The PhoneBook Content is Empty");

        return VOS_ERR;
    }
    else
    {
        PB_INFO_LOG("SI_PB_CheckANRValidity: The PhoneBook Content is Not Empty");

        return VOS_OK;
    }
}



/*****************************************************************************
�� �� ��  :SI_PB_TransANRFromate

��������  :ת����ǰ��һ��ANR�绰��Ϊָ�������ݽṹ

�������  :pstPBContent ת���ĵ绰��������Ϣ
           ucIndex ת���ĵ绰����������/��¼��
           pContent ת���ĵ绰������

�������  :pstRecord ת���ĵ绰�����ݽṹ

�� �� ֵ  :VOS_OK �����ɹ�
           VOS_ERR ����ʧ��

���ú���  :
��������  :
�޶���¼  :
1. ��    ��   : 2009��06��08��
    ��    ��   : m00128685
    �޸�����   : Creat

*****************************************************************************/
VOS_VOID SI_PB_TransANRFromate(VOS_UINT8 ucANROffset,VOS_UINT8 *pANRContent, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32 ulResult;
    VOS_UINT8  ucExtRecord;
    VOS_UINT8  aucPhoneNumber[20] = {0};
    VOS_UINT8  *pucExtContent;
    VOS_UINT8  ucExtNumLen;
    VOS_UINT8  ucAnrNumLen;

    ulResult = SI_PB_CheckANRValidity(pANRContent);/*��鵱ǰ�������Ƿ���Ч*/

    if(ulResult != VOS_OK)
    {
        /*ȫ��Ϊ0*/
        pstRecord->AdditionNumber[ucANROffset].NumberLength = 0;
    }
    else
    {
        pstRecord->ValidFlag = SI_PB_CONTENT_VALID;/*��ǵ�ǰ��������Ч*/

        pstRecord->AdditionNumber[ucANROffset].NumberType = pANRContent[2];

        pucExtContent = gastEXTContent[PB_ADN_CONTENT].pExtContent;

        ucExtRecord = ((VOS_NULL_PTR == pucExtContent)?0xFF:pANRContent[14]);

        if((0xFF != ucExtRecord)&&(VOS_NULL_PTR != pucExtContent)
           &&(ucExtRecord <= gastEXTContent[PB_ADN_CONTENT].usExtTotalNum))
        {
            pucExtContent += (ucExtRecord - 1) * SI_PB_EXT_LEN;
            ucExtNumLen   = (*(pucExtContent + 1) > (SI_PB_NUM_LEN/2))?
                            (SI_PB_NUM_LEN/2) : *(pucExtContent + 1);

            /*lint -e534*/
            VOS_MemCpy_s(aucPhoneNumber, SI_PB_NUM_LEN/2, pANRContent+3, SI_PB_NUM_LEN/2 );
            VOS_MemCpy_s(aucPhoneNumber + (SI_PB_NUM_LEN/2), SI_PB_NUM_LEN/2, pucExtContent + 2, SI_PB_NUM_LEN/2 );
            /*lint +e534*/

            SI_PB_BcdToAscii( (VOS_UINT8)(ucExtNumLen + (SI_PB_NUM_LEN/2)), aucPhoneNumber,
                                pstRecord->AdditionNumber[ucANROffset].Number, &pstRecord->AdditionNumber[ucANROffset].NumberLength);
        }
        else                                                                                /*������������ݿ�ʼ*/
        {
            ucAnrNumLen = ((pANRContent[1]-1) > (SI_PB_NUM_LEN/2))?
                          (SI_PB_NUM_LEN/2) : (pANRContent[1]-1);

            SI_PB_BcdToAscii(ucAnrNumLen, &pANRContent[3],
                            pstRecord->AdditionNumber[ucANROffset].Number,
                            &pstRecord->AdditionNumber[ucANROffset].NumberLength);
        }
    }

    return;
}

/*****************************************************************************
�� �� ��  :SI_PB_TransEMLFromate

��������  :ת��Email�ļ�����Ϊָ�������ݽṹ

�������  :pstPBContent ת���ĵ绰��������Ϣ
           ucIndex ת���ĵ绰����������/��¼��
           pContent ת���ĵ绰������

�������  :pstRecord ת���ĵ绰�����ݽṹ

�� �� ֵ  :VOS_OK �����ɹ�
           VOS_ERR ����ʧ��

���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2009��06��08��
    ��    ��   : m00128685
    �޸�����   : Creat

*****************************************************************************/
VOS_VOID SI_PB_TransEMLFromate(VOS_UINT8 ucEmailMaxLen, VOS_UINT8 *pEMLContent, SI_PB_RECORD_STRU *pstRecord)
{
    VOS_UINT32 i;
    VOS_UINT8  ucEmailLen = 0;

    for(i = 0; i < ucEmailMaxLen; i++)
    {
        if(0xFF == pEMLContent[i])
        {
            break;
        }

        ucEmailLen++;
    }

    if(0 == ucEmailLen)
    {
        pstRecord->Email.EmailLen = 0;
    }
    else
    {
        pstRecord->Email.EmailLen = ucEmailLen;

        pstRecord->ValidFlag = SI_PB_CONTENT_VALID;

        /*lint -e534*/
        VOS_MemCpy_s(pstRecord->Email.Email, ucEmailLen, pEMLContent, ucEmailLen);
        /*lint +e534*/
    }

    return;
}

/*****************************************************************************
�� �� ��  :SI_PB_GetFileCntFromIndex
��������  :���������INDEX��ֵ�õ���Ӧ��EMAIL��ANR�ļ���ƫ�ƣ���1��ʼ��
�������  :ucIndex:   INDEX��ֵ
           pucEMLFileCnt:     ����EMAIL�ļ���ƫ��
�������  :��
�� �� ֵ  : 1:��Ч��0:��Ч
���ú���  :��
�޶���¼  :
1. ��    ��   : 2009��5��19��
    ��    ��   : m00128685
    �޸�����   : Creat
*****************************************************************************/
VOS_UINT32 SI_PB_GetFileCntFromIndex(VOS_UINT16 ucIndex, VOS_UINT8 *pucFileCnt)
{
    VOS_UINT8   i;
    VOS_UINT16  usSum;

    usSum = 0;

    for (i = 0; i < gstPBCtrlInfo.ulADNFileNum; i++)
    {
        if ((ucIndex <= (usSum + gstPBCtrlInfo.astADNInfo[i].ucRecordNum))
            && (ucIndex > usSum))
        {
            break;
        }
        else
        {
            usSum += gstPBCtrlInfo.astADNInfo[i].ucRecordNum;
        }
    }

    if (i >= gstPBCtrlInfo.ulADNFileNum)
    {
        *pucFileCnt = 0;
        return VOS_ERR;
    }
    else
    {
        *pucFileCnt = i + 1;
        return VOS_OK;
    }
}





