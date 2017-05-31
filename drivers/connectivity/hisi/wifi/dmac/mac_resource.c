/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : mac_resource.c
  �� �� ��   : ����
  ��    ��   : c00178899
  ��������   : 2013��5��8��
  ����޸�   :
  ��������   : MAC��Դ�����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��8��
    ��    ��   : c00178899
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
#include "wlan_spec.h"
#include "mac_resource.h"
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151))
#include "dmac_vap.h"
#include "dmac_user.h"
#endif
#if (defined(_PRE_PRODUCT_ID_HI110X_HOST) || (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151))
#include "hmac_vap.h"
#include "hmac_user.h"
#endif


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_MAC_RESOURCE_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* 1��device֧�ֵ��������û��� */
#if (defined(_PRE_PRODUCT_ID_HI110X_DEV) || defined(_PRE_PRODUCT_ID_HI110X_HOST))
oal_uint16      g_us_max_asoc_user = 8;
#else
oal_uint16      g_us_max_asoc_user = 32;
#endif

mac_res_stru    g_st_mac_res;


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : mac_res_check_spec
 ��������  : ��ʼ��MAC��Դ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : zhangyu
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_check_spec(oal_void)
{
    oal_uint32  ul_ret = OAL_SUCC;
    /* ���MAC VAP��С */
#if defined(_PRE_PRODUCT_ID_HI110X_HOST)
    /*����������������ṹ�壬
    ��û���޸Ķ�Ӧ�Ĵ�С�����³�����SIZE������ж����б�Ҫ�ģ�����������*/
    if (OAL_SIZEOF(hmac_vap_stru) > MAC_RES_VAP_SIZE)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{mac_res_check_spec::hmac_vap_stru is over limit! hmac_vap_stru[%d], MAC_RES_VAP_SIZE[%d]}",
                      OAL_SIZEOF(hmac_vap_stru), MAC_RES_VAP_SIZE);
        ul_ret = OAL_FAIL;
    }

    if (OAL_SIZEOF(hmac_user_stru) > MAC_RES_USER_SIZE)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{mac_res_check_spec::hmac_user_stru is over limit! hmac_user_stru[%d], MAC_RES_USER_SIZE[%d]}",
                       OAL_SIZEOF(hmac_user_stru), MAC_RES_USER_SIZE);
        ul_ret = OAL_FAIL;
    }

#elif defined(_PRE_PRODUCT_ID_HI110X_DEV)
    if (OAL_SIZEOF(dmac_vap_stru) > MAC_RES_VAP_SIZE)
    {
        //OAL_IO_PRINT("{mac_res_check_spec::dmac_vap_stru is over limit!dmac_vap_stru[%d], MAC_RES_VAP_SIZE[%d]}\r\n",
        //             OAL_SIZEOF(dmac_vap_stru), MAC_RES_VAP_SIZE);

        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{mac_res_check_spec::dmac_vap_stru is over limit! dmac_vap_stru[%d], MAC_RES_VAP_SIZE[%d]}",
                       OAL_SIZEOF(dmac_vap_stru), MAC_RES_VAP_SIZE);
        ul_ret = OAL_FAIL;
    }

    if (OAL_SIZEOF(dmac_user_stru) > MAC_RES_USER_SIZE)
    {
        //OAL_IO_PRINT("{mac_res_check_spec::dmac_user_stru is over limit!dmac_user_stru[%d], MAC_RES_USER_SIZE[%d]}\r\n",
        //             OAL_SIZEOF(dmac_user_stru), MAC_RES_USER_SIZE);

        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{mac_res_check_spec::hmac_user_stru is over limit! dmac_user_stru[%d], MAC_RES_USER_SIZE[%d]}",
                       OAL_SIZEOF(dmac_user_stru), MAC_RES_USER_SIZE);
        ul_ret = OAL_FAIL;
    }
#elif (_PRE_PRODUCT_ID == _PRE_PRODUCT_ID_HI1151)
    if ((OAL_SIZEOF(hmac_vap_stru) + OAL_SIZEOF(dmac_vap_stru) - OAL_SIZEOF(mac_vap_stru)) > MAC_RES_VAP_SIZE)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{mac_res_check_spec::vap_stru is over limit! vap_stru[%d], MAC_RES_VAP_SIZE[%d]}",
                      (OAL_SIZEOF(hmac_vap_stru) + OAL_SIZEOF(dmac_vap_stru) - OAL_SIZEOF(mac_vap_stru)),
                       MAC_RES_VAP_SIZE);
        OAL_IO_PRINT("{mac_res_check_spec::vap_stru is over limit! hmac_vap[%d], dmac_vap[%d], mac_vap[%d], MAC_RES_VAP_SIZE[%d].\r\n}",
                     OAL_SIZEOF(hmac_vap_stru), OAL_SIZEOF(dmac_vap_stru), OAL_SIZEOF(mac_vap_stru), MAC_RES_VAP_SIZE);
        ul_ret = OAL_FAIL;
    }

    if ((OAL_SIZEOF(hmac_user_stru) + OAL_SIZEOF(dmac_user_stru) - OAL_SIZEOF(mac_user_stru)) > MAC_RES_USER_SIZE)
    {
        OAM_ERROR_LOG2(0, OAM_SF_ANY, "{mac_res_check_spec::user_stru is over limit! user_stru[%d], MAC_RES_USER_SIZE[%d]}",
                       (OAL_SIZEOF(hmac_user_stru) + OAL_SIZEOF(dmac_user_stru) - OAL_SIZEOF(mac_user_stru)), MAC_RES_USER_SIZE);
        OAL_IO_PRINT("{mac_res_check_spec::user_stru is over limit! hmac_user[%d], dmac_user[%d], mac_user[%d], MAC_RES_USER_SIZE[%d].\r\n}",
                     OAL_SIZEOF(hmac_user_stru), OAL_SIZEOF(dmac_user_stru), OAL_SIZEOF(mac_user_stru), MAC_RES_USER_SIZE);
        ul_ret = OAL_FAIL;
    }
#endif
    return ul_ret;
}


#if (defined(_PRE_PRODUCT_ID_HI110X_DEV))

/*****************************************************************************
 �� �� ��  : mac_res_user_init
 ��������  : �û���Դ�س�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_user_init(oal_void)
{
    oal_uint16      us_max_asoc_user_per_board;
    oal_uint16      us_max_service_vap_num_per_board;
    oal_uint16      us_max_user;
    oal_uint32      ul_loop;
    oal_void       *p_user_info = OAL_PTR_NULL;
    oal_void       *p_idx       = OAL_PTR_NULL;
    oal_void       *p_user_cnt  = OAL_PTR_NULL;
    oal_void       *p_hash_info = OAL_PTR_NULL;
    oal_void       *p_hash_idx  = OAL_PTR_NULL;
    oal_void       *p_hash_cnt  = OAL_PTR_NULL;
    oal_uint16      us_user_info_size;
    oal_uint16      us_idx_size;
    oal_uint16      us_user_cnt_size;

    /***************************************************************************
            ��ʼ��USER����Դ��������
    ***************************************************************************/
    /*
    �������û� = 1��device֧�ֵ��������û��� * board�����device��Ŀ;
    ����鲥�û� = 1��device֧�ֵ����ҵ��vap�� * board�����device��Ŀ;
    ����û��� = �������û� + �鲥�û����� */
    us_max_asoc_user_per_board = (oal_uint16)(g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM);
    us_max_service_vap_num_per_board = WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * MAC_RES_MAX_DEV_NUM;
    us_max_user = us_max_asoc_user_per_board + us_max_service_vap_num_per_board;

    /* ����������Դ�ش�С�Ƿ���� */
    us_user_info_size = (oal_uint16)(OAL_SIZEOF(mac_res_mem_user_stru) * us_max_user);
    us_idx_size       = (oal_uint16)(OAL_SIZEOF(oal_uint)* us_max_user);
    us_user_cnt_size  = (oal_uint16)(OAL_SIZEOF(oal_uint8) * us_max_user);
    if (WLAN_MEM_LOCAL_SIZE6 < (us_user_info_size + us_idx_size + us_user_cnt_size))
    {

        OAM_ERROR_LOG2(0, OAM_SF_UM, "{mac_res_user_init::ALLOC_SIZE(%d) too small!,arm(%d).}",WLAN_MEM_LOCAL_SIZE6,(us_user_info_size + us_idx_size + us_user_cnt_size));
        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��̬�����û���Դ������ڴ� */
    p_user_info = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, WLAN_MEM_LOCAL_SIZE6, OAL_TRUE);
    p_idx       = (oal_uint8 *)p_user_info + us_user_info_size;
    p_user_cnt  = (oal_uint8 *)p_idx + us_idx_size;

    if ((OAL_PTR_NULL == p_user_info) || (OAL_PTR_NULL == p_idx) || (OAL_PTR_NULL == p_user_cnt))
    {
        OAM_ERROR_LOG0(0, OAM_SF_UM, "{mac_res_user_init::param null.}");

        OAL_MEM_FREE(p_user_info, OAL_TRUE);

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }


    /* �ڴ��ʼ��0 */
    OAL_MEMZERO(p_user_info, (OAL_SIZEOF(mac_res_mem_user_stru) * us_max_user));
    OAL_MEMZERO(p_idx,       (OAL_SIZEOF(oal_uint) * us_max_user));
    OAL_MEMZERO(p_user_cnt,  (OAL_SIZEOF(oal_uint8) * us_max_user));

    g_st_mac_res.st_user_res.pst_user_info  = p_user_info;
    g_st_mac_res.st_user_res.pul_idx        = p_idx;
    g_st_mac_res.st_user_res.puc_user_cnt   = p_user_cnt;

    g_st_mac_res.st_user_res.us_hmac_priv_size = 0;

    for (ul_loop = 0; ul_loop < us_max_user; ul_loop++)
    {

        /* ��ʼ����Ӧ�����ü���ֵΪ0 */
        g_st_mac_res.st_user_res.puc_user_cnt[ul_loop] = 0;
    }

    /***************************************************************************
            ��ʼ��HASHͰ����Դ��������
    ***************************************************************************/
    us_user_info_size = (oal_uint16)(OAL_SIZEOF(mac_res_user_hash_stru) * us_max_asoc_user_per_board);
    us_idx_size       = (oal_uint16)(OAL_SIZEOF(oal_uint) * us_max_asoc_user_per_board);
    us_user_cnt_size  = (oal_uint16)(OAL_SIZEOF(oal_uint8) * us_max_asoc_user_per_board);

    /* ����������Դ�ش�С�Ƿ���� */
    if (WLAN_MEM_LOCAL_SIZE3 < (us_user_info_size + us_idx_size + us_user_cnt_size))
    {
        OAM_ERROR_LOG2(0, OAM_SF_UM, "{mac_res_user_init::ALLOC_SIZE(%d) too small!,arm(%d).}",WLAN_MEM_LOCAL_SIZE1,(us_user_info_size + us_idx_size + us_user_cnt_size));

        OAL_MEM_FREE(p_user_info, OAL_TRUE);
        g_st_mac_res.st_user_res.pst_user_info  = OAL_PTR_NULL;

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��̬�����û���Դ������ڴ� */
    p_hash_info = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_LOCAL, WLAN_MEM_LOCAL_SIZE3, OAL_TRUE);
    p_hash_idx  = (oal_uint8 *)p_hash_info + us_user_info_size;
    p_hash_cnt  = (oal_uint8 *)p_hash_idx + us_idx_size;

    if ((OAL_PTR_NULL == p_hash_info) || (OAL_PTR_NULL == p_hash_idx) || (OAL_PTR_NULL == p_hash_cnt))
    {
        OAM_ERROR_LOG0(0, OAM_SF_UM, "{mac_res_user_init::param null.}");
        OAL_MEM_FREE(p_hash_info, OAL_TRUE);

        /* �ͷ��û���Դ��������ڴ� */
        OAL_MEM_FREE((p_user_info), OAL_TRUE);

        g_st_mac_res.st_user_res.pst_user_info  = OAL_PTR_NULL;
        g_st_mac_res.st_user_res.pul_idx        = OAL_PTR_NULL;
        g_st_mac_res.st_user_res.puc_user_cnt   = OAL_PTR_NULL;

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* �ڴ��ʼ��0 */
    OAL_MEMZERO(p_hash_info, (OAL_SIZEOF(mac_res_user_hash_stru) * us_max_asoc_user_per_board));
    OAL_MEMZERO(p_hash_idx,  (OAL_SIZEOF(oal_uint) * us_max_asoc_user_per_board));
    OAL_MEMZERO(p_hash_cnt,  (OAL_SIZEOF(oal_uint8) * us_max_asoc_user_per_board));

    g_st_mac_res.st_hash_res.pst_user_hash_info = p_hash_info;
    g_st_mac_res.st_hash_res.pul_idx            = p_hash_idx;
    g_st_mac_res.st_hash_res.puc_user_cnt       = p_hash_cnt;

    oal_queue_set(&(g_st_mac_res.st_hash_res.st_queue),
                  g_st_mac_res.st_hash_res.pul_idx,
                  (oal_uint8)us_max_asoc_user_per_board);

    for (ul_loop = 0; ul_loop < us_max_asoc_user_per_board; ul_loop++)
    {
        /* ��ʼֵ������Ƕ�Ӧ�����±�ֵ��1 */
        oal_queue_enqueue(&(g_st_mac_res.st_hash_res.st_queue), (oal_void *)(ul_loop + 1));

        /* ��ʼ����Ӧ�����ü���ֵΪ0 */
        g_st_mac_res.st_hash_res.puc_user_cnt[ul_loop] = 0;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : mac_res_exit
 ��������  : ��Դ���˳����ͷŶ�̬������ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_exit(void)
{
    OAL_MEM_FREE((g_st_mac_res.st_user_res.pst_user_info), OAL_TRUE);

    OAL_MEM_FREE((g_st_mac_res.st_hash_res.pst_user_hash_info), OAL_TRUE);

    g_st_mac_res.st_user_res.pst_user_info      = OAL_PTR_NULL;
    g_st_mac_res.st_user_res.pul_idx            = OAL_PTR_NULL;
    g_st_mac_res.st_user_res.puc_user_cnt       = OAL_PTR_NULL;

    g_st_mac_res.st_hash_res.pst_user_hash_info = OAL_PTR_NULL;
    g_st_mac_res.st_hash_res.pul_idx            = OAL_PTR_NULL;
    g_st_mac_res.st_hash_res.puc_user_cnt       = OAL_PTR_NULL;

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : mac_res_init
 ��������  : ��ʼ��MAC��Դ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_init(oal_void)
{
    oal_uint        ul_loop;
    oal_uint32      ul_ret;

    OAL_MEMZERO(&g_st_mac_res, OAL_SIZEOF(mac_res_stru));
    /***************************************************************************
            ��ʼ��DEV����Դ��������
    ***************************************************************************/
    oal_queue_set(&(g_st_mac_res.st_dev_res.st_queue),
                  g_st_mac_res.st_dev_res.aul_idx,
                  MAC_RES_MAX_DEV_NUM);

    ul_ret = mac_res_check_spec();
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_res_init::mac_res_user_init failed[%d].}", ul_ret);
        return ul_ret;
    }

    for (ul_loop = 0; ul_loop < MAC_RES_MAX_DEV_NUM; ul_loop++)
    {
        /* ��ʼֵ������Ƕ�Ӧ�����±�ֵ��1 */
        oal_queue_enqueue(&(g_st_mac_res.st_dev_res.st_queue), (oal_void *)(ul_loop + 1));

        /* ��ʼ����Ӧ�����ü���ֵΪ0 */
        g_st_mac_res.st_dev_res.auc_user_cnt[ul_loop] = 0;
    }

    /***************************************************************************
            ��ʼ��VAP����Դ��������
    ***************************************************************************/

    g_st_mac_res.st_vap_res.us_hmac_priv_size = 0;

    for (ul_loop = 0; ul_loop < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; ul_loop++)
    {
        /* ��ʼֵ������Ƕ�Ӧ�����±�ֵ��1 */


        /* ��ʼ����Ӧ�����ü���ֵΪ0 */
        g_st_mac_res.st_vap_res.auc_user_cnt[ul_loop] = 0;
    }

    /***************************************************************************
            ��ʼ��USER����Դ��������
            ��ʼ��HASHͰ����Դ��������
    ***************************************************************************/
    ul_ret = mac_res_user_init();
    if (OAL_SUCC != ul_ret)
    {
        MAC_ERR_LOG1(0, "mac_res_init: mac_res_user_init return err code", ul_ret);
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_res_init::mac_res_user_init failed[%d].}", ul_ret);

        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_res_free_mac_user
 ��������  : �ͷŶ�ӦHMAC USER���ڴ�
 �������  : ��ӦHMAC USER�ڴ�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_free_mac_user(oal_uint16 us_idx)
{
    if (OAL_UNLIKELY(us_idx >= g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * MAC_RES_MAX_DEV_NUM))
    {
        return OAL_FAIL;
    }

    if(0 == g_st_mac_res.st_user_res.puc_user_cnt[us_idx])
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,"mac_res_free_mac_user::cnt==0! idx:%d",us_idx);
        oal_dump_stack();
        return OAL_ERR_CODE_USER_RES_CNT_ZERO;
    }

    (g_st_mac_res.st_user_res.puc_user_cnt[us_idx])--;

    if (0 != g_st_mac_res.st_user_res.puc_user_cnt[us_idx])
    {
        return OAL_SUCC;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_res_free_hmac_vap
 ��������  : �ͷŶ�ӦHMAC VAP���ڴ�
 �������  : ��ӦHMAC VAP�ڴ�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_free_mac_vap(oal_uint32 ul_idx)
{
    if (OAL_UNLIKELY(ul_idx >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        return OAL_FAIL;
    }

    if(0 == g_st_mac_res.st_vap_res.auc_user_cnt[ul_idx])
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,"mac_res_free_mac_vap::cnt==0! idx:%d",ul_idx);
        oal_dump_stack();
        return OAL_SUCC;
    }

    (g_st_mac_res.st_vap_res.auc_user_cnt[ul_idx])--;

    if (0 != g_st_mac_res.st_vap_res.auc_user_cnt[ul_idx])
    {
        return OAL_SUCC;
    }

    return OAL_SUCC;
}

#else

/*****************************************************************************
 �� �� ��  : mac_res_user_init
 ��������  : �û���Դ�س�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_user_init(oal_void)
{
    oal_uint16      us_max_asoc_user_per_board;
    oal_uint16      us_max_service_vap_num_per_board;
    oal_uint16      us_max_user;
    oal_uint        ul_loop;
    oal_void       *p_user_info = OAL_PTR_NULL;
    oal_void       *p_idx       = OAL_PTR_NULL;
    oal_void       *p_user_cnt  = OAL_PTR_NULL;
    oal_void       *p_hash_info = OAL_PTR_NULL;
    oal_void       *p_hash_idx  = OAL_PTR_NULL;
    oal_void       *p_hash_cnt  = OAL_PTR_NULL;

    /***************************************************************************
            ��ʼ��USER����Դ��������
    ***************************************************************************/
    /*
    �������û� = 1��device֧�ֵ��������û��� * board�����device��Ŀ;
    ����鲥�û� = 1��device֧�ֵ����ҵ��vap�� * board�����device��Ŀ;
    ����û��� = �������û� + �鲥�û����� */
    us_max_asoc_user_per_board = (oal_uint16)(g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM);
    us_max_service_vap_num_per_board = WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * MAC_RES_MAX_DEV_NUM;
    us_max_user = us_max_asoc_user_per_board + us_max_service_vap_num_per_board;

    /* ��̬�����û���Դ������ڴ� */
    p_user_info = oal_memalloc(OAL_SIZEOF(mac_res_mem_user_stru) * us_max_user);
    p_idx       = oal_memalloc(OAL_SIZEOF(oal_uint) * us_max_user);
    p_user_cnt  = oal_memalloc(OAL_SIZEOF(oal_uint8) * us_max_user);
    if ((OAL_PTR_NULL == p_user_info) || (OAL_PTR_NULL == p_idx) || (OAL_PTR_NULL == p_user_cnt))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_res_user_init::param null.}");

        if (OAL_PTR_NULL != p_user_info)
        {
            oal_free(p_user_info);
        }

        if (OAL_PTR_NULL != p_idx)
        {
            oal_free(p_idx);
        }

        if (OAL_PTR_NULL != p_user_cnt)
        {
            oal_free(p_user_cnt);
        }

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }


    /* �ڴ��ʼ��0 */
    OAL_MEMZERO(p_user_info, (OAL_SIZEOF(mac_res_mem_user_stru) * us_max_user));
    OAL_MEMZERO(p_idx,       (OAL_SIZEOF(oal_uint) * us_max_user));
    OAL_MEMZERO(p_user_cnt,  (OAL_SIZEOF(oal_uint8) * us_max_user));

    g_st_mac_res.st_user_res.pst_user_info  = p_user_info;
    g_st_mac_res.st_user_res.pul_idx        = p_idx;
    g_st_mac_res.st_user_res.puc_user_cnt   = p_user_cnt;

    oal_queue_set(&(g_st_mac_res.st_user_res.st_queue),
                  g_st_mac_res.st_user_res.pul_idx,
                  (oal_uint8)us_max_user);
    g_st_mac_res.st_user_res.us_hmac_priv_size = 0;

    for (ul_loop = 0; ul_loop < us_max_user; ul_loop++)
    {
        /* ��ʼֵ������Ƕ�Ӧ�����±�ֵ��1 */
        oal_queue_enqueue(&(g_st_mac_res.st_user_res.st_queue), (oal_void *)(ul_loop + 1));

        /* ��ʼ����Ӧ�����ü���ֵΪ0 */
        g_st_mac_res.st_user_res.puc_user_cnt[ul_loop] = 0;
    }

    /***************************************************************************
            ��ʼ��HASHͰ����Դ��������
    ***************************************************************************/
    p_hash_info = oal_memalloc(OAL_SIZEOF(mac_res_user_hash_stru) * us_max_asoc_user_per_board);
    p_hash_idx  = oal_memalloc(OAL_SIZEOF(oal_uint) * us_max_asoc_user_per_board);
    p_hash_cnt  = oal_memalloc(OAL_SIZEOF(oal_uint8) * us_max_asoc_user_per_board);
    if ((OAL_PTR_NULL == p_hash_info) || (OAL_PTR_NULL == p_hash_idx) || (OAL_PTR_NULL == p_hash_cnt))
    {
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_res_user_init::param null.}");

        if (OAL_PTR_NULL != p_hash_info)
        {
            oal_free(p_hash_info);
        }

        if (OAL_PTR_NULL != p_hash_idx)
        {
            oal_free(p_hash_idx);
        }

        if (OAL_PTR_NULL != p_hash_cnt)
        {
            oal_free(p_hash_cnt);
        }

        /* �ͷ��û���Դ��������ڴ� */
        oal_free(p_user_info);
        oal_free(p_idx);
        oal_free(p_user_cnt);

        g_st_mac_res.st_user_res.pst_user_info  = OAL_PTR_NULL;
        g_st_mac_res.st_user_res.pul_idx        = OAL_PTR_NULL;
        g_st_mac_res.st_user_res.puc_user_cnt   = OAL_PTR_NULL;

        return OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* �ڴ��ʼ��0 */
    OAL_MEMZERO(p_hash_info, (OAL_SIZEOF(mac_res_user_hash_stru) * us_max_asoc_user_per_board));
    OAL_MEMZERO(p_hash_idx,  (OAL_SIZEOF(oal_uint) * us_max_asoc_user_per_board));
    OAL_MEMZERO(p_hash_cnt,  (OAL_SIZEOF(oal_uint8) * us_max_asoc_user_per_board));

    g_st_mac_res.st_hash_res.pst_user_hash_info = p_hash_info;
    g_st_mac_res.st_hash_res.pul_idx            = p_hash_idx;
    g_st_mac_res.st_hash_res.puc_user_cnt       = p_hash_cnt;

    oal_queue_set(&(g_st_mac_res.st_hash_res.st_queue),
                  g_st_mac_res.st_hash_res.pul_idx,
                  (oal_uint8)us_max_asoc_user_per_board);

    for (ul_loop = 0; ul_loop < us_max_asoc_user_per_board; ul_loop++)
    {
        /* ��ʼֵ������Ƕ�Ӧ�����±�ֵ��1 */
        oal_queue_enqueue(&(g_st_mac_res.st_hash_res.st_queue), (oal_void *)(ul_loop + 1));

        /* ��ʼ����Ӧ�����ü���ֵΪ0 */
        g_st_mac_res.st_hash_res.puc_user_cnt[ul_loop] = 0;
    }

    return OAL_SUCC;
}
/*****************************************************************************
 �� �� ��  : mac_res_exit
 ��������  : ��Դ���˳����ͷŶ�̬������ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_exit(void)
{
    oal_free(g_st_mac_res.st_user_res.pst_user_info);
    oal_free(g_st_mac_res.st_user_res.pul_idx);
    oal_free(g_st_mac_res.st_user_res.puc_user_cnt);

    oal_free(g_st_mac_res.st_hash_res.pst_user_hash_info);
    oal_free(g_st_mac_res.st_hash_res.pul_idx);
    oal_free(g_st_mac_res.st_hash_res.puc_user_cnt);

    g_st_mac_res.st_user_res.pst_user_info      = OAL_PTR_NULL;
    g_st_mac_res.st_user_res.pul_idx            = OAL_PTR_NULL;
    g_st_mac_res.st_user_res.puc_user_cnt       = OAL_PTR_NULL;

    g_st_mac_res.st_hash_res.pst_user_hash_info = OAL_PTR_NULL;
    g_st_mac_res.st_hash_res.pul_idx            = OAL_PTR_NULL;
    g_st_mac_res.st_hash_res.puc_user_cnt       = OAL_PTR_NULL;

    return OAL_SUCC;
}


/*****************************************************************************
 �� �� ��  : mac_res_init
 ��������  : ��ʼ��MAC��Դ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_init(oal_void)
{
    oal_uint        ul_loop;
    oal_uint32      ul_ret;

    OAL_MEMZERO(&g_st_mac_res, OAL_SIZEOF(mac_res_stru));
    /***************************************************************************
            ��ʼ��DEV����Դ��������
    ***************************************************************************/
    oal_queue_set(&(g_st_mac_res.st_dev_res.st_queue),
                  g_st_mac_res.st_dev_res.aul_idx,
                  MAC_RES_MAX_DEV_NUM);

    ul_ret = mac_res_check_spec();
    if (OAL_SUCC != ul_ret)
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_res_init::mac_res_user_init failed[%d].}", ul_ret);
        return ul_ret;
    }

    for (ul_loop = 0; ul_loop < MAC_RES_MAX_DEV_NUM; ul_loop++)
    {
        /* ��ʼֵ������Ƕ�Ӧ�����±�ֵ��1 */
        oal_queue_enqueue(&(g_st_mac_res.st_dev_res.st_queue), (oal_void *)(ul_loop + 1));

        /* ��ʼ����Ӧ�����ü���ֵΪ0 */
        g_st_mac_res.st_dev_res.auc_user_cnt[ul_loop] = 0;
    }

    /***************************************************************************
            ��ʼ��VAP����Դ��������
    ***************************************************************************/
    oal_queue_set(&(g_st_mac_res.st_vap_res.st_queue),
                  g_st_mac_res.st_vap_res.aul_idx,
                  (oal_uint8)WLAN_VAP_SUPPORT_MAX_NUM_LIMIT);
    g_st_mac_res.st_vap_res.us_hmac_priv_size = 0;

    for (ul_loop = 0; ul_loop < WLAN_VAP_SUPPORT_MAX_NUM_LIMIT; ul_loop++)
    {
        /* ��ʼֵ������Ƕ�Ӧ�����±�ֵ��1 */
        oal_queue_enqueue(&(g_st_mac_res.st_vap_res.st_queue), (oal_void *)(ul_loop + 1));

        /* ��ʼ����Ӧ�����ü���ֵΪ0 */
        g_st_mac_res.st_vap_res.auc_user_cnt[ul_loop] = 0;
    }

    /***************************************************************************
            ��ʼ��USER����Դ��������
            ��ʼ��HASHͰ����Դ��������
    ***************************************************************************/
    ul_ret = mac_res_user_init();
    if (OAL_SUCC != ul_ret)
    {
        MAC_ERR_LOG1(0, "mac_res_init: mac_res_user_init return err code", ul_ret);
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_res_init::mac_res_user_init failed[%d].}", ul_ret);

        return ul_ret;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_res_free_mac_user
 ��������  : �ͷŶ�ӦHMAC USER���ڴ�
 �������  : ��ӦHMAC USER�ڴ�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_free_mac_user(oal_uint16 us_idx)
{
    if (OAL_UNLIKELY(us_idx >= g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM + WLAN_SERVICE_VAP_MAX_NUM_PER_DEVICE * MAC_RES_MAX_DEV_NUM))
    {
        return OAL_FAIL;
    }

    if(0 == g_st_mac_res.st_user_res.puc_user_cnt[us_idx])
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,"mac_res_free_mac_user::cnt==0! idx:%d",us_idx);
        oal_dump_stack();
        return OAL_ERR_CODE_USER_RES_CNT_ZERO;
    }

    (g_st_mac_res.st_user_res.puc_user_cnt[us_idx])--;

    if (0 != g_st_mac_res.st_user_res.puc_user_cnt[us_idx])
    {
        return OAL_SUCC;
    }

    /* �������ֵ��Ҫ��1���� */
    oal_queue_enqueue(&(g_st_mac_res.st_user_res.st_queue), (oal_void *)((oal_uint)us_idx + 1));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_res_free_hmac_vap
 ��������  : �ͷŶ�ӦHMAC VAP���ڴ�
 �������  : ��ӦHMAC VAP�ڴ�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_free_mac_vap(oal_uint32 ul_idx)
{
    if (OAL_UNLIKELY(ul_idx >= WLAN_VAP_SUPPORT_MAX_NUM_LIMIT))
    {
        return OAL_FAIL;
    }

    if(0 == g_st_mac_res.st_vap_res.auc_user_cnt[ul_idx])
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,"mac_res_free_mac_vap::cnt==0! idx:%d",ul_idx);
        oal_dump_stack();
        return OAL_SUCC;
    }

    (g_st_mac_res.st_vap_res.auc_user_cnt[ul_idx])--;

    if (0 != g_st_mac_res.st_vap_res.auc_user_cnt[ul_idx])
    {
        return OAL_SUCC;
    }

    /* �������ֵ��Ҫ��1���� */
    oal_queue_enqueue(&(g_st_mac_res.st_vap_res.st_queue), (oal_void *)((oal_uint)ul_idx + 1));

    return OAL_SUCC;
}

#endif


/*****************************************************************************
 �� �� ��  : mac_res_free_hash
 ��������  : �ͷŶ�ӦHASH���ڴ�
 �������  : ��ӦHASH�ڴ�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_free_hash(oal_uint32 ul_hash_idx)
{
    if (OAL_UNLIKELY(ul_hash_idx >= (oal_uint32)(g_us_max_asoc_user * MAC_RES_MAX_DEV_NUM)))
    {
        return OAL_FAIL;
    }

    if(0 == g_st_mac_res.st_hash_res.puc_user_cnt[ul_hash_idx])
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,"mac_res_free_hash::cnt==0! idx:%d",ul_hash_idx);
        oal_dump_stack();
        return OAL_SUCC;
    }

    (g_st_mac_res.st_hash_res.puc_user_cnt[ul_hash_idx])--;

    if (0 != g_st_mac_res.st_hash_res.puc_user_cnt[ul_hash_idx])
    {
        return OAL_SUCC;
    }

    /* �������ֵ��Ҫ��1���� */
    oal_queue_enqueue(&(g_st_mac_res.st_hash_res.st_queue), (oal_void *)((oal_uint)ul_hash_idx + 1));

    return OAL_SUCC;
}



/*****************************************************************************
 �� �� ��  : mac_set_max_asoc_user
 ��������  : �����������û���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_set_max_asoc_user(oal_uint16 us_num)
{
    g_us_max_asoc_user = us_num;

    /* ��Ҫϵͳ��λ */

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_res_alloc_dmac_dev
 ��������  : ��ȡһ��DEV��Դ
 �������  : ��
 �������  : DEV�ڴ�����ֵ
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
 oal_uint32  mac_res_alloc_dmac_dev(oal_uint8    *puc_dev_idx)
{
    oal_uint  ul_dev_idx_temp;

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_dev_idx))
    {
        OAL_IO_PRINT("mac_res_alloc_dmac_dev: OAL_PTR_NULL == pul_dev_idx");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_res_alloc_dmac_dev::puc_dev_idx null.}");

        return OAL_FAIL;
    }

    ul_dev_idx_temp = (oal_uint)oal_queue_dequeue(&(g_st_mac_res.st_dev_res.st_queue));

    /* 0Ϊ��Чֵ */
    if (0 == ul_dev_idx_temp)
    {
        OAL_IO_PRINT("mac_res_alloc_dmac_dev: 0 == ul_dev_idx_temp");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_res_alloc_dmac_dev::ul_dev_idx_temp=0.}");

        return OAL_FAIL;
    }

    *puc_dev_idx = (oal_uint8)(ul_dev_idx_temp - 1);

    (g_st_mac_res.st_dev_res.auc_user_cnt[ul_dev_idx_temp - 1])++;

    return OAL_SUCC;
}
#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
/*****************************************************************************
 �� �� ��  : mac_res_alloc_hmac_dev
 ��������  : ��ȡһ��DEV��Դ
 �������  : ��
 �������  : DEV�ڴ�����ֵ
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : liuzhengqi
    �޸�����   : �����ɺ���

*****************************************************************************/
 oal_uint32  mac_res_alloc_hmac_dev(oal_uint8    *puc_dev_idx)
{
    oal_uint  ul_dev_idx_temp;

    if (OAL_UNLIKELY(OAL_PTR_NULL == puc_dev_idx))
    {
        OAL_IO_PRINT("mac_res_alloc_hmac_dev: OAL_PTR_NULL == pul_dev_idx");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_res_alloc_hmac_dev::puc_dev_idx null.}");

        return OAL_FAIL;
    }

    ul_dev_idx_temp = (oal_uint)oal_queue_dequeue(&(g_st_mac_res.st_dev_res.st_queue));

    /* 0Ϊ��Чֵ */
    if (0 == ul_dev_idx_temp)
    {
        OAL_IO_PRINT("mac_res_alloc_hmac_dev: 0 == ul_dev_idx_temp");
        OAM_ERROR_LOG0(0, OAM_SF_ANY, "{mac_res_alloc_hmac_dev::ul_dev_idx_temp=0.}");

        return OAL_FAIL;
    }

    *puc_dev_idx = (oal_uint8)(ul_dev_idx_temp - 1);

    (g_st_mac_res.st_dev_res.auc_user_cnt[ul_dev_idx_temp - 1])++;

    return OAL_SUCC;
}
#else
/*****************************************************************************
 �� �� ��  : mac_res_alloc_hmac_dev
 ��������  : ��ȡһ��DEV��Դ
 �������  : ��
 �������  : DEV�ڴ�����ֵ
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_alloc_hmac_dev(oal_uint32    ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        MAC_ERR_LOG(0, "mac_res_alloc_hmac_dev: ul_dev_idx >= MAC_RES_MAX_DEV_NUM");
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_res_alloc_hmac_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_FAIL;
    }

    (g_st_mac_res.st_dev_res.auc_user_cnt[ul_dev_idx])++;

    return OAL_SUCC;
}
#endif
/*****************************************************************************
 �� �� ��  : mac_res_free_dev
 ��������  : �ͷŶ�ӦDEV���ڴ�
 �������  : ��ӦDEV�ڴ�����
 �������  : ��
 �� �� ֵ  : OAL_SUCC/OAL_FAIL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : chenwenfeng
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  mac_res_free_dev(oal_uint32 ul_dev_idx)
{
    if (OAL_UNLIKELY(ul_dev_idx >= MAC_RES_MAX_DEV_NUM))
    {
        MAC_ERR_LOG(0, "mac_res_free_dev: ul_dev_idx >= MAC_RES_MAX_DEV_NUM");
        OAM_ERROR_LOG1(0, OAM_SF_ANY, "{mac_res_free_dev::invalid ul_dev_idx[%d].}", ul_dev_idx);

        return OAL_FAIL;
    }

    if(0 == g_st_mac_res.st_dev_res.auc_user_cnt[ul_dev_idx])
    {
        OAM_ERROR_LOG1(0, OAM_SF_ANY,"mac_res_free_dev::cnt==0! idx:%d",ul_dev_idx);
        oal_dump_stack();
        return OAL_SUCC;
    }

    (g_st_mac_res.st_dev_res.auc_user_cnt[ul_dev_idx])--;

    if (0 != g_st_mac_res.st_dev_res.auc_user_cnt[ul_dev_idx])
    {
        return OAL_SUCC;
    }

    /* �������ֵ��Ҫ��1���� */
    oal_queue_enqueue(&(g_st_mac_res.st_dev_res.st_queue), (oal_void *)((oal_uint)ul_dev_idx + 1));

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : mac_get_max_asoc_user
 ��������  : ��ȡ�������û���
 �������  : ��
 �������  : ��
 �� �� ֵ  : �������û���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��27��
    ��    ��   : zhangheng
    �޸�����   : �����ɺ���

*****************************************************************************/
#if (!defined(_PRE_PRODUCT_ID_HI110X_DEV))
    OAL_INLINE oal_uint16  mac_res_get_max_asoc_user(oal_void)
#else
    oal_uint16  mac_res_get_max_asoc_user(oal_void)
#endif
{
    return g_us_max_asoc_user;
}


/*lint -e19*/
oal_module_symbol(g_st_mac_res);
oal_module_symbol(mac_res_get_max_asoc_user);
oal_module_symbol(mac_res_set_max_asoc_user);
oal_module_symbol(g_us_max_asoc_user);
oal_module_symbol(mac_res_free_dev);
oal_module_symbol(mac_res_alloc_hmac_dev);
oal_module_symbol(mac_res_get_dev);
oal_module_symbol(mac_res_free_mac_user);
oal_module_symbol(mac_res_free_mac_vap);
oal_module_symbol(mac_res_free_hash);
/*lint +e19*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

