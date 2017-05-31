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


#ifndef __DRV_MAILBOX_IFC_H__
#define __DRV_MAILBOX_IFC_H__


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
Զ�̺������ù�����Լ��:
*****************************************************************************/
/*
  Զ�̵��ýӿ���ʽ���̶����ӿڶ��忪�Ÿ��û�����ģ���ṩһ�ֻ���:
    �û����԰��Լ���ʵ����Ҫֱ�Ӷ��岢��������һ��Զ�̺������Ҵ�Զ�̺���������Լ����
    1.  �����ķ���ֵֻ��Ϊlong�ͣ����ܷ��ذ����������ݳ��ȵ�ָ�롣
        �������ó�ʱ���ش����: MAILBOX_TIME_OUT
    2.  �����Ĳ���Ŀǰ���֧��6����
    3.  �����Ĳ���ʵ���϶�������ָ�봦��ֻ��������7�����͵Ĳ�����
        1>  IFC_INFIX:  ����ָ����Σ����С�ں������ɵ�ʱ�򱻶��岢��Ч��
        2>  IFC_OUTFIX: ����ָ����Σ����С�ں������ɵ�ʱ�򱻶��岢��Ч��
        3>  IFC_BIFIX:  ����ָ��˫�Σ����С�ں������ɵ�ʱ�򱻶��岢��Ч��
        4>  IFC_INVAR:  �䳤ָ����Σ����С����һ���̶���С�ı����������壬�ں���������ʱ��Ч��
        5>  IFC_OUTVAR: �䳤ָ����Σ����С����һ���̶���С�ı����������壬�ں���������ʱ��Ч��
        6>  IFC_BIVAR:  �䳤ָ��˫�Σ����С����һ���̶���С�ı����������壬�ں���������ʱ��Ч��
        7>  IFC_INCNT:  4�ֽڳ�����Σ�

    4.  ���ĳ������Ϊ�ɱ��С��������ô������һ�����������ǹ̶���С�ı������������Һ����ں������ù����н�����ǰ�ߵĴ�С��
    5.  �������ÿ�����Ϊ�ȴ��˼䷵�صĵ��úͲ��ȴ��˼䷵�صĵ��ã�����ʽ���ã���
    6.  ע��(���+˫��)�Ĵ�С����(����+˫��)�Ĵ�С���ܳ������䵥���ʼ�������С��
*/
/*****************************************************************************
  1 �궨��
*****************************************************************************/
#define IFC_IN      0x1     /*���*/
#define IFC_OUT     0x2     /*����*/
#define IFC_BI      0x4     /*˫��*/

#define IFC_CNT         (0x1 << 8)   /*���ֽڳ���*/
#define IFC_FIX         (0x2 << 8)   /*�̶���Сָ��*/
#define IFC_VAR         (0x4 << 8)   /*�ɱ��Сָ��*/

#define IFC_INCNT       (IFC_IN  | IFC_CNT)  /*4�ֽڳ������*/
#define IFC_INFIX       (IFC_IN  | IFC_FIX)  /*����ָ����Σ����С�ں������ɵ�ʱ�򱻶��岢��Ч��*/
#define IFC_OUTFIX      (IFC_OUT | IFC_FIX)  /*����ָ����Σ����С�ں������ɵ�ʱ�򱻶��岢��Ч��*/
#define IFC_BIFIX       (IFC_BI  | IFC_FIX)  /*����ָ��˫�Σ����С�ں������ɵ�ʱ�򱻶��岢��Ч��*/
#define IFC_INVAR       (IFC_IN  | IFC_VAR)  /*�䳤ָ����Σ����С����һ���̶���С�ı����������壬�ں���������ʱ��Ч��*/
#define IFC_OUTVAR      (IFC_OUT | IFC_VAR)  /*�䳤ָ����Σ����С����һ���̶���С�ı����������壬�ں���������ʱ��Ч��*/
#define IFC_BIVAR       (IFC_BI  | IFC_VAR)  /*�䳤ָ��˫�Σ����С����һ���̶���С�ı����������壬�ں���������ʱ��Ч��*/

/*Զ�̵��ú���������������*/
#define IFC_MAX_ARG      (6)

#define IFC_LAUNCH        0
#define IFC_RESPONSE      1

#define IFC_INLINE  static __inline

#define IFC_WAIT_FOREVER            (0xffffffff)

#ifdef _DRV_LLT_
#define IFC_DEBUG_PARAM
#endif

#ifdef IFC_DEBUG_PARAM
#define _ifc_chk_arg(ph, db, sb)       __ifc_chk_arg(ph, db, sb)
#define _ifc_dbg_arg(ph, db, sb, df)   __ifc_dbg_arg(ph, db, sb, df)
#else
#define _ifc_chk_arg(ph, db, sb)
#define _ifc_dbg_arg(ph, db, sb, df)
#endif

#define IFC_ALIGN                   sizeof(unsigned int)
#define ifc_align_size(a,p)                     (((a)+((p)-1)) & ~((p)-1))

#ifdef _DRV_LLT_
#define C_CALL_ARG_R2L   /*C���Ե��ò������ҵ������*/
#endif
/*****************************************************************************
  2 �ṹ�嶨��
*****************************************************************************/
/*����Զ�̺���������Ϣͷ���ݽṹ��*/

struct ifc_param
{
    unsigned int type;  /*��¼�������ͣ����Σ���εȣ�IFC_INVAL*/
    unsigned int size;  /*��¼����������С*/
};
/*core share mem struct, don't use pointer or long*/
struct ifc_head
{
    unsigned int         scode;            /* ����Զ�̵����ʼ���š�*/
    unsigned int         rcode;            /* ִ�з�����ʱ���ʼ��š�*/
    unsigned int         stamp;            /* ʱ���������ɸѡ��ʱ�ͺ���Ӧ��*/
    unsigned int         retval;           /* ִ�з��������÷���ֵ��*/
    unsigned int         needret;          /* ִ�з��������÷���ֵ��*/
    unsigned int         argv[IFC_MAX_ARG];/* ִ�з��������÷���ֵ,��out buff�еı����ַ��*/
    unsigned int         data_phy_addr;             /* ��Ϣͷ�����ռ�֮����û��������Կռ���ʼ��ַ,ע�ñ���ֻ���������ַ*/

#ifdef IFC_DEBUG_PARAM      /*��IFC�еĺ��� �������е���*/
    struct ifc_param      param_tbl[IFC_MAX_ARG];
    signed int           param_prob;
#endif
};

struct ifc_arg
{

    unsigned long         addr;      /* ���������ַ */
    unsigned long         size;      /* ����������� */    
};

/*����Զ�̺���������Ϣͷ���ݽṹ��*/
struct ifc_mb
{
    void                 *mbuf;                 /* �����ʼ�������������*/
    struct ifc_arg        argo[IFC_MAX_ARG];    /* �洢��������ռ������*/
    struct ifc_head       head;                 /* ��д���ʼ��е�ifc��Ϣͷ*/
    void                 *waitsem;              /* �ȴ����÷��ص��ź���*/
    unsigned int         total_size;           /* �ʼ����ݳ��ȣ�����:ifc��Ϣͷ+�հ����+�����ݵ��ܳ���*/
    unsigned int         data_size;            /* ifc���ݳ���,������ifc��Ϣͷ����䲿��*/
    unsigned long        data_vitrual_addr; /*64 ������ ifc_head  �ṹ����data��Ա���漰�ĵ��������ַ���浽�ñ���*/
};

#ifdef C_CALL_ARG_R2L
/*vs pc���� �������������������*/
/*���ú�:�����������������ʱ����ĺ�*/

#define _IFC_ADD_ARG0(ary, p)
#define _IFC_ADD_ARG1(ary, d1, t1, a1, s1)                       __ifc_arg_out(ary, d1, (unsigned long)a1, s1, 0)
#define _IFC_ADD_ARG2(ary, d2, t2, a2, s2, d1, t1, a1, s1, ...)  _IFC_ADD_ARG1(ary, d1, t1, a1, s1); __ifc_arg_out(ary, d2, (unsigned long)a2 ,s2, (unsigned long)a1)
#define _IFC_ADD_ARG3(ary, d3, t3, a3, s3, d2, t2, a2, s2, ...)  _IFC_ADD_ARG2(ary, d2, t2, a2, s2, __VA_ARGS__); __ifc_arg_out(ary, d3, (unsigned long)a3 ,s3, (unsigned long)a2)
#define _IFC_ADD_ARG4(ary, d4, t4, a4, s4, d3, t3, a3, s3, ...)  _IFC_ADD_ARG3(ary, d3, t3, a3, s3, __VA_ARGS__); __ifc_arg_out(ary, d4, (unsigned long)a4 ,s4, (unsigned long)a3)
#define _IFC_ADD_ARG5(ary, d5, t5, a5, s5, d4, t4, a4, s4, ...)  _IFC_ADD_ARG4(ary, d4, t4, a4, s4, __VA_ARGS__); __ifc_arg_out(ary, d5, (unsigned long)a5 ,s5, (unsigned long)a4)
#define _IFC_ADD_ARG6(ary, d6, t6, a6, s6, d5, t5, a5, s5, ...)  _IFC_ADD_ARG5(ary, d5, t5, a5, s5, __VA_ARGS__); __ifc_arg_out(ary, d6, (unsigned long)a6 ,s6, (unsigned long)a5)


/*���ú�: ���������ѹ�������û����ݻ���ĺ�*/ /*������buf��������,ͬʱ�ѷ��ز�����ַ�ݴ�*/
/*��x86 c���Ե��ù淶����������ѹ����*/

#define _IFC_PUSHDATA0(d, av, p)
#define _IFC_PUSHDATA1(d, av, d1, t1, a1, s1)                     __ifc_push_arg(d, av, d1, (unsigned long)a1, s1, 0)
#define _IFC_PUSHDATA2(d, av, d2, t2, a2, s2, d1, t1, a1, s1)     _IFC_PUSHDATA1(d, av, d1, t1, a1, s1); __ifc_push_arg(d, av, d2, (unsigned long)a2 ,s2, (unsigned long)a1)
#define _IFC_PUSHDATA3(d, av, d3, t3, a3, s3, d2, t2, a2, s2,...) _IFC_PUSHDATA2(d, av, d2, t2, a2, s2, __VA_ARGS__); __ifc_push_arg(d, av, d3, (unsigned long)a3 ,s3, (unsigned long)a2)
#define _IFC_PUSHDATA4(d, av, d4, t4, a4, s4, d3, t3, a3, s3,...) _IFC_PUSHDATA3(d, av, d3, t3, a3, s3, __VA_ARGS__); __ifc_push_arg(d, av, d4, (unsigned long)a4 ,s4, (unsigned long)a3)
#define _IFC_PUSHDATA5(d, av, d5, t5, a5, s5, d4, t4, a4, s4,...) _IFC_PUSHDATA4(d, av, d4, t4, a4, s4, __VA_ARGS__); __ifc_push_arg(d, av, d5, (unsigned long)a5 ,s5, (unsigned long)a4)
#define _IFC_PUSHDATA6(d, av, d6, t6, a6, s6, d5, t5, a5, s5,...) _IFC_PUSHDATA5(d, av, d5, t5, a5, s5, __VA_ARGS__); __ifc_push_arg(d, av, d6, (unsigned long)a6 ,s6, (unsigned long)a5)


/*ִ�к�: ��˫����������뻺�濽�����������ĺ�*/
#define _IFC_PCOPY0(in, out, av, ao, p)
#define _IFC_PCOPY1(in, out, av, ao, d1, t1, a1, s1)                      __ifc_copy_arg(in, out, d1, s1, av, ao)
#define _IFC_PCOPY2(in, out, av, ao, d2, t2, a2, s2, d1, t1, a1, s1)      _IFC_PCOPY1(in, out, av, ao, d1, t1, a1, s1); __ifc_copy_arg(in, out, d2, s2, av, ao)
#define _IFC_PCOPY3(in, out, av, ao, d3, t3, a3, s3, d2, t2, a2, s2, ...) _IFC_PCOPY2(in, out, av, ao, d2, t2, a2, s2, __VA_ARGS__); __ifc_copy_arg(in, out, d3, s3, av, ao)
#define _IFC_PCOPY4(in, out, av, ao, d4, t4, a4, s4, d3, t3, a3, s3, ...) _IFC_PCOPY3(in, out, av, ao, d3, t3, a3, s3, __VA_ARGS__); __ifc_copy_arg(in, out, d4, s4, av, ao)
#define _IFC_PCOPY5(in, out, av, ao, d5, t5, a5, s5, d4, t4, a4, s4, ...) _IFC_PCOPY4(in, out, av, ao, d4, t4, a4, s4, __VA_ARGS__); __ifc_copy_arg(in, out, d5, s5, av, ao)
#define _IFC_PCOPY6(in, out, av, ao, d6, t6, a6, s6, d5, t5, a5, s5, ...) _IFC_PCOPY5(in, out, av, ao, d5, t5, a5, s5, __VA_ARGS__); __ifc_copy_arg(in, out, d6, s6, av, ao)

/*ִ�к�:���㺯����������ܴ�С�ĺ�*/
#define _IFC_OUTSIZE0(av, p)                                   0
#define _IFC_OUTSIZE1(av, d1, t1, a1, s1)                      __ifc_out_size(d1, s1, av)
#define _IFC_OUTSIZE2(av, d2, t2, a2, s2, d1, t1, a1, s1)      _IFC_OUTSIZE1(av, d1, t1, a1, s1) + __ifc_out_size(d2, s2, av)
#define _IFC_OUTSIZE3(av, d3, t3, a3, s3, d2, t2, a2, s2,...)  _IFC_OUTSIZE2(av, d2, t2, a2, s2, __VA_ARGS__) + __ifc_out_size(d3, s3, av)
#define _IFC_OUTSIZE4(av, d4, t4, a4, s4, d3, t3, a3, s3,...)  _IFC_OUTSIZE3(av, d3, t3, a3, s3, __VA_ARGS__) + __ifc_out_size(d4, s4, av)
#define _IFC_OUTSIZE5(av, d5, t5, a5, s5, d4, t4, a4, s4,...)  _IFC_OUTSIZE4(av, d4, t4, a4, s4, __VA_ARGS__) + __ifc_out_size(d5, s5, av)
#define _IFC_OUTSIZE6(av, d6, t6, a6, s6, d5, t5, a5, s5,...)  _IFC_OUTSIZE5(av, d5, t5, a5, s5, __VA_ARGS__) + __ifc_out_size(d6, s6, av)
#else
/*���ú�:����gcc���뺯�������������Ҽ���*/
/*�����������������ʱ����ĺ�*/

#define _IFC_ADD_ARG0(ary, p)
#define _IFC_ADD_ARG1(ary, d1, t1, a1, s1)                       __ifc_arg_out(ary, d1, (unsigned long)a1, s1, 0)
#define _IFC_ADD_ARG2(ary, d2, t2, a2, s2, d1, t1, a1, s1, ...)  __ifc_arg_out(ary, d2, (unsigned long)a2 ,s2, (unsigned long)a1); _IFC_ADD_ARG1(ary, d1, t1, a1, s1)
#define _IFC_ADD_ARG3(ary, d3, t3, a3, s3, d2, t2, a2, s2, ...)  __ifc_arg_out(ary, d3, (unsigned long)a3 ,s3, (unsigned long)a2); _IFC_ADD_ARG2(ary, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_ADD_ARG4(ary, d4, t4, a4, s4, d3, t3, a3, s3, ...)  __ifc_arg_out(ary, d4, (unsigned long)a4 ,s4, (unsigned long)a3); _IFC_ADD_ARG3(ary, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_ADD_ARG5(ary, d5, t5, a5, s5, d4, t4, a4, s4, ...)  __ifc_arg_out(ary, d5, (unsigned long)a5 ,s5, (unsigned long)a4); _IFC_ADD_ARG4(ary, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_ADD_ARG6(ary, d6, t6, a6, s6, d5, t5, a5, s5, ...)  __ifc_arg_out(ary, d6, (unsigned long)a6 ,s6, (unsigned long)a5); _IFC_ADD_ARG5(ary, d5, t5, a5, s5, __VA_ARGS__)


/*���ú�:���������ѹ�������û����ݻ���ĺ�*/ /*������buf��������,ͬʱ�ѷ��ز�����ַ�ݴ�*/
/*��arm c���Ե��ù淶����������ѹ����*/

#define _IFC_PUSHDATA0(d, av, p)
#define _IFC_PUSHDATA1(d, av, d1, t1, a1, s1)                     __ifc_push_arg(d, av, d1, (unsigned long)a1, s1, 0)
#define _IFC_PUSHDATA2(d, av, d2, t2, a2, s2, d1, t1, a1, s1)     __ifc_push_arg(d, av, d2, (unsigned long)a2 ,s2, (unsigned long)a1); _IFC_PUSHDATA1(d, av, d1, t1, a1, s1)
#define _IFC_PUSHDATA3(d, av, d3, t3, a3, s3, d2, t2, a2, s2,...) __ifc_push_arg(d, av, d3, (unsigned long)a3 ,s3, (unsigned long)a2); _IFC_PUSHDATA2(d, av, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_PUSHDATA4(d, av, d4, t4, a4, s4, d3, t3, a3, s3,...) __ifc_push_arg(d, av, d4, (unsigned long)a4 ,s4, (unsigned long)a3); _IFC_PUSHDATA3(d, av, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_PUSHDATA5(d, av, d5, t5, a5, s5, d4, t4, a4, s4,...) __ifc_push_arg(d, av, d5, (unsigned long)a5 ,s5, (unsigned long)a4); _IFC_PUSHDATA4(d, av, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_PUSHDATA6(d, av, d6, t6, a6, s6, d5, t5, a5, s5,...) __ifc_push_arg(d, av, d6, (unsigned long)a6 ,s6, (unsigned long)a5); _IFC_PUSHDATA5(d, av, d5, t5, a5, s5, __VA_ARGS__)


/*ִ�к�:��˫����������뻺�濽�����������ĺ�*/
#define _IFC_PCOPY0(in, out, av, ao, p)
#define _IFC_PCOPY1(in, out, av, ao, d1, t1, a1, s1)                      __ifc_copy_arg(in, out, d1, s1, av, ao)
#define _IFC_PCOPY2(in, out, av, ao, d2, t2, a2, s2, d1, t1, a1, s1)      __ifc_copy_arg(in, out, d2, s2, av, ao); _IFC_PCOPY1(in, out, av, ao, d1, t1, a1, s1)
#define _IFC_PCOPY3(in, out, av, ao, d3, t3, a3, s3, d2, t2, a2, s2, ...) __ifc_copy_arg(in, out, d3, s3, av, ao); _IFC_PCOPY2(in, out, av, ao, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_PCOPY4(in, out, av, ao, d4, t4, a4, s4, d3, t3, a3, s3, ...) __ifc_copy_arg(in, out, d4, s4, av, ao); _IFC_PCOPY3(in, out, av, ao, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_PCOPY5(in, out, av, ao, d5, t5, a5, s5, d4, t4, a4, s4, ...) __ifc_copy_arg(in, out, d5, s5, av, ao); _IFC_PCOPY4(in, out, av, ao, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_PCOPY6(in, out, av, ao, d6, t6, a6, s6, d5, t5, a5, s5, ...) __ifc_copy_arg(in, out, d6, s6, av, ao); _IFC_PCOPY5(in, out, av, ao, d5, t5, a5, s5, __VA_ARGS__)

/*ִ�к�:���㺯����������ܴ�С�ĺ�*/
#define _IFC_OUTSIZE0(av, p)                                   0
#define _IFC_OUTSIZE1(av, d1, t1, a1, s1)                      __ifc_out_size(d1, s1, av)
#define _IFC_OUTSIZE2(av, d2, t2, a2, s2, d1, t1, a1, s1)      __ifc_out_size(d2, s2, av) + _IFC_OUTSIZE1(av, d1, t1, a1, s1)
#define _IFC_OUTSIZE3(av, d3, t3, a3, s3, d2, t2, a2, s2,...)  __ifc_out_size(d3, s3, av) + _IFC_OUTSIZE2(av, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_OUTSIZE4(av, d4, t4, a4, s4, d3, t3, a3, s3,...)  __ifc_out_size(d4, s4, av) + _IFC_OUTSIZE3(av, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_OUTSIZE5(av, d5, t5, a5, s5, d4, t4, a4, s4,...)  __ifc_out_size(d5, s5, av) + _IFC_OUTSIZE4(av, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_OUTSIZE6(av, d6, t6, a6, s6, d5, t5, a5, s5,...)  __ifc_out_size(d6, s6, av) + _IFC_OUTSIZE5(av, d5, t5, a5, s5, __VA_ARGS__)

#endif

 /*ִ�к�:����Զ��ִ�к�������ָ���ַ�ĺ�*/
#define _IFC_PARAM0(in, out, av, p)
#define _IFC_PARAM1(in, out, av, d1, t1, a1, s1)                      (t1)__ifc_gen_arg(in, out, d1, s1, av)
#define _IFC_PARAM2(in, out, av, d2, t2, a2, s2, d1, t1, a1, s1)      (t2)__ifc_gen_arg(in, out, d2, s2, av), _IFC_PARAM1(in, out, av, d1, t1, a1, s1)
#define _IFC_PARAM3(in, out, av, d3, t3, a3, s3, d2, t2, a2, s2, ...) (t3)__ifc_gen_arg(in, out, d3, s3, av), _IFC_PARAM2(in, out, av, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_PARAM4(in, out, av, d4, t4, a4, s4, d3, t3, a3, s3, ...) (t4)__ifc_gen_arg(in, out, d4, s4, av), _IFC_PARAM3(in, out, av, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_PARAM5(in, out, av, d5, t5, a5, s5, d4, t4, a4, s4, ...) (t5)__ifc_gen_arg(in, out, d5, s5, av), _IFC_PARAM4(in, out, av, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_PARAM6(in, out, av, d6, t6, a6, s6, d5, t5, a5, s5, ...) (t6)__ifc_gen_arg(in, out, d6, s6, av), _IFC_PARAM5(in, out, av, d5, t5, a5, s5, __VA_ARGS__)


/*���ú�:���ɺ��������еĲ����ĺ�*/
#define _IFC_DECL0(p)       /*void*/
#define _IFC_DECL1(d1, t1, a1, s1)       t1 a1,
#define _IFC_DECL2(d2, t2, a2, s2, ...)  t2 a2, _IFC_DECL1(__VA_ARGS__)
#define _IFC_DECL3(d3, t3, a3, s3, ...)  t3 a3, _IFC_DECL2(__VA_ARGS__)
#define _IFC_DECL4(d4, t4, a4, s4, ...)  t4 a4, _IFC_DECL3(__VA_ARGS__)
#define _IFC_DECL5(d5, t5, a5, s5, ...)  t5 a5, _IFC_DECL4(__VA_ARGS__)
#define _IFC_DECL6(d6, t6, a6, s6, ...)  t6 a6, _IFC_DECL5(__VA_ARGS__)

/*���ú�:������������ܴ�С�ĺ�*/

#define _IFC_INSIZE0(p)                                   0
#define _IFC_INSIZE1(d1, t1, a1, s1)                      __ifc_in_size(d1, s1, 0)
#define _IFC_INSIZE2(d2, t2, a2, s2, d1, t1, a1, s1)     _IFC_INSIZE1(d1, t1, a1, s1) + __ifc_in_size(d2, s2, (unsigned long)a1)
#define _IFC_INSIZE3(d3, t3, a3, s3, d2, t2, a2, s2,...) _IFC_INSIZE2(d2, t2, a2, s2, __VA_ARGS__) + __ifc_in_size(d3, s3, (unsigned long)a2)
#define _IFC_INSIZE4(d4, t4, a4, s4, d3, t3, a3, s3,...) _IFC_INSIZE3(d3, t3, a3, s3, __VA_ARGS__) + __ifc_in_size(d4, s4, (unsigned long)a3)
#define _IFC_INSIZE5(d5, t5, a5, s5, d4, t4, a4, s4,...) _IFC_INSIZE4(d4, t4, a4, s4, __VA_ARGS__) + __ifc_in_size(d5, s5, (unsigned long)a4)
#define _IFC_INSIZE6(d6, t6, a6, s6, d5, t5, a5, s5,...) _IFC_INSIZE5(d5, t5, a5, s5, __VA_ARGS__) + __ifc_in_size(d6, s6, (unsigned long)a5)


/*���ú�:���沢������*/
#define _IFC_DBGPARAM0(p, a)
#define _IFC_DBGPARAM1(ph, d1, t1, a1, s1)                     _ifc_dbg_arg(ph, d1, s1, 0)
#define _IFC_DBGPARAM2(ph, d2, t2, a2, s2, d1, t1, a1, s1)     _IFC_DBGPARAM1(ph, d1, t1, a1, s1) ; _ifc_dbg_arg(ph, d2, s2, d1)
#define _IFC_DBGPARAM3(ph, d3, t3, a3, s3, d2, t2, a2, s2,...) _IFC_DBGPARAM2(ph, d2, t2, a2, s2, __VA_ARGS__); _ifc_dbg_arg(ph, d3, s3, d2)
#define _IFC_DBGPARAM4(ph, d4, t4, a4, s4, d3, t3, a3, s3,...) _IFC_DBGPARAM3(ph, d3, t3, a3, s3, __VA_ARGS__); _ifc_dbg_arg(ph, d4, s4, d3)
#define _IFC_DBGPARAM5(ph, d5, t5, a5, s5, d4, t4, a4, s4,...) _IFC_DBGPARAM4(ph, d4, t4, a4, s4, __VA_ARGS__); _ifc_dbg_arg(ph, d5, s5, d4)
#define _IFC_DBGPARAM6(ph, d6, t6, a6, s6, d5, t5, a5, s5,...) _IFC_DBGPARAM5(ph, d5, t5, a5, s5, __VA_ARGS__); _ifc_dbg_arg(ph, d6, s6, d5)

/*ִ�к�:������*/
#define _IFC_CHKPARAM0(p, a)
#define _IFC_CHKPARAM1(ph, d1, t1, a1, s1)                     _ifc_chk_arg(ph, d1, s1)
#define _IFC_CHKPARAM2(ph, d2, t2, a2, s2, d1, t1, a1, s1)     _ifc_chk_arg(ph, d2, s2); _IFC_CHKPARAM1(ph, d1, t1, a1, s1)
#define _IFC_CHKPARAM3(ph, d3, t3, a3, s3, d2, t2, a2, s2,...) _ifc_chk_arg(ph, d3, s3); _IFC_CHKPARAM2(ph, d2, t2, a2, s2, __VA_ARGS__)
#define _IFC_CHKPARAM4(ph, d4, t4, a4, s4, d3, t3, a3, s3,...) _ifc_chk_arg(ph, d4, s4); _IFC_CHKPARAM3(ph, d3, t3, a3, s3, __VA_ARGS__)
#define _IFC_CHKPARAM5(ph, d5, t5, a5, s5, d4, t4, a4, s4,...) _ifc_chk_arg(ph, d5, s5); _IFC_CHKPARAM4(ph, d4, t4, a4, s4, __VA_ARGS__)
#define _IFC_CHKPARAM6(ph, d6, t6, a6, s6, d5, t5, a5, s5,...) _ifc_chk_arg(ph, d6, s6); _IFC_CHKPARAM5(ph, d5, t5, a5, s5, __VA_ARGS__)


/*ִ�к�:����Զ�̵���ִ�к�����*/
#define IFC_GEN_EXEC_NAME(name) ife_##name

#ifdef _DRV_LLT_

#define _IFC_GEN_CALLx(x, id, name,  ...)		\
int name(_IFC_DECL##x(__VA_ARGS__) unsigned int timeout ){return 0;}

#define __IFC_GEN_EXECx(x, name, ...)		  \
int IFC_GEN_EXEC_NAME(name)(struct ifc_head * ifc_h) {return 0;}

#else
/*���ú�:����Զ�̺��������ߵĺ�*/
#define _IFC_GEN_CALLx(x, id, name,  ...)			                                                                                \
int name(_IFC_DECL##x(__VA_ARGS__) unsigned int timeout )                                                                         \
{                                                                                                                                   \
    struct ifc_mb ifc_b;                                                                                                            \
    struct ifc_arg *argo = ifc_b.argo;                                                                                              \
    unsigned long in_buf;                                                                                                           \
    int ret_val;                                                                                                                   \
    unsigned int *argv = ifc_b.head.argv;  /*�˷�����Ҫ���Ǳ�����ִ��˳�����*/                                                    \
    unsigned int in_size = (unsigned int)(_IFC_INSIZE##x(__VA_ARGS__));                                                           \
    argo=argo; argv=argv;                                                                                                           \
    ret_val = mailbox_ifc_init_buf(&ifc_b, id, IFC_LAUNCH, in_size, timeout);                                                       \
    if (ret_val) return ret_val;                                                                                                    \
    in_buf = ifc_b.data_vitrual_addr;                                                                                                       \
    _IFC_DBGPARAM##x(&ifc_b.head, __VA_ARGS__);  /*�����������*/                                                                   \
    _IFC_PUSHDATA##x(&in_buf, &argv, __VA_ARGS__);  /*������buf��������,ͬʱ�ѷ��ز�����ַ�ݴ�*/                                     \
    if (timeout) {                 /*��Ҫ�ȴ�����*/                                                                                 \
        _IFC_ADD_ARG##x(&argo, __VA_ARGS__); /* �ѷ���ֵ�ͳ��εĵ�ַ���뱾ͨ���Ļ����ʼ���Ϣ�������ڻ�ȡ������Ϣ�еĳ���ֵ*/       \
        return mailbox_ifc_send_wait(&ifc_b, timeout); /*�ȴ����յ��÷�����Ϣ��ɣ�*/                                               \
    }                                                                                                                               \
    else                                                                                                                            \
       return mailbox_ifc_send_no_wait(&ifc_b); /*����Ҫ�ȴ�����*/                                                                  \
}

/*ִ�к�:����Զ�̵���ִ�к�����,ע��ִ�к���name�������з���ֵ��(������void�ͣ�������벻��)*/
#define __IFC_GEN_EXECx(x, name, ...)			                                                                                     \
int IFC_GEN_EXEC_NAME(name)(struct ifc_head * ifc_h)                                                                                \
{                                                                                                                                    \
    struct ifc_mb ifc_b;                                                                                                             \
    unsigned long in_b, out_b;                                                                                                       \
    unsigned int *argv = ifc_h->argv;  /*��Ҫ���Ǳ�����ִ��˳�����*/                                                               \
    unsigned int *argo;                                                                                                             \
    unsigned int out_size = (unsigned int)(_IFC_OUTSIZE##x(&argv,__VA_ARGS__));                                                                   \
    if (mailbox_ifc_init_buf(&ifc_b, ifc_h->rcode, IFC_RESPONSE, out_size , 0)) return (int)MAILBOX_ERRO;                                 \
    out_b = ifc_b.data_vitrual_addr;  argv = ifc_h->argv;                                                                \
    in_b = (unsigned long)mailbox_phy_to_virt((unsigned long)(ifc_h->data_phy_addr));                    \
    _IFC_CHKPARAM##x(ifc_h, __VA_ARGS__);  /*�����÷��Ĳ��������Ƿ��ִ�з�һ�£����Ҽ������Ƿ���Ϲ淶*/                        \
    ifc_b.head.retval = (unsigned int)name(_IFC_PARAM##x(&in_b, &out_b, &argv, __VA_ARGS__));                                       \
    if (ifc_h->needret) {                /*��Ҫ�ȴ�����*/                                                                            \
        out_b = ifc_b.data_vitrual_addr; ifc_b.head.stamp = ifc_h->stamp; /*����ʱ�������У��*/                          \
        in_b = (unsigned long)mailbox_phy_to_virt((unsigned long)(ifc_h->data_phy_addr));        \
        argv = ifc_h->argv;  /*�������*/ argo = ifc_b.head.argv; /*�������*/                                                       \
        _IFC_PCOPY##x(&in_b, &out_b, &argv, &argo, __VA_ARGS__);  /*��˫�δ�inbuf������outbuf*/                                      \
       return mailbox_ifc_send_no_wait(&ifc_b);    /*��Ϣ�ܴ�Сд���ʼ�ͷ���������ҷ�������*/                                        \
    }                                                                                                                                \
    else                                                                                                                             \
       return mailbox_ifc_discard_buf(&ifc_b); /*ȡ������buff�������������˴η���*/                                                  \
}
#endif


extern int mailbox_ifc_init_buf(
                struct ifc_mb *ifc_b, 
                unsigned int mailcode, 
                unsigned int direct, 
                unsigned int inlen,
                unsigned int timeout);

extern int mailbox_ifc_send_no_wait(struct ifc_mb *ifc_b);

extern int mailbox_ifc_wait_resp(struct ifc_mb *ifc_b);

extern int mailbox_ifc_discard_buf(struct ifc_mb *ifc_b);

extern int mailbox_ifc_send_wait(struct ifc_mb *ifc_b, unsigned int timeout);


extern int mailbox_ifc_register_exec( 
                unsigned int mailcode,
                int (*ife_cb)(struct ifc_head * ifc_h)
                );

extern void __ifc_arg_out(struct ifc_arg ** p_ary, unsigned int db, unsigned long ab, unsigned int sb, unsigned int af);

extern void __ifc_push_arg(unsigned long * in, unsigned int ** p_av, unsigned int db, unsigned long ab, unsigned int sb, unsigned int af);

extern int __ifc_in_size(unsigned int db, unsigned int sb, unsigned int af);

extern void __ifc_dbg_arg(struct ifc_head *head, unsigned int db, unsigned int sb, unsigned int df);

extern int __ifc_out_size(unsigned int db, unsigned int sb, unsigned int **pp_af);

extern long __ifc_gen_arg(unsigned long *in, unsigned long *out, unsigned int db, unsigned int sb, unsigned int **pp_a);

extern void __ifc_copy_arg(unsigned long *in, unsigned long *out, unsigned int db, unsigned int sb, unsigned int **p_av , unsigned int **p_ao);

extern void __ifc_chk_arg(struct ifc_head *head, unsigned int db, unsigned int sb);

extern long mailbox_phy_to_virt(unsigned long  phy_addr);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /*end of __DRV_MAILBOX_IFC_H__*/

