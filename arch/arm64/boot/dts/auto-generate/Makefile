dtb-y += FRD_TUCL_VN2_config.dtb
dtb-y += FRD_L04_V3_config.dtb
dtb-y += FRD_TUCL_V0_config.dtb
dtb-y += FRD_L09_V4_config.dtb
dtb-y += FRD_L09_V3_config.dtb
dtb-y += FRD_TL00_V2_config.dtb
dtb-y += FRD_TUCL_V4_config.dtb
dtb-y += FRD_TUGL_V4_config.dtb
dtb-y += FRD_L04_V2_config.dtb
dtb-y += FRD_TUGL_TL_VN1_config.dtb
dtb-y += FRD_TUCL_VN1_config.dtb
dtb-y += FRD_CLG_V2_config.dtb
dtb-y += FRD_TUCL_V2_config.dtb
dtb-y += FRD_L09_VN1_config.dtb
dtb-y += FRD_TUGL_DL_VN1_config.dtb
dtb-y += FRD_L09_V2_config.dtb
dtb-y += FRD_TUGL_V2_config.dtb
dtb-y += FRD_TUCL_LV_config.dtb

targets += dtbs

dtbs: $(addprefix $(obj)/, $(dtb-y))
	$(Q)rm -f $(obj)/../*.dtb

clean-files := *.dtb
