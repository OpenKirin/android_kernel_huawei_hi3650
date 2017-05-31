README.TXT

Fairchild Semiconductor FUSB302 Linux Platform Driver Integration Notes
_______________________________________________________________________________
Device Tree
	Currently, the driver requires the use of Device Tree in order to
	function with the I2C bus and the required GPIO pins. Modify the
	following Device Tree snippet to specify resources specific to your
	system and include them in your kernel's Device Tree. The FUSB302
	requires a minimum of 2 GPIO pins, a valid I2C bus, and I2C slave
	address 0x22.

	/*********************************************************************/
	i2c@######## {								// replace ######## with the address of your I2C bus
		fusb30x@22 {							// I2C Slave Address - Always @22
				compatible = "fairchild,fusb302";		// String must match driver's .compatible string exactly
				reg = <0x22>;					// I2C Slave address
				status = "okay";				// The device is enabled, comment out or delete to disable
				//status = "disabled";				// Uncomment to disable the device from being loaded at boot
				//fairchild,vbus5v	= <&msm_gpio 39 0>;	// VBus 5V GPIO pin - <&gpio_bus pin# 0>. Do not change "fairchild,vbus5v"
				//fairchild,vbusOther	= <&msm_gpio 40 0>;	// VBus Other GPIO pin - optional, but if used, name "fairchild,vbusOther" must not change.
				fairchild,int_n		= <&pm8994_gpios 4 0>;	// INT_N GPIO pin - <&gpio_bus pin# 0>. Do not change "fairchild,int_n"
			};
	};
	/*********************************************************************/

_______________________________________________________________________________
Compilation/Makefile
	You must define the preprocessor macro "PLATFORM_LINUX" in order to
	pull in the correct typedefs. You may define the preprocessor macro
	"FSC_INTERRUPT_TRIGGERED" to configure the driver to run in interrupt
	mode. Otherwise, the driver will run in polling mode.

	The following example snippet is from a Makefile expecting the
	following directory structure:

	path/to/MakefileDir/
		|---- Makefile
		|---- Platform_Linux/
		|---- core/
			|---- vdm/
				|---- DisplayPort/

	Makefile
	/*********************************************************************/
	# Required flag to configure the core to operate with the Linux kernel
	ccflags-$(CONFIG_FUSB_30X) += -DFSC_PLATFORM_LINUX
	# Optional flag to enable interrupt-driven operation
	ccflags-$(CONFIG_FUSB_30X) += -DFSC_INTERRUPT_TRIGGERED
	# Optional flag to enable debug/hostcomm interface and functionality
	ccflags-$(CONFIG_FUSB_30X) += -DFSC_DEBUG

	# The following flags are used to configure which features are compiled in,
	# and the allowed combinations are:
	#	FSC_HAVE_SRC - Source only
	#	FSC_HAVE_SNK - Sink only
	#	FSC_HAVE_SRC, FSC_HAVE_SNK - Source or sink configurable
	#	FSC_HAVE_SRC, FSC_HAVE_SNK, FSC_HAVE_DRP - DRP capable source or sink
	#	FSC_HAVE_ACCMODE - Accessory mode. Requires FSC_HAVE_SRC.
	#	FSC_HAVE_VDM - Vendor Defined Message (VDM) support.
	#	FSC_HAVE_DP - Display Port (DP) support. Requires FSC_HAVE_VDM.
	ccflags-$(CONFIG_FUSB_30X) += -DFSC_HAVE_SRC
	ccflags-$(CONFIG_FUSB_30X) += -DFSC_HAVE_SNK
	ccflags-$(CONFIG_FUSB_30X) += -DFSC_HAVE_DRP
	ccflags-$(CONFIG_FUSB_30X) += -DFSC_HAVE_ACCMODE
	ccflags-$(CONFIG_FUSB_30X) += -DFSC_HAVE_VDM
	ccflags-$(CONFIG_FUSB_30X) += -DFSC_HAVE_DP

	obj-$(CONFIG_FUSB_30X)     += fusb30x_whole.o
	fusb30x_whole-objs         := Platform_Linux/fusb30x_driver.o \
			              Platform_Linux/fusb30x_global.o \
			              Platform_Linux/platform.o \
			              Platform_Linux/platform_helpers.o \
			              Platform_Linux/hostcomm.o \
			              core/AlternateModes.o \
			              core/core.o \
			              core/fusb30X.o \
			              core/Log.o \
			              core/PDPolicy.o \
			              core/PDProtocol.o \
			              core/TypeC.o \
			              core/vdm/bitfield_translators.o \
			              core/vdm/vdm.o \
			              core/vdm/vdm_callbacks.o \
			              core/vdm/vdm_config.o \
			              core/vdm/DisplayPort/configure.o \
			              core/vdm/DisplayPort/dp.o \
			              core/vdm/DisplayPort/dp_system_stubs.o
	/*********************************************************************/

_______________________________________________________________________________
SysFs HostComm/Debug interface
	When FSC_HAVE_DEBUG is defined, this driver will attempt to create sysfs files to provide
	user-space access to driver functionality. If it is not defined, then these files will not exist.
	You can find these files in:
		/sys/class/i2c-dev/i2c-<i2c bus number>/device/<i2c bus number>-0022/
		|---- fairchild,dbg_sm (access to debug GPIO)
		|---- fairchild,int_n (access to INT_N GPIO)
		|---- fairchild,vbus5v (access to VBus5V GPIO)
		|---- control/
			|---- fusb30x_hostcomm (Provides access to HostComm interface. Examine Platform_Linux/hostcomm.(h|c) for details.)
			|---- pd_state_log (read this file to fetch and display the driver's PD State Log)
			|---- typec_state_log (read this file to fetch and display the driver's Type-C State Log)
			|---- reinitialize (read this file to reinitialize the FUSB302)

	Usage examples:
		PD State Log:
		$ cat pd_state_log
			PD State Log has <0-12> entries:
			[sec.ms]	State		Detail
			[sec.ms]	State		Detail
			...

		Type-C State Log:
		$ cat typec_state_log
			Type-C State Log has 6 entries:
			[sec.ms]        State
			[sec.ms]        State
			...

		Reinitialize the Device:
		$ cat reinitialize
			FUSB302 Reinitialized!

		Interact with HostComm interface:
		To use fusb30x_hostcomm, first make sure you have write permission:
			$ sudo chmod 666 fusb30x_hostcomm
		Then write a command to it to perform an action, and read it to get the result.
		The expected response for most commands is the command issued as the first byte, and zeros thereafter (unless the command is supposed to return data). If the 2nd byte is 0x01, then the specified command is not supported.

		Send a hard reset:
			$ echo -n "0xAE" > fusb30x_hostcomm
			$ cat fusb30x_hostcomm
				0xae 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00

		I2C read on register 0x01:
			$ echo -n "0xC0 0x01" > fusb30x_hostcomm
			$ cat fusb30x_hostcomm
				0x80 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00 0x00

			This I2C read returned a value of 0x80 from register 0x01 on the FUSB302.

		I2C write to a register (Note - example only, it's typically a bad idea to write to registers by hand):
			Write syntax is: "Write-CMD Register NumBytes Data0 Data1 Data2..."
			$ echo -n "0xC1 0x01 0x03 0x01 0x02 0x03" > fusb30x_hostcomm
			$ $ cat fusb30x_hostcomm
				First byte will be 0x00 on failure, 0x01 on success - all other bytes are 0x00.

		Please see Platform_Linux/hostcomm.h for the command mapping.