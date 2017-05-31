

#include "../../metadata/isp_metadata_vendor_tag.h"
#include "../../metadata/camera_metadata_tags.h"
#include  "../../metadata/simulated_utils.h"
#ifndef NULL
#define NULL ((void *)0)
#endif

static unsigned int imx286dual_position;
static unsigned char imx286dual_lens_facing = ANDROID_LENS_FACING_BACK;
static unsigned int imx286dual_orientation = 90;
static unsigned int imx286dual_jpeg_orientation = 90;
static unsigned char imx286dual_flash_available = 1;
static float imx286dual_focal_lengths = 4.5f;	/*< 2.38mm */
static float imx286dual_aperture = 2.2;
static unsigned int imx286dual_eq_focus = 27;	/* mm */
static float imx286dual_min_focus_distance = 10.0;	/* mm */

static unsigned char imx286dual_availableAfModesBack[] = {
	ANDROID_CONTROL_AF_MODE_AUTO,
	/* CAMERA_FOCUS_INFINITY, */
	ANDROID_CONTROL_AF_MODE_MACRO,
	ANDROID_CONTROL_AF_MODE_CONTINUOUS_VIDEO,
	ANDROID_CONTROL_AF_MODE_CONTINUOUS_PICTURE
};

static int imx286dual_resolution[2] = {
	3968, 2976
};

static int imx286dual_availableRawSize[2] = {
	3968, 2976
};

static unsigned int imx286dual_availableProcessedSizesBack[] = {
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

static unsigned int imx286dual_availableJpegSizesBack[] = {
	640, 480,
	2048, 1536,
	2592, 1952,
	2976, 2976,
	3264, 1840,
	3264, 2448,
	3968, 2976,
};

static float imx286dual_sensorPhysicalSize[] = {
	4.60f,
	3.40f,
};				/* mm */

static const unsigned int imx286dual_videoFPSRange[] = { 120, 60 };

cis_capability imx286dual_capability[] = {
	{(unsigned int)ANDROID_SENSOR_INFO_PHYSICAL_SIZE,
	 imx286dual_sensorPhysicalSize, sizeof(float),
	 sizeof(imx286dual_sensorPhysicalSize) / sizeof(float)},
	{(unsigned int)ANDROID_HUAWEI_DEVICE_SENSOR_POSITION,
	 &imx286dual_position, sizeof(unsigned int),
	 sizeof(imx286dual_position) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_LENS_FACING, &imx286dual_lens_facing,
	 sizeof(unsigned char),
	 sizeof(imx286dual_lens_facing) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_RAW_SIZES,
	 imx286dual_availableRawSize, sizeof(int),
	 sizeof(imx286dual_availableRawSize) / sizeof(int)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_PROCESSED_SIZES,
	 imx286dual_availableProcessedSizesBack, sizeof(unsigned int),
	 sizeof(imx286dual_availableProcessedSizesBack) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_JPEG_SIZES,
	 imx286dual_availableJpegSizesBack, sizeof(unsigned int),
	 sizeof(imx286dual_availableJpegSizesBack) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_SENSOR_ORIENTATION, &imx286dual_orientation,
	 sizeof(unsigned int),
	 sizeof(imx286dual_orientation) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_JPEG_ORIENTATION, &imx286dual_jpeg_orientation,
	 sizeof(unsigned int),
	 sizeof(imx286dual_jpeg_orientation) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_FLASH_INFO_AVAILABLE,
	 &imx286dual_flash_available, sizeof(unsigned char),
	 sizeof(imx286dual_flash_available) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_CONTROL_AF_AVAILABLE_MODES,
	 imx286dual_availableAfModesBack, sizeof(unsigned char),
	 sizeof(imx286dual_availableAfModesBack) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_LENS_APERTURE, &imx286dual_aperture,
	 sizeof(float), sizeof(imx286dual_aperture) / sizeof(float)},
	{(unsigned int)ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS,
	 &imx286dual_focal_lengths, sizeof(float),
	 sizeof(imx286dual_focal_lengths) / sizeof(float)},
	{(unsigned int)ANDROID_HW_EQUIVALENT_FOCUS, &imx286dual_eq_focus,
	 sizeof(unsigned int),
	 sizeof(imx286dual_eq_focus) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_LENS_INFO_MINIMUM_FOCUS_DISTANCE,
	 &imx286dual_min_focus_distance, sizeof(float),
	 sizeof(imx286dual_min_focus_distance) / sizeof(float)},
	{(unsigned int)ANDROID_HW_VIDEO_FPS_SUPPORTED,
	 &imx286dual_videoFPSRange, sizeof(unsigned int),
	 sizeof(imx286dual_videoFPSRange) / sizeof(unsigned int)},
};

int imx286dual_cis_get_capability(isp_metadata_t *metadata)
{
	if (NULL == metadata)
		return -1;

	unsigned int i = 0;

	for (i = 0; i < array_count(imx286dual_capability); i++) {
		isp_metadata_set(metadata,
				 imx286dual_capability[i].tag,
				 imx286dual_capability[i].value,
				 imx286dual_capability[i].type_size,
				 imx286dual_capability[i].count);
	}

	return 0;
}
