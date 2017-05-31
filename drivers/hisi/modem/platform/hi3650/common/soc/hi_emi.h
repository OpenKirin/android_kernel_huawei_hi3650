#ifndef __HI_EMI_H__
#define __HI_EMI_H__ 
#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4) 
#endif
#define HI_EMI_SMBIDCYR0_OFFSET (0x0)
#define HI_EMI_SMBWST1R0_OFFSET (0x4)
#define HI_EMI_SMBWST2R0_OFFSET (0x8)
#define HI_EMI_SMBWSTOENR0_OFFSET (0xC)
#define HI_EMI_SMBWSTWENR0_OFFSET (0x10)
#define HI_EMI_SMBCR0_OFFSET (0x14)
#define HI_EMI_SMBSR0_OFFSET (0x18)
typedef union
{
    struct
    {
        unsigned int idcy : 4;
        unsigned int updlyr_l : 7;
        unsigned int dwndlyr_l : 7;
        unsigned int updlyw_l : 7;
        unsigned int dwndlyw_l : 7;
    } bits;
    unsigned int u32;
}HI_EMI_SMBIDCYR0_T;
typedef union
{
    struct
    {
        unsigned int wst1 : 10;
        unsigned int updlyr_h : 3;
        unsigned int dwndlyr_h : 3;
        unsigned int updlyw_h : 3;
        unsigned int dwndlyw_h : 3;
        unsigned int reserved : 10;
    } bits;
    unsigned int u32;
}HI_EMI_SMBWST1R0_T;
typedef union
{
    struct
    {
        unsigned int wst2 : 10;
        unsigned int reserved_1 : 6;
        unsigned int wst3 : 8;
        unsigned int reserved_0 : 8;
    } bits;
    unsigned int u32;
}HI_EMI_SMBWST2R0_T;
typedef union
{
    struct
    {
        unsigned int wstoen : 4;
        unsigned int oendisable : 1;
        unsigned int oendly : 2;
        unsigned int reserved : 25;
    } bits;
    unsigned int u32;
}HI_EMI_SMBWSTOENR0_T;
typedef union
{
    struct
    {
        unsigned int wstwen : 4;
        unsigned int wendly : 2;
        unsigned int wenclocksel : 1;
        unsigned int ebictrl : 1;
        unsigned int reserved : 24;
    } bits;
    unsigned int u32;
}HI_EMI_SMBWSTWENR0_T;
typedef union
{
    struct
    {
        unsigned int rble : 1;
        unsigned int cspol : 1;
        unsigned int wp : 1;
        unsigned int mw : 2;
        unsigned int addr_cnt : 1;
        unsigned int reserved : 26;
    } bits;
    unsigned int u32;
}HI_EMI_SMBCR0_T;
typedef union
{
    struct
    {
        unsigned int hsizeerr : 1;
        unsigned int writeproerr : 1;
        unsigned int reserved : 30;
    } bits;
    unsigned int u32;
}HI_EMI_SMBSR0_T;
HI_SET_GET(hi_emi_smbidcyr0_idcy,idcy,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_updlyr_l,updlyr_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_dwndlyr_l,dwndlyr_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_updlyw_l,updlyw_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbidcyr0_dwndlyw_l,dwndlyw_l,HI_EMI_SMBIDCYR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBIDCYR0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_wst1,wst1,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_updlyr_h,updlyr_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_dwndlyr_h,dwndlyr_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_updlyw_h,updlyw_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_dwndlyw_h,dwndlyw_h,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst1r0_reserved,reserved,HI_EMI_SMBWST1R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST1R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_wst2,wst2,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_reserved_1,reserved_1,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_wst3,wst3,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwst2r0_reserved_0,reserved_0,HI_EMI_SMBWST2R0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWST2R0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_wstoen,wstoen,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_oendisable,oendisable,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_oendly,oendly,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstoenr0_reserved,reserved,HI_EMI_SMBWSTOENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTOENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_wstwen,wstwen,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_wendly,wendly,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_wenclocksel,wenclocksel,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_ebictrl,ebictrl,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbwstwenr0_reserved,reserved,HI_EMI_SMBWSTWENR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBWSTWENR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_rble,rble,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_cspol,cspol,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_wp,wp,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_mw,mw,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_addr_cnt,addr_cnt,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbcr0_reserved,reserved,HI_EMI_SMBCR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBCR0_OFFSET)
HI_SET_GET(hi_emi_smbsr0_hsizeerr,hsizeerr,HI_EMI_SMBSR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBSR0_OFFSET)
HI_SET_GET(hi_emi_smbsr0_writeproerr,writeproerr,HI_EMI_SMBSR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBSR0_OFFSET)
HI_SET_GET(hi_emi_smbsr0_reserved,reserved,HI_EMI_SMBSR0_T,HI_EMI_REGBASE_ADDR, HI_EMI_SMBSR0_OFFSET)
#endif
