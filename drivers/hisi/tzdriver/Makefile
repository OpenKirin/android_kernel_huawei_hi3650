ifneq ($(TARGET_BUILD_VARIANT),user)
ccflags-y += -DDEBUG_TUI
ccflags-y += -DDEF_ENG
endif

obj-$(CONFIG_TZDRIVER) += tc_client_driver.o teek_client_api.o
obj-$(CONFIG_TZDRIVER) += smc.o agent.o gp_ops.o mem.o
obj-$(CONFIG_TEELOG) += tlogger.o tee_rdr_register.o
obj-$(CONFIG_HISI_MMC_SECURE_RPMB) += agent_rpmb.o
obj-$(CONFIG_TEE_TUI) += tui.o
obj-$(CONFIG_TEE_RANDOM) += tee_random.o
obj-$(CONFIG_TEE_ANTIROOT_CLIENT) += ca_antiroot/
obj-$(CONFIG_TEE_LIBHWSECUREC) += libhwsecurec/

ccflags-y += 	-Idrivers/video/hisi/dss \
		-Idrivers/video/fbdev/hisi/dss \
		-Idrivers/staging/android \
		-Idrivers/hisi/tzdriver/libhwsecurec
