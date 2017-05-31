/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : plat_cali.c
  �� �� ��   : ����
  ��    ��   :
  ��������   :
  ����޸�   :
  ��������   : ���ºͼ��ض���У׼����
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2015��7��16��
    ��    ��   : z00299054
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "plat_firmware.h"
#include "plat_cali.h"
#include "plat_debug.h"
#include "plat_type.h"

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define RF_CALI_DATA_BUF_LEN  (sizeof(oal_cali_param_stru))

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/

/*����У׼���ݵ�buf*/
oal_uint8 *g_pucCaliDataBuf = NULL;
oal_uint8 g_uc_netdev_is_open = OAL_FALSE;
/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : get_cali_count
 ��������  : ����У׼�Ĵ������״ο���У׼ʱΪ0���Ժ����
 �������  : uint32 *count:���ú�������У׼�����ĵ�ַ
 �������  : count:�Կ����������Ѿ�У׼�Ĵ���
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : z00299054
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 get_cali_count(oal_uint32 *count)
{
    oal_cali_param_stru *pst_cali_data = NULL;
    oal_uint16 cali_count;
    oal_uint32 cali_parm;

    if (NULL == count)
    {
        PS_PRINT_ERR("count is NULL\n");
        return -EFAIL;
    }

    if (NULL == g_pucCaliDataBuf)
    {
        PS_PRINT_ERR("g_pucCaliDataBuf is NULL\n");
        return -EFAIL;
    }

    pst_cali_data = (oal_cali_param_stru *)g_pucCaliDataBuf;
    cali_count    = pst_cali_data->st_cali_update_info.ul_cali_time;
    cali_parm     = *(oal_uint32 *)&(pst_cali_data->st_cali_update_info);

    PS_PRINT_WARNING("cali count is [%d], cali update info is [%d]\n", cali_count, cali_parm);

    *count = cali_parm;

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : get_bfgx_cali_data
 ��������  : ���ر���bfgxУ׼���ݵ��ڴ��׵�ַ�Լ�����
 �������  : uint8  *buf:���ú�������bfgxУ׼���ݵ��׵�ַ
             uint32 *len:���ú�������bfgxУ׼�����ڴ泤�ȵĵ�ַ
             uint32 buf_len:buf�ĳ���
 �������  : ��
 �� �� ֵ  : 0��ʾ�ɹ���-1��ʾʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : z00299054
    �޸�����   : �����ɺ���
*****************************************************************************/
int32 get_bfgx_cali_data(oal_uint8 *buf, oal_uint32 *len, oal_uint32 buf_len)
{
    oal_cali_param_stru *pst_cali_data         = NULL;
    oal_cali_param_addition_stru cali_addition = {0x00};
    oal_uint32 bfgx_cali_data_len;
    oal_uint32 bfgx_cali_addition_len;
    oal_int32  wifi_5g_enable_info = WIFI_MODE_5G;
    oal_int32  result;


    if (NULL == buf)
    {
        PS_PRINT_ERR("buf is NULL\n");
        return -EFAIL;
    }

    if (NULL == len)
    {
        PS_PRINT_ERR("len is NULL\n");
        return -EFAIL;
    }

    bfgx_cali_data_len     = sizeof(oal_bfgn_cali_param_stru);
    bfgx_cali_addition_len = sizeof(oal_cali_param_addition_stru);
    if (buf_len < (bfgx_cali_data_len + bfgx_cali_addition_len))
    {
        PS_PRINT_ERR("buf_len[%d] is smaller than struct size[%d]\n", buf_len, bfgx_cali_data_len + bfgx_cali_addition_len);
        return -EFAIL;
    }

    if (NULL == g_pucCaliDataBuf)
    {
        PS_PRINT_ERR("g_pucCaliDataBuf is NULL\n");
        return -EFAIL;
    }

    pst_cali_data = (oal_cali_param_stru *)g_pucCaliDataBuf;
    OS_MEM_CPY(buf, (oal_uint8 *)&(pst_cali_data->st_bfgn_cali_data), bfgx_cali_data_len);
    *len = bfgx_cali_data_len;

    /**********************************************************************************
    |----------------------------------------------------------------------------------|
    |   oal_cali_param_stru          : Դ���ݽṹ        |            216 byte         |
    |----------------------------------------------------------------------------------|
    |   oal_cali_param_addition_stru : ׷�����ݽṹ      |             40 byte         |
    |----------------------------------------------------------------------------------|
    ************************************************************************************/

    /******************************* WIFI 5Gʹ�ܼ���־λ ******************************/
    result = get_cust_conf_int32(INI_MODU_WIFI, CHECK_5G_ENABLE, &wifi_5g_enable_info);
    if (0 > result)
    {
        PS_PRINT_WARNING("host get wifi 5g enable info fail\n");
        /* ��ȡʧ��,Ĭ��Ϊ5G */
        wifi_5g_enable_info = WIFI_MODE_5G;
    }

    if (WIFI_MODE_2_4G == wifi_5g_enable_info)
    {
        cali_addition.ul_wifi_2_4g_only = WIFI_2_4G_ONLY;
    }
    else
    {
        cali_addition.ul_wifi_2_4g_only = 0;
    }

    /******************************** bfgx�쳣�����������־λ *********************************/
    if (is_bfgx_exception())
    {
        cali_addition.ul_excep_reboot = SYS_EXCEP_REBOOT;
    }
    else
    {
        cali_addition.ul_excep_reboot = 0;
    }

    OS_MEM_CPY((buf + *len), (oal_uint8 *)(&cali_addition), bfgx_cali_addition_len);
    *len += bfgx_cali_addition_len;

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : get_cali_data_buf_addr
 ��������  : ���ر���У׼���ݵ��ڴ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : g_pucCaliDataBuf�ĵ�ַ��Ҳ������NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : z00299054
    �޸�����   : �����ɺ���

*****************************************************************************/
void *get_cali_data_buf_addr(void)
{
    return g_pucCaliDataBuf;
}

EXPORT_SYMBOL(get_cali_data_buf_addr);
EXPORT_SYMBOL(g_uc_netdev_is_open);

/*****************************************************************************
 �� �� ��  : plat_bfgx_cali_data_test
 ��������  : test
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : z00299054
    �޸�����   : �����ɺ���

*****************************************************************************/
void plat_bfgx_cali_data_test(void)
{
    oal_cali_param_stru *pst_cali_data = NULL;
    oal_uint32 *p_test = NULL;
    oal_uint32 count;
    oal_uint32 i;

    pst_cali_data = (oal_cali_param_stru *)get_cali_data_buf_addr();
    if (NULL == pst_cali_data)
    {
        PS_PRINT_ERR("get_cali_data_buf_addr failed\n");
        return;
    }

    p_test = (oal_uint32 *)&(pst_cali_data->st_bfgn_cali_data);
    count  = sizeof(oal_bfgn_cali_param_stru) / sizeof(oal_uint32);

    for (i = 0; i < count; i++)
    {
        p_test[i] = i;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : cali_data_buf_malloc
 ��������  : ���䱣��У׼���ݵ��ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : 0��ʾ����ɹ���-1��ʾ����ʧ��
 ���ú���  :
 ��������  : firmware_cfg_init

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : z00299054
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32 cali_data_buf_malloc(void)
{
    oal_uint8 *buffer = NULL;

    buffer = OS_KZALLOC_GFP(RF_CALI_DATA_BUF_LEN);
    if (NULL == buffer)
    {
        return -EFAIL;
    }
    g_pucCaliDataBuf = buffer;

    //plat_bfgx_cali_data_test();

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : cali_data_buf_free
 ��������  : �ͷű���У׼���ݵ��ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  : firmware_cfg_clear

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : z00299054
    �޸�����   : �����ɺ���

*****************************************************************************/
void cali_data_buf_free(void)
{
    if (NULL != g_pucCaliDataBuf)
    {
        OS_MEM_KFREE(g_pucCaliDataBuf);
    }
    g_pucCaliDataBuf = NULL;
}


