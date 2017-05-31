
#ifndef  __PARAM_TO_SEC_OS_H__
#define  __PARAM_TO_SEC_OS_H__

#ifdef __cplusplus
extern "C"
{
#endif


#include <osl_types.h>

enum SVC_SECBOOT_IMG_TYPE {
    MODEM,
    HIFI,
    DSP,
    XDSP,
    TAS,
    WAS,
    CAS,
    MODEM_DTB,
    ISP,
    SOC_MAX
};

void set_param_cfg_to_sec(void);

#define BALONG_PARAM_BASE_ADDR        (0xA09FF800)    /* 0xA07FF800--0xA07FF8FF */
#define PARAM_MAGIC_OFFSET            (0x0)           /* 魔数:判断参数有效性 */
#define PARAM_CFG_OFFSET              (0x8)           /* 配置参数存放基地址*/

/*sec boot start */
struct image_info
{
    u64 ddr_addr;
    unsigned int ddr_size;
    unsigned int unreset_dependcore;
};

struct dynamic_load
{
    u32 load_cmd;
    u32 verify_flag;
};

struct sec_boot_modem_info
{
    struct image_info image_info[SOC_MAX];
    struct dynamic_load dynamic_load;
};

 /*sec boot end */

typedef struct tag_PARAM_CFG
{
    u32   magic;                   /* 魔数，标识配置参数的状态 */
    u32   protect_barrier_size;    /* 预留(4K)防止被踩，初始化为全F */
    u32   param_cfg_size;          /* 配置参数预留(16K)大小 */
    u64   icc_channel_base_addr;
    u32   icc_channel_max_size;
    struct sec_boot_modem_info sec_boot_modem_info;
}g_param_cfg;

void set_param_cfg_to_sec(void);

void set_modem_info_to_sec(void);

#ifdef __cplusplus
}
#endif

#endif   /* __PARAM_TO_SEC_OS_H__ */

