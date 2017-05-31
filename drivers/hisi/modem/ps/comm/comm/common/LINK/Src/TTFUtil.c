




/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "TTFUtil.h"
#include "PsTypeDef.h"
#include "TTFComm.h"
#include "mdrv.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_TTF_UTIL_C
/*lint +e767*/



/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
TTF_COPYLINK_DL_STRU                       g_stTtfCopyLinkDL;
TTF_COPYLINK_UL_STRU                       g_stTtfCopyLinkUL;


/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*lint -save -e958 */
/******************************************************************************
 Prototype      : TTF_QLink
 Description    : ��ʼ�����нڵ㣬��ʹ�øýڵ�֮ǰ��������øú�����ʼ��
 Input          : pItem -- �������нڵ������
                  pLink -- ���нڵ�
 Output         : NULL
 Return Value   : None
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-08-31
    Author      : g45205
    Modification: Created function
******************************************************************************/
VOS_VOID TTF_QLink(VOS_UINT32 ulPid, VOS_VOID *pItem, TTF_Q_LINK_ST *pLink)
{
    if (VOS_NULL_PTR == pLink)
    {
        return;
    }

    pLink->pNext  = VOS_NULL_PTR;
} /* TTF_QLink */


/******************************************************************************
 Prototype       : TTF_QInit
 Description     : ��ʼ������
 Input           : ulPid   -- ���ô˺�����ģ���Pid
                   pQ      -- ����ָ��
 Output          : None
 Return Value    : VOS_VOID
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
VOS_VOID TTF_QInit(VOS_UINT32 ulPid, TTF_Q_ST *pQ)
{
    if (VOS_NULL_PTR == pQ)
    {
        return;
    }

    pQ->stHdr.pHead     = (TTF_Q_LINK_ST *)(&pQ->stHdr);
    pQ->stHdr.pTail     = (TTF_Q_LINK_ST *)(&pQ->stHdr);
    pQ->ulCnt           = 0;

} /* TTF_QInit */


/******************************************************************************
 Prototype       : TTF_QIsEmpty
 Description     : �ж϶����Ƿ�Ϊ��
                   ע��:�����в�����ʱ���˺�������Ϊ�����ǿյ�
 Input           : ulPid   -- ���ô˺�����ģ���Pid
                   pQ      -- ����ָ��
 Output          : NONE
 Return Value    : VOS_YES -- ���п�
                   VOS_NO  -- ���зǿ�
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_QIsEmpty(VOS_UINT32 ulPid, TTF_Q_ST *pQ)
{
    if (VOS_NULL_PTR == pQ)
    {
        return VOS_YES;
    }

    if (0 == pQ->ulCnt)
    {
        return VOS_YES;
    }

    return VOS_NO;
} /*TTF_QIsEmpty*/


/******************************************************************************
 Prototype       : TTF_QCnt
 Description     : ������еĽڵ�����������
 Input           : ulPid   -- ���ô˺�����ģ���Pid
                   pQ      -- ����ָ��
 Output          : NONE
 Return Value    :  -- �����еĽڵ���
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_QCnt(VOS_UINT32 ulPid, TTF_Q_ST *pQ)
{
    if (VOS_NULL_PTR == pQ)
    {
        return 0;
    }

    return (pQ->ulCnt);
} /* TTF_QCnt */


/******************************************************************************
 Prototype       : TTF_QIn
 Description     : ���������
 Input           : ulPid   -- ���ô˺�����ģ���Pid
                   pQ      -- ����ָ��
                   pLink   -- ���нڵ�
 Output          : NONE
 Return Value    : VOS_OK  -- �ɹ�
                   VOS_ERR -- ʧ��
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
VOS_UINT32 TTF_QIn(VOS_UINT32 ulPid, TTF_Q_ST *pQ, TTF_Q_LINK_ST *pLink)
{

    if ( (VOS_NULL_PTR == pQ) || (VOS_NULL_PTR == pLink ))
    {
        return VOS_ERR;
    }

    pLink->pNext            = (TTF_Q_LINK_ST *)&pQ->stHdr;
    pQ->stHdr.pTail->pNext  = pLink;
    pQ->stHdr.pTail         = pLink;
    pQ->ulCnt++;

    return VOS_OK;
} /*TTF_QIn*/


/******************************************************************************
 Prototype       : TTF_QOut
 Description     : ���ݳ����У����س��ӵ����ݵ�ָ��
                   ע��˺�����TTF_QueuePeek()������
 Input           : ulPid  -- ���ô˺�����ģ���Pid
                   pQueue -- ����ָ��
 Output          : NONE
 Return Value    : �������ݵ�ָ��
 History         :
  1.Date         : 2006-08-31
    Author       : g45205
    Modification : Created function
******************************************************************************/
VOS_VOID *TTF_QOut(VOS_UINT32 ulPid, TTF_Q_ST *pQ)
{
    TTF_Q_LINK_ST  *pLink;
    TTF_Q_LINK_ST  *pRtn    = VOS_NULL_PTR;


    if (VOS_NULL_PTR == pQ)
    {
        return VOS_NULL_PTR;
    }

    pLink = pQ->stHdr.pHead;

    if ( pQ->ulCnt > 0 )
    {
        pQ->stHdr.pHead = pLink->pNext;

        if (pLink->pNext == (TTF_Q_LINK_ST *)pQ)
        {
            pQ->stHdr.pTail = (TTF_Q_LINK_ST *)(&pQ->stHdr);
        }

        pQ->ulCnt--;

        pLink->pNext = VOS_NULL_PTR;
        pRtn = pLink;
    }

    return (VOS_VOID *)pRtn;
} /* TTF_QOut */


/******************************************************************************
 Prototype      : TTF_MbufNew
 Description    : ����ָ�����ȵ��ڴ浥Ԫ�����ݸ���TTF_BLK_ST�ṹ֮��
 Input          : usLen  -- Ҫ������ڴ浥Ԫ�Ĵ�С���ֽ�Ϊ��λ
 Output         : NULL
 Return Value   : ������ڴ浥Ԫ�ĵ�ַ
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-08-31
    Author      : g45205
    Modification: Created function
******************************************************************************/
TTF_MBUF_ST *TTF_MbufNew(VOS_UINT32 ulPid, VOS_UINT16 usLen)
{
    TTF_MBUF_ST    *pMbuf;


    /*========================*/    /*�������*/
    if (0 == usLen)
    {
        return VOS_NULL_PTR;
    }

    /*========================*/    /*�����ڴ�*/
    pMbuf = (TTF_MBUF_ST *)VOS_MemAlloc(ulPid, DYNAMIC_MEM_PT,
        sizeof(TTF_MBUF_ST) + usLen);

    if (VOS_NULL_PTR == pMbuf)
    {
        return VOS_NULL_PTR;
    }


    /*========================*/    /*�����ڴ浥Ԫ�Ĳ���*/
    PSACORE_MEM_SET(pMbuf, sizeof(TTF_MBUF_ST) + usLen, 0, sizeof(TTF_MBUF_ST) + usLen);
    TTF_QLink(ulPid, (VOS_VOID *)pMbuf, &pMbuf->stLink);
    pMbuf->pNext    = VOS_NULL_PTR;
    pMbuf->usLen    = usLen;
    pMbuf->usUsed   = 0;
    pMbuf->pData    = (VOS_UINT8 *)(pMbuf + 1);

    return pMbuf;
} /*TTF_MbufNew*/


/******************************************************************************
 Prototype      : TTF_MbufFree
 Description    : �ͷ�ָ���ṹ���ڴ�
 Input          : pMbuf -- Ҫ�ͷŵ��ڴ浥Ԫ�ĵ�ַ
 Output         : pMbuf
 Return Value   : None
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-08-31
    Author      : g45205
    Modification: Created function
******************************************************************************/
void TTF_MbufFree(VOS_UINT32 ulPid, TTF_MBUF_ST *pMbuf)
{
    TTF_MBUF_ST    *pNext;
    TTF_MBUF_ST    *pFree   = pMbuf;


    while(VOS_NULL_PTR != pFree)
    {
        pNext = pFree->pNext;
        (VOS_VOID)VOS_MemFree(ulPid, pFree);
        pFree = pNext;
    }
} /*TTF_MbufFree*/


/******************************************************************************
 Prototype      : TTF_MbufGetLen
 Description    : ��ȡ�����ڴ浥Ԫ�����ֽ�������������������
 Input          : pMbuf -- Ҫ���㳤�ȵ��ڴ浥Ԫ
 Output         : �����ڴ浥Ԫ�ĳ���
 Return Value   : None
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2006-08-31
    Author      : g45205
    Modification: Created function
******************************************************************************/
VOS_UINT16 TTF_MbufGetLen(VOS_UINT32 ulPid, TTF_MBUF_ST *pMbuf)
{
    VOS_UINT16      usLen   = 0;
    TTF_MBUF_ST    *pTmp    = pMbuf;


    while(VOS_NULL_PTR != pTmp)
    {
        usLen   += pTmp->usUsed;
        pTmp    = pTmp->pNext;
    }

    return usLen;
} /*TTF_MbufGetLen*/


/******************************************************************************
 Function:       TTF_LenStr2IpAddr
 Description:    ���ַ�����ʽ��IP��ַת��ΪSMЭ��IP��ַ��ʽ.��ȫ�̳�V100R001
 Calls:
 Data Accessed:
 Data Updated:
 Input:          pucStr - �ַ�����ʽ��IP��ַ
 Output:         pucIpAddr - SMЭ�鶨���IP��ַ
 Return:         TAF_SUCCESS - ת���ɹ�
                 TAF_FAILURE - ת��ʧ��
 Others:
******************************************************************************/
VOS_UINT32  TTF_LenStr2IpAddr(VOS_UINT8* pucStr, VOS_UINT8 *pucIpAddr)
{
    VOS_UINT8 i, j = 0;
    VOS_UINT8 ucValue = 0;

    if (0 == pucStr[0])
    {   /*ADDR����Ϊ0��ֱ�ӳ��ȸ�ֵ����*/
        pucIpAddr[0] = 0;
        pucIpAddr[1] = 0;
        pucIpAddr[2] = 0;
        pucIpAddr[3] = 0;
        return PS_SUCC;
    }

    if (pucStr[0] == '.')
    {   /*�����1����Ч�ַ���'.'��IP��ַ�ǷǷ���*/
        return PS_FAIL;
    }


    for (i = 0; (i <= TTF_MAX_IPV4_ADDR_LEN) && (0 != pucStr[i]) ; i++)
    {   /*�ӵ�1����Ч�ַ���ʼ���*/
        if (((pucStr[i] < 0x30) || (pucStr[i] > 0x39)) && (pucStr[i] != '.'))
        {   /*����'0'-'9'���ַ��Ƿ�*/
            return PS_FAIL;
        }
        if (pucStr[i] != '.')
        {   /*�������Ч�ַ���ת��Ϊ����*/
            if (((ucValue * 10) + (pucStr[i] - 0x30)) <= 255)
            {   /*�ַ���ת��Ϊ��ЧIP��λֵ*/
                ucValue = (VOS_UINT8)((ucValue * 10) + (pucStr[i] - 0x30));
            }
            else
            {   /*����255����*/
                return PS_FAIL;
            }
        }
        else
        {   /*����ַ���'.'��ǰһλ��ֵ�Ѿ��������*/
            if (j <= 3)
            {   /*���汾ֻ֧��IPV4��ַ*/
                pucIpAddr[j] = ucValue;
                ucValue = 0;
                j++;  /*��ʼ��һ����Ч�ַ��εĳ����ۼ�*/
            }
            else
            {   /*����4��IPλ�Σ��Ƿ�*/
                return PS_FAIL;
            }
        }
    }

    if (j == 3)
    {
        pucIpAddr[j] = ucValue;
        return PS_SUCC;
    }
    else
    {
        return PS_FAIL;
    }
}

/*****************************************************************************
 Function   : TTF_Write32RegByBit
 Description: set value to register in position from startBit to endBit
 Input      : ulRegAddr -- address of SOC or BBP
            : ucStartBit -- startBit in 32bit,lower edge
            : ucEndBit  --- endBit in 32bit,upper edge
            : ulSetValue -- the value to set
 Return     : void
 Other      :
 *****************************************************************************/
VOS_VOID TTF_Write32RegByBit(VOS_UINT32 ulRegAddr, VOS_UINT8 ucStartBit, VOS_UINT8 ucEndBit,VOS_UINT32 ulSetValue)
{
    VOS_UINT32                          ulOrgValue;
    VOS_UINT32                          ulOrgMask;
    VOS_UINT32                          ulDataMask;


    /*check parameter*/

    if ( (VOS_NULL_PTR == ulRegAddr) || (ucStartBit > ucEndBit) || (ucStartBit > TTF_REG_MAX_BIT) || (ucEndBit > TTF_REG_MAX_BIT) )
    {
        (VOS_VOID)LogPrint4("TTF_Write32RegByBit para err ,regAddr 0x%x, startBit %d, endBit %d, value %d\r\n",
            (VOS_INT32)ulRegAddr, ucStartBit, ucEndBit, (VOS_INT32)ulSetValue);
        return;
    }

    /*read original value*/
    ulOrgValue = (VOS_UINT32)(*((VOS_UINT32 *)(VOS_UINT_PTR)(ulRegAddr)));

    /*to get the mask form startBit to endbit*/
    ulDataMask  = 0xFFFFFFFF;
    ulDataMask  = ulDataMask >> (ucStartBit);
    ulDataMask  = ulDataMask << (TTF_REG_MAX_BIT - (ucEndBit - ucStartBit));
    ulDataMask  = ulDataMask >> (TTF_REG_MAX_BIT - ucEndBit);
    ulOrgMask   = ~ulDataMask;

    /*set 0 from startBit to endBit*/
    ulOrgValue  &= ulOrgMask;

    /*move setValue to position*/
    ulSetValue  = ulSetValue << ucStartBit;
    ulSetValue &= ulDataMask;

    /*set value to reg*/
    ulSetValue |= ulOrgValue;

    *((VOS_UINT32 *)(VOS_UINT_PTR)(ulRegAddr)) = ulSetValue;
}/* TTF_Write32RegByBit */


/*****************************************************************************
 Function   : TTF_Read32RegByBit
 Description: read value from register in position from startBit to endBit
 Input      : ulRegAddr -- address of SOC or BBP
            : ucStartBit -- startBit in 32bit,lower edge
            : ucEndBit  --- endBit in 32bit,upper edge
 Return     : value
 Other      :
 *****************************************************************************/
VOS_UINT32 TTF_Read32RegByBit(VOS_UINT32 ulRegAddr, VOS_UINT8 ucStartBit, VOS_UINT8 ucEndBit)
{
    VOS_UINT32                          ulOrgValue;
    VOS_UINT32                          ulOrgMask;


    /*check parameter*/

    if ( (VOS_NULL_PTR == ulRegAddr) || (ucStartBit > ucEndBit) || (ucStartBit > TTF_REG_MAX_BIT) || (ucEndBit > TTF_REG_MAX_BIT) )
    {
        (VOS_VOID)LogPrint3("TTF_Read32RegByBit para err ,regAddr 0x%x, startBit %d, endBit %d\r\n",
            (VOS_INT32)ulRegAddr, ucStartBit, ucEndBit);
        return 0;
    }

    /*read original value*/
    ulOrgValue = (VOS_UINT32)(*((VOS_UINT32 *)(VOS_UINT_PTR)(ulRegAddr)));

    /*to get the mask form startBit to endbit*/
    ulOrgMask  = 0xFFFFFFFF;
    ulOrgMask  = ulOrgMask >> (ucStartBit);
    ulOrgMask  = ulOrgMask << (TTF_REG_MAX_BIT - (ucEndBit - ucStartBit));
    ulOrgMask  = ulOrgMask >> (TTF_REG_MAX_BIT - ucEndBit);

    /*get value from startBit to endBit*/
    ulOrgValue  &= ulOrgMask;

    return (ulOrgValue >> ucStartBit);
}/* TTF_Read32RegByBit */


/*****************************************************************************
 �� �� ��  : TTF_CopyLink_Init
 ��������  : ��ʼ������Pdu
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��11��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_CopyLink_DL_Init(TTF_COPYLINK_DL_STRU *pstTtfCpyLink)
{
    pstTtfCpyLink->ulCopyNodeCnt   = 0;

    return PS_SUCC;
}/* TTF_CopyLink_Init */


/*****************************************************************************
 �� �� ��  : TTF_CopyLink_Reg
 ��������  : ע����Ҫ�����Rlc Pdu
 �������  : VOS_UINT8 *pucRegDataDst ��Ҫ���������ݵ�Ŀ�ĵ�ַ
              VOS_UINT8 *pucRegDataSrc ��Ҫ���������ݵ�Դ��ַ
              VOS_UINT16 usRegDataLen  ��Ҫ��������ݳ���
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��11��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_CopyLink_DL_Reg
(
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucRegDataDst,
    VOS_UINT8                          *pucRegDataSrc,
    VOS_UINT16                          usRegDataLen,
    TTF_COPYLINK_DL_STRU               *pstTtfCpyLink
)
{
    TTF_COPYLINK_NODE_STRU             *pstCopyLinkNode;

    if (pstTtfCpyLink->ulCopyNodeCnt >= TTF_COPYLINK_DL_MAX_NUM)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
            "TTF, TTF_CopyLink_Excute, WARNING, NodeCnt <1>",
            (VOS_INT32)(pstTtfCpyLink->ulCopyNodeCnt));

        return PS_FAIL;
    }

    pstCopyLinkNode = &(pstTtfCpyLink->astCopyLinkNodes[pstTtfCpyLink->ulCopyNodeCnt]);

    pstCopyLinkNode->pucDstData  = pucRegDataDst;
    pstCopyLinkNode->pucSrcData  = pucRegDataSrc;
    pstCopyLinkNode->ulDataLen   = usRegDataLen;

    pstTtfCpyLink->ulCopyNodeCnt++;


    return PS_SUCC;
}/* TTF_CopyLink_Reg */


/*****************************************************************************
 �� �� ��  : TTF_CopyLink_Execute
 ��������  : ִ�б���RLC PDU����
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��11��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_CopyLink_DL_Execute(VOS_UINT32 ulPid, TTF_COPYLINK_DL_STRU *pstTtfCpyLink)
{
    VOS_UINT32                          ulCopyNodeLoop;
    TTF_COPYLINK_NODE_STRU             *pstCopyLinkNode;

    if (pstTtfCpyLink->ulCopyNodeCnt > TTF_COPYLINK_DL_MAX_NUM)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
            "TTF, TTF_CopyLink_Excute, WARNING, NodeCnt <1>",
            (VOS_INT32)(pstTtfCpyLink->ulCopyNodeCnt));

        pstTtfCpyLink->ulCopyNodeCnt = 0;
        return PS_FAIL;
    }

    for (ulCopyNodeLoop = 0;
        ulCopyNodeLoop < pstTtfCpyLink->ulCopyNodeCnt;
        ulCopyNodeLoop++)
    {
        pstCopyLinkNode = &(pstTtfCpyLink->astCopyLinkNodes[ulCopyNodeLoop]);

        (VOS_VOID)mdrv_memcpy(pstCopyLinkNode->pucDstData,
            pstCopyLinkNode->pucSrcData,
            pstCopyLinkNode->ulDataLen);
    }

    pstTtfCpyLink->ulCopyNodeCnt = 0;

    return PS_SUCC;
}/* TTF_CopyLink_Execute */


/*****************************************************************************
 �� �� ��  : TTF_CopyLink_Rel
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��24��
    ��    ��   : huangfei
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TTF_CopyLink_DL_Rel( TTF_COPYLINK_DL_STRU *pstTtfCpyLink )
{
    pstTtfCpyLink->ulCopyNodeCnt = 0;
} /* TTF_CopyLink_Rel */


/*****************************************************************************
 �� �� ��  : TTF_CopyLink_Init
 ��������  : ��ʼ������Pdu
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��11��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_CopyLink_UL_Init(TTF_COPYLINK_UL_STRU *pstTtfCpyLink)
{
    pstTtfCpyLink->ulCopyNodeCnt   = 0;

    return PS_SUCC;
}/* TTF_CopyLink_Init */


/*****************************************************************************
 �� �� ��  : TTF_CopyLink_Reg
 ��������  : ע����Ҫ�����Rlc Pdu
 �������  : VOS_UINT8 *pucRegDataDst ��Ҫ���������ݵ�Ŀ�ĵ�ַ
              VOS_UINT8 *pucRegDataSrc ��Ҫ���������ݵ�Դ��ַ
              VOS_UINT16 usRegDataLen  ��Ҫ��������ݳ���
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��11��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_CopyLink_UL_Reg
(
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucRegDataDst,
    VOS_UINT8                          *pucRegDataSrc,
    VOS_UINT16                          usRegDataLen,
    TTF_COPYLINK_UL_STRU               *pstTtfCpyLink
)
{
    TTF_COPYLINK_NODE_STRU             *pstCopyLinkNode;

    if (pstTtfCpyLink->ulCopyNodeCnt >= TTF_COPYLINK_UL_MAX_NUM)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
            "TTF, TTF_CopyLink_Excute, WARNING, NodeCnt <1>",
            (VOS_INT32)(pstTtfCpyLink->ulCopyNodeCnt));

        return PS_FAIL;
    }

    pstCopyLinkNode = &(pstTtfCpyLink->astCopyLinkNodes[pstTtfCpyLink->ulCopyNodeCnt]);

    pstCopyLinkNode->pucDstData  = pucRegDataDst;
    pstCopyLinkNode->pucSrcData  = pucRegDataSrc;
    pstCopyLinkNode->ulDataLen   = usRegDataLen;

    pstTtfCpyLink->ulCopyNodeCnt++;


    return PS_SUCC;
}/* TTF_CopyLink_Reg */


/*****************************************************************************
 �� �� ��  : TTF_CopyLink_Execute
 ��������  : ִ�б���RLC PDU����
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��11��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TTF_CopyLink_UL_Execute(VOS_UINT32 ulPid, TTF_COPYLINK_UL_STRU *pstTtfCpyLink)
{
    VOS_UINT32                          ulCopyNodeLoop;
    TTF_COPYLINK_NODE_STRU             *pstCopyLinkNode;

    if (pstTtfCpyLink->ulCopyNodeCnt > TTF_COPYLINK_UL_MAX_NUM)
    {
        TTF_LOG1(ulPid, 0, PS_PRINT_WARNING,
            "TTF, TTF_CopyLink_Excute, WARNING, NodeCnt <1>",
            (VOS_INT32)(pstTtfCpyLink->ulCopyNodeCnt));

        pstTtfCpyLink->ulCopyNodeCnt = 0;
        return PS_FAIL;
    }

    for (ulCopyNodeLoop = 0;
        ulCopyNodeLoop < pstTtfCpyLink->ulCopyNodeCnt;
        ulCopyNodeLoop++)
    {
        pstCopyLinkNode = &(pstTtfCpyLink->astCopyLinkNodes[ulCopyNodeLoop]);

        (VOS_VOID)mdrv_memcpy(pstCopyLinkNode->pucDstData,
            pstCopyLinkNode->pucSrcData,
            pstCopyLinkNode->ulDataLen);
    }

    pstTtfCpyLink->ulCopyNodeCnt = 0;

    return PS_SUCC;
}/* TTF_CopyLink_Execute */


/*****************************************************************************
 �� �� ��  : TTF_CopyLink_Rel
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��24��
    ��    ��   : huangfei
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TTF_CopyLink_UL_Rel( TTF_COPYLINK_UL_STRU *pstTtfCpyLink )
{
    pstTtfCpyLink->ulCopyNodeCnt = 0;
} /* TTF_CopyLink_Rel */



/*****************************************************************************
 �� �� ��  : TTF_InsertSortAsc16bit
 ��������  : ��Ԫ������ΪVOS_UINT16�����飬������������
 �������  :

 �������  :

 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��28��
    ��    ��   : Huangfei & Hefeng
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TTF_InsertSortAsc16bit
(
    VOS_UINT32                          ulPid,
    VOS_UINT16                          ausSortElement[],
    VOS_UINT32                          ulElementCnt,
    VOS_UINT32                          ulMaxCnt
)
{
    VOS_UINT16                          usTemp;
    VOS_UINT32                          ulElementCntLoop;
    VOS_INT32                           j;


    if ( 0 == ulElementCnt )
    {
        return;
    }

    if ( ulElementCnt > ulMaxCnt  )
    {
        TTF_LOG2(ulPid, 0, PS_PRINT_NORMAL,
            "TTF_InsertSortAsc16bit::ulElementCnt is more than MaxCnt!<1>ulElementCnt,<2>ulMaxCnt",
            (VOS_INT32)ulElementCnt, (VOS_INT32)ulMaxCnt);
        ulElementCnt    = ulMaxCnt;
    }

    for ( ulElementCntLoop = 1; ulElementCntLoop < ulElementCnt; ulElementCntLoop++ )
    {
        if( ausSortElement[ulElementCntLoop] < ausSortElement[ulElementCntLoop-1] )/* ��һ���� < ǰһ���� */
        {
            usTemp  = ausSortElement[ulElementCntLoop];
            j       = (VOS_INT32)(ulElementCntLoop - 1);

            do
            {
                ausSortElement[j+1]= ausSortElement[j];
                j--;
            }while ( (usTemp < ausSortElement[j]) && ( 0 <= j ) );

            ausSortElement[j+1]  = usTemp;
        }
    }

}



/*****************************************************************************
 �� �� ��  : TTF_RemoveDupElement16bit
 ��������  : ��Ԫ������ΪVOS_UINT16�����飬�Ƴ���ͬ,�����������������ģ��Ҵ���ԭʼ
              �����Сֵ
 �������  :

 �������  :

 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��28��
    ��    ��   : Huangfei & Hefeng
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TTF_RemoveDupElement16bit
(
    VOS_UINT32                          ulPid,
    VOS_UINT16                          ausSortElement[],
    VOS_UINT32                         *pulElementCnt,
    VOS_UINT32                          ulMaxCnt
)
{
    VOS_UINT32                          ulElementCntLoop;
    VOS_UINT32                          ulFilterAfterCnt;
    VOS_UINT32                          ulDupCnt = 0;
    VOS_UINT32                          j;


    if ( 0 == *pulElementCnt )
    {
        return;
    }

    if ( *pulElementCnt > ulMaxCnt  )
    {
        TTF_LOG2(ulPid, 0, PS_PRINT_NORMAL,
            "TTF_InsertSortAsc16bit::ulElementCnt is more than MaxCnt!<1>ulElementCnt,<2>ulMaxCnt",
            (VOS_INT32)(*pulElementCnt), (VOS_INT32)ulMaxCnt);
        *pulElementCnt  = ulMaxCnt;
    }

    ulFilterAfterCnt    = *pulElementCnt;

    for ( ulElementCntLoop = 1; ulElementCntLoop < ulFilterAfterCnt; ulElementCntLoop++ )
    {
        if ( ausSortElement[ulElementCntLoop] == ausSortElement[ulElementCntLoop-1] )
        {
            for ( j= ulElementCntLoop; j< ulFilterAfterCnt; j++ )
            {
                ausSortElement[j-1] = ausSortElement[j];
            }
            ulElementCntLoop--;
            ulFilterAfterCnt--;
            ulDupCnt++;
        }
    }

    *pulElementCnt  = *pulElementCnt - ulDupCnt;

    return;
}


/*****************************************************************************
 �� �� ��  : TTF_RingBufWrite
 ��������  : �����ݿ����Զ�Ӧ�Ļ���Buffer��
 �������  : VOS_UINT32 ulPid                  ��Ӧ��Pid
              VOS_UINT32 ulDstRingBufBaseAddr   ��Ӧ����Buffer����ʼ��ַ
              VOS_UINT16 usOffset               ����ʱ��ƫ�Ƶ�ַ
              VOS_UINT8 *pucSrcData             ����Դ���ݵ�ַ
              VOS_UINT16 usDataLen              �������ݵ�Ŀ��UPA����Ļ���ַ
              VOS_UINT16 usModLen               �������ݵ�Ŀ�������ģ

 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ      :
  1.��    ��   : 2010��9��7��
    ��    ��   : x59651
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TTF_RingBufWrite(VOS_UINT32 ulPid, VOS_UINT32 ulDstRingBufBaseAddr, VOS_UINT16 usOffset,
    VOS_UINT8 *pucSrcData, VOS_UINT16 usDataLen, VOS_UINT16 usModLen)
{
    VOS_UINT16  usBufLeftLen;
    VOS_UINT8  *pucDst;

    if (usDataLen >= usModLen)
    {
        TTF_LOG2(ulPid, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "TTF_RingBufWrite, ulDataLen <1> wrong with ulModLen <2>",
            usDataLen, usModLen);
        return;
    }

    if (usOffset >= usModLen)
    {
        TTF_LOG2(ulPid, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "TTF_RingBufWrite, usOffset <1> wrong with ulModLen <2>",
            usOffset, usModLen);
        return;
    }

    usBufLeftLen    = usModLen - usOffset;
    pucDst          = (VOS_UINT8 *)((VOS_UINT_PTR)(ulDstRingBufBaseAddr + usOffset));

    if (usBufLeftLen >= usDataLen)
    {
        (VOS_VOID)mdrv_memcpy(pucDst, pucSrcData, usDataLen);
    }
    else
    {
        (VOS_VOID)mdrv_memcpy(pucDst, pucSrcData, usBufLeftLen);
        (VOS_VOID)mdrv_memcpy((VOS_UINT8 *)(VOS_UINT_PTR)ulDstRingBufBaseAddr, (VOS_UINT8 *)(VOS_UINT_PTR)pucSrcData + usBufLeftLen,
            usDataLen - usBufLeftLen);
    }

    return;
} /* TTF_RingBufWrite */

/*****************************************************************************
 �� �� ��  : TTF_RingBufRead
 ��������  : �����ݴӶ�Ӧ�Ļ���Buffer�п�������
 �������  :  VOS_UINT32 ulPid                  ��Ӧ��Pid
              VOS_UINT32 ulSrcRingBufBaseAddr   ��ӦҪ�����Ļ���Buffer����ʼ��ַ
              VOS_UINT16 usOffset               ��ӦҪ����ʱ��ƫ�Ƶ�ַ
              VOS_UINT8 *pucDstData             ������Ŀ�����ݵ�ַ
              VOS_UINT16 usDataLen              Ҫ�������ݵĳ���
              VOS_UINT16 usModLen               �������ݵ�Դ�����ģ

 �������  : ��
 �� �� ֵ  : ��

 �޸���ʷ      :
  1.��    ��   : 2011��7��18��
    ��    ��   : w00165751
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TTF_RingBufRead
(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulSrcRingBufBaseAddr,
    VOS_UINT32                          usOffset,
    VOS_UINT8                          *pucDstData,
    VOS_UINT16                          usDataLen,
    VOS_UINT32                          usModLen
)
{
    VOS_UINT32                           usLeft;
    VOS_UINT8                           *pucSrc;

    if (usDataLen >= usModLen)
    {
        TTF_LOG(ulPid, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "TTF_RingBufRead, ulDataLen wrong with ulModLen ");
        return;
    }

    if (usOffset >= usModLen)
    {
        TTF_LOG(ulPid, PS_SUBMOD_NULL, PS_PRINT_WARNING,
            "TTF_RingBufRead, usOffset wrong with ulModLen ");

        return;
    }

    usLeft = usModLen - usOffset;
    pucSrc = (VOS_UINT8 *)(VOS_UINT_PTR)(ulSrcRingBufBaseAddr + usOffset);

    if (usDataLen > usLeft)
    {

        (VOS_VOID)mdrv_memcpy( pucDstData, pucSrc, usLeft);
        (VOS_VOID)mdrv_memcpy((VOS_UINT8 *)( pucDstData + usLeft),
                      (VOS_UINT8 *)(VOS_UINT_PTR)ulSrcRingBufBaseAddr,
                      (usDataLen - usLeft));
    }
    else
    {
        (VOS_VOID)mdrv_memcpy(pucDstData,pucSrc,usDataLen);
    }

    return;
} /* TTF_RingBufRead */

/*****************************************************************************
 �� �� ��  : PSACORE_MEM_SET_EX
 ��������  : ��װ��ȫ���� V_MemSet_s ,�����滻 PS_MEM_SET
 �������  : VOS_VOID * ToSet       Ŀ���׵�ַ
             VOS_SIZE_T ulDestSize  ��ʼ�����������ַ�����
             VOS_CHAR Char          ��ʼ�����ַ�
             VOS_SIZE_T Count       ��ʼ���ַ�����
             VOS_UINT32 ulFileNo    ��λ�ļ���
             VOS_UINT32 ulLineNo    ��λ�к�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��2��24��
    ��    ��   : L00349911
    �޸�����   : �����ɺ���

*****************************************************************************/
/*lint -e429*/
VOS_VOID PSACORE_MEM_SET_EX(VOS_VOID *ToSet, VOS_SIZE_T ulDestSize, VOS_CHAR Char, VOS_SIZE_T Count,
                                        VOS_UINT32 ulFileNo, VOS_UINT32 ulLineNo)
{
    VOS_VOID                            *pRslt  = VOS_NULL_PTR;

    pRslt = V_MemSet_s(ToSet, ulDestSize, Char, Count, ulFileNo, (VOS_INT32)ulLineNo);
    if (VOS_NULL_PTR == pRslt)
    {
        /* �ڴ��������λ */
        mdrv_om_system_error((VOS_INT32)TTF_MEM_SET_FAIL_ERROR, (VOS_INT32)ulFileNo, (VOS_INT32)ulLineNo, VOS_NULL_PTR, 0);
    }
}
/*lint +e429*/

/*****************************************************************************
 �� �� ��  : PSACORE_MEM_CPY_EX
 ��������  : ��װ��ȫ���� V_MemCpy_s ,�����滻 PS_MEM_CPY
 �������  : VOS_VOID *Dest         ����Ŀ���׵�ַ
             VOS_SIZE_T ulDestSize  �������������
             const VOS_VOID *Src    ����Դ��ַ
             VOS_SIZE_T Count       ��������
             VOS_UINT32 ulFileNo    ��λ�ļ���
             VOS_UINT32 ulLineNo    ��λ�к�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��2��24��
    ��    ��   : L00349911
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PSACORE_MEM_CPY_EX(VOS_VOID *Dest, VOS_SIZE_T ulDestSize, const VOS_VOID *Src, VOS_SIZE_T Count,
                                        VOS_UINT32 ulFileNo, VOS_UINT32 ulLineNo)
{
    VOS_VOID                            *pRslt          = VOS_NULL_PTR;
    const VOS_VOID                      *pDestChk       = Dest;
    const VOS_VOID                      *pSrcChk        = Src;

    /* ���Դ��ַΪ�գ����ҿ�������Ϊ0���򲻽�������Ĳ��� */
    if ( (VOS_NULL_PTR == Src) 
      && (0 == Count) )
    {    
        return;
    }

    /*  ���1: ���ڴ�ߵ�ַ��͵�ַ�����������Ǵ��б��ͷ����ʼ���������ֿ���������ġ����ԣ�������ֿ���ֱ��ʹ��MemMove����
               �������Լ������д��룬Ŀǰ�����д��������ڴ濽�������������������û�б�Ҫ��λ�����һһ�Ų鶼�ĳ�MemMove��
               ��������©��
        
        ���2: ���ڴ�ߵ�ַ��͵�ַ�����������Ǵ��б��β����ʼ���������ֿ����ǲ�����ģ��ᵼ���ڴ������쳣����ΪMemCpy����
               ������ʵ�ֶ��Ǵ��б�ͷ����ʼ�����ģ�����Ŀǰ�������������������֡�*/       
    if (( pSrcChk > pDestChk ) && ( (VOS_VOID *)((VOS_UINT8 *)pDestChk + Count) > pSrcChk ))
    {
        pRslt = V_MemMove_s( Dest, ulDestSize, Src, Count, ulFileNo, (VOS_INT32)ulLineNo );
        if (VOS_NULL_PTR == pRslt)
        {
            /* �ڴ��������λ */
            mdrv_om_system_error((VOS_INT32)TTF_MEM_MOVE_FAIL_ERROR, (VOS_INT32)ulFileNo, (VOS_INT32)ulLineNo, VOS_NULL_PTR, 0);
        }

        return;
    }    

    /*  ���3: ���ڴ�͵�ַ��ߵ�ַ�����������Ǵ��б��ͷ����ʼ���������ֿ����ǲ�����ģ��ᵼ���ڴ������쳣�������������
               ��ָ�룬ֱ�Ӹ�λ���壬��¶���д�������⡣

        ���4: ���ڴ�͵�ַ��ߵ�ַ�����������Ǵ��б��β����ʼ���������ֿ���������ģ����ᵼ�������쳣����ΪMemCpy����
               ������ʵ�ֶ��Ǵ��б�ͷ����ʼ�����ģ�����Ŀǰ�������������������֡�*/
    pRslt = V_MemCpy_s( Dest, ulDestSize, Src, Count, ulFileNo, (VOS_INT32)ulLineNo );
    if (VOS_NULL_PTR == pRslt)
    {
        /* �ڴ��������λ */
        mdrv_om_system_error((VOS_INT32)TTF_MEM_CPY_FAIL_ERROR, (VOS_INT32)ulFileNo, (VOS_INT32)ulLineNo, VOS_NULL_PTR, 0);
    }
}

/*****************************************************************************
 �� �� ��  : PSACORE_MEM_MOVE_EX
 ��������  : ��װ��ȫ���� V_MemMove_s ,�����滻 PS_MEM_MOVE
 �������  : VOS_VOID *Dest         ����Ŀ���׵�ַ
             VOS_SIZE_T ulDestSize  �������������
             const VOS_VOID *Src    ����Դ��ַ
             VOS_SIZE_T Count       ��������
             VOS_UINT32 ulFileNo    ��λ�ļ���
             VOS_UINT32 ulLineNo    ��λ�к�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2016��2��24��
    ��    ��   : L00349911
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID PSACORE_MEM_MOVE_EX(VOS_VOID *Dest, VOS_SIZE_T ulDestSize, const VOS_VOID *Src, VOS_SIZE_T Count,
                                        VOS_UINT32 ulFileNo, VOS_UINT32 ulLineNo)
{
    VOS_VOID                            *pRslt  = VOS_NULL_PTR;

    /* ���Դ��ַΪ�գ����ҿ�������Ϊ0���򲻽�������Ĳ��� */
    if ( (VOS_NULL_PTR == Src) 
      && (0 == Count) )
    {    
        return;
    }

    pRslt = V_MemMove_s( Dest, ulDestSize, Src, Count, ulFileNo, (VOS_INT32)ulLineNo );
    if (VOS_NULL_PTR == pRslt)
    {
        /* �ڴ��������λ */
        mdrv_om_system_error((VOS_INT32)TTF_MEM_MOVE_FAIL_ERROR, (VOS_INT32)ulFileNo, (VOS_INT32)ulLineNo, VOS_NULL_PTR, 0);
    }
}
/*lint -restore */



