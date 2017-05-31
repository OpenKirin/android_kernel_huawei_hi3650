/*
 *	slimbus is a kernel driver which is used to manager SLIMbus devices
 *	Copyright (C) 2014	Hisilicon

 *	This program is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.

 *	This program is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.

 *	You should have received a copy of the GNU General Public License
 *	along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/platform_device.h>
#include <linux/types.h>
#include <linux/delay.h>
#include <linux/clk.h>
#include <linux/regulator/consumer.h>
#include <linux/of.h>
#include <linux/slab.h>
#include <linux/hisi/hilog.h>
#include <linux/pm_runtime.h>
#include <dsm/dsm_pub.h>

#include "hi3630_asp_common.h"

#include "slimbus_utils.h"
#include "slimbus_drv.h"
#include "slimbus.h"
#include "slimbus_6402.h"
#include "slimbus_6403.h"


extern struct dsm_client *dsm_audio_client;

/*lint -e838 -e730 -e747 -e774 -e826 -e529 -e438*/

#define REG_VIR_ADDR_MAP(phyAddr)		 	ioremap(phyAddr, sizeof(unsigned long))
#define REG_VIR_ADDR_UNMAP(virAddr) 	 		iounmap(virAddr)
#define PMU_AUDIOCLK_ADDR				(0xfff34428)

slimbus_channel_property_t audio_playback[SLIMBUS_AUDIO_PLAYBACK_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t audio_capture[SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t voice_down[SLIMBUS_VOICE_DOWN_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t voice_up[SLIMBUS_VOICE_UP_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t img_download[SLIMBUS_IMAGE_DOWNLOAD_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t ec_ref[SLIMBUS_ECREF_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t sound_trigger[SLIMBUS_SOUND_TRIGGER_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t audio_debug[SLIMBUS_DEBUG_CHANNELS] = {{0,{0,},{{0,},},},};
slimbus_channel_property_t audio_hires_playback[SLIMBUS_AUDIO_PLAYBACK_CHANNELS] = {{0,{0,},{{0,},},},};

enum {
	SLIMBUS_TRACK_PLAY_ON                   = 1<<SLIMBUS_TRACK_AUDIO_PLAY,
	SLIMBUS_TRACK_CAPTURE_ON                = 1<<SLIMBUS_TRACK_AUDIO_CAPTURE,
	SLIMBUS_TRACK_VOICE_DOWN_ON             = 1<<SLIMBUS_TRACK_VOICE_DOWN,
	SLIMBUS_TRACK_VOICE_UP_ON               = 1<<SLIMBUS_TRACK_VOICE_UP,
	SLIMBUS_TRACK_IMAGE_LOAD_ON             = 1<<SLIMBUS_TRACK_IMAGE_LOAD,
	SLIMBUS_TRACK_EC_ON                     = 1<<SLIMBUS_TRACK_ECREF,
	SLIMBUS_TRACK_SOUND_TRIGGER_ON          = 1<<SLIMBUS_TRACK_SOUND_TRIGGER,
	SLIMBUS_TRACK_DEBUG_ON                  = 1<<SLIMBUS_TRACK_DEBUG,
	SLIMBUS_TRACK_HIRES_PLAY_ON             = 1<<SLIMBUS_TRACK_HIRES_PLAY,
};


struct slimbus_private_data
{
	struct device 			*dev;
	void __iomem			*base_addr; 		/* SoC SLIMbus base address (virtual address) */
	void __iomem			*asp_reg_base_addr; /* asp address(virtual address) */
	void __iomem			*sctrl_base_addr;	/* sctrl address(virtual address) */
	uint32_t				asp_power_state_offset;
	uint32_t				asp_clk_state_offset;
	int 					irq;				/* SoC SLIMbus irq num */
	struct regulator		*regu_asp;			/* regulator of asp */
	struct pinctrl			*pctrl;
	struct pinctrl_state	*pin_default;		/* pinctrl default */
	struct pinctrl_state	*pin_idle;			/* pinctrl idle */
	struct clk		*pmu_audio_clk; 	/* codec 19.2M clk */
	struct clk		*asp_subsys_clk;
	uint32_t		portstate;
	slimbus_framer_type_t	framerstate;
	slimbus_framer_type_t	lastframer;
	platform_type_t		platform_type;
	slimbus_device_type_t	device_type;
	struct timer_list	timer;
	bool slimbus_dynamic_freq_enable;
	slimbus_device_ops_t *dev_ops;
	bool pm_runtime_support;
};

static struct slimbus_private_data *pdata;
slimbus_device_info_t *slimbus_devices[SLIMBUS_DEVICE_NUM] = {0};
uint32_t slimbus_log_count		= 300;
uint32_t slimbus_rdwrerr_times	= 0;
slimbus_device_info_t *slimbus_dev = NULL;

bool track_state[SLIMBUS_TRACK_MAX];

slimbus_track_config_t track_config_table[SLIMBUS_TRACK_MAX] = {
	/* play back */
	{
		.params.channels = SLIMBUS_AUDIO_PLAYBACK_CHANNELS,
		.params.rate = SLIMBUS_SAMPLE_RATE_48K,
		.params.callback = NULL,
		.channel_pro = &audio_playback[0],
	},
	/* capture */
	{
		.params.channels = SLIMBUS_AUDIO_CAPTURE_MULTI_MIC_CHANNELS,
		.params.rate = SLIMBUS_SAMPLE_RATE_48K,
		.params.callback = NULL,
		.channel_pro = &audio_capture[0],
	},
	/* voice down */
	{
		.params.channels = SLIMBUS_VOICE_DOWN_CHANNELS,
		.params.rate = SLIMBUS_SAMPLE_RATE_8K,
		.params.callback = NULL,
		.channel_pro = &voice_down[0],
	},
	/* voice up */
	{
		.params.channels = SLIMBUS_VOICE_UP_CHANNELS,
		.params.rate = SLIMBUS_SAMPLE_RATE_8K,
		.params.callback = NULL,
		.channel_pro = &voice_up[0],
	},
	/* img download */
	{
		.params.channels = SLIMBUS_IMAGE_DOWNLOAD_CHANNELS,
		.params.rate = SLIMBUS_SAMPLE_RATE_768K,
		.params.callback = NULL,
		.channel_pro = &img_download[0],
	},
	/* ec */
	{
		.params.channels = SLIMBUS_ECREF_CHANNELS,
		.params.rate = SLIMBUS_SAMPLE_RATE_48K,
		.params.callback = NULL,
		.channel_pro = &ec_ref[0],
	},
	/* sound trigger */
	{
		.params.channels = SLIMBUS_SOUND_TRIGGER_CHANNELS,
		.params.rate = SLIMBUS_SAMPLE_RATE_192K,
		.params.callback = NULL,
		.channel_pro = &sound_trigger[0],
	},
	/* debug */
	{
		.params.channels = SLIMBUS_DEBUG_CHANNELS,
		.params.rate = SLIMBUS_SAMPLE_RATE_192K,
		.params.callback = NULL,
		.channel_pro = &audio_debug[0],
	},
	/* hires play */
	{
		.params.channels = SLIMBUS_AUDIO_PLAYBACK_CHANNELS,
		.params.rate = SLIMBUS_SAMPLE_RATE_192K,
		.params.callback = NULL,
		.channel_pro = &audio_hires_playback[0],
	},

};

/*
 * SLIMbus bus configuration
 */
slimbus_bus_config_t bus_config[SLIMBUS_BUS_CONFIG_MAX] = {
	/* normal run */
	{
		.sm = SLIMBUS_SM_1_CSW_32_SL,						/* control space:4; subframe length:32; */
		.cg = SLIMBUS_CG_10,								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
	/* img download */
	{
		.sm = SLIMBUS_SM_3_CSW_8_SL,						/* control space:3; subframe length:8; */
		.cg = SLIMBUS_CG_10,								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
	/* switch framer */
	{
		.sm = SLIMBUS_SM_1_CSW_32_SL,						 /* control space:4; subframe length:32; */
		.cg = SLIMBUS_CG_10, 								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
	/* reg write img download */
	{
		.sm = SLIMBUS_SM_8_CSW_8_SL,						/* control space:8; subframe length:8; */
		.cg = SLIMBUS_CG_10,								/* clock gear*/
		.rf = SLIMBUS_RF_1, 								/* root frequency: 24.576MHZ*/
	},
};


uint32_t slimbus_logcount_get(void)
{
	return slimbus_log_count;
}
EXPORT_SYMBOL(slimbus_logcount_get);

void slimbus_logcount_set(uint32_t count)
{
	slimbus_log_count = count;
}
EXPORT_SYMBOL(slimbus_logcount_set);

uint32_t slimbus_logtimes_get(void)
{
	return slimbus_rdwrerr_times;
}
EXPORT_SYMBOL(slimbus_logtimes_get);

void slimbus_logtimes_set(uint32_t times)
{
	slimbus_rdwrerr_times = times;
}
EXPORT_SYMBOL(slimbus_logtimes_set);


int slimbus_element_read(
				slimbus_device_info_t	*dev,
				int32_t			byte_address,
				slimbus_slice_size_t	slice_size,
				void			*value)
{
	static int slimbus_dmd_flag = 1;
	uint32_t reg_page = byte_address & (~0xff);
	uint8_t *paddr = (uint8_t*)&byte_address;
	uint8_t ret = 0;

	BUG_ON(slice_size >= SLIMBUS_SS_SLICE_BUT);

	mutex_lock(&dev->rw_mutex);
	if (dev->page_sel_addr != reg_page) {
		ret  = slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_0, SLIMBUS_SS_1_BYTE, (paddr+1));
		ret += slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_1, SLIMBUS_SS_1_BYTE, (paddr+2));
		ret += slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_2, SLIMBUS_SS_1_BYTE, (paddr+3));

		dev->page_sel_addr = reg_page;
	}
	ret += slimbus_drv_element_read(dev->generic_la, SLIMBUS_USER_DATA_BASE_ADDR + *paddr, slice_size, (uint8_t *)value);
	mutex_unlock(&dev->rw_mutex);

	if (ret) {
		SLIMBUS_LIMIT_ERR("read error! slice_size=%d, addr=0x%x!\n", slice_size, byte_address);
		if (1 == slimbus_dmd_flag) {
			if (!dsm_client_ocuppy(dsm_audio_client)) {
				dsm_client_record(dsm_audio_client, "slice_size=%d, addr=0x%x\n",slice_size, byte_address);
				dsm_client_notify(dsm_audio_client, DSM_HI6402_SLIMBUS_READ_ERR);
				slimbus_dmd_flag = 0;
			}
		}
		return -EFAULT;
	}
	SLIMBUS_RECOVER_INFO("read recover, slice_size=%d, addr=%x!\n", slice_size, byte_address);

	return 0;
}

int slimbus_element_write(
				slimbus_device_info_t	*dev,
				int32_t			byte_address,
				slimbus_slice_size_t	slice_size,
				void			*value)
{
	uint32_t reg_page = byte_address & (~0xff);
	uint8_t *paddr = (uint8_t*)&byte_address;
	uint8_t ret = 0;

	BUG_ON(slice_size >= SLIMBUS_SS_SLICE_BUT);

	mutex_lock(&dev->rw_mutex);
	if (dev->page_sel_addr != reg_page) {
		ret  = slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_0, SLIMBUS_SS_1_BYTE, (paddr+1));
		ret += slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_1, SLIMBUS_SS_1_BYTE, (paddr+2));
		ret += slimbus_drv_element_write(dev->generic_la, HI6402_PAGE_SELECT_REG_2, SLIMBUS_SS_1_BYTE, (paddr+3));

		dev->page_sel_addr = reg_page;
	}
	ret += slimbus_drv_element_write(dev->generic_la, (SLIMBUS_USER_DATA_BASE_ADDR + *paddr), slice_size, (uint8_t *)value);
	mutex_unlock(&dev->rw_mutex);

	if (ret) {
		SLIMBUS_LIMIT_ERR("write error! slice_size=%d, addr=0x%x!\n", slice_size, byte_address);
		return -EFAULT;
	}
	SLIMBUS_RECOVER_INFO("write recover, slice_size=%d, addr=%x!\n", slice_size, byte_address);

	return 0;
}

unsigned int slimbus_reg_read_u32(unsigned int pAddr)
{
	unsigned int value = 0;
	void __iomem *virAddr = NULL;

	virAddr = REG_VIR_ADDR_MAP(pAddr);
	value = readl(virAddr);
	REG_VIR_ADDR_UNMAP(virAddr);

	return value;
}


unsigned int slimbus_read_1byte(unsigned int reg)
{
	static unsigned int value = 0;
	int retry_count = 0;
	static uint32_t info0 = 0xa1;
	static uint32_t info1 = 0xa2;
	static uint32_t info2 = 0xa3;
	static uint32_t info3 = 0xa4;

	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return ENXIO;
	}

	value = 0x5A;
	do {
		slimbus_element_read(slimbus_dev, reg, SLIMBUS_SS_1_BYTE, &value);

		if (value == 0x5A) {
			SLIMBUS_LIMIT_INFO("SLIMbus read1byte retry: reg:%#x, val:%#x !\n", reg, value);
			retry_count++;
			mdelay(1);
		}
	} while ((value == 0x5A) && (retry_count <= 3));

	if (retry_count > 0) {
		uint32_t pmu_audioclk_val = 0;

		info0 = 0xa1;
		info1 = 0xa2;
		info2 = 0xa3;
		info3 = 0xa4;
		slimbus_drv_request_info(0x21, 0x400, SLIMBUS_SS_1_BYTE, &info0);
		slimbus_drv_request_info(0x40, 0x400, SLIMBUS_SS_1_BYTE, &info1);
		slimbus_drv_request_info(0x20, 0x400, SLIMBUS_SS_1_BYTE, &info2);
		slimbus_drv_request_info(0x41, 0x400, SLIMBUS_SS_1_BYTE, &info3);
		pmu_audioclk_val = slimbus_reg_read_u32(PMU_AUDIOCLK_ADDR);
		SLIMBUS_LIMIT_INFO("SLIMbus info: %#x, %#x, %#x, %#x ! clk: %#x \n", info0, info1, info2, info3, pmu_audioclk_val);
	}
	return value;
}
EXPORT_SYMBOL(slimbus_read_1byte);


unsigned int slimbus_read_4byte(unsigned int reg)
{
	static unsigned int value = 0;
	static int valbyte = 0;
	int retry_count = 0;

	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return -ENXIO;
	}

	value = 0x6A6A6A6A;
	valbyte = 0;
	do {
		slimbus_element_read(slimbus_dev, reg, SLIMBUS_SS_4_BYTES, &value);
		slimbus_element_read(slimbus_dev, 0x20007022, SLIMBUS_SS_1_BYTE, &valbyte);
		slimbus_element_read(slimbus_dev, 0x20007023, SLIMBUS_SS_4_BYTES, &value);

		if (value == 0x6A6A6A6A) {
			SLIMBUS_LIMIT_INFO("SLIMbus read4byte retry: reg:%#x, val:%#x !\n", reg, value);
			retry_count++;
			mdelay(1);
		}
	} while ((value == 0x6A6A6A6A) && (retry_count <= 3));

	return value;
}
EXPORT_SYMBOL(slimbus_read_4byte);

void slimbus_write_1byte(unsigned int reg, unsigned int val)
{
	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return;
	}

	slimbus_element_write(slimbus_dev, reg, SLIMBUS_SS_1_BYTE, &val);
}
EXPORT_SYMBOL(slimbus_write_1byte);

void slimbus_write_4byte(unsigned int reg, unsigned int val)
{
	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return;
	}

	slimbus_element_write(slimbus_dev, reg, SLIMBUS_SS_4_BYTES, &val);
}
EXPORT_SYMBOL(slimbus_write_4byte);

void slimbus_read_pageaddr(void)
{
	static int page0 = 0;
	static int page1 = 0;
	static int page2 = 0;

	if (slimbus_dev == NULL) {
		SLIMBUS_LIMIT_ERR("slimbus device not allocate!\n");
		return;
	}

	page0 = 0xA5;
	page1 = 0xA5;
	page2 = 0xA5;
	mutex_lock(&slimbus_dev->rw_mutex);
	slimbus_drv_element_read(slimbus_dev->generic_la, HI6402_PAGE_SELECT_REG_0, SLIMBUS_SS_1_BYTE, (uint8_t *)&page0);
	slimbus_drv_element_read(slimbus_dev->generic_la, HI6402_PAGE_SELECT_REG_1, SLIMBUS_SS_1_BYTE, (uint8_t *)&page1);
	slimbus_drv_element_read(slimbus_dev->generic_la, HI6402_PAGE_SELECT_REG_2, SLIMBUS_SS_1_BYTE, (uint8_t *)&page2);
	mutex_unlock(&slimbus_dev->rw_mutex);

	pr_info("[%s:%d] cdc page addr:%#x, page0:%#x, page1:%#x, page2:%#x !\n",
		__FUNCTION__, __LINE__, slimbus_dev->page_sel_addr, page0, page1, page2);
}
EXPORT_SYMBOL(slimbus_read_pageaddr);

uint32_t slimbus_trackstate_get(void)
{
	uint32_t trackstate = 0;
	int track;

	for (track = 0; track < SLIMBUS_TRACK_MAX; track++) {
		if (track_state[track])
			trackstate |= (1<<track);
	}

	return trackstate;
}
EXPORT_SYMBOL(slimbus_trackstate_get);

static bool is_play_scene(uint32_t active_tracks)
{
	switch (active_tracks) {
	case SLIMBUS_TRACK_PLAY_ON:
	case SLIMBUS_TRACK_PLAY_ON | SLIMBUS_TRACK_EC_ON:
	case SLIMBUS_TRACK_EC_ON:
		return true;
	default:
		break;
	}

	return false;
}

static bool is_call_only_scene(uint32_t active_tracks)
{
	switch (active_tracks) {
	case SLIMBUS_TRACK_VOICE_UP_ON:
	case SLIMBUS_TRACK_VOICE_DOWN_ON:
	case SLIMBUS_TRACK_VOICE_UP_ON | SLIMBUS_TRACK_VOICE_DOWN_ON:
		return true;
	default:
		break;
	}

	return false;
}

static bool is_anc_call_scene(uint32_t active_tracks)
{
	switch (active_tracks) {
	case SLIMBUS_TRACK_DEBUG_ON:
	case SLIMBUS_TRACK_DEBUG_ON | SLIMBUS_TRACK_PLAY_ON:
	case SLIMBUS_TRACK_DEBUG_ON | SLIMBUS_TRACK_VOICE_UP_ON:
	case SLIMBUS_TRACK_DEBUG_ON | SLIMBUS_TRACK_VOICE_DOWN_ON:
	case SLIMBUS_TRACK_DEBUG_ON | SLIMBUS_TRACK_VOICE_UP_ON | SLIMBUS_TRACK_VOICE_DOWN_ON:
	case SLIMBUS_TRACK_DEBUG_ON | SLIMBUS_TRACK_VOICE_UP_ON | SLIMBUS_TRACK_PLAY_ON:
	case SLIMBUS_TRACK_DEBUG_ON | SLIMBUS_TRACK_VOICE_DOWN_ON | SLIMBUS_TRACK_PLAY_ON:
	case SLIMBUS_TRACK_DEBUG_ON | SLIMBUS_TRACK_VOICE_UP_ON | SLIMBUS_TRACK_VOICE_DOWN_ON | SLIMBUS_TRACK_PLAY_ON:
		if (track_config_table[SLIMBUS_TRACK_DEBUG].params.channels == 2)
			return true;
		break;
	default:
		break;
	}

	return false;
}

static bool is_hires_play_scene(uint32_t active_tracks)
{
	switch (active_tracks) {
	case SLIMBUS_TRACK_HIRES_PLAY_ON:
	case SLIMBUS_TRACK_HIRES_PLAY_ON | SLIMBUS_TRACK_CAPTURE_ON:
	case SLIMBUS_TRACK_HIRES_PLAY_ON | SLIMBUS_TRACK_EC_ON:
	case SLIMBUS_TRACK_HIRES_PLAY_ON | SLIMBUS_TRACK_SOUND_TRIGGER_ON:
	case SLIMBUS_TRACK_HIRES_PLAY_ON | SLIMBUS_TRACK_CAPTURE_ON | SLIMBUS_TRACK_EC_ON:
	case SLIMBUS_TRACK_HIRES_PLAY_ON | SLIMBUS_TRACK_CAPTURE_ON | SLIMBUS_TRACK_SOUND_TRIGGER_ON:
	case SLIMBUS_TRACK_HIRES_PLAY_ON | SLIMBUS_TRACK_EC_ON | SLIMBUS_TRACK_SOUND_TRIGGER_ON:
	case SLIMBUS_TRACK_HIRES_PLAY_ON | SLIMBUS_TRACK_CAPTURE_ON | SLIMBUS_TRACK_EC_ON | SLIMBUS_TRACK_SOUND_TRIGGER_ON:
		return true;
	default:
		break;
	}

	return false;
}

static bool is_scene_conflict(
				slimbus_track_type_t	track,
				slimbus_scene_config_type_t scenes,
				bool track_enable)
{
	bool is_conflict = false;

	if ((((track == SLIMBUS_TRACK_DEBUG) && track_enable)
		|| track_state[SLIMBUS_TRACK_DEBUG])
			&& (track_config_table[SLIMBUS_TRACK_DEBUG].params.channels == 2)
			&& (scenes != SLIMBUS_SCENE_CONFIG_ANC_CALL)) {

		is_conflict = true;
	} else if ((track == SLIMBUS_TRACK_HIRES_PLAY) && (scenes != SLIMBUS_SCENE_CONFIG_HIRES_PLAY)) {
		is_conflict = true;
	} else {
		/*todo hires and call conflict*/
	}

	return is_conflict;
}

static int slimbus_check_scenes(
				slimbus_track_type_t	track,
				slimbus_scene_config_type_t scenes,
				bool track_enable)
{
	unsigned int i = 0;
	int ret = 0;
	bool need_callback = false;

	BUG_ON(track >= SLIMBUS_TRACK_MAX);
	BUG_ON(scenes >= SLIMBUS_SCENE_CONFIG_MAX);

	if (is_scene_conflict(track, scenes, track_enable)) {
		pr_info("[%s:%d] scenes %d conflict, track %d \n",  __FUNCTION__, __LINE__, scenes, track);

		if ((track == SLIMBUS_TRACK_DEBUG) || (track == SLIMBUS_TRACK_HIRES_PLAY)) {
			track_config_table[track].params.channels = 1;
			ret = -EPERM;
			return ret;
		}

		need_callback = true;
		if (track_state[SLIMBUS_TRACK_DEBUG]) {
			ret = slimbus_drv_track_deactivate(track_config_table[SLIMBUS_TRACK_DEBUG].channel_pro,
							track_config_table[SLIMBUS_TRACK_DEBUG].params.channels);

			track_state[SLIMBUS_TRACK_DEBUG] = false;
			track_config_table[SLIMBUS_TRACK_DEBUG].params.channels = 1;
		}
	}

	for (i = 0; i < SLIMBUS_TRACK_MAX; i++) {
		if ((track_state[i] || (i == SLIMBUS_TRACK_DEBUG)) && track_config_table[i].params.callback && need_callback) {
			track_config_table[i].params.callback(i, (void *)&(track_config_table[i].params));
		}
	}

	return ret;
}

static int slimbus_select_scenes(
				struct slimbus_device_info *dev,
				slimbus_track_type_t	track,
				slimbus_track_param_t *params,
				bool track_enable)
{
	slimbus_scene_config_type_t scene_config_type = SLIMBUS_SCENE_CONFIG_NORMAL;
	slimbus_subframe_mode_t sm = SLIMBUS_SM_1_CSW_32_SL;
	slimbus_clock_gear_t	cg = SLIMBUS_CG_10;
	uint32_t active_tracks = 0;
	int ret = 0;

	BUG_ON(track >= SLIMBUS_TRACK_MAX);

	active_tracks = slimbus_trackstate_get();

	if (track_enable) {
		active_tracks |= (1<<track);
	}

	if (SLIMBUS_TRACK_IMAGE_LOAD_ON == active_tracks) {
		scene_config_type = SLIMBUS_SCENE_CONFIG_IMAGE_LOAD;
		cg = SLIMBUS_CG_10;
		sm = SLIMBUS_SM_3_CSW_8_SL;
	} else if (is_play_scene(active_tracks)) {
		scene_config_type = SLIMBUS_SCENE_CONFIG_PLAY;
		cg = SLIMBUS_CG_8;
		sm = SLIMBUS_SM_8_CSW_32_SL;
	} else if (is_call_only_scene(active_tracks)) {
		scene_config_type = SLIMBUS_SCENE_CONFIG_CALL;
		cg = SLIMBUS_CG_8;
		sm = SLIMBUS_SM_6_CSW_24_SL;
	} else if (is_anc_call_scene(active_tracks)) {
		scene_config_type = SLIMBUS_SCENE_CONFIG_ANC_CALL;
		cg = SLIMBUS_CG_10;
		sm = SLIMBUS_SM_1_CSW_32_SL;
	} else if (is_hires_play_scene(active_tracks)) {
		scene_config_type = SLIMBUS_SCENE_CONFIG_HIRES_PLAY;
		cg = SLIMBUS_CG_10;
		sm = SLIMBUS_SM_4_CSW_32_SL;
	} else {
		scene_config_type = SLIMBUS_SCENE_CONFIG_NORMAL;
		cg = SLIMBUS_CG_10;
		sm = SLIMBUS_SM_1_CSW_32_SL;
	}

	ret = slimbus_check_scenes(track, scene_config_type, track_enable);
	if (ret)
		return ret;

	if (dev->scene_config_type != scene_config_type) {
		pr_info("[%s:%d] scene changed from %d to %d\n", __FUNCTION__, __LINE__, dev->scene_config_type, scene_config_type);
		dev->cg = cg;
		dev->sm = sm;
		dev->scene_config_type = scene_config_type;
	}

	slimbus_hi6403_param_update(dev, track, params);

	return 0;
}

static int slimbus_track_soundtrigger_activate(
						slimbus_track_type_t	track,
						struct slimbus_device_info *dev,
						slimbus_track_param_t	*params)
{
	int ret = 0;
	slimbus_sound_trigger_params_t  st_params;
	slimbus_track_param_t st_normal_params;

	if (SLIMBUS_TRACK_SOUND_TRIGGER != track) {
		pr_err("track %d activate is not soundtriger\n", track);
		return -1;
	}

	memset(&st_params, 0, sizeof(st_params));
	memset(&st_normal_params, 0, sizeof(st_normal_params));

	pdata->dev_ops->slimbus_get_soundtrigger_params(&st_params);
	st_normal_params.channels = st_params.channels;
	st_normal_params.rate = st_params.sample_rate;

	ret = pdata->dev_ops->slimbus_device_param_set(dev, st_params.track_type, &st_normal_params);
	ret += pdata->dev_ops->slimbus_device_param_set(dev, track, params);

	/*  request soc slimbus clk to 24.576M */
	slimbus_freq_request();

	if (pdata->slimbus_dynamic_freq_enable) {
		ret = slimbus_drv_track_update(dev->cg, dev->sm, track, track_config_table[track].params.channels, track_config_table[track].channel_pro);
		ret += slimbus_drv_track_update(dev->cg, dev->sm, st_params.track_type, SLIMBUS_VOICE_UP_SOUNDTRIGGER, track_config_table[st_params.track_type].channel_pro);
	} else {
		ret = slimbus_drv_track_activate(track_config_table[track].channel_pro, track_config_table[track].params.channels);
		ret += slimbus_drv_track_activate(track_config_table[st_params.track_type].channel_pro, SLIMBUS_VOICE_UP_SOUNDTRIGGER);
	}

	return ret;

}

int slimbus_track_activate(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track,
				slimbus_track_param_t	*params)
{
	int ret = 0;
	int pm_ret;
	struct slimbus_device_info *dev = NULL;

	if ( (dev_type >= SLIMBUS_DEVICE_NUM) || (track >= SLIMBUS_TRACK_MAX)) {
		pr_err("slimbus activate param err, dev_type %d, track %d\n", dev_type, track);
		return -1;
	}

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	dev = slimbus_devices[dev_type];

	mutex_lock(&dev->track_mutex);

	if (pdata->pm_runtime_support) {
		if (track_state[track]) {
			pr_info("[%s:%d] track:%d has been configured \n", __FUNCTION__, __LINE__, track);
		} else {
			pm_ret = pm_runtime_get_sync(pdata->dev);
			if (pm_ret < 0) {
				pr_err("[%s:%d] pm resume error, track:%d, pm_ret:%d\n", __FUNCTION__, __LINE__, track, pm_ret);
				mutex_unlock(&dev->track_mutex);
				BUG_ON(true);
				return pm_ret;
			}
			if (!slimbus_trackstate_get()) {
				ret = slimbus_switch_framer(pdata->device_type, SLIMBUS_FRAMER_CODEC);
				if (ret) {
					pr_err("[%s:%d] slimbus switch framer to codec failed!\n", __FUNCTION__, __LINE__);
				}
			}
		}
	}

	if (params) {
		track_config_table[track].params.channels = params->channels;
		track_config_table[track].params.rate = params->rate;
		track_config_table[track].params.callback = params->callback;
	}

	if (pdata->slimbus_dynamic_freq_enable) {
		ret = slimbus_select_scenes(dev, track, params, true);
	} else {
		ret = slimbus_check_scenes(track, dev->scene_config_type, true);
	}
	if (ret) {
		pr_err("slimbus activate track %d fail \n", track);
		if (pdata->pm_runtime_support && !track_state[track]) {
			pm_runtime_mark_last_busy(pdata->dev);
			pm_runtime_put_autosuspend(pdata->dev);
		}
		mutex_unlock(&dev->track_mutex);
		return ret;
	}

	if (SLIMBUS_TRACK_SOUND_TRIGGER == track) {
		ret = slimbus_track_soundtrigger_activate(track, dev, params);
	} else {
		ret = pdata->dev_ops->slimbus_device_param_set(dev, track, params);
		if (pdata->slimbus_dynamic_freq_enable) {
			ret += slimbus_drv_track_update(dev->cg, dev->sm, track, track_config_table[track].params.channels, track_config_table[track].channel_pro);
		} else {
			ret += slimbus_drv_track_activate(track_config_table[track].channel_pro, track_config_table[track].params.channels);
		}
	}

	if (!ret) {
		track_state[track] = true;
	}

	mutex_unlock(&dev->track_mutex);

	return ret;
}
EXPORT_SYMBOL(slimbus_track_activate);

static int slimbus_track_soundtrigger_deactivate(slimbus_track_type_t track)
{
	int ret = 0;
	slimbus_sound_trigger_params_t  st_params;

	if (SLIMBUS_TRACK_SOUND_TRIGGER != track) {
		pr_err("track %d deactive is not soundtriger\n", track);
		return -1;
	}

	memset(&st_params, 0, sizeof(st_params));

	pdata->dev_ops->slimbus_get_soundtrigger_params(&st_params);

	/*  release soc slimbus clk to 21.777M */
	slimbus_freq_release();
	ret = slimbus_drv_track_deactivate(track_config_table[track].channel_pro, track_config_table[track].params.channels);
	ret += slimbus_drv_track_deactivate(track_config_table[st_params.track_type].channel_pro, SLIMBUS_VOICE_UP_SOUNDTRIGGER);

	return ret;
}

int slimbus_track_deactivate(
				slimbus_device_type_t	dev_type,
				slimbus_track_type_t	track,
				slimbus_track_param_t	*params)
{
	int ret = 0;
	struct slimbus_device_info *dev = NULL;

	if ((dev_type >= SLIMBUS_DEVICE_NUM) || (track >= SLIMBUS_TRACK_MAX)) {
		pr_err("slimbus deactivate param err, dev_type %d, track %d\n", dev_type, track);
		return -1;
	}

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	dev = slimbus_devices[dev_type];

	mutex_lock(&dev->track_mutex);

	if (pdata->pm_runtime_support) {
		if (!track_state[track]) {
			pr_err("[%s:%d] track:%d has been removed \n", __FUNCTION__, __LINE__, track);
			mutex_unlock(&dev->track_mutex);
			return 0;
		}
	}

	if (params) {
		track_config_table[track].params.channels = params->channels;
		track_config_table[track].params.rate = params->rate;
		track_config_table[track].params.callback = params->callback;
	}

	if (SLIMBUS_TRACK_SOUND_TRIGGER == track) {
		ret = slimbus_track_soundtrigger_deactivate(track);
	} else {
		ret = slimbus_drv_track_deactivate(track_config_table[track].channel_pro, track_config_table[track].params.channels);
	}

	if (!ret) {
		track_state[track] = false;
	} else {
		pr_err("[%s:%d] fail track %d, ret %d\n", __FUNCTION__, __LINE__, track, ret);
	}

	if (pdata->slimbus_dynamic_freq_enable) {
		ret = slimbus_select_scenes(dev, track, NULL, false);
		ret = slimbus_drv_track_update(dev->cg, dev->sm, track, 0, NULL);
	}

	pr_info("[%s:%d] track:%d trackstate:0x%x portstate:0x%x pm_usage_count:0x%x\n", __FUNCTION__, __LINE__,
		track, slimbus_trackstate_get(), slimbus_port_state_get(pdata->base_addr), atomic_read(&(pdata->dev->power.usage_count)));

	if (pdata->pm_runtime_support) {
		if (!slimbus_trackstate_get()) {
			ret = slimbus_switch_framer(pdata->device_type, SLIMBUS_FRAMER_SOC);
			if (ret) {
				pr_err("[%s:%d] slimbus switch framer to soc failed!\n", __FUNCTION__, __LINE__);
			}
		}

		pm_runtime_mark_last_busy(pdata->dev);
		pm_runtime_put_autosuspend(pdata->dev);
	}

	mutex_unlock(&dev->track_mutex);

	return ret;
}
EXPORT_SYMBOL(slimbus_track_deactivate);

int slimbus_switch_framer(
				slimbus_device_type_t	dev_type,
				slimbus_framer_type_t	framer_type)
{
	int ret = -1;
	uint8_t la;
	struct slimbus_device_info *dev = NULL;
	slimbus_bus_config_t   *bus_cfg = NULL;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);
	BUG_ON(framer_type >= SLIMBUS_FRAMER_NUM);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	dev = slimbus_devices[dev_type];

	if (framer_type == SLIMBUS_FRAMER_CODEC) {
		/*  modify soc slimbus clk to 24.576M */
		slimbus_freq_request();
		bus_cfg = &bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER];
	} else if (framer_type == SLIMBUS_FRAMER_SOC) {
		bus_cfg = &bus_config[SLIMBUS_BUS_CONFIG_NORMAL];
		/*  modify soc slimbus clk to low to avoid signal interference to GPS */
		slimbus_freq_release();
	} else {
		pr_err("[%s:%d] invalid framer_type:%#x \n", __FUNCTION__, __LINE__, framer_type);
		return -EINVAL;
	}

	la = slimbus_drv_get_framerla(framer_type);
	if (la == 0) {
		pr_err("[%s:%d] invalid la:%d framer_type:%#x \n", __FUNCTION__, __LINE__, la, framer_type);
		return -EINVAL;
	}

	if (dev->rf == SLIMBUS_RF_6144) {
		if (framer_type == SLIMBUS_FRAMER_CODEC) {
			ret = slimbus_drv_switch_framer(la, 4, 18, bus_cfg);
		} else if (framer_type == SLIMBUS_FRAMER_SOC) {
			ret = slimbus_drv_switch_framer(la, 17, 3, bus_cfg);
		}
	} else if (dev->rf == SLIMBUS_RF_24576) {
		ret = slimbus_drv_switch_framer(la, 4, 3, bus_cfg);
	}

	if (EOK == ret) {
		pdata->framerstate =  framer_type;
	} else {
		pr_err("slimbus_switch_framer faild, ret = %d, framer_type = %d!\n", ret, framer_type);
	}

	return ret;
}
EXPORT_SYMBOL(slimbus_switch_framer);

int slimbus_pause_clock(
				slimbus_device_type_t	dev_type,
				slimbus_restart_time_t	newrestarttime)
{
	int ret = 0;

	BUG_ON(dev_type >= SLIMBUS_DEVICE_NUM);

	if (NULL == slimbus_devices[dev_type]) {
		pr_err("slimbus havn't been init\n");
		return -1;
	}

	ret = slimbus_drv_pause_clock(newrestarttime);

	return ret;
}
EXPORT_SYMBOL(slimbus_pause_clock);


int slimbus_track_recover(void)
{
	int track_type;
	int ret = 0;

	for (track_type = 0; track_type < SLIMBUS_TRACK_MAX; track_type++) {

		if (track_state[track_type]) {
			pr_info("[%s:%d] recover track:%#x \n", __FUNCTION__, __LINE__, track_type);
			ret += slimbus_track_activate(pdata->device_type, track_type, NULL);
		}
	}

	return ret;
}
EXPORT_SYMBOL(slimbus_track_recover);


slimbus_framer_type_t slimbus_debug_get_framer(void)
{
	return pdata->framerstate;
}
EXPORT_SYMBOL(slimbus_debug_get_framer);

int slimbus_bus_configure(slimbus_bus_config_type_t type)
{
	int ret = 0;
	int pm_ret = 0;

	BUG_ON(type >= SLIMBUS_BUS_CONFIG_MAX);

	if (pdata->pm_runtime_support) {
		pm_ret = pm_runtime_get_sync(pdata->dev);
		if (pm_ret < 0) {
			pr_err("[%s:%d] pm resume error, type:%d pm_ret:%d\n", __FUNCTION__, __LINE__, type, pm_ret);
			BUG_ON(true);
			return pm_ret;
		}
	}

	ret = slimbus_drv_bus_configure(&bus_config[type]);

	if (pdata->pm_runtime_support) {
		pm_runtime_mark_last_busy(pdata->dev);
		pm_runtime_put_autosuspend(pdata->dev);
	}

	return ret;
}
EXPORT_SYMBOL(slimbus_bus_configure);



static int slimbus_init_platform_params(const char *platformtype, slimbus_device_type_t device_type, platform_type_t *platform_type)
{
	int ret = 0;
	uint32_t   slimbusclk_drv = 0;
	uint32_t   slimbusdata_drv = 0;

	pr_info("[%s:%d] platform type:%s device_type: %d!\n", __FUNCTION__, __LINE__, platformtype, device_type);

	slimbus_devices[device_type]->rf = SLIMBUS_RF_6144;
	slimbus_devices[device_type]->slimbusclk_drv = 0xA0;
	slimbus_devices[device_type]->slimbusdata_drv = 0xA3;
	*platform_type = PLATFORM_PHONE;

	if(NULL == platformtype){
		pr_info("[%s:%d] platform not define! default:ASIC!\n", __FUNCTION__, __LINE__);
		slimbus_devices[device_type]->rf = SLIMBUS_RF_24576;
		bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_8_CSW_32_SL;
		bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_8_CSW_32_SL;
		bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = SLIMBUS_CG_10;
		slimbus_devices[device_type]->scene_config_type = SLIMBUS_SCENE_CONFIG_NORMAL;
	} else {
		if (!strcmp(platformtype, "ASIC")) {
			slimbus_devices[device_type]->rf = SLIMBUS_RF_24576;
			bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = SLIMBUS_CG_10;
			slimbus_devices[device_type]->scene_config_type = SLIMBUS_SCENE_CONFIG_NORMAL;
		} else if (!strcmp(platformtype, "UDP")) {
			slimbus_devices[device_type]->rf = SLIMBUS_RF_24576;
			slimbus_devices[device_type]->slimbusclk_drv = 0xC0;
			slimbus_devices[device_type]->slimbusdata_drv = 0xC3;
			bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_8_CSW_32_SL;
			bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].cg = SLIMBUS_CG_10;
			slimbus_devices[device_type]->scene_config_type = SLIMBUS_SCENE_CONFIG_NORMAL;
			*platform_type = PLATFORM_UDP;
		} else if (!strcmp(platformtype, "FPGA")) {
			slimbus_devices[device_type]->rf = SLIMBUS_RF_6144;
			if (SLIMBUS_DEVICE_HI6403 == device_type) {
				slimbus_devices[device_type]->scene_config_type = SLIMBUS_SCENE_CONFIG_6144_FPGA;
			}
			*platform_type = PLATFORM_FPGA;
		} else {
			pr_err("platform type define err, platformtype %s!\n", platformtype);
			ret = -EINVAL;
			return ret;
		}
	}

	if (!of_property_read_u32(pdata->dev->of_node, "slimbusclk_io_driver", &slimbusclk_drv)) {
		slimbus_devices[device_type]->slimbusclk_drv = slimbusclk_drv;
	}

	if (!of_property_read_u32(pdata->dev->of_node, "slimbusdata_io_driver", &slimbusdata_drv)) {
		slimbus_devices[device_type]->slimbusdata_drv = slimbusdata_drv;
	}

	if (SLIMBUS_DEVICE_HI6403 == device_type) {
		bus_config[SLIMBUS_BUS_CONFIG_NORMAL].sm = SLIMBUS_SM_1_CSW_32_SL;
		bus_config[SLIMBUS_BUS_CONFIG_SWITCH_FRAMER].sm = SLIMBUS_SM_1_CSW_32_SL;
		slimbus_devices[device_type]->cg = SLIMBUS_CG_10;
		slimbus_devices[device_type]->sm = SLIMBUS_SM_1_CSW_32_SL;
	}

	if (pdata)
		pdata->dev_ops->slimbus_device_param_init(slimbus_devices[device_type]);

	return ret;
}

static void slimbus_hi6402_register(slimbus_device_ops_t *dev_ops)
{
	if (dev_ops == NULL)
		return;

	dev_ops->create_slimbus_device = create_hi6402_slimbus_device;
	dev_ops->release_slimbus_device = release_hi6402_slimbus_device;
	dev_ops->slimbus_device_param_init = slimbus_hi6402_param_init;
	dev_ops->slimbus_device_param_set = slimbus_hi6402_param_set;
	dev_ops->slimbus_device_param_update = NULL;
	dev_ops->slimbus_get_soundtrigger_params = slimbus_hi6402_get_st_params;

	return;
}

static void slimbus_hi6403_register(slimbus_device_ops_t *dev_ops)
{
	if (dev_ops == NULL)
		return;

	dev_ops->create_slimbus_device = create_hi6403_slimbus_device;
	dev_ops->release_slimbus_device = release_hi6403_slimbus_device;
	dev_ops->slimbus_device_param_init = slimbus_hi6403_param_init;
	dev_ops->slimbus_device_param_set = slimbus_hi6403_param_set;
	dev_ops->slimbus_device_param_update = slimbus_hi6403_param_update;
	dev_ops->slimbus_get_soundtrigger_params = slimbus_hi6403_get_st_params;

	return;
}

static int slimbus_probe(struct platform_device *pdev)
{
	struct slimbus_private_data *pd;
	struct device	*dev = &pdev->dev;
	struct resource *resource;
	const char *platformtype = NULL;
	const char *codectype = NULL;
	int   ret          = 0;
	uint32_t   clk_asp_subsys = 0;
	const char *property_value = NULL;
	slimbus_device_ops_t *dev_ops = NULL;

	pd = devm_kzalloc(dev, sizeof(struct slimbus_private_data), GFP_KERNEL);
	if (!pd) {
		dev_err(dev, "not enough memory for slimbus_private_data\n");
		return -ENOMEM;
	}

	/* get pmu audio clk */
	pd->pmu_audio_clk = devm_clk_get(dev, "clk_pmuaudioclk");
	if (IS_ERR_OR_NULL(pd->pmu_audio_clk)) {
		dev_err(dev, "devm_clk_get: pmu_audio_clk not found!\n");
		HiLOGE("audio", "Slimbus", "_clk_get: pmu_audio_clk not found!\n");
		return -EFAULT;
	}

	ret = clk_prepare_enable(pd->pmu_audio_clk);
	if (ret) {
		dev_err(dev, "pmu_audio_clk :clk prepare enable failed !\n");
		HiLOGE("audio","Slimbus", "pmu_audio_clk :clk prepare enable failed !\n");
		goto get_pmu_audio_clk_err;
	}
	mdelay(1);

	pd->asp_subsys_clk = devm_clk_get(dev, "clk_asp_subsys");
	if (IS_ERR_OR_NULL(pd->pmu_audio_clk)) {
		dev_err(dev, "devm_clk_get: clk_asp_subsys not found!\n");
		goto  pmu_audio_clk_enable_err;
	}

	ret = clk_prepare_enable(pd->asp_subsys_clk);
	if (ret) {
		dev_err(dev, "asp_subsys_clk :clk prepare enable failed !\n");
		goto asp_subsys_clk_clk_err;
	}

	/* SLIMbus base address */
	resource = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!resource) {
		dev_err(dev, "get IORESOURCE_MEM failed\n");
		goto asp_subsys_clk_enable_err;
	}

	pd->base_addr = ioremap(resource->start, resource_size(resource));
	if (!pd->base_addr) {
		dev_err(dev, "remap base address %pK failed\n", (void*)resource->start);
		goto asp_subsys_clk_enable_err;
	}

	resource = platform_get_resource(pdev, IORESOURCE_MEM, 1);
	if (!resource) {
		dev_err(dev, "get IORESOURCE_MEM failed\n");
		goto get_aspres_err;
	}

	pd->asp_reg_base_addr = ioremap(resource->start, resource_size(resource));
	if (!pd->asp_reg_base_addr) {
		dev_err(dev, "remap base address %pK failed\n", (void*)resource->start);
		goto get_aspres_err;
	}

	ret = of_property_read_u32(pdev->dev.of_node, "clk_asp_subsys", &clk_asp_subsys);
	if (ret) {
		pr_info("clk_asp_subsyss not define! use default:480000M\n");
		clk_asp_subsys = 480000;
	}

	slimbus_utils_init(pd->asp_reg_base_addr, clk_asp_subsys);

	/* get asp power state address from dts, step next if fail to protect no definition */
	resource = platform_get_resource(pdev, IORESOURCE_MEM, 2);
	if (!resource) {
		dev_err(dev, "get sctrl base addr failed\n");
	} else {
		pd->sctrl_base_addr = ioremap(resource->start, resource_size(resource));
		if (!pd->sctrl_base_addr) {
			dev_err(dev, "remap base address %pK failed\n", (void*)resource->start);
			goto map_asp_err;
		}

		if (of_property_read_u32(pdev->dev.of_node, "asp_power_state_offset", &(pd->asp_power_state_offset))) {
			dev_err(dev, "of_property_read_u32 return error! ret:%d\n", ret);
			goto map_sctrl_err;
		}

		if (of_property_read_u32(pdev->dev.of_node, "asp_clk_state_offset", &(pd->asp_clk_state_offset))) {
			dev_err(dev, "of_property_read_u32 return error! ret:%d\n", ret);
			goto map_sctrl_err;
		}

		pr_info("[%s:%d] sctrl base addr:0x%pK, virtaddr:0x%pK, power-offset:0x%x clk-offset:0x%x\n",
			__FUNCTION__, __LINE__, (void*)resource->start, pd->sctrl_base_addr, pd->asp_power_state_offset, pd->asp_clk_state_offset);
	}

	dev_info(dev, "[%s:%d] virtual address slimbus:%pK, asp:%pK!\n", __FUNCTION__, __LINE__,pd->base_addr, pd->asp_reg_base_addr);

	/* SLIMbus irq */
	pd->irq = platform_get_irq_byname(pdev, "asp_irq_slimbus");
	if (pd->irq < 0) {
		dev_err(dev, "get irq failed\n");
		goto map_sctrl_err;
	}

	pd->regu_asp = devm_regulator_get(dev, "slimbus-reg");
	if (IS_ERR(pd->regu_asp)) {
		dev_err(dev, "couldn't get regulators !\n");
		goto map_sctrl_err;
	}

	ret = regulator_enable(pd->regu_asp);
	if (ret) {
		dev_err(dev, "couldn't enable regulators %d\n", ret);
		goto map_sctrl_err;
	}

	/* ssi&slimbus iomux config */
	pd->pctrl = pinctrl_get(dev);
	if (IS_ERR(pd->pctrl)) {
		dev_err(dev, "could not get pinctrl\n");
		goto get_pinctrl_err;
	}
	pd->pin_default = pinctrl_lookup_state(pd->pctrl, PINCTRL_STATE_DEFAULT);
	if (IS_ERR(pd->pin_default)) {
		dev_err(dev, "%s : could not get defstate (%li)\n", __FUNCTION__ , PTR_ERR(pd->pin_default));
		goto ops_pinctrl_err;
	}
	pd->pin_idle = pinctrl_lookup_state(pd->pctrl, PINCTRL_STATE_IDLE);
	if (IS_ERR(pd->pin_idle)) {
		dev_err(dev, "%s : could not get defstate (%li)\n", __FUNCTION__ , PTR_ERR(pd->pin_idle));
		goto ops_pinctrl_err;
	}

	ret = pinctrl_select_state(pd->pctrl, pd->pin_default);
	if (ret) {
		dev_err(dev, "%s : could not set pins to default state\n", __FUNCTION__);
		HiLOGE("audio","Slimbus", "%s : could not set pins to default state\n", __FUNCTION__);
		goto ops_pinctrl_err;
	}

	dev_ops = kzalloc(sizeof(*dev_ops), GFP_KERNEL);
	if(!dev_ops){
		pr_err("%s : kzalloc error!\n", __FUNCTION__);
		goto ops_pinctrl_err;
	}

	pd->dev_ops = dev_ops;

	pdata = pd;
	pdata->dev = dev;

	pd->device_type = SLIMBUS_DEVICE_HI6402;
	ret = of_property_read_string(pdev->dev.of_node, "codec-type", &codectype);
	if (ret == 0 && !strcmp(codectype, "slimbus-6403es")) {
		pd->device_type = SLIMBUS_DEVICE_HI6403;
		slimbus_hi6403_register(dev_ops);

		ret = dev_ops->create_slimbus_device(&slimbus_devices[SLIMBUS_DEVICE_HI6403], CODEC_HI6403ES);
	} else if (ret == 0 && !strcmp(codectype, "slimbus-6403cs")) {
		pd->device_type = SLIMBUS_DEVICE_HI6403;
		slimbus_hi6403_register(dev_ops);

		ret = dev_ops->create_slimbus_device(&slimbus_devices[SLIMBUS_DEVICE_HI6403], CODEC_HI6403CS);
	} else {
		pd->device_type = SLIMBUS_DEVICE_HI6402;
		slimbus_hi6402_register(dev_ops);

		ret = dev_ops->create_slimbus_device(&slimbus_devices[SLIMBUS_DEVICE_HI6402], CODEC_HI6403ES);
	}

	if (ret) {
		dev_err(dev, "slimbus device create failed! \n");
		goto ops_pinctrl_err;
	}

	pd->slimbus_dynamic_freq_enable = false;
	ret = of_property_read_string(pdev->dev.of_node, "slimbus_dynamic_freq", &property_value);
	if (!ret && (!strcmp(property_value, "true"))) {
		pd->slimbus_dynamic_freq_enable = true;
	} else {
		pd->slimbus_dynamic_freq_enable = false;
	}

	ret = of_property_read_string(pdev->dev.of_node, "platform-type", &platformtype);
	if (ret) {
		dev_err(dev, "of_property_read_string return error! ret:%d\n", ret);
		goto ops_pinctrl_err;
	}

	if (of_property_read_bool(dev->of_node, "pm_runtime_support"))
		pd->pm_runtime_support = true;

	pr_info("[%s:%d] platform type:%s codectype: %s, dynamic freq %d pm_runtime_suppport:%d!\n",
		__FUNCTION__, __LINE__, platformtype, codectype, pd->slimbus_dynamic_freq_enable, pd->pm_runtime_support);

	ret = slimbus_init_platform_params(platformtype, pd->device_type, &(pd->platform_type));
	if (ret) {
		dev_err(dev, "slimbus platform param init fail\n");
		goto release_slimbusdev;
	}

	memset(track_state, 0, sizeof(track_state));

	slimbus_module_enable(slimbus_devices[pd->device_type], true);

	ret = slimbus_drv_init(pd->platform_type, pd->base_addr, pd->asp_reg_base_addr, pd->irq);
	if (ret) {
		dev_err(dev, "slimbus drv init failed!\n");
		goto slimbus_err;
	}

	ret = slimbus_drv_bus_configure(&bus_config[SLIMBUS_BUS_CONFIG_NORMAL]);
	if (ret) {
		dev_err(dev, "slimbus bus configure failed!!\n");
		slimbus_drv_release(pd->irq);
		goto slimbus_err;
	}

	slimbus_dev = slimbus_devices[pd->device_type];

	pd->framerstate = SLIMBUS_FRAMER_SOC;
	pd->lastframer	= SLIMBUS_FRAMER_SOC;
	platform_set_drvdata(pdev, pd);

	if (pd->pm_runtime_support) {
		pm_runtime_use_autosuspend(&pdev->dev);
		pm_runtime_set_autosuspend_delay(&pdev->dev, 200); /* 200ms */
		pm_runtime_set_active(&pdev->dev);
		pm_suspend_ignore_children(&pdev->dev, true);
		pm_runtime_enable(&pdev->dev);
	}

	return 0;

slimbus_err:
release_slimbusdev:
	if (pdata) {
		pdata->dev_ops->release_slimbus_device(slimbus_dev);
	}
ops_pinctrl_err:
	pinctrl_put(pd->pctrl);
	if (dev_ops) {
		kfree(dev_ops);
		dev_ops = NULL;
	}
get_pinctrl_err:
	regulator_disable(pd->regu_asp);
map_sctrl_err:
	iounmap(pd->sctrl_base_addr);
map_asp_err:
	iounmap(pd->asp_reg_base_addr);
	slimbus_utils_deinit();
get_aspres_err:
	iounmap(pd->base_addr);
asp_subsys_clk_enable_err:
	clk_disable_unprepare(pd->asp_subsys_clk);
asp_subsys_clk_clk_err:
	devm_clk_put(dev, pd->asp_subsys_clk);
pmu_audio_clk_enable_err:
	clk_disable_unprepare(pd->pmu_audio_clk);
get_pmu_audio_clk_err:
	devm_clk_put(dev, pd->pmu_audio_clk);

	devm_kfree(&pdev->dev, pd);

	return -EFAULT;
}

static int slimbus_remove(struct platform_device *pdev)
{
	int ret = 0;
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	struct device	*dev = &pdev->dev;

	BUG_ON(NULL == pd);

	if (pd->pm_runtime_support) {
		pm_runtime_resume(dev);
		pm_runtime_disable(dev);
	}

	ret = slimbus_switch_framer(pd->device_type, SLIMBUS_FRAMER_SOC);
	if (ret) {
		dev_err(dev, "switch framer to SLIMBUS_DEVICE_SOC fail, ret:%d\n", ret);
	}

	slimbus_drv_release(pd->irq);

	pd->dev_ops->release_slimbus_device(slimbus_devices[pd->device_type]);

	pinctrl_put(pd->pctrl);
	ret = regulator_disable(pd->regu_asp);
	if (ret) {
		dev_err(dev, "regulator disable failed!, ret:%d\n", ret);
	}

	iounmap(pd->asp_reg_base_addr);
	slimbus_utils_deinit();
	iounmap(pd->base_addr);
	iounmap(pd->sctrl_base_addr);
	clk_disable_unprepare(pd->pmu_audio_clk);
	devm_clk_put(dev, pd->pmu_audio_clk);
	clk_disable_unprepare(pd->asp_subsys_clk);
	devm_clk_put(dev, pd->asp_subsys_clk);
	devm_kfree(dev, pd);

	platform_set_drvdata(pdev, NULL);

	if (pd->pm_runtime_support) {
		pm_runtime_set_suspended(dev);
	}

	return 0;
}

static int slimbus_suspend(struct device *device)
{
	struct platform_device *pdev = to_platform_device(device);
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	int ret = 0;
	int pm_ret = 0;
	uint32_t asppower = 0;
	uint32_t aspclk = 0;

	BUG_ON(NULL == pd);

	if (pd->pm_runtime_support) {
		pm_ret = pm_runtime_get_sync(device);
		if (pm_ret < 0) {
			pr_err("[%s:%d] pm resume error, pm_ret:%d\n", __FUNCTION__, __LINE__, pm_ret);
			BUG_ON(true);
			return pm_ret;
		}
	}

	pd->portstate = slimbus_port_state_get(pd->base_addr);
	pr_info("[%s:%d] portstate:0x%x usage_count:0x%x status:%x, pmuclk:%d aspclk:%d, --\n",__FUNCTION__, __LINE__,
		pd->portstate, atomic_read(&(device->power.usage_count)), device->power.runtime_status,
		clk_get_enable_count(pd->pmu_audio_clk), clk_get_enable_count(pd->asp_subsys_clk));

	if (!pd->portstate) {

		/* make sure last msg has been processed finished */
		mdelay(1);
		slimbus_int_need_clear_set(true);
		/*
		* while fm, hi64xx pll is in high freq, slimbus framer is in codec side
		* we need to switch to soc in this case, and switch to 64xx in resume
		*/

		if (pd->framerstate == SLIMBUS_FRAMER_CODEC) {
			ret = slimbus_switch_framer(pd->device_type, SLIMBUS_FRAMER_SOC);
			if (ret) {
				pr_err("%s : slimbus switch framer failed!\n", __FUNCTION__);
				goto exit;
			}
			pd->lastframer = SLIMBUS_FRAMER_CODEC;
		} else {
			pd->lastframer = SLIMBUS_FRAMER_SOC;
		}

		ret = slimbus_pause_clock(pd->device_type, SLIMBUS_RT_UNSPECIFIED_DELAY);
		if (ret) {
			dev_err(device, "%s : slimbus pause clock failed, ret=%#x\n", __FUNCTION__, ret);
		}
		/* make sure para has updated */
		mdelay(1);

		ret = slimbus_drv_stop();
		if (ret) {
			pr_err("%s : slimbus stop failed!\n", __FUNCTION__);
		}

		/* set pin to  low power mode */
		ret = pinctrl_select_state(pd->pctrl, pd->pin_idle);
		if (ret) {
			dev_err(device, "%s : could not set pins to idle state\n", __FUNCTION__);
			HiLOGE("audio", "Slimbus", "%s : could not set pins to idle state\n", __FUNCTION__);
			goto exit;
		}

		clk_disable_unprepare(pd->pmu_audio_clk);

		ret = regulator_disable(pd->regu_asp);
		if (ret) {
			dev_err(device, "%s : regulator disable failed! \n", __FUNCTION__);
			goto exit;
		}

		clk_disable_unprepare(pd->asp_subsys_clk);
	}

exit:
	asppower = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);
	aspclk = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_clk_state_offset);
	pr_info("[%s:%d] portstate:0x%x asppower:0x%x aspclkstate:0x%x usage_count:0x%x status:%x, pmuclk:%d aspclk:%d, --\n",__FUNCTION__, __LINE__,
		pd->portstate, asppower, aspclk, atomic_read(&(device->power.usage_count)), device->power.runtime_status,
		clk_get_enable_count(pd->pmu_audio_clk), clk_get_enable_count(pd->asp_subsys_clk));

	return ret;
}

static int slimbus_resume(struct device *device)
{
	struct platform_device *pdev = to_platform_device(device);
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	int ret = 0;
	uint32_t asppower = 0;
	uint32_t aspclk = 0;

	BUG_ON(NULL == pd);
	asppower = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);
	aspclk = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_clk_state_offset);

	pr_info("[%s:%d] portstate:0x%x asppower:0x%x aspclkstate:0x%x usage_count:0x%x status:%x, pmuclk:%d aspclk:%d, --\n",__FUNCTION__, __LINE__,
		pd->portstate, asppower, aspclk, atomic_read(&(device->power.usage_count)), device->power.runtime_status,
		clk_get_enable_count(pd->pmu_audio_clk), clk_get_enable_count(pd->asp_subsys_clk));

	if (!pd->portstate) {
		ret = clk_prepare_enable(pd->asp_subsys_clk);
		if (ret) {
			dev_err(device, "asp_subsys_clk :clk prepare enable failed !\n");
			goto exit;
		}

		ret = regulator_enable(pd->regu_asp);
		if (ret) {
			dev_err(device, "couldn't enable regulators %d\n", ret);
			goto exit;
		}

		ret = clk_prepare_enable(pd->pmu_audio_clk);
		if (ret) {
			dev_err(device, "pmu_audio_clk :clk prepare enable failed !\n");
			goto exit;
		}
		/* make sure pmu clk has stable */
		mdelay(1);

		ret = pinctrl_select_state(pd->pctrl, pd->pin_default);
		if (ret) {
			dev_err(device, "could not set pins to default state\n");
			HiLOGE("audio","Slimbus", "%s : could not set pins to default state\n", __FUNCTION__);
			goto exit;
		}

		slimbus_int_need_clear_set(false);

		slimbus_module_enable(slimbus_devices[pd->device_type], true);
		ret = slimbus_drv_resume_clock();
		if (ret) {
			dev_err(device, "slimbus resume clock failed, ret=%d\n", ret);
		}

		ret = slimbus_dev_init(pd->platform_type);
		if (ret) {
			dev_err(device, "slimbus drv init failed!\n");
			goto exit;
		}

		ret = slimbus_drv_bus_configure(&bus_config[SLIMBUS_BUS_CONFIG_NORMAL]);
		if (ret) {
			dev_err(device, "slimbus bus configure failed!!\n");
			goto exit;
		}

		if (pd->lastframer == SLIMBUS_FRAMER_CODEC) {
			ret = slimbus_switch_framer(pd->device_type, SLIMBUS_FRAMER_CODEC);
			pr_info("[%s:%d] switch_framer:%#x + \n", __FUNCTION__, __LINE__,  pdata->lastframer);
		}
	}

exit:
	if (pd->pm_runtime_support) {
		pm_runtime_mark_last_busy(device);
		pm_runtime_put_autosuspend(device);

		pm_runtime_disable(device);
		pm_runtime_set_active(device);
		pm_runtime_enable(device);
	}

	asppower = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);
	aspclk = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_clk_state_offset);
	pr_info("[%s:%d] portstate:0x%x asppower:0x%x aspclkstate:0x%x usage_count:0x%x status:%x, pmuclk:%d aspclk:%d, --\n",__FUNCTION__, __LINE__,
		pd->portstate, asppower, aspclk, atomic_read(&(device->power.usage_count)), device->power.runtime_status,
		clk_get_enable_count(pd->pmu_audio_clk), clk_get_enable_count(pd->asp_subsys_clk));

	return ret;
}

void slimbus_pm_debug(void)
{
	uint32_t asppower = 0;
	uint32_t aspclk = 0;

	asppower = slimbus_asp_state_get(pdata->sctrl_base_addr, pdata->asp_power_state_offset);
	aspclk = slimbus_asp_state_get(pdata->sctrl_base_addr, pdata->asp_clk_state_offset);

	pr_info("[%s:%d] portstate:0x%x trackstate:0x%x asppower:0x%x aspclkstate:0x%x usage_count:0x%x status:%x clk:%d  ++\n",__FUNCTION__, __LINE__,
		pdata->portstate, slimbus_trackstate_get(), asppower, aspclk, atomic_read(&(pdata->dev->power.usage_count)), pdata->dev->power.runtime_status, clk_get_enable_count(pdata->pmu_audio_clk));
}
EXPORT_SYMBOL(slimbus_pm_debug);

static int slimbus_runtime_suspend(struct device *device)
{
	struct platform_device *pdev = to_platform_device(device);
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	int ret = 0;
	uint32_t asppower = 0;
	uint32_t aspclk = 0;

	BUG_ON(NULL == pd);

	pd->portstate = slimbus_port_state_get(pd->base_addr);

	pr_info("[%s:%d] portstate:0x%x trackstate:0x%x usage_count:0x%x status:%x pmuclk:%d aspclk:%d  ++\n",__FUNCTION__, __LINE__,
		pd->portstate, slimbus_trackstate_get(), atomic_read(&(device->power.usage_count)), device->power.runtime_status,
		clk_get_enable_count(pd->pmu_audio_clk), clk_get_enable_count(pd->asp_subsys_clk));

	if (pd->portstate != 0)
		pr_err("[%s:%d] portstate is nozero:0x%x\n", __FUNCTION__, __LINE__, pd->portstate);

	/* make sure last msg has been processed finished */
	mdelay(1);
	slimbus_int_need_clear_set(true);

	ret = slimbus_pause_clock(pd->device_type, SLIMBUS_RT_UNSPECIFIED_DELAY);
	if (ret) {
		pr_err("%s : slimbus pause clock failed, ret=%#x\n", __FUNCTION__, ret);
	}
	/* make sure para has updated */
	mdelay(1);

	clk_disable_unprepare(pd->pmu_audio_clk);

	clk_disable_unprepare(pd->asp_subsys_clk);

	asppower = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);
	aspclk = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_clk_state_offset);
	pr_info("[%s:%d] portstate:0x%x asppower:0x%x aspclkstate:0x%x usage_count:0x%x status:%x, pmuclk:%d aspclk:%d, --\n",__FUNCTION__, __LINE__,
		pd->portstate, asppower, aspclk, atomic_read(&(device->power.usage_count)), device->power.runtime_status,
		clk_get_enable_count(pd->pmu_audio_clk), clk_get_enable_count(pd->asp_subsys_clk));

	return ret;
}

static int slimbus_runtime_resume(struct device *device)
{
	struct platform_device *pdev = to_platform_device(device);
	struct slimbus_private_data *pd = platform_get_drvdata(pdev);
	int ret = 0;
	uint32_t asppower = 0;
	uint32_t aspclk = 0;

	BUG_ON(NULL == pd);

	asppower = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);
	aspclk = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_clk_state_offset);

	pr_info("[%s:%d] portstate:0x%x asppower:0x%x aspclkstate:0x%x usage_count:0x%x status:%x pmuclk:%d aspclk:%d ++\n",__FUNCTION__, __LINE__,
		pd->portstate, asppower, aspclk, atomic_read(&(device->power.usage_count)), device->power.runtime_status,
		clk_get_enable_count(pd->pmu_audio_clk), clk_get_enable_count(pd->asp_subsys_clk));

	if (pd->portstate != 0)
		pr_err("[%s:%d] portstate is nozero:0x%x\n", __FUNCTION__, __LINE__, pd->portstate);

	ret = clk_prepare_enable(pd->asp_subsys_clk);
	if (ret) {
		pr_err("asp_subsys_clk :clk prepare enable failed !\n");
		goto exit;
	}

	ret = clk_prepare_enable(pd->pmu_audio_clk);
	if (ret) {
		pr_err("pmu_audio_clk :clk prepare enable failed !\n");
		goto exit;
	}
	/* make sure pmu clk has stable */
	mdelay(1);

	slimbus_int_need_clear_set(false);

	ret = slimbus_drv_resume_clock();
	if (ret) {
		pr_err("slimbus resume clock failed, ret=%d\n", ret);
	}

exit:
	asppower = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_power_state_offset);
	aspclk = slimbus_asp_state_get(pd->sctrl_base_addr, pd->asp_clk_state_offset);
	pr_info("[%s:%d] portstate:0x%x asppower:0x%x aspclkstate:0x%x usage_count:0x%x status:%x, pmuclk:%d aspclk:%d, --\n",__FUNCTION__, __LINE__,
		pd->portstate, asppower, aspclk, atomic_read(&(device->power.usage_count)), device->power.runtime_status,
		clk_get_enable_count(pd->pmu_audio_clk), clk_get_enable_count(pd->asp_subsys_clk));

	return ret;
}

static const struct dev_pm_ops slimbus_pm_ops = {
	SET_SYSTEM_SLEEP_PM_OPS(slimbus_suspend, slimbus_resume)
	SET_RUNTIME_PM_OPS(slimbus_runtime_suspend, slimbus_runtime_resume, NULL)
};

static const struct of_device_id slimbus_match[] = {
	{
		.compatible = "candance,slimbus",
	},
	{},
};
MODULE_DEVICE_TABLE(of, slimbus_match);

static struct platform_driver slimbus_driver = {
	.probe	= slimbus_probe,
	.remove = slimbus_remove,
	.driver = {
		.name	= "hisilicon,slimbus",
		.owner	= THIS_MODULE,
		.pm = &slimbus_pm_ops,
		.of_match_table = slimbus_match,
	},
};

static int __init slimbus_init(void)
{
	int ret;

	ret = platform_driver_register(&slimbus_driver);
	if (ret) {
		pr_err("driver register failed\n");
		HiLOGE("audio","Slimbus", "driver register failed\n");
	}

	return ret;
}

static void __exit slimbus_exit(void)
{
	platform_driver_unregister(&slimbus_driver);
}
fs_initcall(slimbus_init);
module_exit(slimbus_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Hisilicon");

