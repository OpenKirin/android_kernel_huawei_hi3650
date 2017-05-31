/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/
#ifndef HISI_OVERLAY_UTILS_H
#define HISI_OVERLAY_UTILS_H

#include "hisi_fb.h"


/*******************************************************************************
**
*/
extern uint32_t g_dss_module_base[DSS_CHN_MAX_DEFINE][MODULE_CHN_MAX];
extern uint32_t g_dss_module_ovl_base[DSS_MCTL_IDX_MAX][MODULE_OVL_MAX];
extern uint32_t g_dss_module_cap[DSS_CHN_MAX_DEFINE][MODULE_CAP_MAX];
extern uint32_t g_dss_mif_sid_map[DSS_CHN_MAX_DEFINE];
extern uint32_t g_dss_smmu_smrx_idx[DSS_CHN_MAX_DEFINE];
extern int g_scf_lut_chn_coef_idx[DSS_CHN_MAX_DEFINE];
extern unsigned int g_dss_smmu_outstanding;
extern void *g_smmu_rwerraddr_virt;

#define DSS_COMPOSER_TIMEOUT_THRESHOLD_FPGA	(10000)
#define DSS_COMPOSER_TIMEOUT_THRESHOLD_ASIC	(300)

enum ENUM_LDI_VSTATE{
    LDI_VSTATE_IDLE = 0x1,
    LDI_VSTATE_VSW = 0x2,
    LDI_VSTATE_VBP = 0x4,
    LDI_VSTATE_VACTIVE0 = 0x8,
    LDI_VSTATE_VACTIVE_SPACE = 0x10,
    LDI_VSTATE_VACTIVE1 = 0x20,
    LDI_VSTATE_VFP = 0x40,
    LDI_VSTATE_V_WAIT_TE0 = 0x80,
    LDI_VSTATE_V_WAIT_TE1 = 0x100,
    LDI_VSTATE_V_WAIT_TE_EN = 0x200,
};

void dumpDssOverlay(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req, bool isNeedSaveFile);

int hisi_get_hal_format(struct fb_info *info);
int hisi_overlay_init(struct hisi_fb_data_type *hisifd);
int hisi_overlay_deinit(struct hisi_fb_data_type *hisifd);
int hisi_overlay_on(struct hisi_fb_data_type *hisifd, bool fastboot_enable);
int hisi_overlay_off(struct hisi_fb_data_type *hisifd);
int hisi_overlay_on_lp(struct hisi_fb_data_type *hisifd);
int hisi_overlay_off_lp(struct hisi_fb_data_type *hisifd);
bool hisi_dss_check_reg_reload_status(struct hisi_fb_data_type *hisifd);
bool hisi_dss_check_crg_sctrl_status(struct hisi_fb_data_type *hisifd);

void hisifb_adjust_block_rect(int block_num, dss_rect_t *ov_block_rects[], dss_wb_layer_t *wb_layer);
void hisifb_dss_disreset(struct hisi_fb_data_type *hisifd);

void hisi_vactive0_start_isr_handler(struct hisi_fb_data_type *hisifd);
int hisi_vactive0_start_config(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req);

int hisi_dss_dirty_region_dbuf_config(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req);
void hisi_dss_dirty_region_updt_config(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req);

int hisi_dss_handle_cur_ovl_req(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req);

int hisi_ov_compose_handler(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req,
	dss_overlay_block_t *pov_h_block,
	dss_layer_t *layer,
	dss_rect_t *wb_dst_rect,
	dss_rect_t *wb_ov_block_rect,
	dss_rect_ltrb_t *clip_rect,
	dss_rect_t *aligned_rect,
	bool *rdma_stretch_enable,
	bool *has_base,
	bool csc_needed,
	bool enable_cmdlist);

int hisi_wb_compose_handler(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req,
	dss_wb_layer_t *wb_layer,
	dss_rect_t *wb_ov_block_rect,
	bool last_block,
	uint32_t wb_type,
	bool csc_needed,
	bool enable_cmdlist);

void hisi_dss_qos_on(struct hisi_fb_data_type *hisifd);
void hisi_dss_mmbuf_on(struct hisi_fb_data_type *hisifd);
void hisi_dss_mif_on(struct hisi_fb_data_type *hisifd);
void hisi_dss_smmu_on(struct hisi_fb_data_type *hisifd);
void hisi_dss_smmu_init(char __iomem *smmu_base,
	dss_smmu_t *s_smmu);
void hisi_dss_smmu_ch_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *smmu_base, dss_smmu_t *s_smmu, int chn_idx);
void hisi_dss_smmu_ov_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *smmu_base, dss_smmu_t *s_smmu);
int hisi_dss_scl_coef_on(struct hisi_fb_data_type *hisifd, bool enable_cmdlist, int coef_lut_idx);

int hisi_overlay_pan_display(struct hisi_fb_data_type *hisifd);
int hisi_ov_online_play(struct hisi_fb_data_type *hisifd, void __user *argp);
int hisi_ov_offline_play(struct hisi_fb_data_type *hisifd, void __user *argp);
int hisi_ov_copybit_play(struct hisi_fb_data_type *hisifd, void __user *argp);
int hisi_overlay_ioctl_handler(struct hisi_fb_data_type *hisifd,
	uint32_t cmd, void __user *argp);

void hisi_dss_unflow_handler(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req, bool unmask);

void hisi_dss_chn_set_reg_default_value(struct hisi_fb_data_type *hisifd,
	char __iomem *dma_base);
void hisi_dss_ov_set_reg_default_value(struct hisi_fb_data_type *hisifd,
	char __iomem *ovl_base, int ovl_idx);
int hisi_dss_prev_module_set_regs(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req, uint32_t cmdlist_pre_idxs, bool enable_cmdlist, bool *use_comm_mmbuf);

int hisi_dss_check_pure_layer(struct hisi_fb_data_type *hisifd, dss_overlay_block_t *pov_h_block,
	void __user *argp);

int hisi_dss_check_userdata(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block_infos);
int hisi_dss_check_layer_par(struct hisi_fb_data_type *hisifd, dss_layer_t *layer);

int hisi_dss_aif_handler(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req, dss_overlay_block_t *pov_h_block);
void hisi_dss_aif_init(char __iomem *aif_ch_base,	dss_aif_t *s_aif);
void hisi_dss_aif_ch_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *aif_ch_base, dss_aif_t *s_aif);
int hisi_dss_aif_ch_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
	dss_layer_t *layer, dss_rect_t *wb_dst_rect, dss_wb_layer_t *wb_layer, int ovl_idx);

int hisi_dss_aif1_ch_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
	dss_layer_t *layer, dss_wb_layer_t *wb_layer, int ovl_idx);

int hisi_dss_mif_config(struct hisi_fb_data_type *hisifd,
	dss_layer_t *layer, dss_wb_layer_t *wb_layer, bool rdma_stretch_enable);

int hisi_dss_smmu_ch_config(struct hisi_fb_data_type *hisifd,
	dss_layer_t *layer, dss_wb_layer_t *wb_layer);

int hisi_dss_rdma_config(struct hisi_fb_data_type *hisifd, int ovl_idx,
	dss_layer_t *layer, dss_rect_ltrb_t *clip_rect, dss_rect_t *aligned_rect,
	bool *rdma_stretch_enable);
int hisi_dss_wdma_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
	dss_wb_layer_t *layer, dss_rect_t aligned_rect, dss_rect_t *ov_block_rect, bool last_block);
int hisi_dss_rdfc_config(struct hisi_fb_data_type *hisifd, dss_layer_t *layer,
	dss_rect_t *aligned_rect, dss_rect_ltrb_t clip_rect);
int hisi_dss_wdfc_config(struct hisi_fb_data_type *hisifd, dss_wb_layer_t *layer,
	dss_rect_t *aligned_rect, dss_rect_t *ov_block_rect);

void hisi_dss_scl_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *scl_base, dss_scl_t *s_scl);
int hisi_dss_chn_scl_load_filter_coef_set_reg(struct hisi_fb_data_type *hisifd, bool enable_cmdlist,
	int chn_idx, uint32_t format);
int hisi_dss_post_scl_load_filter_coef(struct hisi_fb_data_type *hisifd, bool enable_cmdlist,
	char __iomem *scl_lut_base, int coef_lut_idx);
int hisi_dss_scl_config(struct hisi_fb_data_type *hisifd, dss_layer_t *layer,
	dss_rect_t *aligned_rect, bool rdma_stretch_enable);

int hisi_dss_post_scf_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req);
void hisi_dss_csc_init(char __iomem *csc_base, dss_csc_t *s_csc);
void hisi_dss_csc_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem *csc_base, dss_csc_t *s_csc);
int hisi_dss_csc_config(struct hisi_fb_data_type *hisifd, dss_layer_t *layer,
	dss_wb_layer_t *wb_layer);

int hisi_dss_ovl_base_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
      dss_overlay_block_t *pov_h_block, dss_rect_t *wb_ov_block_rect, int ovl_idx, int ov_h_block_idx);
int hisi_dss_ovl_layer_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
	dss_layer_t *layer, dss_rect_t *wb_ov_block_rect, bool has_base);

void hisi_dss_mctl_mutex_lock(struct hisi_fb_data_type *hisifd, int ovl_idx);
void hisi_dss_mctl_mutex_unlock(struct hisi_fb_data_type *hisifd, int ovl_idx);
void hisi_dss_mctl_on(struct hisi_fb_data_type *hisifd,
	int mctl_idx, bool enable_cmdlist, bool fastboot_enable);
int hisi_dss_mctl_ch_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
	dss_layer_t *layer, dss_wb_layer_t *wb_layer, int ovl_idx,
	dss_rect_t *wb_ov_block_rect, bool has_base);
int hisi_dss_mctl_ov_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req,
	int ovl_idx, bool has_base, bool is_first_ov_block);

int hisi_dss_sharpness_config(struct hisi_fb_data_type *hisifd, dss_layer_t *layer);
int hisi_dss_post_clip_config(struct hisi_fb_data_type *hisifd, dss_layer_t *layer);
int hisi_dss_ce_config(struct hisi_fb_data_type *hisifd, dss_layer_t *layer);

int hisi_dss_module_default(struct hisi_fb_data_type *hisifd);
int hisi_dss_module_init(struct hisi_fb_data_type *hisifd);
int hisi_dss_ch_module_set_regs(struct hisi_fb_data_type *hisifd, int32_t mctl_idx,
	int chn_idx, uint32_t wb_type, bool enable_cmdlist);
int hisi_dss_ov_module_set_regs(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req, int ovl_idx,
	bool enable_cmdlist, int task_end, int last, bool is_first_ov_block);

void hisi_dss_secure_layer_check_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req);
void hisi_rch2_ce_end_handle_func(struct work_struct *work);
void hisi_rch4_ce_end_handle_func(struct work_struct *work);
void hisi_dss_dpp_acm_ce_end_handle_func(struct work_struct *work);
void hisi_sec_mctl_set_regs(struct hisi_fb_data_type *hisifd);
void hisi_drm_layer_online_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req_prev, dss_overlay_t *pov_req);
void hisi_drm_layer_offline_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req);
void hisi_drm_layer_offline_clear(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req);

void hisi_crc_isr_handler(struct hisi_fb_data_type *hisifd);
int hisi_crc_enable(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req);
int hisi_crc_config(struct hisi_fb_data_type *hisifd,
	dss_overlay_t *pov_req);
void hisi_dss_debug_func(struct work_struct *work);
void hisi_ldi_underflow_handle_func(struct work_struct *work);

void* hisi_dss_mmbuf_init(struct hisi_fb_data_type *hisifd);
void hisi_dss_mmbuf_deinit(struct hisi_fb_data_type *hisifd);
uint32_t hisi_dss_mmbuf_alloc(void *handle, uint32_t size);
void hisi_dss_mmbuf_free(void *handle, uint32_t addr, uint32_t size);
void hisi_dss_mmbuf_info_clear(struct hisi_fb_data_type *hisifd, int idx);
dss_mmbuf_info_t* hisi_dss_mmbuf_info_get(struct hisi_fb_data_type *hisifd, int idx);
void hisi_mmbuf_info_get_online(struct hisi_fb_data_type *hisifd);
void hisi_dss_mctl_ov_set_ctl_dbg_reg(struct hisi_fb_data_type *hisifd, char __iomem *mctl_base, bool enable_cmdlist);
uint32_t hisi_dss_mif_get_invalid_sel(dss_img_t *img, uint32_t transform, int v_scaling_factor,uint8_t is_tile, bool rdma_stretch_enable);

bool isYUVPackage(uint32_t format);
bool isYUVSemiPlanar(uint32_t format);
bool isYUVPlanar(uint32_t format);
bool isYUV(uint32_t format);

bool is_YUV_SP_420(uint32_t format);
bool is_YUV_SP_422(uint32_t format);
bool is_YUV_P_420(uint32_t format);
bool is_YUV_P_422(uint32_t format);
bool is_RGBX(uint32_t format);

#if defined (CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
int hisi_dss_arsr1p_write_lsc_gain(struct hisi_fb_data_type *hisifd, bool enable_cmdlist,
	char __iomem *addr, const uint32_t **p, int row, int col);
int hisi_dss_arsr1p_write_coefs(struct hisi_fb_data_type *hisifd, bool enable_cmdlist,
	char __iomem *addr, const int **p, int row, int col);

/*arsr2p interface*/
void hisi_dss_arsr2p_init(char __iomem * arsr2p_base, dss_arsr2p_t *s_arsr2p); //arsr2p init
void hisi_dss_arsr2p_set_reg(struct hisi_fb_data_type *hisifd,
	char __iomem * arsr2p_base, dss_arsr2p_t *s_arsr2p);   //arsr2p set reg
void hisi_dss_arsr2p_coef_on(struct hisi_fb_data_type *hisifd, bool enable_cmdlist);   //lut coef
int hisi_dss_arsr2p_config(struct hisi_fb_data_type *hisifd, dss_layer_t *layer, dss_rect_t *aligned_rect, bool rdma_stretch_enable); //arsr2p module config
void hisi_remove_mctl_mutex(struct hisi_fb_data_type *hisifd, int mctl_idx, uint32_t cmdlist_idxs);
#endif

#endif /* HISI_OVERLAY_UTILS_H */
