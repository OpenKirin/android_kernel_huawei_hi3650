ccflags-y += -Idrivers/media/huawei/camera/hisp
ccflags-y += -Idrivers/media/huawei/camera/hisp/simulated_fw
ccflags-y += -Idrivers/media/huawei/camera

ifeq ($(CLT_IV), true)
obj-y += isp_metadata.o
obj-y += isp_metadata_vendor_tag.o
ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV100), y)
EXTRA_CFLAGS += -DHISP_V100
else ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV110), y)
EXTRA_CFLAGS += -DHISP_V110
else ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV150), y)
EXTRA_CFLAGS += -DHISP_V150
endif
endif
