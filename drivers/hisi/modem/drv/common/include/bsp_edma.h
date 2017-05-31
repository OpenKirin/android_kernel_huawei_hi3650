
#ifndef    _BSP_EDMA_H_
#define    _BSP_EDMA_H_

#include "soc_interrupts.h"
#include "osl_types.h"
#include "bsp_memmap.h"
#include "drv_edma_enum.h"
#include "mdrv_edma.h"
#include "bsp_om.h"
/*p531 ���� ʹ�� gu�ڲ��߼� edma ��vic*/
#ifdef  CONFIG_MODULE_VIC
#include "bsp_vic.h"
#endif

#define hiedmac_trace(level, fmt, ...)      (bsp_trace(level, BSP_MODU_EDMA, "[edma]:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))

#ifdef __KERNEL__

#include "drv_edma_enum.h"



/* ??void (*channel_isr)(BSP_U32 channel_arg, BSP_U32 int_status)???int_status?
    ??int balong_dma_channel_init (BALONG_DMA_REQ req,  channel_isr pFunc,
                     UINT32 channel_arg, UINT32 int_flag)???int_flag
    ?????????,???       */
#define BALONG_DMA_INT_DONE           1          /*DMA??????*/
#define BALONG_DMA_INT_LLT_DONE       2          /*??DMA????????*/
#define BALONG_DMA_INT_CONFIG_ERR     4          /*DMA?????????*/
#define BALONG_DMA_INT_TRANSFER_ERR   8          /*DMA?????????*/
#define BALONG_DMA_INT_READ_ERR       16         /*DMA??????????*/

/* EDMAC??????*/
#define BALONG_DMA_P2M      1
#define BALONG_DMA_M2P      2
#define BALONG_DMA_M2M      3

/* ???? */

#define   EDMA_CHN_FREE          1   /* ???? */
#define   EDMA_CHN_BUSY          0   /* ??? */


/* EDMA????,????????????? */
#define   EDMA_TRANS_WIDTH_8       0x0   /* 8bit??*/
#define   EDMA_TRANS_WIDTH_16      0x1   /* 16bit??*/
#define   EDMA_TRANS_WIDTH_32      0x2   /* 32bit??*/
#define   EDMA_TRANS_WIDTH_64      0x3   /* 64bit??*/

/*  EDMA burst length, ????0~15,???burst???1~16*/
#define   EDMA_BUR_LEN_1    0x0    /* burst??,?????????1?*/
#define   EDMA_BUR_LEN_2    0x1    /* burst??,?????????2?*/
#define   EDMA_BUR_LEN_3    0x2   /* burst??,?????????3?*/
#define   EDMA_BUR_LEN_4    0x3   /* burst??,?????????4?*/
#define   EDMA_BUR_LEN_5    0x4   /* burst??,?????????5?*/
#define   EDMA_BUR_LEN_6    0x5   /* burst??,?????????6?*/
#define   EDMA_BUR_LEN_7    0x6   /* burst??,?????????7?*/
#define   EDMA_BUR_LEN_8    0x7   /* burst??,?????????8?*/
#define   EDMA_BUR_LEN_9    0x8   /* burst??,?????????9?*/
#define   EDMA_BUR_LEN_10   0x9   /* burst??,?????????10?*/
#define   EDMA_BUR_LEN_11   0xa   /* burst??,?????????11?*/
#define   EDMA_BUR_LEN_12   0xb   /* burst??,?????????12?*/
#define   EDMA_BUR_LEN_13   0xc   /* burst??,?????????13?*/
#define   EDMA_BUR_LEN_14   0xd   /* burst??,?????????14?*/
#define   EDMA_BUR_LEN_15   0xe   /* burst??,?????????15?*/
#define   EDMA_BUR_LEN_16   0xf   /* burst??,?????????16?*/


/* EDMA ??????,?EDMA  ??????
       EDMAC_BASIC_CONFIG?BALONG_DMA_SET_LLI?BALONG_DMA_SET_CONFIG ??*/
/*config------Bit 31*/
#define EDMAC_TRANSFER_CONFIG_SOUR_INC      (0X80000000)
/*Bit 30*/
#define EDMAC_TRANSFER_CONFIG_DEST_INC      (0X40000000)
#define EDMAC_TRANSFER_CONFIG_BOTH_INC      (0XC0000000)

/*Bit 27-24*/
#define EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH_MASK     (0xF000000)
#define EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH( _len )  ((unsigned int)((_len)<<24))
/*Bit 23-20*/
#define EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH_MASK     (0xF00000)
#define EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH( _len )  ((unsigned int)((_len)<<20))

/*Bit18-16*/
#define EDMAC_TRANSFER_CONFIG_SOUR_WIDTH_MASK     (0x70000)
#define EDMAC_TRANSFER_CONFIG_SOUR_WIDTH( _len )  ((unsigned int)((_len)<<16))
/*Bit14-12*/
#define EDMAC_TRANSFER_CONFIG_DEST_WIDTH_MASK     (0x7000)
#define EDMAC_TRANSFER_CONFIG_DEST_WIDTH( _len )  ((unsigned int)((_len)<<12))

/*Bit9-4*/
#define EDMAC_TRANSFER_CONFIG_REQUEST( _ulReg )    ( (_ulReg ) << 4)
/*Bit3-2*/
#define EDMAC_TRANSFER_CONFIG_FLOW_DMAC( _len )    ((unsigned int)((_len)<<2))

#define EDMAC_TRANSFER_CONFIG_INT_TC_ENABLE            ( 0x2 )
#define EDMAC_TRANSFER_CONFIG_INT_TC_DISABLE           ( 0x0 )

#define EDMAC_TRANSFER_CONFIG_CHANNEL_ENABLE           ( 0x1 )
#define EDMAC_TRANSFER_CONFIG_CHANNEL_DISABLE          ( 0x0 )
#define EDMAC_NEXT_LLI_ENABLE       0x2           /* Bit 1 */
/*Bit 15*/
#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_A_SYNC     ( 0UL )
#define EDMAC_TRANSFER_CONFIG_EXIT_ADD_MODE_AB_SYNC    ( 0x00008000 )

#define P2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_DEST_INC)
#define M2P_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_PRF_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC)
#define M2M_CONFIG   (EDMAC_TRANSFER_CONFIG_FLOW_DMAC(MEM_MEM_DMA) | EDMAC_TRANSFER_CONFIG_SOUR_INC | EDMAC_TRANSFER_CONFIG_DEST_INC)

/******* old version BALONG_DMA_SET_LLI 
new name same as bsp. should bsp.h */
#define EDMAC_MAKE_LLI_ADDR( _p )   (u32)( (u32)(_p) & 0xFFFFFFE0 )

/*???????*/
/*�������������*/
enum edma_req_id
{
    EDMA_REQ_START = 0,
    EDMA_SPI0_RX = 0,
    EDMA_SPI0_TX,
    EDMA_SPI1_RX,
    EDMA_SPI1_TX,   /* Acore drv lcd ˢ��           ʵ�ʷ���ͨ�� edma ch16 - 14 */
    EDMA_LTESIO_RX, /* HIFI                         ʵ�ʷ���ͨ�� edma ch16 - 8  */
    EDMA_LTESIO_TX, /* HIFI                         ʵ�ʷ���ͨ�� edma ch16 - 9  */
    RESERVE_0,
    RESERVE_1,
    EDMA_HSUART_RX = 8, /* Acore drv ������������   ʵ�ʷ���ͨ�� edma ch16 - 12 */
    EDMA_HSUART_TX,     /* Acore drv ������������   ʵ�ʷ���ͨ�� edma ch16 - 13 */
    EDMA_UART0_RX,
    EDMA_UART0_TX,
    EDMA_UART1_RX,
    EDMA_UART1_TX,
    EDMA_UART2_RX,
    EDMA_UART2_TX,
    EDMA_SCI0_RX = 0x10,    /* Acore drv SIM��1��   ʵ�ʷ���ͨ�� edma ch16 - 10 */
	EDMA_SCI_RX  = 0x10,
    EDMA_SCI0_TX,           /* Acore drv SIM��1��   ʵ�ʷ���ͨ�� edma ch16 - 10 */
    EDMA_SCI1_RX,           /* Acore drv SIM��2��   ʵ�ʷ���ͨ�� edma ch16 - 11 */
    EDMA_SCI1_TX,           /* Acore drv SIM��2��   ʵ�ʷ���ͨ�� edma ch16 - 11 */

    EDMA_GBBP0_DBG = 0x14,
    EDMA_BBP_DBG   = 0x14, /* gudsp ������ bbp����  ʵ�ʷ���ͨ�� edma ch16 - 6  */
    EDMA_GBBP1_GRIF = 0x15,
    EDMA_BBP_GRIF   = 0x15,/* gudsp ������ bbp����  ʵ�ʷ���ͨ�� edma ch16 - 6  */

    EDMA_AMON_SOC = 0x16,     /* Acore drv AXIMON   ʵ�ʷ���ͨ�� edma ch16 - 15 */
    EDMA_AMON_CPUFAST = 0x17, /* Acore drv AXIMON   ʵ�ʷ���ͨ�� edma ch16 - 15 */
    EDMA_I2C0_RX,                   /*711����v7r2û��*/
    EDMA_I2C0_TX,                   /*711����v7r2û��*/
    EDMA_I2C1_RX,                   /*711����v7r2û��*/
    EDMA_I2C1_TX,                   /*711����v7r2û��*/
    EDMA_EMI_TRANS,            /*711����v7r2û��,edma_ch16��֧��,edma_ch4��֧��*/


    /* gudsp ������ M2M */
    /* EDMA_GBBP0_DBG      gudspʹ�� EDMA_BBP_DBG   ʵ�ʷ���ͨ�� edma ch16 - 6  */
    EDMA_MEMORY_DSP_1 = 0x20,   /* ����turbo����    ʵ�ʷ���ͨ�� edma ch4  - 0  */
    EDMA_MEMORY_DSP_2,          /* ����viterb����   ʵ�ʷ���ͨ�� edma ch4  - 1  */
    /*TL��GU���� ch16 - 2��Ϊ����ÿ������ǰ��鵱ǰͨ���Ƿ����***/
    EDMA_MEMORY_DSP_3,          /* ����CQI�����    ʵ�ʷ���ͨ�� edma ch16 - 2  */
    EDMA_MEMORY_DSP_4,          /* �������б���     ʵ�ʷ���ͨ�� edma ch4  - 2  */
    EDMA_MEMORY_DSP_5,          /* ����APT�����    ʵ�ʷ���ͨ�� edma ch4  - 3  */
    EDMA_MEMORY_DSP_6 = 0x25,   /* GUDSP/AHB����    ʵ�ʷ���ͨ�� edma ch16 - 7  */

    EDMA_PWC_LDSP_TCM  ,        /* Mcore  drv   ʵ�ʷ���ͨ�� edma ch16 - 0  */
    EDMA_PWC_TDSP_TCM ,         /* Mcore  drv   ʵ�ʷ���ͨ�� edma ch16 - 1  */


    /* TLDSP  �������壬û��ʵ����; �ŵ�MAXǰ�����ڲ���0ͨ�� */
    EDMA_LDSP_API_USED_0,       /* LDSP����ר�о��� ʵ�ʷ���ͨ�� edma ch16 - 0  */

    EDMA_REQ_MAX,               /*����豸����С�ڴ�ֵ����Ϊ�Ƿ�����*/

    /* TLDSP  �������壬û��ʵ����; */
    EDMA_LDSP_API_USED_1,       /* LDSP����ר�о��� ʵ�ʷ���ͨ�� edma ch16 - 1  */
    /*TL��GU���� ch16 - 2��Ϊ����ÿ������ǰ��鵱ǰͨ���Ƿ����***/
    EDMA_LDSP_LCS_SDR,          /* TLDSP LCS        ʵ�ʷ���ͨ�� edma ch16 - 2  */
    EDMA_LDSP_CSU_SDR,          /* LDSPС������     ʵ�ʷ���ͨ�� edma ch16 - 3  */
    EDMA_LDSP_EMU_SDR,          /* LDSP��������     ʵ�ʷ���ͨ�� edma ch16 - 4  */
    EDMA_LDSP_NV_LOADING,       /* LDSP��̬����NV   ʵ�ʷ���ͨ�� edma ch16 - 5  */
    EDMA_PCIE0_M2M_RX,
    EDMA_PCIE0_M2M_TX,
    EDMA_PCIE1_M2M_RX,
    EDMA_PCIE1_M2M_TX,
    EDMA_BUS_ANALYSE_1,
    EDMA_BUS_ANALYSE_2,

    EDMA_BUTT

} ;


/*EDMAC????????*/
typedef enum tagEDMA_TRANS_TYPE
{
    MEM_MEM_DMA = 0x00,    /* ?????,DMA??*/
    MEM_PRF_DMA = 0x01,    /* ?????,DMA??*/
/************should be 0x02 ???*/
    MEM_PRF_PRF = 0x10     /* ?????,????*/
} EDMA_TRANS_TYPE_E;

/*???????????*/
typedef struct _BALONG_DMA_CB
{
    volatile unsigned int lli;     /*????LLI*/
    volatile unsigned int bindx;
    volatile unsigned int cindx;
    volatile unsigned int cnt1;
    volatile unsigned int cnt0;  /*?????LLI??????????? <= 65535??*/
    volatile unsigned int src_addr; /*????*/
    volatile unsigned int des_addr; /*????*/
    volatile unsigned int config;
} BALONG_DMA_CB_S __attribute__ ((aligned (32)));

typedef void (*channel_isr)(unsigned int channel_arg, unsigned int int_status);/* v9r1 */
/*****************************************************************************
	 *  ? ? ?  : mdrv_edma_basic_config
	 *  ????  :  ????edma????????burst width?len?
	                                ????,????u32???
	 *  ????  :
	 *
	 *  ????  : ?
	 *  ? ? ?  :
     	 *
	 ******************************************************************************/
    /*unsigned int mdrv_edma_basic_config (unsigned int burst_width, unsigned int burst_len);*/
#define mdrv_edma_basic_config(burst_width, burst_len) \
        ( EDMAC_TRANSFER_CONFIG_SOUR_BURST_LENGTH(burst_len) | EDMAC_TRANSFER_CONFIG_DEST_BURST_LENGTH(burst_len) \
        | EDMAC_TRANSFER_CONFIG_SOUR_WIDTH(burst_width) | EDMAC_TRANSFER_CONFIG_DEST_WIDTH(burst_width) )
#define EDMAC_BASIC_CONFIG(burst_width, burst_len)  mdrv_edma_basic_config(burst_width, burst_len)

/*****************************************************************************
	 *  ? ? ?  : mdrv_edma_set_lli
	 *  ????  :  ???????,??????BALONG_DMA_CB?lli??
	 *                             ??lli?????????????????
	 *                             ????,?????
	 *  ????  :addr ?????
	 *
	 *  ????  : ?
	 *  ? ? ?  : 0	??????????
        *                        32???	"????"?"??"????????"
     	 *
	 ******************************************************************************/
/*unsigned int mdrv_edma_set_lli (unsigned int addr, unsigned int last);*/
 /*?????????*/
#define mdrv_edma_set_lli(addr,last)  ((last)?0:(EDMAC_MAKE_LLI_ADDR(addr) | EDMAC_NEXT_LLI_ENABLE))

#else
#define edma_req_id _BALONG_DMA_REQ
#define EDMAC_BASIC_CONFIG(burst_width, burst_len)  mdrv_edma_basic_config(burst_width, burst_len)
unsigned int bsp_edma_get_physical_req(BALONG_DMA_REQ_E request);

#endif

/*��ʽ����ʱ�Ľڵ���Ϣ*/
struct edma_cb
{
    volatile unsigned int lli;     /*ָ���¸�LLI*/
    volatile unsigned int bindx;
    volatile unsigned int cindx;
    volatile unsigned int cnt1;
    volatile unsigned int cnt0;   /*�鴫�����LLI�����ÿ���ڵ����ݳ��� <= 65535�ֽ�*/
    volatile unsigned int src_addr; /*�����ַ*/
    volatile unsigned int des_addr; /*�����ַ*/
    volatile unsigned int config;
} __attribute__((aligned(32)));



typedef u32 edma_addr_t;
#define EDMA_CX_LLI (0x800)
#define EDMA_CX_CONFIG (0x81C)


/*�����붨��*/
#ifndef OK
#define OK     0
#endif
#ifndef ERROR
#define ERROR (-1)
#endif
/*�����붨��*/

#define DMAC_SUCCESS                       0
#define DMA_FAIL                          (-1)

#define DMA_ERROR_BASE                          -100
#define DMA_CHANNEL_INVALID                     (DMA_ERROR_BASE-1)
#define DMA_TRXFERSIZE_INVALID                  (DMA_ERROR_BASE-2)
#define DMA_SOURCE_ADDRESS_INVALID              (DMA_ERROR_BASE-3)
#define DMA_DESTINATION_ADDRESS_INVALID         (DMA_ERROR_BASE-4)
#define DMA_MEMORY_ADDRESS_INVALID              (DMA_ERROR_BASE-5)
#define DMA_PERIPHERAL_ID_INVALID               (DMA_ERROR_BASE-6)
#define DMA_DIRECTION_ERROR                     (DMA_ERROR_BASE-7)
#define DMA_TRXFER_ERROR                        (DMA_ERROR_BASE-8)
#define DMA_LLIHEAD_ERROR                       (DMA_ERROR_BASE-9)
#define DMA_SWIDTH_ERROR                        (DMA_ERROR_BASE-0xa)
#define DMA_LLI_ADDRESS_INVALID                 (DMA_ERROR_BASE-0xb)
#define DMA_TRANS_CONTROL_INVALID               (DMA_ERROR_BASE-0xc)
#define DMA_MEMORY_ALLOCATE_ERROR               (DMA_ERROR_BASE-0xd)
#define DMA_NOT_FINISHED                        (DMA_ERROR_BASE-0xe)
#define DMA_CONFIG_ERROR                        (DMA_ERROR_BASE-0xf)


/*�����붨��*/

#define EDMA_SUCCESS         DMAC_SUCCESS
#define EDMA_FAIL            DMA_FAIL

#define EDMA_ERROR_BASE                          DMA_ERROR_BASE
#define EDMA_CHANNEL_INVALID                     DMA_CHANNEL_INVALID
#define EDMA_TRXFERSIZE_INVALID                  DMA_TRXFERSIZE_INVALID
#define EDMA_SOURCE_ADDRESS_INVALID              DMA_SOURCE_ADDRESS_INVALID
#define EDMA_DESTINATION_ADDRESS_INVALID         DMA_DESTINATION_ADDRESS_INVALID
#define EDMA_MEMORY_ADDRESS_INVALID              DMA_MEMORY_ADDRESS_INVALID
#define EDMA_PERIPHERAL_ID_INVALID               DMA_PERIPHERAL_ID_INVALID
#define EDMA_DIRECTION_ERROR                     DMA_DIRECTION_ERROR
#define EDMA_TRXFER_ERROR                        DMA_TRXFER_ERROR
#define EDMA_LLIHEAD_ERROR                       DMA_LLIHEAD_ERROR
#define EDMA_SWIDTH_ERROR                        DMA_SWIDTH_ERROR
#define EDMA_LLI_ADDRESS_INVALID                 DMA_LLI_ADDRESS_INVALID
#define EDMA_TRANS_CONTROL_INVALID               DMA_TRANS_CONTROL_INVALID
#define EDMA_MEMORY_ALLOCATE_ERROR               DMA_MEMORY_ALLOCATE_ERROR
#define EDMA_NOT_FINISHED                        DMA_NOT_FINISHED
#define EDMA_CONFIG_ERROR                        DMA_CONFIG_ERROR

/*  ����void (*channel_isr)(u32 channel_arg, u32 int_status)�Ĳ���int_status��
    ����s32 bsp_edma_channel_init (enum edma_req_id req,  channel_isr pFunc,
    u32 channel_arg, u32 int_flag)�Ĳ���int_flag Ϊ���¼����ж����ͣ������  */
#define EDMA_INT_DONE           BALONG_DMA_INT_DONE                /*EDMA��������ж�*/
#define EDMA_INT_LLT_DONE       BALONG_DMA_INT_LLT_DONE            /*��ʽEDMA�ڵ㴫������ж�*/
#define EDMA_INT_CONFIG_ERR     BALONG_DMA_INT_CONFIG_ERR          /*EDMA���ô����µ��ж�*/
#define EDMA_INT_TRANSFER_ERR   BALONG_DMA_INT_TRANSFER_ERR        /*EDMA��������µ��ж�*/
#define EDMA_INT_READ_ERR       BALONG_DMA_INT_READ_ERR            /*EDMA����������µ��ж�*/
#define EDMA_INT_ALL            0x1F

/* EDMAC���䷽����*/
#define EDMA_P2M      BALONG_DMA_P2M
#define EDMA_M2P      BALONG_DMA_M2P
#define EDMA_M2M      BALONG_DMA_M2M

#define EDMA_GET_DEST_ADDR       0
#define EDMA_GET_SOUR_ADDR       1

#ifdef __KERNEL__
#define EDMA_DATA_TIMEOUT      10 /* 10*5=50ms */
#elif defined (__OS_VXWORKS__)||defined (__OS_RTOSCK__)
#define EDMA_DATA_TIMEOUT      10
#else
#endif

/* EDMAC�������봫������*/

#define MEM_MEM_EDMA    MEM_MEM_DMA   /* �ڴ浽�ڴ棬DMA����*/
#define MEM_PRF_EDMA    MEM_PRF_DMA   /* �ڴ������裬DMA����*/

#define EDMAC_MAX_CHANNEL        (16)

#define EDMAC_DT_NUM       (16)
   /*ACPU=0,CCPU=1  */
#ifdef INT_LVL_EDMAC0

#ifdef __KERNEL__
#define EDMAC_DT_ARM       (0)
#define INT_LVL_EDMAC       INT_LVL_EDMAC0
#define INT_LVL_EDMAC_CH4   INT_LVL_EDMAC_CH4_0
#elif defined (__OS_VXWORKS__)||defined (__OS_RTOSCK__)
#define EDMAC_DT_ARM       (1)
#define INT_LVL_EDMAC       INT_LVL_EDMAC1
#define INT_LVL_EDMAC_CH4   INT_LVL_EDMAC_CH4_1
#else
#endif

#elif (defined INT_LVL_EDMA_MDM1)||(defined INT_LVL_EDMA_MDM0)

#ifdef __KERNEL__
#define EDMAC_DT_ARM       (0)
#define INT_LVL_EDMAC       INT_LVL_EDMA_MDM0
#define INT_LVL_EDMAC_CH4   INT_LVL_EDMAC_SOC_0
#elif defined (__OS_VXWORKS__)||defined (__OS_RTOSCK__)
#define EDMAC_DT_ARM       (1)
#define INT_LVL_EDMAC       INT_LVL_EDMA_MDM1
#define INT_LVL_EDMAC_CH4   INT_LVL_EDMAC_SOC_1
#else
#endif

#endif



#define EDMA_CH16_ID        0
#define EDMA_CH4_ID         1
#define EDMA_NUMBER         2

#define EDMA_ID(channel_id) ((channel_id<EDMA_CH16_NUM) ? EDMA_CH16_ID : EDMA_CH4_ID)
#define EDMA_ID_CHAN_ID(channel_id) \
        ((channel_id<EDMA_CH16_NUM) ? channel_id : (channel_id - EDMA_CH16_NUM))

/* EDMA ��Ӧ�ľ���λ   ��EDMA �Ĵ������ú�
       EDMAC_BASIC_CONFIG��EDMA_SET_LLI��EDMA_SET_CONFIG ʹ��*/

/*Bit3-2*/
#define EDMAC_TRANSFER_CONFIG_FLOW_EDMAC( _len )  EDMAC_TRANSFER_CONFIG_FLOW_DMAC( _len )

/*addr:�����ַ*/
#define EDMA_SET_LLI(addr, last)   mdrv_edma_set_lli(addr, last)

#define BALONG_DMA_SET_CONFIG(req, direction, burst_width, burst_len) \
                 ( EDMAC_BASIC_CONFIG(burst_width, burst_len) | EDMAC_TRANSFER_CONFIG_REQUEST(req) \
                 | EDMAC_TRANSFER_CONFIG_INT_TC_ENABLE | EDMAC_TRANSFER_CONFIG_CHANNEL_ENABLE \
                 | ((direction == BALONG_DMA_M2M)?M2M_CONFIG:((direction == BALONG_DMA_P2M)?P2M_CONFIG:M2P_CONFIG)))

#define EDMA_SET_CONFIG(req, direction, burst_width, burst_len) \
					BALONG_DMA_SET_CONFIG(req, direction, burst_width, burst_len)

#define EDMA_CHANNEL_DISABLE       EDMAC_TRANSFER_CONFIG_CHANNEL_DISABLE
#define EDMA_CHANNEL_ENABLE        EDMAC_TRANSFER_CONFIG_CHANNEL_ENABLE
#define EDMA_NEXT_LLI_ENABLE       EDMAC_NEXT_LLI_ENABLE


struct chan_int_service
{
   channel_isr chan_isr;
   u32 chan_arg;
   u32 int_status;
};

struct EDMAC_FREE_NODE_HEADER_STRU
{
    u32  ulInitFlag;
    u32  ulFirstFreeNode;
};

struct EDMA_LLI_ALLOC_ADDRESS_STRU
{
	u32 s_alloc_virt_address;
	u32 s_alloc_phys_address;
};

struct EDMA_SIMPLE_LLI_STRU
{
    u32 ulSourAddr;
    u32 ulDestAddr;
    u32 ulLength;
    u32 ulConfig;
};

struct EDMAC_TRANSFER_CONFIG_STRU
{
    struct edma_cb    lli_node_info;
	volatile u32   ulPad10[8];
};

struct EDMAC_CURR_STATUS_REG_STRU
{
	volatile u32 ulCxCurrCnt1;
	volatile u32 ulCxCurrCnt0;
	volatile u32 ulCxCurrSrcAddr;
	volatile u32 ulCxCurrDesAddr;
};

/*EDMA �Ĵ����ṹ��*/
typedef struct
{
	/*0x0000---*/
	volatile u32 ulIntState;
	/*0x0004---*/
	volatile u32 ulIntTC1;
	/*0x0008---*/
	volatile u32 ulIntTC2;
	/*0x000C---*/
	volatile u32 ulIntErr1;
	/*0x0010---*/
	volatile u32 ulIntErr2;
	/*0x0014---*/
	volatile u32 ulIntErr3;
	/*0x0018---*/
	volatile u32 ulIntTC1Mask;
	/*0x001C---*/
	volatile u32 ulIntTC2Mask;
	/*0x0020---*/
	volatile u32 ulIntErr1Mask;
	/*0x0024---*/
	volatile u32 ulIntErr2Mask;
	/*0x0028---*/
	volatile u32 ulIntErr3Mask;
	volatile u32 ulPad[(0x40-0x28)/4-1];
}EDMAC_CPU_REG_STRU;

struct edma_reg_struct
{
	volatile EDMAC_CPU_REG_STRU stCpuXReg[EDMAC_DT_NUM];

	volatile u32 ulPad0[(0x600-0x400)/4];
	/*0x0600-- */
	volatile u32 ulIntTC1Raw;
	volatile u32 ulPad1;
	/*0x0608-- */
	volatile u32 ulIntTC2Raw;
	volatile u32 ulPad2;
	/*0x0610-- */
	volatile u32 ulIntERR1Raw;
	volatile u32 ulPad3;
	/*0x0618-- */
	volatile u32 ulIntERR2Raw;
	volatile u32 ulPad4;
	/*0x0620-- */
	volatile u32 ulIntERR3Raw;
	volatile u32 ulPad5[(0x660-0x620)/4-1];
	/*0x0660--*/
	volatile u32 ulSingleReq;
    volatile u32 ulLastSingleReq;
    volatile u32 ulBurstReq;
    volatile u32 ulLastBurstReq;
    volatile u32 ulFlushReq;
    volatile u32 ulLastFlushReq;
	volatile u32 ulPad6[(0x688-0x674)/4-1];
	/*0x0688--*/
	volatile u32 ulChannelPrioritySet;
	volatile u32 ulPad7;
	/*0x0690--*/
    volatile u32 ulChannelState;
    volatile u32 ulPad8;
	/* 0x0698 -- */
    volatile u32 ulDmaCtrl;
    volatile u32 ulPad9[(0x0700-0x698)/4-1];
    /* 0x0700 -- */
	volatile struct EDMAC_CURR_STATUS_REG_STRU stCurrStatusReg[EDMAC_MAX_CHANNEL];
	/* 0x0800 -- */
	volatile struct EDMAC_TRANSFER_CONFIG_STRU stTransferConfig[EDMAC_MAX_CHANNEL];
};

#ifndef EDMAC_MAKE_LLI_ADDR
/*for acore,cause c_mdrv defined*/
#define EDMAC_MAKE_LLI_ADDR( _p )   (u32)( (u32)(_p) & 0xFFFFFFE0 )
#endif

#define EDMAC_CHANNEL_CB(x)   (g_edma_drv_info.edma_reg_str->stTransferConfig[x].lli_node_info)

#ifdef CONFIG_BALONG_EDMA

#ifdef __KERNEL__
#elif  defined(__OS_VXWORKS__)||defined (__OS_RTOSCK__)
s32  bsp_edma_init(void);
#else
#endif
s32 bsp_edma_channel_init (enum edma_req_id request, channel_isr pFunc, u32 channel_arg, u32 int_flag);
s32 bsp_edma_current_transfer_address(u32 channel_id);
u64 bsp_edma_current_cnt(u32 channel_id);
s32 bsp_edma_channel_stop(u32 channel_id);
s32 bsp_edma_channel_is_idle (u32 channel_id);
s32 bsp_edma_chanmap_is_idle (u32 channel_map);
void bsp_edma_channel_obtainable( void );
s32 bsp_edma_channel_set_config (u32 channel_id, u32 direction, u32 burst_width, u32 burst_len);
s32 bsp_edma_channel_dest_set_config(u32 channel_id, u32 dest_width, u32 dest_len);
s32 bsp_edma_channel_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len);
s32 bsp_edma_channel_2vec_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len, u32 size_align);
s32 bsp_edma_channel_async_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len);
struct edma_cb *bsp_edma_channel_get_lli_addr (u32 channel_id);
s32 bsp_edma_channel_lli_start (u32 channel_id);
s32 bsp_edma_channel_lli_async_start (u32 channel_id);
s32 bsp_edma_channel_free (u32 channel_id);
#else
static inline s32  bsp_edma_init(void){return -1;}
static inline s32 bsp_edma_channel_init (enum edma_req_id request, channel_isr pFunc, u32 channel_arg, u32 int_flag){return -1;}
static inline s32 bsp_edma_current_transfer_address(u32 channel_id){return -1;}
static inline u64 bsp_edma_current_cnt(u32 channel_id){return (u64)-1;}
static inline s32 bsp_edma_channel_stop(u32 channel_id){return -1;}
static inline s32 bsp_edma_channel_is_idle (u32 channel_id){return -1;}
static inline s32 bsp_edma_chanmap_is_idle (u32 channel_map){return -1;}
static inline void bsp_edma_channel_obtainable( void ){}
static inline s32 bsp_edma_channel_set_config (u32 channel_id, u32 direction, u32 burst_width, u32 burst_len){return -1;}
static inline s32 bsp_edma_channel_dest_set_config(u32 channel_id, u32 dest_width, u32 dest_len){return -1;}
static inline s32 bsp_edma_channel_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len){return -1;}
static inline s32 bsp_edma_channel_2vec_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len, u32 size_align){return -1;}
static inline s32 bsp_edma_channel_async_start (u32 channel_id, u32 src_addr, u32 des_addr, u32 len){return -1;}
static inline struct edma_cb *bsp_edma_channel_get_lli_addr (u32 channel_id){return (struct edma_cb *)0;}
static inline s32 bsp_edma_channel_lli_start (u32 channel_id){return -1;}
static inline s32 bsp_edma_channel_lli_async_start (u32 channel_id){return -1;}
static inline s32 bsp_edma_channel_free (u32 channel_id){return -1;}
#endif

/* v7r1 bus stress*/
typedef struct tagAXI_DMA_TASK_HANDLE_S
{
	unsigned int u32SrcAddr;
	unsigned int u32DstAddr;
	unsigned int ulLength;
	unsigned int ulChIdx;
}AXI_DMA_TASK_HANDLE_S;

s32 EDMA_NormTaskLaunch(AXI_DMA_TASK_HANDLE_S * pstDMAHandle);
s32 EDMA_2VecTaskLaunch(AXI_DMA_TASK_HANDLE_S * pstDMAHandle);
s32 EDMA_QueryCHNLState(u32 u32ChIdx);
s32 EDMA_QueryCHNsLState(u32 u32ChIdxMap);


#endif    /* End of DMADRV_H */

