

#ifndef __HW_KERNEL_HWCAM_HISP_CFG_BASE_H__
#define __HW_KERNEL_HWCAM_HISP_CFG_BASE_H__

#include <linux/ioctl.h>
#include <linux/types.h>
#include <linux/videodev2.h>
#include <media/huawei/camera.h>
#include <linux/compat.h>

enum {
	HISP_NAME_SIZE = 32,
	HISP_V4L2_EVENT_TYPE = V4L2_EVENT_PRIVATE_START + 0x00090000,

	HISP_HIGH_PRIO_EVENT = 0x1500,
	HISP_MIDDLE_PRIO_EVENT = 0x2000,
	HISP_LOW_PRIO_EVENT = 0x3000,
};

typedef enum _tag_hisp_event_kind {
	HISP_RPMSG_CB,
} hisp_event_kind_t;

typedef struct _tag_hisp_event {
	hisp_event_kind_t kind;
} hisp_event_t;

typedef struct addr_params
{
    uint32_t moduleAddr;
    uint32_t iova;
    uint32_t sharedFd;
    uint32_t type;
    uint32_t prot;
    uint32_t size;
}addr_param_t;

// enum hisi_isp_rproc_case_attr {
//     DEFAULT_CASE = 0,
//     SEC_CASE,
//     NONSEC_CASE,
//     INVAL_CASE,
// };

struct hisp_cfg_data {
	int cfgtype;
	int mode;
	int isSecure;
	addr_param_t param;
};

enum hisp_config_type {
	HISP_CONFIG_POWER_ON = 0,
	HISP_CONFIG_POWER_OFF,
    HISP_CONFIG_GET_MAP_ADDR,
    HISP_CONFIG_UNMAP_ADDR,
	HISP_CONFIG_MAX_INDEX
};

typedef struct _tag_hisp_info {
	char name[HISP_NAME_SIZE];
} hisp_info_t;


#define HISP_IOCTL_POWER_ON   _IO('A', BASE_VIDIOC_PRIVATE + 0x01)
#define HISP_IOCTL_POWER_OFF  _IO('A', BASE_VIDIOC_PRIVATE + 0x02)
#define HISP_IOCTL_GET_INFO   _IOR('A', BASE_VIDIOC_PRIVATE + 0x05, hisp_info_t)
#define HISP_IOCTL_CFG_ISP    _IOWR('A', BASE_VIDIOC_PRIVATE + 0x06, \
				struct hisp_cfg_data)

#endif /* __HW_KERNEL_HWCAM_HISP_CFG_BASE_H__ */
