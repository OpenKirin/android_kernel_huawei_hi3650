#ifndef __SOC_MEMMAP_MDM_H__
#define __SOC_MEMMAP_MDM_H__ 
#ifdef __cplusplus
extern "C" {
#endif
#include "soc_memmap_comm.h"
#define HI_TIMER_00TO07_REGBASE_ADDR (0xE0202000)
#define HI_TIMER_00TO07_REG_SIZE (SZ_4K)
#define HI_TIMER_04_REGBASE_ADDR (HI_TIMER_00TO07_REGBASE_ADDR+0x50)
#ifdef __cplusplus
}
#endif
#endif
