

#ifndef __SIMULATED_FIRMWARE_INTERFACE__
#define __SIMULATED_FIRMWARE_INTERFACE__

#define MAX_ACQUIRE_CAMERA_NUM       3
#define PORTING_L
#ifdef HISP_V150
#include <media/huawei/hisp150_msg.h>
#include "hisp150_md_message.h"
#else
#include <media/huawei/hisp_msg.h>
#include "hisp_md_message.h"
#endif
#include <linux/list.h>

#define PREVIEW_WIDTH 1920
#define PREVIEW_HEIGHT 1080
#define PREVIEW_BUFFER_SIZE  ((PREVIEW_WIDTH * PREVIEW_HEIGHT * 3) >> 1)

typedef enum {
	CAMERA_OPENED,
	CAMERA_CLOSED,
} camera_status_e;

/*typedef enum
{
    STREAM_RESERVED_0,
    STREAM_REP_RAW_IN,
    STREAM_ISP_YUV_OUT_PREVIEW,
    STREAM_ISP_YUV_OUT,
    STREAM_REP_YUV_OUT,
    STREAM_RESERVED_1,
    STREAM_ISP_RAW_OUT,
    STREAM_ISP_YUV_OUT_RESERVED, // unused
    STREAM_RAW_OUT,
    STREAM_POS_MAX,
} stream_pos_e;
*/
typedef struct _buf_file_info {
	int pid;
	int fd;
} buf_file_info;

typedef struct _map_buffer_info {
	int iova;
	struct ion_handle *hdl;
	void *map_kernel_addr;
	struct list_head link;
} map_buffer_info;

typedef struct _frame_request_info {
	hisp_msg_t *recv_msg;
	struct list_head link;
} frame_request_info;
/**
 * @brief the huawei fw simulated fw interface.
 */

int simulated_fw_query_capability(void *isp_msg);

int simulated_fw_acquire_camera(void *isp_msg);

int simulated_fw_release_camera(void *isp_msg);

int simulated_fw_usecase_config(void *isp_msg);

int simulated_fw_stream_on(void *isp_msg);

int simulated_fw_get_otp(void *isp_msg);

int simulated_fw_request(void *isp_msg);

int simulated_fw_warp_request(void *isp_msg);

int simulated_fw_arsr_request(void *isp_msg);

int simulated_fw_dgen_request(void *isp_msg);

int simulated_fw_dopt_request(void *isp_msg);

int simulated_fw_jpeg_encode(void *isp_msg);

int simulated_fw_use_mem_pool(void *isp_msg);

int simulated_fw_unmap_buffer(void *isp_msg);

int simulated_fw_set_cal_data(void *isp_msg);

int simulated_fw_set_isp_regs(void *isp_msg);

int simulated_fw_get_isp_regs(void *isp_msg);

int simulated_fw_set_i2c_regs(void *isp_msg);

int simulated_fw_get_i2c_regs(void *isp_msg);

int simulated_fw_test_case_interface(void *isp_msg);

int simulated_fw_flush(void *isp_msg);

int simulated_fw_extend_set(void *isp_msg);

int simulated_fw_extend_get(void *isp_msg);

int simulated_fw_inv_tlb(void *isp_msg);

int simulated_fw_query_ois_update(void *isp_msg);

int simulated_fw_ois_update(void *isp_msg);

int simulated_fw_query_laser(void *isp_msg);

int simulated_fw_acquire_laser(void *isp_msg);

int simulated_fw_release_laser(void *isp_msg);

int simulated_fw_acquire_depth(void *isp_msg);

int simulated_fw_release_depth(void *isp_msg);

int simulated_fw_msg_log(void *isp_msg);

int simulated_fw_msg_event(void *isp_msg);

int simulated_fw_demap_map_request(void *isp_msg_r);

int simulated_fw_demap_unmap_request(void *isp_msg_r);

int simulated_fw_dgen_flush_request(void *isp_msg_r);

int simulated_fw_dopt_flush_request(void *isp_msg_r);

int simulated_dmap_format_request(void *isp_msg_r);

typedef struct _tag_simulated_fw_msg_pro {
	/* simulated firmware function table */
	int (*query_capability) (void *isp_msg);
	int (*acquire_camera) (void *isp_msg);
	int (*release_camera) (void *isp_msg);
	int (*usecase_config) (void *isp_msg);
	int (*stream_on) (void *isp_msg);
	int (*get_otp) (void *isp_msg);
	int (*request) (void *isp_msg);
	int (*warp_request) (void *isp_msg);
	int (*arsr_request) (void *isp_msg);
	int (*dgen_request) (void *isp_msg);
	int (*dopt_request) (void *isp_msg);
	int (*jpeg_encode) (void *isp_msg);
	int (*use_mem_pool) (void *isp_msg);
	int (*unmap_buffer) (void *isp_msg);
	int (*set_cal_data) (void *isp_msg);
	int (*set_isp_regs) (void *isp_msg);
	int (*get_isp_regs) (void *isp_msg);
	int (*set_i2c_regs) (void *isp_msg);
	int (*get_i2c_regs) (void *isp_msg);
	int (*test_case_interface) (void *isp_msg);
	int (*flush) (void *isp_msg);
	int (*extend_set) (void *isp_msg);
	int (*extend_get) (void *isp_msg);
	int (*inv_tlb) (void *isp_msg);
	int (*query_ois_update) (void *isp_msg);
	int (*ois_update) (void *isp_msg);
	int (*query_laser) (void *isp_msg);
	int (*acquire_laser) (void *isp_msg);
	int (*release_laser) (void *isp_msg);
	int (*acquire_depthisp) (void *isp_msg);
	int (*release_depthisp) (void *isp_msg);
	int (*req_get_cap) (void *isp_msg);
	int (*msg_event) (void *isp_msg);
	int (*msg_log) (void *isp_msg);
	int (*demap_map_request) (void *isp_msg);
	int (*demap_unmap_request) (void *isp_msg);
	int (*dgen_flush_request) (void *isp_msg);
	int (*dopt_flush_request) (void *isp_msg);
	int (*dmap_format_request) (void *isp_msg);

} simulated_fw_msg_pro_t;

typedef struct _tag_simulated_fw_intf {
	simulated_fw_msg_pro_t *msg_pro;
} simulated_fw_intf_t;

typedef struct _tag_simulated_fw {
	simulated_fw_intf_t intf;
	struct task_struct *thread;
	struct rpmsg_driver rpmsg;
	struct rpmsg_channel rpdev;
	struct mutex num_lock;
	wait_queue_head_t done_wq;
	int msg_num;
	int algo_info;/* 0-HDR,1-superzoom */
	hisp_msg_t *msg_base;
	hisp_msg_t *msg_read;
	hisp_msg_t *msg_write;
} simulated_fw_t;

int message_manager(buffer_md_t *p_buffer_md_g, simulated_fw_t
		    s_simulated_fw_g, char *previewBuf);

extern int simulated_fw_rproc_device_enable(void);

extern int simulated_fw_rproc_device_disable(void);

extern int simulated_set_algo_info(int algoInfo);

#endif /* __simulated_FIRMWARE_INTERFACE__ */
