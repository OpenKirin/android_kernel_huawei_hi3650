/*!
 *****************************************************************************
 *
 * @File       sysmem_api_dmabuf.c
 * @Description    This file contains kernel mode implementation of the
 *  System Memory Kernel Mode API.
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

#include <linux/mm.h>
#include <linux/gfp.h>
#include <linux/module.h>
#include <linux/vmalloc.h>
#include <linux/dma-buf.h>
#include <linux/scatterlist.h>
#include <linux/dma-mapping.h>

#include "img_defs.h"
#include "report_api.h"
#include "sysmem_utils.h"
#include "system.h"

struct palloc_dmabuf_priv {
    struct sg_table *sgt;
    struct dma_buf *buf;
    struct dma_buf_attachment *attach;
};

/*!
******************************************************************************

 @Function              ImportPages

******************************************************************************/
static IMG_RESULT ImportPages(
    SYSMEM_Heap        *heap,
    SYSDEVU_sInfo    *sysdev,
    IMG_UINT32        ui32Size,
    SYSMEMU_sPages *psPages,
    SYS_eMemAttrib    eMemAttrib,
    IMG_INT32        buff_fd,
    IMG_UINT64        *pPhyAddrs,
    IMG_VOID        *priv,
    IMG_BOOL        kernelMapped
)
{
    struct sg_table *sgt;
    struct dma_buf *buf;
    IMG_VOID *pvCpuKmAddr = IMG_NULL;
    IMG_RESULT result = IMG_ERROR_FATAL;
    unsigned numPages, pg_i = 0;
    struct scatterlist *sgl, *next;
    struct dma_buf_attachment *attach;
    struct palloc_dmabuf_priv *tmp;

    DEBUG_REPORT(REPORT_MODULE_SYSMEM, "Importing dmabuf %d of size %u", buff_fd, ui32Size);

    tmp = kzalloc(sizeof(struct palloc_dmabuf_priv), GFP_KERNEL);
    if (!tmp) {
        IMG_ASSERT(IMG_FALSE);
        goto alloc_priv_err;
    }

    buf = dma_buf_get(buff_fd);
    if (IS_ERR(buf)) {
        IMG_ASSERT(IMG_FALSE);
        goto buf_no_found;
    }

    numPages = (ui32Size + PAGE_SIZE - 1) / PAGE_SIZE;

    IMG_ASSERT(sysdev);
    IMG_ASSERT(sysdev->native_device);
    attach = dma_buf_attach(buf, sysdev->native_device);
    if (IS_ERR(attach)) {
        IMG_ASSERT(IMG_FALSE);
        goto attach_error;
    }

    sgt = dma_buf_map_attachment(attach, DMA_BIDIRECTIONAL);
    if (IS_ERR(sgt)) {
        IMG_ASSERT(IMG_FALSE);
        goto map_error;
    }

    sgl = sgt->sgl;

    if (sgl == NULL) {
        IMG_ASSERT(IMG_FALSE);
        REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error obtaining scatter list");
        goto map_error;
    }

    // Get physical addresses from scatter list
    for (next = sgl; next; next = sg_next(next))
    {
        //sg_dma_address(next) and sg_dma_len(next) can be used to get the base physical address if the dmabuf allocator supports these interfaces.
        //sg_phys(next) and next->length return incorrect values when used with DMA API in Linux supporting the above
        int offset;
        dma_addr_t chunkBase = sg_phys(next);
        for (offset = 0; offset < next->length; offset += PAGE_SIZE, ++pg_i)
        {
            if (pg_i >= numPages)
                break;

            pPhyAddrs[pg_i] = chunkBase + offset;
        }

        if (pg_i >= numPages)
            break;
    }

    {
        size_t  physAddrArrSize = numPages * sizeof(psPages->ppaPhysAddr[0]);
        size_t  phy_i;

        psPages->ppaPhysAddr = IMG_BIGORSMALL_ALLOC(physAddrArrSize);
        IMG_ASSERT(psPages->ppaPhysAddr != IMG_NULL);
        if (psPages->ppaPhysAddr == IMG_NULL)
        {
            return IMG_ERROR_OUT_OF_MEMORY;
        }

        for (phy_i = 0; phy_i < numPages; ++phy_i) {
            psPages->ppaPhysAddr[phy_i] = pPhyAddrs[phy_i];
        }

    }


    if (kernelMapped) {
        result = dma_buf_begin_cpu_access(buf, 0 /* start */, ui32Size /* size */, DMA_BIDIRECTIONAL);
        if (result) {
            IMG_ASSERT(IMG_FALSE);
            REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "begin_cpu_access failed");
            goto cpu_access_error;
        }

        // FIXME vmap not implemented in dmabuf_exporter, better to use kmap here
        //pvCpuKmAddr = dma_buf_vmap(buf);
        pvCpuKmAddr = dma_buf_kmap(buf, numPages);
        DEBUG_REPORT(REPORT_MODULE_SYSMEM, "psPages=0x%pK phys=0x%llx pvCpuKmAddr=0x%pK\n", 
            psPages, psPages->ppaPhysAddr ? *psPages->ppaPhysAddr : 0, pvCpuKmAddr);
        if (!pvCpuKmAddr) {
            IMG_ASSERT(IMG_FALSE);
            REPORT(REPORT_MODULE_SYSMEM, REPORT_ERR, "Error mapping to kernel address");
            result = IMG_ERROR_FATAL;
            goto buf_vmap_error;
        }
    }

    tmp->attach = attach;
    tmp->buf = buf;
    tmp->sgt = sgt;

    psPages->sysdev = sysdev;
    psPages->hRegHandle = NULL;
    psPages->pvCpuKmAddr = pvCpuKmAddr;
    psPages->pvImplData = (IMG_HANDLE)tmp;

    return IMG_SUCCESS;

buf_vmap_error:
    dma_buf_end_cpu_access(buf, 0, ui32Size, DMA_BIDIRECTIONAL);
cpu_access_error:
    dma_buf_unmap_attachment(attach, sgt, DMA_BIDIRECTIONAL);
map_error:
    dma_buf_detach(buf, attach);
attach_error:
    dma_buf_put(buf);
buf_no_found:
alloc_priv_err:
    return result;
}

/*!
******************************************************************************
 @Function                FreePages

******************************************************************************/
static IMG_VOID FreePages(
    SYSMEM_Heap *  heap,
    IMG_HANDLE     hPagesHandle
)
{
    SYSMEMU_sPages *  psPages = hPagesHandle;
    size_t            numPages;

    numPages = (psPages->ui32Size + HOST_MMU_PAGE_SIZE - 1)/HOST_MMU_PAGE_SIZE;

    if (psPages->bImported) {
        struct palloc_dmabuf_priv *priv = psPages->pvImplData;

        IMG_ASSERT(psPages);
        if (!psPages)
            return;

        DEBUG_REPORT(REPORT_MODULE_SYSMEM, "Releasing dmabuf 0x%pK", psPages);

        if (psPages->pvCpuKmAddr) {
            // vunmap not implemented in dmabuf_exporter
            //dma_buf_vunmap(priv->buf, psPages->pvCpuKmAddr);
            dma_buf_kunmap(priv->buf, numPages, psPages->pvCpuKmAddr);
            dma_buf_end_cpu_access(priv->buf, 0, psPages->ui32Size, DMA_BIDIRECTIONAL);
        }


        if (priv->sgt)
            dma_buf_unmap_attachment(priv->attach, priv->sgt, DMA_BIDIRECTIONAL);


        if (priv->attach)
            dma_buf_detach(priv->buf, priv->attach);

        dma_buf_put(priv->buf);

        kfree(priv);

        psPages->pvImplData = IMG_NULL;

        if(psPages->ppaPhysAddr != IMG_NULL)
        {
            IMG_BIGORSMALL_FREE(numPages * sizeof(psPages->ppaPhysAddr[0]), psPages->ppaPhysAddr);
            psPages->ppaPhysAddr = IMG_NULL;
        }
    }
}

static IMG_PHYSADDR CpuKmAddrToCpuPAddr(
    SYSMEM_Heap *  heap,
    IMG_VOID *     pvCpuKmAddr
)
{
    IMG_PHYSADDR ret = 0;
    if(virt_addr_valid(pvCpuKmAddr))
    {
        /* direct mapping of kernel addresses.
         * this works for kmalloc.
         */
        ret = virt_to_phys(pvCpuKmAddr);
    }
    else
    {
        /* walk the page table.
         * Works for ioremap, vmalloc, and kmalloc(GPF_DMA),
          but not, for some reason, kmalloc(GPF_KERNEL)
         */
        struct page * pg = vmalloc_to_page(pvCpuKmAddr);
        if(pg) {
            ret = page_to_phys(pg);
        }
        else {
            IMG_ASSERT(!"vmalloc_to_page failure");
        }
    }

        return ret;
}

static IMG_RESULT GetCpuKmAddr(
    SYSMEM_Heap *  heap,
    IMG_VOID **    ppvCpuKmAddr,
    IMG_HANDLE     hPagesHandle
)
{
    SYSMEMU_sPages *  psPages = hPagesHandle;

    /* The buffer has to be imported first */
    IMG_ASSERT(psPages->pvCpuKmAddr != IMG_NULL);
    if(ppvCpuKmAddr && *ppvCpuKmAddr) {
        *ppvCpuKmAddr = psPages->pvCpuKmAddr;
    } else {
        return IMG_ERROR_INVALID_PARAMETERS;
    }
    return IMG_SUCCESS;
}

static int map_user(SYSMEMU_sPages *psPages, IMG_VOID *priv) {
    struct vm_area_struct *vma = priv;
    int i, offset, ret=0;

    for(i = 0, offset = 0;
        i < (vma->vm_end - vma->vm_start) / PAGE_SIZE;
        ++i, offset += PAGE_SIZE)
    {
        phys_addr_t pfn = psPages->ppaPhysAddr[i] >> PAGE_SHIFT;
        unsigned long start = vma->vm_start + offset;

        /*
         * On x86 remap_pfn_range will use the flags for
         * the kernel direct mapped memory (if any)
         * instead of the vm_page_prot flags which will override
         * our write-combining flags!
         * NOTE: We can use page->flags |= _PGMT_WC to override that (!?)
         */

#if (0)
//#ifdef CONFIG_X86
        /*
         * vm_insert_page() documentation (3.10.0) says:
         * "The page has to be a nice clean _individual_ kernel allocation",
         * but the  pages to be mapped by Felix.ko have non zero page_count(page)
         * so the mapping fails -> fallback here to remap_pfn_range()
         */
        ret = vm_insert_page(vma, start, pfn_to_page(pfn));
#else
        ret = remap_pfn_range(vma, start, pfn, PAGE_SIZE, vma->vm_page_prot);
#endif

        IMG_ASSERT(ret == 0);

        if (ret != 0)
            break;
    }

    return ret;
}

static IMG_VOID UpdateMemory(
    struct SYSMEM_Heap *    heap,
    IMG_HANDLE              hPagesHandle,
    SYSMEM_UpdateDirection  dir
)
{
    if(dir == CPU_TO_DEV) {
#ifdef CONFIG_ARM
        /* ARM Cortex write buffer needs to be synchronised before device can access it */
        dmb();
#else
        mb();
#endif
    }
    return;
}

static SYSMEM_Ops dmabuf_ops = {
        .FreePages = FreePages,

        .GetCpuKmAddr = GetCpuKmAddr,
        .CpuKmAddrToCpuPAddr = CpuKmAddrToCpuPAddr,

        .ImportPages = ImportPages,
        .UpdateMemory = UpdateMemory,
        .MapUser = map_user
};

IMG_RESULT SYSMEMKM_AddDMABufMemory(
    SYSDEVU_sInfo *sysdev,
    SYS_eMemPool *peMemPool
)
{
    IMG_RESULT ui32Result;
    SYS_eMemPool memPool;

    ui32Result = SYSMEMU_AddMemoryHeap(&dmabuf_ops, sysdev, IMG_TRUE, IMG_NULL, &memPool);
    IMG_ASSERT(IMG_SUCCESS == ui32Result);
    if (IMG_SUCCESS != ui32Result)
    {
        return ui32Result;
    }

    *peMemPool = memPool;

    return IMG_SUCCESS;
}
IMGVIDEO_EXPORT_SYMBOL(SYSMEMKM_AddDMABufMemory)
