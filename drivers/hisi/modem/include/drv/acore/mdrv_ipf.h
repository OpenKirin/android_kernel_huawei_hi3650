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

#ifndef __MDRV_ACORE_IPF_H__
#define __MDRV_ACORE_IPF_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_ipf_comm.h"


typedef int (*BSP_IPF_WakeupDlCb)(void);
typedef int (*BSP_IPF_AdqEmptyDlCb)(IPF_ADQ_EMPTY_E eAdqEmpty);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_config_ulbd
*
* ��������  : ������������
*
* �������  : unsigned int u32Num     ��Ҫ���õ�BD��Ŀ
*             IPF_CONFIG_ULPARAM_S* pstUlPara ���ò����ṹ������ָ��
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_ERROR ����ʧ��
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_config_ulbd(unsigned int u32Num, IPF_CONFIG_ULPARAM_S* pstUlPara);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_ulbd_num
*
* ��������  : ��ȡ����BDQ�п��е�BD��
*
* �������  :
* �������  :
*
* �� �� ֵ  : ���е�BD��Ŀ����ΧΪ0~BD_DESC_SIZE
*
* ����˵��  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_ulbd_num(void);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_uldesc_num
*
* ��������  : ��ȡ���п������õİ���
*
* �������  : void
* �������  :
*
* �� �� ֵ  : ������ɶ�ͷ�����Ŀ��ϴ��İ���
*
* ����˵��  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_uldesc_num(void);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_ulrd_num
*
* ��������  : ��ȡ����RD��Ŀ
*
* �������  : void
* �������  :
*
* �� �� ֵ  : ����Rd��Ŀ
*
* ����˵��  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_ulrd_num (void);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_dlrd
*
* ��������  : ��ȡ����RD
*
* �������  : unsigned int* pu32Num  ���Է��ص�����RD��Ŀ
*             IPF_RD_DESC_S *pstRd  RD�������ṹ���׵�ַ
* �������  :
*
* �� �� ֵ  : ʵ�ʷ��ص�RD��Ŀ
*
* ����˵��  :
*
*****************************************************************************/
void mdrv_ipf_get_dlrd (unsigned int  * pu32Num, IPF_RD_DESC_S *pstRd);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_dlrd_num
*
* ��������  : ��ȡ����RD��Ŀ
*
* �������  : void
* �������  :
*
* �� �� ֵ  : ����Rd��Ŀ
*
* ����˵��  :
*
*****************************************************************************/
unsigned int mdrv_ipf_get_dlrd_num (void);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_config_dlad
*
* ��������  : �����е�AD�����µ��ڴ滺����
*
* �������  : IPF_AD_TYPE_E eAdType   AD���кţ�0���̰����У���1���������У�
*             unsigned int u32AdNum    ��Ҫ���õĵ�AD��Ŀ
*             IPF_AD_DESC_S *pstAdDesc ����ռ��Ӧ�����ݽṹ�׵�ַ
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
*
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_config_dlad(IPF_AD_TYPE_E eAdType, unsigned int u32AdNum, IPF_AD_DESC_S * pstAdDesc);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_dlad_num
*
* ��������  : ��ȡ���У�A�ˣ����У�ָ��Ļ������Ѿ���ʹ�ã�AD��Ŀ
*
* �������  : unsigned int* pu32AD0Num  ���ؿ��е�AD0����Ŀ
*             unsigned int* pu32AD1Num  ���ؿ��е�AD1����Ŀ
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS ���óɹ�
*             IPF_INVALID_PARA ���������Ч
* ����˵��  :
*
*****************************************************************************/
int mdrv_ipf_get_dlad_num (unsigned int* pu32AD0Num, unsigned int* pu32AD1Num);


/*****************************************************************************
* �� �� ��  : mdrv_ipf_reinit_dlreg
*
* ��������  : CCore������λ�ָ�ʱ������IPF�Ĵ���
*
* �������  : void
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
void mdrv_ipf_reinit_dlreg(void);

/*****************************************************************************
* �� �� ��  : mdrv_ipf_get_used_dlad
*
* ��������  : ��ȡδ��ʹ�õ�����AD�Ա�ADS�ͷ�
*
* �������  : IPF_AD_TYPE_E eAdType  AD���ͣ�0���̰����У���1���������У�
*             unsigned int * pu32AdNum    AD��Ŀ
*             IPF_AD_DESC_S * pstAdDesc ��Ҫ�ͷŵ�AD�����׵�ַ
* �������  :
*
* �� �� ֵ  : IPF_SUCCESS����������
*             IPF_ERROR��ʧ�ܷ��أ��ȴ���ʱIPFͨ��ʼ��BUSY
*             IPF_INVALID_PARA����γ���
* ����˵��  : ADS��ccore������λ��������Ҫ���øú������ͷŷ��ص�AD�����������ڴ�й¶
*
*****************************************************************************/
int mdrv_ipf_get_used_dlad(IPF_AD_TYPE_E eAdType, unsigned int * pu32AdNum, IPF_AD_DESC_S * pstAdDesc);

#ifdef __cplusplus
}
#endif

#endif
