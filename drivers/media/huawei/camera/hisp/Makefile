ccflags-y += -Idrivers/media/huawei/camera
ccflags-y += -Idrivers/rpmsg

obj-y += hisp.o

ifeq ($(CLT_IV), true)
obj-y += simulated_fw/

ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV150), y)
subdir-ccflags-y += -DCHICAGO_CAMERA
endif

else ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV100), y)
	obj-y += hisp100/

else ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV110), y)
	obj-y += hisp110/

else ifeq ($(CONFIG_HISI_CAMERA_HISTAR_ISPV150), y)
EXTRA_CFLAGS += -DCHICAGO_CAMERA
	obj-y += hisp150/
endif

ifneq ($(CLT_IV), true)
ifneq ($(CONFIG_RPMSG),y)
	obj-y += fakefw/
endif
endif


