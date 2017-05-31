ccflags-y += -Idrivers/media/huawei/camera/hisp
ccflags-y += -Idrivers/media/huawei/camera
ccflags-y += -Idrivers/media/huawei/camera/hjpeg

ifeq ($(CLT_IV), true)
obj-y += imagefile/
obj-y += metadata/
obj-y += simulated_fw.o
obj-y += simulated_rpmsg_bus.o
obj-y += simulated_hisp.o

ifeq ($(TARGET_BOARD_PLATFORM), hi6250)
subdir-ccflags-y += -DDALLAS_CAMERA
endif

ifeq ($(TARGET_BOARD_PLATFORM), hi3660)
subdir-ccflags-y += -DCHICAGO_CAMERA
endif

ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV100), y)
obj-y += v100/
EXTRA_CFLAGS += -DHISP_V100
else ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV110), y)
obj-y += v110/
EXTRA_CFLAGS += -DHISP_V110
else ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV150), y)
obj-y += v150/
EXTRA_CFLAGS += -DHISP_V150
endif
endif
