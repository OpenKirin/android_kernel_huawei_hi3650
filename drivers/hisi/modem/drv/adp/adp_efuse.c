

#include <linux/kernel.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/mm.h>
#include "product_config.h"
#include "bsp_om.h"
#include "mdrv_efuse.h"
#include "bsp_efuse.h"
#include "hi_efuse.h"

#include <mdrv.h>
#include "../../adrv/adrv.h"

#include <soc_onchiprom.h>


int mdrv_efuse_write_huk(char *pBuf,unsigned int len)
{
    return OK;
}

int mdrv_efuse_check_huk_valid(void)
{
    return OK;
}

/*************************************************
 �� �� ��   : DRV_GET_DIEID
 ��������   : DRV_GET_DIEID
 �������   : buf: data buffer
              len: length of the group
 �������   :
 �� �� ֵ   : OK                (0)
              BUF_ERROR         (-55)
              LEN_ERROR         (-56)
              READ_EFUSE_ERROR  (-57)
 ���ú���   :
 ��������   :

 �޸���ʷ   :
   ��    �� : 2013��8��12��
   ��    �� : l00225826
   �޸����� : �����ɺ���

*************************************************/
int mdrv_efuse_get_dieid(unsigned char* buf,int length)
{
    return get_efuse_dieid_value(buf, (unsigned int)length, 0);
}


/*************************************************
 �� �� ��   : DRV_GET_CHIPID
 ��������   : DRV_GET_CHIPID
 �������   : buf: data buffer
              len: length of the group
 �������   :
 �� �� ֵ   : OK                (0)
              BUF_ERROR         (-55)
              LEN_ERROR         (-56)
              READ_EFUSE_ERROR  (-57)
 ���ú���   :
 ��������   :

 �޸���ʷ   :
   ��    �� : 2013��8��12��
   ��    �� : l00225826
   �޸����� : �����ɺ���

*************************************************/
int mdrv_efuse_get_chipid(unsigned char* buf,int length)
{
    return get_efuse_chipid_value(buf, (unsigned int)length, 0);
}
int mdrv_efuse_ioctl(int cmd, int arg, unsigned char* buf, int len)
{
    efuse_print_error("It's only a stub");

    return EFUSE_OK;
}

void DRV_DIEID_TEST(void)
{
    int i = 0;
    char *buf = kzalloc(EFUSE_DIEID_LEN, GFP_KERNEL);
    if(NULL == buf)
    {
        efuse_print_info("alloc mem is fail.\n");
        return;
    }

    if(EFUSE_OK == mdrv_efuse_get_dieid(buf, EFUSE_DIEID_LEN))
    {
        for(i = 0;i < EFUSE_DIEID_LEN;i++)
        {
            efuse_print_info("0x%x \n", *(buf+i));
        }

    }
    else
    {
        efuse_print_error("DRV_GET_DIEID is fail.\n");
    }

    kfree(buf);
}


