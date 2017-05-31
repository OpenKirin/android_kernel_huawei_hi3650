/*
 * voice_proxy_debug.c - HW voice proxy debug in kernel, it is used for debuging the voice proxy.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 */

#include <linux/kthread.h>
#include "voice_proxy.h"

/*lint -e750 -e838 -e528 -e753 -e754*/
#define TFAGENT_SLEEP_TIME_MSECS (1)
#define HIFI_SLEEP_TIME_MSECS (20)
#define CLASS_NAME    "voice_proxy_debug"

LIST_HEAD(debug_mailbox_cmd_queue);
LIST_HEAD(debug_vowifi_data_queue);

extern int32_t voice_proxy_mailbox_cb_init(void);
extern void voice_proxy_mailbox_cb_register(mailbox_send_msg_cb snd_cb,
                                            read_mailbox_msg_cb read_cb,
                                            register_mailbox_cb register_cb);
extern int32_t proxy_push_data(void *data);
extern int32_t proxy_pull_data(int8_t *data, int32_t size);

typedef void (*voice_proxy_debug_handle_mail_cb)(void *usr_para, void *mail_handle, int32_t mail_len);

struct voice_proxy_debug_priv {
	spinlock_t debug_mailbox_lock;
	spinlock_t debug_tfagent_lock;
	spinlock_t debug_wifi_lock;

	wait_queue_head_t debug_mailbox_waitq;
	wait_queue_head_t debug_tfagent_waitq;

	int32_t debug_mailbox_wait_flag;
	int32_t debug_tfagent_wait_flag;

	struct task_struct *debug_mailbox_thread;
	struct task_struct *debug_hifi_thread;
	struct task_struct *debug_tfagent_thread;

	int32_t debug_hifi_sleep_time;
	int32_t debug_tf_sleep_time;
	int32_t debug_snd_data_order;
	int32_t debug_tf_lost_index;
	int32_t debug_tf_lost_enable;
	int32_t debug_mail_lost_cnf_count;
	int32_t debug_mail_lost_cnf_enable;

	voice_proxy_debug_handle_mail_cb debug_handle_mail;
};

static struct voice_proxy_debug_priv s_priv;
static struct class  *sclass;

static uint32_t ssw = 0;
static uint32_t paraw = 0;

static int32_t debug_create_list_data_node(struct voice_proxy_data_node **node, int8_t *data, uint32_t size)
{
	struct voice_proxy_data_node *n = NULL;

	BUG_ON(NULL == data);/*lint !e730*/
	BUG_ON(NULL == node);/*lint !e730*/

	n = kzalloc(sizeof(*n) + size, GFP_ATOMIC);
	if (!n) {
		loge("n kzalloc failed\n");
		return -ENOMEM;
	}

	memset(n, 0, sizeof(*n) + size);
	memcpy(n->list_data.data, data, (size_t)size);
	n->list_data.size = (int32_t)size;
	*node = n;

	return 0;
}

static int32_t debug_snd_cmd_list_node(uint16_t msg_id)
{
	struct voice_proxy_cmd_node *cmd = NULL;

	BUG_ON(ID_PROXY_VOICE_LTE_RX_NTF > msg_id);/*lint !e730*/
	BUG_ON(ID_PROXY_VOICE_DATA_MSGID_BUT < msg_id);/*lint !e730*/

	cmd = kmalloc(sizeof(*cmd), GFP_ATOMIC);
	if (!cmd) {
		loge("cmd kmalloc failed\n");
		return -ENOMEM;
	}
	memset(cmd, 0, sizeof(*cmd));

	cmd->msg_id = msg_id;
	logi("command type :0x%x\n",cmd->msg_id);

	spin_lock_bh(&s_priv.debug_mailbox_lock);
	list_add_tail(&cmd->list_node, &debug_mailbox_cmd_queue);
	s_priv.debug_mailbox_wait_flag++;
	spin_unlock_bh(&s_priv.debug_mailbox_lock);
	wake_up(&s_priv.debug_mailbox_waitq);

	return 0;
}

static int32_t debug_get_wifi_list_node(struct voice_proxy_data_node **node)
{
	struct voice_proxy_data_node *n = NULL;

	BUG_ON(NULL == node);/*lint !e730*/

	spin_lock_bh(&s_priv.debug_wifi_lock);
	if (!list_empty_careful(&debug_vowifi_data_queue)) {
		n = list_first_entry(&debug_vowifi_data_queue,
                                             struct voice_proxy_data_node,
                                             list_node);/*lint !e826*/

		list_del_init(&n->list_node);
		*node = n;
	}
	spin_unlock_bh(&s_priv.debug_wifi_lock);

	return 0;
}

static int32_t debug_read_mailbox_msg(void *command, int8_t *buf, int32_t *size)
{
	int32_t ret = 0;
	uint16_t msg_id = 0;
	int8_t *mail_buf = NULL;
	int32_t mail_buf_len;
	struct voice_proxy_confirm comfirm;
	struct voice_proxy_data_node *node = NULL;
	struct voice_proxy_lte_rx_notify lte_rx_notify;
	struct voice_proxy_lte_tx_notify lte_tx_notify;
	struct voice_proxy_wifi_rx_notify *wifi_rx_notify = NULL;
	struct voice_proxy_wifi_tx_notify wifi_tx_notify;

	BUG_ON(NULL == command);/*lint !e730*/
	BUG_ON(NULL == buf);/*lint !e730*/
	BUG_ON(NULL == size);/*lint !e730*/

	memset(&comfirm, 0, sizeof(comfirm));

	msg_id = *(uint16_t *)command;

	switch	(msg_id) {
	case ID_VOICE_PROXY_LTE_RX_CNF:
		comfirm.msg_id = ID_VOICE_PROXY_LTE_RX_CNF;
		mail_buf = (int8_t *)&comfirm;
		mail_buf_len = sizeof(comfirm);
		break;

	case ID_VOICE_PROXY_LTE_TX_CNF:
		comfirm.msg_id = ID_VOICE_PROXY_LTE_TX_CNF;
		mail_buf = (int8_t *)&comfirm;
		mail_buf_len = sizeof(comfirm);
		break;

	case ID_VOICE_PROXY_LTE_RX_NTF:
		lte_rx_notify.msg_id = ID_VOICE_PROXY_LTE_RX_NTF;
		memset(lte_rx_notify.data, 0xa7, sizeof(uint16_t)*PROXY_VOICE_CODEC_MAX_DATA_LEN);
		mail_buf = (int8_t *)&lte_rx_notify;
		mail_buf_len = sizeof(lte_rx_notify);
		break;

	case ID_VOICE_PROXY_LTE_TX_NTF:
		lte_tx_notify.msg_id = ID_VOICE_PROXY_LTE_TX_NTF;
		memset(lte_tx_notify.data, 0xc1, sizeof(uint16_t)*PROXY_VOICE_CODEC_MAX_DATA_LEN);
		mail_buf = (int8_t *)&lte_tx_notify;
		mail_buf_len = sizeof(lte_tx_notify);
		break;

	case ID_VOICE_PROXY_WIFI_RX_CNF:
		comfirm.msg_id = ID_VOICE_PROXY_WIFI_RX_CNF;
		mail_buf = (int8_t *)&comfirm;
		mail_buf_len = sizeof(comfirm);
		break;

	case ID_VOICE_PROXY_WIFI_TX_NTF:
		ret = debug_get_wifi_list_node(&node);
		if (0 != ret) {
			ret = -EINVAL;
			goto OUT;
		}

		if (node) {
			memset(&wifi_tx_notify, 0,sizeof(wifi_tx_notify));
			wifi_rx_notify = (struct voice_proxy_wifi_rx_notify *)node->list_data.data;/*lint !e826*/
			wifi_tx_notify.msg_id = ID_VOICE_PROXY_WIFI_TX_NTF;
			wifi_tx_notify.channel_id = wifi_rx_notify->channel_id;
			wifi_tx_notify.port_type = wifi_rx_notify->port_type;
			wifi_tx_notify.data_len = wifi_rx_notify->data_len;
			memcpy(wifi_tx_notify.data, wifi_rx_notify->data, (size_t)wifi_rx_notify->data_len);
			mail_buf = (int8_t *)&wifi_tx_notify;
			mail_buf_len = sizeof(wifi_tx_notify);
			kfree(node);
			node = NULL;
		} else {
			ret = -EINVAL;
			goto OUT;
		}
		break;

	default:
		loge("command type is invalidate, msg_id:0x%x\n", msg_id);
		ret = -EINVAL;
		goto OUT;

	}

	/*cppcheck-suppress * */
	memcpy(buf, mail_buf, mail_buf_len);/*lint !e732 !e747*/
	*size = mail_buf_len;

OUT:

	return ret;/*lint !e438*/
}

static int32_t debug_thread_get_cmd_type(uint16_t *msg_id)
{
	struct voice_proxy_cmd_node *command = NULL;

	BUG_ON(NULL == msg_id);/*lint !e730*/

	if (!list_empty_careful(&debug_mailbox_cmd_queue)) {
		command = list_first_entry(&debug_mailbox_cmd_queue,
                                                   struct voice_proxy_cmd_node,
                                                   list_node);/*lint !e826*/

		*msg_id = command->msg_id;
		list_del_init(&command->list_node);

		kfree(command);
		command = NULL;
	} else {
		return -EINVAL;
	}

	return 0;/*lint !e438*/
}

static int32_t debug_mailbox_thread(void *arg)
{
	int32_t ret = 0;
	uint16_t msg_id = 0;

	UNUSED_PARAMETER(arg);

	while (!kthread_should_stop()) {
		/*wait for reading emaphore*/
		ret = wait_event_interruptible(s_priv.debug_mailbox_waitq,
                                               s_priv.debug_mailbox_wait_flag !=0);/*lint !e40 !e578 !e774 !e845 !e712*/

		if (unlikely(ret)) {/*lint !e730*/
			loge("debug_write_thread wait event failed\n");
			continue;
		}

		spin_lock_bh(&s_priv.debug_mailbox_lock);

		if (likely(s_priv.debug_mailbox_wait_flag> 0)) {/*lint !e730*/
			s_priv.debug_mailbox_wait_flag--;
		}

		do {
			msg_id = 0;
			ret = debug_thread_get_cmd_type(&msg_id);

			spin_unlock_bh(&s_priv.debug_mailbox_lock);

			loge("debug_mailbox_thread msg_id:0x%x\n", msg_id);
			if ((0 == ret) && (s_priv.debug_handle_mail)) {
				s_priv.debug_handle_mail(NULL,
                                                         (void *)&msg_id,
                                                         VOICE_PROXY_LIMIT_PARAM_SIZE);
			}

			spin_lock_bh(&s_priv.debug_mailbox_lock);
		} while (!list_empty_careful(&debug_mailbox_cmd_queue));
		spin_unlock_bh(&s_priv.debug_mailbox_lock);
	}

	return 0;
}

static void debug_snd_mailbox_msg(uint16_t msg_id)
{
	int32_t ret = 0;

	BUG_ON(ID_PROXY_VOICE_LTE_RX_NTF > msg_id);/*lint !e730*/
	BUG_ON(ID_PROXY_VOICE_DATA_MSGID_BUT < msg_id);/*lint !e730*/

	logi("debug_snd_mailbox_msg, msg_id:0x%x\n", msg_id);
	ret = debug_snd_cmd_list_node(msg_id);
	if (0 != ret) {
		loge("send command to debug mailbox thread failed\n");
	}
}

static int32_t debug_hifi_thread(void *arg)
{
	UNUSED_PARAMETER(arg);

	while (!kthread_should_stop()) {
		if (1 == s_priv.debug_snd_data_order) {
			debug_snd_mailbox_msg(ID_VOICE_PROXY_LTE_RX_NTF);
		} else if (2 == s_priv.debug_snd_data_order) {
			debug_snd_mailbox_msg(ID_VOICE_PROXY_LTE_TX_NTF);
		} else {
			debug_snd_mailbox_msg(ID_VOICE_PROXY_LTE_RX_NTF);
			debug_snd_mailbox_msg(ID_VOICE_PROXY_LTE_TX_NTF);
		}

		msleep((uint32_t)s_priv.debug_hifi_sleep_time);
	}

	return 0;
}

static int32_t debug_snd_wifi_list_node(int8_t *data, uint32_t size)
{
	int32_t  ret = 0;
	struct voice_proxy_data_node *data_node = NULL;

	BUG_ON(NULL == data);/*lint !e730*/

	ret = debug_create_list_data_node(&data_node, data, size);
	if (ret) {
		loge("data_node kzalloc failed\n");
		return ret;
	}

	spin_lock_bh(&s_priv.debug_wifi_lock);
	list_add_tail(&data_node->list_node, &debug_vowifi_data_queue);
	spin_unlock_bh(&s_priv.debug_wifi_lock);

	return 0;
}

static int32_t debug_mailbox_snd_msg_cb(uint32_t mailcode, uint16_t msg_id, void *buf, uint32_t size)
{
	int32_t ret = 0;

	logi("debug_mailbox_snd_msg_cb enter\n");

	BUG_ON(NULL == buf);/*lint !e730*/

	UNUSED_PARAMETER(mailcode);

	logi("msg_id :0x%x\n",msg_id);
	if ((ID_PROXY_VOICE_LTE_RX_NTF != msg_id) &&
	    (ID_PROXY_VOICE_LTE_TX_NTF != msg_id) &&
            (ID_PROXY_VOICE_WIFI_RX_NTF != msg_id)) {
		loge("debug_mailbox_snd_msg_cb, no need send cnf msg\n");
		return 0;
	}

	if (ID_PROXY_VOICE_LTE_RX_NTF == msg_id) {
		logi("get right decrypt data\n");
		debug_snd_mailbox_msg(ID_VOICE_PROXY_LTE_RX_CNF);
	} else if (ID_PROXY_VOICE_LTE_TX_NTF == msg_id) {
		logi("get right encrypt data\n");
		debug_snd_mailbox_msg(ID_VOICE_PROXY_LTE_TX_CNF);
	} else if (ID_PROXY_VOICE_WIFI_RX_NTF == msg_id) {
		logi("get right wifi rx data\n");
		debug_snd_mailbox_msg(ID_VOICE_PROXY_WIFI_RX_CNF);
		ret = debug_snd_wifi_list_node((int8_t *)buf, size);
		debug_snd_mailbox_msg(ID_VOICE_PROXY_WIFI_TX_NTF);
	}

	logi("debug_mailbox_snd_msg_cb leave\n");

	return ret;
}

static int32_t debug_tfagent_handle_msg(struct send_tfagent_data *volte_buf)
{
	int32_t ret = 0;
	struct send_tfagent_data buf;

	BUG_ON(NULL == volte_buf);/*lint !e730*/

	memset(&buf, 0, sizeof(struct send_tfagent_data));
	buf.buf_size = PROXY_VOICE_CODEC_MAX_DATA_LEN;
	buf.data_type = volte_buf->data_type;
	buf.id = volte_buf->id;
	memcpy(buf.data, volte_buf->data, (size_t)PROXY_VOICE_CODEC_MAX_DATA_LEN);
	loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
	debug_test_buf((int8_t*)&buf, (uint32_t)sizeof(struct send_tfagent_data));

	if (PROXY_TO_TF_UNDECRYPT_DATA == volte_buf->data_type) {
		logi("get right undecrypt data\n");
		buf.data_type = TF_TO_PROXY_DECRYPTED_DATA;
	} else {
		logi("get right unencrypt data\n");
		buf.data_type = TF_TO_PROXY_ENCRYPTED_DATA;
	}

	if ((s_priv.debug_tf_lost_enable) &&
	    (0 == (buf.id % (uint32_t)s_priv.debug_tf_lost_index))) {
		logi("lost one data id:%d\n", buf.id);
	} else {
		loge("proxy_push_data\n");
		ret = proxy_push_data((void *)&buf);
	}

	return ret;
}

static int32_t debug_tfagent_thread(void *arg)
{
	int32_t size = 0;
	struct send_tfagent_data buf;

	UNUSED_PARAMETER(arg);

	memset(&buf, 0, sizeof(buf));
	while (!kthread_should_stop()) {
		size = proxy_pull_data((int8_t *)&buf, (int32_t)sizeof(buf));
		loge("debug_tfagent_thread\n");
		loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
		debug_test_buf((int8_t*)&buf, (uint32_t)sizeof(buf));
		if (size == (int32_t)sizeof(buf))
			debug_tfagent_handle_msg(&buf);
	}

	return 0;
}

static void debug_reg_mailbox_msg_cb(mb_msg_cb mail_cb)
{
	s_priv.debug_handle_mail = (voice_proxy_debug_handle_mail_cb)mail_cb;
}

static int32_t debug_create_local_thread(void)
{
	int32_t ret = 0;

	logi("debug_create_local_thread enter\n");
	spin_lock_init(&s_priv.debug_mailbox_lock);
	s_priv.debug_mailbox_wait_flag = 0;
	init_waitqueue_head(&s_priv.debug_mailbox_waitq);

	/*create debug mailbox thread to read data from debug hifi thread */
	s_priv.debug_mailbox_thread = kthread_run(debug_mailbox_thread,
                                                  NULL,
                                                  "voice proxy debug mailbox");

	if (IS_ERR(s_priv.debug_mailbox_thread)) {
		loge("debug mailbox thread call kthread_run fail\n");
		ret = -EBUSY;
		goto OUT;
	}

	/*create debug thread to send data to debug mailbox thread*/
	s_priv.debug_hifi_thread = kthread_run(debug_hifi_thread,
                                               NULL,
                                               "voice proxy debug hifi");

	if (IS_ERR(s_priv.debug_hifi_thread)) {
		loge("debug hifi thread call kthread_run fail\n");
		ret = -EBUSY;
		goto ERR;
	}

	return ret;
ERR:
	if (!IS_ERR(s_priv.debug_mailbox_thread)) {
		ret = kthread_stop(s_priv.debug_mailbox_thread);
		spin_lock_bh(&s_priv.debug_mailbox_lock);
		s_priv.debug_mailbox_wait_flag++;
		spin_unlock_bh(&s_priv.debug_mailbox_lock);
		wake_up(&s_priv.debug_mailbox_waitq);
		s_priv.debug_mailbox_thread = NULL;
	}
OUT:

	logi("debug_create_local_thread leave\n");

	return ret;
}

static int32_t debug_create_tfagent_thread(void)
{
	int32_t ret = 0;

	logi("debug_create_tfagent_thread enter\n");
	spin_lock_init(&s_priv.debug_tfagent_lock);
	s_priv.debug_tfagent_wait_flag = 0;
	init_waitqueue_head(&s_priv.debug_tfagent_waitq);

	s_priv.debug_tfagent_thread = kthread_run(debug_tfagent_thread,
                                                  NULL,
                                                  "voice proxy debug mailbox");

	if (IS_ERR(s_priv.debug_tfagent_thread)) {
		loge("debug tfagent thread call kthread_run fail\n");
		ret = -EBUSY;
	}
	logi("debug_create_tfagent_thread leave\n");

	return ret;
}

static void debug_param_init(void)
{
	s_priv.debug_hifi_sleep_time = 20;
	s_priv.debug_tf_sleep_time = 5;
	s_priv.debug_snd_data_order = 3;
	s_priv.debug_tf_lost_index = 100;
	s_priv.debug_tf_lost_enable = 0;
}

void debug_start_hifi_to_tfagent(void)
{
	logi("debug_start_hifi_to_tfagent enter\n");
	debug_create_tfagent_thread();
	debug_param_init();
	/*register callback*/
	voice_proxy_mailbox_cb_init();
	voice_proxy_mailbox_cb_register(NULL, NULL, NULL);
	logi("debug_start_hifi_to_tfagent leave\n");
}

void debug_start_local_to_tfagent(void)
{
	logi("debug_start_local_to_tfagent enter\n");
	/*register callback*/
	voice_proxy_mailbox_cb_register(debug_mailbox_snd_msg_cb,
                                        debug_read_mailbox_msg,
                                        debug_reg_mailbox_msg_cb);
	debug_param_init();
	debug_create_tfagent_thread();
	debug_create_local_thread();
	logi("debug_start_local_to_tfagent leave\n");
}

static int32_t debug_start_mailbox(void)
{
	int32_t ret = 0;
	logi("debug_start_mailbox enter\n");

	voice_proxy_mailbox_cb_register(debug_mailbox_snd_msg_cb,
                                        debug_read_mailbox_msg,
                                        debug_reg_mailbox_msg_cb);
	spin_lock_init(&s_priv.debug_wifi_lock);
	spin_lock_init(&s_priv.debug_mailbox_lock);
	s_priv.debug_mailbox_wait_flag = 0;
	init_waitqueue_head(&s_priv.debug_mailbox_waitq);

	/*create debug mailbox thread to read data from debug hifi thread */
	s_priv.debug_mailbox_thread = kthread_run(debug_mailbox_thread,
                                                  NULL,
                                                  "voice proxy debug mailbox");

	if (IS_ERR(s_priv.debug_mailbox_thread)) {
		loge("debug mailbox thread call kthread_run fail\n");
		ret = -EBUSY;
	}
	logi("debug_start_mailbox leave\n");
	return ret;
}

static int32_t debug_stop_hifi_to_tfagent(void)
{
	int32_t ret = 0;

	logi("debug_stop_hifi_to_tfagent enter\n");

	if (!IS_ERR(s_priv.debug_tfagent_thread)) {
		ret = kthread_stop(s_priv.debug_tfagent_thread);
		spin_lock_bh(&s_priv.debug_tfagent_lock);
		s_priv.debug_tfagent_wait_flag++;
		spin_unlock_bh(&s_priv.debug_tfagent_lock);
		wake_up(&s_priv.debug_tfagent_waitq);
		s_priv.debug_tfagent_thread = NULL;
	} else {
		loge("debug_tfagent_thread is err\n");
	}

	voice_proxy_mailbox_cb_init();

	logi("debug_stop_hifi_to_tfagent leave\n");

	return ret;
}

static int32_t debug_stop_local_to_tfagent(void)
{
	int32_t ret = 0;

	logi("debug_stop_local_to_tfagent enter\n")
	if (!IS_ERR(s_priv.debug_hifi_thread)) {
		ret = kthread_stop(s_priv.debug_hifi_thread);
		s_priv.debug_hifi_thread = NULL;
	} else {
		loge("s_priv.debug_hifi_thread is err\n");
	}

	if (!IS_ERR(s_priv.debug_mailbox_thread)) {
		ret = kthread_stop(s_priv.debug_mailbox_thread);
		spin_lock_bh(&s_priv.debug_mailbox_lock);
		s_priv.debug_mailbox_wait_flag++;
		spin_unlock_bh(&s_priv.debug_mailbox_lock);
		wake_up(&s_priv.debug_mailbox_waitq);
		s_priv.debug_mailbox_thread = NULL;
	} else {
		loge("s_priv.debug_mailbox_thread is err\n");
	}

	if (!IS_ERR(s_priv.debug_tfagent_thread)) {
		ret = kthread_stop(s_priv.debug_tfagent_thread);
		spin_lock_bh(&s_priv.debug_tfagent_lock);
		s_priv.debug_tfagent_wait_flag++;
		spin_unlock_bh(&s_priv.debug_tfagent_lock);
		wake_up(&s_priv.debug_tfagent_waitq);
		s_priv.debug_tfagent_thread = NULL;
	} else {
		loge("s_priv.debug_tfagent_thread is err\n");
	}

	voice_proxy_mailbox_cb_init();
	logi("debug_stop_local_to_tfagent leave\n");

	return ret;
}

static ssize_t debug_ssw(struct class *class, struct class_attribute *attr, const char *buf, size_t size)
{
	ssize_t ret = 0;
	ret = sscanf(buf, "0x%x", &ssw);
	if (!ret) {
		return -EINVAL;
	}

	UNUSED_PARAMETER(class);
	UNUSED_PARAMETER(attr);

	printk(KERN_ERR"[%s:%d] ctlwr:0x%x ! \n", __FUNCTION__, __LINE__, ssw);

	switch (ssw) {
	case 0x1:
		debug_start_hifi_to_tfagent();
		break;
	case 0x2:
		debug_stop_hifi_to_tfagent();
		break;
	case 0x3:
		debug_start_local_to_tfagent();
		break;
	case 0x4:
		debug_stop_local_to_tfagent();
		break;
	case 0x5:
		debug_start_mailbox();
		break;
	default:
		break;
	}
	printk(KERN_ERR"[%s:%d] ssw:0x%x , -----\n", __FUNCTION__, __LINE__, ssw);

	return (long)size;
}

static ssize_t debug_paraw(struct class *class, struct class_attribute *attr, const char *buf, size_t size)
{
	ssize_t ret = 0;
	ret = sscanf(buf, "0x%x", &paraw);
	if (!ret) {
		return -EINVAL;
	}

	UNUSED_PARAMETER(class);
	UNUSED_PARAMETER(attr);

	printk(KERN_ERR"[%s:%d] ctlwr:0x%x ! \n", __FUNCTION__, __LINE__, paraw);

	switch (paraw) {
	case 0x1:
		s_priv.debug_hifi_sleep_time = 20;
		break;
	case 0x2:
		s_priv.debug_hifi_sleep_time = 10;
		break;
	case 0x3:
		s_priv.debug_hifi_sleep_time = 5;
		break;
	case 0x4:
		s_priv.debug_tf_sleep_time = 20;
		break;
	case 0x5:
		s_priv.debug_snd_data_order= 1;
		break;
	case 0x6:
		s_priv.debug_snd_data_order= 2;
		break;
	case 0x7:
		s_priv.debug_snd_data_order= 3;
		break;
	case 0x8:
		s_priv.debug_tf_lost_index = 100;
		s_priv.debug_tf_lost_enable = 1;
		break;
	case 0x9:
		s_priv.debug_tf_lost_enable = 0;
		break;
	default:
		break;
	}

	return (long)size;
}

static const struct class_attribute debug_attrs[] = {
	__ATTR(ssw, 0664, NULL, debug_ssw),/*lint !e846 !e514 !e778 !e866 !e84 */
	__ATTR(paraw, 0664, NULL, debug_paraw),/*lint !e846 !e514 !e778 !e866 !e84 */
};

static int32_t debug_create_attrs(struct class *class)
{
	int i = 0;
	int ret = 0;

	for (i=0; i < (sizeof(debug_attrs)/sizeof(struct class_attribute)); i++) {/*lint !e574 !e737*/
		ret = class_create_file(class, &debug_attrs[i]);
		if (ret < 0) {
			break;
		}
	}

	return ret;
}

static void debug_remove_attrs(struct class *class)
{
	int i = 0;
	for (i=0; i < (sizeof(debug_attrs)/sizeof(struct class_attribute)); i++) {/*lint !e574 !e737*/
		class_remove_file(class, &debug_attrs[i]);
	}
}

static int __init voice_proxy_debug_init(void)
{
	int ret = 0;
	printk(KERN_ERR"[%s:%d], =====================!\n",
		   __FUNCTION__, __LINE__);

	sclass = class_create(THIS_MODULE, CLASS_NAME);/*lint !e64*/
	if (IS_ERR(sclass)) {
		printk(KERN_ERR"[%s:%d], class create error!\n",
			   __FUNCTION__, __LINE__);
		return -EFAULT;
	}

	ret = debug_create_attrs(sclass);
	if(ret < 0) {
		class_destroy(sclass);
		printk(KERN_ERR"[%s:%d], debug_create_attrs error!\n",
			   __FUNCTION__, __LINE__);
		return -EFAULT;
	}

	return 0;
}

static void __exit voice_proxy_debug_exit(void)
{
	printk(KERN_ERR"[%s:%d], =====================!\n", __FUNCTION__, __LINE__);
	debug_remove_attrs(sclass);
	class_destroy(sclass);
}

module_init(voice_proxy_debug_init);
module_exit(voice_proxy_debug_exit);

MODULE_DESCRIPTION("voice_proxy_debug driver");
MODULE_AUTHOR("Huawei Technologies Co., Ltd.");
MODULE_LICENSE("GPL");
