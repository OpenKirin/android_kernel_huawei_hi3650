

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#ifdef _PRE_CONFIG_USE_DTS
#include <linux/of.h>
#include <linux/of_gpio.h>
#endif
/*lint -e322*//*lint -e7*/
#include <linux/clk.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/timer.h>
#include <linux/delay.h>
#include <linux/pinctrl/consumer.h>
/*lint +e322*//*lint +e7*/

#include "board.h"
#include "plat_debug.h"
#include "oal_ext_if.h"
#include "board-hi1102.h"
#include "board-hi1103.h"

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
BOARD_INFO g_board_info = {0};
EXPORT_SYMBOL(g_board_info);

uint32 g_device_subchip_type = 0xFFFFFF;  /*save device board index*/

DEVICE_BOARD_VERSION device_board_version_list[BOARD_VERSION_BOTT] = {
    {.index = BOARD_VERSION_HI1102, .name = BOARD_VERSION_NAME_HI1102},
    {.index = BOARD_VERSION_HI1103, .name = BOARD_VERSION_NAME_HI1103},
};

DOWNLOAD_MODE device_download_mode_list[MODE_DOWNLOAD_BUTT] = {
    {.index = MODE_SDIO, .name = DOWNlOAD_MODE_SDIO},
    {.index = MODE_PCIE, .name = DOWNlOAD_MODE_PCIE},
    {.index = MODE_UART, .name = DOWNlOAD_MODE_UART},
};

/*
*
***************************************************************************
  3
 Function Definition
***
**************************************************************************/
extern irqreturn_t bfg_wake_host_isr(int irq, void *dev_id);

inline BOARD_INFO * get_board_info(void)
{
	return &g_board_info;
}

#ifdef _PRE_CONFIG_USE_DTS
int32 get_board_dts_node(struct device_node ** np, const char * node_prop)
{
	if (NULL ==np || NULL == node_prop)
	{
        PS_PRINT_ERR("func has NULL input param!!!, np=%p, node_prop=%p\n", np, node_prop);
		return BOARD_FAIL;
	}

	*np = of_find_compatible_node(NULL, NULL, node_prop);
	if (NULL == *np)
	{
		PS_PRINT_ERR("HISI IPC:No compatible node found.\n");
		return BOARD_FAIL;
	}

	return BOARD_SUCC;
}

int32 get_board_dts_prop(struct device_node *np, const char * dts_prop, const char ** prop_val)
{
	int32 ret = BOARD_FAIL;

	if (NULL == np || NULL == dts_prop || NULL == prop_val)
	{
        PS_PRINT_ERR("func has NULL input param!!!, np=%p, dts_prop=%p, prop_val=%p\n", np, dts_prop, prop_val);
		return BOARD_FAIL;
	}

	ret = of_property_read_string(np, dts_prop, prop_val);
    if (ret)
    {
        PS_PRINT_ERR("can't get dts_prop value: dts_prop=%s\n", dts_prop);
        return ret;
    }

	PS_PRINT_SUC("have get dts_prop and prop_val: %s=%s\n", dts_prop, *prop_val);

	return BOARD_SUCC;
}

int32 get_board_dts_gpio_prop(struct device_node *np, const char * dts_prop, int32 * prop_val)
{
	int32 ret = BOARD_FAIL;

	if (NULL == np || NULL == dts_prop || NULL == prop_val)
	{
        PS_PRINT_ERR("func has NULL input param!!!, np=%p, dts_prop=%p, prop_val=%p\n", np, dts_prop, prop_val);
		return BOARD_FAIL;
	}

    ret = of_get_named_gpio(np, dts_prop, 0);
    if (ret < 0)
    {
        PS_PRINT_ERR("can't get dts_prop value: dts_prop=%s, ret=%d\n", dts_prop, ret);
        return ret;
    }

    *prop_val = ret;
	PS_PRINT_SUC("have get dts_prop and prop_val: %s=%d\n", dts_prop, *prop_val);

	return BOARD_SUCC;
}

#endif

int32 get_board_gpio(const char * gpio_node, const char * gpio_prop, int32 *physical_gpio)
{
#ifdef _PRE_CONFIG_USE_DTS
	int32 ret= BOARD_FAIL;
	struct device_node * np = NULL;

	ret = get_board_dts_node(&np, gpio_node);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	ret = get_board_dts_gpio_prop(np, gpio_prop, physical_gpio);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	return BOARD_SUCC;
#else
	return BOARD_SUCC;
#endif
}

int32 get_board_custmize(const char * cust_node, const char * cust_prop, const char **cust_prop_val)
{
#ifdef _PRE_CONFIG_USE_DTS
	int32 ret= BOARD_FAIL;
	struct device_node * np = NULL;

	if (NULL == cust_node || NULL == cust_prop || NULL == cust_prop_val)
	{
        PS_PRINT_ERR("func has NULL input param!!!\n");
		return BOARD_FAIL;
	}

	ret = get_board_dts_node(&np, cust_node);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	ret = get_board_dts_prop(np, cust_prop, cust_prop_val);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	PS_PRINT_INFO("get board customize info %s=%s\n", cust_prop, *cust_prop_val);

	return BOARD_SUCC;
#else
	return BOARD_SUCC;
#endif
}

int32 get_board_pmu_clk32k(void)
{
	int32 ret= BOARD_FAIL;
	const char * clk_name = NULL;

	PS_PRINT_DBG("in func\n");
	ret = get_board_custmize(DTS_NODE_HI110X, DTS_PROP_CLK_32K, &clk_name);
	if(BOARD_SUCC != ret)
	{
		return BOARD_FAIL;
	}

	g_board_info.clk_32k_name = clk_name;

	return BOARD_SUCC;
}

int32 set_board_pmu_clk32k(struct platform_device *pdev)
{
	int32 ret= BOARD_FAIL;
	const char * clk_name = NULL;
	struct clk* clk = NULL;
	struct device *dev = NULL;

	PS_PRINT_DBG("in func\n");
	dev = &pdev->dev;
	clk_name = g_board_info.clk_32k_name;
	clk = devm_clk_get(dev, "clk_pmu32kb");
    if (NULL == clk)
	{
        PS_PRINT_ERR("Get 32k clk %s failed!!!\n", clk_name);
        CHR_EXCEPTION(CHR_WIFI_DEV(CHR_WIFI_DEV_EVENT_CHIP, CHR_WIFI_DEV_ERROR_32K_CLK));
        return BOARD_FAIL;
	}
	g_board_info.clk_32k = clk;

	ret = clk_prepare_enable(clk);
    if (unlikely(ret < 0))
    {
		devm_clk_put(dev, clk);
        PS_PRINT_ERR("enable 32K clk failed!!!");
        CHR_EXCEPTION(CHR_WIFI_DEV(CHR_WIFI_DEV_EVENT_CHIP, CHR_WIFI_DEV_ERROR_32K_CLK));
        return BOARD_FAIL;
    }

	return BOARD_SUCC;
}

int32 get_board_uart_port(void)
{
#ifdef _PRE_CONFIG_USE_DTS
    int32 ret= BOARD_FAIL;
    struct device_node * np = NULL;
    const char *uart_port = NULL;

    ret = get_board_dts_node(&np, DTS_NODE_HI110X_BFGX);
    if(BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("DTS read node %s fail!!!\n", DTS_NODE_HI110X);
        return BOARD_FAIL;
    }

    /*ʹ��uart4����Ҫ��dts������DTS_PROP_UART_PCLK�ָ��uart4������sensorhub*/
    if (of_property_read_bool(np, DTS_PROP_UART_PCLK))
    {
        PS_PRINT_INFO("uart pclk normal\n");
        g_board_info.uart_pclk = UART_PCLK_NORMAL;
    }
    else
    {
        PS_PRINT_INFO("uart pclk from sensorhub\n");
        g_board_info.uart_pclk = UART_PCLK_FROM_SENSORHUB;
    }

    ret = get_board_custmize(DTS_NODE_HI110X_BFGX, DTS_PROP_UART_POART, &uart_port);
    if(BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }
    g_board_info.uart_port = uart_port;

    return BOARD_SUCC;
#else
    return BOARD_SUCC;
#endif
}

int32 check_evb_or_fpga(void)
{
#ifdef _PRE_CONFIG_USE_DTS
    int32 ret= BOARD_FAIL;
    struct device_node * np = NULL;

    ret = get_board_dts_node(&np, DTS_NODE_HI110X);
    if(BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("DTS read node %s fail!!!\n", DTS_NODE_HI110X);
        return BOARD_FAIL;
    }

    ret = of_property_read_bool(np, DTS_PROP_VERSION);
    if (ret)
    {
        PS_PRINT_INFO("HI1102 ASIC VERSION\n");
        g_board_info.is_asic = VERSION_ASIC;
    }
    else
    {
        PS_PRINT_INFO("HI1102 FPGA VERSION\n");
        g_board_info.is_asic = VERSION_FPGA;
    }

    return BOARD_SUCC;
#else
    return BOARD_SUCC;
#endif
}

int32 board_get_power_pinctrl(struct platform_device *pdev)
{
    int32  ret = BOARD_FAIL;
    int32  physical_gpio = 0;
    struct device_node * np = NULL;
    struct pinctrl *pinctrl;
    struct pinctrl_state *pinctrl_def;
    struct pinctrl_state *pinctrl_idle;

    /* ����Ƿ���Ҫprepare before board power on */
    /* JTAG SELECT ���ͣ�XLDO MODEѡ��2.8v */
	ret = get_board_dts_node(&np, DTS_NODE_HI110X);
	if(BOARD_SUCC != ret)
	{
        PS_PRINT_ERR("DTS read node %s fail!!!\n", DTS_NODE_HI110X);
        goto err_read_dts_node;
	}

    ret = of_property_read_bool(np, DTS_PROP_POWER_PREPARE);
    if (ret)
    {
        PS_PRINT_INFO("need prepare before board power on\n");
        g_board_info.need_power_prepare = NEED_POWER_PREPARE;
    }
    else
    {
        PS_PRINT_INFO("no need prepare before board power on\n");
        g_board_info.need_power_prepare = NO_NEED_POWER_PREPARE;
    }

    if (NO_NEED_POWER_PREPARE == g_board_info.need_power_prepare)
    {
        return BOARD_SUCC;
    }

    pinctrl = devm_pinctrl_get(&pdev->dev);
    if (IS_ERR_OR_NULL(pinctrl))
    {
        PS_PRINT_ERR("iomux_lookup_block failed, and the value of pinctrl is %p\n", pinctrl);
        CHR_EXCEPTION(CHR_WIFI_DEV(CHR_WIFI_DEV_EVENT_CHIP, CHR_WIFI_DEV_ERROR_IOMUX));
        goto err_pinctrl_get;
    }
    g_board_info.pctrl = pinctrl;

    pinctrl_def = pinctrl_lookup_state(pinctrl, "default");
    if (IS_ERR_OR_NULL(pinctrl_def))
    {
        PS_PRINT_ERR("pinctrl_lookup_state default failed, and the value of pinctrl_def is %p\n", pinctrl_def);
        goto err_lookup_default;
    }
    g_board_info.pins_normal = pinctrl_def;

    pinctrl_idle = pinctrl_lookup_state(pinctrl, "idle");
    if (IS_ERR_OR_NULL(pinctrl_idle))
    {
        PS_PRINT_ERR("pinctrl_lookup_state idel failed, and the value of pinctrl_idle is %p\n", pinctrl_idle);
        goto err_lookup_idle;
    }
    g_board_info.pins_idle = pinctrl_idle;

    ret = pinctrl_select_state(g_board_info.pctrl, g_board_info.pins_normal);
    if (ret < 0)
    {
        PS_PRINT_ERR("pinctrl_select_state default failed.\n");
        goto err_select_state;
    }

    /* LTE_TX_ACTIVT GPIO */
    ret = get_board_gpio(DTS_NODE_HI110X, DTS_PROP_GPIO_XLDO_PINMUX, &physical_gpio);
    if(BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_GPIO_POWEN_ON);
        CHR_EXCEPTION(CHR_WIFI_DEV(CHR_WIFI_DEV_EVENT_CHIP, CHR_WIFI_DEV_ERROR_GPIO));
        goto err_get_xldo_pinmux;
    }

    g_board_info.xldo_pinmux = physical_gpio;

    ret = of_property_read_u32(np, DTS_PROP_GPIO_XLDO_LEVEL, &physical_gpio);
    if(BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_GPIO_XLDO_LEVEL);
        CHR_EXCEPTION(CHR_WIFI_DEV(CHR_WIFI_DEV_EVENT_CHIP, CHR_WIFI_DEV_ERROR_GPIO));
        goto err_read_xldo_level;
    }

    g_board_info.gpio_xldo_level = physical_gpio;

    return BOARD_SUCC;

    err_read_xldo_level:
    err_get_xldo_pinmux:
    err_select_state:
    err_lookup_idle:
    err_lookup_default:
        devm_pinctrl_put(g_board_info.pctrl);
    err_pinctrl_get:
    err_read_dts_node:

    return BOARD_FAIL;
}

int32 board_power_gpio_init(void)
{
    int32 ret = BOARD_FAIL;
    switch (g_device_subchip_type)
    {
        case  BOARD_VERSION_HI1102:
            ret = hi1102_get_board_gpio();
            break;
        case BOARD_VERSION_HI1103:
            ret = hi1103_get_board_gpio();
            break;
        default:
            PS_PRINT_ERR("g_device_subchip_type=%d is illegal\n",g_device_subchip_type);
            break;
    }
    return ret;
}
void free_board_power_gpio(void)
{
    switch (g_device_subchip_type)
    {
        case  BOARD_VERSION_HI1102:
            hi1102_free_board_power_gpio();
            break;
        case BOARD_VERSION_HI1103:
            hi1103_free_board_power_gpio();
            break;
        default:
            PS_PRINT_ERR("g_device_subchip_type=%d is illegal\n",g_device_subchip_type);
            break;
    }
}

void free_board_wakeup_gpio(void)
{
    switch (g_device_subchip_type)
    {
        case BOARD_VERSION_HI1102:
            hi1102_free_board_wakeup_gpio();
            break;
        case BOARD_VERSION_HI1103:
            hi1102_free_board_wakeup_gpio();
            break;
        default:
            PS_PRINT_ERR("g_device_subchip_type=%d is illegal\n",g_device_subchip_type);
            break;
    }
}

int32 board_wakeup_gpio_init(void)
{
    int32 ret = BOARD_FAIL;
    switch (g_device_subchip_type)
    {
        case  BOARD_VERSION_HI1102:
            ret = hi1102_board_wakeup_gpio_init();
            break;
        case BOARD_VERSION_HI1103:
            ret = hi1103_board_wakeup_gpio_init();
            break;
        default:
            PS_PRINT_ERR("g_device_subchip_type=%d is illegal\n",g_device_subchip_type);
            break;
    }
    return ret;
}

int32 board_ir_ctrl_gpio_init(void)
{

    int32 ret = BOARD_FAIL;
    int32 physical_gpio = 0;

    /* ir ctrl gpio request */
    ret = get_board_gpio(DTS_NODE_HI110X, DTS_PROP_GPIO_BFGN_IR_CTRL, &physical_gpio);
    if (BOARD_SUCC != ret)
    {
        PS_PRINT_INFO("dts prop %s not exist\n", DTS_PROP_GPIO_BFGN_IR_CTRL);
        g_board_info.bfgn_ir_ctrl_gpio = -1;
    }
    else
    {
        g_board_info.bfgn_ir_ctrl_gpio = physical_gpio;

        ret = gpio_request_one(physical_gpio, GPIOF_OUT_INIT_LOW, PROC_NAME_GPIO_BFGN_IR_CTRL);
        if (ret)
        {
            PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_BFGN_IR_CTRL);
            return BOARD_FAIL;
        }
    }

    return BOARD_SUCC;
}


int32 board_ir_ctrl_pmic_init(struct platform_device *pdev)
{
    int32 ret = BOARD_FAIL;
    struct device_node * np = NULL;
    int32 irled_voltage = 0;
    if (NULL == pdev){
        PS_PRINT_ERR("board pmu pdev is NULL!\n");
        return ret;
    }

    ret = get_board_dts_node(&np, DTS_NODE_HI110X_BFGX);
    if (BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("DTS read node %s fail!!!\n", DTS_NODE_HI110X_BFGX);
        return ret;
    }

    g_board_info.bfgn_ir_ctrl_ldo = regulator_get(&pdev->dev, DTS_IRLED_LDO_POWER);

    if (IS_ERR(g_board_info.bfgn_ir_ctrl_ldo))
    {
        PS_PRINT_ERR("board_ir_ctrl_pmic_init get ird ldo failed\n");
        return ret;
    }

    ret = of_property_read_u32(np, DTS_IRLED_VOLTAGE, &irled_voltage);
    if (BOARD_SUCC == ret)
    {
        PS_PRINT_INFO("set irled voltage %d mv\n", irled_voltage/1000);
        ret = regulator_set_voltage(g_board_info.bfgn_ir_ctrl_ldo,(int)irled_voltage,(int)irled_voltage);
        if (ret)
        {
            PS_PRINT_ERR("board_ir_ctrl_pmic_init set voltage ldo failed\n");
            return ret;
        }
    }
    else
    {
        PS_PRINT_ERR("get irled voltage failed ,use default\n");
    }

    ret = regulator_set_mode(g_board_info.bfgn_ir_ctrl_ldo,REGULATOR_MODE_NORMAL);
    if (ret)
    {
        PS_PRINT_ERR("board_ir_ctrl_pmic_init set ldo mode failed\n");
        return ret;
    }
    PS_PRINT_INFO("board_ir_ctrl_pmic_init success\n");
    return BOARD_SUCC;
}

int32 board_gpio_init(struct platform_device *pdev)
{
    int32 ret= BOARD_FAIL;
    struct device_node * np = NULL;

    PS_PRINT_INFO("in func board_gpio_init\n");
    if (NULL == pdev)
    {
        PS_PRINT_ERR("func has NULL input param!!!\n");
        return BOARD_FAIL;
    }

    /*power on gpio request*/
    ret = board_power_gpio_init();
    if (BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_GPIO_POWEN_ON);
        goto err_get_power_on_gpio;
    }

    ret = board_wakeup_gpio_init();
    if (BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_GPIO_POWEN_ON);
        goto oal_board_wakup_gpio_fail;
    }

    ret = get_board_dts_node(&np, DTS_NODE_HI110X_BFGX);
    if (BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("DTS read node %s fail!!!\n", DTS_NODE_HI110X_BFGX);
        goto err_get_ir_ctrl_gpio;
    }

    g_board_info.have_ir = of_property_read_bool(np, "have_ir");
    if (!g_board_info.have_ir)
    {
        PS_PRINT_ERR("board has no Ir");
    }
    else
    {
        ret = of_property_read_u32(np, DTS_PROP_IR_LDO_TYPE, &g_board_info.irled_power_type);
        PS_PRINT_INFO("read property ret is %d, irled_power_type is %d\n", ret, g_board_info.irled_power_type);
        if (BOARD_SUCC != ret)
        {
            PS_PRINT_ERR("get dts prop %s failed\n", DTS_PROP_IR_LDO_TYPE);
            goto err_get_ir_ctrl_gpio;
        }

        if (IR_GPIO_CTRL == g_board_info.irled_power_type)
        {
            ret = board_ir_ctrl_gpio_init();
            if (BOARD_SUCC != ret)
            {
                PS_PRINT_ERR("ir_ctrl_gpio init failed\n");
                goto err_get_ir_ctrl_gpio;
            }
        }
        else if (IR_LDO_CTRL == g_board_info.irled_power_type)
        {
            ret = board_ir_ctrl_pmic_init(pdev);
            if (BOARD_SUCC != ret)
            {
                PS_PRINT_ERR("ir_ctrl_pmic init failed\n");
                goto err_get_ir_ctrl_gpio;
            }
        }
        else
        {
            PS_PRINT_ERR("get ir_ldo_type failed!err num is %d\n", g_board_info.irled_power_type);
            goto err_get_ir_ctrl_gpio;
        }
    }


    return BOARD_SUCC;


err_get_ir_ctrl_gpio:
    free_board_wakeup_gpio();
oal_board_wakup_gpio_fail:
    free_board_power_gpio();
err_get_power_on_gpio:

    CHR_EXCEPTION(CHR_WIFI_DEV(CHR_WIFI_DEV_EVENT_CHIP, CHR_WIFI_DEV_ERROR_GPIO));

    return BOARD_FAIL;
}

int board_get_bwkup_gpio_val(void)
{
    return gpio_get_value(g_board_info.bfgn_wakeup_host);
}

int board_get_wlan_wkup_gpio_val(void)
{
    return gpio_get_value(g_board_info.wlan_wakeup_host);
}


int32 board_irq_init(void)
{
    int32 ret = BOARD_FAIL;
    uint32 irq = 0;
    int32 gpio = 0;

    PS_PRINT_INFO("in func\n");

    gpio = g_board_info.wlan_wakeup_host;
    irq = gpio_to_irq(gpio);
    g_board_info.wlan_irq = irq;

    PS_PRINT_INFO("wlan_irq is %d\n", g_board_info.wlan_irq);

    gpio = g_board_info.bfgn_wakeup_host;
    irq = gpio_to_irq(gpio);

    ret = request_irq(irq, bfg_wake_host_isr, IRQF_DISABLED | IRQF_TRIGGER_RISING | IRQF_NO_SUSPEND, "bfgx_wake_host", NULL);
    if (ret < 0)
    {
        PS_PRINT_ERR("couldn't acquire %s IRQ\n", PROC_NAME_GPIO_BFGN_WAKEUP_HOST);
        return BOARD_FAIL;
    }
    g_board_info.bfgn_irq = irq;

    PS_PRINT_INFO("bfgx_irq is %d\n", g_board_info.bfgn_irq);

    return BOARD_SUCC;
}

int32 board_clk_init(struct platform_device *pdev)
{
    int32 ret= BOARD_FAIL;

    PS_PRINT_INFO("in func\n");

    if (NULL == pdev)
    {
        PS_PRINT_ERR("func has NULL input param!!!\n");
        return BOARD_FAIL;
    }

    ret = get_board_pmu_clk32k();
    if(BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    ret = set_board_pmu_clk32k(pdev);
    if(BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    return BOARD_SUCC;
}

void prepare_to_power_on(void)
{
    int32 ret = BOARD_FAIL;

    if (NO_NEED_POWER_PREPARE == g_board_info.need_power_prepare)
    {
        return;
    }

    if (IS_ERR_OR_NULL(g_board_info.pctrl) || IS_ERR_OR_NULL(g_board_info.pins_idle))
    {
        PS_PRINT_ERR("power pinctrl is err, pctrl is %p, pins_idle is %p\n", g_board_info.pctrl, g_board_info.pins_idle);
        return;
    }

    /* set LowerPower mode */
    ret = pinctrl_select_state(g_board_info.pctrl, g_board_info.pins_idle);
    if (BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("power prepare:set LOWPOWER mode failed, ret:%d\n", ret);
        return;
    }

    ret = gpio_request_one(g_board_info.xldo_pinmux, GPIOF_OUT_INIT_LOW, PROC_NAME_GPIO_XLDO_PINMUX);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", PROC_NAME_GPIO_XLDO_PINMUX);
        CHR_EXCEPTION(CHR_WIFI_DEV(CHR_WIFI_DEV_EVENT_CHIP, CHR_WIFI_DEV_ERROR_GPIO));
        return;
    }

    gpio_direction_output(g_board_info.xldo_pinmux, g_board_info.gpio_xldo_level);
    g_board_info.pinmux_set_result = PINMUX_SET_SUCC;

    return;
}

void post_to_power_on(void)
{
    int32 ret = BOARD_FAIL;

    if (NO_NEED_POWER_PREPARE == g_board_info.need_power_prepare)
    {
        return;
    }

    if (PINMUX_SET_SUCC == g_board_info.pinmux_set_result)
    {
        g_board_info.pinmux_set_result = PINMUX_SET_INIT;
        gpio_free(g_board_info.xldo_pinmux);
    }

    if (IS_ERR_OR_NULL(g_board_info.pctrl) || IS_ERR_OR_NULL(g_board_info.pins_normal))
    {
        PS_PRINT_ERR("power pinctrl is err, pctrl is %p, pins_idle is %p\n", g_board_info.pctrl, g_board_info.pins_normal);
        return;
    }

    /* set NORMAL mode */
    ret = pinctrl_select_state(g_board_info.pctrl, g_board_info.pins_normal);
    if (BOARD_SUCC != ret)
    {
        PS_PRINT_ERR("power prepare:set NORMAL mode failed, ret:%d\n", ret);
        return;
    }

    return;
}
void power_state_change(int32 gpio, int32 flag)
{
    if (BOARD_POWER_ON == flag)
    {
        gpio_direction_output(gpio, GPIO_LOWLEVEL);
        mdelay(10);
        gpio_direction_output(gpio, GPIO_HIGHLEVEL);
        mdelay(30);
    }
    else if (BOARD_POWER_OFF == flag)
    {
        gpio_direction_output(gpio, GPIO_LOWLEVEL);
    }
}
void board_power_on(uint32 subsystem)
{
    if (subsystem >= POWER_BUTT)
    {
        PS_PRINT_ERR("power input system:%d error\n", subsystem);
        return;
    }
    prepare_to_power_on();
    switch (g_device_subchip_type)
    {
        case BOARD_VERSION_HI1102:
            /*hi1102 has one power*/
            power_state_change(g_board_info.power_on_enable, BOARD_POWER_ON);
            break;
        case BOARD_VERSION_HI1103:
            if (WLAN_POWER == subsystem)
            {
                /*wlan*/
                power_state_change(g_board_info.wlan_power_on_enbale, BOARD_POWER_ON);
            }
            else if (BFGX_POWER == subsystem)
            {
                /*bfgn*/
                power_state_change(g_board_info.bfgn_power_on_enable, BOARD_POWER_ON);
            }
            break;
          default:
            PS_PRINT_ERR("power on subsystem:%d error\n", subsystem);
            break;
    }

    post_to_power_on();
}
void board_power_off(uint32 subsystem)
{
    if (subsystem >= POWER_BUTT)
    {
        PS_PRINT_ERR("power input system:%d error\n", subsystem);
        return;
    }
    switch (g_device_subchip_type)
    {
        case BOARD_VERSION_HI1102:
            power_state_change(g_board_info.power_on_enable, BOARD_POWER_OFF);
            break;
        case BOARD_VERSION_HI1103:
            if (WLAN_POWER == subsystem)
            {
                /*wlan*/
                power_state_change(g_board_info.wlan_power_on_enbale, BOARD_POWER_OFF);
            }
            else if (BFGX_POWER == subsystem)
            {
                /*bfgn*/
                power_state_change(g_board_info.bfgn_power_on_enable, BOARD_POWER_OFF);
            }
            break;
        default:
            PS_PRINT_ERR("power off subsystem:%d error\n", subsystem);
            break;
    }
}

int32 find_device_board_version(void)
{
    int32 ret= BOARD_FAIL;
    const char *device_version = NULL;

    ret = get_board_custmize(DTS_NODE_HI110X, DTS_PROP_SUBCHIP_TYPE_VERSION, &device_version);
    if(BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    g_board_info.chip_type = device_version;
    return BOARD_SUCC;
}

int32 get_device_board_version(void)
{
    int32 ret= BOARD_FAIL;

    ret = find_device_board_version();
    if(BOARD_SUCC != ret)
    {
        /*����1102*/
        g_board_info.chip_type = device_board_version_list[0].name;
        g_device_subchip_type  = BOARD_VERSION_HI1102;
        PS_PRINT_WARNING("can not find device_board_version ,choose default:%s\n", device_board_version_list[0].name);
    }
    else
    {
        ret = check_device_board_name();
        if (BOARD_SUCC != ret)
        {
            return BOARD_FAIL;
        }
    }
    PS_PRINT_INFO("device_board_version is %s\n", g_board_info.chip_type);

    return BOARD_SUCC;
}

int32 check_download_channel_name(uint8* wlan_buff, int32* index)
{
    int32 i = 0;
    for (i = 0; i < MODE_DOWNLOAD_BUTT; i++)
    {
        if (0 == strncmp(device_download_mode_list[i].name, wlan_buff, strlen(device_download_mode_list[i].name)))
        {
            *index = i;
            return BOARD_SUCC;
        }
    }
    return BOARD_FAIL;
}

int32 get_download_channel(void)
{
    int32 ret= BOARD_FAIL;
    uint8 wlan_mode[DOWNLOAD_CHANNEL_LEN]={0};
    uint8 bfgn_mode[DOWNLOAD_CHANNEL_LEN]={0};

    /*wlan channel*/
    ret = find_download_channel(wlan_mode, INI_WLAN_DOWNLOAD_CHANNEL);
    if (BOARD_SUCC != ret)
    {
        /*����1102,1102�޴�������*/
        g_board_info.wlan_download_channel = MODE_SDIO;
        PS_PRINT_WARNING("can not find wlan_download_channel ,choose default:%s\n", device_download_mode_list[0].name);
    }
    else
    {
        if (BOARD_SUCC != check_download_channel_name(wlan_mode, &(g_board_info.wlan_download_channel)))
        {
            PS_PRINT_ERR("check wlan download channel:%s error\n", wlan_mode);
            return BOARD_FAIL;
        }
    }

    /*bfgn channel*/
    ret = find_download_channel(bfgn_mode, INI_BFGX_DOWNLOAD_CHANNEL);
    if (BOARD_SUCC != ret)
    {
        /*��������ڸ����Ĭ�ϱ��ֺ�wlanһ��*/
        g_board_info.bfgn_download_channel = g_board_info.wlan_download_channel;
        PS_PRINT_WARNING("can not find bfgn_download_channel ,choose default:%s\n", device_download_mode_list[0].name);
        return BOARD_SUCC;
    }

    if (BOARD_SUCC != check_download_channel_name(bfgn_mode, &(g_board_info.bfgn_download_channel)))
    {
        PS_PRINT_ERR("check bfgn download channel:%s error\n", bfgn_mode);
        return BOARD_FAIL;
    }

    PS_PRINT_INFO("wlan_download_channel index:%d, bfgn_download_channel index:%d\n",
                        g_board_info.wlan_download_channel, g_board_info.bfgn_download_channel);

    return BOARD_SUCC;
}

int32 check_device_board_name(void)
{
    int32 i = 0;
    for (i = 0; i < BOARD_VERSION_BOTT; i++)
    {
        if (0 == strncmp(device_board_version_list[i].name, g_board_info.chip_type, strlen(device_board_version_list[i].name)))
        {
            g_device_subchip_type = i;
            return BOARD_SUCC;
        }
    }
    PS_PRINT_ERR("g_board_info.chip_type=%s error\n", g_board_info.chip_type);
    return BOARD_FAIL;
}

int32 get_uart_pclk_source(void)
{
    return g_board_info.uart_pclk;
}

STATIC int32 hi110x_board_probe(struct platform_device *pdev)
{
    int ret = BOARD_FAIL;
    PS_PRINT_INFO("enter\n");

    ret = get_device_board_version();
    if (BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    ret = get_download_channel();
    if (BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    ret = board_clk_init(pdev);
    if (BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    ret = get_board_uart_port();
    if (BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    ret = board_gpio_init(pdev);
    if (BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    ret = check_evb_or_fpga();
    if (BOARD_SUCC != ret)
    {
        return BOARD_FAIL;
    }

    ret = board_irq_init();
    if (BOARD_SUCC != ret)
    {
        goto err_gpio_source;
    }

    ret = board_get_power_pinctrl(pdev);
    if (BOARD_SUCC != ret)
    {
        goto err_get_power_pinctrl;
    }

    PS_PRINT_INFO("board init ok\n");

    return BOARD_SUCC;

err_get_power_pinctrl:
    free_irq(g_board_info.bfgn_irq, NULL);
err_gpio_source:
    if (g_board_info.have_ir)
    {
        if (g_board_info.bfgn_ir_ctrl_gpio > -1)
        {
            gpio_free(g_board_info.bfgn_ir_ctrl_gpio);
        }
    }

    gpio_free(g_board_info.bfgn_wakeup_host);
    gpio_free(g_board_info.wlan_wakeup_host);
    gpio_free(g_board_info.power_on_enable);

    return BOARD_FAIL;
}

STATIC int32 hi110x_board_remove(struct platform_device *pdev)
{
    PS_PRINT_INFO("enter\n");

    if (NEED_POWER_PREPARE == g_board_info.need_power_prepare)
    {
        devm_pinctrl_put(g_board_info.pctrl);
    }

    free_irq(g_board_info.bfgn_irq, NULL);

    if(g_board_info.have_ir)
    {
        if (IR_GPIO_CTRL == g_board_info.irled_power_type)
        {
            if (g_board_info.bfgn_ir_ctrl_gpio > -1)
            {
                gpio_free(g_board_info.bfgn_ir_ctrl_gpio);
            }
        }
    }
    else
    {
        if (g_board_info.bfgn_ir_ctrl_ldo!= NULL)
        {
            regulator_put(g_board_info.bfgn_ir_ctrl_ldo);
            g_board_info.bfgn_ir_ctrl_ldo = NULL;
        }
    }

    free_board_wakeup_gpio();
    free_board_power_gpio();

    return BOARD_SUCC;
}

int32 hi110x_board_suspend(struct platform_device *pdev, pm_message_t state)
{
    return BOARD_SUCC;
}

int32 hi110x_board_resume(struct platform_device *pdev)
{
    return BOARD_SUCC;
}


/*********************************************************************/
/********************   SSI���Դ���start   ***************************/
/*********************************************************************/

#ifdef PLATFORM_DEBUG_ENABLE
#ifdef _PRE_CONFIG_GPIO_TO_SSI_DEBUG

#define HI110X_SSI_CLK_GPIO_NAME  ("hi110x ssi clk")
#define HI110X_SSI_DATA_GPIO_NAME ("hi110x ssi data")
#define INTERVAL_TIME             (10)
#define SSI_DATA_LEN              (16)

uint32 g_ssi_clk  = 0;              /*ģ��ssiʱ�ӵ�GPIO�ܽź�*/
uint32 g_ssi_data = 0;              /*ģ��ssi�����ߵ�GPIO�ܽź�*/
uint16 g_ssi_base = 0x8000;         /*ssi��ַ*/
uint32 g_interval = INTERVAL_TIME;  /*GPIO�������Ĳ��α���ʱ�䣬��λus*/
uint32 g_delay    = 5;

int32 ssi_show_setup(void)
{
    PS_PRINT_INFO("clk=%d, data=%d, interval=%d us, ssi base=0x%x, r/w delay=%d cycle\n",
                    g_ssi_clk, g_ssi_data, g_interval, g_ssi_base, g_delay);
    return BOARD_SUCC;
}

int32 ssi_setup(uint32 interval, uint32 delay, uint16 ssi_base)
{
    g_interval    = interval;
    g_delay       = delay;
    g_ssi_base    = ssi_base;

    return BOARD_SUCC;
}

int32 ssi_request_gpio(uint32 clk, uint32 data)
{
    int32 ret = BOARD_FAIL;

    PS_PRINT_INFO("request hi110x ssi GPIO\n");

    ret = gpio_request_one(clk, GPIOF_OUT_INIT_LOW, HI110X_SSI_CLK_GPIO_NAME);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", HI110X_SSI_CLK_GPIO_NAME);
        goto err_get_ssi_clk_gpio;
    }

    g_ssi_clk = clk;

    ret = gpio_request_one(data, GPIOF_OUT_INIT_LOW, HI110X_SSI_DATA_GPIO_NAME);
    if (ret)
    {
        PS_PRINT_ERR("%s gpio_request failed\n", HI110X_SSI_DATA_GPIO_NAME);
        goto err_get_ssi_data_gpio;
    }

    g_ssi_data = data;

    return BOARD_SUCC;

err_get_ssi_data_gpio:
    gpio_free(clk);
    g_ssi_clk = 0;
err_get_ssi_clk_gpio:

    CHR_EXCEPTION(CHR_WIFI_DEV(CHR_WIFI_DEV_EVENT_CHIP, CHR_WIFI_DEV_ERROR_GPIO));

    return ret;
}

int32 ssi_free_gpio(void)
{
    PS_PRINT_INFO("free hi110x ssi GPIO\n");

    if (0 != g_ssi_clk)
    {
        gpio_free(g_ssi_clk);
        g_ssi_clk = 0;
    }

    if (0 != g_ssi_data)
    {
        gpio_free(g_ssi_data);
        g_ssi_data = 0;
    }

    return BOARD_SUCC;
}

void ssi_clk_output(void)
{
    gpio_direction_output(g_ssi_clk, GPIO_LOWLEVEL);
    udelay(g_interval);
    gpio_direction_output(g_ssi_clk, GPIO_HIGHLEVEL);
}

void ssi_data_output(uint16 data)
{
    udelay(5);
    if (data)
    {
        gpio_direction_output(g_ssi_data, GPIO_HIGHLEVEL);
    }
    else
    {
        gpio_direction_output(g_ssi_data, GPIO_LOWLEVEL);
    }

    udelay(g_interval);
}

int32 ssi_write_data(uint16 addr, uint16 value)
{
    uint16 tx;
    uint32 i;

    for (i = 0; i < g_delay; i++)
    {
        ssi_clk_output();
        ssi_data_output(0);
    }

    /*����SYNCλ*/
    PS_PRINT_DBG("tx sync bit\n");
    ssi_clk_output();
    ssi_data_output(1);

    /*ָʾ���β���Ϊд���߶���д*/
    PS_PRINT_DBG("tx r/w->w\n");
    ssi_clk_output();
    ssi_data_output(0);

    /*���͵�ַ*/
    PS_PRINT_DBG("write addr:0x%x\n", addr);
    for (i = 0; i < SSI_DATA_LEN; i++)
    {
        tx = (addr >> (SSI_DATA_LEN - i - 1)) & 0x0001;
        PS_PRINT_DBG("tx addr bit %d:%d\n", SSI_DATA_LEN - i - 1, tx);
        ssi_clk_output();
        ssi_data_output(tx);
    }

    /*��������*/
    PS_PRINT_DBG("write value:0x%x\n", value);
    for (i = 0; i < SSI_DATA_LEN; i++)
    {
        tx = (value >> (SSI_DATA_LEN - i - 1)) & 0x0001;
        PS_PRINT_DBG("tx data bit %d:%d\n", SSI_DATA_LEN - i - 1, tx);
        ssi_clk_output();
        ssi_data_output(tx);
    }

    /*���ݷ�������Ժ󣬱���delay�����ڵ�0*/
    PS_PRINT_DBG("ssi write:finish, delay %d cycle\n", g_delay);
    for (i = 0; i < g_delay; i++)
    {
        ssi_clk_output();
        ssi_data_output(0);
    }

    return BOARD_SUCC;
}

uint16 ssi_read_data(uint16 addr)
{
#define SSI_READ_RETTY (1000)
    uint16 tx;
    uint32 i;
    uint32 retry = 0;
    uint16 rx;
    uint16 data = 0;

    for (i = 0; i < g_delay; i++)
    {
        ssi_clk_output();
        ssi_data_output(0);
    }

    /*����SYNCλ*/
    PS_PRINT_DBG("tx sync bit\n");
    ssi_clk_output();
    ssi_data_output(1);

    /*ָʾ���β���Ϊ�����߶���д*/
    PS_PRINT_DBG("tx r/w->r\n");
    ssi_clk_output();
    ssi_data_output(1);

    /*���͵�ַ*/
    PS_PRINT_DBG("read addr:0x%x\n", addr);
    for (i = 0; i < SSI_DATA_LEN; i++)
    {
        tx = (addr >> (SSI_DATA_LEN - i - 1)) & 0x0001;
        PS_PRINT_DBG("tx addr bit %d:%d\n", SSI_DATA_LEN - i - 1, tx);
        ssi_clk_output();
        ssi_data_output(tx);
    }

    /*�ӳ�һ��clk��������һ������ֻ�����˰��ʱ������*/
    ssi_clk_output();

    /*����data��GPIOΪ���룬׼����ȡ����*/
    gpio_direction_input(g_ssi_data);

    PS_PRINT_DBG("data in mod, current gpio level is %d\n", gpio_get_value(g_ssi_data));

    /*��ȡSYNCͬ��λ*/
    do
    {
        ssi_clk_output();
        udelay(g_interval);
        if(gpio_get_value(g_ssi_data))
        {
            PS_PRINT_DBG("read data sync bit ok, retry=%d\n", retry);
            break;
        }
        retry++;
    }while(SSI_READ_RETTY != retry);

    if (SSI_READ_RETTY == retry)
    {
        PS_PRINT_ERR("ssi read sync bit timeout\n");
        ssi_data_output(0);
        return data;
    }

    for (i = 0; i < SSI_DATA_LEN; i++)
    {
        ssi_clk_output();
        udelay(g_interval);
        rx = gpio_get_value(g_ssi_data);
        PS_PRINT_DBG("rx data bit %d:%d\n", SSI_DATA_LEN - i - 1, rx);
        data = data | (rx << (SSI_DATA_LEN - i - 1));
    }

    /*�ָ�data��GPIOΪ����������0*/
    ssi_data_output(0);

    return data;
}

int32 ssi_write16(uint16 addr, uint16 value)
{
#define write_retry   (3)
    uint32 retry = 0;

    do
    {
        ssi_write_data(addr, value);
        if (value == ssi_read_data(addr))
        {
            PS_PRINT_DBG("ssi write: 0x%x=0x%x succ\n", addr, value);
            return BOARD_SUCC;
        }
        retry++;
    }while(retry < write_retry);

    PS_PRINT_ERR("ssi write: 0x%x=0x%x fail\n", addr, value);

    return BOARD_FAIL;
}

uint16 ssi_read16(uint16 addr)
{
    uint16 data;

    data = ssi_read_data(addr);

    PS_PRINT_SUC("ssi read: 0x%x=0x%x\n", addr, data);

    return data;
}

int32 ssi_write32(uint32 addr, uint16 value)
{
    uint16 addr_half_word_high;
    uint16 addr_half_word_low;

    addr_half_word_high = (addr >> 16) & 0xffff;
    addr_half_word_low  = (addr & 0xffff) >> 1;

    /*������ַд��ַ�ĸ�16λ*/
    if (ssi_write16(g_ssi_base, addr_half_word_high) < 0)
    {
        PS_PRINT_ERR("ssi write: 0x%x=0x%x fail\n", addr, value);
        return BOARD_FAIL;
    }

    /*�͵�ַдʵ��Ҫд���value*/
    if (ssi_write16(addr_half_word_low, value) < 0)
    {
        PS_PRINT_ERR("ssi write: 0x%x=0x%x fail\n", addr, value);
        return BOARD_FAIL;
    }

    PS_PRINT_SUC("ssi write: 0x%x=0x%x succ\n", addr, value);

    return BOARD_SUCC;
}

int32 ssi_read32(uint32 addr)
{
    uint16  data = 0;
    uint16 addr_half_word_high;
    uint16 addr_half_word_low;

    addr_half_word_high = (addr >> 16) & 0xffff;
    addr_half_word_low  = (addr & 0xffff) >> 1;

    if (ssi_write16(g_ssi_base, addr_half_word_high) < 0)
    {
        PS_PRINT_ERR("ssi read 0x%x fail\n", addr);
        return BOARD_FAIL;
    }

    data = ssi_read_data(addr_half_word_low);

    PS_PRINT_SUC("ssi read: 0x%x=0x%x\n", addr, data);

    return data;
}

#endif
#endif

/*********************************************************************/
/********************   SSI���Դ���end    ****************************/
/*********************************************************************/

#ifdef _PRE_CONFIG_USE_DTS
static struct of_device_id hi110x_board_match_table[] = {
	{
		.compatible = DTS_COMP_HI110X_BOARD_NAME,
		.data = NULL,
    },
	{ },
};
#endif

STATIC struct platform_driver hi110x_board_driver = {
        .probe      = hi110x_board_probe,
        .remove     = hi110x_board_remove,
        .suspend    = hi110x_board_suspend,
        .resume     = hi110x_board_resume,
        .driver     = {
            .name   = "hi110x_board",
            .owner  = THIS_MODULE,
#ifdef _PRE_CONFIG_USE_DTS
			.of_match_table	= hi110x_board_match_table,
#endif
        },
};

int32 hi110x_board_init(void)
{
    int32 ret = BOARD_FAIL;

    PS_PRINT_FUNCTION_NAME;

    ret = platform_driver_register(&hi110x_board_driver);
    if (ret)
    {
        PS_PRINT_ERR("Unable to register hisi connectivity board driver.\n");
    }

    return ret;
}

void hi110x_board_exit(void)
{
    platform_driver_unregister(&hi110x_board_driver);
}


