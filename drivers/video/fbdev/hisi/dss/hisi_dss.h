/* include/linux/hisi_dss.h
 *
 * Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef _HISI_DSS_H_
#define _HISI_DSS_H_

#include <linux/types.h>
#include <linux/fb.h>

#define HISIFB_IOCTL_MAGIC 'M'

#define FB_ACCEL_HI62xx     0x1
#define FB_ACCEL_HI363x     0x2
#define FB_ACCEL_HI365x     0x4
#define FB_ACCEL_HI625x     0x8
#define FB_ACCEL_HI366x     0x10
#define FB_ACCEL_KIRIN970  0x20
#define FB_ACCEL_PLATFORM_TYPE_FPGA     0x10000000   //FPGA
#define FB_ACCEL_PLATFORM_TYPE_ASIC     0x20000000   //ASIC


#define HISIFB_LCD_DIRTY_REGION_INFO_GET _IOW(HISIFB_IOCTL_MAGIC, 801, struct lcd_dirty_region_info)
#define HISIFB_PLATFORM_TYPE_GET _IOW(HISIFB_IOCTL_MAGIC, 802, int)

#define HISIFB_VSYNC_CTRL _IOW(HISIFB_IOCTL_MAGIC, 0x02, unsigned int)
#define HISIFB_DSS_CLK_RATE_SET _IOW(HISIFB_IOCTL_MAGIC, 0x04, struct dss_clk_rate)
#define HISIFB_DIRTY_REGION_UPDT_SET _IOW(HISIFB_IOCTL_MAGIC, 0x06, int)
#define HISIFB_DSS_MMBUF_ALLOC _IOW(HISIFB_IOCTL_MAGIC, 0x08, struct dss_mmbuf)
#define HISIFB_DSS_MMBUF_FREE _IOW(HISIFB_IOCTL_MAGIC, 0x09, struct dss_mmbuf)
#define HISIFB_DSS_VOLTAGE_GET _IOW(HISIFB_IOCTL_MAGIC, 0x10, struct dss_clk_rate)
#define HISIFB_DSS_VOLTAGE_SET _IOW(HISIFB_IOCTL_MAGIC, 0x11, struct dss_clk_rate)

#define HISIFB_OV_ONLINE_PLAY _IOW(HISIFB_IOCTL_MAGIC, 0x21, struct dss_overlay)
#define HISIFB_OV_OFFLINE_PLAY _IOW(HISIFB_IOCTL_MAGIC, 0x22, struct dss_overlay)
#define HISIFB_OV_COPYBIT_PLAY _IOW(HISIFB_IOCTL_MAGIC, 0x23, struct dss_overlay)

#define HISIFB_IDLE_IS_ALLOWED  _IOW(HISIFB_IOCTL_MAGIC, 0x42, int)

#define HISIFB_CE_SUPPORT_GET _IOW(HISIFB_IOCTL_MAGIC, 0x50, unsigned int)
#define HISIFB_CE_SERVICE_LIMIT_GET _IOW(HISIFB_IOCTL_MAGIC, 0x51, int)
#define HISIFB_CE_HIST_GET _IOW(HISIFB_IOCTL_MAGIC, 0x52, int)
#define HISIFB_CE_LUT_SET _IOW(HISIFB_IOCTL_MAGIC, 0x53, int)
#define HISIFB_CE_PARAM_GET _IOW(HISIFB_IOCTL_MAGIC, 0x54, int)

#define HISIFB_EFFECT_MODULE_INIT _IOW(HISIFB_IOCTL_MAGIC, 0x54, struct dss_effect)
#define HISIFB_EFFECT_MODULE_DEINIT _IOW(HISIFB_IOCTL_MAGIC, 0x55, struct dss_effect)
#define HISIFB_EFFECT_INFO_GET _IOW(HISIFB_IOCTL_MAGIC, 0x56, struct dss_effect_info)
#define HISIFB_EFFECT_INFO_SET _IOW(HISIFB_IOCTL_MAGIC, 0x57, struct dss_effect_info)


#ifndef BIT
#define BIT(x)  (1<<(x))
#endif

/* for fb0 fb1 fb2 and so on */
#define PRIMARY_PANEL_IDX	(0)
#define EXTERNAL_PANEL_IDX	(1)
#define AUXILIARY_PANEL_IDX	(2)

/* lcd fps scence */
#define LCD_FPS_SCENCE_NORMAL   (0)
#define LCD_FPS_SCENCE_IDLE     BIT(0)
#define LCD_FPS_SCENCE_VIDEO    BIT(1)
#define LCD_FPS_SCENCE_GAME     BIT(2)
#define LCD_FPS_SCENCE_WEB      BIT(3)
#define LCD_FPS_SCENCE_EBOOK    BIT(4)

/* lcd fps value */
#define LCD_FPS_30 (30)
#define LCD_FPS_60 (60)

#define DSS_WCH_MAX  (2)


/* for YUV */
#define MAX_PLANES	(3)

enum dss_wb_compose_type {
	DSS_WB_COMPOSE_PRIMARY = 0,
	DSS_WB_COMPOSE_COPYBIT,
	DSS_WB_COMPOSE_TYPE_MAX,
};

enum hisi_fb_pixel_format {
	HISI_FB_PIXEL_FORMAT_RGB_565 = 0,
	HISI_FB_PIXEL_FORMAT_RGBX_4444,
	HISI_FB_PIXEL_FORMAT_RGBA_4444,
	HISI_FB_PIXEL_FORMAT_RGBX_5551,
	HISI_FB_PIXEL_FORMAT_RGBA_5551,
	HISI_FB_PIXEL_FORMAT_RGBX_8888,
	HISI_FB_PIXEL_FORMAT_RGBA_8888,

	HISI_FB_PIXEL_FORMAT_BGR_565,
	HISI_FB_PIXEL_FORMAT_BGRX_4444,
	HISI_FB_PIXEL_FORMAT_BGRA_4444,
	HISI_FB_PIXEL_FORMAT_BGRX_5551,
	HISI_FB_PIXEL_FORMAT_BGRA_5551,
	HISI_FB_PIXEL_FORMAT_BGRX_8888,
	HISI_FB_PIXEL_FORMAT_BGRA_8888,

	HISI_FB_PIXEL_FORMAT_YUV_422_I,

	/* YUV Semi-planar */
	HISI_FB_PIXEL_FORMAT_YCbCr_422_SP, /* NV16 */
	HISI_FB_PIXEL_FORMAT_YCrCb_422_SP,
	HISI_FB_PIXEL_FORMAT_YCbCr_420_SP,
	HISI_FB_PIXEL_FORMAT_YCrCb_420_SP, /* NV21*/

	/* YUV Planar */
	HISI_FB_PIXEL_FORMAT_YCbCr_422_P,
	HISI_FB_PIXEL_FORMAT_YCrCb_422_P,
	HISI_FB_PIXEL_FORMAT_YCbCr_420_P,
	HISI_FB_PIXEL_FORMAT_YCrCb_420_P, /* HISI_FB_PIXEL_FORMAT_YV12 */

	/* YUV Package */
	HISI_FB_PIXEL_FORMAT_YUYV_422_Pkg,
	HISI_FB_PIXEL_FORMAT_UYVY_422_Pkg,
	HISI_FB_PIXEL_FORMAT_YVYU_422_Pkg,
	HISI_FB_PIXEL_FORMAT_VYUY_422_Pkg,
	HISI_FB_PIXEL_FORMAT_MAX,
};

enum hisi_fb_blending {
	HISI_FB_BLENDING_NONE = 0,
	HISI_FB_BLENDING_PREMULT = 1,
	HISI_FB_BLENDING_COVERAGE = 2,
	HISI_FB_BLENDING_MAX = 3,
};

enum hisi_fb_transform{
	HISI_FB_TRANSFORM_NOP = 0x0,
	/* flip source image horizontally (around the vertical axis) */
	HISI_FB_TRANSFORM_FLIP_H = 0x01,
	/* flip source image vertically (around the horizontal axis)*/
	HISI_FB_TRANSFORM_FLIP_V = 0x02,
	/* rotate source image 90 degrees clockwise */
	HISI_FB_TRANSFORM_ROT_90 = 0x04,
	/* rotate source image 180 degrees */
	HISI_FB_TRANSFORM_ROT_180 = 0x03,
	/* rotate source image 270 degrees clockwise */
	HISI_FB_TRANSFORM_ROT_270 = 0x07,
};

enum dss_csc_mode {
	DSS_CSC_601_WIDE = 0,
	DSS_CSC_601_NARROW,
	DSS_CSC_709_WIDE,
	DSS_CSC_709_NARROW,
	DSS_CSC_MOD_MAX,
};

enum dss_afbc_scramble_mode {
	DSS_AFBC_SCRAMBLE_NONE = 0,
	DSS_AFBC_SCRAMBLE_MODE1,
	DSS_AFBC_SCRAMBLE_MODE2,
	DSS_AFBC_SCRAMBLE_MODE3,
	DSS_AFBC_SCRAMBLE_MODE_MAX,
};

enum dss_chn_idx {
	DSS_RCHN_NONE = -1,
	DSS_RCHN_D2 = 0,
	DSS_RCHN_D3,
	DSS_RCHN_V0,
	DSS_RCHN_G0,
	DSS_RCHN_V1,
	DSS_RCHN_G1,
	DSS_RCHN_D0,
	DSS_RCHN_D1,

	DSS_WCHN_W0,
	DSS_WCHN_W1,

	DSS_CHN_MAX,

	DSS_RCHN_V2 = DSS_CHN_MAX,  //for copybit, only supported in chicago
	DSS_WCHN_W2,

	DSS_COPYBIT_MAX,
};

enum dss_ovl_idx {
	DSS_OVL0 = 0,
	DSS_OVL1,
	DSS_OVL2,
	DSS_OVL3,
	DSS_OVL_IDX_MAX,
};

/* dss capability priority description */
#define CAP_1D_SHARPNESS	BIT(13)
#define CAP_2D_SHARPNESS	BIT(12)
#define CAP_TILE	BIT(11)
#define CAP_AFBCD	BIT(10)
#define CAP_AFBCE	BIT(9)
#define CAP_YUV_DEINTERLACE	BIT(8)
#define CAP_YUV_PLANAR	BIT(7)
#define CAP_YUV_SEMI_PLANAR	BIT(6)
#define CAP_YUV_PACKAGE	BIT(5)
#define CAP_SCL	BIT(4)
#define CAP_ROT	BIT(3)
#define CAP_PURE_COLOR	BIT(2)
#define CAP_DIM	BIT(1)
#define CAP_BASE	BIT(0)

//this head file to save the structs that both ade and dss will use
//note: if the left_align is 8,right_align is 8,and w_min is larger than 802,then w_min should be set to 808,
//make sure that it is 8 align,if w_min is set to 802,there will be an error.left_align,right_align,top_align
//bottom_align,w_align,h_align,w_min and h_min's valid value should be larger than 0,top_start and bottom_start
//maybe equal to 0. if it's not surpport partial update, these value should set to invalid value(-1).
typedef struct lcd_dirty_region_info {
    int left_align;
    int right_align;
    int top_align;
    int bottom_align;

    int w_align;
    int h_align;
    int w_min;
    int h_min;

    int top_start;
    int bottom_start;
} lcd_dirty_region_info_t;

typedef struct dss_rect {
	int32_t x;
	int32_t y;
	int32_t w;
	int32_t h;
} dss_rect_t;

typedef struct dss_rect_ltrb {
	int32_t left;
	int32_t top;
	int32_t right;
	int32_t bottom;
} dss_rect_ltrb_t;

typedef struct dss_mmbuf {
	uint32_t addr;
	int32_t size;
} dss_mmbuf_t;

typedef struct dss_img {
	uint32_t format;
	uint32_t width;
	uint32_t height;
	uint32_t bpp;	/* bytes per pixel */
	uint32_t buf_size;
	uint32_t stride;
	uint32_t stride_plane1;
	uint32_t stride_plane2;
	uint64_t phy_addr;
	uint64_t vir_addr;
	uint32_t offset_plane1;
	uint32_t offset_plane2;

	uint64_t afbc_header_addr;
	uint64_t afbc_payload_addr;
	uint32_t afbc_header_stride;
	uint32_t afbc_payload_stride;
	uint32_t afbc_scramble_mode;
	uint32_t mmbuf_base;
	uint32_t mmbuf_size;

	uint32_t mmu_enable;
	uint32_t csc_mode;
	uint32_t secure_mode;
	int32_t shared_fd;
	uint32_t reserved0;
} dss_img_t;

typedef struct dss_block_info {
	int32_t first_tile;
	int32_t last_tile;
	uint32_t acc_hscl;
	uint32_t h_ratio;
	uint32_t v_ratio;
	uint32_t h_ratio_arsr2p;
	uint32_t arsr2p_left_clip;
	uint32_t both_vscfh_arsr2p_used;
	dss_rect_t arsr2p_in_rect;
	uint32_t arsr2p_src_x; //new added
	uint32_t arsr2p_src_y; //new added
	uint32_t arsr2p_dst_x; //new added
	uint32_t arsr2p_dst_y; //new added
	uint32_t arsr2p_dst_w; //new added
	int32_t h_v_order;
} dss_block_info_t;

typedef struct dss_layer {
	dss_img_t img;
	dss_rect_t src_rect;
	dss_rect_t src_rect_mask;
	dss_rect_t dst_rect;
	uint32_t transform;
	int32_t blending;
	uint32_t glb_alpha;
	uint32_t color; /* background color or dim color */
	int32_t layer_idx;
	int32_t chn_idx;
	uint32_t need_cap;
	int32_t acquire_fence;

	dss_block_info_t block_info;
} dss_layer_t;

typedef struct dss_wb_layer {
	dss_img_t dst;
	dss_rect_t src_rect;
	dss_rect_t dst_rect;
	uint32_t transform;
	int32_t chn_idx;
	uint32_t need_cap;
	uint32_t reserved0;

	int32_t acquire_fence;
	int32_t release_fence;
} dss_wb_layer_t;


/*
** dss error status
*/
#define DSS_PDP_LDI_UNDERFLOW		BIT(0)
#define DSS_SDP_LDI_UNDERFLOW		BIT(1)
#define DSS_PDP_SMMU_ERR			BIT(2)
#define DSS_SDP_SMMU_ERR			BIT(3)

/*
** crc enable status
*/
enum dss_crc_enable_status {
	DSS_CRC_NONE = 0,
	DSS_CRC_OV_EN = 1,
	DSS_CRC_LDI_EN,
	DSS_CRC_SUM_EN,
};

/*
** sec enable status
*/
enum dss_sec_enable_status {
	DSS_SEC_STOP = 0,
	DSS_SEC_RUN = 1,
};

typedef struct dss_crc_info {
	uint32_t crc_ov_result;
	uint32_t crc_ldi_result;
	uint32_t crc_sum_result;
	uint32_t crc_ov_frm;
	uint32_t crc_ldi_frm;
	uint32_t crc_sum_frm;

	uint32_t err_status;
	uint32_t reserved0;
} dss_crc_info_t;

enum dss_to_be_continued_type {
	DSS_LAYER_SERIAL_COMPOSE = 0,
	DSS_LAYER_PARALLEL_COMPOSE = 1,
};

/* Max multi-src channel number of the DSS. */
#define MAX_DSS_SRC_NUM	(7)
#define MAX_DSS_DST_NUM	(2)

#define HISI_DSS_OV_BLOCK_NUMS	(23)

typedef struct dss_overlay_block {
	dss_layer_t layer_infos[MAX_DSS_SRC_NUM];
	dss_rect_t ov_block_rect;
	uint32_t layer_nums;
	uint32_t reserved0;
} dss_overlay_block_t;

typedef struct dss_overlay {
	dss_wb_layer_t wb_layer_infos[MAX_DSS_DST_NUM];
	dss_rect_t wb_ov_rect;
	uint32_t wb_layer_nums;
	uint32_t wb_compose_type;

	// struct dss_overlay_block
	uint64_t ov_block_infos_ptr;
	uint32_t ov_block_nums;
	int32_t ovl_idx;
	uint32_t wb_enable;
	uint32_t frame_no;

	// dirty region
	dss_rect_t dirty_rect;

	// resolution change
	struct dss_rect res_updt_rect;

	// crc
	dss_crc_info_t crc_info;
	int32_t crc_enable_status;
	uint32_t sec_enable_status;

	uint32_t to_be_continued;
	int32_t release_fence;
} dss_overlay_t;

typedef struct dss_clk_rate {
	uint64_t dss_pri_clk_rate;
	uint64_t dss_pclk_dss_rate;
	uint64_t dss_pclk_pctrl_rate;
	uint32_t dss_voltage_value; //0:0.7v, 2:0.8v
} dss_clk_rate_t;

typedef struct ce_algorithm_parameter {
	int iDiffMaxTH;
	int iDiffMinTH;
	int iAlphaMinTH;
	int iFlatDiffTH;
	int iBinDiffMaxTH;

	int iDarkPixelMinTH;
	int iDarkPixelMaxTH;
	int iDarkAvePixelMinTH;
	int iDarkAvePixelMaxTH;
	int iWhitePixelTH;
	int fweight;
	int fDarkRatio;
	int fWhiteRatio;

	int iDarkPixelTH;
	int fDarkSlopeMinTH;
	int fDarkSlopeMaxTH;
	int fDarkRatioMinTH;
	int fDarkRatioMaxTH;

	int iBrightPixelTH;
	int fBrightSlopeMinTH;
	int fBrightSlopeMaxTH;
	int fBrightRatioMinTH;
	int fBrightRatioMaxTH;

	int iZeroPos0MaxTH;
	int iZeroPos1MaxTH;

	int iDarkFMaxTH;
	int iDarkFMinTH;
	int iPos0MaxTH;
	int iPos0MinTH;

	int fKeepRatio;
} ce_algorithm_parameter_t;

typedef struct ce_parameter {
	int width;
	int height;
	int hist_mode;
	int mode;
	int result;
	uint32_t reserved0;
	uint32_t *histogram;
	uint8_t *lut_table;
	void *service;
	ce_algorithm_parameter_t ce_alg_param;
} ce_parameter_t;

//HIACE struct
typedef struct hiace_alg_parameter {
	//paramters to avoid interference of black/white edge
	int iGlobalHistBlackPos;
	int iGlobalHistWhitePos;
	int iGlobalHistBlackWeight;
	int iGlobalHistWhiteWeight;
	int iGlobalHistZeroCutRatio;
	int iGlobalHistSlopeCutRatio;

	//Photo metadata
	char Classifieresult[1024];
	int iResultLen;

	//function enable/disable switch
	int iDoLCE;
	int iDoSRE;
	int iDoAPLC;

	// minimum ambient light to enable SRE
	int iLaSensorSREOnTH;

	int iWidth;
	int iHeight;
	int bitWidth;
	int iMode;                      // Image(1) or Video(0) mode
	int iLevel;                     // Video(0), gallery(1) ...
	int ilhist_sft;

	int iMaxLcdLuminance;
	int iMinLcdLuminance;
	int iMaxBackLight;
	int iMinBackLight;
	int iAmbientLight;
	int iBackLight;
	long lTimestamp;                 // Timestamp of frame in millisecond

	// path of xml file
	char chCfgName[512];
} hiace_alg_parameter_t;

typedef struct hiace_interface_set {
	int result;
	unsigned int *lut;
	int backlight;
	int thminv;
} hiace_interface_set_t;

typedef enum dss_module_id {
	DSS_EFFECT_MODULE_ARSR2P	= BIT(0),
	DSS_EFFECT_MODULE_ARSR1P	= BIT(1),
	DSS_EFFECT_MODULE_ACM		= BIT(2),
	DSS_EFFECT_MODULE_SBL		= BIT(3),
	DSS_EFFECT_MODULE_HIACE		= BIT(4),
	DSS_EFFECT_MODULE_LCP_GMP	= BIT(5),
	DSS_EFFECT_MODULE_LCP_IGM	= BIT(6),
	DSS_EFFECT_MODULE_LCP_XCC	= BIT(7),
	DSS_EFFECT_MODULE_GAMMA		= BIT(8),
	DSS_EFFECT_MODULE_DITHER	= BIT(9),
	DSS_EFFECT_MODULE_ACE		= BIT(10),
	DSS_EFFECT_MODULE_MAX		= BIT(11),
} dss_module_id;

// for 32/64 bit compatiable
#define compat_pointer(x) \
	union { \
		uint32_t* x; \
		uint64_t x##_sizer; \
	}

// acm algorithm info define, mem_ctrl decide by enable or not
struct acm_info {
	uint32_t enable;
	uint32_t para_mode;
	uint32_t hue_r0_hh;
	uint32_t hue_r0_lh;
	uint32_t hue_r1_hh;
	uint32_t hue_r1_lh;
	uint32_t hue_r2_hh;
	uint32_t hue_r2_lh;
	uint32_t hue_r3_hh;
	uint32_t hue_r3_lh;
	uint32_t hue_r4_hh;
	uint32_t hue_r4_lh;
	uint32_t hue_r5_hh;
	uint32_t hue_r5_lh;
	uint32_t hue_r6_hh;
	uint32_t hue_r6_lh;
	compat_pointer(hue_table);
	compat_pointer(sata_table);
	compat_pointer(satr0_table);
	compat_pointer(satr1_table);
	compat_pointer(satr2_table);
	compat_pointer(satr3_table);
	compat_pointer(satr4_table);
	compat_pointer(satr5_table);
	compat_pointer(satr6_table);
	compat_pointer(satr7_table);
};

struct arsr1p_info {
	uint32_t enable;
	uint32_t para_mode;
	uint32_t sharp_enable;
	uint32_t skin_enable;
	uint32_t shoot_enable;
	uint32_t skin_thres_y;
	uint32_t skin_thres_u;
	uint32_t skin_thres_v;
	uint32_t skin_expected;
	uint32_t skin_cfg;
	uint32_t shoot_cfg1;
	uint32_t shoot_cfg2;
	uint32_t sharp_cfg1;
	uint32_t sharp_cfg2;
	uint32_t sharp_cfg3;
	uint32_t sharp_cfg4;
	uint32_t sharp_cfg5;
	uint32_t sharp_cfg6;
	uint32_t sharp_cfg7;
	uint32_t sharp_cfg8;
	uint32_t sharp_cfg9;
	uint32_t sharp_cfg10;
	uint32_t sharp_cfg11;
	uint32_t diff_ctrl;
	uint32_t lsc_cfg1;
	uint32_t lsc_cfg2;
	uint32_t lsc_cfg3;
};

// define arsr2p effect parameter
struct arsr2p_info {
	uint32_t enable;
	uint32_t sharp_enable;
	uint32_t skin_enable;
	uint32_t shoot_enable;
	uint32_t skin_thres_y;
	uint32_t skin_thres_u;
	uint32_t skin_thres_v;
	uint32_t skin_cfg0;
	uint32_t skin_cfg1;
	uint32_t skin_cfg2;
	uint32_t shoot_cfg1;
	uint32_t shoot_cfg2;
	uint32_t sharp_cfg1;
	uint32_t sharp_cfg2;
	uint32_t sharp_cfg3;
	uint32_t sharp_cfg4;
	uint32_t sharp_cfg5;
	uint32_t sharp_cfg6;
	uint32_t sharp_cfg7;
	uint32_t sharp_cfg8;
	uint32_t sharp_cfg9;
	uint32_t texturw_analysts;
	uint32_t intplshootctrl;
};

struct lcp_info {
	uint32_t gmp_enable;
	uint32_t xcc_enable;
	uint32_t igm_enable;
	compat_pointer(gmp_table_low32); //gmp lut length is 9*9*9
	compat_pointer(gmp_table_high4);
	compat_pointer(igm_r_table); //igm lut length is 257, the same with gamma
	compat_pointer(igm_g_table);
	compat_pointer(igm_b_table);
	compat_pointer(xcc_table);
};

struct gamma_info {
	uint32_t enable;
	uint32_t para_mode;
	compat_pointer(gamma_r_table); //gamma lut length 257
	compat_pointer(gamma_g_table);
	compat_pointer(gamma_b_table);
};

struct dss_effect {
	bool dss_ready;
	bool arsr2p_sharp_support;
	bool arsr1p_sharp_support;
	bool acm_support;
	bool sbl_support;
	bool ace_support;
	bool hiace_support;
	bool lcp_igm_support;
	bool lcp_gmp_support;
	bool lcp_xcc_support;
	bool gamma_support;
	bool dither_support;
};

struct dss_effect_info {
	uint32_t modules;

	struct acm_info acm;
	struct arsr1p_info arsr1p;
	struct arsr2p_info arsr2p;
	struct lcp_info lcp;
	struct gamma_info gamma;
};

#endif /*_HISI_DSS_H_*/
