#ifndef _PARTITION_H_
#define _PARTITION_H_

#include "hisi_partition.h"

typedef struct partition {
	char name[PART_NAMELEN];
	unsigned long long start;
	unsigned long long length;
	unsigned int flags;
}PARTITION;

#if defined(CONFIG_HISI_PARTITION_HI3650)
static const struct partition partition_table_emmc[] =
{
    {PART_XLOADER,           0,         256,      EMMC_BOOT_MAJOR_PART},
    {PART_PTABLE,            0,         512,      EMMC_USER_PART}, /* ptable           512K */
    {PART_VRL,               512,       256,      EMMC_USER_PART}, /* VRL              256K p1*/
    {PART_VRL_BACKUP,        768,       256,      EMMC_USER_PART}, /* VRL backup       256K p2*/
    {PART_FW_LPM3,           1024,      256,      EMMC_USER_PART}, /* mcuimage         256K p3*/
    {PART_FRP,               1280,      768,      EMMC_USER_PART}, /* frp              768K p4*/
    {PART_FASTBOOT,          2*1024,    4*1024,   EMMC_USER_PART}, /* fastboot         4M   p5*/
    {PART_MODEMNVM_FACTORY,  6*1024,    4*1024,   EMMC_USER_PART}, /* modemnvm factory 4M   p6*/
    {PART_NVME,              10*1024,   6*1024,   EMMC_USER_PART}, /* nvme             6M   p7*/
    {PART_OEMINFO,           16*1024,   64*1024,  EMMC_USER_PART}, /* oeminfo          64M  p8*/
    {PART_SPLASH,            80*1024,   8*1024,   EMMC_USER_PART}, /* splash           8M   p9*/
    {PART_MODEMNVM_BACKUP,   88*1024,   4*1024,   EMMC_USER_PART}, /* modemnvm backup  4M   p10*/
    {PART_MODEMNVM_IMG,      92*1024,   8*1024,   EMMC_USER_PART}, /* modemnvm img     8M   p11*/
    {PART_MODEMNVM_SYSTEM,   100*1024,  4*1024,   EMMC_USER_PART}, /* modemnvm system  4M   p12*/
    {PART_SECURE_STORAGE,    104*1024,  32*1024,  EMMC_USER_PART}, /* secure storage   32M  p13*/
    {PART_3RDMODEMNVM,       136*1024,  16*1024,  EMMC_USER_PART}, /* 3rdmodemnvm      16M  p14*/
    {PART_3RDMODEMNVMBKP,    152*1024,  16*1024,  EMMC_USER_PART}, /* 3rdmodemnvmback  16M  p15*/
    {PART_PERSIST,           168*1024,  2*1024,   EMMC_USER_PART}, /* persist          2M   p16*/
    {PART_RESERVED1,         170*1024,  14*1024,  EMMC_USER_PART}, /* reserved1        14M  p17*/
    {PART_MODEM_OM,          184*1024,  32*1024,  EMMC_USER_PART}, /* modem om         32M  p18*/
    {PART_SPLASH2,           216*1024,  64*1024,  EMMC_USER_PART}, /* splash2          64M  p19*/
    {PART_MISC,              280*1024,  2*1024,   EMMC_USER_PART}, /* misc             2M   p20*/
    {PART_MODEMNVM_UPDATE,   282*1024,  24*1024,  EMMC_USER_PART}, /* modemnvm update  24M  p21*/
    {PART_RECOVERY2,         306*1024,  64*1024,  EMMC_USER_PART}, /* recovery2        64M  p22*/
    {PART_RESERVED2,         370*1024,  64*1024,  EMMC_USER_PART}, /* reserved2        64M  p23*/
    {PART_TEEOS,             434*1024,  4*1024,   EMMC_USER_PART}, /* teeos            4M   p24*/
    {PART_TRUSTFIRMWARE,     438*1024,  2*1024,   EMMC_USER_PART}, /* trustfirmware    2M   p25*/
    {PART_SENSORHUB,         440*1024,  16*1024,  EMMC_USER_PART}, /* sensorhub        16M  p26*/
    {PART_FW_HIFI,           456*1024,  12*1024,  EMMC_USER_PART}, /* hifi             12M  p27*/
    {PART_BOOT,              468*1024,  32*1024,  EMMC_USER_PART}, /* boot             32M  p28*/
    {PART_RECOVERY,          500*1024,  64*1024,  EMMC_USER_PART}, /* recovery         64M  p29*/
    {PART_DTS,               564*1024,  64*1024,  EMMC_USER_PART}, /* dtimage          64M  p30*/
    {PART_MODEM,             628*1024,  64*1024,  EMMC_USER_PART}, /* modem            64M  p31*/
    {PART_MODEM_DSP,         692*1024,  16*1024,  EMMC_USER_PART}, /* modem_dsp        16M  p32*/
    {PART_MODEM_DTB,         708*1024,  8*1024,   EMMC_USER_PART}, /* modem_dtb        8M   p33*/
    {PART_DFX,               716*1024,  16*1024,  EMMC_USER_PART}, /* dfx              16M  p34*/
    {PART_3RDMODEM,          732*1024,  64*1024,  EMMC_USER_PART}, /* 3rdmodem         64M  p35*/
    {PART_CACHE,             796*1024,  256*1024, EMMC_USER_PART}, /* cache            256M p36*/
    {PART_HISITEST0,         1052*1024, 2*1024,   EMMC_USER_PART}, /* hisitest0        2M   p37*/
    {PART_HISITEST1,         1054*1024, 2*1024,   EMMC_USER_PART}, /* hisitest1        2M   p38*/
#ifdef CONFIG_VENDORIMAGE_FILE_SYSTEM_TYPE
    {PART_PATCH,             1056*1024,  32*1024,  EMMC_USER_PART}, /* patch            32M  p39*/
    {PART_BOOTFAIL_INFO,     1088*1024,  2*1024,   EMMC_USER_PART}, /* bootfail info    2M   p40*/
    {PART_RRECORD,           1090*1024,  16*1024,  EMMC_USER_PART}, /* rrecord          16M  p41*/
    {PART_RESERVED3,         1106*1024,  14*1024,  EMMC_USER_PART}, /* rrecord          14M  p42*/

#ifdef CONFIG_MARKET_OVERSEA
    {PART_SYSTEM,            1120*1024, 3008*1024,EMMC_USER_PART}, /* system           3008M p43*/
    {PART_CUST,              4128*1024, 192*1024, EMMC_USER_PART}, /* cust             192M  p44*/
    {PART_VERSION,           4320*1024, 32*1024,  EMMC_USER_PART}, /* version          32M    p45*/
    {PART_VENDOR,            4352*1024, 608*1024, EMMC_USER_PART}, /* vendor           608M  p46*/
    {PART_PRODUCT,           4960*1024, 192*1024, EMMC_USER_PART}, /* product          192M   p47*/
    {PART_HISITEST2,         5152*1024, 4*1024,   EMMC_USER_PART}, /* hisitest2        4M    p48*/
    {PART_USERDATA,          5156*1024, 4096*1024,EMMC_USER_PART}, /* userdata         4096M p49*/
#elif defined CONFIG_MARKET_INTERNAL
    {PART_SYSTEM,            1120*1024, 2688*1024,EMMC_USER_PART}, /* system           2688M p43*/
    {PART_CUST,              3808*1024, 192*1024, EMMC_USER_PART}, /* cust             192M  p44*/
    {PART_VERSION,           4000*1024, 32*1024,  EMMC_USER_PART}, /* version          32M    p45*/
    {PART_VENDOR,            4032*1024, 608*1024, EMMC_USER_PART}, /* vendor           608M  p46*/
    {PART_PRODUCT,           4640*1024, 192*1024, EMMC_USER_PART}, /* product          192M   p47*/
    {PART_HISITEST2,         4832*1024, 4*1024,   EMMC_USER_PART}, /* hisitest2        4M    p48*/
    {PART_USERDATA,          4836*1024, 4096*1024,EMMC_USER_PART}, /* userdata         4096M p49*/
#else
    {PART_SYSTEM,            1120*1024, 1984*1024,EMMC_USER_PART}, /* system           1984M p43*/
    {PART_CUST,              3104*1024, 192*1024, EMMC_USER_PART}, /* cust             192M  p44*/
    {PART_VERSION,           3296*1024, 32*1024,   EMMC_USER_PART}, /* version         32M    p45*/
    {PART_VENDOR,            3328*1024, 608*1024, EMMC_USER_PART}, /* vendor           608M  p46*/
    {PART_PRODUCT,           3936*1024, 192*1024,  EMMC_USER_PART}, /* product         192M   p47*/
    {PART_HISITEST2,         4128*1024, 4*1024,   EMMC_USER_PART}, /* hisitest2        4M    p48*/
    {PART_USERDATA,          4132*1024, 4096*1024,EMMC_USER_PART}, /* userdata         4096M p49*/
#endif
#else
#ifdef CONFIG_MARKET_OVERSEA
    {PART_SYSTEM,            1056*1024, 3584*1024,EMMC_USER_PART}, /* system           3584M p39*/
    {PART_CUST,              4640*1024, 512*1024, EMMC_USER_PART}, /* cust             512M  p40*/
    {PART_HISITEST2,         5152*1024, 4*1024,   EMMC_USER_PART}, /* hisitest2        4M    p41*/
    {PART_USERDATA,          5156*1024, 4096*1024,EMMC_USER_PART}, /* userdata         4096M p42*/
#elif defined CONFIG_MARKET_INTERNAL
    {PART_SYSTEM,            1056*1024, 3264*1024,EMMC_USER_PART}, /* system           3264M p39*/
    {PART_CUST,              4320*1024, 512*1024, EMMC_USER_PART}, /* cust             512M  p40*/
    {PART_HISITEST2,         4832*1024, 4*1024,   EMMC_USER_PART}, /* hisitest2        4M    p41*/
    {PART_USERDATA,          4836*1024, 4096*1024,EMMC_USER_PART}, /* userdata         4096M p42*/
#else
    {PART_SYSTEM,            1056*1024, 2560*1024,EMMC_USER_PART}, /* system           2560M p39*/
    {PART_CUST,              3616*1024, 512*1024, EMMC_USER_PART}, /* cust             512M  p40*/
    {PART_HISITEST2,         4128*1024, 4*1024,   EMMC_USER_PART}, /* hisitest2        4M    p41*/
    {PART_USERDATA,          4132*1024, 4096*1024,EMMC_USER_PART}, /* userdata         4096M p42*/
#endif
#endif
    {"0", 0, 0, 0},                                        /* total 8228M*/
};

#elif defined (CONFIG_HISI_PARTITION_HI6250)
static const struct partition partition_table_emmc[] =
{
    {PART_XLOADER,           0,         256,      EMMC_BOOT_MAJOR_PART},
    {PART_PTABLE,            0,         512,      EMMC_USER_PART}, /* ptable           512K */
    {PART_VRL,               512,       256,      EMMC_USER_PART}, /* VRL              256K p1*/
    {PART_VRL_BACKUP,        768,       256,      EMMC_USER_PART}, /* VRL backup       256K p2*/
    {PART_FW_LPM3,           1024,      256,      EMMC_USER_PART}, /* mcuimage         256K p3*/
    {PART_FRP,               1280,      768,      EMMC_USER_PART}, /* frp              768K p4*/
    {PART_FASTBOOT,          2*1024,    4*1024,   EMMC_USER_PART}, /* fastboot         4M   p5*/
    {PART_MODEMNVM_FACTORY,  6*1024,    4*1024,   EMMC_USER_PART}, /* modemnvm factory 4M   p6*/
    {PART_NVME,              10*1024,   6*1024,   EMMC_USER_PART}, /* nvme             6M   p7*/
    {PART_OEMINFO,           16*1024,   64*1024,  EMMC_USER_PART}, /* oeminfo          64M  p8*/
    {PART_RESERVED3,         80*1024,   4*1024,   EMMC_USER_PART}, /* reserved3        4M   p9*/
    {PART_MODEMNVM_BACKUP,   84*1024,   4*1024,   EMMC_USER_PART}, /* modemnvm backup  4M   p10*/
    {PART_MODEMNVM_IMG,      88*1024,   8*1024,   EMMC_USER_PART}, /* modemnvm img     8M   p11*/
    {PART_MODEMNVM_SYSTEM,   96*1024,   4*1024,   EMMC_USER_PART}, /* modemnvm system  4M   p12*/
    {PART_SECURE_STORAGE,    100*1024,  32*1024,  EMMC_USER_PART}, /* secure storage   32M  p13*/
    {PART_RESERVED4,         132*1024,  2*1024,   EMMC_USER_PART}, /* reserved4        2M   p14*/
    {PART_RESERVED5,         134*1024,  2*1024,   EMMC_USER_PART}, /* reserved5        2M   p15*/
    {PART_PERSIST,           136*1024,  2*1024,   EMMC_USER_PART}, /* persist          2M   p16*/
    {PART_RESERVED1,         138*1024,  14*1024,  EMMC_USER_PART}, /* reserved1        14M  p17*/
    {PART_MODEM_OM,          152*1024,  32*1024,  EMMC_USER_PART}, /* modem om         32M  p18*/
    {PART_SPLASH2,           184*1024,  64*1024,  EMMC_USER_PART}, /* splash2          64M  p19*/
    {PART_MISC,              248*1024,  2*1024,   EMMC_USER_PART}, /* misc             2M   p20*/
    {PART_MODEMNVM_UPDATE,   250*1024,  24*1024,  EMMC_USER_PART}, /* modemnvm update  24M  p21*/
    {PART_RECOVERY2,         274*1024,  64*1024,  EMMC_USER_PART}, /* recovery2        64M  p22*/
    {PART_RESERVED2,         338*1024,  60*1024,  EMMC_USER_PART}, /* reserved2        60M  p23*/
    {PART_TEEOS,             398*1024,  4*1024,   EMMC_USER_PART}, /* teeos            4M   p24*/
    {PART_TRUSTFIRMWARE,     402*1024,  2*1024,   EMMC_USER_PART}, /* trustfirmware    2M   p25*/
    {PART_SENSORHUB,         404*1024,  16*1024,  EMMC_USER_PART}, /* sensorhub        16M  p26*/
    {PART_FW_HIFI,           420*1024,  12*1024,  EMMC_USER_PART}, /* hifi             12M  p27*/
    {PART_BOOT,              432*1024,  32*1024,  EMMC_USER_PART}, /* boot             32M  p28*/
    {PART_RECOVERY,          464*1024,  64*1024,  EMMC_USER_PART}, /* recovery         64M  p29*/
    {PART_DTS,               528*1024,  32*1024,  EMMC_USER_PART}, /* dtimage          32M  p30*/
    {PART_MODEM_FW,          560*1024,  96*1024,  EMMC_USER_PART}, /* modem_fw         96M  p31*/
    {PART_RESERVED7,         656*1024,  2*1024,   EMMC_USER_PART}, /* reserved7        2M   p32*/
    {PART_RESERVED8,         658*1024,  2*1024,   EMMC_USER_PART}, /* reserved8        2M   p33*/
    {PART_DFX,               660*1024,  16*1024,  EMMC_USER_PART}, /* dfx              16M  p34*/
    {PART_RESERVED6,         676*1024,  4*1024,   EMMC_USER_PART}, /* reserved6        4M   p35*/
    {PART_CACHE,             680*1024,  256*1024, EMMC_USER_PART}, /* cache            256M p36*/
    {PART_HISITEST0,         936*1024,  2*1024,   EMMC_USER_PART}, /* hisitest0        2M   p37*/
    {PART_HISITEST1,         938*1024,  2*1024,   EMMC_USER_PART}, /* hisitest1        2M   p38*/
    {PART_HISITEST2,         940*1024,  4*1024,   EMMC_USER_PART}, /* hisitest2        4M   p39*/
#if (defined(CONFIG_MARKET_OVERSEA) || defined(CONFIG_MARKET_INTERNAL))
    {PART_PATCH,             944*1024,  32*1024,  EMMC_USER_PART}, /* patch            32M  p40*/
    {PART_BOOTFAIL_INFO,     976*1024,  2*1024,   EMMC_USER_PART}, /* bootfail_info    2M   p41*/
    {PART_RRECORD,           978*1024,  16*1024,  EMMC_USER_PART}, /* rrecord          16M  p42*/
    {PART_RESERVED9,         994*1024,  30*1024,  EMMC_USER_PART}, /* reserved9        30M  p43*/
#endif
#ifdef CONFIG_MARKET_OVERSEA
    {PART_SYSTEM,            1024*1024, 4688*1024,EMMC_USER_PART}, /* system           4688M p44*/
    {PART_CUST,              5712*1024, 192*1024, EMMC_USER_PART}, /* cust             192M  p45*/
    {PART_VERSION,           5904*1024, 32*1024,  EMMC_USER_PART}, /* version          32M   p46*/
    {PART_VENDOR,            5936*1024, 784*1024, EMMC_USER_PART}, /* vendor           784M  p47*/
    {PART_PRODUCT,           6720*1024, 192*1024, EMMC_USER_PART}, /* product          192M  p48*/
    {PART_USERDATA,          6912*1024, 4096*1024,EMMC_USER_PART}, /* userdata         4096M p49*/
#elif defined CONFIG_MARKET_INTERNAL
    {PART_SYSTEM,            1024*1024, 3552*1024,EMMC_USER_PART}, /* system           3552M p44*/
    {PART_CUST,              4576*1024, 192*1024, EMMC_USER_PART}, /* cust             192M  p45*/
    {PART_VERSION,           4768*1024, 32*1024,  EMMC_USER_PART}, /* version          32M   p46*/
    {PART_VENDOR,            4800*1024, 784*1024, EMMC_USER_PART}, /* vendor           784M  p47*/
    {PART_PRODUCT,           5584*1024, 192*1024, EMMC_USER_PART}, /* product          192M  p48*/
    {PART_USERDATA,          5776*1024, 4096*1024,EMMC_USER_PART}, /* userdata         4096M p49*/
#elif defined CONFIG_MARKET_BERLIN_OVERSEA
    {PART_PATCH,             944*1024,  32*1024,  EMMC_USER_PART}, /* patch             32M   p40*/
    {PART_BOOTFAIL_INFO,     976*1024,  2*1024,   EMMC_USER_PART}, /* bootfail_info     2M    p41*/
    {PART_RRECORD,           978*1024,  16*1024,  EMMC_USER_PART}, /* rrecord           16M   p42*/
    {PART_RESERVED9,         994*1024,  14*1024,  EMMC_USER_PART}, /* reserved9         14M   p43*/
    {PART_SYSTEM,            1008*1024, 3008*1024,EMMC_USER_PART}, /* system            3008M p44*/
    {PART_CUST,              4016*1024, 192*1024, EMMC_USER_PART}, /* cust              192M  p45*/
    {PART_VERSION,           4208*1024, 32*1024,  EMMC_USER_PART}, /* version           24M   p46*/
    {PART_VENDOR,            4240*1024, 608*1024, EMMC_USER_PART}, /* vendor            608M  p47*/
    {PART_PRODUCT,           4848*1024, 192*1024, EMMC_USER_PART}, /* product           200M  p48*/
    {PART_USERDATA,          5040*1024, 4096*1024,EMMC_USER_PART}, /* userdata          4096M p49*/
#elif defined CONFIG_MARKET_BERLIN_INTERNAL
    {PART_PATCH,             944*1024,  32*1024,  EMMC_USER_PART}, /* patch             32M   p40*/
    {PART_BOOTFAIL_INFO,     976*1024,  2*1024,   EMMC_USER_PART}, /* bootfail_info     2M    p41*/
    {PART_RRECORD,           978*1024,  16*1024,  EMMC_USER_PART}, /* rrecord           16M   p42*/
    {PART_RESERVED9,         994*1024,  14*1024,  EMMC_USER_PART}, /* reserved9         14M   p43*/
    {PART_SYSTEM,            1008*1024, 2688*1024,EMMC_USER_PART}, /* system            2688M p44*/
    {PART_CUST,              3696*1024, 192*1024, EMMC_USER_PART}, /* cust              192M  p45*/
    {PART_VERSION,           3888*1024, 32*1024,  EMMC_USER_PART}, /* version           32M   p46*/
    {PART_VENDOR,            3920*1024, 608*1024, EMMC_USER_PART}, /* vendor            608M  p47*/
    {PART_PRODUCT,           4528*1024, 192*1024, EMMC_USER_PART}, /* product           192M  p48*/
    {PART_USERDATA,          4720*1024, 4096*1024,EMMC_USER_PART}, /* userdata          4096M p49*/
#else
#ifdef CONFIG_VENDORIMAGE_FILE_SYSTEM_TYPE
    {PART_PATCH,             944*1024,  32*1024,  EMMC_USER_PART}, /* patch             32M   p40*/
    {PART_BOOTFAIL_INFO,     976*1024,  2*1024,   EMMC_USER_PART}, /* bootfail_info     2M    p41*/
    {PART_RRECORD,           978*1024,  16*1024,  EMMC_USER_PART}, /* rrecord           16M   p42*/
    {PART_RESERVED9,         994*1024,  14*1024,  EMMC_USER_PART}, /* reserved9         14M   p43*/
    {PART_SYSTEM,            1008*1024, 1984*1024,EMMC_USER_PART}, /* system            1984M p44*/
    {PART_CUST,              2992*1024, 192*1024, EMMC_USER_PART}, /* cust              192M  p45*/
    {PART_VERSION,           3184*1024, 32*1024,  EMMC_USER_PART}, /* version           32M   p46*/
    {PART_VENDOR,            3216*1024, 608*1024, EMMC_USER_PART}, /* vendor            608M  p47*/
    {PART_PRODUCT,           3824*1024, 192*1024, EMMC_USER_PART}, /* product           192M  p48*/
    {PART_USERDATA,          4016*1024, 4096*1024,EMMC_USER_PART}, /* userdata          4096M p49*/
#else
    {PART_SYSTEM,            944*1024,  2496*1024,EMMC_USER_PART}, /* system           2496M p40*/
    {PART_PATCH,             3440*1024, 32*1024,  EMMC_USER_PART}, /* patch            32M  p41*/
    {PART_BOOTFAIL_INFO,     3472*1024, 2*1024,   EMMC_USER_PART}, /* bootfail_info    2M   p42*/
    {PART_RRECORD,           3474*1024, 16*1024,  EMMC_USER_PART}, /* rrecord          16M  p43*/
    {PART_RESERVED9,         3490*1024, 14*1024,  EMMC_USER_PART}, /* reserved9        14M  p44*/
    {PART_CUST,              3504*1024, 128*1024, EMMC_USER_PART}, /* cust             128M  p45*/
    {PART_VERSION,           3632*1024, 8*1024,   EMMC_USER_PART}, /* version          8M   p46*/
    {PART_VENDOR,            3640*1024, 288*1024, EMMC_USER_PART}, /* vendor           288M p47*/
    {PART_PRODUCT,           3928*1024, 88*1024,  EMMC_USER_PART}, /* product          88M  p48*/
    {PART_USERDATA,          4016*1024, 4096*1024,EMMC_USER_PART}, /* userdata         4096M p49*/
#endif
#endif
    {"0", 0, 0, 0},                                       /* */
};
#elif defined CONFIG_HISI_PARTITION_HI3660
static const struct partition partition_table_emmc[] =
{
  {PART_XLOADER_A,        0,         2*1024,        EMMC_BOOT_MAJOR_PART},
  {PART_XLOADER_B,        0,         2*1024,        EMMC_BOOT_BACKUP_PART},
  {PART_PTABLE,           0,         512,           EMMC_USER_PART},/* ptable          512K */
  {PART_FRP,              512,       512,           EMMC_USER_PART},/* frp             512K   p1*/
  {PART_PERSIST,          1024,      2048,          EMMC_USER_PART},/* persist         2048K  p2*/
  {PART_RESERVED1,        3072,      5120,          EMMC_USER_PART},/* reserved1       5120K  p3*/
  {PART_RESERVED6,        8*1024,    512,           EMMC_USER_PART},/* reserved6       512K   p4*/
  {PART_VRL,              8704,      512,           EMMC_USER_PART},/* vrl             512K   p5*/
  {PART_VRL_BACKUP,       9216,      512,           EMMC_USER_PART},/* vrl backup      512K   p6*/
  {PART_MODEM_SECURE,     9728,      8704,          EMMC_USER_PART},/* modem_secure    8704k  p7*/
  {PART_NVME,             18*1024,   6*1024,        EMMC_USER_PART},/* nvme            6M     p8*/
  {PART_OEMINFO,          24*1024,   64*1024,       EMMC_USER_PART},/* oeminfo         64M    p9*/
  {PART_SECURE_STORAGE,   88*1024,   32*1024,       EMMC_USER_PART},/* secure storage  32M    p10*/
  {PART_MODEM_OM,         120*1024,  32*1024,       EMMC_USER_PART},/* modem om        32M    p11*/
  {PART_MODEMNVM_FACTORY, 152*1024,  4*1024,        EMMC_USER_PART},/* modemnvm factory4M     p12*/
  {PART_MODEMNVM_BACKUP,  156*1024,  4*1024,        EMMC_USER_PART},/* modemnvm backup 4M     p13*/
  {PART_MODEMNVM_IMG,     160*1024,  12*1024,       EMMC_USER_PART},/* modemnvm img    12M    p14*/
  {PART_MODEMNVM_SYSTEM,  172*1024,  4*1024,        EMMC_USER_PART},/* modemnvm system 4M     p15*/
  {PART_SPLASH2,          176*1024,  80*1024,       EMMC_USER_PART},/* splash2         80M    p16*/
  {PART_CACHE,            256*1024,  256*1024,        EMMC_USER_PART},/* cache           8M     p17*/
  {PART_BOOTFAIL_INFO,    512*1024,  2*1024,        EMMC_USER_PART},/* bootfail info   2MB    p18*/
  {PART_MISC,             514*1024,  2*1024,        EMMC_USER_PART},/* misc            2M     p19*/
  {PART_RESERVED2,        516*1024,  32*1024,       EMMC_USER_PART},/* reserved2       32M    p20*/
  {PART_RESERVED10,        548*1024,  4*1024,        EMMC_USER_PART},/* PART_RESERVED10       4M     p21*/
  {PART_HISEE_FS,         552*1024,  8*1024,        EMMC_USER_PART},/* hisee_fs        8M     p22*/
  {PART_DFX,              560*1024,  16*1024,       EMMC_USER_PART},/* dfx             16M    p23*/
  {PART_RRECORD,          576*1024,  16*1024,       EMMC_USER_PART},/* rrecord         16M    p24*/
  {PART_FW_LPM3_A,        592*1024,  256,           EMMC_USER_PART},/* mcuimage        256K   p25*/
  {PART_RESERVED3_A,      606464,    3840,          EMMC_USER_PART},/* reserved3A      3840KB p26*/
  {PART_HISEE_IMG_A,      596*1024,    4*1024,          EMMC_USER_PART},/* part_hisee_img_a   4*1024KB p27*/
  {PART_FASTBOOT_A,       600*1024,  12*1024,       EMMC_USER_PART},/* fastboot        12M    p28*/
  {PART_VECTOR_A,         612*1024,  4*1024,        EMMC_USER_PART},/* avs vector      4M     p29*/
  {PART_ISP_BOOT_A,       616*1024,  2*1024,        EMMC_USER_PART},/* isp_boot        2M     p30*/
  {PART_ISP_FIRMWARE_A,   618*1024,  14*1024,       EMMC_USER_PART},/* isp_firmware    14M    p31*/
  {PART_FW_HIFI_A,        632*1024,  12*1024,       EMMC_USER_PART},/* hifi            12M    p32*/
  {PART_TEEOS_A,          644*1024,  8*1024,        EMMC_USER_PART},/* teeos           8M     p33*/
  {PART_RECOVERY2_A,      652*1024,  64*1024,       EMMC_USER_PART},/* recovery2       64M    p34*/
  {PART_SENSORHUB_A,      716*1024,  16*1024,       EMMC_USER_PART},/* sensorhub       16M    p35*/
  {PART_BOOT_A,           732*1024,  32*1024,       EMMC_USER_PART},/* boot            32M    p36*/
  {PART_RECOVERY_A,       764*1024,  64*1024,       EMMC_USER_PART},/* recovery        64M    p37*/
  {PART_DTS_A,            828*1024,  16*1024,       EMMC_USER_PART},/* dtimage         16M    p38*/
  {PART_TRUSTFIRMWARE_A,  844*1024,  2*1024,        EMMC_USER_PART},/* trustfirmware   2M     p39*/
  {PART_MODEM_FW_A,       846*1024,  56*1024,       EMMC_USER_PART},/* modem_fw        56M    p40*/
  {PART_RESERVED4_A,      902*1024,  50*1024,       EMMC_USER_PART},/* reserved4A      50M    p41*/
  {PART_MODEMNVM_UPDATE_A,952*1024,  80*1024,       EMMC_USER_PART},/* modemnvm update 80M    p42*/
  {PART_PATCH_A,          1032 *1024,  32*1024,       EMMC_USER_PART},/* patch           16M    p43*/
  {PART_VERSION_A,        1064*1024,  24*1024,        EMMC_USER_PART},/* version         8M     p44*/
  {PART_VENDOR_A,         1088*1024,  784*1024,      EMMC_USER_PART},/* vendor          704M   p45*/
  {PART_PRODUCT_A,        1872*1024, 192*1024,      EMMC_USER_PART},/* product         240M   p46*/
  {PART_CUST_A,           2064*1024, 192*1024,      EMMC_USER_PART},/* cust            256M   p47*/
  #ifdef CONFIG_MARKET_INTERNAL
  {PART_SYSTEM_A,         2256*1024, 3552*1024,     EMMC_USER_PART},/* system          3697M  p48*/
  {PART_RESERVED5,        5808*1024, 128*1024,       EMMC_USER_PART},/* reserved5       64M    p49*/
  {PART_USERDATA,         5936*1024, (4UL)*1024*1024,EMMC_USER_PART},/* userdata       4G     p50*/
  #else
  {PART_SYSTEM_A,         2256*1024, 4688*1024,     EMMC_USER_PART},/* system          4000M  p48*/
  {PART_RESERVED5,        6944*1024, 128*1024,       EMMC_USER_PART},/* reserved5       64M    p49*/
  {PART_USERDATA,         7072*1024, (4UL)*1024*1024,EMMC_USER_PART},/* userdata       4G    p50*/
  #endif
  {"0", 0, 0, 0},                                        /* total 11848M*/
};
#ifdef CONFIG_HISI_STORAGE_UFS_PARTITION
static const struct partition partition_table_ufs[] =
{
  {PART_XLOADER_A,        0,         2*1024,        UFS_PART_0},
  {PART_XLOADER_B,        0,         2*1024,        UFS_PART_1},
  {PART_PTABLE,           0,         512,           UFS_PART_2},/* ptable          512K */
  {PART_FRP,              512,       512,           UFS_PART_2},/* frp             512K   p1*/
  {PART_PERSIST,          1024,      2048,          UFS_PART_2},/* persist         2048K  p2*/
  {PART_RESERVED1,        3072,      5120,          UFS_PART_2},/* reserved1       5120K  p3*/
  {PART_PTABLE_LU3,       0,         512,           UFS_PART_3},/* ptable_lu3      512K   p0*/
  {PART_VRL,              512,       512,           UFS_PART_3},/* vrl             512K   p1*/
  {PART_VRL_BACKUP,       1024,      512,           UFS_PART_3},/* vrl backup      512K   p2*/
  {PART_MODEM_SECURE,     1536,      8704,          UFS_PART_3},/* modem_secure    8704k  p3*/
  {PART_NVME,             10*1024,   6*1024,        UFS_PART_3},/* nvme            6M     p4*/
  {PART_OEMINFO,          16*1024,   64*1024,       UFS_PART_3},/* oeminfo         64M    p5*/
  {PART_SECURE_STORAGE,   80*1024,   32*1024,       UFS_PART_3},/* secure storage  32M    p6*/
  {PART_MODEM_OM,         112*1024,  32*1024,       UFS_PART_3},/* modem om        32M    p7*/
  {PART_MODEMNVM_FACTORY, 144*1024,  4*1024,        UFS_PART_3},/* modemnvm factory4M     p8*/
  {PART_MODEMNVM_BACKUP,  148*1024,  4*1024,        UFS_PART_3},/* modemnvm backup 4M     p9*/
  {PART_MODEMNVM_IMG,     152*1024,  12*1024,       UFS_PART_3},/* modemnvm img    12M    p10*/
  {PART_MODEMNVM_SYSTEM,  164*1024,  4*1024,        UFS_PART_3},/* modemnvm system 4M     p11*/
  {PART_SPLASH2,          168*1024,  80*1024,       UFS_PART_3},/* splash2         80M    p12*/
  {PART_CACHE,            248*1024,  256*1024,        UFS_PART_3},/* cache           8M     p13*/
  {PART_BOOTFAIL_INFO,    504*1024,  2*1024,        UFS_PART_3},/* bootfail info   2MB    p14*/
  {PART_MISC,             506*1024,  2*1024,        UFS_PART_3},/* misc            2M     p15*/
  {PART_RESERVED2,        508*1024,  32*1024,       UFS_PART_3},/* reserved2       32M    p16*/
  {PART_RESERVED10,        540*1024,  4*1024,        UFS_PART_3},/* PART_RESERVED10       4M     p17*/
  {PART_HISEE_FS,         544*1024,  8*1024,        UFS_PART_3},/* hisee_fs        8M     p18*/
  {PART_DFX,              552*1024,  16*1024,       UFS_PART_3},/* dfx             16M    p19*/
  {PART_RRECORD,          568*1024,  16*1024,       UFS_PART_3},/* rrecord         16M    p20*/
  {PART_FW_LPM3_A,        584*1024,  256,           UFS_PART_3},/* mcuimage        256K   p21*/
  {PART_RESERVED3_A,      598272,    3840,          UFS_PART_3},/*reserved3A      3840KB  p22*/
  {PART_HISEE_IMG_A,      588*1024,    4*1024,          UFS_PART_3},/*part_hisee_img_a   4*1024KB  p23*/
  {PART_FASTBOOT_A,       592*1024,  12*1024,       UFS_PART_3},/* fastboot        12M    p24*/
  {PART_VECTOR_A,         604*1024,  4*1024,        UFS_PART_3},/* avs vector      4M     p25*/
  {PART_ISP_BOOT_A,       608*1024,  2*1024,        UFS_PART_3},/* isp_boot        2M     p26*/
  {PART_ISP_FIRMWARE_A,   610*1024,  14*1024,       UFS_PART_3},/* isp_firmware    14M    p27*/
  {PART_FW_HIFI_A,        624*1024,  12*1024,       UFS_PART_3},/* hifi            12M    p28*/
  {PART_TEEOS_A,          636*1024,  8*1024,        UFS_PART_3},/* teeos           8M     p29*/
  {PART_RECOVERY2_A,      644*1024,  64*1024,       UFS_PART_3},/* recovery2       64M    p30*/
  {PART_SENSORHUB_A,      708*1024,  16*1024,       UFS_PART_3},/* sensorhub       16M    p31*/
  {PART_BOOT_A,           724*1024,  32*1024,       UFS_PART_3},/* boot            32M    p32*/
  {PART_RECOVERY_A,       756*1024,  64*1024,       UFS_PART_3},/* recovery        64M    p33*/
  {PART_DTS_A,            820*1024,  16*1024,       UFS_PART_3},/* dtimage         16M    p34*/
  {PART_TRUSTFIRMWARE_A,  836*1024,  2*1024,        UFS_PART_3},/* trustfirmware   2M     p35*/
  {PART_MODEM_FW_A,       838*1024,  56*1024,       UFS_PART_3},/* modem_fw        56M    p36*/
  {PART_RESERVED4_A,      894*1024,  50*1024,       UFS_PART_3},/* reserved4A      50M    p37*/
  {PART_MODEMNVM_UPDATE_A,944*1024,  80*1024,       UFS_PART_3},/* modemnvm update 80M    p38*/
  {PART_PATCH_A,          1024*1024,  32*1024,       UFS_PART_3},/* patch           32M    p39*/
  {PART_VERSION_A,        1056*1024,  32*1024,        UFS_PART_3},/* version        24M     p40*/
  {PART_VENDOR_A,         1088*1024,  784*1024,      UFS_PART_3},/* vendor          784M   p41*/
  {PART_PRODUCT_A,        1872*1024, 192*1024,      UFS_PART_3},/* product         192M   p42*/
  {PART_CUST_A,           2064*1024, 192*1024,      UFS_PART_3},/* cust            192M   p43*/
  #ifdef CONFIG_MARKET_INTERNAL
  {PART_SYSTEM_A,         2256*1024, 3552*1024,     UFS_PART_3},/* system          3552M  p44*/
  {PART_RESERVED5,        5808*1024, 128*1024,       UFS_PART_3},/* reserved5       64M    p45*/
  {PART_USERDATA,         5936*1024, (4UL)*1024*1024,UFS_PART_3},/* userdata       4G     p46*/
  #else
  {PART_SYSTEM_A,         2256*1024, 4688*1024,     UFS_PART_3},/* system          4688M  p44*/
  {PART_RESERVED5,        6944*1024, 128*1024,       UFS_PART_3},/* reserved5       64M    p45*/
  {PART_USERDATA,         7072*1024, (4UL)*1024*1024,UFS_PART_3},/* userdata       4G     p46*/
  #endif
  {"0", 0, 0, 0},
};
#endif

#elif defined CONFIG_HISI_PARTITION_KIRIN970
static const struct partition partition_table_emmc[] =
{
  {PART_XLOADER_A,        0,         2*1024,        EMMC_BOOT_MAJOR_PART},
  {PART_XLOADER_B,        0,         2*1024,        EMMC_BOOT_BACKUP_PART},
  {PART_PTABLE,           0,         512,           EMMC_USER_PART},/* ptable          512K */
  {PART_FRP,              512,       512,           EMMC_USER_PART},/* frp             512K   p1*/
  {PART_PERSIST,          1024,      2048,          EMMC_USER_PART},/* persist         2048K  p2*/
  {PART_RESERVED1,        3072,      5120,          EMMC_USER_PART},/* reserved1       5120K  p3*/
  {PART_RESERVED6,        8*1024,    512,           EMMC_USER_PART},/* reserved6       512K   p4*/
  {PART_VRL,              8704,      512,           EMMC_USER_PART},/* vrl             512K   p5*/
  {PART_VRL_BACKUP,       9216,      512,           EMMC_USER_PART},/* vrl backup      512K   p6*/
  {PART_MODEM_SECURE,     9728,      8704,          EMMC_USER_PART},/* modem_secure    8704k  p7*/
  {PART_NVME,             18*1024,   6*1024,        EMMC_USER_PART},/* nvme            6M     p8*/
  {PART_OEMINFO,          24*1024,   64*1024,       EMMC_USER_PART},/* oeminfo         64M    p9*/
  {PART_SECURE_STORAGE,   88*1024,   32*1024,       EMMC_USER_PART},/* secure storage  32M    p10*/
  {PART_MODEM_OM,         120*1024,  32*1024,       EMMC_USER_PART},/* modem om        32M    p11*/
  {PART_MODEMNVM_FACTORY, 152*1024,  4*1024,        EMMC_USER_PART},/* modemnvm factory4M     p12*/
  {PART_MODEMNVM_BACKUP,  156*1024,  4*1024,        EMMC_USER_PART},/* modemnvm backup 4M     p13*/
  {PART_MODEMNVM_IMG,     160*1024,  12*1024,       EMMC_USER_PART},/* modemnvm img    12M    p14*/
  {PART_MODEMNVM_SYSTEM,  172*1024,  4*1024,        EMMC_USER_PART},/* modemnvm system 4M     p15*/
  {PART_SPLASH2,          176*1024,  80*1024,       EMMC_USER_PART},/* splash2         80M    p16*/
  {PART_CACHE,            256*1024,  8*1024,        EMMC_USER_PART},/* cache           8M     p17*/
  {PART_BOOTFAIL_INFO,    264*1024,  2*1024,        EMMC_USER_PART},/* bootfail info   2MB    p18*/
  {PART_MISC,             266*1024,  2*1024,        EMMC_USER_PART},/* misc            2M     p19*/
  {PART_PATCH,            268*1024,  32*1024,       EMMC_USER_PART},/* patch           32M    p20*/
  {PART_HISEE_IMG,        300*1024,  4*1024,        EMMC_USER_PART},/* hisee_img       4M     p21*/
  {PART_HISEE_FS,         304*1024,  8*1024,        EMMC_USER_PART},/* hisee_fs        8M     p22*/
  {PART_DFX,              312*1024,  16*1024,       EMMC_USER_PART},/* dfx             16M    p23*/
  {PART_RRECORD,          328*1024,  16*1024,       EMMC_USER_PART},/* rrecord         16M    p24*/
  {PART_FW_LPM3_A,        344*1024,  256,           EMMC_USER_PART},/* mcuimage        256K   p25*/
  {PART_RESERVED3_A,      352512,    7936,          EMMC_USER_PART},/* reserved3A      7936KB p26*/
  {PART_FASTBOOT_A,       352*1024,  12*1024,       EMMC_USER_PART},/* fastboot        12M    p27*/
  {PART_VECTOR_A,         364*1024,  4*1024,        EMMC_USER_PART},/* avs vector      4M     p28*/
  {PART_ISP_BOOT_A,       368*1024,  2*1024,        EMMC_USER_PART},/* isp_boot        2M     p29*/
  {PART_ISP_FIRMWARE_A,   370*1024,  14*1024,       EMMC_USER_PART},/* isp_firmware    14M    p30*/
  {PART_FW_HIFI_A,        384*1024,  12*1024,       EMMC_USER_PART},/* hifi            12M    p31*/
  {PART_TEEOS_A,          396*1024,  8*1024,        EMMC_USER_PART},/* teeos           8M     p32*/
  {PART_RECOVERY2_A,      404*1024,  64*1024,       EMMC_USER_PART},/* recovery2       64M    p33*/
  {PART_SENSORHUB_A,      468*1024,  16*1024,       EMMC_USER_PART},/* sensorhub       16M    p34*/
  {PART_BOOT_A,           484*1024,  32*1024,       EMMC_USER_PART},/* boot            32M    p35*/
  {PART_RECOVERY_A,       516*1024,  64*1024,       EMMC_USER_PART},/* recovery        64M    p36*/
  {PART_DTS_A,            580*1024,  16*1024,       EMMC_USER_PART},/* dtimage         16M    p37*/
  {PART_TRUSTFIRMWARE_A,  596*1024,  2*1024,        EMMC_USER_PART},/* trustfirmware   2M     p38*/
  {PART_MODEM_FW_A,       598*1024,  56*1024,       EMMC_USER_PART},/* modem_fw        56M    p39*/
  {PART_RESERVED4_A,      654*1024,  50*1024,       EMMC_USER_PART},/* reserved4A      50M    p40*/
  {PART_MODEMNVM_UPDATE_A,704*1024,  80*1024,       EMMC_USER_PART},/* modemnvm update 80M    p41*/
  {PART_ISP_DTS_A,        784*1024,  16*1024,       EMMC_USER_PART},/* isp_dts         16M    p42*/
  {PART_VERSION_A,        800*1024,  8*1024,        EMMC_USER_PART},/* version         8M     p43*/
  {PART_VENDOR_A,         808*1024,  352*1024,      EMMC_USER_PART},/* vendor          352M   p44*/
  {PART_PRODUCT_A,        1160*1024, 120*1024,      EMMC_USER_PART},/* product         120M   p45*/
  {PART_CUST_A,           1280*1024, 128*1024,      EMMC_USER_PART},/* cust            128M   p46*/
  #ifdef CONFIG_MARKET_INTERNAL
  {PART_SYSTEM_A,         1408*1024, 1848*1024,     EMMC_USER_PART},/* system          1848M  p47*/
  {PART_FW_LPM3_B,        3256*1024, 256,           EMMC_USER_PART},/* mcuimage        256K   p48*/
  {PART_RESERVED3_B,      3334400,   7936,          EMMC_USER_PART},/* reserved3A      7936KB p49*/
  {PART_FASTBOOT_B,       3264*1024, 12*1024,       EMMC_USER_PART},/* fastboot        12M    p50*/
  {PART_VECTOR_B,         3276*1024, 4*1024,        EMMC_USER_PART},/* avs vector      4M     p51*/
  {PART_ISP_BOOT_B,       3280*1024, 2*1024,        EMMC_USER_PART},/* isp_boot        2M     p52*/
  {PART_ISP_FIRMWARE_B,   3282*1024, 14*1024,       EMMC_USER_PART},/* isp_firmware    14M    p53*/
  {PART_FW_HIFI_B,        3296*1024, 12*1024,       EMMC_USER_PART},/* hifi            12M    p54*/
  {PART_TEEOS_B,          3308*1024, 8*1024,        EMMC_USER_PART},/* teeos           8M     p55*/
  {PART_RECOVERY2_B,      3316*1024, 64*1024,       EMMC_USER_PART},/* recovery2       64M    p56*/
  {PART_SENSORHUB_B,      3380*1024, 16*1024,       EMMC_USER_PART},/* sensorhub       16M    p57*/
  {PART_BOOT_B,           3396*1024, 32*1024,       EMMC_USER_PART},/* boot            32M    p58*/
  {PART_RECOVERY_B,       3428*1024, 64*1024,       EMMC_USER_PART},/* recovery        64M    p59*/
  {PART_DTS_B,            3492*1024, 16*1024,       EMMC_USER_PART},/* dtimage         16M    p60*/
  {PART_TRUSTFIRMWARE_B,  3508*1024, 2*1024,        EMMC_USER_PART},/* trustfirmware   2M     p61*/
  {PART_MODEM_FW_B,       3510*1024, 56*1024,       EMMC_USER_PART},/* modem_fw        56M    p62*/
  {PART_RESERVED4_B,      3566*1024, 50*1024,       EMMC_USER_PART},/* reserved4B      50M    p63*/
  {PART_MODEMNVM_UPDATE_B,3616*1024, 80*1024,       EMMC_USER_PART},/* modemnvm update 80M    p64*/
  {PART_ISP_DTS_B,        3696*1024, 16*1024,       EMMC_USER_PART},/* isp_dts         16M    p65*/
  {PART_VERSION_B,        3712*1024, 8*1024,        EMMC_USER_PART},/* version         8M     p66*/
  {PART_VENDOR_B,         3720*1024, 352*1024,      EMMC_USER_PART},/* vendor          352M   p67*/
  {PART_PRODUCT_B,        4072*1024, 120*1024,      EMMC_USER_PART},/* product         120M   p68*/
  {PART_CUST_B,           4192*1024, 128*1024,      EMMC_USER_PART},/* cust            128M   p69*/
  {PART_SYSTEM_B,         4320*1024, 1848*1024,     EMMC_USER_PART},/* system          1848M  p70*/
  {PART_RESERVED5,        6168*1024, 64*1024,       EMMC_USER_PART},/* reserved5       64M    p71*/
  {PART_USERDATA,         6232*1024, (4UL)*1024*1024,EMMC_USER_PART},/* userdata       4G     p72*/
  #else
  {PART_SYSTEM_A,         1408*1024, 2640*1024,     EMMC_USER_PART},/* system          2640M  p47*/
  {PART_FW_LPM3_B,        4048*1024, 256,           EMMC_USER_PART},/* mcuimage        256K   p48*/
  {PART_RESERVED3_B,      4145408,   7936,          EMMC_USER_PART},/* reserved3A      7936KB p49*/
  {PART_FASTBOOT_B,       4056*1024, 12*1024,       EMMC_USER_PART},/* fastboot        12M    p50*/
  {PART_VECTOR_B,         4068*1024, 4*1024,        EMMC_USER_PART},/* avs vector      4M     p51*/
  {PART_ISP_BOOT_B,       4072*1024, 2*1024,        EMMC_USER_PART},/* isp_boot        2M     p52*/
  {PART_ISP_FIRMWARE_B,   4074*1024, 14*1024,       EMMC_USER_PART},/* isp_firmware    14M    p53*/
  {PART_FW_HIFI_B,        4088*1024, 12*1024,       EMMC_USER_PART},/* hifi            12M    p54*/
  {PART_TEEOS_B,          4100*1024, 8*1024,        EMMC_USER_PART},/* teeos           8M     p55*/
  {PART_RECOVERY2_B,      4108*1024, 64*1024,       EMMC_USER_PART},/* recovery2       64M    p56*/
  {PART_SENSORHUB_B,      4172*1024, 16*1024,       EMMC_USER_PART},/* sensorhub       16M    p57*/
  {PART_BOOT_B,           4188*1024, 32*1024,       EMMC_USER_PART},/* boot            32M    p58*/
  {PART_RECOVERY_B,       4220*1024, 64*1024,       EMMC_USER_PART},/* recovery        64M    p59*/
  {PART_DTS_B,            4284*1024, 16*1024,       EMMC_USER_PART},/* dtimage         16M    p60*/
  {PART_TRUSTFIRMWARE_B,  4300*1024, 2*1024,        EMMC_USER_PART},/* trustfirmware   2M     p61*/
  {PART_MODEM_FW_B,       4302*1024, 56*1024,       EMMC_USER_PART},/* modem_fw        56M    p62*/
  {PART_RESERVED4_B,      4358*1024, 50*1024,       EMMC_USER_PART},/* reserved4B      50M    p63*/
  {PART_MODEMNVM_UPDATE_B,4408*1024, 80*1024,       EMMC_USER_PART},/* modemnvm update 80M    p64*/
  {PART_ISP_DTS_B,        4488*1024, 16*1024,       EMMC_USER_PART},/* isp_dts         16M    p65*/
  {PART_VERSION_B,        4504*1024, 8*1024,        EMMC_USER_PART},/* version         8M     p66*/
  {PART_VENDOR_B,         4512*1024, 352*1024,      EMMC_USER_PART},/* vendor          352M   p67*/
  {PART_PRODUCT_B,        4864*1024, 120*1024,      EMMC_USER_PART},/* product         120M   p68*/
  {PART_CUST_B,           4984*1024, 128*1024,      EMMC_USER_PART},/* cust            128M   p69*/
  {PART_SYSTEM_B,         5112*1024, 2640*1024,     EMMC_USER_PART},/* system          2640M  p70*/
  {PART_RESERVED5,        7752*1024, 64*1024,       EMMC_USER_PART},/* reserved5       64M    p71*/
  {PART_USERDATA,         7816*1024, (4UL)*1024*1024,EMMC_USER_PART},/* userdata       4G     p72*/
  #endif
  {"0", 0, 0, 0},                                        /* total 11848M*/
};
#ifdef CONFIG_HISI_STORAGE_UFS_PARTITION
static const struct partition partition_table_ufs[] =
{
  {PART_XLOADER_A,        0,         2*1024,        UFS_PART_0},
  {PART_XLOADER_B,        0,         2*1024,        UFS_PART_1},
  {PART_PTABLE,           0,         512,           UFS_PART_2},/* ptable          512K */
  {PART_FRP,              512,       512,           UFS_PART_2},/* frp             512K   p1*/
  {PART_PERSIST,          1024,      2048,          UFS_PART_2},/* persist         2048K  p2*/
  {PART_RESERVED1,        3072,      5120,          UFS_PART_2},/* reserved1       5120K  p3*/
  {PART_PTABLE_LU3,       0,         512,           UFS_PART_3},/* ptable_lu3      512K   p0*/
  {PART_VRL,              512,       512,           UFS_PART_3},/* vrl             512K   p1*/
  {PART_VRL_BACKUP,       1024,      512,           UFS_PART_3},/* vrl backup      512K   p2*/
  {PART_MODEM_SECURE,     1536,      8704,          UFS_PART_3},/* modem_secure    8704k  p3*/
  {PART_NVME,             10*1024,   6*1024,        UFS_PART_3},/* nvme            6M     p4*/
  {PART_OEMINFO,          16*1024,   64*1024,       UFS_PART_3},/* oeminfo         64M    p5*/
  {PART_SECURE_STORAGE,   80*1024,   32*1024,       UFS_PART_3},/* secure storage  32M    p6*/
  {PART_MODEM_OM,         112*1024,  32*1024,       UFS_PART_3},/* modem om        32M    p7*/
  {PART_MODEMNVM_FACTORY, 144*1024,  4*1024,        UFS_PART_3},/* modemnvm factory4M     p8*/
  {PART_MODEMNVM_BACKUP,  148*1024,  4*1024,        UFS_PART_3},/* modemnvm backup 4M     p9*/
  {PART_MODEMNVM_IMG,     152*1024,  12*1024,       UFS_PART_3},/* modemnvm img    12M    p10*/
  {PART_MODEMNVM_SYSTEM,  164*1024,  4*1024,        UFS_PART_3},/* modemnvm system 4M     p11*/
  {PART_SPLASH2,          168*1024,  80*1024,       UFS_PART_3},/* splash2         80M    p12*/
  {PART_CACHE,            248*1024,  8*1024,        UFS_PART_3},/* cache           8M     p13*/
  {PART_BOOTFAIL_INFO,    256*1024,  2*1024,        UFS_PART_3},/* bootfail info   2MB    p14*/
  {PART_MISC,             258*1024,  2*1024,        UFS_PART_3},/* misc            2M     p15*/
  {PART_PATCH,            260*1024,  32*1024,       UFS_PART_3},/* patch           32M    p16*/
  {PART_HISEE_IMG,        292*1024,  4*1024,        UFS_PART_3},/* hisee_img       4M     p17*/
  {PART_HISEE_FS,         296*1024,  8*1024,        UFS_PART_3},/* hisee_fs        8M     p18*/
  {PART_DFX,              304*1024,  16*1024,       UFS_PART_3},/* dfx             16M    p19*/
  {PART_RRECORD,          320*1024,  16*1024,       UFS_PART_3},/* rrecord         16M    p20*/
  {PART_FW_LPM3_A,        336*1024,  256,           UFS_PART_3},/* mcuimage        256K   p21*/
  {PART_RESERVED3_A,      344320,    7936,          UFS_PART_3},/* reserved3A      7936KB p22*/
  {PART_FASTBOOT_A,       344*1024,  12*1024,       UFS_PART_3},/* fastboot        12M    p23*/
  {PART_VECTOR_A,         356*1024,  4*1024,        UFS_PART_3},/* avs vector      4M     p24*/
  {PART_ISP_BOOT_A,       360*1024,  2*1024,        UFS_PART_3},/* isp_boot        2M     p25*/
  {PART_ISP_FIRMWARE_A,   362*1024,  14*1024,       UFS_PART_3},/* isp_firmware    14M    p26*/
  {PART_FW_HIFI_A,        376*1024,  12*1024,       UFS_PART_3},/* hifi            12M    p27*/
  {PART_TEEOS_A,          388*1024,  8*1024,        UFS_PART_3},/* teeos           8M     p28*/
  {PART_RECOVERY2_A,      396*1024,  64*1024,       UFS_PART_3},/* recovery2       64M    p29*/
  {PART_SENSORHUB_A,      460*1024,  16*1024,       UFS_PART_3},/* sensorhub       16M    p30*/
  {PART_BOOT_A,           476*1024,  32*1024,       UFS_PART_3},/* boot            32M    p31*/
  {PART_RECOVERY_A,       508*1024,  64*1024,       UFS_PART_3},/* recovery        64M    p32*/
  {PART_DTS_A,            572*1024,  16*1024,       UFS_PART_3},/* dtimage         16M    p33*/
  {PART_TRUSTFIRMWARE_A,  588*1024,  2*1024,        UFS_PART_3},/* trustfirmware   2M     p34*/
  {PART_MODEM_FW_A,       590*1024,  56*1024,       UFS_PART_3},/* modem_fw        56M    p35*/
  {PART_RESERVED4_A,      646*1024,  50*1024,       UFS_PART_3},/* reserved4A      50M    p36*/
  {PART_MODEMNVM_UPDATE_A,696*1024,  80*1024,       UFS_PART_3},/* modemnvm update 80M    p37*/
  {PART_ISP_DTS_A,        776*1024,  16*1024,       UFS_PART_3},/* isp_dts         16M    p38*/
  {PART_VERSION_A,        792*1024,  8*1024,        UFS_PART_3},/* version         8M     p39*/
  {PART_VENDOR_A,         800*1024,  352*1024,      UFS_PART_3},/* vendor          352M   p40*/
  {PART_PRODUCT_A,        1152*1024, 120*1024,      UFS_PART_3},/* product         120M   p41*/
  {PART_CUST_A,           1272*1024, 128*1024,      UFS_PART_3},/* cust            128M   p42*/
  #ifdef CONFIG_MARKET_INTERNAL
  {PART_SYSTEM_A,         1400*1024, 1848*1024,     UFS_PART_3},/* system          1848M  p43*/
  {PART_FW_LPM3_B,        3248*1024, 256,           UFS_PART_3},/* mcuimage        256K   p44*/
  {PART_RESERVED3_B,      3326208,   7936,          UFS_PART_3},/* reserved3A      7936KB p45*/
  {PART_FASTBOOT_B,       3256*1024, 12*1024,       UFS_PART_3},/* fastboot        12M    p46*/
  {PART_VECTOR_B,         3268*1024, 4*1024,        UFS_PART_3},/* avs vector      4M     p47*/
  {PART_ISP_BOOT_B,       3272*1024, 2*1024,        UFS_PART_3},/* isp_boot        2M     p48*/
  {PART_ISP_FIRMWARE_B,   3274*1024, 14*1024,       UFS_PART_3},/* isp_firmware    14M    p49*/
  {PART_FW_HIFI_B,        3288*1024, 12*1024,       UFS_PART_3},/* hifi            12M    p50*/
  {PART_TEEOS_B,          3300*1024, 8*1024,        UFS_PART_3},/* teeos           8M     p51*/
  {PART_RECOVERY2_B,      3308*1024, 64*1024,       UFS_PART_3},/* recovery2       64M    p52*/
  {PART_SENSORHUB_B,      3372*1024, 16*1024,       UFS_PART_3},/* sensorhub       16M    p53*/
  {PART_BOOT_B,           3388*1024, 32*1024,       UFS_PART_3},/* boot            32M    p54*/
  {PART_RECOVERY_B,       3420*1024, 64*1024,       UFS_PART_3},/* recovery        64M    p55*/
  {PART_DTS_B,            3484*1024, 16*1024,       UFS_PART_3},/* dtimage         16M    p56*/
  {PART_TRUSTFIRMWARE_B,  3500*1024, 2*1024,        UFS_PART_3},/* trustfirmware   2M     p57*/
  {PART_MODEM_FW_B,       3502*1024, 56*1024,       UFS_PART_3},/* modem_fw        56M    p58*/
  {PART_RESERVED4_B,      3558*1024, 50*1024,       UFS_PART_3},/* reserved4B      50M    p59*/
  {PART_MODEMNVM_UPDATE_B,3608*1024, 80*1024,       UFS_PART_3},/* modemnvm update 80M    p60*/
  {PART_ISP_DTS_B,        3688*1024, 16*1024,       UFS_PART_3},/* isp_dts         16M    p61*/
  {PART_VERSION_B,        3704*1024, 8*1024,        UFS_PART_3},/* version         8M     p62*/
  {PART_VENDOR_B,         3712*1024, 352*1024,      UFS_PART_3},/* vendor          352M   p63*/
  {PART_PRODUCT_B,        4064*1024, 120*1024,      UFS_PART_3},/* product         120M   p64*/
  {PART_CUST_B,           4184*1024, 128*1024,      UFS_PART_3},/* cust            128M   p65*/
  {PART_SYSTEM_B,         4312*1024, 1848*1024,     UFS_PART_3},/* system          2640M  p66*/
  {PART_RESERVED5,        6160*1024, 64*1024,       UFS_PART_3},/* reserved5       64M    p67*/
  {PART_USERDATA,         6224*1024, (4UL)*1024*1024,UFS_PART_3},/* userdata       4G     p68*/
  #else //default or CONFIG_MARKET_OVERSEA
  {PART_SYSTEM_A,         1400*1024, 2640*1024,     UFS_PART_3},/* system          2640M  p43*/
  {PART_FW_LPM3_B,        4040*1024, 256,           UFS_PART_3},/* mcuimage        256K   p44*/
  {PART_RESERVED3_B,      4137216,   7936,          UFS_PART_3},/* reserved3A      7936KB p45*/
  {PART_FASTBOOT_B,       4048*1024, 12*1024,       UFS_PART_3},/* fastboot        12M    p46*/
  {PART_VECTOR_B,         4060*1024, 4*1024,        UFS_PART_3},/* avs vector      4M     p47*/
  {PART_ISP_BOOT_B,       4064*1024, 2*1024,        UFS_PART_3},/* isp_boot        2M     p48*/
  {PART_ISP_FIRMWARE_B,   4066*1024, 14*1024,       UFS_PART_3},/* isp_firmware    14M    p49*/
  {PART_FW_HIFI_B,        4080*1024, 12*1024,       UFS_PART_3},/* hifi            12M    p50*/
  {PART_TEEOS_B,          4092*1024, 8*1024,        UFS_PART_3},/* teeos           8M     p51*/
  {PART_RECOVERY2_B,      4100*1024, 64*1024,       UFS_PART_3},/* recovery2       64M    p52*/
  {PART_SENSORHUB_B,      4164*1024, 16*1024,       UFS_PART_3},/* sensorhub       16M    p53*/
  {PART_BOOT_B,           4180*1024, 32*1024,       UFS_PART_3},/* boot            32M    p54*/
  {PART_RECOVERY_B,       4212*1024, 64*1024,       UFS_PART_3},/* recovery        64M    p55*/
  {PART_DTS_B,            4276*1024, 16*1024,       UFS_PART_3},/* dtimage         16M    p56*/
  {PART_TRUSTFIRMWARE_B,  4292*1024, 2*1024,        UFS_PART_3},/* trustfirmware   2M     p57*/
  {PART_MODEM_FW_B,       4294*1024, 56*1024,       UFS_PART_3},/* modem_fw        56M    p58*/
  {PART_RESERVED4_B,      4350*1024, 50*1024,       UFS_PART_3},/* reserved4B      50M    p59*/
  {PART_MODEMNVM_UPDATE_B,4400*1024, 80*1024,       UFS_PART_3},/* modemnvm update 80M    p60*/
  {PART_ISP_DTS_B,        4480*1024, 16*1024,       UFS_PART_3},/* isp_dts         16M    p61*/
  {PART_VERSION_B,        4496*1024, 8*1024,        UFS_PART_3},/* version         8M     p62*/
  {PART_VENDOR_B,         4504*1024, 352*1024,      UFS_PART_3},/* vendor          352M   p63*/
  {PART_PRODUCT_B,        4856*1024, 120*1024,      UFS_PART_3},/* product         120M   p64*/
  {PART_CUST_B,           4976*1024, 128*1024,      UFS_PART_3},/* cust            128M   p65*/
  {PART_SYSTEM_B,         5104*1024, 2640*1024,     UFS_PART_3},/* system          2640M  p66*/
  {PART_RESERVED5,        7744*1024, 64*1024,       UFS_PART_3},/* reserved5       64M    p67*/
  {PART_USERDATA,         7808*1024, (4UL)*1024*1024,UFS_PART_3},/* userdata       4G     p68*/
  #endif
  {"0", 0, 0, 0},
};
#endif

#endif

#endif


