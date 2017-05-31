/* Copyright (c) 2014-2015, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#include "hisi_overlay_utils.h"
#if defined (CONFIG_DRMDRIVER)
#include <linux/hisi/hisi_drmdriver.h>
#endif
#if defined (CONFIG_TEE_TUI)
#include "tui.h"
#endif

static void hisifb_secure_ctrl_wq_handler(struct work_struct *work)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_secure *secure_ctrl = NULL;
	secure_ctrl = container_of(work, typeof(*secure_ctrl), secure_ctrl_work);
	BUG_ON(secure_ctrl == NULL);
	hisifd = secure_ctrl->hisifd;
	BUG_ON(hisifd == NULL);

	HISI_FB_DEBUG(": secure_status = %d, secure_event = %d, frame_no = %d +++ \n",
		secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no);

	down(&hisifd->blank_sem);
	if (!hisifd->panel_power_on) {
	#if defined (CONFIG_TEE_TUI)
		send_tui_msg_config(TUI_POLL_CFG_FAIL, 0, "DSS");
	#endif
		HISI_FB_INFO("fb%d, panel is power off!", hisifd->index);
		up(&hisifd->blank_sem);
		return;
	}

	if ((DSS_SEC_IDLE == secure_ctrl->secure_status)
			&& (DSS_SEC_ENABLE == secure_ctrl->secure_event)) {
		secure_ctrl->secure_status = DSS_SEC_RUNNING;
	}

	if ((DSS_SEC_RUNNING == secure_ctrl->secure_status)
		&& (DSS_SEC_ENABLE == secure_ctrl->secure_event)
		&& (secure_ctrl->tui_need_switch)) {
		hisifb_activate_vsync(hisifd);
	#if defined (CONFIG_TEE_TUI)
		if (hisifd->secure_ctrl.secure_blank_flag) {
			send_tui_msg_config(TUI_POLL_CFG_FAIL, 0, "DSS");
			HISI_FB_INFO("TUI blank switch to DSS_SEC_RUNNING failed !\n");
		} else {
			send_tui_msg_config(TUI_POLL_CFG_OK, 0, "DSS");
			HISI_FB_INFO("TUI switch to DSS_SEC_RUNNING succ !\n");
		}
	#endif
		secure_ctrl->tui_need_switch = 0;
	}
	up(&hisifd->blank_sem);

	HISI_FB_DEBUG(": secure_status = %d, secure_event = %d, frame_no = %d --- \n",
		secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no);
}

/* receive switch tui request
 **1: secure enable
 **0: secure disable
 */
static int notify_dss_tui_request(void *data, int secure)
{
	int ret;
	int tui_request;
	struct hisifb_secure *secure_ctrl;
	struct hisi_fb_data_type *hisifd;

	hisifd = (struct hisi_fb_data_type *)data; //hisifd_list[PRIMARY_PANEL_IDX];
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);

	if (!secure_ctrl->secure_created) {
	#if defined (CONFIG_TEE_TUI)
		if (secure) {
			send_tui_msg_config(TUI_POLL_CFG_FAIL, 0, "DSS");
		}
	#endif
		HISI_FB_ERR("fb%d, secure is not created yet!\n", hisifd->index);
		return -1;
	}

	down(&hisifd->blank_sem);
	if (!hisifd->panel_power_on) {
	#if defined (CONFIG_TEE_TUI)
		if (secure) {
			send_tui_msg_config(TUI_POLL_CFG_FAIL, 0, "DSS");
		}
	#endif
		HISI_FB_INFO("fb%d, panel is power off!", hisifd->index);
		up(&hisifd->blank_sem);
		return -1;
	}

	tui_request = secure ? DSS_SEC_ENABLE : DSS_SEC_DISABLE;
	HISI_FB_INFO(": secure_status = %d, secure_event = %d, frame_no = %d , tui_request = %d +++ \n",
		secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no, tui_request);

	if (secure_ctrl->secure_status == tui_request) {
	#if defined (CONFIG_TEE_TUI)
		if (secure) {
			send_tui_msg_config(TUI_POLL_CFG_FAIL, 0, "DSS");
		}
	#endif
		HISI_FB_INFO("secure_status is not changed, secure_status = %d,---!\n", secure_ctrl->secure_status);
		up(&hisifd->blank_sem);
		return -1;
	}
	secure_ctrl->secure_event = tui_request;
	secure_ctrl->tui_need_switch = 1;
	secure_ctrl->tui_need_skip_report = 0;

	if (DSS_SEC_ENABLE == secure_ctrl->secure_event) {
		hisifb_activate_vsync(hisifd);
		wake_up_interruptible_all(&(hisifd->vsync_ctrl.vsync_wait));
		up(&hisifd->blank_sem);
	} else {
		secure_ctrl->secure_status = DSS_SEC_IDLE;
		up(&hisifd->blank_sem);
		HISI_FB_INFO("secure_blank_flag = %d, panel_power_on = %d\n",
			secure_ctrl->secure_blank_flag, hisifd->panel_power_on);

		if (secure_ctrl->secure_blank_flag) {
			ret = hisi_fb_blank_sub(FB_BLANK_POWERDOWN, hisifd->fbi);
			if (ret != 0) {
				HISI_FB_ERR("fb%d, blank_mode(%d) failed!\n", hisifd->index, FB_BLANK_POWERDOWN);
			}
			secure_ctrl->secure_blank_flag = 0;
		}
	}

	HISI_FB_INFO("secure_status = %d, secure_event = %d, frame_no = %d , tui_request = %d --- \n",
		secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no, tui_request);
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
static ssize_t hisifb_secure_event_store(struct device* dev,
		struct device_attribute* attr, const char* buf, size_t count)
{
	int val = 0;
	struct fb_info *fbi = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -1;
	}

	fbi = dev_get_drvdata(dev);
	if (NULL == fbi) {
		HISI_FB_ERR("NULL Pointer\n");
		return -1;
	}

	hisifd = (struct hisi_fb_data_type *)fbi->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -1;
	}

	val = (int)simple_strtoul(buf, NULL, 0);

	notify_dss_tui_request(hisifd, val);

	return count;
}

static ssize_t hisifb_secure_event_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	ssize_t ret = -1;
	struct fb_info *fbi = NULL;
	struct hisi_fb_data_type *hisifd = NULL;

	if (NULL == dev) {
		HISI_FB_ERR("NULL Pointer\n");
		return -1;
	}

	fbi = dev_get_drvdata(dev);
	if (NULL == fbi) {
		HISI_FB_ERR("NULL Pointer\n");
		return -1;
	}

	hisifd = (struct hisi_fb_data_type *)fbi->par;
	if (NULL == hisifd) {
		HISI_FB_ERR("NULL Pointer\n");
		return -1;
	}

	snprintf(buf, PAGE_SIZE, "SECURE_EVENT=%d, SECURE_STATUS=%d\n",
	        hisifd->secure_ctrl.secure_event, hisifd->secure_ctrl.secure_status);
	ret = strlen(buf) + 1;
	return ret;
}

/*lint -e665*/
static DEVICE_ATTR(dss_secure, S_IRUGO|S_IWUSR, hisifb_secure_event_show, hisifb_secure_event_store);
/*lint -e665*/

/* for DRM config */
#if defined (CONFIG_HISI_FB_3650)
static void hisifd_secure_set_reg(uint32_t addr, uint32_t val, uint8_t bw, uint8_t bs)
{
#if defined (CONFIG_DRMDRIVER)
	configure_dss_register_security(addr, val, bw, bs);
#endif
}

static void hisifd_secure_layer_config(struct hisi_fb_data_type *hisifd, int32_t chn_idx)
{
	struct hisifb_secure *secure_ctrl = NULL;
	dss_module_reg_t *dss_module = NULL;
	uint32_t dss_base = 0;

	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	dss_module = &(hisifd->dss_module);
	HISI_FB_DEBUG("chn_idx = %d, frame_no = %d \n", chn_idx, hisifd->ov_req.frame_no);
	dss_base = hisifd->dss_base_phy;
	secure_ctrl->set_reg(dss_base + g_dss_module_base[chn_idx][MODULE_DMA] + CH_SECU_EN, 0x1, 1, 0);
}

static void hisifd_secure_layer_deconfig(struct hisi_fb_data_type *hisifd, int32_t chn_idx)
{
	struct hisifb_secure *secure_ctrl = NULL;
	dss_module_reg_t *dss_module = NULL;
	uint32_t dss_base = 0;

	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	dss_module = &(hisifd->dss_module);

	HISI_FB_DEBUG("chn_idx = %d, frame_no = %d \n", chn_idx, hisifd->ov_req.frame_no);
	dss_base = hisifd->dss_base_phy;
	secure_ctrl->set_reg(dss_base + g_dss_module_base[chn_idx][MODULE_DMA] + CH_SECU_EN, 0x0, 1, 0);
}
#endif

void hisifd_secure_ch_default_config(struct hisi_fb_data_type *hisifd)
{
	struct hisifb_secure *secure_ctrl = NULL;
	int ch_index = 0;
	uint32_t dss_base = 0;
	uint32_t module_base = 0;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null!\n");
		return;
	}
	secure_ctrl = &(hisifd->secure_ctrl);

	dss_base = hisifd->dss_base_phy;
	for (ch_index = 0; ch_index < DSS_CHN_MAX-1; ch_index++) {
		module_base = g_dss_module_base[ch_index][MODULE_DMA];
		if ((secure_ctrl->set_reg) && (module_base != 0) && (dss_base != 0)) {
			secure_ctrl->set_reg(dss_base + module_base + CH_SECU_EN, 0x0, 1, 0);
		} else {
		#if defined (CONFIG_DRMDRIVER)
			configure_dss_service_security(DSS_CH_DEFAULT_SEC_CONFIG, 0, 0);
		#endif
		}
	}
}

/* TUI is enable, mctl sys ov should sel sec rch in non-secure. */
void hisi_sec_mctl_set_regs(struct hisi_fb_data_type *hisifd)
{
	struct hisifb_secure *secure_ctrl;
	char __iomem *module_base;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null!\n");
		return ;
	}
	secure_ctrl = &(hisifd->secure_ctrl);
	if (DSS_SEC_ENABLE == secure_ctrl->secure_event) {
		module_base = hisifd->dss_module.mctl_sys_base;
		hisifd->set_reg(hisifd, module_base + MCTL_RCH_OV0_SEL, TUI_SEC_RCH, 4, 24);
	}
}

void hisi_drm_layer_online_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req_prev, dss_overlay_t *pov_req)
{
	int i = 0, m = 0;
	dss_layer_t *layer = NULL;
	dss_overlay_block_t *pov_h_block_infos = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	struct hisifb_secure *secure_ctrl = NULL;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null!\n");
		return;
	}
	secure_ctrl = &(hisifd->secure_ctrl);

	if (pov_req_prev == NULL) {
		HISI_FB_INFO("pov_req_prev is null!\n");
		return;
	}
	pov_h_block_infos = (dss_overlay_block_t *)(pov_req_prev->ov_block_infos_ptr);
	for (m = 0; m < pov_req_prev->ov_block_nums; m++) {
		pov_h_block = &(pov_h_block_infos[m]);

		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);
			if (layer->img.secure_mode == 1) {
				HISI_FB_DEBUG("chn_idx = %d, prev_frame_no = %d \n", layer->chn_idx, pov_req_prev->frame_no);
				if (secure_ctrl->secure_layer_deconfig && secure_ctrl->set_reg) {
					secure_ctrl->secure_layer_deconfig(hisifd, layer->chn_idx);
					if ((layer->chn_idx - DSS_RCHN_G0) > 0) {
						secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE1,
							0, 32, 0);
					} else {
						secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE0,
							0, 32, 0);
					}
				} else {
				#if defined (CONFIG_DRMDRIVER)
					configure_dss_service_security(DSS_CH_SEC_DECONFIG, (uint32_t)layer->chn_idx, ONLINE_COMPOSE_MODE);
				#endif
				}
			}
		}
	}

	if (pov_req == NULL) {
		HISI_FB_DEBUG("pov_req is null!\n");
		return;
	}
	pov_h_block_infos = (dss_overlay_block_t *)(pov_req->ov_block_infos_ptr);
	for (m = 0; m < pov_req->ov_block_nums; m++) {
		pov_h_block = &(pov_h_block_infos[m]);

		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);
			if (layer->img.secure_mode == 1) {
				HISI_FB_DEBUG("chn_idx = %d, frame_no = %d \n", layer->chn_idx, pov_req->frame_no);
				if (secure_ctrl->secure_layer_config && secure_ctrl->set_reg) {
					secure_ctrl->secure_layer_config(hisifd, layer->chn_idx);
					if ((layer->chn_idx - DSS_RCHN_G0) > 0) {
						if ((layer->chn_idx - DSS_RCHN_G0) <= 4) {
							secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE1,
								((uint32_t)0x3E << ((uint32_t)((layer->chn_idx - DSS_RCHN_G0) - 1) * 8)), 32, 0);
						}
					} else {
						secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE0,
							((uint32_t)0x3E << ((uint32_t)layer->chn_idx * 8)), 32, 0);
					}
				} else {
				#if defined (CONFIG_DRMDRIVER)
					configure_dss_service_security(DSS_CH_SEC_CONFIG, (uint32_t)layer->chn_idx, ONLINE_COMPOSE_MODE);
				#endif
				}
			}
		}
	}
}

void hisi_drm_layer_offline_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req)
{
	int m = 0, i = 0;
	dss_wb_layer_t *wb_layer4block = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	dss_overlay_block_t *pov_h_block_infos = NULL;
	dss_layer_t *layer = NULL;
	struct hisifb_secure *secure_ctrl = NULL;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null!\n");
		return;
	}

	if (pov_req == NULL) {
		HISI_FB_ERR("pov_req is null!\n");
		return;
	}
	secure_ctrl = &(hisifd_list[PRIMARY_PANEL_IDX]->secure_ctrl);

	pov_h_block_infos = (dss_overlay_block_t *)pov_req->ov_block_infos_ptr;
	if (pov_h_block_infos == NULL) {
		HISI_FB_ERR("fb%d, invalid pov_h_block_infos!\n", hisifd->index);
		return ;
	}

	wb_layer4block = &(pov_req->wb_layer_infos[0]);
	if (wb_layer4block->dst.secure_mode == 1) {
		HISI_FB_DEBUG("chn_idx = %d, frame_no = %d \n", wb_layer4block->chn_idx, pov_req->frame_no);
		if (secure_ctrl->secure_layer_config && secure_ctrl->set_reg) {
			secure_ctrl->secure_layer_config(secure_ctrl->hisifd, wb_layer4block->chn_idx);
			secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE2,
				(uint32_t)BIT(5), 32, 0);
		} else {
		#if defined (CONFIG_DRMDRIVER)
			configure_dss_service_security(DSS_CH_SEC_CONFIG, (uint32_t)wb_layer4block->chn_idx, OFFLINE_COMPOSE_MODE);
		#endif
		}
	}

	for (m = 0; m < pov_req->ov_block_nums; m++) {
		pov_h_block = &(pov_h_block_infos[m]);
		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);
			if (layer->img.secure_mode == 1) {
				HISI_FB_DEBUG("chn_idx = %d, frame_no = %d \n", layer->chn_idx, pov_req->frame_no);
				if (secure_ctrl->secure_layer_config && secure_ctrl->set_reg ) {
					secure_ctrl->secure_layer_config(secure_ctrl->hisifd, layer->chn_idx);
					if ((layer->chn_idx - DSS_RCHN_G0) > 0) {
						if ((layer->chn_idx - DSS_RCHN_G0) <= 4) {
							secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE1,
								((uint32_t)0x3B << ((uint32_t)((layer->chn_idx - DSS_RCHN_G0) - 1) * 8)), 32, 0);
						}
					} else {
						secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE0,
							((uint32_t)0x3B << ((uint32_t)layer->chn_idx * 8)), 32, 0);
					}
				} else {
				#if defined (CONFIG_DRMDRIVER)
					configure_dss_service_security(DSS_CH_SEC_CONFIG, (uint32_t)layer->chn_idx, OFFLINE_COMPOSE_MODE);
				#endif
				}
			}
		}
	}
}

void hisi_drm_layer_offline_clear(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req)
{
	int m = 0, i = 0;
	dss_wb_layer_t *wb_layer4block = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	dss_overlay_block_t *pov_h_block_infos = NULL;
	dss_layer_t *layer = NULL;
	struct hisifb_secure *secure_ctrl = NULL;

	if (hisifd == NULL) {
		HISI_FB_ERR("hisifd is null!\n");
		return;
	}

	if (pov_req == NULL) {
		HISI_FB_ERR("pov_req is null!\n");
		return;
	}
	secure_ctrl = &(hisifd_list[PRIMARY_PANEL_IDX]->secure_ctrl);

	pov_h_block_infos = (dss_overlay_block_t *)pov_req->ov_block_infos_ptr;
	if (pov_h_block_infos == NULL) {
		HISI_FB_ERR("fb%d, invalid pov_h_block_infos!\n", hisifd->index);
		return ;
	}

	wb_layer4block = &(pov_req->wb_layer_infos[0]);
	if (wb_layer4block->dst.secure_mode == 1) {
		if (secure_ctrl->secure_layer_deconfig && secure_ctrl->set_reg) {
			secure_ctrl->secure_layer_deconfig(secure_ctrl->hisifd, wb_layer4block->chn_idx);
			secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE2,
				0, 32, 0);
		} else {
		#if defined (CONFIG_DRMDRIVER)
			configure_dss_service_security(DSS_CH_SEC_DECONFIG, (uint32_t)wb_layer4block->chn_idx, OFFLINE_COMPOSE_MODE);
		#endif
		}
	}

	for (m = 0; m < pov_req->ov_block_nums; m++) {
		pov_h_block = &(pov_h_block_infos[m]);
		for (i = 0; i < pov_h_block->layer_nums; i++) {
			layer = &(pov_h_block->layer_infos[i]);
			if (layer->img.secure_mode == 1) {
				if (secure_ctrl->secure_layer_deconfig && secure_ctrl->set_reg) {
					secure_ctrl->secure_layer_deconfig(secure_ctrl->hisifd, layer->chn_idx);
					if ((layer->chn_idx - DSS_RCHN_G0) > 0) {
						secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE1,
							0, 32, 0);
					} else {
						secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_GATE0,
							0, 32, 0);
					}
				} else {
				#if defined (CONFIG_DRMDRIVER)
					configure_dss_service_security(DSS_CH_SEC_DECONFIG, (uint32_t)layer->chn_idx, OFFLINE_COMPOSE_MODE);
				#endif

				}
			}
		}
	}
}

static bool check_tui_layer_chn_cfg_ok(struct hisi_fb_data_type *hisifd)
{
	dss_layer_t *layer = NULL;
	dss_overlay_t *pov_req_prev = NULL;
	dss_overlay_block_t *pov_h_block = NULL;
	dss_overlay_block_t *pov_h_block_infos = NULL;

	pov_req_prev = &(hisifd->ov_req_prev);
	pov_h_block_infos = (dss_overlay_block_t *)(pov_req_prev->ov_block_infos_ptr);

	/* gpu compose only one block */
	if (pov_req_prev->ov_block_nums > 1) {
		return false;
	}

	if (pov_h_block_infos == NULL) {
		HISI_FB_INFO("pov_h_block_infos is null!\n");
		return false;
	}

	/* gpu compose only one layer */
	pov_h_block = &(pov_h_block_infos[0]);
	if (pov_h_block->layer_nums > 1) {
		return false;
	}

	if (pov_h_block->layer_infos == NULL) {
		HISI_FB_INFO("pov_h_block->layer_infos is null!\n");
		return false;
	}

	/* use chn V0 for TUI compose except dallas */
	layer = &(pov_h_block->layer_infos[0]);
	if (layer->chn_idx == DSS_RCHN_V0) {
		return false;
	}

	return true;
}

static void hisifd_notify_secure_switch(struct hisi_fb_data_type *hisifd)
{
	struct hisifb_secure *secure_ctrl = NULL;

	if (hisifd == NULL) {
		HISI_FB_INFO("hisifd is null!\n");
		return;
	}
	if (hisifd->index != PRIMARY_PANEL_IDX) {
		return;
	}

	secure_ctrl = &(hisifd->secure_ctrl);
	if ((hisifd->ov_req.sec_enable_status == DSS_SEC_ENABLE)
		&& (check_tui_layer_chn_cfg_ok(hisifd))
		&& (secure_ctrl->secure_status != secure_ctrl->secure_event)) {
		schedule_work(&secure_ctrl->secure_ctrl_work);
	}
}

void hisifb_secure_register(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_secure *secure_ctrl = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);

	if (secure_ctrl->secure_created) {
		return;
	}
	secure_ctrl->secure_status = DSS_SEC_IDLE;
	secure_ctrl->secure_event  = DSS_SEC_DISABLE;
	secure_ctrl->secure_blank_flag = 0;
	secure_ctrl->tui_need_switch = 0;

	INIT_WORK(&secure_ctrl->secure_ctrl_work, hisifb_secure_ctrl_wq_handler);
#if defined (CONFIG_TEE_TUI)
	/* register dss tui process function to sw */
	register_tui_driver(notify_dss_tui_request, "DSS", hisifd);
#endif
	secure_ctrl->notify_secure_switch = hisifd_notify_secure_switch;
#if defined (CONFIG_HISI_FB_3650)
	secure_ctrl->set_reg = hisifd_secure_set_reg;
	secure_ctrl->secure_layer_config = hisifd_secure_layer_config;
	secure_ctrl->secure_layer_deconfig = hisifd_secure_layer_deconfig;
#else
	secure_ctrl->set_reg = NULL;
	secure_ctrl->secure_layer_config = NULL;
	secure_ctrl->secure_layer_deconfig = NULL;
#endif
	secure_ctrl->hisifd = hisifd;

	secure_ctrl->secure_created = 1;

	if (hisifd->sysfs_attrs_append_fnc)
		hisifd->sysfs_attrs_append_fnc(hisifd, &dev_attr_dss_secure.attr);
}

void hisifb_secure_unregister(struct platform_device *pdev)
{
	struct hisi_fb_data_type *hisifd = NULL;
	struct hisifb_secure *secure_ctrl = NULL;

	BUG_ON(pdev == NULL);
	hisifd = platform_get_drvdata(pdev);
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);

	if (!secure_ctrl->secure_created)
		return;

	secure_ctrl->secure_created = 0;
}
