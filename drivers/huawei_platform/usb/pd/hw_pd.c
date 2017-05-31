/************************************************************
*
* Copyright (C), 1988-1999, Huawei Tech. Co., Ltd.
* FileName: hw_typec.c
* Author: suoandajie(00318894)       Version : 0.1      Date:  2016-5-9
*
* This software is licensed under the terms of the GNU General Public
* License version 2, as published by the Free Software Foundation, and
* may be copied, distributed, and modified under those terms.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
*  Description:    .c file for type-c core layer which is used to handle
*                  pulic logic management for different chips and to
*                  provide interfaces for exteranl modules.
*  Version:
*  Function List:
*  History:
*  <author>  <time>   <version >   <desc>
***********************************************************/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/jiffies.h>
#include <linux/wakelock.h>
#include <linux/io.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/notifier.h>
#include <linux/mutex.h>
#include <linux/version.h>
#include <huawei_platform/log/hw_log.h>
#include <huawei_platform/usb/hw_pd_dev.h>
#include <linux/hisi/usb/hisi_usb.h>
#include "../switch/switch_usb_class.h"
#include <linux/usb/class-dual-role.h>
#include <huawei_platform/usb/pd/richtek/tcpm.h>
#include <huawei_platform/power/direct_charger.h>

struct pd_dpm_info *g_pd_di = NULL;
static bool g_pd_cc_orientation = false;
static struct class *typec_class = NULL;
static struct device *typec_dev = NULL;
static struct mutex dpm_sink_vbus_lock;
static int pd_dpm_typec_state = PD_DPM_USB_TYPEC_DETACHED;
static struct pd_dpm_vbus_state g_vbus_state;
static unsigned long g_charger_type_event;
struct completion pd_get_typec_state_completion;
static bool g_pd_high_power_charging_status = false;
struct cc_check_ops* g_cc_check_ops;

#ifndef HWLOG_TAG
#define HWLOG_TAG huawei_pd
HWLOG_REGIST();
#endif
bool pd_dpm_get_high_power_charging_status()
{
	hwlog_info("%s status =%d\n", __func__, g_pd_high_power_charging_status);
	return g_pd_high_power_charging_status;
}
void pd_dpm_set_high_power_charging_status(bool status)
{
	hwlog_info("%s status =%d\n", __func__, status);
	g_pd_high_power_charging_status = status;
}

void pd_dpm_get_charge_event(unsigned long *event, struct pd_dpm_vbus_state *state)
{
        hwlog_info("%s event =%d\n", __func__, g_charger_type_event);
	*event = g_charger_type_event;
	memcpy(state, &g_vbus_state, sizeof(struct pd_dpm_vbus_state));
}

static void pd_dpm_set_charge_event(unsigned long event, struct pd_dpm_vbus_state *state)
{
        hwlog_info("%s event =%d\n", __func__, event);
	if(NULL != state)
		memcpy(&g_vbus_state, state, sizeof(struct pd_dpm_vbus_state));
	g_charger_type_event = event;
}

int cc_check_ops_register(struct cc_check_ops* ops)
{
	int ret = 0;
	if (ops != NULL)
	{
		g_cc_check_ops = ops;
	}
	else
	{
		hwlog_err("cc_check ops register fail!\n");
		ret = -EPERM;
	}
	return ret;
}
static int direct_charge_cable_detect(void)
{
	int ret;
	if (NULL == g_cc_check_ops)
	{
		return -1;
	}
	ret = g_cc_check_ops -> is_cable_for_direct_charge();
	if (ret)
	{
		hwlog_info("%s:cc_check  fail!\n",__func__);
		return -1;
	}
	return 0;
}
static struct direct_charge_cable_detect_ops cable_detect_ops = {
	.direct_charge_cable_detect = direct_charge_cable_detect,
};
static bool pd_dpm_get_cc_orientation(void)
{
	hwlog_info("%s cc_orientation =%d\n", __func__, g_pd_cc_orientation);
	return g_pd_cc_orientation;
}

static void pd_dpm_set_cc_orientation(bool cc_orientation)
{
	hwlog_info("%s cc_orientation =%d\n", __func__, cc_orientation);
	g_pd_cc_orientation = cc_orientation;
}

void pd_dpm_get_typec_state(int *typec_state)
{
	hwlog_info("%s pd_dpm_get_typec_state  = %d\n", __func__, pd_dpm_typec_state);

	*typec_state = pd_dpm_typec_state;

	return ;
}

static void pd_dpm_set_typec_state(int typec_state)
{
        hwlog_info("%s pd_dpm_set_typec_state  = %d\n", __func__, typec_state);

	pd_dpm_typec_state = typec_state;

	return ;
}


static ssize_t pd_dpm_cc_orientation_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
	return scnprintf(buf, PAGE_SIZE, "%s\n", pd_dpm_get_cc_orientation()? "2" : "1");
}

static ssize_t pd_dpm_pd_state_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
	hwlog_info("%s  = %d\n", __func__, pd_dpm_get_pd_finish_flag());
	return scnprintf(buf, PAGE_SIZE, "%s\n", pd_dpm_get_pd_finish_flag()? "0" : "1");
}

static DEVICE_ATTR(cc_orientation, S_IRUGO, pd_dpm_cc_orientation_show, NULL);
static DEVICE_ATTR(pd_state, S_IRUGO, pd_dpm_pd_state_show, NULL);

static struct attribute *pd_dpm_ctrl_attributes[] = {
	&dev_attr_cc_orientation.attr,
	&dev_attr_pd_state.attr,
	NULL,
};

static const struct attribute_group pd_dpm_attr_group = {
	.attrs = pd_dpm_ctrl_attributes,
};

static enum dual_role_property pd_dualrole_properties[] = {
	DUAL_ROLE_PROP_MODE,
	DUAL_ROLE_PROP_PR,
	DUAL_ROLE_PROP_DR,
};

static int dual_role_get_local_prop(struct dual_role_phy_instance *dual_role,
				    enum dual_role_property prop,
				    unsigned int *val)
{
	struct pd_dpm_info *di = dual_role_get_drvdata(dual_role);
	int port_mode = 0;

	if (!di)
		return -EINVAL;

	if (prop == DUAL_ROLE_PROP_PR)
	{
		//port_mode = pd_detect_port_power_mode();
		if (port_mode == PD_DEV_PORT_POWERMODE_SOURCE)
			*val = DUAL_ROLE_PROP_PR_SRC;
		else if (port_mode == PD_DEV_PORT_POWERMODE_SINK)
			*val = DUAL_ROLE_PROP_PR_SNK;
		else
			*val = DUAL_ROLE_PROP_MODE_NONE;
	}
	else  if (prop == DUAL_ROLE_PROP_DR)
	{
		//port_mode = pd_detect_port_data_mode();
		if (port_mode == PD_DEV_PORT_DATAMODE_HOST)
			*val = DUAL_ROLE_PROP_DR_HOST;
		else if (port_mode == PD_DEV_PORT_DATAMODE_DEVICE)
			*val = DUAL_ROLE_PROP_DR_DEVICE;
		else
			*val = DUAL_ROLE_PROP_MODE_NONE;
	}
	else
	{
		//port_mode = pd_detect_port_power_mode();
		if (port_mode == PD_DEV_PORT_POWERMODE_SOURCE)
			*val = DUAL_ROLE_PROP_MODE_DFP;
		else if (port_mode == PD_DEV_PORT_POWERMODE_SINK)
			*val = DUAL_ROLE_PROP_MODE_UFP;
		else
			*val = DUAL_ROLE_PROP_MODE_NONE;
	}

	return 0;
}

/* Decides whether userspace can change a specific property */
static int dual_role_is_writeable(struct dual_role_phy_instance *drp,
				  enum dual_role_property prop)
{
	if (prop == DUAL_ROLE_PROP_PR || prop == DUAL_ROLE_PROP_DR)
		return 1;
	else
		return 0;
}

static int dual_role_set_pr_prop(struct dual_role_phy_instance *dual_role,
                                   enum dual_role_property prop,
                                   const unsigned int *val)
{
	//TODO set current pr && send pr_swap
	//should supply the register function to call pr_swap
}

static int dual_role_set_dr_prop(struct dual_role_phy_instance *dual_role,
                                   enum dual_role_property prop,
                                   const unsigned int *val)
{
	//TODO set current dr  && send dr_swap
	//should supply the register function to call pr_swap
}

static int dual_role_set_mode_prop(struct dual_role_phy_instance *dual_role,
				   enum dual_role_property prop,
				   const unsigned int *val)
{
	struct pd_dpm_info *di = dual_role_get_drvdata(dual_role);
	int port_mode = 0;
	unsigned int power_mode = 0;
	unsigned int data_mode = 0;
	int timeout = 0;
	int ret = 0;

	if (!di)
		return -EINVAL;

	if (*val != DUAL_ROLE_PROP_MODE_DFP && *val != DUAL_ROLE_PROP_MODE_UFP)
		return -EINVAL;

	//TODO  detect current port mode

	if (port_mode != PD_DEV_PORT_MODE_DFP
		&& port_mode != PD_DEV_PORT_MODE_UFP)
		return 0;

	if (port_mode == PD_DEV_PORT_MODE_DFP
		&& *val == DUAL_ROLE_PROP_MODE_DFP)
		return 0;

	if (port_mode == PD_DEV_PORT_MODE_UFP
		&& *val == DUAL_ROLE_PROP_MODE_UFP)
		return 0;

	if (port_mode == PD_DEV_PORT_MODE_DFP) {
		power_mode = PD_DEV_PORT_POWERMODE_SOURCE;
		data_mode = PD_DEV_PORT_DATAMODE_HOST;
	} else if (port_mode == PD_DEV_PORT_MODE_UFP) {
		power_mode = PD_DEV_PORT_POWERMODE_SINK;
		data_mode = PD_DEV_PORT_DATAMODE_DEVICE;
	}

	dual_role_set_pr_prop(dual_role,DUAL_ROLE_PROP_PR,&power_mode);
	dual_role_set_dr_prop(dual_role,DUAL_ROLE_PROP_DR,&data_mode);

	if (di->dual_role) {
		dual_role_instance_changed(di->dual_role);
	}

	return ret;
}

static int dual_role_set_prop(struct dual_role_phy_instance *dual_role,
			      enum dual_role_property prop,
			      const unsigned int *val)
{
	if (prop == DUAL_ROLE_PROP_PR)
		return dual_role_set_pr_prop(dual_role, prop, val);
	else if (prop == DUAL_ROLE_PROP_DR)
		return dual_role_set_dr_prop(dual_role, prop, val);
	else if (prop == DUAL_ROLE_PROP_MODE)
		return dual_role_set_mode_prop(dual_role, prop, val);
	else
		return -EINVAL;
}

int pd_dpm_wake_unlock_notifier_call(struct pd_dpm_info *di, unsigned long event, void *data)
{
        return atomic_notifier_call_chain(&di->pd_wake_unlock_evt_nh,event, data);
}

int pd_dpm_vbus_notifier_call(struct pd_dpm_info *di, unsigned long event, void *data)
{
	if(CHARGER_TYPE_NONE == event)
		pd_dpm_set_high_power_charging_status(false);
	pd_dpm_set_charge_event(event, data);
	return atomic_notifier_call_chain(&di->pd_evt_nh,event, data);
}
static int charge_wake_unlock_notifier_call(struct notifier_block *chrg_wake_unlock_nb,
				      unsigned long event, void *data)
{
	if (g_pd_di)
		pd_dpm_wake_unlock_notifier_call(g_pd_di, PD_WAKE_UNLOCK, NULL);

	return NOTIFY_OK;
}

bool pd_dpm_get_pd_finish_flag(void)
{
	if (g_pd_di)
		return g_pd_di->pd_finish_flag;
	else
		return false;
}

bool pd_dpm_get_pd_source_vbus(void)
{
	if (g_pd_di)
		return g_pd_di->pd_source_vbus;
	else
		return false;
}

static void pd_dpm_recovery_work(struct work_struct *work)
{
	int typec_state = PD_DPM_USB_TYPEC_DETACHED;

	hwlog_info("%s + \n", __func__);

	while (true == pd_dpm_get_pd_source_vbus())
	{
		msleep(1000);
		pd_dpm_get_typec_state(&typec_state);
		if (PD_DPM_USB_TYPEC_DEVICE_ATTACHED == typec_state)
		{
			hwlog_info("%s PD_DPM_USB_TYPEC_DEVICE_ATTACHED \n", __func__);
			hisi_usb_otg_event(CHARGER_DISCONNECT_EVENT);
			hisi_usb_otg_event(CHARGER_CONNECT_EVENT);

			if (g_pd_di)
				g_pd_di->pd_source_vbus = false;
			break;
		}
	};

	hwlog_info("%s - \n", __func__);
}

void pd_dpm_report_pd_source_vbus(struct pd_dpm_info *di, void *data)
{
	struct pd_dpm_vbus_state *vbus_state = data;

	mutex_lock(&di->sink_vbus_lock);

	if (vbus_state->vbus_type & TCP_VBUS_CTRL_PD_DETECT)
		di->pd_finish_flag = true;

	if (vbus_state->mv == 0) {
		hwlog_info("%s : Disable\n", __func__);
		pd_dpm_vbus_notifier_call(g_pd_di, CHARGER_TYPE_NONE, data);
	} else {
		di->pd_source_vbus = true;
		hwlog_info("%s : Source %d mV, %d mA\n", __func__, vbus_state->mv, vbus_state->ma);
		pd_dpm_vbus_notifier_call(g_pd_di, PLEASE_PROVIDE_POWER, data);
		schedule_work(&di->recovery_work);
	}
	mutex_unlock(&di->sink_vbus_lock);
}

void pd_dpm_report_pd_sink_vbus(struct pd_dpm_info *di, void *data)
{
	bool skip = false;
	bool high_power_charging = false;
	unsigned long event;
	struct pd_dpm_vbus_state *vbus_state = data;

	mutex_lock(&di->sink_vbus_lock);

	if (vbus_state->vbus_type & TCP_VBUS_CTRL_PD_DETECT)
		di->pd_finish_flag = true;

	if (di->pd_finish_flag) {
		event = PD_DPM_VBUS_TYPE_PD;
	} else if (di->bc12_finish_flag) {
		skip = true;
	} else {
		event = PD_DPM_VBUS_TYPE_TYPEC;
	}

	if (!skip) {
		vbus_state = data;

		if (vbus_state->mv == 0) {
			if(event == PD_DPM_VBUS_TYPE_PD)
			{
				hwlog_info("%s : Disable\n", __func__);
				pd_dpm_vbus_notifier_call(g_pd_di, CHARGER_TYPE_NONE, data);
			}
		}
		else {
			di->pd_source_vbus = false;
			hwlog_info("%s : Sink %d mV, %d mA\n", __func__, vbus_state->mv, vbus_state->ma);
			if((vbus_state->mv * vbus_state->ma) >= 18000000)
			{
				hwlog_info("%s : over 18w\n", __func__);
				high_power_charging = true;
			}
			hwlog_info("%s : %d\n", __func__, vbus_state->mv * vbus_state->ma);
			pd_dpm_set_high_power_charging_status(high_power_charging);
			pd_dpm_vbus_notifier_call(g_pd_di, event, data);
		}
	} else {
		hwlog_info("%s : skip\n", __func__);
	}

	mutex_unlock(&di->sink_vbus_lock);
}

int pd_dpm_report_bc12(struct notifier_block *usb_nb,
                                    unsigned long event, void *data)
{
	struct pd_dpm_vbus_state *vbus_state = data;
	struct pd_dpm_info *di = container_of(usb_nb, struct pd_dpm_info, usb_nb);

	hwlog_info("%s : event (%d)\n", __func__, event);

	if(CHARGER_TYPE_NONE == event && !di->pd_finish_flag && 
		!pd_dpm_get_pd_source_vbus())
	{
		di->bc12_finish_flag = false;
		hwlog_info("%s : PD_WAKE_UNLOCK \n", __func__);
		pd_dpm_wake_unlock_notifier_call(g_pd_di, PD_WAKE_UNLOCK, NULL);
	}

	if(PLEASE_PROVIDE_POWER == event)
		return NOTIFY_OK;


	if(pd_dpm_get_pd_source_vbus())
	{
		hwlog_info("%s : line (%d)\n", __func__, __LINE__);
		return NOTIFY_OK;
	}

	if (!di->pd_finish_flag) {
		hwlog_info("%s : event (%d)\n", __func__, event);
		pd_dpm_vbus_notifier_call(di,event,data);
	} else
		hwlog_info("%s : igrone\n", __func__);

	return NOTIFY_OK;
}

int register_pd_wake_unlock_notifier(struct notifier_block *nb)
{
        int ret = 0;

        if (!nb)
                return -EINVAL;

        if(g_pd_di == NULL)
                return ret;

        ret = atomic_notifier_chain_register(&g_pd_di->pd_wake_unlock_evt_nh, nb);
        if (ret != 0)
                return ret;

        return ret;
}
EXPORT_SYMBOL(register_pd_wake_unlock_notifier);

int unregister_pd_wake_unlock_notifier(struct notifier_block *nb)
{
        return atomic_notifier_chain_unregister(&g_pd_di->pd_wake_unlock_evt_nh, nb);
}
EXPORT_SYMBOL(unregister_pd_wake_unlock_notifier);

int register_pd_dpm_notifier(struct notifier_block *nb)
{
	int ret = 0;

	if (!nb)
		return -EINVAL;

	if(g_pd_di == NULL)
		return ret;

	ret = atomic_notifier_chain_register(&g_pd_di->pd_evt_nh, nb);
	if (ret != 0)
		return ret;

	return ret;
}
EXPORT_SYMBOL(register_pd_dpm_notifier);

int unregister_pd_dpm_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_unregister(&g_pd_di->pd_evt_nh, nb);
}
EXPORT_SYMBOL(unregister_pd_dpm_notifier);


static inline void pd_dpm_report_device_attach(void)
{
	hwlog_info("%s \r\n",__func__);
	if (pd_dpm_get_pd_finish_flag())
	{
		hwlog_info("%s, in pd process, report charger connect event\n",__func__);
		hisi_usb_otg_event(CHARGER_CONNECT_EVENT);
	}
}

static inline void pd_dpm_report_host_attach(void)
{
	hwlog_info("%s \r\n",__func__);
	fsa9685_dcd_timeout_enable(true);
	fsa9685_manual_sw(FSA9685_USB1_ID_TO_IDBYPASS);
	hisi_usb_otg_event(ID_FALL_EVENT);
}

static inline void pd_dpm_report_device_detach(void)
{
	hwlog_info("%s \r\n",__func__);
	complete(&pd_get_typec_state_completion);

	if (pd_dpm_get_pd_finish_flag())
	{
		hwlog_info("%s, in pd process, report charger connect event\n",__func__);
		hisi_usb_otg_event(CHARGER_DISCONNECT_EVENT);
		pd_dpm_vbus_notifier_call(g_pd_di, CHARGER_TYPE_NONE, NULL);
	}
}

static inline void pd_dpm_report_host_detach(void)
{
	hwlog_info("%s \r\n",__func__);
	fsa9685_dcd_timeout_enable(false);
	hisi_usb_otg_event(ID_RISE_EVENT);
}

static void pd_dpm_report_attach(int new_state)
{
	switch (new_state) {
	case PD_DPM_USB_TYPEC_DEVICE_ATTACHED:
		pd_dpm_report_device_attach();
		break;

	case PD_DPM_USB_TYPEC_HOST_ATTACHED:
		pd_dpm_report_host_attach();
		break;
	}
}

static void pd_dpm_report_detach(int last_state)
{
	switch (last_state) {
	case PD_DPM_USB_TYPEC_DEVICE_ATTACHED:
		pd_dpm_report_device_detach();
		break;

	case PD_DPM_USB_TYPEC_HOST_ATTACHED:
		pd_dpm_report_host_detach();
		break;
	}
}

static void pd_dpm_usb_update_state(
				struct work_struct *work)
{
	int new_ev, last_ev;
	struct pd_dpm_info *usb_cb_data =
			container_of(to_delayed_work(work),
					struct pd_dpm_info,
					usb_state_update_work);

	mutex_lock(&usb_cb_data->usb_lock);
	new_ev = usb_cb_data->pending_usb_event;
	mutex_unlock(&usb_cb_data->usb_lock);

	last_ev = usb_cb_data->last_usb_event;

	if (last_ev == new_ev)
		return;

	switch (new_ev) {
	case PD_DPM_USB_TYPEC_DETACHED:
		pd_dpm_report_detach(last_ev);
		break;

	case PD_DPM_USB_TYPEC_DEVICE_ATTACHED:
	case PD_DPM_USB_TYPEC_HOST_ATTACHED:
		if (last_ev != PD_DPM_USB_TYPEC_DETACHED)
			pd_dpm_report_detach(last_ev);
		pd_dpm_report_attach(new_ev);
		break;
	default:
		return;
	}

	usb_cb_data->last_usb_event = new_ev;
}

int pd_dpm_handle_pe_event(unsigned long event, void *data)
{
	bool attach_event = false;
	int usb_event = PD_DPM_USB_TYPEC_NONE;
	struct pd_dpm_typec_state *typec_state = NULL;

	switch (event) {

	case PD_DPM_PE_EVT_TYPEC_STATE:
		{
			typec_state = data;
			switch (typec_state->new_state) {
			case PD_DPM_TYPEC_ATTACHED_SNK:
				attach_event = true;
				usb_event = PD_DPM_USB_TYPEC_DEVICE_ATTACHED;
				break;

			case PD_DPM_TYPEC_ATTACHED_SRC:
				attach_event = true;
				usb_event = PD_DPM_USB_TYPEC_HOST_ATTACHED;
				break;

			case PD_DPM_TYPEC_UNATTACHED:
				mutex_lock(&g_pd_di->sink_vbus_lock);
				g_pd_di->bc12_finish_flag = false;
				mutex_unlock(&g_pd_di->sink_vbus_lock);
				usb_event = PD_DPM_USB_TYPEC_DETACHED;
				break;

			default:
				hwlog_info("%s can not detect typec state\r\n", __func__);
				break;
			}
			pd_dpm_set_typec_state(usb_event);
		}
		break;

	case PD_DPM_PE_EVT_PD_STATE:
		{
			struct pd_dpm_pd_state *pd_state = data;
			switch (pd_state->connected) {
			case PD_CONNECT_PE_READY_SNK:
			case PD_CONNECT_PE_READY_SRC:
				break;
			}
		}
		break;

	case PD_DPM_PE_EVT_DIS_VBUS_CTRL:
		{
			if(g_pd_di->pd_finish_flag == true || pd_dpm_get_pd_source_vbus())
			{
				struct pd_dpm_vbus_state vbus_state;
				hwlog_info("%s : Disable VBUS Control\n", __func__);
				vbus_state.mv = 0;
				vbus_state.ma = 0;

				mutex_lock(&g_pd_di->sink_vbus_lock);
				g_pd_di->pd_source_vbus = false;
				g_pd_di->pd_finish_flag = false;
				mutex_unlock(&g_pd_di->sink_vbus_lock);
				pd_dpm_vbus_notifier_call(g_pd_di, CHARGER_TYPE_NONE, &vbus_state);
			}
		}
		break;

	case PD_DPM_PE_EVT_SINK_VBUS:
		{
			pd_dpm_report_pd_sink_vbus(g_pd_di, data);
		}
		break;

	case PD_DPM_PE_EVT_SOURCE_VBUS:
		{
			pd_dpm_report_pd_source_vbus(g_pd_di, data);
		}
		break;

	case PD_DPM_PE_EVT_DR_SWAP:
		{
			struct pd_dpm_swap_state *swap_state = data;
			if (swap_state->new_role == PD_ROLE_DFP)
				usb_event = PD_DPM_USB_TYPEC_HOST_ATTACHED;
			else
				usb_event = PD_DPM_USB_TYPEC_DEVICE_ATTACHED;
		}
		break;

	case PD_DPM_PE_EVT_PR_SWAP:
		break;

	default:
		hwlog_info("%s  unkonw event \r\n", __func__);
		break;
	};


	if (attach_event) {
		pd_dpm_set_cc_orientation(typec_state->polarity);
	}

	if (usb_event != PD_DPM_USB_TYPEC_NONE) {
		mutex_lock(&g_pd_di->usb_lock);
		if (g_pd_di->pending_usb_event != usb_event) {
		cancel_delayed_work(&g_pd_di->usb_state_update_work);
		g_pd_di->pending_usb_event = usb_event;
		queue_delayed_work(g_pd_di->usb_wq,
				&g_pd_di->usb_state_update_work,
				msecs_to_jiffies(0));
		} else
			pr_info("Pending event is same --> ignore this event %d\n", usb_event);
		mutex_unlock(&g_pd_di->usb_lock);
	}

	return 0;
}
EXPORT_SYMBOL_GPL(pd_dpm_handle_pe_event);

static int pd_dpm_parse_dt(struct pd_dpm_info *info,
	struct device *dev)
{
	struct device_node *np = dev->of_node;

	if (!np)
		return -EINVAL;
	// default name
	if (of_property_read_string(np, "tcp_name",
		&info->tcpc_name) < 0)
		info->tcpc_name = "type_c_port0";

	return 0;
}

static int pd_dpm_probe(struct platform_device *pdev)
{
	int ret = 0;
	struct pd_dpm_info *di;
	enum hisi_charger_type type;

	struct dual_role_phy_desc *desc;
	struct dual_role_phy_instance *dual_role;

	g_charger_type_event = hisi_get_charger_type();

	di = devm_kzalloc(&pdev->dev,sizeof(*di), GFP_KERNEL);
	di->dev = &pdev->dev;

	g_pd_di = di;
	mutex_init(&di->sink_vbus_lock);

#if 0
    desc = devm_kzalloc(&di->dev, sizeof(struct dual_role_phy_desc), GFP_KERNEL);
    if (!desc) {
        hwlog_err("unable to allocate dual role descriptor\n");
        return NULL;
    }

    desc->name = "otg_default";
    desc->supported_modes = DUAL_ROLE_SUPPORTED_MODES_DFP_AND_UFP;
    desc->get_property = dual_role_get_local_prop;
    desc->set_property = dual_role_set_prop;
    desc->properties = pd_dualrole_properties;
    desc->num_properties = ARRAY_SIZE(pd_dualrole_properties);
    desc->property_is_writeable = dual_role_is_writeable;
    dual_role =
        devm_dual_role_instance_register(di->dev, desc);
    dual_role->drv_data = di;
    di->dual_role = dual_role;
    di->desc = desc;
#endif

	ATOMIC_INIT_NOTIFIER_HEAD(&di->pd_evt_nh);
	ATOMIC_INIT_NOTIFIER_HEAD(&di->pd_wake_unlock_evt_nh);

	di->usb_nb.notifier_call = pd_dpm_report_bc12;
	ret = hisi_charger_type_notifier_register(&di->usb_nb);
	if (ret < 0) {
		hwlog_err("hisi_charger_type_notifier_register failed\n");
	}
	di->chrg_wake_unlock_nb.notifier_call = charge_wake_unlock_notifier_call;
	ret = blocking_notifier_chain_register(&charge_wake_unlock_list, &di->chrg_wake_unlock_nb);
	if (ret < 0) {
		hwlog_err("charge_wake_unlock_register_notifier failed\n");
	}

	//adjust the typec  product
        typec_class = class_create(THIS_MODULE, "hw_typec");
        if (IS_ERR(typec_class)) {
                hwlog_err("%s: cannot create class\n", __func__);
                return PTR_ERR(typec_class);
        }

	if (typec_class) {
		typec_dev = device_create(typec_class, NULL, 0, NULL, "typec");
		ret = sysfs_create_group(&typec_dev->kobj, &pd_dpm_attr_group);
		if (ret) {
			hwlog_err("%s: typec sysfs group create error\n", __func__);
		}
	}

	hwlog_info("pd_dpm_probe++++\r\n\r\n");

	di->last_usb_event = PD_DPM_USB_TYPEC_NONE;
	di->pending_usb_event = PD_DPM_USB_TYPEC_NONE;

	mutex_init(&di->usb_lock);

	di->usb_wq = create_workqueue("pd_dpm_usb_wq");
	INIT_DELAYED_WORK(&di->usb_state_update_work,
		pd_dpm_usb_update_state);
	INIT_WORK(&di->recovery_work, pd_dpm_recovery_work);

	platform_set_drvdata(pdev, di);

	pd_dpm_parse_dt(di, &pdev->dev);
	notify_tcp_dev_ready(di->tcpc_name);

	type = hisi_get_charger_type();
	if(CHARGER_TYPE_NONE != type && PLEASE_PROVIDE_POWER != type)
	{
		di->bc12_finish_flag = true;
	}

	hwlog_info("%s:  bc12 type = %d \n", __func__, type);

	init_completion(&pd_get_typec_state_completion);

	di->bc12_event = type;
	cable_detect_ops_register(&cable_detect_ops);
	return ret;
}
EXPORT_SYMBOL_GPL(pd_dpm_probe);

static const struct of_device_id pd_dpm_callback_match_table[] = {
	{.compatible = "huawei,pd_dpm",},
	{},
};

static struct platform_driver pd_dpm_callback_driver = {
	.probe		= pd_dpm_probe,
	.remove		= NULL,
	.driver		= {
		.name	= "huawei,pd_dpm",
		.owner	= THIS_MODULE,
		.of_match_table = pd_dpm_callback_match_table,
	}
};

static int __init pd_dpm_init(void)
{
	hwlog_info("%s \n", __func__);

	return platform_driver_register(&pd_dpm_callback_driver);
}

static void __exit pd_dpm_exit(void)
{
	platform_driver_unregister(&pd_dpm_callback_driver);
}

device_initcall(pd_dpm_init);
module_exit(pd_dpm_exit);
MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("huawei pd dpm");
MODULE_AUTHOR("SuoAnDaJie<suoandajie@huawei.com>");
