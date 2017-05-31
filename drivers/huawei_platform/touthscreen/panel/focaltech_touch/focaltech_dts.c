/*
 *
 * focaltech touchscreen driver.
 * 
 * copyright (c) 2010-2016, focaltech systems, ltd., all rights reserved.
 *
 * this software is licensed under the terms of the gnu general public
 * license version 2, as published by the free software foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * this program is distributed in the hope that it will be useful,
 * but without any warranty; without even the implied warranty of
 * merchantability or fitness for a particular purpose.  see the
 * gnu general public license for more details.
 *
 */

/************************************************************************
*
* file name: focaltech_test_dt.c
*
*  author: xu yf & zr, software department, focaltech
*
* created: 2016-06-06
*
* modified:
*
*  abstract:
*
*for device tree (dt)
*
*
* reference:
*
************************************************************************/

/*******************************************************************************
* included header files
*******************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/debugfs.h>
#include <asm/uaccess.h>
#include <linux/of.h>

#include <linux/i2c.h>
#include <linux/delay.h>

#include "focaltech_test.h"
#include "focaltech_core.h"
#include "focaltech_dts.h"
#include "focaltech_flash.h"


#define FOCALTECH_TEST_DT_INFO  "File Version of  focaltech_test_dt.c:  V1.1.0 2016-06-06"

struct device_node *g_m_dt_np = NULL;

extern struct fts_upgrade_delay_time fts_upgrade_delay;

/**
 * fts_test_dt_find_property - find device node from a property.
 *
 * @propname:	name of the property to be searched.
 *
 * search for a property in a device node and read 32-bit value(s) from
 * it. returns (0 or value length) on success, -einval if the property does not exist,
 * -enodata if property does not have a value, and -eoverflow if the
 * property data isn't large enough.
 *
 * the out_value is modified only if a valid u32 value can be decoded.
 */
int fts_test_dt_find_property(const char *propname) {
#ifdef CONFIG_OF
    struct property *prop = NULL;

    if (NULL == g_m_dt_np) {
        TS_LOG_ERR("device_node is NULL.");
        return -EIO;
    }

    prop = of_find_property(g_m_dt_np, propname, NULL);
    if (!prop) return -EINVAL;
    if (!prop->value) return -ENODATA;

    return ERROR_CODE_OK/*prop->length*/;
#else

    return -EIO;
#endif
}

int fts_test_dt_read_string(const char *propname, u8 *out_value) {
#ifdef CONFIG_OF
    int rc = 0;

    if (NULL == g_m_dt_np) {
        TS_LOG_ERR("device_node is NULL.");
        return -EIO;
    }

    rc = of_property_read_string(g_m_dt_np, propname, (const char **)&out_value);
    if (rc) {
        TS_LOG_ERR("unable to read of_property:%s.", propname);
        return -EIO;
    }
    else {
        TS_LOG_INFO("[FTS] get %s is %s.\n", propname, out_value);
    }

    return ERROR_CODE_OK;
#else

    return -EIO;
#endif
}


int fts_test_dt_read_u32(const char *propname, u32 *out_value) {
#ifdef CONFIG_OF
    int rc = 0;
    u32 tmp_value = 0;

    if (NULL == g_m_dt_np) {
        TS_LOG_ERR("device_node is NULL.");
        return -EIO;
    }
    rc = of_property_read_u32(g_m_dt_np, propname, &tmp_value);
    if (rc) {
        TS_LOG_ERR("unable to read of_property:%s.", propname);
        return -EIO;
    }
    else{
        *out_value = tmp_value;
        TS_LOG_INFO("[FTS] get %s is %d.\n", propname, *out_value);
    }

    return ERROR_CODE_OK;

#else

    return -EIO;
#endif
}

int fts_test_dt_read_u32_array(const char *propname, u32 *out_value) {
#ifdef CONFIG_OF
    int rc = 0;
    struct property *prop;
    u32 size = 0;
    int i = 0;

    if (NULL == g_m_dt_np) {
        TS_LOG_ERR("device_node is NULL.");
        return -EIO;
    }
    prop = of_find_property(g_m_dt_np, propname, NULL);
    if (prop) {
        size = prop->length / sizeof(u32);
      
        rc = of_property_read_u32_array(g_m_dt_np, propname, out_value, size);
        if (rc) {
            TS_LOG_INFO("unable to read of_property:%s.", propname);
            return -EIO;
        }
        else{            
            TS_LOG_INFO("[FTS] get %s is ", propname);
            for(i=0; i<size; i++){
                TS_LOG_INFO("%d ", out_value[i]);
            }
            TS_LOG_INFO("\n\n");
        }
    }

    return size;

#else

    return -EIO;
#endif
}
int fts_dt_init(struct i2c_client *client) {
    TS_LOG_ERR("[focal] %s ",  FOCALTECH_TEST_DT_INFO);

    return ERROR_CODE_OK;
}

int fts_dt_exit(struct i2c_client *client) {

    g_m_dt_np = NULL;

    return ERROR_CODE_OK;
}

void fts_test_dt_init_device_node(struct device_node *device)
{
#ifdef CONFIG_OF
    g_m_dt_np = device;
#else
    g_m_dt_np = NULL;
#endif
}

int fts_create_vendor_compatible_name(
	const char *project_id,
	char *compatible_name,
	size_t size)
{
	int ret = 0;
	ret = snprintf(compatible_name, size, "%s-%s",
		FTS_CHIP_NAME, project_id);
	if (ret >= size) {
		TS_LOG_INFO("%s:compatible_name out of range, ret=%d\n",
			__func__, ret);
		return -EINVAL;
	}

	return 0;
}

int fts_get_vendor_name_from_dts(
	const char *project_id,
	char *vendor_name,
	size_t size)
{
	int ret = 0;
	char *producer = NULL;
	char compatible_name[FTS_COMPATIBLE_NAME_LEN] = {0};

	struct device_node *vendor_node = NULL;

	ret = fts_create_vendor_compatible_name(project_id,
		compatible_name, FTS_COMPATIBLE_NAME_LEN);
	if (ret) {
		TS_LOG_ERR("%s:create vendor compatible name fail, ret=%d\n",
			__func__, ret);
		return -EINVAL;
	}
	
	TS_LOG_INFO("%s:compatible_name is: %s\n", __func__, compatible_name);
	vendor_node = of_find_compatible_node(NULL, NULL, compatible_name);
	if (!vendor_node) {
		TS_LOG_INFO("%s:find vendor node fail\n", __func__);
		return -ENODEV;
	}

	ret = of_property_read_string(vendor_node, "producer", &producer);
	if (!ret) {
		strncpy(vendor_name, producer, size);
	} else {
		TS_LOG_ERR("%s:find producer in dts fail, ret=%d\n",
			__func__, ret);
		return ret;
	}

	return 0;
}

/* query the configure from dts and store in prv_data */
int fts_parse_dts(
	struct device_node *device,
	struct ts_device_data *chip_data)
{
	u32 u32Value = 0;
	int ret = NO_ERR;
	int read_val = NO_ERR;

	chip_data->irq_gpio = of_get_named_gpio(device, FTS_IRQ_GPIO, 0);
	if (!gpio_is_valid(chip_data->irq_gpio)) {
		TS_LOG_ERR("irq gpio is not valid, value is %d\n",
			   chip_data->irq_gpio);
	}

	chip_data->reset_gpio = of_get_named_gpio(device, FTS_RST_GPIO, 0);
	if (!gpio_is_valid(chip_data->reset_gpio))
		TS_LOG_ERR("reset gpio is not valid\n");

	ret =
		of_property_read_u32(device, FTS_IRQ_CFG, &chip_data->irq_config);
	if (ret)
		TS_LOG_ERR("get irq config failed\n");

	ret = of_property_read_u32(device, FTS_ALGO_ID, &chip_data->algo_id);
	if (ret)
		TS_LOG_ERR("get algo id failed\n");

	ret =
		of_property_read_u32(device, FTS_IC_TYPES, &chip_data->ic_type);
	if (ret)
		TS_LOG_ERR("get device ic_type failed\n");

	ret = of_property_read_u32(device, FTS_VCI_LDO_VALUE,
				 &chip_data->regulator_ctr.vci_value);
	if (ret)
		TS_LOG_INFO("Not define Vci value in Dts, use fault value\n");
		chip_data->regulator_ctr.vci_value = 3100000;

	ret = of_property_read_u32(device, FTS_NEED_SET_VDDIO_VALUE,
				 &chip_data->regulator_ctr.need_set_vddio_value);
	if (ret) {
		TS_LOG_INFO("Not define need set Vddio value in Dts, use fault value\n");
		chip_data->regulator_ctr.need_set_vddio_value = 0;
	} else {
		ret = of_property_read_u32(device, FTS_VDDIO_LDO_VALUE,
					 &chip_data->regulator_ctr.vddio_value);
		if (ret) {
			TS_LOG_INFO("Vddio value not defiend, use fault value\n");
				chip_data->regulator_ctr.vddio_value = 1800000;
		}
	}

	ret = of_property_read_u32(device, FTS_X_MAX, &chip_data->x_max);
	if (ret)
		TS_LOG_ERR("get device x_max failed\n");

	ret = of_property_read_u32(device, FTS_Y_MAX, &chip_data->y_max);
	if (ret)
		TS_LOG_ERR("get device y_max failed\n");

	ret = of_property_read_u32(device, FTS_X_MAX_MT,
				 &chip_data->x_max_mt);
	if (ret)
		TS_LOG_ERR("get device x_max failed\n");

	ret = of_property_read_u32(device, FTS_Y_MAX_MT,
				 &chip_data->y_max_mt);
	if (ret)
		TS_LOG_ERR("get device y_max failed\n");

	ret = of_property_read_u32(device, FTS_VCI_GPIO_TYPE,
				 &chip_data->vci_gpio_type);
	if (ret)
		TS_LOG_ERR("get device fts_VCI_GPIO_TYPE failed\n");

	ret = of_property_read_u32(device, FTS_VCI_REGULATOR_TYPE,
				 &chip_data->vci_regulator_type);
	if (ret)
		TS_LOG_ERR("get device FTS_VCI_REGULATOR_TYPE failed\n");

	ret = of_property_read_u32(device, FTS_VDDIO_GPIO_TYPE,
				 &chip_data->vddio_gpio_type);
	if (ret)
		TS_LOG_ERR("get device fts_VDDIO_GPIO_TYPE failed\n");

	ret = of_property_read_u32(device, FTS_VDDIO_REGULATOR_TYPE,
				 &chip_data->vddio_regulator_type);
	if (ret)
		TS_LOG_ERR("get device fts_VDDIO_REGULATOR_TYPE failed\n");

	ret = of_property_read_string(device, FTS_TEST_TYPE,
				 (const char **)&chip_data->tp_test_type);
	if (ret) {
		TS_LOG_INFO("get device fts_TEST_TYPE not exit,use default value\n");
		strncpy(chip_data->tp_test_type, 
			"Normalize_type:judge_last_result",
			TS_CAP_TEST_TYPE_LEN);
	}

	/* 0 is power supplied by gpio, 1 is power supplied by ldo */
	if (1 == chip_data->vci_gpio_type) {
		chip_data->vci_gpio_ctrl =
			of_get_named_gpio(device, FTS_VCI_GPIO_CTRL, 0);

		if (!gpio_is_valid(chip_data->vci_gpio_ctrl))
			TS_LOG_ERR("SFT: ok; ASIC: Real err----power gpio is not valid\n");
	}

	if (1 == chip_data->vddio_gpio_type) {
		chip_data->vddio_gpio_ctrl =
			of_get_named_gpio(device, FTS_VDDIO_GPIO_CTRL, 0);

		if (!gpio_is_valid(chip_data->vddio_gpio_ctrl))
			TS_LOG_ERR("SFT: ok; ASIC: Real err----power gpio is not valid\n");
	}

	/*
	 * 0 is cover without glass, 
	 * 1 is cover with glass that need glove mode
	 */
	ret = of_property_read_u32(device, FTS_COVER_FORCE_GLOVE,
				 &chip_data->cover_force_glove);

	/*if not define in dtsi,set 0 to disable it*/
	if (ret) {
		TS_LOG_INFO("get device FTS_COVER_FORCE_GLOVE failed,use default!\n");
			chip_data->cover_force_glove = 0;
	}

	ret = of_property_read_u32(device, FTS_CHIP_ID_DTS, &u32Value);
	fts_upgrade_delay.chip_id = (u8)u32Value;
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_CHIP_ID_DTS);
		fts_upgrade_delay.chip_id=0x87;//Use default value
	}

	ret = of_property_read_u32(device, FTS_HARD_RESET_DELAY,
				 &fts_upgrade_delay.hard_reset_delay);
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_HARD_RESET_DELAY);
		fts_upgrade_delay.hard_reset_delay=200;//Use default value
	}

	ret = of_property_read_u32(device, FTS_ERASE_MIN_DELAY,
				 &fts_upgrade_delay.erase_min_delay);
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_ERASE_MIN_DELAY);
		fts_upgrade_delay.erase_min_delay=1350;//Use default value
	}

	ret = of_property_read_u32(device, FTS_CALC_CRC_DELAY,
				 &fts_upgrade_delay.calc_crc_delay);
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_CALC_CRC_DELAY);
		fts_upgrade_delay.calc_crc_delay=300;//Use default value
	}

	ret = of_property_read_u32(device, FTS_REBOOT_DELAY,
				 &fts_upgrade_delay.reboot_delay);
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_REBOOT_DELAY);
		fts_upgrade_delay.reboot_delay=200;//Use default value
	}

	ret = of_property_read_u32(device, FTS_ERASE_QUERY_PER_TIME_DELAY,
				 &fts_upgrade_delay.erase_query_per_time_delay);
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_ERASE_QUERY_PER_TIME_DELAY);
		fts_upgrade_delay.erase_query_per_time_delay=50;//Use default value
	}

	ret = of_property_read_u32(device, FTS_WRITE_FLASH_MAX_QUERY_TIME,
				 &fts_upgrade_delay.write_flash_max_query_time);
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_WRITE_FLASH_MAX_QUERY_TIME);
		fts_upgrade_delay.write_flash_max_query_time=30;//Use default value
	}

	ret = of_property_read_u32(device, FTS_READ_ECC_MAX_QUERY_TIME,
				 &fts_upgrade_delay.read_ecc_max_query_time);
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_READ_ECC_MAX_QUERY_TIME);
		fts_upgrade_delay.read_ecc_max_query_time=100;//Use default value
	}

	ret = of_property_read_u32(device, FTS_ERASE_FLASH_MAX_QUERY_TIME,
				 &fts_upgrade_delay.erase_flash_max_query_time);
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_ERASE_FLASH_MAX_QUERY_TIME);
		fts_upgrade_delay.erase_flash_max_query_time=15;//Use default value
	}

	ret = of_property_read_u32(device, FTS_UPGRADE_LOOP_TIME,
				 &fts_upgrade_delay.upgrade_loop_time);
	if (ret) {
		TS_LOG_INFO("not set %s in dts, use default.\n", FTS_UPGRADE_LOOP_TIME);
		fts_upgrade_delay.upgrade_loop_time=30;	//Use default value
	}

	ret = of_property_read_u32(device, FTS_GLOVE_SWITCH_ADDR, &read_val);
	if (!ret) {
		TS_LOG_INFO("get chip specific glove_switch_addr = 0x%04x\n", read_val);
		g_ts_data.feature_info.glove_info.glove_switch_addr = (u16)read_val;
	}


	TS_LOG_INFO
		("reset_gpio = %d, irq_gpio = %d, irq_config = %d, algo_id = %d, ic_type = %d, x_max = %d, y_max = %d, x_mt = %d,y_mt = %d, bootloader_update_enable = %d\n",
		 chip_data->reset_gpio, chip_data->irq_gpio, chip_data->irq_config,
		 chip_data->algo_id, chip_data->ic_type, chip_data->x_max,
		 chip_data->y_max, chip_data->x_max_mt, chip_data->y_max_mt,
		 chip_data->bootloader_update_enable);
	TS_LOG_INFO
		("chip_id = 0x%x, hard_reset_delay = %d, erase_min_delay = %d, calc_crc_delay = %d, reboot_delay = %d, erase_query_per_time_delay = %d,\
		write_flash_max_query_time = %d, read_ecc_max_query_time = %d, erase_flash_max_query_time = %d,upgrade_loop_time = %d\n",
		 fts_upgrade_delay.chip_id, fts_upgrade_delay.hard_reset_delay, fts_upgrade_delay.erase_min_delay, fts_upgrade_delay.calc_crc_delay,
		 fts_upgrade_delay.reboot_delay, fts_upgrade_delay.erase_query_per_time_delay, fts_upgrade_delay.write_flash_max_query_time,
		 fts_upgrade_delay.read_ecc_max_query_time, fts_upgrade_delay.erase_flash_max_query_time, fts_upgrade_delay.upgrade_loop_time);

	TS_LOG_INFO
		("glove switch addr = 0x%04x\n", g_ts_data.feature_info.glove_info.glove_switch_addr);

	fts_test_dt_init_device_node(device);

	return NO_ERR;
}

int fts_init_capacitance_test_data(
	struct fts_ts_platform_data *fts_pdata,
	struct fts_test_params *params) 
{
	int ret, read_val;
	
	char project_id[FTS_PROJECT_ID_LEN + 1] = { 0 };
	char compatible_name[FTS_COMPATIBLE_NAME_LEN] = { 0 };

	struct device_node *np = NULL;
	
	ret = fts_read_project_id(fts_pdata, project_id, FTS_PROJECT_ID_LEN);
	if (ret) {
		TS_LOG_ERR("%s:read project id fail, ret=%d", __func__, ret);
		return ret;
	}

	ret = fts_create_vendor_compatible_name(project_id, compatible_name,
		FTS_COMPATIBLE_NAME_LEN);
	if (ret) {
		TS_LOG_ERR("%s:create compatible name fail, ret=%d",
			__func__, ret);
		return ret;
	}

        TS_LOG_INFO("%s:vendor compatible name is: %s\n", __func__,
		compatible_name);

	np = of_find_compatible_node(NULL, NULL, compatible_name);
	if (!np) {
		TS_LOG_ERR("%s:compatible name not found, name:%s\n",
			__func__, compatible_name);
		return -ENODEV;
	}

        ret = of_property_read_u32(np, DTS_CHANNEL_NUM_TEST, &read_val);
        if (!ret) {
                TS_LOG_INFO("get channel_num_test is %d.\n", read_val);
                params->item_switchs.channel_num_test = read_val;
        }

        ret = of_property_read_u32(np, DTS_RAWDATA_TEST, &read_val);
        if (!ret) {
                TS_LOG_INFO("get rawdata_test is %d.\n", read_val);
                params->item_switchs.rawdata_test = read_val;
        }

        ret = of_property_read_u32(np, DTS_CB_TEST, &read_val);
        if (!ret) {
                TS_LOG_INFO("get cb_test is %d.\n", read_val);
                params->item_switchs.cb_test = read_val;
        }

        ret = of_property_read_u32(np, DTS_SHORT_CIRCUIT_TEST, &read_val);
        if (!ret) {
                TS_LOG_INFO("get short_circuit_test is %d.\n", read_val);
                params->item_switchs.short_test = read_val;
        }

        ret = of_property_read_u32(np, DTS_OPEN_TEST, &read_val);
        if (!ret) {
                TS_LOG_INFO("get open_test is %d.\n", read_val);
                params->item_switchs.open_test = read_val;
        }

        //channel_num_test
        ret = of_property_read_u32(np, DTS_CHANNEL_NUM_X, &read_val);
        if (!ret) {
                TS_LOG_INFO("get y channel number is %d.\n", read_val);
                params->threshold.channel_num_test_channel_x = read_val;
        }

        ret = of_property_read_u32(np, DTS_CHANNEL_NUM_Y, &read_val);
        if (!ret) {
                TS_LOG_INFO("get y channel number is %d.\n", read_val);
                params->threshold.channel_num_test_channel_y = read_val;
        }

        ret = of_property_read_u32(np, DTS_CHANNEL_NUM_KEY, &read_val);
        if (!ret) {
                TS_LOG_INFO("get channel_num_test_key_num is %d.\n", read_val);
                params->threshold.channel_num_test_key_num = read_val;
        }

        //rawdata_test
        ret = of_property_read_u32(np, DTS_RAW_DATA_MIN, &read_val);
        if (!ret) {
                TS_LOG_INFO("get rawdata_min is %d.\n", read_val);
                params->threshold.rawdata_test_min = read_val;
        }

        ret = of_property_read_u32(np, DTS_RAW_DATA_MAX, &read_val);
        if (!ret) {
                TS_LOG_INFO("get rawdata_test_max is %d.\n", read_val);
                params->threshold.rawdata_test_max = read_val;
        }       

	//cb_test
        ret = of_property_read_u32(np, DTS_CB_TEST_VA_CHECK, &read_val);
        if (!ret) {
                TS_LOG_INFO("get cb_test_va_check is %d.\n", read_val);
                params->threshold.cb_test_va_check = read_val;
        }
    
        ret = of_property_read_u32(np, DTS_CB_TEST_MIN, &read_val);
        if (!ret) {
                TS_LOG_INFO("get cb_test_min is %d.\n", read_val);
                params->threshold.cb_test_min = read_val;
        } 

        ret = of_property_read_u32(np, DTS_CB_TEST_MAX, &read_val);
        if (!ret) {
                TS_LOG_INFO("get cb_test_max is %d.\n", read_val);
                params->threshold.cb_test_max = read_val;
        } 

        ret = of_property_read_u32(np, DTS_CB_TEST_VKEY_CHECK, &read_val);
        if (!ret) {
                TS_LOG_INFO("get cb_test_vkey_check is %d.\n", read_val);
                params->threshold.cb_test_vkey_check = read_val;
        } 

        ret = of_property_read_u32(np, DTS_CB_TEST_MIN_VKEY, &read_val);
        if (!ret) {
                TS_LOG_INFO("get cb_test_min_vkey is %d.\n", read_val);
                params->threshold.cb_test_min_vkey = read_val;
        }
    
        ret = of_property_read_u32(np, DTS_CB_TEST_MAX_VKEY, &read_val);
        if (!ret) {
                TS_LOG_INFO("get cb_test_max_vkey is %d.\n", read_val);
                params->threshold.cb_test_max_vkey = read_val;
        }

        //short_circuit_test
        ret = of_property_read_u32(np,
        	DTS_SHORT_CIRCUIT_TEST_REG_MIN, &read_val);
        if (!ret) {
                TS_LOG_INFO("get short_circuit_test_reg_min is %d\n", read_val);
                params->threshold.short_circuit_test_res_min = read_val;
        }

        //open_test
        ret = of_property_read_u32(np, DTS_OPEN_TEST_CB_MIN, &read_val);
        if (!ret) {
                TS_LOG_INFO("get open_test_cb_min is %d.\n", read_val);
                params->threshold.open_test_cb_min = read_val;
        }

        ret = of_property_read_u32(np, DTS_OPEN_TEST_CHECK_K1, &read_val);
        if (!ret) {
                TS_LOG_INFO("get open_test_check_k1 is %d.\n", read_val);
                params->threshold.open_test_check_k1 = read_val;
        }

        ret = of_property_read_u32(np, DTS_OPEN_TEST_K1_THRESHOLD, &read_val);
        if (!ret) {
                TS_LOG_INFO("get open_test_k1_threshold is %d.\n", read_val);
                params->threshold.open_test_k1_threshold = read_val;
        }

        ret = of_property_read_u32(np, DTS_OPEN_TEST_CHECK_K2, &read_val);
        if (!ret) {
                TS_LOG_INFO("get open_test_check_k2 is %d.\n", read_val);
                params->threshold.open_test_check_k2 = read_val;
        }

        ret = of_property_read_u32(np, DTS_OPEN_TEST_K2_THRESHOLD, &read_val);
        if (!ret) {
                TS_LOG_INFO("get open_test_k2_threshold is %d.\n", read_val);
                params->threshold.open_test_k2_threshold = read_val;
        }

        return 0;
}

