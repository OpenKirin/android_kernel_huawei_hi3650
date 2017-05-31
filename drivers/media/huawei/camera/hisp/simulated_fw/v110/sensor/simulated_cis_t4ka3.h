

#include "../../metadata/isp_metadata_vendor_tag.h"
#include  "../../metadata/simulated_utils.h"
uint8_t t4ka3_lensFacing = ANDROID_LENS_FACING_FRONT;

float t4ka3_minFocusDistance = 0.0;

int t4ka3_mOrientation = 270;

int t4ka3_mJpegOrientation = 270;

float t4ka3_focalLength = 2.38f;	/* mm */

uint8_t t4ka3_flashAvailable;

uint8_t t4ka3_availableAfModesFront[] = {
	ANDROID_CONTROL_AF_MODE_OFF
};

float t4ka3_sensorPhysicalSize[2] = { 3.20f, 2.40f };	/* mm */

uint32_t t4ka3_kAvailableJpegSizesFront[] = {
	640, 480,
	1280, 720,
	1280, 800,
	1280, 960,
	2592, 1952,
	2592, 1456,
	3264, 1840,
	3264, 2448
};

uint32_t t4ka3_kAvailableProcessedSizesFront[] = {
	640, 480,
	1280, 720,
	1280, 960,
	1440, 1080,
	1920, 1080,
	208, 144,
	176, 144,
	352, 288,
	320, 240,
/* cts testDigitalZoomPreviewCombinations wil failed .
because AR is 1.32 */
	/* 720, 544, */
	960, 544,
	960, 720,
	720, 720,
};

cis_capability t4ka3_capability[] = {
	{(unsigned int)ANDROID_LENS_FACING, &t4ka3_lensFacing, sizeof(uint8_t),
	 sizeof(t4ka3_lensFacing) / sizeof(uint8_t)}
	,
	{(unsigned int)ANDROID_LENS_INFO_MINIMUM_FOCUS_DISTANCE,
	 &t4ka3_minFocusDistance, sizeof(float),
	 sizeof(t4ka3_minFocusDistance) / sizeof(float)},
	{(unsigned int)ANDROID_SENSOR_ORIENTATION, &t4ka3_mOrientation,
	 sizeof(unsigned int),
	 sizeof(t4ka3_mOrientation) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_JPEG_ORIENTATION, &t4ka3_mJpegOrientation,
	 sizeof(unsigned int),
	 sizeof(t4ka3_mJpegOrientation) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS,
	 &t4ka3_focalLength, sizeof(float),
	 sizeof(t4ka3_focalLength) / sizeof(float)},
	{(unsigned int)ANDROID_FLASH_INFO_AVAILABLE, &t4ka3_flashAvailable,
	 sizeof(unsigned char),
	 sizeof(t4ka3_flashAvailable) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_CONTROL_AF_AVAILABLE_MODES,
	 t4ka3_availableAfModesFront, sizeof(unsigned char),
	 sizeof(t4ka3_availableAfModesFront) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_SENSOR_INFO_PHYSICAL_SIZE,
	 t4ka3_sensorPhysicalSize, sizeof(float),
	 sizeof(t4ka3_sensorPhysicalSize) / sizeof(float)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_JPEG_SIZES,
	 t4ka3_kAvailableJpegSizesFront, sizeof(unsigned int),
	 sizeof(t4ka3_kAvailableJpegSizesFront) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_PROCESSED_SIZES,
	 t4ka3_kAvailableProcessedSizesFront, sizeof(unsigned int),
	 sizeof(t4ka3_kAvailableProcessedSizesFront) / sizeof(unsigned int)},

};

int t4ka3_cis_get_capability(isp_metadata_t *metadata)
{
	if (NULL == metadata)
		return -1;

	unsigned int i = 0;

	for (i = 0; i < array_count(t4ka3_capability); i++) {
		isp_metadata_set(metadata,
				 t4ka3_capability[i].tag,
				 t4ka3_capability[i].value,
				 t4ka3_capability[i].type_size,
				 t4ka3_capability[i].count);
	}
	return 0;
}
