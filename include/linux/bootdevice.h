#ifndef BOOTDEVICE_H
#define BOOTDEVICE_H
#include <linux/device.h>

enum bootdevice_type { BOOT_DEVICE_EMMC = 0, BOOT_DEVICE_UFS = 1 };
#define UFS_VENDOR_HYNIX       0x1AD
void set_bootdevice_type(enum bootdevice_type type);
enum bootdevice_type get_bootdevice_type(void);
unsigned int get_bootdevice_manfid(void);
void set_bootdevice_name(struct device *dev);
void set_bootdevice_size(sector_t size);
void set_bootdevice_cid(u32 *cid);
void set_bootdevice_product_name(char *product_name, u32 len);
void set_bootdevice_pre_eol_info(u8 pre_eol_info);
void set_bootdevice_life_time_est_typ_a(u8 life_time_est_typ_a);
void set_bootdevice_life_time_est_typ_b(u8 life_time_est_typ_b);
void set_bootdevice_manfid(unsigned int manfid);

void set_rpmb_blk_count(uint64_t blk_count);
int get_rpmb_blk_count(uint64_t *blk_count, int delay_ms);

#endif
