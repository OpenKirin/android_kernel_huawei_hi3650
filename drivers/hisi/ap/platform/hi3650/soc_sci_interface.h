#ifndef __SOC_SCI_INTERFACE_H__
#define __SOC_SCI_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_SCI_DATA_ADDR(base) ((base) + (0x0000))
#define SOC_SCI_CR0_ADDR(base) ((base) + (0x0004))
#define SOC_SCI_CR1_ADDR(base) ((base) + (0x0008))
#define SOC_SCI_CR2_ADDR(base) ((base) + (0x000C))
#define SOC_SCI_CLKICC_ADDR(base) ((base) + (0x0010))
#define SOC_SCI_VALUE_ADDR(base) ((base) + (0x0014))
#define SOC_SCI_BAUD_ADDR(base) ((base) + (0x0018))
#define SOC_SCI_TIDE_ADDR(base) ((base) + (0x001C))
#define SOC_SCI_DMACR_ADDR(base) ((base) + (0x0020))
#define SOC_SCI_STABLE_ADDR(base) ((base) + (0x0024))
#define SOC_SCI_ATIME_ADDR(base) ((base) + (0x0028))
#define SOC_SCI_DTIME_ADDR(base) ((base) + (0x002C))
#define SOC_SCI_ATRSTIME_ADDR(base) ((base) + (0x0030))
#define SOC_SCI_ATRDTIME_ADDR(base) ((base) + (0x0034))
#define SOC_SCI_STOPTIME_ADDR(base) ((base) + (0x0038))
#define SOC_SCI_STARTTIME_ADDR(base) ((base) + (0x003C))
#define SOC_SCI_RETRY_ADDR(base) ((base) + (0x0040))
#define SOC_SCI_CHTIMELS_ADDR(base) ((base) + (0x0044))
#define SOC_SCI_CHTIMEMS_ADDR(base) ((base) + (0x0048))
#define SOC_SCI_BLKTIMELS_ADDR(base) ((base) + (0x004C))
#define SOC_SCI_BLKTIMEMS_ADDR(base) ((base) + (0x0050))
#define SOC_SCI_CHGUARD_ADDR(base) ((base) + (0x0054))
#define SOC_SCI_BLKGUARD_ADDR(base) ((base) + (0x0058))
#define SOC_SCI_RXTIME_ADDR(base) ((base) + (0x005C))
#define SOC_SCI_FIFOSTATUS_ADDR(base) ((base) + (0x0060))
#define SOC_SCI_TXCOUNT_ADDR(base) ((base) + (0x0064))
#define SOC_SCI_RXCOUNT_ADDR(base) ((base) + (0x0068))
#define SOC_SCI_IMSC_ADDR(base) ((base) + (0x006C))
#define SOC_SCI_RIS_ADDR(base) ((base) + (0x0070))
#define SOC_SCI_MIS_ADDR(base) ((base) + (0x0074))
#define SOC_SCI_ICR_ADDR(base) ((base) + (0x0078))
#define SOC_SCI_SYNCACT_ADDR(base) ((base) + (0x007C))
#define SOC_SCI_SYNCTX_ADDR(base) ((base) + (0x0080))
#define SOC_SCI_SYNCRX_ADDR(base) ((base) + (0x0084))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short scidata : 8;
        unsigned short parity : 1;
        unsigned short reserved : 7;
    } reg;
} SOC_SCI_DATA_UNION;
#endif
#define SOC_SCI_DATA_scidata_START (0)
#define SOC_SCI_DATA_scidata_END (7)
#define SOC_SCI_DATA_parity_START (8)
#define SOC_SCI_DATA_parity_END (8)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short sense : 1;
        unsigned short order : 1;
        unsigned short txparity : 1;
        unsigned short txnak : 1;
        unsigned short rxparity : 1;
        unsigned short rxnak : 1;
        unsigned short clkdis : 1;
        unsigned short clkval : 1;
        unsigned short reserved : 8;
    } reg;
} SOC_SCI_CR0_UNION;
#endif
#define SOC_SCI_CR0_sense_START (0)
#define SOC_SCI_CR0_sense_END (0)
#define SOC_SCI_CR0_order_START (1)
#define SOC_SCI_CR0_order_END (1)
#define SOC_SCI_CR0_txparity_START (2)
#define SOC_SCI_CR0_txparity_END (2)
#define SOC_SCI_CR0_txnak_START (3)
#define SOC_SCI_CR0_txnak_END (3)
#define SOC_SCI_CR0_rxparity_START (4)
#define SOC_SCI_CR0_rxparity_END (4)
#define SOC_SCI_CR0_rxnak_START (5)
#define SOC_SCI_CR0_rxnak_END (5)
#define SOC_SCI_CR0_clkdis_START (6)
#define SOC_SCI_CR0_clkdis_END (6)
#define SOC_SCI_CR0_clkval_START (7)
#define SOC_SCI_CR0_clkval_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short atrden : 1;
        unsigned short blken : 1;
        unsigned short mode : 1;
        unsigned short clkz1 : 1;
        unsigned short bgten : 1;
        unsigned short exdbnce : 1;
        unsigned short synccard : 1;
        unsigned short reserved : 9;
    } reg;
} SOC_SCI_CR1_UNION;
#endif
#define SOC_SCI_CR1_atrden_START (0)
#define SOC_SCI_CR1_atrden_END (0)
#define SOC_SCI_CR1_blken_START (1)
#define SOC_SCI_CR1_blken_END (1)
#define SOC_SCI_CR1_mode_START (2)
#define SOC_SCI_CR1_mode_END (2)
#define SOC_SCI_CR1_clkz1_START (3)
#define SOC_SCI_CR1_clkz1_END (3)
#define SOC_SCI_CR1_bgten_START (4)
#define SOC_SCI_CR1_bgten_END (4)
#define SOC_SCI_CR1_exdbnce_START (5)
#define SOC_SCI_CR1_exdbnce_END (5)
#define SOC_SCI_CR1_synccard_START (6)
#define SOC_SCI_CR1_synccard_END (6)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short startup : 1;
        unsigned short finish : 1;
        unsigned short wreset : 1;
        unsigned short reserved : 13;
    } reg;
} SOC_SCI_CR2_UNION;
#endif
#define SOC_SCI_CR2_startup_START (0)
#define SOC_SCI_CR2_startup_END (0)
#define SOC_SCI_CR2_finish_START (1)
#define SOC_SCI_CR2_finish_END (1)
#define SOC_SCI_CR2_wreset_START (2)
#define SOC_SCI_CR2_wreset_END (2)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short clkicc : 8;
        unsigned short reserved : 8;
    } reg;
} SOC_SCI_CLKICC_UNION;
#endif
#define SOC_SCI_CLKICC_clkicc_START (0)
#define SOC_SCI_CLKICC_clkicc_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short value : 8;
        unsigned short reserved : 8;
    } reg;
} SOC_SCI_VALUE_UNION;
#endif
#define SOC_SCI_VALUE_value_START (0)
#define SOC_SCI_VALUE_value_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short baud : 16;
    } reg;
} SOC_SCI_BAUD_UNION;
#endif
#define SOC_SCI_BAUD_baud_START (0)
#define SOC_SCI_BAUD_baud_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short txtide : 6;
        unsigned short rxtide : 6;
        unsigned short reserved : 4;
    } reg;
} SOC_SCI_TIDE_UNION;
#endif
#define SOC_SCI_TIDE_txtide_START (0)
#define SOC_SCI_TIDE_txtide_END (5)
#define SOC_SCI_TIDE_rxtide_START (6)
#define SOC_SCI_TIDE_rxtide_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short rxdmae : 1;
        unsigned short txdmae : 1;
        unsigned short reserved : 14;
    } reg;
} SOC_SCI_DMACR_UNION;
#endif
#define SOC_SCI_DMACR_rxdmae_START (0)
#define SOC_SCI_DMACR_rxdmae_END (0)
#define SOC_SCI_DMACR_txdmae_START (1)
#define SOC_SCI_DMACR_txdmae_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short stable : 10;
        unsigned short reserved : 6;
    } reg;
} SOC_SCI_STABLE_UNION;
#endif
#define SOC_SCI_STABLE_stable_START (0)
#define SOC_SCI_STABLE_stable_END (9)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short atime : 16;
    } reg;
} SOC_SCI_ATIME_UNION;
#endif
#define SOC_SCI_ATIME_atime_START (0)
#define SOC_SCI_ATIME_atime_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short dtime : 16;
    } reg;
} SOC_SCI_DTIME_UNION;
#endif
#define SOC_SCI_DTIME_dtime_START (0)
#define SOC_SCI_DTIME_dtime_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short atrstime : 16;
    } reg;
} SOC_SCI_ATRSTIME_UNION;
#endif
#define SOC_SCI_ATRSTIME_atrstime_START (0)
#define SOC_SCI_ATRSTIME_atrstime_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short atrdtime : 16;
    } reg;
} SOC_SCI_ATRDTIME_UNION;
#endif
#define SOC_SCI_ATRDTIME_atrdtime_START (0)
#define SOC_SCI_ATRDTIME_atrdtime_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short stoptime : 12;
        unsigned short reserved : 4;
    } reg;
} SOC_SCI_STOPTIME_UNION;
#endif
#define SOC_SCI_STOPTIME_stoptime_START (0)
#define SOC_SCI_STOPTIME_stoptime_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short starttime : 12;
        unsigned short reserved : 4;
    } reg;
} SOC_SCI_STARTTIME_UNION;
#endif
#define SOC_SCI_STARTTIME_starttime_START (0)
#define SOC_SCI_STARTTIME_starttime_END (11)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short txretry : 3;
        unsigned short rxretry : 3;
        unsigned short reserved : 10;
    } reg;
} SOC_SCI_RETRY_UNION;
#endif
#define SOC_SCI_RETRY_txretry_START (0)
#define SOC_SCI_RETRY_txretry_END (2)
#define SOC_SCI_RETRY_rxretry_START (3)
#define SOC_SCI_RETRY_rxretry_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short chtimels : 16;
    } reg;
} SOC_SCI_CHTIMELS_UNION;
#endif
#define SOC_SCI_CHTIMELS_chtimels_START (0)
#define SOC_SCI_CHTIMELS_chtimels_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short chtimems : 16;
    } reg;
} SOC_SCI_CHTIMEMS_UNION;
#endif
#define SOC_SCI_CHTIMEMS_chtimems_START (0)
#define SOC_SCI_CHTIMEMS_chtimems_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short blktimels : 16;
    } reg;
} SOC_SCI_BLKTIMELS_UNION;
#endif
#define SOC_SCI_BLKTIMELS_blktimels_START (0)
#define SOC_SCI_BLKTIMELS_blktimels_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short blktimems : 16;
    } reg;
} SOC_SCI_BLKTIMEMS_UNION;
#endif
#define SOC_SCI_BLKTIMEMS_blktimems_START (0)
#define SOC_SCI_BLKTIMEMS_blktimems_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short scichguard : 8;
        unsigned short reserved : 8;
    } reg;
} SOC_SCI_CHGUARD_UNION;
#endif
#define SOC_SCI_CHGUARD_scichguard_START (0)
#define SOC_SCI_CHGUARD_scichguard_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short sciblkguard : 8;
        unsigned short reserved : 8;
    } reg;
} SOC_SCI_BLKGUARD_UNION;
#endif
#define SOC_SCI_BLKGUARD_sciblkguard_START (0)
#define SOC_SCI_BLKGUARD_sciblkguard_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short rxtime : 16;
    } reg;
} SOC_SCI_RXTIME_UNION;
#endif
#define SOC_SCI_RXTIME_rxtime_START (0)
#define SOC_SCI_RXTIME_rxtime_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short txff : 1;
        unsigned short txfe : 1;
        unsigned short rxff : 1;
        unsigned short rxfe : 1;
        unsigned short reserved : 12;
    } reg;
} SOC_SCI_FIFOSTATUS_UNION;
#endif
#define SOC_SCI_FIFOSTATUS_txff_START (0)
#define SOC_SCI_FIFOSTATUS_txff_END (0)
#define SOC_SCI_FIFOSTATUS_txfe_START (1)
#define SOC_SCI_FIFOSTATUS_txfe_END (1)
#define SOC_SCI_FIFOSTATUS_rxff_START (2)
#define SOC_SCI_FIFOSTATUS_rxff_END (2)
#define SOC_SCI_FIFOSTATUS_rxfe_START (3)
#define SOC_SCI_FIFOSTATUS_rxfe_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short txcount : 6;
        unsigned short reserved : 10;
    } reg;
} SOC_SCI_TXCOUNT_UNION;
#endif
#define SOC_SCI_TXCOUNT_txcount_START (0)
#define SOC_SCI_TXCOUNT_txcount_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short rxcount : 6;
        unsigned short reserved : 10;
    } reg;
} SOC_SCI_RXCOUNT_UNION;
#endif
#define SOC_SCI_RXCOUNT_rxcount_START (0)
#define SOC_SCI_RXCOUNT_rxcount_END (5)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short cardinim : 1;
        unsigned short cardoutim : 1;
        unsigned short cardupim : 1;
        unsigned short carddnim : 1;
        unsigned short txerrim : 1;
        unsigned short atrstoutim : 1;
        unsigned short atrdtoutim : 1;
        unsigned short blktoutim : 1;
        unsigned short chtoutim : 1;
        unsigned short rtoutim : 1;
        unsigned short rorim : 1;
        unsigned short clkstpim : 1;
        unsigned short clkactim : 1;
        unsigned short rxtideim : 1;
        unsigned short txtideim : 1;
        unsigned short reserved : 1;
    } reg;
} SOC_SCI_IMSC_UNION;
#endif
#define SOC_SCI_IMSC_cardinim_START (0)
#define SOC_SCI_IMSC_cardinim_END (0)
#define SOC_SCI_IMSC_cardoutim_START (1)
#define SOC_SCI_IMSC_cardoutim_END (1)
#define SOC_SCI_IMSC_cardupim_START (2)
#define SOC_SCI_IMSC_cardupim_END (2)
#define SOC_SCI_IMSC_carddnim_START (3)
#define SOC_SCI_IMSC_carddnim_END (3)
#define SOC_SCI_IMSC_txerrim_START (4)
#define SOC_SCI_IMSC_txerrim_END (4)
#define SOC_SCI_IMSC_atrstoutim_START (5)
#define SOC_SCI_IMSC_atrstoutim_END (5)
#define SOC_SCI_IMSC_atrdtoutim_START (6)
#define SOC_SCI_IMSC_atrdtoutim_END (6)
#define SOC_SCI_IMSC_blktoutim_START (7)
#define SOC_SCI_IMSC_blktoutim_END (7)
#define SOC_SCI_IMSC_chtoutim_START (8)
#define SOC_SCI_IMSC_chtoutim_END (8)
#define SOC_SCI_IMSC_rtoutim_START (9)
#define SOC_SCI_IMSC_rtoutim_END (9)
#define SOC_SCI_IMSC_rorim_START (10)
#define SOC_SCI_IMSC_rorim_END (10)
#define SOC_SCI_IMSC_clkstpim_START (11)
#define SOC_SCI_IMSC_clkstpim_END (11)
#define SOC_SCI_IMSC_clkactim_START (12)
#define SOC_SCI_IMSC_clkactim_END (12)
#define SOC_SCI_IMSC_rxtideim_START (13)
#define SOC_SCI_IMSC_rxtideim_END (13)
#define SOC_SCI_IMSC_txtideim_START (14)
#define SOC_SCI_IMSC_txtideim_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short cardinris : 1;
        unsigned short cardoutris : 1;
        unsigned short cardupris : 1;
        unsigned short carddnris : 1;
        unsigned short txerrris : 1;
        unsigned short atrstoutris : 1;
        unsigned short atrdtoutris : 1;
        unsigned short blktoutris : 1;
        unsigned short chtoutris : 1;
        unsigned short rtoutris : 1;
        unsigned short rorris : 1;
        unsigned short clkstpris : 1;
        unsigned short clkactris : 1;
        unsigned short rxtideris : 1;
        unsigned short txtideris : 1;
        unsigned short reserved : 1;
    } reg;
} SOC_SCI_RIS_UNION;
#endif
#define SOC_SCI_RIS_cardinris_START (0)
#define SOC_SCI_RIS_cardinris_END (0)
#define SOC_SCI_RIS_cardoutris_START (1)
#define SOC_SCI_RIS_cardoutris_END (1)
#define SOC_SCI_RIS_cardupris_START (2)
#define SOC_SCI_RIS_cardupris_END (2)
#define SOC_SCI_RIS_carddnris_START (3)
#define SOC_SCI_RIS_carddnris_END (3)
#define SOC_SCI_RIS_txerrris_START (4)
#define SOC_SCI_RIS_txerrris_END (4)
#define SOC_SCI_RIS_atrstoutris_START (5)
#define SOC_SCI_RIS_atrstoutris_END (5)
#define SOC_SCI_RIS_atrdtoutris_START (6)
#define SOC_SCI_RIS_atrdtoutris_END (6)
#define SOC_SCI_RIS_blktoutris_START (7)
#define SOC_SCI_RIS_blktoutris_END (7)
#define SOC_SCI_RIS_chtoutris_START (8)
#define SOC_SCI_RIS_chtoutris_END (8)
#define SOC_SCI_RIS_rtoutris_START (9)
#define SOC_SCI_RIS_rtoutris_END (9)
#define SOC_SCI_RIS_rorris_START (10)
#define SOC_SCI_RIS_rorris_END (10)
#define SOC_SCI_RIS_clkstpris_START (11)
#define SOC_SCI_RIS_clkstpris_END (11)
#define SOC_SCI_RIS_clkactris_START (12)
#define SOC_SCI_RIS_clkactris_END (12)
#define SOC_SCI_RIS_rxtideris_START (13)
#define SOC_SCI_RIS_rxtideris_END (13)
#define SOC_SCI_RIS_txtideris_START (14)
#define SOC_SCI_RIS_txtideris_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short cardinmis : 1;
        unsigned short cardoutmis : 1;
        unsigned short cardupmis : 1;
        unsigned short carddnmis : 1;
        unsigned short txerrmis : 1;
        unsigned short atrstoutim : 1;
        unsigned short atrdtoutmis : 1;
        unsigned short blktoutmis : 1;
        unsigned short chtoutmis : 1;
        unsigned short rtoutmis : 1;
        unsigned short rormis : 1;
        unsigned short clkstpmis : 1;
        unsigned short clkactmis : 1;
        unsigned short rxtidemis : 1;
        unsigned short txtidemis : 1;
        unsigned short reserved : 1;
    } reg;
} SOC_SCI_MIS_UNION;
#endif
#define SOC_SCI_MIS_cardinmis_START (0)
#define SOC_SCI_MIS_cardinmis_END (0)
#define SOC_SCI_MIS_cardoutmis_START (1)
#define SOC_SCI_MIS_cardoutmis_END (1)
#define SOC_SCI_MIS_cardupmis_START (2)
#define SOC_SCI_MIS_cardupmis_END (2)
#define SOC_SCI_MIS_carddnmis_START (3)
#define SOC_SCI_MIS_carddnmis_END (3)
#define SOC_SCI_MIS_txerrmis_START (4)
#define SOC_SCI_MIS_txerrmis_END (4)
#define SOC_SCI_MIS_atrstoutim_START (5)
#define SOC_SCI_MIS_atrstoutim_END (5)
#define SOC_SCI_MIS_atrdtoutmis_START (6)
#define SOC_SCI_MIS_atrdtoutmis_END (6)
#define SOC_SCI_MIS_blktoutmis_START (7)
#define SOC_SCI_MIS_blktoutmis_END (7)
#define SOC_SCI_MIS_chtoutmis_START (8)
#define SOC_SCI_MIS_chtoutmis_END (8)
#define SOC_SCI_MIS_rtoutmis_START (9)
#define SOC_SCI_MIS_rtoutmis_END (9)
#define SOC_SCI_MIS_rormis_START (10)
#define SOC_SCI_MIS_rormis_END (10)
#define SOC_SCI_MIS_clkstpmis_START (11)
#define SOC_SCI_MIS_clkstpmis_END (11)
#define SOC_SCI_MIS_clkactmis_START (12)
#define SOC_SCI_MIS_clkactmis_END (12)
#define SOC_SCI_MIS_rxtidemis_START (13)
#define SOC_SCI_MIS_rxtidemis_END (13)
#define SOC_SCI_MIS_txtidemis_START (14)
#define SOC_SCI_MIS_txtidemis_END (14)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short cardinic : 1;
        unsigned short cardoutic : 1;
        unsigned short cardupic : 1;
        unsigned short carddnic : 1;
        unsigned short txerric : 1;
        unsigned short atrstoutic : 1;
        unsigned short atrdtoutic : 1;
        unsigned short blktoutic : 1;
        unsigned short chtoutic : 1;
        unsigned short rtoutic : 1;
        unsigned short roric : 1;
        unsigned short clkstpic : 1;
        unsigned short clkactic : 1;
        unsigned short reserved : 3;
    } reg;
} SOC_SCI_ICR_UNION;
#endif
#define SOC_SCI_ICR_cardinic_START (0)
#define SOC_SCI_ICR_cardinic_END (0)
#define SOC_SCI_ICR_cardoutic_START (1)
#define SOC_SCI_ICR_cardoutic_END (1)
#define SOC_SCI_ICR_cardupic_START (2)
#define SOC_SCI_ICR_cardupic_END (2)
#define SOC_SCI_ICR_carddnic_START (3)
#define SOC_SCI_ICR_carddnic_END (3)
#define SOC_SCI_ICR_txerric_START (4)
#define SOC_SCI_ICR_txerric_END (4)
#define SOC_SCI_ICR_atrstoutic_START (5)
#define SOC_SCI_ICR_atrstoutic_END (5)
#define SOC_SCI_ICR_atrdtoutic_START (6)
#define SOC_SCI_ICR_atrdtoutic_END (6)
#define SOC_SCI_ICR_blktoutic_START (7)
#define SOC_SCI_ICR_blktoutic_END (7)
#define SOC_SCI_ICR_chtoutic_START (8)
#define SOC_SCI_ICR_chtoutic_END (8)
#define SOC_SCI_ICR_rtoutic_START (9)
#define SOC_SCI_ICR_rtoutic_END (9)
#define SOC_SCI_ICR_roric_START (10)
#define SOC_SCI_ICR_roric_END (10)
#define SOC_SCI_ICR_clkstpic_START (11)
#define SOC_SCI_ICR_clkstpic_END (11)
#define SOC_SCI_ICR_clkactic_START (12)
#define SOC_SCI_ICR_clkactic_END (12)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short power : 1;
        unsigned short creset : 1;
        unsigned short clken : 1;
        unsigned short dataen : 1;
        unsigned short reserved_0 : 1;
        unsigned short nsciclkouten : 1;
        unsigned short nsciclken : 1;
        unsigned short sciclkout : 1;
        unsigned short nscidataouten : 1;
        unsigned short nscidataen : 1;
        unsigned short cardpresent : 1;
        unsigned short reserved_1 : 5;
    } reg;
} SOC_SCI_SYNCACT_UNION;
#endif
#define SOC_SCI_SYNCACT_power_START (0)
#define SOC_SCI_SYNCACT_power_END (0)
#define SOC_SCI_SYNCACT_creset_START (1)
#define SOC_SCI_SYNCACT_creset_END (1)
#define SOC_SCI_SYNCACT_clken_START (2)
#define SOC_SCI_SYNCACT_clken_END (2)
#define SOC_SCI_SYNCACT_dataen_START (3)
#define SOC_SCI_SYNCACT_dataen_END (3)
#define SOC_SCI_SYNCACT_nsciclkouten_START (5)
#define SOC_SCI_SYNCACT_nsciclkouten_END (5)
#define SOC_SCI_SYNCACT_nsciclken_START (6)
#define SOC_SCI_SYNCACT_nsciclken_END (6)
#define SOC_SCI_SYNCACT_sciclkout_START (7)
#define SOC_SCI_SYNCACT_sciclkout_END (7)
#define SOC_SCI_SYNCACT_nscidataouten_START (8)
#define SOC_SCI_SYNCACT_nscidataouten_END (8)
#define SOC_SCI_SYNCACT_nscidataen_START (9)
#define SOC_SCI_SYNCACT_nscidataen_END (9)
#define SOC_SCI_SYNCACT_cardpresent_START (10)
#define SOC_SCI_SYNCACT_cardpresent_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short wdata : 1;
        unsigned short wclk : 1;
        unsigned short wdataen : 1;
        unsigned short wclken : 1;
        unsigned short wrst : 1;
        unsigned short reserved_0: 1;
        unsigned short reserved_1: 10;
    } reg;
} SOC_SCI_SYNCTX_UNION;
#endif
#define SOC_SCI_SYNCTX_wdata_START (0)
#define SOC_SCI_SYNCTX_wdata_END (0)
#define SOC_SCI_SYNCTX_wclk_START (1)
#define SOC_SCI_SYNCTX_wclk_END (1)
#define SOC_SCI_SYNCTX_wdataen_START (2)
#define SOC_SCI_SYNCTX_wdataen_END (2)
#define SOC_SCI_SYNCTX_wclken_START (3)
#define SOC_SCI_SYNCTX_wclken_END (3)
#define SOC_SCI_SYNCTX_wrst_START (4)
#define SOC_SCI_SYNCTX_wrst_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned short value;
    struct
    {
        unsigned short rdata : 1;
        unsigned short rclk : 1;
        unsigned short reserved : 14;
    } reg;
} SOC_SCI_SYNCRX_UNION;
#endif
#define SOC_SCI_SYNCRX_rdata_START (0)
#define SOC_SCI_SYNCRX_rdata_END (0)
#define SOC_SCI_SYNCRX_rclk_START (1)
#define SOC_SCI_SYNCRX_rclk_END (1)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
