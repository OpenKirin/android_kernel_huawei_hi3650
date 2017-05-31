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

#ifndef __BSP_EFUSE_H__
#define __BSP_EFUSE_H__

#include "osl_types.h"
#include "product_config.h"

#define EFUSE_OK               (0)
#define EFUSE_ERROR            (-1)

#define EFUSE_GROUP_SIZE        (4)
#define EFUSE_MAX_ALLOW_SIZE    (16)

#define     BUF_ERROR          (-55)
#define     LEN_ERROR          (-56)
#define     READ_EFUSE_ERROR   (-57)

#define BIT_INDEX_IN_GROUP(bit)             (bit & 0x1F)
#define GROUP_INDEX(bit)                    (bit >> 0x5)

#define  efuse_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_EFUSE, "[efuse]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  efuse_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_INFO,  BSP_MODU_EFUSE, "[efuse]: "fmt, ##__VA_ARGS__))


typedef enum
{
    EFUSE_READ  = 0,
    EFUSE_WRITE = 1

}EFUSE_OPT;

typedef struct
{
    u32 opt;
    u32 start;
    u32 len;
    int ret;
    u32 buf[EFUSE_MAX_ALLOW_SIZE];
}EFUSE_DATA_STRU;

typedef struct
{
    u32 icc_callback_stamp;
    u32 rw_start_stamp;
    u32 rw_end_stamp;
    u32 icc_send_stamp;
}EFUSE_DEBUG_INFO;

#ifdef CONFIG_EFUSE
/*****************************************************************************
* �� �� ��  : bsp_efuse_read
*
* ��������  : �����ȡEFUSE�е�����
*
* �������  : group  ��ʼgroup
*                   num  ���鳤��(word��,������16)
* �������  : pBuf ��EFUSE�е�����
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
int bsp_efuse_read(u32* pBuf, const u32 group, const u32 num);

/*****************************************************************************
* �� �� ��  : bsp_efuse_write
*
* ��������  : ��дEfsue
*
* �������  : pBuf:����д��EFUSEֵ
*                 group,Efuse��ַƫ��
*                 len,��д����
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
int bsp_efuse_write( u32 *pBuf, const u32 group, const u32 len);

/*****************************************************************************
* �� �� ��  : bsp_efuse_show
*
* ��������  : ��ʾefsue������Ϣ
*
* �������  :
*
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*
*****************************************************************************/
int efuse_init(void);

void bsp_efuse_show(void);

#if defined(__KERNEL__)

#include <linux/kernel.h>

#if defined(CONFIG_EFUSE_BALONG)

int bsp_efuse_ops_prepare(void);
void bsp_efuse_ops_complete(void);

int bsp_efuse_write_prepare(void);
void bsp_efuse_write_complete(void);
#else
static inline int bsp_efuse_ops_prepare(void)
{
    return 0;
}
static inline void bsp_efuse_ops_complete(void)
{
}
static inline int bsp_efuse_write_prepare(void)
{
    return 0;
}
static inline void bsp_efuse_write_complete(void)
{
}
#endif
#endif

#else

static inline int efuse_init(void)
{
    return 0;
}
static inline int bsp_efuse_read(u32* pBuf, const u32 group, const u32 num)
{
    return 0;
}
static inline int bsp_efuse_write( u32 *pBuf, const u32 group, const u32 len)
{
    return 0;
}
static inline void bsp_efuse_show(void)
{
    return;
}
static inline int bsp_efuse_ops_prepare(void)
{
    return 0;
}
static inline void bsp_efuse_ops_complete(void)
{
}
static inline int bsp_efuse_write_prepare(void)
{
    return 0;
}
static inline void bsp_efuse_write_complete(void)
{
}
#endif

#endif

