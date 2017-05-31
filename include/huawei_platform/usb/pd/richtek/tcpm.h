/*
 * Copyright (C) 2016 Richtek Technology Corp.
 *
 * Author: TH <tsunghan_tsai@richtek.com>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#ifndef TCPM_H_
#define TCPM_H_

#include <linux/kernel.h>
#include <linux/notifier.h>

#include <huawei_platform/usb/pd/richtek/tcpci_config.h>

#include <huawei_platform/usb/hw_pd_dev.h>
#include <huawei_platform/log/hw_log.h>

#ifndef HWLOG_TAG
#define HWLOG_TAG huawei_pd
HWLOG_REGIST();
#endif

struct tcpc_device;

/*
 * Type-C Port Notify Chain
 */

enum typec_attach_type {
	TYPEC_UNATTACHED = 0,
	TYPEC_ATTACHED_SNK,
	TYPEC_ATTACHED_SRC,
	TYPEC_ATTACHED_AUDIO,
	TYPEC_ATTACHED_DEBUG,

#ifdef CONFIG_TYPEC_CAP_DBGACC_SNK
	TYPEC_ATTACHED_DBGACC_SNK,		/* Rp, Rp */
#endif	/* CONFIG_TYPEC_CAP_DBGACC_SNK */

#ifdef CONFIG_TYPEC_CAP_CUSTOM_SRC
	TYPEC_ATTACHED_CUSTOM_SRC,		/* Same Rp */
#endif	/* CONFIG_TYPEC_CAP_CUSTOM_SRC */
};

#if 0
enum pd_connect_result {
	PD_CONNECT_NONE = 0,
	PD_CONNECT_TYPEC_ONLY,	/* Internal Only */
	PD_CONNECT_TYPEC_ONLY_SNK_DFT,
	PD_CONNECT_TYPEC_ONLY_SNK,
	PD_CONNECT_TYPEC_ONLY_SRC,
	PD_CONNECT_PE_READY,	/* Internal Only */
	PD_CONNECT_PE_READY_SNK,
	PD_CONNECT_PE_READY_SRC,

#ifdef CONFIG_USB_PD_CUSTOM_DBGACC
	PD_CONNECT_PE_READY_DBGACC_UFP,
	PD_CONNECT_PE_READY_DBGACC_DFP,
#endif	/* CONFIG_USB_PD_CUSTOM_DBGACC */
};
#endif

enum dpm_request_state {

	DPM_REQ_NULL,
	DPM_REQ_QUEUE,
	DPM_REQ_RUNNING,
	DPM_REQ_SUCCESS,
	DPM_REQ_FAILED,

	/* Request failed */

	DPM_REQ_ERR_IDLE = DPM_REQ_FAILED,

	DPM_REQ_ERR_NOT_READY,
	DPM_REQ_ERR_WRONG_ROLE,

	DPM_REQ_ERR_RECV_HRESET,
	DPM_REQ_ERR_RECV_SRESET,
	DPM_REQ_ERR_SEND_HRESET,
	DPM_REQ_ERR_SEND_SRESET,
	DPM_REQ_ERR_SEND_BIST,

	/* Internal */
	DPM_REQ_SUCCESS_CODE,

	DPM_REQ_E_UVDM_ACK,
	DPM_REQ_E_UVDM_NAK,
};

/* Power role */
#define PD_ROLE_SINK   0
#define PD_ROLE_SOURCE 1

/* Data role */
#define PD_ROLE_UFP    0
#define PD_ROLE_DFP    1

/* Vconn role */
#define PD_ROLE_VCONN_OFF 0
#define PD_ROLE_VCONN_ON  1

enum {
	TCP_NOTIFY_DIS_VBUS_CTRL,
	TCP_NOTIFY_SOURCE_VCONN,
	TCP_NOTIFY_SOURCE_VBUS,
	TCP_NOTIFY_SINK_VBUS,
	TCP_NOTIFY_PR_SWAP,
	TCP_NOTIFY_DR_SWAP,
	TCP_NOTIFY_VCONN_SWAP,
	TCP_NOTIFY_ENTER_MODE,
	TCP_NOTIFY_EXIT_MODE,
	TCP_NOTIFY_AMA_DP_STATE,
	TCP_NOTIFY_AMA_DP_ATTENTION,
	TCP_NOTIFY_AMA_DP_HPD_STATE,

	TCP_NOTIFY_TYPEC_STATE,
	TCP_NOTIFY_PD_STATE,

#ifdef CONFIG_USB_PD_UVDM
	TCP_NOTIFY_UVDM,
#endif /* CONFIG_USB_PD_UVDM */

#ifdef CONFIG_USB_PD_ALT_MODE_RTDC
	TCP_NOTIFY_DC_EN_UNLOCK,
#endif	/* CONFIG_USB_PD_ALT_MODE_RTDC */

};

struct tcp_ny_pd_state {
	uint8_t connected;
};

struct tcp_ny_swap_state {
	uint8_t new_role;
};

struct tcp_ny_enable_state {
	bool en;
};

struct tcp_ny_typec_state {
	uint8_t rp_level;
	uint8_t polarity;
	uint8_t old_state;
	uint8_t new_state;
};

enum {
	TCP_VBUS_CTRL_REMOVE = 0,
	TCP_VBUS_CTRL_TYPEC = 1,
	TCP_VBUS_CTRL_PD = 2,

	TCP_VBUS_CTRL_HRESET = TCP_VBUS_CTRL_PD,
	TCP_VBUS_CTRL_PR_SWAP = 3,
	TCP_VBUS_CTRL_REQUEST = 4,
	TCP_VBUS_CTRL_STANDBY = 5,
	TCP_VBUS_CTRL_STANDBY_UP = 6,
	TCP_VBUS_CTRL_STANDBY_DOWN = 7,

	TCP_VBUS_CTRL_PD_DETECT = (1 << 7),

	TCP_VBUS_CTRL_PD_HRESET =
		TCP_VBUS_CTRL_HRESET | TCP_VBUS_CTRL_PD_DETECT,

	TCP_VBUS_CTRL_PD_PR_SWAP =
		TCP_VBUS_CTRL_PR_SWAP | TCP_VBUS_CTRL_PD_DETECT,

	TCP_VBUS_CTRL_PD_REQUEST =
		TCP_VBUS_CTRL_REQUEST | TCP_VBUS_CTRL_PD_DETECT,

	TCP_VBUS_CTRL_PD_STANDBY =
		TCP_VBUS_CTRL_STANDBY | TCP_VBUS_CTRL_PD_DETECT,

	TCP_VBUS_CTRL_PD_STANDBY_UP =
		TCP_VBUS_CTRL_STANDBY_UP | TCP_VBUS_CTRL_PD_DETECT,

	TCP_VBUS_CTRL_PD_STANDBY_DOWN =
		TCP_VBUS_CTRL_STANDBY_DOWN | TCP_VBUS_CTRL_PD_DETECT,
};

struct tcp_ny_vbus_state {
	int mv;
	int ma;
	uint8_t type;
};

struct tcp_ny_mode_ctrl {
	uint16_t svid;
	uint8_t ops;
	uint32_t mode;
};

enum {
	SW_USB = 0,
	SW_DFP_D,
	SW_UFP_D,
};

struct tcp_ny_ama_dp_state {
	uint8_t sel_config;
	uint8_t signal;
	uint8_t pin_assignment;
	uint8_t polarity;
	uint8_t active;
};

enum {
	TCP_DP_UFP_U_MASK = 0x7C,
	TCP_DP_UFP_U_POWER_LOW = 1 << 2,
	TCP_DP_UFP_U_ENABLED = 1 << 3,
	TCP_DP_UFP_U_MF_PREFER = 1 << 4,
	TCP_DP_UFP_U_USB_CONFIG = 1 << 5,
	TCP_DP_UFP_U_EXIT_MODE = 1 << 6,
};

struct tcp_ny_ama_dp_attention {
	uint8_t state;
};

struct tcp_ny_ama_dp_hpd_state {
	bool irq : 1;
	bool state : 1;
};

struct tcp_ny_uvdm {
	bool ack;
	uint8_t uvdm_cnt;
	uint16_t uvdm_svid;
	uint32_t *uvdm_data;
};

struct tcp_notify {
	union {
		struct tcp_ny_enable_state en_state;
		struct tcp_ny_vbus_state vbus_state;
		struct tcp_ny_typec_state typec_state;
		struct tcp_ny_swap_state swap_state;
		struct tcp_ny_pd_state pd_state;
		struct tcp_ny_mode_ctrl mode_ctrl;
		struct tcp_ny_ama_dp_state ama_dp_state;
		struct tcp_ny_ama_dp_attention ama_dp_attention;
		struct tcp_ny_ama_dp_hpd_state ama_dp_hpd_state;
		struct tcp_ny_uvdm uvdm_msg;
	};
};

extern struct tcpc_device
		*tcpc_dev_get_by_name(const char *name);

extern int register_tcp_dev_notifier(struct tcpc_device *tcp_dev,
				     struct notifier_block *nb);
extern int unregister_tcp_dev_notifier(struct tcpc_device *tcp_dev,
				       struct notifier_block *nb);

extern struct tcpc_device
		*notify_tcp_dev_ready(const char *name);

/*
 * Type-C Port Control I/F
 */

enum tcpm_error_list {
	TCPM_SUCCESS = 0,
	TCPM_ERROR_UNKNOWN = -1,
	TCPM_ERROR_UNATTACHED = -2,
	TCPM_ERROR_PARAMETER = -3,
	TCPM_ERROR_PUT_EVENT = -4,
	TCPM_ERROR_UNSUPPORT = -5,
	TCPM_ERROR_NO_PD_CONNECTED = -6,
	TCPM_ERROR_NO_POWER_CABLE = -7,
};

#define TCPM_PDO_MAX_SIZE	7

struct tcpm_power_cap {
	uint8_t cnt;
	uint32_t pdos[TCPM_PDO_MAX_SIZE];
};

/* Inquire TCPM status */

enum tcpc_cc_voltage_status {
	TYPEC_CC_VOLT_OPEN = 0,
	TYPEC_CC_VOLT_RA = 1,
	TYPEC_CC_VOLT_RD = 2,

	TYPEC_CC_VOLT_SNK_DFT = 5,
	TYPEC_CC_VOLT_SNK_1_5 = 6,
	TYPEC_CC_VOLT_SNK_3_0 = 7,

	TYPEC_CC_DRP_TOGGLING = 15,
};

enum tcpm_vbus_level {
#ifdef CONFIG_TCPC_VSAFE0V_DETECT
	TCPC_VBUS_SAFE0V = 0,
	TCPC_VBUS_INVALID,
	TCPC_VBUS_VALID,
#else
	TCPC_VBUS_INVALID = 0,
	TCPC_VBUS_VALID,
#endif
};

enum typec_role_defination {
	TYPEC_ROLE_UNKNOWN = 0,
	TYPEC_ROLE_SNK,
	TYPEC_ROLE_SRC,
	TYPEC_ROLE_DRP,
	TYPEC_ROLE_TRY_SRC,
	TYPEC_ROLE_TRY_SNK,
	TYPEC_ROLE_NR,
};

enum pd_cable_current_limit {
	PD_CABLE_CURR_UNKNOWN = 0,
	PD_CABLE_CURR_1A5 = 1,
	PD_CABLE_CURR_3A = 2,
	PD_CABLE_CURR_5A = 3,
};

/* DPM Flags */

#define DPM_FLAGS_PARTNER_DR_POWER		(1<<0)
#define DPM_FLAGS_PARTNER_DR_DATA		(1<<1)
#define DPM_FLAGS_PARTNER_EXTPOWER		(1<<2)
#define DPM_FLAGS_PARTNER_USB_COMM		(1<<3)
#define DPM_FLAGS_PARTNER_USB_SUSPEND	(1<<4)
#define DPM_FLAGS_PARTNER_HIGH_CAP		(1<<5)

#define DPM_FLAGS_PARTNER_MISMATCH		(1<<7)
#define DPM_FLAGS_PARTNER_GIVE_BACK		(1<<8)
#define DPM_FLAGS_PARTNER_NO_SUSPEND	(1<<9)

#define DPM_FLAGS_RESET_PARTNER_MASK	\
	(DPM_FLAGS_PARTNER_DR_POWER | DPM_FLAGS_PARTNER_DR_DATA|\
	DPM_FLAGS_PARTNER_EXTPOWER | DPM_FLAGS_PARTNER_USB_COMM)

#define DPM_FLAGS_CHECK_DC_MODE			(1<<20)
#define DPM_FLAGS_CHECK_UFP_SVID		(1<<21)
#define DPM_FLAGS_CHECK_EXT_POWER		(1<<22)
#define DPM_FLAGS_CHECK_DP_MODE			(1<<23)
#define DPM_FLAGS_CHECK_SINK_CAP		(1<<24)
#define DPM_FLAGS_CHECK_SOURCE_CAP		(1<<25)
#define DPM_FLAGS_CHECK_UFP_ID			(1<<26)
#define DPM_FLAGS_CHECK_CABLE_ID		(1<<27)
#define DPM_FLAGS_CHECK_CABLE_ID_DFP		(1<<28)
#define DPM_FLAGS_CHECK_PR_ROLE			(1<<29)
#define DPM_FLAGS_CHECK_DR_ROLE			(1<<30)

/* DPM_CAPS */

#define DPM_CAP_LOCAL_DR_POWER			(1<<0)
#define DPM_CAP_LOCAL_DR_DATA			(1<<1)
#define DPM_CAP_LOCAL_EXT_POWER			(1<<2)
#define DPM_CAP_LOCAL_USB_COMM			(1<<3)
#define DPM_CAP_LOCAL_USB_SUSPEND		(1<<4)
#define DPM_CAP_LOCAL_HIGH_CAP			(1<<5)
#define DPM_CAP_LOCAL_GIVE_BACK			(1<<6)
#define DPM_CAP_LOCAL_NO_SUSPEND		(1<<7)
#define DPM_CAP_LOCAL_VCONN_SUPPLY		(1<<8)

#define DPM_CAP_ATTEMP_ENTER_DC_MODE		(1<<11)
#define DPM_CAP_ATTEMP_DISCOVER_CABLE_DFP	(1<<12)
#define DPM_CAP_ATTEMP_ENTER_DP_MODE		(1<<13)
#define DPM_CAP_ATTEMP_DISCOVER_CABLE		(1<<14)
#define DPM_CAP_ATTEMP_DISCOVER_ID		(1<<15)

enum dpm_cap_pr_check_prefer {
	DPM_CAP_PR_CHECK_DISABLE = 0,
	DPM_CAP_PR_CHECK_PREFER_SNK = 1,
	DPM_CAP_PR_CHECK_PREFER_SRC = 2,
};

#define DPM_CAP_PR_CHECK_PROP(cap)			((cap & 0x03) << 16)
#define DPM_CAP_EXTRACT_PR_CHECK(raw)		((raw >> 16) & 0x03)
#define DPM_CAP_PR_SWAP_REJECT_AS_SRC		(1<<18)
#define DPM_CAP_PR_SWAP_REJECT_AS_SNK		(1<<19)
#define DPM_CAP_PR_SWAP_CHECK_GP_SRC		(1<<20)
#define DPM_CAP_PR_SWAP_CHECK_GP_SNK		(1<<21)
#define DPM_CAP_PR_SWAP_CHECK_GOOD_POWER	\
	(DPM_CAP_PR_SWAP_CHECK_GP_SRC | DPM_CAP_PR_SWAP_CHECK_GP_SNK)

enum dpm_cap_dr_check_prefer {
	DPM_CAP_DR_CHECK_DISABLE = 0,
	DPM_CAP_DR_CHECK_PREFER_UFP = 1,
	DPM_CAP_DR_CHECK_PREFER_DFP = 2,
};

#define DPM_CAP_DR_CHECK_PROP(cap)		((cap & 0x03) << 22)
#define DPM_CAP_EXTRACT_DR_CHECK(raw)		((raw >> 22) & 0x03)
#define DPM_CAP_DR_SWAP_REJECT_AS_DFP		(1<<24)
#define DPM_CAP_DR_SWAP_REJECT_AS_UFP		(1<<25)

#define DPM_CAP_DP_PREFER_MF				(1<<29)
#define DPM_CAP_SNK_PREFER_LOW_VOLTAGE		(1<<30)
#define DPM_CAP_SNK_IGNORE_MISMATCH_CURRENT	(1<<31)

extern int tcpm_shutdown(struct tcpc_device *tcpc_dev);

extern int tcpm_inquire_remote_cc(struct tcpc_device *tcpc_dev,
	uint8_t *cc1, uint8_t *cc2, bool from_ic);
extern int tcpm_inquire_vbus_level(struct tcpc_device *tcpc_dev, bool from_ic);
extern bool tcpm_inquire_cc_polarity(struct tcpc_device *tcpc_dev);
extern uint8_t tcpm_inquire_typec_attach_state(struct tcpc_device *tcpc_dev);
extern uint8_t tcpm_inquire_typec_role(struct tcpc_device *tcpc_dev);
extern uint8_t tcpm_inquire_typec_local_rp(struct tcpc_device *tcpc_dev);

extern int tcpm_typec_set_wake_lock(
	struct tcpc_device *tcpc, bool user_lock);

extern int tcpm_typec_set_usb_sink_curr(
	struct tcpc_device *tcpc_dev, int curr);

extern int tcpm_typec_set_rp_level(
	struct tcpc_device *tcpc_dev, uint8_t level);

extern int tcpm_typec_role_swap(
	struct tcpc_device *tcpc_dev);

extern int tcpm_typec_change_role(
	struct tcpc_device *tcpc_dev, uint8_t typec_role);

#ifdef CONFIG_USB_POWER_DELIVERY

extern bool tcpm_inquire_pd_connected(
	struct tcpc_device *tcpc_dev);

extern bool tcpm_inquire_pd_prev_connected(
	struct tcpc_device *tcpc_dev);

extern uint8_t tcpm_inquire_pd_data_role(
	struct tcpc_device *tcpc_dev);

extern uint8_t tcpm_inquire_pd_power_role(
	struct tcpc_device *tcpc_dev);

extern uint8_t tcpm_inquire_pd_vconn_role(
	struct tcpc_device *tcpc_dev);

extern uint8_t tcpm_inquire_cable_current(
	struct tcpc_device *tcpc_dev);

extern uint32_t tcpm_inquire_dpm_flags(
	struct tcpc_device *tcpc_dev);

extern uint32_t tcpm_inquire_dpm_caps(
	struct tcpc_device *tcpc_dev);

extern void tcpm_set_dpm_flags(
	struct tcpc_device *tcpc_dev, uint32_t flags);

extern void tcpm_set_dpm_caps(
	struct tcpc_device *tcpc_dev, uint32_t caps);

#endif	/* CONFIG_USB_POWER_DELIVERY */

/* Request TCPM to send PD Request */

extern int tcpm_power_role_swap(struct tcpc_device *tcpc_dev);
extern int tcpm_data_role_swap(struct tcpc_device *tcpc_dev);
extern int tcpm_vconn_swap(struct tcpc_device *tcpc_dev);
extern int tcpm_goto_min(struct tcpc_device *tcpc_dev);
extern int tcpm_soft_reset(struct tcpc_device *tcpc_dev);
extern int tcpm_hard_reset(struct tcpc_device *tcpc_dev);
extern int tcpm_get_source_cap(
	struct tcpc_device *tcpc_dev, struct tcpm_power_cap *cap);
extern int tcpm_get_sink_cap(
	struct tcpc_device *tcpc_dev, struct tcpm_power_cap *cap);
extern int tcpm_bist_cm2(struct tcpc_device *tcpc_dev);
extern int tcpm_request(
	struct tcpc_device *tcpc_dev, int mv, int ma);
extern int tcpm_error_recovery(struct tcpc_device *tcpc_dev);

/* Request TCPM to send VDM */

extern int tcpm_discover_cable(
	struct tcpc_device *tcpc_dev, uint32_t *vdos);

extern int tcpm_vdm_request_id(
	struct tcpc_device *tcpc_dev, uint8_t *cnt, uint32_t *vdos);

/* Request TCPM to send PD-DP Request */

#ifdef CONFIG_USB_PD_ALT_MODE

extern int tcpm_dp_attention(
	struct tcpc_device *tcpc_dev, uint32_t dp_status);

#ifdef CONFIG_USB_PD_ALT_MODE_DFP
extern int tcpm_dp_status_update(
	struct tcpc_device *tcpc_dev, uint32_t dp_status);
extern int tcpm_dp_configuration(
	struct tcpc_device *tcpc_dev, uint32_t dp_config);
#endif	/* CONFIG_USB_PD_ALT_MODE_DFP */

#endif	/* CONFIG_USB_PD_ALT_MODE */

/* Notify TCPM */

extern int tcpm_notify_vbus_stable(struct tcpc_device *tcpc_dev);

#ifdef CONFIG_USB_PD_UVDM

#define PD_UVDM_HDR(vid, custom)	\
	(((vid) << 16) | ((custom) & 0x7FFF))

#define PD_UVDM_HDR_CMD(hdr)	\
	(hdr & 0x7FFF)

extern int tcpm_send_uvdm(struct tcpc_device *tcpc_dev,
	uint8_t cnt, uint32_t *data, bool wait_resp);
#endif	/* CONFIG_USB_PD_UVDM */

#endif /* TCPM_H_ */
