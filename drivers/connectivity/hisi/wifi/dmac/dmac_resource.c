/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dmac_resource.c
  �� �� ��   : ����
  ��    ��   : z00326350
  ��������   : 2015��4��31��
  ����޸�   :
  ��������   : HMAC��Դ�����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��1��31��
    ��    ��   : z00326350
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
#include "dmac_resource.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_DMAC_RESOURCE_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rwdata = "BTCM", code ="ATCM", zidata = "BTCM", rodata = "ATCM"
#endif
dmac_res_stru    g_st_dmac_res;

#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)
#pragma arm section rodata, code, rwdata, zidata  // return to default placement
#endif
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : dmac_res_alloc_mac_dev
 ��������  : ��ȡһ��HMAC DEV��Դ
 �������  : ��
 �������  : HMAC DEV�ڴ�����ֵ
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_res_alloc_mac_dev(oal_uint32    ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_res_alloc_dmac_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_FAIL;
    }

    (g_st_dmac_res.st_dmac_dev_res.auc_user_cnt[ul_dev_idx])++;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_res_free_mac_dev
 ��������  : �ͷŶ�ӦHMAC DEV���ڴ�
 �������  : ��ӦHMAC DEV�ڴ�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��31��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_res_free_mac_dev(oal_uint32 ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_res_free_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_FAIL;
    }

    (g_st_dmac_res.st_dmac_dev_res.auc_user_cnt[ul_dev_idx])--;

    if (0 != g_st_dmac_res.st_dmac_dev_res.auc_user_cnt[ul_dev_idx])
    {
        return OAL_SUCC;
    }

    /* �������ֵ��Ҫ��1���� */
    oal_queue_enqueue(&(g_st_dmac_res.st_dmac_dev_res.st_queue), (oal_void *)((oal_uint)ul_dev_idx + 1));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : dmac_res_get_mac_dev
 ��������  : ��ȡ��ӦHMAC DEV�������ڴ�
 �������  : ��ӦHMAC DEV�ڴ�����
 �������  : ��
 �� �� ֵ  : ��Ӧ�ڴ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��31��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
dmac_device_stru  *dmac_res_get_mac_dev(oal_uint32 ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{dmac_res_get_dmac_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_PTR_NULL;
    }

    return &(g_st_dmac_res.st_dmac_dev_res.ast_dmac_dev_info[ul_dev_idx]);
}

/*****************************************************************************
 �� �� ��  : dmac_res_init
 ��������  : ��ʼ��HMAC��Դ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��31��
    ��    ��   : l00279018
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  dmac_res_init(oal_void)
{
    oal_uint32      ul_loop;

    OAL_MEMZERO(&g_st_dmac_res, OAL_SIZEOF(g_st_dmac_res));

    /***************************************************************************
            ��ʼ��DMAC DEV����Դ��������
    ***************************************************************************/
    oal_queue_set(&(g_st_dmac_res.st_dmac_dev_res.st_queue),
                  g_st_dmac_res.st_dmac_dev_res.aul_idx,
                  MAC_RES_MAX_DEV_NUM);

    for (ul_loop = 0; ul_loop < MAC_RES_MAX_DEV_NUM; ul_loop++)
    {
        /* ��ʼֵ������Ƕ�Ӧ�����±�ֵ��1 */
        oal_queue_enqueue(&(g_st_dmac_res.st_dmac_dev_res.st_queue), (oal_void *)((oal_uint)ul_loop + 1));

        /* ��ʼ����Ӧ�����ü���ֵΪ0 */
        g_st_dmac_res.st_dmac_dev_res.auc_user_cnt[ul_loop] = 0;
    }

    return OAL_SUCC;
}

/*lint -e578*//*lint -e19*/
oal_module_symbol(dmac_res_get_mac_dev);
/*lint -e578*//*lint -e19*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

