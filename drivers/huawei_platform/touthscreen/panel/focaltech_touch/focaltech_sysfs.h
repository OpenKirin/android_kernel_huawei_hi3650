#ifndef __FOCALTECH_SYSFS_H__
#define __FOCALTECH_SYSFS_H__

int fts_sysfs_init(struct i2c_client *client);
int fts_sysfs_exit(struct i2c_client *client);

void fts_test_dt_init_device_node(struct device_node *device);


#endif

