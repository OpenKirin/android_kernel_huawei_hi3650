
#include <linux/sched.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/kthread.h>
#include <linux/rpmsg.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/uaccess.h>
#include <linux/hisi/hisi_ion.h>
#include <linux/ion.h>
#include <linux/sizes.h>

#include "../../cam_log.h"
#include "simulated_fw.h"

/* Maximum number of receive buffers at once */
#define MSG_RECEIVE_MAX_BUFF  50


LIST_HEAD(map_addr_list);

/*
 * Module parameters
 */

simulated_fw_msg_pro_t s_simulated_fw_msg_pro = {
	.query_capability = simulated_fw_query_capability,
	.acquire_camera = simulated_fw_acquire_camera,
	.release_camera = simulated_fw_release_camera,
	.usecase_config = simulated_fw_usecase_config,
	.stream_on = simulated_fw_stream_on,
	.get_otp = simulated_fw_get_otp,
	.request = simulated_fw_request,
	.warp_request = simulated_fw_warp_request,
	.arsr_request = simulated_fw_arsr_request,
	.dgen_request = simulated_fw_dgen_request,
	.dopt_request = simulated_fw_dopt_request,
	.use_mem_pool = simulated_fw_use_mem_pool,
	.unmap_buffer = simulated_fw_unmap_buffer,
	.set_cal_data = simulated_fw_set_cal_data,
	.set_isp_regs = simulated_fw_set_isp_regs,
	.get_isp_regs = simulated_fw_get_isp_regs,
	.set_i2c_regs = simulated_fw_set_i2c_regs,
	.get_i2c_regs = simulated_fw_get_i2c_regs,
	.test_case_interface = simulated_fw_test_case_interface,
	.flush = simulated_fw_flush,
	.extend_set = simulated_fw_extend_set,
	.extend_get = simulated_fw_extend_get,
	.jpeg_encode = simulated_fw_jpeg_encode,
	.inv_tlb = simulated_fw_inv_tlb,
	.query_ois_update = simulated_fw_query_ois_update,
	.ois_update = simulated_fw_ois_update,
	.query_laser = simulated_fw_query_laser,
	.acquire_laser = simulated_fw_acquire_laser,
	.release_laser = simulated_fw_release_laser,
	.acquire_depthisp = simulated_fw_acquire_depth,
	.release_depthisp = simulated_fw_release_depth,
	.msg_event = simulated_fw_msg_event,
	.msg_log = simulated_fw_msg_log,
	.demap_map_request = simulated_fw_demap_map_request,
	.demap_unmap_request = simulated_fw_demap_unmap_request,
	.dgen_flush_request = simulated_fw_dgen_flush_request,
	.dopt_flush_request = simulated_fw_dopt_flush_request,
	.dmap_format_request = simulated_dmap_format_request,
};

simulated_fw_t s_simulated_fw = {
	.intf = {.msg_pro = &s_simulated_fw_msg_pro,}
	,
	.thread = NULL,
	.rpmsg = {}
	,
	.rpdev = {}
	,
	.num_lock = {}
	,
	.done_wq = {}
	,
	.msg_num = 0,
	.msg_base = NULL,
	.msg_read = NULL,
	.msg_write = NULL,
};

void add_kernel_map_addr(int iova, struct ion_handle *hdl,
			 void *map_kernel_addr)
{
	/* cam_info("%s() enter, iova: 0x%x, map_kernel_addr: 0x%x", __func__, iova, map_kernel_addr) */;
	map_buffer_info *pdata =
	    (map_buffer_info *) kmalloc(sizeof(map_buffer_info), GFP_KERNEL);
	pdata->iova = iova;
	pdata->hdl = hdl;
	pdata->map_kernel_addr = map_kernel_addr;
	list_add(&(pdata->link), map_addr_list.prev);
}

EXPORT_SYMBOL(add_kernel_map_addr);

void *get_kernel_map_addr(int iova)
{
    if (list_empty(&map_addr_list))
	    return -1;

	map_buffer_info *getData;
	struct list_head *tmpMapList = NULL;
	for (tmpMapList = map_addr_list.next; tmpMapList != &map_addr_list;
	     tmpMapList = tmpMapList->next) {
		getData = list_entry(tmpMapList, map_buffer_info, link);
		if (getData->iova == iova)
			break;
	}
	if (tmpMapList == &map_addr_list) {
		return -1;
	} else {
		return getData->map_kernel_addr;
	}
}

EXPORT_SYMBOL(get_kernel_map_addr);

struct ion_handle *del_kernel_map_addr(int iova)
{
    if (list_empty(&map_addr_list))
		return -1;
	map_buffer_info *getData;
	struct list_head *tmpMapList = NULL;
	tmpMapList = map_addr_list.next;
	while (tmpMapList != &map_addr_list) {
		getData = list_entry(tmpMapList, map_buffer_info, link);
		tmpMapList = tmpMapList->next;
		if (getData->iova == iova) {
			struct ion_handle *rtn = getData->hdl;
			list_del(&(getData->link));
			kfree(getData);
			getData = NULL;
			return rtn;
		}
	}
	return NULL;
}

EXPORT_SYMBOL(del_kernel_map_addr);

int is_kernel_map_list_empty(void)
{
	if (list_empty(&map_addr_list))
		return 0;
	else
		return 1;
}

EXPORT_SYMBOL(is_kernel_map_list_empty);

struct ion_handle *del_kernel_map_addr_first(void)
{
	map_buffer_info *getData = NULL;
	struct list_head *tmpMapList = NULL;
	if (list_empty(&map_addr_list))
		return NULL;
	tmpMapList = map_addr_list.next;
	getData = list_entry(tmpMapList, map_buffer_info, link);
	if (getData == NULL) {
		return NULL;
	}
	struct ion_handle *rtn = getData->hdl;
	list_del(&(getData->link));
	kfree(getData);
	getData = NULL;
	return rtn;
}

EXPORT_SYMBOL(del_kernel_map_addr_first);

void clear_kernel_map_addr_list(void)
{
	map_buffer_info *getData = NULL;
	struct list_head *tmpMapList = NULL;
	if (list_empty(&map_addr_list))
		return;
	tmpMapList = map_addr_list.next;
	while (tmpMapList != &map_addr_list) {
		getData = list_entry(tmpMapList, map_buffer_info, link);
		tmpMapList = tmpMapList->next;
		cam_info
		    ("%s() enter, iova: 0x%x, map_kernel_addr: 0x%x, prev: 0x%x, next: 0x%x",
		     __func__, getData->iova, getData->map_kernel_addr,
		     getData->link.prev, getData->link.next);
		if (getData == NULL) {
			return;
		}
		list_del(&(getData->link));
		kfree(getData);
		getData = NULL;
	}
	return;
}

EXPORT_SYMBOL(clear_kernel_map_addr_list);

struct rpmsg_endpoint *simulated_fw_rpmsg_create_ept(struct rpmsg_channel
						     *rpdev, rpmsg_rx_cb_t cb,
						     void *priv, u32 addr)
{
	struct rpmsg_endpoint *ept;
	ept = kzalloc(sizeof(*ept), GFP_KERNEL);
	if (!ept) {
		cam_err("%s() failed to kzalloc a new ept\n", __func__);
		return NULL;
	}
	ept->cb = cb;
	ept->rpdev = rpdev;
	ept->priv = priv;
/*    ept->addr = addr;*/
	s_simulated_fw.rpmsg.callback = cb;
	cam_info("%s() ept is %pK", __func__, ept);
	return ept;
}

EXPORT_SYMBOL(simulated_fw_rpmsg_create_ept);

void simulated_fw_rpmsg_destroy_ept(struct rpmsg_endpoint *ept)
{
	if (!ept) {
		cam_err("%s() destroy a NULL ept\n", __func__);
		return;
	}
	cam_info("%s() ept is %pK", __func__, ept);
	s_simulated_fw.rpmsg.callback = NULL;
	/* ept->cb = NULL */;
	kfree(ept);
	return;
}

EXPORT_SYMBOL(simulated_fw_rpmsg_destroy_ept);

int simulated_fw_rproc_device_enable(void)
{
	if (s_simulated_fw.rpmsg.probe)
		s_simulated_fw.rpmsg.probe(&s_simulated_fw.rpdev);
	return 0;
}

EXPORT_SYMBOL(simulated_fw_rproc_device_enable);

int simulated_fw_rproc_device_disable(void)
{
	if (s_simulated_fw.rpmsg.remove)
		s_simulated_fw.rpmsg.remove(&s_simulated_fw.rpdev);
	return 0;
}

EXPORT_SYMBOL(simulated_fw_rproc_device_disable);

/* Register simulated firmware driver */
int simulated_fw_register_rpmsg_driver(struct rpmsg_driver *rpmsg_client)
{
	int ret = 0;
	cam_debug("%s enter", __func__);

	if (NULL == rpmsg_client)
		return -1;

	s_simulated_fw.rpmsg = *rpmsg_client;

	if (s_simulated_fw.rpmsg.probe)
		s_simulated_fw.rpmsg.probe(&s_simulated_fw.rpdev);

	cam_debug("%s exit", __func__);

	return ret;
}

EXPORT_SYMBOL(simulated_fw_register_rpmsg_driver);

/* Unregister simulated firmware driver */
int simulated_fw_unregister_rpmsg_driver(struct rpmsg_driver *rpdrv)
{
	int ret = 0;
	cam_debug("%s enter", __func__);

	if (s_simulated_fw.rpmsg.remove)
		s_simulated_fw.rpmsg.remove(&s_simulated_fw.rpdev);

	memset(&s_simulated_fw.rpmsg, 0, sizeof(struct rpmsg_driver));

	cam_debug("%s exit", __func__);

	return ret;
}

EXPORT_SYMBOL(simulated_fw_unregister_rpmsg_driver);

/*
 * Cyclical Buffer for rpmsg.
 *
 *    __           max _____            max _____
 * /\   |  /\         |_/_/_|_read         |_____|_write
 * ||   |  ||         |_____|              |_/_/_|
 * ||   |  ||  .      |_____|              |_/_/_|
 * ||   |  ||  .      |_____|              |_/_/_|
 * ||   |  ||  .      |_____|              |_/_/_|
 * ||   |  ||         |_____|_write        |_/_/_|_read
 * ||   |__||         |_/_/_|              |_____|
 * buffer          min                  min
 * read/write      read > write.        write > read.
 * direction
 *
 *
 * max _____                            max _____
 *    |_____|                              |_/_/_|
 *    |_____|                              |_/_/_|
 *    |_____|                              |_/_/_|
 *    |_____|                              |_/_/_|
 *    |_____|_write                        |_/_/_|_read
 *    |_____|_read                         |_/_/_|_write
 *    |_____|                              |_/_/_|
 * min                                  min
 * write = read + 1,                    read = write + 1,
 * after read,                          after write,
 * buffer is empty.                     buffer is full.
 *
 *  _____                                _____
 * |_/_/_| used buffer                  |_____| free buffer
 */

int simulated_rpmsg_send(struct rpmsg_channel *rpdev, void *data, int len)
{
	if (NULL == data) {
		cam_err("%s data is null\n", __func__);
		return -1;
	}
	int ret = 0;

	cam_debug("%s fw_api_name = %u", __func__,
		  ((hisp_msg_t *) data)->api_name);

	mutex_lock(&s_simulated_fw.num_lock);

	if (s_simulated_fw.msg_write ==
	    s_simulated_fw.msg_base + MSG_RECEIVE_MAX_BUFF)
		s_simulated_fw.msg_write = s_simulated_fw.msg_base;

	if (s_simulated_fw.msg_write == s_simulated_fw.msg_read) {
		ret = -1;
		cam_err("msg buffer is overflow,write:0x%pK read:0x%pK",
			s_simulated_fw.msg_write, s_simulated_fw.msg_read);
	} else {
		memcpy(s_simulated_fw.msg_write, data, sizeof(hisp_msg_t));
		/*
		 * s_simulated_fw.msg_num > 0 is condition of
		 * simulated firmware thread wakeup.
		 * We flag this condition for now and generate the event later.
		 */
		s_simulated_fw.msg_num++;
		s_simulated_fw.msg_write++;

		/* Wake up the sleep thread on the Tx msg */
		wake_up_interruptible(&s_simulated_fw.done_wq);
	}

	mutex_unlock(&s_simulated_fw.num_lock);

	cam_debug("%s exit", __func__);
	return ret;
}

EXPORT_SYMBOL(simulated_rpmsg_send);

int simulated_set_algo_info(int algoInfo)
{
	s_simulated_fw.algo_info = algoInfo;
	cam_debug("%s exit", __func__);
	return 0;
}

EXPORT_SYMBOL(simulated_set_algo_info);
/*
 * simulated firmware thread .
 * Wake up the sleep thread on simulated_rpmsg_send.
 */
static int simulated_fw_thread(void *data)
{
	/* struct ion_client *pSimulateClient =NULL */;
	buffer_md_t *p_buffer_md = NULL;
	char *p_preview_buffer = NULL;
	int ret = 0;
	p_buffer_md = kzalloc(sizeof(*p_buffer_md), GFP_KERNEL);
	if (!p_buffer_md) {
		cam_err("%s() failed to kzalloc a new metavalue\n", __func__);
		ret = -1;
		return ret;
	}

	p_preview_buffer = kzalloc(PREVIEW_BUFFER_SIZE, GFP_KERNEL);
	if (!p_preview_buffer) {
		cam_err("%s() failed to kzalloc a new preview buffer\n",
			__func__);
		kfree(p_buffer_md);
		p_buffer_md = NULL;
		ret = -1;
		return ret;
	}
	/* pSimulateClient = hisi_ion_client_create("Simulated_isp_ion_Client") */;
	while (!kthread_should_stop()) {

		/* Wait for any transmission to end */
		wait_event_interruptible(s_simulated_fw.done_wq,
					 s_simulated_fw.msg_num > 0);

		mutex_lock(&s_simulated_fw.num_lock);
		s_simulated_fw.msg_num--;
		mutex_unlock(&s_simulated_fw.num_lock);

		if (NULL == s_simulated_fw.msg_read) {
			s_simulated_fw.msg_read = s_simulated_fw.msg_base;
		} else {
			s_simulated_fw.msg_read++;

			if (s_simulated_fw.msg_read ==
			    (s_simulated_fw.msg_base + MSG_RECEIVE_MAX_BUFF)) {
				s_simulated_fw.msg_read =
				    s_simulated_fw.msg_base;
			}
		}

		/* Receive hisp message */
		hisp_msg_t *hisp_msg_recv = s_simulated_fw.msg_read;

		cam_info("%s() get rpmsg API: 0x%x", __func__,
			 hisp_msg_recv->api_name);
		message_manager(p_buffer_md, s_simulated_fw, p_preview_buffer);
	}
	kfree(p_buffer_md);
	p_buffer_md = NULL;
	kfree(p_preview_buffer);
	p_preview_buffer = NULL;
	/*ion_client_destroy(pSimulateClient)*/;
	return ret;
}

/*
 *    simulated_fw_platform_probe - attach a platform interface
 */

static int32_t simulated_fw_platform_probe(void)
{
	hisp_msg_t *buffbase = NULL;

	cam_notice("enter %s", __func__);
	INIT_LIST_HEAD(&map_addr_list);
	s_simulated_fw.msg_base = NULL;
	s_simulated_fw.msg_base =
	    kmalloc(sizeof(hisp_msg_t) * MSG_RECEIVE_MAX_BUFF, GFP_KERNEL);

	if (NULL == s_simulated_fw.msg_base) {
		cam_alert("%s(%d) kmalloc failed.", __func__, __LINE__);
		return -1;
	}

	buffbase = s_simulated_fw.msg_base;

	s_simulated_fw.msg_num = 0;
	s_simulated_fw.msg_write = buffbase;
	s_simulated_fw.msg_read = NULL;

	mutex_init(&s_simulated_fw.num_lock);

	init_waitqueue_head(&s_simulated_fw.done_wq);

	s_simulated_fw.thread =
	    kthread_run(simulated_fw_thread, NULL, "simulated firmware");
	return 0;
}

static int __init simulated_fw_init_module(void)
{
	cam_notice("enter %s", __func__);
	return simulated_fw_platform_probe();
}

static void __exit simulated_fw_exit_module(void)
{
	cam_notice("exit %s", __func__);

	kthread_stop(s_simulated_fw.thread);
	s_simulated_fw.thread = (struct task_struct *)NULL;

	mutex_destroy(&s_simulated_fw.num_lock);

	kfree(s_simulated_fw.msg_base);
	s_simulated_fw.msg_base = NULL;
}

module_init(simulated_fw_init_module);
module_exit(simulated_fw_exit_module);
MODULE_DESCRIPTION("simulated_fw");
MODULE_LICENSE("GPL v2");
