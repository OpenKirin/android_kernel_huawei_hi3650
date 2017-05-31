#ifndef __HISI_DDR_AUTOFSGT_PROXY_KERNEL_H__
#define __HISI_DDR_AUTOFSGT_PROXY_KERNEL_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*same as vender/hisi/confidential/lpmcu/.../ddr_auto_fsgt.h*/
typedef enum {
	DDR_AUTOFSGT_ENABLE = 1,
	DDR_AUTOFSGT_DISABLE,
	DDR_AUTOFSGT_LOGIC_EN,
	DDR_AUTOFSGT_LOGIC_DIS,
} DDR_AUTOFSGT_CMD_ID;

typedef enum {
	DDR_AUTOFSGT_CLIENT_AP = 1,
	DDR_AUTOFSGT_CLIENT_BL31,
	DDR_AUTOFSGT_CLIENT_SECURE_OS,
	DDR_AUTOFSGT_CLIENT_DDR_MESSION,
	DDR_AUTOFSGT_CLIENT_LPMCU,
	DDR_AUTOFSGT_CLIENT_ONOFF,
	DDR_AUTOFSGT_CLIENT_BUTT,
} DDR_AUTOFSGT_CLIENT_ID;


typedef enum {
	DDR_AUTOFSGT_PROXY_CLIENT_DDRFLUX = 1,
	DDR_AUTOFSGT_PROXY_CLIENT_BUTT,
} DDR_AUTOFSGT_PROXY_CLIENT_ID;


/*s32 ddr_autofsgt_ctrl(DDR_AUTOFSGT_PROXY_CLIENT_ID client, DDR_AUTOFSGT_CMD_ID cmd)*/
extern int ddr_autofsgt_ctrl(unsigned int client, unsigned int cmd);




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

#endif /* end of hisi_ddr_autofsgt_proxy_kernel.h */
