/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_profiling.c
  �� �� ��   : ����
  ��    ��   : wangtd
  ��������   : 2015��3��4��
  ����޸�   :
  ��������   : ����ά��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��3��4��
    ��    ��   : Wlan_mib_temp
    �޸�����   : �����ļ�
  2.��    ��   : 2015��8��15��
    ��    ��   : sunxiaolin
    �޸�����   : ���thruput bypass TX����ά���
******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_profiling.h"
#include "oam_ext_if.h"




#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAL_PROFILING_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#ifdef _PRE_WLAN_PROFLING_SOC
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
OAL_VOLATILE oal_uint32 g_ul_b_tcm[1024];
#pragma arm section rodata, code, rwdata, zidata  // return to default placement

#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
OAL_VOLATILE oal_uint32 g_ul_a_tcm[1024];
#pragma arm section rodata, code, rwdata, zidata  // return to default placement

OAL_STATIC oal_uint32 g_ul_w_ram[1024];

OAL_STATIC PACKETMEM oal_uint32 g_ul_pkt_ram[1024];
#endif
#endif

#ifdef _PRE_WLAN_PROFLING_MIPS
/* ����tx profiling���Ե��������� */
oal_profiling_tx_statistic_stru g_mips_tx_statistic;
EXPORT_SYMBOL(g_mips_tx_statistic);
/* ����rx profiling���Ե��������� */
oal_profiling_rx_statistic_stru g_mips_rx_statistic;
EXPORT_SYMBOL(g_mips_rx_statistic);

#endif

oal_thruput_bypass_enum_uint8 g_auc_thruput_bypass_enable[OAL_THRUPUT_BYPASS_BUTT] = {0};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
#ifdef _PRE_WLAN_PROFLING_SOC
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
//#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
/*****************************************************************************
 �� �� ��  : oal_profiling_read16_single
 ��������  :
 �������  : oal_uint32 ul_addr_start
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_read16_single(oal_uint32 ul_addr_start)
{
    oal_uint16 us_val;
    oal_uint32 ul_cycles;

    enable_cycle_counter();
    us_val = OAL_REG_READ16(ul_addr_start);
    ul_cycles = get_cycle_count();
    disable_cycle_counter();

    OAL_IO_PRINT("Single Addr  : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("Read Value   : 0x%08x \n\r", us_val);
    OAL_IO_PRINT("Read Cycle   : %d cycles\n\r", ul_cycles);
}

/*****************************************************************************
 �� �� ��  : oal_profiling_read16_ex
 ��������  :
 �������  : oal_uint32 ul_addr_start
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��10��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_read16_ex(oal_uint32 ul_addr_start)
{
    oal_uint16 us_val;
    oal_uint32 ul_cycles;

    enable_cycle_counter();
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    us_val = OAL_REG_READ16(ul_addr_start);
    ul_cycles = get_cycle_count();
    disable_cycle_counter();

    OAL_IO_PRINT("Single Addr  : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("Read Value   : 0x%08x \n\r", us_val);
    OAL_IO_PRINT("Total Cycle  : %d cycles\n\r", ul_cycles);
    OAL_IO_PRINT("Read Cycle   : %d cycles\n\r", ul_cycles / 32);
}

/*****************************************************************************
 �� �� ��  : oal_profiling_write16_single
 ��������  :
 �������  : oal_uint32 ul_addr_start
             oal_uint16 us_val
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_write16_single(oal_uint32 ul_addr_start, oal_uint16 us_val)
{
    oal_uint32 ul_cycles;

    enable_cycle_counter();
    OAL_REG_WRITE16(ul_addr_start, us_val);
    ul_cycles = get_cycle_count();
    disable_cycle_counter();

    OAL_IO_PRINT("Single Addr : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("Write Value : 0x%08x \n\r", us_val);
    OAL_IO_PRINT("Write Cycle : %d cycles\n\r", ul_cycles);
}

/*****************************************************************************
 �� �� ��  : oal_profiling_write16_ex
 ��������  :
 �������  : oal_uint32 ul_addr_start
             oal_uint16 us_val
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��10��
    ��    ��   : Wlan_mib_temp
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_write16_ex(oal_uint32 ul_addr_start, oal_uint16 us_val)
{
    oal_uint32 ul_cycles;

    enable_cycle_counter();
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    OAL_REG_WRITE16(ul_addr_start, us_val);
    ul_cycles = get_cycle_count();
    disable_cycle_counter();

    OAL_IO_PRINT("Single Addr  : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("Write Value  : 0x%08x \n\r", us_val);
    OAL_IO_PRINT("Write Cycle  : %d cycles\n\r", ul_cycles / 32);
}


/*****************************************************************************
 �� �� ��  : oal_profiling_read32_single
 ��������  :
 �������  : oal_uint32 ul_addr_start
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_read32_single(oal_uint32 ul_addr_start)
{
    oal_uint32 ul_val;
    oal_uint32 ul_cycles;

    enable_cycle_counter();
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_cycles = get_cycle_count();
    disable_cycle_counter();

    OAL_IO_PRINT("Addr         : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("Read Value   : 0x%08x \n\r", ul_val);
    OAL_IO_PRINT("Read Cycle   : %d cycles\n\r", ul_cycles);
}

/*****************************************************************************
 �� �� ��  : oal_profiling_read32_ex
 ��������  :
 �������  : oal_uint32 ul_addr_start
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��10��
    ��    ��   : Wlan_mib_temp
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_read32_ex(oal_uint32 ul_addr_start)
{
    oal_uint32 ul_val;
    oal_uint32 ul_cycles;

    enable_cycle_counter();
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_val = OAL_REG_READ32(ul_addr_start);
    ul_cycles = get_cycle_count();
    disable_cycle_counter();

    OAL_IO_PRINT("Addr         : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("Read Value   : 0x%08x \n\r", ul_val);
    OAL_IO_PRINT("Read Cycle   : %d cycles\n\r", ul_cycles / 32);
}


/*****************************************************************************
 �� �� ��  : oal_profiling_write32_single
 ��������  :
 �������  : oal_uint32 ul_addr_start
             oal_uint32 ul_val
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_write32_single(oal_uint32 ul_addr_start, oal_uint32 ul_val)
{
    oal_uint32 ul_cycles;

    enable_cycle_counter();
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    ul_cycles = get_cycle_count();
    disable_cycle_counter();

    OAL_IO_PRINT("Addr        : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("Write Value : 0x%08x \n\r", ul_val);
    OAL_IO_PRINT("Write Cycle : %d cycles\n\r", ul_cycles);
}

/*****************************************************************************
 �� �� ��  : oal_profiling_write32_ex
 ��������  :
 �������  : oal_uint32 ul_addr_start
             oal_uint32 ul_val
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��10��
    ��    ��   : Wlan_mib_temp
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_write32_ex(oal_uint32 ul_addr_start, oal_uint32 ul_val)
{
    oal_uint32 ul_cycles;

    enable_cycle_counter();
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    OAL_REG_WRITE32(ul_addr_start, ul_val);
    ul_cycles = get_cycle_count();
    disable_cycle_counter();

    OAL_IO_PRINT("Addr        : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("Write Value : 0x%08x \n\r", ul_val);
    OAL_IO_PRINT("Write Cycle : %d cycles\n\r", ul_cycles / 32);
}

/*****************************************************************************
 �� �� ��  : oal_profiling_read32_many
 ��������  :
 �������  : oal_uint32 ul_addr_start
             oal_uint32 ul_addr_end
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_read32_many(oal_uint32 ul_addr_start, oal_uint32 ul_addr_end)
{
    oal_uint32 ul_addr = ul_addr_start;
    oal_uint32 ul_val;
    oal_uint32 ul_cycles;
    oal_uint32 ul_num;

    enable_cycle_counter();
    while (ul_addr <= ul_addr_end)
    {
        ul_val = OAL_REG_READ32(ul_addr);
        ul_addr += 4;
    }
    ul_cycles = get_cycle_count();
    disable_cycle_counter();
    ul_num = (ul_addr_end - ul_addr_start) / 4 + 1;

    OAL_IO_PRINT("Start Addr   : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("End Addr     : 0x%08x \n\r", ul_addr_end);
    OAL_IO_PRINT("32bits Nums  : %d \n\r", ul_num);
    OAL_IO_PRINT("Read Total   : %d cycles\n\r", ul_cycles);
    OAL_IO_PRINT("Read Average : %d cycles\n\r", ul_cycles / ul_num);
}

/*****************************************************************************
 �� �� ��  : oal_profiling_write32_many
 ��������  :
 �������  : oal_uint32 ul_addr_start
             oal_uint32 ul_addr_end
             oal_uint32 ul_val
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_write32_many(oal_uint32 ul_addr_start, oal_uint32 ul_addr_end, oal_uint32 ul_val)
{
    oal_uint32 ul_addr = ul_addr_start;
    oal_uint32 ul_cycles;
    oal_uint32 ul_num;

    enable_cycle_counter();
    while (ul_addr <= ul_addr_end)
    {
        OAL_REG_WRITE32(ul_addr, ul_val);
        ul_addr += 4;
    }
    ul_cycles = get_cycle_count();
    disable_cycle_counter();
    ul_num = (ul_addr_end - ul_addr_start) / 4 + 1;

    OAL_IO_PRINT("Start Addr   : 0x%08x \n\r", ul_addr_start);
    OAL_IO_PRINT("End Addr     : 0x%08x \n\r", ul_addr_end);
    OAL_IO_PRINT("32bits Nums  : %d \n\r", ul_num);
    OAL_IO_PRINT("Write Total  : %d cycles\n\r", ul_cycles);
    OAL_IO_PRINT("Write Average: %d cycles\n\r", ul_cycles / ul_num);
}
//#pragma arm section rodata, code, rwdata, zidata  // return to default placement



/*****************************************************************************
 �� �� ��  : oal_profiling_check_soc
 ��������  :
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_check_soc(oal_void)
{
    enable_caches();
    INT_DisableAll();

    OAL_IO_PRINT("\n\r*********************GLB_CTL********************\n\r");
    oal_profiling_write16_ex(0x50000010, 0x1234);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read16_ex(0x50000010);

    OAL_IO_PRINT("\n\r*********************W_CTL**********************\n\r");
    oal_profiling_write16_ex(0x20000010, 0x5678);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read16_ex(0x20000010);

    OAL_IO_PRINT("\n\r*********************COEX_CTL*******************\n\r");
    oal_profiling_write16_ex(0x50010010, 0x9ABC);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read16_ex(0x50010010);

    OAL_IO_PRINT("\n\r*********************SDIO***********************\n\r");
    OAL_IO_PRINT("FUNCTION 0:\n\r");
    oal_profiling_write32_ex(0x20201010, 0xBEEFBEEF);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x20201010);  //wrong
    OAL_IO_PRINT("\n\r");
    OAL_IO_PRINT("FUNCTION 1:\n\r");
    oal_profiling_write32_ex(0x2020112C, 0x12345678);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x2020112C);  //wrong

    OAL_IO_PRINT("\n\r*********************MAC************************\n\r");
//    HI1102_REG_WRITE16(HI1102_SOC_W_CTL_RB_WCBB_CLK_DIV_1_REG, 0x14);  //80MHz
//    HI1102_REG_WRITE16(HI1102_SOC_W_CTL_RB_WCBB_CLK_DIV_1_REG, 0x12);  //160MHz
    OAL_IO_PRINT("BANK0:\n\r");
    oal_profiling_write32_ex(0x20100018, 0x11111111);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x20100018);
    OAL_IO_PRINT("\n\r");
    OAL_IO_PRINT("BANK1:\n\r");
    oal_profiling_write32_ex(0x201002A8, 0x22222222);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x201002A8);
    OAL_IO_PRINT("\n\r");
    OAL_IO_PRINT("BANK2:\n\r");
    oal_profiling_write32_ex(0x20100414, 0x33333333);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x20100414);
    OAL_IO_PRINT("\n\r");
    OAL_IO_PRINT("BANK3:\n\r");
    oal_profiling_read32_ex(0x20100600);
    OAL_IO_PRINT("\n\r");
    OAL_IO_PRINT("BANK4:\n\r");
    oal_profiling_write32_ex(0x20100800, 0x44444444);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x20100800);

    OAL_IO_PRINT("\n\r*********************PHY************************\n\r");
    OAL_IO_PRINT("BANK0:\n\r");
    OAL_IO_PRINT("\n\r");
    OAL_IO_PRINT("BANK1:\n\r");
    oal_profiling_write32_ex(0x2012084C, 0x55555555);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x2012084C);
    OAL_IO_PRINT("\n\r");
    OAL_IO_PRINT("BANK2:\n\r");
    oal_profiling_write32_ex(0x20120E5C, 0x66666666);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x20120E5C);
    OAL_IO_PRINT("\n\r");
    OAL_IO_PRINT("BANK3:\n\r");
    oal_profiling_write32_ex(0x20121248, 0x77777777);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x20121248);
    OAL_IO_PRINT("\n\r");
    OAL_IO_PRINT("BANK4:\n\r");
    oal_profiling_write32_ex(0x20121498, 0x88888888);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x20121498);

    OAL_IO_PRINT("\n\r*********************BRAM***********************\n\r");
    oal_profiling_read32_ex(0x30000000);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x300E4000);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x301C0000);
    OAL_IO_PRINT("\n\r");
    oal_profiling_write32_ex(0x30178000, 0x99999999);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_ex(0x30178000);

    OAL_IO_PRINT("\n\r*********************BTCM***********************\n\r");
    oal_profiling_write32_single((oal_uint32)&(g_ul_b_tcm[0]), 0x87654321);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_single((oal_uint32)&(g_ul_b_tcm[0]));
    OAL_IO_PRINT("\n\r");
    oal_profiling_write32_many((oal_uint32)&(g_ul_b_tcm[0]), (oal_uint32)&(g_ul_b_tcm[1023]), 0x12345678);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_many((oal_uint32)&(g_ul_b_tcm[0]), (oal_uint32)&(g_ul_b_tcm[1023]));

    OAL_IO_PRINT("\n\r*********************ATCM***********************\n\r");
    oal_profiling_write32_single((oal_uint32)&(g_ul_a_tcm[0]), 0x87654321);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_single((oal_uint32)&(g_ul_a_tcm[0]));
    OAL_IO_PRINT("\n\r");
    oal_profiling_write32_many((oal_uint32)&(g_ul_a_tcm[0]), (oal_uint32)&(g_ul_a_tcm[1023]), 0x12345678);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_many((oal_uint32)&(g_ul_a_tcm[0]), (oal_uint32)&(g_ul_a_tcm[1023]));

    OAL_IO_PRINT("\n\r*********************WRAM***********************\n\r");
    oal_profiling_write32_single((oal_uint32)&(g_ul_w_ram[0]), 0x87654321);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_single((oal_uint32)&(g_ul_w_ram[0]));
    OAL_IO_PRINT("\n\r");
    oal_profiling_write32_many((oal_uint32)&(g_ul_w_ram[0]), (oal_uint32)&(g_ul_w_ram[1023]), 0x12345678);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_many((oal_uint32)&(g_ul_w_ram[0]), (oal_uint32)&(g_ul_w_ram[1023]));
    OAL_IO_PRINT("\n\r");
    oal_profiling_write32_single((oal_uint32)0x000E0000, 0x87654321);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_single((oal_uint32)0x000E0000);

    OAL_IO_PRINT("\n\r*********************PKT_RAM********************\n\r");
    oal_profiling_write32_single((oal_uint32)&(g_ul_pkt_ram[0]), 0x87654321);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_single((oal_uint32)&(g_ul_pkt_ram[0]));
    OAL_IO_PRINT("\n\r");
    oal_profiling_write32_many((oal_uint32)&(g_ul_pkt_ram[0]), (oal_uint32)&(g_ul_pkt_ram[1023]), 0x12345678);
    OAL_IO_PRINT("\n\r");
    oal_profiling_read32_many((oal_uint32)&(g_ul_pkt_ram[0]), (oal_uint32)&(g_ul_pkt_ram[1023]));

    INT_EnableAll();
}
#endif
#endif


#ifdef _PRE_WLAN_PROFLING_MIPS
/*****************************************************************************
 �� �� ��  : oal_profiling_enable_cycles
 ��������  : ��cyclesͳ�ƹ���
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
void oal_profiling_enable_cycles(oal_void)
{
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    enable_cycle_counter();
#else

#endif
}

/*****************************************************************************
 �� �� ��  : oal_profiling_get_cycles
 ��������  : ��ȡcyclesͳ��ֵ
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 oal_profiling_get_cycles(oal_void)
{
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    return get_cycle_count();
#else
    return 0;
#endif
}

/*****************************************************************************
 �� �� ��  : oal_profiling_disable_cycles
 ��������  : �ر�cyclesͳ�ƹ���
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
void oal_profiling_disable_cycles(oal_void)
{
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
    disable_cycle_counter();
#else

#endif
}

/*****************************************************************************
 �� �� ��  : oal_profiling_stop_rx_save
 ��������  : ֹͣ���շ����¼����ֹ���ݱ�����
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_stop_rx_save(oal_void)
{
    g_mips_rx_statistic.en_switch = OAL_SWITCH_OFF;
}
EXPORT_SYMBOL(oal_profiling_stop_rx_save);

/*****************************************************************************
 �� �� ��  : oal_profiling_stop_tx_save
 ��������  : ֹͣ���ͷ����¼����ֹ���ݱ�����
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��22��
    ��    ��   : y00196452
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_stop_tx_save(oal_void)
{
    g_mips_tx_statistic.en_switch = OAL_SWITCH_OFF;
}
EXPORT_SYMBOL(oal_profiling_stop_tx_save);

/*****************************************************************************
 �� �� ��  : oal_profiling_mips_tx_init
 ��������  : DMAC�ķ�������mipsͳ�Ƴ�ʼ��
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 oal_profiling_mips_tx_init(oal_void)
{
    OAL_MEMZERO(&g_mips_tx_statistic, OAL_SIZEOF(oal_profiling_tx_statistic_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oal_profiling_tx_save_data
 ��������  : �������̼�¼����
 �������  : oam_profiling_tx_func_enum_uint8 en_func_index
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_tx_save_data(oal_profiling_tx_func_enum_uint8 en_func_index)
{
    if (OAL_SWITCH_OFF == g_mips_tx_statistic.en_switch)
    {
        return ;
    }

    g_mips_tx_statistic.ast_tx_pass_cycles[0][en_func_index] = cpu_clock(UINT_MAX);
}
EXPORT_SYMBOL(oal_profiling_tx_save_data);

/*****************************************************************************
 �� �� ��  : oal_profiling_tx_dump
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��18��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oal_profiling_tx_dump(
                    oal_uint32                          ul_packet_idx,
                    oal_uint32                          ul_loop,
                    oal_profiling_tx_func_enum_uint8    uc_func_idx)
{
    oal_uint64 ull_cycle_now;
    OAL_STATIC oal_uint64 ull_cycle_last;
    oal_uint64 ull_cycle_offset;

    ull_cycle_now = g_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][ul_loop];

    if (uc_func_idx == ul_loop)
    {
        ull_cycle_offset = 0;
    }
    else
    {
        ull_cycle_offset = ull_cycle_now - ull_cycle_last;
    }

    ull_cycle_last = ull_cycle_now;

    OAM_WARNING_LOG3(0, OAM_SF_ANY, "Host NO %2d %14lu        %lu\r\n", ul_loop, ull_cycle_now, ull_cycle_offset);
}

EXPORT_SYMBOL(oal_profiling_tx_dump);

/*****************************************************************************
 �� �� ��  : oal_profiling_tx_mips_show
 ��������  : ����������ʾ����
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_tx_mips_show(oal_void)
{
    oal_uint32 ul_packet_idx;
    oal_uint32 ul_loop;
    oal_uint64 ull_cycle_0;// ul_cycle_1, ul_cycle_2, ul_cycle_3, ul_cycle_4;

    for (ul_packet_idx = 0; ul_packet_idx < OAL_MIPS_TX_PACKET_MAX_COUNT; ul_packet_idx++)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "\r\nTx Time Show: packet number(%d)\r\n", ul_packet_idx);

        /* Time0 */
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "      Current Time        Offset\r\n");
        for (ul_loop = HMAC_PROFILING_FUNC_BRIDGE_VAP_XMIT; ul_loop <= HMAC_PROFILING_FUNC_TX_EVENT_TO_DMAC; ul_loop++)
        {
            oal_profiling_tx_dump(ul_packet_idx, ul_loop, HMAC_PROFILING_FUNC_BRIDGE_VAP_XMIT);
        }
        ull_cycle_0 = g_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][HMAC_PROFILING_FUNC_TX_EVENT_TO_DMAC] - g_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][HMAC_PROFILING_FUNC_BRIDGE_VAP_XMIT];
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "Time0: %lu ns\r\n", ull_cycle_0);
#if 0

        /* Time1 */
        for (ul_loop = HMAC_PROFILING_FUNC_HCC_TX_ADAPT; ul_loop <= HMAC_PROFILING_FUNC_TX_EVENT_TO_DMAC; ul_loop++)
        {
            oal_profiling_tx_dump(ul_packet_idx, ul_loop, HMAC_PROFILING_FUNC_HCC_TX_ADAPT);
        }
        ul_cycle_1 = g_hmac_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][HMAC_PROFILING_FUNC_TX_EVENT_TO_DMAC] - g_hmac_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][HMAC_PROFILING_FUNC_HCC_TX_ADAPT];
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "Time1: %u Cycles\r\n", ul_cycle_1);


        /* Time2 */
        for (ul_loop = DMAC_PROFILING_FUNC_TX_DMAC_ADAPT_START; ul_loop <= DMAC_PROFILING_FUNC_TX_DMAC_END; ul_loop++)
        {
            oal_profiling_tx_dump(ul_packet_idx, ul_loop, DMAC_PROFILING_FUNC_TX_DMAC_ADAPT_START);
        }
        ul_cycle_2 = g_hmac_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][DMAC_PROFILING_FUNC_TX_DMAC_END] - g_hmac_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][DMAC_PROFILING_FUNC_TX_DMAC_ADAPT_START];
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "Time2: %u Cycles\r\n", ul_cycle_2);

        /* Time3 */
        for (ul_loop = DMAC_PROFILING_FUNC_SCHEDULE_START; ul_loop <= DMAC_PROFILING_FUNC_SCHEDULE_END; ul_loop++)
        {
            oal_profiling_tx_dump(ul_packet_idx, ul_loop, DMAC_PROFILING_FUNC_SCHEDULE_START);
        }
        ul_cycle_3 = g_hmac_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][DMAC_PROFILING_FUNC_SCHEDULE_END] - g_hmac_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][DMAC_PROFILING_FUNC_SCHEDULE_START];
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "Time3: %u Cycles\r\n", ul_cycle_3);

        /* Time4 */
        for (ul_loop = DMAC_PROFILING_FUNC_TX_COMP_IRQ_START; ul_loop <= DMAC_PROFILING_FUNC_TX_COMP_DMAC_END; ul_loop++)
        {
            oal_profiling_tx_dump(ul_packet_idx, ul_loop, DMAC_PROFILING_FUNC_TX_COMP_IRQ_START);
        }
        ul_cycle_4 = g_hmac_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][DMAC_PROFILING_FUNC_TX_COMP_DMAC_END] - g_hmac_mips_tx_statistic.ast_tx_pass_cycles[ul_packet_idx][DMAC_PROFILING_FUNC_TX_COMP_IRQ_START];
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "Time4: %u Cycles\r\n", ul_cycle_4);
#endif

        OAM_WARNING_LOG1(0, OAM_SF_ANY, "Tx Total: %lu ns\r\n\n", ull_cycle_0 );

    }
    OAL_MEMZERO(&g_mips_tx_statistic, OAL_SIZEOF(oal_profiling_tx_statistic_stru));
}

EXPORT_SYMBOL(oal_profiling_tx_mips_show);

/*****************************************************************************
 �� �� ��  : oal_profiling_mips_rx_init
 ��������  : DMAC�Ľ�������mipsͳ�Ƴ�ʼ��
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 oal_profiling_mips_rx_init(oal_void)
{
    OAL_MEMZERO(&g_mips_rx_statistic, OAL_SIZEOF(oal_profiling_rx_statistic_stru));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oal_profiling_rx_save_data
 ��������  : �������̼�¼����
 �������  : oal_profiling_rx_func_enum_uint8 en_func_index
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_rx_save_data(oal_profiling_rx_func_enum_uint8 en_func_index)
{
    if (OAL_SWITCH_OFF == g_mips_rx_statistic.en_switch)
    {
        return ;
    }

    g_mips_rx_statistic.ast_rx_pass_cycles[0][en_func_index] = cpu_clock(UINT_MAX);
}
EXPORT_SYMBOL(oal_profiling_rx_save_data);

/*****************************************************************************
 �� �� ��  : oal_profiling_rx_mips_show
 ��������  : ����������ʾ����
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : w00316376
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void oal_profiling_rx_mips_show(oal_void)
{
    oal_uint32 ul_packet_idx;
    oal_uint32 ul_loop;
    oal_uint64 ull_cycle_now;
    oal_uint64 ull_cycle_last;
    oal_uint64 ull_cycle_offset;
    oal_uint64 ull_cycle_1;

    for (ul_packet_idx = 0; ul_packet_idx < OAL_MIPS_RX_PACKET_MAX_COUNT; ul_packet_idx++)
    {
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "\r\nRx Time Show: packet number(%d)\r\n", ul_packet_idx);

        /* �����ж� */
        OAM_WARNING_LOG0(0, OAM_SF_ANY, "      Current Time        Offset\r\n");

        /* ���� */
        for (ul_loop = HMAC_PROFILING_FUNC_RX_DATA_ADAPT; ul_loop <= HMAC_PROFILING_FUNC_RX_HMAC_END; ul_loop++)
        {
            if (HMAC_PROFILING_FUNC_RX_DATA_ADAPT == ul_loop)
            {
                ull_cycle_now = g_mips_rx_statistic.ast_rx_pass_cycles[ul_packet_idx][ul_loop];
                ull_cycle_offset = 0;
                if (0 == ull_cycle_now)
                {
                    ull_cycle_last = 0;
                }
                else
                {
                    ull_cycle_last = ull_cycle_now;
                }
            }
            else
            {
                ull_cycle_now = g_mips_rx_statistic.ast_rx_pass_cycles[ul_packet_idx][ul_loop];
                if (0 == ull_cycle_now)
                {
                    ull_cycle_offset = 0;
                }
                else
                {
                    if (0 == ull_cycle_last)
                    {
                        ull_cycle_offset = 0;
                    }
                    else
                    {
                        ull_cycle_offset = ull_cycle_now - ull_cycle_last;
                    }
                    ull_cycle_last = ull_cycle_now;
                }
            }

            OAM_WARNING_LOG3(0, OAM_SF_ANY, "Host NO %2d %14u        %u\r\n", ul_loop, ull_cycle_now, ull_cycle_offset);
        }
        ull_cycle_1 = g_mips_rx_statistic.ast_rx_pass_cycles[ul_packet_idx][HMAC_PROFILING_FUNC_RX_HMAC_END] - g_mips_rx_statistic.ast_rx_pass_cycles[ul_packet_idx][HMAC_PROFILING_FUNC_RX_DATA_ADAPT];
        OAM_WARNING_LOG1(0, OAM_SF_ANY, "Rx Hmac Total: %lu ns\r\n", ull_cycle_1);

        OAM_WARNING_LOG1(0, OAM_SF_ANY, "Rx Total: %lu ns\r\n\n", ull_cycle_1);
    }

    OAL_MEMZERO(&g_mips_rx_statistic, OAL_SIZEOF(oal_profiling_rx_statistic_stru));
}
EXPORT_SYMBOL(oal_profiling_rx_mips_show);

/*****************************************************************************
 �� �� ��  : oal_profiling_mips_init
 ��������  :
 �������  : oal_void
 �������  : ��
 �� �� ֵ  : oal_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��4��
    ��    ��   : Wlan_mib_temp
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32 oal_profiling_mips_init(oal_void)
{
    oal_profiling_mips_tx_init();
    oal_profiling_mips_rx_init();

    return OAL_SUCC;
}
EXPORT_SYMBOL(oal_profiling_mips_init);

#endif

oal_uint32 oal_get_thruput_bypass_enable(oal_thruput_bypass_enum_uint8 uc_bypass_type)
{
    return g_auc_thruput_bypass_enable[uc_bypass_type];
}

oal_void oal_set_thruput_bypass_enable(oal_thruput_bypass_enum_uint8 uc_bypass_type, oal_uint8 uc_value)
{
    if(OAL_THRUPUT_BYPASS_BUTT <= uc_bypass_type)
    {
        //OAM_WARNING_LOG1(0, OAM_SF_ANY, "oal_get_thruput_bypass_enable::wrong thruput bypass type:%d.", uc_bypass_type);
        /* ��ӡ��ʱ�޸ĳ�PRINTK��ʽ������51��oal��oam���ϳ�һ��ko�󣬷ſ�OAL����OAM������ */
        OAL_IO_PRINT("oal_get_thruput_bypass_enable::wrong thruput bypass type:%d.\n", uc_bypass_type);
        return;
    }
    g_auc_thruput_bypass_enable[uc_bypass_type] = uc_value;
}

#ifndef _PRE_PC_LINT
oal_module_symbol(oal_get_thruput_bypass_enable);
oal_module_symbol(oal_set_thruput_bypass_enable);
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

