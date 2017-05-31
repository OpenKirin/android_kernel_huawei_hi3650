//****************************************************************************** 
// Copyright     :  Copyright (C) 2014, Hisilicon Technologies Co., Ltd.
// File name     :  asp_cfg_reg_offset.h
// Author        :  huangji
// Version       :  1.0 
// Date          :  2014-09-17
// Description   :  Define all registers/tables for hiaspv300
// Others        :  Generated automatically by nManager V4.0 
// History       :  huangji 2014-09-17 Create file
//******************************************************************************

#ifndef __ASP_CFG_REG_OFFSET_H__
#define __ASP_CFG_REG_OFFSET_H__

/* ASP_CFG Base address of Module's Register */
#define HI3650_ASP_CFG_BASE                       (0xe804e000)

/******************************************************************************/
/*                      hiaspv300 ASP_CFG Registers' Definitions                            */
/******************************************************************************/

#define HI3650_ASP_CFG_R_RST_CTRLEN_REG                         (0 + 0x0)   /* ������λʹ�ܼĴ��� */                    
#define HI3650_ASP_CFG_R_RST_CTRLDIS_REG                        (0 + 0x4)   /* ������λ����Ĵ��� */                    
#define HI3650_ASP_CFG_R_RST_CTRLSTAT_REG                       (0 + 0x8)   /* ������λ״̬�Ĵ��� */                    
#define HI3650_ASP_CFG_R_GATE_EN_REG                            (0 + 0xC)   /* ʱ��ʹ�ܼĴ��� */                       
#define HI3650_ASP_CFG_R_GATE_DIS_REG                           (0 + 0x10)  /* ʱ�ӽ�ֹ�Ĵ��� */                       
#define HI3650_ASP_CFG_R_GATE_CLKEN_REG                         (0 + 0x14)  /* ʱ��ʹ��״̬�Ĵ��� */                     
#define HI3650_ASP_CFG_R_GATE_CLKSTAT_REG                       (0 + 0x18)  /* ʱ������״̬�Ĵ��� */                     
#define HI3650_ASP_CFG_R_GATE_CLKDIV_EN_REG                     (0 + 0x1C)  /* ʱ�ӷ�Ƶ���ſ�ʹ�ܼĴ��� */                  
#define HI3650_ASP_CFG_R_CLK1_DIV_REG                           (0 + 0x20)  /* ��Ƶ�ȿ��ƼĴ���1 */                     
#define HI3650_ASP_CFG_R_CLK2_DIV_REG                           (0 + 0x24)  /* ��Ƶ�ȿ��ƼĴ���2 */                     
#define HI3650_ASP_CFG_R_CLK3_DIV_REG                           (0 + 0x28)  /* ��Ƶ�ȿ��ƼĴ���3 */                     
#define HI3650_ASP_CFG_R_CLK4_DIV_REG                           (0 + 0x2C)  /* ��Ƶ�ȿ��ƼĴ���4 */                     
#define HI3650_ASP_CFG_R_CLK5_DIV_REG                           (0 + 0x30)  /* ��Ƶ�ȿ��ƼĴ���5 */                     
#define HI3650_ASP_CFG_R_CLK6_DIV_REG                           (0 + 0x34)  /* ��Ƶ�ȿ��ƼĴ���6 */                     
#define HI3650_ASP_CFG_R_CLK_SEL_REG                            (0 + 0x38)  /* ʱ��ѡ��Ĵ��� */                       
#define HI3650_ASP_CFG_R_DSP_NMI_REG                            (0 + 0x3C)  /* DSP NMI�жϲ����Ĵ��� */                
#define HI3650_ASP_CFG_R_DSP_PRID_REG                           (0 + 0x40)  /* DSP PRID���üĴ��� */                 
#define HI3650_ASP_CFG_R_DSP_RUNSTALL_REG                       (0 + 0x44)  /* DSP RUNSTALL���üĴ��� */             
#define HI3650_ASP_CFG_R_DSP_STATVECTORSEL_REG                  (0 + 0x48)  /* DSP STATVECTORSEL���üĴ��� */        
#define HI3650_ASP_CFG_R_DSP_OCDHALTONRESET_REG                 (0 + 0x4C)  /* DSP OCDHALTONRESET���üĴ��� */       
#define HI3650_ASP_CFG_R_DSP_STATUS_REG                         (0 + 0x50)  /* DSP ״̬�Ĵ��� */                     
#define HI3650_ASP_CFG_R_DMAC_SEL_REG                           (0 + 0x54)  /* DMACͨ��ѡ��Ĵ��� */                   
#define HI3650_ASP_CFG_R_BUS_PRIORITY_REG                       (0 + 0x58)  /* �������ȼ����üĴ��� */                    
#define HI3650_ASP_CFG_R_CG_EN_REG                              (0 + 0x5C)  /* �Զ��ſ�ʹ�ܼĴ��� */                     
#define HI3650_ASP_CFG_R_OCRAM_RET_REG                          (0 + 0x60)  /* ocram�͹������üĴ��� */                 
#define HI3650_ASP_CFG_R_INTR_NS_INI_REG                        (0 + 0x64)  /* �ǰ�ȫ�ж�ԭʼ״̬�Ĵ��� */                  
#define HI3650_ASP_CFG_R_INTR_NS_EN_REG                         (0 + 0x68)  /* �ǰ�ȫ�ж�ʹ�ܼĴ��� */                    
#define HI3650_ASP_CFG_R_INTR_NS_MASK_REG                       (0 + 0x6C)  /* �ǰ�ȫ�ж����κ�״̬�Ĵ��� */                 
#define HI3650_ASP_CFG_R_DBG_SET_AHB2AXI_REG                    (0 + 0x70)  /* ��ǿ��DBG�ź����üĴ��� */                 
#define HI3650_ASP_CFG_R_DBG_STATUS_AHB2AXI_REG                 (0 + 0x74)  /* ��ǿ��DBG�ź�״̬�Ĵ��� */                 
#define HI3650_ASP_CFG_R_DLOCK_BP_REG                           (0 + 0x78)  /* ���߷�����bypass�Ĵ��� */                
#define HI3650_ASP_CFG_R_DSP_BINTERRUPT_REG                     (0 + 0x7C)  /* �ϱ���hifi dsp���ж��ź�ֻ���Ĵ��� */         
#define HI3650_ASP_CFG_R_DSP_RAM_RET_REG                        (0 + 0x84)  
#define HI3650_ASP_CFG_R_TZ_SECURE_N_REG                        (0 + 0x100) 
#define HI3650_ASP_CFG_R_OCRAM_R0SIZE_REG                       (0 + 0x104) 
#define HI3650_ASP_CFG_R_SIO_LOOP_SECURE_N_REG                  (0 + 0x108) 
#define HI3650_ASP_CFG_R_INTR_S_INI_REG                         (0 + 0x10C) /* ��ȫ�ж�ԭʼ״̬�Ĵ��� */                   
#define HI3650_ASP_CFG_R_INTR_S_EN_REG                          (0 + 0x110) /* ��ȫ�ж�ʹ�ܼĴ��� */                     
#define HI3650_ASP_CFG_R_INTR_S_MASK_REG                        (0 + 0x114) /* ��ȫ�ж����κ�״̬�Ĵ��� */                  
#define HI3650_ASP_CFG_R_DSP_REMAPPING_EN_REG                   (0 + 0x118) /* dsp��ַ��ӳ��ʹ�ܼĴ��� */                 
#define HI3650_ASP_CFG_R_DSP_REMAPPING_SRC_BASE_ADDR_REG        (0 + 0x11C) /* DSP ��ַ��ӳ��Ĵ��� */                  
#define HI3650_ASP_CFG_R_DSP_REMAPPING_DES_BASE_ADDR_REG        (0 + 0x120) /* DSP ��ַ��ӳ��Ĵ��� */                  
#define HI3650_ASP_CFG_R_DDR_HARQ_REMAP_EN_REG                  (0 + 0x124) /* DDR��Harq Memory remap���ƼĴ��� */    
#define HI3650_ASP_CFG_R_DDR_HARQ_REMAP_SRC_BASE_ADDR_REG       (0 + 0x128) /* DDR��Harq Memory remapԴ����ַ�Ĵ��� */  
#define HI3650_ASP_CFG_R_DDR_HARQ_REMAP_DES_BASE_ADDR_REG       (0 + 0x12C) /* DDR��Harq Memory remapĿ�����ַ�Ĵ��� */ 
#define HI3650_ASP_CFG_R_DDR_MMBUF_REMAP_EN_REG                 (0 + 0x130) /* DDR��MMBUF remap���ƼĴ��� */          
#define HI3650_ASP_CFG_R_DDR_MMBUF_REMAP_SRC_BASE_ADDR_REG      (0 + 0x134) /* DDR��MMBUF remapԴ����ַ�Ĵ��� */        
#define HI3650_ASP_CFG_R_DDR_MMBUF_REMAP_DES_BASE_ADDR_REG      (0 + 0x138) /* DDR��MMBUF remapĿ�����ַ�Ĵ��� */       
#define HI3650_ASP_CFG_R_DDR_OCRAM_REMAP_EN_REG                 (0 + 0x13C) /* DDR��OCRAM remap���ƼĴ��� */          
#define HI3650_ASP_CFG_R_DDR_OCRAM_REMAP_SRC_BASE_ADDR_REG      (0 + 0x140) /* DDR��OCRAM remapԴ����ַ�Ĵ��� */        
#define HI3650_ASP_CFG_R_DDR_OCRAM_REMAP_DES_BASE_ADDR_REG      (0 + 0x144) /* DDR��OCRAM remapĿ�����ַ�Ĵ��� */       
#define HI3650_ASP_CFG_R_MMBUF_CTRL_REG                         (0 + 0x148) /* MMBUF CTRL���üĴ��� */               
#define HI3650_ASP_CFG_R_HIFIDSP_CLK_DIV_AUTO_REG               (0 + 0x14C) /* HIFIDSPʱ��Ƶ���Զ���Ƶ���üĴ��� */          
#define HI3650_ASP_CFG_R_INTR_FREQ_OFFSET_CFG_REG               (0 + 0x150) /* Ƶƫ��¼ģ�����üĴ��� */                   
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR_EN_ADDR_REG        (0 + 0x160) /* �ڴ���ģ��ʹ�����üĴ��� */                 
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_CLR_ADDR_REG  (0 + 0x164) /* �ڴ���ģ���ж��������üĴ��� */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_EN_ADDR_REG   (0 + 0x168) /* �ڴ���ģ���ж�ʹ�����üĴ��� */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR_INTR_STAT_ADDR_REG (0 + 0x16C) /* �ڴ���ģ���ж�״̬�Ĵ��� */                 
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR0_BASE_ADDR_REG     (0 + 0x170) /* �ڴ���ģ��0����ַ���üĴ��� */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR0_LEN_ADDR_REG      (0 + 0x174) /* �ڴ���ģ��0��ַ�������üĴ��� */              
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_AWADDR_REG    (0 + 0x178) /* �ڴ���ģ��0Խ���д��ַ��¼�Ĵ��� */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR0_HIT_ARADDR_REG    (0 + 0x17C) /* �ڴ���ģ��0Խ��Ķ���ַ��¼�Ĵ��� */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR1_BASE_ADDR_REG     (0 + 0x180) /* �ڴ���ģ��1����ַ���üĴ��� */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR1_LEN_ADDR_REG      (0 + 0x184) /* �ڴ���ģ��1��ַ�������üĴ��� */              
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_AWADDR_REG    (0 + 0x188) /* �ڴ���ģ��1Խ���д��ַ��¼�Ĵ��� */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR1_HIT_ARADDR_REG    (0 + 0x18C) /* �ڴ���ģ��1Խ��Ķ���ַ��¼�Ĵ��� */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR2_BASE_ADDR_REG     (0 + 0x190) /* �ڴ���ģ��2����ַ���üĴ��� */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR2_LEN_ADDR_REG      (0 + 0x194) /* �ڴ���ģ��2��ַ�������üĴ��� */              
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_AWADDR_REG    (0 + 0x198) /* �ڴ���ģ��2Խ���д��ַ��¼�Ĵ��� */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR2_HIT_ARADDR_REG    (0 + 0x19C) /* �ڴ���ģ��2Խ��Ķ���ַ��¼�Ĵ��� */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR3_BASE_ADDR_REG     (0 + 0x1A0) /* �ڴ���ģ��3����ַ���üĴ��� */               
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR3_LEN_ADDR_REG      (0 + 0x1A4) /* �ڴ���ģ��3��ַ�������üĴ��� */              
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_AWADDR_REG    (0 + 0x1A8) /* �ڴ���ģ��3Խ���д��ַ��¼�Ĵ��� */            
#define HI3650_ASP_CFG_R_ACCESS_ADDR_MONITOR3_HIT_ARADDR_REG    (0 + 0x1AC) /* �ڴ���ģ��3Խ��Ķ���ַ��¼�Ĵ��� */            
#define HI3650_ASP_CFG_R_MEMORY_CTRL_REG                        (0 + 0x1B0) /* memory�������üĴ��� */                 
#define HI3650_ASP_CFG_R_SLIMBUS_PRIMARY_ADDR_REG               (0 + 0x1B4) /* slimbus primary���üĴ��� */          
#define HI3650_ASP_CFG_R_SLIMBUS_ID_ADDR_REG                    (0 + 0x1B8) /* slimbus id���üĴ��� */               
#define HI3650_ASP_CFG_R_SECURE_AUTHORITY_EN_REG                (0 + 0x200) /* ��ȫ�������Կ��ƼĴ��� */                   

#endif // __ASP_CFG_REG_OFFSET_H__
