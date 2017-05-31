#ifndef __SOC_ISP_CSI2IF_INTERFACE_H__
#define __SOC_ISP_CSI2IF_INTERFACE_H__ 
#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif
#define SOC_ISP_CSI2IF_VERSION_ADDR(base) ((base) + (0x0))
#define SOC_ISP_CSI2IF_N_LANES_ADDR(base) ((base) + (0x4))
#define SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_ADDR(base) ((base) + (0x8))
#define SOC_ISP_CSI2IF_DPHY_RSTZ_ADDR(base) ((base) + (0xC))
#define SOC_ISP_CSI2IF_CSI2_RESETN_ADDR(base) ((base) + (0x10))
#define SOC_ISP_CSI2IF_PHY_STATE_ADDR(base) ((base) + (0x14))
#define SOC_ISP_CSI2IF_DATA_IDS_1_ADDR(base) ((base) + (0x18))
#define SOC_ISP_CSI2IF_ERR1_ADDR(base) ((base) + (0x20))
#define SOC_ISP_CSI2IF_ERR2_ADDR(base) ((base) + (0x24))
#define SOC_ISP_CSI2IF_MASK1_ADDR(base) ((base) + (0x28))
#define SOC_ISP_CSI2IF_MASK2_ADDR(base) ((base) + (0x2C))
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_ADDR(base) ((base) + (0x30))
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_ADDR(base) ((base) + (0x34))
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int version : 32;
    } reg;
} SOC_ISP_CSI2IF_VERSION_UNION;
#endif
#define SOC_ISP_CSI2IF_VERSION_version_START (0)
#define SOC_ISP_CSI2IF_VERSION_version_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int n_lanes : 2;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_CSI2IF_N_LANES_UNION;
#endif
#define SOC_ISP_CSI2IF_N_LANES_n_lanes_START (0)
#define SOC_ISP_CSI2IF_N_LANES_n_lanes_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_shutdownz : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_UNION;
#endif
#define SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_phy_shutdownz_START (0)
#define SOC_ISP_CSI2IF_PHY_SHUTDOWNZ_phy_shutdownz_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int dphy_rstz : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_CSI2IF_DPHY_RSTZ_UNION;
#endif
#define SOC_ISP_CSI2IF_DPHY_RSTZ_dphy_rstz_START (0)
#define SOC_ISP_CSI2IF_DPHY_RSTZ_dphy_rstz_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int csi2_resetn : 1;
        unsigned int reserved : 31;
    } reg;
} SOC_ISP_CSI2IF_CSI2_RESETN_UNION;
#endif
#define SOC_ISP_CSI2IF_CSI2_RESETN_csi2_resetn_START (0)
#define SOC_ISP_CSI2IF_CSI2_RESETN_csi2_resetn_END (0)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_rxulpsesc_0 : 1;
        unsigned int phy_rxulpsesc_1 : 1;
        unsigned int phy_rxulpsesc_2 : 1;
        unsigned int phy_rxulpsesc_3 : 1;
        unsigned int phy_stopstatedata_0 : 1;
        unsigned int phy_stopstatedata_1 : 1;
        unsigned int phy_stopstatedata_2 : 1;
        unsigned int phy_stopstatedata_3 : 1;
        unsigned int phy_rxclkactivehs : 1;
        unsigned int phy_rxulpsclknot : 1;
        unsigned int phy_stopstateclk : 1;
        unsigned int reserved : 21;
    } reg;
} SOC_ISP_CSI2IF_PHY_STATE_UNION;
#endif
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_0_START (0)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_0_END (0)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_1_START (1)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_1_END (1)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_2_START (2)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_2_END (2)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_3_START (3)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsesc_3_END (3)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_0_START (4)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_0_END (4)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_1_START (5)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_1_END (5)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_2_START (6)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_2_END (6)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_3_START (7)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstatedata_3_END (7)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxclkactivehs_START (8)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxclkactivehs_END (8)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsclknot_START (9)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_rxulpsclknot_END (9)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstateclk_START (10)
#define SOC_ISP_CSI2IF_PHY_STATE_phy_stopstateclk_END (10)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int di0_dt : 6;
        unsigned int di0_vc : 2;
        unsigned int di1_dt : 6;
        unsigned int di1_vc : 2;
        unsigned int di2_dt : 6;
        unsigned int di2_vc : 2;
        unsigned int di3_dt : 6;
        unsigned int di3_vc : 2;
    } reg;
} SOC_ISP_CSI2IF_DATA_IDS_1_UNION;
#endif
#define SOC_ISP_CSI2IF_DATA_IDS_1_di0_dt_START (0)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di0_dt_END (5)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di0_vc_START (6)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di0_vc_END (7)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di1_dt_START (8)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di1_dt_END (13)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di1_vc_START (14)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di1_vc_END (15)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di2_dt_START (16)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di2_dt_END (21)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di2_vc_START (22)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di2_vc_END (23)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di3_dt_START (24)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di3_dt_END (29)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di3_vc_START (30)
#define SOC_ISP_CSI2IF_DATA_IDS_1_di3_vc_END (31)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_errsotsynchs_0 : 1;
        unsigned int phy_errsotsynchs_1 : 1;
        unsigned int phy_errsotsynchs_2 : 1;
        unsigned int phy_errsotsynchs_3 : 1;
        unsigned int err_f_bndry_match_vc0 : 1;
        unsigned int err_f_bndry_match_vc1 : 1;
        unsigned int err_f_bndry_match_vc2 : 1;
        unsigned int err_f_bndry_match_vc3 : 1;
        unsigned int err_f_seq_vc0 : 1;
        unsigned int err_f_seq_vc1 : 1;
        unsigned int err_f_seq_vc2 : 1;
        unsigned int err_f_seq_vc3 : 1;
        unsigned int err_frame_data_vc0 : 1;
        unsigned int err_frame_data_vc1 : 1;
        unsigned int err_frame_data_vc2 : 1;
        unsigned int err_frame_data_vc3 : 1;
        unsigned int err_l_bndry_match_di0 : 1;
        unsigned int err_l_bndry_match_di1 : 1;
        unsigned int err_l_bndry_match_di2 : 1;
        unsigned int err_l_bndry_match_di3 : 1;
        unsigned int err_l_seq_di0 : 1;
        unsigned int err_l_seq_di1 : 1;
        unsigned int err_l_seq_di2 : 1;
        unsigned int err_l_seq_di3 : 1;
        unsigned int vc0_err_crc : 1;
        unsigned int vc1_err_crc : 1;
        unsigned int vc2_err_crc : 1;
        unsigned int vc3_err_crc : 1;
        unsigned int err_ecc_double : 1;
        unsigned int reserved : 3;
    } reg;
} SOC_ISP_CSI2IF_ERR1_UNION;
#endif
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_0_START (0)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_0_END (0)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_1_START (1)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_1_END (1)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_2_START (2)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_2_END (2)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_3_START (3)
#define SOC_ISP_CSI2IF_ERR1_phy_errsotsynchs_3_END (3)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc0_START (4)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc0_END (4)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc1_START (5)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc1_END (5)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc2_START (6)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc2_END (6)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc3_START (7)
#define SOC_ISP_CSI2IF_ERR1_err_f_bndry_match_vc3_END (7)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc0_START (8)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc0_END (8)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc1_START (9)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc1_END (9)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc2_START (10)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc2_END (10)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc3_START (11)
#define SOC_ISP_CSI2IF_ERR1_err_f_seq_vc3_END (11)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc0_START (12)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc0_END (12)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc1_START (13)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc1_END (13)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc2_START (14)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc2_END (14)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc3_START (15)
#define SOC_ISP_CSI2IF_ERR1_err_frame_data_vc3_END (15)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di0_START (16)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di0_END (16)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di1_START (17)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di1_END (17)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di2_START (18)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di2_END (18)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di3_START (19)
#define SOC_ISP_CSI2IF_ERR1_err_l_bndry_match_di3_END (19)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di0_START (20)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di0_END (20)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di1_START (21)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di1_END (21)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di2_START (22)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di2_END (22)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di3_START (23)
#define SOC_ISP_CSI2IF_ERR1_err_l_seq_di3_END (23)
#define SOC_ISP_CSI2IF_ERR1_vc0_err_crc_START (24)
#define SOC_ISP_CSI2IF_ERR1_vc0_err_crc_END (24)
#define SOC_ISP_CSI2IF_ERR1_vc1_err_crc_START (25)
#define SOC_ISP_CSI2IF_ERR1_vc1_err_crc_END (25)
#define SOC_ISP_CSI2IF_ERR1_vc2_err_crc_START (26)
#define SOC_ISP_CSI2IF_ERR1_vc2_err_crc_END (26)
#define SOC_ISP_CSI2IF_ERR1_vc3_err_crc_START (27)
#define SOC_ISP_CSI2IF_ERR1_vc3_err_crc_END (27)
#define SOC_ISP_CSI2IF_ERR1_err_ecc_double_START (28)
#define SOC_ISP_CSI2IF_ERR1_err_ecc_double_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_erresc_0 : 1;
        unsigned int phy_erresc_1 : 1;
        unsigned int phy_erresc_2 : 1;
        unsigned int phy_erresc_3 : 1;
        unsigned int phy_errsoths_0 : 1;
        unsigned int phy_errsoths_1 : 1;
        unsigned int phy_errsoths_2 : 1;
        unsigned int phy_errsoths_3 : 1;
        unsigned int vc0_err_ecc_corrected : 1;
        unsigned int vc1_err_ecc_corrected : 1;
        unsigned int vc2_err_ecc_corrected : 1;
        unsigned int vc3_err_ecc_corrected : 1;
        unsigned int err_id_vc0 : 1;
        unsigned int err_id_vc1 : 1;
        unsigned int err_id_vc2 : 1;
        unsigned int err_id_vc3 : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_CSI2IF_ERR2_UNION;
#endif
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_0_START (0)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_0_END (0)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_1_START (1)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_1_END (1)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_2_START (2)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_2_END (2)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_3_START (3)
#define SOC_ISP_CSI2IF_ERR2_phy_erresc_3_END (3)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_0_START (4)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_0_END (4)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_1_START (5)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_1_END (5)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_2_START (6)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_2_END (6)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_3_START (7)
#define SOC_ISP_CSI2IF_ERR2_phy_errsoths_3_END (7)
#define SOC_ISP_CSI2IF_ERR2_vc0_err_ecc_corrected_START (8)
#define SOC_ISP_CSI2IF_ERR2_vc0_err_ecc_corrected_END (8)
#define SOC_ISP_CSI2IF_ERR2_vc1_err_ecc_corrected_START (9)
#define SOC_ISP_CSI2IF_ERR2_vc1_err_ecc_corrected_END (9)
#define SOC_ISP_CSI2IF_ERR2_vc2_err_ecc_corrected_START (10)
#define SOC_ISP_CSI2IF_ERR2_vc2_err_ecc_corrected_END (10)
#define SOC_ISP_CSI2IF_ERR2_vc3_err_ecc_corrected_START (11)
#define SOC_ISP_CSI2IF_ERR2_vc3_err_ecc_corrected_END (11)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc0_START (12)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc0_END (12)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc1_START (13)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc1_END (13)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc2_START (14)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc2_END (14)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc3_START (15)
#define SOC_ISP_CSI2IF_ERR2_err_id_vc3_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mask_phy_errsotsynchs_0 : 1;
        unsigned int mask_phy_errsotsynchs_1 : 1;
        unsigned int mask_phy_errsotsynchs_2 : 1;
        unsigned int mask_phy_errsotsynchs_3 : 1;
        unsigned int mask_err_f_bndry_match_vc0 : 1;
        unsigned int mask_err_f_bndry_match_vc1 : 1;
        unsigned int mask_err_f_bndry_match_vc2 : 1;
        unsigned int mask_err_f_bndry_match_vc3 : 1;
        unsigned int mask_err_f_seq_vc0 : 1;
        unsigned int mask_err_f_seq_vc1 : 1;
        unsigned int mask_err_f_seq_vc2 : 1;
        unsigned int mask_err_f_seq_vc3 : 1;
        unsigned int mask_err_frame_data_vc0 : 1;
        unsigned int mask_err_frame_data_vc1 : 1;
        unsigned int mask_err_frame_data_vc2 : 1;
        unsigned int mask_err_frame_data_vc3 : 1;
        unsigned int mask_err_l_bndry_match_di0 : 1;
        unsigned int mask_err_l_bndry_match_di1 : 1;
        unsigned int mask_err_l_bndry_match_di2 : 1;
        unsigned int mask_err_l_bndry_match_di3 : 1;
        unsigned int mask_err_l_seq_di0 : 1;
        unsigned int mask_err_l_seq_di1 : 1;
        unsigned int mask_err_l_seq_di2 : 1;
        unsigned int mask_err_l_seq_di3 : 1;
        unsigned int mask_vc0_err_crc : 1;
        unsigned int mask_vc1_err_crc : 1;
        unsigned int mask_vc2_err_crc : 1;
        unsigned int mask_vc3_err_crc : 1;
        unsigned int mask_err_ecc_double : 1;
        unsigned int reserved : 3;
    } reg;
} SOC_ISP_CSI2IF_MASK1_UNION;
#endif
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_0_START (0)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_0_END (0)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_1_START (1)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_1_END (1)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_2_START (2)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_2_END (2)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_3_START (3)
#define SOC_ISP_CSI2IF_MASK1_mask_phy_errsotsynchs_3_END (3)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc0_START (4)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc0_END (4)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc1_START (5)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc1_END (5)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc2_START (6)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc2_END (6)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc3_START (7)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_bndry_match_vc3_END (7)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc0_START (8)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc0_END (8)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc1_START (9)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc1_END (9)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc2_START (10)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc2_END (10)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc3_START (11)
#define SOC_ISP_CSI2IF_MASK1_mask_err_f_seq_vc3_END (11)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc0_START (12)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc0_END (12)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc1_START (13)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc1_END (13)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc2_START (14)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc2_END (14)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc3_START (15)
#define SOC_ISP_CSI2IF_MASK1_mask_err_frame_data_vc3_END (15)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di0_START (16)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di0_END (16)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di1_START (17)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di1_END (17)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di2_START (18)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di2_END (18)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di3_START (19)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_bndry_match_di3_END (19)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di0_START (20)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di0_END (20)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di1_START (21)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di1_END (21)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di2_START (22)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di2_END (22)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di3_START (23)
#define SOC_ISP_CSI2IF_MASK1_mask_err_l_seq_di3_END (23)
#define SOC_ISP_CSI2IF_MASK1_mask_vc0_err_crc_START (24)
#define SOC_ISP_CSI2IF_MASK1_mask_vc0_err_crc_END (24)
#define SOC_ISP_CSI2IF_MASK1_mask_vc1_err_crc_START (25)
#define SOC_ISP_CSI2IF_MASK1_mask_vc1_err_crc_END (25)
#define SOC_ISP_CSI2IF_MASK1_mask_vc2_err_crc_START (26)
#define SOC_ISP_CSI2IF_MASK1_mask_vc2_err_crc_END (26)
#define SOC_ISP_CSI2IF_MASK1_mask_vc3_err_crc_START (27)
#define SOC_ISP_CSI2IF_MASK1_mask_vc3_err_crc_END (27)
#define SOC_ISP_CSI2IF_MASK1_mask_err_ecc_double_START (28)
#define SOC_ISP_CSI2IF_MASK1_mask_err_ecc_double_END (28)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int mask_phy_erresc_0 : 1;
        unsigned int mask_phy_erresc_1 : 1;
        unsigned int mask_phy_erresc_2 : 1;
        unsigned int mask_phy_erresc_3 : 1;
        unsigned int mask_phy_errsoths_0 : 1;
        unsigned int mask_phy_errsoths_1 : 1;
        unsigned int mask_phy_errsoths_2 : 1;
        unsigned int mask_phy_errsoths_3 : 1;
        unsigned int mask_vc0_err_ecc_corrected : 1;
        unsigned int mask_vc1_err_ecc_corrected : 1;
        unsigned int mask_vc2_err_ecc_corrected : 1;
        unsigned int mask_vc3_err_ecc_corrected : 1;
        unsigned int mask_err_id_vc0 : 1;
        unsigned int mask_err_id_vc1 : 1;
        unsigned int mask_err_id_vc2 : 1;
        unsigned int mask_err_id_vc3 : 1;
        unsigned int reserved : 16;
    } reg;
} SOC_ISP_CSI2IF_MASK2_UNION;
#endif
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_0_START (0)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_0_END (0)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_1_START (1)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_1_END (1)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_2_START (2)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_2_END (2)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_3_START (3)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_erresc_3_END (3)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_0_START (4)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_0_END (4)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_1_START (5)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_1_END (5)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_2_START (6)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_2_END (6)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_3_START (7)
#define SOC_ISP_CSI2IF_MASK2_mask_phy_errsoths_3_END (7)
#define SOC_ISP_CSI2IF_MASK2_mask_vc0_err_ecc_corrected_START (8)
#define SOC_ISP_CSI2IF_MASK2_mask_vc0_err_ecc_corrected_END (8)
#define SOC_ISP_CSI2IF_MASK2_mask_vc1_err_ecc_corrected_START (9)
#define SOC_ISP_CSI2IF_MASK2_mask_vc1_err_ecc_corrected_END (9)
#define SOC_ISP_CSI2IF_MASK2_mask_vc2_err_ecc_corrected_START (10)
#define SOC_ISP_CSI2IF_MASK2_mask_vc2_err_ecc_corrected_END (10)
#define SOC_ISP_CSI2IF_MASK2_mask_vc3_err_ecc_corrected_START (11)
#define SOC_ISP_CSI2IF_MASK2_mask_vc3_err_ecc_corrected_END (11)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc0_START (12)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc0_END (12)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc1_START (13)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc1_END (13)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc2_START (14)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc2_END (14)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc3_START (15)
#define SOC_ISP_CSI2IF_MASK2_mask_err_id_vc3_END (15)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_testclr : 1;
        unsigned int phy_testclk : 1;
        unsigned int reserved : 30;
    } reg;
} SOC_ISP_CSI2IF_PHY_TEST_CTRL0_UNION;
#endif
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_phy_testclr_START (0)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_phy_testclr_END (0)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_phy_testclk_START (1)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL0_phy_testclk_END (1)
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int value;
    struct
    {
        unsigned int phy_testdin : 8;
        unsigned int phy_testdout : 8;
        unsigned int phy_testen : 1;
        unsigned int reserved : 15;
    } reg;
} SOC_ISP_CSI2IF_PHY_TEST_CTRL1_UNION;
#endif
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testdin_START (0)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testdin_END (7)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testdout_START (8)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testdout_END (15)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testen_START (16)
#define SOC_ISP_CSI2IF_PHY_TEST_CTRL1_phy_testen_END (16)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif
