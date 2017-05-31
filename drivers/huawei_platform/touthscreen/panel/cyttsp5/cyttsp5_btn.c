/*
 * cyttsp5_btn.c
 * Cypress TrueTouch(TM) Standard Product V5 CapSense Reports Module.
 * For use with Cypress Txx5xx parts.
 * Supported parts include:
 * TMA5XX
 *
 * Copyright (C) 2012-2014 Cypress Semiconductor
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2, and only version 2, as published by the
 * Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Contact Cypress Semiconductor at www.cypress.com <ttdrivers@cypress.com>
 *
 */

#include "cyttsp5_regs.h"

static inline void cyttsp5_btn_key_action(struct cyttsp5_btn_data *bd,
					  int btn_no, int btn_state)
{
	struct cyttsp5_sysinfo *si = bd->si;

	if (!si->btn[btn_no].enabled || si->btn[btn_no].state == btn_state) {
		TS_LOG_DEBUG("%s: si->btn[%d].enabled = %d\n", __func__, btn_no,
			     si->btn[btn_no].enabled);
		TS_LOG_DEBUG("%s: si->btn[%d].state = %d,btn_state = %d.\n",
			     __func__, btn_no, si->btn[btn_no].state,
			     btn_state);
		return;
	}

	si->btn[btn_no].state = btn_state;
	input_report_key(bd->input, si->btn[btn_no].key_code, btn_state);
	input_sync(bd->input);

	TS_LOG_DEBUG("%s: btn=%d key_code=%d %s\n", __func__,
		     btn_no, si->btn[btn_no].key_code,
		     btn_state == CY_BTN_PRESSED ? "PRESSED" : "RELEASED");
}

static void cyttsp5_get_btn_touches(struct cyttsp5_btn_data *bd)
{
	struct cyttsp5_sysinfo *si = bd->si;
	int num_btns = si->num_btns;
	int cur_btn;
	int cur_btn_state;

	TS_LOG_DEBUG("Enter %s.\n", __func__);

	for (cur_btn = 0; cur_btn < num_btns; cur_btn++) {
		/* Get current button state */
		cur_btn_state = (si->xy_data[0] >> (cur_btn * CY_BITS_PER_BTN))
		    & CY_NUM_BTN_EVENT_ID;

		cyttsp5_btn_key_action(bd, cur_btn, cur_btn_state);
	}
}

static void cyttsp5_btn_lift_all(struct cyttsp5_btn_data *bd)
{
	struct cyttsp5_sysinfo *si = bd->si;
	int i;

	if (!si || si->num_btns == 0)
		return;

	for (i = 0; i < si->num_btns; i++)
		cyttsp5_btn_key_action(bd, i, CY_BTN_RELEASED);
}

#ifdef VERBOSE_DEBUG
static void cyttsp5_log_btn_data(struct cyttsp5_btn_data *bd)
{
	struct device *dev = bd->dev;
	struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
	u8 *pr_buf = cd->pr_buf;
	struct cyttsp5_sysinfo *si = bd->si;
	int cur;
	int value;

	for (cur = 0; cur < si->num_btns; cur++) {
		pr_buf[0] = 0;
		if (si->xy_data[0] & (1 << cur))
			value = 1;
		else
			value = 0;
		snprintf(pr_buf, CY_MAX_PRBUF_SIZE, "btn_rec[%d]=0x", cur);
		snprintf(pr_buf, CY_MAX_PRBUF_SIZE, "%s%X (%02X)",
			 pr_buf, value, le16_to_cpu(si->xy_data[1 + cur * 2]));

		TS_LOG_DEBUG("%s: %s\n", __func__, pr_buf);
	}
}
#endif

/* read xy_data for all current CapSense button touches */
static int cyttsp5_xy_worker(struct cyttsp5_btn_data *bd)
{
	struct cyttsp5_sysinfo *si = bd->si;

	TS_LOG_DEBUG("%s,si->num_btns = %d,\n", __func__, si->num_btns);

	/* extract button press/release touch information */
	if (si->num_btns > 0) {
		cyttsp5_get_btn_touches(bd);
#ifdef VERBOSE_DEBUG
		/* log button press/release touch information */
		cyttsp5_log_btn_data(bd);
#endif
	}

	return 0;
}

static int cyttsp5_btn_attention(struct device *dev)
{
	struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
	struct cyttsp5_btn_data *bd = &cd->bd;
	int rc;

	if (bd->si->xy_mode[2] != bd->si->desc.btn_report_id)
		return 0;

	/* core handles handshake */
	mutex_lock(&bd->btn_lock);
	rc = cyttsp5_xy_worker(bd);
	mutex_unlock(&bd->btn_lock);
	if (rc < 0)
		TS_LOG_ERR("%s: xy_worker error r=%d\n", __func__, rc);

	return rc;
}

static int cyttsp5_startup_attention(struct device *dev)
{
	struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
	struct cyttsp5_btn_data *bd = &cd->bd;

	mutex_lock(&bd->btn_lock);
	cyttsp5_btn_lift_all(bd);
	mutex_unlock(&bd->btn_lock);

	return 0;
}

static int cyttsp5_btn_open(struct input_dev *input)
{
	struct device *dev = input->dev.parent;

	TS_LOG_DEBUG("%s: setup subscriptions\n", __func__);

	/* set up touch call back */
	_cyttsp5_subscribe_attention(dev, CY_ATTEN_IRQ, CY_MODULE_BTN,
				     cyttsp5_btn_attention,
				     CY_MODE_OPERATIONAL);

	/* set up startup call back */
	_cyttsp5_subscribe_attention(dev, CY_ATTEN_STARTUP, CY_MODULE_BTN,
				     cyttsp5_startup_attention, 0);

	return 0;
}

static void cyttsp5_btn_close(struct input_dev *input)
{
	struct device *dev = input->dev.parent;

	_cyttsp5_unsubscribe_attention(dev, CY_ATTEN_IRQ, CY_MODULE_BTN,
				       cyttsp5_btn_attention,
				       CY_MODE_OPERATIONAL);

	_cyttsp5_unsubscribe_attention(dev, CY_ATTEN_STARTUP, CY_MODULE_BTN,
				       cyttsp5_startup_attention, 0);
}

static int cyttsp5_setup_input_device(struct device *dev)
{
	struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
	struct cyttsp5_btn_data *bd = &cd->bd;
	int i;
	int rc;

	TS_LOG_INFO("%s: Initialize event signals\n", __func__);
	__set_bit(EV_KEY, bd->input->evbit);
	TS_LOG_INFO("%s: Number of buttons %d\n", __func__, bd->si->num_btns);
	for (i = 0; i < bd->si->num_btns; i++) {
		TS_LOG_INFO("%s: btn:%d keycode:%d\n",
			    __func__, i, bd->si->btn[i].key_code);
		__set_bit(bd->si->btn[i].key_code, bd->input->keybit);
	}

	rc = input_register_device(bd->input);
	if (rc < 0)
		TS_LOG_ERR("%s: Error, failed register input device r=%d\n",
			   __func__, rc);
	else
		bd->input_device_registered = true;

	return rc;
}

static int cyttsp5_setup_input_attention(struct device *dev)
{
	struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
	struct cyttsp5_btn_data *bd = &cd->bd;
	int rc = 0;

	bd->si = _cyttsp5_request_sysinfo(dev);
	if (!bd->si) {
		TS_LOG_ERR("%s: Error, bd->si is NULL.\n", __func__);
		return -1;
	}

	rc = cyttsp5_setup_input_device(dev);

	_cyttsp5_unsubscribe_attention(dev, CY_ATTEN_STARTUP, CY_MODULE_BTN,
				       cyttsp5_setup_input_attention, 0);

	return rc;
}

int cyttsp5_btn_probe(struct device *dev)
{
	struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
	struct cyttsp5_btn_data *bd = &cd->bd;
	struct cyttsp5_platform_data *pdata = dev_get_platdata(dev);
	struct cyttsp5_btn_platform_data *btn_pdata;
	int rc = 0;

	if (!pdata || !pdata->btn_pdata) {
		TS_LOG_ERR("%s: Missing platform data\n", __func__);
		rc = -ENODEV;
		goto error_no_pdata;
	}
	btn_pdata = pdata->btn_pdata;

	mutex_init(&bd->btn_lock);
	bd->dev = dev;
	bd->pdata = btn_pdata;

	/* Create the input device and register it. */
	TS_LOG_INFO("%s: Create the input device and register it\n", __func__);
	bd->input = input_allocate_device();
	if (!bd->input) {
		TS_LOG_ERR("%s: Error, failed to allocate input device\n",
			   __func__);
		rc = -ENOSYS;
		goto error_alloc_failed;
	}

	if (bd->pdata->inp_dev_name)
		bd->input->name = bd->pdata->inp_dev_name;
	else
		bd->input->name = CYTTSP5_BTN_NAME;
	scnprintf(bd->phys, sizeof(bd->phys), "%s/input%d", dev_name(dev),
		  cd->phys_num++);
	bd->input->phys = bd->phys;
	bd->input->dev.parent = bd->dev;
	bd->input->open = cyttsp5_btn_open;
	bd->input->close = cyttsp5_btn_close;
	input_set_drvdata(bd->input, bd);

	/* get sysinfo */
	bd->si = _cyttsp5_request_sysinfo(dev);

	if (bd->si) {
		rc = cyttsp5_setup_input_device(dev);
		if (rc)
			goto error_init_input;
	} else {
		TS_LOG_ERR("%s: Fail get sysinfo pointer from core p=%p\n",
			   __func__, bd->si);
		_cyttsp5_subscribe_attention(dev, CY_ATTEN_STARTUP,
					     CY_MODULE_BTN,
					     cyttsp5_setup_input_attention, 0);
	}

	TS_LOG_INFO("%s: btn probe successful.\n", __func__);

	return 0;

error_init_input:
	input_free_device(bd->input);
error_alloc_failed:
error_no_pdata:
	TS_LOG_ERR("%s failed.\n", __func__);
	return rc;
}

int cyttsp5_btn_release(struct device *dev)
{
	struct cyttsp5_core_data *cd = dev_get_drvdata(dev);
	struct cyttsp5_btn_data *bd = &cd->bd;

	if (bd->input_device_registered) {
		input_unregister_device(bd->input);
	} else {
		input_free_device(bd->input);
		_cyttsp5_unsubscribe_attention(dev, CY_ATTEN_STARTUP,
					       CY_MODULE_BTN,
					       cyttsp5_setup_input_attention,
					       0);
	}

	return 0;
}
