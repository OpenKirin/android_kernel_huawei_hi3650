/*************************************************************************
*   ��Ȩ����(C) 1987-2004, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  MemoryLayout.h
*
*   ��    �� :  liumengcun
*
*   ��    �� :  ���������ڴ����
*
*   �޸ļ�¼ :  2011��12��20��  v1.00  liumengcun  ����
*
*************************************************************************/
#ifndef __MEMMORY_LAYOUT_H__
#define __MEMMORY_LAYOUT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "product_config.h"

#include "bsp_shared_ddr.h"
#include "bsp_sram.h"
#include "bsp_memmap.h"
#if 0
/* ���ַת������ */
#define IO_ADDRESS(x)         ((((x) & 0xF0000000) >> 4) | ((x) & 0x00FFFFFF) | 0xF0000000)

#if (defined(BOARD_ASIC) && defined(VERSION_V3R2))


#elif (defined (BOARD_FPGA) && defined(VERSION_V3R2))
/*monan for v9r1bbit*/
/* ����DDR�ڴ� */
#define GLOBAL_MEM_BASE_ADDR                   (0xC0000000)
#define GLOBAL_MEM_SIZE                        (0x10000000)           /*128MB*2*/
#define GLOBAL_MEM_BASE_ADDR_VIRT              (0xFC000000)

/*                      DDR ����ͼ

               +---------------------+---------+ --> 0xC0000000
               | A���ڴ�             | 32M     |
               +---------------------+---------+ --> 0xC2000000
               | C���ڴ�             | 48M     |
               +---------------------+---------+ --> 0xC5000000        ���ַͳһ��0xFC000000��ʼ
               | GUPSԤ���ڴ�        | 26M+672KB|
               +---------------------+---------+ --> 0xC6AA8000
               | �쳣��¼            | 512K    |
               +---------------------+---------+ --> 0xC6BA8000
               | �����ڴ�            | 640K    |
               +---------------------+---------+ --> 0xC6FA8000
               | HIFI�ڴ�(Ԥ��)      | 11M+352KB|
               +---------------------+---------+ --> 0xC7B00000
               | GUPSԤ���ڴ�        | 5M      |
               +---------------------+---------+ --> 0xc8000000
*/
/* ACOREʹ���ڴ� */
#define GLOBAL_MEM_ACORE_BASE_ADDR             (GLOBAL_MEM_BASE_ADDR)       /*0x30000000*/
#define GLOBAL_MEM_ACORE_SIZE                  (0x02000000)  /*32MB*/


/* MCOREʹ���ڴ� */
#define GLOBAL_MEM_MCORE_BASE_ADDR             (GLOBAL_MEM_ACORE_BASE_ADDR + GLOBAL_MEM_ACORE_SIZE)
#define GLOBAL_MEM_MCORE_SIZE                  (0x03200000)  /*48MB+2MB GUL��֧��ʱ�޸�*/

/* ��GUԤ�����ڴ� */
#define GLOBAL_MEM_GU_RESERVED_ADDR            (GLOBAL_MEM_MCORE_BASE_ADDR + GLOBAL_MEM_MCORE_SIZE)
#define GLOBAL_MEM_GU_RESERVED_ADDR_VIRT       (GLOBAL_MEM_BASE_ADDR_VIRT)
#define GLOBAL_MEM_GU_RESERVED_SIZE            (0x018A8000)  /*26.672MB-2MB GUL��֧��ʱ�޸�*/


/* �쳣��¼�ڴ� */
#define GLOBAL_MEM_EXCP_BASE_ADDR              (GLOBAL_MEM_GU_RESERVED_ADDR + GLOBAL_MEM_GU_RESERVED_SIZE)
#define GLOBAL_MEM_EXCP_BASE_ADDR_VIRT         (GLOBAL_MEM_GU_RESERVED_ADDR_VIRT + GLOBAL_MEM_GU_RESERVED_SIZE)
#define GLOBAL_MEM_EXCP_SIZE                   (0x00100000)

/* �˼乲���ڴ� */
#define GLOBAL_MEM_CORE_SHARE_ADDR             (GLOBAL_MEM_EXCP_BASE_ADDR + GLOBAL_MEM_EXCP_SIZE)
#define GLOBAL_MEM_CORE_SHARE_ADDR_VIRT        (GLOBAL_MEM_EXCP_BASE_ADDR_VIRT + GLOBAL_MEM_EXCP_SIZE)
#define GLOBAL_MEM_CORE_SHARE_SIZE             (0x00400000)


/* HIFI�ڴ� */
#define GLOBAL_MEM_HIFI_BASE_ADDR              (GLOBAL_MEM_CORE_SHARE_ADDR + GLOBAL_MEM_CORE_SHARE_SIZE)            /*0x33F38000*/
#define GLOBAL_MEM_HIFI_SIZE                   (0xB58000)/*(0x000C8000)
 */


/* ��LģԤ�����ڴ� */
#define GLOBAL_MEM_L_RESERVED_ADDR            (GLOBAL_MEM_HIFI_BASE_ADDR + GLOBAL_MEM_HIFI_SIZE)
#define GLOBAL_MEM_L_RESERVED_ADDR_VIRT       (GLOBAL_MEM_BASE_ADDR_VIRT + GLOBAL_MEM_GU_RESERVED_SIZE)
#define GLOBAL_MEM_L_RESERVED_SIZE            (0x00500000)


/*vxworks�ߵ͵�ַ����*/
#define VXWORKS_HIGH_ADDR                      (GLOBAL_MEM_MCORE_BASE_ADDR + GLOBAL_MEM_MCORE_SIZE - 6*4096)  /*Ԥ��24K��DMR*/
#define VXWORKS_LOW_ADDR                       (GLOBAL_MEM_MCORE_BASE_ADDR + 0x4000)


/*Android boot.img ��ʼ��������ַ����*/
#define LINUX_ADDR_TAGS                        (GLOBAL_MEM_ACORE_BASE_ADDR + 0x100)
#define LINUX_PHYS_OFFSET                      (GLOBAL_MEM_ACORE_BASE_ADDR)


/* ����AXI�ڴ� */
#define GLOBAL_AXI_MEM_BASE_ADDR_PHY           (0x30000000)
#define GLOBAL_AXI_MEM_SIZE                    (0x00020000)

#define GLOBAL_AXI_MEM_BASE_ADDR_VIRT          (IO_ADDRESS(GLOBAL_AXI_MEM_BASE_ADDR_PHY))


#ifdef BSP_CORE_MODEM
#define GLOBAL_AXI_MEM_BASE_ADDR               (GLOBAL_AXI_MEM_BASE_ADDR_PHY)
#else
#ifdef __FASTBOOT__
#define GLOBAL_AXI_MEM_BASE_ADDR               (GLOBAL_AXI_MEM_BASE_ADDR_PHY)
#else
#define GLOBAL_AXI_MEM_BASE_ADDR               (GLOBAL_AXI_MEM_BASE_ADDR_VIRT)
#endif

#define AXI_MEM_BASE_ADDR                      (GLOBAL_AXI_MEM_BASE_ADDR_PHY)
#define AXI_MEM_ADDR                           (GLOBAL_AXI_MEM_BASE_ADDR)
#define AXI_MEM_SIZE                           (GLOBAL_AXI_MEM_SIZE)
#endif

/*                      AXI Memory ����ͼ

               +---------------------+---------+ --> 0x2FFE0000
               | A�˵͹���           | 16KB    |
               +---------------------+---------+ --> 0x2FFE4000
               | FLASH��Դ��         | 32B     |
               +---------------------+---------+ --> 0x2FFE4020
               | IFC��ʶ             | 32B     |
               +---------------------+---------+ --> 0x2FFE4040
	           | ICC��ʶ             | 1K      |
	           +---------------------+---------+ --> 0x2FFE4440
	           | �ڴ����            | 1K      |
               +---------------------+---------+ --> 0x2FFE4840
               | ��̬�ڴ���          |73K-256B|
               +---------------------+---------+ --> 0x2FFF6B40
               | IPF������           | 30K     |
               +---------------------+---------+ --> 0x2FFFE340
               | �±���              | 128B    |
               +---------------------+---------+ --> 0x2FFFE3C0
               | ���ػ�              | 32B     |
               +---------------------+---------+ --> 0x2FFFE3E0
               | DICC��ʶ            | 32B     |
               +---------------------+---------+ --> 0x2FFFE400
               | HIFI������          | 6K      |
               +---------------------+---------+ --> 0x2FFFFC00
               | ������              | 1K-256B |
               +---------------------+---------+ --> 0x2FFFFF00
               | ������ʶ            | 256B    |
               +---------------------+---------+ --> 0x30000000
*/
/*FastBoot*/
#define MEMORY_AXI_FASTBOOT_START_ADDR        (GLOBAL_AXI_MEM_BASE_ADDR)
#define MEMORY_AXI_FASTBOOT_START_SIZE        (0x08)

/* ���ػ� */
#define MEMORY_AXI_ONOFF_ADDR               (MEMORY_AXI_FASTBOOT_START_ADDR + MEMORY_AXI_FASTBOOT_START_SIZE)
#define MEMORY_AXI_ONOFF_SIZE               (32)

/* DICC��ʶ */
#define MEMORY_AXI_DICC_ADDR                (MEMORY_AXI_ONOFF_ADDR + MEMORY_AXI_ONOFF_SIZE)
#define MEMORY_AXI_DICC_SIZE                (32)

/* �±��� */
#define GLOBAL_AXI_TEMP_PROTECT_ADDR        (MEMORY_AXI_DICC_ADDR + MEMORY_AXI_DICC_SIZE)
#define GLOBAL_AXI_TEMP_PROTECT_SIZE        (128)

/* USB�β� */
#define MEMORY_AXI_USB_INOUT_ADDR           (GLOBAL_AXI_TEMP_PROTECT_ADDR + GLOBAL_AXI_TEMP_PROTECT_SIZE)
#define MEMORY_AXI_USB_INOUT_SIZE           (4)

/*CSHELL*/
#define MEMORY_AXI_USB_CSHELL_ADDR         (MEMORY_AXI_USB_INOUT_ADDR + MEMORY_AXI_USB_INOUT_SIZE)
#define MEMORY_AXI_USB_CSHELL_SIZE         (4)

/* ��������A/C shell���л� */
#define MEMORY_AXI_UART_INOUT_ADDR          (MEMORY_AXI_USB_CSHELL_ADDR + MEMORY_AXI_USB_CSHELL_SIZE)
#define MEMORY_AXI_UART_INOUT_SIZE          (4)

/* ���־������С��ȥ��8����Ϊ���ĵط������˱�� */
#define MEMORY_AXI_SOFT_FLAG_ADDR           (MEMORY_AXI_UART_INOUT_ADDR + MEMORY_AXI_UART_INOUT_SIZE)
#define MEMORY_AXI_SOFT_FLAG_SIZE           (1024 - (MEMORY_AXI_SOFT_FLAG_ADDR - GLOBAL_AXI_MEM_BASE_ADDR) - 8)

/* A�˵͹��� */
#define MEMORY_AXI_ACPU_DEEPSLEEP_ADDR      (GLOBAL_AXI_MEM_BASE_ADDR + 1024)
#define MEMORY_AXI_ACPU_DEEPSLEEP_SIZE      (0x3000)

/* ICC��ʶ */
#define MEMORY_AXI_ICC_ADDR                 (MEMORY_AXI_ACPU_DEEPSLEEP_ADDR + MEMORY_AXI_ACPU_DEEPSLEEP_SIZE)
#define MEMORY_AXI_ICC_SIZE                 (1024)

/* �ڴ���� */
#define MEMORY_AXI_MEMMGR_FLAG_ADDR         (MEMORY_AXI_ICC_ADDR + MEMORY_AXI_ICC_SIZE)
#define MEMORY_AXI_MEMMGR_FLAG_SIZE         (1024)

/* ��̬�ڴ��� */
#define MEMORY_AXI_DYNAMIC_SEC_ADDR         (MEMORY_AXI_MEMMGR_FLAG_ADDR + MEMORY_AXI_MEMMGR_FLAG_SIZE)
#define MEMORY_AXI_DYNAMIC_SEC_SIZE         (48*1024 - (MEMORY_AXI_DYNAMIC_SEC_ADDR - GLOBAL_AXI_MEM_BASE_ADDR))

/* FLASH��Դ�� */
#define MEMORY_AXI_FLASH_SEM_ADDR           (MEMORY_AXI_DYNAMIC_SEC_ADDR + MEMORY_AXI_DYNAMIC_SEC_SIZE)
#define MEMORY_AXI_FLASH_SEM_SIZE           (4)

/* IFC��ʶ */
#define MEMORY_AXI_IFC_ADDR                 (MEMORY_AXI_FLASH_SEM_ADDR + MEMORY_AXI_FLASH_SEM_SIZE)
#define MEMORY_AXI_IFC_SIZE                 (32)

/* HIFI������ */
#define MEMORY_AXI_HIFI_ADDR                (MEMORY_AXI_IFC_ADDR + MEMORY_AXI_IFC_SIZE)
#define MEMORY_AXI_HIFI_SIZE                (6*1024)

/* ���� */
#define MEMORY_AXI_RESERVE_ADDR             (MEMORY_AXI_HIFI_ADDR + MEMORY_AXI_HIFI_SIZE)
#define MEMORY_AXI_RESERVE_SIZE             (GLOBAL_AXI_MEM_SIZE - (MEMORY_AXI_RESERVE_ADDR - GLOBAL_AXI_MEM_BASE_ADDR) - \
                                            MEMORY_AXI_PTABLE_SIZE - MEMORY_AXI_FLAG_BAK_SIZE - \
                                            MEMORY_AXI_DLOAD_SIZE - MEMORY_AXI_DLOAD_AUTOINSTALL_SIZE)/*monan for v9r1bbit
 */

/* ��λ��Ǳ����� */
#define MEMORY_AXI_FLAG_BAK_ADDR             (MEMORY_AXI_RESERVE_ADDR + MEMORY_AXI_RESERVE_SIZE)
#define MEMORY_AXI_FLAG_BAK_SIZE             (1024)

/* ������ʶ *//*monan for v9r1bbit ��Ϊp500 A��������������sram������sram�������������ܣ� �ƶ���sram�󲿷�*/
#define MEMORY_AXI_DLOAD_ADDR               (MEMORY_AXI_FLAG_BAK_ADDR + MEMORY_AXI_FLAG_BAK_SIZE)
#define MEMORY_AXI_DLOAD_SIZE               (256-48)

#define MEMORY_AXI_DLOAD_AUTOINSTALL_ADDR   (MEMORY_AXI_DLOAD_ADDR + MEMORY_AXI_DLOAD_SIZE)
#define MEMORY_AXI_DLOAD_AUTOINSTALL_SIZE   (48)

/* Flash������ */
#define MEMORY_AXI_PTABLE_ADDR              (MEMORY_AXI_DLOAD_AUTOINSTALL_ADDR + MEMORY_AXI_DLOAD_AUTOINSTALL_SIZE)
#define MEMORY_AXI_PTABLE_SIZE              (2*1024)

#define MEMORY_AXI_END_ADDR               (MEMORY_AXI_PTABLE_ADDR + MEMORY_AXI_PTABLE_SIZE)


#define MEMORY_AXI_NEED_TO_SAVE_BEFORE_RESET   4
#define MEMORY_AXI_VX_BACK_UP_FLAG1 0x12121212
#define MEMORY_AXI_VX_BACK_UP_FLAG2 0x21212121

#define MEMORY_AXI_BOOTROM_BACK_UP_FLAG1 0x34343434
#define MEMORY_AXI_BOOTROM_BACK_UP_FLAG2 0x43434343


/*Memory size check*/
#if (MEMORY_AXI_END_ADDR > (GLOBAL_AXI_MEM_BASE_ADDR + GLOBAL_AXI_MEM_SIZE))
#error AXI(MEMORY_AXI_END_ADDR) USED beyond the mark (GLOBAL_AXI_MEM_BASE_ADDR + GLOBAL_AXI_MEM_SIZE)
#endif


#endif
/*Memory size check*/
#if (MEMORY_AXI_END_ADDR > (GLOBAL_AXI_MEM_BASE_ADDR + GLOBAL_AXI_MEM_SIZE))
#error AXI(MEMORY_AXI_END_ADDR) USED beyond the mark (GLOBAL_AXI_MEM_BASE_ADDR + GLOBAL_AXI_MEM_SIZE)
#endif

/*-------------------------------------------------------------------------------
                            ˫�˹����ڴ�
  -------------------------------------------------------------------------------
                         -----------------------
                         |  SYNC(0x60)                  |
                         -----------------------
                         |  MEM spinlock(0x20)       |
                         -----------------------
                         |  ICC(0x80)                    |
                         -----------------------
                         | TENCILICA_TEXT(0)       |
                         -----------------------
                         |  WAN0x8000)                 |
                         -----------------------
                         |  MEM MGR M                  |
                         -----------------------
-------------------------------------------------------------------------------*/
/* �Ӷ����·��䣬���µ�ַ�ʹ�С���ɸı� */
#define MEMORY_RAM_CORESHARE_SIZE                   (GLOBAL_MEM_CORE_SHARE_SIZE)

#define MEMORY_RAM_CORESHARE_SYNC_RESV              (96)
#define MEMORY_RAM_CORESHARE_MEM_RESV               (32)
#define MEMORY_RAM_CORESHARE_ICC_RESV               (128)
/* ��bandԤ���ڴ�,װ��CT BTʹ��*/
#define CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE  (0x8000)

#define MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV    (0)
#define MEMORY_RAM_CORESHARE_MEM_WAN_SIZE           (0x8000)
#if (defined(BOARD_ASIC) && defined(VERSION_V3R2) && (defined(CHIP_BB_6756CS)))||(defined(BOARD_FPGA) && defined(VERSION_V3R2)) /*monan for v9r1bbit
 */
#define MEMORY_RAM_CORESHARE_MEM_IPF_SIZE            (30*1024)
#define MEMORY_RAM_CORESHARE_MEMMGR_SIZE            (MEMORY_RAM_CORESHARE_SIZE \
                                                    - MEMORY_RAM_CORESHARE_ICC_RESV \
                                                    - CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE\
                                                    - MEMORY_RAM_CORESHARE_MEM_RESV \
                                                    - MEMORY_RAM_CORESHARE_SYNC_RESV \
                                                    - MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV\
                                                    - MEMORY_RAM_CORESHARE_MEM_WAN_SIZE\
                                                    - MEMORY_RAM_CORESHARE_MEM_IPF_SIZE)
#else
#define MEMORY_RAM_CORESHARE_MEMMGR_SIZE            (MEMORY_RAM_CORESHARE_SIZE \
                                                    - MEMORY_RAM_CORESHARE_ICC_RESV \
                                                    - CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE\
                                                    - MEMORY_RAM_CORESHARE_MEM_RESV \
                                                    - MEMORY_RAM_CORESHARE_SYNC_RESV \
                                                    - MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV\
                                                    - MEMORY_RAM_CORESHARE_MEM_WAN_SIZE)
#endif

#ifdef BSP_CORE_MODEM
#define MEMORY_RAM_CORESHARE_ADDR                   (GLOBAL_MEM_CORE_SHARE_ADDR)
#else
#define MEMORY_RAM_CORESHARE_ADDR                   (GLOBAL_MEM_CORE_SHARE_ADDR_VIRT)
#endif
#define MEMORY_RAM_CORESHARE_MEMMGR_ADDR            (MEMORY_RAM_CORESHARE_ADDR)
#if (defined(BOARD_ASIC) && defined(VERSION_V3R2) && (defined(CHIP_BB_6756CS)))||(defined(BOARD_FPGA) && defined(VERSION_V3R2)) /*monan for v9r1bbit
 */


#define MEMORY_RAM_CORESHARE_IPF_ADDR               (MEMORY_RAM_CORESHARE_MEMMGR_ADDR + MEMORY_RAM_CORESHARE_MEMMGR_SIZE)
#define MEMORY_RAM_CORESHARE_MEM_WAN_ADDR           (MEMORY_RAM_CORESHARE_IPF_ADDR + MEMORY_RAM_CORESHARE_MEM_IPF_SIZE)
#else
#define MEMORY_RAM_CORESHARE_MEM_WAN_ADDR           (MEMORY_RAM_CORESHARE_MEMMGR_ADDR+MEMORY_RAM_CORESHARE_MEMMGR_SIZE)
#endif
#define MEMORY_RAM_CORESHARE_TENCILICA_TEXT_ADDR    (MEMORY_RAM_CORESHARE_MEM_WAN_ADDR+MEMORY_RAM_CORESHARE_MEM_WAN_SIZE)
#define MEMORY_RAM_CORESHARE_ICC_ADDR               (MEMORY_RAM_CORESHARE_TENCILICA_TEXT_ADDR+MEMORY_RAM_CORESHARE_TENCILICA_TEXT_RESV)
#define CORESHARE_MEM_TENCILICA_MULT_BAND_ADDR ((MEMORY_RAM_CORESHARE_ICC_ADDR) + (MEMORY_RAM_CORESHARE_ICC_RESV))
#define MEMORY_RAM_CORESHARE_MEM_ADDR               (CORESHARE_MEM_TENCILICA_MULT_BAND_ADDR + CORESHARE_MEM_TENCILICA_MULT_BAND_SIZE)
#define MEMORY_RAM_CORESHARE_SYNC_ADDR              (MEMORY_RAM_CORESHARE_MEM_ADDR + MEMORY_RAM_CORESHARE_MEM_RESV)

#if (defined(BOARD_ASIC) && defined(VERSION_V3R2) && (defined(CHIP_BB_6756CS)))\
    ||(defined(BOARD_FPGA) && defined(VERSION_V3R2)) /*monan for v9r1bbit
 */
#define MEMORY_AXI_IPF_ADDR MEMORY_RAM_CORESHARE_IPF_ADDR
#define MEMORY_AXI_IPF_SIZE MEMORY_RAM_CORESHARE_MEM_IPF_SIZE
#endif

/* ʹ�������ַ */
#define CORESHARE_MEM_WAN_ADDR                      (MEMORY_RAM_CORESHARE_MEM_WAN_ADDR - MEMORY_RAM_CORESHARE_ADDR + GLOBAL_MEM_CORE_SHARE_ADDR)
#define CORESHARE_MEM_WAN_SIZE                      (MEMORY_RAM_CORESHARE_MEM_WAN_SIZE)

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of __MEMMORY_LAYOUT_H__ */

