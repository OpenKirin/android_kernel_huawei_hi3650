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
#ifndef _BSP_SYSCTRL_H
#define _BSP_SYSCTRL_H

#include <product_config.h>
#include <bsp_om.h>

typedef enum tagBSP_SYSCTRL_INDEX
{
    sysctrl_ao = 0x0,
    sysctrl_pd,
    sysctrl_mdm,
    sysctrl_ap_peri, /*pctrl*/
    sysctrl_ap_pericrg,
    sysctrl_reservel,/*Ԥ��ϵͳ������*/
    sysctrl_reserve2,
    sysctrl_reserve3,
    sysctrl_reserve4,
    sysctrl_reserve5,

    sysctrl_max
}BSP_SYSCTRL_INDEX;

#define  sc_pr_debug(fmt, ...)    \
	(bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_SYSCTRL, "[sc]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  sc_pr_warn(fmt, ...)      \
	(bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_SYSCTRL, "[sc]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  sc_pr_info(fmt, ...)      \
	(bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_SYSCTRL, "[sc]:"fmt, ##__VA_ARGS__))
#define  sc_pr_err(fmt, ...)      \
	(bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SYSCTRL, "[sc]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#ifdef CONFIG_OF
extern void* bsp_sysctrl_addr_get(void* phy_addr);
extern void* bsp_sysctrl_addr_byindex(BSP_SYSCTRL_INDEX index);
extern void* bsp_sysctrl_addr_phy_byindex(BSP_SYSCTRL_INDEX index);
#else /* CONFIG_OF */
static inline void* bsp_sysctrl_addr_get(void* phy_addr){
	return 0;
}
static inline void* bsp_sysctrl_addr_byindex(BSP_SYSCTRL_INDEX index){
	return 0;
}
static inline void* bsp_sysctrl_addr_phy_byindex(BSP_SYSCTRL_INDEX index){
	return 0;
}
#endif

void system_status_init(void);

/*****************************************************************************
* �� �� ��  : get_system_status
* ��������  : �ж�оƬ��ǰ״̬
* �������  : ��
* �������  : ��
* �� �� ֵ  : 1:  ϵͳû�е�������·���������
*             0:  ��������
*            -1:  û�г�ʼ������оƬ��֧�ָù��ܡ���ħ��������������
*****************************************************************************/
int get_system_status(void);

#ifndef __KERNEL__
#ifdef CONFIG_OF
extern int dt_sysctrl_init(void);
#else /* CONFIG_OF */
static inline int dt_sysctrl_init(void) {};
#endif
#endif

#endif

