/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef _NV_XML_DEC_H_
#define _NV_XML_DEC_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif
#pragma pack(push)
#pragma pack(4)

/*****************************************************************************
1 ����ͷ�ļ�����
*****************************************************************************/
/*lint -save -e537*/
#include "nv_comm.h"
#include "nv_ctrl.h"
#include "msp_nv_id.h"
/*lint -restore +e537*/


/*****************************************************************************
2 �궨��
*****************************************************************************/
#define  XML_FILE_READ_BUFF_SIZE              (0x1000)  /* ���ļ���������С         */
#define  XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL  (0X80)   /* �ڵ��ǩ��������С       */
#define  XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL  (0X8000) /* �ڵ�ֵ��������С         */
#define  XML_MAX_HARDWARE_LEN                 (0X20)    /* ����Product Id����󳤶� */

/*****************************************************************************
3 ö�ٶ���
*****************************************************************************/

/*****************************************************************************
ö����    : XML_RESULT_ENUM_UINT32
Э����  :
ASN.1���� :
ö��˵��  : XML����������״̬����ֵ
*****************************************************************************/
enum XML_RESULT_ENUM
{
    XML_RESULT_SUCCEED                        = 0 , /* �ɹ�                      */
    XML_RESULT_SUCCEED_IGNORE_CHAR                , /* ���Ժ��Ե��ַ�\r\n\t      */
    XML_RESULT_FALIED_PARA_POINTER                , /* ����Ĳ���ָ��            */
    XML_RESULT_FALIED_MALLOC                      , /* �ڴ�����ʧ��              */
    XML_RESULT_FALIED_BAD_SYNTAX                  , /* �����XML�﷨             */
    XML_RESULT_FALIED_BAD_CHAR                    , /* ������ַ�                */
    XML_RESULT_FALIED_READ_FILE                   , /* ��ȡ�ļ�ʧ��              */
    XML_RESULT_FALIED_WRITE_NV                    , /* дNV Value����            */
    XML_RESULT_FALIED_OUT_OF_BUFF_LEN             , /* ��������������            */
    XML_RESULT_FALIED_OUT_OF_MAX_VALUE            , /* ����NV ID�����ֵ         */
    XML_RESULT_FALIED_OUT_OF_0_9                  , /* NV IDֵ����0-9            */
    XML_RESULT_FALIED_OUT_OF_0_F                  , /* NV Valueֵ����0-F         */
    XML_RESULT_FALIED_OUT_OF_2_CHAR               , /* NV Valueֵ����1Byte       */
    XML_RESULT_FALIED_NV_ID_IS_NULL               , /* NV IDֵΪ��               */
    XML_RESULT_FALIED_NV_VALUE_IS_NULL            , /* NV ValueֵΪ��            */
    XML_RESULT_FALIED_PRODUCT_MATCH               , /* <product>������ǩû��ƥ�� */
    XML_RESULT_BUTT
};
typedef u32 XML_RESULT_ENUM_UINT32;

/*****************************************************************************
ö����    : XML_RESULT_ENUM_UINT32
Э����  :
ASN.1���� :
ö��˵��  : XML������״̬
*****************************************************************************/
enum XML_ANALYSE_STATUS_ENUM
{
    XML_ANASTT_ORIGINAL                       = 0 , /* ��ʼ                 */
    XML_ANASTT_ENTER_LABLE                        , /* �����ǩ             */
    XML_ANASTT_IGNORE                             , /* ���Ի�ע��           */
    XML_ANASTT_NODE_LABLE                         , /* ������ǩ��           */
    XML_ANASTT_SINGLE_ENDS_LABLE                  , /* ������β��ǩ         */
    XML_ANASTT_LABLE_END_MUST_RIGHT               , /* ��ǩ��ʼ����β       */
    XML_ANASTT_PROPERTY_START                     , /* ��ʼ��������         */
    XML_ANASTT_PROPERTY_NAME_START                , /* ��ʼ������������     */
    XML_ANASTT_PROPERTY_NAME_END                  , /* �������ƽ������ȴ�"  */
    XML_ANASTT_PROPERTY_VALUE_START               , /* "�������ȴ�="        */
    XML_ANASTT_PROPERTY_VALUE_END                 , /* ����ֵ�������ȴ�>    */
    XML_ANASTT_BUTT
};
typedef u32 XML_ANALYSE_STATUS_ENUM_UINT32;
typedef u32 (*XML_FUN)(s8 cnowchar);

/*****************************************************************************
ö����    : XML_PRODUCT_NODE_STATUS_ENUM_UINT32
Э����  :
ASN.1���� :
ö��˵��  : ���ڽ���xnv.xml�ļ�ʱ����¼product�ڵ��¸��ӽڵ�ڵ��Ƿ���Ч
*****************************************************************************/
enum XML_PRODUCT_STATUS_ENUM
{
    XML_PRODUCT_NODE_STATUS_INVALID           = 0 , /* Product�ڵ��Ӧ��ID����Ч�� */
    XML_PRODUCT_NODE_STATUS_VALID                 , /* Product�ڵ��Ӧ��ID����Ч�� */
    XML_PRODUCT_NODE_BUTT
};
typedef u32 XML_PRODUCT_STATUS_ENUM_UINT32;

/*****************************************************************************
ö����    : XML_DECODE_STATE_ENUM_UINT32
Э����  :
ASN.1���� :
ö��˵��  : ���ڽ���xnv.xml�ļ�ʱ����¼��ǰXML�ļ��Ƿ�������
*****************************************************************************/
enum XML_DECODE_STATUS_ENUM
{
    XML_DECODE_STATUS_DECODING                = 0 , /* ��ǰXML�ļ�������   */
    XML_DECODE_STATUS_FINISHED                    , /* ��ǰXML�ļ�������� */
    XML_DECODE_BUTT
};
typedef u32 XML_DECODE_STATE_ENUM_UINT32;

/*****************************************************************************
ö����    : XML_DECODE_JUMP_FLAG_ENUM
Э����  :
ASN.1���� :
ö��˵��  : ���ڽ���xnv.xml�ļ�ʱ����¼��ǰ�Ƿ���Ҫ��ת
*****************************************************************************/
enum XML_DECODE_JUMP_FLAG_ENUM
{
    XML_DECODE_STATUS_NOJUMP    = 0,              /* product_NvInfo�ڵ�������ת   */
    XML_DECODE_STATUS_JUMP ,                      /* product_NvInfo�ڵ���Ҫ��ת*/
    XML_DECODE_STATUS_2JUMP,                      /* product�ڵ���ת*/
    XML_DECODE_STATUS_JUMP_BUTT
};
typedef u32 XML_DECODE_JUMP_FLAG_ENUM;

/*****************************************************************************
4 UNION����
*****************************************************************************/

/*****************************************************************************
5 STRUCT����
*****************************************************************************/

/*****************************************************************************
�ṹ��    : XNV_MAP_PRODUCT_INFO
Э����  :
ASN.1���� :
�ṹ˵��  : XNV XMLӳ���ļ�product�ڵ���Ϣ
*****************************************************************************/
typedef struct
{
    u32 product_id;              /*product id*/
    u32 productCatOff;           /*product cat offset in the file*/
    u32 productIdOff;            /*product id  offset in the file*/
}XNV_MAP_PRODUCT_INFO;


/*****************************************************************************
�ṹ��    : XNV_MAP_HEAD_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : XNV XMLӳ���ļ�ͷ�ṹ
*****************************************************************************/
typedef struct
{
    u32 magic_num;               /*0x13579bde*/
    u32 product_num;             /*product ��Ŀ*/
    u8  md5[16];                 /*MD5У����*/
    XNV_MAP_PRODUCT_INFO product_info[0];
}XNV_MAP_HEAD_STRU;

/*****************************************************************************
�ṹ��    : XML_NODE_PROPERTY
Э����  :
ASN.1���� :
�ṹ˵��  : �ڵ���������ĵ�Ԫ
*****************************************************************************/
typedef struct
{
    u32 ulnamelength;                  /* pcPropertyName ����������  */
    u32 ulvaluelength;                 /* pcPropertyValue ���������� */
    s8* pcpropertyname;                 /* ��������                   */
    s8* pcpropertyvalue;                /* ����ֵ                     */
}XML_NODE_PROPERTY_STRU;

/*NV���Եĸ���*/

#define XML_NODE_PROPERTY_NUM   (2)
/*****************************************************************************
�ṹ��    : XML_NODE_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : XML���Ľڵ�
*****************************************************************************/
typedef struct
{
    u32 ullabellength;                 /* pcNodeLabel ����������    */
    u32 ullabelendlength;              /* pcNodeLabelEnd ���������� */
    u32 ulvaluelength;                 /* pcNodeValue ����������    */
    u32  ulPropertyIndex;               /*���Խڵ�����,��¼stproperty���±�ֵ*/
    s8*  pcnodelabel;                   /* �ڵ��ǩ                  */
    s8*  pcnodelabelend;                /* ��β������ǩ              */
    s8*  pcnodevalue;                   /* �ڵ�ֵ                    */
    XML_NODE_PROPERTY_STRU stproperty[XML_NODE_PROPERTY_NUM];        /* ����                      */
}XML_NODE_STRU;

/*****************************************************************************
�ṹ��    : XML_PRODUCT_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : ���ڼ�¼PRODUCT�ڵ���Ϣ
*****************************************************************************/
typedef struct
{
    /* ��¼product�ڵ��¸��ӽڵ�ڵ��Ƿ���Ч    */
    XML_PRODUCT_STATUS_ENUM_UINT32 envalidnode;
    /* �ж�XML�����Ƿ����                      */
    XML_DECODE_STATE_ENUM_UINT32   enxmldecodestate;
    /* ��Ч��Product�ڵ㼰����product�ڵ�ĸ��� */
    u32                     ulnodelevel;
    /* ��¼��ǰ�����product id                 */
    s8                       acproductid[XML_MAX_HARDWARE_LEN];
    /*�ж�XML�����Ƿ���Ҫ����product_NvInfo��ת*/
    XML_DECODE_JUMP_FLAG_ENUM      enxmldecodejump;
}XML_PRODUCT_STRU;

/*****************************************************************************
�ṹ��    : XML_ERROR_INFO_STRU
Э����  :
ASN.1���� :
�ṹ˵��  : ���ڼ�¼XML������Ϣ
*****************************************************************************/
typedef struct
{
    u32 ulxmlline;      /* XML��Ӧ���к�      */
    u32 ulstatus;       /* XML��Ӧ�Ľ���״̬  */
    u32 ulcodeline;     /* ��������Ӧ���к� */
    u16 usnvid;         /* NV ID��ֵ          */
    u16 usreserve;      /* NV ID��ֵ          */
    u32 ulresult;       /* ���صĽ��         */
} XML_ERROR_INFO_STRU;


typedef struct
{
    XML_NODE_STRU g_stlxmlcurrentnode;
    XML_PRODUCT_STRU g_stlxmlproductinfo;
    u8 *g_puclnvitem;
    s8  *g_pclfilereadbuff;
    u32 g_stlxml_lineno;
    s32 g_stlxmlproductid;
    XML_ERROR_INFO_STRU g_stlxmlerrorinfo;
    u32 card_type;
    /*����ӳ���ļ��ж��ܷ���ת*/
    XML_DECODE_JUMP_FLAG_ENUM g_stlxmljumpflag;
    /*ͨ��product id�����ļ���תλ��*/
    XNV_MAP_PRODUCT_INFO g_stlxmljumpinfo;
}XML_DOCODE_INFO;
/*****************************************************************************
6 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
7 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
8 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
9 OTHERS����
*****************************************************************************/


/*****************************************************************************
10 ��������
*****************************************************************************/

u32 xml_decode_main(FILE* fp,s8* map_path,u32 card_type);
void xml_help(void);
u32 xml_nv_search_byid(u32 itemid,u8* pdata,struct nv_ref_data_info_stru* ref_info,struct nv_file_list_info_stru* file_info, u8** ref_offset);
void xml_nv_write_priority(u8* ref_offset , u16 priority);
u32 xml_nv_write_to_mem(u8* pdata,u32 size,u32 file_id,u32 offset);
XML_RESULT_ENUM_UINT32 xml_analyse(s8 cnowchar);
void xml_write_error_log(u32 ulerrorline, u16 ulnvid, u32 ret);
XML_RESULT_ENUM_UINT32 xml_procinit(s8* map_path);



#pragma pack(pop)
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* _NV_XML_DEC_H_ */



