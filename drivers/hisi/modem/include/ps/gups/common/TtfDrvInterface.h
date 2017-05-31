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

#ifndef __TTFDRVINTERFACE_H__
#define __TTFDRVINTERFACE_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TtfLinkInterface.h"

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
enum TTF_BLK_MEM_STATE_ENUM
{
    TTF_BLK_MEM_STATE_FREE,       /*���ڴ�δ����������ͷ�*/
    TTF_BLK_MEM_STATE_ALLOC,      /*���ڴ�������*/

    TTF_BLK_MEM_STATE_BUTT
};
typedef unsigned int TTF_BLK_MEM_STATE_ENUM_UINT32;

enum TTF_PS_DATA_PRIORITY_ENUM
{
    TTF_PS_DATA_PRIORITY_NORMAL = 0,
    TTF_PS_DATA_PRIORITY_MIDDLE,
    TTF_PS_DATA_PRIORITY_HIGH,
    TTF_PS_DATA_PRIORITY_BUTT,
};
typedef unsigned char TTF_PS_DATA_PRIORITY_ENUM_UINT8;

typedef struct
{
    TTF_BLK_MEM_STATE_ENUM_UINT32   enMemStateFlag;
    unsigned int                    ulAllocTick;        /* CPU tick when alloc or free */
    unsigned short                  usAllocFileId;      /* File ID when alloc or free */
    unsigned short                  usAllocLineNum;     /* File Line when alloc or free */
    unsigned short                  usTraceFileId;      /* File ID when traced */
    unsigned short                  usTraceLineNum;     /* File Line when traced */
    unsigned int                    ulTraceTick;        /* CPU tick when traced */
} TTF_BLK_MEM_DEBUG_ST;

typedef struct
{
    unsigned int    aulGroupCnt[4];    /* �� TTF_BLK_MEM_CNT Ƭ TTF_MEM �ڴ����Ϊ 4 ��,
                                        �ֱ��¼��ǰ�������� [0, TTF_BLK_MEM_CNT/4-1],
                                        [TTF_BLK_MEM_CNT/4, TTF_BLK_MEM_CNT/2-1],
                                        [TTF_BLK_MEM_CNT/2, 3*TTF_BLK_MEM_CNT/4-1],
                                        [3*TTF_BLK_MEM_CNT/4, TTF_BLK_MEM_CNT] ��Χ�Ĵ��� */
    unsigned int    ulMaxCnt;    /* ��¼ʹ�õ� TTF_MEM ��ֵ */
} TTF_BLK_MEM_CNT_ST;

typedef struct _TTF_MEM_ST
{
    TTF_NODE_ST                     stNode;
    unsigned char                   ucPoolId;       /*���ڴ�������һ���ڴ�� */
    unsigned char                   ucClusterId;    /*���ڴ���������һ������*/
    TTF_PS_DATA_PRIORITY_ENUM_UINT8 ucDataPriority;
    unsigned char                   ucReserve;
    struct _TTF_MEM_ST             *pNext;          /* �����ݵ���һ�� */
    unsigned short                  usType;         /* �ڴ����ͣ�DYN��BLK��EXT���� */
    unsigned short                  usLen;          /* �������ݵ��ܳ��ȣ�����һ��ȫ����ʹ�� */
    unsigned short                  usUsed;         /* �Ѿ�ʹ�õ����ݳ���   */
    unsigned short                  usApp;          /* ʹ���߿���ʹ�õ����� */

    TTF_BLK_MEM_DEBUG_ST           *pstDbgInfo;

    unsigned char                  *pOrigData;      /* ��¼���ݵ�ԭʼָ�� */
    unsigned char                  *pData;          /* ������ݵ�ָ�룬������ָ��ṹ��������ڴ� */
    void                           *pExtBuffAddr;   /* ����extern���͵��ڴ��ַ�����ͷ� */
    unsigned int                    ulForCds[1];    /*Ԥ����CDSʹ�ã�GUģ���ó�ʼ��*/

#if( FEATURE_LTE == FEATURE_ON )
    unsigned int                    ulForLte[6];    /*Ԥ����LTEʹ�ã�GUģ���ó�ʼ��*/
#endif
} TTF_MEM_ST;


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TtfDrvInterface.h */

