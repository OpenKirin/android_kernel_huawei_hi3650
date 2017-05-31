#ifndef __SOC_VCODEC_BUS_INTERFACE_H__
#define __SOC_VCODEC_BUS_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1000))
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1004))
#define SOC_VCODEC_BUS_VENC_ADAPTERRATE_ADDR(base) ((base) + (0x1008))
#define SOC_VCODEC_BUS_VENC_ADAP_BYPASS_ADDR(base) ((base) + (0x100C))
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_ADDR(base) ((base) + (0x1080))
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_ADDR(base) ((base) + (0x1084))
#define SOC_VCODEC_BUS_VDEC_ADAPTERRATE_ADDR(base) ((base) + (0x1088))
#define SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_ADDR(base) ((base) + (0x108C))
#define SOC_VCODEC_BUS_ERR_ID_COREID_ADDR(base) ((base) + (0x1C00))
#define SOC_VCODEC_BUS_ID_REVISIONID_ADDR(base) ((base) + (0x1C04))
#define SOC_VCODEC_BUS_FAULTEN_ADDR(base) ((base) + (0x1C08))
#define SOC_VCODEC_BUS_ERRVLD_ADDR(base) ((base) + (0x1C0C))
#define SOC_VCODEC_BUS_ERRCLR_ADDR(base) ((base) + (0x1C10))
#define SOC_VCODEC_BUS_ERRLOG0_ADDR(base) ((base) + (0x1C14))
#define SOC_VCODEC_BUS_ERRLOG1_ADDR(base) ((base) + (0x1C18))
#define SOC_VCODEC_BUS_ERRLOG3_ADDR(base) ((base) + (0x1C20))
#define SOC_VCODEC_BUS_ERRLOG5_ADDR(base) ((base) + (0x1C28))
#define SOC_VCODEC_BUS_ERRLOG7_ADDR(base) ((base) + (0x1C30))
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_ADDR(base) ((base) + (0x0100))
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0104))
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_ADDR(base) ((base) + (0x0108))
#define SOC_VCODEC_BUS_VENC_QOS_MODE_ADDR(base) ((base) + (0x010C))
#define SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0110))
#define SOC_VCODEC_BUS_VENC_QOS_SATURATION_ADDR(base) ((base) + (0x0114))
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0118))
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_ADDR(base) ((base) + (0x8000))
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_ADDR(base) ((base) + (0x8004))
#define SOC_VCODEC_BUS_VENC_TRANS_F_MODE_ADDR(base) ((base) + (0x8008))
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_ADDR(base) ((base) + (0x800C))
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_ADDR(base) ((base) + (0x8010))
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_ADDR(base) ((base) + (0x8014))
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_ADDR(base) ((base) + (0x8020))
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_ADDR(base) ((base) + (0x8024))
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_ADDR(base) ((base) + (0x8028))
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_ADDR(base) ((base) + (0x802C))
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_ADDR(base) ((base) + (0x8030))
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_ADDR(base) ((base) + (0x8080))
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_ADDR(base) ((base) + (0x8084))
#define SOC_VCODEC_BUS_VENC_TRANS_P_EN_ADDR(base) ((base) + (0x8088))
#define SOC_VCODEC_BUS_VENC_TRANS_P_MODE_ADDR(base) ((base) + (0x808C))
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_ADDR(base) ((base) + (0x80EC))
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_ADDR(base) ((base) + (0x80F0))
#define SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_ADDR(base) ((base) + (0x80F4))
#define SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_ADDR(base) ((base) + (0x80F8))
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_ADDR(base) ((base) + (0x8400))
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_ADDR(base) ((base) + (0x8404))
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_ADDR(base) ((base) + (0x8408))
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_ADDR(base) ((base) + (0x840C))
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_ADDR(base) ((base) + (0x8424))
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_ADDR(base) ((base) + (0x8428))
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_ADDR(base) ((base) + (0x842C))
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_ADDR(base) ((base) + (0x8430))
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_ADDR(base) ((base) + (0x8434))
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_ADDR(base) ((base) + (0x8438))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_ADDR(base) ((base) + (0x8538))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_ADDR(base) ((base) + (0x853C))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_ADDR(base) ((base) + (0x8540))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_ADDR(base) ((base) + (0x854C))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_ADDR(base) ((base) + (0x8550))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_ADDR(base) ((base) + (0x8554))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_ADDR(base) ((base) + (0x8560))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_ADDR(base) ((base) + (0x8564))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_ADDR(base) ((base) + (0x8568))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_ADDR(base) ((base) + (0x8574))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_ADDR(base) ((base) + (0x8578))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_ADDR(base) ((base) + (0x857C))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_ADDR(base) ((base) + (0x8588))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_ADDR(base) ((base) + (0x858C))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_ADDR(base) ((base) + (0x8590))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_ADDR(base) ((base) + (0x859C))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_ADDR(base) ((base) + (0x85A0))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_ADDR(base) ((base) + (0x85A4))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_ADDR(base) ((base) + (0x85B0))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_ADDR(base) ((base) + (0x85B4))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_ADDR(base) ((base) + (0x85B8))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_ADDR(base) ((base) + (0x85C4))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_ADDR(base) ((base) + (0x85C8))
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_ADDR(base) ((base) + (0x85CC))
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_ADDR(base) ((base) + (0x0000))
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_ADDR(base) ((base) + (0x0004))
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_ADDR(base) ((base) + (0x0008))
#define SOC_VCODEC_BUS_VDEC_QOS_MODE_ADDR(base) ((base) + (0x000C))
#define SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_ADDR(base) ((base) + (0x0010))
#define SOC_VCODEC_BUS_VDEC_QOS_SATURATION_ADDR(base) ((base) + (0x0014))
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_ADDR(base) ((base) + (0x0018))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_VCODEC_BUS_VENC_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_VCODEC_BUS_VENC_ADAPTERRATE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAPTERRATE_rate_START (0)
#define SOC_VCODEC_BUS_VENC_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_ADAP_BYPASS_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_ADAP_BYPASS_bypass_START (0)
#define SOC_VCODEC_BUS_VENC_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_id_coreid_START (0)
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_id_revisionid_START (0)
#define SOC_VCODEC_BUS_VDEC_ADAPTER_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rate : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_VCODEC_BUS_VDEC_ADAPTERRATE_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAPTERRATE_rate_START (0)
#define SOC_VCODEC_BUS_VDEC_ADAPTERRATE_rate_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bypass : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_bypass_START (0)
#define SOC_VCODEC_BUS_VDEC_ADAP_BYPASS_bypass_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_VCODEC_BUS_ERR_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_ERR_ID_COREID_id_coreid_START (0)
#define SOC_VCODEC_BUS_ERR_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_VCODEC_BUS_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_ID_REVISIONID_id_revisionid_START (0)
#define SOC_VCODEC_BUS_ID_REVISIONID_id_revisionid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faulten : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_FAULTEN_UNION;
#endif
#define SOC_VCODEC_BUS_FAULTEN_faulten_START (0)
#define SOC_VCODEC_BUS_FAULTEN_faulten_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errvld : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_ERRVLD_UNION;
#endif
#define SOC_VCODEC_BUS_ERRVLD_errvld_START (0)
#define SOC_VCODEC_BUS_ERRVLD_errvld_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_ERRCLR_UNION;
#endif
#define SOC_VCODEC_BUS_ERRCLR_errclr_START (0)
#define SOC_VCODEC_BUS_ERRCLR_errclr_END (0)
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
} SOC_VCODEC_BUS_ERRLOG0_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG0_lock_START (0)
#define SOC_VCODEC_BUS_ERRLOG0_lock_END (0)
#define SOC_VCODEC_BUS_ERRLOG0_opc_START (1)
#define SOC_VCODEC_BUS_ERRLOG0_opc_END (4)
#define SOC_VCODEC_BUS_ERRLOG0_errcode_START (8)
#define SOC_VCODEC_BUS_ERRLOG0_errcode_END (10)
#define SOC_VCODEC_BUS_ERRLOG0_len1_START (16)
#define SOC_VCODEC_BUS_ERRLOG0_len1_END (23)
#define SOC_VCODEC_BUS_ERRLOG0_format_START (31)
#define SOC_VCODEC_BUS_ERRLOG0_format_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog1 : 22;
        unsigned int reserved : 10;
    } reg;
} SOC_VCODEC_BUS_ERRLOG1_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG1_errlog1_START (0)
#define SOC_VCODEC_BUS_ERRLOG1_errlog1_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog3 : 31;
        unsigned int reserved : 1;
    } reg;
} SOC_VCODEC_BUS_ERRLOG3_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG3_errlog3_START (0)
#define SOC_VCODEC_BUS_ERRLOG3_errlog3_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog5 : 17;
        unsigned int reserved : 15;
    } reg;
} SOC_VCODEC_BUS_ERRLOG5_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG5_errlog5_START (0)
#define SOC_VCODEC_BUS_ERRLOG5_errlog5_END (16)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int errlog7 : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_ERRLOG7_UNION;
#endif
#define SOC_VCODEC_BUS_ERRLOG7_errlog7_START (0)
#define SOC_VCODEC_BUS_ERRLOG7_errlog7_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_VCODEC_BUS_VENC_QOS_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_coretypeid_START (0)
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_coretypeid_END (7)
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_corechecksum_START (8)
#define SOC_VCODEC_BUS_VENC_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_userid_START (0)
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_userid_END (7)
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_VCODEC_BUS_VENC_QOS_ID_REVISIONID_flexnocid_END (31)
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
} SOC_VCODEC_BUS_VENC_QOS_PRIORITY_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p0_START (0)
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p0_END (1)
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p1_START (8)
#define SOC_VCODEC_BUS_VENC_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_QOS_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_MODE_mode_START (0)
#define SOC_VCODEC_BUS_VENC_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bandwidth : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_bandwidth_START (0)
#define SOC_VCODEC_BUS_VENC_QOS_BANDWIDTH_bandwidth_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int saturation : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_VCODEC_BUS_VENC_QOS_SATURATION_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_SATURATION_saturation_START (0)
#define SOC_VCODEC_BUS_VENC_QOS_SATURATION_saturation_END (9)
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
} SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_extthren_START (1)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_extthren_END (1)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_intclken_START (2)
#define SOC_VCODEC_BUS_VENC_QOS_EXTCONTROL_intclken_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_coretypeid_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_coretypeid_END (7)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_corechecksum_START (8)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_userid_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_userid_END (7)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_flexnocid_START (8)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_MODE_mode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_MODE_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addrbase_low : 32;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_addrbase_low_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_LOW_addrbase_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addrbase_high : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_addrbase_high_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRBASE_HIGH_addrbase_high_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addrwindowsize : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_ADDRWINDOWSIZE_addrwindowsize_END (5)
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
} SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_rden_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_rden_END (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_wren_START (1)
#define SOC_VCODEC_BUS_VENC_TRANS_F_OPCODE_wren_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userbase : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_userbase_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERBASE_userbase_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int usermask : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_usermask_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_USERMASK_usermask_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int securitybase : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_securitybase_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYBASE_securitybase_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int securitymask : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_securitymask_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_F_SECURITYMASK_securitymask_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_coretypeid_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_coretypeid_END (7)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_corechecksum_START (8)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_userid_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_userid_END (7)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_flexnocid_START (8)
#define SOC_VCODEC_BUS_VENC_TRANS_P_ID_REVISIONID_flexnocid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_P_EN_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_EN_en_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_EN_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_P_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_MODE_mode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_MODE_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflowstatus : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_overflowstatus_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWSTATUS_overflowstatus_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overflowreset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_overflowreset_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_OVERFLOWRESET_overflowreset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pendingeventmode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_pendingeventmode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_PENDINGEVENTMODE_pendingeventmode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int prescaler : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_prescaler_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_P_PRESCALER_prescaler_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_coreid : 32;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_id_coreid_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_COREID_id_coreid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id_revisionid : 32;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_id_revisionid_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_ID_REVISIONID_id_revisionid_END (31)
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
} SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_erren_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_erren_END (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_traceen_START (1)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_traceen_END (1)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_payloaden_START (2)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_payloaden_END (2)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_staten_START (3)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_staten_END (3)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_alarmen_START (4)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_alarmen_END (4)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_statconddump_START (5)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_statconddump_END (5)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_intrusivemode_START (6)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_intrusivemode_END (6)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_filtbytealwayschainableen_START (7)
#define SOC_VCODEC_BUS_VENC_TRANS_M_MAINCTL_filtbytealwayschainableen_END (7)
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
} SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_globalen_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_globalen_END (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_active_START (1)
#define SOC_VCODEC_BUS_VENC_TRANS_M_CFGCTL_active_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statperiod : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_statperiod_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATPERIOD_statperiod_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statgo : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_statgo_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATGO_statgo_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmmin : 32;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_statalarmmin_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMIN_statalarmmin_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmmax : 32;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_statalarmmax_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMMAX_statalarmmax_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmstatus : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_statalarmstatus_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMSTATUS_statalarmstatus_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int statalarmclr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_statalarmclr_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_STATALARMCLR_statalarmclr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_counters_0_src_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_SRC_counters_0_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_ALARMMODE_counters_0_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_0_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_counters_0_val_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_0_VAL_counters_0_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_counters_1_src_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_SRC_counters_1_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_ALARMMODE_counters_1_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_1_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_counters_1_val_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_1_VAL_counters_1_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_2_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_counters_2_src_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_SRC_counters_2_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_2_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_ALARMMODE_counters_2_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_2_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_counters_2_val_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_2_VAL_counters_2_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_3_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_counters_3_src_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_SRC_counters_3_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_3_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_ALARMMODE_counters_3_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_3_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_counters_3_val_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_3_VAL_counters_3_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_4_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_counters_4_src_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_SRC_counters_4_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_4_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_ALARMMODE_counters_4_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_4_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_counters_4_val_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_4_VAL_counters_4_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_5_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_counters_5_src_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_SRC_counters_5_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_5_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_ALARMMODE_counters_5_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_5_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_counters_5_val_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_5_VAL_counters_5_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_6_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_counters_6_src_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_SRC_counters_6_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_6_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_ALARMMODE_counters_6_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_6_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_counters_6_val_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_6_VAL_counters_6_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_7_src : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_counters_7_src_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_SRC_counters_7_src_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_7_alarmmode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_ALARMMODE_counters_7_alarmmode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int counters_7_val : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_UNION;
#endif
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_counters_7_val_START (0)
#define SOC_VCODEC_BUS_VENC_TRANS_M_COUNTERS_7_VAL_counters_7_val_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int coretypeid : 8;
        unsigned int corechecksum : 24;
    } reg;
} SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_coretypeid_START (0)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_coretypeid_END (7)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_corechecksum_START (8)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_COREID_corechecksum_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int userid : 8;
        unsigned int flexnocid : 24;
    } reg;
} SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_userid_START (0)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_userid_END (7)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_flexnocid_START (8)
#define SOC_VCODEC_BUS_VDEC_QOS_ID_REVISIONID_flexnocid_END (31)
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
} SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p0_START (0)
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p0_END (1)
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p1_START (8)
#define SOC_VCODEC_BUS_VDEC_QOS_PRIORITY_p1_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_VCODEC_BUS_VDEC_QOS_MODE_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_MODE_mode_START (0)
#define SOC_VCODEC_BUS_VDEC_QOS_MODE_mode_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bandwidth : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_bandwidth_START (0)
#define SOC_VCODEC_BUS_VDEC_QOS_BANDWIDTH_bandwidth_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int saturation : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_VCODEC_BUS_VDEC_QOS_SATURATION_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_SATURATION_saturation_START (0)
#define SOC_VCODEC_BUS_VDEC_QOS_SATURATION_saturation_END (9)
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
} SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_UNION;
#endif
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_socketqosen_START (0)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_socketqosen_END (0)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_extthren_START (1)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_extthren_END (1)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_intclken_START (2)
#define SOC_VCODEC_BUS_VDEC_QOS_EXTCONTROL_intclken_END (2)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
