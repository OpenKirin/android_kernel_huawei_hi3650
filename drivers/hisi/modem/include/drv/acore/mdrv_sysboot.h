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

#ifndef __MDRV_ACORE_SYSBOOT_H__
#define __MDRV_ACORE_SYSBOOT_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <mdrv_sysboot_commmon.h>

typedef enum DRV_SHUTDOWN_REASON_tag_s
{
	DRV_SHUTDOWN_POWER_KEY,             /* ���� Power ���ػ�          */
	DRV_SHUTDOWN_BATTERY_ERROR,         /* ����쳣                   */
	DRV_SHUTDOWN_LOW_BATTERY,           /* ��ص�����                 */
	DRV_SHUTDOWN_TEMPERATURE_PROTECT,   /* ���±����ػ�               */
	DRV_SHUTDOWN_CHARGE_REMOVE,         /* �ػ����ģʽ�£��γ������ */
	DRV_SHUTDOWN_UPDATE,                /* �ػ�����������ģʽ         */
	DRV_SHUTDOWN_RESET,                 /* ϵͳ��λ                 */
	DRV_SHUTDOWN_BUTT
}DRV_SHUTDOWN_REASON_E;

/*****************************************************************************
* �� �� ��  : mdrv_sysboot_shutdown
*
* ��������  : Modem��ϵͳ�ػ��ӿ�
*
* �������  :
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*            1 PS/TAF�ϲ�ֻ���ע���¹ػ�������
*            2 ���ڰ����ػ����͵�ػ����ػ����ʱ�γ�������ػ���MBB��������ĳ�����ʹ�õ����ڲ��ӿڣ�
*              ��Ҫ����mdrv_sysboot_shutdown�ӿڡ�
*
*****************************************************************************/
void mdrv_sysboot_shutdown(void);

/*****************************************************************************
* �� �� ��  : mdrv_sysboot_restart
*
* ��������  : ��λModem��ϵͳ
*
* �������  :
* �������  :
*
* �� �� ֵ  :
*
* ����˵��  :
*            1 ��phone��̬�£��ú���ʵ�ֶ�Modem��ϵͳ��C�ˣ��ĵ�����λ��MBB��̬�£����Ƕ�ȫϵͳ��λ��
*            2 ccore��acore�����Ե��ã����ս��һ�£��ڲ�����ʵ���в��죻
*            3 �쳣����£������Ҫ����modemʱ����ʹ��system_error�ӿڣ��Ͻ�ֱ�ӵ��øýӿڡ�
*
*****************************************************************************/
void mdrv_sysboot_restart(void);

/*****************************************************************************
* �� �� ��  : mdrv_set_modem_state
*
* ��������  : ����Modem״̬��Ready����Off��
*
* �������  : unsigned int state  Modem״̬��MODEM_NOT_READY(0), MODEM_READY(1)
* �������  :
*
* �� �� ֵ  : 0�����óɹ���1�����ò��ɹ�
*
* ����˵��  :1 tafͨ���ýӿ�����Modem״̬��
*            2 ͬʱ���ڶ��Modemʱ���ϲ����������Modem״̬��ȷ�Ϻ��ٵ��øýӿ�����Modem״̬���ϲ���øýӿ�����MODEM_READY
*            ǰ��Ӧ�ò��ȡ����״̬ΪModem Off��
*
*****************************************************************************/
int  mdrv_set_modem_state(unsigned int state);

/*****************************************************************************
* �� �� ��  : mdrv_sysboot_register_reset_notify
*
* ��������  : ��resetģ��ע��֪ͨmodem C�� reset������֪ͨ����
*
* �������  : const char *pname   �ϲ����ע������֣��9���ַ�������������������������洢
*             pdrv_reset_cbfun pcbfun  �ص�����ָ��
*             int userdata      �ϲ�������ݣ��ڵ��ûص�����ʱ����Ϊ��δ���ע����
*             int priolevel  �ص������������ȼ����ο�emum DRV_RESET_CALLCBFUN_PRIO���壬ֵԽС���ȼ�Խ��
* �������  :
*
* �� �� ֵ  : 0��ע��ɹ���1��ע�᲻�ɹ�
*
* ����˵��  :
*
*****************************************************************************/
typedef int (*pdrv_reset_cbfun)(DRV_RESET_CB_MOMENT_E enparam, int userdata);
int mdrv_sysboot_register_reset_notify(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);

/*****************************************************************************
 �� �� ��  : hifireset_regcbfunc
 ��������  : �ṩ�ϲ�Ӧ�ó���ע��HIFI������λ�Ļص��ӿں�����
 �������  : pname���ϲ����ע������֣�ע�ⲻ�����������9���ַ���������洢��
             pcbfun���ص�����ָ�롣
             puserdata:�ϲ�������ݣ��ڵ��ûص�����ʱ����Ϊ��δ����û���
             priolevel: �ص������������ȼ���0-49
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
extern int hifireset_regcbfunc(const char *pname, pdrv_reset_cbfun pcbfun, int userdata, int priolevel);
#define DRV_HIFIRESET_REGCBFUNC(pname,pcbfun, userdata, priolevel)\
                hifireset_regcbfunc(pname,pcbfun, userdata, priolevel)

#ifdef __cplusplus
}
#endif
#endif
