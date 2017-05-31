#ifndef __HI6551_H__
#define __HI6551_H__ 
#ifndef HI_SET_GET
#define HI_SET_GET(a0,a1,a2,a3,a4) 
#endif
#define HI6551_STATUS1_OFFSET (0x1)
#define HI6551_STATUS2_OFFSET (0x2)
#define HI6551_IRQ1_OFFSET (0x3)
#define HI6551_IRQ2_OFFSET (0x4)
#define HI6551_IRQ3_OFFSET (0x5)
#define HI6551_IRQ4_OFFSET (0x6)
#define HI6551_COUL_IRQ_OFFSET (0x7)
#define HI6551_IRQ1_MASK_OFFSET (0x8)
#define HI6551_IRQ2_MASK_OFFSET (0x9)
#define HI6551_IRQ3_MASK_OFFSET (0xA)
#define HI6551_IRQ4_MASK_OFFSET (0xB)
#define HI6551_COUL_IRQ_MASK_OFFSET (0xC)
#define HI6551_SCP_RECORD1_OFFSET (0xD)
#define HI6551_OCP_RECORD1_OFFSET (0xE)
#define HI6551_OCP_RECORD2_OFFSET (0xF)
#define HI6551_OCP_RECORD3_OFFSET (0x10)
#define HI6551_OCP_RECORD4_OFFSET (0x11)
#define HI6551_OCP_RECORD5_OFFSET (0x12)
#define HI6551_OCP_RECORD6_OFFSET (0x13)
#define HI6551_OCP_RECORD7_OFFSET (0x14)
#define HI6551_NP_IRQ1_RECORD_OFFSET (0x15)
#define HI6551_NP_IRQ2_RECORD_OFFSET (0x16)
#define HI6551_NP_IRQ3_RECORD_OFFSET (0x17)
#define HI6551_NP_SCP_RECORD1_OFFSET (0x18)
#define HI6551_NP_OCP_RECORD1_OFFSET (0x19)
#define HI6551_NP_OCP_RECORD2_OFFSET (0x1A)
#define HI6551_NP_OCP_RECORD3_OFFSET (0x1B)
#define HI6551_NP_OCP_RECORD4_OFFSET (0x1C)
#define HI6551_NP_OCP_RECORD5_OFFSET (0x1D)
#define HI6551_NP_OCP_RECORD6_OFFSET (0x1E)
#define HI6551_NP_OCP_RECORD7_OFFSET (0x1F)
#define HI6551_OCP_DEB_OFFSET (0x20)
#define HI6551_ONOFF8_OFFSET (0x21)
#define HI6551_OCP_SCP_MOD_CTRL1_OFFSET (0x22)
#define HI6551_OCP_SCP_MOD_CTRL2_OFFSET (0x23)
#define HI6551_OCP_MOD_CTRL3_OFFSET (0x24)
#define HI6551_OCP_MOD_CTRL4_OFFSET (0x25)
#define HI6551_OCP_MOD_CTRL5_OFFSET (0x26)
#define HI6551_OCP_MOD_CTRL6_OFFSET (0x27)
#define HI6551_OCP_MOD_CTRL7_OFFSET (0x28)
#define HI6551_OCP_MOD_CTRL8_OFFSET (0x29)
#define HI6551_OCP_MOD_CTRL9_OFFSET (0x2A)
#define HI6551_OCP_MOD_CTRL10_OFFSET (0x2B)
#define HI6551_OCP_MOD_CTRL11_OFFSET (0x2C)
#define HI6551_ENABLE1_OFFSET (0x2D)
#define HI6551_DISABLE1_OFFSET (0x2E)
#define HI6551_ONOFF_STATUS1_OFFSET (0x2F)
#define HI6551_ENABLE2_OFFSET (0x30)
#define HI6551_DISABLE2_OFFSET (0x31)
#define HI6551_ONOFF_STATUS2_OFFSET (0x32)
#define HI6551_ENABLE3_OFFSET (0x33)
#define HI6551_DISABLE3_OFFSET (0x34)
#define HI6551_ONOFF_STATUS3_OFFSET (0x35)
#define HI6551_ENABLE4_OFFSET (0x36)
#define HI6551_DISABLE4_OFFSET (0x37)
#define HI6551_ONOFF_STATUS4_OFFSET (0x38)
#define HI6551_ENABLE5_OFFSET (0x39)
#define HI6551_DISABLE5_OFFSET (0x3A)
#define HI6551_ONOFF_STATUS5_OFFSET (0x3B)
#define HI6551_ENABLE6_OFFSET (0x3C)
#define HI6551_DISABLE6_OFFSET (0x3D)
#define HI6551_ONOFF_STATUS6_OFFSET (0x3E)
#define HI6551_ENABLE7_OFFSET (0x3F)
#define HI6551_SIMCARD_EN_OFFSET (0x40)
#define HI6551_SIM0_CFG_OFFSET (0x41)
#define HI6551_SIM1_CFG_OFFSET (0x42)
#define HI6551_SIM_DEB_OFFSET (0x43)
#define HI6551_ECO_MOD_CFG1_OFFSET (0x44)
#define HI6551_ECO_MOD_CFG2_OFFSET (0x45)
#define HI6551_ECO_MOD_CFG3_OFFSET (0x46)
#define HI6551_ECO_MOD_CFG4_OFFSET (0x47)
#define HI6551_ENB3_ECO_MARK_OFFSET (0x48)
#define HI6551_BUCK01_REG1_ADJ_OFFSET (0x49)
#define HI6551_BUCK01_REG2_ADJ_OFFSET (0x4A)
#define HI6551_BUCK01_REG3_ADJ_OFFSET (0x4B)
#define HI6551_BUCK01_REG4_ADJ_OFFSET (0x4C)
#define HI6551_BUCK01_REG5_ADJ_OFFSET (0x4D)
#define HI6551_BUCK01_REG6_ADJ_OFFSET (0x4E)
#define HI6551_BUCK01_REG7_ADJ_OFFSET (0x4F)
#define HI6551_BUCK01_REG8_ADJ_OFFSET (0x50)
#define HI6551_BUCK01_REG9_ADJ_OFFSET (0x51)
#define HI6551_BUCK01_REG10_ADJ_OFFSET (0x52)
#define HI6551_BUCK01_REG11_ADJ_OFFSET (0x53)
#define HI6551_BUCK01_REG12_ADJ_OFFSET (0x54)
#define HI6551_BUCK01_REG13_ADJ_OFFSET (0x55)
#define HI6551_BUCK01_REG14_ADJ_OFFSET (0x56)
#define HI6551_BUCK01_REG15_ADJ_OFFSET (0x57)
#define HI6551_BUCK01_REG16_ADJ_OFFSET (0x58)
#define HI6551_BUCK01_REG17_ADJ_OFFSET (0x59)
#define HI6551_BUCK2_REG1_ADJ_OFFSET (0x5A)
#define HI6551_BUCK2_REG2_ADJ_OFFSET (0x5B)
#define HI6551_BUCK2_REG3_ADJ_OFFSET (0x5C)
#define HI6551_BUCK2_REG4_ADJ_OFFSET (0x5D)
#define HI6551_BUCK2_REG5_ADJ_OFFSET (0x5E)
#define HI6551_BUCK2_REG6_ADJ_OFFSET (0x5F)
#define HI6551_BUCK2_REG7_ADJ_OFFSET (0x60)
#define HI6551_BUCK2_REG8_ADJ_OFFSET (0x61)
#define HI6551_BUCK2_REG9_ADJ_OFFSET (0x62)
#define HI6551_BUCK2_REG10_ADJ_OFFSET (0x63)
#define HI6551_BUCK2_REG11_ADJ_OFFSET (0x64)
#define HI6551_BUCK2_REG12_ADJ_OFFSET (0x65)
#define HI6551_BUCK3_REG1_ADJ_OFFSET (0x66)
#define HI6551_BUCK3_REG2_ADJ_OFFSET (0x67)
#define HI6551_BUCK3_REG3_ADJ_OFFSET (0x68)
#define HI6551_BUCK3_REG4_ADJ_OFFSET (0x69)
#define HI6551_BUCK3_REG5_ADJ_OFFSET (0x6A)
#define HI6551_BUCK3_REG6_ADJ_OFFSET (0x6B)
#define HI6551_BUCK3_REG7_ADJ_OFFSET (0x6C)
#define HI6551_BUCK3_REG8_ADJ_OFFSET (0x6D)
#define HI6551_BUCK3_REG9_ADJ_OFFSET (0x6E)
#define HI6551_BUCK3_REG10_ADJ_OFFSET (0x6F)
#define HI6551_BUCK3_REG11_ADJ_OFFSET (0x70)
#define HI6551_BUCK3_REG12_ADJ_OFFSET (0x71)
#define HI6551_BUCK4_REG1_ADJ_OFFSET (0x72)
#define HI6551_BUCK4_REG2_ADJ_OFFSET (0x73)
#define HI6551_BUCK4_REG3_ADJ_OFFSET (0x74)
#define HI6551_BUCK4_REG4_ADJ_OFFSET (0x75)
#define HI6551_BUCK4_REG5_ADJ_OFFSET (0x76)
#define HI6551_BUCK4_REG6_ADJ_OFFSET (0x77)
#define HI6551_BUCK4_REG7_ADJ_OFFSET (0x78)
#define HI6551_BUCK4_REG8_ADJ_OFFSET (0x79)
#define HI6551_BUCK4_REG9_ADJ_OFFSET (0x7A)
#define HI6551_BUCK4_REG10_ADJ_OFFSET (0x7B)
#define HI6551_BUCK4_REG12_ADJ_OFFSET (0x7C)
#define HI6551_BUCK5_REG1_ADJ_OFFSET (0x7D)
#define HI6551_BUCK5_REG2_ADJ_OFFSET (0x7E)
#define HI6551_BUCK5_REG3_ADJ_OFFSET (0x7F)
#define HI6551_BUCK5_REG4_ADJ_OFFSET (0x80)
#define HI6551_BUCK5_REG5_ADJ_OFFSET (0x81)
#define HI6551_BUCK5_REG6_ADJ_OFFSET (0x82)
#define HI6551_BUCK5_REG7_ADJ_OFFSET (0x83)
#define HI6551_BUCK5_REG8_ADJ_OFFSET (0x84)
#define HI6551_BUCK5_REG9_ADJ_OFFSET (0x85)
#define HI6551_BUCK5_REG10_ADJ_OFFSET (0x86)
#define HI6551_BUCK5_REG12_ADJ_OFFSET (0x87)
#define HI6551_BUCK5_REG13_ADJ_OFFSET (0x88)
#define HI6551_BUCK5_REG14_ADJ_OFFSET (0x89)
#define HI6551_BUCK6_REG1_ADJ_OFFSET (0x8A)
#define HI6551_BUCK6_REG2_ADJ_OFFSET (0x8B)
#define HI6551_BUCK6_REG3_ADJ_OFFSET (0x8C)
#define HI6551_BUCK6_REG4_ADJ_OFFSET (0x8D)
#define HI6551_BUCK6_REG5_ADJ_OFFSET (0x8E)
#define HI6551_BUCK6_REG6_ADJ_OFFSET (0x8F)
#define HI6551_BUCK6_REG7_ADJ_OFFSET (0x90)
#define HI6551_BUCK6_REG8_ADJ_OFFSET (0x91)
#define HI6551_BUCK6_REG9_ADJ_OFFSET (0x92)
#define HI6551_BUCK6_REG10_ADJ_OFFSET (0x93)
#define HI6551_BUCK6_REG11_ADJ_OFFSET (0x94)
#define HI6551_BUCK6_REG12_ADJ_OFFSET (0x95)
#define HI6551_CHG_PUMP2_ADJ_OFFSET (0x96)
#define HI6551_VSET_BUCK01_ADJ_OFFSET (0x97)
#define HI6551_VSET_BUCK2_ADJ_OFFSET (0x98)
#define HI6551_VSET_BUCK3_ADJ_OFFSET (0x99)
#define HI6551_VSET_BUCK4_ADJ_OFFSET (0x9A)
#define HI6551_VSET_BUCK5_ADJ_OFFSET (0x9B)
#define HI6551_VSET_BUCK6_ADJ_OFFSET (0x9C)
#define HI6551_LDO1_REG_ADJ_OFFSET (0x9D)
#define HI6551_LDO2_REG_ADJ_OFFSET (0x9E)
#define HI6551_LDO3_REG_ADJ_OFFSET (0x9F)
#define HI6551_LDO4_REG_ADJ_OFFSET (0xA0)
#define HI6551_LDO5_REG_ADJ_OFFSET (0xA1)
#define HI6551_LDO6_REG_ADJ_OFFSET (0xA2)
#define HI6551_LDO7_REG_ADJ_OFFSET (0xA3)
#define HI6551_LDO8_REG_ADJ_OFFSET (0xA4)
#define HI6551_LDO9_REG_ADJ_OFFSET (0xA5)
#define HI6551_LDO10_REG_ADJ_OFFSET (0xA6)
#define HI6551_LDO11_REG_ADJ_OFFSET (0xA7)
#define HI6551_LDO12_REG_ADJ_OFFSET (0xA8)
#define HI6551_LDO13_REG_ADJ_OFFSET (0xA9)
#define HI6551_LDO14_REG_ADJ_OFFSET (0xAA)
#define HI6551_LDO15_REG_ADJ_OFFSET (0xAB)
#define HI6551_LDO16_REG_ADJ_OFFSET (0xAC)
#define HI6551_LDO17_REG_ADJ_OFFSET (0xAD)
#define HI6551_LDO18_REG_ADJ_OFFSET (0xAE)
#define HI6551_LDO19_REG_ADJ_OFFSET (0xAF)
#define HI6551_LDO20_REG_ADJ_OFFSET (0xB0)
#define HI6551_LDO21_REG_ADJ_OFFSET (0xB1)
#define HI6551_LDO22_REG_ADJ_OFFSET (0xB2)
#define HI6551_LDO23_REG_ADJ_OFFSET (0xB3)
#define HI6551_LDO24_REG_ADJ_OFFSET (0xB4)
#define HI6551_PMUA_REG_ADJ_OFFSET (0xB5)
#define HI6551_LVS_ADJ1_OFFSET (0xB6)
#define HI6551_LVS_ADJ2_OFFSET (0xB7)
#define HI6551_LVS_ADJ3_OFFSET (0xB8)
#define HI6551_BOOST_ADJ0_OFFSET (0xB9)
#define HI6551_BOOST_ADJ1_OFFSET (0xBA)
#define HI6551_BOOST_ADJ2_OFFSET (0xBB)
#define HI6551_BOOST_ADJ3_OFFSET (0xBC)
#define HI6551_BOOST_ADJ4_OFFSET (0xBD)
#define HI6551_BOOST_ADJ5_OFFSET (0xBE)
#define HI6551_BOOST_ADJ6_OFFSET (0xBF)
#define HI6551_BOOST_ADJ7_OFFSET (0xC0)
#define HI6551_BOOST_ADJ8_OFFSET (0xC1)
#define HI6551_BOOST_ADJ9_OFFSET (0xC2)
#define HI6551_BOOST_ADJ10_OFFSET (0xC3)
#define HI6551_BOOST_ADJ11_OFFSET (0xC4)
#define HI6551_CLASSD_ADJ0_OFFSET (0xC5)
#define HI6551_CLASSD_ADJ1_OFFSET (0xC6)
#define HI6551_CLASSD_ADJ2_OFFSET (0xC7)
#define HI6551_BANDGAP_THSD_ADJ1_OFFSET (0xC8)
#define HI6551_BANDGAP_THSD_ADJ2_OFFSET (0xC9)
#define HI6551_DR_FLA_CTRL1_OFFSET (0xCA)
#define HI6551_DR_FLA_CTRL2_OFFSET (0xCB)
#define HI6551_FLASH_PERIOD_OFFSET (0xCC)
#define HI6551_FLASH_ON_OFFSET (0xCD)
#define HI6551_DR_MODE_SEL_OFFSET (0xCE)
#define HI6551_DR_BRE_CTRL_OFFSET (0xCF)
#define HI6551_DR1_TIM_CONF0_OFFSET (0xD0)
#define HI6551_DR1_TIM_CONF1_OFFSET (0xD1)
#define HI6551_DR1_ISET_OFFSET (0xD2)
#define HI6551_DR2_TIM_CONF0_OFFSET (0xD3)
#define HI6551_DR2_TIM_CONF1_OFFSET (0xD4)
#define HI6551_DR2_ISET_OFFSET (0xD5)
#define HI6551_DR_LED_CTRL_OFFSET (0xD6)
#define HI6551_DR_OUT_CTRL_OFFSET (0xD7)
#define HI6551_DR3_ISET_OFFSET (0xD8)
#define HI6551_DR3_START_DEL_OFFSET (0xD9)
#define HI6551_DR3_TIM_CONF0_OFFSET (0xDA)
#define HI6551_DR3_TIM_CONF1_OFFSET (0xDB)
#define HI6551_DR4_ISET_OFFSET (0xDC)
#define HI6551_DR4_START_DEL_OFFSET (0xDD)
#define HI6551_DR4_TIM_CONF0_OFFSET (0xDE)
#define HI6551_DR4_TIM_CONF1_OFFSET (0xDF)
#define HI6551_DR5_ISET_OFFSET (0xE0)
#define HI6551_DR5_START_DEL_OFFSET (0xE1)
#define HI6551_DR5_TIM_CONF0_OFFSET (0xE2)
#define HI6551_DR5_TIM_CONF1_OFFSET (0xE3)
#define HI6551_OTP_CTRL1_OFFSET (0xE4)
#define HI6551_OTP_CTRL2_OFFSET (0xE5)
#define HI6551_OTP_PDIN_OFFSET (0xE6)
#define HI6551_OTP_PDOB0_OFFSET (0xE7)
#define HI6551_OTP_PDOB1_OFFSET (0xE8)
#define HI6551_OTP_PDOB2_OFFSET (0xE9)
#define HI6551_OTP_PDOB3_OFFSET (0xEA)
#define HI6551_RTCCR_A0_OFFSET (0xEB)
#define HI6551_RTCCR_A1_OFFSET (0xEC)
#define HI6551_RTCCR_A2_OFFSET (0xED)
#define HI6551_RTCCR_A3_OFFSET (0xEE)
#define HI6551_RTCLR_A0_OFFSET (0xEF)
#define HI6551_RTCLR_A1_OFFSET (0xF0)
#define HI6551_RTCLR_A2_OFFSET (0xF1)
#define HI6551_RTCLR_A3_OFFSET (0xF2)
#define HI6551_RTCCTRL_A_OFFSET (0xF3)
#define HI6551_RTCMR_A_A0_OFFSET (0xF4)
#define HI6551_RTCMR_A_A1_OFFSET (0xF5)
#define HI6551_RTCMR_A_A2_OFFSET (0xF6)
#define HI6551_RTCMR_A_A3_OFFSET (0xF7)
#define HI6551_RTCMR_A_B0_OFFSET (0xF8)
#define HI6551_RTCMR_A_B1_OFFSET (0xF9)
#define HI6551_RTCMR_A_B2_OFFSET (0xFA)
#define HI6551_RTCMR_A_B3_OFFSET (0xFB)
#define HI6551_RTCMR_A_C0_OFFSET (0xFC)
#define HI6551_RTCMR_A_C1_OFFSET (0xFD)
#define HI6551_RTCMR_A_C2_OFFSET (0xFE)
#define HI6551_RTCMR_A_C3_OFFSET (0xFF)
#define HI6551_RTCMR_A_D0_OFFSET (0x100)
#define HI6551_RTCMR_A_D1_OFFSET (0x101)
#define HI6551_RTCMR_A_D2_OFFSET (0x102)
#define HI6551_RTCMR_A_D3_OFFSET (0x103)
#define HI6551_RTCMR_A_E0_OFFSET (0x104)
#define HI6551_RTCMR_A_E1_OFFSET (0x105)
#define HI6551_RTCMR_A_E2_OFFSET (0x106)
#define HI6551_RTCMR_A_E3_OFFSET (0x107)
#define HI6551_RTCMR_A_F0_OFFSET (0x108)
#define HI6551_RTCMR_A_F1_OFFSET (0x109)
#define HI6551_RTCMR_A_F2_OFFSET (0x10A)
#define HI6551_RTCMR_A_F3_OFFSET (0x10B)
#define HI6551_RTCCR_NA0_OFFSET (0x10C)
#define HI6551_RTCCR_NA1_OFFSET (0x10D)
#define HI6551_RTCCR_NA2_OFFSET (0x10E)
#define HI6551_RTCCR_NA3_OFFSET (0x10F)
#define HI6551_RTCLR_NA0_OFFSET (0x110)
#define HI6551_RTCLR_NA1_OFFSET (0x111)
#define HI6551_RTCLR_NA2_OFFSET (0x112)
#define HI6551_RTCLR_NA3_OFFSET (0x113)
#define HI6551_RTCCTRL_NA_OFFSET (0x114)
#define HI6551_VERSION_OFFSET (0x115)
#define HI6551_RESERVED0_OFFSET (0x116)
#define HI6551_RESERVED1_OFFSET (0x117)
#define HI6551_RESERVED2_OFFSET (0x118)
#define HI6551_RESERVED3_OFFSET (0x119)
#define HI6551_RESERVED4_OFFSET (0x11A)
#define HI6551_HTOL_MODE_OFFSET (0x11B)
#define HI6551_DAC_CTRL_OFFSET (0x11C)
#define HI6551_CHIP_SOFT_RST_OFFSET (0x11D)
#define HI6551_NP_REG_ADJ_OFFSET (0x11E)
#define HI6551_NP_REG_CHG_OFFSET (0x11F)
#define HI6551_NP_RSVED1_OFFSET (0x120)
#define HI6551_NP_RSVED2_OFFSET (0x121)
#define HI6551_NP_RSVED3_OFFSET (0x122)
#define HI6551_NP_RSVED4_OFFSET (0x123)
#define HI6551_RTC_ADJ1_OFFSET (0x124)
#define HI6551_RTC_ADJ2_OFFSET (0x125)
#define HI6551_CLJ_CTRL_REG_OFFSET (0x133)
#define HI6551_ECO_REFALSH_TIME_OFFSET (0x134)
#define HI6551_CL_OUT0_OFFSET (0x135)
#define HI6551_CL_OUT1_OFFSET (0x136)
#define HI6551_CL_OUT2_OFFSET (0x137)
#define HI6551_CL_OUT3_OFFSET (0x138)
#define HI6551_CL_IN0_OFFSET (0x139)
#define HI6551_CL_IN1_OFFSET (0x13A)
#define HI6551_CL_IN2_OFFSET (0x13B)
#define HI6551_CL_IN3_OFFSET (0x13C)
#define HI6551_CHG_TIMER0_OFFSET (0x13D)
#define HI6551_CHG_TIMER1_OFFSET (0x13E)
#define HI6551_CHG_TIMER2_OFFSET (0x13F)
#define HI6551_CHG_TIMER3_OFFSET (0x140)
#define HI6551_LOAD_TIMER0_OFFSET (0x141)
#define HI6551_LOAD_TIMER1_OFFSET (0x142)
#define HI6551_LOAD_TIMER2_OFFSET (0x143)
#define HI6551_LOAD_TIMER3_OFFSET (0x144)
#define HI6551_OFF_TIMER0_OFFSET (0x145)
#define HI6551_OFF_TIMER1_OFFSET (0x146)
#define HI6551_OFF_TIMER2_OFFSET (0x147)
#define HI6551_OFF_TIMER3_OFFSET (0x148)
#define HI6551_CL_INT0_OFFSET (0x149)
#define HI6551_CL_INT1_OFFSET (0x14A)
#define HI6551_CL_INT2_OFFSET (0x14B)
#define HI6551_CL_INT3_OFFSET (0x14C)
#define HI6551_V_INT0_OFFSET (0x14D)
#define HI6551_V_INT1_OFFSET (0x14E)
#define HI6551_OFFSET_CURRENT0_OFFSET (0x14F)
#define HI6551_OFFSET_CURRENT1_OFFSET (0x150)
#define HI6551_OFFSET_VOLTAGE0_OFFSET (0x151)
#define HI6551_OFFSET_VOLTAGE1_OFFSET (0x152)
#define HI6551_OCV_DATA1_OFFSET (0x153)
#define HI6551_OCV_DATA2_OFFSET (0x154)
#define HI6551_V_OUT0_PRE0_OFFSET (0x155)
#define HI6551_V_OUT1_PRE0_OFFSET (0x156)
#define HI6551_V_OUT0_PRE1_OFFSET (0x157)
#define HI6551_V_OUT1_PRE1_OFFSET (0x158)
#define HI6551_V_OUT0_PRE2_OFFSET (0x159)
#define HI6551_V_OUT1_PRE2_OFFSET (0x15A)
#define HI6551_V_OUT0_PRE3_OFFSET (0x15B)
#define HI6551_V_OUT1_PRE3_OFFSET (0x15C)
#define HI6551_V_OUT0_PRE4_OFFSET (0x15D)
#define HI6551_V_OUT1_PRE4_OFFSET (0x15E)
#define HI6551_V_OUT0_PRE5_OFFSET (0x15F)
#define HI6551_V_OUT1_PRE5_OFFSET (0x160)
#define HI6551_V_OUT0_PRE6_OFFSET (0x161)
#define HI6551_V_OUT1_PRE6_OFFSET (0x162)
#define HI6551_V_OUT0_PRE7_OFFSET (0x163)
#define HI6551_V_OUT1_PRE7_OFFSET (0x164)
#define HI6551_V_OUT0_PRE8_OFFSET (0x165)
#define HI6551_V_OUT1_PRE8_OFFSET (0x166)
#define HI6551_V_OUT0_PRE9_OFFSET (0x167)
#define HI6551_V_OUT1_PRE9_OFFSET (0x168)
#define HI6551_V_OUT0_PRE10_OFFSET (0x169)
#define HI6551_V_OUT1_PRE10_OFFSET (0x16A)
#define HI6551_V_OUT0_PRE11_OFFSET (0x16B)
#define HI6551_V_OUT1_PRE11_OFFSET (0x16C)
#define HI6551_V_OUT0_PRE12_OFFSET (0x16D)
#define HI6551_V_OUT1_PRE12_OFFSET (0x16E)
#define HI6551_V_OUT0_PRE13_OFFSET (0x16F)
#define HI6551_V_OUT1_PRE13_OFFSET (0x170)
#define HI6551_V_OUT0_PRE14_OFFSET (0x171)
#define HI6551_V_OUT1_PRE14_OFFSET (0x172)
#define HI6551_V_OUT0_PRE15_OFFSET (0x173)
#define HI6551_V_OUT1_PRE15_OFFSET (0x174)
#define HI6551_V_OUT0_PRE16_OFFSET (0x175)
#define HI6551_V_OUT1_PRE16_OFFSET (0x176)
#define HI6551_V_OUT0_PRE17_OFFSET (0x177)
#define HI6551_V_OUT1_PRE17_OFFSET (0x178)
#define HI6551_V_OUT0_PRE18_OFFSET (0x179)
#define HI6551_V_OUT1_PRE18_OFFSET (0x17A)
#define HI6551_V_OUT0_PRE19_OFFSET (0x17B)
#define HI6551_V_OUT1_PRE19_OFFSET (0x17C)
#define HI6551_CURRENT0_PRE0_OFFSET (0x17D)
#define HI6551_CURRENT1_PRE0_OFFSET (0x17E)
#define HI6551_CURRENT0_PRE1_OFFSET (0x17F)
#define HI6551_CURRENT1_PRE1_OFFSET (0x180)
#define HI6551_CURRENT0_PRE2_OFFSET (0x181)
#define HI6551_CURRENT1_PRE2_OFFSET (0x182)
#define HI6551_CURRENT0_PRE3_OFFSET (0x183)
#define HI6551_CURRENT1_PRE3_OFFSET (0x184)
#define HI6551_CURRENT0_PRE4_OFFSET (0x185)
#define HI6551_CURRENT1_PRE4_OFFSET (0x186)
#define HI6551_CURRENT0_PRE5_OFFSET (0x187)
#define HI6551_CURRENT1_PRE5_OFFSET (0x188)
#define HI6551_CURRENT0_PRE6_OFFSET (0x189)
#define HI6551_CURRENT1_PRE6_OFFSET (0x18A)
#define HI6551_CURRENT0_PRE7_OFFSET (0x18B)
#define HI6551_CURRENT1_PRE7_OFFSET (0x18C)
#define HI6551_CURRENT0_PRE8_OFFSET (0x18D)
#define HI6551_CURRENT1_PRE8_OFFSET (0x18E)
#define HI6551_CURRENT0_PRE9_OFFSET (0x18F)
#define HI6551_CURRENT1_PRE9_OFFSET (0x190)
#define HI6551_CURRENT0_PRE10_OFFSET (0x191)
#define HI6551_CURRENT1_PRE10_OFFSET (0x192)
#define HI6551_CURRENT0_PRE11_OFFSET (0x193)
#define HI6551_CURRENT1_PRE11_OFFSET (0x194)
#define HI6551_CURRENT0_PRE12_OFFSET (0x195)
#define HI6551_CURRENT1_PRE12_OFFSET (0x196)
#define HI6551_CURRENT0_PRE13_OFFSET (0x197)
#define HI6551_CURRENT1_PRE13_OFFSET (0x198)
#define HI6551_CURRENT0_PRE14_OFFSET (0x199)
#define HI6551_CURRENT1_PRE14_OFFSET (0x19A)
#define HI6551_CURRENT0_PRE15_OFFSET (0x19B)
#define HI6551_CURRENT1_PRE15_OFFSET (0x19C)
#define HI6551_CURRENT0_PRE16_OFFSET (0x19D)
#define HI6551_CURRENT1_PRE16_OFFSET (0x19E)
#define HI6551_CURRENT0_PRE17_OFFSET (0x19F)
#define HI6551_CURRENT1_PRE17_OFFSET (0x1A0)
#define HI6551_CURRENT0_PRE18_OFFSET (0x1A1)
#define HI6551_CURRENT1_PRE18_OFFSET (0x1A2)
#define HI6551_CURRENT0_PRE19_OFFSET (0x1A3)
#define HI6551_CURRENT1_PRE19_OFFSET (0x1A4)
#define HI6551_CLJ_DEBUG_OFFSET (0x1A5)
#define HI6551_STATE_TEST_OFFSET (0x1A6)
#define HI6551_CLJ_RESERVED1_OFFSET (0x1A7)
#define HI6551_CLJ_RESERVED2_OFFSET (0x1A8)
#define HI6551_CLJ_RESERVED3_OFFSET (0x1A9)
#define HI6551_CLJ_RESERVED4_OFFSET (0x1AA)
#define HI6551_CLJ_RESERVED5_OFFSET (0x1AB)
#define HI6551_CLJ_RESERVED6_OFFSET (0x1AC)
#define HI6551_CLJ_RESERVED7_OFFSET (0x1AD)
#define HI6551_CLJ_RESERVED8_OFFSET (0x1AE)
typedef union
{
    struct
    {
        unsigned int otmp_d1r : 1;
        unsigned int otmp150_d1r : 1;
        unsigned int osc_state : 1;
        unsigned int vsys_uv_d2f : 1;
        unsigned int vsys_6p0_d200ur : 1;
        unsigned int pwron_d20r : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_STATUS1_T;
typedef union
{
    struct
    {
        unsigned int alarm_on_a : 1;
        unsigned int alarm_on_b : 1;
        unsigned int alarm_on_c : 1;
        unsigned int alarm_on_d : 1;
        unsigned int alarm_on_e : 1;
        unsigned int vbus_det_0p9_d3r : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_STATUS2_T;
typedef union
{
    struct
    {
        unsigned int otmp_d1r : 1;
        unsigned int vsys_2p5_f : 1;
        unsigned int vsys_uv_d2f : 1;
        unsigned int vsys_6p0_d200ur : 1;
        unsigned int pwron_d4sr : 1;
        unsigned int pwron_d20f : 1;
        unsigned int pwron_d20r : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_IRQ1_T;
typedef union
{
    struct
    {
        unsigned int ocp_scp_r : 1;
        unsigned int vbus_det_1p375_d90ur : 1;
        unsigned int vbus_det_0p9_d3f : 1;
        unsigned int vbus_det_0p9_d3r : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_IRQ2_T;
typedef union
{
    struct
    {
        unsigned int alarm_on_a : 1;
        unsigned int alarm_on_b : 1;
        unsigned int alarm_on_c : 1;
        unsigned int alarm_on_d : 1;
        unsigned int alarm_on_e : 1;
        unsigned int alarm_on_f : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_IRQ3_T;
typedef union
{
    struct
    {
        unsigned int sim0_hpd_out_f : 1;
        unsigned int sim0_hpd_out_r : 1;
        unsigned int sim0_hpd_in_f : 1;
        unsigned int sim0_hpd_in_r : 1;
        unsigned int sim1_hpd_out_f : 1;
        unsigned int sim1_hpd_out_r : 1;
        unsigned int sim1_hpd_in_f : 1;
        unsigned int sim1_hpd_in_r : 1;
    } bits;
    unsigned int u32;
}HI6551_IRQ4_T;
typedef union
{
    struct
    {
        unsigned int cl_int_i : 1;
        unsigned int cl_out_i : 1;
        unsigned int cl_in_i : 1;
        unsigned int chg_timer_i : 1;
        unsigned int load_timer_i : 1;
        unsigned int vbat_int_i : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_COUL_IRQ_T;
typedef union
{
    struct
    {
        unsigned int otmp_d1r_mk : 1;
        unsigned int vsys_2p5_f_mk : 1;
        unsigned int vsys_uv_d2f_mk : 1;
        unsigned int vsys_6p0_d200ur_mk : 1;
        unsigned int pwron_d4sr_mk : 1;
        unsigned int pwron_d20f_mk : 1;
        unsigned int pwron_d20r_mk : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_IRQ1_MASK_T;
typedef union
{
    struct
    {
        unsigned int ocp_scp_r_mk : 1;
        unsigned int vbus_det_1p375_mk : 1;
        unsigned int vbus_det_0p9_d3f_mk : 1;
        unsigned int vbus_det_0p9_d3r_mk : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_IRQ2_MASK_T;
typedef union
{
    struct
    {
        unsigned int alarm_on_a_mk : 1;
        unsigned int alarm_on_b_mk : 1;
        unsigned int alarm_on_c_mk : 1;
        unsigned int alarm_on_d_mk : 1;
        unsigned int alarm_on_e_mk : 1;
        unsigned int alarm_on_f_mk : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_IRQ3_MASK_T;
typedef union
{
    struct
    {
        unsigned int sim0_hpd_out_f_mk : 1;
        unsigned int sim0_hpd_out_r_mk : 1;
        unsigned int sim0_hpd_in_f_mk : 1;
        unsigned int sim0_hpd_in_r_mk : 1;
        unsigned int sim1_hpd_out_f_mk : 1;
        unsigned int sim1_hpd_out_r_mk : 1;
        unsigned int sim1_hpd_in_f_mk : 1;
        unsigned int sim1_in_hpd_r_mk : 1;
    } bits;
    unsigned int u32;
}HI6551_IRQ4_MASK_T;
typedef union
{
    struct
    {
        unsigned int cl_int_i_mk : 1;
        unsigned int cl_out_i_mk : 1;
        unsigned int cl_in_i_mk : 1;
        unsigned int chg_timer_i_mk : 1;
        unsigned int load_timer_i_mk : 1;
        unsigned int vbat_int_i_mk : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_COUL_IRQ_MASK_T;
typedef union
{
    struct
    {
        unsigned int scp_buck0_1 : 1;
        unsigned int scp_buck2 : 1;
        unsigned int scp_buck3 : 1;
        unsigned int scp_buck4 : 1;
        unsigned int scp_buck5 : 1;
        unsigned int scp_buck6 : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_SCP_RECORD1_T;
typedef union
{
    struct
    {
        unsigned int ocp_buck0_1 : 1;
        unsigned int ocp_buck2 : 1;
        unsigned int ocp_buck3 : 1;
        unsigned int ocp_buck4 : 1;
        unsigned int ocp_buck5 : 1;
        unsigned int ocp_buck6 : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_OCP_RECORD1_T;
typedef union
{
    struct
    {
        unsigned int ocp_ldo1 : 1;
        unsigned int ocp_ldo2 : 1;
        unsigned int ocp_ldo3 : 1;
        unsigned int ocp_ldo4 : 1;
        unsigned int ocp_ldo5 : 1;
        unsigned int ocp_ldo6 : 1;
        unsigned int ocp_ldo7 : 1;
        unsigned int ocp_ldo8 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_RECORD2_T;
typedef union
{
    struct
    {
        unsigned int ocp_ldo9 : 1;
        unsigned int ocp_ldo10 : 1;
        unsigned int ocp_ldo11 : 1;
        unsigned int ocp_ldo12 : 1;
        unsigned int ocp_ldo13 : 1;
        unsigned int ocp_ldo14 : 1;
        unsigned int ocp_ldo15 : 1;
        unsigned int ocp_ldo16 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_RECORD3_T;
typedef union
{
    struct
    {
        unsigned int ocp_ldo17 : 1;
        unsigned int ocp_ldo18 : 1;
        unsigned int ocp_ldo19 : 1;
        unsigned int ocp_ldo20 : 1;
        unsigned int ocp_ldo21 : 1;
        unsigned int ocp_ldo22 : 1;
        unsigned int ocp_ldo23 : 1;
        unsigned int ocp_ldo24 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_RECORD4_T;
typedef union
{
    struct
    {
        unsigned int ocp_lvs2 : 1;
        unsigned int ocp_lvs3 : 1;
        unsigned int ocp_lvs4 : 1;
        unsigned int ocp_lvs5 : 1;
        unsigned int ocp_lvs7 : 1;
        unsigned int ocp_lvs6 : 1;
        unsigned int ocp_lvs8 : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_RECORD5_T;
typedef union
{
    struct
    {
        unsigned int ocp_lvs9 : 1;
        unsigned int ocp_lvs10 : 1;
        unsigned int reserved : 6;
    } bits;
    unsigned int u32;
}HI6551_OCP_RECORD6_T;
typedef union
{
    struct
    {
        unsigned int ocp_boost : 1;
        unsigned int scp_boost : 1;
        unsigned int ovp_boost : 1;
        unsigned int uvp_boost : 1;
        unsigned int ocp_classd : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_OCP_RECORD7_T;
typedef union
{
    struct
    {
        unsigned int np_otmp_d1r : 1;
        unsigned int np_hreset_n_f : 1;
        unsigned int np_vsys_2p5_f : 1;
        unsigned int np_vsys_uv_d2f : 1;
        unsigned int np_vsys_6p0_d200ur : 1;
        unsigned int np_pwron_d4sr : 1;
        unsigned int np_pwron_d20f : 1;
        unsigned int np_pwron_d20r : 1;
    } bits;
    unsigned int u32;
}HI6551_NP_IRQ1_RECORD_T;
typedef union
{
    struct
    {
        unsigned int np_vbus_det_0p9_d150r : 1;
        unsigned int np_vbus_det_1p375 : 1;
        unsigned int np_vbus_det_0p9_d3f : 1;
        unsigned int np_vbus_det_0p9_d3r : 1;
        unsigned int np_pwron_restart : 1;
        unsigned int np_pwron_dnsr : 1;
        unsigned int np_pwron_d500r : 1;
        unsigned int np_otmp150_d1r : 1;
    } bits;
    unsigned int u32;
}HI6551_NP_IRQ2_RECORD_T;
typedef union
{
    struct
    {
        unsigned int np_alarm_on_a : 1;
        unsigned int np_alarm_on_b : 1;
        unsigned int np_alarm_on_c : 1;
        unsigned int np_alarm_on_d : 1;
        unsigned int np_alarm_on_e : 1;
        unsigned int np_alarm_on_f : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_NP_IRQ3_RECORD_T;
typedef union
{
    struct
    {
        unsigned int np_scp_buck0_1 : 1;
        unsigned int np_scp_buck2 : 1;
        unsigned int np_scp_buck3 : 1;
        unsigned int np_scp_buck4 : 1;
        unsigned int np_scp_buck5 : 1;
        unsigned int np_scp_buck6 : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_NP_SCP_RECORD1_T;
typedef union
{
    struct
    {
        unsigned int np_ocp_buck0 : 1;
        unsigned int np_ocp_buck1 : 1;
        unsigned int np_ocp_buck0_1 : 1;
        unsigned int np_ocp_buck2 : 1;
        unsigned int np_ocp_buck3 : 1;
        unsigned int np_ocp_buck4 : 1;
        unsigned int np_ocp_buck5 : 1;
        unsigned int np_ocp_buck6 : 1;
    } bits;
    unsigned int u32;
}HI6551_NP_OCP_RECORD1_T;
typedef union
{
    struct
    {
        unsigned int np_ocp_ldo1 : 1;
        unsigned int np_ocp_ldo2 : 1;
        unsigned int np_ocp_ldo3 : 1;
        unsigned int np_ocp_ldo4 : 1;
        unsigned int np_ocp_ldo5 : 1;
        unsigned int np_ocp_ldo6 : 1;
        unsigned int np_ocp_ldo7 : 1;
        unsigned int np_ocp_ldo8 : 1;
    } bits;
    unsigned int u32;
}HI6551_NP_OCP_RECORD2_T;
typedef union
{
    struct
    {
        unsigned int np_ocp_ldo9 : 1;
        unsigned int np_ocp_ldo10 : 1;
        unsigned int np_ocp_ldo11 : 1;
        unsigned int np_ocp_ldo12 : 1;
        unsigned int np_ocp_ldo13 : 1;
        unsigned int np_ocp_ldo14 : 1;
        unsigned int np_ocp_ldo15 : 1;
        unsigned int np_ocp_ldo16 : 1;
    } bits;
    unsigned int u32;
}HI6551_NP_OCP_RECORD3_T;
typedef union
{
    struct
    {
        unsigned int np_ocp_ldo17 : 1;
        unsigned int np_ocp_ldo18 : 1;
        unsigned int np_ocp_ldo19 : 1;
        unsigned int np_ocp_ldo20 : 1;
        unsigned int np_ocp_ldo21 : 1;
        unsigned int np_ocp_ldo22 : 1;
        unsigned int np_ocp_ldo23 : 1;
        unsigned int np_ocp_ldo24 : 1;
    } bits;
    unsigned int u32;
}HI6551_NP_OCP_RECORD4_T;
typedef union
{
    struct
    {
        unsigned int np_ocp_lvs2 : 1;
        unsigned int np_ocp_lvs3 : 1;
        unsigned int np_ocp_lvs4 : 1;
        unsigned int np_ocp_lvs5 : 1;
        unsigned int np_ocp_lvs7 : 1;
        unsigned int np_ocp_lvs6 : 1;
        unsigned int np_ocp_lvs8 : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_NP_OCP_RECORD5_T;
typedef union
{
    struct
    {
        unsigned int np_ocp_lvs9 : 1;
        unsigned int np_ocp_lvs10 : 1;
        unsigned int reserved : 6;
    } bits;
    unsigned int u32;
}HI6551_NP_OCP_RECORD6_T;
typedef union
{
    struct
    {
        unsigned int np_ocp_boost : 1;
        unsigned int np_scp_boost : 1;
        unsigned int np_ovp_boost : 1;
        unsigned int np_uvp_boost : 1;
        unsigned int np_ocp_classd : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_NP_OCP_RECORD7_T;
typedef union
{
    struct
    {
        unsigned int ocp_ldo_deb_sel : 2;
        unsigned int en_ldo_ocp_deb : 1;
        unsigned int ocp_buck_deb_sel : 2;
        unsigned int en_buck_ocp_deb : 1;
        unsigned int en_buck_scp_deb : 1;
        unsigned int en_bst_ocp_deb : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_DEB_T;
typedef union
{
    struct
    {
        unsigned int vbus_det_0p9_ctrl : 1;
        unsigned int vsys_2p5_ctrl : 1;
        unsigned int vsys_uv_ctrl : 1;
        unsigned int vsys_6p0_ctrl : 1;
        unsigned int otmp150_ctrl : 1;
        unsigned int en_32kc : 1;
        unsigned int en_32kb : 1;
        unsigned int en_32ka : 1;
    } bits;
    unsigned int u32;
}HI6551_ONOFF8_T;
typedef union
{
    struct
    {
        unsigned int ocp_scp_ctrl_buck0_1 : 1;
        unsigned int ocp_scp_off_buck0_1 : 1;
        unsigned int ocp_scp_ctrl_buck2 : 1;
        unsigned int ocp_scp_off_buck2 : 1;
        unsigned int ocp_scp_ctrl_buck3 : 1;
        unsigned int ocp_scp_off_buck3 : 1;
        unsigned int ocp_scp_ctrl_buck4 : 1;
        unsigned int ocp_scp_off_buck4 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_SCP_MOD_CTRL1_T;
typedef union
{
    struct
    {
        unsigned int ocp_scp_ctrl_buck5 : 1;
        unsigned int ocp_scp_off_buck5 : 1;
        unsigned int ocp_scp_ctrl_buck6 : 1;
        unsigned int ocp_scp_off_buck6 : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_OCP_SCP_MOD_CTRL2_T;
typedef union
{
    struct
    {
        unsigned int ocp_ctrl_ldo1 : 1;
        unsigned int ocp_off_ldo1 : 1;
        unsigned int ocp_ctrl_ldo2 : 1;
        unsigned int ocp_off_ldo2 : 1;
        unsigned int ocp_ctrl_ldo3 : 1;
        unsigned int ocp_off_ldo3 : 1;
        unsigned int ocp_ctrl_ldo4 : 1;
        unsigned int ocp_off_ldo4 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_MOD_CTRL3_T;
typedef union
{
    struct
    {
        unsigned int ocp_ctrl_ldo5 : 1;
        unsigned int ocp_off_ldo5 : 1;
        unsigned int ocp_ctrl_ldo6 : 1;
        unsigned int ocp_off_ldo6 : 1;
        unsigned int ocp_ctrl_ldo7 : 1;
        unsigned int ocp_off_ldo7 : 1;
        unsigned int ocp_ctrl_ldo8 : 1;
        unsigned int ocp_off_ldo8 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_MOD_CTRL4_T;
typedef union
{
    struct
    {
        unsigned int ocp_ctrl_ldo9 : 1;
        unsigned int ocp_off_ldo9 : 1;
        unsigned int ocp_ctrl_ldo10 : 1;
        unsigned int ocp_off_ldo10 : 1;
        unsigned int ocp_ctrl_ldo11 : 1;
        unsigned int ocp_off_ldo11 : 1;
        unsigned int ocp_ctrl_ldo12 : 1;
        unsigned int ocp_off_ldo12 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_MOD_CTRL5_T;
typedef union
{
    struct
    {
        unsigned int ocp_ctrl_ldo13 : 1;
        unsigned int ocp_off_ldo13 : 1;
        unsigned int ocp_ctrl_ldo14 : 1;
        unsigned int ocp_off_ldo14 : 1;
        unsigned int ocp_ctrl_ldo15 : 1;
        unsigned int ocp_off_ldo15 : 1;
        unsigned int ocp_ctrl_ldo16 : 1;
        unsigned int ocp_off_ldo16 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_MOD_CTRL6_T;
typedef union
{
    struct
    {
        unsigned int ocp_ctrl_ldo17 : 1;
        unsigned int ocp_off_ldo17 : 1;
        unsigned int ocp_ctrl_ldo18 : 1;
        unsigned int ocp_off_ldo18 : 1;
        unsigned int ocp_ctrl_ldo19 : 1;
        unsigned int ocp_off_ldo19 : 1;
        unsigned int ocp_ctrl_ldo20 : 1;
        unsigned int ocp_off_ldo20 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_MOD_CTRL7_T;
typedef union
{
    struct
    {
        unsigned int ocp_ctrl_ldo21 : 1;
        unsigned int ocp_off_ldo21 : 1;
        unsigned int ocp_ctrl_ldo22 : 1;
        unsigned int ocp_off_ldo22 : 1;
        unsigned int ocp_ctrl_ldo23 : 1;
        unsigned int ocp_off_ldo23 : 1;
        unsigned int ocp_ctrl_ldo24 : 1;
        unsigned int ocp_off_ldo24 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_MOD_CTRL8_T;
typedef union
{
    struct
    {
        unsigned int ocp_ctrl_lvs2 : 1;
        unsigned int ocp_off_lvs2 : 1;
        unsigned int ocp_ctrl_lvs3 : 1;
        unsigned int ocp_off_lvs3 : 1;
        unsigned int ocp_ctrl_lvs4 : 1;
        unsigned int ocp_off_lvs4 : 1;
        unsigned int ocp_ctrl_lvs5 : 1;
        unsigned int ocp_off_lvs5 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_MOD_CTRL9_T;
typedef union
{
    struct
    {
        unsigned int ocp_ctrl_lvs7 : 1;
        unsigned int ocp_off_lvs7 : 1;
        unsigned int ocp_ctrl_lvs6 : 1;
        unsigned int ocp_off_lvs6 : 1;
        unsigned int ocp_ctrl_lvs8 : 1;
        unsigned int ocp_off_lvs8 : 1;
        unsigned int ocp_ctrl_lvs9 : 1;
        unsigned int ocp_off_lvs9 : 1;
    } bits;
    unsigned int u32;
}HI6551_OCP_MOD_CTRL10_T;
typedef union
{
    struct
    {
        unsigned int ocp_ctrl_lvs10 : 1;
        unsigned int ocp_off_lvs10 : 1;
        unsigned int ocp_ctrl_bst : 1;
        unsigned int ocp_off_bst : 1;
        unsigned int ocp_ctrl_classd : 1;
        unsigned int ocp_off_classd : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_OCP_MOD_CTRL11_T;
typedef union
{
    struct
    {
        unsigned int en_buck0_int : 1;
        unsigned int en_buck1_int : 1;
        unsigned int en_buck2_int : 1;
        unsigned int en_buck3_int : 1;
        unsigned int en_buck4_int : 1;
        unsigned int en_buck5_int : 1;
        unsigned int en_buck6_int : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_ENABLE1_T;
typedef union
{
    struct
    {
        unsigned int dis_buck0_int : 1;
        unsigned int dis_buck1_int : 1;
        unsigned int dis_buck2_int : 1;
        unsigned int dis_buck3_int : 1;
        unsigned int dis_buck4_int : 1;
        unsigned int dis_buck5_int : 1;
        unsigned int dis_buck6_int : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_DISABLE1_T;
typedef union
{
    struct
    {
        unsigned int st_buck0_int : 1;
        unsigned int st_buck1_int : 1;
        unsigned int st_buck2_int : 1;
        unsigned int st_buck3_int : 1;
        unsigned int st_buck4_int : 1;
        unsigned int st_buck5_int : 1;
        unsigned int st_buck6_int : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_ONOFF_STATUS1_T;
typedef union
{
    struct
    {
        unsigned int en_ldo1_int : 1;
        unsigned int en_ldo2_int : 1;
        unsigned int en_ldo3_buck_int : 1;
        unsigned int en_ldo4_int : 1;
        unsigned int en_ldo5_int : 1;
        unsigned int en_ldo6_int : 1;
        unsigned int en_ldo7_int : 1;
        unsigned int en_ldo8_int : 1;
    } bits;
    unsigned int u32;
}HI6551_ENABLE2_T;
typedef union
{
    struct
    {
        unsigned int dis_ldo1_int : 1;
        unsigned int dis_ldo2_int : 1;
        unsigned int dis_ldo3_buck_int : 1;
        unsigned int dis_ldo4_int : 1;
        unsigned int dis_ldo5_int : 1;
        unsigned int dis_ldo6_int : 1;
        unsigned int dis_ldo7_int : 1;
        unsigned int dis_ldo8_int : 1;
    } bits;
    unsigned int u32;
}HI6551_DISABLE2_T;
typedef union
{
    struct
    {
        unsigned int st_ldo1_int : 1;
        unsigned int st_ldo2_int : 1;
        unsigned int st_ldo3_buck_int : 1;
        unsigned int st_ldo4_int : 1;
        unsigned int st_ldo5_int : 1;
        unsigned int st_ldo6_int : 1;
        unsigned int st_ldo7_int : 1;
        unsigned int st_ldo8_int : 1;
    } bits;
    unsigned int u32;
}HI6551_ONOFF_STATUS2_T;
typedef union
{
    struct
    {
        unsigned int en_ldo10_int : 1;
        unsigned int en_ldo12_int : 1;
        unsigned int en_ldo13_int : 1;
        unsigned int en_ldo14_int : 1;
        unsigned int en_ldo15_int : 1;
        unsigned int en_ldo16_int : 1;
        unsigned int en_ldo17_int : 1;
        unsigned int en_ldo18_int : 1;
    } bits;
    unsigned int u32;
}HI6551_ENABLE3_T;
typedef union
{
    struct
    {
        unsigned int dis_ldo10_int : 1;
        unsigned int dis_ldo12_int : 1;
        unsigned int dis_ldo13_int : 1;
        unsigned int dis_ldo14_int : 1;
        unsigned int dis_ldo15_int : 1;
        unsigned int dis_ldo16_int : 1;
        unsigned int dis_ldo17_int : 1;
        unsigned int dis_ldo18_int : 1;
    } bits;
    unsigned int u32;
}HI6551_DISABLE3_T;
typedef union
{
    struct
    {
        unsigned int st_ldo10_int : 1;
        unsigned int st_ldo12_int : 1;
        unsigned int st_ldo13_int : 1;
        unsigned int st_ldo14_int : 1;
        unsigned int st_ldo15_int : 1;
        unsigned int st_ldo16_int : 1;
        unsigned int st_ldo17_int : 1;
        unsigned int st_ldo18_int : 1;
    } bits;
    unsigned int u32;
}HI6551_ONOFF_STATUS3_T;
typedef union
{
    struct
    {
        unsigned int en_ldo19_int : 1;
        unsigned int en_ldo20_int : 1;
        unsigned int en_ldo21_int : 1;
        unsigned int en_ldo22_int : 1;
        unsigned int en_ldo23_int : 1;
        unsigned int en_ldo24_int : 1;
        unsigned int en_ldo3_batt_int : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_ENABLE4_T;
typedef union
{
    struct
    {
        unsigned int dis_ldo19_int : 1;
        unsigned int dis_ldo20_int : 1;
        unsigned int dis_ldo21_int : 1;
        unsigned int dis_ldo22_int : 1;
        unsigned int dis_ldo23_int : 1;
        unsigned int dis_ldo24_int : 1;
        unsigned int dis_ldo3_batt_int : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_DISABLE4_T;
typedef union
{
    struct
    {
        unsigned int st_ldo19_int : 1;
        unsigned int st_ldo20_int : 1;
        unsigned int st_ldo21_int : 1;
        unsigned int st_ldo22_int : 1;
        unsigned int st_ldo23_int : 1;
        unsigned int st_ldo24_int : 1;
        unsigned int st_ldo3_batt_int : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_ONOFF_STATUS4_T;
typedef union
{
    struct
    {
        unsigned int en_lvs2_int : 1;
        unsigned int en_lvs3_int : 1;
        unsigned int en_lvs4_int : 1;
        unsigned int en_lvs5_int : 1;
        unsigned int en_lvs7_int : 1;
        unsigned int en_lvs6_int : 1;
        unsigned int en_lvs8_int : 1;
        unsigned int en_lvs9_int : 1;
    } bits;
    unsigned int u32;
}HI6551_ENABLE5_T;
typedef union
{
    struct
    {
        unsigned int dis_lvs2_int : 1;
        unsigned int dis_lvs3_int : 1;
        unsigned int dis_lvs4_int : 1;
        unsigned int dis_lvs5_int : 1;
        unsigned int dis_lvs7_int : 1;
        unsigned int dis_lvs6_int : 1;
        unsigned int dis_lvs8_int : 1;
        unsigned int dis_lvs9_int : 1;
    } bits;
    unsigned int u32;
}HI6551_DISABLE5_T;
typedef union
{
    struct
    {
        unsigned int st_lvs2_int : 1;
        unsigned int st_lvs3_int : 1;
        unsigned int st_lvs4_int : 1;
        unsigned int st_lvs5_int : 1;
        unsigned int st_lvs7_int : 1;
        unsigned int st_lvs6_int : 1;
        unsigned int st_lvs8_int : 1;
        unsigned int st_lvs9_int : 1;
    } bits;
    unsigned int u32;
}HI6551_ONOFF_STATUS5_T;
typedef union
{
    struct
    {
        unsigned int en_lvs10_int : 1;
        unsigned int reserved : 7;
    } bits;
    unsigned int u32;
}HI6551_ENABLE6_T;
typedef union
{
    struct
    {
        unsigned int dis_lvs10_int : 1;
        unsigned int reserved : 7;
    } bits;
    unsigned int u32;
}HI6551_DISABLE6_T;
typedef union
{
    struct
    {
        unsigned int st_lvs10_int : 1;
        unsigned int reserved : 7;
    } bits;
    unsigned int u32;
}HI6551_ONOFF_STATUS6_T;
typedef union
{
    struct
    {
        unsigned int en_cp2_int : 1;
        unsigned int cp2_always_on_int : 1;
        unsigned int reserved : 6;
    } bits;
    unsigned int u32;
}HI6551_ENABLE7_T;
typedef union
{
    struct
    {
        unsigned int en_ldo9_int : 1;
        unsigned int sim0_en_int : 1;
        unsigned int en_ldo11_int : 1;
        unsigned int sim1_en_int : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_SIMCARD_EN_T;
typedef union
{
    struct
    {
        unsigned int simcard0_resv : 2;
        unsigned int simcard0_bbrp : 1;
        unsigned int simcard0_simrp : 1;
        unsigned int simcard0_200ns_en : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_SIM0_CFG_T;
typedef union
{
    struct
    {
        unsigned int simcard1_resv : 2;
        unsigned int simcard1_bbrp : 1;
        unsigned int simcard1_simrp : 1;
        unsigned int simcard1_200ns_en : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_SIM1_CFG_T;
typedef union
{
    struct
    {
        unsigned int simcard_deb_sel : 5;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_SIM_DEB_T;
typedef union
{
    struct
    {
        unsigned int en_eco_buck3_int : 1;
        unsigned int en_eco_buck4_int : 1;
        unsigned int en_eco_buck5_int : 1;
        unsigned int en_eco_buck6_int : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_ECO_MOD_CFG1_T;
typedef union
{
    struct
    {
        unsigned int en_eco_ldo3_int : 1;
        unsigned int en_eco_ldo7_int : 1;
        unsigned int en_eco_ldo9_int : 1;
        unsigned int en_eco_ldo10_int : 1;
        unsigned int en_eco_ldo11_int : 1;
        unsigned int en_eco_ldo12_int : 1;
        unsigned int en_eco_ldo22_int : 1;
        unsigned int en_eco_ldo24_int : 1;
    } bits;
    unsigned int u32;
}HI6551_ECO_MOD_CFG2_T;
typedef union
{
    struct
    {
        unsigned int force_eco_buck3_int : 1;
        unsigned int force_eco_buck4_int : 1;
        unsigned int force_eco_buck5_int : 1;
        unsigned int force_eco_buck6_int : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_ECO_MOD_CFG3_T;
typedef union
{
    struct
    {
        unsigned int force_eco_ldo3_int : 1;
        unsigned int force_eco_ldo7_int : 1;
        unsigned int force_eco_ldo9_int : 1;
        unsigned int force_eco_ldo10_int : 1;
        unsigned int force_eco_ldo11_int : 1;
        unsigned int force_eco_ldo12_int : 1;
        unsigned int force_eco_ldo22_int : 1;
        unsigned int force_eco_ldo24_int : 1;
    } bits;
    unsigned int u32;
}HI6551_ECO_MOD_CFG4_T;
typedef union
{
    struct
    {
        unsigned int eco_pwrsel : 2;
        unsigned int peri_en_ctrl_ldo12 : 1;
        unsigned int peri_en_ctrl_lvs9 : 1;
        unsigned int peri_en_ctrl_ldo8 : 1;
        unsigned int peri_en_ctrl_buck3 : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_ENB3_ECO_MARK_T;
typedef union
{
    struct
    {
        unsigned int buck01_osc_d : 4;
        unsigned int buck0_pfm_vth_sel : 1;
        unsigned int buck0_sc_sel : 2;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG1_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck01_mod_sel : 2;
        unsigned int buck0_bt_sel : 1;
        unsigned int buck0_pd_sel : 1;
        unsigned int buck0_burst_drv_ctr : 1;
        unsigned int buck01_ocp_mod_sel : 1;
        unsigned int buck01_ocp_clamp_sel : 1;
        unsigned int buck01_ocp_shied_sel : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG2_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck0_vc_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck01_auto_pfm_ctr : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG3_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck0_isc_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck0_ipk_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG4_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck01_dt_sel : 2;
        unsigned int buck01_pg_dt_sel : 1;
        unsigned int buck01_ng_dt_sel : 1;
        unsigned int buck01_sft_sel : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG5_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck01_pg_p_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck01_pg_n_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG6_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck01_ng_p_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck01_ng_n_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG7_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck0_ccm_sel : 2;
        unsigned int buck1_ccm_sel : 2;
        unsigned int buck0_ccc_sel : 2;
        unsigned int buck0_cs_sel : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG8_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck0_dmd_sel : 2;
        unsigned int buck01_ton_off : 1;
        unsigned int buck01_pfm_sleep : 1;
        unsigned int buck01_ton_on : 2;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG9_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck01_new_dmd_sel : 5;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG10_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck0_ocp_sel : 4;
        unsigned int buck01_ocp_en : 1;
        unsigned int buck01_dmd_en : 1;
        unsigned int buck01_ea_sel : 1;
        unsigned int buck01_clk_sel : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG11_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck0_sleep_depth_adj : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck0_ea_comp_cap : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG12_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck01_slope_gen : 3;
        unsigned int buck01_pdn_lx_det : 1;
        unsigned int buck01_sleep_dmd : 1;
        unsigned int buck01_dmd_shield_n : 1;
        unsigned int buck01_ocp_delay_sel : 1;
        unsigned int buck01_dmd_clamp : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG13_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck01_slope_dc : 2;
        unsigned int buck01_unsleep : 1;
        unsigned int buck01_dmd_float : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG14_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck0_comp_adj1 : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG15_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck01_reserved1 : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG16_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck01_reserved0 : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK01_REG17_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_adj_rlx : 4;
        unsigned int buck2_adj_clx : 4;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG1_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_new_dmd_sel : 5;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG2_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_shield_i : 2;
        unsigned int buck2_en_regop_clamp : 1;
        unsigned int buck2_dmd_clamp : 1;
        unsigned int buck2_ocp_delay_sel : 1;
        unsigned int buck2_dmd_shield_n : 1;
        unsigned int buck2_sleep_dmd : 1;
        unsigned int buck2_pdn_lx_det : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG3_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_ocp_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck2_dmd_sel : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG4_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_ng_dt_sel : 1;
        unsigned int buck2_pg_dt_sel : 1;
        unsigned int buck2_sft_sel : 1;
        unsigned int buck2_sleep : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG5_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_pg_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck2_pg_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG6_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_ng_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck2_ng_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG7_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_dbias : 2;
        unsigned int buck2_ocp_d : 1;
        unsigned int reserved_1 : 1;
        unsigned int buck2_ton : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG8_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_nmos_off : 1;
        unsigned int buck2_reg_c : 1;
        unsigned int buck2_short_pdp : 1;
        unsigned int buck2_reg_ss_d : 1;
        unsigned int buck2_dt_sel : 2;
        unsigned int buck2_regop_c : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG9_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_reg_dr : 3;
        unsigned int buck2_en_reg : 1;
        unsigned int buck2_ocp_clamp_sel : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG10_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_reg_idr : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck2_reg_r : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG11_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_reserve : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK2_REG12_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_adj_rlx : 4;
        unsigned int buck3_adj_clx : 4;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG1_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_new_dmd_sel : 5;
        unsigned int buck3_ocp_sel : 2;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG2_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_dmd_sel : 2;
        unsigned int buck3_en_regop_clamp : 1;
        unsigned int buck3_dmd_clamp : 1;
        unsigned int buck3_ocp_delay_sel : 1;
        unsigned int buck3_dmd_shield_n : 1;
        unsigned int buck3_sleep_dmd : 1;
        unsigned int buck3_pdn_lx_det : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG3_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_ng_dt_sel : 1;
        unsigned int buck3_pg_dt_sel : 1;
        unsigned int buck3_sft_sel : 1;
        unsigned int reserved_1 : 1;
        unsigned int buck3_shield_i : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG4_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_pg_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck3_pg_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG5_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_ng_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck3_ng_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG6_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_dbias : 2;
        unsigned int buck3_ocp_d : 1;
        unsigned int reserved_1 : 1;
        unsigned int buck3_ton : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG7_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_nmos_off : 1;
        unsigned int buck3_reg_c : 1;
        unsigned int buck3_short_pdp : 1;
        unsigned int buck3_reg_ss_d : 1;
        unsigned int buck3_dt_sel : 2;
        unsigned int buck3_regop_c : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG8_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_reg_dr : 3;
        unsigned int buck3_en_reg : 1;
        unsigned int buck3_ocp_clamp_sel : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG9_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_reg_idr : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck3_reg_r : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG10_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_mos_sel : 2;
        unsigned int reserved : 6;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG11_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_reserve : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK3_REG12_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_adj_rlx : 4;
        unsigned int buck4_adj_clx : 4;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG1_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_new_dmd_sel : 5;
        unsigned int buck4_ocp_sel : 2;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG2_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_dmd_sel : 2;
        unsigned int buck4_en_regop_clamp : 1;
        unsigned int buck4_dmd_clamp : 1;
        unsigned int buck4_ocp_delay_sel : 1;
        unsigned int buck4_dmd_shield_n : 1;
        unsigned int buck4_sleep_dmd : 1;
        unsigned int buck4_pdn_lx_det : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG3_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_ng_dt_sel : 1;
        unsigned int buck4_pg_dt_sel : 1;
        unsigned int buck4_sft_sel : 1;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG4_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_pg_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck4_pg_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG5_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_ng_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck4_ng_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG6_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_dbias : 2;
        unsigned int buck4_ocp_d : 1;
        unsigned int reserved_1 : 1;
        unsigned int buck4_ton : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG7_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_nmos_off : 1;
        unsigned int buck4_reg_c : 1;
        unsigned int buck4_short_pdp : 1;
        unsigned int buck4_reg_ss_d : 1;
        unsigned int buck4_dt_sel : 2;
        unsigned int buck4_regop_c : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG8_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_reg_dr : 3;
        unsigned int buck4_en_reg : 1;
        unsigned int buck4_ocp_clamp_sel : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG9_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_reg_idr : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck4_reg_r : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG10_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_reserve : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK4_REG12_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_adj_rlx : 4;
        unsigned int buck5_adj_clx : 4;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG1_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_new_dmd_sel : 5;
        unsigned int buck5_ocp_sel : 2;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG2_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_dmd_sel : 2;
        unsigned int buck5_en_regop_clamp : 1;
        unsigned int buck5_dmd_clamp : 1;
        unsigned int buck5_ocp_delay_sel : 1;
        unsigned int buck5_dmd_shield_n : 1;
        unsigned int buck5_sleep_dmd : 1;
        unsigned int buck5_pdn_lx_det : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG3_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_ng_dt_sel : 1;
        unsigned int buck5_pg_dt_sel : 1;
        unsigned int buck5_sft_sel : 1;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG4_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_pg_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck5_pg_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG5_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_ng_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck5_ng_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG6_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_dbias : 2;
        unsigned int buck5_ocp_d : 1;
        unsigned int reserved_1 : 1;
        unsigned int buck5_ton : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG7_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_nmos_off : 1;
        unsigned int buck5_reg_c : 1;
        unsigned int buck5_short_pdp : 1;
        unsigned int buck5_reg_ss_d : 1;
        unsigned int buck5_dt_sel : 2;
        unsigned int buck5_regop_c : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG8_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_reg_dr : 3;
        unsigned int buck5_en_reg : 1;
        unsigned int buck5_ocp_clamp_sel : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG9_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_reg_idr : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck5_reg_r : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG10_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_reserve0 : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG12_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_reserve1 : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG13_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_reserve2 : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK5_REG14_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_adj_rlx : 4;
        unsigned int buck6_adj_clx : 4;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG1_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_new_dmd_sel : 5;
        unsigned int buck6_ocp_sel : 2;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG2_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_dmd_sel : 2;
        unsigned int buck6_en_regop_clamp : 1;
        unsigned int buck6_dmd_clamp : 1;
        unsigned int buck6_ocp_delay_sel : 1;
        unsigned int buck6_dmd_shield_n : 1;
        unsigned int buck6_sleep_dmd : 1;
        unsigned int buck6_pdn_lx_det : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG3_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_ng_dt_sel : 1;
        unsigned int buck6_pg_dt_sel : 1;
        unsigned int buck6_sft_sel : 1;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG4_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_pg_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck6_pg_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG5_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_ng_n_sel : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck6_ng_p_sel : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG6_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_dbias : 2;
        unsigned int buck6_ocp_d : 1;
        unsigned int reserved_1 : 1;
        unsigned int buck6_ton : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG7_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_nmos_off : 1;
        unsigned int buck6_reg_c : 1;
        unsigned int buck6_short_pdp : 1;
        unsigned int buck6_reg_ss_d : 1;
        unsigned int buck6_dt_sel : 2;
        unsigned int buck6_regop_c : 1;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG8_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_reg_dr : 3;
        unsigned int buck6_en_reg : 1;
        unsigned int buck6_ocp_clamp_sel : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG9_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_reg_idr : 2;
        unsigned int reserved_1 : 2;
        unsigned int buck6_reg_r : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG10_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_mos_sel : 2;
        unsigned int reserved : 6;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG11_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_reserve : 8;
    } bits;
    unsigned int u32;
}HI6551_BUCK6_REG12_ADJ_T;
typedef union
{
    struct
    {
        unsigned int cp2_vout_sel : 2;
        unsigned int reserved : 6;
    } bits;
    unsigned int u32;
}HI6551_CHG_PUMP2_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck0_vck : 6;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_VSET_BUCK01_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck2_dv : 8;
    } bits;
    unsigned int u32;
}HI6551_VSET_BUCK2_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck3_dv : 4;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_VSET_BUCK3_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck4_dv : 4;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_VSET_BUCK4_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck5_dv : 8;
    } bits;
    unsigned int u32;
}HI6551_VSET_BUCK5_ADJ_T;
typedef union
{
    struct
    {
        unsigned int buck6_dv : 4;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_VSET_BUCK6_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo1 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_LDO1_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo2 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_LDO2_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo3 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo3 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO3_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo4 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_LDO4_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo5 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo5 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO5_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo6 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_LDO6_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo7 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_LDO7_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo8 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo8 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO8_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo9 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo9 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO9_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo10 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo10 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO10_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo11 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo11 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO11_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo12 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo12 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO12_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo13 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_LDO13_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo14 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo14 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO14_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo15 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo15 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO15_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo16 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo16 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO16_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo17 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo17 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO17_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo18 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo18 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO18_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo19 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo19 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO19_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo20 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo20 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO20_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo21 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo21 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO21_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo22 : 3;
        unsigned int en_sink_ldo22 : 1;
        unsigned int rset_sink_ldo22 : 2;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_LDO22_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo23 : 3;
        unsigned int reserved_1 : 1;
        unsigned int vrset_ldo23 : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_LDO23_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_ldo24 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_LDO24_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int vset_pmua : 3;
        unsigned int eco_pmua : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_PMUA_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int sstset_lvs5 : 2;
        unsigned int sstset_lvs4 : 2;
        unsigned int sstset_lvs3 : 2;
        unsigned int sstset_lvs2 : 2;
    } bits;
    unsigned int u32;
}HI6551_LVS_ADJ1_T;
typedef union
{
    struct
    {
        unsigned int sstset_lvs9 : 2;
        unsigned int sstset_lvs8 : 2;
        unsigned int sstset_lvs7 : 2;
        unsigned int sstset_lvs6 : 2;
    } bits;
    unsigned int u32;
}HI6551_LVS_ADJ2_T;
typedef union
{
    struct
    {
        unsigned int sstset_lvs10 : 2;
        unsigned int reserved : 6;
    } bits;
    unsigned int u32;
}HI6551_LVS_ADJ3_T;
typedef union
{
    struct
    {
        unsigned int en_bst_int : 1;
        unsigned int bst_pm_th : 1;
        unsigned int bst_pm_cut : 1;
        unsigned int bst_reserved0 : 5;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ0_T;
typedef union
{
    struct
    {
        unsigned int bst_sel_scp : 1;
        unsigned int bst_sel_pd : 1;
        unsigned int bst_en_uvp : 1;
        unsigned int bst_en_scp : 1;
        unsigned int bst_en_ovp : 1;
        unsigned int bst_en_ocp : 1;
        unsigned int bst_reserved1 : 2;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ1_T;
typedef union
{
    struct
    {
        unsigned int bst_drv_mode : 1;
        unsigned int bst_loop_mode : 1;
        unsigned int bst_en_pfm : 1;
        unsigned int bst_en_nring : 1;
        unsigned int bst_en_clp_os : 1;
        unsigned int bst_en_slop : 1;
        unsigned int bst_en_dmd : 1;
        unsigned int bst_reserved2 : 1;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ2_T;
typedef union
{
    struct
    {
        unsigned int bst_clp : 3;
        unsigned int bst_itail : 1;
        unsigned int bst_gm : 3;
        unsigned int bst_reserved3 : 1;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ3_T;
typedef union
{
    struct
    {
        unsigned int bst_ccom2 : 2;
        unsigned int bst_ccom1 : 2;
        unsigned int bst_rcom : 2;
        unsigned int bst_reserved4 : 2;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ4_T;
typedef union
{
    struct
    {
        unsigned int bst_slop : 2;
        unsigned int bst_ri : 2;
        unsigned int bst_reserved5 : 4;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ5_T;
typedef union
{
    struct
    {
        unsigned int bst_nsn : 2;
        unsigned int bst_nsp : 2;
        unsigned int bst_psn : 2;
        unsigned int bst_psp : 2;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ6_T;
typedef union
{
    struct
    {
        unsigned int bst_dt_nm : 2;
        unsigned int bst_dt_pm : 2;
        unsigned int bst_lxde : 2;
        unsigned int bst_reserved6 : 2;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ7_T;
typedef union
{
    struct
    {
        unsigned int bst_ckmin : 2;
        unsigned int bst_osc : 4;
        unsigned int bst_reserved7 : 2;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ8_T;
typedef union
{
    struct
    {
        unsigned int vo : 3;
        unsigned int sel_ocp : 2;
        unsigned int bst_start : 3;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ9_T;
typedef union
{
    struct
    {
        unsigned int bst_dmd_ofs : 4;
        unsigned int bst_reserved10 : 4;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ10_T;
typedef union
{
    struct
    {
        unsigned int bst_v2clp : 2;
        unsigned int bst_v2div : 2;
        unsigned int bst_v2ramp : 2;
        unsigned int bst_reserved11 : 2;
    } bits;
    unsigned int u32;
}HI6551_BOOST_ADJ11_T;
typedef union
{
    struct
    {
        unsigned int classd_mute_sel : 1;
        unsigned int classd_mute : 1;
        unsigned int classd_gain : 2;
        unsigned int en_classd_int : 1;
        unsigned int classd_i_ocp : 2;
        unsigned int reserved : 1;
    } bits;
    unsigned int u32;
}HI6551_CLASSD_ADJ0_T;
typedef union
{
    struct
    {
        unsigned int classd_n_sel : 2;
        unsigned int classd_p_sel : 2;
        unsigned int classd_i_ramp : 2;
        unsigned int classd_i_pump : 2;
    } bits;
    unsigned int u32;
}HI6551_CLASSD_ADJ1_T;
typedef union
{
    struct
    {
        unsigned int classd_ocp_bps : 1;
        unsigned int classd_fx_bps : 1;
        unsigned int classd_dt_sel : 1;
        unsigned int classd_pls_byp : 1;
        unsigned int classd_reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_CLASSD_ADJ2_T;
typedef union
{
    struct
    {
        unsigned int bg_test : 4;
        unsigned int bg_sleep : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_BANDGAP_THSD_ADJ1_T;
typedef union
{
    struct
    {
        unsigned int en_tmp_int : 2;
        unsigned int reserved_1 : 2;
        unsigned int thsd_set_tmp : 2;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_BANDGAP_THSD_ADJ2_T;
typedef union
{
    struct
    {
        unsigned int en_dr3_int : 1;
        unsigned int dr3_mode : 1;
        unsigned int en_dr4_int : 1;
        unsigned int dr4_mode : 1;
        unsigned int en_dr5_int : 1;
        unsigned int dr5_mode : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_DR_FLA_CTRL1_T;
typedef union
{
    struct
    {
        unsigned int en_dr1_int : 1;
        unsigned int dr1_mode : 1;
        unsigned int reserved_1 : 2;
        unsigned int en_dr2_int : 1;
        unsigned int dr2_mode : 1;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_DR_FLA_CTRL2_T;
typedef union
{
    struct
    {
        unsigned int flash_period : 8;
    } bits;
    unsigned int u32;
}HI6551_FLASH_PERIOD_T;
typedef union
{
    struct
    {
        unsigned int flash_on : 8;
    } bits;
    unsigned int u32;
}HI6551_FLASH_ON_T;
typedef union
{
    struct
    {
        unsigned int dr1_mode_sel : 1;
        unsigned int dr2_mode_sel : 1;
        unsigned int dr3_mode_sel : 1;
        unsigned int dr4_mode_sel : 1;
        unsigned int dr5_mode_sel : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_DR_MODE_SEL_T;
typedef union
{
    struct
    {
        unsigned int dr1_en : 1;
        unsigned int dr1_flash_en : 1;
        unsigned int reserved_1 : 2;
        unsigned int dr2_en : 1;
        unsigned int dr2_flash_en : 1;
        unsigned int reserved_0 : 2;
    } bits;
    unsigned int u32;
}HI6551_DR_BRE_CTRL_T;
typedef union
{
    struct
    {
        unsigned int dr1_t_off : 3;
        unsigned int reserved_1 : 1;
        unsigned int dr1_t_on : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_DR1_TIM_CONF0_T;
typedef union
{
    struct
    {
        unsigned int dr1_t_rise : 3;
        unsigned int reserved_1 : 1;
        unsigned int dr1_t_fall : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_DR1_TIM_CONF1_T;
typedef union
{
    struct
    {
        unsigned int iset_dr1 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_DR1_ISET_T;
typedef union
{
    struct
    {
        unsigned int dr2_t_off : 3;
        unsigned int reserved_1 : 1;
        unsigned int dr2_t_on : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_DR2_TIM_CONF0_T;
typedef union
{
    struct
    {
        unsigned int dr2_t_rise : 3;
        unsigned int reserved_1 : 1;
        unsigned int dr2_t_fall : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_DR2_TIM_CONF1_T;
typedef union
{
    struct
    {
        unsigned int iset_dr2 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_DR2_ISET_T;
typedef union
{
    struct
    {
        unsigned int dr3_en : 1;
        unsigned int dr4_en : 1;
        unsigned int dr5_en : 1;
        unsigned int dr_eco_en : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_DR_LED_CTRL_T;
typedef union
{
    struct
    {
        unsigned int dr3_out_ctrl : 2;
        unsigned int dr4_out_ctrl : 2;
        unsigned int dr5_out_ctrl : 2;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_DR_OUT_CTRL_T;
typedef union
{
    struct
    {
        unsigned int iset_dr3 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_DR3_ISET_T;
typedef union
{
    struct
    {
        unsigned int dr3_start_delay : 8;
    } bits;
    unsigned int u32;
}HI6551_DR3_START_DEL_T;
typedef union
{
    struct
    {
        unsigned int dr3_t_off : 4;
        unsigned int dr3_t_on : 4;
    } bits;
    unsigned int u32;
}HI6551_DR3_TIM_CONF0_T;
typedef union
{
    struct
    {
        unsigned int dr3_t_rise : 3;
        unsigned int reserved_1 : 1;
        unsigned int dr3_t_fall : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_DR3_TIM_CONF1_T;
typedef union
{
    struct
    {
        unsigned int iset_dr4 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_DR4_ISET_T;
typedef union
{
    struct
    {
        unsigned int dr4_start_delay : 8;
    } bits;
    unsigned int u32;
}HI6551_DR4_START_DEL_T;
typedef union
{
    struct
    {
        unsigned int dr4_t_off : 4;
        unsigned int dr4_t_on : 4;
    } bits;
    unsigned int u32;
}HI6551_DR4_TIM_CONF0_T;
typedef union
{
    struct
    {
        unsigned int dr4_t_rise : 3;
        unsigned int reserved_1 : 1;
        unsigned int dr4_t_fall : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_DR4_TIM_CONF1_T;
typedef union
{
    struct
    {
        unsigned int iset_dr5 : 3;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_DR5_ISET_T;
typedef union
{
    struct
    {
        unsigned int dr5_start_delay : 8;
    } bits;
    unsigned int u32;
}HI6551_DR5_START_DEL_T;
typedef union
{
    struct
    {
        unsigned int dr5_t_off : 4;
        unsigned int dr5_t_on : 4;
    } bits;
    unsigned int u32;
}HI6551_DR5_TIM_CONF0_T;
typedef union
{
    struct
    {
        unsigned int dr5_t_rise : 3;
        unsigned int reserved_1 : 1;
        unsigned int dr5_t_fall : 3;
        unsigned int reserved_0 : 1;
    } bits;
    unsigned int u32;
}HI6551_DR5_TIM_CONF1_T;
typedef union
{
    struct
    {
        unsigned int otp_pwe_int : 1;
        unsigned int otp_pwe_pulse : 1;
        unsigned int otp_write_mask : 1;
        unsigned int otp_por_int : 1;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_OTP_CTRL1_T;
typedef union
{
    struct
    {
        unsigned int otp_pa : 2;
        unsigned int otp_ptm : 2;
        unsigned int otp_pprog : 1;
        unsigned int reserved : 3;
    } bits;
    unsigned int u32;
}HI6551_OTP_CTRL2_T;
typedef union
{
    struct
    {
        unsigned int otp_pdin : 8;
    } bits;
    unsigned int u32;
}HI6551_OTP_PDIN_T;
typedef union
{
    struct
    {
        unsigned int otp_pdob0 : 8;
    } bits;
    unsigned int u32;
}HI6551_OTP_PDOB0_T;
typedef union
{
    struct
    {
        unsigned int otp_pdob1 : 8;
    } bits;
    unsigned int u32;
}HI6551_OTP_PDOB1_T;
typedef union
{
    struct
    {
        unsigned int otp_pdob2 : 8;
    } bits;
    unsigned int u32;
}HI6551_OTP_PDOB2_T;
typedef union
{
    struct
    {
        unsigned int otp_pdob3 : 8;
    } bits;
    unsigned int u32;
}HI6551_OTP_PDOB3_T;
typedef union
{
    struct
    {
        unsigned int rtccr_a0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCCR_A0_T;
typedef union
{
    struct
    {
        unsigned int rtccr_a1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCCR_A1_T;
typedef union
{
    struct
    {
        unsigned int rtccr_a2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCCR_A2_T;
typedef union
{
    struct
    {
        unsigned int rtccr_a3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCCR_A3_T;
typedef union
{
    struct
    {
        unsigned int rtclr_a0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCLR_A0_T;
typedef union
{
    struct
    {
        unsigned int rtclr_a1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCLR_A1_T;
typedef union
{
    struct
    {
        unsigned int rtclr_a2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCLR_A2_T;
typedef union
{
    struct
    {
        unsigned int rtclr_a3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCLR_A3_T;
typedef union
{
    struct
    {
        unsigned int rtccr_a : 1;
        unsigned int reserved : 7;
    } bits;
    unsigned int u32;
}HI6551_RTCCTRL_A_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_a0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_A0_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_a1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_A1_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_a2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_A2_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_a3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_A3_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_b0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_B0_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_b1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_B1_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_b2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_B2_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_b3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_B3_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_c0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_C0_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_c1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_C1_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_c2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_C2_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_c3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_C3_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_d0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_D0_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_d1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_D1_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_d2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_D2_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_d3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_D3_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_e0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_E0_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_e1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_E1_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_e2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_E2_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_e3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_E3_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_f0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_F0_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_f1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_F1_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_f2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_F2_T;
typedef union
{
    struct
    {
        unsigned int rtcmr_a_f3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCMR_A_F3_T;
typedef union
{
    struct
    {
        unsigned int rtccr_na0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCCR_NA0_T;
typedef union
{
    struct
    {
        unsigned int rtccr_na1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCCR_NA1_T;
typedef union
{
    struct
    {
        unsigned int rtccr_na2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCCR_NA2_T;
typedef union
{
    struct
    {
        unsigned int rtccr_na3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCCR_NA3_T;
typedef union
{
    struct
    {
        unsigned int rtclr_na0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCLR_NA0_T;
typedef union
{
    struct
    {
        unsigned int rtclr_na1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCLR_NA1_T;
typedef union
{
    struct
    {
        unsigned int rtclr_na2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCLR_NA2_T;
typedef union
{
    struct
    {
        unsigned int rtclr_na3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTCLR_NA3_T;
typedef union
{
    struct
    {
        unsigned int rtccr_na : 1;
        unsigned int reserved : 7;
    } bits;
    unsigned int u32;
}HI6551_RTCCTRL_NA_T;
typedef union
{
    struct
    {
        unsigned int version : 8;
    } bits;
    unsigned int u32;
}HI6551_VERSION_T;
typedef union
{
    struct
    {
        unsigned int reserved0 : 8;
    } bits;
    unsigned int u32;
}HI6551_RESERVED0_T;
typedef union
{
    struct
    {
        unsigned int reserved1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RESERVED1_T;
typedef union
{
    struct
    {
        unsigned int reserved2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RESERVED2_T;
typedef union
{
    struct
    {
        unsigned int reserved3 : 8;
    } bits;
    unsigned int u32;
}HI6551_RESERVED3_T;
typedef union
{
    struct
    {
        unsigned int reserved4 : 8;
    } bits;
    unsigned int u32;
}HI6551_RESERVED4_T;
typedef union
{
    struct
    {
        unsigned int htol_mode : 4;
        unsigned int reserved : 4;
    } bits;
    unsigned int u32;
}HI6551_HTOL_MODE_T;
typedef union
{
    struct
    {
        unsigned int dac_on_sel : 1;
        unsigned int aux_ibias_cfg : 2;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_DAC_CTRL_T;
typedef union
{
    struct
    {
        unsigned int soft_rst : 8;
    } bits;
    unsigned int u32;
}HI6551_CHIP_SOFT_RST_T;
typedef union
{
    struct
    {
        unsigned int pdns_sel : 3;
        unsigned int pdns_mk : 1;
        unsigned int vsys_uv_adj : 1;
        unsigned int nopwr_rc_off : 1;
        unsigned int reserved : 2;
    } bits;
    unsigned int u32;
}HI6551_NP_REG_ADJ_T;
typedef union
{
    struct
    {
        unsigned int nopwr_vcoinsl : 2;
        unsigned int nopwr_en_backup_chg : 1;
        unsigned int reserved : 5;
    } bits;
    unsigned int u32;
}HI6551_NP_REG_CHG_T;
typedef union
{
    struct
    {
        unsigned int no_pwr_resved1 : 8;
    } bits;
    unsigned int u32;
}HI6551_NP_RSVED1_T;
typedef union
{
    struct
    {
        unsigned int no_pwr_resved2 : 8;
    } bits;
    unsigned int u32;
}HI6551_NP_RSVED2_T;
typedef union
{
    struct
    {
        unsigned int no_pwr_resved3 : 8;
    } bits;
    unsigned int u32;
}HI6551_NP_RSVED3_T;
typedef union
{
    struct
    {
        unsigned int no_pwr_resved4 : 8;
    } bits;
    unsigned int u32;
}HI6551_NP_RSVED4_T;
typedef union
{
    struct
    {
        unsigned int rtc_clk_step_adj1 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTC_ADJ1_T;
typedef union
{
    struct
    {
        unsigned int rtc_clk_step_adj2 : 8;
    } bits;
    unsigned int u32;
}HI6551_RTC_ADJ2_T;
typedef union
{
    struct
    {
        unsigned int eco_ctrl : 3;
        unsigned int reflash_value_ctrl : 1;
        unsigned int eco_filter_time : 2;
        unsigned int calibration_ctrl : 1;
        unsigned int coul_ctrl_onoff_reg : 1;
    } bits;
    unsigned int u32;
}HI6551_CLJ_CTRL_REG_T;
typedef union
{
    struct
    {
        unsigned int eco_reflash_time : 8;
    } bits;
    unsigned int u32;
}HI6551_ECO_REFALSH_TIME_T;
typedef union
{
    struct
    {
        unsigned int cl_out0 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_OUT0_T;
typedef union
{
    struct
    {
        unsigned int cl_out1 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_OUT1_T;
typedef union
{
    struct
    {
        unsigned int cl_out2 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_OUT2_T;
typedef union
{
    struct
    {
        unsigned int cl_out3 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_OUT3_T;
typedef union
{
    struct
    {
        unsigned int cl_in0 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_IN0_T;
typedef union
{
    struct
    {
        unsigned int cl_in1 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_IN1_T;
typedef union
{
    struct
    {
        unsigned int cl_in2 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_IN2_T;
typedef union
{
    struct
    {
        unsigned int cl_in3 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_IN3_T;
typedef union
{
    struct
    {
        unsigned int chg_timer0 : 8;
    } bits;
    unsigned int u32;
}HI6551_CHG_TIMER0_T;
typedef union
{
    struct
    {
        unsigned int chg_timer1 : 8;
    } bits;
    unsigned int u32;
}HI6551_CHG_TIMER1_T;
typedef union
{
    struct
    {
        unsigned int chg_timer2 : 8;
    } bits;
    unsigned int u32;
}HI6551_CHG_TIMER2_T;
typedef union
{
    struct
    {
        unsigned int chg_timer3 : 8;
    } bits;
    unsigned int u32;
}HI6551_CHG_TIMER3_T;
typedef union
{
    struct
    {
        unsigned int load_timer0 : 8;
    } bits;
    unsigned int u32;
}HI6551_LOAD_TIMER0_T;
typedef union
{
    struct
    {
        unsigned int load_timer1 : 8;
    } bits;
    unsigned int u32;
}HI6551_LOAD_TIMER1_T;
typedef union
{
    struct
    {
        unsigned int load_timer2 : 8;
    } bits;
    unsigned int u32;
}HI6551_LOAD_TIMER2_T;
typedef union
{
    struct
    {
        unsigned int load_timer3 : 8;
    } bits;
    unsigned int u32;
}HI6551_LOAD_TIMER3_T;
typedef union
{
    struct
    {
        unsigned int off_timer0 : 8;
    } bits;
    unsigned int u32;
}HI6551_OFF_TIMER0_T;
typedef union
{
    struct
    {
        unsigned int off_timer1 : 8;
    } bits;
    unsigned int u32;
}HI6551_OFF_TIMER1_T;
typedef union
{
    struct
    {
        unsigned int off_timer2 : 8;
    } bits;
    unsigned int u32;
}HI6551_OFF_TIMER2_T;
typedef union
{
    struct
    {
        unsigned int off_timer3 : 8;
    } bits;
    unsigned int u32;
}HI6551_OFF_TIMER3_T;
typedef union
{
    struct
    {
        unsigned int cl_int0 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_INT0_T;
typedef union
{
    struct
    {
        unsigned int cl_int1 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_INT1_T;
typedef union
{
    struct
    {
        unsigned int cl_int2 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_INT2_T;
typedef union
{
    struct
    {
        unsigned int cl_int3 : 8;
    } bits;
    unsigned int u32;
}HI6551_CL_INT3_T;
typedef union
{
    struct
    {
        unsigned int v_int0 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_INT0_T;
typedef union
{
    struct
    {
        unsigned int v_int1 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_INT1_T;
typedef union
{
    struct
    {
        unsigned int offset_current0 : 8;
    } bits;
    unsigned int u32;
}HI6551_OFFSET_CURRENT0_T;
typedef union
{
    struct
    {
        unsigned int offset_current1 : 8;
    } bits;
    unsigned int u32;
}HI6551_OFFSET_CURRENT1_T;
typedef union
{
    struct
    {
        unsigned int offset_voltage0 : 8;
    } bits;
    unsigned int u32;
}HI6551_OFFSET_VOLTAGE0_T;
typedef union
{
    struct
    {
        unsigned int offset_voltage1 : 8;
    } bits;
    unsigned int u32;
}HI6551_OFFSET_VOLTAGE1_T;
typedef union
{
    struct
    {
        unsigned int ocv_data0 : 8;
    } bits;
    unsigned int u32;
}HI6551_OCV_DATA1_T;
typedef union
{
    struct
    {
        unsigned int ocv_data1 : 8;
    } bits;
    unsigned int u32;
}HI6551_OCV_DATA2_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre0 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE0_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre0 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE0_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre1 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE1_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre1 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE1_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre2 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE2_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre2 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE2_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre3 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE3_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre3 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE3_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre4 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE4_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre4 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE4_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre5 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE5_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre5 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE5_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre6 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE6_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre6 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE6_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre7 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE7_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre7 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE7_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre8 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE8_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre8 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE8_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre9 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE9_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre9 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE9_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre10 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE10_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre10 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE10_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre11 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE11_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre11 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE11_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre12 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE12_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre12 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE12_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre13 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE13_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre13 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE13_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre14 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE14_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre14 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE14_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre15 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE15_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre15 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE15_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre16 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE16_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre16 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE16_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre17 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE17_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre17 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE17_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre18 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE18_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre18 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE18_T;
typedef union
{
    struct
    {
        unsigned int v_out0_pre19 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT0_PRE19_T;
typedef union
{
    struct
    {
        unsigned int v_out1_pre19 : 8;
    } bits;
    unsigned int u32;
}HI6551_V_OUT1_PRE19_T;
typedef union
{
    struct
    {
        unsigned int current0_pre0 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE0_T;
typedef union
{
    struct
    {
        unsigned int current1_pre0 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE0_T;
typedef union
{
    struct
    {
        unsigned int current0_pre1 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE1_T;
typedef union
{
    struct
    {
        unsigned int current1_pre1 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE1_T;
typedef union
{
    struct
    {
        unsigned int current0_pre2 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE2_T;
typedef union
{
    struct
    {
        unsigned int current1_pre2 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE2_T;
typedef union
{
    struct
    {
        unsigned int current0_pre3 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE3_T;
typedef union
{
    struct
    {
        unsigned int current1_pre3 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE3_T;
typedef union
{
    struct
    {
        unsigned int current0_pre4 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE4_T;
typedef union
{
    struct
    {
        unsigned int current1_pre4 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE4_T;
typedef union
{
    struct
    {
        unsigned int current0_pre5 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE5_T;
typedef union
{
    struct
    {
        unsigned int current1_pre5 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE5_T;
typedef union
{
    struct
    {
        unsigned int current0_pre6 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE6_T;
typedef union
{
    struct
    {
        unsigned int current1_pre6 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE6_T;
typedef union
{
    struct
    {
        unsigned int current0_pre7 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE7_T;
typedef union
{
    struct
    {
        unsigned int current1_pre7 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE7_T;
typedef union
{
    struct
    {
        unsigned int current0_pre8 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE8_T;
typedef union
{
    struct
    {
        unsigned int current1_pre8 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE8_T;
typedef union
{
    struct
    {
        unsigned int current0_pre9 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE9_T;
typedef union
{
    struct
    {
        unsigned int current1_pre9 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE9_T;
typedef union
{
    struct
    {
        unsigned int current0_pre10 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE10_T;
typedef union
{
    struct
    {
        unsigned int current1_pre10 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE10_T;
typedef union
{
    struct
    {
        unsigned int current0_pre11 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE11_T;
typedef union
{
    struct
    {
        unsigned int current1_pre11 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE11_T;
typedef union
{
    struct
    {
        unsigned int current0_pre12 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE12_T;
typedef union
{
    struct
    {
        unsigned int current1_pre12 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE12_T;
typedef union
{
    struct
    {
        unsigned int current0_pre13 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE13_T;
typedef union
{
    struct
    {
        unsigned int current1_pre13 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE13_T;
typedef union
{
    struct
    {
        unsigned int current0_pre14 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE14_T;
typedef union
{
    struct
    {
        unsigned int current1_pre14 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE14_T;
typedef union
{
    struct
    {
        unsigned int current0_pre15 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE15_T;
typedef union
{
    struct
    {
        unsigned int current1_pre15 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE15_T;
typedef union
{
    struct
    {
        unsigned int current0_pre16 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE16_T;
typedef union
{
    struct
    {
        unsigned int current1_pre16 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE16_T;
typedef union
{
    struct
    {
        unsigned int current0_pre17 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE17_T;
typedef union
{
    struct
    {
        unsigned int current1_pre17 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE17_T;
typedef union
{
    struct
    {
        unsigned int current0_pre18 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE18_T;
typedef union
{
    struct
    {
        unsigned int current1_pre18 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE18_T;
typedef union
{
    struct
    {
        unsigned int current0_pre19 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT0_PRE19_T;
typedef union
{
    struct
    {
        unsigned int current1_pre19 : 8;
    } bits;
    unsigned int u32;
}HI6551_CURRENT1_PRE19_T;
typedef union
{
    struct
    {
        unsigned int cic_clk_inv_i : 1;
        unsigned int cic_clk_inv_v : 1;
        unsigned int adc_ana_v_output : 1;
        unsigned int adc_ana_i_output : 1;
        unsigned int cali_en_i : 1;
        unsigned int cali_en_i_force : 1;
        unsigned int cali_en_v_force : 1;
        unsigned int cali_en_v : 1;
    } bits;
    unsigned int u32;
}HI6551_CLJ_DEBUG_T;
typedef union
{
    struct
    {
        unsigned int state_test : 8;
    } bits;
    unsigned int u32;
}HI6551_STATE_TEST_T;
typedef union
{
    struct
    {
        unsigned int reg_data_clr : 1;
        unsigned int clj_rw_inf1 : 7;
    } bits;
    unsigned int u32;
}HI6551_CLJ_RESERVED1_T;
typedef union
{
    struct
    {
        unsigned int clj_rw_inf2 : 8;
    } bits;
    unsigned int u32;
}HI6551_CLJ_RESERVED2_T;
typedef union
{
    struct
    {
        unsigned int clj_rw_inf3 : 8;
    } bits;
    unsigned int u32;
}HI6551_CLJ_RESERVED3_T;
typedef union
{
    struct
    {
        unsigned int clj_rw_inf4 : 8;
    } bits;
    unsigned int u32;
}HI6551_CLJ_RESERVED4_T;
typedef union
{
    struct
    {
        unsigned int i_reserve_1 : 8;
    } bits;
    unsigned int u32;
}HI6551_CLJ_RESERVED5_T;
typedef union
{
    struct
    {
        unsigned int i_reserve_2 : 8;
    } bits;
    unsigned int u32;
}HI6551_CLJ_RESERVED6_T;
typedef union
{
    struct
    {
        unsigned int v_reserve_1 : 8;
    } bits;
    unsigned int u32;
}HI6551_CLJ_RESERVED7_T;
typedef union
{
    struct
    {
        unsigned int v_reserve_2 : 8;
    } bits;
    unsigned int u32;
}HI6551_CLJ_RESERVED8_T;
HI_SET_GET(hi_hi6551_status1_otmp_d1r,otmp_d1r,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_otmp150_d1r,otmp150_d1r,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_osc_state,osc_state,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_vsys_uv_d2f,vsys_uv_d2f,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_vsys_6p0_d200ur,vsys_6p0_d200ur,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_pwron_d20r,pwron_d20r,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status1_reserved,reserved,HI6551_STATUS1_T,HI6551_BASE_ADDR, HI6551_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_a,alarm_on_a,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_b,alarm_on_b,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_c,alarm_on_c,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_d,alarm_on_d,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_alarm_on_e,alarm_on_e,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_vbus_det_0p9_d3r,vbus_det_0p9_d3r,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_status2_reserved,reserved,HI6551_STATUS2_T,HI6551_BASE_ADDR, HI6551_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_irq1_otmp_d1r,otmp_d1r,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_vsys_2p5_f,vsys_2p5_f,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_vsys_uv_d2f,vsys_uv_d2f,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_vsys_6p0_d200ur,vsys_6p0_d200ur,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_pwron_d4sr,pwron_d4sr,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_pwron_d20f,pwron_d20f,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_pwron_d20r,pwron_d20r,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq1_reserved,reserved,HI6551_IRQ1_T,HI6551_BASE_ADDR, HI6551_IRQ1_OFFSET)
HI_SET_GET(hi_hi6551_irq2_ocp_scp_r,ocp_scp_r,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq2_vbus_det_1p375_d90ur,vbus_det_1p375_d90ur,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq2_vbus_det_0p9_d3f,vbus_det_0p9_d3f,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq2_vbus_det_0p9_d3r,vbus_det_0p9_d3r,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq2_reserved,reserved,HI6551_IRQ2_T,HI6551_BASE_ADDR, HI6551_IRQ2_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_a,alarm_on_a,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_b,alarm_on_b,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_c,alarm_on_c,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_d,alarm_on_d,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_e,alarm_on_e,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_alarm_on_f,alarm_on_f,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq3_reserved,reserved,HI6551_IRQ3_T,HI6551_BASE_ADDR, HI6551_IRQ3_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim0_hpd_out_f,sim0_hpd_out_f,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim0_hpd_out_r,sim0_hpd_out_r,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim0_hpd_in_f,sim0_hpd_in_f,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim0_hpd_in_r,sim0_hpd_in_r,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim1_hpd_out_f,sim1_hpd_out_f,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim1_hpd_out_r,sim1_hpd_out_r,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim1_hpd_in_f,sim1_hpd_in_f,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_irq4_sim1_hpd_in_r,sim1_hpd_in_r,HI6551_IRQ4_T,HI6551_BASE_ADDR, HI6551_IRQ4_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_cl_int_i,cl_int_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_cl_out_i,cl_out_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_cl_in_i,cl_in_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_chg_timer_i,chg_timer_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_load_timer_i,load_timer_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_vbat_int_i,vbat_int_i,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_reserved,reserved,HI6551_COUL_IRQ_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_otmp_d1r_mk,otmp_d1r_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_vsys_2p5_f_mk,vsys_2p5_f_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_vsys_uv_d2f_mk,vsys_uv_d2f_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_vsys_6p0_d200ur_mk,vsys_6p0_d200ur_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_pwron_d4sr_mk,pwron_d4sr_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_pwron_d20f_mk,pwron_d20f_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_pwron_d20r_mk,pwron_d20r_mk,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq1_mask_reserved,reserved,HI6551_IRQ1_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ1_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_ocp_scp_r_mk,ocp_scp_r_mk,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_vbus_det_1p375_mk,vbus_det_1p375_mk,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_vbus_det_0p9_d3f_mk,vbus_det_0p9_d3f_mk,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_vbus_det_0p9_d3r_mk,vbus_det_0p9_d3r_mk,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq2_mask_reserved,reserved,HI6551_IRQ2_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ2_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_a_mk,alarm_on_a_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_b_mk,alarm_on_b_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_c_mk,alarm_on_c_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_d_mk,alarm_on_d_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_e_mk,alarm_on_e_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_alarm_on_f_mk,alarm_on_f_mk,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq3_mask_reserved,reserved,HI6551_IRQ3_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ3_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim0_hpd_out_f_mk,sim0_hpd_out_f_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim0_hpd_out_r_mk,sim0_hpd_out_r_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim0_hpd_in_f_mk,sim0_hpd_in_f_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim0_hpd_in_r_mk,sim0_hpd_in_r_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim1_hpd_out_f_mk,sim1_hpd_out_f_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim1_hpd_out_r_mk,sim1_hpd_out_r_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim1_hpd_in_f_mk,sim1_hpd_in_f_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_irq4_mask_sim1_in_hpd_r_mk,sim1_in_hpd_r_mk,HI6551_IRQ4_MASK_T,HI6551_BASE_ADDR, HI6551_IRQ4_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_cl_int_i_mk,cl_int_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_cl_out_i_mk,cl_out_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_cl_in_i_mk,cl_in_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_chg_timer_i_mk,chg_timer_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_load_timer_i_mk,load_timer_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_vbat_int_i_mk,vbat_int_i_mk,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_coul_irq_mask_reserved,reserved,HI6551_COUL_IRQ_MASK_T,HI6551_BASE_ADDR, HI6551_COUL_IRQ_MASK_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck0_1,scp_buck0_1,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck2,scp_buck2,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck3,scp_buck3,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck4,scp_buck4,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck5,scp_buck5,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_scp_buck6,scp_buck6,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_scp_record1_reserved,reserved,HI6551_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck0_1,ocp_buck0_1,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck2,ocp_buck2,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck3,ocp_buck3,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck4,ocp_buck4,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck5,ocp_buck5,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_ocp_buck6,ocp_buck6,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record1_reserved,reserved,HI6551_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo1,ocp_ldo1,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo2,ocp_ldo2,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo3,ocp_ldo3,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo4,ocp_ldo4,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo5,ocp_ldo5,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo6,ocp_ldo6,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo7,ocp_ldo7,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record2_ocp_ldo8,ocp_ldo8,HI6551_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo9,ocp_ldo9,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo10,ocp_ldo10,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo11,ocp_ldo11,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo12,ocp_ldo12,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo13,ocp_ldo13,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo14,ocp_ldo14,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo15,ocp_ldo15,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record3_ocp_ldo16,ocp_ldo16,HI6551_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo17,ocp_ldo17,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo18,ocp_ldo18,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo19,ocp_ldo19,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo20,ocp_ldo20,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo21,ocp_ldo21,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo22,ocp_ldo22,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo23,ocp_ldo23,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record4_ocp_ldo24,ocp_ldo24,HI6551_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs2,ocp_lvs2,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs3,ocp_lvs3,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs4,ocp_lvs4,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs5,ocp_lvs5,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs7,ocp_lvs7,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs6,ocp_lvs6,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_ocp_lvs8,ocp_lvs8,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record5_reserved,reserved,HI6551_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record6_ocp_lvs9,ocp_lvs9,HI6551_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record6_ocp_lvs10,ocp_lvs10,HI6551_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record6_reserved,reserved,HI6551_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_ocp_boost,ocp_boost,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_scp_boost,scp_boost,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_ovp_boost,ovp_boost,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_uvp_boost,uvp_boost,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_ocp_classd,ocp_classd,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_record7_reserved,reserved,HI6551_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_otmp_d1r,np_otmp_d1r,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_hreset_n_f,np_hreset_n_f,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_vsys_2p5_f,np_vsys_2p5_f,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_vsys_uv_d2f,np_vsys_uv_d2f,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_vsys_6p0_d200ur,np_vsys_6p0_d200ur,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_pwron_d4sr,np_pwron_d4sr,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_pwron_d20f,np_pwron_d20f,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq1_record_np_pwron_d20r,np_pwron_d20r,HI6551_NP_IRQ1_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ1_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_vbus_det_0p9_d150r,np_vbus_det_0p9_d150r,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_vbus_det_1p375,np_vbus_det_1p375,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_vbus_det_0p9_d3f,np_vbus_det_0p9_d3f,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_vbus_det_0p9_d3r,np_vbus_det_0p9_d3r,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_pwron_restart,np_pwron_restart,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_pwron_dnsr,np_pwron_dnsr,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_pwron_d500r,np_pwron_d500r,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq2_record_np_otmp150_d1r,np_otmp150_d1r,HI6551_NP_IRQ2_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ2_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_a,np_alarm_on_a,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_b,np_alarm_on_b,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_c,np_alarm_on_c,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_d,np_alarm_on_d,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_e,np_alarm_on_e,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_np_alarm_on_f,np_alarm_on_f,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_irq3_record_reserved,reserved,HI6551_NP_IRQ3_RECORD_T,HI6551_BASE_ADDR, HI6551_NP_IRQ3_RECORD_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck0_1,np_scp_buck0_1,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck2,np_scp_buck2,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck3,np_scp_buck3,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck4,np_scp_buck4,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck5,np_scp_buck5,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_np_scp_buck6,np_scp_buck6,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_scp_record1_reserved,reserved,HI6551_NP_SCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_SCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck0,np_ocp_buck0,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck1,np_ocp_buck1,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck0_1,np_ocp_buck0_1,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck2,np_ocp_buck2,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck3,np_ocp_buck3,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck4,np_ocp_buck4,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck5,np_ocp_buck5,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record1_np_ocp_buck6,np_ocp_buck6,HI6551_NP_OCP_RECORD1_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD1_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo1,np_ocp_ldo1,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo2,np_ocp_ldo2,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo3,np_ocp_ldo3,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo4,np_ocp_ldo4,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo5,np_ocp_ldo5,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo6,np_ocp_ldo6,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo7,np_ocp_ldo7,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record2_np_ocp_ldo8,np_ocp_ldo8,HI6551_NP_OCP_RECORD2_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD2_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo9,np_ocp_ldo9,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo10,np_ocp_ldo10,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo11,np_ocp_ldo11,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo12,np_ocp_ldo12,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo13,np_ocp_ldo13,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo14,np_ocp_ldo14,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo15,np_ocp_ldo15,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record3_np_ocp_ldo16,np_ocp_ldo16,HI6551_NP_OCP_RECORD3_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD3_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo17,np_ocp_ldo17,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo18,np_ocp_ldo18,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo19,np_ocp_ldo19,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo20,np_ocp_ldo20,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo21,np_ocp_ldo21,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo22,np_ocp_ldo22,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo23,np_ocp_ldo23,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record4_np_ocp_ldo24,np_ocp_ldo24,HI6551_NP_OCP_RECORD4_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD4_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs2,np_ocp_lvs2,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs3,np_ocp_lvs3,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs4,np_ocp_lvs4,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs5,np_ocp_lvs5,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs7,np_ocp_lvs7,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs6,np_ocp_lvs6,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_np_ocp_lvs8,np_ocp_lvs8,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record5_reserved,reserved,HI6551_NP_OCP_RECORD5_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD5_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record6_np_ocp_lvs9,np_ocp_lvs9,HI6551_NP_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record6_np_ocp_lvs10,np_ocp_lvs10,HI6551_NP_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record6_reserved,reserved,HI6551_NP_OCP_RECORD6_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD6_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_ocp_boost,np_ocp_boost,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_scp_boost,np_scp_boost,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_ovp_boost,np_ovp_boost,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_uvp_boost,np_uvp_boost,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_np_ocp_classd,np_ocp_classd,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_np_ocp_record7_reserved,reserved,HI6551_NP_OCP_RECORD7_T,HI6551_BASE_ADDR, HI6551_NP_OCP_RECORD7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_ocp_ldo_deb_sel,ocp_ldo_deb_sel,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_en_ldo_ocp_deb,en_ldo_ocp_deb,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_ocp_buck_deb_sel,ocp_buck_deb_sel,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_en_buck_ocp_deb,en_buck_ocp_deb,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_en_buck_scp_deb,en_buck_scp_deb,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_ocp_deb_en_bst_ocp_deb,en_bst_ocp_deb,HI6551_OCP_DEB_T,HI6551_BASE_ADDR, HI6551_OCP_DEB_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_vbus_det_0p9_ctrl,vbus_det_0p9_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_vsys_2p5_ctrl,vsys_2p5_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_vsys_uv_ctrl,vsys_uv_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_vsys_6p0_ctrl,vsys_6p0_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_otmp150_ctrl,otmp150_ctrl,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_en_32kc,en_32kc,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_en_32kb,en_32kb,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_onoff8_en_32ka,en_32ka,HI6551_ONOFF8_T,HI6551_BASE_ADDR, HI6551_ONOFF8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_ctrl_buck0_1,ocp_scp_ctrl_buck0_1,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_off_buck0_1,ocp_scp_off_buck0_1,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_ctrl_buck2,ocp_scp_ctrl_buck2,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_off_buck2,ocp_scp_off_buck2,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_ctrl_buck3,ocp_scp_ctrl_buck3,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_off_buck3,ocp_scp_off_buck3,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_ctrl_buck4,ocp_scp_ctrl_buck4,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl1_ocp_scp_off_buck4,ocp_scp_off_buck4,HI6551_OCP_SCP_MOD_CTRL1_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_ocp_scp_ctrl_buck5,ocp_scp_ctrl_buck5,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_ocp_scp_off_buck5,ocp_scp_off_buck5,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_ocp_scp_ctrl_buck6,ocp_scp_ctrl_buck6,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_ocp_scp_off_buck6,ocp_scp_off_buck6,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_scp_mod_ctrl2_reserved,reserved,HI6551_OCP_SCP_MOD_CTRL2_T,HI6551_BASE_ADDR, HI6551_OCP_SCP_MOD_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_ctrl_ldo1,ocp_ctrl_ldo1,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_off_ldo1,ocp_off_ldo1,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_ctrl_ldo2,ocp_ctrl_ldo2,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_off_ldo2,ocp_off_ldo2,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_ctrl_ldo3,ocp_ctrl_ldo3,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_off_ldo3,ocp_off_ldo3,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_ctrl_ldo4,ocp_ctrl_ldo4,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl3_ocp_off_ldo4,ocp_off_ldo4,HI6551_OCP_MOD_CTRL3_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL3_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_ctrl_ldo5,ocp_ctrl_ldo5,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_off_ldo5,ocp_off_ldo5,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_ctrl_ldo6,ocp_ctrl_ldo6,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_off_ldo6,ocp_off_ldo6,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_ctrl_ldo7,ocp_ctrl_ldo7,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_off_ldo7,ocp_off_ldo7,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_ctrl_ldo8,ocp_ctrl_ldo8,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl4_ocp_off_ldo8,ocp_off_ldo8,HI6551_OCP_MOD_CTRL4_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL4_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_ctrl_ldo9,ocp_ctrl_ldo9,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_off_ldo9,ocp_off_ldo9,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_ctrl_ldo10,ocp_ctrl_ldo10,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_off_ldo10,ocp_off_ldo10,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_ctrl_ldo11,ocp_ctrl_ldo11,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_off_ldo11,ocp_off_ldo11,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_ctrl_ldo12,ocp_ctrl_ldo12,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl5_ocp_off_ldo12,ocp_off_ldo12,HI6551_OCP_MOD_CTRL5_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL5_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_ctrl_ldo13,ocp_ctrl_ldo13,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_off_ldo13,ocp_off_ldo13,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_ctrl_ldo14,ocp_ctrl_ldo14,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_off_ldo14,ocp_off_ldo14,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_ctrl_ldo15,ocp_ctrl_ldo15,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_off_ldo15,ocp_off_ldo15,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_ctrl_ldo16,ocp_ctrl_ldo16,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl6_ocp_off_ldo16,ocp_off_ldo16,HI6551_OCP_MOD_CTRL6_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL6_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_ctrl_ldo17,ocp_ctrl_ldo17,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_off_ldo17,ocp_off_ldo17,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_ctrl_ldo18,ocp_ctrl_ldo18,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_off_ldo18,ocp_off_ldo18,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_ctrl_ldo19,ocp_ctrl_ldo19,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_off_ldo19,ocp_off_ldo19,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_ctrl_ldo20,ocp_ctrl_ldo20,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl7_ocp_off_ldo20,ocp_off_ldo20,HI6551_OCP_MOD_CTRL7_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL7_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_ctrl_ldo21,ocp_ctrl_ldo21,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_off_ldo21,ocp_off_ldo21,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_ctrl_ldo22,ocp_ctrl_ldo22,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_off_ldo22,ocp_off_ldo22,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_ctrl_ldo23,ocp_ctrl_ldo23,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_off_ldo23,ocp_off_ldo23,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_ctrl_ldo24,ocp_ctrl_ldo24,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl8_ocp_off_ldo24,ocp_off_ldo24,HI6551_OCP_MOD_CTRL8_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL8_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_ctrl_lvs2,ocp_ctrl_lvs2,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_off_lvs2,ocp_off_lvs2,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_ctrl_lvs3,ocp_ctrl_lvs3,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_off_lvs3,ocp_off_lvs3,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_ctrl_lvs4,ocp_ctrl_lvs4,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_off_lvs4,ocp_off_lvs4,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_ctrl_lvs5,ocp_ctrl_lvs5,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl9_ocp_off_lvs5,ocp_off_lvs5,HI6551_OCP_MOD_CTRL9_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL9_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_ctrl_lvs7,ocp_ctrl_lvs7,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_off_lvs7,ocp_off_lvs7,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_ctrl_lvs6,ocp_ctrl_lvs6,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_off_lvs6,ocp_off_lvs6,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_ctrl_lvs8,ocp_ctrl_lvs8,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_off_lvs8,ocp_off_lvs8,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_ctrl_lvs9,ocp_ctrl_lvs9,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl10_ocp_off_lvs9,ocp_off_lvs9,HI6551_OCP_MOD_CTRL10_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL10_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_ctrl_lvs10,ocp_ctrl_lvs10,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_off_lvs10,ocp_off_lvs10,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_ctrl_bst,ocp_ctrl_bst,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_off_bst,ocp_off_bst,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_ctrl_classd,ocp_ctrl_classd,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_ocp_off_classd,ocp_off_classd,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_ocp_mod_ctrl11_reserved,reserved,HI6551_OCP_MOD_CTRL11_T,HI6551_BASE_ADDR, HI6551_OCP_MOD_CTRL11_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck0_int,en_buck0_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck1_int,en_buck1_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck2_int,en_buck2_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck3_int,en_buck3_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck4_int,en_buck4_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck5_int,en_buck5_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_en_buck6_int,en_buck6_int,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_enable1_reserved,reserved,HI6551_ENABLE1_T,HI6551_BASE_ADDR, HI6551_ENABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck0_int,dis_buck0_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck1_int,dis_buck1_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck2_int,dis_buck2_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck3_int,dis_buck3_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck4_int,dis_buck4_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck5_int,dis_buck5_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_dis_buck6_int,dis_buck6_int,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_disable1_reserved,reserved,HI6551_DISABLE1_T,HI6551_BASE_ADDR, HI6551_DISABLE1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck0_int,st_buck0_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck1_int,st_buck1_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck2_int,st_buck2_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck3_int,st_buck3_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck4_int,st_buck4_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck5_int,st_buck5_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_st_buck6_int,st_buck6_int,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status1_reserved,reserved,HI6551_ONOFF_STATUS1_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS1_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo1_int,en_ldo1_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo2_int,en_ldo2_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo3_buck_int,en_ldo3_buck_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo4_int,en_ldo4_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo5_int,en_ldo5_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo6_int,en_ldo6_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo7_int,en_ldo7_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_enable2_en_ldo8_int,en_ldo8_int,HI6551_ENABLE2_T,HI6551_BASE_ADDR, HI6551_ENABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo1_int,dis_ldo1_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo2_int,dis_ldo2_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo3_buck_int,dis_ldo3_buck_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo4_int,dis_ldo4_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo5_int,dis_ldo5_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo6_int,dis_ldo6_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo7_int,dis_ldo7_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_disable2_dis_ldo8_int,dis_ldo8_int,HI6551_DISABLE2_T,HI6551_BASE_ADDR, HI6551_DISABLE2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo1_int,st_ldo1_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo2_int,st_ldo2_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo3_buck_int,st_ldo3_buck_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo4_int,st_ldo4_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo5_int,st_ldo5_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo6_int,st_ldo6_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo7_int,st_ldo7_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status2_st_ldo8_int,st_ldo8_int,HI6551_ONOFF_STATUS2_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS2_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo10_int,en_ldo10_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo12_int,en_ldo12_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo13_int,en_ldo13_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo14_int,en_ldo14_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo15_int,en_ldo15_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo16_int,en_ldo16_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo17_int,en_ldo17_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_enable3_en_ldo18_int,en_ldo18_int,HI6551_ENABLE3_T,HI6551_BASE_ADDR, HI6551_ENABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo10_int,dis_ldo10_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo12_int,dis_ldo12_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo13_int,dis_ldo13_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo14_int,dis_ldo14_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo15_int,dis_ldo15_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo16_int,dis_ldo16_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo17_int,dis_ldo17_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_disable3_dis_ldo18_int,dis_ldo18_int,HI6551_DISABLE3_T,HI6551_BASE_ADDR, HI6551_DISABLE3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo10_int,st_ldo10_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo12_int,st_ldo12_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo13_int,st_ldo13_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo14_int,st_ldo14_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo15_int,st_ldo15_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo16_int,st_ldo16_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo17_int,st_ldo17_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status3_st_ldo18_int,st_ldo18_int,HI6551_ONOFF_STATUS3_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS3_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo19_int,en_ldo19_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo20_int,en_ldo20_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo21_int,en_ldo21_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo22_int,en_ldo22_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo23_int,en_ldo23_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo24_int,en_ldo24_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_en_ldo3_batt_int,en_ldo3_batt_int,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_enable4_reserved,reserved,HI6551_ENABLE4_T,HI6551_BASE_ADDR, HI6551_ENABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo19_int,dis_ldo19_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo20_int,dis_ldo20_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo21_int,dis_ldo21_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo22_int,dis_ldo22_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo23_int,dis_ldo23_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo24_int,dis_ldo24_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_dis_ldo3_batt_int,dis_ldo3_batt_int,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_disable4_reserved,reserved,HI6551_DISABLE4_T,HI6551_BASE_ADDR, HI6551_DISABLE4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo19_int,st_ldo19_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo20_int,st_ldo20_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo21_int,st_ldo21_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo22_int,st_ldo22_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo23_int,st_ldo23_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo24_int,st_ldo24_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_st_ldo3_batt_int,st_ldo3_batt_int,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status4_reserved,reserved,HI6551_ONOFF_STATUS4_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS4_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs2_int,en_lvs2_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs3_int,en_lvs3_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs4_int,en_lvs4_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs5_int,en_lvs5_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs7_int,en_lvs7_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs6_int,en_lvs6_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs8_int,en_lvs8_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_enable5_en_lvs9_int,en_lvs9_int,HI6551_ENABLE5_T,HI6551_BASE_ADDR, HI6551_ENABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs2_int,dis_lvs2_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs3_int,dis_lvs3_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs4_int,dis_lvs4_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs5_int,dis_lvs5_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs7_int,dis_lvs7_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs6_int,dis_lvs6_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs8_int,dis_lvs8_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_disable5_dis_lvs9_int,dis_lvs9_int,HI6551_DISABLE5_T,HI6551_BASE_ADDR, HI6551_DISABLE5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs2_int,st_lvs2_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs3_int,st_lvs3_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs4_int,st_lvs4_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs5_int,st_lvs5_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs7_int,st_lvs7_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs6_int,st_lvs6_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs8_int,st_lvs8_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status5_st_lvs9_int,st_lvs9_int,HI6551_ONOFF_STATUS5_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS5_OFFSET)
HI_SET_GET(hi_hi6551_enable6_en_lvs10_int,en_lvs10_int,HI6551_ENABLE6_T,HI6551_BASE_ADDR, HI6551_ENABLE6_OFFSET)
HI_SET_GET(hi_hi6551_enable6_reserved,reserved,HI6551_ENABLE6_T,HI6551_BASE_ADDR, HI6551_ENABLE6_OFFSET)
HI_SET_GET(hi_hi6551_disable6_dis_lvs10_int,dis_lvs10_int,HI6551_DISABLE6_T,HI6551_BASE_ADDR, HI6551_DISABLE6_OFFSET)
HI_SET_GET(hi_hi6551_disable6_reserved,reserved,HI6551_DISABLE6_T,HI6551_BASE_ADDR, HI6551_DISABLE6_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status6_st_lvs10_int,st_lvs10_int,HI6551_ONOFF_STATUS6_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS6_OFFSET)
HI_SET_GET(hi_hi6551_onoff_status6_reserved,reserved,HI6551_ONOFF_STATUS6_T,HI6551_BASE_ADDR, HI6551_ONOFF_STATUS6_OFFSET)
HI_SET_GET(hi_hi6551_enable7_en_cp2_int,en_cp2_int,HI6551_ENABLE7_T,HI6551_BASE_ADDR, HI6551_ENABLE7_OFFSET)
HI_SET_GET(hi_hi6551_enable7_cp2_always_on_int,cp2_always_on_int,HI6551_ENABLE7_T,HI6551_BASE_ADDR, HI6551_ENABLE7_OFFSET)
HI_SET_GET(hi_hi6551_enable7_reserved,reserved,HI6551_ENABLE7_T,HI6551_BASE_ADDR, HI6551_ENABLE7_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_en_ldo9_int,en_ldo9_int,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_sim0_en_int,sim0_en_int,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_en_ldo11_int,en_ldo11_int,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_sim1_en_int,sim1_en_int,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_simcard_en_reserved,reserved,HI6551_SIMCARD_EN_T,HI6551_BASE_ADDR, HI6551_SIMCARD_EN_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_simcard0_resv,simcard0_resv,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_simcard0_bbrp,simcard0_bbrp,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_simcard0_simrp,simcard0_simrp,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_simcard0_200ns_en,simcard0_200ns_en,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim0_cfg_reserved,reserved,HI6551_SIM0_CFG_T,HI6551_BASE_ADDR, HI6551_SIM0_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_simcard1_resv,simcard1_resv,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_simcard1_bbrp,simcard1_bbrp,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_simcard1_simrp,simcard1_simrp,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_simcard1_200ns_en,simcard1_200ns_en,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim1_cfg_reserved,reserved,HI6551_SIM1_CFG_T,HI6551_BASE_ADDR, HI6551_SIM1_CFG_OFFSET)
HI_SET_GET(hi_hi6551_sim_deb_simcard_deb_sel,simcard_deb_sel,HI6551_SIM_DEB_T,HI6551_BASE_ADDR, HI6551_SIM_DEB_OFFSET)
HI_SET_GET(hi_hi6551_sim_deb_reserved,reserved,HI6551_SIM_DEB_T,HI6551_BASE_ADDR, HI6551_SIM_DEB_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_en_eco_buck3_int,en_eco_buck3_int,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_en_eco_buck4_int,en_eco_buck4_int,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_en_eco_buck5_int,en_eco_buck5_int,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_en_eco_buck6_int,en_eco_buck6_int,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg1_reserved,reserved,HI6551_ECO_MOD_CFG1_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG1_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo3_int,en_eco_ldo3_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo7_int,en_eco_ldo7_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo9_int,en_eco_ldo9_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo10_int,en_eco_ldo10_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo11_int,en_eco_ldo11_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo12_int,en_eco_ldo12_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo22_int,en_eco_ldo22_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg2_en_eco_ldo24_int,en_eco_ldo24_int,HI6551_ECO_MOD_CFG2_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG2_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_force_eco_buck3_int,force_eco_buck3_int,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_force_eco_buck4_int,force_eco_buck4_int,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_force_eco_buck5_int,force_eco_buck5_int,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_force_eco_buck6_int,force_eco_buck6_int,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg3_reserved,reserved,HI6551_ECO_MOD_CFG3_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG3_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo3_int,force_eco_ldo3_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo7_int,force_eco_ldo7_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo9_int,force_eco_ldo9_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo10_int,force_eco_ldo10_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo11_int,force_eco_ldo11_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo12_int,force_eco_ldo12_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo22_int,force_eco_ldo22_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_eco_mod_cfg4_force_eco_ldo24_int,force_eco_ldo24_int,HI6551_ECO_MOD_CFG4_T,HI6551_BASE_ADDR, HI6551_ECO_MOD_CFG4_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_eco_pwrsel,eco_pwrsel,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_peri_en_ctrl_ldo12,peri_en_ctrl_ldo12,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_peri_en_ctrl_lvs9,peri_en_ctrl_lvs9,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_peri_en_ctrl_ldo8,peri_en_ctrl_ldo8,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_peri_en_ctrl_buck3,peri_en_ctrl_buck3,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_enb3_eco_mark_reserved,reserved,HI6551_ENB3_ECO_MARK_T,HI6551_BASE_ADDR, HI6551_ENB3_ECO_MARK_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg1_adj_buck01_osc_d,buck01_osc_d,HI6551_BUCK01_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg1_adj_buck0_pfm_vth_sel,buck0_pfm_vth_sel,HI6551_BUCK01_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg1_adj_buck0_sc_sel,buck0_sc_sel,HI6551_BUCK01_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg1_adj_reserved,reserved,HI6551_BUCK01_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck01_mod_sel,buck01_mod_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck0_bt_sel,buck0_bt_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck0_pd_sel,buck0_pd_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck0_burst_drv_ctr,buck0_burst_drv_ctr,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck01_ocp_mod_sel,buck01_ocp_mod_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck01_ocp_clamp_sel,buck01_ocp_clamp_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg2_adj_buck01_ocp_shied_sel,buck01_ocp_shied_sel,HI6551_BUCK01_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg3_adj_buck0_vc_sel,buck0_vc_sel,HI6551_BUCK01_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg3_adj_reserved_1,reserved_1,HI6551_BUCK01_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg3_adj_buck01_auto_pfm_ctr,buck01_auto_pfm_ctr,HI6551_BUCK01_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg3_adj_reserved_0,reserved_0,HI6551_BUCK01_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg4_adj_buck0_isc_sel,buck0_isc_sel,HI6551_BUCK01_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg4_adj_reserved_1,reserved_1,HI6551_BUCK01_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg4_adj_buck0_ipk_sel,buck0_ipk_sel,HI6551_BUCK01_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg4_adj_reserved_0,reserved_0,HI6551_BUCK01_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_buck01_dt_sel,buck01_dt_sel,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_buck01_pg_dt_sel,buck01_pg_dt_sel,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_buck01_ng_dt_sel,buck01_ng_dt_sel,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_buck01_sft_sel,buck01_sft_sel,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg5_adj_reserved,reserved,HI6551_BUCK01_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg6_adj_buck01_pg_p_sel,buck01_pg_p_sel,HI6551_BUCK01_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg6_adj_reserved_1,reserved_1,HI6551_BUCK01_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg6_adj_buck01_pg_n_sel,buck01_pg_n_sel,HI6551_BUCK01_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg6_adj_reserved_0,reserved_0,HI6551_BUCK01_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg7_adj_buck01_ng_p_sel,buck01_ng_p_sel,HI6551_BUCK01_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg7_adj_reserved_1,reserved_1,HI6551_BUCK01_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg7_adj_buck01_ng_n_sel,buck01_ng_n_sel,HI6551_BUCK01_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg7_adj_reserved_0,reserved_0,HI6551_BUCK01_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg8_adj_buck0_ccm_sel,buck0_ccm_sel,HI6551_BUCK01_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg8_adj_buck1_ccm_sel,buck1_ccm_sel,HI6551_BUCK01_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg8_adj_buck0_ccc_sel,buck0_ccc_sel,HI6551_BUCK01_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg8_adj_buck0_cs_sel,buck0_cs_sel,HI6551_BUCK01_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_buck0_dmd_sel,buck0_dmd_sel,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_buck01_ton_off,buck01_ton_off,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_buck01_pfm_sleep,buck01_pfm_sleep,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_buck01_ton_on,buck01_ton_on,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg9_adj_reserved,reserved,HI6551_BUCK01_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg10_adj_buck01_new_dmd_sel,buck01_new_dmd_sel,HI6551_BUCK01_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg10_adj_reserved,reserved,HI6551_BUCK01_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck0_ocp_sel,buck0_ocp_sel,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck01_ocp_en,buck01_ocp_en,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck01_dmd_en,buck01_dmd_en,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck01_ea_sel,buck01_ea_sel,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg11_adj_buck01_clk_sel,buck01_clk_sel,HI6551_BUCK01_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg12_adj_buck0_sleep_depth_adj,buck0_sleep_depth_adj,HI6551_BUCK01_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg12_adj_reserved_1,reserved_1,HI6551_BUCK01_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg12_adj_buck0_ea_comp_cap,buck0_ea_comp_cap,HI6551_BUCK01_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg12_adj_reserved_0,reserved_0,HI6551_BUCK01_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_slope_gen,buck01_slope_gen,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_pdn_lx_det,buck01_pdn_lx_det,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_sleep_dmd,buck01_sleep_dmd,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_dmd_shield_n,buck01_dmd_shield_n,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_ocp_delay_sel,buck01_ocp_delay_sel,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg13_adj_buck01_dmd_clamp,buck01_dmd_clamp,HI6551_BUCK01_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg14_adj_buck01_slope_dc,buck01_slope_dc,HI6551_BUCK01_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg14_adj_buck01_unsleep,buck01_unsleep,HI6551_BUCK01_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg14_adj_buck01_dmd_float,buck01_dmd_float,HI6551_BUCK01_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg14_adj_reserved,reserved,HI6551_BUCK01_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg15_adj_buck0_comp_adj1,buck0_comp_adj1,HI6551_BUCK01_REG15_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG15_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg16_adj_buck01_reserved1,buck01_reserved1,HI6551_BUCK01_REG16_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG16_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck01_reg17_adj_buck01_reserved0,buck01_reserved0,HI6551_BUCK01_REG17_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK01_REG17_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg1_adj_buck2_adj_rlx,buck2_adj_rlx,HI6551_BUCK2_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg1_adj_buck2_adj_clx,buck2_adj_clx,HI6551_BUCK2_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg2_adj_buck2_new_dmd_sel,buck2_new_dmd_sel,HI6551_BUCK2_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg2_adj_reserved,reserved,HI6551_BUCK2_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_shield_i,buck2_shield_i,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_en_regop_clamp,buck2_en_regop_clamp,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_dmd_clamp,buck2_dmd_clamp,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_ocp_delay_sel,buck2_ocp_delay_sel,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_dmd_shield_n,buck2_dmd_shield_n,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_sleep_dmd,buck2_sleep_dmd,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg3_adj_buck2_pdn_lx_det,buck2_pdn_lx_det,HI6551_BUCK2_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg4_adj_buck2_ocp_sel,buck2_ocp_sel,HI6551_BUCK2_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg4_adj_reserved_1,reserved_1,HI6551_BUCK2_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg4_adj_buck2_dmd_sel,buck2_dmd_sel,HI6551_BUCK2_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg4_adj_reserved_0,reserved_0,HI6551_BUCK2_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_buck2_ng_dt_sel,buck2_ng_dt_sel,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_buck2_pg_dt_sel,buck2_pg_dt_sel,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_buck2_sft_sel,buck2_sft_sel,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_buck2_sleep,buck2_sleep,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg5_adj_reserved,reserved,HI6551_BUCK2_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg6_adj_buck2_pg_n_sel,buck2_pg_n_sel,HI6551_BUCK2_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg6_adj_reserved_1,reserved_1,HI6551_BUCK2_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg6_adj_buck2_pg_p_sel,buck2_pg_p_sel,HI6551_BUCK2_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg6_adj_reserved_0,reserved_0,HI6551_BUCK2_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg7_adj_buck2_ng_n_sel,buck2_ng_n_sel,HI6551_BUCK2_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg7_adj_reserved_1,reserved_1,HI6551_BUCK2_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg7_adj_buck2_ng_p_sel,buck2_ng_p_sel,HI6551_BUCK2_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg7_adj_reserved_0,reserved_0,HI6551_BUCK2_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_buck2_dbias,buck2_dbias,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_buck2_ocp_d,buck2_ocp_d,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_reserved_1,reserved_1,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_buck2_ton,buck2_ton,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg8_adj_reserved_0,reserved_0,HI6551_BUCK2_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_nmos_off,buck2_nmos_off,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_reg_c,buck2_reg_c,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_short_pdp,buck2_short_pdp,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_reg_ss_d,buck2_reg_ss_d,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_dt_sel,buck2_dt_sel,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_buck2_regop_c,buck2_regop_c,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg9_adj_reserved,reserved,HI6551_BUCK2_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg10_adj_buck2_reg_dr,buck2_reg_dr,HI6551_BUCK2_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg10_adj_buck2_en_reg,buck2_en_reg,HI6551_BUCK2_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg10_adj_buck2_ocp_clamp_sel,buck2_ocp_clamp_sel,HI6551_BUCK2_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg10_adj_reserved,reserved,HI6551_BUCK2_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg11_adj_buck2_reg_idr,buck2_reg_idr,HI6551_BUCK2_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg11_adj_reserved_1,reserved_1,HI6551_BUCK2_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg11_adj_buck2_reg_r,buck2_reg_r,HI6551_BUCK2_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg11_adj_reserved_0,reserved_0,HI6551_BUCK2_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck2_reg12_adj_buck2_reserve,buck2_reserve,HI6551_BUCK2_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK2_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg1_adj_buck3_adj_rlx,buck3_adj_rlx,HI6551_BUCK3_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg1_adj_buck3_adj_clx,buck3_adj_clx,HI6551_BUCK3_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg2_adj_buck3_new_dmd_sel,buck3_new_dmd_sel,HI6551_BUCK3_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg2_adj_buck3_ocp_sel,buck3_ocp_sel,HI6551_BUCK3_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg2_adj_reserved,reserved,HI6551_BUCK3_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_dmd_sel,buck3_dmd_sel,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_en_regop_clamp,buck3_en_regop_clamp,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_dmd_clamp,buck3_dmd_clamp,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_ocp_delay_sel,buck3_ocp_delay_sel,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_dmd_shield_n,buck3_dmd_shield_n,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_sleep_dmd,buck3_sleep_dmd,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg3_adj_buck3_pdn_lx_det,buck3_pdn_lx_det,HI6551_BUCK3_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_buck3_ng_dt_sel,buck3_ng_dt_sel,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_buck3_pg_dt_sel,buck3_pg_dt_sel,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_buck3_sft_sel,buck3_sft_sel,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_reserved_1,reserved_1,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_buck3_shield_i,buck3_shield_i,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg4_adj_reserved_0,reserved_0,HI6551_BUCK3_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg5_adj_buck3_pg_n_sel,buck3_pg_n_sel,HI6551_BUCK3_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg5_adj_reserved_1,reserved_1,HI6551_BUCK3_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg5_adj_buck3_pg_p_sel,buck3_pg_p_sel,HI6551_BUCK3_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg5_adj_reserved_0,reserved_0,HI6551_BUCK3_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg6_adj_buck3_ng_n_sel,buck3_ng_n_sel,HI6551_BUCK3_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg6_adj_reserved_1,reserved_1,HI6551_BUCK3_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg6_adj_buck3_ng_p_sel,buck3_ng_p_sel,HI6551_BUCK3_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg6_adj_reserved_0,reserved_0,HI6551_BUCK3_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_buck3_dbias,buck3_dbias,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_buck3_ocp_d,buck3_ocp_d,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_reserved_1,reserved_1,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_buck3_ton,buck3_ton,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg7_adj_reserved_0,reserved_0,HI6551_BUCK3_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_nmos_off,buck3_nmos_off,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_reg_c,buck3_reg_c,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_short_pdp,buck3_short_pdp,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_reg_ss_d,buck3_reg_ss_d,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_dt_sel,buck3_dt_sel,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_buck3_regop_c,buck3_regop_c,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg8_adj_reserved,reserved,HI6551_BUCK3_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg9_adj_buck3_reg_dr,buck3_reg_dr,HI6551_BUCK3_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg9_adj_buck3_en_reg,buck3_en_reg,HI6551_BUCK3_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg9_adj_buck3_ocp_clamp_sel,buck3_ocp_clamp_sel,HI6551_BUCK3_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg9_adj_reserved,reserved,HI6551_BUCK3_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg10_adj_buck3_reg_idr,buck3_reg_idr,HI6551_BUCK3_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg10_adj_reserved_1,reserved_1,HI6551_BUCK3_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg10_adj_buck3_reg_r,buck3_reg_r,HI6551_BUCK3_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg10_adj_reserved_0,reserved_0,HI6551_BUCK3_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg11_adj_buck3_mos_sel,buck3_mos_sel,HI6551_BUCK3_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg11_adj_reserved,reserved,HI6551_BUCK3_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck3_reg12_adj_buck3_reserve,buck3_reserve,HI6551_BUCK3_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK3_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg1_adj_buck4_adj_rlx,buck4_adj_rlx,HI6551_BUCK4_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg1_adj_buck4_adj_clx,buck4_adj_clx,HI6551_BUCK4_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg2_adj_buck4_new_dmd_sel,buck4_new_dmd_sel,HI6551_BUCK4_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg2_adj_buck4_ocp_sel,buck4_ocp_sel,HI6551_BUCK4_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg2_adj_reserved,reserved,HI6551_BUCK4_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_dmd_sel,buck4_dmd_sel,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_en_regop_clamp,buck4_en_regop_clamp,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_dmd_clamp,buck4_dmd_clamp,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_ocp_delay_sel,buck4_ocp_delay_sel,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_dmd_shield_n,buck4_dmd_shield_n,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_sleep_dmd,buck4_sleep_dmd,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg3_adj_buck4_pdn_lx_det,buck4_pdn_lx_det,HI6551_BUCK4_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg4_adj_buck4_ng_dt_sel,buck4_ng_dt_sel,HI6551_BUCK4_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg4_adj_buck4_pg_dt_sel,buck4_pg_dt_sel,HI6551_BUCK4_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg4_adj_buck4_sft_sel,buck4_sft_sel,HI6551_BUCK4_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg4_adj_reserved,reserved,HI6551_BUCK4_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg5_adj_buck4_pg_n_sel,buck4_pg_n_sel,HI6551_BUCK4_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg5_adj_reserved_1,reserved_1,HI6551_BUCK4_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg5_adj_buck4_pg_p_sel,buck4_pg_p_sel,HI6551_BUCK4_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg5_adj_reserved_0,reserved_0,HI6551_BUCK4_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg6_adj_buck4_ng_n_sel,buck4_ng_n_sel,HI6551_BUCK4_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg6_adj_reserved_1,reserved_1,HI6551_BUCK4_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg6_adj_buck4_ng_p_sel,buck4_ng_p_sel,HI6551_BUCK4_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg6_adj_reserved_0,reserved_0,HI6551_BUCK4_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_buck4_dbias,buck4_dbias,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_buck4_ocp_d,buck4_ocp_d,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_reserved_1,reserved_1,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_buck4_ton,buck4_ton,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg7_adj_reserved_0,reserved_0,HI6551_BUCK4_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_nmos_off,buck4_nmos_off,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_reg_c,buck4_reg_c,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_short_pdp,buck4_short_pdp,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_reg_ss_d,buck4_reg_ss_d,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_dt_sel,buck4_dt_sel,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_buck4_regop_c,buck4_regop_c,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg8_adj_reserved,reserved,HI6551_BUCK4_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg9_adj_buck4_reg_dr,buck4_reg_dr,HI6551_BUCK4_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg9_adj_buck4_en_reg,buck4_en_reg,HI6551_BUCK4_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg9_adj_buck4_ocp_clamp_sel,buck4_ocp_clamp_sel,HI6551_BUCK4_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg9_adj_reserved,reserved,HI6551_BUCK4_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg10_adj_buck4_reg_idr,buck4_reg_idr,HI6551_BUCK4_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg10_adj_reserved_1,reserved_1,HI6551_BUCK4_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg10_adj_buck4_reg_r,buck4_reg_r,HI6551_BUCK4_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg10_adj_reserved_0,reserved_0,HI6551_BUCK4_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck4_reg12_adj_buck4_reserve,buck4_reserve,HI6551_BUCK4_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK4_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg1_adj_buck5_adj_rlx,buck5_adj_rlx,HI6551_BUCK5_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg1_adj_buck5_adj_clx,buck5_adj_clx,HI6551_BUCK5_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg2_adj_buck5_new_dmd_sel,buck5_new_dmd_sel,HI6551_BUCK5_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg2_adj_buck5_ocp_sel,buck5_ocp_sel,HI6551_BUCK5_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg2_adj_reserved,reserved,HI6551_BUCK5_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_dmd_sel,buck5_dmd_sel,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_en_regop_clamp,buck5_en_regop_clamp,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_dmd_clamp,buck5_dmd_clamp,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_ocp_delay_sel,buck5_ocp_delay_sel,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_dmd_shield_n,buck5_dmd_shield_n,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_sleep_dmd,buck5_sleep_dmd,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg3_adj_buck5_pdn_lx_det,buck5_pdn_lx_det,HI6551_BUCK5_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg4_adj_buck5_ng_dt_sel,buck5_ng_dt_sel,HI6551_BUCK5_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg4_adj_buck5_pg_dt_sel,buck5_pg_dt_sel,HI6551_BUCK5_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg4_adj_buck5_sft_sel,buck5_sft_sel,HI6551_BUCK5_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg4_adj_reserved,reserved,HI6551_BUCK5_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg5_adj_buck5_pg_n_sel,buck5_pg_n_sel,HI6551_BUCK5_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg5_adj_reserved_1,reserved_1,HI6551_BUCK5_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg5_adj_buck5_pg_p_sel,buck5_pg_p_sel,HI6551_BUCK5_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg5_adj_reserved_0,reserved_0,HI6551_BUCK5_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg6_adj_buck5_ng_n_sel,buck5_ng_n_sel,HI6551_BUCK5_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg6_adj_reserved_1,reserved_1,HI6551_BUCK5_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg6_adj_buck5_ng_p_sel,buck5_ng_p_sel,HI6551_BUCK5_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg6_adj_reserved_0,reserved_0,HI6551_BUCK5_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_buck5_dbias,buck5_dbias,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_buck5_ocp_d,buck5_ocp_d,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_reserved_1,reserved_1,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_buck5_ton,buck5_ton,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg7_adj_reserved_0,reserved_0,HI6551_BUCK5_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_nmos_off,buck5_nmos_off,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_reg_c,buck5_reg_c,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_short_pdp,buck5_short_pdp,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_reg_ss_d,buck5_reg_ss_d,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_dt_sel,buck5_dt_sel,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_buck5_regop_c,buck5_regop_c,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg8_adj_reserved,reserved,HI6551_BUCK5_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg9_adj_buck5_reg_dr,buck5_reg_dr,HI6551_BUCK5_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg9_adj_buck5_en_reg,buck5_en_reg,HI6551_BUCK5_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg9_adj_buck5_ocp_clamp_sel,buck5_ocp_clamp_sel,HI6551_BUCK5_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg9_adj_reserved,reserved,HI6551_BUCK5_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg10_adj_buck5_reg_idr,buck5_reg_idr,HI6551_BUCK5_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg10_adj_reserved_1,reserved_1,HI6551_BUCK5_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg10_adj_buck5_reg_r,buck5_reg_r,HI6551_BUCK5_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg10_adj_reserved_0,reserved_0,HI6551_BUCK5_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg12_adj_buck5_reserve0,buck5_reserve0,HI6551_BUCK5_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg13_adj_buck5_reserve1,buck5_reserve1,HI6551_BUCK5_REG13_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG13_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck5_reg14_adj_buck5_reserve2,buck5_reserve2,HI6551_BUCK5_REG14_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK5_REG14_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg1_adj_buck6_adj_rlx,buck6_adj_rlx,HI6551_BUCK6_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg1_adj_buck6_adj_clx,buck6_adj_clx,HI6551_BUCK6_REG1_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG1_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg2_adj_buck6_new_dmd_sel,buck6_new_dmd_sel,HI6551_BUCK6_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg2_adj_buck6_ocp_sel,buck6_ocp_sel,HI6551_BUCK6_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg2_adj_reserved,reserved,HI6551_BUCK6_REG2_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_dmd_sel,buck6_dmd_sel,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_en_regop_clamp,buck6_en_regop_clamp,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_dmd_clamp,buck6_dmd_clamp,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_ocp_delay_sel,buck6_ocp_delay_sel,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_dmd_shield_n,buck6_dmd_shield_n,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_sleep_dmd,buck6_sleep_dmd,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg3_adj_buck6_pdn_lx_det,buck6_pdn_lx_det,HI6551_BUCK6_REG3_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg4_adj_buck6_ng_dt_sel,buck6_ng_dt_sel,HI6551_BUCK6_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg4_adj_buck6_pg_dt_sel,buck6_pg_dt_sel,HI6551_BUCK6_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg4_adj_buck6_sft_sel,buck6_sft_sel,HI6551_BUCK6_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg4_adj_reserved,reserved,HI6551_BUCK6_REG4_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg5_adj_buck6_pg_n_sel,buck6_pg_n_sel,HI6551_BUCK6_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg5_adj_reserved_1,reserved_1,HI6551_BUCK6_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg5_adj_buck6_pg_p_sel,buck6_pg_p_sel,HI6551_BUCK6_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg5_adj_reserved_0,reserved_0,HI6551_BUCK6_REG5_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg6_adj_buck6_ng_n_sel,buck6_ng_n_sel,HI6551_BUCK6_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg6_adj_reserved_1,reserved_1,HI6551_BUCK6_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg6_adj_buck6_ng_p_sel,buck6_ng_p_sel,HI6551_BUCK6_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg6_adj_reserved_0,reserved_0,HI6551_BUCK6_REG6_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_buck6_dbias,buck6_dbias,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_buck6_ocp_d,buck6_ocp_d,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_reserved_1,reserved_1,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_buck6_ton,buck6_ton,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg7_adj_reserved_0,reserved_0,HI6551_BUCK6_REG7_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG7_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_nmos_off,buck6_nmos_off,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_reg_c,buck6_reg_c,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_short_pdp,buck6_short_pdp,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_reg_ss_d,buck6_reg_ss_d,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_dt_sel,buck6_dt_sel,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_buck6_regop_c,buck6_regop_c,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg8_adj_reserved,reserved,HI6551_BUCK6_REG8_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG8_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg9_adj_buck6_reg_dr,buck6_reg_dr,HI6551_BUCK6_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg9_adj_buck6_en_reg,buck6_en_reg,HI6551_BUCK6_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg9_adj_buck6_ocp_clamp_sel,buck6_ocp_clamp_sel,HI6551_BUCK6_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg9_adj_reserved,reserved,HI6551_BUCK6_REG9_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG9_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg10_adj_buck6_reg_idr,buck6_reg_idr,HI6551_BUCK6_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg10_adj_reserved_1,reserved_1,HI6551_BUCK6_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg10_adj_buck6_reg_r,buck6_reg_r,HI6551_BUCK6_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg10_adj_reserved_0,reserved_0,HI6551_BUCK6_REG10_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG10_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg11_adj_buck6_mos_sel,buck6_mos_sel,HI6551_BUCK6_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg11_adj_reserved,reserved,HI6551_BUCK6_REG11_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG11_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_buck6_reg12_adj_buck6_reserve,buck6_reserve,HI6551_BUCK6_REG12_ADJ_T,HI6551_BASE_ADDR, HI6551_BUCK6_REG12_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_chg_pump2_adj_cp2_vout_sel,cp2_vout_sel,HI6551_CHG_PUMP2_ADJ_T,HI6551_BASE_ADDR, HI6551_CHG_PUMP2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_chg_pump2_adj_reserved,reserved,HI6551_CHG_PUMP2_ADJ_T,HI6551_BASE_ADDR, HI6551_CHG_PUMP2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck01_adj_buck0_vck,buck0_vck,HI6551_VSET_BUCK01_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK01_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck01_adj_reserved,reserved,HI6551_VSET_BUCK01_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK01_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck2_adj_buck2_dv,buck2_dv,HI6551_VSET_BUCK2_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK2_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck3_adj_buck3_dv,buck3_dv,HI6551_VSET_BUCK3_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck3_adj_reserved,reserved,HI6551_VSET_BUCK3_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK3_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck4_adj_buck4_dv,buck4_dv,HI6551_VSET_BUCK4_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck4_adj_reserved,reserved,HI6551_VSET_BUCK4_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK4_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck5_adj_buck5_dv,buck5_dv,HI6551_VSET_BUCK5_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK5_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck6_adj_buck6_dv,buck6_dv,HI6551_VSET_BUCK6_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_vset_buck6_adj_reserved,reserved,HI6551_VSET_BUCK6_ADJ_T,HI6551_BASE_ADDR, HI6551_VSET_BUCK6_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo1_reg_adj_vset_ldo1,vset_ldo1,HI6551_LDO1_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO1_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo1_reg_adj_reserved,reserved,HI6551_LDO1_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO1_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo2_reg_adj_vset_ldo2,vset_ldo2,HI6551_LDO2_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO2_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo2_reg_adj_reserved,reserved,HI6551_LDO2_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO2_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo3_reg_adj_vset_ldo3,vset_ldo3,HI6551_LDO3_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO3_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo3_reg_adj_reserved_1,reserved_1,HI6551_LDO3_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO3_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo3_reg_adj_vrset_ldo3,vrset_ldo3,HI6551_LDO3_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO3_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo3_reg_adj_reserved_0,reserved_0,HI6551_LDO3_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO3_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo4_reg_adj_vset_ldo4,vset_ldo4,HI6551_LDO4_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO4_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo4_reg_adj_reserved,reserved,HI6551_LDO4_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO4_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo5_reg_adj_vset_ldo5,vset_ldo5,HI6551_LDO5_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO5_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo5_reg_adj_reserved_1,reserved_1,HI6551_LDO5_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO5_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo5_reg_adj_vrset_ldo5,vrset_ldo5,HI6551_LDO5_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO5_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo5_reg_adj_reserved_0,reserved_0,HI6551_LDO5_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO5_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo6_reg_adj_vset_ldo6,vset_ldo6,HI6551_LDO6_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO6_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo6_reg_adj_reserved,reserved,HI6551_LDO6_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO6_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo7_reg_adj_vset_ldo7,vset_ldo7,HI6551_LDO7_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO7_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo7_reg_adj_reserved,reserved,HI6551_LDO7_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO7_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo8_reg_adj_vset_ldo8,vset_ldo8,HI6551_LDO8_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO8_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo8_reg_adj_reserved_1,reserved_1,HI6551_LDO8_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO8_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo8_reg_adj_vrset_ldo8,vrset_ldo8,HI6551_LDO8_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO8_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo8_reg_adj_reserved_0,reserved_0,HI6551_LDO8_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO8_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo9_reg_adj_vset_ldo9,vset_ldo9,HI6551_LDO9_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO9_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo9_reg_adj_reserved_1,reserved_1,HI6551_LDO9_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO9_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo9_reg_adj_vrset_ldo9,vrset_ldo9,HI6551_LDO9_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO9_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo9_reg_adj_reserved_0,reserved_0,HI6551_LDO9_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO9_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo10_reg_adj_vset_ldo10,vset_ldo10,HI6551_LDO10_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO10_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo10_reg_adj_reserved_1,reserved_1,HI6551_LDO10_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO10_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo10_reg_adj_vrset_ldo10,vrset_ldo10,HI6551_LDO10_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO10_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo10_reg_adj_reserved_0,reserved_0,HI6551_LDO10_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO10_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo11_reg_adj_vset_ldo11,vset_ldo11,HI6551_LDO11_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO11_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo11_reg_adj_reserved_1,reserved_1,HI6551_LDO11_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO11_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo11_reg_adj_vrset_ldo11,vrset_ldo11,HI6551_LDO11_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO11_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo11_reg_adj_reserved_0,reserved_0,HI6551_LDO11_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO11_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo12_reg_adj_vset_ldo12,vset_ldo12,HI6551_LDO12_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO12_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo12_reg_adj_reserved_1,reserved_1,HI6551_LDO12_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO12_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo12_reg_adj_vrset_ldo12,vrset_ldo12,HI6551_LDO12_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO12_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo12_reg_adj_reserved_0,reserved_0,HI6551_LDO12_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO12_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo13_reg_adj_vset_ldo13,vset_ldo13,HI6551_LDO13_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO13_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo13_reg_adj_reserved,reserved,HI6551_LDO13_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO13_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo14_reg_adj_vset_ldo14,vset_ldo14,HI6551_LDO14_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO14_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo14_reg_adj_reserved_1,reserved_1,HI6551_LDO14_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO14_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo14_reg_adj_vrset_ldo14,vrset_ldo14,HI6551_LDO14_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO14_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo14_reg_adj_reserved_0,reserved_0,HI6551_LDO14_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO14_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo15_reg_adj_vset_ldo15,vset_ldo15,HI6551_LDO15_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO15_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo15_reg_adj_reserved_1,reserved_1,HI6551_LDO15_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO15_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo15_reg_adj_vrset_ldo15,vrset_ldo15,HI6551_LDO15_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO15_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo15_reg_adj_reserved_0,reserved_0,HI6551_LDO15_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO15_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo16_reg_adj_vset_ldo16,vset_ldo16,HI6551_LDO16_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO16_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo16_reg_adj_reserved_1,reserved_1,HI6551_LDO16_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO16_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo16_reg_adj_vrset_ldo16,vrset_ldo16,HI6551_LDO16_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO16_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo16_reg_adj_reserved_0,reserved_0,HI6551_LDO16_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO16_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo17_reg_adj_vset_ldo17,vset_ldo17,HI6551_LDO17_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO17_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo17_reg_adj_reserved_1,reserved_1,HI6551_LDO17_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO17_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo17_reg_adj_vrset_ldo17,vrset_ldo17,HI6551_LDO17_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO17_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo17_reg_adj_reserved_0,reserved_0,HI6551_LDO17_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO17_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo18_reg_adj_vset_ldo18,vset_ldo18,HI6551_LDO18_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO18_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo18_reg_adj_reserved_1,reserved_1,HI6551_LDO18_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO18_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo18_reg_adj_vrset_ldo18,vrset_ldo18,HI6551_LDO18_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO18_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo18_reg_adj_reserved_0,reserved_0,HI6551_LDO18_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO18_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo19_reg_adj_vset_ldo19,vset_ldo19,HI6551_LDO19_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO19_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo19_reg_adj_reserved_1,reserved_1,HI6551_LDO19_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO19_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo19_reg_adj_vrset_ldo19,vrset_ldo19,HI6551_LDO19_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO19_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo19_reg_adj_reserved_0,reserved_0,HI6551_LDO19_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO19_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo20_reg_adj_vset_ldo20,vset_ldo20,HI6551_LDO20_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO20_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo20_reg_adj_reserved_1,reserved_1,HI6551_LDO20_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO20_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo20_reg_adj_vrset_ldo20,vrset_ldo20,HI6551_LDO20_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO20_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo20_reg_adj_reserved_0,reserved_0,HI6551_LDO20_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO20_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo21_reg_adj_vset_ldo21,vset_ldo21,HI6551_LDO21_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO21_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo21_reg_adj_reserved_1,reserved_1,HI6551_LDO21_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO21_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo21_reg_adj_vrset_ldo21,vrset_ldo21,HI6551_LDO21_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO21_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo21_reg_adj_reserved_0,reserved_0,HI6551_LDO21_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO21_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo22_reg_adj_vset_ldo22,vset_ldo22,HI6551_LDO22_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO22_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo22_reg_adj_en_sink_ldo22,en_sink_ldo22,HI6551_LDO22_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO22_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo22_reg_adj_rset_sink_ldo22,rset_sink_ldo22,HI6551_LDO22_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO22_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo22_reg_adj_reserved,reserved,HI6551_LDO22_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO22_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo23_reg_adj_vset_ldo23,vset_ldo23,HI6551_LDO23_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO23_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo23_reg_adj_reserved_1,reserved_1,HI6551_LDO23_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO23_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo23_reg_adj_vrset_ldo23,vrset_ldo23,HI6551_LDO23_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO23_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo23_reg_adj_reserved_0,reserved_0,HI6551_LDO23_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO23_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo24_reg_adj_vset_ldo24,vset_ldo24,HI6551_LDO24_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO24_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_ldo24_reg_adj_reserved,reserved,HI6551_LDO24_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_LDO24_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_pmua_reg_adj_vset_pmua,vset_pmua,HI6551_PMUA_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_PMUA_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_pmua_reg_adj_eco_pmua,eco_pmua,HI6551_PMUA_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_PMUA_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_pmua_reg_adj_reserved,reserved,HI6551_PMUA_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_PMUA_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj1_sstset_lvs5,sstset_lvs5,HI6551_LVS_ADJ1_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj1_sstset_lvs4,sstset_lvs4,HI6551_LVS_ADJ1_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj1_sstset_lvs3,sstset_lvs3,HI6551_LVS_ADJ1_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj1_sstset_lvs2,sstset_lvs2,HI6551_LVS_ADJ1_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj2_sstset_lvs9,sstset_lvs9,HI6551_LVS_ADJ2_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj2_sstset_lvs8,sstset_lvs8,HI6551_LVS_ADJ2_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj2_sstset_lvs7,sstset_lvs7,HI6551_LVS_ADJ2_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj2_sstset_lvs6,sstset_lvs6,HI6551_LVS_ADJ2_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj3_sstset_lvs10,sstset_lvs10,HI6551_LVS_ADJ3_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_lvs_adj3_reserved,reserved,HI6551_LVS_ADJ3_T,HI6551_BASE_ADDR, HI6551_LVS_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj0_en_bst_int,en_bst_int,HI6551_BOOST_ADJ0_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj0_bst_pm_th,bst_pm_th,HI6551_BOOST_ADJ0_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj0_bst_pm_cut,bst_pm_cut,HI6551_BOOST_ADJ0_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj0_bst_reserved0,bst_reserved0,HI6551_BOOST_ADJ0_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_sel_scp,bst_sel_scp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_sel_pd,bst_sel_pd,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_en_uvp,bst_en_uvp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_en_scp,bst_en_scp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_en_ovp,bst_en_ovp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_en_ocp,bst_en_ocp,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj1_bst_reserved1,bst_reserved1,HI6551_BOOST_ADJ1_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_drv_mode,bst_drv_mode,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_loop_mode,bst_loop_mode,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_pfm,bst_en_pfm,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_nring,bst_en_nring,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_clp_os,bst_en_clp_os,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_slop,bst_en_slop,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_en_dmd,bst_en_dmd,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj2_bst_reserved2,bst_reserved2,HI6551_BOOST_ADJ2_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj3_bst_clp,bst_clp,HI6551_BOOST_ADJ3_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj3_bst_itail,bst_itail,HI6551_BOOST_ADJ3_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj3_bst_gm,bst_gm,HI6551_BOOST_ADJ3_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj3_bst_reserved3,bst_reserved3,HI6551_BOOST_ADJ3_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ3_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj4_bst_ccom2,bst_ccom2,HI6551_BOOST_ADJ4_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ4_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj4_bst_ccom1,bst_ccom1,HI6551_BOOST_ADJ4_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ4_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj4_bst_rcom,bst_rcom,HI6551_BOOST_ADJ4_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ4_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj4_bst_reserved4,bst_reserved4,HI6551_BOOST_ADJ4_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ4_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj5_bst_slop,bst_slop,HI6551_BOOST_ADJ5_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ5_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj5_bst_ri,bst_ri,HI6551_BOOST_ADJ5_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ5_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj5_bst_reserved5,bst_reserved5,HI6551_BOOST_ADJ5_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ5_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj6_bst_nsn,bst_nsn,HI6551_BOOST_ADJ6_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ6_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj6_bst_nsp,bst_nsp,HI6551_BOOST_ADJ6_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ6_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj6_bst_psn,bst_psn,HI6551_BOOST_ADJ6_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ6_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj6_bst_psp,bst_psp,HI6551_BOOST_ADJ6_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ6_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj7_bst_dt_nm,bst_dt_nm,HI6551_BOOST_ADJ7_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ7_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj7_bst_dt_pm,bst_dt_pm,HI6551_BOOST_ADJ7_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ7_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj7_bst_lxde,bst_lxde,HI6551_BOOST_ADJ7_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ7_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj7_bst_reserved6,bst_reserved6,HI6551_BOOST_ADJ7_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ7_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj8_bst_ckmin,bst_ckmin,HI6551_BOOST_ADJ8_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ8_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj8_bst_osc,bst_osc,HI6551_BOOST_ADJ8_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ8_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj8_bst_reserved7,bst_reserved7,HI6551_BOOST_ADJ8_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ8_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj9_vo,vo,HI6551_BOOST_ADJ9_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ9_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj9_sel_ocp,sel_ocp,HI6551_BOOST_ADJ9_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ9_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj9_bst_start,bst_start,HI6551_BOOST_ADJ9_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ9_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj10_bst_dmd_ofs,bst_dmd_ofs,HI6551_BOOST_ADJ10_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ10_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj10_bst_reserved10,bst_reserved10,HI6551_BOOST_ADJ10_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ10_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj11_bst_v2clp,bst_v2clp,HI6551_BOOST_ADJ11_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ11_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj11_bst_v2div,bst_v2div,HI6551_BOOST_ADJ11_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ11_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj11_bst_v2ramp,bst_v2ramp,HI6551_BOOST_ADJ11_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ11_OFFSET)
HI_SET_GET(hi_hi6551_boost_adj11_bst_reserved11,bst_reserved11,HI6551_BOOST_ADJ11_T,HI6551_BASE_ADDR, HI6551_BOOST_ADJ11_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_classd_mute_sel,classd_mute_sel,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_classd_mute,classd_mute,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_classd_gain,classd_gain,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_en_classd_int,en_classd_int,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_classd_i_ocp,classd_i_ocp,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj0_reserved,reserved,HI6551_CLASSD_ADJ0_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ0_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj1_classd_n_sel,classd_n_sel,HI6551_CLASSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj1_classd_p_sel,classd_p_sel,HI6551_CLASSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj1_classd_i_ramp,classd_i_ramp,HI6551_CLASSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj1_classd_i_pump,classd_i_pump,HI6551_CLASSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_ocp_bps,classd_ocp_bps,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_fx_bps,classd_fx_bps,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_dt_sel,classd_dt_sel,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_pls_byp,classd_pls_byp,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_classd_adj2_classd_reserved,classd_reserved,HI6551_CLASSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_CLASSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj1_bg_test,bg_test,HI6551_BANDGAP_THSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj1_bg_sleep,bg_sleep,HI6551_BANDGAP_THSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj1_reserved,reserved,HI6551_BANDGAP_THSD_ADJ1_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj2_en_tmp_int,en_tmp_int,HI6551_BANDGAP_THSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj2_reserved_1,reserved_1,HI6551_BANDGAP_THSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj2_thsd_set_tmp,thsd_set_tmp,HI6551_BANDGAP_THSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_bandgap_thsd_adj2_reserved_0,reserved_0,HI6551_BANDGAP_THSD_ADJ2_T,HI6551_BASE_ADDR, HI6551_BANDGAP_THSD_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_en_dr3_int,en_dr3_int,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_dr3_mode,dr3_mode,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_en_dr4_int,en_dr4_int,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_dr4_mode,dr4_mode,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_en_dr5_int,en_dr5_int,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_dr5_mode,dr5_mode,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl1_reserved,reserved,HI6551_DR_FLA_CTRL1_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_en_dr1_int,en_dr1_int,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_dr1_mode,dr1_mode,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_reserved_1,reserved_1,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_en_dr2_int,en_dr2_int,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_dr2_mode,dr2_mode,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_dr_fla_ctrl2_reserved_0,reserved_0,HI6551_DR_FLA_CTRL2_T,HI6551_BASE_ADDR, HI6551_DR_FLA_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_flash_period_flash_period,flash_period,HI6551_FLASH_PERIOD_T,HI6551_BASE_ADDR, HI6551_FLASH_PERIOD_OFFSET)
HI_SET_GET(hi_hi6551_flash_on_flash_on,flash_on,HI6551_FLASH_ON_T,HI6551_BASE_ADDR, HI6551_FLASH_ON_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr1_mode_sel,dr1_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr2_mode_sel,dr2_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr3_mode_sel,dr3_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr4_mode_sel,dr4_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_dr5_mode_sel,dr5_mode_sel,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_mode_sel_reserved,reserved,HI6551_DR_MODE_SEL_T,HI6551_BASE_ADDR, HI6551_DR_MODE_SEL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_dr1_en,dr1_en,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_dr1_flash_en,dr1_flash_en,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_reserved_1,reserved_1,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_dr2_en,dr2_en,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_dr2_flash_en,dr2_flash_en,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_bre_ctrl_reserved_0,reserved_0,HI6551_DR_BRE_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_BRE_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf0_dr1_t_off,dr1_t_off,HI6551_DR1_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf0_reserved_1,reserved_1,HI6551_DR1_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf0_dr1_t_on,dr1_t_on,HI6551_DR1_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf0_reserved_0,reserved_0,HI6551_DR1_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf1_dr1_t_rise,dr1_t_rise,HI6551_DR1_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf1_reserved_1,reserved_1,HI6551_DR1_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf1_dr1_t_fall,dr1_t_fall,HI6551_DR1_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr1_tim_conf1_reserved_0,reserved_0,HI6551_DR1_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR1_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr1_iset_iset_dr1,iset_dr1,HI6551_DR1_ISET_T,HI6551_BASE_ADDR, HI6551_DR1_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr1_iset_reserved,reserved,HI6551_DR1_ISET_T,HI6551_BASE_ADDR, HI6551_DR1_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf0_dr2_t_off,dr2_t_off,HI6551_DR2_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf0_reserved_1,reserved_1,HI6551_DR2_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf0_dr2_t_on,dr2_t_on,HI6551_DR2_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf0_reserved_0,reserved_0,HI6551_DR2_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf1_dr2_t_rise,dr2_t_rise,HI6551_DR2_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf1_reserved_1,reserved_1,HI6551_DR2_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf1_dr2_t_fall,dr2_t_fall,HI6551_DR2_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr2_tim_conf1_reserved_0,reserved_0,HI6551_DR2_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR2_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr2_iset_iset_dr2,iset_dr2,HI6551_DR2_ISET_T,HI6551_BASE_ADDR, HI6551_DR2_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr2_iset_reserved,reserved,HI6551_DR2_ISET_T,HI6551_BASE_ADDR, HI6551_DR2_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_dr3_en,dr3_en,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_dr4_en,dr4_en,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_dr5_en,dr5_en,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_dr_eco_en,dr_eco_en,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_led_ctrl_reserved,reserved,HI6551_DR_LED_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_LED_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_out_ctrl_dr3_out_ctrl,dr3_out_ctrl,HI6551_DR_OUT_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_OUT_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_out_ctrl_dr4_out_ctrl,dr4_out_ctrl,HI6551_DR_OUT_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_OUT_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_out_ctrl_dr5_out_ctrl,dr5_out_ctrl,HI6551_DR_OUT_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_OUT_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr_out_ctrl_reserved,reserved,HI6551_DR_OUT_CTRL_T,HI6551_BASE_ADDR, HI6551_DR_OUT_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dr3_iset_iset_dr3,iset_dr3,HI6551_DR3_ISET_T,HI6551_BASE_ADDR, HI6551_DR3_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr3_iset_reserved,reserved,HI6551_DR3_ISET_T,HI6551_BASE_ADDR, HI6551_DR3_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr3_start_del_dr3_start_delay,dr3_start_delay,HI6551_DR3_START_DEL_T,HI6551_BASE_ADDR, HI6551_DR3_START_DEL_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf0_dr3_t_off,dr3_t_off,HI6551_DR3_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf0_dr3_t_on,dr3_t_on,HI6551_DR3_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf1_dr3_t_rise,dr3_t_rise,HI6551_DR3_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf1_reserved_1,reserved_1,HI6551_DR3_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf1_dr3_t_fall,dr3_t_fall,HI6551_DR3_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr3_tim_conf1_reserved_0,reserved_0,HI6551_DR3_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR3_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr4_iset_iset_dr4,iset_dr4,HI6551_DR4_ISET_T,HI6551_BASE_ADDR, HI6551_DR4_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr4_iset_reserved,reserved,HI6551_DR4_ISET_T,HI6551_BASE_ADDR, HI6551_DR4_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr4_start_del_dr4_start_delay,dr4_start_delay,HI6551_DR4_START_DEL_T,HI6551_BASE_ADDR, HI6551_DR4_START_DEL_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf0_dr4_t_off,dr4_t_off,HI6551_DR4_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf0_dr4_t_on,dr4_t_on,HI6551_DR4_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf1_dr4_t_rise,dr4_t_rise,HI6551_DR4_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf1_reserved_1,reserved_1,HI6551_DR4_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf1_dr4_t_fall,dr4_t_fall,HI6551_DR4_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr4_tim_conf1_reserved_0,reserved_0,HI6551_DR4_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR4_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr5_iset_iset_dr5,iset_dr5,HI6551_DR5_ISET_T,HI6551_BASE_ADDR, HI6551_DR5_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr5_iset_reserved,reserved,HI6551_DR5_ISET_T,HI6551_BASE_ADDR, HI6551_DR5_ISET_OFFSET)
HI_SET_GET(hi_hi6551_dr5_start_del_dr5_start_delay,dr5_start_delay,HI6551_DR5_START_DEL_T,HI6551_BASE_ADDR, HI6551_DR5_START_DEL_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf0_dr5_t_off,dr5_t_off,HI6551_DR5_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf0_dr5_t_on,dr5_t_on,HI6551_DR5_TIM_CONF0_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF0_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf1_dr5_t_rise,dr5_t_rise,HI6551_DR5_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf1_reserved_1,reserved_1,HI6551_DR5_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf1_dr5_t_fall,dr5_t_fall,HI6551_DR5_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_dr5_tim_conf1_reserved_0,reserved_0,HI6551_DR5_TIM_CONF1_T,HI6551_BASE_ADDR, HI6551_DR5_TIM_CONF1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_otp_pwe_int,otp_pwe_int,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_otp_pwe_pulse,otp_pwe_pulse,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_otp_write_mask,otp_write_mask,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_otp_por_int,otp_por_int,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl1_reserved,reserved,HI6551_OTP_CTRL1_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL1_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl2_otp_pa,otp_pa,HI6551_OTP_CTRL2_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl2_otp_ptm,otp_ptm,HI6551_OTP_CTRL2_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl2_otp_pprog,otp_pprog,HI6551_OTP_CTRL2_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_otp_ctrl2_reserved,reserved,HI6551_OTP_CTRL2_T,HI6551_BASE_ADDR, HI6551_OTP_CTRL2_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdin_otp_pdin,otp_pdin,HI6551_OTP_PDIN_T,HI6551_BASE_ADDR, HI6551_OTP_PDIN_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdob0_otp_pdob0,otp_pdob0,HI6551_OTP_PDOB0_T,HI6551_BASE_ADDR, HI6551_OTP_PDOB0_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdob1_otp_pdob1,otp_pdob1,HI6551_OTP_PDOB1_T,HI6551_BASE_ADDR, HI6551_OTP_PDOB1_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdob2_otp_pdob2,otp_pdob2,HI6551_OTP_PDOB2_T,HI6551_BASE_ADDR, HI6551_OTP_PDOB2_OFFSET)
HI_SET_GET(hi_hi6551_otp_pdob3_otp_pdob3,otp_pdob3,HI6551_OTP_PDOB3_T,HI6551_BASE_ADDR, HI6551_OTP_PDOB3_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_a0_rtccr_a0,rtccr_a0,HI6551_RTCCR_A0_T,HI6551_BASE_ADDR, HI6551_RTCCR_A0_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_a1_rtccr_a1,rtccr_a1,HI6551_RTCCR_A1_T,HI6551_BASE_ADDR, HI6551_RTCCR_A1_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_a2_rtccr_a2,rtccr_a2,HI6551_RTCCR_A2_T,HI6551_BASE_ADDR, HI6551_RTCCR_A2_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_a3_rtccr_a3,rtccr_a3,HI6551_RTCCR_A3_T,HI6551_BASE_ADDR, HI6551_RTCCR_A3_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_a0_rtclr_a0,rtclr_a0,HI6551_RTCLR_A0_T,HI6551_BASE_ADDR, HI6551_RTCLR_A0_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_a1_rtclr_a1,rtclr_a1,HI6551_RTCLR_A1_T,HI6551_BASE_ADDR, HI6551_RTCLR_A1_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_a2_rtclr_a2,rtclr_a2,HI6551_RTCLR_A2_T,HI6551_BASE_ADDR, HI6551_RTCLR_A2_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_a3_rtclr_a3,rtclr_a3,HI6551_RTCLR_A3_T,HI6551_BASE_ADDR, HI6551_RTCLR_A3_OFFSET)
HI_SET_GET(hi_hi6551_rtcctrl_a_rtccr_a,rtccr_a,HI6551_RTCCTRL_A_T,HI6551_BASE_ADDR, HI6551_RTCCTRL_A_OFFSET)
HI_SET_GET(hi_hi6551_rtcctrl_a_reserved,reserved,HI6551_RTCCTRL_A_T,HI6551_BASE_ADDR, HI6551_RTCCTRL_A_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_a0_rtcmr_a_a0,rtcmr_a_a0,HI6551_RTCMR_A_A0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_A0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_a1_rtcmr_a_a1,rtcmr_a_a1,HI6551_RTCMR_A_A1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_A1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_a2_rtcmr_a_a2,rtcmr_a_a2,HI6551_RTCMR_A_A2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_A2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_a3_rtcmr_a_a3,rtcmr_a_a3,HI6551_RTCMR_A_A3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_A3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_b0_rtcmr_a_b0,rtcmr_a_b0,HI6551_RTCMR_A_B0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_B0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_b1_rtcmr_a_b1,rtcmr_a_b1,HI6551_RTCMR_A_B1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_B1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_b2_rtcmr_a_b2,rtcmr_a_b2,HI6551_RTCMR_A_B2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_B2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_b3_rtcmr_a_b3,rtcmr_a_b3,HI6551_RTCMR_A_B3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_B3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_c0_rtcmr_a_c0,rtcmr_a_c0,HI6551_RTCMR_A_C0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_C0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_c1_rtcmr_a_c1,rtcmr_a_c1,HI6551_RTCMR_A_C1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_C1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_c2_rtcmr_a_c2,rtcmr_a_c2,HI6551_RTCMR_A_C2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_C2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_c3_rtcmr_a_c3,rtcmr_a_c3,HI6551_RTCMR_A_C3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_C3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_d0_rtcmr_a_d0,rtcmr_a_d0,HI6551_RTCMR_A_D0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_D0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_d1_rtcmr_a_d1,rtcmr_a_d1,HI6551_RTCMR_A_D1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_D1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_d2_rtcmr_a_d2,rtcmr_a_d2,HI6551_RTCMR_A_D2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_D2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_d3_rtcmr_a_d3,rtcmr_a_d3,HI6551_RTCMR_A_D3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_D3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_e0_rtcmr_a_e0,rtcmr_a_e0,HI6551_RTCMR_A_E0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_E0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_e1_rtcmr_a_e1,rtcmr_a_e1,HI6551_RTCMR_A_E1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_E1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_e2_rtcmr_a_e2,rtcmr_a_e2,HI6551_RTCMR_A_E2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_E2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_e3_rtcmr_a_e3,rtcmr_a_e3,HI6551_RTCMR_A_E3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_E3_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_f0_rtcmr_a_f0,rtcmr_a_f0,HI6551_RTCMR_A_F0_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_F0_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_f1_rtcmr_a_f1,rtcmr_a_f1,HI6551_RTCMR_A_F1_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_F1_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_f2_rtcmr_a_f2,rtcmr_a_f2,HI6551_RTCMR_A_F2_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_F2_OFFSET)
HI_SET_GET(hi_hi6551_rtcmr_a_f3_rtcmr_a_f3,rtcmr_a_f3,HI6551_RTCMR_A_F3_T,HI6551_BASE_ADDR, HI6551_RTCMR_A_F3_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_na0_rtccr_na0,rtccr_na0,HI6551_RTCCR_NA0_T,HI6551_BASE_ADDR, HI6551_RTCCR_NA0_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_na1_rtccr_na1,rtccr_na1,HI6551_RTCCR_NA1_T,HI6551_BASE_ADDR, HI6551_RTCCR_NA1_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_na2_rtccr_na2,rtccr_na2,HI6551_RTCCR_NA2_T,HI6551_BASE_ADDR, HI6551_RTCCR_NA2_OFFSET)
HI_SET_GET(hi_hi6551_rtccr_na3_rtccr_na3,rtccr_na3,HI6551_RTCCR_NA3_T,HI6551_BASE_ADDR, HI6551_RTCCR_NA3_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_na0_rtclr_na0,rtclr_na0,HI6551_RTCLR_NA0_T,HI6551_BASE_ADDR, HI6551_RTCLR_NA0_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_na1_rtclr_na1,rtclr_na1,HI6551_RTCLR_NA1_T,HI6551_BASE_ADDR, HI6551_RTCLR_NA1_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_na2_rtclr_na2,rtclr_na2,HI6551_RTCLR_NA2_T,HI6551_BASE_ADDR, HI6551_RTCLR_NA2_OFFSET)
HI_SET_GET(hi_hi6551_rtclr_na3_rtclr_na3,rtclr_na3,HI6551_RTCLR_NA3_T,HI6551_BASE_ADDR, HI6551_RTCLR_NA3_OFFSET)
HI_SET_GET(hi_hi6551_rtcctrl_na_rtccr_na,rtccr_na,HI6551_RTCCTRL_NA_T,HI6551_BASE_ADDR, HI6551_RTCCTRL_NA_OFFSET)
HI_SET_GET(hi_hi6551_rtcctrl_na_reserved,reserved,HI6551_RTCCTRL_NA_T,HI6551_BASE_ADDR, HI6551_RTCCTRL_NA_OFFSET)
HI_SET_GET(hi_hi6551_version_version,version,HI6551_VERSION_T,HI6551_BASE_ADDR, HI6551_VERSION_OFFSET)
HI_SET_GET(hi_hi6551_reserved0_reserved0,reserved0,HI6551_RESERVED0_T,HI6551_BASE_ADDR, HI6551_RESERVED0_OFFSET)
HI_SET_GET(hi_hi6551_reserved1_reserved1,reserved1,HI6551_RESERVED1_T,HI6551_BASE_ADDR, HI6551_RESERVED1_OFFSET)
HI_SET_GET(hi_hi6551_reserved2_reserved2,reserved2,HI6551_RESERVED2_T,HI6551_BASE_ADDR, HI6551_RESERVED2_OFFSET)
HI_SET_GET(hi_hi6551_reserved3_reserved3,reserved3,HI6551_RESERVED3_T,HI6551_BASE_ADDR, HI6551_RESERVED3_OFFSET)
HI_SET_GET(hi_hi6551_reserved4_reserved4,reserved4,HI6551_RESERVED4_T,HI6551_BASE_ADDR, HI6551_RESERVED4_OFFSET)
HI_SET_GET(hi_hi6551_htol_mode_htol_mode,htol_mode,HI6551_HTOL_MODE_T,HI6551_BASE_ADDR, HI6551_HTOL_MODE_OFFSET)
HI_SET_GET(hi_hi6551_htol_mode_reserved,reserved,HI6551_HTOL_MODE_T,HI6551_BASE_ADDR, HI6551_HTOL_MODE_OFFSET)
HI_SET_GET(hi_hi6551_dac_ctrl_dac_on_sel,dac_on_sel,HI6551_DAC_CTRL_T,HI6551_BASE_ADDR, HI6551_DAC_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dac_ctrl_aux_ibias_cfg,aux_ibias_cfg,HI6551_DAC_CTRL_T,HI6551_BASE_ADDR, HI6551_DAC_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_dac_ctrl_reserved,reserved,HI6551_DAC_CTRL_T,HI6551_BASE_ADDR, HI6551_DAC_CTRL_OFFSET)
HI_SET_GET(hi_hi6551_chip_soft_rst_soft_rst,soft_rst,HI6551_CHIP_SOFT_RST_T,HI6551_BASE_ADDR, HI6551_CHIP_SOFT_RST_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_pdns_sel,pdns_sel,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_pdns_mk,pdns_mk,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_vsys_uv_adj,vsys_uv_adj,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_nopwr_rc_off,nopwr_rc_off,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_adj_reserved,reserved,HI6551_NP_REG_ADJ_T,HI6551_BASE_ADDR, HI6551_NP_REG_ADJ_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_chg_nopwr_vcoinsl,nopwr_vcoinsl,HI6551_NP_REG_CHG_T,HI6551_BASE_ADDR, HI6551_NP_REG_CHG_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_chg_nopwr_en_backup_chg,nopwr_en_backup_chg,HI6551_NP_REG_CHG_T,HI6551_BASE_ADDR, HI6551_NP_REG_CHG_OFFSET)
HI_SET_GET(hi_hi6551_np_reg_chg_reserved,reserved,HI6551_NP_REG_CHG_T,HI6551_BASE_ADDR, HI6551_NP_REG_CHG_OFFSET)
HI_SET_GET(hi_hi6551_np_rsved1_no_pwr_resved1,no_pwr_resved1,HI6551_NP_RSVED1_T,HI6551_BASE_ADDR, HI6551_NP_RSVED1_OFFSET)
HI_SET_GET(hi_hi6551_np_rsved2_no_pwr_resved2,no_pwr_resved2,HI6551_NP_RSVED2_T,HI6551_BASE_ADDR, HI6551_NP_RSVED2_OFFSET)
HI_SET_GET(hi_hi6551_np_rsved3_no_pwr_resved3,no_pwr_resved3,HI6551_NP_RSVED3_T,HI6551_BASE_ADDR, HI6551_NP_RSVED3_OFFSET)
HI_SET_GET(hi_hi6551_np_rsved4_no_pwr_resved4,no_pwr_resved4,HI6551_NP_RSVED4_T,HI6551_BASE_ADDR, HI6551_NP_RSVED4_OFFSET)
HI_SET_GET(hi_hi6551_rtc_adj1_rtc_clk_step_adj1,rtc_clk_step_adj1,HI6551_RTC_ADJ1_T,HI6551_BASE_ADDR, HI6551_RTC_ADJ1_OFFSET)
HI_SET_GET(hi_hi6551_rtc_adj2_rtc_clk_step_adj2,rtc_clk_step_adj2,HI6551_RTC_ADJ2_T,HI6551_BASE_ADDR, HI6551_RTC_ADJ2_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_eco_ctrl,eco_ctrl,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_reflash_value_ctrl,reflash_value_ctrl,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_eco_filter_time,eco_filter_time,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_calibration_ctrl,calibration_ctrl,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_clj_ctrl_reg_coul_ctrl_onoff_reg,coul_ctrl_onoff_reg,HI6551_CLJ_CTRL_REG_T,HI6551_BASE_ADDR, HI6551_CLJ_CTRL_REG_OFFSET)
HI_SET_GET(hi_hi6551_eco_refalsh_time_eco_reflash_time,eco_reflash_time,HI6551_ECO_REFALSH_TIME_T,HI6551_BASE_ADDR, HI6551_ECO_REFALSH_TIME_OFFSET)
HI_SET_GET(hi_hi6551_cl_out0_cl_out0,cl_out0,HI6551_CL_OUT0_T,HI6551_BASE_ADDR, HI6551_CL_OUT0_OFFSET)
HI_SET_GET(hi_hi6551_cl_out1_cl_out1,cl_out1,HI6551_CL_OUT1_T,HI6551_BASE_ADDR, HI6551_CL_OUT1_OFFSET)
HI_SET_GET(hi_hi6551_cl_out2_cl_out2,cl_out2,HI6551_CL_OUT2_T,HI6551_BASE_ADDR, HI6551_CL_OUT2_OFFSET)
HI_SET_GET(hi_hi6551_cl_out3_cl_out3,cl_out3,HI6551_CL_OUT3_T,HI6551_BASE_ADDR, HI6551_CL_OUT3_OFFSET)
HI_SET_GET(hi_hi6551_cl_in0_cl_in0,cl_in0,HI6551_CL_IN0_T,HI6551_BASE_ADDR, HI6551_CL_IN0_OFFSET)
HI_SET_GET(hi_hi6551_cl_in1_cl_in1,cl_in1,HI6551_CL_IN1_T,HI6551_BASE_ADDR, HI6551_CL_IN1_OFFSET)
HI_SET_GET(hi_hi6551_cl_in2_cl_in2,cl_in2,HI6551_CL_IN2_T,HI6551_BASE_ADDR, HI6551_CL_IN2_OFFSET)
HI_SET_GET(hi_hi6551_cl_in3_cl_in3,cl_in3,HI6551_CL_IN3_T,HI6551_BASE_ADDR, HI6551_CL_IN3_OFFSET)
HI_SET_GET(hi_hi6551_chg_timer0_chg_timer0,chg_timer0,HI6551_CHG_TIMER0_T,HI6551_BASE_ADDR, HI6551_CHG_TIMER0_OFFSET)
HI_SET_GET(hi_hi6551_chg_timer1_chg_timer1,chg_timer1,HI6551_CHG_TIMER1_T,HI6551_BASE_ADDR, HI6551_CHG_TIMER1_OFFSET)
HI_SET_GET(hi_hi6551_chg_timer2_chg_timer2,chg_timer2,HI6551_CHG_TIMER2_T,HI6551_BASE_ADDR, HI6551_CHG_TIMER2_OFFSET)
HI_SET_GET(hi_hi6551_chg_timer3_chg_timer3,chg_timer3,HI6551_CHG_TIMER3_T,HI6551_BASE_ADDR, HI6551_CHG_TIMER3_OFFSET)
HI_SET_GET(hi_hi6551_load_timer0_load_timer0,load_timer0,HI6551_LOAD_TIMER0_T,HI6551_BASE_ADDR, HI6551_LOAD_TIMER0_OFFSET)
HI_SET_GET(hi_hi6551_load_timer1_load_timer1,load_timer1,HI6551_LOAD_TIMER1_T,HI6551_BASE_ADDR, HI6551_LOAD_TIMER1_OFFSET)
HI_SET_GET(hi_hi6551_load_timer2_load_timer2,load_timer2,HI6551_LOAD_TIMER2_T,HI6551_BASE_ADDR, HI6551_LOAD_TIMER2_OFFSET)
HI_SET_GET(hi_hi6551_load_timer3_load_timer3,load_timer3,HI6551_LOAD_TIMER3_T,HI6551_BASE_ADDR, HI6551_LOAD_TIMER3_OFFSET)
HI_SET_GET(hi_hi6551_off_timer0_off_timer0,off_timer0,HI6551_OFF_TIMER0_T,HI6551_BASE_ADDR, HI6551_OFF_TIMER0_OFFSET)
HI_SET_GET(hi_hi6551_off_timer1_off_timer1,off_timer1,HI6551_OFF_TIMER1_T,HI6551_BASE_ADDR, HI6551_OFF_TIMER1_OFFSET)
HI_SET_GET(hi_hi6551_off_timer2_off_timer2,off_timer2,HI6551_OFF_TIMER2_T,HI6551_BASE_ADDR, HI6551_OFF_TIMER2_OFFSET)
HI_SET_GET(hi_hi6551_off_timer3_off_timer3,off_timer3,HI6551_OFF_TIMER3_T,HI6551_BASE_ADDR, HI6551_OFF_TIMER3_OFFSET)
HI_SET_GET(hi_hi6551_cl_int0_cl_int0,cl_int0,HI6551_CL_INT0_T,HI6551_BASE_ADDR, HI6551_CL_INT0_OFFSET)
HI_SET_GET(hi_hi6551_cl_int1_cl_int1,cl_int1,HI6551_CL_INT1_T,HI6551_BASE_ADDR, HI6551_CL_INT1_OFFSET)
HI_SET_GET(hi_hi6551_cl_int2_cl_int2,cl_int2,HI6551_CL_INT2_T,HI6551_BASE_ADDR, HI6551_CL_INT2_OFFSET)
HI_SET_GET(hi_hi6551_cl_int3_cl_int3,cl_int3,HI6551_CL_INT3_T,HI6551_BASE_ADDR, HI6551_CL_INT3_OFFSET)
HI_SET_GET(hi_hi6551_v_int0_v_int0,v_int0,HI6551_V_INT0_T,HI6551_BASE_ADDR, HI6551_V_INT0_OFFSET)
HI_SET_GET(hi_hi6551_v_int1_v_int1,v_int1,HI6551_V_INT1_T,HI6551_BASE_ADDR, HI6551_V_INT1_OFFSET)
HI_SET_GET(hi_hi6551_offset_current0_offset_current0,offset_current0,HI6551_OFFSET_CURRENT0_T,HI6551_BASE_ADDR, HI6551_OFFSET_CURRENT0_OFFSET)
HI_SET_GET(hi_hi6551_offset_current1_offset_current1,offset_current1,HI6551_OFFSET_CURRENT1_T,HI6551_BASE_ADDR, HI6551_OFFSET_CURRENT1_OFFSET)
HI_SET_GET(hi_hi6551_offset_voltage0_offset_voltage0,offset_voltage0,HI6551_OFFSET_VOLTAGE0_T,HI6551_BASE_ADDR, HI6551_OFFSET_VOLTAGE0_OFFSET)
HI_SET_GET(hi_hi6551_offset_voltage1_offset_voltage1,offset_voltage1,HI6551_OFFSET_VOLTAGE1_T,HI6551_BASE_ADDR, HI6551_OFFSET_VOLTAGE1_OFFSET)
HI_SET_GET(hi_hi6551_ocv_data1_ocv_data0,ocv_data0,HI6551_OCV_DATA1_T,HI6551_BASE_ADDR, HI6551_OCV_DATA1_OFFSET)
HI_SET_GET(hi_hi6551_ocv_data2_ocv_data1,ocv_data1,HI6551_OCV_DATA2_T,HI6551_BASE_ADDR, HI6551_OCV_DATA2_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre0_v_out0_pre0,v_out0_pre0,HI6551_V_OUT0_PRE0_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE0_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre0_v_out1_pre0,v_out1_pre0,HI6551_V_OUT1_PRE0_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE0_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre1_v_out0_pre1,v_out0_pre1,HI6551_V_OUT0_PRE1_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE1_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre1_v_out1_pre1,v_out1_pre1,HI6551_V_OUT1_PRE1_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE1_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre2_v_out0_pre2,v_out0_pre2,HI6551_V_OUT0_PRE2_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE2_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre2_v_out1_pre2,v_out1_pre2,HI6551_V_OUT1_PRE2_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE2_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre3_v_out0_pre3,v_out0_pre3,HI6551_V_OUT0_PRE3_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE3_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre3_v_out1_pre3,v_out1_pre3,HI6551_V_OUT1_PRE3_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE3_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre4_v_out0_pre4,v_out0_pre4,HI6551_V_OUT0_PRE4_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE4_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre4_v_out1_pre4,v_out1_pre4,HI6551_V_OUT1_PRE4_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE4_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre5_v_out0_pre5,v_out0_pre5,HI6551_V_OUT0_PRE5_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE5_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre5_v_out1_pre5,v_out1_pre5,HI6551_V_OUT1_PRE5_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE5_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre6_v_out0_pre6,v_out0_pre6,HI6551_V_OUT0_PRE6_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE6_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre6_v_out1_pre6,v_out1_pre6,HI6551_V_OUT1_PRE6_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE6_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre7_v_out0_pre7,v_out0_pre7,HI6551_V_OUT0_PRE7_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE7_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre7_v_out1_pre7,v_out1_pre7,HI6551_V_OUT1_PRE7_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE7_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre8_v_out0_pre8,v_out0_pre8,HI6551_V_OUT0_PRE8_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE8_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre8_v_out1_pre8,v_out1_pre8,HI6551_V_OUT1_PRE8_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE8_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre9_v_out0_pre9,v_out0_pre9,HI6551_V_OUT0_PRE9_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE9_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre9_v_out1_pre9,v_out1_pre9,HI6551_V_OUT1_PRE9_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE9_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre10_v_out0_pre10,v_out0_pre10,HI6551_V_OUT0_PRE10_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE10_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre10_v_out1_pre10,v_out1_pre10,HI6551_V_OUT1_PRE10_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE10_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre11_v_out0_pre11,v_out0_pre11,HI6551_V_OUT0_PRE11_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE11_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre11_v_out1_pre11,v_out1_pre11,HI6551_V_OUT1_PRE11_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE11_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre12_v_out0_pre12,v_out0_pre12,HI6551_V_OUT0_PRE12_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE12_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre12_v_out1_pre12,v_out1_pre12,HI6551_V_OUT1_PRE12_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE12_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre13_v_out0_pre13,v_out0_pre13,HI6551_V_OUT0_PRE13_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE13_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre13_v_out1_pre13,v_out1_pre13,HI6551_V_OUT1_PRE13_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE13_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre14_v_out0_pre14,v_out0_pre14,HI6551_V_OUT0_PRE14_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE14_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre14_v_out1_pre14,v_out1_pre14,HI6551_V_OUT1_PRE14_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE14_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre15_v_out0_pre15,v_out0_pre15,HI6551_V_OUT0_PRE15_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE15_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre15_v_out1_pre15,v_out1_pre15,HI6551_V_OUT1_PRE15_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE15_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre16_v_out0_pre16,v_out0_pre16,HI6551_V_OUT0_PRE16_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE16_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre16_v_out1_pre16,v_out1_pre16,HI6551_V_OUT1_PRE16_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE16_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre17_v_out0_pre17,v_out0_pre17,HI6551_V_OUT0_PRE17_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE17_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre17_v_out1_pre17,v_out1_pre17,HI6551_V_OUT1_PRE17_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE17_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre18_v_out0_pre18,v_out0_pre18,HI6551_V_OUT0_PRE18_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE18_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre18_v_out1_pre18,v_out1_pre18,HI6551_V_OUT1_PRE18_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE18_OFFSET)
HI_SET_GET(hi_hi6551_v_out0_pre19_v_out0_pre19,v_out0_pre19,HI6551_V_OUT0_PRE19_T,HI6551_BASE_ADDR, HI6551_V_OUT0_PRE19_OFFSET)
HI_SET_GET(hi_hi6551_v_out1_pre19_v_out1_pre19,v_out1_pre19,HI6551_V_OUT1_PRE19_T,HI6551_BASE_ADDR, HI6551_V_OUT1_PRE19_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre0_current0_pre0,current0_pre0,HI6551_CURRENT0_PRE0_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE0_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre0_current1_pre0,current1_pre0,HI6551_CURRENT1_PRE0_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE0_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre1_current0_pre1,current0_pre1,HI6551_CURRENT0_PRE1_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE1_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre1_current1_pre1,current1_pre1,HI6551_CURRENT1_PRE1_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE1_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre2_current0_pre2,current0_pre2,HI6551_CURRENT0_PRE2_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE2_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre2_current1_pre2,current1_pre2,HI6551_CURRENT1_PRE2_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE2_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre3_current0_pre3,current0_pre3,HI6551_CURRENT0_PRE3_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE3_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre3_current1_pre3,current1_pre3,HI6551_CURRENT1_PRE3_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE3_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre4_current0_pre4,current0_pre4,HI6551_CURRENT0_PRE4_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE4_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre4_current1_pre4,current1_pre4,HI6551_CURRENT1_PRE4_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE4_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre5_current0_pre5,current0_pre5,HI6551_CURRENT0_PRE5_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE5_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre5_current1_pre5,current1_pre5,HI6551_CURRENT1_PRE5_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE5_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre6_current0_pre6,current0_pre6,HI6551_CURRENT0_PRE6_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE6_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre6_current1_pre6,current1_pre6,HI6551_CURRENT1_PRE6_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE6_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre7_current0_pre7,current0_pre7,HI6551_CURRENT0_PRE7_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE7_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre7_current1_pre7,current1_pre7,HI6551_CURRENT1_PRE7_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE7_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre8_current0_pre8,current0_pre8,HI6551_CURRENT0_PRE8_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE8_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre8_current1_pre8,current1_pre8,HI6551_CURRENT1_PRE8_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE8_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre9_current0_pre9,current0_pre9,HI6551_CURRENT0_PRE9_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE9_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre9_current1_pre9,current1_pre9,HI6551_CURRENT1_PRE9_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE9_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre10_current0_pre10,current0_pre10,HI6551_CURRENT0_PRE10_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE10_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre10_current1_pre10,current1_pre10,HI6551_CURRENT1_PRE10_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE10_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre11_current0_pre11,current0_pre11,HI6551_CURRENT0_PRE11_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE11_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre11_current1_pre11,current1_pre11,HI6551_CURRENT1_PRE11_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE11_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre12_current0_pre12,current0_pre12,HI6551_CURRENT0_PRE12_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE12_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre12_current1_pre12,current1_pre12,HI6551_CURRENT1_PRE12_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE12_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre13_current0_pre13,current0_pre13,HI6551_CURRENT0_PRE13_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE13_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre13_current1_pre13,current1_pre13,HI6551_CURRENT1_PRE13_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE13_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre14_current0_pre14,current0_pre14,HI6551_CURRENT0_PRE14_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE14_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre14_current1_pre14,current1_pre14,HI6551_CURRENT1_PRE14_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE14_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre15_current0_pre15,current0_pre15,HI6551_CURRENT0_PRE15_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE15_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre15_current1_pre15,current1_pre15,HI6551_CURRENT1_PRE15_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE15_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre16_current0_pre16,current0_pre16,HI6551_CURRENT0_PRE16_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE16_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre16_current1_pre16,current1_pre16,HI6551_CURRENT1_PRE16_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE16_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre17_current0_pre17,current0_pre17,HI6551_CURRENT0_PRE17_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE17_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre17_current1_pre17,current1_pre17,HI6551_CURRENT1_PRE17_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE17_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre18_current0_pre18,current0_pre18,HI6551_CURRENT0_PRE18_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE18_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre18_current1_pre18,current1_pre18,HI6551_CURRENT1_PRE18_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE18_OFFSET)
HI_SET_GET(hi_hi6551_current0_pre19_current0_pre19,current0_pre19,HI6551_CURRENT0_PRE19_T,HI6551_BASE_ADDR, HI6551_CURRENT0_PRE19_OFFSET)
HI_SET_GET(hi_hi6551_current1_pre19_current1_pre19,current1_pre19,HI6551_CURRENT1_PRE19_T,HI6551_BASE_ADDR, HI6551_CURRENT1_PRE19_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cic_clk_inv_i,cic_clk_inv_i,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cic_clk_inv_v,cic_clk_inv_v,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_adc_ana_v_output,adc_ana_v_output,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_adc_ana_i_output,adc_ana_i_output,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cali_en_i,cali_en_i,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cali_en_i_force,cali_en_i_force,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cali_en_v_force,cali_en_v_force,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_clj_debug_cali_en_v,cali_en_v,HI6551_CLJ_DEBUG_T,HI6551_BASE_ADDR, HI6551_CLJ_DEBUG_OFFSET)
HI_SET_GET(hi_hi6551_state_test_state_test,state_test,HI6551_STATE_TEST_T,HI6551_BASE_ADDR, HI6551_STATE_TEST_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved1_reg_data_clr,reg_data_clr,HI6551_CLJ_RESERVED1_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED1_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved1_clj_rw_inf1,clj_rw_inf1,HI6551_CLJ_RESERVED1_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED1_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved2_clj_rw_inf2,clj_rw_inf2,HI6551_CLJ_RESERVED2_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED2_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved3_clj_rw_inf3,clj_rw_inf3,HI6551_CLJ_RESERVED3_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED3_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved4_clj_rw_inf4,clj_rw_inf4,HI6551_CLJ_RESERVED4_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED4_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved5_i_reserve_1,i_reserve_1,HI6551_CLJ_RESERVED5_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED5_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved6_i_reserve_2,i_reserve_2,HI6551_CLJ_RESERVED6_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED6_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved7_v_reserve_1,v_reserve_1,HI6551_CLJ_RESERVED7_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED7_OFFSET)
HI_SET_GET(hi_hi6551_clj_reserved8_v_reserve_2,v_reserve_2,HI6551_CLJ_RESERVED8_T,HI6551_BASE_ADDR, HI6551_CLJ_RESERVED8_OFFSET)
#endif
