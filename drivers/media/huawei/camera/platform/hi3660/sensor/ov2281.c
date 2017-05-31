


#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/rpmsg.h>

#include "hwsensor.h"
#include "sensor_commom.h"
#include "hw_csi.h"
#include "../pmic/hw_pmic.h"
//lint -save -e30 -e64 -e84 -e715 -e747 -e753 -e774 -e778 -e785 -e826
//lint -save -e838 -e846 -e866 -e514 -e52 -e528
#define I2S(i) container_of(i, sensor_t, intf)
#define CTL_RESET_HOLD    (0)
#define CTL_RESET_RELEASE (1)

static bool s_ov2281_power_on = false;

static struct sensor_power_setting ov2281_power_setting[] = {

	//SCAM1 AVDD 2.8V
	{
		.seq_type = SENSOR_AVDD,
		.data = (void*)"front-sensor-avdd",
		.config_val = LDO_VOLTAGE_V2P8V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//SCAM1 DVDD 1.2V
	{
		.seq_type = SENSOR_PMIC,
		.seq_val = VOUT_LDO_1,
		.config_val = LDO_VOLTAGE_1P2V,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 0,
	},

	//enable gpio51 output iovdd 1.8v
    {
        .seq_type = SENSOR_LDO_EN,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

	{
		.seq_type = SENSOR_MCLK,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},

	{
		.seq_type = SENSOR_RST,
		.config_val = SENSOR_GPIO_LOW,
		.sensor_index = SENSOR_INDEX_INVALID,
		.delay = 1,
	},
};


static char const*
ov2281_get_name(
        hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

static int
ov2281_power_up(
        hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;
    sensor = I2S(si);
    cam_info("enter %s. index = %d name = %s", __func__, sensor->board_info->sensor_index, sensor->board_info->name);
    if (hw_is_fpga_board()) {
        ret = do_sensor_power_on(sensor->board_info->sensor_index, sensor->board_info->name);
    } else {
        ret = hw_sensor_power_up(sensor);
    }
    if (0 == ret )
    {
        cam_info("%s. power up sensor success.", __func__);
    }
    else
    {
        cam_err("%s. power up sensor fail.", __func__);
    }
    return ret;
}

static int
ov2281_power_down( hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;
    sensor = I2S(si);
    cam_info("enter %s. index = %d name = %s", __func__, sensor->board_info->sensor_index, sensor->board_info->name);
    if (hw_is_fpga_board()) {
        ret = do_sensor_power_off(sensor->board_info->sensor_index, sensor->board_info->name);
    } else {
        ret = hw_sensor_power_down(sensor);
    }
    if (0 == ret )
    {
        cam_info("%s. power down sensor success.", __func__);
    }
    else
    {
        cam_err("%s. power down sensor fail.", __func__);
    }
    return ret;
}

static int ov2281_csi_enable(hwsensor_intf_t* si)
{
    return 0;
}

static int ov2281_csi_disable(hwsensor_intf_t* si)
{
    return 0;
}

static int
ov2281_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;

    cam_info("%s name:%s", __func__, sensor->board_info->name);

    strncpy(cdata->cfg.name, sensor->board_info->name, DEVICE_NAME_SIZE-1);
    cdata->data = sensor->board_info->sensor_index;

    return 0;
}
// to confirm
static int ov2281_do_hw_reset(hwsensor_intf_t* si, int ctl, int id)
{
    char *state = NULL;
    sensor_t* sensor = I2S(si);
    hwsensor_board_info_t *b_info = NULL;
    int ret = 0;

    b_info = sensor->board_info;
    if (NULL == b_info) {
        cam_warn("%s invalid sensor board info", __func__);
        return 0;
    }

    ret  = gpio_request(b_info->gpios[RESETB].gpio, "ov2281reset-0");
    if (ret) {
        cam_err("%s requeset reset pin failed", __func__);
        return ret;
    }

    if (ctl == CTL_RESET_HOLD) {
        state = "hold";
        ret  = gpio_direction_output(b_info->gpios[RESETB].gpio, 0);
    } else {
        state = "release";
        ret  = gpio_direction_output(b_info->gpios[RESETB].gpio, 1);
        udelay(2000);
    }
    gpio_free(b_info->gpios[RESETB].gpio);

    if (ret) {
        cam_err("%s set reset pin failed", __func__);
    } else {
        cam_info("%s: set reset state=%s", __func__, state);
    }
    return ret;
}

static int
ov2281_config(
        hwsensor_intf_t* si,
        void  *argp)
{
    struct sensor_cfg_data *data;

    int ret =0;
    data = (struct sensor_cfg_data *)argp;
    cam_debug("ov2281 cfgtype = %d",data->cfgtype);
    switch(data->cfgtype){
        case SEN_CONFIG_POWER_ON:
            if (!s_ov2281_power_on) {
				cam_info("enter power on branch %s",__func__);
                ret = si->vtbl->power_up(si);
                s_ov2281_power_on = true;
            }
            break;
        case SEN_CONFIG_POWER_OFF:
            if (s_ov2281_power_on) {
                ret = si->vtbl->power_down(si);
                s_ov2281_power_on = false;
            }
            break;
        case SEN_CONFIG_WRITE_REG:
            break;
        case SEN_CONFIG_READ_REG:
            break;
        case SEN_CONFIG_WRITE_REG_SETTINGS:
            break;
        case SEN_CONFIG_READ_REG_SETTINGS:
            break;
        case SEN_CONFIG_ENABLE_CSI:
            break;
        case SEN_CONFIG_DISABLE_CSI:
            break;
        case SEN_CONFIG_MATCH_ID:
            ret = si->vtbl->match_id(si,argp);
            break;
        case SEN_CONFIG_RESET_HOLD:
            ret = ov2281_do_hw_reset(si, CTL_RESET_HOLD, data->mode);
            break;
        case SEN_CONFIG_RESET_RELEASE:
            ret = ov2281_do_hw_reset(si, CTL_RESET_RELEASE, data->mode);
            break;
        default:
            cam_err("%s cfgtype(%d) is error", __func__, data->cfgtype);
            break;
    }
    return ret;
}


static hwsensor_vtbl_t s_ov2281_vtbl =
{
    .get_name = ov2281_get_name,
    .config = ov2281_config,
    .power_up = ov2281_power_up,
    .power_down = ov2281_power_down,
    .match_id = ov2281_match_id,
    .csi_enable = ov2281_csi_enable,
    .csi_disable = ov2281_csi_disable,
};


/* individual driver data for each device */
atomic_t volatile ov2281_powered = ATOMIC_INIT(0);
static sensor_t s_ov2281 =
{
    .intf = { .vtbl = &s_ov2281_vtbl, },//common intf
    .power_setting_array = {
        .size = ARRAY_SIZE(ov2281_power_setting),
        .power_setting = ov2281_power_setting,
     },
     .p_atpowercnt = &ov2281_powered,
};

static const struct of_device_id
s_ov2281_dt_match[] =
{
    {
        .compatible = "huawei,ov2281",
        .data = &s_ov2281.intf,
    },
    { } /* terminate list */
};

MODULE_DEVICE_TABLE(of, s_ov2281_dt_match);


/* platform driver struct */
static int32_t ov2281_platform_probe(struct platform_device* pdev);
static int32_t ov2281_platform_remove(struct platform_device* pdev);
static struct platform_driver
s_ov2281_driver =
{
    .probe = ov2281_platform_probe,
    .remove = ov2281_platform_remove,
    .driver =
    {
        .name = "huawei,ov2281",
        .owner = THIS_MODULE,
        .of_match_table = s_ov2281_dt_match,
    },
};


static int32_t
ov2281_platform_probe(
        struct platform_device* pdev)
{
    int rc = 0;
    struct device_node *np = pdev->dev.of_node;
    const struct of_device_id *id;
    hwsensor_intf_t *intf;
    sensor_t *sensor;

    cam_info("enter %s",__func__);

    if (!np) {
        cam_err("%s of_node is NULL", __func__);
        return -ENODEV;
    }

    id = of_match_node(s_ov2281_dt_match, np);
    if (!id) {
        cam_err("%s none id matched", __func__);
        return -ENODEV;
    }

    intf = (hwsensor_intf_t*)id->data;
    sensor = I2S(intf);

    cam_info("zpc to get dt data :%s",__func__);
    rc = hw_sensor_get_dt_data(pdev, sensor);
    if (rc < 0) {
        cam_err("%s no dt data", __func__);
        return -ENODEV;
    }
    sensor->dev = &pdev->dev;

    rc = hwsensor_register(pdev, intf);
    rc = rpmsg_sensor_register(pdev, (void*)sensor);

    return rc;
}


static int32_t
ov2281_platform_remove(
    struct platform_device * pdev)
{
    struct device_node *np = pdev->dev.of_node;
    const struct of_device_id *id;
    hwsensor_intf_t *intf;
    sensor_t *sensor;

    cam_info("enter %s",__func__);

    if (!np) {
        cam_info("%s of_node is NULL", __func__);
        return 0;
    }
    /* don't use dev->p->driver_data
     * we need to search again */
    id = of_match_node(s_ov2281_dt_match, np);
    if (!id) {
        cam_info("%s none id matched", __func__);
        return 0;
    }

    intf = (hwsensor_intf_t*)id->data;
    sensor = I2S(intf);

    rpmsg_sensor_unregister((void*)&sensor);
    hwsensor_unregister(intf);
    return 0;
}


/* module declare */
static int __init
ov2281_init_module(void)
{
    cam_notice("enter %s",__func__);
    return platform_driver_probe(&s_ov2281_driver,
            ov2281_platform_probe);
}

static void __exit
ov2281_exit_module(void)
{
    cam_info("enter %s",__func__);
    platform_driver_unregister(&s_ov2281_driver);
}

module_init(ov2281_init_module);
module_exit(ov2281_exit_module);
MODULE_DESCRIPTION("ov2281");
MODULE_LICENSE("GPL v2");
