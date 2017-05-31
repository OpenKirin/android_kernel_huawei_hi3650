#ifndef __SOC_CFG_SYS_NOC_BUS_INTERFACE_H__
#define __SOC_CFG_SYS_NOC_BUS_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_ADDR(base) ((base) + (0x000C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_ADDR(base) ((base) + (0x1C10))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_ADDR(base) ((base) + (0x8008))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_ADDR(base) ((base) + (0x8088))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_ADDR(base) ((base) + (0x808C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0x80AC))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0x80B0))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_ADDR(base) ((base) + (0x000C))
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0010))
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_ADDR(base) ((base) + (0x0014))
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_ADDR(base) ((base) + (0x8008))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_ADDR(base) ((base) + (0x8088))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_ADDR(base) ((base) + (0x808C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_ADDR(base) ((base) + (0x80AC))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_ADDR(base) ((base) + (0x80B0))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_ADDR(base) ((base) + (0x80B4))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_ADDR(base) ((base) + (0x80B8))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_ADDR(base) ((base) + (0x000C))
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_ADDR(base) ((base) + (0x1008))
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1080))
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1084))
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_ADDR(base) ((base) + (0x1088))
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_ADDR(base) ((base) + (0x108C))
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1100))
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1104))
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_ADDR(base) ((base) + (0x1108))
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_ADDR(base) ((base) + (0x110C))
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1180))
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1184))
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_ADDR(base) ((base) + (0x1188))
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_ADDR(base) ((base) + (0x118C))
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1200))
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1204))
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_ADDR(base) ((base) + (0x1208))
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_ADDR(base) ((base) + (0x120C))
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1280))
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1284))
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_ADDR(base) ((base) + (0x1288))
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_ADDR(base) ((base) + (0x128C))
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1300))
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1304))
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_ADDR(base) ((base) + (0x1308))
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_ADDR(base) ((base) + (0x130C))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_ADDR(base) ((base) + (0x1C10))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_ADDR(base) ((base) + (0x2000))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_ADDR(base) ((base) + (0x2004))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_ADDR(base) ((base) + (0x2008))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_ADDR(base) ((base) + (0x200C))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_ADDR(base) ((base) + (0x2014))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_ADDR(base) ((base) + (0x2024))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_ADDR(base) ((base) + (0x2028))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_ADDR(base) ((base) + (0x202C))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_ADDR(base) ((base) + (0x2030))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_ADDR(base) ((base) + (0x2034))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_ADDR(base) ((base) + (0x2038))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_ADDR(base) ((base) + (0x2044))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_ADDR(base) ((base) + (0x2048))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_ADDR(base) ((base) + (0x204C))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_ADDR(base) ((base) + (0x2054))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_ADDR(base) ((base) + (0x2058))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_ADDR(base) ((base) + (0x205C))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_ADDR(base) ((base) + (0x2060))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_ADDR(base) ((base) + (0x2064))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_ADDR(base) ((base) + (0x2068))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_ADDR(base) ((base) + (0x206C))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_ADDR(base) ((base) + (0x2070))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_ADDR(base) ((base) + (0x2074))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_ADDR(base) ((base) + (0x2138))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x213C))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_ADDR(base) ((base) + (0x2140))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_ADDR(base) ((base) + (0x214C))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x2150))
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_ADDR(base) ((base) + (0x2154))
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_ADDR(base) ((base) + (0x000C))
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_ADDR(base) ((base) + (0x008C))
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_ADDR(base) ((base) + (0x010C))
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_ADDR(base) ((base) + (0x1C10))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_ADDR(base) ((base) + (0x000C))
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_ADDR(base) ((base) + (0x1008))
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_ADDR(base) ((base) + (0x1C08))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_ADDR(base) ((base) + (0x1C10))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_ADDR(base) ((base) + (0x000C))
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0010))
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_ADDR(base) ((base) + (0x0014))
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_ADDR(base) ((base) + (0x008C))
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_ADDR(base) ((base) + (0x010C))
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_ADDR(base) ((base) + (0x0180))
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0184))
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_ADDR(base) ((base) + (0x0188))
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_ADDR(base) ((base) + (0x018C))
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0198))
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_ADDR(base) ((base) + (0x0200))
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0204))
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_ADDR(base) ((base) + (0x0208))
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_ADDR(base) ((base) + (0x020C))
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0218))
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_ADDR(base) ((base) + (0x0280))
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0284))
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_ADDR(base) ((base) + (0x0288))
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_ADDR(base) ((base) + (0x028C))
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0298))
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_ADDR(base) ((base) + (0x1008))
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_ADDR(base) ((base) + (0x1C08))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_ADDR(base) ((base) + (0x1C10))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_ADDR(base) ((base) + (0x008C))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_ADDR(base) ((base) + (0x1C08))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_ADDR(base) ((base) + (0x1C10))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_ADDR(base) ((base) + (0x000C))
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_ADDR(base) ((base) + (0x0080))
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0084))
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_ADDR(base) ((base) + (0x0088))
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_ADDR(base) ((base) + (0x008C))
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0098))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_ADDR(base) ((base) + (0x010C))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_ADDR(base) ((base) + (0x1008))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_ADDR(base) ((base) + (0x1C08))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_ADDR(base) ((base) + (0x1C10))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_ADDR(base) ((base) + (0x000C))
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))
#define SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_ADDR(base) ((base) + (0x1C08))
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_ADDR(base) ((base) + (0x1C0C))
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_ADDR(base) ((base) + (0x1C10))
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_ADDR(base) ((base) + (0x1C14))
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_ADDR(base) ((base) + (0x1C18))
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_ADDR(base) ((base) + (0x1C20))
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_ADDR(base) ((base) + (0x1C28))
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_ADDR(base) ((base) + (0x1C30))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_MODEM_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERR_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faulten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_faulten_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_FAULTEN_faulten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errvld : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_errvld_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRVLD_errvld_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_errclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRCLR_errclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lock : 1;
        unsigned int opc : 4;
        unsigned int reserved_0: 3;
        unsigned int errcode : 3;
        unsigned int reserved_1: 5;
        unsigned int len1 : 8;
        unsigned int reserved_2: 7;
        unsigned int format : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_lock_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_lock_END (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_opc_START (1)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_opc_END (4)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_errcode_START (8)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_errcode_END (10)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_len1_START (16)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_len1_END (23)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_format_START (31)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG0_format_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog1 : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_errlog1_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG1_errlog1_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog3 : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_errlog3_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG3_errlog3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog5 : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_errlog5_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG5_errlog5_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_errlog7_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEMBUS_ERRLOG7_errlog7_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_MODE_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addrbase_low : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_addrbase_low_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRBASE_LOW_addrbase_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addrwindowsize : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rden : 1;
        unsigned int wren : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_rden_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_rden_END (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_wren_START (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_OPCODE_wren_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userbase : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_userbase_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERBASE_userbase_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int usermask : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_usermask_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_USERMASK_usermask_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int securitybase : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_securitybase_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYBASE_securitybase_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int securitymask : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_securitymask_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_F_SECURITYMASK_securitymask_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_en_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_EN_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_MODE_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thresholds_0_0 : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thresholds_0_1 : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflowstatus : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_overflowstatus_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWSTATUS_overflowstatus_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflowreset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_overflowreset_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_OVERFLOWRESET_overflowreset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pendingeventmode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int prescaler : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_prescaler_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_P_PRESCALER_prescaler_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int erren : 1;
        unsigned int traceen : 1;
        unsigned int payloaden : 1;
        unsigned int staten : 1;
        unsigned int alarmen : 1;
        unsigned int statconddump : 1;
        unsigned int intrusivemode : 1;
        unsigned int filtbytealwayschainableen : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_erren_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_erren_END (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_traceen_START (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_traceen_END (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_payloaden_START (2)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_payloaden_END (2)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_staten_START (3)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_staten_END (3)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_alarmen_START (4)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_alarmen_END (4)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_statconddump_START (5)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_statconddump_END (5)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_intrusivemode_START (6)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_intrusivemode_END (6)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_filtbytealwayschainableen_START (7)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_MAINCTL_filtbytealwayschainableen_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int globalen : 1;
        unsigned int active : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_globalen_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_globalen_END (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_active_START (1)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_CFGCTL_active_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statperiod : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_statperiod_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATPERIOD_statperiod_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statgo : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_statgo_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATGO_statgo_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmmin : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_statalarmmin_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMIN_statalarmmin_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmmax : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_statalarmmax_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMMAX_statalarmmax_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmstatus : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_statalarmstatus_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMSTATUS_statalarmstatus_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_statalarmclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_STATALARMCLR_statalarmclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_counters_0_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_SRC_counters_0_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_counters_0_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_0_VAL_counters_0_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_counters_1_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_SRC_counters_1_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_counters_1_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_1_VAL_counters_1_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_2_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_counters_2_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_SRC_counters_2_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_2_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_2_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_counters_2_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_2_VAL_counters_2_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_3_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_counters_3_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_SRC_counters_3_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_3_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_3_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_counters_3_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_3_VAL_counters_3_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_4_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_counters_4_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_SRC_counters_4_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_4_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_4_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_counters_4_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_4_VAL_counters_4_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_5_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_counters_5_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_SRC_counters_5_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_5_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_5_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_counters_5_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_5_VAL_counters_5_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_6_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_counters_6_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_SRC_counters_6_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_6_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_6_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_counters_6_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_6_VAL_counters_6_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_7_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_counters_7_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_SRC_counters_7_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_7_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_7_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_counters_7_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM_TRANS_M_COUNTERS_7_VAL_counters_7_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bandwidth : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_bandwidth_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_BANDWIDTH_bandwidth_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int saturation : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_saturation_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_SATURATION_saturation_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_ASP_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_MODE_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addrbase_low : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_addrbase_low_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRBASE_LOW_addrbase_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addrwindowsize : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rden : 1;
        unsigned int wren : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_rden_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_rden_END (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_wren_START (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_OPCODE_wren_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userbase : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_userbase_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERBASE_userbase_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int usermask : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_usermask_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_USERMASK_usermask_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int securitybase : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_securitybase_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYBASE_securitybase_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int securitymask : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_securitymask_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_F_SECURITYMASK_securitymask_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_en_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_EN_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_MODE_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thresholds_0_0 : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_0_thresholds_0_0_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thresholds_0_1 : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_1_thresholds_0_1_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thresholds_0_2 : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_2_thresholds_0_2_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thresholds_0_3 : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_THRESHOLDS_0_3_thresholds_0_3_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflowstatus : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_overflowstatus_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWSTATUS_overflowstatus_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflowreset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_overflowreset_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_OVERFLOWRESET_overflowreset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pendingeventmode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int prescaler : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_prescaler_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_P_PRESCALER_prescaler_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int erren : 1;
        unsigned int traceen : 1;
        unsigned int payloaden : 1;
        unsigned int staten : 1;
        unsigned int alarmen : 1;
        unsigned int statconddump : 1;
        unsigned int intrusivemode : 1;
        unsigned int filtbytealwayschainableen : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_erren_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_erren_END (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_traceen_START (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_traceen_END (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_payloaden_START (2)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_payloaden_END (2)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_staten_START (3)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_staten_END (3)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_alarmen_START (4)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_alarmen_END (4)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_statconddump_START (5)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_statconddump_END (5)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_intrusivemode_START (6)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_intrusivemode_END (6)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_filtbytealwayschainableen_START (7)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_MAINCTL_filtbytealwayschainableen_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int globalen : 1;
        unsigned int active : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_globalen_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_globalen_END (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_active_START (1)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_CFGCTL_active_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statperiod : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_statperiod_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATPERIOD_statperiod_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statgo : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_statgo_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATGO_statgo_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmmin : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_statalarmmin_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMIN_statalarmmin_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmmax : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_statalarmmax_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMMAX_statalarmmax_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmstatus : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_statalarmstatus_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMSTATUS_statalarmstatus_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_statalarmclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_STATALARMCLR_statalarmclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_counters_0_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_SRC_counters_0_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_counters_0_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_0_VAL_counters_0_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_counters_1_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_SRC_counters_1_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_counters_1_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_1_VAL_counters_1_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_2_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_counters_2_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_SRC_counters_2_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_2_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_2_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_counters_2_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_2_VAL_counters_2_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_3_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_counters_3_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_SRC_counters_3_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_3_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_3_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_counters_3_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_3_VAL_counters_3_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_4_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_counters_4_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_SRC_counters_4_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_4_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_4_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_counters_4_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_4_VAL_counters_4_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_5_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_counters_5_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_SRC_counters_5_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_5_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_5_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_counters_5_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_5_VAL_counters_5_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_6_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_counters_6_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_SRC_counters_6_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_6_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_6_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_counters_6_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_6_VAL_counters_6_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_7_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_counters_7_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_SRC_counters_7_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_7_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_7_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_counters_7_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_ASP_TRANS_M_COUNTERS_7_VAL_counters_7_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_CCI2SYSBUS_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_AOBUS2DDRC_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2CFG_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_PERI2DDRC_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYS2PERI_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_MODEM2DDR_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFG2SYS_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERR_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faulten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_faulten_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_FAULTEN_faulten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errvld : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_errvld_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRVLD_errvld_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_errclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRCLR_errclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lock : 1;
        unsigned int opc : 4;
        unsigned int reserved_0: 3;
        unsigned int errcode : 3;
        unsigned int reserved_1: 5;
        unsigned int len1 : 8;
        unsigned int reserved_2: 7;
        unsigned int format : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_lock_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_lock_END (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_opc_START (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_opc_END (4)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_errcode_START (8)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_errcode_END (10)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_len1_START (16)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_len1_END (23)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_format_START (31)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG0_format_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog1 : 22;
        unsigned int reserved : 10;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_errlog1_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG1_errlog1_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog3 : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_errlog3_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG3_errlog3_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog5 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_errlog5_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG5_errlog5_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_errlog7_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_ERRLOG7_errlog7_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int erren : 1;
        unsigned int traceen : 1;
        unsigned int payloaden : 1;
        unsigned int staten : 1;
        unsigned int alarmen : 1;
        unsigned int statconddump : 1;
        unsigned int intrusivemode : 1;
        unsigned int filtbytealwayschainableen : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_erren_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_erren_END (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_traceen_START (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_traceen_END (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_payloaden_START (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_payloaden_END (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_staten_START (3)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_staten_END (3)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_alarmen_START (4)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_alarmen_END (4)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_statconddump_START (5)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_statconddump_END (5)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_intrusivemode_START (6)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_intrusivemode_END (6)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_filtbytealwayschainableen_START (7)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_MAINCTL_filtbytealwayschainableen_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int globalen : 1;
        unsigned int active : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_globalen_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_globalen_END (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_active_START (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_CFGCTL_active_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filterlut : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_filterlut_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_FILTERLUT_filterlut_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statperiod : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_statperiod_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATPERIOD_statperiod_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statgo : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_statgo_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATGO_statgo_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmmin : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_statalarmmin_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMIN_statalarmmin_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmmax : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_statalarmmax_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMMAX_statalarmmax_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmstatus : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_statalarmstatus_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMSTATUS_statalarmstatus_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_statalarmclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_STATALARMCLR_statalarmclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_routeidbase : 22;
        unsigned int reserved : 10;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_filters_0_routeidbase_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDBASE_filters_0_routeidbase_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_routeidmask : 22;
        unsigned int reserved : 10;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_filters_0_routeidmask_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ROUTEIDMASK_filters_0_routeidmask_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_addrbase_low : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_filters_0_addrbase_low_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_ADDRBASE_filters_0_addrbase_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_windowsize : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_filters_0_windowsize_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_WINDOWSIZE_filters_0_windowsize_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_securitybase : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_filters_0_securitybase_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYBASE_filters_0_securitybase_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_securitymask : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_filters_0_securitymask_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_SECURITYMASK_filters_0_securitymask_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rden : 1;
        unsigned int wren : 1;
        unsigned int locken : 1;
        unsigned int urgen : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_rden_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_rden_END (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_wren_START (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_wren_END (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_locken_START (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_locken_END (2)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_urgen_START (3)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_OPCODE_urgen_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reqen : 1;
        unsigned int rspen : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_reqen_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_reqen_END (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_rspen_START (1)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_STATUS_rspen_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_length : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_filters_0_length_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_LENGTH_filters_0_length_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_urgency : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_filters_0_urgency_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_URGENCY_filters_0_urgency_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_userbase : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_filters_0_userbase_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERBASE_filters_0_userbase_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int filters_0_usermask : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_filters_0_usermask_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_F0_USERMASK_filters_0_usermask_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_src : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_counters_0_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_SRC_counters_0_src_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_val : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_counters_0_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_0_VAL_counters_0_val_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_src : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_counters_1_src_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_SRC_counters_1_src_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_val : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_counters_1_val_START (0)
#define SOC_CFG_SYS_NOC_BUS_SYSBUS_DDRC_PACKET_COUNTERS_1_VAL_counters_1_val_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_DJTAG_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_A7TOCFG_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_LPMCU_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERR_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faulten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_faulten_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_FAULTEN_faulten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errvld : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_errvld_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRVLD_errvld_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_errclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRCLR_errclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lock : 1;
        unsigned int opc : 4;
        unsigned int reserved_0: 3;
        unsigned int errcode : 3;
        unsigned int reserved_1: 5;
        unsigned int len1 : 8;
        unsigned int reserved_2: 7;
        unsigned int format : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_lock_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_lock_END (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_opc_START (1)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_opc_END (4)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_errcode_START (8)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_errcode_END (10)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_len1_START (16)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_len1_END (23)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_format_START (31)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG0_format_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog1 : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_errlog1_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG1_errlog1_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog3 : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_errlog3_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG3_errlog3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog5 : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_errlog5_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG5_errlog5_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_errlog7_START (0)
#define SOC_CFG_SYS_NOC_BUS_CFGBUS_ERRLOG7_errlog7_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_DMAC_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMA2SYS_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERR_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faulten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_faulten_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_FAULTEN_faulten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errvld : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_errvld_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRVLD_errvld_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_errclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRCLR_errclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lock : 1;
        unsigned int opc : 4;
        unsigned int reserved_0: 3;
        unsigned int errcode : 3;
        unsigned int reserved_1: 5;
        unsigned int len1 : 8;
        unsigned int reserved_2: 7;
        unsigned int format : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_lock_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_lock_END (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_opc_START (1)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_opc_END (4)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_errcode_START (8)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_errcode_END (10)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_len1_START (16)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_len1_END (23)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_format_START (31)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG0_format_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog1 : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_errlog1_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG1_errlog1_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog3 : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_errlog3_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG3_errlog3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog5 : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_errlog5_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG5_errlog5_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_errlog7_START (0)
#define SOC_CFG_SYS_NOC_BUS_DMABUS_ERRLOG7_errlog7_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bandwidth : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_bandwidth_START (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_BANDWIDTH_bandwidth_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int saturation : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_saturation_START (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_SATURATION_saturation_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_USB3_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_SEC_P_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_SEC_S_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_SOCP_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_CSSYS_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_PERF_STAT_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBG2SYS_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERR_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faulten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_faulten_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_FAULTEN_faulten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errvld : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_errvld_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRVLD_errvld_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_errclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRCLR_errclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lock : 1;
        unsigned int opc : 4;
        unsigned int reserved_0: 3;
        unsigned int errcode : 3;
        unsigned int reserved_1: 5;
        unsigned int len1 : 8;
        unsigned int reserved_2: 7;
        unsigned int format : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_lock_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_lock_END (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_opc_START (1)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_opc_END (4)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_errcode_START (8)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_errcode_END (10)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_len1_START (16)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_len1_END (23)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_format_START (31)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG0_format_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog1 : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_errlog1_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG1_errlog1_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog3 : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_errlog3_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG3_errlog3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog5 : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_errlog5_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG5_errlog5_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_errlog7_START (0)
#define SOC_CFG_SYS_NOC_BUS_DBGBUS_ERRLOG7_errlog7_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERR_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faulten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_faulten_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_FAULTEN_faulten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errvld : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_errvld_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRVLD_errvld_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_errclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRCLR_errclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lock : 1;
        unsigned int opc : 4;
        unsigned int reserved_0: 3;
        unsigned int errcode : 3;
        unsigned int reserved_1: 5;
        unsigned int len1 : 8;
        unsigned int reserved_2: 7;
        unsigned int format : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_lock_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_lock_END (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_opc_START (1)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_opc_END (4)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_errcode_START (8)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_errcode_END (10)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_len1_START (16)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_len1_END (23)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_format_START (31)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG0_format_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog1 : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_errlog1_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG1_errlog1_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog3 : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_errlog3_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG3_errlog3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog5 : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_errlog5_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG5_errlog5_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_errlog7_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC1BUS_ERRLOG7_errlog7_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_EMMC0_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_EMMC1_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_rate_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_bypass_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERR_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faulten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_faulten_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_FAULTEN_faulten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errvld : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_errvld_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRVLD_errvld_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_errclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRCLR_errclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lock : 1;
        unsigned int opc : 4;
        unsigned int reserved_0: 3;
        unsigned int errcode : 3;
        unsigned int reserved_1: 5;
        unsigned int len1 : 8;
        unsigned int reserved_2: 7;
        unsigned int format : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_lock_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_lock_END (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_opc_START (1)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_opc_END (4)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_errcode_START (8)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_errcode_END (10)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_len1_START (16)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_len1_END (23)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_format_START (31)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG0_format_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog1 : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_errlog1_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG1_errlog1_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog3 : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_errlog3_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG3_errlog3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog5 : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_errlog5_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG5_errlog5_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_errlog7_START (0)
#define SOC_CFG_SYS_NOC_BUS_MMC0BUS_ERRLOG7_errlog7_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_coretypeid_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_coretypeid_END (7)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_corechecksum_START (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_userid_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_userid_END (7)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p0 : 2;
        unsigned int reserved_0: 6;
        unsigned int p1 : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p0_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p0_END (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p1_START (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_mode_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socketqosen : 1;
        unsigned int extthren : 1;
        unsigned int intclken : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_extthren_START (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_extthren_END (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_intclken_START (2)
#define SOC_CFG_SYS_NOC_BUS_IVP32_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_id_coreid_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_id_revisionid_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERR_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faulten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_faulten_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_FAULTEN_faulten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errvld : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_errvld_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRVLD_errvld_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_errclr_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRCLR_errclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lock : 1;
        unsigned int opc : 4;
        unsigned int reserved_0: 3;
        unsigned int errcode : 3;
        unsigned int reserved_1: 5;
        unsigned int len1 : 8;
        unsigned int reserved_2: 7;
        unsigned int format : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_lock_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_lock_END (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_opc_START (1)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_opc_END (4)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_errcode_START (8)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_errcode_END (10)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_len1_START (16)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_len1_END (23)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_format_START (31)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG0_format_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog1 : 22;
        unsigned int reserved : 10;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_errlog1_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG1_errlog1_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog3 : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_errlog3_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG3_errlog3_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog5 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_errlog5_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG5_errlog5_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_UNION;
#endif
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_errlog7_START (0)
#define SOC_CFG_SYS_NOC_BUS_IVP32_ERRLOG7_errlog7_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
