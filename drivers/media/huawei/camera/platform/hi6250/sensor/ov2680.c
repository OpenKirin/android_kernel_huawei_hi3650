 

#include <linux/module.h>
#include <linux/printk.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/platform_device.h>
#include <linux/rpmsg.h>

#include "hwsensor.h"
#include "sensor_commom.h"
#include "hw_csi.h"

#define I2S(i) container_of(i, sensor_t, intf)

static hwsensor_vtbl_t s_ov2680_vtbl;
static bool power_on_status = false;//false: power off, true:power on

int ov2680_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting ov2680_power_up_setting[] = {

    //MCAM1 IOVDD 1.80V
    {
        .seq_type = SENSOR_IOVDD,
        .data = (void*)"main-sensor-iovdd",
        .config_val = LDO_VOLTAGE_1P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
	
    //MCAM1 AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD,
        .data = (void*)"main-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //SCAM AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD2,
        .data = (void*)"slave-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    {
        .seq_type = SENSOR_PWDN2,
        .config_val = SENSOR_GPIO_HIGH,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    {
        .seq_type = SENSOR_RST3,
        .config_val = SENSOR_GPIO_HIGH,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
	
    {
        .seq_type = SENSOR_MIPI_SW,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    {
        .seq_type = SENSOR_MCLK,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
};
struct sensor_power_setting ov2680_power_down_setting[] = {
    {
        .seq_type = SENSOR_MCLK,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    {
        .seq_type = SENSOR_MIPI_SW,
        .config_val = SENSOR_GPIO_HIGH,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    {
        .seq_type = SENSOR_RST3,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    {
        .seq_type = SENSOR_PWDN2,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    //SCAM AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD2,
        .data = (void*)"slave-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },
    //MCAM1 AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD,
        .data = (void*)"main-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },
    //MCAM1 IOVDD 1.80V
    {
        .seq_type = SENSOR_IOVDD,
        .data = (void*)"main-sensor-iovdd",
        .config_val = LDO_VOLTAGE_1P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
};

atomic_t volatile ov2680_powered = ATOMIC_INIT(0);
static sensor_t s_ov2680 =
{
    .intf = { .vtbl = &s_ov2680_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(ov2680_power_up_setting),
            .power_setting = ov2680_power_up_setting,
     },
    .power_down_setting_array = {
            .size = ARRAY_SIZE(ov2680_power_down_setting),
            .power_setting = ov2680_power_down_setting,
    },

    .p_atpowercnt = &ov2680_powered,
};

static const struct of_device_id s_ov2680_dt_match[] =
{
    {
        .compatible = "huawei,ov2680",
        .data = &s_ov2680.intf,
    },
    {
    },
};

MODULE_DEVICE_TABLE(of, s_ov2680_dt_match);

static struct platform_driver s_ov2680_driver =
{
    .driver =
    {
        .name = "huawei,ov2680",
        .owner = THIS_MODULE,
        .of_match_table = s_ov2680_dt_match,
    },
};

char const* ov2680_get_name(hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int ov2680_power_up(hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;
    sensor = I2S(si);
    cam_info("enter %s. index = %d name = %s", __func__, sensor->board_info->sensor_index, sensor->board_info->name);

    ret = hw_sensor_power_up_config(s_ov2680.dev, sensor->board_info);
    if (0 == ret ){
        cam_info("%s. power up config success.", __func__);
    }else{
        cam_err("%s. power up config fail.", __func__);
        return ret;
    }
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

int
ov2680_power_down(
        hwsensor_intf_t* si)
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
    hw_sensor_power_down_config(sensor->board_info);
    return ret;
}

int ov2680_csi_enable(hwsensor_intf_t* si)
{
    return 0;
}

int ov2680_csi_disable(hwsensor_intf_t* si)
{
    return 0;
}

static int ov2680_match_id(
        hwsensor_intf_t* si, void * data)
{
    sensor_t* sensor = I2S(si);
    struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;

    cam_info("%s enter.", __func__);

    cdata->data = sensor->board_info->sensor_index;

    hwsensor_writefile(sensor->board_info->sensor_index, sensor->board_info->name);
    return 0;
}

static hwsensor_vtbl_t s_ov2680_vtbl =
{
    .get_name = ov2680_get_name,
    .config = ov2680_config,
    .power_up = ov2680_power_up,
    .power_down = ov2680_power_down,
    .match_id = ov2680_match_id,
    .csi_enable = ov2680_csi_enable,
    .csi_disable = ov2680_csi_disable,
};

int ov2680_config(hwsensor_intf_t* si, void  *argp)
{
    struct sensor_cfg_data *data;

    int ret =0;

	if (NULL == si || NULL == argp){
		cam_err("%s : si or argp is null", __func__);
		return -1;
	}

    data = (struct sensor_cfg_data *)argp;
    cam_debug("ov2680 cfgtype = %d",data->cfgtype);
    switch(data->cfgtype){
        case SEN_CONFIG_POWER_ON:
            if(false == power_on_status){
            ret = si->vtbl->power_up(si);
                power_on_status = true;
            }
            break;
        case SEN_CONFIG_POWER_OFF:
            if(true == power_on_status){
            ret = si->vtbl->power_down(si);
                power_on_status = false;
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
            //ret = si->vtbl->csi_enable(si);
            break;
        case SEN_CONFIG_DISABLE_CSI:
            //ret = si->vtbl->csi_disable(si);
            break;
        case SEN_CONFIG_MATCH_ID:
            ret = si->vtbl->match_id(si,argp);
            break;
        case SEN_CONFIG_RESET_HOLD:
            cam_warn("%s cfgtype(%d) does not support", __func__, data->cfgtype);
            break;
        case SEN_CONFIG_RESET_RELEASE:
            cam_warn("%s cfgtype(%d) does not support", __func__, data->cfgtype);
            break;
        default:
            cam_err("%s cfgtype(%d) is error", __func__, data->cfgtype);
            break;
    }

    return ret;
}

static int32_t ov2680_platform_probe(struct platform_device* pdev)
{
    int rc = 0;
    cam_notice("enter %s",__func__);

    if (pdev->dev.of_node) {
        rc = hw_sensor_get_dt_data(pdev, &s_ov2680);
        if (rc < 0) {
            cam_err("%s failed line %d\n", __func__, __LINE__);
            goto ov2680_sensor_probe_fail;

		/*CASE 1.2v dvdd, revew;CASE 1.05v use default; Other cases need add*/
		}
    } else {
        cam_err("%s ov2680 of_node is NULL.\n", __func__);
        goto ov2680_sensor_probe_fail;
    }
    s_ov2680.dev = &pdev->dev;
    rc = hwsensor_register(pdev, &s_ov2680.intf);
    rc = rpmsg_sensor_register(pdev, (void*)&s_ov2680);
ov2680_sensor_probe_fail:
    return rc;
}

static int __init ov2680_init_module(void)
{
    cam_info("Enter: %s", __func__);
    return platform_driver_probe(&s_ov2680_driver,
            ov2680_platform_probe);
}

static void __exit ov2680_exit_module(void)
{
    hwsensor_unregister(&s_ov2680.intf);
    platform_driver_unregister(&s_ov2680_driver);
}

module_init(ov2680_init_module);
module_exit(ov2680_exit_module);
MODULE_DESCRIPTION("ov2680");
MODULE_LICENSE("GPL v2");

