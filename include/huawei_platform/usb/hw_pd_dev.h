

#ifndef __HW_PD_DEV_H__
#define __HW_PD_DEV_H__

#include <linux/device.h>
#include <linux/hisi/usb/hisi_usb.h>
#include <huawei_platform/log/hw_log.h>
#include <linux/completion.h>

#define CONFIG_DPM_USB_PD_CUSTOM_DBGACC
#define CONFIG_DPM_TYPEC_CAP_DBGACC_SNK
#define CONFIG_DPM_TYPEC_CAP_CUSTOM_SRC

/* type-c inserted plug orientation */
enum pd_cc_orient{
    PD_CC_ORIENT_DEFAULT = 0,
    PD_CC_ORIENT_CC1,
    PD_CC_ORIENT_CC2,
    PD_CC_NOT_READY,
};

enum pd_connect_result {
    PD_CONNECT_NONE = 0,
    PD_CONNECT_TYPEC_ONLY,
    PD_CONNECT_TYPEC_ONLY_SNK_DFT,
    PD_CONNECT_TYPEC_ONLY_SNK,
    PD_CONNECT_TYPEC_ONLY_SRC,
    PD_CONNECT_PE_READY,
    PD_CONNECT_PE_READY_SNK,
    PD_CONNECT_PE_READY_SRC,

#ifdef CONFIG_DPM_USB_PD_CUSTOM_DBGACC
	PD_CONNECT_PE_READY_DBGACC_UFP,
	PD_CONNECT_PE_READY_DBGACC_DFP,
#endif	/* CONFIG_USB_PD_CUSTOM_DBGACC */
};

enum pd_device_port_power_mode{
    PD_DEV_PORT_POWERMODE_SOURCE = 0,
    PD_DEV_PORT_POWERMODE_SINK,
    PD_DEV_PORT_POWERMODE_NOT_READY,
};

enum pd_device_port_data_mode{
    PD_DEV_PORT_DATAMODE_HOST = 0,
    PD_DEV_PORT_DATAMODE_DEVICE,
    PD_DEV_PORT_DATAMODE_NOT_READY,
};

enum pd_device_port_mode{
    PD_DEV_PORT_MODE_DFP = 0,
    PD_DEV_PORT_MODE_UFP,
    PD_DEV_PORT_MODE_NOT_READY,
};

enum {
    PD_DPM_PE_EVT_DIS_VBUS_CTRL,
    PD_DPM_PE_EVT_SOURCE_VCONN,
    PD_DPM_PE_EVT_SOURCE_VBUS,
    PD_DPM_PE_EVT_SINK_VBUS,
    PD_DPM_PE_EVT_PR_SWAP,
    PD_DPM_PE_EVT_DR_SWAP,
    PD_DPM_PE_EVT_VCONN_SWAP,
    PD_DPM_PE_EVT_TYPEC_STATE,
    PD_DPM_PE_EVT_PD_STATE,
    PD_DPM_PE_EVT_BC12,
};

enum pd_typec_attach_type {
    PD_DPM_TYPEC_UNATTACHED = 0,
    PD_DPM_TYPEC_ATTACHED_SNK,
    PD_DPM_TYPEC_ATTACHED_SRC,
    PD_DPM_TYPEC_ATTACHED_AUDIO,
    PD_DPM_TYPEC_ATTACHED_DEBUG,

#ifdef CONFIG_DPM_TYPEC_CAP_DBGACC_SNK
	PD_DPM_TYPEC_ATTACHED_DBGACC_SNK,		/* Rp, Rp */
#endif	/* CONFIG_TYPEC_CAP_DBGACC_SNK */

#ifdef CONFIG_DPM_TYPEC_CAP_CUSTOM_SRC
	PD_DPM_TYPEC_ATTACHED_CUSTOM_SRC,		/* Same Rp */
#endif	/* CONFIG_TYPEC_CAP_CUSTOM_SRC */
};

enum pd_dpm_charger_event_type {
    PD_EVENT_CHARGER_TYPE_USB = 0,	/*SDP*/
    PD_EVENT_CHARGER_TYPE_BC_USB,	/*CDP*/
    PD_EVENT_CHARGER_TYPE_NON_STANDARD,	/*UNKNOW*/
    PD_EVENT_CHARGER_TYPE_STANDARD,	/*DCP*/
    PD_EVENT_CHARGER_TYPE_FCP,	/*FCP*/
};

enum {
        PD_DPM_USB_TYPEC_NONE = 0,
        PD_DPM_USB_TYPEC_DETACHED,
        PD_DPM_USB_TYPEC_DEVICE_ATTACHED,
        PD_DPM_USB_TYPEC_HOST_ATTACHED,
};

enum pd_dpm_uevent_type {
    PD_DPM_UEVENT_START = 0,
    PD_DPM_UEVENT_COMPLETE,
};

enum pd_dpm_wake_lock_type {
    PD_WAKE_LOCK = 100,
    PD_WAKE_UNLOCK,
};

struct pd_dpm_typec_state {
    bool polarity;
    int cc1_status;
    int cc2_status;
    int old_state;
    int new_state;
};

struct pd_dpm_pd_state {
	uint8_t connected;
};

struct pd_dpm_swap_state {
	uint8_t new_role;
};

enum pd_dpm_vbus_type {
    PD_DPM_VBUS_TYPE_TYPEC = 20,
    PD_DPM_VBUS_TYPE_PD,
};

struct pd_dpm_vbus_state {
    int mv;
    int ma;
    uint8_t vbus_type;
    bool ext_power;
};

struct pd_dpm_info{
    struct i2c_client *client;
    struct device *dev;
    struct mutex pd_lock;
    struct mutex sink_vbus_lock;

    struct dual_role_phy_instance *dual_role;
    struct dual_role_phy_desc *desc;

    enum hisi_charger_type charger_type;
    struct notifier_block usb_nb;
    struct notifier_block chrg_wake_unlock_nb;
    struct atomic_notifier_head pd_evt_nh;
    struct atomic_notifier_head pd_wake_unlock_evt_nh;

    enum pd_dpm_uevent_type uevent_type;
    struct work_struct pd_work;
    struct work_struct recovery_work;

    const char *tcpc_name;

	/* usb state update */
    struct mutex usb_lock;
    int pending_usb_event;
    int last_usb_event;
    struct workqueue_struct *usb_wq;
    struct delayed_work usb_state_update_work;

	

    bool bc12_finish_flag;
    bool pd_finish_flag;
    bool pd_source_vbus;
    unsigned long bc12_event;
    struct pd_dpm_vbus_state bc12_sink_vbus_state;
};

struct cc_check_ops {
	int (*is_cable_for_direct_charge)(void);
};
int cc_check_ops_register(struct cc_check_ops*);

/* for chip layer to get class created by core layer */
struct class *hw_pd_get_class(void);

extern struct tcpc_device *tcpc_dev_get_by_name(const char *name);

extern int register_pd_dpm_notifier(struct notifier_block *nb);
extern int unregister_pd_dpm_notifier(struct notifier_block *nb);
extern int register_pd_wake_unlock_notifier(struct notifier_block *nb);
extern int unregister_pd_wake_unlock_notifier(struct notifier_block *nb);
extern int pd_dpm_handle_pe_event(unsigned long event, void *data);
extern bool pd_dpm_get_pd_finish_flag(void);
extern bool pd_dpm_get_pd_source_vbus(void);
extern void pd_dpm_get_typec_state(int *typec_detach);
extern void pd_dpm_get_charge_event(unsigned long *event, struct pd_dpm_vbus_state *state);
extern bool pd_dpm_get_high_power_charging_status(void);
#endif
