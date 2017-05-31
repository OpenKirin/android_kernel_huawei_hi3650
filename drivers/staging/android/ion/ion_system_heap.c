/*
 * drivers/staging/android/ion/ion_system_heap.c
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

#include <asm/page.h>
#include <linux/dma-mapping.h>
#include <linux/err.h>
#include <linux/highmem.h>
#include <linux/mm.h>
#include <linux/scatterlist.h>
#include <linux/seq_file.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/sizes.h>
#include <linux/hisi/ion-iommu.h>
#include <linux/hisi/page_tracker.h>

#include "ion.h"
#include "ion_priv.h"

#ifdef CONFIG_HISI_SMARTPOOL_OPT
#include "hisi/hisi_ion_smart_pool.h"
#endif

/*for pclin*/
/*lint -save -e732 -e713 -e794 -e846 -e514 -e866 -e30*/
/*lint -save -e84 -e737*/

static gfp_t high_order_gfp_flags = (GFP_USER | __GFP_NOWARN |
				     __GFP_NORETRY) & ~__GFP_WAIT;
static gfp_t low_order_gfp_flags  = GFP_USER;

static const unsigned int orders[] = {8, 4, 0};
#define NUM_ORDERS ARRAY_SIZE(orders)

static int order_to_index(unsigned int order)
{
	int i;

	for (i = 0; i < NUM_ORDERS; i++)
		if (order == orders[i])
			return i;
	BUG();
	return -1;
}

static inline unsigned int order_to_size(int order)
{
	return PAGE_SIZE << order;
}

struct ion_system_heap {
	struct ion_heap heap;

#ifdef CONFIG_HISI_SMARTPOOL_OPT
	struct ion_smart_pool *smart_pool;
#endif

	struct ion_page_pool *uncached_pools[NUM_ORDERS];
	struct ion_page_pool *cached_pools[NUM_ORDERS];
};

static struct page *alloc_buffer_page(struct ion_system_heap *heap,
				      struct ion_buffer *buffer,
				      unsigned long order)
{
	bool cached = ion_buffer_cached(buffer);
	struct ion_page_pool *pool;
	struct page *page;

	if (!cached)
		pool = heap->uncached_pools[order_to_index(order)];
	else
		pool = heap->cached_pools[order_to_index(order)];

	page = ion_page_pool_alloc(pool);

	if (!page) {
		if (!order) {
			pr_err("%s: Out of mem, ion_page_pool_alloc failed!\n",
				 __func__);
		}
		return NULL;
		/*change here: flush cache has already done by caller*/
		/*ion_pages_sync_for_device(NULL, page, PAGE_SIZE << order,
						DMA_BIDIRECTIONAL);*/
	}

#ifdef CONFIG_HISI_KERNELDUMP
	SetPageMemDump(page);
#endif

	return page;
}

static void free_buffer_page(struct ion_system_heap *heap,
			     struct ion_buffer *buffer, struct page *page)
{
	struct ion_page_pool *pool;
	unsigned int order = compound_order(page);
	bool cached = ion_buffer_cached(buffer);

#ifdef CONFIG_HISI_SMARTPOOL_OPT
	if (ion_smart_is_graphic_buffer(buffer) && (heap->smart_pool)) {
		if (0 == ion_smart_pool_free(heap->smart_pool, page))
			return;
	}
#endif

	if (!cached)
		pool = heap->uncached_pools[order_to_index(order)];
	else
		pool = heap->cached_pools[order_to_index(order)];

	if (order == 0) {
		ion_page_pool_free_immediate(pool, page);
		return;
	}

	if (buffer->private_flags & ION_PRIV_FLAG_SHRINKER_FREE)
		ion_page_pool_free_immediate(pool, page);
	else
		ion_page_pool_free(pool, page);
}


static struct page *alloc_largest_available(struct ion_system_heap *heap,
					    struct ion_buffer *buffer,
					    unsigned long size,
					    unsigned int max_order)
{
	struct page *page;
	int i;

	for (i = 0; i < NUM_ORDERS; i++) {
		if (size < order_to_size(orders[i]))
			continue;
		if (max_order < orders[i])
			continue;

		page = alloc_buffer_page(heap, buffer, orders[i]);
		if (!page)
			continue;

		return page;
	}

	return NULL;
}

static int ion_system_heap_allocate(struct ion_heap *heap,
				     struct ion_buffer *buffer,
				     unsigned long size, unsigned long align,
				     unsigned long flags)
{
	struct ion_system_heap *sys_heap = container_of(heap,
							struct ion_system_heap,
							heap);
	struct sg_table *table;
	struct scatterlist *sg;
	struct list_head pages;
	struct page *page, *tmp_page;
	int i = 0;
	unsigned long size_remaining = PAGE_ALIGN(size);
	unsigned int max_order = orders[0];

	if (size / PAGE_SIZE > totalram_pages / 2) {
		pr_err("%s: (size/PAGE_SIZE > totalram_pages/2)\n", __func__);
		return -ENOMEM;
	}

	INIT_LIST_HEAD(&pages);

#ifdef CONFIG_HISI_SMARTPOOL_OPT
	if (ion_smart_is_graphic_buffer(buffer) && (sys_heap->smart_pool)) {
		while (size_remaining > 0) {
			page = ion_smart_pool_allocate(sys_heap->smart_pool,
						size_remaining, max_order);
			if (!page)
				break;

			list_add_tail(&page->lru, &pages);
			size_remaining -= PAGE_SIZE << compound_order(page);
			max_order = compound_order(page);
			i++;
			page_tracker_set_type(page, TRACK_ION, max_order);
		}

		max_order = orders[0];
	}
#endif

	while (size_remaining > 0) {
		page = alloc_largest_available(sys_heap, buffer, size_remaining,
						max_order);
		if (!page) {
			pr_err("%s: alloc largest avaliable failed!\n",
					__func__);
			goto free_pages;
		}

#ifdef CONFIG_HISI_SMARTPOOL_OPT
		if (ion_smart_is_graphic_buffer(buffer))
			ion_smart_sp_init_page(page);
#endif
		list_add_tail(&page->lru, &pages);
		size_remaining -= PAGE_SIZE << compound_order(page);
		max_order = compound_order(page);
		i++;
		page_tracker_set_type(page, TRACK_ION, max_order);
	}
	table = kmalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table)
		goto free_pages;

	if (sg_alloc_table(table, i, GFP_KERNEL))
		goto free_table;

	sg = table->sgl;
	list_for_each_entry_safe(page, tmp_page, &pages, lru) {
		sg_set_page(sg, page, PAGE_SIZE << compound_order(page), 0);
		sg = sg_next(sg);
		list_del(&page->lru);
	}

	buffer->priv_virt = table;

#ifdef CONFIG_HISI_SMARTPOOL_OPT
	if (ion_smart_is_graphic_buffer(buffer))
		ion_smart_pool_wakeup_process();
#endif
	return 0;

free_table:
	kfree(table);
free_pages:
	list_for_each_entry_safe(page, tmp_page, &pages, lru)
		free_buffer_page(sys_heap, buffer, page);
	return -ENOMEM;
}

static void ion_system_heap_free(struct ion_buffer *buffer)
{
	struct ion_system_heap *sys_heap = container_of(buffer->heap,
							struct ion_system_heap,
							heap);
	struct sg_table *table = buffer->sg_table;
/* now we only have cached buffer */
#if 0
	bool cached = ion_buffer_cached(buffer);
#endif
	struct scatterlist *sg;
	LIST_HEAD(pages);
	int i;
/* zero buffer when allocate */
#if 0
	/* uncached pages come from the page uncached_pools,
		zero them before returningfor security purposes
		(other allocations are zerod at alloc time */
	if (!cached && !(buffer->private_flags & ION_PRIV_FLAG_SHRINKER_FREE))
		ion_heap_buffer_zero(buffer);
#endif

	for_each_sg(table->sgl, sg, table->nents, i)
		free_buffer_page(sys_heap, buffer, sg_page(sg));
	sg_free_table(table);
	kfree(table);
}

static struct sg_table *ion_system_heap_map_dma(struct ion_heap *heap,
						struct ion_buffer *buffer)
{
	return buffer->priv_virt;
}

static void ion_system_heap_unmap_dma(struct ion_heap *heap,
				      struct ion_buffer *buffer)
{
}

static int ion_system_heap_shrink(struct ion_heap *heap, gfp_t gfp_mask,
					int nr_to_scan)
{
	struct ion_page_pool *uncached_pool;
	struct ion_page_pool *cached_pool;
	struct ion_system_heap *sys_heap;
	int nr_total = 0;
	int i, nr_freed;
	int only_scan = 0;

	sys_heap = container_of(heap, struct ion_system_heap, heap);

	if (!nr_to_scan)
		only_scan = 1;

	for (i = 0; i < NUM_ORDERS; i++) {
		uncached_pool = sys_heap->uncached_pools[i];
		cached_pool = sys_heap->cached_pools[i];

		if (only_scan) {
#ifdef CONFIG_HISI_SMARTPOOL_OPT
			nr_total += ion_smart_pool_shrink(
						sys_heap->smart_pool,
						sys_heap->smart_pool->pools[i],
						gfp_mask,
						nr_to_scan);
#endif
			nr_total += ion_page_pool_shrink(uncached_pool,
							 gfp_mask,
							 nr_to_scan);

			nr_total += ion_page_pool_shrink(cached_pool,
							 gfp_mask,
							 nr_to_scan);
		} else {

#ifdef CONFIG_HISI_SMARTPOOL_OPT
			nr_freed = ion_smart_pool_shrink(
						sys_heap->smart_pool,
						sys_heap->smart_pool->pools[i],
						gfp_mask,
						nr_to_scan);
			nr_to_scan -= nr_freed;
			nr_total += nr_freed;
			if (nr_to_scan <= 0)
				break;
#endif
			nr_freed = ion_page_pool_shrink(uncached_pool,
							gfp_mask,
							nr_to_scan);
			nr_to_scan -= nr_freed;
			nr_total += nr_freed;
			if (nr_to_scan <= 0)
				break;
			nr_freed = ion_page_pool_shrink(cached_pool,
							gfp_mask,
							nr_to_scan);
			nr_to_scan -= nr_freed;
			nr_total += nr_freed;
			if (nr_to_scan <= 0)
				break;
		}
	}

	return nr_total;
}

static void ion_system_heap_buffer_zero(struct ion_buffer *buffer)
{
	ion_heap_buffer_zero(buffer);
}

static struct ion_heap_ops system_heap_ops = {
	.allocate = ion_system_heap_allocate,
	.free = ion_system_heap_free,
	.map_dma = ion_system_heap_map_dma,
	.unmap_dma = ion_system_heap_unmap_dma,
	.map_kernel = ion_heap_map_kernel,
	.unmap_kernel = ion_heap_unmap_kernel,
	.map_user = ion_heap_map_user,
	.map_iommu = ion_heap_map_iommu,
	.unmap_iommu = ion_heap_unmap_iommu,
	.buffer_zero = ion_system_heap_buffer_zero,
	.shrink = ion_system_heap_shrink,
};

static int ion_system_heap_debug_show(struct ion_heap *heap, struct seq_file *s,
				      void *unused)
{

	struct ion_system_heap *sys_heap = container_of(heap,
							struct ion_system_heap,
							heap);
	int i;

	for (i = 0; i < NUM_ORDERS; i++) {
		struct ion_page_pool *pool = sys_heap->uncached_pools[i];

		seq_printf(s, "%d order %u highmem pages in uncached pool = %lu total\n",
			   pool->high_count, pool->order,
			   (PAGE_SIZE << pool->order) * pool->high_count);
		seq_printf(s, "%d order %u lowmem pages in uncached pool = %lu total\n",
			   pool->low_count, pool->order,
			   (PAGE_SIZE << pool->order) * pool->low_count);
	}

	for (i = 0; i < NUM_ORDERS; i++) {
		struct ion_page_pool *pool = sys_heap->cached_pools[i];

		seq_printf(s, "%d order %u highmem pages in cached pool = %lu total\n",
			   pool->high_count, pool->order,
			   (PAGE_SIZE << pool->order) * pool->high_count);
		seq_printf(s, "%d order %u lowmem pages in cached pool = %lu total\n",
			   pool->low_count, pool->order,
			   (PAGE_SIZE << pool->order) * pool->low_count);
	}

#ifdef CONFIG_HISI_SMARTPOOL_OPT
	if (sys_heap->smart_pool) {
		ion_smart_pool_debug_show_total(s, sys_heap->smart_pool);

		for (i = 0; i < NUM_ORDERS; i++) {
			struct ion_page_pool *pool =
				sys_heap->smart_pool->pools[i];

			seq_printf(s, "%d order %u highmem pages in smart pool = %lu total\n",
				pool->high_count, pool->order,
				(PAGE_SIZE << pool->order) * pool->high_count);
			seq_printf(s, "%d order %u lowmem pages in smart pool = %lu total\n",
				pool->low_count, pool->order,
				(PAGE_SIZE << pool->order) * pool->low_count);
		}
	}
#endif

	return 0;
}

void ion_system_heap_destroy_pools(struct ion_page_pool **pools)
{
	int i;

	for (i = 0; i < NUM_ORDERS; i++)
		if (pools[i])
			ion_page_pool_destroy(pools[i]);
}

int ion_system_heap_create_pools(struct ion_page_pool **pools,
		bool graphic_buffer_flag)
{
	int i;

	for (i = 0; i < NUM_ORDERS; i++) {
		struct ion_page_pool *pool;
		gfp_t gfp_flags = low_order_gfp_flags;

		if (orders[i] >= 4)
			gfp_flags = high_order_gfp_flags;

		if (orders[i] == 8)
			gfp_flags = high_order_gfp_flags | __GFP_NO_KSWAPD;

		pool = ion_page_pool_create(gfp_flags, orders[i],
					graphic_buffer_flag);
		if (!pool)
			goto err_create_pool;
		pools[i] = pool;
	}

	return 0;

err_create_pool:
	ion_system_heap_destroy_pools(pools);
	return -ENOMEM;
}

struct ion_heap *ion_system_heap_create(struct ion_platform_heap *unused)
{
	struct ion_system_heap *heap;
	bool  graphic_buffer_flag = false;

	heap = kzalloc(sizeof(struct ion_system_heap), GFP_KERNEL);
	if (!heap)
		return ERR_PTR(-ENOMEM);

	heap->heap.ops = &system_heap_ops;
	heap->heap.type = ION_HEAP_TYPE_SYSTEM;
	heap->heap.flags = ION_HEAP_FLAG_DEFER_FREE;

	if (ion_system_heap_create_pools(heap->uncached_pools,
			graphic_buffer_flag))
		goto free_heap;

	if (ion_system_heap_create_pools(heap->cached_pools,
			graphic_buffer_flag))
		goto destroy_uncached_pools;

#ifdef CONFIG_HISI_SMARTPOOL_OPT
	heap->smart_pool = ion_smart_pool_create();
	if (!heap->smart_pool) {
		pr_err("%s: create smart_pool failed!\n", __func__);
		goto destroy_pools;
	}
#endif

	heap->heap.debug_show = ion_system_heap_debug_show;

	return &heap->heap;

#ifdef CONFIG_HISI_SMARTPOOL_OPT
destroy_pools:
	ion_system_heap_destroy_pools(heap->cached_pools);
#endif

destroy_uncached_pools:
	ion_system_heap_destroy_pools(heap->uncached_pools);

free_heap:
	kfree(heap);
	return ERR_PTR(-ENOMEM);
}

void ion_system_heap_destroy(struct ion_heap *heap)
{
	struct ion_system_heap *sys_heap = container_of(heap,
							struct ion_system_heap,
							heap);
	int i;

	for (i = 0; i < NUM_ORDERS; i++) {
		ion_page_pool_destroy(sys_heap->uncached_pools[i]);
		ion_page_pool_destroy(sys_heap->cached_pools[i]);
#ifdef CONFIG_HISI_SMARTPOOL_OPT
		if (sys_heap->smart_pool)
			ion_page_pool_destroy(sys_heap->smart_pool->pools[i]);
#endif
	}

#ifdef CONFIG_HISI_SMARTPOOL_OPT
	kfree(sys_heap->smart_pool);
	sys_heap->smart_pool = NULL;
#endif

	kfree(sys_heap);
}

static int ion_system_contig_heap_allocate(struct ion_heap *heap,
					   struct ion_buffer *buffer,
					   unsigned long len,
					   unsigned long align,
					   unsigned long flags)
{
	int order = get_order(len);
	struct page *page;
	struct sg_table *table;
	unsigned long i;
	int ret;

	if (align > (PAGE_SIZE << order))
		return -EINVAL;

	page = alloc_pages(low_order_gfp_flags | __GFP_ZERO, order);
	if (!page)
		return -ENOMEM;

	split_page(page, order);

	len = PAGE_ALIGN(len);
	for (i = len >> PAGE_SHIFT; i < (1 << order); i++)
		__free_page(page + i);

	table = kmalloc(sizeof(struct sg_table), GFP_KERNEL);
	if (!table) {
		ret = -ENOMEM;
		goto free_pages;
	}

	ret = sg_alloc_table(table, 1, GFP_KERNEL);
	if (ret)
		goto free_table;

	sg_set_page(table->sgl, page, len, 0);

	buffer->priv_virt = table;

	ion_pages_sync_for_device(NULL, page, len, DMA_BIDIRECTIONAL);

	return 0;

free_table:
	kfree(table);

free_pages:
	for (i = 0; i < len >> PAGE_SHIFT; i++)
		__free_page(page + i);

	return ret;
}

static void ion_system_contig_heap_free(struct ion_buffer *buffer)
{
	struct sg_table *table = buffer->priv_virt;
	struct page *page = sg_page(table->sgl);
	unsigned long pages = PAGE_ALIGN(buffer->size) >> PAGE_SHIFT;
	unsigned long i;

	for (i = 0; i < pages; i++)
		__free_page(page + i);
	sg_free_table(table);
	kfree(table);
}

static int ion_system_contig_heap_phys(struct ion_heap *heap,
				       struct ion_buffer *buffer,
				       ion_phys_addr_t *addr, size_t *len)
{
	struct sg_table *table = buffer->priv_virt;
	struct page *page = sg_page(table->sgl);
	*addr = page_to_phys(page);
	*len = buffer->size;
	return 0;
}

static struct sg_table *ion_system_contig_heap_map_dma(struct ion_heap *heap,
						struct ion_buffer *buffer)
{
	return buffer->priv_virt;
}

static void ion_system_contig_heap_unmap_dma(struct ion_heap *heap,
					     struct ion_buffer *buffer)
{
}

static struct ion_heap_ops kmalloc_ops = {
	.allocate = ion_system_contig_heap_allocate,
	.free = ion_system_contig_heap_free,
	.phys = ion_system_contig_heap_phys,
	.map_dma = ion_system_contig_heap_map_dma,
	.unmap_dma = ion_system_contig_heap_unmap_dma,
	.map_kernel = ion_heap_map_kernel,
	.unmap_kernel = ion_heap_unmap_kernel,
	.map_user = ion_heap_map_user,
};

struct ion_heap *ion_system_contig_heap_create(struct ion_platform_heap *unused)
{
	struct ion_heap *heap;

	heap = kzalloc(sizeof(struct ion_heap), GFP_KERNEL);
	if (!heap)
		return ERR_PTR(-ENOMEM);
	heap->ops = &kmalloc_ops;
	heap->type = ION_HEAP_TYPE_SYSTEM_CONTIG;
	return heap;
}

void ion_system_contig_heap_destroy(struct ion_heap *heap)
{
	kfree(heap);
}
/*lint -restore*/
