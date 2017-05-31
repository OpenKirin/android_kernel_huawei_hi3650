#include "isp_metadata_vendor_tag.h"
#ifdef HISP_V150
#include <media/huawei/hisp150_msg.h>
#else
#include <media/huawei/hisp_msg.h>
#endif
#define YUVSC_MAX_RATIO             4
#define METADATA_BUFFER_SIZE    0x00096000

typedef struct _msg_qurey_handler_t {
	unsigned int cmd_id;
	int (*handler)(hisp_msg_t *msg, isp_metadata_t *p_metadata);
} msg_qurey_handler_t;

int query_max_digital_zoom(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	unsigned int ratio;

	ratio = YUVSC_MAX_RATIO;

	ret =
	    isp_metadata_set(p_metadata,
			     ANDROID_SCALER_AVAILABLE_MAX_DIGITAL_ZOOM, &ratio,
			     sizeof(ratio), 1);
	return ret;
}

int query_face_detect_modes(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t availableFaceDetectModes[] = {
		ANDROID_STATISTICS_FACE_DETECT_MODE_OFF,
		ANDROID_STATISTICS_FACE_DETECT_MODE_SIMPLE,
		ANDROID_STATISTICS_FACE_DETECT_MODE_FULL
	};
	ret =
	    isp_metadata_set(p_metadata,
			     ANDROID_STATISTICS_INFO_AVAILABLE_FACE_DETECT_MODES,
			     availableFaceDetectModes, sizeof(uint8_t),
			     sizeof(availableFaceDetectModes) /
			     sizeof(uint8_t));
	return ret;
}

int query_max_regions(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	unsigned int max3aRegions[] = { 1, 1, 1 };

	ret = isp_metadata_set(p_metadata, ANDROID_CONTROL_MAX_REGIONS,
			       max3aRegions, sizeof(unsigned int),
			       sizeof(max3aRegions) / sizeof(unsigned int));
	return ret;
}

int query_ae_avaliable_modes(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t availableAeModes[] = {
		ANDROID_CONTROL_AE_MODE_OFF,
		ANDROID_CONTROL_AE_MODE_ON,
		ANDROID_CONTROL_AE_MODE_ON_AUTO_FLASH,
		ANDROID_CONTROL_AE_MODE_ON_ALWAYS_FLASH,
		/* CAMERA_FLASH_TORCH */
	};
	ret = isp_metadata_set(p_metadata, ANDROID_CONTROL_AE_AVAILABLE_MODES,
			       availableAeModes, sizeof(uint8_t),
			       sizeof(availableAeModes) / sizeof(uint8_t));
	return ret;
}

int query_ae_compensation_step(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	camera_rational_t exposureCompensationStep = { 1, 1 };

	ret = isp_metadata_set(p_metadata, ANDROID_CONTROL_AE_COMPENSATION_STEP,
			       &exposureCompensationStep,
			       sizeof(exposureCompensationStep), 1);
	return ret;
}

int query_awb_avaliable_modes(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t availableAwbModes[] = {
		ANDROID_CONTROL_AWB_MODE_AUTO,
		ANDROID_CONTROL_AWB_MODE_INCANDESCENT,
		ANDROID_CONTROL_AWB_MODE_FLUORESCENT,
		ANDROID_CONTROL_AWB_MODE_DAYLIGHT,
		ANDROID_CONTROL_AWB_MODE_CLOUDY_DAYLIGHT,
	};
	ret = isp_metadata_set(p_metadata, ANDROID_CONTROL_AWB_AVAILABLE_MODES,
			       availableAwbModes, sizeof(uint8_t),
			       sizeof(availableAwbModes) / sizeof(uint8_t));
	return ret;
}

int query_max_face_count(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	unsigned int maxFaceCount = 10;

	ret = isp_metadata_set(p_metadata
			     , ANDROID_STATISTICS_INFO_MAX_FACE_COUNT,
			     &maxFaceCount, sizeof(maxFaceCount), 1);
	return ret;
}

int query_compensation_range(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	int exposureCompensationRange[] = { -2, 2 };

	ret = isp_metadata_set(p_metadata
			     , ANDROID_CONTROL_AE_COMPENSATION_RANGE,
			     exposureCompensationRange, sizeof(int),
			     sizeof(exposureCompensationRange) / sizeof(int));
	return ret;
}

int query_manual_vcm_start(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	int manualVcmStart = 0;

	ret = isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_MANUAL_VCM_START_VALUE,
			     &manualVcmStart, sizeof(manualVcmStart), 1);
	return ret;
}

int query_manual_vcm_end(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	int manualVcmEnd = 1023;

	ret = isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_MANUAL_VCM_END_VALUE,
			     &manualVcmEnd, sizeof(manualVcmEnd), 1);
	return ret;
}

int query_supported_metering(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t metering[] = {
		(uint8_t) ANDROID_HW_METERING_AVERAGE,
		ANDROID_HW_METERING_CENTER_WEIGHTED,
		ANDROID_HW_METERING_SPOT,
		ANDROID_HW_METERING_MATRIX
	};
	ret =
	    isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_SUPPORTED_METERING,
			     metering, sizeof(uint8_t),
			     sizeof(metering) / sizeof(uint8_t));
	return ret;
}

int query_supported_hdr_movie(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t supportedHdrMovie = 0;

	ret = isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_HDR_MOVIE_SUPPORTED,
			     &supportedHdrMovie, sizeof(supportedHdrMovie), 1);
	return ret;
}

int query_supported_sharpness(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t supportedSharpnessValues[] = {
		ANDROID_HW_SHARPNESS_AUTO,
		ANDROID_HW_SHARPNESS_1,
		ANDROID_HW_SHARPNESS_2,
		ANDROID_HW_SHARPNESS_3,
		ANDROID_HW_SHARPNESS_4,
		ANDROID_HW_SHARPNESS_5
	};
	ret =
	    isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_SUPPORTED_SHARPNESS,
			     supportedSharpnessValues, sizeof(uint8_t),
			     sizeof(supportedSharpnessValues) /
			     sizeof(uint8_t));
	return ret;
}

int query_supported_brightness(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t supportedBrightnessValues[] = {
		ANDROID_HW_BRIGHTNESS_NEGATIVE2,
		ANDROID_HW_BRIGHTNESS_NEGATIVE1,
		ANDROID_HW_BRIGHTNESS_0,
		ANDROID_HW_BRIGHTNESS_POSITIVE1,
		ANDROID_HW_BRIGHTNESS_POSITIVE2
	};
	ret =
	    isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_SUPPORTED_BRIGHTNESS,
			     supportedBrightnessValues, sizeof(uint8_t),
			     sizeof(supportedBrightnessValues) /
			     sizeof(uint8_t));
	return ret;
}

int query_supported_saturation(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t supportedSaturationValues[] = {
		ANDROID_HW_SATURATION_NEGATIVE2,
		ANDROID_HW_SATURATION_NEGATIVE1,
		ANDROID_HW_SATURATION_0,
		ANDROID_HW_SATURATION_POSITIVE1,
		ANDROID_HW_SATURATION_POSITIVE2
	};
	ret =
	    isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_SUPPORTED_SATURATION,
			     supportedSaturationValues, sizeof(uint8_t),
			     sizeof(supportedSaturationValues) /
			     sizeof(uint8_t));
	return ret;
}

int query_supported_contrast(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t supportedContrastValues[] = {
		ANDROID_HW_CONTRAST_NEGATIVE2,
		ANDROID_HW_CONTRAST_NEGATIVE1,
		ANDROID_HW_CONTRAST_0,
		ANDROID_HW_CONTRAST_POSITIVE1,
		ANDROID_HW_CONTRAST_POSITIVE2
	};
	ret =
	    isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_SUPPORTED_CONTRAST,
			     supportedContrastValues, sizeof(uint8_t),
			     sizeof(supportedContrastValues) / sizeof(uint8_t));
	return ret;
}

int query_expowure_comp_supported(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t expowureCompSupported = ANDROID_HW_TRUE;

	ret = isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_EXPOWURE_COMP_SUPPORTED,
			     &expowureCompSupported,
			     sizeof(expowureCompSupported), 1);
	return ret;
}

int query_expowure_comp_step(hisp_msg_t *msg, isp_metadata_t *p_metadata)
{
	int ret;
	int expowureCompStep = 1;

	ret = isp_metadata_set(p_metadata,
			     (unsigned int)ANDROID_HW_EXPOWURE_COMP_STEP,
			     &expowureCompStep, sizeof(expowureCompStep), 1);
	return ret;
}

int query_video_stabilization_modes(hisp_msg_t *msg,
				    isp_metadata_t *p_metadata)
{
	int ret;
	uint8_t videoStabilizationMode = ANDROID_HW_TRUE;

	ret = isp_metadata_set(p_metadata, (unsigned int)
			       ANDROID_HW_AVAILABLE_VIDEO_STABILIZATION_MODES,
			       &videoStabilizationMode,
			       sizeof(videoStabilizationMode), 1);
	return ret;
}

/* static */
msg_qurey_handler_t querey_cap_list[] = {
	{ANDROID_SCALER_AVAILABLE_MAX_DIGITAL_ZOOM, query_max_digital_zoom}
	,
	{ANDROID_STATISTICS_INFO_AVAILABLE_FACE_DETECT_MODES,
	 query_face_detect_modes}
	,
	{ANDROID_CONTROL_MAX_REGIONS, query_max_regions}
	,
	{ANDROID_CONTROL_AE_AVAILABLE_MODES, query_ae_avaliable_modes}
	,
	{ANDROID_CONTROL_AE_COMPENSATION_STEP, query_ae_compensation_step}
	,
	{ANDROID_CONTROL_AWB_AVAILABLE_MODES, query_awb_avaliable_modes}
	,
	{ANDROID_STATISTICS_INFO_MAX_FACE_COUNT, query_max_face_count}
	,
	{ANDROID_CONTROL_AE_COMPENSATION_RANGE, query_compensation_range}
	,
	{(unsigned int)ANDROID_HW_MANUAL_VCM_START_VALUE,
	 query_manual_vcm_start},
	{(unsigned int)ANDROID_HW_MANUAL_VCM_END_VALUE, query_manual_vcm_end},
	{(unsigned int)ANDROID_HW_SUPPORTED_METERING, query_supported_metering},
	/* {ANDROID_HW_HDR_MOVIE_SUPPORTED, query_supported_hdr_movie}, */
	{(unsigned int)ANDROID_HW_SUPPORTED_SHARPNESS,
	 query_supported_sharpness},
	{(unsigned int)ANDROID_HW_SUPPORTED_BRIGHTNESS,
	 query_supported_brightness},
	{(unsigned int)ANDROID_HW_SUPPORTED_SATURATION,
	 query_supported_saturation},
	{(unsigned int)ANDROID_HW_SUPPORTED_CONTRAST, query_supported_contrast},
	{(unsigned int)ANDROID_HW_EXPOWURE_COMP_SUPPORTED,
	 query_expowure_comp_supported},
	{(unsigned int)ANDROID_HW_EXPOWURE_COMP_STEP, query_expowure_comp_step},
	{(unsigned int)ANDROID_HW_AVAILABLE_VIDEO_STABILIZATION_MODES,
	 query_video_stabilization_modes},
};
