#ifndef __HI_AP_SCTRL_H__
#define __HI_AP_SCTRL_H__ 
#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4) 
#endif
#define HI_AP_SCTRL_SCCTRL_OFFSET (0x0)
#define HI_AP_SCTRL_SCSYSSTAT_OFFSET (0x4)
#define HI_AP_SCTRL_SCITMCTRL_OFFSET (0x8)
#define HI_AP_SCTRL_SCIMSTAT_OFFSET (0xC)
#define HI_AP_SCTRL_SCXTALCTRL_OFFSET (0x10)
#define HI_AP_SCTRL_SCXTALTIMEOUT0_OFFSET (0x14)
#define HI_AP_SCTRL_SCXTALTIMEOUT1_OFFSET (0x18)
#define HI_AP_SCTRL_SCXTALSTAT_OFFSET (0x1C)
#define HI_AP_SCTRL_SCPPLLCTRL0_OFFSET (0x20)
#define HI_AP_SCTRL_SCPPLLCTRL1_OFFSET (0x24)
#define HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET (0x28)
#define HI_AP_SCTRL_SCPPLLSTAT_OFFSET (0x2C)
#define HI_AP_SCTRL_SCPEREN0_OFFSET (0x30)
#define HI_AP_SCTRL_SCPERDIS0_OFFSET (0x34)
#define HI_AP_SCTRL_SCPERCLKEN0_OFFSET (0x38)
#define HI_AP_SCTRL_SCPERSTAT0_OFFSET (0x3C)
#define HI_AP_SCTRL_SCPEREN1_OFFSET (0x40)
#define HI_AP_SCTRL_SCPERDIS1_OFFSET (0x44)
#define HI_AP_SCTRL_SCPERCLKEN1_OFFSET (0x48)
#define HI_AP_SCTRL_SCPERSTAT1_OFFSET (0x4C)
#define HI_AP_SCTRL_SCPEREN2_OFFSET (0x50)
#define HI_AP_SCTRL_SCPERDIS2_OFFSET (0x54)
#define HI_AP_SCTRL_SCPERCLKEN2_OFFSET (0x58)
#define HI_AP_SCTRL_SCPERSTAT2_OFFSET (0x5C)
#define HI_AP_SCTRL_SCPERRSTEN0_OFFSET (0x80)
#define HI_AP_SCTRL_SCPERRSTDIS0_OFFSET (0x84)
#define HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET (0x88)
#define HI_AP_SCTRL_SCPERRSTEN1_OFFSET (0x8C)
#define HI_AP_SCTRL_SCPERRSTDIS1_OFFSET (0x90)
#define HI_AP_SCTRL_SCPERRSTSTAT1_OFFSET (0x94)
#define HI_AP_SCTRL_SCPERRSTEN2_OFFSET (0x98)
#define HI_AP_SCTRL_SCPERRSTDIS2_OFFSET (0x9C)
#define HI_AP_SCTRL_SCPERRSTSTAT2_OFFSET (0xA0)
#define HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET (0xA4)
#define HI_AP_SCTRL_SCISOEN_OFFSET (0xC0)
#define HI_AP_SCTRL_SCISODIS_OFFSET (0xC4)
#define HI_AP_SCTRL_SCISOSTAT_OFFSET (0xC8)
#define HI_AP_SCTRL_SCPWREN_OFFSET (0xD0)
#define HI_AP_SCTRL_SCPWRDIS_OFFSET (0xD4)
#define HI_AP_SCTRL_SCPWRSTAT_OFFSET (0xD8)
#define HI_AP_SCTRL_SCPWRACK_OFFSET (0xDC)
#define HI_AP_SCTRL_SCPERPWRDOWNTIME_OFFSET (0xE0)
#define HI_AP_SCTRL_SCPERPWRUPTIME_OFFSET (0xE4)
#define HI_AP_SCTRL_SCCLKDIV0_OFFSET (0x100)
#define HI_AP_SCTRL_SCCLKDIV1_OFFSET (0x104)
#define HI_AP_SCTRL_SCCLKDIV2_OFFSET (0x108)
#define HI_AP_SCTRL_SCCLKDIV3_OFFSET (0x10C)
#define HI_AP_SCTRL_SCCLKDIV4_OFFSET (0x110)
#define HI_AP_SCTRL_SCCLKDIV5_OFFSET (0x114)
#define HI_AP_SCTRL_SCPERCTRL0_OFFSET (0x200)
#define HI_AP_SCTRL_SCPERCTRL1_OFFSET (0x204)
#define HI_AP_SCTRL_SCPERCTRL2_OFFSET (0x208)
#define HI_AP_SCTRL_SCPERCTRL3_OFFSET (0x20C)
#define HI_AP_SCTRL_SCPERCTRL4_OFFSET (0x210)
#define HI_AP_SCTRL_SCPERCTRL5_OFFSET (0x214)
#define HI_AP_SCTRL_SCPERCTRL6_OFFSET (0x218)
#define HI_AP_SCTRL_SCPERSTATUS0_OFFSET (0x21C)
#define HI_AP_SCTRL_SCPERSTATUS1_OFFSET (0x220)
#define HI_AP_SCTRL_SCPERSTATUS2_OFFSET (0x224)
#define HI_AP_SCTRL_SCPERSTATUS3_OFFSET (0x228)
#define HI_AP_SCTRL_SCPERSTATUS4_OFFSET (0x22C)
#define HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET (0x300)
#define HI_AP_SCTRL_SCMRBBUSYSTAT_OFFSET (0x304)
#define HI_AP_SCTRL_SCSWADDR_OFFSET (0x308)
#define HI_AP_SCTRL_SCDDRADDR_OFFSET (0x30C)
#define HI_AP_SCTRL_SCDDRDATA_OFFSET (0x310)
#define HI_AP_SCTRL_SCBAKDATA0_OFFSET (0x314)
#define HI_AP_SCTRL_SCBAKDATA1_OFFSET (0x318)
#define HI_AP_SCTRL_SCBAKDATA2_OFFSET (0x31C)
#define HI_AP_SCTRL_SCBAKDATA3_OFFSET (0x320)
#define HI_AP_SCTRL_SCBAKDATA4_OFFSET (0x324)
#define HI_AP_SCTRL_SCBAKDATA5_OFFSET (0x328)
#define HI_AP_SCTRL_SCBAKDATA6_OFFSET (0x32C)
#define HI_AP_SCTRL_SCBAKDATA7_OFFSET (0x330)
#define HI_AP_SCTRL_SCBAKDATA8_OFFSET (0x334)
#define HI_AP_SCTRL_SCBAKDATA9_OFFSET (0x338)
#define HI_AP_SCTRL_SCBAKDATA10_OFFSET (0x33C)
#define HI_AP_SCTRL_SCBAKDATA11_OFFSET (0x340)
#define HI_AP_SCTRL_SCBAKDATA12_OFFSET (0x344)
#define HI_AP_SCTRL_SCBAKDATA13_OFFSET (0x348)
#define HI_AP_SCTRL_SCBAKDATA14_OFFSET (0x34C)
#define HI_AP_SCTRL_SCBAKDATA15_OFFSET (0x350)
#define HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET (0x450)
#define HI_AP_SCTRL_SCINT_MASK_OFFSET (0x454)
#define HI_AP_SCTRL_SCINT_STAT_OFFSET (0x458)
#define HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET (0x45C)
#define HI_AP_SCTRL_SCLPM3WFI_INT_CLR_OFFSET (0x460)
#define HI_AP_SCTRL_SCMALIBYPCFG_OFFSET (0x48C)
#define HI_AP_SCTRL_SCLPM3CLKEN_OFFSET (0x500)
#define HI_AP_SCTRL_SCLPM3RSTEN_OFFSET (0x504)
#define HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET (0x508)
#define HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET (0x50C)
#define HI_AP_SCTRL_SCLPM3CTRL_OFFSET (0x510)
#define HI_AP_SCTRL_SCLPM3STAT_OFFSET (0x514)
#define HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET (0x518)
#define HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET (0x530)
#define HI_AP_SCTRL_SCBBPDRXSTAT1_OFFSET (0x534)
#define HI_AP_SCTRL_SCBBPDRXSTAT2_OFFSET (0x538)
#define HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET (0x550)
#define HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET (0x554)
#define HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET (0x558)
#define HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET (0x55C)
#define HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET (0x560)
#define HI_AP_SCTRL_SCEVENT_STAT_OFFSET (0x564)
#define HI_AP_SCTRL_SCJTAG_SEL_OFFSET (0x800)
#define HI_AP_SCTRL_SCMODEM_KEY0_OFFSET (0x804)
#define HI_AP_SCTRL_SCMODEM_KEY1_OFFSET (0x808)
#define HI_AP_SCTRL_SCMODEM_KEY2_OFFSET (0x80C)
#define HI_AP_SCTRL_SCMODEM_KEY3_OFFSET (0x810)
#define HI_AP_SCTRL_SCCFG_DJTAG_OFFSET (0x814)
#define HI_AP_SCTRL_SCCP15_DISABLE_OFFSET (0x818)
#define HI_AP_SCTRL_SCCLKCNTSTAT_OFFSET (0x81C)
#define HI_AP_SCTRL_SCCLKCNTCFG_OFFSET (0x820)
#define HI_AP_SCTRL_SCCLKMONCTRL_OFFSET (0x824)
#define HI_AP_SCTRL_SCCLKMONINT_OFFSET (0x828)
#define HI_AP_SCTRL_SCCFG_ARM_DBGEN_OFFSET (0x82C)
#define HI_AP_SCTRL_SCARM_DBG_KEY0_OFFSET (0x830)
#define HI_AP_SCTRL_SCARM_DBG_KEY1_OFFSET (0x834)
#define HI_AP_SCTRL_SCARM_DBGEN_STAT_OFFSET (0x838)
#define HI_AP_SCTRL_SCEFUSECTRL_OFFSET (0x83C)
#define HI_AP_SCTRL_SCEFUSESEL_OFFSET (0x840)
#define HI_AP_SCTRL_SCSECURITYSTAT_OFFSET (0x844)
#define HI_AP_SCTRL_SCCHIP_ID0_OFFSET (0x848)
#define HI_AP_SCTRL_SCCHIP_ID1_OFFSET (0x84C)
#define HI_AP_SCTRL_SCSOCID0_OFFSET (0xE00)
typedef union
{
    struct
    {
        unsigned int modectrl : 3;
        unsigned int modestatus : 4;
        unsigned int reserved_1 : 1;
        unsigned int timeforcehigh : 1;
        unsigned int timeren0sel : 1;
        unsigned int timeren0ov : 1;
        unsigned int timeren1sel : 1;
        unsigned int timeren1ov : 1;
        unsigned int timeren2sel : 1;
        unsigned int timeren2ov : 1;
        unsigned int timeren3sel : 1;
        unsigned int timeren3ov : 1;
        unsigned int timeren4sel : 1;
        unsigned int timeren4ov : 1;
        unsigned int timeren5sel : 1;
        unsigned int timeren5ov : 1;
        unsigned int timeren6sel : 1;
        unsigned int timeren6ov : 1;
        unsigned int timeren7sel : 1;
        unsigned int timeren7ov : 1;
        unsigned int deepsleepen : 1;
        unsigned int reserved_0 : 6;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCTRL_T;
typedef union
{
    struct
    {
        unsigned int reset_source : 11;
        unsigned int reserved : 21;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCSYSSTAT_T;
typedef union
{
    struct
    {
        unsigned int itmden : 1;
        unsigned int itmdctrl : 3;
        unsigned int reserved_1 : 3;
        unsigned int inmdtype : 1;
        unsigned int reserved_0 : 24;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCITMCTRL_T;
typedef union
{
    struct
    {
        unsigned int itmdstat : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCIMSTAT_T;
typedef union
{
    struct
    {
        unsigned int tcxopresel_apb : 1;
        unsigned int tcxohardcon_bypass : 1;
        unsigned int tcxosel_apb : 1;
        unsigned int tcxosoft_apb : 1;
        unsigned int defau_tcxo : 1;
        unsigned int tcxofast_ctrl0 : 1;
        unsigned int tcxofast_ctrl1 : 1;
        unsigned int ctrlen1_apb : 1;
        unsigned int ctrlsel1_apb : 1;
        unsigned int ctrlen0_apb : 1;
        unsigned int ctrlsel0_apb : 1;
        unsigned int timeout_bypass0 : 1;
        unsigned int timeout_bypass1 : 1;
        unsigned int tcxoseq_bypass : 1;
        unsigned int tcxoseq0_time : 5;
        unsigned int tcxoseq1_time : 5;
        unsigned int reserved : 8;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCXTALCTRL_T;
typedef union
{
    struct
    {
        unsigned int timeoutcnt0_apb : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCXTALTIMEOUT0_T;
typedef union
{
    struct
    {
        unsigned int timeoutcnt1_apb : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCXTALTIMEOUT1_T;
typedef union
{
    struct
    {
        unsigned int tcxo_en0 : 1;
        unsigned int tcxo_en1 : 1;
        unsigned int tcxo_timeout1 : 1;
        unsigned int tcxo_timeout0 : 1;
        unsigned int sysclk_en1 : 1;
        unsigned int sysclk_en0 : 1;
        unsigned int sysclk_sel : 1;
        unsigned int clkgt_ctrl0 : 1;
        unsigned int clkgt_ctrl1 : 1;
        unsigned int clkgt_ctrl : 1;
        unsigned int abbbuf_en0 : 1;
        unsigned int abbbuf_en1 : 1;
        unsigned int tcxoseq_finish0 : 1;
        unsigned int tcxoseq_finish1 : 1;
        unsigned int reserved : 18;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCXTALSTAT_T;
typedef union
{
    struct
    {
        unsigned int ppll0_en : 1;
        unsigned int ppll0_bp : 1;
        unsigned int ppll0_refdiv : 6;
        unsigned int ppll0_fbdiv : 12;
        unsigned int ppll0_postdiv1 : 3;
        unsigned int ppll0_postdiv2 : 3;
        unsigned int reserved : 6;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPPLLCTRL0_T;
typedef union
{
    struct
    {
        unsigned int ppll0_fracdiv : 24;
        unsigned int ppll0_int_mod : 1;
        unsigned int ppll0_cfg_vld : 1;
        unsigned int gt_clk_ppll0 : 1;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPPLLCTRL1_T;
typedef union
{
    struct
    {
        unsigned int ppll0_ssc_reset : 1;
        unsigned int ppll0_ssc_disable : 1;
        unsigned int ppll0_ssc_downspread : 1;
        unsigned int ppll0_ssc_spread : 3;
        unsigned int ppll0_ssc_divval : 4;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPPLLSSCCTRL_T;
typedef union
{
    struct
    {
        unsigned int pllstat : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPPLLSTAT_T;
typedef union
{
    struct
    {
        unsigned int reserved : 1;
        unsigned int gt_pclk_rtc : 1;
        unsigned int gt_pclk_rtc1 : 1;
        unsigned int gt_pclk_timer0 : 1;
        unsigned int gt_clk_timer0 : 1;
        unsigned int gt_pclk_timer1 : 1;
        unsigned int gt_clk_timer1 : 1;
        unsigned int gt_pclk_timer2 : 1;
        unsigned int gt_clk_timer2 : 1;
        unsigned int gt_pclk_timer3 : 1;
        unsigned int gt_clk_timer3 : 1;
        unsigned int gt_pclk_ao_gpio0 : 1;
        unsigned int gt_pclk_ao_gpio1 : 1;
        unsigned int gt_pclk_ao_gpio2 : 1;
        unsigned int gt_pclk_ao_gpio3 : 1;
        unsigned int gt_pclk_ao_ioc : 1;
        unsigned int gt_clk_out0 : 1;
        unsigned int gt_clk_out1 : 1;
        unsigned int gt_clk_jtag_auth : 1;
        unsigned int gt_pclk_syscnt : 1;
        unsigned int gt_clk_syscnt : 1;
        unsigned int gt_pclk_ao_gpio4 : 1;
        unsigned int gt_pclk_ao_gpio5 : 1;
        unsigned int gt_clk_sci0 : 1;
        unsigned int gt_clk_sci1 : 1;
        unsigned int gt_clk_memrep : 1;
        unsigned int gt_clk_asp_subsys : 1;
        unsigned int gt_clk_asp_tcxo : 1;
        unsigned int gt_clk_bbpdrx : 1;
        unsigned int gt_clk_aobus : 1;
        unsigned int gt_pclk_efusec : 1;
        unsigned int gt_clk_ppll0_sscg : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPEREN0_T;
typedef union
{
    struct
    {
        unsigned int reserved : 1;
        unsigned int gt_pclk_rtc : 1;
        unsigned int gt_pclk_rtc1 : 1;
        unsigned int gt_pclk_timer0 : 1;
        unsigned int gt_clk_timer0 : 1;
        unsigned int gt_pclk_timer1 : 1;
        unsigned int gt_clk_timer1 : 1;
        unsigned int gt_pclk_timer2 : 1;
        unsigned int gt_clk_timer2 : 1;
        unsigned int gt_pclk_timer3 : 1;
        unsigned int gt_clk_timer3 : 1;
        unsigned int gt_pclk_ao_gpio0 : 1;
        unsigned int gt_pclk_ao_gpio1 : 1;
        unsigned int gt_pclk_ao_gpio2 : 1;
        unsigned int gt_pclk_ao_gpio3 : 1;
        unsigned int gt_pclk_ao_ioc : 1;
        unsigned int gt_clk_out0 : 1;
        unsigned int gt_clk_out1 : 1;
        unsigned int gt_clk_jtag_auth : 1;
        unsigned int gt_pclk_syscnt : 1;
        unsigned int gt_clk_syscnt : 1;
        unsigned int gt_pclk_ao_gpio4 : 1;
        unsigned int gt_pclk_ao_gpio5 : 1;
        unsigned int gt_clk_sci0 : 1;
        unsigned int gt_clk_sci1 : 1;
        unsigned int gt_clk_memrep : 1;
        unsigned int gt_clk_asp_subsys : 1;
        unsigned int gt_clk_asp_tcxo : 1;
        unsigned int gt_clk_bbpdrx : 1;
        unsigned int gt_clk_aobus : 1;
        unsigned int gt_pclk_efusec : 1;
        unsigned int gt_clk_ppll0_sscg : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERDIS0_T;
typedef union
{
    struct
    {
        unsigned int reserved : 1;
        unsigned int gt_pclk_rtc : 1;
        unsigned int gt_pclk_rtc1 : 1;
        unsigned int gt_pclk_timer0 : 1;
        unsigned int gt_clk_timer0 : 1;
        unsigned int gt_pclk_timer1 : 1;
        unsigned int gt_clk_timer1 : 1;
        unsigned int gt_pclk_timer2 : 1;
        unsigned int gt_clk_timer2 : 1;
        unsigned int gt_pclk_timer3 : 1;
        unsigned int gt_clk_timer3 : 1;
        unsigned int gt_pclk_ao_gpio0 : 1;
        unsigned int gt_pclk_ao_gpio1 : 1;
        unsigned int gt_pclk_ao_gpio2 : 1;
        unsigned int gt_pclk_ao_gpio3 : 1;
        unsigned int gt_pclk_ao_ioc : 1;
        unsigned int gt_clk_out0 : 1;
        unsigned int gt_clk_out1 : 1;
        unsigned int gt_clk_jtag_auth : 1;
        unsigned int gt_pclk_syscnt : 1;
        unsigned int gt_clk_syscnt : 1;
        unsigned int gt_pclk_ao_gpio4 : 1;
        unsigned int gt_pclk_ao_gpio5 : 1;
        unsigned int gt_clk_sci0 : 1;
        unsigned int gt_clk_sci1 : 1;
        unsigned int gt_clk_memrep : 1;
        unsigned int gt_clk_asp_subsys : 1;
        unsigned int gt_clk_asp_tcxo : 1;
        unsigned int gt_clk_bbpdrx : 1;
        unsigned int gt_clk_aobus : 1;
        unsigned int gt_pclk_efusec : 1;
        unsigned int gt_clk_ppll0_sscg : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCLKEN0_T;
typedef union
{
    struct
    {
        unsigned int gt_clk_ao_cc : 1;
        unsigned int gt_pclk_rtc : 1;
        unsigned int gt_pclk_rtc1 : 1;
        unsigned int gt_pclk_timer0 : 1;
        unsigned int gt_clk_timer0 : 1;
        unsigned int gt_pclk_timer1 : 1;
        unsigned int gt_clk_timer1 : 1;
        unsigned int gt_pclk_timer2 : 1;
        unsigned int gt_clk_timer2 : 1;
        unsigned int gt_pclk_timer3 : 1;
        unsigned int gt_clk_timer3 : 1;
        unsigned int gt_pclk_ao_gpio0 : 1;
        unsigned int gt_pclk_ao_gpio1 : 1;
        unsigned int gt_pclk_ao_gpio2 : 1;
        unsigned int gt_pclk_ao_gpio3 : 1;
        unsigned int gt_pclk_ao_ioc : 1;
        unsigned int gt_clk_out0 : 1;
        unsigned int gt_clk_out1 : 1;
        unsigned int gt_clk_jtag_auth : 1;
        unsigned int gt_pclk_syscnt : 1;
        unsigned int gt_clk_syscnt : 1;
        unsigned int gt_pclk_ao_gpio4 : 1;
        unsigned int gt_pclk_ao_gpio5 : 1;
        unsigned int gt_clk_sci0 : 1;
        unsigned int gt_clk_sci1 : 1;
        unsigned int gt_clk_memrep : 1;
        unsigned int gt_clk_asp_subsys : 1;
        unsigned int gt_clk_asp_tcxo : 1;
        unsigned int gt_clk_bbpdrx : 1;
        unsigned int gt_clk_aobus : 1;
        unsigned int gt_pclk_efusec : 1;
        unsigned int gt_clk_ppll0_sscg : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERSTAT0_T;
typedef union
{
    struct
    {
        unsigned int gt_clk_asp_dw_axi : 1;
        unsigned int gt_clk_asp_x2h : 1;
        unsigned int gt_clk_asp_h2p : 1;
        unsigned int gt_asp_cfg : 1;
        unsigned int gt_clk_bbpdrx_oth : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPEREN1_T;
typedef union
{
    struct
    {
        unsigned int gt_clk_asp_dw_axi : 1;
        unsigned int gt_clk_asp_x2h : 1;
        unsigned int gt_clk_asp_h2p : 1;
        unsigned int gt_asp_cfg : 1;
        unsigned int gt_clk_bbpdrx_oth : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERDIS1_T;
typedef union
{
    struct
    {
        unsigned int gt_clk_asp_dw_axi : 1;
        unsigned int gt_clk_asp_x2h : 1;
        unsigned int gt_clk_asp_h2p : 1;
        unsigned int gt_asp_cfg : 1;
        unsigned int gt_clk_bbpdrx_oth : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCLKEN1_T;
typedef union
{
    struct
    {
        unsigned int gt_clk_asp_dw_axi : 1;
        unsigned int gt_clk_asp_x2h : 1;
        unsigned int gt_clk_asp_h2p : 1;
        unsigned int gt_asp_cfg : 1;
        unsigned int gt_clk_bbpdrx_oth : 1;
        unsigned int reserved : 22;
        unsigned int swdone_clk_asp_subsys_div : 1;
        unsigned int swdone_clk_sci_div : 1;
        unsigned int swdone_clk_aobus_div : 1;
        unsigned int aobusclksw2sys : 1;
        unsigned int aobusclksw2pll : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERSTAT1_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPEREN2_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERDIS2_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCLKEN2_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERSTAT2_T;
typedef union
{
    struct
    {
        unsigned int ip_rst_ao_cc : 1;
        unsigned int ip_rst_rtc : 1;
        unsigned int ip_rst_rtc1 : 1;
        unsigned int ip_rst_timer0 : 1;
        unsigned int ip_rst_timer1 : 1;
        unsigned int ip_rst_timer2 : 1;
        unsigned int ip_rst_timer3 : 1;
        unsigned int rst_asp_cfg : 1;
        unsigned int rst_asp_dw_axi : 1;
        unsigned int rst_asp_x2h : 1;
        unsigned int rst_asp_h2p : 1;
        unsigned int ip_rst_ao_gpio0 : 1;
        unsigned int ip_rst_ao_gpio1 : 1;
        unsigned int ip_rst_ao_gpio2 : 1;
        unsigned int ip_rst_ao_gpio3 : 1;
        unsigned int ip_rst_ao_gpio4 : 1;
        unsigned int ip_rst_ao_gpio5 : 1;
        unsigned int reserved_3 : 1;
        unsigned int ip_rst_ao_ioc : 1;
        unsigned int ip_prst_syscnt : 1;
        unsigned int ip_rst_syscnt : 1;
        unsigned int reserved_2 : 2;
        unsigned int ip_rst_sci0 : 1;
        unsigned int ip_rst_sci1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int ip_rst_asp_subsys : 1;
        unsigned int ip_rst_bbpdrx : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_rst_aobus : 1;
        unsigned int sc_rst_src_clr : 1;
        unsigned int sc_pmurst_ctrl : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERRSTEN0_T;
typedef union
{
    struct
    {
        unsigned int ip_rst_ao_cc : 1;
        unsigned int ip_rst_rtc : 1;
        unsigned int ip_rst_rtc1 : 1;
        unsigned int ip_rst_timer0 : 1;
        unsigned int ip_rst_timer1 : 1;
        unsigned int ip_rst_timer2 : 1;
        unsigned int ip_rst_timer3 : 1;
        unsigned int rst_asp_cfg : 1;
        unsigned int rst_asp_dw_axi : 1;
        unsigned int rst_asp_x2h : 1;
        unsigned int rst_asp_h2p : 1;
        unsigned int ip_rst_ao_gpio0 : 1;
        unsigned int ip_rst_ao_gpio1 : 1;
        unsigned int ip_rst_ao_gpio2 : 1;
        unsigned int ip_rst_ao_gpio3 : 1;
        unsigned int ip_rst_ao_gpio4 : 1;
        unsigned int ip_rst_ao_gpio5 : 1;
        unsigned int reserved_3 : 1;
        unsigned int ip_rst_ao_ioc : 1;
        unsigned int ip_prst_syscnt : 1;
        unsigned int ip_rst_syscnt : 1;
        unsigned int reserved_2 : 2;
        unsigned int ip_rst_sci0 : 1;
        unsigned int ip_rst_sci1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int ip_rst_asp_subsys : 1;
        unsigned int ip_rst_bbpdrx : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_rst_aobus : 1;
        unsigned int sc_rst_src_clr : 1;
        unsigned int sc_pmurst_ctrl : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERRSTDIS0_T;
typedef union
{
    struct
    {
        unsigned int ip_rst_ao_cc : 1;
        unsigned int ip_rst_rtc : 1;
        unsigned int ip_rst_rtc1 : 1;
        unsigned int ip_rst_timer0 : 1;
        unsigned int ip_rst_timer1 : 1;
        unsigned int ip_rst_timer2 : 1;
        unsigned int ip_rst_timer3 : 1;
        unsigned int rst_asp_cfg : 1;
        unsigned int rst_asp_dw_axi : 1;
        unsigned int rst_asp_x2h : 1;
        unsigned int rst_asp_h2p : 1;
        unsigned int ip_rst_ao_gpio0 : 1;
        unsigned int ip_rst_ao_gpio1 : 1;
        unsigned int ip_rst_ao_gpio2 : 1;
        unsigned int ip_rst_ao_gpio3 : 1;
        unsigned int ip_rst_ao_gpio4 : 1;
        unsigned int ip_rst_ao_gpio5 : 1;
        unsigned int reserved_3 : 1;
        unsigned int ip_rst_ao_ioc : 1;
        unsigned int ip_prst_syscnt : 1;
        unsigned int ip_rst_syscnt : 1;
        unsigned int reserved_2 : 2;
        unsigned int ip_rst_sci0 : 1;
        unsigned int ip_rst_sci1 : 1;
        unsigned int reserved_1 : 1;
        unsigned int ip_rst_asp_subsys : 1;
        unsigned int ip_rst_bbpdrx : 1;
        unsigned int reserved_0 : 1;
        unsigned int ip_rst_aobus : 1;
        unsigned int sc_rst_src_clr : 1;
        unsigned int sc_pmurst_ctrl : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERRSTSTAT0_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERRSTEN1_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERRSTDIS1_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERRSTSTAT1_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERRSTEN2_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERRSTDIS2_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERRSTSTAT2_T;
typedef union
{
    struct
    {
        unsigned int rst_gt_rtc_bypass : 1;
        unsigned int rst_gt_rtc1_bypass : 1;
        unsigned int rst_gt_timer0_bypass : 1;
        unsigned int rst_gt_timer1_bypass : 1;
        unsigned int rst_gt_timer2_bypass : 1;
        unsigned int rst_gt_timer3_bypass : 1;
        unsigned int rst_gt_gpio0_bypass : 1;
        unsigned int rst_gt_gpio1_bypass : 1;
        unsigned int rst_gt_gpio2_bypass : 1;
        unsigned int rst_gt_gpio3_bypass : 1;
        unsigned int rst_gt_gpio4_bypass : 1;
        unsigned int rst_gt_gpio5_bypass : 1;
        unsigned int rst_gt_ioc_bypass : 1;
        unsigned int rst_gt_syscnt_bypass : 1;
        unsigned int rst_gt_sci0_bypass : 1;
        unsigned int rst_gt_sci1_bypass : 1;
        unsigned int rst_gt_bbpdrx_bypass : 1;
        unsigned int rst_gt_efusec_bypass : 1;
        unsigned int reserved : 14;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCIPCLKRSTBUS_T;
typedef union
{
    struct
    {
        unsigned int audioisoen : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCISOEN_T;
typedef union
{
    struct
    {
        unsigned int audioisoen : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCISODIS_T;
typedef union
{
    struct
    {
        unsigned int audioisoen : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCISOSTAT_T;
typedef union
{
    struct
    {
        unsigned int audiopwren : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPWREN_T;
typedef union
{
    struct
    {
        unsigned int audiopwren : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPWRDIS_T;
typedef union
{
    struct
    {
        unsigned int audiopwrstat : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPWRSTAT_T;
typedef union
{
    struct
    {
        unsigned int audiopwrack : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPWRACK_T;
typedef union
{
    struct
    {
        unsigned int peri_pwr_down_time : 25;
        unsigned int reserved : 7;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERPWRDOWNTIME_T;
typedef union
{
    struct
    {
        unsigned int peri_pwr_up_time : 25;
        unsigned int reserved : 7;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERPWRUPTIME_T;
typedef union
{
    struct
    {
        unsigned int sc_div_asp_subsys : 3;
        unsigned int sc_div_hifidsp : 6;
        unsigned int sc_div_sci : 2;
        unsigned int reserved : 4;
        unsigned int extclk_en : 1;
        unsigned int clkdivmasken : 16;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKDIV0_T;
typedef union
{
    struct
    {
        unsigned int sc_div_aobus : 6;
        unsigned int div_clkout0_tcxo : 3;
        unsigned int div_clkout1_tcxo : 3;
        unsigned int sel_clkout0 : 2;
        unsigned int sel_clkout1 : 2;
        unsigned int clkdivmasken : 16;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKDIV1_T;
typedef union
{
    struct
    {
        unsigned int gt_clk_asp_subsys : 1;
        unsigned int gt_hifidsp_clk_div : 1;
        unsigned int gt_clk_sci : 1;
        unsigned int gt_clk_aobus : 1;
        unsigned int gt_asp_hclk_div : 1;
        unsigned int reserved_1 : 3;
        unsigned int sc_div_asp_hclk : 2;
        unsigned int reserved_0 : 6;
        unsigned int clkdivmasken : 16;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKDIV2_T;
typedef union
{
    struct
    {
        unsigned int reserved : 16;
        unsigned int clkdivmasken : 16;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKDIV3_T;
typedef union
{
    struct
    {
        unsigned int reserved : 16;
        unsigned int clkdivmasken : 16;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKDIV4_T;
typedef union
{
    struct
    {
        unsigned int reserved : 16;
        unsigned int clkdivmasken : 16;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKDIV5_T;
typedef union
{
    struct
    {
        unsigned int efusec_mem_ctrl : 16;
        unsigned int efuse_remap : 1;
        unsigned int reserved : 15;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCTRL0_T;
typedef union
{
    struct
    {
        unsigned int reserved : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCTRL1_T;
typedef union
{
    struct
    {
        unsigned int repair_disable : 20;
        unsigned int reserved_1 : 4;
        unsigned int jtaq_to_sdcard : 1;
        unsigned int reserved_0 : 7;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCTRL2_T;
typedef union
{
    struct
    {
        unsigned int reserved_1 : 1;
        unsigned int reset_memrep_msk : 1;
        unsigned int repair_iddq : 1;
        unsigned int repair_frm_sram : 1;
        unsigned int repair_frm_efu : 1;
        unsigned int dram_pwr_ctl : 3;
        unsigned int efusec_timeout_bypass : 1;
        unsigned int bbdrx_timeout_bypass : 1;
        unsigned int sleep_mode_cfgbus_bypass : 1;
        unsigned int sleep_mode_lpmcu_bypass : 1;
        unsigned int sleep_mode_iomcu_bypass : 1;
        unsigned int sleep_mode_aobus_bypass : 1;
        unsigned int bbp_clk_en : 1;
        unsigned int reserved_0 : 17;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCTRL3_T;
typedef union
{
    struct
    {
        unsigned int ddr_ret_en : 2;
        unsigned int reserved : 30;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCTRL4_T;
typedef union
{
    struct
    {
        unsigned int usim0_io_sel18 : 1;
        unsigned int usim1_io_sel18 : 1;
        unsigned int sdcard_io_sel18 : 1;
        unsigned int tp_sel : 3;
        unsigned int tcxo_mode : 1;
        unsigned int reserved : 25;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCTRL5_T;
typedef union
{
    struct
    {
        unsigned int peri_io_ret : 1;
        unsigned int reserved_1 : 3;
        unsigned int peri_bootio_ret : 1;
        unsigned int peri_bootio_ret_mode : 1;
        unsigned int reserved_0 : 26;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERCTRL6_T;
typedef union
{
    struct
    {
        unsigned int asp_dwaxi_dlock_wr : 1;
        unsigned int asp_dwaxi_dlock_id : 4;
        unsigned int asp_dwaxi_dlock_slv : 3;
        unsigned int asp_dwaxi_dlock_mst : 2;
        unsigned int sys_pw_stat : 4;
        unsigned int tcxoseq_stat0 : 3;
        unsigned int tcxoseq_stat1 : 3;
        unsigned int tp_a3_grp : 9;
        unsigned int tp_a4_grp0 : 2;
        unsigned int tp_a4_grp1 : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERSTATUS0_T;
typedef union
{
    struct
    {
        unsigned int err_flag : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERSTATUS1_T;
typedef union
{
    struct
    {
        unsigned int peri_stat2 : 10;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERSTATUS2_T;
typedef union
{
    struct
    {
        unsigned int efusec_timeout_dbg_info : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERSTATUS3_T;
typedef union
{
    struct
    {
        unsigned int bbdrx_timeout_dbg_info : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCPERSTATUS4_T;
typedef union
{
    struct
    {
        unsigned int deepsleeped : 1;
        unsigned int reserved_1 : 3;
        unsigned int sleeped : 1;
        unsigned int reserved_0 : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCDEEPSLEEPED_T;
typedef union
{
    struct
    {
        unsigned int mrb_efuse_busy : 20;
        unsigned int reserved : 12;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCMRBBUSYSTAT_T;
typedef union
{
    struct
    {
        unsigned int swaddr : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCSWADDR_T;
typedef union
{
    struct
    {
        unsigned int ddrtrainaddr : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCDDRADDR_T;
typedef union
{
    struct
    {
        unsigned int ddrtraindata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCDDRDATA_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA0_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA1_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA2_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA3_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA4_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA5_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA6_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA7_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA8_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA9_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA10_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA11_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA12_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA13_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA14_T;
typedef union
{
    struct
    {
        unsigned int bakdata : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBAKDATA15_T;
typedef union
{
    struct
    {
        unsigned int int_wakeup_sys : 1;
        unsigned int drx0_int : 1;
        unsigned int drx1_int : 1;
        unsigned int notdrx_int : 1;
        unsigned int reserved : 28;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCINT_GATHER_STAT_T;
typedef union
{
    struct
    {
        unsigned int gpio_22_int : 1;
        unsigned int gpio_23_int : 1;
        unsigned int gpio_24_int : 1;
        unsigned int gpio_25_int : 1;
        unsigned int gpio_26_int : 1;
        unsigned int rtc_int : 1;
        unsigned int rtc1_int : 1;
        unsigned int timer0_int : 1;
        unsigned int timer1_int : 1;
        unsigned int timer2_int : 1;
        unsigned int timer3_int : 1;
        unsigned int timer4_int : 1;
        unsigned int timer5_int : 1;
        unsigned int timer6_int : 1;
        unsigned int timer7_int : 1;
        unsigned int gic_irq_int0 : 1;
        unsigned int gic_irq_int1 : 1;
        unsigned int gic_fiq_int2 : 1;
        unsigned int gic_fiq_int3 : 1;
        unsigned int lpm3_int : 1;
        unsigned int iom3_int : 1;
        unsigned int asp_ipc_arm_int : 1;
        unsigned int drx0_int : 1;
        unsigned int drx1_int : 1;
        unsigned int drx2_int : 1;
        unsigned int drx3_int : 1;
        unsigned int drx4_int : 1;
        unsigned int gpio_27_int : 1;
        unsigned int gpio_asp_int : 1;
        unsigned int gpio_asp_int_sc : 1;
        unsigned int intr_asp_watchdog : 1;
        unsigned int lpm3_wfi_int : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCINT_MASK_T;
typedef union
{
    struct
    {
        unsigned int gpio_22_int : 1;
        unsigned int gpio_23_int : 1;
        unsigned int gpio_24_int : 1;
        unsigned int gpio_25_int : 1;
        unsigned int gpio_26_int : 1;
        unsigned int rtc_int : 1;
        unsigned int rtc1_int : 1;
        unsigned int timer0_int : 1;
        unsigned int timer1_int : 1;
        unsigned int timer2_int : 1;
        unsigned int timer3_int : 1;
        unsigned int timer4_int : 1;
        unsigned int timer5_int : 1;
        unsigned int timer6_int : 1;
        unsigned int timer7_int : 1;
        unsigned int gic_int0 : 1;
        unsigned int gic_int1 : 1;
        unsigned int gic_int2 : 1;
        unsigned int gic_int3 : 1;
        unsigned int lpm3_int : 1;
        unsigned int iom3_int : 1;
        unsigned int asp_ipc_arm_int : 1;
        unsigned int drx0_int : 1;
        unsigned int drx1_int : 1;
        unsigned int drx2_int : 1;
        unsigned int drx3_int : 1;
        unsigned int drx4_int : 1;
        unsigned int gpio_27_int : 1;
        unsigned int intr_asp_watchdog : 1;
        unsigned int gpio_asp_int : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCINT_STAT_T;
typedef union
{
    struct
    {
        unsigned int drx0_int : 1;
        unsigned int drx1_int : 1;
        unsigned int drx2_int : 1;
        unsigned int drx3_int : 1;
        unsigned int drx4_int : 1;
        unsigned int gpio_asp_int : 1;
        unsigned int reserved : 26;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCDRX_INT_CFG_T;
typedef union
{
    struct
    {
        unsigned int lpm3_wfi_int_clr : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCLPM3WFI_INT_CLR_T;
typedef union
{
    struct
    {
        unsigned int mali_dbgack_byp : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCMALIBYPCFG_T;
typedef union
{
    struct
    {
        unsigned int dapclkoff_sys_n : 1;
        unsigned int reserved_1 : 1;
        unsigned int rom_clk_clkoff_sys_n : 1;
        unsigned int ram_clk_clkoff_sys_n : 1;
        unsigned int reserved_0 : 1;
        unsigned int ddrc_clk_clkoff_sys_n : 1;
        unsigned int tsen_clk_clkoff_sys_n : 1;
        unsigned int pmc_clk_clkoff_sys_n : 1;
        unsigned int uart_clk_clkoff_sys_n : 1;
        unsigned int i2c_clk_clkoff_sys_n : 1;
        unsigned int ssi_clk_clkoff_sys_n : 1;
        unsigned int pcrg_clk_clkoff_sys_n : 1;
        unsigned int nandc_clk_clkoff_sys_n : 1;
        unsigned int wdog_clk_clkoff_sys_n : 1;
        unsigned int tim_clk_clkoff_sys_n : 1;
        unsigned int cssys_clk_clkoff_sys_n : 1;
        unsigned int clkdivmasken : 16;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCLPM3CLKEN_T;
typedef union
{
    struct
    {
        unsigned int rst_software_req : 1;
        unsigned int coresight_soft_rst_req : 1;
        unsigned int reserved_2 : 1;
        unsigned int rom_soft_rst_req : 1;
        unsigned int ram_soft_rst_req : 1;
        unsigned int reserved_1 : 1;
        unsigned int ddrc_soft_rst_req : 1;
        unsigned int tsen_soft_rst_req : 1;
        unsigned int pmc_soft_rst_req : 1;
        unsigned int uart_soft_rst_req : 1;
        unsigned int i2c_soft_rst_req : 1;
        unsigned int ssi_soft_rst_req : 1;
        unsigned int pcrg_soft_rst_req : 1;
        unsigned int nandc_soft_rst_req : 1;
        unsigned int wdog_soft_rst_req : 1;
        unsigned int tim_soft_rst_req : 1;
        unsigned int cssys_soft_rst_req : 1;
        unsigned int reserved_0 : 15;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCLPM3RSTEN_T;
typedef union
{
    struct
    {
        unsigned int rst_software_req : 1;
        unsigned int coresight_soft_rst_req : 1;
        unsigned int bus_soft_rst_req : 1;
        unsigned int rom_soft_rst_req : 1;
        unsigned int ram_soft_rst_req : 1;
        unsigned int aon_soft_rst_req : 1;
        unsigned int ddrc_soft_rst_req : 1;
        unsigned int tsen_soft_rst_req : 1;
        unsigned int pmc_soft_rst_req : 1;
        unsigned int uart_soft_rst_req : 1;
        unsigned int i2c_soft_rst_req : 1;
        unsigned int ssi_soft_rst_req : 1;
        unsigned int pcrg_soft_rst_req : 1;
        unsigned int nandc_soft_rst_req : 1;
        unsigned int wdog_soft_rst_req : 1;
        unsigned int tim_soft_rst_req : 1;
        unsigned int cssys_soft_rst_req : 1;
        unsigned int reserved : 15;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCLPM3RSTDIS_T;
typedef union
{
    struct
    {
        unsigned int rst_software_req : 1;
        unsigned int coresight_soft_rst_req : 1;
        unsigned int bus_soft_rst_req : 1;
        unsigned int rom_soft_rst_req : 1;
        unsigned int ram_soft_rst_req : 1;
        unsigned int aon_soft_rst_req : 1;
        unsigned int ddrc_soft_rst_req : 1;
        unsigned int tsen_soft_rst_req : 1;
        unsigned int pmc_soft_rst_req : 1;
        unsigned int uart_soft_rst_req : 1;
        unsigned int i2c_soft_rst_req : 1;
        unsigned int ssi_soft_rst_req : 1;
        unsigned int pcrg_soft_rst_req : 1;
        unsigned int nandc_soft_rst_req : 1;
        unsigned int wdog_soft_rst_req : 1;
        unsigned int tim_soft_rst_req : 1;
        unsigned int cssys_soft_rst_req : 1;
        unsigned int reserved : 15;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCLPM3RSTSTAT_T;
typedef union
{
    struct
    {
        unsigned int boot_remap_en : 1;
        unsigned int mpudisable : 1;
        unsigned int nmi_in : 1;
        unsigned int bus_div_clk_sel : 2;
        unsigned int sysresetreq_en : 1;
        unsigned int mem_ctrl_ema_lpram : 5;
        unsigned int lpm3idle_bypass : 1;
        unsigned int reserved_1 : 12;
        unsigned int reserved_0 : 8;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCLPM3CTRL_T;
typedef union
{
    struct
    {
        unsigned int sysresetreq_sign_out_stat : 1;
        unsigned int sleeping : 1;
        unsigned int lockup : 1;
        unsigned int halted : 1;
        unsigned int reserved : 28;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCLPM3STAT_T;
typedef union
{
    struct
    {
        unsigned int lpramctrl_sel : 1;
        unsigned int lpram0_mod : 2;
        unsigned int lpram1_mod : 2;
        unsigned int lpram2_mod : 2;
        unsigned int lpram3_mod : 2;
        unsigned int lpram0ctrl_soft : 3;
        unsigned int lpram1ctrl_soft : 3;
        unsigned int lpram2ctrl_soft : 3;
        unsigned int lpram3ctrl_soft : 3;
        unsigned int memrep_ram_mod : 2;
        unsigned int memrep_ramctrl_soft : 3;
        unsigned int reserved : 6;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCLPM3RAMCTRL_T;
typedef union
{
    struct
    {
        unsigned int g2_gdrx_depsleep_flag : 1;
        unsigned int g1_gdrx_depsleep_flag : 1;
        unsigned int wdrx_deepsleep_flag : 1;
        unsigned int reserved : 29;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBBPDRXSTAT0_T;
typedef union
{
    struct
    {
        unsigned int ldrx2dbg_abs_timer : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBBPDRXSTAT1_T;
typedef union
{
    struct
    {
        unsigned int ldrx2dbg_abs_timer : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCBBPDRXSTAT2_T;
typedef union
{
    struct
    {
        unsigned int a7_event_mask : 1;
        unsigned int a15_event_mask : 1;
        unsigned int iom3_event_mask : 1;
        unsigned int lpm3_event_mask : 1;
        unsigned int mcpu_event_mask : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCA7_EVENT_MASK_T;
typedef union
{
    struct
    {
        unsigned int a7_event_mask : 1;
        unsigned int a15_event_mask : 1;
        unsigned int iom3_event_mask : 1;
        unsigned int lpm3_event_mask : 1;
        unsigned int mcpu_event_mask : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCA15_EVENT_MASK_T;
typedef union
{
    struct
    {
        unsigned int a7_event_mask : 1;
        unsigned int a15_event_mask : 1;
        unsigned int iom3_event_mask : 1;
        unsigned int lpm3_event_mask : 1;
        unsigned int mcpu_event_mask : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCIOM3_EVENT_MASK_T;
typedef union
{
    struct
    {
        unsigned int a7_event_mask : 1;
        unsigned int a15_event_mask : 1;
        unsigned int iom3_event_mask : 1;
        unsigned int lpm3_event_mask : 1;
        unsigned int mcpu_event_mask : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCLPM3_EVENT_MASK_T;
typedef union
{
    struct
    {
        unsigned int a7_event_mask : 1;
        unsigned int a15_event_mask : 1;
        unsigned int iom3_event_mask : 1;
        unsigned int lpm3_event_mask : 1;
        unsigned int mcpu_event_mask : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCMCPU_EVENT_MASK_T;
typedef union
{
    struct
    {
        unsigned int a7_event : 1;
        unsigned int a15_event : 1;
        unsigned int iom3_event : 1;
        unsigned int lpm3_event : 1;
        unsigned int mcpu_event : 1;
        unsigned int reserved : 27;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCEVENT_STAT_T;
typedef union
{
    struct
    {
        unsigned int processor_jtag_sel : 1;
        unsigned int dsp_jtag_sel : 2;
        unsigned int reserved : 29;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCJTAG_SEL_T;
typedef union
{
    struct
    {
        unsigned int modem_key0 : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCMODEM_KEY0_T;
typedef union
{
    struct
    {
        unsigned int modem_key1 : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCMODEM_KEY1_T;
typedef union
{
    struct
    {
        unsigned int modem_key2 : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCMODEM_KEY2_T;
typedef union
{
    struct
    {
        unsigned int modem_key3 : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCMODEM_KEY3_T;
typedef union
{
    struct
    {
        unsigned int cfg_djtag : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCFG_DJTAG_T;
typedef union
{
    struct
    {
        unsigned int a7cp15disable0 : 1;
        unsigned int a7cp15disable1 : 1;
        unsigned int a7cp15disable2 : 1;
        unsigned int a7cp15disable3 : 1;
        unsigned int a15cp15disable0 : 1;
        unsigned int a15cp15disable1 : 1;
        unsigned int a15cp15disable2 : 1;
        unsigned int a15cp15disable3 : 1;
        unsigned int a9cp15disable : 1;
        unsigned int gicdisable : 1;
        unsigned int reserved : 22;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCP15_DISABLE_T;
typedef union
{
    struct
    {
        unsigned int cnt_stat : 16;
        unsigned int reserved : 16;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKCNTSTAT_T;
typedef union
{
    struct
    {
        unsigned int cnt_cfg : 16;
        unsigned int timer_secu_en : 1;
        unsigned int reserved : 13;
        unsigned int clk_cnt_en : 1;
        unsigned int clk_monitor_en : 1;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKCNTCFG_T;
typedef union
{
    struct
    {
        unsigned int intr_clr : 1;
        unsigned int intr_mask : 1;
        unsigned int reserved : 30;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKMONCTRL_T;
typedef union
{
    struct
    {
        unsigned int raw_intr : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCLKMONINT_T;
typedef union
{
    struct
    {
        unsigned int cfg_arm_dbgen : 4;
        unsigned int reserved : 28;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCFG_ARM_DBGEN_T;
typedef union
{
    struct
    {
        unsigned int arm_dbg_key0 : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCARM_DBG_KEY0_T;
typedef union
{
    struct
    {
        unsigned int arm_dbg_key1 : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCARM_DBG_KEY1_T;
typedef union
{
    struct
    {
        unsigned int arm_dbgen_wr : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCARM_DBGEN_STAT_T;
typedef union
{
    struct
    {
        unsigned int sys_efuse_pad_sel : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCEFUSECTRL_T;
typedef union
{
    struct
    {
        unsigned int gt_clk_ao_cc_secs : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCEFUSESEL_T;
typedef union
{
    struct
    {
        unsigned int security_n : 1;
        unsigned int reserved : 31;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCSECURITYSTAT_T;
typedef union
{
    struct
    {
        unsigned int chip_id0 : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCHIP_ID0_T;
typedef union
{
    struct
    {
        unsigned int chip_id1 : 32;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCCHIP_ID1_T;
typedef union
{
    struct
    {
        unsigned int version_code : 16;
        unsigned int chip_code : 16;
    } bits;
    unsigned int u32;
}HI_AP_SCTRL_SCSOCID0_T;
HI_SET_GET(hi_ap_sctrl_scctrl_modectrl,modectrl,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_modestatus,modestatus,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_reserved_1,reserved_1,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeforcehigh,timeforcehigh,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren0sel,timeren0sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren0ov,timeren0ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren1sel,timeren1sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren1ov,timeren1ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren2sel,timeren2sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren2ov,timeren2ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren3sel,timeren3sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren3ov,timeren3ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren4sel,timeren4sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren4ov,timeren4ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren5sel,timeren5sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren5ov,timeren5ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren6sel,timeren6sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren6ov,timeren6ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren7sel,timeren7sel,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_timeren7ov,timeren7ov,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_deepsleepen,deepsleepen,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scctrl_reserved_0,reserved_0,HI_AP_SCTRL_SCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsysstat_reset_source,reset_source,HI_AP_SCTRL_SCSYSSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSYSSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsysstat_reserved,reserved,HI_AP_SCTRL_SCSYSSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSYSSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_itmden,itmden,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_itmdctrl,itmdctrl,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_reserved_1,reserved_1,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_inmdtype,inmdtype,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scitmctrl_reserved_0,reserved_0,HI_AP_SCTRL_SCITMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCITMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scimstat_itmdstat,itmdstat,HI_AP_SCTRL_SCIMSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIMSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scimstat_reserved,reserved,HI_AP_SCTRL_SCIMSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIMSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxopresel_apb,tcxopresel_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxohardcon_bypass,tcxohardcon_bypass,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxosel_apb,tcxosel_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxosoft_apb,tcxosoft_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_defau_tcxo,defau_tcxo,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxofast_ctrl0,tcxofast_ctrl0,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxofast_ctrl1,tcxofast_ctrl1,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlen1_apb,ctrlen1_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlsel1_apb,ctrlsel1_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlen0_apb,ctrlen0_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_ctrlsel0_apb,ctrlsel0_apb,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_timeout_bypass0,timeout_bypass0,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_timeout_bypass1,timeout_bypass1,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxoseq_bypass,tcxoseq_bypass,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxoseq0_time,tcxoseq0_time,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_tcxoseq1_time,tcxoseq1_time,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalctrl_reserved,reserved,HI_AP_SCTRL_SCXTALCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtaltimeout0_timeoutcnt0_apb,timeoutcnt0_apb,HI_AP_SCTRL_SCXTALTIMEOUT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALTIMEOUT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtaltimeout1_timeoutcnt1_apb,timeoutcnt1_apb,HI_AP_SCTRL_SCXTALTIMEOUT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALTIMEOUT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_en0,tcxo_en0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_en1,tcxo_en1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_timeout1,tcxo_timeout1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxo_timeout0,tcxo_timeout0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_sysclk_en1,sysclk_en1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_sysclk_en0,sysclk_en0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_sysclk_sel,sysclk_sel,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_clkgt_ctrl0,clkgt_ctrl0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_clkgt_ctrl1,clkgt_ctrl1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_clkgt_ctrl,clkgt_ctrl,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_abbbuf_en0,abbbuf_en0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_abbbuf_en1,abbbuf_en1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxoseq_finish0,tcxoseq_finish0,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_tcxoseq_finish1,tcxoseq_finish1,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scxtalstat_reserved,reserved,HI_AP_SCTRL_SCXTALSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCXTALSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_en,ppll0_en,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_bp,ppll0_bp,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_refdiv,ppll0_refdiv,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_fbdiv,ppll0_fbdiv,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_postdiv1,ppll0_postdiv1,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_ppll0_postdiv2,ppll0_postdiv2,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl0_reserved,reserved,HI_AP_SCTRL_SCPPLLCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_ppll0_fracdiv,ppll0_fracdiv,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_ppll0_int_mod,ppll0_int_mod,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_ppll0_cfg_vld,ppll0_cfg_vld,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_gt_clk_ppll0,gt_clk_ppll0,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllctrl1_reserved,reserved,HI_AP_SCTRL_SCPPLLCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_reset,ppll0_ssc_reset,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_disable,ppll0_ssc_disable,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_downspread,ppll0_ssc_downspread,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_spread,ppll0_ssc_spread,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_ppll0_ssc_divval,ppll0_ssc_divval,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllsscctrl_reserved,reserved,HI_AP_SCTRL_SCPPLLSSCCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSSCCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllstat_pllstat,pllstat,HI_AP_SCTRL_SCPPLLSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scppllstat_reserved,reserved,HI_AP_SCTRL_SCPPLLSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPPLLSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_reserved,reserved,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPEREN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_reserved,reserved,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPERDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_reserved,reserved,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPERCLKEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_ao_cc,gt_clk_ao_cc,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_rtc,gt_pclk_rtc,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_rtc1,gt_pclk_rtc1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer0,gt_pclk_timer0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer0,gt_clk_timer0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer1,gt_pclk_timer1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer1,gt_clk_timer1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer2,gt_pclk_timer2,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer2,gt_clk_timer2,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_timer3,gt_pclk_timer3,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_timer3,gt_clk_timer3,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio0,gt_pclk_ao_gpio0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio1,gt_pclk_ao_gpio1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio2,gt_pclk_ao_gpio2,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio3,gt_pclk_ao_gpio3,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_ioc,gt_pclk_ao_ioc,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_out0,gt_clk_out0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_out1,gt_clk_out1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_jtag_auth,gt_clk_jtag_auth,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_syscnt,gt_pclk_syscnt,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_syscnt,gt_clk_syscnt,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio4,gt_pclk_ao_gpio4,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_ao_gpio5,gt_pclk_ao_gpio5,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_sci0,gt_clk_sci0,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_sci1,gt_clk_sci1,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_memrep,gt_clk_memrep,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_asp_tcxo,gt_clk_asp_tcxo,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_bbpdrx,gt_clk_bbpdrx,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_pclk_efusec,gt_pclk_efusec,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat0_gt_clk_ppll0_sscg,gt_clk_ppll0_sscg,HI_AP_SCTRL_SCPERSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen1_reserved,reserved,HI_AP_SCTRL_SCPEREN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis1_reserved,reserved,HI_AP_SCTRL_SCPERDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken1_reserved,reserved,HI_AP_SCTRL_SCPERCLKEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_asp_dw_axi,gt_clk_asp_dw_axi,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_asp_x2h,gt_clk_asp_x2h,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_asp_h2p,gt_clk_asp_h2p,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_asp_cfg,gt_asp_cfg,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_gt_clk_bbpdrx_oth,gt_clk_bbpdrx_oth,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_reserved,reserved,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_swdone_clk_asp_subsys_div,swdone_clk_asp_subsys_div,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_swdone_clk_sci_div,swdone_clk_sci_div,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_swdone_clk_aobus_div,swdone_clk_aobus_div,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_aobusclksw2sys,aobusclksw2sys,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat1_aobusclksw2pll,aobusclksw2pll,HI_AP_SCTRL_SCPERSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperen2_reserved,reserved,HI_AP_SCTRL_SCPEREN2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPEREN2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperdis2_reserved,reserved,HI_AP_SCTRL_SCPERDIS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERDIS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperclken2_reserved,reserved,HI_AP_SCTRL_SCPERCLKEN2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCLKEN2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstat2_reserved,reserved,HI_AP_SCTRL_SCPERSTAT2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTAT2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_cc,ip_rst_ao_cc,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_rtc,ip_rst_rtc,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_rtc1,ip_rst_rtc1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer0,ip_rst_timer0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer1,ip_rst_timer1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer2,ip_rst_timer2,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_timer3,ip_rst_timer3,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_cfg,rst_asp_cfg,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_dw_axi,rst_asp_dw_axi,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_x2h,rst_asp_x2h,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_rst_asp_h2p,rst_asp_h2p,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio0,ip_rst_ao_gpio0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio1,ip_rst_ao_gpio1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio2,ip_rst_ao_gpio2,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio3,ip_rst_ao_gpio3,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio4,ip_rst_ao_gpio4,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_gpio5,ip_rst_ao_gpio5,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_3,reserved_3,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_ao_ioc,ip_rst_ao_ioc,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_prst_syscnt,ip_prst_syscnt,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_syscnt,ip_rst_syscnt,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_2,reserved_2,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_sci0,ip_rst_sci0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_sci1,ip_rst_sci1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_1,reserved_1,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_asp_subsys,ip_rst_asp_subsys,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_bbpdrx,ip_rst_bbpdrx,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_reserved_0,reserved_0,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_ip_rst_aobus,ip_rst_aobus,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_sc_rst_src_clr,sc_rst_src_clr,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten0_sc_pmurst_ctrl,sc_pmurst_ctrl,HI_AP_SCTRL_SCPERRSTEN0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_cc,ip_rst_ao_cc,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_rtc,ip_rst_rtc,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_rtc1,ip_rst_rtc1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer0,ip_rst_timer0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer1,ip_rst_timer1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer2,ip_rst_timer2,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_timer3,ip_rst_timer3,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_cfg,rst_asp_cfg,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_dw_axi,rst_asp_dw_axi,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_x2h,rst_asp_x2h,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_rst_asp_h2p,rst_asp_h2p,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio0,ip_rst_ao_gpio0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio1,ip_rst_ao_gpio1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio2,ip_rst_ao_gpio2,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio3,ip_rst_ao_gpio3,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio4,ip_rst_ao_gpio4,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_gpio5,ip_rst_ao_gpio5,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_3,reserved_3,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_ao_ioc,ip_rst_ao_ioc,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_prst_syscnt,ip_prst_syscnt,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_syscnt,ip_rst_syscnt,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_2,reserved_2,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_sci0,ip_rst_sci0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_sci1,ip_rst_sci1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_1,reserved_1,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_asp_subsys,ip_rst_asp_subsys,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_bbpdrx,ip_rst_bbpdrx,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_reserved_0,reserved_0,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_ip_rst_aobus,ip_rst_aobus,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_sc_rst_src_clr,sc_rst_src_clr,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis0_sc_pmurst_ctrl,sc_pmurst_ctrl,HI_AP_SCTRL_SCPERRSTDIS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_cc,ip_rst_ao_cc,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_rtc,ip_rst_rtc,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_rtc1,ip_rst_rtc1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer0,ip_rst_timer0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer1,ip_rst_timer1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer2,ip_rst_timer2,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_timer3,ip_rst_timer3,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_cfg,rst_asp_cfg,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_dw_axi,rst_asp_dw_axi,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_x2h,rst_asp_x2h,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_rst_asp_h2p,rst_asp_h2p,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio0,ip_rst_ao_gpio0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio1,ip_rst_ao_gpio1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio2,ip_rst_ao_gpio2,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio3,ip_rst_ao_gpio3,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio4,ip_rst_ao_gpio4,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_gpio5,ip_rst_ao_gpio5,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_3,reserved_3,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_ao_ioc,ip_rst_ao_ioc,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_prst_syscnt,ip_prst_syscnt,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_syscnt,ip_rst_syscnt,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_2,reserved_2,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_sci0,ip_rst_sci0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_sci1,ip_rst_sci1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_1,reserved_1,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_asp_subsys,ip_rst_asp_subsys,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_bbpdrx,ip_rst_bbpdrx,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_reserved_0,reserved_0,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_ip_rst_aobus,ip_rst_aobus,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_sc_rst_src_clr,sc_rst_src_clr,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat0_sc_pmurst_ctrl,sc_pmurst_ctrl,HI_AP_SCTRL_SCPERRSTSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten1_reserved,reserved,HI_AP_SCTRL_SCPERRSTEN1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis1_reserved,reserved,HI_AP_SCTRL_SCPERRSTDIS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat1_reserved,reserved,HI_AP_SCTRL_SCPERRSTSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrsten2_reserved,reserved,HI_AP_SCTRL_SCPERRSTEN2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTEN2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrstdis2_reserved,reserved,HI_AP_SCTRL_SCPERRSTDIS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTDIS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperrststat2_reserved,reserved,HI_AP_SCTRL_SCPERRSTSTAT2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERRSTSTAT2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_rtc_bypass,rst_gt_rtc_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_rtc1_bypass,rst_gt_rtc1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer0_bypass,rst_gt_timer0_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer1_bypass,rst_gt_timer1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer2_bypass,rst_gt_timer2_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_timer3_bypass,rst_gt_timer3_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio0_bypass,rst_gt_gpio0_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio1_bypass,rst_gt_gpio1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio2_bypass,rst_gt_gpio2_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio3_bypass,rst_gt_gpio3_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio4_bypass,rst_gt_gpio4_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_gpio5_bypass,rst_gt_gpio5_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_ioc_bypass,rst_gt_ioc_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_syscnt_bypass,rst_gt_syscnt_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_sci0_bypass,rst_gt_sci0_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_sci1_bypass,rst_gt_sci1_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_bbpdrx_bypass,rst_gt_bbpdrx_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_rst_gt_efusec_bypass,rst_gt_efusec_bypass,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scipclkrstbus_reserved,reserved,HI_AP_SCTRL_SCIPCLKRSTBUS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIPCLKRSTBUS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisoen_audioisoen,audioisoen,HI_AP_SCTRL_SCISOEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisoen_reserved,reserved,HI_AP_SCTRL_SCISOEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisodis_audioisoen,audioisoen,HI_AP_SCTRL_SCISODIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISODIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisodis_reserved,reserved,HI_AP_SCTRL_SCISODIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISODIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisostat_audioisoen,audioisoen,HI_AP_SCTRL_SCISOSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scisostat_reserved,reserved,HI_AP_SCTRL_SCISOSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCISOSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwren_audiopwren,audiopwren,HI_AP_SCTRL_SCPWREN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWREN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwren_reserved,reserved,HI_AP_SCTRL_SCPWREN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWREN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrdis_audiopwren,audiopwren,HI_AP_SCTRL_SCPWRDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrdis_reserved,reserved,HI_AP_SCTRL_SCPWRDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrstat_audiopwrstat,audiopwrstat,HI_AP_SCTRL_SCPWRSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrstat_reserved,reserved,HI_AP_SCTRL_SCPWRSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrack_audiopwrack,audiopwrack,HI_AP_SCTRL_SCPWRACK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRACK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scpwrack_reserved,reserved,HI_AP_SCTRL_SCPWRACK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPWRACK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwrdowntime_peri_pwr_down_time,peri_pwr_down_time,HI_AP_SCTRL_SCPERPWRDOWNTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRDOWNTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwrdowntime_reserved,reserved,HI_AP_SCTRL_SCPERPWRDOWNTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRDOWNTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwruptime_peri_pwr_up_time,peri_pwr_up_time,HI_AP_SCTRL_SCPERPWRUPTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRUPTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperpwruptime_reserved,reserved,HI_AP_SCTRL_SCPERPWRUPTIME_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERPWRUPTIME_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_sc_div_asp_subsys,sc_div_asp_subsys,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_sc_div_hifidsp,sc_div_hifidsp,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_sc_div_sci,sc_div_sci,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_reserved,reserved,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_extclk_en,extclk_en,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv0_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_sc_div_aobus,sc_div_aobus,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_div_clkout0_tcxo,div_clkout0_tcxo,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_div_clkout1_tcxo,div_clkout1_tcxo,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_sel_clkout0,sel_clkout0,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_sel_clkout1,sel_clkout1,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv1_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_clk_asp_subsys,gt_clk_asp_subsys,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_hifidsp_clk_div,gt_hifidsp_clk_div,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_clk_sci,gt_clk_sci,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_clk_aobus,gt_clk_aobus,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_gt_asp_hclk_div,gt_asp_hclk_div,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_reserved_1,reserved_1,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_sc_div_asp_hclk,sc_div_asp_hclk,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_reserved_0,reserved_0,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv2_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv3_reserved,reserved,HI_AP_SCTRL_SCCLKDIV3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv3_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv4_reserved,reserved,HI_AP_SCTRL_SCCLKDIV4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv4_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv5_reserved,reserved,HI_AP_SCTRL_SCCLKDIV5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkdiv5_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCCLKDIV5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKDIV5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl0_efusec_mem_ctrl,efusec_mem_ctrl,HI_AP_SCTRL_SCPERCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl0_efuse_remap,efuse_remap,HI_AP_SCTRL_SCPERCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl0_reserved,reserved,HI_AP_SCTRL_SCPERCTRL0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl1_reserved,reserved,HI_AP_SCTRL_SCPERCTRL1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_repair_disable,repair_disable,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_reserved_1,reserved_1,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_jtaq_to_sdcard,jtaq_to_sdcard,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl2_reserved_0,reserved_0,HI_AP_SCTRL_SCPERCTRL2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_reserved_1,reserved_1,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_reset_memrep_msk,reset_memrep_msk,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_repair_iddq,repair_iddq,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_repair_frm_sram,repair_frm_sram,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_repair_frm_efu,repair_frm_efu,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_dram_pwr_ctl,dram_pwr_ctl,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_efusec_timeout_bypass,efusec_timeout_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_bbdrx_timeout_bypass,bbdrx_timeout_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_cfgbus_bypass,sleep_mode_cfgbus_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_lpmcu_bypass,sleep_mode_lpmcu_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_iomcu_bypass,sleep_mode_iomcu_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_sleep_mode_aobus_bypass,sleep_mode_aobus_bypass,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_bbp_clk_en,bbp_clk_en,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl3_reserved_0,reserved_0,HI_AP_SCTRL_SCPERCTRL3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl4_ddr_ret_en,ddr_ret_en,HI_AP_SCTRL_SCPERCTRL4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl4_reserved,reserved,HI_AP_SCTRL_SCPERCTRL4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_usim0_io_sel18,usim0_io_sel18,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_usim1_io_sel18,usim1_io_sel18,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_sdcard_io_sel18,sdcard_io_sel18,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_tp_sel,tp_sel,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_tcxo_mode,tcxo_mode,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl5_reserved,reserved,HI_AP_SCTRL_SCPERCTRL5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_peri_io_ret,peri_io_ret,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_reserved_1,reserved_1,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_peri_bootio_ret,peri_bootio_ret,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_peri_bootio_ret_mode,peri_bootio_ret_mode,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperctrl6_reserved_0,reserved_0,HI_AP_SCTRL_SCPERCTRL6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERCTRL6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_wr,asp_dwaxi_dlock_wr,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_id,asp_dwaxi_dlock_id,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_slv,asp_dwaxi_dlock_slv,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_asp_dwaxi_dlock_mst,asp_dwaxi_dlock_mst,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_sys_pw_stat,sys_pw_stat,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tcxoseq_stat0,tcxoseq_stat0,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tcxoseq_stat1,tcxoseq_stat1,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tp_a3_grp,tp_a3_grp,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tp_a4_grp0,tp_a4_grp0,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus0_tp_a4_grp1,tp_a4_grp1,HI_AP_SCTRL_SCPERSTATUS0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus1_err_flag,err_flag,HI_AP_SCTRL_SCPERSTATUS1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus2_peri_stat2,peri_stat2,HI_AP_SCTRL_SCPERSTATUS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus2_reserved,reserved,HI_AP_SCTRL_SCPERSTATUS2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus3_efusec_timeout_dbg_info,efusec_timeout_dbg_info,HI_AP_SCTRL_SCPERSTATUS3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scperstatus4_bbdrx_timeout_dbg_info,bbdrx_timeout_dbg_info,HI_AP_SCTRL_SCPERSTATUS4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCPERSTATUS4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_deepsleeped,deepsleeped,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_reserved_1,reserved_1,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_sleeped,sleeped,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdeepsleeped_reserved_0,reserved_0,HI_AP_SCTRL_SCDEEPSLEEPED_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDEEPSLEEPED_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmrbbusystat_mrb_efuse_busy,mrb_efuse_busy,HI_AP_SCTRL_SCMRBBUSYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMRBBUSYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmrbbusystat_reserved,reserved,HI_AP_SCTRL_SCMRBBUSYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMRBBUSYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scswaddr_swaddr,swaddr,HI_AP_SCTRL_SCSWADDR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSWADDR_OFFSET)
HI_SET_GET(hi_ap_sctrl_scddraddr_ddrtrainaddr,ddrtrainaddr,HI_AP_SCTRL_SCDDRADDR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDDRADDR_OFFSET)
HI_SET_GET(hi_ap_sctrl_scddrdata_ddrtraindata,ddrtraindata,HI_AP_SCTRL_SCDDRDATA_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDDRDATA_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata0_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata1_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata2_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata3_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA3_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata4_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA4_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA4_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata5_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA5_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA5_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata6_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA6_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA6_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata7_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA7_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA7_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata8_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA8_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA8_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata9_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA9_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA9_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata10_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA10_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA10_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata11_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA11_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA11_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata12_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA12_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA12_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata13_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA13_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA13_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata14_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA14_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA14_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbakdata15_bakdata,bakdata,HI_AP_SCTRL_SCBAKDATA15_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBAKDATA15_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_int_wakeup_sys,int_wakeup_sys,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_drx0_int,drx0_int,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_drx1_int,drx1_int,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_notdrx_int,notdrx_int,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_gather_stat_reserved,reserved,HI_AP_SCTRL_SCINT_GATHER_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_GATHER_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_22_int,gpio_22_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_23_int,gpio_23_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_24_int,gpio_24_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_25_int,gpio_25_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_26_int,gpio_26_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_rtc_int,rtc_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_rtc1_int,rtc1_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer0_int,timer0_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer1_int,timer1_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer2_int,timer2_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer3_int,timer3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer4_int,timer4_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer5_int,timer5_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer6_int,timer6_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_timer7_int,timer7_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_irq_int0,gic_irq_int0,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_irq_int1,gic_irq_int1,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_fiq_int2,gic_fiq_int2,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gic_fiq_int3,gic_fiq_int3,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_lpm3_int,lpm3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_iom3_int,iom3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_asp_ipc_arm_int,asp_ipc_arm_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx0_int,drx0_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx1_int,drx1_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx2_int,drx2_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx3_int,drx3_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_drx4_int,drx4_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_27_int,gpio_27_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_asp_int,gpio_asp_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_gpio_asp_int_sc,gpio_asp_int_sc,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_intr_asp_watchdog,intr_asp_watchdog,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_mask_lpm3_wfi_int,lpm3_wfi_int,HI_AP_SCTRL_SCINT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_22_int,gpio_22_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_23_int,gpio_23_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_24_int,gpio_24_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_25_int,gpio_25_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_26_int,gpio_26_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_rtc_int,rtc_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_rtc1_int,rtc1_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer0_int,timer0_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer1_int,timer1_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer2_int,timer2_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer3_int,timer3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer4_int,timer4_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer5_int,timer5_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer6_int,timer6_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_timer7_int,timer7_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int0,gic_int0,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int1,gic_int1,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int2,gic_int2,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gic_int3,gic_int3,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_lpm3_int,lpm3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_iom3_int,iom3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_asp_ipc_arm_int,asp_ipc_arm_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx0_int,drx0_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx1_int,drx1_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx2_int,drx2_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx3_int,drx3_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_drx4_int,drx4_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_27_int,gpio_27_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_intr_asp_watchdog,intr_asp_watchdog,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_gpio_asp_int,gpio_asp_int,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scint_stat_reserved,reserved,HI_AP_SCTRL_SCINT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCINT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx0_int,drx0_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx1_int,drx1_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx2_int,drx2_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx3_int,drx3_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_drx4_int,drx4_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_gpio_asp_int,gpio_asp_int,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scdrx_int_cfg_reserved,reserved,HI_AP_SCTRL_SCDRX_INT_CFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCDRX_INT_CFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3wfi_int_clr_lpm3_wfi_int_clr,lpm3_wfi_int_clr,HI_AP_SCTRL_SCLPM3WFI_INT_CLR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3WFI_INT_CLR_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3wfi_int_clr_reserved,reserved,HI_AP_SCTRL_SCLPM3WFI_INT_CLR_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3WFI_INT_CLR_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmalibypcfg_mali_dbgack_byp,mali_dbgack_byp,HI_AP_SCTRL_SCMALIBYPCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMALIBYPCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmalibypcfg_reserved,reserved,HI_AP_SCTRL_SCMALIBYPCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMALIBYPCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_dapclkoff_sys_n,dapclkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_reserved_1,reserved_1,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_rom_clk_clkoff_sys_n,rom_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_ram_clk_clkoff_sys_n,ram_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_reserved_0,reserved_0,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_ddrc_clk_clkoff_sys_n,ddrc_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_tsen_clk_clkoff_sys_n,tsen_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_pmc_clk_clkoff_sys_n,pmc_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_uart_clk_clkoff_sys_n,uart_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_i2c_clk_clkoff_sys_n,i2c_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_ssi_clk_clkoff_sys_n,ssi_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_pcrg_clk_clkoff_sys_n,pcrg_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_nandc_clk_clkoff_sys_n,nandc_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_wdog_clk_clkoff_sys_n,wdog_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_tim_clk_clkoff_sys_n,tim_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_cssys_clk_clkoff_sys_n,cssys_clk_clkoff_sys_n,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3clken_clkdivmasken,clkdivmasken,HI_AP_SCTRL_SCLPM3CLKEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CLKEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_rst_software_req,rst_software_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_coresight_soft_rst_req,coresight_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_reserved_2,reserved_2,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_rom_soft_rst_req,rom_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_ram_soft_rst_req,ram_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_reserved_1,reserved_1,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_ddrc_soft_rst_req,ddrc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_tsen_soft_rst_req,tsen_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_pmc_soft_rst_req,pmc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_uart_soft_rst_req,uart_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_i2c_soft_rst_req,i2c_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_ssi_soft_rst_req,ssi_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_pcrg_soft_rst_req,pcrg_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_nandc_soft_rst_req,nandc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_wdog_soft_rst_req,wdog_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_tim_soft_rst_req,tim_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_cssys_soft_rst_req,cssys_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rsten_reserved_0,reserved_0,HI_AP_SCTRL_SCLPM3RSTEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_rst_software_req,rst_software_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_coresight_soft_rst_req,coresight_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_bus_soft_rst_req,bus_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_rom_soft_rst_req,rom_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_ram_soft_rst_req,ram_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_aon_soft_rst_req,aon_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_ddrc_soft_rst_req,ddrc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_tsen_soft_rst_req,tsen_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_pmc_soft_rst_req,pmc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_uart_soft_rst_req,uart_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_i2c_soft_rst_req,i2c_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_ssi_soft_rst_req,ssi_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_pcrg_soft_rst_req,pcrg_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_nandc_soft_rst_req,nandc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_wdog_soft_rst_req,wdog_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_tim_soft_rst_req,tim_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_cssys_soft_rst_req,cssys_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rstdis_reserved,reserved,HI_AP_SCTRL_SCLPM3RSTDIS_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTDIS_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_rst_software_req,rst_software_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_coresight_soft_rst_req,coresight_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_bus_soft_rst_req,bus_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_rom_soft_rst_req,rom_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_ram_soft_rst_req,ram_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_aon_soft_rst_req,aon_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_ddrc_soft_rst_req,ddrc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_tsen_soft_rst_req,tsen_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_pmc_soft_rst_req,pmc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_uart_soft_rst_req,uart_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_i2c_soft_rst_req,i2c_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_ssi_soft_rst_req,ssi_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_pcrg_soft_rst_req,pcrg_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_nandc_soft_rst_req,nandc_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_wdog_soft_rst_req,wdog_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_tim_soft_rst_req,tim_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_cssys_soft_rst_req,cssys_soft_rst_req,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3rststat_reserved,reserved,HI_AP_SCTRL_SCLPM3RSTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RSTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_boot_remap_en,boot_remap_en,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_mpudisable,mpudisable,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_nmi_in,nmi_in,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_bus_div_clk_sel,bus_div_clk_sel,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_sysresetreq_en,sysresetreq_en,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_mem_ctrl_ema_lpram,mem_ctrl_ema_lpram,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_lpm3idle_bypass,lpm3idle_bypass,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_reserved_1,reserved_1,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ctrl_reserved_0,reserved_0,HI_AP_SCTRL_SCLPM3CTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3CTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_sysresetreq_sign_out_stat,sysresetreq_sign_out_stat,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_sleeping,sleeping,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_lockup,lockup,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_halted,halted,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3stat_reserved,reserved,HI_AP_SCTRL_SCLPM3STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpramctrl_sel,lpramctrl_sel,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram0_mod,lpram0_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram1_mod,lpram1_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram2_mod,lpram2_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram3_mod,lpram3_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram0ctrl_soft,lpram0ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram1ctrl_soft,lpram1ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram2ctrl_soft,lpram2ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_lpram3ctrl_soft,lpram3ctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_memrep_ram_mod,memrep_ram_mod,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_memrep_ramctrl_soft,memrep_ramctrl_soft,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3ramctrl_reserved,reserved,HI_AP_SCTRL_SCLPM3RAMCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3RAMCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_g2_gdrx_depsleep_flag,g2_gdrx_depsleep_flag,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_g1_gdrx_depsleep_flag,g1_gdrx_depsleep_flag,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_wdrx_deepsleep_flag,wdrx_deepsleep_flag,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat0_reserved,reserved,HI_AP_SCTRL_SCBBPDRXSTAT0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat1_ldrx2dbg_abs_timer,ldrx2dbg_abs_timer,HI_AP_SCTRL_SCBBPDRXSTAT1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scbbpdrxstat2_ldrx2dbg_abs_timer,ldrx2dbg_abs_timer,HI_AP_SCTRL_SCBBPDRXSTAT2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCBBPDRXSTAT2_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca7_event_mask_reserved,reserved,HI_AP_SCTRL_SCA7_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA7_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sca15_event_mask_reserved,reserved,HI_AP_SCTRL_SCA15_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCA15_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sciom3_event_mask_reserved,reserved,HI_AP_SCTRL_SCIOM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCIOM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_sclpm3_event_mask_reserved,reserved,HI_AP_SCTRL_SCLPM3_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCLPM3_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_a7_event_mask,a7_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_a15_event_mask,a15_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_iom3_event_mask,iom3_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_lpm3_event_mask,lpm3_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_mcpu_event_mask,mcpu_event_mask,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmcpu_event_mask_reserved,reserved,HI_AP_SCTRL_SCMCPU_EVENT_MASK_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMCPU_EVENT_MASK_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_a7_event,a7_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_a15_event,a15_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_iom3_event,iom3_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_lpm3_event,lpm3_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_mcpu_event,mcpu_event,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scevent_stat_reserved,reserved,HI_AP_SCTRL_SCEVENT_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEVENT_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scjtag_sel_processor_jtag_sel,processor_jtag_sel,HI_AP_SCTRL_SCJTAG_SEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCJTAG_SEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scjtag_sel_dsp_jtag_sel,dsp_jtag_sel,HI_AP_SCTRL_SCJTAG_SEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCJTAG_SEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scjtag_sel_reserved,reserved,HI_AP_SCTRL_SCJTAG_SEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCJTAG_SEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key0_modem_key0,modem_key0,HI_AP_SCTRL_SCMODEM_KEY0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key1_modem_key1,modem_key1,HI_AP_SCTRL_SCMODEM_KEY1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key2_modem_key2,modem_key2,HI_AP_SCTRL_SCMODEM_KEY2_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY2_OFFSET)
HI_SET_GET(hi_ap_sctrl_scmodem_key3_modem_key3,modem_key3,HI_AP_SCTRL_SCMODEM_KEY3_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCMODEM_KEY3_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_djtag_cfg_djtag,cfg_djtag,HI_AP_SCTRL_SCCFG_DJTAG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_DJTAG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_djtag_reserved,reserved,HI_AP_SCTRL_SCCFG_DJTAG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_DJTAG_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable0,a7cp15disable0,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable1,a7cp15disable1,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable2,a7cp15disable2,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a7cp15disable3,a7cp15disable3,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable0,a15cp15disable0,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable1,a15cp15disable1,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable2,a15cp15disable2,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a15cp15disable3,a15cp15disable3,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_a9cp15disable,a9cp15disable,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_gicdisable,gicdisable,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccp15_disable_reserved,reserved,HI_AP_SCTRL_SCCP15_DISABLE_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCP15_DISABLE_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntstat_cnt_stat,cnt_stat,HI_AP_SCTRL_SCCLKCNTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntstat_reserved,reserved,HI_AP_SCTRL_SCCLKCNTSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_cnt_cfg,cnt_cfg,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_timer_secu_en,timer_secu_en,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_reserved,reserved,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_clk_cnt_en,clk_cnt_en,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkcntcfg_clk_monitor_en,clk_monitor_en,HI_AP_SCTRL_SCCLKCNTCFG_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKCNTCFG_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonctrl_intr_clr,intr_clr,HI_AP_SCTRL_SCCLKMONCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonctrl_intr_mask,intr_mask,HI_AP_SCTRL_SCCLKMONCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonctrl_reserved,reserved,HI_AP_SCTRL_SCCLKMONCTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONCTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonint_raw_intr,raw_intr,HI_AP_SCTRL_SCCLKMONINT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONINT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scclkmonint_reserved,reserved,HI_AP_SCTRL_SCCLKMONINT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCLKMONINT_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_arm_dbgen_cfg_arm_dbgen,cfg_arm_dbgen,HI_AP_SCTRL_SCCFG_ARM_DBGEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_ARM_DBGEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_sccfg_arm_dbgen_reserved,reserved,HI_AP_SCTRL_SCCFG_ARM_DBGEN_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCFG_ARM_DBGEN_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbg_key0_arm_dbg_key0,arm_dbg_key0,HI_AP_SCTRL_SCARM_DBG_KEY0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBG_KEY0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbg_key1_arm_dbg_key1,arm_dbg_key1,HI_AP_SCTRL_SCARM_DBG_KEY1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBG_KEY1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbgen_stat_arm_dbgen_wr,arm_dbgen_wr,HI_AP_SCTRL_SCARM_DBGEN_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBGEN_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scarm_dbgen_stat_reserved,reserved,HI_AP_SCTRL_SCARM_DBGEN_STAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCARM_DBGEN_STAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusectrl_sys_efuse_pad_sel,sys_efuse_pad_sel,HI_AP_SCTRL_SCEFUSECTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSECTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusectrl_reserved,reserved,HI_AP_SCTRL_SCEFUSECTRL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSECTRL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusesel_gt_clk_ao_cc_secs,gt_clk_ao_cc_secs,HI_AP_SCTRL_SCEFUSESEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSESEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scefusesel_reserved,reserved,HI_AP_SCTRL_SCEFUSESEL_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCEFUSESEL_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsecuritystat_security_n,security_n,HI_AP_SCTRL_SCSECURITYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSECURITYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsecuritystat_reserved,reserved,HI_AP_SCTRL_SCSECURITYSTAT_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSECURITYSTAT_OFFSET)
HI_SET_GET(hi_ap_sctrl_scchip_id0_chip_id0,chip_id0,HI_AP_SCTRL_SCCHIP_ID0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCHIP_ID0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scchip_id1_chip_id1,chip_id1,HI_AP_SCTRL_SCCHIP_ID1_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCCHIP_ID1_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsocid0_version_code,version_code,HI_AP_SCTRL_SCSOCID0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSOCID0_OFFSET)
HI_SET_GET(hi_ap_sctrl_scsocid0_chip_code,chip_code,HI_AP_SCTRL_SCSOCID0_T,HI_AP_SCTRL_BASE_ADDR, HI_AP_SCTRL_SCSOCID0_OFFSET)
#endif
