/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : oal_sdio.h
  �� �� ��   : ����
  ��    ��   : z00262551
  ��������   : 2012��11��7��
  ����޸�   :
  ��������   : oal_sdio.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��20��
    ��    ��   : z00262551
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_SDIO_H__
#define __OAL_SDIO_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#ifdef  CONFIG_HI110X_SDIO_STD_CARD_SUPPORT
#define HISDIO_VENDOR_ID_HISI                      0x0296      /* VENDOR ID */
#define HISDIO_PRODUCT_ID_HISI                     0x5347      /* Product 1102 */
#else
#define HISDIO_VENDOR_ID_HISI                      0x22D1      /* VENDOR ID */
#define HISDIO_PRODUCT_ID_HISI                     0x1101      /* Product 1102 */
#endif


#define SDIO_MAX_CONTINUS_RX_COUNT          64          /* sdio max continus rx cnt */


#define HISDIO_REG_FUNC1_FIFO                      0x00        /* Read Write FIFO */
#define HISDIO_REG_FUNC1_INT_STATUS                0x08        /* interrupt mask and clear reg */
#define HISDIO_REG_FUNC1_INT_ENABLE                0x09        /* interrupt */
#define HISDIO_REG_FUNC1_XFER_COUNT                0x0c        /* notify number of bytes to be read */
#define HISDIO_REG_FUNC1_WRITE_MSG                 0x24        /* write msg to device */
#define HISDIO_REG_FUNC1_MSG_FROM_DEV              0x28        /* notify Host that device has got the msg */
#define HISDIO_REG_FUNC1_MSG_HIGH_FROM_DEV         0x2b        /* notify Host that device has got the msg, Host receive the msg ack */


/*sdio extend function, add 64B register for hcc*/
#define HISDIO_FUNC1_EXTEND_REG_BASE        0x3c
#define HISDIO_FUNC1_EXTEND_REG_LEN         64

#define HISDIO_FUNC1_INT_DREADY      (1 << 0)           /* data ready interrupt */
#define HISDIO_FUNC1_INT_RERROR      (1 << 1)           /* data read error interrupt */
#define HISDIO_FUNC1_INT_MFARM       (1 << 2)           /* ARM Msg interrupt */
#define HISDIO_FUNC1_INT_ACK         (1 << 3)           /* ACK interrupt */

//#define HISDIO_FUNC1_INT_MASK        (HISDIO_FUNC1_INT_DREADY | HISDIO_FUNC1_INT_RERROR | HISDIO_FUNC1_INT_MFARM | HISDIO_FUNC1_INT_ACK)
#define HISDIO_FUNC1_INT_MASK        (HISDIO_FUNC1_INT_DREADY | HISDIO_FUNC1_INT_RERROR | HISDIO_FUNC1_INT_MFARM )

/* Device to Host Msg */
#if 0
#define HISDIO_MSG_FLOW_ON           (1 << 2)    /* can transfer */
#define HISDIO_MSG_FLOW_OFF          (1 << 1)    /* can't transfer */
#define HISDIO_MSG_VERIFY_ERROR      (1 << 3)

#define HISDIO_MSG_DEVICE_ERROR      (1 << 7)   /*device is abort*/
#define HISDIO_MSG_DEVICE_NO_RX      (1 << 8)   /*device is norx */

#define HISDIO_MSG_RESET_FLOWCTRL    (1 << 0)    /* reset device flowctrl */
#define HISDIO_MSG_ALLOWSLEEP        (1 << 5)   /* allow Device to sleep */
#define HISDIO_MSG_FORBIDSLEEP       (1 << 6)   /* forbid Device sleep */

#define HISDIO_MSG_DISCONN           (1 << 0)

#define HISDIO_MSG_DEV_PRE_SHUTDOWN_REPLY       ((1<<7)|(1<<30))
#endif

#define HISDIO_RX_THREAD_NICE    (-20)
#define HISDIO_SDIO_RX_THREAD_POLICY             SCHED_FIFO
#define HISDIO_GPIO_RXDATA_THREAD_PRIORITY       (20)
#define HISDIO_SDIO_DISPOSE_THREAD_PRIORITY      (10)


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_sdio.h */

