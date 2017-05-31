#ifndef __SOC_TZPC_INTERFACE_H__
#define __SOC_TZPC_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_TZPC_R0SIZE_ADDR(base) ((base) + (0x000))
#define SOC_TZPC_DECPROT0STAT_ADDR(base) ((base) + (0x800))
#define SOC_TZPC_DECPROT0SET_ADDR(base) ((base) + (0x804))
#define SOC_TZPC_DECPROT0CLR_ADDR(base) ((base) + (0x808))
#define SOC_TZPC_DECPROT1STAT_ADDR(base) ((base) + (0x80C))
#define SOC_TZPC_DECPROT1SET_ADDR(base) ((base) + (0x810))
#define SOC_TZPC_DECPROT1CLR_ADDR(base) ((base) + (0x814))
#define SOC_TZPC_DECPROT2STAT_ADDR(base) ((base) + (0x818))
#define SOC_TZPC_DECPROT2SET_ADDR(base) ((base) + (0x81C))
#define SOC_TZPC_DECPROT2CLR_ADDR(base) ((base) + (0x820))
#define SOC_TZPC_DECPROT3STAT_ADDR(base) ((base) + (0x824))
#define SOC_TZPC_DECPROT3SET_ADDR(base) ((base) + (0x828))
#define SOC_TZPC_DECPROT3CLR_ADDR(base) ((base) + (0x82C))
#define SOC_TZPC_DECPROT4STAT_ADDR(base) ((base) + (0x830))
#define SOC_TZPC_DECPROT4SET_ADDR(base) ((base) + (0x834))
#define SOC_TZPC_DECPROT4CLR_ADDR(base) ((base) + (0x838))
#define SOC_TZPC_DECPROT5STAT_ADDR(base) ((base) + (0x83C))
#define SOC_TZPC_DECPROT5SET_ADDR(base) ((base) + (0x840))
#define SOC_TZPC_DECPROT5CLR_ADDR(base) ((base) + (0x844))
#define SOC_TZPC_DECPROT6STAT_ADDR(base) ((base) + (0x848))
#define SOC_TZPC_DECPROT6SET_ADDR(base) ((base) + (0x84C))
#define SOC_TZPC_DECPROT6CLR_ADDR(base) ((base) + (0x850))
#define SOC_TZPC_DECPROT7STAT_ADDR(base) ((base) + (0x854))
#define SOC_TZPC_DECPROT7SET_ADDR(base) ((base) + (0x858))
#define SOC_TZPC_DECPROT7CLR_ADDR(base) ((base) + (0x85C))
#define SOC_TZPC_DECPROT8STAT_ADDR(base) ((base) + (0x860))
#define SOC_TZPC_DECPROT8SET_ADDR(base) ((base) + (0x864))
#define SOC_TZPC_DECPROT8CLR_ADDR(base) ((base) + (0x868))
#define SOC_TZPC_REG0_STAT_ADDR(base) ((base) + (0x86C))
#define SOC_TZPC_REG1_STAT_ADDR(base) ((base) + (0x870))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0: 10;
        unsigned int reserved_1: 22;
    } reg;
} SOC_TZPC_R0SIZE_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int efusec : 1;
        unsigned int rtc0 : 1;
        unsigned int rtc1 : 1;
        unsigned int sci0 : 1;
        unsigned int sci1 : 1;
        unsigned int syscnt : 1;
        unsigned int sctrl_region1 : 1;
        unsigned int sctrl_region2 : 1;
        unsigned int sctrl_region3 : 1;
        unsigned int sctrl_region4 : 1;
        unsigned int gpio22 : 1;
        unsigned int gpio23 : 1;
        unsigned int gpio24 : 1;
        unsigned int gpio25 : 1;
        unsigned int gpio26 : 1;
        unsigned int gpio27 : 1;
        unsigned int ao_ioc : 1;
        unsigned int bb_drx : 1;
        unsigned int time0 : 1;
        unsigned int time1 : 1;
        unsigned int time2 : 1;
        unsigned int time3 : 1;
        unsigned int time4 : 1;
        unsigned int time5 : 1;
        unsigned int time6 : 1;
        unsigned int time7 : 1;
        unsigned int time8 : 1;
        unsigned int mmbuf : 1;
        unsigned int asc : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
    } reg;
} SOC_TZPC_DECPROT0STAT_UNION;
#endif
#define SOC_TZPC_DECPROT0STAT_efusec_START (0)
#define SOC_TZPC_DECPROT0STAT_efusec_END (0)
#define SOC_TZPC_DECPROT0STAT_rtc0_START (1)
#define SOC_TZPC_DECPROT0STAT_rtc0_END (1)
#define SOC_TZPC_DECPROT0STAT_rtc1_START (2)
#define SOC_TZPC_DECPROT0STAT_rtc1_END (2)
#define SOC_TZPC_DECPROT0STAT_sci0_START (3)
#define SOC_TZPC_DECPROT0STAT_sci0_END (3)
#define SOC_TZPC_DECPROT0STAT_sci1_START (4)
#define SOC_TZPC_DECPROT0STAT_sci1_END (4)
#define SOC_TZPC_DECPROT0STAT_syscnt_START (5)
#define SOC_TZPC_DECPROT0STAT_syscnt_END (5)
#define SOC_TZPC_DECPROT0STAT_sctrl_region1_START (6)
#define SOC_TZPC_DECPROT0STAT_sctrl_region1_END (6)
#define SOC_TZPC_DECPROT0STAT_sctrl_region2_START (7)
#define SOC_TZPC_DECPROT0STAT_sctrl_region2_END (7)
#define SOC_TZPC_DECPROT0STAT_sctrl_region3_START (8)
#define SOC_TZPC_DECPROT0STAT_sctrl_region3_END (8)
#define SOC_TZPC_DECPROT0STAT_sctrl_region4_START (9)
#define SOC_TZPC_DECPROT0STAT_sctrl_region4_END (9)
#define SOC_TZPC_DECPROT0STAT_gpio22_START (10)
#define SOC_TZPC_DECPROT0STAT_gpio22_END (10)
#define SOC_TZPC_DECPROT0STAT_gpio23_START (11)
#define SOC_TZPC_DECPROT0STAT_gpio23_END (11)
#define SOC_TZPC_DECPROT0STAT_gpio24_START (12)
#define SOC_TZPC_DECPROT0STAT_gpio24_END (12)
#define SOC_TZPC_DECPROT0STAT_gpio25_START (13)
#define SOC_TZPC_DECPROT0STAT_gpio25_END (13)
#define SOC_TZPC_DECPROT0STAT_gpio26_START (14)
#define SOC_TZPC_DECPROT0STAT_gpio26_END (14)
#define SOC_TZPC_DECPROT0STAT_gpio27_START (15)
#define SOC_TZPC_DECPROT0STAT_gpio27_END (15)
#define SOC_TZPC_DECPROT0STAT_ao_ioc_START (16)
#define SOC_TZPC_DECPROT0STAT_ao_ioc_END (16)
#define SOC_TZPC_DECPROT0STAT_bb_drx_START (17)
#define SOC_TZPC_DECPROT0STAT_bb_drx_END (17)
#define SOC_TZPC_DECPROT0STAT_time0_START (18)
#define SOC_TZPC_DECPROT0STAT_time0_END (18)
#define SOC_TZPC_DECPROT0STAT_time1_START (19)
#define SOC_TZPC_DECPROT0STAT_time1_END (19)
#define SOC_TZPC_DECPROT0STAT_time2_START (20)
#define SOC_TZPC_DECPROT0STAT_time2_END (20)
#define SOC_TZPC_DECPROT0STAT_time3_START (21)
#define SOC_TZPC_DECPROT0STAT_time3_END (21)
#define SOC_TZPC_DECPROT0STAT_time4_START (22)
#define SOC_TZPC_DECPROT0STAT_time4_END (22)
#define SOC_TZPC_DECPROT0STAT_time5_START (23)
#define SOC_TZPC_DECPROT0STAT_time5_END (23)
#define SOC_TZPC_DECPROT0STAT_time6_START (24)
#define SOC_TZPC_DECPROT0STAT_time6_END (24)
#define SOC_TZPC_DECPROT0STAT_time7_START (25)
#define SOC_TZPC_DECPROT0STAT_time7_END (25)
#define SOC_TZPC_DECPROT0STAT_time8_START (26)
#define SOC_TZPC_DECPROT0STAT_time8_END (26)
#define SOC_TZPC_DECPROT0STAT_mmbuf_START (27)
#define SOC_TZPC_DECPROT0STAT_mmbuf_END (27)
#define SOC_TZPC_DECPROT0STAT_asc_START (28)
#define SOC_TZPC_DECPROT0STAT_asc_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int efusec : 1;
        unsigned int rtc0 : 1;
        unsigned int rtc1 : 1;
        unsigned int sci0 : 1;
        unsigned int sci1 : 1;
        unsigned int syscnt : 1;
        unsigned int sctrl_region1 : 1;
        unsigned int sctrl_region2 : 1;
        unsigned int sctrl_region3 : 1;
        unsigned int sctrl_region4 : 1;
        unsigned int gpio22 : 1;
        unsigned int gpio23 : 1;
        unsigned int gpio24 : 1;
        unsigned int gpio25 : 1;
        unsigned int gpio26 : 1;
        unsigned int gpio27 : 1;
        unsigned int ao_ioc : 1;
        unsigned int bb_drx : 1;
        unsigned int time0 : 1;
        unsigned int time1 : 1;
        unsigned int time2 : 1;
        unsigned int time3 : 1;
        unsigned int time4 : 1;
        unsigned int time5 : 1;
        unsigned int time6 : 1;
        unsigned int time7 : 1;
        unsigned int time8 : 1;
        unsigned int mmbuf : 1;
        unsigned int asc : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
    } reg;
} SOC_TZPC_DECPROT0SET_UNION;
#endif
#define SOC_TZPC_DECPROT0SET_efusec_START (0)
#define SOC_TZPC_DECPROT0SET_efusec_END (0)
#define SOC_TZPC_DECPROT0SET_rtc0_START (1)
#define SOC_TZPC_DECPROT0SET_rtc0_END (1)
#define SOC_TZPC_DECPROT0SET_rtc1_START (2)
#define SOC_TZPC_DECPROT0SET_rtc1_END (2)
#define SOC_TZPC_DECPROT0SET_sci0_START (3)
#define SOC_TZPC_DECPROT0SET_sci0_END (3)
#define SOC_TZPC_DECPROT0SET_sci1_START (4)
#define SOC_TZPC_DECPROT0SET_sci1_END (4)
#define SOC_TZPC_DECPROT0SET_syscnt_START (5)
#define SOC_TZPC_DECPROT0SET_syscnt_END (5)
#define SOC_TZPC_DECPROT0SET_sctrl_region1_START (6)
#define SOC_TZPC_DECPROT0SET_sctrl_region1_END (6)
#define SOC_TZPC_DECPROT0SET_sctrl_region2_START (7)
#define SOC_TZPC_DECPROT0SET_sctrl_region2_END (7)
#define SOC_TZPC_DECPROT0SET_sctrl_region3_START (8)
#define SOC_TZPC_DECPROT0SET_sctrl_region3_END (8)
#define SOC_TZPC_DECPROT0SET_sctrl_region4_START (9)
#define SOC_TZPC_DECPROT0SET_sctrl_region4_END (9)
#define SOC_TZPC_DECPROT0SET_gpio22_START (10)
#define SOC_TZPC_DECPROT0SET_gpio22_END (10)
#define SOC_TZPC_DECPROT0SET_gpio23_START (11)
#define SOC_TZPC_DECPROT0SET_gpio23_END (11)
#define SOC_TZPC_DECPROT0SET_gpio24_START (12)
#define SOC_TZPC_DECPROT0SET_gpio24_END (12)
#define SOC_TZPC_DECPROT0SET_gpio25_START (13)
#define SOC_TZPC_DECPROT0SET_gpio25_END (13)
#define SOC_TZPC_DECPROT0SET_gpio26_START (14)
#define SOC_TZPC_DECPROT0SET_gpio26_END (14)
#define SOC_TZPC_DECPROT0SET_gpio27_START (15)
#define SOC_TZPC_DECPROT0SET_gpio27_END (15)
#define SOC_TZPC_DECPROT0SET_ao_ioc_START (16)
#define SOC_TZPC_DECPROT0SET_ao_ioc_END (16)
#define SOC_TZPC_DECPROT0SET_bb_drx_START (17)
#define SOC_TZPC_DECPROT0SET_bb_drx_END (17)
#define SOC_TZPC_DECPROT0SET_time0_START (18)
#define SOC_TZPC_DECPROT0SET_time0_END (18)
#define SOC_TZPC_DECPROT0SET_time1_START (19)
#define SOC_TZPC_DECPROT0SET_time1_END (19)
#define SOC_TZPC_DECPROT0SET_time2_START (20)
#define SOC_TZPC_DECPROT0SET_time2_END (20)
#define SOC_TZPC_DECPROT0SET_time3_START (21)
#define SOC_TZPC_DECPROT0SET_time3_END (21)
#define SOC_TZPC_DECPROT0SET_time4_START (22)
#define SOC_TZPC_DECPROT0SET_time4_END (22)
#define SOC_TZPC_DECPROT0SET_time5_START (23)
#define SOC_TZPC_DECPROT0SET_time5_END (23)
#define SOC_TZPC_DECPROT0SET_time6_START (24)
#define SOC_TZPC_DECPROT0SET_time6_END (24)
#define SOC_TZPC_DECPROT0SET_time7_START (25)
#define SOC_TZPC_DECPROT0SET_time7_END (25)
#define SOC_TZPC_DECPROT0SET_time8_START (26)
#define SOC_TZPC_DECPROT0SET_time8_END (26)
#define SOC_TZPC_DECPROT0SET_mmbuf_START (27)
#define SOC_TZPC_DECPROT0SET_mmbuf_END (27)
#define SOC_TZPC_DECPROT0SET_asc_START (28)
#define SOC_TZPC_DECPROT0SET_asc_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int efusec : 1;
        unsigned int rtc0 : 1;
        unsigned int rtc1 : 1;
        unsigned int sci0 : 1;
        unsigned int sci1 : 1;
        unsigned int syscnt : 1;
        unsigned int sctrl_region1 : 1;
        unsigned int sctrl_region2 : 1;
        unsigned int sctrl_region3 : 1;
        unsigned int sctrl_region4 : 1;
        unsigned int gpio22 : 1;
        unsigned int gpio23 : 1;
        unsigned int gpio24 : 1;
        unsigned int gpio25 : 1;
        unsigned int gpio26 : 1;
        unsigned int gpio27 : 1;
        unsigned int ao_ioc : 1;
        unsigned int bb_drx : 1;
        unsigned int time0 : 1;
        unsigned int time1 : 1;
        unsigned int time2 : 1;
        unsigned int time3 : 1;
        unsigned int time4 : 1;
        unsigned int time5 : 1;
        unsigned int time6 : 1;
        unsigned int time7 : 1;
        unsigned int time8 : 1;
        unsigned int mmbuf : 1;
        unsigned int asc : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
    } reg;
} SOC_TZPC_DECPROT0CLR_UNION;
#endif
#define SOC_TZPC_DECPROT0CLR_efusec_START (0)
#define SOC_TZPC_DECPROT0CLR_efusec_END (0)
#define SOC_TZPC_DECPROT0CLR_rtc0_START (1)
#define SOC_TZPC_DECPROT0CLR_rtc0_END (1)
#define SOC_TZPC_DECPROT0CLR_rtc1_START (2)
#define SOC_TZPC_DECPROT0CLR_rtc1_END (2)
#define SOC_TZPC_DECPROT0CLR_sci0_START (3)
#define SOC_TZPC_DECPROT0CLR_sci0_END (3)
#define SOC_TZPC_DECPROT0CLR_sci1_START (4)
#define SOC_TZPC_DECPROT0CLR_sci1_END (4)
#define SOC_TZPC_DECPROT0CLR_syscnt_START (5)
#define SOC_TZPC_DECPROT0CLR_syscnt_END (5)
#define SOC_TZPC_DECPROT0CLR_sctrl_region1_START (6)
#define SOC_TZPC_DECPROT0CLR_sctrl_region1_END (6)
#define SOC_TZPC_DECPROT0CLR_sctrl_region2_START (7)
#define SOC_TZPC_DECPROT0CLR_sctrl_region2_END (7)
#define SOC_TZPC_DECPROT0CLR_sctrl_region3_START (8)
#define SOC_TZPC_DECPROT0CLR_sctrl_region3_END (8)
#define SOC_TZPC_DECPROT0CLR_sctrl_region4_START (9)
#define SOC_TZPC_DECPROT0CLR_sctrl_region4_END (9)
#define SOC_TZPC_DECPROT0CLR_gpio22_START (10)
#define SOC_TZPC_DECPROT0CLR_gpio22_END (10)
#define SOC_TZPC_DECPROT0CLR_gpio23_START (11)
#define SOC_TZPC_DECPROT0CLR_gpio23_END (11)
#define SOC_TZPC_DECPROT0CLR_gpio24_START (12)
#define SOC_TZPC_DECPROT0CLR_gpio24_END (12)
#define SOC_TZPC_DECPROT0CLR_gpio25_START (13)
#define SOC_TZPC_DECPROT0CLR_gpio25_END (13)
#define SOC_TZPC_DECPROT0CLR_gpio26_START (14)
#define SOC_TZPC_DECPROT0CLR_gpio26_END (14)
#define SOC_TZPC_DECPROT0CLR_gpio27_START (15)
#define SOC_TZPC_DECPROT0CLR_gpio27_END (15)
#define SOC_TZPC_DECPROT0CLR_ao_ioc_START (16)
#define SOC_TZPC_DECPROT0CLR_ao_ioc_END (16)
#define SOC_TZPC_DECPROT0CLR_bb_drx_START (17)
#define SOC_TZPC_DECPROT0CLR_bb_drx_END (17)
#define SOC_TZPC_DECPROT0CLR_time0_START (18)
#define SOC_TZPC_DECPROT0CLR_time0_END (18)
#define SOC_TZPC_DECPROT0CLR_time1_START (19)
#define SOC_TZPC_DECPROT0CLR_time1_END (19)
#define SOC_TZPC_DECPROT0CLR_time2_START (20)
#define SOC_TZPC_DECPROT0CLR_time2_END (20)
#define SOC_TZPC_DECPROT0CLR_time3_START (21)
#define SOC_TZPC_DECPROT0CLR_time3_END (21)
#define SOC_TZPC_DECPROT0CLR_time4_START (22)
#define SOC_TZPC_DECPROT0CLR_time4_END (22)
#define SOC_TZPC_DECPROT0CLR_time5_START (23)
#define SOC_TZPC_DECPROT0CLR_time5_END (23)
#define SOC_TZPC_DECPROT0CLR_time6_START (24)
#define SOC_TZPC_DECPROT0CLR_time6_END (24)
#define SOC_TZPC_DECPROT0CLR_time7_START (25)
#define SOC_TZPC_DECPROT0CLR_time7_END (25)
#define SOC_TZPC_DECPROT0CLR_time8_START (26)
#define SOC_TZPC_DECPROT0CLR_time8_END (26)
#define SOC_TZPC_DECPROT0CLR_mmbuf_START (27)
#define SOC_TZPC_DECPROT0CLR_mmbuf_END (27)
#define SOC_TZPC_DECPROT0CLR_asc_START (28)
#define SOC_TZPC_DECPROT0CLR_asc_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int timer9 : 1;
        unsigned int timer10 : 1;
        unsigned int timer11 : 1;
        unsigned int timer12 : 1;
        unsigned int pctrl_region1 : 1;
        unsigned int pctrl_region2 : 1;
        unsigned int pctrl_region3 : 1;
        unsigned int pctrl_region4 : 1;
        unsigned int pwm : 1;
        unsigned int reserved_2 : 1;
        unsigned int watchdog0 : 1;
        unsigned int watchdog1 : 1;
        unsigned int gpio0 : 1;
        unsigned int gpio1 : 1;
        unsigned int gpio2 : 1;
        unsigned int gpio3 : 1;
        unsigned int gpio4 : 1;
        unsigned int gpio5 : 1;
        unsigned int gpio6 : 1;
        unsigned int gpio7 : 1;
        unsigned int gpio8 : 1;
        unsigned int gpio9 : 1;
        unsigned int gpio10 : 1;
        unsigned int gpio11 : 1;
        unsigned int gpio12 : 1;
        unsigned int gpio13 : 1;
        unsigned int gpio14 : 1;
        unsigned int gpio15 : 1;
        unsigned int gpio16 : 1;
        unsigned int gpio17 : 1;
    } reg;
} SOC_TZPC_DECPROT1STAT_UNION;
#endif
#define SOC_TZPC_DECPROT1STAT_timer9_START (2)
#define SOC_TZPC_DECPROT1STAT_timer9_END (2)
#define SOC_TZPC_DECPROT1STAT_timer10_START (3)
#define SOC_TZPC_DECPROT1STAT_timer10_END (3)
#define SOC_TZPC_DECPROT1STAT_timer11_START (4)
#define SOC_TZPC_DECPROT1STAT_timer11_END (4)
#define SOC_TZPC_DECPROT1STAT_timer12_START (5)
#define SOC_TZPC_DECPROT1STAT_timer12_END (5)
#define SOC_TZPC_DECPROT1STAT_pctrl_region1_START (6)
#define SOC_TZPC_DECPROT1STAT_pctrl_region1_END (6)
#define SOC_TZPC_DECPROT1STAT_pctrl_region2_START (7)
#define SOC_TZPC_DECPROT1STAT_pctrl_region2_END (7)
#define SOC_TZPC_DECPROT1STAT_pctrl_region3_START (8)
#define SOC_TZPC_DECPROT1STAT_pctrl_region3_END (8)
#define SOC_TZPC_DECPROT1STAT_pctrl_region4_START (9)
#define SOC_TZPC_DECPROT1STAT_pctrl_region4_END (9)
#define SOC_TZPC_DECPROT1STAT_pwm_START (10)
#define SOC_TZPC_DECPROT1STAT_pwm_END (10)
#define SOC_TZPC_DECPROT1STAT_watchdog0_START (12)
#define SOC_TZPC_DECPROT1STAT_watchdog0_END (12)
#define SOC_TZPC_DECPROT1STAT_watchdog1_START (13)
#define SOC_TZPC_DECPROT1STAT_watchdog1_END (13)
#define SOC_TZPC_DECPROT1STAT_gpio0_START (14)
#define SOC_TZPC_DECPROT1STAT_gpio0_END (14)
#define SOC_TZPC_DECPROT1STAT_gpio1_START (15)
#define SOC_TZPC_DECPROT1STAT_gpio1_END (15)
#define SOC_TZPC_DECPROT1STAT_gpio2_START (16)
#define SOC_TZPC_DECPROT1STAT_gpio2_END (16)
#define SOC_TZPC_DECPROT1STAT_gpio3_START (17)
#define SOC_TZPC_DECPROT1STAT_gpio3_END (17)
#define SOC_TZPC_DECPROT1STAT_gpio4_START (18)
#define SOC_TZPC_DECPROT1STAT_gpio4_END (18)
#define SOC_TZPC_DECPROT1STAT_gpio5_START (19)
#define SOC_TZPC_DECPROT1STAT_gpio5_END (19)
#define SOC_TZPC_DECPROT1STAT_gpio6_START (20)
#define SOC_TZPC_DECPROT1STAT_gpio6_END (20)
#define SOC_TZPC_DECPROT1STAT_gpio7_START (21)
#define SOC_TZPC_DECPROT1STAT_gpio7_END (21)
#define SOC_TZPC_DECPROT1STAT_gpio8_START (22)
#define SOC_TZPC_DECPROT1STAT_gpio8_END (22)
#define SOC_TZPC_DECPROT1STAT_gpio9_START (23)
#define SOC_TZPC_DECPROT1STAT_gpio9_END (23)
#define SOC_TZPC_DECPROT1STAT_gpio10_START (24)
#define SOC_TZPC_DECPROT1STAT_gpio10_END (24)
#define SOC_TZPC_DECPROT1STAT_gpio11_START (25)
#define SOC_TZPC_DECPROT1STAT_gpio11_END (25)
#define SOC_TZPC_DECPROT1STAT_gpio12_START (26)
#define SOC_TZPC_DECPROT1STAT_gpio12_END (26)
#define SOC_TZPC_DECPROT1STAT_gpio13_START (27)
#define SOC_TZPC_DECPROT1STAT_gpio13_END (27)
#define SOC_TZPC_DECPROT1STAT_gpio14_START (28)
#define SOC_TZPC_DECPROT1STAT_gpio14_END (28)
#define SOC_TZPC_DECPROT1STAT_gpio15_START (29)
#define SOC_TZPC_DECPROT1STAT_gpio15_END (29)
#define SOC_TZPC_DECPROT1STAT_gpio16_START (30)
#define SOC_TZPC_DECPROT1STAT_gpio16_END (30)
#define SOC_TZPC_DECPROT1STAT_gpio17_START (31)
#define SOC_TZPC_DECPROT1STAT_gpio17_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int timer9 : 1;
        unsigned int timer10 : 1;
        unsigned int timer11 : 1;
        unsigned int timer12 : 1;
        unsigned int pctrl_region1 : 1;
        unsigned int pctrl_region2 : 1;
        unsigned int pctrl_region3 : 1;
        unsigned int pctrl_region4 : 1;
        unsigned int pwm : 1;
        unsigned int reserved_2 : 1;
        unsigned int watchdog0 : 1;
        unsigned int watchdog1 : 1;
        unsigned int gpio0 : 1;
        unsigned int gpio1 : 1;
        unsigned int gpio2 : 1;
        unsigned int gpio3 : 1;
        unsigned int gpio4 : 1;
        unsigned int gpio5 : 1;
        unsigned int gpio6 : 1;
        unsigned int gpio7 : 1;
        unsigned int gpio8 : 1;
        unsigned int gpio9 : 1;
        unsigned int gpio10 : 1;
        unsigned int gpio11 : 1;
        unsigned int gpio12 : 1;
        unsigned int gpio13 : 1;
        unsigned int gpio14 : 1;
        unsigned int gpio15 : 1;
        unsigned int gpio16 : 1;
        unsigned int gpio17 : 1;
    } reg;
} SOC_TZPC_DECPROT1SET_UNION;
#endif
#define SOC_TZPC_DECPROT1SET_timer9_START (2)
#define SOC_TZPC_DECPROT1SET_timer9_END (2)
#define SOC_TZPC_DECPROT1SET_timer10_START (3)
#define SOC_TZPC_DECPROT1SET_timer10_END (3)
#define SOC_TZPC_DECPROT1SET_timer11_START (4)
#define SOC_TZPC_DECPROT1SET_timer11_END (4)
#define SOC_TZPC_DECPROT1SET_timer12_START (5)
#define SOC_TZPC_DECPROT1SET_timer12_END (5)
#define SOC_TZPC_DECPROT1SET_pctrl_region1_START (6)
#define SOC_TZPC_DECPROT1SET_pctrl_region1_END (6)
#define SOC_TZPC_DECPROT1SET_pctrl_region2_START (7)
#define SOC_TZPC_DECPROT1SET_pctrl_region2_END (7)
#define SOC_TZPC_DECPROT1SET_pctrl_region3_START (8)
#define SOC_TZPC_DECPROT1SET_pctrl_region3_END (8)
#define SOC_TZPC_DECPROT1SET_pctrl_region4_START (9)
#define SOC_TZPC_DECPROT1SET_pctrl_region4_END (9)
#define SOC_TZPC_DECPROT1SET_pwm_START (10)
#define SOC_TZPC_DECPROT1SET_pwm_END (10)
#define SOC_TZPC_DECPROT1SET_watchdog0_START (12)
#define SOC_TZPC_DECPROT1SET_watchdog0_END (12)
#define SOC_TZPC_DECPROT1SET_watchdog1_START (13)
#define SOC_TZPC_DECPROT1SET_watchdog1_END (13)
#define SOC_TZPC_DECPROT1SET_gpio0_START (14)
#define SOC_TZPC_DECPROT1SET_gpio0_END (14)
#define SOC_TZPC_DECPROT1SET_gpio1_START (15)
#define SOC_TZPC_DECPROT1SET_gpio1_END (15)
#define SOC_TZPC_DECPROT1SET_gpio2_START (16)
#define SOC_TZPC_DECPROT1SET_gpio2_END (16)
#define SOC_TZPC_DECPROT1SET_gpio3_START (17)
#define SOC_TZPC_DECPROT1SET_gpio3_END (17)
#define SOC_TZPC_DECPROT1SET_gpio4_START (18)
#define SOC_TZPC_DECPROT1SET_gpio4_END (18)
#define SOC_TZPC_DECPROT1SET_gpio5_START (19)
#define SOC_TZPC_DECPROT1SET_gpio5_END (19)
#define SOC_TZPC_DECPROT1SET_gpio6_START (20)
#define SOC_TZPC_DECPROT1SET_gpio6_END (20)
#define SOC_TZPC_DECPROT1SET_gpio7_START (21)
#define SOC_TZPC_DECPROT1SET_gpio7_END (21)
#define SOC_TZPC_DECPROT1SET_gpio8_START (22)
#define SOC_TZPC_DECPROT1SET_gpio8_END (22)
#define SOC_TZPC_DECPROT1SET_gpio9_START (23)
#define SOC_TZPC_DECPROT1SET_gpio9_END (23)
#define SOC_TZPC_DECPROT1SET_gpio10_START (24)
#define SOC_TZPC_DECPROT1SET_gpio10_END (24)
#define SOC_TZPC_DECPROT1SET_gpio11_START (25)
#define SOC_TZPC_DECPROT1SET_gpio11_END (25)
#define SOC_TZPC_DECPROT1SET_gpio12_START (26)
#define SOC_TZPC_DECPROT1SET_gpio12_END (26)
#define SOC_TZPC_DECPROT1SET_gpio13_START (27)
#define SOC_TZPC_DECPROT1SET_gpio13_END (27)
#define SOC_TZPC_DECPROT1SET_gpio14_START (28)
#define SOC_TZPC_DECPROT1SET_gpio14_END (28)
#define SOC_TZPC_DECPROT1SET_gpio15_START (29)
#define SOC_TZPC_DECPROT1SET_gpio15_END (29)
#define SOC_TZPC_DECPROT1SET_gpio16_START (30)
#define SOC_TZPC_DECPROT1SET_gpio16_END (30)
#define SOC_TZPC_DECPROT1SET_gpio17_START (31)
#define SOC_TZPC_DECPROT1SET_gpio17_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int timer9 : 1;
        unsigned int timer10 : 1;
        unsigned int timer11 : 1;
        unsigned int timer12 : 1;
        unsigned int pctrl_region1 : 1;
        unsigned int pctrl_region2 : 1;
        unsigned int pctrl_region3 : 1;
        unsigned int pctrl_region4 : 1;
        unsigned int pwm : 1;
        unsigned int reserved_2 : 1;
        unsigned int watchdog0 : 1;
        unsigned int watchdog1 : 1;
        unsigned int gpio0 : 1;
        unsigned int gpio1 : 1;
        unsigned int gpio2 : 1;
        unsigned int gpio3 : 1;
        unsigned int gpio4 : 1;
        unsigned int gpio5 : 1;
        unsigned int gpio6 : 1;
        unsigned int gpio7 : 1;
        unsigned int gpio8 : 1;
        unsigned int gpio9 : 1;
        unsigned int gpio10 : 1;
        unsigned int gpio11 : 1;
        unsigned int gpio12 : 1;
        unsigned int gpio13 : 1;
        unsigned int gpio14 : 1;
        unsigned int gpio15 : 1;
        unsigned int gpio16 : 1;
        unsigned int gpio17 : 1;
    } reg;
} SOC_TZPC_DECPROT1CLR_UNION;
#endif
#define SOC_TZPC_DECPROT1CLR_timer9_START (2)
#define SOC_TZPC_DECPROT1CLR_timer9_END (2)
#define SOC_TZPC_DECPROT1CLR_timer10_START (3)
#define SOC_TZPC_DECPROT1CLR_timer10_END (3)
#define SOC_TZPC_DECPROT1CLR_timer11_START (4)
#define SOC_TZPC_DECPROT1CLR_timer11_END (4)
#define SOC_TZPC_DECPROT1CLR_timer12_START (5)
#define SOC_TZPC_DECPROT1CLR_timer12_END (5)
#define SOC_TZPC_DECPROT1CLR_pctrl_region1_START (6)
#define SOC_TZPC_DECPROT1CLR_pctrl_region1_END (6)
#define SOC_TZPC_DECPROT1CLR_pctrl_region2_START (7)
#define SOC_TZPC_DECPROT1CLR_pctrl_region2_END (7)
#define SOC_TZPC_DECPROT1CLR_pctrl_region3_START (8)
#define SOC_TZPC_DECPROT1CLR_pctrl_region3_END (8)
#define SOC_TZPC_DECPROT1CLR_pctrl_region4_START (9)
#define SOC_TZPC_DECPROT1CLR_pctrl_region4_END (9)
#define SOC_TZPC_DECPROT1CLR_pwm_START (10)
#define SOC_TZPC_DECPROT1CLR_pwm_END (10)
#define SOC_TZPC_DECPROT1CLR_watchdog0_START (12)
#define SOC_TZPC_DECPROT1CLR_watchdog0_END (12)
#define SOC_TZPC_DECPROT1CLR_watchdog1_START (13)
#define SOC_TZPC_DECPROT1CLR_watchdog1_END (13)
#define SOC_TZPC_DECPROT1CLR_gpio0_START (14)
#define SOC_TZPC_DECPROT1CLR_gpio0_END (14)
#define SOC_TZPC_DECPROT1CLR_gpio1_START (15)
#define SOC_TZPC_DECPROT1CLR_gpio1_END (15)
#define SOC_TZPC_DECPROT1CLR_gpio2_START (16)
#define SOC_TZPC_DECPROT1CLR_gpio2_END (16)
#define SOC_TZPC_DECPROT1CLR_gpio3_START (17)
#define SOC_TZPC_DECPROT1CLR_gpio3_END (17)
#define SOC_TZPC_DECPROT1CLR_gpio4_START (18)
#define SOC_TZPC_DECPROT1CLR_gpio4_END (18)
#define SOC_TZPC_DECPROT1CLR_gpio5_START (19)
#define SOC_TZPC_DECPROT1CLR_gpio5_END (19)
#define SOC_TZPC_DECPROT1CLR_gpio6_START (20)
#define SOC_TZPC_DECPROT1CLR_gpio6_END (20)
#define SOC_TZPC_DECPROT1CLR_gpio7_START (21)
#define SOC_TZPC_DECPROT1CLR_gpio7_END (21)
#define SOC_TZPC_DECPROT1CLR_gpio8_START (22)
#define SOC_TZPC_DECPROT1CLR_gpio8_END (22)
#define SOC_TZPC_DECPROT1CLR_gpio9_START (23)
#define SOC_TZPC_DECPROT1CLR_gpio9_END (23)
#define SOC_TZPC_DECPROT1CLR_gpio10_START (24)
#define SOC_TZPC_DECPROT1CLR_gpio10_END (24)
#define SOC_TZPC_DECPROT1CLR_gpio11_START (25)
#define SOC_TZPC_DECPROT1CLR_gpio11_END (25)
#define SOC_TZPC_DECPROT1CLR_gpio12_START (26)
#define SOC_TZPC_DECPROT1CLR_gpio12_END (26)
#define SOC_TZPC_DECPROT1CLR_gpio13_START (27)
#define SOC_TZPC_DECPROT1CLR_gpio13_END (27)
#define SOC_TZPC_DECPROT1CLR_gpio14_START (28)
#define SOC_TZPC_DECPROT1CLR_gpio14_END (28)
#define SOC_TZPC_DECPROT1CLR_gpio15_START (29)
#define SOC_TZPC_DECPROT1CLR_gpio15_END (29)
#define SOC_TZPC_DECPROT1CLR_gpio16_START (30)
#define SOC_TZPC_DECPROT1CLR_gpio16_END (30)
#define SOC_TZPC_DECPROT1CLR_gpio17_START (31)
#define SOC_TZPC_DECPROT1CLR_gpio17_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpio18 : 1;
        unsigned int gpio19 : 1;
        unsigned int gpio20 : 1;
        unsigned int gpio21 : 1;
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
    } reg;
} SOC_TZPC_DECPROT2STAT_UNION;
#endif
#define SOC_TZPC_DECPROT2STAT_gpio18_START (0)
#define SOC_TZPC_DECPROT2STAT_gpio18_END (0)
#define SOC_TZPC_DECPROT2STAT_gpio19_START (1)
#define SOC_TZPC_DECPROT2STAT_gpio19_END (1)
#define SOC_TZPC_DECPROT2STAT_gpio20_START (2)
#define SOC_TZPC_DECPROT2STAT_gpio20_END (2)
#define SOC_TZPC_DECPROT2STAT_gpio21_START (3)
#define SOC_TZPC_DECPROT2STAT_gpio21_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpio18 : 1;
        unsigned int gpio19 : 1;
        unsigned int gpio20 : 1;
        unsigned int gpio21 : 1;
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
    } reg;
} SOC_TZPC_DECPROT2SET_UNION;
#endif
#define SOC_TZPC_DECPROT2SET_gpio18_START (0)
#define SOC_TZPC_DECPROT2SET_gpio18_END (0)
#define SOC_TZPC_DECPROT2SET_gpio19_START (1)
#define SOC_TZPC_DECPROT2SET_gpio19_END (1)
#define SOC_TZPC_DECPROT2SET_gpio20_START (2)
#define SOC_TZPC_DECPROT2SET_gpio20_END (2)
#define SOC_TZPC_DECPROT2SET_gpio21_START (3)
#define SOC_TZPC_DECPROT2SET_gpio21_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int gpio18 : 1;
        unsigned int gpio19 : 1;
        unsigned int gpio20 : 1;
        unsigned int gpio21 : 1;
        unsigned int reserved_0: 1;
        unsigned int reserved_1: 1;
        unsigned int reserved_2: 1;
        unsigned int reserved_3: 1;
        unsigned int reserved_4: 1;
        unsigned int reserved_5: 1;
        unsigned int reserved_6: 1;
        unsigned int reserved_7: 1;
        unsigned int reserved_8: 1;
        unsigned int reserved_9: 1;
        unsigned int reserved_10: 1;
        unsigned int reserved_11: 1;
        unsigned int reserved_12: 1;
        unsigned int reserved_13: 1;
        unsigned int reserved_14: 1;
        unsigned int reserved_15: 1;
        unsigned int reserved_16: 1;
        unsigned int reserved_17: 1;
        unsigned int reserved_18: 1;
        unsigned int reserved_19: 1;
        unsigned int reserved_20: 1;
        unsigned int reserved_21: 1;
        unsigned int reserved_22: 1;
        unsigned int reserved_23: 1;
        unsigned int reserved_24: 1;
        unsigned int reserved_25: 1;
        unsigned int reserved_26: 1;
        unsigned int reserved_27: 1;
    } reg;
} SOC_TZPC_DECPROT2CLR_UNION;
#endif
#define SOC_TZPC_DECPROT2CLR_gpio18_START (0)
#define SOC_TZPC_DECPROT2CLR_gpio18_END (0)
#define SOC_TZPC_DECPROT2CLR_gpio19_START (1)
#define SOC_TZPC_DECPROT2CLR_gpio19_END (1)
#define SOC_TZPC_DECPROT2CLR_gpio20_START (2)
#define SOC_TZPC_DECPROT2CLR_gpio20_END (2)
#define SOC_TZPC_DECPROT2CLR_gpio21_START (3)
#define SOC_TZPC_DECPROT2CLR_gpio21_END (3)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vdec_firewall : 8;
        unsigned int venc_firewall : 8;
        unsigned int hkmem_firewall : 8;
        unsigned int g3d : 1;
        unsigned int reserved_0 : 1;
        unsigned int emmc0 : 1;
        unsigned int emmc1 : 1;
        unsigned int sd30 : 1;
        unsigned int sdio0 : 1;
        unsigned int sdio1 : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_TZPC_DECPROT3STAT_UNION;
#endif
#define SOC_TZPC_DECPROT3STAT_vdec_firewall_START (0)
#define SOC_TZPC_DECPROT3STAT_vdec_firewall_END (7)
#define SOC_TZPC_DECPROT3STAT_venc_firewall_START (8)
#define SOC_TZPC_DECPROT3STAT_venc_firewall_END (15)
#define SOC_TZPC_DECPROT3STAT_hkmem_firewall_START (16)
#define SOC_TZPC_DECPROT3STAT_hkmem_firewall_END (23)
#define SOC_TZPC_DECPROT3STAT_g3d_START (24)
#define SOC_TZPC_DECPROT3STAT_g3d_END (24)
#define SOC_TZPC_DECPROT3STAT_emmc0_START (26)
#define SOC_TZPC_DECPROT3STAT_emmc0_END (26)
#define SOC_TZPC_DECPROT3STAT_emmc1_START (27)
#define SOC_TZPC_DECPROT3STAT_emmc1_END (27)
#define SOC_TZPC_DECPROT3STAT_sd30_START (28)
#define SOC_TZPC_DECPROT3STAT_sd30_END (28)
#define SOC_TZPC_DECPROT3STAT_sdio0_START (29)
#define SOC_TZPC_DECPROT3STAT_sdio0_END (29)
#define SOC_TZPC_DECPROT3STAT_sdio1_START (30)
#define SOC_TZPC_DECPROT3STAT_sdio1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vdec_firewall : 8;
        unsigned int venc_firewall : 8;
        unsigned int hkmem_firewall : 8;
        unsigned int g3d : 1;
        unsigned int reserved_0 : 1;
        unsigned int emmc0 : 1;
        unsigned int emmc1 : 1;
        unsigned int sd30 : 1;
        unsigned int sdio0 : 1;
        unsigned int sdio1 : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_TZPC_DECPROT3SET_UNION;
#endif
#define SOC_TZPC_DECPROT3SET_vdec_firewall_START (0)
#define SOC_TZPC_DECPROT3SET_vdec_firewall_END (7)
#define SOC_TZPC_DECPROT3SET_venc_firewall_START (8)
#define SOC_TZPC_DECPROT3SET_venc_firewall_END (15)
#define SOC_TZPC_DECPROT3SET_hkmem_firewall_START (16)
#define SOC_TZPC_DECPROT3SET_hkmem_firewall_END (23)
#define SOC_TZPC_DECPROT3SET_g3d_START (24)
#define SOC_TZPC_DECPROT3SET_g3d_END (24)
#define SOC_TZPC_DECPROT3SET_emmc0_START (26)
#define SOC_TZPC_DECPROT3SET_emmc0_END (26)
#define SOC_TZPC_DECPROT3SET_emmc1_START (27)
#define SOC_TZPC_DECPROT3SET_emmc1_END (27)
#define SOC_TZPC_DECPROT3SET_sd30_START (28)
#define SOC_TZPC_DECPROT3SET_sd30_END (28)
#define SOC_TZPC_DECPROT3SET_sdio0_START (29)
#define SOC_TZPC_DECPROT3SET_sdio0_END (29)
#define SOC_TZPC_DECPROT3SET_sdio1_START (30)
#define SOC_TZPC_DECPROT3SET_sdio1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vdec_firewall : 8;
        unsigned int venc_firewall : 8;
        unsigned int hkmem_firewall : 8;
        unsigned int g3d : 1;
        unsigned int reserved_0 : 1;
        unsigned int emmc0 : 1;
        unsigned int emmc1 : 1;
        unsigned int sd30 : 1;
        unsigned int sdio0 : 1;
        unsigned int sdio1 : 1;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_TZPC_DECPROT3CLR_UNION;
#endif
#define SOC_TZPC_DECPROT3CLR_vdec_firewall_START (0)
#define SOC_TZPC_DECPROT3CLR_vdec_firewall_END (7)
#define SOC_TZPC_DECPROT3CLR_venc_firewall_START (8)
#define SOC_TZPC_DECPROT3CLR_venc_firewall_END (15)
#define SOC_TZPC_DECPROT3CLR_hkmem_firewall_START (16)
#define SOC_TZPC_DECPROT3CLR_hkmem_firewall_END (23)
#define SOC_TZPC_DECPROT3CLR_g3d_START (24)
#define SOC_TZPC_DECPROT3CLR_g3d_END (24)
#define SOC_TZPC_DECPROT3CLR_emmc0_START (26)
#define SOC_TZPC_DECPROT3CLR_emmc0_END (26)
#define SOC_TZPC_DECPROT3CLR_emmc1_START (27)
#define SOC_TZPC_DECPROT3CLR_emmc1_END (27)
#define SOC_TZPC_DECPROT3CLR_sd30_START (28)
#define SOC_TZPC_DECPROT3CLR_sd30_END (28)
#define SOC_TZPC_DECPROT3CLR_sdio0_START (29)
#define SOC_TZPC_DECPROT3CLR_sdio0_END (29)
#define SOC_TZPC_DECPROT3CLR_sdio1_START (30)
#define SOC_TZPC_DECPROT3CLR_sdio1_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socp : 1;
        unsigned int usb3otg : 1;
        unsigned int usb3otg_bc : 1;
        unsigned int perf_stat : 1;
        unsigned int reserved_0 : 1;
        unsigned int ipcns : 1;
        unsigned int ipc : 1;
        unsigned int ioc : 1;
        unsigned int vcodecbus : 1;
        unsigned int reserved_1 : 1;
        unsigned int hkadc_ssi : 1;
        unsigned int codec_ssi : 1;
        unsigned int reserved_2 : 1;
        unsigned int ipc_mdm : 1;
        unsigned int uart0 : 1;
        unsigned int uart1 : 1;
        unsigned int uart2 : 1;
        unsigned int uart4 : 1;
        unsigned int uart5 : 1;
        unsigned int spi1 : 1;
        unsigned int i2c3 : 1;
        unsigned int i2c4 : 1;
        unsigned int ddrc : 1;
        unsigned int bisr : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10: 1;
    } reg;
} SOC_TZPC_DECPROT4STAT_UNION;
#endif
#define SOC_TZPC_DECPROT4STAT_socp_START (0)
#define SOC_TZPC_DECPROT4STAT_socp_END (0)
#define SOC_TZPC_DECPROT4STAT_usb3otg_START (1)
#define SOC_TZPC_DECPROT4STAT_usb3otg_END (1)
#define SOC_TZPC_DECPROT4STAT_usb3otg_bc_START (2)
#define SOC_TZPC_DECPROT4STAT_usb3otg_bc_END (2)
#define SOC_TZPC_DECPROT4STAT_perf_stat_START (3)
#define SOC_TZPC_DECPROT4STAT_perf_stat_END (3)
#define SOC_TZPC_DECPROT4STAT_ipcns_START (5)
#define SOC_TZPC_DECPROT4STAT_ipcns_END (5)
#define SOC_TZPC_DECPROT4STAT_ipc_START (6)
#define SOC_TZPC_DECPROT4STAT_ipc_END (6)
#define SOC_TZPC_DECPROT4STAT_ioc_START (7)
#define SOC_TZPC_DECPROT4STAT_ioc_END (7)
#define SOC_TZPC_DECPROT4STAT_vcodecbus_START (8)
#define SOC_TZPC_DECPROT4STAT_vcodecbus_END (8)
#define SOC_TZPC_DECPROT4STAT_hkadc_ssi_START (10)
#define SOC_TZPC_DECPROT4STAT_hkadc_ssi_END (10)
#define SOC_TZPC_DECPROT4STAT_codec_ssi_START (11)
#define SOC_TZPC_DECPROT4STAT_codec_ssi_END (11)
#define SOC_TZPC_DECPROT4STAT_ipc_mdm_START (13)
#define SOC_TZPC_DECPROT4STAT_ipc_mdm_END (13)
#define SOC_TZPC_DECPROT4STAT_uart0_START (14)
#define SOC_TZPC_DECPROT4STAT_uart0_END (14)
#define SOC_TZPC_DECPROT4STAT_uart1_START (15)
#define SOC_TZPC_DECPROT4STAT_uart1_END (15)
#define SOC_TZPC_DECPROT4STAT_uart2_START (16)
#define SOC_TZPC_DECPROT4STAT_uart2_END (16)
#define SOC_TZPC_DECPROT4STAT_uart4_START (17)
#define SOC_TZPC_DECPROT4STAT_uart4_END (17)
#define SOC_TZPC_DECPROT4STAT_uart5_START (18)
#define SOC_TZPC_DECPROT4STAT_uart5_END (18)
#define SOC_TZPC_DECPROT4STAT_spi1_START (19)
#define SOC_TZPC_DECPROT4STAT_spi1_END (19)
#define SOC_TZPC_DECPROT4STAT_i2c3_START (20)
#define SOC_TZPC_DECPROT4STAT_i2c3_END (20)
#define SOC_TZPC_DECPROT4STAT_i2c4_START (21)
#define SOC_TZPC_DECPROT4STAT_i2c4_END (21)
#define SOC_TZPC_DECPROT4STAT_ddrc_START (22)
#define SOC_TZPC_DECPROT4STAT_ddrc_END (22)
#define SOC_TZPC_DECPROT4STAT_bisr_START (23)
#define SOC_TZPC_DECPROT4STAT_bisr_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socp : 1;
        unsigned int usb3otg : 1;
        unsigned int usb3otg_bc : 1;
        unsigned int perf_stat : 1;
        unsigned int reserved_0 : 1;
        unsigned int ipcns : 1;
        unsigned int ipc : 1;
        unsigned int ioc : 1;
        unsigned int vcodecbus : 1;
        unsigned int reserved_1 : 1;
        unsigned int hkadc_ssi : 1;
        unsigned int codec_ssi : 1;
        unsigned int reserved_2 : 1;
        unsigned int ipc_mdm : 1;
        unsigned int uart0 : 1;
        unsigned int uart1 : 1;
        unsigned int uart2 : 1;
        unsigned int uart4 : 1;
        unsigned int uart5 : 1;
        unsigned int spi1 : 1;
        unsigned int i2c3 : 1;
        unsigned int i2c4 : 1;
        unsigned int ddrc : 1;
        unsigned int bisr : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10: 1;
    } reg;
} SOC_TZPC_DECPROT4SET_UNION;
#endif
#define SOC_TZPC_DECPROT4SET_socp_START (0)
#define SOC_TZPC_DECPROT4SET_socp_END (0)
#define SOC_TZPC_DECPROT4SET_usb3otg_START (1)
#define SOC_TZPC_DECPROT4SET_usb3otg_END (1)
#define SOC_TZPC_DECPROT4SET_usb3otg_bc_START (2)
#define SOC_TZPC_DECPROT4SET_usb3otg_bc_END (2)
#define SOC_TZPC_DECPROT4SET_perf_stat_START (3)
#define SOC_TZPC_DECPROT4SET_perf_stat_END (3)
#define SOC_TZPC_DECPROT4SET_ipcns_START (5)
#define SOC_TZPC_DECPROT4SET_ipcns_END (5)
#define SOC_TZPC_DECPROT4SET_ipc_START (6)
#define SOC_TZPC_DECPROT4SET_ipc_END (6)
#define SOC_TZPC_DECPROT4SET_ioc_START (7)
#define SOC_TZPC_DECPROT4SET_ioc_END (7)
#define SOC_TZPC_DECPROT4SET_vcodecbus_START (8)
#define SOC_TZPC_DECPROT4SET_vcodecbus_END (8)
#define SOC_TZPC_DECPROT4SET_hkadc_ssi_START (10)
#define SOC_TZPC_DECPROT4SET_hkadc_ssi_END (10)
#define SOC_TZPC_DECPROT4SET_codec_ssi_START (11)
#define SOC_TZPC_DECPROT4SET_codec_ssi_END (11)
#define SOC_TZPC_DECPROT4SET_ipc_mdm_START (13)
#define SOC_TZPC_DECPROT4SET_ipc_mdm_END (13)
#define SOC_TZPC_DECPROT4SET_uart0_START (14)
#define SOC_TZPC_DECPROT4SET_uart0_END (14)
#define SOC_TZPC_DECPROT4SET_uart1_START (15)
#define SOC_TZPC_DECPROT4SET_uart1_END (15)
#define SOC_TZPC_DECPROT4SET_uart2_START (16)
#define SOC_TZPC_DECPROT4SET_uart2_END (16)
#define SOC_TZPC_DECPROT4SET_uart4_START (17)
#define SOC_TZPC_DECPROT4SET_uart4_END (17)
#define SOC_TZPC_DECPROT4SET_uart5_START (18)
#define SOC_TZPC_DECPROT4SET_uart5_END (18)
#define SOC_TZPC_DECPROT4SET_spi1_START (19)
#define SOC_TZPC_DECPROT4SET_spi1_END (19)
#define SOC_TZPC_DECPROT4SET_i2c3_START (20)
#define SOC_TZPC_DECPROT4SET_i2c3_END (20)
#define SOC_TZPC_DECPROT4SET_i2c4_START (21)
#define SOC_TZPC_DECPROT4SET_i2c4_END (21)
#define SOC_TZPC_DECPROT4SET_ddrc_START (22)
#define SOC_TZPC_DECPROT4SET_ddrc_END (22)
#define SOC_TZPC_DECPROT4SET_bisr_START (23)
#define SOC_TZPC_DECPROT4SET_bisr_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int socp : 1;
        unsigned int usb3otg : 1;
        unsigned int usb3otg_bc : 1;
        unsigned int perf_stat : 1;
        unsigned int reserved_0 : 1;
        unsigned int ipcns : 1;
        unsigned int ipc : 1;
        unsigned int ioc : 1;
        unsigned int vcodecbus : 1;
        unsigned int reserved_1 : 1;
        unsigned int hkadc_ssi : 1;
        unsigned int codec_ssi : 1;
        unsigned int reserved_2 : 1;
        unsigned int ipc_mdm : 1;
        unsigned int uart0 : 1;
        unsigned int uart1 : 1;
        unsigned int uart2 : 1;
        unsigned int uart4 : 1;
        unsigned int uart5 : 1;
        unsigned int spi1 : 1;
        unsigned int i2c3 : 1;
        unsigned int i2c4 : 1;
        unsigned int ddrc : 1;
        unsigned int bisr : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10: 1;
    } reg;
} SOC_TZPC_DECPROT4CLR_UNION;
#endif
#define SOC_TZPC_DECPROT4CLR_socp_START (0)
#define SOC_TZPC_DECPROT4CLR_socp_END (0)
#define SOC_TZPC_DECPROT4CLR_usb3otg_START (1)
#define SOC_TZPC_DECPROT4CLR_usb3otg_END (1)
#define SOC_TZPC_DECPROT4CLR_usb3otg_bc_START (2)
#define SOC_TZPC_DECPROT4CLR_usb3otg_bc_END (2)
#define SOC_TZPC_DECPROT4CLR_perf_stat_START (3)
#define SOC_TZPC_DECPROT4CLR_perf_stat_END (3)
#define SOC_TZPC_DECPROT4CLR_ipcns_START (5)
#define SOC_TZPC_DECPROT4CLR_ipcns_END (5)
#define SOC_TZPC_DECPROT4CLR_ipc_START (6)
#define SOC_TZPC_DECPROT4CLR_ipc_END (6)
#define SOC_TZPC_DECPROT4CLR_ioc_START (7)
#define SOC_TZPC_DECPROT4CLR_ioc_END (7)
#define SOC_TZPC_DECPROT4CLR_vcodecbus_START (8)
#define SOC_TZPC_DECPROT4CLR_vcodecbus_END (8)
#define SOC_TZPC_DECPROT4CLR_hkadc_ssi_START (10)
#define SOC_TZPC_DECPROT4CLR_hkadc_ssi_END (10)
#define SOC_TZPC_DECPROT4CLR_codec_ssi_START (11)
#define SOC_TZPC_DECPROT4CLR_codec_ssi_END (11)
#define SOC_TZPC_DECPROT4CLR_ipc_mdm_START (13)
#define SOC_TZPC_DECPROT4CLR_ipc_mdm_END (13)
#define SOC_TZPC_DECPROT4CLR_uart0_START (14)
#define SOC_TZPC_DECPROT4CLR_uart0_END (14)
#define SOC_TZPC_DECPROT4CLR_uart1_START (15)
#define SOC_TZPC_DECPROT4CLR_uart1_END (15)
#define SOC_TZPC_DECPROT4CLR_uart2_START (16)
#define SOC_TZPC_DECPROT4CLR_uart2_END (16)
#define SOC_TZPC_DECPROT4CLR_uart4_START (17)
#define SOC_TZPC_DECPROT4CLR_uart4_END (17)
#define SOC_TZPC_DECPROT4CLR_uart5_START (18)
#define SOC_TZPC_DECPROT4CLR_uart5_END (18)
#define SOC_TZPC_DECPROT4CLR_spi1_START (19)
#define SOC_TZPC_DECPROT4CLR_spi1_END (19)
#define SOC_TZPC_DECPROT4CLR_i2c3_START (20)
#define SOC_TZPC_DECPROT4CLR_i2c3_END (20)
#define SOC_TZPC_DECPROT4CLR_i2c4_START (21)
#define SOC_TZPC_DECPROT4CLR_i2c4_END (21)
#define SOC_TZPC_DECPROT4CLR_ddrc_START (22)
#define SOC_TZPC_DECPROT4CLR_ddrc_END (22)
#define SOC_TZPC_DECPROT4CLR_bisr_START (23)
#define SOC_TZPC_DECPROT4CLR_bisr_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lpm3_pmussi1 : 1;
        unsigned int ddrc : 1;
        unsigned int lpm3_tsensorc : 1;
        unsigned int lpm3_pmc : 1;
        unsigned int lpm3_uart : 1;
        unsigned int lpm3_pmui2c : 1;
        unsigned int lpm3_pmussi0 : 1;
        unsigned int crg_region1 : 1;
        unsigned int crg_region2 : 1;
        unsigned int crg_region3 : 1;
        unsigned int crg_region4 : 1;
        unsigned int crg_region5 : 1;
        unsigned int lpm3_wd : 1;
        unsigned int lpm3_timer : 1;
        unsigned int lpm3_config : 1;
        unsigned int lpm3_nandc : 1;
        unsigned int lpm3_gnspwm : 1;
        unsigned int lpm3_ram : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
    } reg;
} SOC_TZPC_DECPROT5STAT_UNION;
#endif
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi1_START (0)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi1_END (0)
#define SOC_TZPC_DECPROT5STAT_ddrc_START (1)
#define SOC_TZPC_DECPROT5STAT_ddrc_END (1)
#define SOC_TZPC_DECPROT5STAT_lpm3_tsensorc_START (2)
#define SOC_TZPC_DECPROT5STAT_lpm3_tsensorc_END (2)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmc_START (3)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmc_END (3)
#define SOC_TZPC_DECPROT5STAT_lpm3_uart_START (4)
#define SOC_TZPC_DECPROT5STAT_lpm3_uart_END (4)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmui2c_START (5)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmui2c_END (5)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi0_START (6)
#define SOC_TZPC_DECPROT5STAT_lpm3_pmussi0_END (6)
#define SOC_TZPC_DECPROT5STAT_crg_region1_START (7)
#define SOC_TZPC_DECPROT5STAT_crg_region1_END (7)
#define SOC_TZPC_DECPROT5STAT_crg_region2_START (8)
#define SOC_TZPC_DECPROT5STAT_crg_region2_END (8)
#define SOC_TZPC_DECPROT5STAT_crg_region3_START (9)
#define SOC_TZPC_DECPROT5STAT_crg_region3_END (9)
#define SOC_TZPC_DECPROT5STAT_crg_region4_START (10)
#define SOC_TZPC_DECPROT5STAT_crg_region4_END (10)
#define SOC_TZPC_DECPROT5STAT_crg_region5_START (11)
#define SOC_TZPC_DECPROT5STAT_crg_region5_END (11)
#define SOC_TZPC_DECPROT5STAT_lpm3_wd_START (12)
#define SOC_TZPC_DECPROT5STAT_lpm3_wd_END (12)
#define SOC_TZPC_DECPROT5STAT_lpm3_timer_START (13)
#define SOC_TZPC_DECPROT5STAT_lpm3_timer_END (13)
#define SOC_TZPC_DECPROT5STAT_lpm3_config_START (14)
#define SOC_TZPC_DECPROT5STAT_lpm3_config_END (14)
#define SOC_TZPC_DECPROT5STAT_lpm3_nandc_START (15)
#define SOC_TZPC_DECPROT5STAT_lpm3_nandc_END (15)
#define SOC_TZPC_DECPROT5STAT_lpm3_gnspwm_START (16)
#define SOC_TZPC_DECPROT5STAT_lpm3_gnspwm_END (16)
#define SOC_TZPC_DECPROT5STAT_lpm3_ram_START (17)
#define SOC_TZPC_DECPROT5STAT_lpm3_ram_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lpm3_pmussi1 : 1;
        unsigned int ddrc : 1;
        unsigned int lpm3_tsensorc : 1;
        unsigned int lpm3_pmc : 1;
        unsigned int lpm3_uart : 1;
        unsigned int lpm3_pmui2c : 1;
        unsigned int lpm3_pmussi0 : 1;
        unsigned int crg_region1 : 1;
        unsigned int crg_region2 : 1;
        unsigned int crg_region3 : 1;
        unsigned int crg_region4 : 1;
        unsigned int crg_region5 : 1;
        unsigned int lpm3_wd : 1;
        unsigned int lpm3_timer : 1;
        unsigned int lpm3_config : 1;
        unsigned int lpm3_nandc : 1;
        unsigned int lpm3_gnspwm : 1;
        unsigned int lpm3_ram : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
    } reg;
} SOC_TZPC_DECPROT5SET_UNION;
#endif
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi1_START (0)
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi1_END (0)
#define SOC_TZPC_DECPROT5SET_ddrc_START (1)
#define SOC_TZPC_DECPROT5SET_ddrc_END (1)
#define SOC_TZPC_DECPROT5SET_lpm3_tsensorc_START (2)
#define SOC_TZPC_DECPROT5SET_lpm3_tsensorc_END (2)
#define SOC_TZPC_DECPROT5SET_lpm3_pmc_START (3)
#define SOC_TZPC_DECPROT5SET_lpm3_pmc_END (3)
#define SOC_TZPC_DECPROT5SET_lpm3_uart_START (4)
#define SOC_TZPC_DECPROT5SET_lpm3_uart_END (4)
#define SOC_TZPC_DECPROT5SET_lpm3_pmui2c_START (5)
#define SOC_TZPC_DECPROT5SET_lpm3_pmui2c_END (5)
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi0_START (6)
#define SOC_TZPC_DECPROT5SET_lpm3_pmussi0_END (6)
#define SOC_TZPC_DECPROT5SET_crg_region1_START (7)
#define SOC_TZPC_DECPROT5SET_crg_region1_END (7)
#define SOC_TZPC_DECPROT5SET_crg_region2_START (8)
#define SOC_TZPC_DECPROT5SET_crg_region2_END (8)
#define SOC_TZPC_DECPROT5SET_crg_region3_START (9)
#define SOC_TZPC_DECPROT5SET_crg_region3_END (9)
#define SOC_TZPC_DECPROT5SET_crg_region4_START (10)
#define SOC_TZPC_DECPROT5SET_crg_region4_END (10)
#define SOC_TZPC_DECPROT5SET_crg_region5_START (11)
#define SOC_TZPC_DECPROT5SET_crg_region5_END (11)
#define SOC_TZPC_DECPROT5SET_lpm3_wd_START (12)
#define SOC_TZPC_DECPROT5SET_lpm3_wd_END (12)
#define SOC_TZPC_DECPROT5SET_lpm3_timer_START (13)
#define SOC_TZPC_DECPROT5SET_lpm3_timer_END (13)
#define SOC_TZPC_DECPROT5SET_lpm3_config_START (14)
#define SOC_TZPC_DECPROT5SET_lpm3_config_END (14)
#define SOC_TZPC_DECPROT5SET_lpm3_nandc_START (15)
#define SOC_TZPC_DECPROT5SET_lpm3_nandc_END (15)
#define SOC_TZPC_DECPROT5SET_lpm3_gnspwm_START (16)
#define SOC_TZPC_DECPROT5SET_lpm3_gnspwm_END (16)
#define SOC_TZPC_DECPROT5SET_lpm3_ram_START (17)
#define SOC_TZPC_DECPROT5SET_lpm3_ram_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lpm3_pmussi1 : 1;
        unsigned int ddrc : 1;
        unsigned int lpm3_tsensorc : 1;
        unsigned int lpm3_pmc : 1;
        unsigned int lpm3_uart : 1;
        unsigned int lpm3_pmui2c : 1;
        unsigned int lpm3_pmussi0 : 1;
        unsigned int crg_region1 : 1;
        unsigned int crg_region2 : 1;
        unsigned int crg_region3 : 1;
        unsigned int crg_region4 : 1;
        unsigned int crg_region5 : 1;
        unsigned int lpm3_wd : 1;
        unsigned int lpm3_timer : 1;
        unsigned int lpm3_config : 1;
        unsigned int lpm3_nandc : 1;
        unsigned int lpm3_gnspwm : 1;
        unsigned int lpm3_ram : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int reserved_2 : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
    } reg;
} SOC_TZPC_DECPROT5CLR_UNION;
#endif
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi1_START (0)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi1_END (0)
#define SOC_TZPC_DECPROT5CLR_ddrc_START (1)
#define SOC_TZPC_DECPROT5CLR_ddrc_END (1)
#define SOC_TZPC_DECPROT5CLR_lpm3_tsensorc_START (2)
#define SOC_TZPC_DECPROT5CLR_lpm3_tsensorc_END (2)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmc_START (3)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmc_END (3)
#define SOC_TZPC_DECPROT5CLR_lpm3_uart_START (4)
#define SOC_TZPC_DECPROT5CLR_lpm3_uart_END (4)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmui2c_START (5)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmui2c_END (5)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi0_START (6)
#define SOC_TZPC_DECPROT5CLR_lpm3_pmussi0_END (6)
#define SOC_TZPC_DECPROT5CLR_crg_region1_START (7)
#define SOC_TZPC_DECPROT5CLR_crg_region1_END (7)
#define SOC_TZPC_DECPROT5CLR_crg_region2_START (8)
#define SOC_TZPC_DECPROT5CLR_crg_region2_END (8)
#define SOC_TZPC_DECPROT5CLR_crg_region3_START (9)
#define SOC_TZPC_DECPROT5CLR_crg_region3_END (9)
#define SOC_TZPC_DECPROT5CLR_crg_region4_START (10)
#define SOC_TZPC_DECPROT5CLR_crg_region4_END (10)
#define SOC_TZPC_DECPROT5CLR_crg_region5_START (11)
#define SOC_TZPC_DECPROT5CLR_crg_region5_END (11)
#define SOC_TZPC_DECPROT5CLR_lpm3_wd_START (12)
#define SOC_TZPC_DECPROT5CLR_lpm3_wd_END (12)
#define SOC_TZPC_DECPROT5CLR_lpm3_timer_START (13)
#define SOC_TZPC_DECPROT5CLR_lpm3_timer_END (13)
#define SOC_TZPC_DECPROT5CLR_lpm3_config_START (14)
#define SOC_TZPC_DECPROT5CLR_lpm3_config_END (14)
#define SOC_TZPC_DECPROT5CLR_lpm3_nandc_START (15)
#define SOC_TZPC_DECPROT5CLR_lpm3_nandc_END (15)
#define SOC_TZPC_DECPROT5CLR_lpm3_gnspwm_START (16)
#define SOC_TZPC_DECPROT5CLR_lpm3_gnspwm_END (16)
#define SOC_TZPC_DECPROT5CLR_lpm3_ram_START (17)
#define SOC_TZPC_DECPROT5CLR_lpm3_ram_END (17)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lpm3 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int emmc0 : 1;
        unsigned int emmc1 : 1;
        unsigned int sd30 : 1;
        unsigned int sdio0 : 1;
        unsigned int sdio1 : 1;
        unsigned int usb3otg : 1;
        unsigned int g3d : 1;
        unsigned int reserved_2 : 1;
        unsigned int vdec : 1;
        unsigned int venc : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int isp_a7tocfg : 1;
        unsigned int isp_a7_axi_mst : 1;
        unsigned int isp_core_axi_mst : 1;
        unsigned int perf_stat : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
    } reg;
} SOC_TZPC_DECPROT6STAT_UNION;
#endif
#define SOC_TZPC_DECPROT6STAT_lpm3_START (0)
#define SOC_TZPC_DECPROT6STAT_lpm3_END (0)
#define SOC_TZPC_DECPROT6STAT_emmc0_START (3)
#define SOC_TZPC_DECPROT6STAT_emmc0_END (3)
#define SOC_TZPC_DECPROT6STAT_emmc1_START (4)
#define SOC_TZPC_DECPROT6STAT_emmc1_END (4)
#define SOC_TZPC_DECPROT6STAT_sd30_START (5)
#define SOC_TZPC_DECPROT6STAT_sd30_END (5)
#define SOC_TZPC_DECPROT6STAT_sdio0_START (6)
#define SOC_TZPC_DECPROT6STAT_sdio0_END (6)
#define SOC_TZPC_DECPROT6STAT_sdio1_START (7)
#define SOC_TZPC_DECPROT6STAT_sdio1_END (7)
#define SOC_TZPC_DECPROT6STAT_usb3otg_START (8)
#define SOC_TZPC_DECPROT6STAT_usb3otg_END (8)
#define SOC_TZPC_DECPROT6STAT_g3d_START (9)
#define SOC_TZPC_DECPROT6STAT_g3d_END (9)
#define SOC_TZPC_DECPROT6STAT_vdec_START (11)
#define SOC_TZPC_DECPROT6STAT_vdec_END (11)
#define SOC_TZPC_DECPROT6STAT_venc_START (12)
#define SOC_TZPC_DECPROT6STAT_venc_END (12)
#define SOC_TZPC_DECPROT6STAT_isp_a7tocfg_START (15)
#define SOC_TZPC_DECPROT6STAT_isp_a7tocfg_END (15)
#define SOC_TZPC_DECPROT6STAT_isp_a7_axi_mst_START (16)
#define SOC_TZPC_DECPROT6STAT_isp_a7_axi_mst_END (16)
#define SOC_TZPC_DECPROT6STAT_isp_core_axi_mst_START (17)
#define SOC_TZPC_DECPROT6STAT_isp_core_axi_mst_END (17)
#define SOC_TZPC_DECPROT6STAT_perf_stat_START (18)
#define SOC_TZPC_DECPROT6STAT_perf_stat_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lpm3 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int emmc0 : 1;
        unsigned int emmc1 : 1;
        unsigned int sd30 : 1;
        unsigned int sdio0 : 1;
        unsigned int sdio1 : 1;
        unsigned int usb3otg : 1;
        unsigned int g3d : 1;
        unsigned int reserved_2 : 1;
        unsigned int vdec : 1;
        unsigned int venc : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int isp_a7tocfg : 1;
        unsigned int isp_a7_axi_mst : 1;
        unsigned int isp_core_axi_mst : 1;
        unsigned int perf_stat : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
    } reg;
} SOC_TZPC_DECPROT6SET_UNION;
#endif
#define SOC_TZPC_DECPROT6SET_lpm3_START (0)
#define SOC_TZPC_DECPROT6SET_lpm3_END (0)
#define SOC_TZPC_DECPROT6SET_emmc0_START (3)
#define SOC_TZPC_DECPROT6SET_emmc0_END (3)
#define SOC_TZPC_DECPROT6SET_emmc1_START (4)
#define SOC_TZPC_DECPROT6SET_emmc1_END (4)
#define SOC_TZPC_DECPROT6SET_sd30_START (5)
#define SOC_TZPC_DECPROT6SET_sd30_END (5)
#define SOC_TZPC_DECPROT6SET_sdio0_START (6)
#define SOC_TZPC_DECPROT6SET_sdio0_END (6)
#define SOC_TZPC_DECPROT6SET_sdio1_START (7)
#define SOC_TZPC_DECPROT6SET_sdio1_END (7)
#define SOC_TZPC_DECPROT6SET_usb3otg_START (8)
#define SOC_TZPC_DECPROT6SET_usb3otg_END (8)
#define SOC_TZPC_DECPROT6SET_g3d_START (9)
#define SOC_TZPC_DECPROT6SET_g3d_END (9)
#define SOC_TZPC_DECPROT6SET_vdec_START (11)
#define SOC_TZPC_DECPROT6SET_vdec_END (11)
#define SOC_TZPC_DECPROT6SET_venc_START (12)
#define SOC_TZPC_DECPROT6SET_venc_END (12)
#define SOC_TZPC_DECPROT6SET_isp_a7tocfg_START (15)
#define SOC_TZPC_DECPROT6SET_isp_a7tocfg_END (15)
#define SOC_TZPC_DECPROT6SET_isp_a7_axi_mst_START (16)
#define SOC_TZPC_DECPROT6SET_isp_a7_axi_mst_END (16)
#define SOC_TZPC_DECPROT6SET_isp_core_axi_mst_START (17)
#define SOC_TZPC_DECPROT6SET_isp_core_axi_mst_END (17)
#define SOC_TZPC_DECPROT6SET_perf_stat_START (18)
#define SOC_TZPC_DECPROT6SET_perf_stat_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int lpm3 : 1;
        unsigned int reserved_0 : 1;
        unsigned int reserved_1 : 1;
        unsigned int emmc0 : 1;
        unsigned int emmc1 : 1;
        unsigned int sd30 : 1;
        unsigned int sdio0 : 1;
        unsigned int sdio1 : 1;
        unsigned int usb3otg : 1;
        unsigned int g3d : 1;
        unsigned int reserved_2 : 1;
        unsigned int vdec : 1;
        unsigned int venc : 1;
        unsigned int reserved_3 : 1;
        unsigned int reserved_4 : 1;
        unsigned int isp_a7tocfg : 1;
        unsigned int isp_a7_axi_mst : 1;
        unsigned int isp_core_axi_mst : 1;
        unsigned int perf_stat : 1;
        unsigned int reserved_5 : 1;
        unsigned int reserved_6 : 1;
        unsigned int reserved_7 : 1;
        unsigned int reserved_8 : 1;
        unsigned int reserved_9 : 1;
        unsigned int reserved_10 : 1;
        unsigned int reserved_11 : 1;
        unsigned int reserved_12 : 1;
        unsigned int reserved_13 : 1;
        unsigned int reserved_14 : 1;
        unsigned int reserved_15 : 1;
        unsigned int reserved_16 : 1;
        unsigned int reserved_17 : 1;
    } reg;
} SOC_TZPC_DECPROT6CLR_UNION;
#endif
#define SOC_TZPC_DECPROT6CLR_lpm3_START (0)
#define SOC_TZPC_DECPROT6CLR_lpm3_END (0)
#define SOC_TZPC_DECPROT6CLR_emmc0_START (3)
#define SOC_TZPC_DECPROT6CLR_emmc0_END (3)
#define SOC_TZPC_DECPROT6CLR_emmc1_START (4)
#define SOC_TZPC_DECPROT6CLR_emmc1_END (4)
#define SOC_TZPC_DECPROT6CLR_sd30_START (5)
#define SOC_TZPC_DECPROT6CLR_sd30_END (5)
#define SOC_TZPC_DECPROT6CLR_sdio0_START (6)
#define SOC_TZPC_DECPROT6CLR_sdio0_END (6)
#define SOC_TZPC_DECPROT6CLR_sdio1_START (7)
#define SOC_TZPC_DECPROT6CLR_sdio1_END (7)
#define SOC_TZPC_DECPROT6CLR_usb3otg_START (8)
#define SOC_TZPC_DECPROT6CLR_usb3otg_END (8)
#define SOC_TZPC_DECPROT6CLR_g3d_START (9)
#define SOC_TZPC_DECPROT6CLR_g3d_END (9)
#define SOC_TZPC_DECPROT6CLR_vdec_START (11)
#define SOC_TZPC_DECPROT6CLR_vdec_END (11)
#define SOC_TZPC_DECPROT6CLR_venc_START (12)
#define SOC_TZPC_DECPROT6CLR_venc_END (12)
#define SOC_TZPC_DECPROT6CLR_isp_a7tocfg_START (15)
#define SOC_TZPC_DECPROT6CLR_isp_a7tocfg_END (15)
#define SOC_TZPC_DECPROT6CLR_isp_a7_axi_mst_START (16)
#define SOC_TZPC_DECPROT6CLR_isp_a7_axi_mst_END (16)
#define SOC_TZPC_DECPROT6CLR_isp_core_axi_mst_START (17)
#define SOC_TZPC_DECPROT6CLR_isp_core_axi_mst_END (17)
#define SOC_TZPC_DECPROT6CLR_perf_stat_START (18)
#define SOC_TZPC_DECPROT6CLR_perf_stat_END (18)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_TZPC_DECPROT7STAT_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_TZPC_DECPROT7SET_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_TZPC_DECPROT7CLR_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vivobus_firewall : 8;
        unsigned int reserved_0 : 23;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_TZPC_DECPROT8STAT_UNION;
#endif
#define SOC_TZPC_DECPROT8STAT_vivobus_firewall_START (0)
#define SOC_TZPC_DECPROT8STAT_vivobus_firewall_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vivobus_firewall : 8;
        unsigned int reserved_0 : 23;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_TZPC_DECPROT8SET_UNION;
#endif
#define SOC_TZPC_DECPROT8SET_vivobus_firewall_START (0)
#define SOC_TZPC_DECPROT8SET_vivobus_firewall_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int vivobus_firewall : 8;
        unsigned int reserved_0 : 23;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_TZPC_DECPROT8CLR_UNION;
#endif
#define SOC_TZPC_DECPROT8CLR_vivobus_firewall_START (0)
#define SOC_TZPC_DECPROT8CLR_vivobus_firewall_END (7)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_TZPC_REG0_STAT_UNION;
#endif
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved : 32;
    } reg;
} SOC_TZPC_REG1_STAT_UNION;
#endif
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
