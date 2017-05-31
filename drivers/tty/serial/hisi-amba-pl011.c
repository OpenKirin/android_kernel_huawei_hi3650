/*
 * Hisilicon Amba-pl011.c.
 *
 * Copyright (c) 2016 HUAWEI.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */
#define TX_WORK_TIMEOUT  1600000

int pl011_tx_stat_show(struct seq_file *s, void *arg)
{
	unsigned int uart_tx_buf_size = 0;
	struct uart_tx_unit *unit = (struct uart_tx_unit *)s->private;
	uart_tx_buf_size = kfifo_size(&unit->tx_fifo);
	seq_puts(s, "console transfer statics:\n");
	seq_printf(s, "fifo over cnt : %ld\n", unit->tx_buf_over_cnt);
	seq_printf(s, "fifo over len : %ld\n", unit->tx_buf_over_size);
	seq_printf(s, "fifo capacity : 0x%lx(%ldk)\n", (unsigned long)uart_tx_buf_size, (unsigned long)uart_tx_buf_size/1024);
	seq_printf(s, "fifo required : 0x%lx(%ldk)\n", unit->tx_buf_max, unit->tx_buf_max/1024);
	seq_printf(s, "fifo useage   : %ld%%\n", (unit->tx_buf_max*100)/uart_tx_buf_size);
	if (unit->tx_buf_max > uart_tx_buf_size) {
		seq_printf(s, "     overflow : %ld%% ~ %ld%%\n", ((unit->tx_buf_max-uart_tx_buf_size)*100)/uart_tx_buf_size, ((unit->tx_buf_max-uart_tx_buf_size)*100)/uart_tx_buf_size + 1);
	}
	seq_printf(s, "printk cnt    : %ld\n", unit->tx_buf_times);
	seq_printf(s, "printk data   : %ld\n", unit->tx_got);
	seq_printf(s, "fifo in       : %ld\n", unit->tx_queued);
	seq_printf(s, "fifo out      : %ld\n", unit->tx_out);
	seq_printf(s, "uart send     : %ld\n", unit->tx_sent);
	seq_printf(s, "tasklet run   : %ld\n", unit->tx_uart_tasklet_run);
	seq_printf(s, "p_cnt/t_run   : %ld:1\n", unit->tx_buf_times/unit->tx_uart_tasklet_run);
	return 0;
}

int pl011_tx_stat_open(struct inode *inode, struct file *file)
{
	return single_open(file, pl011_tx_stat_show, inode->i_private);
}

const struct file_operations pl011_tx_stat_ops = {
	.open		= pl011_tx_stat_open,
	.read		= seq_read,
	.llseek		= seq_lseek,
	.release	= single_release,
};

#ifdef CONFIG_SERIAL_AMBA_PL011_CONSOLE
#ifdef PL011_UART_TX_WORK
void pl011_uart_tx_work(struct work_struct *work)
#else
void pl011_uart_tx_work(unsigned long work)
#endif
{
	struct uart_tx_unit *unit = (struct uart_tx_unit *)work;
	struct uart_amba_port *uap = container_of(unit, struct uart_amba_port, tx_unit);
	static char local_static_buf[PL011_TX_LOCAL_BUF_SIZE] = "";
	unsigned int out_len = 0;
	unsigned int pos = 0;
	unsigned int status, old_cr, new_cr;
	int locked = 1;
	int ret, timeout = TX_WORK_TIMEOUT;
	unsigned long flags = 0;
	unsigned int fbrd = 0, ibrd = 0, lcrh_rx = 0, lcrh_tx = 0;

	unit->tx_uart_tasklet_run++;

	local_irq_save(flags);

	/* lock uart port */
	if (uap->port.sysrq) {
		locked = 0;
	}
	else if (oops_in_progress) {
		locked = spin_trylock(&uap->port.lock);
	}
	else
		spin_lock(&uap->port.lock);

	ret = clk_enable(uap->clk);
	if (ret) {
		printk(KERN_ERR	"could not enable clock\n");
	}

	fbrd = readw(uap->port.membase + UART011_FBRD);
	ibrd = readw(uap->port.membase + UART011_IBRD);
	lcrh_rx = readw(uap->port.membase + uap->lcrh_rx);
	if (uap->lcrh_tx != uap->lcrh_rx)
		lcrh_tx = readw(uap->port.membase + uap->lcrh_tx);
	writew(uap->console_fbrd, uap->port.membase + UART011_FBRD);
	writew(uap->console_ibrd, uap->port.membase + UART011_IBRD);
	writew(uap->console_lcrh_rx, uap->port.membase + uap->lcrh_rx);
	if (uap->lcrh_tx != uap->lcrh_rx) {
		int i;
		/*
		* Wait 10 PCLKs before writing LCRH_TX register,
		* to get this delay write read only register 10 times
		*/
		for (i = 0; i < 10; ++i)
			writew(0xff, uap->port.membase + UART011_MIS);
		writew(uap->console_lcrh_tx, uap->port.membase + uap->lcrh_tx);
	}

	/*
	 *	First save the CR then disable the interrupts
	 */
	old_cr = readw(uap->port.membase + UART011_CR);
	new_cr = old_cr & ~UART011_CR_CTSEN;
	new_cr |= UART01x_CR_UARTEN | UART011_CR_TXE;
	writew(new_cr, uap->port.membase + UART011_CR);

	/* fifo out and send */
	spin_lock(&unit->tx_lock_in);
	out_len = kfifo_out(&unit->tx_fifo, local_static_buf, PL011_TX_LOCAL_BUF_SIZE);
	spin_unlock(&unit->tx_lock_in);
	unit->tx_out += out_len;
	for (pos = 0; pos < out_len; pos++) {
		if (('\n' == local_static_buf[pos]) && (0 != pos) && ('\r' != local_static_buf[pos-1])) {
			pl011_console_putchar(&uap->port, '\r');
		}
		pl011_console_putchar(&uap->port, local_static_buf[pos]);
		unit->tx_sent++;
	}

	/* still something to print, call another work */
	if (kfifo_len(&unit->tx_fifo) > 0) {
		if ((-1 == unit->tx_cpuid) || (unit->max_cpus <= unit->tx_cpuid)) {
			schedule_work(&unit->tx_work);
		} else {
			schedule_work_on(unit->tx_cpuid, &unit->tx_work);
		}
	}

	/*
	 *	Finally, wait for transmitter to become empty
	 *	and restore the TCR
	 */
	do {
		status = readw(uap->port.membase + UART01x_FR);
	} while ((status & UART01x_FR_BUSY) && timeout--);
	writew(old_cr, uap->port.membase + UART011_CR);

	if (timeout == -1) {
		printk(KERN_ERR "%s: PL011 tx work timeout\n", __func__);
	}

	writew(fbrd, uap->port.membase + UART011_FBRD);
	writew(ibrd, uap->port.membase + UART011_IBRD);
	writew(lcrh_rx, uap->port.membase + uap->lcrh_rx);
	if (uap->lcrh_tx != uap->lcrh_rx) {
		int i;
		/*
		* Wait 10 PCLKs before writing LCRH_TX register,
		* to get this delay write read only register 10 times
		*/
		for (i = 0; i < 10; ++i)
			writew(0xff, uap->port.membase + UART011_MIS);
		writew(lcrh_tx, uap->port.membase + uap->lcrh_tx);
	}

#ifdef CONFIG_ARCH_HI6XXX
	if (false == Chip_Verification_Check_Debug(CHIP_VERIFICATION_UART_DEBUG)) {
		clk_disable(uap->clk);
	}
#else
		clk_disable(uap->clk);
#endif

	/* unlock uart port */
	if (locked)
		spin_unlock(&uap->port.lock);

	local_irq_restore(flags);
}
int pl011_tx_work_init(struct uart_amba_port *uap, unsigned int aurt_tx_buf_size, int cpuid)
{
	struct uart_tx_unit *unit = &uap->tx_unit;
	char dbgfs_name[16];
	int ret;

	ret = kfifo_alloc(&unit->tx_fifo, aurt_tx_buf_size, GFP_KERNEL | __GFP_ZERO);
	if (ret) {
		printk(KERN_ERR "%s: port[%d] malloc fail\n", __func__, uap->port.line);
		return ret;
	}

	spin_lock_init(&unit->tx_lock_in);

#ifdef PL011_UART_TX_WORK
	INIT_WORK(&unit->tx_work, pl011_uart_tx_work);
#else
	tasklet_init(&unit->tx_work, pl011_uart_tx_work, (unsigned long)unit);
#endif

	unit->tx_got  = 0;
	unit->tx_uart_fifo_full = 0;
	unit->tx_uart_fifo_full_lost = 0;
	unit->tx_sent = 0;
	unit->tx_out = 0;
	unit->tx_queued  = 0;
	unit->tx_valid   = 1;
	unit->tx_cpuid = cpuid;
	unit->max_cpus = num_possible_cpus();
	unit->tx_buf_times     = 0;
	unit->tx_buf_max       = 0;
	unit->tx_buf_over_cnt  = 0;
	unit->tx_buf_over_size = 0;
	unit->tx_uart_tasklet_run = 0;

	snprintf(dbgfs_name, 16, "uart%d_stat", uap->port.line);
#ifdef CONFIG_HISI_DEBUG_FS
	debugfs_create_file(dbgfs_name, S_IRUGO, NULL, unit, &pl011_tx_stat_ops);
#endif
	return 0;
}

int pl011_tx_work_uninit(struct uart_amba_port *uap)
{
	struct uart_tx_unit *unit = &uap->tx_unit;

	if (!unit->tx_valid) {
		return -ENODEV;
	}
	unit->tx_valid   = 0;
	unit->tx_cpuid = UART_TX_CPUON_NOTSET;
	kfifo_free(&unit->tx_fifo);
	unit->tx_got     = 0;
	unit->tx_uart_fifo_full = 0;
	unit->tx_uart_fifo_full_lost = 0;
	unit->tx_queued  = 0;
	unit->tx_sent    = 0;
	unit->tx_out     = 0;
	unit->tx_buf_times     = 0;
	unit->tx_buf_max       = 0;
	unit->tx_buf_over_cnt  = 0;
	unit->tx_buf_over_size = 0;
	unit->tx_uart_tasklet_run = 0;
	return 0;
}
#endif

void uart_chip_reset_endisable(struct uart_amba_port *dev, unsigned int enable)
{
	unsigned int ret;
	int timeout = 10;
	if (dev->reset) {
		if (enable) {
			writel(BIT(dev->reset_bit), dev->reset_reg_base + dev->reset_enable_off);
			do {
				ret = readl(dev->reset_reg_base + dev->reset_status_off);
				ret &= BIT(dev->reset_bit);
				udelay(1);
			} while (!ret && timeout--);
		} else {
			writel(BIT(dev->reset_bit), dev->reset_reg_base  + dev->reset_disable_off);
			do {
				ret = readl(dev->reset_reg_base + dev->reset_status_off);
				ret &= BIT(dev->reset_bit);
				udelay(1);
			} while (ret && timeout--);
		}
	}
}
void
pl011_console_write_tx(struct console *co, const char *s, unsigned int count)
{
	struct uart_amba_port *uap = amba_ports[co->index];
	struct uart_tx_unit *unit = &uap->tx_unit;
	unsigned int copyed_len = 0;
	unsigned int fifo_len = 0;
	unsigned long flag = 0;

	spin_lock_irqsave(&unit->tx_lock_in, flag);
	copyed_len = kfifo_in(&unit->tx_fifo, s, count);
	fifo_len = kfifo_len(&unit->tx_fifo);
	unit->tx_got += count;
	unit->tx_buf_times++;
	unit->tx_queued += copyed_len;
	if (copyed_len < count) {
		/* fifo over-flow */
		unit->tx_buf_over_cnt++;
		unit->tx_buf_over_size += (count-copyed_len);
		unit->tx_buf_max = max(unit->tx_buf_max, (unsigned long)(fifo_len + count - copyed_len));
	} else {
		unit->tx_buf_max = max(unit->tx_buf_max, (unsigned long)fifo_len);
	}
#ifdef PL011_UART_TX_WORK
	if ((-1 == unit->tx_cpuid) || (unit->max_cpus <= unit->tx_cpuid) || !cpu_online(unit->tx_cpuid)) {
		schedule_work(&unit->tx_work);
	} else {
		schedule_work_on(unit->tx_cpuid, &unit->tx_work);
	}
#else
	tasklet_schedule(&unit->tx_work);
#endif
	spin_unlock_irqrestore(&unit->tx_lock_in, flag);

}

int hisi_pl011_probe_get_clk_freq(struct amba_device *dev, struct uart_amba_port *uap, int i) {
	int ret;
	u64 clk_rate = 0;	        /* high speed clk vaule */


	ret = of_property_read_u64(dev->dev.of_node, "clock-rate", &clk_rate);
	if (!ret && (clk_rate > 0)) {
		dev_info(&dev->dev, "%s:reset clock rate[%lld]!\n", __func__, clk_rate);
		/* reset the clock rate*/
		ret = clk_set_rate(uap->clk, clk_rate);
		if (ret) {
			dev_err(&dev->dev, "%s:set clock rate[%lld] fail! ret[0x%x]\n",
				__func__, clk_rate, ret);
			devm_clk_put(&dev->dev, uap->clk);
		}
	} else {
		dev_info(&dev->dev, "UART%d doesn't have valid clock-rate value in dts!\n", i);
	}
	return ret;
}
int hisi_pl011_probe_reset_func_enable(struct amba_device *dev, struct uart_amba_port *uap) {
	struct device_node *node = NULL;
	int ret;
	u32 data[4];
	u32 flag_reset_enable = 0;

	/* get uart reset base regester */
	node = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");

	if (node)
		uap->reset_reg_base = of_iomap(node, 0);

	/*read reset function*/
	ret = of_property_read_u32(dev->dev.of_node, "reset-enable-flag", &flag_reset_enable);
	if (ret || (NULL == node)) {
		uap->reset = false;
		dev_info(&dev->dev, "can't get \"reset-enable-flag\" property. reset will be disable.\n");
	} else {
		if (flag_reset_enable) {
			/* get uart reset-base regester */
			ret = of_property_read_u32_array(dev->dev.of_node, "reset-reg-base", &data[0], 4);
			if (ret) {
				uap->reset_reg_base = NULL;
				uap->reset = false;
				dev_info(&dev->dev, "can't get \"reset-reg-base\" property. reset will be disable.\n");
			} else {
				uap->reset_reg_base = ioremap(data[1], data[3]);
			}

			/* get uart reset control regester */
			ret = of_property_read_u32_array(dev->dev.of_node, "reset-controller-reg", &data[0], 4);
			if (ret) {
				uap->reset = false;
				dev_info(&dev->dev, "can't get \"reset-controller-reg\" property. reset will be disable.\n");
			} else {
				uap->reset_enable_off = data[0];
				uap->reset_disable_off = data[1];
				uap->reset_status_off = data[2];
				uap->reset_bit = data[3];
				if (uap->reset_reg_base != NULL) {
					uap->reset = true;
				} else {
					uap->reset = false;
				}
			}
		} else {
			uap->reset = false;
		}
	}
	return ret;
}
void hisi_pl011_probe_console_enable(struct amba_device *dev, struct uart_amba_port *uap, char* amba_console_name) {
	u32 console_fifo_size = 0;
	int console_fifo_cpuon = 0;
	char console_uart_name[8] = "";

	if (0 == get_console_name(console_uart_name, sizeof(console_uart_name))) {
		if (0 == strcmp(console_uart_name, amba_console_name))
			console_uart_name_is_ttyAMA = 1;
	}
	if (console_uart_name_is_ttyAMA && (get_console_index() == (int)uap->port.line)) {
		/* get console fifo enable flag */
		if (of_property_read_u32(dev->dev.of_node, "console-fifo-enable", &uap->tx_unit.tx_valid)) {
			uap->tx_unit.tx_valid = 0;
			dev_info(&dev->dev, "%s:don't have console-fifo-enable property! set disable as default.\n", __func__);
		} else {
			if (uap->tx_unit.tx_valid) {
				dev_info(&dev->dev, "%s:enable serial console fifo!\n", __func__);
				/* get console fifo size */
				if (of_property_read_u32(dev->dev.of_node, "console-fifo-size", &console_fifo_size)) {
					console_fifo_size = UART_TX_BUF_SIZE_DEF;
					dev_err(&dev->dev, "%s don't have console-fifo-size property! set 0x%x as default.\n", __func__, UART_TX_BUF_SIZE_DEF);
				}
				/* get console fifo cpuon */
				if (of_property_read_u32(dev->dev.of_node, "console-fifo-cpuon", (u32 *)&console_fifo_cpuon)) {
					console_fifo_cpuon = UART_TX_CPUON_NOTSET;
					dev_err(&dev->dev, "%s don't have console-fifo-cpuon property! set fifo on cpu disabled.\n", __func__);
				} else {
					dev_info(&dev->dev, "%s set fifo on cpu:%d.\n", __func__, console_fifo_cpuon);
				}
				pl011_tx_work_init(uap, console_fifo_size, console_fifo_cpuon);
			} else {
				dev_info(&dev->dev, "%s:disable serial console fifo!\n", __func__);
			}
		}
	}
}
void pl011_pm(struct uart_port *port, unsigned int state, unsigned int oldstate)
{
	int retval;
	struct uart_amba_port *uap = (struct uart_amba_port *)port;
	switch (state) {
	case UART_PM_STATE_ON:
		retval = clk_prepare_enable(uap->clk);
		if (retval)
			dev_err(uap->port.dev, "%s: clk_prepare_enable failed!!\n", __func__);
		break;

	case UART_PM_STATE_OFF:
		clk_disable_unprepare(uap->clk);
		break;
	default:
		dev_err(uap->port.dev, "%s: pm state error!!state=%d.\n", __func__, state);
		break;
	}
	return;
}

struct console *get_uart_console(void) /* add by hisi-balong */
{
	struct console *uart_console = amba_reg.cons;
	return uart_console;
}
void
hisi_pl011_console_write(struct console *co, const char *s, unsigned int count)
{
	if (amba_ports[co->index]->tx_unit.tx_valid) {
		pl011_console_write_tx(co, s, count);
	} else {
		pl011_console_write(co, s, count);
	}
}
#ifdef CONFIG_PM_SLEEP
int hisi_pl011_suspend(struct device *dev)
{
	struct uart_amba_port *uap = dev_get_drvdata(dev);
	int ret;

	if (!uap)
		return -EINVAL;
	dev_info(uap->port.dev, "%s: +\n", __func__);
	ret = uart_suspend_port(&amba_reg, &uap->port);
	dev_info(uap->port.dev, "%s: -\n", __func__);
	return ret;
}

int hisi_pl011_resume(struct device *dev)
{
	struct uart_amba_port *uap = dev_get_drvdata(dev);
	int ret;

	if (!uap)
		return -EINVAL;
	dev_info(uap->port.dev, "%s: +\n", __func__);
	ret =  uart_resume_port(&amba_reg, &uap->port);
	dev_info(uap->port.dev, "%s: -\n", __func__);
	return ret;
}
#endif

int hisi_pl011_pinctrl(struct amba_device *dev, struct uart_amba_port *uap)
{
	int ret = 0;

	uap->pinctrl = devm_pinctrl_get(&dev->dev);

	if (IS_ERR(uap->pinctrl)) {
		ret = PTR_ERR(uap->pinctrl);
		return ret;
	}
	uap->pins_default = pinctrl_lookup_state(uap->pinctrl,
						 PINCTRL_STATE_DEFAULT);
	if (IS_ERR(uap->pins_default))
		dev_err(&dev->dev, "could not get default pinstate\n");

	uap->pins_idle = pinctrl_lookup_state(uap->pinctrl,
					       PINCTRL_STATE_IDLE);
	if (IS_ERR(uap->pins_idle))
		dev_err(&dev->dev, "could not get sleep pinstate\n");

	return ret;
}
void hisi_pl011_disable_ms(struct uart_port *port)
{
	struct uart_amba_port *uap =
	    container_of(port, struct uart_amba_port, port);

	uap->im &= ~(UART011_RIMIM|UART011_CTSMIM|UART011_DCDMIM|UART011_DSRMIM);
	writew(uap->im, uap->port.membase + UART011_IMSC);
}