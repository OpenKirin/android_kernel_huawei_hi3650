

#ifndef _SOCP_BALONG_H
#define _SOCP_BALONG_H

#ifdef __cplusplus
extern "C"
{
#endif

/**************************************************************************
  ͷ�ļ�����
**************************************************************************/
#include "bsp_memmap.h"
#include "soc_interrupts.h"
#include "product_config.h"
#include "hi_socp.h"
#include "bsp_socp.h"
#include "bsp_om.h"
#include <linux/dma-mapping.h>
#include <linux/semaphore.h>
#include <linux/workqueue.h>
#include <linux/kernel.h>
#include <asm/io.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/regulator/consumer.h>
#if defined(__OS_RTOSCK__)
#include "securec.h"
#endif

/**************************************************************************
  �궨��
**************************************************************************/
#if 0
#define SOCP_VIRT_PHY(virt)          virt_to_phys((void*)virt)
#define SOCP_PHY_VIRT(phy)           phys_to_virt((unsigned long)phy)
#else
#define SOCP_VIRT_PHY(virt)          (virt)
#define SOCP_PHY_VIRT(phy)           (phy)

#endif
typedef int (*socp_task_entry)(void * data);

/**************************************************************************
  �Ĵ�������,ƫ�Ƶ�ַ
**************************************************************************/
#define SOCP_REG_GBLRST             (HI_SOCP_GLOBAL_SRST_CTRL_OFFSET)
#define SOCP_REG_ENCRST             (HI_SOCP_ENC_SRST_CTRL_OFFSET)
#define SOCP_REG_DECRST             (HI_SOCP_DEC_SRST_CTRL_OFFSET)
#define SOCP_REG_ENCSTAT            (HI_SOCP_ENC_CH_STATUS_OFFSET)
#define SOCP_REG_DECSTAT            (HI_SOCP_DEC_CH_STATUS_OFFSET)
#define SOCP_REG_CLKCTRL            (HI_SOCP_CLK_CTRL_OFFSET)
#define SOCP_REG_PRICFG             (HI_SOCP_PRIOR_CFG_OFFSET)
#if (FEATURE_SOCP_DECODE_INT_TIMEOUT == FEATURE_ON)
#define SOCP_REG_DEC_INT_TIMEOUT    (HI_SOCP_DEC_INT_TIMEOUT_OFFSET)
#endif
#define SOCP_REG_INTTIMEOUT         (HI_SOCP_INT_TIMEOUT_OFFSET)
#define SOCP_REG_BUFTIMEOUT         (HI_SOCP_BUFFER_TIMEOUT_OFFSET)
#define SOCP_REG_DEC_PKTLEN         (HI_SOCP_DEC_PKT_LEN_CFG_OFFSET)
#define SOCP_REG_GBL_INTSTAT        (HI_SOCP_GLOBAL_INT_STATUS_OFFSET)

/* ������ �жϼĴ���*/
#define SOCP_REG_ENC_MASK0          (HI_SOCP_ENC_CORE0_MASK0_OFFSET)
#define SOCP_REG_ENC_RAWINT0        (HI_SOCP_ENC_CORE0_RAWINT0_OFFSET)
#define SOCP_REG_ENC_INTSTAT0       (HI_SOCP_ENC_CORE0_INT0_OFFSET)
#define SOCP_REG_APP_MASK1          (HI_SOCP_ENC_CORE0_MASK1_OFFSET)
#define SOCP_REG_MODEM_MASK1        (HI_SOCP_ENC_CORE1_MASK1_OFFSET)
#define SOCP_REG_ENC_RAWINT1        (HI_SOCP_ENC_RAWINT1_OFFSET)
#define SOCP_REG_APP_INTSTAT1       (HI_SOCP_ENC_CORE0_INT1_OFFSET)
#define SOCP_REG_MODEM_INTSTAT1     (HI_SOCP_ENC_CORE1_INT1_OFFSET)
#define SOCP_REG_ENC_MASK2          (HI_SOCP_ENC_CORE0_MASK2_OFFSET)
#define SOCP_REG_ENC_RAWINT2        (HI_SOCP_ENC_CORE0_RAWINT2_OFFSET)
#define SOCP_REG_ENC_INTSTAT2       (HI_SOCP_ENC_CORE0_INT2_OFFSET)
#define SOCP_REG_APP_MASK3          (HI_SOCP_ENC_CORE0_MASK3_OFFSET)
#define SOCP_REG_MODEM_MASK3        (HI_SOCP_ENC_CORE1_MASK3_OFFSET)
#define SOCP_REG_ENC_RAWINT3        (HI_SOCP_ENC_RAWINT3_OFFSET)
#define SOCP_REG_APP_INTSTAT3       (HI_SOCP_ENC_CORE0_INT3_OFFSET)
#define SOCP_REG_MODEM_INTSTAT3     (HI_SOCP_ENC_CORE1_INT3_OFFSET)
#define SOCP_REG_ENC_CORE1_MASK0    (HI_SOCP_ENC_CORE1_MASK0_OFFSET)
#define SOCP_REG_ENC_CORE1_INT0     (HI_SOCP_ENC_CORE1_INT0_OFFSET)
#define SOCP_REG_ENC_CORE1_MASK2    (HI_SOCP_ENC_CORE1_MASK2_OFFSET)
#define SOCP_REG_ENC_CORE1_INT2     (HI_SOCP_ENC_CORE1_INT2_OFFSET)

/* �������жϼĴ���*/
#define SOCP_REG_DEC_CORE0MASK0     (HI_SOCP_DEC_CORE0_MASK0_OFFSET)
#define SOCP_REG_DEC_CORE1MASK0     (HI_SOCP_DEC_CORE1_MASK0_OFFSET)
#define SOCP_REG_DEC_RAWINT0        (HI_SOCP_DEC_RAWINT0_OFFSET)
#define SOCP_REG_DEC_CORE0ISTAT0    (HI_SOCP_DEC_CORE0_INT0_OFFSET)
#define SOCP_REG_DEC_CORE1ISTAT0    (HI_SOCP_DEC_CORE1_INT0_OFFSET)
#define SOCP_REG_DEC_MASK1          (HI_SOCP_DEC_CORE0_MASK1_OFFSET)
#define SOCP_REG_DEC_RAWINT1        (HI_SOCP_DEC_CORE0_RAWINT1_OFFSET)
#define SOCP_REG_DEC_INTSTAT1       (HI_SOCP_DEC_CORE0_INT1_OFFSET)
#define SOCP_REG_DEC_CORE0MASK2     (HI_SOCP_DEC_CORE0_MASK2_OFFSET)
#define SOCP_REG_DEC_CORE1MASK2     (HI_SOCP_DEC_CORE1NOTE_MASK2_OFFSET)
#define SOCP_REG_DEC_RAWINT2        (HI_SOCP_DEC_RAWINT2_OFFSET)
#define SOCP_REG_DEC_CORE0ISTAT2    (HI_SOCP_DEC_CORE0NOTE_NT2_OFFSET)
#define SOCP_REG_DEC_CORE1ISTAT2    (HI_SOCP_DEC_CORE1NOTE_INT2_OFFSET)
#define SOCP_REG_DEC_CORE1_MASK1    (HI_SOCP_DEC_CORE1_MASK1_OFFSET)
#define SOCP_REG_DEC_CORE1_INT1     (HI_SOCP_DEC_CORE1_INT1_OFFSET)

/*������ͨ��buffer�Ĵ���*/
#define SOCP_REG_ENCSRC_BUFWPTR(m)  (HI_SOCP_ENC_SRC_BUFM_WPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFRPTR(m)  (HI_SOCP_ENC_SRC_BUFM_RPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFADDR(m)  (HI_SOCP_ENC_SRC_BUFM_ADDR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFCFG0(m)  (HI_SOCP_ENC_SRC_BUFM_CFG0_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_BUFCFG1(m)  (HI_SOCP_ENC_SRC_BUFM_CFG1_0_OFFSET + m*0x40)

#define SOCP_REG_ENCSRC_RDQWPTR(m)  (HI_SOCP_ENC_SRC_RDQ_WPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQRPTR(m)  (HI_SOCP_ENC_SRC_RDQ_RPTR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQADDR(m)  (HI_SOCP_ENC_SRC_RDQ_BADDR_0_OFFSET + m*0x40)
#define SOCP_REG_ENCSRC_RDQCFG(m)   (HI_SOCP_ENC_SRC_RDQ_CFG_0_OFFSET + m*0x40)

#define SOCP_REG_ENCDEST_BUFWPTR(n) (HI_SOCP_ENC_DEST_BUFN_WPTR_0_OFFSET + (n)*0x20)
#define SOCP_REG_ENCDEST_BUFRPTR(n) (HI_SOCP_ENC_DEST_BUFN_RPTR_0_OFFSET + (n)*0x20)
#define SOCP_REG_ENCDEST_BUFADDR(n) (HI_SOCP_ENC_DEST_BUFN_ADDR_0_OFFSET + (n)*0x20)
#define SOCP_REG_ENCDEST_BUFCFG(n)  (HI_SOCP_ENC_DEST_BUFN_CFG_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFTHRH(n) (HI_SOCP_ENC_DEST_BUFN_THRH_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFTHRESHOLD(n) (HI_SOCP_ENC_INT_THRESHOLD_0_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_SBCFG(n)        (HI_SOCP_ENC_DEST_SB_CFG_OFFSET + n*0x20)
#define SOCP_REG_ENCDEST_BUFSIDEBAND(n)  (HI_SOCP_ENC_DEST_BUFN_SIDBAND_OFFSET + n*0x20)

/*������ͨ��buffer�Ĵ���*/
#define SOCP_REG_DECSRC_BUFWPTR(x)  (HI_SOCP_DEC_SRC_BUFX_WPTR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFRPTR(x)  (HI_SOCP_DEC_SRC_BUFX_RPTR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFADDR(x)  (HI_SOCP_DEC_SRC_BUFX_ADDR_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFCFG0(x)  (HI_SOCP_DEC_SRC_BUFX_CFG0_0_OFFSET + x*0x40)
#define SOCP_REG_DEC_BUFSTAT0(x)    (HI_SOCP_DEC_BUFX_STATUS0_0_OFFSET + x*0x40)
#define SOCP_REG_DEC_BUFSTAT1(x)    (HI_SOCP_DEC_BUFX_STATUS1_0_OFFSET + x*0x40)
#define SOCP_REG_DECSRC_BUFSIDEBAND(x) (HI_SOCP_DEC_SRC_BUFX_SIDEBAND_OFFSET + x*0x40)

#define SOCP_REG_DECDEST_BUFWPTR(y) (HI_SOCP_DEC_DEST_BUFY_WPTR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFRPTR(y) (HI_SOCP_DEC_DEST_BUFY_RPTR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFADDR(y) (HI_SOCP_DEC_DEST_BUFY_ADDR_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFCFG(y)  (HI_SOCP_DEC_DEST_BUFY_CFG0_0_OFFSET + y*0x10)
#define SOCP_REG_DECDEST_BUFSIDEBAND(y)  (HI_SOCP_DEC_DEST_BUFY_SIDEBAND_OFFSET + y*0x10)

/*DEBUG�Ĵ���*/
#define SOCP_REG_ENCCD_DBG0         (HI_SOCP_ENC_CD_DBG0_OFFSET)
#define SOCP_REG_ENCCD_DBG1         (HI_SOCP_ENC_CD_DBG1_OFFSET)
#define SOCP_REG_ENCIBUF_DBG0       (HI_SOCP_ENC_IBUF_DBG0_OFFSET)
#define SOCP_REG_ENCIBUF_DBG1       (HI_SOCP_ENC_IBUF_DBG1_OFFSET)
#define SOCP_REG_ENCIBUF_DBG2       (HI_SOCP_ENC_IBUF_DBG2_OFFSET)
#define SOCP_REG_ENCIBUF_DBG3       (HI_SOCP_ENC_IBUF_DBG3_OFFSET)
#define SOCP_REG_ENCOBUF_DBG0       (HI_SOCP_ENC_OBUF_DBG0_OFFSET)
#define SOCP_REG_ENCOBUF_DBG1       (HI_SOCP_ENC_OBUF_DBG1_OFFSET)
#define SOCP_REG_ENCOBUF_DBG2       (HI_SOCP_ENC_OBUF_DBG2_OFFSET)
#define SOCP_REG_ENCOBUF_DBG3       (HI_SOCP_ENC_OBUF_DBG3_OFFSET)
#define SOCP_REG_DECIBUF_DBG0       (HI_SOCP_DEC_IBUF_DBG0_OFFSET)
#define SOCP_REG_DECIBUF_DBG1       (HI_SOCP_DEC_IBUF_DBG1_OFFSET)
#define SOCP_REG_DECIBUF_DBG2       (HI_SOCP_DEC_IBUF_DBG2_OFFSET)
#define SOCP_REG_DECIBUF_DBG3       (HI_SOCP_DEC_IBUF_DBG3_OFFSET)
#define SOCP_REG_DECOBUF_DBG0       (HI_SOCP_DEC_OBUF_DBG0_OFFSET)
#define SOCP_REG_DECOBUF_DBG1       (HI_SOCP_DEC_OBUF_DBG1_OFFSET)
#define SOCP_REG_DECOBUF_DBG2       (HI_SOCP_DEC_OBUF_DBG2_OFFSET)
#define SOCP_REG_DECOBUF_DBG3       (HI_SOCP_DEC_OBUF_DBG3_OFFSET)

/*�汾�Ĵ���*/
#define SOCP_REG_SOCP_VERSION       (HI_SOCP_SOCP_VERSION_OFFSET)
#define SOCP_NEW_VERSION            (0x201)

/* BBP ͨ���Ĵ��� */
#define BBP_REG_LOG_ADDR(m)         (0x0200 + 0x10*m)
#define BBP_REG_LOG_WPTR(m)         (0x0204 + 0x10*m)
#define BBP_REG_LOG_RPTR(m)         (0x0208 + 0x10*m)
#define BBP_REG_LOG_CFG(m)          (0x020C + 0x10*m)
#define BBP_REG_DS_ADDR             (0x0280)
#define BBP_REG_DS_WPTR             (0x0284)
#define BBP_REG_DS_RPTR             (0x0288)
#define BBP_REG_DS_CFG              (0x028C)
#define BBP_REG_PTR_ADDR            (0x0290)
#define BBP_REG_CH_EN               (0x0294)
#define BBP_REG_PKT_CNT             (0x0298)
#define BBP_REG_CH_STAT             (0x029C)
#define BBP_REG_LOG_EN              (0x02B8)

/**************************************************************************
  ͨ�����ֵ����
**************************************************************************/
#define SOCP_TOTAL_ENCSRC_CHN         (0x20)

#define BBP_MAX_CHN                   (0x09)
#define BBP_MAX_LOG_CHN               (0x08)
#define DSP_MAX_CHN                   (0x02)
#define SOCP_FIXED_MAX_CHAN           (BBP_MAX_CHN+DSP_MAX_CHN)
#define SOCP_MAX_ENCSRC_CHN           (0x20)    /* ����Դͨ�� */
#define SOCP_MAX_ENCDST_CHN           (0x07)
#define SOCP_MAX_DECSRC_CHN           (0x04)
#define SOCP_MAX_DECDST_CHN           (0x10)
#define SOCP_CCORE_ENCSRC_CHN_BASE    (4)
#define SOCP_CCORE_ENCSRC_CHN_NUM     (5)

/* LTE DSP/BBPͨ�� */
#define SOCP_DSPLOG_CHN               (0x0e)         // 14
#define SOCP_BBPLOG_CHN               (SOCP_DSPLOG_CHN + 2)  // 16��ʼ����8��
#define SOCP_BBPDS_CHN                (SOCP_BBPLOG_CHN + 8)  // 24
#define SOCP_FIXCHN_BASE              (SOCP_DSPLOG_CHN)
#define SOCP_FIXCHN_END               (SOCP_BBPDS_CHN)

/* ��ַ��ȷ�� */
#define BBP_REG_ARM_BASEADDR          HI_BBP_DMA_BASE_ADDR_VIRT
#define TENSILICA_CORE0_DRAM_ADDR     (0x49f80000)      /* DSP��ַ��ȷ�� */
#define SOCP_REG_BASEADDR             (g_strSocpStat.baseAddr)

/*SOCP BBP����ʹ�õ�Ԥ���ڴ�ռ�궨��*/
#define PBXA9_DRAM_BBPDS_VIRT         (IO_ADDRESS(DDR_SOCP_ADDR))      /* �õ�ַ��Ҫȷ�� */
#define PBXA9_DRAM_BBPDS_PHYS         (DDR_SOCP_ADDR)      /* �õ�ַ��Ҫȷ�� */
#define PBXA9_DRAM_BBPDS_SIZE         (DDR_SOCP_SIZE)           /* �ÿռ��С��Ҫȷ�� */

#define INT_LVL_SOCP                  INT_LVL_SOCP0

/*ϵͳ������*/
#define SOCP_BBPDS_CHN_ADDR           (PBXA9_DRAM_BBPDS_PHYS)
#define SOCP_BBPDS_CHN_SIZE           (PBXA9_DRAM_BBPDS_SIZE)


#define SOCP_BBPLOG_CHN_SIZE          (0x2000)
#define SOCP_BBPLOG0_CHN_SIZE         (0x2000*8)
#define SOCP_FIXEDID_BASE             (SOCP_DSPLOG_CHN - SOCP_FIXCHN_BASE)

#define SOCP_DSPLOG_DST_BUFID         ((s32) 1)
#define SOCP_BBPLOG_DST_BUFID         ((s32) 1)
#define SOCP_BBPDS_DST_BUFID          ((s32) 1)


/* log2.0 2014-03-19 Begin:*/
/* SOCP�������������������ӳ�ʱ�䣬10msΪ��λ */
#define SOCP_LOG_FLUSH_MAX_OVER_TIME    10
/* log2.0 2014-03-19 End:*/
/**************************************************************************
  �ṹ����
**************************************************************************/

/* ͨ��״̬�ṹ�壬������ */
typedef struct tagSOCP_RING_BUF_S
{
    u32             u32Start;
    u32             u32End;
    u32             u32Write;
    u32             u32Read;
    u32             u32Length;
    u32             u32IdleSize;
}SOCP_RING_BUF_S;

typedef struct tagSOCP_ENCSRC_CHAN_S
{
    u32                     u32ChanID;
    u32                     u32ChanEn;
    u32                     u32DestChanID;
    u32                     u32BypassEn;
    u32                     u32AllocStat;  /* ͨ���Ѿ���û�з���ı�ʶ*/
    u32                     u32LastRdSize;
    u32                     u32RdThreshold;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eChnMode;      /* ���ݽṹ���� */
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eDebugEn;
    SOCP_RING_BUF_S         sEncSrcBuf;
    SOCP_RING_BUF_S         sRdBuf;
    socp_event_cb           event_cb;
    socp_rd_cb              rd_cb;
}SOCP_ENCSRC_CHAN_S;


typedef struct tagSOCP_ENCSRC_FIXCHAN_S
{
    u32                     u32ChanID;
    u32                     u32ChanEn;
    u32                     u32DestChanID;
    SOCP_ENCSRC_CHNMODE_ENUM_UIN32   eChnMode;      /* ���ݽṹ���� */
    SOCP_CHAN_PRIORITY_ENUM_UIN32    ePriority;
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_ENC_DEBUG_EN_ENUM_UIN32     eDebugEn;
    SOCP_RING_BUF_S         sEncSrcBuf;
    SOCP_RING_BUF_S         sRdBuf;
    socp_event_cb           event_cb;
    socp_rd_cb              rd_cb;
}SOCP_ENCSRC_FIXCHAN_S;



typedef struct socp_compress
{
    int bcompress;
    socp_compress_ops_stru  ops;
}socp_compress_stru;

typedef struct tagSOCP_ENCDST_CHAN_S
{
    u32                     u32ChanID;
    u32                     u32SetStat;    /* ͨ���Ѿ���û�����õı�ʶ*/
    u32                     u32Thrh;       /* ��ֵ*/
    socp_compress_stru      struCompress;
    SOCP_RING_BUF_S         sEncDstBuf;
    SOCP_EVENT_ENUM_UIN32            eChnEvent;
    socp_event_cb           event_cb;
    socp_read_cb            read_cb;
    u32                     bufThreshold;
}SOCP_ENCDST_CHAN_S;

typedef struct tagSOCP_DECSRC_CHAN_S
{
    u32                     u32ChanID;
    u32                     u32ChanEn;
    u32                     u32SetStat;    /* ͨ���Ѿ���û�����õı�ʶ*/
    u32                     u32RdThreshold;
    SOCP_DATA_TYPE_EN_ENUM_UIN32     eDataTypeEn;
    SOCP_DECSRC_CHNMODE_ENUM_UIN32   eChnMode;      /* ���ݽṹ���� */
    SOCP_RING_BUF_S         sDecSrcBuf;
    SOCP_RING_BUF_S         sDecRdBuf;
    socp_event_cb           event_cb;
    socp_rd_cb              rd_cb;
}SOCP_DECSRC_CHAN_S;

typedef struct tagSOCP_DECDST_CHAN_S
{
    u32                     u32ChanID;
    u32                     u32AllocStat;
    SOCP_DATA_TYPE_ENUM_UIN32        eDataType;
    SOCP_RING_BUF_S         sDecDstBuf;
    socp_event_cb           event_cb;
    socp_read_cb            read_cb;
}SOCP_DECDST_CHAN_S;


/* ȫ��״̬�ṹ�� */
typedef struct tagSOCP_GBL_STATE
{
    s32                     bInitFlag;
    unsigned long           baseAddr;
    unsigned long           armBaseAddr;
    unsigned long           tensiAddr;
    unsigned long           bbpDsAddr;
    struct semaphore        u32EncSrcSemID;
    struct semaphore        u32EncDstSemID;
    struct semaphore        u32DecSrcSemID;
    struct semaphore        u32DecDstSemID;
    unsigned long           u32EncSrcTskID;
    unsigned long           u32EncDstTskID;
    unsigned long           u32DecSrcTskID;
    unsigned long           u32DecDstTskID;
    u32                     u32IntEncSrcHeader;
    u32                     u32IntEncSrcRD;
    u32                     u32IntEncDstTfr;
    u32                     u32IntEncDstOvf;
    u32                     u32IntEncDstThresholdOvf;
    u32                     u32IntDecSrcErr;
    u32                     u32IntDecDstTfr;
    u32                     u32IntDecDstOvf;
    socp_compress_isr       compress_isr;
    SOCP_ENCSRC_CHAN_S      sEncSrcChan[SOCP_MAX_ENCSRC_CHN];
    SOCP_ENCDST_CHAN_S      sEncDstChan[SOCP_MAX_ENCDST_CHN];
    SOCP_DECSRC_CHAN_S      sDecSrcChan[SOCP_MAX_DECSRC_CHN];
    SOCP_DECDST_CHAN_S      sDecDstChan[SOCP_MAX_DECDST_CHN];
}SOCP_GBL_STATE;

/*����ѹ��ö��*/
enum SOCP_ENC_DST_OUTPUT_COMPRESS_ENUM
{
    SOCP_NO_COMPRESS       = 0,
    SOCP_COMPRESS,
};
typedef unsigned int SOCP_ENC_DST_COMPRESS_UINT32;

typedef struct tagSOCP_DEBUG_GBL_S
{
    u32  u32SocpAllocEncSrcCnt;        /* SOCP�������Դͨ���Ĵ���*/
    u32  u32SocpAllocEncSrcSucCnt;     /* SOCP�������Դͨ���ɹ��Ĵ���*/
    u32  u32SocpSetEncDstCnt;          /* SOCP���ñ���Ŀ��ͨ���Ĵ���*/
    u32  u32SocpSetEncDstSucCnt;       /* SOCP���ñ���Ŀ��ͨ���ɹ��Ĵ���*/
    u32  u32SocpSetDecSrcCnt;          /* SOCP���ý���Դͨ���Ĵ���*/
    u32  u32SocpSetDeSrcSucCnt;        /* SOCP���ý���Դͨ���ɹ��Ĵ���*/
    u32  u32SocpAllocDecDstCnt;        /* SOCP�������Ŀ��ͨ���Ĵ���*/
    u32  u32SocpAllocDecDstSucCnt;     /* SOCP�������Ŀ��ͨ���ɹ��Ĵ���*/
    u32 u32SocpAppEtrIntCnt;           /* ����APP�жϵĴ���*/
    u32 u32SocpAppSucIntCnt;           /* ����APP�жϴ���ɹ��Ĵ���*/
} SOCP_DEBUG_GBL_S;

typedef struct tagSOCP_DEBUG_ENCSRC_S
{
    u32 u32SocpFreeEncSrcCnt[SOCP_MAX_ENCSRC_CHN];         /* SOCP�ͷű���Դͨ���ɹ��Ĵ���*/
    u32 u32SocpSoftResetEncSrcCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCP��λ����Դͨ���Ĵ���*/
    u32 u32SocpStartEncSrcCnt[SOCP_MAX_ENCSRC_CHN];        /* SOCP��������Դͨ���Ĵ���*/
    u32 u32SocpStopEncSrcCnt[SOCP_MAX_ENCSRC_CHN];         /* SOCP�رձ���Դͨ���Ĵ���*/
    u32 u32SocpRegEventEncSrcCnt[SOCP_MAX_ENCSRC_CHN];     /* SOCPע�����Դͨ���¼��Ĵ���*/
    u32 u32SocpGetWBufEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];      /* SOCP����Դͨ�����Ի��дbuffer�Ĵ���*/
    u32 u32SocpGetWBufEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];      /* SOCP����Դͨ���ɹ����дbuffer�Ĵ���*/
    u32 u32socp_write_doneEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCP����Դͨ������д��buffer�Ĵ���*/
    u32 u32socp_write_doneEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCP����Դͨ���ɹ�д��buffer�Ĵ���*/
    u32 u32socp_write_doneEncSrcFailCnt[SOCP_MAX_ENCSRC_CHN];    /* SOCP����Դͨ��д��bufferʧ�ܵĴ���*/
    u32 u32SocpRegRdCBEncSrcCnt[SOCP_MAX_ENCSRC_CHN];          /* SOCPע�����Դͨ��RDbuffer�ص������Ĵ���*/
    u32 u32SocpGetRdBufEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];     /* SOCP����Դͨ�����Ի��Rdbuffer�Ĵ���*/
    u32 u32SocpGetRdBufEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];     /* SOCP����Դͨ���ɹ����Rdbuffer�Ĵ���*/
    u32 u32SocpReadRdDoneEncSrcEtrCnt[SOCP_MAX_ENCSRC_CHN];   /* SOCP����Դͨ������д��Rdbuffer�Ĵ���*/
    u32 u32SocpReadRdDoneEncSrcSucCnt[SOCP_MAX_ENCSRC_CHN];   /* SOCP����Դͨ���ɹ�д��Rdbuffer�Ĵ���*/
    u32 u32SocpReadRdDoneEncSrcFailCnt[SOCP_MAX_ENCSRC_CHN];   /* SOCP����Դͨ��д��Rdbufferʧ�ܵĴ���*/
    u32 u32SocpEncSrcTskHeadCbCnt[SOCP_MAX_ENCSRC_CHN];      /* �����лص�����Դͨ����ͷ�����жϴ�������ɵĴ���*/
    u32 u32SocpEncSrcTskHeadCbOriCnt[SOCP_MAX_ENCSRC_CHN];   /* �����лص�����Դͨ����ͷ�����жϴ���������*/
    u32 u32SocpEncSrcTskRdCbCnt[SOCP_MAX_ENCSRC_CHN];        /* �����лص�����Դͨ��Rd ����жϴ�������ɵĴ���*/
    u32 u32SocpEncSrcTskRdCbOriCnt[SOCP_MAX_ENCSRC_CHN];     /* �����лص�����Դͨ��Rd ����жϴ���������*/
    u32 u32SocpEncSrcIsrHeadIntCnt[SOCP_MAX_ENCSRC_CHN];      /* ISR�н������Դͨ����ͷ�����жϴ���*/
    u32 u32SocpEncSrcIsrRdIntCnt[SOCP_MAX_ENCSRC_CHN];        /* ISR�������Դͨ��Rd ����жϴ���*/
} SOCP_DEBUG_ENCSRC_S;

typedef struct tagSOCP_DEBUG_ENCDST_S
{
    u32 u32SocpRegEventEncDstCnt[SOCP_MAX_ENCDST_CHN];     /* SOCPע�����Ŀ��ͨ���¼��Ĵ���*/
    u32 u32SocpRegReadCBEncDstCnt[SOCP_MAX_ENCDST_CHN];    /* SOCPע�����Ŀ��ͨ�������ݻص������Ĵ���*/
    u32 u32SocpGetReadBufEncDstEtrCnt[SOCP_MAX_ENCDST_CHN];   /* SOCP����Ŀ��ͨ�����Զ����ݵĴ���*/
    u32 u32SocpGetReadBufEncDstSucCnt[SOCP_MAX_ENCDST_CHN];   /* SOCP����Ŀ��ͨ���ɹ������ݵĴ���*/
    u32 u32socp_read_doneEncDstEtrCnt[SOCP_MAX_ENCDST_CHN];     /* SOCP����Ŀ��ͨ������д��Ŀ��buffer�Ĵ���*/
    u32 u32socp_read_doneEncDstSucCnt[SOCP_MAX_ENCDST_CHN];     /* SOCP����Ŀ��ͨ��д��Ŀ��buffer�ɹ��Ĵ���*/
    u32 u32socp_read_doneEncDstFailCnt[SOCP_MAX_ENCDST_CHN];     /* SOCP����Ŀ��ͨ��д��Ŀ��bufferʧ�ܵĴ���*/
    u32 u32socp_read_doneZeroEncDstCnt[SOCP_MAX_ENCDST_CHN];     /* SOCP����Ŀ��ͨ��д��Ŀ��buffer size ����0 �Ĵ���*/
    u32 u32socp_read_doneValidEncDstCnt[SOCP_MAX_ENCDST_CHN];    /* SOCP����Ŀ��ͨ��д��Ŀ��buffer size ������0 �Ĵ���*/
    u32 u32SocpEncDstTskTrfCbCnt[SOCP_MAX_ENCDST_CHN];        /* �����лص�����Ŀ��ͨ����������жϴ�������ɵĴ���*/
    u32 u32SocpEncDstTskTrfCbOriCnt[SOCP_MAX_ENCDST_CHN];        /* �����лص�����Ŀ��ͨ����������жϴ������Ĵ���*/
    u32 u32SocpEncDstTskOvfCbCnt[SOCP_MAX_ENCDST_CHN];        /* �����лص�����Ŀ��ͨ��buf ����жϴ�������ɵĴ���*/
    u32 u32SocpEncDstTskOvfCbOriCnt[SOCP_MAX_ENCDST_CHN];     /* �����лص�����Ŀ��ͨ��buf ����жϴ���������*/
    u32 u32SocpEncDstIsrTrfIntCnt[SOCP_MAX_ENCDST_CHN];        /* ISR�н������Ŀ��ͨ����������жϴ���*/
    u32 u32SocpEncDstIsrOvfIntCnt[SOCP_MAX_ENCDST_CHN];        /* ISR�н������Ŀ��ͨ��buf ����жϴ���*/
    u32 u32SocpEncDstTskThresholdOvfCbCnt[SOCP_MAX_ENCDST_CHN];        /* �����лص�����Ŀ��ͨ��buf��ֵ����жϴ�������ɵĴ���*/
    u32 u32SocpEncDstTskThresholdOvfCbOriCnt[SOCP_MAX_ENCDST_CHN];     /* �����лص�����Ŀ��ͨ��buf��ֵ����жϴ���������*/
    u32 u32SocpEncDstIsrThresholdOvfIntCnt[SOCP_MAX_ENCDST_CHN];       /* ISR�н������Ŀ��ͨ��buf��ֵ����жϴ���*/
    /* log2.0 2014-03-19 Begin:*/
	BSP_U32 u32SocpEncDstSoftOverTimeOriCnt[SOCP_MAX_ENCDST_CHN];  /* SOCP����Ŀ��ͨ�������ʱ������� */
    BSP_U32 u32SocpEncDstSoftOverTimeCnt[SOCP_MAX_ENCDST_CHN];     /* SOCP����Ŀ��ͨ�������ʱ������ɴ��� */
	/* log2.0 2014-03-19 End:*/
} SOCP_DEBUG_ENCDST_S;

typedef struct tagSOCP_DEBUG_DECSRC_S
{
    u32 u32SocpSoftResetDecSrcCnt[SOCP_MAX_DECSRC_CHN];    /* SOCP��λ����Դͨ���Ĵ���*/
    u32 u32SocpStartDecSrcCnt[SOCP_MAX_DECSRC_CHN];        /* SOCP��������Դͨ���Ĵ���*/
    u32 u32SocpStopDecSrcCnt[SOCP_MAX_DECSRC_CHN];         /* SOCP�رս���Դͨ���Ĵ���*/
    u32 u32SocpRegEventDecSrcCnt[SOCP_MAX_DECSRC_CHN];     /* SOCPע�����Դͨ���¼��Ĵ���*/
    u32 u32SocpGetWBufDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];      /* SOCP����Դͨ�����Ի��дbuffer�Ĵ���*/
    u32 u32SocpGetWBufDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];      /* SOCP����Դͨ�����дbuffer�ɹ��Ĵ���*/
    u32 u32socp_write_doneDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];    /* SOCP����Դͨ������д��buffer�Ĵ���*/
    u32 u32socp_write_doneDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];    /* SOCP����Դͨ��д��buffer�ɹ��Ĵ���*/
    u32 u32socp_write_doneDecSrcFailCnt[SOCP_MAX_DECSRC_CHN];    /* SOCP����Դͨ��д��bufferʧ�ܵĴ���*/
    u32 u32SocpRegRdCBDecSrcCnt[SOCP_MAX_DECSRC_CHN];      /* SOCPע�����Դͨ��RDbuffer�ص������Ĵ���*/
    u32 u32SocpGetRdBufDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];     /* SOCP����Դͨ�����Ի��Rdbuffer�Ĵ���*/
    u32 u32SocpGetRdBufDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];     /* SOCP����Դͨ�����Rdbuffer�ɹ��Ĵ���*/
    u32 u32SocpReadRdDoneDecSrcEtrCnt[SOCP_MAX_DECSRC_CHN];   /* SOCP����Դͨ������д��Rdbuffer�Ĵ���*/
    u32 u32SocpReadRdDoneDecSrcSucCnt[SOCP_MAX_DECSRC_CHN];   /* SOCP����Դͨ��д��Rdbuffer�ɹ��Ĵ���*/
    u32 u32SocpReadRdDoneDecSrcFailCnt[SOCP_MAX_DECSRC_CHN];   /* SOCP����Դͨ��д��Rdbufferʧ�ܵĴ���*/
    u32 u32SocpDecSrcIsrErrIntCnt[SOCP_MAX_DECSRC_CHN];        /* ISR�н������Դͨ�������жϴ���*/
    u32 u32SocpDecSrcTskErrCbCnt[SOCP_MAX_DECSRC_CHN];        /* �����е��ý���Դͨ�������жϴ�������ɵĴ���*/
    u32 u32SocpDecSrcTskErrCbOriCnt[SOCP_MAX_DECSRC_CHN];     /* �����е��ý���Դͨ�������жϴ���������*/
} SOCP_DEBUG_DECSRC_S;

typedef struct tagSOCP_DEBUG_DECDST_S
{
    u32 u32SocpFreeDecDstCnt[SOCP_MAX_DECDST_CHN];         /* SOCP�ͷŽ���Ŀ��ͨ���ɹ��Ĵ���*/
    u32 u32SocpRegEventDecDstCnt[SOCP_MAX_DECDST_CHN];     /* SOCPע�����Ŀ��ͨ���¼��Ĵ���*/
    u32 u32SocpRegReadCBDecDstCnt[SOCP_MAX_DECDST_CHN];    /* SOCPע�����Ŀ��ͨ�������ݻص������Ĵ���*/
    u32 u32SocpGetReadBufDecDstEtrCnt[SOCP_MAX_DECDST_CHN];   /* SOCP����Ŀ��ͨ�����Զ����ݵĴ���*/
    u32 u32SocpGetReadBufDecDstSucCnt[SOCP_MAX_DECDST_CHN];   /* SOCP����Ŀ��ͨ�������ݳɹ��Ĵ���*/
    u32 u32socp_read_doneDecDstEtrCnt[SOCP_MAX_DECDST_CHN];     /* SOCP����Ŀ��ͨ������д��Ŀ��buffer�Ĵ���*/
    u32 u32socp_read_doneDecDstSucCnt[SOCP_MAX_DECDST_CHN];     /* SOCP����Ŀ��ͨ��д��Ŀ��buffer�ɹ��Ĵ���*/
    u32 u32socp_read_doneDecDstFailCnt[SOCP_MAX_DECDST_CHN];     /* SOCP����Ŀ��ͨ��д��Ŀ��bufferʧ�ܵĴ���*/
    u32 u32socp_read_doneZeroDecDstCnt[SOCP_MAX_DECDST_CHN];   /* SOCP����Ŀ��ͨ��д��Ŀ��buffer size ����0 �Ĵ���*/
    u32 u32socp_read_doneValidDecDstCnt[SOCP_MAX_DECDST_CHN];   /* SOCP����Ŀ��ͨ��д��Ŀ��buffer size ������0 �Ĵ���*/
    u32 u32SocpDecDstIsrTrfIntCnt[SOCP_MAX_DECDST_CHN];        /* ISR�н������Ŀ��ͨ����������жϴ���*/
    u32 u32SocpDecDstTskTrfCbCnt[SOCP_MAX_DECDST_CHN];         /* �����лص�����Ŀ��ͨ����������жϴ�������ɵĴ���*/
    u32 u32SocpDecDstTskTrfCbOriCnt[SOCP_MAX_DECDST_CHN];      /* �����лص�����Ŀ��ͨ����������жϴ���������*/
    u32 u32SocpDecDstIsrOvfIntCnt[SOCP_MAX_DECDST_CHN];        /* ISR�н������Ŀ��ͨ��buf ����жϴ���*/
    u32 u32SocpDecDstTskOvfCbCnt[SOCP_MAX_DECDST_CHN];         /* �����н������Ŀ��ͨ��buf ����жϴ�������ɵĴ���*/
    u32 u32SocpDecDstTskOvfCbOriCnt[SOCP_MAX_DECDST_CHN];      /* �����н������Ŀ��ͨ��buf ����жϴ���������*/
} SOCP_DEBUG_DECDST_S;

/* ������Ϣ*/
typedef struct tagSOCP_DEBUG_INFO_S
{
    SOCP_DEBUG_GBL_S    sSocpDebugGBl;
    SOCP_DEBUG_ENCSRC_S sSocpDebugEncSrc;
    SOCP_DEBUG_ENCDST_S sSocpDebugEncDst;
    SOCP_DEBUG_DECSRC_S sSocpDebugDecSrc;
    SOCP_DEBUG_DECDST_S sSocpDebugDecDst;
}SOCP_DEBUG_INFO_S;

typedef struct
{
    SOCP_VOTE_TYPE_ENUM_U32 vote_type;
    BSP_U32                 vote_time;
}SOCP_VOTE_INFO_STRU;

typedef struct
{
    BSP_U32 en_flag;
}SOCP_ON_DEMAND_STRU;

typedef struct
{
    struct device * dev;
    struct regulator_bulk_data socp_vcc;
}SOCP_VCC_STRU;

#if(FEATURE_SOCP_ON_DEMAND == FEATURE_ON)
enum SOCP_POWER_STATE_ENUM
{
    SOCP_POWER_ON,
    SOCP_POWER_OFF_REQ,
    SOCP_POWER_OFF,
    SOCP_POWER_STATE_BUTT,
};
typedef unsigned int SOCP_POWER_STATE_ENUM_U32;
#endif


typedef enum{
    SOCP_DST_CHAN_CFG_ADDR = 0,
    SOCP_DST_CHAN_CFG_SIZE,
    SOCP_DST_CHAN_CFG_TIME,
    SOCP_DST_CHAN_CFG_RSV,
    SOCP_DST_CHAN_CFG_BUTT
}SOCP_DST_CHAN_CFG_ENUM;

typedef struct
{
    struct device * dev;
    struct clk    * socp_clk;
    u32             ulCnt;
}SOCP_CLK_STRU;

/**************************************************************************
  �Ĵ���λ����
**************************************************************************/

/*
* Bit masks for registers: ENCSTAT,DECSTAT, channel state
*/
#define SOCP_CHN_BUSY                   ( (s32) 1)   /*ͨ��æ*/
#define SOCP_CHN_IDLE                   ( (s32) 0)   /*ͨ����*/

/*
* ͨ���򿪺궨�壬�����ڱ���Դͨ���ͽ���Ŀ��ͨ��
*/
#define SOCP_CHN_ALLOCATED              ((s32) 1)    /*ͨ���Ѿ�����*/
#define SOCP_CHN_UNALLOCATED            ((s32) 0)    /*ͨ��û�з���*/

/*
* ͨ��ʹ�ܺ궨�壬ͬʱ�����ڱ���Դͨ���ͽ���Դͨ��
*/
#define SOCP_CHN_ENABLE                 ( (s32) 1)   /*ͨ����*/
#define SOCP_CHN_DISABLE                ( (s32) 0)   /*ͨ���ر�*/

/*
* ͨ���Ƿ��Ѿ�����
*/
#define SOCP_CHN_SET                    ( (s32) 1)     /*ͨ���Ѿ�����*/
#define SOCP_CHN_UNSET                  ( (s32) 0)     /*ͨ��û������*/
/*
* ������·����ʹ��λ
*/
#define SOCP_ENCSRC_BYPASS_ENABLE       ( (s32) 1)     /*ͨ����·ʹ��*/
#define SOCP_ENCSRC_BYPASS_DISABLE      ( (s32) 0)     /*ͨ����·û��ʹ��*/


/*
* ������·����ʹ��λ
*/
#define SOCP_DECSRC_DEBUG_ENBALE        ( (s32) 1)     /*ͨ��DEBUG ʹ��*/
#define SOCP_DECSRC_DEBUG_DISBALE       ( (s32) 0)     /*ͨ��DEBUG û��ʹ��*/

#define SOCP_CORE0_DEC_OUTOVFINT_MASK   ( (s32)(1))          /* ����core0 Ŀ��BUFFER����ж� */
#define SOCP_DEC_INERRINT_MASK          ( (s32)(1<<1))       /* ��������������ж� */
#define SOCP_CORE0_DEC_TFRINT_MASK      ( (s32)(1<<2))       /* ����core0 ��������ж� */
#define SOCP_CORE1_DEC_TFRINT_MASK      ( (s32)(1<<3))       /* ����core1 ��������ж� */
#define SOCP_CORE1_DEC_OUTOVFINT_MASK   ( (s32)(1<<4))       /* ����core1 Ŀ��BUFFER����ж�*/
#define SOCP_CORE0_ENC_MODESWT_MASK     ( (s32)(1<<6))       /* ����core0 ����Ŀ��bufferģʽ�л���� */
#define SOCP_CORE1_ENC_MODESWT_MASK     ( (s32)(1<<7))       /* ����core1 ����Ŀ��bufferģʽ�л���� */
#define SOCP_MODEM_ENC_RDINT_MASK       ( (s32)(1<<10))      /* ����RDBUFFER����ж� */
#define SOCP_APP_ENC_RDINT_MASK         ( (s32)(1<<11))      /* ����APPCPU��ѯ����ͨ��Rd���ȫ���ж� */
#define SOCP_APP_ENC_OUTOVFINT_MASK     ( (s32)(1<<12))      /* ����RDBUFFER����ж� */
#define SOCP_MODEM_ENC_FLAGINT_MASK     ( (s32)(1<<13))      /* ����MODEMCPU��ͷ�������ж� */
#define SOCP_APP_ENC_FLAGINT_MASK       ( (s32)(1<<14))      /* ����APP  CPU��ͷ�������ж� */
#define SOCP_APP_ENC_TFRINT_MASK        ( (s32)(1<<15))      /* ����ͨ������ȫ���ж� */
#define SOCP_DEC_SRCINT_NUM             (6)                  /* ����MODEMCPU��ͷ�������ж� */


#define SOCP_TRANS_TIMEOUT_DEFAULT      (0x17)     //dec:23
#define SOCP_OVERFLOW_TIMEOUT_DEFAULT   (0x5969)   //dec:22889

#define SOCP_DEC_PKTLGTH_MAX            (0x04)     //dec:4096, ��λΪKB
#define SOCP_DEC_PKTLGTH_MIN            (0x06)     //dec:6, ��λΪ�ֽ�
#define SOCP_TIMEOUT_MAX                (0xffff)
#define SOCP_DEC_MAXPKT_MAX             (0x1000)
#define SOCP_DEC_MINPKT_MAX             (0x1f)
#define SOCP_ENC_SRC_BUFLGTH_MAX        (0x7ffffff)
#define SOCP_ENC_SRC_RDLGTH_MAX         (0xffff)
#define SOCP_ENC_DST_BUFLGTH_MAX        (0x1fffff)
#define SOCP_ENC_DST_TH_MAX             (0x7ff)
#define SOCP_DEC_SRC_BUFLGTH_MAX        (0xffff)
#define SOCP_DEC_SRC_RDLGTH_MAX         (0xffff)
#define SOCP_DEC_DST_BUFLGTH_MAX        (0xffff)
#define SOCP_DEC_DST_TH_MAX             (0xff)

// ����Ŀ��buffer�����ж�״̬�Ĵ���16-22λָʾ��ֵ����ж�
#define SOCP_ENC_DST_BUFF_THRESHOLD_OVF_MASK    (0x007f0000)
#define SOCP_ENC_DST_BUFF_OVF_MASK              (0x0000007f)
// ��ֵ�жϼĴ�����ʼλ
#define SOCP_ENC_DST_BUFF_THRESHOLD_OVF_BEGIN   (16)

#define SOCP_RESET_TIME                 (1000)
#define SOCP_GBLRESET_TIME              (100)

extern SOCP_GBL_STATE g_strSocpStat;

/* ����Ƿ��ʼ���ĺ궨�� */
#define SOCP_CHECK_INIT() \
    do{\
        if (!g_strSocpStat.bInitFlag)\
        {\
            socp_printf("the module has not been initialized!\n");\
            return BSP_ERR_SOCP_NOT_INIT;\
        }\
    }while(0)

/* �������Ƿ���Ч */
#define SOCP_CHECK_PARA(para) \
    do{\
        if (0 == para)\
        {\
            socp_printf("the parameter is NULL!\n");\
            return BSP_ERR_SOCP_NULL;\
        }\
    }while(0)

#define SOCP_CHECK_BUF_ADDR(start, end) \
    do{\
        if (start >= end)\
        {\
            socp_printf("the buff is valid!\n");\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)


#define SOCP_CHECK_CHAN_TYPE(para, type) \
    do{\
        if (type != para)\
        {\
            socp_printf("the Chan's Type is Valid!\n");\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

#define SOCP_CHECK_CHAN_ID(para, id) \
    do{\
        if (para >= id)\
        {\
            socp_printf("the Chan Id is Valid!\n");\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

#define SOCP_CHECK_ENCSRC_CHAN_ID(id) \
    do {\
        if ((id >= SOCP_CCORE_ENCSRC_CHN_BASE) && (id < (SOCP_CCORE_ENCSRC_CHN_BASE + SOCP_CCORE_ENCSRC_CHN_NUM)))\
        {\
            socp_printf("the Chan Id is Valid!\n"); \
            return BSP_ERR_SOCP_INVALID_CHAN; \
        } \
    } while (0)

/* ����Ƿ�8�ֽڶ��� */
#define SOCP_CHECK_8BYTESALIGN(para) \
    do{\
        if (0 != (para%8))\
        {\
            socp_printf("the parameter is not 8 bytes aligned!\n");\
            return BSP_ERR_SOCP_NOT_8BYTESALIGN;\
        }\
    }while(0)

#define SOCP_CHECK_ENCSRC_CHNMODE(para) \
    do{\
        if (para >= SOCP_ENCSRC_CHNMODE_BUTT)\
        {\
            socp_printf("encoder src channele mode is %d, which is valid!\n", para);\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)

#define SOCP_CHECK_DECSRC_CHNMODE(para) \
    do{\
        if (para >= SOCP_DECSRC_CHNMODE_BUTT)\
        {\
            socp_printf("decoder dst channele mode is %d, which is valid!\n", para);\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)

#define SOCP_CHECK_CHAN_PRIORITY(para) \
    do{\
        if (para >= SOCP_CHAN_PRIORITY_BUTT)\
        {\
            socp_printf("encoder src channele priority is %d, which is valid!\n", para);\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)

#define SOCP_CHECK_DATA_TYPE(para) \
    do{\
        if (para >= SOCP_DATA_TYPE_BUTT)\
        {\
            socp_printf("channel data type is %d, which is valid!\n", para);\
            return BSP_ERR_SOCP_INVALID_PARA;\
        }\
    }while(0)

#define SOCP_CHECK_ENCSRC_ALLOC(id) \
    do{\
        if(SOCP_CHN_ALLOCATED != g_strSocpStat.sEncSrcChan[id].u32AllocStat)\
        {\
            socp_printf("encoder src[%d] not allocated!\n", id);\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

#define SOCP_CHECK_ENCDST_SET(id) \
    do{\
        if(SOCP_CHN_SET!= g_strSocpStat.sEncDstChan[id].u32SetStat)\
        {\
            socp_printf("encoder dst[%d] set failed!\n", id);\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

#define SOCP_CHECK_DECSRC_SET(id) \
    do{\
        if(SOCP_CHN_SET!= g_strSocpStat.sDecSrcChan[id].u32SetStat)\
        {\
            socp_printf("decoder[%d] src set failed!\n", id);\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

#define SOCP_CHECK_DECDST_ALLOC(id) \
    do{\
        if(SOCP_CHN_ALLOCATED!= g_strSocpStat.sDecDstChan[id].u32AllocStat)\
        {\
            socp_printf("decoder dst[%d] alloc failed!\n", id);\
            return BSP_ERR_SOCP_INVALID_CHAN;\
        }\
    }while(0)

#define SOCP_CHECK_DATA_TYPE_EN(param) \
    do {\
        if (param >= SOCP_DATA_TYPE_EN_BUTT)\
        {\
            socp_printf("the data type en is valid, para is %d!\n", param); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)

#define SOCP_CHECK_ENC_DEBUG_EN(param) \
    do {\
        if (param >= SOCP_ENC_DEBUG_EN_BUTT)\
        {\
            socp_printf("the enc src debug en is valid, para is %d!\n", param); \
            return BSP_ERR_SOCP_INVALID_PARA; \
        } \
    } while (0)


/**************************************************************************
  ��������
**************************************************************************/
s32 socp_soft_free_encdst_chan(u32 u32EncDstChanId);
s32 socp_soft_free_decsrc_chan(u32 u32DecSrcChanId);
s32 socp_reset_dec_chan(u32 u32ChanID);
s32 socp_get_index(u32 u32Size,u32 *index);
u32 BSP_SOCP_CanSleep(void);
s32 socp_can_sleep(void);

/* log2.0 2014-03-19 Begin:*/
s32 bsp_socp_set_log_cfg(struct socp_enc_dst_log_cfg * cfg);
u32 socp_is_encdst_chan_empty(void);
/* log2.0 2014-03-19 End:*/

void socp_get_dst_chan_buffer(u32 size);

void socp_help(void);

#define BSP_REG_SETBITS(base, reg, pos, bits, val) (BSP_REG(base, reg) = (BSP_REG(base, reg) & (~((((u32)1 << (bits)) - 1) << (pos)))) \
                                                                         | ((u32)((val) & (((u32)1 << (bits)) - 1)) << (pos)))
#define BSP_REG_GETBITS(base, reg, pos, bits) ((BSP_REG(base, reg) >> (pos)) & (((u32)1 << (bits)) - 1))

#define SOCP_REG_WRITE(reg, data) (writel(data, (volatile void *)(g_strSocpStat.baseAddr + reg)))
#define SOCP_REG_READ(reg, result) (result = readl((const volatile void *)(g_strSocpStat.baseAddr + reg)))

#define SOCP_REG_SETBITS(reg, pos, bits, val) BSP_REG_SETBITS(g_strSocpStat.baseAddr, reg, pos, bits, val)
#define SOCP_REG_GETBITS(reg, pos, bits) BSP_REG_GETBITS(g_strSocpStat.baseAddr, reg, pos, bits)

#define BBP_REG_WRITE(reg, data) (writel(data, (volatile void *)(g_strSocpStat.armBaseAddr + reg)))
#define BBP_REG_READ(reg, result) (result = readl((const volatile void *)(g_strSocpStat.armBaseAddr + reg)))

#define BBP_REG_SETBITS(reg, pos, bits, val) BSP_REG_SETBITS(g_strSocpStat.armBaseAddr, reg, pos, bits, val)
#define BBP_REG_GETBITS(reg, pos, bits) BSP_REG_GETBITS(g_strSocpStat.armBaseAddr, reg, pos, bits)
/**************************************************************************/
#if 0
#define SOCP_FLUSH_CACHE(ptr, size) __dma_single_cpu_to_dev(ptr, size, 1)
#define SOCP_INVALID_CACHE(ptr, size) __dma_single_dev_to_cpu(ptr, size, 2)
#else
#define SOCP_FLUSH_CACHE(ptr, size)  (0)
#define SOCP_INVALID_CACHE(ptr, size) (0)
#endif


#if defined(__KERNEL__)

#define Socp_Memcpy(dst,src,len)       (void)memcpy(dst,src,len)
#define Socp_Memset(src,count,len)     (void)memset(src,count,len)

#elif defined(__OS_VXWORKS__)

#define Socp_Memcpy(dst,src,len)       (void)memcpy(dst,src,len)
#define Socp_Memset(src,count,len)     (void)memset(src,count,len)

#elif defined(__OS_RTOSCK__)

#define Socp_Memcpy(dst,src,len)       (void)memcpy_s(dst,len,src,len)
#define Socp_Memset(src,count,len)     (void)memset_s(src, len, count,len)

#endif
#define socp_printf(fmt,...)     bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_SOCP,fmt,##__VA_ARGS__)

#ifdef __cplusplus
}
#endif

#endif



