#ifndef __SOC_G3D_INTERFACE_H__
#define __SOC_G3D_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_G3D_GPU_ID_ADDR(base) ((base) + (0x0000))
#define SOC_G3D_L2_FEATURES_ADDR(base) ((base) + (0x0004))
#define SOC_G3D_TILER_FEATURES_ADDR(base) ((base) + (0x000C))
#define SOC_G3D_MEM_FEATURES_ADDR(base) ((base) + (0x0010))
#define SOC_G3D_MMU_FEATURES_ADDR(base) ((base) + (0x0014))
#define SOC_G3D_AS_PRESENT_ADDR(base) ((base) + (0x0018))
#define SOC_G3D_JS_PRESENT_ADDR(base) ((base) + (0x001C))
#define SOC_G3D_GPU_IRQ_RAWSTAT_ADDR(base) ((base) + (0x0020))
#define SOC_G3D_GPU_IRQ_CLEAR_ADDR(base) ((base) + (0x0024))
#define SOC_G3D_GPU_IRQ_MASK_ADDR(base) ((base) + (0x0028))
#define SOC_G3D_GPU_IRQ_STATUS_ADDR(base) ((base) + (0x002C))
#define SOC_G3D_GPU_COMMAND_ADDR(base) ((base) + (0x0030))
#define SOC_G3D_GPU_STATUS_ADDR(base) ((base) + (0x0034))
#define SOC_G3D_GPU_FAULTSTATUS_ADDR(base) ((base) + (0x003C))
#define SOC_G3D_GPU_FAULTADDRESS_LO_ADDR(base) ((base) + (0x0040))
#define SOC_G3D_GPU_FAULTADDRESS_HI_ADDR(base) ((base) + (0x0044))
#define SOC_G3D_PWR_KEY_ADDR(base) ((base) + (0x0050))
#define SOC_G3D_PWR_KEYOVERRIDE0_ADDR(base) ((base) + (0x0054))
#define SOC_G3D_PWR_KEYOVERRIDE1_ADDR(base) ((base) + (0x0058))
#define SOC_G3D_PRFCNT_BASE_LO_ADDR(base) ((base) + (0x0060))
#define SOC_G3D_PRFCNT_BASE_HI_ADDR(base) ((base) + (0x0064))
#define SOC_G3D_PRFCNT_CONFIG_ADDR(base) ((base) + (0x0068))
#define SOC_G3D_PRFCNT_JM_EN_ADDR(base) ((base) + (0x006C))
#define SOC_G3D_PRFCNT_SHADER_EN_ADDR(base) ((base) + (0x0070))
#define SOC_G3D_PRFCNT_TILER_EN_ADDR(base) ((base) + (0x0074))
#define SOC_G3D_PRFCNT_MMU_L2_EN_ADDR(base) ((base) + (0x007C))
#define SOC_G3D_CYCLE_COUNT_LO_ADDR(base) ((base) + (0x0090))
#define SOC_G3D_CYCLE_COUNT_HI_ADDR(base) ((base) + (0x0094))
#define SOC_G3D_TIMESTAMP_LO_ADDR(base) ((base) + (0x0098))
#define SOC_G3D_TIMESTAMP_HI_ADDR(base) ((base) + (0x009C))
#define SOC_G3D_THREAD_MAX_THREADS_ADDR(base) ((base) + (0x00A0))
#define SOC_G3D_THREAD_MAX_WORKGROUP_ADDR(base) ((base) + (0x00A4))
#define SOC_G3D_THREAD_MAX_BARRIER_SIZE_ADDR(base) ((base) + (0x00A8))
#define SOC_G3D_THREAD_FEATURES_ADDR(base) ((base) + (0x00AC))
#define SOC_G3D_TEXTURE_FEATURES_0_ADDR(base) ((base) + (0x00B0))
#define SOC_G3D_TEXTURE_FEATURES_1_ADDR(base) ((base) + (0x00B4))
#define SOC_G3D_TEXTURE_FEATURES_2_ADDR(base) ((base) + (0x00B8))
#define SOC_G3D_JS0_FEATURES_ADDR(base) ((base) + (0x00C0))
#define SOC_G3D_JS1_FEATURES_ADDR(base) ((base) + (0x00C4))
#define SOC_G3D_JS2_FEATURES_ADDR(base) ((base) + (0x00C8))
#define SOC_G3D_SHADER_PRESENT_LO_ADDR(base) ((base) + (0x0100))
#define SOC_G3D_SHADER_PRESENT_HI_ADDR(base) ((base) + (0x0104))
#define SOC_G3D_TILER_PRESENT_LO_ADDR(base) ((base) + (0x0110))
#define SOC_G3D_TILER_PRESENT_HI_ADDR(base) ((base) + (0x0114))
#define SOC_G3D_L2_PRESENT_LO_ADDR(base) ((base) + (0x0120))
#define SOC_G3D_L2_PRESENT_HI_ADDR(base) ((base) + (0x0124))
#define SOC_G3D_SHADER_READY_LO_ADDR(base) ((base) + (0x0140))
#define SOC_G3D_SHADER_READY_HI_ADDR(base) ((base) + (0x0144))
#define SOC_G3D_TILER_READY_LO_ADDR(base) ((base) + (0x0150))
#define SOC_G3D_TILER_READY_HI_ADDR(base) ((base) + (0x0154))
#define SOC_G3D_L2_READY_LO_ADDR(base) ((base) + (0x0160))
#define SOC_G3D_L2_READY_HI_ADDR(base) ((base) + (0x0164))
#define SOC_G3D_SHADER_PWRON_LO_ADDR(base) ((base) + (0x0180))
#define SOC_G3D_SHADER_PWRON_HI_ADDR(base) ((base) + (0x0184))
#define SOC_G3D_TILER_PWRON_LO_ADDR(base) ((base) + (0x0190))
#define SOC_G3D_TILER_PWRON_HI_ADDR(base) ((base) + (0x0194))
#define SOC_G3D_L2_PWRON_LO_ADDR(base) ((base) + (0x01A0))
#define SOC_G3D_L2_PWRON_HI_ADDR(base) ((base) + (0x01A4))
#define SOC_G3D_SHADER_PWROFF_LO_ADDR(base) ((base) + (0x01C0))
#define SOC_G3D_SHADER_PWROFF_HI_ADDR(base) ((base) + (0x01C4))
#define SOC_G3D_TILER_PWROFF_LO_ADDR(base) ((base) + (0x01D0))
#define SOC_G3D_TILER_PWROFF_HI_ADDR(base) ((base) + (0x01D4))
#define SOC_G3D_L2_PWROFF_LO_ADDR(base) ((base) + (0x01E0))
#define SOC_G3D_L2_PWROFF_HI_ADDR(base) ((base) + (0x01E4))
#define SOC_G3D_SHADER_PWRTRANS_LO_ADDR(base) ((base) + (0x0200))
#define SOC_G3D_SHADER_PWRTRANS_HI_ADDR(base) ((base) + (0x0204))
#define SOC_G3D_TILER_PWRTRANS_LO_ADDR(base) ((base) + (0x0210))
#define SOC_G3D_TILER_PWRTRANS_HI_ADDR(base) ((base) + (0x0214))
#define SOC_G3D_L2_PWRTRANS_LO_ADDR(base) ((base) + (0x0220))
#define SOC_G3D_L2_PWRTRANS_HI_ADDR(base) ((base) + (0x0224))
#define SOC_G3D_SHADER_PWRACTIVE_LO_ADDR(base) ((base) + (0x0240))
#define SOC_G3D_SHADER_PWRACTIVE_HI_ADDR(base) ((base) + (0x0244))
#define SOC_G3D_TILER_PWRACTIVE_LO_ADDR(base) ((base) + (0x0250))
#define SOC_G3D_TILER_PWRACTIVE_HI_ADDR(base) ((base) + (0x0254))
#define SOC_G3D_L2_PWRACTIVE_LO_ADDR(base) ((base) + (0x0260))
#define SOC_G3D_L2_PWRACTIVE_HI_ADDR(base) ((base) + (0x0264))
#define SOC_G3D_REV_ID_ADDR(base) ((base) + (0x0280))
#define SOC_G3D_JM_CONFIG_ADDR(base) ((base) + (0x0F00))
#define SOC_G3D_SHADER_CONFIG_ADDR(base) ((base) + (0x0F04))
#define SOC_G3D_TILER_CONFIG_ADDR(base) ((base) + (0x0F08))
#define SOC_G3D_L2_MMU_CONFIG_ADDR(base) ((base) + (0x0F0C))
#define SOC_G3D_JOB_IRQ_RAWSTAT_ADDR(base) ((base) + (0x1000))
#define SOC_G3D_JOB_IRQ_CLEAR_ADDR(base) ((base) + (0x1004))
#define SOC_G3D_JOB_IRQ_MASK_ADDR(base) ((base) + (0x1008))
#define SOC_G3D_JOB_IRQ_STATUS_ADDR(base) ((base) + (0x100C))
#define SOC_G3D_JOB_IRQ_JS_STATE_ADDR(base) ((base) + (0x1010))
#define SOC_G3D_JOB_IRQ_THROTTLE_ADDR(base) ((base) + (0x1014))
#define SOC_G3D_JS0_HEAD_LO_ADDR(base) ((base) + (0x1800))
#define SOC_G3D_JS0_HEAD_HI_ADDR(base) ((base) + (0x1804))
#define SOC_G3D_JS0_TAIL_LO_ADDR(base) ((base) + (0x1808))
#define SOC_G3D_JS0_TAIL_HI_ADDR(base) ((base) + (0x180C))
#define SOC_G3D_JS0_AFFINITY_LO_ADDR(base) ((base) + (0x1810))
#define SOC_G3D_JS0_AFFINITY_HI_ADDR(base) ((base) + (0x1814))
#define SOC_G3D_JS0_CONFIG_ADDR(base) ((base) + (0x1818))
#define SOC_G3D_JS0_COMMAND_ADDR(base) ((base) + (0x1820))
#define SOC_G3D_JS0_STATUS_ADDR(base) ((base) + (0x1824))
#define SOC_G3D_JS0_HEAD_NEXT_LO_ADDR(base) ((base) + (0x1840))
#define SOC_G3D_JS0_HEAD_NEXT_HI_ADDR(base) ((base) + (0x1844))
#define SOC_G3D_JS0_AFFINITY_NEXT_LO_ADDR(base) ((base) + (0x1850))
#define SOC_G3D_JS0_AFFINITY_NEXT_HI_ADDR(base) ((base) + (0x1854))
#define SOC_G3D_JS0_CONFIG_NEXT_ADDR(base) ((base) + (0x1858))
#define SOC_G3D_JS0_COMMAND_NEXT_ADDR(base) ((base) + (0x1860))
#define SOC_G3D_JS1_HEAD_LO_ADDR(base) ((base) + (0x1880))
#define SOC_G3D_JS1_HEAD_HI_ADDR(base) ((base) + (0x1884))
#define SOC_G3D_JS1_TAIL_LO_ADDR(base) ((base) + (0x1888))
#define SOC_G3D_JS1_TAIL_HI_ADDR(base) ((base) + (0x188C))
#define SOC_G3D_JS1_AFFINITY_LO_ADDR(base) ((base) + (0x1890))
#define SOC_G3D_JS1_AFFINITY_HI_ADDR(base) ((base) + (0x1894))
#define SOC_G3D_JS1_CONFIG_ADDR(base) ((base) + (0x1898))
#define SOC_G3D_JS1_COMMAND_ADDR(base) ((base) + (0x18A0))
#define SOC_G3D_JS1_STATUS_ADDR(base) ((base) + (0x18A4))
#define SOC_G3D_JS1_HEAD_NEXT_LO_ADDR(base) ((base) + (0x18C0))
#define SOC_G3D_JS1_HEAD_NEXT_HI_ADDR(base) ((base) + (0x18C4))
#define SOC_G3D_JS1_AFFINITY_NEXT_LO_ADDR(base) ((base) + (0x18D0))
#define SOC_G3D_JS1_AFFINITY_NEXT_HI_ADDR(base) ((base) + (0x18D4))
#define SOC_G3D_JS1_CONFIG_NEXT_ADDR(base) ((base) + (0x18D8))
#define SOC_G3D_JS1_COMMAND_NEXT_ADDR(base) ((base) + (0x18E0))
#define SOC_G3D_JS2_HEAD_LO_ADDR(base) ((base) + (0x1900))
#define SOC_G3D_JS2_HEAD_HI_ADDR(base) ((base) + (0x1904))
#define SOC_G3D_JS2_TAIL_LO_ADDR(base) ((base) + (0x1908))
#define SOC_G3D_JS2_TAIL_HI_ADDR(base) ((base) + (0x190C))
#define SOC_G3D_JS2_AFFINITY_LO_ADDR(base) ((base) + (0x1910))
#define SOC_G3D_JS2_AFFINITY_HI_ADDR(base) ((base) + (0x1914))
#define SOC_G3D_JS2_CONFIG_ADDR(base) ((base) + (0x1918))
#define SOC_G3D_JS2_COMMAND_ADDR(base) ((base) + (0x1920))
#define SOC_G3D_JS2_STATUS_ADDR(base) ((base) + (0x1924))
#define SOC_G3D_JS2_HEAD_NEXT_LO_ADDR(base) ((base) + (0x1940))
#define SOC_G3D_JS2_HEAD_NEXT_HI_ADDR(base) ((base) + (0x1944))
#define SOC_G3D_JS2_AFFINITY_NEXT_LO_ADDR(base) ((base) + (0x1950))
#define SOC_G3D_JS2_AFFINITY_NEXT_HI_ADDR(base) ((base) + (0x1954))
#define SOC_G3D_JS2_CONFIG_NEXT_ADDR(base) ((base) + (0x1958))
#define SOC_G3D_JS2_COMMAND_NEXT_ADDR(base) ((base) + (0x1960))
#define SOC_G3D_MMU_IRQ_RAWSTAT_ADDR(base) ((base) + (0x2000))
#define SOC_G3D_MMU_IRQ_CLEAR_ADDR(base) ((base) + (0x2004))
#define SOC_G3D_MMU_IRQ_MASK_ADDR(base) ((base) + (0x2008))
#define SOC_G3D_MMU_IRQ_STATUS_ADDR(base) ((base) + (0x200C))
#define SOC_G3D_AS0_TRANSTAB_LO_ADDR(base) ((base) + (0x2400))
#define SOC_G3D_AS0_TRANSTAB_HI_ADDR(base) ((base) + (0x2404))
#define SOC_G3D_AS0_MEMATTR_LO_ADDR(base) ((base) + (0x2408))
#define SOC_G3D_AS0_MEMATTR_HI_ADDR(base) ((base) + (0x240C))
#define SOC_G3D_AS0_LOCKADDR_LO_ADDR(base) ((base) + (0x2410))
#define SOC_G3D_AS0_LOCKADDR_HI_ADDR(base) ((base) + (0x2414))
#define SOC_G3D_AS0_COMMAND_ADDR(base) ((base) + (0x2418))
#define SOC_G3D_AS0_FAULTSTATUS_ADDR(base) ((base) + (0x241C))
#define SOC_G3D_AS0_FAULTADDRESS_LO_ADDR(base) ((base) + (0x2420))
#define SOC_G3D_AS0_FAULTADDRESS_HI_ADDR(base) ((base) + (0x2424))
#define SOC_G3D_AS0_STATUS_ADDR(base) ((base) + (0x2428))
#define SOC_G3D_AS1_TRANSTAB_LO_ADDR(base) ((base) + (0x2440))
#define SOC_G3D_AS1_TRANSTAB_HI_ADDR(base) ((base) + (0x2444))
#define SOC_G3D_AS1_MEMATTR_LO_ADDR(base) ((base) + (0x2448))
#define SOC_G3D_AS1_MEMATTR_HI_ADDR(base) ((base) + (0x244C))
#define SOC_G3D_AS1_LOCKADDR_LO_ADDR(base) ((base) + (0x2450))
#define SOC_G3D_AS1_LOCKADDR_HI_ADDR(base) ((base) + (0x2454))
#define SOC_G3D_AS1_COMMAND_ADDR(base) ((base) + (0x2458))
#define SOC_G3D_AS1_FAULTSTATUS_ADDR(base) ((base) + (0x245C))
#define SOC_G3D_AS1_FAULTADDRESS_LO_ADDR(base) ((base) + (0x2460))
#define SOC_G3D_AS1_FAULTADDRESS_HI_ADDR(base) ((base) + (0x2464))
#define SOC_G3D_AS1_STATUS_ADDR(base) ((base) + (0x2468))
#define SOC_G3D_AS2_TRANSTAB_LO_ADDR(base) ((base) + (0x2480))
#define SOC_G3D_AS2_TRANSTAB_HI_ADDR(base) ((base) + (0x2484))
#define SOC_G3D_AS2_MEMATTR_LO_ADDR(base) ((base) + (0x2488))
#define SOC_G3D_AS2_MEMATTR_HI_ADDR(base) ((base) + (0x248C))
#define SOC_G3D_AS2_LOCKADDR_LO_ADDR(base) ((base) + (0x2490))
#define SOC_G3D_AS2_LOCKADDR_HI_ADDR(base) ((base) + (0x2494))
#define SOC_G3D_AS2_COMMAND_ADDR(base) ((base) + (0x2498))
#define SOC_G3D_AS2_FAULTSTATUS_ADDR(base) ((base) + (0x249C))
#define SOC_G3D_AS2_FAULTADDRESS_LO_ADDR(base) ((base) + (0x24A0))
#define SOC_G3D_AS2_FAULTADDRESS_HI_ADDR(base) ((base) + (0x24A4))
#define SOC_G3D_AS2_STATUS_ADDR(base) ((base) + (0x24A8))
#define SOC_G3D_AS3_TRANSTAB_LO_ADDR(base) ((base) + (0x24C0))
#define SOC_G3D_AS3_TRANSTAB_HI_ADDR(base) ((base) + (0x24C4))
#define SOC_G3D_AS3_MEMATTR_LO_ADDR(base) ((base) + (0x24C8))
#define SOC_G3D_AS3_MEMATTR_HI_ADDR(base) ((base) + (0x24CC))
#define SOC_G3D_AS3_LOCKADDR_LO_ADDR(base) ((base) + (0x24D0))
#define SOC_G3D_AS3_LOCKADDR_HI_ADDR(base) ((base) + (0x24D4))
#define SOC_G3D_AS3_COMMAND_ADDR(base) ((base) + (0x24D8))
#define SOC_G3D_AS3_FAULTSTATUS_ADDR(base) ((base) + (0x24DC))
#define SOC_G3D_AS3_FAULTADDRESS_LO_ADDR(base) ((base) + (0x24E0))
#define SOC_G3D_AS3_FAULTADDRESS_HI_ADDR(base) ((base) + (0x24E4))
#define SOC_G3D_AS3_STATUS_ADDR(base) ((base) + (0x24E8))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int version_status : 4;
        unsigned int version_minor : 8;
        unsigned int version_major : 4;
        unsigned int product_id : 16;
    } reg;
} SOC_G3D_GPU_ID_UNION;
#endif
#define SOC_G3D_GPU_ID_version_status_START (0)
#define SOC_G3D_GPU_ID_version_status_END (3)
#define SOC_G3D_GPU_ID_version_minor_START (4)
#define SOC_G3D_GPU_ID_version_minor_END (11)
#define SOC_G3D_GPU_ID_version_major_START (12)
#define SOC_G3D_GPU_ID_version_major_END (15)
#define SOC_G3D_GPU_ID_product_id_START (16)
#define SOC_G3D_GPU_ID_product_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int line_size : 8;
        unsigned int associativity : 8;
        unsigned int cache_size : 8;
        unsigned int external_bus_width : 8;
    } reg;
} SOC_G3D_L2_FEATURES_UNION;
#endif
#define SOC_G3D_L2_FEATURES_line_size_START (0)
#define SOC_G3D_L2_FEATURES_line_size_END (7)
#define SOC_G3D_L2_FEATURES_associativity_START (8)
#define SOC_G3D_L2_FEATURES_associativity_END (15)
#define SOC_G3D_L2_FEATURES_cache_size_START (16)
#define SOC_G3D_L2_FEATURES_cache_size_END (23)
#define SOC_G3D_L2_FEATURES_external_bus_width_START (24)
#define SOC_G3D_L2_FEATURES_external_bus_width_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bin_size : 6;
        unsigned int reserved_0 : 2;
        unsigned int max_active_levels : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_G3D_TILER_FEATURES_UNION;
#endif
#define SOC_G3D_TILER_FEATURES_bin_size_START (0)
#define SOC_G3D_TILER_FEATURES_bin_size_END (5)
#define SOC_G3D_TILER_FEATURES_max_active_levels_START (8)
#define SOC_G3D_TILER_FEATURES_max_active_levels_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int COHERENT_CORE_GROUP : 1;
        unsigned int COHERENT_SUPERGROUP : 1;
        unsigned int reserved_0 : 6;
        unsigned int l2_slices : 4;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_G3D_MEM_FEATURES_UNION;
#endif
#define SOC_G3D_MEM_FEATURES_COHERENT_CORE_GROUP_START (0)
#define SOC_G3D_MEM_FEATURES_COHERENT_CORE_GROUP_END (0)
#define SOC_G3D_MEM_FEATURES_COHERENT_SUPERGROUP_START (1)
#define SOC_G3D_MEM_FEATURES_COHERENT_SUPERGROUP_END (1)
#define SOC_G3D_MEM_FEATURES_l2_slices_START (8)
#define SOC_G3D_MEM_FEATURES_l2_slices_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int va_bits : 8;
        unsigned int pa_bits : 8;
        unsigned int mmu_features : 16;
    } reg;
} SOC_G3D_MMU_FEATURES_UNION;
#endif
#define SOC_G3D_MMU_FEATURES_va_bits_START (0)
#define SOC_G3D_MMU_FEATURES_va_bits_END (7)
#define SOC_G3D_MMU_FEATURES_pa_bits_START (8)
#define SOC_G3D_MMU_FEATURES_pa_bits_END (15)
#define SOC_G3D_MMU_FEATURES_mmu_features_START (16)
#define SOC_G3D_MMU_FEATURES_mmu_features_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as_present_low : 8;
        unsigned int as_present : 24;
    } reg;
} SOC_G3D_AS_PRESENT_UNION;
#endif
#define SOC_G3D_AS_PRESENT_as_present_low_START (0)
#define SOC_G3D_AS_PRESENT_as_present_low_END (7)
#define SOC_G3D_AS_PRESENT_as_present_START (8)
#define SOC_G3D_AS_PRESENT_as_present_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js_present_low : 4;
        unsigned int js_present : 28;
    } reg;
} SOC_G3D_JS_PRESENT_UNION;
#endif
#define SOC_G3D_JS_PRESENT_js_present_low_START (0)
#define SOC_G3D_JS_PRESENT_js_present_low_END (3)
#define SOC_G3D_JS_PRESENT_js_present_START (4)
#define SOC_G3D_JS_PRESENT_js_present_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpu_fault : 1;
        unsigned int reserved_0 : 6;
        unsigned int multi_gpu_fault : 1;
        unsigned int reset_completed : 1;
        unsigned int power_change_single : 1;
        unsigned int power_change_all : 1;
        unsigned int reserved_1 : 5;
        unsigned int prfcnt_sample_complete : 1;
        unsigned int clean_cache_completed : 1;
        unsigned int reserved_2 : 14;
    } reg;
} SOC_G3D_GPU_IRQ_RAWSTAT_UNION;
#endif
#define SOC_G3D_GPU_IRQ_RAWSTAT_gpu_fault_START (0)
#define SOC_G3D_GPU_IRQ_RAWSTAT_gpu_fault_END (0)
#define SOC_G3D_GPU_IRQ_RAWSTAT_multi_gpu_fault_START (7)
#define SOC_G3D_GPU_IRQ_RAWSTAT_multi_gpu_fault_END (7)
#define SOC_G3D_GPU_IRQ_RAWSTAT_reset_completed_START (8)
#define SOC_G3D_GPU_IRQ_RAWSTAT_reset_completed_END (8)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_single_START (9)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_single_END (9)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_all_START (10)
#define SOC_G3D_GPU_IRQ_RAWSTAT_power_change_all_END (10)
#define SOC_G3D_GPU_IRQ_RAWSTAT_prfcnt_sample_complete_START (16)
#define SOC_G3D_GPU_IRQ_RAWSTAT_prfcnt_sample_complete_END (16)
#define SOC_G3D_GPU_IRQ_RAWSTAT_clean_cache_completed_START (17)
#define SOC_G3D_GPU_IRQ_RAWSTAT_clean_cache_completed_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpu_fault : 1;
        unsigned int reserved_0 : 6;
        unsigned int multi_gpu_fault : 1;
        unsigned int reset_completed : 1;
        unsigned int power_change_single : 1;
        unsigned int power_change_all : 1;
        unsigned int reserved_1 : 5;
        unsigned int prfcnt_sample_complete : 1;
        unsigned int clean_cache_completed : 1;
        unsigned int reserved_2 : 14;
    } reg;
} SOC_G3D_GPU_IRQ_CLEAR_UNION;
#endif
#define SOC_G3D_GPU_IRQ_CLEAR_gpu_fault_START (0)
#define SOC_G3D_GPU_IRQ_CLEAR_gpu_fault_END (0)
#define SOC_G3D_GPU_IRQ_CLEAR_multi_gpu_fault_START (7)
#define SOC_G3D_GPU_IRQ_CLEAR_multi_gpu_fault_END (7)
#define SOC_G3D_GPU_IRQ_CLEAR_reset_completed_START (8)
#define SOC_G3D_GPU_IRQ_CLEAR_reset_completed_END (8)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_single_START (9)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_single_END (9)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_all_START (10)
#define SOC_G3D_GPU_IRQ_CLEAR_power_change_all_END (10)
#define SOC_G3D_GPU_IRQ_CLEAR_prfcnt_sample_complete_START (16)
#define SOC_G3D_GPU_IRQ_CLEAR_prfcnt_sample_complete_END (16)
#define SOC_G3D_GPU_IRQ_CLEAR_clean_cache_completed_START (17)
#define SOC_G3D_GPU_IRQ_CLEAR_clean_cache_completed_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpu_fault : 1;
        unsigned int reserved_0 : 6;
        unsigned int multi_gpu_fault : 1;
        unsigned int reset_completed : 1;
        unsigned int power_change_single : 1;
        unsigned int power_change_all : 1;
        unsigned int reserved_1 : 5;
        unsigned int prfcnt_sample_complete : 1;
        unsigned int clean_cache_completed : 1;
        unsigned int reserved_2 : 14;
    } reg;
} SOC_G3D_GPU_IRQ_MASK_UNION;
#endif
#define SOC_G3D_GPU_IRQ_MASK_gpu_fault_START (0)
#define SOC_G3D_GPU_IRQ_MASK_gpu_fault_END (0)
#define SOC_G3D_GPU_IRQ_MASK_multi_gpu_fault_START (7)
#define SOC_G3D_GPU_IRQ_MASK_multi_gpu_fault_END (7)
#define SOC_G3D_GPU_IRQ_MASK_reset_completed_START (8)
#define SOC_G3D_GPU_IRQ_MASK_reset_completed_END (8)
#define SOC_G3D_GPU_IRQ_MASK_power_change_single_START (9)
#define SOC_G3D_GPU_IRQ_MASK_power_change_single_END (9)
#define SOC_G3D_GPU_IRQ_MASK_power_change_all_START (10)
#define SOC_G3D_GPU_IRQ_MASK_power_change_all_END (10)
#define SOC_G3D_GPU_IRQ_MASK_prfcnt_sample_complete_START (16)
#define SOC_G3D_GPU_IRQ_MASK_prfcnt_sample_complete_END (16)
#define SOC_G3D_GPU_IRQ_MASK_clean_cache_completed_START (17)
#define SOC_G3D_GPU_IRQ_MASK_clean_cache_completed_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpu_fault : 1;
        unsigned int reserved_0 : 6;
        unsigned int multi_gpu_fault : 1;
        unsigned int reset_completed : 1;
        unsigned int power_change_single : 1;
        unsigned int power_change_all : 1;
        unsigned int reserved_1 : 5;
        unsigned int prfcnt_sample_complete : 1;
        unsigned int clean_cache_completed : 1;
        unsigned int reserved_2 : 14;
    } reg;
} SOC_G3D_GPU_IRQ_STATUS_UNION;
#endif
#define SOC_G3D_GPU_IRQ_STATUS_gpu_fault_START (0)
#define SOC_G3D_GPU_IRQ_STATUS_gpu_fault_END (0)
#define SOC_G3D_GPU_IRQ_STATUS_multi_gpu_fault_START (7)
#define SOC_G3D_GPU_IRQ_STATUS_multi_gpu_fault_END (7)
#define SOC_G3D_GPU_IRQ_STATUS_reset_completed_START (8)
#define SOC_G3D_GPU_IRQ_STATUS_reset_completed_END (8)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_single_START (9)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_single_END (9)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_all_START (10)
#define SOC_G3D_GPU_IRQ_STATUS_power_change_all_END (10)
#define SOC_G3D_GPU_IRQ_STATUS_prfcnt_sample_complete_START (16)
#define SOC_G3D_GPU_IRQ_STATUS_prfcnt_sample_complete_END (16)
#define SOC_G3D_GPU_IRQ_STATUS_clean_cache_completed_START (17)
#define SOC_G3D_GPU_IRQ_STATUS_clean_cache_completed_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 1;
        unsigned int soft_reset : 1;
        unsigned int hard_reset : 1;
        unsigned int prfcnt_clear : 1;
        unsigned int prfcnt_sample : 1;
        unsigned int cycle_count_start : 1;
        unsigned int cycle_count_stop : 1;
        unsigned int clean_caches : 1;
        unsigned int clean_inv_caches : 1;
        unsigned int gpu_command : 23;
    } reg;
} SOC_G3D_GPU_COMMAND_UNION;
#endif
#define SOC_G3D_GPU_COMMAND_soft_reset_START (1)
#define SOC_G3D_GPU_COMMAND_soft_reset_END (1)
#define SOC_G3D_GPU_COMMAND_hard_reset_START (2)
#define SOC_G3D_GPU_COMMAND_hard_reset_END (2)
#define SOC_G3D_GPU_COMMAND_prfcnt_clear_START (3)
#define SOC_G3D_GPU_COMMAND_prfcnt_clear_END (3)
#define SOC_G3D_GPU_COMMAND_prfcnt_sample_START (4)
#define SOC_G3D_GPU_COMMAND_prfcnt_sample_END (4)
#define SOC_G3D_GPU_COMMAND_cycle_count_start_START (5)
#define SOC_G3D_GPU_COMMAND_cycle_count_start_END (5)
#define SOC_G3D_GPU_COMMAND_cycle_count_stop_START (6)
#define SOC_G3D_GPU_COMMAND_cycle_count_stop_END (6)
#define SOC_G3D_GPU_COMMAND_clean_caches_START (7)
#define SOC_G3D_GPU_COMMAND_clean_caches_END (7)
#define SOC_G3D_GPU_COMMAND_clean_inv_caches_START (8)
#define SOC_G3D_GPU_COMMAND_clean_inv_caches_END (8)
#define SOC_G3D_GPU_COMMAND_gpu_command_START (9)
#define SOC_G3D_GPU_COMMAND_gpu_command_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpu_active : 1;
        unsigned int pwr_active : 1;
        unsigned int prfcnt_active : 1;
        unsigned int job_active : 1;
        unsigned int page_fault : 1;
        unsigned int irq_active : 1;
        unsigned int cycle_count_active : 1;
        unsigned int gpu_status : 25;
    } reg;
} SOC_G3D_GPU_STATUS_UNION;
#endif
#define SOC_G3D_GPU_STATUS_gpu_active_START (0)
#define SOC_G3D_GPU_STATUS_gpu_active_END (0)
#define SOC_G3D_GPU_STATUS_pwr_active_START (1)
#define SOC_G3D_GPU_STATUS_pwr_active_END (1)
#define SOC_G3D_GPU_STATUS_prfcnt_active_START (2)
#define SOC_G3D_GPU_STATUS_prfcnt_active_END (2)
#define SOC_G3D_GPU_STATUS_job_active_START (3)
#define SOC_G3D_GPU_STATUS_job_active_END (3)
#define SOC_G3D_GPU_STATUS_page_fault_START (4)
#define SOC_G3D_GPU_STATUS_page_fault_END (4)
#define SOC_G3D_GPU_STATUS_irq_active_START (5)
#define SOC_G3D_GPU_STATUS_irq_active_END (5)
#define SOC_G3D_GPU_STATUS_cycle_count_active_START (6)
#define SOC_G3D_GPU_STATUS_cycle_count_active_END (6)
#define SOC_G3D_GPU_STATUS_gpu_status_START (7)
#define SOC_G3D_GPU_STATUS_gpu_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int exception_type : 8;
        unsigned int access_type : 2;
        unsigned int gpu_faultstatus : 22;
    } reg;
} SOC_G3D_GPU_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_GPU_FAULTSTATUS_exception_type_START (0)
#define SOC_G3D_GPU_FAULTSTATUS_exception_type_END (7)
#define SOC_G3D_GPU_FAULTSTATUS_access_type_START (8)
#define SOC_G3D_GPU_FAULTSTATUS_access_type_END (9)
#define SOC_G3D_GPU_FAULTSTATUS_gpu_faultstatus_START (10)
#define SOC_G3D_GPU_FAULTSTATUS_gpu_faultstatus_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpu_faultaddress_lo : 32;
    } reg;
} SOC_G3D_GPU_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_GPU_FAULTADDRESS_LO_gpu_faultaddress_lo_START (0)
#define SOC_G3D_GPU_FAULTADDRESS_LO_gpu_faultaddress_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpu_faultaddress_hi : 32;
    } reg;
} SOC_G3D_GPU_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_GPU_FAULTADDRESS_HI_gpu_faultaddress_hi_START (0)
#define SOC_G3D_GPU_FAULTADDRESS_HI_gpu_faultaddress_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwr_key : 32;
    } reg;
} SOC_G3D_PWR_KEY_UNION;
#endif
#define SOC_G3D_PWR_KEY_pwr_key_START (0)
#define SOC_G3D_PWR_KEY_pwr_key_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pwrup_override : 2;
        unsigned int isolate_override : 2;
        unsigned int reset_override : 2;
        unsigned int clken_override : 2;
        unsigned int ack_override : 2;
        unsigned int isolate_ack_override : 2;
        unsigned int reserved_0 : 4;
        unsigned int powertrain_limt : 6;
        unsigned int reserved_1 : 10;
    } reg;
} SOC_G3D_PWR_KEYOVERRIDE0_UNION;
#endif
#define SOC_G3D_PWR_KEYOVERRIDE0_pwrup_override_START (0)
#define SOC_G3D_PWR_KEYOVERRIDE0_pwrup_override_END (1)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_override_START (2)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_override_END (3)
#define SOC_G3D_PWR_KEYOVERRIDE0_reset_override_START (4)
#define SOC_G3D_PWR_KEYOVERRIDE0_reset_override_END (5)
#define SOC_G3D_PWR_KEYOVERRIDE0_clken_override_START (6)
#define SOC_G3D_PWR_KEYOVERRIDE0_clken_override_END (7)
#define SOC_G3D_PWR_KEYOVERRIDE0_ack_override_START (8)
#define SOC_G3D_PWR_KEYOVERRIDE0_ack_override_END (9)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_ack_override_START (10)
#define SOC_G3D_PWR_KEYOVERRIDE0_isolate_ack_override_END (11)
#define SOC_G3D_PWR_KEYOVERRIDE0_powertrain_limt_START (16)
#define SOC_G3D_PWR_KEYOVERRIDE0_powertrain_limt_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_PWR_KEYOVERRIDE1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 8;
        unsigned int prfcnt_base_lo : 24;
    } reg;
} SOC_G3D_PRFCNT_BASE_LO_UNION;
#endif
#define SOC_G3D_PRFCNT_BASE_LO_prfcnt_base_lo_START (8)
#define SOC_G3D_PRFCNT_BASE_LO_prfcnt_base_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int prfcnt_base_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_PRFCNT_BASE_HI_UNION;
#endif
#define SOC_G3D_PRFCNT_BASE_HI_prfcnt_base_hi_START (0)
#define SOC_G3D_PRFCNT_BASE_HI_prfcnt_base_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 2;
        unsigned int address_space : 2;
        unsigned int reserved : 28;
    } reg;
} SOC_G3D_PRFCNT_CONFIG_UNION;
#endif
#define SOC_G3D_PRFCNT_CONFIG_mode_START (0)
#define SOC_G3D_PRFCNT_CONFIG_mode_END (1)
#define SOC_G3D_PRFCNT_CONFIG_address_space_START (2)
#define SOC_G3D_PRFCNT_CONFIG_address_space_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pfrcnt_jm_en : 32;
    } reg;
} SOC_G3D_PRFCNT_JM_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_JM_EN_pfrcnt_jm_en_START (0)
#define SOC_G3D_PRFCNT_JM_EN_pfrcnt_jm_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pfrcnt_shader_en : 32;
    } reg;
} SOC_G3D_PRFCNT_SHADER_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_SHADER_EN_pfrcnt_shader_en_START (0)
#define SOC_G3D_PRFCNT_SHADER_EN_pfrcnt_shader_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pfrcnt_tiler_en : 32;
    } reg;
} SOC_G3D_PRFCNT_TILER_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_TILER_EN_pfrcnt_tiler_en_START (0)
#define SOC_G3D_PRFCNT_TILER_EN_pfrcnt_tiler_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pfrcnt_mmu_en : 32;
    } reg;
} SOC_G3D_PRFCNT_MMU_L2_EN_UNION;
#endif
#define SOC_G3D_PRFCNT_MMU_L2_EN_pfrcnt_mmu_en_START (0)
#define SOC_G3D_PRFCNT_MMU_L2_EN_pfrcnt_mmu_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cycle_count_lo : 32;
    } reg;
} SOC_G3D_CYCLE_COUNT_LO_UNION;
#endif
#define SOC_G3D_CYCLE_COUNT_LO_cycle_count_lo_START (0)
#define SOC_G3D_CYCLE_COUNT_LO_cycle_count_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cycle_count_hi : 32;
    } reg;
} SOC_G3D_CYCLE_COUNT_HI_UNION;
#endif
#define SOC_G3D_CYCLE_COUNT_HI_cycle_count_hi_START (0)
#define SOC_G3D_CYCLE_COUNT_HI_cycle_count_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timestamp_lo : 32;
    } reg;
} SOC_G3D_TIMESTAMP_LO_UNION;
#endif
#define SOC_G3D_TIMESTAMP_LO_timestamp_lo_START (0)
#define SOC_G3D_TIMESTAMP_LO_timestamp_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int timestamp_hi : 32;
    } reg;
} SOC_G3D_TIMESTAMP_HI_UNION;
#endif
#define SOC_G3D_TIMESTAMP_HI_timestamp_hi_START (0)
#define SOC_G3D_TIMESTAMP_HI_timestamp_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thread_max_thread : 32;
    } reg;
} SOC_G3D_THREAD_MAX_THREADS_UNION;
#endif
#define SOC_G3D_THREAD_MAX_THREADS_thread_max_thread_START (0)
#define SOC_G3D_THREAD_MAX_THREADS_thread_max_thread_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thread_max_workgroup : 32;
    } reg;
} SOC_G3D_THREAD_MAX_WORKGROUP_UNION;
#endif
#define SOC_G3D_THREAD_MAX_WORKGROUP_thread_max_workgroup_START (0)
#define SOC_G3D_THREAD_MAX_WORKGROUP_thread_max_workgroup_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int thread_max_barrier_size : 32;
    } reg;
} SOC_G3D_THREAD_MAX_BARRIER_SIZE_UNION;
#endif
#define SOC_G3D_THREAD_MAX_BARRIER_SIZE_thread_max_barrier_size_START (0)
#define SOC_G3D_THREAD_MAX_BARRIER_SIZE_thread_max_barrier_size_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int max_registers : 16;
        unsigned int max_task_queue : 8;
        unsigned int max_thread_group_split : 6;
        unsigned int reserved : 2;
    } reg;
} SOC_G3D_THREAD_FEATURES_UNION;
#endif
#define SOC_G3D_THREAD_FEATURES_max_registers_START (0)
#define SOC_G3D_THREAD_FEATURES_max_registers_END (15)
#define SOC_G3D_THREAD_FEATURES_max_task_queue_START (16)
#define SOC_G3D_THREAD_FEATURES_max_task_queue_END (23)
#define SOC_G3D_THREAD_FEATURES_max_thread_group_split_START (24)
#define SOC_G3D_THREAD_FEATURES_max_thread_group_split_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int texture_features_0 : 32;
    } reg;
} SOC_G3D_TEXTURE_FEATURES_0_UNION;
#endif
#define SOC_G3D_TEXTURE_FEATURES_0_texture_features_0_START (0)
#define SOC_G3D_TEXTURE_FEATURES_0_texture_features_0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int texture_features_1 : 32;
    } reg;
} SOC_G3D_TEXTURE_FEATURES_1_UNION;
#endif
#define SOC_G3D_TEXTURE_FEATURES_1_texture_features_1_START (0)
#define SOC_G3D_TEXTURE_FEATURES_1_texture_features_1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int texture_features_2 : 32;
    } reg;
} SOC_G3D_TEXTURE_FEATURES_2_UNION;
#endif
#define SOC_G3D_TEXTURE_FEATURES_2_texture_features_2_START (0)
#define SOC_G3D_TEXTURE_FEATURES_2_texture_features_2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js0_features : 32;
    } reg;
} SOC_G3D_JS0_FEATURES_UNION;
#endif
#define SOC_G3D_JS0_FEATURES_js0_features_START (0)
#define SOC_G3D_JS0_FEATURES_js0_features_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js1_features : 32;
    } reg;
} SOC_G3D_JS1_FEATURES_UNION;
#endif
#define SOC_G3D_JS1_FEATURES_js1_features_START (0)
#define SOC_G3D_JS1_FEATURES_js1_features_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js2_features : 32;
    } reg;
} SOC_G3D_JS2_FEATURES_UNION;
#endif
#define SOC_G3D_JS2_FEATURES_js2_features_START (0)
#define SOC_G3D_JS2_FEATURES_js2_features_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_present_lo : 32;
    } reg;
} SOC_G3D_SHADER_PRESENT_LO_UNION;
#endif
#define SOC_G3D_SHADER_PRESENT_LO_shader_present_lo_START (0)
#define SOC_G3D_SHADER_PRESENT_LO_shader_present_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_present_hi : 32;
    } reg;
} SOC_G3D_SHADER_PRESENT_HI_UNION;
#endif
#define SOC_G3D_SHADER_PRESENT_HI_shader_present_hi_START (0)
#define SOC_G3D_SHADER_PRESENT_HI_shader_present_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_present_lo : 32;
    } reg;
} SOC_G3D_TILER_PRESENT_LO_UNION;
#endif
#define SOC_G3D_TILER_PRESENT_LO_tiler_present_lo_START (0)
#define SOC_G3D_TILER_PRESENT_LO_tiler_present_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_present_hi : 32;
    } reg;
} SOC_G3D_TILER_PRESENT_HI_UNION;
#endif
#define SOC_G3D_TILER_PRESENT_HI_tiler_present_hi_START (0)
#define SOC_G3D_TILER_PRESENT_HI_tiler_present_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_present_lo : 32;
    } reg;
} SOC_G3D_L2_PRESENT_LO_UNION;
#endif
#define SOC_G3D_L2_PRESENT_LO_l2_present_lo_START (0)
#define SOC_G3D_L2_PRESENT_LO_l2_present_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_present_hi : 32;
    } reg;
} SOC_G3D_L2_PRESENT_HI_UNION;
#endif
#define SOC_G3D_L2_PRESENT_HI_l2_present_hi_START (0)
#define SOC_G3D_L2_PRESENT_HI_l2_present_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_ready_lo : 32;
    } reg;
} SOC_G3D_SHADER_READY_LO_UNION;
#endif
#define SOC_G3D_SHADER_READY_LO_shader_ready_lo_START (0)
#define SOC_G3D_SHADER_READY_LO_shader_ready_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_ready_hi : 32;
    } reg;
} SOC_G3D_SHADER_READY_HI_UNION;
#endif
#define SOC_G3D_SHADER_READY_HI_shader_ready_hi_START (0)
#define SOC_G3D_SHADER_READY_HI_shader_ready_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_ready_lo : 32;
    } reg;
} SOC_G3D_TILER_READY_LO_UNION;
#endif
#define SOC_G3D_TILER_READY_LO_tiler_ready_lo_START (0)
#define SOC_G3D_TILER_READY_LO_tiler_ready_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_ready_hi : 32;
    } reg;
} SOC_G3D_TILER_READY_HI_UNION;
#endif
#define SOC_G3D_TILER_READY_HI_tiler_ready_hi_START (0)
#define SOC_G3D_TILER_READY_HI_tiler_ready_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_ready_lo : 32;
    } reg;
} SOC_G3D_L2_READY_LO_UNION;
#endif
#define SOC_G3D_L2_READY_LO_l2_ready_lo_START (0)
#define SOC_G3D_L2_READY_LO_l2_ready_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_ready_hi : 32;
    } reg;
} SOC_G3D_L2_READY_HI_UNION;
#endif
#define SOC_G3D_L2_READY_HI_l2_ready_hi_START (0)
#define SOC_G3D_L2_READY_HI_l2_ready_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_pwron_lo : 32;
    } reg;
} SOC_G3D_SHADER_PWRON_LO_UNION;
#endif
#define SOC_G3D_SHADER_PWRON_LO_shader_pwron_lo_START (0)
#define SOC_G3D_SHADER_PWRON_LO_shader_pwron_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_pwron_hi : 32;
    } reg;
} SOC_G3D_SHADER_PWRON_HI_UNION;
#endif
#define SOC_G3D_SHADER_PWRON_HI_shader_pwron_hi_START (0)
#define SOC_G3D_SHADER_PWRON_HI_shader_pwron_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_pwron_lo : 32;
    } reg;
} SOC_G3D_TILER_PWRON_LO_UNION;
#endif
#define SOC_G3D_TILER_PWRON_LO_tiler_pwron_lo_START (0)
#define SOC_G3D_TILER_PWRON_LO_tiler_pwron_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_pwron_hi : 32;
    } reg;
} SOC_G3D_TILER_PWRON_HI_UNION;
#endif
#define SOC_G3D_TILER_PWRON_HI_tiler_pwron_hi_START (0)
#define SOC_G3D_TILER_PWRON_HI_tiler_pwron_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_pwron_lo : 32;
    } reg;
} SOC_G3D_L2_PWRON_LO_UNION;
#endif
#define SOC_G3D_L2_PWRON_LO_l2_pwron_lo_START (0)
#define SOC_G3D_L2_PWRON_LO_l2_pwron_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_pwron_hi : 32;
    } reg;
} SOC_G3D_L2_PWRON_HI_UNION;
#endif
#define SOC_G3D_L2_PWRON_HI_l2_pwron_hi_START (0)
#define SOC_G3D_L2_PWRON_HI_l2_pwron_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_pwroff_lo : 32;
    } reg;
} SOC_G3D_SHADER_PWROFF_LO_UNION;
#endif
#define SOC_G3D_SHADER_PWROFF_LO_shader_pwroff_lo_START (0)
#define SOC_G3D_SHADER_PWROFF_LO_shader_pwroff_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_pwroff_hi : 32;
    } reg;
} SOC_G3D_SHADER_PWROFF_HI_UNION;
#endif
#define SOC_G3D_SHADER_PWROFF_HI_shader_pwroff_hi_START (0)
#define SOC_G3D_SHADER_PWROFF_HI_shader_pwroff_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_pwroff_lo : 32;
    } reg;
} SOC_G3D_TILER_PWROFF_LO_UNION;
#endif
#define SOC_G3D_TILER_PWROFF_LO_tiler_pwroff_lo_START (0)
#define SOC_G3D_TILER_PWROFF_LO_tiler_pwroff_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_pwroff_hi : 32;
    } reg;
} SOC_G3D_TILER_PWROFF_HI_UNION;
#endif
#define SOC_G3D_TILER_PWROFF_HI_tiler_pwroff_hi_START (0)
#define SOC_G3D_TILER_PWROFF_HI_tiler_pwroff_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_pwroff_lo : 32;
    } reg;
} SOC_G3D_L2_PWROFF_LO_UNION;
#endif
#define SOC_G3D_L2_PWROFF_LO_l2_pwroff_lo_START (0)
#define SOC_G3D_L2_PWROFF_LO_l2_pwroff_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_pwroff_hi : 32;
    } reg;
} SOC_G3D_L2_PWROFF_HI_UNION;
#endif
#define SOC_G3D_L2_PWROFF_HI_l2_pwroff_hi_START (0)
#define SOC_G3D_L2_PWROFF_HI_l2_pwroff_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_SHADER_PWRTRANS_LO_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_SHADER_PWRTRANS_HI_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_pwrtrans_lo : 32;
    } reg;
} SOC_G3D_TILER_PWRTRANS_LO_UNION;
#endif
#define SOC_G3D_TILER_PWRTRANS_LO_tiler_pwrtrans_lo_START (0)
#define SOC_G3D_TILER_PWRTRANS_LO_tiler_pwrtrans_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_pwrtrans_hi : 32;
    } reg;
} SOC_G3D_TILER_PWRTRANS_HI_UNION;
#endif
#define SOC_G3D_TILER_PWRTRANS_HI_tiler_pwrtrans_hi_START (0)
#define SOC_G3D_TILER_PWRTRANS_HI_tiler_pwrtrans_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_pwrtrans_lo : 32;
    } reg;
} SOC_G3D_L2_PWRTRANS_LO_UNION;
#endif
#define SOC_G3D_L2_PWRTRANS_LO_l2_pwrtrans_lo_START (0)
#define SOC_G3D_L2_PWRTRANS_LO_l2_pwrtrans_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_pwrtrans_hi : 32;
    } reg;
} SOC_G3D_L2_PWRTRANS_HI_UNION;
#endif
#define SOC_G3D_L2_PWRTRANS_HI_l2_pwrtrans_hi_START (0)
#define SOC_G3D_L2_PWRTRANS_HI_l2_pwrtrans_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_pwractive_lo : 32;
    } reg;
} SOC_G3D_SHADER_PWRACTIVE_LO_UNION;
#endif
#define SOC_G3D_SHADER_PWRACTIVE_LO_shader_pwractive_lo_START (0)
#define SOC_G3D_SHADER_PWRACTIVE_LO_shader_pwractive_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int shader_pwractive_hi : 32;
    } reg;
} SOC_G3D_SHADER_PWRACTIVE_HI_UNION;
#endif
#define SOC_G3D_SHADER_PWRACTIVE_HI_shader_pwractive_hi_START (0)
#define SOC_G3D_SHADER_PWRACTIVE_HI_shader_pwractive_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_pwractive_lo : 32;
    } reg;
} SOC_G3D_TILER_PWRACTIVE_LO_UNION;
#endif
#define SOC_G3D_TILER_PWRACTIVE_LO_tiler_pwractive_lo_START (0)
#define SOC_G3D_TILER_PWRACTIVE_LO_tiler_pwractive_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_pwractive_hi : 32;
    } reg;
} SOC_G3D_TILER_PWRACTIVE_HI_UNION;
#endif
#define SOC_G3D_TILER_PWRACTIVE_HI_tiler_pwractive_hi_START (0)
#define SOC_G3D_TILER_PWRACTIVE_HI_tiler_pwractive_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_pwractive_lo : 32;
    } reg;
} SOC_G3D_L2_PWRACTIVE_LO_UNION;
#endif
#define SOC_G3D_L2_PWRACTIVE_LO_l2_pwractive_lo_START (0)
#define SOC_G3D_L2_PWRACTIVE_LO_l2_pwractive_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int l2_pwractive_hi : 32;
    } reg;
} SOC_G3D_L2_PWRACTIVE_HI_UNION;
#endif
#define SOC_G3D_L2_PWRACTIVE_HI_l2_pwractive_hi_START (0)
#define SOC_G3D_L2_PWRACTIVE_HI_l2_pwractive_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rev_id : 32;
    } reg;
} SOC_G3D_REV_ID_UNION;
#endif
#define SOC_G3D_REV_ID_rev_id_START (0)
#define SOC_G3D_REV_ID_rev_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int jc_config : 32;
    } reg;
} SOC_G3D_JM_CONFIG_UNION;
#endif
#define SOC_G3D_JM_CONFIG_jc_config_START (0)
#define SOC_G3D_JM_CONFIG_jc_config_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 3;
        unsigned int all_counters : 1;
        unsigned int shader_config : 28;
    } reg;
} SOC_G3D_SHADER_CONFIG_UNION;
#endif
#define SOC_G3D_SHADER_CONFIG_all_counters_START (3)
#define SOC_G3D_SHADER_CONFIG_all_counters_END (3)
#define SOC_G3D_SHADER_CONFIG_shader_config_START (4)
#define SOC_G3D_SHADER_CONFIG_shader_config_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tiler_config : 32;
    } reg;
} SOC_G3D_TILER_CONFIG_UNION;
#endif
#define SOC_G3D_TILER_CONFIG_tiler_config_START (0)
#define SOC_G3D_TILER_CONFIG_tiler_config_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 24;
        unsigned int limit_external_reads : 2;
        unsigned int limit_external_writes : 2;
        unsigned int l2_mmu_config : 4;
    } reg;
} SOC_G3D_L2_MMU_CONFIG_UNION;
#endif
#define SOC_G3D_L2_MMU_CONFIG_limit_external_reads_START (24)
#define SOC_G3D_L2_MMU_CONFIG_limit_external_reads_END (25)
#define SOC_G3D_L2_MMU_CONFIG_limit_external_writes_START (26)
#define SOC_G3D_L2_MMU_CONFIG_limit_external_writes_END (27)
#define SOC_G3D_L2_MMU_CONFIG_l2_mmu_config_START (28)
#define SOC_G3D_L2_MMU_CONFIG_l2_mmu_config_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int job_done : 3;
        unsigned int reserved_0: 13;
        unsigned int job_fail : 3;
        unsigned int reserved_1: 13;
    } reg;
} SOC_G3D_JOB_IRQ_RAWSTAT_UNION;
#endif
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_done_START (0)
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_done_END (2)
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_fail_START (16)
#define SOC_G3D_JOB_IRQ_RAWSTAT_job_fail_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int job_done : 3;
        unsigned int reserved : 13;
        unsigned int job_fail : 3;
        unsigned int job_irq_clear : 13;
    } reg;
} SOC_G3D_JOB_IRQ_CLEAR_UNION;
#endif
#define SOC_G3D_JOB_IRQ_CLEAR_job_done_START (0)
#define SOC_G3D_JOB_IRQ_CLEAR_job_done_END (2)
#define SOC_G3D_JOB_IRQ_CLEAR_job_fail_START (16)
#define SOC_G3D_JOB_IRQ_CLEAR_job_fail_END (18)
#define SOC_G3D_JOB_IRQ_CLEAR_job_irq_clear_START (19)
#define SOC_G3D_JOB_IRQ_CLEAR_job_irq_clear_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int job_done : 3;
        unsigned int reserved_0: 13;
        unsigned int job_fail : 3;
        unsigned int reserved_1: 13;
    } reg;
} SOC_G3D_JOB_IRQ_MASK_UNION;
#endif
#define SOC_G3D_JOB_IRQ_MASK_job_done_START (0)
#define SOC_G3D_JOB_IRQ_MASK_job_done_END (2)
#define SOC_G3D_JOB_IRQ_MASK_job_fail_START (16)
#define SOC_G3D_JOB_IRQ_MASK_job_fail_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int job_done : 3;
        unsigned int reserved_0: 13;
        unsigned int job_fail : 3;
        unsigned int reserved_1: 13;
    } reg;
} SOC_G3D_JOB_IRQ_STATUS_UNION;
#endif
#define SOC_G3D_JOB_IRQ_STATUS_job_done_START (0)
#define SOC_G3D_JOB_IRQ_STATUS_job_done_END (2)
#define SOC_G3D_JOB_IRQ_STATUS_job_fail_START (16)
#define SOC_G3D_JOB_IRQ_STATUS_job_fail_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int job_active_n : 16;
        unsigned int job_next_active_n : 16;
    } reg;
} SOC_G3D_JOB_IRQ_JS_STATE_UNION;
#endif
#define SOC_G3D_JOB_IRQ_JS_STATE_job_active_n_START (0)
#define SOC_G3D_JOB_IRQ_JS_STATE_job_active_n_END (15)
#define SOC_G3D_JOB_IRQ_JS_STATE_job_next_active_n_START (16)
#define SOC_G3D_JOB_IRQ_JS_STATE_job_next_active_n_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int job_irq_throttle : 32;
    } reg;
} SOC_G3D_JOB_IRQ_THROTTLE_UNION;
#endif
#define SOC_G3D_JOB_IRQ_THROTTLE_job_irq_throttle_START (0)
#define SOC_G3D_JOB_IRQ_THROTTLE_job_irq_throttle_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 6;
        unsigned int js0_head_lo : 26;
    } reg;
} SOC_G3D_JS0_HEAD_LO_UNION;
#endif
#define SOC_G3D_JS0_HEAD_LO_js0_head_lo_START (6)
#define SOC_G3D_JS0_HEAD_LO_js0_head_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js0_head_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_JS0_HEAD_HI_UNION;
#endif
#define SOC_G3D_JS0_HEAD_HI_js0_head_hi_START (0)
#define SOC_G3D_JS0_HEAD_HI_js0_head_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 6;
        unsigned int js0_tail_lo : 26;
    } reg;
} SOC_G3D_JS0_TAIL_LO_UNION;
#endif
#define SOC_G3D_JS0_TAIL_LO_js0_tail_lo_START (6)
#define SOC_G3D_JS0_TAIL_LO_js0_tail_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js0_tail_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_JS0_TAIL_HI_UNION;
#endif
#define SOC_G3D_JS0_TAIL_HI_js0_tail_hi_START (0)
#define SOC_G3D_JS0_TAIL_HI_js0_tail_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js0_affinity_lo : 32;
    } reg;
} SOC_G3D_JS0_AFFINITY_LO_UNION;
#endif
#define SOC_G3D_JS0_AFFINITY_LO_js0_affinity_lo_START (0)
#define SOC_G3D_JS0_AFFINITY_LO_js0_affinity_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js0_affinity_hi : 32;
    } reg;
} SOC_G3D_JS0_AFFINITY_HI_UNION;
#endif
#define SOC_G3D_JS0_AFFINITY_HI_js0_affinity_hi_START (0)
#define SOC_G3D_JS0_AFFINITY_HI_js0_affinity_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_space : 4;
        unsigned int reserved_0 : 4;
        unsigned int start_flush : 2;
        unsigned int start_mmu : 1;
        unsigned int reserved_1 : 1;
        unsigned int end_flush : 2;
        unsigned int reserved_2 : 18;
    } reg;
} SOC_G3D_JS0_CONFIG_UNION;
#endif
#define SOC_G3D_JS0_CONFIG_address_space_START (0)
#define SOC_G3D_JS0_CONFIG_address_space_END (3)
#define SOC_G3D_JS0_CONFIG_start_flush_START (8)
#define SOC_G3D_JS0_CONFIG_start_flush_END (9)
#define SOC_G3D_JS0_CONFIG_start_mmu_START (10)
#define SOC_G3D_JS0_CONFIG_start_mmu_END (10)
#define SOC_G3D_JS0_CONFIG_end_flush_START (12)
#define SOC_G3D_JS0_CONFIG_end_flush_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nop : 1;
        unsigned int start : 1;
        unsigned int soft_stop : 1;
        unsigned int hard_stop : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_G3D_JS0_COMMAND_UNION;
#endif
#define SOC_G3D_JS0_COMMAND_nop_START (0)
#define SOC_G3D_JS0_COMMAND_nop_END (0)
#define SOC_G3D_JS0_COMMAND_start_START (1)
#define SOC_G3D_JS0_COMMAND_start_END (1)
#define SOC_G3D_JS0_COMMAND_soft_stop_START (2)
#define SOC_G3D_JS0_COMMAND_soft_stop_END (2)
#define SOC_G3D_JS0_COMMAND_hard_stop_START (3)
#define SOC_G3D_JS0_COMMAND_hard_stop_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int exception_type : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_G3D_JS0_STATUS_UNION;
#endif
#define SOC_G3D_JS0_STATUS_exception_type_START (0)
#define SOC_G3D_JS0_STATUS_exception_type_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js0_head_next_lo : 32;
    } reg;
} SOC_G3D_JS0_HEAD_NEXT_LO_UNION;
#endif
#define SOC_G3D_JS0_HEAD_NEXT_LO_js0_head_next_lo_START (0)
#define SOC_G3D_JS0_HEAD_NEXT_LO_js0_head_next_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js0_head_next_hi : 32;
    } reg;
} SOC_G3D_JS0_HEAD_NEXT_HI_UNION;
#endif
#define SOC_G3D_JS0_HEAD_NEXT_HI_js0_head_next_hi_START (0)
#define SOC_G3D_JS0_HEAD_NEXT_HI_js0_head_next_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_JS0_AFFINITY_NEXT_LO_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_JS0_AFFINITY_NEXT_HI_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_space : 4;
        unsigned int reserved_0 : 4;
        unsigned int start_flush : 2;
        unsigned int start_mmu : 1;
        unsigned int reserved_1 : 1;
        unsigned int end_flush : 2;
        unsigned int reserved_2 : 18;
    } reg;
} SOC_G3D_JS0_CONFIG_NEXT_UNION;
#endif
#define SOC_G3D_JS0_CONFIG_NEXT_address_space_START (0)
#define SOC_G3D_JS0_CONFIG_NEXT_address_space_END (3)
#define SOC_G3D_JS0_CONFIG_NEXT_start_flush_START (8)
#define SOC_G3D_JS0_CONFIG_NEXT_start_flush_END (9)
#define SOC_G3D_JS0_CONFIG_NEXT_start_mmu_START (10)
#define SOC_G3D_JS0_CONFIG_NEXT_start_mmu_END (10)
#define SOC_G3D_JS0_CONFIG_NEXT_end_flush_START (12)
#define SOC_G3D_JS0_CONFIG_NEXT_end_flush_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_JS0_COMMAND_NEXT_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 6;
        unsigned int js1_head_lo : 26;
    } reg;
} SOC_G3D_JS1_HEAD_LO_UNION;
#endif
#define SOC_G3D_JS1_HEAD_LO_js1_head_lo_START (6)
#define SOC_G3D_JS1_HEAD_LO_js1_head_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js1_head_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_JS1_HEAD_HI_UNION;
#endif
#define SOC_G3D_JS1_HEAD_HI_js1_head_hi_START (0)
#define SOC_G3D_JS1_HEAD_HI_js1_head_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 6;
        unsigned int js1_tail_lo : 26;
    } reg;
} SOC_G3D_JS1_TAIL_LO_UNION;
#endif
#define SOC_G3D_JS1_TAIL_LO_js1_tail_lo_START (6)
#define SOC_G3D_JS1_TAIL_LO_js1_tail_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js1_tail_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_JS1_TAIL_HI_UNION;
#endif
#define SOC_G3D_JS1_TAIL_HI_js1_tail_hi_START (0)
#define SOC_G3D_JS1_TAIL_HI_js1_tail_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js1_affinity_lo : 32;
    } reg;
} SOC_G3D_JS1_AFFINITY_LO_UNION;
#endif
#define SOC_G3D_JS1_AFFINITY_LO_js1_affinity_lo_START (0)
#define SOC_G3D_JS1_AFFINITY_LO_js1_affinity_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js1_affinity_hi : 32;
    } reg;
} SOC_G3D_JS1_AFFINITY_HI_UNION;
#endif
#define SOC_G3D_JS1_AFFINITY_HI_js1_affinity_hi_START (0)
#define SOC_G3D_JS1_AFFINITY_HI_js1_affinity_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_space : 4;
        unsigned int reserved_0 : 4;
        unsigned int start_flush : 2;
        unsigned int start_mmu : 1;
        unsigned int reserved_1 : 1;
        unsigned int end_flush : 2;
        unsigned int reserved_2 : 18;
    } reg;
} SOC_G3D_JS1_CONFIG_UNION;
#endif
#define SOC_G3D_JS1_CONFIG_address_space_START (0)
#define SOC_G3D_JS1_CONFIG_address_space_END (3)
#define SOC_G3D_JS1_CONFIG_start_flush_START (8)
#define SOC_G3D_JS1_CONFIG_start_flush_END (9)
#define SOC_G3D_JS1_CONFIG_start_mmu_START (10)
#define SOC_G3D_JS1_CONFIG_start_mmu_END (10)
#define SOC_G3D_JS1_CONFIG_end_flush_START (12)
#define SOC_G3D_JS1_CONFIG_end_flush_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js1_command : 32;
    } reg;
} SOC_G3D_JS1_COMMAND_UNION;
#endif
#define SOC_G3D_JS1_COMMAND_js1_command_START (0)
#define SOC_G3D_JS1_COMMAND_js1_command_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js1_status : 32;
    } reg;
} SOC_G3D_JS1_STATUS_UNION;
#endif
#define SOC_G3D_JS1_STATUS_js1_status_START (0)
#define SOC_G3D_JS1_STATUS_js1_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js1_head_next_lo : 32;
    } reg;
} SOC_G3D_JS1_HEAD_NEXT_LO_UNION;
#endif
#define SOC_G3D_JS1_HEAD_NEXT_LO_js1_head_next_lo_START (0)
#define SOC_G3D_JS1_HEAD_NEXT_LO_js1_head_next_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js1_head_next_hi : 32;
    } reg;
} SOC_G3D_JS1_HEAD_NEXT_HI_UNION;
#endif
#define SOC_G3D_JS1_HEAD_NEXT_HI_js1_head_next_hi_START (0)
#define SOC_G3D_JS1_HEAD_NEXT_HI_js1_head_next_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_JS1_AFFINITY_NEXT_LO_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_JS1_AFFINITY_NEXT_HI_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_space : 4;
        unsigned int reserved_0 : 4;
        unsigned int start_flush : 2;
        unsigned int start_mmu : 1;
        unsigned int reserved_1 : 1;
        unsigned int end_flush : 2;
        unsigned int reserved_2 : 18;
    } reg;
} SOC_G3D_JS1_CONFIG_NEXT_UNION;
#endif
#define SOC_G3D_JS1_CONFIG_NEXT_address_space_START (0)
#define SOC_G3D_JS1_CONFIG_NEXT_address_space_END (3)
#define SOC_G3D_JS1_CONFIG_NEXT_start_flush_START (8)
#define SOC_G3D_JS1_CONFIG_NEXT_start_flush_END (9)
#define SOC_G3D_JS1_CONFIG_NEXT_start_mmu_START (10)
#define SOC_G3D_JS1_CONFIG_NEXT_start_mmu_END (10)
#define SOC_G3D_JS1_CONFIG_NEXT_end_flush_START (12)
#define SOC_G3D_JS1_CONFIG_NEXT_end_flush_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_JS1_COMMAND_NEXT_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 6;
        unsigned int js2_head_lo : 26;
    } reg;
} SOC_G3D_JS2_HEAD_LO_UNION;
#endif
#define SOC_G3D_JS2_HEAD_LO_js2_head_lo_START (6)
#define SOC_G3D_JS2_HEAD_LO_js2_head_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js2_head_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_JS2_HEAD_HI_UNION;
#endif
#define SOC_G3D_JS2_HEAD_HI_js2_head_hi_START (0)
#define SOC_G3D_JS2_HEAD_HI_js2_head_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 6;
        unsigned int js2_tail_lo : 26;
    } reg;
} SOC_G3D_JS2_TAIL_LO_UNION;
#endif
#define SOC_G3D_JS2_TAIL_LO_js2_tail_lo_START (6)
#define SOC_G3D_JS2_TAIL_LO_js2_tail_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js2_tail_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_JS2_TAIL_HI_UNION;
#endif
#define SOC_G3D_JS2_TAIL_HI_js2_tail_hi_START (0)
#define SOC_G3D_JS2_TAIL_HI_js2_tail_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js2_affinity_lo : 32;
    } reg;
} SOC_G3D_JS2_AFFINITY_LO_UNION;
#endif
#define SOC_G3D_JS2_AFFINITY_LO_js2_affinity_lo_START (0)
#define SOC_G3D_JS2_AFFINITY_LO_js2_affinity_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js2_affinity_hi : 32;
    } reg;
} SOC_G3D_JS2_AFFINITY_HI_UNION;
#endif
#define SOC_G3D_JS2_AFFINITY_HI_js2_affinity_hi_START (0)
#define SOC_G3D_JS2_AFFINITY_HI_js2_affinity_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_space : 4;
        unsigned int reserved_0 : 4;
        unsigned int start_flush : 2;
        unsigned int start_mmu : 1;
        unsigned int reserved_1 : 1;
        unsigned int end_flush : 2;
        unsigned int reserved_2 : 18;
    } reg;
} SOC_G3D_JS2_CONFIG_UNION;
#endif
#define SOC_G3D_JS2_CONFIG_address_space_START (0)
#define SOC_G3D_JS2_CONFIG_address_space_END (3)
#define SOC_G3D_JS2_CONFIG_start_flush_START (8)
#define SOC_G3D_JS2_CONFIG_start_flush_END (9)
#define SOC_G3D_JS2_CONFIG_start_mmu_START (10)
#define SOC_G3D_JS2_CONFIG_start_mmu_END (10)
#define SOC_G3D_JS2_CONFIG_end_flush_START (12)
#define SOC_G3D_JS2_CONFIG_end_flush_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js2_command : 32;
    } reg;
} SOC_G3D_JS2_COMMAND_UNION;
#endif
#define SOC_G3D_JS2_COMMAND_js2_command_START (0)
#define SOC_G3D_JS2_COMMAND_js2_command_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js2_status : 32;
    } reg;
} SOC_G3D_JS2_STATUS_UNION;
#endif
#define SOC_G3D_JS2_STATUS_js2_status_START (0)
#define SOC_G3D_JS2_STATUS_js2_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js2_head_next_lo : 32;
    } reg;
} SOC_G3D_JS2_HEAD_NEXT_LO_UNION;
#endif
#define SOC_G3D_JS2_HEAD_NEXT_LO_js2_head_next_lo_START (0)
#define SOC_G3D_JS2_HEAD_NEXT_LO_js2_head_next_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int js2_head_next_hi : 32;
    } reg;
} SOC_G3D_JS2_HEAD_NEXT_HI_UNION;
#endif
#define SOC_G3D_JS2_HEAD_NEXT_HI_js2_head_next_hi_START (0)
#define SOC_G3D_JS2_HEAD_NEXT_HI_js2_head_next_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_JS2_AFFINITY_NEXT_LO_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_JS2_AFFINITY_NEXT_HI_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int address_space : 4;
        unsigned int reserved_0 : 4;
        unsigned int start_flush : 2;
        unsigned int start_mmu : 1;
        unsigned int reserved_1 : 1;
        unsigned int end_flush : 2;
        unsigned int reserved_2 : 18;
    } reg;
} SOC_G3D_JS2_CONFIG_NEXT_UNION;
#endif
#define SOC_G3D_JS2_CONFIG_NEXT_address_space_START (0)
#define SOC_G3D_JS2_CONFIG_NEXT_address_space_END (3)
#define SOC_G3D_JS2_CONFIG_NEXT_start_flush_START (8)
#define SOC_G3D_JS2_CONFIG_NEXT_start_flush_END (9)
#define SOC_G3D_JS2_CONFIG_NEXT_start_mmu_START (10)
#define SOC_G3D_JS2_CONFIG_NEXT_start_mmu_END (10)
#define SOC_G3D_JS2_CONFIG_NEXT_end_flush_START (12)
#define SOC_G3D_JS2_CONFIG_NEXT_end_flush_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_G3D_JS2_COMMAND_NEXT_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int page_fault : 4;
        unsigned int reserved_0 : 12;
        unsigned int bus_error : 4;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_G3D_MMU_IRQ_RAWSTAT_UNION;
#endif
#define SOC_G3D_MMU_IRQ_RAWSTAT_page_fault_START (0)
#define SOC_G3D_MMU_IRQ_RAWSTAT_page_fault_END (3)
#define SOC_G3D_MMU_IRQ_RAWSTAT_bus_error_START (16)
#define SOC_G3D_MMU_IRQ_RAWSTAT_bus_error_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int page_fault : 4;
        unsigned int reserved_0 : 12;
        unsigned int bus_error : 4;
        unsigned int reserved_1 : 12;
    } reg;
} SOC_G3D_MMU_IRQ_CLEAR_UNION;
#endif
#define SOC_G3D_MMU_IRQ_CLEAR_page_fault_START (0)
#define SOC_G3D_MMU_IRQ_CLEAR_page_fault_END (3)
#define SOC_G3D_MMU_IRQ_CLEAR_bus_error_START (16)
#define SOC_G3D_MMU_IRQ_CLEAR_bus_error_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int page_fault : 8;
        unsigned int reserved : 8;
        unsigned int bus_error : 8;
        unsigned int interruptmaskregister : 8;
    } reg;
} SOC_G3D_MMU_IRQ_MASK_UNION;
#endif
#define SOC_G3D_MMU_IRQ_MASK_page_fault_START (0)
#define SOC_G3D_MMU_IRQ_MASK_page_fault_END (7)
#define SOC_G3D_MMU_IRQ_MASK_bus_error_START (16)
#define SOC_G3D_MMU_IRQ_MASK_bus_error_END (23)
#define SOC_G3D_MMU_IRQ_MASK_interruptmaskregister_START (24)
#define SOC_G3D_MMU_IRQ_MASK_interruptmaskregister_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int page_fault : 8;
        unsigned int reserved : 8;
        unsigned int bus_error : 8;
        unsigned int mmu_irq_status : 8;
    } reg;
} SOC_G3D_MMU_IRQ_STATUS_UNION;
#endif
#define SOC_G3D_MMU_IRQ_STATUS_page_fault_START (0)
#define SOC_G3D_MMU_IRQ_STATUS_page_fault_END (7)
#define SOC_G3D_MMU_IRQ_STATUS_bus_error_START (16)
#define SOC_G3D_MMU_IRQ_STATUS_bus_error_END (23)
#define SOC_G3D_MMU_IRQ_STATUS_mmu_irq_status_START (24)
#define SOC_G3D_MMU_IRQ_STATUS_mmu_irq_status_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int transtab_adrmode : 2;
        unsigned int transtab_read_inner : 1;
        unsigned int reserved_0 : 1;
        unsigned int share_out : 1;
        unsigned int reserved_1 : 7;
        unsigned int as0_transtab_lo : 20;
    } reg;
} SOC_G3D_AS0_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_adrmode_START (0)
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_adrmode_END (1)
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_read_inner_START (2)
#define SOC_G3D_AS0_TRANSTAB_LO_transtab_read_inner_END (2)
#define SOC_G3D_AS0_TRANSTAB_LO_share_out_START (4)
#define SOC_G3D_AS0_TRANSTAB_LO_share_out_END (4)
#define SOC_G3D_AS0_TRANSTAB_LO_as0_transtab_lo_START (12)
#define SOC_G3D_AS0_TRANSTAB_LO_as0_transtab_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as0_transtab_hi : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_G3D_AS0_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS0_TRANSTAB_HI_as0_transtab_hi_START (0)
#define SOC_G3D_AS0_TRANSTAB_HI_as0_transtab_hi_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as0_memattr_l3 : 8;
        unsigned int as0_memattr_l2 : 8;
        unsigned int as0_memattr_l1 : 8;
        unsigned int as0_memattr_l0 : 8;
    } reg;
} SOC_G3D_AS0_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l3_START (0)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l3_END (7)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l2_START (8)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l2_END (15)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l1_START (16)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l1_END (23)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l0_START (24)
#define SOC_G3D_AS0_MEMATTR_LO_as0_memattr_l0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as0_memattr_h3 : 8;
        unsigned int as0_memattr_h2 : 8;
        unsigned int as0_memattr_h1 : 8;
        unsigned int as0_memattr_h0 : 8;
    } reg;
} SOC_G3D_AS0_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h3_START (0)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h3_END (7)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h2_START (8)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h2_END (15)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h1_START (16)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h1_END (23)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h0_START (24)
#define SOC_G3D_AS0_MEMATTR_HI_as0_memattr_h0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lockaddr_size : 6;
        unsigned int reserved : 6;
        unsigned int as0_lockaddr_l0 : 20;
    } reg;
} SOC_G3D_AS0_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS0_LOCKADDR_LO_lockaddr_size_START (0)
#define SOC_G3D_AS0_LOCKADDR_LO_lockaddr_size_END (5)
#define SOC_G3D_AS0_LOCKADDR_LO_as0_lockaddr_l0_START (12)
#define SOC_G3D_AS0_LOCKADDR_LO_as0_lockaddr_l0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as0_lockaddr_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_AS0_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS0_LOCKADDR_HI_as0_lockaddr_hi_START (0)
#define SOC_G3D_AS0_LOCKADDR_HI_as0_lockaddr_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nop : 1;
        unsigned int update : 1;
        unsigned int lock : 1;
        unsigned int unlock : 1;
        unsigned int flush_pt : 1;
        unsigned int flush_mem : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_G3D_AS0_COMMAND_UNION;
#endif
#define SOC_G3D_AS0_COMMAND_nop_START (0)
#define SOC_G3D_AS0_COMMAND_nop_END (0)
#define SOC_G3D_AS0_COMMAND_update_START (1)
#define SOC_G3D_AS0_COMMAND_update_END (1)
#define SOC_G3D_AS0_COMMAND_lock_START (2)
#define SOC_G3D_AS0_COMMAND_lock_END (2)
#define SOC_G3D_AS0_COMMAND_unlock_START (3)
#define SOC_G3D_AS0_COMMAND_unlock_END (3)
#define SOC_G3D_AS0_COMMAND_flush_pt_START (4)
#define SOC_G3D_AS0_COMMAND_flush_pt_END (4)
#define SOC_G3D_AS0_COMMAND_flush_mem_START (5)
#define SOC_G3D_AS0_COMMAND_flush_mem_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int exception_type : 8;
        unsigned int access_type : 2;
        unsigned int reserved : 6;
        unsigned int source_id : 16;
    } reg;
} SOC_G3D_AS0_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS0_FAULTSTATUS_exception_type_START (0)
#define SOC_G3D_AS0_FAULTSTATUS_exception_type_END (7)
#define SOC_G3D_AS0_FAULTSTATUS_access_type_START (8)
#define SOC_G3D_AS0_FAULTSTATUS_access_type_END (9)
#define SOC_G3D_AS0_FAULTSTATUS_source_id_START (16)
#define SOC_G3D_AS0_FAULTSTATUS_source_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as0_faultaddress_lo : 32;
    } reg;
} SOC_G3D_AS0_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS0_FAULTADDRESS_LO_as0_faultaddress_lo_START (0)
#define SOC_G3D_AS0_FAULTADDRESS_LO_as0_faultaddress_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as0_faultaddress_hi : 32;
    } reg;
} SOC_G3D_AS0_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS0_FAULTADDRESS_HI_as0_faultaddress_hi_START (0)
#define SOC_G3D_AS0_FAULTADDRESS_HI_as0_faultaddress_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mmu_flush_active : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_G3D_AS0_STATUS_UNION;
#endif
#define SOC_G3D_AS0_STATUS_mmu_flush_active_START (0)
#define SOC_G3D_AS0_STATUS_mmu_flush_active_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int transtab_adrmode : 2;
        unsigned int transtab_read_inner : 1;
        unsigned int reserved_0 : 1;
        unsigned int share_out : 1;
        unsigned int reserved_1 : 7;
        unsigned int as1_transtab_lo : 20;
    } reg;
} SOC_G3D_AS1_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_adrmode_START (0)
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_adrmode_END (1)
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_read_inner_START (2)
#define SOC_G3D_AS1_TRANSTAB_LO_transtab_read_inner_END (2)
#define SOC_G3D_AS1_TRANSTAB_LO_share_out_START (4)
#define SOC_G3D_AS1_TRANSTAB_LO_share_out_END (4)
#define SOC_G3D_AS1_TRANSTAB_LO_as1_transtab_lo_START (12)
#define SOC_G3D_AS1_TRANSTAB_LO_as1_transtab_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as1_transtab_hi : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_G3D_AS1_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS1_TRANSTAB_HI_as1_transtab_hi_START (0)
#define SOC_G3D_AS1_TRANSTAB_HI_as1_transtab_hi_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as1_memattr_l3 : 8;
        unsigned int as1_memattr_l2 : 8;
        unsigned int as1_memattr_l1 : 8;
        unsigned int as1_memattr_l0 : 8;
    } reg;
} SOC_G3D_AS1_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l3_START (0)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l3_END (7)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l2_START (8)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l2_END (15)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l1_START (16)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l1_END (23)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l0_START (24)
#define SOC_G3D_AS1_MEMATTR_LO_as1_memattr_l0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as1_memattr_h3 : 8;
        unsigned int as1_memattr_h2 : 8;
        unsigned int as1_memattr_h1 : 8;
        unsigned int as1_memattr_h0 : 8;
    } reg;
} SOC_G3D_AS1_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h3_START (0)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h3_END (7)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h2_START (8)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h2_END (15)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h1_START (16)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h1_END (23)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h0_START (24)
#define SOC_G3D_AS1_MEMATTR_HI_as1_memattr_h0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lockaddr_size : 6;
        unsigned int reserved : 6;
        unsigned int as1_lockaddr_l0 : 20;
    } reg;
} SOC_G3D_AS1_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS1_LOCKADDR_LO_lockaddr_size_START (0)
#define SOC_G3D_AS1_LOCKADDR_LO_lockaddr_size_END (5)
#define SOC_G3D_AS1_LOCKADDR_LO_as1_lockaddr_l0_START (12)
#define SOC_G3D_AS1_LOCKADDR_LO_as1_lockaddr_l0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as1_lockaddr_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_AS1_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS1_LOCKADDR_HI_as1_lockaddr_hi_START (0)
#define SOC_G3D_AS1_LOCKADDR_HI_as1_lockaddr_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nop : 1;
        unsigned int update : 1;
        unsigned int lock : 1;
        unsigned int unlock : 1;
        unsigned int flush_pt : 1;
        unsigned int flush_mem : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_G3D_AS1_COMMAND_UNION;
#endif
#define SOC_G3D_AS1_COMMAND_nop_START (0)
#define SOC_G3D_AS1_COMMAND_nop_END (0)
#define SOC_G3D_AS1_COMMAND_update_START (1)
#define SOC_G3D_AS1_COMMAND_update_END (1)
#define SOC_G3D_AS1_COMMAND_lock_START (2)
#define SOC_G3D_AS1_COMMAND_lock_END (2)
#define SOC_G3D_AS1_COMMAND_unlock_START (3)
#define SOC_G3D_AS1_COMMAND_unlock_END (3)
#define SOC_G3D_AS1_COMMAND_flush_pt_START (4)
#define SOC_G3D_AS1_COMMAND_flush_pt_END (4)
#define SOC_G3D_AS1_COMMAND_flush_mem_START (5)
#define SOC_G3D_AS1_COMMAND_flush_mem_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int exception_type : 8;
        unsigned int access_type : 2;
        unsigned int reserved : 6;
        unsigned int source_id : 16;
    } reg;
} SOC_G3D_AS1_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS1_FAULTSTATUS_exception_type_START (0)
#define SOC_G3D_AS1_FAULTSTATUS_exception_type_END (7)
#define SOC_G3D_AS1_FAULTSTATUS_access_type_START (8)
#define SOC_G3D_AS1_FAULTSTATUS_access_type_END (9)
#define SOC_G3D_AS1_FAULTSTATUS_source_id_START (16)
#define SOC_G3D_AS1_FAULTSTATUS_source_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as1_faultaddress_lo : 32;
    } reg;
} SOC_G3D_AS1_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS1_FAULTADDRESS_LO_as1_faultaddress_lo_START (0)
#define SOC_G3D_AS1_FAULTADDRESS_LO_as1_faultaddress_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as0_faultaddress_hi : 32;
    } reg;
} SOC_G3D_AS1_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS1_FAULTADDRESS_HI_as0_faultaddress_hi_START (0)
#define SOC_G3D_AS1_FAULTADDRESS_HI_as0_faultaddress_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mmu_flush_active : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_G3D_AS1_STATUS_UNION;
#endif
#define SOC_G3D_AS1_STATUS_mmu_flush_active_START (0)
#define SOC_G3D_AS1_STATUS_mmu_flush_active_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int transtab_adrmode : 2;
        unsigned int transtab_read_inner : 1;
        unsigned int reserved_0 : 1;
        unsigned int share_out : 1;
        unsigned int reserved_1 : 7;
        unsigned int as2_transtab_lo : 20;
    } reg;
} SOC_G3D_AS2_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_adrmode_START (0)
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_adrmode_END (1)
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_read_inner_START (2)
#define SOC_G3D_AS2_TRANSTAB_LO_transtab_read_inner_END (2)
#define SOC_G3D_AS2_TRANSTAB_LO_share_out_START (4)
#define SOC_G3D_AS2_TRANSTAB_LO_share_out_END (4)
#define SOC_G3D_AS2_TRANSTAB_LO_as2_transtab_lo_START (12)
#define SOC_G3D_AS2_TRANSTAB_LO_as2_transtab_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as2_transtab_hi : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_G3D_AS2_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS2_TRANSTAB_HI_as2_transtab_hi_START (0)
#define SOC_G3D_AS2_TRANSTAB_HI_as2_transtab_hi_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as2_memattr_l3 : 8;
        unsigned int as2_memattr_l2 : 8;
        unsigned int as2_memattr_l1 : 8;
        unsigned int as2_memattr_l0 : 8;
    } reg;
} SOC_G3D_AS2_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l3_START (0)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l3_END (7)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l2_START (8)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l2_END (15)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l1_START (16)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l1_END (23)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l0_START (24)
#define SOC_G3D_AS2_MEMATTR_LO_as2_memattr_l0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as2_memattr_h3 : 8;
        unsigned int as2_memattr_h2 : 8;
        unsigned int as2_memattr_h1 : 8;
        unsigned int as2_memattr_h0 : 8;
    } reg;
} SOC_G3D_AS2_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h3_START (0)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h3_END (7)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h2_START (8)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h2_END (15)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h1_START (16)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h1_END (23)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h0_START (24)
#define SOC_G3D_AS2_MEMATTR_HI_as2_memattr_h0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lockaddr_size : 6;
        unsigned int reserved : 6;
        unsigned int as2_lockaddr_l0 : 20;
    } reg;
} SOC_G3D_AS2_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS2_LOCKADDR_LO_lockaddr_size_START (0)
#define SOC_G3D_AS2_LOCKADDR_LO_lockaddr_size_END (5)
#define SOC_G3D_AS2_LOCKADDR_LO_as2_lockaddr_l0_START (12)
#define SOC_G3D_AS2_LOCKADDR_LO_as2_lockaddr_l0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as2_lockaddr_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_AS2_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS2_LOCKADDR_HI_as2_lockaddr_hi_START (0)
#define SOC_G3D_AS2_LOCKADDR_HI_as2_lockaddr_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nop : 1;
        unsigned int update : 1;
        unsigned int lock : 1;
        unsigned int unlock : 1;
        unsigned int flush_pt : 1;
        unsigned int flush_mem : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_G3D_AS2_COMMAND_UNION;
#endif
#define SOC_G3D_AS2_COMMAND_nop_START (0)
#define SOC_G3D_AS2_COMMAND_nop_END (0)
#define SOC_G3D_AS2_COMMAND_update_START (1)
#define SOC_G3D_AS2_COMMAND_update_END (1)
#define SOC_G3D_AS2_COMMAND_lock_START (2)
#define SOC_G3D_AS2_COMMAND_lock_END (2)
#define SOC_G3D_AS2_COMMAND_unlock_START (3)
#define SOC_G3D_AS2_COMMAND_unlock_END (3)
#define SOC_G3D_AS2_COMMAND_flush_pt_START (4)
#define SOC_G3D_AS2_COMMAND_flush_pt_END (4)
#define SOC_G3D_AS2_COMMAND_flush_mem_START (5)
#define SOC_G3D_AS2_COMMAND_flush_mem_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int exception_type : 8;
        unsigned int access_type : 2;
        unsigned int reserved : 6;
        unsigned int source_id : 16;
    } reg;
} SOC_G3D_AS2_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS2_FAULTSTATUS_exception_type_START (0)
#define SOC_G3D_AS2_FAULTSTATUS_exception_type_END (7)
#define SOC_G3D_AS2_FAULTSTATUS_access_type_START (8)
#define SOC_G3D_AS2_FAULTSTATUS_access_type_END (9)
#define SOC_G3D_AS2_FAULTSTATUS_source_id_START (16)
#define SOC_G3D_AS2_FAULTSTATUS_source_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as2_faultaddress_lo : 32;
    } reg;
} SOC_G3D_AS2_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS2_FAULTADDRESS_LO_as2_faultaddress_lo_START (0)
#define SOC_G3D_AS2_FAULTADDRESS_LO_as2_faultaddress_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as2_faultaddress_hi : 32;
    } reg;
} SOC_G3D_AS2_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS2_FAULTADDRESS_HI_as2_faultaddress_hi_START (0)
#define SOC_G3D_AS2_FAULTADDRESS_HI_as2_faultaddress_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mmu_flush_active : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_G3D_AS2_STATUS_UNION;
#endif
#define SOC_G3D_AS2_STATUS_mmu_flush_active_START (0)
#define SOC_G3D_AS2_STATUS_mmu_flush_active_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int transtab_adrmode : 2;
        unsigned int transtab_read_inner : 1;
        unsigned int reserved_0 : 1;
        unsigned int share_out : 1;
        unsigned int reserved_1 : 7;
        unsigned int as3_transtab_lo : 20;
    } reg;
} SOC_G3D_AS3_TRANSTAB_LO_UNION;
#endif
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_adrmode_START (0)
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_adrmode_END (1)
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_read_inner_START (2)
#define SOC_G3D_AS3_TRANSTAB_LO_transtab_read_inner_END (2)
#define SOC_G3D_AS3_TRANSTAB_LO_share_out_START (4)
#define SOC_G3D_AS3_TRANSTAB_LO_share_out_END (4)
#define SOC_G3D_AS3_TRANSTAB_LO_as3_transtab_lo_START (12)
#define SOC_G3D_AS3_TRANSTAB_LO_as3_transtab_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as3_transtab_hi : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_G3D_AS3_TRANSTAB_HI_UNION;
#endif
#define SOC_G3D_AS3_TRANSTAB_HI_as3_transtab_hi_START (0)
#define SOC_G3D_AS3_TRANSTAB_HI_as3_transtab_hi_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as3_memattr_l3 : 8;
        unsigned int as3_memattr_l2 : 8;
        unsigned int as3_memattr_l1 : 8;
        unsigned int as3_memattr_l0 : 8;
    } reg;
} SOC_G3D_AS3_MEMATTR_LO_UNION;
#endif
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l3_START (0)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l3_END (7)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l2_START (8)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l2_END (15)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l1_START (16)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l1_END (23)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l0_START (24)
#define SOC_G3D_AS3_MEMATTR_LO_as3_memattr_l0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as3_memattr_h3 : 8;
        unsigned int as3_memattr_h2 : 8;
        unsigned int as3_memattr_h1 : 8;
        unsigned int as3_memattr_h0 : 8;
    } reg;
} SOC_G3D_AS3_MEMATTR_HI_UNION;
#endif
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h3_START (0)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h3_END (7)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h2_START (8)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h2_END (15)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h1_START (16)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h1_END (23)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h0_START (24)
#define SOC_G3D_AS3_MEMATTR_HI_as3_memattr_h0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lockaddr_size : 6;
        unsigned int reserved : 6;
        unsigned int as3_lockaddr_l0 : 20;
    } reg;
} SOC_G3D_AS3_LOCKADDR_LO_UNION;
#endif
#define SOC_G3D_AS3_LOCKADDR_LO_lockaddr_size_START (0)
#define SOC_G3D_AS3_LOCKADDR_LO_lockaddr_size_END (5)
#define SOC_G3D_AS3_LOCKADDR_LO_as3_lockaddr_l0_START (12)
#define SOC_G3D_AS3_LOCKADDR_LO_as3_lockaddr_l0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as3_lockaddr_hi : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_G3D_AS3_LOCKADDR_HI_UNION;
#endif
#define SOC_G3D_AS3_LOCKADDR_HI_as3_lockaddr_hi_START (0)
#define SOC_G3D_AS3_LOCKADDR_HI_as3_lockaddr_hi_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nop : 1;
        unsigned int update : 1;
        unsigned int lock : 1;
        unsigned int unlock : 1;
        unsigned int flush_pt : 1;
        unsigned int flush_mem : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_G3D_AS3_COMMAND_UNION;
#endif
#define SOC_G3D_AS3_COMMAND_nop_START (0)
#define SOC_G3D_AS3_COMMAND_nop_END (0)
#define SOC_G3D_AS3_COMMAND_update_START (1)
#define SOC_G3D_AS3_COMMAND_update_END (1)
#define SOC_G3D_AS3_COMMAND_lock_START (2)
#define SOC_G3D_AS3_COMMAND_lock_END (2)
#define SOC_G3D_AS3_COMMAND_unlock_START (3)
#define SOC_G3D_AS3_COMMAND_unlock_END (3)
#define SOC_G3D_AS3_COMMAND_flush_pt_START (4)
#define SOC_G3D_AS3_COMMAND_flush_pt_END (4)
#define SOC_G3D_AS3_COMMAND_flush_mem_START (5)
#define SOC_G3D_AS3_COMMAND_flush_mem_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int exception_type : 8;
        unsigned int access_type : 2;
        unsigned int reserved : 6;
        unsigned int source_id : 16;
    } reg;
} SOC_G3D_AS3_FAULTSTATUS_UNION;
#endif
#define SOC_G3D_AS3_FAULTSTATUS_exception_type_START (0)
#define SOC_G3D_AS3_FAULTSTATUS_exception_type_END (7)
#define SOC_G3D_AS3_FAULTSTATUS_access_type_START (8)
#define SOC_G3D_AS3_FAULTSTATUS_access_type_END (9)
#define SOC_G3D_AS3_FAULTSTATUS_source_id_START (16)
#define SOC_G3D_AS3_FAULTSTATUS_source_id_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as3_faultaddress_lo : 32;
    } reg;
} SOC_G3D_AS3_FAULTADDRESS_LO_UNION;
#endif
#define SOC_G3D_AS3_FAULTADDRESS_LO_as3_faultaddress_lo_START (0)
#define SOC_G3D_AS3_FAULTADDRESS_LO_as3_faultaddress_lo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int as3_faultaddress_hi : 32;
    } reg;
} SOC_G3D_AS3_FAULTADDRESS_HI_UNION;
#endif
#define SOC_G3D_AS3_FAULTADDRESS_HI_as3_faultaddress_hi_START (0)
#define SOC_G3D_AS3_FAULTADDRESS_HI_as3_faultaddress_hi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mmu_flush_active : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_G3D_AS3_STATUS_UNION;
#endif
#define SOC_G3D_AS3_STATUS_mmu_flush_active_START (0)
#define SOC_G3D_AS3_STATUS_mmu_flush_active_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
