ifeq ($(CONFIG_HISI_CLK_HI3660),y)
obj-$(CONFIG_HISI_CLK)			+= clk-kirin.o
else
obj-$(CONFIG_HISI_CLK)			+= clk-hi3xxx.o
endif
obj-$(CONFIG_HISI_CLK_MAILBOX_SUPPORT)	+= hisi-clk-mailbox.o

ifeq ($(CONFIG_HISI_CLK_HI3660),y)
obj-$(CONFIG_HISI_CLK)			+= clk_peri_dvfs.o
endif
obj-$(CONFIG_HISI_CLK_PM_MONITOR)	+= hisi_clk_pm_monitor.o
obj-$(CONFIG_HISI_PERIDVFS)  += peri_dvfs/
