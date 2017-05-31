/* Copyright (c) 2011-2013, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include "hw_flash.h"
//lint -save -e31 -e64 -e84 -e708 -e712 -e713 -e715 -e732 -e734 -e737 -e651
//lint -save -e747 -e753 -e778 -e785 -e838 -e846 -e866 -e514 -e528 -e570 -e574 -e578
/* LM3642 Registers define */
#define REG_CHIP_ID			0x00
#define REG_ENABLE			0x0a
#define REG_FLAGS			0x0b
#define REG_FLASH_FEATURES		0x08
#define REG_CURRENT_CONTROL		0x09
#define REG_IVFM			0x01


#define MODE_STANDBY			0x00
#define UVLO_VOLTAGE                   0x0C   //3.2v
#define FLASH_TIMEOUT			0x05   // 600ms
#define FLASH_RAMP_TIME             0x08   //512us
#define MODE_TORCH			0x02
#define MODE_FLASH			0x03
#define IVFM_EN                       0x80
#define UVLO_EN                       0x80
#define TX_PIN				0x40

#define LM3642_FLASH_DEFAULT_CUR_LEV          7  //760mA
#define LM3642_TORCH_DEFAULT_CUR_LEV         2    //140mA
#define LM3642_FLASH_MAX_CUR_LEV                 15  //1500mA
#define LM3642_FLASH_MAX_CUR                         1500
#define LM3642_TORCH_MAX_CUR_LEV                 7   //375mA
#define LM3642_TORCH_MAX_CUR                         375

#define FLASH_LED_MAX			16
#define TORCH_LED_MAX			8
#define FLASH_LED_LEVEL_INVALID  0xff

/* Internal data struct define */
struct hw_lm3642_private_data_t {
	unsigned char flash_led[FLASH_LED_MAX];
	unsigned char torch_led[TORCH_LED_MAX];
	unsigned int flash_led_num;
	unsigned int torch_led_num;
	unsigned int flash_current;
	unsigned int torch_current;

	/* flash control pin */
	unsigned int strobe;

	unsigned int chipid;
};

static int flash_arry[16] = {94, 188, 281, 375, 469, 563, 656, 750, 844, 938, 1031, 1125, 1219, 1313, 1406, 1500};
static int torch_arry[8] = {48, 94, 141, 188, 234, 281, 328, 375};

/* Internal varible define */
static struct hw_lm3642_private_data_t hw_lm3642_pdata;
static struct hw_flash_ctrl_t hw_lm3642_ctrl;
static struct i2c_driver hw_lm3642_i2c_driver;

DEFINE_HISI_FLASH_MUTEX(lm3642);

/* Function define */
#if 0
static int lm3642_set_strobe(struct hw_flash_ctrl_t *flash_ctrl,
	unsigned int state)
{
	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	cam_debug("%s strobe0=%d, state=%d.", __func__,
		flash_ctrl->flash_info.strobe0, state);
	gpio_direction_output(flash_ctrl->flash_info.strobe0, state);
	return 0;
}
#endif

static int hw_lm3642_find_match_flash_current(int cur_flash)
{
    int cur_level = 0;
    int i = 0;

    cam_info("%s ernter cur_flash %d.\n", __func__, cur_flash);
    if(cur_flash <= 0){
        cam_err("%s current set is error", __func__);
        return -1;
    }

    if(cur_flash >= LM3642_FLASH_MAX_CUR){
        cam_warn("%s current set is %d", __func__, cur_flash);
        return LM3642_FLASH_DEFAULT_CUR_LEV;
    }

    for(i=0; i < 16; i ++){
       if(cur_flash <= flash_arry[i]){
            cam_info("%s  i %d.\n", __func__, i);
            break;
       }
    }

    if( i==0 ){
          cur_level = i;
    }
    else if(i == 16){
        if((cur_flash - flash_arry[i-2]) < (flash_arry[i - 1] -cur_flash))
              cur_level = i -2;
        else
              cur_level = i -1;
    }
    else{
        if((cur_flash - flash_arry[i-1]) < (flash_arry[i] -cur_flash))
              cur_level = i -1;
        else
              cur_level = i;
    }

    return cur_level;
}

static int hw_lm3642_find_match_torch_current(int cur_torch)
{
    int cur_level = 0;
    int i = 0;

    cam_info("%s ernter cur_torch %d.\n", __func__, cur_torch);
    if(cur_torch <= 0){
        cam_err("%s current set is error", __func__);
        return -1;
    }

    if(cur_torch >= LM3642_TORCH_MAX_CUR){
        cam_warn("%s current set is %d", __func__, cur_torch);
        return LM3642_TORCH_DEFAULT_CUR_LEV;
    }

    for(i=0; i < 8; i ++){
       if(cur_torch <= torch_arry[i]){
            cam_info("%s  i %d.\n", __func__, i);
            break;
       }
    }

    if( i==0 ){
          cur_level = i;
    }
    else if(i == 8){
        if((cur_torch - torch_arry[i-2]) < (torch_arry[i - 1] -cur_torch))
              cur_level = i -2;
        else
              cur_level = i - 1;
   }
    else{
        if((cur_torch - torch_arry[i-1]) < (torch_arry[i] -cur_torch))
              cur_level = i -1;
        else
              cur_level = i;
    }

    return cur_level;
}

static int hw_lm3642_init(struct hw_flash_ctrl_t *flash_ctrl)
{
#if 0
	struct hw_lm3642_private_data_t *pdata;
#endif

	cam_debug("%s ernter.\n", __func__);
	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}
#if 0
	pdata = (struct hw_lm3642_private_data_t *)flash_ctrl->pdata;

	flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
						PINCTRL_STATE_DEFAULT);

	rc = gpio_request(pdata->strobe, "flash-strobe");
	if (rc < 0) {
		cam_err("%s failed to request strobe pin.", __func__);
		return -EIO;
	}
#endif
	return 0;
}

static int hw_lm3642_exit(struct hw_flash_ctrl_t *flash_ctrl)
{
#if 0
	struct hw_lm3642_private_data_t *pdata;
#endif

	cam_debug("%s ernter.\n", __func__);
	if (NULL == flash_ctrl) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	flash_ctrl->func_tbl->flash_off(flash_ctrl);
#if 0
	pdata = (struct hw_lm3642_private_data_t *)flash_ctrl->pdata;

	gpio_free(pdata->strobe);
	flash_ctrl->pctrl = devm_pinctrl_get_select(flash_ctrl->dev,
						PINCTRL_STATE_IDLE);
#endif
	return 0;
}

static int hw_lm3642_flash_mode(struct hw_flash_ctrl_t *flash_ctrl,
	int data)
{
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	struct hw_lm3642_private_data_t *pdata;
	unsigned char val;
	int current_level = 0;

	cam_info("%s data=%d.\n", __func__, data);
	if ((NULL == flash_ctrl) || (NULL == flash_ctrl->pdata) || (NULL == flash_ctrl->flash_i2c_client)) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = flash_ctrl->pdata;
	if (FLASH_LED_LEVEL_INVALID == pdata->flash_current)
	{
		current_level = LM3642_FLASH_DEFAULT_CUR_LEV;
	}
	else
	{
		current_level = hw_lm3642_find_match_flash_current(data);
		if(current_level < 0){
		     current_level = LM3642_FLASH_DEFAULT_CUR_LEV;
		}
	}
	/* clear error flag,resume chip */
	loge_if_ret(i2c_func->i2c_read(i2c_client, REG_FLAGS, &val) < 0);
	loge_if_ret(i2c_func->i2c_read(i2c_client, REG_CURRENT_CONTROL, &val) < 0);

	/* set LED Flash current value */
	val = (val & 0xf0) | (current_level & 0x0f);
	cam_info("%s led flash current val=0x%x, current level=%d.\n", __func__, val, current_level);

	loge_if_ret(i2c_func->i2c_write(i2c_client, REG_CURRENT_CONTROL, val) < 0);
	loge_if_ret(i2c_func->i2c_write(i2c_client, REG_FLASH_FEATURES, FLASH_RAMP_TIME|FLASH_TIMEOUT) < 0);  //set timout and ramp time
	if (flash_ctrl->flash_mask_enable) {
		loge_if_ret(i2c_func->i2c_write(i2c_client, REG_ENABLE, MODE_FLASH|TX_PIN) < 0);
	} else {
		loge_if_ret(i2c_func->i2c_write(i2c_client, REG_ENABLE, MODE_FLASH|IVFM_EN) < 0);
	}

	return 0;
}

static int hw_lm3642_torch_mode(struct hw_flash_ctrl_t *flash_ctrl,
	int data)
{
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	struct hw_lm3642_private_data_t *pdata;
	unsigned char val;
	int current_level = 0;

	cam_info("%s data=%d.\n", __func__, data);
	if ((NULL == flash_ctrl) || (NULL == flash_ctrl->pdata) || (NULL == flash_ctrl->flash_i2c_client)) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = (struct hw_lm3642_private_data_t *)flash_ctrl->pdata;
	if (FLASH_LED_LEVEL_INVALID == pdata->torch_current)
	{
		current_level = LM3642_TORCH_DEFAULT_CUR_LEV;
	}
	else
	{
		current_level = hw_lm3642_find_match_torch_current(data);
		if(current_level < 0){
		      current_level = LM3642_TORCH_DEFAULT_CUR_LEV;
		}
	}
	/* clear error flag,resume chip */
	loge_if_ret(i2c_func->i2c_read(i2c_client, REG_FLAGS, &val) < 0);
	loge_if_ret(i2c_func->i2c_read(i2c_client, REG_CURRENT_CONTROL, &val) < 0);

	/* set LED Flash current value */
	val = (val & 0x0f) | (current_level << 4);
	cam_info("%s the led torch current val=0x%x, current_level=%d.\n", __func__, val, current_level);

	loge_if_ret(i2c_func->i2c_write(i2c_client, REG_CURRENT_CONTROL, val) < 0);
	loge_if_ret(i2c_func->i2c_write(i2c_client, REG_ENABLE, MODE_TORCH|IVFM_EN) < 0);

	return 0;
}

static int hw_lm3642_on(struct hw_flash_ctrl_t *flash_ctrl, void *data)
{
	struct hw_flash_cfg_data *cdata = (struct hw_flash_cfg_data *)data;
	int rc=-1;

	cam_debug("%s ernter.\n", __func__);
	if ((NULL == flash_ctrl) || (NULL == cdata)) {
		cam_err("%s flash_ctrl or cdata is NULL.", __func__);
		return -1;
	}

	cam_info("%s mode=%d, level=%d.\n", __func__, cdata->mode, cdata->data);
	mutex_lock(flash_ctrl->hw_flash_mutex);
	if (FLASH_MODE == cdata->mode) {
		rc = hw_lm3642_flash_mode(flash_ctrl, cdata->data);
	} else {
		rc = hw_lm3642_torch_mode(flash_ctrl, cdata->data);
	}
	flash_ctrl->state.mode = cdata->mode;
	flash_ctrl->state.data = cdata->data;
	mutex_unlock(flash_ctrl->hw_flash_mutex);

	return rc;
}

static int hw_lm3642_off(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	unsigned char val;

	cam_debug("%s ernter.\n", __func__);
	if ((NULL == flash_ctrl) || (NULL == flash_ctrl->flash_i2c_client) || (NULL == flash_ctrl->flash_i2c_client->i2c_func_tbl)) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	mutex_lock(flash_ctrl->hw_flash_mutex);
	flash_ctrl->state.mode = STANDBY_MODE;
	flash_ctrl->state.data = 0;
	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;

	if(i2c_func->i2c_read(i2c_client, REG_FLAGS, &val) < 0){
		cam_err("%s %d", __func__, __LINE__);
	}
	if(i2c_func->i2c_write(i2c_client, REG_ENABLE, MODE_STANDBY) < 0){
		cam_err("%s %d", __func__, __LINE__);
	}
	mutex_unlock(flash_ctrl->hw_flash_mutex);

	return 0;
}

static int hw_lm3642_match(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_flash_i2c_client *i2c_client;
	struct hw_flash_i2c_fn_t *i2c_func;
	struct hw_lm3642_private_data_t *pdata;
	unsigned char id;

	cam_debug("%s ernter.\n", __func__);
	if ((NULL == flash_ctrl) || (NULL == flash_ctrl->pdata) || (NULL == flash_ctrl->flash_i2c_client)) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return -1;
	}

	i2c_client = flash_ctrl->flash_i2c_client;
	i2c_func = flash_ctrl->flash_i2c_client->i2c_func_tbl;
	pdata = (struct hw_lm3642_private_data_t *)flash_ctrl->pdata;

	loge_if_ret(i2c_func->i2c_read(i2c_client, REG_CHIP_ID, &id) < 0);
	cam_info("%s id=0x%x.\n", __func__, id);
	if (id != pdata->chipid) {
		cam_err("%s match error, id(0x%x) != 0x%x.",
			__func__, (id&0x7), pdata->chipid);
		return -1;
	}
	loge_if_ret(i2c_func->i2c_write(i2c_client, REG_ENABLE, IVFM_EN) < 0);  //enable IVFM
	loge_if_ret(i2c_func->i2c_write(i2c_client, REG_IVFM, UVLO_EN|UVLO_VOLTAGE) < 0);    //enable UVLO, set voltage 3.2v

	return 0;
}

static int hw_lm3642_get_dt_data(struct hw_flash_ctrl_t *flash_ctrl)
{
	struct hw_lm3642_private_data_t *pdata;
	struct device_node *of_node;
	int rc = -1;

	cam_debug("%s enter.\n", __func__);
	if ((NULL == flash_ctrl) || (NULL == flash_ctrl->pdata)) {
		cam_err("%s flash_ctrl is NULL.", __func__);
		return rc;
	}

	pdata = (struct hw_lm3642_private_data_t *)flash_ctrl->pdata;
	of_node = flash_ctrl->dev->of_node;
#if 0
	rc = of_property_read_u32(of_node, "huawei,flash-pin",
		&pdata->strobe);
	cam_info("%s hisi,flash-pin %d, rc %d\n", __func__,
		pdata->strobe, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		/* return rc; */
	}
#endif

	rc = of_property_read_u32(of_node, "huawei,flash_current",
		&pdata->flash_current);
	cam_info("%s hisi,flash_current %d, rc %d\n", __func__,
		pdata->flash_current, rc);
	if (rc < 0) {
		cam_info("%s failed %d\n", __func__, __LINE__);
		pdata->flash_current = FLASH_LED_LEVEL_INVALID;
		//return rc;
	}

	rc = of_property_read_u32(of_node, "huawei,torch_current",
		&pdata->torch_current);
	cam_info("%s hisi,torch_current %d, rc %d\n", __func__,
		pdata->torch_current, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		pdata->torch_current = FLASH_LED_LEVEL_INVALID;
		//TO FIX
		//return rc;
	}
#if 0
	rc = of_property_read_u32(of_node, "huawei,flash_led_num",
		&pdata->flash_led_num);
	cam_info("%s hisi,flash_led_num %d, rc %d\n", __func__,
		pdata->flash_led_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u32(of_node, "huawei,torch_led_num",
		&pdata->torch_led_num);
	cam_info("%s hisi,torch_led_num %d, rc %d\n", __func__,
		pdata->torch_led_num, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}

	rc = of_property_read_u8_array(of_node, "huawei,flash_led",
		pdata->flash_led, pdata->flash_led_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		//TO FIX
		/* return rc; */
	} else {
		for (i=0; i< pdata->flash_led_num; i++) {
			cam_debug("%s flash_led[%d]=%d.\n", __func__, i,
				pdata->flash_led[i]);
		}
	}

	rc = of_property_read_u8_array(of_node, "huawei,torch_led",
		pdata->torch_led, pdata->torch_led_num);
	if (rc < 0) {
		cam_err("%s failed line %d\n", __func__, __LINE__);
		//TO FIX
		/* return rc; */
	} else {
		for (i=0; i< pdata->torch_led_num; i++) {
			cam_debug("%s torch_led[%d]=%d.\n", __func__, i,
				pdata->torch_led[i]);
		}
	}
#endif
	rc = of_property_read_u32(of_node, "huawei,flash-chipid",
		&pdata->chipid);
	cam_info("%s hisi,chipid 0x%x, rc %d\n", __func__,
		pdata->chipid, rc);
	if (rc < 0) {
		cam_err("%s failed %d\n", __func__, __LINE__);
		return rc;
	}
	return rc;
}

static ssize_t hw_lm3642_lightness_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;

        snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "mode=%d, data=%d.\n",
		hw_lm3642_ctrl.state.mode, hw_lm3642_ctrl.state.mode);
        rc = strlen(buf)+1;
        return rc;
}

static int hw_lm3642_param_check(char *buf, unsigned long *param,
	int num_of_par)
{
	char *token;
	int base, cnt;

	token = strsep(&buf, " ");

	for (cnt = 0; cnt < num_of_par; cnt++)
	{
		if (token != NULL)
		{
			if ((token[1] == 'x') || (token[1] == 'X')) {
				base = 16;
			} else {
				base = 10;
			}

			if (strict_strtoul(token, base, &param[cnt]) != 0) {
				return -EINVAL;
			}

			token = strsep(&buf, " ");
		}
		else
		{
			return -EINVAL;
		}
	}
	return 0;
}

static ssize_t hw_lm3642_lightness_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	struct hw_flash_cfg_data cdata = {0};
	unsigned long param[2]={0};
	int rc=0;

	rc = hw_lm3642_param_check((char *)buf, param, 2);
	if (rc < 0) {
		cam_err("%s failed to check param.", __func__);
		return rc;
	}

	cdata.mode = (int)param[0];
	cdata.data = (int)param[1];

	if (cdata.mode == STANDBY_MODE) {
		rc = hw_lm3642_off(&hw_lm3642_ctrl);
		if (rc < 0) {
			cam_err("%s lm3642 flash off error.", __func__);
			return rc;
		}
	} else {
		rc = hw_lm3642_on(&hw_lm3642_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s lm3642 flash on error.", __func__);
			return rc;
		}
	}

	return count;
}

static ssize_t hw_lm3642_flash_mask_show(struct device *dev,
	struct device_attribute *attr,char *buf)
{
        int rc=0;

        snprintf(buf, MAX_ATTRIBUTE_BUFFER_SIZE, "flash_mask_disabled=%d.\n",
		hw_lm3642_ctrl.flash_mask_enable);
        rc = strlen(buf)+1;
        return rc;
}

static ssize_t hw_lm3642_flash_mask_store(struct device *dev,
	struct device_attribute *attr, const char *buf, size_t count)
{
	if ('0' == buf[0]) {
		hw_lm3642_ctrl.flash_mask_enable = false;
	} else {
		hw_lm3642_ctrl.flash_mask_enable = true;
	}
	cam_debug("%s flash_mask_enable=%d.", __func__,
			hw_lm3642_ctrl.flash_mask_enable);
	return count;
}

static void hw_lm3642_torch_brightness_set(struct led_classdev *cdev,
	enum led_brightness brightness)
{
	struct hw_flash_cfg_data cdata;
	int rc;
	unsigned int led_bright = brightness;

	if (STANDBY_MODE == led_bright) {
		rc = hw_lm3642_off(&hw_lm3642_ctrl);
		if (rc < 0) {
			cam_err("%s pmu_led off error.", __func__);
			return;
		}
	} else {
		cdata.mode = TORCH_MODE;
		cdata.data = brightness-1;
		rc = hw_lm3642_on(&hw_lm3642_ctrl, &cdata);
		if (rc < 0) {
			cam_err("%s pmu_led on error.", __func__);
			return;
		}
	}
}

static struct device_attribute hw_lm3642_lightness =
    __ATTR(lightness, 0664, hw_lm3642_lightness_show, hw_lm3642_lightness_store);

static struct device_attribute hw_lm3642_flash_mask =
    __ATTR(flash_mask, 0664, hw_lm3642_flash_mask_show, hw_lm3642_flash_mask_store);

static int hw_lm3642_register_attribute(struct hw_flash_ctrl_t *flash_ctrl, struct device *dev)
{
	int rc = 0;

	if ((NULL == flash_ctrl) || (NULL == dev)) {
		cam_err("%s flash_ctrl or dev is NULL.", __func__);
		return -1;
	}

	flash_ctrl->cdev_torch.name = "torch";
	flash_ctrl->cdev_torch.max_brightness
		= ((struct hw_lm3642_private_data_t *)(flash_ctrl->pdata))->torch_led_num;
	flash_ctrl->cdev_torch.brightness_set = hw_lm3642_torch_brightness_set;
	rc = led_classdev_register((struct device *)dev, &flash_ctrl->cdev_torch);
	if (rc < 0) {
		cam_err("%s failed to register torch classdev.", __func__);
		goto err_out;
	}

	rc = device_create_file(dev, &hw_lm3642_lightness);
	if (rc < 0) {
		cam_err("%s failed to creat lightness attribute.", __func__);
		goto err_create_lightness_file;
	}

	rc = device_create_file(dev, &hw_lm3642_flash_mask);
	if (rc < 0) {
		cam_err("%s failed to creat flash_mask attribute.", __func__);
		goto err_create_flash_mask_file;
	}
	return 0;
err_create_flash_mask_file:
	device_remove_file(dev, &hw_lm3642_lightness);
err_create_lightness_file:
	led_classdev_unregister(&flash_ctrl->cdev_torch);
err_out:
	return rc;
}

static int hw_lm3642_remove(struct i2c_client *client)
{
	cam_debug("%s enter.", __func__);

	hw_lm3642_ctrl.func_tbl->flash_exit(&hw_lm3642_ctrl);

	client->adapter = NULL;
	return 0;
}

static void hw_lm3642_shutdown(struct i2c_client *client)
{
	int rc = -1;
	rc = hw_lm3642_off(&hw_lm3642_ctrl);
	cam_info("%s lm3642 shut down at (%d)",__func__,__LINE__);
	if (rc < 0) {
		cam_err("%s lm3642 flash off error.", __func__);
	}
}

static const struct i2c_device_id hw_lm3642_id[] = {
	{"lm3642", (unsigned long)&hw_lm3642_ctrl},
	{}
};

static const struct of_device_id hw_lm3642_dt_match[] = {
	{.compatible = "huawei,lm3642"},
	{}
};
MODULE_DEVICE_TABLE(of, lm3642_dt_match);

static struct i2c_driver hw_lm3642_i2c_driver = {
	.probe	= hw_flash_i2c_probe,
	.remove = hw_lm3642_remove,
	.shutdown = hw_lm3642_shutdown,
	.id_table	= hw_lm3642_id,
	.driver = {
		.name = "hw_lm3642",
		.of_match_table = hw_lm3642_dt_match,
	},
};

static int __init hw_lm3642_module_init(void)
{
	cam_info("%s erter.\n", __func__);
	return i2c_add_driver(&hw_lm3642_i2c_driver);
}

static void __exit hw_lm3642_module_exit(void)
{
	cam_info("%s enter.", __func__);
	i2c_del_driver(&hw_lm3642_i2c_driver);
	return;
}

static struct hw_flash_i2c_client hw_lm3642_i2c_client;

static struct hw_flash_fn_t hw_lm3642_func_tbl = {
	.flash_config = hw_flash_config,
	.flash_init = hw_lm3642_init,
	.flash_exit = hw_lm3642_exit,
	.flash_on = hw_lm3642_on,
	.flash_off = hw_lm3642_off,
	.flash_match = hw_lm3642_match,
	.flash_get_dt_data = hw_lm3642_get_dt_data,
	.flash_register_attribute = hw_lm3642_register_attribute,
};

static struct hw_flash_ctrl_t hw_lm3642_ctrl = {
	.flash_i2c_client = &hw_lm3642_i2c_client,
	.func_tbl = &hw_lm3642_func_tbl,
	.hw_flash_mutex = &flash_mut_lm3642,
	.pdata = (void*)&hw_lm3642_pdata,
	.flash_mask_enable = false,
	.state = {
		.mode = STANDBY_MODE,
	},
};

module_init(hw_lm3642_module_init);
module_exit(hw_lm3642_module_exit);
MODULE_DESCRIPTION("LM3642 FLASH");
MODULE_LICENSE("GPL v2");
