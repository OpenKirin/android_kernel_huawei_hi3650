

#include <linux/compiler.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/module.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/rpmsg.h>
#include <linux/skbuff.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <linux/file.h>
#include <media/huawei/camera.h>
#ifdef HISP_V150
#include <media/huawei/hisp150_cfg.h>
#else
#include <media/huawei/hisp_cfg.h>
#endif
#include <media/v4l2-event.h>
#include <media/v4l2-fh.h>
#include <media/v4l2-subdev.h>
#include <media/videobuf2-core.h>
#include <linux/pm_qos.h>
#include <clocksource/arm_arch_timer.h>
#include <asm/arch_timer.h>
#include <linux/time.h>
#include <linux/jiffies.h>
#include "cam_log.h"
#include "hisp_intf.h"
#include "platform/sensor_commom.h"
#include <linux/hisi/hisi_ion.h>
#include <linux/hisi/hisi-iommu.h>
#include <linux/iommu.h>
#include <linux/wakelock.h>
#include "trace_hisp.h"

/* add for HiLOGE */
#include <linux/hisi/hilog.h>
/* lint -save -e740 */
#define HILOG_CAMERA_MODULE_NAME    "Camera"
#define HILOG_CAMERA_SUBMODULE_NAME    "FW_Interaction"

DEFINE_MUTEX(hisi_rpmsg_service_mutex);
DEFINE_MUTEX(hisp_wake_lock_mutex);

static struct pm_qos_request qos_request_ddr_down_record;
static int current_ddr_bandwidth;
static struct wake_lock hisp_power_wakelock;

extern struct completion simulated_channel_sync;

extern void hisi_isp_boot_stat_dump(void);

extern int hisp_set_algo_info(int algoInfo);

extern int simulated_hisi_isp_rproc_enable(void);

extern int simulated_hisi_isp_rproc_setclkdepend(struct clk *aclk_dss,
						 struct clk *pclk_dss);

extern struct rpmsg_endpoint *simulated_rpmsg_create_ept(struct rpmsg_channel
							 *rpdev,
							 rpmsg_rx_cb_t cb,
							 void *priv, u32 addr);

extern int simulated_rpmsg_send_offchannel(struct rpmsg_channel *rpdev, u32 src,
					   u32 dst, void *data, int len);

extern int simulated_hisi_isp_rproc_disable(void);

extern void simulated_rproc_set_sync_flag(bool flag);

extern void simulated_rpmsg_destroy_ept(struct rpmsg_endpoint *ept);

extern int simulated_register_rpmsg_driver(struct rpmsg_driver *rpdrv);

extern void simulated_unregister_rpmsg_driver(struct rpmsg_driver *rpdrv);

extern void simulated_add_kernel_map_addr(int iova, struct ion_handle *hdl,
					  void *map_kernel_addr);

extern void *simulated_get_kernel_map_addr(int iova);

extern int simulated_is_kernel_map_list_empty(void);

extern struct ion_handle *simulated_del_kernel_map_addr_first(void);

extern void simulated_clear_kernel_map_addr_list(void);

extern struct ion_handle *simulated_del_kernel_map_addr(int iova);

typedef enum _timestamp_state_t {
	TIMESTAMP_UNINTIAL = 0,
	TIMESTAMP_INTIAL,
} timestamp_state_t;
static timestamp_state_t s_timestamp_state;
static struct timeval s_timeval;
static u32 s_system_couter_rate;
static u64 s_system_counter;

enum Simulated_hisp_rpmsg_state {
	RPMSG_UNCONNECTED,
	RPMSG_CONNECTED,
	RPMSG_FAIL,
};

/*
 *These are used for distinguish the rpmsg_msg status
 *The process in Simulated_hisp_rpmsg_ept_cb are different
 *for the first receive and later.
 */
enum {
	HISP_SERV_FIRST_RECV,
	HISP_SERV_NOT_FIRST_RECV,
};

/**@brief the instance for rpmsg service
 *
 *When Histar ISP is probed, this sturcture will be initialized,
 *the object is used to send/recv rpmsg and store the rpmsg data
 *
 *@end
 */
struct rpmsg_Simulated_hisp_service {
	struct rpmsg_channel *rpdev;
	struct mutex send_lock;
	struct mutex recv_lock;
	struct completion *comp;
	struct sk_buff_head queue;
	wait_queue_head_t readq;
	struct rpmsg_endpoint *ept;
	u32 dst;
	int state;
	char recv_count;
};

/**@brief the instance to talk to hisp driver
 *
 *When Histar ISP is probed, this sturcture will be initialized,
 *the object is used to notify hisp driver when needed.
 *
 *@end
 */
typedef struct _tag_Simulated_hisp {
	hisp_intf_t intf;
	hisp_notify_intf_t *notify;
	char const *name;
	atomic_t opened;
	struct platform_device *pdev;	/* by used to get dts node */
	hisp_dt_data_t dt;
	struct iommu_domain *domain;
	struct ion_handle *handle;
	struct ion_client *ion_client;
} Simulated_hisp_t;

struct rpmsg_service_info {
	struct rpmsg_Simulated_hisp_service *hisi_isp_serv;
	struct completion isp_comp;
	int isp_minor;
};

/*Store the only rpmsg_Simulated_hisp_service pointer to local static rpmsg_local*/
static struct rpmsg_service_info rpmsg_local;
static bool remote_processor_up;

#define I2HI(i) container_of(i, Simulated_hisp_t, intf)

static void Simulated_hisp_notify_rpmsg_cb(void);

char const *Simulated_hisp_get_name(hisp_intf_t *i);

static int Simulated_hisp_config(hisp_intf_t *i, void *cfg);

static int Simulated_hisp_power_on(hisp_intf_t *i);

static int Simulated_hisp_power_off(hisp_intf_t *i);

static int Simulated_hisp_send_rpmsg(hisp_intf_t *i, hisp_msg_t *m,
				     size_t len);

static int Simulated_hisp_recv_rpmsg(hisp_intf_t *i,
				     hisp_msg_t *user_addr, size_t len);

static int Simulated_hisp_set_Algoinfo(hisp_intf_t *i, int mode);

static void Simulated_hisp_set_ddrfreq(int ddr_bandwidth);

static void Simulated_hisp_release_ddrfreq(void);

static void Simulated_hisp_update_ddrfreq(unsigned int ddr_bandwidth);
void Simulated_hisp_init_timestamp(void);
void Simulated_hisp_destroy_timestamp(void);
void Simulated_hisp_set_timestamp(msg_ack_request_t *ack);
void Simulated_hisp_handle_msg(hisp_msg_t *msg);

void Simulated_hisp_init_timestamp(void)
{
	s_timestamp_state = TIMESTAMP_INTIAL;
	s_system_counter = arch_counter_get_cntvct();
	s_system_couter_rate = arch_timer_get_rate();
	do_gettimeofday(&s_timeval);

	cam_info("%s state=%u system_counter=%llu rate=%u" " time_second=%ld time_usecond=%ld size=%lu", __func__, (unsigned int)s_timestamp_state, s_system_counter, s_system_couter_rate, s_timeval.tv_sec, s_timeval.tv_usec, sizeof(s_timeval) / sizeof(u32));	/* FIXME */
}

void Simulated_hisp_destroy_timestamp(void)
{
	s_timestamp_state = TIMESTAMP_UNINTIAL;
	s_system_counter = 0;
	s_system_couter_rate = 0;
	memset(&s_timeval, 0x00, sizeof(s_timeval));
}

/*Function declaration */
/**********************************************
 * |-----pow-on------->||<----  fw-SOF ---->|
 *  timeval(got)       ----------------->fw_timeval=?
 *  system_counter(got)----------------->fw_sys_counter(got)
 *
 *  fw_timeval = timeval + (fw_sys_counter - system_counter)
 *
 *With a base position(<timeval, system_counter>, we get it at same time),
 *we can calculate fw_timeval with fw syscounter
 *and deliver it to hal. Hal then gets second and microsecond
 *********************************************/
void Simulated_hisp_set_timestamp(msg_ack_request_t *ack)
{
#define NANOSECOND_PER_SECOND     (1000000000)
#define MICROSECOND_PER_SECOND     (1000000)
	u64 fw_micro_second = 0;

	if (NULL == ack) {
		cam_err("%s err ack is NULL.", __func__);
		return;
	}
	do_gettimeofday(&s_timeval);
	fw_micro_second =
	    s_timeval.tv_sec * MICROSECOND_PER_SECOND + s_timeval.tv_usec;

	ack->timestampH = (u32) (fw_micro_second >> 32 & 0xFFFFFFFF);
	ack->timestampL = (u32) (fw_micro_second & 0xFFFFFFFF);

	cam_debug("%s h:0x%x l:0x%x", __func__, ack->timestampH,
		  ack->timestampL);
}

void Simulated_hisp_handle_msg(hisp_msg_t *msg)
{
	if (NULL == msg)
		return;
	switch (msg->api_name) {
	case REQUEST_RESPONSE:
		Simulated_hisp_set_timestamp(&(msg->u.ack_request));
		break;

	default:
		break;
	}
}

static hisp_vtbl_t s_vtbl_Simulated_hisp = {
	.get_name = Simulated_hisp_get_name,
	.config = Simulated_hisp_config,
	.power_on = Simulated_hisp_power_on,
	.power_off = Simulated_hisp_power_off,
	.send_rpmsg = Simulated_hisp_send_rpmsg,
	.recv_rpmsg = Simulated_hisp_recv_rpmsg,
	/* .set_Algoinfo = Simulated_hisp_set_Algoinfo, */
};

static Simulated_hisp_t s_Simulated_hisp = {
	.intf = {.vtbl = &s_vtbl_Simulated_hisp,},
#ifdef HISP_V100
	.name = "hisp100",
#else
#ifdef HISP_V110
	.name = "hisp110",
#else
#ifdef HISP_V150
	.name = "hisp150",
#endif
#endif
#endif
};

static void Simulated_hisp_notify_rpmsg_cb(void)
{
	hisp_event_t isp_ev;
	isp_ev.kind = HISP_RPMSG_CB;
	cam_debug("%s, %d", __func__, __LINE__);
	hisp_notify_intf_rpmsg_cb(s_Simulated_hisp.notify, &isp_ev);
}

/*Function declaration */
/**********************************************
 *Save the rpmsg from isp to locally skb queue.
 *Only called by Simulated_hisp_rpmsg_ept_cb when api_name
 *is NOT POWER_REQ, will notify user space through HISP
 *********************************************/
static void Simulated_hisp_save_rpmsg_data(void *data, int len)
{
	struct rpmsg_Simulated_hisp_service *hisi_serv =
	    rpmsg_local.hisi_isp_serv;
	struct sk_buff *skb = NULL;
	char *skbdata = NULL;

	cam_debug("Enter %s\n", __func__);
	if (NULL == hisi_serv) {
		cam_err("func %s: hisi_serv is NULL", __func__);
		return;
	}
	if (NULL == data) {
		cam_err("func %s: hisi_serv is NULL", __func__);
		return;
	}

	if (len <= 0) {
		cam_err("func %s: len = %d", __func__, len);
		return;
	}

	skb = alloc_skb(len, GFP_KERNEL);
	if (!skb) {
		cam_err("%s() %d failed: alloc_skb len is %u!\n", __func__,
			__LINE__, len);
		return;
	}

	skbdata = skb_put(skb, len);
	memcpy(skbdata, data, len);

	/*add skb to skb queue */
	mutex_lock(&hisi_serv->recv_lock);
	skb_queue_tail(&hisi_serv->queue, skb);
	mutex_unlock(&hisi_serv->recv_lock);

	wake_up_interruptible(&hisi_serv->readq);
	Simulated_hisp_notify_rpmsg_cb();
	trace_hisp_rpmsg_notify((hisp_msg_t *) data);
}

/*Function declaration */
/**********************************************
 *Power up CSI/DPHY/sensor according to isp req
 *Only called by Simulated_hisp_rpmsg_ept_cb when api_name
 *is POWER_REQ, and will send a POWER_RSP to isp
 *after power request done.
 *********************************************/
#if 0
static void Simulated_hisp_power_req(hisp_msg_t *msg, int len)
{
	struct rpmsg_Simulated_hisp_service *hisi_serv =
	    rpmsg_local.hisi_isp_serv;

	cam_info("Enter %s\n", __func__);
	if (NULL == hisi_serv) {
		cam_err("func %s: hisi_serv is NULL", __func__);
		return;
	}
	if (NULL == msg) {
		cam_err("func %s: msg is NULL", __func__);
		return;
	}
	if (len <= 0) {
		cam_err("func %s: len = %d", __func__, len);
		return;
	}
#if 0
	hisp_assert(POWER_REQ == msg->api_name);
	hisp_assert(HISP_SERV_FIRST_RECV != hisi_serv->recv_count);

	switch (msg->u.req_power.power_req_nr) {
		/*TODO: power up csi/DPHY/sensor according to isp req */
	default:
		cam_info("%s invalid req_power!\n", __func__);
		break;
	}
	msg->api_name = POWER_RSP;
#endif
#ifdef FAKE_FW
	fake_rpmsg_send(hisi_serv->rpdev, (void *)msg, len);
#else
	if (0 !=
	    simulated_rpmsg_send_offchannel(hisi_serv->rpdev,
					    hisi_serv->ept->addr,
					    hisi_serv->dst, (void *)msg, len)) {
		cam_err("func %s failed  \n", __func__);
		return;
	}
#endif
	cam_info("%s Not implement yet ....\n", __func__);
}
#endif

static void
Simulated_hisp_rpmsg_ept_cb(struct rpmsg_channel *rpdev,
			    void *data, int len, void *priv, u32 src)
{
	struct rpmsg_Simulated_hisp_service *hisi_serv =
	    rpmsg_local.hisi_isp_serv;
	hisp_msg_t *msg = NULL;
	struct rpmsg_hdr *rpmsg_msg = NULL;

	cam_debug("Enter %s\n", __func__);
	if (NULL == hisi_serv) {
		cam_err("func %s: hisi_serv is NULL", __func__);
		return;
	}
	if (NULL == data) {
		cam_err("func %s: data is NULL", __func__);
		return;
	}

	if (len <= 0) {
		cam_err("func %s: len = %d", __func__, len);
		return;
	}

	if (RPMSG_CONNECTED != hisi_serv->state) {
		hisp_assert(RPMSG_UNCONNECTED == hisi_serv->state);
		rpmsg_msg = container_of(data, struct rpmsg_hdr, data);
		cam_info("msg src.%u, msg dst.%u\n", rpmsg_msg->src,
			 rpmsg_msg->dst);

		/*add instance dst and modify the instance state */
		hisi_serv->dst = rpmsg_msg->src;
		hisi_serv->state = RPMSG_CONNECTED;
	}

	msg = (hisp_msg_t *) (data);
	trace_hisp_rpmsg_ept_cb(msg);
	/* save the data and wait for Simulated_hisp_recv_rpmsg to get the data */
	Simulated_hisp_save_rpmsg_data(data, len);

}

char const *Simulated_hisp_get_name(hisp_intf_t *i)
{
	Simulated_hisp_t *hi = NULL;
	hisp_assert(NULL != i);
	hi = I2HI(i);
	if (NULL == hi) {
		cam_err("func %s: hi is NULL", __func__);
		return NULL;
	}
	return hi->name;
}

static int Simulated_unmap_a7isp_addr(void *cfg)
{
	struct hisp_cfg_data *pcfg = NULL;
	if (NULL == cfg) {
		cam_err("func %s: cfg is NULL", __func__);
		return -1;
	}

	pcfg = (struct hisp_cfg_data *)cfg;

	cam_info("func %s: a7 %x, size %x", __func__, pcfg->param.moduleAddr,
		 pcfg->param.size);
	struct ion_handle *hdl = NULL;
	hdl = simulated_del_kernel_map_addr(pcfg->param.iova);
	if (hdl != NULL && s_Simulated_hisp.ion_client != NULL) {
		cam_info("func %s: ion handle 0x%x", __func__, hdl);
		ion_unmap_kernel(s_Simulated_hisp.ion_client, hdl);
		ion_free(s_Simulated_hisp.ion_client, hdl);
		cam_info("func %s: iova %x, map addr not exist", __func__,
			 pcfg->param.iova);
	}
	/* a7_mmu_unmap(pcfg->param.moduleAddr, pcfg->param.size); */

	return 0;
}

static int Simulated_get_a7isp_addr(void *cfg)
{
	struct hisp_cfg_data *pcfg = NULL;
	struct scatterlist *sg;
	struct sg_table *table;
	struct ion_handle *hdl = NULL;
	void *kernel_vaddr = NULL;
	if (NULL == cfg) {
		cam_err("func %s: cfg is NULL", __func__);
		return -1;
	}
	pcfg = (struct hisp_cfg_data *)cfg;
	kernel_vaddr = simulated_get_kernel_map_addr(pcfg->param.iova);
	if (-1 == kernel_vaddr) {
		hdl =
		    ion_import_dma_buf(s_Simulated_hisp.ion_client,
				       pcfg->param.sharedFd);
		if (IS_ERR_OR_NULL(hdl)) {
			cam_err("failed to create ion handle!");
			return PTR_ERR(hdl);
		}
		cam_info("func %s: import ok", __func__);

		s_Simulated_hisp.handle = hdl;
		/* table = ion_sg_table(s_Simulated_hisp.ion_client, s_Simulated_hisp.handle);
		   if (IS_ERR_OR_NULL(table)) {
		   cam_err("%s Failed : ion_sg_table.%lu\n", __func__, PTR_ERR(table));
		   return PTR_ERR(table);
		   }
		   cam_info("func %s: ion_sg_table ok",__func__);

		   sg = table->sgl;

		   pcfg->param.moduleAddr = a7_mmu_map(sg, pcfg->param.size,
		   pcfg->param.prot, pcfg->param.type); */
		kernel_vaddr =
		    ion_map_kernel(s_Simulated_hisp.ion_client,
				   s_Simulated_hisp.handle);
		simulated_add_kernel_map_addr(pcfg->param.iova,
					      s_Simulated_hisp.handle,
					      kernel_vaddr);
		cam_info
		    ("func %s: iova: 0x%x, ion handle: 0x%x, map_addr: 0x%x",
		     __func__, pcfg->param.iova, s_Simulated_hisp.handle,
		     kernel_vaddr);
	}
	pcfg->param.moduleAddr = pcfg->param.iova;
	return 0;
}

static int Simulated_hisp_config(hisp_intf_t *i, void *cfg)
{
	int rc = 0;
	Simulated_hisp_t *hi = NULL;
	struct hisp_cfg_data *pcfg = NULL;

	if ((NULL == cfg) || (NULL == i)) {
		cam_err("func %s: cfg(%pK) i(%pK)", __func__, cfg, i);
		return -1;
	}
	pcfg = (struct hisp_cfg_data *)cfg;
	hi = I2HI(i);
	if (NULL == hi) {
		cam_err("func %s: hi is NULL", __func__);
		return -1;
	}

	switch (pcfg->cfgtype) {
	case HISP_CONFIG_POWER_ON:
		if (!remote_processor_up) {
			cam_notice("%s power on the Simulated_hisp.\n",
				   __func__);
			rc = Simulated_hisp_power_on(i);
		} else {
			cam_warn
			    ("%s Simulated_hisp is still on power-on state, power off it.\n",
			     __func__);
			rc = Simulated_hisp_power_off(i);
			if (0 != rc) {
				break;
			}

			cam_warn("%s begin to power on the Simulated_hisp.\n",
				 __func__);
			rc = Simulated_hisp_power_on(i);
		}
		break;
	case HISP_CONFIG_POWER_OFF:
		if (remote_processor_up) {
			cam_notice("%s power off the Simulated_hisp.\n",
				   __func__);
			rc = Simulated_hisp_power_off(i);
		}
		break;
	case HISP_CONFIG_GET_MAP_ADDR:
		rc = Simulated_get_a7isp_addr(cfg);
		cam_info("%s get a7 map address 0x%x\n", __func__,
			 pcfg->param.moduleAddr);
		break;
	case HISP_CONFIG_UNMAP_ADDR:
		cam_info("%s unmap a7 address from isp atf\n", __func__);
		rc = Simulated_unmap_a7isp_addr(cfg);
		break;
	default:
		break;
	}
	return rc;
}

static int Simulated_hisp_set_Algoinfo(hisp_intf_t *i, int mode)
{
	int rc = 0;
	Simulated_hisp_t *hi = NULL;
	int Algoinfo = 0;

	if ((NULL == i)) {
		cam_err("func %s: i(%pK)", __func__, i);
		return -1;
	}

	hi = I2HI(i);
	if (NULL == hi) {
		cam_err("func %s: hi is NULL", __func__);
		return -1;
	}
	Algoinfo = mode;
	rc = hisp_set_algo_info(Algoinfo);
	return rc;
}

/* TRICY:
 * the chip issue: Need keep dss aclk, pclk enable while ISP is accessing DDRC.
 * Enable dss aclk, pclk before ISP power on, diable them after ISP power off.
 */

static int Simulated_hisp_dependent_clock_enable(Simulated_hisp_t *hi)
{
	int rc = 0;

	cam_info("%s: enter. Enable dss aclk, pclk.", __func__);

	return rc;
}

static int Simulated_hisp_dependent_clock_disable(Simulated_hisp_t *hi)
{
	cam_info("%s: enter. Disable dss aclk, pclk.", __func__);

	return 0;
}

static int Simulated_hisp_power_on(hisp_intf_t *i)
{
	int rc = 0;
	bool rproc_enable = false;
	bool hi_opened = false;
	bool clock_enable = false;
	bool ion_client_created = false;
	Simulated_hisp_t *hi = NULL;
	unsigned long current_jiffies = jiffies;
	uint32_t timeout = hw_is_fpga_board() ? 30000 : 15000;

	struct rpmsg_Simulated_hisp_service *hisi_serv = NULL;
	if (NULL == i) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME,
		       "func %s: i is NULL", __func__);
		return -1;
	}
	hi = I2HI(i);

	cam_info("%s enter ....\n", __func__);

	mutex_lock(&hisp_wake_lock_mutex);
	if (!wake_lock_active(&hisp_power_wakelock)) {
		wake_lock(&hisp_power_wakelock);
		cam_info("%s hisp power on enter, wake lock\n", __func__);
	}
	mutex_unlock(&hisp_wake_lock_mutex);

	mutex_lock(&hisi_rpmsg_service_mutex);
	if (!atomic_read((&hi->opened))) {
		if (!hw_is_fpga_board()) {
			Simulated_hisp_dependent_clock_enable(hi);
			clock_enable = true;
			if (!IS_ERR(hi->dt.pinctrl_default)) {
				/* rc = pinctrl_select_state(hi->dt.pinctrl, hi->dt.pinctrl_default); */
				rc = 0;
				if (0 != rc) {
					HiLOGE(HILOG_CAMERA_MODULE_NAME,
					       HILOG_CAMERA_SUBMODULE_NAME,
					       "could not set pins to default state.\n");
					goto FAILED_RET;
				}
			}
		}

		rc = simulated_hisi_isp_rproc_enable();
		if (rc != 0) {
			HiLOGE(HILOG_CAMERA_MODULE_NAME,
			       HILOG_CAMERA_SUBMODULE_NAME,
			       "Failed: simulated_hisi_isp_rproc_enable.%d!\n",
			       rc);
			goto FAILED_RET;
		}
		rproc_enable = true;

		rc = wait_for_completion_timeout(&simulated_channel_sync,
						 msecs_to_jiffies(timeout));
		if (0 == rc) {
			HiLOGE(HILOG_CAMERA_MODULE_NAME,
			       HILOG_CAMERA_SUBMODULE_NAME,
			       "Boot failed: wait_for_completion_interruptible_timeout timed out, ret.%d!\n",
			       rc);
			rc = -ETIME;
			goto FAILED_RET;
		} else {
			cam_info("%s() %d after wait completion, rc = %d!\n",
				 __func__, __LINE__, rc);
			rc = 0;
		}
		atomic_inc(&hi->opened);
		hi_opened = true;
	} else {
		cam_notice("%s isp has been opened.\n", __func__);
	}
	remote_processor_up = true;

	hisi_serv = rpmsg_local.hisi_isp_serv;
	if (!hisi_serv) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME,
		       "failed: hisi_serv does not exist!\n");
		rc = -ENODEV;
		goto FAILED_RET;
	}

	/*assign a new, unique, local address and associate instance with it */
	hisi_serv->ept =
	    simulated_rpmsg_create_ept(hisi_serv->rpdev,
				       Simulated_hisp_rpmsg_ept_cb, hisi_serv,
				       RPMSG_ADDR_ANY);
	if (!hisi_serv->ept) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME,
		       "failed: create ept!\n");
		hisi_serv->state = RPMSG_FAIL;
		rc = -ENOMEM;
		goto FAILED_RET;
	}
	cam_info("%s() %d hisi_serv->rpdev:src.%d, dst.%d\n",
		 __func__, __LINE__,
		 hisi_serv->rpdev->src, hisi_serv->rpdev->dst);
	hisi_serv->state = RPMSG_CONNECTED;
	/*set the instance recv_count */
	hisi_serv->recv_count = HISP_SERV_FIRST_RECV;

	Simulated_hisp_init_timestamp();
	if(s_Simulated_hisp.ion_client == NULL)
	{
		s_Simulated_hisp.ion_client = hisi_ion_client_create("hwcam-Simulated");
		if (IS_ERR_OR_NULL(s_Simulated_hisp.ion_client)) {
			cam_err("failed to create ion client! \n");
			rc = -ENOMEM;
			goto FAILED_RET;
		}
	}
	ion_client_created = true;
	mutex_unlock(&hisi_rpmsg_service_mutex);
	cam_info("%s exit ,power on time:%d....\n", __func__,
		 jiffies_to_msecs(jiffies - current_jiffies));
	return rc;

FAILED_RET:
	if (hi_opened) {
		atomic_dec(&hi->opened);
	}
	if (rproc_enable) {
		simulated_hisi_isp_rproc_disable();
		simulated_rproc_set_sync_flag(true);
	}

	if (clock_enable) {
		Simulated_hisp_dependent_clock_disable(hi);
	}
	if (ion_client_created) {
		ion_client_destroy(s_Simulated_hisp.ion_client);
	}
	remote_processor_up = false;

	mutex_unlock(&hisi_rpmsg_service_mutex);

	mutex_lock(&hisp_wake_lock_mutex);
	if (wake_lock_active(&hisp_power_wakelock)) {
		wake_unlock(&hisp_power_wakelock);
		cam_info("%s hisp power on failed, wake unlock\n", __func__);
	}
	mutex_unlock(&hisp_wake_lock_mutex);
	return rc;
}

static int Simulated_hisp_power_off(hisp_intf_t *i)
{
	int rc = 0;
	Simulated_hisp_t *hi = NULL;
	unsigned long current_jiffies = jiffies;
	struct rpmsg_Simulated_hisp_service *hisi_serv = NULL;
	if (NULL == i) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME,
		       "func %s: i is NULL", __func__);
		return -1;
	}
	hi = I2HI(i);

	cam_info("%s enter ....\n", __func__);

	/*check the remote processor boot flow */
	if (false == remote_processor_up) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME,
		       "failed: rproc boot failure: BOOT_FAILURE!\n");
		rc = -EPERM;
		goto RET;
	}

	hisi_serv = rpmsg_local.hisi_isp_serv;
	if (!hisi_serv) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME,
		       "failed: hisi_serv does not exist!\n");
		rc = -ENODEV;
		goto RET;
	}

	if (RPMSG_FAIL == hisi_serv->state) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME,
		       "failed: hisi_serv->state is RPMSG_FAIL!\n");
		rc = -EFAULT;
		goto RET;
	}

	mutex_lock(&hisi_rpmsg_service_mutex);

	if (!hisi_serv->ept) {
		HiLOGE(HILOG_CAMERA_MODULE_NAME, HILOG_CAMERA_SUBMODULE_NAME,
		       "failed: hisi_serv->ept is NULL!\n");
		rc = -ENODEV;
		goto UNLOCK_RET;
	}
	simulated_rpmsg_destroy_ept(hisi_serv->ept);

	hisi_serv->state = RPMSG_UNCONNECTED;
	hisi_serv->recv_count = HISP_SERV_FIRST_RECV;

	if (atomic_read((&hi->opened))) {

#if 0
		rc = simulated_rpmsg_reset_device();
		if (rc != 0) {
			cam_err
			    ("%s() %d failed: simulated_rpmsg_reset_device ret is %d!\n",
			     __func__, __LINE__, rc);
		}

		/*todo: release resources here */
		/*
		 *If state == fail, remote processor crashed, so don't send it
		 *any message.
		 */
		simulated_hisi_rproc_flush();
		simulated_hisi_isp_rproc_device_disable();
		/* print_rpmsg_vq_msg(); */
#else
		simulated_hisi_isp_rproc_disable();
#endif

		if (!hw_is_fpga_board()) {
			if (!IS_ERR(hi->dt.pinctrl_idle)) {
				/* rc = pinctrl_select_state(hi->dt.pinctrl, hi->dt.pinctrl_idle); */
				rc = 0;
				if (0 != rc) {
					HiLOGE(HILOG_CAMERA_MODULE_NAME,
					       HILOG_CAMERA_SUBMODULE_NAME,
					       "could not set pins to default state.");
				}
			}

			Simulated_hisp_dependent_clock_disable(hi);
		}

		remote_processor_up = false;
		atomic_dec(&hi->opened);
	} else {
		cam_notice("%s isp hasn't been opened.\n", __func__);
	}

	Simulated_hisp_destroy_timestamp();
UNLOCK_RET:
	mutex_unlock(&hisi_rpmsg_service_mutex);
RET:

	cam_info("%s exit ,power 0ff time:%d....\n", __func__,
		 jiffies_to_msecs(jiffies - current_jiffies));

	mutex_lock(&hisp_wake_lock_mutex);
	if (wake_lock_active(&hisp_power_wakelock)) {
		wake_unlock(&hisp_power_wakelock);
		cam_info("%s hisp power off exit, wake unlock\n", __func__);
	}
	mutex_unlock(&hisp_wake_lock_mutex);
	return rc;
}

static void Simulated_hisp_rpmsg_remove(struct rpmsg_channel *rpdev)
{
	if (NULL == rpdev) {
		cam_err("func %s: rpdev is NULL", __func__);
		return -1;
	}
	struct rpmsg_Simulated_hisp_service *hisi_serv =
	    dev_get_drvdata(&rpdev->dev);

	cam_info("%s enter ....\n", __func__);

	if (hisi_serv == NULL) {
		cam_err("%s: hisi_serv == NULL!", __func__);
		return;
	}
/* mutex_lock(&hisi_rpmsg_service_mutex); */
/* unblock any pending thread */
/* complete(hisi_serv->comp); */
	mutex_destroy(&hisi_serv->send_lock);
	mutex_destroy(&hisi_serv->recv_lock);

	kfree(hisi_serv);
	rpmsg_local.hisi_isp_serv = NULL;
/* mutex_unlock(&hisi_rpmsg_service_mutex); */
	cam_notice("rpmsg hisi driver is removed\n");
}

static void
Simulated_hisp_rpmsg_driver_cb(struct rpmsg_channel *rpdev,
			       void *data, int len, void *priv, u32 src)
{
	cam_info("%s enter ....\n", __func__);
	cam_warn("%s() %d uhm, unexpected message!\n", __func__, __LINE__);
	if (NULL == data || len <= 0) {
		cam_err("%s: data(%pK) len(%d)", __func__, data, len);
		return;
	}
	print_hex_dump(KERN_DEBUG, __func__, DUMP_PREFIX_NONE, 16, 1,
		       data, len, true);
}

static int
Simulated_hisp_send_rpmsg(hisp_intf_t *i, hisp_msg_t *from_user, size_t len)
{
	int rc = 0;
	Simulated_hisp_t *hi = NULL;
	struct rpmsg_Simulated_hisp_service *hisi_serv = NULL;
	hisp_msg_t *msg = from_user;
	if ((NULL == i) || (NULL == from_user || (0 >= len))) {
		cam_err("func %s: from_user(%pK) i(%pK) len(%zu)", __func__,
			from_user, i, len);
		return -1;
	}
	hi = I2HI(i);

	cam_debug("%s enter. api_name(0x%x)\n", __func__, msg->api_name);

	hisi_serv = rpmsg_local.hisi_isp_serv;
	if (!hisi_serv) {
		cam_err("%s() %d failed: hisi_serv does not exist!\n", __func__,
			__LINE__);
		rc = -ENODEV;
		goto RET;
	}

	if (!hisi_serv->ept) {
		cam_err("%s() %d failed:hisi_serv->ept does not exist!\n",
			__func__, __LINE__);
		rc = -ENODEV;
		goto RET;
	}

	mutex_lock(&hisi_serv->send_lock);
	/*if the msg is the first msg, let's treat it special */
	if (RPMSG_CONNECTED != hisi_serv->state) {
		if (!hisi_serv->rpdev) {
			cam_err
			    ("%s() %d failed:hisi_serv->rpdev does not exist!\n",
			     __func__, __LINE__);
			rc = -ENODEV;
			goto UNLOCK_RET;
		}

		rc = simulated_rpmsg_send_offchannel(hisi_serv->rpdev,
						     hisi_serv->ept->addr,
						     hisi_serv->rpdev->dst,
						     (void *)msg, len);
		if (rc) {
			cam_err
			    ("%s() %d failed: first simulated_rpmsg_send_offchannel ret is %d!\n",
			     __func__, __LINE__, rc);
		}
		goto UNLOCK_RET;
	}

	rc = simulated_rpmsg_send_offchannel(hisi_serv->rpdev,
					     hisi_serv->ept->addr,
					     hisi_serv->dst, (void *)msg, len);
	if (rc) {
		cam_err
		    ("%s() %d failed: simulated_rpmsg_send_offchannel ret is %d!\n",
		     __func__, __LINE__, rc);
		goto UNLOCK_RET;
	}

UNLOCK_RET:
	mutex_unlock(&hisi_serv->send_lock);
RET:
	return rc;
}

static int
Simulated_hisp_recv_rpmsg(hisp_intf_t *i, hisp_msg_t *user_addr, size_t len)
{
	int rc = len;
	Simulated_hisp_t *hi = NULL;
	struct rpmsg_Simulated_hisp_service *hisi_serv = NULL;
	struct sk_buff *skb = NULL;
	hisp_msg_t *msg = NULL;
	if ((NULL == user_addr) || (NULL == i)) {
		cam_err("func %s: user_addr(%pK) i(%pK)", __func__, user_addr, i);
		return -1;
	}
	hi = I2HI(i);

	cam_debug("%s enter. \n", __func__);

	hisi_serv = rpmsg_local.hisi_isp_serv;
	if (!hisi_serv) {
		cam_err("%s() %d failed: hisi_serv does not exist!\n", __func__,
			__LINE__);
		rc = -ENODEV;
		goto RET;
	}

	if (HISP_SERV_FIRST_RECV == hisi_serv->recv_count) {
		hisi_serv->recv_count = HISP_SERV_NOT_FIRST_RECV;
	}

	if (mutex_lock_interruptible(&hisi_serv->recv_lock)) {
		cam_err("%s() %d failed: mutex_lock_interruptible!\n", __func__,
			__LINE__);
		rc = -ERESTARTSYS;
		goto RET;
	}

	if (RPMSG_CONNECTED != hisi_serv->state) {
		cam_err("%s() %d hisi_serv->state != RPMSG_CONNECTED!\n",
			__func__, __LINE__);
		rc = -ENOTCONN;
		goto UNLOCK_RET;
	}

	/*nothing to read ? */
	/*check if skb_queue is NULL ? */
	if (skb_queue_empty(&hisi_serv->queue)) {
		mutex_unlock(&hisi_serv->recv_lock);
		cam_err("%s() %d skb_queue is empty!\n", __func__, __LINE__);

		/*otherwise block, and wait for data */
		if (wait_event_interruptible_timeout(hisi_serv->readq,
						(!skb_queue_empty
						(&hisi_serv->queue)
						|| hisi_serv->state == RPMSG_FAIL), HISP_WAIT_TIMEOUT)) {	/* lint !e666 */
			cam_err("%s() %d hisi_serv->state = %d!\n", __func__,
				__LINE__, hisi_serv->state);
			rc = -ERESTARTSYS;
			goto RET;
		}

		if (mutex_lock_interruptible(&hisi_serv->recv_lock)) {
			cam_err("%s() %d failed: mutex_lock_interruptible!\n",
				__func__, __LINE__);
			rc = -ERESTARTSYS;
			goto RET;
		}
	}

	if (RPMSG_FAIL == hisi_serv->state) {
		cam_err("%s() %d state = RPMSG_FAIL!\n", __func__, __LINE__);
		rc = -ENXIO;
		goto UNLOCK_RET;
	}

	skb = skb_dequeue(&hisi_serv->queue);
	if (!skb) {
		cam_err("%s() %d skb is NULL!\n", __func__, __LINE__);
		rc = -EIO;
		goto UNLOCK_RET;
	}

	rc = min((unsigned int)len, skb->len);
	msg = (hisp_msg_t *) (skb->data);

	cam_debug("%s: api_name(0x%x)\n", __func__, msg->api_name);

	Simulated_hisp_handle_msg(msg);
	if (!memcpy(user_addr, msg, rc)) {
		rc = -EFAULT;
		cam_err("Fail: %s()%d ret = %d\n", __func__, __LINE__, rc);
	}
	kfree_skb(skb);

UNLOCK_RET:
	mutex_unlock(&hisi_serv->recv_lock);
RET:
	return rc;
}

static void Simulated_hisp_set_ddrfreq(int ddr_bandwidth)
{
	cam_info("%s enter,ddr_bandwidth:%d\n", __func__, ddr_bandwidth);
	qos_request_ddr_down_record.pm_qos_class = 0;
	/* pm_qos_add_request(&qos_request_ddr_down_record,PM_QOS_MEMORY_THROUGHPUT , ddr_bandwidth); */
	current_ddr_bandwidth = ddr_bandwidth;
}

static void Simulated_hisp_release_ddrfreq(void)
{
	cam_info("%s enter\n", __func__);
	if (current_ddr_bandwidth == 0)
		return;
	/* pm_qos_remove_request(&qos_request_ddr_down_record); */
	current_ddr_bandwidth = 0;
}

static void Simulated_hisp_update_ddrfreq(unsigned int ddr_bandwidth)
{
	cam_info("%s enter,ddr_bandwidth:%u\n", __func__, ddr_bandwidth);
	if (!atomic_read(&s_Simulated_hisp.opened)) {
		cam_info
		    ("%s ,cam is not opened,so u can not set ddr bandwidth\n",
		     __func__);
		return;
	}

	if (current_ddr_bandwidth == 0) {
		/* Simulated_hisp_set_ddrfreq(ddr_bandwidth) */ ;
	} else if (current_ddr_bandwidth > 0) {
		/* pm_qos_update_request(&qos_request_ddr_down_record, ddr_bandwidth); */
		current_ddr_bandwidth = ddr_bandwidth;
	} else {
		cam_err("%s,current_ddr_bandwidth is invalid\n", __func__);
	}
}

static ssize_t hisp_ddr_freq_ctrl_show(struct device *dev,
				       struct device_attribute *attr, char *buf)
{
	cam_info("enter %s,current_ddr_bandwidth:%d\n", __func__,
		 current_ddr_bandwidth);
	if (buf == NULL) {
		cam_err("%s,input buffer is invalid\n", __func__);
		return -EINVAL;
	}
	return snprintf(buf, PAGE_SIZE, "%d\n", current_ddr_bandwidth);
}

static ssize_t hisp_ddr_freq_store(struct device *dev,
				   struct device_attribute *attr,
				   const char *buf, size_t count)
{
	int ddr_bandwidth = 0;
	if (buf == NULL) {
		cam_err("%s,input buffer is invalid\n", __func__);
		return -EINVAL;
	}

	ddr_bandwidth = simple_strtol(buf, NULL, 10);
	cam_info("%s enter,ddr_bandwidth:%d\n", __func__, ddr_bandwidth);

	if (ddr_bandwidth < 0) {
		cam_err("%s,ddr_bandwidth is invalid\n", __func__);
		return -EINVAL;
	} else if (ddr_bandwidth == 0) {
		Simulated_hisp_release_ddrfreq();
	} else if (ddr_bandwidth > 0) {
		Simulated_hisp_update_ddrfreq(ddr_bandwidth);
	}

	return count;
}

static int32_t Simulated_hisp_rpmsg_probe(struct rpmsg_channel *rpdev)
{
	int32_t ret = 0;
	struct rpmsg_Simulated_hisp_service *hisi_serv = NULL;
	cam_notice("%s enter\n", __func__);
	if (NULL == rpdev) {
		cam_err("func %s: rpdev is NULL", __func__);
		return -1;
	}
	if (NULL != rpmsg_local.hisi_isp_serv) {
		cam_notice("%s hisi_serv is already up!\n", __func__);
		goto SERVER_UP;
	}

	hisi_serv = kzalloc(sizeof(*hisi_serv), GFP_KERNEL);
	if (!hisi_serv) {
		cam_err("%s() %d kzalloc failed!\n", __func__, __LINE__);
		ret = -ENOMEM;
		goto ERROR_RET;
	}
	mutex_init(&hisi_serv->send_lock);
	mutex_init(&hisi_serv->recv_lock);
	skb_queue_head_init(&hisi_serv->queue);
	init_waitqueue_head(&hisi_serv->readq);
	hisi_serv->ept = NULL;
	hisi_serv->comp = &rpmsg_local.isp_comp;

	rpmsg_local.hisi_isp_serv = hisi_serv;
SERVER_UP:
	if (NULL == hisi_serv) {
		cam_err("func %s: hisi_serv is NULL", __func__);
		return -1;
	}
	hisi_serv->rpdev = rpdev;
	hisi_serv->state = RPMSG_UNCONNECTED;
	dev_set_drvdata(&rpdev->dev, hisi_serv);

	complete(hisi_serv->comp);

	cam_info("new HISI connection srv channel: %u -> %u!\n",
		 rpdev->src, rpdev->dst);

ERROR_RET:
	return ret;
}

static struct rpmsg_device_id rpmsg_Simulated_hisp_id_table[] = {
	{.name = "rpmsg-hisi"},
	{},
};

MODULE_DEVICE_TABLE(platform, rpmsg_Simulated_hisp_id_table);

static const struct of_device_id s_Simulated_hisp_dt_match[] = {
	{
#ifdef HISP_V100
	 .compatible = "huawei,hisi_isp100",
#else
#ifdef HISP_V110
	 .compatible = "huawei,hisi_isp110",
#else
#ifdef HISP_V150
	 .compatible = "huawei,hisi_isp150",
#endif
#endif
#endif
	 .data = &s_Simulated_hisp.intf,
	 },
	{
	 },
};

MODULE_DEVICE_TABLE(of, s_Simulated_hisp_dt_match);

static struct rpmsg_driver rpmsg_Simulated_hisp_driver = {
	.id_table = rpmsg_Simulated_hisp_id_table,
	.probe = Simulated_hisp_rpmsg_probe,
	.callback = Simulated_hisp_rpmsg_driver_cb,
	.remove = Simulated_hisp_rpmsg_remove,
};

static struct device_attribute hisp_ddr_freq_ctrl_attr =
__ATTR(ddr_freq_ctrl, 0664, hisp_ddr_freq_ctrl_show, hisp_ddr_freq_store);

static int32_t Simulated_hisp_platform_probe(struct platform_device *pdev)
{
	int32_t ret = 0;
	if (NULL == pdev) {
		cam_err("func %s: pdev is NULL", __func__);
		return -1;
	}
	cam_info("%s: enter", __func__);
	wake_lock_init(&hisp_power_wakelock, WAKE_LOCK_SUSPEND,
		       "hisp_power_wakelock");
	ret = hisp_get_dt_data(pdev, &s_Simulated_hisp.dt);
	if (ret < 0) {
		cam_err("%s: get dt failed.", __func__);
		goto error;
	}

	init_completion(&rpmsg_local.isp_comp);
	ret = hisp_register(&s_Simulated_hisp.intf, &s_Simulated_hisp.notify);
	if (0 == ret) {
		atomic_set(&s_Simulated_hisp.opened, 0);
	} else {
		cam_err("%s() %d hisp_register failed with ret %d!\n", __func__,
			__LINE__, ret);
		goto error;
	}

	rpmsg_local.hisi_isp_serv = NULL;

	ret = simulated_register_rpmsg_driver(&rpmsg_Simulated_hisp_driver);
	if (0 != ret) {
		cam_err
		    ("%s() %d simulated_register_rpmsg_driver failed with ret %d!\n",
		     __func__, __LINE__, ret);
		hisp_unregister(&s_Simulated_hisp.intf);
		goto error;
	}

	s_Simulated_hisp.pdev = pdev;

#ifdef DEBUG_HISI_CAMERA
	ret = device_create_file(&pdev->dev, &hisp_ddr_freq_ctrl_attr);
	if (ret < 0) {
		cam_err("%s failed to creat hisp ddr freq ctrl attribute.",
			__func__);
		simulated_unregister_rpmsg_driver(&rpmsg_Simulated_hisp_driver);
		hisp_unregister(&s_Simulated_hisp.intf);
		goto error;
	}
#endif
	return 0;

error:
	wake_lock_destroy(&hisp_power_wakelock);
	cam_notice("%s exit with ret = %d\n", __func__, ret);
	return ret;
}

static struct platform_driver s_Simulated_hisp_driver = {
	.probe = Simulated_hisp_platform_probe,
	.driver = {
#ifdef HISP_V100
		   .name = "huawei,hisi_isp100",
#else
#ifdef HISP_V110
		   .name = "huawei,hisi_isp110",
#else
#ifdef HISP_V150
		   .name = "huawei,hisi_isp150",
#endif
#endif
#endif
		   .owner = THIS_MODULE,
		   .of_match_table = s_Simulated_hisp_dt_match,
		   },
};

static int __init Simulated_hisp_init_module(void)
{
	cam_notice("%s enter\n", __func__);
	return platform_driver_register(&s_Simulated_hisp_driver);
}

static void __exit Simulated_hisp_exit_module(void)
{
	cam_notice("%s enter\n", __func__);
	simulated_unregister_rpmsg_driver(&rpmsg_Simulated_hisp_driver);
	hisp_unregister(&s_Simulated_hisp.intf);
	platform_driver_unregister(&s_Simulated_hisp_driver);
	wake_lock_destroy(&hisp_power_wakelock);
}

module_init(Simulated_hisp_init_module);
module_exit(Simulated_hisp_exit_module);
MODULE_DESCRIPTION("Simulated_hisp driver");
MODULE_LICENSE("GPL v2");
