


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

//lint -save -e846 -e514 -e866 -e30 -e84 -e785 -e64 -e826 -e838 -e715 -e747 -e778 -e774 -e732 -e650 -e31 -e731 -e528 -e753 -e737

static char *sensor_dts_name = "IMX386E3_VENDOR";

extern struct hw_csi_pad hw_csi_pad;
static hwsensor_vtbl_t s_imx386E3_vtbl;

static bool power_on_status = false;//false: power off, true:power on
int imx386E3_config(hwsensor_intf_t* si, void  *argp);

struct sensor_power_setting hw_imx386E3_power_up_setting[] = {

    //disable sec camera reset
    {
        .seq_type = SENSOR_SUSPEND,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //SCAM AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD,
        .data = (void*)"slave-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },

    //SCAM DVDD1.2V
    {
        .seq_type = SENSOR_DVDD,
        .config_val = LDO_VOLTAGE_1P2V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

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
        .seq_type = SENSOR_AVDD2,
        .data = (void*)"main-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },
    
    //MCAM1 DVDD 1.2V
    {
        .seq_type = SENSOR_DVDD2,
        .config_val = LDO_VOLTAGE_1P1V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 AFVDD 2.85V
    {
        .seq_type = SENSOR_VCM_AVDD,
        .data = (void*)"cameravcm-vcc",
        .config_val = LDO_VOLTAGE_V2P85V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 VCM PD Enable
    {
        .seq_type = SENSOR_VCM_PWDN,
        .config_val = SENSOR_GPIO_HIGH,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    {
        .seq_type = SENSOR_MCLK,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    {
        .seq_type = SENSOR_RST,
        .config_val = SENSOR_GPIO_HIGH,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
};
struct sensor_power_setting hw_imx386E3_power_down_setting[] = {
    {
        .seq_type = SENSOR_RST,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    {
        .seq_type = SENSOR_MCLK,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 VCM Enable
    {
        .seq_type = SENSOR_VCM_PWDN,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },

    //MCAM1 AFVDD 2.85V
    {
        .seq_type = SENSOR_VCM_AVDD,
        .data = (void*)"cameravcm-vcc",
        .config_val = LDO_VOLTAGE_V2P85V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    //MCAM1 DVDD 1.2V
    {
        .seq_type = SENSOR_DVDD2,
        .config_val = LDO_VOLTAGE_1P1V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    //MCAM1 AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD2,
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
    //SCAM DVDD1.2V
    {
        .seq_type = SENSOR_DVDD,
        .config_val = LDO_VOLTAGE_1P2V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 1,
    },
    //SCAM AVDD 2.80V
    {
        .seq_type = SENSOR_AVDD,
        .data = (void*)"slave-sensor-avdd",
        .config_val = LDO_VOLTAGE_V2P8V,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },
    //disable sec camera reset
    {
        .seq_type = SENSOR_SUSPEND,
        .config_val = SENSOR_GPIO_LOW,
        .sensor_index = SENSOR_INDEX_INVALID,
        .delay = 0,
    },
};

atomic_t volatile imx386E3_powered = ATOMIC_INIT(0);
static sensor_t s_imx386E3 =
{
    .intf = { .vtbl = &s_imx386E3_vtbl, },
    .power_setting_array = {
            .size = ARRAY_SIZE(hw_imx386E3_power_up_setting),
            .power_setting = hw_imx386E3_power_up_setting,
     },
    .power_down_setting_array = {
            .size = ARRAY_SIZE(hw_imx386E3_power_down_setting),
            .power_setting = hw_imx386E3_power_down_setting,
    },
     .p_atpowercnt = &imx386E3_powered,
};

static const struct of_device_id
s_imx386E3_dt_match[] =
{
    {
        .compatible = "huawei,imx386E3",
        .data = &s_imx386E3.intf,
    },
    {
    },
};

MODULE_DEVICE_TABLE(of, s_imx386E3_dt_match);

static struct platform_driver
s_imx386E3_driver =
{
    .driver =
    {
        .name = "huawei,imx386E3",
        .owner = THIS_MODULE,
        .of_match_table = s_imx386E3_dt_match,
    },
};

char const* imx386E3_get_name(hwsensor_intf_t* si)
{
    sensor_t* sensor = I2S(si);
    return sensor->board_info->name;
}

int imx386E3_power_up(hwsensor_intf_t* si)
{
    int ret = 0;
    sensor_t* sensor = NULL;
    sensor = I2S(si);
    cam_info("enter %s. index = %d name = %s", __func__, sensor->board_info->sensor_index, sensor->board_info->name);
    ret = hw_sensor_power_up_config(s_imx386E3.dev, sensor->board_info);
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

int imx386E3_power_down(hwsensor_intf_t* si)
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

int imx386E3_csi_enable(hwsensor_intf_t* si)
{
    return 0;
}

int imx386E3_csi_disable(hwsensor_intf_t* si)
{
    return 0;
}

static int
imx386E3_match_id(
        hwsensor_intf_t* si, void * data)
{
	sensor_t* sensor = I2S(si);
	struct sensor_cfg_data *cdata = (struct sensor_cfg_data *)data;
	uint32_t module_id_0 = 0;
	uint32_t module_id_1 = 0;
	struct pinctrl_state *pinctrl_def;
	struct pinctrl_state *pinctrl_idle;
	struct pinctrl *p;
	char *sensor_name [] = {"IMX386E3_OFILM", "IMX386E3_SUNNY"};
	int rc = 0;

	memset(cdata->cfg.name, 0, DEVICE_NAME_SIZE);
	if (!strncmp(sensor->board_info->name, sensor_dts_name, strlen(sensor_dts_name))) {
	    p = devm_pinctrl_get(s_imx386E3.dev);
	    if (IS_ERR_OR_NULL(p)) {
	        cam_err("could not get pinctrl.\n");
	        rc = -1;
	        goto matchID_exit;
	    }

	    rc = gpio_request(sensor->board_info->gpios[FSIN].gpio, NULL);
	    if(rc < 0) {
	        cam_err("%s failed to request gpio[%d]", __func__, sensor->board_info->gpios[FSIN].gpio);
	        rc = -1;
	        goto matchID_exit;
	    }
	    cam_info("%s gpio[%d].", __func__, sensor->board_info->gpios[FSIN].gpio);

	    pinctrl_def = pinctrl_lookup_state(p, "default");
	    if (IS_ERR_OR_NULL(pinctrl_def)) {
	        cam_err("could not get defstate.\n");
	        rc = -1;
	        goto pinctrl_error;
	    }

	    pinctrl_idle = pinctrl_lookup_state(p, "idle");
	    if (IS_ERR_OR_NULL(pinctrl_idle)) {
	        pr_err("could not get idle defstate.\n");
	        rc = -1;
	        goto pinctrl_error;
	    }
	    /*PULL UP*/
	    rc = pinctrl_select_state(p, pinctrl_def);
	    if (rc) {
	        cam_err("could not set pins to default state.\n");
	        rc = -1;
	        goto pinctrl_error;
	    }
	    udelay(10);
	    cam_info("%s gpio[%d].", __func__, sensor->board_info->gpios[FSIN].gpio);
	    rc = gpio_direction_input(sensor->board_info->gpios[FSIN].gpio);
	    if (rc < 0) {
	        cam_err("%s failed to config gpio(%d) input.\n",__func__, sensor->board_info->gpios[FSIN].gpio);
	        rc = -1;
	        goto pinctrl_error;
	    }

	    module_id_1 = gpio_get_value(sensor->board_info->gpios[FSIN].gpio);

	    /*PULL DOWN*/
	    rc = pinctrl_select_state(p, pinctrl_idle);
	    if (rc) {
	    cam_err("could not set pins to idle state.\n");
	    rc = -1;
	    goto pinctrl_error;
	    }
	    udelay(10);
	    cam_info("%s gpio[%d].", __func__, sensor->board_info->gpios[FSIN].gpio);
	    rc = gpio_direction_input(sensor->board_info->gpios[FSIN].gpio);
	    if (rc < 0) {
	    cam_err("%s failed to config gpio(%d) input.\n",__func__, sensor->board_info->gpios[FSIN].gpio);
	    rc = -1;
	    goto pinctrl_error;
	    }
	    module_id_0 = gpio_get_value(sensor->board_info->gpios[FSIN].gpio);

	    cam_info("%s module_id_0 %d module_id_1 %d .\n",__func__, module_id_0, module_id_1);
	    if((module_id_0 == 0) && (module_id_1 == 0)){//ofilm module
	        strncpy(cdata->cfg.name, sensor_name[0], strlen(sensor_name[0])+1);
	        cdata->data = sensor->board_info->sensor_index;
	        rc = 0;
	    }
	    else if((module_id_0 == 1) && (module_id_1 == 1)){//v1&v2 foxconn module & final sunny module
	        strncpy(cdata->cfg.name, sensor_name[1], strlen(sensor_name[1])+1);
	        cdata->data = sensor->board_info->sensor_index;
	        rc = 0;
	    }else{//23060227 NO SUCH MODULE
	        strncpy(cdata->cfg.name, sensor->board_info->name, strlen(sensor->board_info->name)+1);
	        cdata->data = sensor->board_info->sensor_index;
	        cam_err("%s failed to get the module id value.\n",__func__);
	        rc = 0;
	    }

	    gpio_free(sensor->board_info->gpios[FSIN].gpio);
	    goto matchID_exit;
	    } else {
	        strncpy(cdata->cfg.name, sensor->board_info->name, strlen(sensor->board_info->name)+1);
	        cdata->data = sensor->board_info->sensor_index;
	        rc = 0;
	        goto matchID_exit;
	    }

pinctrl_error:
	    gpio_free(sensor->board_info->gpios[FSIN].gpio);
matchID_exit:
	    if (cdata->data != SENSOR_INDEX_INVALID) {
	        hwsensor_writefile(sensor->board_info->sensor_index, cdata->cfg.name);
	        cam_info("%s, cdata->cfg.name = %s", __func__,cdata->cfg.name );
	    }

    return rc;
}

#if 0
static ssize_t imx386E3_powerctrl_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;
        cam_info("enter %s", __func__);

        return rc;
}
static ssize_t imx386E3_powerctrl_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	int state = simple_strtol(buf, NULL, 10);
	cam_info("enter %s, state %d", __func__, state);

	if (state == POWER_ON)
		imx386E3_power_up(&s_imx386E3.intf);
	else
		imx386E3_power_down(&s_imx386E3.intf);

	return count;
}


static struct device_attribute imx386E3_powerctrl =
    __ATTR(power_ctrl, 0664, imx386E3_powerctrl_show, imx386E3_powerctrl_store);

int imx386E3_register_attribute(hwsensor_intf_t* intf, struct device* dev)
{
	int ret = 0;
	cam_info("enter %s", __func__);

	ret = device_create_file(dev, &imx386E3_powerctrl);
	if (ret < 0) {
		cam_err("%s failed to creat power ctrl attribute.", __func__);
		goto err_create_power_ctrl;
	}
	return 0;
err_create_power_ctrl:
	device_remove_file(dev, &imx386E3_powerctrl);
	return ret;
}
#endif

static hwsensor_vtbl_t
s_imx386E3_vtbl =
{
	.get_name = imx386E3_get_name,
	.config = imx386E3_config,
	.power_up = imx386E3_power_up,
	.power_down = imx386E3_power_down,
	.match_id = imx386E3_match_id,
	.csi_enable = imx386E3_csi_enable,
	.csi_disable = imx386E3_csi_disable,
	/*.sensor_register_attribute = imx386E3_register_attribute,*/
};

int
imx386E3_config(
        hwsensor_intf_t* si,
        void  *argp)
{
	struct sensor_cfg_data *data;

	int ret =0;

	if (NULL == si || NULL == argp){
		cam_err("%s : si or argp is null", __func__);
		return -1;
	}

	data = (struct sensor_cfg_data *)argp;
	cam_debug("imx386E3 cfgtype = %d",data->cfgtype);
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
			break;
		case SEN_CONFIG_DISABLE_CSI:
			break;
		case SEN_CONFIG_MATCH_ID:
			ret = si->vtbl->match_id(si,argp);
			break;
		default:
			cam_err("%s cfgtype(%d) is error", __func__, data->cfgtype);
			break;
	}
	return ret;
}

static int32_t
imx386E3_platform_probe(
        struct platform_device* pdev)
{
	int rc = 0;
	cam_notice("enter %s",__func__);
	if (pdev->dev.of_node) {
		rc = hw_sensor_get_dt_data(pdev, &s_imx386E3);
		if (rc < 0) {
			cam_err("%s failed line %d\n", __func__, __LINE__);
			goto imx386E3_sensor_probe_fail;
		}
	} else {
		cam_err("%s imx386E3 of_node is NULL.\n", __func__);
		goto imx386E3_sensor_probe_fail;
	}

    s_imx386E3.dev = &pdev->dev;

	rc = hwsensor_register(pdev, &s_imx386E3.intf);
	rc = rpmsg_sensor_register(pdev, (void*)&s_imx386E3);

imx386E3_sensor_probe_fail:
	return rc;
}

static int __init
imx386E3_init_module(void)
{
    cam_notice("enter %s",__func__);
    return platform_driver_probe(&s_imx386E3_driver,
            imx386E3_platform_probe);
}

static void __exit
imx386E3_exit_module(void)
{
    rpmsg_sensor_unregister((void*)&s_imx386E3);
    hwsensor_unregister(&s_imx386E3.intf);
    platform_driver_unregister(&s_imx386E3_driver);
}
//lint -restore

/*lint -e528 -esym(528,*)*/
module_init(imx386E3_init_module);
module_exit(imx386E3_exit_module);
/*lint -e528 +esym(528,*)*/
/*lint -e753 -esym(753,*)*/
MODULE_DESCRIPTION("imx386E3");
MODULE_LICENSE("GPL v2");
/*lint -e753 +esym(753,*)*/
