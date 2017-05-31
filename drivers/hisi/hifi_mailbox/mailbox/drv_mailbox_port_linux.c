/******************************************************************************

			  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
�� �� ��   : drv_mailbox_vxworks.c
�� �� ��   : ����
��	  ��   : Ī�� 00176101
��������   : 2012��9��24��
����޸�   :
��������   : mailbox C��  linuxƽ̨ϵͳ�����ļ�
�����б�   :

�޸���ʷ   :
1.��	��	 : 2012��10��24��
��	  ��   : ���׳� 00209607
�޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/

#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/semaphore.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/sched.h>
#include <linux/sched/rt.h>
#include <linux/delay.h>
#include <linux/freezer.h>
#include <linux/completion.h>
#include <linux/wakelock.h>
#include <linux/wait.h>
#include <linux/spinlock.h>

//#include "excDrv.h"
//#include "BSP.h"
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_debug.h"
//#include "drv_mailbox_linux.h"
#include "bsp_drv_ipc.h"

/*****************************************************************************
  1 ��ά�ɲ���Ϣ�а�����C�ļ���ź궨��
*****************************************************************************/
#undef	_MAILBOX_FILE_
#define _MAILBOX_FILE_	 "linux"
/*lint -e750*/
#define MAILBOX_MILLISEC_PER_SECOND 					  1000

#define  MAILBOX_LINUX_SEND_FULL_DELAY_MS				  10		 /*�������ӳٺ���*/

#define  MAILBOX_LINUX_SEND_FULL_DELAY_TIMES			  0 		 /*�������ӳ��ٳ��Դ���*/

enum MAILBOX_LOCK_TYPE
{
	MAILBOX_LOCK_SEMAPHORE = 0x00010000,
	MAILBOX_LOCK_SPINLOCK  = 0x00020000
};
/*****************************************************************************
  ����C��vxworks����ϵͳ���������ݵĴ���ӿڵ��÷�ʽ
*****************************************************************************/
#define MAILBOX_PROC_MASK  0x0000ffff
enum MAILBOX_LINUX_PROC_STYLE_E
{
    MAILBOX_SEND   = 0,  
    
    MAILBOX_RECEV_START,
    
    /*�ҽ��������ϵ��ʼ�������п�ʼ*/
    MAILBOX_RECV_TASK_START,
    MAILBOX_RECV_TASK_NORMAL,
    MAILBOX_RECV_TASK_HIGH,

    /*�ҽ��������ϵ��ʼ�������н���*/
    MAILBOX_RECV_TASK_END,

    /*tasklet���洦�����Ϣ*/
    MAILBOX_RECV_TASKLET,
    MAILBOX_RECV_TASKLET_HI,

    /*���ж��д�����ʼ��������*/
    MAILBOX_RECV_INT_IRQ,
    MAILBOX_RECV_END,
};

/*****************************************************************************
    ����C�����䵥������ҽӵ����乤�����м�������
*****************************************************************************/
struct mb_local_work
{
    unsigned int             channel_id;      /*����ID�ţ������Ǻ˼�����ID,Ҳ����������ͨ��ID*/
    unsigned int             data_flag;       /*�������Ƿ������ݵı�־λ*/
    int		      (*cb)(unsigned int channel_id);
    struct mb_local_work            *next;          /*ָ����һ��*/
    void                     *mb_priv;
};

/*****************************************************************************
  ����C������������ص�����
*****************************************************************************/
struct mb_local_proc
{
    signed char                 proc_name[16];   /*����ʽ����*/
    unsigned int               proc_id;         /*����ʽID��*/
    signed int                 priority;       /*�������ȼ�*/
    struct mb_local_work       *work_list;      /*������ҽӵ����䴦�����*/
    wait_queue_head_t           wait;           /*����ʽ�ȴ�����Ϣ*/
    struct tasklet_struct       tasklet;        /*tasklet��ʽ�ľ��*/
    int                         incoming;

};

/*****************************************************************************
  ������������ͨ�������񣬺˼��жϼ����ջص�����֮��Ķ�Ӧ��ϵ
*****************************************************************************/
struct mb_local_cfg
{
    unsigned int               channel_id;      /*����ͨ��ID��*/
    unsigned int               property;      /*ͨ������*/
    unsigned int               int_src;         /*����ͨ����ʹ�õĺ˼��ж���Դ�š�*/
    unsigned int               dst_id;          /*����ͨ����ʹ�õĺ˼��ж�Ŀ��CPU��*/
};

struct mb_mutex
{
    void          *lock;
    unsigned long  flags;
    unsigned int  type;
};

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
static struct wake_lock mb_lpwr_lock; /*��ֹ�ڻ��Ѻ󣬴����ʼ������н���˯��*/

/*�������������б�*/
MAILBOX_LOCAL struct mb_local_proc g_mailbox_local_proc_tbl[] =
{
    /*����ʽ���ʼ����ݴ���*/
    {"mailboxNormal",   MAILBOX_RECV_TASK_NORMAL,   86,  0, },
    {"mailboxHigh",     MAILBOX_RECV_TASK_HIGH,     99,  0, },

    /*tasklet ��ʽ������Ϣ*/
    {"mailboxTasklet",  MAILBOX_RECV_TASKLET,     0,  0, },
    {"mailboxTasklet",  MAILBOX_RECV_TASKLET_HI,     0,  0, },

    /*�жϷ�ʽ���ʼ����ݴ���*/
    {"mailboxInt",      MAILBOX_RECV_INT_IRQ,     0,  0, },

    /*���ڴ˺���������ʽ��Ŀ�������Ӱ��UT����*/

    /*����*/
};

/*A�˵�����ͨ����Դ��ƽ̨ϵͳ��Դ��Ӧ��ϵ���ñ�*/
MAILBOX_LOCAL struct mb_local_cfg g_mb_local_cfg_tbl[] =
{
    /*����ͨ��������*/
    /*ChannelID*/                                   /*ͨ������*/             
    {MAILBOX_MAILCODE_RESERVED(MCU,  ACPU, MSG),    MAILBOX_RECV_TASKLET_HI,     0    },
    {MAILBOX_MAILCODE_RESERVED(HIFI, ACPU, MSG),    MAILBOX_RECV_TASKLET_HI,     0    },
    {MAILBOX_MAILCODE_RESERVED(CCPU, ACPU, MSG),    MAILBOX_RECV_TASKLET_HI,     0    },
    {MAILBOX_MAILCODE_RESERVED(CCPU, ACPU, IFC),    MAILBOX_RECV_TASK_NORMAL,   0    },
    {MAILBOX_MAILCODE_RESERVED(MCU, ACPU, IFC),     MAILBOX_RECV_TASK_HIGH,   0    },

    /*����ͨ������*/
    /*ChannelID*/                                   /*ͨ������*/                
    {MAILBOX_MAILCODE_RESERVED( ACPU, MCU,  MSG),   MAILBOX_SEND | MAILBOX_LOCK_SPINLOCK,   0    },
    {MAILBOX_MAILCODE_RESERVED( ACPU, HIFI, MSG),   MAILBOX_SEND | MAILBOX_LOCK_SPINLOCK,   0    },

    {MAILBOX_MAILCODE_RESERVED( ACPU, CCPU, MSG),   MAILBOX_SEND |
     MAILBOX_LOCK_SEMAPHORE /*�����Ϣͨ����ΪIFC�ķ���ͨ���������IFCִ�з���
                               ������˯�߶���������Ϣͨ����ֻ�����ź���������*/
    ,   0    },
    
    {MAILBOX_MAILCODE_RESERVED( ACPU, CCPU, IFC),   MAILBOX_SEND | MAILBOX_LOCK_SEMAPHORE,   0    },
    {MAILBOX_MAILCODE_RESERVED( ACPU, MCU,  IFC),   MAILBOX_SEND | MAILBOX_LOCK_SEMAPHORE,   0    },
    
    /*���ڴ˺�����ͨ�����ã������Ӱ��UT����*/

    /*������־*/
    {MAILBOX_MAILCODE_INVALID, 0,0}
};

MAILBOX_LOCAL void *mailbox_mutex_create(struct mb_local_cfg *local_cfg);
/*****************************************************************************
  3 ��������
*****************************************************************************/
MAILBOX_LOCAL void mailbox_receive_process(unsigned long data)
{
    struct mb_local_proc *proc = (struct mb_local_proc *)data;
    struct mb_local_work *work = proc->work_list;

    
    while (MAILBOX_NULL != work) {
        /*������־λ���������λ�����ö�Ӧ������ID�ŵĻص�����*/
        if (MAILBOX_TRUE == work->data_flag) {
            work->data_flag = MAILBOX_FALSE;
            mailbox_record_sche_recv(work->mb_priv);
            if (MAILBOX_NULL != work->cb) {
                if (MAILBOX_OK !=  work->cb(work->channel_id))
                {
                     mailbox_logerro_p1(MAILBOX_ERR_LINUX_CALLBACK_ERRO, work->channel_id);
                }
            } else {
                mailbox_logerro_p1(MAILBOX_ERR_LINUX_CALLBACK_NOT_FIND, work->channel_id);
            }
        }
        work = work->next;
    }
    wake_unlock(&mb_lpwr_lock);
}
/*****************************************************************************
 �� �� ��  : mailbox_receive_task
 ��������  : ���ڽӿ�
 ��������  : ���ݽ�������������
 �������  :struct mb_local_proc *pProcCfg - �������������þ��

 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��19��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_receive_task(void * data)
{
    struct mb_local_proc *proc = (struct mb_local_proc *)data;
    struct sched_param param;

    param.sched_priority = (proc->priority < MAX_RT_PRIO) ? proc->priority : (MAX_RT_PRIO-1);
    (void)sched_setscheduler(current, SCHED_FIFO, &param);

    /*set_freezable();*/          /*  advised by l56193         */

    do {
        wait_event(proc->wait, proc->incoming);
        proc->incoming = MAILBOX_FALSE;

        mailbox_receive_process((unsigned long)data);
        
    }while (!kthread_should_stop());
    return MAILBOX_OK;
}

/*������˵Ķ����ṩ�ӿ�*/
/*****************************************************************************
 �� �� ��  : mailbox_init_platform
 �ӿ�����  : ����ӿ�
 ��������  : ����ģ��ƽ̨���䲿�ֳ�ʼ��,��ʼ�����䲢��ʼ����ƽ̨��صĲ��컯���֣��������ʼ����ʱ����á�
 �������  :

 �������  : ��
 �� �� ֵ  : �̲߳������
 ���ú���  :
 ��������  : mailbox_init_platform()

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_EXTERN int mailbox_init_platform(void)
{
    struct mb_local_proc     *local_proc    = &g_mailbox_local_proc_tbl[0];
    unsigned int            count    =  sizeof(g_mailbox_local_proc_tbl) / sizeof(struct mb_local_proc);
    unsigned int            proc_id;
    struct task_struct *task = MAILBOX_NULL;

    wake_lock_init(&mb_lpwr_lock, WAKE_LOCK_SUSPEND, "mailbox_low_power_wake_lock");

    /*����ƽ̨�����ж��ź�������*/
    while(count) {
        /*Ϊ������ʽ������ͨ����������*/
        proc_id = local_proc->proc_id;
        if((proc_id > MAILBOX_RECV_TASK_START) && (proc_id < MAILBOX_RECV_TASK_END)) {
            
            /* ���������������ȴ��ź���*/
            init_waitqueue_head(&local_proc->wait);
                
            /* �������������ݴ�������*/
            task = kthread_run(mailbox_receive_task, (void*)local_proc, local_proc->proc_name);
            if (IS_ERR(task)) {
                return mailbox_logerro_p1(MAILBOX_ERR_LINUX_TASK_CREATE, proc_id);
            }
        }

        if ((MAILBOX_RECV_TASKLET == proc_id) || 
           (MAILBOX_RECV_TASKLET_HI == proc_id)) {
	        tasklet_init(&local_proc->tasklet,
		    mailbox_receive_process, (unsigned long)local_proc);
        
        }
        count--;
        local_proc++;
    }

    return MAILBOX_OK;
}

/*****************************************************************************
 �� �� ��  : mailbox_ipc_process
 �ӿ�����  : ���ڽӿ�
 ��������  : ���ø����ʼ������ö�Ӧ���ʼ��������б�־λ����������Ϣ֪ͨ��������
 �������  :  struct mb_local_work *pQueueList   --  ���乤������
              struct mb_local_proc    *pMailBoxTask --  ���䴦����
              unsigned long ChannelId -- ����ͨ����
              unsigned long ProcId    -- ����ͨ������ʽID
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��24��
    ��    ��   : Ī�� 00176101
    �޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_ipc_process(
                struct mb_local_work  *local_work,
                struct mb_local_proc  *local_proc,
                unsigned int channel_id,
                unsigned int proc_id)
{
    unsigned int is_find = MAILBOX_TRUE;

    while (local_work) {
        /*�����乤���������ҵ���Ӧ�����䣬���ñ�־λ���ͷ��ź���֪ͨ��������*/
        if (channel_id  == local_work->channel_id) {
            /*�����������乤�����������д���������ݱ�־λ*/
            local_work->data_flag = MAILBOX_TRUE;
            
            mailbox_record_sche_send(local_work->mb_priv);
            wake_lock(&mb_lpwr_lock);

            if ((proc_id > MAILBOX_RECV_TASK_START)
                && (proc_id < MAILBOX_RECV_TASK_END)) {
             
                /*�ͷ��ź�����֪ͨ����*/
                local_proc->incoming = MAILBOX_TRUE;
                wake_up(&local_proc->wait);

            } else if(MAILBOX_RECV_TASKLET_HI == proc_id) {
                 /*tasklet����ʽ����tasklet�д�����������*/
                tasklet_hi_schedule(&local_proc->tasklet);
                 
            } else if(MAILBOX_RECV_TASKLET == proc_id) {
                 /*tasklet����ʽ����tasklet�д�����������*/
                tasklet_schedule(&local_proc->tasklet);
                 
            } else if(MAILBOX_RECV_INT_IRQ == proc_id) {
                /*�жϴ���ʽ�����ж���ֱ�Ӵ�����������*/
                mailbox_receive_process((unsigned long)local_proc);
                
            } else {
                is_find = MAILBOX_FALSE;
            }

		}

		local_work = local_work->next;
	}

	return is_find;
}

/*****************************************************************************
 �� �� ��  : mailbox_ipc_int_handle
 �ӿ�����  : ���ڽӿ�
 ��������  : ���ø����ʼ������ö�Ӧ���ʼ��������б�־λ����������Ϣ֪ͨ��������
 �������  :  unsigned long    MailBoxID  --�����ڲ�������ţ������ڲ������ȫϵͳΨһ�����кţ�


 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��9��24��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL int mailbox_ipc_int_handle(unsigned int int_num)
{
    struct mb_local_cfg         *local_cfg    =  &g_mb_local_cfg_tbl[0];
    struct mb_local_proc        *local_proc   =   MAILBOX_NULL;
    struct mb_local_work        *local_work      =   MAILBOX_NULL;
    unsigned int count = sizeof(g_mailbox_local_proc_tbl)/sizeof(struct mb_local_proc);
    unsigned int proc_id = 0;
    unsigned int channel_id = 0;
    unsigned int is_find = MAILBOX_FALSE;
    unsigned int ret_val = MAILBOX_OK;

    /*�ҵ�����ID��Ӧ����������*/
    while (MAILBOX_MAILCODE_INVALID != local_cfg->channel_id) {
        /*�������йҽӵ�����жϺŵĽ�������ͨ��*/
        proc_id = local_cfg->property;
        if ((int_num == local_cfg->int_src) && (MAILBOX_SEND 
              != (MAILBOX_PROC_MASK & local_cfg->property))) {
            channel_id = local_cfg->channel_id;


            local_proc   =  &g_mailbox_local_proc_tbl[0];
            count          =   sizeof(g_mailbox_local_proc_tbl)/sizeof(struct mb_local_proc);
            while (count) {
                /*�ҵ�������ͨ����Ӧ��������Ϣ*/
                if (proc_id == local_proc->proc_id) {
                    local_work = local_proc->work_list;
                    is_find = mailbox_ipc_process( local_work,
                                                 local_proc,
                                                 channel_id,
                                                 proc_id);
                    break;
                }
                count--;
                local_proc++;
            }

			if (0 == count) {
				ret_val = mailbox_logerro_p1(MAILBOX_ERR_LINUX_MAIL_TASK_NOT_FIND, channel_id);
			}
		}
		local_cfg++;
	}

	if (MAILBOX_TRUE != is_find) {
		ret_val = mailbox_logerro_p1(MAILBOX_ERR_LINUX_MAIL_INT_NOT_FIND, channel_id);
	}

	return ret_val;
}

/*****************************************************************************
 �� �� ��  : mailbox_process_register
 �ӿ�����  : ����ӿ�
 ��������  : ����MailBoxID��pProcessCallBack���һ�׻��ƣ�����MailBoxIDע�᱾ϵͳ�Ķ�Ӧ�˼��ʼ�֪ͨ�жϣ�
				���յ��ʼ�֪ͨ�Ժ󣬵��ö�Ӧ��pProcessCallBack�ص�����
 �������  :  unsigned long 			   MailBoxID  --�����ڲ�������ţ�������
											�������ȫϵͳΨһ�����кţ�
											   --��ID���ڲ��ṹ��DRV_MAILBOX_ID_STRU���塣
			 MAILBOX_PROCSS_FUNCPTR pMainThreadCallBack --�����յ��ʼ���Ĵ���ص�����,
												�˺�������ڲ���������Ĳ���MailBoxID��ֵ

 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��9��24��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_EXTERN int mailbox_process_register(
                unsigned int channel_id, 
                 int (*cb)(unsigned int channel_id),
                 void *priv)
{
    struct mb_local_work        *local_work    =   MAILBOX_NULL;
    struct mb_local_cfg         *local_cfg  =  &g_mb_local_cfg_tbl[0];
    struct mb_local_proc        *local_proc =  &g_mailbox_local_proc_tbl[0];
    struct mb_local_cfg*         find_cfg     =   MAILBOX_NULL;
    unsigned int count = sizeof(g_mailbox_local_proc_tbl)/sizeof(struct mb_local_proc);

	while (MAILBOX_MAILCODE_INVALID != local_cfg->channel_id) {
		/*�ҵ��봫������ID�������ϵͳ��������*/
		if (local_cfg->channel_id ==  channel_id) {
			find_cfg = local_cfg;
			break;
		}
		local_cfg++;
	}

	if (find_cfg) {
		/*�������������Ӧ�����乤������*/
		while (count) {
			if (find_cfg->property == local_proc->proc_id) {
				if (local_proc->work_list) {
					local_work = local_proc->work_list;
					while (MAILBOX_NULL != local_work->next) {
						local_work = local_work->next;
					}
					local_work->next			= (struct mb_local_work *)kcalloc(
													  sizeof(struct mb_local_work), 1, GFP_KERNEL);
					if (NULL == local_work->next)  {
						(void)printk(KERN_ERR "%s: memory alloc error!\n",__func__);
						return MAILBOX_ERR_LINUX_ALLOC_MEMORY;
					}
					local_work->next->channel_id = find_cfg->channel_id;
					local_work->next->cb  = cb;
					local_work->next->next = MAILBOX_NULL;
					local_work->next->mb_priv = priv;

				} else {
					local_proc->work_list	  = (struct mb_local_work *)kcalloc(
													sizeof(struct mb_local_work), 1, GFP_KERNEL);
					if (NULL == local_proc->work_list) {
						(void)printk(KERN_ERR "%s: memory alloc error!\n",__func__);
						return MAILBOX_ERR_LINUX_ALLOC_MEMORY;
					}
					local_proc->work_list->channel_id = find_cfg->channel_id;
					local_proc->work_list->cb  = cb;
					local_proc->work_list->next = MAILBOX_NULL;
					local_proc->work_list->mb_priv = priv;
				}

			}
			count--;
			local_proc++;
		}

		return MAILBOX_OK;
	}

	return	mailbox_logerro_p1(MAILBOX_ERR_LINUX_CHANNEL_NOT_FIND, channel_id);

}

/*****************************************************************************
 �� �� ��  : mailbox_channel_register
 �ӿ�����  : ����ӿ�
 ��������  : ������ͨ������ע�ᵽ�������ϵͳƽ̨
 �������  :  unsigned long ChannelID -- ����ͨ����
			  unsigned long IntNum	  -- �жϺ�
			  unsigned long Direct	  -- ���ͷ���
			  void	 **mutex		  -- ��ͨ������Դ������
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��9��24��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_EXTERN int mailbox_channel_register(
                unsigned int channel_id,
                unsigned int int_src,
                unsigned int dst_id,
                unsigned int direct,
                void   **mutex)
{
	struct mb_local_cfg    *local_cfg  =  &g_mb_local_cfg_tbl[0];
	while (MAILBOX_MAILCODE_INVALID != local_cfg->channel_id) {
		if (channel_id == local_cfg->channel_id) {
			*mutex = mailbox_mutex_create(local_cfg);
			if (MAILBOX_NULL == *mutex) {
				return mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
			}

			/*ͨ����Դ�������ҵ���ע��IPC�ж�*/
			local_cfg->int_src = int_src;
			local_cfg->dst_id  = dst_id;

			if(MIALBOX_DIRECTION_RECEIVE == direct) {
				IPC_IntConnect((IPC_INT_LEV_E)int_src , (VOIDFUNCPTR)mailbox_ipc_int_handle, int_src);
				IPC_IntEnable ((IPC_INT_LEV_E)int_src);

				/*���ST����ͨ��ע��*/
				//test_mailbox_msg_reg(channel_id);
			}
			break;
		}

		local_cfg++;
	}

	/*���������Ҳ�����Ӧ�����ã�����*/
	if (MAILBOX_MAILCODE_INVALID == local_cfg->channel_id) {
		return mailbox_logerro_p1(MAILBOX_ERR_LINUX_CHANNEL_NOT_FIND, channel_id);
	}

	return MAILBOX_OK;
}

/*****************************************************************************
 �� �� ��  : mailbox_delivery
 �ӿ�����  : ����ӿ�
 ��������  : ֪ͨ�Է��˽����ʼ���
 �������  : unsigned long MailBoxID	-	ȫϵͳΨһ������ͨ��ID��

 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��9��24��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

 ��ϸ����: ��д�����ʼ��󣬷��ͺ˼�֪ͨ��֪ͨ�Է��˽����ʼ���
*****************************************************************************/
MAILBOX_EXTERN int mailbox_delivery(unsigned int channel_id)
{
	struct mb_local_cfg 	*local_cfg	  =  &g_mb_local_cfg_tbl[0];
	struct mb_local_cfg 	*find_cfg		=	MAILBOX_NULL;

	while (MAILBOX_MAILCODE_INVALID != local_cfg->channel_id) {
		/*�ҵ��봫������ID�������ϵͳ��������*/
		if (local_cfg->channel_id == channel_id) {
			find_cfg = local_cfg;
			break;
		}
		local_cfg++;
	}

    if (MAILBOX_NULL != find_cfg) {
        return (int)IPC_IntSend((IPC_INT_CORE_E)find_cfg->dst_id,
                                (IPC_INT_LEV_E)find_cfg->int_src);
    }

	return mailbox_logerro_p1(MAILBOX_ERR_LINUX_CHANNEL_NOT_FIND, channel_id);
}


/*****************************************************************************
 �� �� ��  : mailbox_mutex_create
 ��������  : ����������Դ���̻߳����ź���
 �������  : void
 �������  : ��
 �� �� ֵ  : �ɹ����ؾ������ʧ�ܷ��ؿ�
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��9��24��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

*****************************************************************************/
MAILBOX_LOCAL void *mailbox_mutex_create(struct mb_local_cfg *local_cfg)
{
    unsigned int channel_id = local_cfg->channel_id;
	struct mb_mutex* mtx = MAILBOX_NULL;

	/*���ݲ�ͬͨ���������벻ͬ����Դ������*/
	mtx = (struct mb_mutex*)kmalloc(sizeof(struct mb_mutex), GFP_KERNEL);
	if (!mtx) {
		mailbox_logerro_p1(MAILBOX_ERR_LINUX_CHANNEL_NOT_FIND, channel_id);
		goto error_exit;
	}

	if ((local_cfg->property > MAILBOX_RECEV_START) &&
		(local_cfg->property < MAILBOX_RECV_END)) {
		/*����ͨ������ʹ�������������ڻص�ע�ᱣ��*/
		mtx->lock = kmalloc(sizeof(spinlock_t), GFP_KERNEL);
		if (mtx->lock) {
			spin_lock_init((spinlock_t*)mtx->lock);
			mtx->type = MAILBOX_LOCK_SPINLOCK;
		} else {
			mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
			goto error_exit;
		}
	} else {
		if (MAILBOX_LOCK_SEMAPHORE & local_cfg->property) {
			mtx->lock = kmalloc(sizeof(struct semaphore), GFP_KERNEL);
			if (mtx->lock) {
				sema_init(mtx->lock, 1);
				mtx->type = MAILBOX_LOCK_SEMAPHORE;
			} else {
				mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
				goto error_exit;
			}
		} else if (MAILBOX_LOCK_SPINLOCK & local_cfg->property) {
			mtx->lock = kmalloc(sizeof(spinlock_t), GFP_KERNEL);
			if (mtx->lock) {
				spin_lock_init((spinlock_t*)mtx->lock);
				mtx->type = MAILBOX_LOCK_SPINLOCK;
			} else {
				mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
				goto error_exit;
			}
		} else {
			mailbox_logerro_p1(MAILBOX_CRIT_PORT_CONFIG, channel_id);
			goto error_exit;
		}
	}
	return mtx;

error_exit:
	if (mtx)
		kfree(mtx);

	return (void *)0;
}

/*****************************************************************************
 �� �� ��  : mailbox_mutex_lock
 ��������  : ����ͨ����Դ�������
 �������  : void **mutexId  ָ�򻥳���������ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��9��24��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

 ��ϸ����: ʹ�õ��ź����������жϷ�ʽʵ��,�Զ�������ʵĽϴ�δ������Դ���б�����

*****************************************************************************/
MAILBOX_EXTERN int mailbox_mutex_lock(void **mutexId)
{
	struct mb_mutex *mtx = (struct mb_mutex *)*mutexId;

	if (MAILBOX_LOCK_SEMAPHORE == mtx->type ) {
		down((struct semaphore*)mtx->lock);
	} else if (MAILBOX_LOCK_SPINLOCK == mtx->type ) {
		spin_lock_irqsave((spinlock_t*)mtx->lock, mtx->flags);
	}

	return MAILBOX_OK;
}

/*****************************************************************************
 �� �� ��  : mailbox_mutex_lock
 ��������  : ����ͨ����Դ�����˳�
 �������  : void **mutexId  ָ�򻥳���������ָ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��9��24��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

 ��ϸ����: ʹ���ͷ��ź������߽����жϷ�ʽʵ��

*****************************************************************************/
MAILBOX_EXTERN void mailbox_mutex_unlock(void **mutexId)
{
	struct mb_mutex *mtx = (struct mb_mutex *)*mutexId;

	if (MAILBOX_LOCK_SEMAPHORE == mtx->type ) {
		up((struct semaphore*)mtx->lock);
	} else	if (MAILBOX_LOCK_SPINLOCK == mtx->type ) {
		spin_unlock_irqrestore((spinlock_t*)mtx->lock, mtx->flags);
	}

	return ;
}

MAILBOX_EXTERN void *mailbox_init_completion(void)
{
	struct completion *wait;
	wait = (struct completion*)kmalloc(sizeof(struct completion), GFP_KERNEL);
	if(!wait) {
		return MAILBOX_NULL;
	}
	init_completion(wait);

	return (void*)wait;
}

MAILBOX_EXTERN int mailbox_wait_completion(void **wait, unsigned int timeout)
{
	long jiffies = msecs_to_jiffies(timeout);
	long ret =	wait_for_completion_timeout(*wait, jiffies);

	return (ret > 0) ? MAILBOX_OK : MAILBOX_ERRO ;
}

MAILBOX_EXTERN void mailbox_complete(void **wait)
{
	complete(*wait);
}

MAILBOX_EXTERN void mailbox_del_completion(void **wait)
{
	kfree(*wait);
}

/*****************************************************************************
 �� �� ��  : mailbox_memcpy
 ��������  : �ڴ濽������
 �������  : void		*Destination  -- Ŀ�ĵ�ַ
			 const void *Source 	  -- Դ��ַ
			 long		 Size		   -- ����
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��11��07��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

 ��ϸ����: ʵ��memcpy����

*****************************************************************************/
MAILBOX_EXTERN void *mailbox_memcpy(void *Destination, const void *Source, unsigned int Size)
{

	return (void *)memcpy(Destination, Source, Size);
}

/*****************************************************************************
 �� �� ��  : mailbox_memset
 ��������  : �ڴ濽������
 �������  : void		*Destination  -- Ŀ�ĵ�ַ
			 const void *Source 	  -- Դ��ַ
			 long		 Size		   -- ����
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��11��07��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

 ��ϸ����: ʵ��memset����

*****************************************************************************/
MAILBOX_EXTERN void *mailbox_memset(void * m, int c, unsigned int size)
{

	return memset(m, c, size);
}

/*****************************************************************************
 �� �� ��  : mailbox_assert
 ��������  : �쳣���ԣ����ڵ��ԡ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��9��24��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���
*****************************************************************************/
MAILBOX_EXTERN void mailbox_assert(unsigned int ErroNo)
{

}

/*****************************************************************************
 �� �� ��  : mailbox_int_context
 ��������  : ����ǲ������ж���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ɹ�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��10��25��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���
*****************************************************************************/
MAILBOX_EXTERN int mailbox_int_context(void)
{
	return	in_interrupt();
}


/*****************************************************************************
 �� �� ��  : mailbox_scene_delay
 ��������  : ���ݴ���ĳ����ţ������ӳٲ�������״̬
 �������  : unsigned long SceneID		--	��ʱ������
			 unsigned long TryTimes 	--	�˳����ڼ��εȴ�
 �������  : ��
 �� �� ֵ  : �Ƿ�����ȴ�
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��11��29��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���
*****************************************************************************/
MAILBOX_EXTERN int mailbox_scene_delay(unsigned int scene_id, int *try_times)
{
    unsigned int go_on = MAILBOX_FALSE;
    unsigned int delay_ms = 0;

    switch (scene_id)
    {
        case MAILBOX_DELAY_SCENE_MSG_FULL:
        case MAILBOX_DELAY_SCENE_IFC_FULL:

			delay_ms = MAILBOX_LINUX_SEND_FULL_DELAY_MS;

			go_on = (*try_times >= MAILBOX_LINUX_SEND_FULL_DELAY_TIMES) ?
					MAILBOX_FALSE : MAILBOX_TRUE;

			break;
		default:

			break;
	}

	if (MAILBOX_TRUE == go_on) {
		msleep(delay_ms);
	}

	*try_times = *try_times + 1;
	return go_on;
}

/*****************************************************************************
 �� �� ��  : mailbox_get_timestamp
 ��������  : ���ʱ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ϵͳʱ�������λ(us)
 ���ú���  :
 ��������  :

 �޸���ʷ	   :
  1.��	  ��   : 2012��10��16��
	��	  ��   : Ī�� 00176101
	�޸�����   : �����ɺ���

��������: ����ϵͳ��ʱ���������CPU���ã���Ϊ��Ϣ����ʱ����ߴ���ʱ��Ĳ��ա�
*****************************************************************************/
extern void * g_slice_reg;
MAILBOX_EXTERN int mailbox_get_timestamp(void)
{
	if (g_slice_reg) {
		return (long)readl(g_slice_reg);
	}
	return 0;

}


