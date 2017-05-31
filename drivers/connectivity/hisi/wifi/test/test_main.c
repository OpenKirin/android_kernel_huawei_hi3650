/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : test_main.c
  �� �� ��   : ����
  ��    ��   : mayuan
  ��������   : 2013��7��3��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��3��
    ��    ��   : mayuan
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "oal_ext_if.h"
#include "hal_ext_if.h"
#include "hal_chip.h"
#include "hal_device.h"
#include "hal_witp_mac.h"
#include "hal_witp_soc.h"
#include "hal_witp_rf.h"
#include "test_main.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_TEST_MAIN_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
OAL_STATIC oal_proc_dir_entry_stru *g_pst_test_proc_entry;

#define TEST_HIPRIV_CMD_MAX_LEN   80

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
oal_uint32  wal_test_hipriv_reg_write(oal_int8 *pc_param)
{
    oal_int8       *pc_token;
    oal_int8       *pc_end;
    oal_int8       *pc_ctx;
    oal_int8       *pc_sep = " ";
    oal_uint32      ul_addr;
    oal_uint32      ul_val = 0;
    hal_device_stru   *pst_device;

    pst_device = &gst_hal_board.ast_chip[0].ast_device[0];

    /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_param))
    {
        OAL_IO_PRINT("wal_test_hipriv_reg_write: pst_net_dev or pc_param null ptr error!\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�Ĵ�����ַ */
    pc_token = oal_strtok((oal_int8 *)pc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAL_IO_PRINT("wal_test_hipriv_reg_write: ul_addr null ptr error!\n");
        return OAL_FAIL;
    }

    ul_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    /* ��ȡ��Ҫд���ֵ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAL_IO_PRINT("wal_test_hipriv_reg_write: ul_val null ptr error!\n");
        return OAL_FAIL;
    }

    ul_val = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    OAL_IO_PRINT("wal_test_hipriv_reg_write, addr = 0x%x, val = 0x%x.\n", ul_addr, ul_val);

    WITP_REG_WRITE32(pst_device, ul_addr, ul_val, IDX_WITP_NOT_RECROD_INDEX, HAL_SOFT_REG_TBL_SOC,OAL_FALSE);

    return OAL_SUCC;
}

oal_uint32  wal_test_hipriv_reg_read(oal_int8 *pc_param)
{
    oal_int8       *pc_token;
    oal_int8       *pc_end;
    oal_int8       *pc_ctx;
    oal_int8       *pc_sep = " ";
    oal_uint32       ul_addr;
    oal_uint32      ul_val = 0;
    hal_device_stru   *pst_device;

    pst_device = &gst_hal_board.ast_chip[0].ast_device[0];

    /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_param))
    {
        OAL_IO_PRINT("wal_test_hipriv_reg_read : pst_net_dev or pc_param null ptr error!\n");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡ�Ĵ�����ַ */
    pc_token = oal_strtok((oal_int8 *)pc_param, pc_sep, &pc_ctx);
    if (NULL == pc_token)
    {
        OAL_IO_PRINT("wal_test_hipriv_reg_read: ul_addr null ptr error!\n");
        return OAL_FAIL;
    }

    ul_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

    OAL_IO_PRINT("addr = 0x%x, val = 0x%x.\n", ul_addr, ul_val);

    ul_val = WITP_REG_READ32(pst_device, ul_addr);

    OAL_IO_PRINT("wal_test_hipriv_reg_read, addr = 0x%x, val = 0x%x.\n", ul_addr, ul_val);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : wal_test_fix_test
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��11��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  wal_long_rf_test(oal_void)
{
    hal_device_stru   *pst_device;
    oal_uint16         us_val = 0;
    oal_uint32         ul_loop;

    pst_device = &gst_hal_board.ast_chip[0].ast_device[0];

    /* RF/ABB��memory�ڿ���ѡ��; 0:CBB����, 1:SOC���� */
    WITP_REG_WRITE32(pst_device, WITP_RF_ABB_CTL_REGBANK_WL_RF_ABB_REG_SEL_REG, 0x1,
                    IDX_WITP_NOT_RECROD_INDEX,HAL_SOFT_REG_TBL_SOC,OAL_FALSE);

#if(_PRE_WLAN_CHIP_FPGA_HI1151RF == _PRE_WLAN_CHIP_VERSION)
        WITP_REG_WRITE32(pst_device, WITP_ABB_RF_WIRE_CTL_BASE_ADDR + 0x8C, 0x0,
                        IDX_WITP_NOT_RECROD_INDEX,HAL_SOFT_REG_TBL_SOC,OAL_FALSE);
#endif

    for (ul_loop = 0; ul_loop < 50000; ul_loop++)
    {
        hi1151_rf_write_reg(pst_device, 1, 0x0);
        hi1151_rf_read_reg(pst_device, 1, &us_val);
        if (us_val != 0x0)
        {
            OAL_IO_PRINT("wal_long_rf_test fail, loop = %d, addr = 1, expect val = 0x0, real val = 0x%x.\n", ul_loop, us_val);
            return;
        }

        hi1151_rf_write_reg(pst_device, 3, 0x0F0E);
        hi1151_rf_read_reg(pst_device, 3, &us_val);
        if (us_val != 0x0F0E)
        {
            OAL_IO_PRINT("wal_long_rf_test fail, loop = %d, addr = 3, expect val = 0x0F0E, real val = 0x%x.\n", ul_loop, us_val);
            return;
        }

        hi1151_rf_write_reg(pst_device, 5, 0x0016);
        hi1151_rf_read_reg(pst_device, 5, &us_val);
        if (us_val != 0x0016)
        {
            OAL_IO_PRINT("wal_long_rf_test fail, loop = %d, addr = 5, expect val = 0x0016, real val = 0x%x.\n", ul_loop, us_val);
            return;
        }
    }

    WITP_REG_WRITE32(pst_device, WITP_ABB_RF_WIRE_CTL_BASE_ADDR + 0x8C, 0x1,
                IDX_WITP_NOT_RECROD_INDEX,HAL_SOFT_REG_TBL_SOC,OAL_FALSE);

#if(_PRE_WLAN_CHIP_FPGA_HI1151RF == _PRE_WLAN_CHIP_VERSION)
        WITP_REG_WRITE32(pst_device, WITP_ABB_RF_WIRE_CTL_BASE_ADDR + 0x8C, 0x1,
                    IDX_WITP_NOT_RECROD_INDEX,HAL_SOFT_REG_TBL_SOC,OAL_FALSE);
#endif

    OAL_IO_PRINT("wal_long_rf_test succ.\n");

    return;
}

/*****************************************************************************
 �� �� ��  : wal_long_mac_test
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  wal_long_mac_test(oal_void)
{
    hal_device_stru   *pst_device;
    oal_uint32         ul_loop;

    pst_device = &gst_hal_board.ast_chip[0].ast_device[0];

    for (ul_loop = 0; ul_loop < 1; ul_loop++)
    {
        WITP_REG_WRITE32(pst_device, WITP_PA_AP0_MACADDR_L_REG, 0x12345678, IDX_WITP_PA_AP0_MACADDR_L_REG, HAL_SOFT_REG_TBL_MAC, OAL_FALSE);
    }

    OAL_IO_PRINT("wal_long_mac_test end.\n");

    return;
}

/*****************************************************************************
 �� �� ��  : wal_hipriv_5115_reg_read
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��14��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  wal_test_5115_reg_read(oal_int8 *pc_param)
{
    oal_int8             *pc_token;
    oal_int8             *pc_end;
    oal_int8             *pc_ctx;
    oal_int8             *pc_sep = " ";

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
        oal_uint32            ul_val = 0;
#endif

    struct wal_reg_info_stru
    {
        oal_int8     *pc_reg_type;
        oal_uint32    ul_addr;
        oal_uint32    ul_val;
    }st_reg_info = {0};

     /* ��μ�� */
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_param))
    {
        OAL_IO_PRINT("wal_hipriv_5115_reg_read: pst_net_dev or pc_param null ptr error!");
        return OAL_ERR_CODE_PTR_NULL;
    }

    /* ��ȡҪ��ȡ�ļĴ������� */
    pc_token = oal_strtok((oal_int8 *)pc_param, pc_sep, &pc_ctx);
    if (OAL_PTR_NULL == pc_token)
    {
        return OAL_FAIL;
    }

    /* ������� */
    /*lint -e960*/
    if ((0 != oal_strcmp(pc_token, "sys")) && (0 != oal_strcmp(pc_token, "pci0")))
    {
        return OAL_FAIL;
    }
    /*lint +e960*/

    st_reg_info.pc_reg_type = pc_token;

    /* ��ȡ��ַ */
    pc_token = oal_strtok(OAL_PTR_NULL, pc_sep, &pc_ctx);
    if (OAL_PTR_NULL == pc_token)
    {
        return OAL_FAIL;
    }

    st_reg_info.ul_addr = (oal_uint32)oal_strtol(pc_token, &pc_end, 16);

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    if ((0 == oal_strcmp(st_reg_info.pc_reg_type, "sys")))   /* sys ctl */
    {
        st_reg_info.ul_val = oal_readl(g_pst_5115_sys_ctl + (st_reg_info.ul_addr - OAL_PCIE_SYS_BASE_PHYS));
    }
    else   /* pcie0 */
    {
        /* ���ù���ģʽ����5115�� */
        ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_R_PCIE0);
        ul_val |= BIT21;
        oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_R_PCIE0);

        /* TBD���������ĳ�pst_device->p_pci_dbi_base */
        /* st_reg_info.ul_val = oal_readl(g_pst_5115_pci0 + (st_reg_info.ul_addr - OAL_DBI_BASE_ADDR_0)); */

        /* ���ù���ģʽ���ָ���wifi�� */
        ul_val = oal_readl(g_pst_5115_sys_ctl + OAL_PERI_R_PCIE0);
        ul_val &= (~BIT21);
        oal_writel(ul_val, g_pst_5115_sys_ctl + OAL_PERI_R_PCIE0);
    }
#endif

    OAL_IO_PRINT("read 5115 reg, addr = 0x%x, val = 0x%x.\n", st_reg_info.ul_addr, st_reg_info.ul_val);

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : test_hipriv_proc_write
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  test_hipriv_proc_write(oal_file_stru *pst_file, const oal_int8 *pc_buffer, oal_uint32 ul_len, oal_void *p_data)
{
    oal_int8  *pc_cmd;
    oal_uint32 ul_ret;

    OAL_IO_PRINT("test_hipriv_proc_write start!\n");

    if (ul_len > TEST_HIPRIV_CMD_MAX_LEN)
    {
        OAL_IO_PRINT("test_hipriv_proc_write: test_hipriv_proc_write ul_len > WAL_HIPRIV_CMD_MAX_LEN, ul_len:%d.\n", ul_len);
        return -OAL_EINVAL;
    }

    pc_cmd = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, TEST_HIPRIV_CMD_MAX_LEN, OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pc_cmd))
    {
        OAL_IO_PRINT("test_hipriv_proc_write: alloc mem return null ptr!");
        return -OAL_ENOMEM;
    }

    OAL_MEMZERO(pc_cmd, TEST_HIPRIV_CMD_MAX_LEN);

    ul_ret = oal_copy_from_user(pc_cmd, pc_buffer, ul_len);

    /* copy_from_user������Ŀ���Ǵ��û��ռ俽�����ݵ��ں˿ռ䣬ʧ�ܷ���û�б��������ֽ������ɹ�����0 */
    if (ul_ret > 0)
    {
        OAL_IO_PRINT("test_hipriv_proc_write: oal_copy_from_user return ul_ret:%d.\n", ul_ret);
        OAL_MEM_FREE(pc_cmd, OAL_TRUE);

        return -OAL_EFAUL;
    }

    pc_cmd[ul_len - 1] = '\0';

    if ('1' == pc_cmd[0])
    {
        wal_test_hipriv_reg_write(&pc_cmd[2]);
    }
    else if ('2' == pc_cmd[0])
    {
        wal_test_hipriv_reg_read(&pc_cmd[2]);
    }
    else if ('3' == pc_cmd[0])
    {
        wal_long_rf_test();
    }
    else if ('4' == pc_cmd[0])
    {
        wal_long_mac_test();
    }
    else if ('5' == pc_cmd[0])
    {
        wal_test_5115_reg_read(&pc_cmd[2]);
    }
    else
    {
        OAL_IO_PRINT("test_hipriv_proc_write: the  param is invalid!");
    }

    OAL_MEM_FREE(pc_cmd, OAL_TRUE);

    return (oal_int32)ul_len;
}

/*****************************************************************************
 �� �� ��  : test_hipriv_create_proc
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  test_hipriv_create_proc(oal_void *p_proc_arg)
{
    OAL_IO_PRINT("enter func:test_hipriv_create_proc!");

    /* 420ʮ���ƶ�Ӧ�˽�����0644 linuxģʽ���� S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH); */
    /* S_IRUSR�ļ������߾߿ɶ�ȡȨ��, S_IWUSR�ļ������߾߿�д��Ȩ��, S_IRGRP�û���߿ɶ�ȡȨ��, S_IROTH�����û��߿ɶ�ȡȨ�� */
    g_pst_test_proc_entry = oal_create_proc_entry(WITP_RW_TEST_HIPRIV_PROC_ENTRY_NAME, 420, NULL);
    if (OAL_PTR_NULL == g_pst_test_proc_entry)
    {
        OAL_IO_PRINT("test_hipriv_create_proc: oal_create_proc_entry return null ptr!");
        return OAL_ERR_CODE_PTR_NULL;
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    /* oal_create_proc_entryֱ�ӷ���ΪNULL */
#else
    g_pst_test_proc_entry->data       = p_proc_arg;
    g_pst_test_proc_entry->nlink      = 1;                   /* linux����procĬ��ֵ */
    g_pst_test_proc_entry->read_proc  = OAL_PTR_NULL;

    g_pst_test_proc_entry->write_proc = (write_proc_t *)test_hipriv_proc_write;
#endif
    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : test_hipriv_destroy_proc
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��24��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  test_hipriv_destroy_proc(oal_void)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    oal_remove_proc_entry(WITP_RW_TEST_HIPRIV_PROC_ENTRY_NAME, NULL);
#elif (_PRE_OS_VERSION_WIN32 == _PRE_OS_VERSION)
    oal_remove_proc_entry(WITP_RW_TEST_HIPRIV_PROC_ENTRY_NAME, g_pst_test_proc_entry);
#endif
}

/*****************************************************************************
 �� �� ��  : test_main_init
 ��������  : �������(��ʼ��)����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32 test_main_init(oal_void)
{
    oal_uint32   ul_ret;

    ul_ret = test_hipriv_create_proc(OAL_PTR_NULL);
    if (OAL_SUCC != ul_ret)
    {
        OAL_IO_PRINT("test_main_init: test_hipriv_create_proc failed!\n");
        return (oal_int32)ul_ret;
    }

    OAL_IO_PRINT("test_main_init successful!\n");

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : test_main_exit
 ��������  : ����ģ���˳�(���)����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��3��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void test_main_exit(oal_void)
{
    test_hipriv_destroy_proc();
}


/*lint -e578*//*lint -e19*/
oal_module_init(test_main_init);
oal_module_exit(test_main_exit);
/*lint +e578*//*lint +e19*/





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

