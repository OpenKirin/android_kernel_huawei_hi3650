

/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��      : ombufmngr.c
  �� �� ��      : ����
  ��    ��      : ����
  ��������      : 2012��07��31��
  ����޸�      :
  ��������      : ��C�ļ�������BM(Buffer Manager)ģ���ʵ��
  �����б�      :

  �޸���ʷ      :
   1.��    ��   : 2012��07��31��
     ��    ��   : g47350
     �޸�����   : V900R001��Ŀ�����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�
*****************************************************************************/
#include "ombufmngr.h"



/*lint -e767 Log��ӡ */
#define    THIS_FILE_ID        PS_FILE_ID_OM_BUF_MMNGR_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
OM_BUF_RECORD_STRU                      g_stOmBufRecord;

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : OM_CreateTraceBuffer
 ��������  : ����OM������
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             lBufSize:   ���仺������С

 �������  : ��

 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��07��31��
    ��    ��   : g47350
    �޸�����   : V900R001��Ŀ��������

*****************************************************************************/
VOS_UINT32 OM_CreateTraceBuffer(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lBufSize)
{
    VOS_UINT_PTR ulRealAddr;

    /* ������� */
    if ((VOS_NULL_PTR == pstBufCtrl) || (0 == lBufSize))
    {
        return VOS_ERR;
    }

    pstBufCtrl->lAlloc   = 0;
    pstBufCtrl->lRelease = 0;
    pstBufCtrl->lPadding = 0;
    pstBufCtrl->lBufSize = lBufSize + 1;

    /*����uncache�Ķ�̬�ڴ���*/
    pstBufCtrl->pucBuf = (VOS_UINT8*)VOS_UnCacheMemAlloc((VOS_UINT32)pstBufCtrl->lBufSize, &ulRealAddr);

    /* �����ڴ�ʧ�� */
    if (VOS_NULL_PTR == pstBufCtrl->pucBuf)
    {
        return VOS_ERR;
    }

    /* ����bufʵ��ַ */
    pstBufCtrl->pucRealBuf = (VOS_UINT8 *)ulRealAddr;

    /*lint -e534*/
    vos_printf("\r\nOM_CreateTraceBuffer: real addr=0x%p, virt addr==0x%p\n", ulRealAddr, pstBufCtrl->pucBuf);

    VOS_MemSet_s(&g_stOmBufRecord, sizeof(g_stOmBufRecord), 0, sizeof(g_stOmBufRecord));
    /*lint +e534*/

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : OM_AllocTraceMem
 ��������  : �ӻ������з��������������ڴ�.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             lLen:      �����ڴ��С

 �������  : ��

 �� �� ֵ  : VOS_NULL_PTR ����ʧ��
             VOS_VOID*    �����ڴ��ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��07��31��
    ��    ��   : g47350
    �޸�����   : V900R001��Ŀ��������

*****************************************************************************/
VOS_VOID* OM_AllocTraceMem(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lLen)
{
    VOS_INT32                           lFreeSize;
    VOS_UINT8                          *pucAddr;
    VOS_INT32                           lTmpAlloc;
    VOS_INT32                           lTmpPadding;

    /* ���������� */
    if ((VOS_NULL_PTR == pstBufCtrl)
        || (lLen >= pstBufCtrl->lBufSize)
        || (0 == lLen))
    {
        OM_ALLOC_RECORD(VOS_NULL_PTR, lLen);

        return VOS_NULL_PTR;
    }

    lTmpAlloc       = pstBufCtrl->lAlloc;
    lTmpPadding     = pstBufCtrl->lPadding;

    /* û�з�ת */
    if (pstBufCtrl->lAlloc >= pstBufCtrl->lRelease)
    {
        /* ��ȡʣ���ڴ��С */
        if (0 == pstBufCtrl->lRelease)
        {
            lFreeSize = (pstBufCtrl->lBufSize - pstBufCtrl->lAlloc) - 1;
        }
        else
        {
            lFreeSize = pstBufCtrl->lBufSize - pstBufCtrl->lAlloc;
        }

        /* �����û������ڴ��С�򷵻� */
        if (lFreeSize >= lLen)
        {
            pucAddr = pstBufCtrl->pucBuf + pstBufCtrl->lAlloc;
            pstBufCtrl->lAlloc += lLen;

            OM_ALLOC_RECORD(pucAddr, lLen);

            return pucAddr;
        }

        lTmpPadding  = lFreeSize;
        lTmpAlloc    = 0;
    }

    /* ��ת����ȡʣ���ڴ��С */
    lFreeSize = (pstBufCtrl->lRelease - lTmpAlloc) - 1;

    if (lFreeSize >= lLen)
    {
        pucAddr = pstBufCtrl->pucBuf + lTmpAlloc;

        pstBufCtrl->lAlloc    = lTmpAlloc + lLen;
        pstBufCtrl->lPadding  = lTmpPadding;

        OM_ALLOC_RECORD(pucAddr, lLen);

        return pucAddr;
    }

    OM_ALLOC_RECORD(VOS_NULL_PTR, lLen);

    /* �������ʧ�ܣ����ؿ�ָ�� */
    return VOS_NULL_PTR;
}

/*****************************************************************************
 �� �� ��  : OM_ReleaseTraceMem
 ��������  : �ͷŴӻ������з��������������ڴ�.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             pAddr:      ָ���ͷ��ڴ��ָ��
             lLen:       �ͷŻ�������С

 �������  : ��

 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��07��31��
    ��    ��   : g47350
    �޸�����   : V900R001��Ŀ��������

*****************************************************************************/
VOS_UINT32 OM_ReleaseTraceMem(OM_BUF_CTRL_STRU *pstBufCtrl,
                                        VOS_VOID *pAddr, VOS_INT32 lLen)
{
    VOS_INT32                           lUsedSize;
    VOS_INT32                           lTmpRls;

    OM_RLS_RECORD(pAddr, lLen);

    /* ���������� */
    if ((VOS_NULL_PTR == pstBufCtrl) || (lLen >= pstBufCtrl->lBufSize))
    {
        return VOS_ERR;
    }

    /* �ͷ��ڴ��ַ���м�� */
    if ((pAddr != (pstBufCtrl->pucBuf + pstBufCtrl->lRelease))
        && (pAddr != pstBufCtrl->pucBuf))
    {
        g_stOmBufRecord.ulSocpBug++;
        /*return VOS_ERR;*/
    }

    /* δ��ת */
    if (pstBufCtrl->lAlloc >= pstBufCtrl->lRelease)
    {
        lUsedSize = pstBufCtrl->lAlloc - pstBufCtrl->lRelease;

        /* ���ȴ��� */
        if (lUsedSize < lLen)
        {
            return VOS_ERR;
        }

        pstBufCtrl->lRelease = (VOS_UINT8 *)pAddr + lLen - pstBufCtrl->pucBuf;

        return VOS_OK;
    }

    if (((VOS_UINT8 *)pAddr - pstBufCtrl->pucBuf + lLen) > pstBufCtrl->lBufSize)
    {
        lTmpRls = (((VOS_UINT8 *)pAddr - pstBufCtrl->pucBuf + lLen) + pstBufCtrl->lPadding) % pstBufCtrl->lBufSize;
    }
    else
    {
        lTmpRls = ((VOS_UINT8 *)pAddr - pstBufCtrl->pucBuf + lLen) % pstBufCtrl->lBufSize;
    }

    /* ����ulLen����ȷ */
    if ((lTmpRls > pstBufCtrl->lAlloc) && (lTmpRls < pstBufCtrl->lRelease))
    {
        return VOS_ERR;
    }

    /* ���������ת��Paddingֵ��0 */
    if (lTmpRls <= pstBufCtrl->lAlloc)
    {
        pstBufCtrl->lPadding = 0;
    }

    pstBufCtrl->lRelease = lTmpRls;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : OM_TraceMemNBytes
 ��������  : ��û�������ʹ���ڴ��С.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��

 �������  : ��

 �� �� ֵ  : VOS_INT32 ʹ���ڴ��С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��07��31��
    ��    ��   : g47350
    �޸�����   : V900R001��Ŀ��������

*****************************************************************************/
VOS_INT32 OM_TraceMemNBytes(OM_BUF_CTRL_STRU *pstBufCtrl)
{
    VOS_INT32 lUsedBytes;

    /* ���������� */
    if (VOS_NULL_PTR == pstBufCtrl)
    {
        return 0;
    }

    lUsedBytes = pstBufCtrl->lAlloc - pstBufCtrl->lRelease;

    /* ָ���з�ת */
    if (lUsedBytes < 0)
    {
        lUsedBytes += pstBufCtrl->lBufSize;
    }

    return lUsedBytes;
}

/*****************************************************************************
 �� �� ��  : OM_AddrVirtToReal
 ��������  : �����ַת��Ϊʵ��ַ.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             pucVirtAddr:��ת�����ַ

 �������  : ��

 �� �� ֵ  : VOS_NULL_PTR ת��ʧ��
             VOS_VOID*    ָ��ת����ʵ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��07��31��
    ��    ��   : g47350
    �޸�����   : V900R001��Ŀ��������

*****************************************************************************/
VOS_VOID* OM_AddrVirtToReal(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_UINT8 *pucVirtAddr)
{
    return (VOS_VOID *)VOS_UncacheMemVirtToPhy(pucVirtAddr, pstBufCtrl->pucRealBuf, pstBufCtrl->pucBuf, (VOS_UINT32)pstBufCtrl->lBufSize);
}

/*****************************************************************************
 �� �� ��  : OM_AddrRealToVirt
 ��������  : ��ʵ��ַת��Ϊ���ַ.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             pucRealAddr:��ת��ʵ��ַ

 �������  : ��

 �� �� ֵ  : VOS_NULL_PTR ת��ʧ��
             VOS_VOID*    ָ��ת�������ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��07��31��
    ��    ��   : g47350
    �޸�����   : V900R001��Ŀ��������

*****************************************************************************/
VOS_VOID* OM_AddrRealToVirt(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_UINT8 *pucRealAddr)
{
    return (VOS_VOID*)VOS_UncacheMemPhyToVirt(pucRealAddr, pstBufCtrl->pucRealBuf, pstBufCtrl->pucBuf, (VOS_UINT32)pstBufCtrl->lBufSize);
}

/*****************************************************************************
 �� �� ��  : OM_BufShow
 ��������  :
 �������  : VOS_VOID

 �������  : ��

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��07��31��
    ��    ��   : g47350
    �޸�����   : V900R001��Ŀ��������

*****************************************************************************/
VOS_VOID OM_BufShow(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    /*lint -e534*/
    vos_printf("\r\n OM ALLOC DATA SOCP Bug: %d.\r\n",g_stOmBufRecord.ulSocpBug);

    vos_printf("\r\n OM ALLOC DATA LIST: \r\n");
    /*lint +e534*/

    for (ulIndex = g_stOmBufRecord.ulAllocNum; ulIndex < OM_RECORD_MAX_NUM; ulIndex++)
    {
        /*lint -e534*/
        vos_printf("Slice: 0x%x, Addr: 0x%p, Len: 0x%x.\r\n ",
                    g_stOmBufRecord.astAllocItem[ulIndex].ulSlice,
                    g_stOmBufRecord.astAllocItem[ulIndex].pucData,
                    g_stOmBufRecord.astAllocItem[ulIndex].lLen);
        /*lint +e534*/
    }

    for (ulIndex = 0; ulIndex < g_stOmBufRecord.ulAllocNum; ulIndex++)
    {
        /*lint -e534*/
        vos_printf("Slice: 0x%x, Addr: 0x%p, Len: 0x%x.\r\n ",
                    g_stOmBufRecord.astAllocItem[ulIndex].ulSlice,
                    g_stOmBufRecord.astAllocItem[ulIndex].pucData,
                    g_stOmBufRecord.astAllocItem[ulIndex].lLen);
        /*lint +e534*/
    }

    /*lint -e534*/
    vos_printf("\r\n OM RELEASE DATA LIST: \r\n");
    /*lint +e534*/

    for (ulIndex = g_stOmBufRecord.ulRlsNum; ulIndex < OM_RECORD_MAX_NUM; ulIndex++)
    {
        /*lint -e534*/
        vos_printf("Slice: 0x%x, Addr: 0x%p, Len: 0x%x.\r\n ",
                    g_stOmBufRecord.astRlsItem[ulIndex].ulSlice,
                    g_stOmBufRecord.astRlsItem[ulIndex].pucData,
                    g_stOmBufRecord.astRlsItem[ulIndex].lLen);
        /*lint +e534*/
    }

    for (ulIndex = 0; ulIndex < g_stOmBufRecord.ulRlsNum; ulIndex++)
    {
        /*lint -e534*/
        vos_printf("Slice: 0x%x, Addr: 0x%p, Len: 0x%x.\r\n ",
                    g_stOmBufRecord.astRlsItem[ulIndex].ulSlice,
                    g_stOmBufRecord.astRlsItem[ulIndex].pucData,
                    g_stOmBufRecord.astRlsItem[ulIndex].lLen);
        /*lint +e534*/
    }

    return;
}


