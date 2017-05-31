/*
 *  Hisilicon K3 SOC camera driver source file
 *
 *  Copyright (C) Huawei Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <linux/delay.h>
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
#include <linux/syscalls.h>
#include "../../../cam_log.h"
#include "../simulated_fw.h"
#include "../metadata/isp_metadata.h"
#include "../metadata/isp_metadata_vendor_tag.h"
#include "../metadata/simulated_metadata.h"
#include "sensor/simulated_cis_imx214_sunny.h"
#include "sensor/simulated_cis_t4ka3.h"
#include "sensor/simulated_cis_imx286dual.h"
#include "sensor/simulated_cis_imx179_4l.h"
#include "../imagefile/simulated_file_utils.h"

extern void *get_kernel_map_addr(int iova);

LIST_HEAD(recv_msg_main);

LIST_HEAD(recv_msg_sub);

/*
 * Global variable of Module parameters
 */
buffer_md_t *g_p_buffer_md;
char *g_preview_yuv_data;
/* struct ion_client *g_pSimulateClient = NULL; */
simulated_fw_t g_simulated_fw_r;

typedef struct _tag_simulated_fw_camera_info_t {
	unsigned int handle;
	unsigned int camera_id;
	char match_name[32];
	char sensor_name[32];
	camera_status_e status;
	msg_req_usecase_config_t usecase_config;
	int (*get_capability) (isp_metadata_t *p_metadata);
} simulated_fw_camera_info_t;

/*
 * Current camera informations.
 */
simulated_fw_camera_info_t simulated_fw_camera_info[] = {
	{
	 .handle = 0,
	 .camera_id = 0,
	 .match_name = "IMX286HYBIRD",
	 .sensor_name = "IMX286DUALHYBIRD_SUNNY",
	 .status = CAMERA_CLOSED,
	 .get_capability = imx286dual_cis_get_capability,
	 .usecase_config = {0},
	 },
	{
	 .handle = 0,
	 .camera_id = 1,
	 .match_name = "IMX179_4L_FOXCONN",
	 .sensor_name = "IMX179_4L_FOXCONN",
	 .status = CAMERA_CLOSED,
	 .get_capability = imx179_4l_cis_get_capability,
	 .usecase_config = {0},
	 },
	{
	 .handle = 0,
	 .camera_id = 2,
	 .match_name = "IMX286HYBIRD",
	 .sensor_name = "IMX286DUALHYBIRD_SUNNY",
	 .status = CAMERA_CLOSED,
	 .get_capability = imx286dual_cis_get_capability,
	 .usecase_config = {0},
	 },
};

static void init_isp_metada(buffer_md_t *buffer_md)
{
	/* raw_size_info */
	buffer_md->common_info.raw_width = 4160;
	buffer_md->common_info.raw_height = 3120;
	/*raw_pattern
	buffer_md->raw_pattern = BAYER_RGGB;
	p_buffer_md->blc_md.reserved[] = {
	0, 0, 0, 0};
	*/
	/* stat_3a */
	/* awb_stat ... */
	buffer_md->stat_3a.awb_stat.green_count = 14;
	buffer_md->stat_3a.awb_stat.green_gravity_bg = 333;
	buffer_md->stat_3a.awb_stat.green_count = 14;
	/* monitor_result */
	buffer_md->monitor_result.sensor_err_code = 0;
	buffer_md->monitor_result.vcm_err_code = 0;
	buffer_md->monitor_result.ois_err_code = 0;
	buffer_md->monitor_result.cam_id = 0;
	/* p_buffer_md->monitor_result.reserved[]={0}; */

	buffer_md->laser_md.err_code = 0;
	/* cc_md ... */

	/* ANDROID_HW_INTERNAL_CROP_REGION */
	buffer_md->crop_region.x = 0;
	buffer_md->crop_region.y = 4160;
	buffer_md->crop_region.width = 3120;
	buffer_md->crop_region.height = 508;
	/* ANDROID_HISTAR_COMMON_STAT3A */
	buffer_md->af_md.af_mmi_7cm_report = 0;
	buffer_md->af_md.af_mmi_pdaf_report = 0;
	buffer_md->af_md.af_detailed_info.report = 0;
	/* AF INFO */

	buffer_md->stat_3a.awb_stat.green_count = 14;
	buffer_md->stat_3a.awb_stat.green_gravity_bg = 333;
	buffer_md->stat_3a.awb_stat.green_count = 14;

	buffer_md->af_md.af_ctrl_mode = 1;
	buffer_md->af_md.af_ctrl_state = 4;
	buffer_md->af_md.af_ctrl_trigger_id = 2;
	buffer_md->af_md.af_ctrl_cur_code = 436;
	buffer_md->af_md.af_ctrl_cur_virtual_code = 1023;
	/* AE INFO */
	buffer_md->ae_md.exposure_param.iso = 431;
	buffer_md->ae_md.exposure_param.expo = 40000;
	buffer_md->ae_md.exposure_param.aver_lum = 36;
	buffer_md->ae_md.exposure_param.stable = 1;
	buffer_md->ae_md.exposure_param.gain = 2207;
	buffer_md->ae_md.exposure_param.expo_max = 83333;
	buffer_md->ae_md.exposure_param.expo_min = 30;
	buffer_md->ae_md.exposure_param.gain_max = 16384;
	buffer_md->ae_md.exposure_param.gain_min = 256;
	buffer_md->ae_md.exposure_param.lum_max = 33;
	buffer_md->ae_md.exposure_param.lum_min = 33;
	buffer_md->ae_md.exposure_param.banding_type = 0;
	buffer_md->ae_md.exposure_param.fps = 12;
	buffer_md->ae_md.exposure_param.EI_value = -474;
	buffer_md->ae_md.exposure_param.sae_expo_comp = 0;
	buffer_md->ae_md.exposure_param.report_ev_diff = 0;
	buffer_md->ae_md.exposure_param.ae_lock = 0;
	buffer_md->ae_md.exposure_param.curr_lum = 37;
	buffer_md->ae_md.exposure_param.expo_value = 16774;

	buffer_md->flash_md.ae_state = 2;
	buffer_md->flash_md.ae_precapture_id = 0;
	/* p_buffer_md->flash_md.preflash_state = 0; */
	buffer_md->flash_md.need_lcd_compension = 0;
	buffer_md->flash_md.flash_state = 2;
	buffer_md->flash_md.capflash_ae_effect = 0;
	buffer_md->flash_md.resume_ae_doing = 0;
	/* AWB INFO */
	buffer_md->awb_md.wb_gain_param.R_gain = 1728;
	buffer_md->awb_md.wb_gain_param.R_gain = 2606;
	buffer_md->awb_md.wb_gain_param.Gr_gain = 1092;
	buffer_md->awb_md.wb_gain_param.Gb_gain = 1092;
	buffer_md->awb_md.CCT_value = 3361;
}

int simulated_fw_query_capability(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	int i = 0;
	int cmp = 0;
	int cmp_match = 0;
	int len = 0;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;
	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = QUERY_CAPABILITY_RESPONSE;
	cam_info("%s , req sensor id is:%d", __func__,
		 isp_msg->u.req_query_capability.cam_id);
	cam_info("%s , req sensor name is:%s", __func__,
		 isp_msg->u.req_query_capability.sensor_name);
	int name_len = strlen(isp_msg->u.req_query_capability.sensor_name);
	isp_msg_ack.u.ack_query_capability.status = -1;
	/* Do something. */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		cmp = strcmp(simulated_fw_camera_info[i].sensor_name,
			     (isp_msg->u.req_query_capability.sensor_name));

		cmp_match = strcmp(simulated_fw_camera_info[i].match_name,
			     (isp_msg->u.req_query_capability.sensor_name));
		if ((isp_msg->u.req_query_capability.cam_id ==
		     simulated_fw_camera_info[i].camera_id) &&
		    ((0 == name_len) || (0 == cmp) || (cmp_match))) {
			len = strlen(simulated_fw_camera_info[i].sensor_name);
			strncpy(isp_msg_ack.u.ack_query_capability.sensor_name,
				simulated_fw_camera_info[i].sensor_name,
				len + 1);
			isp_msg_ack.u.ack_query_capability.cam_id =
			    simulated_fw_camera_info[i].camera_id;
			len =
			    strlen(isp_msg_ack.u.
				   req_query_capability.product_name);
			strncpy(isp_msg_ack.u.ack_query_capability.product_name,
				isp_msg_ack.u.req_query_capability.product_name,
				len + 1);
		} else {
			continue;
		}

		if (isp_msg->u.req_query_capability.input_settings_buffer == 0) {
			isp_msg_ack.u.
			    ack_query_capability.output_metadata_buffer = 0;
		} else {
			void *vaddr;
			vaddr =
			    get_kernel_map_addr(isp_msg->u.
						req_query_capability.input_settings_buffer);
			cam_info
			    ("%s().get_kernel_map_addr, iova: 0x%x, map_kernel_addr: 0x%x",
			     __func__,
			     isp_msg->u.
			     req_query_capability.input_settings_buffer, vaddr);
			int retm = 0;
			isp_metadata_t *p_metadata;
			p_metadata =
			    isp_metadata_create(vaddr, METADATA_BUFFER_SIZE);

			for (i = 0; i < ARRAY_SIZE(querey_cap_list); i++) {
				retm =
				    (querey_cap_list[i].handler) (isp_msg,
								  p_metadata);
				cam_info("test query_cap_list %d .", retm);
				if (0 != retm) {
					cam_info
					    ("Have not get the test query_cap_list, cmd_id = %d, rlt = %d.",
					     querey_cap_list[i].cmd_id, retm);
				}
			}
			retm =
			    simulated_fw_camera_info[isp_msg_ack.
						     u.ack_query_capability.cam_id].get_capability
			    (p_metadata);
			if (0 != retm) {
				cam_info("Have not get the sensor capability");
			}
			/* isp_metadata_dump(p_metadata); */
			isp_metadata_destroy(&p_metadata);
			isp_msg_ack.u.
			    ack_query_capability.output_metadata_buffer =
			    (unsigned int)isp_msg->u.
			    req_query_capability.input_settings_buffer;

		}
		isp_msg_ack.u.ack_query_capability.status = 0;
		break;
	}
	cam_info("%s , sensor name is:%s", __func__,
		 isp_msg_ack.u.ack_query_capability.sensor_name);
	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

/*
 * Open the camera.
 * @isp_msg: hisp message of open parameters.
 *
 * If input sensor_name of req_release_camera isn't empty,
 * then driver campare input sensor_name with camera informations.
 * else driver copy sensor_name of camera informations to input sensor_name.
 */
int simulated_fw_acquire_camera(void *isp_msg_r)
{
	int ret = 0;
	int i = 0;
	int cmp = 0;
	int len;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;
	hisp_msg_t isp_msg_ack;
	int name_len = strlen(isp_msg->u.req_acquire_camera.sensor_name);

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = ACQUIRE_CAMERA_RESPONSE;
	
	cam_info("%s , req camera id:%u name:%s", __func__,
		 isp_msg->u.req_acquire_camera.cam_id,
		 isp_msg->u.req_acquire_camera.sensor_name);
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		/*
		 * Try to find matched camera name
		 * from current camera informations.
		 */
		cmp = strcmp(simulated_fw_camera_info[i].sensor_name,
			     (isp_msg->u.req_acquire_camera.sensor_name));

		if ((isp_msg->u.req_acquire_camera.cam_id ==
		     simulated_fw_camera_info[i].camera_id) &&
		    ((0 == name_len) || (0 == cmp))) {
			
			simulated_fw_camera_info[i].status = CAMERA_OPENED;
			len = strlen(simulated_fw_camera_info[i].sensor_name);
			strncpy(isp_msg_ack.u.ack_require_camera.sensor_name,
				simulated_fw_camera_info[i].sensor_name,
				len + 1);

			cam_info
			    ("%s , camera id:%u name:%s,save_name=%s. api_name = %d",
			     __func__, isp_msg->u.req_acquire_camera.cam_id,
			     isp_msg->u.req_acquire_camera.sensor_name,
			     isp_msg_ack.u.ack_require_camera.sensor_name,
			     isp_msg_ack.api_name);

			break;
		}
	}

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

/*
 * Close the camera.
 * @isp_msg: hisp message of close parameters.
 */
int simulated_fw_release_camera(void *isp_msg_r)
{
	int i = 0;
	int ret = 0;
	int index = -1;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;
	hisp_msg_t isp_msg_ack;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = RELEASE_CAMERA_RESPONSE;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_release_camera.cam_id ==
		    simulated_fw_camera_info[i].camera_id) {
			index = i;
			break;
		}
	}

	if (index >= 0) {
		if (simulated_fw_camera_info[index].status == CAMERA_OPENED) {
			simulated_fw_camera_info[index].status = CAMERA_CLOSED;
			isp_msg_ack.u.ack_release_camera.cam_id
			    = simulated_fw_camera_info[index].camera_id;
		} else {
			cam_err("%s error, camera id:%d not opened.",
				__func__, isp_msg->u.req_release_camera.cam_id);
		}
	} else {
		cam_err("%s error, camera id:%d not index.",
			__func__, isp_msg->u.req_release_camera.cam_id);
	}

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

/*
 * Calculate stream buffer size
 */

static unsigned int get_stream_buffer_size(unsigned int width,
					   unsigned int height,
					   unsigned int format)
{
	unsigned int size = 0;
	cam_debug("%s(%u)", __func__, __LINE__);

	switch (format) {
		/* Raw stream buffer size */
	case PIXEL_FMT_RAW10:
	case PIXEL_FMT_RAW12:
	case PIXEL_FMT_RAW14:
		size = width * height * 2;
		break;
		/* Jpeg stream buffer size */
	case PIXEL_FMT_JPEG:
		size = ((width * height * 3) >> 1);
		break;
		/* YUV422 stream buffer size */
	case PIXEL_FMT_YUV422_UYVY:
	case PIXEL_FMT_YUV422_VYUY:
	case PIXEL_FMT_YUV422_YUYV:
	case PIXEL_FMT_YUV422_YVYU:
		size = width * height * 2;
		break;
		/* YUV420_NV12 stream buffer size */
	case PIXEL_FMT_YUV420_NV12:
		size = ((width * height * 3) >> 1);
		break;
		/* YUV420_NV21 stream buffer size */
	case PIXEL_FMT_YUV420_NV21:
		size = ((width * height * 3) >> 1);
		break;
	case PIXEL_FMT_MONOCHROME:
	case PIXEL_FMT_Y8:
		size = width * height;
		break;
	default:
		size = 0;
		break;
	}

	return size;
}

/*
 * usecase config buffers.
 * @isp_msg: hisp message of usecase config parameters.
 */
int simulated_fw_usecase_config(void *isp_msg_r)
{
	int ret = 0;
	int i = 0;
	int index = -1;
	int buf_size = 0;
	int color_delta = 0x55;
	int temp_camid = 0;
	int temp_width = 0;
	int temp_height = 0;
	int temp_format = 0;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;
	hisp_msg_t isp_msg_ack;
	stream_config_t stream_cfg;
	msg_ack_usecase_config_t *config = NULL;
	isp_msg_ack = *isp_msg;

	isp_msg_ack.api_name = USECASE_CONFIG_RESPONSE;
	config = &(isp_msg_ack.u.ack_usecase_config);
	config->status = -1;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_usecase_config.cam_id ==
		    simulated_fw_camera_info[i].camera_id) {
			index = i;
			break;
		}
	}

	if (index >= 0) {
		/* Packet ack usecase config parameters. */
		if (simulated_fw_camera_info[index].status == CAMERA_OPENED) {
			simulated_fw_camera_info[index].usecase_config =
			    isp_msg->u.req_usecase_config;
			config->sensor_width = 0;
			config->sensor_height = 0;
			for (i = 0; i < MAX_STREAM_NUM; i++) {
				cam_info
				    ("%s,stream %d info: type:%d, format:%d, sensor_width:%d,sensor_height:%d",
				     __func__, i,
				     simulated_fw_camera_info
				     [index].usecase_config.stream_cfg[i].type,
				     simulated_fw_camera_info
				     [index].usecase_config.stream_cfg[i].
				     format,
				     simulated_fw_camera_info
				     [index].usecase_config.stream_cfg[i].width,
				     simulated_fw_camera_info
				     [index].usecase_config.stream_cfg[i].
				     height);

				if (simulated_fw_camera_info
				    [index].usecase_config.stream_cfg[i].width >
				    config->sensor_width
				    &&
				    simulated_fw_camera_info
				    [index].usecase_config.stream_cfg[i].
				    height > config->sensor_height) {
					config->sensor_width =
					    simulated_fw_camera_info
					    [index].usecase_config.
					    stream_cfg[i].width;
					config->sensor_height =
					    simulated_fw_camera_info
					    [index].usecase_config.
					    stream_cfg[i].height;
				}
			}
			cam_info("%s, max sensor width, height: %d, %d" , __func__, config->sensor_width, config->sensor_height);
			temp_camid = simulated_fw_camera_info[index].camera_id;
			temp_width =
			    simulated_fw_camera_info[index].
			    usecase_config.stream_cfg
			    [STREAM_ISP_YUV_OUT_PREVIEW].width;
			temp_height =
			    simulated_fw_camera_info[index].
			    usecase_config.stream_cfg
			    [STREAM_ISP_YUV_OUT_PREVIEW].height;
			temp_format =
			    simulated_fw_camera_info[index].
			    usecase_config.stream_cfg
			    [STREAM_ISP_YUV_OUT_PREVIEW].format;
			buf_size =
			    get_stream_buffer_size(temp_width, temp_height,
						   temp_format);

			if (buf_size > 0) {
				if (NULL == g_preview_yuv_data) {
					cam_err
					    ("%s g_preview_yuv_data kzalloc fail \n!",
					     __func__);
				} else {
					ret =
					    load_preview_yuv_data(temp_camid,
								  g_preview_yuv_data,
								  buf_size,
								  temp_width,
								  temp_height);
					if (ret < 0) {
						cam_err
						    ("%s load_preview_yuv_data error\n",
						     __func__);
						static unsigned char num;
						num = num + color_delta;
						memset(g_preview_yuv_data, num,
						       buf_size);
					}
				}
			}

			config->status = 0;

			config->cam_id =
			    simulated_fw_camera_info[index].camera_id;
		} else {
			cam_err("%s error, camera id:%d not opened.", __func__,
				isp_msg->u.req_usecase_config.cam_id);
		}
	} else {
		cam_err("%s error, camera id:%d not index.",
			__func__, isp_msg->u.req_usecase_config.cam_id);
	}

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);

	cam_info("exit %s(%u)", __func__, __LINE__);
	config = NULL;
	return ret;
}

int simulated_fw_stream_on(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;

	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;
	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = STREAM_ON_RESPONSE;

	isp_msg_ack.u.ack_stream_on.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_get_otp(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;

	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;
	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = GET_OTP_RESPONSE;

	isp_msg_ack.u.ack_get_otp.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

/*
 * Fill output buffer.
 * @in_addr   : address of input buffer.
 * @in_config : config of input buffer.
 * @out_addr  : address of output buffer.
 * @out_config: config of output buffer.
 */
static int fill_output_buffer(unsigned long in_addr,
			      stream_config_t *in_config,
			      unsigned long out_addr,
			      stream_config_t *out_config)
{
	int ret = 0;
	cam_debug("enter %s(%u)", __func__, __LINE__);

	/*
	 * The buffer address is actually a physical buffer,
	 * so driver won't be able to write it directly.
	 * Do nothing in driver for now.
	 */
	int size = 50;

	if (in_addr > 0) {
		memcpy(out_addr, in_addr, size);
		memcpy(out_addr, in_config, sizeof(stream_config_t));
		memcpy((stream_config_t *)
		       ((unsigned long)out_addr + sizeof(stream_config_t)),
		       out_config, sizeof(stream_config_t));
	} else {
		memset(out_addr, 0, size);
		memcpy((stream_config_t *)
		       ((unsigned long)out_addr + sizeof(stream_config_t)),
		       out_config, sizeof(stream_config_t));
	}

	cam_debug("exit %s(%u)", __func__, __LINE__);

	return ret;
}

/*
 * Request buffers.
 * @isp_msg: hisp message of request parameters.
 */
int simulated_fw_request(void *isp_msg_r)
{
	int ret = 0;
	int i = 0;
	int index = -1;
	unsigned int preview_buffer_size = 0;
	unsigned int color_delta = 0x55;
	unsigned long input_addr = 0;
	unsigned long output_addr = 0;
	stream_config_t *intput_config = NULL;
	stream_config_t *output_config = NULL;
	msg_req_usecase_config_t *usecase_config = NULL;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;
	hisp_msg_t isp_msg_ack;

	msg_ack_request_t *ack_req = &isp_msg_ack.u.ack_request;
	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = REQUEST_RESPONSE;
	ack_req->frame_number = isp_msg->u.req_request.frame_number;

	cam_info("%s enter,camID %d frame num:%d", __func__,
		 isp_msg->u.req_request.cam_id, ack_req->frame_number);
	ack_req->input_setting_buffer =
	    isp_msg->u.req_request.output_metadata_buffer;
	ack_req->output_metadata_buffer =
	    isp_msg->u.req_request.output_metadata_buffer;
	void *buffer_vaddr = NULL;
	ack_req->input_setting_buffer =
	    isp_msg->u.req_request.input_setting_buffer;
	cam_debug("%s enter,input_setting_buffer:%d", __func__,
		  ack_req->input_setting_buffer);

	if (ack_req->input_setting_buffer != 0) {
		buffer_vaddr =
		    get_kernel_map_addr(isp_msg->u.
					req_request.input_setting_buffer);
		/* cam_info("%s().get_kernel_map_addr, iova: 0x%x, map_kernel_addr: 0x%x",
		   __func__, isp_msg->u.req_request.input_setting_buffer, buffer_vaddr); */
		isp_metadata_t *p_inputmetadata;
		p_inputmetadata =
		    isp_metadata_create(buffer_vaddr, METADATA_BUFFER_SIZE);
		/* isp_metadata_dump(p_inputmetadata); */
		isp_metadata_destroy(&p_inputmetadata);
		p_inputmetadata = NULL;
		buffer_vaddr = NULL;
	}

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_request.cam_id ==
		    simulated_fw_camera_info[i].camera_id) {
			index = i;
			break;
		}
	}
       //cppcheck-suppress *
	usecase_config = &(simulated_fw_camera_info[index].usecase_config);
	if (index >= 0) {
		if (simulated_fw_camera_info[index].status == CAMERA_CLOSED) {
			cam_err("%s error, camera id:%d not opened.", __func__,
				isp_msg->u.req_release_camera.cam_id);
			goto out;
		}
		/* cam_info("%s,stream_nr:%u target_map:0x%x", __func__,
		   usecase_config->stream_nr, isp_msg->u.req_request.target_map); */
		/*
		 * Try to find input stream buffer
		 * from request parameters.
		 */
		ack_req->num_targets = 0;
		ack_req->target_map = 0;
		i = 0;
		while (i < MAX_STREAM_NUM) {
			if ((isp_msg->u.req_request.target_map >> i) & 0x1) {
				/* cam_info("%s,request[%u] type:%u, addr:0x%x", __func__, i,
				   usecase_config->stream_cfg[i].type, isp_msg->u.req_request.buf[i]); */
				if (usecase_config->stream_cfg[i].type ==
				    STREAM_TYPE_INPUT) {
					input_addr =
					    isp_msg->u.req_request.buf[i];
					/* cam_info("%s enter, input addr 0x%x", __func__, input_addr); */
					if (0 == input_addr) {
						cam_alert
						    ("%s error, read buffer:0",
						     __func__);
						goto out;
					} else {
						/* buffer_vaddr = get_kernel_map_addr(input_addr); */
						/* cam_info("%s().get_kernel_map_addr, iova: 0x%x,
						   map_kernel_addr: 0x%x", __func__, input_addr, buffer_vaddr); */
						buffer_vaddr = NULL;
					}
				} else
				    if ((usecase_config->stream_cfg[i].type ==
					 STREAM_TYPE_OUTPUT)) {
					output_addr =
					    isp_msg->u.req_request.buf[i];
					/* cam_info("%s enter, output addr 0x%x", __func__, output_addr); */
					if (0 == output_addr) {
						cam_info
						    ("%s error, read buffer:0",
						     __func__);
						goto out;
					}

					output_config =
					    &(usecase_config->stream_cfg[i]);
					cam_info("%s enter, output addr 0x%x",
						 __func__, output_addr);
					buffer_vaddr =
					    get_kernel_map_addr(output_addr);
					cam_info
					    ("%s().get_kernel_map_addr, iova: 0x%x, map_kernel_addr: 0x%x",
					     __func__, output_addr,
					     buffer_vaddr);
					ack_req->stream_info[i].valid = 1;
					ack_req->stream_info[i].buffer =
					    isp_msg->u.req_request.buf[i];
					ack_req->stream_info[i].width =
					    simulated_fw_camera_info
					    [index].usecase_config.
					    stream_cfg[i].width;
					ack_req->stream_info[i].height =
					    simulated_fw_camera_info
					    [index].usecase_config.
					    stream_cfg[i].height;
					ack_req->stream_info[i].format =
					    simulated_fw_camera_info
					    [index].usecase_config.
					    stream_cfg[i].format;
					ack_req->stream_info[i].frame_num =
					    isp_msg->u.req_request.frame_number;
					ack_req->stream_info[i].stride =
					    simulated_fw_camera_info
					    [index].usecase_config.
					    stream_cfg[i].stride;
					if (i == STREAM_ISP_YUV_OUT_PREVIEW) {
						preview_buffer_size =
						    get_stream_buffer_size
						    (ack_req->
						     stream_info[i].width,
						     ack_req->
						     stream_info[i].height,
						     ack_req->
						     stream_info[i].format);
						if (NULL != g_preview_yuv_data) {
							memcpy(buffer_vaddr,
							       g_preview_yuv_data,
							       preview_buffer_size);
						}
					} else if ((i == STREAM_REP_YUV_OUT)
						   || (i ==
						       STREAM_ISP_YUV_OUT_VIDEO)){
						preview_buffer_size =
						    get_stream_buffer_size
						    (ack_req->
						     stream_info[i].width,
						     ack_req->
						     stream_info[i].height,
						     ack_req->
						     stream_info[i].format);
						load_capture_yuv_data
						    (isp_msg->u.req_release_camera.cam_id,
						     buffer_vaddr,
						     preview_buffer_size,
						     ack_req->stream_info[i].
						     width,
						     ack_req->stream_info
						     [i].height);
					} else {
						/* to do */
					}

					buffer_vaddr = NULL;
				} else {
					cam_info("bad stream type");
					goto out;
				}
				ack_req->num_targets++;
				ack_req->target_map |= (0x1 << i);
			}
			i++;
		}
		/* fill out put_metabuffer */
		if (ack_req->output_metadata_buffer != 0) {
			buffer_vaddr =
			    get_kernel_map_addr
			    (ack_req->output_metadata_buffer);
			isp_metadata_t *p_metadata;

			p_metadata =
			    isp_metadata_create(buffer_vaddr,
						METADATA_BUFFER_SIZE);

			isp_metadata_set(p_metadata,
					 ANDROID_HISTAR_BUFFER_METADATA,
					 g_p_buffer_md, sizeof(int),
					 sizeof(*g_p_buffer_md) / sizeof(int));

			/* isp_metadata_dump(p_metadata); */

			isp_metadata_destroy(&p_metadata);
			p_metadata = NULL;
			buffer_vaddr = NULL;
		}

		cam_debug("%s,num_targets:%u target_map:%u", __func__,
			  ack_req->num_targets, ack_req->target_map);
	} else {
		cam_err("%s error, camera id:%d not index.", __func__,
			isp_msg->u.req_release_camera.cam_id);
	}

	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;

out:
	cam_debug("%s, num_targets:%u, target_map:0x%x", __func__,
		  ack_req->num_targets, ack_req->target_map);
	return -1;
}

int simulated_fw_warp_request(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = WARP_REQUEST_RESPONSE;

	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_arsr_request(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = ARSR_REQUEST_RESPONSE;

	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_dgen_request(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = DGEN_REQUEST_RESPONSE;
	isp_msg_ack.u.ack_dgen_request.output_disp_buffer =
	    isp_msg->u.req_dgen_request.output_disp_fw_addr;
	isp_msg_ack.u.ack_dgen_request.output_conf_buffer =
	    isp_msg->u.req_dgen_request.output_conf_fw_addr;
	isp_msg_ack.u.ack_dgen_request.output_left_raster =
	    isp_msg->u.req_dgen_request.output_left_raster;
	isp_msg_ack.u.ack_dgen_request.input_left_buffer =
	    isp_msg->u.req_dgen_request.input_left_buffer;
	isp_msg_ack.u.ack_dgen_request.input_right_buffer =
	    isp_msg->u.req_dgen_request.input_right_buffer;
	isp_msg_ack.u.ack_dgen_request.base_img =
	    isp_msg->u.req_dgen_request.base_img;
	isp_msg_ack.u.ack_dgen_request.frame_number =
	    isp_msg->u.req_dgen_request.frame_number;
	isp_msg_ack.u.ack_dgen_request.req_type =
	    isp_msg->u.req_dgen_request.req_type;
	isp_msg_ack.u.ack_dgen_request.status = 0;

	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_dopt_request(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = DOPT_REQUEST_RESPONSE;
	isp_msg_ack.u.ack_dopt_request.base_img =
	    isp_msg->u.req_dopt_request.base_img;
	isp_msg_ack.u.ack_dopt_request.frame_number =
	    isp_msg->u.req_dopt_request.frame_number;
	isp_msg_ack.u.ack_dopt_request.req_type =
	    isp_msg->u.req_dopt_request.req_type;
	isp_msg_ack.u.ack_dopt_request.output_disp_buffer =
	    isp_msg->u.req_dopt_request.output_disp_buffer;
	isp_msg_ack.u.ack_dopt_request.input_horz_left_image =
	    isp_msg->u.req_dopt_request.input_horz_left_image;
	isp_msg_ack.u.ack_dopt_request.input_vert_left_image =
	    isp_msg->u.req_dopt_request.input_vert_left_image;
	isp_msg_ack.u.ack_dopt_request.input_raster_disp_buffer =
	    isp_msg->u.req_dopt_request.input_raster_disp_buffer;
	isp_msg_ack.u.ack_dopt_request.input_last_left_buffer =
	    isp_msg->u.req_dopt_request.input_last_left_buffer;
	isp_msg_ack.u.ack_dopt_request.input_last_disp_buffer =
	    isp_msg->u.req_dopt_request.input_last_disp_buffer;
	isp_msg_ack.u.ack_dopt_request.status = 0;

	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_jpeg_encode(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = JPEG_ENCODE_RESPONSE;

	isp_msg_ack.u.ack_jpeg_encode.status = 0;

	isp_msg_ack.u.ack_jpeg_encode.output_buffer =
	    isp_msg->u.req_jpeg_encode.output_buffer;
	isp_msg_ack.u.ack_jpeg_encode.filesize = 0;
	isp_msg_ack.u.ack_jpeg_encode.status = 0;

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_use_mem_pool(void *isp_msg_r)
{
	int ret = 0;
	int i = 0;
	int index = -1;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = MAP_BUFFER_RESPONSE;

	isp_msg_ack.u.ack_map_buffer.status = -1;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_map_buffer.cam_id ==
		    simulated_fw_camera_info[i].camera_id) {
			index = i;
			break;
		}
	}
	if (index >= 0) {
		isp_msg_ack.u.ack_map_buffer.status = 0;
	} else {
		cam_err("%s error, camera id:%d not index.",
			__func__, isp_msg->u.req_map_buffer.cam_id);
	}

	cam_info("%s() map status is %d", __func__,
		 isp_msg_ack.u.ack_map_buffer.status);

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_unmap_buffer(void *isp_msg_r)
{
	int ret = 0;
	int i = 0;
	int index = -1;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = UNMAP_BUFFER_RESPONSE;

	isp_msg_ack.u.ack_unmap_buffer.status = -1;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_unmap_buffer.cam_id ==
		    simulated_fw_camera_info[i].camera_id) {
			index = i;
			break;
		}
	}

	if (index >= 0) {
		if (simulated_fw_camera_info[index].status == CAMERA_OPENED) {

			/* Do something. */

			isp_msg_ack.u.ack_unmap_buffer.status = 0;
		} else {
			cam_err("%s error, camera id:%d not opened.",
				__func__, isp_msg->u.req_unmap_buffer.cam_id);
		}
	} else {
		cam_err("%s error, camera id:%d not index.",
			__func__, isp_msg->u.req_unmap_buffer.cam_id);
	}

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_set_cal_data(void *isp_msg_r)
{

	int ret = 0;
	int i = 0;
	int index = -1;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = CALIBRATION_DATA_RESPONSE;

	isp_msg_ack.u.ack_cal_data.status = -1;

	/*
	 * Try to find matched camera handle
	 * from current camera informations.
	 */
	for (i = 0; i < MAX_ACQUIRE_CAMERA_NUM; i++) {
		if (isp_msg->u.req_cal_data.cam_id ==
		    simulated_fw_camera_info[i].camera_id) {
			index = i;
			break;
		}
	}

	if (index >= 0) {
		if (simulated_fw_camera_info[index].status == CAMERA_OPENED) {

			/* Do something */

			isp_msg_ack.u.ack_cal_data.status = 0;
		} else {
			cam_err("%s error, camera id:%d not opened.",
				__func__, isp_msg->u.req_cal_data.cam_id);
		}
	} else {
		cam_err("%s error, camera id:%d not index.", __func__,
			isp_msg->u.req_cal_data.cam_id);
	}

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_set_isp_regs(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = SET_ISP_REGISTERS_RESPONSE;

	isp_msg_ack.u.ack_set_isp_regs.status = 0;

	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_get_isp_regs(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = GET_ISP_REGISTER_RESPONSE;

	isp_msg_ack.u.ack_get_isp_regs.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_set_i2c_regs(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = SET_IIC_REGISTER_RESPONSE;

	isp_msg_ack.u.ack_set_i2c_regs.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_get_i2c_regs(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = GET_IIC_REGISTER_RESPONSE;

	isp_msg_ack.u.ack_get_i2c_regs.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_test_case_interface(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = TEST_CASE_RESPONSE;

	isp_msg_ack.u.ack_test_case_interface.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_flush(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = FLUSH_RESPONSE;

	isp_msg_ack.u.ack_flush.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_extend_set(void *isp_msg_r)
{
	int i = 0;
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;
	capture_params_t  *tmp_capture_params_t = NULL;
	int tmp_cam_id = 0;

	if (isp_msg->u.req_extend_set.extend_cmd == SUBCMD_START_CAPTURE) {
		tmp_capture_params_t = (capture_params_t*)isp_msg->u.req_extend_set.paras;

		for (i = 0; i < tmp_capture_params_t->streams.count; i++) {
			tmp_cam_id = tmp_capture_params_t->streams.info[i].cam_id;
			simulated_fw_camera_info[tmp_cam_id].usecase_config.stream_cfg[STREAM_REP_YUV_OUT].height
				= tmp_capture_params_t->streams.info[i].resolution.height;
			simulated_fw_camera_info[tmp_cam_id].usecase_config.stream_cfg[STREAM_REP_YUV_OUT].width
				= tmp_capture_params_t->streams.info[i].resolution.width;
			cam_info(" height, width: %d, %d",simulated_fw_camera_info[tmp_cam_id].usecase_config.stream_cfg[STREAM_REP_YUV_OUT].height,
					simulated_fw_camera_info[tmp_cam_id].usecase_config.stream_cfg[STREAM_REP_YUV_OUT].width);
			cam_info(" height, width: %u, %u",tmp_capture_params_t->streams.info[i].resolution.height,
					tmp_capture_params_t->streams.info[i].resolution.width);
		}
	}

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = EXTEND_SET_RESPONSE;

	isp_msg_ack.u.ack_extend_set.status = 0;
	/* Do something. */
	isp_msg_ack.u.ack_extend_set.cam_id = isp_msg->u.req_extend_set.cam_id;
	isp_msg_ack.u.ack_extend_set.extend_cmd =
	    isp_msg->u.req_extend_set.extend_cmd;
	cam_info("%s enter, extend cmd:ox%x", __func__,
		 isp_msg->u.req_extend_set.extend_cmd);
	isp_msg_ack.u.ack_extend_set.status = 0;
	memset(isp_msg_ack.u.ack_extend_set.ack_info, 0,
	       sizeof(isp_msg_ack.u.ack_extend_set.ack_info));
	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_extend_get(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = EXTEND_GET_RESPONSE;

	isp_msg_ack.u.ack_extend_get.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_inv_tlb(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = INV_TLB_RESPONSE;

	isp_msg_ack.u.ack_inv_tlb.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_query_ois_update(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = QUERY_OIS_UPDATE_RESPONSE;

	isp_msg_ack.u.ack_query_ois_update.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_ois_update(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = OIS_UPDATE_RESPONSE;

	isp_msg_ack.u.ack_ois_update.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_query_laser(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = QUERY_LASER_RESPONSE;

	isp_msg_ack.u.ack_query_laser.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_acquire_laser(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = ACQUIRE_LASER_RESPONSE;

	isp_msg_ack.u.ack_require_laser.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_release_laser(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = RELEASE_LASER_RESPONSE;

	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_acquire_depth(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = ACQUIRE_DEPTHISP_RESPONSE;

	isp_msg_ack.u.ack_require_depthisp.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_release_depth(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = RELEASE_DEPTHISP_RESPONSE;

	/* isp_msg_ack.u.ack_release_depthisp.status = 0; */
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_demap_map_request(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = DMAP_MAP_RESPONSE;
	isp_msg_ack.u.ack_dmap_map_buffer.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_demap_unmap_request(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = DMAP_UNMAP_RESPONSE;
	isp_msg_ack.u.ack_dmap_unmap_buffer.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_dgen_flush_request(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = DGEN_FLUSH_RESPONSE;
	isp_msg_ack.u.ack_dgen_flush.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_dopt_flush_request(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = DOPT_FLUSH_RESPONSE;
	isp_msg_ack.u.ack_dopt_flush.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_dmap_format_request(void *isp_msg_r)
{
	int ret = 0;
	hisp_msg_t isp_msg_ack;
	hisp_msg_t *isp_msg = (hisp_msg_t *) isp_msg_r;

	isp_msg_ack = *isp_msg;
	isp_msg_ack.api_name = DMAP_FORMAT_RESPONSE;
	isp_msg_ack.u.ack_dmap_format.status = 0;
	/* Do something. */

	/* Act upon a hisp driver notification */
	g_simulated_fw_r.rpmsg.callback(&g_simulated_fw_r.rpdev,
					&isp_msg_ack,
					sizeof(hisp_msg_t), NULL, 0);
	return ret;
}

int simulated_fw_msg_event(void *isp_msg)
{
	int ret = 0;

	return ret;
}

int simulated_fw_msg_log(void *isp_msg)
{
	int ret = 0;

	return ret;
}

void clear_request_link(struct list_head *recv_msg_link)
{
	struct list_head *tmpMapList;
	frame_request_info *getData = NULL;

	cam_info("%s() this: 0x%x, prev: 0x%x, next: 0x%x", __func__,
		 recv_msg_link, recv_msg_link->prev, recv_msg_link->next);
//	if (recv_msg_link->next == recv_msg_link->prev)
//		return;
	if (list_empty(recv_msg_link))
	{
		cam_info("%s() list is empty", __func__);
		return;
	}
	tmpMapList = recv_msg_link->next;
	while (!list_empty(recv_msg_link)) {
		getData = list_entry(tmpMapList, frame_request_info, link);
		cam_info
		    ("%s() cancle request frame num: %d, prev: 0x%x, next: 0x%x",
		     __func__, getData->recv_msg->u.req_request.frame_number,
		     getData->link.prev, getData->link.next);
		tmpMapList = tmpMapList->next;
		msleep(2);
		g_simulated_fw_r.intf.msg_pro->request(getData->recv_msg);
		list_del(&(getData->link));
		kfree(getData);
		getData = NULL;
	}
}

/*
 * Hisp message processor.
 */
int message_manager(buffer_md_t *p_buffer_md_g,
		    simulated_fw_t s_simulated_fw_g, char *previewBuf)
{
	g_p_buffer_md = p_buffer_md_g;
	/* g_pSimulateClient = pSimulateClient_g; */
	g_simulated_fw_r = s_simulated_fw_g;
	g_preview_yuv_data = previewBuf;
	hisp_msg_t *hisp_msg_recv = (hisp_msg_t *) (g_simulated_fw_r.msg_read);

	if (hisp_msg_recv == NULL) {
		cam_err("%s error, hisp_msg_recv is null", __func__);
		return -1;
	}
	cam_debug("%s() get rpmsg API: 0x%x", __func__,
		  hisp_msg_recv->api_name);
	simulated_fw_msg_pro_t *pro = g_simulated_fw_r.intf.msg_pro;

	/* Receive hisp message */
	switch (hisp_msg_recv->api_name) {
	case COMMAND_QUERY_CAPABILITY:
		pro->query_capability(hisp_msg_recv);
		break;
	case COMMAND_ACQUIRE_CAMERA:
		init_isp_metada(g_p_buffer_md);
		if (hisp_msg_recv->u.req_acquire_camera.cam_id == 0) {
			INIT_LIST_HEAD(&recv_msg_main);
			cam_info("%s() this: 0x%x, prev: 0x%x, next: 0x%x",
				 __func__, &recv_msg_main, recv_msg_main.prev,
				 recv_msg_main.next);
		} else if (hisp_msg_recv->u.req_acquire_camera.cam_id == 2) {
			INIT_LIST_HEAD(&recv_msg_sub);
			cam_info("%s() this: 0x%x, prev: 0x%x, next: 0x%x",
				 __func__, &recv_msg_sub, recv_msg_sub.prev,
				 recv_msg_sub.next);
		} else {
			/* TO DO */
		}
		pro->acquire_camera(hisp_msg_recv);
		break;
	case COMMAND_RELEASE_CAMERA:
		pro->release_camera(hisp_msg_recv);
		break;
	case COMMAND_USECASE_CONFIG:
		if (hisp_msg_recv->u.req_usecase_config.cam_id != 2)
			clear_request_link(&recv_msg_main);
		else
			clear_request_link(&recv_msg_sub);
		pro->usecase_config(hisp_msg_recv);
		break;
	case COMMAND_STREAM_ON:
		pro->stream_on(hisp_msg_recv);
		break;
	case COMMAND_GET_OTP:
		pro->get_otp(hisp_msg_recv);
		break;
	case COMMAND_REQUEST:
		if ((hisp_msg_recv->u.req_request.target_map >> 8) & 0x1)
		{
			cam_info("%s() enter dual camera, start damp stream", __func__);
			frame_request_info *pdata = (frame_request_info *)
			    kmalloc(sizeof(frame_request_info), GFP_KERNEL);
			if (pdata == NULL) {
				cam_err("%s()  kmalloc fail: ", __func__);
				return;
			}
			frame_request_info *main_data = NULL;
			frame_request_info *sub_data = NULL;

			pdata->recv_msg = hisp_msg_recv;
			if (hisp_msg_recv->u.req_request.cam_id != 2)
				list_add(&(pdata->link), recv_msg_main.prev);
			else
				list_add(&(pdata->link), recv_msg_sub.prev);
			if (!list_empty(&recv_msg_main)
			    && !list_empty(&recv_msg_sub)) {
				struct list_head *tmpMapList = NULL;

				tmpMapList = recv_msg_main.next;
//				while (tmpMapList->next != &recv_msg_main)
//					tmpMapList = tmpMapList->next;
				main_data =
				    list_entry(tmpMapList, frame_request_info,
					       link);
				tmpMapList = recv_msg_sub.next;
//				while (tmpMapList->next != &recv_msg_sub)
//					tmpMapList = tmpMapList->next;
				sub_data =
				    list_entry(tmpMapList, frame_request_info,
					       link);
				cam_info("%s() main request frame num: %d",
					 __func__,
					 main_data->recv_msg->u.
					 req_request.frame_number);
				cam_info("%s() sub request frame num: %d",
					 __func__,
					 sub_data->recv_msg->u.
					 req_request.frame_number);
				pro->request(main_data->recv_msg);
				msleep(5);
				pro->request(sub_data->recv_msg);
				list_del(&(main_data->link));
				list_del(&(sub_data->link));
				kfree(main_data);
				kfree(sub_data);
				main_data = NULL;
				sub_data = NULL;
			}
		} else {
			cam_info("%s() enter single camera, do not start damp stream", __func__);
			pro->request(hisp_msg_recv);
			msleep(2);
		}
		break;
	case COMMAND_WARP_REQUEST:
		pro->warp_request(hisp_msg_recv);
		break;
	case COMMAND_ARSR_REQUEST:
		pro->arsr_request(hisp_msg_recv);
		break;
	case COMMAND_DGEN_REQUEST:
		pro->dgen_request(hisp_msg_recv);
		break;
	case COMMAND_DOPT_REQUEST:
		pro->dopt_request(hisp_msg_recv);
		break;
	case COMMAND_JPEG_ENCODE:
		pro->jpeg_encode(hisp_msg_recv);
		break;
	case COMMAND_MAP_BUFFER:
		pro->use_mem_pool(hisp_msg_recv);
		break;
	case COMMAND_UNMAP_BUFFER:
		pro->unmap_buffer(hisp_msg_recv);
		break;
	case COMMAND_CALIBRATION_DATA:
		pro->set_cal_data(hisp_msg_recv);
		break;
	case COMMAND_SET_ISP_REGISTERS:
		pro->set_isp_regs(hisp_msg_recv);
		break;
	case COMMAND_GET_ISP_REGISTER:
		pro->get_isp_regs(hisp_msg_recv);
		break;
	case COMMAND_SET_IIC_REGISTER:
		pro->set_i2c_regs(hisp_msg_recv);
		break;
	case COMMAND_GET_IIC_REGISTER:
		pro->get_i2c_regs(hisp_msg_recv);
		break;
	case COMMAND_TEST_CASE_INTERFACE:
		pro->test_case_interface(hisp_msg_recv);
		break;
	case COMMAND_FLUSH:
		clear_request_link(&recv_msg_main);
		clear_request_link(&recv_msg_sub);
		pro->flush(hisp_msg_recv);
		break;
	case COMMAND_EXTEND_SET:
		pro->extend_set(hisp_msg_recv);
		break;
	case COMMAND_EXTEND_GET:
		pro->extend_get(hisp_msg_recv);
		break;
	case COMMAND_INV_TLB:
		pro->inv_tlb(hisp_msg_recv);
		break;
	case COMMAND_QUERY_OIS_UPDATE:
		pro->query_ois_update(hisp_msg_recv);
		break;
	case COMMAND_OIS_UPDATE:
		pro->ois_update(hisp_msg_recv);
		break;
	case COMMAND_QUERY_LASER:
		pro->query_laser(hisp_msg_recv);
		break;
	case COMMAND_ACQUIRE_LASER:
		pro->acquire_laser(hisp_msg_recv);
		break;
	case COMMAND_RELEASE_LASER:
		pro->release_laser(hisp_msg_recv);
		break;
	case COMMAND_ACQUIRE_DEPTHISP:
		pro->acquire_depthisp(hisp_msg_recv);
		break;
	case COMMAND_RELEASE_DEPTHISP:
		pro->release_depthisp(hisp_msg_recv);
		break;
	case COMMAND_DMAP_MAP_REQUEST:
		pro->demap_map_request(hisp_msg_recv);
		break;
	case COMMAND_DMAP_UNMAP_REQUEST:
		pro->demap_unmap_request(hisp_msg_recv);
		break;
	case COMMAND_DGEN_FLUSH_REQUEST:
		pro->dgen_flush_request(hisp_msg_recv);
		break;
	case COMMAND_DOPT_FLUSH_REQUEST:
		pro->dopt_flush_request(hisp_msg_recv);
		break;
	case COMMAND_DMAP_FORMAT_REQUEST:
		pro->dmap_format_request(hisp_msg_recv);
		break;
	default:
		cam_err("%s apiname(%u) is error",
			__func__, hisp_msg_recv->api_name);
		break;
	}
	return 0;
}

EXPORT_SYMBOL(message_manager);
