#include <linux/module.h>
#include <linux/of.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/platform_device.h>
#include <linux/gpio.h>

#include "dwc3-hisi.h"

/*lint -e750 -esym(750,*)*/
/* clk module will round to 228M */
#define USB3OTG_ACLK_FREQ		229000000

#define IP_RST_USB3OTG_MISC				(1 << 7)
#define SCTRL_SCDEEPSLEEPED				0x08
#define USB_REFCLK_ISO_EN               (1 << 25)
#define PCTRL_PERI_CTRL3                0x10
#define USB_TCXO_EN						(1 << 1)
#define PERI_CTRL3_MSK_START            (16)
#define SC_CLK_USB3PHY_3MUX1_SEL        (1 << 25)

#define SC_SEL_ABB_BACKUP               (1 << 8)
#define CLKDIV_MASK_START               (16)

#define PERI_CRG_CLKDIV21               0xFC

#define GT_CLK_ABB_BACKUP               (1 << 22)
#define PERI_CRG_CLK_DIS5               0x54

#define PMC_PPLL3CTRL0                  0x048
#define PPLL3_FBDIV_START               (8)
#define PPLL3_EN                        (1 << 0)
#define PPLL3_BP                        (1 << 1)
#define PPLL3_LOCK                      (1 << 26)

#define PMC_PPLL3CTRL1                  0x04C
#define PPLL3_INT_MOD                   (1 << 24)
#define GT_CLK_PPLL3                    (1 << 26)

#define PERI_CRG_CLK_EN5                0x50

#define SC_USB3PHY_ABB_GT_EN            (1 << 15)
#define REF_SSP_EN                      (1 << 16)
/*lint -e750 +esym(750,*)*/

/* usb3 misc ctrl driver */
void __iomem *reg_base_usb_misc_ctrl;
static inline void set_misc_base_addr(void __iomem *base)
{
	printk(KERN_ERR "[USB.DBG]:misc base:%pK\n", base);
	reg_base_usb_misc_ctrl = base;
}

/*lint -e528 -esym(528,*)*/
static inline void __iomem *get_misc_base_addr(void)
{
	return reg_base_usb_misc_ctrl;
}
/*lint -e528 +esym(528,*)*/

/*lint -e715 -e716 -e717 -e835 -e838 -e845 -e533 -e835 -e778 -e774 -e747 -e785*/
void usb3_misc_reg_writel(u32 val, unsigned long int misc_offset)
{
	writel(val, (get_misc_base_addr() + misc_offset));
}

u32 usb3_misc_reg_readl(unsigned long int misc_offset)
{
	return  readl(get_misc_base_addr() + misc_offset);
}

void usb3_misc_reg_setbit(u32 bit, unsigned long int misc_offset)
{
	volatile uint32_t temp;
	temp = usb3_misc_reg_readl(misc_offset);
	temp |= (1u << bit);
	usb3_misc_reg_writel(temp, misc_offset);
}

void usb3_misc_reg_clrbit(u32 bit, unsigned long int misc_offset)
{
	volatile uint32_t temp;
	temp = usb3_misc_reg_readl(misc_offset);
	temp &= ~(1u << bit);
	usb3_misc_reg_writel(temp, misc_offset);
}

void usb3_misc_reg_setvalue(u32 value, unsigned long int misc_offset)
{
	volatile uint32_t temp;
	temp = usb3_misc_reg_readl(misc_offset);
	temp |= value;
	usb3_misc_reg_writel(temp, misc_offset);
}

void usb3_misc_reg_clrvalue(u32 value, unsigned long int misc_offset)
{
	volatile uint32_t temp;
	temp = usb3_misc_reg_readl(misc_offset);
	temp &= ~value;
	usb3_misc_reg_writel(temp, misc_offset);
}

/* usb3 misc ctrl driver */

#define SET_NBITS_MASK(start, end) (((2u << ((end) - (start))) - 1) << (start))

int config_usb_phy_controller(void)
{
	/* Release USB20 PHY out of IDDQ mode */
	usb3_misc_reg_clrbit(0u, 0x14ul);

	/* Release USB31 PHY out of  TestPowerDown mode */
	usb3_misc_reg_clrbit(23u, 0x50ul);

	/* Tell the PHY power is stable */
	usb3_misc_reg_setvalue((1u << 1) | (1u << 9) | (1u << 11), 0x54ul);


	/*
	 * config the TCA mux mode
	 * register:
	 *      -- 0x204 0x208: write immediately
	 *      -- 0x200 0x210 0x214 0x240: read-update-write
	 */

	usb3_misc_reg_writel(0xffffu, 0x208ul);
	usb3_misc_reg_writel(0x3u, 0x204ul);

	usb3_misc_reg_clrvalue(~SET_NBITS_MASK(0, 1), 0x200ul);
	usb3_misc_reg_setbit(4u, 0x210ul);

	usb3_misc_reg_clrvalue(~(SET_NBITS_MASK(0, 1) | SET_NBITS_MASK(3, 4)), 0x214ul);
	usb3_misc_reg_setvalue(0x1u | (0x2u << 3), 0x214ul);

	usb3_misc_reg_clrvalue(~SET_NBITS_MASK(0, 3), 0x240ul);
	usb3_misc_reg_setvalue(0x3u | (0x3u << 2), 0x240ul);

	return 0;
}

int set_usb_phy_clk(void __iomem *base)
{
/*lint -save -e550 */
	volatile int32_t temp;

	/* usb refclk iso enable */
	writel(USB_REFCLK_ISO_EN, PERI_CRG_ISODIS + base);
	/* enable usb_tcxo_en */
	writel(USB_TCXO_EN | (USB_TCXO_EN << PERI_CTRL3_MSK_START),
			PCTRL_PERI_CTRL3 + base);
	/* select usbphy clk from abb */
	temp = readl(base + PCTRL_PERI_CTRL24);
	temp &= ~SC_CLK_USB3PHY_3MUX1_SEL;
	writel(temp, base + PCTRL_PERI_CTRL24);

	return 0xabb;
/*lint -restore */
}
void set_gpio_if_fpga(void)
{
	if(gpio_request(15, "usb_fpga")) {
		usb_err("request gpio error!\n");
	}

	gpio_direction_output(15, 1);
	udelay(100);

	gpio_direction_output(15, 0);
	udelay(100);

}

static void dwc3_release(struct hisi_dwc3_device *hisi_dwc3)
{
	void __iomem *pericfg_base = hisi_dwc3->pericfg_reg_base;
	void __iomem *otg_bc_base = hisi_dwc3->otg_bc_reg_base;
	int clk_type = 0xabb;

	set_misc_base_addr(otg_bc_base);

	/* open misc clk gate */
	writel(GT_CLK_USB3OTG_REF | GT_ACLK_USB3OTG, pericfg_base + 0x40);

	/* dis-reset usb misc ctrl module */
	writel(IP_RST_USB3OTG_MISC | IP_RST_USB3OTG_32K, pericfg_base + 0x94);

	clk_type = set_usb_phy_clk(pericfg_base);
	if(clk_type) {
		usb_err("usb clk type:%x\n", clk_type);
	}

	config_usb_phy_controller();

	/* unreset phy */
	usb3_misc_reg_setvalue(0x3, 0xa0);
	udelay(100);
	set_gpio_if_fpga();

	/* unreset controller */
	usb3_misc_reg_setvalue(0x7 << 8, 0xa0);
	udelay(100);

	/* set vbus valid */
	usb3_misc_reg_setvalue(0x3 << 6, 0x0);

	/* require to delay 10us */
	udelay(100);
}

static void dwc3_reset(struct hisi_dwc3_device *hisi_dwc3)
{
	void __iomem *pericfg_base = hisi_dwc3->pericfg_reg_base;
/*lint -e438 -esym(438,*)*/
/*lint -e529 -esym(529,*)*/
	/* set vbus valid */
	usb3_misc_reg_clrbit(7u, 0x0ul);
	usb_err("vbus disvalid\n");

	/* reset controller */
	usb3_misc_reg_clrvalue(~(SET_NBITS_MASK(8, 9)), 0xa0ul);
	usb_err("reset controller\n");

	/* reset phy */
	usb3_misc_reg_clrvalue(~(SET_NBITS_MASK(0, 1)), 0xa0ul); /*lint !e835 */
	usb_err("reset phy\n");

	/* usb refclk iso disable */
	writel(USB_REFCLK_ISO_EN, pericfg_base + 0x144);

	/* disable usb_tcxo_en */
	writel(0 | (USB_TCXO_EN << PERI_CTRL3_MSK_START),
			pericfg_base + PCTRL_PERI_CTRL3);

	/* reset usb misc ctrl module */
	writel(IP_RST_USB3OTG_MISC | IP_RST_USB3OTG_32K, pericfg_base + 0x90);

	/* close misc clk gate */
	writel(GT_CLK_USB3OTG_REF | GT_ACLK_USB3OTG, pericfg_base + 0x44);

	usb_err("close usb success\n");
}
/*lint -e438 +esym(438,*)*/
/*lint -e529 +esym(529,*)*/
static int kirin970_usb3phy_init(struct hisi_dwc3_device *hisi_dwc3)
{
	usb_dbg("+\n");
#if 0
	ret = usb3_regu_init(hisi_dwc3);
	if (ret)
		return ret;

	ret = usb3_clk_init(hisi_dwc3);
	if (ret)
		return ret;
#endif

	dwc3_release(hisi_dwc3);
#if 0
	config_femtophy_param(hisi_dwc3);
#endif

	set_hisi_dwc3_power_flag(1);

	usb_dbg("-\n");

	return 0;
}

static int kirin970_usb3phy_shutdown(struct hisi_dwc3_device *hisi_dwc3)
{
	usb_dbg("+\n");

	set_hisi_dwc3_power_flag(0);

	dwc3_reset(hisi_dwc3);
#if 0
	usb3_clk_shutdown(hisi_dwc3);

	ret = usb3_regu_shutdown(hisi_dwc3);
	if (ret)
		return ret;

#endif
	usb_dbg("-\n");

	return 0;
}


static struct usb3_phy_ops kirin970_phy_ops = {
	.init		= kirin970_usb3phy_init,
	.shutdown	= kirin970_usb3phy_shutdown,
};

static int dwc3_kirin970_probe(struct platform_device *pdev)
{
	int ret = 0;

	ret = hisi_dwc3_probe(pdev, &kirin970_phy_ops);
	if (ret)
		usb_err("probe failed, ret=[%d]\n", ret);

	return ret;
}

static int dwc3_kirin970_remove(struct platform_device *pdev)
{
	int ret = 0;

	ret = hisi_dwc3_remove(pdev);
	if (ret)
		usb_err("hisi_dwc3_remove failed, ret=[%d]\n", ret);

	return ret;
}
#ifdef CONFIG_OF
static const struct of_device_id dwc3_kirin970_match[] = {
	{ .compatible = "hisilicon,kirin970-dwc3" },
	{},
};
MODULE_DEVICE_TABLE(of, dwc3_kirin970_match);
#else
#define dwc3_kirin970_match NULL
#endif

static struct platform_driver dwc3_kirin970_driver = {
	.probe		= dwc3_kirin970_probe,
	.remove		= dwc3_kirin970_remove,
	.driver		= {
		.name	= "usb3-kirin970",
		.of_match_table = of_match_ptr(dwc3_kirin970_match),
		.pm	= HISI_DWC3_PM_OPS,
	},
};
/*lint +e715 +e716 +e717 +e835 +e838 +e845 +e533 +e835 +e778 +e774 +e747 +e785*/
/*lint -e64 -esym(64,*)*/
/*lint -e528 -esym(528,*)*/
module_platform_driver(dwc3_kirin970_driver);
/*lint -e528 +esym(528,*)*/
/*lint -e753 -esym(753,*)*/
MODULE_LICENSE("GPL");
/*lint -e753 +esym(753,*)*/
/*lint -e64 +esym(64,*)*/
