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
#ifndef _APPLOG_H
#define _APPLOG_H
#endif

#include <product_config.h>

#include "osl_types.h"
#include "osl_sem.h"

#include "osl_spinlock.h"
#include "osl_thread.h"
#include "drv_nv_id.h"
#include <linux/dma-mapping.h>
//#include "diag_frame.h"
#include "bsp_diag_frame.h"
#include <bsp_socp.h>

#define APPLOG_OK                           (0)
#define APPLOG_ERR                         (-1) 
#define APPLOG_NULL                        (void*)0
#define APPLOG_VIRT_TO_PHYS(virt)           virt_to_phys((void*)virt)
#define APPLOG_SRC_BUF_LEN                 0x10000
#define APPLOG_CHN_INIT                    ((s32) 1)    /*通道已经分配*/
#define APPLOG_CHN_UNINIT                  ((s32) 0)    /*通道没有分配*/
#define APPLOG_MAX_USER_BUFF_LEN            511
#define APPLOG_MAX_FILENAME_LINENO_LEN      9
#define APPLOG_MAX_HIDS_BUFF_LEN            520

#define APPLOG_HEAD_LEN            2
#define applog_printf(fmt, ...)            (bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SOCP, "[applog]: <%s> %d  "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define applog_warning_printf(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_WARNING,BSP_MODU_SOCP, "[applog]: <%s> %d  "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define APPLOG_PHYS_TO_VIRT(phy)       (void *)(phys_to_virt((unsigned long)phy))

#define SOCP_CODER_SRC_APPLOG_IND  20

unsigned long long g_applog_dma_test_mask=0xffffffffULL;
#define APPLOG_FLUSH_CACHE(ptr, size)                      \
    do{                                                 \
        struct device dev;                              \
        memset(&dev,0,sizeof(struct device));           \
        dev.dma_mask = (unsigned long long *)(&g_applog_dma_test_mask);    \
        dma_map_single(&dev, ptr, size, DMA_TO_DEVICE);  \
    }while(0)
    
typedef struct 
{
    u8  level;
    u8  data[APPLOG_MAX_USER_BUFF_LEN];
}applog_data_stru;

typedef struct 
{
    diag_socp_head_stru     socp_head;
    diag_frame_head_stru    diag_head;
    diag_print_head_stru    print_head;
    u8  data[APPLOG_MAX_HIDS_BUFF_LEN];
}applog_send_buff;

typedef struct
{   
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eEncDebugEn;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eMode;
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;
    u32		            u32BypassEn;
    u32                 SrcCh;
    u32                 DstCh;
    u32                 u32SrcBufLen;
   // u32                 u32RDBufLen;
   // u32                 u32Threshold;
     
}applog_src_cfg_stru;
struct applog_ctrl_info
{
    u32   u32ApplogSwitchOnOff;
    u32   u32ApplogInvalidParameter;
    u32   u32ApplogLevel;
    u32   u32ApplogLength;
    u32   u32ApplogReport    ;
    u32   u32ApplogSendData ;
};
applog_src_cfg_stru      g_astAppLogCoderSrcCfg=
{
 
 SOCP_DATA_TYPE_0, SOCP_DATA_TYPE_EN,SOCP_ENC_DEBUG_DIS, SOCP_ENCSRC_CHNMODE_CTSPACKET,SOCP_CHAN_PRIORITY_2,0,SOCP_CODER_SRC_APPLOG_IND,SOCP_CODER_DST_OM_IND, 0x40000
};

u32 applog_src_chan_cfg(void);
u32 applog_send_data(u8* data,u32 len);
u32 applog_report(applog_send_buff *pstAppLogData,u32 datalen, u8 level);




