#include <linux/kernel.h>
#include <linux/stat.h>                                                         // File permission masks
#include <linux/types.h>                                                        // Kernel datatypes
#include <linux/i2c.h>                                                          // I2C access, mutex
#include <linux/errno.h>                                                        // Linux kernel error definitions
#include <linux/hrtimer.h>                                                      // hrtimer
#include <linux/workqueue.h>                                                    // work_struct, delayed_work
#include <linux/delay.h>                                                        // udelay, usleep_range, msleep
#include <linux/wakelock.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/of_irq.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/irqflags.h>

#include "fusb30x_global.h"                                                     // Chip structure access
#include "../core/core.h"                                                       // Core access
#include "platform_helpers.h"
#include "huawei_platform/power/charger/direct_charger/loadswitch/rt9748/rt9748.h"
#include "../core/platform.h"

#ifdef CONFIG_DUAL_ROLE_USB_INTF
#include <linux/usb/class-dual-role.h>
#endif
#ifdef FSC_DEBUG
#include "hostcomm.h"
#include "../core/PD_Types.h"                                                   // State Log states
#include "../core/TypeC_Types.h"                                                // State Log states
#endif // FSC_DEBUG

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/********************************************        GPIO Interface         ******************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
const char* FUSB_DT_INTERRUPT_INTN =    "fsc_interrupt_int_n";      // Name of the INT_N interrupt in the Device Tree
#define FUSB_DT_GPIO_INTN               "fairchild,int_n"           // Name of the Int_N GPIO pin in the Device Tree
#define FUSB_DT_GPIO_VBUS_5V            "fairchild,vbus5v"          // Name of the VBus 5V GPIO pin in the Device Tree
#define FUSB_DT_GPIO_VBUS_OTHER         "fairchild,vbusOther"       // Name of the VBus Other GPIO pin in the Device Tree

#ifdef FSC_DEBUG
#define FUSB_DT_GPIO_DEBUG_SM_TOGGLE    "fairchild,dbg_sm"          // Name of the debug State Machine toggle GPIO pin in the Device Tree
#endif  // FSC_DEBUG

#ifdef FSC_INTERRUPT_TRIGGERED
/* Internal forward declarations */
static irqreturn_t _fusb_isr_intn(int irq, void *dev_id);
#endif  // FSC_INTERRUPT_TRIGGERED





static void fusb_force_source(struct dual_role_phy_instance *dual_role)
{
    struct fusb30x_chip* chip;

    chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }

    FSC_PRINT("FUSB  %s - Force State Source\n", __func__);
    core_set_source();
    fusb_StartTimers(&chip->timer_force_timeout, 1500); /* ms */
	if (dual_role) {
		dual_role_instance_changed(dual_role);
	}
}

static void fusb_force_sink(struct dual_role_phy_instance *dual_role)
{
    struct fusb30x_chip* chip;

    chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }

    FSC_PRINT("FUSB  %s - Force State Sink\n", __func__);
    core_set_sink();
    fusb_StartTimers(&chip->timer_force_timeout, 1500); /* ms */
	if (dual_role) {
		dual_role_instance_changed(dual_role);
	}
}
#ifdef CONFIG_DUAL_ROLE_USB_INTF
static enum dual_role_property fusb_dual_role_props[] = {
	DUAL_ROLE_PROP_SUPPORTED_MODES,
	DUAL_ROLE_PROP_MODE,
	DUAL_ROLE_PROP_PR,
	DUAL_ROLE_PROP_DR,
	DUAL_ROLE_PROP_VCONN_SUPPLY,
};
static int fusb_get_dual_role_mode(void)
{
	struct fusb30x_chip* chip = fusb30x_GetChip();
	int mode = DUAL_ROLE_PROP_MODE_NONE;
	FSC_PRINT("%s +\n", __func__);
	if (chip->orientation != NONE)
	{
		if (chip->sourceOrSink == SOURCE)
		{
			mode = DUAL_ROLE_PROP_MODE_DFP;
		}
		else
		{
			mode = DUAL_ROLE_PROP_MODE_UFP;
		}
	}
	else if(chip->orientation == NONE)
	{
		mode = DUAL_ROLE_PROP_MODE_NONE;
	}
	FSC_PRINT("%s - orientation %d, sourceOrSink %d, mode %d\n", __func__, chip->orientation, chip->sourceOrSink, mode);
	return mode;
}
static int fusb_dual_role_get_prop(struct dual_role_phy_instance *dual_role,
			enum dual_role_property prop, unsigned int *val)
{
	int ret = 0;
	int mode = fusb_get_dual_role_mode();
	FSC_PRINT("%s + prop =  %d, mode = %d\n", __func__, prop, mode);
	switch (prop) {
	case DUAL_ROLE_PROP_SUPPORTED_MODES:
		*val = DUAL_ROLE_SUPPORTED_MODES_DFP_AND_UFP;
		break;
	case DUAL_ROLE_PROP_MODE:
		*val = mode;
		break;
	case DUAL_ROLE_PROP_PR:
		{
			switch(mode)
			{
				case DUAL_ROLE_PROP_MODE_DFP:
					*val = DUAL_ROLE_PROP_PR_SRC;
					FSC_PRINT("%s + prop =  %d, mode = DUAL_ROLE_PROP_PR_SRC\n", __func__, prop);
					break;
				case DUAL_ROLE_PROP_MODE_UFP:
					*val = DUAL_ROLE_PROP_PR_SNK;
					FSC_PRINT("%s + prop =  %d, mode = DUAL_ROLE_PROP_PR_SNK\n", __func__, prop);
					break;
				default:
					*val = DUAL_ROLE_PROP_PR_NONE;
					FSC_PRINT("%s + prop =  %d, mode = DUAL_ROLE_PROP_PR_NONE\n", __func__, prop);
					break;
			}
		}
		break;
	case DUAL_ROLE_PROP_DR:
		{
			switch(mode)
			{
				case DUAL_ROLE_PROP_MODE_DFP:
					*val = DUAL_ROLE_PROP_DR_HOST;
					FSC_PRINT("%s + prop =  %d, mode = DUAL_ROLE_PROP_DR_HOST\n", __func__, prop);
					break;
				case DUAL_ROLE_PROP_MODE_UFP:
					*val = DUAL_ROLE_PROP_DR_DEVICE;
					FSC_PRINT("%s + prop =  %d, mode = DUAL_ROLE_PROP_DR_DEVICE\n", __func__, prop);
					break;
				default:
					*val = DUAL_ROLE_PROP_DR_NONE;
					FSC_PRINT("%s + prop =  %d, mode = DUAL_ROLE_PROP_DR_NONE\n", __func__, prop);
					break;
			}
		}
		break;
	case DUAL_ROLE_PROP_VCONN_SUPPLY:
		{
			switch(mode)
			{
				case DUAL_ROLE_PROP_MODE_DFP:
					*val = DUAL_ROLE_PROP_VCONN_SUPPLY_YES;
					FSC_PRINT("%s + prop =  %d, mode = DUAL_ROLE_PROP_DR_HOST\n", __func__, prop);
					break;
				case DUAL_ROLE_PROP_MODE_UFP:
					*val = DUAL_ROLE_PROP_VCONN_SUPPLY_NO;
					FSC_PRINT("%s + prop =  %d, mode = DUAL_ROLE_PROP_DR_DEVICE\n", __func__, prop);
					break;
				default:
					*val = DUAL_ROLE_PROP_VCONN_SUPPLY_NO;
					FSC_PRINT("%s + prop =  %d, mode = DUAL_ROLE_PROP_DR_NONE\n", __func__, prop);
					break;
			}
		}
		break;
	default:
		ret = -EINVAL;
		break;
	}
	FSC_PRINT("%s - %d\n", __func__, ret);
	return ret;
}
static int fusb_dual_role_prop_is_writeable(
	struct dual_role_phy_instance *dual_role, enum dual_role_property prop)
{
	FSC_PRINT("%s +\n", __func__);
	switch (prop) {
		case DUAL_ROLE_PROP_PR:
		case DUAL_ROLE_PROP_DR:
			return 1;
	}
	return 0;
}
static int fusb_dual_role_set_prop(struct dual_role_phy_instance *dual_role,
			enum dual_role_property prop, const unsigned int *val)
{
	struct fusb30x_chip* chip = fusb30x_GetChip();
	int mode = DUAL_ROLE_PROP_MODE_NONE;
	mode = fusb_get_dual_role_mode();
	FSC_PRINT("%s +  prop= %d   val=  %d   mode = %d\n", __func__, prop, *val, mode);

	switch (prop) {
		case DUAL_ROLE_PROP_MODE:
			if(*val != mode)
			{
				if(DUAL_ROLE_PROP_MODE_UFP == mode)
					fusb_force_source(dual_role);
				else if(DUAL_ROLE_PROP_MODE_DFP == mode)
					fusb_force_sink(dual_role);
			}
			break;
		case DUAL_ROLE_PROP_PR:
			if((*val == DUAL_ROLE_PROP_PR_SRC) && (mode == DUAL_ROLE_PROP_MODE_UFP))
			{
				fusb_force_source(dual_role);
			}
			else if((*val == DUAL_ROLE_PROP_PR_SNK) && (mode == DUAL_ROLE_PROP_MODE_DFP))
			{
				fusb_force_sink(dual_role);
			}
			break;
		case DUAL_ROLE_PROP_DR:
			FSC_PRINT("%s DUAL_ROLE_PROP_DR\n", __func__);
			break;
		default:
			FSC_PRINT("%s default case\n", __func__);
			break;
	}
	FSC_PRINT("%s -\n", __func__);
	return 0;
}
FSC_S32 fusb_dual_role_phy_init(void)
{
	FSC_PRINT("%s +\n", __func__);
	struct dual_role_phy_desc *dual_desc;
	struct dual_role_phy_instance *dual_role;
	struct fusb30x_chip* chip = fusb30x_GetChip();
	dual_desc = devm_kzalloc(&chip->client->dev, sizeof(struct dual_role_phy_desc), GFP_KERNEL);
	if (!dual_desc) {
		pr_err("unable to allocate dual role descriptor\n");
		return -ENOMEM;
	}
	dual_role = devm_kzalloc(&chip->client->dev, sizeof(struct dual_role_phy_instance), GFP_KERNEL);
	if (!dual_role) {
		pr_err("unable to allocate dual role phy instance\n");
		return -ENOMEM;
	}
	dual_desc->name = "otg_default";
	dual_desc->supported_modes = DUAL_ROLE_SUPPORTED_MODES_DFP_AND_UFP;
	dual_desc->properties = fusb_dual_role_props;
	dual_desc->num_properties = ARRAY_SIZE(fusb_dual_role_props);
	dual_desc->get_property = fusb_dual_role_get_prop;
	dual_desc->set_property = fusb_dual_role_set_prop;
	dual_desc->property_is_writeable = fusb_dual_role_prop_is_writeable;

	dual_role = devm_dual_role_instance_register(&chip->client->dev, dual_desc);
	if (IS_ERR(dual_role)) {
		pr_err("fusb fail to register dual role usb\n");
		return -EINVAL;
	}
	chip->dual_desc = dual_desc;
	chip->dual_role = dual_role;
	FSC_PRINT("%s -\n", __func__);
	return 0;
}
#endif /* CONFIG_DUAL_ROLE_USB_INTF */

FSC_S32 fusb_InitializeGPIO(void)
{
    FSC_S32 ret = 0;
    struct device_node* node;
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return -ENOMEM;
    }
    /* Get our device tree node */
    node = chip->client->dev.of_node;

    /* Get our GPIO pins from the device tree, allocate them, and then set their direction (input/output) */
    chip->gpio_IntN = of_get_named_gpio(node, FUSB_DT_GPIO_INTN, 0);
    if (!gpio_is_valid(chip->gpio_IntN))
    {
        dev_err(&chip->client->dev, "%s - Error: Could not get named GPIO for Int_N! Error code: %d\n", __func__, chip->gpio_IntN);
        return chip->gpio_IntN;
    }

    // Request our GPIO to reserve it in the system - this should help ensure we have exclusive access (not guaranteed)
    ret = gpio_request(chip->gpio_IntN, FUSB_DT_GPIO_INTN);
    if (ret < 0)
    {
        dev_err(&chip->client->dev, "%s - Error: Could not request GPIO for Int_N! Error code: %d\n", __func__, ret);
        return ret;
    }

    ret = gpio_direction_input(chip->gpio_IntN);
    if (ret < 0)
    {
        dev_err(&chip->client->dev, "%s - Error: Could not set GPIO direction to input for Int_N! Error code: %d\n", __func__, ret);
        return ret;
    }

    return ret;

#ifdef FSC_DEBUG
    /* Export to sysfs */
    gpio_export(chip->gpio_IntN, false);
    gpio_export_link(&chip->client->dev, FUSB_DT_GPIO_INTN, chip->gpio_IntN);
#endif // FSC_DEBUG

    FSC_PRINT("FUSB  %s - INT_N GPIO initialized as pin '%d'\n", __func__, chip->gpio_IntN);


    // VBus 5V
    chip->gpio_VBus5V = of_get_named_gpio(node, FUSB_DT_GPIO_VBUS_5V, 0);
    if (!gpio_is_valid(chip->gpio_VBus5V))
    {
        dev_err(&chip->client->dev, "%s - Error: Could not get named GPIO for VBus5V! Error code: %d\n", __func__, chip->gpio_VBus5V);
        fusb_GPIO_Cleanup();
        return chip->gpio_VBus5V;
    }

    // Request our GPIO to reserve it in the system - this should help ensure we have exclusive access (not guaranteed)
    ret = gpio_request(chip->gpio_VBus5V, FUSB_DT_GPIO_VBUS_5V);
    if (ret < 0)
    {
        dev_err(&chip->client->dev, "%s - Error: Could not request GPIO for VBus5V! Error code: %d\n", __func__, ret);
        return ret;
    }

    ret = gpio_direction_output(chip->gpio_VBus5V, chip->gpio_VBus5V_value);
    if (ret < 0)
    {
        dev_err(&chip->client->dev, "%s - Error: Could not set GPIO direction to output for VBus5V! Error code: %d\n", __func__, ret);
        fusb_GPIO_Cleanup();
        return ret;
    }

#ifdef FSC_DEBUG
    // Export to sysfs
    gpio_export(chip->gpio_VBus5V, false);
    gpio_export_link(&chip->client->dev, FUSB_DT_GPIO_VBUS_5V, chip->gpio_VBus5V);
#endif // FSC_DEBUG

    FSC_PRINT("FUSB  %s - VBus 5V initialized as pin '%d' and is set to '%d'\n", __func__, chip->gpio_VBus5V, chip->gpio_VBus5V_value ? 1 : 0);

    // VBus other (eg. 12V)
    // NOTE - This VBus is optional, so if it doesn't exist then fake it like it's on.
    chip->gpio_VBusOther = of_get_named_gpio(node, FUSB_DT_GPIO_VBUS_OTHER, 0);
    if (!gpio_is_valid(chip->gpio_VBusOther))
    {
        // Soft fail - provide a warning, but don't quit because we don't really need this VBus if only using VBus5v
        pr_warning("%s - Warning: Could not get GPIO for VBusOther! Error code: %d\n", __func__, chip->gpio_VBusOther);
    }
    else
    {
        // Request our GPIO to reserve it in the system - this should help ensure we have exclusive access (not guaranteed)
        ret = gpio_request(chip->gpio_VBusOther, FUSB_DT_GPIO_VBUS_OTHER);
        if (ret < 0)
        {
            dev_err(&chip->client->dev, "%s - Error: Could not request GPIO for VBusOther! Error code: %d\n", __func__, ret);
            return ret;
        }

        ret = gpio_direction_output(chip->gpio_VBusOther, chip->gpio_VBusOther_value);
        if (ret != 0)
        {
            dev_err(&chip->client->dev, "%s - Error: Could not set GPIO direction to output for VBusOther! Error code: %d\n", __func__, ret);
            return ret;
        }
        else
        {
            FSC_PRINT("FUSB  %s - VBusOther initialized as pin '%d' and is set to '%d'\n", __func__, chip->gpio_VBusOther, chip->gpio_VBusOther_value ? 1 : 0);

        }
    }

#ifdef FSC_DEBUG
    // State Machine Debug Notification
    // Optional GPIO - toggles each time the state machine is called
    chip->dbg_gpio_StateMachine = of_get_named_gpio(node, FUSB_DT_GPIO_DEBUG_SM_TOGGLE, 0);
    if (!gpio_is_valid(chip->dbg_gpio_StateMachine))
    {
        // Soft fail - provide a warning, but don't quit because we don't really need this VBus if only using VBus5v
        pr_warning("%s - Warning: Could not get GPIO for Debug GPIO! Error code: %d\n", __func__, chip->dbg_gpio_StateMachine);
    }
    else
    {
        // Request our GPIO to reserve it in the system - this should help ensure we have exclusive access (not guaranteed)
        ret = gpio_request(chip->dbg_gpio_StateMachine, FUSB_DT_GPIO_DEBUG_SM_TOGGLE);
        if (ret < 0)
        {
            dev_err(&chip->client->dev, "%s - Error: Could not request GPIO for Debug GPIO! Error code: %d\n", __func__, ret);
            return ret;
        }

        ret = gpio_direction_output(chip->dbg_gpio_StateMachine, chip->dbg_gpio_StateMachine_value);
        if (ret != 0)
        {
            dev_err(&chip->client->dev, "%s - Error: Could not set GPIO direction to output for Debug GPIO! Error code: %d\n", __func__, ret);
            return ret;
        }
        else
        {
            FSC_PRINT("FUSB  %s - Debug GPIO initialized as pin '%d' and is set to '%d'\n", __func__, chip->dbg_gpio_StateMachine, chip->dbg_gpio_StateMachine_value ? 1 : 0);

        }

        // Export to sysfs
        gpio_export(chip->dbg_gpio_StateMachine, true); // Allow direction to change to provide max debug flexibility
        gpio_export_link(&chip->client->dev, FUSB_DT_GPIO_DEBUG_SM_TOGGLE, chip->dbg_gpio_StateMachine);
    }
#endif  // FSC_DEBUG

    return 0;   // Success!
}

void fusb_GPIO_Set_VBus5v(FSC_BOOL set)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

	return;

    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
    }

    // GPIO must be valid by this point
    if (gpio_cansleep(chip->gpio_VBus5V))
    {
        /*
         * If your system routes GPIO calls through a queue of some kind, then
         * it may need to be able to sleep. If so, this call must be used.
         */
        gpio_set_value_cansleep(chip->gpio_VBus5V, set ? 1 : 0);
    }
    else
    {
        gpio_set_value(chip->gpio_VBus5V, set ? 1 : 0);
    }
    chip->gpio_VBus5V_value = set;

    pr_debug("FUSB  %s - VBus 5V set to: %d\n", __func__, chip->gpio_VBus5V_value ? 1 : 0);
}

void fusb_GPIO_Set_VBusOther(FSC_BOOL set)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

	return;

    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
    }

    // Only try to set if feature is enabled, otherwise just fake it
    if (gpio_is_valid(chip->gpio_VBusOther))
    {
        /*
        * If your system routes GPIO calls through a queue of some kind, then
        * it may need to be able to sleep. If so, this call must be used.
        */
        if (gpio_cansleep(chip->gpio_VBusOther))
        {
            gpio_set_value_cansleep(chip->gpio_VBusOther, set ? 1 : 0);
        }
        else
        {
            gpio_set_value(chip->gpio_VBusOther, set ? 1 : 0);
        }
    }
    chip->gpio_VBusOther_value = set;
}

FSC_BOOL fusb_GPIO_Get_VBus5v(void)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return false;
    }

    if (!gpio_is_valid(chip->gpio_VBus5V))
    {
        pr_debug("FUSB  %s - Error: VBus 5V pin invalid! Pin value: %d\n", __func__, chip->gpio_VBus5V);
    }

    return chip->gpio_VBus5V_value;
}

FSC_BOOL fusb_GPIO_Get_VBusOther(void)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return false;
    }

    return chip->gpio_VBusOther_value;
}

FSC_BOOL fusb_GPIO_Get_IntN(void)
{
    FSC_S32 ret = 0;
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return false;
    }
    else
    {
        /*
        * If your system routes GPIO calls through a queue of some kind, then
        * it may need to be able to sleep. If so, this call must be used.
        */
        if (gpio_cansleep(chip->gpio_IntN))
        {
            ret = !gpio_get_value_cansleep(chip->gpio_IntN);
        }
        else
        {
            ret = !gpio_get_value(chip->gpio_IntN); // Int_N is active low
        }
        return (ret != 0);
    }
}

#ifdef FSC_DEBUG
void dbg_fusb_GPIO_Set_SM_Toggle(FSC_BOOL set)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
    }

    if (gpio_is_valid(chip->dbg_gpio_StateMachine))
    {
        /*
        * If your system routes GPIO calls through a queue of some kind, then
        * it may need to be able to sleep. If so, this call must be used.
        */
        if (gpio_cansleep(chip->dbg_gpio_StateMachine))
        {
            gpio_set_value_cansleep(chip->dbg_gpio_StateMachine, set ? 1 : 0);
        }
        else
        {
            gpio_set_value(chip->dbg_gpio_StateMachine, set ? 1 : 0);
        }
        chip->dbg_gpio_StateMachine_value = set;
    }
}

FSC_BOOL dbg_fusb_GPIO_Get_SM_Toggle(void)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return false;
    }
    return chip->dbg_gpio_StateMachine_value;
}
#endif  // FSC_DEBUG

void fusb_GPIO_Cleanup(void)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }

#ifdef FSC_INTERRUPT_TRIGGERED
    if (gpio_is_valid(chip->gpio_IntN) && chip->gpio_IntN_irq != -1)    // -1 indicates that we don't have an IRQ to free
    {
        devm_free_irq(&chip->client->dev, chip->gpio_IntN_irq, chip);
    }

    wake_lock_destroy(&chip->fusb302_wakelock);
#endif // FSC_INTERRUPT_TRIGGERED

    if (gpio_is_valid(chip->gpio_IntN) >= 0)
    {
#ifdef FSC_DEBUG
        gpio_unexport(chip->gpio_IntN);
#endif // FSC_DEBUG

        gpio_free(chip->gpio_IntN);
    }

    if (gpio_is_valid(chip->gpio_VBus5V) >= 0)
    {
#ifdef FSC_DEBUG
        gpio_unexport(chip->gpio_VBus5V);
#endif // FSC_DEBUG

        gpio_free(chip->gpio_VBus5V);
    }

    if (gpio_is_valid(chip->gpio_VBusOther) >= 0)
    {
        gpio_free(chip->gpio_VBusOther);
    }

#ifdef FSC_DEBUG
    if (gpio_is_valid(chip->dbg_gpio_StateMachine) >= 0)
    {
        gpio_unexport(chip->dbg_gpio_StateMachine);
        gpio_free(chip->dbg_gpio_StateMachine);
    }
#endif  // FSC_DEBUG
}

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/********************************************         I2C Interface         ******************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
FSC_BOOL fusb_I2C_WriteData(FSC_U8 address, FSC_U8 length, FSC_U8* data)
{
    FSC_S32 i = 0;
    FSC_S32 ret = 0;
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (chip == NULL || chip->client == NULL || data == NULL)               // Sanity check
    {
        pr_err("%s - Error: %s is NULL!\n", __func__, (chip == NULL ? "Internal chip structure"
            : (chip->client == NULL ? "I2C Client"
            : "Write data buffer")));
        return false;
    }

    mutex_lock(&chip->lock);
    ls_i2c_mutex_lock();

    // Retry on failure up to the retry limit
    for (i = 0; i <= chip->numRetriesI2C; i++)
    {
        ret = i2c_smbus_write_i2c_block_data(chip->client,                      // Perform the actual I2C write on our client
                                             address,                           // Register address to write to
                                             length,                            // Number of bytes to write
                                             data);                             // Ptr to unsigned char data

        if (ret < 0)                                                            // Errors report as negative
        {
            if (ret == -ERANGE) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ERANGE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EINVAL) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EINVAL.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EAGAIN) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EAGAIN.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EALREADY) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EALREADY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EBADE) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EBADE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EBADMSG) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EBADMSG.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EBUSY) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EBUSY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECANCELED) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ECANCELED.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECOMM) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ECOMM.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECONNABORTED) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ECONNABORTED.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECONNREFUSED) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ECONNREFUSED.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECONNRESET) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ECONNRESET.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EDEADLK) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EDEADLK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EDEADLOCK) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EDEADLOCK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EDESTADDRREQ) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EDESTADDRREQ.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EFAULT) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EFAULT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EHOSTDOWN) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EHOSTDOWN.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EHOSTUNREACH) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EHOSTUNREACH.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EILSEQ) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EILSEQ.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EINPROGRESS) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EINPROGRESS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EINTR) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EINTR.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EIO) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EIO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELIBACC) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ELIBACC.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELIBBAD) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ELIBBAD.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELIBMAX) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ELIBMAX.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELOOP) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ELOOP.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EMSGSIZE) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EMSGSIZE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EMULTIHOP) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EMULTIHOP.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOBUFS) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOBUFS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENODATA) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENODATA.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENODEV) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENODEV.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOLCK) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOLCK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOMEM) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOMEM.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOMSG) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOMSG.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOPROTOOPT) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOPROTOOPT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOSPC) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOSPC.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOSYS) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOSYS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOTBLK) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOTBLK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOTTY) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOTTY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOTUNIQ) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENOTUNIQ.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENXIO) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ENXIO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EOVERFLOW) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EOVERFLOW.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPERM) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EPERM.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPFNOSUPPORT) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EPFNOSUPPORT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPIPE) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EPIPE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPROTO) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EPROTO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPROTONOSUPPORT) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EPROTONOSUPPORT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ERANGE) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ERANGE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EREMCHG) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EREMCHG.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EREMOTE) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EREMOTE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EREMOTEIO) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EREMOTEIO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ERESTART) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ERESTART.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ESRCH) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ESRCH.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ETIME) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ETIME.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ETIMEDOUT) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ETIMEDOUT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ETXTBSY) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -ETXTBSY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EUCLEAN) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EUCLEAN.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EUNATCH) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EUNATCH.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EUSERS) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EUSERS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EWOULDBLOCK) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EWOULDBLOCK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EXDEV) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EXDEV.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EXFULL) { dev_err(&chip->client->dev, "%s - I2C Error block writing byte data. Address: '0x%02x', Return: -EXFULL.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EOPNOTSUPP) { dev_err(&chip->client->dev, "%s - I2C Error writing byte data. Address: '0x%02x', Return: -EOPNOTSUPP.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPROBE_DEFER) { dev_err(&chip->client->dev, "%s - I2C Error writing byte data. Address: '0x%02x', Return: -EPROBE_DEFER.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOENT) { dev_err(&chip->client->dev, "%s - I2C Error writing byte data. Address: '0x%02x', Return: -ENOENT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else { dev_err(&chip->client->dev, "%s - Unexpected I2C error block writing byte data. Address: '0x%02x', Return: '%d'.  Attempt #%d / %d...\n", __func__, address, ret, i, chip->numRetriesI2C); }
        }
        else                                                                    // Successful i2c writes should always return 0
        {
            break;
        }
    }

    ls_i2c_mutex_unlock();

    mutex_unlock(&chip->lock);
    return (ret >= 0);
}

FSC_BOOL fusb_I2C_ReadData(FSC_U8 address, FSC_U8* data)
{
    FSC_S32 i = 0;
    FSC_S32 ret = 0;
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (chip == NULL || chip->client == NULL || data == NULL)
    {
        pr_err("%s - Error: %s is NULL!\n", __func__, (chip == NULL ? "Internal chip structure"
            : (chip->client == NULL ? "I2C Client"
            : "read data buffer")));
        return false;
    }
    mutex_lock(&chip->lock);
    ls_i2c_mutex_lock();

    // Retry on failure up to the retry limit
    for (i = 0; i <= chip->numRetriesI2C; i++)
    {
        ret = i2c_smbus_read_byte_data(chip->client, (u8)address);         // Read a byte of data from address
        if (ret < 0)                                                            // Errors report as negative
        {
            if (ret == -ERANGE) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ERANGE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EINVAL) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EINVAL.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EAGAIN) { dev_err(&chip->client->dev, "%s - "
                                                                   " reading byte data. Address: '0x%02x', Return: -EAGAIN.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EALREADY) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EALREADY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EBADE) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EBADE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EBADMSG) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EBADMSG.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EBUSY) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EBUSY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECANCELED) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ECANCELED.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECOMM) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ECOMM.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECONNABORTED) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ECONNABORTED.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECONNREFUSED) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ECONNREFUSED.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECONNRESET) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ECONNRESET.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EDEADLK) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EDEADLK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EDEADLOCK) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EDEADLOCK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EDESTADDRREQ) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EDESTADDRREQ.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EFAULT) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EFAULT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EHOSTDOWN) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EHOSTDOWN.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EHOSTUNREACH) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EHOSTUNREACH.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EILSEQ) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EILSEQ.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EINPROGRESS) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EINPROGRESS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EINTR) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EINTR.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EIO) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EIO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELIBACC) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ELIBACC.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELIBBAD) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ELIBBAD.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELIBMAX) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ELIBMAX.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELOOP) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ELOOP.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EMSGSIZE) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EMSGSIZE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EMULTIHOP) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EMULTIHOP.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOBUFS) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOBUFS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENODATA) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENODATA.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENODEV) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENODEV.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOLCK) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOLCK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOMEM) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOMEM.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOMSG) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOMSG.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOPROTOOPT) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOPROTOOPT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOSPC) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOSPC.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOSYS) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOSYS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOTBLK) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOTBLK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOTTY) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOTTY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOTUNIQ) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOTUNIQ.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENXIO) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENXIO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EOVERFLOW) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EOVERFLOW.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPERM) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EPERM.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPFNOSUPPORT) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EPFNOSUPPORT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPIPE) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EPIPE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPROTO) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EPROTO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPROTONOSUPPORT) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EPROTONOSUPPORT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ERANGE) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ERANGE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EREMCHG) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EREMCHG.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EREMOTE) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EREMOTE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EREMOTEIO) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EREMOTEIO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ERESTART) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ERESTART.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ESRCH) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ESRCH.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ETIME) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ETIME.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ETIMEDOUT) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ETIMEDOUT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ETXTBSY) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ETXTBSY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EUCLEAN) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EUCLEAN.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EUNATCH) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EUNATCH.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EUSERS) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EUSERS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EWOULDBLOCK) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EWOULDBLOCK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EXDEV) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EXDEV.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EXFULL) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EXFULL.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EOPNOTSUPP) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EOPNOTSUPP.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPROBE_DEFER) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EPROBE_DEFER.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOENT) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOENT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else { dev_err(&chip->client->dev, "%s - Unexpected I2C error reading byte data. Address: '0x%02x', Return: '%d'.  Attempt #%d / %d...\n", __func__, address, ret, i, chip->numRetriesI2C); }
        }
        else                                                                    // Successful i2c writes should always return 0
        {
            *data = (FSC_U8)ret;
            break;
        }
    }

    ls_i2c_mutex_unlock();
    mutex_unlock(&chip->lock);
    return (ret >= 0);
}

FSC_BOOL fusb_I2C_ReadBlockData(FSC_U8 address, FSC_U8 length, FSC_U8* data)
{
    FSC_S32 i = 0;
    FSC_S32 ret = 0;
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (chip == NULL || chip->client == NULL || data == NULL)
    {
        pr_err("%s - Error: %s is NULL!\n", __func__, (chip == NULL ? "Internal chip structure"
            : (chip->client == NULL ? "I2C Client"
            : "block read data buffer")));
        return false;
    }

    mutex_lock(&chip->lock);
    ls_i2c_mutex_lock();

    // Retry on failure up to the retry limit
    for (i = 0; i <= chip->numRetriesI2C; i++)
    {
        ret = i2c_smbus_read_i2c_block_data(chip->client, (u8)address, (u8)length, (u8*)data);          // Read a byte of data from address
        if (ret < 0)                                                                                    // Errors report as negative
        {
            if (ret == -ERANGE) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ERANGE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EINVAL) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EINVAL.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EAGAIN) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EAGAIN.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EALREADY) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EALREADY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EBADE) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EBADE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EBADMSG) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EBADMSG.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EBUSY) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EBUSY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECANCELED) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ECANCELED.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECOMM) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ECOMM.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECONNABORTED) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ECONNABORTED.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECONNREFUSED) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ECONNREFUSED.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ECONNRESET) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ECONNRESET.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EDEADLK) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EDEADLK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EDEADLOCK) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EDEADLOCK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EDESTADDRREQ) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EDESTADDRREQ.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EFAULT) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EFAULT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EHOSTDOWN) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EHOSTDOWN.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EHOSTUNREACH) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EHOSTUNREACH.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EILSEQ) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EILSEQ.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EINPROGRESS) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EINPROGRESS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EINTR) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EINTR.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EIO) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EIO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELIBACC) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ELIBACC.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELIBBAD) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ELIBBAD.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELIBMAX) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ELIBMAX.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ELOOP) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ELOOP.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EMSGSIZE) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EMSGSIZE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EMULTIHOP) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EMULTIHOP.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOBUFS) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOBUFS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENODATA) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENODATA.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENODEV) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENODEV.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOLCK) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOLCK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOMEM) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOMEM.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOMSG) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOMSG.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOPROTOOPT) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOPROTOOPT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOSPC) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOSPC.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOSYS) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOSYS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOTBLK) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOTBLK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOTTY) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOTTY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOTUNIQ) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENOTUNIQ.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENXIO) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ENXIO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EOVERFLOW) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EOVERFLOW.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPERM) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EPERM.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPFNOSUPPORT) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EPFNOSUPPORT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPIPE) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EPIPE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPROTO) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EPROTO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPROTONOSUPPORT) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EPROTONOSUPPORT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ERANGE) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ERANGE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EREMCHG) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EREMCHG.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EREMOTE) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EREMOTE.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EREMOTEIO) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EREMOTEIO.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ERESTART) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ERESTART.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ESRCH) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ESRCH.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ETIME) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ETIME.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ETIMEDOUT) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ETIMEDOUT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ETXTBSY) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -ETXTBSY.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EUCLEAN) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EUCLEAN.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EUNATCH) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EUNATCH.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EUSERS) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EUSERS.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EWOULDBLOCK) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EWOULDBLOCK.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EXDEV) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EXDEV.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EXFULL) { dev_err(&chip->client->dev, "%s - I2C Error block reading byte data. Address: '0x%02x', Return: -EXFULL.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EOPNOTSUPP) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EOPNOTSUPP.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -EPROBE_DEFER) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -EPROBE_DEFER.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else if (ret == -ENOENT) { dev_err(&chip->client->dev, "%s - I2C Error reading byte data. Address: '0x%02x', Return: -ENOENT.  Attempt #%d / %d...\n", __func__, address, i, chip->numRetriesI2C); }
            else { dev_err(&chip->client->dev, "%s - Unexpected I2C error block reading byte data. Address: '0x%02x', Return: '%d'.  Attempt #%d / %d...\n", __func__, address, ret, i, chip->numRetriesI2C); }
        }
        else if (ret != length) // We didn't read everything we wanted
        {
            dev_err(&chip->client->dev, "%s - Error: Block read request of %u bytes truncated to %u bytes.\n", __func__, length, I2C_SMBUS_BLOCK_MAX);
        }
        else
        {
            break;  // Success, don't retry
        }
    }

    ls_i2c_mutex_unlock();
    mutex_unlock(&chip->lock);
    return (ret == length);
}


/*********************************************************************************************************************/
/*********************************************************************************************************************/
/********************************************        Timer Interface        ******************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
static const unsigned long g_fusb_timer_tick_period_ns = 1000000;    // Tick SM every 1ms -> 1000000ns
static FSC_BOOL need_hardreset = FALSE;

int _send_hard_reset(void *empty)
{
    FSC_U8 data = 0x40;
    int ret = 0;
    struct sched_param param = { .sched_priority = MAX_RT_PRIO - 1 };
    sched_setscheduler(current, SCHED_FIFO, &param);
    do
    {
        set_current_state(TASK_INTERRUPTIBLE);
        /* Issue Hard Reset to 302 */
        if (need_hardreset) {
            ret = fusb_I2C_WriteData(0x09, 1, &data);
            need_hardreset = FALSE;
        }
	FSC_PRINT("FUSB  %s - Hard Reset Thread Result: %d\n", __func__, ret);
    } while(!kthread_should_stop());
    return 0;
}


/*******************************************************************************
* Function:        _fusb_TimerHandler
* Input:           timer: hrtimer struct to be handled
* Return:          HRTIMER_RESTART to restart the timer, or HRTIMER_NORESTART otherwise
* Description:     Ticks state machine timer counters and rearms itself
********************************************************************************/
enum hrtimer_restart _fusb_TimerHandler(struct hrtimer* timer)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    //int dummy;

    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    if (!timer)
    {
        pr_err("FUSB  %s - Error: High-resolution timer is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    need_hardreset = TRUE;

    FSC_PRINT("FUSB  %s - Hard Reset Thread Started\n", __func__);
    //kthread_run(_send_hard_reset, (void*)&dummy, "hard_reset_thread");
    //wake_up_processs(chip->hard_reset_thread);
    queue_kthread_work(&chip->hardreset_worker, &chip->hardreset_work);
    return HRTIMER_NORESTART;
}

enum hrtimer_restart _fusb_wake_timeout(struct hrtimer* timer)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    if (!timer)
    {
        pr_err("FUSB  %s - Error: High-resolution timer is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    FSC_PRINT("FUSB  %s - Wake Unlock\n", __func__);
    wake_unlock(&chip->fusb302_wakelock);

    return HRTIMER_NORESTART;
}

enum hrtimer_restart _fusb_force_state_timeout(struct hrtimer* timer)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    if (!timer)
    {
        pr_err("FUSB  %s - Error: High-resolution timer is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    FSC_PRINT("FUSB %s - Force State Timeout\n", __func__);
    queue_kthread_work(&chip->set_drp_worker, &chip->set_drp_work);

    return HRTIMER_NORESTART;
}

enum hrtimer_restart _fusb_vbus_timeout(struct hrtimer* timer)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }
    if (!timer)
    {
        pr_err("FUSB %s - Error: High resolution timer is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    FSC_PRINT("FUSB %s - Vbus Timeout\n", __func__);
    queue_kthread_work(&chip->vbus_timeout_worker, &chip->vbus_timeout_work);
    return HRTIMER_NORESTART;
}

enum hrtimer_restart _fusb_ccdebounce_timeout(struct hrtimer* timer)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }
    if (!timer)
    {
        pr_err("FUSB %s - Error: High resolution timer is NULL!\n", __func__);
        return HRTIMER_NORESTART;
	}

    FSC_PRINT("FUSB %s - Timer Timeout\n", __func__);
    core_set_expire(CC_DEBOUNCE);
    queue_kthread_work(&chip->main_worker, &chip->main_work);

    return HRTIMER_NORESTART;
}

enum hrtimer_restart _fusb_pddebounce_timeout(struct hrtimer* timer)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
        return HRTIMER_NORESTART;
	}
    if (!timer)
    {
        pr_err("FUSB %s - Error: High resolution timer is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    FSC_PRINT("FUSB %s - Timer Timeout\n", __func__);

    core_set_expire(PD_DEBOUNCE);
    queue_kthread_work(&chip->main_worker, &chip->main_work);

    return HRTIMER_NORESTART;
}

enum hrtimer_restart _fusb_statetimer_timeout(struct hrtimer* timer)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }
    if (!timer)
    {
        pr_err("FUSB %s - Error: High resolution timer is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    FSC_PRINT("FUSB %s - Timer Timeout\n", __func__);

    core_set_expire(STATE_TIMER);
    queue_kthread_work(&chip->main_worker, &chip->main_work);

    return HRTIMER_NORESTART;
}

enum hrtimer_restart _fusb_policystatetimer_timeout(struct hrtimer* timer)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }
    if (!timer)
    {
        pr_err("FUSB %s - Error: High resolution timer is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    FSC_PRINT("FUSB %s - Timer Timeout\n", __func__);

    core_set_expire(POLICY_STATE_TIMER);
    queue_kthread_work(&chip->main_worker, &chip->main_work);

    return HRTIMER_NORESTART;
}

enum hrtimer_restart _fusb_noresponsetimer_timeout(struct hrtimer* timer)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }
    if (!timer)
    {
        pr_err("FUSB %s - Error: High resolution timer is NULL!\n", __func__);
        return HRTIMER_NORESTART;
    }

    FSC_PRINT("FUSB %s - Timer Timeout\n", __func__);

    core_set_expire(NO_RESPONSE_TIMER);
    queue_kthread_work(&chip->main_worker, &chip->main_work);

    return HRTIMER_NORESTART;
}

enum hrtimer_restart _fusb_loopresettimer_timeout(struct hrtimer* timer)
{
        struct fusb30x_chip* chip = fusb30x_GetChip();
        if (!chip)
        {
                pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
                return HRTIMER_NORESTART;
        }
        if (!timer)
        {
                pr_err("FUSB %s - Error: High resolution timer is NULL!\n", __func__);
                return HRTIMER_NORESTART;
        }
        pr_info("FUSB %s - Timer Timeout\n", __func__);
        core_clear_loop_counter();
        return HRTIMER_NORESTART;
}
void fusb_InitializeTimer(void)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }

    chip->hard_reset_thread = kthread_create(_send_hard_reset, NULL, "hard_reset_thread");

    hrtimer_init(&chip->timer_state_machine, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_state_machine.function = _fusb_TimerHandler;

    hrtimer_init(&chip->timer_force_timeout, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_force_timeout.function = _fusb_force_state_timeout;

    hrtimer_init(&chip->timer_wake_unlock, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_wake_unlock.function = _fusb_wake_timeout;

    hrtimer_init(&chip->timer_ccdebounce, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_ccdebounce.function = _fusb_ccdebounce_timeout;

    hrtimer_init(&chip->timer_pddebounce, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_pddebounce.function = _fusb_pddebounce_timeout;

    hrtimer_init(&chip->timer_statetimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_statetimer.function = _fusb_statetimer_timeout;

    hrtimer_init(&chip->timer_policystatetimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_policystatetimer.function = _fusb_policystatetimer_timeout;

    hrtimer_init(&chip->timer_noresponsetimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_noresponsetimer.function = _fusb_noresponsetimer_timeout;

    hrtimer_init(&chip->timer_vbus_timeout, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_vbus_timeout.function = _fusb_vbus_timeout;

    hrtimer_init(&chip->timer_loopresettimer, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
    chip->timer_loopresettimer.function = _fusb_loopresettimer_timeout;

    pr_debug("FUSB  %s - Timer initialized!\n", __func__);
}

void fusb_StartTimers(struct hrtimer *timer, FSC_U32 timeout)
{
    ktime_t ktime;
    int ret;
    struct fusb30x_chip *chip;

    chip = fusb30x_GetChip();
	if (!chip)
	{
		pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
        return;
	}
	FSC_PRINT("FUSB %s - Platform Starting Timer\n", __func__);
	ktime = ktime_set(0, timeout * g_fusb_timer_tick_period_ns);
	ret = hrtimer_start(timer, ktime, HRTIMER_MODE_REL);
	FSC_PRINT("FUSB %s - Platform Starting Timer Ret:%d\n", __func__, ret);
}

void fusb_StopTimers(struct hrtimer *timer)
{
    FSC_U32 ret = 0;
    struct fusb30x_chip *chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }
    mutex_lock(&chip->lock);
    if (hrtimer_active(timer) != 0)
    {
        ret = hrtimer_cancel(timer);
        pr_debug("%s - Active state machine hrtimer canceld:%d\n", __func__, ret);
    }

    if (hrtimer_is_queued(timer) != 0)
    {
        ret = hrtimer_cancel(timer);
        pr_debug("%s - Queued state machine hrtimer canceled:%d\n", __func__, ret);
    }

    mutex_unlock(&chip->lock);
    pr_debug("FUSB %s - Timer stopped!\n", __func__);
}


// Get the max value that we can delay in 10us increments at compile time
static const FSC_U32 MAX_DELAY_10US = (UINT_MAX / 10);
void fusb_Delay10us(FSC_U32 delay10us)
{
    FSC_U32 us = 0;
    if (delay10us > MAX_DELAY_10US)
    {
        pr_err("%s - Error: Delay of '%u' is too long! Must be less than '%u'.\n", __func__, delay10us, MAX_DELAY_10US);
        return;
    }

    us = delay10us * 10;                                    // Convert to microseconds (us)

    if (us <= 10)                                           // Best practice is to use udelay() for < ~10us times
    {
        udelay(us);                                         // BLOCKING delay for < 10us
    }
    else if (us < 20000)                                    // Best practice is to use usleep_range() for 10us-20ms
    {
        // TODO - optimize this range, probably per-platform
        usleep_range(us, us + (us / 10));                   // Non-blocking sleep for at least the requested time, and up to the requested time + 10%
    }
    else                                                    // Best practice is to use msleep() for > 20ms
    {
        msleep(us / 1000);                                  // Convert to ms. Non-blocking, low-precision sleep
    }
}

FSC_U16 get_system_time(void)
{
    unsigned long ms;

    ms = jiffies * 1000 / HZ;

    return (FSC_U16)ms;
}

#ifdef FSC_DEBUG
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/********************************************        SysFS Interface        ******************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
/*******************************************************************************
* Function:        fusb_timestamp_bytes_to_time
* Input:           outSec: Seconds part of output is stored here
*                  outMS10ths: 10ths of MS part of output is stored here
*                  inBuf: Ptr to first of 4 timestamp bytes, where the timestamp is in this format:
*                    [HI-10thsMS LO-10thsMS HI-Sec LO-Sec]
* Return:          None
* Description:     Parses the 4 bytes in inBuf into a 2-part timestamp: Seconds and 10ths of MS
********************************************************************************/
void fusb_timestamp_bytes_to_time(FSC_U32* outSec, FSC_U32* outMS10ths, FSC_U8* inBuf)
{
    if (outSec && outMS10ths && inBuf)
    {
        *outMS10ths = inBuf[0];
        *outMS10ths = *outMS10ths << 8;
        *outMS10ths |= inBuf[1];

        *outSec = inBuf[2];
        *outSec = *outSec << 8;
        *outSec |= inBuf[3];
    }
}

/*******************************************************************************
* Function:        fusb_get_pd_message_type
* Input:           header: PD message header. Bits 4..0 are the pd message type, bits 14..12 are num data objs
*                  out: Buffer to which the message type will be written, should be at least 32 bytes long
* Return:          int - Number of chars written to out, negative on error
* Description:     Parses both PD message header bytes for the message type as a null-terminated string.
********************************************************************************/
FSC_S32 fusb_get_pd_message_type(FSC_U16 header, FSC_U8* out)
{
    FSC_S32 numChars = -1;   // Number of chars written, return value
    if ((!out) || !(out + 31))    // Check for our 32 byte buffer
    {
        pr_err("%s FUSB - Error: Invalid input buffer! header: 0x%x\n", __func__, header);
        return -1;
    }

    // Bits 14..12 give num of data obj. This is a data message if there are data objects, otherwise it's a control message
    // See the PD spec, Table 6-1 "Message Header", for more details.
    if ((header & 0x7000) > 0)
    {
        switch (header & 0x0F)
        {
            case DMTSourceCapabilities:    // Source Capabilities
            {
                numChars = sprintf(out, "Source Capabilities");
                break;
            }
            case DMTRequest:    // Request
            {
                numChars = sprintf(out, "Request");
                break;
            }
            case DMTBIST:    // BIST
            {
                numChars = sprintf(out, "BIST");
                break;
            }
            case DMTSinkCapabilities:    // Sink Capabilities
            {
                numChars = sprintf(out, "Sink Capabilities");
                break;
            }
            case 0b00101:    // Battery Status
            {
                numChars = sprintf(out, "Battery Status");
                break;
            }
            case 0b00110:    // Source Alert
            {
                numChars = sprintf(out, "Source Alert");
                break;
            }
            case DMTVenderDefined:    // Vendor Defined
            {
                numChars = sprintf(out, "Vendor Defined");
                break;
            }
            default:            // Reserved/unused/unknown
            {
                numChars = sprintf(out, "Reserved (Data) (0x%x)", header);
                break;
            }
        }
    }
    else
    {
        switch (header & 0x0F)
        {
            case CMTGoodCRC:    // Good CRC
            {
                numChars = sprintf(out, "Good CRC");
                break;
            }
            case CMTGotoMin:    // Go to min
            {
                numChars = sprintf(out, "Go to Min");
                break;
            }
            case CMTAccept:    // Accept
            {
                numChars = sprintf(out, "Accept");
                break;
            }
            case CMTReject:    // Reject
            {
                numChars = sprintf(out, "Reject");
                break;
            }
            case CMTPing:    // Ping
            {
                numChars = sprintf(out, "Ping");
                break;
            }
            case CMTPS_RDY:    // PS_RDY
            {
                numChars = sprintf(out, "PS_RDY");
                break;
            }
            case CMTGetSourceCap:    // Get Source Cap
            {
                numChars = sprintf(out, "Get Source Capabilities");
                break;
            }
            case CMTGetSinkCap:    // Get Sink Cap
            {
                numChars = sprintf(out, "Get Sink Capabilities");
                break;
            }
            case CMTDR_Swap:    // Data Role Swap
            {
                numChars = sprintf(out, "Data Role Swap");
                break;
            }
            case CMTPR_Swap:    // Power Role Swap
            {
                numChars = sprintf(out, "Power Role Swap");
                break;
            }
            case CMTVCONN_Swap:    // VConn Swap
            {
                numChars = sprintf(out, "VConn Swap");
                break;
            }
            case CMTWait:    // Wait
            {
                numChars = sprintf(out, "Wait");
                break;
            }
            case CMTSoftReset:    // Soft Reset
            {
                numChars = sprintf(out, "Soft Reset");
                break;
            }
            case 0b01110:    // Not Supported
            {
                numChars = sprintf(out, "Not Supported");
                break;
            }
            case 0b01111:    // Get Source Cap Extended
            {
                numChars = sprintf(out, "Get Source Cap Ext");
                break;
            }
            case 0b10000:    // Get Source Status
            {
                numChars = sprintf(out, "Get Source Status");
                break;
            }
            case 0b10001:    // FR Swap
            {
                numChars = sprintf(out, "FR Swap");
                break;
            }
            default:            // Reserved/unused/unknown
            {
                numChars = sprintf(out, "Reserved (CMD) (0x%x)", header);
                break;
            }
        }
    }
    return numChars;
}

/*******************************************************************************
* Function:        fusb_Sysfs_Handle_Read
* Input:           output: Buffer to which the output will be written
* Return:          Number of chars written to output
* Description:     Reading this file will output the most recently saved hostcomm output buffer
********************************************************************************/
#define FUSB_MAX_BUF_SIZE 256   // Arbitrary temp buffer for parsing out driver data to sysfs
static ssize_t _fusb_Sysfs_Hostcomm_show(struct device* dev, struct device_attribute* attr, char* buf)
{
    FSC_S32 i = 0;
    FSC_S32 numLogs = 0;
    FSC_S32 numChars = 0;
    FSC_U32 TimeStampSeconds = 0;   // Timestamp value in seconds
    FSC_U32 TimeStampMS10ths = 0;   // Timestamp fraction in 10ths of milliseconds
    FSC_S8 tempBuf[FUSB_MAX_BUF_SIZE] = { 0 };
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (chip == NULL)
    {
        pr_err("%s - Chip structure is null!\n", __func__);
    }
    else if (buf == NULL || chip->HostCommBuf == NULL)
    {
        pr_err("%s - Buffer is null!\n", __func__);
    }
    else if (chip->HostCommBuf[0] == CMD_READ_PD_STATE_LOG)  // Parse out the PD state log
    {
        numLogs = chip->HostCommBuf[3];
        /* First byte echos the command, 4th byte is number of logs (2nd and 3rd bytes reserved as 0) */
        numChars += sprintf(tempBuf, "PD State Log has %u entries:\n", numLogs); // Copy string + null terminator
        strcat(buf, tempBuf);

        /* Relevant data starts at 5th byte in this format: CMD 0 0 #Logs PDState time time time time */
        for (i = 4; (i + 4 < FSC_HOSTCOMM_BUFFER_SIZE) && (numChars < PAGE_SIZE) && (numLogs > 0); i += 5, numLogs--) // Must be able to peek 4 bytes ahead, and don't overflow the output buffer (PAGE_SIZE)
        {
            fusb_timestamp_bytes_to_time(&TimeStampSeconds, &TimeStampMS10ths, &chip->HostCommBuf[i + 1]);

            // sprintf should be safe here because we're controlling the strings being printed, just make sure the strings are less than FUSB_MAX_BUF_SIZE+1
            switch (chip->HostCommBuf[i])
            {
                case peDisabled:		    // Policy engine is disabled
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDisabled\t\tPolicy engine is disabled\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peErrorRecovery:		// Error recovery state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeErrorRecovery\t\tError recovery state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceHardReset:		// Received a hard reset
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceHardReset\t\tReceived a hard reset\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceSendHardReset:		// Source send a hard reset
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendHardReset\t\tSource send a hard reset\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceSoftReset:		// Received a soft reset
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSoftReset\t\tReceived a soft reset\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceSendSoftReset:		// Send a soft reset
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendSoftReset\t\tSend a soft reset\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceStartup:		// Initial state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceStartup\t\tInitial state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceSendCaps:		// Send the source capabilities
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendCaps\t\tSend the source capabilities\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceDiscovery:		// Waiting to detect a USB PD sink
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceDiscovery\t\tWaiting to detect a USB PD sink\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceDisabled:		// Disabled state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceDisabled\t\tDisabled state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceTransitionDefault:		// Transition to default 5V state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceTransitionDefault\t\tTransition to default 5V state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceNegotiateCap:		// Negotiate capability and PD contract
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceNegotiateCap\t\tNegotiate capability and PD contract\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceCapabilityResponse:		// Respond to a request message with a reject/wait
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceCapabilityResponse\t\tRespond to a request message with a reject/wait\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceTransitionSupply:		// Transition the power supply to the new setting (accept request)
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceTransitionSupply\t\tTransition the power supply to the new setting (accept request)\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceReady:		// Contract is in place and output voltage is stable
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceReady\t\tContract is in place and output voltage is stable\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceGiveSourceCaps:		// State to resend source capabilities
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGiveSourceCaps\t\tState to resend source capabilities\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceGetSinkCaps:		// State to request the sink capabilities
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGetSinkCaps\t\tState to request the sink capabilities\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceSendPing:		// State to send a ping message
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendPing\t\tState to send a ping message\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceGotoMin:		// State to send the gotoMin and ready the power supply
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGotoMin\t\tState to send the gotoMin and ready the power supply\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceGiveSinkCaps:		// State to send the sink capabilities if dual-role
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGiveSinkCaps\t\tState to send the sink capabilities if dual-role\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceGetSourceCaps:		// State to request the source caps from the UFP
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGetSourceCaps\t\tState to request the source caps from the UFP\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceSendDRSwap:		// State to send a DR_Swap message
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendDRSwap\t\tState to send a DR_Swap message\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceEvaluateDRSwap:		// Evaluate whether we are going to accept or reject the swap
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceEvaluateDRSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkHardReset:		// Received a hard reset
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkHardReset\t\tReceived a hard reset\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkSendHardReset:		// Sink send hard reset
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSendHardReset\t\tSink send hard reset\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkSoftReset:		// Sink soft reset
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSoftReset\t\tSink soft reset\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkSendSoftReset:		// Sink send soft reset
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSendSoftReset\t\tSink send soft reset\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkTransitionDefault:		// Transition to the default state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkTransitionDefault\t\tTransition to the default state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkStartup:		// Initial sink state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkStartup\t\tInitial sink state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkDiscovery:		// Sink discovery state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkDiscovery\t\tSink discovery state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkWaitCaps:		// Sink wait for capabilities state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkWaitCaps\t\tSink wait for capabilities state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkEvaluateCaps:		// Sink state to evaluate the received source capabilities
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkEvaluateCaps\t\tSink state to evaluate the received source capabilities\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkSelectCapability:		// Sink state for selecting a capability
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSelectCapability\t\tSink state for selecting a capability\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkTransitionSink:		// Sink state for transitioning the current power
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkTransitionSink\t\tSink state for transitioning the current power\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkReady:		// Sink ready state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkReady\t\tSink ready state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkGiveSinkCap:		// Sink send capabilities state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkGiveSinkCap\t\tSink send capabilities state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkGetSourceCap:		// Sink get source capabilities state
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkGetSourceCap\t\tSink get source capabilities state\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkGetSinkCap:		// Sink state to get the sink capabilities of the connected source
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkGetSinkCap\t\tSink state to get the sink capabilities of the connected source\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkGiveSourceCap:		// Sink state to send the source capabilities if dual-role
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkGiveSourceCap\t\tSink state to send the source capabilities if dual-role\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkSendDRSwap:		// State to send a DR_Swap message
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSendDRSwap\t\tState to send a DR_Swap message\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkEvaluateDRSwap:		// Evaluate whether we are going to accept or reject the swap
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkEvaluateDRSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceSendVCONNSwap:		// Initiate a VCONN swap sequence
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendVCONNSwap\t\tInitiate a VCONN swap sequence\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkEvaluateVCONNSwap:		// Evaluate whether we are going to accept or reject the swap
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkEvaluateVCONNSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceSendPRSwap:		// Initiate a PR_Swap sequence
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendPRSwap\t\tInitiate a PR_Swap sequence\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceEvaluatePRSwap:		// Evaluate whether we are going to accept or reject the swap
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceEvaluatePRSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkSendPRSwap:		// Initiate a PR_Swap sequence
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSendPRSwap\t\tInitiate a PR_Swap sequence\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSinkEvaluatePRSwap:		// Evaluate whether we are going to accept or reject the swap
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkEvaluatePRSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peGiveVdm:		// Send VDM data
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeGiveVdm\t\tSend VDM data\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmGetIdentity:		// Requesting Identity information from DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmGetIdentity\t\tRequesting Identity information from DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmSendIdentity:		// Sending Discover Identity ACK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmSendIdentity\t\tSending Discover Identity ACK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmGetSvids:		// Requesting SVID info from DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmGetSvids\t\tRequesting SVID info from DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmSendSvids:		// Sending Discover SVIDs ACK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmSendSvids\t\tSending Discover SVIDs ACK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmGetModes:		// Requesting Mode info from DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmGetModes\t\tRequesting Mode info from DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmSendModes:		// Sending Discover Modes ACK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmSendModes\t\tSending Discover Modes ACK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmEvaluateModeEntry:		// Requesting DPM to evaluate request to enter a mode, and enter if OK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmEvaluateModeEntry\t\tRequesting DPM to evaluate request to enter a mode, and enter if OK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmModeEntryNak:		// Sending Enter Mode NAK response
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeEntryNak\t\tSending Enter Mode NAK response\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmModeEntryAck:		// Sending Enter Mode ACK response
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeEntryAck\t\tSending Enter Mode ACK response\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmModeExit:		// Requesting DPM to evalute request to exit mode
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeExit\t\tRequesting DPM to evalute request to exit mode\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmModeExitNak:		// Sending Exit Mode NAK reponse
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeExitNak\t\tSending Exit Mode NAK reponse\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmModeExitAck:		// Sending Exit Mode ACK Response
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeExitAck\t\tSending Exit Mode ACK Response\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peUfpVdmAttentionRequest:		// Sending Attention Command
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmAttentionRequest\t\tSending Attention Command\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpUfpVdmIdentityRequest:		// Sending Identity Request
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpUfpVdmIdentityRequest\t\tSending Identity Request\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpUfpVdmIdentityAcked:		// Inform DPM of Identity
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpUfpVdmIdentityAcked\t\tInform DPM of Identity\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpUfpVdmIdentityNaked:		// Inform DPM of result
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpUfpVdmIdentityNaked\t\tInform DPM of result\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpCblVdmIdentityRequest:		// Sending Identity Request
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpCblVdmIdentityRequest\t\tSending Identity Request\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpCblVdmIdentityAcked:		// Inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpCblVdmIdentityAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpCblVdmIdentityNaked:		// Inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpCblVdmIdentityNaked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmSvidsRequest:		// Sending Discover SVIDs request
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmSvidsRequest\t\tSending Discover SVIDs request\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmSvidsAcked:		// Inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmSvidsAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmSvidsNaked:		// Inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmSvidsNaked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmModesRequest:		// Sending Discover Modes request
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModesRequest\t\tSending Discover Modes request\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmModesAcked:		// Inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModesAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmModesNaked:		// Inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModesNaked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmModeEntryRequest:		// Sending Mode Entry request
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModeEntryRequest\t\tSending Mode Entry request\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmModeEntryAcked:		// Inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModeEntryAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmModeEntryNaked:		// Inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModeEntryNaked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmModeExitRequest:		// Sending Exit Mode request
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModeExitRequest\t\tSending Exit Mode request\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmExitModeAcked:		// Inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmExitModeAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSrcVdmIdentityRequest:		// sending Discover Identity request
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSrcVdmIdentityRequest\t\tsending Discover Identity request\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSrcVdmIdentityAcked:		// inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSrcVdmIdentityAcked\t\tinform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSrcVdmIdentityNaked:		// inform DPM
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSrcVdmIdentityNaked\t\tinform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDfpVdmAttentionRequest:		// Attention Request received
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmAttentionRequest\t\tAttention Request received\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblReady:		// Cable power up state?
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblReady\t\tCable power up state?\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblGetIdentity:		// Discover Identity request received
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetIdentity\t\tDiscover Identity request received\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblGetIdentityNak:		// Respond with NAK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetIdentityNak\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblSendIdentity:		// Respond with Ack
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblSendIdentity\t\tRespond with Ack\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblGetSvids:		// Discover SVIDs request received
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetSvids\t\tDiscover SVIDs request received\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblGetSvidsNak:		// Respond with NAK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetSvidsNak\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblSendSvids:		// Respond with ACK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblSendSvids\t\tRespond with ACK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblGetModes:		// Discover Modes request received
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetModes\t\tDiscover Modes request received\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblGetModesNak:		// Respond with NAK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetModesNak\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblSendModes:		// Respond with ACK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblSendModes\t\tRespond with ACK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblEvaluateModeEntry:		// Enter Mode request received
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblEvaluateModeEntry\t\tEnter Mode request received\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblModeEntryAck:		// Respond with NAK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeEntryAck\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblModeEntryNak:		// Respond with ACK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeEntryNak\t\tRespond with ACK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblModeExit:		// Exit Mode request received
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeExit\t\tExit Mode request received\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblModeExitAck:		// Respond with NAK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeExitAck\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peCblModeExitNak:		// Respond with ACK
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeExitNak\t\tRespond with ACK\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peDpRequestStatus:		// Requesting PP Status
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeDpRequestStatus\t\tRequesting PP Status\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case PE_BIST_Receive_Mode:		// Bist Receive Mode
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tPE_BIST_Receive_Mode\t\tBist Receive Mode\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case PE_BIST_Frame_Received:		// Test Frame received by Protocol layer
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tPE_BIST_Frame_Received\t\tTest Frame received by Protocol layer\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case PE_BIST_Carrier_Mode_2:		// BIST Carrier Mode 2
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tPE_BIST_Carrier_Mode_2\t\tBIST Carrier Mode 2\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case peSourceWaitNewCapabilities:		// Wait for new Source Capabilities from Policy Manager
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceWaitNewCapabilities\t\tWait for new Source Capabilities from Policy Manager\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case dbgGetRxPacket:		        // Debug point for measuring Rx packet handling in ProtocolGetRxPacket()
                {
                    // Special parsing for this state - TimeStampSeconds is really the number of I2C reads performed, and TimeStampMS10ths is the time elapsed (in ms)
                    numChars += sprintf(tempBuf, "%02u|0.%04u\tdbgGetRxPacket\t\t\tNumber of I2C bytes read | Time elapsed\n", TimeStampSeconds, TimeStampMS10ths);
                //    numChars += sprintf(tempBuf, "%u | %u\tdbgGetRxPacket\t\t\tHeader[0] | Header[1]", chip->HostCommBuf[i + 1], chip->HostCommBuf[i + 3]);
                    strcat(buf, tempBuf);
                    break;
                }

                case dbgSendTxPacket:		        // Debug point for measuring Tx packet handling in ProtocolTransmitMessage()
                {
                    // Special parsing for this state - TimeStampSeconds is really the number of I2C reads performed, and TimeStampMS10ths is the time elapsed (in ms)
                    numChars += sprintf(tempBuf, "%02u|0.%04u\tdbgGetTxPacket\t\t\tNumber of I2C bytes sent | Time elapsed\n", TimeStampSeconds, TimeStampMS10ths);
                    //    numChars += sprintf(tempBuf, "%u | %u\tdbgGetRxPacket\t\t\tHeader[0] | Header[1]", chip->HostCommBuf[i + 1], chip->HostCommBuf[i + 3]);
                    strcat(buf, tempBuf);
                    break;
                }

                default:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tUKNOWN STATE: 0x%02x\n", TimeStampSeconds, TimeStampMS10ths, chip->HostCommBuf[i]);
                    strcat(buf, tempBuf);
                    break;
                }
            }
        }
        strcat(buf, "\n");   // Append a newline for pretty++
        numChars++;          // Account for newline
    }
    else if (chip->HostCommBuf[0] == CMD_READ_STATE_LOG)  // Parse out the Type-C state log
    {
        numLogs = chip->HostCommBuf[3];
        /* First byte echos the command, 4th byte is number of logs (2nd and 3rd bytes reserved as 0) */
        numChars += sprintf(tempBuf, "Type-C State Log has %u entries:\n", numLogs); // Copy string + null terminator
        strcat(buf, tempBuf);

        /* Relevant data starts at 5th byte in this format: CMD 0 0 #Logs State time time time time */
        for (i = 4; (i + 4 < FSC_HOSTCOMM_BUFFER_SIZE) && (numChars < PAGE_SIZE) && (numLogs > 0); i += 5, numLogs--) // Must be able to peek 4 bytes ahead, and don't overflow the output buffer (PAGE_SIZE), only print logs we have
        {
            // Parse out the timestamp
            fusb_timestamp_bytes_to_time(&TimeStampSeconds, &TimeStampMS10ths, &chip->HostCommBuf[i + 1]);

            // sprintf should be safe here because we're controlling the strings being printed, just make sure the strings are less than FUSB_MAX_BUF_SIZE+1
            switch (chip->HostCommBuf[i])
            {
                case Disabled:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tDisabled\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case ErrorRecovery:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tErrorRecovery\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case Unattached:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tUnattached\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case AttachWaitSink:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tAttachWaitSink\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case AttachedSink:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tAttachedSink\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case AttachWaitSource:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tAttachWaitSource\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case AttachedSource:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tAttachedSource\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case TrySource:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tTrySource\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case TryWaitSink:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tTryWaitSink\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case TrySink:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tTrySink\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case TryWaitSource:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tTryWaitSource\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case AudioAccessory:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tAudioAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case DebugAccessorySource:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tDebugAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case AttachWaitAccessory:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tAttachWaitAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case PoweredAccessory:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tPoweredAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case UnsupportedAccessory:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tUnsupportedAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case DelayUnattached:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tDelayUnattached\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }

                case UnattachedSource:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tUnattachedSource\n", TimeStampSeconds, TimeStampMS10ths);
                    strcat(buf, tempBuf);
                    break;
                }
                default:
                {
                    numChars += sprintf(tempBuf, "[%u.%04u]\tUKNOWN STATE: 0x%02x\n", TimeStampSeconds, TimeStampMS10ths, chip->HostCommBuf[i]);
                    strcat(buf, tempBuf);
                    break;
                }
            }
        }
        strcat(buf, "\n");   // Append a newline for pretty++
        numChars++;          // Account for newline
    }
    else
    {
        for (i = 0; i < FSC_HOSTCOMM_BUFFER_SIZE; i++)
        {
            numChars += scnprintf(tempBuf, 6 * sizeof(char), "0x%02x ", chip->HostCommBuf[i]); // Copy 1 byte + null term
            strcat(buf, tempBuf);   // Append each number to the output buffer
        }
        strcat(buf, "\n");   // Append a newline for pretty++
        numChars++;          // Account for newline
    }
    return numChars;
}

/*******************************************************************************
* Function:        fusb_Sysfs_Handle_Write
* Input:           input: Buffer passed in from OS (space-separated list of 8-bit hex values)
*                  size: Number of chars in input
*                  output: Buffer to which the output will be written
* Return:          Number of chars written to output
* Description:     Performs hostcomm duties, and stores output buffer in chip structure
********************************************************************************/
static ssize_t _fusb_Sysfs_Hostcomm_store(struct device* dev, struct device_attribute* attr, const char* input, size_t size)
{
    FSC_S32 ret = 0;
    FSC_S32 i = 0;
    FSC_S32 j = 0;
    FSC_S8 tempByte = 0;
    FSC_S32 numBytes = 0;
    FSC_S8 temp[6] = { 0 };   // Temp buffer to parse out individual hex numbers, +1 for null terminator
    FSC_S8 temp_input[FSC_HOSTCOMM_BUFFER_SIZE] = { 0 };
    FSC_S8 output[FSC_HOSTCOMM_BUFFER_SIZE] = { 0 };
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (chip == NULL)
    {
        pr_err("%s - Chip structure is null!\n", __func__);
    }
    else if (input == NULL)
    {
        pr_err("%s - Error: Input buffer is NULL!\n", __func__);
    }
    else
    {
        // Convert the buffer to hex values
        for (i = 0; i < size; i = i + j)
        {
            // Parse out a hex number (at most 5 chars: "0x## ")
            for (j = 0; (j < 5) && (j + i < size); j++)
            {
                // End of the hex number (space-delimited)
                if (input[i + j] == ' ')
                {
                    break;                  // We found a space, stop copying this number and convert it
                }

                temp[j] = input[i + j];     // Copy the non-space byte into the temp buffer
            }

            temp[j++] = 0;                  // Add a null terminator and move past the space

            // We have a hex digit (hopefully), now convert it
            ret = kstrtou8(temp, 16, &tempByte);
            if (ret != 0)
            {
                pr_err("FUSB  %s - Error: Hostcomm input is not a valid hex value! Return: '%d'\n", __func__, ret);
                return 0;  // Quit on error
            }
            else
            {
                temp_input[numBytes++] = tempByte;
                if (numBytes >= FSC_HOSTCOMM_BUFFER_SIZE)
                {
                    break;
                }
            }
        }

        fusb_ProcessMsg(temp_input, output);                                                // Handle the message
        memcpy(chip->HostCommBuf, output, FSC_HOSTCOMM_BUFFER_SIZE);                        // Copy input into temp buffer
    }

    return size;
}

/* Fetch and display the PD state log */
static ssize_t _fusb_Sysfs_PDStateLog_show(struct device* dev, struct device_attribute* attr, char* buf)
{
    FSC_S32 i = 0;
    FSC_S32 numChars = 0;
    FSC_S32 numLogs = 0;
    FSC_U16 PDMessageHeader = 0;                        // PD Message header bytes
    FSC_U32 TimeStampSeconds = 0;                       // Timestamp value in seconds
    FSC_U32 TimeStampMS10ths = 0;                       // Timestamp fraction in 10ths of milliseconds
    FSC_U8 MessageType[32] = { 0 };                     // Temp buffer to parse the PD message type from the PD message header
    FSC_U8 output[FSC_HOSTCOMM_BUFFER_SIZE] = { 0 };
    FSC_U8 tempBuf[FUSB_MAX_BUF_SIZE] = { 0 };
    tempBuf[0] = CMD_READ_PD_STATE_LOG;                 // To request the PD statelog from Hostcomm

    /* Get the PD State Log */
    fusb_ProcessMsg(tempBuf, output);

    numLogs = output[3];
    /* First byte echos the command, 4th byte is number of logs (2nd and 3rd bytes reserved as 0) */
    numChars += sprintf(tempBuf, "PD State Log has %u entries:\n", numLogs); // Copy string + null terminator
    strcat(buf, tempBuf);

    /* Relevant data starts at 5th byte in this format: CMD 0 0 #Logs PDState time time time time */
    for (i = 4; (i + 4 < FSC_HOSTCOMM_BUFFER_SIZE) && (numChars < PAGE_SIZE) && (numLogs > 0); i += 5, numLogs--) // Must be able to peek 4 bytes ahead, and don't overflow the output buffer (PAGE_SIZE)
    {
        // Parse out the timestamp

        // Parse out the timestamp
        if (output[i] != dbgGetRxPacket)
        {
            fusb_timestamp_bytes_to_time(&TimeStampSeconds, &TimeStampMS10ths, &output[i + 1]);
        }

        // sprintf should be safe here because we're controlling the strings being printed, just make sure the strings are less than FUSB_MAX_BUF_SIZE+1
        switch (output[i])
        {
            case peDisabled:		    // Policy engine is disabled
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDisabled\t\tPolicy engine is disabled\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peErrorRecovery:		// Error recovery state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeErrorRecovery\t\tError recovery state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceHardReset:		// Received a hard reset
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceHardReset\t\tReceived a hard reset\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceSendHardReset:		// Source send a hard reset
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendHardReset\t\tSource send a hard reset\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceSoftReset:		// Received a soft reset
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSoftReset\t\tReceived a soft reset\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceSendSoftReset:		// Send a soft reset
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendSoftReset\t\tSend a soft reset\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceStartup:		// Initial state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceStartup\t\tInitial state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceSendCaps:		// Send the source capabilities
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendCaps\t\tSend the source capabilities\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceDiscovery:		// Waiting to detect a USB PD sink
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceDiscovery\t\tWaiting to detect a USB PD sink\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceDisabled:		// Disabled state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceDisabled\t\tDisabled state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceTransitionDefault:		// Transition to default 5V state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceTransitionDefault\t\tTransition to default 5V state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceNegotiateCap:		// Negotiate capability and PD contract
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceNegotiateCap\t\tNegotiate capability and PD contract\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceCapabilityResponse:		// Respond to a request message with a reject/wait
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceCapabilityResponse\t\tRespond to a request message with a reject/wait\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceTransitionSupply:		// Transition the power supply to the new setting (accept request)
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceTransitionSupply\t\tTransition the power supply to the new setting (accept request)\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceReady:		// Contract is in place and output voltage is stable
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceReady\t\tContract is in place and output voltage is stable\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceGiveSourceCaps:		// State to resend source capabilities
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGiveSourceCaps\t\tState to resend source capabilities\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceGetSinkCaps:		// State to request the sink capabilities
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGetSinkCaps\t\tState to request the sink capabilities\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceSendPing:		// State to send a ping message
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendPing\t\tState to send a ping message\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceGotoMin:		// State to send the gotoMin and ready the power supply
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGotoMin\t\tState to send the gotoMin and ready the power supply\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceGiveSinkCaps:		// State to send the sink capabilities if dual-role
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGiveSinkCaps\t\tState to send the sink capabilities if dual-role\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceGetSourceCaps:		// State to request the source caps from the UFP
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceGetSourceCaps\t\tState to request the source caps from the UFP\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceSendDRSwap:		// State to send a DR_Swap message
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendDRSwap\t\tState to send a DR_Swap message\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceEvaluateDRSwap:		// Evaluate whether we are going to accept or reject the swap
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceEvaluateDRSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkHardReset:		// Received a hard reset
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkHardReset\t\tReceived a hard reset\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkSendHardReset:		// Sink send hard reset
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSendHardReset\t\tSink send hard reset\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkSoftReset:		// Sink soft reset
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSoftReset\t\tSink soft reset\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkSendSoftReset:		// Sink send soft reset
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSendSoftReset\t\tSink send soft reset\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkTransitionDefault:		// Transition to the default state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkTransitionDefault\t\tTransition to the default state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkStartup:		// Initial sink state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkStartup\t\tInitial sink state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkDiscovery:		// Sink discovery state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkDiscovery\t\tSink discovery state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkWaitCaps:		// Sink wait for capabilities state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkWaitCaps\t\tSink wait for capabilities state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkEvaluateCaps:		// Sink state to evaluate the received source capabilities
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkEvaluateCaps\t\tSink state to evaluate the received source capabilities\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkSelectCapability:		// Sink state for selecting a capability
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSelectCapability\t\tSink state for selecting a capability\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkTransitionSink:		// Sink state for transitioning the current power
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkTransitionSink\t\tSink state for transitioning the current power\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkReady:		// Sink ready state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkReady\t\tSink ready state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkGiveSinkCap:		// Sink send capabilities state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkGiveSinkCap\t\tSink send capabilities state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkGetSourceCap:		// Sink get source capabilities state
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkGetSourceCap\t\tSink get source capabilities state\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkGetSinkCap:		// Sink state to get the sink capabilities of the connected source
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkGetSinkCap\t\tSink state to get the sink capabilities of the connected source\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkGiveSourceCap:		// Sink state to send the source capabilities if dual-role
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkGiveSourceCap\t\tSink state to send the source capabilities if dual-role\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkSendDRSwap:		// State to send a DR_Swap message
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSendDRSwap\t\tState to send a DR_Swap message\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkEvaluateDRSwap:		// Evaluate whether we are going to accept or reject the swap
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkEvaluateDRSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceSendVCONNSwap:		// Initiate a VCONN swap sequence
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendVCONNSwap\t\tInitiate a VCONN swap sequence\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkEvaluateVCONNSwap:		// Evaluate whether we are going to accept or reject the swap
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkEvaluateVCONNSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceSendPRSwap:		// Initiate a PR_Swap sequence
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceSendPRSwap\t\tInitiate a PR_Swap sequence\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceEvaluatePRSwap:		// Evaluate whether we are going to accept or reject the swap
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceEvaluatePRSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkSendPRSwap:		// Initiate a PR_Swap sequence
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkSendPRSwap\t\tInitiate a PR_Swap sequence\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSinkEvaluatePRSwap:		// Evaluate whether we are going to accept or reject the swap
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSinkEvaluatePRSwap\t\tEvaluate whether we are going to accept or reject the swap\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peGiveVdm:		// Send VDM data
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeGiveVdm\t\tSend VDM data\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmGetIdentity:		// Requesting Identity information from DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmGetIdentity\t\tRequesting Identity information from DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmSendIdentity:		// Sending Discover Identity ACK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmSendIdentity\t\tSending Discover Identity ACK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmGetSvids:		// Requesting SVID info from DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmGetSvids\t\tRequesting SVID info from DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmSendSvids:		// Sending Discover SVIDs ACK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmSendSvids\t\tSending Discover SVIDs ACK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmGetModes:		// Requesting Mode info from DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmGetModes\t\tRequesting Mode info from DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmSendModes:		// Sending Discover Modes ACK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmSendModes\t\tSending Discover Modes ACK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmEvaluateModeEntry:		// Requesting DPM to evaluate request to enter a mode, and enter if OK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmEvaluateModeEntry\t\tRequesting DPM to evaluate request to enter a mode, and enter if OK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmModeEntryNak:		// Sending Enter Mode NAK response
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeEntryNak\t\tSending Enter Mode NAK response\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmModeEntryAck:		// Sending Enter Mode ACK response
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeEntryAck\t\tSending Enter Mode ACK response\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmModeExit:		// Requesting DPM to evalute request to exit mode
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeExit\t\tRequesting DPM to evalute request to exit mode\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmModeExitNak:		// Sending Exit Mode NAK reponse
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeExitNak\t\tSending Exit Mode NAK reponse\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmModeExitAck:		// Sending Exit Mode ACK Response
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmModeExitAck\t\tSending Exit Mode ACK Response\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peUfpVdmAttentionRequest:		// Sending Attention Command
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeUfpVdmAttentionRequest\t\tSending Attention Command\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpUfpVdmIdentityRequest:		// Sending Identity Request
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpUfpVdmIdentityRequest\t\tSending Identity Request\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpUfpVdmIdentityAcked:		// Inform DPM of Identity
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpUfpVdmIdentityAcked\t\tInform DPM of Identity\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpUfpVdmIdentityNaked:		// Inform DPM of result
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpUfpVdmIdentityNaked\t\tInform DPM of result\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpCblVdmIdentityRequest:		// Sending Identity Request
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpCblVdmIdentityRequest\t\tSending Identity Request\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpCblVdmIdentityAcked:		// Inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpCblVdmIdentityAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpCblVdmIdentityNaked:		// Inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpCblVdmIdentityNaked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmSvidsRequest:		// Sending Discover SVIDs request
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmSvidsRequest\t\tSending Discover SVIDs request\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmSvidsAcked:		// Inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmSvidsAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmSvidsNaked:		// Inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmSvidsNaked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmModesRequest:		// Sending Discover Modes request
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModesRequest\t\tSending Discover Modes request\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmModesAcked:		// Inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModesAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmModesNaked:		// Inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModesNaked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmModeEntryRequest:		// Sending Mode Entry request
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModeEntryRequest\t\tSending Mode Entry request\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmModeEntryAcked:		// Inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModeEntryAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmModeEntryNaked:		// Inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModeEntryNaked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmModeExitRequest:		// Sending Exit Mode request
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmModeExitRequest\t\tSending Exit Mode request\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmExitModeAcked:		// Inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmExitModeAcked\t\tInform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSrcVdmIdentityRequest:		// sending Discover Identity request
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSrcVdmIdentityRequest\t\tsending Discover Identity request\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSrcVdmIdentityAcked:		// inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSrcVdmIdentityAcked\t\tinform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSrcVdmIdentityNaked:		// inform DPM
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSrcVdmIdentityNaked\t\tinform DPM\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDfpVdmAttentionRequest:		// Attention Request received
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDfpVdmAttentionRequest\t\tAttention Request received\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblReady:		// Cable power up state?
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblReady\t\tCable power up state?\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblGetIdentity:		// Discover Identity request received
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetIdentity\t\tDiscover Identity request received\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblGetIdentityNak:		// Respond with NAK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetIdentityNak\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblSendIdentity:		// Respond with Ack
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblSendIdentity\t\tRespond with Ack\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblGetSvids:		// Discover SVIDs request received
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetSvids\t\tDiscover SVIDs request received\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblGetSvidsNak:		// Respond with NAK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetSvidsNak\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblSendSvids:		// Respond with ACK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblSendSvids\t\tRespond with ACK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblGetModes:		// Discover Modes request received
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetModes\t\tDiscover Modes request received\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblGetModesNak:		// Respond with NAK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblGetModesNak\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblSendModes:		// Respond with ACK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblSendModes\t\tRespond with ACK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblEvaluateModeEntry:		// Enter Mode request received
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblEvaluateModeEntry\t\tEnter Mode request received\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblModeEntryAck:		// Respond with NAK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeEntryAck\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblModeEntryNak:		// Respond with ACK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeEntryNak\t\tRespond with ACK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblModeExit:		// Exit Mode request received
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeExit\t\tExit Mode request received\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblModeExitAck:		// Respond with NAK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeExitAck\t\tRespond with NAK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peCblModeExitNak:		// Respond with ACK
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeCblModeExitNak\t\tRespond with ACK\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peDpRequestStatus:		// Requesting PP Status
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeDpRequestStatus\t\tRequesting PP Status\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case PE_BIST_Receive_Mode:		// Bist Receive Mode
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tPE_BIST_Receive_Mode\t\tBist Receive Mode\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case PE_BIST_Frame_Received:		// Test Frame received by Protocol layer
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tPE_BIST_Frame_Received\t\tTest Frame received by Protocol layer\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case PE_BIST_Carrier_Mode_2:		// BIST Carrier Mode 2
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tPE_BIST_Carrier_Mode_2\t\tBIST Carrier Mode 2\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case peSourceWaitNewCapabilities:		// Wait for new Source Capabilities from Policy Manager
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tpeSourceWaitNewCapabilities\t\tWait for new Source Capabilities from Policy Manager\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case dbgSendTxPacket:                // Treat the same as Rx packet, just change "Rx" to "Tx"
            case dbgGetRxPacket:		        // Debug point for measuring Rx packet handling time in ProtocolGetRxPacket()
            {
                // Special parsing for this state - TimeStampSeconds is really the number of I2C reads performed, and TimeStampMS10ths is the time elapsed (in ms)
           //   numChars += sprintf(tempBuf, "%02u|0.%04u\tdbgGetRxPacket\t\t\tNumber of I2C bytes read | Time elapsed\n", TimeStampSeconds, TimeStampMS10ths);

                // Recombine the 2 header bytes into a u16
                PDMessageHeader = output[i + 4];                // Get MSByte
                PDMessageHeader = PDMessageHeader << 8;         // Shift into MS position
                PDMessageHeader |= output[i + 2];               // Get LSByte

                // Parse out the message type to make the log easier to read
                if (fusb_get_pd_message_type(PDMessageHeader, MessageType) > -1)
                {
                    numChars += sprintf(tempBuf, "0x%x\t\t%s\t\tMessage Type: %s\n", PDMessageHeader, (output[i] == dbgGetRxPacket) ? "dbgGetRxPacket" : "dbgSendTxPacket", MessageType);
                }
                else
                {
                    numChars += sprintf(tempBuf, "0x%x\t\t%s\t\tMessage Type: UNKNOWN\n", PDMessageHeader, (output[i] == dbgGetRxPacket) ? "dbgGetRxPacket" : "dbgSendTxPacket");
                }
                strcat(buf, tempBuf);
                break;
            }

            default:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tUKNOWN STATE: 0x%02x\n", TimeStampSeconds, TimeStampMS10ths, output[i]);
                strcat(buf, tempBuf);
                break;
            }
        }
    }
    strcat(buf, "\n");   // Append a newline for pretty++
    return ++numChars;   // Account for newline and return number of bytes to be shown
}

/* Fetch and display the Type-C state log */
static ssize_t _fusb_Sysfs_TypeCStateLog_show(struct device* dev, struct device_attribute* attr, char* buf)
{
    FSC_S32 i = 0;
    FSC_S32 numChars = 0;
    FSC_S32 numLogs = 0;
    FSC_U32 TimeStampSeconds = 0;                       // Timestamp value in seconds
    FSC_U32 TimeStampMS10ths = 0;                       // Timestamp fraction in 10ths of milliseconds
    FSC_S8 output[FSC_HOSTCOMM_BUFFER_SIZE] = { 0 };
    FSC_S8 tempBuf[FUSB_MAX_BUF_SIZE] = { 0 };
    tempBuf[0] = CMD_READ_STATE_LOG;                    // To request the Type-C statelog from Hostcomm

    /* Get the PD State Log */
    fusb_ProcessMsg(tempBuf, output);

    numLogs = output[3];
    /* First byte echos the command, 4th byte is number of logs (2nd and 3rd bytes reserved as 0) */
    numChars += sprintf(tempBuf, "Type-C State Log has %u entries:\n", numLogs); // Copy string + null terminator
    strcat(buf, tempBuf);

    /* Relevant data starts at 5th byte in this format: CMD 0 0 #Logs State time time time time */
    for (i = 4; (i + 4 < FSC_HOSTCOMM_BUFFER_SIZE) && (numChars < PAGE_SIZE) && (numLogs > 0); i += 5, numLogs--) // Must be able to peek 4 bytes ahead, and don't overflow the output buffer (PAGE_SIZE), only print logs we have
    {
        // Parse out the timestamp
        fusb_timestamp_bytes_to_time(&TimeStampSeconds, &TimeStampMS10ths, &output[i + 1]);

        // sprintf should be safe here because we're controlling the strings being printed, just make sure the strings are less than FUSB_MAX_BUF_SIZE+1
        switch (output[i])
        {
            case Disabled:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tDisabled\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case ErrorRecovery:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tErrorRecovery\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case Unattached:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tUnattached\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case AttachWaitSink:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tAttachWaitSink\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case AttachedSink:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tAttachedSink\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case AttachWaitSource:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tAttachWaitSource\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case AttachedSource:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tAttachedSource\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case TrySource:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tTrySource\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case TryWaitSink:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tTryWaitSink\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case TrySink:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tTrySink\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case TryWaitSource:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tTryWaitSource\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case AudioAccessory:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tAudioAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case DebugAccessorySource:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tDebugAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case AttachWaitAccessory:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tAttachWaitAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case PoweredAccessory:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tPoweredAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case UnsupportedAccessory:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tUnsupportedAccessory\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case DelayUnattached:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tDelayUnattached\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }

            case UnattachedSource:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tUnattachedSource\n", TimeStampSeconds, TimeStampMS10ths);
                strcat(buf, tempBuf);
                break;
            }
            default:
            {
                numChars += sprintf(tempBuf, "[%u.%04u]\tUKNOWN STATE: 0x%02x\n", TimeStampSeconds, TimeStampMS10ths, output[i]);
                strcat(buf, tempBuf);
                break;
            }
        }
    }
    strcat(buf, "\n");   // Append a newline for pretty++
    return ++numChars;   // Account for newline and return number of bytes to be shown
}

/* Reinitialize the FUSB302 */
static ssize_t _fusb_Sysfs_Reinitialize_fusb302(struct device* dev, struct device_attribute* attr, char* buf)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (chip == NULL)
    {
        return sprintf(buf, "FUSB302 Error: Internal chip structure pointer is NULL!\n");
    }

    /* Make sure that we are doing this in a thread-safe manner */
#ifdef FSC_INTERRUPT_TRIGGERED
    disable_irq(chip->gpio_IntN_irq);   // Waits for current IRQ handler to return, then disables it
#else
    fusb_StopThreads();                 // Waits for current work to complete, then cancels scheduled work and flushed the work queue
#endif // FSC_INTERRUPT_TRIGGERED

    core_initialize();
    pr_debug ("FUSB  %s - Core is initialized!\n", __func__);
    core_enable_typec(TRUE);
    pr_debug ("FUSB  %s - Type-C State Machine is enabled!\n", __func__);

#ifdef FSC_INTERRUPT_TRIGGERED
    enable_irq(chip->gpio_IntN_irq);
#else
    // Schedule to kick off the main working thread
    schedule_work(&chip->worker);
#endif // FSC_INTERRUPT_TRIGGERED

    return sprintf(buf, "FUSB302 Reinitialized!\n");
}

static ssize_t _fusb_force_sink(struct device* dev, struct device_attribute* attr, char* buf)
{
	//fusb_force_sink();
    return 0;   // Account for newline and return number of bytes to be shown
}

static ssize_t _fusb_force_source(struct device* dev, struct device_attribute* attr, char* buf)
{
	//fusb_force_source();
    return 0;   // Account for newline and return number of bytes to be shown
}

// Define our device attributes to export them to sysfs
static DEVICE_ATTR(fusb30x_hostcomm, S_IRWXU | S_IRWXG | S_IROTH, _fusb_Sysfs_Hostcomm_show, _fusb_Sysfs_Hostcomm_store);
static DEVICE_ATTR(pd_state_log, S_IRUSR | S_IRGRP | S_IROTH, _fusb_Sysfs_PDStateLog_show, NULL);
static DEVICE_ATTR(typec_state_log, S_IRUSR | S_IRGRP | S_IROTH, _fusb_Sysfs_TypeCStateLog_show, NULL);
static DEVICE_ATTR(reinitialize, S_IRUSR | S_IRGRP | S_IROTH, _fusb_Sysfs_Reinitialize_fusb302, NULL);
static DEVICE_ATTR(fusb_force_sink, S_IRUSR | S_IRGRP | S_IROTH, _fusb_force_sink, NULL);
static DEVICE_ATTR(fusb_force_source, S_IRUSR | S_IRGRP | S_IROTH, _fusb_force_source, NULL);

static struct attribute *fusb302_sysfs_attrs[] = {
    &dev_attr_fusb30x_hostcomm.attr,
    &dev_attr_pd_state_log.attr,
    &dev_attr_typec_state_log.attr,
    &dev_attr_reinitialize.attr,
	&dev_attr_fusb_force_sink.attr,
	&dev_attr_fusb_force_source.attr,
    NULL
};

static struct attribute_group fusb302_sysfs_attr_grp = {
    .name = "control",
    .attrs = fusb302_sysfs_attrs,
};

void fusb_Sysfs_Init(void)
{
    FSC_S32 ret = 0;
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (chip == NULL)
    {
        pr_err("%s - Chip structure is null!\n", __func__);
        return;
    }

    /* create attribute group for accessing the FUSB302 */
    ret = sysfs_create_group(&chip->client->dev.kobj, &fusb302_sysfs_attr_grp);
    if (ret)
    {
        pr_err("FUSB %s - Error creating sysfs attributes!\n", __func__);
    }
}

#endif // FSC_DEBUG

/*********************************************************************************************************************/
/*********************************************************************************************************************/
/********************************************        Driver Helpers         ******************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
void fusb_InitializeCore(void)
{
    core_initialize();
    pr_debug("FUSB  %s - Core is initialized!\n", __func__);
    core_enable_typec(TRUE);
    pr_debug("FUSB  %s - Type-C State Machine is enabled!\n", __func__);
}

FSC_BOOL fusb_IsDeviceValid(void)
{
    FSC_U8 val = 0;
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return FALSE;
    }

    // Test to see if we can do a successful I2C read
    if (!fusb_I2C_ReadData((FSC_U8)0x01, &val))
    {
        pr_err("FUSB  %s - Error: Could not communicate with device over I2C!\n", __func__);
        return FALSE;
    }

    return TRUE;
}

void fusb_InitChipData(void)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (chip == NULL)
    {
        pr_err("%s - Chip structure is null!\n", __func__);
        return;
    }

#ifdef FSC_DEBUG
    chip->dbgTimerTicks = 0;
    chip->dbgTimerRollovers = 0;
    chip->dbgSMTicks = 0;
    chip->dbgSMRollovers = 0;
    chip->dbg_gpio_StateMachine = -1;
    chip->dbg_gpio_StateMachine_value = false;
#endif  // FSC_DEBUG

    /* GPIO Defaults */
    chip->gpio_VBus5V = -1;
    chip->gpio_VBus5V_value = false;
    chip->gpio_VBusOther = -1;
    chip->gpio_VBusOther_value = false;
    chip->gpio_IntN = -1;

#ifdef FSC_INTERRUPT_TRIGGERED
    chip->gpio_IntN_irq = -1;
#endif // FSC_INTERRUPT_TRIGGERED

    /* I2C Configuration */
    chip->InitDelayMS = INIT_DELAY_MS;                                              // Time to wait before device init
    chip->numRetriesI2C = RETRIES_I2C;                                              // Number of times to retry I2C reads and writes
    chip->use_i2c_blocks = false;                                                   // Assume failure
}


/*********************************************************************************************************************/
/*********************************************************************************************************************/
/******************************************      IRQ/Threading Helpers       *****************************************/
/*********************************************************************************************************************/
/*********************************************************************************************************************/
#ifdef FSC_INTERRUPT_TRIGGERED

static void fusb302_hardreset_work_handler(struct kthread_work *work)
{
	//hard reset;;
	FSC_U8 data = 0x40;
	fusb_I2C_WriteData(0x09, 1, &data);
	FSC_PRINT("FUSB %s - fusb302_hardreset_work_handler\n", __func__);
}

static void fusb302_vbus_timeout_work_handler(struct kthread_work *work)
{
    FSC_PRINT("FUSB - %s\n", __func__);
    platform_set_vbus_lvl_enable(VBUS_LVL_ALL, FALSE, FALSE);
    platform_set_vbus_discharge(TRUE);
}

static void fusb302_set_drp_work_handler(struct kthread_work *work)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }

    FSC_PRINT("FUSB - %s\n", __func__);
    fusb_StopTimers(&chip->timer_state_machine);
    fusb_StopTimers(&chip->timer_vbus_timeout);
    core_set_try_snk();
}


static void fusb302_main_work_handler(struct kthread_work *work)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();

    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }

    fusb_StopTimers(&chip->timer_wake_unlock);
    mutex_lock(&chip->thread_lock);
    wake_lock(&chip->fusb302_wakelock);


    FSC_PRINT("FUSB %s - Entering State Machine via Timer Interrupt\n", __func__);
    do
    {
        core_state_machine();             // Run the state machine
    } while(platform_get_device_irq_state());

    fusb_StartTimers(&chip->timer_wake_unlock, 3000); /* 3 second */
    //wake_unlock(&chip->fusb302_wakelock);
    FSC_PRINT("FUSB %s - Exiting State Machine via Timer Interrupt\n", __func__);
    mutex_unlock(&chip->thread_lock);

    return;
}

FSC_S32 fusb_EnableInterrupts(void)
{
    FSC_S32 ret = 0;
    struct sched_param param = { .sched_priority = MAX_RT_PRIO - 1 };

    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return -ENOMEM;
    }

    wake_lock_init(&chip->fusb302_wakelock, WAKE_LOCK_SUSPEND, "fusb302wakelock");

    /* Set up IRQ for INT_N GPIO */
    ret = gpio_to_irq(chip->gpio_IntN); // Returns negative errno on error
    if (ret < 0)
    {
        dev_err(&chip->client->dev, "%s - Error: Unable to request IRQ for INT_N GPIO! Error code: %d\n", __func__, ret);
        chip->gpio_IntN_irq = -1;   // Set to indicate error
        fusb_GPIO_Cleanup();
        return ret;
    }
    chip->gpio_IntN_irq = ret;
    pr_debug("%s - Success: Requested INT_N IRQ: '%d'\n", __func__, chip->gpio_IntN_irq);

    /* Request threaded IRQ because we will likely sleep while handling the interrupt, trigger is active-low, don't handle concurrent interrupts */
    ret = devm_request_threaded_irq(&chip->client->dev, chip->gpio_IntN_irq, NULL, _fusb_isr_intn, IRQF_ONESHOT | IRQF_TRIGGER_FALLING, FUSB_DT_INTERRUPT_INTN, chip);  // devm_* allocation/free handled by system
    if (ret)
    {
        dev_err(&chip->client->dev, "%s - Error: Unable to request threaded IRQ for INT_N GPIO! Error code: %d\n", __func__, ret);
        fusb_GPIO_Cleanup();
        return ret;
    }

    enable_irq_wake(chip->gpio_IntN_irq);

    //B.Yang
    init_kthread_worker(&chip->hardreset_worker);
    chip->hardreset_worker_task = kthread_run(kthread_worker_fn,
            &chip->hardreset_worker, "fusb302 hard reset");
    sched_setscheduler(chip->hardreset_worker_task, SCHED_FIFO, &param);
    init_kthread_work(&chip->hardreset_work, fusb302_hardreset_work_handler);

    init_kthread_worker(&chip->vbus_timeout_worker);
    chip->vbus_timeout_worker_task = kthread_run(kthread_worker_fn,
	    &chip->vbus_timeout_worker, "fusb302 vbus timeout");
    sched_setscheduler(chip->vbus_timeout_worker_task, SCHED_FIFO, &param);
    init_kthread_work(&chip->vbus_timeout_work, fusb302_vbus_timeout_work_handler);

    init_kthread_worker(&chip->main_worker);
    chip->main_worker_task = kthread_run(kthread_worker_fn,
        &chip->main_worker, "fusb302 main worker");
    sched_setscheduler(chip->main_worker_task, SCHED_FIFO, &param);
    init_kthread_work(&chip->main_work, fusb302_main_work_handler);

    init_kthread_worker(&chip->set_drp_worker);
    chip->set_drp_worker_task = kthread_run(kthread_worker_fn,
        &chip->set_drp_worker, "fusb302 set drp worker");
    sched_setscheduler(chip->set_drp_worker_task, SCHED_FIFO, &param);
    init_kthread_work(&chip->set_drp_work, fusb302_set_drp_work_handler);

    return 0;
}

/*******************************************************************************
* Function:        _fusb_isr_intn
* Input:           irq - IRQ that was triggered
*                  dev_id - Ptr to driver data structure
* Return:          irqreturn_t - IRQ_HANDLED on success, IRQ_NONE on failure
* Description:     Activates the core
********************************************************************************/
static irqreturn_t _fusb_isr_intn(FSC_S32 irq, void *dev_id)
{
    struct fusb30x_chip* chip = dev_id;
    struct sched_param param = { .sched_priority = MAX_RT_PRIO - 1 };

    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return IRQ_NONE;
    }

    sched_setscheduler(current, SCHED_FIFO, &param);

    FSC_PRINT("FUSB _fusb_isr_intn, current)(%p)\n",current);
    fusb_StopTimers(&chip->timer_wake_unlock);
    mutex_lock(&chip->thread_lock);
    wake_lock(&chip->fusb302_wakelock);
    FSC_PRINT("FUSB %s - Entering ISR\n", __func__);

    do
    {
        core_state_machine();             // Run the state machine
    } while(platform_get_device_irq_state());

    FSC_PRINT("FUSB  %s - Scheduling Wake Unlock\n", __func__);
    fusb_StartTimers(&chip->timer_wake_unlock, 3000); /* 3 second */
    //wake_unlock(&chip->fusb302_wakelock);
    mutex_unlock(&chip->thread_lock);

    FSC_PRINT("FUSB %s - Exiting ISR\n", __func__);
    return IRQ_HANDLED;
}

#else

/*******************************************************************************
* Function:        _fusb_InitWorker
* Input:           delayed_work - passed in from OS
* Return:          none
* Description:     Callback for the init worker, kicks off the main worker
********************************************************************************/
void _fusb_InitWorker(struct work_struct* delayed_work)
{
    struct fusb30x_chip* chip = container_of(delayed_work, struct fusb30x_chip, init_worker.work);
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }

    // Schedule to kick off the main working thread
    schedule_work(&chip->worker);
}

/*******************************************************************************
* Function:        _fusb_MainWorker
* Input:           delayed_work - passed in from OS
* Return:          none
* Description:     Activates the core
********************************************************************************/
void _fusb_MainWorker(struct work_struct* work)
{
    struct fusb30x_chip* chip = container_of(work, struct fusb30x_chip, worker);
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }

#ifdef FSC_DEBUG
    dbg_fusb_GPIO_Set_SM_Toggle(!chip->dbg_gpio_StateMachine_value);    // Optionally toggle debug GPIO when SM is called to measure thread tick rate

    if (chip->dbgSMTicks++ >= U8_MAX)                                   // Tick our state machine tick counter
    {
        chip->dbgSMRollovers++;                                         // Record a moderate amount of rollovers
    }
#endif  // FSC_DEBUG

    core_state_machine();                                               // Run the state machine
    schedule_work(&chip->worker);                                       // Reschedule ourselves to run again
}

void fusb_InitializeWorkers(void)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    pr_debug("FUSB  %s - Initializing threads!\n", __func__);
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }

    // Initialize our delayed_work and work structs
    INIT_DELAYED_WORK(&chip->init_worker, _fusb_InitWorker);
    INIT_WORK(&chip->worker, _fusb_MainWorker);
}

void fusb_StopThreads(void)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }
    // Cancel the initial delayed work
    cancel_delayed_work_sync(&chip->init_worker);
    flush_delayed_work(&chip->init_worker);

    // Cancel the main worker
    flush_work(&chip->worker);
    cancel_work_sync(&chip->worker);
}

void fusb_ScheduleWork(void)
{
    struct fusb30x_chip* chip = fusb30x_GetChip();
    if (!chip)
    {
        pr_err("FUSB  %s - Error: Chip structure is NULL!\n", __func__);
        return;
    }
    schedule_delayed_work(&chip->init_worker, msecs_to_jiffies(chip->InitDelayMS));
}



#endif // FSC_INTERRUPT_TRIGGERED, else
