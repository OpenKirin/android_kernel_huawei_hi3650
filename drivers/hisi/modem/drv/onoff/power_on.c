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

/*lint --e{537} */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/syscalls.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/rtc.h>

#include <product_config.h>
#include <mdrv_sysboot.h>
#include <mdrv_chg.h>
#include <bsp_icc.h>
#include <bsp_onoff.h>
#include "power_exchange.h"
#include "mdrv_chg.h"



int his_boot_is_modem_crash(void)
{
    c_power_st_e status = power_on_c_status_get();

    if (status < POWER_MSP_OK )
        return 1;
    else
        return 0;
}


/*****************************************************************************
 �� �� ��  : bsp_start_mode_get
 ��������  : ���ڻ�ȡ����ģʽ
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
int bsp_start_mode_get(void)
{
    return DRV_START_MODE_NORMAL;
}


/*****************************************************************************
 �� �� ��  : bsp_power_icc_send_state
 ��������  : C�˺˼�ͨ�ź���
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static void bsp_power_icc_send_state(void)
{
    int ret = 0;
    int mode = 0;
    u32 icc_channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ONOFF;

    mode = bsp_start_mode_get();

    ret = bsp_icc_send(ICC_CPU_MODEM, icc_channel_id, (u8*)&mode, sizeof(mode));
    if (ret != (int)sizeof(mode))
    {
        pr_dbg("send len(%x) != expected len(%lu)\n", ret, (unsigned long)sizeof(mode));
    }
}

/*****************************************************************************
 �� �� ��  : bsp_power_ctrl_read_cb
 ��������  : C�˺˼�ص�����
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static s32 bsp_power_ctrl_read_cb( void )
{
    int rt = 0;
    int read_len = 0;
    stCtrlMsg msg;
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ONOFF;

	read_len = bsp_icc_read(channel_id, (u8*)&msg, sizeof(stCtrlMsg));
	if(read_len != (int)sizeof(stCtrlMsg))
	{
		pr_dbg("read len(%x) != expected len(%lu)\n", read_len, (unsigned long)sizeof(stCtrlMsg));
		return -1;
	}

	pr_dbg("bsp_power_ctrl_read_cb 0x%x\n", msg.pwr_type);

    switch(msg.pwr_type)
    {
    case E_POWER_ON_MODE_GET:
        bsp_power_icc_send_state();
        break;
    case E_POWER_SHUT_DOWN:
        drv_shut_down(msg.reason);
        break;
    case E_POWER_POWER_OFF:
        bsp_drv_power_off();
        break;
    case E_POWER_POWER_REBOOT:
        bsp_drv_power_reboot();
        break;
    default:
        pr_dbg("invalid ctrl by ccore\n");
        break;
    }

    return rt;
}

/*****************************************************************************
 �� �� ��  : his_boot_probe
 ��������  : power on
 �������  :
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
*****************************************************************************/
static int __init his_boot_probe(struct platform_device *pdev)
{
    int rt;
    u32 channel_id = ICC_CHN_IFC << 16 | IFC_RECV_FUNC_ONOFF;

    rt = bsp_icc_event_register(channel_id, (read_cb_func)bsp_power_ctrl_read_cb, NULL, NULL, NULL);
    if(rt != 0){
        pr_dbg("icc event register failed.\n");
    }

    return rt;
}

static struct platform_device his_boot_dev = {
    .name = "his_boot",
    .id = 0,
    .dev = {
    .init_name = "his_boot",
    },
};

static struct platform_driver his_boot_drv = {
    .probe      = his_boot_probe,
	.driver		= {
		.name	= "his_boot",
		.owner	= THIS_MODULE,
	},
};

static int __init his_boot_init(void)
{
    ssize_t ret = 0;

    pr_dbg(KERN_DEBUG "his_boot_init.\r\n");

    ret = platform_device_register(&his_boot_dev);
    if(ret)
    {
        pr_dbg("register his_boot device failed. \r\n");
        return ret;
    }

    ret = platform_driver_register(&his_boot_drv);
    if(ret)
    {
        pr_dbg("register his_boot driver failed. \r\n");
        platform_device_unregister(&his_boot_dev);
    }

    return ret;

}

static void __exit his_boot_exit(void)
{
    platform_driver_unregister(&his_boot_drv);
    platform_device_unregister(&his_boot_dev);
}

late_initcall(his_boot_init);

MODULE_AUTHOR("E5 FEATURE");

