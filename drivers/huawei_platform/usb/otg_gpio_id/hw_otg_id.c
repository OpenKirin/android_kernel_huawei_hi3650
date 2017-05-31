#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/spinlock.h>
#include <linux/mutex.h>
#include <linux/wakelock.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_irq.h>
#include <linux/delay.h>
#include <linux/of_address.h>
#include <linux/regulator/consumer.h>
#include <linux/clk.h>
#include <linux/of_gpio.h>
#include <linux/hisi/usb/hisi_usb.h>

#include "hw_otg_id.h"

#include <linux/mfd/hisi_pmic.h>
#include <pmic_interface.h>
#include <linux/hisi/hisi_adc.h>

static struct work_struct   otg_id_intb_work;
static struct otg_gpio_id_dev *otg_gpio_id_dev_p;

#define VBATT_AVR_MAX_COUNT 10
#define ADC_VOLTAGE_LIMIT   150    //mV


/*************************************************************************************************
*  Function:       hw_is_usb_cable_connected
*  Discription:    Check whether Vbus has been exist.
*  Parameters:   void
*  return value:  zero:     Vbus isn't exist.
*                      no zero:  Vbus is exist.
**************************************************************************************************/

static int hw_is_usb_cable_connected(void)
{
    struct otg_gpio_id_dev *dev = otg_gpio_id_dev_p;
    int ret = 0;

    if (0 == dev->fpga_flag) {
        ret = (hisi_pmic_reg_read(PMIC_STATUS0_ADDR(0)) & (VBUS4P3_D10 | VBUS_COMP_VBAT_D20));
    }
    return ret;
}

/*************************************************************************************************
*  Function:       hw_otg_intb_work
*  Discription:    Handle GPIO about OTG.
*  Parameters:   work: The work struct of otg.
*  return value:  void
**************************************************************************************************/
static void hw_otg_id_intb_work(struct work_struct *work)
{
    int gpio_value = -1;
    int avgvalue = 0,i = 0,sum = 0;
    int vol_value = 0;

    /* VBUS is on or not*/
    if (0 == !hw_is_usb_cable_connected()){
        hw_usb_err("%s The vbus is on ,otg fail !\n", __func__);
        return;
    }

    /*get GPIO value level*/
    gpio_value = gpio_get_value(otg_gpio_id_dev_p->gpio);
    if (0 == gpio_value){
        /*get adc channel*/
        if (0 == otg_gpio_id_dev_p->otg_adc_channel){
            hw_usb_err("%s Get otg_adc_channel is fail!\n", __func__);
            return;
        }

        for(i = 0;i < VBATT_AVR_MAX_COUNT; i++){
            vol_value = hisi_adc_get_value(otg_gpio_id_dev_p->otg_adc_channel);
            if(vol_value < 0){
                hw_usb_err("%s The value from ADC is error", __func__);
                continue;
            }
            msleep(10);
            sum += vol_value;
        }
        avgvalue = sum/VBATT_AVR_MAX_COUNT;

        hw_usb_err("%s The average voltage of ADC is %d\n", __func__, avgvalue);
        if(avgvalue <= ADC_VOLTAGE_LIMIT){
            hw_usb_err("%s Send ID_FALL_EVENT\n", __func__);
            hisi_usb_otg_event(ID_FALL_EVENT);
        }
    }
    else{
		hw_usb_err("%s Send ID_RISE_EVENT\n", __func__);
        hisi_usb_otg_event(ID_RISE_EVENT);
    }
    return;
}

/*************************************************************************************************
*  Function:       hw_otg_id_irq_handle
*  Discription:    Handle the GPIO200 irq.
*  Parameters:   irq: The number of irq for GPIO200
*                      dev_id: The id of devices.
*  return value:  IRQ_HANDLED
**************************************************************************************************/
static irqreturn_t hw_otg_id_irq_handle(int irq, void *dev_id)
{
	schedule_work(&otg_id_intb_work);
    return IRQ_HANDLED;
}

/*************************************************************************************************
*  Function:       hw_otg_id_probe
*  Discription:    otg probe function.
*  Parameters:   pdev: The porinter of pdev
*  return value:  IRQ_HANDLED
**************************************************************************************************/
static int hw_otg_id_probe(struct platform_device *pdev)
{
    int ret = -1;
    struct device_node *np = NULL;
    struct device* dev = NULL;

    hw_usb_err("Enter %s funtion\n", __func__);

    if (NULL == pdev) {
        hw_usb_err("%s The pdev is NULL !\n", __func__);
        return ret;
    }

    otg_gpio_id_dev_p = (struct otg_gpio_id_dev *)devm_kzalloc(&pdev->dev, sizeof(*otg_gpio_id_dev_p), GFP_KERNEL);
    if (NULL == otg_gpio_id_dev_p) {
        hw_usb_err("%s alloc otg_dev failed! not enough memory\n", __func__);
        return ret;
    }
    otg_gpio_id_dev_p->pdev = pdev;

    dev = &pdev->dev;
    np = dev->of_node;

    ret = of_property_read_u32(np, "otg_adc_channel", &(otg_gpio_id_dev_p->otg_adc_channel));
    if (0 != ret) {
        hw_usb_err("%s Get otg_adc_channel failed !!! \n", __func__);
        return ret;
    }

    otg_gpio_id_dev_p->gpio = of_get_named_gpio(np, "otg-gpio", 0);
    if (otg_gpio_id_dev_p->gpio < 0) {
        hw_usb_err("%s of_get_named_gpio error!!! gpio=%d.\n", __func__, otg_gpio_id_dev_p->gpio);
        return ret;
    }

    ret = of_property_read_u32(np, "fpga_flag", &(otg_gpio_id_dev_p->fpga_flag));
    if (0 != ret) {
        otg_gpio_id_dev_p->fpga_flag = 0;
        usb_dbg("%s in asic mode!\n", __func__);
    }

    /*init otg intr handle work funtion*/
    INIT_WORK(&otg_id_intb_work, hw_otg_id_intb_work);
    /*
     * init otg gpio process
     */
    ret = gpio_request(otg_gpio_id_dev_p->gpio, "otg_gpio_irq");
    if (ret < 0) {
        hw_usb_err("%s gpio_request error!!! ret=%d. gpio=%d.\n", __func__, ret, otg_gpio_id_dev_p->gpio);
        return ret;
    }

    ret = gpio_direction_input(otg_gpio_id_dev_p->gpio);
    if (ret < 0) {
        hw_usb_err("%s gpio_direction_input error!!! ret=%d. gpio=%d.\n", __func__, ret, otg_gpio_id_dev_p->gpio);
        return ret;
    }

    otg_gpio_id_dev_p->irq = gpio_to_irq(otg_gpio_id_dev_p->gpio);
    if (otg_gpio_id_dev_p->irq < 0) {
        hw_usb_err("%s gpio_to_irq error!!! dev_p->gpio=%d, dev_p->irq=%d.\n", __func__, otg_gpio_id_dev_p->gpio, otg_gpio_id_dev_p->irq);
        return ret;
    }

    ret = request_irq(otg_gpio_id_dev_p->irq,
               hw_otg_id_irq_handle,
               IRQF_NO_SUSPEND | IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING,
               "otg_gpio_irq", NULL);
    if (ret < 0) {
        hw_usb_err("%s request otg irq handle funtion fail!! ret:%d\n", __func__, ret);
        return ret;
    }

    /* check the otg status when the phone poweron*/
    ret = gpio_get_value(otg_gpio_id_dev_p->gpio);
    if(0 == ret){
      /*call work function to handle irq*/
      schedule_work(&otg_id_intb_work);
    }

    usb_dbg("Exit [%s]-\n", __func__);

    return 0;
}

static struct of_device_id hw_otg_id_of_match[] = {
    { .compatible = "huawei,usbotg-by-id", },
    { },
};

static struct platform_driver hw_otg_id_drv = {
    .probe      = hw_otg_id_probe,
    .driver     = {
        .owner      = THIS_MODULE,
        .name       = "hw_otg_id",
        .of_match_table = hw_otg_id_of_match,
    },
};

static int __init hw_otg_id_init(void)
{
    int ret = 0;

    ret = platform_driver_register(&hw_otg_id_drv);
    hw_usb_err("Enter [%s] function, ret is %d\n", __func__, ret);
    return ret;
}

static void __exit hw_otg_id_exit(void)
{
    platform_driver_unregister(&hw_otg_id_drv);
    return ;
}

device_initcall_sync(hw_otg_id_init);
module_exit(hw_otg_id_exit);

MODULE_AUTHOR("huawei");
MODULE_DESCRIPTION("This module detect USB OTG connection/disconnection");
MODULE_LICENSE("GPL v2");

