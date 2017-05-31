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

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifndef __DRV_TEMP_CFG_H__
#define __DRV_TEMP_CFG_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define HKADC_LOGIC_CHAN_MAX 32 /* ����߼�ͨ���� */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*����hkadc����ͨ����*/
#define HKADC_CHAN_MAX 16
#define TSENS_REGION_MAX 3

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/
struct drv_hkadc_map
{
    unsigned int logic_chan;
    unsigned int phy_chan;
    unsigned int nv_id;
    unsigned int nv_len;
    unsigned int modem_id;
    char * name;
};

/* �¶�������ṹ */
typedef struct hkadc_chan_out
{
    unsigned short volt_l;    /* ���ص�HKADC��ѹֵ����λ:���� */
    unsigned short volt_r;   /* ���ص�HKADC��ѹֵȡ�� */
    short          temp_l;     /* ���ص��¶�ֵ����λ:���϶� */
    short          temp_r;    /* ���ص��¶�ֵȡ�� */
}DRV_CHANNEL_OUTPUT;

/* �¶ȵ�ѹ��Ӧ��ṹ */
typedef struct hkadc_tem_value
{
    short   temp;             /* �¶ȵ㣬��λ:���϶� */
    unsigned short volt;      /* ��ѹ�㣬��λ:���� */
}TEM_VOLT_TABLE;

/* �������bit�ṹ */
typedef struct hkadc_out_config
{
   unsigned int out_prop:2;
   unsigned int out_wake:1;
   unsigned int out_vol_temp:1;
   unsigned int out_reserv1:4;
   unsigned int out_acore:1;
   unsigned int out_ccore:1;
   unsigned int out_reserv2:22;
} OUT_PROP_CONFIG;

/* �¶��������ṹ */
typedef struct hkadc_chan_config
{
    union
    {
        unsigned int out_config;       /* bit0-bit1 0:����� 1:������� 2:ѭ����� */
                                       /* bit2 1:������� 0:�ǻ������ */
                                       /* bit3: 0:ֻ�����ѹ 1:��ѹ�¶Ⱦ���� */
                                       /* bit8: A����� */
                                       /* bit9: C����� */
        struct hkadc_out_config bit_out_config;
    } outcfg;

    unsigned int have_config;
    unsigned short out_peroid;     /* ѭ�����ʱ��ѭ�����ڣ���λ:�� */
    unsigned short temp_data_len;  /* �¶�ת������ */
    struct hkadc_tem_value temp_table[32]; /* �¶�ת����ʵ�ʳ��Ȳμ�temp_data_len */
} DRV_CHANNEL_CONFIG;

/* ϵͳ�ŵ��¶ȱ������ýṹ */
typedef struct sys_temp_cfg
{
    unsigned short enable;        /* bit0:���±���ʹ�� bit1:���±���ʹ�� 1 ʹ�� 0 �ر�*/
    unsigned short hkadc_id;      /* ϵͳ�ŵ��¶ȱ�����hkadcͨ��ID */
    short          high_thres;    /* ϵͳ�ŵ���±����ĵ�ѹ��ֵ ���¶�Խ�ߣ���ѹԽ��*/
    unsigned short high_count;    /* ϵͳ�ŵ���±����������ޣ����˺�ϵͳ�ػ� */
    short          low_thres;     /* ϵͳ�ŵ���±����ĵ�ѹ��ֵ ���¶�Խ�ͣ���ѹԽ��*/
    unsigned short low_count;     /* ϵͳ�ŵ���±����������ޣ����˺�ϵͳ�ػ� */

    unsigned int   reserved[2];   /*����*/
} DRV_SYS_TEMP_PRO;

/* �����¶������ݽṹ */
typedef struct thermal_data_area
{
    unsigned int               magic_start;                 /* ������ʼMagic Code 0x5A5A5A5A*/
    struct hkadc_chan_out       chan_out[HKADC_CHAN_MAX];    /* ��ͨ���������*/
    struct hkadc_chan_config    chan_cfg[HKADC_CHAN_MAX];    /* ��ͨ���������� */
    struct sys_temp_cfg         sys_temp_cfg;                /* ϵͳ�ŵ��±����� */
    unsigned int               hw_ver_id;                   /* �汾ID */
    unsigned char               phy_tbl[HKADC_LOGIC_CHAN_MAX];     /* HKADC�߼�ͨ��������ͨ����Ӧ�� */
    unsigned int               debug_flag;                  /* ���⿪�� */
    unsigned int               magic_end;                   /* ��������Magic Code 0x5A5A5A5A*/
} DRV_HKADC_DATA_AREA;

/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

