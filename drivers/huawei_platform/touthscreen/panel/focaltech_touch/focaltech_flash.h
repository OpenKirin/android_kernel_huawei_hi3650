

#ifndef __FOCALTECH_FLASH_H__
#define __FOCALTECH_FLASH_H__

#include "focaltech_core.h"

/* common global define of all ic */
#define FTS_CMD_READ_FLASH		0x03
#define FTS_CMD_READ_PRAM		0x85

#define FTS_BOOT_VENDER_ID_ADDR1	0x00
#define FTS_BOOT_VENDER_ID_ADDR2	0x04
#define FTS_BOOT_PROJ_CODE_ADDR1	0x00
#define FTS_BOOT_PROJ_CODE_ADDR2	0x20

#define FTS_PACKAGE_SIZE		128
#define FTS_MAX_PACKET_LENGTH		256

#define FTS_RST_CMD_REG1		0xFC
#define FTS_READ_ID_REG			0x90
#define FTS_ERASE_APP_REG		0x61
#define FTS_ERASE_PARAMS_CMD		0x63
#define FTS_FW_WRITE_CMD		0xBF
#define FTS_REG_RESET_FW		0x07
#define FTS_REG_ECC			0xCC
#define FTS_RST_CMD_REG2		0xBC

#ifndef ERROR_CODE_OK
#define ERROR_CODE_OK			0x00
#endif
#define FTS_UPGRADE_AA			0xAA
#define FTS_UPGRADE_55			0x55

#define FTS_REG_CHIP_ID			0xA3
#define FTS_REG_CHIP_ID2		0x9F
#define FTS_REG_FW_VER			0xA6

#define FTS_REG_VENDOR_ID	 	0xA8
#define LEN_FLASH_ECC_MAX 		0xFFFE
#define FTS_REG_PROJ_CODE 		0x99
#define FTS_REG_OFFSET_CODE		0x90

#define FTS_MAX_PRAM_SIZE 		0x10000

#define FTS_REG_SOFT_RESET_FC 		0xFC
#define FTS_REG_BOOT_CHIP_ID 		0x90

#define FTS_CMD_WRITE_PRAM		0xAE
#define FTS_CMD_WRITE_FLASH   		0xBF
#define FTS_CMD_START_APP   		0x08
#define FTS_CMD_REBOOT_APP   		0x07
#define FTS_CMD_SET_MODE   		0x09

#define FTS_CMD_ERASURE_APP   		0x61
#define FTS_CMD_GET_STATUS   		0x6A

#define FTS_CMD_CALC_CRC   		0x64
#define FTS_CMD_SET_CALC_ADDR   	0x65
#define FTS_CMD_READ_CRC   		0x66

#define FTS_MODE_UPGRADE 		0X0B

#define FTS_REG_FLASH_TYPE 		0x05
#define FTS_FLASH_TYPE_WINBOND 		0x81
#define FTS_FLASH_TYPE_FT5003	 	0x80
#define FTS_FLASH_MAX_LEN_WINBOND 	(1024 * 60)
#define FTS_FLASH_MAX_LEN_FT5003 	(1024 * 64)
#define FTS_ERASURE_OK_STATUS 		0xF0AA
#define FTS_ECC_OK_STATUS 		0xF055
#define FTS_PROJECT_ID_LEN 		10

#define FTS_MODEL_SET_NO		2
#define FTS_FW_NAME_LEN			64
#define FTS_VENDOR_NAME_LEN		16

#define FTS_IC_MODE_ADDR		0x00
#define FTS_WORK_MODE_VALUE		0x00

#define FTS_FACTORYMODE_VALUE		0x40

#define FTS_PROJECT_INFO_ADDR		0xD7A0
#define FTS_REG_SLEEP			0xA5

/* addr of firmware */
#define FTS_FW_IMG_ADDR_VER		0x10E
#define FTS_FW_IC_ADDR_START		0x1000

/* length of string */
#define PRAM_NAME_DEFAULT_LEN		64

extern struct ts_data g_ts_data;

struct fts_upgrade_info 
{
    u8 chip_id;			/*from reg 0xa3*/
    u8 chip_id2;		/*from reg 0x9f*/
    u8 tpd_max_points;
    u8 auto_clb;
    u16 delay_aa;		/*delay of write FT_UPGRADE_AA */
    u16 delay_55;		/*delay of write FT_UPGRADE_55 */
    u8 upgrade_id_1;		/*upgrade id 1 */
    u8 upgrade_id_2;		/*upgrade id 2 */
    u16 delay_readid;		/*delay of read id */
    u16 delay_erase_flash;	/*delay of earse flash*/
    u8 tp_firmware_ver;		/*from reg 0xa6*/
    u8 vendor_id;
};

struct fts_upgrade_delay_time
{
    u8  chip_id;
    int hard_reset_delay;
    int erase_min_delay;
    int calc_crc_delay;
    int reboot_delay;
    int erase_query_per_time_delay;
        
    int write_flash_max_query_time;
    int read_ecc_max_query_time;
    int erase_flash_max_query_time;
    int upgrade_loop_time;
};

extern struct fts_upgrade_info fts_upgrade_info_curr;

int fts_flash_init(struct i2c_client *client);
int fts_flash_exit(void);
int fts_flash_upgrade_with_bin_file(struct fts_ts_platform_data *fts_pdata,
	char *firmware_name);

int fts_hardware_reset(struct fts_ts_platform_data *fts_pdata, int model);
int fts_read_vendor_id(struct fts_ts_platform_data *fts_pdata, u8 *vendor_id);

int fts_read_project_id_from_app(unsigned char *buf, size_t size);
int fts_read_project_id_from_pram(struct fts_ts_platform_data *fts_pdata,
	char *project_code, size_t size);
bool fts_read_pram_package(unsigned int offset, unsigned char *buf,
	unsigned short size);

int fts_enter_work_model(void);

int fts_enter_rom_update_model_by_software(void);
int fts_read_chip_id(unsigned int *chip_id);
int fts_firmware_auto_update(struct fts_ts_platform_data *fts_pdata,
	const char *product_name);
int fts_firmware_manual_update(struct fts_ts_platform_data *fts_pdata,
	const char *fw_name);
int fts_read_chip_id_from_rom(struct fts_ts_platform_data *fts_pdata,
	unsigned int *chip_id);
int fts_get_ic_firmware_version(unsigned char *ver);
int fts_read_project_id(struct fts_ts_platform_data *fts_pdata,
	char *project_id, size_t size);

#endif
