#ifndef __SOC_ASP_HDMI_INTERFACE_H__
#define __SOC_ASP_HDMI_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ASP_HDMI_ASP_TX3_ADDR(base) ((base) + (0x000))
#define SOC_ASP_HDMI_ASP_DER_ADDR(base) ((base) + (0x004))
#define SOC_ASP_HDMI_ASP_DSTOP_ADDR(base) ((base) + (0x008))
#define SOC_ASP_HDMI_ASP_ASS_ISR_ADDR(base) ((base) + (0x00C))
#define SOC_ASP_HDMI_ASP_IRSR_ADDR(base) ((base) + (0x010))
#define SOC_ASP_HDMI_ASP_IER_ADDR(base) ((base) + (0x014))
#define SOC_ASP_HDMI_ASP_IMSR_ADDR(base) ((base) + (0x018))
#define SOC_ASP_HDMI_ASP_ICR_ADDR(base) ((base) + (0x01C))
#define SOC_ASP_HDMI_ASP_PCMNSSR_ADDR(base) ((base) + (0x020))
#define SOC_ASP_HDMI_ASP_P30CGR_ADDR(base) ((base) + (0x028))
#define SOC_ASP_HDMI_ASP_P31CGR_ADDR(base) ((base) + (0x02C))
#define SOC_ASP_HDMI_ASP_P32CGR_ADDR(base) ((base) + (0x030))
#define SOC_ASP_HDMI_ASP_P33CGR_ADDR(base) ((base) + (0x034))
#define SOC_ASP_HDMI_ASP_P34CGR_ADDR(base) ((base) + (0x038))
#define SOC_ASP_HDMI_ASP_P35CGR_ADDR(base) ((base) + (0x03C))
#define SOC_ASP_HDMI_ASP_P36CGR_ADDR(base) ((base) + (0x040))
#define SOC_ASP_HDMI_ASP_P37CGR_ADDR(base) ((base) + (0x044))
#define SOC_ASP_HDMI_ASP_P3ASAR_ADDR(base) ((base) + (0x048))
#define SOC_ASP_HDMI_ASP_P3ADLR_ADDR(base) ((base) + (0x04C))
#define SOC_ASP_HDMI_ASP_P3BSAR_ADDR(base) ((base) + (0x050))
#define SOC_ASP_HDMI_ASP_P3BDLR_ADDR(base) ((base) + (0x054))
#define SOC_ASP_HDMI_ASP_SPDIFSEL_ADDR(base) ((base) + (0x058))
#define SOC_ASP_HDMI_ASP_P3ADLS_ADDR(base) ((base) + (0x05C))
#define SOC_ASP_HDMI_ASP_P3BDLS_ADDR(base) ((base) + (0x060))
#define SOC_ASP_HDMI_ASP_FDS_ADDR(base) ((base) + (0x064))
#define SOC_ASP_HDMI_ASP_P3ADL_ADDR(base) ((base) + (0x068))
#define SOC_ASP_HDMI_ASP_P3BDL_ADDR(base) ((base) + (0x06C))
#define SOC_ASP_HDMI_ASP_SECURE_ADDR(base) ((base) + (0x070))
#define SOC_ASP_HDMI_RESERVED1_ADDR(base) ((base) + (0x074))
#define SOC_ASP_HDMI_SIO1_ASPIF_SEL_ADDR(base) ((base) + (0x400))
#define SOC_ASP_HDMI_SIO1_RAW_INT_ADDR(base) ((base) + (0x408))
#define SOC_ASP_HDMI_SIO1_INT_CLR_ADDR(base) ((base) + (0x40C))
#define SOC_ASP_HDMI_SIO1_INT_ENABLE_ADDR(base) ((base) + (0x410))
#define SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_ADDR(base) ((base) + (0x414))
#define SOC_ASP_HDMI_SIO1_I2S_SET_ADDR(base) ((base) + (0x41C))
#define SOC_ASP_HDMI_SIO1_I2S_CLR_ADDR(base) ((base) + (0x420))
#define SOC_ASP_HDMI_SIO1_TX_STA_ADDR(base) ((base) + (0x42C))
#define SOC_ASP_HDMI_SIO1_CLR_ADDR(base) ((base) + (0x438))
#define SOC_ASP_HDMI_SIO1_TST_TX0_DATA_ADDR(base) ((base) + (0x440))
#define SOC_ASP_HDMI_SIO1_TST_TX1_DATA_ADDR(base) ((base) + (0x444))
#define SOC_ASP_HDMI_SIO1_TST_TX2_DATA_ADDR(base) ((base) + (0x448))
#define SOC_ASP_HDMI_SIO1_TST_TX3_DATA_ADDR(base) ((base) + (0x44C))
#define SOC_ASP_HDMI_SIO1_TST_TX4_DATA_ADDR(base) ((base) + (0x450))
#define SOC_ASP_HDMI_SIO1_TST_TX5_DATA_ADDR(base) ((base) + (0x454))
#define SOC_ASP_HDMI_SIO1_TST_TX6_DATA_ADDR(base) ((base) + (0x458))
#define SOC_ASP_HDMI_SIO1_TST_TX7_DATA_ADDR(base) ((base) + (0x45C))
#define SOC_ASP_HDMI_SPDIF_CTRL_ADDR(base) ((base) + (0x800))
#define SOC_ASP_HDMI_SPDIF_CONFIG_ADDR(base) ((base) + (0x804))
#define SOC_ASP_HDMI_SPDIF_INTRUPT_ADDR(base) ((base) + (0x808))
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_ADDR(base) ((base) + (0x80C))
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_ADDR(base) ((base) + (0x810))
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ADDR(base) ((base) + (0x820))
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ADDR(base) ((base) + (0x824))
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ADDR(base) ((base) + (0x828))
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ADDR(base) ((base) + (0x82C))
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ADDR(base) ((base) + (0x830))
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_ADDR(base) ((base) + (0x840))
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_ADDR(base) ((base) + (0x844))
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_ADDR(base) ((base) + (0x848))
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_ADDR(base) ((base) + (0x84C))
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_ADDR(base) ((base) + (0x850))
#define SOC_ASP_HDMI_SPDIF_EDITION_ADDR(base) ((base) + (0x8F0))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pcm3en : 1;
        unsigned int pcm3ge : 1;
        unsigned int pcm3tsen : 1;
        unsigned int pcm3_data_in_width : 3;
        unsigned int pcm3_halfword_align_en : 1;
        unsigned int pcm3_ch_num : 3;
        unsigned int pcm3_8bit_usymb : 1;
        unsigned int pcm3_big_endian : 1;
        unsigned int pcm3_switch_order : 1;
        unsigned int reserved : 19;
    } reg;
} SOC_ASP_HDMI_ASP_TX3_UNION;
#endif
#define SOC_ASP_HDMI_ASP_TX3_pcm3en_START (0)
#define SOC_ASP_HDMI_ASP_TX3_pcm3en_END (0)
#define SOC_ASP_HDMI_ASP_TX3_pcm3ge_START (1)
#define SOC_ASP_HDMI_ASP_TX3_pcm3ge_END (1)
#define SOC_ASP_HDMI_ASP_TX3_pcm3tsen_START (2)
#define SOC_ASP_HDMI_ASP_TX3_pcm3tsen_END (2)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_data_in_width_START (3)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_data_in_width_END (5)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_halfword_align_en_START (6)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_halfword_align_en_END (6)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_ch_num_START (7)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_ch_num_END (9)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_8bit_usymb_START (10)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_8bit_usymb_END (10)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_big_endian_START (11)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_big_endian_END (11)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_switch_order_START (12)
#define SOC_ASP_HDMI_ASP_TX3_pcm3_switch_order_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pcm3ade : 1;
        unsigned int pcm3bde : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ASP_HDMI_ASP_DER_UNION;
#endif
#define SOC_ASP_HDMI_ASP_DER_pcm3ade_START (0)
#define SOC_ASP_HDMI_ASP_DER_pcm3ade_END (0)
#define SOC_ASP_HDMI_ASP_DER_pcm3bde_START (1)
#define SOC_ASP_HDMI_ASP_DER_pcm3bde_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pcm3ads : 1;
        unsigned int pcm3bds : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ASP_HDMI_ASP_DSTOP_UNION;
#endif
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3ads_START (0)
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3ads_END (0)
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3bds_START (1)
#define SOC_ASP_HDMI_ASP_DSTOP_pcm3bds_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio1is : 1;
        unsigned int spdifis : 1;
        unsigned int aspis : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ASP_HDMI_ASP_ASS_ISR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_ASS_ISR_sio1is_START (0)
#define SOC_ASP_HDMI_ASP_ASS_ISR_sio1is_END (0)
#define SOC_ASP_HDMI_ASP_ASS_ISR_spdifis_START (1)
#define SOC_ASP_HDMI_ASP_ASS_ISR_spdifis_END (1)
#define SOC_ASP_HDMI_ASP_ASS_ISR_aspis_START (2)
#define SOC_ASP_HDMI_ASP_ASS_ISR_aspis_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3adfirs : 1;
        unsigned int p3bdfirs : 1;
        unsigned int aberirs : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ASP_HDMI_ASP_IRSR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_IRSR_p3adfirs_START (0)
#define SOC_ASP_HDMI_ASP_IRSR_p3adfirs_END (0)
#define SOC_ASP_HDMI_ASP_IRSR_p3bdfirs_START (1)
#define SOC_ASP_HDMI_ASP_IRSR_p3bdfirs_END (1)
#define SOC_ASP_HDMI_ASP_IRSR_aberirs_START (2)
#define SOC_ASP_HDMI_ASP_IRSR_aberirs_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3adfie : 1;
        unsigned int p3bdfie : 1;
        unsigned int aberie : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ASP_HDMI_ASP_IER_UNION;
#endif
#define SOC_ASP_HDMI_ASP_IER_p3adfie_START (0)
#define SOC_ASP_HDMI_ASP_IER_p3adfie_END (0)
#define SOC_ASP_HDMI_ASP_IER_p3bdfie_START (1)
#define SOC_ASP_HDMI_ASP_IER_p3bdfie_END (1)
#define SOC_ASP_HDMI_ASP_IER_aberie_START (2)
#define SOC_ASP_HDMI_ASP_IER_aberie_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3adfims : 1;
        unsigned int p3bdfims : 1;
        unsigned int aberims : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ASP_HDMI_ASP_IMSR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_IMSR_p3adfims_START (0)
#define SOC_ASP_HDMI_ASP_IMSR_p3adfims_END (0)
#define SOC_ASP_HDMI_ASP_IMSR_p3bdfims_START (1)
#define SOC_ASP_HDMI_ASP_IMSR_p3bdfims_END (1)
#define SOC_ASP_HDMI_ASP_IMSR_aberims_START (2)
#define SOC_ASP_HDMI_ASP_IMSR_aberims_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3adficr : 1;
        unsigned int p3bdficr : 1;
        unsigned int abericr : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ASP_HDMI_ASP_ICR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_ICR_p3adficr_START (0)
#define SOC_ASP_HDMI_ASP_ICR_p3adficr_END (0)
#define SOC_ASP_HDMI_ASP_ICR_p3bdficr_START (1)
#define SOC_ASP_HDMI_ASP_ICR_p3bdficr_END (1)
#define SOC_ASP_HDMI_ASP_ICR_abericr_START (2)
#define SOC_ASP_HDMI_ASP_ICR_abericr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3dsr : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASP_HDMI_ASP_PCMNSSR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_PCMNSSR_p3dsr_START (0)
#define SOC_ASP_HDMI_ASP_PCMNSSR_p3dsr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p30cgr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_ASP_P30CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P30CGR_p30cgr_START (0)
#define SOC_ASP_HDMI_ASP_P30CGR_p30cgr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p31cgr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_ASP_P31CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P31CGR_p31cgr_START (0)
#define SOC_ASP_HDMI_ASP_P31CGR_p31cgr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p32cgr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_ASP_P32CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P32CGR_p32cgr_START (0)
#define SOC_ASP_HDMI_ASP_P32CGR_p32cgr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p33cgr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_ASP_P33CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P33CGR_p33cgr_START (0)
#define SOC_ASP_HDMI_ASP_P33CGR_p33cgr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p34cgr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_ASP_P34CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P34CGR_p34cgr_START (0)
#define SOC_ASP_HDMI_ASP_P34CGR_p34cgr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p35cgr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_ASP_P35CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P35CGR_p35cgr_START (0)
#define SOC_ASP_HDMI_ASP_P35CGR_p35cgr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p36cgr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_ASP_P36CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P36CGR_p36cgr_START (0)
#define SOC_ASP_HDMI_ASP_P36CGR_p36cgr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p37cgr : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_ASP_P37CGR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P37CGR_p37cgr_START (0)
#define SOC_ASP_HDMI_ASP_P37CGR_p37cgr_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3asar : 32;
    } reg;
} SOC_ASP_HDMI_ASP_P3ASAR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ASAR_p3asar_START (0)
#define SOC_ASP_HDMI_ASP_P3ASAR_p3asar_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3adlr : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ASP_HDMI_ASP_P3ADLR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ADLR_p3adlr_START (0)
#define SOC_ASP_HDMI_ASP_P3ADLR_p3adlr_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3bsar : 32;
    } reg;
} SOC_ASP_HDMI_ASP_P3BSAR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BSAR_p3bsar_START (0)
#define SOC_ASP_HDMI_ASP_P3BSAR_p3bsar_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3bdlr : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ASP_HDMI_ASP_P3BDLR_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BDLR_p3bdlr_START (0)
#define SOC_ASP_HDMI_ASP_P3BDLR_p3bdlr_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spdifsel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASP_HDMI_ASP_SPDIFSEL_UNION;
#endif
#define SOC_ASP_HDMI_ASP_SPDIFSEL_spdifsel_START (0)
#define SOC_ASP_HDMI_ASP_SPDIFSEL_spdifsel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3adls : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ASP_HDMI_ASP_P3ADLS_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ADLS_p3adls_START (0)
#define SOC_ASP_HDMI_ASP_P3ADLS_p3adls_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3bdls : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ASP_HDMI_ASP_P3BDLS_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BDLS_p3bdls_START (0)
#define SOC_ASP_HDMI_ASP_P3BDLS_p3bdls_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pcm3_fds : 6;
        unsigned int reserved : 26;
    } reg;
} SOC_ASP_HDMI_ASP_FDS_UNION;
#endif
#define SOC_ASP_HDMI_ASP_FDS_pcm3_fds_START (0)
#define SOC_ASP_HDMI_ASP_FDS_pcm3_fds_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3adl : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ASP_HDMI_ASP_P3ADL_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3ADL_p3adl_START (0)
#define SOC_ASP_HDMI_ASP_P3ADL_p3adl_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int p3bdl : 20;
        unsigned int reserved : 12;
    } reg;
} SOC_ASP_HDMI_ASP_P3BDL_UNION;
#endif
#define SOC_ASP_HDMI_ASP_P3BDL_p3bdl_START (0)
#define SOC_ASP_HDMI_ASP_P3BDL_p3bdl_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int asp_secure_en_n : 1;
        unsigned int asp_addr_secure_en_n : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ASP_HDMI_ASP_SECURE_UNION;
#endif
#define SOC_ASP_HDMI_ASP_SECURE_asp_secure_en_n_START (0)
#define SOC_ASP_HDMI_ASP_SECURE_asp_secure_en_n_END (0)
#define SOC_ASP_HDMI_ASP_SECURE_asp_addr_secure_en_n_START (1)
#define SOC_ASP_HDMI_ASP_SECURE_asp_addr_secure_en_n_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 2;
        unsigned int reserved_1: 30;
    } reg;
} SOC_ASP_HDMI_RESERVED1_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int access_ctrl : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASP_HDMI_SIO1_ASPIF_SEL_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_ASPIF_SEL_access_ctrl_START (0)
#define SOC_ASP_HDMI_SIO1_ASPIF_SEL_access_ctrl_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int tx_int : 1;
        unsigned int reserved_1: 30;
    } reg;
} SOC_ASP_HDMI_SIO1_RAW_INT_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_RAW_INT_tx_int_START (1)
#define SOC_ASP_HDMI_SIO1_RAW_INT_tx_int_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int tx_int_clr : 1;
        unsigned int reserved_1 : 30;
    } reg;
} SOC_ASP_HDMI_SIO1_INT_CLR_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_INT_CLR_tx_int_clr_START (1)
#define SOC_ASP_HDMI_SIO1_INT_CLR_tx_int_clr_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int tx_int_enable : 1;
        unsigned int reserved_1 : 30;
    } reg;
} SOC_ASP_HDMI_SIO1_INT_ENABLE_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_INT_ENABLE_tx_int_enable_START (1)
#define SOC_ASP_HDMI_SIO1_INT_ENABLE_tx_int_enable_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int tx_int_mask : 1;
        unsigned int reserved_1 : 30;
    } reg;
} SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_tx_int_mask_START (1)
#define SOC_ASP_HDMI_SIO1_INT_MASKED_STATUS_tx_int_mask_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int tx_ws_sel : 1;
        unsigned int tx_clk_sel : 1;
        unsigned int tx_fifo_threshold : 5;
        unsigned int reserved_1 : 5;
        unsigned int tx_fifo_disable : 1;
        unsigned int reserved_2 : 1;
        unsigned int tx_enable : 1;
        unsigned int reserved_3 : 1;
        unsigned int dsp_mode : 1;
        unsigned int tx_rx_reset_n : 1;
        unsigned int reserved_4 : 12;
    } reg;
} SOC_ASP_HDMI_SIO1_I2S_SET_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_ws_sel_START (2)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_ws_sel_END (2)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_clk_sel_START (3)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_clk_sel_END (3)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_threshold_START (4)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_threshold_END (8)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_disable_START (14)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_fifo_disable_END (14)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_enable_START (16)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_enable_END (16)
#define SOC_ASP_HDMI_SIO1_I2S_SET_dsp_mode_START (18)
#define SOC_ASP_HDMI_SIO1_I2S_SET_dsp_mode_END (18)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_rx_reset_n_START (19)
#define SOC_ASP_HDMI_SIO1_I2S_SET_tx_rx_reset_n_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 2;
        unsigned int tx_ws_sel_clr : 1;
        unsigned int tx_clk_sel_clr : 1;
        unsigned int tx_fifo_threshold_clr : 5;
        unsigned int reserved_1 : 5;
        unsigned int tx_fifo_disable_clr : 1;
        unsigned int reserved_2 : 1;
        unsigned int tx_enable_clr : 1;
        unsigned int reserved_3 : 1;
        unsigned int dsp_mode_clr : 1;
        unsigned int tx_rx_reset_n_clr : 1;
        unsigned int reserved_4 : 12;
    } reg;
} SOC_ASP_HDMI_SIO1_I2S_CLR_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_ws_sel_clr_START (2)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_ws_sel_clr_END (2)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_clk_sel_clr_START (3)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_clk_sel_clr_END (3)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_threshold_clr_START (4)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_threshold_clr_END (8)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_disable_clr_START (14)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_fifo_disable_clr_END (14)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_enable_clr_START (16)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_enable_clr_END (16)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_dsp_mode_clr_START (18)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_dsp_mode_clr_END (18)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_rx_reset_n_clr_START (19)
#define SOC_ASP_HDMI_SIO1_I2S_CLR_tx_rx_reset_n_clr_END (19)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_rfifo_over : 1;
        unsigned int tx_lfifo_over : 1;
        unsigned int tx_rfifo_depth : 6;
        unsigned int tx_lfifo_depth : 6;
        unsigned int reserved : 18;
    } reg;
} SOC_ASP_HDMI_SIO1_TX_STA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_over_START (0)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_over_END (0)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_over_START (1)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_over_END (1)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_depth_START (2)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_rfifo_depth_END (7)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_depth_START (8)
#define SOC_ASP_HDMI_SIO1_TX_STA_tx_lfifo_depth_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int tx_clr : 1;
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 30;
    } reg;
} SOC_ASP_HDMI_SIO1_CLR_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_CLR_tx_clr_START (0)
#define SOC_ASP_HDMI_SIO1_CLR_tx_clr_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio1_tst_tx0_data : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX0_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX0_DATA_sio1_tst_tx0_data_START (0)
#define SOC_ASP_HDMI_SIO1_TST_TX0_DATA_sio1_tst_tx0_data_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio1_tst_tx1_data : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX1_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX1_DATA_sio1_tst_tx1_data_START (0)
#define SOC_ASP_HDMI_SIO1_TST_TX1_DATA_sio1_tst_tx1_data_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio1_tst_tx2_data : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX2_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX2_DATA_sio1_tst_tx2_data_START (0)
#define SOC_ASP_HDMI_SIO1_TST_TX2_DATA_sio1_tst_tx2_data_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio1_tst_tx3_data : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX3_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX3_DATA_sio1_tst_tx3_data_START (0)
#define SOC_ASP_HDMI_SIO1_TST_TX3_DATA_sio1_tst_tx3_data_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio1_tst_tx4_data : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX4_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX4_DATA_sio1_tst_tx4_data_START (0)
#define SOC_ASP_HDMI_SIO1_TST_TX4_DATA_sio1_tst_tx4_data_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio1_tst_tx5_data : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX5_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX5_DATA_sio1_tst_tx5_data_START (0)
#define SOC_ASP_HDMI_SIO1_TST_TX5_DATA_sio1_tst_tx5_data_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio1_tst_tx6_data : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX6_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX6_DATA_sio1_tst_tx6_data_START (0)
#define SOC_ASP_HDMI_SIO1_TST_TX6_DATA_sio1_tst_tx6_data_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int sio1_tst_tx7_data : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_ASP_HDMI_SIO1_TST_TX7_DATA_UNION;
#endif
#define SOC_ASP_HDMI_SIO1_TST_TX7_DATA_sio1_tst_tx7_data_START (0)
#define SOC_ASP_HDMI_SIO1_TST_TX7_DATA_sio1_tst_tx7_data_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spdif_en : 1;
        unsigned int afifo_wlevel : 3;
        unsigned int intr_en : 1;
        unsigned int dma_en : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_ASP_HDMI_SPDIF_CTRL_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CTRL_spdif_en_START (0)
#define SOC_ASP_HDMI_SPDIF_CTRL_spdif_en_END (0)
#define SOC_ASP_HDMI_SPDIF_CTRL_afifo_wlevel_START (1)
#define SOC_ASP_HDMI_SPDIF_CTRL_afifo_wlevel_END (3)
#define SOC_ASP_HDMI_SPDIF_CTRL_intr_en_START (4)
#define SOC_ASP_HDMI_SPDIF_CTRL_intr_en_END (4)
#define SOC_ASP_HDMI_SPDIF_CTRL_dma_en_START (5)
#define SOC_ASP_HDMI_SPDIF_CTRL_dma_en_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int validity_info : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ASP_HDMI_SPDIF_CONFIG_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CONFIG_validity_info_START (0)
#define SOC_ASP_HDMI_SPDIF_CONFIG_validity_info_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afifo_empty_intr : 1;
        unsigned int afifo_single_intr : 1;
        unsigned int dma_burstintr : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ASP_HDMI_SPDIF_INTRUPT_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_empty_intr_START (0)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_empty_intr_END (0)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_single_intr_START (1)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_afifo_single_intr_END (1)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_dma_burstintr_START (2)
#define SOC_ASP_HDMI_SPDIF_INTRUPT_dma_burstintr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afifo_empty_intr_mask : 1;
        unsigned int afifo_single_intr_mask : 1;
        unsigned int dma_burstintr_mask : 1;
        unsigned int reserved : 29;
    } reg;
} SOC_ASP_HDMI_SPDIF_INTR_MASK_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_empty_intr_mask_START (0)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_empty_intr_mask_END (0)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_single_intr_mask_START (1)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_afifo_single_intr_mask_END (1)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_dma_burstintr_mask_START (2)
#define SOC_ASP_HDMI_SPDIF_INTR_MASK_dma_burstintr_mask_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int afifo_empty_intr_state : 1;
        unsigned int afifo_single_intr_state : 1;
        unsigned int dma_burstintr_state : 1;
        unsigned int afifo_depth : 5;
        unsigned int reserved : 24;
    } reg;
} SOC_ASP_HDMI_SPDIF_FIFO_STATE_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_empty_intr_state_START (0)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_empty_intr_state_END (0)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_single_intr_state_START (1)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_single_intr_state_END (1)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_dma_burstintr_state_START (2)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_dma_burstintr_state_END (2)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_depth_START (3)
#define SOC_ASP_HDMI_SPDIF_FIFO_STATE_afifo_depth_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_status1_0 : 1;
        unsigned int ch_status1_1 : 1;
        unsigned int ch_status1_2 : 1;
        unsigned int ch_status1_5 : 3;
        unsigned int ch_status1_7 : 2;
        unsigned int ch_status1_8 : 1;
        unsigned int ch_status1_9 : 1;
        unsigned int ch_status1_10 : 1;
        unsigned int ch_status1_13 : 3;
        unsigned int ch_status1 : 2;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS1_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_0_START (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_0_END (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_1_START (1)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_1_END (1)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_2_START (2)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_2_END (2)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_5_START (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_5_END (5)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_7_START (6)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_7_END (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_8_START (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_8_END (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_9_START (9)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_9_END (9)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_10_START (10)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_10_END (10)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_13_START (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_13_END (13)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_START (14)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS1_ch_status1_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_status2_7 : 8;
        unsigned int ch_status2_15 : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS2_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_7_START (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_7_END (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_15_START (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS2_ch_status2_15_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_status3_3 : 4;
        unsigned int ch_status3_7 : 4;
        unsigned int ch_status3_11 : 4;
        unsigned int ch_status3_15 : 4;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS3_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_3_START (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_3_END (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_7_START (4)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_7_END (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_11_START (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_11_END (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_15_START (12)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS3_ch_status3_15_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_status4_3 : 4;
        unsigned int ch_status4_5 : 2;
        unsigned int ch_status4_7 : 2;
        unsigned int ch_status4_11 : 4;
        unsigned int ch_status4_13 : 2;
        unsigned int ch_status4_15 : 2;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS4_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_3_START (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_3_END (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_5_START (4)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_5_END (5)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_7_START (6)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_7_END (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_11_START (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_11_END (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_13_START (12)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_13_END (13)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_15_START (14)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS4_ch_status4_15_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ch_status5_0 : 1;
        unsigned int ch_status5_3 : 3;
        unsigned int ch_status5_7 : 4;
        unsigned int ch_status5_8 : 1;
        unsigned int ch_status5_11 : 3;
        unsigned int ch_status5_15 : 4;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_CH_STATUS5_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_0_START (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_0_END (0)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_3_START (1)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_3_END (3)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_7_START (4)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_7_END (7)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_8_START (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_8_END (8)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_11_START (9)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_11_END (11)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_15_START (12)
#define SOC_ASP_HDMI_SPDIF_CH_STATUS5_ch_status5_15_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int user_data1_lc : 8;
        unsigned int user_data1_rc : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA1_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_lc_START (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_lc_END (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_rc_START (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA1_user_data1_rc_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int user_data2_lc : 8;
        unsigned int user_data2_rc : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA2_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_lc_START (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_lc_END (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_rc_START (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA2_user_data2_rc_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int user_data3_lc : 8;
        unsigned int user_data3_rc : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA3_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_lc_START (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_lc_END (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_rc_START (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA3_user_data3_rc_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int user_data4_lc : 8;
        unsigned int user_data4_rc : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA4_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_lc_START (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_lc_END (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_rc_START (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA4_user_data4_rc_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int user_data5_lc : 8;
        unsigned int user_data5_rc : 8;
        unsigned int reserved : 16;
    } reg;
} SOC_ASP_HDMI_SPDIF_USER_DATA5_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_lc_START (0)
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_lc_END (7)
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_rc_START (8)
#define SOC_ASP_HDMI_SPDIF_USER_DATA5_user_data5_rc_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spdif_edition : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_ASP_HDMI_SPDIF_EDITION_UNION;
#endif
#define SOC_ASP_HDMI_SPDIF_EDITION_spdif_edition_START (0)
#define SOC_ASP_HDMI_SPDIF_EDITION_spdif_edition_END (7)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
