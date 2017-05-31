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
#ifndef HISI_DISPLAY_EFFECT_H
#define HISI_DISPLAY_EFFECT_H

#include "hisi_fb_def.h"
#include "hisi_dss.h"


#define CE_VALUE_BITWIDTH			(8)
#define CE_VALUE_RANK				(1 << CE_VALUE_BITWIDTH)
#define METADATA_SIZE				(1024)

#if defined(CONFIG_HISI_FB_3660) || defined (CONFIG_HISI_FB_970)
#define DISPLAY_EFFECT_USE_FRM_END_INT
#define XBLOCKNUM					(6)
#define YBLOCKNUM					(6)
#define HIACE_LHIST_RANK			(16)
#define HIACE_GAMMA_RANK			(11)
#define HIACE_GHIST_RANK			(32)
#define CE_SIZE_HIST				HIACE_GHIST_RANK + YBLOCKNUM * XBLOCKNUM * HIACE_LHIST_RANK
#define CE_SIZE_LUT					YBLOCKNUM * XBLOCKNUM * HIACE_GAMMA_RANK
#else
#define CE_SIZE_HIST				CE_VALUE_RANK
#define CE_SIZE_LUT					CE_VALUE_RANK
#endif

// Debug parameter
#define ENABLE_EFFECT_HIACE			((int)BIT(0))
#define ENABLE_EFFECT_BL			((int)BIT(1))
#define DEBUG_EFFECT_ENTRY			((int)BIT(0)) // Trace entrance
#define DEBUG_EFFECT_DELAY			((int)BIT(1)) // Count average delay of each step
#define DEBUG_EFFECT_FRAME			((int)BIT(2)) // Trace every frame
#define DEBUG_EFFECT_METADATA		((int)BIT(3)) // Print metadata

/*
*1542 = gamma_r + gamma_g + gamma_b = (257 + 257 + 257) * sizeof(u16);
*1542 = degamma_r + degamma_g + degamma_b = (257 + 257 +257) * sizeof(u16);
*/
#define GM_IGM_LEN (1542 + 1542)

struct hisi_fb_data_type;

typedef enum {
	CE_SERVICE_IDLE = 0,
	CE_SERVICE_HIST_REQ,
	CE_SERVICE_LUT_REQ,
	CE_SERVICE_STATUS_COUNT,
} ce_service_status;

typedef enum {
	CE_MODE_DISABLE = 0,
	CE_MODE_VIDEO,
	CE_MODE_IMAGE,
	CE_MODE_COUNT,
} ce_mode;

typedef enum {
	SCENE_MODE_GALLERY = 0,
	SCENE_MODE_DEFAULT,
	SCENE_MODE_VIDEO,
} scene_mode;

typedef struct dss_display_effect_al {
	int ctrl_al_value; // ambient light
	struct mutex ctrl_lock;
} dss_display_effect_al_t;

typedef struct dss_display_effect_ce {
	int ctrl_ce_mode; //0: disable, 1: weak mode 2: stronger mode
	struct mutex ctrl_lock;
} dss_display_effect_ce_t;

typedef struct dss_display_effect_bl {
	int ctrl_bl_delta; // back light output by BLC algorithm
	struct mutex ctrl_lock;
} dss_display_effect_bl_t;

typedef struct dss_display_effect_bl_enable {
	int ctrl_bl_enable; // 0 -- disable back light algorithm; 1 -- enable algorithm
	struct mutex ctrl_lock;
} dss_display_effect_bl_enable_t;

typedef struct dss_display_effect_sre {
	int ctrl_sre_enable; // 0 -- disable sre algorithm; 1 -- enable sre algorithm
	int ctrl_sre_al; // ambient light
	int ctrl_sre_al_threshold; // ambient light threshold of enable sre
	struct mutex ctrl_lock;
} dss_display_effect_sre_t;

typedef struct dss_display_effect_metadata {
	char metadata[METADATA_SIZE];
	int count;
	struct mutex ctrl_lock;
} dss_display_effect_metadata_t;

typedef struct dss_ce_info {
	// Running control
	bool new_hist_rpt;
	bool first_lut_set;
	bool hiace_enable;
	int gradual_frames;
	bool to_stop_hdr;
	bool to_stop_sre;
#if defined(CONFIG_HISI_FB_3660) || defined (CONFIG_HISI_FB_970)
	struct mutex hist_lock;
	struct mutex lut_lock;
#endif

	// Register value
	int algorithm_result;
	uint32_t lut_sel;
	char __iomem *lut_base;
	uint32_t histogram[CE_SIZE_HIST];
#if defined(CONFIG_HISI_FB_3660) || defined (CONFIG_HISI_FB_970)
	uint32_t lut_table[CE_SIZE_LUT];
#else
	uint8_t lut_table[CE_SIZE_LUT];
#endif

	// Algorithm parameter
	int width; // Image size
	int height; // Image size
	int hist_mode; // 0 -- V of HSV, 1 -- Y of YUV
	int mode; // 0 -- video, 1 -- normal image
	ce_algorithm_parameter_t *p_ce_alg_param;
	int thminv;
} dss_ce_info_t;

typedef struct ce_service {
#if defined(CONFIG_HISI_FB_3660) || defined (CONFIG_HISI_FB_970)
	bool is_ready;
	bool new_hist;
	bool new_lut;
	bool stop;
	bool use_last_value;
#endif
	ce_service_status status;
	wait_queue_head_t wq_hist;
	wait_queue_head_t wq_lut;
	dss_ce_info_t *ce_info;
} ce_service_t;

typedef struct _dynamic_gamma {
	int use_dynamic_gm;
	int use_dynamic_gm_init;
} dss_gm_t;

typedef struct dss_module_update {
	bool acm_effect_updated;
	bool arsr1p_effect_updated;
	bool arsr2p_effect_updated;
	bool lcp_effect_updated;
	bool gamma_effect_updated;
} dss_module_update_t;


/*******************************************************************************
** FUNCTIONS PROTOTYPES
*/
void hisi_effect_init(struct hisi_fb_data_type *hisifd);
void hisi_effect_deinit(struct hisi_fb_data_type *hisifd);

int hisifb_ce_service_blank(int blank_mode, struct fb_info *info);
int hisifb_ce_service_get_support(struct fb_info *info, void __user *argp);
int hisifb_ce_service_get_limit(struct fb_info *info, void __user *argp);
int hisifb_ce_service_get_param(struct fb_info *info, void __user *argp);
int hisifb_ce_service_get_hist(struct fb_info *info, void __user *argp);
int hisifb_ce_service_set_lut(struct fb_info *info, void __user *argp);
ssize_t hisifb_display_effect_al_ctrl_show(struct fb_info *info, char *buf);
ssize_t hisifb_display_effect_al_ctrl_store(struct fb_info *info, const char *buf, size_t count);
ssize_t hisifb_display_effect_ce_ctrl_show(struct fb_info *info, char *buf);
ssize_t hisifb_display_effect_ce_ctrl_store(struct fb_info *info, const char *buf, size_t count);
ssize_t hisifb_display_effect_bl_ctrl_show(struct fb_info *info, char *buf);
ssize_t hisifb_display_effect_bl_enable_ctrl_show(struct fb_info *info, char *buf);
ssize_t hisifb_display_effect_bl_enable_ctrl_store(struct fb_info *info, const char *buf, size_t count);
ssize_t hisifb_display_effect_sre_ctrl_show(struct fb_info *info, char *buf);
ssize_t hisifb_display_effect_sre_ctrl_store(struct fb_info *info, const char *buf, size_t count);
ssize_t hisifb_display_effect_metadata_ctrl_show(struct fb_info *info, char *buf);
ssize_t hisifb_display_effect_metadata_ctrl_store(struct fb_info *info, const char *buf, size_t count);

bool hisifb_display_effect_is_need_ace(struct hisi_fb_data_type *hisifd);
bool hisifb_display_effect_fine_tune_backlight(struct hisi_fb_data_type *hisifd, int backlight_in, int *backlight_out);

void init_acm_ce(struct hisi_fb_data_type *hisifd);
void hisi_dss_dpp_ace_set_reg(struct hisi_fb_data_type *hisifd);
void hisi_dpp_ace_end_handle_func(struct work_struct *work);

#if defined(CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
void init_hiace(struct hisi_fb_data_type *hisifd);
void hisi_dss_dpp_hiace_set_reg(struct hisi_fb_data_type *hisifd);
void hisi_dpp_hiace_end_handle_func(struct work_struct *work);
void hisifb_update_dynamic_gamma(struct hisi_fb_data_type *hisifd, char* buffer, int len);
int hisifb_use_dynamic_gamma(struct hisi_fb_data_type *hisifd, char __iomem *dpp_base);
int hisifb_use_dynamic_degamma(struct hisi_fb_data_type *hisifd, char __iomem *dpp_base);
void hisifb_update_gm_from_reserved_mem(uint32_t *gm_r, uint32_t *gm_g, uint32_t *gm_b, uint32_t *igm_r, uint32_t *igm_g, uint32_t *igm_b);
#else
int do_contrast(dss_ce_info_t *info);
#endif

void hisi_display_effect_init(struct hisi_fb_data_type *hisifd);

int hisi_effect_arsr2p_info_get(struct hisi_fb_data_type *hisifd, struct arsr2p_info *arsr2p);
int hisi_effect_arsr1p_info_get(struct hisi_fb_data_type *hisifd, struct arsr1p_info *arsr1p);
int hisi_effect_acm_info_get(struct hisi_fb_data_type *hisifd, struct acm_info *acm);
int hisi_effect_lcp_info_get(struct hisi_fb_data_type *hisifd, struct lcp_info *lcp);
int hisi_effect_gamma_info_get(struct hisi_fb_data_type *hisifd, struct gamma_info *gamma);

int hisi_effect_arsr2p_info_set(struct hisi_fb_data_type *hisifd, struct arsr2p_info *arsr2p);
int hisi_effect_arsr1p_info_set(struct hisi_fb_data_type *hisifd, struct arsr1p_info *arsr1p);
int hisi_effect_acm_info_set(struct hisi_fb_data_type *hisifd, struct acm_info *acm);
int hisi_effect_lcp_info_set(struct hisi_fb_data_type *hisifd, struct lcp_info *lcp);
int hisi_effect_gamma_info_set(struct hisi_fb_data_type *hisifd, struct gamma_info *gamma);

void hisi_effect_acm_set_reg(struct hisi_fb_data_type *hisifd);
void hisi_effect_lcp_set_reg(struct hisi_fb_data_type *hisifd);
void hisi_effect_gamma_set_reg(struct hisi_fb_data_type *hisifd);
void hisi_dss_effect_set_reg(struct hisi_fb_data_type *hisifd);

int hisi_effect_arsr2p_config(struct arsr2p_info *arsr2p_effect_dst, int ih_inc, int iv_inc);
int hisi_effect_arsr1p_config(struct hisi_fb_data_type *hisifd, dss_overlay_t *pov_req);

#endif  //HISI_DISPLAY_EFFECT_H
