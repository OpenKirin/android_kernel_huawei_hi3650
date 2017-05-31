/*
 * drivers/staging/android/ion/ion_dma_pool_heap.c
 *
 * Copyright (C) 2011 Google, Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#define pr_fmt(fmt) "[dma_pool: ]" fmt

#include <linux/spinlock.h>
#include <linux/dma-mapping.h>
#include <linux/err.h>
#include <linux/genalloc.h>
#include <linux/io.h>
#include <linux/ion.h>
#include <linux/workqueue.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/time.h>
#include <linux/of_reserved_mem.h>
#include <linux/dma-contiguous.h>
#include <linux/cma.h>
#include <linux/atomic.h>
#include <linux/hisi/hisi_ion.h>

#include "ion.h"
#include "ion_priv.h"

/**
 * Why pre-allocation size is 32MB?
 * 1.The time of 32MB memory cma releasing is short
 * 2.32MB memory is larger then iris's memory size
 */

#define PREALLOC_CNT     (32UL * SZ_1M / PAGE_SIZE)
#define DMA_CAMERA_WATER_MARK (100 * SZ_1M)
#define PREALLOC_ALIGN   (13U)
static void pre_alloc_wk_func(struct work_struct *work);

struct ion_dma_pool_heap {
	struct ion_heap heap;
	struct gen_pool *pool;
	struct device	*dev;
	ion_phys_addr_t base;
	size_t size;
	atomic64_t alloc_size;
};
struct cma *ion_dma_camera_cma;
static struct ion_dma_pool_heap *ion_dma_camera_heap;
static DECLARE_WORK(ion_pre_alloc_wk, pre_alloc_wk_func);

void ion_register_dma_camera_cma(void *p)
{
	struct cma *cma = (struct cma *)p;
	if (cma
	    && cma_get_size(cma) > DMA_CAMERA_WATER_MARK){
		ion_dma_camera_cma = cma;
		pr_info("register_dma_camera_cma is ok\n");
	}
}

void ion_clean_dma_camera_cma(void)
{
	ion_phys_addr_t addr;
	long long size = 0;
#ifdef ION_DMA_POOL_DEBUG
	int free_count = 0;
	unsigned long t_ns = 0;
	ktime_t t1 = ktime_get();
#endif
	if (!ion_dma_camera_heap)
		return;

	if (!atomic64_sub_and_test(0L, &ion_dma_camera_heap->alloc_size)) {
		size = atomic64_read(&ion_dma_camera_heap->alloc_size);/*lint !e529 !e438*/
		pr_err("camera daemon heap remain %lld\n", size);
	}

	while (!!(addr = gen_pool_alloc(ion_dma_camera_heap->pool, PAGE_SIZE))) {/*lint !e820*/
		memset(phys_to_virt(addr), 0x0, PAGE_SIZE);
		if (ion_dma_camera_cma
		    && !cma_release(ion_dma_camera_cma,  phys_to_page(addr), 1))
			pr_err("cma release failed\n");
#ifdef ION_DMA_POOL_DEBUG
		else
			free_count++;
#endif
	}
#ifdef ION_DMA_POOL_DEBUG
	t_ns = ktime_to_ns(ktime_sub(ktime_get(), t1));
	pr_err("cma free size %lu B time is %lu us\n",
		free_count * PAGE_SIZE, t_ns / 1000UL);
#endif
}

static void pre_alloc_wk_func(struct work_struct *work)
{
	struct page *page = NULL;
	struct page *t_page = NULL;
	ion_phys_addr_t addr;
	int k;
#ifdef ION_DMA_POOL_DEBUG
	unsigned long t_ns = 0;
	ktime_t t1 = ktime_get();
#endif
	if (!ion_dma_camera_heap)
		return;

	page = cma_alloc(ion_dma_camera_cma, PREALLOC_CNT, PREALLOC_ALIGN);/*lint !e838*/
	if (page) {
		addr = page_to_phys(page);
		memset(phys_to_virt(addr), 0x0, PREALLOC_CNT * PAGE_SIZE);
		gen_pool_free(ion_dma_camera_heap->pool,
			      page_to_phys(page),
			      PREALLOC_CNT * PAGE_SIZE);
#ifdef CONFIG_HISI_KERNELDUMP
		t_page = page;
		for (k = 0; k < (int)PREALLOC_CNT; k++) {
			SetPageMemDump(t_page);
			t_page++;
		}
#endif

#ifdef ION_DMA_POOL_DEBUG
		t_ns = ktime_to_ns(ktime_sub(ktime_get(), t1));
		pr_err("cma alloc size %lu B time is %lu us\n",
			PREALLOC_CNT * PAGE_SIZE, t_ns / 1000);
#endif
		return;
	}
	ion_clean_dma_camera_cma();
}/*lint !e715*/

static ion_phys_addr_t ion_dma_pool_allocate(struct ion_heap *heap,
				      unsigned long size,
				      unsigned long align)
{
	struct ion_dma_pool_heap *dma_pool_heap =
		container_of(heap, struct ion_dma_pool_heap, heap);/*lint !e826*/


	unsigned long offset = gen_pool_alloc(dma_pool_heap->pool, size);
	if (!offset) {
		if (heap->id == ION_CAMERA_DAEMON_HEAP_ID)
			schedule_work(&ion_pre_alloc_wk);
		return (ion_phys_addr_t)-1L;
	}
	atomic64_add(size, &dma_pool_heap->alloc_size);/*lint !e713*/
	return offset;
}/*lint !e715*/

static void ion_dma_pool_free(struct ion_heap *heap, ion_phys_addr_t addr,
		       unsigned long size)
{
	struct ion_dma_pool_heap *dma_pool_heap =
		container_of(heap, struct ion_dma_pool_heap, heap);/*lint !e826*/

	if (addr == (ion_phys_addr_t)-1L)
		return;

	atomic64_sub(size, &dma_pool_heap->alloc_size);/*lint !e713*/

	if (heap->id == ION_CAMERA_DAEMON_HEAP_ID) {
		memset(phys_to_virt(addr), 0x0, size);
		if (ion_dma_camera_cma
		    && (!cma_release(ion_dma_camera_cma,  phys_to_page(addr), size / PAGE_SIZE)))/*lint !e712 !e747*/
			pr_err("cma release failed\n");
		if (atomic64_sub_and_test(0L, &dma_pool_heap->alloc_size))
			ion_clean_dma_camera_cma();
	}
	else
		gen_pool_free(dma_pool_heap->pool, addr, size);
}

static int ion_dma_pool_heap_phys(struct ion_heap *heap,
				  struct ion_buffer *buffer,
				  ion_phys_addr_t *addr, size_t *len)
{
	struct sg_table *table = buffer->priv_virt;
	struct page *page = sg_page(table->sgl);
	ion_phys_addr_t paddr = PFN_PHYS(page_to_pfn(page));

	*addr = paddr;
	*len = buffer->size;
	return 0;
}/*lint !e715*/

static int ion_dma_pool_heap_allocate(struct ion_heap *heap,
				      struct ion_buffer *buffer,
				      unsigned long size, unsigned long align,
				      unsigned long flags)
{
	struct sg_table *table;
	ion_phys_addr_t paddr;
	int ret;

	if (align > PAGE_SIZE)
		return -EINVAL;

	table = kmalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table)
		return -ENOMEM;
	ret = sg_alloc_table(table, 1, GFP_KERNEL);
	if (ret)
		goto err_free;

	paddr = ion_dma_pool_allocate(heap, size, align);
	if (paddr == (ion_phys_addr_t)-1L) {
		ret = -ENOMEM;
		goto err_free_table;
	}

	sg_set_page(table->sgl, pfn_to_page(PFN_DOWN(paddr)), (unsigned int)size, (unsigned int)0);
	buffer->priv_virt = table;

	return 0;

err_free_table:
	sg_free_table(table);
err_free:
	kfree(table);
	return ret;
}/*lint !e715*/

static void ion_dma_pool_heap_free(struct ion_buffer *buffer)
{
	struct ion_heap *heap = buffer->heap;
	struct sg_table *table = buffer->priv_virt;
	struct page *page = sg_page(table->sgl);
	ion_phys_addr_t paddr = PFN_PHYS(page_to_pfn(page));

	/*the sync has done by caller, we don't need to do any more */
	ion_heap_buffer_zero(buffer);

	if (ion_buffer_cached(buffer))
		dma_sync_sg_for_device(NULL, table->sgl, (int)table->nents,
				       DMA_BIDIRECTIONAL);

	ion_dma_pool_free(heap, paddr, buffer->size);
	sg_free_table(table);
	kfree(table);
}

static struct sg_table *ion_dma_pool_heap_map_dma(struct ion_heap *heap,
						  struct ion_buffer *buffer)
{
	return buffer->priv_virt;
}/*lint !e715*/

static void ion_dma_pool_heap_unmap_dma(struct ion_heap *heap,
					struct ion_buffer *buffer)
{
}/*lint !e715*/

static void ion_dma_pool_heap_buffer_zero(struct ion_buffer *buffer)
{
	ion_heap_buffer_zero(buffer);
}

static struct ion_heap_ops dma_pool_heap_ops = {
	.allocate = ion_dma_pool_heap_allocate,
	.free = ion_dma_pool_heap_free,
	.phys = ion_dma_pool_heap_phys,
	.map_dma = ion_dma_pool_heap_map_dma,
	.unmap_dma = ion_dma_pool_heap_unmap_dma,
	.map_user = ion_heap_map_user,
	.map_kernel = ion_heap_map_kernel,
	.unmap_kernel = ion_heap_unmap_kernel,
	.map_iommu = ion_heap_map_iommu,
	.unmap_iommu = ion_heap_unmap_iommu,
	.buffer_zero = ion_dma_pool_heap_buffer_zero,
};/*lint !e785*/

static struct ion_heap *ion_dynamic_dma_pool_heap_create(struct ion_platform_heap *heap_data)
{
	struct ion_dma_pool_heap *dma_pool_heap =
				kzalloc(sizeof(struct ion_dma_pool_heap), GFP_KERNEL);

	dma_pool_heap->heap.ops = &dma_pool_heap_ops;
	dma_pool_heap->heap.type = ION_HEAP_TYPE_DMA_POOL;
	dma_pool_heap->heap.flags = ION_HEAP_FLAG_DEFER_FREE;
	if (!ion_dma_camera_cma)
		goto alloc_err;
	dma_pool_heap->base = cma_get_base(ion_dma_camera_cma);
	dma_pool_heap->size = cma_get_size(ion_dma_camera_cma);
	dma_pool_heap->pool = gen_pool_create(PAGE_SHIFT, -1);
	if (!dma_pool_heap->pool)
		goto alloc_err;
	if (gen_pool_add(dma_pool_heap->pool,
			 dma_pool_heap->base,
			 dma_pool_heap->size,
			 -1))
		goto pool_create_err;
	if (!gen_pool_alloc(dma_pool_heap->pool, dma_pool_heap->size))
		goto pool_create_err;

	atomic64_set(&dma_pool_heap->alloc_size, 0);

	ion_dma_camera_heap = dma_pool_heap;

	heap_data->size = dma_pool_heap->size;
	heap_data->base = dma_pool_heap->base;

	return &dma_pool_heap->heap;

pool_create_err:
	gen_pool_destroy(dma_pool_heap->pool);
alloc_err:
	kfree(dma_pool_heap);

	return ERR_PTR(-ENOMEM);/*lint !e747*/
}/*lint !e715*/

struct ion_heap *ion_static_dma_pool_heap_create(struct ion_platform_heap *heap_data)/*lint !e715*/
{
	struct ion_dma_pool_heap *dma_pool_heap;
	int ret, k;
	struct device *dev;
	struct page *page, *t_page;
	size_t size;

	dev = (struct device *)heap_data->priv;
	if (of_reserved_mem_device_init(dev))
		return ERR_PTR(-ENOMEM);/*lint !e747*/

	size = cma_get_size(dev_get_cma_area(dev));
	page = dma_alloc_from_contiguous(dev, size >> PAGE_SHIFT, 0);
	if (!page)
		return ERR_PTR(-ENOMEM);/*lint !e747*/

#ifdef CONFIG_HISI_KERNELDUMP
		t_page = page;
		for (k = 0; k < (int)(size >> PAGE_SHIFT); k++) {
			SetPageMemDump(t_page);
			t_page++;
		}
#endif

	ion_pages_sync_for_device(NULL, page, size, DMA_BIDIRECTIONAL);

	ret = ion_heap_pages_zero(page, size, pgprot_writecombine(PAGE_KERNEL));
	if (ret)
		return ERR_PTR(ret);/*lint !e747*/

	dma_pool_heap = kzalloc(sizeof(struct ion_dma_pool_heap), GFP_KERNEL);
	if (!dma_pool_heap)
		return ERR_PTR(-ENOMEM);/*lint !e747*/

	dma_pool_heap->pool = gen_pool_create(PAGE_SHIFT, -1);
	if (!dma_pool_heap->pool) {
		kfree(dma_pool_heap);
		return ERR_PTR(-ENOMEM);/*lint !e747*/
	}

	dma_pool_heap->base = page_to_phys(page);
	dma_pool_heap->size = size;
	gen_pool_add(dma_pool_heap->pool, dma_pool_heap->base, dma_pool_heap->size,
		     -1);
	dma_pool_heap->heap.ops = &dma_pool_heap_ops;
	dma_pool_heap->heap.type = ION_HEAP_TYPE_DMA_POOL;
	dma_pool_heap->heap.flags = ION_HEAP_FLAG_DEFER_FREE;
	dma_pool_heap->dev = dev;
	atomic64_set(&dma_pool_heap->alloc_size, 0);

	heap_data->size = size;
	heap_data->base = page_to_phys(page);

	return &dma_pool_heap->heap;
}

struct ion_heap *ion_dma_pool_heap_create(struct ion_platform_heap *heap_data)/*lint !e715*/
{
	if (heap_data->id == ION_CAMERA_DAEMON_HEAP_ID)
		return ion_dynamic_dma_pool_heap_create(heap_data);
	else
		return ion_static_dma_pool_heap_create(heap_data);

}

static void ion_dynamic_dma_pool_heap_destroy(struct ion_heap *heap)
{
	struct ion_dma_pool_heap *dma_pool_heap =
	     container_of(heap, struct  ion_dma_pool_heap, heap);/*lint !e826*/
	kfree(dma_pool_heap);
	dma_pool_heap = NULL;
}/*lint !e438*/

void ion_static_dma_pool_heap_destroy(struct ion_heap *heap)/*lint !e438*/
{
	struct ion_dma_pool_heap *dma_pool_heap =
	     container_of(heap, struct  ion_dma_pool_heap, heap);/*lint !e826*/
	size_t size = dma_pool_heap->size;
	struct page *page = phys_to_page(dma_pool_heap->base);

	gen_pool_destroy(dma_pool_heap->pool);
	dma_release_from_contiguous(dma_pool_heap->dev, page, (int)(size >> PAGE_SHIFT));
	kfree(dma_pool_heap);
	dma_pool_heap = NULL;
}/*lint !e438*/

void ion_dma_pool_heap_destroy(struct ion_heap *heap)/*lint !e438*/
{
	if (heap->id == ION_CAMERA_DAEMON_HEAP_ID)
		ion_dynamic_dma_pool_heap_destroy(heap);
	else
		ion_static_dma_pool_heap_destroy(heap);
}
