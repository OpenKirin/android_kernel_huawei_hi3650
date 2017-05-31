enum {
	HS_PMCTRL,
	HS_SYSCTRL,
	HS_CRGCTRL,
	HS_PMUCTRL,
	HS_PCTRL,
	HS_MEDIACRG,
	HS_IOMCUCRG,
};

void __iomem *hs_clk_base(u32 ctrl);