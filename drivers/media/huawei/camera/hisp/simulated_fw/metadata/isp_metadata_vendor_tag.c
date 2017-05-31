
/*lint -e732 -e774 -e785 -e845 -e715 -e818 -e705 -e717 -e734 -e835 -e713 -e838 -e826 -e737 -e701 -e801
-e778
-esym(732,*) -esym(774,*) -esym(785,*) -esym(845,*) -esym(715,*) -esym(818,*) -esym(705,*) -esym(717,*) -esym(734,*)
-esym(835,*) -esym(713,*) -esym(838,*) -esym(826,*) -esym(737,*) -esym(701,*)
-esym(801,*) -esym(778,*)*/
#define ISP_METADATA_LINUX

#ifdef ISP_METADATA_FIRMWARE

#include <stdlib.h>
#include "utils/log.h"
#include "utils/isp_metadata.h"
#include "utils/isp_metadata_vendor_tag.h"

#elif defined ISP_METADATA_ANDROID

#include <stdlib.h>
#include <utils/Log.h>
#include "isp_metadata.h"
#include "isp_metadata_vendor_tag.h"

#elif defined ISP_METADATA_LINUX

//#include <stdlib.h>
//#include <stdio.h>
#include <linux/stddef.h>
#include <linux/errno.h>
#include <linux/types.h>
#include "isp_metadata.h"
#include "isp_metadata_vendor_tag.h"
#ifdef HISP_V150
#include "../hisp150_md_message.h"
#else
#include "../hisp_md_message.h"
#endif

#endif


const char *isp_metadata_vendor_section_names[ANDROID_HUAWEI_SECTION_MAX -
    VENDOR_SECTION] =
{
    "ANDROID_HUAWEI_DEVICE_CAPABILITIES",
    "ANDROID_HUAWEI_DEVICE_PARAMETERS",
    "ANDROID_HUAWEI_METADATA",
    "ANDROID_HUAWEI_STREAM_INFO",
    "ANDROID_HUAWEI_STREAM_PARAMETERS",
};

static int vendor_section_bounds[ANDROID_HUAWEI_SECTION_MAX -
    VENDOR_SECTION][2] =
{
    {ANDROID_HUAWEI_DEVICE_CAPABILITIES_START, ANDROID_HUAWEI_DEVICE_CAPABILITIES_END},//no tag now
    {ANDROID_HUAWEI_DEVICE_PARAMETERS_START, ANDROID_HUAWEI_DEVICE_PARAMETERS_END},//no tag now
    {ANDROID_HUAWEI_METADATA_START, ANDROID_HUAWEI_METADATA_END},
    {ANDROID_HUAWEI_STREAM_INFO_START, ANDROID_HUAWEI_STREAM_INFO_END},//no tag now
    {ANDROID_HUAWEI_STREAM_PARAMETERS_START, ANDROID_HUAWEI_STREAM_PARAMETERS_END}//no tag now
};

static tag_info_t android_huawei_device_capabilities[ANDROID_HUAWEI_DEVICE_CAPABILITIES_END -
    ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
{
    [ANDROID_HUAWEI_DEVICE_SENSOR_POSITION - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.device.sensor.position",       DATA_INT32, 1},
    [ANDROID_HW_VIDEO_FPS_SUPPORTED - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"hw-video-fps-supported", DATA_INT32, 32},
    [ANDROID_HW_SUPPORTED_ISO_VALUES - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.supported.iso.values",  DATA_BYTE, 8},
    [ANDROID_HW_SUPPORTED_CONTRAST - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.supported.contrast",       DATA_BYTE, 32},
    [ANDROID_HW_SUPPORTED_SATURATION - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.supported.saturation",       DATA_BYTE, 32},
    [ANDROID_HW_SUPPORTED_BRIGHTNESS - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.supported.brightness",       DATA_BYTE, 32},
    [ANDROID_HW_SUPPORTED_SHARPNESS - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.supported.sharpness",       DATA_BYTE, 32},
    [ANDROID_HW_SUPPORTED_METERING - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.supported.metering",       DATA_BYTE, 32},
    //[ANDROID_HW_HDR_MOVIE_SUPPORTED - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
    //    {"android.hw.hdr.movie.supported",       DATA_BYTE, 1},
    [ANDROID_HW_CAPTURE_MIRROR_SUPPORTED - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.capture.mirror.supported", DATA_BYTE, 1},
    [ANDROID_HW_MANUAL_VCM_START_VALUE - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.manual.vcm.start.value",       DATA_INT32, 1},
    [ANDROID_HW_MANUAL_VCM_END_VALUE - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.manual.vcm.end.value",       DATA_INT32, 1},
    [ANDROID_HW_BURST_SUPPORT_COUNT - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.burst.support.count",       DATA_INT32, 1},
    [ANDROID_HW_BURST_JPEG_QUALITY - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.burst.jpeg.quality",       DATA_INT32, 1},
    [ANDROID_HW_BURST_YUV_BUFFER_COUNT - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.burst.yuv.buffer.count",       DATA_INT32, 1},
    [ANDROID_HW_BURST_RAW_BUFFER_COUNT - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.burst.raw.buffer.count",       DATA_INT32, 1},
    [ANDROID_HW_EQUIVALENT_FOCUS - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.equivalent.focus", DATA_INT32, 1},
    [ANDROID_HW_EXPOWURE_COMP_SUPPORTED - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.expowure.comp.supported",       DATA_BYTE, 1},
    [ANDROID_HW_EXPOWURE_COMP_STEP - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.expowure.comp.step",       DATA_FLOAT, 1},
    [ANDROID_HW_AVAILABLE_VIDEO_STABILIZATION_MODES - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
        {"android.hw.available.video.stabilization.modes",       DATA_BYTE, 1},
    [ANDROID_HW_PROFESSIONAL_RAW12_SUPPORTED - ANDROID_HUAWEI_DEVICE_CAPABILITIES_START] =
    {"android.hw.professional.raw12.supported",       DATA_INT32, 1},
};

static tag_info_t android_huawei_metadata[ANDROID_HUAWEI_METADATA_END -
    ANDROID_HUAWEI_METADATA_START] =
{
    //AF
    [ANDROID_HW_MANUAL_FOCUS_MODE - ANDROID_HUAWEI_METADATA_START] =
        { "android.hw.manual.focusMode",           DATA_BYTE,        1      },
    [ANDROID_HW_MANUAL_FOCUS_STEP_VALUE - ANDROID_HUAWEI_METADATA_START] =
        { "android.hw.manual.focusStepValue",      DATA_INT32,       1      },
    [ANDROID_HW_FAST_SHOT_MODE - ANDROID_HUAWEI_METADATA_START] =
        { "android.hw.fastShotMode",               DATA_BYTE,        1      },
    [ANDROID_HW_DEVICE_TARGET_TRACKING - ANDROID_HUAWEI_METADATA_START] =
        { "android.hw.deviceTargetTracking",       DATA_BYTE,        1      },
    [ANDROID_HW_ZOOM_IN - ANDROID_HUAWEI_METADATA_START] =
        { "android.hw.zoomIn",                     DATA_FLOAT,       1      },
    [ANDROID_HW_DUAL_CAMERA_VERIFICATION_MODE - ANDROID_HUAWEI_METADATA_START] =
        { "android.hw.dualCameraVerificationMode", DATA_BYTE,        1      },
    [ANDROID_HW_MMI_7CMAF_TEST_ENABLE - ANDROID_HUAWEI_METADATA_START] =
        { "android.hw.mmi7CmafTestEnable",         DATA_BYTE,        1      },

    //common
    [ANDROID_HISTAR_COMMON_SENSOR_INFO - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.common.sensorInfo",       DATA_INT32, 4},
    [ANDROID_HISTAR_COMMON_SENSOR_RESOLUTION - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.common.sensorResolution", DATA_INT32, 2},
    [ANDROID_HISTAR_COMMON_OTPINFO - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.common.otpInfo",          DATA_BYTE,  1219},
    [ANDROID_HISTAR_COMMON_STAT3A - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.common.stat3a",           DATA_INT32, (sizeof(stat3a_md_t)/sizeof(int32_t))},
    [ANDROID_HISTAR_COMMON_SAVERAW - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.common.saveraw",          DATA_INT32, 1},
    [ANDROID_HISTAR_COMMON_SAVEYUV - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.common.saveyuv",          DATA_INT32, 1},
    [ANDROID_HISTAR_COMMON_FACE_DETECTION - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.common.faceDetection", DATA_INT32, 111},
    //blc
    [ANDROID_HISTAR_BLC_VALUE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.blc.setValue", DATA_INT32, 4},

    //dgamma
    [ANDROID_HISTAR_DGAMMA_ENABLE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.dgamma.enable",         DATA_INT32,       1      },
    [ANDROID_HISTAR_DGAMMA_SET - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.dgamma.set",             DATA_INT32,       96*3   },
    [ANDROID_HISTAR_DGAMMA_GET - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.dgamma.get",   DATA_INT32,       96*3  },
    [ANDROID_HISTAR_DGAMMA_SET_LUTSCL_FACTOR - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.dgamma.setLutsclFactor", DATA_INT32,       1      },

    //lsc
    [ANDROID_HISTAR_LSC_ENABLE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.lsc.enable",            DATA_INT32,       1      },
    [ANDROID_HISTAR_LSC_MANUAL - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.lsc.manual",            DATA_INT32,       1      },
    [ANDROID_HISTAR_LSC_MANUAL_GAIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.lsc.manualGain",        DATA_INT32,       1      },
    [ANDROID_HISTAR_LSC_MANUAL_AWB - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.lsc.manualAWB",         DATA_INT32,       2      },
    [ANDROID_HISTAR_LSC_SET_INTENSITY - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.lsc.setIntensity",      DATA_INT32,       1      },
    [ANDROID_HISTAR_LSC_GET_INTENSITY - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.lsc.getIntensity",      DATA_INT32,       1      },
    [ANDROID_HISTAR_LSC_SET_CHROMATIX - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.lsc.setChromatix",      DATA_INT32,       15159  },
    [ANDROID_HISTAR_LSC_GET_AUTO_GAIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.lsc.getAutoGain",      DATA_INT32,       1      },
    [ANDROID_HISTAR_LSC_GET_AUTO_AWB - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.lsc.getAutoAWB",       DATA_INT32,       2      },

    //awb
    [ANDROID_HISTAR_AWB_ENABLE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.awb.enable",           DATA_INT32,       1      },
    [ANDROID_HISTAR_AWB_GET_GAIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.awb.getGain",          DATA_INT32,       4      },
    [ANDROID_HISTAR_AWB_SET_LIGHT - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.awb.setLight",         DATA_INT32,       1      },
    [ANDROID_HISTAR_AWB_SET_GAIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.awb.setGain",          DATA_INT32,       4      },
    [ANDROID_HISTAR_AWB_DAMPING_ENABLE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.awb.dampingEnable",    DATA_INT32,       1      },
    [ANDROID_HISTAR_AWB_SET_DAMPING_PARAM - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.awb.setDampingParam",  DATA_INT32,       1      },
    [ANDROID_HISTAR_AWB_GET_WHITEPOINT - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.awb.getWhitepoint",    DATA_INT32,       2      },
    [ANDROID_HISTAR_AWB_SET_WHITEPOINT - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.awb.setWhitepoint",    DATA_INT32,       2      },

    //gamma
    [ANDROID_HISTAR_GAMMA_ENABLE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.gamma.enable",          DATA_INT32,       1      },
    [ANDROID_HISTAR_GAMMA_MANUAL - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.gamma.manual",          DATA_INT32,       1      },
    [ANDROID_HISTAR_GAMMA_GET_AUTO_PARAMS - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.gamma.getAutoParams",   DATA_INT32,       257*4  },
    [ANDROID_HISTAR_GAMMA_SET_MANUAL_PARAMS - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.gamma.setManualParams", DATA_INT32,       257    },
    [ANDROID_HISTAR_GAMMA_SET_AUTO_PARAMS - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.gamma.setAutoParams",   DATA_INT32,       257*3  },

    //AE
    [ANDROID_HW_ISO - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.setCaptureIso",      DATA_INT32,       1      },
    [ANDROID_HW_METERING_MODE - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.setMeteringMode",    DATA_INT32,       1      },
    [ANDROID_HW_EXPOSURE_TIME - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.setExposureTime",    DATA_INT32,       1      },
    [ANDROID_HW_ALGO_EXPO_MAX - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getMaxExposureTime", DATA_INT32,       1      },
    [ANDROID_HW_ALGO_EXPO_MIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getMinExposureTime", DATA_INT32,       1      },
    [ANDROID_HW_ALGO_GAIN_MAX - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getMaxGain",         DATA_INT32,       1      },
    [ANDROID_HW_ALGO_GAIN_MIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getMinGain",         DATA_INT32,       1      },
    [ANDROID_HW_ALGO_LUM_MAX - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getLumMax",          DATA_INT32,       1      },
    [ANDROID_HW_ALGO_LUM_MIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getLumMin",          DATA_INT32,       1      },
    [ANDROID_HW_ALGO_EXPO - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getExposure",        DATA_INT32,       1      },
    [ANDROID_HW_ALGO_EXPO_TIME - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getExposureTime",    DATA_INT32,       1      },
    [ANDROID_HW_ALGO_GAIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getGain",            DATA_INT32,       1      },
    [ANDROID_HW_ALGO_ISO - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getIso",             DATA_INT32,       1      },
    [ANDROID_HW_ALGO_MEAN_Y - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getMeanY",           DATA_INT32,       1      },
    [ANDROID_HW_ALGO_AECSTABE - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getAecStableState",  DATA_INT32,       1      },
    [ANDROID_HW_ISO_STATE - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getIsoState",        DATA_INT32,       1      },
    [ANDROID_HW_AE_TARGET_LOW - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getTargetLow",       DATA_INT32,       1      },
    [ANDROID_HW_AE_TARGET_HIGH - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.getTargetHigh",      DATA_INT32,       1      },
    [ANDROID_HW_METERING_AREAS - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.setMeteringArea",    DATA_INT32,       5      },
    [ANDROID_HW_EXPOSURE_COMP_VALUE - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.setExposureCompensation", DATA_INT32,  1      },
    [ANDROID_HW_MANUAL_ISO - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.setManualIso",       DATA_INT32,       1      },
    [ANDROID_HW_MANUAL_EXPOSURE - ANDROID_HUAWEI_METADATA_START] =
        {"android.huawei.ae.setManualExpoTime",  DATA_INT32,       1      },

    [ANDROID_HISTAR_AE_SET_TARGET_Y - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.setTargetY",         DATA_INT32,       1      },
    [ANDROID_HISTAR_AE_SET_METER_MODE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.setMeterMode",       DATA_INT32,       1      },
    [ANDROID_HISTAR_AE_SET_METER_AREA - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.setMeterArea",       DATA_INT32,       4      },
    [ANDROID_HISTAR_AE_SET_TOLERANCE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.setTolerance",       DATA_INT32,       2      },
    [ANDROID_HISTAR_AE_MANUAL - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.setManual",          DATA_INT32,       1      },
    [ANDROID_HISTAR_AE_SET_GAIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.setGain",            DATA_INT32,       1      },
    [ ANDROID_HISTAR_AE_SET_EXPO_TIME - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.setExpoTime",        DATA_INT32,       1      },
    [ANDROID_HISTAR_AE_GET_CURRENT_Y - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.getCurrentY",        DATA_INT32,       1      },
    [ANDROID_HISTAR_AE_GET_GAIN - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.getGain",            DATA_INT32,       1      },
    [ANDROID_HISTAR_AE_GET_EXPO_TIME - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.getExpoTime",        DATA_INT32,       1      },
    [ANDROID_HISTAR_AE_GET_STABLE_STATUS- ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.getStableStatus",    DATA_INT32,       1      },
    [ANDROID_HISTAR_AE_GET_LOCK_STATUS - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.getLockStatus",      DATA_INT32,       1      },
    [ANDROID_HISTAR_AE_GAIN_RANGE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.ae.gainRange",          DATA_INT32,       2      },
    [ANDROID_HISTAR_VIDEO_STABILIZATION_MODE - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.vstab.mode",               DATA_BYTE,       1  },
    [ANDROID_HISTAR_BUFFER_METADATA - ANDROID_HUAWEI_METADATA_START] =
        {"android.histar.raw2yuv",               DATA_INT32,       MD_PARAM_SIZE * MAX_COP_CAM_CNT  },
};

tag_info_t* vendor_tag_infos[ANDROID_HUAWEI_SECTION_MAX - VENDOR_SECTION] =
{
    android_huawei_device_capabilities, //ANDROID_HUAWEI_DEVICE_CAPABILITIES
    NULL, //ANDROID_HUAWEI_DEVICE_PARAMETERS
    android_huawei_metadata,
    NULL, //ANDROID_HUAWEI_STREAM_INFO
    NULL, //ANDROID_HUAWEI_STREAM_PARAMETERS
};

const char* get_vendor_section_name(unsigned int tag)
{
    unsigned int index = ((tag>>16)&0x0000ffff) - VENDOR_SECTION;
    if(index < ANDROID_HUAWEI_SECTION_MAX - VENDOR_SECTION)
    {
        return isp_metadata_vendor_section_names[index];
    }

    return NULL;
}

const tag_info_t* get_vendor_tag_info(unsigned int tag)
{
    unsigned int index = ((tag>>16)&0x0000ffff) - VENDOR_SECTION;

    if(index < ANDROID_HUAWEI_SECTION_MAX - VENDOR_SECTION)
    {
        if(tag < (unsigned int)vendor_section_bounds[index][1])
        {
            return &(vendor_tag_infos[index][tag&0x0000ffff]);
        }
    }

    return NULL;
}

unsigned int get_vendor_tag_count(void)
{
    unsigned int count = 0;
    unsigned int i = 0;

    for(i = 0; i < ANDROID_HUAWEI_SECTION_MAX - VENDOR_SECTION; i++)
    {
        count += vendor_section_bounds[i][1] - vendor_section_bounds[i][0];
    }

    return count;
}

void get_all_vendor_tags(unsigned int *tag_array)
{
    unsigned int i = 0;
    unsigned int tag = 0;
    if(NULL == tag_array)
    {
        META_LOGE("%s: tag_array buffer is NULL!", __FUNCTION__);
        return;
    }

    /* add other section tags here. */
    for(tag = (unsigned int)ANDROID_HUAWEI_METADATA_START; tag < (unsigned int)ANDROID_HUAWEI_METADATA_END; tag++)
    {
        tag_array[i++] = tag;
    }
}

int get_section_index_offset_vendor(unsigned int tag, unsigned int* offset)
{
    unsigned int i = 0;
    unsigned int temp_offset = 0;
    unsigned int section_index = ((tag>>16)&0x0000ffff) - VENDOR_SECTION;

    if(section_index < ANDROID_HUAWEI_SECTION_MAX - VENDOR_SECTION)
    {
        for(i = 0; i < section_index; i++)
        {
            temp_offset += vendor_section_bounds[i][1] - vendor_section_bounds[i][0];
        }

        *offset = temp_offset;
        return 0;
    }

    META_LOGE("%s: invalid vendor tag, can't find section index offset!", __FUNCTION__);

    return -1;
}
/*lint +e732 +e774 +e785 +e845 +e715 +e818 +e705 +e717 +e734 +e835 +e713 +e838 +e826 +e737 +e701 +e801
+esym(732,*) +esym(774,*) +esym(785,*) +esym(845,*) +esym(715,*) +esym(818,*) +esym(705,*) +esym(717,*) +esym(734,*)
+esym(835,*) +esym(713,*) +esym(838,*) +esym(826,*) +esym(737,*) +esym(701,*) +esym(801,*)*/
/********************************** END **********************************************/

