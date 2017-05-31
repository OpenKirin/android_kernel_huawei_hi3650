

#include <linux/init.h>
#include <linux/cpuidle.h>
#include <linux/platform_device.h>
#include <asm/cpuidle.h>

#define ZYNQ_MAX_STATES		2

/* Actual code that puts the SoC in different idle states */
static int zynq_enter_idle(struct cpuidle_device *dev,
			   struct cpuidle_driver *drv, int index)
{
	cpu_do_idle();

	return index;
}

static struct cpuidle_driver zynq_idle_driver = {
	.name = "zynq_idle",
	.owner = THIS_MODULE,
	.states = {
		ARM_CPUIDLE_WFI_STATE,
		{
			.enter			= zynq_enter_idle,
			.exit_latency		= 10,
			.target_residency	= 10000,
			.name			= "RAM_SR",
			.desc			= "WFI and RAM Self Refresh",
		},
	},
	.safe_state_index = 0,
	.state_count = ZYNQ_MAX_STATES,
};

/* Initialize CPU idle by registering the idle states */
static int zynq_cpuidle_probe(struct platform_device *pdev)
{
	pr_info("Xilinx Zynq CpuIdle Driver started\n");

	return cpuidle_register(&zynq_idle_driver, NULL);
}

static struct platform_driver zynq_cpuidle_driver = {
	.driver = {
		.name = "cpuidle-zynq",
	},
	.probe = zynq_cpuidle_probe,
};

module_platform_driver(zynq_cpuidle_driver);
