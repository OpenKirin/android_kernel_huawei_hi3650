/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oam_linux_netlink.c
  �� �� ��   : ����
  ��    ��   : z00241943
  ��������   : 2014��5��15��
  ����޸�   :
  ��������   : netlink�����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��5��15��
    ��    ��   : z00241943
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
#include "oam_ext_if.h"
#include "oam_linux_netlink.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_OAM_LINUX_NETLINK_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
oam_netlink_stru        g_st_netlink;

oam_netlink_proto_ops   g_st_netlink_ops;

/* �����ϱ�app�Ľṹ�� */
typedef struct
{
    oal_uint32      ul_daq_addr;         /* ���������׵�ַ */
    oal_uint32      ul_data_len;         /* ���������ܵĳ��� */
    oal_uint32      ul_unit_len;         /* ��Ԫ���ݵ���󳤶�:������(daq_unit_head)ͷ���� */
}oam_data_acq_info_stru;

/* ���ɵ�Ԫͷ�ṹ�� */
typedef struct
{
    oal_uint8                           en_send_type;        /* ���ɵ�Ԫ�������к� */
    oal_uint8                           uc_resv[3];
    oal_uint32                          ul_msg_sn;           /* ���ɵ�Ԫ�������к� */
    oal_uint32                          ul_data_len;         /* ��ǰ��Ԫ���� */
}oam_data_acq_data_head_stru;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : oam_netlink_ops_register
 ��������  : WALģ��������ģ���ṩ��ע��netlink��Ϣ������(���շ���)
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��17��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_netlink_ops_register(oam_nl_cmd_enum_uint8 en_type, oal_uint32 (*p_func)(oal_uint8 *puc_data, oal_uint32 ul_len))
{
    if (OAL_UNLIKELY(OAL_PTR_NULL == p_func))
    {
        OAL_IO_PRINT("oam_netlink_ops_register, p_func is null ptr.");
        return;
    }

    switch (en_type)
    {
        case OAM_NL_CMD_SDT:
            g_st_netlink_ops.p_oam_sdt_func = p_func;
            break;

        case OAM_NL_CMD_HUT:
            g_st_netlink_ops.p_oam_hut_func = p_func;
            break;

        case OAM_NL_CMD_ALG:
            g_st_netlink_ops.p_oam_alg_func = p_func;
            break;

        case OAM_NL_CMD_DAQ:
            g_st_netlink_ops.p_oam_daq_func = p_func;
            break;

        case OAM_NL_CMD_REG:
            g_st_netlink_ops.p_oam_reg_func = p_func;
            break;

        case OAM_NL_CMD_ACS:
            g_st_netlink_ops.p_oam_acs_func = p_func;
            break;

        case OAM_NL_CMD_PSTA:
            g_st_netlink_ops.p_oam_psta_func = p_func;
            break;

        default:
            OAL_IO_PRINT("oam_netlink_ops_register, err type = %d.", en_type);
            break;
    }
}

/*****************************************************************************
 �� �� ��  : oam_netlink_ops_unregister
 ��������  : OAMģ��������ģ���ṩ��ж��netlink��Ϣ������(���շ���)
 �������  : en_type: ģ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��22��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_netlink_ops_unregister(oam_nl_cmd_enum_uint8 en_type)
{
    switch (en_type)
    {
        case OAM_NL_CMD_SDT:
            g_st_netlink_ops.p_oam_sdt_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_HUT:
            g_st_netlink_ops.p_oam_hut_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_ALG:
            g_st_netlink_ops.p_oam_alg_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_DAQ:
            g_st_netlink_ops.p_oam_daq_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_REG:
            g_st_netlink_ops.p_oam_reg_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_ACS:
            g_st_netlink_ops.p_oam_acs_func = OAL_PTR_NULL;
            break;

        case OAM_NL_CMD_PSTA:
            g_st_netlink_ops.p_oam_psta_func = OAL_PTR_NULL;
            break;

        default:
            OAL_IO_PRINT("oam_netlink_ops_unregister::err type = %d.", en_type);
            break;
    }
}

/*****************************************************************************
 �� �� ��  : oam_netlink_kernel_recv
 ��������  : netlink��Ϣ���պ���(����: host app -> �ں�)
 �������  : pst_buf: ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_netlink_kernel_recv(oal_netbuf_stru *pst_buf)
{
    oal_netbuf_stru     *pst_netbuf;
    oal_nlmsghdr_stru   *pst_nlmsghdr;

    if (OAL_PTR_NULL == pst_buf)
    {
        OAL_IO_PRINT("oam_netlink_kernel_recv, pst_buf is null.");
        return;
    }

    pst_netbuf = oal_netbuf_get(pst_buf);

    while (OAL_NETBUF_LEN(pst_netbuf) >= OAL_NLMSG_SPACE(0))
    {
        pst_nlmsghdr = oal_nlmsg_hdr(pst_netbuf);

        g_st_netlink.ul_pid = pst_nlmsghdr->nlmsg_pid;

        switch (pst_nlmsghdr->nlmsg_type)
        {
            case OAM_NL_CMD_SDT:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_sdt_func)
                {
                    g_st_netlink_ops.p_oam_sdt_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;

            case OAM_NL_CMD_HUT:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_hut_func)
                {
                    g_st_netlink_ops.p_oam_hut_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;

            case OAM_NL_CMD_ALG:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_alg_func)
                {
                    g_st_netlink_ops.p_oam_alg_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;
            case OAM_NL_CMD_DAQ:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_daq_func)
                {
                    g_st_netlink_ops.p_oam_daq_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;
            case OAM_NL_CMD_REG:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_reg_func)
                {
                    g_st_netlink_ops.p_oam_reg_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;
            case OAM_NL_CMD_ACS:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_acs_func)
                {
                    g_st_netlink_ops.p_oam_acs_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;
            case OAM_NL_CMD_PSTA:
                if (OAL_PTR_NULL != g_st_netlink_ops.p_oam_psta_func)
                {
                    g_st_netlink_ops.p_oam_psta_func(OAL_NLMSG_DATA(pst_nlmsghdr), OAL_NLMSG_PAYLOAD(pst_nlmsghdr, 0));
                }
                break;
            default:
                // OAL_IO_PRINT("oam_netlink_kernel_recv, error nlmsg_type = %d.\n", pst_nlmsghdr->nlmsg_type);
                break;
        }

        oal_netbuf_pull(pst_netbuf, OAL_NLMSG_ALIGN(pst_nlmsghdr->nlmsg_len));
    }

    oal_netbuf_free(pst_netbuf);
}

/*****************************************************************************
 �� �� ��  : oam_netlink_kernel_send
 ��������  : netlink��Ϣ���ͺ���(����: �ں� -> host app)
 �������  : puc_data   : ��������
             ul_data_len: ���ݳ���
             en_type    : netlink msg����
 �������  : ��
 �� �� ֵ  : �ɹ�: ���͵��ֽ���(netlinkͷ + payload + padding)
             ʧ��: ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  oam_netlink_kernel_send(oal_uint8 *puc_data, oal_uint32 ul_data_len, oam_nl_cmd_enum_uint8 en_type)
{
#if (_PRE_OS_VERSION_RAW == _PRE_OS_VERSION)

	return 0;
#else

#if(_PRE_TARGET_PRODUCT_TYPE_1102COMMON == _PRE_CONFIG_TARGET_PRODUCT)
    /*TBD*/
    return 0;
#else
    oal_netbuf_stru     *pst_netbuf;
    oal_nlmsghdr_stru   *pst_nlmsghdr;
    oal_uint32           ul_size;
    oal_int32            l_ret;

    ul_size = OAL_NLMSG_SPACE(ul_data_len);
    pst_netbuf = oal_netbuf_alloc(ul_size, 0, WLAN_MEM_NETBUF_ALIGN);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return -1;
    }

    /* ��ʼ��netlink��Ϣ�ײ� */
    pst_nlmsghdr = oal_nlmsg_put(pst_netbuf, 0, 0, (oal_int32)en_type, (oal_int32)ul_data_len, 0);

    /* ���ÿ����ֶ� */
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
    OAL_NETLINK_CB(pst_netbuf).portid = 0;
#else
    OAL_NETLINK_CB(pst_netbuf).pid = 0;
#endif
    OAL_NETLINK_CB(pst_netbuf).dst_group = 0;

    /* ��������� */
    oal_memcopy(OAL_NLMSG_DATA(pst_nlmsghdr), puc_data, ul_data_len);

    /* �������� */
    l_ret = oal_netlink_unicast(g_st_netlink.pst_nlsk, pst_netbuf, g_st_netlink.ul_pid, OAL_MSG_DONTWAIT);

    return l_ret;

#endif /* _PRE_TARGET_PRODUCT_TYPE_1102COMMON == _PRE_CONFIG_TARGET_PRODUCT */
#endif /* _PRE_OS_VERSION_RAW == _PRE_OS_VERSION  */
}

/*****************************************************************************
 �� �� ��  : oam_netlink_kernel_send_ex
 ��������  : netlink��Ϣ���ͺ���(����: �ں� -> host app)
 �������  : puc_data_1st: ��������1
             puc_data_2nd: ��������2
             ul_len_1st  : ���ݳ���1
             ul_len_2nd  : ���ݳ���2
             en_type     : netlink msg����
 �������  : ��
 �� �� ֵ  : �ɹ�: ���͵��ֽ���(netlinkͷ + payload + padding)
             ʧ��: ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��17��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_int32  oam_netlink_kernel_send_ex(oal_uint8 *puc_data_1st, oal_uint8 *puc_data_2nd,
                                      oal_uint32 ul_len_1st, oal_uint32 ul_len_2nd,
                                      oam_nl_cmd_enum_uint8 en_type)
{
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3,10,44))
        /*TBD*/
        return 0;
#else

    oal_netbuf_stru     *pst_netbuf;
    oal_nlmsghdr_stru   *pst_nlmsghdr;
    oal_uint32           ul_size;
    oal_int32            l_ret;

    ul_size = OAL_NLMSG_SPACE(ul_len_1st + ul_len_2nd);
    pst_netbuf = oal_netbuf_alloc(ul_size, 0, WLAN_MEM_NETBUF_ALIGN);
    if (OAL_PTR_NULL == pst_netbuf)
    {
        return -1;
    }

    /* ��ʼ��netlink��Ϣ�ײ� */
    pst_nlmsghdr = oal_nlmsg_put(pst_netbuf, 0, 0, (oal_int32)en_type, (oal_int32)(ul_len_1st + ul_len_2nd), 0);

    /* ���ÿ����ֶ� */
    OAL_NETLINK_CB(pst_netbuf).pid = 0;
    OAL_NETLINK_CB(pst_netbuf).dst_group = 0;

    /* ��������� */
    oal_memcopy(OAL_NLMSG_DATA(pst_nlmsghdr), puc_data_1st, ul_len_1st);
    oal_memcopy((oal_uint8 *)OAL_NLMSG_DATA(pst_nlmsghdr) + ul_len_1st, puc_data_2nd, ul_len_2nd);

    /* �������� */
    l_ret = oal_netlink_unicast(g_st_netlink.pst_nlsk, pst_netbuf, g_st_netlink.ul_pid, OAL_MSG_DONTWAIT);

    return l_ret;
#endif
}

/*****************************************************************************
 �� �� ��  : oam_kernel_netlink_create
 ��������  : �ں�netlink��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�: OAL_SUCC
             ʧ��: ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  oam_netlink_kernel_create(oal_void)
{
    g_st_netlink.pst_nlsk = oal_netlink_kernel_create(&OAL_INIT_NET, OAM_NETLINK_ID, 0, oam_netlink_kernel_recv, OAL_PTR_NULL, OAL_THIS_MODULE);
    if (OAL_PTR_NULL == g_st_netlink.pst_nlsk)
    {
        OAL_IO_PRINT("oam_netlink_kernel_create, can not create netlink.");

        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_IO_PRINT("netlink create succ.");

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : oam_netlink_kernel_destroy
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��8��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  oam_netlink_kernel_release(oal_void)
{
    oal_netlink_kernel_release(g_st_netlink.pst_nlsk);

    g_st_netlink.ul_pid = 0;

    OAL_IO_PRINT("netlink release succ.");
}


/*lint -e578*//*lint -e19*/
oal_module_symbol(g_st_netlink_ops);
oal_module_symbol(oam_netlink_ops_register);
oal_module_symbol(oam_netlink_ops_unregister);
oal_module_symbol(oam_netlink_kernel_send);
oal_module_symbol(oam_netlink_kernel_send_ex);














#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

