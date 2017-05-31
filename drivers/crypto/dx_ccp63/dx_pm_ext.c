/***************************************************************
*  Copyright 2014 (c) Discretix Technologies Ltd.              *
*  This software is protected by copyright, international      *
*  treaties and various patents. Any copy, reproduction or     *
*  otherwise use of this software must be authorized in a      *
*  license agreement and include this Copyright Notice and any *
*  other notices specified in the license agreement.           *
*  Any redistribution in binary form must be authorized in the *
*  license agreement and include this Copyright Notice and     *
*  any other notices specified in the license agreement and/or *
*  in materials provided with the binary distribution.         *
****************************************************************/


#include "dx_config.h"
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/interrupt.h>
#include <crypto/ctr.h>
#include <linux/pm_runtime.h>
#include <linux/clk.h>
#include "dx_driver.h"
#include "dx_sram_mgr.h"

#ifdef CONFIG_CRYPTO_SECP_POWER_CTRL
#include <soc_crgperiph_interface.h>
#include <soc_acpu_baseaddr_interface.h>

#define SOC_ACPU_PERI_CRG_SIZE 	(0x1000)
#define SECP_WORK_FREQ 			(115000000)

void secp_reset(void)
{
	void __iomem *peri_crg_base = NULL;

	peri_crg_base = ioremap(SOC_ACPU_PERI_CRG_BASE_ADDR, SOC_ACPU_PERI_CRG_SIZE);
	if (unlikely(peri_crg_base == NULL)) {
		DX_LOG_ERR("secp_reset: ioremap failed!\n");
		return;
	}
	/*secp*/
	WRITE_REGISTER(SOC_CRGPERIPH_PERRSTEN4_ADDR(peri_crg_base), 0x8000);
	DX_LOG(KERN_INFO, "secp_reset success!\n");
}

void secp_unreset(void)
{
	void __iomem *peri_crg_base = NULL;

	peri_crg_base = ioremap(SOC_ACPU_PERI_CRG_BASE_ADDR, SOC_ACPU_PERI_CRG_SIZE);
	if (unlikely(peri_crg_base == NULL)) {
		DX_LOG_ERR("secp_unreset: ioremap failed!\n");
		return;
	}
	/*secp clk disable*/
	WRITE_REGISTER(SOC_CRGPERIPH_PERRSTDIS4_ADDR(peri_crg_base), 0x8000);
	DX_LOG(KERN_INFO, "secp_unreset success!\n");
}
#endif

/*
This function should suspend the HW (if possiable), It should be implemented by 
the driver user. 
The reference code clears the internal SRAM to imitate lose of state. 
*/
void dx_pm_ext_hw_suspend(struct device *dev)
{
	struct dx_drvdata *drvdata =
		(struct dx_drvdata *)dev_get_drvdata(dev);
	unsigned int val;
	void __iomem *cc_base = drvdata->cc_base;
	unsigned int  sram_addr = 0;
#if DX_CC_HAS_ROM 
	sram_addr = READ_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, HOST_SEP_SRAM_THRESHOLD));
#endif

	WRITE_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, SRAM_ADDR), sram_addr);

	for (;sram_addr < DX_CC_SRAM_SIZE ; sram_addr+=4) {
		WRITE_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, SRAM_DATA), 0x0);

		do {
			val = READ_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, SRAM_DATA_READY));
		} while (!(val &0x1));
	}
	WRITE_REGISTER(cc_base + DX_CC_REG_OFFSET(HOST_RGF, HOST_CC_SW_RST), 1);

#ifdef CONFIG_CRYPTO_SECP_POWER_CTRL
	/*add to suspend seceng_p6.3 for chicago*/
	secp_reset();
	clk_disable_unprepare(drvdata->ccp_clk);
#else
	/*add to suspend seceng_p6.3 for austin&dallas*/
	if (regulator_is_enabled(drvdata->ccp_regu)) {
		val = regulator_disable(drvdata->ccp_regu);
		if (val) {
			DX_LOG_ERR("dx_pm_ext_hw_suspend: regulator_disable error(%x)\n", val);
			return;
		}
	}
#endif
}

/*
This function should resume the HW (if possiable).It should be implemented by 
the driver user. 
*/
void dx_pm_ext_hw_resume(struct device *dev)
{
	int rc;
	struct dx_drvdata *drvdata = (struct dx_drvdata *)dev_get_drvdata(dev);
	if(NULL == drvdata)
	{
		DX_LOG_ERR("dx_pm_ext_hw_resume: dev_get_drvdata error!\n");
		return;
	}

#ifdef CONFIG_CRYPTO_SECP_POWER_CTRL
	/*add to resume seceng_p6.3 for chicago*/
	rc = clk_set_rate(drvdata->ccp_clk, SECP_WORK_FREQ);
	if (0 != rc) {
		DX_LOG_ERR("dx_pm_ext_hw_resume: fail to set clock rate(%x)!\n",rc);
		return;
	}

	rc = clk_prepare_enable(drvdata->ccp_clk);
	if (0 != rc) {
		DX_LOG_ERR("dx_pm_ext_hw_resume: secp clk enable failed(%x)!\n",rc);
	}

	secp_unreset();
#else
	/*add to resume seceng_p6.3 for austin&dallas*/
	if (!regulator_is_enabled(drvdata->ccp_regu)) {
		rc = regulator_enable(drvdata->ccp_regu);
		if (rc) {
			DX_LOG_ERR("dx_pm_ext_hw_resume: regulator_enable error(%x)\n", rc);
		}
	}
#endif
}

