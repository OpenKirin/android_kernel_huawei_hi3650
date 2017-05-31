/*************************************************************************
*   ��Ȩ����(C) 1987-2011, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  DrvInterface.h
*
*   ��    �� :  yangzhi
*
*   ��    �� :  ���ļ�����Ϊ"DrvInterface.h", ����V7R1�����Э��ջ֮���API�ӿ�ͳ��
*
*   �޸ļ�¼ :  2011��1��18��  v1.00  yangzhi����
*************************************************************************/

#ifndef __DRV_COMM_H__
#define __DRV_COMM_H__



/*************************GLOBAL BEGIN*****************************/
/* �����������Ͷ��� */
#ifndef _WIN32_COMPILE
typedef signed long long    BSP_S64;
#else
typedef double              BSP_S64;
#endif
typedef signed int          BSP_S32;
typedef signed short        BSP_S16;
typedef signed char         BSP_S8;
typedef char                BSP_CHAR;
typedef char                BSP_CHAR_TL;

#ifndef _WIN32_COMPILE
typedef unsigned long long  BSP_U64;
#else
typedef double              BSP_U64;
#endif
typedef unsigned int        BSP_U32;
typedef unsigned short      BSP_U16;
typedef unsigned char       BSP_U8;

typedef int                 BSP_BOOL;
typedef void                BSP_VOID;
typedef int                 BSP_STATUS;

#ifndef _WIN32_COMPILE
typedef signed long long*   BSP_PS64;
#else
typedef double*             BSP_PS64;
#endif
typedef signed int*         BSP_PS32;
typedef signed short*       BSP_PS16;
typedef signed char*        BSP_PS8;

#ifndef _WIN32_COMPILE
typedef unsigned long long* BSP_PU64;
#else
typedef double*             BSP_PU64;
#endif
typedef unsigned int*       BSP_PU32;
typedef unsigned short*     BSP_PU16;
typedef unsigned char*      BSP_PU8;

#ifndef UINT8
typedef unsigned char       UINT8;
#endif
#ifndef UINT32
typedef unsigned int        UINT32;
#endif
typedef int*                BSP_PBOOL;
typedef void*               BSP_PVOID;
typedef int*                BSP_PSTATUS;

typedef void                VOID;
typedef BSP_S32             STATUS;
typedef BSP_S32             UDI_HANDLE;

#ifndef BSP_CONST
#define BSP_CONST           const
#endif

#ifndef OK
#define OK                  (0)
#endif

#ifndef ERROR
#define ERROR               (-1)
#endif

#ifndef TRUE
#define TRUE                (1)
#endif

#ifndef FALSE
#define FALSE               (0)
#endif

#ifndef BSP_OK
#define BSP_OK              (0)
#endif

#ifndef BSP_ERROR
#define BSP_ERROR           (-1)
#endif

#ifndef BSP_TRUE
#define BSP_TRUE            (1)
#endif

#ifndef BSP_FALSE
#define BSP_FALSE           (0)
#endif

#ifndef BSP_NULL
#define BSP_NULL            (void*)0
#endif

typedef BSP_S32 (*FUNCPTR_1)(int);
typedef int (*PWRCTRLFUNCPTRVOID)(void);
typedef unsigned int (*PWRCTRLFUNCPTR)(unsigned int arg);     /* ptr to function returning int */

#ifndef INLINE
#ifdef __KERNEL__
#define INLINE              inline
#else
#define INLINE              __inline__
#endif
#endif

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM)
#ifndef _VOIDFUNCPTR_DEFINED
typedef BSP_VOID (*VOIDFUNCPTR)();
#endif
#else
typedef BSP_VOID (*VOIDFUNCPTR)(BSP_U32);
#define SEM_FULL            (1)
#define SEM_EMPTY           (0)
#define LOCAL                   static
#define IVEC_TO_INUM(intVec)    ((int)(intVec))
#endif


/* ������궨�� */
#define BSP_ERR_MODULE_OFFSET (0x1000)    /* ��ֹ��ϵͳ�Ĵ������ص� */
#define BSP_DEF_ERR( mod, errid) \
    ((((BSP_U32) mod + BSP_ERR_MODULE_OFFSET) << 16) | (errid))

#define BSP_REG(base, reg) (*(volatile BSP_U32 *)((BSP_U32)base + (reg)))

#if defined(BSP_CORE_MODEM) || defined(PRODUCT_CFG_CORE_TYPE_MODEM) || defined(__VXWORKS__)
#define BSP_REG_READ(base, reg, result) \
    ((result) = BSP_REG(base, reg))

#define BSP_REG_WRITE(base, reg, data) \
    (BSP_REG(base, reg) = (data))

#else
#define BSP_REG_READ(base, reg, resule) \
    (resule = readl(base + reg))

#define BSP_REG_WRITE(base, reg, data) \
    (writel(data, (base + reg)))
#endif

#define BSP_REG_SETBITS(base, reg, pos, bits, val) (BSP_REG(base, reg) = (BSP_REG(base, reg) & (~((((u32)1 << (bits)) - 1) << (pos)))) \
                                                                         | ((u32)((val) & (((u32)1 << (bits)) - 1)) << (pos)))
#define BSP_REG_GETBITS(base, reg, pos, bits) ((BSP_REG(base, reg) >> (pos)) & (((u32)1 << (bits)) - 1))



/*****************************************************************************
  1 GU����������ӿڣ�GUPorting��Ŀ���.
*****************************************************************************/

/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define DRV_OK                          (0)
#define DRV_ERROR                       (-1)
#define DRV_INTERFACE_RSLT_OK           (0)

/* �����������Ͷ��� */

typedef int  (*pFUNCPTR)(void);

typedef unsigned long (*pFUNCPTR2)( unsigned long ulPara1, unsigned long ulPara2);

typedef unsigned int tagUDI_DEVICE_ID_UINT32;

/*��Ҫ�Ƶ����ͷ�ļ��� start*/
/*����Flash��Ϣ*/
typedef struct
{
    BSP_U32 ulblockCount;    /*Block����*/
    BSP_U32 ulpageSize;    /*pageҳ��С*/
    BSP_U32 ulpgCntPerBlk;    /*һ��Block�е�page����*/
}DLOAD_FLASH_STRU;
/*��Ҫ�Ƶ����ͷ�ļ��� end*/

/* ������·�հ�����ָ�� */
typedef BSP_VOID (*UpLinkRxFunc)(BSP_U8 *buf, BSP_U32 len);

/* ����װ�ͷź���ָ�� */
typedef BSP_VOID (*FreePktEncap)(BSP_VOID *PktEncap);

/* GMAC������ö�� */
typedef enum tagGMAC_OWNER_E
{
    GMAC_OWNER_VXWORKS = 0, /* Vxworks����Э��ջ */
    GMAC_OWNER_PS,          /* LTE����Э��ջ */
    GMAC_OWNER_MSP,         /* MSP */
    GMAC_OWNER_MAX          /* �߽�ֵ */
}GMAC_OWNER_E;

typedef enum tagWDT_TIMEOUT_E
{
    WDT_TIMEOUT_1   = 0,        /*0xFFFF000/WDT_CLK_FREQ,  about 3657ms*/      /*WDT_CLK_FREQ = ARM_FREQ/6 = 70M*/
    WDT_TIMEOUT_2,              /*0x1FFFE000/WDT_CLK_FREQ, about 7314ms*/
    WDT_TIMEOUT_3,              /*0x3FFFC000/WDT_CLK_FREQ, about 14628ms*/
    WDT_TIMEOUT_4,              /*0x7FFF8000/WDT_CLK_FREQ, about 29257ms*/
    WDT_TIMEOUT_BUTT
}WDT_TIMEOUT_E;

/*************************GLOBAL END****************************/

#endif

