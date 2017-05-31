/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : Hi6210-pcm.h
  �� �� ��   : ����
  ��    ��   : ʯ���� s00212991
  ��������   : 2012��7��31��
  ����޸�   :
  ��������   : Hi6210-pcm.h ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��7��31��
    ��    ��   : ʯ���� s00212991
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef HI6210_PCM_H
#define HI6210_PCM_H


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define HI_CHN_COMMON   \
	unsigned short  msg_type;   \
	unsigned short  reserved;   \
	unsigned short  pcm_mode;   \
	unsigned short  reserved1;


#define INT_TO_ADDR(low,high) (void*) (unsigned long)((unsigned long long)(low) | ((unsigned long long)(high)<<32))
#define GET_LOW32(x) (unsigned int)(((unsigned long long)(unsigned long)(x))&0xffffffffULL)
#define GET_HIG32(x) (unsigned int)((((unsigned long long)(unsigned long)(x))>>32)&0xffffffffULL)
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

/* HI6210 PCM����״̬ */
enum HI6210_STATUS
{
	STATUS_STOP = 0,
	STATUS_RUNNING = 1,
	STATUS_STOPPING = 2
};

/* AP��HIFI��Ƶ���ݴ�����Ϣ���� */
#if 1
/*temp add*/
enum AUDIO_MSG_ENUM
{
	/* AP DSP������HIFI������ͨ��ģ�齻����ϢID */
	ID_AP_AUDIO_PLAY_DECODE_REQ         = 0xDD33,
	ID_AUDIO_AP_PLAY_DECODE_RSP         = 0xDD34,

	ID_AP_AUDIO_RECORD_START_REQ        = 0xDD40,
	ID_AP_AUDIO_RECORD_STOP_REQ         = 0xDD41,

	/* AP��Ƶ������HIFI��Ƶͨ��ģ�齻����ϢID */
	ID_AP_AUDIO_PCM_OPEN_REQ            = 0xDD25,
	ID_AP_AUDIO_PCM_CLOSE_REQ           = 0xDD26,
	ID_AP_AUDIO_PCM_HW_PARA_REQ         = 0xDD27,
	ID_AP_AUDIO_PCM_HW_FREE_REQ         = 0xDD28,   /* ��δʹ�ã����� */
	ID_AP_AUDIO_PCM_PREPARE_REQ         = 0xDD29,   /* ��δʹ�ã����� */
	ID_AP_AUDIO_PCM_TRIGGER_REQ         = 0xDD2A,
	ID_AP_AUDIO_PCM_POINTER_REQ         = 0xDD2B,   /* ��δʹ�ã����� */
	ID_AP_AUDIO_PCM_SET_BUF_CMD         = 0xDD2C,
	ID_AUDIO_AP_PCM_PERIOD_ELAPSED_CMD  = 0xDD2D,

	/* HIFI��Ƶͨ��ģ���ڲ�������ϢID */
	ID_AUDIO_UPDATE_PLAY_BUFF_CMD       = 0xDD2E,
	ID_AUDIO_UPDATE_CAPTURE_BUFF_CMD    = 0xDD2F,
	ID_AUDIO_AP_PCM_TRIGGER_CNF         = 0xDDA0
};
typedef unsigned short  AUDIO_MSG_ENUM_UINT16;

enum HIFI_CHN_MSG_TYPE
{
	HI_CHN_MSG_PCM_OPEN             = ID_AP_AUDIO_PCM_OPEN_REQ,
	HI_CHN_MSG_PCM_CLOSE            = ID_AP_AUDIO_PCM_CLOSE_REQ,
	HI_CHN_MSG_PCM_HW_PARAMS        = ID_AP_AUDIO_PCM_HW_PARA_REQ,
	HI_CHN_MSG_PCM_HW_FREE          = ID_AP_AUDIO_PCM_HW_FREE_REQ,
	HI_CHN_MSG_PCM_PREPARE          = ID_AP_AUDIO_PCM_PREPARE_REQ,
	HI_CHN_MSG_PCM_TRIGGER          = ID_AP_AUDIO_PCM_TRIGGER_REQ,
	HI_CHN_MSG_PCM_POINTER          = ID_AP_AUDIO_PCM_POINTER_REQ,
	/* ���ݰ��� */
	HI_CHN_MSG_PCM_SET_BUF          = ID_AP_AUDIO_PCM_SET_BUF_CMD,
	/* HIFI���ݰ������*/
	HI_CHN_MSG_PCM_PERIOD_ELAPSED   = ID_AUDIO_AP_PCM_PERIOD_ELAPSED_CMD,
	HI_CHN_MSG_PCM_PERIOD_STOP      = ID_AUDIO_AP_PCM_TRIGGER_CNF,
};
#else
enum HIFI_CHN_MSG_TYPE
{
	HI_CHN_MSG_PCM_OPEN             = 0,
	HI_CHN_MSG_PCM_CLOSE            ,
	HI_CHN_MSG_PCM_HW_PARAMS        ,
	HI_CHN_MSG_PCM_HW_FREE          ,
	HI_CHN_MSG_PCM_PREPARE          ,
	HI_CHN_MSG_PCM_TRIGGER          ,
	HI_CHN_MSG_PCM_POINTER          ,
	/* ���ݰ��� */
	HI_CHN_MSG_PCM_SET_BUF          ,
	/* HIFI���ݰ������*/
	HI_CHN_MSG_PCM_PERIOD_ELAPSED
};
#endif

enum IRQ_RT
{
	/* IRQ Not Handled as Other problem */
	IRQ_NH_OTHERS    = -5,
	/* IRQ Not Handled as Mailbox problem */
	IRQ_NH_MB     = -4,
	/* IRQ Not Handled as pcm MODE problem */
	IRQ_NH_MODE     = -3,
	/* IRQ Not Handled as TYPE problem */
	IRQ_NH_TYPE     = -2,
	/* IRQ Not Handled */
	IRQ_NH          = -1,
	/* IRQ HanDleD */
	IRQ_HDD         = 0,
	/* IRQ HanDleD related to PoinTeR */
	IRQ_HDD_PTR     = 1,
	/* IRQ HanDleD related to STATUS */
	IRQ_HDD_STATUS,
	/* IRQ HanDleD related to SIZE */
	IRQ_HDD_SIZE,
	/* IRQ HanDleD related to PoinTeR of Substream */
	IRQ_HDD_PTRS,
	/* IRQ HanDleD Error */
	IRQ_HDD_ERROR,
};
typedef enum IRQ_RT irq_rt_t;

typedef irq_rt_t (*irq_hdl_t)(void *, unsigned int);

/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/

/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/

/*****************************************************************************s
  6 STRUCT����
*****************************************************************************/

#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
struct hi6210_simu_pcm_data
{
	struct workqueue_struct *simu_pcm_delay_wq;
	struct delayed_work  simu_pcm_delay_work;

	unsigned short  msg_type;   /* ��Ϣ���ͣ�HIFI_CHN_MSG_TYPE */
	unsigned short  reserved;   /* reserved for aligned */
	unsigned short  pcm_mode;   /* PLAYBACK �� CAPTURE */
	unsigned short  tg_cmd;     /* ��������,����SNDRV_PCM_TRIGGER_START */
	void *          substream;  /* ͨ��SubStream����ĵ�ַ */
	unsigned int    data_addr;  /* DMA���ݰ��˵�����ָ�룬�����ַ */
	unsigned int    data_len;   /* ���ݳ��ȣ���λByte */
};
#endif

#ifdef __DRV_AUDIO_MAILBOX_WORK__
struct hi6210_pcm_mailbox_data
{
	struct list_head node;
	unsigned short   msg_type;   /* ��Ϣ���ͣ�HIFI_CHN_MSG_TYPE */
	unsigned short   pcm_mode;   /* PLAYBACK �� CAPTURE */
	void *           substream;  /* ͨ��SubStream����ĵ�ַ */
};
#endif

/* runtime data������PLAYBACK��CAPTURE */
struct hi6210_runtime_data
{
	spinlock_t          lock;         /* protect hi6210_runtime_data */
	unsigned int        period_next;  /* record which period to fix dma next time */
	unsigned int        period_cur;   /* record which period using now */
	unsigned int        period_size;  /* DMA SIZE */
	enum HI6210_STATUS  status;       /* pcm status running or stop */
#ifdef __DRV_AUDIO_MAILBOX_WORK__
	struct hi6210_pcm_mailbox_data hi6210_pcm_mailbox;
#endif
#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
	struct hi6210_simu_pcm_data hi6210_simu_pcm;
#endif
};

/* AP�˼�ͨ�Ŵ��ݸ�HIFI�����ݣ���PCM OPENʱʹ�õĽṹ����Ϣ */
struct hifi_chn_pcm_open
{
	HI_CHN_COMMON
};

/* AP�˼�ͨ�Ŵ��ݸ�HIFI�����ݣ���PCM OPENʱʹ�õĽṹ����Ϣ */
struct hifi_chn_pcm_close
{
	HI_CHN_COMMON
};

/* AP�˼�ͨ�Ŵ��ݸ�HIFI�����ݣ���HW PARAMSʱʹ�õĽṹ����Ϣ */
struct hifi_chn_pcm_hw_params
{
	HI_CHN_COMMON
	unsigned int    channel_num;    /* ͨ���������� */
	unsigned int    sample_rate;    /* ͨ�������� */
	unsigned int    format;         /* ��Ƶ��ʽ */
};

/* AP�˼�ͨ�Ŵ��ݸ�HIFI�����ݣ���HW FREEʱʹ�õĽṹ����Ϣ
struct hifi_chn_pcm_hw_free
{
    HI_CHN_COMMON
};*/

/* AP�˼�ͨ�Ŵ��ݸ�HIFI�����ݣ���PCM PREPAREʱʹ�õĽṹ����Ϣ
struct hifi_chn_pcm_prepare
{
    HI_CHN_COMMON
};*/

/* AP�˼�ͨ�Ŵ��ݸ�HIFI�����ݣ���PCM TRIGGERʱʹ�õĽṹ����Ϣ */
struct hifi_chn_pcm_trigger
{
	unsigned short  msg_type;       /* ��Ϣ���ͣ�HIFI_CHN_MSG_TYPE */
	unsigned short  reserved;       /* reserved for aligned */
	unsigned short  pcm_mode;       /* PLAYBACK �� CAPTURE */
	unsigned short  tg_cmd;         /* ��������,����SNDRV_PCM_TRIGGER_START */
	unsigned short  enPcmObj;       /* �����Ķ���ΪAP����Hifi */
	unsigned short  reserved1;      /* reserved for aligned */
	unsigned int    substream_l32;  /* ͨ��SubStream����ĵ�ַ */
	unsigned int    substream_h32;  /* ͨ��SubStream����ĵ�ַ */
	unsigned int    data_addr;      /* DMA���ݰ��˵�����ָ�룬�����ַ */
	unsigned int    data_len;       /* ���ݳ��ȣ���λByte */
};

/* AP�˼�ͨ�Ŵ��ݸ�HIFI�����ݣ�DMA Buffer���ݴ���ʱʹ�� */
struct hifi_channel_set_buffer
{
	HI_CHN_COMMON
	unsigned int    data_addr;  /* DMA���ݰ��˵�����ָ�룬�����ַ
									   PLAYBACKʱ��ΪDMA���ݰ���Դ
									   CAPTURE ʱ��ΪDMA���ݰ���Ŀ�ĵ� */
	unsigned int    data_len;   /* ���ݳ��ȣ���λByte */
};

/* HIFI�˼�ͨ�Ŵ��ݸ�AP�����ݣ���DMA���ݰ�����ɺ󴫵� */
struct hifi_chn_pcm_period_elapsed
{
	HI_CHN_COMMON
	unsigned int    substream_l32;  /* ͨ��SubStream����ĵ�ַ */
	unsigned int    substream_h32;  /* ͨ��SubStream����ĵ�ַ */
};



/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /*HI6210_PCM_H*/
