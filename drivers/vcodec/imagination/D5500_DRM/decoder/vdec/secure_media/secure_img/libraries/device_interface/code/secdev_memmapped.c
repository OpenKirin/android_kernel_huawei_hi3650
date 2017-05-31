/*!
 *****************************************************************************
 *
 * @File       secdev_memmapped.c
 * @Description    This file contains the kernel mode implementation of the
 *  memory-mapped device interface.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#include "secure_device.h"
#include <img_defs.h>
#include "target.h"

#include <linux/pci.h>
#include <linux/kobject.h>
#include <linux/interrupt.h>
#include <asm/io.h>
#include <asm/page.h>
#include <linux/mm.h>
#include <linux/delay.h>
#include <linux/version.h>
#include <linux/module.h>

#include <linux/platform_device.h>
#include <linux/clk.h>

#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,2,0)
    #include <linux/export.h>
#endif

#ifdef TARGET_HEADER_NAME
    #include TARGET_HEADER_NAME
#else
    #error TARGET_HEADER_NAME has to be defined
#endif

//MEMMAPPED device detected
static IMG_BOOL gbDevMapped = IMG_FALSE;

//Device information
static TARGET_sTargetConfig	gsFullInfo;
static SECURE_sDev *gpsInfo = IMG_NULL;
static IMG_CHAR *gpszDevName;

//Module parameters used only by memory mapped devices (ie not PCI)
static void* reg_base_addr;
static IMG_PHYSADDR module_reg_base = 0xa0000000;
static unsigned int module_reg_size = 0x10000;

static void* ram_base_addr;
static unsigned int module_ram_base = 0;
static unsigned int module_ram_size = 0;

module_param(module_reg_base, IMG_PHYSADDR, S_IRUGO);
module_param(module_reg_size, uint, S_IRUGO);

module_param(module_ram_base, uint, S_IRUGO);
module_param(module_ram_size, uint, S_IRUGO);

/*!
******************************************************************************

 @Function				memmappedio_DetectDevice

******************************************************************************/
static IMG_RESULT memmappedio_DetectDevice(SECDEV_eMapArea eArea)
{
	IMG_UINT32 ui32Result = IMG_SUCCESS;

	if (!gbDevMapped)
	{
		if (module_reg_base && module_reg_size)
			reg_base_addr = ioremap(module_reg_base, module_reg_size);

		if (module_ram_base && module_ram_size)
			ram_base_addr = ioremap(module_ram_base, module_ram_size);

		gbDevMapped = IMG_TRUE;
	}

	return ui32Result;
}

/*!
******************************************************************************

 @Function				memmappedio_DeviceAttach

******************************************************************************/
static IMG_RESULT memmappedio_DeviceAttach(
    IMG_CHAR *				pszDevName,
	SECDEV_eMapArea    eArea
)
{
	IMG_UINT32	ui32Result;

	IMG_ASSERT(gpszDevName != IMG_NULL);
	if (gpszDevName != IMG_NULL)
	{
		IMG_ASSERT(IMG_STRCMP(pszDevName, gpszDevName) == 0);
	}
	else
	{
		return IMG_ERROR_GENERIC_FAILURE;
	}

	/* In this implementation we initialise the MEMMAPPED component */
	ui32Result = memmappedio_DetectDevice(eArea);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);
	if (ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	return IMG_SUCCESS;
}

/*!
******************************************************************************
 @Function				SECDEV_Initialise

******************************************************************************/
IMG_RESULT SECDEV_Initialise(IMG_VOID)
{
    IMG_UINT32 ui32Result;

    gsFullInfo = gsTargetConfig;

    if (gpszDevName == IMG_NULL)
	{
		gpszDevName = IMG_STRDUP(asDevice[0].pszDeviceName);
        IMG_ASSERT(gpszDevName);
        if (gpszDevName == IMG_NULL)
        {
            ui32Result = IMG_ERROR_OUT_OF_MEMORY;
            goto error;
        }

        if (gsFullInfo.psWrapperControl)
        {
            gsFullInfo.psWrapperControl->ui32HostTargetCycleRatio = asDevice[0].ui32HostTargetRatio;
            gsFullInfo.psWrapperControl->ui32Flags = asDevice[0].ui32WrapFlags;
        }

        gsFullInfo.psPciInterface = &sPciInterface;
    }

	return IMG_SUCCESS;

error:
    return ui32Result;
}

/*!
******************************************************************************

 @Function				SECDEV_DeInitialise

******************************************************************************/
IMG_VOID SECDEV_DeInitialise(SECDEV_eMapArea    eArea)
{
	if (reg_base_addr)
	{
		iounmap(reg_base_addr);
	}

	if (ram_base_addr)
	{
		iounmap(ram_base_addr);
	}

	gpszDevName = IMG_NULL;

    if (gpszDevName)
    {
        IMG_FREE(gpszDevName);
    }

	gbDevMapped = IMG_FALSE;
}

/*!
******************************************************************************

 @Function				SECDEV_LocateDevice

 @Description
 This implementation can be called twice:
 Once for the main device under test, and once for a PDP subdevice on an ATLAS card

******************************************************************************/
IMG_RESULT SECDEV_LocateDevice(
	SECURE_sDev *			psInfo,
	SECDEV_eMapArea        eArea
)
{
	//TARGET_sPciDevice * psPciDeviceBaseInfo = gsFullInfo.psPciDevice;
	IMG_UINT32 ui32Result = IMG_SUCCESS;

	if(gpsInfo == NULL)
	{
        gpsInfo = psInfo;
	}
	
	/* Configure the device...*/
	ui32Result = memmappedio_DeviceAttach(psInfo->pszDeviceName, eArea);
	IMG_ASSERT(ui32Result == IMG_SUCCESS);

	if(ui32Result != IMG_SUCCESS)
	{
		return ui32Result;
	}

	//Save register pointer etc
	psInfo->paPhysRegBase = module_reg_base;
	psInfo->pvKmRegBase = reg_base_addr;
	psInfo->ui32RegSize	= module_reg_size;

	return ui32Result;
}

/*!
******************************************************************************

 @Function				SECDEV_GetMemoryInfo

******************************************************************************/
IMG_VOID SECDEV_GetMemoryInfo(
	IMG_VOID **         ppui32KmMemory,
	IMG_UINT64 *        pui64MemSize
)
{
	*ppui32KmMemory = ram_base_addr;
	*pui64MemSize = module_ram_size;
}

/*!
******************************************************************************

 @Function				SECDEV_CpuVirtAddrToCpuPAddr

******************************************************************************/
IMG_PHYSADDR SECDEV_CpuVirtAddrToCpuPAddr(
	IMG_VOID *pvCpuKmAddr
)
{
	IMG_PHYSADDR ret = 0;
	if(virt_addr_valid(pvCpuKmAddr))
	{
		//direct mapping of kernel addresses.
		//this works for kmalloc.
		ret = virt_to_phys(pvCpuKmAddr);
	}
	else
	{
		//walk the page table. 
		//Works for ioremap, vmalloc, and kmalloc(GPF_DMA),
		//but not, for some reason, kmalloc(GPF_KERNEL)
		struct page * pg = vmalloc_to_page(pvCpuKmAddr);
		if(pg) 
		{
			ret = page_to_phys(pg);
		}
		else 
		{
			IMG_ASSERT(!"vmalloc_to_page failure");
		}
	}
	return ret;
}
