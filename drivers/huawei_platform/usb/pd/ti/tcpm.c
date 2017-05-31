/*
 * Texas Instruments TUSB422 Power Delivery
 *
 * Author: Brian Quach <brian.quach@ti.com>
 * Copyright: (C) 2016 Texas Instruments, Inc.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 */

#include "tcpm.h"
#include "tcpci.h"
#include "tusb422.h"
#include "tusb422_common.h"
#ifdef CONFIG_WAKELOCK
	#include "tusb422_linux.h"
#endif
#ifdef CONFIG_TUSB422_PAL
	#include "usb_pd_pal.h"
#endif
#ifndef CONFIG_TUSB422
	#include <string.h>
#endif
#include "usb_pd_policy_engine.h"
//
//  Global variables
//

#define T_CC_DEBOUNCE_MS     150    /* 100 - 200 ms */
#define T_PD_DEBOUNCE_MS     15     /*  10 - 20 ms */
#define T_DRP_TRY_MS         125    /*  75 - 150 ms */
#define T_DRP_TRY_WAIT_MS    600    /* 400 - 800 ms */
#define T_VBUS_OFF_MS        650    /*  ?? - 650 ms */
#define T_ERROR_RECOVERY_MS  T_VBUS_OFF_MS   /*  25 - ?? ms */
#define T_TRY_TIMEOUT_MS     800    /* 550 - 1100 ms */
#define T_TRY_ROLE_SWAP_MS   500    /* custom value not defined by Type-C spec (500 ms minimum) */

#define TCPC_POLLING_DELAY()  tcpm_msleep(1)  /* Delay to wait for next CC and voltage polling period */

static tcpc_device_t tcpc_dev[NUM_TCPC_DEVICES];

static void (*conn_state_change_cbk)(unsigned int port, tcpc_state_t state) = NULL;
static void (*current_change_cbk)(unsigned int port, tcpc_cc_snk_state_t state) = NULL;
static void (*volt_alarm_cbk)(unsigned int port, bool hi_voltage) = NULL;
static void (*pd_hard_reset_cbk)(unsigned int port) = NULL;
static void (*pd_transmit_cbk)(unsigned int port, tx_status_t status) = NULL;
static void (*pd_receive_cbk)(unsigned int port) = NULL;

const char * const tcstate2string[TCPC_NUM_STATES] =
{
	"UNATTACHED_SRC",
	"UNATTACHED_SNK",
	"ATTACH_WAIT_SRC",
	"ATTACH_WAIT_SNK",
	"TRY_SNK",
	"TRY_SNK_LOOK4SRC",
	"TRY_SRC",
	"TRY_WAIT_SRC",
	"TRY_WAIT_SNK",
	"ATTACHED_SRC",
	"ATTACHED_SNK",
	"UNORIENTED_DEBUG_ACC_SRC",
	"ORIENTED_DEBUG_ACC_SRC",
	"DEBUG_ACC_SNK",
	"AUDIO_ACC",
	"ERROR_RECOVERY",
	"DISABLED"
};

tcpc_device_t* tcpm_get_device(unsigned int port)
{
	return &tcpc_dev[port];
}

#ifndef CONFIG_TUSB422
void tcpm_dump_state(unsigned int port)
{
	tcpc_device_t *dev = tcpm_get_device(port);

	PRINT("\nType-C State: %s (last: %s)\n", tcstate2string[dev->state], tcstate2string[dev->last_state]);
	return;
}
#endif

static void tcpm_notify_conn_state(unsigned int port, tcpc_state_t state)
{
	if (conn_state_change_cbk) conn_state_change_cbk(port, state);

	// For Attached.SRC state, PAL is notified before VBUS is applied.
	if (state != TCPC_STATE_ATTACHED_SRC)
	{
#ifdef CONFIG_TUSB422_PAL
		usb_pd_pal_notify_connect_state(port, state, tcpc_dev[port].plug_polarity);
#endif
	}

	return;
}

static void tcpm_notify_current_change(unsigned int port, tcpc_cc_snk_state_t state)
{
	DEBUG("Current advertisement change detected: %s\n",
		  (state == CC_SNK_STATE_POWER30) ? "3.0A" :
		  (state == CC_SNK_STATE_POWER15) ? "1.5A" :
		  (state == CC_SNK_STATE_DEFAULT) ? "500/900mA" : "?");

	if (current_change_cbk)	current_change_cbk(port, state);

	return;
}

static void tcpm_notify_hard_reset(unsigned int port)
{
	DEBUG("Hard Reset Rx'd.\n");
	if (pd_hard_reset_cbk) pd_hard_reset_cbk(port);
	return;
}

static void tcpm_notify_pd_transmit(unsigned int port, tx_status_t status)
{
	DEBUG("PD Tx %s.\n", (status == TX_STATUS_SUCCESS) ? "OK" :
		  (status == TX_STATUS_DISCARDED) ? "discarded" :
		  (status == TX_STATUS_FAILED) ? "failed" : "?");

	if (pd_transmit_cbk) pd_transmit_cbk(port, status);
	return;
}

static void tcpm_notify_pd_receive(unsigned int port)
{
	DEBUG("PD Rx\n");
	if (pd_receive_cbk)	pd_receive_cbk(port);
	return;
}

static void tcpm_notify_voltage_alarm(unsigned int port, bool hi_voltage)
{
	DEBUG("%s-Voltage alarm\n", (hi_voltage) ? "Hi" : "Lo");
	if (volt_alarm_cbk)	volt_alarm_cbk(port, hi_voltage);
	return;
}

void tcpm_src_vbus_disable(unsigned int port)
{
	DEBUG("SRC VBUS off.\n");
	tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_DISABLE_SRC_VBUS);
	tcpm_hal_vbus_disable(port, VBUS_SRC_HI_VOLT);
	tcpm_hal_vbus_disable(port, VBUS_SRC_5V);
	return;
}

void tcpm_src_vbus_5v_enable(unsigned int port)
{
	DEBUG("-> SRC VBUS 5V.\n");
	tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_SRC_VBUS_DEFAULT);
	tcpm_hal_vbus_enable(port, VBUS_SRC_5V);
	return;
}

void tcpm_src_vbus_hi_volt_enable(unsigned int port)
{
	DEBUG("-> SRC VBUS Hi.\n");
	tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_SRC_VBUS_HI_VOLTAGE);
	tcpm_hal_vbus_enable(port, VBUS_SRC_HI_VOLT);
	return;
}

void tcpm_snk_vbus_enable(unsigned int port)
{
	DEBUG("-> SNK VBUS.\n");
	tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_SNK_VBUS);
	tcpm_hal_vbus_enable(port, VBUS_SNK);
	return;
}

void tcpm_snk_vbus_disable(unsigned int port)
{
	DEBUG("SNK VBUS off.\n");
	tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_DISABLE_SNK_VBUS);
	tcpm_hal_vbus_disable(port, VBUS_SNK);
	return;
}

void tcpm_set_voltage_alarm_hi(unsigned int port, uint16_t threshold_25mv)
{
	tcpc_write16(port, TCPC_REG_VBUS_VOLTAGE_ALARM_HI_CFG, threshold_25mv);
	return;
}

void tcpm_set_voltage_alarm_lo(unsigned int port, uint16_t threshold_25mv)
{
	tcpc_write16(port, TCPC_REG_VBUS_VOLTAGE_ALARM_LO_CFG, threshold_25mv);
	return;
}

static uint16_t tcpm_get_voltage_alarm_lo_threshold(unsigned int port)
{
	uint16_t threshold_25mv;

	tcpc_read16(port, TCPC_REG_VBUS_VOLTAGE_ALARM_LO_CFG, &threshold_25mv);

	return threshold_25mv;
}

bool tcpm_is_vbus_present(unsigned int port)
{
	uint8_t pwr_status;

	tcpc_read8(port, TCPC_REG_POWER_STATUS, &pwr_status);

	return(pwr_status & TCPC_PWR_STATUS_VBUS_PRESENT) ? true : false;
}


void tcpm_set_vconn_enable(unsigned int port, bool enable)
{
	if (enable)
	{
		tcpc_modify8(port, TCPC_REG_POWER_CTRL, 0, TCPC_PWR_CTRL_ENABLE_VCONN);
	}
	else
	{
		tcpc_modify8(port, TCPC_REG_POWER_CTRL, TCPC_PWR_CTRL_ENABLE_VCONN, 0);
	}

	return;
}


bool tcpm_is_vconn_source(unsigned int port)
{
	uint8_t pwr_ctrl;

	tcpc_read8(port, TCPC_REG_POWER_CTRL, &pwr_ctrl);

	return(pwr_ctrl & TCPC_PWR_CTRL_ENABLE_VCONN) ? true : false;
}


void tcpm_set_rp_value(unsigned int port, tcpc_role_rp_val_t rp_val)
{
	tcpc_modify8(port, TCPC_REG_ROLE_CTRL, TCPC_ROLE_CTRL_RP_VALUE_MASK, (rp_val << TCPC_ROLE_CTRL_RP_VALUE_SHIFT));
	return;
}

void tcpm_remove_rp_from_vconn_pin(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	if (dev->plug_polarity == PLUG_UNFLIPPED)
	{
		// Remove Rp from CC2 pin.
		tcpc_write8(port, TCPC_REG_ROLE_CTRL,
					tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_RP, CC_OPEN));
	}
	else
	{
		// Remove Rp from CC1 pin.
		tcpc_write8(port, TCPC_REG_ROLE_CTRL,
					tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_OPEN, CC_RP));
	}

	return;
}

void tcpm_cc_pin_control(unsigned int port, tc_role_t new_role)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	if (dev->silicon_revision == 0)
	{
		tcpc_write8(port, TCPC_REG_ROLE_CTRL,
					tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_OPEN, CC_OPEN));
	}

	if (new_role == ROLE_SNK)
	{
		tcpc_write8(port, TCPC_REG_ROLE_CTRL,
					tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_RD, CC_RD));
	}
	else if (new_role == ROLE_SRC)
	{
		tcpc_write8(port, TCPC_REG_ROLE_CTRL,
					tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_RP, CC_RP));
	}

	return;
}

void tcpm_update_msg_header_info(unsigned int port, uint8_t data_role, uint8_t power_role)
{
	// Update msg header info.
	tcpc_write8(port, TCPC_REG_MSG_HDR_INFO,
				TCPC_REG_MSG_HDR_INFO_SET(0, data_role, power_role));

	return;
}

void tcpm_set_bist_test_mode(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];
	uint8_t ctrl = TCPC_CTRL_BIST_TEST_MODE;

	ctrl |= (dev->plug_polarity == PLUG_FLIPPED) ? TCPC_CTRL_PLUG_ORIENTATION : 0;

	// Note: This setting has no effect in PG1.0.
	tusb422_i2c_write_byte(TCPC_REG_TCPC_CTRL, ctrl);
	//	tcpc_write8(port, TCPC_REG_TCPC_CTRL, ctrl);
	return;
}

void tcpm_enable_bleed_discharge(unsigned int port)
{
	tcpc_modify8(port, TCPC_REG_POWER_CTRL, 0, TCPC_PWR_CTRL_ENABLE_BLEED_DISCHARGE);
	return;
}

static void tcpm_enable_voltage_monitoring(unsigned int port)
{
	uint8_t pwr_ctrl;

	tcpc_read8(port, TCPC_REG_POWER_CTRL, &pwr_ctrl);

	if (pwr_ctrl & (TCPC_PWR_CTRL_VBUS_VOLTAGE_MONITOR | TCPC_PWR_CTRL_DISABLE_VOLTAGE_ALARM))
	{
		// Enable voltage monitoring and alarms.
		pwr_ctrl &= ~(TCPC_PWR_CTRL_VBUS_VOLTAGE_MONITOR | TCPC_PWR_CTRL_DISABLE_VOLTAGE_ALARM);
		tcpc_write8(port, TCPC_REG_POWER_CTRL, pwr_ctrl);

		// Delay by one polling period to ensure VBUS measurement is valid.
		TCPC_POLLING_DELAY();
	}

	return;
}

void tcpm_enable_vbus_detect(unsigned int port)
{
	uint8_t pwr_status;

	// Read power status.
	tcpc_read8(port, TCPC_REG_POWER_STATUS, &pwr_status);

	if (!(pwr_status & TCPC_PWR_STATUS_VBUS_PRES_DETECT_EN))
	{
		// ADC is used for VBUS detection so ensure voltage monitoring is enabled.
		tcpc_modify8(port, TCPC_REG_POWER_CTRL, TCPC_PWR_CTRL_VBUS_VOLTAGE_MONITOR, 0);

		// Enable VBUS detect.
		tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_ENABLE_VBUS_DETECT);

		// Delay by one polling period to ensure VBUS measurement is valid.
		TCPC_POLLING_DELAY();
	}

	return;
}

void tcpm_disable_vbus_detect(unsigned int port)
{
	// Disable VBUS detect.
	tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_DISABLE_VBUS_DETECT);

	return;
}


void tcpm_register_dump(unsigned int port)
{
	uint8_t i;
	uint8_t data;

	PRINT("\nTCPC-%u Regs:\n", port);

	for (i = 0x10; i < 0x16; i++)
	{
		tcpc_read8(port, i, &data);
		PRINT("%02x: %02x\n", i, data);
	}

	for (i = 0x18; i < 0x20; i++)
	{
		tcpc_read8(port, i, &data);
		PRINT("%02x: %02x\n", i, data);
	}

	for (i = 0x2E; i < 0x30; i++)
	{
		tcpc_read8(port, i, &data);
		PRINT("%02x: %02x\n", i, data);
	}

	for (i = 0x70; i < 0x7A; i++)
	{
		tcpc_read8(port, i, &data);
		PRINT("%02x: %02x\n", i, data);
	}

	tcpc_read8(port, 0x90, &data);
	PRINT("90: %02x\n", data);

	tcpc_read8(port, 0x94, &data);
	PRINT("94: %02x\n", data);

	return;
}


void tcpm_register_callbacks(const tcpm_callbacks_t *callbacks)
{
	conn_state_change_cbk = callbacks->conn_state_change_cbk;
	current_change_cbk = callbacks->current_change_cbk;
	volt_alarm_cbk = callbacks->volt_alarm_cbk;

	pd_hard_reset_cbk = callbacks->pd_hard_reset_cbk;
	pd_transmit_cbk = callbacks->pd_transmit_cbk;
	pd_receive_cbk = callbacks->pd_receive_cbk;

	return;
}


static void tcpm_set_state(tcpc_device_t *dev, tcpc_state_t new_state)
{
	CRIT("%s\n", tcstate2string[new_state]);

	dev->last_state = dev->state;
	dev->state = new_state;
	dev->state_change = true;

	return;
}


static void timeout_cc_debounce(unsigned int port)
{
	unsigned int cc1, cc2;
	tcpc_device_t *dev = &tcpc_dev[port];

	// Read CC status.
	tcpc_read8(port, TCPC_REG_CC_STATUS, &dev->cc_status);
	DEBUG("%s CC status = 0x%x\n", __func__, dev->cc_status);

	cc1 = TCPC_CC1_STATE(dev->cc_status);
	cc2 = TCPC_CC2_STATE(dev->cc_status);

	if (dev->state == TCPC_STATE_ATTACH_WAIT_SRC)
	{
		if ((cc1 == CC_SRC_STATE_RA) &&
			(cc2 == CC_SRC_STATE_RA))
		{
			tcpm_set_state(dev, TCPC_STATE_AUDIO_ACC);
		}
		else if ((cc1 == CC_SRC_STATE_RD) &&
				 (cc2 == CC_SRC_STATE_RD))
		{
			tcpm_set_state(dev, TCPC_STATE_UNORIENTED_DEBUG_ACC_SRC);
		}
		else if ((cc1 == CC_SRC_STATE_RD) ||
				 (cc2 == CC_SRC_STATE_RD))
		{
			if ((dev->flags & TC_FLAGS_TRY_SNK) &&
				(dev->role == ROLE_DRP))
			{
				tcpm_set_state(dev, TCPC_STATE_TRY_SNK);
			}
			else
			{
				// Check if VBUS is below vSafe0V.
				if (tcpm_get_vbus_voltage(port) < VSAFE0V_MAX)
				{
					tcpm_set_state(dev, TCPC_STATE_ATTACHED_SRC);
				}
				else
				{
					// Set low voltage alarm for vSafe0V to trigger transition to Attached.SRC.
					tcpm_set_voltage_alarm_lo(port, VSAFE0V_MAX);
				}
			}
		}
		else /* Invalid CC state */
		{
			tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SRC);
		}
	}
	else if ((dev->state == TCPC_STATE_TRY_SRC) ||
			 (dev->state == TCPC_STATE_TRY_WAIT_SRC))
	{
		// Enable voltage monitoring.
		tcpm_enable_voltage_monitoring(port);

		// Verify VBUS is still below vSafe0V.
		if (tcpm_get_vbus_voltage(port) < VSAFE0V_MAX)
		{
			// Disable force discharge.
			tcpc_modify8(port, TCPC_REG_POWER_CTRL, TCPC_PWR_CTRL_FORCE_DISCHARGE, 0);

			tcpm_set_state(dev, TCPC_STATE_ATTACHED_SRC);
		}
		else
		{
			// Set low voltage alarm for vSafe0V to trigger transition to Attached.SRC.
			tcpm_set_voltage_alarm_lo(port, VSAFE0V_MAX);
		}
	}
	else if (dev->state == TCPC_STATE_ATTACH_WAIT_SNK)
	{
		dev->src_detected = true;

		if (tcpm_is_vbus_present(port))
		{
			// Debug Accessory if SNK.Rp on both CC1 and CC2.
			if ((cc1 != CC_SNK_STATE_OPEN) &&
				(cc2 != CC_SNK_STATE_OPEN))
			{
				tcpm_set_state(dev, TCPC_STATE_DEBUG_ACC_SNK);
			}
			else if ((dev->flags & TC_FLAGS_TRY_SRC) &&
					 (dev->role == ROLE_DRP))
			{
				tcpm_set_state(dev, TCPC_STATE_TRY_SRC);
			}
			else
			{
				tcpm_set_state(dev, TCPC_STATE_ATTACHED_SNK);
			}
		}
	}
	else if (dev->state == TCPC_STATE_TRY_WAIT_SNK)
	{
		dev->src_detected = true;

		if (tcpm_is_vbus_present(port))
		{
			tcpm_set_state(dev, TCPC_STATE_ATTACHED_SNK);
		}
	}
	else if (dev->state == TCPC_STATE_AUDIO_ACC)
	{
		if ((cc1 == CC_SNK_STATE_OPEN) &&
			(cc2 == CC_SNK_STATE_OPEN))
		{
			if (dev->role == ROLE_SNK)
			{
				tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
			}
			else
			{
				tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SRC);
			}
		}
	}

	return;
}

static void timeout_try_timeout(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	tcpm_set_state(dev, TCPC_STATE_TRY_WAIT_SNK);
	return;
}

static void timeout_drp_try(unsigned int port)
{
	unsigned int cc1, cc2;
	tcpc_device_t *dev = &tcpc_dev[port];

	DEBUG("%s\n", __func__);

	if (dev->state == TCPC_STATE_TRY_SNK)
	{
		tcpm_set_state(dev, TCPC_STATE_TRY_SNK_LOOK4SRC);
	}
	else
	{
		// Read CC status.
		tcpc_read8(port, TCPC_REG_CC_STATUS, &dev->cc_status);
		DEBUG("%s CC status = 0x%x\n", __func__, dev->cc_status);

		cc1 = TCPC_CC1_STATE(dev->cc_status);
		cc2 = TCPC_CC2_STATE(dev->cc_status);

		// If neither CC pin is in Rd state.
		if ((cc1 != CC_SRC_STATE_RD) &&
			(cc2 != CC_SRC_STATE_RD))
		{
			if (dev->state == TCPC_STATE_TRY_SRC)
			{
				// Check if VBUS is below vSafe0V.
				if (tcpm_get_vbus_voltage(port) < VSAFE0V_MAX)
				{
					tcpm_set_state(dev, TCPC_STATE_TRY_WAIT_SNK);
				}
				else
				{
					// Set low voltage alarm for vSafe0V to trigger transition to TryWait.SNK.
					tcpm_set_voltage_alarm_lo(port, VSAFE0V_MAX);

					// Start tTryTimeout timer.
					timer_start(&dev->timer, T_TRY_TIMEOUT_MS, timeout_try_timeout);
				}
			}
			else if (dev->state == TCPC_STATE_TRY_WAIT_SRC)
			{
				tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
			}
		}
	}

	return;
}

#if 0
static void timeout_drp_try_wait(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	DEBUG("%s\n", __func__);

	return;
}
#endif

static void timeout_pd_debounce(unsigned int port)
{
	unsigned int cc1, cc2;
	tcpc_device_t *dev = &tcpc_dev[port];

	// Read CC status.
	tcpc_read8(port, TCPC_REG_CC_STATUS, &dev->cc_status);
	DEBUG("%s CC status = 0x%x\n", __func__, dev->cc_status);

	cc1 = TCPC_CC1_STATE(dev->cc_status);
	cc2 = TCPC_CC2_STATE(dev->cc_status);

	if (dev->state == TCPC_STATE_TRY_SNK_LOOK4SRC)
	{
		// Check for Rp on exactly one pin.
		if (((cc1 == CC_SNK_STATE_OPEN) && (cc2 != CC_SNK_STATE_OPEN)) ||
			((cc1 != CC_SNK_STATE_OPEN) && (cc2 == CC_SNK_STATE_OPEN)))
		{
			// Source detected for tPDDebounce.
			dev->src_detected = true;

			// Enable VBUS detection.
			tcpm_enable_vbus_detect(dev->port);

			if (tcpm_is_vbus_present(port))
			{
				tcpm_set_state(dev, TCPC_STATE_ATTACHED_SNK);
			}
		}
	}
	else if ((dev->state == TCPC_STATE_TRY_SRC) ||
			 (dev->state == TCPC_STATE_TRY_WAIT_SRC))
	{
		// Check for Rd on exactly one pin.
		if (((cc1 == CC_SRC_STATE_RD) && (cc2 != CC_SRC_STATE_RD)) ||
			((cc1 != CC_SRC_STATE_RD) && (cc2 == CC_SRC_STATE_RD)))
		{
			// Enable voltage monitoring.
			tcpm_enable_voltage_monitoring(port);

			// Check if VBUS is below vSafe0V. It should always be for TryWait.SRC.
			if (tcpm_get_vbus_voltage(port) < VSAFE0V_MAX)
			{
				tcpm_set_state(dev, TCPC_STATE_ATTACHED_SRC);
			}
			else
			{
				// Set low voltage alarm for vSafe0V to trigger transition to Attached.SRC.
				tcpm_set_voltage_alarm_lo(port, VSAFE0V_MAX);
			}
		}
	}

	if ((cc1 == CC_STATE_OPEN) && (cc2 == CC_STATE_OPEN))
	{
		if (dev->state == TCPC_STATE_ATTACH_WAIT_SNK)
		{
			if (dev->role == ROLE_DRP)
			{
				tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SRC);
			}
			else
			{
				tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
			}
		}
		else if (dev->state == TCPC_STATE_TRY_SNK_LOOK4SRC)
		{
			tcpm_set_state(dev, TCPC_STATE_TRY_WAIT_SRC);
		}
		else if (dev->state == TCPC_STATE_TRY_WAIT_SNK)
		{
			tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
		}
		else if ((dev->state == TCPC_STATE_TRY_SRC) ||
				 (dev->state == TCPC_STATE_TRY_WAIT_SRC))
		{
			// Set state change flag so tDRPTry timer will be restarted in connection state machine.
			dev->state_change = true;
		}
		else
		{
			if (dev->role == ROLE_SNK)
			{
				tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
			}
			else
			{
				tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SRC);
			}
		}
	}

	return;
}


static void timeout_vbus4v_debounce(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];
	uint16_t v_threshold;

	INFO("%s\n", __func__);

	if ((dev->state == TCPC_STATE_ATTACHED_SNK) ||
		(dev->state == TCPC_STATE_DEBUG_ACC_SNK))
	{
		// If VBUS is <= 4V, consider it a disconnect.
		if (tcpm_get_vbus_voltage(port) <= VDISCON_MAX)
		{
			// Unattached.SNK.
			tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
		}
		else
		{
			tcpc_read16(port, TCPC_REG_VBUS_VOLTAGE_ALARM_LO_CFG, &v_threshold);

			// Re-enabled the voltage alarm if it is disabled.
			if (v_threshold == 0)
			{
				tcpm_set_voltage_alarm_lo(port, VDISCON_MAX);
			}
		}
	}

	return;
}

static void timeout_error_recovery(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	INFO("%s\n", __func__);

	if (dev->role == ROLE_SNK)
	{
		tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
	}
	else
	{
		tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SRC);
	}

	return;
}


void tcpm_enable_pd_receive(unsigned int port, bool enable_sop_p, bool enable_sop_pp)
{
	uint8_t rx_det_en = (TCPC_RX_EN_HARD_RESET | TCPC_RX_EN_SOP);

	INFO("Enable PD Rx: SOP'=%u, SOP\"=%u\n", enable_sop_p, enable_sop_pp);

	// Ensure BIST test mode is disabled.
	tcpc_modify8(port, TCPC_REG_TCPC_CTRL, TCPC_CTRL_BIST_TEST_MODE, 0);

	if (enable_sop_p)
	{
		rx_det_en |= TCPC_RX_EN_SOP_P;
	}

	if (enable_sop_pp)
	{
		rx_det_en |= TCPC_RX_EN_SOP_PP;
	}

	// Enable PD receive. (will be cleared by TCPC upon hard reset or disconnect)
	tcpc_write8(port, TCPC_REG_RX_DETECT, rx_det_en);

	return;
}

void tcpm_disable_pd_receive(unsigned int port)
{
	// Disable PD receive.
	tcpc_write8(port, TCPC_REG_RX_DETECT, 0);
	return;
}


/* Returns VBUS voltage in 25mV units.  Must be in ATTACHED state where VBUS monitoring is enabled. */
uint16_t tcpm_get_vbus_voltage(unsigned int port)
{
	uint16_t volt;

	tcpc_read16(port, TCPC_REG_VBUS_VOLTAGE, &volt);

	// Assume no scale factor.
	return(volt & 0x3FF);
}

void tcpm_force_discharge(unsigned int port, uint16_t threshold_25mv)
{
	CRIT("Force VBUS discharge to %u mV\n", threshold_25mv * 25);

	tcpc_write16(port, TCPC_REG_VBUS_STOP_DISCHARGE_THRESH, threshold_25mv);

	tcpc_modify8(port, TCPC_REG_POWER_CTRL, 0, TCPC_PWR_CTRL_FORCE_DISCHARGE);

	return;
}

/* For policy engine control for sinks only */
void tcpm_set_autodischarge_disconnect(unsigned int port, bool enable)
{
	if (enable)
	{
		tcpc_modify8(port, TCPC_REG_POWER_CTRL, 0, TCPC_PWR_CTRL_AUTO_DISCHARGE_DISCONNECT);

		// Set low voltage alarm to trigger transition to Unattached.SNK if
		// VBUS <= 4V for longer than (2 x tPDDebounce).
		tcpm_set_voltage_alarm_lo(port, VDISCON_MAX);   // BQ - remove to fix phone reboot with PD charger.
	}
	else
	{
		tcpc_modify8(port, TCPC_REG_POWER_CTRL, TCPC_PWR_CTRL_AUTO_DISCHARGE_DISCONNECT, 0);

		// Disable low voltage alarm.
		tcpm_set_voltage_alarm_lo(port, 0);

		tcpm_disable_vbus_detect(port);
	}

	return;
}

/* threshold has 25mV LSB, set to zero to disable and use VBUS_PRESENT to start auto-discharge disconnect */
void tcpm_set_sink_disconnect_threshold(unsigned int port, uint16_t threshold_25mv)
{
	tcpc_write16(port, TCPC_REG_VBUS_SINK_DISCONNECT_THRESH, threshold_25mv);
	return;
}

void tcpm_get_msg_header_type(unsigned int port, uint8_t *frame_type, uint16_t *header)
{
	// Read Rx header.
	tcpc_read16(port, TCPC_REG_RX_HDR, header);

	// Read Rx SOP type.
	tcpc_read8(port, TCPC_REG_RX_BUF_FRAME_TYPE, frame_type);

	return;
}

#ifdef CONFIG_TUSB422
// Use this funcion if using an I2C read transfer instead of SMBus block read.
void tcpm_read_message(unsigned int port, uint8_t *buf, uint8_t len)
{
	uint8_t i;
	uint8_t byte_cnt;

	// Read Rx Byte Cnt.
	tcpc_read8(port, TCPC_REG_RX_BYTE_CNT, &byte_cnt);

	if (tcpc_dev[port].silicon_revision == 0)
	{
		/****** TUSB422 PG1.0 workaround for zero byte cnt issue (CDDS #48) ******/
		if (byte_cnt == 0)
		{
			CRIT("\n## ERROR: tcpm_read_msg: zero byte cnt!\n\n");
		}

		if (byte_cnt != (len + 3))
		{
			CRIT("RxByteCnt = %u invalid, using length %u from header!\n", byte_cnt, len);
			byte_cnt = len + 3;
		}
	}

	if (byte_cnt > 3)
	{
		// Subtract 3-bytes for frame type and header.
		byte_cnt -= 3;

		if (byte_cnt)
		{
			tcpc_read_block(port, TCPC_REG_RX_DATA, buf, byte_cnt);
		}
	}

	DEBUG("rx_buf: 0x");
	for (i = 0; i < byte_cnt; i++)
	{
		DEBUG("%02x ", buf[i]);
	}
	DEBUG("\n");

	return;
}
#else
void tcpm_read_message(unsigned int port, uint8_t *buf, uint8_t len)
{
	uint8_t i;
	uint8_t byte_cnt;
	uint8_t local_buf[32];

	// Read Rx Byte Cnt.
	tcpc_read8(port, TCPC_REG_RX_BYTE_CNT, &byte_cnt);

	if (tcpc_dev[port].silicon_revision == 0)
	{
		if (byte_cnt == 0)
		{
			CRIT("\n## ERROR: tcpm_read_msg: zero byte cnt!\n\n");
		}

		if (byte_cnt != (len + 3))
		{
			CRIT("RxByteCnt = %u invalid, using length %u from header!\n", byte_cnt, len);
			byte_cnt = len + 3;
		}
	}

	if (byte_cnt > 3)
	{
		tcpc_read_block(port, TCPC_REG_RX_BYTE_CNT, local_buf, byte_cnt + 1);

		// Copy message to buffer. (Subtract 3-bytes for frame type and header)
		memcpy(buf, &local_buf[4], (byte_cnt - 3));

		DEBUG("rx_buf: 0x");
		for (i = 0; i < (byte_cnt - 3); i++)
		{
			DEBUG("%02x ", buf[i]);
		}
		DEBUG("\n");
	}

	return;
}
#endif

// buf[0] Tx byte cnt including 2-byte header.
void tcpm_transmit(unsigned int port, uint8_t *buf, tcpc_transmit_t sop_type)
{
	if (buf)
	{
		// Write Tx byte cnt, header, and buffer all together.
		// (Add 1 to length since we are also writing byte cnt)
#ifdef CONFIG_TUSB422
		tcpc_write_block(port, TCPC_REG_TX_BYTE_CNT, buf, buf[0] + 1);
#else
		/* If using SMBus block write */
		tcpc_write_block(port, TCPC_REG_TX_BYTE_CNT, &buf[1], buf[0]);
#endif
	}

	// Start transmit.
	tcpc_write8(port, TCPC_REG_TRANSMIT, TCPC_REG_TRANSMIT_SET(sop_type));

	return;
}


void tcpm_execute_error_recovery(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	if (dev->state == TCPC_STATE_ERROR_RECOVERY)
	{
		return;
	}

	PRINT("Error Recovery!\n");

	tcpm_set_state(dev, TCPC_STATE_ERROR_RECOVERY);

	// Disable low voltage alarm.
	tcpm_set_voltage_alarm_lo(port, 0);

	// Disable VBUS.
	tcpm_src_vbus_disable(port);
	tcpm_snk_vbus_disable(port);

	tcpc_write16(port, TCPC_REG_VBUS_STOP_DISCHARGE_THRESH, VSTOP_DISCHRG);

	// AutoDischargeDisconnect=0, Disable VCONN, Enable VBUS voltage monitor/alarms, Force discharge, Enable bleed.
	tcpc_write8(port, TCPC_REG_POWER_CTRL,
				(TCPC_PWR_CTRL_FORCE_DISCHARGE | TCPC_PWR_CTRL_ENABLE_BLEED_DISCHARGE));

	// Remove CC1 & CC2 terminations.
	tcpc_write8(port, TCPC_REG_ROLE_CTRL,
				tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_OPEN, CC_OPEN));

	timer_start(&dev->timer, T_ERROR_RECOVERY_MS, timeout_error_recovery);

	return;
}


static void timeout_try_role_swap(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	INFO("%s\n", __func__);

	if ((dev->flags & TC_FLAGS_TEMP_ROLE) &&
		((dev->state == TCPC_STATE_UNATTACHED_SRC) ||
		 (dev->state == TCPC_STATE_UNATTACHED_SNK)))
	{
		// Restore DRP role which will take effect on next unattach.
		dev->role = ROLE_DRP;
		// Clear flag.
		dev->flags &= ~TC_FLAGS_TEMP_ROLE;

		tcpm_execute_error_recovery(port);
	}

	return;
}


/* This function will permanently change the role of the Type-C port and
 * perform an error recovery */
void tcpm_change_role(unsigned int port, tc_role_t new_role)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	dev->role = new_role;

	tcpm_execute_error_recovery(port);

	return;
}


/* This function will attempt a manual Type-C role swap. It will temporarily
 * change the role from DRP to DFP or UFP and perform a Type-C error recovery.
 * If a new connection is not established within 1 second, the DRP role will be
 * automatically restored and another Type-C error recovery will be executed.
 * Note: If Try.SRC is enabled and currently Attached.SNK, this function will
 * not be able to swap to SRC if the port partner also implements Try.SRC. */
void tcpm_try_role_swap(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	INFO("%s\n", __func__);

	if (!(dev->cc_status & CC_STATUS_LOOKING4CONNECTION) &&
		(dev->role == ROLE_DRP))
	{
		if (dev->cc_status & CC_STATUS_CONNECT_RESULT)
		{
			// Currently SNK, change to SRC.
			dev->role = ROLE_SRC;
		}
		else
		{
			// Currently SRC, change to SNK.
			dev->role = ROLE_SNK;
		}

		dev->flags |= TC_FLAGS_TEMP_ROLE;

		tcpm_execute_error_recovery(port);
	}

	return;
}

void tcpm_handle_power_role_swap(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	INFO("%s\n", __func__);

	if (dev->state == TCPC_STATE_ATTACHED_SRC)
	{
		tcpm_set_state(dev, TCPC_STATE_ATTACHED_SNK);
		dev->state_change = false;
	}
	else if (dev->state == TCPC_STATE_ATTACHED_SNK)
	{
		tcpm_set_state(dev, TCPC_STATE_ATTACHED_SRC);
		dev->state_change = false;
	}

	return;
}

static void tcpm_handle_attached_state(unsigned int port)
{
	tcpc_device_t *dev = &tcpc_dev[port];

	// Cancel all timers.
	timer_cancel(&dev->timer);
	tusb422_lfo_timer_cancel(&dev->timer2);

#ifdef CONFIG_WAKELOCK
	tusb422_wake_lock_attach();
#endif

	if (dev->flags & TC_FLAGS_TEMP_ROLE)
	{
		// Restore DRP role which will take effect on next unattach.
		dev->role = ROLE_DRP;
		// Clear flag.
		dev->flags &= ~TC_FLAGS_TEMP_ROLE;
	}

	return;
}


void tcpm_connection_state_machine(unsigned int port)
{
	unsigned int cc1, cc2;
	tcpc_role_cc_t cc_pull;
	tcpc_device_t *dev = &tcpc_dev[port];

	INFO("%s: state_change = %x, state = 0x%x.", __func__, dev->state_change, dev->state);

	if (!dev->state_change)
		return;

	// Read current CC status.
	tcpc_read8(port, TCPC_REG_CC_STATUS, &dev->cc_status);

	cc1 = TCPC_CC1_STATE(dev->cc_status);
	cc2 = TCPC_CC2_STATE(dev->cc_status);

	switch (dev->state)
	{
		case TCPC_STATE_UNATTACHED_SNK:
		case TCPC_STATE_UNATTACHED_SRC:
			timer_cancel(&dev->timer);
			tusb422_lfo_timer_cancel(&dev->timer2);

			dev->src_detected = false;
			dev->src_attach_notify = false;

			// Disable VBUS.
			tcpm_src_vbus_disable(port);
			tcpm_snk_vbus_disable(port);

			tcpc_write16(port, TCPC_REG_VBUS_STOP_DISCHARGE_THRESH, VSTOP_DISCHRG);

			if (dev->silicon_revision <= 1)
			{
				/*** TUSB422 PG1.0 workaround for CC polling issue (CDDS #59) ***/
				/*** TUSB422 PG1.0 workaround for Tx Discarded issue (CDDS #38) ***/
				/*** TUSB422 PG1.0/1.1 workaround for DRP toggle cycle not reset (CDDS #65) ***/
				tusb422_sw_reset(port);

#ifdef DISABLE_VCONN_OC_DETECT
				// Disable VCONN OC fault detection.
				tcpc_modify8(port, TCPC_REG_FAULT_CTRL, 0, TCPC_FLT_CTRL_VCONN_OC_FAULT);
#endif
				// Re-Initialize vendor-specific registers.
				tusb422_init(port);

				// Set hi voltage alarm threshold to max and clear alert.
				tcpm_set_voltage_alarm_hi(port, 0x3FF);
				tcpc_write16(port, TCPC_REG_ALERT, TCPC_ALERT_VOLT_ALARM_HI);

				// Set low voltage alarm so we can disable voltage monitoring when discharge is complete.
				tcpm_set_voltage_alarm_lo(port, VSTOP_DISCHRG);

				// AutoDischargeDisconnect=0, Disable VCONN, Enable VBUS voltage monitor/alarms, Force discharge, Enable bleed.
				tcpc_write8(port, TCPC_REG_POWER_CTRL,
							(TCPC_PWR_CTRL_FORCE_DISCHARGE | TCPC_PWR_CTRL_ENABLE_BLEED_DISCHARGE));
			}
			else
			{
				if (dev->silicon_revision <= 3)
				{
					// Disable PD receive. PG1.1/1.2/1.3 does not automatically disable PD upon disconnect.
					tcpc_write8(port, TCPC_REG_RX_DETECT, 0);
				}

				// Set low voltage alarm so we can disable voltage monitoring when discharge is complete.
				tcpm_set_voltage_alarm_lo(port, VSTOP_DISCHRG);

				// AutoDischargeDisconnect=0, Disable VCONN, Enable VBUS voltage monitor/alarms, Force discharge, Enable bleed.
				tcpc_write8(port, TCPC_REG_POWER_CTRL,
							(TCPC_PWR_CTRL_FORCE_DISCHARGE | TCPC_PWR_CTRL_ENABLE_BLEED_DISCHARGE));

				// Disable VBUS detect.
				tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_DISABLE_VBUS_DETECT);

				// Disable sink disconnect threshold.
				tcpm_set_sink_disconnect_threshold(port, 0);

				// Set TCPC control to default.
				tcpc_write8(port, TCPC_REG_TCPC_CTRL, 0);
			}

			// Configure role control.
			if (dev->role == ROLE_DRP)
			{
				// Set starting CC pin state for autonomous DRP toggle.
				cc_pull = (dev->state == TCPC_STATE_UNATTACHED_SNK) ? CC_RD : CC_RP;

				if (dev->silicon_revision <= 1)
				{
					/*** TUSB422 PG1.0/1.1 workaround for DRP toggle cycle not reset (CDDS #65) ***/
					// Clear the DRP bit to force the CC pin state immediately.
					tcpc_write8(port, TCPC_REG_ROLE_CTRL,
								tcpc_reg_role_ctrl_set(false, dev->rp_val, cc_pull, cc_pull));
				}

				tcpc_write8(port, TCPC_REG_ROLE_CTRL,
							tcpc_reg_role_ctrl_set(true, dev->rp_val, cc_pull, cc_pull));
			}
			else if (dev->role == ROLE_SNK)
			{
				tcpc_write8(port, TCPC_REG_ROLE_CTRL,
							tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_RD, CC_RD));
			}
			else /* ROLE_SRC */
			{
				tcpc_write8(port, TCPC_REG_ROLE_CTRL,
							tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_RP, CC_RP));
			}

			// Notify upper layer.
			tcpm_notify_conn_state(port, dev->state);

			// Look for connection.
			tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_SRC_LOOK4CONNECTION);

			if (dev->flags & TC_FLAGS_TEMP_ROLE)
			{
				tusb422_lfo_timer_start(&dev->timer2, T_TRY_ROLE_SWAP_MS, timeout_try_role_swap);
			}

#ifdef CONFIG_WAKELOCK
			tusb422_wake_lock_detach();
#endif
			break;

		case TCPC_STATE_TRY_WAIT_SRC:
			// Pull up both CC pins to Rp.
			tcpc_write8(port, TCPC_REG_ROLE_CTRL,
						tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_RP, CC_RP));

			timer_start(&dev->timer, T_DRP_TRY_MS, timeout_drp_try);
			break;

		case TCPC_STATE_TRY_WAIT_SNK:
			// Terminate both CC pins to Rd.
			tcpc_write8(port, TCPC_REG_ROLE_CTRL,
						tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_RD, CC_RD));

			timer_start(&dev->timer, T_PD_DEBOUNCE_MS, timeout_pd_debounce);
			break;

		case TCPC_STATE_ATTACHED_SNK:
		case TCPC_STATE_DEBUG_ACC_SNK:
			tcpm_handle_attached_state(port);

			if (cc1 > cc2)
			{
				// CC1 used for USB-PD.
				dev->plug_polarity = PLUG_UNFLIPPED;

				dev->src_current_adv = (tcpc_cc_snk_state_t)cc1;

				DEBUG("SRC current: %s\n",
					  (cc1 == CC_SNK_STATE_POWER30) ? "3.0A" :
					  (cc1 == CC_SNK_STATE_POWER15) ? "1.5A" :
					  (cc1 == CC_SNK_STATE_DEFAULT) ? "500/900mA" : "?");
			}
			else /* CC1 voltage < CC2 voltage */
			{
				// CC2 used for USB-PD.
				dev->plug_polarity = PLUG_FLIPPED;

				dev->src_current_adv = (tcpc_cc_snk_state_t)cc2;

				DEBUG("SRC current: %s\n",
					  (cc2 == CC_SNK_STATE_POWER30) ? "3.0A" :
					  (cc2 == CC_SNK_STATE_POWER15) ? "1.5A" :
					  (cc2 == CC_SNK_STATE_DEFAULT) ? "500/900mA" : "?");
			}

			// Set plug orientation for attached states.
			tcpc_write8(port, TCPC_REG_TCPC_CTRL,
						(dev->plug_polarity == PLUG_FLIPPED) ? TCPC_CTRL_PLUG_ORIENTATION : 0);

			// Update msg header info for UFP sink.
			tcpc_write8(port, TCPC_REG_MSG_HDR_INFO,
						TCPC_REG_MSG_HDR_INFO_SET(0, PD_DATA_ROLE_UFP, PD_PWR_ROLE_SNK));

			// AutoDischargeDisconnect=1, Enable VBUS voltage monitor & alarms, Enable Bleed discharge.
			tcpc_write8(port, TCPC_REG_POWER_CTRL,
						(TCPC_PWR_CTRL_AUTO_DISCHARGE_DISCONNECT | TCPC_PWR_CTRL_ENABLE_BLEED_DISCHARGE));

			// Set low voltage alarm to trigger transition to Unattached.SNK if
			// VBUS <= 4V for longer than (2 x tPDDebounce).
			tcpm_set_voltage_alarm_lo(port, VDISCON_MAX);

			// Enable VBUS sink.
			tcpm_snk_vbus_enable(port);

			// Notify upper layers.
			tcpm_notify_conn_state(port, dev->state);
			break;

		case TCPC_STATE_AUDIO_ACC:
			tcpm_handle_attached_state(port);

			// Notify upper layers.
			tcpm_notify_conn_state(port, dev->state);
			break;

		case TCPC_STATE_UNORIENTED_DEBUG_ACC_SRC:
			tcpm_handle_attached_state(port);

			// Update msg header info for DFP source.
			tcpc_write8(port, TCPC_REG_MSG_HDR_INFO,
						TCPC_REG_MSG_HDR_INFO_SET(0, PD_DATA_ROLE_DFP, PD_PWR_ROLE_SRC));

			// AutoDischargeDisconnect=1, VCONN=off, Enable VBUS voltage monitor & voltage alarms.
			tcpc_write8(port, TCPC_REG_POWER_CTRL, TCPC_PWR_CTRL_AUTO_DISCHARGE_DISCONNECT);

			// Enable VBUS source.
			tcpm_src_vbus_5v_enable(port);

			// Notify upper layers.
			tcpm_notify_conn_state(port, dev->state);
			break;

		case TCPC_STATE_ATTACHED_SRC:
		case TCPC_STATE_ORIENTED_DEBUG_ACC_SRC:
			tcpm_handle_attached_state(port);

			if (cc1 == CC_SRC_STATE_RD)
			{
				dev->plug_polarity = PLUG_UNFLIPPED;
			}
			else /* Rd on CC2 */
			{
				dev->plug_polarity = PLUG_FLIPPED;
			}

			// Set plug orientation for attached states.
			tcpc_write8(port, TCPC_REG_TCPC_CTRL,
						(dev->plug_polarity == PLUG_FLIPPED) ? TCPC_CTRL_PLUG_ORIENTATION : 0);

			// Update msg header info for DFP source.
			tcpc_write8(port, TCPC_REG_MSG_HDR_INFO,
						TCPC_REG_MSG_HDR_INFO_SET(0, PD_DATA_ROLE_DFP, PD_PWR_ROLE_SRC));

			if (dev->state == TCPC_STATE_ATTACHED_SRC)
			{
				if ((cc1 == CC_SRC_STATE_RA) ||
					(cc2 == CC_SRC_STATE_RA))
				{
					CRIT("VCONN enabled\n");

					// Remove Rp from VCONN pin.
					tcpm_remove_rp_from_vconn_pin(port);

					// AutoDischargeDisconnect=1, Enable VCONN, Enable VBUS voltage monitor & alarms.
					tcpc_write8(port, TCPC_REG_POWER_CTRL,
								(TCPC_PWR_CTRL_AUTO_DISCHARGE_DISCONNECT | TCPC_PWR_CTRL_ENABLE_VCONN));
				}
				else /* No Ra detected. Do not enable VCONN */
				{
					if (dev->silicon_revision <= 1)
					{
						/****** TUSB422 PG1.0/1.1 workaround for DFP may disconnect during PD receive (CDDS #63) ******/
						// Remove Rp from unconnected pin.
						tcpm_remove_rp_from_vconn_pin(port);
					}

					// AutoDischargeDisconnect=1, VCONN=off, Enable VBUS voltage monitor & alarms.
					tcpc_write8(port, TCPC_REG_POWER_CTRL, TCPC_PWR_CTRL_AUTO_DISCHARGE_DISCONNECT);
				}

#ifdef CONFIG_TUSB422_PAL
				usb_pd_pal_notify_connect_state(port, dev->state, tcpc_dev[port].plug_polarity);
#endif

				// Enable VBUS source.
				tcpm_src_vbus_5v_enable(port);

				// Notify upper layers after vSafe5V is reached.
				dev->src_attach_notify = true;
				tcpm_set_voltage_alarm_hi(port, VSAFE5V_MIN);
			}
			else /* TCPC_STATE_ORIENTED_DEBUG_ACC_SRC */
			{
				// Notify upper layers.
				tcpm_notify_conn_state(port, dev->state);
			}
			break;

		case TCPC_STATE_TRY_SRC:
		case TCPC_STATE_TRY_SNK:
			if (dev->silicon_revision == 0)
			{
				/****** TUSB422 PG1.0 workaround for role change issue (CDDS #41) ******/
				// Disable VBUS detect. (Try.SRC fix)
				tcpc_write8(port, TCPC_REG_COMMAND, TCPC_CMD_DISABLE_VBUS_DETECT);

				// Remove CC1 & CC2 terminations.
				tcpc_write8(port, TCPC_REG_ROLE_CTRL,
							tcpc_reg_role_ctrl_set(false, dev->rp_val, CC_OPEN, CC_OPEN));
			}

			// Try.SRC - Both CC1 and CC2 pulled to Rp.
			// Try.SNK - Both CC1 and CC2 terminated to Rd.
			cc_pull = (dev->state == TCPC_STATE_TRY_SNK) ? CC_RD : CC_RP;

			tcpc_write8(port, TCPC_REG_ROLE_CTRL,
						tcpc_reg_role_ctrl_set(false, dev->rp_val, cc_pull, cc_pull));

			timer_start(&dev->timer, T_DRP_TRY_MS, timeout_drp_try);
			break;

		case TCPC_STATE_TRY_SNK_LOOK4SRC:
			timer_start(&dev->timer, T_PD_DEBOUNCE_MS, timeout_pd_debounce);
			break;

		case TCPC_STATE_ERROR_RECOVERY:
			// Do nothing. Everything is handled in tcpm_execute_error_recovery() which is called directly.
			break;

		default:
			// Do nothing.
			break;
	}

	// Clear flag.
	dev->state_change = false;

	return;
}


static void alert_cc_status_handler(tcpc_device_t *dev)
{
	unsigned int cc1, cc2;
	usb_pd_port_t *pd_dev;

	// Read CC status.
	tcpc_read8(dev->port, TCPC_REG_CC_STATUS, &dev->cc_status);

	CRIT("CC status = 0x%02x\n", dev->cc_status);

	if (dev->state == TCPC_STATE_TRY_SNK)
	{
		// Do not monitor CC1 & CC2 while in Try.SNK.  Wait until tDRPTryWait expires.
		return;
	}

	if (!(dev->cc_status & CC_STATUS_LOOKING4CONNECTION))
	{
		cc1 = TCPC_CC1_STATE(dev->cc_status);
		cc2 = TCPC_CC2_STATE(dev->cc_status);

		// If open state on CC1 and CC2.
		if ((cc1 == CC_STATE_OPEN) &&
			(cc2 == CC_STATE_OPEN))
		{
			switch (dev->state)
			{
				case TCPC_STATE_ATTACH_WAIT_SRC:
				case TCPC_STATE_ATTACHED_SRC:
				case TCPC_STATE_UNORIENTED_DEBUG_ACC_SRC:
				case TCPC_STATE_ORIENTED_DEBUG_ACC_SRC:
					if ((dev->flags & TC_FLAGS_TRY_SRC) &&
						(dev->role == ROLE_DRP) &&
						(dev->state == TCPC_STATE_ATTACHED_SRC))
					{
						// If exiting Attached.SRC and Try.SRC is supported,
						// disable VBUS and transition to TryWait.SNK.
						tcpm_src_vbus_disable(dev->port);

						tcpm_set_state(dev, TCPC_STATE_TRY_WAIT_SNK);
					}
					else if (dev->role == ROLE_DRP)
					{
						tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
					}
					else
					{
						tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SRC);
					}
					break;

				case TCPC_STATE_AUDIO_ACC:
					// Debounce for tCCDebounce.
					timer_start(&dev->timer, T_CC_DEBOUNCE_MS, timeout_cc_debounce);
					break;

				case TCPC_STATE_TRY_SNK_LOOK4SRC:
					// Restart tPDDebounce timer.
					timer_start(&dev->timer, T_PD_DEBOUNCE_MS, timeout_pd_debounce);
					break;

				case TCPC_STATE_ATTACH_WAIT_SNK:
				case TCPC_STATE_TRY_WAIT_SNK:
					// Debounce for tPDDebounce.
					// Use LFO timer to prevent stopping concurrent CC debounce timer.
					tusb422_lfo_timer_start(&dev->timer2, T_PD_DEBOUNCE_MS, timeout_pd_debounce);
					break;

				case TCPC_STATE_ATTACHED_SNK:
				case TCPC_STATE_DEBUG_ACC_SNK:
					pd_dev = usb_pd_pe_get_device(dev->port);
					if (*pd_dev->current_state != PE_PRS_TRANSITION_TO_OFF)
					{
						tcpm_enable_vbus_detect(dev->port);
					}
					break;

				default:
					// Do nothing. We are either waiting for VBUS removal or a timeout to occur.
					break;
			}
		}
		else /* At least one CC pin is connected */
		{
			// Cancel tPDDebounce timer.
			if (dev->timer2.function == timeout_pd_debounce)
			{
				tusb422_lfo_timer_cancel(&dev->timer2);
			}

			switch (dev->state)
			{
				case TCPC_STATE_UNATTACHED_SRC:
				case TCPC_STATE_UNATTACHED_SNK:
					if (dev->cc_status & CC_STATUS_CONNECT_RESULT)
					{
						/* TCPC is presenting Rd */
						/* Rp was detected on at least one CC pin */

						// Enable VBUS detection.
						tcpm_enable_vbus_detect(dev->port);

						tcpm_set_state(dev, TCPC_STATE_ATTACH_WAIT_SNK);

						// Debounce CC.
						timer_start(&dev->timer, T_CC_DEBOUNCE_MS, timeout_cc_debounce);
					}
					else /* TCPC is presenting Rp */
					{
						// If Rd on either CC pin or Ra on both CC pins.
						if (((cc1 == CC_SRC_STATE_RD) || (cc2 == CC_SRC_STATE_RD)) ||
							((cc1 == CC_SRC_STATE_RA) && (cc2 == CC_SRC_STATE_RA)))
						{
							// Enable voltage monitoring.
							tcpm_enable_voltage_monitoring(dev->port);

							// Check if VBUS is below vSafe0V.
							if (tcpm_get_vbus_voltage(dev->port) < VSAFE0V_MAX)
							{
								tcpm_set_state(dev, TCPC_STATE_ATTACH_WAIT_SRC);

								// Debounce CC.
								timer_start(&dev->timer, T_CC_DEBOUNCE_MS, timeout_cc_debounce);
							}
							else
							{
								tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SRC);
							}
						}
					}
					break;

				case TCPC_STATE_ATTACH_WAIT_SNK:
					// Do nothing.  Wait for CC debounce timer to expire.
					break;

				case TCPC_STATE_ATTACH_WAIT_SRC:
					if (((cc1 == CC_STATE_OPEN) && (cc2 == CC_SRC_STATE_RA)) ||
						((cc1 == CC_SRC_STATE_RA) && (cc2 == CC_STATE_OPEN)))
					{
						if (dev->role == ROLE_DRP)
						{
							tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
						}
						else
						{
							tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SRC);
						}
					}
					break;

				case TCPC_STATE_TRY_SNK_LOOK4SRC:
					// Check for Rp on exactly one CC pin.
					if (((cc1 == CC_SNK_STATE_OPEN) && (cc2 != CC_SNK_STATE_OPEN)) ||
						((cc1 != CC_SNK_STATE_OPEN) && (cc2 == CC_SNK_STATE_OPEN)))
					{
						// Restart tPDDebounce timer.
						timer_start(&dev->timer, T_PD_DEBOUNCE_MS, timeout_pd_debounce);
					}
					break;

				case TCPC_STATE_TRY_WAIT_SNK:
					// Enable VBUS detection.
					tcpm_enable_vbus_detect(dev->port);

					// Debounce CC.
					timer_start(&dev->timer, T_CC_DEBOUNCE_MS, timeout_cc_debounce);
					break;

				case TCPC_STATE_TRY_SRC:
				case TCPC_STATE_TRY_WAIT_SRC:
					// Check for Rd on exactly one CC pin.
					if (((cc1 == CC_SRC_STATE_RD) && (cc2 != CC_SRC_STATE_RD)) ||
						((cc1 != CC_SRC_STATE_RD) && (cc2 == CC_SRC_STATE_RD)))
					{
						// Debounce.
						timer_start(&dev->timer, T_PD_DEBOUNCE_MS, timeout_pd_debounce);
					}
					break;

				case TCPC_STATE_UNORIENTED_DEBUG_ACC_SRC:
					if ((cc1 == CC_SRC_STATE_RA) ||
						(cc2 == CC_SRC_STATE_RA))
					{
						tcpm_set_state(dev, TCPC_STATE_ORIENTED_DEBUG_ACC_SRC);
					}
					break;

				case TCPC_STATE_ATTACHED_SNK:
				case TCPC_STATE_DEBUG_ACC_SNK:
					// Report current change to upper layers.
					if (dev->plug_polarity == PLUG_UNFLIPPED)
					{
						dev->src_current_adv = (tcpc_cc_snk_state_t)cc1;
					}
					else
					{
						dev->src_current_adv = (tcpc_cc_snk_state_t)cc2;
					}

					tcpm_notify_current_change(dev->port, dev->src_current_adv);
					break;

				default:
					break;
			}
		}
	}

	return;
}


static void alert_power_status_handler(tcpc_device_t *dev)
{
	unsigned int cc1, cc2;
	uint8_t pwr_status;

	// Read power status.
	tcpc_read8(dev->port, TCPC_REG_POWER_STATUS, &pwr_status);

	INFO("pwr_status = 0x%02x\n", pwr_status);

	if (pwr_status & TCPC_PWR_STATUS_VBUS_PRES_DETECT_EN)
	{
		if (pwr_status & TCPC_PWR_STATUS_VBUS_PRESENT)
		{
			DEBUG("VBUS present\n");

			if (dev->src_detected)
			{
				if (dev->state == TCPC_STATE_ATTACH_WAIT_SNK)
				{
					cc1 = TCPC_CC1_STATE(dev->cc_status);
					cc2 = TCPC_CC2_STATE(dev->cc_status);

					if ((cc1 != CC_SNK_STATE_OPEN) &&
						(cc2 != CC_SNK_STATE_OPEN))
					{
						// Debug Accessory if SNK.Rp on both CC1 and CC2.
						tcpm_set_state(dev, TCPC_STATE_DEBUG_ACC_SNK);
					}
					else if ((dev->flags & TC_FLAGS_TRY_SRC) &&
							 (dev->role == ROLE_DRP))
					{
						tcpm_set_state(dev, TCPC_STATE_TRY_SRC);
					}
					else
					{
						tcpm_set_state(dev, TCPC_STATE_ATTACHED_SNK);
					}
				}
				else if ((dev->state == TCPC_STATE_TRY_SNK_LOOK4SRC) ||
						 (dev->state == TCPC_STATE_TRY_WAIT_SNK))
				{
					tcpm_set_state(dev, TCPC_STATE_ATTACHED_SNK);
				}
			}
		}
		else /* VBUS below threshold */
		{
			if ((dev->state == TCPC_STATE_ATTACHED_SNK) ||
				(dev->state == TCPC_STATE_DEBUG_ACC_SNK))
			{
				// Unattached.SNK.
				tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
			}
		}
	}

	return;
}


static void alert_fault_status_handler(tcpc_device_t *dev)
{
	uint8_t status;

	tcpc_read8(dev->port, TCPC_REG_FAULT_STATUS, &status);

	CRIT("Fault status = 0x%02x\n", status);

	if (status & TCPC_AUTO_DIS_FAIL_STATUS)
	{
		if (dev->silicon_revision == 0)
		{
			// Stop VBUS discharge.
			tusb422_stop_vbus_discharge(dev->port);
		}
	}

	if (status & TCPC_FORCE_DIS_FAIL_STATUS)
	{
		// Disable force VBUS discharge.
		tcpc_modify8(dev->port, TCPC_REG_POWER_CTRL, TCPC_PWR_CTRL_FORCE_DISCHARGE, 0);
	}

	if (status & TCPC_VCONN_OCP_FAULT_STATUS)
	{
		DEBUG("VCONN OCP\n");
		dev->vconn_ocp_cnt++;
	}

	// Clear status.
	tcpc_write8(dev->port, TCPC_REG_FAULT_STATUS, status);

	return;
}

static void tcpm_alert_handler(unsigned int port)
{
	unsigned int cc1, cc2;
	uint16_t alert;
	uint16_t clear_bits;
	uint16_t v_threshold;
	tcpc_device_t *dev = &tcpc_dev[port];

	// Read alerts.
	tcpc_read16(port, TCPC_REG_ALERT, &alert);

	INFO("->P%u IRQ: 0x%04x\n", port, alert);

	// Clear alerts except voltage alarms, fault, vendor IRQ, and Rx status which cannot be cleared until after servicing.
	clear_bits = alert & ~(TCPC_ALERT_RX_STATUS | TCPC_ALERT_FAULT |
						   TCPC_ALERT_VOLT_ALARM_HI | TCPC_ALERT_VOLT_ALARM_LO | TUSB422_ALERT_IRQ_STATUS);

	if (clear_bits)
	{
		tcpc_write16(port, TCPC_REG_ALERT, clear_bits);
	}

	if (alert & TUSB422_ALERT_IRQ_STATUS)
	{
		tusb422_isr(port);

		// Clear alert.
		tcpc_write16(port, TCPC_REG_ALERT, TUSB422_ALERT_IRQ_STATUS);
	}

	if (alert & TCPC_ALERT_VBUS_DISCONNECT)
	{
		// Not active unless VBUS SNK DISCONNECT THRESHOLD is set.
		// Do nothing.  If we are sink, wait for POWER_STATUS.VbusPresent = 0.
	}

	if (alert & TCPC_ALERT_RX_BUF_OVERFLOW)
	{
		CRIT("Alert: Rx Buff overflow!\n");
		dev->rx_buff_overflow_cnt++;
	}

	if (alert & TCPC_ALERT_FAULT)
	{
		alert_fault_status_handler(dev);
		// Clear alert.
		tcpc_write16(port, TCPC_REG_ALERT, TCPC_ALERT_FAULT);
	}

	if (alert & TCPC_ALERT_VOLT_ALARM_LO)
	{
		v_threshold = tcpm_get_voltage_alarm_lo_threshold(port);

		// Clear alarm threshold.
		tcpc_write16(port, TCPC_REG_VBUS_VOLTAGE_ALARM_LO_CFG, 0);
		// Clear alert.
		tcpc_write16(port, TCPC_REG_ALERT, TCPC_ALERT_VOLT_ALARM_LO);

		if ((dev->state == TCPC_STATE_UNATTACHED_SRC) ||
			(dev->state == TCPC_STATE_UNATTACHED_SNK))
		{
			// Disable force discharge.
			// AutoDischargeDisconnect=0, Disable VCONN, Disable VBUS voltage monitor/alarms, Enable bleed.
			tcpc_write8(port, TCPC_REG_POWER_CTRL,
						(TCPC_PWR_CTRL_DEFAULTS | TCPC_PWR_CTRL_ENABLE_BLEED_DISCHARGE));
		}
		else if (dev->state == TCPC_STATE_ATTACH_WAIT_SRC)
		{
			// Start timer to transition to Attached.SRC after vSafe0V and sink detected for tCCDebounce.
			timer_start(&dev->timer, T_CC_DEBOUNCE_MS, timeout_cc_debounce);
		}
		else if ((dev->state == TCPC_STATE_TRY_SRC) ||
				 (dev->state == TCPC_STATE_TRY_WAIT_SRC))
		{
			// Read CC status.
			tcpc_read8(port, TCPC_REG_CC_STATUS, &dev->cc_status);
			DEBUG("%s CC status = 0x%x\n", __func__, dev->cc_status);

			cc1 = TCPC_CC1_STATE(dev->cc_status);
			cc2 = TCPC_CC2_STATE(dev->cc_status);

			// Check for Rd on exactly one pin.
			if (((cc1 == CC_SRC_STATE_RD) && (cc2 != CC_SRC_STATE_RD)) ||
				((cc1 != CC_SRC_STATE_RD) && (cc2 == CC_SRC_STATE_RD)))
			{
				// Wait for tCCDebounce before we transition to Attached.SRC and enable VBUS.
				timer_start(&dev->timer, T_CC_DEBOUNCE_MS, timeout_cc_debounce);
			}
			else if (dev->state == TCPC_STATE_TRY_SRC)
			{
				// Cancel tTryTimeout timer.
				timer_cancel(&dev->timer);

				tcpm_set_state(dev, TCPC_STATE_TRY_WAIT_SNK);
			}
		}
		else if ((dev->state == TCPC_STATE_ATTACHED_SNK) ||
				 (dev->state == TCPC_STATE_DEBUG_ACC_SNK))
		{
			if (v_threshold == VDISCON_MAX)
			{
				// Debounce for (2 x tPDDebounce). (per USB-IF recommendation)
				timer_start(&dev->timer, (T_PD_DEBOUNCE_MS * 2), timeout_vbus4v_debounce);
			}
		}

		// Notify upper layers.
		tcpm_notify_voltage_alarm(port, false);
	}

	if (alert & TCPC_ALERT_VOLT_ALARM_HI)
	{
		// Set alarm threshold to max.
		tcpc_write16(port, TCPC_REG_VBUS_VOLTAGE_ALARM_HI_CFG, 0x3FF);
		// Clear alert.
		tcpc_write16(port, TCPC_REG_ALERT, TCPC_ALERT_VOLT_ALARM_HI);

		if (dev->state == TCPC_STATE_ATTACHED_SRC)
		{
			if (dev->src_attach_notify)
			{
				dev->src_attach_notify = false;

				// Notify upper layers.
				tcpm_notify_conn_state(port, dev->state);
			}
		}

		// Notify upper layers.
		tcpm_notify_voltage_alarm(port, true);
	}

	// Sending a Hard Reset will set both SUCCESS and FAILED status.
	if (alert & TCPC_ALERT_TX_SUCCESS)
	{
		tcpm_notify_pd_transmit(port, TX_STATUS_SUCCESS);
	}
	else if (alert & TCPC_ALERT_TX_DISCARDED)
	{
		tcpm_notify_pd_transmit(port, TX_STATUS_DISCARDED);
	}
	else if (alert & TCPC_ALERT_TX_FAILED)
	{
		tcpm_notify_pd_transmit(port, TX_STATUS_FAILED);
	}

	if (alert & TCPC_ALERT_RX_HARD_RESET)
	{
		tcpm_notify_hard_reset(port);
	}

	if (alert & TCPC_ALERT_RX_STATUS)
	{
		tcpm_notify_pd_receive(port);

		// Clear alert.
		tcpc_write16(port, TCPC_REG_ALERT, TCPC_ALERT_RX_STATUS);
	}

	if (alert & TCPC_ALERT_POWER_STATUS)
	{
		alert_power_status_handler(dev);
	}

	if (alert & TCPC_ALERT_CC_STATUS)
	{
		alert_cc_status_handler(dev);
	}

	return;
}


static int tcpm_port_init(unsigned int port, const tcpc_config_t *config)
{
	tcpc_device_t *dev = &tcpc_dev[port];
	uint8_t pwr_status;
	uint16_t id;

#ifndef	CONFIG_TUSB422
	tcpc_config(port, config->intf, config->slave_addr);
#endif

	dev->role = config->role;
	dev->flags = config->flags;
	dev->port = port;
	dev->rp_val = config->rp_val;

	dev->timer.data = port;
	dev->timer2.data = port;
	dev->state = TCPC_STATE_DISABLED;
	dev->rx_buff_overflow_cnt = 0;
	dev->vconn_ocp_cnt = 0;
	dev->src_attach_notify = false;
	dev->src_detected = false;

	if (dev->role == ROLE_SNK)
	{
		tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SNK);
	}
	else /* ROLE_SRC or ROLE_DRP */
	{
		tcpm_set_state(dev, TCPC_STATE_UNATTACHED_SRC);
	}

	PRINT("Port[%u]: addr: 0x%02x, %s, Rp: %s, Flags: %s.\n",
		  port, config->slave_addr,
		  (dev->role == ROLE_SRC) ? "SRC" :
		  (dev->role == ROLE_SNK) ? "SNK" : "DRP",
		  (dev->rp_val == RP_DEFAULT_CURRENT) ? "default" :
		  (dev->rp_val == RP_MEDIUM_CURRENT) ? "1.5A" : "3.0A",
		  (dev->flags & TC_FLAGS_TRY_SRC) ? "Try-SRC" : (dev->flags & TC_FLAGS_TRY_SNK) ? "Try-SNK" : "None");

	// Read VID/PID/DID.
	tcpc_read16(port, TCPC_REG_VENDOR_ID, &id);
	PRINT("VID: 0x%04x\n", id);
	if (id != TI_VID)
		return ERR_NO_TI_DEV;

	tcpc_read16(port, TCPC_REG_PRODUCT_ID, &id);
	PRINT("PID: 0x%04x\n", id);
	if (id != TI_PID)
		return ERR_NO_TI_DEV;

	tcpc_read16(port, TCPC_REG_DEVICE_ID, &id);
	PRINT("DID: 0x%04x\n", id);

	// Wait for TCPC init status to clear.
	do
	{
		tcpc_read8(port, TCPC_REG_POWER_STATUS, &pwr_status);

	} while (pwr_status & TCPC_PWR_STATUS_TCPC_INIT_STATUS);

#ifdef DISABLE_VCONN_OC_DETECT
	// Disable VCONN OC fault detection.
	tcpc_modify8(port, TCPC_REG_FAULT_CTRL, 0, TCPC_FLT_CTRL_VCONN_OC_FAULT);
#endif

	if (!tusb422_is_trimmed(port))
	{
		PRINT("Warning: Chip is not factory trimmed. Using nominal soft trim values.\n");
	}

	// Initialize vendor-specific registers.
	tusb422_init(port);

	// Read the silicon revision.
	dev->silicon_revision = tusb422_get_revision(port);
	PRINT("REV: 0x%02x\n", dev->silicon_revision);

	return 0;
}

int tcpm_init(const tcpc_config_t *config)
{
	unsigned int port;
	int ret;

#ifndef	CONFIG_TUSB422
	// Initialize I2C master.
	tcpc_init();
#endif

	// Init all TCPC devices.
	for (port = 0; port < NUM_TCPC_DEVICES; port++)
	{
		ret = tcpm_port_init(port, &config[port]);
		if (ret)
			break;
	}

	return ret;
}



//
// Events
//
//*****************************************************************************
//
//! Event for alert
//!
//! Event called by HAL when alert line goes low to indicate that an interrupt
//! has occurred
//!
//! \return  true to wake-up MCU, false to stay in LPMx
//
// *****************************************************************************
bool tcpm_alert_event(unsigned int port)
{
	tcpm_alert_handler(port);

	return true;
}


bool tcpm_vbus_snk_fault_event(unsigned int port)
{
	CRIT("VBUS SNK fault!\n");

	return false;
}


bool tcpm_vbus_src_fault_event(unsigned int port)
{
	CRIT("VBUS SRC fault!\n");

	return false;
}
