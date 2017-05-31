#ifndef __SOC_DSS_OV6_INTERFACE_H__
#define __SOC_DSS_OV6_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_DSS_OV6_OV_SIZE_ADDR(base) ((base) + (0x0000))
#define SOC_DSS_OV6_OV_BG_COLOR_ADDR(base) ((base) + (0x4))
#define SOC_DSS_OV6_DST_STARTPOS_ADDR(base) ((base) + (0x8))
#define SOC_DSS_OV6_DST_ENDPOS_ADDR(base) ((base) + (0xC))
#define SOC_DSS_OV6_OV_GCFG_ADDR(base) ((base) + (0x10))
#define SOC_DSS_OV6_LAYER0_POS_ADDR(base) ((base) + (0x14))
#define SOC_DSS_OV6_LAYER0_SIZE_ADDR(base) ((base) + (0x18))
#define SOC_DSS_OV6_LAYER0_SRCLOKEY_ADDR(base) ((base) + (0x1C))
#define SOC_DSS_OV6_LAYER0_SRCHIKEY_ADDR(base) ((base) + (0x20))
#define SOC_DSS_OV6_LAYER0_DSTLOKEY_ADDR(base) ((base) + (0x24))
#define SOC_DSS_OV6_LAYER0_DSTHIKEY_ADDR(base) ((base) + (0x28))
#define SOC_DSS_OV6_LAYER0_PATTERN_ADDR(base) ((base) + (0x2C))
#define SOC_DSS_OV6_LAYER0_ALPHA_ADDR(base) ((base) + (0x30))
#define SOC_DSS_OV6_LAYER0_CFG_ADDR(base) ((base) + (0x34))
#define SOC_DSS_OV6_LAYER0_PSPOS_ADDR(base) ((base) + (0x38))
#define SOC_DSS_OV6_LAYER0_PEPOS_ADDR(base) ((base) + (0x3C))
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_ADDR(base) ((base) + (0x40))
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_ADDR(base) ((base) + (0x44))
#define SOC_DSS_OV6_LAYER0_ST_INFO_ADDR(base) ((base) + (0x48))
#define SOC_DSS_OV6_LAYER0_IST_INFO_ADDR(base) ((base) + (0x4C))
#define SOC_DSS_OV6_LAYER1_POS_ADDR(base) ((base) + (0x50))
#define SOC_DSS_OV6_LAYER1_SIZE_ADDR(base) ((base) + (0x54))
#define SOC_DSS_OV6_LAYER1_SRCLOKEY_ADDR(base) ((base) + (0x58))
#define SOC_DSS_OV6_LAYER1_SRCHIKEY_ADDR(base) ((base) + (0x5C))
#define SOC_DSS_OV6_LAYER1_DSTLOKEY_ADDR(base) ((base) + (0x60))
#define SOC_DSS_OV6_LAYER1_DSTHIKEY_ADDR(base) ((base) + (0x64))
#define SOC_DSS_OV6_LAYER1_PATTERN_ADDR(base) ((base) + (0x68))
#define SOC_DSS_OV6_LAYER1_ALPHA_ADDR(base) ((base) + (0x6C))
#define SOC_DSS_OV6_LAYER1_CFG_ADDR(base) ((base) + (0x70))
#define SOC_DSS_OV6_LAYER1_PSPOS_ADDR(base) ((base) + (0x74))
#define SOC_DSS_OV6_LAYER1_PEPOS_ADDR(base) ((base) + (0x78))
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_ADDR(base) ((base) + (0x7C))
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_ADDR(base) ((base) + (0x80))
#define SOC_DSS_OV6_LAYER1_ST_INFO_ADDR(base) ((base) + (0x84))
#define SOC_DSS_OV6_LAYER1_IST_INFO_ADDR(base) ((base) + (0x88))
#define SOC_DSS_OV6_LAYER2_POS_ADDR(base) ((base) + (0x8C))
#define SOC_DSS_OV6_LAYER2_SIZE_ADDR(base) ((base) + (0x90))
#define SOC_DSS_OV6_LAYER2_SRCLOKEY_ADDR(base) ((base) + (0x94))
#define SOC_DSS_OV6_LAYER2_SRCHIKEY_ADDR(base) ((base) + (0x98))
#define SOC_DSS_OV6_LAYER2_DSTLOKEY_ADDR(base) ((base) + (0x9C))
#define SOC_DSS_OV6_LAYER2_DSTHIKEY_ADDR(base) ((base) + (0xA0))
#define SOC_DSS_OV6_LAYER2_PATTERN_ADDR(base) ((base) + (0xA4))
#define SOC_DSS_OV6_LAYER2_ALPHA_ADDR(base) ((base) + (0xA8))
#define SOC_DSS_OV6_LAYER2_CFG_ADDR(base) ((base) + (0xAC))
#define SOC_DSS_OV6_LAYER2_PSPOS_ADDR(base) ((base) + (0xB0))
#define SOC_DSS_OV6_LAYER2_PEPOS_ADDR(base) ((base) + (0xB4))
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_ADDR(base) ((base) + (0xB8))
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_ADDR(base) ((base) + (0xBC))
#define SOC_DSS_OV6_LAYER2_ST_INFO_ADDR(base) ((base) + (0xC0))
#define SOC_DSS_OV6_LAYER2_IST_INFO_ADDR(base) ((base) + (0xC4))
#define SOC_DSS_OV6_LAYER3_POS_ADDR(base) ((base) + (0xC8))
#define SOC_DSS_OV6_LAYER3_SIZE_ADDR(base) ((base) + (0xCC))
#define SOC_DSS_OV6_LAYER3_SRCLOKEY_ADDR(base) ((base) + (0xD0))
#define SOC_DSS_OV6_LAYER3_SRCHIKEY_ADDR(base) ((base) + (0xD4))
#define SOC_DSS_OV6_LAYER3_DSTLOKEY_ADDR(base) ((base) + (0xD8))
#define SOC_DSS_OV6_LAYER3_DSTHIKEY_ADDR(base) ((base) + (0xDC))
#define SOC_DSS_OV6_LAYER3_PATTERN_ADDR(base) ((base) + (0xE0))
#define SOC_DSS_OV6_LAYER3_ALPHA_ADDR(base) ((base) + (0xE4))
#define SOC_DSS_OV6_LAYER3_CFG_ADDR(base) ((base) + (0xE8))
#define SOC_DSS_OV6_LAYER3_PSPOS_ADDR(base) ((base) + (0xEC))
#define SOC_DSS_OV6_LAYER3_PEPOS_ADDR(base) ((base) + (0xF0))
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_ADDR(base) ((base) + (0xF4))
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_ADDR(base) ((base) + (0xF8))
#define SOC_DSS_OV6_LAYER3_ST_INFO_ADDR(base) ((base) + (0xFC))
#define SOC_DSS_OV6_LAYER3_IST_INFO_ADDR(base) ((base) + (0x100))
#define SOC_DSS_OV6_LAYER4_POS_ADDR(base) ((base) + (0x104))
#define SOC_DSS_OV6_LAYER4_SIZE_ADDR(base) ((base) + (0x108))
#define SOC_DSS_OV6_LAYER4_SRCLOKEY_ADDR(base) ((base) + (0x10C))
#define SOC_DSS_OV6_LAYER4_SRCHIKEY_ADDR(base) ((base) + (0x110))
#define SOC_DSS_OV6_LAYER4_DSTLOKEY_ADDR(base) ((base) + (0x114))
#define SOC_DSS_OV6_LAYER4_DSTHIKEY_ADDR(base) ((base) + (0x118))
#define SOC_DSS_OV6_LAYER4_PATTERN_ADDR(base) ((base) + (0x11C))
#define SOC_DSS_OV6_LAYER4_ALPHA_ADDR(base) ((base) + (0x120))
#define SOC_DSS_OV6_LAYER4_CFG_ADDR(base) ((base) + (0x124))
#define SOC_DSS_OV6_LAYER4_PSPOS_ADDR(base) ((base) + (0x128))
#define SOC_DSS_OV6_LAYER4_PEPOS_ADDR(base) ((base) + (0x12C))
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_ADDR(base) ((base) + (0x130))
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_ADDR(base) ((base) + (0x134))
#define SOC_DSS_OV6_LAYER4_ST_INFO_ADDR(base) ((base) + (0x138))
#define SOC_DSS_OV6_LAYER4_IST_INFO_ADDR(base) ((base) + (0x13C))
#define SOC_DSS_OV6_LAYER5_POS_ADDR(base) ((base) + (0x140))
#define SOC_DSS_OV6_LAYER5_SIZE_ADDR(base) ((base) + (0x144))
#define SOC_DSS_OV6_LAYER5_SRCLOKEY_ADDR(base) ((base) + (0x148))
#define SOC_DSS_OV6_LAYER5_SRCHIKEY_ADDR(base) ((base) + (0x14C))
#define SOC_DSS_OV6_LAYER5_DSTLOKEY_ADDR(base) ((base) + (0x150))
#define SOC_DSS_OV6_LAYER5_DSTHIKEY_ADDR(base) ((base) + (0x154))
#define SOC_DSS_OV6_LAYER5_PATTERN_ADDR(base) ((base) + (0x158))
#define SOC_DSS_OV6_LAYER5_ALPHA_ADDR(base) ((base) + (0x15C))
#define SOC_DSS_OV6_LAYER5_CFG_ADDR(base) ((base) + (0x160))
#define SOC_DSS_OV6_LAYER5_PSPOS_ADDR(base) ((base) + (0x164))
#define SOC_DSS_OV6_LAYER5_PEPOS_ADDR(base) ((base) + (0x168))
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_ADDR(base) ((base) + (0x16C))
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_ADDR(base) ((base) + (0x170))
#define SOC_DSS_OV6_LAYER5_ST_INFO_ADDR(base) ((base) + (0x174))
#define SOC_DSS_OV6_LAYER5_IST_INFO_ADDR(base) ((base) + (0x178))
#define SOC_DSS_OV6_BASE_ST_INFO_ADDR(base) ((base) + (0x17C))
#define SOC_DSS_OV6_BASE_IST_INFO_ADDR(base) ((base) + (0x180))
#define SOC_DSS_OV6_GATE_CTRL_ADDR(base) ((base) + (0x184))
#define SOC_DSS_OV6_OV_RD_SHADOW_SEL_ADDR(base) ((base) + (0x188))
#define SOC_DSS_OV6_OV_CLK_SEL_ADDR(base) ((base) + (0x018C))
#define SOC_DSS_OV6_OV_CLK_EN_ADDR(base) ((base) + (0x0190))
#define SOC_DSS_OV6_BLOCK_SIZE_ADDR(base) ((base) + (0x01A0))
#define SOC_DSS_OV6_BLOCK_DBG_ADDR(base) ((base) + (0x01A4))
#define SOC_DSS_OV6_REG_DEFAULT_ADDR(base) ((base) + (0x01A8))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int img_width : 15;
        unsigned int reserved_0 : 1;
        unsigned int img_height : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_OV_SIZE_UNION;
#endif
#define SOC_DSS_OV6_OV_SIZE_img_width_START (0)
#define SOC_DSS_OV6_OV_SIZE_img_width_END (14)
#define SOC_DSS_OV6_OV_SIZE_img_height_START (16)
#define SOC_DSS_OV6_OV_SIZE_img_height_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bg_color : 32;
    } reg;
} SOC_DSS_OV6_OV_BG_COLOR_UNION;
#endif
#define SOC_DSS_OV6_OV_BG_COLOR_bg_color_START (0)
#define SOC_DSS_OV6_OV_BG_COLOR_bg_color_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int blayer_startx : 15;
        unsigned int reserved_0 : 1;
        unsigned int blayer_starty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_DST_STARTPOS_UNION;
#endif
#define SOC_DSS_OV6_DST_STARTPOS_blayer_startx_START (0)
#define SOC_DSS_OV6_DST_STARTPOS_blayer_startx_END (14)
#define SOC_DSS_OV6_DST_STARTPOS_blayer_starty_START (16)
#define SOC_DSS_OV6_DST_STARTPOS_blayer_starty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int blayer_endx : 15;
        unsigned int reserved_0 : 1;
        unsigned int blayer_endy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_DST_ENDPOS_UNION;
#endif
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endx_START (0)
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endx_END (14)
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endy_START (16)
#define SOC_DSS_OV6_DST_ENDPOS_blayer_endy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int overlay_enable : 1;
        unsigned int reserved_0 : 7;
        unsigned int reserved_1 : 3;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 2;
        unsigned int blayer_bgcolor_en : 1;
        unsigned int reserved_4 : 3;
        unsigned int p3fmt : 2;
        unsigned int reserved_5 : 2;
        unsigned int p3fmt_enable : 1;
        unsigned int reserved_6 : 7;
    } reg;
} SOC_DSS_OV6_OV_GCFG_UNION;
#endif
#define SOC_DSS_OV6_OV_GCFG_overlay_enable_START (0)
#define SOC_DSS_OV6_OV_GCFG_overlay_enable_END (0)
#define SOC_DSS_OV6_OV_GCFG_blayer_bgcolor_en_START (16)
#define SOC_DSS_OV6_OV_GCFG_blayer_bgcolor_en_END (16)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_START (20)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_END (21)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_enable_START (24)
#define SOC_DSS_OV6_OV_GCFG_p3fmt_enable_END (24)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_startx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer0_starty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER0_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_POS_layer0_startx_START (0)
#define SOC_DSS_OV6_LAYER0_POS_layer0_startx_END (14)
#define SOC_DSS_OV6_LAYER0_POS_layer0_starty_START (16)
#define SOC_DSS_OV6_LAYER0_POS_layer0_starty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_endx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer0_endy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER0_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endx_START (0)
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endx_END (14)
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endy_START (16)
#define SOC_DSS_OV6_LAYER0_SIZE_layer0_endy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_src_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER0_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_SRCLOKEY_layer0_src_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER0_SRCLOKEY_layer0_src_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_src_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER0_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_SRCHIKEY_layer0_src_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER0_SRCHIKEY_layer0_src_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_dst_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER0_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_DSTLOKEY_layer0_dst_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER0_DSTLOKEY_layer0_dst_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_dst_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER0_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_DSTHIKEY_layer0_dst_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER0_DSTHIKEY_layer0_dst_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_pattern : 32;
    } reg;
} SOC_DSS_OV6_LAYER0_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_PATTERN_layer0_pattern_START (0)
#define SOC_DSS_OV6_LAYER0_PATTERN_layer0_pattern_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_dst_global_alpha : 8;
        unsigned int layer0_fix_mode : 1;
        unsigned int layer0_dst_pmode : 1;
        unsigned int layer0_alpha_offdst : 2;
        unsigned int layer0_dst_gmode : 2;
        unsigned int layer0_dst_amode : 2;
        unsigned int layer0_src_global_alpha : 8;
        unsigned int layer0_alpha_smode : 1;
        unsigned int layer0_src_pmode : 1;
        unsigned int layer0_src_lmode : 1;
        unsigned int layer0_alpha_offsrc : 1;
        unsigned int layer0_src_gmode : 2;
        unsigned int layer0_src_amode : 2;
    } reg;
} SOC_DSS_OV6_LAYER0_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_global_alpha_START (0)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_global_alpha_END (7)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_fix_mode_START (8)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_fix_mode_END (8)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_pmode_START (9)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_pmode_END (9)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offdst_START (10)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offdst_END (11)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_gmode_START (12)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_gmode_END (13)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_amode_START (14)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_dst_amode_END (15)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_global_alpha_START (16)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_global_alpha_END (23)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_smode_START (24)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_smode_END (24)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_pmode_START (25)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_pmode_END (25)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_lmode_START (26)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_lmode_END (26)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offsrc_START (27)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_alpha_offsrc_END (27)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_gmode_START (28)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_gmode_END (29)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_amode_START (30)
#define SOC_DSS_OV6_LAYER0_ALPHA_layer0_src_amode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int layer0_trop_en : 1;
        unsigned int layer0_rop_en : 1;
        unsigned int reserved_1 : 2;
        unsigned int layer0_src_cfg : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 3;
        unsigned int reserved_4 : 1;
        unsigned int layer0_auto_nosrc : 1;
        unsigned int reserved_5 : 3;
        unsigned int layer0_trop_code : 4;
        unsigned int layer0_rop_code : 8;
    } reg;
} SOC_DSS_OV6_LAYER0_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_CFG_layer0_enable_START (0)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_enable_END (0)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_en_START (4)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_en_END (4)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_en_START (5)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_en_END (5)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_src_cfg_START (8)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_src_cfg_END (8)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_auto_nosrc_START (16)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_auto_nosrc_END (16)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_code_START (20)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_trop_code_END (23)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_code_START (24)
#define SOC_DSS_OV6_LAYER0_CFG_layer0_rop_code_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_pstartx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer0_pstarty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER0_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstartx_START (0)
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstartx_END (14)
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstarty_START (16)
#define SOC_DSS_OV6_LAYER0_PSPOS_layer0_pstarty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_pendx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer0_pendy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER0_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendx_START (0)
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendx_END (14)
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendy_START (16)
#define SOC_DSS_OV6_LAYER0_PEPOS_layer0_pendy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_frame_end : 1;
        unsigned int layer0_nosrc : 1;
        unsigned int layer0_dstalpha_flag : 1;
        unsigned int layer0_srcalpha_flag : 1;
        unsigned int reserved_0 : 4;
        unsigned int layer0_dstalpha_info : 8;
        unsigned int layer0_srcalpha_info : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_OV6_LAYER0_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_frame_end_START (0)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_frame_end_END (0)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_nosrc_START (1)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_nosrc_END (1)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_flag_START (2)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_flag_END (2)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_flag_START (3)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_flag_END (3)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_info_START (8)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_dstalpha_info_END (15)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_info_START (16)
#define SOC_DSS_OV6_LAYER0_INFO_ALPHA_layer0_srcalpha_info_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_srccolor_flag : 1;
        unsigned int reserved : 7;
        unsigned int layer0_srccolor_info : 24;
    } reg;
} SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_flag_START (0)
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_flag_END (0)
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_info_START (8)
#define SOC_DSS_OV6_LAYER0_INFO_SRCCOLOR_layer0_srccolor_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_stall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER0_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_ST_INFO_layer0_stall_info_START (0)
#define SOC_DSS_OV6_LAYER0_ST_INFO_layer0_stall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer0_istall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER0_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER0_IST_INFO_layer0_istall_info_START (0)
#define SOC_DSS_OV6_LAYER0_IST_INFO_layer0_istall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_startx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer1_starty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER1_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_POS_layer1_startx_START (0)
#define SOC_DSS_OV6_LAYER1_POS_layer1_startx_END (14)
#define SOC_DSS_OV6_LAYER1_POS_layer1_starty_START (16)
#define SOC_DSS_OV6_LAYER1_POS_layer1_starty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_endx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer1_endy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER1_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endx_START (0)
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endx_END (14)
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endy_START (16)
#define SOC_DSS_OV6_LAYER1_SIZE_layer1_endy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_src_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER1_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_SRCLOKEY_layer1_src_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER1_SRCLOKEY_layer1_src_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_src_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER1_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_SRCHIKEY_layer1_src_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER1_SRCHIKEY_layer1_src_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_dst_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER1_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_DSTLOKEY_layer1_dst_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER1_DSTLOKEY_layer1_dst_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_dst_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER1_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_DSTHIKEY_layer1_dst_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER1_DSTHIKEY_layer1_dst_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_pattern : 32;
    } reg;
} SOC_DSS_OV6_LAYER1_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_PATTERN_layer1_pattern_START (0)
#define SOC_DSS_OV6_LAYER1_PATTERN_layer1_pattern_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_dst_global_alpha : 8;
        unsigned int layer1_fix_mode : 1;
        unsigned int layer1_dst_pmode : 1;
        unsigned int layer1_off_dst : 2;
        unsigned int layer1_dst_gmode : 2;
        unsigned int layer1_dst_amode : 2;
        unsigned int layer1_src_global_alpha : 8;
        unsigned int layer1_alpha_smode : 1;
        unsigned int layer1_src_pmode : 1;
        unsigned int layer1_src_lmode : 1;
        unsigned int layer1_off_src : 1;
        unsigned int layer1_src_gmode : 2;
        unsigned int layer1_src_amode : 2;
    } reg;
} SOC_DSS_OV6_LAYER1_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_global_alpha_START (0)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_global_alpha_END (7)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_fix_mode_START (8)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_fix_mode_END (8)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_pmode_START (9)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_pmode_END (9)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_dst_START (10)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_dst_END (11)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_gmode_START (12)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_gmode_END (13)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_amode_START (14)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_dst_amode_END (15)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_global_alpha_START (16)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_global_alpha_END (23)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_alpha_smode_START (24)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_alpha_smode_END (24)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_pmode_START (25)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_pmode_END (25)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_lmode_START (26)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_lmode_END (26)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_src_START (27)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_off_src_END (27)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_gmode_START (28)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_gmode_END (29)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_amode_START (30)
#define SOC_DSS_OV6_LAYER1_ALPHA_layer1_src_amode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int layer1_trop_en : 1;
        unsigned int layer1_rop_en : 1;
        unsigned int reserved_1 : 2;
        unsigned int layer1_src_cfg : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 3;
        unsigned int reserved_4 : 1;
        unsigned int layer1_auto_nosrc : 1;
        unsigned int reserved_5 : 3;
        unsigned int layer1_trop_code : 4;
        unsigned int layer1_rop_code : 8;
    } reg;
} SOC_DSS_OV6_LAYER1_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_CFG_layer1_enable_START (0)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_enable_END (0)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_en_START (4)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_en_END (4)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_en_START (5)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_en_END (5)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_src_cfg_START (8)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_src_cfg_END (8)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_auto_nosrc_START (16)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_auto_nosrc_END (16)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_code_START (20)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_trop_code_END (23)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_code_START (24)
#define SOC_DSS_OV6_LAYER1_CFG_layer1_rop_code_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_pstartx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer1_pstarty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER1_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstartx_START (0)
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstartx_END (14)
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstarty_START (16)
#define SOC_DSS_OV6_LAYER1_PSPOS_layer1_pstarty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_pendx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer1_pendy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER1_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendx_START (0)
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendx_END (14)
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendy_START (16)
#define SOC_DSS_OV6_LAYER1_PEPOS_layer1_pendy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_frame_end : 1;
        unsigned int layer1_nosrc : 1;
        unsigned int layer1_dstalpha_flag : 1;
        unsigned int layer1_srcalpha_flag : 1;
        unsigned int reserved_0 : 4;
        unsigned int layer1_dstalpha_info : 8;
        unsigned int layer1_srcalpha_info : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_OV6_LAYER1_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_frame_end_START (0)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_frame_end_END (0)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_nosrc_START (1)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_nosrc_END (1)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_flag_START (2)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_flag_END (2)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_flag_START (3)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_flag_END (3)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_info_START (8)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_dstalpha_info_END (15)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_info_START (16)
#define SOC_DSS_OV6_LAYER1_INFO_ALPHA_layer1_srcalpha_info_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_srccolor_flag : 1;
        unsigned int reserved : 7;
        unsigned int layer1_srccolor_info : 24;
    } reg;
} SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_flag_START (0)
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_flag_END (0)
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_info_START (8)
#define SOC_DSS_OV6_LAYER1_INFO_SRCCOLOR_layer1_srccolor_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_stall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER1_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_ST_INFO_layer1_stall_info_START (0)
#define SOC_DSS_OV6_LAYER1_ST_INFO_layer1_stall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer1_istall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER1_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER1_IST_INFO_layer1_istall_info_START (0)
#define SOC_DSS_OV6_LAYER1_IST_INFO_layer1_istall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_startx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer2_starty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER2_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_POS_layer2_startx_START (0)
#define SOC_DSS_OV6_LAYER2_POS_layer2_startx_END (14)
#define SOC_DSS_OV6_LAYER2_POS_layer2_starty_START (16)
#define SOC_DSS_OV6_LAYER2_POS_layer2_starty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_endx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer2_endy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER2_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endx_START (0)
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endx_END (14)
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endy_START (16)
#define SOC_DSS_OV6_LAYER2_SIZE_layer2_endy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_src_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER2_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_SRCLOKEY_layer2_src_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER2_SRCLOKEY_layer2_src_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_src_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER2_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_SRCHIKEY_layer2_src_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER2_SRCHIKEY_layer2_src_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_dst_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER2_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_DSTLOKEY_layer2_dst_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER2_DSTLOKEY_layer2_dst_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_dst_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER2_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_DSTHIKEY_layer2_dst_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER2_DSTHIKEY_layer2_dst_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_pattern : 32;
    } reg;
} SOC_DSS_OV6_LAYER2_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_PATTERN_layer2_pattern_START (0)
#define SOC_DSS_OV6_LAYER2_PATTERN_layer2_pattern_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_dst_global_alpha : 8;
        unsigned int layer2_fix_mode : 1;
        unsigned int layer2_dst_pmode : 1;
        unsigned int layer2_off_dst : 2;
        unsigned int layer2_dst_gmode : 2;
        unsigned int layer2_dst_amode : 2;
        unsigned int layer2_src_global_alpha : 8;
        unsigned int layer2_alpha_smode : 1;
        unsigned int layer2_src_pmode : 1;
        unsigned int layer2_src_lmode : 1;
        unsigned int layer2_off_src : 1;
        unsigned int layer2_src_gmode : 2;
        unsigned int layer2_src_amode : 2;
    } reg;
} SOC_DSS_OV6_LAYER2_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_global_alpha_START (0)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_global_alpha_END (7)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_fix_mode_START (8)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_fix_mode_END (8)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_pmode_START (9)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_pmode_END (9)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_dst_START (10)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_dst_END (11)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_gmode_START (12)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_gmode_END (13)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_amode_START (14)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_dst_amode_END (15)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_global_alpha_START (16)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_global_alpha_END (23)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_alpha_smode_START (24)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_alpha_smode_END (24)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_pmode_START (25)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_pmode_END (25)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_lmode_START (26)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_lmode_END (26)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_src_START (27)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_off_src_END (27)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_gmode_START (28)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_gmode_END (29)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_amode_START (30)
#define SOC_DSS_OV6_LAYER2_ALPHA_layer2_src_amode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int layer2_trop_en : 1;
        unsigned int layer2_rop_en : 1;
        unsigned int reserved_1 : 2;
        unsigned int layer2_src_cfg : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 3;
        unsigned int reserved_4 : 1;
        unsigned int layer2_auto_nosrc : 1;
        unsigned int reserved_5 : 3;
        unsigned int layer2_trop_code : 4;
        unsigned int layer2_rop_code : 8;
    } reg;
} SOC_DSS_OV6_LAYER2_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_CFG_layer2_enable_START (0)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_enable_END (0)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_en_START (4)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_en_END (4)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_en_START (5)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_en_END (5)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_src_cfg_START (8)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_src_cfg_END (8)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_auto_nosrc_START (16)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_auto_nosrc_END (16)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_code_START (20)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_trop_code_END (23)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_code_START (24)
#define SOC_DSS_OV6_LAYER2_CFG_layer2_rop_code_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_pstartx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer2_pstarty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER2_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstartx_START (0)
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstartx_END (14)
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstarty_START (16)
#define SOC_DSS_OV6_LAYER2_PSPOS_layer2_pstarty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_pendx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer2_pendy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER2_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendx_START (0)
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendx_END (14)
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendy_START (16)
#define SOC_DSS_OV6_LAYER2_PEPOS_layer2_pendy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_frame_end : 1;
        unsigned int layer2_nosrc : 1;
        unsigned int layer2_dstalpha_flag : 1;
        unsigned int layer2_srcalpha_flag : 1;
        unsigned int reserved_0 : 4;
        unsigned int layer2_dstalpha_info : 8;
        unsigned int layer2_srcalpha_info : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_OV6_LAYER2_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_frame_end_START (0)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_frame_end_END (0)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_nosrc_START (1)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_nosrc_END (1)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_flag_START (2)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_flag_END (2)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_flag_START (3)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_flag_END (3)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_info_START (8)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_dstalpha_info_END (15)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_info_START (16)
#define SOC_DSS_OV6_LAYER2_INFO_ALPHA_layer2_srcalpha_info_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_srccolor_flag : 1;
        unsigned int reserved : 7;
        unsigned int layer2_srccolor_info : 24;
    } reg;
} SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_flag_START (0)
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_flag_END (0)
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_info_START (8)
#define SOC_DSS_OV6_LAYER2_INFO_SRCCOLOR_layer2_srccolor_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_stall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER2_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_ST_INFO_layer2_stall_info_START (0)
#define SOC_DSS_OV6_LAYER2_ST_INFO_layer2_stall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer2_istall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER2_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER2_IST_INFO_layer2_istall_info_START (0)
#define SOC_DSS_OV6_LAYER2_IST_INFO_layer2_istall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_startx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer3_starty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER3_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_POS_layer3_startx_START (0)
#define SOC_DSS_OV6_LAYER3_POS_layer3_startx_END (14)
#define SOC_DSS_OV6_LAYER3_POS_layer3_starty_START (16)
#define SOC_DSS_OV6_LAYER3_POS_layer3_starty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_endx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer3_endy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER3_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endx_START (0)
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endx_END (14)
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endy_START (16)
#define SOC_DSS_OV6_LAYER3_SIZE_layer3_endy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_src_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER3_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_SRCLOKEY_layer3_src_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER3_SRCLOKEY_layer3_src_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_src_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER3_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_SRCHIKEY_layer3_src_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER3_SRCHIKEY_layer3_src_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_dst_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER3_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_DSTLOKEY_layer3_dst_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER3_DSTLOKEY_layer3_dst_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_dst_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER3_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_DSTHIKEY_layer3_dst_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER3_DSTHIKEY_layer3_dst_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_pattern : 32;
    } reg;
} SOC_DSS_OV6_LAYER3_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_PATTERN_layer3_pattern_START (0)
#define SOC_DSS_OV6_LAYER3_PATTERN_layer3_pattern_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_dst_global_alpha : 8;
        unsigned int layer3_fix_mode : 1;
        unsigned int layer3_dst_pmode : 1;
        unsigned int layer3_off_dst : 2;
        unsigned int layer3_dst_gmode : 2;
        unsigned int layer3_dst_amode : 2;
        unsigned int layer3_src_global_alpha : 8;
        unsigned int layer3_alpha_smode : 1;
        unsigned int layer3_src_pmode : 1;
        unsigned int layer3_src_lmode : 1;
        unsigned int layer3_off_src : 1;
        unsigned int layer3_src_gmode : 2;
        unsigned int layer3_src_amode : 2;
    } reg;
} SOC_DSS_OV6_LAYER3_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_global_alpha_START (0)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_global_alpha_END (7)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_fix_mode_START (8)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_fix_mode_END (8)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_pmode_START (9)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_pmode_END (9)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_dst_START (10)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_dst_END (11)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_gmode_START (12)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_gmode_END (13)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_amode_START (14)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_dst_amode_END (15)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_global_alpha_START (16)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_global_alpha_END (23)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_alpha_smode_START (24)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_alpha_smode_END (24)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_pmode_START (25)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_pmode_END (25)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_lmode_START (26)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_lmode_END (26)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_src_START (27)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_off_src_END (27)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_gmode_START (28)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_gmode_END (29)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_amode_START (30)
#define SOC_DSS_OV6_LAYER3_ALPHA_layer3_src_amode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int layer3_trop_en : 1;
        unsigned int layer3_rop_en : 1;
        unsigned int reserved_1 : 2;
        unsigned int layer3_src_cfg : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 3;
        unsigned int reserved_4 : 1;
        unsigned int layer3_auto_nosrc : 1;
        unsigned int reserved_5 : 3;
        unsigned int layer3_trop_code : 4;
        unsigned int layer3_rop_code : 8;
    } reg;
} SOC_DSS_OV6_LAYER3_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_CFG_layer3_enable_START (0)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_enable_END (0)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_en_START (4)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_en_END (4)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_en_START (5)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_en_END (5)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_src_cfg_START (8)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_src_cfg_END (8)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_auto_nosrc_START (16)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_auto_nosrc_END (16)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_code_START (20)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_trop_code_END (23)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_code_START (24)
#define SOC_DSS_OV6_LAYER3_CFG_layer3_rop_code_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_pstartx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer3_pstarty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER3_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstartx_START (0)
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstartx_END (14)
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstarty_START (16)
#define SOC_DSS_OV6_LAYER3_PSPOS_layer3_pstarty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_pendx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer3_pendy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER3_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendx_START (0)
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendx_END (14)
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendy_START (16)
#define SOC_DSS_OV6_LAYER3_PEPOS_layer3_pendy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_frame_end : 1;
        unsigned int layer3_nosrc : 1;
        unsigned int layer3_dstalpha_flag : 1;
        unsigned int layer3_srcalpha_flag : 1;
        unsigned int reserved_0 : 4;
        unsigned int layer3_dstalpha_info : 8;
        unsigned int layer3_srcalpha_info : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_OV6_LAYER3_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_frame_end_START (0)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_frame_end_END (0)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_nosrc_START (1)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_nosrc_END (1)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_flag_START (2)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_flag_END (2)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_flag_START (3)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_flag_END (3)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_info_START (8)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_dstalpha_info_END (15)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_info_START (16)
#define SOC_DSS_OV6_LAYER3_INFO_ALPHA_layer3_srcalpha_info_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_srccolor_flag : 1;
        unsigned int reserved : 7;
        unsigned int layer3_srccolor_info : 24;
    } reg;
} SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_flag_START (0)
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_flag_END (0)
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_info_START (8)
#define SOC_DSS_OV6_LAYER3_INFO_SRCCOLOR_layer3_srccolor_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_stall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER3_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_ST_INFO_layer3_stall_info_START (0)
#define SOC_DSS_OV6_LAYER3_ST_INFO_layer3_stall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer3_istall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER3_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER3_IST_INFO_layer3_istall_info_START (0)
#define SOC_DSS_OV6_LAYER3_IST_INFO_layer3_istall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_startx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer4_starty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER4_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_POS_layer4_startx_START (0)
#define SOC_DSS_OV6_LAYER4_POS_layer4_startx_END (14)
#define SOC_DSS_OV6_LAYER4_POS_layer4_starty_START (16)
#define SOC_DSS_OV6_LAYER4_POS_layer4_starty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_endx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer4_endy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER4_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endx_START (0)
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endx_END (14)
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endy_START (16)
#define SOC_DSS_OV6_LAYER4_SIZE_layer4_endy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_src_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER4_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_SRCLOKEY_layer4_src_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER4_SRCLOKEY_layer4_src_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_src_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER4_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_SRCHIKEY_layer4_src_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER4_SRCHIKEY_layer4_src_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_dst_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER4_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_DSTLOKEY_layer4_dst_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER4_DSTLOKEY_layer4_dst_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_dst_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER4_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_DSTHIKEY_layer4_dst_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER4_DSTHIKEY_layer4_dst_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_pattern : 32;
    } reg;
} SOC_DSS_OV6_LAYER4_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_PATTERN_layer4_pattern_START (0)
#define SOC_DSS_OV6_LAYER4_PATTERN_layer4_pattern_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_dst_global_alpha : 8;
        unsigned int layer4_fix_mode : 1;
        unsigned int layer4_dst_pmode : 1;
        unsigned int layer4_off_dst : 2;
        unsigned int layer4_dst_gmode : 2;
        unsigned int layer4_dst_amode : 2;
        unsigned int layer4_src_global_alpha : 8;
        unsigned int layer4_alpha_smode : 1;
        unsigned int layer4_src_pmode : 1;
        unsigned int layer4_src_lmode : 1;
        unsigned int layer4_off_src : 1;
        unsigned int layer4_src_gmode : 2;
        unsigned int layer4_src_amode : 2;
    } reg;
} SOC_DSS_OV6_LAYER4_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_global_alpha_START (0)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_global_alpha_END (7)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_fix_mode_START (8)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_fix_mode_END (8)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_pmode_START (9)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_pmode_END (9)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_dst_START (10)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_dst_END (11)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_gmode_START (12)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_gmode_END (13)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_amode_START (14)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_dst_amode_END (15)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_global_alpha_START (16)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_global_alpha_END (23)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_alpha_smode_START (24)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_alpha_smode_END (24)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_pmode_START (25)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_pmode_END (25)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_lmode_START (26)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_lmode_END (26)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_src_START (27)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_off_src_END (27)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_gmode_START (28)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_gmode_END (29)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_amode_START (30)
#define SOC_DSS_OV6_LAYER4_ALPHA_layer4_src_amode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int layer4_trop_en : 1;
        unsigned int layer4_rop_en : 1;
        unsigned int reserved_1 : 2;
        unsigned int layer4_src_cfg : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 3;
        unsigned int reserved_4 : 1;
        unsigned int layer4_auto_nosrc : 1;
        unsigned int reserved_5 : 3;
        unsigned int layer4_trop_code : 4;
        unsigned int layer4_rop_code : 8;
    } reg;
} SOC_DSS_OV6_LAYER4_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_CFG_layer4_enable_START (0)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_enable_END (0)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_en_START (4)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_en_END (4)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_en_START (5)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_en_END (5)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_src_cfg_START (8)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_src_cfg_END (8)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_auto_nosrc_START (16)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_auto_nosrc_END (16)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_code_START (20)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_trop_code_END (23)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_code_START (24)
#define SOC_DSS_OV6_LAYER4_CFG_layer4_rop_code_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_pstartx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer4_pstarty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER4_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstartx_START (0)
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstartx_END (14)
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstarty_START (16)
#define SOC_DSS_OV6_LAYER4_PSPOS_layer4_pstarty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_pendx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer4_pendy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER4_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendx_START (0)
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendx_END (14)
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendy_START (16)
#define SOC_DSS_OV6_LAYER4_PEPOS_layer4_pendy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_frame_end : 1;
        unsigned int layer4_nosrc : 1;
        unsigned int layer4_dstalpha_flag : 1;
        unsigned int layer4_srcalpha_flag : 1;
        unsigned int reserved_0 : 4;
        unsigned int layer4_dstalpha_info : 8;
        unsigned int layer4_srcalpha_info : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_OV6_LAYER4_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_frame_end_START (0)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_frame_end_END (0)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_nosrc_START (1)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_nosrc_END (1)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_flag_START (2)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_flag_END (2)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_flag_START (3)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_flag_END (3)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_info_START (8)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_dstalpha_info_END (15)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_info_START (16)
#define SOC_DSS_OV6_LAYER4_INFO_ALPHA_layer4_srcalpha_info_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_srccolor_flag : 1;
        unsigned int reserved : 7;
        unsigned int layer4_srccolor_info : 24;
    } reg;
} SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_flag_START (0)
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_flag_END (0)
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_info_START (8)
#define SOC_DSS_OV6_LAYER4_INFO_SRCCOLOR_layer4_srccolor_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_stall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER4_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_ST_INFO_layer4_stall_info_START (0)
#define SOC_DSS_OV6_LAYER4_ST_INFO_layer4_stall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer4_istall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER4_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER4_IST_INFO_layer4_istall_info_START (0)
#define SOC_DSS_OV6_LAYER4_IST_INFO_layer4_istall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_startx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer5_starty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER5_POS_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_POS_layer5_startx_START (0)
#define SOC_DSS_OV6_LAYER5_POS_layer5_startx_END (14)
#define SOC_DSS_OV6_LAYER5_POS_layer5_starty_START (16)
#define SOC_DSS_OV6_LAYER5_POS_layer5_starty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_endx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer5_endy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER5_SIZE_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endx_START (0)
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endx_END (14)
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endy_START (16)
#define SOC_DSS_OV6_LAYER5_SIZE_layer5_endy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_src_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER5_SRCLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_SRCLOKEY_layer5_src_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER5_SRCLOKEY_layer5_src_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_src_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER5_SRCHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_SRCHIKEY_layer5_src_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER5_SRCHIKEY_layer5_src_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_dst_locolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER5_DSTLOKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_DSTLOKEY_layer5_dst_locolorkey_START (0)
#define SOC_DSS_OV6_LAYER5_DSTLOKEY_layer5_dst_locolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_dst_hicolorkey : 24;
        unsigned int reserved : 8;
    } reg;
} SOC_DSS_OV6_LAYER5_DSTHIKEY_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_DSTHIKEY_layer5_dst_hicolorkey_START (0)
#define SOC_DSS_OV6_LAYER5_DSTHIKEY_layer5_dst_hicolorkey_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_pattern : 32;
    } reg;
} SOC_DSS_OV6_LAYER5_PATTERN_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_PATTERN_layer5_pattern_START (0)
#define SOC_DSS_OV6_LAYER5_PATTERN_layer5_pattern_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_dst_global_alpha : 8;
        unsigned int layer5_fix_mode : 1;
        unsigned int layer5_dst_pmode : 1;
        unsigned int layer5_off_dst : 2;
        unsigned int layer5_dst_gmode : 2;
        unsigned int layer5_dst_amode : 2;
        unsigned int layer5_src_global_alpha : 8;
        unsigned int layer5_alpha_smode : 1;
        unsigned int layer5_src_pmode : 1;
        unsigned int layer5_src_lmode : 1;
        unsigned int layer5_off_src : 1;
        unsigned int layer5_src_gmode : 2;
        unsigned int layer5_src_amode : 2;
    } reg;
} SOC_DSS_OV6_LAYER5_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_global_alpha_START (0)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_global_alpha_END (7)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_fix_mode_START (8)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_fix_mode_END (8)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_pmode_START (9)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_pmode_END (9)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_dst_START (10)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_dst_END (11)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_gmode_START (12)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_gmode_END (13)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_amode_START (14)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_dst_amode_END (15)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_global_alpha_START (16)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_global_alpha_END (23)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_alpha_smode_START (24)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_alpha_smode_END (24)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_pmode_START (25)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_pmode_END (25)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_lmode_START (26)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_lmode_END (26)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_src_START (27)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_off_src_END (27)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_gmode_START (28)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_gmode_END (29)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_amode_START (30)
#define SOC_DSS_OV6_LAYER5_ALPHA_layer5_src_amode_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_enable : 1;
        unsigned int reserved_0 : 3;
        unsigned int layer5_trop_en : 1;
        unsigned int layer5_rop_en : 1;
        unsigned int reserved_1 : 2;
        unsigned int layer5_src_cfg : 1;
        unsigned int reserved_2 : 3;
        unsigned int reserved_3 : 3;
        unsigned int reserved_4 : 1;
        unsigned int layer5_auto_nosrc : 1;
        unsigned int reserved_5 : 3;
        unsigned int layer5_trop_code : 4;
        unsigned int layer5_rop_code : 8;
    } reg;
} SOC_DSS_OV6_LAYER5_CFG_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_CFG_layer5_enable_START (0)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_enable_END (0)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_en_START (4)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_en_END (4)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_en_START (5)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_en_END (5)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_src_cfg_START (8)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_src_cfg_END (8)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_auto_nosrc_START (16)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_auto_nosrc_END (16)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_code_START (20)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_trop_code_END (23)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_code_START (24)
#define SOC_DSS_OV6_LAYER5_CFG_layer5_rop_code_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_pstartx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer5_pstarty : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER5_PSPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstartx_START (0)
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstartx_END (14)
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstarty_START (16)
#define SOC_DSS_OV6_LAYER5_PSPOS_layer5_pstarty_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_pendx : 15;
        unsigned int reserved_0 : 1;
        unsigned int layer5_pendy : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_LAYER5_PEPOS_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendx_START (0)
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendx_END (14)
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendy_START (16)
#define SOC_DSS_OV6_LAYER5_PEPOS_layer5_pendy_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_frame_end : 1;
        unsigned int layer5_nosrc : 1;
        unsigned int layer5_dstalpha_flag : 1;
        unsigned int layer5_srcalpha_flag : 1;
        unsigned int reserved_0 : 4;
        unsigned int layer5_dstalpha_info : 8;
        unsigned int layer5_srcalpha_info : 8;
        unsigned int reserved_1 : 8;
    } reg;
} SOC_DSS_OV6_LAYER5_INFO_ALPHA_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_frame_end_START (0)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_frame_end_END (0)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_nosrc_START (1)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_nosrc_END (1)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_flag_START (2)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_flag_END (2)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_flag_START (3)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_flag_END (3)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_info_START (8)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_dstalpha_info_END (15)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_info_START (16)
#define SOC_DSS_OV6_LAYER5_INFO_ALPHA_layer5_srcalpha_info_END (23)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_srccolor_flag : 1;
        unsigned int reserved : 7;
        unsigned int layer5_srccolor_info : 24;
    } reg;
} SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_flag_START (0)
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_flag_END (0)
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_info_START (8)
#define SOC_DSS_OV6_LAYER5_INFO_SRCCOLOR_layer5_srccolor_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_stall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER5_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_ST_INFO_layer5_stall_info_START (0)
#define SOC_DSS_OV6_LAYER5_ST_INFO_layer5_stall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int layer5_istall_info : 32;
    } reg;
} SOC_DSS_OV6_LAYER5_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_LAYER5_IST_INFO_layer5_istall_info_START (0)
#define SOC_DSS_OV6_LAYER5_IST_INFO_layer5_istall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bs_stall_info : 32;
    } reg;
} SOC_DSS_OV6_BASE_ST_INFO_UNION;
#endif
#define SOC_DSS_OV6_BASE_ST_INFO_bs_stall_info_START (0)
#define SOC_DSS_OV6_BASE_ST_INFO_bs_stall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int bs_istall_info : 32;
    } reg;
} SOC_DSS_OV6_BASE_IST_INFO_UNION;
#endif
#define SOC_DSS_OV6_BASE_IST_INFO_bs_istall_info_START (0)
#define SOC_DSS_OV6_BASE_IST_INFO_bs_istall_info_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov_core_gt : 2;
        unsigned int reserved_0 : 2;
        unsigned int stall_info_en : 1;
        unsigned int reserved_1 : 27;
    } reg;
} SOC_DSS_OV6_GATE_CTRL_UNION;
#endif
#define SOC_DSS_OV6_GATE_CTRL_ov_core_gt_START (0)
#define SOC_DSS_OV6_GATE_CTRL_ov_core_gt_END (1)
#define SOC_DSS_OV6_GATE_CTRL_stall_info_en_START (4)
#define SOC_DSS_OV6_GATE_CTRL_stall_info_en_END (4)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov_rd_shadow_sel : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_OV6_OV_RD_SHADOW_SEL_UNION;
#endif
#define SOC_DSS_OV6_OV_RD_SHADOW_SEL_ov_rd_shadow_sel_START (0)
#define SOC_DSS_OV6_OV_RD_SHADOW_SEL_ov_rd_shadow_sel_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov_clk_sel : 32;
    } reg;
} SOC_DSS_OV6_OV_CLK_SEL_UNION;
#endif
#define SOC_DSS_OV6_OV_CLK_SEL_ov_clk_sel_START (0)
#define SOC_DSS_OV6_OV_CLK_SEL_ov_clk_sel_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int ov_clk_en : 32;
    } reg;
} SOC_DSS_OV6_OV_CLK_EN_UNION;
#endif
#define SOC_DSS_OV6_OV_CLK_EN_ov_clk_en_START (0)
#define SOC_DSS_OV6_OV_CLK_EN_ov_clk_en_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reserved_0 : 16;
        unsigned int block_height : 15;
        unsigned int reserved_1 : 1;
    } reg;
} SOC_DSS_OV6_BLOCK_SIZE_UNION;
#endif
#define SOC_DSS_OV6_BLOCK_SIZE_block_height_START (16)
#define SOC_DSS_OV6_BLOCK_SIZE_block_height_END (30)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int block_dbg : 32;
    } reg;
} SOC_DSS_OV6_BLOCK_DBG_UNION;
#endif
#define SOC_DSS_OV6_BLOCK_DBG_block_dbg_START (0)
#define SOC_DSS_OV6_BLOCK_DBG_block_dbg_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int reg_default : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_DSS_OV6_REG_DEFAULT_UNION;
#endif
#define SOC_DSS_OV6_REG_DEFAULT_reg_default_START (0)
#define SOC_DSS_OV6_REG_DEFAULT_reg_default_END (0)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
