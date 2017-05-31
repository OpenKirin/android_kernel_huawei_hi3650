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

#ifndef __MDRV_NVIM_COMMON_H__
#define __MDRV_NVIM_COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <product_config.h>



/******************************** NV return value, need to be cleared *********************************/
#define NV_OK                           0
#define NV_ID_NOT_EXIST                 1
#define NV_BUFFER_TOO_LONG              2
#define NV_BUFFER_NOT_EXIST             4
#define NV_WRITE_SECURE_FAIL            18
#define NV_RESTORE_RUNNING              0x5A5A55AA


/******************************** NV�ָ������� *********************************/
enum NV_RESUME_ITEM
{
    NV_MANUFACTURE_ITEM = 0,
    NV_USER_ITEM,
    NV_SECURE_ITEM,
    NV_ITEM_BUTT
};
typedef unsigned long NV_RESUME_ITEM_ENUM_UINT32;

/*****************************************************************************
 *  �ṹ��    : NV_LIST_INFO_STRU
 *  Э����  :
 *  ASN.1���� :
 *  �ṹ˵��  : ��ȡNV�б���Ϣ
 ******************************************************************************/
typedef struct tag_NV_LIST_INFO_STRU
{
	unsigned short usNvId;                  /*NVIDֵ*/
	unsigned char  ucNvModemNum;            /*NV�Ƿ���ڶ��*/
	unsigned char  ucRsv;
}NV_LIST_INFO_STRU;  /*back*/


/* ����ͬModem NV������ */
unsigned int mdrv_nv_readex(unsigned int modemid, unsigned int itemid, void *pdata, unsigned int ulLength);

/* д��ͬModem NV������ */
unsigned int mdrv_nv_writeex(unsigned int modemid, unsigned int itemid,void *pdata, unsigned int ulLength);

/* ��NV������ */
unsigned int mdrv_nv_read_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength);

/* д����NV������ */
unsigned int mdrv_nv_write_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength);


/* ��ȡNV���� */
unsigned int mdrv_nv_get_length(unsigned int itemid, unsigned int *pulLength);

/* ��NV������ */
unsigned int mdrv_nv_read(unsigned int itemid, void *pdata, unsigned int ulLength);

/* дNV������ */
unsigned int mdrv_nv_write(unsigned int itemid, void *pdata, unsigned int ulLength);

/* ��NV������ */
unsigned int mdrv_nv_readpart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength);

/* д����NV������ */
unsigned int mdrv_nv_writepart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength);

#if defined (INSTANCE_1)
#define MDRV_MODEM_ID     MODEM_ID_1
#elif defined (INSTANCE_2)
#define MDRV_MODEM_ID     MODEM_ID_2
#else
#define MDRV_MODEM_ID     MODEM_ID_0
#endif

#define NV_GetLength(id, len)                        mdrv_nv_get_length(id, len)
#define NV_Read(id, item, len)                       mdrv_nv_readex(MDRV_MODEM_ID, id, item, len)
#define NV_Write(id, item, len)                      mdrv_nv_writeex(MDRV_MODEM_ID, id, item, len)
#define NV_ReadPart(id, off, item, len)              mdrv_nv_read_partex(MDRV_MODEM_ID, id, off, item, len)
#define NV_WritePart(id, off, item, len)             mdrv_nv_write_partex(MDRV_MODEM_ID, id, off, item, len)
#define NVM_Read(id, item, len)                      mdrv_nv_readex(MDRV_MODEM_ID, id, item, len)
#define NVM_Write(id, item, len)                     mdrv_nv_writeex(MDRV_MODEM_ID, id, item, len)
#define NV_ReadEx(modemid, id, item, len)	     mdrv_nv_readex(modemid, id, item, len)
#define NV_WriteEx(modemid, id, item, len) 	     mdrv_nv_writeex(modemid, id, item, len)
#define NV_ReadPartEx(modemid, id, off, item, len)   mdrv_nv_read_partex(modemid, id, off, item, len)
#define NV_WritePartEx(modemid, id, off, item, len)  mdrv_nv_write_partex(modemid, id, off, item, len)

#ifdef __cplusplus
}
#endif
#endif //__MDRV_NVIM_COMMON_H__
