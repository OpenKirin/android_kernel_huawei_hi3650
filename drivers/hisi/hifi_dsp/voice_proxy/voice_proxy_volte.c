/*
 * Hifi_voice_proxy.c - HW voice proxy in kernel, it is used for pass through voice
 * data between AP and hifi.
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

#include <linux/miscdevice.h>
#include "voice_proxy.h"

/*lint -e528 -e753 */
#define VOICE_PROXY_VOLTE_DATA_COUNT_MAX 100000000
#define DTS_COMP_VOICE_PROXY_VOLTE_NAME "hisilicon,voice_proxy_volte"

enum {
	SEC_KEY_NEGO_ENABLE,
	SEC_KEY_NEGO_SUCC_DISABLE,
	SEC_KEY_NEGO_FAIL_DISABLE,
};

/*
 * this queue is used for saving the struct of voice_proxy_lte_rx_notify when the
 * voice data is sent to tfagent. when the tfagent return the decrypted voice data,
 * proxy will get the struct of voice_proxy_lte_rx_notify and push the decrypted
 * voice data to it, finally send the this struct to hifi.
 */
LIST_HEAD(decrypting_queue);
LIST_HEAD(decrypted_queue);

/*
 * this queue is used for saving the struct of voice_proxy_lte_tx_notify when the
 * voice data is sent to tfagent. when the tfagent return the encrypted voice data,
 * proxy will get the struct of voice_proxy_lte_tx_notify and push the encrypted
 * voice data to it, finally send the this struct to hifi.
 */
LIST_HEAD(encrypting_queue);
LIST_HEAD(encrypted_queue);

/* this queue is used for saving the data which is sent to tfagent*/
LIST_HEAD(pull_queue);

struct volte_priv {
	/* it is used for handling the queue of decrypting_queue/encrypting_queue*/
	spinlock_t push_lock;

	/* they are used for sending data to tfagent*/
	spinlock_t pull_lock;
	wait_queue_head_t pull_waitq;
	int32_t pull_wait_flag;

	/* this is used for counting the size of decrypting_queue*/
	int32_t decrypting_cnt;

	/* this is used for counting the size of decrypted_queue*/
	int32_t decrypted_cnt;

	/* this is used for counting the size of encrypting_queue*/
	int32_t encrypting_cnt;

	/* this is used for counting the size of encrypted_queue*/
	int32_t encrypted_cnt;

	/* decrypted voice data confirm*/
	bool plaintext_cnf;

	/* first decrypted voice data from tfagent*/
	bool first_plaintext;

	/* decrypted voice data time stamp*/
	int64_t plaintext_stamp;

	/* encrypted voice data confirm*/
	bool ciphertext_cnf;

	/* first encrypted voice data from tfagent*/
	bool first_ciphertext;

	/* encrypted voice data time stamp*/
	int64_t ciphertext_stamp;

	/* this handle is get from voice proxy when register sign init callback*/
	int32_t sign_handle;
};

static struct volte_priv priv;

extern int32_t voice_proxy_mailbox_send_msg_cb(uint32_t mailcode, uint16_t msg_id, void *buf, uint32_t size);

static void volte_sign_init(void)
{
	priv.plaintext_cnf = false;
	priv.first_plaintext = true;
	priv.ciphertext_cnf = false;
	priv.first_ciphertext = true;
}

void debug_test_buf(int8_t *buf, uint32_t buf_size)
{
	int i;
	printk(KERN_ERR "debug_data_print:\n");
	for (i = 0; i < buf_size; i++) {/*lint !e574 !e737*/
		if ( 0 == i%16) {
			printk(KERN_ERR "\n%08X : ", i);
		}
		printk(KERN_ERR " %02X ", buf[i]);
	}

	return;
}

static int32_t volte_add_decrypted_data(int8_t *data, uint32_t size)
{
	struct voice_proxy_data_node *node;

	UNUSED_PARAMETER(size);

	BUG_ON(NULL == data);/*lint !e730*/

	if (priv.decrypted_cnt > VOICE_PROXY_QUEUE_SIZE_MAX) {
		loge("out of queue, decrypted_cnt(%d) > QUEUE_SIZE_MAX(%d)\n",
			priv.decrypted_cnt, VOICE_PROXY_QUEUE_SIZE_MAX);
		return -ENOMEM;
	}

	node = (struct voice_proxy_data_node *)data;/*lint !e826*/

	list_add_tail(&node->list_node, &decrypted_queue);
	priv.decrypted_cnt++;

	return 0;
}

static int32_t volte_add_encrypted_data(int8_t *data, uint32_t size)
{
	struct voice_proxy_data_node *node;

	UNUSED_PARAMETER(size);

	BUG_ON(NULL == data);/*lint !e730*/

	if (priv.encrypted_cnt > VOICE_PROXY_QUEUE_SIZE_MAX) {
		loge("out of queue, encrypted_cnt(%d) > QUEUE_SIZE_MAX(%d)\n",
			 priv.encrypted_cnt, VOICE_PROXY_QUEUE_SIZE_MAX);
		return -ENOMEM;
	}

	node = (struct voice_proxy_data_node *)data;/*lint !e826*/

	list_add_tail(&node->list_node, &encrypted_queue);
	priv.encrypted_cnt++;

	return 0;
}

static int32_t volte_send_data(struct voice_proxy_data_node *node, struct send_tfagent_data *buf)
{
	int32_t ret = 0;
	struct voice_proxy_lte_rx_notify *rx;
	struct voice_proxy_lte_tx_notify *tx;

	BUG_ON(NULL == node);/*lint !e730*/
	BUG_ON(NULL == buf);/*lint !e730*/

	/*fill handled voice buf to the packege of mailbox*/
	if (TF_TO_PROXY_DECRYPTED_DATA == buf->data_type) {/*lint !e826*/
		rx = (struct voice_proxy_lte_rx_notify *)node->list_data.data;/*lint !e826*/
		memset(rx->data, 0, sizeof(rx->data));
		memcpy((int8_t *)rx->data, buf->data, (size_t)PROXY_VOICE_CODEC_MAX_DATA_LEN);
		rx->msg_id = ID_PROXY_VOICE_LTE_RX_NTF;
		node->list_data.size = sizeof(*rx);

		loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
		debug_test_buf((int8_t *)rx->data, PROXY_VOICE_CODEC_MAX_DATA_LEN);
		ret = voice_proxy_add_data(volte_add_decrypted_data,
		                           (int8_t *)node,
		                           (uint32_t)sizeof(*node),
		                           ID_PROXY_VOICE_LTE_RX_NTF);
	} else {
		tx = (struct voice_proxy_lte_tx_notify *)node->list_data.data;/*lint !e826*/
		memset(tx->data, 0, sizeof(tx->data));
		memcpy((int8_t *)tx->data, buf->data, (size_t)PROXY_VOICE_CODEC_MAX_DATA_LEN);
		tx->msg_id = ID_PROXY_VOICE_LTE_TX_NTF;
		node->list_data.size = sizeof(*tx);

		loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
		debug_test_buf((int8_t *)tx->data, PROXY_VOICE_CODEC_MAX_DATA_LEN);
		ret = voice_proxy_add_data(volte_add_encrypted_data,
		                           (int8_t *)node,
		                           (uint32_t)sizeof(*node),
		                           ID_PROXY_VOICE_LTE_TX_NTF);
	}

	if (ret) {
		loge("send node fail, ret:%d\n", ret);
		kfree(node);
		node = NULL;
	}

	return ret;/*lint !e438*/
}

/*
 * this function is called by tfagent kernel to return the voice data which have encrypted/decrypted.
 */
int32_t proxy_push_data(void *data)
{
	struct send_tfagent_data *buf;
	struct voice_proxy_data_node *node = NULL;

	if (NULL == data) {
		loge("data is NULL\n");
		return -EINVAL;
	}

	buf = (struct send_tfagent_data *)data;
	while (1) {
		spin_lock_bh(&priv.push_lock);
		node = NULL;
		if (TF_TO_PROXY_DECRYPTED_DATA == buf->data_type) {
			if (!list_empty_careful(&decrypting_queue)) {
				node = list_first_entry(&decrypting_queue,
                                                                struct voice_proxy_data_node,
                                                                list_node);/*lint !e826*/

				list_del_init(&node->list_node);
				priv.decrypting_cnt--;
			}
		} else if (TF_TO_PROXY_ENCRYPTED_DATA == buf->data_type) {
			if (!list_empty_careful(&encrypting_queue)) {
				node = list_first_entry(&encrypting_queue,
                                                                struct voice_proxy_data_node,
                                                                list_node);/*lint !e826*/

				list_del_init(&node->list_node);
				priv.encrypting_cnt--;
			}
		} else {
			loge("data type is error, data_type:%d\n", buf->data_type);
			spin_unlock_bh(&priv.push_lock);
			return -EINVAL;
		}
		spin_unlock_bh(&priv.push_lock);

		if (node) {
			logi("list data id:%d voice id:%d\n", node->list_data.id, buf->id);
			if (node->list_data.id < buf->id) {
				loge("ignore this node\n");
				kfree(node);
				node = NULL;
			} else if (node->list_data.id == buf->id) {
				logi("send this node\n");
				loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
				debug_test_buf((int8_t*)buf, (uint32_t)sizeof(struct send_tfagent_data));
				volte_send_data(node, buf);
				break;
			} else {
				loge("no avail node\n");
				kfree(node);
				node = NULL;
				return -EINVAL;
			}
		}  else {
			loge("node is null\n");
			break;
		}
	}

	return 0;
}
EXPORT_SYMBOL(proxy_push_data);

/* this function is called by tfagent kernel to get voice data for encrypt/decrypt*/
int32_t proxy_pull_data(int8_t *data, int32_t size)
{
	int32_t ret = 0;
	struct send_tfagent_data buf;
	struct voice_proxy_data_node *node = NULL;

	if (NULL == data) {
		loge("data is null\n");
		return -EINVAL;
	}

	if (size < sizeof(buf)) {/*lint !e574 !e737*/
		loge("param error,size(%d)<buf size(%ld)\n", size, sizeof(buf));
		return -EINVAL;
	}

	memset(&buf, 0, sizeof(buf));

	spin_lock_bh(&priv.pull_lock);
	if (list_empty_careful(&pull_queue)) {
		spin_unlock_bh(&priv.pull_lock);
		ret = wait_event_interruptible(priv.pull_waitq, priv.pull_wait_flag > 0);/*lint !e40 !e578 !e774 !e845 !e712*/
		if (ret) {
			if (ret != -ERESTARTSYS) {
				loge("wait event interruptible fail, 0x%x.\n", ret);
			}

			return -EBUSY;
		}
		spin_lock_bh(&priv.pull_lock);
	}

	priv.pull_wait_flag = 0;

	if (!list_empty_careful(&pull_queue)) {
		node = list_first_entry(&pull_queue, struct voice_proxy_data_node, list_node);/*lint !e826*/

		list_del_init(&node->list_node);

		spin_unlock_bh(&priv.pull_lock);

		if (node->list_data.size <= size) {
			memcpy(data, node->list_data.data, node->list_data.size);/*lint !e732 !e747*/
			ret = node->list_data.size;
			loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
			debug_test_buf(data, (uint32_t)ret);
		} else {
			loge("data size err, data size(%d)>size(%d)\n", node->list_data.size, size);
			ret = -EFAULT;
		}

		kfree(node);
		node = NULL;
	} else {
		spin_unlock_bh(&priv.pull_lock);
		ret = -EAGAIN;
	}

	return ret;/*lint !e438*/
}
EXPORT_SYMBOL(proxy_pull_data);

void proxy_wake_up_pull(void)
{
	spin_lock_bh(&priv.pull_lock);
	priv.pull_wait_flag++;
	spin_unlock_bh(&priv.pull_lock);
	wake_up(&priv.pull_waitq);
}
EXPORT_SYMBOL(proxy_wake_up_pull);

int32_t proxy_enable_sec_key_negotiation(int32_t enable)
{
	int32_t ret;
	struct voice_proxy_voice_encrypt_key_end msg;

	if (SEC_KEY_NEGO_ENABLE != enable &&
            SEC_KEY_NEGO_SUCC_DISABLE != enable &&
            SEC_KEY_NEGO_FAIL_DISABLE != enable) {
		loge("param error, enable:%d\n", enable);
		return -EINVAL;
	}

	if (SEC_KEY_NEGO_ENABLE == enable) {
		msg.msg_id = ID_PROXY_VOICE_ENCRYPT_KEY_BEGIN;
	} else if (SEC_KEY_NEGO_SUCC_DISABLE == enable) {
		msg.msg_id = ID_PROXY_VOICE_ENCRYPT_KEY_END;
		msg.encrypt_negotiation_result = true;
	} else {
		msg.msg_id = ID_PROXY_VOICE_ENCRYPT_KEY_END;
		msg.encrypt_negotiation_result = false;
	}

	ret = voice_proxy_mailbox_send_msg_cb(MAILBOX_MAILCODE_ACPU_TO_HIFI_VOICE_RT,
                                              msg.msg_id,
                                              &msg,
                                              (uint32_t)sizeof(msg));
	if (ret)
                loge("mailbox_send_msg fail:%d\n", ret);

	return ret;
}
EXPORT_SYMBOL(proxy_enable_sec_key_negotiation);

static int32_t volte_add_pull_data(int8_t *rev_buf, uint32_t buf_size, int32_t type)
{
	int32_t ret = 0;
	static uint32_t rx_cnt = 0;
	static uint32_t tx_cnt = 0;
	struct send_tfagent_data buf;
	struct voice_proxy_data_node *node = NULL;
	struct voice_proxy_data_node *tf_node = NULL;
	struct voice_proxy_lte_rx_notify *rx = NULL;
	struct voice_proxy_lte_tx_notify *tx = NULL;

	BUG_ON(NULL == rev_buf);/*lint !e730*/

	logi("type:%d\n", type);

	if (PROXY_TO_TF_UNDECRYPT_DATA == type) {
		if (priv.decrypting_cnt > VOICE_PROXY_QUEUE_SIZE_MAX) {
			loge("out of queue, decrypting_cnt(%d)>(%d)\n",
			        priv.decrypting_cnt, VOICE_PROXY_QUEUE_SIZE_MAX);
                        goto OUT;
		}
	} else {
		if (priv.encrypting_cnt > VOICE_PROXY_QUEUE_SIZE_MAX) {
			loge("out of queue, encrypting_cnt(%d)>(%d)\n",
                                priv.encrypting_cnt, VOICE_PROXY_QUEUE_SIZE_MAX);
			goto OUT;
		}
	}

	ret = voice_proxy_create_data_node(&node, rev_buf, (int32_t)buf_size);
	if (ret) {
		loge("kmalloc node failed %d\n", ret);
		return ret;
	}

	buf.buf_size = PROXY_VOICE_CODEC_MAX_DATA_LEN;
	buf.data_type = type;
	memset(buf.data, 0, sizeof(buf.data));

	/*
	 * 1.get the voice data from the structure of
	 * voice_proxy_lte_rx_notify/voice_proxy_lte_tx_notify
	 */
	if (PROXY_TO_TF_UNDECRYPT_DATA == type) {
		rx = (struct voice_proxy_lte_rx_notify *)rev_buf;/*lint !e826*/
		memcpy(buf.data, (int8_t *)rx->data, buf.buf_size);/*lint !e732 !e747*/
		node->list_data.id = rx_cnt;
		buf.id = node->list_data.id;
		rx_cnt++;
	} else {
		tx = (struct voice_proxy_lte_tx_notify *)rev_buf;/*lint !e826*/
		memcpy(buf.data, (int8_t *)tx->data, buf.buf_size);/*lint !e732 !e747*/
		node->list_data.id = tx_cnt;
		buf.id = node->list_data.id;
		tx_cnt++;
	}

	ret = voice_proxy_create_data_node(&tf_node, (int8_t *)&buf, (int32_t)sizeof(buf));
	if (ret) {
		loge("kmalloc push_node failed %d\n", ret);
		kfree(node);
		node = NULL;
		return ret;/*lint !e438*/
	}

	/*
	 * 2.save the structure for decrypted/encrypted voice
	 * data and then send the structure to hifi
	 */
	spin_lock_bh(&priv.push_lock);
	if (PROXY_TO_TF_UNDECRYPT_DATA == type) {
		list_add_tail(&node->list_node, &decrypting_queue);
		priv.decrypting_cnt++;
	} else {
		list_add_tail(&node->list_node, &encrypting_queue);
		priv.encrypting_cnt++;
	}
	spin_unlock_bh(&priv.push_lock);

	/* 3.send voice data to tfagent for decrypting/encrypting*/
	spin_lock_bh(&priv.pull_lock);
	list_add_tail(&tf_node->list_node, &pull_queue);
	priv.pull_wait_flag++;
	spin_unlock_bh(&priv.pull_lock);
	wake_up(&priv.pull_waitq);

	if (VOICE_PROXY_VOLTE_DATA_COUNT_MAX <= rx_cnt) {
		rx_cnt = 0;
	}

	if (VOICE_PROXY_VOLTE_DATA_COUNT_MAX <= tx_cnt) {
		tx_cnt = 0;
	}

	return ret;

OUT:
        spin_lock_bh(&priv.pull_lock);
        priv.pull_wait_flag++;
        spin_unlock_bh(&priv.pull_lock);
        wake_up(&priv.pull_waitq);

        return -ENOMEM;
}

static void volte_receive_undecrypt_ntf(int8_t *rev_buf, uint32_t buf_size)
{
	int32_t ret;
	static int32_t cnt = 0;

	BUG_ON(NULL == rev_buf);/*lint !e730*/

	loge("volte_receive_undecrypt_ntf\n");
	loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
	debug_test_buf(rev_buf, buf_size);

	ret = volte_add_pull_data(rev_buf, buf_size, PROXY_TO_TF_UNDECRYPT_DATA);
	if (ret) {
		loge("volte_add_pull_data failed\n");
		return;
	}

	voice_proxy_add_work_queue_cmd(ID_PROXY_VOICE_LTE_RX_CNF);

	cnt++;
	logi("receive ciphertext msg: cnt:%d\n", cnt);
}

static void volte_receive_unencrypt_ntf(int8_t *rev_buf, uint32_t buf_size)
{
	int32_t ret;
	static int32_t cnt = 0;

	BUG_ON(NULL == rev_buf);/*lint !e730*/

	loge("volte_receive_unencrypt_ntf\n");
	loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
	debug_test_buf(rev_buf, buf_size);

	ret = volte_add_pull_data(rev_buf, buf_size, PROXY_TO_TF_UNENCRYPT_DATA);
	if (ret) {
		loge("volte_add_pull_data failed\n");
		return;
	}

	voice_proxy_add_work_queue_cmd(ID_PROXY_VOICE_LTE_TX_CNF);

	cnt++;
	logi("receive plaintext msg: cnt:%d\n", cnt);
}

static void volte_receive_decrypted_cnf(int8_t *rev_buf, uint32_t buf_size)
{
	int32_t ret;
	static int32_t cnt = 0;

	UNUSED_PARAMETER(rev_buf);
	UNUSED_PARAMETER(buf_size);

	loge("volte_receive_decrypted_cnf\n");

	ret = voice_proxy_add_cmd(ID_VOICE_PROXY_LTE_RX_CNF);
	if (ret) {
		loge("send plaintext data cnf failed\n");
	}

	cnt++;
	logi("receive plaintext cnf msg: cnt:%d\n", cnt);
}

static void volte_receive_encrypted_cnf(int8_t *rev_buf, uint32_t buf_size)
{
	int32_t ret;
	static int32_t cnt = 0;

	UNUSED_PARAMETER(rev_buf);
	UNUSED_PARAMETER(buf_size);

	loge("volte_receive_encrypted_cnf\n");

	ret = voice_proxy_add_cmd(ID_VOICE_PROXY_LTE_TX_CNF);
	if (ret) {
		loge("send ciphertext data cnf failed\n");
	}

	cnt++;
	logi("receive ciphertext cnf msg: cnt:%d\n", cnt);
}

static void volte_get_decryped_data(int8_t *data, uint32_t *size)
{
	struct voice_proxy_data_node *node = NULL;

	loge("volte_get_decryped_data\n");

	BUG_ON(NULL == data);/*lint !e730*/
	BUG_ON(NULL == size);/*lint !e730*/

	if (!list_empty_careful(&decrypted_queue)) {
		node = list_first_entry(&decrypted_queue,
						struct voice_proxy_data_node,
						list_node);/*lint !e826*/

		BUG_ON(*size < (uint32_t)node->list_data.size);/*lint !e730*/

		*size = (uint32_t)node->list_data.size;
		memcpy(data, node->list_data.data, (size_t)*size);

		list_del_init(&node->list_node);
		kfree(node);
		node = NULL;

		priv.decrypted_cnt--;
		priv.first_plaintext = false;
		priv.plaintext_cnf = false;
	} else {
		*size = 0;
	}
}/*lint !e438*/

static void volte_get_encrypted_data(int8_t *data, uint32_t *size)
{
	struct voice_proxy_data_node *node = NULL;

	BUG_ON(NULL == data);/*lint !e730*/
	BUG_ON(NULL == size);/*lint !e730*/
	loge("volte_get_encrypted_data\n");
	if (!list_empty_careful(&encrypted_queue)) {
		node = list_first_entry(&encrypted_queue,
						struct voice_proxy_data_node,
						list_node);/*lint !e826*/

		BUG_ON(*size < (uint32_t)node->list_data.size);/*lint !e730*/

		*size = (uint32_t)node->list_data.size;
		memcpy(data, node->list_data.data, (size_t)*size);

		list_del_init(&node->list_node);
		kfree(node);
		node = NULL;

		priv.encrypted_cnt--;
		priv.first_ciphertext = false;
		priv.ciphertext_cnf = false;
	} else {
		*size = 0;
	}
}/*lint !e438*/


static void volte_handle_decrypted_ntf(int8_t *data, uint32_t *size, uint16_t *msg_id)
{
	logi("msg id ID_PROXY_VOICE_LTE_RX_NTF\n");
	loge("volte_handle_decrypted_ntf\n");

	BUG_ON(NULL == data);/*lint !e730*/
	BUG_ON(NULL == size);/*lint !e730*/
	BUG_ON(NULL == msg_id);/*lint !e730*/

	voice_proxy_set_send_sign(priv.first_plaintext, &priv.plaintext_cnf, &priv.plaintext_stamp);

	if (priv.first_plaintext || priv.plaintext_cnf) {
		volte_get_decryped_data(data, size);
	} else {
		*size = 0;
	}
	*msg_id = ID_PROXY_VOICE_LTE_RX_NTF;

	loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
	debug_test_buf(data, *size);
}

static void volte_handle_decrypted_cnf(int8_t *data, uint32_t *size, uint16_t *msg_id)
{
	logi("msg id ID_VOICE_PROXY_LTE_RX_CNF\n");
	loge("volte_handle_decrypted_cnf\n");

	BUG_ON(NULL == data);/*lint !e730*/
	BUG_ON(NULL == size);/*lint !e730*/
	BUG_ON(NULL == msg_id);/*lint !e730*/

	priv.plaintext_cnf = true;
	priv.plaintext_stamp = voice_proxy_get_time_ms();

	volte_get_decryped_data(data, size);
	*msg_id = ID_PROXY_VOICE_LTE_RX_NTF;

	loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
	debug_test_buf(data, *size);
}

static void volte_handle_encrypted_ntf(int8_t *data, uint32_t *size, uint16_t *msg_id)
{
	logi("msg id ID_PROXY_VOICE_LTE_TX_NTF\n");
	loge("volte_handle_encrypted_ntf\n");

	BUG_ON(NULL == data);/*lint !e730*/
	BUG_ON(NULL == size);/*lint !e730*/
	BUG_ON(NULL == msg_id);/*lint !e730*/

	voice_proxy_set_send_sign(priv.first_ciphertext, &priv.ciphertext_cnf, &priv.ciphertext_stamp);

	if (priv.first_ciphertext || priv.ciphertext_cnf) {
		volte_get_encrypted_data(data, size);
	} else {
		*size = 0;
	}
	*msg_id = ID_PROXY_VOICE_LTE_TX_NTF;

	loge("debug_test_buf %d, %s, %s", __LINE__, __FUNCTION__, __FILE__);
	debug_test_buf(data, *size);
}

static void volte_handle_encrypted_cnf(int8_t *data, uint32_t *size, uint16_t *msg_id)
{
	logi("msg id ID_VOICE_PROXY_LTE_TX_CNF\n");
	loge("volte_handle_encrypted_cnf\n");

	BUG_ON(NULL == data);/*lint !e730*/
	BUG_ON(NULL == size);/*lint !e730*/
	BUG_ON(NULL == msg_id);/*lint !e730*/

	priv.ciphertext_cnf = true;
	priv.ciphertext_stamp = voice_proxy_get_time_ms();

	volte_get_encrypted_data(data, size);
	*msg_id = ID_PROXY_VOICE_LTE_TX_NTF;
}

static int volte_probe(struct platform_device *pdev)
{
	int32_t ret;
	memset(&priv, 0, sizeof(priv));

	logi("voice proxy volte prob,pdev name[%s]\n", pdev->name);

	priv.pull_wait_flag = 0;

	spin_lock_init(&priv.push_lock);
	spin_lock_init(&priv.pull_lock);
	init_waitqueue_head(&priv.pull_waitq);

	volte_sign_init();

	ret = voice_proxy_register_msg_callback(ID_VOICE_PROXY_LTE_RX_NTF, volte_receive_undecrypt_ntf);
	BUG_ON(0 != ret);/*lint !e730*/
	ret = voice_proxy_register_msg_callback(ID_VOICE_PROXY_LTE_TX_NTF, volte_receive_unencrypt_ntf);
	BUG_ON(0 != ret);/*lint !e730*/
	ret = voice_proxy_register_msg_callback(ID_VOICE_PROXY_LTE_RX_CNF, volte_receive_decrypted_cnf);
	BUG_ON(0 != ret);/*lint !e730*/
	ret = voice_proxy_register_msg_callback(ID_VOICE_PROXY_LTE_TX_CNF, volte_receive_encrypted_cnf);
	BUG_ON(0 != ret);/*lint !e730*/
	ret = voice_proxy_register_cmd_callback(ID_PROXY_VOICE_LTE_RX_NTF, volte_handle_decrypted_ntf);
	BUG_ON(0 != ret);/*lint !e730*/
	ret = voice_proxy_register_cmd_callback(ID_PROXY_VOICE_LTE_TX_NTF, volte_handle_encrypted_ntf);
	BUG_ON(0 != ret);/*lint !e730*/
	ret = voice_proxy_register_cmd_callback(ID_VOICE_PROXY_LTE_RX_CNF, volte_handle_decrypted_cnf);
	BUG_ON(0 != ret);/*lint !e730*/
	ret = voice_proxy_register_cmd_callback(ID_VOICE_PROXY_LTE_TX_CNF, volte_handle_encrypted_cnf);
	BUG_ON(0 != ret);/*lint !e730*/

	voice_proxy_register_sign_init_callback(volte_sign_init, &priv.sign_handle);

	return ret;
}

static int volte_remove(struct platform_device *pdev)
{

	UNUSED_PARAMETER(pdev);

	voice_proxy_deregister_msg_callback(ID_VOICE_PROXY_LTE_RX_NTF);
	voice_proxy_deregister_msg_callback(ID_VOICE_PROXY_LTE_TX_NTF);
	voice_proxy_deregister_msg_callback(ID_VOICE_PROXY_LTE_RX_CNF);
	voice_proxy_deregister_msg_callback(ID_VOICE_PROXY_LTE_TX_CNF);

	voice_proxy_deregister_cmd_callback(ID_PROXY_VOICE_LTE_RX_NTF);
	voice_proxy_deregister_cmd_callback(ID_PROXY_VOICE_LTE_TX_NTF);
	voice_proxy_deregister_cmd_callback(ID_VOICE_PROXY_LTE_RX_CNF);
	voice_proxy_deregister_cmd_callback(ID_VOICE_PROXY_LTE_TX_CNF);

	voice_proxy_deregister_sign_init_callback(priv.sign_handle);

	return 0;
}

static const struct of_device_id volte_match_table[] = {
	{
		.compatible = DTS_COMP_VOICE_PROXY_VOLTE_NAME,
		.data = NULL,
	},
	{}/*lint !e785*/
};

static struct platform_driver volte_driver = {
	.driver = {
		.name  = "voice proxy volte",
		.owner = THIS_MODULE,/*lint !e64*/
		.of_match_table = of_match_ptr(volte_match_table),
	},/*lint !e785*/
	.probe = volte_probe,
	.remove = volte_remove,
};/*lint !e785*/

static int __init volte_init( void )
{
	int32_t ret;

	printk("Audio:voice proxy volte init\n");

	ret = platform_driver_register(&volte_driver);/*lint !e64*/
	if (ret) {
		loge("voice proxy volte driver register fail,ERROR is %d\n", ret);
	}

	return ret;
}

static void __exit volte_exit( void )
{
	platform_driver_unregister(&volte_driver);
}

module_init(volte_init);
module_exit(volte_exit);

MODULE_DESCRIPTION("voice proxy volte driver");
MODULE_AUTHOR("Huawei Technologies Co., Ltd.");
MODULE_LICENSE("GPL");
