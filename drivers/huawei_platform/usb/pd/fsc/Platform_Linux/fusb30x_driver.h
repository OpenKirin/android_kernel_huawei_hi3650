/*
 * File:   fusb30x_driver.h
 * Author: Tim Bremm <tim.bremm@fairchildsemi.com>
 * Company: Fairchild Semiconductor
 *
 * Created on September 2, 2015, 9:02 AM
 */

#ifndef FUSB30X_DRIVER_H
#define	FUSB30X_DRIVER_H

#ifdef	__cplusplus
extern "C" {
#endif

#define FUSB_VIN_3V3 3300000
#define FSC_PMIC_LDO_3 2
#ifndef BIT
#define BIT(x)    (1 << (x))
#endif

#define FSC_CC_STATUS_MASK (BIT(0) | BIT(1))
#define FSC_CC_STATUS_40H 0x40
#define FSC_CC_STATUS_FOR_DOUBLE_56K 0x01
#define FSC_CC_SELECT_REG_02H 0x02
#define FSC_CC_SELECT_MASK  (BIT(2) | BIT(3))
#define FSC_CC_SELECT_SHIFT  2


/*******************************************************************************
 * Platform-specific configuration data
 ******************************************************************************/
#define FUSB30X_I2C_DRIVER_NAME                 "fusb302"                                                       // Length must be less than I2C_NAME_SIZE (currently 20, see include/linux/mod_devicetable.h)
#define FUSB30X_I2C_DEVICETREE_NAME             "fairchild,fusb302"                                             // Must match device tree .compatible string exactly
#define FUSB30X_I2C_SMBUS_BLOCK_REQUIRED_FUNC   (I2C_FUNC_SMBUS_I2C_BLOCK)                                      // First try for block reads/writes
#define FUSB30X_I2C_SMBUS_REQUIRED_FUNC         (I2C_FUNC_SMBUS_WRITE_I2C_BLOCK | \
                                                I2C_FUNC_SMBUS_READ_BYTE_DATA)                                  // If no block reads/writes, try single reads/block writes

/*******************************************************************************
* Driver structs
******************************************************************************/
#ifdef CONFIG_OF                                                                // Defined by the build system when configuring "open firmware" (OF) aka device-tree
static const struct of_device_id fusb30x_dt_match[] = {                         // Used by kernel to match device-tree entry to driver
    { .compatible = FUSB30X_I2C_DEVICETREE_NAME },                              // String must match device-tree node exactly
    {},
};
MODULE_DEVICE_TABLE(of, fusb30x_dt_match);
#endif	/* CONFIG_OF */

/* This identifies our I2C driver in the kernel's driver module table */
static const struct i2c_device_id fusb30x_i2c_device_id[] = {
    { FUSB30X_I2C_DRIVER_NAME, 0 },
    {}
};
MODULE_DEVICE_TABLE(i2c, fusb30x_i2c_device_id);                                // Used to generate map files used by depmod for module dependencies

/*******************************************************************************
 * Driver module functions
 ******************************************************************************/
static int __init fusb30x_init(void);                                                                   // Called when driver is inserted into the kernel
static void __exit fusb30x_exit(void);                                                                  // Called when driver is removed from the kernel
static int fusb30x_probe(struct i2c_client* client,                                                     // Called when the associated device is added
                         const struct i2c_device_id* id);
static int fusb30x_remove(struct i2c_client* client);                                                   // Called when the associated device is removed

/* Defines our driver's name, device-tree match, and required driver callbacks */
static struct i2c_driver fusb30x_driver = {
    .driver = {
        .name = FUSB30X_I2C_DRIVER_NAME,                                        // Must match our id_table name
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(fusb30x_dt_match),                       // Device-tree match structure to pair the DT device with our driver
    },
    .probe = fusb30x_probe,                                                     // Called on device add, inits/starts driver
    .remove = fusb30x_remove,                                                   // Called on device remove, cleans up driver
    .id_table = fusb30x_i2c_device_id,                                          // I2C id structure to associate with our driver
};

#ifdef	__cplusplus
}
#endif

#endif	/* FUSB30X_DRIVER_H */
