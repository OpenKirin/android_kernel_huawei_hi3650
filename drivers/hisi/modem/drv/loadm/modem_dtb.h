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

#ifndef _MODEM_DTB_H
#define _MODEM_DTB_H
#include <linux/types.h>

#define MODEM_DTB_HEADER_LEN (1024*6)

#define MODEMID_MASK_BITS	   (0xff)
#define MODEMID_K_BITS(n)      ((n >> 24) & MODEMID_MASK_BITS)
#define MODEMID_H_BITS(n)      ((n >> 16) & MODEMID_MASK_BITS)
#define MODEMID_M_BITS(n)      ((n >> 8) & MODEMID_MASK_BITS)
#define MODEMID_L_BITS(n)      (n & MODEMID_MASK_BITS)

/* ��Ҫmask����Ƶ�۰�ID�Ż�modemid��bit[9:0] */
#define MODEMID_VENDOR_MASK		(~(uint32_t)0x3FF)

typedef struct modem_dt_table_t {
	uint32_t magic;
	uint32_t version;
	uint32_t num_entries;
} modem_dt_table_t;

typedef struct modem_dt_entry_t {
    uint8_t boardid[4];
    uint8_t reserved[4];
    uint32_t dtb_size;
    uint32_t vrl_size;
    uint32_t dtb_offset;
    uint32_t vrl_offset;
    uint64_t dtb_file;
    uint64_t vrl_file;
} modem_dt_entry_t;

#endif
