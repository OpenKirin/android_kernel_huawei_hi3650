#=============================================================================
#=============================================================================

obj-$(CONFIG_HW_ANTENNA_BOARD_MATCH)  += antenna_board_match/
obj-$(CONFIG_ANTENNA_FPGA) += antenna_fpga/
obj-$(CONFIG_HUAWEI_AUDIO) += audio/
obj-$(CONFIG_CHR_NETLINK_MODULE)   += chr/
obj-y   += connectivity/
obj-$(CONFIG_HUAWEI_HW_DEV_DCT)  += devdetect/
#obj-${CONFIG_HUAWEI_DSM} += dsm/
ifneq ($(strip $(OBB_SEPARATE)),true)
obj-$(CONFIG_VIACBP82D_3RD_MODEM) += ext_modem/
endif
obj-$(CONFIG_INPUTHUB)   += inputhub/iom7/

obj-$(CONFIG_MAXQ616_POWER_SWITCH) += irda/
obj-$(CONFIG_LOGGER_EXTEND) += log/
obj-$(CONFIG_HW_STAT_MM) += mm/
obj-$(CONFIG_NFC_DEVICES)   += nfc/
obj-$(CONFIG_HW_WIFI)   += net/
obj-y   += power/
obj-$(CONFIG_HUAWEI_DSM) += recovery/
obj-$(CONFIG_HUAWEI_SENSORS_INPUT_INFO)   += sensor/
obj-y   += storage/
obj-$(CONFIG_HUAWEI_TS)   += touthscreen/
obj-$(CONFIG_HUAWEI_UID_IO_STATS) += uid_iostats/
obj-y   += usb/
obj-$(CONFIG_HW_VOLTAGE_DETECTION) += voltage_detection/
obj-$(CONFIG_ANTENNA_BOARDID_GPIO_DETECT) += antenna_board_gpio_match/
obj-$(CONFIG_HUAWEI_VIBRATOR) += vibrator/
obj-$(CONFIG_HUAWEI_OCP) += ocp/
obj-$(CONFIG_MADAPT) += madapt/
obj-$(CONFIG_DOME_KEY) += dome_key/
obj-$(CONFIG_HUAWEI_IO_TRACING) += iotrace/
obj-$(CONFIG_HW_HANDPRESS_SWITCH) += handpress_switch/
obj-$(CONFIG_HW_LED_ALWAYSON) += led_alwayson/
