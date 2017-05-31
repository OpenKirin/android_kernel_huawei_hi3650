/*
 * hisilicon efuse driver, hisi_atfisp.c
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 */

//ISP_LINT
/*lint -e750
 -esym(750,*)*/
#include <linux/init.h>
#include <linux/module.h>
#include <linux/regulator/consumer.h>
#include <linux/platform_device.h>
#include <linux/miscdevice.h>
#include <linux/device.h>
#include <linux/clk.h>
#include <linux/of.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/dma-mapping.h>
#include <linux/fcntl.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/scatterlist.h>
#include <linux/printk.h>
#include <linux/file.h>
#include <linux/kthread.h>
#include <linux/rproc_share.h>
#include <linux/remoteproc.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/genalloc.h>
#include <linux/hisi/hisi-iommu.h>
#include <linux/hisi/ion-iommu.h>
#include <linux/mutex.h>
#include <linux/iommu.h>
#include <linux/compiler.h>
#include <linux/cpumask.h>
#include <asm/uaccess.h>
#include <asm/compiler.h>
#include <global_ddr_map.h>
#include "teek_client_id.h"
#include <linux/hisi/hisi_load_image.h>
#include <linux/hisi/kirin_partition.h>
#include <linux/platform_data/remoteproc-hisi.h>
#include "hisi_partition.h"
#include "partition.h"

#define MAX_SIZE    64
#define ISP_ATF_CPU 1
#define ISP_RESERVED_BASE (HISI_RESERVED_ISP_BOOT_PHYMEM_BASE)
#define DEVICE_PATH  "/dev/block/bootdevice/by-name/"

#define A7_REQUEST_ADDR         0xD0000000
#define A7_REQUEST_BUF_SIZE     0x96000
#define A7_REQUEST_BUF_NUM      16
#define A7_ISPDTS_ADDR          0xC8000000
#define A7_ISPDTS_SIZE          0x02000000
#define A7_DTS_BUF_SIZE         0x200000
#define A7_DTS_BUF_NUM          16
#define A7_GET_OTP_ADDR         0xD0A00000
#define A7_CAPABILITY_ADDR      0xD0B00000
#define A7_ACQUIRE_ADDR         0xD0C00000
#define A7_CALIBRATION_ADDR     0xD0D00000
#define A7_TONEMAP_ADDR         0xD0E00000
#define A7_MAP_BUFFER_ADDR      0xD1000000
#define A7_MAP_DMAP_BUFFER_ADDR 0xCA000000
#define A7_MAP_BUFFER_SIZE      0xF000000

#define ISP_FN_SET_PARAMS   (0xC500AB00)
#define ISP_FN_A7_INIT      (0xC500AB22)
#define ISP_FN_A7_EXIT      (0xC500AB23)
#define ISP_FN_A7_MAP       (0xC500AB24)
#define ISP_FN_A7_UNMAP     (0xC500AB25)
#define ISP_FN_SET_NONSEC   (0xC500AB26)
#define ISP_FN_DISRESET_A7  (0xC500AB27)

/* VivoBus Regs Base & Offset */
#define REG_BASE_VIVOBUS_PHY         (0xE86D0000)
#define ISP_RD_QOS_PRIORITY          (0x8)
#define ISP_RD_QOS_MODE              (0xC)
#define ISP_WR_QOS_PRIORITY          (0x88)
#define ISP_WR_QOS_MODE              (0x8C)
#define A7T0VIVOBUS_RD_QOS_PRIORITY  (0x108)
#define A7T0VIVOBUS_RD_QOS_MODE      (0x10C)
#define A7T0VIVOBUS_WR_QOS_PRIORITY  (0x188)
#define A7T0VIVOBUS_WR_QOS_MODE      (0x18C)
#define ISP1_RD_QOS_PRIORITY          (0x208)
#define ISP1_RD_QOS_MODE              (0x20C)
#define ISP1_WR_QOS_PRIORITY          (0x288)
#define ISP1_WR_QOS_MODE              (0x28C)

#define QOS_FIX_MODE 0x0
#define QOS_BYPASS_MODE 0x2
#define QOS_PRIO_1 0x0
#define QOS_PRIO_2 0x101
#define QOS_PRIO_3 0x202
#define QOS_PRIO_3_PLUS_RD 0x302
#define QOS_PRIO_4 0x303

#define AP_A7_SHARE_OFFSET      (0x1000)

/* pclint coverity--not used */
#define ISP_FN_ISP_INIT         (0xC500AB11)
#define ISP_FN_ISP_EXIT         (0xC500AB12)

enum mapType
{
    MAP_TYPE_DYNAMIC = 0,
    MAP_TYPE_STATIC,
    MAP_TYPE_MAX,
};

struct hisi_isp_ops {
#define UNINITIAL   0
	unsigned int refs_ispsrt_subsys;
    unsigned int refs_isp_module;
    unsigned int refs_a7_module;
    unsigned int refs_dts;
    unsigned int refs_rsc;
    unsigned int refs_fw;
	unsigned int refs_setparams;
	int (*ispsrtup)(void);
	int (*ispsrtdn)(void);
	int (*ispinit)(void);
	int (*ispexit)(void);
	int (*a7init)(void);
	int (*a7exit)(void);
    int (*loaddts)(void);
    int (*loadrsc)(void);
    int (*loadfw)(void);
	int (*setparams)(unsigned int, unsigned int, unsigned int);
};

struct hisi_a7mapping_s {
    unsigned int a7va;
    unsigned int size;
    unsigned int prot;
    unsigned int reserve;
    unsigned long a7pa;
    void *apva;
};

struct hisi_atfshrdmem_s {
    struct hisi_a7mapping_s a7mapping[MAXA7MAPPING];
};

enum HISP_CLK_TYPE {
    ISP_A7_CLK = 0,
    ISP_FUNC_CLK = 1,
    ISP_CLK_MAX
};

struct hisi_atfisp_s {
    struct device *device;
    unsigned int boardid;
    void *atfshrd_vaddr;
    unsigned long long atfshrd_paddr;
    void *rsctable_vaddr;
    unsigned long long rsctable_paddr;
    struct hisi_atfshrdmem_s *shrdmem;
    struct regulator *ispsrt_supply;
    struct clk *ispclk[ISP_CLK_MAX];
    unsigned int ispclk_value[ISP_CLK_MAX];
    struct hisi_isp_ops *ispops;
    struct task_struct *secisp_kthread;
    wait_queue_head_t secisp_wait;
    bool secisp_wake;
    struct mutex pwrlock;
    struct mutex isp_iova_pool_mutex;
    unsigned long long phy_pgd_base;
    struct iommu_domain *domain;
    struct gen_pool *isp_iova_pool;
    unsigned long isp_iova_start;
    unsigned long isp_iova_size;
    struct ion_handle *handle;
    struct ion_client *client;
    unsigned int a7va_a7ispmem;
    unsigned int ispva_a7ispmem;
    void *ap_dyna_array;
    struct hisi_a7mapping_s *ap_dyna;
    int map_req_flag;
	int map_dts_flag;
	struct rproc_shared_para *sec_isp_share_para;
} atfisp_dev;

struct map_type_info {
    unsigned int va;
    unsigned int size;
};

struct map_sglist_s {
    unsigned long long addr;
    unsigned int size;
};

unsigned int map_type_info[MAP_TYPE_MAX];
extern u64 get_isprdr_addr(void);

noinline int atfd_hisi_service_isp_smc(u64 funcid, u64 arg0, u64 arg1, u64 arg2)
{
       asm volatile (
            __asmeq("%0", "x0")
            __asmeq("%1", "x1")
            __asmeq("%2", "x2")
            __asmeq("%3", "x3")
            "smc    #0\n"
        : "+r" (funcid)
        : "r" (arg0), "r" (arg1), "r" (arg2));

    return (int)funcid;
}

struct regulator *get_isp_regulator(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    if (NULL == dev->ispsrt_supply)
        return NULL;

    return dev->ispsrt_supply;
}

static void isp_iova_pool_destroy(struct gen_pool *pool)
{
    gen_pool_destroy(pool);
}

/*lint -save -e838 */
static unsigned long hisi_isp_alloc_iova(struct gen_pool *pool,
        unsigned long size, unsigned long align)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    unsigned long iova = 0;

    mutex_lock(&dev->isp_iova_pool_mutex);

	iova = gen_pool_alloc(pool, size);
    if(!iova){
        pr_err("hisi isp iommu gen_pool_alloc failed!\n");
        mutex_unlock(&dev->isp_iova_pool_mutex);
        return 0;
    }

    if(align > ((unsigned long)1 << (unsigned long)(pool->min_alloc_order)))/*lint !e571 */
        pr_info("hisi iommu domain cant align to 0x%lx\n", align);
    mutex_unlock(&dev->isp_iova_pool_mutex);
    return iova;
}

static void hisi_isp_free_iova(struct gen_pool *pool,
        unsigned long iova, size_t size)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    mutex_lock(&dev->isp_iova_pool_mutex);
    gen_pool_free(pool, iova, size);
    mutex_unlock(&dev->isp_iova_pool_mutex);
}
static struct gen_pool *isp_iova_pool_setup(unsigned long start,
        unsigned long size, unsigned int align)
{
    struct gen_pool *pool = NULL;
    int ret = 0;

    pool = gen_pool_create((int)(order_base_2(align)), -1);/*lint !e666 !e835 !e747 !e516 !e866 !e712 */
    if(!pool){
        pr_err("Create isp gen pool failed!\n");
        return NULL;
    }
    /* iova start should not be 0, because return
       0 when alloc iova is considered as error */
    if(!start)
        pr_err("iova start should not be 0!\n");
    ret = gen_pool_add(pool, start, size, -1);
    if(ret){
        pr_err("Gen pool add failed!\n");
        isp_iova_pool_destroy(pool);
        return NULL;
    }

    return pool;
}
/*lint -restore */
int hisp_getsglist(void *listmem, void **vaddr, int size)
{
    struct scatterlist *sg;
    struct sg_table *table;
    dma_addr_t dma_addr = 0;
    struct page **pages, **tmppages;
    int npages = 0, ret, i;
    unsigned long long *plist = listmem;
    pgprot_t pageprot = PAGE_KERNEL;

    if ((npages = PAGE_ALIGN(size) / PAGE_SIZE) <= 0) {
        pr_err("[%s] Failed : npages.0x%x, size.0x%x\n", __func__, npages, size);
        return -EINVAL;
    }

    if ((table = kzalloc(sizeof(struct sg_table), GFP_KERNEL)) == NULL) {
        pr_err("[%s] Failed : kzalloc.%p\n", __func__, table);
        return -ENOMEM;
    }

    if ((ret = sg_alloc_table(table, npages, GFP_KERNEL)) != 0) {
        pr_err("[%s] Failed : sg_alloc_table.%d, table.%p, npages.%d\n", __func__, ret, table, npages);
        kfree(table);
        return -ENOMEM;
    }

    if ((pages = vmalloc(npages * sizeof(struct page *))) == NULL) {
        pr_err("[%s] Failed : vmalloc.%p\n", __func__, pages);
        sg_free_table(table);
        kfree(table);
        return -ENOMEM;
    }

    for (i = 0; i < npages; i ++)
        pages[i] = alloc_page(GFP_KERNEL | GFP_DMA | __GFP_ZERO);

    pageprot = pgprot_noncached(pageprot);
    if ((*vaddr = vmap(pages, npages, VM_MAP, pageprot)) == NULL) {
        pr_err("[%s] Failed : vmap.%p\n", __func__, *vaddr);
        sg_free_table(table);
        kfree(table);
        for (i = 0; i < npages; i ++){
            free_page((unsigned long)pages[i]);
        }
        vfree(pages);
        return -ENOMEM;
    }

    tmppages = pages;
    sg = table->sgl;
    while (sg) {
        struct page *page = *tmppages;
        sg_set_page(sg, page, PAGE_SIZE, 0);
        if ((dma_addr = sg_dma_address(sg)) == 0)
            dma_addr = sg_phys(sg);

        *plist = (unsigned long long)dma_addr;
        //pr_err("[%s] size.(0x%x, 0x%x), vmap.%p, dma_addr.0x%llx, tmppages.%p, *plist.(%p, 0x%llx, %p)\n", __func__, size, npages, *vaddr, dma_addr, tmppages, *plist, *plist, plist);
        plist ++;
        tmppages ++;
        sg = sg_next(sg);
    }
    sg_free_table(table);
    kfree(table);
    vfree(pages);

    return npages;
}

int hisp_unmap_a7ispmem(void *listmem, void **vaddr, int size)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    ion_unmap_iommu(dev->client, dev->handle);
    ion_free(dev->client, dev->handle);

    return 0;
}

void dump_mem(void *addr, int size)
{
    int i;
    pr_err("[%s] addr.%p, size.0x%x\n", __func__, addr, size);
    for (i = 0; i < size; i += 16)
        printk("0x%08x 0x%08x 0x%08x 0x%08x\n", __raw_readl(addr + i + 0), __raw_readl(addr + i + 4), __raw_readl(addr + i + 8), __raw_readl(addr + i + 12));
}

void *getsec_a7sharedmem_addr(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    return dev->shrdmem->a7mapping[A7SHARED].apva;
}

int get_ispops(struct hisi_isp_ops **ops)
{
	struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

	*ops = dev->ispops;

	return 0;
}

int hisp_jpeg_powerdn(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    int ret = 0;

    if (use_nonsec_isp()) {
        pr_info("%s: use_nonsec_isp.\n", __func__);
        return hisp_nsec_jpeg_powerdn();
    }

    if (!dev->ispops) {
        pr_err("[%s] Failed : ispops.%p\n", __func__, dev->ispops);
        return -EINVAL;
    }

    if (dev->ispops->ispexit)
        if ((ret = dev->ispops->ispexit()) < 0)
            pr_err("[%s] Failed : ispexit.%d\n", __func__, ret);

    if (dev->ispops->ispsrtdn)
        if ((ret = dev->ispops->ispsrtdn()) < 0)
            pr_err("[%s] Failed : ispsrtdn.%d\n", __func__, ret);

    return 0;
}
EXPORT_SYMBOL(hisp_jpeg_powerdn);

int hisp_a7isp_powerdn(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    int ret = 0;

    if (!dev->ispops) {
        pr_err("[%s] Failed : ispops.%p\n", __func__, dev->ispops);
        return -EINVAL;
    }

    if (dev->ispops->a7exit)
        if ((ret = dev->ispops->a7exit()) < 0)
            pr_err("[%s] Failed : a7exit.%d\n", __func__, ret);

	return (ret | hisp_jpeg_powerdn());
}

int hisp_jpeg_powerup(void)
{
	struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
	int ret = 0;

    if (use_nonsec_isp()) {
        pr_info("%s: use_nonsec_isp.\n", __func__);
        return hisp_nsec_jpeg_powerup();
    }

    if (!dev->ispops) {
        pr_err("[%s] Failed : ispops.%p\n", __func__, dev->ispops);
        return -EINVAL;
    }

	if (dev->ispops->ispsrtup) {
		if ((ret = dev->ispops->ispsrtup()) < 0) {
			pr_err("[%s] Failed : ispsrtup.%d\n", __func__, ret);
			return ret;
		}
	}

    if (dev->ispops->ispinit) {
        if ((ret = dev->ispops->ispinit()) < 0) {
            pr_err("[%s] Failed : ispinit.%d\n", __func__, ret);
            goto err_jpegup;
        }
    }

	return 0;

err_jpegup:
    if (dev->ispops->ispsrtdn)
        if (dev->ispops->ispsrtdn() < 0)
            pr_err("[%s] Failed : err_jpegup ispsrtdn\n", __func__);

	return ret;
}
EXPORT_SYMBOL(hisp_jpeg_powerup);

int hisp_a7isp_powerup(void)
{
	struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
	int ret = 0;

	if (!dev->ispops) {
		pr_err("[%s] Failed : ispops.%p\n", __func__, dev->ispops);
		return -EINVAL;
	}

	if ((ret = hisp_jpeg_powerup()) < 0) {
		pr_err("[%s] Failed : hisp_jpeg_powerup.%d\n", __func__, ret);
		return ret;
	}

    if (dev->ispops->a7init) {
        if ((ret = dev->ispops->a7init()) < 0) {
            pr_err("[%s] Failed : a7init.%d\n", __func__, ret);
            goto err_a7up;
        }
    }

	if (dev->ispops->loadfw) {
		if ((ret = dev->ispops->loadfw()) < 0) {
			pr_err("[%s] Failed : loadfw.%d\n", __func__, ret);
			goto err_loadfw;
		}
	}

	return 0;

err_loadfw:
    if (dev->ispops->a7exit)
        if (dev->ispops->a7exit() < 0)
            pr_err("[%s] Failed : err_loadfw a7exit\n", __func__);
err_a7up:
    if (hisp_jpeg_powerdn() < 0)
        pr_err("[%s] Failed : err_a7up hisp_jpeg_powerdn\n", __func__);

    return ret;
}

static int bsp_read_bin(const char *partion_name, unsigned int offset,
				unsigned int length, char *buffer)
{
	int ret          = -1;
	char *pathname   = NULL;
    unsigned long pathlen;
	struct file *fp;
	mm_segment_t fs;
	loff_t pos = 0;

	if ((NULL == partion_name) || (NULL == buffer)) {
		pr_err("partion_name(%p) or buffer(%p) is null", partion_name, buffer);
		return -1;
	}

    /*get resource*/
    pathlen = sizeof(DEVICE_PATH) + strnlen(partion_name, (unsigned long)PART_NAMELEN);
	pathname = kmalloc(pathlen, GFP_KERNEL);
	if (!pathname) {
		pr_err("pathname malloc failed\n");
		return -1;
	}

	ret = flash_find_ptn((const char *)partion_name, pathname);
	if (ret < 0) {
		pr_err("partion_name(%s) is not in partion table!\n", partion_name);
		goto error;
	}

	fp = filp_open(pathname, O_RDONLY, 0600);
	if (IS_ERR(fp)) {
		pr_err("filp_open(%s) failed", pathname);
		goto error;
	}

	ret = vfs_llseek(fp, offset, SEEK_SET);
	if (ret < 0) {
		pr_err("seek ops failed, ret %d", ret);
		goto error2;
	}

	fs = get_fs();
	set_fs(KERNEL_DS);

	pos = fp->f_pos;
	ret = vfs_read(fp, (char __user *)buffer, length, &pos);
	if (ret != length) {
		pr_err("read ops failed, ret=%d(len=%d)", ret, length);
		set_fs(fs);
		goto error2;
	}
	set_fs(fs);

    filp_close(fp, NULL);

    /*free resource*/
    if(NULL != pathname) {
       kfree(pathname);
       pathname = NULL;
    }

    return 0;

error2:
    filp_close(fp, NULL);

error:
    if(NULL != pathname) {
       kfree(pathname);
       pathname = NULL;
    }

    pr_err("failed");
    return -1;
}

typedef enum {
    ISPIMG_DTS = 0,
    ISPIMG_RSC,
    ISPIMG_FW,
    ISPIMG_MAX
} ISPIMG_TYPE_E;

typedef enum {
    ISPPWR_JPEGUP = 0,
    ISPPWR_JPEGDN,
    ISPPWR_A7UP,
    ISPPWR_A7DN,
    ISPPWR_MAX
} ISPPWR_TYPE_E;

struct hisi_isp_loadimg_s {
#define ISP_SECBASE     (0x1AC00000)
#define ISPDTS_BASE     (0x00000000)
#define ISPFW_BASE      (0x00010000 + ISP_SECBASE)
#define ISPRSC_BASE     (0x00003000)
#define ISPDTS_SIZE     (0x02000000)
#define ISPRSC_SIZE     (0x00001000)
#define ISPFW_SIZE      (0x00800000)
    unsigned int addr;
    unsigned int size;
    char *partition;
} loadimg[] = {
    {ISPDTS_BASE,   ISPDTS_SIZE,    "isp_dts"},
    {ISPRSC_BASE,   ISPRSC_SIZE,    "isp_firmware"},
    {ISPFW_BASE,    ISPFW_SIZE,     "isp_firmware"}
};

static int atfisp_loaddts(void)
{
    unsigned int offset;
	char *pname;

    pname = loadimg[ISPIMG_DTS].partition;
    offset = loadimg[ISPIMG_DTS].addr;
/*    size = dev->shrdmem->a7mapping[A7DTS].size;
    if ((ret = bsp_read_bin(pname, offset, size, dev->shrdmem->a7mapping[A7DTS].apva)) < 0) {
        pr_err("[%s] bsp_read_bin.%d\n", __func__, ret);
        return ret;
    }
*/
	return 0;
}

static int atfisp_loadrsctable(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    unsigned int offset, size;
    int ret = 0;
    char *pname;

    pname = loadimg[ISPIMG_RSC].partition;
    offset = loadimg[ISPIMG_RSC].addr;
    size = loadimg[ISPIMG_RSC].size;
    if ((ret = bsp_read_bin(pname, offset, size, dev->rsctable_vaddr)) < 0) {
        pr_err("[%s] bsp_read_bin.%d\n", __func__, ret);
        return ret;
    }

	return 0;
}

static int atfisp_loadfw(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    struct load_image_info loadinfo;
	int ret = 0;

    loadinfo.ecoretype      = ISP;
	loadinfo.image_addr     = loadimg[ISPIMG_FW].addr;
	loadinfo.image_size     = loadimg[ISPIMG_FW].size;
	loadinfo.partion_name   = loadimg[ISPIMG_FW].partition;
	pr_info("[%s] + %s.(0x%lx, 0x%x), init.%x\n", __func__, loadinfo.partion_name, loadinfo.image_addr, loadinfo.image_size, dev->ispops->refs_fw);
    if ((ret = bsp_load_and_verify_image(&loadinfo)) < 0) {
	    pr_err("[%s] Failed : bsp_load_and_verify_image.%d, %s.(0x%lx, 0x%x)\n", __func__, ret, loadinfo.partion_name, loadinfo.image_addr, loadinfo.image_size);
	    return ret;
	}

    dev->ispops->refs_fw++;

    pr_info("[%s] - bsp_load_and_verify_image.%d, %s.(0x%lx, 0x%x), init.%x\n", __func__, ret, loadinfo.partion_name, loadinfo.image_addr, loadinfo.image_size, dev->ispops->refs_fw);

	return 0;
}

#define HISP_PARAMS_SHRDLIST    (0xCCCE0000)
#define HISP_PARAMS_DUMP        (0xCCCE0006)

#define RSC_OFFSET              (0x00003000)
#define RSC_SIZE                (0x00001000)
#define LISTENTRY_SIZE          (0x00140000)

void atfisp_set_nonsec(void)
{
    atfd_hisi_service_isp_smc(ISP_FN_SET_NONSEC, 0, 0, 0);
}

void atfisp_disreset_a7(unsigned int remap_addr)
{
    atfd_hisi_service_isp_smc(ISP_FN_DISRESET_A7, remap_addr, 0, 0);
}

static int atfisp_setparams(unsigned int type, unsigned int param1, unsigned int param2)
{
	atfd_hisi_service_isp_smc(ISP_FN_SET_PARAMS, type, param1, param2);
	return 0;
}

static int ispa7_setclk_enable(struct hisi_atfisp_s *dev)
{
	int ret;

    if ((ret = clk_set_rate(dev->ispclk[ISP_A7_CLK], dev->ispclk_value[ISP_A7_CLK])) < 0) {
        pr_err("[%s] Failed: clk_set_rate.%d\n", __func__, ret);
        return ret;
    }

    if ((ret = clk_prepare_enable(dev->ispclk[ISP_A7_CLK])) < 0) {
        pr_err("[%s] Failed: clk_prepare_enable.%d\n", __func__, ret);
        return ret;
    }

    return 0;
}

static int ispfunc_setclk_enable(struct hisi_atfisp_s *dev)
{
    int ret;

    if ((ret = clk_set_rate(dev->ispclk[ISP_FUNC_CLK], dev->ispclk_value[ISP_FUNC_CLK])) < 0) {
        pr_err("[%s] Failed: clk_set_rate.%d\n", __func__, ret);
        return ret;
    }

    if ((ret = clk_prepare_enable(dev->ispclk[ISP_FUNC_CLK])) < 0) {
        pr_err("[%s] Failed: clk_prepare_enable.%d\n", __func__, ret);
        return ret;
    }

    return 0;
}

static void ispa7_clk_disable(struct hisi_atfisp_s *dev)
{
    clk_disable_unprepare(dev->ispclk[ISP_A7_CLK]);
}

static void ispfunc_clk_disable(struct hisi_atfisp_s *dev)
{
    clk_disable_unprepare(dev->ispclk[ISP_FUNC_CLK]);
}

static int atfispsrt_subsysup(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    int ret;

    pr_info("[%s] + refs.%d\n", __func__, dev->ispops->refs_ispsrt_subsys);

    if ((ret = ispfunc_setclk_enable(dev)) < 0) {
        pr_err("Failed: ispfunc_setclk_enable.%d\n", ret);
        return ret;
    }

    if ((ret = ispa7_setclk_enable(dev)) < 0) {
        pr_err("Failed: ispa7_setclk_enable.%d\n", ret);
        ispfunc_clk_disable(dev);
        return ret;
    }

    if ((ret = regulator_enable(dev->ispsrt_supply)) != 0) {
        pr_err("Failed: regulator_enable.%d\n", ret);
        goto err_clk;
    }

    dev->ispops->refs_ispsrt_subsys++;
    pr_info("[%s] - refs.%d\n", __func__, dev->ispops->refs_ispsrt_subsys);

    return 0;

err_clk:
    ispa7_clk_disable(dev);
    ispfunc_clk_disable(dev);

    return ret;
}

static int atfispsrt_subsysdown(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    int ret = 0;

    pr_info("[%s] + refs.%d\n", __func__, dev->ispops->refs_ispsrt_subsys);
    if ((ret = regulator_disable(dev->ispsrt_supply)) != 0)
        pr_err("Failed: regulator_disable.%d\n", ret);

    ispa7_clk_disable(dev);
    ispfunc_clk_disable(dev);

    dev->ispops->refs_ispsrt_subsys--;
    pr_info("[%s] - refs.%d\n", __func__, dev->ispops->refs_ispsrt_subsys);

    return 0;
}

static int atfisp_module_init(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    pr_info("[%s] + refs.%d\n", __func__, dev->ispops->refs_isp_module);
    atfd_hisi_service_isp_smc(ISP_FN_ISP_INIT, dev->phy_pgd_base, 0, 0);
    dev->ispops->refs_isp_module++;
    pr_info("[%s] - refs.%d\n", __func__, dev->ispops->refs_isp_module);

    return 0;
}

static int atfisp_module_exit(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    pr_info("[%s] + refs.%d\n", __func__, dev->ispops->refs_isp_module);
    atfd_hisi_service_isp_smc(ISP_FN_ISP_EXIT, 0, 0, 0);
    dev->ispops->refs_isp_module--;
    pr_info("[%s] - refs.%d\n", __func__, dev->ispops->refs_isp_module);

    return 0;
}

static int atfa7_module_init(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
	unsigned int isp_base;

    pr_info("[%s] + refs.%d\n", __func__, dev->ispops->refs_a7_module);
	isp_base = ISP_RESERVED_BASE;
    atfd_hisi_service_isp_smc(ISP_FN_A7_INIT, isp_base, 0, 0);
    dev->ispops->refs_a7_module++;
    pr_info("[%s] - refs.%d\n", __func__, dev->ispops->refs_a7_module);

    return 0;
}

static int atfa7_module_exit(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
	unsigned int type;

    pr_info("[%s] + refs.%d\n", __func__, dev->ispops->refs_a7_module);
	type = 1;
    atfd_hisi_service_isp_smc(ISP_FN_A7_EXIT, type, 0, 0);
    dev->ispops->refs_a7_module--;
    pr_info("[%s] - refs.%d\n", __func__, dev->ispops->refs_a7_module);

    return 0;
}

struct hisi_isp_ops atfisp_ops = {
	.ispsrtup   = atfispsrt_subsysup,
	.ispsrtdn   = atfispsrt_subsysdown,
    .ispinit    = atfisp_module_init,
    .ispexit    = atfisp_module_exit,
    .a7init     = atfa7_module_init,
    .a7exit     = atfa7_module_exit,
    .loaddts    = atfisp_loaddts,
    .loadrsc    = atfisp_loadrsctable,
    .loadfw     = atfisp_loadfw,
	.setparams  = atfisp_setparams,
};

int secisp_device_enable(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    if (!dev->secisp_kthread) {
        pr_err("[%s] Failed : secisp_kthread.%p\n", __func__, dev->secisp_kthread);
        return -ENXIO;
    }

    dev->secisp_wake = 1;
    wake_up(&dev->secisp_wait);

    return 0;
}

static void isp_a7_qos_cfg(void)
{
    void __iomem* vivobus_base;

    pr_info("[%s] +\n", __func__);
    vivobus_base = (void __iomem*)ioremap(REG_BASE_VIVOBUS_PHY, SZ_4K);
    if (vivobus_base == NULL) {
        pr_err("vivobus_base remap fail");
        return;
    }

    __raw_writel(QOS_PRIO_3,            (volatile void __iomem*)(vivobus_base + ISP_RD_QOS_PRIORITY));
    __raw_writel(QOS_BYPASS_MODE,            (volatile void __iomem*)(vivobus_base + ISP_RD_QOS_MODE));
    __raw_writel(QOS_PRIO_3,      (volatile void __iomem*)(vivobus_base + ISP_WR_QOS_PRIORITY));
    __raw_writel(QOS_BYPASS_MODE, (volatile void __iomem*)(vivobus_base + ISP_WR_QOS_MODE));
    __raw_writel(QOS_PRIO_4,      (volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_RD_QOS_PRIORITY));
    __raw_writel(QOS_FIX_MODE,    (volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_RD_QOS_MODE));
    __raw_writel(QOS_PRIO_4,      (volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_WR_QOS_PRIORITY));
    __raw_writel(QOS_FIX_MODE,    (volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_WR_QOS_MODE));
    __raw_writel(QOS_PRIO_3,            (volatile void __iomem*)(vivobus_base + ISP1_RD_QOS_PRIORITY));
    __raw_writel(QOS_BYPASS_MODE,            (volatile void __iomem*)(vivobus_base + ISP1_RD_QOS_MODE));
    __raw_writel(QOS_PRIO_3,      (volatile void __iomem*)(vivobus_base + ISP1_WR_QOS_PRIORITY));
    __raw_writel(QOS_BYPASS_MODE, (volatile void __iomem*)(vivobus_base + ISP1_WR_QOS_MODE));

    pr_info("QOS : ISP.rd.(prio.0x%x, mode.0x%x), ISP.wr.(prio.0x%x, mode.0x%x), A7.rd.(prio.0x%x, mode.0x%x), A7.wr.(prio.0x%x, mode.0x%x),ISP1.rd.(prio.0x%x, mode.0x%x), ISP1.wr.(prio.0x%x, mode.0x%x)\n",
    __raw_readl((volatile void __iomem*)(vivobus_base + ISP_RD_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + ISP_RD_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + ISP_WR_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + ISP_WR_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_RD_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_RD_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_WR_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + A7T0VIVOBUS_WR_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + ISP1_RD_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + ISP1_RD_QOS_MODE)),
    __raw_readl((volatile void __iomem*)(vivobus_base + ISP1_WR_QOS_PRIORITY)), __raw_readl((volatile void __iomem*)(vivobus_base + ISP1_WR_QOS_MODE)));

    iounmap(vivobus_base);
    vivobus_base = NULL;
    pr_info("[%s] -\n", __func__);
}

static int do_secisp_device_enable(void)
{
    int ret, err_ret;;

    if ((ret = atfispsrt_subsysup()) < 0) {
        pr_err("[%s] Failed : atfispsrt_subsysup.%d\n", __func__, ret);
        return ret;
    }

    if ((ret = atfisp_module_init()) < 0) {
        pr_err("[%s] Failed : atfisp_module_init.%d\n", __func__, ret);
        if ((err_ret = atfispsrt_subsysdown()) < 0)
            pr_err("[%s] Failed : atfispsrt_subsysdown.%d\n", __func__, err_ret);
        return ret;
    }

    isp_a7_qos_cfg();

    if ((ret = atfa7_module_init()) < 0) {
        pr_err("[%s] Failed : atfa7_module_init.%d\n", __func__, ret);
        if ((err_ret = atfisp_module_exit()) < 0)
            pr_err("[%s] Failed : atfisp_module_exit.%d\n", __func__, err_ret);
        if ((err_ret = atfispsrt_subsysdown()) < 0)
            pr_err("[%s] Failed : atfispsrt_subsysdown.%d\n", __func__, err_ret);
        return ret;
    }

    if ((ret = atfisp_loadfw()) < 0) {
        pr_err("[%s] Failed : atfisp_loadfw.%d\n", __func__, ret);
        if ((err_ret = atfa7_module_exit()) < 0)
            pr_err("[%s] Failed : atfa7_module_exit.%d\n", __func__, err_ret);
        if ((err_ret = atfisp_module_exit()) < 0)
            pr_err("[%s] Failed : atfisp_module_exit.%d\n", __func__, err_ret);
        if ((err_ret = atfispsrt_subsysdown()) < 0)
            pr_err("[%s] Failed : atfispsrt_subsysdown.%d\n", __func__, err_ret);
        return ret;
    }

    return 0;
}

int secisp_device_disable(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    struct cpumask cpu_mask;
    int ret, cpu_no;

    cpumask_clear(&cpu_mask);

    for (cpu_no = 1; cpu_no < 4; cpu_no++)
    {
        cpumask_set_cpu(cpu_no, &cpu_mask);
    }

    if(sched_setaffinity(current->pid, &cpu_mask) < 0)
    {
        pr_err("%s: Couldn't set affinity to cpu\n", __func__);
    }

    mutex_lock(&dev->pwrlock);
    if ((ret = atfa7_module_exit()) < 0)
        pr_err("[%s] Failed : atfa7_module_exit.%d\n", __func__, ret);

    if ((ret = atfisp_module_exit()) < 0)
        pr_err("[%s] Failed : atfisp_module_exit.%d\n", __func__, ret);

    if ((ret = atfispsrt_subsysdown()) < 0)
        pr_err("[%s] Failed : atfispsrt_subsysdown.%d\n", __func__, ret);
    mutex_unlock(&dev->pwrlock);

	if (sync_isplogcat() < 0)
	    pr_err("[%s] Failed: sync_isplogcat\n", __func__);

    return 0;
}

static ssize_t atfisp_show(struct device *, struct device_attribute *, char *);
static ssize_t atfisp_store(struct device *, struct device_attribute *, const char *, size_t);
static ssize_t regs_show(struct device *, struct device_attribute *, char *);
static ssize_t regs_store(struct device *, struct device_attribute *, const char *, size_t);
static ssize_t dump_show(struct device *, struct device_attribute *, char *);
static ssize_t dump_store(struct device *, struct device_attribute *, const char *, size_t);
static DEVICE_ATTR(atfisp, (S_IRUGO | S_IWUSR | S_IWGRP), atfisp_show, atfisp_store);
static DEVICE_ATTR(regs, (S_IRUGO | S_IWUSR | S_IWGRP), regs_show, regs_store);
static DEVICE_ATTR(dump, (S_IRUGO | S_IWUSR | S_IWGRP), dump_show, dump_store);

static struct miscdevice atf_ispdev = {
    .minor = 255,
    .name = "atf_ispdev",
};

static unsigned long get_a7shared_pa(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    return dev->atfshrd_paddr + AP_A7_SHARE_OFFSET;
}

static void *get_a7shared_va(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    return dev->atfshrd_vaddr + AP_A7_SHARE_OFFSET;
}

static unsigned long hisp_getreservemem(unsigned int etype, unsigned long paddr)
{
#define ISP_MEM_BASE		(0x1AC00000)
#define MEM_DATA_PGM     	(ISP_MEM_BASE)
#define MEM_TEXT_PA     	(ISP_MEM_BASE + 0x00010000)
#define MEM_DATA_PA     	(ISP_MEM_BASE + 0x00310000)
#define MEM_DATA_PTE     	(ISP_MEM_BASE + 0x00810000)
#define MEM_HEAP_PA      	(ISP_MEM_BASE + 0x00A10000)
#define REG_BASE		    (0xE8400000)
#define REG_IPCSEC		    (0xE896A000)
#define REG_IPCNSEC		    (0xE896B000)
#define REG_PCTRL		    (0xE8A09000)
#define REG_SCTRL		    (0xFFF0A000)
#define REG_PCFG		    (0xFFF35000)
#define REG_GIC		        (0xE82B0000)
#define REG_SYSC		    (0xFFF09000)
#define REG_UART		    (0xFFF32000)
#define REG_GPIO            (0xE8A0B000)
#define REG_GPIO25          (0xFFF0E000)
#define REG_IOC             (0xE896C000)
    unsigned long addr;

    switch(etype) {
        case A7BOOT:
            addr = MEM_TEXT_PA;
            break;
        case A7TEXT:
            addr = MEM_TEXT_PA;
            break;
        case A7PGM:
            addr = MEM_DATA_PGM;
            break;
        case A7PTE:
            addr = MEM_DATA_PTE;
            break;
        case A7DATA:
            addr = MEM_DATA_PA;
            break;
        case A7HEAP:
            addr = MEM_HEAP_PA;
            break;
        case A7REGISP:
            addr = REG_BASE;
            break;
        case A7REGIPCS:
            addr = REG_IPCSEC;
            break;
        case A7REGIPCNS:
            addr = REG_IPCNSEC;
            break;
        case A7REGPCTRL:
            addr = REG_PCTRL;
            break;
        case A7REGSCTRL:
            addr = REG_SCTRL;
            break;
        case A7REGPCFG:
            addr = REG_PCFG;
            break;
        case A7REGGIC:
            addr = REG_GIC;
            break;
        case A7REGSYSC:
            addr = REG_SYSC;
            break;
        case A7REGUART:
            addr = REG_UART;
            break;
        case A7REGGPIO:
            addr = REG_GPIO;
            break;
        case A7REGGPIO25:
            addr = REG_GPIO25;
            break;
        case A7REGIOC:
            addr = REG_IOC;
            break;
        case A7VQ:
        case A7VRING0:
        case A7VRING1:
            addr = paddr;
            break;
        case A7RDR:
            addr = get_isprdr_addr();
            pr_info("[%s] A7RDR.0x%lx\n", __func__, addr);
            break;
        case A7SHARED:
            addr = get_a7shared_pa();
            pr_info("[%s] A7SHARED.0x%lx\n", __func__, addr);
            break;
        default:
            pr_err("[%s] Failed : etype.0x%x\n", __func__, etype);
            return 0;
    }

    return addr;
}

int hisp_meminit(unsigned int etype, unsigned long paddr)
{
    const char *propname[] = {
        "a7-vaddr-boot",
        "a7-vaddr-text",
        "a7-vaddr-data",
        "a7-vaddr-pgm",
        "a7-vaddr-pte",
        "a7-vaddr-rdr",
        "a7-vaddr-shrd",
        "a7-vaddr-vq",
        "a7-vaddr-vr0",
        "a7-vaddr-vr1",
        "a7-vaddr-heap",
        "a7-vaddr-a7dyna",
        "a7-vaddr-regisp",
        "a7-vaddr-regipcs",
        "a7-vaddr-regipcns",
        "a7-vaddr-regpctrl",
        "a7-vaddr-regsctrl",
        "a7-vaddr-regpcfg",
        "a7-vaddr-reggic",
        "a7-vaddr-regsysc",
        "a7-vaddr-reguart",
        "a7-vaddr-reggpio",
        "a7-vaddr-reggpio25",
        "a7-vaddr-regioc",
    };
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    struct device_node *np = dev->device->of_node;
    unsigned int offset = 0, size = 0;
    void *addr = NULL, *vaddr = NULL;
	int ret, index;

    if (!np) {
        pr_err("[%s] Failed : np.%p\n", __func__, np);
        return -EINVAL;	
    }

    if (etype >= MAXA7MAPPING) {
        pr_err("[%s] Failed : etype.(0x%x >= 0x%x)\n", __func__, etype, MAXA7MAPPING);
        return -EINVAL;	
    }

    if (dev->shrdmem == NULL) {
        pr_err("[%s] Failed : shrdmem.(%p = %p)\n", __func__, dev->shrdmem, dev->atfshrd_vaddr);
        return -ENOMEM;	
    }

    if((ret = of_property_read_u32_array(np, propname[etype], (unsigned int *)(&dev->shrdmem->a7mapping[etype]), 4)) < 0) {
        pr_err("[%s] Failed : propname.%s, of_property_read_u32_array.%d\n",
            __func__, propname[etype], ret);
        return -EINVAL;	
	}
    pr_info("[%s] propname.%s, of_property_read_u32_array.%d.(0x%x, 0x%x, 0x%x, 0x%x)\n", __func__, propname[etype], ret,
        dev->shrdmem->a7mapping[etype].a7va, dev->shrdmem->a7mapping[etype].size, dev->shrdmem->a7mapping[etype].prot, dev->shrdmem->a7mapping[etype].reserve);

    if (dev->shrdmem->a7mapping[etype].reserve) {
        dev->shrdmem->a7mapping[etype].a7pa = hisp_getreservemem(etype, paddr);
        if (etype ==  A7SHARED) {
            dev->shrdmem->a7mapping[etype].apva = get_a7shared_va();
        }
    } else {
        index = 4;
        if((ret = of_property_read_u32_index(np, propname[etype], index, &offset)) < 0) {
            pr_err("[%s] Failed : propname.%s, %d.of_property_read_u32_index.%d\n", __func__, propname[etype], index, ret);
            return -EINVAL;	
    	}

        index = 5;
        if((ret = of_property_read_u32_index(np, propname[etype], index, &size)) < 0) {
            pr_err("[%s] Failed : propname.%s, %d.of_property_read_u32_index.%d\n", __func__, propname[etype], index, ret);
            return -EINVAL;	
    	}

        dev->shrdmem->a7mapping[etype].a7pa = dev->atfshrd_paddr + offset;
        addr = offset + dev->atfshrd_vaddr;
        pr_err("[%s] atfshrd_vaddr.0x%llx, addr.0x%p, vaddr.0x%p, offset.0x%x, size.0x%x\n", __func__, (long long unsigned int)dev->atfshrd_vaddr, addr, vaddr, offset, size);
        switch (etype) {
            case A7DYNAMIC:
                dev->ap_dyna_array = addr;
                dev->ap_dyna = (struct hisi_a7mapping_s *)&dev->shrdmem->a7mapping[etype];
                pr_err("[%s] dyna_array.0x%p\n", __func__, dev->ap_dyna_array);
                break;
            default :
                if ((ret = hisp_getsglist(addr, &vaddr, size)) < 0) {
                    pr_err("[%s] hisp_getsglist.0x%p\n", __func__, vaddr);
                    return -ENOMEM;
                }
                dev->shrdmem->a7mapping[etype].apva = vaddr;
                pr_err("[%s] etype.0x%x, addr.%p, vaddr.%p, size.0x%x\n", __func__, etype, addr, vaddr, size);
                break;
        }
    }

    return 0;
}

int hisp_apisp_map(unsigned int *a7addr, unsigned int *ispaddr, unsigned int size)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    if ((dev->a7va_a7ispmem == 0) || (dev->ispva_a7ispmem == 0))
        return -EINVAL;	

    *a7addr = dev->a7va_a7ispmem;
    *ispaddr = dev->ispva_a7ispmem;
    pr_info("[%s] X a7va.(0x%x, 0x%x), ispva.(0x%x, 0x%x)\n", __func__, *a7addr, dev->a7va_a7ispmem, *ispaddr, dev->ispva_a7ispmem);

    return 0;
}
EXPORT_SYMBOL(hisp_apisp_map);

int hisp_apisp_unmap(void)
{
    return 0;
}
EXPORT_SYMBOL(hisp_apisp_unmap);

static int hisp_rsctablemem_init(struct hisi_atfisp_s *dev)
{
    dma_addr_t dma_addr = 0;

    if ((dev->rsctable_vaddr = dma_alloc_coherent(dev->device, RSC_SIZE, &dma_addr, GFP_KERNEL)) == NULL) {
        pr_err("[%s] rsctable_vaddr.0x%p\n", __func__, dev->rsctable_vaddr);
        return -ENOMEM;
    }
    dev->rsctable_paddr = (unsigned long long)dma_addr;

    pr_info("[%s] [A7RSC].paddr.0x%llx\n", __func__, dev->rsctable_paddr);

    return 0;
}

static int hisp_sharedmem_init(struct hisi_atfisp_s *dev)
{
    dma_addr_t dma_addr = 0;
    int ret;

    if ((dev->atfshrd_vaddr = hisi_fstcma_alloc(&dma_addr, LISTENTRY_SIZE, GFP_KERNEL)) == NULL) {
        pr_err("[%s] atfshrd_vaddr.0x%p\n", __func__, dev->atfshrd_vaddr);
        return -ENOMEM;
    }
    dev->atfshrd_paddr = (unsigned long long)dma_addr;
    dev->shrdmem = (struct hisi_atfshrdmem_s *)dev->atfshrd_vaddr;

    if ((ret = atfisp_setparams(HISP_PARAMS_SHRDLIST, dev->atfshrd_paddr, LISTENTRY_SIZE)) < 0) {
	    pr_err("[%s] atfisp_setparams.%d, (type.0x%x, atfshrd_paddr.(0x%llx >> 0x%llx))\n", __func__, ret, HISP_PARAMS_SHRDLIST, dev->atfshrd_paddr, (unsigned long long)dev->atfshrd_vaddr);
	    kfree(dev->atfshrd_vaddr);
	    return -ENODEV;
	}

	pr_info("[%s] atfisp_setparams.%d, (type.0x%x, atfshrd_paddr.(0x%llx >> 0x%llx))\n", __func__, ret, HISP_PARAMS_SHRDLIST, dev->atfshrd_paddr, (unsigned long long)dev->atfshrd_vaddr);

	return 0;
}


static int hisi_atf_getdts(struct platform_device *pdev)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    struct device *device = &pdev->dev;
    struct device_node *np = device->of_node;

    const char *clk_name[ISP_CLK_MAX];
    int ret, i;

    if (!np) {
        pr_err("[%s] Failed : np.%p.\n", __func__, np);
        return -ENODEV;
    }

    dev->ispsrt_supply = devm_regulator_get(device, "isp-srt");
    if (IS_ERR(dev->ispsrt_supply)) {
        pr_err("[%s] Failed : ISPSRT devm_regulator_get.%p\n", __func__, dev->ispsrt_supply);
        return -EINVAL;
    }

    if ((ret = of_property_read_string_array(np, "clock-names", clk_name, ISP_CLK_MAX)) < 0) {
        pr_err("[%s] Failed : of_property_read_string_array.%d, boardid.0x%x\n", __func__, ret, dev->boardid);
        return -EINVAL;
    }

    if ((ret = of_property_read_u32_array(np, "clock-value", (unsigned int *)(&dev->ispclk_value[0]), ISP_CLK_MAX)) < 0) {
        pr_err("[%s] Failed: of_property_read_u32_array.%d\n", __func__, ret);
        return -EINVAL;
    }

    if ((ret = of_property_read_u32(np, "isp-iova-start", (unsigned int *)(&dev->isp_iova_start))) < 0 ) {
        pr_err("Failed : isp-iova_addr.0x%lx of_property_read_u32.%d\n", dev->isp_iova_start, ret);
        return -EINVAL;
    }

    pr_info("isp-iova_addr.0x%lx of_property_read_u32.%d\n", dev->isp_iova_start, ret);

    if ((ret = of_property_read_u32(np, "isp-iova-size", (unsigned int *)(&dev->isp_iova_size))) < 0 ) {
        pr_err("Failed : isp-iova_size.0x%lx of_property_read_u32.%d\n", dev->isp_iova_size, ret);
        return -EINVAL;
    }

    pr_info("isp-iova_size.0x%lx of_property_read_u32.%d\n", dev->isp_iova_size, ret);

    for (i = 0; i < ISP_CLK_MAX; i ++) {
        dev->ispclk[i] = devm_clk_get(device, clk_name[i]);
        if (IS_ERR_OR_NULL(dev->ispclk[i])) {
            pr_err("[%s] Failed : ispclk.%s.%d.%li\n", __func__, clk_name[i], i, PTR_ERR(dev->ispclk[i]));
            return -EINVAL;
        }
        pr_info("[%s] ISP clock.%d.%s: %d M\n", __func__, i, clk_name[i], dev->ispclk_value[i]);
    }

    return 0;
}

void *get_rsctable(int *tablesz)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;

    *tablesz = RSC_SIZE;
    return dev->rsctable_vaddr;
}

void a7_map_set_pa_list(void *listmem, struct scatterlist *sg, unsigned int size)
{
    dma_addr_t dma_addr = 0;
    unsigned int len, set_size = 0;
    struct map_sglist_s *maplist = listmem;
    unsigned int last_counts = 0, last_len = 0;

    while (sg) {
        if ((dma_addr = sg_dma_address(sg)) == 0)
            dma_addr = sg_phys(sg);

        len = sg->length;
        if (len == 0) {
            pr_err("[%s] break len.0x%x\n", __func__, len);
            break;
        }
        set_size += len;
        if (set_size > size) {
            pr_err("[%s] break size.(0x%x > 0x%x), len.0x%x\n", __func__, set_size, size, len);
            break;
        }

        maplist->addr = (unsigned long long)dma_addr;
        maplist->size = len;
        if (last_len != len) {
            if (last_len != 0)
                pr_info("[%s] list.(0x%p + 0x%p), maplist.(0x%llx, 0x%x X 0x%x)\n", __func__, listmem, maplist, (unsigned long long)dma_addr, last_counts, last_len);
            last_counts = 1;
            last_len = len;
        } else {
            last_counts ++;
        }
        maplist++;
        sg = sg_next(sg);
    }

    pr_info("[%s] list.(0x%p + 0x%p), maplist.(0x%llx, 0x%x X 0x%x)\n", __func__, listmem, maplist, (unsigned long long)dma_addr, last_counts, last_len);
    pr_info("%s: size.0x%x == set_size.0x%x\n", __func__, size, set_size);
}
/*lint -save -e838 */
unsigned int a7_mmu_map(struct scatterlist *sgl, unsigned int size, unsigned int prot, unsigned int flag)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    unsigned int map_size = 0, map_prot;
    struct hisi_a7mapping_s *map_info = dev->ap_dyna;
    void *addr = dev->ap_dyna_array;
    unsigned long iova;

    if (size == 0) {
        pr_err("%s: invalid para, size == 0x%x.\n", __func__, size);
        return 0;
    }

    map_size = PAGE_ALIGN(size);

    if (prot == 0) {
        map_prot = map_info->prot;
    } else {
        map_prot = prot;    
        map_info->prot = map_prot;
    }

    switch(flag) {
        case MAP_TYPE_DYNAMIC:
            iova = hisi_isp_alloc_iova(dev->isp_iova_pool, (unsigned long)map_size, (unsigned long)0);
            if(iova == 0){
                pr_err("[%s] Failed : hisi_isp_alloc_iova iova.0x%lx\n", __func__,iova);
                return 0;
            }
            map_info->a7va = (unsigned int)iova;
            map_info->size = map_size;

            break;
        case MAP_TYPE_STATIC:
            map_info->a7va = A7_MAP_BUFFER_ADDR;
            map_info->size = size;

            if (size > A7_MAP_BUFFER_SIZE) {
                pr_err("%s: invalid para, size == 0x%x.\n", __func__, size);
                return 0;
            }

            break;
        default:
            pr_err("[%s] Failed : type.0x%x\n", __func__, flag);
            return 0;
    }
    pr_info("[%s] type.0x%x, a7va.0x%x, size.0x%x, map_size.0x%x, map_prot.0x%x\n", __func__,
                            flag, map_info->a7va, size, map_size, map_prot);
    a7_map_set_pa_list(addr, sgl, map_size);

    atfd_hisi_service_isp_smc((unsigned long long)ISP_FN_A7_MAP, (unsigned long long)0, (unsigned long long)0, (unsigned long long)0);
    return map_info->a7va;
}

void a7_mmu_unmap(unsigned int va, unsigned int size)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    struct hisi_a7mapping_s *map_info = dev->ap_dyna;
    unsigned int map_size;

    map_size = PAGE_ALIGN(size);/*lint !e50 */
    pr_info("%s: va = 0x%x, size = 0x%x, map_size = 0x%x\n", __func__, va, size, map_size);
    map_info->a7va = va;
    map_info->size = map_size;

    atfd_hisi_service_isp_smc(ISP_FN_A7_UNMAP, 0, 0, 0);

    if((dev->isp_iova_start <= map_info->a7va) && (map_info->a7va < (dev->isp_iova_start + dev->isp_iova_size)))
    {
        pr_info("[%s] map_info->a7va.0x%x map_info->size.0x%x\n", __func__, map_info->a7va, map_info->size);
        hisi_isp_free_iova(dev->isp_iova_pool, (unsigned long)map_info->a7va, (unsigned long)map_info->size);
    }
}
/*lint -restore */
int hisp_rsctable_init(void)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    int ret;

    pr_info("[%s] +\n", __func__);
    if (!dev->rsctable_vaddr) {
        pr_err("[%s] rsctable_vaddr.0x%p\n", __func__, dev->rsctable_vaddr);
        return -ENOMEM;
    }

    if ((ret = bsp_read_bin("isp_firmware", RSC_OFFSET, RSC_SIZE, dev->rsctable_vaddr)) < 0) {
        pr_err("[%s] bsp_read_bin.%d\n", __func__, ret);
        return ret;
    }

    pr_info("[%s] -\n", __func__);

    return 0;
}

static int secisp_work_fn(void *data)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    struct cpumask cpu_mask;
    int ret, cpu_no;

    pr_info("[%s] +\n", __func__);

    cpumask_clear(&cpu_mask);

    for (cpu_no = 1; cpu_no < 4; cpu_no++)
    {
        cpumask_set_cpu(cpu_no, &cpu_mask);
    }

    if(sched_setaffinity(current->pid, &cpu_mask) < 0)
    {
        pr_err("%s: Couldn't set affinity to cpu\n", __func__);
    }


    while (1) {
        if (kthread_should_stop())
            break;
        wait_event(dev->secisp_wait, dev->secisp_wake);
        mutex_lock(&dev->pwrlock);
        if ((ret = do_secisp_device_enable()) < 0) {
            pr_err("[%s] Failed : do_secisp_device_enable.%d.\n", __func__, ret);
        }
        mutex_unlock(&dev->pwrlock);
        dev->secisp_wake = 0;
    }
    pr_info("[%s] -\n", __func__);

    return 0;
}

void hisi_ispsec_share_para_set(void)
{
	struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
	isp_share_para = dev->sec_isp_share_para;
	pr_info("%s.%d: isp_share_para.%p, dev->sec_isp_share_para.%p, case.%u\n",
			__func__, __LINE__, isp_share_para, dev->sec_isp_share_para,
			hisi_isp_rproc_case_get());
}

int hisi_atfisp_probe(struct platform_device *pdev)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    struct iommu_domain_data *info = NULL;
    struct device *device = &pdev->dev;
    int ret = 0, index = 0;

    dev->map_req_flag               = 0;
	dev->map_dts_flag               = 0;
    dev->device                     = &pdev->dev;
    atfisp_ops.refs_ispsrt_subsys   = UNINITIAL;
    atfisp_ops.refs_isp_module      = UNINITIAL;
    atfisp_ops.refs_a7_module       = UNINITIAL;
    atfisp_ops.refs_dts             = UNINITIAL;
    atfisp_ops.refs_fw              = UNINITIAL;
    dev->ispops                     = &atfisp_ops;

    if ((ret = misc_register(&atf_ispdev)) != 0) {
        pr_err("[%s] Failed : misc_register.%d.\n", __func__, ret);
        return ret;
	}

    if ((ret = device_create_file(atf_ispdev.this_device, &dev_attr_atfisp)) != 0)
        pr_err("[%s] Faield : atfisp device_create_file.%d\n", __func__, ret);
    if ((ret = device_create_file(atf_ispdev.this_device, &dev_attr_regs)) != 0)
        pr_err("[%s] Faield : regs device_create_file.%d\n", __func__, ret);
    if ((ret = device_create_file(atf_ispdev.this_device, &dev_attr_dump)) != 0)
        pr_err("[%s] Faield : dump device_create_file.%d\n", __func__, ret);

    ret = hisi_atfisp_cma_alloc();
    if (0 != ret) {
        pr_err("%s: hisi_atfisp_cma_alloc failed, ret.%d\n", __func__, ret);
        return ret;
    }

    if ((ret = hisi_atf_getdts(pdev)) < 0)
        pr_err("[%s] Failed : hisi_atf_getdts.%d.\n", __func__, ret);

	if ((ret = hisp_sharedmem_init(dev)) < 0)
		pr_err("[%s] Failed : hisp_sharedmem_init.%d.\n", __func__, ret);

	if ((ret = hisp_rsctablemem_init(dev)) < 0)
		pr_err("[%s] Failed : hisp_rsctablemem_init.%d.\n", __func__, ret);

    for (index = 0; index < MAXA7MAPPING; index ++)
        if ((ret = hisp_meminit(index, 0)) < 0)
            pr_err("Failed : index.%d, hisp_meminit.%d\n", index, ret);

    isp_share_para = (struct rproc_shared_para *)dev->shrdmem->a7mapping[A7SHARED].apva;
	dev->sec_isp_share_para = isp_share_para;

    if ((dev->domain = iommu_domain_alloc(device->bus)) == NULL) {
        pr_err("[%s] Failed : iommu_domain_alloc.%p\n", __func__, dev->domain);
        return -ENODEV;
    }

    if ((ret = iommu_attach_device(dev->domain, device)) != 0) {
        iommu_domain_free(dev->domain);
        pr_err("[%s] Failed : iommu_attach_device.%d\n", __func__, ret);
        ret = -ENODEV;
        goto out;
    }
    
    if ((info = (struct iommu_domain_data *)dev->domain->priv) == NULL) {
		iommu_detach_device(dev->domain, device);
        iommu_domain_free(dev->domain);
        pr_err("[%s] Failed : info.%p\n",__func__, info);
        ret = -ENODEV;
        goto out;
    }
    dev->phy_pgd_base = info->phy_pgd_base;
    pr_info("[%s] info.iova.(0x%x, 0x%x) phy_pgd_base.0x%llx\n", __func__,
            info->iova_start,
            info->iova_size,
			dev->phy_pgd_base);
	iommu_detach_device(dev->domain, device);
	iommu_domain_free(dev->domain);

    mutex_init(&dev->isp_iova_pool_mutex);

    dev->isp_iova_pool =  isp_iova_pool_setup(dev->isp_iova_start, dev->isp_iova_size, 0x8000);
    if(dev->isp_iova_pool == NULL)
    {
        pr_err("[%s] Failed : isp_iova_pool.%p\n",__func__,dev->isp_iova_pool);
        ret = -ENOMEM;
        goto out;
    }
    pr_info("[%s] sucessfully : isp_iova_pool.%p\n",__func__,dev->isp_iova_pool);

    mutex_init(&dev->pwrlock);

    init_waitqueue_head(&dev->secisp_wait);
    dev->secisp_kthread = kthread_create(secisp_work_fn, NULL, "secispwork");
    if (IS_ERR(dev->secisp_kthread)) {
        iommu_domain_free(dev->domain);
        pr_err("[%s] Failed : kthread_create.%ld\n", __func__, PTR_ERR(dev->secisp_kthread));
        ret = -1;
        isp_iova_pool_destroy(dev->isp_iova_pool);
        dev->isp_iova_pool = NULL;
        goto out;
    }
    wake_up_process(dev->secisp_kthread);

    return 0;

out:
    hisi_atfisp_cma_free();

    return ret;
}

int hisi_atfisp_remove(struct platform_device *pdev)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
    if(dev->domain){
        iommu_domain_free(dev->domain);
        dev->domain = NULL;
    }

    hisi_atfisp_cma_free();
    return 0;
}

MODULE_DESCRIPTION("Hisilicon atfisp module");
MODULE_AUTHOR("chentao20@huawei.com");
MODULE_LICENSE("GPL");

/* For debug */
static int debug_ispsrtup(void)
{
    int ret;

    if ((ret = atfispsrt_subsysup()) < 0) {
        pr_err("[%s] Failed : atfispsrt_subsysup.%d\n", __func__, ret);
        return ret;
    }

    return 0;
}

static int debug_ispsrtdn(void)
{
    int ret;

    if ((ret = atfispsrt_subsysdown()) < 0)
        pr_err("[%s] Failed : atfispsrt_subsysdown.%d\n", __func__, ret);

    return 0;
}

static int debug_ispinit(void)
{
    int ret;

    if ((ret = atfispsrt_subsysup()) < 0) {
        pr_err("[%s] Failed : atfispsrt_subsysup.%d\n", __func__, ret);
        return ret;
    }

    if ((ret = atfisp_module_init()) < 0) {
        int err_ret;
        pr_err("[%s] Failed : atfisp_module_init.%d\n", __func__, ret);
        if ((err_ret = atfispsrt_subsysdown()) < 0)
            pr_err("[%s] Failed : atfisp_subsysdown.%d\n", __func__, err_ret);
        return ret;
    }

    return 0;
}

static int debug_ispexit(void)
{
    int ret;

    if ((ret = atfisp_module_exit()) < 0)
        pr_err("[%s] Failed : atfisp_module_exit.%d\n", __func__, ret);

    if ((ret = atfispsrt_subsysdown()) < 0)
        pr_err("[%s] Failed : atfispsrt_subsysdown.%d\n", __func__, ret);

    return 0;
}

static int debug_a7up(void)
{
    return secisp_device_enable();
}

static int debug_a7dn(void)
{
    return secisp_device_disable();
}

static int debug_rscup(void)
{
    int ret;

    if ((ret = hisp_rsctable_init()) < 0) {
        pr_err("[%s] Failed : hisp_rsctable_init.%d\n", __func__, ret);
        return ret;
    }

    return 0;
}

static int debug_rscdn(void)
{
    return 0;
}

struct isp_powerdebug_s {
    char pwrup_cmd[8];
    char pwrdn_cmd[8];
    int (*pwrup_handler)(void);
    int (*pwrdn_handler)(void);
    char info[32];
} pwrdbg[] = {
    {
	"up", "dn", debug_ispsrtup, debug_ispsrtdn, "ispsrt"}, {
	"up", "dn", debug_ispinit, debug_ispexit, "ispinit"}, {
	"ld", "de", atfisp_loaddts, NULL, "dts"}, {
	"ld", "de", atfisp_loadfw, NULL, "fw"}, {
	"up", "dn", debug_a7up, debug_a7dn, "a7"}, {
	"up", "dn", debug_rscup, debug_rscdn, "rsc"},};

static ssize_t atfisp_show(struct device *pdev,
			       struct device_attribute *attr, char *buf)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
	char *s = buf;

    s += snprintf(s, MAX_SIZE, "BoardID: 0x%x\n", dev->boardid);
    if (dev->ispops) {
        s += snprintf(s, MAX_SIZE, "Vote: ispsrt.%d\n", dev->ispops->refs_ispsrt_subsys);
        s += snprintf(s, MAX_SIZE, "Vote: initisp.%d\n", dev->ispops->refs_isp_module);
        s += snprintf(s, MAX_SIZE, "Vote: inita7.%d\n", dev->ispops->refs_a7_module);
        s += snprintf(s, MAX_SIZE, "Load: dts.%d\n", dev->ispops->refs_dts);
        s += snprintf(s, MAX_SIZE, "Load: fw.%d\n", dev->ispops->refs_fw);
        s += snprintf(s, MAX_SIZE, "Load: rsc.%d\n", dev->ispops->refs_rsc);
        s += snprintf(s, MAX_SIZE, "Load: setparams.%d\n", dev->ispops->refs_setparams);
    } else {
        s += snprintf(s, MAX_SIZE, "Vote: NULL point!!!\n");
    }

	return (s - buf);
}

static void atfisp_usage(void)
{
	int i = 0;

	pr_info("<Usage: >\n");
	for (i = 0; i < sizeof(pwrdbg) / sizeof(struct isp_powerdebug_s); i ++)
		pr_info("echo <%s>:<%s/%s> > atfisp\n", pwrdbg[i].info, pwrdbg[i].pwrup_cmd, pwrdbg[i].pwrdn_cmd);
}

static ssize_t atfisp_store(struct device *pdev,
				struct device_attribute *attr, const char *buf,
				size_t count)
{
    int i = 0, len = 0, flag = 1;
    char *p = NULL;

    p = memchr(buf, ':', count);
    len = p ? p - buf : count;

    for (i = 0; i < sizeof(pwrdbg) / sizeof(struct isp_powerdebug_s); i++) {
        if (!strncmp(buf, pwrdbg[i].info, len)) {
            p += 1;
			flag = 0;
            if (!strncmp(p, pwrdbg[i].pwrup_cmd,
                strlen(pwrdbg[i].pwrup_cmd)))
				pwrdbg[i].pwrup_handler();
            else if (!strncmp(p, pwrdbg[i].pwrdn_cmd,
                strlen(pwrdbg[i].pwrdn_cmd)))
				pwrdbg[i].pwrdn_handler();
            else
				flag = 1;
            break;
        }
    }

	if (flag)
		atfisp_usage();

    return count;
}

static ssize_t regs_show(struct device *pdev,
			       struct device_attribute *attr, char *buf)
{
    struct hisi_atfisp_s *dev = (struct hisi_atfisp_s *)&atfisp_dev;
	char *s = buf;

    s += snprintf(s, MAX_SIZE, "BoardID: 0x%x\n", dev->boardid);

	return (s - buf);
}

static ssize_t regs_store(struct device *pdev,
				struct device_attribute *attr, const char *buf,
				size_t count)
{
    return count;
}

void hisi_secisp_dump(void)
{
    atfisp_setparams(HISP_PARAMS_DUMP, 1, 0);
}

static ssize_t dump_show(struct device *pdev,
			       struct device_attribute *attr, char *buf)
{
	char *s = buf;

    hisi_secisp_dump();
    s += snprintf(s, MAX_SIZE, "hisi_secisp_dump\n");

	return (s - buf);
}

static ssize_t dump_store(struct device *pdev,
                struct device_attribute *attr, const char *buf,
                size_t count)
{
    return count;
}

