#ifndef __FOCALTECH_I2C_H__
#define __FOCALTECH_I2C_H__

int fts_i2c_read_universal(struct i2c_client *client,
	char *write_buf, int write_len, char *read_buf, int read_len);
int fts_i2c_write_universal(struct i2c_client
	*client, char *write_buf, int write_len);

int fts_i2c_read(unsigned char *addr, int addr_len,
	unsigned char *value_buf, int value_len);

int fts_read_reg(unsigned char addr, unsigned char *val);

int fts_i2c_write(unsigned char *write_buf, int write_len);
int fts_write_command(unsigned char command);
int fts_write_reg(unsigned char addr, const unsigned char val);

#endif
