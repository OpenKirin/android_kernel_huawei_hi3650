/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : drv_mailbox_ifc.c
  �� �� ��   : ����
  ��    ��   : Ī�� 00176101
  ��������   : 2013��4��11��
  ����޸�   :
  ��������   : mailbox&�����������������˼����������롣
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2013��4��11��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_debug.h"
#include "drv_mailbox_gut.h"
#include "drv_mailbox_ifc.h"
#include "drv_mailbox_msg.h"


/*****************************************************************************
    ��ά�ɲ���Ϣ�а�����C�ļ���ź궨��
*****************************************************************************/
#undef  _MAILBOX_FILE_
#define _MAILBOX_FILE_   "ifc"
//extern int BSP_CPU_StateGet(int CpuID);
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*Զ�̺������ù�����Լ��:
  Զ�̵��ýӿ���ʽ���̶����ӿڶ��忪�Ÿ��û�����ģ���ṩһ�ֻ���:
    �û����԰��Լ���ʵ����Ҫֱ�Ӷ��岢��������һ��Զ�̺������Ҵ�Զ�̺���������Լ����
    1.  �����ķ���ֵֻ��Ϊlong�ͣ����ܷ���ָ�롣
    2.  �����Ĳ���Ŀǰ���֧��6����
    3.  �����Ĳ���ʵ���϶�������ָ�봦��ֻ��������6�����͵Ĳ�����
        1>  �̶���С��(ָ��)��Σ����С�ں������ɵ�ʱ�򱻶��岢��Ч��
        2>  �̶���С��(ָ��)���Σ����С�ں������ɵ�ʱ�򱻶��岢��Ч��
        3>  �̶���С��(ָ��)˫�Σ����С�ں������ɵ�ʱ�򱻶��岢��Ч��
        4>  �ɱ��С��(ָ��)��Σ��䳤������һ���̶���С�Ĳ���(�������)���壬
            �ں���������ʱ��Ч��
        5>  �ɱ��С��(ָ��)���Σ��䳤������һ���̶���С�Ĳ���(�������)���壬
            �ں���������ʱ��Ч��
        6>  �ɱ��С��(ָ��)˫��)���䳤������һ���̶���С�Ĳ���(�������)���壬
            �ں���������ʱ��Ч��
        7>  ������Ρ�
    4.  ���ĳ������Ϊ�ɱ��С��������ô������һ�����������ǹ̶���С�Ĳ���(long��)��
         ���Һ����ں������ù����н�����ǰ�ߵĴ�С��
    5.  �������ÿ�����Ϊ�ȴ��˼䷵�صĵ��úͲ��ȴ��˼䷵�صĵ��ã�����ʽ���ã���
    6.  ע��(���+˫��)�Ĵ�С����(����+˫��)�Ĵ�С���ܳ������䵥���ʼ�������С��
*/

/*
    ���ݷ����ʱ��(send code)����ý����ʱ��(receive code)
*/
int mailbox_ifc_get_rcode(unsigned int scode)
{
    unsigned int src_id      = mailbox_get_src_id(scode);
    unsigned int dst_id       = mailbox_get_dst_id(scode);
    /*unsigned long carrier_id   = mailbox_get_carrier_id(scode);*/

    /*����ifc�����ʱ�Ź̶�ʹ�÷���Գ�0��buffͨ����0��Ӧ��(��ͨ����0ƫ��Ӧ�ú�),
      ��Ҫ��֤ÿ��ifcͨ����Ӧ����һ���������0��ͨ�������ͨ�����ʱ඼ֻ����������;��
      ��ˣ�ifcͨ������ʹ��0������ͨ����������ܻ����������
      (ÿ���˼�0������ͨ��ֻ������Ϣ����ֻ�����޷��صĺ���)*/

    return (int)((dst_id << MAILBOX_ID_SRC_CPU_OFFSET)
           |(src_id << MAILBOX_ID_DST_CPU_OFFSET)
           /*|(carrier_id << MAILBOX_ID_CHANNEL_OFFSET)*/
            );
}

int mailbox_ifc_buf_pad(struct ifc_mb *ifc_b, unsigned int datalen)
{
    /* ��Ҫ:�˴���Ҫ���in arg buff�ռ��Ƿ�Ϊ���ԣ����Ϊ�����ԵĻ���
       ��Ҫ�Զ����հ���fifo��ĩ�ˣ��Ա�֤����ִ�в����ռ��������*/
    struct mb_queue   *que = (MAILBOX_USER_QUEUE(ifc_b->mbuf));

    unsigned int talsize;

    talsize = sizeof(struct ifc_head) + datalen;
    /*ifc_b->head.lmsg = talsize;*/

    if ((que->front + sizeof(struct ifc_head)) >= que->base + que->length) {
        /*��Ϣͷ��ת,���ԣ�*/
        /*ifc_b->head.data = que->front + sizeof(struct ifc_head) - que->length;*/
    ifc_b->data_vitrual_addr = que->front + sizeof(struct ifc_head) - que->length;
    } else  {
        if ((que->front + talsize) >= que->base + que->length) {
            /*data���䷴ת��������*/
            /*ifc_b->head.data = que->base;*/
            ifc_b->data_vitrual_addr = que->base;
            talsize += (unsigned int)((que->base + que->length) -  /*���β���ռ�*/
                (que->front + sizeof(struct ifc_head)));
        }
        else {/*�������,����*/
            /*ifc_b->head.data = que->front + sizeof(struct ifc_head);*/
            ifc_b->data_vitrual_addr = que->front + sizeof(struct ifc_head);
        }
    }

    /*�����Ե�ǰ���£���Ҫ��֤�ռ��㹻*/
    if( talsize > (unsigned int)mailbox_queue_left(que->rear, que->front, que->length)){

        return mailbox_logerro_p1(MAILBOX_FULL, datalen);
    }

    ifc_b->total_size = talsize;
    ifc_b->data_size = datalen;
    return MAILBOX_OK;
}
/*lint -e838*/
int mailbox_ifc_send_buf(struct ifc_mb *ifc_b)
{
    int ret_val = 0;
    unsigned long ifc_data = 0;
    struct mb_queue   *que = (MAILBOX_USER_QUEUE(ifc_b->mbuf));

    ifc_data = ifc_b->data_vitrual_addr; /*����ifc�������ݵ�ַ*/

    /*ifc����buff���������ݵ�ַ����Զ��ִ�к�ʹ�ã���Ҫת���������ַ*/

    ifc_b->head.data_phy_addr = (unsigned int)mailbox_virt_to_phy(ifc_b->data_vitrual_addr);

    /*��ifc��Ϣͷд�뻺��*/
    mailbox_write_buff(que, (char *)&ifc_b->head, sizeof(struct ifc_head));

    /*���Ҹ�������дָ�뵽ifc����ĩβ*/
    que->front = ifc_data + ifc_b->data_size;

    if (MAILBOX_OK == mailbox_sealup_buff( ifc_b->mbuf,  ifc_b->total_size)) {
         ret_val = mailbox_send_buff(ifc_b->mbuf);
    } else {
        ret_val = (int)MAILBOX_ERRO;
    }

    return ret_val;
}
/*lint -e715*/
/*lint -e818*/
void mailbox_ifc_waiter(void *mbuf, void *usrhandle, void *data)
{
    struct ifc_mb *ifc_b = (struct ifc_mb *)usrhandle;
    struct mb_queue *queue = MAILBOX_USER_QUEUE(mbuf);
    struct ifc_head  head_r ;

    int i;

    mailbox_read_buff(queue, (char*)&head_r, sizeof(struct ifc_head));

    if (head_r.stamp == ifc_b->head.stamp) { /*ͨ��ʱ�������֮ǰ�ĳ�ʱ��Ӧ*/
        for ( i = 0; i < IFC_MAX_ARG ;  i++ ) {
            if (ifc_b->argo[i].addr) { /*��������*/
                mailbox_memcpy((void *) (unsigned long)ifc_b->argo[i].addr,
                    (const void *)mailbox_phy_to_virt((unsigned long)(head_r.argv[i])),
                    (ifc_b->argo[i].size));
            }
        }

        ifc_b->head.retval = head_r.retval;
        mailbox_complete(&ifc_b->waitsem);
    }
}
/*lint +e715*/
/*lint -e801*/
/*���������Ϣ�����ȴ����÷���*/
int mailbox_ifc_send_wait(struct ifc_mb *ifc_b, unsigned int timeout)
{
    unsigned int rcode = ifc_b->head.rcode;

    if (MAILBOX_OK != mailbox_register_cb(rcode , mailbox_ifc_waiter, ifc_b,
                          MAILBOX_NULL)) {
        goto wait_exit;
    }

    ifc_b->waitsem = mailbox_init_completion();
    if(MAILBOX_NULL == ifc_b->waitsem){
        goto wait_exit;
    }
    if (MAILBOX_OK != mailbox_ifc_send_buf(ifc_b)) {
        goto wait_exit;
    }

    if (MAILBOX_OK != mailbox_wait_completion(&ifc_b->waitsem, timeout)) {
        ifc_b->head.retval = MAILBOX_TIME_OUT;

        /*��ʱ��Ҫע���ص������ߺ�����ܻ��ӳ���Ӧ,��ifc_bջ�ռ�ĵ�ַ*/
        mailbox_register_cb(rcode , MAILBOX_NULL, MAILBOX_NULL,
                              MAILBOX_NULL);
    }

wait_exit:
    mailbox_del_completion(&ifc_b->waitsem);
    mailbox_release_buff(ifc_b->mbuf);

    return (int)(ifc_b->head.retval);
}
/*lint +e801*/
/*���������Ϣ�����ȴ����÷���*/
int mailbox_ifc_send_no_wait(struct ifc_mb *ifc_b)
{
    int ret = mailbox_ifc_send_buf(ifc_b);

    ret |=  mailbox_release_buff(ifc_b->mbuf);

    return ret;
}

/*��������ִ�б������䷢��*/
int mailbox_ifc_discard_buf(struct ifc_mb *ifc_b)
{
    int ret = mailbox_release_buff(ifc_b->mbuf);
    return ret;
}
/*lint -e715*/
void mailbox_ifc_executer(void *mbuf, void *handle, void *data)
{
    int (*ife)(struct ifc_head * ifc_h) = handle;
    struct ifc_head  head;

    struct mb_queue *queue = MAILBOX_USER_QUEUE(mbuf);
    (void)mailbox_read_buff(queue, (char*)&head, sizeof(struct ifc_head));

    /*���ú��͹������������ַ,(����mailbox_ifc_send_buf��)
    ������ִ�к�ת���������ַ����ʹ��*/

    /*head.data = mailbox_phy_to_virt(head.data);*/ /*arm64λ����head.data ֻ���������ַ*/
    if (ife) {
        ife(&head);
    }
}
/*lint +e715*/
/*lint +e818*/
/*lint -e611*/
int mailbox_ifc_register_exec(
                unsigned int mailcode,
                int (*ife_cb)(struct ifc_head * ifc_h)
                )
{
    return mailbox_register_cb(mailcode, mailbox_ifc_executer,
                   (void*)ife_cb, (void *)(unsigned long)mailcode);
}
/*lint +e611*/
int mailbox_ifc_init_buf(
                struct ifc_mb *ifc_b,
                unsigned int mailcode,
                unsigned int direct,
                unsigned int inlen,
                unsigned int timeout)
{
    int ret_val = MAILBOX_OK;
    int try_times = 0;
    unsigned int go_on = MAILBOX_FALSE;

    mailbox_memset(ifc_b, 0x00, sizeof(struct ifc_mb));
    ifc_b->head.scode = mailcode;
    ifc_b->head.retval= MAILBOX_ERRO;

    ret_val= (int)BSP_CPU_StateGet(mailbox_get_dst_id(mailcode));
    if(!ret_val) {
        return (int)MAILBOX_TARGET_NOT_READY;
    }

    if (timeout){
        ifc_b->head.needret = MAILBOX_TRUE;
    }

    if (IFC_LAUNCH == direct) { /*��������,������Ϣ��ʼ��*/
        ifc_b->head.rcode = (unsigned int)mailbox_ifc_get_rcode(mailcode);  /*��ù̶����÷����ʱ��*/
        ifc_b->head.stamp = (unsigned int)mailbox_get_timestamp(); /*��ȡʱ���������ӦУ��*/
    } else if (IFC_RESPONSE == direct) {
        ifc_b->head.rcode = 0;
    }

    do { /*���ȴ��ӳ�����*/
        ret_val = mailbox_request_buff(mailcode, (void*)&ifc_b->mbuf);
        if (ifc_b->mbuf) {
            ret_val =  mailbox_ifc_buf_pad(ifc_b, inlen);
        }

        if ((int)MAILBOX_FULL == ret_val) {
            go_on = (unsigned int)mailbox_scene_delay(MAILBOX_DELAY_SCENE_IFC_FULL, &try_times);
            if (ifc_b->mbuf) {
                mailbox_release_buff(ifc_b->mbuf);
                ifc_b->mbuf = MAILBOX_NULL;
            }
        } else {
            go_on = MAILBOX_FALSE;
        }

    } while (MAILBOX_TRUE == go_on);

    if (MAILBOX_OK != ret_val) {
            if (MAILBOX_NULL != ifc_b->mbuf) {
                mailbox_release_buff(ifc_b->mbuf);
            }
            /*mailbox_show(mailcode,0);*/
            /*mailbox_assert(mailcode);*/
            return mailbox_logerro_p1(ret_val, mailcode);
        }

    return  MAILBOX_OK;
}
/*lint +e611*//*lint +e838*/
/*
���º����Ǳ�ifc���ɺ���õĲ��������ǵ������Ƕ��û�������ߴ����Զ�̵��ò������д���,
��������ǲ���ͨ�����ͽ���ͳһ˵��
    db: ��ǰ��������, ����:IFC_INVAR
    ab: ��ǰ������ֵ, ������ָ�룬Ҳ�����Ǳ���
    sb: ��ǰ����size, ����Ƕ���ָ�룬�����ʾ��ָ������ݳ��ȡ�
    df: ��һ����������
    af: ��һ��������ֵ
    sf: ��һ������size
    in:����������buffer�����ԡ�
    out: �������buffer,���ԡ�
*/

/*�����û���������������ַ���ڵ��÷��غ󣬽��ӽ���buffer������������
    ary: �����û�����Ĳ���ֵ������ǳ��Σ����ֵ���ڷ��ص�ʱ���õ���
*/

void __ifc_arg_out(struct ifc_arg ** p_ary, unsigned int db, unsigned long ab, unsigned int sb, unsigned int af)
{
    struct ifc_arg * ary = *p_ary;
    if ((IFC_OUT & db) || (IFC_BI & db)) {
         ary->addr = ab; /*���ճ�������ַ��ֻ�ڱ���ʹ�ã�����Ҫת��*/
        if (IFC_FIX & db) {
            ary->size = sb;
        }
        else if (IFC_VAR & db) {
            ary->size = af;
        }
    }
    *p_ary = *p_ary + 1;
}

/* ��Զ�̺������������ѹ������ķ���ͨ��buffer:
    av:�������ֵ������б䳤ָ�룬ִ�к˽�ʹ�����ﱣ��ı䳤ָ�볤��
*/
void __ifc_push_arg(unsigned long * in, unsigned int ** p_av, unsigned int db,
                        unsigned long ab, unsigned int sb, unsigned int af)
{

    unsigned int *av = *p_av;
    *av = ab;
    if ((IFC_IN & db) || (IFC_BI & db)) {
        if (IFC_CNT & db){
            *(unsigned int*)(*in) = (unsigned int)ab;
            *in += ifc_align_size(sizeof(unsigned int), IFC_ALIGN);
        }
        else if (IFC_FIX & db) {
            mailbox_memcpy((void*)*in, (const void*)ab, sb);
            *in += ifc_align_size(sb, IFC_ALIGN);
        }
        else if (IFC_VAR & db) {
            mailbox_memcpy((void*)*in, (const void*)ab, af);
            *in += ifc_align_size(af, IFC_ALIGN);
        }
    }
    *p_av = *p_av + 1;
}

/* ��������buffer��ifc����ռ�õĿռ� */
int __ifc_in_size(unsigned int db, unsigned int sb, unsigned int af)
{
    if ((IFC_IN & db) || (IFC_BI & db)) {
        if (IFC_CNT & db){
            return ifc_align_size(sizeof(unsigned int), IFC_ALIGN);
        } else if (IFC_FIX & db) {
            return (int)ifc_align_size(sb, IFC_ALIGN);
        } else if (IFC_VAR & db) {
            return (int)ifc_align_size(af, IFC_ALIGN);
        }
    }
    return 0;
}

/* �������buffer��ifc����ռ�õĿռ�
    pp_a:ָ�����ֵ�����е�ǰ����ֵ��ָ��
*/
int __ifc_out_size(unsigned int db, unsigned int sb, unsigned int **pp_a)
{
    unsigned int size = 0;
    if ((IFC_OUT & db) || (IFC_BI & db)) {
        if (IFC_FIX & db){
            size = ifc_align_size(sb, IFC_ALIGN);
        } else if (IFC_VAR & db) {
               unsigned int v_sz = *(unsigned int*)(*pp_a + 1);
            size =  ifc_align_size(v_sz, IFC_ALIGN);
        }
    }
    *pp_a = *pp_a + 1;
    return (int)size;
}

/*ΪԶ����ʵִ�к������ɲ���ֵ
    pp_a:ָ�����ֵ�����е�ǰ����ֵ��ָ��
*/
long __ifc_gen_arg(unsigned long *in, unsigned long *out, unsigned int db,
                unsigned int sb, unsigned int **pp_a)
{
    unsigned long ret_val = 0;
    unsigned int v_sz = 0;
    if (IFC_VAR & db) {
            v_sz = *(unsigned int*)(*pp_a + 1);
    }

    if (IFC_IN & db) {
        if (IFC_CNT & db){
            ret_val = *(unsigned int*)*in;
            *in = *in + sizeof(unsigned int);
        } else if (IFC_FIX & db) {
            ret_val = *in;
            *in = *in + ifc_align_size(sb, IFC_ALIGN);
        } else if (IFC_VAR & db) {
            ret_val = *in;
            *in = *in + ifc_align_size(v_sz , IFC_ALIGN);
        }
    } else if (IFC_BI & db) {
        if (IFC_FIX & db) {
            ret_val = *in;
            *in = *in + ifc_align_size(sb, IFC_ALIGN);
            *out = *out + ifc_align_size(sb, IFC_ALIGN);
        } else if (IFC_VAR & db) {
            ret_val = *in;
            *in = *in + ifc_align_size(v_sz, IFC_ALIGN);
            *out= *out + ifc_align_size(v_sz, IFC_ALIGN);
        }
    }
    else if (IFC_OUT & db) {
        ret_val = *out;
        if (IFC_FIX & db) {
            *out = *out + ifc_align_size(sb, IFC_ALIGN);
        } else if (IFC_VAR & db) {
            *out = *out + ifc_align_size(v_sz, IFC_ALIGN);
        }
    }
    *pp_a = *pp_a + 1;
    return  (long)ret_val;
}

/*Զ�̺���ִ����󣬰�˫�����ݿ��������buffer��ָ�롣
    pp_a:ָ�����ֵ�����е�ǰ����ֵ��ָ��
*/
void __ifc_copy_arg(unsigned long *in, unsigned long *out, unsigned int db,
                unsigned int sb, unsigned int **p_av , unsigned int **p_ao)
{
    unsigned int cpsize = 0;
    unsigned int *av = *p_av;
    unsigned int *ao = *p_ao;

    *ao = 0;
    if (IFC_FIX & db) {
        cpsize = ifc_align_size(sb, IFC_ALIGN);
    } else if (IFC_VAR & db) {
           unsigned int v_sz = *(av + 1);
        cpsize = ifc_align_size(v_sz, IFC_ALIGN);
    } else if (IFC_CNT & db) {
        cpsize = sizeof(unsigned int);
    }

    if (IFC_BI & db){
        mailbox_memcpy((void*)(*out), (const void*)(*in), (unsigned int)cpsize);
        *ao = (unsigned int)mailbox_virt_to_phy(*out); /*�ڵ��ú�mailbox_ifc_waiter()�б�����*/
        *out += cpsize;
        *in  += cpsize;
    }
    else if (IFC_IN & db) {
        *in += cpsize;
    }
    else if (IFC_OUT & db) {
        *ao = (unsigned int)mailbox_virt_to_phy(*out);
        *out += cpsize;
    }

    *p_av = *p_av + 1;
    *p_ao = *p_ao + 1;
}




