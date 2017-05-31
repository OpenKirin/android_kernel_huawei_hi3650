/******************************************************************************

��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
�� �� ��   : drv_mailbox.c
�� �� ��   : ����
��	  ��   : Ī�� 00176101
��������   : 2012��9��21��
����޸�   :
��������   : mailbox&����������������������롣
�����б�   :
	MAILBOX_BufIdleSize
	MAILBOX_BufDataSize
	mailbox_queue_write
	mailbox_request_channel
	mailbox_release_channel
	mailbox_read_mail
	MAILBOX_PostMails
	mailbox_receive_all_mails
	mailbox_check_mail
	mailbox_read_channel
	mailbox_init_mem
	mailbox_create_box
	mailbox_log_erro
	mailbox_init
	mailbox_queue_read
	MAILBOX_MailReceiverRegister
	mailbox_send_msg
	mailbox_show
�޸���ʷ   :
1.��	��	 : 2012��9��21��
��	  ��   : Ī�� 00176101
�޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_platform.h"
#include "drv_mailbox_debug.h"
#include "drv_mailbox_gut.h"
#include <asm/io.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/console.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/types.h>
#include <linux/string.h>
#include <asm/pgtable.h>
#include<linux/vmalloc.h>
#include <asm/io.h>
#include <linux/mm.h>

extern int logMsg(char *fmt, ...);
/*****************************************************************************
��ά�ɲ���Ϣ�а�����C�ļ���ź궨��
*****************************************************************************/
#undef	_MAILBOX_FILE_
#define _MAILBOX_FILE_	 "gut"

#define SLICE_REG 0xFFF0A534
#define mem_remap_nocache(phys_addr, size) mem_remap_type(phys_addr, size, pgprot_writecombine(PAGE_KERNEL))
/*****************************************************************************
2 ȫ�ֱ�������
*****************************************************************************/

/*����ģ���ܿ��ƾ��*/
MAILBOX_EXTERN struct mb g_mailbox_handle = {MAILBOX_MAILCODE_INVALID};
void __iomem *g_shareMemBase = NULL;
void * g_slice_reg = NULL;

MAILBOX_LOCAL int mailbox_init_mem(struct mb_cfg *config);

/*****************************************************************************
3 ����ʵ��
*****************************************************************************/

/*�����ڲ��ӿڿ�ʼ*/
/*****************************************************************************
�� �� ��  : mailbox_queue_write
��������  :
��������  : ������д��ָ���������ݲ�����дָ��
�������  : struct mb_queue    *queue - ��д����в�����
signed char 	   *data	  - ��д������ָ��
unsigned long	   size 	  - ��д�����ݳ��ȣ���λbyte
�������  : struct mb_queue    *queue	 - ������״̬,���¶���дָ�롣
�� �� ֵ  : void
���ú���  :
��������  : mailbox_write_mail()
MAILBOX_Read()

�޸���ʷ	  :
1.��	��	 : 2011��6��14��
��	  ��   : Ԭ�� 00145322
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_EXTERN int mailbox_queue_write(
                struct mb_queue      *queue,
                char                 *data,
                unsigned int         size)
{
    unsigned int SizeToBottom;

    /*����дָ��λ�þ��뻷�λ���β������*/
    SizeToBottom  = (unsigned int)((queue->base + queue->length) - queue->front);

    /*��дָ��໷�λ���β�����ȴ���Ҫд�����ݳ��ȣ���ֱ�ӿ������ݣ�������дָ��*/
    if (SizeToBottom > size){
        /*д��pucData��дָ�봦*/
        mailbox_memcpy((void*)queue->front, (const void*)data, size);

		/*����дָ��*/
		queue->front += size;
	} else {
		/*д��pucDataǰR���ȵ�дָ�봦*/
        mailbox_memcpy((void*)(queue->front), (const void*)data, SizeToBottom);

        /*д��pucData+R�����λ�����ʼ��*/
        mailbox_memcpy((void*)(queue->base),  (const void*)(data + SizeToBottom),
                       (size - SizeToBottom));

        /*����дָ��*/
        queue->front = (queue->base + size) - SizeToBottom;
    }

    return (int)size;
}

/*****************************************************************************
�� �� ��  : mailbox_queue_read
��������  : �����û������ݽ��ջص������е���, �������ж�ȡһ�����ȵ�����ʼ�

�������  : queue -- ������, ���ݽ��ջص��������
buff	  -- ������������ݵĻ����ַ
size	  -- ����ȡ�ʼ�����
�������  : struct mb_queue    *pMailQueue	 - ������״̬,���¶��ж�ָ�룬ָ�밴4�ֽ���ǰ���롣
�� �� ֵ  : ʵ�ʶ�ȡ����, ��λbyte
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��10��26��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_GLOBAL int mailbox_queue_read(
                struct mb_queue   *queue,
                char              *buff,
                unsigned int      size)
{
    unsigned int             to_bottom;

    /*�����ָ��λ�þ��뻷�λ���β������*/
    to_bottom  = (unsigned int)((queue->base + queue->length) - queue->rear);

    /*����ָ��໷�λ���β�����ȴ���Ҫд�����ݳ��ȣ���ֱ�ӿ������ݣ������¶�ָ��*/
    if (to_bottom > size) {
        /*����ָ�봦���ݿ�����pData��*/
        mailbox_memcpy((void*)buff, (const void*)(queue->rear), size);

        /*���¶�ָ��*/
        queue->rear += size;
    } else {
        /*����ָ�봦����ǰ����byte������pData��*/
        mailbox_memcpy((void*)buff, (const void*)(queue->rear), to_bottom);

        /*�ӻ��λ�����ʼ������ʣ�����ݵ�pData*/
        mailbox_memcpy((void*)(buff + to_bottom), (const void*)(queue->base),
                        (size - to_bottom));

        /*���¶�ָ��*/
        queue->rear = (queue->base + size) - to_bottom;
    }

    return (int)size;
}


/*****************************************************************************
�� �� ��  : mailbox_check_mail
�ӿ�����  : ���ڽӿ�
��������  : ����������Ϣ�Ƿ�����쳣������SN���Ƿ���������Ϣ����ʱ���Ƿ�
����
�������  : mb_buff 			*mbuff - ����������
struct mb_mail		*msg_head  - ������Ϣ����Ϣͷ
�������  : ��
�� �� ֵ  : ��Ϣͷ�Ƿ���Ч
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��24��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_check_mail(struct mb_buff *mbuff,
                struct mb_mail *msg_head,
                unsigned long data_addr)
{
    unsigned int          time_stamp;
    unsigned int          seq_num;
    int          ret_val = MAILBOX_OK;
    /* ���ȼ����Ϣͷ������*/
    if (MAILBOX_MSGHEAD_NUMBER != msg_head->ulPartition) {
         ret_val = mailbox_logerro_p1(MAILBOX_CRIT_GUT_MSG_CHECK_FAIL, msg_head->ulMailCode);
    }

    seq_num = mbuff->seq_num;

    /*��SN�Ų�����(ȥ����CPU���ܳ��ֱַ��µ�����)*/
    if (MAILBOX_SEQNUM_START == msg_head->ulSeqNum) {
        /*�����ߵ�һ�ν���*/
        ret_val = mailbox_logerro_p1(MAILBOX_INFO_RECEIVE_FIRST_MAIL, msg_head->ulMailCode);
    } else if ((seq_num + 1) != msg_head->ulSeqNum) {
        /*�Ƿ�ת����*/
        ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_MAILBOX_SEQNUM_CHECK_FAIL, msg_head->ulMailCode);
    }

    mbuff->seq_num = msg_head->ulSeqNum;

    /*�����Ϣ�ڹ����ڴ������ʱ��*/
    time_stamp = (unsigned int)mailbox_get_timestamp();

    msg_head->ulReadSlice = time_stamp;

    mailbox_record_transport(&(mbuff->mntn), msg_head->ulMailCode ,
                    msg_head->ulWriteSlice, msg_head->ulReadSlice, data_addr);
    return ret_val;
}

/*****************************************************************************
�� �� ��  : mailbox_get_mb
�ӿ�����  : ����ӿ�
��������  : ��ȡ��������ܾ��
�������  : ��
�������  : ��
�� �� ֵ  : ��������ܾ��
���ú���  :

��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��27��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_EXTERN struct mb *mailbox_get_mb(void)
{
    if (MAILBOX_INIT_MAGIC == g_mailbox_handle.init_flag) {
        return &g_mailbox_handle;
    }

	/*��������δ��ʼ��*/
	mailbox_out(("error: mb not init\n"));
	return MAILBOX_NULL;
}

/*****************************************************************************
�� �� ��  : mailbox_request_channel
�ӿ�����  : ����ӿ�
��������  : ��һ������ͨ����׼����ʼд����һ���ʼ���
�������е�����ͨ���ţ�����һ������������ţ�����������ͷ��������������Ϣ
�������  : struct mb *mailbox ��������ܾ��
unsigned long	  mailcode	-- �������ʼ���ID
�������  : ��
�� �� ֵ  : һ������ͨ���Ĳ�����
���ú���  :

��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��27��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_EXTERN struct mb_buff *mailbox_get_channel_handle(
                struct mb *mailbox,
                unsigned int mailcode)
{
    struct mb_link          *link_array   = MAILBOX_NULL;
    struct mb_buff                 *mbuff   = MAILBOX_NULL;
    unsigned int            src_id        = 0;
    unsigned int            dst_id        = 0;
    unsigned int            carrier_id    = 0;

	src_id		 = mailbox_get_src_id(mailcode);
	dst_id		 = mailbox_get_dst_id(mailcode);
	carrier_id	 = mailbox_get_carrier_id(mailcode);

    if (src_id == mailbox->local_id) {
        if (dst_id < MAILBOX_CPUID_BUTT) {
            link_array = &mailbox->send_tbl[dst_id];
        } else {
            /*��ЧĿ��ţ�����Խ��*/
            (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID, mailcode);
            return MAILBOX_NULL;
        }
    } else if (dst_id == mailbox->local_id) {
        if (src_id < MAILBOX_CPUID_BUTT) {
            link_array = &mailbox->recv_tbl[src_id];
        } else {
            /*��ЧĿ��ţ�����Խ��*/
            (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID, mailcode);
            return MAILBOX_NULL;
        }
    } else {
        /*�˴������շ�����ж�*/
    }

    if ((MAILBOX_NULL == link_array) || (0 == link_array->carrier_butt)) {
        /*��ǰ����CPU֮�䲻�����κ�����ͨ��*/
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CPU_LINK, mailcode);
        return MAILBOX_NULL;
    }

    /*���ͨ���������*/
    if (carrier_id < link_array->carrier_butt) {
        mbuff = &link_array->channel_buff[carrier_id];
    } else {
        /*�Ƿ�����ţ�����Խ��*/
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CARRIER_ID, mailcode);
        return MAILBOX_NULL;
    }

    /*���mail code�� use ID�ĺϷ���*/
    if (mailbox_get_use_id(mailcode) >= mailbox_get_use_id(mbuff->config->butt_id)) {
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_USER_ID, mailcode);

        return MAILBOX_NULL;
    }

    return mbuff;
}

/*****************************************************************************
 �� �� ��  : mailbox_request_channel
 �ӿ�����  : ����ӿ�
 ��������  : ��һ������ͨ����׼����ʼд����һ���ʼ���
             �������е�����ͨ���ţ�����һ������������ţ�����������ͷ��������������Ϣ
 �������  : struct mb *mb     -- �����ܾ��
             struct mb_buff ** -- ����ͨ������������
             unsigned long     mailcode  -- �������ʼ���ID
 �������  : ��
 �� �� ֵ  : һ������ͨ���Ĳ�����
 ���ú���  :

��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��27��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_request_channel(
                struct mb *mb,
                struct mb_buff ** mb_buf,
                unsigned int mailcode)
{
    struct mb_head       *head  = MAILBOX_NULL;
    struct mb_queue      *queue = MAILBOX_NULL;
    struct mb_buff       *mbuff = MAILBOX_NULL;
    int ret_val = MAILBOX_OK;

	mailbox_dpm_device_get();

    *mb_buf = MAILBOX_NULL;
    mbuff = mailbox_get_channel_handle(mb, mailcode);
    if (MAILBOX_NULL == mbuff) {
        ret_val = (int)MAILBOX_ERRO;
        goto request_erro;
    }

	/*ͨ���ж�ͨ�������֣����ͨ����û�г�ʼ��*/
	head = (struct mb_head*)mbuff->config->head_addr;
	if ((  (MAILBOX_PROTECT1 != head->ulProtectWord1) )
		|| (MAILBOX_PROTECT2 != head->ulProtectWord2)
		||(MAILBOX_PROTECT1 != head->ulProtectWord3)
		|| (MAILBOX_PROTECT2 != head->ulProtectWord4)) {
		/*�����ֲ���ȷ��˵������δ��ʼ���������ڴ汻�ȣ�����*/
		/* do not check cause hifi maybe not pwr on when the first ipc message send */

		mailbox_init_mem(mbuff->config);

		mailbox_logerro_p1(MAILBOX_NOT_READY, mailcode);
	}

	if(mailbox_get_src_id(mailcode) == mb->local_id) {
		/* ���������ж��з��ʼ�*/
		if (MAILBOX_TRUE == mailbox_int_context()) {
//TODO:�������Ŀ���(IFC for �͹���)������Ҫ֧�����ж��з����ʼ����������Ҫ���жϡ�
			ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_SEND_MAIL_IN_INT_CONTEXT, mailcode);
			goto request_erro;
		} else {
			if (MAILBOX_OK != mailbox_mutex_lock(&mbuff->mutex)) {
				/*���жϷ��ͣ���Ҫ��Դ��������ȡ��ǰͨ����Դ��*/
				ret_val = mailbox_logerro_p1(MAILBOX_CRIT_GUT_MUTEX_LOCK_FAILED, mailcode);
				goto request_erro;
			}
		}
	}

	mbuff->mailcode = mailcode;

    /*�����ڴ���У���Ҫ��������ͷ��Ϣ�Զ��в������������*/
    queue = &mbuff->mail_queue;
    queue->front = queue->base + head->ulFront * sizeof(unsigned int);
    queue->rear  = queue->base + head->ulRear * sizeof(unsigned int);

	mbuff->mb = mb;
	*mb_buf = mbuff;
	return MAILBOX_OK;
request_erro:
	mailbox_out(("###mailbox_request_channel ERR! \n"));
	mailbox_dpm_device_put();
	return ret_val;
}

/*****************************************************************************
�� �� ��  : mailbox_release_channel
�ӿ�����  : ���ڽӿ�
��������  : �ر����䣬�ͷ���Դ��

�������  : mb_buff* fpMailBox	- ����ͨ�����������
�������  : ��
�� �� ֵ  : ����ر��Ƿ�ɹ�
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��27��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_release_channel(struct mb *mb,
                struct mb_buff *mbuff)
{
    unsigned int         channel_id    = mbuff->channel_id;

	/*��Ҫ�����Ƕ�����д*/
	if (mb->local_id == mailbox_get_src_id(channel_id)) {
		if (MAILBOX_TRUE == mailbox_int_context()) {
			/*TODO:�������Ŀ���(IFC for �͹���)������Ҫ֧�����ж��з����ʼ���
			�������Ҫ�����жϡ�*/
		} else {
			mailbox_mutex_unlock(&mbuff->mutex);
		}
	}

	mailbox_dpm_device_put();
	return MAILBOX_OK;
}

/*****************************************************************************
�� �� ��  : mailbox_read_mail
�ӿ�����  : ���ڽӿ�
��������  : ��ȡ������һ�������������������,�����������ݵ����ݲ���ڣ�
���ҵ����ϲ�ע����ʼ����ݴ���ص�����
�������  : mb_buff*	   pstMailbox  - ����ͨ��������

�������  : ��
�� �� ֵ  : ��ȡ���ʼ����ݳ��ȣ������ʼ�ͷ������0��ʾʧ�ܡ�
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��24��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_read_mail(struct mb_buff *mbuff)
{
    struct mb_mail        mail;
    struct mb_cb         *read_cb = MAILBOX_NULL;/*������ͨ���Ĺ��ܻص���������*/
    struct mb_queue       tmp_queue;
    struct mb_queue      *usr_queue   = MAILBOX_NULL;
    struct mb_queue      *m_queue   = MAILBOX_NULL;
    unsigned int         use_id;
    unsigned int         slice_start;
    unsigned int         to_bottom;
    void                 *usr_handle;
    void                 *usr_data;
    void (*usr_func)(void *mbuf, void *handle, void *data);

	m_queue = &(mbuff->mail_queue);
	usr_queue = &(mbuff->usr_queue);
	mailbox_memcpy((void *) usr_queue, (const void *) m_queue, sizeof(struct mb_queue));

	/*������ʱ����״̬,������дָ�롣*/
	tmp_queue.base	 = usr_queue->base;
	tmp_queue.length = usr_queue->length;
	tmp_queue.front  = usr_queue->rear;
	tmp_queue.rear	 = usr_queue->front;

	/*��ȡ�ʼ���ͷ��Ϣ*/
	mailbox_queue_read(usr_queue, (char*)&mail, sizeof(struct mb_mail));

	/*1.����ʼ�ͷ���ж϶�������Ϣ�Ƿ�����쳣������SN���Ƿ���������Ϣ����ʱ���Ƿ������
	2.�����Ϣ��ȡʱ��*/
	mailbox_check_mail(mbuff, &mail, m_queue->rear);

	/*�Ѷ�ȡʱ��д���������*/
	mailbox_queue_write(&tmp_queue, (char*)&mail, sizeof(struct mb_mail));
	use_id = mailbox_get_use_id(mail.ulMailCode);

	/*���Use ID����Ч��*/
	if (use_id >= mailbox_get_use_id(mbuff->config->butt_id)) {
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_USER_ID, mail.ulMailCode);
		goto EXIT;
	}

	read_cb = &mbuff->read_cb[use_id];
	mailbox_mutex_lock(&mbuff->mutex);
	usr_handle = read_cb->handle;
	usr_data = read_cb->data;
	usr_func = read_cb->func;
	mailbox_mutex_unlock(&mbuff->mutex);
	if (MAILBOX_NULL != usr_func) {
		usr_queue->size = mail.ulMsgLength;
        slice_start = (unsigned int)mailbox_get_timestamp();
		usr_func(mbuff, usr_handle , usr_data);

		/*��¼��ά�ɲ���Ϣ*/
         mailbox_record_receive(&mbuff->mntn, mail.ulMailCode, slice_start);
	} else {
        (void)mailbox_logerro_p1(MAILBOX_ERR_GUT_READ_CALLBACK_NOT_FIND, mail.ulMailCode);
	}

EXIT:

	/*�����û���û���ûص������ݣ����˶������ݣ�������еĶ�ָ�붼��Ҫ��ʵ��
	��Сƫ�ƣ��Ա�֤�����ʼ���ȡ����ȷ�ԡ�*/
    to_bottom  = (unsigned int)((m_queue->base + m_queue->length) - m_queue->rear);
	if (to_bottom > (mail.ulMsgLength + sizeof(struct mb_mail))) {
		m_queue->rear += (mail.ulMsgLength + sizeof(struct mb_mail));
	} else {
		m_queue->rear = m_queue->base + ((mail.ulMsgLength +
										  sizeof(struct mb_mail)) - to_bottom);
	}

	/*����ָ֤��4�ֽڶ���*/
	m_queue->rear = mailbox_align_size(m_queue->rear, MAILBOX_ALIGN);

    return (int)(mailbox_align_size(mail.ulMsgLength, MAILBOX_ALIGN)
            + sizeof(struct mb_mail));

}

/****************************************************************************************************
�� �� ��  : mailbox_receive_all_mails
�ӿ�����  : ���ڽӿ�
��������  : ��ȡ��ǰ�����δ��ȡ���ݳ��ȣ�������ȴ���0�����ζ�ȡ������һ���ʼ���
ֱ���������ݶ�ȡ��.
�������  : mb_buff*  fpMail -- ĳ������ͨ���Ĳ������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��24��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************************************/
MAILBOX_LOCAL int mailbox_receive_all_mails(struct mb_buff *mbuf)
{

    struct mb_queue      *queue;   /* ��ʱ������Ϣ״̬�ṹ�� */
    signed int           size_left;   /* ����δ������Ϣ���� */
    unsigned int         mail_len = 0;
    int          ret_val = MAILBOX_OK;

	queue = &(mbuf->mail_queue);

     /*���������д�ȡ���ݳ��ȣ���λbyte, ����ĳ������������д��������4byte����*/
    if (queue->front >= queue->rear) {
        size_left    = (signed int)(queue->front - queue->rear);
    } else {
        size_left    = (signed int)( (queue->length) - ((queue->rear)
                       - (queue->front)) );
    }

    /*����ȡ���ݳ��ȷ�0�����������ݷǿ�*/
    while (size_left > 0) {
        /*ÿ�δ������ȡһ���ʼ��������ʼ�ͷ*/
        mail_len = (unsigned int)mailbox_read_mail(mbuf);
        if (0 == mail_len) {
            ret_val = mailbox_logerro_p1(MAILBOX_CRIT_GUT_READ_MAIL, mbuf->channel_id);
        }
        /*���´�ȡ���ݳ���*/
        size_left -= (signed int)(mail_len);
    }

    if (size_left < 0) {
       return mailbox_logerro_p1(MAILBOX_CRIT_GUT_RECEIVE_MAIL, mbuf->channel_id);
    }
    return ret_val ;
}

/*****************************************************************************
�� �� ��  : mailbox_read_channel
�ӿ�����  : ���ڽӿ�
��������  : ���乲���ڴ�ͨ�����ܵ������ݵĴ���ص�����.
���ݴ���Ĳ���(MailBoxID)����������ͨ����������֣�ʹ�ò�ͬ��ɨ�������ȡ����:
��24bit��Ч ֪ͨ�ĸ�CPU������ͨ�����ʼ�����:ɨ�������ͨ�������������ʼ���
�������  : unsigned long MailBoxID -- ����ͨ����
�������  : ��
�� �� ֵ  : ��
���ú���  : mailbox_receive_all_mails()
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��24��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_read_channel(unsigned int channel_id)
{
    struct mb_buff      *mbuf  = MAILBOX_NULL;     /*����������*/
    struct mb           *mb    = MAILBOX_NULL;
    int       ret_val      = MAILBOX_OK;

    mb = mailbox_get_mb();

    if (MAILBOX_NULL == mb) {
        return (int)MAILBOX_ERRO;
    }

	/*�жϷ����Ƿ���ȷ,�Ƿ�Ϊ����ͨ��*/
	if (mb->local_id != mailbox_get_dst_id(channel_id)) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_TARGET_CPU, channel_id);
	}

	/*�򿪴�����ͨ��*/
	ret_val = mailbox_request_channel(mb, &mbuf, channel_id);
	if (MAILBOX_OK != ret_val) {
		return ret_val;
	}

	/*���մ�����ͨ���������ʼ�*/
	ret_val = mailbox_receive_all_mails(mbuf);

	mailbox_flush_buff(mbuf); /*������ͨ������������Ϣд������ͷ��*/

	/*������ɣ��ر�����*/
	if (MAILBOX_OK != mailbox_release_channel(mb, mbuf)) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_RELEASE_CHANNEL, channel_id);
	}

	return ret_val;
}

/*****************************************************************************
�� �� ��  : mailbox_init_mem
�ӿ�����  : ���ڽӿ�
��������  : ��ʼ������ͨ���ڴ�,��ʼ������ͷ�������壬���ýṹ��ʼֵ�ͱ����ֵ�
�������  : pstDrvMbMemCfg -- ĳ�������ڴ�ͨ��������
�������  : ��
�� �� ֵ  : �ɹ���ʧ��
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��24��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_init_mem(struct mb_cfg *config)
{
    struct mb_head       *head = (struct mb_head*)config->head_addr;
    unsigned long         data_addr       = config->data_addr;
    unsigned int         data_size       = config->data_size;

	/*����Ҳ��������ж�*/
	if ((0 == data_addr) || (MAILBOX_NULL == head) || (0 == data_size)) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INIT_CORESHARE_MEM, config->butt_id);
	}

	/*��ʼ��������*/
	mailbox_memset((signed char *)data_addr, 0, data_size);

	/*��ʼ������ͷ��������*/
	mailbox_write_reg(data_addr, MAILBOX_PROTECT1);
	mailbox_write_reg(data_addr + MAILBOX_PROTECT_LEN, MAILBOX_PROTECT2);

	/*��ʼ������β��������*/
	mailbox_write_reg((data_addr + data_size) - (2*MAILBOX_PROTECT_LEN),
					  MAILBOX_PROTECT1);
	mailbox_write_reg((data_addr + data_size) - MAILBOX_PROTECT_LEN,
					  MAILBOX_PROTECT2);

	/*��ʼ������ͷ*/
	head->ulFront		  = 0;
	head->ulFrontslice	  = 0;
	head->ulRear		  = head->ulFront;
	head->ulRearslice	  = 0;
	head->ulProtectWord4  = MAILBOX_PROTECT2;
	head->ulProtectWord3  = MAILBOX_PROTECT1;
	head->ulProtectWord2  = MAILBOX_PROTECT2;
	head->ulProtectWord1  = MAILBOX_PROTECT1;

	return MAILBOX_OK;
}

/*****************************************************************************
�� �� ��  : mailbox_calculate_space
�ӿ�����  : ���ڽӿ�
��������  : ͳ��ͨ����Ϣ��������Ҫ������ڴ�ռ�
�������  : pMailbox  -- �����ܾ��
ChCfgTbl  -- ����ͨ����ȫ�����ñ�
CpuID	  -- ע���ͨ����CPU�š�
�������  : ��
�� �� ֵ  : ����������
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��7��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_calculate_space(
                struct mb           *mb,
                struct mb_cfg    *config,
                unsigned int     cpu_id)
{
    struct mb_link          *send_link    = MAILBOX_NULL;/*ָ�����ṹ��ķ���ͨ���������ַ*/
    struct mb_link          *recev_link   = MAILBOX_NULL;/*ָ�����ṹ��Ľ���ͨ���������ַ*/
    int            ret_val      = MAILBOX_OK;
    unsigned int            src_id       = 0;
    unsigned int            dst_id       = 0;
    unsigned int            carrier_id   = 0;

	send_link	=  mb->send_tbl;
	recev_link	=  mb->recv_tbl;

	while (MAILBOX_MAILCODE_INVALID != config->butt_id) {
		src_id		 = mailbox_get_src_id(config->butt_id);
		dst_id		 = mailbox_get_dst_id(config->butt_id);
		carrier_id	 = mailbox_get_carrier_id(config->butt_id);

		/*����ǲ��Ǳ�CPU����ͨ��*/
		if (cpu_id == src_id) {
			/*���Ŀ��CPU����Ч��*/
			if (dst_id < MAILBOX_CPUID_BUTT) {
				/*��¼��CPU���ӵ����ͨ��*/
				if ((carrier_id + 1) > send_link[dst_id].carrier_butt) {
					send_link[dst_id].carrier_butt = (carrier_id + 1);
				} else {
					/*����¼*/
				}
			} else {
				/*����Խ��*/
				ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID,
											 config->butt_id);
			}
		}
		/*����ǲ��Ǳ�CPU����ͨ��*/
		if (cpu_id == dst_id) {
			/*��鷢��CPU����Ч��*/
			if (src_id < MAILBOX_CPUID_BUTT) {
				/*��¼��CPU���ӵ����ͨ��*/
				if ((carrier_id + 1) > recev_link[src_id].carrier_butt) {
					recev_link[src_id].carrier_butt = (carrier_id + 1);
				} else {
					/*����¼*/
				}
			} else {
				/*����Խ��*/
				ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID,
											 config->butt_id);
			}
		}

		config++;
	}

	return ret_val;
}

/*****************************************************************************
�� �� ��  : mailbox_init_all_handle
�ӿ�����  : ���ڽӿ�
��������  : ��ʼ�����������ͨ�����
�������  : pMailbox  -- �����ܾ��
ChCfgTbl  -- ����ͨ����ȫ�����ñ�
CpuID	  -- ע���ͨ����CPU�š�
�������  : ��
�� �� ֵ  : ����������
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��7��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_init_all_handle(
                struct mb           *mb,
                struct mb_cfg    *config,
                unsigned int     cpu_id)
{
    struct mb_queue        *queue  = MAILBOX_NULL;
    unsigned int           direct= MIALBOX_DIRECTION_INVALID; /*��ǵ�ǰ����ͨ��
                                            �ǲ��Ǳ�����ص���Чͨ��*/
    int           ret_val      = MAILBOX_OK;
    struct mb_link         *send_link    = MAILBOX_NULL;/*ָ�����ṹ��ķ���ͨ��
                                                          �������ַ*/
    struct mb_link         *recv_link = MAILBOX_NULL;   /*ָ�����ṹ��Ľ���ͨ��
                                                          �������ַ*/
    struct mb_buff         *mbuf_prob   = &g_mailbox_channel_handle_pool[0];
    struct mb_cb           *cb_prob  = &g_mailbox_user_cb_pool[0];
    struct mb_buff         *mbuf_cur = MAILBOX_NULL;    /*ָ�����ڴ��������ͨ��*/
    unsigned int           channel_sum    = 0;
    unsigned int           use_sum    = 0;
    unsigned int           src_id       = 0;
    unsigned int           dst_id       = 0;
    unsigned int           carrier_id   = 0;
    unsigned int           use_max      = 0;

	send_link  =  mb->send_tbl;
	recv_link  =  mb->recv_tbl;




	/*�ڶ���ѭ����ÿ��ͨ���������ռ�,����ֵ��(��δ������̫�࣬�������������)*/
	/*��ʼ��ÿ������Ŀ��ƾ��*/
	while (MAILBOX_MAILCODE_INVALID != config->butt_id) {
		direct = MIALBOX_DIRECTION_INVALID;
		src_id		 = mailbox_get_src_id(config->butt_id);
		dst_id		 = mailbox_get_dst_id(config->butt_id);
		carrier_id	 = mailbox_get_carrier_id(config->butt_id);
		use_max 	 = mailbox_get_use_id(config->butt_id);

		printk("******************func = %s line = %d src_id = %d dst_id = %d******************\n",
			   __func__, __LINE__, src_id, dst_id);


		/*����ǲ��Ǳ�CPU����ͨ��*/
		if (cpu_id == src_id) {
			direct = MIALBOX_DIRECTION_SEND;

			/*û�з���ռ������ռ�*/
			if (MAILBOX_NULL == send_link[dst_id].channel_buff) {
				send_link[dst_id].channel_buff = mbuf_prob;
				mbuf_prob += (send_link[dst_id].carrier_butt);
				channel_sum  += (send_link[dst_id].carrier_butt);
				if (channel_sum > MAILBOX_CHANNEL_NUM) {
					return mailbox_logerro_p1(MAILBOX_CRIT_GUT_INIT_CHANNEL_POOL_TOO_SMALL,
											  channel_sum);
				}
			}
			mbuf_cur = &send_link[dst_id].channel_buff[carrier_id];
		}

		/*����ǲ��Ǳ�CPU����ͨ��*/
		if (cpu_id == dst_id) {
			direct = MIALBOX_DIRECTION_RECEIVE;

			/*û�з���ռ������ռ�*/
			if (MAILBOX_NULL == recv_link[src_id].channel_buff) {
				recv_link[src_id].channel_buff = mbuf_prob;
				mbuf_prob += (recv_link[src_id].carrier_butt);
				channel_sum  += (recv_link[src_id].carrier_butt);
				if (channel_sum > MAILBOX_CHANNEL_NUM) {
					return mailbox_logerro_p1(MAILBOX_CRIT_GUT_INIT_CHANNEL_POOL_TOO_SMALL,
											  channel_sum);
				}
			}

			mbuf_cur = &recv_link[src_id].channel_buff[carrier_id];

			/*1��Ϊ�ʼ�ע��ص���������ռ�*/
			mbuf_cur->read_cb = cb_prob;
			cb_prob += use_max;
			use_sum   += use_max;
			if (use_sum > MAILBOX_USER_NUM) {
				return mailbox_logerro_p1(MAILBOX_CRIT_GUT_INIT_USER_POOL_TOO_SMALL, use_sum);
			}

			/*3.ע�������̻߳ص��ӿڣ����ڻ�ȡ�����ڴ��������ݵĴ���*/
			ret_val = mailbox_process_register(mailbox_get_channel_id(config->butt_id),
											   mailbox_read_channel, mbuf_cur);

			/*4.��ʼ�����乲���ڴ棬���ñ�־λ��*/
			ret_val |= mailbox_init_mem(config);

		}

		if ((MIALBOX_DIRECTION_INVALID != direct ) && (MAILBOX_NULL != mbuf_cur)) {
			/*����ͨ��:����ʱ��Ҫ�������⣬
			����ͨ��:��Ҫ�Իص�ע����л���*/

			/*�����ƾ����������ID��*/
			mbuf_cur->channel_id = mailbox_get_channel_id(config->butt_id);
			mbuf_cur->seq_num = MAILBOX_SEQNUM_START;
			mbuf_cur->mntn.peak_traffic_left = MAILBOX_QUEUE_LEFT_INVALID;
			mbuf_cur->mntn.mbuff	= mbuf_cur;
			/*����������������Դ*/
			mbuf_cur->config = config;

			/*��ʼ��ͨ����Դ*/
			queue = &(mbuf_cur->mail_queue);

			/*��ʼ������ͨ���Ļ��ζ��п��Ʒ������������ǳ�ʼ���Ժ󲻻��ٱ仯�ġ�*/
			queue->length  = mbuf_cur->config->data_size -
							 (MAILBOX_DATA_LEN_PROTECT_NUM * MAILBOX_PROTECT_LEN);
			queue->base    = mbuf_cur->config->data_addr +
							 (MAILBOX_DATA_BASE_PROTECT_NUM * MAILBOX_PROTECT_LEN);


			/*�Ѵ�ͨ��ע�ᵽ����ƽ̨*/
			ret_val = mailbox_channel_register(mailbox_get_channel_id(config->butt_id), /*lint !e539*/
											   config->int_src,
											   mailbox_get_dst_id(config->butt_id),
											   direct,
											   &mbuf_cur->mutex);
		}

		config++;
	}

	/*����ڴ�ش�С�Ƿ�պ�,�����������������Ƿ�ƥ��:
	������������������Ŀռ��Ƿ����䡣
	g_mailbox_global_cfg_tbl[];
	g_mailbox_channel_handle_pool[MAILBOX_CHANNEL_NUM];
	g_mailbox_user_cb_pool[MAILBOX_USER_NUM];
	*/
    if((unsigned int)MAILBOX_CHANNEL_NUM != channel_sum ) {
		ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_INIT_CHANNEL_POOL_TOO_LARGE,
                                    ((MAILBOX_CHANNEL_NUM<<16) | channel_sum));
	}

	if(MAILBOX_USER_NUM != use_sum) {
		ret_val = mailbox_logerro_p1(MAILBOX_ERR_GUT_INIT_USER_POOL_TOO_LARGE, use_sum);
	}

	return ret_val;
}

/*****************************************************************************
�� �� ��  : mailbox_create_box
�ӿ�����  : ���ڽӿ�
��������  : ��������������,���������ܲ�������ռ䣬����ʼ������ͨ����Դ.
�������  : ChCfgTbl  -- ����ͨ����ȫ�����ñ�
CpuID	  -- ע���ͨ����CPU�š�
�������  : ��
�� �� ֵ  : ����������
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��7��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_create_box(
                struct mb          *mb,
                struct mb_cfg   *config,
                unsigned int    cpu_id)
{
	mb->local_id = cpu_id;

	printk("<<<<<<<<<<<<<<mailbox_create_box cpu_id = %d>>>>>>>>>>>>>>\n", cpu_id);

	/*��һ��ѭ�����ͨ���ŵ���Ч�ԣ���ͳ��ÿ���˼�ͨ������Ŀռ�*/
	if(MAILBOX_OK !=   mailbox_calculate_space(mb, config, cpu_id)) {
		return mailbox_logerro_p0(MAILBOX_ERR_GUT_CALCULATE_SPACE);
	}

	/*�ڶ���ѭ����ÿ��ͨ���������ռ�,����ֵ��*/
	/*��ʼ��ÿ������Ŀ��ƾ��*/
	return mailbox_init_all_handle(mb, config, cpu_id);
}

/*****************************************************************************
�� �� ��  : mem_remap_type
�ӿ�����  : ���ڽӿ�
��������  : ��һ��ddr�ڴ棬ӳ�䵽�����ڴ���
�������  :	phys_addr �����ַ��size �����ַ��С�� pgprot ӳ������
�������  :  ��
�� �� ֵ  : �ں������ַ

��	��	  : 2014��11��17��
�޸�����  :  �����ɺ���
*****************************************************************************/
void *mem_remap_type(unsigned long phys_addr, size_t size, pgprot_t pgprot)
{
    int i;
    u8* vaddr;
    int npages = PAGE_ALIGN((phys_addr & (PAGE_SIZE - 1)) + size) >> PAGE_SHIFT;
    unsigned long offset = phys_addr & (PAGE_SIZE - 1);
    struct page **pages;
    pages = vmalloc(sizeof(struct page *) * npages);
    if (!pages)
    {
        printk(KERN_ERR "%s: vmalloc return NULL!\n", __FUNCTION__);
        return NULL;
    }
    pages[0] = phys_to_page(phys_addr);
    for (i = 0; i < npages - 1 ; i++) {
        pages[i + 1] = pages[i] + 1;
    }
    vaddr = (u8*)vmap(pages, npages, VM_MAP, pgprot);
    if(vaddr == 0)
    {
        printk(KERN_ERR "%s: vmap return NULL!\n", __FUNCTION__);
    }
    else
    {
        vaddr += offset;
    }
    vfree(pages);
    printk(KERN_DEBUG "%s: phys_addr:0x%08lx size:0x%08lx npages:%d vaddr:%pK offset:0x%08lx\n", __FUNCTION__, phys_addr, (unsigned long)size, npages, vaddr, offset);
    return (void *)vaddr;
}

/*****************************************************************************
�� �� ��  : mailbox_init
�ӿ�����  : ����ӿ�
��������  : ����ģ��ƽ̨���䲿�ֳ�ʼ��
�������  :

�������  : ��
�� �� ֵ  : �̲߳������
���ú���  :
��������  : mailbox_init_platform()

�޸���ʷ	  :
1.��	��	 : 2012��9��24��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

��ϸ����: ��ʼ�����䲢��ʼ����ƽ̨��صĲ��컯���֣��������ʼ����ʱ����á�
*****************************************************************************/
MAILBOX_GLOBAL int mailbox_init(void)
{
	unsigned long offset = 0;
	int i = 0;
	struct mb_head *head = NULL;

	if (MAILBOX_INIT_MAGIC == g_mailbox_handle.init_flag) {
		/*���ǵ������µ���������̬���ݲ��ᶪʧ������ֻ��ӡ�澯��
		���ش���Ļ��������ƽ̨��ʼ������������IPC�ж��޷�ע��*/
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_ALREADY_INIT, g_mailbox_handle.init_flag);
	}

	printk("func = %s, line = %d baseaddr = 0x%x\n", __func__, __LINE__, (unsigned int)MAILBOX_MEM_BASEADDR);

	g_shareMemBase = mem_remap_nocache(MAILBOX_MEM_BASEADDR, MAILBOX_MEM_LENGTH);
	/*��ʼ�������е�����*/
//memset(g_shareMemBase,0x0,MAILBOX_MEM_LENGTH);

	if(NULL == g_shareMemBase) {
		printk("func = %s, mmap mailbox mem error!!\n", __func__);
		return mailbox_logerro_p0(MAILBOX_CRIT_GUT_MEMORY_CONFIG);
	}

	offset = (unsigned long)g_shareMemBase - MAILBOX_MEM_BASEADDR;
	for(i = 0; i < MAILBOX_GLOBAL_CHANNEL_NUM; i++) {
		g_mailbox_global_cfg_tbl[i].head_addr = g_mailbox_global_cfg_tbl[i].head_addr + offset;
		g_mailbox_global_cfg_tbl[i].data_addr = g_mailbox_global_cfg_tbl[i].data_addr + offset;

		printk("i = %d, head_addr = 0x%lx, data_addr = 0x%lx\n", i,
			   g_mailbox_global_cfg_tbl[i].head_addr, g_mailbox_global_cfg_tbl[i].data_addr);

		/*��ʼ������ͷ*/
		head = (struct mb_head *)g_mailbox_global_cfg_tbl[i].head_addr;
		head->ulFront = 0x0;
		head->ulRear = 0x0;
		head->ulFrontslice = 0x0;
		head->ulRearslice = 0x0;
	}

	/*TODO:���е����µ��������Կ���ʱ��������Ҫɾ��*/
	mailbox_memset(&g_mailbox_handle, 0x00, sizeof(struct mb));

    if ((MAILBOX_HEAD_BOTTOM_ADDR > (MAILBOX_MEM_BASEADDR + MAILBOX_MEM_HEAD_LEN)) ||
       (MAILBOX_MEMORY_BOTTOM_ADDR > (MAILBOX_MEM_BASEADDR + MAILBOX_MEM_LENGTH)))
    {
        mailbox_out(("mailbox address overflow: headbuttom valid(0x%lx), config(0x%x)!\n\
          \r                          databuttom valid(0x%x), config(0x%x)!"RT,
        (MAILBOX_MEM_BASEADDR + MAILBOX_MEM_HEAD_LEN), (unsigned int)MAILBOX_HEAD_BOTTOM_ADDR,
        (unsigned int)(MAILBOX_MEM_BASEADDR + MAILBOX_MEM_LENGTH), (unsigned int)MAILBOX_MEMORY_BOTTOM_ADDR));
        return mailbox_logerro_p0(MAILBOX_CRIT_GUT_MEMORY_CONFIG);
    }

	/*��ʼ���������岿�֣����������ܾ����*/
	if (MAILBOX_OK != mailbox_create_box(&g_mailbox_handle,
										 &g_mailbox_global_cfg_tbl[0], MAILBOX_LOCAL_CPUID)) {
		return mailbox_logerro_p0(MAILBOX_ERR_GUT_CREATE_BOX);
	}

	/*��ʼ��ƽ̨���첿��*/
	if (MAILBOX_OK != mailbox_init_platform()) {
		return mailbox_logerro_p0(MAILBOX_ERR_GUT_INIT_PLATFORM);
	}

	g_mailbox_handle.init_flag = MAILBOX_INIT_MAGIC;

//mailbox_ifc_test_init();

//fixme: there isn't go to unremap
	g_slice_reg = (void*)ioremap(SLICE_REG, 0x4);
	if (NULL == g_slice_reg) {
		printk("ioremap of slice reg fail.\n");
	}

	mailbox_out(("mb init OK!\n"));

	return MAILBOX_OK;
}

/*�������ӿڿ�ʼ*/
/*****************************************************************************
�� �� ��  : MAILBOX_RegisterRecvFuncByHandle
��������  : �˼��ʼ����ݽ��ջص�������ע��
�������  : struct mb				*pMailBox	 -- ĳ���˵������ܾ����
unsigned long				MailId		-- ���յ����ʼ���id�š��뷢�ͷ����ʼ�����Ŀ��ID��һ�¡�
mb_cb_func		pFun		-- �ʼ����ݽ��մ���ص�����
�������  : ��
�� �� ֵ  : MAILBOX_OK, �쳣����ֵ
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2012��9��29��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_EXTERN int mailbox_register_cb(
                unsigned int  mailcode,
                void (*cb)(void *mbuf, void *handle, void *data),
                void *usr_handle,
                void *usr_data)
{
    struct mb_cb           *read_cb    = MAILBOX_NULL;
    struct mb_buff         *mbuf = MAILBOX_NULL;
    struct mb              *mb     = MAILBOX_NULL;
    unsigned int           dst_id;

	mb = &g_mailbox_handle;/*�п����ڳ�ʼ��������ע��*/

	/*	����ע��ջص����൱��UnRegister
	if (MAILBOX_NULL == pFun)
	{
	return mailbox_logerro_p1(MAILBOX_ERR_GUT_MAILBOX_NULL_PARAM, mailcode);
	}
	*/
	/*��ĳ��CPU��ĳ������ͨ���е�ĳ���ʼ�Ӧ����ע��ص�����*/
	dst_id = mailbox_get_dst_id(mailcode);

	printk("mb->local_id = %d dst_id = %d\n", mb->local_id, dst_id);

	if (mb->local_id != dst_id) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_TARGET_CPU, mailcode);
	}

	mbuf = mailbox_get_channel_handle(mb, mailcode);
	if (MAILBOX_NULL == mbuf) {
		/*�Ҳ�������ͨ��δ��ʼ����*/
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_CHANNEL_ID, mailcode);
	}

	/*���OK, ��ֵ���ص�����ָ��*/
	read_cb = &mbuf->read_cb[mailbox_get_use_id(mailcode)];
	if (MAILBOX_NULL != read_cb->func) {
		/*mailbox_logerro_p1(MAILBOX_WARNING_USER_CALLBACK_ALREADY_EXIST, mailcode);*/
	}

	mailbox_mutex_lock(&mbuf->mutex);
	read_cb->handle = usr_handle;
	read_cb->data	= usr_data;
	read_cb->func = cb;
	mailbox_mutex_unlock(&mbuf->mutex);

	return MAILBOX_OK;
}

/*��ʼ�������û��ռ�Ļ���fifo������*/
MAILBOX_EXTERN int mailbox_init_usr_queue(struct mb_buff *mb_buf)
{
    unsigned int hsize = sizeof(struct mb_mail);
    struct mb_queue * usrqu = &mb_buf->usr_queue;

	/*��ʼ���û�����fifo,��Ҫ����������Ϣͷ����*/
	mailbox_memcpy((void*)usrqu, (const void*)&mb_buf->mail_queue, sizeof(struct mb_queue));
	if (hsize >  mailbox_queue_left(usrqu->rear, usrqu->front, usrqu->length)) {
		return mailbox_logerro_p1(MAILBOX_FULL, mb_buf->mailcode);
	}

	if (hsize + usrqu->front >= usrqu->base + usrqu->length) {
		usrqu->front = usrqu->front + hsize - usrqu->length;
	} else {
		usrqu->front =	usrqu->front + hsize;
	}
	return MAILBOX_OK;
}

/*��ȡһ����������ͨ��buff*/
MAILBOX_EXTERN int mailbox_request_buff(unsigned int mailcode,  void* mb_buf)
{
    struct mb        *mailbox     = MAILBOX_NULL;
    int     ret_val       = MAILBOX_OK;
    struct mb_buff ** mbuf  = (struct mb_buff **)mb_buf;

	mailbox 	= mailbox_get_mb();
	*mbuf = MAILBOX_NULL;
	if (MAILBOX_NULL == mailbox) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INPUT_PARAMETER, mailcode);
	}

	/*����Ƿ�Ϊ����ͨ��*/
	if (mailbox->local_id != mailbox_get_src_id(mailcode)) {
		return mailbox_logerro_p1(MAILBOX_ERR_GUT_INVALID_SRC_CPU, mailcode);
	}

	/*��ô��ʼ�����ͨ���Ĳ������: open mail*/
	ret_val = mailbox_request_channel(mailbox, mbuf, mailcode);
	if (MAILBOX_OK == ret_val) {
		(*mbuf)->mb = mailbox;
		ret_val = mailbox_init_usr_queue(*mbuf);
		if (MAILBOX_OK == ret_val) {
			return	MAILBOX_OK;
		} else {
			mailbox_release_channel(mailbox, *mbuf);
			*mbuf = MAILBOX_NULL;
			return ret_val;
		}
	} else {
		return ret_val;
	}
}

/*���û�����������������ͨ��buff*/
MAILBOX_EXTERN int mailbox_write_buff(
                struct mb_queue      *queue,
                 char                *data,
                unsigned int         size)
{
	if ((size  <= mailbox_queue_left(queue->rear, queue->front, queue->length)) &&
		(size + sizeof(struct mb_mail)	<= mailbox_queue_left(queue->rear, queue->front, queue->length))
	   ) {
		return mailbox_queue_write(queue, (char*)data, size);
	}
	return 0;
}

/*��ȡ��������ͨ������*/
MAILBOX_EXTERN int mailbox_read_buff(
                struct mb_queue      *queue,
                 char                *data,
                unsigned int         size)
{
	return mailbox_queue_read(queue, (char*)data, size);
}
/*��Ҫ���������ṩ�Ľӿڣ���gut.c����ʵ��*/

/*���ţ�׼������*/
MAILBOX_EXTERN int mailbox_sealup_buff(struct mb_buff * mb_buf , unsigned int usr_size)
{

    struct mb_mail        mail = {0};
    struct mb_queue      *m_queue   = MAILBOX_NULL;
    unsigned int         time_stamp;
    unsigned long         mail_addr;

	m_queue = &mb_buf->mail_queue;

    /*�ж��Ƿ񳬹����η�������С*/
    if (usr_size > (mb_buf->config->single_max - sizeof(struct mb_mail) )){
        return (int) mailbox_logerro_p2(MAILBOX_ERR_GUT_WRITE_EXCEED_MAX_SIZE,
            usr_size ,mb_buf->mailcode);
    } else {
    }

    time_stamp = (unsigned int)mailbox_get_timestamp();
    /*�����Ϣͷ*/
    mail.ulPartition   =  MAILBOX_MSGHEAD_NUMBER;
    mail.ulWriteSlice  =  time_stamp;
    mail.ulReadSlice   =  0;
    mail.ulPriority    =  0;/*�����Ժ�OM�˶��ѷ�������ʹ��*/
    mail.ulSeqNum      =  mb_buf->seq_num;
    mail.ulMsgLength   =  usr_size ;
    mail.ulMailCode    =  mb_buf->mailcode;

    if (MAILBOX_SEQNUM_START == mb_buf->seq_num) {
        (void)mailbox_logerro_p1(MAILBOX_INFO_SEND_FIRST_MAIL, mb_buf->mailcode);
    }

    mb_buf->seq_num++;

	/*�����������д���ʼ�ͷ�������¶���״̬��¼��ʱ�ṹ��*/
	mail_addr = m_queue->front;
	mailbox_queue_write(m_queue, (char*)(&mail), sizeof(struct mb_mail));

	/*�������价�λ�����Ϣ*/
	m_queue->front = mailbox_align_size(mb_buf->usr_queue.front, MAILBOX_ALIGN);

	mailbox_flush_buff(mb_buf); /*������ͨ������������Ϣд������ͷ��*/


	mailbox_record_send(&(mb_buf->mntn), mb_buf->mailcode, time_stamp, mail_addr);

	/*׼����һ���ʼ�д��*/
	return mailbox_init_usr_queue(mb_buf);
}

/*****************************************************************************
�� �� ��  : mailbox_flush_buff
�ӿ�����  : ���ڽӿ�
��������  : ��������Ϣ���е�ͷβָ��д������ͷ

�������  : mb_buff* fpMailBox	- ����ͨ��������
�������  : ��
�� �� ֵ  : ����ر��Ƿ�ɹ�
���ú���  :
��������  :

�޸���ʷ	  :
1.��	��	 : 2013��5��08��
��	  ��   : Ī�� 00176101
�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_EXTERN int mailbox_flush_buff( struct mb_buff *mbuff)
{
    struct mb_head       *head = MAILBOX_NULL;
    struct mb_queue      *queue   = MAILBOX_NULL;
    unsigned int         channel_id    = mbuff->channel_id;
    struct mb *mb         = mbuff->mb;
    /*������ͨ������������Ϣд������ͷ��*/
    head = (struct mb_head*)mbuff->config->head_addr;
    queue   = &mbuff->mail_queue;

    /*��Ҫ�����Ƕ�����д*/
    if (mb->local_id == mailbox_get_src_id(channel_id)) {
        /*д�رգ���������ͷдָ��,ͬʱ�ͷ�������Դ*/
        head->ulFront      = (unsigned int)(queue->front - queue->base ) / sizeof(unsigned int) ;
        head->ulFrontslice = (unsigned int)mailbox_get_timestamp();

    } else if (mb->local_id == mailbox_get_dst_id(channel_id)) {
        /*���رգ�ֻ��������ͷ��ָ��*/
        head->ulRear        =  (unsigned int)(queue->rear - queue->base ) / sizeof(unsigned int);
        head->ulRearslice   =  (unsigned int)mailbox_get_timestamp();
    }

	return MAILBOX_OK;
}

MAILBOX_EXTERN int mailbox_send_buff(struct mb_buff * mbuf)
{
	return mailbox_delivery(mbuf->channel_id);
}

MAILBOX_EXTERN int mailbox_release_buff(struct mb_buff * mbuf)
{
	return mailbox_release_channel(mbuf->mb, mbuf);
}

MAILBOX_EXTERN unsigned long mailbox_virt_to_phy(unsigned long  virt_addr)
{
	unsigned long offset = 0;
	if(NULL == g_shareMemBase) {
		g_shareMemBase = ioremap(MAILBOX_MEM_BASEADDR, MAILBOX_MEM_LENGTH);
	}
	offset = (unsigned long)g_shareMemBase - MAILBOX_MEM_BASEADDR;

	return (virt_addr - offset);
}

MAILBOX_EXTERN unsigned long mailbox_phy_to_virt(unsigned long  phy_addr)
{
	unsigned long offset = 0;
	if(NULL == g_shareMemBase) {
		g_shareMemBase = ioremap(MAILBOX_MEM_BASEADDR, MAILBOX_MEM_LENGTH);
	}
	offset = (unsigned long)g_shareMemBase - MAILBOX_MEM_BASEADDR;


	return (phy_addr + offset);
}


