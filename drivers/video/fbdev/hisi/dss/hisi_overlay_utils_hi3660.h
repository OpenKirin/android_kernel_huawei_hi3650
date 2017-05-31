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
#ifndef _HISI_OVERLAY_UTILS_PLATFORM_H_
#define _HISI_OVERLAY_UTILS_PLATFORM_H_

#define CONFIG_DSS_LP_USED
#define HISI_DSS_VERSION_V400

//GPIO
#define GPIO_LCD_POWER_1V2  (54)     //GPIO_6_6
#define GPIO_LCD_STANDBY    (67)     //GPIO_8_3
#define GPIO_LCD_RESETN     (65)     //GPIO_8_1
#define GPIO_LCD_GATING     (60)     //GPIO_7_4
#define GPIO_LCD_PCLK_GATING (58)    //GPIO_7_2
#define GPIO_LCD_REFCLK_GATING (59)  //GPIO_7_3
#define GPIO_LCD_SPICS         (168) //GPIO_21_0
#define GPIO_LCD_DRV_EN        (73)  //GPIO_9_1

#define GPIO_PG_SEL_A (72)    //GPIO_9_0
#define GPIO_TX_RX_A (74)    //GPIO_9_2
#define GPIO_PG_SEL_B (76)    //GPIO_9_4
#define GPIO_TX_RX_B (78)    //GPIO_9_6

/*******************************************************************************
**
*/
#define CRGPERI_PLL0_CLK_RATE	(1600000000UL)
#define CRGPERI_PLL2_CLK_RATE	(960000000UL)
#define CRGPERI_PLL3_CLK_RATE	(1600000000UL)

#define DEFAULT_DSS_CORE_CLK_08V_RATE	(535000000UL)
#define DEFAULT_DSS_CORE_CLK_07V_RATE	(400000000UL)
#define DEFAULT_PCLK_DSS_RATE	(114000000UL)
#define DEFAULT_PCLK_PCTRL_RATE	(80000000UL)
#define DSS_MAX_PXL0_CLK_288M (288000000UL)

//288 KB
#define MMBUF_SIZE_MAX	(288 * 1024)
#define HISI_DSS_CMDLIST_MAX	(16)
#define HISI_DSS_CMDLIST_IDXS_MAX (0xFFFF)   //16 cmdlist, 16bit, 1111,1111,1111,1111=0xFFFF
#define HISI_DSS_COPYBIT_CMDLIST_IDXS	 (0xC000)  //bit14, bit15
#define HISI_DSS_DPP_MAX_SUPPORT_BIT (0x7ff) //10 dpp module, 10bit, contrast to enmu dpp_module_idx
#define HISIFB_DSS_PLATFORM_TYPE  (FB_ACCEL_HI366x | FB_ACCEL_PLATFORM_TYPE_ASIC)

#define DSS_MIF_SMMU_SMRX_IDX_STEP (16)

//PERI REG
#define CRG_PERI_DIS3_DEFAULT_VAL     (0x0002F000)

//scl
#define SCF_LINE_BUF	(2560)

//DSS global
#define DSS_GLB_MODULE_CLK_SEL_DEFAULT_VAL  (0xF0000008)


//LDI0 clk sel
#define DSS_LDI_CLK_SEL_DEFAULT_VAL    (0x00000004)

//DBuf mem ctrl
#define DSS_DBUF_MEM_CTRL_DEFAULT_VAL  (0x00000008)

//SMMU
#define DSS_SMMU_RLD_EN0_DEFAULT_VAL    (0xffffffff)
#define DSS_SMMU_RLD_EN1_DEFAULT_VAL    (0xffffff8f)
#define DSS_SMMU_OUTSTANDING_VAL		(0xf)

//MIF
#define DSS_MIF_CTRL2_INVAL_SEL3_STRIDE_MASK		(0xc)

//AFBCE
#define DSS_AFBCE_ENC_OS_CFG_DEFAULT_VAL			(0x7)

#define TUI_SEC_RCH			(DSS_RCHN_V0)

#define DSS_CHN_MAX_DEFINE (DSS_COPYBIT_MAX)

/* perf stat */
#define DSS_DEVMEM_PERF_BASE						(0xFDF10000)
#define CRG_PERIPH_APB_PERRSTSTAT0_REG 				(0x68)
#define CRG_PERIPH_APB_IP_RST_PERF_STAT_BIT 		(18)
#define PERF_SAMPSTOP_REG 							(0x10)
#define DEVMEM_PERF_SIZE							(0x100)

#endif
