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


/*lint -save -e537*/
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/thread_info.h>
#include <linux/syslog.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/notifier.h>
#include <linux/kdebug.h>
#include <linux/reboot.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/delay.h>
#include <linux/wakelock.h>
#include <asm/string.h>
#include <asm/traps.h>
#include "product_config.h"
#include <linux/syscalls.h>
#include "osl_types.h"
#include "osl_io.h"
#include "osl_bio.h"
#include "osl_malloc.h"
#include "bsp_dump.h"
#include "bsp_ipc.h"
#include "bsp_memmap.h"
#include "bsp_wdt.h"
#include "bsp_icc.h"
#include "bsp_onoff.h"
#include "bsp_nvim.h"
#include "bsp_softtimer.h"
#include "bsp_version.h"
#include "bsp_sram.h"
#include "bsp_dump_mem.h"
#include "bsp_coresight.h"
#include "bsp_reset.h"
#include "drv_nv_def.h"
#include "mdrv_om.h"
#include <gunas_errno.h>
#include "modem_dump.h"
#include "modem_dump_base.h"
#include "modem_dump_apr.h"
#include "bsp_dump.h"
#include "bsp_dump_def.h"
#include "bsp_dump_drv.h"
#include "modem_dump_area.h"
#include "bsp_dump_mem.h"



/*lint -restore*/
 /*�洢cp�ж���Ϣ �жϺ� �������*/
interupt_table_t *g_cp_interupt_table = NULL;

/*�洢cp���� ���������Ϣ*/
task_table_t *g_cp_task_table = NULL;
/*�洢modid��Χ ���������Ϣ*/
modid_info_t *g_p_modid_table = NULL;

/*****************************************************************************
* �� �� ��  : bsp_dump_parse_apr_dts_info
*
* ��������  : ��ȡdts��ʼ��������Ϣ���ж���Ϣ �����Ϣ
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
u32 bsp_apr_init(void)
{
    struct device_node *dev_node = NULL;
    struct device_node *child = NULL;
    struct property *prop = NULL;
    const __be32 *p = NULL;
    char * module_name = NULL;
    u32 sum = 0;
    u32 alloc_size = 0;
    u32 index = 0;
    u32 module_index = 0;
    void * temp = NULL;
    u32 modid_sum = 0;
    u32 task_sum = 0;
    u32 int_sum = 0;
    u32 u = 0;
    u32 i = 0;
    /*��ȡ���������Ϣ*/
    dev_node = of_find_compatible_node(NULL,NULL,"hisilicon,apr_config");
    if(!dev_node)
    {
        dump_fetal("get apr_config node failed!\n");
        return MDRV_ERROR;
    }

    for_each_child_of_node(dev_node,child)
    {
        if(of_property_read_u32(child, "modid_sum", &sum))
        {
            sum = 0;
            dump_fetal("get modid_sum failed!\n");
        }
        modid_sum+=sum;
        if(of_property_read_u32(child, "task_sum", &sum))
        {
            sum = 0;
            dump_fetal("get task_sum failed!\n");
        }
        task_sum+=sum;
        if(of_property_read_u32(child, "int_sum", &sum))
        {
            sum = 0;
            dump_fetal("get int_sum failed!\n");
        }
        int_sum+=sum;
    }

    alloc_size = modid_sum*(sizeof(modid_info_t) - sizeof(u32)) + sizeof(u32);
    g_p_modid_table = osl_malloc(alloc_size);
    if(NULL == g_p_modid_table)
    {
        dump_fetal("p_module_info malloc fail, size:0x%x\n", alloc_size);
    }
    memset(g_p_modid_table, 0, alloc_size);
    alloc_size = int_sum*(sizeof(interupt_table_t) - sizeof(u32)) + sizeof(u32);
    g_cp_interupt_table = (interupt_table_t *)osl_malloc(alloc_size);
    if(NULL == g_cp_interupt_table)
    {
        dump_fetal("g_cp_interupt_table malloc fail, size:0x%x\n", alloc_size);
    }
    memset(g_cp_interupt_table, 0, alloc_size);

    alloc_size = task_sum*(sizeof(task_table_t) - sizeof(u32)) + sizeof(u32);
    g_cp_task_table = (task_table_t *)osl_malloc(alloc_size);
    if(NULL == g_cp_task_table)
    {
        dump_fetal("g_cp_task_table malloc fail, size:0x%x\n", alloc_size);
    }
    memset(g_cp_task_table, 0, alloc_size);

    child = NULL;
    for_each_child_of_node(dev_node,child)
    {
        /*������ζ�ȡ�������ʧ�����ٶ�ȡ������Ϣ*/
        if(of_property_read_string(child, (const char*)"module_name", (const char**)&module_name))
        {
            dump_fetal("get module_name fail\n");
            continue;
        }
        /*��ȡmodid��Ϣ*/
        if(of_property_read_u32(child, "modid_sum", &sum))
        {
            sum = 0;
            dump_fetal("get modid_sum failed!\n");
        }

        of_property_for_each_u32(child, "modid_range", prop , p, u)
        {
            module_index = g_p_modid_table->moudid_sum;
            if(i%2 == 0)
            {
                g_p_modid_table->modid_info[module_index].modid_start = u;
            }
            if(i%2 == 1)
            {
                g_p_modid_table->modid_info[module_index].modid_end = u;
                snprintf(g_p_modid_table->modid_info[module_index].module,DUMP_MODULE_NAME_LEN, "%s", module_name);
                g_p_modid_table->moudid_sum++;
            }
            i++;
        }
        /*��ȡtask��Ϣ*/
        if(of_property_read_u32(child, "task_sum", &sum))
        {
            sum = 0;
            dump_fetal("get task_sum failed!\n");
        }
        for(index = 0; (index < sum)&&(g_cp_task_table); index++)
        {
            module_index = g_cp_task_table->task_sum;
            if(of_property_read_string_index(child, (const char*)"task_name", index,(const char**)&temp))
            {
                dump_fetal("get task_name fail\n");
            }
            else
            {
                snprintf(g_cp_task_table->task_info[module_index].task_name, 16, "%s",(char *)temp);
                snprintf(g_cp_task_table->task_info[module_index].module,DUMP_MODULE_NAME_LEN, "%s", module_name);
                g_cp_task_table->task_sum++;
            }
        }
        /*��ȡ�ж���Ϣ*/
        if(of_property_read_u32(child, "int_sum", &sum))
        {
            sum = 0;
            dump_fetal("get int_sum failed!\n");
        }
        for(index = 0; (index < sum)&&(g_cp_interupt_table); index++)
        {
            module_index = g_cp_interupt_table->intrupt_sum;
            if(of_property_read_u32_index(child, "int_id" ,index, &(g_cp_interupt_table->interupt_info[module_index].interrpt_id)))
            {
                dump_fetal("get int_id fail\n");
            }
            else
            {
                snprintf(g_cp_interupt_table->interupt_info[module_index].module,DUMP_MODULE_NAME_LEN, "%s", module_name);
                g_cp_interupt_table->intrupt_sum++;
            }
        }
    }

    dump_fetal("init apr dts success\n");
    return MDRV_OK;
}
/*****************************************************************************
* �� �� ��  : bsp_dump_parse_reset_info
*
* ��������  : ���쳣��Ϣ����
*
* �������  :  reset_info:�洢��������쳣��Ϣ��������
               size
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_parse_reset_info( dump_reset_log_t *dump_reset_info, dump_except_info_t dump_except_info)
{
    bsp_dump_get_reset_ccore(dump_except_info.except_core, dump_reset_info->reboot_core);
    bsp_dump_get_reset_reason(dump_except_info.except_reason, dump_reset_info->reboot_reson);
    bsp_dump_get_reset_modid(dump_except_info.except_reason, dump_except_info.modId, &dump_reset_info->modid);
    bsp_dump_get_reset_voice(dump_except_info.voice, dump_reset_info->voice);
    bsp_dump_get_reset_task(dump_except_info, dump_reset_info->task_name,&dump_reset_info->reboot_int);
    bsp_dump_get_reset_module(dump_except_info, dump_reset_info->task_name,dump_reset_info->module_name);
    if(DUMP_OUT_VOICE == dump_except_info.voice)
    {
        snprintf(dump_reset_info->brieftype, sizeof(dump_reset_info->brieftype), "%s", dump_reset_info->module_name);
    }
    else
    {
        snprintf(dump_reset_info->brieftype, sizeof(dump_reset_info->brieftype),"%s_VOICE", dump_reset_info->module_name);
    }
}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_module
*
* ��������  : ������λ���������
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_module(dump_except_info_t dump_except_info, u8* task_name,u8 * module)
{
    u32 index = 0;
    u32 size = 0;
    u32 reboot_reason = 0;

    bsp_dump_get_reboot_contex(NULL, &reboot_reason);
    /*������λ����modidȷ���������*/
    if(DUMP_REASON_NORMAL == reboot_reason)
    {
        if(!g_p_modid_table)
        {
            return;
        }
        for(index = 0; index < g_p_modid_table->moudid_sum; index++)
        {
            if((dump_except_info.modId >=g_p_modid_table->modid_info[index].modid_start)
                &&(dump_except_info.modId< g_p_modid_table->modid_info[index].modid_end) )
            {
                snprintf(module, 12, "%s", g_p_modid_table->modid_info[index].module);
                return;
            }
        }
        /*������Ҳ�����λ������������ø�λ������ж����ж��������*/
        if(index == g_p_modid_table->moudid_sum)
        {
            dump_fetal("can't find the modid in dts config\n");
            dump_fetal("reboot modid:0x%x\n", dump_except_info.modId);
        }
    }

    /*wdg abort�����������������жϺ�ȷ���������*/
    /*���Ϊ�жϸ�λ*/
    if(DUMP_CTX_INT == dump_except_info.reboot_context)
    {
        if(!g_cp_interupt_table)
        {
            return;
        }
        for(index = 0; index < g_cp_interupt_table->intrupt_sum; index++ )
        {
            if(dump_except_info.reboot_int == g_cp_interupt_table->interupt_info[index].interrpt_id)
            {
                snprintf(module, 12, "%s",  g_cp_interupt_table->interupt_info[index].module);
                break;
            }
        }
        if(index == g_cp_interupt_table->intrupt_sum)
        {
            dump_fetal("can't find the int in dts config\n");
            dump_fetal("reboot int num:0x%x\n", dump_except_info.reboot_int);
        }
        return;
    }
    if(DUMP_CTX_TASK == dump_except_info.reboot_context)
    {
        /*����Ϊ����λ*/
        if(!g_cp_task_table)
        {
            return;
        }
        /*�����������*/
        for(index = 0; index < g_cp_task_table->task_sum; index++ )
        {
            size = strlen(g_cp_task_table->task_info[index].task_name) > strlen(task_name)? \
                        strlen(task_name):strlen(g_cp_task_table->task_info[index].task_name);
            if(!strncmp(task_name, g_cp_task_table->task_info[index].task_name, size))
            {
                snprintf(module, 12, "%s",  g_cp_task_table->task_info[index].module);
                break;
            }
        }
        /*��������������в��Ҳ��������������Ϊ��*/
        if(index == g_cp_task_table->task_sum)
        {
            dump_fetal("can't find the task in dts config\n");
            dump_fetal("reboot task name:%s\n", task_name);
            return;
        }
    }
}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_cp_reset_reason
*
* ��������  : ��ȡCP��λ��ԭ��
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_task(dump_except_info_t dump_except_info,  u8 * task_name, u32 * reboot_int)
{
    u8* task_name_table = NULL;
    u32 task_cnt = 0;
    dump_task_info_s * temp_task_name = NULL;
    u8 *dump_base_info = NULL;
    u32 task_index = 0;
    u32 task_info_filed = 0;
    unsigned long task_name_offset = 0;
    u32 reboot_reason = 0;
    u32 reboot_core = 0;

    bsp_dump_get_reboot_contex(&reboot_core, &reboot_reason);


    /*�жϴ���*/
    if(DUMP_CTX_INT == dump_except_info.reboot_context)
    {
        dump_fetal("reboot reason int\n");
        *reboot_int = dump_except_info.reboot_int;
        return;
    }
    /*������*/
    if((DUMP_REASON_NORMAL == reboot_reason)||(DUMP_REASON_ARM == reboot_reason))
    {
        if(DUMP_CPU_COMM == reboot_core)
        {
            task_info_filed = DUMP_CP_BASE_INFO;
            task_name_offset = DUMP_CP_TASK_NAME_OFFSET;
        }
        else if(DUMP_CPU_APP == reboot_core)
        {
            task_info_filed = DUMP_MODEMAP_BASE_INFO;
            task_name_offset = DUMP_MODEMAP_TASK_NAME_OFFSET;
        }
        else
        {
            dump_fetal("except core error value:0x%x\n", dump_except_info.except_core);
            return;
        }
        /*��ȡ������Ϣ�������л���¼��ַ��Ϣ*/
        dump_base_info = bsp_dump_get_field_addr(task_info_filed);
        if(NULL == dump_base_info)
        {
            dump_fetal("get ddr info fail\n");
            dump_fetal("base info   field:0x%x ptr:0x%p\n", task_info_filed, dump_base_info);
            return;
        }
        snprintf(task_name, 16, "%s",(dump_base_info + task_name_offset));
    }
    else if(DUMP_REASON_WDT == reboot_reason)
    {
        /*���Ϊwdg��λ*/
        if(DUMP_CPU_COMM == reboot_core)
        {
            task_info_filed = DUMP_CP_ALLTASK_NAME;
        }
        else if(DUMP_CPU_APP == reboot_core)
        {
            task_info_filed = DUMP_MODEMAP_ALLTASK;
        }
        /*CP�洢������������*/
        task_name_table = bsp_dump_get_field_addr(task_info_filed);
        if(NULL == task_name_table)
        {
            dump_fetal("get cp tasck name ddr fail, field:0x%x\n", task_info_filed);
            return;
        }

        task_cnt = *((u32 *)task_name_table + 3)/4;
        /* ƫ��10�ֽڣ�ȥ������ͷ */
        task_name_table += 0x10;
        temp_task_name = (dump_task_info_s *)task_name_table;
        dump_fetal("task_cnt:0x%x\n", task_cnt);
        /*����������*/
        for(task_index = 0;task_index < task_cnt; task_index++)
        {
            if(temp_task_name->task_id == dump_except_info.reboot_task)
            {
                dump_fetal("reboot task:%s\n", temp_task_name->task_name);
                snprintf(task_name, 12 , "%s", temp_task_name->task_name);
                break;
            }
            temp_task_name++;
        }

        /*û���ҵ�������*/
        if(task_index == task_cnt)
        {
            dump_fetal("can't find the task, task id:0x%x\n", dump_except_info.reboot_task);
            return;
        }
    }
    else
    {
        dump_base_info = bsp_dump_get_field_addr(DUMP_MODEMAP_BASE_INFO);
        if(NULL == dump_base_info)
        {
            dump_fetal("get ddr info fail\n");
            dump_fetal("base info   field:0x%x ptr:0x%p\n", task_info_filed, dump_base_info);
            return;
        }
        snprintf(task_name, 16, "%s",(dump_base_info + DUMP_MODEMAP_TASK_NAME_OFFSET));
    }
}
u32 bsp_dump_search_taskid(dump_queue_t *Q)
{
    u32 element = 0;
    u32 index = 0;
    u32 queue_index = 0;
    u32 element_num = 0;

    if(Q->num < Q->maxNum)
    {
        element_num = Q->num;
    }
    else
    {
        element_num = Q->maxNum;
    }

    for(index = 0; index < element_num/2; index++)
    {
        queue_index = ((Q->rear+Q->maxNum)-2*(index + 1)) %Q->maxNum;
        element = Q->data[queue_index];
        dump_fetal("queue_index 0x%x element 0x%x\n", queue_index, element);
        if((DUMP_INT_IN_FLAG != ((element>>16)&0xFFFF))&&(DUMP_INT_EXIT_FLAG != ((element>>16)&0xFFFF)))
        {
            return element;
        }
    }
    return MDRV_ERROR;
}

/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_context_and_taskid
*
* ��������  :��ȡ��λΪ�жϸ�λ��������λ,���Ϊ����λ,������λ����id�������λΪ�жϣ�������λ�жϺ�
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_context_and_id(u32 *reboot_context, u32 *reboot_task,u32 *reboot_int, struct dump_global_struct_s* dump_head)
{
    dump_queue_t* task_switch = NULL;
    dump_base_info_t *dump_base_info = NULL;
    u32 task_switch_field = 0;
    u32 base_info_field = 0;
    u32 element = 0;
    u32 reboot_core = 0;

    *reboot_task = MDRV_ERROR;

    bsp_dump_get_reboot_contex(&reboot_core,NULL);
    if(DUMP_CPU_COMM== reboot_core)
    {
        task_switch_field = DUMP_CP_TASK_SWITCH;
        base_info_field = DUMP_CP_BASE_INFO;
        task_switch = (dump_queue_t*)bsp_dump_get_field_addr(task_switch_field);
        if(NULL == task_switch)
        {
            dump_fetal("get cp task switch ddr fail, field:0x%x\n", task_switch_field);
            return;
        }
    }
    else if(DUMP_CPU_APP == reboot_core)
    {
        task_switch_field = DUMP_MODEMAP_TASK_SWITCH;
        base_info_field = DUMP_MODEMAP_BASE_INFO;
    }
    else
    {
        return;
    }

    dump_base_info = (dump_base_info_t*)bsp_dump_get_field_addr(base_info_field);
    if(NULL == dump_base_info)
    {
        dump_fetal("get ddr info fail\n");
        dump_fetal("base info field:0x%x ptr:0x%p\n", base_info_field, dump_base_info);
        return;
    }

    if(NULL != dump_base_info)
    {
        if((dump_base_info->modId != DRV_ERRNO_DUMP_ARM_EXC) && (dump_base_info->modId != DRV_ERRNO_DUMP_CP_WDT))
        {
            *reboot_context = dump_base_info->reboot_context;
            if(DUMP_CTX_INT == dump_base_info->reboot_context)
            {
                *reboot_int = dump_base_info->reboot_int;
                *reboot_task = 0xFFFFFFFF;
                return;
            }
            else 
            {
                *reboot_int = 0xFFFFFFFF;
                if(task_switch != NULL)
                {
                    *reboot_task = bsp_dump_search_taskid(task_switch);
                }
                else
                {
                    *reboot_task =  dump_base_info->reboot_task;
                }
                return;
            }
        }
        else         
        {
            if(task_switch == NULL)
            {
                return;
            }
            /*���Ϊwdg��abort��λ*/
            element = task_switch->data[((task_switch->rear+task_switch->maxNum)-2) % task_switch->maxNum];/* [false alarm]:fortify */

            if(DUMP_INT_IN_FLAG == ((element>>16)&0xFFFF))
            {
                *reboot_context = DUMP_CTX_INT;
                *reboot_int = element&0xFFFF;
                *reboot_task = 0xFFFFFFFF;
            }
            else
            {
                *reboot_context = DUMP_CTX_TASK;
                *reboot_int = 0xFFFFFFFF;
                *reboot_task = bsp_dump_search_taskid(task_switch);
            }

        }
    }


}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_voice
*
* ��������  : ������λʱ�Ƿ���������
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_voice(u32 voice, u8 * reboot_voice)
{
    if(DUMP_OUT_VOICE == voice)
    {
        snprintf(reboot_voice, 4, "no");
    }
    else
    {
        snprintf(reboot_voice, 4, "yes");
    }
    return;
}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_modid
*
* ��������  : ��ȡ��λ��modid
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_modid(u32 reason, u32 reboot_modid, u32 * modId)
{
    if(DUMP_REASON_WDT == reason)
    {
       *modId =  DRV_ERRNO_DUMP_CP_WDT;
    }
    else
    {
        *modId = reboot_modid;
    }
}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_cp_reset_reason
*
* ��������  : ��ȡ��λ��ԭ��
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_reason(u32 reason, u8 * reboot_reason)
{
    if(DUMP_REASON_NORMAL == reason)
    {
        snprintf(reboot_reason, 16, "%s", NOARMAL);
    }
    else if(DUMP_REASON_WDT == reason)
    {
        snprintf(reboot_reason, 16, "%s", WDT);
    }
    else if(DUMP_REASON_ARM == reason)
    {
        snprintf(reboot_reason, 16, "%s", DATA_ABORT);
    }
    else if(DUMP_REASON_NOC == reason)
    {
        snprintf(reboot_reason, 16, "%s", NOC);
    }
    else if(DUMP_REASON_DMSS == reason)
    {
        snprintf(reboot_reason, 16, "%s", DMSS);
    }
    else if(DUMP_REASON_RST_FAIL== reason)
    {
        snprintf(reboot_reason, 16, "%s", RST_FAIL);
    }
    else if(DUMP_REASON_RST_NOT_SUPPORT== reason)
    {
        snprintf(reboot_reason, 16, "%s", RST_NOT_SUPPORT);
    }
    else if(DUMP_REASON_UNDEF == reason)
    {
        snprintf(reboot_reason, 16, "%s", UNDEFFINE);
    }
    else
    {
        snprintf(reboot_reason, 16, "%s", UNKNOW);
    }

}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_ccore
*
* ��������  : ��ȡCP��λ��ԭ��
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_ccore(u32 core, char *reboot_core)
{
    if(DUMP_CPU_COMM == core)
    {
        snprintf(reboot_core, 8, "%s", CCORE);
    }
    else if(DUMP_CPU_APP == core)
    {
        snprintf(reboot_core, 8, "%s", ACORE);
    }
    else
    {
        snprintf(reboot_core, 8, "%s", UNKNOW_CORE);
    }
    return;
}

u32  bsp_dump_show_apr_cfg(u32 type)
{
    u32 index = 0;

    if((2 == type)||(0 == type))
    {
        if(!g_cp_interupt_table)
        {
            dump_fetal("g_cp_interupt_table = NULL\n");
            return MDRV_ERROR;
        }
        dump_fetal("interupt sum :0x%x\n", g_cp_interupt_table->intrupt_sum);
        for(index = 0;index < g_cp_interupt_table->intrupt_sum; index++)
        {
            dump_fetal("index:0x%-2x interrpt_id:0x%-8x module_name:%s\n", \
                index, g_cp_interupt_table->interupt_info[index].interrpt_id, \
                g_cp_interupt_table->interupt_info[index].module);
        }
    }
    if((3 == type)||(0 == type))
    {
        if(!g_cp_task_table)
        {
            dump_fetal("g_cp_task_table = NULL\n");
            return MDRV_ERROR;
        }
        dump_fetal("task sum :0x%x\n", g_cp_task_table->task_sum);
        for(index = 0;index < g_cp_task_table->task_sum; index++)
        {
            dump_fetal("index:0x%-2x task:%-16s  module_name:%s\n", \
                index, g_cp_task_table->task_info[index].task_name, \
                g_cp_task_table->task_info[index].module);
        }
    }
    if((4 == type)||(0 == type))
    {
        if(!g_p_modid_table)
        {
            dump_fetal("g_p_modid_table = NULL\n");
            return MDRV_ERROR;
        }
        dump_fetal("modid sum :0x%x\n", g_p_modid_table->moudid_sum);
        for(index = 0;index < g_p_modid_table->moudid_sum; index++)
        {
            dump_fetal("index:0x%-2x modid start:0x%-8x end:0x%-8x module_name:%s\n", \
                index, g_p_modid_table->modid_info[index].modid_start, g_p_modid_table->modid_info[index].modid_end, \
                g_p_modid_table->modid_info[index].module);
        }
    }
    return MDRV_OK;
}
/*****************************************************************************
* �� �� ��  : om_get_reset_info
*
* ��������  : ��ȡ��λ��Ϣ
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void om_get_reset_info(char * reset_info, u32 size)
{
    struct dump_global_area_ctrl_s global_area = {0,};
    struct dump_global_base_info_s *dump_head = NULL;
    dump_except_info_t dump_except_info = {-1, -1, -1, -1, -1, -1, -1};
    dump_reset_log_t dump_reset_info = {};
    dump_base_info_t *dump_base_info = NULL;
    u32 base_info_field = 0;
    unsigned long modid_offset = 0;
    u32 reboot_reason = 0;
    u32 reboot_core = 0;
    struct dump_area_mntn_addr_info_s area_info = {NULL,NULL,0};
    u32 flag = DUMP_VOICE_BUTT;
    dump_area_head_t* area_head = NULL;
    s32 ret = BSP_ERROR;
    
    ret = dump_get_area_info(DUMP_AREA_CP,&area_info);
    
    if(ret == BSP_OK && area_info.vaddr)
    {
        area_head = (dump_area_head_t*)(area_info.vaddr);
        memcpy((u8*)&flag,(u8*)(area_head->version + 12),sizeof(u32));   
    }
  
    bsp_dump_get_reboot_contex(&reboot_core,&reboot_reason);

    if(dump_get_global_info(&global_area) == BSP_ERROR)
    {
        return ;
    }

    dump_head = &(global_area.virt_addr->base_info);
    /*��ȡ��λ�����Ϣ*/
    if(DUMP_CPU_COMM == reboot_core)
    {
        base_info_field = DUMP_CP_BASE_INFO;
        modid_offset = DUMP_CP_MODID_OFFSET;
    }
    else if(DUMP_CPU_APP == reboot_core)
    {
        base_info_field = DUMP_MODEMAP_BASE_INFO;
        modid_offset = DUMP_MODEMAP_MODID_OFFSET;
    }
    else
    {
        dump_fetal("except core error value:0x%x\n", dump_head->e_core);
        return;
    }

    dump_base_info = (dump_base_info_t*)bsp_dump_get_field_addr(base_info_field);
    if(NULL == dump_base_info)
    {
        dump_fetal("get ddr info fail\n");
        dump_fetal("base info   field:0x%x ptr:0x%p\n", base_info_field, dump_base_info);
        return;
    }
    dump_except_info.except_core = reboot_core;
    dump_except_info.voice = flag;
    dump_except_info.modId= dump_base_info->modId;
    dump_except_info.except_reason = reboot_reason;
    bsp_dump_get_reset_context_and_id(&(dump_except_info.reboot_context),\
                &(dump_except_info.reboot_task),&(dump_except_info.reboot_int),(struct dump_global_struct_s*)dump_head);


    dump_fetal("except_core = 0x%x\n", dump_except_info.except_core);
    dump_fetal("voice = 0x%x\n", dump_except_info.voice);
    dump_fetal("modId = 0x%x\n", dump_except_info.modId);
    dump_fetal("except_reason = 0x%x\n", dump_except_info.except_reason);
    dump_fetal("reboot_int = 0x%x\n", dump_except_info.reboot_int);
    dump_fetal("reboot_context = 0x%x\n", dump_except_info.reboot_context);
    dump_fetal("reboot_task = 0x%x\n", dump_except_info.reboot_task);
    /*������λ��Ϣ*/
    bsp_dump_parse_reset_info(&dump_reset_info, dump_except_info);
    /*��λ��Ϣд��������*/
    snprintf(reset_info, size,"brief:%s\ncmpnt:%s\nreset_reason:%s\ntask_name:%s\nmodid:0x%x\nreboot_int:0x%x\nvoice:%s\nreset_core:%s\n",
                dump_reset_info.brieftype,
                dump_reset_info.module_name,
                dump_reset_info.reboot_reson,
                dump_reset_info.task_name,
                dump_reset_info.modid,
                dump_reset_info.reboot_int,
                dump_reset_info.voice,
                dump_reset_info.reboot_core
            );


}
