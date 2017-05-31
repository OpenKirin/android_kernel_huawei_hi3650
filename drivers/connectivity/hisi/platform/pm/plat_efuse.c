/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : plat_efuse.c
  �� �� ��   : ����
  ��    ��   : k00355907
  ��������   : 2016��5��12��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2016��5��12��
    ��    ��   : k00355907
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
#include "plat_efuse.h"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
uint8 g_uc_hi110x_ec_version = V100;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : read_efuse_ec_version
 ��������  : ��device EFUSE�ж�ȡEC�汾��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��23��
    ��    ��   : z000299054
    �޸�����   : �����ɺ���

*****************************************************************************/
void read_efuse_ec_version(void)
{
    int32 ret = 0;
    uint8 buff[EFUSE_REG_WIDTH] = {0x00};
    uint8 uc_ec_version = V100;
    uint32 i = 0;

    ret = number_type_cmd_send(RMEM_CMD_KEYWORD, GET_EFUSE_EC_VERSION);
    if (0 > ret)
    {
        PS_PRINT_WARNING("send cmd %s:%s fail,ret = %d\n", RMEM_CMD_KEYWORD, GET_EFUSE_EC_VERSION, ret);
        return;
    }

    ret = read_msg((uint8*)buff, sizeof(buff));
    if (0 > ret)
    {
        PS_PRINT_WARNING("read efuse ec version fail, read_len = %d, return = %d\n", (int32)sizeof(buff), ret);
        return;
    }

    for (i = 0; i < sizeof(buff); i++)
    {
        PS_PRINT_DBG("ec version[%d]=0x%x\n", i , buff[i]);
    }

    uc_ec_version  = buff[1];        //Byte24(0x50000771)��Ӧbit[191:184]
    uc_ec_version &= ((uint8)0x03);  //bit[185:184]��ʾEC version

    if (V100 == uc_ec_version)
    {
        PS_PRINT_INFO("hi110x read efuse V100[0x%x]\n", uc_ec_version);
        g_uc_hi110x_ec_version = V100;
    }
    else
    {
        PS_PRINT_INFO("hi110x read efuse V120[0x%x]\n", uc_ec_version);
        g_uc_hi110x_ec_version = V120;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : get_ec_version
 ��������  : ��ȡhi110xоƬEC�汾��
 �������  : ��
 �������  : ��
 �� �� ֵ  : EC�汾��
 ���ú���  : �ɵ����߱�֤��Ч��
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��11��23��
    ��    ��   : z000299054
    �޸�����   : �����ɺ���

*****************************************************************************/
uint8 get_ec_version(void)
{
    return g_uc_hi110x_ec_version;
}

/*****************************************************************************
 �� �� ��  : mask_bits
 ��������  : ��λ����Ϊ��
 �������  : uint32 value[]
             int32 start_bits
             int32 end_bits
 �������  : ��
 �� �� ֵ  : static void
 ���ú���  : �ɵ����߱�֤��Ч��
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��16��
    ��    ��   : k00355907
    �޸�����   : �����ɺ���

*****************************************************************************/
static void mask_bits(uint32 value[], int32 start_bits, int32 end_bits)
{
    int32 index = 0;
    int32     i = 0;
    int32     j = 0;

    if (NULL == value)
    {
        return;
    }

    for (index = start_bits; index <= end_bits; index++)
    {
        i = index / EFUSE_VALUE_WIDTH;
        j = index % EFUSE_VALUE_WIDTH;
        value[i] &= ~(1 << j);
    }
}
/*****************************************************************************
 �� �� ��  : check_efuse_file_exist
 ��������  : ����ļ��Ƿ����
 �������  : void
 �������  : ��
 �� �� ֵ  : static int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��16��
    ��    ��   : k00355907
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 check_efuse_file_exist(void)
{
    struct file* fp = NULL;

    fp = filp_open(EFUSE_FILE_PATH, O_RDONLY, 0);
    if (IS_ERR(fp))
    {
        return -EFAIL;
    }

    filp_close(fp, NULL);

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : get_efuse_from_device
 ��������  : ��device��ȡefuse��Ϣ
 �������  : uint32* buff
             int32 len
 �������  : ��
 �� �� ֵ  : static int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��12��
    ��    ��   : k00355907
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 get_efuse_from_device(uint32* buff, int32 len)
{
    int32 ret = 0;

    if (NULL == buff)
    {
        PS_PRINT_ERR("efuse buff is NULL\n");
        return -EFAIL;
    }

    ret = number_type_cmd_send(RMEM_CMD_KEYWORD, GET_EFUSE_CMD);
    if (0 > ret)
    {
        PS_PRINT_WARNING("send cmd %s:%s fail,ret = %d\n", RMEM_CMD_KEYWORD, GET_EFUSE_CMD, ret);
        return -EFAIL;
    }

    ret = read_msg((uint8*)buff, len);
    if (0 > ret)
    {
        PS_PRINT_WARNING("read efuse fail, read_len = %d, return = %d\n", len, ret);
        return -EFAIL;
    }

    return SUCC;

}
/*****************************************************************************
 �� �� ��  : store_efuse_into_file
 ��������  : ��efuse��Ϣ��������
 �������  : uint32* buff
 �������  : ��
 �� �� ֵ  : static int32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��12��
    ��    ��   : k00355907
    �޸�����   : �����ɺ���

*****************************************************************************/
static int32 store_efuse_into_file(uint32* buff)
{
    struct file *fp  = NULL;
    loff_t       pos = 0;
    int32      index = 0;
    ssize_t      ret = 0;
    mm_segment_t fs;

    if (NULL == buff)
    {
        PS_PRINT_ERR("efuse buff is NULL\n");
        return -EFAIL;
    }

    mask_bits(buff, DIEID_BIT_4,  DIEID_BIT_21);
    mask_bits(buff, DIEID_BIT_45, DIEID_BIT_45);
    mask_bits(buff, DIEID_BIT_53, DIEID_BIT_53);
    mask_bits(buff, DIEID_BIT_79, DIEID_BIT_95);

    memset(&fs, 0x00, sizeof(fs));    /* [false alarm]:fortify��  */

    fp = filp_open(EFUSE_FILE_PATH, O_CREAT|O_RDWR, 0644);
    if (IS_ERR(fp))
    {
        PS_PRINT_ERR("open %s fail, errno = %ld\n", EFUSE_FILE_PATH, PTR_ERR(fp));
        return -EFAIL;
    }

    fs = get_fs();
    set_fs(KERNEL_DS);
    pos = 0;
    for (index = 0; index < EFUSE_REG_NUM; index++)
    {
        ret = vfs_write(fp, (uint8 *)(&buff[index]), sizeof(uint16), &pos);
        if (ret < 0)
        {
            PS_PRINT_ERR("write %s fail, ret = %d\n", EFUSE_FILE_PATH, (int32)ret);
            filp_close(fp, NULL);
            set_fs(fs);
            return -EFAIL;
        }
    }

    filp_close(fp, NULL);
    set_fs(fs);

    return SUCC;
}

/*****************************************************************************
 �� �� ��  : store_efuse_info
 ��������  :
 �������  : void
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��5��12��
    ��    ��   : k00355907
    �޸�����   : �����ɺ���

*****************************************************************************/
void store_efuse_info(void)
{
    int32  ret = 0;
    uint32 buff[EFUSE_REG_NUM] = {0x00};
    static int32 retry_count = 0;

    if (retry_count >= EFUSE_RETRY)
    {
        return;
    }
    retry_count++;

    read_efuse_ec_version();

    ret = check_efuse_file_exist();
    if (ret == SUCC)
    {
        retry_count = EFUSE_RETRY;
        return;
    }

    ret = get_efuse_from_device(buff, sizeof(buff));
    if (SUCC != ret)
    {
        PS_PRINT_ERR("get efuse from device fail\n");
        return;
    }

    ret = store_efuse_into_file(buff);
    if (SUCC != ret)
    {
        PS_PRINT_ERR("store efuse into %s fail\n", EFUSE_FILE_PATH);
        return;
    }

    retry_count = EFUSE_RETRY;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

