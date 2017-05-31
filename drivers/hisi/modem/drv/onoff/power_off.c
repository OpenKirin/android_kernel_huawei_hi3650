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
#include <hi_gpio.h>
#include <linux/gpio.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/syscalls.h>
#include <linux/errno.h>
#include <linux/err.h>
#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/rtc.h>

#include <product_config.h>
#include <osl_list.h>
#include <osl_types.h>
#include <osl_spinlock.h>
#include <mdrv_chg.h>
#include <mdrv_sysboot.h>
#include <bsp_pmu.h>
#include <power_com.h>
#include "power_exchange.h"

#include <bsp_reset.h>

#include <bsp_onoff.h>
#include <bsp_sysctrl.h>
#include "mdrv_chg.h"

#include "bsp_dump.h"


struct bsp_onoff_callback {
    struct list_head node;
    void (*fn)(void);
};

static LIST_HEAD(list_callback);
static DEFINE_SPINLOCK(list_spinlock); //lint !e43 !e64 !e120



void bsp_reboot_callback_register(void (*hook)(void))
{
    /*lint --e{*} */
    unsigned long flags = 0;

    struct bsp_onoff_callback *callback =
        (struct bsp_onoff_callback *)kmalloc(sizeof(struct bsp_onoff_callback), GFP_KERNEL);
    if (NULL == callback)
    {
        pr_dbg("fail to malloc struct bsp_onoff_callback \n");
        return;
    }

    callback->fn = hook;

    spin_lock_irqsave(&list_spinlock, flags);
    list_add(&callback->node, &list_callback);
    spin_unlock_irqrestore(&list_spinlock, flags);
    /*coverity[leaked_storage] */
}

/******************************************************************************
*  Function:  drv_shut_down
*  Description: start the power off process.
*  Input:
*         eReason : shutdown reason.
*  Output:
*         None
*  Return:
*         None
*  Note  : �ײ���ùػ��ӿڣ����ö�ʱ�����ϱ��¼���Ӧ�á�
*          ��ʱʱ����Ӧ�ò��ػ����ɵײ�ǿ�ƹػ���
********************************************************************************/
void drv_shut_down( DRV_SHUTDOWN_REASON_E enReason )
{
    if (DRV_SHUTDOWN_RESET == enReason)
    {
        pr_dbg("drv_shut_down is called, modem reset...");

        system_error(DRV_ERROR_USER_RESET, 0, 0, NULL, 0);
    }
    /* Notify the monitor task */
}

/******************************************************************************
*  Function:  bsp_drv_power_off
*  Description: same as drv_power_off, the public API
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : Ӧ�õ��ùػ�ʱ���ã�at+cfun=8
********************************************************************************/
void bsp_drv_power_off( void )
{
    printk(KERN_ERR"we will do nothing...\n");
}

/******************************************************************************
*  Function:  bsp_drv_power_reboot
*  Description: same as drv_power_off, the public API
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : Ӧ�õ�������ʱ���ã�at+cfun=6
********************************************************************************/
void bsp_drv_power_reboot( void )
{
    printk(KERN_ERR"bsp_drv_power_reboot is called, modem reset...\n");

    system_error(DRV_ERROR_USER_RESET, 0, 0, NULL, 0);
}

void mdrv_sysboot_restart(void)
{
	bsp_om_save_reboot_log(__FUNCTION__, __builtin_return_address(0));
	bsp_drv_power_reboot();
}


/******************************************************************************
*  Function:  bsp_drv_power_reboot_direct
*  Description:
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  : ֱ������
********************************************************************************/
void bsp_drv_power_reboot_direct( void )
{
    printk(KERN_ERR"bsp_drv_power_reboot_direct is called, modem reset...\n");

    system_error(DRV_ERROR_USER_RESET, 0, 0, NULL, 0);
}

/******************************************************************************
*  Function:  balong_power_restart
*  Description: same as bsp_drv_power_reboot, ϵͳ����ʱʹ��
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :android_reboot(ANDROID_RB_RESTART, 0, 0);
********************************************************************************/
/*lint -save -e958 */
void balong_power_restart(char mode, const char *cmd)
{
	bsp_om_save_reboot_log(__FUNCTION__, __builtin_return_address(0));
    bsp_drv_power_reboot();
}
EXPORT_SYMBOL_GPL(balong_power_restart);
/*lint -restore */

/******************************************************************************
*  Function:  balong_power_off
*  Description: same as bsp_drv_power_off, ϵͳ����ʱʹ��
*  Input:
*         None
*  Output:
*         None
*  Return:
*         None
*  Note  :android_reboot(ANDROID_RB_POWER_OFF, 0, 0);
********************************************************************************/
void balong_power_off( void )
{
	bsp_om_save_reboot_log(__FUNCTION__, __builtin_return_address(0));
	bsp_drv_power_off();
}
EXPORT_SYMBOL_GPL(balong_power_off);



void mdrv_sysboot_shutdown(void)
{
	bsp_om_save_reboot_log(__FUNCTION__, __builtin_return_address(0));
	drv_shut_down(DRV_SHUTDOWN_TEMPERATURE_PROTECT);
}



