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
#ifndef __MDM_APR_H__
#define __MDM_APR_H__

#include "osl_types.h"
#include "bsp_dump_def.h"

typedef struct module_info
{
    u32     moudle_sum;               /*�������*/
    struct
    {
    	u32 module;	                  /*�������*/
        char module_name[DUMP_MODULE_NAME_LEN];         /*�����������*/
    }module_info[1];
}module_info_t;

typedef struct modid_info
{
    u32     moudid_sum;             /*��Χ����*/
    struct
    {
    	u32  modid_start;		    /*���������λmodid��ʼֵ*/
    	u32  modid_end;		        /*���������λmodid����ֵ*/
    	char module[DUMP_MODULE_NAME_LEN];	        /*�������*/
    }modid_info[1];
}modid_info_t;

typedef struct task_table
{
    u32 task_sum;                /*��������*/
    struct
    {
    	char  task_name[16]; 	/*������*/
    	char  module[DUMP_MODULE_NAME_LEN]; 		/*�������*/
    }task_info[1];
}task_table_t;

typedef struct interupt_table
{
    u32 intrupt_sum;            /*�ж�����*/
    struct
    {
    	u32 interrpt_id; 		/*�жϺ�*/
    	char  module[DUMP_MODULE_NAME_LEN]; 		/*�������*/
    }interupt_info[1];
}interupt_table_t;

typedef struct
{
    u32 except_core;
    u32 except_reason;
    u32 voice;
    u32 modId;
    u32 reboot_context;
    u32 reboot_task;
    u32 reboot_int;
}dump_except_info_t;

typedef struct
{
    u8  brieftype[16];       /*module+voice*/
    u8  module_name[12];      /*���������*/
    u8  voice[4];            /*�Ƿ����������쳣, yes,no*/
    u8  task_name[16];       /*��λ������,���Ϊ�ж���Ϊ�жϺ�,�������Ϊ������Ϊ������*/
    u32 reboot_int;          /*��λ�жϺ�*/
    u32 modid;               /*��λmodid,system_error�ĵ�һ�����*/
    u8  reboot_core[8];      /*ȡֵAP CP*/
    u8  reboot_reson[16];    /*ȡֵNormal/DataAbort/Wdt*/
}dump_reset_log_t;
u32 bsp_apr_init(void);
void bsp_dump_parse_reset_info( dump_reset_log_t *dump_reset_info, dump_except_info_t dump_except_info);
void bsp_dump_get_reset_module(dump_except_info_t dump_except_info, u8* task_name,u8 * module);
void bsp_dump_get_reset_task(dump_except_info_t dump_except_info,  u8 * task_name, u32 * reboot_int);
u32 bsp_dump_search_taskid(dump_queue_t *Q);
void bsp_dump_get_reset_context_and_id(u32 *reboot_context, u32 *reboot_task,u32 *reboot_int, struct dump_global_struct_s* dump_head);
void bsp_dump_get_reset_voice(u32 voice, u8 * reboot_voice);
void bsp_dump_get_reset_voice(u32 voice, u8 * reboot_voice);
void bsp_dump_get_reset_reason(u32 reason, u8 * reboot_reason);
void bsp_dump_get_reset_ccore(u32 core, char *reboot_core);
void bsp_dump_get_reset_ccore(u32 core, char *reboot_core);
void om_get_reset_info(char * reset_info, u32 size);
void bsp_dump_get_reset_modid(u32 reason, u32 reboot_modid, u32 * modId);


#endif
