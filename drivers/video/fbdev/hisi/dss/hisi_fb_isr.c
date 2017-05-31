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

#include "hisi_fb.h"
#include "hisi_overlay_utils.h"


/*******************************************************************************
** handle isr
*/
irqreturn_t dss_pdp_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_s1 = 0;
	uint32_t isr_s2 = 0;
	uint32_t isr_s2_dpp = 0;
#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	uint32_t isr_s2_rch = 0;
#endif
	uint32_t isr_s2_smmu = 0;
	uint32_t mask = 0;
	uint32_t isr_te_vsync = 0;
	uint32_t i = 0;
	uint32_t temp = 0;
	struct timeval tv;
	struct hisifb_secure *secure_ctrl = NULL;
	dss_module_reg_t *dss_module = NULL;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);
	secure_ctrl = &(hisifd->secure_ctrl);
	dss_module = &(hisifd->dss_module);

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_PDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INTS);
	isr_s2_dpp = inp32(hisifd->dss_base + GLB_GLB_DPP_INTS);
	isr_s2_rch = inp32(hisifd->dss_base + GLB_RCH_CE_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + GLB_RCH_CE_INTS, isr_s2_rch);
	outp32(hisifd->dss_base + GLB_GLB_DPP_INTS, isr_s2_dpp);
	outp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_PDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_PDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INT_MSK));
	isr_s2_dpp &= ~(inp32(hisifd->dss_base + GLB_GLB_DPP_INT_MSK));
	isr_s2_rch &= ~(inp32(hisifd->dss_base + GLB_RCH_CE_INT_MSK));
#elif defined(CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_PDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INTS);
	isr_s2_dpp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_INTS, isr_s2_dpp);
	outp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_PDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_PDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INT_MSK));
	isr_s2_dpp &= ~(inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_INT_MSK));
#endif

	if (is_mipi_cmd_panel(hisifd)) {
		isr_te_vsync = BIT_LCD_TE0_PIN;
	} else {
		isr_te_vsync = BIT_VSYNC;
	}

	if (isr_s2 & BIT_VACTIVE0_END) {
		hisifd->vactive0_end_flag = 1;

		if (hisifd->color_temperature_flag > 0)
			hisifd->color_temperature_flag--;

		if (hisifd->panel_info.dsi_bit_clk_upt_support
			&& hisifd->mipi_dsi_bit_clk_upt_isr_handler
			&& (hisifd->panel_info.mipi.dsi_bit_clk_upt != hisifd->panel_info.mipi.dsi_bit_clk)) {

			if (!(isr_s2 & BIT_VACTIVE0_START)) {
				hisifd->mipi_dsi_bit_clk_upt_isr_handler(hisifd);
			}
		} else if (hisifd->panel_info.fps_updt_support
			&& hisifd->fps_upt_isr_handler
			&& (hisifd->panel_info.fps_updt != hisifd->panel_info.fps)) {
			hisifd->fps_upt_isr_handler(hisifd);
		} else {
			;
		}

		if (secure_ctrl->notify_secure_switch) {
			secure_ctrl->notify_secure_switch(hisifd);
		}

		if (g_err_status & DSS_PDP_LDI_UNDERFLOW) {
			temp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_DBG_CNT);
			HISI_FB_INFO("fb%d, BIT_VACTIVE0_END: frame_no=%d, dpp_dbg =0x%x\n",
				hisifd->index, hisifd->ov_req.frame_no, temp);
			g_err_status &= ~DSS_PDP_LDI_UNDERFLOW;
		}
	}

	if (isr_s2 & BIT_VACTIVE0_START) {
		if (hisifd->ov_vactive0_start_isr_handler) {
			hisifd->ov_vactive0_start_isr_handler(hisifd);
		}

		if (g_err_status & DSS_PDP_LDI_UNDERFLOW) {
			temp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_DBG_CNT);
			HISI_FB_INFO("fb%d, BIT_VACTIVE0_START: frame_no=%d, dpp_dbg=0x%x\n",
				hisifd->index, hisifd->ov_req.frame_no, temp);
		}
	}

	if (isr_s2 & isr_te_vsync) {
		if (hisifd->vsync_isr_handler) {
			hisifd->vsync_isr_handler(hisifd);
		}

		if (hisifd->buf_sync_signal) {
			hisifd->buf_sync_signal(hisifd);
		}

		if (g_err_status & (DSS_PDP_LDI_UNDERFLOW | DSS_PDP_SMMU_ERR | DSS_SDP_SMMU_ERR)) {
			temp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_DBG_CNT);
			HISI_FB_INFO("isr_te_vsync:frame_no = %d,dpp_dbg = 0x%x\n", hisifd->ov_req.frame_no, temp);
		}

		if (g_debug_ldi_underflow) {
			hisifb_get_timestamp(&tv);
			HISI_FB_INFO("isr_te_vsync:frame_no = %d,isr_s2 = 0x%x\n", hisifd->ov_req.frame_no, isr_s2);
		}
	}

	if (isr_s2 & BIT_LDI_UNFLOW) {
	#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
		mask = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + GLB_GLB_CPU_ITF0_INT_MSK, mask);
	#elif defined(CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
		mask = inp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + DSS_LDI0_OFFSET + LDI_CPU_ITF_INT_MSK, mask);
	#endif

		if (g_debug_ldi_underflow_clear) {
			if (is_mipi_cmd_panel(hisifd)) {
				if (g_ldi_data_gate_en == 0) {
					if (hisifd->ldi_underflow_wq) {
						disable_ldi(hisifd);
						queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
					}
				}
			} else {
				if (hisifd->ldi_underflow_wq) {
					disable_ldi(hisifd);
					queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
				}
			}
		}

		if (g_debug_ldi_underflow) {
			if (g_debug_ovl_online_composer) {
				if (hisifd->dss_debug_wq)
					queue_work(hisifd->dss_debug_wq, &hisifd->dss_debug_work);
			}
		}

		g_err_status |= DSS_PDP_LDI_UNDERFLOW;

		if (hisifd->ldi_data_gate_en == 0) {
			//FIXME:
			temp = inp32(hisifd->dss_base + DSS_DPP_OFFSET + DPP_DBG_CNT);
			HISI_FB_INFO("ldi underflow! frame_no = %d,dpp_dbg = 0x%x!\n", hisifd->ov_req.frame_no,temp);

			//FIXME:
			for (i = 0; i < DSS_WCHN_W0; i++) {
			    if ((i != DSS_RCHN_V0) && (i != DSS_RCHN_G0)) {
					HISI_FB_INFO("RCH[%d], DMA_BUF_DBG0 = 0x%x,DMA_BUF_DBG1 = 0x%x!!\n", i,
						inp32(dss_module->dma_base[i]+ DMA_BUF_DBG0),
						inp32(dss_module->dma_base[i]+ DMA_BUF_DBG1));
				}
			}

			//FIXME:
			for (i = 0; i < 18; i++) {
				HISI_FB_INFO("MCTL_MOD%d_STATUS = 0x%x\n",
					i, inp32(dss_module->mctl_sys_base + MCTL_MOD0_STATUS + i * 0x4));
			}

		#if defined (CONFIG_HUAWEI_DSM)
			if (hisifd->dss_underflow_debug_workqueue && !g_fake_lcd_flag)
				queue_work(hisifd->dss_underflow_debug_workqueue, &hisifd->dss_underflow_debug_work);
		#endif
		}
	}

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	if (isr_s2_rch & BIT_CE_END_RCH4_IND) {
		if (hisifd->panel_info.prefix_ce_support && hisifd->rch4_ce_end_wq) {
			queue_work(hisifd->rch4_ce_end_wq, &hisifd->rch4_ce_end_work);
		}
	}

	if (isr_s2_rch & BIT_CE_END_RCH2_IND) {
		if (hisifd->panel_info.prefix_ce_support && hisifd->rch2_ce_end_wq) {
			queue_work(hisifd->rch2_ce_end_wq, &hisifd->rch2_ce_end_work);
		}
	}

	if (isr_s2_dpp & BIT_CE_END_IND) {
		if (hisifd->panel_info.acm_ce_support
		 && g_dss_effect_acm_ce_en == 1
		 && hisifd->dpp_ce_end_wq
		 && HISI_DSS_SUPPORT_DPP_MODULE_BIT(DPP_MODULE_ACE)) {
			queue_work(hisifd->dpp_ce_end_wq, &hisifd->dpp_ce_end_work);
		}
	}

	if (isr_s2_dpp & BIT_BACKLIGHT_INTP) {
		hisifb_sbl_isr_handler(hisifd);
	}

	if (isr_s2_smmu & 0x3f) {
		if (g_debug_mmu_error == 1) {
			g_err_status |= DSS_PDP_SMMU_ERR;

			HISI_FB_ERR("fb%d, "
				"SMMU_INTSTAT_NS=0x%x, "
				"SMMU_FAULT_ADDR=0x%x, "
				"SMMU_FAULT_ID=0x%x,"
				"SMMU_FAULT_INFO=0x%x!\n",
				hisifd->index, isr_s2_smmu,
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ADDR),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ID),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_INFO));
		}
	} else {
		g_err_status &= ~DSS_PDP_SMMU_ERR;
		if (g_debug_layerbuf_sync) {
			g_debug_layerbuf_sync--;
		}
	}
#elif defined(CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
	#ifdef DISPLAY_EFFECT_USE_FRM_END_INT
		if (isr_s2 & BIT_FRM_END) {
			if (hisifd->panel_info.hiace_support && hisifd->hiace_end_wq) {
				queue_work(hisifd->hiace_end_wq, &hisifd->hiace_end_work);
			}
		}
	#else
		if (isr_s2_dpp & BIT_HIACE_IND) {
			if (hisifd->panel_info.hiace_support && hisifd->hiace_end_wq) {
				queue_work(hisifd->hiace_end_wq, &hisifd->hiace_end_work);
			}
		}
	#endif

	if (isr_s2_dpp & BIT_CE_END_IND) {
		if (hisifd->panel_info.acm_ce_support && hisifd->dpp_ce_end_wq) {
			queue_work(hisifd->dpp_ce_end_wq, &hisifd->dpp_ce_end_work);
		}
	}
#endif

	return IRQ_HANDLED;
}

irqreturn_t dss_sdp_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_s1 = 0;
	uint32_t isr_s2 = 0;
	uint32_t isr_s2_smmu = 0;
	uint32_t mask = 0;

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_SDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_SDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_SDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INT_MSK));
#elif defined(CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_SDP_INTS);
	isr_s2 = inp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INTS, isr_s2);
	outp32(hisifd->dss_base + GLB_CPU_SDP_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_SDP_INT_MSK));
	isr_s2 &= ~(inp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INT_MSK));
#endif

	if (isr_s2 & BIT_VACTIVE0_END) {
		hisifd->vactive0_end_flag = 1;
	}

	if (isr_s2 & BIT_VACTIVE0_START) {
		if (hisifd->ov_vactive0_start_isr_handler)
			hisifd->ov_vactive0_start_isr_handler(hisifd);
	}

	if (isr_s2 & BIT_VSYNC) {
		if (hisifd->vsync_isr_handler) {
			hisifd->vsync_isr_handler(hisifd);
		}

		if (hisifd->buf_sync_signal) {
			hisifd->buf_sync_signal(hisifd);
		}
	}

	if (isr_s2 & BIT_LDI_UNFLOW) {
#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
		mask = inp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + GLB_GLB_CPU_ITF1_INT_MSK, mask);
#elif defined(CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
		mask = inp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INT_MSK);
		mask |= BIT_LDI_UNFLOW;
		outp32(hisifd->dss_base + DSS_LDI1_OFFSET + LDI_CPU_ITF_INT_MSK, mask);
#endif
		if (g_debug_ldi_underflow_clear) {
			if (is_mipi_cmd_panel(hisifd)) {
				if (g_ldi_data_gate_en == 0) {
					if (hisifd->ldi_underflow_wq) {
						disable_ldi(hisifd);
						queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
					}
				}
			} else {
				if (hisifd->ldi_underflow_wq) {
					disable_ldi(hisifd);
					queue_work(hisifd->ldi_underflow_wq, &hisifd->ldi_underflow_work);
				}
			}
		}

		if (g_debug_ldi_underflow) {
			if (g_debug_ovl_online_composer) {
				if (hisifd->dss_debug_wq)
					queue_work(hisifd->dss_debug_wq, &hisifd->dss_debug_work);
			}
		}

		g_err_status |= DSS_SDP_LDI_UNDERFLOW;

		if (hisifd->ldi_data_gate_en == 0)
			HISI_FB_ERR("ldi underflow!\n");
	}

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	if (isr_s2_smmu & 0x3f) {
		if (g_debug_mmu_error == 1) {
			g_err_status |= DSS_PDP_SMMU_ERR;
			HISI_FB_INFO("fb%d, SMMU_FAULT_ADDR=0x%x, SMMU_FAULT_ID=0x%x, SMMU_FAULT_INFO=0x%x!\n",
				hisifd->index,
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ADDR),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ID),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_INFO));
		}
	} else {
		g_err_status &= ~DSS_PDP_SMMU_ERR;
	}
#endif
	return IRQ_HANDLED;
}

irqreturn_t dss_adp_isr(int irq, void *ptr)
{
	struct hisi_fb_data_type *hisifd = NULL;
	uint32_t isr_s1 = 0;
	uint32_t isr_s2_smmu = 0;
#if defined(CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
	uint32_t isr_s3_copybit = 0;
#endif

	hisifd = (struct hisi_fb_data_type *)ptr;
	BUG_ON(hisifd == NULL);

	isr_s1 = inp32(hisifd->dss_base + GLB_CPU_OFF_INTS);
	isr_s2_smmu = inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTSTAT_NS);

	outp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_INTCLR_NS, isr_s2_smmu);
	outp32(hisifd->dss_base + GLB_CPU_OFF_INTS, isr_s1);

	isr_s1 &= ~(inp32(hisifd->dss_base + GLB_CPU_OFF_INT_MSK));
#if defined(CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
	isr_s3_copybit = inp32(hisifd->dss_base + GLB_CPU_OFF_CAM_INTS);
	outp32(hisifd->dss_base + GLB_CPU_OFF_CAM_INTS, isr_s3_copybit);
	isr_s3_copybit &= ~(inp32(hisifd->dss_base + GLB_CPU_OFF_CAM_INT_MSK));
#endif

#ifdef CONFIG_FIX_DSS_WCH_ISR_BUG
	if (isr_s1 & BIT_OFF_CMDLIST8) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH0] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH0] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH0]));
		}

		outp32(hisifd->dss_base + DSS_CMDLIST_OFFSET + CMDLIST_CH0_INTC + DSS_CMDLIST_W0 *0x40, 0xFF);
	}

	if (isr_s1 & BIT_OFF_CMDLIST9) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH1] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH1] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH1]));
		}

		outp32(hisifd->dss_base + DSS_CMDLIST_OFFSET + CMDLIST_CH0_INTC + DSS_CMDLIST_W1 *0x40, 0xFF);
	}
#else
	if (isr_s1 & BIT_OFF_WCH0_INTS) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH0] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH0] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH0]));
		}
	}

	if (isr_s1 & BIT_OFF_WCH1_INTS) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH1] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH1] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH1]));
		}
	}

	if (isr_s1 & BIT_OFF_WCH0_WCH1_FRM_END_INT) {
		if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH0_WCH1] == 1) {
			hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH0_WCH1] = 1;
			wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH0_WCH1]));
		}
	}

	#if defined(CONFIG_HISI_FB_3660) || defined(CONFIG_HISI_FB_970)
		if (isr_s3_copybit & BIT_OFF_CAM_WCH2_FRMEND_INTS) {
			if (hisifd->copybit_info->copybit_flag == 1) {
				hisifd->copybit_info->copybit_done = 1;
				wake_up_interruptible_all(&(hisifd->copybit_info->copybit_wq));
			}

			if (hisifd->cmdlist_info->cmdlist_wb_flag[WB_TYPE_WCH2] == 1) {
				hisifd->cmdlist_info->cmdlist_wb_done[WB_TYPE_WCH2] = 1;
				wake_up_interruptible_all(&(hisifd->cmdlist_info->cmdlist_wb_wq[WB_TYPE_WCH2]));
			}
		}
	#endif
#endif

#if defined(CONFIG_HISI_FB_3650) || defined(CONFIG_HISI_FB_6250)
	if (isr_s2_smmu & 0x3f) {
		if (g_debug_mmu_error == 1) {
			HISI_FB_INFO("fb%d, SMMU_FAULT_ADDR=0x%x, SMMU_FAULT_ID=0x%x, SMMU_FAULT_INFO=0x%x!\n",
				hisifd->index,
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ADDR),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_ID),
				inp32(hisifd->dss_base + DSS_SMMU_OFFSET + SMMU_FAULT_INFO));
		}
	}
#endif

	return IRQ_HANDLED;
}
