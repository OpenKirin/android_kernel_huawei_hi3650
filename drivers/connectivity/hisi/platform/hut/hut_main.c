/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hut_main.c
  �� �� ��   : ����
  ��    ��   : mayuan
  ��������   : 2013��10��15��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��15��
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
#include "oam_ext_if.h"
#include "hal_ext_if.h"
#include "hut_main.h"


#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_HUT_MAIN_C


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ��������������� */
#define HUT_CMD_NAME_MAX_LEN   3

/* HUTģ�����������ڴ泤��(��λ: �ֽ�) */
#define HUT_MEM_MAX_LEN        (1024 * 640)   /* 640K */

/* netlink��Ϣ��󳤶�(���ڴ˳�����Ҫ��Ƭ) */
#if (_PRE_WLAN_REAL_CHIP == _PRE_WLAN_CHIP_SIM)
#define HUT_NLMSG_FRAG_THRESHOLD      (60*1024 - 100)
/* #define HUT_NLMSG_FRAG_THRESHOLD      (4 * 1024) */
#else
#define HUT_NLMSG_FRAG_THRESHOLD      8
#endif


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* ״̬����������ö�� */
typedef enum
{
    HUT_FSM_INPUT_TYPE_WM = 0,   /* д�ڴ� */

    HUT_FSM_INPUT_TYPE_BUTT
}hut_fms_input_type_enum;
typedef oal_uint8 hut_fsm_input_type_enum_uint8;

/* ״̬��״̬ö�� */
typedef enum
{
    HUT_FSM_STATE_INIT = 0,     /* ���ڷ�Ƭ֡�ĵ�һ֡ */
    HUT_FSM_STATE_IN_FRAG,      /* ���ڷ�Ƭ֡��(����һ֡��)������֡ */

    HUT_FSM_STATE_BUTT
}hut_fsm_state_enum;
typedef oal_uint8 hut_fsm_state_enum_uint8;


/*****************************************************************************
  3 �ṹ�嶨��
*****************************************************************************/
/* ״̬���ṹ�嶨��(д�ڴ�������õ���״̬��) */
typedef struct
{
    hut_fsm_state_enum_uint8    en_state;   /* ״̬ */
    oal_uint8                   auc_resv[3];
    oal_int32 (*hut_fsm_func[HUT_FSM_STATE_BUTT][HUT_FSM_INPUT_TYPE_BUTT])(oal_uint8 *puc_data, oal_void *p_param);   /* ��Ӧ������ */
}hut_fsm_stru;

/* ˽��������ڽṹ���� */
typedef struct
{
    oal_int8         *pc_cmd_name;                      /* �����ַ��� */
    oal_int32 (*p_hut_cmd_func)(oal_uint8 *puc_data);   /* �����Ӧ�Ĵ����� */
}hut_cmd_entry_stru;

typedef struct
{
    oal_uint32   ul_addr;
    oal_uint32   ul_val;
}hut_cmd_fmt_stru;

typedef struct
{
    oal_workqueue_stru   *pst_rx_workqueue;
    oal_work_stru         rx_work;
    oal_dlist_head_stru   st_list;
    oal_spin_lock_stru    st_spin_lock;
}hut_workqueue_stru;

typedef struct
{
    oal_uint8            *puc_data;
    oal_uint32            ul_data1;
    oal_uint32            ul_data2;
    oal_uint32            ul_data3;
    oal_uint32            ul_data4;
    oal_uint32            ul_data5;
    oal_dlist_head_stru   st_list;
}hut_rx_node;

typedef struct
{
    oal_dlist_head_stru   st_list;
    oal_spin_lock_stru    st_spin_lock;
}hut_intr_queue;

typedef struct
{
    oal_uint32                 *pul_prev_rx_dscr;
    oal_uint32                  ul_skb_start_addr;
    oal_uint32                 *pul_next_rx_dscr;
    oal_uint32                  ul_mac_hdr_start_addr;
    oal_uint32                  ul_payload_start_addr;
}hut_rx_buffer_addr_stru;


/*****************************************************************************
  4 ��������
*****************************************************************************/
OAL_STATIC oal_int32  hut_read_reg(oal_uint8 *puc_data);
OAL_STATIC oal_int32  hut_write_reg(oal_uint8 *puc_data);
OAL_STATIC oal_int32  hut_read_mem(oal_uint8 *puc_data);
OAL_STATIC oal_int32  hut_write_mem(oal_uint8 *puc_data);
OAL_STATIC oal_int32  hut_read_start_mem_addr(oal_uint8 *puc_data);


/*****************************************************************************
  5 ȫ�ֱ�������
*****************************************************************************/
/* ����������б� */
OAL_STATIC OAL_CONST hut_cmd_entry_stru g_ast_hut_cmd_ops[] =
{
    {"rr", hut_read_reg},             /* ���Ĵ������� */
    {"wr", hut_write_reg},            /* д�Ĵ������� */
    {"rm", hut_read_mem},             /* ���ڴ����� */
    {"wm", hut_write_mem},            /* д�ڴ����� */
    {"rd", hut_read_start_mem_addr}   /* ���ڴ���ʼ��ַ���� */
};

/* ����HUTģ�����ʱ���뵽���ڴ���ʼ��ַ(������HUTģ��ж��ʱ�ͷ��ڴ�) */
OAL_STATIC hut_mem_addr_stru g_st_base_addr;

/* HUTģ�鶨���tasklet(�ϱ��ж�ʱʹ��) */
OAL_STATIC oal_tasklet_stru   g_st_hut_tasklet;

/* ״̬��(д�ڴ�������õ���״̬��)*/
OAL_STATIC hut_fsm_stru  g_pa_hut_fsm;

/* �������� */
hut_workqueue_stru   g_st_hut_workqueue;

hut_cmd_fmt_stru   g_tmp;

/* �ж϶��У����ڱ����ж�״̬�Ĵ����ʹ���״̬�Ĵ��� */
hut_intr_queue       g_st_intr_queue;


/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : hut_read_reg
 ��������  : ���Ĵ���
 �������  : puc_data: ��������
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
OAL_STATIC oal_int32  hut_read_reg(oal_uint8 *puc_data)
{
    hal_to_dmac_device_stru   *pst_hal_device;
    hut_frag_hdr_stru          st_frag_hdr;
    oal_uint32                 ul_addr;
    oal_uint32                 ul_val;

    hal_get_hal_to_dmac_device(0, 0, &pst_hal_device);

    /***********
     ����֡��ʽ
    --------
    | ��ַ |
    --------
    | 4    |
    --------
    ************/

    ul_addr = (puc_data[3] << 24) | (puc_data[2] << 16) | (puc_data[1] << 8) | puc_data[0];

    hal_reg_info(pst_hal_device, ul_addr, &ul_val);

    /*******************************************************
     ��Ӧ֡��ʽ
    --------------------------------------------------------
    | bit_flag | bit_last | bit_resv | us_num | us_len| ֵ |
    --------------------------------------------------------
    | 1                              | 1      | 2     | 4  |
    --------------------------------------------------------
    ********************************************************/
    st_frag_hdr.bit_flag = 0;   /* ���ֶ� */
    st_frag_hdr.bit_last = 1;   /* ���һ�� */
    st_frag_hdr.us_len   = 4;


    return oam_netlink_kernel_send_ex((oal_uint8 *)&st_frag_hdr, (oal_uint8 *)&ul_val,
                    OAL_SIZEOF(st_frag_hdr), OAL_SIZEOF(ul_val), OAM_NL_CMD_HUT);
}

/*****************************************************************************
 �� �� ��  : hut_write_reg
 ��������  : д�Ĵ���
 �������  : puc_data: ��������
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32  hut_write_reg(oal_uint8 *puc_data)
{
    hal_to_dmac_device_stru   *pst_hal_device;
    hut_cmd_fmt_stru          *pst_cmd_fmt;

    hal_get_hal_to_dmac_device(0, 0, &pst_hal_device);

    /*************
     ����֡��ʽ
    -------------
    | ��ַ | ֵ |
    -------------
    | 4    | 4  |
    -------------
    **************/

    pst_cmd_fmt = (hut_cmd_fmt_stru *)puc_data;

    hal_reg_write(pst_hal_device, pst_cmd_fmt->ul_addr, pst_cmd_fmt->ul_val);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hut_read_mem
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��26��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32  hut_read_mem(oal_uint8 *puc_data)
{
    hut_rx_node   *pst_rx_node;

    pst_rx_node = oal_memalloc(OAL_SIZEOF(hut_rx_node));
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_rx_node))
    {
        HUT_ERR_LOG(0, "hut_read_mem, alloc memory failed.");

        return -1;
    }

    oal_spin_lock_bh(&g_st_hut_workqueue.st_spin_lock);

    pst_rx_node->puc_data = puc_data;
    oal_dlist_add_tail(&pst_rx_node->st_list, &g_st_hut_workqueue.st_list);

    oal_spin_unlock_bh(&g_st_hut_workqueue.st_spin_lock);

    return oal_queue_work(g_st_hut_workqueue.pst_rx_workqueue, &g_st_hut_workqueue.rx_work);
}

/*****************************************************************************
 �� �� ��  : hut_write_mem
 ��������  : д�ڴ�
 �������  : puc_data: ��������
 �������  : ��
 �� �� ֵ  : OAL_SUCC
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32  hut_write_mem(oal_uint8 *puc_data)
{
    hut_cmd_fmt_stru   *pst_cmd_fmt;
    oal_uint32         ul_virt_addr;

    /**********************
     ����֡��ʽ
    ----------------------
    | ��ַ | ���� | ֵ
    ----------------------
    | 4    | 4    | ���� ~
    ----------------------
    **********************/

    pst_cmd_fmt = (hut_cmd_fmt_stru *)puc_data;

    /* �����ַת�����ַ */
    ul_virt_addr = (oal_uint32)(OAL_PHY_TO_VIRT_ADDR(pst_cmd_fmt->ul_addr));

    oal_memcopy((oal_uint8 *)ul_virt_addr, puc_data + OAL_SIZEOF(hut_cmd_fmt_stru), pst_cmd_fmt->ul_val);

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hut_read_start_mem_addr
 ��������  : ���ڴ���ʼ��ַ
 �������  : puc_data: ��������
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
OAL_STATIC oal_int32  hut_read_start_mem_addr(oal_uint8 *puc_data)
{
    hut_frag_hdr_stru   st_frag_hdr;
    hut_cmd_fmt_stru    st_cmd_fmt;

    /**************************************************************
     ��Ӧ֡��ʽ
    ---------------------------------------------------------------
    | bit_flag | bit_last | bit_resv | us_num | us_len| ��ַ | ֵ |
    ---------------------------------------------------------------
    | 1                              | 1      | 2     | 4    | 4  |
    ---------------------------------------------------------------
    ***************************************************************/
    st_frag_hdr.bit_flag = 0;   /* ���ֶ� */
    st_frag_hdr.bit_last = 1;   /* ���һ�� */
    st_frag_hdr.us_len   = OAL_SIZEOF(hut_cmd_fmt_stru);

    /* ���ص��������ַ */
    st_cmd_fmt.ul_addr = OAL_VIRT_TO_PHY_ADDR((oal_void *)g_st_base_addr.puc_base_addr_align);
    st_cmd_fmt.ul_val  = HUT_MEM_MAX_LEN;

    return oam_netlink_kernel_send_ex((oal_uint8 *)&st_frag_hdr, (oal_uint8 *)&st_cmd_fmt,
                    OAL_SIZEOF(st_frag_hdr), OAL_SIZEOF(st_cmd_fmt), OAM_NL_CMD_HUT);
}

/*****************************************************************************
 �� �� ��  : hut_irq_isr_all
 ��������  : HUT�жϷ���������(�ж��ϰ벿)
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
#if 0
OAL_STATIC oal_void  hut_irq_isr_all(oal_void)
{
    hal_to_dmac_device_stru   *pst_hal_device;
    hut_rx_node               *pst_rx_node;
    oal_uint                   ul_flag;

    HUT_INFO_LOG(0, "hut_irq_isr_all");

    hal_get_hal_to_dmac_device(0, 0, &pst_hal_device);

    /* ���ж� */
    oal_irq_disable();

    pst_rx_node = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_EVENT, OAL_SIZEOF(hut_rx_node), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_rx_node))
    {
        HUT_ERR_LOG(0, "hut_irq_isr_all, alloc memory failed.");

        oal_irq_restore();

        return;
    }

    /* ���ж� */
    oal_irq_restore();

    /* ���������ж� */
    oal_spin_lock_irq_save(&g_st_intr_queue.st_spin_lock, &ul_flag);

    /* ��ȡ״̬�Ĵ��� */
    hal_get_mac_int_status(pst_hal_device, &pst_rx_node->ul_data1);

    /* ��ȡ����״̬�Ĵ��� */
    hal_get_mac_error_int_status(pst_hal_device, &pst_rx_node->ul_data2);

    OAL_IO_PRINT("stat = 0x%x, err = 0x%x\n", pst_rx_node->ul_data1, pst_rx_node->ul_data2);

    /* ���ж�״̬�Ĵ��� */
    hal_clear_mac_int_status(pst_hal_device, 0xFFFFFFFF);

    /* �����״̬�Ĵ��� */
    hal_clear_mac_error_int_status(pst_hal_device, 0xFFFFFFFF);

    oal_dlist_add_tail(&pst_rx_node->st_list, &g_st_intr_queue.st_list);

    /* ���������ж� */
    oal_spin_unlock_irq_restore(&g_st_intr_queue.st_spin_lock, &ul_flag);

    /* ����һ��tasklet */
    oal_task_sched(&g_st_hut_tasklet);
}
#endif

OAL_STATIC oal_void  hut_irq_isr_all(oal_void)
{
    hal_to_dmac_device_stru   *pst_hal_device;
    hut_rx_node               *pst_rx_node;
    oal_uint                   ul_flag;
    oal_uint32                 ul_base_addr;
    oal_uint32                *pul_tx_dscr;
    oal_uint32                *pul_rx_dscr;
    oal_uint                   ul_irq_flag;
    hal_error_state_stru       st_state;

    HUT_INFO_LOG(0, "hut_irq_isr_all");

    hal_get_hal_to_dmac_device(0, 0, &pst_hal_device);

    /* ���ж� */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_HIIA);

    pst_rx_node = OAL_MEM_ALLOC(OAL_MEM_POOL_ID_EVENT, OAL_SIZEOF(hut_rx_node), OAL_TRUE);
    if (OAL_UNLIKELY(OAL_PTR_NULL == pst_rx_node))
    {
        HUT_ERR_LOG(0, "hut_irq_isr_all, alloc memory failed.");

        oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_HIIA);

        return;
    }

    /* ���ж� */
    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_HIIA);

    /* ���������ж� */
    oal_spin_lock_irq_save(&g_st_intr_queue.st_spin_lock, &ul_flag);

    /* ��ȡ״̬�Ĵ��� */
    hal_get_mac_int_status(pst_hal_device, &pst_rx_node->ul_data1);

    /* ��ȡ����״̬�Ĵ��� */
    hal_get_mac_error_int_status(pst_hal_device, &st_state);
    pst_rx_node->ul_data2 = st_state.ul_error1_val;

    if (pst_rx_node->ul_data1 & (1 << 0))   /* ��������ж� */
    {
        hal_reg_info(pst_hal_device, 0x20002420, &pst_rx_node->ul_data3);
        hal_reg_info(pst_hal_device, 0x20002418, &pst_rx_node->ul_data4);

        ul_base_addr = (oal_uint32)OAL_PHY_TO_VIRT_ADDR(pst_rx_node->ul_data3);

        OAL_IO_PRINT("hut_irq_isr_all rx, ul_base_addr = 0x%x.\n", ul_base_addr);

        pul_rx_dscr = (oal_uint32 *)ul_base_addr;

        pst_rx_node->ul_data5 = pul_rx_dscr[4];

        //hal_dump_rx_dscr(pst_hal_device, pul_rx_dscr);
    }
    else if (pst_rx_node->ul_data1 & (1 << 1))   /* ��������ж� */
    {
        hal_reg_info(pst_hal_device, 0x20002424, &pst_rx_node->ul_data3);
        hal_reg_info(pst_hal_device, 0x20002428, &pst_rx_node->ul_data4);

        ul_base_addr = (oal_uint32)OAL_PHY_TO_VIRT_ADDR(pst_rx_node->ul_data3);

        OAL_IO_PRINT("hut_irq_isr_all tx, ul_base_addr = 0x%x.\n", ul_base_addr);

        pul_tx_dscr = (oal_uint32 *)ul_base_addr;

        pst_rx_node->ul_data5 = pul_tx_dscr[7];
    }

    OAL_IO_PRINT("stat = 0x%x, err = 0x%x, ptr = 0x%x, count = 0x%x.\n",
        pst_rx_node->ul_data1, pst_rx_node->ul_data2, pst_rx_node->ul_data3, pst_rx_node->ul_data4);

    /* �����״̬�Ĵ��� */
    hal_reg_write(pst_hal_device, 0x20002410, pst_rx_node->ul_data2);

    /* ���ж�״̬�Ĵ��� */
    hal_reg_write(pst_hal_device,0x20002404, pst_rx_node->ul_data1);

    oal_dlist_add_tail(&pst_rx_node->st_list, &g_st_intr_queue.st_list);

    /* ���������ж� */
    oal_spin_unlock_irq_restore(&g_st_intr_queue.st_spin_lock, &ul_flag);

    /* ����һ��tasklet */
    oal_task_sched(&g_st_hut_tasklet);
}

/*****************************************************************************
 �� �� ��  : hut_report_in
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��1��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hut_report_in(hut_rx_node *pst_rx_node)
{
    hal_to_dmac_device_stru   *pst_hal_device;
    hut_frag_hdr_stru          st_frag_hdr;
    oal_uint8                  auc_buf[22];
    oal_uint32                 ul_intr_status;
    oal_uint32                 ul_err_intr_stat;
    oal_uint32                 ul_dscr_ptr;
    oal_uint32                 ul_mpdu_cnt;
    oal_uint32                 ul_status;
    oal_uint                   ul_irq_flag;

    HUT_INFO_LOG(0, "hut_report_in, raise interrupt");

    hal_get_hal_to_dmac_device(0, 0, &pst_hal_device);

    /*******************************************************
     ��Ӧ֡��ʽ
    --------------------------------------------------------
    | bit_flag | bit_last | bit_resv | us_num | us_len| ֵ |
    --------------------------------------------------------
    | 1                              | 1      | 2     | 2  |
    --------------------------------------------------------
    *********************************************************/
    st_frag_hdr.bit_flag = 0;   /* ���ֶ� */
    st_frag_hdr.bit_last = 1;   /* ���һ�� */
    st_frag_hdr.us_len   = OAL_SIZEOF(auc_buf);

    auc_buf[0] = 'i';
    auc_buf[1] = 'n';

    /* ��ȡ״̬�Ĵ��� */
    ul_intr_status = pst_rx_node->ul_data1;

    auc_buf[2] = ul_intr_status & 0xFF;
    auc_buf[3] = (ul_intr_status >> 8) & 0xFF;
    auc_buf[4] = (ul_intr_status >> 16) & 0xFF;
    auc_buf[5] = (ul_intr_status >> 24) & 0xFF;

    /* ��ȡ����״̬�Ĵ��� */
    ul_err_intr_stat = pst_rx_node->ul_data2;

    auc_buf[6] = ul_err_intr_stat & 0xFF;
    auc_buf[7] = (ul_err_intr_stat >> 8) & 0xFF;
    auc_buf[8] = (ul_err_intr_stat >> 16) & 0xFF;
    auc_buf[9] = (ul_err_intr_stat >> 24) & 0xFF;

    /* ��ȡtx/rx mpdu count */
    ul_mpdu_cnt = pst_rx_node->ul_data4;

    auc_buf[10] = ul_mpdu_cnt & 0xFF;
    auc_buf[11] = (ul_mpdu_cnt >> 8) & 0xFF;
    auc_buf[12] = (ul_mpdu_cnt >> 16) & 0xFF;
    auc_buf[13] = (ul_mpdu_cnt >> 24) & 0xFF;

    /* ��ȡtx/rx frame ptr */
    ul_dscr_ptr = pst_rx_node->ul_data3;

    auc_buf[14] = ul_dscr_ptr & 0xFF;
    auc_buf[15] = (ul_dscr_ptr >> 8) & 0xFF;
    auc_buf[16] = (ul_dscr_ptr >> 16) & 0xFF;
    auc_buf[17] = (ul_dscr_ptr >> 24) & 0xFF;

    /* ��ȡstatus */
    ul_status = ul_dscr_ptr = pst_rx_node->ul_data5;

    auc_buf[18] = ul_status & 0xFF;
    auc_buf[19] = (ul_status >> 8) & 0xFF;
    auc_buf[20] = (ul_status >> 16) & 0xFF;
    auc_buf[21] = (ul_status >> 24) & 0xFF;

    /* �ж��ϰ벿�������¼���������Ҫ���ж� */
    oal_irq_save(&ul_irq_flag, OAL_5115IRQ_HRI);

    OAL_MEM_FREE(pst_rx_node, OAL_TRUE);

    oal_irq_restore(&ul_irq_flag, OAL_5115IRQ_HRI);

    oam_netlink_kernel_send_ex((oal_uint8 *)&st_frag_hdr, (oal_uint8 *)auc_buf,
                    OAL_SIZEOF(st_frag_hdr), OAL_SIZEOF(auc_buf), OAM_NL_CMD_HUT);
}

/*****************************************************************************
 �� �� ��  : hut_tasklet_handler
 ��������  : HUT�жϷ�������°벿(�����ϱ��ж�)
 �������  : l_data
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hut_tasklet_handler(oal_uint l_data)
{
    oal_dlist_head_stru   *pst_entry;
    hut_rx_node           *pst_rx_node;
    oal_uint               ul_flag;

    HUT_INFO_LOG(0, "hut_tasklet_handler start.");

    /* ���������ж� */
    oal_spin_lock_irq_save(&g_st_intr_queue.st_spin_lock, &ul_flag);

    while (!oal_dlist_is_empty(&g_st_intr_queue.st_list))
    {
        pst_entry = g_st_intr_queue.st_list.pst_next;
        oal_dlist_delete_entry(pst_entry);
        oal_spin_unlock_irq_restore(&g_st_intr_queue.st_spin_lock, &ul_flag);

        pst_rx_node = OAL_DLIST_GET_ENTRY(pst_entry, hut_rx_node, st_list);
        hut_report_in(pst_rx_node);

        oal_spin_lock_irq_save(&g_st_intr_queue.st_spin_lock, &ul_flag);
    }

    /* ���������ж� */
    oal_spin_unlock_irq_restore(&g_st_intr_queue.st_spin_lock, &ul_flag);
}

/*****************************************************************************
 �� �� ��  : hut_get_cmd_name
 ��������  : �������ִ�Ŀ�ĵ�ַ������Դ��ַ
 �������  : pc_src: Դ��ַ
 �������  : pc_dst: Ŀ�ĵ�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_void hut_get_cmd_name(oal_int8 *pc_dst, oal_int8 *pc_src)
{
    pc_dst[0] = pc_src[0];
    pc_dst[1] = pc_src[1];
    pc_dst[2] = '\0';
}

/*****************************************************************************
 �� �� ��  : hut_get_cmd_id
 ��������  : ���������ֻ�ȡ����ID
 �������  : puc_data  : ��������
 �������  : puc_cmd_id: ����ID
 �� �� ֵ  : �ɹ�: OAL_SUCC
 ���ú���  : ʧ��: OAL_FAIL
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��16��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC OAL_INLINE oal_uint32  hut_get_cmd_id(oal_uint8 *puc_data, oal_uint8 *puc_cmd_id)
{
    oal_uint8   uc_cmd_idx;
    oal_int8    ac_cmd[HUT_CMD_NAME_MAX_LEN];

    /* ��ȡ������ */
    hut_get_cmd_name(ac_cmd, (oal_int8 *)puc_data);

    for (uc_cmd_idx = 0; uc_cmd_idx < OAL_ARRAY_SIZE(g_ast_hut_cmd_ops); uc_cmd_idx++)
    {
        /* ���������ֲ�������ID */
        if (!oal_strcmp(g_ast_hut_cmd_ops[uc_cmd_idx].pc_cmd_name, ac_cmd))
        {
            *puc_cmd_id = uc_cmd_idx;

            return OAL_SUCC;
        }
    }

    return OAL_FAIL;
}

/*****************************************************************************
 �� �� ��  : hut_non_frag_msg_recv
 ��������  : ����δ�ֶ�֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��22��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hut_non_frag_msg_recv(oal_uint8 *puc_data, oal_uint32 ul_len)
{
    oal_uint8    uc_cmd_id;
    oal_uint32   ul_ret;

    /***********************
    ������ݸ�ʽ
    ----------------------
    | Byte 0-1 | Byte 2 ~
    ----------------------
    |  ������  |
    ----------------------
    ***********************/
    ul_ret = hut_get_cmd_id(puc_data, &uc_cmd_id);
    if (OAL_SUCC != ul_ret)
    {
        HUT_WARNING_VAR(0, "hut_receive_msg, can not find cmd id, err code = %d.", ul_ret);

        return ul_ret;
    }

    return (oal_uint32)g_ast_hut_cmd_ops[uc_cmd_id].p_hut_cmd_func(puc_data + 2);
}

/*****************************************************************************
 �� �� ��  : hut_frag_write_mem
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32  hut_1st_frag_write_mem(oal_uint8 *puc_data, oal_void *p_param)
{
    hut_frag_hdr_stru   *pst_frag_hdr;
    hut_cmd_fmt_stru    *pst_cmd_fmt;
    oal_uint32           ul_virt_addr;
    oal_uint32           ul_write_len;

    pst_frag_hdr = (hut_frag_hdr_stru *)puc_data;

    HUT_INFO_VAR(0, "hut_1st_frag_write_mem, bit_flag = %d, bit_last = %d, us_len = %d.",
                 pst_frag_hdr->bit_flag, pst_frag_hdr->bit_last, pst_frag_hdr->us_len);


    /* ����϶�������ִ�еĵ� */
    if (1 == pst_frag_hdr->bit_last)
    {
        g_pa_hut_fsm.en_state = HUT_FSM_STATE_INIT;
    }

    g_pa_hut_fsm.en_state = HUT_FSM_STATE_IN_FRAG;

    puc_data += OAL_SIZEOF(hut_frag_hdr_stru) + 2;
    pst_cmd_fmt = (hut_cmd_fmt_stru *)puc_data;

    HUT_INFO_VAR(0, "hut_1st_frag_write_mem, addr = 0x%x, len = %d.", pst_cmd_fmt->ul_addr, pst_cmd_fmt->ul_val);

    /* �����ַת�����ַ */
    ul_virt_addr = (oal_uint32)(OAL_PHY_TO_VIRT_ADDR(pst_cmd_fmt->ul_addr));

    /* ��һ��д�볤�� = frag_hdr->us_len - 2("wm") - 4(��ַ) - 4(����) */
    ul_write_len = pst_frag_hdr->us_len - 2 - OAL_SIZEOF(hut_cmd_fmt_stru);

    oal_memcopy((oal_uint8 *)ul_virt_addr, puc_data + OAL_SIZEOF(hut_cmd_fmt_stru), ul_write_len);

    g_tmp.ul_addr = ul_virt_addr + ul_write_len;

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hut_2nd_frag_write_mem
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32  hut_2nd_frag_write_mem(oal_uint8 *puc_data, oal_void *p_param)
{
    hut_frag_hdr_stru   *pst_frag_hdr;
    oal_uint32           ul_virt_addr;
    oal_uint32           ul_len;

    pst_frag_hdr = (hut_frag_hdr_stru *)puc_data;

    HUT_INFO_VAR(0, "hut_2nd_frag_write_mem, bit_flag = %d, bit_last = %d, us_len = %d.",
                 pst_frag_hdr->bit_flag, pst_frag_hdr->bit_last, pst_frag_hdr->us_len);

    HUT_INFO_VAR(0, "hut_2nd_frag_write_mem, g_tmp.ul_addr = 0x%x, g_tmp.ul_val = %d.", g_tmp.ul_addr, g_tmp.ul_val);

    ul_virt_addr = g_tmp.ul_addr;

    /* �ڶ���д�볤�� = frag_hdr->us_len*/
    ul_len = pst_frag_hdr->us_len;

    oal_memcopy((oal_uint8 *)ul_virt_addr, puc_data + OAL_SIZEOF(hut_frag_hdr_stru), ul_len);

    g_tmp.ul_addr = ul_virt_addr + ul_len;

    if (1 == pst_frag_hdr->bit_last)
    {
        g_pa_hut_fsm.en_state = HUT_FSM_STATE_INIT;
    }

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hut_frag_msg_recv
 ��������  : ����ֶ�֡
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��22��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_uint32  hut_frag_msg_recv(oal_uint8 *puc_data, oal_uint32 ul_len)
{
    /* Ŀǰ�ֶε�ֻ֡��д�ڴ�(wm) */
    return (oal_uint32)g_pa_hut_fsm.hut_fsm_func[g_pa_hut_fsm.en_state][HUT_FSM_INPUT_TYPE_WM](puc_data, OAL_PTR_NULL);
}

#ifdef _PRE_DEBUG_MODE
/*****************************************************************************
 �� �� ��  : hut_debug_info
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��25��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hut_debug_info(oal_uint8 *puc_data, oal_uint32 ul_len)
{
    hut_frag_hdr_stru   *pst_frag_hdr;
    oal_int8             ac_cmd[HUT_CMD_NAME_MAX_LEN];

    pst_frag_hdr = (hut_frag_hdr_stru *)puc_data;

    HUT_INFO_VAR(0, "hut_debug_info, bit_flag = %d, bit_last = %d, us_len = %d.",
                 pst_frag_hdr->bit_flag, pst_frag_hdr->bit_last, pst_frag_hdr->us_len);

    puc_data += OAL_SIZEOF(hut_frag_hdr_stru);

    if (0 == pst_frag_hdr->bit_flag)
    {
        /* ��ȡ������ */
        hut_get_cmd_name(ac_cmd, (oal_int8 *)puc_data);

        HUT_INFO_VAR(0, "hut_debug_info, command is %s.", ac_cmd);
    }
}
#endif

/*****************************************************************************
 �� �� ��  : hut_receive_msg
 ��������  : HUTģ��netlink���մ�����ں���
 �������  : puc_data: ��������
             ul_len  : ���ݳ���
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_uint32  hut_receive_msg(oal_uint8 *puc_data, oal_uint32 ul_len)
{
    hut_frag_hdr_stru   *pst_frag_hdr;

#ifdef _PRE_DEBUG_MODE
    hut_debug_info(puc_data, ul_len);
#endif

    pst_frag_hdr = (hut_frag_hdr_stru *)puc_data;

    /* ���ֶ� */
    if (0 == pst_frag_hdr->bit_flag)
    {
        /****************************************************************
         ��θ�ʽ
        -----------------------------------------------------------------
        | bit_flag | bit_last | bit_resv | us_num | us_len| ������ | ֵ |
        -----------------------------------------------------------------
        | 1                              | 1      | 2     | 2      | var
        -----------------------------------------------------------------
        *****************************************************************/
        return hut_non_frag_msg_recv(puc_data + OAL_SIZEOF(hut_frag_hdr_stru), ul_len);
    }
    /* �ֶ� */
    else
    {
        return hut_frag_msg_recv(puc_data, ul_len);
    }
}

/*****************************************************************************
 �� �� ��  : hut_fsm_null_fn
 ��������  : �պ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_int32  hut_fsm_null_fn(oal_uint8 *puc_data, oal_void *p_param)
{
    /* ʲô������ */

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hut_read_mem_and_report
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��26��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hut_report_mem(oal_uint8 *puc_data)
{
    hut_frag_hdr_stru    st_frag_hdr;
    hut_cmd_fmt_stru    *pst_cmd_fmt;
    oal_uint32           ul_virt_addr;
    oal_uint32           ul_send_len;
    oal_uint32           ul_remain_len;
    oal_int32            l_ret;

    hal_to_dmac_device_stru   *pst_hal_device;
    hal_tx_dscr_stru          *pst_dscr;

    struct hut_frag_hdr_ex
    {
        hut_frag_hdr_stru   st_hdr;
        oal_uint32          ul_len;
    }st_frag_hdr_ex = {{0}, 0};

    hal_get_hal_to_dmac_device(0, 0, &pst_hal_device);

    /***************
     ����֡��ʽ
    ---------------
    | ��ַ | ���� |
    ---------------
    | 4    | 4    |
    ---------------
    ****************/

    HUT_INFO_LOG(0, "hut_workqueu_handler start.");

    pst_cmd_fmt = (hut_cmd_fmt_stru *)puc_data;

    /* �����ַת�����ַ */
    ul_virt_addr = (oal_uint32)(OAL_PHY_TO_VIRT_ADDR(pst_cmd_fmt->ul_addr));

    HUT_INFO_VAR(0, "hut_read_mem, pst_cmd_fmt->ul_addr = 0x%x, pst_cmd_fmt->ul_val = %d.", pst_cmd_fmt->ul_addr, pst_cmd_fmt->ul_val);

    /******************************************************************
     ��Ӧ֡��ʽ
    -------------------------------------------------------------------
    | bit_flag | bit_last | bit_resv | us_num | us_len | ���� | ֵ    |
    -------------------------------------------------------------------
    | 1                              | 1      | 2      | 4    | ���� ~
    -------------------------------------------------------------------
    *******************************************************************/
    if (pst_cmd_fmt->ul_val > HUT_NLMSG_FRAG_THRESHOLD)
    {
        st_frag_hdr_ex.st_hdr.bit_flag = 1;   /* �ֶ� */
        st_frag_hdr_ex.st_hdr.bit_last = 0;   /* �м�� */
        st_frag_hdr_ex.st_hdr.us_len   = (oal_uint16)(OAL_SIZEOF(pst_cmd_fmt->ul_val) + HUT_NLMSG_FRAG_THRESHOLD);  /* 4�ֽڳ����ֶ� + ֵ�ĳ���(�ɳ����ֶ�ָ��) */
        ul_send_len = HUT_NLMSG_FRAG_THRESHOLD;
    }
    else
    {
        st_frag_hdr_ex.st_hdr.bit_flag = 0;   /* ���ֶ� */
        st_frag_hdr_ex.st_hdr.bit_last = 1;   /* ���һ�� */
        st_frag_hdr_ex.st_hdr.us_len   = (oal_uint16)(OAL_SIZEOF(pst_cmd_fmt->ul_val) + pst_cmd_fmt->ul_val);  /* 4�ֽڳ����ֶ� + ֵ�ĳ���(�ɳ����ֶ�ָ��) */
        ul_send_len = pst_cmd_fmt->ul_val;
    }

    st_frag_hdr_ex.ul_len = pst_cmd_fmt->ul_val;

    /* debug */
    OAL_IO_PRINT("hut_report_mem, ul_virt_addr = 0x%x.\n", ul_virt_addr);
    pst_dscr = (hal_tx_dscr_stru *)((oal_uint8 *)ul_virt_addr - OAL_SIZEOF(oal_dlist_head_stru));
    hal_dump_tx_dscr(pst_hal_device, (oal_uint32 *)pst_dscr);
    /* debug */


    l_ret = oam_netlink_kernel_send_ex((oal_uint8 *)&st_frag_hdr_ex, (oal_uint8 *)ul_virt_addr,
                    OAL_SIZEOF(st_frag_hdr_ex), ul_send_len, OAM_NL_CMD_HUT);

    ul_virt_addr += ul_send_len;

    ul_remain_len = (pst_cmd_fmt->ul_val > HUT_NLMSG_FRAG_THRESHOLD) ? (pst_cmd_fmt->ul_val - HUT_NLMSG_FRAG_THRESHOLD) : 0;

    HUT_INFO_VAR(0, "hut_read_mem, ul_remain_len = %d.", ul_remain_len);

    while (ul_remain_len)
    {
        oal_msleep(100);

        if (ul_remain_len > HUT_NLMSG_FRAG_THRESHOLD)
        {
            st_frag_hdr.bit_flag = 1;  /* �ֶ� */
            st_frag_hdr.bit_last = 0;  /* �м�� */
            st_frag_hdr.us_len   = HUT_NLMSG_FRAG_THRESHOLD;
            ul_send_len          = HUT_NLMSG_FRAG_THRESHOLD;
        }
        else
        {
            st_frag_hdr.bit_flag = 1;  /* �ֶ� */
            st_frag_hdr.bit_last = 1;  /* ���һ���� */
            st_frag_hdr.us_len   = (oal_uint16)ul_remain_len;
            ul_send_len          = ul_remain_len;
        }

        /******************************************************************
         ��Ӧ֡��ʽ
        -------------------------------------------------------------------
        | bit_flag | bit_last | bit_resv | us_num | us_len | ֵ
        -------------------------------------------------------------------
        | 1                              | 1      | 2      | ���� ~
        -------------------------------------------------------------------
        *******************************************************************/
        /*lint -e716*/
        while (1)
        {
            l_ret = oam_netlink_kernel_send_ex((oal_uint8 *)&st_frag_hdr, (oal_uint8 *)ul_virt_addr,
                        OAL_SIZEOF(st_frag_hdr), ul_send_len, OAM_NL_CMD_HUT);

            if (l_ret < 0)
            {
                oal_msleep(100);
            }
            else
            {
                break;
            }
        }

        ul_virt_addr += ul_send_len;

        ul_remain_len = ul_remain_len > HUT_NLMSG_FRAG_THRESHOLD ? ul_remain_len - HUT_NLMSG_FRAG_THRESHOLD : 0;

        HUT_INFO_VAR(0, "hut_read_mem2, ul_remain_len = %d.", ul_remain_len);
    }
}

/*****************************************************************************
 �� �� ��  : hut_workqueu_handler
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��28��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hut_workqueu_handler(oal_work_stru *pst_work)
{
    oal_dlist_head_stru   *pst_entry;
    hut_rx_node           *pst_rx_node;

    oal_spin_lock_bh(&g_st_hut_workqueue.st_spin_lock);

    while (!oal_dlist_is_empty(&g_st_hut_workqueue.st_list))
    {
        pst_entry = g_st_hut_workqueue.st_list.pst_next;
        oal_dlist_delete_entry(pst_entry);
        oal_spin_unlock_bh(&g_st_hut_workqueue.st_spin_lock);

        pst_rx_node = OAL_DLIST_GET_ENTRY(pst_entry, hut_rx_node, st_list);
        hut_report_mem(pst_rx_node->puc_data);
        oal_free(pst_rx_node);

        oal_spin_lock_bh(&g_st_hut_workqueue.st_spin_lock);
    }

    oal_spin_unlock_bh(&g_st_hut_workqueue.st_spin_lock);
}


/*****************************************************************************
 �� �� ��  : hut_fsm_init
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��23��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
OAL_STATIC oal_void  hut_fsm_init(hut_fsm_stru *pst_fsm)
{
    hut_fsm_state_enum_uint8        en_state;
    hut_fsm_input_type_enum_uint8   en_input;

    for (en_state = 0; en_state < HUT_FSM_STATE_BUTT; en_state++)
    {
        for (en_input = 0; en_input < HUT_FSM_INPUT_TYPE_BUTT; en_input++)
        {
            pst_fsm->hut_fsm_func[en_state][en_input] = hut_fsm_null_fn;
        }
    }

    /*
    +----------------------------------+-------------------------
     | FSM State                        | FSM Function
     +----------------------------------+------------------------
     | HUT_FSM_STATE_INIT               | hut_1st_frag_write_mem
     | HUT_FSM_STATE_IN_FRAG            | hut_2nd_frag_write_mem
     +----------------------------------+------------------------
    */
    pst_fsm->hut_fsm_func[HUT_FSM_STATE_INIT][HUT_FSM_INPUT_TYPE_WM] = hut_1st_frag_write_mem;
    pst_fsm->hut_fsm_func[HUT_FSM_STATE_IN_FRAG][HUT_FSM_INPUT_TYPE_WM] = hut_2nd_frag_write_mem;

    /* ����״̬����ʼ״̬ */
    pst_fsm->en_state = HUT_FSM_STATE_INIT;
}

/*****************************************************************************
 �� �� ��  : hut_set_rx_dscr_queue_circle
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��21��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hut_set_rx_dscr_queue_circle(oal_void)
{
    hal_to_dmac_device_stru         *pst_hal_device;
    hal_rx_dscr_queue_header_stru   *pst_rx_dscr_queue;
    hut_rx_buffer_addr_stru         *pst_rx_dscr_addr;
    hal_rx_dscr_queue_id_enum_uint8  en_queue_num;

    hal_get_hal_to_dmac_device(0, 0, &pst_hal_device);

    for (en_queue_num = 0; en_queue_num < HAL_RX_DSCR_QUEUE_ID_BUTT; en_queue_num++)
    {
        pst_rx_dscr_queue = &(pst_hal_device->ast_rx_dscr_queue[en_queue_num]);

        pst_rx_dscr_addr = (hut_rx_buffer_addr_stru *)pst_rx_dscr_queue->pul_element_tail;

        pst_rx_dscr_addr->pul_next_rx_dscr =
            (oal_uint32 *)OAL_DSCR_VIRT_TO_PHY(pst_rx_dscr_queue->pul_element_head);
    }
}

/*****************************************************************************
 �� �� ��  : hut_set_rx_dscr_queue_uncircle
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��21��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hut_set_rx_dscr_queue_uncircle(void)
{
    hal_to_dmac_device_stru         *pst_hal_device;
    hal_rx_dscr_queue_header_stru   *pst_rx_dscr_queue;
    hut_rx_buffer_addr_stru         *pst_rx_dscr_addr;
    hal_rx_dscr_queue_id_enum_uint8  en_queue_num;

    hal_get_hal_to_dmac_device(0, 0, &pst_hal_device);

    for (en_queue_num = 0; en_queue_num < HAL_RX_DSCR_QUEUE_ID_BUTT; en_queue_num++)
    {
        pst_rx_dscr_queue = &(pst_hal_device->ast_rx_dscr_queue[en_queue_num]);

        pst_rx_dscr_addr = (hut_rx_buffer_addr_stru *)pst_rx_dscr_queue->pul_element_tail;

        pst_rx_dscr_addr->pul_next_rx_dscr = OAL_PTR_NULL;
    }
}

/*****************************************************************************
 �� �� ��  : hut_main_init
 ��������  : HUTģ���ʼ�������
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
oal_int32 hut_main_init(oal_void)
{
    oal_uint8 *puc_base_addr = OAL_PTR_NULL;

    puc_base_addr = (oal_uint8 *)oal_memalloc(HUT_MEM_MAX_LEN + 3);
    if (OAL_PTR_NULL == puc_base_addr)
    {
        HUT_ERR_LOG(0, "hut_main_init, memory allocation fail.");

        return (oal_int32)OAL_ERR_CODE_ALLOC_MEM_FAIL;
    }

    /* ��ʼ��״̬�� */
    hut_fsm_init(&g_pa_hut_fsm);

    /* ��¼�ڴ�������ʼ��ַ */
    g_st_base_addr.puc_base_addr_origin = puc_base_addr;

    puc_base_addr = (oal_uint8 *)OAL_GET_4BYTE_ALIGN_VALUE((oal_uint32)puc_base_addr);

    /* ��¼�ڴ����4�ֽڶ�������ʼ��ַ */
    g_st_base_addr.puc_base_addr_align = puc_base_addr;

    HUT_INFO_VAR(0, "hut_main_init, mem start addr is 0x%x.", OAL_VIRT_TO_PHY_ADDR((oal_void *)g_st_base_addr.puc_base_addr_align));

    /* �����������У������ڴ������ϱ� */
    g_st_hut_workqueue.pst_rx_workqueue = OAL_CREATE_SINGLETHREAD_WORKQUEUE("hut_rx");
    if (OAL_PTR_NULL == g_st_hut_workqueue.pst_rx_workqueue)
    {
        HUT_ERR_LOG(0, "hut_main_init, create singlethread workqueue fail.");

        oal_free(g_st_base_addr.puc_base_addr_origin);

        return OAL_ERR_CODE_PTR_NULL;
    }

    OAL_INIT_WORK(&g_st_hut_workqueue.rx_work, hut_workqueu_handler);

    oal_dlist_init_head(&g_st_hut_workqueue.st_list);
    oal_spin_lock_init(&g_st_hut_workqueue.st_spin_lock);

    oal_dlist_init_head(&g_st_intr_queue.st_list);
    oal_spin_lock_init(&g_st_intr_queue.st_spin_lock);

    /* ��WALģ��ע��HUT netlink���պ��� */
    oam_netlink_ops_register(OAM_NL_CMD_HUT, hut_receive_msg);

    /* ��ʼ��HUTģ��tasklet */
    oal_task_init(&g_st_hut_tasklet, hut_tasklet_handler ,0);

    /* ��HALģ��ע��HUT�ж��ϰ벿������� */
    hal_to_hut_irq_isr_register(HAL_OPER_MODE_HUT, hut_irq_isr_all);

    hut_set_rx_dscr_queue_circle();

    return OAL_SUCC;
}

/*****************************************************************************
 �� �� ��  : hut_main_exit
 ��������  : HUTģ��ж�غ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : mayuan
    �޸�����   : �����ɺ���

*****************************************************************************/
oal_void  hut_main_exit(oal_void)
{
    if (OAL_PTR_NULL != g_st_base_addr.puc_base_addr_origin)
    {
        /* �ͷ�������ڴ� */
        oal_free(g_st_base_addr.puc_base_addr_origin);
    }

    /* ж��HUT.KO����ʱע����жϷ�����򣬲�������ģʽ��ΪNORMAL */
    hal_to_hut_irq_isr_unregister();

    /* ���ٹ������� */
    oal_destroy_workqueue(g_st_hut_workqueue.pst_rx_workqueue);

    /* ж��HUTģ��netlink���պ��� */
    oam_netlink_ops_unregister(OAM_NL_CMD_HUT);

    hut_set_rx_dscr_queue_uncircle();
}


/*lint -e578*//*lint -e19*/
oal_module_init(hut_main_init);
oal_module_exit(hut_main_exit);

oal_module_license("GPL");


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

