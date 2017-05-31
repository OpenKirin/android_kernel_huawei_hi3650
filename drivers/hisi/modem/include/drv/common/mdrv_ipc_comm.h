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

#ifndef __MDRV_IPC_COMMON_H__
#define __MDRV_IPC_COMMON_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_public.h"
#include "mdrv_ipc_enum.h"

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_sem_create
 *  ��������  :  ����IPC�ź�����
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_sem_create (unsigned int u32SignalNum);

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_sem_delete
 *  ��������  :  ɾ��������IPC�ź�����
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_sem_delete(unsigned int u32SignalNum);


/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_int_enable
 *  ��������  :  ʹ��ĳ���жϡ�
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_int_enable (IPC_INT_LEV_E ulLvl);

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_int_enable
 *  ��������  :  ȥʹ��ĳ���жϡ�
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_int_disable (IPC_INT_LEV_E ulLvl);

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_int_connect
 *  ��������  :  ��ĳ���жϹҽӷ������
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_int_connect (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter);

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_int_disconnect
 *  ��������  :  ɾ��ĳ���жϹҽӵķ������
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_int_disconnect (IPC_INT_LEV_E ulLvl,VOIDFUNCPTR routine, unsigned int parameter);

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_int_send
 *  ��������  :  ��Ŀ��˷����жϡ�
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_int_send(IPC_INT_CORE_E enDstCore, IPC_INT_LEV_E ulLvl);

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_sem_take
 *  ��������  :  ��˯�߹��ܵĻ�ȡĳ���ź�����
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_sem_take (unsigned int u32SignalNum,int s32timeout);

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_sem_give
 *  ��������  :  �ͷ�take�����ź�����
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_sem_give(unsigned int u32SignalNum);

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_spin_lock
 *  ��������  :  ѭ���ȴ���ȡĳ�� ipc �ź�����
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  : void
 *
 ******************************************************************************/
void mdrv_ipc_spin_lock(unsigned int u32SignalNum);

/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_spin_trylock
 *  ��������  :  ���Ի�ȡĳ�� ipc �ź��������ȴ�
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  :  0	       �����ɹ���
 *                           ����	����ʧ�ܡ�
 *
 ******************************************************************************/
int mdrv_ipc_spin_trylock(unsigned int u32SignalNum);


/*****************************************************************************
 *  �� �� ��  : mdrv_ipc_spin_unlock
 *  ��������  :  �ͷ�ѭ���ȴ���ȡ�����ź�����
 *  �������  :
 *
 *  �������  : ��
 *  �� �� ֵ  : void
 *
 ******************************************************************************/
void mdrv_ipc_spin_unlock(unsigned int u32SignalNum);


#ifdef __cplusplus
}
#endif
#endif
