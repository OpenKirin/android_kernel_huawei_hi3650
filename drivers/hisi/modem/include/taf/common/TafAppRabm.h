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

#ifndef __TAF_APP_RABM_H__
#define __TAF_APP_RABM_H__


#include "TafTypeDef.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#pragma pack(4)

/*�����ӿں궨��*/
#define TAF_DATA_CS_DOMAIN                   0    /*CS��*/
#define TAF_DATA_PS_DOMAIN                   1    /*PS��*/

#define TAF_RABM_STOP_DATA                   0    /*ָʾAPPֹͣ��������*/
#define TAF_RABM_START_DATA                  1    /*ָʾAPP��ʼ��������*/
#define TAF_DATA_STOP                        2    /*�޷�������������ֹͣ����*/
#define TAF_DATA_START                       3    /*��������(δ��)*/

/*ָʾAPPֹͣ�������ݵ�ԭ��ֵ*/
#define TAF_RABM_STOP_CAUSE_NORMAL                        0xff      /*ֹͣ����*/

/*ָʾAPP��ʼ�������ݵ�ԭ��ֵ*/
#define TAF_RABM_START_CAUSE_REEST_FAILURE                0         /*���ؽ�RABʧ�ܿ�ʼ��������*/
#define TAF_RABM_START_CAUSE_REEST_SUCCESS                1         /*���ؽ�RAB�ɹ���ʼ��������*/
#define TAF_RABM_START_CAUSE_RRC_INDICATION               2         /*��RRCָʾ��ʼ��������*/
#define TAF_RABM_START_CAUSE_2G_TO_3G_CUR_2G              3         /*2Gģʽ����3Gģʽ����ǰ����Ϊ2G(V200R001�汾����)*/
#define TAF_RABM_START_CAUSE_2G_TO_3G_CUR_3G              4         /*2Gģʽ����3Gģʽ����ǰ����Ϊ3G(V200R001�汾����)*/
#define TAR_RABM_START_CAUSE_3G_TO_2G_CUR_3G              5         /*3Gģʽ����2Gģʽ����ǰ����Ϊ3G(V200R001�汾����)*/
#define TAF_RABM_START_CAUSE_3G_TO_2G_RA_UPDATE_FINISH    6         /*3G��2G�л��е�·�����������̽���(V200R001�汾����)*/

/*�޷�����������ԭ��ֵ*/
#define TAF_DATA_CAUSE_REEST_FAILURE         0    /*�û�������ؽ�ʧ��*/
#define TAF_DATA_CAUSE_REEST_SUCCESS         1    /*�û�������ؽ��ɹ�*/
#define TAF_DATA_CAUSE_LOWLAYER_INDICATION   2    /*�û���ײ�ԭ��*/
#define TAF_DATA_CAUSE_NO_TRANSMODE          3    /*��ʱ��NSAPIδ����TRANSMODE(V200R001�汾����)*/
#define TAF_DATA_CAUSE_3G_TO_2G_RA_UPDATE    4    /*���ڽ���3G��2G�л��е�·��������(V200R001�汾����)*/

/*�����궨��:*/
#define   TAF_RABM_MAX_ENT_NUM               11





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

#endif /* end of TafAppRabm.h */
