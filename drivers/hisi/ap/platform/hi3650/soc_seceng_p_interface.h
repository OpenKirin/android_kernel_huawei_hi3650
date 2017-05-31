#ifndef __SOC_SECENG_P_INTERFACE_H__
#define __SOC_SECENG_P_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_SECENG_P_AES_CLK_ENABLE_ADDR(base) ((base) + (0x00810))
#define SOC_SECENG_P_DES_CLK_ENABLE_ADDR(base) ((base) + (0x00814))
#define SOC_SECENG_P_HASH_CLK_ENABLE_ADDR(base) ((base) + (0x00818))
#define SOC_SECENG_P_DMA_CLK_ENABLE_ADDR(base) ((base) + (0x00820))
#define SOC_SECENG_P_CLK_STATUS_ADDR(base) ((base) + (0x00824))
#define SOC_SECENG_P_CRYPTO_CTL_ADDR(base) ((base) + (0x00900))
#define SOC_SECENG_P_CRYPTO_BUSY_ADDR(base) ((base) + (0x00910))
#define SOC_SECENG_P_HASH_BUSY_ADDR(base) ((base) + (0x0091C))
#define SOC_SECENG_P_VERSION_ADDR(base) ((base) + (0x00928))
#define SOC_SECENG_P_CONTEXT_ID_ADDR(base) ((base) + (0x00930))
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_ADDR(base) ((base) + (0x00940))
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_ADDR(base) ((base) + (0x00944))
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_ADDR(base) ((base) + (0x00948))
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_ADDR(base) ((base) + (0x0094C))
#define SOC_SECENG_P_HOST_IRR_ADDR(base) ((base) + (0x00A00))
#define SOC_SECENG_P_HOST_IMR_ADDR(base) ((base) + (0x00A04))
#define SOC_SECENG_P_HOST_ICR_ADDR(base) ((base) + (0x00A08))
#define SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_ADDR(base) ((base) + (0x00A10))
#define SOC_SECENG_P_HOST_SEP_BUSY_ADDR(base) ((base) + (0x00A14))
#define SOC_SECENG_P_HOST_SEP_SW_MONITOR_ADDR(base) ((base) + (0x00A20))
#define SOC_SECENG_P_HOST_CC_SW_RST_ADDR(base) ((base) + (0x00A40))
#define SOC_SECENG_P_HOST_SEP_HOST_GPR0_ADDR(base) ((base) + (0x00A80))
#define SOC_SECENG_P_HOST_HOST_SEP_GPR0_ADDR(base) ((base) + (0x00A84))
#define SOC_SECENG_P_HOST_SEP_HOST_GPR1_ADDR(base) ((base) + (0x00A88))
#define SOC_SECENG_P_HOST_HOST_SEP_GPR1_ADDR(base) ((base) + (0x00A8C))
#define SOC_SECENG_P_HOST_SEP_HOST_GPR2_ADDR(base) ((base) + (0x00A90))
#define SOC_SECENG_P_HOST_HOST_SEP_GPR2_ADDR(base) ((base) + (0x00A94))
#define SOC_SECENG_P_HOST_SEP_HOST_GPR3_ADDR(base) ((base) + (0x00A98))
#define SOC_SECENG_P_HOST_HOST_SEP_GPR3_ADDR(base) ((base) + (0x00A9C))
#define SOC_SECENG_P_HOST_SEP_HOST_GPR4_ADDR(base) ((base) + (0x00AA0))
#define SOC_SECENG_P_HOST_HOST_SEP_GPR4_ADDR(base) ((base) + (0x00AA4))
#define SOC_SECENG_P_HOST_SEP_HOST_GPR5_ADDR(base) ((base) + (0x00AA8))
#define SOC_SECENG_P_HOST_HOST_SEP_GPR5_ADDR(base) ((base) + (0x00AAC))
#define SOC_SECENG_P_HOST_SEP_HOST_GPR6_ADDR(base) ((base) + (0x00AB0))
#define SOC_SECENG_P_HOST_HOST_SEP_GPR6_ADDR(base) ((base) + (0x00AB4))
#define SOC_SECENG_P_HOST_SEP_HOST_GPR7_ADDR(base) ((base) + (0x00AB8))
#define SOC_SECENG_P_HOST_HOST_SEP_GPR7_ADDR(base) ((base) + (0x00ABC))
#define SOC_SECENG_P_HOST_CC_SIGNATURE_ADDR(base) ((base) + (0x00AC8))
#define SOC_SECENG_P_HOST_HOST_ENDIAN_ADDR(base) ((base) + (0x00AD0))
#define SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_ADDR(base) ((base) + (0x0AD4))
#define SOC_SECENG_P_HOST_VERSION_ADDR(base) ((base) + (0x0AD8))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT0_ADDR(base) ((base) + (0x00B00))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT1_ADDR(base) ((base) + (0x00B04))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT2_ADDR(base) ((base) + (0x00B08))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT3_ADDR(base) ((base) + (0x00B0C))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT4_ADDR(base) ((base) + (0x00B10))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT5_ADDR(base) ((base) + (0x00B14))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT8_ADDR(base) ((base) + (0x00B20))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT9_ADDR(base) ((base) + (0x00B24))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT10_ADDR(base) ((base) + (0x00B28))
#define SOC_SECENG_P_AXIM_MON_INFLIGHT11_ADDR(base) ((base) + (0x00B2C))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_ADDR(base) ((base) + (0x00B40))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_ADDR(base) ((base) + (0x00B44))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_ADDR(base) ((base) + (0x00B48))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_ADDR(base) ((base) + (0x00B4C))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_ADDR(base) ((base) + (0x00B50))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_ADDR(base) ((base) + (0x00B54))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_ADDR(base) ((base) + (0x00B60))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_ADDR(base) ((base) + (0x00B64))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_ADDR(base) ((base) + (0x00B68))
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_ADDR(base) ((base) + (0x00B6C))
#define SOC_SECENG_P_AXIM_PIDTABLE0_ADDR(base) ((base) + (0x00B70))
#define SOC_SECENG_P_AXIM_PIDTABLE1_ADDR(base) ((base) + (0x00B74))
#define SOC_SECENG_P_AXIM_PIDTABLE2_ADDR(base) ((base) + (0x00B78))
#define SOC_SECENG_P_AXIM_PIDTABLE3_ADDR(base) ((base) + (0x00B7C))
#define SOC_SECENG_P_AXIM_MON_COMP0_ADDR(base) ((base) + (0x00B80))
#define SOC_SECENG_P_AXIM_MON_COMP1_ADDR(base) ((base) + (0x00B84))
#define SOC_SECENG_P_AXIM_MON_COMP2_ADDR(base) ((base) + (0x00B88))
#define SOC_SECENG_P_AXIM_MON_COMP3_ADDR(base) ((base) + (0x00B8C))
#define SOC_SECENG_P_AXIM_MON_COMP4_ADDR(base) ((base) + (0x00B90))
#define SOC_SECENG_P_AXIM_MON_COMP5_ADDR(base) ((base) + (0x00B94))
#define SOC_SECENG_P_AXIM_MON_COMP8_ADDR(base) ((base) + (0x00BA0))
#define SOC_SECENG_P_AXIM_MON_COMP9_ADDR(base) ((base) + (0x00BA4))
#define SOC_SECENG_P_AXIM_MON_COMP10_ADDR(base) ((base) + (0x00BA8))
#define SOC_SECENG_P_AXIM_MON_COMP11_ADDR(base) ((base) + (0x00BAC))
#define SOC_SECENG_P_AXIM_MON_RMAX_ADDR(base) ((base) + (0x00BB4))
#define SOC_SECENG_P_AXIM_MON_RMIN_ADDR(base) ((base) + (0x00BB8))
#define SOC_SECENG_P_AXIM_MON_WMAX_ADDR(base) ((base) + (0x00BBC))
#define SOC_SECENG_P_AXIM_MON_WMIN_ADDR(base) ((base) + (0x00BC0))
#define SOC_SECENG_P_AXIM_MON_ERR_ADDR(base) ((base) + (0x00BC4))
#define SOC_SECENG_P_AXIM_RDSTAT_ADDR(base) ((base) + (0x00BC8))
#define SOC_SECENG_P_AXIM_RLATENCY_ADDR(base) ((base) + (0x00BD0))
#define SOC_SECENG_P_AXIM_RBURST_ADDR(base) ((base) + (0x00BD4))
#define SOC_SECENG_P_AXIM_WLATENCY_ADDR(base) ((base) + (0x00BD8))
#define SOC_SECENG_P_AXIM_WBURST_ADDR(base) ((base) + (0x00BDC))
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_ADDR(base) ((base) + (0x00BE0))
#define SOC_SECENG_P_AXIM_PROT_CFG_ADDR(base) ((base) + (0x00BE4))
#define SOC_SECENG_P_AXIM_CFG1_ADDR(base) ((base) + (0x00BE8))
#define SOC_SECENG_P_AXIM_ACE_CONST_ADDR(base) ((base) + (0x0BEC))
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_ADDR(base) ((base) + (0x0BF0))
#define SOC_SECENG_P_ADDR_AXIM_CTRL_ADDR(base) ((base) + (0x0BF4))
#define SOC_SECENG_P_DIN_BUFFER_ADDR(base) ((base) + (0x00C00))
#define SOC_SECENG_P_DIN_MEM_DMA_BUSY_ADDR(base) ((base) + (0x00C20))
#define SOC_SECENG_P_SRC_LLI_SRAM_ADDR_ADDR(base) ((base) + (0x00C24))
#define SOC_SECENG_P_SRC_LLI_WORD0_ADDR(base) ((base) + (0x00C28))
#define SOC_SECENG_P_SRC_LLI_WORD1_ADDR(base) ((base) + (0x00C2C))
#define SOC_SECENG_P_SRAM_SRC_ADDR_ADDR(base) ((base) + (0x00C30))
#define SOC_SECENG_P_DIN_SRAM_BYTES_LEN_ADDR(base) ((base) + (0x00C34))
#define SOC_SECENG_P_DIN_SRAM_DMA_BUSY_ADDR(base) ((base) + (0x00C38))
#define SOC_SECENG_P_DIN_SRAM_ENDIANNESS_ADDR(base) ((base) + (0x00C3C))
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_ADDR(base) ((base) + (0x00C40))
#define SOC_SECENG_P_DIN_SW_RESET_ADDR(base) ((base) + (0x00C44))
#define SOC_SECENG_P_DIN_CPU_DATA_SIZE_ADDR(base) ((base) + (0x0C48))
#define SOC_SECENG_P_WRITE_ALIGN_LAST_ADDR(base) ((base) + (0x00C4C))
#define SOC_SECENG_P_FIFO_IN_EMPTY_ADDR(base) ((base) + (0x00C50))
#define SOC_SECENG_P_DISABLE_OUTSTD_REQ_ADDR(base) ((base) + (0x00C54))
#define SOC_SECENG_P_DIN_FIFO_RST_PNTR_ADDR(base) ((base) + (0x00C58))
#define SOC_SECENG_P_DOUT_BUFFER_ADDR(base) ((base) + (0x00D00))
#define SOC_SECENG_P_DOUT_MEM_DMA_BUSY_ADDR(base) ((base) + (0x00D20))
#define SOC_SECENG_P_DST_LLI_SRAM_ADDR_ADDR(base) ((base) + (0x00D24))
#define SOC_SECENG_P_DST_LLI_WORD0_ADDR(base) ((base) + (0x00D28))
#define SOC_SECENG_P_DST_LLI_WORD1_ADDR(base) ((base) + (0x00D2C))
#define SOC_SECENG_P_SRAM_DEST_ADDR_ADDR(base) ((base) + (0x00D30))
#define SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_ADDR(base) ((base) + (0x00D34))
#define SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_ADDR(base) ((base) + (0x00D38))
#define SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_ADDR(base) ((base) + (0x00D3C))
#define SOC_SECENG_P_READ_ALIGN_LAST_ADDR(base) ((base) + (0x00D44))
#define SOC_SECENG_P_DOUT_FIFO_EMPTY_ADDR(base) ((base) + (0x00D50))
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_ADDR(base) ((base) + (0x00D54))
#define SOC_SECENG_P_DOUT_SW_RESET_ADDR(base) ((base) + (0x00D58))
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_ADDR(base) ((base) + (0x00E00))
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_ADDR(base) ((base) + (0x00E04))
#define SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_ADDR(base) ((base) + (0x00E3C))
#define SOC_SECENG_P_DSCRPTR_SW_RESET_ADDR(base) ((base) + (0x00E40))
#define SOC_SECENG_P_DSCRPTR_DEBUG_MODE_ADDR(base) ((base) + (0x00E4C))
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_ADDR(base) ((base) + (0x00E50))
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_ADDR(base) ((base) + (0x00E54))
#define SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_ADDR(base) ((base) + (0x00E58))
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_ADDR(base) ((base) + (0x00E5C))
#define SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_ADDR(base) ((base) + (0x00E60))
#define SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_ADDR(base) ((base) + (0x0E64))
#define SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_ADDR(base) ((base) + (0x0E68))
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_ADDR(base) ((base) + (0x0E6C))
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_ADDR(base) ((base) + (0x00E80))
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_ADDR(base) ((base) + (0x00E84))
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_ADDR(base) ((base) + (0x00E88))
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_ADDR(base) ((base) + (0x00E8C))
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_ADDR(base) ((base) + (0x00E90))
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_ADDR(base) ((base) + (0x00E94))
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_ADDR(base) ((base) + (0x00E98))
#define SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_ADDR(base) ((base) + (0x00E9C))
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_ADDR(base) ((base) + (0x00EA0))
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_ADDR(base) ((base) + (0x00EA4))
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_ADDR(base) ((base) + (0x00EA8))
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_ADDR(base) ((base) + (0x00EAC))
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_ADDR(base) ((base) + (0x00EB0))
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_ADDR(base) ((base) + (0x0EB4))
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_ADDR(base) ((base) + (0x00EB8))
#define SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_ADDR(base) ((base) + (0x00EBC))
#define SOC_SECENG_P_SRAM_DATA_ADDR(base) ((base) + (0x00F00))
#define SOC_SECENG_P_SRAM_ADDR_ADDR(base) ((base) + (0x00F04))
#define SOC_SECENG_P_SRAM_DATA_READY_ADDR(base) ((base) + (0x00F08))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_AES_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_P_AES_CLK_ENABLE_en_START (0)
#define SOC_SECENG_P_AES_CLK_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DES_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_P_DES_CLK_ENABLE_en_START (0)
#define SOC_SECENG_P_DES_CLK_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_HASH_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_P_HASH_CLK_ENABLE_en_START (0)
#define SOC_SECENG_P_HASH_CLK_ENABLE_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DMA_CLK_ENABLE_UNION;
#endif
#define SOC_SECENG_P_DMA_CLK_ENABLE_en_START (0)
#define SOC_SECENG_P_DMA_CLK_ENABLE_en_END (0)
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
} SOC_SECENG_P_CLK_STATUS_UNION;
#endif
#define SOC_SECENG_P_CLK_STATUS_aes_clk_status_START (0)
#define SOC_SECENG_P_CLK_STATUS_aes_clk_status_END (0)
#define SOC_SECENG_P_CLK_STATUS_des_clk_status_START (1)
#define SOC_SECENG_P_CLK_STATUS_des_clk_status_END (1)
#define SOC_SECENG_P_CLK_STATUS_hash_clk_status_START (2)
#define SOC_SECENG_P_CLK_STATUS_hash_clk_status_END (2)
#define SOC_SECENG_P_CLK_STATUS_pka_clk_status_START (3)
#define SOC_SECENG_P_CLK_STATUS_pka_clk_status_END (3)
#define SOC_SECENG_P_CLK_STATUS_dma_clk_status_START (8)
#define SOC_SECENG_P_CLK_STATUS_dma_clk_status_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mode : 5;
        unsigned int reserved : 27;
    } reg;
} SOC_SECENG_P_CRYPTO_CTL_UNION;
#endif
#define SOC_SECENG_P_CRYPTO_CTL_mode_START (0)
#define SOC_SECENG_P_CRYPTO_CTL_mode_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int crypto_busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_CRYPTO_BUSY_UNION;
#endif
#define SOC_SECENG_P_CRYPTO_BUSY_crypto_busy_START (0)
#define SOC_SECENG_P_CRYPTO_BUSY_crypto_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_HASH_BUSY_UNION;
#endif
#define SOC_SECENG_P_HASH_BUSY_hash_busy_START (0)
#define SOC_SECENG_P_HASH_BUSY_hash_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int version : 32;
    } reg;
} SOC_SECENG_P_VERSION_UNION;
#endif
#define SOC_SECENG_P_VERSION_version_START (0)
#define SOC_SECENG_P_VERSION_version_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int context_id : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_CONTEXT_ID_UNION;
#endif
#define SOC_SECENG_P_CONTEXT_ID_context_id_START (0)
#define SOC_SECENG_P_CONTEXT_ID_context_id_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_compare_error_id_fifo0 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_UNION;
#endif
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_hash_compare_error_id_fifo0_START (0)
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO0_hash_compare_error_id_fifo0_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_compare_error_id_fifo1 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_UNION;
#endif
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_hash_compare_error_id_fifo1_START (0)
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO1_hash_compare_error_id_fifo1_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_compare_error_id_fifo2 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_UNION;
#endif
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_hash_compare_error_id_fifo2_START (0)
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO2_hash_compare_error_id_fifo2_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int hash_compare_error_id_fifo3 : 26;
        unsigned int reserved : 6;
    } reg;
} SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_UNION;
#endif
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_hash_compare_error_id_fifo3_START (0)
#define SOC_SECENG_P_HASH_COMPARE_ERR_ID_FIFO3_hash_compare_error_id_fifo3_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int dscrptr_completion_low_int : 1;
        unsigned int host_sram_vio : 1;
        unsigned int sram_to_din_int : 1;
        unsigned int dout_to_sram_int : 1;
        unsigned int mem_to_din_int : 1;
        unsigned int dout_to_mem_int : 1;
        unsigned int axi_err_int : 1;
        unsigned int pka_exp_int : 1;
        unsigned int rng_int : 1;
        unsigned int sep_host_gpr0_int : 1;
        unsigned int sep_host_gpr1_int : 1;
        unsigned int sep_host_gpr2_int : 1;
        unsigned int sep_host_gpr3_int : 1;
        unsigned int sep_host_gpr4_int : 1;
        unsigned int sep_host_gpr5_int : 1;
        unsigned int sep_host_gpr6_int : 1;
        unsigned int sep_host_gpr7_int : 1;
        unsigned int dscrptr_watermark0_int : 1;
        unsigned int dscrptr_watermark1_int : 1;
        unsigned int reserved_1 : 1;
        unsigned int hash_cmp_error_int : 1;
        unsigned int axim_cmp_int : 1;
        unsigned int reserved_2 : 8;
    } reg;
} SOC_SECENG_P_HOST_IRR_UNION;
#endif
#define SOC_SECENG_P_HOST_IRR_dscrptr_completion_low_int_START (2)
#define SOC_SECENG_P_HOST_IRR_dscrptr_completion_low_int_END (2)
#define SOC_SECENG_P_HOST_IRR_host_sram_vio_START (3)
#define SOC_SECENG_P_HOST_IRR_host_sram_vio_END (3)
#define SOC_SECENG_P_HOST_IRR_sram_to_din_int_START (4)
#define SOC_SECENG_P_HOST_IRR_sram_to_din_int_END (4)
#define SOC_SECENG_P_HOST_IRR_dout_to_sram_int_START (5)
#define SOC_SECENG_P_HOST_IRR_dout_to_sram_int_END (5)
#define SOC_SECENG_P_HOST_IRR_mem_to_din_int_START (6)
#define SOC_SECENG_P_HOST_IRR_mem_to_din_int_END (6)
#define SOC_SECENG_P_HOST_IRR_dout_to_mem_int_START (7)
#define SOC_SECENG_P_HOST_IRR_dout_to_mem_int_END (7)
#define SOC_SECENG_P_HOST_IRR_axi_err_int_START (8)
#define SOC_SECENG_P_HOST_IRR_axi_err_int_END (8)
#define SOC_SECENG_P_HOST_IRR_pka_exp_int_START (9)
#define SOC_SECENG_P_HOST_IRR_pka_exp_int_END (9)
#define SOC_SECENG_P_HOST_IRR_rng_int_START (10)
#define SOC_SECENG_P_HOST_IRR_rng_int_END (10)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr0_int_START (11)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr0_int_END (11)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr1_int_START (12)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr1_int_END (12)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr2_int_START (13)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr2_int_END (13)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr3_int_START (14)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr3_int_END (14)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr4_int_START (15)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr4_int_END (15)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr5_int_START (16)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr5_int_END (16)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr6_int_START (17)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr6_int_END (17)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr7_int_START (18)
#define SOC_SECENG_P_HOST_IRR_sep_host_gpr7_int_END (18)
#define SOC_SECENG_P_HOST_IRR_dscrptr_watermark0_int_START (19)
#define SOC_SECENG_P_HOST_IRR_dscrptr_watermark0_int_END (19)
#define SOC_SECENG_P_HOST_IRR_dscrptr_watermark1_int_START (20)
#define SOC_SECENG_P_HOST_IRR_dscrptr_watermark1_int_END (20)
#define SOC_SECENG_P_HOST_IRR_hash_cmp_error_int_START (22)
#define SOC_SECENG_P_HOST_IRR_hash_cmp_error_int_END (22)
#define SOC_SECENG_P_HOST_IRR_axim_cmp_int_START (23)
#define SOC_SECENG_P_HOST_IRR_axim_cmp_int_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int dscrptr_completion_mask : 1;
        unsigned int host_sram_vio_mask : 1;
        unsigned int sram_to_din_mask : 1;
        unsigned int dout_to_sram_mask : 1;
        unsigned int mem_to_din_mask : 1;
        unsigned int dout_to_mem_mask : 1;
        unsigned int axi_err_mask : 1;
        unsigned int pka_exp_mask : 1;
        unsigned int rng_int_mask : 1;
        unsigned int sep_host_gpr0_mask : 1;
        unsigned int sep_host_gpr1_mask : 1;
        unsigned int sep_host_gpr2_mask : 1;
        unsigned int sep_host_gpr3_mask : 1;
        unsigned int sep_host_gpr4_mask : 1;
        unsigned int sep_host_gpr5_mask : 1;
        unsigned int sep_host_gpr6_mask : 1;
        unsigned int sep_host_gpr7_mask : 1;
        unsigned int dscrptr_watermark_mask0 : 1;
        unsigned int dscrptr_watermark_mask1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int hash_cmp_error_mask : 1;
        unsigned int axim_comp_mask : 1;
        unsigned int reserved_2 : 8;
    } reg;
} SOC_SECENG_P_HOST_IMR_UNION;
#endif
#define SOC_SECENG_P_HOST_IMR_dscrptr_completion_mask_START (2)
#define SOC_SECENG_P_HOST_IMR_dscrptr_completion_mask_END (2)
#define SOC_SECENG_P_HOST_IMR_host_sram_vio_mask_START (3)
#define SOC_SECENG_P_HOST_IMR_host_sram_vio_mask_END (3)
#define SOC_SECENG_P_HOST_IMR_sram_to_din_mask_START (4)
#define SOC_SECENG_P_HOST_IMR_sram_to_din_mask_END (4)
#define SOC_SECENG_P_HOST_IMR_dout_to_sram_mask_START (5)
#define SOC_SECENG_P_HOST_IMR_dout_to_sram_mask_END (5)
#define SOC_SECENG_P_HOST_IMR_mem_to_din_mask_START (6)
#define SOC_SECENG_P_HOST_IMR_mem_to_din_mask_END (6)
#define SOC_SECENG_P_HOST_IMR_dout_to_mem_mask_START (7)
#define SOC_SECENG_P_HOST_IMR_dout_to_mem_mask_END (7)
#define SOC_SECENG_P_HOST_IMR_axi_err_mask_START (8)
#define SOC_SECENG_P_HOST_IMR_axi_err_mask_END (8)
#define SOC_SECENG_P_HOST_IMR_pka_exp_mask_START (9)
#define SOC_SECENG_P_HOST_IMR_pka_exp_mask_END (9)
#define SOC_SECENG_P_HOST_IMR_rng_int_mask_START (10)
#define SOC_SECENG_P_HOST_IMR_rng_int_mask_END (10)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr0_mask_START (11)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr0_mask_END (11)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr1_mask_START (12)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr1_mask_END (12)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr2_mask_START (13)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr2_mask_END (13)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr3_mask_START (14)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr3_mask_END (14)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr4_mask_START (15)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr4_mask_END (15)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr5_mask_START (16)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr5_mask_END (16)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr6_mask_START (17)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr6_mask_END (17)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr7_mask_START (18)
#define SOC_SECENG_P_HOST_IMR_sep_host_gpr7_mask_END (18)
#define SOC_SECENG_P_HOST_IMR_dscrptr_watermark_mask0_START (19)
#define SOC_SECENG_P_HOST_IMR_dscrptr_watermark_mask0_END (19)
#define SOC_SECENG_P_HOST_IMR_dscrptr_watermark_mask1_START (20)
#define SOC_SECENG_P_HOST_IMR_dscrptr_watermark_mask1_END (20)
#define SOC_SECENG_P_HOST_IMR_hash_cmp_error_mask_START (22)
#define SOC_SECENG_P_HOST_IMR_hash_cmp_error_mask_END (22)
#define SOC_SECENG_P_HOST_IMR_axim_comp_mask_START (23)
#define SOC_SECENG_P_HOST_IMR_axim_comp_mask_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int dscrptr_completion_clear : 1;
        unsigned int host_sram_vio_clear : 1;
        unsigned int sram_to_din_clear : 1;
        unsigned int dout_to_sram_clear : 1;
        unsigned int mem_to_din_clear : 1;
        unsigned int dout_to_mem_clear : 1;
        unsigned int axi_err_clear : 1;
        unsigned int pka_exp_clear : 1;
        unsigned int rng_int_clear : 1;
        unsigned int sep_host_gpr0_clear : 1;
        unsigned int sep_host_gpr1_clear : 1;
        unsigned int sep_host_gpr2_clear : 1;
        unsigned int sep_host_gpr3_clear : 1;
        unsigned int sep_host_gpr4_clear : 1;
        unsigned int sep_host_gpr5_clear : 1;
        unsigned int sep_host_gpr6_clear : 1;
        unsigned int sep_host_gpr7_clear : 1;
        unsigned int dscrptr_watermark_queue0_clear : 1;
        unsigned int dscrptr_watermark_queue1_clear : 1;
        unsigned int reserved_1 : 1;
        unsigned int hash_cmp_error_clear : 1;
        unsigned int axim_comp_clear : 1;
        unsigned int reserved_2 : 8;
    } reg;
} SOC_SECENG_P_HOST_ICR_UNION;
#endif
#define SOC_SECENG_P_HOST_ICR_dscrptr_completion_clear_START (2)
#define SOC_SECENG_P_HOST_ICR_dscrptr_completion_clear_END (2)
#define SOC_SECENG_P_HOST_ICR_host_sram_vio_clear_START (3)
#define SOC_SECENG_P_HOST_ICR_host_sram_vio_clear_END (3)
#define SOC_SECENG_P_HOST_ICR_sram_to_din_clear_START (4)
#define SOC_SECENG_P_HOST_ICR_sram_to_din_clear_END (4)
#define SOC_SECENG_P_HOST_ICR_dout_to_sram_clear_START (5)
#define SOC_SECENG_P_HOST_ICR_dout_to_sram_clear_END (5)
#define SOC_SECENG_P_HOST_ICR_mem_to_din_clear_START (6)
#define SOC_SECENG_P_HOST_ICR_mem_to_din_clear_END (6)
#define SOC_SECENG_P_HOST_ICR_dout_to_mem_clear_START (7)
#define SOC_SECENG_P_HOST_ICR_dout_to_mem_clear_END (7)
#define SOC_SECENG_P_HOST_ICR_axi_err_clear_START (8)
#define SOC_SECENG_P_HOST_ICR_axi_err_clear_END (8)
#define SOC_SECENG_P_HOST_ICR_pka_exp_clear_START (9)
#define SOC_SECENG_P_HOST_ICR_pka_exp_clear_END (9)
#define SOC_SECENG_P_HOST_ICR_rng_int_clear_START (10)
#define SOC_SECENG_P_HOST_ICR_rng_int_clear_END (10)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr0_clear_START (11)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr0_clear_END (11)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr1_clear_START (12)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr1_clear_END (12)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr2_clear_START (13)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr2_clear_END (13)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr3_clear_START (14)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr3_clear_END (14)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr4_clear_START (15)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr4_clear_END (15)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr5_clear_START (16)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr5_clear_END (16)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr6_clear_START (17)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr6_clear_END (17)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr7_clear_START (18)
#define SOC_SECENG_P_HOST_ICR_sep_host_gpr7_clear_END (18)
#define SOC_SECENG_P_HOST_ICR_dscrptr_watermark_queue0_clear_START (19)
#define SOC_SECENG_P_HOST_ICR_dscrptr_watermark_queue0_clear_END (19)
#define SOC_SECENG_P_HOST_ICR_dscrptr_watermark_queue1_clear_START (20)
#define SOC_SECENG_P_HOST_ICR_dscrptr_watermark_queue1_clear_END (20)
#define SOC_SECENG_P_HOST_ICR_hash_cmp_error_clear_START (22)
#define SOC_SECENG_P_HOST_ICR_hash_cmp_error_clear_END (22)
#define SOC_SECENG_P_HOST_ICR_axim_comp_clear_START (23)
#define SOC_SECENG_P_HOST_ICR_axim_comp_clear_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_sram_threshold : 12;
        unsigned int reserved : 20;
    } reg;
} SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_sep_sram_threshold_START (0)
#define SOC_SECENG_P_HOST_SEP_SRAM_THRESHOLD_sep_sram_threshold_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_HOST_SEP_BUSY_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_BUSY_sep_busy_START (0)
#define SOC_SECENG_P_HOST_SEP_BUSY_sep_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_sw_monitor : 32;
    } reg;
} SOC_SECENG_P_HOST_SEP_SW_MONITOR_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_SW_MONITOR_sep_sw_monitor_START (0)
#define SOC_SECENG_P_HOST_SEP_SW_MONITOR_sep_sw_monitor_END (31)
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
} SOC_SECENG_P_HOST_CC_SW_RST_UNION;
#endif
#define SOC_SECENG_P_HOST_CC_SW_RST_cc_sw_rst_req_START (0)
#define SOC_SECENG_P_HOST_CC_SW_RST_cc_sw_rst_req_END (0)
#define SOC_SECENG_P_HOST_CC_SW_RST_cc_sw_rst_force_START (1)
#define SOC_SECENG_P_HOST_CC_SW_RST_cc_sw_rst_force_END (1)
#define SOC_SECENG_P_HOST_CC_SW_RST_axis_sysreq_START (2)
#define SOC_SECENG_P_HOST_CC_SW_RST_axis_sysreq_END (2)
#define SOC_SECENG_P_HOST_CC_SW_RST_axim_sysreq_START (3)
#define SOC_SECENG_P_HOST_CC_SW_RST_axim_sysreq_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_host_gpr0 : 32;
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR0_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR0_sep_host_gpr0_START (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR0_sep_host_gpr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_sep_gpr0 : 32;
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR0_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR0_host_sep_gpr0_START (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR0_host_sep_gpr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_host_gpr1 : 32;
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR1_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR1_sep_host_gpr1_START (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR1_sep_host_gpr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_sep_gpr1 : 32;
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR1_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR1_host_sep_gpr1_START (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR1_host_sep_gpr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_host_gpr2 : 32;
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR2_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR2_sep_host_gpr2_START (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR2_sep_host_gpr2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_sep_gpr2 : 32;
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR2_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR2_host_sep_gpr2_START (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR2_host_sep_gpr2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_host_gpr3 : 32;
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR3_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR3_sep_host_gpr3_START (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR3_sep_host_gpr3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_sep_gpr3 : 32;
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR3_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR3_host_sep_gpr3_START (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR3_host_sep_gpr3_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_host_gpr4 : 32;
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR4_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR4_sep_host_gpr4_START (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR4_sep_host_gpr4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_sep_gpr4 : 32;
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR4_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR4_host_sep_gpr4_START (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR4_host_sep_gpr4_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_host_gpr5 : 32;
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR5_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR5_sep_host_gpr5_START (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR5_sep_host_gpr5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_sep_gpr5 : 32;
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR5_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR5_host_sep_gpr5_START (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR5_host_sep_gpr5_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_host_gpr6 : 32;
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR6_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR6_sep_host_gpr6_START (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR6_sep_host_gpr6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_sep_gpr6 : 32;
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR6_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR6_host_sep_gpr6_START (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR6_host_sep_gpr6_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sep_host_gpr7 : 32;
    } reg;
} SOC_SECENG_P_HOST_SEP_HOST_GPR7_UNION;
#endif
#define SOC_SECENG_P_HOST_SEP_HOST_GPR7_sep_host_gpr7_START (0)
#define SOC_SECENG_P_HOST_SEP_HOST_GPR7_sep_host_gpr7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_sep_gpr7 : 32;
    } reg;
} SOC_SECENG_P_HOST_HOST_SEP_GPR7_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_SEP_GPR7_host_sep_gpr7_START (0)
#define SOC_SECENG_P_HOST_HOST_SEP_GPR7_host_sep_gpr7_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_cc_signature : 32;
    } reg;
} SOC_SECENG_P_HOST_CC_SIGNATURE_UNION;
#endif
#define SOC_SECENG_P_HOST_CC_SIGNATURE_host_cc_signature_START (0)
#define SOC_SECENG_P_HOST_CC_SIGNATURE_host_cc_signature_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int din_dd_end : 1;
        unsigned int din_dma_end : 1;
        unsigned int reserved_1 : 2;
        unsigned int dout_dd_end : 1;
        unsigned int dout_dma_end : 1;
        unsigned int intenal_word_end : 8;
        unsigned int reserved_2 : 16;
    } reg;
} SOC_SECENG_P_HOST_HOST_ENDIAN_UNION;
#endif
#define SOC_SECENG_P_HOST_HOST_ENDIAN_din_dd_end_START (2)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_din_dd_end_END (2)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_din_dma_end_START (3)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_din_dma_end_END (3)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_dout_dd_end_START (6)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_dout_dd_end_END (6)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_dout_dma_end_START (7)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_dout_dma_end_END (7)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_intenal_word_end_START (8)
#define SOC_SECENG_P_HOST_HOST_ENDIAN_intenal_word_end_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_irq_timer_init_val : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_UNION;
#endif
#define SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_host_irq_timer_init_val_START (0)
#define SOC_SECENG_P_HOST_IRQ_TIMER_INIT_VAL_host_irq_timer_init_val_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int host_version : 32;
    } reg;
} SOC_SECENG_P_HOST_VERSION_UNION;
#endif
#define SOC_SECENG_P_HOST_VERSION_host_version_START (0)
#define SOC_SECENG_P_HOST_VERSION_host_version_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT0_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT0_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT0_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT1_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT1_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT1_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT2_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT2_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT2_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT3_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT3_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT3_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT4_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT4_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT4_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT5_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT5_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT5_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT8_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT8_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT8_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT9_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT9_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT9_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT10_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT10_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT10_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHT11_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHT11_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHT11_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST0_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST1_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST2_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST3_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST4_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST5_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int unused : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_inflightcntr_END (7)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_unused_START (8)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST8_unused_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST9_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST10_inflightcntr_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int inflightcntr : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_inflightcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_INFLIGHTLAST11_inflightcntr_END (7)
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
} SOC_SECENG_P_AXIM_PIDTABLE0_UNION;
#endif
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_broken1_START (0)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_broken1_END (0)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_broken2_START (1)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_broken2_END (1)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_oscntr_START (2)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_oscntr_END (9)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_id_START (10)
#define SOC_SECENG_P_AXIM_PIDTABLE0_pid_id_END (14)
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
} SOC_SECENG_P_AXIM_PIDTABLE1_UNION;
#endif
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_broken1_START (0)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_broken1_END (0)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_broken2_START (1)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_broken2_END (1)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_oscntr_START (2)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_oscntr_END (9)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_id_START (10)
#define SOC_SECENG_P_AXIM_PIDTABLE1_pid_id_END (14)
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
} SOC_SECENG_P_AXIM_PIDTABLE2_UNION;
#endif
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_broken1_START (0)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_broken1_END (0)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_broken2_START (1)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_broken2_END (1)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_oscntr_START (2)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_oscntr_END (9)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_id_START (10)
#define SOC_SECENG_P_AXIM_PIDTABLE2_pid_id_END (14)
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
} SOC_SECENG_P_AXIM_PIDTABLE3_UNION;
#endif
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_broken1_START (0)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_broken1_END (0)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_broken2_START (1)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_broken2_END (1)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_oscntr_START (2)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_oscntr_END (9)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_id_START (10)
#define SOC_SECENG_P_AXIM_PIDTABLE3_pid_id_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP0_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP0_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP0_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP1_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP1_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP1_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP2_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP2_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP2_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP3_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP3_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP3_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP4_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP4_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP4_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP5_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP5_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP5_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP8_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP8_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP8_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP9_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP9_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP9_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP10_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP10_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP10_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int complastcntr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_AXIM_MON_COMP11_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_COMP11_complastcntr_START (0)
#define SOC_SECENG_P_AXIM_MON_COMP11_complastcntr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rmax : 32;
    } reg;
} SOC_SECENG_P_AXIM_MON_RMAX_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_RMAX_rmax_START (0)
#define SOC_SECENG_P_AXIM_MON_RMAX_rmax_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rmin : 32;
    } reg;
} SOC_SECENG_P_AXIM_MON_RMIN_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_RMIN_rmin_START (0)
#define SOC_SECENG_P_AXIM_MON_RMIN_rmin_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wmax : 32;
    } reg;
} SOC_SECENG_P_AXIM_MON_WMAX_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_WMAX_wmax_START (0)
#define SOC_SECENG_P_AXIM_MON_WMAX_wmax_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wmin : 32;
    } reg;
} SOC_SECENG_P_AXIM_MON_WMIN_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_WMIN_wmin_START (0)
#define SOC_SECENG_P_AXIM_MON_WMIN_wmin_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bresp : 2;
        unsigned int bid : 4;
        unsigned int reserved_0: 10;
        unsigned int rresp : 2;
        unsigned int rid : 4;
        unsigned int reserved_1: 10;
    } reg;
} SOC_SECENG_P_AXIM_MON_ERR_UNION;
#endif
#define SOC_SECENG_P_AXIM_MON_ERR_bresp_START (0)
#define SOC_SECENG_P_AXIM_MON_ERR_bresp_END (1)
#define SOC_SECENG_P_AXIM_MON_ERR_bid_START (2)
#define SOC_SECENG_P_AXIM_MON_ERR_bid_END (5)
#define SOC_SECENG_P_AXIM_MON_ERR_rresp_START (16)
#define SOC_SECENG_P_AXIM_MON_ERR_rresp_END (17)
#define SOC_SECENG_P_AXIM_MON_ERR_rid_START (18)
#define SOC_SECENG_P_AXIM_MON_ERR_rid_END (21)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int oscntr : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_SECENG_P_AXIM_RDSTAT_UNION;
#endif
#define SOC_SECENG_P_AXIM_RDSTAT_oscntr_START (0)
#define SOC_SECENG_P_AXIM_RDSTAT_oscntr_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rlatency : 32;
    } reg;
} SOC_SECENG_P_AXIM_RLATENCY_UNION;
#endif
#define SOC_SECENG_P_AXIM_RLATENCY_rlatency_START (0)
#define SOC_SECENG_P_AXIM_RLATENCY_rlatency_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rburst : 32;
    } reg;
} SOC_SECENG_P_AXIM_RBURST_UNION;
#endif
#define SOC_SECENG_P_AXIM_RBURST_rburst_START (0)
#define SOC_SECENG_P_AXIM_RBURST_rburst_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wlatency : 32;
    } reg;
} SOC_SECENG_P_AXIM_WLATENCY_UNION;
#endif
#define SOC_SECENG_P_AXIM_WLATENCY_wlatency_START (0)
#define SOC_SECENG_P_AXIM_WLATENCY_wlatency_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int wburst : 32;
    } reg;
} SOC_SECENG_P_AXIM_WBURST_UNION;
#endif
#define SOC_SECENG_P_AXIM_WBURST_wburst_START (0)
#define SOC_SECENG_P_AXIM_WBURST_wburst_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int dd_arcache : 4;
        unsigned int reserved_1 : 12;
        unsigned int dd_awcache : 4;
        unsigned int reserved_2 : 4;
    } reg;
} SOC_SECENG_P_AXIM_CACHETYPE_CFG_UNION;
#endif
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_dd_arcache_START (8)
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_dd_arcache_END (11)
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_dd_awcache_START (24)
#define SOC_SECENG_P_AXIM_CACHETYPE_CFG_dd_awcache_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 4;
        unsigned int dd_arprot : 1;
        unsigned int reserved_1: 7;
        unsigned int dd_awprot : 1;
        unsigned int reserved_2: 19;
    } reg;
} SOC_SECENG_P_AXIM_PROT_CFG_UNION;
#endif
#define SOC_SECENG_P_AXIM_PROT_CFG_dd_arprot_START (4)
#define SOC_SECENG_P_AXIM_PROT_CFG_dd_arprot_END (4)
#define SOC_SECENG_P_AXIM_PROT_CFG_dd_awprot_START (12)
#define SOC_SECENG_P_AXIM_PROT_CFG_dd_awprot_END (12)
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
        unsigned int ompmask : 1;
        unsigned int reserved_0 : 8;
        unsigned int accum_limit : 5;
        unsigned int reserved_1 : 11;
    } reg;
} SOC_SECENG_P_AXIM_CFG1_UNION;
#endif
#define SOC_SECENG_P_AXIM_CFG1_rd_after_wr_stall_START (0)
#define SOC_SECENG_P_AXIM_CFG1_rd_after_wr_stall_END (3)
#define SOC_SECENG_P_AXIM_CFG1_brespmask_START (4)
#define SOC_SECENG_P_AXIM_CFG1_brespmask_END (4)
#define SOC_SECENG_P_AXIM_CFG1_rrespmask_START (5)
#define SOC_SECENG_P_AXIM_CFG1_rrespmask_END (5)
#define SOC_SECENG_P_AXIM_CFG1_infltmask_START (6)
#define SOC_SECENG_P_AXIM_CFG1_infltmask_END (6)
#define SOC_SECENG_P_AXIM_CFG1_ompmask_START (7)
#define SOC_SECENG_P_AXIM_CFG1_ompmask_END (7)
#define SOC_SECENG_P_AXIM_CFG1_accum_limit_START (16)
#define SOC_SECENG_P_AXIM_CFG1_accum_limit_END (20)
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
} SOC_SECENG_P_AXIM_ACE_CONST_UNION;
#endif
#define SOC_SECENG_P_AXIM_ACE_CONST_ardomain_START (0)
#define SOC_SECENG_P_AXIM_ACE_CONST_ardomain_END (1)
#define SOC_SECENG_P_AXIM_ACE_CONST_awdomain_START (2)
#define SOC_SECENG_P_AXIM_ACE_CONST_awdomain_END (3)
#define SOC_SECENG_P_AXIM_ACE_CONST_arbar_START (4)
#define SOC_SECENG_P_AXIM_ACE_CONST_arbar_END (5)
#define SOC_SECENG_P_AXIM_ACE_CONST_awbar_START (6)
#define SOC_SECENG_P_AXIM_ACE_CONST_awbar_END (7)
#define SOC_SECENG_P_AXIM_ACE_CONST_arsnoop_START (8)
#define SOC_SECENG_P_AXIM_ACE_CONST_arsnoop_END (11)
#define SOC_SECENG_P_AXIM_ACE_CONST_awsnoop_not_aligned_START (12)
#define SOC_SECENG_P_AXIM_ACE_CONST_awsnoop_not_aligned_END (14)
#define SOC_SECENG_P_AXIM_ACE_CONST_awsnoop_aligned_START (15)
#define SOC_SECENG_P_AXIM_ACE_CONST_awsnoop_aligned_END (17)
#define SOC_SECENG_P_AXIM_ACE_CONST_awaddr_not_masked_START (18)
#define SOC_SECENG_P_AXIM_ACE_CONST_awaddr_not_masked_END (24)
#define SOC_SECENG_P_AXIM_ACE_CONST_awlen_val_START (25)
#define SOC_SECENG_P_AXIM_ACE_CONST_awlen_val_END (28)
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
} SOC_SECENG_P_AXIM_CACHE_PARAMS_UNION;
#endif
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_awcache_last_START (0)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_awcache_last_END (3)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_awcache_START (4)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_awcache_END (7)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_arcache_START (8)
#define SOC_SECENG_P_AXIM_CACHE_PARAMS_arcache_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int addr_axim_ctrl : 4;
        unsigned int reserved : 28;
    } reg;
} SOC_SECENG_P_ADDR_AXIM_CTRL_UNION;
#endif
#define SOC_SECENG_P_ADDR_AXIM_CTRL_addr_axim_ctrl_START (0)
#define SOC_SECENG_P_ADDR_AXIM_CTRL_addr_axim_ctrl_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_buffer_data : 32;
    } reg;
} SOC_SECENG_P_DIN_BUFFER_UNION;
#endif
#define SOC_SECENG_P_DIN_BUFFER_din_buffer_data_START (0)
#define SOC_SECENG_P_DIN_BUFFER_din_buffer_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_mem_dma_busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DIN_MEM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_P_DIN_MEM_DMA_BUSY_din_mem_dma_busy_START (0)
#define SOC_SECENG_P_DIN_MEM_DMA_BUSY_din_mem_dma_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int src_lli_sram_addr : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_P_SRC_LLI_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_P_SRC_LLI_SRAM_ADDR_src_lli_sram_addr_START (0)
#define SOC_SECENG_P_SRC_LLI_SRAM_ADDR_src_lli_sram_addr_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int src_lli_word0 : 32;
    } reg;
} SOC_SECENG_P_SRC_LLI_WORD0_UNION;
#endif
#define SOC_SECENG_P_SRC_LLI_WORD0_src_lli_word0_START (0)
#define SOC_SECENG_P_SRC_LLI_WORD0_src_lli_word0_END (31)
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
} SOC_SECENG_P_SRC_LLI_WORD1_UNION;
#endif
#define SOC_SECENG_P_SRC_LLI_WORD1_bytes_num_START (0)
#define SOC_SECENG_P_SRC_LLI_WORD1_bytes_num_END (29)
#define SOC_SECENG_P_SRC_LLI_WORD1_first_START (30)
#define SOC_SECENG_P_SRC_LLI_WORD1_first_END (30)
#define SOC_SECENG_P_SRC_LLI_WORD1_last_START (31)
#define SOC_SECENG_P_SRC_LLI_WORD1_last_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_source : 32;
    } reg;
} SOC_SECENG_P_SRAM_SRC_ADDR_UNION;
#endif
#define SOC_SECENG_P_SRAM_SRC_ADDR_sram_source_START (0)
#define SOC_SECENG_P_SRAM_SRC_ADDR_sram_source_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bytes_len : 32;
    } reg;
} SOC_SECENG_P_DIN_SRAM_BYTES_LEN_UNION;
#endif
#define SOC_SECENG_P_DIN_SRAM_BYTES_LEN_bytes_len_START (0)
#define SOC_SECENG_P_DIN_SRAM_BYTES_LEN_bytes_len_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DIN_SRAM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_P_DIN_SRAM_DMA_BUSY_busy_START (0)
#define SOC_SECENG_P_DIN_SRAM_DMA_BUSY_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_din_endianness : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DIN_SRAM_ENDIANNESS_UNION;
#endif
#define SOC_SECENG_P_DIN_SRAM_ENDIANNESS_sram_din_endianness_START (0)
#define SOC_SECENG_P_DIN_SRAM_ENDIANNESS_sram_din_endianness_END (0)
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
} SOC_SECENG_P_AXI_CPU_DIN_PARAMS_UNION;
#endif
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_rdid_START (0)
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_rdid_END (3)
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_prot_START (8)
#define SOC_SECENG_P_AXI_CPU_DIN_PARAMS_prot_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int kick_sw_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DIN_SW_RESET_UNION;
#endif
#define SOC_SECENG_P_DIN_SW_RESET_kick_sw_reset_START (0)
#define SOC_SECENG_P_DIN_SW_RESET_kick_sw_reset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cpu_din_size : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_DIN_CPU_DATA_SIZE_UNION;
#endif
#define SOC_SECENG_P_DIN_CPU_DATA_SIZE_cpu_din_size_START (0)
#define SOC_SECENG_P_DIN_CPU_DATA_SIZE_cpu_din_size_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int last : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_WRITE_ALIGN_LAST_UNION;
#endif
#define SOC_SECENG_P_WRITE_ALIGN_LAST_last_START (0)
#define SOC_SECENG_P_WRITE_ALIGN_LAST_last_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int empty : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_FIFO_IN_EMPTY_UNION;
#endif
#define SOC_SECENG_P_FIFO_IN_EMPTY_empty_START (0)
#define SOC_SECENG_P_FIFO_IN_EMPTY_empty_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int disable_outstd_req : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DISABLE_OUTSTD_REQ_UNION;
#endif
#define SOC_SECENG_P_DISABLE_OUTSTD_REQ_disable_outstd_req_START (0)
#define SOC_SECENG_P_DISABLE_OUTSTD_REQ_disable_outstd_req_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int rst : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DIN_FIFO_RST_PNTR_UNION;
#endif
#define SOC_SECENG_P_DIN_FIFO_RST_PNTR_rst_START (0)
#define SOC_SECENG_P_DIN_FIFO_RST_PNTR_rst_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_buffer_data : 32;
    } reg;
} SOC_SECENG_P_DOUT_BUFFER_UNION;
#endif
#define SOC_SECENG_P_DOUT_BUFFER_dout_buffer_data_START (0)
#define SOC_SECENG_P_DOUT_BUFFER_dout_buffer_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_mem_dma_busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DOUT_MEM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_P_DOUT_MEM_DMA_BUSY_dout_mem_dma_busy_START (0)
#define SOC_SECENG_P_DOUT_MEM_DMA_BUSY_dout_mem_dma_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dst_lli_sram_addr : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_P_DST_LLI_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_P_DST_LLI_SRAM_ADDR_dst_lli_sram_addr_START (0)
#define SOC_SECENG_P_DST_LLI_SRAM_ADDR_dst_lli_sram_addr_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dst_lli_word0 : 32;
    } reg;
} SOC_SECENG_P_DST_LLI_WORD0_UNION;
#endif
#define SOC_SECENG_P_DST_LLI_WORD0_dst_lli_word0_START (0)
#define SOC_SECENG_P_DST_LLI_WORD0_dst_lli_word0_END (31)
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
} SOC_SECENG_P_DST_LLI_WORD1_UNION;
#endif
#define SOC_SECENG_P_DST_LLI_WORD1_bytes_num_START (0)
#define SOC_SECENG_P_DST_LLI_WORD1_bytes_num_END (29)
#define SOC_SECENG_P_DST_LLI_WORD1_first_START (30)
#define SOC_SECENG_P_DST_LLI_WORD1_first_END (30)
#define SOC_SECENG_P_DST_LLI_WORD1_last_START (31)
#define SOC_SECENG_P_DST_LLI_WORD1_last_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_dest : 32;
    } reg;
} SOC_SECENG_P_SRAM_DEST_ADDR_UNION;
#endif
#define SOC_SECENG_P_SRAM_DEST_ADDR_sram_dest_START (0)
#define SOC_SECENG_P_SRAM_DEST_ADDR_sram_dest_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bytes_len : 32;
    } reg;
} SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_UNION;
#endif
#define SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_bytes_len_START (0)
#define SOC_SECENG_P_DOUT_SRAM_BYTES_LEN_bytes_len_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int busy : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_UNION;
#endif
#define SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_busy_START (0)
#define SOC_SECENG_P_DOUT_SRAM_DMA_BUSY_busy_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_sram_endianness : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_UNION;
#endif
#define SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_dout_sram_endianness_START (0)
#define SOC_SECENG_P_DOUT_SRAM_ENDIANNESS_dout_sram_endianness_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int last : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_READ_ALIGN_LAST_UNION;
#endif
#define SOC_SECENG_P_READ_ALIGN_LAST_last_START (0)
#define SOC_SECENG_P_READ_ALIGN_LAST_last_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_fifo_empty : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DOUT_FIFO_EMPTY_UNION;
#endif
#define SOC_SECENG_P_DOUT_FIFO_EMPTY_dout_fifo_empty_START (0)
#define SOC_SECENG_P_DOUT_FIFO_EMPTY_dout_fifo_empty_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cache_type : 4;
        unsigned int reserved_0 : 8;
        unsigned int wrid : 4;
        unsigned int prot : 2;
        unsigned int force_cpu_params : 1;
        unsigned int reserved_1 : 13;
    } reg;
} SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_UNION;
#endif
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_cache_type_START (0)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_cache_type_END (3)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_wrid_START (12)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_wrid_END (15)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_prot_START (16)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_prot_END (17)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_force_cpu_params_START (18)
#define SOC_SECENG_P_AXI_CPU_DOUT_PARAMS_force_cpu_params_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_sw_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DOUT_SW_RESET_UNION;
#endif
#define SOC_SECENG_P_DOUT_SW_RESET_dout_sw_reset_START (0)
#define SOC_SECENG_P_DOUT_SW_RESET_dout_sw_reset_END (0)
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
} SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_completion_counter_START (0)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_completion_counter_END (5)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_overflow_counter_START (6)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER0_overflow_counter_END (6)
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
} SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_completion_counter_START (0)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_completion_counter_END (5)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_overflow_counter_START (6)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_COUNTER1_overflow_counter_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int completion_counter_status : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_completion_counter_status_START (0)
#define SOC_SECENG_P_DSCRPTR_COMPLETION_STATUS_completion_counter_status_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dscrptr_sw_reset : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DSCRPTR_SW_RESET_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_SW_RESET_dscrptr_sw_reset_START (0)
#define SOC_SECENG_P_DSCRPTR_SW_RESET_dscrptr_sw_reset_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dscrptr_debug_mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DSCRPTR_DEBUG_MODE_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_DEBUG_MODE_dscrptr_debug_mode_START (0)
#define SOC_SECENG_P_DSCRPTR_DEBUG_MODE_dscrptr_debug_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dscrptr_filter_drop_count : 32;
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_dscrptr_filter_drop_count_START (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_CNT_dscrptr_filter_drop_count_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dscrptr_filter_drop_mem_count : 32;
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_dscrptr_filter_drop_mem_count_START (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_MEM_CNT_dscrptr_filter_drop_mem_count_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dscrptr_debug_mode : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_dscrptr_debug_mode_START (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DEBUG_dscrptr_debug_mode_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dropped_address : 32;
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_dropped_address_START (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_dropped_address_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_queue_size : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_sram_queue_size_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE_SRAM_SIZE_sram_queue_size_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dscrptr_single_addr_en : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_dscrptr_single_addr_en_START (0)
#define SOC_SECENG_P_DSCRPTR_SINGLE_ADDR_EN_dscrptr_single_addr_en_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int measure_cntr : 32;
    } reg;
} SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_measure_cntr_START (0)
#define SOC_SECENG_P_DSCRPTR_MEASURE_CNTR_measure_cntr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dropped_address_high : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_dropped_address_high_START (0)
#define SOC_SECENG_P_DSCRPTR_FILTER_DROPPED_ADDRESS_HIGH_dropped_address_high_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_dma_address : 32;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_din_dma_address_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD0_din_dma_address_END (31)
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
        unsigned int reserved : 1;
        unsigned int din_virtual_host : 2;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_dma_mode_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_dma_mode_END (1)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_size_START (2)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_size_END (25)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_ns_bit_START (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_ns_bit_END (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_const_value_START (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_const_value_END (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_not_last_START (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_not_last_END (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_virtual_host_START (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD1_din_virtual_host_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_dma_address : 32;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_dout_dma_address_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD2_dout_dma_address_END (31)
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
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_dma_mode_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_dma_mode_END (1)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_size_START (2)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_size_END (25)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_ns_bit_START (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_ns_bit_END (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_last_ind_START (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_last_ind_END (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_hash_xor_bit_START (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_hash_xor_bit_END (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_virtual_host_START (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD3_dout_virtual_host_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_flow_mode : 6;
        unsigned int aes_sel_n_hash : 1;
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
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_data_flow_mode_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_data_flow_mode_END (5)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_aes_sel_n_hash_START (6)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_aes_sel_n_hash_END (6)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_aes_xor_crypto_key_START (7)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_aes_xor_crypto_key_END (7)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_ack_needed_START (8)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_ack_needed_END (9)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_mode_START (10)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_mode_END (13)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cmac_size0_START (14)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cmac_size0_END (14)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_do_START (15)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_do_END (16)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf0_START (17)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf0_END (18)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf1_START (19)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf1_END (19)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf2_START (20)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_cipher_conf2_END (21)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_key_size_START (22)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_key_size_END (23)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_setup_operation_START (24)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_setup_operation_END (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_din_sram_endianness_START (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_din_sram_endianness_END (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_dout_sram_endianness_START (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_dout_sram_endianness_END (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_word_swap_START (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_word_swap_END (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_bytes_swap_START (31)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD4_bytes_swap_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_addr_high : 16;
        unsigned int dout_addr_high : 16;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_din_addr_high_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_din_addr_high_END (15)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_dout_addr_high_START (16)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WORD5_dout_addr_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int watermark : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_watermark_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_WATERMARK_watermark_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int queue0_content : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_queue0_content_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE0_CONTENT_queue0_content_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_dma_address : 32;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_din_dma_address_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD0_din_dma_address_END (31)
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
        unsigned int reserved : 1;
        unsigned int din_virtual_host : 2;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_dma_mode_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_dma_mode_END (1)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_size_START (2)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_size_END (25)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_ns_bit_START (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_ns_bit_END (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_const_value_START (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_const_value_END (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_not_last_START (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_not_last_END (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_virtual_host_START (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD1_din_virtual_host_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dout_dma_address : 32;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_dout_dma_address_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD2_dout_dma_address_END (31)
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
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_dma_mode_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_dma_mode_END (1)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_size_START (2)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_size_END (25)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_ns_bit_START (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_ns_bit_END (26)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_last_ind_START (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_last_ind_END (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_hash_xor_bit_START (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_hash_xor_bit_END (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_virtual_host_START (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD3_dout_virtual_host_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int data_flow_mode : 6;
        unsigned int aes_sel_n_hash : 1;
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
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_data_flow_mode_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_data_flow_mode_END (5)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_aes_sel_n_hash_START (6)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_aes_sel_n_hash_END (6)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_aes_xor_crypto_key_START (7)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_aes_xor_crypto_key_END (7)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_ack_needed_START (8)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_ack_needed_END (9)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_mode_START (10)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_mode_END (13)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cmac_size0_START (14)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cmac_size0_END (14)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_do_START (15)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_do_END (16)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf0_START (17)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf0_END (18)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf1_START (19)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf1_END (19)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf2_START (20)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_cipher_conf2_END (21)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_key_size_START (22)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_key_size_END (23)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_setup_operation_START (24)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_setup_operation_END (27)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_din_sram_endianness_START (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_din_sram_endianness_END (28)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_dout_sram_endianness_START (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_dout_sram_endianness_END (29)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_word_swap_START (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_word_swap_END (30)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_bytes_swap_START (31)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD4_bytes_swap_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int din_addr_high : 16;
        unsigned int dout_addr_high : 16;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_din_addr_high_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_din_addr_high_END (15)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_dout_addr_high_START (16)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WORD5_dout_addr_high_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int watermark : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_watermark_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_WATERMARK_watermark_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int queue1_content : 10;
        unsigned int reserved : 22;
    } reg;
} SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_UNION;
#endif
#define SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_queue1_content_START (0)
#define SOC_SECENG_P_DSCRPTR_QUEUE1_CONTENT_queue1_content_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_data : 32;
    } reg;
} SOC_SECENG_P_SRAM_DATA_UNION;
#endif
#define SOC_SECENG_P_SRAM_DATA_sram_data_START (0)
#define SOC_SECENG_P_SRAM_DATA_sram_data_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_addr : 15;
        unsigned int reserved : 17;
    } reg;
} SOC_SECENG_P_SRAM_ADDR_UNION;
#endif
#define SOC_SECENG_P_SRAM_ADDR_sram_addr_START (0)
#define SOC_SECENG_P_SRAM_ADDR_sram_addr_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sram_ready : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SECENG_P_SRAM_DATA_READY_UNION;
#endif
#define SOC_SECENG_P_SRAM_DATA_READY_sram_ready_START (0)
#define SOC_SECENG_P_SRAM_DATA_READY_sram_ready_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
