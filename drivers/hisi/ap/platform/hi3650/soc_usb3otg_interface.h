#ifndef __SOC_USB3OTG_INTERFACE_H__
#define __SOC_USB3OTG_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_USB3OTG_CAPLENGTH_ADDR(base) ((base) + (0x0000))
#define SOC_USB3OTG_HCSPARAMS1_ADDR(base) ((base) + (0x0004))
#define SOC_USB3OTG_HCSPARAMS2_ADDR(base) ((base) + (0x0008))
#define SOC_USB3OTG_HCSPARAMS3_ADDR(base) ((base) + (0x000C))
#define SOC_USB3OTG_HCCPARAMS_ADDR(base) ((base) + (0x0010))
#define SOC_USB3OTG_DBOFF_ADDR(base) ((base) + (0x0014))
#define SOC_USB3OTG_RTSOFF_ADDR(base) ((base) + (0x0018))
#define SOC_USB3OTG_USBCMD_ADDR(base) ((base) + (0x0020))
#define SOC_USB3OTG_USBSTS_ADDR(base) ((base) + (0x0024))
#define SOC_USB3OTG_PAGESIZE_ADDR(base) ((base) + (0x0028))
#define SOC_USB3OTG_DNCTRL_ADDR(base) ((base) + (0x0034))
#define SOC_USB3OTG_CRCR_L_ADDR(base) ((base) + (0x0038))
#define SOC_USB3OTG_CRCR_H_ADDR(base) ((base) + (0x003C))
#define SOC_USB3OTG_DCBAAP_L_ADDR(base) ((base) + (0x0050))
#define SOC_USB3OTG_DCBAAP_H_ADDR(base) ((base) + (0x0054))
#define SOC_USB3OTG_CONFIG_ADDR(base) ((base) + (0x0058))
#define SOC_USB3OTG_PORTSC_ADDR(base) ((base) + (0x0420))
#define SOC_USB3OTG_PORTPMSC_20_ADDR(base) ((base) + (0x0424))
#define SOC_USB3OTG_PORTLI_ADDR(base) ((base) + (0x0428))
#define SOC_USB3OTG_PORTHLPMC_20_ADDR(base) ((base) + (0x042C))
#define SOC_USB3OTG_MFINDEX_ADDR(base) ((base) + (0x440))
#define SOC_USB3OTG_IMAN_ADDR(base) ((base) + (0x460))
#define SOC_USB3OTG_IMOD_ADDR(base) ((base) + (0x464))
#define SOC_USB3OTG_ERSTSZ_ADDR(base) ((base) + (0x468))
#define SOC_USB3OTG_ERSTBA_L_ADDR(base) ((base) + (0x470))
#define SOC_USB3OTG_ERSTBA_H_ADDR(base) ((base) + (0x474))
#define SOC_USB3OTG_ERDP_L_ADDR(base) ((base) + (0x478))
#define SOC_USB3OTG_ERDP_H_ADDR(base) ((base) + (0x47C))
#define SOC_USB3OTG_DB_ADDR(base) ((base) + (0x480))
#define SOC_USB3OTG_USBLEGSUP_ADDR(base) ((base) + (0x8A0))
#define SOC_USB3OTG_USBLEGCTLSTS_ADDR(base) ((base) + (0x8A4))
#define SOC_USB3OTG_GSBUSCFG0_ADDR(base) ((base) + (0xC100))
#define SOC_USB3OTG_GSBUSCFG1_ADDR(base) ((base) + (0xC104))
#define SOC_USB3OTG_GTXTHRCFG_ADDR(base) ((base) + (0xC108))
#define SOC_USB3OTG_GRXTHRCFG_ADDR(base) ((base) + (0xC10C))
#define SOC_USB3OTG_GCTL_ADDR(base) ((base) + (0xC110))
#define SOC_USB3OTG_GPMSTS_ADDR(base) ((base) + (0xC114))
#define SOC_USB3OTG_GSTS_ADDR(base) ((base) + (0xC118))
#define SOC_USB3OTG_GUCTL1_ADDR(base) ((base) + (0xC11C))
#define SOC_USB3OTG_GSNPSID_ADDR(base) ((base) + (0xC120))
#define SOC_USB3OTG_GUCTL_ADDR(base) ((base) + (0xC12C))
#define SOC_USB3OTG_GBUSERRADDRL_ADDR(base) ((base) + (0xC130))
#define SOC_USB3OTG_GBUSERRADDRH_ADDR(base) ((base) + (0xC134))
#define SOC_USB3OTG_GHWPARAMS0_ADDR(base) ((base) + (0xC140))
#define SOC_USB3OTG_GHWPARAMS1_ADDR(base) ((base) + (0xC144))
#define SOC_USB3OTG_GHWPARAMS2_ADDR(base) ((base) + (0xC148))
#define SOC_USB3OTG_GHWPARAMS3_ADDR(base) ((base) + (0xC14C))
#define SOC_USB3OTG_GHWPARAMS4_ADDR(base) ((base) + (0xC150))
#define SOC_USB3OTG_GHWPARAMS5_ADDR(base) ((base) + (0xC154))
#define SOC_USB3OTG_GHWPARAMS6_ADDR(base) ((base) + (0xC158))
#define SOC_USB3OTG_GHWPARAMS7_ADDR(base) ((base) + (0xC15C))
#define SOC_USB3OTG_GHWPARAMS8_ADDR(base) ((base) + (0xC600))
#define SOC_USB3OTG_GDBGFIFOSPACE_ADDR(base) ((base) + (0xC160))
#define SOC_USB3OTG_GDBGLTSSM_ADDR(base) ((base) + (0xC164))
#define SOC_USB3OTG_GDBGLNMCC_ADDR(base) ((base) + (0xC168))
#define SOC_USB3OTG_GCBGBMU_ADDR(base) ((base) + (0xC16C))
#define SOC_USB3OTG_GDBGLSPMUX_ADDR(base) ((base) + (0xC170))
#define SOC_USB3OTG_GDBGLSP_ADDR(base) ((base) + (0xC174))
#define SOC_USB3OTG_GDBGEPINFO0_ADDR(base) ((base) + (0xC178))
#define SOC_USB3OTG_GDBGEPINFO1_ADDR(base) ((base) + (0xC17C))
#define SOC_USB3OTG_GUSB2PHYCFG_ADDR(base) ((base) + (0xC200))
#define SOC_USB3OTG_GUSB3PIPECTL_ADDR(base) ((base) + (0xC2C0))
#define SOC_USB3OTG_GTXFIFOSIZm_ADDR(base) ((base) + (0xC300+m*0x4))
#define SOC_USB3OTG_GRXFIFOSIZn_ADDR(base,n) ((base) + (0xC380+(n)*0x4))
#define SOC_USB3OTG_GEVNTADRLo_ADDR(base) ((base) + (0xC400))
#define SOC_USB3OTG_GEVNTADRHi_ADDR(base) ((base) + (0xC404))
#define SOC_USB3OTG_GEVNTSIZ_ADDR(base) ((base) + (0xC408))
#define SOC_USB3OTG_GEVNTCOUNT_ADDR(base) ((base) + (0xC40C))
#define SOC_USB3OTG_GTXFIFOPRIDEV_ADDR(base) ((base) + (0xC610))
#define SOC_USB3OTG_GTXFIFOPRIHST_ADDR(base) ((base) + (0xC618))
#define SOC_USB3OTG_GRXFIFOPRIHST_ADDR(base) ((base) + (0xC61C))
#define SOC_USB3OTG_GDMAHLRATIO_ADDR(base) ((base) + (0xC624))
#define SOC_USB3OTG_GFLADJ_ADDR(base) ((base) + (0xC630))
#define SOC_USB3OTG_DCFG_ADDR(base) ((base) + (0xC700))
#define SOC_USB3OTG_DCTL_ADDR(base) ((base) + (0xC704))
#define SOC_USB3OTG_DEVNTEN_ADDR(base) ((base) + (0xC708))
#define SOC_USB3OTG_DSTS_ADDR(base) ((base) + (0xC70C))
#define SOC_USB3OTG_DGCMDPAR_ADDR(base) ((base) + (0xC710))
#define SOC_USB3OTG_DGCMD_ADDR(base) ((base) + (0xC714))
#define SOC_USB3OTG_DALEPENA_ADDR(base) ((base) + (0xC720))
#define SOC_USB3OTG_DEPCMDPAR2m_ADDR(base) ((base) + (0xC800+m*0x10))
#define SOC_USB3OTG_DEPCMDPAR1m_ADDR(base) ((base) + (0xC804+m*0x10))
#define SOC_USB3OTG_DEPCMDPAR0m_ADDR(base) ((base) + (0xC808+m*0x10))
#define SOC_USB3OTG_DEPCMDm_ADDR(base) ((base) + (0xC80C+m*0x10))
#define SOC_USB3OTG_OCFG_ADDR(base) ((base) + (0xCC00))
#define SOC_USB3OTG_OCTL_ADDR(base) ((base) + (0xCC04))
#define SOC_USB3OTG_OEVNT_ADDR(base) ((base) + (0xCC08))
#define SOC_USB3OTG_OEVNTEN_ADDR(base) ((base) + (0xCC0C))
#define SOC_USB3OTG_OSTS_ADDR(base) ((base) + (0xCC10))
#define SOC_USB3OTG_ADPCFG_ADDR(base) ((base) + (0xCC20))
#define SOC_USB3OTG_ADPCTL_ADDR(base) ((base) + (0xCC24))
#define SOC_USB3OTG_ADPEVNT_ADDR(base) ((base) + (0xCC28))
#define SOC_USB3OTG_ADPEVNTEN_ADDR(base) ((base) + (0xCC28))
#define SOC_USB3OTG_BCFG_ADDR(base) ((base) + (0xCC30))
#define SOC_USB3OTG_BCEVT_ADDR(base) ((base) + (0xCC38))
#define SOC_USB3OTG_BCEVTEN_ADDR(base) ((base) + (0xCC3C))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CAPLENGTH : 8;
        unsigned int reserved : 8;
        unsigned int HCIVERSION : 16;
    } reg;
} SOC_USB3OTG_CAPLENGTH_UNION;
#endif
#define SOC_USB3OTG_CAPLENGTH_CAPLENGTH_START (0)
#define SOC_USB3OTG_CAPLENGTH_CAPLENGTH_END (7)
#define SOC_USB3OTG_CAPLENGTH_HCIVERSION_START (16)
#define SOC_USB3OTG_CAPLENGTH_HCIVERSION_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int MaxSlots : 8;
        unsigned int MaxIntrs : 11;
        unsigned int reserved : 5;
        unsigned int MaxPorts : 8;
    } reg;
} SOC_USB3OTG_HCSPARAMS1_UNION;
#endif
#define SOC_USB3OTG_HCSPARAMS1_MaxSlots_START (0)
#define SOC_USB3OTG_HCSPARAMS1_MaxSlots_END (7)
#define SOC_USB3OTG_HCSPARAMS1_MaxIntrs_START (8)
#define SOC_USB3OTG_HCSPARAMS1_MaxIntrs_END (18)
#define SOC_USB3OTG_HCSPARAMS1_MaxPorts_START (24)
#define SOC_USB3OTG_HCSPARAMS1_MaxPorts_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IST : 4;
        unsigned int ERST_Max : 4;
        unsigned int reserved : 13;
        unsigned int Max_Scratchpad_Bufs_H : 5;
        unsigned int SPR : 1;
        unsigned int Max_Scratchpad_Bufs_L : 5;
    } reg;
} SOC_USB3OTG_HCSPARAMS2_UNION;
#endif
#define SOC_USB3OTG_HCSPARAMS2_IST_START (0)
#define SOC_USB3OTG_HCSPARAMS2_IST_END (3)
#define SOC_USB3OTG_HCSPARAMS2_ERST_Max_START (4)
#define SOC_USB3OTG_HCSPARAMS2_ERST_Max_END (7)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_H_START (21)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_H_END (25)
#define SOC_USB3OTG_HCSPARAMS2_SPR_START (26)
#define SOC_USB3OTG_HCSPARAMS2_SPR_END (26)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_L_START (27)
#define SOC_USB3OTG_HCSPARAMS2_Max_Scratchpad_Bufs_L_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int U1_Exit_Latency : 8;
        unsigned int reserved : 8;
        unsigned int U2_Exit_Latency : 16;
    } reg;
} SOC_USB3OTG_HCSPARAMS3_UNION;
#endif
#define SOC_USB3OTG_HCSPARAMS3_U1_Exit_Latency_START (0)
#define SOC_USB3OTG_HCSPARAMS3_U1_Exit_Latency_END (7)
#define SOC_USB3OTG_HCSPARAMS3_U2_Exit_Latency_START (16)
#define SOC_USB3OTG_HCSPARAMS3_U2_Exit_Latency_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int AC64 : 1;
        unsigned int BNC : 1;
        unsigned int CSZ : 1;
        unsigned int PPC : 1;
        unsigned int PIND : 1;
        unsigned int LHRC : 1;
        unsigned int LTC : 1;
        unsigned int NSS : 1;
        unsigned int PAE : 1;
        unsigned int reserved : 3;
        unsigned int MaxPSASize : 4;
        unsigned int xECP : 16;
    } reg;
} SOC_USB3OTG_HCCPARAMS_UNION;
#endif
#define SOC_USB3OTG_HCCPARAMS_AC64_START (0)
#define SOC_USB3OTG_HCCPARAMS_AC64_END (0)
#define SOC_USB3OTG_HCCPARAMS_BNC_START (1)
#define SOC_USB3OTG_HCCPARAMS_BNC_END (1)
#define SOC_USB3OTG_HCCPARAMS_CSZ_START (2)
#define SOC_USB3OTG_HCCPARAMS_CSZ_END (2)
#define SOC_USB3OTG_HCCPARAMS_PPC_START (3)
#define SOC_USB3OTG_HCCPARAMS_PPC_END (3)
#define SOC_USB3OTG_HCCPARAMS_PIND_START (4)
#define SOC_USB3OTG_HCCPARAMS_PIND_END (4)
#define SOC_USB3OTG_HCCPARAMS_LHRC_START (5)
#define SOC_USB3OTG_HCCPARAMS_LHRC_END (5)
#define SOC_USB3OTG_HCCPARAMS_LTC_START (6)
#define SOC_USB3OTG_HCCPARAMS_LTC_END (6)
#define SOC_USB3OTG_HCCPARAMS_NSS_START (7)
#define SOC_USB3OTG_HCCPARAMS_NSS_END (7)
#define SOC_USB3OTG_HCCPARAMS_PAE_START (8)
#define SOC_USB3OTG_HCCPARAMS_PAE_END (8)
#define SOC_USB3OTG_HCCPARAMS_MaxPSASize_START (12)
#define SOC_USB3OTG_HCCPARAMS_MaxPSASize_END (15)
#define SOC_USB3OTG_HCCPARAMS_xECP_START (16)
#define SOC_USB3OTG_HCCPARAMS_xECP_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 2;
        unsigned int Doorbell_Array_Offset : 30;
    } reg;
} SOC_USB3OTG_DBOFF_UNION;
#endif
#define SOC_USB3OTG_DBOFF_Doorbell_Array_Offset_START (2)
#define SOC_USB3OTG_DBOFF_Doorbell_Array_Offset_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 5;
        unsigned int Runtime_Register_Space_Offset : 27;
    } reg;
} SOC_USB3OTG_RTSOFF_UNION;
#endif
#define SOC_USB3OTG_RTSOFF_Runtime_Register_Space_Offset_START (5)
#define SOC_USB3OTG_RTSOFF_Runtime_Register_Space_Offset_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int Run_Stop : 1;
        unsigned int HCRST : 1;
        unsigned int INTE : 1;
        unsigned int HSEE : 1;
        unsigned int reserved_0: 3;
        unsigned int LHCRST : 1;
        unsigned int CSS : 1;
        unsigned int CRS : 1;
        unsigned int EWE : 1;
        unsigned int EU3S : 1;
        unsigned int reserved_1: 20;
    } reg;
} SOC_USB3OTG_USBCMD_UNION;
#endif
#define SOC_USB3OTG_USBCMD_Run_Stop_START (0)
#define SOC_USB3OTG_USBCMD_Run_Stop_END (0)
#define SOC_USB3OTG_USBCMD_HCRST_START (1)
#define SOC_USB3OTG_USBCMD_HCRST_END (1)
#define SOC_USB3OTG_USBCMD_INTE_START (2)
#define SOC_USB3OTG_USBCMD_INTE_END (2)
#define SOC_USB3OTG_USBCMD_HSEE_START (3)
#define SOC_USB3OTG_USBCMD_HSEE_END (3)
#define SOC_USB3OTG_USBCMD_LHCRST_START (7)
#define SOC_USB3OTG_USBCMD_LHCRST_END (7)
#define SOC_USB3OTG_USBCMD_CSS_START (8)
#define SOC_USB3OTG_USBCMD_CSS_END (8)
#define SOC_USB3OTG_USBCMD_CRS_START (9)
#define SOC_USB3OTG_USBCMD_CRS_END (9)
#define SOC_USB3OTG_USBCMD_EWE_START (10)
#define SOC_USB3OTG_USBCMD_EWE_END (10)
#define SOC_USB3OTG_USBCMD_EU3S_START (11)
#define SOC_USB3OTG_USBCMD_EU3S_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int HCH : 1;
        unsigned int reserved_0: 1;
        unsigned int HSE : 1;
        unsigned int EINT : 1;
        unsigned int PCD : 1;
        unsigned int reserved_1: 3;
        unsigned int SSS : 1;
        unsigned int RSS : 1;
        unsigned int SRE : 1;
        unsigned int CNR : 1;
        unsigned int HCE : 1;
        unsigned int reserved_2: 19;
    } reg;
} SOC_USB3OTG_USBSTS_UNION;
#endif
#define SOC_USB3OTG_USBSTS_HCH_START (0)
#define SOC_USB3OTG_USBSTS_HCH_END (0)
#define SOC_USB3OTG_USBSTS_HSE_START (2)
#define SOC_USB3OTG_USBSTS_HSE_END (2)
#define SOC_USB3OTG_USBSTS_EINT_START (3)
#define SOC_USB3OTG_USBSTS_EINT_END (3)
#define SOC_USB3OTG_USBSTS_PCD_START (4)
#define SOC_USB3OTG_USBSTS_PCD_END (4)
#define SOC_USB3OTG_USBSTS_SSS_START (8)
#define SOC_USB3OTG_USBSTS_SSS_END (8)
#define SOC_USB3OTG_USBSTS_RSS_START (9)
#define SOC_USB3OTG_USBSTS_RSS_END (9)
#define SOC_USB3OTG_USBSTS_SRE_START (10)
#define SOC_USB3OTG_USBSTS_SRE_END (10)
#define SOC_USB3OTG_USBSTS_CNR_START (11)
#define SOC_USB3OTG_USBSTS_CNR_END (11)
#define SOC_USB3OTG_USBSTS_HCE_START (12)
#define SOC_USB3OTG_USBSTS_HCE_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int page_size : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_USB3OTG_PAGESIZE_UNION;
#endif
#define SOC_USB3OTG_PAGESIZE_page_size_START (0)
#define SOC_USB3OTG_PAGESIZE_page_size_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int notification_enable : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_USB3OTG_DNCTRL_UNION;
#endif
#define SOC_USB3OTG_DNCTRL_notification_enable_START (0)
#define SOC_USB3OTG_DNCTRL_notification_enable_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int RCS : 1;
        unsigned int CS : 1;
        unsigned int CA : 1;
        unsigned int CRR : 1;
        unsigned int reserved : 2;
        unsigned int command_ring_pointor : 26;
    } reg;
} SOC_USB3OTG_CRCR_L_UNION;
#endif
#define SOC_USB3OTG_CRCR_L_RCS_START (0)
#define SOC_USB3OTG_CRCR_L_RCS_END (0)
#define SOC_USB3OTG_CRCR_L_CS_START (1)
#define SOC_USB3OTG_CRCR_L_CS_END (1)
#define SOC_USB3OTG_CRCR_L_CA_START (2)
#define SOC_USB3OTG_CRCR_L_CA_END (2)
#define SOC_USB3OTG_CRCR_L_CRR_START (3)
#define SOC_USB3OTG_CRCR_L_CRR_END (3)
#define SOC_USB3OTG_CRCR_L_command_ring_pointor_START (6)
#define SOC_USB3OTG_CRCR_L_command_ring_pointor_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int command_ring_pointor : 32;
    } reg;
} SOC_USB3OTG_CRCR_H_UNION;
#endif
#define SOC_USB3OTG_CRCR_H_command_ring_pointor_START (0)
#define SOC_USB3OTG_CRCR_H_command_ring_pointor_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 6;
        unsigned int DCBAAR_point : 26;
    } reg;
} SOC_USB3OTG_DCBAAP_L_UNION;
#endif
#define SOC_USB3OTG_DCBAAP_L_DCBAAR_point_START (6)
#define SOC_USB3OTG_DCBAAP_L_DCBAAR_point_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DCBAAR_point : 32;
    } reg;
} SOC_USB3OTG_DCBAAP_H_UNION;
#endif
#define SOC_USB3OTG_DCBAAP_H_DCBAAR_point_START (0)
#define SOC_USB3OTG_DCBAAP_H_DCBAAR_point_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int MaxSlotsEn : 8;
        unsigned int reserved : 24;
    } reg;
} SOC_USB3OTG_CONFIG_UNION;
#endif
#define SOC_USB3OTG_CONFIG_MaxSlotsEn_START (0)
#define SOC_USB3OTG_CONFIG_MaxSlotsEn_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CCS : 1;
        unsigned int PED : 1;
        unsigned int reserved_0: 1;
        unsigned int OCA : 1;
        unsigned int PR : 1;
        unsigned int PLS : 4;
        unsigned int PP : 1;
        unsigned int PortSpeed : 4;
        unsigned int PIC : 2;
        unsigned int LWS : 1;
        unsigned int CSC : 1;
        unsigned int PEC : 1;
        unsigned int WRC : 1;
        unsigned int OCC : 1;
        unsigned int PRC : 1;
        unsigned int PLC : 1;
        unsigned int CEC : 1;
        unsigned int CAS : 1;
        unsigned int WCE : 1;
        unsigned int WDE : 1;
        unsigned int WOE : 1;
        unsigned int reserved_1: 2;
        unsigned int DR : 1;
        unsigned int WPR : 1;
    } reg;
} SOC_USB3OTG_PORTSC_UNION;
#endif
#define SOC_USB3OTG_PORTSC_CCS_START (0)
#define SOC_USB3OTG_PORTSC_CCS_END (0)
#define SOC_USB3OTG_PORTSC_PED_START (1)
#define SOC_USB3OTG_PORTSC_PED_END (1)
#define SOC_USB3OTG_PORTSC_OCA_START (3)
#define SOC_USB3OTG_PORTSC_OCA_END (3)
#define SOC_USB3OTG_PORTSC_PR_START (4)
#define SOC_USB3OTG_PORTSC_PR_END (4)
#define SOC_USB3OTG_PORTSC_PLS_START (5)
#define SOC_USB3OTG_PORTSC_PLS_END (8)
#define SOC_USB3OTG_PORTSC_PP_START (9)
#define SOC_USB3OTG_PORTSC_PP_END (9)
#define SOC_USB3OTG_PORTSC_PortSpeed_START (10)
#define SOC_USB3OTG_PORTSC_PortSpeed_END (13)
#define SOC_USB3OTG_PORTSC_PIC_START (14)
#define SOC_USB3OTG_PORTSC_PIC_END (15)
#define SOC_USB3OTG_PORTSC_LWS_START (16)
#define SOC_USB3OTG_PORTSC_LWS_END (16)
#define SOC_USB3OTG_PORTSC_CSC_START (17)
#define SOC_USB3OTG_PORTSC_CSC_END (17)
#define SOC_USB3OTG_PORTSC_PEC_START (18)
#define SOC_USB3OTG_PORTSC_PEC_END (18)
#define SOC_USB3OTG_PORTSC_WRC_START (19)
#define SOC_USB3OTG_PORTSC_WRC_END (19)
#define SOC_USB3OTG_PORTSC_OCC_START (20)
#define SOC_USB3OTG_PORTSC_OCC_END (20)
#define SOC_USB3OTG_PORTSC_PRC_START (21)
#define SOC_USB3OTG_PORTSC_PRC_END (21)
#define SOC_USB3OTG_PORTSC_PLC_START (22)
#define SOC_USB3OTG_PORTSC_PLC_END (22)
#define SOC_USB3OTG_PORTSC_CEC_START (23)
#define SOC_USB3OTG_PORTSC_CEC_END (23)
#define SOC_USB3OTG_PORTSC_CAS_START (24)
#define SOC_USB3OTG_PORTSC_CAS_END (24)
#define SOC_USB3OTG_PORTSC_WCE_START (25)
#define SOC_USB3OTG_PORTSC_WCE_END (25)
#define SOC_USB3OTG_PORTSC_WDE_START (26)
#define SOC_USB3OTG_PORTSC_WDE_END (26)
#define SOC_USB3OTG_PORTSC_WOE_START (27)
#define SOC_USB3OTG_PORTSC_WOE_END (27)
#define SOC_USB3OTG_PORTSC_DR_START (30)
#define SOC_USB3OTG_PORTSC_DR_END (30)
#define SOC_USB3OTG_PORTSC_WPR_START (31)
#define SOC_USB3OTG_PORTSC_WPR_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int L1S : 3;
        unsigned int RWE : 1;
        unsigned int HIRD : 4;
        unsigned int L1_Device_Slot : 8;
        unsigned int HLE : 1;
        unsigned int reserved : 11;
        unsigned int Port_Test_Control : 4;
    } reg;
} SOC_USB3OTG_PORTPMSC_20_UNION;
#endif
#define SOC_USB3OTG_PORTPMSC_20_L1S_START (0)
#define SOC_USB3OTG_PORTPMSC_20_L1S_END (2)
#define SOC_USB3OTG_PORTPMSC_20_RWE_START (3)
#define SOC_USB3OTG_PORTPMSC_20_RWE_END (3)
#define SOC_USB3OTG_PORTPMSC_20_HIRD_START (4)
#define SOC_USB3OTG_PORTPMSC_20_HIRD_END (7)
#define SOC_USB3OTG_PORTPMSC_20_L1_Device_Slot_START (8)
#define SOC_USB3OTG_PORTPMSC_20_L1_Device_Slot_END (15)
#define SOC_USB3OTG_PORTPMSC_20_HLE_START (16)
#define SOC_USB3OTG_PORTPMSC_20_HLE_END (16)
#define SOC_USB3OTG_PORTPMSC_20_Port_Test_Control_START (28)
#define SOC_USB3OTG_PORTPMSC_20_Port_Test_Control_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int link_error_count : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_USB3OTG_PORTLI_UNION;
#endif
#define SOC_USB3OTG_PORTLI_link_error_count_START (0)
#define SOC_USB3OTG_PORTLI_link_error_count_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int HIRDM : 2;
        unsigned int L1_timeout : 8;
        unsigned int HIRDD : 4;
        unsigned int reserved : 18;
    } reg;
} SOC_USB3OTG_PORTHLPMC_20_UNION;
#endif
#define SOC_USB3OTG_PORTHLPMC_20_HIRDM_START (0)
#define SOC_USB3OTG_PORTHLPMC_20_HIRDM_END (1)
#define SOC_USB3OTG_PORTHLPMC_20_L1_timeout_START (2)
#define SOC_USB3OTG_PORTHLPMC_20_L1_timeout_END (9)
#define SOC_USB3OTG_PORTHLPMC_20_HIRDD_START (10)
#define SOC_USB3OTG_PORTHLPMC_20_HIRDD_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int microframe_index : 14;
        unsigned int reserved : 18;
    } reg;
} SOC_USB3OTG_MFINDEX_UNION;
#endif
#define SOC_USB3OTG_MFINDEX_microframe_index_START (0)
#define SOC_USB3OTG_MFINDEX_microframe_index_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IP : 1;
        unsigned int IE : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_USB3OTG_IMAN_UNION;
#endif
#define SOC_USB3OTG_IMAN_IP_START (0)
#define SOC_USB3OTG_IMAN_IP_END (0)
#define SOC_USB3OTG_IMAN_IE_START (1)
#define SOC_USB3OTG_IMAN_IE_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int IMODI : 16;
        unsigned int IMODC : 16;
    } reg;
} SOC_USB3OTG_IMOD_UNION;
#endif
#define SOC_USB3OTG_IMOD_IMODI_START (0)
#define SOC_USB3OTG_IMOD_IMODI_END (15)
#define SOC_USB3OTG_IMOD_IMODC_START (16)
#define SOC_USB3OTG_IMOD_IMODC_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_ring_segment_table_size : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_USB3OTG_ERSTSZ_UNION;
#endif
#define SOC_USB3OTG_ERSTSZ_event_ring_segment_table_size_START (0)
#define SOC_USB3OTG_ERSTSZ_event_ring_segment_table_size_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 6;
        unsigned int event_ring_segment_table_base_address : 26;
    } reg;
} SOC_USB3OTG_ERSTBA_L_UNION;
#endif
#define SOC_USB3OTG_ERSTBA_L_event_ring_segment_table_base_address_START (6)
#define SOC_USB3OTG_ERSTBA_L_event_ring_segment_table_base_address_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_ring_segment_table_base_address : 32;
    } reg;
} SOC_USB3OTG_ERSTBA_H_UNION;
#endif
#define SOC_USB3OTG_ERSTBA_H_event_ring_segment_table_base_address_START (0)
#define SOC_USB3OTG_ERSTBA_H_event_ring_segment_table_base_address_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DESI : 3;
        unsigned int EHB : 1;
        unsigned int event_ring_dequeue_pointer : 28;
    } reg;
} SOC_USB3OTG_ERDP_L_UNION;
#endif
#define SOC_USB3OTG_ERDP_L_DESI_START (0)
#define SOC_USB3OTG_ERDP_L_DESI_END (2)
#define SOC_USB3OTG_ERDP_L_EHB_START (3)
#define SOC_USB3OTG_ERDP_L_EHB_END (3)
#define SOC_USB3OTG_ERDP_L_event_ring_dequeue_pointer_START (4)
#define SOC_USB3OTG_ERDP_L_event_ring_dequeue_pointer_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int event_ring_dequeue_pointer : 32;
    } reg;
} SOC_USB3OTG_ERDP_H_UNION;
#endif
#define SOC_USB3OTG_ERDP_H_event_ring_dequeue_pointer_START (0)
#define SOC_USB3OTG_ERDP_H_event_ring_dequeue_pointer_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DB_tagger : 8;
        unsigned int reserved : 8;
        unsigned int DB_Stream_ID : 16;
    } reg;
} SOC_USB3OTG_DB_UNION;
#endif
#define SOC_USB3OTG_DB_DB_tagger_START (0)
#define SOC_USB3OTG_DB_DB_tagger_END (7)
#define SOC_USB3OTG_DB_DB_Stream_ID_START (16)
#define SOC_USB3OTG_DB_DB_Stream_ID_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int capability_ID : 8;
        unsigned int next_capability_pointer : 8;
        unsigned int HC_BIOS_owned_semaphore : 1;
        unsigned int reserved_0 : 7;
        unsigned int HC_OS_owned_semaphore : 1;
        unsigned int reserved_1 : 7;
    } reg;
} SOC_USB3OTG_USBLEGSUP_UNION;
#endif
#define SOC_USB3OTG_USBLEGSUP_capability_ID_START (0)
#define SOC_USB3OTG_USBLEGSUP_capability_ID_END (7)
#define SOC_USB3OTG_USBLEGSUP_next_capability_pointer_START (8)
#define SOC_USB3OTG_USBLEGSUP_next_capability_pointer_END (15)
#define SOC_USB3OTG_USBLEGSUP_HC_BIOS_owned_semaphore_START (16)
#define SOC_USB3OTG_USBLEGSUP_HC_BIOS_owned_semaphore_END (16)
#define SOC_USB3OTG_USBLEGSUP_HC_OS_owned_semaphore_START (24)
#define SOC_USB3OTG_USBLEGSUP_HC_OS_owned_semaphore_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int USB_SMI_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int SMI_on_host_system_error_enable : 1;
        unsigned int reserved_1 : 8;
        unsigned int SMI_on_OS_ownership_enable : 1;
        unsigned int SMI_on_PCI_command_enable : 1;
        unsigned int SMI_on_BAR_enable : 1;
        unsigned int SMI_on_event_interrupt : 1;
        unsigned int reserved_2 : 3;
        unsigned int SMI_on_host_system_error : 1;
        unsigned int reserved_3 : 8;
        unsigned int SMI_on_OS_ownership_change : 1;
        unsigned int SMI_on_PCI_command : 1;
        unsigned int SMI_on_BAR : 1;
    } reg;
} SOC_USB3OTG_USBLEGCTLSTS_UNION;
#endif
#define SOC_USB3OTG_USBLEGCTLSTS_USB_SMI_enable_START (0)
#define SOC_USB3OTG_USBLEGCTLSTS_USB_SMI_enable_END (0)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_enable_START (4)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_enable_END (4)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_enable_START (13)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_enable_END (13)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_enable_START (14)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_enable_END (14)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_enable_START (15)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_enable_END (15)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_event_interrupt_START (16)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_event_interrupt_END (16)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_START (20)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_host_system_error_END (20)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_change_START (29)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_OS_ownership_change_END (29)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_START (30)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_PCI_command_END (30)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_START (31)
#define SOC_USB3OTG_USBLEGCTLSTS_SMI_on_BAR_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int INCRBrstEna : 1;
        unsigned int INCR4BrstEna : 1;
        unsigned int INCR8BrstEna : 1;
        unsigned int INCR16BrstEna : 1;
        unsigned int INCR32BrstEna : 1;
        unsigned int INCR64BrstEna : 1;
        unsigned int INCR128BrstEna : 1;
        unsigned int INCR256BrstEna : 1;
        unsigned int reserved_0 : 2;
        unsigned int DescBigEnd : 1;
        unsigned int DatBigEnd : 1;
        unsigned int reserved_1 : 4;
        unsigned int DesWrReqInfo : 4;
        unsigned int DatWrReqInfo : 4;
        unsigned int DesRdReqInfo : 4;
        unsigned int DatRdReqInfo : 4;
    } reg;
} SOC_USB3OTG_GSBUSCFG0_UNION;
#endif
#define SOC_USB3OTG_GSBUSCFG0_INCRBrstEna_START (0)
#define SOC_USB3OTG_GSBUSCFG0_INCRBrstEna_END (0)
#define SOC_USB3OTG_GSBUSCFG0_INCR4BrstEna_START (1)
#define SOC_USB3OTG_GSBUSCFG0_INCR4BrstEna_END (1)
#define SOC_USB3OTG_GSBUSCFG0_INCR8BrstEna_START (2)
#define SOC_USB3OTG_GSBUSCFG0_INCR8BrstEna_END (2)
#define SOC_USB3OTG_GSBUSCFG0_INCR16BrstEna_START (3)
#define SOC_USB3OTG_GSBUSCFG0_INCR16BrstEna_END (3)
#define SOC_USB3OTG_GSBUSCFG0_INCR32BrstEna_START (4)
#define SOC_USB3OTG_GSBUSCFG0_INCR32BrstEna_END (4)
#define SOC_USB3OTG_GSBUSCFG0_INCR64BrstEna_START (5)
#define SOC_USB3OTG_GSBUSCFG0_INCR64BrstEna_END (5)
#define SOC_USB3OTG_GSBUSCFG0_INCR128BrstEna_START (6)
#define SOC_USB3OTG_GSBUSCFG0_INCR128BrstEna_END (6)
#define SOC_USB3OTG_GSBUSCFG0_INCR256BrstEna_START (7)
#define SOC_USB3OTG_GSBUSCFG0_INCR256BrstEna_END (7)
#define SOC_USB3OTG_GSBUSCFG0_DescBigEnd_START (10)
#define SOC_USB3OTG_GSBUSCFG0_DescBigEnd_END (10)
#define SOC_USB3OTG_GSBUSCFG0_DatBigEnd_START (11)
#define SOC_USB3OTG_GSBUSCFG0_DatBigEnd_END (11)
#define SOC_USB3OTG_GSBUSCFG0_DesWrReqInfo_START (16)
#define SOC_USB3OTG_GSBUSCFG0_DesWrReqInfo_END (19)
#define SOC_USB3OTG_GSBUSCFG0_DatWrReqInfo_START (20)
#define SOC_USB3OTG_GSBUSCFG0_DatWrReqInfo_END (23)
#define SOC_USB3OTG_GSBUSCFG0_DesRdReqInfo_START (24)
#define SOC_USB3OTG_GSBUSCFG0_DesRdReqInfo_END (27)
#define SOC_USB3OTG_GSBUSCFG0_DatRdReqInfo_START (28)
#define SOC_USB3OTG_GSBUSCFG0_DatRdReqInfo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int PipeTransLimit : 4;
        unsigned int EN1KPAGE : 1;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_USB3OTG_GSBUSCFG1_UNION;
#endif
#define SOC_USB3OTG_GSBUSCFG1_PipeTransLimit_START (8)
#define SOC_USB3OTG_GSBUSCFG1_PipeTransLimit_END (11)
#define SOC_USB3OTG_GSBUSCFG1_EN1KPAGE_START (12)
#define SOC_USB3OTG_GSBUSCFG1_EN1KPAGE_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 16;
        unsigned int USBMaxTxBurstSize : 8;
        unsigned int USBTxPktCnt : 4;
        unsigned int reserved_1 : 1;
        unsigned int USBTxPktCntSel : 1;
        unsigned int reserved_2 : 2;
    } reg;
} SOC_USB3OTG_GTXTHRCFG_UNION;
#endif
#define SOC_USB3OTG_GTXTHRCFG_USBMaxTxBurstSize_START (16)
#define SOC_USB3OTG_GTXTHRCFG_USBMaxTxBurstSize_END (23)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCnt_START (24)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCnt_END (27)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCntSel_START (29)
#define SOC_USB3OTG_GTXTHRCFG_USBTxPktCntSel_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 19;
        unsigned int USBMaxRxBurstSize : 5;
        unsigned int USBRxPktCnt : 4;
        unsigned int reserved_1 : 1;
        unsigned int USBRxPktCntSel : 1;
        unsigned int reserved_2 : 2;
    } reg;
} SOC_USB3OTG_GRXTHRCFG_UNION;
#endif
#define SOC_USB3OTG_GRXTHRCFG_USBMaxRxBurstSize_START (19)
#define SOC_USB3OTG_GRXTHRCFG_USBMaxRxBurstSize_END (23)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCnt_START (24)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCnt_END (27)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCntSel_START (29)
#define SOC_USB3OTG_GRXTHRCFG_USBRxPktCntSel_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DsblClkGtng : 1;
        unsigned int GblHibernationEn : 1;
        unsigned int U2EXIT_LFPS : 1;
        unsigned int DisScramble : 1;
        unsigned int ScaleDown : 2;
        unsigned int RAMClkSel : 2;
        unsigned int DebugAttach : 1;
        unsigned int DisU1U2TimerScale : 1;
        unsigned int SOFTITPSYNC : 1;
        unsigned int CoreSoftReset : 1;
        unsigned int PrtCapDir : 2;
        unsigned int FrmSclDwn : 2;
        unsigned int U2RSTECN : 1;
        unsigned int BypassSetAddr : 1;
        unsigned int MasterFiltBypass : 1;
        unsigned int GPwrDnScale : 13;
    } reg;
} SOC_USB3OTG_GCTL_UNION;
#endif
#define SOC_USB3OTG_GCTL_DsblClkGtng_START (0)
#define SOC_USB3OTG_GCTL_DsblClkGtng_END (0)
#define SOC_USB3OTG_GCTL_GblHibernationEn_START (1)
#define SOC_USB3OTG_GCTL_GblHibernationEn_END (1)
#define SOC_USB3OTG_GCTL_U2EXIT_LFPS_START (2)
#define SOC_USB3OTG_GCTL_U2EXIT_LFPS_END (2)
#define SOC_USB3OTG_GCTL_DisScramble_START (3)
#define SOC_USB3OTG_GCTL_DisScramble_END (3)
#define SOC_USB3OTG_GCTL_ScaleDown_START (4)
#define SOC_USB3OTG_GCTL_ScaleDown_END (5)
#define SOC_USB3OTG_GCTL_RAMClkSel_START (6)
#define SOC_USB3OTG_GCTL_RAMClkSel_END (7)
#define SOC_USB3OTG_GCTL_DebugAttach_START (8)
#define SOC_USB3OTG_GCTL_DebugAttach_END (8)
#define SOC_USB3OTG_GCTL_DisU1U2TimerScale_START (9)
#define SOC_USB3OTG_GCTL_DisU1U2TimerScale_END (9)
#define SOC_USB3OTG_GCTL_SOFTITPSYNC_START (10)
#define SOC_USB3OTG_GCTL_SOFTITPSYNC_END (10)
#define SOC_USB3OTG_GCTL_CoreSoftReset_START (11)
#define SOC_USB3OTG_GCTL_CoreSoftReset_END (11)
#define SOC_USB3OTG_GCTL_PrtCapDir_START (12)
#define SOC_USB3OTG_GCTL_PrtCapDir_END (13)
#define SOC_USB3OTG_GCTL_FrmSclDwn_START (14)
#define SOC_USB3OTG_GCTL_FrmSclDwn_END (15)
#define SOC_USB3OTG_GCTL_U2RSTECN_START (16)
#define SOC_USB3OTG_GCTL_U2RSTECN_END (16)
#define SOC_USB3OTG_GCTL_BypassSetAddr_START (17)
#define SOC_USB3OTG_GCTL_BypassSetAddr_END (17)
#define SOC_USB3OTG_GCTL_MasterFiltBypass_START (18)
#define SOC_USB3OTG_GCTL_MasterFiltBypass_END (18)
#define SOC_USB3OTG_GCTL_GPwrDnScale_START (19)
#define SOC_USB3OTG_GCTL_GPwrDnScale_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int U2Wakeup : 10;
        unsigned int reserved_0: 2;
        unsigned int U3Wakeup : 5;
        unsigned int reserved_1: 11;
        unsigned int PortSel : 4;
    } reg;
} SOC_USB3OTG_GPMSTS_UNION;
#endif
#define SOC_USB3OTG_GPMSTS_U2Wakeup_START (0)
#define SOC_USB3OTG_GPMSTS_U2Wakeup_END (9)
#define SOC_USB3OTG_GPMSTS_U3Wakeup_START (12)
#define SOC_USB3OTG_GPMSTS_U3Wakeup_END (16)
#define SOC_USB3OTG_GPMSTS_PortSel_START (28)
#define SOC_USB3OTG_GPMSTS_PortSel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 4;
        unsigned int BusErrAddrVld : 1;
        unsigned int CSRTimeout : 1;
        unsigned int Device_IP : 1;
        unsigned int Host_IP : 1;
        unsigned int ADP_IP : 1;
        unsigned int BC_IP : 1;
        unsigned int OTG_IP : 1;
        unsigned int reserved_1 : 9;
        unsigned int CBELT : 12;
    } reg;
} SOC_USB3OTG_GSTS_UNION;
#endif
#define SOC_USB3OTG_GSTS_BusErrAddrVld_START (4)
#define SOC_USB3OTG_GSTS_BusErrAddrVld_END (4)
#define SOC_USB3OTG_GSTS_CSRTimeout_START (5)
#define SOC_USB3OTG_GSTS_CSRTimeout_END (5)
#define SOC_USB3OTG_GSTS_Device_IP_START (6)
#define SOC_USB3OTG_GSTS_Device_IP_END (6)
#define SOC_USB3OTG_GSTS_Host_IP_START (7)
#define SOC_USB3OTG_GSTS_Host_IP_END (7)
#define SOC_USB3OTG_GSTS_ADP_IP_START (8)
#define SOC_USB3OTG_GSTS_ADP_IP_END (8)
#define SOC_USB3OTG_GSTS_BC_IP_START (9)
#define SOC_USB3OTG_GSTS_BC_IP_END (9)
#define SOC_USB3OTG_GSTS_OTG_IP_START (10)
#define SOC_USB3OTG_GSTS_OTG_IP_END (10)
#define SOC_USB3OTG_GSTS_CBELT_START (20)
#define SOC_USB3OTG_GSTS_CBELT_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int LOA_FILTER_EN : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_USB3OTG_GUCTL1_UNION;
#endif
#define SOC_USB3OTG_GUCTL1_LOA_FILTER_EN_START (0)
#define SOC_USB3OTG_GUCTL1_LOA_FILTER_EN_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int SynopsysID : 32;
    } reg;
} SOC_USB3OTG_GSNPSID_UNION;
#endif
#define SOC_USB3OTG_GSNPSID_SynopsysID_START (0)
#define SOC_USB3OTG_GSNPSID_SynopsysID_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DTFT : 9;
        unsigned int DTCT : 2;
        unsigned int CSR : 1;
        unsigned int ExtCapSuptEN : 1;
        unsigned int EnOverlapChk : 1;
        unsigned int USBHstInAutoRetryEn : 1;
        unsigned int CMDevAddr : 1;
        unsigned int ResBwHSEPS : 1;
        unsigned int SprsCtrlTransEn : 1;
        unsigned int PSQExtrResSp : 3;
        unsigned int NoExtrDl : 1;
        unsigned int REFCLKPER : 10;
    } reg;
} SOC_USB3OTG_GUCTL_UNION;
#endif
#define SOC_USB3OTG_GUCTL_DTFT_START (0)
#define SOC_USB3OTG_GUCTL_DTFT_END (8)
#define SOC_USB3OTG_GUCTL_DTCT_START (9)
#define SOC_USB3OTG_GUCTL_DTCT_END (10)
#define SOC_USB3OTG_GUCTL_CSR_START (11)
#define SOC_USB3OTG_GUCTL_CSR_END (11)
#define SOC_USB3OTG_GUCTL_ExtCapSuptEN_START (12)
#define SOC_USB3OTG_GUCTL_ExtCapSuptEN_END (12)
#define SOC_USB3OTG_GUCTL_EnOverlapChk_START (13)
#define SOC_USB3OTG_GUCTL_EnOverlapChk_END (13)
#define SOC_USB3OTG_GUCTL_USBHstInAutoRetryEn_START (14)
#define SOC_USB3OTG_GUCTL_USBHstInAutoRetryEn_END (14)
#define SOC_USB3OTG_GUCTL_CMDevAddr_START (15)
#define SOC_USB3OTG_GUCTL_CMDevAddr_END (15)
#define SOC_USB3OTG_GUCTL_ResBwHSEPS_START (16)
#define SOC_USB3OTG_GUCTL_ResBwHSEPS_END (16)
#define SOC_USB3OTG_GUCTL_SprsCtrlTransEn_START (17)
#define SOC_USB3OTG_GUCTL_SprsCtrlTransEn_END (17)
#define SOC_USB3OTG_GUCTL_PSQExtrResSp_START (18)
#define SOC_USB3OTG_GUCTL_PSQExtrResSp_END (20)
#define SOC_USB3OTG_GUCTL_NoExtrDl_START (21)
#define SOC_USB3OTG_GUCTL_NoExtrDl_END (21)
#define SOC_USB3OTG_GUCTL_REFCLKPER_START (22)
#define SOC_USB3OTG_GUCTL_REFCLKPER_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int BusAddrl : 32;
    } reg;
} SOC_USB3OTG_GBUSERRADDRL_UNION;
#endif
#define SOC_USB3OTG_GBUSERRADDRL_BusAddrl_START (0)
#define SOC_USB3OTG_GBUSERRADDRL_BusAddrl_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int BusAddrh : 32;
    } reg;
} SOC_USB3OTG_GBUSERRADDRH_UNION;
#endif
#define SOC_USB3OTG_GBUSERRADDRH_BusAddrh_START (0)
#define SOC_USB3OTG_GBUSERRADDRH_BusAddrh_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DWC_USB3_MODE : 3;
        unsigned int DWC_USB3_MBUS_TYPE : 3;
        unsigned int DWC_USB3_SBUS_TYPE : 2;
        unsigned int DWC_USB3_MDWIDTH : 8;
        unsigned int DWC_USB3_SDWIDTH : 8;
        unsigned int DWC_USB3_AWIDTH : 8;
    } reg;
} SOC_USB3OTG_GHWPARAMS0_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MODE_START (0)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MODE_END (2)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MBUS_TYPE_START (3)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MBUS_TYPE_END (5)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SBUS_TYPE_START (6)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SBUS_TYPE_END (7)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MDWIDTH_START (8)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_MDWIDTH_END (15)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SDWIDTH_START (16)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_SDWIDTH_END (23)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_AWIDTH_START (24)
#define SOC_USB3OTG_GHWPARAMS0_DWC_USB3_AWIDTH_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DWC_USB3_IDWIDTH : 3;
        unsigned int DWC_USB3_BURSTWIDTH : 3;
        unsigned int DWC_USB3_DATAINFOWIDTH : 3;
        unsigned int DWC_USB3_REQINFOWIDTH : 3;
        unsigned int DWC_USB3_ASPACEWIDTH : 3;
        unsigned int DWC_USB3_DEVICE_NUM_INT : 6;
        unsigned int DWC_USB3_NUM_RAMS : 2;
        unsigned int DWC_USB3_SRAM_TYP : 1;
        unsigned int DWC_USB3_EN_PWROPT : 2;
        unsigned int reserved : 6;
    } reg;
} SOC_USB3OTG_GHWPARAMS1_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_IDWIDTH_START (0)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_IDWIDTH_END (2)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_BURSTWIDTH_START (3)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_BURSTWIDTH_END (5)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DATAINFOWIDTH_START (6)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DATAINFOWIDTH_END (8)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_REQINFOWIDTH_START (9)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_REQINFOWIDTH_END (11)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_ASPACEWIDTH_START (12)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_ASPACEWIDTH_END (14)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DEVICE_NUM_INT_START (15)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_DEVICE_NUM_INT_END (20)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_NUM_RAMS_START (21)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_NUM_RAMS_END (22)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_SRAM_TYP_START (23)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_SRAM_TYP_END (23)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_EN_PWROPT_START (24)
#define SOC_USB3OTG_GHWPARAMS1_DWC_USB3_EN_PWROPT_END (25)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DWC_USB3_USERID : 32;
    } reg;
} SOC_USB3OTG_GHWPARAMS2_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS2_DWC_USB3_USERID_START (0)
#define SOC_USB3OTG_GHWPARAMS2_DWC_USB3_USERID_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DWC_USB3_SSPHY_INTERFACE : 2;
        unsigned int DWC_USB3_HSPHY_INTERFACE : 2;
        unsigned int DWC_USB3_FSPHY_INTERFACE : 2;
        unsigned int DWC_USB3_HSPHY_DWIDTH : 2;
        unsigned int reserved_0 : 2;
        unsigned int DWC_USB3_VENDOR_CTL_INTERFACE : 1;
        unsigned int reserved_1 : 1;
        unsigned int DWC_USB3_NUM_EPS : 6;
        unsigned int DWC_USB3_NUM_IN_EPS : 5;
        unsigned int DWC_USB3_CACHE_TOTAL_XFER_RESOURCE : 8;
        unsigned int reserved_2 : 1;
    } reg;
} SOC_USB3OTG_GHWPARAMS3_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_SSPHY_INTERFACE_START (0)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_SSPHY_INTERFACE_END (1)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_INTERFACE_START (2)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_INTERFACE_END (3)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_FSPHY_INTERFACE_START (4)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_FSPHY_INTERFACE_END (5)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_DWIDTH_START (6)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_HSPHY_DWIDTH_END (7)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_VENDOR_CTL_INTERFACE_START (10)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_VENDOR_CTL_INTERFACE_END (10)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_EPS_START (12)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_EPS_END (17)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_IN_EPS_START (18)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_NUM_IN_EPS_END (22)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_CACHE_TOTAL_XFER_RESOURCE_START (23)
#define SOC_USB3OTG_GHWPARAMS3_DWC_USB3_CACHE_TOTAL_XFER_RESOURCE_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DWC_USB3_CACHE_TRBS_PER_TRANSFER : 6;
        unsigned int reserved_0 : 7;
        unsigned int DWC_USB3_HIBER_SCRATCHBUFS : 4;
        unsigned int DWC_USB3_NUM_SS_USB_INSTANCE : 4;
        unsigned int reserved_1 : 2;
        unsigned int DWC_USB3_EN_ISOC_SUPT : 1;
        unsigned int DWC_USB3_BMU_PTL_DEPTH : 4;
        unsigned int DWC_USB3_BMU_LSP_DEPTH : 4;
    } reg;
} SOC_USB3OTG_GHWPARAMS4_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_CACHE_TRBS_PER_TRANSFER_START (0)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_CACHE_TRBS_PER_TRANSFER_END (5)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_HIBER_SCRATCHBUFS_START (13)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_HIBER_SCRATCHBUFS_END (16)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_NUM_SS_USB_INSTANCE_START (17)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_NUM_SS_USB_INSTANCE_END (20)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_EN_ISOC_SUPT_START (23)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_EN_ISOC_SUPT_END (23)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_PTL_DEPTH_START (24)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_PTL_DEPTH_END (27)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_LSP_DEPTH_START (28)
#define SOC_USB3OTG_GHWPARAMS4_DWC_USB3_BMU_LSP_DEPTH_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DWC_USB3_BMU_BUSGM_DEPTH : 4;
        unsigned int DWC_USB3_RXQ_FIFO_DEPTH : 6;
        unsigned int DWC_USB3_TXQ_FIFO_DEPTH : 6;
        unsigned int DWC_USB3_DWQ_FIFO_DEPTH : 6;
        unsigned int DWC_USB3_DFQ_FIFO_DEPTH : 6;
        unsigned int reserved : 4;
    } reg;
} SOC_USB3OTG_GHWPARAMS5_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_BMU_BUSGM_DEPTH_START (0)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_BMU_BUSGM_DEPTH_END (3)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_RXQ_FIFO_DEPTH_START (4)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_RXQ_FIFO_DEPTH_END (9)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_TXQ_FIFO_DEPTH_START (10)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_TXQ_FIFO_DEPTH_END (15)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DWQ_FIFO_DEPTH_START (16)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DWQ_FIFO_DEPTH_END (21)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DFQ_FIFO_DEPTH_START (22)
#define SOC_USB3OTG_GHWPARAMS5_DWC_USB3_DFQ_FIFO_DEPTH_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DWC_USB3_PSQ_FIFO_DEPTH : 6;
        unsigned int reserved_0 : 1;
        unsigned int DWC_USB3_EN_FPGA : 1;
        unsigned int reserved_1 : 2;
        unsigned int DWC_USB3_EN_SRP : 1;
        unsigned int DWC_USB3_EN_HNP : 1;
        unsigned int DWC_USB3_EN_ADP : 1;
        unsigned int DWC_USB3_OTG3_SUPT : 1;
        unsigned int DWC_USB3_EN_BC : 1;
        unsigned int DWC_USB3_EN_BUS_FILTER : 1;
        unsigned int DWC_USB3_RAM0_DEPTH : 16;
    } reg;
} SOC_USB3OTG_GHWPARAMS6_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_PSQ_FIFO_DEPTH_START (0)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_PSQ_FIFO_DEPTH_END (5)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_FPGA_START (7)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_FPGA_END (7)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_SRP_START (10)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_SRP_END (10)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_HNP_START (11)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_HNP_END (11)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_ADP_START (12)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_ADP_END (12)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_OTG3_SUPT_START (13)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_OTG3_SUPT_END (13)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BC_START (14)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BC_END (14)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BUS_FILTER_START (15)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_EN_BUS_FILTER_END (15)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_RAM0_DEPTH_START (16)
#define SOC_USB3OTG_GHWPARAMS6_DWC_USB3_RAM0_DEPTH_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DWC_USB3_RAM1_DEPTH : 16;
        unsigned int DWC_USB3_RAM2_DEPTH : 16;
    } reg;
} SOC_USB3OTG_GHWPARAMS7_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM1_DEPTH_START (0)
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM1_DEPTH_END (15)
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM2_DEPTH_START (16)
#define SOC_USB3OTG_GHWPARAMS7_DWC_USB3_RAM2_DEPTH_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DWC_USB3_DCACHE_DEPTH_INFO : 32;
    } reg;
} SOC_USB3OTG_GHWPARAMS8_UNION;
#endif
#define SOC_USB3OTG_GHWPARAMS8_DWC_USB3_DCACHE_DEPTH_INFO_START (0)
#define SOC_USB3OTG_GHWPARAMS8_DWC_USB3_DCACHE_DEPTH_INFO_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int FIFOSek : 8;
        unsigned int reserved : 8;
        unsigned int SpaceAvailable : 16;
    } reg;
} SOC_USB3OTG_GDBGFIFOSPACE_UNION;
#endif
#define SOC_USB3OTG_GDBGFIFOSPACE_FIFOSek_START (0)
#define SOC_USB3OTG_GDBGFIFOSPACE_FIFOSek_END (7)
#define SOC_USB3OTG_GDBGFIFOSPACE_SpaceAvailable_START (16)
#define SOC_USB3OTG_GDBGFIFOSPACE_SpaceAvailable_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ltssm : 32;
    } reg;
} SOC_USB3OTG_GDBGLTSSM_UNION;
#endif
#define SOC_USB3OTG_GDBGLTSSM_ltssm_START (0)
#define SOC_USB3OTG_GDBGLTSSM_ltssm_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int LNMCC_BERC : 9;
        unsigned int reserved : 23;
    } reg;
} SOC_USB3OTG_GDBGLNMCC_UNION;
#endif
#define SOC_USB3OTG_GDBGLNMCC_LNMCC_BERC_START (0)
#define SOC_USB3OTG_GDBGLNMCC_LNMCC_BERC_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CCU : 4;
        unsigned int DCU : 4;
        unsigned int BCU : 24;
    } reg;
} SOC_USB3OTG_GCBGBMU_UNION;
#endif
#define SOC_USB3OTG_GCBGBMU_CCU_START (0)
#define SOC_USB3OTG_GCBGBMU_CCU_END (3)
#define SOC_USB3OTG_GCBGBMU_DCU_START (4)
#define SOC_USB3OTG_GCBGBMU_DCU_END (7)
#define SOC_USB3OTG_GCBGBMU_BCU_START (8)
#define SOC_USB3OTG_GCBGBMU_BCU_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int LSPMUX : 32;
    } reg;
} SOC_USB3OTG_GDBGLSPMUX_UNION;
#endif
#define SOC_USB3OTG_GDBGLSPMUX_LSPMUX_START (0)
#define SOC_USB3OTG_GDBGLSPMUX_LSPMUX_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int LSP : 32;
    } reg;
} SOC_USB3OTG_GDBGLSP_UNION;
#endif
#define SOC_USB3OTG_GDBGLSP_LSP_START (0)
#define SOC_USB3OTG_GDBGLSP_LSP_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int EpDbg : 32;
    } reg;
} SOC_USB3OTG_GDBGEPINFO0_UNION;
#endif
#define SOC_USB3OTG_GDBGEPINFO0_EpDbg_START (0)
#define SOC_USB3OTG_GDBGEPINFO0_EpDbg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int EpDbg : 32;
    } reg;
} SOC_USB3OTG_GDBGEPINFO1_UNION;
#endif
#define SOC_USB3OTG_GDBGEPINFO1_EpDbg_START (0)
#define SOC_USB3OTG_GDBGEPINFO1_EpDbg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TOutCal : 3;
        unsigned int PHYIf : 1;
        unsigned int reserved_0 : 2;
        unsigned int SusPHY : 1;
        unsigned int reserved_1 : 1;
        unsigned int EnblSlpM : 1;
        unsigned int reserved_2 : 1;
        unsigned int USBTrdTim : 4;
        unsigned int reserved_3 : 16;
        unsigned int U2_FREECLK_EXISTS : 1;
        unsigned int PHYSoftRst : 1;
    } reg;
} SOC_USB3OTG_GUSB2PHYCFG_UNION;
#endif
#define SOC_USB3OTG_GUSB2PHYCFG_TOutCal_START (0)
#define SOC_USB3OTG_GUSB2PHYCFG_TOutCal_END (2)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYIf_START (3)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYIf_END (3)
#define SOC_USB3OTG_GUSB2PHYCFG_SusPHY_START (6)
#define SOC_USB3OTG_GUSB2PHYCFG_SusPHY_END (6)
#define SOC_USB3OTG_GUSB2PHYCFG_EnblSlpM_START (8)
#define SOC_USB3OTG_GUSB2PHYCFG_EnblSlpM_END (8)
#define SOC_USB3OTG_GUSB2PHYCFG_USBTrdTim_START (10)
#define SOC_USB3OTG_GUSB2PHYCFG_USBTrdTim_END (13)
#define SOC_USB3OTG_GUSB2PHYCFG_U2_FREECLK_EXISTS_START (30)
#define SOC_USB3OTG_GUSB2PHYCFG_U2_FREECLK_EXISTS_END (30)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYSoftRst_START (31)
#define SOC_USB3OTG_GUSB2PHYCFG_PHYSoftRst_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ElesticBufferMode : 1;
        unsigned int TxDeemphasis : 2;
        unsigned int TxMargin : 3;
        unsigned int TxSwing : 1;
        unsigned int reserved : 1;
        unsigned int RxDetToPolling : 1;
        unsigned int LFPSFilt : 1;
        unsigned int P3ExSigP2 : 1;
        unsigned int P3P2TranOK : 1;
        unsigned int LFPSP0Algn : 1;
        unsigned int SkipRxDet : 1;
        unsigned int AbortRxDetInU2 : 1;
        unsigned int DatWidth : 2;
        unsigned int Suspend_en : 1;
        unsigned int DelayP1P2P3En : 1;
        unsigned int DelayP1P2P3 : 3;
        unsigned int DisRxDetU3RxDet : 1;
        unsigned int StartRxdetU3ExDet : 1;
        unsigned int RequestP1P2P3 : 1;
        unsigned int U1U2ExitFailToRecov : 1;
        unsigned int PingEnhancementEn : 1;
        unsigned int UxExitInPx : 1;
        unsigned int DisRxDetP3 : 1;
        unsigned int u2SSInactP3ok : 1;
        unsigned int HstPrtCmpl : 1;
        unsigned int PHYSoftRst : 1;
    } reg;
} SOC_USB3OTG_GUSB3PIPECTL_UNION;
#endif
#define SOC_USB3OTG_GUSB3PIPECTL_ElesticBufferMode_START (0)
#define SOC_USB3OTG_GUSB3PIPECTL_ElesticBufferMode_END (0)
#define SOC_USB3OTG_GUSB3PIPECTL_TxDeemphasis_START (1)
#define SOC_USB3OTG_GUSB3PIPECTL_TxDeemphasis_END (2)
#define SOC_USB3OTG_GUSB3PIPECTL_TxMargin_START (3)
#define SOC_USB3OTG_GUSB3PIPECTL_TxMargin_END (5)
#define SOC_USB3OTG_GUSB3PIPECTL_TxSwing_START (6)
#define SOC_USB3OTG_GUSB3PIPECTL_TxSwing_END (6)
#define SOC_USB3OTG_GUSB3PIPECTL_RxDetToPolling_START (8)
#define SOC_USB3OTG_GUSB3PIPECTL_RxDetToPolling_END (8)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSFilt_START (9)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSFilt_END (9)
#define SOC_USB3OTG_GUSB3PIPECTL_P3ExSigP2_START (10)
#define SOC_USB3OTG_GUSB3PIPECTL_P3ExSigP2_END (10)
#define SOC_USB3OTG_GUSB3PIPECTL_P3P2TranOK_START (11)
#define SOC_USB3OTG_GUSB3PIPECTL_P3P2TranOK_END (11)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSP0Algn_START (12)
#define SOC_USB3OTG_GUSB3PIPECTL_LFPSP0Algn_END (12)
#define SOC_USB3OTG_GUSB3PIPECTL_SkipRxDet_START (13)
#define SOC_USB3OTG_GUSB3PIPECTL_SkipRxDet_END (13)
#define SOC_USB3OTG_GUSB3PIPECTL_AbortRxDetInU2_START (14)
#define SOC_USB3OTG_GUSB3PIPECTL_AbortRxDetInU2_END (14)
#define SOC_USB3OTG_GUSB3PIPECTL_DatWidth_START (15)
#define SOC_USB3OTG_GUSB3PIPECTL_DatWidth_END (16)
#define SOC_USB3OTG_GUSB3PIPECTL_Suspend_en_START (17)
#define SOC_USB3OTG_GUSB3PIPECTL_Suspend_en_END (17)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3En_START (18)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3En_END (18)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3_START (19)
#define SOC_USB3OTG_GUSB3PIPECTL_DelayP1P2P3_END (21)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetU3RxDet_START (22)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetU3RxDet_END (22)
#define SOC_USB3OTG_GUSB3PIPECTL_StartRxdetU3ExDet_START (23)
#define SOC_USB3OTG_GUSB3PIPECTL_StartRxdetU3ExDet_END (23)
#define SOC_USB3OTG_GUSB3PIPECTL_RequestP1P2P3_START (24)
#define SOC_USB3OTG_GUSB3PIPECTL_RequestP1P2P3_END (24)
#define SOC_USB3OTG_GUSB3PIPECTL_U1U2ExitFailToRecov_START (25)
#define SOC_USB3OTG_GUSB3PIPECTL_U1U2ExitFailToRecov_END (25)
#define SOC_USB3OTG_GUSB3PIPECTL_PingEnhancementEn_START (26)
#define SOC_USB3OTG_GUSB3PIPECTL_PingEnhancementEn_END (26)
#define SOC_USB3OTG_GUSB3PIPECTL_UxExitInPx_START (27)
#define SOC_USB3OTG_GUSB3PIPECTL_UxExitInPx_END (27)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetP3_START (28)
#define SOC_USB3OTG_GUSB3PIPECTL_DisRxDetP3_END (28)
#define SOC_USB3OTG_GUSB3PIPECTL_u2SSInactP3ok_START (29)
#define SOC_USB3OTG_GUSB3PIPECTL_u2SSInactP3ok_END (29)
#define SOC_USB3OTG_GUSB3PIPECTL_HstPrtCmpl_START (30)
#define SOC_USB3OTG_GUSB3PIPECTL_HstPrtCmpl_END (30)
#define SOC_USB3OTG_GUSB3PIPECTL_PHYSoftRst_START (31)
#define SOC_USB3OTG_GUSB3PIPECTL_PHYSoftRst_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TxFDep : 16;
        unsigned int TxFStAddr : 16;
    } reg;
} SOC_USB3OTG_GTXFIFOSIZm_UNION;
#endif
#define SOC_USB3OTG_GTXFIFOSIZm_TxFDep_START (0)
#define SOC_USB3OTG_GTXFIFOSIZm_TxFDep_END (15)
#define SOC_USB3OTG_GTXFIFOSIZm_TxFStAddr_START (16)
#define SOC_USB3OTG_GTXFIFOSIZm_TxFStAddr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int RxFDep : 16;
        unsigned int RxFStAddr : 16;
    } reg;
} SOC_USB3OTG_GRXFIFOSIZn_UNION;
#endif
#define SOC_USB3OTG_GRXFIFOSIZn_RxFDep_START (0)
#define SOC_USB3OTG_GRXFIFOSIZn_RxFDep_END (15)
#define SOC_USB3OTG_GRXFIFOSIZn_RxFStAddr_START (16)
#define SOC_USB3OTG_GRXFIFOSIZn_RxFStAddr_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int EvntAdrLo : 32;
    } reg;
} SOC_USB3OTG_GEVNTADRLo_UNION;
#endif
#define SOC_USB3OTG_GEVNTADRLo_EvntAdrLo_START (0)
#define SOC_USB3OTG_GEVNTADRLo_EvntAdrLo_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int EvntAdrHi : 32;
    } reg;
} SOC_USB3OTG_GEVNTADRHi_UNION;
#endif
#define SOC_USB3OTG_GEVNTADRHi_EvntAdrHi_START (0)
#define SOC_USB3OTG_GEVNTADRHi_EvntAdrHi_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int EVNTSiz : 16;
        unsigned int reserved : 15;
        unsigned int EvntIntMask : 1;
    } reg;
} SOC_USB3OTG_GEVNTSIZ_UNION;
#endif
#define SOC_USB3OTG_GEVNTSIZ_EVNTSiz_START (0)
#define SOC_USB3OTG_GEVNTSIZ_EVNTSiz_END (15)
#define SOC_USB3OTG_GEVNTSIZ_EvntIntMask_START (31)
#define SOC_USB3OTG_GEVNTSIZ_EvntIntMask_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int EVNTCount : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_USB3OTG_GEVNTCOUNT_UNION;
#endif
#define SOC_USB3OTG_GEVNTCOUNT_EVNTCount_START (0)
#define SOC_USB3OTG_GEVNTCOUNT_EVNTCount_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TxFifoPri : 16;
        unsigned int reserved : 16;
    } reg;
} SOC_USB3OTG_GTXFIFOPRIDEV_UNION;
#endif
#define SOC_USB3OTG_GTXFIFOPRIDEV_TxFifoPri_START (0)
#define SOC_USB3OTG_GTXFIFOPRIDEV_TxFifoPri_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TxFifoPri : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_USB3OTG_GTXFIFOPRIHST_UNION;
#endif
#define SOC_USB3OTG_GTXFIFOPRIHST_TxFifoPri_START (0)
#define SOC_USB3OTG_GTXFIFOPRIHST_TxFifoPri_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int RxFifoPri : 3;
        unsigned int reserved : 29;
    } reg;
} SOC_USB3OTG_GRXFIFOPRIHST_UNION;
#endif
#define SOC_USB3OTG_GRXFIFOPRIHST_RxFifoPri_START (0)
#define SOC_USB3OTG_GRXFIFOPRIHST_RxFifoPri_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int TxFifoRatio : 5;
        unsigned int reserved_0 : 3;
        unsigned int RxFifoRatio : 5;
        unsigned int reserved_1 : 19;
    } reg;
} SOC_USB3OTG_GDMAHLRATIO_UNION;
#endif
#define SOC_USB3OTG_GDMAHLRATIO_TxFifoRatio_START (0)
#define SOC_USB3OTG_GDMAHLRATIO_TxFifoRatio_END (4)
#define SOC_USB3OTG_GDMAHLRATIO_RxFifoRatio_START (8)
#define SOC_USB3OTG_GDMAHLRATIO_RxFifoRatio_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int fladj : 32;
    } reg;
} SOC_USB3OTG_GFLADJ_UNION;
#endif
#define SOC_USB3OTG_GFLADJ_fladj_START (0)
#define SOC_USB3OTG_GFLADJ_fladj_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DevSpd : 3;
        unsigned int DevAddr : 7;
        unsigned int reserved_0 : 2;
        unsigned int IntrNum : 5;
        unsigned int NumP : 5;
        unsigned int LPMCap : 1;
        unsigned int IgnoreStreamPP : 1;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_USB3OTG_DCFG_UNION;
#endif
#define SOC_USB3OTG_DCFG_DevSpd_START (0)
#define SOC_USB3OTG_DCFG_DevSpd_END (2)
#define SOC_USB3OTG_DCFG_DevAddr_START (3)
#define SOC_USB3OTG_DCFG_DevAddr_END (9)
#define SOC_USB3OTG_DCFG_IntrNum_START (12)
#define SOC_USB3OTG_DCFG_IntrNum_END (16)
#define SOC_USB3OTG_DCFG_NumP_START (17)
#define SOC_USB3OTG_DCFG_NumP_END (21)
#define SOC_USB3OTG_DCFG_LPMCap_START (22)
#define SOC_USB3OTG_DCFG_LPMCap_END (22)
#define SOC_USB3OTG_DCFG_IgnoreStreamPP_START (23)
#define SOC_USB3OTG_DCFG_IgnoreStreamPP_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int TstCtl : 4;
        unsigned int ULstChngReq : 4;
        unsigned int AcceptU1Ena : 1;
        unsigned int InitU1Ena : 1;
        unsigned int AcceptU2Ena : 1;
        unsigned int InitU2Ena : 1;
        unsigned int reserved_1 : 3;
        unsigned int CSS : 1;
        unsigned int CRS : 1;
        unsigned int L1HibernationEn : 1;
        unsigned int KeepConnect : 1;
        unsigned int AppL1Res : 4;
        unsigned int HIRD_Thres : 5;
        unsigned int reserved_2 : 1;
        unsigned int CSftRst : 1;
        unsigned int RunStop : 1;
    } reg;
} SOC_USB3OTG_DCTL_UNION;
#endif
#define SOC_USB3OTG_DCTL_TstCtl_START (1)
#define SOC_USB3OTG_DCTL_TstCtl_END (4)
#define SOC_USB3OTG_DCTL_ULstChngReq_START (5)
#define SOC_USB3OTG_DCTL_ULstChngReq_END (8)
#define SOC_USB3OTG_DCTL_AcceptU1Ena_START (9)
#define SOC_USB3OTG_DCTL_AcceptU1Ena_END (9)
#define SOC_USB3OTG_DCTL_InitU1Ena_START (10)
#define SOC_USB3OTG_DCTL_InitU1Ena_END (10)
#define SOC_USB3OTG_DCTL_AcceptU2Ena_START (11)
#define SOC_USB3OTG_DCTL_AcceptU2Ena_END (11)
#define SOC_USB3OTG_DCTL_InitU2Ena_START (12)
#define SOC_USB3OTG_DCTL_InitU2Ena_END (12)
#define SOC_USB3OTG_DCTL_CSS_START (16)
#define SOC_USB3OTG_DCTL_CSS_END (16)
#define SOC_USB3OTG_DCTL_CRS_START (17)
#define SOC_USB3OTG_DCTL_CRS_END (17)
#define SOC_USB3OTG_DCTL_L1HibernationEn_START (18)
#define SOC_USB3OTG_DCTL_L1HibernationEn_END (18)
#define SOC_USB3OTG_DCTL_KeepConnect_START (19)
#define SOC_USB3OTG_DCTL_KeepConnect_END (19)
#define SOC_USB3OTG_DCTL_AppL1Res_START (20)
#define SOC_USB3OTG_DCTL_AppL1Res_END (23)
#define SOC_USB3OTG_DCTL_HIRD_Thres_START (24)
#define SOC_USB3OTG_DCTL_HIRD_Thres_END (28)
#define SOC_USB3OTG_DCTL_CSftRst_START (30)
#define SOC_USB3OTG_DCTL_CSftRst_END (30)
#define SOC_USB3OTG_DCTL_RunStop_START (31)
#define SOC_USB3OTG_DCTL_RunStop_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int DisconnEvtEn : 1;
        unsigned int USBRstEn : 1;
        unsigned int ConnectDoneEn : 1;
        unsigned int ULStsChngEn : 1;
        unsigned int WkUpEvntEn : 1;
        unsigned int HibernationReqEvtEn : 1;
        unsigned int U3L2L1SuspEn : 1;
        unsigned int SofEn : 1;
        unsigned int reserved_0 : 1;
        unsigned int ErrticErrEn : 1;
        unsigned int reserved_1 : 2;
        unsigned int VndrDevTstRcvedEn : 1;
        unsigned int reserved_2 : 19;
    } reg;
} SOC_USB3OTG_DEVNTEN_UNION;
#endif
#define SOC_USB3OTG_DEVNTEN_DisconnEvtEn_START (0)
#define SOC_USB3OTG_DEVNTEN_DisconnEvtEn_END (0)
#define SOC_USB3OTG_DEVNTEN_USBRstEn_START (1)
#define SOC_USB3OTG_DEVNTEN_USBRstEn_END (1)
#define SOC_USB3OTG_DEVNTEN_ConnectDoneEn_START (2)
#define SOC_USB3OTG_DEVNTEN_ConnectDoneEn_END (2)
#define SOC_USB3OTG_DEVNTEN_ULStsChngEn_START (3)
#define SOC_USB3OTG_DEVNTEN_ULStsChngEn_END (3)
#define SOC_USB3OTG_DEVNTEN_WkUpEvntEn_START (4)
#define SOC_USB3OTG_DEVNTEN_WkUpEvntEn_END (4)
#define SOC_USB3OTG_DEVNTEN_HibernationReqEvtEn_START (5)
#define SOC_USB3OTG_DEVNTEN_HibernationReqEvtEn_END (5)
#define SOC_USB3OTG_DEVNTEN_U3L2L1SuspEn_START (6)
#define SOC_USB3OTG_DEVNTEN_U3L2L1SuspEn_END (6)
#define SOC_USB3OTG_DEVNTEN_SofEn_START (7)
#define SOC_USB3OTG_DEVNTEN_SofEn_END (7)
#define SOC_USB3OTG_DEVNTEN_ErrticErrEn_START (9)
#define SOC_USB3OTG_DEVNTEN_ErrticErrEn_END (9)
#define SOC_USB3OTG_DEVNTEN_VndrDevTstRcvedEn_START (12)
#define SOC_USB3OTG_DEVNTEN_VndrDevTstRcvedEn_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ConnectSpd : 3;
        unsigned int SOFFN : 14;
        unsigned int RxFIFOEmpty : 1;
        unsigned int USBLnkSts : 4;
        unsigned int DevCtrlHlt : 1;
        unsigned int CoreIdle : 1;
        unsigned int SSS : 1;
        unsigned int RSS : 1;
        unsigned int reserved_0 : 2;
        unsigned int SRE : 1;
        unsigned int DCNRD : 1;
        unsigned int reserved_1 : 2;
    } reg;
} SOC_USB3OTG_DSTS_UNION;
#endif
#define SOC_USB3OTG_DSTS_ConnectSpd_START (0)
#define SOC_USB3OTG_DSTS_ConnectSpd_END (2)
#define SOC_USB3OTG_DSTS_SOFFN_START (3)
#define SOC_USB3OTG_DSTS_SOFFN_END (16)
#define SOC_USB3OTG_DSTS_RxFIFOEmpty_START (17)
#define SOC_USB3OTG_DSTS_RxFIFOEmpty_END (17)
#define SOC_USB3OTG_DSTS_USBLnkSts_START (18)
#define SOC_USB3OTG_DSTS_USBLnkSts_END (21)
#define SOC_USB3OTG_DSTS_DevCtrlHlt_START (22)
#define SOC_USB3OTG_DSTS_DevCtrlHlt_END (22)
#define SOC_USB3OTG_DSTS_CoreIdle_START (23)
#define SOC_USB3OTG_DSTS_CoreIdle_END (23)
#define SOC_USB3OTG_DSTS_SSS_START (24)
#define SOC_USB3OTG_DSTS_SSS_END (24)
#define SOC_USB3OTG_DSTS_RSS_START (25)
#define SOC_USB3OTG_DSTS_RSS_END (25)
#define SOC_USB3OTG_DSTS_SRE_START (28)
#define SOC_USB3OTG_DSTS_SRE_END (28)
#define SOC_USB3OTG_DSTS_DCNRD_START (29)
#define SOC_USB3OTG_DSTS_DCNRD_END (29)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int parameter : 32;
    } reg;
} SOC_USB3OTG_DGCMDPAR_UNION;
#endif
#define SOC_USB3OTG_DGCMDPAR_parameter_START (0)
#define SOC_USB3OTG_DGCMDPAR_parameter_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CmdTyp : 8;
        unsigned int CmdIOC : 1;
        unsigned int reserved_0: 1;
        unsigned int CmdAct : 1;
        unsigned int reserved_1: 4;
        unsigned int CmdSts : 1;
        unsigned int reserved_2: 16;
    } reg;
} SOC_USB3OTG_DGCMD_UNION;
#endif
#define SOC_USB3OTG_DGCMD_CmdTyp_START (0)
#define SOC_USB3OTG_DGCMD_CmdTyp_END (7)
#define SOC_USB3OTG_DGCMD_CmdIOC_START (8)
#define SOC_USB3OTG_DGCMD_CmdIOC_END (8)
#define SOC_USB3OTG_DGCMD_CmdAct_START (10)
#define SOC_USB3OTG_DGCMD_CmdAct_END (10)
#define SOC_USB3OTG_DGCMD_CmdSts_START (15)
#define SOC_USB3OTG_DGCMD_CmdSts_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int USBActEp : 32;
    } reg;
} SOC_USB3OTG_DALEPENA_UNION;
#endif
#define SOC_USB3OTG_DALEPENA_USBActEp_START (0)
#define SOC_USB3OTG_DALEPENA_USBActEp_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int parameter2 : 32;
    } reg;
} SOC_USB3OTG_DEPCMDPAR2m_UNION;
#endif
#define SOC_USB3OTG_DEPCMDPAR2m_parameter2_START (0)
#define SOC_USB3OTG_DEPCMDPAR2m_parameter2_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int parameter1 : 32;
    } reg;
} SOC_USB3OTG_DEPCMDPAR1m_UNION;
#endif
#define SOC_USB3OTG_DEPCMDPAR1m_parameter1_START (0)
#define SOC_USB3OTG_DEPCMDPAR1m_parameter1_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int parameter0 : 32;
    } reg;
} SOC_USB3OTG_DEPCMDPAR0m_UNION;
#endif
#define SOC_USB3OTG_DEPCMDPAR0m_parameter0_START (0)
#define SOC_USB3OTG_DEPCMDPAR0m_parameter0_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int CmdTyp : 4;
        unsigned int reserved_0 : 4;
        unsigned int CmdIOC : 1;
        unsigned int reserved_1 : 1;
        unsigned int CmdAct : 1;
        unsigned int HiPri_ForceRM : 1;
        unsigned int CmdStatus : 4;
        unsigned int CommandParam : 16;
    } reg;
} SOC_USB3OTG_DEPCMDm_UNION;
#endif
#define SOC_USB3OTG_DEPCMDm_CmdTyp_START (0)
#define SOC_USB3OTG_DEPCMDm_CmdTyp_END (3)
#define SOC_USB3OTG_DEPCMDm_CmdIOC_START (8)
#define SOC_USB3OTG_DEPCMDm_CmdIOC_END (8)
#define SOC_USB3OTG_DEPCMDm_CmdAct_START (10)
#define SOC_USB3OTG_DEPCMDm_CmdAct_END (10)
#define SOC_USB3OTG_DEPCMDm_HiPri_ForceRM_START (11)
#define SOC_USB3OTG_DEPCMDm_HiPri_ForceRM_END (11)
#define SOC_USB3OTG_DEPCMDm_CmdStatus_START (12)
#define SOC_USB3OTG_DEPCMDm_CmdStatus_END (15)
#define SOC_USB3OTG_DEPCMDm_CommandParam_START (16)
#define SOC_USB3OTG_DEPCMDm_CommandParam_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int SRPCap : 1;
        unsigned int HNPCap : 1;
        unsigned int OTGVersion : 1;
        unsigned int OTGSftRstMsk : 1;
        unsigned int OTGHibDisMsk : 1;
        unsigned int DisPrtPwrCutOff : 1;
        unsigned int reserved : 26;
    } reg;
} SOC_USB3OTG_OCFG_UNION;
#endif
#define SOC_USB3OTG_OCFG_SRPCap_START (0)
#define SOC_USB3OTG_OCFG_SRPCap_END (0)
#define SOC_USB3OTG_OCFG_HNPCap_START (1)
#define SOC_USB3OTG_OCFG_HNPCap_END (1)
#define SOC_USB3OTG_OCFG_OTGVersion_START (2)
#define SOC_USB3OTG_OCFG_OTGVersion_END (2)
#define SOC_USB3OTG_OCFG_OTGSftRstMsk_START (3)
#define SOC_USB3OTG_OCFG_OTGSftRstMsk_END (3)
#define SOC_USB3OTG_OCFG_OTGHibDisMsk_START (4)
#define SOC_USB3OTG_OCFG_OTGHibDisMsk_END (4)
#define SOC_USB3OTG_OCFG_DisPrtPwrCutOff_START (5)
#define SOC_USB3OTG_OCFG_DisPrtPwrCutOff_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int HstSetHNPEn : 1;
        unsigned int DevSetHNPEn : 1;
        unsigned int TermSelDLPulse : 1;
        unsigned int SesReq : 1;
        unsigned int HNPReq : 1;
        unsigned int PrtPwrCtl : 1;
        unsigned int PeriMode : 1;
        unsigned int OTG3_GOERR : 1;
        unsigned int reserved : 24;
    } reg;
} SOC_USB3OTG_OCTL_UNION;
#endif
#define SOC_USB3OTG_OCTL_HstSetHNPEn_START (0)
#define SOC_USB3OTG_OCTL_HstSetHNPEn_END (0)
#define SOC_USB3OTG_OCTL_DevSetHNPEn_START (1)
#define SOC_USB3OTG_OCTL_DevSetHNPEn_END (1)
#define SOC_USB3OTG_OCTL_TermSelDLPulse_START (2)
#define SOC_USB3OTG_OCTL_TermSelDLPulse_END (2)
#define SOC_USB3OTG_OCTL_SesReq_START (3)
#define SOC_USB3OTG_OCTL_SesReq_END (3)
#define SOC_USB3OTG_OCTL_HNPReq_START (4)
#define SOC_USB3OTG_OCTL_HNPReq_END (4)
#define SOC_USB3OTG_OCTL_PrtPwrCtl_START (5)
#define SOC_USB3OTG_OCTL_PrtPwrCtl_END (5)
#define SOC_USB3OTG_OCTL_PeriMode_START (6)
#define SOC_USB3OTG_OCTL_PeriMode_END (6)
#define SOC_USB3OTG_OCTL_OTG3_GOERR_START (7)
#define SOC_USB3OTG_OCTL_OTG3_GOERR_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int OEVNTError : 1;
        unsigned int SesReqSts : 1;
        unsigned int HstNegStss : 1;
        unsigned int BSesVld : 1;
        unsigned int reserved_0 : 4;
        unsigned int OTGBVbsChg : 1;
        unsigned int OTGBSrpChg : 1;
        unsigned int OTGBHnpChg : 1;
        unsigned int OTGBDevBHostEndEvnt : 1;
        unsigned int reserved_1 : 4;
        unsigned int OTGADevSessEndDetEvnt : 1;
        unsigned int OTGADevEvtInfo : 1;
        unsigned int OTGADevHNPChngEvnt : 1;
        unsigned int OTGADevHostEvnt : 1;
        unsigned int OTGADevBHostEndEvnt : 1;
        unsigned int OTGADevIdleEvnt : 1;
        unsigned int HRRInitNotifEvnt : 1;
        unsigned int HRRConfNotifEvnt : 1;
        unsigned int OTGConIDStsChngEvnt : 1;
        unsigned int OTGHibEntryEvnt : 1;
        unsigned int OTGDevRunStpSetEcnt : 1;
        unsigned int OTGXhciRunStpSetEvnt : 1;
        unsigned int reserved_2 : 3;
        unsigned int DeviceMode : 1;
    } reg;
} SOC_USB3OTG_OEVNT_UNION;
#endif
#define SOC_USB3OTG_OEVNT_OEVNTError_START (0)
#define SOC_USB3OTG_OEVNT_OEVNTError_END (0)
#define SOC_USB3OTG_OEVNT_SesReqSts_START (1)
#define SOC_USB3OTG_OEVNT_SesReqSts_END (1)
#define SOC_USB3OTG_OEVNT_HstNegStss_START (2)
#define SOC_USB3OTG_OEVNT_HstNegStss_END (2)
#define SOC_USB3OTG_OEVNT_BSesVld_START (3)
#define SOC_USB3OTG_OEVNT_BSesVld_END (3)
#define SOC_USB3OTG_OEVNT_OTGBVbsChg_START (8)
#define SOC_USB3OTG_OEVNT_OTGBVbsChg_END (8)
#define SOC_USB3OTG_OEVNT_OTGBSrpChg_START (9)
#define SOC_USB3OTG_OEVNT_OTGBSrpChg_END (9)
#define SOC_USB3OTG_OEVNT_OTGBHnpChg_START (10)
#define SOC_USB3OTG_OEVNT_OTGBHnpChg_END (10)
#define SOC_USB3OTG_OEVNT_OTGBDevBHostEndEvnt_START (11)
#define SOC_USB3OTG_OEVNT_OTGBDevBHostEndEvnt_END (11)
#define SOC_USB3OTG_OEVNT_OTGADevSessEndDetEvnt_START (16)
#define SOC_USB3OTG_OEVNT_OTGADevSessEndDetEvnt_END (16)
#define SOC_USB3OTG_OEVNT_OTGADevEvtInfo_START (17)
#define SOC_USB3OTG_OEVNT_OTGADevEvtInfo_END (17)
#define SOC_USB3OTG_OEVNT_OTGADevHNPChngEvnt_START (18)
#define SOC_USB3OTG_OEVNT_OTGADevHNPChngEvnt_END (18)
#define SOC_USB3OTG_OEVNT_OTGADevHostEvnt_START (19)
#define SOC_USB3OTG_OEVNT_OTGADevHostEvnt_END (19)
#define SOC_USB3OTG_OEVNT_OTGADevBHostEndEvnt_START (20)
#define SOC_USB3OTG_OEVNT_OTGADevBHostEndEvnt_END (20)
#define SOC_USB3OTG_OEVNT_OTGADevIdleEvnt_START (21)
#define SOC_USB3OTG_OEVNT_OTGADevIdleEvnt_END (21)
#define SOC_USB3OTG_OEVNT_HRRInitNotifEvnt_START (22)
#define SOC_USB3OTG_OEVNT_HRRInitNotifEvnt_END (22)
#define SOC_USB3OTG_OEVNT_HRRConfNotifEvnt_START (23)
#define SOC_USB3OTG_OEVNT_HRRConfNotifEvnt_END (23)
#define SOC_USB3OTG_OEVNT_OTGConIDStsChngEvnt_START (24)
#define SOC_USB3OTG_OEVNT_OTGConIDStsChngEvnt_END (24)
#define SOC_USB3OTG_OEVNT_OTGHibEntryEvnt_START (25)
#define SOC_USB3OTG_OEVNT_OTGHibEntryEvnt_END (25)
#define SOC_USB3OTG_OEVNT_OTGDevRunStpSetEcnt_START (26)
#define SOC_USB3OTG_OEVNT_OTGDevRunStpSetEcnt_END (26)
#define SOC_USB3OTG_OEVNT_OTGXhciRunStpSetEvnt_START (27)
#define SOC_USB3OTG_OEVNT_OTGXhciRunStpSetEvnt_END (27)
#define SOC_USB3OTG_OEVNT_DeviceMode_START (31)
#define SOC_USB3OTG_OEVNT_DeviceMode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 8;
        unsigned int OTGBVbsChgEn : 1;
        unsigned int OTGBSrpChgEn : 1;
        unsigned int OTGBHnpChgEn : 1;
        unsigned int OTGBDevBHostEndEvntEn : 1;
        unsigned int reserved_1 : 4;
        unsigned int OTGADevSessEndDetEvntEn : 1;
        unsigned int OTGADevEvtInfoEn : 1;
        unsigned int OTGADevHNPChngEvntEn : 1;
        unsigned int OTGADevHostEvntEn : 1;
        unsigned int OTGADevBHostEndEvntEn : 1;
        unsigned int OTGADevIdleEvntEn : 1;
        unsigned int HRRInitNotifEvntEn : 1;
        unsigned int HRRConfNotifEvntEn : 1;
        unsigned int OTGConIDStsChngEvntEn : 1;
        unsigned int OTGHibEntryEvntEn : 1;
        unsigned int OTGDevRunStpSetEcntEn : 1;
        unsigned int OTGXhciRunStpSetEvntEn : 1;
        unsigned int reserved_2 : 4;
    } reg;
} SOC_USB3OTG_OEVNTEN_UNION;
#endif
#define SOC_USB3OTG_OEVNTEN_OTGBVbsChgEn_START (8)
#define SOC_USB3OTG_OEVNTEN_OTGBVbsChgEn_END (8)
#define SOC_USB3OTG_OEVNTEN_OTGBSrpChgEn_START (9)
#define SOC_USB3OTG_OEVNTEN_OTGBSrpChgEn_END (9)
#define SOC_USB3OTG_OEVNTEN_OTGBHnpChgEn_START (10)
#define SOC_USB3OTG_OEVNTEN_OTGBHnpChgEn_END (10)
#define SOC_USB3OTG_OEVNTEN_OTGBDevBHostEndEvntEn_START (11)
#define SOC_USB3OTG_OEVNTEN_OTGBDevBHostEndEvntEn_END (11)
#define SOC_USB3OTG_OEVNTEN_OTGADevSessEndDetEvntEn_START (16)
#define SOC_USB3OTG_OEVNTEN_OTGADevSessEndDetEvntEn_END (16)
#define SOC_USB3OTG_OEVNTEN_OTGADevEvtInfoEn_START (17)
#define SOC_USB3OTG_OEVNTEN_OTGADevEvtInfoEn_END (17)
#define SOC_USB3OTG_OEVNTEN_OTGADevHNPChngEvntEn_START (18)
#define SOC_USB3OTG_OEVNTEN_OTGADevHNPChngEvntEn_END (18)
#define SOC_USB3OTG_OEVNTEN_OTGADevHostEvntEn_START (19)
#define SOC_USB3OTG_OEVNTEN_OTGADevHostEvntEn_END (19)
#define SOC_USB3OTG_OEVNTEN_OTGADevBHostEndEvntEn_START (20)
#define SOC_USB3OTG_OEVNTEN_OTGADevBHostEndEvntEn_END (20)
#define SOC_USB3OTG_OEVNTEN_OTGADevIdleEvntEn_START (21)
#define SOC_USB3OTG_OEVNTEN_OTGADevIdleEvntEn_END (21)
#define SOC_USB3OTG_OEVNTEN_HRRInitNotifEvntEn_START (22)
#define SOC_USB3OTG_OEVNTEN_HRRInitNotifEvntEn_END (22)
#define SOC_USB3OTG_OEVNTEN_HRRConfNotifEvntEn_START (23)
#define SOC_USB3OTG_OEVNTEN_HRRConfNotifEvntEn_END (23)
#define SOC_USB3OTG_OEVNTEN_OTGConIDStsChngEvntEn_START (24)
#define SOC_USB3OTG_OEVNTEN_OTGConIDStsChngEvntEn_END (24)
#define SOC_USB3OTG_OEVNTEN_OTGHibEntryEvntEn_START (25)
#define SOC_USB3OTG_OEVNTEN_OTGHibEntryEvntEn_END (25)
#define SOC_USB3OTG_OEVNTEN_OTGDevRunStpSetEcntEn_START (26)
#define SOC_USB3OTG_OEVNTEN_OTGDevRunStpSetEcntEn_END (26)
#define SOC_USB3OTG_OEVNTEN_OTGXhciRunStpSetEvntEn_START (27)
#define SOC_USB3OTG_OEVNTEN_OTGXhciRunStpSetEvntEn_END (27)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ConIDSts : 1;
        unsigned int VbusVld : 1;
        unsigned int BSesVld : 1;
        unsigned int xHCIPrtPower : 1;
        unsigned int PeripheralState : 1;
        unsigned int reserved_0 : 3;
        unsigned int OTG2State : 4;
        unsigned int HstRunStp : 1;
        unsigned int DevRunStp : 1;
        unsigned int reserved_1 : 18;
    } reg;
} SOC_USB3OTG_OSTS_UNION;
#endif
#define SOC_USB3OTG_OSTS_ConIDSts_START (0)
#define SOC_USB3OTG_OSTS_ConIDSts_END (0)
#define SOC_USB3OTG_OSTS_VbusVld_START (1)
#define SOC_USB3OTG_OSTS_VbusVld_END (1)
#define SOC_USB3OTG_OSTS_BSesVld_START (2)
#define SOC_USB3OTG_OSTS_BSesVld_END (2)
#define SOC_USB3OTG_OSTS_xHCIPrtPower_START (3)
#define SOC_USB3OTG_OSTS_xHCIPrtPower_END (3)
#define SOC_USB3OTG_OSTS_PeripheralState_START (4)
#define SOC_USB3OTG_OSTS_PeripheralState_END (4)
#define SOC_USB3OTG_OSTS_OTG2State_START (8)
#define SOC_USB3OTG_OSTS_OTG2State_END (11)
#define SOC_USB3OTG_OSTS_HstRunStp_START (12)
#define SOC_USB3OTG_OSTS_HstRunStp_END (12)
#define SOC_USB3OTG_OSTS_DevRunStp_START (13)
#define SOC_USB3OTG_OSTS_DevRunStp_END (13)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 26;
        unsigned int PrbDschg : 2;
        unsigned int ProbeDelta : 2;
        unsigned int PrbPer : 2;
    } reg;
} SOC_USB3OTG_ADPCFG_UNION;
#endif
#define SOC_USB3OTG_ADPCFG_PrbDschg_START (26)
#define SOC_USB3OTG_ADPCFG_PrbDschg_END (27)
#define SOC_USB3OTG_ADPCFG_ProbeDelta_START (28)
#define SOC_USB3OTG_ADPCFG_ProbeDelta_END (29)
#define SOC_USB3OTG_ADPCFG_PrbPer_START (30)
#define SOC_USB3OTG_ADPCFG_PrbPer_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 24;
        unsigned int WB : 1;
        unsigned int ADPRes : 1;
        unsigned int ADPEn : 1;
        unsigned int EnaSns : 1;
        unsigned int EnaPrb : 1;
        unsigned int reserved_1: 3;
    } reg;
} SOC_USB3OTG_ADPCTL_UNION;
#endif
#define SOC_USB3OTG_ADPCTL_WB_START (24)
#define SOC_USB3OTG_ADPCTL_WB_END (24)
#define SOC_USB3OTG_ADPCTL_ADPRes_START (25)
#define SOC_USB3OTG_ADPCTL_ADPRes_END (25)
#define SOC_USB3OTG_ADPCTL_ADPEn_START (26)
#define SOC_USB3OTG_ADPCTL_ADPEn_END (26)
#define SOC_USB3OTG_ADPCTL_EnaSns_START (27)
#define SOC_USB3OTG_ADPCTL_EnaSns_END (27)
#define SOC_USB3OTG_ADPCTL_EnaPrb_START (28)
#define SOC_USB3OTG_ADPCTL_EnaPrb_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int RTIM : 16;
        unsigned int reserved_0 : 9;
        unsigned int ADPRstCmpltEvnt : 1;
        unsigned int ADPTimeoutEvnt : 1;
        unsigned int ADPSnsEvnt : 1;
        unsigned int ADPEVTInfo : 1;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_USB3OTG_ADPEVNT_UNION;
#endif
#define SOC_USB3OTG_ADPEVNT_RTIM_START (0)
#define SOC_USB3OTG_ADPEVNT_RTIM_END (15)
#define SOC_USB3OTG_ADPEVNT_ADPRstCmpltEvnt_START (25)
#define SOC_USB3OTG_ADPEVNT_ADPRstCmpltEvnt_END (25)
#define SOC_USB3OTG_ADPEVNT_ADPTimeoutEvnt_START (26)
#define SOC_USB3OTG_ADPEVNT_ADPTimeoutEvnt_END (26)
#define SOC_USB3OTG_ADPEVNT_ADPSnsEvnt_START (27)
#define SOC_USB3OTG_ADPEVNT_ADPSnsEvnt_END (27)
#define SOC_USB3OTG_ADPEVNT_ADPEVTInfo_START (28)
#define SOC_USB3OTG_ADPEVNT_ADPEVTInfo_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 25;
        unsigned int ADPRstCmpltEvntEn : 1;
        unsigned int ADPTimeoutEvntEn : 1;
        unsigned int ADPSnsEvntEn : 1;
        unsigned int ADPEVTInfoEn : 1;
        unsigned int reserved_1 : 3;
    } reg;
} SOC_USB3OTG_ADPEVNTEN_UNION;
#endif
#define SOC_USB3OTG_ADPEVNTEN_ADPRstCmpltEvntEn_START (25)
#define SOC_USB3OTG_ADPEVNTEN_ADPRstCmpltEvntEn_END (25)
#define SOC_USB3OTG_ADPEVNTEN_ADPTimeoutEvntEn_START (26)
#define SOC_USB3OTG_ADPEVNTEN_ADPTimeoutEvntEn_END (26)
#define SOC_USB3OTG_ADPEVNTEN_ADPSnsEvntEn_START (27)
#define SOC_USB3OTG_ADPEVNTEN_ADPSnsEvntEn_END (27)
#define SOC_USB3OTG_ADPEVNTEN_ADPEVTInfoEn_START (28)
#define SOC_USB3OTG_ADPEVNTEN_ADPEVTInfoEn_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int chirp_en : 1;
        unsigned int IDDIG_SEL : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_USB3OTG_BCFG_UNION;
#endif
#define SOC_USB3OTG_BCFG_chirp_en_START (0)
#define SOC_USB3OTG_BCFG_chirp_en_END (0)
#define SOC_USB3OTG_BCFG_IDDIG_SEL_START (1)
#define SOC_USB3OTG_BCFG_IDDIG_SEL_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int MultValIdBc : 5;
        unsigned int reserved_0 : 19;
        unsigned int mv_chngevnt : 1;
        unsigned int reserved_1 : 7;
    } reg;
} SOC_USB3OTG_BCEVT_UNION;
#endif
#define SOC_USB3OTG_BCEVT_MultValIdBc_START (0)
#define SOC_USB3OTG_BCEVT_MultValIdBc_END (4)
#define SOC_USB3OTG_BCEVT_mv_chngevnt_START (24)
#define SOC_USB3OTG_BCEVT_mv_chngevnt_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 24;
        unsigned int mv_chngevntena : 1;
        unsigned int reserved_1 : 7;
    } reg;
} SOC_USB3OTG_BCEVTEN_UNION;
#endif
#define SOC_USB3OTG_BCEVTEN_mv_chngevntena_START (24)
#define SOC_USB3OTG_BCEVTEN_mv_chngevntena_END (24)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
