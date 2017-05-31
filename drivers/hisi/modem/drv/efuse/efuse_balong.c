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
#include <linux/errno.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/clk.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/semaphore.h>
#include <linux/regulator/consumer.h>

#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>

#include "product_config.h"
#include "osl_bio.h"
#include "osl_sem.h"
#include "osl_thread.h"
#include "osl_wait.h"
#include "soc_clk.h"
#include "bsp_memmap.h"
#include "hi_base.h"
#include "hi_efuse.h"

#include "bsp_icc.h"
#include "bsp_sec_call.h"
#include "bsp_hardtimer.h"
#include "bsp_om.h"
#include "bsp_efuse.h"


/*lint -restore*/

#define MAX_EFUSE_DELAY   (0x1000000)       /*最大延迟时间*/

void* g_efuse_addr = 0;

struct clk* g_efuse_clk = NULL;
struct regulator* g_efuse_regulator = NULL;

struct semaphore g_efuse_semaphore;


int bsp_efuse_ops_prepare(void)
{
    int ret = EFUSE_OK;

    while (down_interruptible(&g_efuse_semaphore)) ;

    g_efuse_clk = (struct clk *)clk_get(NULL,"efuse_clk");
    if (IS_ERR(g_efuse_clk)) {
        efuse_print_error("clk_get error, 0x%x.\n", g_efuse_clk);
        ret = EFUSE_ERROR;
        goto clk_get_error;
    }

    ret = clk_prepare(g_efuse_clk);
    if (ret) {
        efuse_print_error("clk_prepare error, 0x%x.\n", (u32)ret);
        goto clk_prepare_error;
    }

    ret = clk_enable(g_efuse_clk);
    if (ret) {
        efuse_print_error("clk_enable error, 0x%x.\n", g_efuse_clk);
        goto clk_enable_error;
    }

    return ret;

clk_enable_error:
    clk_unprepare(g_efuse_clk);

clk_prepare_error:
    clk_put(g_efuse_clk);

clk_get_error:
    up(&g_efuse_semaphore);

    return ret;
}

void bsp_efuse_ops_complete(void)
{
    clk_disable(g_efuse_clk);

    clk_unprepare(g_efuse_clk);

    clk_put(g_efuse_clk);

    up(&g_efuse_semaphore);
}

int bsp_efuse_write_prepare(void)
{
    int ret = EFUSE_OK;

    ret = bsp_efuse_ops_prepare();
    if (ret)
        return ret;

    g_efuse_regulator = regulator_get(NULL, "EFUSE-vcc");
    if (NULL == g_efuse_regulator) {
        efuse_print_error("regulator_get error.\n");
        ret = EFUSE_ERROR;
        goto regulator_get_error;
    }

    ret = regulator_enable(g_efuse_regulator);
    if (ret) {
        efuse_print_error("regulator_enable error.\n");
        ret = EFUSE_ERROR;
        goto regulator_enable_error;
    }

    udelay(1000);/*lint !e737*/

    return ret;

regulator_enable_error:
    regulator_put(g_efuse_regulator);

regulator_get_error:
    bsp_efuse_ops_complete();

    return ret;
}

void bsp_efuse_write_complete(void)
{
    regulator_disable(g_efuse_regulator);
    regulator_put(g_efuse_regulator);
    bsp_efuse_ops_complete();
}

#ifndef CONFIG_TRUSTZONE

/*lint -save -e718 -e746*/
/*****************************************************************************
* 函 数 名  : bsp_efuse_read
*
* 功能描述  : 按组读取EFUSE中的数据
*
* 输入参数  : group  起始group
*                   num  数组长度(word数,不超过16)
* 输出参数  : pBuf ：EFUSE中的数据
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int bsp_efuse_read(u32* pBuf, const u32 group, const u32 num)
{
    u32 delay = 0;
    u32 count = 0;
    u32 value = 0;
    u32* buffer = 0;

    int ret = EFUSE_OK;

    if ((0 == num) || (group + num > EFUSE_MAX_SIZE) || (NULL == pBuf)) {
        efuse_print_error("error args, group=%d, num=%d, pBuf=0x%x.\n", group, num, pBuf);
        return EFUSE_ERROR;
    }

    ret = bsp_efuse_ops_prepare();
    if (ret) {
        return ret;
    }

    buffer = pBuf;

    if (osl_reg_get_bit(g_efuse_addr+HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_PD_STAT_BIT, HI_EFUSE_PD_STAT_BIT)) {

        osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_CFG_OFFSET, HI_EFUSE_PD_EN_BIT, HI_EFUSE_PD_EN_BIT, 0);

        delay = MAX_EFUSE_DELAY;
        do{
            value = osl_reg_get_bit(g_efuse_addr+HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_PD_STAT_BIT, HI_EFUSE_PD_STAT_BIT);
        } while ((value == 1) && (--delay));

        if (!delay) {
            ret = EFUSE_ERROR;
            goto efuse_read_error;
        }
    }

    osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_CFG_OFFSET, HI_EFUSE_AIB_SEL_BIT, HI_EFUSE_AIB_SEL_BIT, 1);

    for (count = 0; count < num; count++) {
        osl_reg_set_bit(g_efuse_addr+HI_EFUSE_GROUP_OFFSET, HI_EFUSE_GROUP_LBIT, HI_EFUSE_GROUP_HBIT, group+count);

        osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_CFG_OFFSET, HI_EFUSE_RD_EN_BIT, HI_EFUSE_RD_EN_BIT, 1);

        delay = MAX_EFUSE_DELAY;
        do {
            value = osl_reg_get_bit(g_efuse_addr+HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_RD_STAT_BIT, HI_EFUSE_RD_STAT_BIT);
        } while ((value == 0) && (--delay));

        if (!delay) {
            ret = EFUSE_ERROR;
            goto efuse_read_error;
        }

        *buffer = osl_reg_get_bit(g_efuse_addr+HI_EFUSEC_DATA_OFFSET, HI_EFUSE_DATA_LBIT, HI_EFUSE_DATA_HBIT);
        buffer++;
    }

    osl_reg_set_bit(g_efuse_addr + HI_EFUSEC_CFG_OFFSET, HI_EFUSE_AIB_SEL_BIT, HI_EFUSE_AIB_SEL_BIT, 0);

efuse_read_error:
    bsp_efuse_ops_complete();

    return ret;
}
/*lint -restore*/

/*****************************************************************************
* 函 数 名  : bsp_efuse_write
*
* 功能描述  : 烧写Efsue
*
* 输入参数  : pBuf:待烧写的EFUSE值
*                 group,Efuse地址偏移
*                 len,烧写长度
* 输出参数  :
*
* 返 回 值  :
*
* 其它说明  :
*
*****************************************************************************/
int bsp_efuse_write(u32 *pBuf, const u32 group, const u32 len)
{
    u32 delay = 0;
    u32 count = 0;
    u32 value = 0;
    u32 *buffer = NULL;

    int ret = EFUSE_OK;

    if ((0 == len) || (group + len > EFUSE_MAX_SIZE) || (NULL == pBuf)) {
        efuse_print_error("error args, group=%d, len=%d, pBuf=0x%x.\n", group, len, pBuf);
        return EFUSE_ERROR;
    }

    ret = bsp_efuse_write_prepare();
    if (ret) {
        return ret;
    }

    if (osl_reg_get_bit(g_efuse_addr+HI_HW_CFG_OFFSET, HI_EFUSE_DISFLAG_BIT, HI_EFUSE_DISFLAG_BIT)) {
        efuse_print_error("write is disable.\n");
        goto efuse_write_error;
    }

    if (osl_reg_get_bit(g_efuse_addr+HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_PD_STAT_BIT, HI_EFUSE_PD_STAT_BIT)) {

        osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_CFG_OFFSET, HI_EFUSE_PD_EN_BIT, HI_EFUSE_PD_EN_BIT, 0);

        delay = MAX_EFUSE_DELAY;
        do{
            value = osl_reg_get_bit(g_efuse_addr+HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_PD_STAT_BIT, HI_EFUSE_PD_STAT_BIT);
        } while ((value == 1) && (--delay));

        if (!delay) {
            ret = EFUSE_ERROR;
            goto efuse_exit_pd_error;
        }
    }

    osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_CFG_OFFSET, HI_EFUSE_AIB_SEL_BIT, HI_EFUSE_AIB_SEL_BIT, 1);

    osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_COUNT_OFFSET, HI_EFUSE_COUNT_LBIT, HI_EFUSE_COUNT_HBIT, EFUSE_COUNT_CFG);
    osl_reg_set_bit(g_efuse_addr+HI_PGM_COUNT_OFFSET, HI_EFUSE_PGM_COUNT_LBIT, HI_EFUSE_PGM_COUNT_HBIT, PGM_COUNT_CFG);

    osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_CFG_OFFSET, HI_EFUSE_PRE_PG_BIT, HI_EFUSE_PRE_PG_BIT, 1);

    delay = MAX_EFUSE_DELAY;
    do{
        value = osl_reg_get_bit(g_efuse_addr+HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_PGENB_STAT_BIT, HI_EFUSE_PGENB_STAT_BIT);
    } while ((value == 0) && (--delay));

    if (!delay) {
        ret = EFUSE_ERROR;
        goto efuse_write_error;
    }

    buffer = pBuf;
    for (count = 0; count < len; count++) {
        osl_reg_set_bit(g_efuse_addr+HI_EFUSE_GROUP_OFFSET, HI_EFUSE_GROUP_LBIT, HI_EFUSE_GROUP_HBIT, group+count);
        osl_reg_set_bit(g_efuse_addr+HI_PG_VALUE_OFFSET, HI_EFUSE_PG_VALUE_LBIT, HI_EFUSE_PG_VALUE_HBIT, *buffer);
        osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_CFG_OFFSET, HI_EFUSE_PGEN_BIT, HI_EFUSE_PGEN_BIT, 1);

        delay = MAX_EFUSE_DELAY;
        do{
            value = (unsigned)osl_reg_get_bit(g_efuse_addr+HI_EFUSEC_STATUS_OFFSET, HI_EFUSE_PG_STAT_BIT, HI_EFUSE_PG_STAT_BIT);
        } while ((value == 0) && (--delay));

        if (!delay) {
            ret = EFUSE_ERROR;
            goto efuse_write_error;
        }

        buffer++;
    }

efuse_write_error:
    osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_CFG_OFFSET, HI_EFUSE_AIB_SEL_BIT, HI_EFUSE_AIB_SEL_BIT, 0);
    osl_reg_set_bit(g_efuse_addr+HI_EFUSEC_CFG_OFFSET, HI_EFUSE_PRE_PG_BIT, HI_EFUSE_PRE_PG_BIT, 0);

efuse_exit_pd_error:
    bsp_efuse_write_complete();

    return ret;
}

static int __init bsp_efuse_init(void)
{
    void *addr = NULL;
    struct clk *efuse_clk = NULL;

    struct device_node *dev = NULL;
    const char name[] = "hisilicon,efuse_balong_app";

    sema_init(&g_efuse_semaphore, 1);

    dev = of_find_compatible_node(NULL, NULL, name);
    if(NULL == dev) {
        efuse_print_error("device node not found\n");
        return -1;
    }

    addr = of_iomap(dev, 0);
    if (0 == addr) {
        efuse_print_error("remap addr fail\n");
        return -1;
    }

    g_efuse_addr = addr;

    efuse_clk = (struct clk *)clk_get(NULL,"efuse_clk");
    if (IS_ERR(efuse_clk)) {
        efuse_print_error("efuse clk cannot get, 0x%x.\n", efuse_clk);
        return EFUSE_ERROR;
    }

    (void)clk_prepare(efuse_clk);
    (void)clk_enable(efuse_clk);
    clk_disable(efuse_clk);
    clk_unprepare(efuse_clk);
    clk_put(efuse_clk);

    efuse_print_info("efuse init ok.\n");

    return EFUSE_OK;
}

#else

u32 *g_efuse_buffer[EFUSE_MAX_SIZE];

int bsp_efuse_read(u32* pBuf, const u32 group, const u32 num)
{
    int ret = 0;

    if ((0 == num) || (group + num > EFUSE_MAX_SIZE) || (NULL == pBuf)) {
        efuse_print_error("error args, group=%d, num=%d, pBuf=0x%x.\n", group, num, pBuf);
        return EFUSE_ERROR;
    }

    memset((void*)g_efuse_buffer, 0, sizeof(g_efuse_buffer));

    ret = bsp_efuse_ops_prepare();
    if (ret) {
        return ret;
    }

    ret = bsp_sec_call(FUNC_EFUSE_READ, (unsigned int)(virt_to_phys(g_efuse_buffer)));

    bsp_efuse_ops_complete();

    memcpy((void*)pBuf, (void*)&g_efuse_buffer[group], num);

    return ret;
}
int bsp_efuse_write( u32 *pBuf, const u32 group, const u32 len )
{
    int ret = 0;

    if ((0 == len) || (group + len > EFUSE_MAX_SIZE) || (NULL == pBuf)) {
        efuse_print_error("error args, group=%d, len=%d, pBuf=0x%x.\n", group, len, pBuf);
        return EFUSE_ERROR;
    }

    memset((void*)g_efuse_buffer, 0, sizeof(g_efuse_buffer));
    memcpy((void*)&g_efuse_buffer[group], (void*)pBuf, len);

    ret = bsp_efuse_write_prepare();
    if (ret) {
        return ret;
    }

    ret = bsp_sec_call(FUNC_EFUSE_WRITE, (unsigned int)(virt_to_phys(g_efuse_buffer)));

    bsp_efuse_write_complete();

    return ret;
}
static int __init bsp_efuse_init(void)
{
    sema_init(&g_efuse_semaphore, 1);

    return EFUSE_OK;
}

#endif

int bsp_efuse_read_debug(u32 group)
{
    int ret = 0;
    u32 value = 0;

    ret = bsp_efuse_read(&value, group, 1);
    printk(KERN_ERR"group = 0x%08X, value = 0x%08X\n", group, value);

    return ret;
}

int bsp_efuse_write_debug(u32 group, u32 value)
{
    int ret = 0;

    ret = bsp_efuse_write(&value, group, 1);
    if (!ret)
        ret = bsp_efuse_read_debug(group);

    return ret;
}

void bsp_efuse_show(void)
{
    u32 group = 0;
    u32 value = 0;

    for (group = 0; group < EFUSE_MAX_SIZE; group++) {
        if (!bsp_efuse_read(&value, group, 1)) {
            printk(KERN_ERR"group = 0x%08X, value = 0x%08X\n", group, value);
        } else {
            printk(KERN_ERR"efuse group %d read fail.\n", group);
            return;
        }
    }
}


fs_initcall_sync(bsp_efuse_init);

EXPORT_SYMBOL(bsp_efuse_show);
EXPORT_SYMBOL(bsp_efuse_read);
EXPORT_SYMBOL(bsp_efuse_write);

