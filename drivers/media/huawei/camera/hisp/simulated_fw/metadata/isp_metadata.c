
/*lint -e732 -e774 -e785 -e845 -e715 -e818 -e705 -e717 -e734 -e835 -e713 -e838 -e826 -e737 -e701 -e801 -e778 -e785
-esym(732,*) -esym(774,*) -esym(785,*) -esym(845,*) -esym(715,*) -esym(818,*) -esym(705,*) -esym(717,*) -esym(734,*)
-esym(835,*) -esym(713,*) -esym(838,*) -esym(826,*) -esym(737,*) -esym(701,*)
-esym(801,*) -esym(778,*) -esym(785,*)*/
#define ISP_METADATA_LINUX

#define LOG_TAG "isp_metadata"

#ifdef ISP_METADATA_FIRMWARE

#define DEBUG_DEBUG 0
#include <string.h>
#include <stdio.h>
#include "utils/log.h"
#include "oslayer/oslayer.h"
#include "framework/error.h"
#include "utils/isp_metadata.h"
#include "utils/isp_metadata_vendor_tag.h"
//#include "algo/algo_metadata.h"

#elif defined ISP_METADATA_ANDROID

#include <log/log.h>
#include "isp_metadata.h"
#include "isp_metadata_vendor_tag.h"

#elif defined ISP_METADATA_LINUX

#include <linux/stddef.h>
#include <linux/slab.h>
#include "isp_metadata.h"
#include "isp_metadata_vendor_tag.h"
#include "camera_metadata_tags.h"

#endif

#define HEAD_FLAG 0x003EFEFE
#define TOTAL_ENTRY_SIZE 0x2000 /* 8k */
#define MIN_BUFFER_SIZE (sizeof(meta_head_t) + TOTAL_ENTRY_SIZE)

const char *camera_metadata_section_names[ANDROID_SECTION_COUNT] = {
    [ANDROID_COLOR_CORRECTION]     = "android.colorCorrection",
    [ANDROID_CONTROL]              = "android.control",
    [ANDROID_DEMOSAIC]             = "android.demosaic",
    [ANDROID_EDGE]                 = "android.edge",
    [ANDROID_FLASH]                = "android.flash",
    [ANDROID_FLASH_INFO]           = "android.flash.info",
    [ANDROID_HOT_PIXEL]            = "android.hotPixel",
    [ANDROID_JPEG]                 = "android.jpeg",
    [ANDROID_LENS]                 = "android.lens",
    [ANDROID_LENS_INFO]            = "android.lens.info",
    [ANDROID_NOISE_REDUCTION]      = "android.noiseReduction",
    [ANDROID_QUIRKS]               = "android.quirks",
    [ANDROID_REQUEST]              = "android.request",
    [ANDROID_SCALER]               = "android.scaler",
    [ANDROID_SENSOR]               = "android.sensor",
    [ANDROID_SENSOR_INFO]          = "android.sensor.info",
    [ANDROID_SHADING]              = "android.shading",
    [ANDROID_STATISTICS]           = "android.statistics",
    [ANDROID_STATISTICS_INFO]      = "android.statistics.info",
    [ANDROID_TONEMAP]              = "android.tonemap",
    [ANDROID_LED]                  = "android.led",
    [ANDROID_INFO]                 = "android.info",
    [ANDROID_BLACK_LEVEL]          = "android.blackLevel",
    [ANDROID_SYNC]                 = "android.sync",
    [ANDROID_REPROCESS]            = "android.reprocess",
    [ANDROID_DEPTH]                = "android.depth",
};

unsigned int camera_metadata_section_bounds[ANDROID_SECTION_COUNT][2] = {
    [ANDROID_COLOR_CORRECTION]     = { ANDROID_COLOR_CORRECTION_START,
                                       ANDROID_COLOR_CORRECTION_END },
    [ANDROID_CONTROL]              = { ANDROID_CONTROL_START,
                                       ANDROID_CONTROL_END },
    [ANDROID_DEMOSAIC]             = { ANDROID_DEMOSAIC_START,
                                       ANDROID_DEMOSAIC_END },
    [ANDROID_EDGE]                 = { ANDROID_EDGE_START,
                                       ANDROID_EDGE_END },
    [ANDROID_FLASH]                = { ANDROID_FLASH_START,
                                       ANDROID_FLASH_END },
    [ANDROID_FLASH_INFO]           = { ANDROID_FLASH_INFO_START,
                                       ANDROID_FLASH_INFO_END },
    [ANDROID_HOT_PIXEL]            = { ANDROID_HOT_PIXEL_START,
                                       ANDROID_HOT_PIXEL_END },
    [ANDROID_JPEG]                 = { ANDROID_JPEG_START,
                                       ANDROID_JPEG_END },
    [ANDROID_LENS]                 = { ANDROID_LENS_START,
                                       ANDROID_LENS_END },
    [ANDROID_LENS_INFO]            = { ANDROID_LENS_INFO_START,
                                       ANDROID_LENS_INFO_END },
    [ANDROID_NOISE_REDUCTION]      = { ANDROID_NOISE_REDUCTION_START,
                                       ANDROID_NOISE_REDUCTION_END },
    [ANDROID_QUIRKS]               = { ANDROID_QUIRKS_START,
                                       ANDROID_QUIRKS_END },
    [ANDROID_REQUEST]              = { ANDROID_REQUEST_START,
                                       ANDROID_REQUEST_END },
    [ANDROID_SCALER]               = { ANDROID_SCALER_START,
                                       ANDROID_SCALER_END },
    [ANDROID_SENSOR]               = { ANDROID_SENSOR_START,
                                       ANDROID_SENSOR_END },
    [ANDROID_SENSOR_INFO]          = { ANDROID_SENSOR_INFO_START,
                                       ANDROID_SENSOR_INFO_END },
    [ANDROID_SHADING]              = { ANDROID_SHADING_START,
                                       ANDROID_SHADING_END },
    [ANDROID_STATISTICS]           = { ANDROID_STATISTICS_START,
                                       ANDROID_STATISTICS_END },
    [ANDROID_STATISTICS_INFO]      = { ANDROID_STATISTICS_INFO_START,
                                       ANDROID_STATISTICS_INFO_END },
    [ANDROID_TONEMAP]              = { ANDROID_TONEMAP_START,
                                       ANDROID_TONEMAP_END },
    [ANDROID_LED]                  = { ANDROID_LED_START,
                                       ANDROID_LED_END },
    [ANDROID_INFO]                 = { ANDROID_INFO_START,
                                       ANDROID_INFO_END },
    [ANDROID_BLACK_LEVEL]          = { ANDROID_BLACK_LEVEL_START,
                                       ANDROID_BLACK_LEVEL_END },
    [ANDROID_SYNC]                 = { ANDROID_SYNC_START,
                                       ANDROID_SYNC_END },
    [ANDROID_REPROCESS]            = { ANDROID_REPROCESS_START,
                                       ANDROID_REPROCESS_END },
    [ANDROID_DEPTH]                = { ANDROID_DEPTH_START,
                                       ANDROID_DEPTH_END },
};

static tag_info_t android_color_correction[ANDROID_COLOR_CORRECTION_END -
        ANDROID_COLOR_CORRECTION_START] = {
    [ ANDROID_COLOR_CORRECTION_MODE - ANDROID_COLOR_CORRECTION_START ] =
    { "mode",                          DATA_BYTE,       1   },
    [ ANDROID_COLOR_CORRECTION_TRANSFORM - ANDROID_COLOR_CORRECTION_START ] =
    { "transform",                     DATA_RATIONAL,   3*3   },
    [ ANDROID_COLOR_CORRECTION_GAINS - ANDROID_COLOR_CORRECTION_START ] =
    { "gains",                         DATA_FLOAT,      4   },
    [ ANDROID_COLOR_CORRECTION_ABERRATION_MODE - ANDROID_COLOR_CORRECTION_START ] =
    { "aberrationMode",                DATA_BYTE,       1   },
    [ ANDROID_COLOR_CORRECTION_AVAILABLE_ABERRATION_MODES - ANDROID_COLOR_CORRECTION_START ] =
    { "availableAberrationModes",      DATA_BYTE,       4/* FIXME */   },
};

static tag_info_t android_control[ANDROID_CONTROL_END -
        ANDROID_CONTROL_START] = {
    [ ANDROID_CONTROL_AE_ANTIBANDING_MODE - ANDROID_CONTROL_START ] =
    { "aeAntibandingMode",             DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AE_EXPOSURE_COMPENSATION - ANDROID_CONTROL_START ] =
    { "aeExposureCompensation",        DATA_INT32,      1   },
    [ ANDROID_CONTROL_AE_LOCK - ANDROID_CONTROL_START ] =
    { "aeLock",                        DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AE_MODE - ANDROID_CONTROL_START ] =
    { "aeMode",                        DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AE_REGIONS - ANDROID_CONTROL_START ] =
    { "aeRegions",                     DATA_INT32,      5*4 },
    [ ANDROID_CONTROL_AE_TARGET_FPS_RANGE - ANDROID_CONTROL_START ] =
    { "aeTargetFpsRange",              DATA_INT32,      2   },
    [ ANDROID_CONTROL_AE_PRECAPTURE_TRIGGER - ANDROID_CONTROL_START ] =
    { "aePrecaptureTrigger",           DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AF_MODE - ANDROID_CONTROL_START ] =
    { "afMode",                        DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AF_REGIONS - ANDROID_CONTROL_START ] =
    { "afRegions",                     DATA_INT32,      5*4 },
    [ ANDROID_CONTROL_AF_TRIGGER - ANDROID_CONTROL_START ] =
    { "afTrigger",                     DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AWB_LOCK - ANDROID_CONTROL_START ] =
    { "awbLock",                       DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AWB_MODE - ANDROID_CONTROL_START ] =
    { "awbMode",                       DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AWB_REGIONS - ANDROID_CONTROL_START ] =
    { "awbRegions",                    DATA_INT32,      5*4 },
    [ ANDROID_CONTROL_CAPTURE_INTENT - ANDROID_CONTROL_START ] =
    { "captureIntent",                 DATA_BYTE,       1   },
    [ ANDROID_CONTROL_EFFECT_MODE - ANDROID_CONTROL_START ] =
    { "effectMode",                    DATA_BYTE,       1   },
    [ ANDROID_CONTROL_MODE - ANDROID_CONTROL_START ] =
    { "mode",                          DATA_BYTE,       1   },
    [ ANDROID_CONTROL_SCENE_MODE - ANDROID_CONTROL_START ] =
    { "sceneMode",                     DATA_BYTE,       1   },
    [ ANDROID_CONTROL_VIDEO_STABILIZATION_MODE - ANDROID_CONTROL_START ] =
    { "videoStabilizationMode",        DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AE_AVAILABLE_ANTIBANDING_MODES - ANDROID_CONTROL_START ] =
    { "aeAvailableAntibandingModes",   DATA_BYTE,       5   },
    [ ANDROID_CONTROL_AE_AVAILABLE_MODES - ANDROID_CONTROL_START ] =
    { "aeAvailableModes",              DATA_BYTE,       5   },
    [ ANDROID_CONTROL_AE_AVAILABLE_TARGET_FPS_RANGES - ANDROID_CONTROL_START ] =
    { "aeAvailableTargetFpsRanges",    DATA_INT32,      2*3 },
    [ ANDROID_CONTROL_AE_COMPENSATION_RANGE - ANDROID_CONTROL_START ] =
    { "aeCompensationRange",           DATA_INT32,      2 },
    [ ANDROID_CONTROL_AE_COMPENSATION_STEP - ANDROID_CONTROL_START ] =
    { "aeCompensationStep",            DATA_RATIONAL,   1   },
    [ ANDROID_CONTROL_AF_AVAILABLE_MODES - ANDROID_CONTROL_START ] =
    { "afAvailableModes",              DATA_BYTE,       5  },
    [ ANDROID_CONTROL_AVAILABLE_EFFECTS - ANDROID_CONTROL_START ] =
    { "availableEffects",              DATA_BYTE,       9   },
    [ ANDROID_CONTROL_AVAILABLE_SCENE_MODES - ANDROID_CONTROL_START ] =
    { "availableSceneModes",           DATA_BYTE,       19  },
    [ ANDROID_CONTROL_AVAILABLE_VIDEO_STABILIZATION_MODES - ANDROID_CONTROL_START ] =
    { "availableVideoStabilizationModes",
                                        DATA_BYTE,      2   },
    [ ANDROID_CONTROL_AWB_AVAILABLE_MODES - ANDROID_CONTROL_START ] =
    { "awbAvailableModes",             DATA_BYTE,       9   },
    [ ANDROID_CONTROL_MAX_REGIONS - ANDROID_CONTROL_START ] =
    { "maxRegions",                    DATA_INT32,      3   },
    [ ANDROID_CONTROL_SCENE_MODE_OVERRIDES - ANDROID_CONTROL_START ] =
    { "sceneModeOverrides",            DATA_BYTE,       3*19   },
    [ ANDROID_CONTROL_AE_PRECAPTURE_ID - ANDROID_CONTROL_START ] =
    { "aePrecaptureId",                DATA_INT32,      1   },
    [ ANDROID_CONTROL_AE_STATE - ANDROID_CONTROL_START ] =
    { "aeState",                       DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AF_STATE - ANDROID_CONTROL_START ] =
    { "afState",                       DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AF_TRIGGER_ID - ANDROID_CONTROL_START ] =
    { "afTriggerId",                   DATA_INT32,      1   },
    [ ANDROID_CONTROL_AWB_STATE - ANDROID_CONTROL_START ] =
    { "awbState",                      DATA_BYTE,       1   },
    [ ANDROID_CONTROL_AVAILABLE_HIGH_SPEED_VIDEO_CONFIGURATIONS - ANDROID_CONTROL_START ] =
    { "availableHighSpeedVideoConfigurations",
                                        DATA_INT32,     4   },
};

static tag_info_t android_demosaic[ANDROID_DEMOSAIC_END -
        ANDROID_DEMOSAIC_START] = {
    [ ANDROID_DEMOSAIC_MODE - ANDROID_DEMOSAIC_START ] =
    { "mode",                          DATA_BYTE,       1   },
};

static tag_info_t android_edge[ANDROID_EDGE_END -
        ANDROID_EDGE_START] = {
    [ ANDROID_EDGE_MODE - ANDROID_EDGE_START ] =
    { "mode",                          DATA_BYTE,       1   },
    [ ANDROID_EDGE_STRENGTH - ANDROID_EDGE_START ] =
    { "strength",                      DATA_BYTE,       1   },
    [ ANDROID_EDGE_AVAILABLE_EDGE_MODES - ANDROID_EDGE_START ] =
    { "availableEdgeModes",            DATA_BYTE,       3   },
};

static tag_info_t android_flash[ANDROID_FLASH_END -
        ANDROID_FLASH_START] = {
    [ ANDROID_FLASH_FIRING_POWER - ANDROID_FLASH_START ] =
    { "firingPower",                   DATA_BYTE,       1   },
    [ ANDROID_FLASH_FIRING_TIME - ANDROID_FLASH_START ] =
    { "firingTime",                    DATA_INT64,      1  },
    [ ANDROID_FLASH_MODE - ANDROID_FLASH_START ] =
    { "mode",                          DATA_BYTE,       1   },
    [ ANDROID_FLASH_COLOR_TEMPERATURE - ANDROID_FLASH_START ] =
    { "colorTemperature",              DATA_BYTE,       1   },
    [ ANDROID_FLASH_MAX_ENERGY - ANDROID_FLASH_START ] =
    { "maxEnergy",                     DATA_BYTE,       1   },
    [ ANDROID_FLASH_STATE - ANDROID_FLASH_START ] =
    { "state",                         DATA_BYTE,       1   },
};

static tag_info_t android_flash_info[ANDROID_FLASH_INFO_END -
        ANDROID_FLASH_INFO_START] = {
    [ ANDROID_FLASH_INFO_AVAILABLE - ANDROID_FLASH_INFO_START ] =
    { "available",                     DATA_BYTE,       1   },
    [ ANDROID_FLASH_INFO_CHARGE_DURATION - ANDROID_FLASH_INFO_START ] =
    { "chargeDuration",                DATA_INT64,      1   },
};

static tag_info_t android_hot_pixel[ANDROID_HOT_PIXEL_END -
        ANDROID_HOT_PIXEL_START] = {
    [ ANDROID_HOT_PIXEL_MODE - ANDROID_HOT_PIXEL_START ] =
    { "mode",                          DATA_BYTE,       1   },
    [ ANDROID_HOT_PIXEL_AVAILABLE_HOT_PIXEL_MODES - ANDROID_HOT_PIXEL_START ] =
    { "availableHotPixelModes",        DATA_BYTE,       3   },
};

static tag_info_t android_jpeg[ANDROID_JPEG_END -
        ANDROID_JPEG_START] = {
    [ ANDROID_JPEG_GPS_COORDINATES - ANDROID_JPEG_START ] =
    { "gpsCoordinates",                DATA_DOUBLE,     3   },
    [ ANDROID_JPEG_GPS_PROCESSING_METHOD - ANDROID_JPEG_START ] =
    { "gpsProcessingMethod",           DATA_BYTE,       3   },
    [ ANDROID_JPEG_GPS_TIMESTAMP - ANDROID_JPEG_START ] =
    { "gpsTimestamp",                  DATA_INT64,      1   },
    [ ANDROID_JPEG_ORIENTATION - ANDROID_JPEG_START ] =
    { "orientation",                   DATA_INT32,      1   },
    [ ANDROID_JPEG_QUALITY - ANDROID_JPEG_START ] =
    { "quality",                       DATA_BYTE,       1   },
    [ ANDROID_JPEG_THUMBNAIL_QUALITY - ANDROID_JPEG_START ] =
    { "thumbnailQuality",              DATA_BYTE,       1   },
    [ ANDROID_JPEG_THUMBNAIL_SIZE - ANDROID_JPEG_START ] =
    { "thumbnailSize",                 DATA_INT32,      2   },
    [ ANDROID_JPEG_AVAILABLE_THUMBNAIL_SIZES - ANDROID_JPEG_START ] =
    { "availableThumbnailSizes",       DATA_INT32,      2   },
    [ ANDROID_JPEG_MAX_SIZE - ANDROID_JPEG_START ] =
    { "maxSize",                       DATA_INT32,      1   },
    [ ANDROID_JPEG_SIZE - ANDROID_JPEG_START ] =
    { "size",                          DATA_INT32,      1   },
};

static tag_info_t android_lens[ANDROID_LENS_END -
        ANDROID_LENS_START] = {
    [ ANDROID_LENS_APERTURE - ANDROID_LENS_START ] =
    { "aperture",                      DATA_FLOAT,      1   },
    [ ANDROID_LENS_FILTER_DENSITY - ANDROID_LENS_START ] =
    { "filterDensity",                 DATA_FLOAT,      1   },
    [ ANDROID_LENS_FOCAL_LENGTH - ANDROID_LENS_START ] =
    { "focalLength",                   DATA_FLOAT,      1   },
    [ ANDROID_LENS_FOCUS_DISTANCE - ANDROID_LENS_START ] =
    { "focusDistance",                 DATA_FLOAT,      1   },
    [ ANDROID_LENS_OPTICAL_STABILIZATION_MODE - ANDROID_LENS_START ] =
    { "opticalStabilizationMode",      DATA_BYTE,       1   },
    [ ANDROID_LENS_FACING - ANDROID_LENS_START ] =
    { "facing",                        DATA_BYTE,       1   },
    [ ANDROID_LENS_OPTICAL_AXIS_ANGLE - ANDROID_LENS_START ] =
    { "opticalAxisAngle",              DATA_FLOAT,      2   },
    [ ANDROID_LENS_POSITION - ANDROID_LENS_START ] =
    { "position",                      DATA_FLOAT,      3   },
    [ ANDROID_LENS_FOCUS_RANGE - ANDROID_LENS_START ] =
    { "focusRange",                    DATA_FLOAT,      2   },
    [ ANDROID_LENS_STATE - ANDROID_LENS_START ] =
    { "state",                         DATA_BYTE,       1   },
};

static tag_info_t android_lens_info[ANDROID_LENS_INFO_END -
        ANDROID_LENS_INFO_START] = {
    [ ANDROID_LENS_INFO_AVAILABLE_APERTURES - ANDROID_LENS_INFO_START ] =
    { "availableApertures",            DATA_FLOAT,      1   },
    [ ANDROID_LENS_INFO_AVAILABLE_FILTER_DENSITIES - ANDROID_LENS_INFO_START ] =
    { "availableFilterDensities",      DATA_FLOAT,      1   },
    [ ANDROID_LENS_INFO_AVAILABLE_FOCAL_LENGTHS - ANDROID_LENS_INFO_START ] =
    { "availableFocalLengths",         DATA_FLOAT,      1   },
    [ ANDROID_LENS_INFO_AVAILABLE_OPTICAL_STABILIZATION - ANDROID_LENS_INFO_START ] =
    { "availableOpticalStabilization", DATA_BYTE,       2   },
    [ ANDROID_LENS_INFO_HYPERFOCAL_DISTANCE - ANDROID_LENS_INFO_START ] =
    { "hyperfocalDistance",            DATA_FLOAT,      1   },
    [ ANDROID_LENS_INFO_MINIMUM_FOCUS_DISTANCE - ANDROID_LENS_INFO_START ] =
    { "minimumFocusDistance",          DATA_FLOAT,      1   },
    [ ANDROID_LENS_INFO_SHADING_MAP_SIZE - ANDROID_LENS_INFO_START ] =
    { "shadingMapSize",                DATA_INT32,      2   },
    [ ANDROID_LENS_INFO_FOCUS_DISTANCE_CALIBRATION - ANDROID_LENS_INFO_START ] =
    { "focusDistanceCalibration",      DATA_BYTE,       1   },
};

static tag_info_t android_noise_reduction[ANDROID_NOISE_REDUCTION_END -
        ANDROID_NOISE_REDUCTION_START] = {
    [ ANDROID_NOISE_REDUCTION_MODE - ANDROID_NOISE_REDUCTION_START ] =
    { "mode",                          DATA_BYTE,       1   },
    [ ANDROID_NOISE_REDUCTION_STRENGTH - ANDROID_NOISE_REDUCTION_START ] =
    { "strength",                      DATA_BYTE,       1   },
    [ ANDROID_NOISE_REDUCTION_AVAILABLE_NOISE_REDUCTION_MODES - ANDROID_NOISE_REDUCTION_START ] =
    { "availableNoiseReductionModes",  DATA_BYTE,       3   },
};

static tag_info_t android_quirks[ANDROID_QUIRKS_END -
        ANDROID_QUIRKS_START] = {
    [ ANDROID_QUIRKS_METERING_CROP_REGION - ANDROID_QUIRKS_START ] =
    { "meteringCropRegion",            DATA_BYTE,       1   },
    [ ANDROID_QUIRKS_TRIGGER_AF_WITH_AUTO - ANDROID_QUIRKS_START ] =
    { "triggerAfWithAuto",             DATA_BYTE,       1   },
    [ ANDROID_QUIRKS_USE_ZSL_FORMAT - ANDROID_QUIRKS_START ] =
    { "useZslFormat",                  DATA_BYTE,       1   },
    [ ANDROID_QUIRKS_USE_PARTIAL_RESULT - ANDROID_QUIRKS_START ] =
    { "usePartialResult",              DATA_BYTE,       1   },
    [ ANDROID_QUIRKS_PARTIAL_RESULT - ANDROID_QUIRKS_START ] =
    { "partialResult",                 DATA_BYTE,       1   },
};

static tag_info_t android_request[ANDROID_REQUEST_END -
        ANDROID_REQUEST_START] = {
    [ ANDROID_REQUEST_FRAME_COUNT - ANDROID_REQUEST_START ] =
    { "frameCount",                    DATA_INT32,      1   },
    [ ANDROID_REQUEST_ID - ANDROID_REQUEST_START ] =
    { "id",                            DATA_INT32,      1   },
    [ ANDROID_REQUEST_INPUT_STREAMS - ANDROID_REQUEST_START ] =
    { "inputStreams",                  DATA_INT32,      1   },
    [ ANDROID_REQUEST_METADATA_MODE - ANDROID_REQUEST_START ] =
    { "metadataMode",                  DATA_BYTE,       1   },
    [ ANDROID_REQUEST_OUTPUT_STREAMS - ANDROID_REQUEST_START ] =
    { "outputStreams",                 DATA_INT32,      1   },
    [ ANDROID_REQUEST_TYPE - ANDROID_REQUEST_START ] =
    { "type",                          DATA_BYTE,       1   },
    [ ANDROID_REQUEST_MAX_NUM_OUTPUT_STREAMS - ANDROID_REQUEST_START ] =
    { "maxNumOutputStreams",           DATA_INT32,      3   },
    [ ANDROID_REQUEST_MAX_NUM_REPROCESS_STREAMS - ANDROID_REQUEST_START ] =
    { "maxNumReprocessStreams",        DATA_INT32,      1   },
    [ ANDROID_REQUEST_MAX_NUM_INPUT_STREAMS - ANDROID_REQUEST_START ] =
    { "maxNumInputStreams",            DATA_INT32,      1   },
    [ ANDROID_REQUEST_PIPELINE_DEPTH - ANDROID_REQUEST_START ] =
    { "pipelineDepth",                 DATA_BYTE,       1   },
    [ ANDROID_REQUEST_PIPELINE_MAX_DEPTH - ANDROID_REQUEST_START ] =
    { "pipelineMaxDepth",              DATA_BYTE,       1   },
    [ ANDROID_REQUEST_PARTIAL_RESULT_COUNT - ANDROID_REQUEST_START ] =
    { "partialResultCount",            DATA_INT32,      1   },
    [ ANDROID_REQUEST_AVAILABLE_CAPABILITIES - ANDROID_REQUEST_START ] =
    { "availableCapabilities",         DATA_BYTE,       5   },
    [ ANDROID_REQUEST_AVAILABLE_REQUEST_KEYS - ANDROID_REQUEST_START ] =
    { "availableRequestKeys",          DATA_INT32,      1/*n*/   },
    [ ANDROID_REQUEST_AVAILABLE_RESULT_KEYS - ANDROID_REQUEST_START ] =
    { "availableResultKeys",           DATA_INT32,      1/*n*/   },
    [ ANDROID_REQUEST_AVAILABLE_CHARACTERISTICS_KEYS - ANDROID_REQUEST_START ] =
    { "availableCharacteristicsKeys",  DATA_INT32,      1/*n*/  },
};

static tag_info_t android_scaler[ANDROID_SCALER_END -
        ANDROID_SCALER_START] = {
    [ ANDROID_SCALER_CROP_REGION - ANDROID_SCALER_START ] =
    { "cropRegion",                    DATA_INT32,      4   },
    [ ANDROID_SCALER_AVAILABLE_FORMATS - ANDROID_SCALER_START ] =
    { "availableFormats",              DATA_INT32,      1   },
    [ ANDROID_SCALER_AVAILABLE_JPEG_MIN_DURATIONS - ANDROID_SCALER_START ] =
    { "availableJpegMinDurations",     DATA_INT64,      1   },
    [ ANDROID_SCALER_AVAILABLE_JPEG_SIZES - ANDROID_SCALER_START ] =
    { "availableJpegSizes",            DATA_INT32,      24   },
    [ ANDROID_SCALER_AVAILABLE_MAX_DIGITAL_ZOOM - ANDROID_SCALER_START ] =
    { "availableMaxDigitalZoom",       DATA_FLOAT,      1   },
    [ ANDROID_SCALER_AVAILABLE_PROCESSED_MIN_DURATIONS - ANDROID_SCALER_START ] =
    { "availableProcessedMinDurations",
                                        DATA_INT64,     1   },
    [ ANDROID_SCALER_AVAILABLE_PROCESSED_SIZES - ANDROID_SCALER_START ] =
    { "availableProcessedSizes",       DATA_INT32,      32   },
    [ ANDROID_SCALER_AVAILABLE_RAW_MIN_DURATIONS - ANDROID_SCALER_START ] =
    { "availableRawMinDurations",      DATA_INT64,      1   },
    [ ANDROID_SCALER_AVAILABLE_RAW_SIZES - ANDROID_SCALER_START ] =
    { "availableRawSizes",             DATA_INT32,      2   },
    [ ANDROID_SCALER_AVAILABLE_INPUT_OUTPUT_FORMATS_MAP - ANDROID_SCALER_START ] =
    { "availableInputOutputFormatsMap",
                                        DATA_INT32,     7   },
    [ ANDROID_SCALER_AVAILABLE_STREAM_CONFIGURATIONS - ANDROID_SCALER_START ] =
    { "availableStreamConfigurations", DATA_INT32,      4   },
    [ ANDROID_SCALER_AVAILABLE_MIN_FRAME_DURATIONS - ANDROID_SCALER_START ] =
    { "availableMinFrameDurations",    DATA_INT64,      4   },
    [ ANDROID_SCALER_AVAILABLE_STALL_DURATIONS - ANDROID_SCALER_START ] =
    { "availableStallDurations",       DATA_INT64,      4   },
    [ ANDROID_SCALER_CROPPING_TYPE - ANDROID_SCALER_START ] =
    { "croppingType",                  DATA_BYTE,       1   },
};

static tag_info_t android_sensor[ANDROID_SENSOR_END -
        ANDROID_SENSOR_START] = {
    [ ANDROID_SENSOR_EXPOSURE_TIME - ANDROID_SENSOR_START ] =
    { "exposureTime",                  DATA_INT64,      1   },
    [ ANDROID_SENSOR_FRAME_DURATION - ANDROID_SENSOR_START ] =
    { "frameDuration",                 DATA_INT64,      1   },
    [ ANDROID_SENSOR_SENSITIVITY - ANDROID_SENSOR_START ] =
    { "sensitivity",                   DATA_INT32,      1   },
    [ ANDROID_SENSOR_REFERENCE_ILLUMINANT1 - ANDROID_SENSOR_START ] =
    { "referenceIlluminant1",          DATA_BYTE,       1   },
    [ ANDROID_SENSOR_REFERENCE_ILLUMINANT2 - ANDROID_SENSOR_START ] =
    { "referenceIlluminant2",          DATA_BYTE,       1   },
    [ ANDROID_SENSOR_CALIBRATION_TRANSFORM1 - ANDROID_SENSOR_START ] =
    { "calibrationTransform1",         DATA_RATIONAL,   3*3 },
    [ ANDROID_SENSOR_CALIBRATION_TRANSFORM2 - ANDROID_SENSOR_START ] =
    { "calibrationTransform2",         DATA_RATIONAL,   3*3 },
    [ ANDROID_SENSOR_COLOR_TRANSFORM1 - ANDROID_SENSOR_START ] =
    { "colorTransform1",               DATA_RATIONAL,   3*3 },
    [ ANDROID_SENSOR_COLOR_TRANSFORM2 - ANDROID_SENSOR_START ] =
    { "colorTransform2",               DATA_RATIONAL,   3*3 },
    [ ANDROID_SENSOR_FORWARD_MATRIX1 - ANDROID_SENSOR_START ] =
    { "forwardMatrix1",                DATA_RATIONAL,   3*3 },
    [ ANDROID_SENSOR_FORWARD_MATRIX2 - ANDROID_SENSOR_START ] =
    { "forwardMatrix2",                DATA_RATIONAL,   3*3 },
    [ ANDROID_SENSOR_BASE_GAIN_FACTOR - ANDROID_SENSOR_START ] =
    { "baseGainFactor",                DATA_RATIONAL,   1   },
    [ ANDROID_SENSOR_BLACK_LEVEL_PATTERN - ANDROID_SENSOR_START ] =
    { "blackLevelPattern",             DATA_INT32,      4   },
    [ ANDROID_SENSOR_MAX_ANALOG_SENSITIVITY - ANDROID_SENSOR_START ] =
    { "maxAnalogSensitivity",          DATA_INT32,      1   },
    [ ANDROID_SENSOR_ORIENTATION - ANDROID_SENSOR_START ] =
    { "orientation",                   DATA_INT32,      1   },
    [ ANDROID_SENSOR_PROFILE_HUE_SAT_MAP_DIMENSIONS - ANDROID_SENSOR_START ] =
    { "profileHueSatMapDimensions",    DATA_INT32,      3   },
    [ ANDROID_SENSOR_TIMESTAMP - ANDROID_SENSOR_START ] =
    { "timestamp",                     DATA_INT64,      1   },
    [ ANDROID_SENSOR_TEMPERATURE - ANDROID_SENSOR_START ] =
    { "temperature",                   DATA_FLOAT,      1   },
    [ ANDROID_SENSOR_NEUTRAL_COLOR_POINT - ANDROID_SENSOR_START ] =
    { "neutralColorPoint",             DATA_RATIONAL,   3   },
    [ ANDROID_SENSOR_NOISE_PROFILE - ANDROID_SENSOR_START ] =
    { "noiseProfile",                  DATA_DOUBLE,     8   },
    [ ANDROID_SENSOR_PROFILE_HUE_SAT_MAP - ANDROID_SENSOR_START ] =
    { "profileHueSatMap",              DATA_FLOAT,      3   },
    [ ANDROID_SENSOR_PROFILE_TONE_CURVE - ANDROID_SENSOR_START ] =
    { "profileToneCurve",              DATA_FLOAT,      2   },
    [ ANDROID_SENSOR_GREEN_SPLIT - ANDROID_SENSOR_START ] =
    { "greenSplit",                    DATA_FLOAT,      1   },
    [ ANDROID_SENSOR_TEST_PATTERN_DATA - ANDROID_SENSOR_START ] =
    { "testPatternData",               DATA_INT32,      4   },
    [ ANDROID_SENSOR_TEST_PATTERN_MODE - ANDROID_SENSOR_START ] =
    { "testPatternMode",               DATA_INT32,      1   },
    [ ANDROID_SENSOR_AVAILABLE_TEST_PATTERN_MODES - ANDROID_SENSOR_START ] =
    { "availableTestPatternModes",     DATA_INT32,      6   },
    [ ANDROID_SENSOR_ROLLING_SHUTTER_SKEW - ANDROID_SENSOR_START ] =
    { "rollingShutterSkew",            DATA_INT64,      1   },
};

static tag_info_t android_sensor_info[ANDROID_SENSOR_INFO_END -
        ANDROID_SENSOR_INFO_START] = {
    [ ANDROID_SENSOR_INFO_ACTIVE_ARRAY_SIZE - ANDROID_SENSOR_INFO_START ] =
    { "activeArraySize",               DATA_INT32,      2   },
    [ ANDROID_SENSOR_INFO_SENSITIVITY_RANGE - ANDROID_SENSOR_INFO_START ] =
    { "sensitivityRange",              DATA_INT32,      2   },
    [ ANDROID_SENSOR_INFO_COLOR_FILTER_ARRANGEMENT - ANDROID_SENSOR_INFO_START ] =
    { "colorFilterArrangement",        DATA_BYTE,       1   },
    [ ANDROID_SENSOR_INFO_EXPOSURE_TIME_RANGE - ANDROID_SENSOR_INFO_START ] =
    { "exposureTimeRange",             DATA_INT64,      2   },
    [ ANDROID_SENSOR_INFO_MAX_FRAME_DURATION - ANDROID_SENSOR_INFO_START ] =
    { "maxFrameDuration",              DATA_INT64,      1   },
    [ ANDROID_SENSOR_INFO_PHYSICAL_SIZE - ANDROID_SENSOR_INFO_START ] =
    { "physicalSize",                  DATA_FLOAT,      2   },
    [ ANDROID_SENSOR_INFO_PIXEL_ARRAY_SIZE - ANDROID_SENSOR_INFO_START ] =
    { "pixelArraySize",                DATA_INT32,      2   },
    [ ANDROID_SENSOR_INFO_WHITE_LEVEL - ANDROID_SENSOR_INFO_START ] =
    { "whiteLevel",                    DATA_INT32,      1   },
    [ ANDROID_SENSOR_INFO_TIMESTAMP_SOURCE - ANDROID_SENSOR_INFO_START ] =
    { "timestampSource",               DATA_BYTE,       1   },
};

static tag_info_t android_shading[ANDROID_SHADING_END -
        ANDROID_SHADING_START] = {
    [ ANDROID_SHADING_MODE - ANDROID_SHADING_START ] =
    { "mode",                          DATA_BYTE,       1   },
    [ ANDROID_SHADING_STRENGTH - ANDROID_SHADING_START ] =
    { "strength",                      DATA_BYTE,       1   },
};

static tag_info_t android_statistics[ANDROID_STATISTICS_END -
        ANDROID_STATISTICS_START] = {
    [ ANDROID_STATISTICS_FACE_DETECT_MODE - ANDROID_STATISTICS_START ] =
    { "faceDetectMode",                DATA_BYTE,       1   },
    [ ANDROID_STATISTICS_HISTOGRAM_MODE - ANDROID_STATISTICS_START ] =
    { "histogramMode",                 DATA_BYTE,       1   },
    [ ANDROID_STATISTICS_SHARPNESS_MAP_MODE - ANDROID_STATISTICS_START ] =
    { "sharpnessMapMode",              DATA_BYTE,       1   },
    [ ANDROID_STATISTICS_HOT_PIXEL_MAP_MODE - ANDROID_STATISTICS_START ] =
    { "hotPixelMapMode",               DATA_BYTE,       1   },
    [ ANDROID_STATISTICS_FACE_IDS - ANDROID_STATISTICS_START ] =
    { "faceIds",                       DATA_INT32,      35  },
    [ ANDROID_STATISTICS_FACE_LANDMARKS - ANDROID_STATISTICS_START ] =
    { "faceLandmarks",                 DATA_INT32,      35*6   },
    [ ANDROID_STATISTICS_FACE_RECTANGLES - ANDROID_STATISTICS_START ] =
    { "faceRectangles",                DATA_INT32,      35*4   },
    [ ANDROID_STATISTICS_FACE_SCORES - ANDROID_STATISTICS_START ] =
    { "faceScores",                    DATA_BYTE,       35   },
    [ ANDROID_STATISTICS_HISTOGRAM - ANDROID_STATISTICS_START ] =
    { "histogram",                     DATA_INT32,      256  },
    [ ANDROID_STATISTICS_SHARPNESS_MAP - ANDROID_STATISTICS_START ] =
    { "sharpnessMap",                  DATA_INT32,      32*32*3  },
    [ ANDROID_STATISTICS_LENS_SHADING_CORRECTION_MAP - ANDROID_STATISTICS_START ] =
    { "lensShadingCorrectionMap",      DATA_BYTE,       4*32*32  },
    [ ANDROID_STATISTICS_LENS_SHADING_MAP - ANDROID_STATISTICS_START ] =
    { "lensShadingMap",                DATA_FLOAT,      4*32*32  },
    [ ANDROID_STATISTICS_PREDICTED_COLOR_GAINS - ANDROID_STATISTICS_START ] =
    { "predictedColorGains",           DATA_FLOAT,      4  },
    [ ANDROID_STATISTICS_PREDICTED_COLOR_TRANSFORM - ANDROID_STATISTICS_START ] =
    { "predictedColorTransform",       DATA_RATIONAL,   3*3},
    [ ANDROID_STATISTICS_SCENE_FLICKER - ANDROID_STATISTICS_START ] =
    { "sceneFlicker",                  DATA_BYTE,       1   },
    [ ANDROID_STATISTICS_HOT_PIXEL_MAP - ANDROID_STATISTICS_START ] =
    { "hotPixelMap",                   DATA_INT32,      2   },
    [ ANDROID_STATISTICS_LENS_SHADING_MAP_MODE - ANDROID_STATISTICS_START ] =
    { "lensShadingMapMode",            DATA_BYTE,       1   },
};

static tag_info_t android_statistics_info[ANDROID_STATISTICS_INFO_END -
        ANDROID_STATISTICS_INFO_START] = {
    [ ANDROID_STATISTICS_INFO_AVAILABLE_FACE_DETECT_MODES - ANDROID_STATISTICS_INFO_START ] =
    { "availableFaceDetectModes",      DATA_BYTE,       3   },
    [ ANDROID_STATISTICS_INFO_HISTOGRAM_BUCKET_COUNT - ANDROID_STATISTICS_INFO_START ] =
    { "histogramBucketCount",          DATA_INT32,      1   },
    [ ANDROID_STATISTICS_INFO_MAX_FACE_COUNT - ANDROID_STATISTICS_INFO_START ] =
    { "maxFaceCount",                  DATA_INT32,      1   },
    [ ANDROID_STATISTICS_INFO_MAX_HISTOGRAM_COUNT - ANDROID_STATISTICS_INFO_START ] =
    { "maxHistogramCount",             DATA_INT32,      1   },
    [ ANDROID_STATISTICS_INFO_MAX_SHARPNESS_MAP_VALUE - ANDROID_STATISTICS_INFO_START ] =
    { "maxSharpnessMapValue",          DATA_INT32,      1   },
    [ ANDROID_STATISTICS_INFO_SHARPNESS_MAP_SIZE - ANDROID_STATISTICS_INFO_START ] =
    { "sharpnessMapSize",              DATA_INT32,      2   },
    [ ANDROID_STATISTICS_INFO_AVAILABLE_HOT_PIXEL_MAP_MODES - ANDROID_STATISTICS_INFO_START ] =
    { "availableHotPixelMapModes",     DATA_BYTE,       2   },
};

static tag_info_t android_tonemap[ANDROID_TONEMAP_END -
        ANDROID_TONEMAP_START] = {
    [ ANDROID_TONEMAP_CURVE_BLUE - ANDROID_TONEMAP_START ] =
    { "curveBlue",                     DATA_FLOAT,      514   },
    [ ANDROID_TONEMAP_CURVE_GREEN - ANDROID_TONEMAP_START ] =
    { "curveGreen",                    DATA_FLOAT,      514  },
    [ ANDROID_TONEMAP_CURVE_RED - ANDROID_TONEMAP_START ] =
    { "curveRed",                      DATA_FLOAT,      514  },
    [ ANDROID_TONEMAP_MODE - ANDROID_TONEMAP_START ] =
    { "mode",                          DATA_BYTE,       1   },
    [ ANDROID_TONEMAP_MAX_CURVE_POINTS - ANDROID_TONEMAP_START ] =
    { "maxCurvePoints",                DATA_INT32,      1   },
    [ ANDROID_TONEMAP_AVAILABLE_TONE_MAP_MODES - ANDROID_TONEMAP_START ] =
    { "availableToneMapModes",         DATA_BYTE,       3   },
};

static tag_info_t android_led[ANDROID_LED_END -
        ANDROID_LED_START] = {
    [ ANDROID_LED_TRANSMIT - ANDROID_LED_START ] =
    { "transmit",                      DATA_BYTE,       1   },
    [ ANDROID_LED_AVAILABLE_LEDS - ANDROID_LED_START ] =
    { "availableLeds",                 DATA_BYTE,       2   },
};

static tag_info_t android_info[ANDROID_INFO_END -
        ANDROID_INFO_START] = {
    [ ANDROID_INFO_SUPPORTED_HARDWARE_LEVEL - ANDROID_INFO_START ] =
    { "supportedHardwareLevel",        DATA_BYTE,       1   },
};

static tag_info_t android_black_level[ANDROID_BLACK_LEVEL_END -
        ANDROID_BLACK_LEVEL_START] = {
    [ ANDROID_BLACK_LEVEL_LOCK - ANDROID_BLACK_LEVEL_START ] =
    { "lock",                          DATA_BYTE,       1   },
};

static tag_info_t android_sync[ANDROID_SYNC_END -
        ANDROID_SYNC_START] = {
    [ ANDROID_SYNC_FRAME_NUMBER - ANDROID_SYNC_START ] =
    { "frameNumber",                   DATA_INT64,      1   },
    [ ANDROID_SYNC_MAX_LATENCY - ANDROID_SYNC_START ] =
    { "maxLatency",                    DATA_INT32,      1   },
};


static tag_info_t android_reprocess[ANDROID_REPROCESS_END -
        ANDROID_REPROCESS_START] = {
    [ ANDROID_REPROCESS_EFFECTIVE_EXPOSURE_FACTOR - ANDROID_REPROCESS_START  ] =
    { "effectiveExposureFactor",       DATA_FLOAT,    1   },
    [ ANDROID_REPROCESS_MAX_CAPTURE_STALL - ANDROID_REPROCESS_START  ] =
    { "maxCaptureStall",               DATA_INT32,    1   },
};

static tag_info_t android_depth[ANDROID_DEPTH_END -
        ANDROID_DEPTH_START] = {
    [ ANDROID_DEPTH_MAX_DEPTH_SAMPLES - ANDROID_DEPTH_START  ] =
    { "maxDepthSamples",                    DATA_INT32, 1   },
    [ ANDROID_DEPTH_AVAILABLE_DEPTH_STREAM_CONFIGURATIONS - ANDROID_DEPTH_START  ] =
    { "availableDepthStreamConfigurations", DATA_INT32, 1   },
    [ ANDROID_DEPTH_AVAILABLE_DEPTH_MIN_FRAME_DURATIONS - ANDROID_DEPTH_START  ] =
    { "availableDepthMinFrameDurations",    DATA_INT64, 1   },
    [ ANDROID_DEPTH_AVAILABLE_DEPTH_STALL_DURATIONS - ANDROID_DEPTH_START  ] =
    { "availableDepthStallDurations",        DATA_INT64, 1   },
    [ ANDROID_DEPTH_DEPTH_IS_EXCLUSIVE - ANDROID_DEPTH_START  ] =
    { "depthIsExclusive",                    DATA_BYTE,  1   },
};

tag_info_t *tags_info[ANDROID_SECTION_COUNT] = {
    android_color_correction,
    android_control,
    android_demosaic,
    android_edge,
    android_flash,
    android_flash_info,
    android_hot_pixel,
    android_jpeg,
    android_lens,
    android_lens_info,
    android_noise_reduction,
    android_quirks,
    android_request,
    android_scaler,
    android_sensor,
    android_sensor_info,
    android_shading,
    android_statistics,
    android_statistics_info,
    android_tonemap,
    android_led,
    android_info,
    android_black_level,
    android_sync,
    android_reprocess,
    android_depth,
};

typedef struct meta_head
{
    unsigned int verify_flag_a; //this value should be (head_flag + tail_offset)
    unsigned int verify_flag_b; // this value should be (head_flag - 1)
    unsigned int tail_offset; //offset of last tag payload tail from the buffer's very begin
    unsigned int tag_count;
}meta_head_t;

typedef struct meta_priv
{
    void* metadata_buffer;
    unsigned int buffer_size;
}meta_priv_t;

static unsigned int get_type_size(unsigned int type)
{
    switch(type)
    {
        case DATA_BYTE:
            return sizeof(unsigned char);
        case DATA_INT32:
            return sizeof(signed int);
        case DATA_FLOAT:
            return sizeof(float);
        case DATA_INT64:
            return sizeof(signed long long int);
        case DATA_DOUBLE:
            return sizeof(double);
        case DATA_RATIONAL:
            return sizeof(camera_rational_t);
        default:
            return 0;
    }
}

static int check_metadata(const isp_metadata_t* meta)
{
    if(NULL == meta)
    {
        META_LOGE("%s: isp_metadata_t is NULL", __FUNCTION__);
        return -1;
    }

    if(NULL == meta->priv)
    {
        META_LOGE("%s: invalid isp_metadata_t", __FUNCTION__);
        return -1;
    }

    meta_priv_t* priv = (meta_priv_t* )(meta->priv);

    if(NULL == priv->metadata_buffer)
    {

        META_LOGE("%s: isp_metadata_t contaions no buffer", __FUNCTION__);
        return -1;
    }

    if(priv->buffer_size <= MIN_BUFFER_SIZE)
    {

        META_LOGE("%s: isp_metadata_t contaions buffer too small!", __FUNCTION__);
        return -1;
    }

    return 0;
}

static int get_tag_entry_offset(unsigned int tag, unsigned int* offset)
{
    unsigned int i = 0;
    unsigned int temp_offset = 0;
    unsigned int temp_offset_vendor = 0;
    unsigned int section_index = (tag>>16)&0x0000ffff;

    if(section_index < ANDROID_SECTION_COUNT)
    {
        for(i = 0; i < section_index; i++)
        {
            temp_offset += camera_metadata_section_bounds[i][1] - camera_metadata_section_bounds[i][0];
        }

        *offset = (temp_offset + (tag&0x0000ffff)) * sizeof(meta_entry_t);
        return 0;
    }
    else
    {
        for(i = 0; i < ANDROID_SECTION_COUNT; i++)
        {
            temp_offset += camera_metadata_section_bounds[i][1] - camera_metadata_section_bounds[i][0];
        }
    }

    if(0 != get_section_index_offset_vendor(tag, &temp_offset_vendor))
    {
        META_LOGE("%s: fail to get vendor tag section index offset! tag:0x%x", __FUNCTION__, tag);
        return -META_EINVAL;
    }

    *offset = (temp_offset + temp_offset_vendor + (tag&0x0000ffff)) * sizeof(meta_entry_t);
    return 0;
}

static int get_tag_entry(void* meta_buffer, unsigned int tag, meta_entry_t* entry)
{
    if(NULL == entry)
    {
        META_LOGE("%s: invalid entry pointer!", __FUNCTION__);
        return -META_EINVAL;
    }

    unsigned int entry_offset;

    if(0 != get_tag_entry_offset(tag, &entry_offset))
    {
        META_LOGE("%s: fail to get tag entry offset! tag:0x%x", __FUNCTION__, tag);
        return -META_EINVAL;
    }

    memcpy(entry, (char*)meta_buffer + entry_offset + sizeof(meta_head_t), sizeof(meta_entry_t));

    return 0;
}

static int update_tag_entry(void* meta_buffer, meta_entry_t* entry, unsigned int tag)
{
    if(NULL == entry)
    {
        META_LOGE("%s: input entry is NULL", __FUNCTION__);
        return -META_EINVAL;
    }

    unsigned int entry_offset;

    if(get_tag_entry_offset(tag, &entry_offset))
    {
        META_LOGE("%s: get entry offset failed! tag: 0x%x", __FUNCTION__, tag);
        return -META_EINVAL;
    }

    memcpy((char*)meta_buffer + entry_offset + sizeof(meta_head_t), entry, sizeof(meta_entry_t));
    return 0;
}

#if 0
static unsigned int get_tags_count(isp_metadata_t* meta)
{
    META_LOGD("enter %s", __FUNCTION__);

    if(check_metadata(meta) != 0)
    {
        META_LOGE("%s: invalid metadata!", __FUNCTION__);
        return -META_EINVAL;
    }

    unsigned int count = 0;
    meta_head_t head;
    const tag_info_t* tag_info;
    meta_entry_t entry;
    unsigned int tag_exist;
    unsigned int tag;
    unsigned int data_size;
    unsigned int offset = sizeof(meta_head_t) + TOTAL_ENTRY_SIZE;
    meta_priv_t* priv = (meta_priv_t*)(meta->priv);


    memcpy(&head, priv->metadata_buffer, sizeof(head));

    char* tag_addr = (char*)priv->metadata_buffer + offset;

    while(offset < head.tail_offset)
    {
        memcpy(&tag, tag_addr, sizeof(tag));
        //check taginfo
        tag_info = isp_metadata_get_taginfo(tag);
        if(tag_info == NULL)
        {
            META_LOGE("%s: can't get tag info tag = 0x%x", __FUNCTION__, tag);
            return 0;
        }
        //check tag entry exist flag
        if(0 != get_tag_entry(priv->metadata_buffer, tag, &entry))
        {
            META_LOGE("%s: get tag entry failed! tag = 0x%x", __FUNCTION__, tag);
            return 0;
        }
        tag_exist = entry.entry_info&0x80000000;
        if(tag_exist)
        {
            count++;
        }
        data_size = get_type_size(tag_info->data_type) * (tag_info->data_max_count);
        offset += (sizeof(tag) + data_size);
        tag_addr = tag_addr + sizeof(tag) + data_size;//next tag address
    }

    return count;
}
#endif
int isp_metadata_get_tag_entry(isp_metadata_t* meta, unsigned int tag, meta_entry_t* entry)
{
    if(check_metadata(meta) != 0)
    {
        META_LOGE("%s: invalid metadata!", __FUNCTION__);
        return -META_EINVAL;
    }

    meta_priv_t* priv = (meta_priv_t*)(meta->priv);

    const tag_info_t* tag_info = isp_metadata_get_taginfo(tag);
    if(NULL == tag_info)
    {
        META_LOGE("%s: invalid tag 0x%x!", __FUNCTION__, tag);
        return -META_EINVAL;
    }

    if(0 != get_tag_entry(priv->metadata_buffer, tag, entry))
    {
        META_LOGE("%s: get tag entry failed! tag = 0x%x", __FUNCTION__, tag);
        return -META_EINVAL;
    }

    return 0;
}

const tag_info_t* isp_metadata_get_taginfo(unsigned int tag)
{
    unsigned int section_index = (tag>>16)&0x0000ffff;

    if(section_index < ANDROID_SECTION_COUNT)
    {
        if(tag < camera_metadata_section_bounds[section_index][1])
        {
            return &tags_info[section_index][tag&0x0000ffff];
        }
        else
        {
            return NULL;
        }
    }
    else
    {
        return get_vendor_tag_info(tag);
    }
}

const char* isp_metadata_get_vendor_section_name(unsigned int tag)
{
    return get_vendor_section_name(tag);
}

unsigned int isp_metadata_get_vendor_tag_count()
{
    return get_vendor_tag_count();
}

void isp_metadata_get_all_vendor_tags(unsigned int *tag_array)
{
    get_all_vendor_tags(tag_array);
}

int isp_metadata_attach_buffer(isp_metadata_t* meta, void* buffer, unsigned int buffer_size)
{
    META_LOGD("enter %s, meta=%pK, buffer=%pK, size=0x%x", __FUNCTION__, meta, buffer, buffer_size);

    meta_head_t head;

    if(NULL == meta || NULL == buffer)
    {
        META_LOGE("%s: invalid isp_metadata_t or buffer! meta = %pK, buffer = %pK", __FUNCTION__, meta, buffer);
        return -META_EINVAL;
    }

    if(buffer_size <= MIN_BUFFER_SIZE)
    {
        META_LOGE("%s: buffer size too small! at least:0x%x, actually:0x%x", __FUNCTION__, MIN_BUFFER_SIZE+1, buffer_size);
        return -META_EINVAL;
    }

    meta_priv_t* priv = (meta_priv_t*)(meta->priv);

    if(NULL == priv)
    {
        priv = (meta_priv_t*)META_MALLOC(sizeof(meta_priv_t));
        if(NULL == priv)
        {
            META_LOGE("%s: META_MALLOC for meta_priv_t failed!", __FUNCTION__);
            return -META_ENOMEM;
        }

        memset(priv, 0, sizeof(meta_priv_t));
        meta->priv = priv;
    }

    if(NULL != priv->metadata_buffer)
    {
        META_LOGE("buffer already setted! can't set again!");
        return -META_EPERM;
    }

    memcpy(&head, buffer, sizeof(head));
    priv->metadata_buffer   = buffer;
    priv->buffer_size       = buffer_size;

    if(head.verify_flag_a != (HEAD_FLAG + head.tail_offset)
        || head.verify_flag_b != HEAD_FLAG - 1)
    {
        memset(buffer, 0x00, buffer_size);
        //write head
        head.tail_offset = TOTAL_ENTRY_SIZE + sizeof(meta_head_t);
        head.verify_flag_a = HEAD_FLAG + head.tail_offset;
        head.verify_flag_b = HEAD_FLAG - 1;
        head.tag_count     = 0;
        memcpy(buffer, &head, sizeof(head));
    }

    return 0;
}

void* isp_metadata_detach_buffer(const isp_metadata_t* meta)
{
    META_LOGD("enter %s", __FUNCTION__);

    void* buffer;
    meta_priv_t* priv;
    if(NULL == meta || NULL == meta->priv)
    {
        META_LOGE("%s: invalid parameter!", __FUNCTION__);
        return NULL;
    }

    priv = (meta_priv_t*)(meta->priv);

    if(NULL == priv->metadata_buffer)
    {
        META_LOGE("%s: no buffer to release!", __FUNCTION__);
        return NULL;
    }

    buffer = priv->metadata_buffer;
    memset(priv, 0, sizeof(meta_priv_t));

    return buffer;
}

isp_metadata_t* isp_metadata_create(void* buffer, unsigned int buffer_size)
{
    META_LOGD("enter %s, buffer=%pK, buffer_size=0x%x", __FUNCTION__, buffer, buffer_size);

    isp_metadata_t* meta = (isp_metadata_t*)META_MALLOC(sizeof(isp_metadata_t));
    if(NULL == meta)
    {
        META_LOGE("%s: META_MALLOC for isp_metadata_t failed!", __FUNCTION__);
        goto ERROR_1;
    }

    meta->priv = NULL;

    if(NULL == buffer)
    {
        //This is not an error. Buffer whould be setted in later.
        META_LOGD("%s: isp_metadata_t created with no buffer.", __FUNCTION__);
        return meta;
    }

    if(isp_metadata_attach_buffer(meta, buffer, buffer_size) != 0)
    {
        META_LOGE("%s: attach buffer failed!", __FUNCTION__);
        goto ERROR_2;
    }

    return meta;

ERROR_2:
    META_FREE(meta);
ERROR_1:
    return NULL;
}

void* isp_metadata_destroy(isp_metadata_t** meta)
{
    META_LOGD("enter %s", __FUNCTION__);

    void* buffer = NULL;

    if(NULL == meta || NULL == *meta)
    {
        META_LOGE("%s: NULL metadata to destroy!", __FUNCTION__);
        return NULL;
    }

    meta_priv_t *priv = (meta_priv_t *)((*meta)->priv);

    if(NULL != priv)
    {
        buffer = priv->metadata_buffer;
        META_FREE(priv);
    }

    META_FREE(*meta);
    *meta = NULL;

    return buffer;
}

int isp_metadata_set(const isp_metadata_t* meta, unsigned int tag, const void* value, unsigned int type_size, unsigned int count)
{
//    META_LOGD("enter %s", __FUNCTION__);

    if(check_metadata(meta) != 0)
    {
        META_LOGE("%s: invalid metadata", __FUNCTION__);
        return -META_EINVAL;
    }

    if(NULL == value)
    {
        META_LOGE("%s: value is NULL", __FUNCTION__);
        return -META_EINVAL;
    }

    const tag_info_t* tag_info = isp_metadata_get_taginfo(tag);
    if(NULL == tag_info)
    {
        META_LOGE("%s: invalid tag 0x%x", __FUNCTION__, tag);
        return -META_EINVAL;
    }

    meta_priv_t* priv = (meta_priv_t* )(meta->priv);
    meta_head_t head;
    memcpy(&head, priv->metadata_buffer, sizeof(head));

    if(type_size != get_type_size(tag_info->data_type) || count > tag_info->data_max_count)
    {
        META_LOGE("%s: %s tag(0x%x) data size or count fault! expected size = %u, max_count = %u, actually: size = %u, count = %u",
            __FUNCTION__,  tag_info->tag_name, tag, get_type_size(tag_info->data_type), tag_info->data_max_count, type_size, count);
        return -META_EINVAL;
    }

    meta_entry_t entry;
    if(0 != get_tag_entry(priv->metadata_buffer, tag, &entry))
    {
        META_LOGE("%s: get tag entry failed! tag = 0x%x", __FUNCTION__, tag);
        return -META_EINVAL;
    }

    unsigned int tag_exist  = entry.entry_info&0x80000000;
    unsigned int tag_offset = entry.entry_info&0x7fffffff;

    if(tag_exist && (tag_offset < priv->buffer_size - sizeof(tag)))
    {
        memcpy((char*)priv->metadata_buffer + tag_offset + sizeof(tag), value, type_size*count);
        entry.data_count = count;
        if(0 != update_tag_entry(priv->metadata_buffer, &entry, tag))
        {
            META_LOGE("%s: fail to update tag entry! tag:0x%x", __FUNCTION__, tag);
            return -META_EINVAL;
        }
    }
    else
    {
        char* tag_addr = NULL;
        unsigned int payload_size = type_size*count;
        unsigned int payload_space = type_size*tag_info->data_max_count;

        if((head.tail_offset + sizeof(tag) + payload_space) > priv->buffer_size)
        {
            META_LOGE("%s: buffer too small, can't set[tag:%s 0x%x], need %u more, current free space:%u",
                    __FUNCTION__, tag_info->tag_name, tag, sizeof(tag) + payload_space, priv->buffer_size - head.tail_offset);
            return -META_ENOMEM;
        }

        tag_addr = (char*)(priv->metadata_buffer) + head.tail_offset;
        memcpy(tag_addr, &tag, sizeof(tag));
        memcpy(tag_addr + sizeof(tag), value, payload_size);
        entry.entry_info = head.tail_offset|0x80000000;
        entry.data_count = count;
        head.tail_offset += sizeof(tag) + payload_space;
        head.verify_flag_a = HEAD_FLAG + head.tail_offset;
        head.verify_flag_b = HEAD_FLAG - 1 ;
        head.tag_count++;
        if(0 != update_tag_entry(priv->metadata_buffer, &entry, tag))
        {
            META_LOGE("%s: fail to update tag entry! tag:0x%x", __FUNCTION__, tag);
            return -META_EINVAL;
        }
        memcpy(priv->metadata_buffer, &head, sizeof(head));
    }

    return 0;
}

int isp_metadata_get(const isp_metadata_t* meta, unsigned int tag, void* result, unsigned int type_size, unsigned int count)
{
//    META_LOGD("enter %s", __FUNCTION__);
    if(NULL == result)
    {
        META_LOGE("%s: result buffer is NULL", __FUNCTION__);
        return -META_EINVAL;
    }

    if(check_metadata(meta) != 0)
    {
        META_LOGE("%s: invalid metadata!", __FUNCTION__);
        return -META_EINVAL;
    }
    meta_priv_t* priv = (meta_priv_t*)(meta->priv);

    const tag_info_t* tag_info = isp_metadata_get_taginfo(tag);
    if(NULL == tag_info)
    {
        META_LOGE("%s: invalid tag 0x%x!", __FUNCTION__, tag);
        return -META_EINVAL;
    }

    if(type_size != get_type_size(tag_info->data_type))
    {
        META_LOGE("%s: [tag %s 0x%x] mismatching type size: %u, expected: %u!", __FUNCTION__, tag_info->tag_name, tag, type_size, get_type_size(tag_info->data_type));
        return -META_EINVAL;
    }

    meta_entry_t entry;
    if(get_tag_entry(priv->metadata_buffer, tag, &entry) != 0)
    {
        META_LOGE("%s: can't find tag entry!", __FUNCTION__);
        return -META_EINVAL;
    }
    unsigned int tag_exist  = entry.entry_info&0x80000000;
    unsigned int tag_offset = entry.entry_info&0x7fffffff;

    if(!tag_exist)
    {
        //no value of this tag
        return -META_EINVAL;
    }

    if(entry.data_count != count)
    {
        META_LOGE("%s: [tag %s 0x%x] data count : %u mismatch, setted count is: %u!", __FUNCTION__, tag_info->tag_name, tag, count, entry.data_count);
        return -META_EINVAL;
    }

    void* data_addr = (void*)((char*)priv->metadata_buffer + tag_offset + sizeof(tag));

    memcpy(result, data_addr, type_size*count);
    return 0;
}

int isp_metadata_delete(const isp_metadata_t* meta, unsigned int tag)
{
    return 0;
}

int isp_metadata_update(const isp_metadata_t* src_meta, isp_metadata_t* des_meta)
{
    META_LOGD("enter %s", __FUNCTION__);

    int ret;
    if(check_metadata(src_meta) != 0)
    {
        META_LOGE("%s: invalid src_meta!", __FUNCTION__);
        return -META_EINVAL;
    }

    if(check_metadata(des_meta) != 0)
    {
        META_LOGE("%s: invalid des_meta!", __FUNCTION__);
        return -META_EINVAL;
    }

    meta_head_t       head;
    unsigned int      tag;
    const tag_info_t* tag_info;
    unsigned int      type_size;
    unsigned int      payload_size;

    meta_priv_t* src_priv = (meta_priv_t*)(src_meta->priv);
    unsigned int offset = sizeof(meta_head_t) + TOTAL_ENTRY_SIZE;
    char* tag_addr = (char*)src_priv->metadata_buffer + offset;
    memcpy(&head, src_priv->metadata_buffer, sizeof(head));

    while(offset < head.tail_offset)
    {
        memcpy(&tag, tag_addr, sizeof(tag));
        tag_info = isp_metadata_get_taginfo(tag);
        if(tag_info == NULL)
        {
            META_LOGE("%s: can't get tag info tag = 0x%x", __FUNCTION__, tag);
            return -META_EINVAL;
        }
        type_size = get_type_size(tag_info->data_type);
        payload_size = type_size * tag_info->data_max_count;

        ret = isp_metadata_set(des_meta, tag, tag_addr + sizeof(tag), type_size, tag_info->data_max_count);
        if(0 != ret)
        {
            META_LOGE("%s: set metadata tag failed! tag:0x%x", __FUNCTION__, tag);
            return ret;
        }

        offset += (sizeof(tag) + payload_size);
        tag_addr = tag_addr + sizeof(tag) + payload_size;//next tag address
    }

    return 0;
}

unsigned int isp_metadata_get_tags_count(isp_metadata_t* meta)
{
    META_LOGD("enter %s", __FUNCTION__);

    if(check_metadata(meta) != 0)
    {
        META_LOGE("%s: invalid metadata!", __FUNCTION__);
        return 0;
    }
    meta_priv_t* priv = (meta_priv_t*)(meta->priv);
    meta_head_t head;
    memcpy(&head, priv->metadata_buffer, sizeof(head));
    return head.tag_count;
}

int isp_metadata_get_tags(isp_metadata_t* meta, unsigned int *tag_array, unsigned int array_size)
{
    META_LOGD("enter %s", __FUNCTION__);

    if(check_metadata(meta) != 0)
    {
        META_LOGE("%s: invalid metadata!", __FUNCTION__);
        return -META_EINVAL;
    }

    if(NULL == tag_array)
    {
        META_LOGE("%s: tag_array is NULL!", __FUNCTION__);
        return -META_EINVAL;
    }

    unsigned int count = 0;
    meta_head_t head;
    const tag_info_t* tag_info;
    unsigned int tag;
    unsigned int data_size;
    unsigned int tag_exist;
    unsigned int offset = sizeof(meta_head_t) + TOTAL_ENTRY_SIZE;
    meta_priv_t* priv = (meta_priv_t*)(meta->priv);

    memcpy(&head, priv->metadata_buffer, sizeof(head));

    char* tag_addr = (char*)priv->metadata_buffer + offset;

    while((offset < head.tail_offset) && (count < array_size))
    {
        memcpy(&tag, tag_addr, sizeof(tag));
        tag_info = isp_metadata_get_taginfo(tag);
        if(tag_info == NULL)
        {
            META_LOGE("%s: can't get tag info tag = 0x%x", __FUNCTION__, tag);
            return -META_EINVAL;
        }

        meta_entry_t entry;
        if(get_tag_entry(priv->metadata_buffer, tag, &entry) != 0)
        {
            META_LOGE("%s: can't find tag entry!", __FUNCTION__);
            return -META_EINVAL;
        }
        tag_exist  = entry.entry_info&0x80000000;

        if(tag_exist)
        {
            tag_array[count] = tag;
        }

        data_size = get_type_size(tag_info->data_type) * (tag_info->data_max_count);
        offset += (sizeof(tag) + data_size);
        tag_addr = tag_addr + sizeof(tag) + data_size;//next tag address
        count++;
    }

    return 0;
}

unsigned int isp_metadata_get_type_size(unsigned int tag)
{
    const tag_info_t* tag_info = isp_metadata_get_taginfo(tag);
    if(tag_info == NULL)
    {
        META_LOGE("%s: get tag[0x%x] info failed!", __FUNCTION__, tag);
        return 0;
    }
    return get_type_size(tag_info->data_type);
}

unsigned int isp_metadata_get_data_count(unsigned int tag)
{
    const tag_info_t* tag_info = isp_metadata_get_taginfo(tag);
    if(tag_info == NULL)
    {
        META_LOGE("%s: get tag[0x%x] info failed!", __FUNCTION__, tag);
        return 0;
    }
    return tag_info->data_max_count;
}

void* isp_metadata_get_data_addr(const isp_metadata_t* meta, unsigned int tag)
{
    if(check_metadata(meta) != 0)
    {
        META_LOGE("%s: invalid metadata!", __FUNCTION__);
        return NULL;
    }

    meta_priv_t* priv = (meta_priv_t*)(meta->priv);

    const tag_info_t* tag_info = isp_metadata_get_taginfo(tag);
    if(NULL == tag_info)
    {
        META_LOGE("%s: invalid tag 0x%x!", __FUNCTION__, tag);
        return NULL;
    }

    meta_entry_t entry;
    if(get_tag_entry(priv->metadata_buffer, tag, &entry) != 0)
    {
        META_LOGE("%s: can't find tag entry!", __FUNCTION__);
        return NULL;
    }
    unsigned int tag_exist  = entry.entry_info&0x80000000;
    unsigned int tag_offset = entry.entry_info&0x7fffffff;

    if(!tag_exist)
    {
        //no value of this tag
        return NULL;
    }

    return (void*)((char*)priv->metadata_buffer + tag_offset + sizeof(tag));
}

void print_data(int data_type, char* data_ptr, unsigned int data_count)
{
    char                  char_value;
    float                float_value;
    int                  int32_value;
    long long int        int64_value;
    double              double_value;
    camera_rational_t rational_value;

    unsigned int i;
    unsigned int bp = 0;

    char temp[120];
    memset(temp, 0, sizeof(temp));

    if(NULL == data_ptr)
    {
        return;
    }

    for(i = 0; i < data_count; i++)
    {
        switch(data_type)
        {
            case DATA_BYTE:
                memcpy(&char_value, data_ptr + i, sizeof(char_value));
                bp += (unsigned int)sprintf(&temp[bp], "%d, ", char_value);
                break;
            case DATA_FLOAT:
                //memcpy(&float_value, data_ptr + i*sizeof(float_value), sizeof(float_value));
                //bp += (unsigned int)sprintf(&temp[bp], "%d.%d, ", (int)float_value, ((int)((float_value) * 1000) % 1000));
                break;
            case DATA_INT32:
                memcpy(&int32_value, data_ptr + i*sizeof(int32_value), sizeof(int32_value));
                bp += (unsigned int)sprintf(&temp[bp], "%d, ", int32_value);
                break;
            case DATA_INT64:
                memcpy(&int64_value, data_ptr + i*sizeof(int64_value), sizeof(int64_value));
                bp += (unsigned int)sprintf(&temp[bp], "%lld, ", int64_value);
                break;
            case DATA_DOUBLE:
                //memcpy(&double_value, data_ptr + i*sizeof(double_value), sizeof(double_value));
                //bp += (unsigned int)sprintf(&temp[bp], "%d.%d, ", (int)double_value, ((int)((double_value) * 1000) % 1000));
                break;
            case DATA_RATIONAL:
                memcpy(&rational_value, data_ptr + i*sizeof(rational_value), sizeof(rational_value));
                bp += (unsigned int)sprintf(&temp[bp], "%d/%d, ", rational_value.numerator, rational_value.denominator);
                break;
            default:
                break;
        }

        if(bp > 100)
        {
            META_LOGI(" |     %s", temp);
            bp = 0;
            memset(temp, 0, sizeof(temp));
            break;
        }
    }

    if(bp != 0)
    {
        META_LOGI(" |     %s", temp);
    }
}

void isp_metadata_dump(const isp_metadata_t* meta)
{
    META_LOGD("enter %s", __FUNCTION__);

    if(check_metadata(meta) != 0)
    {
        return;
    }

    unsigned int count = 0;
    meta_head_t head;
    const tag_info_t* tag_info;
    unsigned int tag;
    unsigned int data_size;
    unsigned int tag_exist;
    unsigned int offset = sizeof(meta_head_t) + TOTAL_ENTRY_SIZE;
    meta_priv_t* priv = (meta_priv_t*)(meta->priv);


    memcpy(&head, priv->metadata_buffer, sizeof(head));

    char* tag_addr = (char*)priv->metadata_buffer + offset;
    META_LOGI("  ================metadata dump begin=================");
    META_LOGI("  ===buffer size=0x%.8x, tail offset=0x%.8x===", priv->buffer_size, head.tail_offset);

    while(offset < head.tail_offset)
    {
        memcpy(&tag, tag_addr, sizeof(tag));
        tag_info = isp_metadata_get_taginfo(tag);
        if(tag_info == NULL)
        {
            META_LOGE("%s: can't get tag info tag = 0x%x", __FUNCTION__, tag);
            return;
        }
        META_LOGI(" | %s 0x%.8x", tag_info->tag_name, tag);

        const char* type = NULL;

        switch(tag_info->data_type)
        {
            case DATA_BYTE:
                type = "BYTE,     ";
                break;
            case DATA_FLOAT:
                type = "FLOAT,    ";
                break;
            case DATA_INT32:
                type = "INT32,    ";
                break;
            case DATA_INT64:
                type = "INT64,    ";
                break;
            case DATA_DOUBLE:
                type = "DOUBLE,   ";
                break;
            case DATA_RATIONAL:
                type = "RATIONAL, ";
                break;
            default:
                type = "ERRORTYPE,";
                break;
        }

        meta_entry_t entry;
        if(get_tag_entry(priv->metadata_buffer, tag, &entry) != 0)
        {
            META_LOGE("%s: can't find tag entry, dump fail!", __FUNCTION__);
            break;
        }
        tag_exist  = entry.entry_info&0x80000000;

        META_LOGI(" |   %sCOUNT=%5u: offset = 0x%.8x", type, entry.data_count, offset);

        if(!tag_exist)
        {
            META_LOGI("|   tag_deleted!");
        }

        print_data(tag_info->data_type, tag_addr + sizeof(tag), entry.data_count);

        data_size = get_type_size(tag_info->data_type) * (tag_info->data_max_count);
        offset += (sizeof(tag) + data_size);
        tag_addr = tag_addr + sizeof(tag) + data_size;//next tag address
        count++;
    }

    META_LOGI("  =======metadata dump end,total tag count = %u=======", count);
}
/*lint +e732 +e774 +e785 +e845 +e715 +e818 +e705 +e717 +e734 +e835 +e713 +e838 +e826 +e737 +e701 +e801 +e778 +e785
+esym(732,*) +esym(774,*) +esym(785,*) +esym(845,*) +esym(715,*) +esym(818,*) +esym(705,*) +esym(717,*) +esym(734,*)
+esym(835,*) +esym(713,*) +esym(838,*) +esym(826,*) +esym(737,*) +esym(701,*)
+esym(801,*) +esym(778,*) +esym(785,*)*/
/********************************** END **********************************************/

