

/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : ombufmngr.h
  �� �� ��   : ����
  ��    ��   : ����
  ��������   : 2012��07��31��
  ����޸�   :
  ��������   : BM(Buffer Manager)ģ��ͷ�ļ�
  �����б�   :

  �޸���ʷ      :
   1.��    ��   : 2012��07��31��
     ��    ��   : g47350
     �޸�����   : V900R001��Ŀ����ͷ�ļ�

******************************************************************************/

#ifndef __OMBUFMNGR_H__
#define __OMBUFMNGR_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
#define OM_RECORD_MAX_NUM  (100)


#define OM_ALLOC_RECORD(pData, lLen) \
    { \
        g_stOmBufRecord.astAllocItem[g_stOmBufRecord.ulAllocNum].pucData    = pData; \
        g_stOmBufRecord.astAllocItem[g_stOmBufRecord.ulAllocNum].lLen       = lLen; \
        g_stOmBufRecord.astAllocItem[g_stOmBufRecord.ulAllocNum].ulSlice    = VOS_GetSlice(); \
        \
        g_stOmBufRecord.ulAllocNum++; \
        /* �ﵽĩβ��Ҫ��ת*/ \
        if (OM_RECORD_MAX_NUM == g_stOmBufRecord.ulAllocNum) \
        { \
            g_stOmBufRecord.ulAllocNum = 0; \
        } \
    } \

#define OM_RLS_RECORD(pData, lLen) \
    { \
        g_stOmBufRecord.astRlsItem[g_stOmBufRecord.ulRlsNum].pucData    = pData; \
        g_stOmBufRecord.astRlsItem[g_stOmBufRecord.ulRlsNum].lLen       = lLen; \
        g_stOmBufRecord.astRlsItem[g_stOmBufRecord.ulRlsNum].ulSlice    = VOS_GetSlice(); \
        \
        g_stOmBufRecord.ulRlsNum++; \
        /* �ﵽĩβ��Ҫ��ת*/ \
        if (OM_RECORD_MAX_NUM == g_stOmBufRecord.ulRlsNum) \
        { \
            g_stOmBufRecord.ulRlsNum = 0; \
        } \
    } \

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : OM_BUF_CTRL_STRU
 �ṹ˵��  : ����OM���������������Ϣ
*****************************************************************************/
typedef struct
{
    VOS_INT32                           lAlloc;         /* ָ������ڴ��ƫ�Ƶ�ַ */
    VOS_INT32                           lRelease;       /* ָ���ͷ��ڴ��ƫ�Ƶ�ַ */
    VOS_INT32                           lPadding;       /* ��������ڴ�Ĵ�С */
    VOS_INT32                           lBufSize;       /* ���滺�����ܴ�С */
    VOS_UINT8                          *pucBuf;         /* ָ�򻺳��������׵�ַ */
    VOS_UINT8                          *pucRealBuf;     /* ָ�򻺳���ʵ�׵�ַ */
}OM_BUF_CTRL_STRU;


typedef struct
{
    VOS_UINT8                          *pucData;
    VOS_INT32                           lLen;
    VOS_UINT32                          ulSlice;
}OM_DATA_ITEM_STRU;

typedef struct
{
    VOS_UINT32                          ulSocpBug;
    VOS_UINT32                          ulAllocNum;
    VOS_UINT32                          ulRlsNum;
    OM_DATA_ITEM_STRU                   astAllocItem[OM_RECORD_MAX_NUM];
    OM_DATA_ITEM_STRU                   astRlsItem[OM_RECORD_MAX_NUM];
}OM_BUF_RECORD_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/
/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
extern OM_BUF_RECORD_STRU                      g_stOmBufRecord;

/*****************************************************************************
  10 ��������
*****************************************************************************/

extern VOS_UINT32 OM_GetSlice(VOS_VOID);

/*****************************************************************************
 �� �� ��  : OM_CreateTraceBuffer
 ��������  : ����OM������
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             lBufSize:   ���仺������С

 �������  : ��

 �� �� ֵ  : VOS_OK/VOS_ERR
*****************************************************************************/
VOS_UINT32 OM_CreateTraceBuffer(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lBufSize);

/*****************************************************************************
 �� �� ��  : OM_AllocTraceMem
 ��������  : �ӻ������з��������������ڴ�.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             lLen:       �����ڴ��С

 �������  : ��

 �� �� ֵ  : VOS_NULL_PTR ����ʧ��
             VOS_VOID*    �����ڴ��ָ��
*****************************************************************************/
VOS_VOID* OM_AllocTraceMem(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_INT32 lLen);

/*****************************************************************************
 �� �� ��  : OM_ReleaseTraceMem
 ��������  : �ͷŴӻ������з��������������ڴ�.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             pucAddr:    ָ���ͷ��ڴ��ָ��
             lLen:      �ͷŻ�������С

 �������  : ��

 �� �� ֵ  : VOS_OK/VOS_ERR
*****************************************************************************/
VOS_UINT32 OM_ReleaseTraceMem(OM_BUF_CTRL_STRU *pstBufCtrl,
                                        VOS_VOID *pAddr, VOS_INT32 lLen);

/*****************************************************************************
 �� �� ��  : OM_TraceMemFreeBytes
 ��������  : ��û�������ʹ���ڴ��С.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��

 �������  : ��

 �� �� ֵ  : VOS_INT32 ʹ���ڴ��С
*****************************************************************************/
VOS_INT32 OM_TraceMemNBytes(OM_BUF_CTRL_STRU *pstBufCtrl);

/*****************************************************************************
 �� �� ��  : OM_AddrVirtToReal
 ��������  : �����ַת��Ϊʵ��ַ.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             pucVirtAddr:��ת�����ַ

 �������  : ��

 �� �� ֵ  : VOS_NULL_PTR ת��ʧ��
             VOS_VOID*    ָ��ת����ʵ��ַ
*****************************************************************************/
VOS_VOID* OM_AddrVirtToReal(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_UINT8 *pucVirtAddr);

/*****************************************************************************
 �� �� ��  : OM_AddrRealToVirt
 ��������  : ��ʵ��ַת��Ϊ���ַ.
 �������  : pstBufCtrl: ָ�򻺳������ƿ�ָ��
             pucRealAddr:��ת��ʵ��ַ

 �������  : ��

 �� �� ֵ  : VOS_NULL_PTR ת��ʧ��
             VOS_VOID*    ָ��ת�������ַ
*****************************************************************************/
VOS_VOID* OM_AddrRealToVirt(OM_BUF_CTRL_STRU *pstBufCtrl, VOS_UINT8 *pucRealAddr);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

#endif
