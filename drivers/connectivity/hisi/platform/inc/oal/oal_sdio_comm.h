/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : sdio_comm.h
  �� �� ��   : ����
  ��    ��   : z00262551
  ��������   : 2012��11��24��
  ����޸�   :
  ��������   : host/device ������Ϣ���ͷ�ļ�,host/device �ӿڻ��Ʋ����
			 �ӿڲ�Ҫ��������һ�����ǽṹ�壬��ö�ٵȹ�����Ϣ��Ҫ�ŵ����ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��11��24��
    ��    ��   : z00262551
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __OAL_SDIO_COMM_H__
#define __OAL_SDIO_COMM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

//#define CONFIG_SDIO_DEBUG
#undef CONFIG_SDIO_DEBUG
#define CONFIG_SDIO_FUNC_EXTEND
//#undef CONFIG_SDIO_FUNC_EXTEND

#define CONFIG_SDIO_MSG_FLOWCTRL
//#undef CONFIG_SDIO_MSG_FLOWCTRL
#undef CONFIG_CREDIT_MSG_FLOW_CTRL_DEBUG

#undef CONFIG_SDIO_REINIT_SUPPORT

/*SDIO����ʱ�������е�SG LIST �ϲ���һ���������ڴ淢��!*/
#define CONFIG_HISDIO_H2D_SCATT_LIST_ASSEMBLE

/*����˺��ʾ��arm to host ����Ϣ�ض�ACK��
  ��Ϣ�Ǵ�ARM������host,
  ��������ֽڲ��ܲ���ACK*/
#define CONFIG_SDIO_D2H_MSG_ACK

/*����˺��ʾ��host to arm ����Ϣ�ض�ACK��
  ��Ϣ�Ǵ�Host������ARM,
  ��������ֽڲ��ܲ���ACK*/
#undef CONFIG_SDIO_H2D_MSG_ACK
/*Device to host sdio message type*/
typedef enum _HISDIO_D2H_MSG_TYPE_{
    D2H_MSG_WLAN_READY = 0,
	D2H_MSG_FLOWCTRL_UPDATE = 1,/*For the credit flow ctrl*/
	D2H_MSG_FLOWCTRL_OFF =2,/*can't send data*/
	D2H_MSG_FLOWCTRL_ON =3, /*can send data*/
	D2H_MSG_WAKEUP_SUCC =4, /*Wakeup done*/
	D2H_MSG_ALLOW_SLEEP =5, /*ALLOW Sleep*/
	D2H_MSG_DISALLOW_SLEEP = 6, /*DISALLOW Sleep*/
	D2H_MSG_DEVICE_PANIC =7, /*arm abort*/
	D2H_MSG_POWEROFF_ACK = 8, /* Poweroff cmd ack*/
	D2H_MSG_OPEN_BCPU_ACK = 9, /* OPEN BCPU cmd ack*/
	D2H_MSG_CLOSE_BCPU_ACK = 10, /* CLOSE BCPU cmd ack*/
    D2H_MSG_CREDIT_UPDATE = 11,  /* update high priority buffer credit value */
    D2H_MSG_HIGH_PKT_LOSS = 12,  /* high pri pkts loss count */
    D2H_MSG_HALT_BCPU = 13,      /*halt bcpu ack*/

    D2H_MSG_COUNT = 16 /*max support msg count*/
}HISDIO_D2H_MSG_TYPE;


/*Host to device sdio message type*/
typedef enum _HISDIO_H2D_MSG_TYPE_{
    H2D_MSG_FLOWCTRL_ON         = 0,/*can send data, force to open*/
    H2D_MSG_DEVICE_INFO_DUMP    = 1,
    H2D_MSG_DEVICE_MEM_DUMP     = 2,
    H2D_MSG_TEST                = 3,
    H2D_MSG_PM_WLAN_OFF         = 4,
    H2D_MSG_SLEEP_REQ           = 5,
    H2D_MSG_PM_DEBUG            = 6,

    H2D_MSG_RESET_BCPU          = 7,
    H2D_MSG_QUERY_RF_TEMP       = 8,


    H2D_MSG_HCC_SLAVE_THRUPUT_BYPASS = 9,
    H2D_MSG_DEVICE_MEM_INFO          = 10,
    H2D_MSG_STOP_SDIO_TEST		= 11,
    H2D_MSG_PM_BCPU_OFF         = 12,
    H2D_MSG_HALT_BCPU           =13,

    H2D_MSG_COUNT = 16 /*max support msg count*/
}HISDIO_H2D_MSG_TYPE;

/*sdio flow control info, free cnt*/
#define HISDIO_SHORT_PKT_SET(reg, num)    do{reg = (((reg) & 0xFFFFFF00) | (((num) & 0xFF)));}while(0)
#define HISDIO_LARGE_PKT_SET(reg, num)    do{reg = (((reg) & 0xFFFF00FF) | (((num) & 0xFF) << 8));}while(0)
#define HISDIO_RESERVE_PKT_SET(reg, num)  do{reg = (((reg) & 0xFF00FFFF) | (((num) & 0xFF) << 16));}while(0)
#define HISDIO_COMM_REG_SEQ_SET(reg, num) do{reg = (((reg) & 0x00FFFFFF) | (((num) & 0xFF) << 24));}while(0)

#define HISDIO_SHORT_PKT_GET(reg)           ((reg) & 0xFF)
#define HISDIO_LARGE_PKT_GET(reg)           (((reg) >> 8) & 0xFF)
#define HISDIO_RESERVE_PKT_GET(reg)         (((reg) >> 16) & 0xFF)
#define HISDIO_COMM_REG_SEQ_GET(reg)        (((reg) >> 24) & 0xFF)


#define HISDIO_BLOCK_SIZE                     512         /* one size of data transfer block size,
                                                         * 64, 128, 256, 512, 1024 */
/*The max scatter buffers when host to device*/
#define HISDIO_HOST2DEV_SCATT_MAX       (64)
#define HISDIO_HOST2DEV_SCATT_SIZE      (64)

/*The max scatter buffers when device to host*/
#define HISDIO_DEV2HOST_SCATT_MAX       (64)

/*The max scatt num of rx and tx*/
#define HISDIO_SCATT_MAX_NUM    (HISDIO_DEV2HOST_SCATT_MAX)

/*64B used to store the scatt info,1B means 1 pkt.*/
#define HISDIO_H2D_SCATT_BUFFLEN_ALIGN_BITS     (3)
/*1 << 5*/
/*Host to device's descr align length depends on the
   CONFIG_HISDIO_H2D_SCATT_LIST_ASSEMBLE*/
#ifdef CONFIG_HISDIO_H2D_SCATT_LIST_ASSEMBLE
#define HISDIO_H2D_SCATT_BUFFLEN_ALIGN    (8)
#else
#define HISDIO_H2D_SCATT_BUFFLEN_ALIGN    (32)
#endif

/*Device To Host,descr just request 4 bytes aligned,
  but 10 bits round [0~1023], so we also aligned to 32 bytes*/
#define HISDIO_D2H_SCATT_BUFFLEN_ALIGN_BITS     (5)
/*1 << 5*/
#define HISDIO_D2H_SCATT_BUFFLEN_ALIGN    (512)


#define HSDIO_HOST2DEV_PKTS_MAX_LEN     (1544)
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

