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

#include <product_config.h>

#include <osl_types.h>

#include <bsp_om.h>

#ifdef __cplusplus
extern "C"
{
#endif


#define mipi_print_error(fmt, ...)
#ifndef MIPI_OK
#define MIPI_OK (0)
#endif

#ifndef MIPI_ERROR
#define MIPI_ERROR  (-1)
#endif


#ifdef CONFIG_MIPI


/*****************************************************************************
* �� �� ��  : bsp_mipi_raw_write
*
* ��������  : MIPI Raw Write
*
* �������  : u32 mipi_id   MIPI ID
*             u32 cmd_low   MIPI ָ��ĵ�32λ
*             u32 cmd_high  MIPI ָ��ĸ�32λ
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_raw_write(u32 mipi_id, u32 cmd_low, u32 cmd_high);


/*****************************************************************************
* �� �� ��  : bsp_mipi_r0_write
*
* ��������  : MIPI R0 Write
*
* �������  : u32 mipi_id   MIPI ID
*             u32 slave_id  Slave ID
*             u8  value     ��Ҫ��Slaveд���ֵ
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_r0_write(u32 mipi_id, u32 slave_id, u8 value);

/*****************************************************************************
* �� �� ��  : bsp_mipi_read
*
* ��������  : MIPI Register Read
*
* �������  : u32 mipi_id   MIPI ID
*             u32 slave_id  Slave ID
*             u32 reg_addr  Slave�ļĴ�����ַ
*             u32 is_half_speed �Ƿ���Ҫ���ٴ���
* �������  : u8 *value     �ض����
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value);


/*****************************************************************************
* �� �� ��  : bsp_mipi_write
*
* ��������  : MIPI Register Write
*
* �������  : u32 mipi_id   MIPI ID
*             u32 slave_id  Slave ID
*             u32 reg_addr  Slave�ļĴ�����ַ
*             u8  value     ��Ҫ��Slaveд���ֵ
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value);


/*****************************************************************************
* �� �� ��  : bsp_mipi_ex_read
*
* ��������  : MIPI Expended Register Read
*
* �������  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave�ļĴ�����ַ
*             u32 is_half_speed �Ƿ���Ҫ���ٴ���
*             u32 byte_count ��Ҫ�ض����ֽ���
* �������  : u8 *value      �ض�buffer��ַ
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_ex_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value, u32 byte_count);


/*****************************************************************************
* �� �� ��  : bsp_mipi_ex_write
*
* ��������  : MIPI Expended Register Write
*
* �������  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave�ļĴ�����ַ
*             u8* value      ��Ҫ��Slaveд���buffer��ַ
*             u32 byte_count ��Ҫд����ֽ���
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_ex_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 *value, u32 byte_count);


/*****************************************************************************
* �� �� ��  : bsp_mipi_ex_read_byte
*
* ��������  : MIPI Expended Register Read�����ֽڶ�ȡ
*
* �������  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave�ļĴ�����ַ
*             u32 is_half_speed �Ƿ���Ҫ���ٴ���
* �������  : u8  *value     �ض�buffer��ַ
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_ex_read_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value);

/*****************************************************************************
* �� �� ��  : bsp_mipi_ex_read_word
*
* ��������  : MIPI Expended Register Read�����ֶ�ȡ
*
* �������  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave�ļĴ�����ַ
*             u32 is_half_speed �Ƿ���Ҫ���ٴ���
* �������  : u16 *value      �ض�buffer��ַ
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_ex_read_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u16 *value);


/*****************************************************************************
* �� �� ��  : bsp_mipi_ex_read_dword
*
* ��������  : MIPI Expended Register Read��˫�ֶ�ȡ
*
* �������  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave�ļĴ�����ַ
*             u32 is_half_speed �Ƿ���Ҫ���ٴ���
* �������  : u32 *value      �ض�buffer��ַ
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_ex_read_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u32 *value);


/*****************************************************************************
* �� �� ��  : bsp_mipi_ex_write_byte
*
* ��������  : MIPI Expended Register Write�����ֽ�д��
*
* �������  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave�ļĴ�����ַ
*             u8  value      ��Ҫ��Slaveд���ֵ
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_ex_write_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value);


/*****************************************************************************
* �� �� ��  : bsp_mipi_ex_write_word
*
* ��������  : MIPI Expended Register Write������д��
*
* �������  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave�ļĴ�����ַ
*             u16 value      ��Ҫ��Slaveд���ֵ
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_ex_write_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u16 value);


/*****************************************************************************
* �� �� ��  : bsp_mipi_ex_write_dword
*
* ��������  : MIPI Expended Register Write��˫��д��
*
* �������  : u32 mipi_id    MIPI ID
*             u32 slave_id   Slave ID
*             u32 reg_addr   Slave�ļĴ�����ַ
*             u32 value      ��Ҫ��Slaveд���ֵ
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_ex_write_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 value);


/*****************************************************************************
* �� �� ��  : bsp_mipi_init
*
* ��������  : MIPI ��ʼ��
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : 0 �ɹ���������ʧ�ܣ�
*
* ����˵��  :
*
*****************************************************************************/
int bsp_mipi_init(void);

#else

static inline int bsp_mipi_raw_write(u32 mipi_id, u32 cmd_low, u32 cmd_high)
{
    return 0;
}

static inline int bsp_mipi_r0_write(u32 mipi_id, u32 slave_id, u8 value)
{
    return 0;
}

static inline int bsp_mipi_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value)
{
    return 0;
}

static inline int bsp_mipi_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value)
{
    return 0;
}

static inline int bsp_mipi_ex_read(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value, u32 byte_count)
{
    return 0;
}

static inline int bsp_mipi_ex_write(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 *value, u32 byte_count)
{
    return 0;
}

static inline int bsp_mipi_ex_read_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u8 *value)
{
    return 0;
}

static inline int bsp_mipi_ex_read_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u32 *value)
{
    return 0;
}

static inline int bsp_mipi_ex_read_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 is_half_speed, u16 *value)
{
    return 0;
}

static inline int bsp_mipi_ex_write_byte(u32 mipi_id, u32 slave_id, u32 reg_addr, u8 value)
{
    return 0;
}

static inline int bsp_mipi_ex_write_word(u32 mipi_id, u32 slave_id, u32 reg_addr, u16 value)
{
    return 0;
}

static inline int bsp_mipi_ex_write_dword(u32 mipi_id, u32 slave_id, u32 reg_addr, u32 value)
{
    return 0;
}

static inline void bsp_mipi_init(void)
{
}

#endif


#ifdef __cplusplus
    }
#endif

