#ifndef __BSP_TSENSOR_H__
#define __BSP_TSENSOR_H__

#include <product_config.h>
#include <osl_types.h>
/*tsensor精度提升倍率*/
#define TSENSOR_PRECISION (1024)
enum temp_type{
    en_temp_high,
    en_temp_low,
};
typedef void (*pTFUNCPTR)(enum temp_type);

#if defined(CONFIG_TSENSOR_V610)
int bsp_tsensor_init(void);                     /* for C core and M3 core */
enum temp_type bsp_tsensor_temptype_get(void);  /* for C core */
s32 bsp_tsensor_callback_regist(pTFUNCPTR p);   /* for C core */
void bsp_tsensor_enable(void);                  /* for M3 core */
void bsp_tsensor_disable(void);                 /* for M3 core */

#elif defined(CONFIG_TSENSOR_V560)
int bsp_tsensor_tem_get(void);                  /* for M3 core */
void bsp_tsensor_enable(void);                  /* for M3 core */
void bsp_tsensor_disable(void);                 /* for M3 core */
#if defined(__CMSIS_RTOS)
int bsp_tsensor_init(void);                     /* for M3 core */
#else
static inline int bsp_tsensor_init(void){}                    /* for C core */
#endif

#else   /* stub */
static inline enum temp_type bsp_tsensor_temptype_get(void){ return en_temp_low; }    /* for C core */
static inline s32 bsp_tsensor_callback_regist(pTFUNCPTR p){ return 0; }               /* for C core */
static inline void bsp_tsensor_enable(void){}                 /* for M3 core */
static inline void bsp_tsensor_disable(void){}                /* for M3 core */
static inline int bsp_tsensor_init(void){return 0;}           /* for C core and M3 core */

#endif  /* #if defined(TSENSOR_V610) */
#endif  /* #ifdef __BSP_TSENSOR_H__  */

