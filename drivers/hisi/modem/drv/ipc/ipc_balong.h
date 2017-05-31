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

#ifndef _IPC_BALONG_H_
#define _IPC_BALONG_H_
#include <bsp_ipc.h>
#include <osl_irq.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#ifdef __cplusplus
extern "C" {
#endif

#define BSP_IPC_CPU_RAW_INT(i)		(0x400 + (i * 0x10))
#define BSP_IPC_CPU_INT_MASK(i)		(0x404 + (i * 0x10))
#define BSP_IPC_CPU_INT_STAT(i)		(0x408 + (i * 0x10))
#define BSP_IPC_CPU_INT_CLR(i)		(0x40C + (i * 0x10))

#define BSP_IPC_SEM_RAW_INT(i)		(0x600 + (i * 0x10))
#define BSP_IPC_SEM_INT_MASK(i)		(0x604 + (i * 0x10))
#define BSP_IPC_SEM_INT_STAT(i)		(0x608 + (i * 0x10))
#define BSP_IPC_SEM_INT_CLR(i)		(0x60C + (i * 0x10))

#define BSP_IPC_HS_CTRL(i,j)		(0x800 + (i * 0x100) + (j * 0x8 ))
#define BSP_IPC_HS_STAT(i,j)		(0x804 + (i * 0x100) + (j * 0x8 ))



#ifndef SEM_FULL
#define SEM_FULL            (1)
#endif
#ifndef SEM_EMPTY
#define SEM_EMPTY           (0)
#endif

struct ipc_debug_s
{
	u32 u32RecvIntCore;										/*��ǰ�����ж�Ŀ���ID*/
	u32 u32IntHandleTimes[INTSRC_NUM];						/*��¼ĳ���жϽ��մ���*/
	u32 u32IntSendTimes[IPC_CORE_BUTTOM][INTSRC_NUM];		/*��¼��ÿ���˷���ÿ���жϵĴ���*/
	u32 u32SemId;											/*��ǰռ���ź���*/
	u32 u32SemTakeTimes[INTSRC_NUM];						/*ĳ�ź���ռ�óɹ�����*/
	u32 u32SemTakeFailTimes[INTSRC_NUM];					/*ĳ�ź���ռ��ʧ�ܴ���*/
	u32 u32SemGiveTimes[INTSRC_NUM];						/*ĳ�ź����ͷŴ���*/
	u32 u32IntTimeDelta[INTSRC_NUM];						/*��¼ÿ���ж϶�Ӧ����������ʱ��*/
	u32 u32SemCore;											/*��ȡ�ź�����ʱʱ��Ӧ�ĳ��к�*/
};
struct ipc_control{
    u32     core_num;										/*��¼IPCģ�鹤�����ڵĺ�ID*/
    void*   ipc_base;										/*ipc��ַ*/
    bool   sem_exist[INTSRC_NUM];							/*��¼�ź����Ƿ��Ѿ�����*/
    struct ipc_entry ipc_int_table[INTSRC_NUM];				/*��¼ÿһ���ж�Դע��Ļص�����*/
    osl_sem_id	 sem_ipc_task[INTSRC_NUM];
    spinlock_t lock;
	unsigned long last_int_cb_addr;  /* ���һ�����ص����жϺ����ĵ�ַ */
};
#ifdef __cplusplus
}
#endif

#endif /* end #define _IPC_BALONG_H_*/

