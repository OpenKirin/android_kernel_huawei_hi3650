obj-y	+= hisi_atfisp.o hisi_ispcma.o hisi_fstcma.o hisi_isp_rproc.o
ifeq ($(CONFIG_HISI_HISTAR_ISP), y)
EXTRA_CFLAGS += -Idrivers/hisi/tzdriver \
				-Idrivers/hisi/load_image \
				-I$(src)/../../../../../../../external/efipartition
endif
