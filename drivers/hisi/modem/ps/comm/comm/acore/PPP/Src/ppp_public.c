/*
 *
 * All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses. You may choose this file to be licensed under the terms
 * of the GNU General Public License (GPL) Version 2 or the 2-clause
 * BSD license listed below:
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */



/******************************************************************************
   1 ͷ�ļ�����
******************************************************************************/
#include "PPP/Inc/ppp_public.h"
#include "PPP/Inc/hdlc_interface.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767  �����־�ļ���ID���� */
#define    THIS_FILE_ID                 PS_FILE_ID_PPP_PUBLIC_C
/*lint +e767   */


/******************************************************************************
   2 �ⲿ������������
******************************************************************************/



/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
extern PPP_DATA_Q_CTRL_ST               g_PppDataQCtrl;

VOS_UINT32                              g_ulPppDebugLevel = PS_PRINT_WARNING;
/******************************************************************************
   5 ����ʵ��
******************************************************************************/
/*****************************************************************************
 �� �� ��  : PPP_MemAlloc
 ��������  : �����㿽���ڴ�
 �������  : usLen      -- ���ݿ鳤��,��λΪ�ֽ�
 �������  : ��
 �� �� ֵ  : �㿽���ڴ�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
PPP_ZC_STRU * PPP_MemAlloc(VOS_UINT16 usLen, VOS_UINT16 usReserveLen)
{
    /* �ýӿ���������ʱ��Ҫ����MACͷ���ȣ�
      ������ADS�շ���ΪIP����Ϊ��NDIS��E5�������ݽṹͳһ����Ҫ����MACͷ��
      �㿽��ָ���C�˷��ص�ʱ��ͳһƫ�ƹ̶��ֽڣ��ҵ��㿽��ͷ����
    */
    /*
       ��������ʱ����������0��������USB�շ�����Ϊ�ֽ�����ʽ��PPP֡����MACͷ
    */
    PPP_ZC_STRU *pstMem = PPP_ZC_MEM_ALLOC(usLen + usReserveLen);


    if (VOS_NULL_PTR != pstMem)
    {
        if ( usReserveLen > 0)
        {
            /* �ճ��������ȣ���PPPģ��������ݳ�����usLen���������������δ��ֵǰ���� */
            PPP_ZC_RESERVE(pstMem, usReserveLen);

            /* �������������ܴ��� */
            g_PppDataQCtrl.stStat.ulMemAllocUplinkCnt++;

            /* ��������Э�̽׶��ͷŵ�������Դ */
            PPP_ZC_SET_DATA_APP(pstMem, (VOS_UINT16)(1 << 8) | (VOS_UINT16)PPP_PULL_PACKET_TYPE);
        }
        else
        {
            /* �������������ܴ��� */
            g_PppDataQCtrl.stStat.ulMemAllocDownlinkCnt++;

            /* ��������Э�̽׶��ͷŵ�������Դ */
            PPP_ZC_SET_DATA_APP(pstMem, (VOS_UINT16)(1 << 8) | (VOS_UINT16)PPP_PUSH_PACKET_TYPE);
        }
    }
    else
    {
        if ( usReserveLen > 0)
        {
            /* ������������ʧ�ܴ��� */
            g_PppDataQCtrl.stStat.ulMemAllocUplinkFailCnt++;
        }
        else
        {
            /* ������������ʧ�ܴ��� */
            g_PppDataQCtrl.stStat.ulMemAllocDownlinkFailCnt++;
        }
    }

    return pstMem;
}

/*****************************************************************************
 �� �� ��  : PPP_MemWriteData
 ��������  : ���㿽�����ݽṹд��һ�����ȵ�����
 �������  : pMemSrc  -- Ҫ��ȡ���ݵ�TTF�ڴ��ͷָ��
 �������  : ��
 �� �� ֵ  : ���ݳ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-12-14
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_VOID PPP_MemWriteData(PPP_ZC_STRU *pstMem, VOS_UINT8 *pucSrc, VOS_UINT16 usLen)
{
    /* ���úý�Ҫд���㿽���ڴ��������ݳ��� */
    PPP_ZC_SET_DATA_LEN(pstMem, usLen);

    /* �������ڴ����ݲ��� */
    PPP_MemSingleCopy(PPP_ZC_GET_DATA_PTR(pstMem), pucSrc, usLen);

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_MemCopyAllocForUlSdu
 ��������  : �����㿽���ڴ�飬���������Ѿ���д��ɵ���������
 �������  : pSrc  -- �Ѿ������д������ͷָ��
             usLen -- Ҫ���Ƶ����ݿ鳤��,��λΪ�ֽ�
 �������  : ��
 �� �� ֵ  : TTF�ڴ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
PPP_ZC_STRU * PPP_MemCopyAlloc(VOS_UINT8 *pSrc, VOS_UINT16 usLen, VOS_UINT16 usReserveLen)
{
    PPP_ZC_STRU                        *pstMem = VOS_NULL_PTR;


    pstMem = PPP_MemAlloc(usLen, usReserveLen);

    if ( VOS_NULL_PTR != pstMem )
    {
        /* �������ڴ����ݲ��� */
        PPP_MemWriteData(pstMem, pSrc, usLen);
    }

    return pstMem;
}

/*****************************************************************************
 �� �� ��  : PPP_MemCutTailData
 ��������  : ���㿽����β����ȥָ���ֽ���Ŀ������
 �������  : ppMemSrc   -- TTF MEM�ڴ�ṹ
             pucDest    -- ���ݿ���Ŀ�ĵص�ַ
             ulDataLen  -- �追������
 �������  : ��
 �� �� ֵ  : ��ȡ���ݳɹ�����PS_SUCC��ʧ�ܷ���PS_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 PPP_MemCutTailData
(
    PPP_ZC_STRU **ppMemSrc,
    VOS_UINT8 *pucDest,
    VOS_UINT16 usLen,
    VOS_UINT16 usReserveLen
)
{
    PPP_ZC_STRU                        *pCurrMem;
    VOS_UINT16                          usCurrLen;
    VOS_UINT16                          usCurrOffset;


    /* ������� */
    if ( (VOS_NULL_PTR == ppMemSrc) ||
         (VOS_NULL_PTR == *ppMemSrc) ||
         (VOS_NULL_PTR == pucDest))
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_MemCutTailData input parameters error, \
                      src addr'addr: 0X%p, dest addr: 0X%p\r\n",
                      (VOS_UINT_PTR)ppMemSrc, (VOS_UINT_PTR)pucDest);

        return PS_FAIL;
    }

    pCurrMem    = (PPP_ZC_STRU *)(*ppMemSrc);
    usCurrLen   = PPP_ZC_GET_DATA_LEN(pCurrMem);

    if ( ( 0 == usLen) || (usCurrLen < usLen) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_MemCutTailData, Warning, usCurrLen %d Less Than usLen %d!\r\n",
                      usCurrLen, usLen);

        return PS_FAIL;
    }

    /* ��β�������������ݣ�ֻ����һ���ڵ� */
    usCurrOffset = usCurrLen - usLen;

    mdrv_memcpy(pucDest, &(PPP_ZC_GET_DATA_PTR(pCurrMem)[usCurrOffset]), usLen);

    if ( usCurrOffset > 0 )
    {
        /* ����ʣ�����ݣ�Ŀǰû�����㳤�Ȳ���Tailָ��ǰ�ƵĽӿڣ��������� */
        (*ppMemSrc) = PPP_MemCopyAlloc(PPP_ZC_GET_DATA_PTR(pCurrMem), usCurrOffset, usReserveLen);
    }
    else
    {
        (*ppMemSrc) = VOS_NULL_PTR;
    }

    /* �ͷ��ڴ� */
    PPP_MemFree(pCurrMem);

    return PS_SUCC;
}

/*****************************************************************************
 �� �� ��  : PPP_MemCutHeadData
 ��������  : ���㿽���ڴ��ͷ������ָ���ֽ���Ŀ������
             �����¸��ֽ�λ�÷���
 �������  : ppMemSrc   -- TTF MEM�ڴ�ṹ
             pucDest    -- ���ݿ���Ŀ�ĵص�ַ
             ulDataLen  -- �追������
 �������  : ��
 �� �� ֵ  : ��ȡ���ݳɹ�����PS_SUCC��ʧ�ܷ���PS_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 PPP_MemCutHeadData
(
    PPP_ZC_STRU **ppMemSrc,
    VOS_UINT8 *pucDest,
    VOS_UINT16 usDataLen
)
{
    PPP_ZC_STRU                        *pCurrMem;
    VOS_UINT16                          usMemSrcLen;


    if ( (VOS_NULL_PTR == ppMemSrc) ||
         (VOS_NULL_PTR == *ppMemSrc) ||
         (VOS_NULL_PTR == pucDest) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                     "PPP_MemCutHeadData input parameters error, \
                     src addr'addr: 0x%p, dest addr: 0x%p\r\n",
                    (VOS_UINT_PTR)ppMemSrc, (VOS_UINT_PTR)pucDest);

        return PS_FAIL;
    }

    /* �ж�TTF�ڴ��ĳ����Ƿ����Ҫ�� */
    pCurrMem        = (PPP_ZC_STRU *)(*ppMemSrc);
    usMemSrcLen     = PPP_ZC_GET_DATA_LEN(pCurrMem);

    if ( ( 0 == usDataLen) || (usMemSrcLen < usDataLen) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, LOG_LEVEL_WARNING,
                      "PPP_MemCutHeadData, Warning: usMemSrcLen: %d Less Than usDataLen: %d!\r\n",
                      usMemSrcLen, usDataLen);

        return PS_FAIL;
    }

    /* ��ͷ�������������ݣ�ֻ����һ���ڵ� */
    mdrv_memcpy(pucDest, PPP_ZC_GET_DATA_PTR(pCurrMem), usDataLen);

    if ( usMemSrcLen >  usDataLen)
    {
        /* ����ʣ�����ݣ���������ָ��ͳ��� */
        PPP_ZC_REMOVE_HDR(pCurrMem, usDataLen);
    }
    else
    {
        /* �ͷ�ԭʼ�ڴ� */
        PPP_MemFree(pCurrMem);
        (*ppMemSrc) = VOS_NULL_PTR;
    }

    return PS_SUCC;
}

/*****************************************************************************
 �� �� ��  : PPP_MemGet
 ��������  : ��һTTF�ڴ���ȡһ�����ȵ����ݵ�ָ��Ŀ���ַ
 �������  : pMemSrc  -- Ҫ��ȡ���ݵ�TTF�ڴ��ͷָ��
             usOffset -- �ڴ������ƫ��
             pDest    -- ��Ż�ȡ���ݵ�Ŀ���ַ
             usLen    -- ��ȡ�����ݳ��ȣ���λΪ�ֽ�
 �������  : ��
 �� �� ֵ  : ��ȡ���ݳɹ�����PS_SUCC��ʧ�ܷ���PS_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_UINT32 PPP_MemGet(PPP_ZC_STRU *pMemSrc, VOS_UINT16 usOffset, VOS_UINT8 *pDest, VOS_UINT16 usLen)
{
    VOS_UINT16                          usMemSrcLen;


    /* ������� */
    if ( (VOS_NULL_PTR == pMemSrc)||(VOS_NULL_PTR == pDest) )
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "PPP_MemGet, Warning, Input Par pMemSrc Or pDest is Null!\r\n");

        return PS_FAIL;
    }

    if ( 0 == usLen )
    {
        PPP_MNTN_LOG(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                     "PPP_MemGet, Warning, Input Par usLen is 0!\r\n");

        return PS_FAIL;
    }

    /* �ж�TTF�ڴ��ĳ����Ƿ����Ҫ�� */
    usMemSrcLen = PPP_ZC_GET_DATA_LEN(pMemSrc);

    if ( usMemSrcLen < (usOffset + usLen) )
    {
        PPP_MNTN_LOG2(PS_PID_APP_PPP, 0, PS_PRINT_WARNING,
                      "PPP_MemGet, Warning, MemSrcLen %d Less Than (Offset + Len) %d!\r\n",
                      usMemSrcLen, (usOffset + usLen));

        return PS_FAIL;
    }

    mdrv_memcpy(pDest, PPP_ZC_GET_DATA_PTR(pMemSrc) + usOffset, usLen);

    return PS_SUCC;
}

/*****************************************************************************
 �� �� ��  : PPP_MemFreeWithData
 ��������  : �ͷ��㿽���ڴ�
 �������  : pstMem  --- TTF_MEM��ʽ������
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_VOID PPP_MemFree(PPP_ZC_STRU *pstMem)
{
    /* �ͷ��㿽���ڴ� */
    PPP_ZC_MEM_FREE(pstMem);

    g_PppDataQCtrl.stStat.ulMemFreeCnt++;

    return;
}

/*****************************************************************************
 �� �� ��  : PPP_MemSingleCopy
 ��������  : ��ȡ�����ڴ浥Ԫʵ��ʹ�õ����ֽ�������������������
 �������  : pMemSrc  -- Ҫ��ȡ���ݵ�TTF�ڴ��ͷָ��
 �������  : ��
 �� �� ֵ  : ���ݳ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011-03-09
    ��    ��   : l00164359
    �޸�����   : Created
*****************************************************************************/
VOS_VOID PPP_MemSingleCopy(VOS_UINT8 *pucDest, VOS_UINT8 *pucSrc, VOS_UINT32 ulLen)
{
    /* ���޸�ΪEDMA���� */
    mdrv_memcpy(pucDest, pucSrc, ulLen);

    return;
}

VOS_VOID     PPP_SetPrintLevel
(
    VOS_UINT32      ulLevel
)
{
    g_ulPppDebugLevel = ulLevel;
}

VOS_VOID     PPP_PrintLog
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString);
    }

    return;
}

VOS_VOID     PPP_PrintLog1
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString, lPara1);
    }

    return;
}
VOS_VOID     PPP_PrintLog2
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT_PTR     lPara1,
    VOS_INT_PTR     lPara2
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString, lPara1, lPara2);
    }

    return;
}

VOS_VOID     PPP_PrintLog3
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2,
    VOS_INT32       lPara3
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString, lPara1, lPara2, lPara3);
    }

    return;
}
VOS_VOID     PPP_PrintLog4
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2,
    VOS_INT32       lPara3,
    VOS_INT32       lPara4
)
{
    if ( g_ulPppDebugLevel >=  ulLevel)
    {
        vos_printf(pcString, lPara1, lPara2, lPara3, lPara4);
    }

    return;
}



