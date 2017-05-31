

//lint -save -e7
#include <linux/compiler.h>
#include <linux/gpio.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of.h>
#include <linux/platform_device.h>
#include <linux/sched.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <media/v4l2-subdev.h>
#include <media/huawei/hjpeg_cfg.h>

#include "hjpeg_intf.h"
#include "hwcam_intf.h"
#include "cam_log.h"

typedef struct _tag_hjpeg
{
    struct v4l2_subdev                          subdev;
    struct platform_device*                     pdev;


    struct mutex                                lock;
    hjpeg_intf_t*                               intf;

} hjpeg_t;

#define SD2Hjpeg(sd) container_of(sd, hjpeg_t, subdev)
#define I2Hjpeg(jpeg_intf) container_of(jpeg_intf, hjpeg_t, intf)

static long
hjpeg_vo_subdev_ioctl(struct v4l2_subdev *sd, unsigned int cmd, void *arg)
{
    long rc = -EINVAL;
    hjpeg_t* hjpeg = NULL;

    hjpeg = SD2Hjpeg(sd);

    switch (cmd) {
        case HJPEG_ENCODE_PROCESS:
            rc = hjpeg->intf->vtbl->encode_process(hjpeg->intf, arg);
            break;
        case HJPEG_ENCODE_POWERON:
            rc = hjpeg->intf->vtbl->power_on(hjpeg->intf);
            break;
        case HJPEG_ENCODE_POWERDOWN:
            rc = hjpeg->intf->vtbl->power_down(hjpeg->intf);
            break;
        case HJPEG_ENCODE_SETREG:
            rc = hjpeg->intf->vtbl->set_reg(hjpeg->intf, arg);
            break;
        case HJPEG_ENCODE_GETREG:
            rc = hjpeg->intf->vtbl->get_reg(hjpeg->intf, arg);
            break;
        default:
            cam_info("%s: invalid ioctl cmd for hjpeg!!!cmd is %d\n", __func__, cmd);
            break;
    }
    return rc;
}

static int
hjpeg_vo_power(
        struct v4l2_subdev* sd,
        int on)
{
    return 0;
}


static int hjpeg_subdev_open(
        struct v4l2_subdev *sd,
        struct v4l2_subdev_fh *fh)
{
    cam_info("%s hjpeg_sbudev open! \n",__func__);
    return 0;
}

static int
hjpeg_subdev_close(
        struct v4l2_subdev *sd,
        struct v4l2_subdev_fh *fh)
{
    cam_info("%s hjpeg_sbudev close! \n", __func__);
    return 0;
}

static struct v4l2_subdev_internal_ops
s_subdev_internal_ops_hjpeg =
{
    .open = hjpeg_subdev_open,
    .close = hjpeg_subdev_close,
};


static struct v4l2_subdev_core_ops
s_subdev_core_ops_hjpeg =
{
    .ioctl = hjpeg_vo_subdev_ioctl,
    .s_power = hjpeg_vo_power,
};

static struct v4l2_subdev_ops
s_subdev_ops_hjpeg =
{
    .core = &s_subdev_core_ops_hjpeg,
};


int
hjpeg_register(
        struct platform_device* pdev,
        hjpeg_intf_t* si)
{
    int rc = 0;

    struct v4l2_subdev* subdev = NULL;
    hjpeg_t* jpeg = (hjpeg_t*)kzalloc(
            sizeof(hjpeg_t), GFP_KERNEL);

    if (jpeg == NULL) {
        rc = -ENOMEM;
        goto register_fail;
    }

    subdev = &jpeg->subdev;
    mutex_init(&jpeg->lock);

    v4l2_subdev_init(subdev, &s_subdev_ops_hjpeg);
    subdev->internal_ops = &s_subdev_internal_ops_hjpeg;
    snprintf(subdev->name, sizeof(subdev->name),
            "%s", "hwcam-cfg-jpeg");
    subdev->flags |= V4L2_SUBDEV_FL_HAS_DEVNODE;
    v4l2_set_subdevdata(subdev, pdev);

    media_entity_init(&subdev->entity, 0, NULL, 0);
    subdev->entity.type = MEDIA_ENT_T_V4L2_SUBDEV;
    subdev->entity.group_id = HWCAM_SUBDEV_HJPEG;
    subdev->entity.name = subdev->name;

    hwcam_cfgdev_register_subdev(subdev);
    subdev->devnode->lock = &jpeg->lock;

    jpeg->intf = si;
    jpeg->pdev = pdev;


register_fail:
    return rc;
}

void
hjpeg_unregister(hjpeg_intf_t* si)
{
    struct v4l2_subdev* subdev = NULL;
    hjpeg_t* jpeg = NULL;
    jpeg =  I2Hjpeg(si);

    subdev = &jpeg->subdev;
    media_entity_cleanup(&subdev->entity);
    hwcam_cfgdev_unregister_subdev(subdev);

    kzfree(jpeg);
}
//lint -restore