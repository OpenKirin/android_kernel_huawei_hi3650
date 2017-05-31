#include <linux/module.h>
#include <linux/init.h>
#include <linux/kernel.h>
#include <huawei_platform/connectivity/huawei_gps.h>

GPS_SET_REF_CLK_FUNC g_pfn_set_gps_ref_clk_enable;

void register_gps_set_ref_clk_func(void *pFunc)
{
	g_pfn_set_gps_ref_clk_enable = (GPS_SET_REF_CLK_FUNC) pFunc;
}
EXPORT_SYMBOL(register_gps_set_ref_clk_func);

int set_gps_ref_clk_enable(bool enable, gps_modem_id_enum modem_id,
			   gps_rat_mode_enum rat_mode)
{
	if (NULL != g_pfn_set_gps_ref_clk_enable) {
		return (*g_pfn_set_gps_ref_clk_enable) (enable, modem_id,
							rat_mode);
	}

	return -1;
}
