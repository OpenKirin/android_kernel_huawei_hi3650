/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
�� �� ��   : plat_main
�� �� ��   : ����
��    ��   : z00273164
��������   : 2014��10��10��
����޸�   :
��������   : plat_main.c �ļ�
�����б�   :
�޸���ʷ   :
1.��    ��   : 2014��10��10��
 ��    ��   : z00273164
 �޸�����   : �����ļ�

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#define HISI_LOG_TAG "[plat_init]"
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "plat_main.h"
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include "board.h"
#include "oneimage.h"
#include "plat_pm.h"
#include "hw_bfg_ps.h"
#include "oal_kernel_file.h"
#include "hisi_ini.h"
#endif

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_PLAT_MAIN_C

extern int plat_exception_reset_init(void);
extern int plat_exception_reset_exit(void);
extern int low_power_init(void);
extern void  low_power_exit(void);
extern int hw_ps_init(void);
extern void hw_ps_exit(void);

#if (defined(CONFIG_HISI_GPS_REF_CLK) || defined(CONFIG_CONNECTIVITY_HI110X_HI6250) || defined(CONFIG_CONNECTIVITY_HI110X_HI3650) || defined(CONFIG_CONNECTIVITY_HI110X_HI3660))
extern int hi_gps_plat_init(void);
extern void hi_gps_plat_exit(void);
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
extern int hw_misc_connectivity_init(void);
extern void hw_misc_connectivity_exit(void);
#endif

#ifdef CONFIG_HI1102_PLAT_HW_CHR
extern int chr_miscdevs_init(void);
extern void chr_miscdevs_exit(void);
#endif


#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
extern BOARD_INFO g_board_info;
int isAsic(void)
{
    if (VERSION_ASIC == g_board_info.is_asic)
    {
        return VERSION_ASIC;
    }
    else
    {
        return VERSION_FPGA;
    }
}

EXPORT_SYMBOL_GPL(isAsic);
#else
int isAsic(void)
{
    return 1;
}
#endif

/*****************************************************************************
 �� �� ��  : plat_init
 ��������  : ƽ̨��ʼ����������ڣ�Ŀǰʵ����wifiҵ��Ŀ¼�£��˴���ʱע�գ�
             ����Ų������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��3��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  plat_init(oal_void)
{
    oal_int32   l_return   = OAL_FAIL;
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#ifdef HI110X_DRV_VERSION
    OAL_IO_PRINT("HI110X_DRV_VERSION: %s\r\n", HI110X_DRV_VERSION);
    OAL_IO_PRINT("HI110X_DRV compileTime: %s, %s\r\n", __DATE__,__TIME__);
#endif
    if(false == is_my_chip())
    {
        return OAL_SUCC;
    }
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    l_return = ini_cfg_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: customize init fail\r\n");
        goto customize_init_failed;
    }
#endif

    l_return = plat_exception_reset_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: plat_exception_reset_init fail\r\n");
        goto plat_exception_rst_init_fail;
    }

#ifdef CONFIG_HI1102_PLAT_HW_CHR
    l_return = chr_miscdevs_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: chr_miscdev_init return error code: %d\r\n", l_return);

        goto chr_miscdevs_init_fail;
    }
#endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    l_return = hi110x_board_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: hi110x_board_init fail\r\n");
        goto board_init_fail;
    }
#endif

    l_return = oal_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: oal_main_init return error code: %d\r\n", l_return);
        goto oal_main_init_fail;
    }

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    l_return = hw_misc_connectivity_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: hw_misc_connectivity_init return error code: %d\r\n", l_return);
        goto  hw_misc_connectivity_init_fail;
    }
#endif

    l_return = oam_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: oam_main_init return error code: %d\r\n", l_return);
        goto oam_main_init_fail;
    }

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    l_return = sdt_drv_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: sdt_drv_main_init return error code: %d\r\n", l_return);
        goto sdt_drv_main_init_fail;
    }
#endif

    l_return = frw_main_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: frw_main_init return error code: %d\r\n", l_return);
        goto frw_main_init_fail;
    }

    l_return = low_power_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: low_power_init return error code: %d\r\n", l_return);
        goto low_power_init_fail;
    }

    l_return = hw_ps_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: hw_ps_init return error code: %d\r\n", l_return);
        goto hw_ps_init_fail;
    }

#if (defined(CONFIG_HISI_GPS_REF_CLK) || defined(CONFIG_CONNECTIVITY_HI110X_HI6250) || defined(CONFIG_CONNECTIVITY_HI110X_HI3650) || defined(CONFIG_CONNECTIVITY_HI110X_HI3660))
    l_return = hi_gps_plat_init();
    if (OAL_SUCC != l_return)
    {
        OAL_IO_PRINT("plat_init: hi_gps_plat_init fail\r\n");
        goto gps_plat_init_fail;
    }
#endif

#ifdef HAVE_HISI_NFC
        /* ��ȡnfc�͵�log����,Ȼ���µ磬����ǰ��ʼ���쳣�����ᵹ��NFC�͵�log*/
        save_nfc_lowpower_log();
#endif

    /*������ɺ������ӡ*/
    OAL_IO_PRINT("plat_init:: platform_main_init finish!\r\n");

    return OAL_SUCC;

#if (defined(CONFIG_HISI_GPS_REF_CLK) || defined(CONFIG_CONNECTIVITY_HI110X_HI6250) || defined(CONFIG_CONNECTIVITY_HI110X_HI3650) || defined(CONFIG_CONNECTIVITY_HI110X_HI3660))
gps_plat_init_fail:
    hw_ps_exit();
#endif
hw_ps_init_fail:
    low_power_exit();
low_power_init_fail:
    frw_main_exit();
frw_main_init_fail:
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    sdt_drv_main_exit();
sdt_drv_main_init_fail:
#endif
    oam_main_exit();
oam_main_init_fail:
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    hw_misc_connectivity_exit();
hw_misc_connectivity_init_fail:
#endif
    oal_main_exit();
oal_main_init_fail:
    /*�쳣�رյ�Դ*/
    #ifdef HAVE_HISI_NFC
    hi_wlan_power_off();
    #endif

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    hi110x_board_exit();
board_init_fail:
#endif
#ifdef CONFIG_HI1102_PLAT_HW_CHR
    chr_miscdevs_exit();
chr_miscdevs_init_fail:
#endif
    plat_exception_reset_exit();
plat_exception_rst_init_fail:
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    ini_cfg_exit();
customize_init_failed:
#endif

    return l_return;
}

/*****************************************************************************
 �� �� ��  : plat_exit
 ��������  : ƽ̨ж�غ�������ڣ�Ŀǰʵ����wifiҵ��Ŀ¼�£��˴���ʱע�գ�
             ����Ų������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��3��
    ��    ��   : z00273164
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void plat_exit(oal_void)
{
#if (defined(CONFIG_HISI_GPS_REF_CLK) || defined(CONFIG_CONNECTIVITY_HI110X_HI6250) || defined(CONFIG_CONNECTIVITY_HI110X_HI3650) || defined(CONFIG_CONNECTIVITY_HI110X_HI3660))
    hi_gps_plat_exit();
#endif

    hw_ps_exit();
    low_power_exit();
    frw_main_exit();

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    sdt_drv_main_exit();
#endif

    oam_main_exit();

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    hw_misc_connectivity_exit();
#endif

    oal_main_exit();

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    hi110x_board_exit();
#endif

#ifdef CONFIG_HI1102_PLAT_HW_CHR
    chr_miscdevs_exit();
#endif

    plat_exception_reset_exit();
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    ini_cfg_exit();
#endif
    return;
}

/*lint -e578*//*lint -e19*/
#if defined(_PRE_PRODUCT_ID_HI110X_HOST) && !defined(CONFIG_HI110X_KERNEL_MODULES_BUILD_SUPPORT) && defined(_PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT)
oal_int32 g_plat_init_flag = 0;
oal_int32 g_plat_init_ret;
/*built-in*/
OAL_STATIC ssize_t  plat_sysfs_set_init(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
    char            mode[128] = {0};
    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    if ((sscanf(buf, "%20s", mode) != 1))
    {
        OAL_IO_PRINT("set value one param!\n");
        return -OAL_EINVAL;
    }

    if(sysfs_streq("init", mode))
    {
        /*init*/
        if(0 == g_plat_init_flag)
        {
            g_plat_init_ret = plat_init();
            g_plat_init_flag = 1;
        }
        else
        {
            OAL_IO_PRINT("double init!\n");
        }
    }
    else
    {
        OAL_IO_PRINT("invalid input:%s\n",mode);
    }

    return count;
}

OAL_STATIC ssize_t  plat_sysfs_get_init(struct device *dev, struct device_attribute *attr, char*buf)
{
    int ret = 0;
    OAL_BUG_ON(NULL == dev);
    OAL_BUG_ON(NULL == attr);
    OAL_BUG_ON(NULL == buf);

    if(1 == g_plat_init_flag)
    {
        if(OAL_SUCC == g_plat_init_ret)
        {
            ret +=  snprintf(buf + ret , PAGE_SIZE-ret, "running\n");
        }
        else
        {
            ret +=  snprintf(buf + ret , PAGE_SIZE-ret, "boot failed ret=%d\n", g_plat_init_ret);
        }
    }
    else
    {
        ret +=  snprintf(buf + ret , PAGE_SIZE-ret, "uninit\n");
    }

    return ret;
}
OAL_STATIC DEVICE_ATTR(plat, S_IRUGO | S_IWUSR, plat_sysfs_get_init, plat_sysfs_set_init);
OAL_STATIC struct attribute *plat_init_sysfs_entries[] = {
        &dev_attr_plat.attr,
        NULL
};

OAL_STATIC struct attribute_group plat_init_attribute_group = {
        .attrs = plat_init_sysfs_entries,
};

oal_int32  plat_sysfs_init(oal_void)
{
    oal_int32 ret = 0;
    oal_uint32 ul_rslt;
    oal_kobject*     pst_root_boot_object = NULL;

    /*110X ����build in���ڴ�س�ʼ�����Ƶ��ں���ɣ���֤��Ƭ�ڴ�����ɹ�*/
    ul_rslt = oal_mem_init_pool();
    if (ul_rslt != OAL_SUCC)
    {
        OAL_IO_PRINT("oal_main_init: oal_mem_init_pool return error code: %d", ul_rslt);
        OAL_BUG_ON(1);
        return -OAL_EFAIL;
    }

    OAL_IO_PRINT("mem pool init succ\n");

    pst_root_boot_object = oal_get_sysfs_root_boot_object();
    if(NULL == pst_root_boot_object)
    {
        OAL_IO_PRINT("[E]get root boot sysfs object failed!\n");
        return -OAL_EBUSY;
    }

    ret = sysfs_create_group(pst_root_boot_object,&plat_init_attribute_group);
    if (ret)
    {
        OAL_IO_PRINT("sysfs create plat boot group fail.ret=%d\n",ret);
        ret = -OAL_ENOMEM;
        return ret;
    }

    return ret;
}

oal_void  plat_sysfs_exit(oal_void)
{
    /*need't exit,built-in*/
    return;
}
oal_module_init(plat_sysfs_init);
oal_module_exit(plat_sysfs_exit);
#else
//#ifdef CONFIG_HI1102_PLATFORM_MODULE
oal_module_init(plat_init);
oal_module_exit(plat_exit);
#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

