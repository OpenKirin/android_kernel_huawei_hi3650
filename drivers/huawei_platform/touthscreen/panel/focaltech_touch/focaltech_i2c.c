
#include "focaltech_core.h"

#define I2C_M_WRITE		0

static DEFINE_MUTEX(i2c_rw_access);

extern struct i2c_client *fts_i2c_client;

int fts_i2c_read_universal(struct i2c_client *client,
	char *write_buf, int write_len, char *read_buf, int read_len)
{
	int i = 0;
	int ret = 0;
	int msg_len = 0;
	struct i2c_msg msgs[2];
	struct i2c_msg *msg_addr = NULL;

	if (read_len <= 0 || NULL == read_buf) {
		TS_LOG_ERR("%s:%s, read len=%d\n", __func__,
			"read len is 0 or read buf is null", read_len);
		return -EINVAL;
	}

	msgs[0].addr = client->addr;
	msgs[0].flags = I2C_M_WRITE;
	msgs[0].len = write_len;
	msgs[0].buf = write_buf;

	msgs[1].addr = client->addr;
	msgs[1].flags = I2C_M_RD;
	msgs[1].len = read_len;
	msgs[1].buf = read_buf;

	if (write_len > 0) {
		msg_len = 2;
		msg_addr = &msgs[0];
	} else {
		msg_len = 1;
		msg_addr = &msgs[1];
	}

	mutex_lock(&i2c_rw_access);
	for (i = 0; i < 5; i++) {
		ret = i2c_transfer(client->adapter, msg_addr, msg_len);
		if (ret == msg_len) {
			mutex_unlock(&i2c_rw_access);			
			return 0;
		} else {
			TS_LOG_ERR("%s:i2c read error, ret=%d, retry=%d\n",
				__func__, ret, i);
		}
	}

	mutex_unlock(&i2c_rw_access);

	if (ret < 0 || ret != msg_len) {
		TS_LOG_ERR("%s:i2c read error, ret=%d, msg_len=%d\n",
			__func__, ret, msg_len);
		for (i = 0; i < write_len; i++) {
			TS_LOG_ERR("%s:cmd[%d]=0x%02X\n",
				__func__, write_buf[i]);
		}
	}

	if (ret > 0 && ret != msg_len)
		ret = -EIO;

	return ret;
}

int fts_i2c_read(
	unsigned char *addr,
	int addr_len,
	unsigned char *value_buf,
	int value_len)
{
	return fts_i2c_read_universal(fts_i2c_client,
		addr, addr_len, value_buf, value_len);
}

//int fts_i2c_read

int fts_read_reg(unsigned char addr, unsigned char *val)
{
	return fts_i2c_read(&addr, 1, val, 1);
}

int fts_i2c_write_universal(struct i2c_client *client,
	char *write_buf, int write_len)
{
	int i = 0;
	int ret = 0;
	struct i2c_msg msgs[1];

	if (write_len <= 0 || NULL == write_buf) {
		TS_LOG_ERR("%s:write len is less than 0\n", __func__);
		return -EINVAL;
	}

	msgs[0].addr = client->addr;
	msgs[0].flags = I2C_M_WRITE;
	msgs[0].len = write_len;
	msgs[0].buf = write_buf;

	mutex_lock(&i2c_rw_access);

	for (i = 0; i < 5; i++) {
		ret = i2c_transfer(client->adapter, msgs, 1);		
		if (ret == 1) {
			mutex_unlock(&i2c_rw_access);
			return 0;
		} else {
			TS_LOG_ERR("%s:i2c write error, ret=%d, retry=%d\n",
				__func__, ret, i);
		}
	}
	
	mutex_unlock(&i2c_rw_access);

	if (ret < 0 || ret != 1) {
		TS_LOG_ERR("%s:i2c write error, ret=%d\n", __func__, ret);
		for (i = 0; i < write_len; i++) {
			TS_LOG_ERR("%s:cmd[%d]=0x%02X\n",
				__func__, write_buf[i]);
		}
	}

	if (ret != 1 && ret > 0) {
		ret = -EIO;
	}

	return ret;
}

int fts_i2c_write(unsigned char *write_buf, int write_len)
{
	return fts_i2c_write_universal(fts_i2c_client, write_buf, write_len);
}

int fts_write_command(unsigned char command)
{
	return fts_i2c_write(&command, 1);
}

int fts_write_reg(unsigned char addr, const unsigned char val)
{
	unsigned char buf[2] = {0};

	buf[0] = addr;
	buf[1] = val;

	return fts_i2c_write(buf, sizeof(buf));
}

