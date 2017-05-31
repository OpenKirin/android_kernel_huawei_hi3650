#ifndef __SOC_ASP_HIFI3_INTERFACE_H__
#define __SOC_ASP_HIFI3_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ASP_HIFI3_TRAXID_ADDR(base) ((base) + (0x0000))
#define SOC_ASP_HIFI3_TRAXCTRL_ADDR(base) ((base) + (0x0004))
#define SOC_ASP_HIFI3_TRAXSTAT_ADDR(base) ((base) + (0x0008))
#define SOC_ASP_HIFI3_TRAXDATA_ADDR(base) ((base) + (0x000C))
#define SOC_ASP_HIFI3_TRAXADDR_ADDR(base) ((base) + (0x0010))
#define SOC_ASP_HIFI3_TRIGGERPC_ADDR(base) ((base) + (0x0014))
#define SOC_ASP_HIFI3_PCMATCHCTRL_ADDR(base) ((base) + (0x0018))
#define SOC_ASP_HIFI3_DELAYCNT_ADDR(base) ((base) + (0x001C))
#define SOC_ASP_HIFI3_MEMADDRSTART_ADDR(base) ((base) + (0x0020))
#define SOC_ASP_HIFI3_MEMADDREND_ADDR(base) ((base) + (0x0024))
#define SOC_ASP_HIFI3_compressparams_ADDR(base) ((base) + (0x006C))
#define SOC_ASP_HIFI3_PMG_ADDR(base) ((base) + (0x1000))
#define SOC_ASP_HIFI3_INTPC_ADDR(base) ((base) + (0x1010))
#define SOC_ASP_HIFI3_perfcounter0_ADDR(base) ((base) + (0x1080))
#define SOC_ASP_HIFI3_perfcounter1_ADDR(base) ((base) + (0x1084))
#define SOC_ASP_HIFI3_perfcounter2_ADDR(base) ((base) + (0x1088))
#define SOC_ASP_HIFI3_perfcounter3_ADDR(base) ((base) + (0x108C))
#define SOC_ASP_HIFI3_PMCTRL0_ADDR(base) ((base) + (0x1100))
#define SOC_ASP_HIFI3_PMCTRL1_ADDR(base) ((base) + (0x1104))
#define SOC_ASP_HIFI3_PMCTRL2_ADDR(base) ((base) + (0x1108))
#define SOC_ASP_HIFI3_PMCTRL3_ADDR(base) ((base) + (0x110C))
#define SOC_ASP_HIFI3_PMSTA0_ADDR(base) ((base) + (0x1180))
#define SOC_ASP_HIFI3_PMSTA1_ADDR(base) ((base) + (0x1184))
#define SOC_ASP_HIFI3_PMSTA2_ADDR(base) ((base) + (0x1188))
#define SOC_ASP_HIFI3_PMSTA3_ADDR(base) ((base) + (0x118C))
#define SOC_ASP_HIFI3_OCDID_ADDR(base) ((base) + (0x2000))
#define SOC_ASP_HIFI3_DCRCLR_ADDR(base) ((base) + (0x2008))
#define SOC_ASP_HIFI3_DCRSET_ADDR(base) ((base) + (0x200C))
#define SOC_ASP_HIFI3_DSR_ADDR(base) ((base) + (0x2010))
#define SOC_ASP_HIFI3_DDR_ADDR(base) ((base) + (0x2014))
#define SOC_ASP_HIFI3_DDREXEC_ADDR(base) ((base) + (0x2018))
#define SOC_ASP_HIFI3_DIR0EXEC_ADDR(base) ((base) + (0x201C))
#define SOC_ASP_HIFI3_denugInst0_ADDR(base) ((base) + (0x2020))
#define SOC_ASP_HIFI3_debugInst1_ADDR(base) ((base) + (0x2024))
#define SOC_ASP_HIFI3_PWRCTL_ADDR(base) ((base) + (0x3020))
#define SOC_ASP_HIFI3_PWRSTAT_ADDR(base) ((base) + (0x3024))
#define SOC_ASP_HIFI3_ERISTAT_ADDR(base) ((base) + (0x3028))
#define SOC_ASP_HIFI3_undoRegThID1_ADDR(base) ((base) + (0x3034))
#define SOC_ASP_HIFI3_undocRegBuild_ADDR(base) ((base) + (0x3038))
#define SOC_ASP_HIFI3_undocRegBcid_ADDR(base) ((base) + (0x303C))
#define SOC_ASP_HIFI3_itCtrl_ADDR(base) ((base) + (0x3F00))
#define SOC_ASP_HIFI3_claimSet_ADDR(base) ((base) + (0x3FA0))
#define SOC_ASP_HIFI3_claimClear_ADDR(base) ((base) + (0x3FA4))
#define SOC_ASP_HIFI3_devId_ADDR(base) ((base) + (0x3FC8))
#define SOC_ASP_HIFI3_devType_ADDR(base) ((base) + (0x3FCC))
#define SOC_ASP_HIFI3_peripheralId4_ADDR(base) ((base) + (0x3FD0))
#define SOC_ASP_HIFI3_peripheralId5_ADDR(base) ((base) + (0x3FD4))
#define SOC_ASP_HIFI3_peripheralId6_ADDR(base) ((base) + (0x3FD8))
#define SOC_ASP_HIFI3_peripheralId7_ADDR(base) ((base) + (0x3FDC))
#define SOC_ASP_HIFI3_peripheralId0_ADDR(base) ((base) + (0x3FE0))
#define SOC_ASP_HIFI3_peripheralId1_ADDR(base) ((base) + (0x3FE4))
#define SOC_ASP_HIFI3_peripheralId2_ADDR(base) ((base) + (0x3FE8))
#define SOC_ASP_HIFI3_peripheralId3_ADDR(base) ((base) + (0x3FEC))
#define SOC_ASP_HIFI3_componentId0_ADDR(base) ((base) + (0x3FF0))
#define SOC_ASP_HIFI3_componentId1_ADDR(base) ((base) + (0x3FF4))
#define SOC_ASP_HIFI3_componentId2_ADDR(base) ((base) + (0x3FF8))
#define SOC_ASP_HIFI3_componentId3_ADDR(base) ((base) + (0x3FFC))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TRAXID : 32;
    } reg;
} SOC_ASP_HIFI3_TRAXID_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXID_TRAXID_START (0)
#define SOC_ASP_HIFI3_TRAXID_TRAXID_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int traceEnabled : 1;
        unsigned int traceStop : 1;
        unsigned int pcMatchEn : 1;
        unsigned int reserved_0 : 1;
        unsigned int processorTriggerInEn : 1;
        unsigned int crossTriggerInEn : 1;
        unsigned int reserved_1 : 1;
        unsigned int traceMemOutEn : 1;
        unsigned int reserved_2 : 1;
        unsigned int CountUnitIsinst : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int encodeSyncMessageFreq : 3;
        unsigned int reserved_5 : 1;
        unsigned int processorTriggerOutUponPrimeTrigger : 1;
        unsigned int processorTriggerOutUponZeroCount : 1;
        unsigned int reserved_6 : 2;
        unsigned int CrossTriggerOutUponPrimeTrigger : 1;
        unsigned int CrossTriggerOutUponZeroCount : 1;
        unsigned int CrossTriggerOutTopology : 1;
        unsigned int CrossTriggerInAckTopology : 1;
        unsigned int TRAXCTRL : 8;
    } reg;
} SOC_ASP_HIFI3_TRAXCTRL_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXCTRL_traceEnabled_START (0)
#define SOC_ASP_HIFI3_TRAXCTRL_traceEnabled_END (0)
#define SOC_ASP_HIFI3_TRAXCTRL_traceStop_START (1)
#define SOC_ASP_HIFI3_TRAXCTRL_traceStop_END (1)
#define SOC_ASP_HIFI3_TRAXCTRL_pcMatchEn_START (2)
#define SOC_ASP_HIFI3_TRAXCTRL_pcMatchEn_END (2)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerInEn_START (4)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerInEn_END (4)
#define SOC_ASP_HIFI3_TRAXCTRL_crossTriggerInEn_START (5)
#define SOC_ASP_HIFI3_TRAXCTRL_crossTriggerInEn_END (5)
#define SOC_ASP_HIFI3_TRAXCTRL_traceMemOutEn_START (7)
#define SOC_ASP_HIFI3_TRAXCTRL_traceMemOutEn_END (7)
#define SOC_ASP_HIFI3_TRAXCTRL_CountUnitIsinst_START (9)
#define SOC_ASP_HIFI3_TRAXCTRL_CountUnitIsinst_END (9)
#define SOC_ASP_HIFI3_TRAXCTRL_encodeSyncMessageFreq_START (12)
#define SOC_ASP_HIFI3_TRAXCTRL_encodeSyncMessageFreq_END (14)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponPrimeTrigger_START (16)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponPrimeTrigger_END (16)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponZeroCount_START (17)
#define SOC_ASP_HIFI3_TRAXCTRL_processorTriggerOutUponZeroCount_END (17)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponPrimeTrigger_START (20)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponPrimeTrigger_END (20)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponZeroCount_START (21)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutUponZeroCount_END (21)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutTopology_START (22)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerOutTopology_END (22)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerInAckTopology_START (23)
#define SOC_ASP_HIFI3_TRAXCTRL_CrossTriggerInAckTopology_END (23)
#define SOC_ASP_HIFI3_TRAXCTRL_TRAXCTRL_START (24)
#define SOC_ASP_HIFI3_TRAXCTRL_TRAXCTRL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int traceActive : 1;
        unsigned int primeTrigger : 1;
        unsigned int pcMatchImputed : 1;
        unsigned int precedingJTAGxsacResult0 : 1;
        unsigned int processTriggerInImputed : 1;
        unsigned int corssTriggerInImputed : 1;
        unsigned int reserved_0 : 2;
        unsigned int reserved_1 : 5;
        unsigned int reserved_2 : 3;
        unsigned int processorTriggerOut : 1;
        unsigned int crossTriggerOut : 1;
        unsigned int reserved_3 : 4;
        unsigned int crossTriggerOutAckTopology : 1;
        unsigned int crossTriggerInTopology : 1;
        unsigned int TRAXSTAT : 8;
    } reg;
} SOC_ASP_HIFI3_TRAXSTAT_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXSTAT_traceActive_START (0)
#define SOC_ASP_HIFI3_TRAXSTAT_traceActive_END (0)
#define SOC_ASP_HIFI3_TRAXSTAT_primeTrigger_START (1)
#define SOC_ASP_HIFI3_TRAXSTAT_primeTrigger_END (1)
#define SOC_ASP_HIFI3_TRAXSTAT_pcMatchImputed_START (2)
#define SOC_ASP_HIFI3_TRAXSTAT_pcMatchImputed_END (2)
#define SOC_ASP_HIFI3_TRAXSTAT_precedingJTAGxsacResult0_START (3)
#define SOC_ASP_HIFI3_TRAXSTAT_precedingJTAGxsacResult0_END (3)
#define SOC_ASP_HIFI3_TRAXSTAT_processTriggerInImputed_START (4)
#define SOC_ASP_HIFI3_TRAXSTAT_processTriggerInImputed_END (4)
#define SOC_ASP_HIFI3_TRAXSTAT_corssTriggerInImputed_START (5)
#define SOC_ASP_HIFI3_TRAXSTAT_corssTriggerInImputed_END (5)
#define SOC_ASP_HIFI3_TRAXSTAT_processorTriggerOut_START (16)
#define SOC_ASP_HIFI3_TRAXSTAT_processorTriggerOut_END (16)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOut_START (17)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOut_END (17)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOutAckTopology_START (22)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerOutAckTopology_END (22)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerInTopology_START (23)
#define SOC_ASP_HIFI3_TRAXSTAT_crossTriggerInTopology_END (23)
#define SOC_ASP_HIFI3_TRAXSTAT_TRAXSTAT_START (24)
#define SOC_ASP_HIFI3_TRAXSTAT_TRAXSTAT_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TRAXDATA : 32;
    } reg;
} SOC_ASP_HIFI3_TRAXDATA_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXDATA_TRAXDATA_START (0)
#define SOC_ASP_HIFI3_TRAXDATA_TRAXDATA_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TRAXADDR : 32;
    } reg;
} SOC_ASP_HIFI3_TRAXADDR_UNION;
#endif
#define SOC_ASP_HIFI3_TRAXADDR_TRAXADDR_START (0)
#define SOC_ASP_HIFI3_TRAXADDR_TRAXADDR_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TRIGGERPC : 32;
    } reg;
} SOC_ASP_HIFI3_TRIGGERPC_UNION;
#endif
#define SOC_ASP_HIFI3_TRIGGERPC_TRIGGERPC_START (0)
#define SOC_ASP_HIFI3_TRIGGERPC_TRIGGERPC_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int PCMATCHCTRL : 32;
    } reg;
} SOC_ASP_HIFI3_PCMATCHCTRL_UNION;
#endif
#define SOC_ASP_HIFI3_PCMATCHCTRL_PCMATCHCTRL_START (0)
#define SOC_ASP_HIFI3_PCMATCHCTRL_PCMATCHCTRL_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DELAYCNT : 32;
    } reg;
} SOC_ASP_HIFI3_DELAYCNT_UNION;
#endif
#define SOC_ASP_HIFI3_DELAYCNT_DELAYCNT_START (0)
#define SOC_ASP_HIFI3_DELAYCNT_DELAYCNT_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int MEMADDRSTART : 32;
    } reg;
} SOC_ASP_HIFI3_MEMADDRSTART_UNION;
#endif
#define SOC_ASP_HIFI3_MEMADDRSTART_MEMADDRSTART_START (0)
#define SOC_ASP_HIFI3_MEMADDRSTART_MEMADDRSTART_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int MEMADDREND : 32;
    } reg;
} SOC_ASP_HIFI3_MEMADDREND_UNION;
#endif
#define SOC_ASP_HIFI3_MEMADDREND_MEMADDREND_START (0)
#define SOC_ASP_HIFI3_MEMADDREND_MEMADDREND_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cp2 : 16;
        unsigned int cp1 : 16;
    } reg;
} SOC_ASP_HIFI3_compressparams_UNION;
#endif
#define SOC_ASP_HIFI3_compressparams_cp2_START (0)
#define SOC_ASP_HIFI3_compressparams_cp2_END (15)
#define SOC_ASP_HIFI3_compressparams_cp1_START (16)
#define SOC_ASP_HIFI3_compressparams_cp1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pergloben : 1;
        unsigned int PMG : 31;
    } reg;
} SOC_ASP_HIFI3_PMG_UNION;
#endif
#define SOC_ASP_HIFI3_PMG_pergloben_START (0)
#define SOC_ASP_HIFI3_PMG_pergloben_END (0)
#define SOC_ASP_HIFI3_PMG_PMG_START (1)
#define SOC_ASP_HIFI3_PMG_PMG_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int INTPC : 32;
    } reg;
} SOC_ASP_HIFI3_INTPC_UNION;
#endif
#define SOC_ASP_HIFI3_INTPC_INTPC_START (0)
#define SOC_ASP_HIFI3_INTPC_INTPC_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int PM0 : 32;
    } reg;
} SOC_ASP_HIFI3_perfcounter0_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter0_PM0_START (0)
#define SOC_ASP_HIFI3_perfcounter0_PM0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int PM1 : 32;
    } reg;
} SOC_ASP_HIFI3_perfcounter1_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter1_PM1_START (0)
#define SOC_ASP_HIFI3_perfcounter1_PM1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int PM2 : 32;
    } reg;
} SOC_ASP_HIFI3_perfcounter2_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter2_PM2_START (0)
#define SOC_ASP_HIFI3_perfcounter2_PM2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int PM3 : 32;
    } reg;
} SOC_ASP_HIFI3_perfcounter3_UNION;
#endif
#define SOC_ASP_HIFI3_perfcounter3_PM3_START (0)
#define SOC_ASP_HIFI3_perfcounter3_PM3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perfIntEn0 : 1;
        unsigned int reserved_0 : 2;
        unsigned int kernelcount0 : 1;
        unsigned int traceLevel0 : 4;
        unsigned int perfSelect0 : 5;
        unsigned int reserved_1 : 3;
        unsigned int perMask0 : 16;
    } reg;
} SOC_ASP_HIFI3_PMCTRL0_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL0_perfIntEn0_START (0)
#define SOC_ASP_HIFI3_PMCTRL0_perfIntEn0_END (0)
#define SOC_ASP_HIFI3_PMCTRL0_kernelcount0_START (3)
#define SOC_ASP_HIFI3_PMCTRL0_kernelcount0_END (3)
#define SOC_ASP_HIFI3_PMCTRL0_traceLevel0_START (4)
#define SOC_ASP_HIFI3_PMCTRL0_traceLevel0_END (7)
#define SOC_ASP_HIFI3_PMCTRL0_perfSelect0_START (8)
#define SOC_ASP_HIFI3_PMCTRL0_perfSelect0_END (12)
#define SOC_ASP_HIFI3_PMCTRL0_perMask0_START (16)
#define SOC_ASP_HIFI3_PMCTRL0_perMask0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perfIntEn1 : 1;
        unsigned int reserved_0 : 2;
        unsigned int kernelcount1 : 1;
        unsigned int traceLevel1 : 4;
        unsigned int perfSelect1 : 5;
        unsigned int reserved_1 : 3;
        unsigned int perMask1 : 16;
    } reg;
} SOC_ASP_HIFI3_PMCTRL1_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL1_perfIntEn1_START (0)
#define SOC_ASP_HIFI3_PMCTRL1_perfIntEn1_END (0)
#define SOC_ASP_HIFI3_PMCTRL1_kernelcount1_START (3)
#define SOC_ASP_HIFI3_PMCTRL1_kernelcount1_END (3)
#define SOC_ASP_HIFI3_PMCTRL1_traceLevel1_START (4)
#define SOC_ASP_HIFI3_PMCTRL1_traceLevel1_END (7)
#define SOC_ASP_HIFI3_PMCTRL1_perfSelect1_START (8)
#define SOC_ASP_HIFI3_PMCTRL1_perfSelect1_END (12)
#define SOC_ASP_HIFI3_PMCTRL1_perMask1_START (16)
#define SOC_ASP_HIFI3_PMCTRL1_perMask1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perfIntEn2 : 1;
        unsigned int reserved_0 : 2;
        unsigned int kernelcount2 : 1;
        unsigned int traceLevel2 : 4;
        unsigned int perfSelect2 : 5;
        unsigned int reserved_1 : 3;
        unsigned int perMask2 : 16;
    } reg;
} SOC_ASP_HIFI3_PMCTRL2_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL2_perfIntEn2_START (0)
#define SOC_ASP_HIFI3_PMCTRL2_perfIntEn2_END (0)
#define SOC_ASP_HIFI3_PMCTRL2_kernelcount2_START (3)
#define SOC_ASP_HIFI3_PMCTRL2_kernelcount2_END (3)
#define SOC_ASP_HIFI3_PMCTRL2_traceLevel2_START (4)
#define SOC_ASP_HIFI3_PMCTRL2_traceLevel2_END (7)
#define SOC_ASP_HIFI3_PMCTRL2_perfSelect2_START (8)
#define SOC_ASP_HIFI3_PMCTRL2_perfSelect2_END (12)
#define SOC_ASP_HIFI3_PMCTRL2_perMask2_START (16)
#define SOC_ASP_HIFI3_PMCTRL2_perMask2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perfIntEn3 : 1;
        unsigned int reserved_0 : 2;
        unsigned int kernelcount3 : 1;
        unsigned int traceLevel3 : 4;
        unsigned int perfSelect3 : 5;
        unsigned int reserved_1 : 3;
        unsigned int perMask3 : 16;
    } reg;
} SOC_ASP_HIFI3_PMCTRL3_UNION;
#endif
#define SOC_ASP_HIFI3_PMCTRL3_perfIntEn3_START (0)
#define SOC_ASP_HIFI3_PMCTRL3_perfIntEn3_END (0)
#define SOC_ASP_HIFI3_PMCTRL3_kernelcount3_START (3)
#define SOC_ASP_HIFI3_PMCTRL3_kernelcount3_END (3)
#define SOC_ASP_HIFI3_PMCTRL3_traceLevel3_START (4)
#define SOC_ASP_HIFI3_PMCTRL3_traceLevel3_END (7)
#define SOC_ASP_HIFI3_PMCTRL3_perfSelect3_START (8)
#define SOC_ASP_HIFI3_PMCTRL3_perfSelect3_END (12)
#define SOC_ASP_HIFI3_PMCTRL3_perMask3_START (16)
#define SOC_ASP_HIFI3_PMCTRL3_perMask3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perfverflow0 : 1;
        unsigned int reserved_0 : 3;
        unsigned int perfIntAsserted0 : 1;
        unsigned int reserved_1 : 27;
    } reg;
} SOC_ASP_HIFI3_PMSTA0_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA0_perfverflow0_START (0)
#define SOC_ASP_HIFI3_PMSTA0_perfverflow0_END (0)
#define SOC_ASP_HIFI3_PMSTA0_perfIntAsserted0_START (4)
#define SOC_ASP_HIFI3_PMSTA0_perfIntAsserted0_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perfverflow1 : 1;
        unsigned int reserved_0 : 3;
        unsigned int perfIntAsserted1 : 1;
        unsigned int reserved_1 : 27;
    } reg;
} SOC_ASP_HIFI3_PMSTA1_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA1_perfverflow1_START (0)
#define SOC_ASP_HIFI3_PMSTA1_perfverflow1_END (0)
#define SOC_ASP_HIFI3_PMSTA1_perfIntAsserted1_START (4)
#define SOC_ASP_HIFI3_PMSTA1_perfIntAsserted1_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perfverflow2 : 1;
        unsigned int reserved_0 : 3;
        unsigned int perfIntAsserted2 : 1;
        unsigned int reserved_1 : 27;
    } reg;
} SOC_ASP_HIFI3_PMSTA2_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA2_perfverflow2_START (0)
#define SOC_ASP_HIFI3_PMSTA2_perfverflow2_END (0)
#define SOC_ASP_HIFI3_PMSTA2_perfIntAsserted2_START (4)
#define SOC_ASP_HIFI3_PMSTA2_perfIntAsserted2_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int perfverflow3 : 1;
        unsigned int reserved_0 : 3;
        unsigned int perfIntAsserted3 : 1;
        unsigned int reserved_1 : 27;
    } reg;
} SOC_ASP_HIFI3_PMSTA3_UNION;
#endif
#define SOC_ASP_HIFI3_PMSTA3_perfverflow3_START (0)
#define SOC_ASP_HIFI3_PMSTA3_perfverflow3_END (0)
#define SOC_ASP_HIFI3_PMSTA3_perfIntAsserted3_START (4)
#define SOC_ASP_HIFI3_PMSTA3_perfIntAsserted3_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int OCDID : 32;
    } reg;
} SOC_ASP_HIFI3_OCDID_UNION;
#endif
#define SOC_ASP_HIFI3_OCDID_OCDID_START (0)
#define SOC_ASP_HIFI3_OCDID_OCDID_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableOCD : 1;
        unsigned int hostDebugInterrupt : 1;
        unsigned int induceOCDoverride : 1;
        unsigned int reserved_0 : 13;
        unsigned int extDbgIntEn : 1;
        unsigned int xOCDModePulseEn : 1;
        unsigned int reserved_1 : 6;
        unsigned int breakOutTopology : 1;
        unsigned int breakInAckTopology : 1;
        unsigned int reserved_2 : 6;
    } reg;
} SOC_ASP_HIFI3_DCRCLR_UNION;
#endif
#define SOC_ASP_HIFI3_DCRCLR_enableOCD_START (0)
#define SOC_ASP_HIFI3_DCRCLR_enableOCD_END (0)
#define SOC_ASP_HIFI3_DCRCLR_hostDebugInterrupt_START (1)
#define SOC_ASP_HIFI3_DCRCLR_hostDebugInterrupt_END (1)
#define SOC_ASP_HIFI3_DCRCLR_induceOCDoverride_START (2)
#define SOC_ASP_HIFI3_DCRCLR_induceOCDoverride_END (2)
#define SOC_ASP_HIFI3_DCRCLR_extDbgIntEn_START (16)
#define SOC_ASP_HIFI3_DCRCLR_extDbgIntEn_END (16)
#define SOC_ASP_HIFI3_DCRCLR_xOCDModePulseEn_START (17)
#define SOC_ASP_HIFI3_DCRCLR_xOCDModePulseEn_END (17)
#define SOC_ASP_HIFI3_DCRCLR_breakOutTopology_START (24)
#define SOC_ASP_HIFI3_DCRCLR_breakOutTopology_END (24)
#define SOC_ASP_HIFI3_DCRCLR_breakInAckTopology_START (25)
#define SOC_ASP_HIFI3_DCRCLR_breakInAckTopology_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableOCD : 1;
        unsigned int hostDebugInterrupt : 1;
        unsigned int induceOCDoverride : 1;
        unsigned int reserved_0 : 13;
        unsigned int extDbgIntEn : 1;
        unsigned int xOCDModePulseEn : 1;
        unsigned int reserved_1 : 6;
        unsigned int breakOutTopology : 1;
        unsigned int breakInAckTopology : 1;
        unsigned int DCRSET : 6;
    } reg;
} SOC_ASP_HIFI3_DCRSET_UNION;
#endif
#define SOC_ASP_HIFI3_DCRSET_enableOCD_START (0)
#define SOC_ASP_HIFI3_DCRSET_enableOCD_END (0)
#define SOC_ASP_HIFI3_DCRSET_hostDebugInterrupt_START (1)
#define SOC_ASP_HIFI3_DCRSET_hostDebugInterrupt_END (1)
#define SOC_ASP_HIFI3_DCRSET_induceOCDoverride_START (2)
#define SOC_ASP_HIFI3_DCRSET_induceOCDoverride_END (2)
#define SOC_ASP_HIFI3_DCRSET_extDbgIntEn_START (16)
#define SOC_ASP_HIFI3_DCRSET_extDbgIntEn_END (16)
#define SOC_ASP_HIFI3_DCRSET_xOCDModePulseEn_START (17)
#define SOC_ASP_HIFI3_DCRSET_xOCDModePulseEn_END (17)
#define SOC_ASP_HIFI3_DCRSET_breakOutTopology_START (24)
#define SOC_ASP_HIFI3_DCRSET_breakOutTopology_END (24)
#define SOC_ASP_HIFI3_DCRSET_breakInAckTopology_START (25)
#define SOC_ASP_HIFI3_DCRSET_breakInAckTopology_END (25)
#define SOC_ASP_HIFI3_DCRSET_DCRSET_START (26)
#define SOC_ASP_HIFI3_DCRSET_DCRSET_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int execDone : 1;
        unsigned int exeException : 1;
        unsigned int exeBusy : 1;
        unsigned int execOverrun : 1;
        unsigned int ocdDtopped : 1;
        unsigned int reserved_0 : 5;
        unsigned int corewroteDDR : 1;
        unsigned int coreReadDDR : 1;
        unsigned int reserved_1 : 2;
        unsigned int hostWroteDDR : 1;
        unsigned int hostReadDDR : 1;
        unsigned int debugPendBreakin : 1;
        unsigned int debugpendhost : 1;
        unsigned int debugpendtrax : 1;
        unsigned int reserved_2 : 1;
        unsigned int debugIntBreakin : 1;
        unsigned int debugIntHost : 1;
        unsigned int debugIntTrax : 1;
        unsigned int reserved_3 : 2;
        unsigned int beakOutAckTopology : 1;
        unsigned int breakInTopology : 1;
        unsigned int reserved_4 : 5;
    } reg;
} SOC_ASP_HIFI3_DSR_UNION;
#endif
#define SOC_ASP_HIFI3_DSR_execDone_START (0)
#define SOC_ASP_HIFI3_DSR_execDone_END (0)
#define SOC_ASP_HIFI3_DSR_exeException_START (1)
#define SOC_ASP_HIFI3_DSR_exeException_END (1)
#define SOC_ASP_HIFI3_DSR_exeBusy_START (2)
#define SOC_ASP_HIFI3_DSR_exeBusy_END (2)
#define SOC_ASP_HIFI3_DSR_execOverrun_START (3)
#define SOC_ASP_HIFI3_DSR_execOverrun_END (3)
#define SOC_ASP_HIFI3_DSR_ocdDtopped_START (4)
#define SOC_ASP_HIFI3_DSR_ocdDtopped_END (4)
#define SOC_ASP_HIFI3_DSR_corewroteDDR_START (10)
#define SOC_ASP_HIFI3_DSR_corewroteDDR_END (10)
#define SOC_ASP_HIFI3_DSR_coreReadDDR_START (11)
#define SOC_ASP_HIFI3_DSR_coreReadDDR_END (11)
#define SOC_ASP_HIFI3_DSR_hostWroteDDR_START (14)
#define SOC_ASP_HIFI3_DSR_hostWroteDDR_END (14)
#define SOC_ASP_HIFI3_DSR_hostReadDDR_START (15)
#define SOC_ASP_HIFI3_DSR_hostReadDDR_END (15)
#define SOC_ASP_HIFI3_DSR_debugPendBreakin_START (16)
#define SOC_ASP_HIFI3_DSR_debugPendBreakin_END (16)
#define SOC_ASP_HIFI3_DSR_debugpendhost_START (17)
#define SOC_ASP_HIFI3_DSR_debugpendhost_END (17)
#define SOC_ASP_HIFI3_DSR_debugpendtrax_START (18)
#define SOC_ASP_HIFI3_DSR_debugpendtrax_END (18)
#define SOC_ASP_HIFI3_DSR_debugIntBreakin_START (20)
#define SOC_ASP_HIFI3_DSR_debugIntBreakin_END (20)
#define SOC_ASP_HIFI3_DSR_debugIntHost_START (21)
#define SOC_ASP_HIFI3_DSR_debugIntHost_END (21)
#define SOC_ASP_HIFI3_DSR_debugIntTrax_START (22)
#define SOC_ASP_HIFI3_DSR_debugIntTrax_END (22)
#define SOC_ASP_HIFI3_DSR_beakOutAckTopology_START (25)
#define SOC_ASP_HIFI3_DSR_beakOutAckTopology_END (25)
#define SOC_ASP_HIFI3_DSR_breakInTopology_START (26)
#define SOC_ASP_HIFI3_DSR_breakInTopology_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DDR : 32;
    } reg;
} SOC_ASP_HIFI3_DDR_UNION;
#endif
#define SOC_ASP_HIFI3_DDR_DDR_START (0)
#define SOC_ASP_HIFI3_DDR_DDR_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DDREXEC : 32;
    } reg;
} SOC_ASP_HIFI3_DDREXEC_UNION;
#endif
#define SOC_ASP_HIFI3_DDREXEC_DDREXEC_START (0)
#define SOC_ASP_HIFI3_DDREXEC_DDREXEC_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DIR0EXEC : 32;
    } reg;
} SOC_ASP_HIFI3_DIR0EXEC_UNION;
#endif
#define SOC_ASP_HIFI3_DIR0EXEC_DIR0EXEC_START (0)
#define SOC_ASP_HIFI3_DIR0EXEC_DIR0EXEC_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int denugInst0 : 32;
    } reg;
} SOC_ASP_HIFI3_denugInst0_UNION;
#endif
#define SOC_ASP_HIFI3_denugInst0_denugInst0_START (0)
#define SOC_ASP_HIFI3_denugInst0_denugInst0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int debugInst1 : 32;
    } reg;
} SOC_ASP_HIFI3_debugInst1_UNION;
#endif
#define SOC_ASP_HIFI3_debugInst1_debugInst1_START (0)
#define SOC_ASP_HIFI3_debugInst1_debugInst1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 16;
        unsigned int apbcorereset : 1;
        unsigned int reserved_1 : 11;
        unsigned int apbdebugreset : 1;
        unsigned int pwrctl : 3;
    } reg;
} SOC_ASP_HIFI3_PWRCTL_UNION;
#endif
#define SOC_ASP_HIFI3_PWRCTL_apbcorereset_START (16)
#define SOC_ASP_HIFI3_PWRCTL_apbcorereset_END (16)
#define SOC_ASP_HIFI3_PWRCTL_apbdebugreset_START (28)
#define SOC_ASP_HIFI3_PWRCTL_apbdebugreset_END (28)
#define SOC_ASP_HIFI3_PWRCTL_pwrctl_START (29)
#define SOC_ASP_HIFI3_PWRCTL_pwrctl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 16;
        unsigned int apbcorewasreset : 1;
        unsigned int reserved_1 : 11;
        unsigned int apbdebugwasreset : 1;
        unsigned int PWRSTAT : 3;
    } reg;
} SOC_ASP_HIFI3_PWRSTAT_UNION;
#endif
#define SOC_ASP_HIFI3_PWRSTAT_apbcorewasreset_START (16)
#define SOC_ASP_HIFI3_PWRSTAT_apbcorewasreset_END (16)
#define SOC_ASP_HIFI3_PWRSTAT_apbdebugwasreset_START (28)
#define SOC_ASP_HIFI3_PWRSTAT_apbdebugwasreset_END (28)
#define SOC_ASP_HIFI3_PWRSTAT_PWRSTAT_START (29)
#define SOC_ASP_HIFI3_PWRSTAT_PWRSTAT_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int stickyErriWrResult : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASP_HIFI3_ERISTAT_UNION;
#endif
#define SOC_ASP_HIFI3_ERISTAT_stickyErriWrResult_START (0)
#define SOC_ASP_HIFI3_ERISTAT_stickyErriWrResult_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int undoRegThID1 : 32;
    } reg;
} SOC_ASP_HIFI3_undoRegThID1_UNION;
#endif
#define SOC_ASP_HIFI3_undoRegThID1_undoRegThID1_START (0)
#define SOC_ASP_HIFI3_undoRegThID1_undoRegThID1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int undocRegBuild : 32;
    } reg;
} SOC_ASP_HIFI3_undocRegBuild_UNION;
#endif
#define SOC_ASP_HIFI3_undocRegBuild_undocRegBuild_START (0)
#define SOC_ASP_HIFI3_undocRegBuild_undocRegBuild_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int undocRegBcid : 32;
    } reg;
} SOC_ASP_HIFI3_undocRegBcid_UNION;
#endif
#define SOC_ASP_HIFI3_undocRegBcid_undocRegBcid_START (0)
#define SOC_ASP_HIFI3_undocRegBcid_undocRegBcid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int itCtrl : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASP_HIFI3_itCtrl_UNION;
#endif
#define SOC_ASP_HIFI3_itCtrl_itCtrl_START (0)
#define SOC_ASP_HIFI3_itCtrl_itCtrl_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int claimSet : 32;
    } reg;
} SOC_ASP_HIFI3_claimSet_UNION;
#endif
#define SOC_ASP_HIFI3_claimSet_claimSet_START (0)
#define SOC_ASP_HIFI3_claimSet_claimSet_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int claimClear : 32;
    } reg;
} SOC_ASP_HIFI3_claimClear_UNION;
#endif
#define SOC_ASP_HIFI3_claimClear_claimClear_START (0)
#define SOC_ASP_HIFI3_claimClear_claimClear_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int devId : 32;
    } reg;
} SOC_ASP_HIFI3_devId_UNION;
#endif
#define SOC_ASP_HIFI3_devId_devId_START (0)
#define SOC_ASP_HIFI3_devId_devId_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int devType : 32;
    } reg;
} SOC_ASP_HIFI3_devType_UNION;
#endif
#define SOC_ASP_HIFI3_devType_devType_START (0)
#define SOC_ASP_HIFI3_devType_devType_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripheralId4 : 32;
    } reg;
} SOC_ASP_HIFI3_peripheralId4_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId4_peripheralId4_START (0)
#define SOC_ASP_HIFI3_peripheralId4_peripheralId4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripheralId5 : 32;
    } reg;
} SOC_ASP_HIFI3_peripheralId5_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId5_peripheralId5_START (0)
#define SOC_ASP_HIFI3_peripheralId5_peripheralId5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripheralId6 : 32;
    } reg;
} SOC_ASP_HIFI3_peripheralId6_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId6_peripheralId6_START (0)
#define SOC_ASP_HIFI3_peripheralId6_peripheralId6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripheralId7 : 32;
    } reg;
} SOC_ASP_HIFI3_peripheralId7_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId7_peripheralId7_START (0)
#define SOC_ASP_HIFI3_peripheralId7_peripheralId7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripheralId0 : 32;
    } reg;
} SOC_ASP_HIFI3_peripheralId0_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId0_peripheralId0_START (0)
#define SOC_ASP_HIFI3_peripheralId0_peripheralId0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripheralId1 : 32;
    } reg;
} SOC_ASP_HIFI3_peripheralId1_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId1_peripheralId1_START (0)
#define SOC_ASP_HIFI3_peripheralId1_peripheralId1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripheralId2 : 32;
    } reg;
} SOC_ASP_HIFI3_peripheralId2_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId2_peripheralId2_START (0)
#define SOC_ASP_HIFI3_peripheralId2_peripheralId2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int peripheralId3 : 32;
    } reg;
} SOC_ASP_HIFI3_peripheralId3_UNION;
#endif
#define SOC_ASP_HIFI3_peripheralId3_peripheralId3_START (0)
#define SOC_ASP_HIFI3_peripheralId3_peripheralId3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int componentId0 : 32;
    } reg;
} SOC_ASP_HIFI3_componentId0_UNION;
#endif
#define SOC_ASP_HIFI3_componentId0_componentId0_START (0)
#define SOC_ASP_HIFI3_componentId0_componentId0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int componentId1 : 32;
    } reg;
} SOC_ASP_HIFI3_componentId1_UNION;
#endif
#define SOC_ASP_HIFI3_componentId1_componentId1_START (0)
#define SOC_ASP_HIFI3_componentId1_componentId1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int componentId2 : 32;
    } reg;
} SOC_ASP_HIFI3_componentId2_UNION;
#endif
#define SOC_ASP_HIFI3_componentId2_componentId2_START (0)
#define SOC_ASP_HIFI3_componentId2_componentId2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int componentId3 : 32;
    } reg;
} SOC_ASP_HIFI3_componentId3_UNION;
#endif
#define SOC_ASP_HIFI3_componentId3_componentId3_START (0)
#define SOC_ASP_HIFI3_componentId3_componentId3_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
