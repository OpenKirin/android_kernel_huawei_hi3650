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

#ifndef __BSP_DDR_TEST_H__
#define __BSP_DDR_TEST_H__

#ifdef __cplusplus
extern "C" {
#endif



#include "product_config.h"
#include <osl_types.h>
#include <osl_bio.h>
#include <hi_pmu.h>
#include <bsp_pmu.h>

/* ddr_test_ctrl */

/* use pmu_reg 0x153, wr, val consist when reset
 * 8 bits
 * reg_addr may change in different soc-platform
 */
#if defined(__KERNEL__) 
#define DDR_TEST_CTRL_REG   (void*)((unsigned)pmic_get_base_addr()+(0x153<<2))
#elif defined(__OS_VXWORKS__) || defined(__OS_RTOSCK__)
#define DDR_TEST_CTRL_REG   ((unsigned)pmic_get_base_addr()+(0x153<<2))
#else
#define DDR_TEST_CTRL_REG   (0x9001a000+(0x153<<2))
#endif

/* DDR检测功能使用 PMU复位不丢失寄存器 0x153寄存器
   地址为 (0x9001A000 + (0x153<<2) */
enum ddr_test_ctrl{
    ddr_test_ctrl_start = 0,
    ddr_test_ctrl_loop   = ddr_test_ctrl_start,
    ddr_test_ctrl_exmist,
    ddr_test_ctrl_loopback,
    ddr_test_ctrl_jump,
    ddr_test_ctrl_boot,
    ddr_test_ctrl_reboot,

    ddr_test_ctrl_end = 8, /* use pmu reg, 8bit */
};

#define ddr_test_print(fmt, ...) (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_EDMA, "[ddr_test]:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))


#if ( defined(ATE_VECTOR)||defined(BSP_CONFIG_EMU) || (!defined(PMIC_HI6559)) )

static inline u32 get_ddr_test_ctrl(enum ddr_test_ctrl bit)
{
    UNUSED(bit);
    return 0;
}
#else

static inline u32 get_ddr_test_ctrl(enum ddr_test_ctrl bit)
{   return readl(DDR_TEST_CTRL_REG) & (0x1<<bit);   }

#endif

#if defined (CONFIG_DDR_TEST_KERNEL)
int ddr_test_period_pm(void);
#else
static inline int ddr_test_period_pm(void){ return 0; };
#endif

#ifdef __cplusplus
}
#endif

#endif    /* __BSP_DDR_TEST_H__ */

