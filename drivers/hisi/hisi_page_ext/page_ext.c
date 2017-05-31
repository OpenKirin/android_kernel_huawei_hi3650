#include <linux/mm.h>
#include <linux/mmzone.h>
#include <linux/bootmem.h>
#include <linux/memblock.h>
#include <linux/page_ext.h>
#include <linux/memory.h>

static unsigned long free_unused_pgext(unsigned long start_pfn, unsigned long end_pfn)
{
	struct page *start_pg, *end_pg;
	struct page_ext *start_ext, *end_ext;
	unsigned long start, end;

	/*
	 * Convert start_pfn/end_pfn to a struct page pointer.
	 */
	start_pg = pfn_to_page(start_pfn - 1) + 1;
	end_pg = pfn_to_page(end_pfn - 1) + 1;

	start_ext = lookup_page_ext(start_pg);
	end_ext = lookup_page_ext(end_pg);
	if (!start_ext || !end_ext) {
		pr_err("in free_unused_pgext end_ext or end_ext invalid\n");
		return 0;
	}
	/*
	 * Convert to physical addresses, and round start upwards and end
	 * downwards.
	 */
	start = (unsigned long)(PAGE_ALIGN(__pa(start_ext)));/*lint !e648 !e834*/
	end = (unsigned long)(__pa(end_ext) & PAGE_MASK);/*lint !e648 !e834*/

	/*
	 * If there are free pages between these, free the section of the
	 * memmap array.
	 */
	if (start >= end)
		return 0;

	free_bootmem(start, end - start);

	return (end - start);
}

unsigned long  _free_unused_page_ext(void)
{
	unsigned long start, prev_end = 0;
	struct memblock_region *reg;
	unsigned long size = 0;

	for_each_memblock(memory, reg) {
		start = __phys_to_pfn(reg->base);

		/*
		 * If we had a previous bank, and there is a space between the
		 * current bank and the previous, free it.
		 */
		if (prev_end && prev_end < start) {
			size += free_unused_pgext(prev_end, start);
			pr_info("+++start 0x%lx prev_end 0x%lx\n", start, prev_end);
		}

		/*
		 * Align up here since the VM subsystem insists that the
		 * memmap entries are valid from the bank end aligned to
		 * MAX_ORDER_NR_PAGES.
		 */
		prev_end = ALIGN(__phys_to_pfn(reg->base + reg->size),
				 MAX_ORDER_NR_PAGES);
	}

	return size;
}
