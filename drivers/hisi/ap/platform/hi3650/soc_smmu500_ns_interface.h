#ifndef __SOC_SMMU500_NS_INTERFACE_H__
#define __SOC_SMMU500_NS_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_SMMU500_NS_SMMU_CR0_ADDR(base) ((base) + (0x0000))
#define SOC_SMMU500_NS_SMMU_ACR_ADDR(base) ((base) + (0x0010))
#define SOC_SMMU500_NS_SMMU_IDR0_ADDR(base) ((base) + (0x0020))
#define SOC_SMMU500_NS_SMMU_IDR1_ADDR(base) ((base) + (0x0024))
#define SOC_SMMU500_NS_SMMU_IDR2_ADDR(base) ((base) + (0x0028))
#define SOC_SMMU500_NS_SMMU_IDR7_ADDR(base) ((base) + (0x003C))
#define SOC_SMMU500_NS_SMMU_GFAR_LOW_ADDR(base) ((base) + (0x0040))
#define SOC_SMMU500_NS_SMMU_GFAR_HIGH_ADDR(base) ((base) + (0x0044))
#define SOC_SMMU500_NS_SMMU_GFSR_ADDR(base) ((base) + (0x0048))
#define SOC_SMMU500_NS_SMMU_GFSRRESTORE_ADDR(base) ((base) + (0x004C))
#define SOC_SMMU500_NS_SMMU_GFSYNR0_ADDR(base) ((base) + (0x0050))
#define SOC_SMMU500_NS_SMMU_GFSYNR1_ADDR(base) ((base) + (0x0054))
#define SOC_SMMU500_NS_SMMU_TLBIALLNSNH_ADDR(base) ((base) + (0x0068))
#define SOC_SMMU500_NS_SMMU_TLBGSYNC_ADDR(base) ((base) + (0x0070))
#define SOC_SMMU500_NS_SMMU_TLBGSTATUS_ADDR(base) ((base) + (0x0074))
#define SOC_SMMU500_NS_SMMU_SMR0_ADDR(base) ((base) + (0x0800))
#define SOC_SMMU500_NS_SMMU_SMR1_ADDR(base) ((base) + (0x0804))
#define SOC_SMMU500_NS_SMMU_SMR2_ADDR(base) ((base) + (0x0808))
#define SOC_SMMU500_NS_SMMU_SMR3_ADDR(base) ((base) + (0x080C))
#define SOC_SMMU500_NS_SMMU_S2CR0_ADDR(base) ((base) + (0x0C00))
#define SOC_SMMU500_NS_SMMU_S2CR1_ADDR(base) ((base) + (0x0C04))
#define SOC_SMMU500_NS_SMMU_S2CR2_ADDR(base) ((base) + (0x0C08))
#define SOC_SMMU500_NS_SMMU_S2CR3_ADDR(base) ((base) + (0x0C0C))
#define SOC_SMMU500_NS_SMMU_CBAR0_ADDR(base) ((base) + (0x1000))
#define SOC_SMMU500_NS_SMMU_CBAR1_ADDR(base) ((base) + (0x1004))
#define SOC_SMMU500_NS_SMMU_CBAR2_ADDR(base) ((base) + (0x1008))
#define SOC_SMMU500_NS_SMMU_CBAR3_ADDR(base) ((base) + (0x100C))
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA0_ADDR(base) ((base) + (0x1400))
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA1_ADDR(base) ((base) + (0x1404))
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA2_ADDR(base) ((base) + (0x1408))
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA3_ADDR(base) ((base) + (0x140C))
#define SOC_SMMU500_NS_ITCTRL_ADDR(base) ((base) + (0x2000))
#define SOC_SMMU500_NS_ITOP_ADDR(base) ((base) + (0x2008))
#define SOC_SMMU500_NS_ITIP_ADDR(base) ((base) + (0x2004))
#define SOC_SMMU500_NS_PMEVCNTR0_ADDR(base) ((base) + (0x3000))
#define SOC_SMMU500_NS_PMEVCNTR1_ADDR(base) ((base) + (0x3004))
#define SOC_SMMU500_NS_PMEVCNTR2_ADDR(base) ((base) + (0x3008))
#define SOC_SMMU500_NS_PMEVTYPE0_ADDR(base) ((base) + (0x3400))
#define SOC_SMMU500_NS_PMEVTYPE1_ADDR(base) ((base) + (0x3404))
#define SOC_SMMU500_NS_PMEVTYPE2_ADDR(base) ((base) + (0x3408))
#define SOC_SMMU500_NS_PMCGCR0_ADDR(base) ((base) + (0x3800))
#define SOC_SMMU500_NS_PMCGSMR0_ADDR(base) ((base) + (0x3A00))
#define SOC_SMMU500_NS_PMCNTENSET_ADDR(base) ((base) + (0x3C00))
#define SOC_SMMU500_NS_PMCNTENCLR_ADDR(base) ((base) + (0x3C20))
#define SOC_SMMU500_NS_PMINTENSET_ADDR(base) ((base) + (0x3C40))
#define SOC_SMMU500_NS_PMINTENCLR_ADDR(base) ((base) + (0x3C60))
#define SOC_SMMU500_NS_PMOVSCLR_ADDR(base) ((base) + (0x3C80))
#define SOC_SMMU500_NS_PMOVSSET_ADDR(base) ((base) + (0x3CC0))
#define SOC_SMMU500_NS_PMCFGR_ADDR(base) ((base) + (0x3E00))
#define SOC_SMMU500_NS_PMCR_ADDR(base) ((base) + (0x3E04))
#define SOC_SMMU500_NS_PMCEID0_ADDR(base) ((base) + (0x3E20))
#define SOC_SMMU500_NS_PMAUTHSTATUS_ADDR(base) ((base) + (0x3FB8))
#define SOC_SMMU500_NS_PMDEVTYPE_ADDR(base) ((base) + (0x3FCC))
#define SOC_SMMU500_NS_PERIPHID4_ADDR(base) ((base) + (0xFFD0))
#define SOC_SMMU500_NS_PERIPHID5_ADDR(base) ((base) + (0xFFD4))
#define SOC_SMMU500_NS_PERIPHID6_ADDR(base) ((base) + (0xFFD8))
#define SOC_SMMU500_NS_PERIPHID7_ADDR(base) ((base) + (0xFFDC))
#define SOC_SMMU500_NS_PERIPHID0_ADDR(base) ((base) + (0xFFE0))
#define SOC_SMMU500_NS_PERIPHID1_ADDR(base) ((base) + (0xFFE4))
#define SOC_SMMU500_NS_PERIPHID2_ADDR(base) ((base) + (0xFFE8))
#define SOC_SMMU500_NS_PERIPHID3_ADDR(base) ((base) + (0xFFEC))
#define SOC_SMMU500_NS_COMPONENTID0_ADDR(base) ((base) + (0xFFF0))
#define SOC_SMMU500_NS_COMPONENTID1_ADDR(base) ((base) + (0xFFF4))
#define SOC_SMMU500_NS_COMPONENTID2_ADDR(base) ((base) + (0xFFF8))
#define SOC_SMMU500_NS_COMPONENTID3_ADDR(base) ((base) + (0xFFFC))
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_ADDR(base) ((base) + (0x8000))
#define SOC_SMMU500_NS_SMMU_CB0_TTBR0_LOW_ADDR(base) ((base) + (0x8020))
#define SOC_SMMU500_NS_SMMU_CB0_TTBR0_HIGH_ADDR(base) ((base) + (0x8024))
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_ADDR(base) ((base) + (0x8030))
#define SOC_SMMU500_NS_SMMU_CB0_FSR_ADDR(base) ((base) + (0x8058))
#define SOC_SMMU500_NS_SMMU_CB0_FSRRESTORE_ADDR(base) ((base) + (0x805C))
#define SOC_SMMU500_NS_SMMU_CB0_FAR_LOW_ADDR(base) ((base) + (0x8060))
#define SOC_SMMU500_NS_SMMU_CB0_FAR_HIGH_ADDR(base) ((base) + (0x8064))
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_ADDR(base) ((base) + (0x8068))
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR0_ADDR(base) ((base) + (0x8E00))
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR1_ADDR(base) ((base) + (0x8E04))
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR2_ADDR(base) ((base) + (0x8E08))
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_ADDR(base) ((base) + (0x8E80))
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_ADDR(base) ((base) + (0x8E84))
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_ADDR(base) ((base) + (0x8E88))
#define SOC_SMMU500_NS_SMMU_CB0_PMCFGR_ADDR(base) ((base) + (0x8F00))
#define SOC_SMMU500_NS_SMMU_CB0_PMCR_ADDR(base) ((base) + (0x8F04))
#define SOC_SMMU500_NS_SMMU_CB0_PMCEID0_ADDR(base) ((base) + (0x8F20))
#define SOC_SMMU500_NS_SMMU_CB0_PMCNTENSET_ADDR(base) ((base) + (0x8F40))
#define SOC_SMMU500_NS_SMMU_CB0_PMCNTENCLR_ADDR(base) ((base) + (0x8F44))
#define SOC_SMMU500_NS_SMMU_CB0_PMINTENSET_ADDR(base) ((base) + (0x8F48))
#define SOC_SMMU500_NS_SMMU_CB0_PMINTENCLR_ADDR(base) ((base) + (0x8F4C))
#define SOC_SMMU500_NS_SMMU_CB0_PMOVSRCLR_ADDR(base) ((base) + (0x8F50))
#define SOC_SMMU500_NS_SMMU_CB0_PMOVSRSET_ADDR(base) ((base) + (0x8F58))
#define SOC_SMMU500_NS_SMMU_CB0_PMAUTHSTATUS_ADDR(base) ((base) + (0x8FB8))
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_ADDR(base) ((base) + (0x9000))
#define SOC_SMMU500_NS_SMMU_CB1_TTBR0_LOW_ADDR(base) ((base) + (0x9020))
#define SOC_SMMU500_NS_SMMU_CB1_TTBR0_HIGH_ADDR(base) ((base) + (0x9024))
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_ADDR(base) ((base) + (0x9030))
#define SOC_SMMU500_NS_SMMU_CB1_FSR_ADDR(base) ((base) + (0x9058))
#define SOC_SMMU500_NS_SMMU_CB1_FSRRESTORE_ADDR(base) ((base) + (0x905C))
#define SOC_SMMU500_NS_SMMU_CB1_FAR_LOW_ADDR(base) ((base) + (0x9060))
#define SOC_SMMU500_NS_SMMU_CB1_FAR_HIGH_ADDR(base) ((base) + (0x9064))
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_ADDR(base) ((base) + (0x9068))
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR0_ADDR(base) ((base) + (0x9E00))
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR1_ADDR(base) ((base) + (0x9E04))
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR2_ADDR(base) ((base) + (0x9E08))
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_ADDR(base) ((base) + (0x9E80))
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_ADDR(base) ((base) + (0x9E84))
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_ADDR(base) ((base) + (0x9E88))
#define SOC_SMMU500_NS_SMMU_CB1_PMCFGR_ADDR(base) ((base) + (0x9F00))
#define SOC_SMMU500_NS_SMMU_CB1_PMCR_ADDR(base) ((base) + (0x9F04))
#define SOC_SMMU500_NS_SMMU_CB1_PMCEID0_ADDR(base) ((base) + (0x9F20))
#define SOC_SMMU500_NS_SMMU_CB1_PMCNTENSET_ADDR(base) ((base) + (0x9F40))
#define SOC_SMMU500_NS_SMMU_CB1_PMCNTENCLR_ADDR(base) ((base) + (0x9F44))
#define SOC_SMMU500_NS_SMMU_CB1_PMINTENSET_ADDR(base) ((base) + (0x9F48))
#define SOC_SMMU500_NS_SMMU_CB1_PMINTENCLR_ADDR(base) ((base) + (0x9F4C))
#define SOC_SMMU500_NS_SMMU_CB1_PMOVSRCLR_ADDR(base) ((base) + (0x9F50))
#define SOC_SMMU500_NS_SMMU_CB1_PMOVSRSET_ADDR(base) ((base) + (0x9F58))
#define SOC_SMMU500_NS_SMMU_CB1_PMAUTHSTATUS_ADDR(base) ((base) + (0x9FB8))
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_ADDR(base) ((base) + (0xA000))
#define SOC_SMMU500_NS_SMMU_CB2_TTBR0_LOW_ADDR(base) ((base) + (0xA020))
#define SOC_SMMU500_NS_SMMU_CB2_TTBR0_HIGH_ADDR(base) ((base) + (0xA024))
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_ADDR(base) ((base) + (0xA030))
#define SOC_SMMU500_NS_SMMU_CB2_FSR_ADDR(base) ((base) + (0xA058))
#define SOC_SMMU500_NS_SMMU_CB2_FSRRESTORE_ADDR(base) ((base) + (0xA05C))
#define SOC_SMMU500_NS_SMMU_CB2_FAR_LOW_ADDR(base) ((base) + (0xA060))
#define SOC_SMMU500_NS_SMMU_CB2_FAR_HIGH_ADDR(base) ((base) + (0xA064))
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_ADDR(base) ((base) + (0xA068))
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR0_ADDR(base) ((base) + (0xAE00))
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR1_ADDR(base) ((base) + (0xAE04))
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR2_ADDR(base) ((base) + (0xAE08))
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_ADDR(base) ((base) + (0xAE80))
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_ADDR(base) ((base) + (0xAE84))
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_ADDR(base) ((base) + (0xAE88))
#define SOC_SMMU500_NS_SMMU_CB2_PMCFGR_ADDR(base) ((base) + (0xAF00))
#define SOC_SMMU500_NS_SMMU_CB2_PMCR_ADDR(base) ((base) + (0xAF04))
#define SOC_SMMU500_NS_SMMU_CB2_PMCEID0_ADDR(base) ((base) + (0xAF20))
#define SOC_SMMU500_NS_SMMU_CB2_PMCNTENSET_ADDR(base) ((base) + (0xAF40))
#define SOC_SMMU500_NS_SMMU_CB2_PMCNTENCLR_ADDR(base) ((base) + (0xAF44))
#define SOC_SMMU500_NS_SMMU_CB2_PMINTENSET_ADDR(base) ((base) + (0xAF48))
#define SOC_SMMU500_NS_SMMU_CB2_PMINTENCLR_ADDR(base) ((base) + (0xAF4C))
#define SOC_SMMU500_NS_SMMU_CB2_PMOVSRCLR_ADDR(base) ((base) + (0xAF50))
#define SOC_SMMU500_NS_SMMU_CB2_PMOVSRSET_ADDR(base) ((base) + (0xAF58))
#define SOC_SMMU500_NS_SMMU_CB2_PMAUTHSTATUS_ADDR(base) ((base) + (0xAFB8))
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_ADDR(base) ((base) + (0xB000))
#define SOC_SMMU500_NS_SMMU_CB3_TTBR0_LOW_ADDR(base) ((base) + (0xB020))
#define SOC_SMMU500_NS_SMMU_CB3_TTBR0_HIGH_ADDR(base) ((base) + (0xB024))
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_ADDR(base) ((base) + (0xB030))
#define SOC_SMMU500_NS_SMMU_CB3_FSR_ADDR(base) ((base) + (0xB058))
#define SOC_SMMU500_NS_SMMU_CB3_FSRRESTORE_ADDR(base) ((base) + (0xB05C))
#define SOC_SMMU500_NS_SMMU_CB3_FAR_LOW_ADDR(base) ((base) + (0xB060))
#define SOC_SMMU500_NS_SMMU_CB3_FAR_HIGH_ADDR(base) ((base) + (0xB064))
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_ADDR(base) ((base) + (0xB068))
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR0_ADDR(base) ((base) + (0xBE00))
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR1_ADDR(base) ((base) + (0xBE04))
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR2_ADDR(base) ((base) + (0xBE08))
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_ADDR(base) ((base) + (0xBE80))
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_ADDR(base) ((base) + (0xBE84))
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_ADDR(base) ((base) + (0xBE88))
#define SOC_SMMU500_NS_SMMU_CB3_PMCFGR_ADDR(base) ((base) + (0xBF00))
#define SOC_SMMU500_NS_SMMU_CB3_PMCR_ADDR(base) ((base) + (0xBF04))
#define SOC_SMMU500_NS_SMMU_CB3_PMCEID0_ADDR(base) ((base) + (0xBF20))
#define SOC_SMMU500_NS_SMMU_CB3_PMCNTENSET_ADDR(base) ((base) + (0xBF40))
#define SOC_SMMU500_NS_SMMU_CB3_PMCNTENCLR_ADDR(base) ((base) + (0x9F44))
#define SOC_SMMU500_NS_SMMU_CB3_PMINTENSET_ADDR(base) ((base) + (0xBF48))
#define SOC_SMMU500_NS_SMMU_CB3_PMINTENCLR_ADDR(base) ((base) + (0xBF4C))
#define SOC_SMMU500_NS_SMMU_CB3_PMOVSRCLR_ADDR(base) ((base) + (0xBF50))
#define SOC_SMMU500_NS_SMMU_CB3_PMOVSRSET_ADDR(base) ((base) + (0xBF58))
#define SOC_SMMU500_NS_SMMU_CB3_PMAUTHSTATUS_ADDR(base) ((base) + (0xBFB8))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int clientpd : 1;
        unsigned int gfre : 1;
        unsigned int gfie : 1;
        unsigned int reserved_0: 1;
        unsigned int gcfgfre : 1;
        unsigned int gcfgfie : 1;
        unsigned int reserved_1: 2;
        unsigned int stalld : 1;
        unsigned int gse : 1;
        unsigned int smtnmc : 1;
        unsigned int vmidpne : 1;
        unsigned int ptm : 1;
        unsigned int fb : 1;
        unsigned int bsu : 2;
        unsigned int memattr : 4;
        unsigned int mtcfg : 1;
        unsigned int smcfcfg : 1;
        unsigned int shcfg : 2;
        unsigned int racfg : 2;
        unsigned int wacfg : 2;
        unsigned int reserved_2: 4;
    } reg;
} SOC_SMMU500_NS_SMMU_CR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CR0_clientpd_START (0)
#define SOC_SMMU500_NS_SMMU_CR0_clientpd_END (0)
#define SOC_SMMU500_NS_SMMU_CR0_gfre_START (1)
#define SOC_SMMU500_NS_SMMU_CR0_gfre_END (1)
#define SOC_SMMU500_NS_SMMU_CR0_gfie_START (2)
#define SOC_SMMU500_NS_SMMU_CR0_gfie_END (2)
#define SOC_SMMU500_NS_SMMU_CR0_gcfgfre_START (4)
#define SOC_SMMU500_NS_SMMU_CR0_gcfgfre_END (4)
#define SOC_SMMU500_NS_SMMU_CR0_gcfgfie_START (5)
#define SOC_SMMU500_NS_SMMU_CR0_gcfgfie_END (5)
#define SOC_SMMU500_NS_SMMU_CR0_stalld_START (8)
#define SOC_SMMU500_NS_SMMU_CR0_stalld_END (8)
#define SOC_SMMU500_NS_SMMU_CR0_gse_START (9)
#define SOC_SMMU500_NS_SMMU_CR0_gse_END (9)
#define SOC_SMMU500_NS_SMMU_CR0_smtnmc_START (10)
#define SOC_SMMU500_NS_SMMU_CR0_smtnmc_END (10)
#define SOC_SMMU500_NS_SMMU_CR0_vmidpne_START (11)
#define SOC_SMMU500_NS_SMMU_CR0_vmidpne_END (11)
#define SOC_SMMU500_NS_SMMU_CR0_ptm_START (12)
#define SOC_SMMU500_NS_SMMU_CR0_ptm_END (12)
#define SOC_SMMU500_NS_SMMU_CR0_fb_START (13)
#define SOC_SMMU500_NS_SMMU_CR0_fb_END (13)
#define SOC_SMMU500_NS_SMMU_CR0_bsu_START (14)
#define SOC_SMMU500_NS_SMMU_CR0_bsu_END (15)
#define SOC_SMMU500_NS_SMMU_CR0_memattr_START (16)
#define SOC_SMMU500_NS_SMMU_CR0_memattr_END (19)
#define SOC_SMMU500_NS_SMMU_CR0_mtcfg_START (20)
#define SOC_SMMU500_NS_SMMU_CR0_mtcfg_END (20)
#define SOC_SMMU500_NS_SMMU_CR0_smcfcfg_START (21)
#define SOC_SMMU500_NS_SMMU_CR0_smcfcfg_END (21)
#define SOC_SMMU500_NS_SMMU_CR0_shcfg_START (22)
#define SOC_SMMU500_NS_SMMU_CR0_shcfg_END (23)
#define SOC_SMMU500_NS_SMMU_CR0_racfg_START (24)
#define SOC_SMMU500_NS_SMMU_CR0_racfg_END (25)
#define SOC_SMMU500_NS_SMMU_CR0_wacfg_START (26)
#define SOC_SMMU500_NS_SMMU_CR0_wacfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int prefetchen : 1;
        unsigned int wc1en : 1;
        unsigned int wc2en : 1;
        unsigned int reserved_0 : 5;
        unsigned int smtnmb_tlben : 1;
        unsigned int mmudisb_tlben : 1;
        unsigned int s2crb_tlben : 1;
        unsigned int reserved_1 : 21;
    } reg;
} SOC_SMMU500_NS_SMMU_ACR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_ACR_prefetchen_START (0)
#define SOC_SMMU500_NS_SMMU_ACR_prefetchen_END (0)
#define SOC_SMMU500_NS_SMMU_ACR_wc1en_START (1)
#define SOC_SMMU500_NS_SMMU_ACR_wc1en_END (1)
#define SOC_SMMU500_NS_SMMU_ACR_wc2en_START (2)
#define SOC_SMMU500_NS_SMMU_ACR_wc2en_END (2)
#define SOC_SMMU500_NS_SMMU_ACR_smtnmb_tlben_START (8)
#define SOC_SMMU500_NS_SMMU_ACR_smtnmb_tlben_END (8)
#define SOC_SMMU500_NS_SMMU_ACR_mmudisb_tlben_START (9)
#define SOC_SMMU500_NS_SMMU_ACR_mmudisb_tlben_END (9)
#define SOC_SMMU500_NS_SMMU_ACR_s2crb_tlben_START (10)
#define SOC_SMMU500_NS_SMMU_ACR_s2crb_tlben_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int numsmrg : 8;
        unsigned int reserved_0: 1;
        unsigned int numsidb : 4;
        unsigned int btm : 1;
        unsigned int cttw : 1;
        unsigned int reserved_1: 1;
        unsigned int numirpt : 8;
        unsigned int ptfs : 2;
        unsigned int atosns : 1;
        unsigned int sms : 1;
        unsigned int nts : 1;
        unsigned int s2ts : 1;
        unsigned int s1ts : 1;
        unsigned int ses : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_IDR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_IDR0_numsmrg_START (0)
#define SOC_SMMU500_NS_SMMU_IDR0_numsmrg_END (7)
#define SOC_SMMU500_NS_SMMU_IDR0_numsidb_START (9)
#define SOC_SMMU500_NS_SMMU_IDR0_numsidb_END (12)
#define SOC_SMMU500_NS_SMMU_IDR0_btm_START (13)
#define SOC_SMMU500_NS_SMMU_IDR0_btm_END (13)
#define SOC_SMMU500_NS_SMMU_IDR0_cttw_START (14)
#define SOC_SMMU500_NS_SMMU_IDR0_cttw_END (14)
#define SOC_SMMU500_NS_SMMU_IDR0_numirpt_START (16)
#define SOC_SMMU500_NS_SMMU_IDR0_numirpt_END (23)
#define SOC_SMMU500_NS_SMMU_IDR0_ptfs_START (24)
#define SOC_SMMU500_NS_SMMU_IDR0_ptfs_END (25)
#define SOC_SMMU500_NS_SMMU_IDR0_atosns_START (26)
#define SOC_SMMU500_NS_SMMU_IDR0_atosns_END (26)
#define SOC_SMMU500_NS_SMMU_IDR0_sms_START (27)
#define SOC_SMMU500_NS_SMMU_IDR0_sms_END (27)
#define SOC_SMMU500_NS_SMMU_IDR0_nts_START (28)
#define SOC_SMMU500_NS_SMMU_IDR0_nts_END (28)
#define SOC_SMMU500_NS_SMMU_IDR0_s2ts_START (29)
#define SOC_SMMU500_NS_SMMU_IDR0_s2ts_END (29)
#define SOC_SMMU500_NS_SMMU_IDR0_s1ts_START (30)
#define SOC_SMMU500_NS_SMMU_IDR0_s1ts_END (30)
#define SOC_SMMU500_NS_SMMU_IDR0_ses_START (31)
#define SOC_SMMU500_NS_SMMU_IDR0_ses_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int numcb : 8;
        unsigned int numssdndxb : 4;
        unsigned int ssdtp : 1;
        unsigned int reserved_0 : 2;
        unsigned int smcd : 1;
        unsigned int nums2cb : 8;
        unsigned int reserved_1 : 4;
        unsigned int numpagendxb : 3;
        unsigned int pagesize : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_IDR1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_IDR1_numcb_START (0)
#define SOC_SMMU500_NS_SMMU_IDR1_numcb_END (7)
#define SOC_SMMU500_NS_SMMU_IDR1_numssdndxb_START (8)
#define SOC_SMMU500_NS_SMMU_IDR1_numssdndxb_END (11)
#define SOC_SMMU500_NS_SMMU_IDR1_ssdtp_START (12)
#define SOC_SMMU500_NS_SMMU_IDR1_ssdtp_END (12)
#define SOC_SMMU500_NS_SMMU_IDR1_smcd_START (15)
#define SOC_SMMU500_NS_SMMU_IDR1_smcd_END (15)
#define SOC_SMMU500_NS_SMMU_IDR1_nums2cb_START (16)
#define SOC_SMMU500_NS_SMMU_IDR1_nums2cb_END (23)
#define SOC_SMMU500_NS_SMMU_IDR1_numpagendxb_START (28)
#define SOC_SMMU500_NS_SMMU_IDR1_numpagendxb_END (30)
#define SOC_SMMU500_NS_SMMU_IDR1_pagesize_START (31)
#define SOC_SMMU500_NS_SMMU_IDR1_pagesize_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ias : 4;
        unsigned int oas : 4;
        unsigned int ubs : 4;
        unsigned int PTFSv8_4kB : 1;
        unsigned int PTFSv8_16kB : 1;
        unsigned int PTFSv8_64kB : 1;
        unsigned int reserved : 17;
    } reg;
} SOC_SMMU500_NS_SMMU_IDR2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_IDR2_ias_START (0)
#define SOC_SMMU500_NS_SMMU_IDR2_ias_END (3)
#define SOC_SMMU500_NS_SMMU_IDR2_oas_START (4)
#define SOC_SMMU500_NS_SMMU_IDR2_oas_END (7)
#define SOC_SMMU500_NS_SMMU_IDR2_ubs_START (8)
#define SOC_SMMU500_NS_SMMU_IDR2_ubs_END (11)
#define SOC_SMMU500_NS_SMMU_IDR2_PTFSv8_4kB_START (12)
#define SOC_SMMU500_NS_SMMU_IDR2_PTFSv8_4kB_END (12)
#define SOC_SMMU500_NS_SMMU_IDR2_PTFSv8_16kB_START (13)
#define SOC_SMMU500_NS_SMMU_IDR2_PTFSv8_16kB_END (13)
#define SOC_SMMU500_NS_SMMU_IDR2_PTFSv8_64kB_START (14)
#define SOC_SMMU500_NS_SMMU_IDR2_PTFSv8_64kB_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int minor : 4;
        unsigned int major : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_IDR7_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_IDR7_minor_START (0)
#define SOC_SMMU500_NS_SMMU_IDR7_minor_END (3)
#define SOC_SMMU500_NS_SMMU_IDR7_major_START (4)
#define SOC_SMMU500_NS_SMMU_IDR7_major_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_low : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_GFAR_LOW_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_GFAR_LOW_faddr_low_START (0)
#define SOC_SMMU500_NS_SMMU_GFAR_LOW_faddr_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_high : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_GFAR_HIGH_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_GFAR_HIGH_faddr_high_START (0)
#define SOC_SMMU500_NS_SMMU_GFAR_HIGH_faddr_high_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int icf : 1;
        unsigned int usf : 1;
        unsigned int smcf : 1;
        unsigned int ucbf : 1;
        unsigned int ucif : 1;
        unsigned int caf : 1;
        unsigned int ef : 1;
        unsigned int pf : 1;
        unsigned int reserved : 23;
        unsigned int multi : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_GFSR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_GFSR_icf_START (0)
#define SOC_SMMU500_NS_SMMU_GFSR_icf_END (0)
#define SOC_SMMU500_NS_SMMU_GFSR_usf_START (1)
#define SOC_SMMU500_NS_SMMU_GFSR_usf_END (1)
#define SOC_SMMU500_NS_SMMU_GFSR_smcf_START (2)
#define SOC_SMMU500_NS_SMMU_GFSR_smcf_END (2)
#define SOC_SMMU500_NS_SMMU_GFSR_ucbf_START (3)
#define SOC_SMMU500_NS_SMMU_GFSR_ucbf_END (3)
#define SOC_SMMU500_NS_SMMU_GFSR_ucif_START (4)
#define SOC_SMMU500_NS_SMMU_GFSR_ucif_END (4)
#define SOC_SMMU500_NS_SMMU_GFSR_caf_START (5)
#define SOC_SMMU500_NS_SMMU_GFSR_caf_END (5)
#define SOC_SMMU500_NS_SMMU_GFSR_ef_START (6)
#define SOC_SMMU500_NS_SMMU_GFSR_ef_END (6)
#define SOC_SMMU500_NS_SMMU_GFSR_pf_START (7)
#define SOC_SMMU500_NS_SMMU_GFSR_pf_END (7)
#define SOC_SMMU500_NS_SMMU_GFSR_multi_START (31)
#define SOC_SMMU500_NS_SMMU_GFSR_multi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int smmu_gfsrrestore : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_GFSRRESTORE_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_GFSRRESTORE_smmu_gfsrrestore_START (0)
#define SOC_SMMU500_NS_SMMU_GFSRRESTORE_smmu_gfsrrestore_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nested : 1;
        unsigned int wnr : 1;
        unsigned int pnu : 1;
        unsigned int ind : 1;
        unsigned int nsstate : 1;
        unsigned int nsattr : 1;
        unsigned int reserved_0 : 2;
        unsigned int implementationdefined : 8;
        unsigned int reserved_1 : 16;
    } reg;
} SOC_SMMU500_NS_SMMU_GFSYNR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_GFSYNR0_nested_START (0)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_nested_END (0)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_wnr_START (1)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_wnr_END (1)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_pnu_START (2)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_pnu_END (2)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_ind_START (3)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_ind_END (3)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_nsstate_START (4)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_nsstate_END (4)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_nsattr_START (5)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_nsattr_END (5)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_implementationdefined_START (8)
#define SOC_SMMU500_NS_SMMU_GFSYNR0_implementationdefined_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int streamid : 2;
        unsigned int reserved_0: 14;
        unsigned int reserved_1: 16;
    } reg;
} SOC_SMMU500_NS_SMMU_GFSYNR1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_GFSYNR1_streamid_START (0)
#define SOC_SMMU500_NS_SMMU_GFSYNR1_streamid_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_TLBIALLNSNH_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_TLBGSYNC_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gsactive : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SMMU500_NS_SMMU_TLBGSTATUS_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_TLBGSTATUS_gsactive_START (0)
#define SOC_SMMU500_NS_SMMU_TLBGSTATUS_gsactive_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id : 2;
        unsigned int reserved_0: 13;
        unsigned int reserved_1: 1;
        unsigned int mask : 2;
        unsigned int reserved_2: 13;
        unsigned int valid : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_SMR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_SMR0_id_START (0)
#define SOC_SMMU500_NS_SMMU_SMR0_id_END (1)
#define SOC_SMMU500_NS_SMMU_SMR0_mask_START (16)
#define SOC_SMMU500_NS_SMMU_SMR0_mask_END (17)
#define SOC_SMMU500_NS_SMMU_SMR0_valid_START (31)
#define SOC_SMMU500_NS_SMMU_SMR0_valid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id : 2;
        unsigned int reserved_0: 13;
        unsigned int reserved_1: 1;
        unsigned int mask : 2;
        unsigned int reserved_2: 13;
        unsigned int valid : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_SMR1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_SMR1_id_START (0)
#define SOC_SMMU500_NS_SMMU_SMR1_id_END (1)
#define SOC_SMMU500_NS_SMMU_SMR1_mask_START (16)
#define SOC_SMMU500_NS_SMMU_SMR1_mask_END (17)
#define SOC_SMMU500_NS_SMMU_SMR1_valid_START (31)
#define SOC_SMMU500_NS_SMMU_SMR1_valid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id : 2;
        unsigned int reserved_0: 13;
        unsigned int reserved_1: 1;
        unsigned int mask : 2;
        unsigned int reserved_2: 13;
        unsigned int valid : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_SMR2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_SMR2_id_START (0)
#define SOC_SMMU500_NS_SMMU_SMR2_id_END (1)
#define SOC_SMMU500_NS_SMMU_SMR2_mask_START (16)
#define SOC_SMMU500_NS_SMMU_SMR2_mask_END (17)
#define SOC_SMMU500_NS_SMMU_SMR2_valid_START (31)
#define SOC_SMMU500_NS_SMMU_SMR2_valid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id : 2;
        unsigned int reserved_0: 13;
        unsigned int reserved_1: 1;
        unsigned int mask : 2;
        unsigned int reserved_2: 13;
        unsigned int valid : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_SMR3_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_SMR3_id_START (0)
#define SOC_SMMU500_NS_SMMU_SMR3_id_END (1)
#define SOC_SMMU500_NS_SMMU_SMR3_mask_START (16)
#define SOC_SMMU500_NS_SMMU_SMR3_mask_END (17)
#define SOC_SMMU500_NS_SMMU_SMR3_valid_START (31)
#define SOC_SMMU500_NS_SMMU_SMR3_valid_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cbndx : 2;
        unsigned int reserved_0 : 6;
        unsigned int shcfg : 2;
        unsigned int reserved_1 : 1;
        unsigned int mtcfg : 1;
        unsigned int memattr : 4;
        unsigned int type : 2;
        unsigned int nscfg : 2;
        unsigned int racfg : 2;
        unsigned int wacfg : 2;
        unsigned int privcfg : 2;
        unsigned int instcfg : 2;
        unsigned int implementationdefined : 4;
    } reg;
} SOC_SMMU500_NS_SMMU_S2CR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_S2CR0_cbndx_START (0)
#define SOC_SMMU500_NS_SMMU_S2CR0_cbndx_END (1)
#define SOC_SMMU500_NS_SMMU_S2CR0_shcfg_START (8)
#define SOC_SMMU500_NS_SMMU_S2CR0_shcfg_END (9)
#define SOC_SMMU500_NS_SMMU_S2CR0_mtcfg_START (11)
#define SOC_SMMU500_NS_SMMU_S2CR0_mtcfg_END (11)
#define SOC_SMMU500_NS_SMMU_S2CR0_memattr_START (12)
#define SOC_SMMU500_NS_SMMU_S2CR0_memattr_END (15)
#define SOC_SMMU500_NS_SMMU_S2CR0_type_START (16)
#define SOC_SMMU500_NS_SMMU_S2CR0_type_END (17)
#define SOC_SMMU500_NS_SMMU_S2CR0_nscfg_START (18)
#define SOC_SMMU500_NS_SMMU_S2CR0_nscfg_END (19)
#define SOC_SMMU500_NS_SMMU_S2CR0_racfg_START (20)
#define SOC_SMMU500_NS_SMMU_S2CR0_racfg_END (21)
#define SOC_SMMU500_NS_SMMU_S2CR0_wacfg_START (22)
#define SOC_SMMU500_NS_SMMU_S2CR0_wacfg_END (23)
#define SOC_SMMU500_NS_SMMU_S2CR0_privcfg_START (24)
#define SOC_SMMU500_NS_SMMU_S2CR0_privcfg_END (25)
#define SOC_SMMU500_NS_SMMU_S2CR0_instcfg_START (26)
#define SOC_SMMU500_NS_SMMU_S2CR0_instcfg_END (27)
#define SOC_SMMU500_NS_SMMU_S2CR0_implementationdefined_START (28)
#define SOC_SMMU500_NS_SMMU_S2CR0_implementationdefined_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cbndx : 2;
        unsigned int reserved_0 : 6;
        unsigned int shcfg : 2;
        unsigned int reserved_1 : 1;
        unsigned int mtcfg : 1;
        unsigned int memattr : 4;
        unsigned int type : 2;
        unsigned int nscfg : 2;
        unsigned int racfg : 2;
        unsigned int wacfg : 2;
        unsigned int privcfg : 2;
        unsigned int instcfg : 2;
        unsigned int implementationdefined : 4;
    } reg;
} SOC_SMMU500_NS_SMMU_S2CR1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_S2CR1_cbndx_START (0)
#define SOC_SMMU500_NS_SMMU_S2CR1_cbndx_END (1)
#define SOC_SMMU500_NS_SMMU_S2CR1_shcfg_START (8)
#define SOC_SMMU500_NS_SMMU_S2CR1_shcfg_END (9)
#define SOC_SMMU500_NS_SMMU_S2CR1_mtcfg_START (11)
#define SOC_SMMU500_NS_SMMU_S2CR1_mtcfg_END (11)
#define SOC_SMMU500_NS_SMMU_S2CR1_memattr_START (12)
#define SOC_SMMU500_NS_SMMU_S2CR1_memattr_END (15)
#define SOC_SMMU500_NS_SMMU_S2CR1_type_START (16)
#define SOC_SMMU500_NS_SMMU_S2CR1_type_END (17)
#define SOC_SMMU500_NS_SMMU_S2CR1_nscfg_START (18)
#define SOC_SMMU500_NS_SMMU_S2CR1_nscfg_END (19)
#define SOC_SMMU500_NS_SMMU_S2CR1_racfg_START (20)
#define SOC_SMMU500_NS_SMMU_S2CR1_racfg_END (21)
#define SOC_SMMU500_NS_SMMU_S2CR1_wacfg_START (22)
#define SOC_SMMU500_NS_SMMU_S2CR1_wacfg_END (23)
#define SOC_SMMU500_NS_SMMU_S2CR1_privcfg_START (24)
#define SOC_SMMU500_NS_SMMU_S2CR1_privcfg_END (25)
#define SOC_SMMU500_NS_SMMU_S2CR1_instcfg_START (26)
#define SOC_SMMU500_NS_SMMU_S2CR1_instcfg_END (27)
#define SOC_SMMU500_NS_SMMU_S2CR1_implementationdefined_START (28)
#define SOC_SMMU500_NS_SMMU_S2CR1_implementationdefined_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cbndx : 2;
        unsigned int reserved_0 : 6;
        unsigned int shcfg : 2;
        unsigned int reserved_1 : 1;
        unsigned int mtcfg : 1;
        unsigned int memattr : 4;
        unsigned int type : 2;
        unsigned int nscfg : 2;
        unsigned int racfg : 2;
        unsigned int wacfg : 2;
        unsigned int privcfg : 2;
        unsigned int instcfg : 2;
        unsigned int implementationdefined : 4;
    } reg;
} SOC_SMMU500_NS_SMMU_S2CR2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_S2CR2_cbndx_START (0)
#define SOC_SMMU500_NS_SMMU_S2CR2_cbndx_END (1)
#define SOC_SMMU500_NS_SMMU_S2CR2_shcfg_START (8)
#define SOC_SMMU500_NS_SMMU_S2CR2_shcfg_END (9)
#define SOC_SMMU500_NS_SMMU_S2CR2_mtcfg_START (11)
#define SOC_SMMU500_NS_SMMU_S2CR2_mtcfg_END (11)
#define SOC_SMMU500_NS_SMMU_S2CR2_memattr_START (12)
#define SOC_SMMU500_NS_SMMU_S2CR2_memattr_END (15)
#define SOC_SMMU500_NS_SMMU_S2CR2_type_START (16)
#define SOC_SMMU500_NS_SMMU_S2CR2_type_END (17)
#define SOC_SMMU500_NS_SMMU_S2CR2_nscfg_START (18)
#define SOC_SMMU500_NS_SMMU_S2CR2_nscfg_END (19)
#define SOC_SMMU500_NS_SMMU_S2CR2_racfg_START (20)
#define SOC_SMMU500_NS_SMMU_S2CR2_racfg_END (21)
#define SOC_SMMU500_NS_SMMU_S2CR2_wacfg_START (22)
#define SOC_SMMU500_NS_SMMU_S2CR2_wacfg_END (23)
#define SOC_SMMU500_NS_SMMU_S2CR2_privcfg_START (24)
#define SOC_SMMU500_NS_SMMU_S2CR2_privcfg_END (25)
#define SOC_SMMU500_NS_SMMU_S2CR2_instcfg_START (26)
#define SOC_SMMU500_NS_SMMU_S2CR2_instcfg_END (27)
#define SOC_SMMU500_NS_SMMU_S2CR2_implementationdefined_START (28)
#define SOC_SMMU500_NS_SMMU_S2CR2_implementationdefined_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cbndx : 2;
        unsigned int reserved_0 : 6;
        unsigned int shcfg : 2;
        unsigned int reserved_1 : 1;
        unsigned int mtcfg : 1;
        unsigned int memattr : 4;
        unsigned int type : 2;
        unsigned int nscfg : 2;
        unsigned int racfg : 2;
        unsigned int wacfg : 2;
        unsigned int privcfg : 2;
        unsigned int instcfg : 2;
        unsigned int implementationdefined : 4;
    } reg;
} SOC_SMMU500_NS_SMMU_S2CR3_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_S2CR3_cbndx_START (0)
#define SOC_SMMU500_NS_SMMU_S2CR3_cbndx_END (1)
#define SOC_SMMU500_NS_SMMU_S2CR3_shcfg_START (8)
#define SOC_SMMU500_NS_SMMU_S2CR3_shcfg_END (9)
#define SOC_SMMU500_NS_SMMU_S2CR3_mtcfg_START (11)
#define SOC_SMMU500_NS_SMMU_S2CR3_mtcfg_END (11)
#define SOC_SMMU500_NS_SMMU_S2CR3_memattr_START (12)
#define SOC_SMMU500_NS_SMMU_S2CR3_memattr_END (15)
#define SOC_SMMU500_NS_SMMU_S2CR3_type_START (16)
#define SOC_SMMU500_NS_SMMU_S2CR3_type_END (17)
#define SOC_SMMU500_NS_SMMU_S2CR3_nscfg_START (18)
#define SOC_SMMU500_NS_SMMU_S2CR3_nscfg_END (19)
#define SOC_SMMU500_NS_SMMU_S2CR3_racfg_START (20)
#define SOC_SMMU500_NS_SMMU_S2CR3_racfg_END (21)
#define SOC_SMMU500_NS_SMMU_S2CR3_wacfg_START (22)
#define SOC_SMMU500_NS_SMMU_S2CR3_wacfg_END (23)
#define SOC_SMMU500_NS_SMMU_S2CR3_privcfg_START (24)
#define SOC_SMMU500_NS_SMMU_S2CR3_privcfg_END (25)
#define SOC_SMMU500_NS_SMMU_S2CR3_instcfg_START (26)
#define SOC_SMMU500_NS_SMMU_S2CR3_instcfg_END (27)
#define SOC_SMMU500_NS_SMMU_S2CR3_implementationdefined_START (28)
#define SOC_SMMU500_NS_SMMU_S2CR3_implementationdefined_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vmid : 8;
        unsigned int reserved_0: 8;
        unsigned int type : 2;
        unsigned int sbz : 2;
        unsigned int reserved_1: 4;
        unsigned int irptdx : 8;
    } reg;
} SOC_SMMU500_NS_SMMU_CBAR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CBAR0_vmid_START (0)
#define SOC_SMMU500_NS_SMMU_CBAR0_vmid_END (7)
#define SOC_SMMU500_NS_SMMU_CBAR0_type_START (16)
#define SOC_SMMU500_NS_SMMU_CBAR0_type_END (17)
#define SOC_SMMU500_NS_SMMU_CBAR0_sbz_START (18)
#define SOC_SMMU500_NS_SMMU_CBAR0_sbz_END (19)
#define SOC_SMMU500_NS_SMMU_CBAR0_irptdx_START (24)
#define SOC_SMMU500_NS_SMMU_CBAR0_irptdx_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vmid : 8;
        unsigned int reserved_0: 8;
        unsigned int type : 2;
        unsigned int sbz : 2;
        unsigned int reserved_1: 4;
        unsigned int irptdx : 8;
    } reg;
} SOC_SMMU500_NS_SMMU_CBAR1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CBAR1_vmid_START (0)
#define SOC_SMMU500_NS_SMMU_CBAR1_vmid_END (7)
#define SOC_SMMU500_NS_SMMU_CBAR1_type_START (16)
#define SOC_SMMU500_NS_SMMU_CBAR1_type_END (17)
#define SOC_SMMU500_NS_SMMU_CBAR1_sbz_START (18)
#define SOC_SMMU500_NS_SMMU_CBAR1_sbz_END (19)
#define SOC_SMMU500_NS_SMMU_CBAR1_irptdx_START (24)
#define SOC_SMMU500_NS_SMMU_CBAR1_irptdx_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vmid : 8;
        unsigned int reserved_0: 8;
        unsigned int type : 2;
        unsigned int sbz : 2;
        unsigned int reserved_1: 4;
        unsigned int irptdx : 8;
    } reg;
} SOC_SMMU500_NS_SMMU_CBAR2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CBAR2_vmid_START (0)
#define SOC_SMMU500_NS_SMMU_CBAR2_vmid_END (7)
#define SOC_SMMU500_NS_SMMU_CBAR2_type_START (16)
#define SOC_SMMU500_NS_SMMU_CBAR2_type_END (17)
#define SOC_SMMU500_NS_SMMU_CBAR2_sbz_START (18)
#define SOC_SMMU500_NS_SMMU_CBAR2_sbz_END (19)
#define SOC_SMMU500_NS_SMMU_CBAR2_irptdx_START (24)
#define SOC_SMMU500_NS_SMMU_CBAR2_irptdx_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vmid : 8;
        unsigned int reserved_0: 8;
        unsigned int type : 2;
        unsigned int sbz : 2;
        unsigned int reserved_1: 4;
        unsigned int irptdx : 8;
    } reg;
} SOC_SMMU500_NS_SMMU_CBAR3_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CBAR3_vmid_START (0)
#define SOC_SMMU500_NS_SMMU_CBAR3_vmid_END (7)
#define SOC_SMMU500_NS_SMMU_CBAR3_type_START (16)
#define SOC_SMMU500_NS_SMMU_CBAR3_type_END (17)
#define SOC_SMMU500_NS_SMMU_CBAR3_sbz_START (18)
#define SOC_SMMU500_NS_SMMU_CBAR3_sbz_END (19)
#define SOC_SMMU500_NS_SMMU_CBAR3_irptdx_START (24)
#define SOC_SMMU500_NS_SMMU_CBAR3_irptdx_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int streamid : 2;
        unsigned int reserved_0: 14;
        unsigned int ssd_index : 15;
        unsigned int reserved_1: 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CBFRSYNRA0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA0_streamid_START (0)
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA0_streamid_END (1)
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA0_ssd_index_START (16)
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA0_ssd_index_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int streamid : 2;
        unsigned int reserved_0: 14;
        unsigned int ssd_index : 15;
        unsigned int reserved_1: 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CBFRSYNRA1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA1_streamid_START (0)
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA1_streamid_END (1)
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA1_ssd_index_START (16)
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA1_ssd_index_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int streamid : 2;
        unsigned int reserved_0: 14;
        unsigned int ssd_index : 15;
        unsigned int reserved_1: 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CBFRSYNRA2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA2_streamid_START (0)
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA2_streamid_END (1)
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA2_ssd_index_START (16)
#define SOC_SMMU500_NS_SMMU_CBFRSYNRA2_ssd_index_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CBFRSYNRA3_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int integration_mode : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SMMU500_NS_ITCTRL_UNION;
#endif
#define SOC_SMMU500_NS_ITCTRL_integration_mode_START (0)
#define SOC_SMMU500_NS_ITCTRL_integration_mode_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int nscaf : 1;
        unsigned int gnsf : 1;
        unsigned int pi : 1;
        unsigned int ci : 1;
        unsigned int reserved_0: 4;
        unsigned int scaf : 1;
        unsigned int gsf : 1;
        unsigned int reserved_1: 22;
    } reg;
} SOC_SMMU500_NS_ITOP_UNION;
#endif
#define SOC_SMMU500_NS_ITOP_nscaf_START (0)
#define SOC_SMMU500_NS_ITOP_nscaf_END (0)
#define SOC_SMMU500_NS_ITOP_gnsf_START (1)
#define SOC_SMMU500_NS_ITOP_gnsf_END (1)
#define SOC_SMMU500_NS_ITOP_pi_START (2)
#define SOC_SMMU500_NS_ITOP_pi_END (2)
#define SOC_SMMU500_NS_ITOP_ci_START (3)
#define SOC_SMMU500_NS_ITOP_ci_END (3)
#define SOC_SMMU500_NS_ITOP_scaf_START (8)
#define SOC_SMMU500_NS_ITOP_scaf_END (8)
#define SOC_SMMU500_NS_ITOP_gsf_START (9)
#define SOC_SMMU500_NS_ITOP_gsf_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int spniden : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_SMMU500_NS_ITIP_UNION;
#endif
#define SOC_SMMU500_NS_ITIP_spniden_START (0)
#define SOC_SMMU500_NS_ITIP_spniden_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntrn : 32;
    } reg;
} SOC_SMMU500_NS_PMEVCNTR0_UNION;
#endif
#define SOC_SMMU500_NS_PMEVCNTR0_evcntrn_START (0)
#define SOC_SMMU500_NS_PMEVCNTR0_evcntrn_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntrn : 32;
    } reg;
} SOC_SMMU500_NS_PMEVCNTR1_UNION;
#endif
#define SOC_SMMU500_NS_PMEVCNTR1_evcntrn_START (0)
#define SOC_SMMU500_NS_PMEVCNTR1_evcntrn_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntrn : 32;
    } reg;
} SOC_SMMU500_NS_PMEVCNTR2_UNION;
#endif
#define SOC_SMMU500_NS_PMEVCNTR2_evcntrn_START (0)
#define SOC_SMMU500_NS_PMEVCNTR2_evcntrn_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_PMEVTYPE0_UNION;
#endif
#define SOC_SMMU500_NS_PMEVTYPE0_event_START (0)
#define SOC_SMMU500_NS_PMEVTYPE0_event_END (4)
#define SOC_SMMU500_NS_PMEVTYPE0_nsu_START (28)
#define SOC_SMMU500_NS_PMEVTYPE0_nsu_END (28)
#define SOC_SMMU500_NS_PMEVTYPE0_nsp_START (29)
#define SOC_SMMU500_NS_PMEVTYPE0_nsp_END (29)
#define SOC_SMMU500_NS_PMEVTYPE0_u_START (30)
#define SOC_SMMU500_NS_PMEVTYPE0_u_END (30)
#define SOC_SMMU500_NS_PMEVTYPE0_p_START (31)
#define SOC_SMMU500_NS_PMEVTYPE0_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_PMEVTYPE1_UNION;
#endif
#define SOC_SMMU500_NS_PMEVTYPE1_event_START (0)
#define SOC_SMMU500_NS_PMEVTYPE1_event_END (4)
#define SOC_SMMU500_NS_PMEVTYPE1_nsu_START (28)
#define SOC_SMMU500_NS_PMEVTYPE1_nsu_END (28)
#define SOC_SMMU500_NS_PMEVTYPE1_nsp_START (29)
#define SOC_SMMU500_NS_PMEVTYPE1_nsp_END (29)
#define SOC_SMMU500_NS_PMEVTYPE1_u_START (30)
#define SOC_SMMU500_NS_PMEVTYPE1_u_END (30)
#define SOC_SMMU500_NS_PMEVTYPE1_p_START (31)
#define SOC_SMMU500_NS_PMEVTYPE1_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_PMEVTYPE2_UNION;
#endif
#define SOC_SMMU500_NS_PMEVTYPE2_event_START (0)
#define SOC_SMMU500_NS_PMEVTYPE2_event_END (4)
#define SOC_SMMU500_NS_PMEVTYPE2_nsu_START (28)
#define SOC_SMMU500_NS_PMEVTYPE2_nsu_END (28)
#define SOC_SMMU500_NS_PMEVTYPE2_nsp_START (29)
#define SOC_SMMU500_NS_PMEVTYPE2_nsp_END (29)
#define SOC_SMMU500_NS_PMEVTYPE2_u_START (30)
#define SOC_SMMU500_NS_PMEVTYPE2_u_END (30)
#define SOC_SMMU500_NS_PMEVTYPE2_p_START (31)
#define SOC_SMMU500_NS_PMEVTYPE2_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ndx : 2;
        unsigned int reserved_0: 6;
        unsigned int tcefcfg : 2;
        unsigned int cbaen : 1;
        unsigned int cen : 1;
        unsigned int ex : 1;
        unsigned int reserved_1: 3;
        unsigned int sidg : 7;
        unsigned int reserved_2: 1;
        unsigned int cgnc : 4;
        unsigned int reserved_3: 4;
    } reg;
} SOC_SMMU500_NS_PMCGCR0_UNION;
#endif
#define SOC_SMMU500_NS_PMCGCR0_ndx_START (0)
#define SOC_SMMU500_NS_PMCGCR0_ndx_END (1)
#define SOC_SMMU500_NS_PMCGCR0_tcefcfg_START (8)
#define SOC_SMMU500_NS_PMCGCR0_tcefcfg_END (9)
#define SOC_SMMU500_NS_PMCGCR0_cbaen_START (10)
#define SOC_SMMU500_NS_PMCGCR0_cbaen_END (10)
#define SOC_SMMU500_NS_PMCGCR0_cen_START (11)
#define SOC_SMMU500_NS_PMCGCR0_cen_END (11)
#define SOC_SMMU500_NS_PMCGCR0_ex_START (12)
#define SOC_SMMU500_NS_PMCGCR0_ex_END (12)
#define SOC_SMMU500_NS_PMCGCR0_sidg_START (16)
#define SOC_SMMU500_NS_PMCGCR0_sidg_END (22)
#define SOC_SMMU500_NS_PMCGCR0_cgnc_START (24)
#define SOC_SMMU500_NS_PMCGCR0_cgnc_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int id : 2;
        unsigned int reserved_0: 13;
        unsigned int reserved_1: 1;
        unsigned int mask : 2;
        unsigned int reserved_2: 13;
        unsigned int reserved_3: 1;
    } reg;
} SOC_SMMU500_NS_PMCGSMR0_UNION;
#endif
#define SOC_SMMU500_NS_PMCGSMR0_id_START (0)
#define SOC_SMMU500_NS_PMCGSMR0_id_END (1)
#define SOC_SMMU500_NS_PMCGSMR0_mask_START (16)
#define SOC_SMMU500_NS_PMCGSMR0_mask_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_PMCNTENSET_UNION;
#endif
#define SOC_SMMU500_NS_PMCNTENSET_enableset_START (0)
#define SOC_SMMU500_NS_PMCNTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_PMCNTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_PMCNTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_PMCNTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_PMINTENSET_UNION;
#endif
#define SOC_SMMU500_NS_PMINTENSET_enableset_START (0)
#define SOC_SMMU500_NS_PMINTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_PMINTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_PMINTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_PMINTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_PMOVSCLR_UNION;
#endif
#define SOC_SMMU500_NS_PMOVSCLR_enableclr_START (0)
#define SOC_SMMU500_NS_PMOVSCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_PMOVSSET_UNION;
#endif
#define SOC_SMMU500_NS_PMOVSSET_enableset_START (0)
#define SOC_SMMU500_NS_PMOVSSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int n : 8;
        unsigned int reserved_0: 3;
        unsigned int size : 2;
        unsigned int reserved_1: 1;
        unsigned int cc : 1;
        unsigned int ccd : 1;
        unsigned int ex : 1;
        unsigned int na : 1;
        unsigned int wt : 1;
        unsigned int uen : 1;
        unsigned int reserved_2: 4;
        unsigned int ncg : 8;
    } reg;
} SOC_SMMU500_NS_PMCFGR_UNION;
#endif
#define SOC_SMMU500_NS_PMCFGR_n_START (0)
#define SOC_SMMU500_NS_PMCFGR_n_END (7)
#define SOC_SMMU500_NS_PMCFGR_size_START (11)
#define SOC_SMMU500_NS_PMCFGR_size_END (12)
#define SOC_SMMU500_NS_PMCFGR_cc_START (14)
#define SOC_SMMU500_NS_PMCFGR_cc_END (14)
#define SOC_SMMU500_NS_PMCFGR_ccd_START (15)
#define SOC_SMMU500_NS_PMCFGR_ccd_END (15)
#define SOC_SMMU500_NS_PMCFGR_ex_START (16)
#define SOC_SMMU500_NS_PMCFGR_ex_END (16)
#define SOC_SMMU500_NS_PMCFGR_na_START (17)
#define SOC_SMMU500_NS_PMCFGR_na_END (17)
#define SOC_SMMU500_NS_PMCFGR_wt_START (18)
#define SOC_SMMU500_NS_PMCFGR_wt_END (18)
#define SOC_SMMU500_NS_PMCFGR_uen_START (19)
#define SOC_SMMU500_NS_PMCFGR_uen_END (19)
#define SOC_SMMU500_NS_PMCFGR_ncg_START (24)
#define SOC_SMMU500_NS_PMCFGR_ncg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int e : 1;
        unsigned int p : 1;
        unsigned int reserved_0: 2;
        unsigned int x : 1;
        unsigned int reserved_1: 3;
        unsigned int reserved_2: 24;
    } reg;
} SOC_SMMU500_NS_PMCR_UNION;
#endif
#define SOC_SMMU500_NS_PMCR_e_START (0)
#define SOC_SMMU500_NS_PMCR_e_END (0)
#define SOC_SMMU500_NS_PMCR_p_START (1)
#define SOC_SMMU500_NS_PMCR_p_END (1)
#define SOC_SMMU500_NS_PMCR_x_START (4)
#define SOC_SMMU500_NS_PMCR_x_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmceid0 : 32;
    } reg;
} SOC_SMMU500_NS_PMCEID0_UNION;
#endif
#define SOC_SMMU500_NS_PMCEID0_pmceid0_START (0)
#define SOC_SMMU500_NS_PMCEID0_pmceid0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmauthstatus : 32;
    } reg;
} SOC_SMMU500_NS_PMAUTHSTATUS_UNION;
#endif
#define SOC_SMMU500_NS_PMAUTHSTATUS_pmauthstatus_START (0)
#define SOC_SMMU500_NS_PMAUTHSTATUS_pmauthstatus_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmdevtype : 32;
    } reg;
} SOC_SMMU500_NS_PMDEVTYPE_UNION;
#endif
#define SOC_SMMU500_NS_PMDEVTYPE_pmdevtype_START (0)
#define SOC_SMMU500_NS_PMDEVTYPE_pmdevtype_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int code : 4;
        unsigned int count : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_PERIPHID4_UNION;
#endif
#define SOC_SMMU500_NS_PERIPHID4_code_START (0)
#define SOC_SMMU500_NS_PERIPHID4_code_END (3)
#define SOC_SMMU500_NS_PERIPHID4_count_START (4)
#define SOC_SMMU500_NS_PERIPHID4_count_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_SMMU500_NS_PERIPHID5_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_SMMU500_NS_PERIPHID6_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_SMMU500_NS_PERIPHID7_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int partnumber0 : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_PERIPHID0_UNION;
#endif
#define SOC_SMMU500_NS_PERIPHID0_partnumber0_START (0)
#define SOC_SMMU500_NS_PERIPHID0_partnumber0_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int partnumber1 : 4;
        unsigned int jep106identitycode : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_PERIPHID1_UNION;
#endif
#define SOC_SMMU500_NS_PERIPHID1_partnumber1_START (0)
#define SOC_SMMU500_NS_PERIPHID1_partnumber1_END (3)
#define SOC_SMMU500_NS_PERIPHID1_jep106identitycode_START (4)
#define SOC_SMMU500_NS_PERIPHID1_jep106identitycode_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int jep106identitycode : 3;
        unsigned int jedec : 1;
        unsigned int revision : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_PERIPHID2_UNION;
#endif
#define SOC_SMMU500_NS_PERIPHID2_jep106identitycode_START (0)
#define SOC_SMMU500_NS_PERIPHID2_jep106identitycode_END (2)
#define SOC_SMMU500_NS_PERIPHID2_jedec_START (3)
#define SOC_SMMU500_NS_PERIPHID2_jedec_END (3)
#define SOC_SMMU500_NS_PERIPHID2_revision_START (4)
#define SOC_SMMU500_NS_PERIPHID2_revision_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int customermodified : 4;
        unsigned int revand : 4;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_PERIPHID3_UNION;
#endif
#define SOC_SMMU500_NS_PERIPHID3_customermodified_START (0)
#define SOC_SMMU500_NS_PERIPHID3_customermodified_END (3)
#define SOC_SMMU500_NS_PERIPHID3_revand_START (4)
#define SOC_SMMU500_NS_PERIPHID3_revand_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int preamble : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_COMPONENTID0_UNION;
#endif
#define SOC_SMMU500_NS_COMPONENTID0_preamble_START (0)
#define SOC_SMMU500_NS_COMPONENTID0_preamble_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int preamble : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_COMPONENTID1_UNION;
#endif
#define SOC_SMMU500_NS_COMPONENTID1_preamble_START (0)
#define SOC_SMMU500_NS_COMPONENTID1_preamble_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int preamble : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_COMPONENTID2_UNION;
#endif
#define SOC_SMMU500_NS_COMPONENTID2_preamble_START (0)
#define SOC_SMMU500_NS_COMPONENTID2_preamble_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int preamble : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_COMPONENTID3_UNION;
#endif
#define SOC_SMMU500_NS_COMPONENTID3_preamble_START (0)
#define SOC_SMMU500_NS_COMPONENTID3_preamble_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m : 1;
        unsigned int tre : 1;
        unsigned int afe : 1;
        unsigned int affd : 1;
        unsigned int e : 1;
        unsigned int cfre : 1;
        unsigned int cfie : 1;
        unsigned int cfcfg : 1;
        unsigned int hupcf : 1;
        unsigned int reserved_0: 4;
        unsigned int reserved_1: 1;
        unsigned int bsu : 2;
        unsigned int memattr : 4;
        unsigned int reserved_2: 1;
        unsigned int fb : 1;
        unsigned int shcfg : 2;
        unsigned int racfg : 2;
        unsigned int wacfg : 2;
        unsigned int reserved_3: 4;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_SCTLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_m_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_m_END (0)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_tre_START (1)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_tre_END (1)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_afe_START (2)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_afe_END (2)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_affd_START (3)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_affd_END (3)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_e_START (4)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_e_END (4)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_cfre_START (5)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_cfre_END (5)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_cfie_START (6)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_cfie_END (6)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_cfcfg_START (7)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_cfcfg_END (7)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_hupcf_START (8)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_hupcf_END (8)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_bsu_START (14)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_bsu_END (15)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_memattr_START (16)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_memattr_END (19)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_fb_START (21)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_fb_END (21)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_shcfg_START (22)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_shcfg_END (23)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_racfg_START (24)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_racfg_END (25)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_wacfg_START (26)
#define SOC_SMMU500_NS_SMMU_CB0_SCTLR_wacfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int translationtablebaseregister_low : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_TTBR0_LOW_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_TTBR0_LOW_translationtablebaseregister_low_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_TTBR0_LOW_translationtablebaseregister_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int translationtablebaseregister_high : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_TTBR0_HIGH_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_TTBR0_HIGH_translationtablebaseregister_high_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_TTBR0_HIGH_translationtablebaseregister_high_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t0sz : 4;
        unsigned int s : 1;
        unsigned int reserved_0: 1;
        unsigned int sl0 : 2;
        unsigned int irgn0 : 2;
        unsigned int orgn0 : 2;
        unsigned int sh0 : 2;
        unsigned int reserved_1: 17;
        unsigned int eae : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_TTBCR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_t0sz_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_t0sz_END (3)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_s_START (4)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_s_END (4)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_sl0_START (6)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_sl0_END (7)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_irgn0_START (8)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_irgn0_END (9)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_orgn0_START (10)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_orgn0_END (11)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_sh0_START (12)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_sh0_END (13)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_eae_START (31)
#define SOC_SMMU500_NS_SMMU_CB0_TTBCR_eae_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int tf : 1;
        unsigned int aff : 1;
        unsigned int pf : 1;
        unsigned int ef : 1;
        unsigned int tlbmcf : 1;
        unsigned int tlblkf : 1;
        unsigned int reserved_1: 23;
        unsigned int ss : 1;
        unsigned int multi : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_FSR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_FSR_tf_START (1)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_tf_END (1)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_aff_START (2)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_aff_END (2)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_pf_START (3)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_pf_END (3)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_ef_START (4)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_ef_END (4)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_tlbmcf_START (5)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_tlbmcf_END (5)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_tlblkf_START (6)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_tlblkf_END (6)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_ss_START (30)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_ss_END (30)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_multi_START (31)
#define SOC_SMMU500_NS_SMMU_CB0_FSR_multi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int smmu_cb0_fsrrestore : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_FSRRESTORE_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_FSRRESTORE_smmu_cb0_fsrrestore_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_FSRRESTORE_smmu_cb0_fsrrestore_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_low : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_FAR_LOW_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_FAR_LOW_faddr_low_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_FAR_LOW_faddr_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_high : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_FAR_HIGH_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_FAR_HIGH_faddr_high_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_FAR_HIGH_faddr_high_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int plvl : 2;
        unsigned int reserved_0: 2;
        unsigned int wnr : 1;
        unsigned int pnu : 1;
        unsigned int ind : 1;
        unsigned int nsstate : 1;
        unsigned int nsattr : 1;
        unsigned int atof : 1;
        unsigned int ptwf : 1;
        unsigned int afr : 1;
        unsigned int reserved_1: 20;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_FSYNR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_plvl_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_plvl_END (1)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_wnr_START (4)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_wnr_END (4)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_pnu_START (5)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_pnu_END (5)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_ind_START (6)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_ind_END (6)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_nsstate_START (7)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_nsstate_END (7)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_nsattr_START (8)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_nsattr_END (8)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_atof_START (9)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_atof_END (9)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_ptwf_START (10)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_ptwf_END (10)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_afr_START (11)
#define SOC_SMMU500_NS_SMMU_CB0_FSYNR0_afr_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr0 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR0_evcntr0_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR0_evcntr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr1 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR1_evcntr1_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR1_evcntr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr2 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR2_evcntr2_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVCNTR2_evcntr2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER0_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER1_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB0_PMXEVTYPER2_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cb0_pmcfgr : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMCFGR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMCFGR_cb0_pmcfgr_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMCFGR_cb0_pmcfgr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int e : 1;
        unsigned int p : 1;
        unsigned int reserved_0: 2;
        unsigned int x : 1;
        unsigned int reserved_1: 3;
        unsigned int reserved_2: 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMCR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMCR_e_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMCR_e_END (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMCR_p_START (1)
#define SOC_SMMU500_NS_SMMU_CB0_PMCR_p_END (1)
#define SOC_SMMU500_NS_SMMU_CB0_PMCR_x_START (4)
#define SOC_SMMU500_NS_SMMU_CB0_PMCR_x_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmceid0 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMCEID0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMCEID0_pmceid0_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMCEID0_pmceid0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMCNTENSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMCNTENSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMCNTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMCNTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMCNTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMCNTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMINTENSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMINTENSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMINTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMINTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMINTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMINTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMOVSRCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMOVSRCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMOVSRCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMOVSRSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMOVSRSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMOVSRSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmauthstatus : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB0_PMAUTHSTATUS_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB0_PMAUTHSTATUS_pmauthstatus_START (0)
#define SOC_SMMU500_NS_SMMU_CB0_PMAUTHSTATUS_pmauthstatus_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m : 1;
        unsigned int tre : 1;
        unsigned int afe : 1;
        unsigned int affd : 1;
        unsigned int e : 1;
        unsigned int cfre : 1;
        unsigned int cfie : 1;
        unsigned int cfcfg : 1;
        unsigned int hupcf : 1;
        unsigned int reserved_0: 4;
        unsigned int reserved_1: 1;
        unsigned int bsu : 2;
        unsigned int memattr : 4;
        unsigned int reserved_2: 1;
        unsigned int fb : 1;
        unsigned int shcfg : 2;
        unsigned int racfg : 2;
        unsigned int wacfg : 2;
        unsigned int reserved_3: 4;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_SCTLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_m_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_m_END (0)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_tre_START (1)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_tre_END (1)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_afe_START (2)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_afe_END (2)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_affd_START (3)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_affd_END (3)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_e_START (4)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_e_END (4)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_cfre_START (5)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_cfre_END (5)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_cfie_START (6)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_cfie_END (6)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_cfcfg_START (7)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_cfcfg_END (7)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_hupcf_START (8)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_hupcf_END (8)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_bsu_START (14)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_bsu_END (15)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_memattr_START (16)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_memattr_END (19)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_fb_START (21)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_fb_END (21)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_shcfg_START (22)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_shcfg_END (23)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_racfg_START (24)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_racfg_END (25)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_wacfg_START (26)
#define SOC_SMMU500_NS_SMMU_CB1_SCTLR_wacfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int translationtablebaseregister_low : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_TTBR0_LOW_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_TTBR0_LOW_translationtablebaseregister_low_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_TTBR0_LOW_translationtablebaseregister_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int translationtablebaseregister_high : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_TTBR0_HIGH_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_TTBR0_HIGH_translationtablebaseregister_high_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_TTBR0_HIGH_translationtablebaseregister_high_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t0sz : 4;
        unsigned int s : 1;
        unsigned int reserved_0: 1;
        unsigned int sl0 : 2;
        unsigned int irgn0 : 2;
        unsigned int orgn0 : 2;
        unsigned int sh0 : 2;
        unsigned int reserved_1: 17;
        unsigned int eae : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_TTBCR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_t0sz_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_t0sz_END (3)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_s_START (4)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_s_END (4)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_sl0_START (6)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_sl0_END (7)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_irgn0_START (8)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_irgn0_END (9)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_orgn0_START (10)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_orgn0_END (11)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_sh0_START (12)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_sh0_END (13)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_eae_START (31)
#define SOC_SMMU500_NS_SMMU_CB1_TTBCR_eae_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int tf : 1;
        unsigned int aff : 1;
        unsigned int pf : 1;
        unsigned int ef : 1;
        unsigned int tlbmcf : 1;
        unsigned int tlblkf : 1;
        unsigned int reserved_1: 23;
        unsigned int ss : 1;
        unsigned int multi : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_FSR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_FSR_tf_START (1)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_tf_END (1)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_aff_START (2)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_aff_END (2)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_pf_START (3)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_pf_END (3)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_ef_START (4)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_ef_END (4)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_tlbmcf_START (5)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_tlbmcf_END (5)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_tlblkf_START (6)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_tlblkf_END (6)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_ss_START (30)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_ss_END (30)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_multi_START (31)
#define SOC_SMMU500_NS_SMMU_CB1_FSR_multi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int smmu_cb1_fsrrestore : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_FSRRESTORE_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_FSRRESTORE_smmu_cb1_fsrrestore_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_FSRRESTORE_smmu_cb1_fsrrestore_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_low : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_FAR_LOW_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_FAR_LOW_faddr_low_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_FAR_LOW_faddr_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_high : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_FAR_HIGH_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_FAR_HIGH_faddr_high_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_FAR_HIGH_faddr_high_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int plvl : 2;
        unsigned int reserved_0: 2;
        unsigned int wnr : 1;
        unsigned int pnu : 1;
        unsigned int ind : 1;
        unsigned int nsstate : 1;
        unsigned int nsattr : 1;
        unsigned int atof : 1;
        unsigned int ptwf : 1;
        unsigned int afr : 1;
        unsigned int reserved_1: 20;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_FSYNR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_plvl_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_plvl_END (1)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_wnr_START (4)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_wnr_END (4)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_pnu_START (5)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_pnu_END (5)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_ind_START (6)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_ind_END (6)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_nsstate_START (7)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_nsstate_END (7)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_nsattr_START (8)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_nsattr_END (8)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_atof_START (9)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_atof_END (9)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_ptwf_START (10)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_ptwf_END (10)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_afr_START (11)
#define SOC_SMMU500_NS_SMMU_CB1_FSYNR0_afr_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr0 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR0_evcntr0_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR0_evcntr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr1 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR1_evcntr1_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR1_evcntr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr2 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR2_evcntr2_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVCNTR2_evcntr2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER0_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER1_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB1_PMXEVTYPER2_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CB1_pmcfgr : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMCFGR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMCFGR_CB1_pmcfgr_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMCFGR_CB1_pmcfgr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int e : 1;
        unsigned int p : 1;
        unsigned int reserved_0: 2;
        unsigned int x : 1;
        unsigned int reserved_1: 3;
        unsigned int reserved_2: 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMCR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMCR_e_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMCR_e_END (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMCR_p_START (1)
#define SOC_SMMU500_NS_SMMU_CB1_PMCR_p_END (1)
#define SOC_SMMU500_NS_SMMU_CB1_PMCR_x_START (4)
#define SOC_SMMU500_NS_SMMU_CB1_PMCR_x_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmceid0 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMCEID0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMCEID0_pmceid0_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMCEID0_pmceid0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMCNTENSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMCNTENSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMCNTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMCNTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMCNTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMCNTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMINTENSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMINTENSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMINTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMINTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMINTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMINTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMOVSRCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMOVSRCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMOVSRCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMOVSRSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMOVSRSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMOVSRSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmauthstatus : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB1_PMAUTHSTATUS_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB1_PMAUTHSTATUS_pmauthstatus_START (0)
#define SOC_SMMU500_NS_SMMU_CB1_PMAUTHSTATUS_pmauthstatus_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m : 1;
        unsigned int tre : 1;
        unsigned int afe : 1;
        unsigned int affd : 1;
        unsigned int e : 1;
        unsigned int cfre : 1;
        unsigned int cfie : 1;
        unsigned int cfcfg : 1;
        unsigned int hupcf : 1;
        unsigned int reserved_0: 4;
        unsigned int reserved_1: 1;
        unsigned int bsu : 2;
        unsigned int memattr : 4;
        unsigned int reserved_2: 1;
        unsigned int fb : 1;
        unsigned int shcfg : 2;
        unsigned int racfg : 2;
        unsigned int wacfg : 2;
        unsigned int reserved_3: 4;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_SCTLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_m_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_m_END (0)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_tre_START (1)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_tre_END (1)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_afe_START (2)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_afe_END (2)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_affd_START (3)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_affd_END (3)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_e_START (4)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_e_END (4)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_cfre_START (5)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_cfre_END (5)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_cfie_START (6)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_cfie_END (6)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_cfcfg_START (7)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_cfcfg_END (7)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_hupcf_START (8)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_hupcf_END (8)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_bsu_START (14)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_bsu_END (15)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_memattr_START (16)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_memattr_END (19)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_fb_START (21)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_fb_END (21)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_shcfg_START (22)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_shcfg_END (23)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_racfg_START (24)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_racfg_END (25)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_wacfg_START (26)
#define SOC_SMMU500_NS_SMMU_CB2_SCTLR_wacfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int translationtablebaseregister_low : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_TTBR0_LOW_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_TTBR0_LOW_translationtablebaseregister_low_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_TTBR0_LOW_translationtablebaseregister_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int translationtablebaseregister_high : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_TTBR0_HIGH_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_TTBR0_HIGH_translationtablebaseregister_high_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_TTBR0_HIGH_translationtablebaseregister_high_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t0sz : 4;
        unsigned int s : 1;
        unsigned int reserved_0: 1;
        unsigned int sl0 : 2;
        unsigned int irgn0 : 2;
        unsigned int orgn0 : 2;
        unsigned int sh0 : 2;
        unsigned int reserved_1: 17;
        unsigned int eae : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_TTBCR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_t0sz_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_t0sz_END (3)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_s_START (4)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_s_END (4)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_sl0_START (6)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_sl0_END (7)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_irgn0_START (8)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_irgn0_END (9)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_orgn0_START (10)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_orgn0_END (11)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_sh0_START (12)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_sh0_END (13)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_eae_START (31)
#define SOC_SMMU500_NS_SMMU_CB2_TTBCR_eae_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int tf : 1;
        unsigned int aff : 1;
        unsigned int pf : 1;
        unsigned int ef : 1;
        unsigned int tlbmcf : 1;
        unsigned int tlblkf : 1;
        unsigned int reserved_1: 23;
        unsigned int ss : 1;
        unsigned int multi : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_FSR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_FSR_tf_START (1)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_tf_END (1)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_aff_START (2)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_aff_END (2)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_pf_START (3)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_pf_END (3)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_ef_START (4)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_ef_END (4)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_tlbmcf_START (5)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_tlbmcf_END (5)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_tlblkf_START (6)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_tlblkf_END (6)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_ss_START (30)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_ss_END (30)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_multi_START (31)
#define SOC_SMMU500_NS_SMMU_CB2_FSR_multi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int smmu_cb2_fsrrestore : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_FSRRESTORE_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_FSRRESTORE_smmu_cb2_fsrrestore_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_FSRRESTORE_smmu_cb2_fsrrestore_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_low : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_FAR_LOW_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_FAR_LOW_faddr_low_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_FAR_LOW_faddr_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_high : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_FAR_HIGH_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_FAR_HIGH_faddr_high_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_FAR_HIGH_faddr_high_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int plvl : 2;
        unsigned int reserved_0: 2;
        unsigned int wnr : 1;
        unsigned int pnu : 1;
        unsigned int ind : 1;
        unsigned int nsstate : 1;
        unsigned int nsattr : 1;
        unsigned int atof : 1;
        unsigned int ptwf : 1;
        unsigned int afr : 1;
        unsigned int reserved_1: 20;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_FSYNR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_plvl_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_plvl_END (1)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_wnr_START (4)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_wnr_END (4)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_pnu_START (5)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_pnu_END (5)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_ind_START (6)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_ind_END (6)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_nsstate_START (7)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_nsstate_END (7)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_nsattr_START (8)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_nsattr_END (8)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_atof_START (9)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_atof_END (9)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_ptwf_START (10)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_ptwf_END (10)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_afr_START (11)
#define SOC_SMMU500_NS_SMMU_CB2_FSYNR0_afr_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr0 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR0_evcntr0_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR0_evcntr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr1 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR1_evcntr1_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR1_evcntr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr2 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR2_evcntr2_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVCNTR2_evcntr2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER0_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER1_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB2_PMXEVTYPER2_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cb0_pmcfgr : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMCFGR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMCFGR_cb0_pmcfgr_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMCFGR_cb0_pmcfgr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int e : 1;
        unsigned int p : 1;
        unsigned int reserved_0: 2;
        unsigned int x : 1;
        unsigned int reserved_1: 3;
        unsigned int reserved_2: 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMCR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMCR_e_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMCR_e_END (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMCR_p_START (1)
#define SOC_SMMU500_NS_SMMU_CB2_PMCR_p_END (1)
#define SOC_SMMU500_NS_SMMU_CB2_PMCR_x_START (4)
#define SOC_SMMU500_NS_SMMU_CB2_PMCR_x_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmceid0 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMCEID0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMCEID0_pmceid0_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMCEID0_pmceid0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMCNTENSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMCNTENSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMCNTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMCNTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMCNTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMCNTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMINTENSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMINTENSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMINTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMINTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMINTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMINTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMOVSRCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMOVSRCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMOVSRCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMOVSRSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMOVSRSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMOVSRSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmauthstatus : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB2_PMAUTHSTATUS_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB2_PMAUTHSTATUS_pmauthstatus_START (0)
#define SOC_SMMU500_NS_SMMU_CB2_PMAUTHSTATUS_pmauthstatus_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int m : 1;
        unsigned int tre : 1;
        unsigned int afe : 1;
        unsigned int affd : 1;
        unsigned int e : 1;
        unsigned int cfre : 1;
        unsigned int cfie : 1;
        unsigned int cfcfg : 1;
        unsigned int hupcf : 1;
        unsigned int reserved_0: 4;
        unsigned int reserved_1: 1;
        unsigned int bsu : 2;
        unsigned int memattr : 4;
        unsigned int reserved_2: 1;
        unsigned int fb : 1;
        unsigned int shcfg : 2;
        unsigned int racfg : 2;
        unsigned int wacfg : 2;
        unsigned int reserved_3: 4;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_SCTLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_m_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_m_END (0)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_tre_START (1)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_tre_END (1)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_afe_START (2)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_afe_END (2)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_affd_START (3)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_affd_END (3)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_e_START (4)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_e_END (4)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_cfre_START (5)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_cfre_END (5)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_cfie_START (6)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_cfie_END (6)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_cfcfg_START (7)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_cfcfg_END (7)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_hupcf_START (8)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_hupcf_END (8)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_bsu_START (14)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_bsu_END (15)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_memattr_START (16)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_memattr_END (19)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_fb_START (21)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_fb_END (21)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_shcfg_START (22)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_shcfg_END (23)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_racfg_START (24)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_racfg_END (25)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_wacfg_START (26)
#define SOC_SMMU500_NS_SMMU_CB3_SCTLR_wacfg_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int translationtablebaseregister_low : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_TTBR0_LOW_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_TTBR0_LOW_translationtablebaseregister_low_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_TTBR0_LOW_translationtablebaseregister_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int translationtablebaseregister_high : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_TTBR0_HIGH_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_TTBR0_HIGH_translationtablebaseregister_high_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_TTBR0_HIGH_translationtablebaseregister_high_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int t0sz : 4;
        unsigned int s : 1;
        unsigned int reserved_0: 1;
        unsigned int sl0 : 2;
        unsigned int irgn0 : 2;
        unsigned int orgn0 : 2;
        unsigned int sh0 : 2;
        unsigned int reserved_1: 17;
        unsigned int eae : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_TTBCR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_t0sz_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_t0sz_END (3)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_s_START (4)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_s_END (4)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_sl0_START (6)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_sl0_END (7)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_irgn0_START (8)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_irgn0_END (9)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_orgn0_START (10)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_orgn0_END (11)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_sh0_START (12)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_sh0_END (13)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_eae_START (31)
#define SOC_SMMU500_NS_SMMU_CB3_TTBCR_eae_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 1;
        unsigned int tf : 1;
        unsigned int aff : 1;
        unsigned int pf : 1;
        unsigned int ef : 1;
        unsigned int tlbmcf : 1;
        unsigned int tlblkf : 1;
        unsigned int reserved_1: 23;
        unsigned int ss : 1;
        unsigned int multi : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_FSR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_FSR_tf_START (1)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_tf_END (1)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_aff_START (2)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_aff_END (2)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_pf_START (3)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_pf_END (3)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_ef_START (4)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_ef_END (4)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_tlbmcf_START (5)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_tlbmcf_END (5)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_tlblkf_START (6)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_tlblkf_END (6)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_ss_START (30)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_ss_END (30)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_multi_START (31)
#define SOC_SMMU500_NS_SMMU_CB3_FSR_multi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int smmu_cb3_fsrrestore : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_FSRRESTORE_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_FSRRESTORE_smmu_cb3_fsrrestore_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_FSRRESTORE_smmu_cb3_fsrrestore_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_low : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_FAR_LOW_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_FAR_LOW_faddr_low_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_FAR_LOW_faddr_low_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int faddr_high : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_FAR_HIGH_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_FAR_HIGH_faddr_high_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_FAR_HIGH_faddr_high_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int plvl : 2;
        unsigned int reserved_0: 2;
        unsigned int wnr : 1;
        unsigned int pnu : 1;
        unsigned int ind : 1;
        unsigned int nsstate : 1;
        unsigned int nsattr : 1;
        unsigned int atof : 1;
        unsigned int ptwf : 1;
        unsigned int afr : 1;
        unsigned int reserved_1: 20;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_FSYNR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_plvl_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_plvl_END (1)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_wnr_START (4)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_wnr_END (4)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_pnu_START (5)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_pnu_END (5)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_ind_START (6)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_ind_END (6)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_nsstate_START (7)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_nsstate_END (7)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_nsattr_START (8)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_nsattr_END (8)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_atof_START (9)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_atof_END (9)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_ptwf_START (10)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_ptwf_END (10)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_afr_START (11)
#define SOC_SMMU500_NS_SMMU_CB3_FSYNR0_afr_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr0 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR0_evcntr0_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR0_evcntr0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr1 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR1_evcntr1_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR1_evcntr1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int evcntr2 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR2_evcntr2_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVCNTR2_evcntr2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER0_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER1_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event : 5;
        unsigned int reserved : 23;
        unsigned int nsu : 1;
        unsigned int nsp : 1;
        unsigned int u : 1;
        unsigned int p : 1;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_event_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_event_END (4)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_nsu_START (28)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_nsu_END (28)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_nsp_START (29)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_nsp_END (29)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_u_START (30)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_u_END (30)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_p_START (31)
#define SOC_SMMU500_NS_SMMU_CB3_PMXEVTYPER2_p_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int cb3_pmcfgr : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMCFGR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMCFGR_cb3_pmcfgr_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMCFGR_cb3_pmcfgr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int e : 1;
        unsigned int p : 1;
        unsigned int reserved_0: 2;
        unsigned int x : 1;
        unsigned int reserved_1: 3;
        unsigned int reserved_2: 24;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMCR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMCR_e_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMCR_e_END (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMCR_p_START (1)
#define SOC_SMMU500_NS_SMMU_CB3_PMCR_p_END (1)
#define SOC_SMMU500_NS_SMMU_CB3_PMCR_x_START (4)
#define SOC_SMMU500_NS_SMMU_CB3_PMCR_x_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmceid0 : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMCEID0_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMCEID0_pmceid0_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMCEID0_pmceid0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMCNTENSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMCNTENSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMCNTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMCNTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMCNTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMCNTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMINTENSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMINTENSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMINTENSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMINTENCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMINTENCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMINTENCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableclr : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMOVSRCLR_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMOVSRCLR_enableclr_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMOVSRCLR_enableclr_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int enableset : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMOVSRSET_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMOVSRSET_enableset_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMOVSRSET_enableset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int pmauthstatus : 32;
    } reg;
} SOC_SMMU500_NS_SMMU_CB3_PMAUTHSTATUS_UNION;
#endif
#define SOC_SMMU500_NS_SMMU_CB3_PMAUTHSTATUS_pmauthstatus_START (0)
#define SOC_SMMU500_NS_SMMU_CB3_PMAUTHSTATUS_pmauthstatus_END (31)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
