#ifndef __SOC_SECENG_S_INTERFACE_H__
#define __SOC_SECENG_S_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_SECENG_S_MEMORY_MAP0_ADDR(base) ((base) + (0x00000))
#define SOC_SECENG_S_MEMORY_MAP1_ADDR(base) ((base) + (0x00004))
#define SOC_SECENG_S_MEMORY_MAP2_ADDR(base) ((base) + (0x00008))
#define SOC_SECENG_S_MEMORY_MAP3_ADDR(base) ((base) + (0x0000C))
#define SOC_SECENG_S_MEMORY_MAP4_ADDR(base) ((base) + (0x00010))
#define SOC_SECENG_S_MEMORY_MAP5_ADDR(base) ((base) + (0x00014))
#define SOC_SECENG_S_MEMORY_MAP6_ADDR(base) ((base) + (0x00018))
#define SOC_SECENG_S_MEMORY_MAP7_ADDR(base) ((base) + (0x0001C))
#define SOC_SECENG_S_MEMORY_MAP8_ADDR(base) ((base) + (0x00020))
#define SOC_SECENG_S_MEMORY_MAP9_ADDR(base) ((base) + (0x00024))
#define SOC_SECENG_S_MEMORY_MAP10_ADDR(base) ((base) + (0x00028))
#define SOC_SECENG_S_MEMORY_MAP11_ADDR(base) ((base) + (0x0002C))
#define SOC_SECENG_S_MEMORY_MAP12_ADDR(base) ((base) + (0x00030))
#define SOC_SECENG_S_MEMORY_MAP13_ADDR(base) ((base) + (0x00034))
#define SOC_SECENG_S_MEMORY_MAP14_ADDR(base) ((base) + (0x00038))
#define SOC_SECENG_S_MEMORY_MAP15_ADDR(base) ((base) + (0x0003C))
#define SOC_SECENG_S_MEMORY_MAP16_ADDR(base) ((base) + (0x00040))
#define SOC_SECENG_S_MEMORY_MAP17_ADDR(base) ((base) + (0x00044))
#define SOC_SECENG_S_MEMORY_MAP18_ADDR(base) ((base) + (0x00048))
#define SOC_SECENG_S_MEMORY_MAP19_ADDR(base) ((base) + (0x0004C))
#define SOC_SECENG_S_MEMORY_MAP20_ADDR(base) ((base) + (0x00050))
#define SOC_SECENG_S_MEMORY_MAP21_ADDR(base) ((base) + (0x00054))
#define SOC_SECENG_S_MEMORY_MAP22_ADDR(base) ((base) + (0x00058))
#define SOC_SECENG_S_MEMORY_MAP23_ADDR(base) ((base) + (0x0005C))
#define SOC_SECENG_S_MEMORY_MAP24_ADDR(base) ((base) + (0x00060))
#define SOC_SECENG_S_MEMORY_MAP25_ADDR(base) ((base) + (0x00064))
#define SOC_SECENG_S_MEMORY_MAP26_ADDR(base) ((base) + (0x00068))
#define SOC_SECENG_S_MEMORY_MAP27_ADDR(base) ((base) + (0x0006C))
#define SOC_SECENG_S_MEMORY_MAP28_ADDR(base) ((base) + (0x00070))
#define SOC_SECENG_S_MEMORY_MAP29_ADDR(base) ((base) + (0x00074))
#define SOC_SECENG_S_MEMORY_MAP30_ADDR(base) ((base) + (0x00078))
#define SOC_SECENG_S_MEMORY_MAP31_ADDR(base) ((base) + (0x0007C))
#define SOC_SECENG_S_OPCODE_ADDR(base) ((base) + (0x00080))
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_ADDR(base) ((base) + (0x00084))
#define SOC_SECENG_S_PKA_STATUS_ADDR(base) ((base) + (0x00088))
#define SOC_SECENG_S_PKA_SW_RESET_ADDR(base) ((base) + (0x0008C))
#define SOC_SECENG_S_PKA_L0_ADDR(base) ((base) + (0x00090))
#define SOC_SECENG_S_PKA_L1_ADDR(base) ((base) + (0x00094))
#define SOC_SECENG_S_PKA_L2_ADDR(base) ((base) + (0x00098))
#define SOC_SECENG_S_PKA_L3_ADDR(base) ((base) + (0x0009C))
#define SOC_SECENG_S_PKA_L4_ADDR(base) ((base) + (0x000A0))
#define SOC_SECENG_S_PKA_L5_ADDR(base) ((base) + (0x000A4))
#define SOC_SECENG_S_PKA_L6_ADDR(base) ((base) + (0x000A8))
#define SOC_SECENG_S_PKA_L7_ADDR(base) ((base) + (0x000AC))
#define SOC_SECENG_S_PKA_PIPE_RDY_ADDR(base) ((base) + (0x000B0))
#define SOC_SECENG_S_PKA_DONE_ADDR(base) ((base) + (0x000B4))
#define SOC_SECENG_S_PKA_MON_SELECT_ADDR(base) ((base) + (0x000B8))
#define SOC_SECENG_S_PKA_DEBUG_REG_EN_ADDR(base) ((base) + (0x000BC))
#define SOC_SECENG_S_DEBUG_CNT_ADDR_ADDR(base) ((base) + (0x000C0))
#define SOC_SECENG_S_PKA_DEBUG_HALT_ADDR(base) ((base) + (0x000C8))
#define SOC_SECENG_S_PKA_MSB_ADDR_ADDR(base) ((base) + (0x000CC))
#define SOC_SECENG_S_PKA_MON_READ_ADDR(base) ((base) + (0x000D0))
#define SOC_SECENG_S_RNG_IMR_ADDR(base) ((base) + (0x00100))
#define SOC_SECENG_S_RNG_ISR_ADDR(base) ((base) + (0x00104))
#define SOC_SECENG_S_RNG_ICR_ADDR(base) ((base) + (0x00108))
#define SOC_SECENG_S_TRNG_CONFIG_ADDR(base) ((base) + (0x0010C))
#define SOC_SECENG_S_TRNG_VALID_ADDR(base) ((base) + (0x00110))
#define SOC_SECENG_S_EHR_DATA_0_ADDR(base) ((base) + (0x00114))
#define SOC_SECENG_S_EHR_DATA_1_ADDR(base) ((base) + (0x00118))
#define SOC_SECENG_S_EHR_DATA_2_ADDR(base) ((base) + (0x0011C))
#define SOC_SECENG_S_EHR_DATA_3_ADDR(base) ((base) + (0x00120))
#define SOC_SECENG_S_EHR_DATA_4_ADDR(base) ((base) + (0x00124))
#define SOC_SECENG_S_EHR_DATA_5_ADDR(base) ((base) + (0x00128))
#define SOC_SECENG_S_RND_SOURCE_ENABLE_ADDR(base) ((base) + (0x0012C))
#define SOC_SECENG_S_SAMPLE_CNT1_ADDR(base) ((base) + (0x00130))
#define SOC_SECENG_S_AUTOCORR_STATISTIC_ADDR(base) ((base) + (0x00134))
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_ADDR(base) ((base) + (0x00138))
#define SOC_SECENG_S_RNG_SW_RESET_ADDR(base) ((base) + (0x00140))
#define SOC_SECENG_S_RNG_DEBUG_EN_INPUT_ADDR(base) ((base) + (0x001B4))
#define SOC_SECENG_S_RNG_BUSY_ADDR(base) ((base) + (0x001B8))
#define SOC_SECENG_S_RST_BITS_COUNTER_ADDR(base) ((base) + (0x001BC))
#define SOC_SECENG_S_RNG_VERSION_ADDR(base) ((base) + (0x001C0))
#define SOC_SECENG_S_RNG_CLK_ENABLE_ADDR(base) ((base) + (0x001C4))
#define SOC_SECENG_S_RNG_DMA_ENABLE_ADDR(base) ((base) + (0x001C8))
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_ADDR(base) ((base) + (0x001CC))
#define SOC_SECENG_S_RNG_DMA_SRAM_ADDR_ADDR(base) ((base) + (0x001D0))
#define SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_ADDR(base) ((base) + (0x001D4))
#define SOC_SECENG_S_RNG_WATCHDOG_VAL_ADDR(base) ((base) + (0x001D8))
#define SOC_SECENG_S_RNG_DMA_STATUS_ADDR(base) ((base) + (0x001DC))
#define SOC_SECENG_S_AES_CLK_ENABLE_ADDR(base) ((base) + (0x00810))
#define SOC_SECENG_S_DES_CLK_ENABLE_ADDR(base) ((base) + (0x00814))
#define SOC_SECENG_S_HASH_CLK_ENABLE_ADDR(base) ((base) + (0x00818))
#define SOC_SECENG_S_PKA_CLK_ENABLE_ADDR(base) ((base) + (0x0081C))
#define SOC_SECENG_S_DMA_CLK_ENABLE_ADDR(base) ((base) + (0x00820))
#define SOC_SECENG_S_CLK_STATUS_ADDR(base) ((base) + (0x00824))
#define SOC_SECENG_S_CRYPTO_CTL_ADDR(base) ((base) + (0x00900))
#define SOC_SECENG_S_CRYPTO_BUSY_ADDR(base) ((base) + (0x00910))
#define SOC_SECENG_S_HASH_BUSY_ADDR(base) ((base) + (0x0091C))
#define SOC_SECENG_S_VERSION_ADDR(base) ((base) + (0x00928))
#define SOC_SECENG_S_CONTEXT_ID_ADDR(base) ((base) + (0x00930))
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_ADDR(base) ((base) + (0x00940))
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_ADDR(base) ((base) + (0x00944))
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_ADDR(base) ((base) + (0x00948))
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_ADDR(base) ((base) + (0x0094C))
#define SOC_SECENG_S_HOST_RGF_IRR_ADDR(base) ((base) + (0x00A00))
#define SOC_SECENG_S_HOST_RGF_IMR_ADDR(base) ((base) + (0x00A04))
#define SOC_SECENG_S_HOST_RGF_ICR_ADDR(base) ((base) + (0x00A08))
#define SOC_SECENG_S_HOST_RGF_ENDIAN_ADDR(base) ((base) + (0x00A0C))
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_ADDR(base) ((base) + (0x00A20))
#define SOC_SECENG_S_HOST_RGF_SIGNATURE_ADDR(base) ((base) + (0x00A24))
#define SOC_SECENG_S_HOST_BOOT_ADDR(base) ((base) + (0x00A28))
#define SOC_SECENG_S_HOST_PROVISION_CONST_MASK_ADDR(base) ((base) + (0x00A30))
#define SOC_SECENG_S_HOST_CRYPTOKEY_SEL_ADDR(base) ((base) + (0x00A38))
#define SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_ADDR(base) ((base) + (0x0A44))
#define SOC_SECENG_S_HOST_DCU_EN_ADDR(base) ((base) + (0x0A64))
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_ADDR(base) ((base) + (0x0A68))
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_ADDR(base) ((base) + (0x0A6C))
#define SOC_SECENG_S_HOST_CC_AO_TEST_ADDR(base) ((base) + (0x0A70))
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_ADDR(base) ((base) + (0x0A74))
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_ADDR(base) ((base) + (0x0A78))
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_ADDR(base) ((base) + (0x0A7C))
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_ADDR(base) ((base) + (0x0A80))
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_ADDR(base) ((base) + (0x0A84))
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_ADDR(base) ((base) + (0x0A88))
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_ADDR(base) ((base) + (0x0A8C))
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_ADDR(base) ((base) + (0x0A90))
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_ADDR(base) ((base) + (0x0A94))
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_ADDR(base) ((base) + (0x0A98))
#define SOC_SECENG_S_NVM_CC_BOOT_ADDR(base) ((base) + (0x00AA0))
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_ADDR(base) ((base) + (0x00AA4))
#define SOC_SECENG_S_HOST_AIB_WDATA_REG_ADDR(base) ((base) + (0x00AA8))
#define SOC_SECENG_S_HOST_AIB_RDATA_REG_ADDR(base) ((base) + (0x00AAC))
#define SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_ADDR(base) ((base) + (0x00AB0))
#define SOC_SECENG_S_AIB_FUSE_ACK_ADDR(base) ((base) + (0x00AB4))
#define SOC_SECENG_S_AIB_DEBUG_STATUS_ADDR(base) ((base) + (0x00AB8))
#define SOC_SECENG_S_LCS_IS_VALID_ADDR(base) ((base) + (0x00ABC))
#define SOC_SECENG_S_HOST_SESSION_KEY0_ADDR(base) ((base) + (0x00AC0))
#define SOC_SECENG_S_HOST_SESSION_KEY1_ADDR(base) ((base) + (0x00AC4))
#define SOC_SECENG_S_HOST_SESSION_KEY2_ADDR(base) ((base) + (0x00AC8))
#define SOC_SECENG_S_HOST_SESSION_KEY3_ADDR(base) ((base) + (0x00ACC))
#define SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_ADDR(base) ((base) + (0x00AD0))
#define SOC_SECENG_S_LCS_REG_ADDR(base) ((base) + (0x00AD4))
#define SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_ADDR(base) ((base) + (0x00AD8))
#define SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_ADDR(base) ((base) + (0x00ADC))
#define SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_ADDR(base) ((base) + (0x00AE0))
#define SOC_SECENG_S_HOST_AO_CC_IS_SD_ADDR(base) ((base) + (0x00AE4))
#define SOC_SECENG_S_HOST_RMA_RKEK_WR_ADDR(base) ((base) + (0x00AE8))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT0_ADDR(base) ((base) + (0x00B00))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT1_ADDR(base) ((base) + (0x00B04))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT2_ADDR(base) ((base) + (0x00B08))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT3_ADDR(base) ((base) + (0x00B0C))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT4_ADDR(base) ((base) + (0x00B10))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT5_ADDR(base) ((base) + (0x00B14))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT8_ADDR(base) ((base) + (0x00B20))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT9_ADDR(base) ((base) + (0x00B24))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT10_ADDR(base) ((base) + (0x00B28))
#define SOC_SECENG_S_AXIM_MON_INFLIGHT11_ADDR(base) ((base) + (0x00B2C))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_ADDR(base) ((base) + (0x00B40))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_ADDR(base) ((base) + (0x00B44))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_ADDR(base) ((base) + (0x00B48))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_ADDR(base) ((base) + (0x00B4C))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_ADDR(base) ((base) + (0x00B50))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_ADDR(base) ((base) + (0x00B54))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_ADDR(base) ((base) + (0x00B60))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_ADDR(base) ((base) + (0x00B64))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_ADDR(base) ((base) + (0x00B68))
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_ADDR(base) ((base) + (0x00B6C))
#define SOC_SECENG_S_AXIM_PIDTABLE0_ADDR(base) ((base) + (0x00B70))
#define SOC_SECENG_S_AXIM_PIDTABLE1_ADDR(base) ((base) + (0x00B74))
#define SOC_SECENG_S_AXIM_PIDTABLE2_ADDR(base) ((base) + (0x00B78))
#define SOC_SECENG_S_AXIM_PIDTABLE3_ADDR(base) ((base) + (0x00B7C))
#define SOC_SECENG_S_AXIM_MON_COMP0_ADDR(base) ((base) + (0x00B80))
#define SOC_SECENG_S_AXIM_MON_COMP1_ADDR(base) ((base) + (0x00B84))
#define SOC_SECENG_S_AXIM_MON_COMP2_ADDR(base) ((base) + (0x00B88))
#define SOC_SECENG_S_AXIM_MON_COMP3_ADDR(base) ((base) + (0x00B8C))
#define SOC_SECENG_S_AXIM_MON_COMP4_ADDR(base) ((base) + (0x00B90))
#define SOC_SECENG_S_AXIM_MON_COMP5_ADDR(base) ((base) + (0x00B94))
#define SOC_SECENG_S_AXIM_MON_COMP8_ADDR(base) ((base) + (0x00BA0))
#define SOC_SECENG_S_AXIM_MON_COMP9_ADDR(base) ((base) + (0x00BA4))
#define SOC_SECENG_S_AXIM_MON_COMP10_ADDR(base) ((base) + (0x00BA8))
#define SOC_SECENG_S_AXIM_MON_COMP11_ADDR(base) ((base) + (0x00BAC))
#define SOC_SECENG_S_AXIM_MON_RMAX_ADDR(base) ((base) + (0x00BB4))
#define SOC_SECENG_S_AXIM_MON_RMIN_ADDR(base) ((base) + (0x00BB8))
#define SOC_SECENG_S_AXIM_MON_WMAX_ADDR(base) ((base) + (0x00BBC))
#define SOC_SECENG_S_AXIM_MON_WMIN_ADDR(base) ((base) + (0x00BC0))
#define SOC_SECENG_S_AXIM_MON_ERR_ADDR(base) ((base) + (0x00BC4))
#define SOC_SECENG_S_AXIM_RDSTAT_ADDR(base) ((base) + (0x00BC8))
#define SOC_SECENG_S_AXIM_RLATENCY_ADDR(base) ((base) + (0x00BD0))
#define SOC_SECENG_S_AXIM_RBURST_ADDR(base) ((base) + (0x00BD4))
#define SOC_SECENG_S_AXIM_WLATENCY_ADDR(base) ((base) + (0x00BD8))
#define SOC_SECENG_S_AXIM_WBURST_ADDR(base) ((base) + (0x00BDC))
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_ADDR(base) ((base) + (0x00BE0))
#define SOC_SECENG_S_AXIM_PROT_CFG_ADDR(base) ((base) + (0x00BE4))
#define SOC_SECENG_S_AXIM_CFG1_ADDR(base) ((base) + (0x00BE8))
#define SOC_SECENG_S_AXIM_ACE_CONST_ADDR(base) ((base) + (0x00BEC))
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_ADDR(base) ((base) + (0x00BF0))
#define SOC_SECENG_S_ADDR_AXIM_CTRL_ADDR(base) ((base) + (0x00BF4))
#define SOC_SECENG_S_DIN_BUFFER_ADDR(base) ((base) + (0x00C00))
#define SOC_SECENG_S_DIN_MEM_DMA_BUSY_ADDR(base) ((base) + (0x00C20))
#define SOC_SECENG_S_SRC_LLI_SRAM_ADDR_ADDR(base) ((base) + (0x00C24))
#define SOC_SECENG_S_SRC_LLI_WORD0_ADDR(base) ((base) + (0x00C28))
#define SOC_SECENG_S_SRC_LLI_WORD1_ADDR(base) ((base) + (0x00C2C))
#define SOC_SECENG_S_SRAM_SRC_ADDR_ADDR(base) ((base) + (0x00C30))
#define SOC_SECENG_S_DIN_SRAM_BYTES_LEN_ADDR(base) ((base) + (0x00C34))
#define SOC_SECENG_S_DIN_SRAM_DMA_BUSY_ADDR(base) ((base) + (0x00C38))
#define SOC_SECENG_S_DIN_SRAM_ENDIANNESS_ADDR(base) ((base) + (0x00C3C))
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_ADDR(base) ((base) + (0x00C40))
#define SOC_SECENG_S_DIN_SW_RESET_ADDR(base) ((base) + (0x00C44))
#define SOC_SECENG_S_DIN_CPU_DATA_SIZE_ADDR(base) ((base) + (0x0C48))
#define SOC_SECENG_S_WRITE_ALIGN_LAST_ADDR(base) ((base) + (0x00C4C))
#define SOC_SECENG_S_FIFO_IN_EMPTY_ADDR(base) ((base) + (0x00C50))
#define SOC_SECENG_S_DISABLE_OUTSTD_REQ_ADDR(base) ((base) + (0x00C54))
#define SOC_SECENG_S_DIN_FIFO_RST_PNTR_ADDR(base) ((base) + (0x00C58))
#define SOC_SECENG_S_DOUT_BUFFER_ADDR(base) ((base) + (0x00D00))
#define SOC_SECENG_S_DOUT_MEM_DMA_BUSY_ADDR(base) ((base) + (0x00D20))
#define SOC_SECENG_S_DST_LLI_SRAM_ADDR_ADDR(base) ((base) + (0x00D24))
#define SOC_SECENG_S_DST_LLI_WORD0_ADDR(base) ((base) + (0x00D28))
#define SOC_SECENG_S_DST_LLI_WORD1_ADDR(base) ((base) + (0x00D2C))
#define SOC_SECENG_S_SRAM_DEST_ADDR_ADDR(base) ((base) + (0x00D30))
#define SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_ADDR(base) ((base) + (0x00D34))
#define SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_ADDR(base) ((base) + (0x00D38))
#define SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_ADDR(base) ((base) + (0x00D3C))
#define SOC_SECENG_S_READ_ALIGN_LAST_ADDR(base) ((base) + (0x00D44))
#define SOC_SECENG_S_DOUT_FIFO_EMPTY_ADDR(base) ((base) + (0x00D50))
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_ADDR(base) ((base) + (0x00D54))
#define SOC_SECENG_S_DOUT_SW_RESET_ADDR(base) ((base) + (0x00D58))
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_ADDR(base) ((base) + (0x00E00))
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_ADDR(base) ((base) + (0x00E04))
#define SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_ADDR(base) ((base) + (0x00E3C))
#define SOC_SECENG_S_DSCRPTR_SW_RESET_ADDR(base) ((base) + (0x00E40))
#define SOC_SECENG_S_DSCRPTR_DEBUG_MODE_ADDR(base) ((base) + (0x00E4C))
#define SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_ADDR(base) ((base) + (0x0E64))
#define SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_ADDR(base) ((base) + (0x0E68))
#define SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_ADDR(base) ((base) + (0x0E6C))
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_ADDR(base) ((base) + (0x00E80))
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_ADDR(base) ((base) + (0x00E84))
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_ADDR(base) ((base) + (0x00E88))
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_ADDR(base) ((base) + (0x00E8C))
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_ADDR(base) ((base) + (0x00E90))
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_ADDR(base) ((base) + (0x00E94))
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_ADDR(base) ((base) + (0x00E98))
#define SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_ADDR(base) ((base) + (0x00E9C))
#define SOC_SECENG_S_SRAM_DATA_ADDR(base) ((base) + (0x00F00))
#define SOC_SECENG_S_SRAM_ADDR_ADDR(base) ((base) + (0x00F04))
#define SOC_SECENG_S_SRAM_DATA_READY_ADDR(base) ((base) + (0x00F08))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map0 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP0_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP0_memory_map0_START (2)
#define SOC_SECENG_S_MEMORY_MAP0_memory_map0_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map1 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP1_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP1_memory_map1_START (2)
#define SOC_SECENG_S_MEMORY_MAP1_memory_map1_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map2 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP2_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP2_memory_map2_START (2)
#define SOC_SECENG_S_MEMORY_MAP2_memory_map2_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map3 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP3_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP3_memory_map3_START (2)
#define SOC_SECENG_S_MEMORY_MAP3_memory_map3_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map4 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP4_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP4_memory_map4_START (2)
#define SOC_SECENG_S_MEMORY_MAP4_memory_map4_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map5 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP5_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP5_memory_map5_START (2)
#define SOC_SECENG_S_MEMORY_MAP5_memory_map5_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map6 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP6_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP6_memory_map6_START (2)
#define SOC_SECENG_S_MEMORY_MAP6_memory_map6_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map7 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP7_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP7_memory_map7_START (2)
#define SOC_SECENG_S_MEMORY_MAP7_memory_map7_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map8 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP8_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP8_memory_map8_START (2)
#define SOC_SECENG_S_MEMORY_MAP8_memory_map8_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map9 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP9_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP9_memory_map9_START (2)
#define SOC_SECENG_S_MEMORY_MAP9_memory_map9_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map10 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP10_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP10_memory_map10_START (2)
#define SOC_SECENG_S_MEMORY_MAP10_memory_map10_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map11 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP11_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP11_memory_map11_START (2)
#define SOC_SECENG_S_MEMORY_MAP11_memory_map11_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map12 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP12_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP12_memory_map12_START (2)
#define SOC_SECENG_S_MEMORY_MAP12_memory_map12_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map13 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP13_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP13_memory_map13_START (2)
#define SOC_SECENG_S_MEMORY_MAP13_memory_map13_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map14 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP14_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP14_memory_map14_START (2)
#define SOC_SECENG_S_MEMORY_MAP14_memory_map14_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map15 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP15_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP15_memory_map15_START (2)
#define SOC_SECENG_S_MEMORY_MAP15_memory_map15_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map16 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP16_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP16_memory_map16_START (2)
#define SOC_SECENG_S_MEMORY_MAP16_memory_map16_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map17 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP17_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP17_memory_map17_START (2)
#define SOC_SECENG_S_MEMORY_MAP17_memory_map17_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map18 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP18_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP18_memory_map18_START (2)
#define SOC_SECENG_S_MEMORY_MAP18_memory_map18_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map19 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP19_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP19_memory_map19_START (2)
#define SOC_SECENG_S_MEMORY_MAP19_memory_map19_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map20 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP20_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP20_memory_map20_START (2)
#define SOC_SECENG_S_MEMORY_MAP20_memory_map20_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map21 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP21_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP21_memory_map21_START (2)
#define SOC_SECENG_S_MEMORY_MAP21_memory_map21_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map22 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP22_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP22_memory_map22_START (2)
#define SOC_SECENG_S_MEMORY_MAP22_memory_map22_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map23 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP23_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP23_memory_map23_START (2)
#define SOC_SECENG_S_MEMORY_MAP23_memory_map23_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map24 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP24_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP24_memory_map24_START (2)
#define SOC_SECENG_S_MEMORY_MAP24_memory_map24_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map25 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP25_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP25_memory_map25_START (2)
#define SOC_SECENG_S_MEMORY_MAP25_memory_map25_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map26 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP26_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP26_memory_map26_START (2)
#define SOC_SECENG_S_MEMORY_MAP26_memory_map26_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map27 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP27_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP27_memory_map27_START (2)
#define SOC_SECENG_S_MEMORY_MAP27_memory_map27_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map28 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP28_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP28_memory_map28_START (2)
#define SOC_SECENG_S_MEMORY_MAP28_memory_map28_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map29 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP29_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP29_memory_map29_START (2)
#define SOC_SECENG_S_MEMORY_MAP29_memory_map29_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map30 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP30_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP30_memory_map30_START (2)
#define SOC_SECENG_S_MEMORY_MAP30_memory_map30_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int memory_map31 : 10;
        unsigned int reserved_1 : 20;
    } reg;
} SOC_SECENG_S_MEMORY_MAP31_UNION;
#endif
#define SOC_SECENG_S_MEMORY_MAP31_memory_map31_START (2)
#define SOC_SECENG_S_MEMORY_MAP31_memory_map31_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tag : 6;
        unsigned int reg_r : 6;
        unsigned int reg_b : 6;
        unsigned int reg_a : 6;
        unsigned int len : 3;
        unsigned int opcode : 5;
    } reg;
} SOC_SECENG_S_OPCODE_UNION;
#endif
#define SOC_SECENG_S_OPCODE_tag_START (0)
#define SOC_SECENG_S_OPCODE_tag_END (5)
#define SOC_SECENG_S_OPCODE_reg_r_START (6)
#define SOC_SECENG_S_OPCODE_reg_r_END (11)
#define SOC_SECENG_S_OPCODE_reg_b_START (12)
#define SOC_SECENG_S_OPCODE_reg_b_END (17)
#define SOC_SECENG_S_OPCODE_reg_a_START (18)
#define SOC_SECENG_S_OPCODE_reg_a_END (23)
#define SOC_SECENG_S_OPCODE_len_START (24)
#define SOC_SECENG_S_OPCODE_len_END (26)
#define SOC_SECENG_S_OPCODE_opcode_START (27)
#define SOC_SECENG_S_OPCODE_opcode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int n_virtual_addr : 5;
        unsigned int np_virtual_addr : 5;
        unsigned int t0_virtual_addr : 5;
        unsigned int t1_virtual_addr : 5;
        unsigned int reserved : 12;
    } reg;
} SOC_SECENG_S_N_NP_T0_T1_ADDR_UNION;
#endif
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_n_virtual_addr_START (0)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_n_virtual_addr_END (4)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_np_virtual_addr_START (5)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_np_virtual_addr_END (9)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_t0_virtual_addr_START (10)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_t0_virtual_addr_END (14)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_t1_virtual_addr_START (15)
#define SOC_SECENG_S_N_NP_T0_T1_ADDR_t1_virtual_addr_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pipe_is_rdy : 1;
        unsigned int pka_busy : 1;
        unsigned int alu_out_zero : 1;
        unsigned int alu_modovrflw : 1;
        unsigned int div_by_zero : 1;
        unsigned int alu_carry : 1;
        unsigned int alu_sign_out : 1;
        unsigned int modinv_of_zero : 1;
        unsigned int pka_cpu_busy : 1;
        unsigned int opcode : 5;
        unsigned int tag : 6;
        unsigned int reserved : 12;
    } reg;
} SOC_SECENG_S_PKA_STATUS_UNION;
#endif
#define SOC_SECENG_S_PKA_STATUS_pipe_is_rdy_START (0)
#define SOC_SECENG_S_PKA_STATUS_pipe_is_rdy_END (0)
#define SOC_SECENG_S_PKA_STATUS_pka_busy_START (1)
#define SOC_SECENG_S_PKA_STATUS_pka_busy_END (1)
#define SOC_SECENG_S_PKA_STATUS_alu_out_zero_START (2)
#define SOC_SECENG_S_PKA_STATUS_alu_out_zero_END (2)
#define SOC_SECENG_S_PKA_STATUS_alu_modovrflw_START (3)
#define SOC_SECENG_S_PKA_STATUS_alu_modovrflw_END (3)
#define SOC_SECENG_S_PKA_STATUS_div_by_zero_START (4)
#define SOC_SECENG_S_PKA_STATUS_div_by_zero_END (4)
#define SOC_SECENG_S_PKA_STATUS_alu_carry_START (5)
#define SOC_SECENG_S_PKA_STATUS_alu_carry_END (5)
#define SOC_SECENG_S_PKA_STATUS_alu_sign_out_START (6)
#define SOC_SECENG_S_PKA_STATUS_alu_sign_out_END (6)
#define SOC_SECENG_S_PKA_STATUS_modinv_of_zero_START (7)
#define SOC_SECENG_S_PKA_STATUS_modinv_of_zero_END (7)
#define SOC_SECENG_S_PKA_STATUS_pka_cpu_busy_START (8)
#define SOC_SECENG_S_PKA_STATUS_pka_cpu_busy_END (8)
#define SOC_SECENG_S_PKA_STATUS_opcode_START (9)
#define SOC_SECENG_S_PKA_STATUS_opcode_END (13)
#define SOC_SECENG_S_PKA_STATUS_tag_START (14)
#define SOC_SECENG_S_PKA_STATUS_tag_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_sw_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_PKA_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_PKA_SW_RESET_pka_sw_reset_START (0)
#define SOC_SECENG_S_PKA_SW_RESET_pka_sw_reset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_l0 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_SECENG_S_PKA_L0_UNION;
#endif
#define SOC_SECENG_S_PKA_L0_pka_l0_START (0)
#define SOC_SECENG_S_PKA_L0_pka_l0_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_l1 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_SECENG_S_PKA_L1_UNION;
#endif
#define SOC_SECENG_S_PKA_L1_pka_l1_START (0)
#define SOC_SECENG_S_PKA_L1_pka_l1_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_l2 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_SECENG_S_PKA_L2_UNION;
#endif
#define SOC_SECENG_S_PKA_L2_pka_l2_START (0)
#define SOC_SECENG_S_PKA_L2_pka_l2_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_l3 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_SECENG_S_PKA_L3_UNION;
#endif
#define SOC_SECENG_S_PKA_L3_pka_l3_START (0)
#define SOC_SECENG_S_PKA_L3_pka_l3_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_l4 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_SECENG_S_PKA_L4_UNION;
#endif
#define SOC_SECENG_S_PKA_L4_pka_l4_START (0)
#define SOC_SECENG_S_PKA_L4_pka_l4_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_l5 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_SECENG_S_PKA_L5_UNION;
#endif
#define SOC_SECENG_S_PKA_L5_pka_l5_START (0)
#define SOC_SECENG_S_PKA_L5_pka_l5_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_l6 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_SECENG_S_PKA_L6_UNION;
#endif
#define SOC_SECENG_S_PKA_L6_pka_l6_START (0)
#define SOC_SECENG_S_PKA_L6_pka_l6_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_l7 : 13;
        unsigned int reserved : 19;
    } reg;
} SOC_SECENG_S_PKA_L7_UNION;
#endif
#define SOC_SECENG_S_PKA_L7_pka_l7_START (0)
#define SOC_SECENG_S_PKA_L7_pka_l7_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_pipe_rdy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_PKA_PIPE_RDY_UNION;
#endif
#define SOC_SECENG_S_PKA_PIPE_RDY_pka_pipe_rdy_START (0)
#define SOC_SECENG_S_PKA_PIPE_RDY_pka_pipe_rdy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_done : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_PKA_DONE_UNION;
#endif
#define SOC_SECENG_S_PKA_DONE_pka_done_START (0)
#define SOC_SECENG_S_PKA_DONE_pka_done_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_mon_select : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_SECENG_S_PKA_MON_SELECT_UNION;
#endif
#define SOC_SECENG_S_PKA_MON_SELECT_pka_mon_select_START (0)
#define SOC_SECENG_S_PKA_MON_SELECT_pka_mon_select_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_debug_reg_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_PKA_DEBUG_REG_EN_UNION;
#endif
#define SOC_SECENG_S_PKA_DEBUG_REG_EN_pka_debug_reg_en_START (0)
#define SOC_SECENG_S_PKA_DEBUG_REG_EN_pka_debug_reg_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int debug_cnt_addr : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_SECENG_S_DEBUG_CNT_ADDR_UNION;
#endif
#define SOC_SECENG_S_DEBUG_CNT_ADDR_debug_cnt_addr_START (0)
#define SOC_SECENG_S_DEBUG_CNT_ADDR_debug_cnt_addr_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_debug_halt : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_PKA_DEBUG_HALT_UNION;
#endif
#define SOC_SECENG_S_PKA_DEBUG_HALT_pka_debug_halt_START (0)
#define SOC_SECENG_S_PKA_DEBUG_HALT_pka_debug_halt_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_msb_addr : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_SECENG_S_PKA_MSB_ADDR_UNION;
#endif
#define SOC_SECENG_S_PKA_MSB_ADDR_pka_msb_addr_START (0)
#define SOC_SECENG_S_PKA_MSB_ADDR_pka_msb_addr_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pka_mon_read : 32;
    } reg;
} SOC_SECENG_S_PKA_MON_READ_UNION;
#endif
#define SOC_SECENG_S_PKA_MON_READ_pka_mon_read_START (0)
#define SOC_SECENG_S_PKA_MON_READ_pka_mon_read_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_valid_int_mask : 1;
        unsigned int autocorr_err_int_mask : 1;
        unsigned int crngt_err_int_mask : 1;
        unsigned int vn_err_int_mask : 1;
        unsigned int watchdog_int_mask : 1;
        unsigned int rng_dma_done_int : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_SECENG_S_RNG_IMR_UNION;
#endif
#define SOC_SECENG_S_RNG_IMR_ehr_valid_int_mask_START (0)
#define SOC_SECENG_S_RNG_IMR_ehr_valid_int_mask_END (0)
#define SOC_SECENG_S_RNG_IMR_autocorr_err_int_mask_START (1)
#define SOC_SECENG_S_RNG_IMR_autocorr_err_int_mask_END (1)
#define SOC_SECENG_S_RNG_IMR_crngt_err_int_mask_START (2)
#define SOC_SECENG_S_RNG_IMR_crngt_err_int_mask_END (2)
#define SOC_SECENG_S_RNG_IMR_vn_err_int_mask_START (3)
#define SOC_SECENG_S_RNG_IMR_vn_err_int_mask_END (3)
#define SOC_SECENG_S_RNG_IMR_watchdog_int_mask_START (4)
#define SOC_SECENG_S_RNG_IMR_watchdog_int_mask_END (4)
#define SOC_SECENG_S_RNG_IMR_rng_dma_done_int_START (5)
#define SOC_SECENG_S_RNG_IMR_rng_dma_done_int_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_valid : 1;
        unsigned int autocorr_err : 1;
        unsigned int crngt_err : 1;
        unsigned int vn_err : 1;
        unsigned int watchdog_int_mask : 1;
        unsigned int rng_dma_done : 1;
        unsigned int reserved_0 : 10;
        unsigned int reseeding_done : 1;
        unsigned int instantiation_done : 1;
        unsigned int final_update_done : 1;
        unsigned int output_ready : 1;
        unsigned int reseed_cntr_full : 1;
        unsigned int reseed_cntr_top_40 : 1;
        unsigned int prng_crngt_err : 1;
        unsigned int req_size : 1;
        unsigned int kat_err : 1;
        unsigned int which_kat_err : 2;
        unsigned int reserved_1 : 5;
    } reg;
} SOC_SECENG_S_RNG_ISR_UNION;
#endif
#define SOC_SECENG_S_RNG_ISR_ehr_valid_START (0)
#define SOC_SECENG_S_RNG_ISR_ehr_valid_END (0)
#define SOC_SECENG_S_RNG_ISR_autocorr_err_START (1)
#define SOC_SECENG_S_RNG_ISR_autocorr_err_END (1)
#define SOC_SECENG_S_RNG_ISR_crngt_err_START (2)
#define SOC_SECENG_S_RNG_ISR_crngt_err_END (2)
#define SOC_SECENG_S_RNG_ISR_vn_err_START (3)
#define SOC_SECENG_S_RNG_ISR_vn_err_END (3)
#define SOC_SECENG_S_RNG_ISR_watchdog_int_mask_START (4)
#define SOC_SECENG_S_RNG_ISR_watchdog_int_mask_END (4)
#define SOC_SECENG_S_RNG_ISR_rng_dma_done_START (5)
#define SOC_SECENG_S_RNG_ISR_rng_dma_done_END (5)
#define SOC_SECENG_S_RNG_ISR_reseeding_done_START (16)
#define SOC_SECENG_S_RNG_ISR_reseeding_done_END (16)
#define SOC_SECENG_S_RNG_ISR_instantiation_done_START (17)
#define SOC_SECENG_S_RNG_ISR_instantiation_done_END (17)
#define SOC_SECENG_S_RNG_ISR_final_update_done_START (18)
#define SOC_SECENG_S_RNG_ISR_final_update_done_END (18)
#define SOC_SECENG_S_RNG_ISR_output_ready_START (19)
#define SOC_SECENG_S_RNG_ISR_output_ready_END (19)
#define SOC_SECENG_S_RNG_ISR_reseed_cntr_full_START (20)
#define SOC_SECENG_S_RNG_ISR_reseed_cntr_full_END (20)
#define SOC_SECENG_S_RNG_ISR_reseed_cntr_top_40_START (21)
#define SOC_SECENG_S_RNG_ISR_reseed_cntr_top_40_END (21)
#define SOC_SECENG_S_RNG_ISR_prng_crngt_err_START (22)
#define SOC_SECENG_S_RNG_ISR_prng_crngt_err_END (22)
#define SOC_SECENG_S_RNG_ISR_req_size_START (23)
#define SOC_SECENG_S_RNG_ISR_req_size_END (23)
#define SOC_SECENG_S_RNG_ISR_kat_err_START (24)
#define SOC_SECENG_S_RNG_ISR_kat_err_END (24)
#define SOC_SECENG_S_RNG_ISR_which_kat_err_START (25)
#define SOC_SECENG_S_RNG_ISR_which_kat_err_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_valid : 1;
        unsigned int autocorr_err : 1;
        unsigned int crngt_err : 1;
        unsigned int vn_err : 1;
        unsigned int rng_watchdog : 1;
        unsigned int rng_dma_done : 1;
        unsigned int reserved_0 : 10;
        unsigned int reseeding_done : 1;
        unsigned int instantiation_done : 1;
        unsigned int final_update_done : 1;
        unsigned int output_ready : 1;
        unsigned int reseed_cntr_full : 1;
        unsigned int reseed_cntr_top_40 : 1;
        unsigned int prng_crngt_err : 1;
        unsigned int req_size : 1;
        unsigned int kat_err : 1;
        unsigned int which_kat_err : 2;
        unsigned int reserved_1 : 5;
    } reg;
} SOC_SECENG_S_RNG_ICR_UNION;
#endif
#define SOC_SECENG_S_RNG_ICR_ehr_valid_START (0)
#define SOC_SECENG_S_RNG_ICR_ehr_valid_END (0)
#define SOC_SECENG_S_RNG_ICR_autocorr_err_START (1)
#define SOC_SECENG_S_RNG_ICR_autocorr_err_END (1)
#define SOC_SECENG_S_RNG_ICR_crngt_err_START (2)
#define SOC_SECENG_S_RNG_ICR_crngt_err_END (2)
#define SOC_SECENG_S_RNG_ICR_vn_err_START (3)
#define SOC_SECENG_S_RNG_ICR_vn_err_END (3)
#define SOC_SECENG_S_RNG_ICR_rng_watchdog_START (4)
#define SOC_SECENG_S_RNG_ICR_rng_watchdog_END (4)
#define SOC_SECENG_S_RNG_ICR_rng_dma_done_START (5)
#define SOC_SECENG_S_RNG_ICR_rng_dma_done_END (5)
#define SOC_SECENG_S_RNG_ICR_reseeding_done_START (16)
#define SOC_SECENG_S_RNG_ICR_reseeding_done_END (16)
#define SOC_SECENG_S_RNG_ICR_instantiation_done_START (17)
#define SOC_SECENG_S_RNG_ICR_instantiation_done_END (17)
#define SOC_SECENG_S_RNG_ICR_final_update_done_START (18)
#define SOC_SECENG_S_RNG_ICR_final_update_done_END (18)
#define SOC_SECENG_S_RNG_ICR_output_ready_START (19)
#define SOC_SECENG_S_RNG_ICR_output_ready_END (19)
#define SOC_SECENG_S_RNG_ICR_reseed_cntr_full_START (20)
#define SOC_SECENG_S_RNG_ICR_reseed_cntr_full_END (20)
#define SOC_SECENG_S_RNG_ICR_reseed_cntr_top_40_START (21)
#define SOC_SECENG_S_RNG_ICR_reseed_cntr_top_40_END (21)
#define SOC_SECENG_S_RNG_ICR_prng_crngt_err_START (22)
#define SOC_SECENG_S_RNG_ICR_prng_crngt_err_END (22)
#define SOC_SECENG_S_RNG_ICR_req_size_START (23)
#define SOC_SECENG_S_RNG_ICR_req_size_END (23)
#define SOC_SECENG_S_RNG_ICR_kat_err_START (24)
#define SOC_SECENG_S_RNG_ICR_kat_err_END (24)
#define SOC_SECENG_S_RNG_ICR_which_kat_err_START (25)
#define SOC_SECENG_S_RNG_ICR_which_kat_err_END (26)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rnd_src_sel : 2;
        unsigned int sop_sel : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_SECENG_S_TRNG_CONFIG_UNION;
#endif
#define SOC_SECENG_S_TRNG_CONFIG_rnd_src_sel_START (0)
#define SOC_SECENG_S_TRNG_CONFIG_rnd_src_sel_END (1)
#define SOC_SECENG_S_TRNG_CONFIG_sop_sel_START (2)
#define SOC_SECENG_S_TRNG_CONFIG_sop_sel_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_valid : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_TRNG_VALID_UNION;
#endif
#define SOC_SECENG_S_TRNG_VALID_ehr_valid_START (0)
#define SOC_SECENG_S_TRNG_VALID_ehr_valid_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_data : 32;
    } reg;
} SOC_SECENG_S_EHR_DATA_0_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_0_ehr_data_START (0)
#define SOC_SECENG_S_EHR_DATA_0_ehr_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_data : 32;
    } reg;
} SOC_SECENG_S_EHR_DATA_1_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_1_ehr_data_START (0)
#define SOC_SECENG_S_EHR_DATA_1_ehr_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_data : 32;
    } reg;
} SOC_SECENG_S_EHR_DATA_2_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_2_ehr_data_START (0)
#define SOC_SECENG_S_EHR_DATA_2_ehr_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_data : 32;
    } reg;
} SOC_SECENG_S_EHR_DATA_3_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_3_ehr_data_START (0)
#define SOC_SECENG_S_EHR_DATA_3_ehr_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_data : 32;
    } reg;
} SOC_SECENG_S_EHR_DATA_4_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_4_ehr_data_START (0)
#define SOC_SECENG_S_EHR_DATA_4_ehr_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_data : 32;
    } reg;
} SOC_SECENG_S_EHR_DATA_5_UNION;
#endif
#define SOC_SECENG_S_EHR_DATA_5_ehr_data_START (0)
#define SOC_SECENG_S_EHR_DATA_5_ehr_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rnd_src_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_RND_SOURCE_ENABLE_UNION;
#endif
#define SOC_SECENG_S_RND_SOURCE_ENABLE_rnd_src_en_START (0)
#define SOC_SECENG_S_RND_SOURCE_ENABLE_rnd_src_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sample_cntr1 : 32;
    } reg;
} SOC_SECENG_S_SAMPLE_CNT1_UNION;
#endif
#define SOC_SECENG_S_SAMPLE_CNT1_sample_cntr1_START (0)
#define SOC_SECENG_S_SAMPLE_CNT1_sample_cntr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int autocorr_trys : 14;
        unsigned int autocorr_fails : 8;
        unsigned int reserved : 10;
    } reg;
} SOC_SECENG_S_AUTOCORR_STATISTIC_UNION;
#endif
#define SOC_SECENG_S_AUTOCORR_STATISTIC_autocorr_trys_START (0)
#define SOC_SECENG_S_AUTOCORR_STATISTIC_autocorr_trys_END (13)
#define SOC_SECENG_S_AUTOCORR_STATISTIC_autocorr_fails_START (14)
#define SOC_SECENG_S_AUTOCORR_STATISTIC_autocorr_fails_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int vnc_bypass : 1;
        unsigned int trng_crngt_bypass : 1;
        unsigned int auto_correlate_bypass : 1;
        unsigned int reserved_1 : 28;
    } reg;
} SOC_SECENG_S_TRNG_DEBUG_CONTROL_UNION;
#endif
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_vnc_bypass_START (1)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_vnc_bypass_END (1)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_trng_crngt_bypass_START (2)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_trng_crngt_bypass_END (2)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_auto_correlate_bypass_START (3)
#define SOC_SECENG_S_TRNG_DEBUG_CONTROL_auto_correlate_bypass_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rng_sw_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_RNG_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_RNG_SW_RESET_rng_sw_reset_START (0)
#define SOC_SECENG_S_RNG_SW_RESET_rng_sw_reset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rng_debug_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_RNG_DEBUG_EN_INPUT_UNION;
#endif
#define SOC_SECENG_S_RNG_DEBUG_EN_INPUT_rng_debug_en_START (0)
#define SOC_SECENG_S_RNG_DEBUG_EN_INPUT_rng_debug_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rng_busy : 1;
        unsigned int trng_busy : 1;
        unsigned int prng_busy : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_SECENG_S_RNG_BUSY_UNION;
#endif
#define SOC_SECENG_S_RNG_BUSY_rng_busy_START (0)
#define SOC_SECENG_S_RNG_BUSY_rng_busy_END (0)
#define SOC_SECENG_S_RNG_BUSY_trng_busy_START (1)
#define SOC_SECENG_S_RNG_BUSY_trng_busy_END (1)
#define SOC_SECENG_S_RNG_BUSY_prng_busy_START (2)
#define SOC_SECENG_S_RNG_BUSY_prng_busy_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rst_bits_counter : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_RST_BITS_COUNTER_UNION;
#endif
#define SOC_SECENG_S_RST_BITS_COUNTER_rst_bits_counter_START (0)
#define SOC_SECENG_S_RST_BITS_COUNTER_rst_bits_counter_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ehr_width_192 : 1;
        unsigned int crngt_exists : 1;
        unsigned int autocorr_exists : 1;
        unsigned int trng_tests_bypass_en : 1;
        unsigned int prng_exists : 1;
        unsigned int kat_exists : 1;
        unsigned int reseeding_exists : 1;
        unsigned int rng_use_5_sboxes : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_RNG_VERSION_UNION;
#endif
#define SOC_SECENG_S_RNG_VERSION_ehr_width_192_START (0)
#define SOC_SECENG_S_RNG_VERSION_ehr_width_192_END (0)
#define SOC_SECENG_S_RNG_VERSION_crngt_exists_START (1)
#define SOC_SECENG_S_RNG_VERSION_crngt_exists_END (1)
#define SOC_SECENG_S_RNG_VERSION_autocorr_exists_START (2)
#define SOC_SECENG_S_RNG_VERSION_autocorr_exists_END (2)
#define SOC_SECENG_S_RNG_VERSION_trng_tests_bypass_en_START (3)
#define SOC_SECENG_S_RNG_VERSION_trng_tests_bypass_en_END (3)
#define SOC_SECENG_S_RNG_VERSION_prng_exists_START (4)
#define SOC_SECENG_S_RNG_VERSION_prng_exists_END (4)
#define SOC_SECENG_S_RNG_VERSION_kat_exists_START (5)
#define SOC_SECENG_S_RNG_VERSION_kat_exists_END (5)
#define SOC_SECENG_S_RNG_VERSION_reseeding_exists_START (6)
#define SOC_SECENG_S_RNG_VERSION_reseeding_exists_END (6)
#define SOC_SECENG_S_RNG_VERSION_rng_use_5_sboxes_START (7)
#define SOC_SECENG_S_RNG_VERSION_rng_use_5_sboxes_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_RNG_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_RNG_CLK_ENABLE_en_START (0)
#define SOC_SECENG_S_RNG_CLK_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_RNG_DMA_ENABLE_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_ENABLE_en_START (0)
#define SOC_SECENG_S_RNG_DMA_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en_src_sel0 : 1;
        unsigned int en_src_sel1 : 1;
        unsigned int en_src_sel2 : 1;
        unsigned int en_src_sel3 : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_SECENG_S_RNG_DMA_SRC_MASK_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel0_START (0)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel0_END (0)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel1_START (1)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel1_END (1)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel2_START (2)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel2_END (2)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel3_START (3)
#define SOC_SECENG_S_RNG_DMA_SRC_MASK_en_src_sel3_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rng_sram_dma_addr : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_SECENG_S_RNG_DMA_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_SRAM_ADDR_rng_sram_dma_addr_START (0)
#define SOC_SECENG_S_RNG_DMA_SRAM_ADDR_rng_sram_dma_addr_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rng_samples_num : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_rng_samples_num_START (0)
#define SOC_SECENG_S_RNG_DMA_SAMPLES_NUM_rng_samples_num_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rng_watchdog_val : 32;
    } reg;
} SOC_SECENG_S_RNG_WATCHDOG_VAL_UNION;
#endif
#define SOC_SECENG_S_RNG_WATCHDOG_VAL_rng_watchdog_val_START (0)
#define SOC_SECENG_S_RNG_WATCHDOG_VAL_rng_watchdog_val_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rng_dma_busy : 1;
        unsigned int dma_src_sel : 2;
        unsigned int num_of_samples : 8;
        unsigned int reserved : 21;
    } reg;
} SOC_SECENG_S_RNG_DMA_STATUS_UNION;
#endif
#define SOC_SECENG_S_RNG_DMA_STATUS_rng_dma_busy_START (0)
#define SOC_SECENG_S_RNG_DMA_STATUS_rng_dma_busy_END (0)
#define SOC_SECENG_S_RNG_DMA_STATUS_dma_src_sel_START (1)
#define SOC_SECENG_S_RNG_DMA_STATUS_dma_src_sel_END (2)
#define SOC_SECENG_S_RNG_DMA_STATUS_num_of_samples_START (3)
#define SOC_SECENG_S_RNG_DMA_STATUS_num_of_samples_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_AES_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_AES_CLK_ENABLE_en_START (0)
#define SOC_SECENG_S_AES_CLK_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DES_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_DES_CLK_ENABLE_en_START (0)
#define SOC_SECENG_S_DES_CLK_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HASH_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_HASH_CLK_ENABLE_en_START (0)
#define SOC_SECENG_S_HASH_CLK_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_PKA_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_PKA_CLK_ENABLE_en_START (0)
#define SOC_SECENG_S_PKA_CLK_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DMA_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_S_DMA_CLK_ENABLE_en_START (0)
#define SOC_SECENG_S_DMA_CLK_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aes_clk_status : 1;
        unsigned int des_clk_status : 1;
        unsigned int hash_clk_status : 1;
        unsigned int pka_clk_status : 1;
        unsigned int reserved_0 : 4;
        unsigned int dma_clk_status : 1;
        unsigned int reserved_1 : 23;
    } reg;
} SOC_SECENG_S_CLK_STATUS_UNION;
#endif
#define SOC_SECENG_S_CLK_STATUS_aes_clk_status_START (0)
#define SOC_SECENG_S_CLK_STATUS_aes_clk_status_END (0)
#define SOC_SECENG_S_CLK_STATUS_des_clk_status_START (1)
#define SOC_SECENG_S_CLK_STATUS_des_clk_status_END (1)
#define SOC_SECENG_S_CLK_STATUS_hash_clk_status_START (2)
#define SOC_SECENG_S_CLK_STATUS_hash_clk_status_END (2)
#define SOC_SECENG_S_CLK_STATUS_pka_clk_status_START (3)
#define SOC_SECENG_S_CLK_STATUS_pka_clk_status_END (3)
#define SOC_SECENG_S_CLK_STATUS_dma_clk_status_START (8)
#define SOC_SECENG_S_CLK_STATUS_dma_clk_status_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_SECENG_S_CRYPTO_CTL_UNION;
#endif
#define SOC_SECENG_S_CRYPTO_CTL_mode_START (0)
#define SOC_SECENG_S_CRYPTO_CTL_mode_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crypto_busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_CRYPTO_BUSY_UNION;
#endif
#define SOC_SECENG_S_CRYPTO_BUSY_crypto_busy_START (0)
#define SOC_SECENG_S_CRYPTO_BUSY_crypto_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HASH_BUSY_UNION;
#endif
#define SOC_SECENG_S_HASH_BUSY_hash_busy_START (0)
#define SOC_SECENG_S_HASH_BUSY_hash_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int version : 32;
    } reg;
} SOC_SECENG_S_VERSION_UNION;
#endif
#define SOC_SECENG_S_VERSION_version_START (0)
#define SOC_SECENG_S_VERSION_version_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int context_id : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_CONTEXT_ID_UNION;
#endif
#define SOC_SECENG_S_CONTEXT_ID_context_id_START (0)
#define SOC_SECENG_S_CONTEXT_ID_context_id_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_compare_error_id_fifo0 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_UNION;
#endif
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_hash_compare_error_id_fifo0_START (0)
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO0_hash_compare_error_id_fifo0_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_compare_error_id_fifo1 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_UNION;
#endif
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_hash_compare_error_id_fifo1_START (0)
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO1_hash_compare_error_id_fifo1_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_compare_error_id_fifo2 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_UNION;
#endif
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_hash_compare_error_id_fifo2_START (0)
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO2_hash_compare_error_id_fifo2_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_compare_error_id_fifo3 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_UNION;
#endif
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_hash_compare_error_id_fifo3_START (0)
#define SOC_SECENG_S_HASH_COMPARE_ERR_ID_FIFO3_hash_compare_error_id_fifo3_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int dscrptr_completion_low_int : 1;
        unsigned int reserved_2 : 1;
        unsigned int sram_to_din_int : 1;
        unsigned int dout_to_sram_int : 1;
        unsigned int mem_to_din_int : 1;
        unsigned int dout_to_mem_int : 1;
        unsigned int axi_err_int : 1;
        unsigned int pka_exp_int : 1;
        unsigned int rng_int : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int dscrptr_watermark_int : 1;
        unsigned int dscrptr_watermark1_int : 1;
        unsigned int reserved_11 : 1;
        unsigned int hash_cmp_error_int : 1;
        unsigned int secure_timer_int : 1;
        unsigned int axim_comp_int : 1;
        unsigned int reserved_12 : 7;
    } reg;
} SOC_SECENG_S_HOST_RGF_IRR_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_completion_low_int_START (2)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_completion_low_int_END (2)
#define SOC_SECENG_S_HOST_RGF_IRR_sram_to_din_int_START (4)
#define SOC_SECENG_S_HOST_RGF_IRR_sram_to_din_int_END (4)
#define SOC_SECENG_S_HOST_RGF_IRR_dout_to_sram_int_START (5)
#define SOC_SECENG_S_HOST_RGF_IRR_dout_to_sram_int_END (5)
#define SOC_SECENG_S_HOST_RGF_IRR_mem_to_din_int_START (6)
#define SOC_SECENG_S_HOST_RGF_IRR_mem_to_din_int_END (6)
#define SOC_SECENG_S_HOST_RGF_IRR_dout_to_mem_int_START (7)
#define SOC_SECENG_S_HOST_RGF_IRR_dout_to_mem_int_END (7)
#define SOC_SECENG_S_HOST_RGF_IRR_axi_err_int_START (8)
#define SOC_SECENG_S_HOST_RGF_IRR_axi_err_int_END (8)
#define SOC_SECENG_S_HOST_RGF_IRR_pka_exp_int_START (9)
#define SOC_SECENG_S_HOST_RGF_IRR_pka_exp_int_END (9)
#define SOC_SECENG_S_HOST_RGF_IRR_rng_int_START (10)
#define SOC_SECENG_S_HOST_RGF_IRR_rng_int_END (10)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_watermark_int_START (19)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_watermark_int_END (19)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_watermark1_int_START (20)
#define SOC_SECENG_S_HOST_RGF_IRR_dscrptr_watermark1_int_END (20)
#define SOC_SECENG_S_HOST_RGF_IRR_hash_cmp_error_int_START (22)
#define SOC_SECENG_S_HOST_RGF_IRR_hash_cmp_error_int_END (22)
#define SOC_SECENG_S_HOST_RGF_IRR_secure_timer_int_START (23)
#define SOC_SECENG_S_HOST_RGF_IRR_secure_timer_int_END (23)
#define SOC_SECENG_S_HOST_RGF_IRR_axim_comp_int_START (24)
#define SOC_SECENG_S_HOST_RGF_IRR_axim_comp_int_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int dscrptr_completion_mask : 1;
        unsigned int reserved_2 : 1;
        unsigned int sram_to_din_mask : 1;
        unsigned int dout_to_sram_mask : 1;
        unsigned int mem_to_din_mask : 1;
        unsigned int dout_to_mem_mask : 1;
        unsigned int axi_err_mask : 1;
        unsigned int pka_exp_mask : 1;
        unsigned int rng_mask : 1;
        unsigned int reserved_3 : 8;
        unsigned int dscrptr_watermark_mask0 : 1;
        unsigned int dscrptr_watermark_mask1 : 1;
        unsigned int reserved_4 : 1;
        unsigned int hash_cmp_error : 1;
        unsigned int secure_timer_int_mask : 1;
        unsigned int axim_comp_int_mask : 1;
        unsigned int reserved_5 : 7;
    } reg;
} SOC_SECENG_S_HOST_RGF_IMR_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_completion_mask_START (2)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_completion_mask_END (2)
#define SOC_SECENG_S_HOST_RGF_IMR_sram_to_din_mask_START (4)
#define SOC_SECENG_S_HOST_RGF_IMR_sram_to_din_mask_END (4)
#define SOC_SECENG_S_HOST_RGF_IMR_dout_to_sram_mask_START (5)
#define SOC_SECENG_S_HOST_RGF_IMR_dout_to_sram_mask_END (5)
#define SOC_SECENG_S_HOST_RGF_IMR_mem_to_din_mask_START (6)
#define SOC_SECENG_S_HOST_RGF_IMR_mem_to_din_mask_END (6)
#define SOC_SECENG_S_HOST_RGF_IMR_dout_to_mem_mask_START (7)
#define SOC_SECENG_S_HOST_RGF_IMR_dout_to_mem_mask_END (7)
#define SOC_SECENG_S_HOST_RGF_IMR_axi_err_mask_START (8)
#define SOC_SECENG_S_HOST_RGF_IMR_axi_err_mask_END (8)
#define SOC_SECENG_S_HOST_RGF_IMR_pka_exp_mask_START (9)
#define SOC_SECENG_S_HOST_RGF_IMR_pka_exp_mask_END (9)
#define SOC_SECENG_S_HOST_RGF_IMR_rng_mask_START (10)
#define SOC_SECENG_S_HOST_RGF_IMR_rng_mask_END (10)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_watermark_mask0_START (19)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_watermark_mask0_END (19)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_watermark_mask1_START (20)
#define SOC_SECENG_S_HOST_RGF_IMR_dscrptr_watermark_mask1_END (20)
#define SOC_SECENG_S_HOST_RGF_IMR_hash_cmp_error_START (22)
#define SOC_SECENG_S_HOST_RGF_IMR_hash_cmp_error_END (22)
#define SOC_SECENG_S_HOST_RGF_IMR_secure_timer_int_mask_START (23)
#define SOC_SECENG_S_HOST_RGF_IMR_secure_timer_int_mask_END (23)
#define SOC_SECENG_S_HOST_RGF_IMR_axim_comp_int_mask_START (24)
#define SOC_SECENG_S_HOST_RGF_IMR_axim_comp_int_mask_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int dscrptr_completion_clear : 1;
        unsigned int reserved_2 : 1;
        unsigned int sram_to_din_clear : 1;
        unsigned int dout_to_sram_clear : 1;
        unsigned int mem_to_din_clear : 1;
        unsigned int dout_to_mem_clear : 1;
        unsigned int axi_err_clear : 1;
        unsigned int pka_exp_clear : 1;
        unsigned int rng_int_clear : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int dscrptr_watermark_queue0_clear : 1;
        unsigned int dscrptr_watermark_queue1_clear : 1;
        unsigned int reserved_11 : 1;
        unsigned int hash_cmp_error_clear : 1;
        unsigned int secure_timer_int_clear : 1;
        unsigned int axim_comp_int_clear : 1;
        unsigned int reserved_12 : 7;
    } reg;
} SOC_SECENG_S_HOST_RGF_ICR_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_completion_clear_START (2)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_completion_clear_END (2)
#define SOC_SECENG_S_HOST_RGF_ICR_sram_to_din_clear_START (4)
#define SOC_SECENG_S_HOST_RGF_ICR_sram_to_din_clear_END (4)
#define SOC_SECENG_S_HOST_RGF_ICR_dout_to_sram_clear_START (5)
#define SOC_SECENG_S_HOST_RGF_ICR_dout_to_sram_clear_END (5)
#define SOC_SECENG_S_HOST_RGF_ICR_mem_to_din_clear_START (6)
#define SOC_SECENG_S_HOST_RGF_ICR_mem_to_din_clear_END (6)
#define SOC_SECENG_S_HOST_RGF_ICR_dout_to_mem_clear_START (7)
#define SOC_SECENG_S_HOST_RGF_ICR_dout_to_mem_clear_END (7)
#define SOC_SECENG_S_HOST_RGF_ICR_axi_err_clear_START (8)
#define SOC_SECENG_S_HOST_RGF_ICR_axi_err_clear_END (8)
#define SOC_SECENG_S_HOST_RGF_ICR_pka_exp_clear_START (9)
#define SOC_SECENG_S_HOST_RGF_ICR_pka_exp_clear_END (9)
#define SOC_SECENG_S_HOST_RGF_ICR_rng_int_clear_START (10)
#define SOC_SECENG_S_HOST_RGF_ICR_rng_int_clear_END (10)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_watermark_queue0_clear_START (19)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_watermark_queue0_clear_END (19)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_watermark_queue1_clear_START (20)
#define SOC_SECENG_S_HOST_RGF_ICR_dscrptr_watermark_queue1_clear_END (20)
#define SOC_SECENG_S_HOST_RGF_ICR_hash_cmp_error_clear_START (22)
#define SOC_SECENG_S_HOST_RGF_ICR_hash_cmp_error_clear_END (22)
#define SOC_SECENG_S_HOST_RGF_ICR_secure_timer_int_clear_START (23)
#define SOC_SECENG_S_HOST_RGF_ICR_secure_timer_int_clear_END (23)
#define SOC_SECENG_S_HOST_RGF_ICR_axim_comp_int_clear_START (24)
#define SOC_SECENG_S_HOST_RGF_ICR_axim_comp_int_clear_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 3;
        unsigned int dout_wr_bg : 1;
        unsigned int reserved_1 : 3;
        unsigned int din_rd_bg : 1;
        unsigned int reserved_2 : 3;
        unsigned int dout_wr_wbg : 1;
        unsigned int reserved_3 : 3;
        unsigned int din_rd_wbg : 1;
        unsigned int reserved_4 : 16;
    } reg;
} SOC_SECENG_S_HOST_RGF_ENDIAN_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_ENDIAN_dout_wr_bg_START (3)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_dout_wr_bg_END (3)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_din_rd_bg_START (7)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_din_rd_bg_END (7)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_dout_wr_wbg_START (11)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_dout_wr_wbg_END (11)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_din_rd_wbg_START (15)
#define SOC_SECENG_S_HOST_RGF_ENDIAN_din_rd_wbg_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cc_sw_rst_req : 1;
        unsigned int cc_sw_rst_force : 1;
        unsigned int axis_sysreq : 1;
        unsigned int axim_sysreq : 1;
        unsigned int reserved : 28;
    } reg;
} SOC_SECENG_S_HOST_RGF_CC_SW_RST_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_cc_sw_rst_req_START (0)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_cc_sw_rst_req_END (0)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_cc_sw_rst_force_START (1)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_cc_sw_rst_force_END (1)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_axis_sysreq_START (2)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_axis_sysreq_END (2)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_axim_sysreq_START (3)
#define SOC_SECENG_S_HOST_RGF_CC_SW_RST_axim_sysreq_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_signature : 32;
    } reg;
} SOC_SECENG_S_HOST_RGF_SIGNATURE_UNION;
#endif
#define SOC_SECENG_S_HOST_RGF_SIGNATURE_host_signature_START (0)
#define SOC_SECENG_S_HOST_RGF_SIGNATURE_host_signature_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int power_gating_exists : 1;
        unsigned int large_rkek : 1;
        unsigned int hask_in_fuses : 1;
        unsigned int ext_mem_secured : 1;
        unsigned int reserved_0 : 1;
        unsigned int rkek_ecc_exists_n : 1;
        unsigned int sram_size : 3;
        unsigned int dscrptr_exists : 1;
        unsigned int pau__exists : 1;
        unsigned int rng_exists : 1;
        unsigned int pka_exists : 1;
        unsigned int reserved_1 : 1;
        unsigned int sha_512_prsnt : 1;
        unsigned int sha_256_prsnt : 1;
        unsigned int md5_prsnt : 1;
        unsigned int hash_exists : 1;
        unsigned int reserved_2 : 1;
        unsigned int des_exists : 1;
        unsigned int aes_xcbc_mac_exists : 1;
        unsigned int aes_cmac_exists : 1;
        unsigned int aes_ccm_exists : 1;
        unsigned int aes_xex_hw_t_calc : 1;
        unsigned int aes_xex_exists : 1;
        unsigned int ctr_exists : 1;
        unsigned int aes_din_byte_resolution : 1;
        unsigned int tunneling_enb : 1;
        unsigned int support_256_192_key : 1;
        unsigned int only_encrypt : 1;
        unsigned int aes_exists : 1;
        unsigned int reserved_3 : 1;
    } reg;
} SOC_SECENG_S_HOST_BOOT_UNION;
#endif
#define SOC_SECENG_S_HOST_BOOT_power_gating_exists_START (0)
#define SOC_SECENG_S_HOST_BOOT_power_gating_exists_END (0)
#define SOC_SECENG_S_HOST_BOOT_large_rkek_START (1)
#define SOC_SECENG_S_HOST_BOOT_large_rkek_END (1)
#define SOC_SECENG_S_HOST_BOOT_hask_in_fuses_START (2)
#define SOC_SECENG_S_HOST_BOOT_hask_in_fuses_END (2)
#define SOC_SECENG_S_HOST_BOOT_ext_mem_secured_START (3)
#define SOC_SECENG_S_HOST_BOOT_ext_mem_secured_END (3)
#define SOC_SECENG_S_HOST_BOOT_rkek_ecc_exists_n_START (5)
#define SOC_SECENG_S_HOST_BOOT_rkek_ecc_exists_n_END (5)
#define SOC_SECENG_S_HOST_BOOT_sram_size_START (6)
#define SOC_SECENG_S_HOST_BOOT_sram_size_END (8)
#define SOC_SECENG_S_HOST_BOOT_dscrptr_exists_START (9)
#define SOC_SECENG_S_HOST_BOOT_dscrptr_exists_END (9)
#define SOC_SECENG_S_HOST_BOOT_pau__exists_START (10)
#define SOC_SECENG_S_HOST_BOOT_pau__exists_END (10)
#define SOC_SECENG_S_HOST_BOOT_rng_exists_START (11)
#define SOC_SECENG_S_HOST_BOOT_rng_exists_END (11)
#define SOC_SECENG_S_HOST_BOOT_pka_exists_START (12)
#define SOC_SECENG_S_HOST_BOOT_pka_exists_END (12)
#define SOC_SECENG_S_HOST_BOOT_sha_512_prsnt_START (14)
#define SOC_SECENG_S_HOST_BOOT_sha_512_prsnt_END (14)
#define SOC_SECENG_S_HOST_BOOT_sha_256_prsnt_START (15)
#define SOC_SECENG_S_HOST_BOOT_sha_256_prsnt_END (15)
#define SOC_SECENG_S_HOST_BOOT_md5_prsnt_START (16)
#define SOC_SECENG_S_HOST_BOOT_md5_prsnt_END (16)
#define SOC_SECENG_S_HOST_BOOT_hash_exists_START (17)
#define SOC_SECENG_S_HOST_BOOT_hash_exists_END (17)
#define SOC_SECENG_S_HOST_BOOT_des_exists_START (19)
#define SOC_SECENG_S_HOST_BOOT_des_exists_END (19)
#define SOC_SECENG_S_HOST_BOOT_aes_xcbc_mac_exists_START (20)
#define SOC_SECENG_S_HOST_BOOT_aes_xcbc_mac_exists_END (20)
#define SOC_SECENG_S_HOST_BOOT_aes_cmac_exists_START (21)
#define SOC_SECENG_S_HOST_BOOT_aes_cmac_exists_END (21)
#define SOC_SECENG_S_HOST_BOOT_aes_ccm_exists_START (22)
#define SOC_SECENG_S_HOST_BOOT_aes_ccm_exists_END (22)
#define SOC_SECENG_S_HOST_BOOT_aes_xex_hw_t_calc_START (23)
#define SOC_SECENG_S_HOST_BOOT_aes_xex_hw_t_calc_END (23)
#define SOC_SECENG_S_HOST_BOOT_aes_xex_exists_START (24)
#define SOC_SECENG_S_HOST_BOOT_aes_xex_exists_END (24)
#define SOC_SECENG_S_HOST_BOOT_ctr_exists_START (25)
#define SOC_SECENG_S_HOST_BOOT_ctr_exists_END (25)
#define SOC_SECENG_S_HOST_BOOT_aes_din_byte_resolution_START (26)
#define SOC_SECENG_S_HOST_BOOT_aes_din_byte_resolution_END (26)
#define SOC_SECENG_S_HOST_BOOT_tunneling_enb_START (27)
#define SOC_SECENG_S_HOST_BOOT_tunneling_enb_END (27)
#define SOC_SECENG_S_HOST_BOOT_support_256_192_key_START (28)
#define SOC_SECENG_S_HOST_BOOT_support_256_192_key_END (28)
#define SOC_SECENG_S_HOST_BOOT_only_encrypt_START (29)
#define SOC_SECENG_S_HOST_BOOT_only_encrypt_END (29)
#define SOC_SECENG_S_HOST_BOOT_aes_exists_START (30)
#define SOC_SECENG_S_HOST_BOOT_aes_exists_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int provision_mask : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_PROVISION_CONST_MASK_UNION;
#endif
#define SOC_SECENG_S_HOST_PROVISION_CONST_MASK_provision_mask_START (0)
#define SOC_SECENG_S_HOST_PROVISION_CONST_MASK_provision_mask_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sel_crypto_key : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_SECENG_S_HOST_CRYPTOKEY_SEL_UNION;
#endif
#define SOC_SECENG_S_HOST_CRYPTOKEY_SEL_sel_crypto_key_START (0)
#define SOC_SECENG_S_HOST_CRYPTOKEY_SEL_sel_crypto_key_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_cry_access_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_UNION;
#endif
#define SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_host_cry_access_en_START (0)
#define SOC_SECENG_S_HOST_HOST_CRY_ACCESS_EN_host_cry_access_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int secure_CPU_dbgen_en : 1;
        unsigned int secure_CPU_niden_en : 1;
        unsigned int secure_CPU_spiden_en : 1;
        unsigned int secure_CPU_spniden_en : 1;
        unsigned int switch_CPU_dbgen_en : 1;
        unsigned int switch_CPU_niden_en : 1;
        unsigned int switch_CPU_spiden_en : 1;
        unsigned int switch_CPU_spniden_en : 1;
        unsigned int nonsecure_CPU_dbgen_en : 1;
        unsigned int nonsecure_CPU_niden_en : 1;
        unsigned int nonsecure_CPU_spiden_en : 1;
        unsigned int nonsecure_CPU_spniden_en : 1;
        unsigned int reserved_0 : 5;
        unsigned int ivp_dsp_dbgen_en : 1;
        unsigned int hifi_dsp_dbgen_en : 1;
        unsigned int BBE16_dsp_dbgen_en : 1;
        unsigned int coresight_deviceen_en : 1;
        unsigned int coresight_dbgen_en : 1;
        unsigned int coresight_niden_en : 1;
        unsigned int coresight_spiden_en : 1;
        unsigned int coresight_spniden_en : 1;
        unsigned int reserved_1 : 6;
        unsigned int lock_bit : 1;
    } reg;
} SOC_SECENG_S_HOST_DCU_EN_UNION;
#endif
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_dbgen_en_START (0)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_dbgen_en_END (0)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_niden_en_START (1)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_niden_en_END (1)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_spiden_en_START (2)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_spiden_en_END (2)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_spniden_en_START (3)
#define SOC_SECENG_S_HOST_DCU_EN_secure_CPU_spniden_en_END (3)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_dbgen_en_START (4)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_dbgen_en_END (4)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_niden_en_START (5)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_niden_en_END (5)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_spiden_en_START (6)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_spiden_en_END (6)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_spniden_en_START (7)
#define SOC_SECENG_S_HOST_DCU_EN_switch_CPU_spniden_en_END (7)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_dbgen_en_START (8)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_dbgen_en_END (8)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_niden_en_START (9)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_niden_en_END (9)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_spiden_en_START (10)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_spiden_en_END (10)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_spniden_en_START (11)
#define SOC_SECENG_S_HOST_DCU_EN_nonsecure_CPU_spniden_en_END (11)
#define SOC_SECENG_S_HOST_DCU_EN_ivp_dsp_dbgen_en_START (17)
#define SOC_SECENG_S_HOST_DCU_EN_ivp_dsp_dbgen_en_END (17)
#define SOC_SECENG_S_HOST_DCU_EN_hifi_dsp_dbgen_en_START (18)
#define SOC_SECENG_S_HOST_DCU_EN_hifi_dsp_dbgen_en_END (18)
#define SOC_SECENG_S_HOST_DCU_EN_BBE16_dsp_dbgen_en_START (19)
#define SOC_SECENG_S_HOST_DCU_EN_BBE16_dsp_dbgen_en_END (19)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_deviceen_en_START (20)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_deviceen_en_END (20)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_dbgen_en_START (21)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_dbgen_en_END (21)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_niden_en_START (22)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_niden_en_END (22)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_spiden_en_START (23)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_spiden_en_END (23)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_spniden_en_START (24)
#define SOC_SECENG_S_HOST_DCU_EN_coresight_spniden_en_END (24)
#define SOC_SECENG_S_HOST_DCU_EN_lock_bit_START (31)
#define SOC_SECENG_S_HOST_DCU_EN_lock_bit_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_secure_timer_bist_kick : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_UNION;
#endif
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_host_secure_timer_bist_kick_START (0)
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_KICK_host_secure_timer_bist_kick_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_secure_timer_bist_val : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_UNION;
#endif
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_host_secure_timer_bist_val_START (0)
#define SOC_SECENG_S_HOST_SECURE_TIMER_BIST_VAL_host_secure_timer_bist_val_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_cc_ao_test : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_CC_AO_TEST_UNION;
#endif
#define SOC_SECENG_S_HOST_CC_AO_TEST_host_cc_ao_test_START (0)
#define SOC_SECENG_S_HOST_CC_AO_TEST_host_cc_ao_test_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_low_res_secure_timer_rst : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_UNION;
#endif
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_host_low_res_secure_timer_rst_START (0)
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_RST_host_low_res_secure_timer_rst_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_low_res_secure_timer_0 : 32;
    } reg;
} SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_UNION;
#endif
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_host_low_res_secure_timer_0_START (0)
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_0_host_low_res_secure_timer_0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_low_res_secure_timer_1 : 32;
    } reg;
} SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_UNION;
#endif
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_host_low_res_secure_timer_1_START (0)
#define SOC_SECENG_S_HOST_LOW_RES_SECURE_TIMER_1_host_low_res_secure_timer_1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_high_res_secure_timer_rst : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_host_high_res_secure_timer_rst_START (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_RST_host_high_res_secure_timer_rst_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_high_res_secure_timer_0 : 32;
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_host_high_res_secure_timer_0_START (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_0_host_high_res_secure_timer_0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_high_res_secure_timer_1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_host_high_res_secure_timer_1_START (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_1_host_high_res_secure_timer_1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_high_res_secure_timer_th_0 : 32;
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_host_high_res_secure_timer_th_0_START (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_0_host_high_res_secure_timer_th_0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_high_res_secure_timer_th_1 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_UNION;
#endif
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_host_high_res_secure_timer_th_1_START (0)
#define SOC_SECENG_S_HOST_HIGH_RES_SECURE_TIMER_TH_1_host_high_res_secure_timer_th_1_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_latched_external_timer_0 : 32;
    } reg;
} SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_UNION;
#endif
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_host_latched_external_timer_0_START (0)
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_0_host_latched_external_timer_0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_latched_external_timer_1 : 32;
    } reg;
} SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_UNION;
#endif
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_host_latched_external_timer_1_START (0)
#define SOC_SECENG_S_HOST_LATCHED_EXTERNAL_TIMER_1_host_latched_external_timer_1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int large_rkek_local : 1;
        unsigned int hash_in_fuses_local : 1;
        unsigned int reserved_1 : 29;
    } reg;
} SOC_SECENG_S_NVM_CC_BOOT_UNION;
#endif
#define SOC_SECENG_S_NVM_CC_BOOT_large_rkek_local_START (1)
#define SOC_SECENG_S_NVM_CC_BOOT_large_rkek_local_END (1)
#define SOC_SECENG_S_NVM_CC_BOOT_hash_in_fuses_local_START (2)
#define SOC_SECENG_S_NVM_CC_BOOT_hash_in_fuses_local_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_aib_addr_reg : 12;
        unsigned int reserved_0 : 4;
        unsigned int read_access : 1;
        unsigned int write_access : 1;
        unsigned int reserved_1 : 14;
    } reg;
} SOC_SECENG_S_HOST_AIB_ADDR_REG_UNION;
#endif
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_host_aib_addr_reg_START (0)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_host_aib_addr_reg_END (11)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_read_access_START (16)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_read_access_END (16)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_write_access_START (17)
#define SOC_SECENG_S_HOST_AIB_ADDR_REG_write_access_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_aib_wdata_reg : 32;
    } reg;
} SOC_SECENG_S_HOST_AIB_WDATA_REG_UNION;
#endif
#define SOC_SECENG_S_HOST_AIB_WDATA_REG_host_aib_wdata_reg_START (0)
#define SOC_SECENG_S_HOST_AIB_WDATA_REG_host_aib_wdata_reg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_aib_rdata_reg : 32;
    } reg;
} SOC_SECENG_S_HOST_AIB_RDATA_REG_UNION;
#endif
#define SOC_SECENG_S_HOST_AIB_RDATA_REG_host_aib_rdata_reg_START (0)
#define SOC_SECENG_S_HOST_AIB_RDATA_REG_host_aib_rdata_reg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aib_fuse_prog_completed : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_UNION;
#endif
#define SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_aib_fuse_prog_completed_START (0)
#define SOC_SECENG_S_AIB_FUSE_PROG_COMPLETED_aib_fuse_prog_completed_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int aib_fuse_ack_reg : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_AIB_FUSE_ACK_UNION;
#endif
#define SOC_SECENG_S_AIB_FUSE_ACK_aib_fuse_ack_reg_START (0)
#define SOC_SECENG_S_AIB_FUSE_ACK_aib_fuse_ack_reg_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int forbidden_cpu_access : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_AIB_DEBUG_STATUS_UNION;
#endif
#define SOC_SECENG_S_AIB_DEBUG_STATUS_forbidden_cpu_access_START (0)
#define SOC_SECENG_S_AIB_DEBUG_STATUS_forbidden_cpu_access_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lcs_is_valid_reg : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_LCS_IS_VALID_UNION;
#endif
#define SOC_SECENG_S_LCS_IS_VALID_lcs_is_valid_reg_START (0)
#define SOC_SECENG_S_LCS_IS_VALID_lcs_is_valid_reg_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int session_key0_reg : 32;
    } reg;
} SOC_SECENG_S_HOST_SESSION_KEY0_UNION;
#endif
#define SOC_SECENG_S_HOST_SESSION_KEY0_session_key0_reg_START (0)
#define SOC_SECENG_S_HOST_SESSION_KEY0_session_key0_reg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int session_key1_reg : 32;
    } reg;
} SOC_SECENG_S_HOST_SESSION_KEY1_UNION;
#endif
#define SOC_SECENG_S_HOST_SESSION_KEY1_session_key1_reg_START (0)
#define SOC_SECENG_S_HOST_SESSION_KEY1_session_key1_reg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int session_key2_reg : 32;
    } reg;
} SOC_SECENG_S_HOST_SESSION_KEY2_UNION;
#endif
#define SOC_SECENG_S_HOST_SESSION_KEY2_session_key2_reg_START (0)
#define SOC_SECENG_S_HOST_SESSION_KEY2_session_key2_reg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int session_key3_reg : 32;
    } reg;
} SOC_SECENG_S_HOST_SESSION_KEY3_UNION;
#endif
#define SOC_SECENG_S_HOST_SESSION_KEY3_session_key3_reg_START (0)
#define SOC_SECENG_S_HOST_SESSION_KEY3_session_key3_reg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int session_key_is_valid : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_UNION;
#endif
#define SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_session_key_is_valid_START (0)
#define SOC_SECENG_S_HOST_SEESION_KEY_IS_VALID_session_key_is_valid_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lcs_reg : 8;
        unsigned int error_kdr_zero_cnt : 1;
        unsigned int error_prov_zero_cnt : 1;
        unsigned int reserved : 22;
    } reg;
} SOC_SECENG_S_LCS_REG_UNION;
#endif
#define SOC_SECENG_S_LCS_REG_lcs_reg_START (0)
#define SOC_SECENG_S_LCS_REG_lcs_reg_END (7)
#define SOC_SECENG_S_LCS_REG_error_kdr_zero_cnt_START (8)
#define SOC_SECENG_S_LCS_REG_error_kdr_zero_cnt_END (8)
#define SOC_SECENG_S_LCS_REG_error_prov_zero_cnt_START (9)
#define SOC_SECENG_S_LCS_REG_error_prov_zero_cnt_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_security_disable : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_UNION;
#endif
#define SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_host_security_disable_START (0)
#define SOC_SECENG_S_HOST_CPC_SECURITY_DISABLE_host_security_disable_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ao_cc_state_counter : 32;
    } reg;
} SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_UNION;
#endif
#define SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_ao_cc_state_counter_START (0)
#define SOC_SECENG_S_HOST_AO_CC_STATE_COUNTER_ao_cc_state_counter_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cc_ao_state_counter_inc : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_UNION;
#endif
#define SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_cc_ao_state_counter_inc_START (0)
#define SOC_SECENG_S_HOST_CC_AO_STATE_COUNTER_INC_cc_ao_state_counter_inc_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ao_cc_lcs_is_sd : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_AO_CC_IS_SD_UNION;
#endif
#define SOC_SECENG_S_HOST_AO_CC_IS_SD_ao_cc_lcs_is_sd_START (0)
#define SOC_SECENG_S_HOST_AO_CC_IS_SD_ao_cc_lcs_is_sd_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_rma_rkek_write : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_HOST_RMA_RKEK_WR_UNION;
#endif
#define SOC_SECENG_S_HOST_RMA_RKEK_WR_host_rma_rkek_write_START (0)
#define SOC_SECENG_S_HOST_RMA_RKEK_WR_host_rma_rkek_write_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT0_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT0_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT0_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT1_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT1_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT1_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT2_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT2_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT2_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT3_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT3_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT3_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT4_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT4_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT4_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT5_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT5_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT5_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT8_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT8_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT8_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT9_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT9_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT9_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT10_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT10_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT10_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHT11_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHT11_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHT11_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST0_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST1_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST2_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST3_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST4_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST5_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST8_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST9_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST10_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_inflightcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_INFLIGHTLAST11_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pid_broken1 : 1;
        unsigned int pid_broken2 : 1;
        unsigned int pid_oscntr : 8;
        unsigned int pid_id : 5;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_S_AXIM_PIDTABLE0_UNION;
#endif
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_broken1_START (0)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_broken1_END (0)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_broken2_START (1)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_broken2_END (1)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_oscntr_START (2)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_oscntr_END (9)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_id_START (10)
#define SOC_SECENG_S_AXIM_PIDTABLE0_pid_id_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pid_broken1 : 1;
        unsigned int pid_broken2 : 1;
        unsigned int pid_oscntr : 8;
        unsigned int pid_id : 5;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_S_AXIM_PIDTABLE1_UNION;
#endif
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_broken1_START (0)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_broken1_END (0)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_broken2_START (1)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_broken2_END (1)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_oscntr_START (2)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_oscntr_END (9)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_id_START (10)
#define SOC_SECENG_S_AXIM_PIDTABLE1_pid_id_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pid_broken1 : 1;
        unsigned int pid_broken2 : 1;
        unsigned int pid_oscntr : 8;
        unsigned int pid_id : 5;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_S_AXIM_PIDTABLE2_UNION;
#endif
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_broken1_START (0)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_broken1_END (0)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_broken2_START (1)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_broken2_END (1)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_oscntr_START (2)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_oscntr_END (9)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_id_START (10)
#define SOC_SECENG_S_AXIM_PIDTABLE2_pid_id_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pid_broken1 : 1;
        unsigned int pid_broken2 : 1;
        unsigned int pid_oscntr : 8;
        unsigned int pid_id : 5;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_S_AXIM_PIDTABLE3_UNION;
#endif
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_broken1_START (0)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_broken1_END (0)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_broken2_START (1)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_broken2_END (1)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_oscntr_START (2)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_oscntr_END (9)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_id_START (10)
#define SOC_SECENG_S_AXIM_PIDTABLE3_pid_id_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP0_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP0_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP0_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP1_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP1_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP1_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP2_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP2_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP2_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP3_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP3_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP3_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP4_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP4_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP4_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP5_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP5_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP5_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP8_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP8_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP8_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP9_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP9_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP9_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP10_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP10_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP10_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_AXIM_MON_COMP11_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_COMP11_complastcntr_START (0)
#define SOC_SECENG_S_AXIM_MON_COMP11_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rmax : 32;
    } reg;
} SOC_SECENG_S_AXIM_MON_RMAX_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_RMAX_rmax_START (0)
#define SOC_SECENG_S_AXIM_MON_RMAX_rmax_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rmin : 32;
    } reg;
} SOC_SECENG_S_AXIM_MON_RMIN_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_RMIN_rmin_START (0)
#define SOC_SECENG_S_AXIM_MON_RMIN_rmin_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wmax : 32;
    } reg;
} SOC_SECENG_S_AXIM_MON_WMAX_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_WMAX_wmax_START (0)
#define SOC_SECENG_S_AXIM_MON_WMAX_wmax_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wmin : 32;
    } reg;
} SOC_SECENG_S_AXIM_MON_WMIN_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_WMIN_wmin_START (0)
#define SOC_SECENG_S_AXIM_MON_WMIN_wmin_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bresp : 2;
        unsigned int bid : 4;
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 9;
        unsigned int rresp : 2;
        unsigned int rid : 4;
        unsigned int reserved_2: 10;
    } reg;
} SOC_SECENG_S_AXIM_MON_ERR_UNION;
#endif
#define SOC_SECENG_S_AXIM_MON_ERR_bresp_START (0)
#define SOC_SECENG_S_AXIM_MON_ERR_bresp_END (1)
#define SOC_SECENG_S_AXIM_MON_ERR_bid_START (2)
#define SOC_SECENG_S_AXIM_MON_ERR_bid_END (5)
#define SOC_SECENG_S_AXIM_MON_ERR_rresp_START (16)
#define SOC_SECENG_S_AXIM_MON_ERR_rresp_END (17)
#define SOC_SECENG_S_AXIM_MON_ERR_rid_START (18)
#define SOC_SECENG_S_AXIM_MON_ERR_rid_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int oscntr : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_SECENG_S_AXIM_RDSTAT_UNION;
#endif
#define SOC_SECENG_S_AXIM_RDSTAT_oscntr_START (0)
#define SOC_SECENG_S_AXIM_RDSTAT_oscntr_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rlatency : 32;
    } reg;
} SOC_SECENG_S_AXIM_RLATENCY_UNION;
#endif
#define SOC_SECENG_S_AXIM_RLATENCY_rlatency_START (0)
#define SOC_SECENG_S_AXIM_RLATENCY_rlatency_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rburst : 32;
    } reg;
} SOC_SECENG_S_AXIM_RBURST_UNION;
#endif
#define SOC_SECENG_S_AXIM_RBURST_rburst_START (0)
#define SOC_SECENG_S_AXIM_RBURST_rburst_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wlatency : 32;
    } reg;
} SOC_SECENG_S_AXIM_WLATENCY_UNION;
#endif
#define SOC_SECENG_S_AXIM_WLATENCY_wlatency_START (0)
#define SOC_SECENG_S_AXIM_WLATENCY_wlatency_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wburst : 32;
    } reg;
} SOC_SECENG_S_AXIM_WBURST_UNION;
#endif
#define SOC_SECENG_S_AXIM_WBURST_wburst_START (0)
#define SOC_SECENG_S_AXIM_WBURST_wburst_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int reserved_1 : 4;
        unsigned int dd_arcache : 4;
        unsigned int reserved_2 : 4;
        unsigned int reserved_3 : 4;
        unsigned int reserved_4 : 4;
        unsigned int dd_awcache : 4;
        unsigned int reserved_5 : 4;
    } reg;
} SOC_SECENG_S_AXIM_CACHETYPE_CFG_UNION;
#endif
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_dd_arcache_START (8)
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_dd_arcache_END (11)
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_dd_awcache_START (24)
#define SOC_SECENG_S_AXIM_CACHETYPE_CFG_dd_awcache_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 2;
        unsigned int reserved_1: 2;
        unsigned int dd_arprot : 1;
        unsigned int reserved_2: 3;
        unsigned int reserved_3: 2;
        unsigned int reserved_4: 2;
        unsigned int dd_awprot : 1;
        unsigned int reserved_5: 3;
        unsigned int reserved_6: 16;
    } reg;
} SOC_SECENG_S_AXIM_PROT_CFG_UNION;
#endif
#define SOC_SECENG_S_AXIM_PROT_CFG_dd_arprot_START (4)
#define SOC_SECENG_S_AXIM_PROT_CFG_dd_arprot_END (4)
#define SOC_SECENG_S_AXIM_PROT_CFG_dd_awprot_START (12)
#define SOC_SECENG_S_AXIM_PROT_CFG_dd_awprot_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rd_after_wr_stall : 4;
        unsigned int brespmask : 1;
        unsigned int rrespmask : 1;
        unsigned int infltmask : 1;
        unsigned int compmask : 1;
        unsigned int reserved_0 : 8;
        unsigned int accum_limit : 5;
        unsigned int reserved_1 : 11;
    } reg;
} SOC_SECENG_S_AXIM_CFG1_UNION;
#endif
#define SOC_SECENG_S_AXIM_CFG1_rd_after_wr_stall_START (0)
#define SOC_SECENG_S_AXIM_CFG1_rd_after_wr_stall_END (3)
#define SOC_SECENG_S_AXIM_CFG1_brespmask_START (4)
#define SOC_SECENG_S_AXIM_CFG1_brespmask_END (4)
#define SOC_SECENG_S_AXIM_CFG1_rrespmask_START (5)
#define SOC_SECENG_S_AXIM_CFG1_rrespmask_END (5)
#define SOC_SECENG_S_AXIM_CFG1_infltmask_START (6)
#define SOC_SECENG_S_AXIM_CFG1_infltmask_END (6)
#define SOC_SECENG_S_AXIM_CFG1_compmask_START (7)
#define SOC_SECENG_S_AXIM_CFG1_compmask_END (7)
#define SOC_SECENG_S_AXIM_CFG1_accum_limit_START (16)
#define SOC_SECENG_S_AXIM_CFG1_accum_limit_END (20)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ardomain : 2;
        unsigned int awdomain : 2;
        unsigned int arbar : 2;
        unsigned int awbar : 2;
        unsigned int arsnoop : 4;
        unsigned int awsnoop_not_aligned : 3;
        unsigned int awsnoop_aligned : 3;
        unsigned int awaddr_not_masked : 7;
        unsigned int awlen_val : 4;
        unsigned int reserved : 3;
    } reg;
} SOC_SECENG_S_AXIM_ACE_CONST_UNION;
#endif
#define SOC_SECENG_S_AXIM_ACE_CONST_ardomain_START (0)
#define SOC_SECENG_S_AXIM_ACE_CONST_ardomain_END (1)
#define SOC_SECENG_S_AXIM_ACE_CONST_awdomain_START (2)
#define SOC_SECENG_S_AXIM_ACE_CONST_awdomain_END (3)
#define SOC_SECENG_S_AXIM_ACE_CONST_arbar_START (4)
#define SOC_SECENG_S_AXIM_ACE_CONST_arbar_END (5)
#define SOC_SECENG_S_AXIM_ACE_CONST_awbar_START (6)
#define SOC_SECENG_S_AXIM_ACE_CONST_awbar_END (7)
#define SOC_SECENG_S_AXIM_ACE_CONST_arsnoop_START (8)
#define SOC_SECENG_S_AXIM_ACE_CONST_arsnoop_END (11)
#define SOC_SECENG_S_AXIM_ACE_CONST_awsnoop_not_aligned_START (12)
#define SOC_SECENG_S_AXIM_ACE_CONST_awsnoop_not_aligned_END (14)
#define SOC_SECENG_S_AXIM_ACE_CONST_awsnoop_aligned_START (15)
#define SOC_SECENG_S_AXIM_ACE_CONST_awsnoop_aligned_END (17)
#define SOC_SECENG_S_AXIM_ACE_CONST_awaddr_not_masked_START (18)
#define SOC_SECENG_S_AXIM_ACE_CONST_awaddr_not_masked_END (24)
#define SOC_SECENG_S_AXIM_ACE_CONST_awlen_val_START (25)
#define SOC_SECENG_S_AXIM_ACE_CONST_awlen_val_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int awcache_last : 4;
        unsigned int awcache : 4;
        unsigned int arcache : 4;
        unsigned int reserved : 20;
    } reg;
} SOC_SECENG_S_AXIM_CACHE_PARAMS_UNION;
#endif
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_awcache_last_START (0)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_awcache_last_END (3)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_awcache_START (4)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_awcache_END (7)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_arcache_START (8)
#define SOC_SECENG_S_AXIM_CACHE_PARAMS_arcache_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_axim_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_SECENG_S_ADDR_AXIM_CTRL_UNION;
#endif
#define SOC_SECENG_S_ADDR_AXIM_CTRL_addr_axim_ctrl_START (0)
#define SOC_SECENG_S_ADDR_AXIM_CTRL_addr_axim_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_buffer_data : 32;
    } reg;
} SOC_SECENG_S_DIN_BUFFER_UNION;
#endif
#define SOC_SECENG_S_DIN_BUFFER_din_buffer_data_START (0)
#define SOC_SECENG_S_DIN_BUFFER_din_buffer_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_mem_dma_busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DIN_MEM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_S_DIN_MEM_DMA_BUSY_din_mem_dma_busy_START (0)
#define SOC_SECENG_S_DIN_MEM_DMA_BUSY_din_mem_dma_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int src_lli_sram_addr : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_S_SRC_LLI_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_S_SRC_LLI_SRAM_ADDR_src_lli_sram_addr_START (0)
#define SOC_SECENG_S_SRC_LLI_SRAM_ADDR_src_lli_sram_addr_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int src_lli_word0 : 32;
    } reg;
} SOC_SECENG_S_SRC_LLI_WORD0_UNION;
#endif
#define SOC_SECENG_S_SRC_LLI_WORD0_src_lli_word0_START (0)
#define SOC_SECENG_S_SRC_LLI_WORD0_src_lli_word0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bytes_num : 30;
        unsigned int first : 1;
        unsigned int last : 1;
    } reg;
} SOC_SECENG_S_SRC_LLI_WORD1_UNION;
#endif
#define SOC_SECENG_S_SRC_LLI_WORD1_bytes_num_START (0)
#define SOC_SECENG_S_SRC_LLI_WORD1_bytes_num_END (29)
#define SOC_SECENG_S_SRC_LLI_WORD1_first_START (30)
#define SOC_SECENG_S_SRC_LLI_WORD1_first_END (30)
#define SOC_SECENG_S_SRC_LLI_WORD1_last_START (31)
#define SOC_SECENG_S_SRC_LLI_WORD1_last_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_source : 32;
    } reg;
} SOC_SECENG_S_SRAM_SRC_ADDR_UNION;
#endif
#define SOC_SECENG_S_SRAM_SRC_ADDR_sram_source_START (0)
#define SOC_SECENG_S_SRAM_SRC_ADDR_sram_source_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bytes_len : 32;
    } reg;
} SOC_SECENG_S_DIN_SRAM_BYTES_LEN_UNION;
#endif
#define SOC_SECENG_S_DIN_SRAM_BYTES_LEN_bytes_len_START (0)
#define SOC_SECENG_S_DIN_SRAM_BYTES_LEN_bytes_len_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DIN_SRAM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_S_DIN_SRAM_DMA_BUSY_busy_START (0)
#define SOC_SECENG_S_DIN_SRAM_DMA_BUSY_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_din_endianness : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DIN_SRAM_ENDIANNESS_UNION;
#endif
#define SOC_SECENG_S_DIN_SRAM_ENDIANNESS_sram_din_endianness_START (0)
#define SOC_SECENG_S_DIN_SRAM_ENDIANNESS_sram_din_endianness_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rdid : 4;
        unsigned int reserved_0: 4;
        unsigned int prot : 2;
        unsigned int reserved_1: 22;
    } reg;
} SOC_SECENG_S_AXI_CPU_DIN_PARAMS_UNION;
#endif
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_rdid_START (0)
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_rdid_END (3)
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_prot_START (8)
#define SOC_SECENG_S_AXI_CPU_DIN_PARAMS_prot_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int kick_sw_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DIN_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_DIN_SW_RESET_kick_sw_reset_START (0)
#define SOC_SECENG_S_DIN_SW_RESET_kick_sw_reset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_din_size : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_DIN_CPU_DATA_SIZE_UNION;
#endif
#define SOC_SECENG_S_DIN_CPU_DATA_SIZE_cpu_din_size_START (0)
#define SOC_SECENG_S_DIN_CPU_DATA_SIZE_cpu_din_size_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int last : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_WRITE_ALIGN_LAST_UNION;
#endif
#define SOC_SECENG_S_WRITE_ALIGN_LAST_last_START (0)
#define SOC_SECENG_S_WRITE_ALIGN_LAST_last_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int empty : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_FIFO_IN_EMPTY_UNION;
#endif
#define SOC_SECENG_S_FIFO_IN_EMPTY_empty_START (0)
#define SOC_SECENG_S_FIFO_IN_EMPTY_empty_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int disable_outstd_req : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DISABLE_OUTSTD_REQ_UNION;
#endif
#define SOC_SECENG_S_DISABLE_OUTSTD_REQ_disable_outstd_req_START (0)
#define SOC_SECENG_S_DISABLE_OUTSTD_REQ_disable_outstd_req_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rst : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DIN_FIFO_RST_PNTR_UNION;
#endif
#define SOC_SECENG_S_DIN_FIFO_RST_PNTR_rst_START (0)
#define SOC_SECENG_S_DIN_FIFO_RST_PNTR_rst_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_buffer_data : 32;
    } reg;
} SOC_SECENG_S_DOUT_BUFFER_UNION;
#endif
#define SOC_SECENG_S_DOUT_BUFFER_dout_buffer_data_START (0)
#define SOC_SECENG_S_DOUT_BUFFER_dout_buffer_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_mem_dma_busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DOUT_MEM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_S_DOUT_MEM_DMA_BUSY_dout_mem_dma_busy_START (0)
#define SOC_SECENG_S_DOUT_MEM_DMA_BUSY_dout_mem_dma_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dst_lli_sram_addr : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_S_DST_LLI_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_S_DST_LLI_SRAM_ADDR_dst_lli_sram_addr_START (0)
#define SOC_SECENG_S_DST_LLI_SRAM_ADDR_dst_lli_sram_addr_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dst_lli_word0 : 32;
    } reg;
} SOC_SECENG_S_DST_LLI_WORD0_UNION;
#endif
#define SOC_SECENG_S_DST_LLI_WORD0_dst_lli_word0_START (0)
#define SOC_SECENG_S_DST_LLI_WORD0_dst_lli_word0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bytes_num : 30;
        unsigned int first : 1;
        unsigned int last : 1;
    } reg;
} SOC_SECENG_S_DST_LLI_WORD1_UNION;
#endif
#define SOC_SECENG_S_DST_LLI_WORD1_bytes_num_START (0)
#define SOC_SECENG_S_DST_LLI_WORD1_bytes_num_END (29)
#define SOC_SECENG_S_DST_LLI_WORD1_first_START (30)
#define SOC_SECENG_S_DST_LLI_WORD1_first_END (30)
#define SOC_SECENG_S_DST_LLI_WORD1_last_START (31)
#define SOC_SECENG_S_DST_LLI_WORD1_last_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_dest : 32;
    } reg;
} SOC_SECENG_S_SRAM_DEST_ADDR_UNION;
#endif
#define SOC_SECENG_S_SRAM_DEST_ADDR_sram_dest_START (0)
#define SOC_SECENG_S_SRAM_DEST_ADDR_sram_dest_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bytes_len : 32;
    } reg;
} SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_UNION;
#endif
#define SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_bytes_len_START (0)
#define SOC_SECENG_S_DOUT_SRAM_BYTES_LEN_bytes_len_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_busy_START (0)
#define SOC_SECENG_S_DOUT_SRAM_DMA_BUSY_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_sram_endianness : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_UNION;
#endif
#define SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_dout_sram_endianness_START (0)
#define SOC_SECENG_S_DOUT_SRAM_ENDIANNESS_dout_sram_endianness_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int last : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_READ_ALIGN_LAST_UNION;
#endif
#define SOC_SECENG_S_READ_ALIGN_LAST_last_START (0)
#define SOC_SECENG_S_READ_ALIGN_LAST_last_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_fifo_empty : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DOUT_FIFO_EMPTY_UNION;
#endif
#define SOC_SECENG_S_DOUT_FIFO_EMPTY_dout_fifo_empty_START (0)
#define SOC_SECENG_S_DOUT_FIFO_EMPTY_dout_fifo_empty_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cache_type : 4;
        unsigned int reserved_0 : 4;
        unsigned int reserved_1 : 4;
        unsigned int wrid : 4;
        unsigned int prot : 2;
        unsigned int force_cpu_params : 1;
        unsigned int reserved_2 : 13;
    } reg;
} SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_UNION;
#endif
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_cache_type_START (0)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_cache_type_END (3)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_wrid_START (12)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_wrid_END (15)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_prot_START (16)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_prot_END (17)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_force_cpu_params_START (18)
#define SOC_SECENG_S_AXI_CPU_DOUT_PARAMS_force_cpu_params_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_sw_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DOUT_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_DOUT_SW_RESET_dout_sw_reset_START (0)
#define SOC_SECENG_S_DOUT_SW_RESET_dout_sw_reset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int completion_counter : 6;
        unsigned int overflow_counter : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_completion_counter_START (0)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_completion_counter_END (5)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_overflow_counter_START (6)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER0_overflow_counter_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int completion_counter : 6;
        unsigned int overflow_counter : 1;
        unsigned int reserved : 25;
    } reg;
} SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_completion_counter_START (0)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_completion_counter_END (5)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_overflow_counter_START (6)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_COUNTER1_overflow_counter_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int completion_counter_status : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_completion_counter_status_START (0)
#define SOC_SECENG_S_DSCRPTR_COMPLETION_STATUS_completion_counter_status_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dscrptr_sw_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DSCRPTR_SW_RESET_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_SW_RESET_dscrptr_sw_reset_START (0)
#define SOC_SECENG_S_DSCRPTR_SW_RESET_dscrptr_sw_reset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dscrptr_debug_mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DSCRPTR_DEBUG_MODE_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_DEBUG_MODE_dscrptr_debug_mode_START (0)
#define SOC_SECENG_S_DSCRPTR_DEBUG_MODE_dscrptr_debug_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dscrptr_single_addr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_dscrptr_single_addr_START (0)
#define SOC_SECENG_S_DSCRPTR_SINGLE_ADDR_EN_dscrptr_single_addr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int measure_cntr : 32;
    } reg;
} SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_measure_cntr_START (0)
#define SOC_SECENG_S_DSCRPTR_MEASURE_CNTR_measure_cntr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dropped_address_high : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_dropped_address_high_START (0)
#define SOC_SECENG_S_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_dropped_address_high_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_dma_address : 32;
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_din_dma_address_START (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD0_din_dma_address_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_dma_mode : 2;
        unsigned int din_size : 24;
        unsigned int ns_bit : 1;
        unsigned int din_const_value : 1;
        unsigned int not_last : 1;
        unsigned int lock_queue : 1;
        unsigned int din_virtual_host : 2;
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_dma_mode_START (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_dma_mode_END (1)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_size_START (2)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_size_END (25)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_ns_bit_START (26)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_ns_bit_END (26)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_const_value_START (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_const_value_END (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_not_last_START (28)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_not_last_END (28)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_lock_queue_START (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_lock_queue_END (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_virtual_host_START (30)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD1_din_virtual_host_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_dma_address : 32;
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_dout_dma_address_START (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD2_dout_dma_address_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_dma_mode : 2;
        unsigned int dout_size : 24;
        unsigned int ns_bit : 1;
        unsigned int dout_last_ind : 1;
        unsigned int reserved : 1;
        unsigned int hash_xor_bit : 1;
        unsigned int dout_virtual_host : 2;
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_dma_mode_START (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_dma_mode_END (1)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_size_START (2)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_size_END (25)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_ns_bit_START (26)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_ns_bit_END (26)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_last_ind_START (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_last_ind_END (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_hash_xor_bit_START (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_hash_xor_bit_END (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_virtual_host_START (30)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD3_dout_virtual_host_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_flow_mode : 6;
        unsigned int reserved : 1;
        unsigned int aes_xor_crypto_key : 1;
        unsigned int ack_needed : 2;
        unsigned int cipher_mode : 4;
        unsigned int cmac_size0 : 1;
        unsigned int cipher_do : 2;
        unsigned int cipher_conf0 : 2;
        unsigned int cipher_conf1 : 1;
        unsigned int cipher_conf2 : 2;
        unsigned int key_size : 2;
        unsigned int setup_operation : 4;
        unsigned int din_sram_endianness : 1;
        unsigned int dout_sram_endianness : 1;
        unsigned int word_swap : 1;
        unsigned int bytes_swap : 1;
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_data_flow_mode_START (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_data_flow_mode_END (5)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_aes_xor_crypto_key_START (7)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_aes_xor_crypto_key_END (7)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_ack_needed_START (8)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_ack_needed_END (9)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_mode_START (10)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_mode_END (13)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cmac_size0_START (14)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cmac_size0_END (14)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_do_START (15)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_do_END (16)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf0_START (17)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf0_END (18)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf1_START (19)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf1_END (19)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf2_START (20)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_cipher_conf2_END (21)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_key_size_START (22)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_key_size_END (23)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_setup_operation_START (24)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_setup_operation_END (27)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_din_sram_endianness_START (28)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_din_sram_endianness_END (28)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_dout_sram_endianness_START (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_dout_sram_endianness_END (29)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_word_swap_START (30)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_word_swap_END (30)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_bytes_swap_START (31)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD4_bytes_swap_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_addr_high : 16;
        unsigned int din_addr_high : 16;
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_dout_addr_high_START (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_dout_addr_high_END (15)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_din_addr_high_START (16)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WORD5_din_addr_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int watermark : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_watermark_START (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_WATERMARK_watermark_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int queue0_content : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_UNION;
#endif
#define SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_queue0_content_START (0)
#define SOC_SECENG_S_DSCRPTR_QUEUE0_CONTENT_queue0_content_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_data : 32;
    } reg;
} SOC_SECENG_S_SRAM_DATA_UNION;
#endif
#define SOC_SECENG_S_SRAM_DATA_sram_data_START (0)
#define SOC_SECENG_S_SRAM_DATA_sram_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_addr : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_S_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_S_SRAM_ADDR_sram_addr_START (0)
#define SOC_SECENG_S_SRAM_ADDR_sram_addr_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_ready : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_S_SRAM_DATA_READY_UNION;
#endif
#define SOC_SECENG_S_SRAM_DATA_READY_sram_ready_START (0)
#define SOC_SECENG_S_SRAM_DATA_READY_sram_ready_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
