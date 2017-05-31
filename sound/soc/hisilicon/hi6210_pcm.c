/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : hi6210_pcm.c
  �� �� ��   : ����
  ��    ��   : ʯ���� s00212991
  ��������   : 2012��7��31��
  ����޸�   :
  ��������   : xxxx
  �����б�   :
              hi6210_exit
              hi6210_init
              hi6210_intr_handle_cp
              hi6210_intr_handle_pb
              hi6210_c
              hi6210_mb_intr_handle
              hi6210_notify_isr_register
              hi6210_notify_pcm_close
              hi6210_notify_pcm_hw_free
              hi6210_notify_pcm_hw_params
              hi6210_notify_pcm_open
              hi6210_notify_pcm_prepare
              hi6210_notify_pcm_set_buf
              hi6210_notify_pcm_trigger
              hi6210_notify_recv_isr
              hi6210_pcm_close
              hi6210_pcm_free
              hi6210_pcm_hifi_close
              hi6210_pcm_hifi_hw_free
              hi6210_pcm_hifi_hw_params
              hi6210_pcm_hifi_open
              hi6210_pcm_hifi_pointer
              hi6210_pcm_hifi_prepare
              hi6210_pcm_hifi_trigger
              hi6210_pcm_hw_free
              hi6210_pcm_hw_params
              hi6210_pcm_new
              hi6210_pcm_open
              hi6210_pcm_pointer
              hi6210_pcm_prepare
              hi6210_pcm_trigger
              hi6210_platform_probe
              hi6210_platform_remove
              status_read_proc_hstatus
              status_write_proc_hstatus
  �޸���ʷ   :
  1.��    ��   : 2012��7��31��
    ��    ��   : ʯ���� s00212991
    �޸�����   : �����ļ�

******************************************************************************/

/*
the 2 MACRO should be used seperately
CONFIG_SND_TEST_AUDIO_PCM_LOOP : for ST, simu data send of mailbox
__DRV_AUDIO_MAILBOX_WORK__   : leave mailbox's work to workqueue
*/
#ifndef CONFIG_SND_TEST_AUDIO_PCM_LOOP
#define __DRV_AUDIO_MAILBOX_WORK__
#endif

/*****************************************************************************
  1 ͷ�ļ�����
 *****************************************************************************/
#include <linux/module.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
#include <linux/time.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/kernel.h>
#include <linux/mutex.h>
#include <linux/proc_fs.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/sched/rt.h>


#include <linux/hisi/hilog.h>

#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include "hifi_lpp.h"

#ifdef CONFIG_HIFI_MAILBOX
#include "drv_mailbox_cfg.h"
//#include "../../../drivers/hisi/hifi_mailbox/mailbox/drv_mailbox_cfg.h"
#endif

#ifdef CONFIG_HI6XXX_MAILBOX_MULTICORE
#include <../../../drivers/hisi/mailbox/hi6xxx_mailbox/drv_mailbox.h>
#endif

#include "hi6210_pcm.h"
#include "hi6210_log.h"

/*lint -e750*/

/*****************************************************************************
  2 �궨��
 *****************************************************************************/

#define HI6210_PCM "hi6210-hifi"
/*
 * PLAYBACK SUPPORT FORMATS
 * BITS : 8/16/24  18/20
 * LITTLE_ENDIAN / BIG_ENDIAN
 * MONO / STEREO
 * UNSIGNED / SIGNED
 */
#define HI6210_PB_FORMATS  (SNDRV_PCM_FMTBIT_S8 | \
		SNDRV_PCM_FMTBIT_U8 | \
		SNDRV_PCM_FMTBIT_S16_LE | \
		SNDRV_PCM_FMTBIT_S16_BE | \
		SNDRV_PCM_FMTBIT_U16_LE | \
		SNDRV_PCM_FMTBIT_U16_BE | \
		SNDRV_PCM_FMTBIT_S24_LE | \
		SNDRV_PCM_FMTBIT_S24_BE | \
		SNDRV_PCM_FMTBIT_U24_LE | \
		SNDRV_PCM_FMTBIT_U24_BE)

/*
 * PLAYBACK SUPPORT RATES
 * 8/11.025/16/22.05/32/44.1/48/88.2/96kHz
 */
#define HI6210_PB_RATES    (SNDRV_PCM_RATE_8000_48000 | \
		SNDRV_PCM_RATE_88200 | \
		SNDRV_PCM_RATE_96000)

#define HI6210_PB_MIN_CHANNELS  ( 1 )
#define HI6210_PB_MAX_CHANNELS  ( 2 )
/* Assume the FIFO size */
#define HI6210_PB_FIFO_SIZE     ( 16 )

/* CAPTURE SUPPORT FORMATS : SIGNED 16/24bit */
#define HI6210_CP_FORMATS  ( SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S24_LE)

/* CAPTURE SUPPORT RATES : 48/96kHz */
#define HI6210_CP_RATES    ( SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000 )

#define HI6210_CP_MIN_CHANNELS  ( 1 )
#define HI6210_CP_MAX_CHANNELS  ( 6 )
/* Assume the FIFO size */
#define HI6210_CP_FIFO_SIZE     ( 32 )
#define HI6210_MODEM_RATES      ( SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 )
#define HI6210_BT_RATES         ( SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 )
#define HI6210_FM_RATES         ( SNDRV_PCM_RATE_8000 | SNDRV_PCM_RATE_16000 )

#define HI6210_MAX_BUFFER_SIZE  ( 192 * 1024 )    /* 0x30000 */
#define HI6210_BUFFER_SIZE_MM   ( 32 * 1024 )
#define HI6210_MIN_BUFFER_SIZE  ( 32 )
#define HI6210_MAX_PERIODS      ( 32 )
#define HI6210_MIN_PERIODS      ( 2 )
#define HI6210_WORK_DELAY_1MS   ( 33 )    /* 33 equals 1ms */
#define HI6210_CYC_SUB(Cur, Pre, CycLen)                    \
	(((Cur) < (Pre)) ? (((CycLen) - (Pre)) + (Cur)) : ((Cur) - (Pre))) /* ���Ǹ�����Χ��ѭ��, ��������������Ĳ� */

#ifndef OK
#define OK              0
#endif
#ifndef ERROR
#define ERROR           -1
#endif

#undef NULL
#define NULL ((void *)0)

#define PCM_DMA_BUF_PLAYBACK_LEN    (0x00030000)
#define PCM_DMA_BUF_0_PLAYBACK_BASE (PCM_PLAY_BUFF_LOCATION)
#define PCM_DMA_BUF_0_PLAYBACK_LEN  (PCM_DMA_BUF_PLAYBACK_LEN)
#define PCM_DMA_BUF_0_CAPTURE_BASE  (PCM_DMA_BUF_0_PLAYBACK_BASE+PCM_DMA_BUF_0_PLAYBACK_LEN)
#define PCM_DMA_BUF_0_CAPTURE_LEN   (PCM_DMA_BUF_PLAYBACK_LEN)

#define PCM_DMA_BUF_1_PLAYBACK_BASE (PCM_DMA_BUF_0_CAPTURE_BASE+PCM_DMA_BUF_0_CAPTURE_LEN)
#define PCM_DMA_BUF_1_PLAYBACK_LEN  (PCM_DMA_BUF_PLAYBACK_LEN)
#define PCM_DMA_BUF_1_CAPTURE_BASE  (PCM_DMA_BUF_1_PLAYBACK_BASE+PCM_DMA_BUF_1_PLAYBACK_LEN)
#define PCM_DMA_BUF_1_CAPTURE_LEN   (64*1024)

#define PCM_DMA_BUF_2_PLAYBACK_BASE (PCM_DMA_BUF_1_CAPTURE_BASE+PCM_DMA_BUF_1_CAPTURE_LEN)
#define PCM_DMA_BUF_2_PLAYBACK_LEN  (PCM_DMA_BUF_PLAYBACK_LEN)
#define PCM_DMA_BUF_2_CAPTURE_BASE  (PCM_DMA_BUF_2_PLAYBACK_BASE+PCM_DMA_BUF_2_PLAYBACK_LEN)
#define PCM_DMA_BUF_2_CAPTURE_LEN   (0)

#define PCM_DMA_BUF_3_PLAYBACK_BASE (PCM_DMA_BUF_2_CAPTURE_BASE+PCM_DMA_BUF_2_CAPTURE_LEN)
#define PCM_DMA_BUF_3_PLAYBACK_LEN  (PCM_DMA_BUF_PLAYBACK_LEN)
#define PCM_DMA_BUF_3_CAPTURE_BASE  (PCM_DMA_BUF_3_PLAYBACK_BASE+PCM_DMA_BUF_3_PLAYBACK_LEN)
#define PCM_DMA_BUF_3_CAPTURE_LEN   (0)

#define PCM_STREAM_MAX              (2)
#define PCM_DEVICE_MAX              (4)
typedef struct pcm_dma_buf_config
{
	u64       pcm_dma_buf_base;
	u64       pcm_dma_buf_len;
}PCM_DMA_BUF_CONFIG;

PCM_DMA_BUF_CONFIG  g_pcm_dma_buf_config[PCM_DEVICE_MAX][PCM_STREAM_MAX] =
{
	{{PCM_DMA_BUF_0_PLAYBACK_BASE,PCM_DMA_BUF_0_PLAYBACK_LEN},{PCM_DMA_BUF_0_CAPTURE_BASE,PCM_DMA_BUF_0_CAPTURE_LEN}},
	{{PCM_DMA_BUF_1_PLAYBACK_BASE,PCM_DMA_BUF_1_PLAYBACK_LEN},{PCM_DMA_BUF_1_CAPTURE_BASE,PCM_DMA_BUF_1_CAPTURE_LEN}},
	{{PCM_DMA_BUF_2_PLAYBACK_BASE,PCM_DMA_BUF_2_PLAYBACK_LEN},{PCM_DMA_BUF_2_CAPTURE_BASE,PCM_DMA_BUF_2_CAPTURE_LEN}},
	{{PCM_DMA_BUF_3_PLAYBACK_BASE,PCM_DMA_BUF_3_PLAYBACK_LEN},{PCM_DMA_BUF_3_CAPTURE_BASE,PCM_DMA_BUF_3_CAPTURE_LEN}}
};

/*****************************************************************************
  2 ȫ�ֱ�������
 *****************************************************************************/
static const unsigned int freq[] = {
	8000,   11025,  12000,  16000,
	22050,  24000,  32000,  44100,
	48000,  88200,  96000,  176400,
	192000,
};

static const struct snd_soc_component_driver hi6210_pcm_component = {
	.name   = HI6210_PCM,
};

static u64 hi6210_pcm_dmamask           = (u64)(0xffffffff);

static struct snd_soc_dai_driver hi6210_dai[] =
{
	{
		.name = "hi6210-mm",
		.playback = {
			.stream_name  = "hi6210-mm Playback",
			.channels_min = HI6210_PB_MIN_CHANNELS,
			.channels_max = HI6210_PB_MAX_CHANNELS,
			.rates        = HI6210_PB_RATES,
			.formats      = HI6210_PB_FORMATS},
		.capture = {
			.stream_name  = "hi6210-mm Capture",
			.channels_min = HI6210_CP_MIN_CHANNELS,
			.channels_max = HI6210_CP_MAX_CHANNELS,
			.rates        = HI6210_CP_RATES,
			.formats      = HI6210_CP_FORMATS
		},
	},
	{
		.name = "hi6210-modem",
		.playback = {
			.stream_name  = "hi6210-modem Playback",
			.channels_min = HI6210_PB_MIN_CHANNELS,
			.channels_max = HI6210_PB_MAX_CHANNELS,
			.rates        = HI6210_MODEM_RATES,
			.formats      = HI6210_PB_FORMATS
		},
	},
	{
		.name = "hi6210-fm",
		.playback = {
			.stream_name  = "hi6210-fm Playback",
			.channels_min = HI6210_PB_MIN_CHANNELS,
			.channels_max = HI6210_PB_MAX_CHANNELS,
			.rates        = HI6210_FM_RATES,
			.formats      = HI6210_PB_FORMATS
		},
	},
	{
		.name = "hi6210-bt",
		.playback = {
			.stream_name  = "hi6210-bt Playback",
			.channels_min = HI6210_PB_MIN_CHANNELS,
			.channels_max = HI6210_PB_MAX_CHANNELS,
			.rates        = HI6210_BT_RATES,
			.formats      = HI6210_PB_FORMATS},
	},
	{
		.name = "hi6210-lpp",
		.playback = {
			.stream_name  = "hi6210-lpp Playback",
			.channels_min = HI6210_PB_MIN_CHANNELS,
			.channels_max = HI6210_PB_MAX_CHANNELS,
			.rates        = HI6210_PB_RATES,
			.formats      = HI6210_PB_FORMATS},
	},
};

/* define the capability of playback channel */
static const struct snd_pcm_hardware hi6210_hardware_playback =
{
	.info             = SNDRV_PCM_INFO_INTERLEAVED
		| SNDRV_PCM_INFO_NONINTERLEAVED
		| SNDRV_PCM_INFO_MMAP
		| SNDRV_PCM_INFO_MMAP_VALID
		| SNDRV_PCM_INFO_PAUSE,
	.formats          = SNDRV_PCM_FMTBIT_S16_LE,
	.channels_min     = HI6210_PB_MIN_CHANNELS,
	.channels_max     = HI6210_PB_MAX_CHANNELS,
	.buffer_bytes_max = HI6210_MAX_BUFFER_SIZE,
	.period_bytes_min = HI6210_MIN_BUFFER_SIZE,
	.period_bytes_max = HI6210_MAX_BUFFER_SIZE,
	.periods_min      = HI6210_MIN_PERIODS,
	.periods_max      = HI6210_MAX_PERIODS,
	.fifo_size        = HI6210_PB_FIFO_SIZE,
};

/* define the capability of capture channel */
static const struct snd_pcm_hardware hi6210_hardware_capture =
{
	.info             = SNDRV_PCM_INFO_INTERLEAVED,
	.formats          = SNDRV_PCM_FMTBIT_S16_LE,
	.rates            = SNDRV_PCM_RATE_48000,
	.channels_min     = HI6210_CP_MIN_CHANNELS,
	.channels_max     = HI6210_CP_MAX_CHANNELS,
	.buffer_bytes_max = HI6210_MAX_BUFFER_SIZE,
	.period_bytes_min = HI6210_MIN_BUFFER_SIZE,
	.period_bytes_max = HI6210_MAX_BUFFER_SIZE,
	.periods_min      = HI6210_MIN_PERIODS,
	.periods_max      = HI6210_MAX_PERIODS,
	.fifo_size        = HI6210_CP_FIFO_SIZE,
};

/* define the capability of playback channel for Modem */
static const struct snd_pcm_hardware hi6210_hardware_modem_playback =
{
	.info             = SNDRV_PCM_INFO_INTERLEAVED
		| SNDRV_PCM_INFO_NONINTERLEAVED
		| SNDRV_PCM_INFO_BLOCK_TRANSFER
		| SNDRV_PCM_INFO_PAUSE,
	.formats          = SNDRV_PCM_FMTBIT_S16_LE,
	.channels_min     = HI6210_PB_MIN_CHANNELS,
	.channels_max     = HI6210_PB_MAX_CHANNELS,
	.buffer_bytes_max = HI6210_MAX_BUFFER_SIZE,
	.period_bytes_min = HI6210_MIN_BUFFER_SIZE,
	.period_bytes_max = HI6210_MAX_BUFFER_SIZE,
	.periods_min      = HI6210_MIN_PERIODS,
	.periods_max      = HI6210_MAX_PERIODS,
	.fifo_size        = HI6210_PB_FIFO_SIZE,
};

#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
struct hi6210_simu_pcm_data hi6210_simu_pcm;
#endif

static u32 pcm_cp_status_open = 0;
static u32 pcm_pb_status_open = 0;

static struct hi6210_runtime_data g_pcm_rtd_playback;
static struct hi6210_runtime_data g_pcm_rtd_capture;

spinlock_t g_pcm_cp_open_lock;
spinlock_t g_pcm_pb_open_lock;

/*****************************************************************************
  3 ��������
 *****************************************************************************/
extern int mailbox_get_timestamp(void);
static int hi6210_notify_pcm_set_buf( struct snd_pcm_substream *substream );
#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
static irq_rt_t hi6210_notify_recv_isr( void *usr_para, void *mail_handle,  unsigned int mail_len );
#endif
#ifdef __DRV_AUDIO_MAILBOX_WORK__
static irq_rt_t hi6210_mb_intr_handle(unsigned short pcm_mode,
		struct snd_pcm_substream *substream);
#endif

/*****************************************************************************
  3 ����ʵ��
 *****************************************************************************/


#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
void simu_pcm_work_func(struct work_struct *work)
{
	struct hi6210_simu_pcm_data *priv =
		container_of(work, struct hi6210_simu_pcm_data, simu_pcm_delay_work.work);
	struct hifi_chn_pcm_period_elapsed pk_data;

	logd("simu_pcm_work_func:\r\n");
	logd("      msg_type = %x\r\n", priv->msg_type);
	logd("      pcm_mode = %d\r\n", priv->pcm_mode);
	logd("      data_addr = 0x%x\r\n", priv->data_addr);
	logd("      data_len = %d\r\n", priv->data_len);
	logd("      substream = 0x%x\r\n", priv->substream);

	/* simu data move and make response */
	memset(&pk_data, 0, sizeof(struct hifi_chn_pcm_period_elapsed));
	pk_data.msg_type = HI_CHN_MSG_PCM_PERIOD_ELAPSED;
	pk_data.pcm_mode = priv->pcm_mode;
	//pk_data.substream = priv->substream;
	pk_data.substream_h32 = GET_HIG32(priv->substream);
	pk_data.substream_l32 = GET_LOW32(priv->substream);
	hi6210_notify_recv_isr(0, &pk_data, sizeof(struct hifi_chn_pcm_period_elapsed));

}
#endif

/*****************************************************************************
  �� �� ��  : hi6210_intr_handle_pb
  ��������  : PLAYBACK�����֧, �˼�ͨ��һ�����ݴ�����ɺ�Ĵ���
  �������  : struct snd_pcm_substream *substream : �������ݴ����substream
  �������  : ��
  �� �� ֵ  : STATIC irq_rt_t
  ���ú���  : hi6210_mb_intr_handle()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static irq_rt_t hi6210_intr_handle_pb(struct snd_pcm_substream *substream)
{
	struct hi6210_runtime_data *prtd        = NULL;
	snd_pcm_uframes_t rt_period_size        = 0;
	unsigned int num_period                 = 0;
	snd_pcm_uframes_t avail                 = 0;
	int ret                                 = OK;

	logd("Begin\r\n");

	if (NULL == substream)
	{
		loge("End, substream == NULL\n");
		return IRQ_HDD_PTR;
	}
	if (NULL == substream->runtime)
	{
		loge("End, substream->runtime == NULL\n");
		return IRQ_HDD_PTR;
	}

	prtd            = (struct hi6210_runtime_data *)substream->runtime->private_data;
	rt_period_size  = substream->runtime->period_size;
	num_period      = substream->runtime->periods;

	if (NULL == prtd)
	{
		loge("End, prtd == NULL\n");
		return IRQ_HDD_PTR;
	}

	/* dmas��¼dma�ж�״̬����HIFIά����AP��ά��buffer״̬ */

	spin_lock(&prtd->lock);
	++prtd->period_cur;
	prtd->period_cur = (prtd->period_cur) % num_period;
	spin_unlock(&prtd->lock);

	snd_pcm_period_elapsed(substream);

	if (STATUS_RUNNING != prtd->status)
	{
		logd("End, dma stopped\n");
		return IRQ_HDD_STATUS;
	}

	avail = (snd_pcm_uframes_t)snd_pcm_playback_hw_avail(substream->runtime);
	if(avail < rt_period_size)
	{
		logd("End, avail(%d)< rt_period_size(%d)\n", (int)avail, rt_period_size);
		return IRQ_HDD_SIZE;
	}
	else
	{
		/*
		   DMA���˽��������жϣ���������ݿɰ�ʱ��ʹ���µ�DMA����
		   MailBox֪ͨHIFI������һ�ε�DMA����
		 */
		ret = hi6210_notify_pcm_set_buf( substream );
		if( ret < 0 )
		{
			loge("End, hi6210_notify_pcm_set_buf(ret=%d)\n", ret);
			return IRQ_HDD_ERROR;
		}

		spin_lock(&prtd->lock);
		prtd->period_next = (prtd->period_next + 1) % num_period;
		spin_unlock(&prtd->lock);
	}

	logd("End\r\n");
	return IRQ_HDD;
}

/*****************************************************************************
  �� �� ��  : hi6210_intr_handle_cp
  ��������  : CAPTURE�����֧, �˼�ͨ��һ�����ݴ�����ɺ�Ĵ���
  �������  : struct snd_pcm_substream *substream
  �������  : ��
  �� �� ֵ  : STATIC irq_rt_t
  ���ú���  : hi6210_mb_intr_handle()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static irq_rt_t hi6210_intr_handle_cp(struct snd_pcm_substream *substream)
{
	struct hi6210_runtime_data *prtd        = NULL;
	snd_pcm_uframes_t rt_period_size        = 0;
	unsigned int num_period                 = 0;
	snd_pcm_uframes_t avail                 = 0;
	int ret                                 = OK;

	logd("Begin\r\n");

	if (NULL == substream)
	{
		loge("End, substream == NULL\n");
		return IRQ_HDD_PTR;
	}
	if (NULL == substream->runtime)
	{
		loge("End, substream->runtime == NULL\n");
		return IRQ_HDD_PTR;
	}

	prtd    = (struct hi6210_runtime_data *)substream->runtime->private_data;
	rt_period_size  = substream->runtime->period_size;
	num_period      = substream->runtime->periods;

	if (NULL == prtd)
	{
		loge("End, prtd == NULL\n");
		return IRQ_HDD_PTR;
	}

	spin_lock(&prtd->lock);
	++prtd->period_cur;
	prtd->period_cur = (prtd->period_cur) % num_period;
	spin_unlock(&prtd->lock);

	if (STATUS_RUNNING != prtd->status)
	{
		logd("dma stopped\n");
		return IRQ_HDD_STATUS;
	}

	snd_pcm_period_elapsed(substream);

	avail = (snd_pcm_uframes_t)snd_pcm_capture_hw_avail(substream->runtime);
	if(avail < rt_period_size)
	{
		logd("avail(%d)< rt_period_size(%d)\n", (int)avail, rt_period_size);
		return IRQ_HDD_SIZE;
	}
	else
	{
		/*
		   DMA���˽��������жϣ���������ݿɰ�ʱ��ʹ���µ�DMA����
		   MailBox֪ͨHIFI������һ�ε�DMA����
		 */
		ret = hi6210_notify_pcm_set_buf( substream );
		if( ret < 0 )
		{
			loge("hi6210_notify_pcm_set_buf(%d)\n", ret);
			return IRQ_HDD_ERROR;
		}

		spin_lock(&prtd->lock);
		prtd->period_next = (prtd->period_next + 1) % num_period;
		spin_unlock(&prtd->lock);
	}

	logd("End\r\n");
	return IRQ_HDD;
}

/*****************************************************************************
  �� �� ��  : hi6210_mb_intr_handle
  ��������  : ����˼�ͨ��ͨ�ô�����
  �������  : unsigned short pcm_mode        : PLAYBACK or CAPTURE
  snd_pcm_substream *substream   : substream
  �������  : ��
  �� �� ֵ  : STATIC irq_rt_t
  ���ú���  : hi6210_notify_recv_isr()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static irq_rt_t hi6210_mb_intr_handle(unsigned short pcm_mode,
		struct snd_pcm_substream *substream)
{
	irq_rt_t ret = IRQ_NH;

	switch( pcm_mode )
	{
		case SNDRV_PCM_STREAM_PLAYBACK:
			if ( NULL != substream)
			{
				/* lock used to protect close while doing _intr_handle_pb */
				spin_lock_bh(&g_pcm_pb_open_lock);
				if (0 == pcm_pb_status_open)
				{
					logd("pcm playback closed\n");
					spin_unlock_bh(&g_pcm_pb_open_lock);
					return IRQ_HDD;
				}

				ret = hi6210_intr_handle_pb(substream);
				spin_unlock_bh(&g_pcm_pb_open_lock);
			}
			else
			{
				loge("PB,substream is NULL\n");
				ret = IRQ_HDD_PTRS;
			}
			break;
		case SNDRV_PCM_STREAM_CAPTURE:
			if ( NULL != substream)
			{
				/* lock used to protect close while doing _intr_handle_cp */
				spin_lock_bh(&g_pcm_cp_open_lock);

				if (0 == pcm_cp_status_open)
				{
					logd("pcm capture closed\n");
					spin_unlock_bh(&g_pcm_cp_open_lock);;
					return IRQ_HDD;
				}
				ret = hi6210_intr_handle_cp(substream);
				spin_unlock_bh(&g_pcm_cp_open_lock);
			}
			else
			{
				loge("CP,substream is NULL\n");
				ret = IRQ_HDD_PTRS;
			}
			break;
		default:
			ret = IRQ_NH_MODE;
			loge("PCM Mode error(%d)\n", pcm_mode);
			break;
	}

	return ret;
}

/*****************************************************************************
  �� �� ��  : hi6210_mailbox_send_data
  ��������  : ����˼�ͨ�����ݷ���
  �������  : void *pmsg_body        : Ҫ���͵����ݰ�
  unsigned int msg_len   : ���ݰ�����
  �������  : ��
  �� �� ֵ  : STATIC int
  ���ú���  : hi6210_notify_pcm_*()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_mailbox_send_data( void *pmsg_body, unsigned int msg_len,
		unsigned int msg_priority )
{
	unsigned int ret                        = 0;

#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
	struct hifi_chn_pcm_trigger*    pmsg    = NULL;
	struct hifi_channel_set_buffer* pbuf    = NULL;
	/* simu */
	switch (((struct hifi_chn_pcm_trigger *)pmsg_body)->msg_type) {
		case HI_CHN_MSG_PCM_TRIGGER :
			pmsg   = (struct hifi_chn_pcm_trigger*)   pmsg_body;
			if((SNDRV_PCM_TRIGGER_START            == pmsg->tg_cmd) ||
					(SNDRV_PCM_TRIGGER_RESUME         == pmsg->tg_cmd) ||
					(SNDRV_PCM_TRIGGER_PAUSE_RELEASE  == pmsg->tg_cmd))
			{
				hi6210_simu_pcm.msg_type  = pmsg->msg_type;
				hi6210_simu_pcm.pcm_mode  = pmsg->pcm_mode;
				hi6210_simu_pcm.substream = INT_TO_ADDR(pmsg->substream_l32,pmsg->substream_h32);
				hi6210_simu_pcm.data_addr = pmsg->data_addr;
				hi6210_simu_pcm.data_len  = pmsg->data_len;
				queue_delayed_work(hi6210_simu_pcm.simu_pcm_delay_wq,
						&hi6210_simu_pcm.simu_pcm_delay_work,
						msecs_to_jiffies(20/*0*/));

			}
			break;
		case HI_CHN_MSG_PCM_SET_BUF :
			pbuf                      = (struct hifi_channel_set_buffer*)pmsg_body;
			hi6210_simu_pcm.msg_type  = pbuf->msg_type;
			hi6210_simu_pcm.pcm_mode  = pbuf->pcm_mode;
			hi6210_simu_pcm.data_addr = pbuf->data_addr;
			hi6210_simu_pcm.data_len  = pbuf->data_len;
			queue_delayed_work(hi6210_simu_pcm.simu_pcm_delay_wq,
					&hi6210_simu_pcm.simu_pcm_delay_work,
					msecs_to_jiffies(0/*20*/));
			break;
		default:
			logi("hi6210_mailbox_send_data MSG_TYPE(0x%x)\r\n", ((struct hifi_chn_pcm_trigger *)pmsg_body)->msg_type);
			break;
	}

#else

	ret = DRV_MAILBOX_SENDMAIL(MAILBOX_MAILCODE_ACPU_TO_HIFI_AUDIO, pmsg_body, msg_len);
	if( MAILBOX_OK != ret )
	{
		loge("Mailbox send mail failed,ret=%d\n", ret);
		HiLOGE("audio", "Hi6210_pcm","Mailbox send mail failed,ret=%d\n", ret);
	}
#endif
	return (int)ret;
}

/*****************************************************************************
  �� �� ��  : hi6210_notify_pcm_open
  ��������  : �˼�ͨ�Ÿ�֪HIFI PCM OPEN
  �������  : hifi_chn_pcm_open *psrc_data : Ҫ������������
  �������  : ��
  �� �� ֵ  : STATIC int, 0 for Success; Others for error
  ���ú���  : hi6210_pcm_hifi_open()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_notify_pcm_open( unsigned short pcm_mode )
{
	struct hifi_chn_pcm_open msg_body   = { 0 };
	int ret                             = OK;

	if ( (SNDRV_PCM_STREAM_PLAYBACK != pcm_mode) &&
			(SNDRV_PCM_STREAM_CAPTURE != pcm_mode) )
	{
		loge("pcm_mode=%d\n", pcm_mode);
		return -EINVAL;
	}

	msg_body.msg_type    = (unsigned short)HI_CHN_MSG_PCM_OPEN;
	msg_body.pcm_mode    = pcm_mode;

	/* mail-box send */
	ret = hi6210_mailbox_send_data( &msg_body, sizeof(struct hifi_chn_pcm_open), 0 );
	if( OK != ret )
	{
		ret = -EBUSY;
	}

	return ret;
}


/*****************************************************************************
  �� �� ��  : hi6210_notify_pcm_close
  ��������  : �˼�ͨ�Ÿ�֪HIFI PCM CLOSE
  �������  : hifi_chn_pcm_close *psrc_data : Ҫ������������
  �������  : ��
  �� �� ֵ  : STATIC int, 0 for Success; Others for error
  ���ú���  : hi6210_pcm_hifi_close()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_notify_pcm_close( unsigned short pcm_mode )
{
	struct hifi_chn_pcm_close msg_body  = { 0 };
	int ret                             = OK;

	if ( (SNDRV_PCM_STREAM_PLAYBACK != pcm_mode) &&
			(SNDRV_PCM_STREAM_CAPTURE != pcm_mode) )
	{
		loge("pcm_mode=%d\n", pcm_mode);
		return -EINVAL;
	}

	msg_body.msg_type    = (unsigned short)HI_CHN_MSG_PCM_CLOSE;
	msg_body.pcm_mode    = pcm_mode;

	/* mail-box send */
	ret = hi6210_mailbox_send_data( &msg_body, sizeof(struct hifi_chn_pcm_close), 0 );
	if( OK != ret )
	{
		ret = -EBUSY;
	}
	logi("mailbox ret=%d\r\n", ret);

	return ret;
}

/*****************************************************************************
  �� �� ��  : hi6210_notify_pcm_hw_params
  ��������  : �˼�ͨ�Ÿ�֪HIFI PCM HW PARAMS
  �������  : unsigned short pcm_mode : PLAYBACK or CAPTURE
  struct snd_pcm_hw_params *params : ���ò���
  �������  : ��
  �� �� ֵ  : STATIC int, 0 for Success; Negative for error
  ���ú���  : hi6210_pcm_hifi_hw_params()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_notify_pcm_hw_params( unsigned short pcm_mode,
		struct snd_pcm_hw_params *params )
{
	struct hifi_chn_pcm_hw_params msg_body  = { 0 };
	unsigned int params_value               = 0;
	unsigned int infreq_index               = 0;
	int ret                                 = OK;

	if ( (SNDRV_PCM_STREAM_PLAYBACK != pcm_mode) &&
			(SNDRV_PCM_STREAM_CAPTURE != pcm_mode) )
	{
		loge("pcm_mode=%d\n", pcm_mode);
		return -EINVAL;
	}

	msg_body.msg_type = (unsigned short)HI_CHN_MSG_PCM_HW_PARAMS;
	msg_body.pcm_mode = pcm_mode;

	/* CHECK SUPPORT CHANNELS : mono or stereo */
	params_value = params_channels(params);
	if (HI6210_CP_MIN_CHANNELS <= params_value
			&& HI6210_CP_MAX_CHANNELS >= params_value)
	{
		msg_body.channel_num = params_value;
	}
	else
	{
		loge("DAC not support %d channels\n", params_value);
		return -EINVAL;
	}

	/* CHECK SUPPORT RATE */
	params_value = params_rate(params);
	logd("set rate = %d \n", params_value);
	for (infreq_index = 0; infreq_index < ARRAY_SIZE(freq); infreq_index++)
	{
		if(params_value == freq[infreq_index])
			break;
	}
	if ( ARRAY_SIZE(freq) <= infreq_index )
	{
		loge("set rate = %d \n", params_value);
		return -EINVAL;
	}
	msg_body.sample_rate = params_value;

	/* PLAYBACK */
	if ( SNDRV_PCM_STREAM_PLAYBACK == pcm_mode )
	{
		params_value = (unsigned int)params_format(params);
		/* check formats */
		if( (SNDRV_PCM_FORMAT_S16_BE == params_value) ||
				(SNDRV_PCM_FORMAT_S16_LE == params_value) )
		{
			msg_body.format = params_value;
		}
		else
		{
			loge("format err : %d, not support\n", params_value);
			return -EINVAL;
		}
	}
	else
		/* CAPTURE */
	{
		params_value = (unsigned int)params_format(params);
		/* check formats */
		if ( params_value > SNDRV_PCM_FORMAT_LAST )
		{
			loge("format err2 : %d, not support\n", params_value);
			return -EINVAL;
		}
		msg_body.format = params_value;
	}

	logi("%s: pcm_mode = %d channel_num = %d sample_rate = %d format = %d\r\n",
			__func__,msg_body.pcm_mode,msg_body.channel_num,msg_body.sample_rate,msg_body.format);

	/* mail-box send */
	ret = hi6210_mailbox_send_data( &msg_body, sizeof(struct hifi_chn_pcm_hw_params), 0 );
	if( OK != ret )
	{
		ret = -EBUSY;
	}

	return ret;
}

/*****************************************************************************
  �� �� ��  : hi6210_notify_pcm_trigger
  ��������  : �˼�ͨ�Ÿ�֪HIFI PCM TRIGGER
  �������  : hifi_chn_pcm_trigger *psrc_data : Ҫ������������
  �������  : ��
  �� �� ֵ  : STATIC int, 0 for Success; Others for error
  ���ú���  : hi6210_pcm_hifi_trigger()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_notify_pcm_trigger( int cmd,
		struct snd_pcm_substream *substream )
{
	struct hi6210_runtime_data *prtd        =
		(struct hi6210_runtime_data *)substream->runtime->private_data;
	unsigned int period_size                = 0;
	struct hifi_chn_pcm_trigger msg_body    = { 0 };
	int ret                                 = OK;

	if(NULL == prtd ){
		loge("hi6210_notify_pcm_trigger failed prtd = NULL");
		return -EINVAL;
	}

	period_size = prtd->period_size;

	msg_body.msg_type   	= (unsigned short)HI_CHN_MSG_PCM_TRIGGER;
	msg_body.pcm_mode   	= (unsigned short)substream->stream;
	msg_body.tg_cmd     	= (unsigned short)cmd;
	msg_body.enPcmObj   	= (unsigned short)0;/*AP*/
	msg_body.substream_l32  = GET_LOW32(substream);
	msg_body.substream_h32  = GET_HIG32(substream);

	if( (SNDRV_PCM_TRIGGER_START == cmd) ||
			(SNDRV_PCM_TRIGGER_RESUME == cmd) ||
			(SNDRV_PCM_TRIGGER_PAUSE_RELEASE == cmd) )
	{
		msg_body.data_addr = (substream->runtime->dma_addr + prtd->period_next * period_size) - PCM_DMA_BUF_0_PLAYBACK_BASE;
		msg_body.data_len  = period_size;
	}

	logi("%s:cmd = %d pcm_mode = %d data_addr = 0x%x data_len = %d\r\n",
			__func__,cmd,msg_body.pcm_mode,msg_body.data_addr,msg_body.data_len);

	/* mail-box send */
	ret = hi6210_mailbox_send_data( &msg_body, sizeof(struct hifi_chn_pcm_trigger), 0 );
	if( OK != ret )
	{
		ret = -EBUSY;
	}

	return ret;
}

/*****************************************************************************
  �� �� ��  : hi6210_notify_pcm_set_buf
  ��������  : �˼�ͨ�Ÿ�֪HIFI ����BUFFER�Ѿ���
  �������  : hifi_channel_set_buffer *psrc_data
  �������  : ��
  �� �� ֵ  : STATIC int, 0 for Success; Others for error
  ���ú���  : hi6210_intr_handle_pb()��hi6210_intr_handle_cp()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_notify_pcm_set_buf( struct snd_pcm_substream *substream )
{
	struct hi6210_runtime_data *prtd        =
		(struct hi6210_runtime_data *)substream->runtime->private_data;
	unsigned int period_size;
	unsigned short pcm_mode                 = (unsigned short)substream->stream;
	struct hifi_channel_set_buffer msg_body    = { 0 };
	int ret                                 = 0;

	if (NULL == prtd) {
		loge("hi6210_notify_pcm_set_buf faied prtd = NULL");
		return -EINVAL;
	}
	period_size = prtd->period_size;

	if ((SNDRV_PCM_STREAM_PLAYBACK != pcm_mode)
			&& (SNDRV_PCM_STREAM_CAPTURE != pcm_mode)) {
		loge("pcm mode invalid, mode=%d\n", pcm_mode);
		return -EINVAL;
	}

	msg_body.msg_type   = (unsigned short)HI_CHN_MSG_PCM_SET_BUF;
	msg_body.pcm_mode   = pcm_mode;
	msg_body.data_addr  = (substream->runtime->dma_addr + prtd->period_next * period_size) - PCM_DMA_BUF_0_PLAYBACK_BASE;
	msg_body.data_len   = period_size;

	if (STATUS_RUNNING != prtd->status) {
		logd("pcm is closed \n");
		return -EINVAL;
	}

	/* mail-box send */
	/* trace_dot(APCM,"4",0); */
	ret = hi6210_mailbox_send_data( &msg_body, sizeof(struct hifi_channel_set_buffer), 0 );
	if (OK != ret)
		ret = -EBUSY;

	/* trace_dot(APCM,"5",0); */

	logd("End(%d)\r\n", ret);
	return ret;
}

/*****************************************************************************
  �� �� ��  : hi6210_notify_recv_isr
  ��������  : �����˼�ͨ����Ϣ���յ������ݰ������ݣ�������Ӧ����
  ע��Ϊ�˼�ͨ������Ľ��պ���
  �������  : void *usr_para             : ע��ʱ���ݵĲ���
  void *mail_handle          : �������ݲ���
  unsigned int mail_len      : �������ݳ���
  �������  : ��
  �� �� ֵ  : STATIC irq_rt_t
  ���ú���  : hi6210_pcm_new()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static irq_rt_t hi6210_notify_recv_isr( void *usr_para, void *mail_handle,  unsigned int mail_len )
{
	struct snd_pcm_substream * substream    = NULL;
	struct hi6210_runtime_data *prtd        = NULL;
	struct hifi_chn_pcm_period_elapsed mail_buf;
	unsigned int mail_size          = mail_len;
	unsigned int ret_mail           = MAILBOX_OK;
	irq_rt_t ret                    = IRQ_NH;
	unsigned int delay_time = 0;
	unsigned int pre_time = 0;
	unsigned int cur_time = 0;

	pre_time = (unsigned int)mailbox_get_timestamp();

	memset(&mail_buf, 0, sizeof(struct hifi_chn_pcm_period_elapsed));

	/*��ȡ������������*/
#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
	memcpy(&mail_buf, mail_handle, sizeof(struct hifi_chn_pcm_period_elapsed));
#else
	ret_mail = DRV_MAILBOX_READMAILDATA(mail_handle, (unsigned char*)&mail_buf, &mail_size);
	if ((ret_mail != MAILBOX_OK)
			|| (mail_size <= 0)
			|| (mail_size > sizeof(struct hifi_chn_pcm_period_elapsed)))
	{
		loge("Empty point or data length error! size: %d\n", mail_size);
		HiLOGE("audio", "Hi6210_pcm", "Empty point or data length error! size: %d\n", mail_size);
		return IRQ_NH_MB;
	}
#endif

#ifdef __DRV_AUDIO_MAILBOX_WORK__
	substream = INT_TO_ADDR(mail_buf.substream_l32,mail_buf.substream_h32);
	if (NULL == substream) {
		loge("substream from hifi is NULL\n");
		return IRQ_NH_OTHERS;
	}
	if (NULL == substream->runtime) {
		loge("substream->runtime is NULL\n");
		return IRQ_NH_OTHERS;
	}

	prtd = (struct hi6210_runtime_data *)substream->runtime->private_data;
	if (NULL == prtd) {
		loge("prtd is NULL\n");
		return IRQ_NH_OTHERS;
	}
	if (STATUS_STOP == prtd->status) {
		logi("process has stopped there is still info coming from hifi\n");
		return IRQ_NH_OTHERS;
	}

	switch(mail_buf.msg_type) {
		case HI_CHN_MSG_PCM_PERIOD_ELAPSED:
			if (STATUS_STOPPING == prtd->status) {
				logi("stopping ignore period\n");
				break;
			}
			ret = hi6210_mb_intr_handle(mail_buf.pcm_mode, substream);
			if (ret == IRQ_NH)
				loge("mb msg handle err, ret : %d\n", ret);
			break;
		case HI_CHN_MSG_PCM_PERIOD_STOP:
			if (STATUS_STOPPING == prtd->status) {
				spin_lock(&prtd->lock);
				prtd->status = STATUS_STOP;
				spin_unlock(&prtd->lock);
				logi("stop now \n");
			}
			break;
		default:
			loge("msg_type 0x%x\n", mail_buf.msg_type);
			break;
	}

	cur_time = (unsigned int)mailbox_get_timestamp();
	delay_time = HI6210_CYC_SUB(cur_time, pre_time, 0xffffffff);
	if (delay_time > (HI6210_WORK_DELAY_1MS * 5)) {
		logw("[%d]:this msg delayed %d slices, pcm mode:%d\n",
			mailbox_get_timestamp(), delay_time, mail_buf.pcm_mode);
	}

	return ret;
#else
	substream = INT_TO_ADDR(mail_buf.substream_l32,mail_buf.substream_h32);
	switch(mail_buf.msg_type)
	{
		case HI_CHN_MSG_PCM_PERIOD_ELAPSED:
			ret = hi6210_mb_intr_handle(mail_buf.pcm_mode, substream);
			if (ret == IRQ_NH)
				loge("ret : %d\n", ret);
			break;
		default:
			ret = IRQ_NH_TYPE;
			/*������Ϣ���������Ͳ�Ӧ����*/
			loge("msg_type 0x%x\n", mail_buf.msg_type);
			break;
	}

	return ret;
#endif
}

/*****************************************************************************
  �� �� ��  : hi6210_notify_isr_register
  ��������  : ����˼����ݽ��ջص�����ע��
  �������  : void *pisr     : �ص�����ָ��
  �������  : ��
  �� �� ֵ  : STATIC int
  ���ú���  : hi6210_pcm_new()
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��7��31��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_notify_isr_register( irq_hdl_t pisr )
{
#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
	return OK;
#else
	int ret                     = OK;
	unsigned int mailbox_ret    = MAILBOX_OK;

	if( NULL == pisr )
	{
		loge("pisr==NULL!\n");
		ret = ERROR;
	}
	else
	{
		mailbox_ret = DRV_MAILBOX_REGISTERRECVFUNC( MAILBOX_MAILCODE_HIFI_TO_ACPU_AUDIO, (void *)pisr, NULL );
		if(MAILBOX_OK != mailbox_ret)
		{
			ret = ERROR;
			loge("ret : %d,0x%x\n", ret,MAILBOX_MAILCODE_HIFI_TO_ACPU_AUDIO);
		}
	}

	return ret;
#endif
}


/*****************************************************************************
  �� �� ��  : hi6210_pcm_hifi_hw_params
  ��������  : Ӳ��ͨ���������ã�����ʹ�ú˼�ͨ�Ÿ�֪HIFI�����������
  �������  : struct snd_pcm_substream *substream
  struct snd_pcm_hw_params *params
  �������  : ��
  �� �� ֵ  : static int
  ���ú���  :
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��8��4��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_pcm_hifi_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params)
{
	size_t bytes                 = params_buffer_bytes(params);
	struct hi6210_runtime_data *prtd    =
		(struct hi6210_runtime_data *)substream->runtime->private_data;
	int ret                             = 0;

	IN_FUNCTION;

	if(NULL == prtd){
		loge("hi6210_pcm_hifi_hw_params faied prtd = NULL");
		return -EINVAL;
	}


	logd("entry : %s\n", substream->stream == SNDRV_PCM_STREAM_PLAYBACK
			? "PLAYBACK" : "CAPTURE");

	ret = snd_pcm_lib_malloc_pages(substream, bytes);
	if ( ret < 0 )
	{
		loge("snd_pcm_lib_malloc_pages ret : %d\n", ret);

		OUT_FUNCTION;
		return ret;
	}
	spin_lock_bh(&prtd->lock);
	prtd->period_size = params_period_bytes(params);
	prtd->period_next = 0;
	spin_unlock_bh(&prtd->lock);

	/* ͨ���˼�ͨ�Ÿ�֪HIFI����hw_params */
	ret = hi6210_notify_pcm_hw_params( (unsigned short)substream->stream, params );
	if ( ret < 0 )
	{
		loge("hi6210_notify_pcm_hw_params ret : %d\n", ret);
		snd_pcm_lib_free_pages(substream);

		OUT_FUNCTION;
		return ret;
	}

	OUT_FUNCTION;

	return ret;
}

static int hi6210_pcm_hifi_hw_free(struct snd_pcm_substream *substream)
{
	logd("entry : %s\n", substream->stream == SNDRV_PCM_STREAM_PLAYBACK
			? "PLAYBACK" : "CAPTURE");

	/*
	   ͨ���˼�ͨ�Ÿ�֪HIFI����hw_free(Playback/Capture)
	   ��ע�͵��������н���
	   hi6210_notify_pcm_hw_free( pcm_mode );
	 */

	return snd_pcm_lib_free_pages(substream);
}

/*****************************************************************************
  �� �� ��  : hi6210_pcm_hifi_prepare
  ��������  : ��ʼ��˽������private������ʹ�ú˼�ͨ�Ÿ�֪HIFI����pcm prepare
  �������  : struct snd_pcm_substream *substream
  �������  : ��
  �� �� ֵ  : static int
  ���ú���  :
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��8��4��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_pcm_hifi_prepare(struct snd_pcm_substream *substream)
{
	struct hi6210_runtime_data *prtd        =
		(struct hi6210_runtime_data *)substream->runtime->private_data;
	int ret                                 = OK;

	logd("entry : %s\n", substream->stream == SNDRV_PCM_STREAM_PLAYBACK
			? "PLAYBACK" : "CAPTURE");

	/*
	   ��ע�͵��������н���
	   msg_body.pcm_mode = substream->stream;
	   hi6210_notify_pcm_prepare( &msg_body );
	 */

	if(NULL == prtd){
		loge("hi6210_pcm_hifi_prepare faied prtd = NULL");
		return -EINVAL;
	}

	/* init prtd */
	spin_lock_bh(&prtd->lock);
	prtd->status        = STATUS_STOP;
	prtd->period_next   = 0;
	prtd->period_cur    = 0;
	spin_unlock_bh(&prtd->lock);
	return ret;
}

/*****************************************************************************
  �� �� ��  : hi6210_pcm_hifi_trigger
  ��������  : ����������ֹͣPCM������������ʹ�ú˼�ͨ�Ÿ�֪HIFI�������������-
  DMA����
  �������  : struct snd_pcm_substream *substream
  int cmd
  �������  : ��
  �� �� ֵ  : static int
  ���ú���  :
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��8��4��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_pcm_hifi_trigger(int cmd, struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime         = substream->runtime;
	struct hi6210_runtime_data *prtd        =
		(struct hi6210_runtime_data *)substream->runtime->private_data;
	unsigned int num_periods                = runtime->periods;
	int ret                                 = OK;

	IN_FUNCTION;

	logd("entry : %s, cmd : %d\n", substream->stream == SNDRV_PCM_STREAM_PLAYBACK
			? "PLAYBACK" : "CAPTURE", cmd);


	if(NULL == prtd){
		loge("hi6210_pcm_hifi_trigger faied prtd = NULL");
		return -EINVAL;
	}

	switch (cmd)
	{
		case SNDRV_PCM_TRIGGER_START:
		case SNDRV_PCM_TRIGGER_RESUME:
		case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			/* ͨ���˼�ͨ�Ÿ�֪HIFI trigger״̬ */

			ret = hi6210_notify_pcm_trigger( cmd, substream );
			if ( ret < 0 )
			{
				loge("hi6210_notify_pcm_trigger ret : %d\n", ret);
			}
			else
			{
				spin_lock_bh(&prtd->lock);
				prtd->status = STATUS_RUNNING;
				prtd->period_next = (prtd->period_next + 1) % num_periods;
				spin_unlock_bh(&prtd->lock);
			}
			break;

		case SNDRV_PCM_TRIGGER_STOP:
		case SNDRV_PCM_TRIGGER_SUSPEND:
		case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			/* ͨ���˼�ͨ�Ÿ�֪HIFI trigger״̬ */

			spin_lock_bh(&prtd->lock);
			prtd->status = STATUS_STOPPING;
			spin_unlock_bh(&prtd->lock);

			ret = hi6210_notify_pcm_trigger( cmd, substream );
			if ( ret < 0 )
			{
				loge("hi6210_notify_pcm_trigger ret : %d\n", ret);
			}

			break;

		default:
			loge("cmd error : %d", cmd);
			ret = -EINVAL;
			break;
	}

	OUT_FUNCTION;

	return ret;
}

/*****************************************************************************
  �� �� ��  : hi6210_pcm_hifi_pointer
  ��������  : ��ѯ��ǰPCM����������֡��
  �������  : struct snd_pcm_substream *substream
  �������  : ��
  �� �� ֵ  : static snd_pcm_uframes_t
  ���ú���  :
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��8��4��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static snd_pcm_uframes_t hi6210_pcm_hifi_pointer(struct snd_pcm_substream *substream)
{
	struct snd_pcm_runtime *runtime         = substream->runtime;
	struct hi6210_runtime_data *prtd        =
		(struct hi6210_runtime_data *)substream->runtime->private_data;
	long frame                     = 0L;


	if(NULL == prtd){
		loge("hi6210_pcm_hifi_pointer faied prtd = NULL");
		return -EINVAL;
	}

	frame = bytes_to_frames(runtime, prtd->period_cur * prtd->period_size);
	if(frame >= runtime->buffer_size)
		frame = 0;

	return (snd_pcm_uframes_t)frame;
}

/*****************************************************************************
  �� �� ��  : hi6210_pcm_hifi_open
  ��������  : PCM���������л�����ʼ��������ͬʱʹ�ú˼�ͨ�Ÿ�֪HIFI PCM����
  �������  : struct snd_pcm_substream *substream
  �������  : ��
  �� �� ֵ  : static int
  ���ú���  :
  ��������  :

  �޸���ʷ      :
  1.��    ��   : 2012��8��4��
  ��    ��   : ʯ���� s00212991
  �޸�����   : �����ɺ���

 *****************************************************************************/
static int hi6210_pcm_hifi_open(struct snd_pcm_substream *substream)
{
	struct hi6210_runtime_data *prtd    = NULL;
	int ret                             = OK;

	IN_FUNCTION;

	logd("entry : %s\n", substream->stream == SNDRV_PCM_STREAM_PLAYBACK
			? "PLAYBACK" : "CAPTURE");



	if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream){
		snd_soc_set_runtime_hwparams(substream, &hi6210_hardware_playback);
		prtd = &g_pcm_rtd_playback;
	}
	else {
		snd_soc_set_runtime_hwparams(substream, &hi6210_hardware_capture);
		prtd = &g_pcm_rtd_capture;
	}

	spin_lock_bh(&prtd->lock);
	prtd->period_cur  = 0;
	prtd->period_next = 0;
	prtd->period_size = 0;
	prtd->status      = STATUS_STOP;
	spin_unlock_bh(&prtd->lock);


	substream->runtime->private_data = prtd;
	/* ֪ͨHIFI PCM Open */
	ret = hi6210_notify_pcm_open( (unsigned short)substream->stream );
	if ( ret < 0 )
	{
		loge("hi6210_notify_pcm_open ret : %d\n", ret);
	}

	OUT_FUNCTION;
	return ret;
}

static int hi6210_pcm_hifi_close(struct snd_pcm_substream *substream)
{
	struct hi6210_runtime_data *prtd        =
		(struct hi6210_runtime_data *)substream->runtime->private_data;

	IN_FUNCTION;

	logd("entry : %s\n", substream->stream == SNDRV_PCM_STREAM_PLAYBACK
			? "PLAYBACK" : "CAPTURE");

	if(NULL == prtd)
	{
		loge("prtd==NULL\n");
	}

	hi6210_notify_pcm_close( (unsigned short)substream->stream );

#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
	if(hi6210_simu_pcm.simu_pcm_delay_wq) {
		cancel_delayed_work(&hi6210_simu_pcm.simu_pcm_delay_work);
		flush_workqueue(hi6210_simu_pcm.simu_pcm_delay_wq);
	}
#endif

	substream->runtime->private_data = NULL;

	OUT_FUNCTION;

	return OK;
}

static int hi6210_pcm_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params)
{
	int ret = 0;
	if (substream->pcm->device == 0)
		ret = hi6210_pcm_hifi_hw_params(substream, params);
	return ret;
}

static int hi6210_pcm_hw_free(struct snd_pcm_substream *substream)
{
	int ret = 0;
	struct hi6210_runtime_data *prtd        = NULL;
	int i   = 0;

	prtd    = (struct hi6210_runtime_data *)substream->runtime->private_data;

	if(NULL == prtd){
		if(0 == substream->pcm->device){
			loge("hi6210_pcm_hw_free faied prtd = NULL");
			return -EINVAL;
		}
		else {
			return ret;
		}
	}

	if (0 == substream->pcm->device){
		for(i = 0; i < 30 ; i++){  /* wait for dma ok */
			if (STATUS_STOP == prtd->status){
				break;
			} else {
				msleep(10);
			}
		}
		if (30 == i){
			logi("timeout for waiting for stop info from hifi \n");
		}

		ret = hi6210_pcm_hifi_hw_free(substream);
	}
	return ret;
}

static int hi6210_pcm_prepare(struct snd_pcm_substream *substream)
{
	int ret = 0;
	if (substream->pcm->device == 0)
		ret = hi6210_pcm_hifi_prepare(substream);
	return ret;
}

static int hi6210_pcm_trigger(struct snd_pcm_substream *substream, int cmd)
{
	int ret = 0;
	if (substream->pcm->device == 0)
		ret = hi6210_pcm_hifi_trigger(cmd, substream);
	return ret;
}

static snd_pcm_uframes_t hi6210_pcm_pointer(struct snd_pcm_substream *substream)
{
	unsigned long ret = 0L;
	if (substream->pcm->device == 0)
		ret = hi6210_pcm_hifi_pointer(substream);
	return ret;
}

static int hi6210_pcm_open(struct snd_pcm_substream *substream)
{
	int ret = 0;
	if (substream->pcm->device == 0)
	{
		logi("hi6210_pcm_open substream = 0x%pK, runtime = 0x%pK", substream, substream->runtime);

		if(SNDRV_PCM_STREAM_CAPTURE == substream->stream)
		{
			spin_lock_bh(&g_pcm_cp_open_lock);
			pcm_cp_status_open = (u32)1;
			ret = hi6210_pcm_hifi_open(substream);
			spin_unlock_bh(&g_pcm_cp_open_lock);
		}
		else if(SNDRV_PCM_STREAM_PLAYBACK == substream->stream)
		{
			spin_lock_bh(&g_pcm_pb_open_lock);
			pcm_pb_status_open = (u32)1;
			ret = hi6210_pcm_hifi_open(substream);
			spin_unlock_bh(&g_pcm_pb_open_lock);
		}
		else
		{
			/* do nothing */
		}
	}
	else
	{
		if (SNDRV_PCM_STREAM_PLAYBACK == substream->stream)
			snd_soc_set_runtime_hwparams(substream, &hi6210_hardware_modem_playback);
	}
	return ret;
}

static int hi6210_pcm_close(struct snd_pcm_substream *substream)
{
	int ret = 0;
	if (substream->pcm->device == 0)
	{
		logi ("hi6210_pcm_close, substream = 0x%pK, runtime = 0x%pK \n", substream, substream->runtime);
		if(SNDRV_PCM_STREAM_CAPTURE == substream->stream)
		{
			spin_lock_bh(&g_pcm_cp_open_lock);
			pcm_cp_status_open = (u32)0;
			ret = hi6210_pcm_hifi_close(substream);
			spin_unlock_bh(&g_pcm_cp_open_lock);
		}
		else if(SNDRV_PCM_STREAM_PLAYBACK == substream->stream)
		{
			spin_lock_bh(&g_pcm_pb_open_lock);
			pcm_pb_status_open = (u32)0;
			ret = hi6210_pcm_hifi_close(substream);
			spin_unlock_bh(&g_pcm_pb_open_lock);
		}
		else
		{
			/* do nothing */
		}
	}
	return ret;
}

/* define all pcm ops of hi6210 pcm */
static struct snd_pcm_ops hi6210_pcm_ops = {
	.open       = hi6210_pcm_open,
	.close      = hi6210_pcm_close,
	.ioctl      = snd_pcm_lib_ioctl,
	.hw_params  = hi6210_pcm_hw_params,
	.hw_free    = hi6210_pcm_hw_free,
	.prepare    = hi6210_pcm_prepare,
	.trigger    = hi6210_pcm_trigger,
	.pointer    = hi6210_pcm_pointer,
};


static int preallocate_dma_buffer(struct snd_pcm *pcm, int stream)
{
	struct snd_pcm_substream 	*substream = pcm->streams[stream].substream;
	struct snd_dma_buffer 		*buf = &substream->dma_buffer;

	if ((pcm->device >= PCM_DEVICE_MAX) ||(stream >= PCM_STREAM_MAX)) {
		loge("Invalid argument  : device %d stream %d \n", pcm->device, stream);
		return -EINVAL;
	}

	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = pcm->card->dev;
	buf->private_data = NULL;
	buf->addr = g_pcm_dma_buf_config[pcm->device][stream].pcm_dma_buf_base;
	buf->bytes = g_pcm_dma_buf_config[pcm->device][stream].pcm_dma_buf_len;
	buf->area = ioremap(buf->addr, buf->bytes);

	if (!buf->area){
		return -ENOMEM;
	}

	return 0;
}

static void free_dma_buffers(struct snd_pcm *pcm)
{
	struct snd_pcm_substream *substream;
	struct snd_dma_buffer *buf;
	int stream;

	pr_debug("Entered %s\n", __func__);

	for (stream = 0; stream < 2; stream++) {
		substream = pcm->streams[stream].substream;
		if (!substream)
			continue;

		buf = &substream->dma_buffer;
		if (!buf->area)
			continue;

		iounmap(buf->area);

		buf->area = NULL;
		buf->addr = 0;
	}
}

static int hi6210_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
	int ret = 0;
	struct snd_card *card = rtd->card->snd_card;
	struct snd_pcm  *pcm  = rtd->pcm;

	IN_FUNCTION;

	if (!card->dev->dma_mask)
	{
		logi("dev->dma_mask not set\n");
		card->dev->dma_mask = &hi6210_pcm_dmamask;
	}

	if (!card->dev->coherent_dma_mask)
	{
		logi("dev->coherent_dma_mask not set\n");
		card->dev->coherent_dma_mask = hi6210_pcm_dmamask;
	}


	logi("PLATFORM machine set\n");
	if (pcm->device == 0)
	{
		/* ע��˼�ͨ�����ݽ��պ��� */
		ret = hi6210_notify_isr_register( (void*)hi6210_notify_recv_isr );
		if (ret)
		{
			loge("notify Isr register error : %d\n", ret);
			goto out;
		}
	}

	if(pcm->device > PCM_DEVICE_MAX-1){
		logi("We just alloc space for the first four device \n");
		goto out;
	}
	logi("pcm-device = %d\n", pcm->device);

	if (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) {
		ret = preallocate_dma_buffer(pcm,
				SNDRV_PCM_STREAM_PLAYBACK);
		if (ret)
			goto out;
	}

	if (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) {
		ret = preallocate_dma_buffer(pcm,
				SNDRV_PCM_STREAM_CAPTURE);
		if (ret)
			goto out;
	}
out:
	OUT_FUNCTION;

	return ret;
}

static void hi6210_pcm_free(struct snd_pcm *pcm)
{
	IN_FUNCTION;
	free_dma_buffers(pcm);
	OUT_FUNCTION;
}

struct snd_soc_platform_driver hi6210_pcm_platform = {
	.ops      = &hi6210_pcm_ops,
	.pcm_new  =  hi6210_pcm_new,
	.pcm_free =  hi6210_pcm_free,
};

static int  hi6210_platform_probe(struct platform_device *pdev)
{
	int ret = -ENODEV;

	IN_FUNCTION;
	//logi("hi6210_platform_probe beg\n");
	printk("hi6210_platform_probe beg\n");
	/* register dai (name : hi6210-hifi) */

	ret = snd_soc_register_component(&pdev->dev, &hi6210_pcm_component,
			hi6210_dai, ARRAY_SIZE(hi6210_dai));
	if (ret) {
		loge("snd_soc_register_dai return %d\n" ,ret);
		goto probe_failed;
	}

	/* register platform (name : hi6210-hifi) */
	dev_set_name(&pdev->dev, HI6210_PCM);
	ret = snd_soc_register_platform(&pdev->dev, &hi6210_pcm_platform);
	if (ret) {
		loge("snd_soc_register_platform return %d\n", ret);
		snd_soc_unregister_component(&pdev->dev);
		goto probe_failed;
	}

#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
	hi6210_simu_pcm.simu_pcm_delay_wq = create_singlethread_workqueue("simu_pcm_delay_wq");
	if (!(hi6210_simu_pcm.simu_pcm_delay_wq)) {
		pr_err("%s(%u) : workqueue create failed", __FUNCTION__,__LINE__);
		HiLOGE("audio", "Hi6210_pcm", "%s(%u) : workqueue create failed", __FUNCTION__,__LINE__);
		ret = -ENOMEM;
		goto simu_pcm_wq_failed;
	}
	INIT_DELAYED_WORK(&hi6210_simu_pcm.simu_pcm_delay_work, simu_pcm_work_func);
#endif
#ifdef __DRV_AUDIO_MAILBOX_WORK__
	spin_lock_init(&g_pcm_rtd_playback.lock);
	spin_lock_init(&g_pcm_rtd_capture.lock);
	spin_lock_init(&g_pcm_cp_open_lock);
	spin_lock_init(&g_pcm_pb_open_lock);
#endif

	OUT_FUNCTION;
	logi("hi6210_platform_probe end");

	return ret;

#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
simu_pcm_wq_failed:
	snd_soc_unregister_platform(&pdev->dev);
	snd_soc_unregister_component(&pdev->dev);
#endif

probe_failed:

	OUT_FUNCTION;
	return ret;
}

static int hi6210_platform_remove(struct platform_device *pdev)
{
#ifdef CONFIG_SND_TEST_AUDIO_PCM_LOOP
	if(hi6210_simu_pcm.simu_pcm_delay_wq) {
		cancel_delayed_work(&hi6210_simu_pcm.simu_pcm_delay_work);
		flush_workqueue(hi6210_simu_pcm.simu_pcm_delay_wq);
		destroy_workqueue(hi6210_simu_pcm.simu_pcm_delay_wq);
	}
#endif
	snd_soc_unregister_platform(&pdev->dev);
	snd_soc_unregister_component(&pdev->dev);
	return 0;
}


static const struct of_device_id hi6210_hifi_match_table[] =
{
	{.compatible = HI6210_PCM, },
	{ },
};
static struct platform_driver hi6210_platform_driver = {
	.driver = {
		.name  = HI6210_PCM,
		.owner = THIS_MODULE,
		.of_match_table = hi6210_hifi_match_table,
	},
	.probe  = hi6210_platform_probe,
	.remove = hi6210_platform_remove,
};

static int __init hi6210_init(void)
{
	logi("%s\n",__FUNCTION__);
	return platform_driver_register(&hi6210_platform_driver);
}
module_init(hi6210_init);

static void __exit hi6210_exit(void)
{
	platform_driver_unregister(&hi6210_platform_driver);
}
module_exit(hi6210_exit);

MODULE_AUTHOR("S00212991");
MODULE_DESCRIPTION("Hi6210 HIFI platform driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:hifi");

