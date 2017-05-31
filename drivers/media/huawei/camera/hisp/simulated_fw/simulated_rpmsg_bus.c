

#include <linux/slab.h>
#include <linux/rpmsg.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include "../../cam_log.h"
#include <global_ddr_map.h>
#include "simulated_fw.h"

#define ISP_BASEADDR (HISI_RESERVED_ISP_BOOT_PHYMEM_BASE)

unsigned int g_remap_addr;

extern void add_kernel_map_addr(int iova, struct ion_handle *hdl,
				void *map_kernel_addr);

extern void *get_kernel_map_addr(int iova);

extern struct ion_handle *del_kernel_map_addr(int iova);

extern int is_kernel_map_list_empty(void);

extern struct ion_handle *del_kernel_map_addr_first(void);

extern void clear_kernel_map_addr_list(void);

extern int simulated_fw_register_rpmsg_driver(struct rpmsg_driver
					      *rpmsg_client);

extern int simulated_fw_unregister_rpmsg_driver(struct rpmsg_driver *rpdrv);

extern int simulated_rpmsg_send(struct rpmsg_channel *rpdev, void *data,
				int len);

extern struct rpmsg_endpoint *simulated_fw_rpmsg_create_ept(struct rpmsg_channel
							    *rpdev,
							    rpmsg_rx_cb_t cb,
							    void *priv,
							    u32 addr);

extern void simulated_fw_rpmsg_destroy_ept(struct rpmsg_endpoint *rpdrv);

extern int simulated_set_algo_info(int algoInfo);

void simulated_add_kernel_map_addr(int iova, struct ion_handle *hdl,
				   void *map_kernel_addr)
{
	add_kernel_map_addr(iova, hdl, map_kernel_addr);
}

EXPORT_SYMBOL(simulated_add_kernel_map_addr);

void *simulated_get_kernel_map_addr(int iova)
{
	return get_kernel_map_addr(iova);
}

EXPORT_SYMBOL(simulated_get_kernel_map_addr);

struct ion_handle *simulated_del_kernel_map_addr(int iova)
{
	return del_kernel_map_addr(iova);
}

EXPORT_SYMBOL(simulated_del_kernel_map_addr);

int simulated_is_kernel_map_list_empty(void)
{
	return is_kernel_map_list_empty();
}

EXPORT_SYMBOL(simulated_is_kernel_map_list_empty);

struct ion_handle *simulated_del_kernel_map_addr_first(void)
{
	return del_kernel_map_addr_first();
}

EXPORT_SYMBOL(simulated_del_kernel_map_addr_first);

void simulated_clear_kernel_map_addr_list(void)
{
	clear_kernel_map_addr_list();
}

EXPORT_SYMBOL(simulated_clear_kernel_map_addr_list);

/**
 * register_rpmsg_driver() - register an rpmsg driver with the fake rpmsg bus
 * @rpdrv: pointer to a struct rpmsg_driver
 *
 * Returns 0 on success, and an appropriate error value on failure.
 */
int simulated_register_rpmsg_driver(struct rpmsg_driver *rpdrv)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return simulated_fw_register_rpmsg_driver(rpdrv);
}

EXPORT_SYMBOL(simulated_register_rpmsg_driver);

/**
 * unregister_rpmsg_driver() - unregister an rpmsg driver from the fake rpmsg bus
 * @rpdrv: pointer to a struct rpmsg_driver
 */
void simulated_unregister_rpmsg_driver(struct rpmsg_driver *rpdrv)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	simulated_fw_unregister_rpmsg_driver(rpdrv);
}

EXPORT_SYMBOL(simulated_unregister_rpmsg_driver);

/**
 * rpmsg_send_offchannel_raw() - send a message across to the remote
 * processor
 * @rpdev: the rpmsg channel
 * @src: source address
 * @dst: destination address
 * @data: payload of message
 * @len: length of payload
 * @wait: indicates whether caller should block in case no TX buffers available
 *
 * Returns 0 on success and an appropriate error value on failure.
 */
int simulated_rpmsg_send_offchannel_raw(struct rpmsg_channel *rpdev, u32 src,
					u32 dst, void *data, int len, bool wait)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return simulated_rpmsg_send(rpdev, data, len);
}

int simulated_rpmsg_send_offchannel(struct rpmsg_channel *rpdev, u32 src,
				    u32 dst, void *data, int len)
{
	return simulated_rpmsg_send_offchannel_raw(rpdev, src, dst, data, len,
						   true);
}

EXPORT_SYMBOL(simulated_rpmsg_send_offchannel);

int simulated_hisp_set_algo_info(int algoInfo)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return simulated_set_algo_info(algoInfo);
}

EXPORT_SYMBOL(simulated_hisp_set_algo_info);

/**
 * rpmsg_create_ept() - create a new rpmsg_endpoint
 * @rpdev: rpmsg channel device
 * @cb: rx callback handler
 * @priv: private data for the driver's use
 * @addr: local rpmsg address to bind with @cb
 *
 * Returns a pointer to the endpoint on success, or NULL on error.
 */
struct rpmsg_endpoint *simulated_rpmsg_create_ept(struct rpmsg_channel *rpdev,
						  rpmsg_rx_cb_t cb, void *priv,
						  u32 addr)
{
	struct rpmsg_endpoint *ept;
	cam_info("%s:%s() enter", __FILE__, __func__);
	ept = simulated_fw_rpmsg_create_ept(rpdev, cb, priv, addr);
	cam_info("create ept %pK ", ept);
	return ept;
}

/**
 * rpmsg_destroy_ept() - do nothing for fake rpmsg bus
 * @ept: endpoing to destroy
 *
 * Should be used by drivers to destroy an rpmsg endpoint previously
 * created with rpmsg_create_ept().
 */
void simulated_rpmsg_destroy_ept(struct rpmsg_endpoint *ept)
{
	cam_info("%s:%s() destory ept %pK enter", __FILE__, __func__, ept);
	simulated_fw_rpmsg_destroy_ept(ept);
	return;
}

EXPORT_SYMBOL(simulated_rpmsg_destroy_ept);

void simulated_hisi_rproc_flush(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return;
}

struct completion simulated_channel_sync;

int simulated_hisi_isp_rproc_disable(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return 0;
}

int simulated_hisi_isp_rproc_enable(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	init_completion(&simulated_channel_sync);
	complete(&simulated_channel_sync);
	return 0;
}

/* enable rproc a7 and isp core*/
int simulated_hisi_isp_rproc_device_enable(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
#ifdef PORTING_L
	return 0;
#else
	return simulated_fw_rproc_device_enable();
#endif
}

void simulated_hisi_isp_rproc_device_disable(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
#ifdef PORTING_L
	return;
#else
	simulated_fw_rproc_device_disable();
#endif
}

int simulated_hisi_isp_rproc_setpinctl(struct pinctrl *isp_pinctrl,
				       struct pinctrl_state *pinctrl_def,
				       struct pinctrl_state *pinctrl_idle)
{
	return 0;
}

int simulated_hisi_isp_rproc_setclkdepend(struct clk *aclk_dss,
					  struct clk *pclk_dss)
{
	return 0;
}

void simulated_flush_rproc_carveout_cache(void)
{
	return;
}

int simulated_rpmsg_reset_device(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return 0;
}

int simulated_rproc_fw_elf_reload(void)
{
	cam_info("%s:%s() enter", __FILE__, __func__);
	return 0;
}

void simulated_print_rpmsg_vq_msg(void)
{
	return;
}

int simulated_set_plat_parameters(void)
{
	return 0;
}

void simulated_rproc_set_sync_flag(bool flag)
{
	return;
}
