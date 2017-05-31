

#include "../../metadata/isp_metadata_vendor_tag.h"
#include "../../metadata/camera_metadata_tags.h"
#include  "simulated_cis_if.h"
#include  "../../metadata/simulated_utils.h"
#ifndef NULL
#define NULL ((void *)0)
#endif

unsigned int imx214_sunny_position;
unsigned char imx214_sunny_lens_facing = ANDROID_LENS_FACING_BACK;
unsigned int imx214_sunny_orientation = 90;
unsigned int imx214_sunny_jpeg_orientation = 90;
unsigned char imx214_sunny_flash_available = 1;
float imx214_sunny_focal_lengths = 4.5f;	/*< 2.38mm */
float imx214_sunny_aperture = 2.2;
unsigned int imx214_sunny_eq_focus = 27;	/* mm */
float imx214_sunny_min_focus_distance = 10.0;	/* mm */

unsigned char imx214dual_availableAfModesBack[] = {
	ANDROID_CONTROL_AF_MODE_AUTO,
	/* CAMERA_FOCUS_INFINITY, */
	ANDROID_CONTROL_AF_MODE_MACRO,
	ANDROID_CONTROL_AF_MODE_CONTINUOUS_VIDEO,
	ANDROID_CONTROL_AF_MODE_CONTINUOUS_PICTURE
};

int imx214dual_resolution[2] = {
	4160, 3120
};

int imx214dual_availableRawSize[2] = {
	4160, 3120
};

unsigned int imx214dual_availableProcessedSizesBack[] = {
	1280, 720,
	1280, 960,
	1440, 1080,
	1920, 1080,
	208, 144,
	176, 144,
	240, 160,
	352, 288,
	320, 240,
	480, 320,
	640, 480,
	800, 480,
	960, 544,
	960, 720,
	720, 720
};

unsigned int imx214dual_availableJpegSizesBack[] = {
	640, 480,
	2048, 1536,
	2592, 1952,
	3264, 1840,
	3264, 2448,
};

float imx214dual_sensorPhysicalSize[] = {
	4.60f,
	3.40f,
};				/* mm */

unsigned int imx214_sunny_videoFPSRange[] = { 120 };

cis_capability imx214dual_capability[] = {
	{(unsigned int)ANDROID_SENSOR_INFO_PHYSICAL_SIZE,
	 imx214dual_sensorPhysicalSize, sizeof(float),
	 sizeof(imx214dual_sensorPhysicalSize) / sizeof(float)},
	{(unsigned int)ANDROID_HUAWEI_DEVICE_SENSOR_POSITION,
	 &imx214_sunny_position, sizeof(unsigned int),
	 sizeof(imx214_sunny_position) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_LENS_FACING, &imx214_sunny_lens_facing,
	 sizeof(unsigned char),
	 sizeof(imx214_sunny_lens_facing) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE,
	 imx214dual_resolution, sizeof(int),
	 sizeof(imx214dual_resolution) / sizeof(int)},
	{(unsigned int)ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE,
	 imx214dual_resolution, sizeof(int),
	 sizeof(imx214dual_resolution) / sizeof(int)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_RAW_SIZES,
	 imx214dual_availableRawSize, sizeof(int),
	 sizeof(imx214dual_availableRawSize) / sizeof(int)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_PROCESSED_SIZES,
	 imx214dual_availableProcessedSizesBack, sizeof(unsigned int),
	 sizeof(imx214dual_availableProcessedSizesBack) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_JPEG_SIZES,
	 imx214dual_availableJpegSizesBack, sizeof(unsigned int),
	 sizeof(imx214dual_availableJpegSizesBack) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_SENSOR_ORIENTATION, &imx214_sunny_orientation,
	 sizeof(unsigned int),
	 sizeof(imx214_sunny_orientation) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_JPEG_ORIENTATION, &imx214_sunny_jpeg_orientation,
	 sizeof(unsigned int),
	 sizeof(imx214_sunny_jpeg_orientation) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_FLASH_INFO_AVAILABLE,
	 &imx214_sunny_flash_available, sizeof(unsigned char),
	 sizeof(imx214_sunny_flash_available) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_CONTROL_AF_AVAILABLE_MODES,
	 imx214dual_availableAfModesBack, sizeof(unsigned char),
	 sizeof(imx214dual_availableAfModesBack) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_LENS_APERTURE, &imx214_sunny_aperture,
	 sizeof(float), sizeof(imx214_sunny_aperture) / sizeof(float)},
	{(unsigned int)ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS,
	 &imx214_sunny_focal_lengths, sizeof(float),
	 sizeof(imx214_sunny_focal_lengths) / sizeof(float)},
	{(unsigned int)ANDROID_HW_EQUIVALENT_FOCUS, &imx214_sunny_eq_focus,
	 sizeof(unsigned int),
	 sizeof(imx214_sunny_eq_focus) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_LENS_INFO_MINIMUM_FOCUS_DISTANCE,
	 &imx214_sunny_min_focus_distance, sizeof(float),
	 sizeof(imx214_sunny_min_focus_distance) / sizeof(float)},
	{(unsigned int)ANDROID_HW_VIDEO_FPS_SUPPORTED,
	 &imx214_sunny_videoFPSRange, sizeof(unsigned int),
	 sizeof(imx214_sunny_videoFPSRange) / sizeof(unsigned int)},
};

/* common implements */
int imx214_sunny_cis_get_capability(isp_metadata_t *metadata)
{
	if (NULL == metadata)
		return -1;

	unsigned int i = 0;

	for (i = 0; i < array_count(imx214dual_capability); i++) {
		isp_metadata_set(metadata,
				 imx214dual_capability[i].tag,
				 imx214dual_capability[i].value,
				 imx214dual_capability[i].type_size,
				 imx214dual_capability[i].count);
	}

	return 0;
}
