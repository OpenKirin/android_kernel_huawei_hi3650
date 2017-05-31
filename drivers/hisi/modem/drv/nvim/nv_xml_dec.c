



/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/
/*lint -save -e537*/
#include "bsp_version.h"
#include "nv_xml_dec.h"
#include "nv_debug.h"
/*lint -restore +e537*/

extern int strcmp(const char *a, const char *b);

/*****************************************************************************
2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958*/
/*xml decode info*/
static XML_DOCODE_INFO xml_ctrl;

/* XML�ؼ���,������0-9,a-z,A-Z */
static s8   g_stlxmkeywordtbl[] = { '<', '>', '/', '=', '"',
                                   ' ', '!', '?', '_', '-',
                                   ',' };

/* XML�ļ�����ʱ��״̬                  */
static XML_ANALYSE_STATUS_ENUM_UINT32 g_stlxmlstatus = XML_ANASTT_ORIGINAL;

/* ��ͨ�ڵ�����                         */
static s8 g_aclnodelabelcommon[]               = "common_NvInfo";

/* Product�ڵ�����                      */
static s8 g_aclnodelabelproduct[]              = "product";

/* Product_NvInfo�ڵ�����                      */
static s8 g_aclnodelabelproductNvInfo[]          = "product_NvInfo";

/* NV�ڵ�����                           */
static s8 g_aclnodelabelnv[]                   = "nv";

/* Cust�ڵ�����                         */
static s8 g_aclnodelabelcust[]                 = "cust";

/* NV id��������                           */
static s8 g_aclpropertyId[]                   = "id";

/* NV ���ȼ���������                          */
static s8 g_aclpropertyWp[]                   = "wp";


/* �ڵ�ʮ������ֵ֮��ķָ���           */
static s8 g_separator                        = ',';

/*****************************************************************************
3 ��������
*****************************************************************************/
/*****************************************************************************
�� �� ��  : XML_WriteErrorLog
��������  : ��¼������Ϣ��Log�ļ�
�������  : ulErrLine ָ����ʱ�Ĵ����к�
          : ulnvid    ָ����ʱ��Ӧ��NV ID
          : ulResult  ָ����ʱ������Ӧ�ķ���ֵ
�������  : ��
�� �� ֵ  : ��
���ú���  : ��
��������  : XML_CheckCharValidity
            XML_ProcXmlOrinigal
            XML_ProcXmlEnterLabel
            XML_ProcXmlIgnore
            XML_ProcXmlNodeLabel
            XML_ProcXmlSingleEndLabel
            XML_ProcXmlEndMustBeRight
            XML_ProcXmlPropertyStart
            XML_ProcXmlPropertyName
            XML_ProcXmlPropertyNameTail
            XML_ProcXmlValueStart
            XML_ProcXmlValueTail
            XML_Analyse
            XML_DecodeXMLFile
            XML_ProcInit
            XML_GetProductId
            XML_CheckXMLKeyWord
            XML_CheckCharValidity
            XML_WriteNVItem
            XML_StringToNvId
            XML_StringToNvValue
            XML_StringToHex
�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
/*lint -save -e958*/
void xml_write_error_log(u32 ulerrorline, u16 ulnvid,
                                u32 ret)
{
    xml_ctrl.g_stlxmlerrorinfo.ulxmlline = xml_ctrl.g_stlxml_lineno;
    xml_ctrl.g_stlxmlerrorinfo.ulstatus  = g_stlxmlstatus;
    xml_ctrl.g_stlxmlerrorinfo.ulcodeline= ulerrorline;
    xml_ctrl.g_stlxmlerrorinfo.usnvid    = ulnvid;
    xml_ctrl.g_stlxmlerrorinfo.ulresult  = (u32)ret;

    return ;
}
/*lint -restore +e958*/

/*****************************************************************************
�� �� ��  : XML_CheckXMLKeyWord
��������  : ��鵱ǰ�ַ����Ƿ���XML�ؼ���
�������  : currentchar ָ��ǰ�ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : ��
��������  : XML_CheckCharValidity

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_checkxmlkeyword(s8 currentchar)
{
    u32 lcount;

    if ((('0' <= currentchar) && ('9' >= currentchar))   /* ��Ч�ַ���0-9  */
        ||(('a' <= currentchar) && ('z' >= currentchar)) /* ��Ч�ַ���a-z  */
        ||(('A' <= currentchar) && ('Z' >= currentchar)))/* ��Ч�ַ���A-Z  */
    {
        return XML_RESULT_SUCCEED;
    }
/*lint -save -e958*/
    /* �� 0-9,a-z,A-Z ֮��� XML�ؼ��� */
    for (lcount=0; lcount<sizeof(g_stlxmkeywordtbl); lcount++)
    {
        if (currentchar == g_stlxmkeywordtbl[lcount])
        {
            return XML_RESULT_SUCCEED;
        }
    }
/*lint -restore +e958*/
    nv_mntn_record("<%s>: err char :%c\n",__func__,currentchar);
    return XML_RESULT_FALIED_BAD_CHAR;
}


/*****************************************************************************
�� �� ��  : XML_CheckCharValidity
��������  : ��鵱ǰ�ַ�����Ч��
�������  : currentchar ָ��ǰ�ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_CheckXMLKeyWord
            XML_WriteErrorLog
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
/*lint -save -e958*/
XML_RESULT_ENUM_UINT32 xml_checkcharvalidity(s8 currentchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    if (('\r' == currentchar)       /* ���Իس�   */
        || ('\t' == currentchar))   /* �����Ʊ�� */
    {
        return XML_RESULT_SUCCEED_IGNORE_CHAR;
    }

    if ('\n' == currentchar)    /* ���Ի���   */
    {
        xml_ctrl.g_stlxml_lineno++;
        return XML_RESULT_SUCCEED_IGNORE_CHAR;
    }

    /* ��ע���е��ַ�������� */
    if ( XML_ANASTT_IGNORE == g_stlxmlstatus)
    {
        return XML_RESULT_SUCCEED;
    }

    /* ���XML�Ĺؼ��� */
    returnval = xml_checkxmlkeyword(currentchar);
    if (XML_RESULT_SUCCEED != returnval)
    {
        printf("returnval = %d\n",returnval);
        xml_write_error_log(__LINE__, 0, returnval);

        return returnval;
    }

    return XML_RESULT_SUCCEED;
}
/*lint -restore +e958*/
/*****************************************************************************
�� �� ��  : XML_StringToNvId
��������  : ���ַ���ת��ʮ���Ƶĸ�ʽ
�������  : pcbuff ָ�ַ���������
�������  : pusretval ָת����ķ���ֵ
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_WriteErrorLog
��������  : XML_WriteNVItem

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_stringtou16(s8  *pcbuff,
                                            u16 *pusretval)
{
    u32 ultemp = 0;  /* �ַ���ת������ʱ���м���� */
    s8   currentchar;
    s8  *pcsrc;

    pcsrc = pcbuff;

    /* ���NV ID�ǿյģ��򷵻ش��� */
    if (0 == *pcsrc)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_NV_ID_IS_NULL);

        return XML_RESULT_FALIED_NV_ID_IS_NULL;
    }

    /* ���ַ���ת��ʮ���Ƶĸ�ʽ */
    while (0 != *pcsrc)
    {
        currentchar = *pcsrc;

        /* �Բ���0��9֮����ַ����������� */
        if ((currentchar < '0') || (currentchar > '9'))
        {
            xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_0_9);
            return XML_RESULT_FALIED_OUT_OF_0_9;
        }

        /* ת��ʮ���Ƹ�ʽ */
        currentchar -= '0';
        ultemp = (ultemp*10) + (u8)currentchar;

        /* ����NV ID�����ֵ */
        if (EN_NV_ID_END <= ultemp)
        {
            xml_write_error_log(__LINE__, (u16)ultemp, XML_RESULT_FALIED_OUT_OF_MAX_VALUE);

            return XML_RESULT_FALIED_OUT_OF_MAX_VALUE;
        }

        pcsrc++;
    }

    /* ��� ת�����ֵ */
    *pusretval = (u16)ultemp;

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
�� �� ��  : XML_StringToHex
��������  : ���ַ�ת��ʮ�����Ƶĸ�ʽ
�������  : pucsrc ��ת�����ַ���
�������  : pucdestת���������
          : pucdestLen ת��������ݳ���
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_WriteErrorLog
��������  : XML_StringToNvValue

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_stringtohex(u8 *pucsrc, u8 *pucdest)
{
    u8  ucurrent;
    u8  uctemp  = 0;
    u16 uscount = 0;

    /* pucsrc�ĳ���һ����ż��,������Ĳ�����֤ */
    while (0 != *pucsrc)
    {
        ucurrent = *pucsrc;

        if ((ucurrent >= 'a') && (ucurrent <= 'f'))
        {
            /* ��Сд�ַ�ת�ɴ�д*/
            ucurrent -= 'a'-'A';
        }

        /* ת��ʮ�����Ƹ�ʽ */
        if ((ucurrent >= 'A') && (ucurrent <= 'F'))
        {
            uscount++;
            uctemp = (u8)(uctemp * 16) + (u8)(ucurrent - 'A') + 10;
        }
        else if ((ucurrent >= '0') && (ucurrent <= '9'))
        {
            uscount++;
            uctemp = (u8)(uctemp * 16) + (u8)(ucurrent - '0');
        }
        else
        {
            /* �Բ���0-9,a-f,A-F֮����ַ����������� */
            xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_0_F);

            return XML_RESULT_FALIED_OUT_OF_0_F;
        } /* end of if ((ucurrent >= 'a') && (ucurrent <= 'f')) */

        /* ��2���ַ�ת����һ��ʮ�����ƺ�,���浽Ŀ�껺������ */
        if (2 == uscount)
        {
            *pucdest++ = uctemp;
            uctemp = 0;
            uscount = 0;
        }

        pucsrc++;
    }

    /* �����ַ���������'\0' */
    *pucdest = 0;

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
�� �� ��  : XML_StringToNvValue
��������  : ���ַ���ת��ʮ�����Ƶĸ�ʽ
�������  : pucbuff ָ�ַ���������
�������  : pucRetBuffת���������
          : pucRetBuffLenת�������ݵĳ���
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_WriteErrorLog
            XML_StringToHex
��������  : XML_WriteNVItem

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_stringtovalue(u8  *pucbuff,
                                                 u8  *pucretbuff,
                                                 u32 *pretbufflen)
{
    XML_RESULT_ENUM_UINT32 returnval = 0;
    u32 ulcount = 0;    /* �ж��Ƿ񱣴浱ǰת�����ֵ */
    u8 *pcsrc;
    u8 *pcdest;
    pcsrc  = pucbuff;
    pcdest = pucbuff;

     /* ���NV VALUE�ǿյģ��򷵻ش��� */
    if (0 == *pcsrc)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_NV_VALUE_IS_NULL);
        return XML_RESULT_FALIED_NV_VALUE_IS_NULL;
    }


    /* �Ȱ�ԭ�ַ����еķָ���ȥ�� */
    while (0 != *pcsrc)
    {
        /* �����ǰ�ַ��Ƿָ��� */
        if (g_separator == *pcsrc)
        {
            /* �����2���ָ���֮��ֻ��һ���ַ�,������ǰ�����һ��'0' */
            if (1 == ulcount)
            {
                *pcdest = *(pcdest-1);
                *(pcdest-1) = '0';
                pcdest++;
            }

            ulcount = 0;
            pcsrc++;

            continue;
        }

        /* �����һ��NV���2���ַ�,������.��<nv id="1">A3E</nvs> */
        if (2 <= ulcount)
        {
            xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_2_CHAR);
            return XML_RESULT_FALIED_OUT_OF_2_CHAR;
        }

        *pcdest++ = *pcsrc++;
        ulcount++;    /* ��¼�ָ���֮���ַ��ĸ��� */
    }


    /* �����ַ���������'\0' */
    *pcdest = '\0';


    /* ��¼ת��������ݳ��� */
    *pretbufflen = (u32)(pcdest - pucbuff)/2;

    /* ת��ʮ�����Ƹ�ʽ */
    pcsrc  = pucbuff;
    pcdest = pucretbuff;

    returnval =  xml_stringtohex(pcsrc, pcdest);

    return returnval;
}

/*****************************************************************************
�� �� ��  : XML_WriteNVItem
��������  : �ѽڵ���Ϣд��NV��
�������  : ��
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : VOS_StrCmp
            XML_StringToNvId
            XML_StringToNvValue
            NV_Write
            XML_WriteErrorLog
��������  : XML_CheckNodeLabelValid
            XML_CheckNodeEndLabelValid
            XML_ProcXmlEnterLabel
�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_write_nv_data(void)
{
    XML_RESULT_ENUM_UINT32 returnval = NV_ERROR;
    u16 usnvitemid  = 0;
    u16 priority = 0xFFFF;
    u32 ulnvitemlen = 0;
    s32    lisnv       = 0;
    s32    liscust     = 0;
    struct nv_ref_data_info_stru ref_info = {0};
    struct nv_file_list_info_stru file_info = {0};
    u32 ulPropertyIndex = 0;
    u8* ref_offset = NULL;

    /* �����ǰ�ڵ㲻����Ч�Ľڵ�,�����κδ��� */
    if (XML_PRODUCT_NODE_STATUS_INVALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
    {
        return XML_RESULT_SUCCEED;
    }

    /* �������ֵΪ��,���ҽڵ�ֵΪ��,�����κδ���, ��<cust/> */
    xml_ctrl.g_stlxmlcurrentnode.stproperty[0].pcpropertyvalue[
                        xml_ctrl.g_stlxmlcurrentnode.stproperty[0].ulvaluelength] = '\0';

    xml_ctrl.g_stlxmlcurrentnode.pcnodevalue[xml_ctrl.g_stlxmlcurrentnode.ulvaluelength] = '\0';

    if ((0 == *xml_ctrl.g_stlxmlcurrentnode.stproperty[0].pcpropertyvalue)
        || (0 == *xml_ctrl.g_stlxmlcurrentnode.pcnodevalue))
    {
        return XML_RESULT_SUCCEED;
    }

    /* ֻ��nv��cust�ڵ�д��NV�� */
    xml_ctrl.g_stlxmlcurrentnode.pcnodelabel[xml_ctrl.g_stlxmlcurrentnode.ullabelendlength] = '\0';

    lisnv = strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel, g_aclnodelabelnv);

    liscust = strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel, g_aclnodelabelcust);

    if ((0 != lisnv) && (0 != liscust))
    {
        return XML_RESULT_SUCCEED;
    }
    for(ulPropertyIndex = 0; ulPropertyIndex <= xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex; ulPropertyIndex++)
    {
        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname[
                    xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulnamelength] = '\0';

        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue[
                            xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength] = '\0';

        if(!strcmp(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname, g_aclpropertyId))
        {
            /* ��id ����ֵת��NV ID */
            returnval = xml_stringtou16(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                                        &usnvitemid);

            if (XML_RESULT_SUCCEED != returnval)
            {
                goto out;
            }
        }
        else if(!strcmp(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname, g_aclpropertyWp))
        {
            /* ��wp����ֵת��priority */
            returnval = xml_stringtou16(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                                        &priority);

            if (XML_RESULT_SUCCEED != returnval)
            {
                goto out;
            }
        }
        else
        {
            /* coverity[uninit_use_in_call] */
            xml_write_error_log(__LINE__, usnvitemid, returnval);
            printf("<%s>: pcpropertyvalue :%s\n",__func__, xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue);
        }

    }

    /* �ѽڵ�ֵת��NV Value */
    ulnvitemlen = 0;

    returnval = xml_stringtovalue((u8 *)xml_ctrl.g_stlxmlcurrentnode.pcnodevalue,
                                  xml_ctrl.g_puclnvitem,
                                  &ulnvitemlen);

    if (XML_RESULT_SUCCEED != returnval)
    {
        xml_write_error_log(__LINE__, usnvitemid, returnval);
        goto out;
    }


    /* д��NV�� */
    /*���xml�д��ڲ����ڵ�NV���д�룬��������*/
    returnval = xml_nv_search_byid((u32)usnvitemid,((u8*)NV_GLOBAL_CTRL_INFO_ADDR),&ref_info,&file_info, (u8**)&ref_offset);
    if(returnval)
    {
        return XML_RESULT_SUCCEED;
    }
	/*���xml�����Ƿ���ȷ,����:����comm����Ϊ֧��1��modem,diff�ļ�ͬʱ����2��diff�����*/
	if(xml_ctrl.card_type > ref_info.modem_num)
	{
        xml_write_error_log(__LINE__, usnvitemid, BSP_ERR_NV_XML_CFG_ERR);
		printf("nv:0x%x xml config error\n", usnvitemid);
		printf("comm xml modem = 0x%x, diff xml modem = 0x%x\n", ref_info.modem_num ,xml_ctrl.card_type);
		return BSP_ERR_NV_XML_CFG_ERR;
	}
    ref_info.nv_off += (xml_ctrl.card_type - NV_USIMM_CARD_1)*ref_info.nv_len;

    returnval = xml_nv_write_to_mem(xml_ctrl.g_puclnvitem,ref_info.nv_len,file_info.file_id,ref_info.nv_off);
    if(returnval)
    {
        xml_write_error_log(__LINE__, usnvitemid, returnval);
        goto out;
    }

    if(0xFFFF != priority)
    {
        xml_nv_write_priority(ref_offset, priority);
    }
    return XML_RESULT_SUCCEED;
out:
    /* ��¼�����NV ID */
    return XML_RESULT_FALIED_WRITE_NV;
}

/*****************************************************************************
�� �� ��  : XML_NodeReset
��������  : ��սڵ���Ϣ
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  : ��
��������  : XML_CheckNodeLabelValid
            XML_CheckNodeEndLabelValid
            XML_ProcXmlEnterLabel

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
void xml_nodereset(void)
{
    u32 ulPropertyIndex = 0;

    /* �ڵ��ǩ��λ,��ʹ�õĳ���Ϊ0  */
    xml_ctrl.g_stlxmlcurrentnode.ullabellength= 0;

    /* �ڵ�ֵ��λ,��ʹ�õĳ���Ϊ0 */
    xml_ctrl.g_stlxmlcurrentnode.ulvaluelength= 0;

    /* �ڵ������ǩ��λ,��ʹ�õĳ���Ϊ0 */
    xml_ctrl.g_stlxmlcurrentnode.ullabelendlength= 0;
    /*xml_ctrl.g_stlxmlcurrentnode.stproperty���±�������0*/
    xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex = 0;
    for(ulPropertyIndex = 0; ulPropertyIndex < XML_NODE_PROPERTY_NUM; ulPropertyIndex++)
    {
        /* �ڵ���������λ,��ʹ�õĳ���Ϊ0 */
        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulnamelength= 0;

        /* �ڵ�����ֵ��λ,��ʹ�õĳ���Ϊ0 */
        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength= 0;
    }
    /*lint -save -e665*/
    memset(xml_ctrl.g_stlxmlcurrentnode.pcnodevalue,0,XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);
    /*lint -restore +e665*/

    return ;
}


/*****************************************************************************
�� �� ��  : xml_write_char_to_buff
��������  : ���ַ���ӽ�ָ�����Ȼ�����
�������  : pcdestChar����ӵ��ַ���
          : pcstrbuff������ַ���ָ��ĵ�ַ��
          : plbufflength�ַ�����ǰ���ȵĵ�ַ
          : ulisnodevalueָpcstrbuff�Ƿ���ָ��Node Value
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_WriteErrorLog
��������  : XML_ProcXmlOrinigal
            XML_ProcXmlEnterLabel
            XML_ProcXmlNodeLabel
            XML_ProcXmlSingleEndLabel
            XML_ProcXmlPropertyStart
            XML_ProcXmlPropertyName
            XML_ProcXmlValueStart

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_write_char_to_buff(s8   cnowchar,
                                                 s8   *pcstrbuff,
                                                 u32 *plbufflength,
                                                 bool   ulisnodevalue)
{
    /* ���Կո� */
    if (' ' == cnowchar)
    {
        return XML_RESULT_SUCCEED;
    }
/*lint -save -e731*/
    /* ����ﵽ��Node Value����󳤶� */
    if ((true == ulisnodevalue)
        && (*plbufflength >= XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_BUFF_LEN);

        return XML_RESULT_FALIED_OUT_OF_BUFF_LEN;
    }


    /* ����ﵽ��Node Lable����󳤶� */
    if ((false == ulisnodevalue)
        && (*plbufflength >= XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_BUFF_LEN);

        return XML_RESULT_FALIED_OUT_OF_BUFF_LEN;
    }
/*lint -restore +e731*/
    /* �����ַ��ӽ������� */
    *(pcstrbuff + *plbufflength) = cnowchar;

    /* ���������ȼ�1 */
    (*plbufflength)++;

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
�� �� ��  : XML_CheckNodeLabelValid
��������  : ��鵱ǰ��ǩ�Ƿ�����Ч��ǩ
�������  : ��
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : VOS_StrCmp
��������  : XML_ProcXmlNodeLabel
            XML_ProcXmlPropertyStart
            XML_ProcXmlValueTail
�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_checknodelabelvalid(void)
{
    u32 ulPropertyIndex = 0;

    /* �жϸñ�ǩ�Ƿ���Ч */
    xml_ctrl.g_stlxmlcurrentnode.pcnodelabel[xml_ctrl.g_stlxmlcurrentnode.ullabellength] = '\0';

    /* �����ǰ�ڵ�Ϊ��Ч״̬,��Ҫ����ǩ�Ƿ�Ϊ��Ч�ڵ� */
    if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                        g_aclnodelabelcommon))
    {
        /* �����<Common_NvInfo>��ǩ,�����ýڵ�Ϊ��Ч״̬ */
        xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }
    /* �����<Cust>��ǩ,�����ýڵ�Ϊ��Ч״̬ */
    if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             g_aclnodelabelcust))
    {
        xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }
    /* �����ǰ�ڵ�Ϊ��Ч״̬,��Ҫ����ǩ�Ƿ�Ϊ��Ч�ڵ� */
    if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                        g_aclnodelabelproductNvInfo))
    {
        /* �����<product_NvInfo>��ǩ,�����ýڵ�Ϊ��Ч״̬ */
        xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }


    if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             g_aclnodelabelproduct))
    {

        ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;

        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue[
                      xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength] = '\0';

        /*��һ������product�ڵ�����Ϊ��Ч�ڵ�*/
        /* �����<product>��ǩ��Product id�뵱ǰ������ͬ,�����ýڵ�Ϊ��Ч״̬ */
        xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_INVALID;

        if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                            xml_ctrl.g_stlxmlproductinfo.acproductid))
        {
            xml_ctrl.g_stlxmlproductinfo.envalidnode= XML_PRODUCT_NODE_STATUS_VALID;
            xml_ctrl.g_stlxmlproductinfo.ulnodelevel++;
        }
        else/*product ���Խڵ���ת*/
        {
            xml_ctrl.g_stlxmlproductinfo.envalidnode     = XML_PRODUCT_NODE_STATUS_INVALID;
            xml_ctrl.g_stlxmlproductinfo.enxmldecodejump = XML_DECODE_STATUS_2JUMP;
        }
        return XML_RESULT_SUCCEED;
    }

    if (XML_PRODUCT_NODE_STATUS_VALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
    {
        /* �ڽڵ�Ϊ��Ч״̬�£���Product�ڵ㣬Ҫ��¼<product>�ڵ���ֵĴ��� */
        if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                            g_aclnodelabelproduct))
        {
            xml_ctrl.g_stlxmlproductinfo.ulnodelevel++;
        }

        return XML_RESULT_SUCCEED;
    }

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
�� �� ��  : XML_CheckNodeEndLabelValid
��������  : ��鵱ǰ������ǩ�Ƿ�����Ч�ڵ�Ľ�����ǩ
�������  : ��
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_WriteNVItem
            VOS_StrCmp
            XML_NodeReset
��������  : XML_ProcXmlSingleEndLabel

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_checknodeendlabelvalid(void)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* д�ڵ���Ϣ��NV�� */
    returnval = xml_write_nv_data();

    if (XML_RESULT_SUCCEED != returnval)
    {
        return returnval;
    }

    xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend[xml_ctrl.g_stlxmlcurrentnode.ullabelendlength]='\0';

    if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                        g_aclnodelabelproduct))
    {
        if (XML_PRODUCT_NODE_STATUS_VALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
        {
            xml_ctrl.g_stlxmlproductinfo.ulnodelevel--;

            if (0 == xml_ctrl.g_stlxmlproductinfo.ulnodelevel)
            {
                /* ���һ����Ч��</product>��ǩ����ʱ����������XML�ļ��Ľ��� */
                xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_FINISHED;
                xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
            }
        }
    }
    else if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                             g_aclnodelabelcommon))
    {
        /* </Common_NvInfo>��ǩ����ʱ,�ѽڵ�״ֻ̬Ϊ��Ч ,ͬʱ��Ϊ����ת״̬*/
        xml_ctrl.g_stlxmlproductinfo.envalidnode     = XML_PRODUCT_NODE_STATUS_INVALID;
        xml_ctrl.g_stlxmlproductinfo.enxmldecodejump = XML_DECODE_STATUS_JUMP;
    }
    else if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                             g_aclnodelabelcust))
    {
        /* </Cust>��ǩ����ʱ,�ѽڵ�״ֻ̬Ϊ��Ч */
        xml_ctrl.g_stlxmlproductinfo.envalidnode = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                             g_aclnodelabelproductNvInfo))
    {
        /* ��һ��</product_NvInfo>��ǩ����ʱ,ͬ����Ҫ��������XML�ļ��Ľ���*/
        xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_FINISHED;
        xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else
    {
        /* Do nothing */

    } /* end of if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcnodelabelend, */

    /* </xx>��ǩ����ʱ����սڵ���Ϣ */
    xml_nodereset();

    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
�� �� ��  : XML_CreateAProperty
��������  : ���ڴ��д���һ�����Բ���ʼ��
�������  : ��
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : VOS_MemAlloc
            XML_WriteErrorLogs
��������  : XML_CreateANode

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_createaproperty( void )
{
    u32 propertyIndex = 0;

    for(propertyIndex = 0;propertyIndex < XML_NODE_PROPERTY_NUM; propertyIndex++)
    {
        /* �����������ڴ�,+1Ϊ�����ַ����������� */
        xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].ulnamelength = 0; /* ��ʹ�õĳ��� */

        xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].pcpropertyname
                                    = (s8*)nv_malloc(
                                       XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

        if (NULL == xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].pcpropertyname)
        {
             xml_write_error_log(__LINE__, propertyIndex, XML_RESULT_FALIED_MALLOC);

            return XML_RESULT_FALIED_MALLOC;
        }

        /* ��������ֵ�ڴ�,+1Ϊ�����ַ����������� */
        xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].ulvaluelength = 0; /* ��ʹ�õĳ��� */


        xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].pcpropertyvalue
                                    = (s8*)nv_malloc(
                                       XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);
        if (NULL == xml_ctrl.g_stlxmlcurrentnode.stproperty[propertyIndex].pcpropertyvalue)
        {
            xml_write_error_log(__LINE__, propertyIndex, XML_RESULT_FALIED_MALLOC);

            return XML_RESULT_FALIED_MALLOC;
        }
    }
    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
�� �� ��  : XML_CreateANode
��������  : ����һ���½ڵ�
�������  : ��
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : VOS_MemAlloc
            XML_CreateAProperty
            XML_WriteErrorLog
��������  : XML_ProcInit

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_createanode(void)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;


    /* ����һ�������� */
    returnval = xml_createaproperty();

    if(XML_RESULT_SUCCEED != returnval)
    {
        return returnval;
    }

    /* ����ڵ��ǩ�ڴ�,+1Ϊ�����ַ�����������*/
    xml_ctrl.g_stlxmlcurrentnode.ullabellength = 0; /* ��ʹ�õĳ��� */



    xml_ctrl.g_stlxmlcurrentnode.pcnodelabel = (s8*)nv_malloc(
                                      XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (NULL ==  xml_ctrl.g_stlxmlcurrentnode.pcnodelabel)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* ����ڵ��β������ǩ�ڴ�,+1Ϊ�����ַ����������� */
    xml_ctrl.g_stlxmlcurrentnode.ullabelendlength = 0; /* ��ʹ�õĳ��� */

    xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend = (s8*)nv_malloc(
                                        XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (NULL ==  xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* ����ڵ�ֵ�ڴ�,+1Ϊ�����ַ����������� */
    xml_ctrl.g_stlxmlcurrentnode.ulvaluelength = 0; /* ��ʹ�õĳ��� */

    xml_ctrl.g_stlxmlcurrentnode.pcnodevalue = (s8*)nv_malloc(
                                      XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);

    if (NULL == xml_ctrl.g_stlxmlcurrentnode.pcnodevalue)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    return returnval;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlOrinigal
��������  : ״̬������������ʼ״̬�Ĵ�����
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_AddACharToBuff
            XML_WriteErrorLog
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_procxmlorginal(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;

    /* ����<�����״̬ */
    if ('<' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_ENTER_LABLE;
        return XML_RESULT_SUCCEED;
    }

    /* ����>,/,",=���ʾXML�﷨���� */
    if (('>' == cnowchar)
         ||('/' == cnowchar)
         ||('"' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);
        nv_mntn_record("%s  err char %c \n",__func__,cnowchar);
        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

/*lint -save -e747*/
    if (XML_PRODUCT_NODE_STATUS_VALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
    {
        /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
        returnval = xml_write_char_to_buff(cnowchar,
                                     xml_ctrl.g_stlxmlcurrentnode.pcnodevalue,
                                     &(xml_ctrl.g_stlxmlcurrentnode.ulvaluelength),
                                     true);
    }
/*lint -restore +e747*/

    return returnval;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlIgnore
��������  : ״̬�������������Դ�����
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : ��
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_procxmlignore(s8 cnowchar)
{

    /* ֱ��������ǩ��β������һֱ���� */
    if ('>' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;
    }
    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlSingleEndLabel
��������  : ״̬������������������Ľ�β��ǩ�Ĵ���
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_AddACharToBuff
            XML_CheckNodeEndLabelValid
            XML_WriteErrorLog
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_proc_xmlsingle_endlabel(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    returnval = XML_RESULT_SUCCEED;

    /* ����<�����״̬ */
    if ('>' == cnowchar)
    {
        /* ���״̬ */
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        /* ������������ǩ�Ƿ���Ч */
        returnval = xml_checknodeendlabelvalid();

        return returnval;
    }

    /* ����<,/,",=���ʾXML�﷨���� */
    if (('<' == cnowchar)
         ||('"' == cnowchar)
         ||('/' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }
/*lint -save -e747*/
    /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
    returnval = xml_write_char_to_buff(cnowchar,
                                  xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend,
                                  &(xml_ctrl.g_stlxmlcurrentnode.ullabelendlength),
                                  false);
/*lint -restore +e747*/
    return returnval;
}


/*****************************************************************************
�� �� ��  : xml_checknode_rightlabel
��������  : must be right�����ʽ�ڵ㴦��
�������  : ��
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_WriteNVItem
            VOS_StrCmp
            XML_NodeReset
��������  : XML_ProcXmlSingleEndLabel

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_checknode_rightlabel(void)
{
    u32 ulPropertyIndex = 0;

    /* �жϸñ�ǩ�Ƿ���Ч */
    xml_ctrl.g_stlxmlcurrentnode.pcnodelabel[xml_ctrl.g_stlxmlcurrentnode.ullabellength] = '\0';

    if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                        g_aclnodelabelproduct))
    {
        ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;

        xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue[
                      xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength] = '\0';

        /* ��ʽ<product product_id="123456"/>����product id�뵥��product id��ͬ��������XML�ļ��Ľ��� */
        if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                            xml_ctrl.g_stlxmlproductinfo.acproductid))
        {
            xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_FINISHED;
            xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
        }
        else
        {
            xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
        }
    }
    else if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             g_aclnodelabelcommon))
    {
        /* <Common_NvInfo/>��ǩ����ʱ,�ѽڵ�״ֻ̬Ϊ��Ч ,ͬʱ��Ϊ����ת״̬*/
        xml_ctrl.g_stlxmlproductinfo.envalidnode     = XML_PRODUCT_NODE_STATUS_INVALID;
        xml_ctrl.g_stlxmlproductinfo.enxmldecodejump = XML_DECODE_STATUS_JUMP;
    }
    else if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             g_aclnodelabelcust))
    {
        /* <Cust/>��ǩ����ʱ,�ѽڵ�״ֻ̬Ϊ��Ч */
        xml_ctrl.g_stlxmlproductinfo.envalidnode = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else if (0 == strcmp(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                             g_aclnodelabelproductNvInfo))
    {
        /* <product_NvInfo/>��ǩ����ʱ,ͬ����Ҫ��������XML�ļ��Ľ���*/
        xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_FINISHED;
        xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else
    {
        /* Do nothing */

    }

    /* <xx/>��ǩ����ʱ����սڵ���Ϣ */
    xml_nodereset();

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlEndMustBeRight
��������  : ״̬��������������Lable/�ȴ�>
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_WriteNVItem
            XML_NodeReset
            XML_WriteErrorLog
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_procxmlend_mustberight(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* ���Կո� */
    if (' ' == cnowchar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* ��������>,���ʾXML�﷨���� */
    if ('>' != cnowchar)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* ���״̬ */
    g_stlxmlstatus = XML_ANASTT_ORIGINAL;

    /*must be right need to check label*/
    returnval = xml_checknode_rightlabel();

    if (XML_RESULT_SUCCEED != returnval)
    {
        return returnval;
    }

    if (XML_PRODUCT_NODE_STATUS_VALID == xml_ctrl.g_stlxmlproductinfo.envalidnode)
    {
        /* д�ڵ���Ϣ��NV�� */
        returnval = xml_write_nv_data();

        if (XML_RESULT_SUCCEED != returnval)
        {
            return returnval;
        }

        /* <xx/>��ǩ����ʱ����սڵ���Ϣ */
        xml_nodereset();
    }

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlEnterLabel
��������  : ״̬��������������ڵ��Ĵ���
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_CheckNodeLabelValid
            XML_AddACharToBuff
            XML_WriteErrorLog
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_proc_xml_node_label(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* ����/����>���߿ո�˵��Node�����ֽ����� */
    if ('/' == cnowchar)
    {
        /* ��������β�����ڵ�,�¸��ֽ�һ����> */
        g_stlxmlstatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* ��ǩ���� */
    if ('>' == cnowchar)
    {
        /* ���״̬ */
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        /* ��鵱ǰ�ڵ�����Ч�ڵ� */
        returnval = xml_checknodelabelvalid();

        return returnval;
    }

    /* ��ǩ���ֽ���,�������Խ���״̬ */
    if (' ' == cnowchar)
    {
        /* ���״̬ */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_START;

        return XML_RESULT_SUCCEED;
    }

    /* ����<,",=���ʾXML�﷨���� */
    if (('<' == cnowchar)
         ||('"' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0,XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }
/*lint -save -e747*/
    /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
    returnval = xml_write_char_to_buff(cnowchar,
                                     xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                                     &(xml_ctrl.g_stlxmlcurrentnode.ullabellength),
                                     false);
/*lint -restore +e747*/
    return returnval;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlEnterLabel
��������  : ״̬��������������Label��Ĵ���
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_WriteNVItem
            XML_NodeReset
            XML_AddACharToBuff
            XML_WriteErrorLog
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_proc_xml_enter_label(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;

    /* �������а汾��Ϣ */
    if ('?' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_IGNORE;

        return XML_RESULT_SUCCEED;
    }

    /* �������� */
    if ('!' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_IGNORE;

        return XML_RESULT_SUCCEED;
    }

    /* ����β�ڵ��ǩ */
    if ('/' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_SINGLE_ENDS_LABLE;

        return XML_RESULT_SUCCEED;
    }

    /* ������ǩ���� */
    if ('>' == cnowchar)
    {
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        return XML_RESULT_SUCCEED;
    }

    /* ����<,",=���ʾXML�﷨���� */
    if (('<' == cnowchar)
         ||('"' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);
        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* �����ո� */
    if (' ' != cnowchar)
    {
        /* д�ڵ���Ϣ��NV�� */
        returnval = xml_write_nv_data();

        if (XML_RESULT_SUCCEED != returnval)
        {
            return returnval;
        }

        /* ����һ���½ڵ�ʱ������սڵ���Ϣ */
        xml_nodereset();

        /* ���״̬����ʾ����һ���½ڵ� */
        g_stlxmlstatus = XML_ANASTT_NODE_LABLE;
/*lint -save -e747*/
        /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
        returnval = xml_write_char_to_buff(cnowchar,
                                         xml_ctrl.g_stlxmlcurrentnode.pcnodelabel,
                                         &(xml_ctrl.g_stlxmlcurrentnode.ullabellength),
                                         false);
/*lint -restore +e747*/
    }

    return returnval;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlPropertyStart
��������  : ״̬�����������������ԵĽ���
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_CheckNodeLabelValid
            XML_AddACharToBuff
            XML_WriteErrorLog
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_proc_xml_propertystart(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;
    u32 ulPropertyIndex = 0;


    /* ����β�ڵ��ǩ */
    if ('/' == cnowchar)
    {
        /* ���״̬ */
        g_stlxmlstatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* ��ǩ���� */
    if ('>' == cnowchar)
    {
        /* ���״̬ */
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        /* ��鵱ǰ�ڵ���Ч */
        returnval = xml_checknodelabelvalid();

        return returnval;
    }

    /* ����<,",=���ʾXML�﷨���� */
    if (('<' == cnowchar)
         ||('"' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* ����״̬ */
    g_stlxmlstatus = XML_ANASTT_PROPERTY_NAME_START;

    ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;
/*lint -save -e747*/
    returnval = xml_write_char_to_buff(cnowchar,
                  xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname,
                  &(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulnamelength),
                  FALSE);
/*lint -restore +e747*/

    return returnval;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlPropertyName
��������  : ״̬�����������������ֵĽ���
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_AddACharToBuff
            XML_WriteErrorLog
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_proc_xml_propertyname(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;
    u32 ulPropertyIndex = 0;

    /* �ȴ�=��������ֵ���� */
    if ('=' == cnowchar)
    {
        /* ��״̬ */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_NAME_END;

        return XML_RESULT_SUCCEED;
    }

    /* ����<,>,/,"���ʾXML�﷨���� */
    if (('<' == cnowchar)||('>' == cnowchar)
        ||('/' == cnowchar)||('"' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;
/*lint -save -e747*/
    /* �����������еĿո����, �� <nv i d="123"> */
    returnval = xml_write_char_to_buff(cnowchar,
                  xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname,
                  &(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulnamelength),
                  false);
/*lint -restore +e747*/

    return returnval;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlPropertyNameTail
��������  : ״̬�����������������ֽ������ȴ�"������ֵ��ʼ
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_WriteErrorLog
��������  : XML_Analyse

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_proc_xml_propertyname_tail(s8 cnowchar)
{

    /* �����ո� */
    if ( ' ' == cnowchar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* �ȴ�" */
    if ('"' == cnowchar)
    {
        /* ����״̬ */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_VALUE_START;

        return XML_RESULT_SUCCEED;
    }

    /* ��������"�����ʾXML�﷨���� */
    xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

    return XML_RESULT_FALIED_BAD_SYNTAX;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlValueStart
��������  : ״̬�����������������ֽ������ȴ�"������ֵ����
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_AddACharToBuff
            XML_WriteErrorLog
��������  : XML_Analyse
��������  :

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_proc_xml_valuestart(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval = XML_RESULT_SUCCEED;
    u32 ulPropertyIndex = 0;

    /* ����" */
    if ('"' == cnowchar)
    {
        /* ��״̬,���ؿ�ʼ�������Ե�״̬ */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_VALUE_END;

        return XML_RESULT_SUCCEED;
    }

    /* ����<,>,/,=���ʾXML�﷨���� */
    if (('<' == cnowchar)
         ||('>' == cnowchar)
         ||('/' == cnowchar)
         ||('=' == cnowchar))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    ulPropertyIndex = xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex;
/*lint -save -e747*/
    /* �ѵ�ǰ�ַ��ӵ�����ֵ�� */
    returnval = xml_write_char_to_buff(cnowchar,
                  xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue,
                  &(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].ulvaluelength),
                  false);
/*lint -restore +e747*/
    return returnval;
}


/*****************************************************************************
�� �� ��  : XML_ProcXmlValueTail
��������  : ״̬�����������������ֽ������ȴ�"������ֵ����
�������  : ��ǰ������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_CheckNodeLabelValid
            XML_WriteErrorLog
��������  : XML_Analyse
��������  :

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_proc_xml_valuetail(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* �ո���һ�����Խ�����ʼ */
    if (' ' == cnowchar)
    {
        /* ���״̬,���ؿ�ʼ�������Ե�״̬ */
        g_stlxmlstatus = XML_ANASTT_PROPERTY_START;
        xml_ctrl.g_stlxmlcurrentnode.ulPropertyIndex++;
        return XML_RESULT_SUCCEED;
    }

    /* ����'/' */
    if ('/' == cnowchar)
    {
        /* ���״̬ */
        g_stlxmlstatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* ����'>' */
    if ('>' == cnowchar)
    {
        /* ���״̬,���ؿ�ʼ�������Ե�״̬ */
        g_stlxmlstatus = XML_ANASTT_ORIGINAL;

        /* ��鵱ǰ�ڵ���Ч */
        returnval = xml_checknodelabelvalid();

        return returnval;
    }

    /* ��������>,/���ʾXML�﷨���� */
    xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

    return XML_RESULT_FALIED_BAD_SYNTAX;
}

/*****************************************************************************
�� �� ��  : XML_Analyse
��������  : ��״̬��
�������  : ��ǰ�������ַ�
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_CheckCharValidity
            XML_ProcXmlOrinigal
            XML_ProcXmlEnterLabel
            XML_ProcXmlIgnore
            XML_ProcXmlNodeLabel
            XML_ProcXmlSingleEndLabel
            XML_ProcXmlEndMustBeRight
            XML_ProcXmlPropertyStart
            XML_ProcXmlPropertyName
            XML_ProcXmlPropertyNameTail
            XML_ProcXmlValueStart
            XML_ProcXmlValueTail
��������  : XML_DecodeXMLFile

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
/*Global map table used to find the function according the xml analyse status.*/
XML_FUN g_uslxmlanalysefuntbl[] =
{
    xml_procxmlorginal,         /* ��ʼ״̬�µĴ���                  */
    xml_proc_xml_enter_label,       /* ����Lable��Ĵ���                 */
    xml_procxmlignore,           /* ���Ի�ע��״̬��ֱ������">"����   */
    xml_proc_xml_node_label,        /* ��ǩ���ֿ�ʼ                      */
    xml_proc_xmlsingle_endlabel,   /* ��׼�Ľ�β��ǩ</XXX>              */
    xml_procxmlend_mustberight,   /* ���� <XXX/>�ı�ǩ,�ڽ�����/��״̬ */
    xml_proc_xml_propertystart,    /* ��ʼ��������                      */
    xml_proc_xml_propertyname,     /* ��ʼ������������                  */
    xml_proc_xml_propertyname_tail, /* �������ֽ������ȴ�"������ֵ��ʼ   */
    xml_proc_xml_valuestart,       /* ����ֵ��ʼ                        */
    xml_proc_xml_valuetail,        /* ����ֵ����                        */
};

XML_RESULT_ENUM_UINT32 xml_analyse(s8 cnowchar)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* ��鵱ǰ�ַ�����Ч�� */
    returnval = xml_checkcharvalidity(cnowchar);

    if (XML_RESULT_SUCCEED_IGNORE_CHAR == returnval)
    {
        /* ����������ԣ����������ַ� */
        return XML_RESULT_SUCCEED;
    }

    if (XML_RESULT_FALIED_BAD_CHAR == returnval)
    {
        /* ��������Ƿ��ַ�����ֹͣ���� */
        return XML_RESULT_FALIED_BAD_CHAR;
    }
    /* ����XML����ʱ����Ӧ״̬�Ķ�Ӧ���� */
    returnval = g_uslxmlanalysefuntbl[g_stlxmlstatus](cnowchar);

    return returnval;
}

/*****************************************************************************
�� �� ��  : XML_DecodeXMLFile
��������  : ��ȡXML�ļ����ݣ����н���
�������  : lFileָ�򿪵��ļ�������
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : DRV_FILE_READ
            mdrv_file_close
            XML_Analyse
            XML_WriteErrorLog
��������  : XML_DecodeMain

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_decode_xml_file(FILE* pfile)
{
    s32               lreaded = 0;       /* �������ֽ��� */
    s32               lcount;            /* ������������ */
    XML_RESULT_ENUM_UINT32  returnval;



    /*read 4k*/
    lreaded = nv_file_read((u8*)(xml_ctrl.g_pclfilereadbuff),1,XML_FILE_READ_BUFF_SIZE,pfile);
    if((0 == lreaded)||(lreaded > XML_FILE_READ_BUFF_SIZE)||(lreaded < 0))
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);
        return XML_RESULT_FALIED_READ_FILE;
    }


    while(0 != lreaded)
    {
        for(lcount = 0;lcount < lreaded; lcount++)
        {
            returnval = xml_analyse(*(xml_ctrl.g_pclfilereadbuff + lcount));
            if(XML_RESULT_SUCCEED != returnval)
            {
                /* ��������������ֹͣ���� */
                return returnval;
            }

            /* �ж��Ƿ������� */
            if (XML_DECODE_STATUS_FINISHED
                == xml_ctrl.g_stlxmlproductinfo.enxmldecodestate)
            {
                nv_mntn_record("%s: xml decode success !\n",__func__);
                return XML_RESULT_SUCCEED;
            }

            /*������common�ڵ�֮���ж��Ƿ���Ҫ��ת*/
            if((XML_DECODE_STATUS_JUMP == xml_ctrl.g_stlxmlproductinfo.enxmldecodejump) &&
               (XML_DECODE_STATUS_JUMP == xml_ctrl.g_stlxmljumpflag))
            {
                nv_mntn_record("%s: product info decode jump  0x%x!\n",__func__,xml_ctrl.g_stlxmljumpinfo.productCatOff);
                nv_file_seek(pfile,(s32)(xml_ctrl.g_stlxmljumpinfo.productCatOff),SEEK_SET);
                xml_ctrl.g_stlxmlproductinfo.enxmldecodejump= XML_DECODE_STATUS_NOJUMP;
                g_stlxmlstatus = XML_ANASTT_ORIGINAL;
                break;
            }

            /*product �ڵ������ת*/
            if((XML_DECODE_STATUS_2JUMP == xml_ctrl.g_stlxmlproductinfo.enxmldecodejump) &&
               (XML_DECODE_STATUS_JUMP == xml_ctrl.g_stlxmljumpflag))
            {
                nv_mntn_record("%s: product id decode jump  0x%x!\n",__func__,xml_ctrl.g_stlxmljumpinfo.productIdOff);
                nv_file_seek(pfile,(s32)(xml_ctrl.g_stlxmljumpinfo.productIdOff),SEEK_SET);
                xml_ctrl.g_stlxmljumpflag = XML_DECODE_STATUS_NOJUMP;
                xml_ctrl.g_stlxmlproductinfo.enxmldecodejump = XML_DECODE_STATUS_NOJUMP;
                g_stlxmlstatus = XML_ANASTT_ORIGINAL;
                break;
            }
        }

        memset(xml_ctrl.g_pclfilereadbuff,0,XML_FILE_READ_BUFF_SIZE);

        lreaded = nv_file_read((u8*)(xml_ctrl.g_pclfilereadbuff),1,XML_FILE_READ_BUFF_SIZE,pfile);
        if((lreaded > XML_FILE_READ_BUFF_SIZE)||(lreaded < 0))
        {

            xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);
            return XML_RESULT_FALIED_READ_FILE;
        }
    }

    /* ���ulnodelevel��Ϊ0��˵��<product>û���������� */
    if (0 != xml_ctrl.g_stlxmlproductinfo.ulnodelevel)
    {
        xml_write_error_log(__LINE__,0,XML_RESULT_FALIED_PRODUCT_MATCH);
        return XML_RESULT_FALIED_PRODUCT_MATCH;
    }

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
�� �� ��  : XML_GetProductId
��������  : ��õ�ǰ�����product id
�������  : ��
�������  : pcProductId ��õ�ǰ�����product ids
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : VOS_MemSet
            DRV_MEM_VERCTRL
            XML_WriteErrorLog
��������  : XML_ProcInit

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_getproductid(void)
{
	u32    lproductid;

	/* ����ڴ� */
	memset(xml_ctrl.g_stlxmlproductinfo.acproductid, 0, XML_MAX_HARDWARE_LEN);

	/* ȡ�õ�ǰ�����Product id */
	lproductid=  bsp_get_version_info()->board_id;/*get hardware version*/

	xml_ctrl.g_stlxmlproductid = lproductid;

    /* coverity[secure_coding] */
    sprintf(xml_ctrl.g_stlxmlproductinfo.acproductid,"%d",lproductid);

    return XML_RESULT_SUCCEED;
}


/*****************************************************************************
�� �� ��  : XML_InitGlobal
��������  : ��ʼ��ȫ�ֱ���
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  : ��
��������  : XML_ProcInit

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
void xml_initglobal(void)
{
    /* ��ʼ��Product�ڵ���Ϣ */
    xml_ctrl.g_stlxmlproductinfo.envalidnode      = XML_PRODUCT_NODE_STATUS_INVALID;
    xml_ctrl.g_stlxmlproductinfo.enxmldecodestate = XML_DECODE_STATUS_DECODING;
    xml_ctrl.g_stlxmlproductinfo.enxmldecodejump  = XML_DECODE_STATUS_JUMP_BUTT;
    xml_ctrl.g_stlxmlproductinfo.ulnodelevel      = 0; /* ��¼product�ڵ���ֵĴ��� */

    /* ��ʼ����ǰ״̬ */
    g_stlxmlstatus = XML_ANASTT_ORIGINAL;

    /* ���ڼ�¼��ȡXML�ļ������� */
    xml_ctrl.g_stlxml_lineno    = 1;

    /*���ڼ�¼�ܷ���ת��־*/
    xml_ctrl.g_stlxmljumpflag   = XML_DECODE_STATUS_JUMP_BUTT;
    /*���ڼ�¼��תƫ�� ��תʱƫ��Ϊ0�򱣳ֵ�ǰƫ��*/
    memset(&xml_ctrl.g_stlxmljumpinfo,0,sizeof(xml_ctrl.g_stlxmljumpinfo));

    return ;
}


/*
 * search product info through product id
 */
s32  xml_search_productinfo(u32 product_id,u8* pdata,XNV_MAP_PRODUCT_INFO* product_info)
{
    u32 low;
    u32 high;
    u32 mid;
    u32 offset;
    XNV_MAP_HEAD_STRU * map_file = (XNV_MAP_HEAD_STRU*)pdata;

    low  = 1;
    high = map_file->product_num;

    while(low <= high)
    {
        mid = (low+high)/2;
        offset = sizeof(XNV_MAP_HEAD_STRU)+(mid-1)*sizeof(XNV_MAP_PRODUCT_INFO);

        memcpy((u8*)product_info,(u8*)pdata+offset,sizeof(XNV_MAP_PRODUCT_INFO));

        if(product_id < product_info->product_id)
        {
            high = mid - 1;
        }
        else if(product_id > product_info->product_id)
        {
            low = mid + 1;
        }
        else
        {
            return 0;
        }
    }
    return -1;
}

void xml_getjumpinfo(s8* map_path)
{
    FILE* fp = NULL;
    s32 ret = 0;
    u32 file_len;
    XNV_MAP_HEAD_STRU* map_file = NULL;
    XNV_MAP_PRODUCT_INFO product_info = {0};

    if(!map_path)
        return;
    fp = nv_file_open(map_path,NV_FILE_READ);
    if(!fp)
        return;
    file_len = nv_get_file_len(fp);

    /* coverity[negative_returns] */
    map_file = (XNV_MAP_HEAD_STRU*)nv_malloc(file_len);
    if(!map_file)
    {
        nv_file_close(fp);
        return;
    }

    ret = nv_file_read((u8*)map_file,1,file_len,fp);
/*lint -save -e737*/
    if(ret != file_len)
    {
        nv_mntn_record("%s  ret :%d,file_len :0x%x\n",__func__,ret,file_len);
        goto out;
    }
/*lint -restore +e737*/
    ret = xml_search_productinfo((u32)(xml_ctrl.g_stlxmlproductid),(u8*)map_file,&product_info);
    if(ret)
        goto out;

    memcpy(&xml_ctrl.g_stlxmljumpinfo,&product_info,sizeof(product_info));
    xml_ctrl.g_stlxmljumpflag = XML_DECODE_STATUS_JUMP;

    nv_file_close(fp);
    nv_free(map_file);
    return;

out:
    nv_file_close(fp);
    nv_free(map_file);
    memset(&xml_ctrl.g_stlxmljumpinfo,0,sizeof(xml_ctrl.g_stlxmljumpinfo));
    xml_ctrl.g_stlxmljumpflag = XML_DECODE_STATUS_NOJUMP;
    return;
}


/*****************************************************************************
�� �� ��  : XML_ProcInit
��������  : ��ʱ����ģ��ȫ����������
�������  : ��
�������  : ��
�� �� ֵ  : XML_RESULT_ENUM_UINT32
���ú���  : XML_InitGlobal
            XML_GetProductId
            XML_CreateANode
            VOS_MemAlloc
            XML_WriteErrorLogs
��������  : XML_DecodeMain

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
XML_RESULT_ENUM_UINT32 xml_procinit(s8* map_path)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* ��ʼ��ȫ�ֱ��� */
    xml_initglobal();

    /* ��õ�ǰ�����product id*/   /*? UDP*/
    xml_getproductid();

    /*��ȡ��ǰ��ת��Ϣ*/
    xml_getjumpinfo(map_path);

    /* �����ڵ���Ϣ */
    returnval = xml_createanode();

    if (XML_RESULT_SUCCEED != returnval)
    {
        return returnval;
    }

    /* ������NV Item��ֵ�Ļ�����,+1Ϊ�����ַ����������� */  /*����̶��ռ�*/
    xml_ctrl.g_puclnvitem = (u8 *)nv_malloc(
                                         XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);
    if (NULL == xml_ctrl.g_puclnvitem)
    {
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* �����ȡ�ļ����ݵĻ�����,+1Ϊ�����ַ����������� */ /*�Ƿ����ռ�?*/
    xml_ctrl.g_pclfilereadbuff = (s8*)nv_malloc(
                                                XML_FILE_READ_BUFF_SIZE+1);
    if (NULL == xml_ctrl.g_pclfilereadbuff)
    {
        nv_free(xml_ctrl.g_puclnvitem);
        xml_write_error_log(__LINE__, 0, XML_RESULT_FALIED_MALLOC);
        return XML_RESULT_FALIED_MALLOC;
    }



    return XML_RESULT_SUCCEED;
}

/*****************************************************************************
�� �� ��  : XML_FreeMem
��������  : XML �ͷ��ڴ溯��
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  : ��
��������  : XML_DecodeMain

�޸���ʷ
1.��    ��   : 2011��04��14��
��    ��   : x51137
�޸�����   : �����ɺ���
*****************************************************************************/
void xml_freemem(void)
{
    u32 ulPropertyIndex = 0;

    for(ulPropertyIndex = 0; ulPropertyIndex < XML_NODE_PROPERTY_NUM; ulPropertyIndex++)
    {
        nv_free(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname);

        nv_free(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyvalue);
    }
    nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel);

    nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend);

    nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodevalue);

    nv_free(xml_ctrl.g_puclnvitem);

    nv_free(xml_ctrl.g_pclfilereadbuff);
}

void xml_decodefail_freemem(void)
{
    u32 ulPropertyIndex = 0;

    for(ulPropertyIndex = 0; ulPropertyIndex < XML_NODE_PROPERTY_NUM; ulPropertyIndex++)
    {
    	if(NULL != xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname)
    	{
    		nv_free(xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname);
    		xml_ctrl.g_stlxmlcurrentnode.stproperty[ulPropertyIndex].pcpropertyname = NULL;
    	}
    }

	if(NULL != xml_ctrl.g_stlxmlcurrentnode.pcnodelabel)
	{
    	nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodelabel);
		xml_ctrl.g_stlxmlcurrentnode.pcnodelabel = NULL;
	}

	if(NULL != xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend)
	{
		nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend);
		xml_ctrl.g_stlxmlcurrentnode.pcnodelabelend = NULL;
	}

	if(NULL != xml_ctrl.g_stlxmlcurrentnode.pcnodevalue)
	{
    	nv_free(xml_ctrl.g_stlxmlcurrentnode.pcnodevalue);
		xml_ctrl.g_stlxmlcurrentnode.pcnodevalue = NULL;
	}

	if(NULL != xml_ctrl.g_puclnvitem)
	{
    	nv_free(xml_ctrl.g_puclnvitem);
		xml_ctrl.g_puclnvitem = NULL;
	}

	if(NULL != xml_ctrl.g_pclfilereadbuff)
	{
    	nv_free(xml_ctrl.g_pclfilereadbuff);
		xml_ctrl.g_pclfilereadbuff = NULL;
	}

}

/*****************************************************************************
�� �� ��  : XML_DecodeMain
��������  : XML������������
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  : mdrv_file_open
            mdrv_file_close
            mdrv_file_remove
            DRV_SYSTEM_ERROR
            VOS_FlowReboot
            XML_ProcInit
            XML_InitGlobal
            XML_DecodeXMLFile
            XML_WriteErrorLog
��������  : VOS_Startup

�޸���ʷ
1.��    ��   : 2010��12��20��
��    ��   : ֣���� 176513
�޸�����   : �����ɺ���
*****************************************************************************/
u32 xml_decode_main(FILE* fp,s8* map_path,u32 card_type)
{
    XML_RESULT_ENUM_UINT32 returnval;

    /* ��ʱ����ģ��ȫ���������� */
    returnval = xml_procinit(map_path);
    xml_ctrl.card_type = card_type;

    if (XML_RESULT_SUCCEED != returnval)
    {
        printf("xml_procinit error! returnval = %d\n",returnval);
        goto out;
    }

    /* ����xnv.xml�ļ�  */
    returnval = xml_decode_xml_file(fp);

    if (XML_RESULT_SUCCEED != returnval)
    {
        printf(" xml_decode_xml_file: returnval = %d!\n",returnval);
        goto out;
    }
    /* �ͷ��ѷ�����ڴ� */
    xml_freemem();
    /*�������֮�󽫿������޸�Ϊ��1*/
    xml_ctrl.card_type = NV_USIMM_CARD_1;
    return NV_OK;
out:
    xml_help();
	xml_decodefail_freemem();
    return returnval;
}


/*****************************************************************************
* �� �� ��  : xml_nv_boot_search_byid
*
* ��������  : ����id Ϊitemid��NV�������Ϣ
*
* �������  : itemid: NV id
*           : pdata :
* �������  : ref_info  : NV��Ϣ
*           : file_info : NV���ڵ��ļ���Ϣ
*           : ref_offset: ref_info���ڵ��ڴ�
* �� �� ֵ  : void
*****************************************************************************/
u32 xml_nv_search_byid(u32 itemid,u8* pdata,struct nv_ref_data_info_stru* ref_info,struct nv_file_list_info_stru* file_info, u8** ref_offset)
{
    u32 low;
    u32 high;
    u32 mid;
    u32 offset;
    struct nv_ctrl_file_info_stru* ctrl_info = (struct nv_ctrl_file_info_stru*)pdata;

    high = ctrl_info->ref_count;
    low  = 1;

    while(low <= high)
    {
        mid = (low+high)/2;

        offset =NV_GLOBAL_CTRL_INFO_SIZE +NV_GLOBAL_FILE_ELEMENT_SIZE*ctrl_info->file_num + (mid -1)*NV_REF_LIST_ITEM_SIZE;
        memcpy((u8*)ref_info,(u8*)ctrl_info+offset,NV_REF_LIST_ITEM_SIZE);

        if(itemid < ref_info->itemid)
        {
            high = mid-1;
        }
        else if(itemid > ref_info->itemid)
        {
            low = mid+1;
        }
        else
        {
            *ref_offset = (u8*)ctrl_info + offset;
            offset = NV_GLOBAL_CTRL_INFO_SIZE + NV_GLOBAL_FILE_ELEMENT_SIZE*(ref_info->file_id -1);
            memcpy((u8*)file_info,(u8*)ctrl_info+offset,NV_GLOBAL_FILE_ELEMENT_SIZE);
            return NV_OK;
        }
    }
    return BSP_ERR_NV_NO_THIS_ID;

}
/*****************************************************************************
* �� �� ��  : xml_nv_boot_write_priority
*
* ��������  : ��priority���ȼ�д�뵽ref_offsetָ����ڴ���
*
* �������  : ref_offset:��д�����ȼ���nv��Ϣ��ָ��
*           : priority  :����������ȼ�
*
* �������  : ��
*
* �� �� ֵ  : void
*****************************************************************************/
void xml_nv_write_priority(u8* ref_offset , u16 priority)
{
    struct nv_ref_data_info_stru *ref_info = NULL;
    ref_info = (struct nv_ref_data_info_stru *)ref_offset;
    ref_info->priority = priority;
    return;
}
/*
 * copy user buff to global ddr,used to write nv data to ddr
 * &file_id :file id
 * &offset:  offset of global file ddr
 */
u32 xml_nv_write_to_mem(u8* pdata,u32 size,u32 file_id,u32 offset)
{
    struct nv_global_ddr_info_stru* ddr_info = (struct nv_global_ddr_info_stru*)NV_GLOBAL_INFO_ADDR;
    if(offset > ddr_info->file_info[file_id-1].size)
    {
        printf("[%s]:offset 0x%x\n",__FUNCTION__,offset);
        return BSP_ERR_NV_FILE_ERROR;
    }
    memcpy((u8*)(NV_GLOBAL_CTRL_INFO_ADDR+ddr_info->file_info[file_id-1].offset + offset),pdata,(s32)size);

    return NV_OK;
}


void xml_help(void)
{
	printf("xml_ctrl.g_stlxmlerrorinfo.ulxmlline  =  %d\n",xml_ctrl.g_stlxmlerrorinfo.ulxmlline);
	printf("xml_ctrl.g_stlxmlerrorinfo.ulstatus   =  %d\n",xml_ctrl.g_stlxmlerrorinfo.ulstatus);
	printf("xml_ctrl.g_stlxmlerrorinfo.ulcodeline =  %d\n",xml_ctrl.g_stlxmlerrorinfo.ulcodeline);
	printf("xml_ctrl.g_stlxmlerrorinfo.usnvid     =  %d\n",xml_ctrl.g_stlxmlerrorinfo.usnvid);
	printf("xml_ctrl.g_stlxmlerrorinfo.ulresult   =  %d\n",xml_ctrl.g_stlxmlerrorinfo.ulresult);
	printf("\n");
	printf("g_stlxmlstatus                        = %d\n",g_stlxmlstatus);
	printf("xml_ctrl.g_stlxml_lineno              = %d\n",xml_ctrl.g_stlxml_lineno);
	printf("acProductId                           = %d\n",xml_ctrl.g_stlxmlproductid);
    printf("xml_ctrl.g_stlxmlproductinfo.envalidnode   =  %d\n",xml_ctrl.g_stlxmlproductinfo.envalidnode);
}
/*lint -restore +e958*/

EXPORT_SYMBOL(xml_analyse);
EXPORT_SYMBOL(xml_help);
EXPORT_SYMBOL(xml_write_error_log);
EXPORT_SYMBOL(xml_procinit);










