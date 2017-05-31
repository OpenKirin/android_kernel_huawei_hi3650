

#include "../../metadata/isp_metadata_vendor_tag.h"
#include "../../metadata/camera_metadata_tags.h"
#include  "../../metadata/simulated_utils.h"
#ifndef NULL
#define NULL ((void *)0)
#endif

static unsigned int imx179_4l_position = 1;
static unsigned int imx179_4l_eq_focus = 26;
static unsigned char imx179_4l_lens_facing = ANDROID_LENS_FACING_FRONT;
static unsigned int imx179_4l_orientation = 270;
static unsigned int imx179_4l_jpeg_orientation = 270;
static float imx179_4l_aperture = 2.4;
static float imx179_4l_min_focus_distance = 10.0;
static float imx179_4l_focal_lengths = 3.38f;	/* < 3.38mm */

static unsigned char imx179_4l_flash_available;
/*< TBD, ANDROID_HW_TRUE, ANDROID_HW_FALSE */
static unsigned char imx179_4l_supported_front_mirror = 1;

static unsigned char imx179_4l_availableAfModeFront[] = {
	ANDROID_CONTROL_AF_MODE_AUTO,
	ANDROID_CONTROL_AF_MODE_MACRO,
	ANDROID_CONTROL_AF_MODE_CONTINUOUS_VIDEO,
	ANDROID_CONTROL_AF_MODE_CONTINUOUS_PICTURE
};

static int imx179_4l_availableProcessSize[] = {
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
	800, 480,

};

static int imx179_4l_availableJpegSize[] =	/*< TBD, maybe need modify */
{
	640, 480,
	2592, 1952,
	3264, 1840,
	3264, 2448,
	2448, 2448,
	320, 240,
	1280, 720,
	1920, 1080,
	1600, 1200,
	1536, 864,
	1200, 1200,
	/*
	   640, 368,
	   640, 480,
	   1280, 720,
	   1280, 800,
	   1280, 960,
	   2592, 1952,
	   2592, 1456,
	   3264, 1840,
	   3264, 2448,
	 */
};

static float imx179_4l_sensorPhysicalSize[] = {
	3.20f,			/*< 3.20mm */
	2.40f,			/*< 2.40mm */
};

static int imx179_4l_resolution[] =	/*< TBD, need renamed */
{
	3264, 2448
};

static int imx179_4l_availableRawSize[] = {
	3264, 2448
};

static unsigned char imx179_4l_supportedIsoValues[] = {
	0,			/* ANDROID_HW_ISO_AUTO */
	2,			/* ANDROID_HW_ISO_100 */
	3,			/* ANDROID_HW_ISO_200 */
	4,			/* ANDROID_HW_ISO_400 */
	5,			/* ANDROID_HW_ISO_800 */
	7			/* ANDROID_HW_ISO_1600 */
};

cis_capability imx179_4l_capability[] = {
	{(unsigned int)ANDROID_HUAWEI_DEVICE_SENSOR_POSITION,
	 &imx179_4l_position, sizeof(unsigned int),
	 sizeof(imx179_4l_position) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_LENS_APERTURE, &imx179_4l_aperture,
	 sizeof(float), sizeof(imx179_4l_aperture) / sizeof(float)},
	{(unsigned int)ANDROID_HW_EQUIVALENT_FOCUS, &imx179_4l_eq_focus,
	 sizeof(unsigned int),
	 sizeof(imx179_4l_eq_focus) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_LENS_FACING, &imx179_4l_lens_facing,
	 sizeof(unsigned char),
	 sizeof(imx179_4l_lens_facing) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_LENS_INFO_MINIMUM_FOCUS_DISTANCE,
	 &imx179_4l_min_focus_distance, sizeof(float),
	 sizeof(imx179_4l_min_focus_distance) / sizeof(float)},
	{(unsigned int)ANDROID_SENSOR_ORIENTATION, &imx179_4l_orientation,
	 sizeof(unsigned int),
	 sizeof(imx179_4l_orientation) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_JPEG_ORIENTATION, &imx179_4l_jpeg_orientation,
	 sizeof(unsigned int),
	 sizeof(imx179_4l_jpeg_orientation) / sizeof(unsigned int)},
	{(unsigned int)ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS,
	 &imx179_4l_focal_lengths, sizeof(float),
	 sizeof(imx179_4l_focal_lengths) / sizeof(float)},
	{(unsigned int)ANDROID_FLASH_INFO_AVAILABLE, &imx179_4l_flash_available,
	 sizeof(unsigned char),
	 sizeof(imx179_4l_flash_available) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_CONTROL_AF_AVAILABLE_MODES,
	 imx179_4l_availableAfModeFront, sizeof(unsigned char),
	 sizeof(imx179_4l_availableAfModeFront) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_PROCESSED_SIZES,
	 imx179_4l_availableProcessSize, sizeof(int),
	 sizeof(imx179_4l_availableProcessSize) / sizeof(int)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_JPEG_SIZES,
	 imx179_4l_availableJpegSize, sizeof(int),
	 sizeof(imx179_4l_availableJpegSize) / sizeof(int)},
	{(unsigned int)ANDROID_SENSOR_INFO_PHYSICAL_SIZE,
	 imx179_4l_sensorPhysicalSize, sizeof(float),
	 sizeof(imx179_4l_sensorPhysicalSize) / sizeof(float)},
	{(unsigned int)ANDROID_SCALER_AVAILABLE_RAW_SIZES,
	 imx179_4l_availableRawSize, sizeof(int),
	 sizeof(imx179_4l_availableRawSize) / sizeof(int)},
	{(unsigned int)ANDROID_HW_CAPTURE_MIRROR_SUPPORTED,
	 &imx179_4l_supported_front_mirror, sizeof(unsigned char),
	 sizeof(imx179_4l_supported_front_mirror) / sizeof(unsigned char)},
	{(unsigned int)ANDROID_HW_SUPPORTED_ISO_VALUES,
	 imx179_4l_supportedIsoValues, sizeof(unsigned char),
	 sizeof(imx179_4l_supportedIsoValues) / sizeof(unsigned char)}
};

int imx179_4l_cis_get_capability(isp_metadata_t *metadata)
{
	if (NULL == metadata)
		return -1;

	unsigned int i = 0;

	for (i = 0; i < array_count(imx179_4l_capability); i++) {
		isp_metadata_set(metadata,
				 imx179_4l_capability[i].tag,
				 imx179_4l_capability[i].value,
				 imx179_4l_capability[i].type_size,
				 imx179_4l_capability[i].count);
	}

	return 0;
}
