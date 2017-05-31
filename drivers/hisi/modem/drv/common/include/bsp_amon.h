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

#ifndef __BSP_AMON_H__
#define __BSP_AMON_H__

#ifdef __cplusplus
extern "C" {
#endif


#include "osl_common.h"

#ifdef ENABLE_BUILD_AMON
/* Monitor��ء��ɼ�ID�����Ŀ */
#define AXI_MAX_CONFIG_ID	8
#define AXI_MAX_PORT_CNT    8

#define AMON_SOC_MASK           0x1
#define AMON_CPUFAST_MASK       0x2
#define AMON_ENABLE_MASK        0x4
#define AMON_OPT_READ           0x1
#define AMON_OPT_WRITE          0x2

#ifdef BSP_CONFIG_PHONE_TYPE 
/*PORT����*/
#define AMON_PORT_MAX           (5)
#endif
typedef struct
{
    u32 hig_count;
    u32 low_count;
}count_stru;
typedef struct
{
    count_stru soc_read_count[AXI_MAX_CONFIG_ID];
    count_stru soc_write_count[AXI_MAX_CONFIG_ID];
    count_stru fast_read_count[AXI_MAX_CONFIG_ID];
    count_stru fast_write_count[AXI_MAX_CONFIG_ID];
	u64			global_access_count;
	u64			monitor_time_delta;
}amon_count_stru;
typedef struct
{
    u32 reset_flag;     /* ��λ��־��ƥ�䵽��������Ƿ�λ */
    u32 opt_type;       /* ������ͣ�01:����10:д��11:��д������ֵ:����� */
    u32 port;           /* ��ض˿� */
    u32 master_id;      /* ���masterid */
    u32 start_addr;     /* �����ʼ��ַ */
    u32 end_addr;       /* ��ؽ�����ַ */
} amon_config_t;

typedef struct
{
    u32             en_flag;                            /* ʹ�ܱ�־��00:ȥʹ�ܣ�01:SOC��10:CPUFAST��11:SOC,CPUFAST */    
    amon_config_t   soc_config[AXI_MAX_CONFIG_ID];      /* SOC���� */
    amon_config_t   cpufast_config[AXI_MAX_CONFIG_ID];  /* CPUFAST���� */
} amon_config_stru;
/* AXI����ѡ�� */
enum axi_config_enum
{
    AXI_CPUFAST_CONFIG,         /* CPUFAST���� */
    AXI_SOC_CONFIG,             /* SOC���� */
    AXI_CONFIG_BUTT
};
typedef unsigned int axi_config_enum_uint32;



s32 bsp_amon_init(void);
s32 amon_set_config(amon_config_stru configinfo);
s32 amon_start(axi_config_enum_uint32 config);
s32 amon_stop(axi_config_enum_uint32 config);
s32 amon_get_info(amon_count_stru *count);
#else
static s32 inline bsp_amon_init(void)
{
    return 0;
}

#endif


#ifdef __cplusplus
}
#endif


#endif

