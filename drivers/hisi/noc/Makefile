#
#NoC Makefile
#

subdir-ccflags-$(CONFIG_HISI_BB)               += -Idrivers/hisi/mntn/blackbox/
subdir-ccflags-$(CONFIG_HISI_NOC)              += -Idrivers/hisi/mntn/ -Wall -Werror

obj-$(CONFIG_HISI_NOC) +=  hisi_noc.o             \
                           hisi_noc_err_probe.o       \
                           hisi_noc_packet.o      \
                           hisi_noc_transcation.o \
                           hisi_noc_info.o        \
                           hisi_noc_dump.o

obj-$(CONFIG_HISI_NOC_DBG) += hisi_noc_dbg.o

obj-$(CONFIG_HISI_NOC_HI3650_PLATFORM) += hisi_noc_info_hi3650.o
obj-$(CONFIG_HISI_NOC_HI3660_PLATFORM) += hisi_noc_info_hi3660.o
obj-$(CONFIG_HISI_NOC_HI6250_PLATFORM) += hisi_noc_info_hi6250.o
obj-$(CONFIG_HISI_NOC_KIRIN970_PLATFORM) += hisi_noc_info_kirin970.o
