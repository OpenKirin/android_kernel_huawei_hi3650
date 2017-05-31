/*!
 *****************************************************************************
 *
 * @File       sysbrg_pdump.c
 * @Title      The System Bridge pdump interface.
 * @Description    This file contains the System Bridge Pdump support for Linux.
 * ---------------------------------------------------------------------------
 *
 * Copyright (c) Imagination Technologies Ltd.
 * 
 * The contents of this file are subject to the MIT license as set out below.
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in 
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN 
 * THE SOFTWARE.
 * 
 * Alternatively, the contents of this file may be used under the terms of the 
 * GNU General Public License Version 2 ("GPL")in which case the provisions of
 * GPL are applicable instead of those above. 
 * 
 * If you wish to allow use of your version of this file only under the terms 
 * of GPL, and not to allow others to use your version of this file under the 
 * terms of the MIT license, indicate your decision by deleting the provisions 
 * above and replace them with the notice and other provisions required by GPL 
 * as set out in the file called "GPLHEADER" included in this distribution. If 
 * you do not delete the provisions above, a recipient may use your version of 
 * this file under the terms of either the MIT license or GPL.
 * 
 * This License is also included in this distribution in the file called 
 * "MIT_COPYING".
 *
 *****************************************************************************/

#include <img_defs.h>
#include <linux/sysbrg_pdump.h>

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/poll.h>
#include <linux/device.h>
#include <linux/pci.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/idr.h>
#include <linux/string.h>
#include <linux/kobject.h>
#include <linux/interrupt.h>
#include <linux/sched.h>
#include <asm/io.h>
#include <linux/version.h>


/* Default ISR parameters */
static struct imgpci_isrparams	default_isrparams =
{
	/* addr_status */
	{
		2,
		0x608
	},
	/* addr_mask */
	{
		2,
		0x610
	},
	/* addr_clear */
	{
		2,
		0x60C
	}
};

static IMG_INT32 imgpci_major;
static DEFINE_IDR(imgpci_idr);
static struct file_operations imgpci_fops;

static struct pci_device_id imgpci_pci_ids[] =
{
	{
		.vendor =       IMGPCI_VENDOR_ID,
		.device =       PCI_ANY_ID,
		.subvendor =    PCI_ANY_ID,
		.subdevice =    PCI_ANY_ID,
        0, 0, 0,
	},
	{
		0,0,0,0,0,0,0,
	}
};

/* IMGPCI class infrastructure */
static struct imgpci_class
{
	struct kref kref;
	struct class *class;
} *imgpci_class;

static int imgpci_read32(struct imgpci_info *info, unsigned long bar, unsigned long offset, unsigned long * value);
static int imgpci_write32(struct imgpci_info *info, unsigned long bar, unsigned long offset, unsigned long value);

#ifdef IMGPCI_EXTRA_DEBUG
unsigned long g_int_count_total		= 0;
unsigned long g_int_count_acked		= 0;
unsigned long g_read_count =0, g_rw_error_count = 0, g_open_count = 0;
#endif

/*
 * attributes
 */

static struct attribute attr_addr =
{
	.name  = "addr",
	.mode  = S_IRUGO,
};

static struct attribute attr_size =
{
	.name  = "size",
	.mode  = S_IRUGO,
};

#ifdef IMGPCI_EXTRA_DEBUG
static struct attribute attr_intaddr =
{
	.name  = "intaddr",
	.mode  = S_IRUGO,
};
#endif

static struct attribute* map_attrs[] =
{
  #ifdef IMGPCI_EXTRA_DEBUG
	&attr_addr, &attr_size, &attr_intaddr, NULL
  #else
	&attr_addr, &attr_size, NULL
  #endif
};

/*!
******************************************************************************

 @Function              map_attr_show

******************************************************************************/
static ssize_t map_attr_show(struct kobject *kobj, struct attribute *attr, char *buf)
{
	struct imgpci_mem *mem = container_of(kobj, struct imgpci_mem, kobj);

	if (strncmp(attr->name,"addr",4) == 0)
	{
		return sprintf(buf, "0x%lx\n", mem->addr);
	}

	if (strncmp(attr->name,"size",4) == 0)
	{
		return sprintf(buf, "0x%lx\n", mem->size);
	}

  #ifdef IMGPCI_EXTRA_DEBUG
	if (strncmp(attr->name,"intaddr",4) == 0)
	{
		return sprintf(buf, "0x%lx\n", mem->internal_addr);
	}
  #endif

	return -ENODEV;
}

/*!
******************************************************************************

 @Function              map_attr_release

******************************************************************************/
static void map_attr_release(struct kobject *kobj)
{
	/* needs doing */
}

static struct sysfs_ops map_attr_ops =
{
	.show  = map_attr_show,
};

static struct kobj_type map_attr_type =
{
	.release	= map_attr_release,
	.sysfs_ops	= &map_attr_ops,
	.default_attrs	= map_attrs,
};

/*!
******************************************************************************

 @Function              show_name

******************************************************************************/
static ssize_t show_name(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct imgpci_device *idev = dev_get_drvdata(dev);
	if (idev)
	{
		return sprintf(buf, "%s\n", idev->info->name);
	}
	else
	{
		return -ENODEV;
	}
}
static DEVICE_ATTR(name, S_IRUGO, show_name, NULL);

/*!
******************************************************************************

 @Function              show_version

******************************************************************************/
static ssize_t show_version(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct imgpci_device *idev = dev_get_drvdata(dev);
	if (idev)
	{
		return sprintf(buf, "%s\n", idev->info->version);
	}
	else
	{
		return -ENODEV;
	}
}
static DEVICE_ATTR(version, S_IRUGO, show_version, NULL);

/*!
******************************************************************************

 @Function              show_event

******************************************************************************/
static ssize_t show_event(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct imgpci_device *idev = dev_get_drvdata(dev);
	if (idev)
	{
		return sprintf(buf, "%u\n", (unsigned int)atomic_read(&idev->event));
	}
	else
	{
		return -ENODEV;
	}
}
static DEVICE_ATTR(event, S_IRUGO, show_event, NULL);

/*!
******************************************************************************

@Function              show_fpga_release

******************************************************************************/
static ssize_t show_fpga_release(struct device *dev, struct device_attribute *attr, char *buf)
{
#define BAR                 (1)
#define FPGA_RELEASE_OFFSET (0x604)
#define FPGA_RELEASE_MASK   (0x0000FFFF)

	struct imgpci_device *idev = dev_get_drvdata(dev);
	struct imgpci_info *		info = idev->info;
	unsigned long value = 0;

	if (idev)
	{
		imgpci_read32(info, BAR, FPGA_RELEASE_OFFSET, &value);

		return sprintf(buf, "%ld (0x%lx)\n", value & FPGA_RELEASE_MASK, value & FPGA_RELEASE_MASK);
	}
	else
	{
		return -ENODEV;
	}
#undef BAR
#undef FPGA_RELEASE_OFFSET
#undef FPGA_RELEASE_MASK
}
static DEVICE_ATTR(fpga_release, S_IRUGO, show_fpga_release, NULL);

/*!
******************************************************************************

@Function              show_msvdx_core_rev

******************************************************************************/
static ssize_t show_msvdx_core_rev(struct device *dev, struct device_attribute *attr, char *buf)
{
#define BAR                 (1)
#define FPGA_MSVDX_CORE_REV_OFFSET (0x640)
#define FPGA_MSVDX_CORE_REV_MASK   (0xFFFFFFFF)
#define FPGA_MSVDX_CORE_REV_MAJOR_MASK   (0x00FF0000)
#define FPGA_MSVDX_CORE_REV_MINOR_MASK   (0x0000FF00)
#define FPGA_MSVDX_CORE_REV_MAINT_MASK   (0x000000FF)

	struct imgpci_device *idev = dev_get_drvdata(dev);
	struct imgpci_info *		info = idev->info;
	unsigned long value = 0;

	if (idev)
	{
		imgpci_read32(info, BAR, FPGA_MSVDX_CORE_REV_OFFSET, &value);

		return sprintf(buf, "%ld.%ld.%ld (major.minor.maint)\n", (value & FPGA_MSVDX_CORE_REV_MAJOR_MASK) >> 16, (value & FPGA_MSVDX_CORE_REV_MINOR_MASK) >> 8, value & FPGA_MSVDX_CORE_REV_MAINT_MASK);
	}
	else
	{
		return -ENODEV;
	}
#undef BAR
#undef FPGA_MSVDX_CORE_REV_OFFSET
#undef FPGA_MSVDX_CORE_REV_MASK
}
static DEVICE_ATTR(msvdx_core_rev, S_IRUGO, show_msvdx_core_rev, NULL);

#ifdef IMGPCI_EXTRA_DEBUG
/*!
******************************************************************************

 @Function              show_intstate

******************************************************************************/
static ssize_t show_intstate(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct imgpci_device *idev = dev_get_drvdata(dev);
	struct imgpci_info *		info = idev->info;
	if (idev)
	{
		unsigned long mask, status;

		imgpci_read32(info, info->isrparams.addr_mask.bar, info->isrparams.addr_mask.offset, &mask);
		imgpci_read32(info, info->isrparams.addr_status.bar, info->isrparams.addr_status.offset, &status);

		return sprintf(buf, "Interrupt Status:\nint_mask=0x%08X\nint_status=0x%08X\nint_disabled=%d\n\nmask=0x%08X\nstatus=0x%08X\n\ng_int_count_total=%d\ng_int_count_acked=%d\ng_read_count=%d\ng_rw_error_count=%d\n\ng_open_count=%d\n", idev->info->int_mask, idev->info->int_status, idev->info->int_disabled, mask, status, g_int_count_total, g_int_count_acked, g_read_count, g_rw_error_count, g_open_count);
	}
	else
	{
		return -ENODEV;
	}
}
static DEVICE_ATTR(intstate, S_IRUGO, show_intstate, NULL);
#endif

static struct attribute *imgpci_attrs[] =
{
	&dev_attr_name.attr,
	&dev_attr_version.attr,
	&dev_attr_event.attr,
	&dev_attr_fpga_release.attr,
    &dev_attr_msvdx_core_rev.attr,
  #ifdef IMGPCI_EXTRA_DEBUG
	&dev_attr_intstate.attr,
  #endif
	NULL,
};

static struct attribute_group imgpci_attr_grp =
{
	.attrs = imgpci_attrs,
};

/*!
******************************************************************************

 @Function              imgpci_dev_add_attributes

******************************************************************************/
static IMG_INT32 imgpci_dev_add_attributes(struct imgpci_device *idev)
{
	IMG_INT32 ret;
	IMG_INT32 mi;
	IMG_INT32 map_found = 0;
	struct imgpci_mem *mem;

	ret = sysfs_create_group(&idev->dev->kobj, &imgpci_attr_grp);
	if (ret)
	{
		goto err_group;
	}

	for (mi = 0; mi < MAX_IMGPCI_MAPS; mi++)
	{
		mem = &idev->info->mem[mi];
		if (mem->size == 0)
		{
			break;
		}
		if (!map_found)
		{
			map_found = 1;

			kobject_set_name(&idev->map_attr_kset.kobj,"maps");

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
			idev->map_attr_kset.ktype = &map_attr_type;
#else
			idev->map_attr_kset.kobj.ktype = &map_attr_type;
#endif
			idev->map_attr_kset.kobj.parent = &idev->dev->kobj;
			ret = kset_register(&idev->map_attr_kset);
			if (ret)
			{
				goto err_remove_group;
			}
		}
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
		kobject_init(&mem->kobj);
		kobject_set_name(&mem->kobj,"map%d",mi);
		mem->kobj.parent = &idev->map_attr_kset.kobj;
#else
		kobject_init(&mem->kobj, &map_attr_type);
#endif
		mem->kobj.kset = &idev->map_attr_kset;
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
		ret = kobject_add(&mem->kobj);
#else
		ret = kobject_add(&mem->kobj, &idev->map_attr_kset.kobj, "map%d",mi);
#endif
		if (ret)
		{
			goto err_remove_maps;
		}
	}

	return IMG_SUCCESS;

err_remove_maps:
	for (mi--; mi>=0; mi--)
	{
		mem = &idev->info->mem[mi];
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
		kobject_unregister(&mem->kobj);
#else
		kobject_put(&mem->kobj);
#endif
	}
	kset_unregister(&idev->map_attr_kset); /* Needed ? */
err_remove_group:
	sysfs_remove_group(&idev->dev->kobj, &imgpci_attr_grp);
err_group:
	dev_err(idev->dev, "error creating sysfs files (%d)\n", ret);
	return ret;
}


/*!
******************************************************************************

 @Function              imgpci_dev_del_attributes

******************************************************************************/
static IMG_VOID imgpci_dev_del_attributes(struct imgpci_device *idev)
{
	IMG_INT32 mi;
	struct imgpci_mem *mem;
	for (mi = 0; mi < MAX_IMGPCI_MAPS; mi++)
	{
		mem = &idev->info->mem[mi];
		if (mem->size == 0)
		{
			break;
		}
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,25)
		kobject_unregister(&mem->kobj);
#else
		kobject_put(&mem->kobj);
#endif
	}
	kset_unregister(&idev->map_attr_kset);
	sysfs_remove_group(&idev->dev->kobj, &imgpci_attr_grp);
}


/*!
******************************************************************************

 @Function              imgpci_get_minor

******************************************************************************/
static IMG_INT32 imgpci_get_minor(struct imgpci_device *idev)
{
	static DEFINE_MUTEX(minor_lock);
	IMG_INT32 retval = -ENOMEM;
	IMG_INT32 id;

	mutex_lock(&minor_lock);
	if (idr_pre_get(&imgpci_idr, GFP_KERNEL) == 0)
	{
		goto exit;
	}

	retval = idr_get_new(&imgpci_idr, idev, &id);
	if (retval < 0)
	{
		if (retval == -EAGAIN)
		{
			retval = -ENOMEM;
		}
		goto exit;
	}
	idev->minor = id & 255;
exit:
	mutex_unlock(&minor_lock);
	return retval;
}


/*!
******************************************************************************

 @Function              imgpci_free_minor

******************************************************************************/
static IMG_VOID imgpci_free_minor(struct imgpci_device *idev)
{
	idr_remove(&imgpci_idr, idev->minor);
}


/*!
******************************************************************************

 @Function              imgpci_event_notify

******************************************************************************/
static void imgpci_event_notify(struct imgpci_info *info)
{
	struct imgpci_device *idev = info->imgpci_dev;

	atomic_inc(&idev->event);
	wake_up_interruptible(&idev->wait);
	kill_fasync(&idev->async_queue, SIGIO, POLL_IN);
}

/*!
******************************************************************************

 @Function              imgpci_interrupt

******************************************************************************/
#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,19)
static irqreturn_t imgpci_interrupt(IMG_INT32 irq, IMG_VOID *dev_id, struct pt_regs *regs)
#else
static irqreturn_t imgpci_interrupt(IMG_INT32 irq, IMG_VOID *dev_id)
#endif
{
	struct imgpci_device *idev = (struct imgpci_device *)dev_id;
	irqreturn_t ret = idev->info->handler(irq, idev->info);

	if (ret == IRQ_HANDLED)
	{
		imgpci_event_notify(idev->info);
	}

	return ret;
}


struct imgpci_listener
{
	struct imgpci_device *dev;
	IMG_INT32 event_count;
};

/*!
******************************************************************************

 @Function              imgpci_open

******************************************************************************/
static IMG_INT32 imgpci_open(struct inode *inode, struct file *filep)
{
	struct imgpci_device *		idev;
	struct imgpci_listener *	listener;
	struct imgpci_info *		info;

	idev = idr_find(&imgpci_idr, iminor(inode));
	if (!idev)
	{
		return -ENODEV;
	}
	info = idev->info;

	listener = kmalloc(sizeof(*listener), GFP_KERNEL);
	if (!listener)
	{
		return -ENOMEM;
	}

	listener->dev = idev;
	listener->event_count = atomic_read(&idev->event);
	filep->private_data = listener;

	/* Return the ISR data to the ground state */
	spin_lock_irq(&info->read_lock);
	imgpci_write32(info, info->isrparams.addr_mask.bar, info->isrparams.addr_mask.offset, 0);
	imgpci_write32(info, info->isrparams.addr_clear.bar, info->isrparams.addr_clear.offset, info->int_mask);
	info->int_mask = 0;
	info->int_status = 0;
	info->int_disabled = 1;
	spin_unlock_irq(&info->read_lock);
  #ifdef IMGPCI_EXTRA_DEBUG
	g_open_count ++;
  #endif
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              imgpci_fasync

******************************************************************************/
static IMG_INT32 imgpci_fasync(IMG_INT32 fd, struct file *filep, IMG_INT32 on)
{
	struct imgpci_listener *listener = filep->private_data;
	struct imgpci_device *idev = listener->dev;

	return fasync_helper(fd, filep, on, &idev->async_queue);
}


/*!
******************************************************************************

 @Function              imgpci_release

******************************************************************************/
static IMG_INT32 imgpci_release(struct inode *inode, struct file *filep)
{
	IMG_INT32    				ret = 0;
	struct imgpci_listener *	listener = filep->private_data;
	struct imgpci_device *		idev = listener->dev;
	struct imgpci_info *		info = idev->info;

	if (filep->f_flags & FASYNC)
	{
		ret = imgpci_fasync(-1, filep, 0);
	}

	/* Return the ISR data to the ground state */
	spin_lock_irq(&info->read_lock);
	imgpci_write32(info, info->isrparams.addr_mask.bar, info->isrparams.addr_mask.offset, 0);
	imgpci_write32(info, info->isrparams.addr_clear.bar, info->isrparams.addr_clear.offset, info->int_mask);
	info->int_mask = 0;
	info->int_status = 0;
	info->int_disabled = 1;
	spin_unlock_irq(&info->read_lock);

	kfree(listener);
	return ret;
}


/*!
******************************************************************************

 @Function              imgpci_poll

******************************************************************************/
static IMG_UINT32 imgpci_poll(struct file *filep, poll_table *wait)
{
	struct imgpci_listener *listener = filep->private_data;
	struct imgpci_device *idev = listener->dev;

	poll_wait(filep, &idev->wait, wait);
	if (listener->event_count != atomic_read(&idev->event))
	{
		return POLLIN | POLLRDNORM;
	}
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              imgpci_read

******************************************************************************/
static ssize_t imgpci_read(struct file *filep, IMG_CHAR __user *buf, size_t count, loff_t *ppos)
{
	struct imgpci_listener *	listener = filep->private_data;
	struct imgpci_device *		idev = listener->dev;
	struct imgpci_info *		info = idev->info;
	DECLARE_WAITQUEUE(wait, current);
	ssize_t						retval;
	struct imgpci_readdata __user *	user_readdata	= (struct imgpci_readdata __user *) buf;
	struct imgpci_readdata		local_readdata;


	if (count != sizeof(struct imgpci_readdata))
	{
		return -EINVAL;
	}

  #ifdef IMGPCI_EXTRA_DEBUG
	g_read_count ++;
  #endif

	/* Clear, then enable interrupts */
	spin_lock_irq(&info->read_lock);
	imgpci_write32(info, info->isrparams.addr_clear.bar, info->isrparams.addr_clear.offset, (info->int_mask & info->int_status));
	imgpci_write32(info, info->isrparams.addr_mask.bar, info->isrparams.addr_mask.offset, info->int_mask);
	info->int_disabled = 0;
	spin_unlock_irq(&info->read_lock);

	add_wait_queue(&idev->wait, &wait);

	do
	{
		set_current_state(TASK_INTERRUPTIBLE);

		local_readdata.event_count = atomic_read(&idev->event);

		if (local_readdata.event_count != listener->event_count)
		{
			// do we need a protected read around this variable?
			local_readdata.int_status = info->int_status;

			if (copy_to_user(user_readdata, &local_readdata, sizeof(struct imgpci_readdata)))
			{
				retval = -EFAULT;
			}
			else
			{
				listener->event_count = local_readdata.event_count;
				retval = count;
			}
			break;
		}

		if (filep->f_flags & O_NONBLOCK)
		{
			retval = -EAGAIN;
			break;
		}

		if (signal_pending(current))
		{
			retval = -ERESTARTSYS;
			break;
		}
		/*	We have set the task as TASK_INTERRUPTIBLE so the schedule call will put us to sleep
			until the next time there is an interrupt (http://www.faqs.org/docs/kernel_2_4/lki-2.html)
		*/
		schedule();
	} while (1);

	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&idev->wait, &wait);

	return retval;
}


/*!
******************************************************************************

 @Function              imgpci_find_mem_index

******************************************************************************/
static int imgpci_find_mem_index(struct vm_area_struct *vma)
{
	int mi;
	struct imgpci_device *idev = vma->vm_private_data;

	for (mi = 0; mi < MAX_IMGPCI_MAPS; mi++)
	{
		if (idev->info->mem[mi].size == 0)
		{
			return -1;
		}
		if (vma->vm_pgoff == mi)
		{
			return mi;
		}
	}
	return -1;
}


/*!
******************************************************************************

 @Function              imgpci_mmap_physical

******************************************************************************/
static IMG_INT32 imgpci_mmap_physical(struct vm_area_struct *vma)
{
	struct imgpci_device *idev = vma->vm_private_data;
	IMG_INT32 mi = imgpci_find_mem_index(vma);
	if (mi < 0)
	{
		return -EINVAL;
	}

	vma->vm_flags |= VM_IO;
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	return remap_pfn_range(vma,
			       vma->vm_start,
			       idev->info->mem[mi].addr >> PAGE_SHIFT,
			       vma->vm_end - vma->vm_start,
			       vma->vm_page_prot);
}


/*!
******************************************************************************

 @Function              imgpci_mmap

******************************************************************************/
static IMG_INT32 imgpci_mmap(struct file *filep, struct vm_area_struct *vma)
{
	struct imgpci_listener *listener = filep->private_data;
	struct imgpci_device *idev = listener->dev;
	int mi;
	unsigned long requested_pages, actual_pages;

	if (vma->vm_end < vma->vm_start)
	{
		return -EINVAL;
	}

	vma->vm_private_data = idev;

	mi = imgpci_find_mem_index(vma);
	if (mi < 0)
	{
		return -EINVAL;
	}

	requested_pages = (vma->vm_end - vma->vm_start) >> PAGE_SHIFT;
	actual_pages = (idev->info->mem[mi].size + PAGE_SIZE -1) >> PAGE_SHIFT;
	if (requested_pages > actual_pages)
	{
		return -EINVAL;
	}

	return imgpci_mmap_physical(vma);
}



/*!
******************************************************************************

 @Function              imgpci_ioctl

******************************************************************************/
static long imgpci_ioctl(struct file *filep, IMG_UINT32 cmd, unsigned long arg)
{
	struct imgpci_listener *listener = filep->private_data;
	struct imgpci_device *idev = listener->dev;

	if (idev->info->ioctl)
	{
		return (idev->info->ioctl(idev->info, cmd, arg));
	}
	else
	{
		return -ENOTTY;
	}
}


static struct file_operations imgpci_fops =
{
	.owner		= THIS_MODULE,
	.open		= imgpci_open,
	.release	= imgpci_release,
	.read		= imgpci_read,
	.mmap		= imgpci_mmap,
	.poll		= imgpci_poll,
	.fasync		= imgpci_fasync,
	.unlocked_ioctl	= imgpci_ioctl,
};

/*!
******************************************************************************

 @Function              imgpci_major_init

******************************************************************************/
static IMG_INT32 imgpci_major_init(IMG_VOID)
{
	imgpci_major = register_chrdev(0, "imgpci", &imgpci_fops);
	if (imgpci_major < 0)
	{
		return imgpci_major;
	}
	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              imgpci_major_cleanup

******************************************************************************/
static IMG_VOID imgpci_major_cleanup(IMG_VOID)
{
	unregister_chrdev(imgpci_major, "imgpci");
}


/*!
******************************************************************************

 @Function              init_imgpci_class

******************************************************************************/
static IMG_INT32 init_imgpci_class(IMG_VOID)
{
	IMG_INT32 ret = 0;

	if (imgpci_class != NULL)
	{
		kref_get(&imgpci_class->kref);
		goto exit;
	}

	/* This is the first time in here, set everything up properly */
	ret = imgpci_major_init();
	if (ret)
	{
		goto exit;
	}

	imgpci_class = kzalloc(sizeof(*imgpci_class), GFP_KERNEL);
	if (!imgpci_class)
	{
		ret = -ENOMEM;
		goto err_kzalloc;
	}

	kref_init(&imgpci_class->kref);
	imgpci_class->class = class_create(THIS_MODULE, "imgpci");
	if (IS_ERR(imgpci_class->class))
	{
		ret = IS_ERR(imgpci_class->class);
		printk(KERN_ERR "class_create failed for imgpci\n");
		goto err_class_create;
	}
	return IMG_SUCCESS;

err_class_create:
	kfree(imgpci_class);
	imgpci_class = NULL;
err_kzalloc:
	imgpci_major_cleanup();
exit:
	return ret;
}


/*!
******************************************************************************

 @Function              release_imgpci_class

******************************************************************************/
static IMG_VOID release_imgpci_class(struct kref *kref)
{
	/* Ok, we cheat as we know we only have one imgpci_class */
	class_destroy(imgpci_class->class);
	kfree(imgpci_class);
	imgpci_major_cleanup();
	imgpci_class = NULL;
}


/*!
******************************************************************************

 @Function              imgpci_class_destroy

******************************************************************************/
static IMG_VOID imgpci_class_destroy(IMG_VOID)
{
	if (imgpci_class)
	{
		kref_put(&imgpci_class->kref, release_imgpci_class);
	}
}


/*!
******************************************************************************

 @Function              imgpci_request_irq

******************************************************************************/
static IMG_INT32 imgpci_request_irq (struct imgpci_info *info)
{
	struct imgpci_device *idev = info->imgpci_dev;
	IMG_INT32 ret = 0;

	if (idev->info->irq_enabled)
	{
		return -1;
	}

	ret = request_irq(idev->info->irq, imgpci_interrupt, idev->info->irq_flags, idev->info->name, idev);

	if (ret)
	{
		return -1;
	}

	idev->info->irq_enabled = 1;

	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              imgpci_register_device

******************************************************************************/
static IMG_INT32 imgpci_register_device(struct device *parent, struct imgpci_info *info)
{
	struct imgpci_device *idev;
	IMG_INT32 ret = 0;

	if (!parent || !info || !info->name || !info->version)
	{
		return -EINVAL;
	}

	info->imgpci_dev = NULL;

	ret = init_imgpci_class();
	if (ret)
	{
		return ret;
	}

	idev = kzalloc(sizeof(*idev), GFP_KERNEL);
	if (!idev)
	{
		ret = -ENOMEM;
		goto err_kzalloc;
	}

	idev->owner = THIS_MODULE;
	idev->info = info;
	init_waitqueue_head(&idev->wait);
	atomic_set(&idev->event, 0);

	ret = imgpci_get_minor(idev);
	if (ret)
	{
		goto err_get_minor;
	}

#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,26)
	idev->dev = device_create(imgpci_class->class, parent, MKDEV(imgpci_major, idev->minor), "imgpci%u", idev->minor);
#elif ((LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,26)) && (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,27)))
	idev->dev = device_create_drvdata(imgpci_class->class, parent, MKDEV(imgpci_major, idev->minor), NULL, "imgpci%u", idev->minor);
#else
	idev->dev = device_create(imgpci_class->class, parent, MKDEV(imgpci_major, idev->minor), NULL, "imgpci%u", idev->minor);
#endif
	if (IS_ERR(idev->dev))
	{
		printk(KERN_ERR "IMGPCI: device register failed\n");
		ret = PTR_ERR(idev->dev);
		goto err_device_create;
	}
	dev_set_drvdata(idev->dev, idev);

	ret = imgpci_dev_add_attributes(idev);
	if (ret)
	{
		goto err_imgpci_dev_add_attributes;
	}

	info->imgpci_dev = idev;

#ifndef IMG_PENWELL
	/* request irq */
	ret = imgpci_request_irq (info);
	if(ret)
	{
		goto err_imgpci_dev_add_attributes;
	}
#endif

	return IMG_SUCCESS;

	imgpci_dev_del_attributes(idev);
err_imgpci_dev_add_attributes:
	device_destroy(imgpci_class->class, MKDEV(imgpci_major, idev->minor));
err_device_create:
	imgpci_free_minor(idev);
err_get_minor:
	kfree(idev);
err_kzalloc:
	imgpci_class_destroy();
	return ret;
}


/*!
******************************************************************************

 @Function              imgpci_unregister_device

******************************************************************************/
static IMG_VOID imgpci_unregister_device(struct imgpci_info *info)
{
	struct imgpci_device *idev;

	if (!info || !info->imgpci_dev)
	{
        printk(KERN_ERR "%s info 0x%pK info->imgpci_dev 0x%pK\n", __FUNCTION__,
               info, info? info->imgpci_dev: NULL);
		return;
	}

	idev = info->imgpci_dev;

	imgpci_free_minor(idev);

	if ((info->irq >= 0) && info->irq_enabled)
	{
		free_irq(info->irq, idev);
	}

	imgpci_dev_del_attributes(idev);

	dev_set_drvdata(idev->dev, NULL);
	device_destroy(imgpci_class->class, MKDEV(imgpci_major, idev->minor));
	kfree(idev);
	imgpci_class_destroy();

	return;
}



/************************************************************************************************
							Lower level driver functions
*************************************************************************************************/



/*!
******************************************************************************

 @Function              imgpci_write32

******************************************************************************/
static IMG_INT32 imgpci_write32(struct imgpci_info *info, unsigned long bar, unsigned long offset, unsigned long value)
{
	IMG_VOID *reg;

	if ((bar > MAX_IMGPCI_MAPS) || !info->mem[bar].internal_addr)
	{
	  #ifdef IMGPCI_EXTRA_DEBUG
		g_rw_error_count += 0x10000;
	  #endif
		return -1;
	}

	reg = info->mem[bar].internal_addr + offset;
	iowrite32(value, (void __iomem *) reg);

	return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              imgpci_read32

******************************************************************************/
static IMG_INT32 imgpci_read32(struct imgpci_info *info, unsigned long bar, unsigned long offset, unsigned long * value)
{
	IMG_VOID *reg;

	if ((bar > MAX_IMGPCI_MAPS) || !info->mem[bar].internal_addr)
	{
	  #ifdef IMGPCI_EXTRA_DEBUG
		g_rw_error_count ++;
	  #endif
		return -1;
	}

	reg = info->mem[bar].internal_addr + offset;
	*value = ioread32((void __iomem *) reg);

	return IMG_SUCCESS;
}


/*!
******************************************************************************

 @Function              imgpci_handler

******************************************************************************/
static irqreturn_t imgpci_handler(IMG_INT32 irq, struct imgpci_info *info)
{
	unsigned long	int_status = 0;

#ifdef IMGPCI_EXTRA_DEBUG
	g_int_count_total++;
#endif

	imgpci_read32(info, info->isrparams.addr_status.bar, info->isrparams.addr_status.offset, &int_status);

	/*	If the interrupt is disabled or there is no indication of an interrupt in the int_status
		we return IRQ_NONE. This probably means that the interrupt was generated by another device
		with the same IRQ#
	*/
	if (info->int_disabled || ((info->int_mask & int_status) == 0))
	{
		return IRQ_NONE;
	}

	/* This interrupt looks like it belongs to us... */


	/* Record the interrupt status register value */
	info->int_status = int_status;

	/* Disable all interrupts */
	imgpci_write32(info, info->isrparams.addr_mask.bar, info->isrparams.addr_mask.offset, 0x00000000);
	info->int_disabled = 1;

  #ifdef IMGPCI_EXTRA_DEBUG
	g_int_count_acked++;
  #endif

	return IRQ_HANDLED;
}


/*!
******************************************************************************

 @Function              imgpci_perform_ioctl

******************************************************************************/
static IMG_INT32 imgpci_perform_ioctl(struct imgpci_info *info,	IMG_UINT32 cmd, unsigned long arg)
{
	IMG_VOID __user *argp = (IMG_VOID __user *) arg;

	if ((_IOC_TYPE(cmd) != IMGPCI_IOCTL_MAGIC) ||
		(_IOC_NR(cmd) > IMGPCI_IOCTL_MAXNR)
	)
	{
		return -ENOTTY;
	}

	switch (cmd)
	{
		/* Write32 */
		case IMGPCI_IOCTL_WRITE32:
		{
			struct imgpci_reg32	reg;

			if (copy_from_user(&reg, argp, sizeof(reg)))
			{
				return -EFAULT;
			}

			spin_lock(&info->ioctl_lock);
			if (imgpci_write32(info, reg.address.bar, reg.address.offset, reg.value))
			{
				spin_unlock(&info->ioctl_lock);
				return -EINVAL;
			}
			spin_unlock(&info->ioctl_lock);
			break;
		}
		/* Read32 */
		case IMGPCI_IOCTL_READ32:
		{
			struct imgpci_reg32		reg;

			if (copy_from_user(&reg, argp, sizeof(reg)))
			{
				return -EFAULT;
			}

			spin_lock(&info->ioctl_lock);
			if (imgpci_read32(info, reg.address.bar, reg.address.offset, &reg.value))
			{
				spin_unlock(&info->ioctl_lock);
				return -EINVAL;
			}
			spin_unlock(&info->ioctl_lock);

			if (copy_to_user(argp, &reg, sizeof(reg)))
			{
				return -EFAULT;
			}
			break;
		}
		/* Interrupt enable/disable */
		case IMGPCI_IOCTL_INTEN:
		case IMGPCI_IOCTL_INTDIS:
		{
			/* The enable pattern is passed directly as the argument */
			unsigned long	en_pattern = arg;

			spin_lock_irq(&info->ioctl_lock);

			/* Apply the enable pattern to the interrupt mask */
			if (cmd == IMGPCI_IOCTL_INTEN)
			{
				info->int_mask |= en_pattern;	/* Interrupt enable */
			}
			else
			{
				info->int_mask &= ~en_pattern;	/* Interrupt disable */
			}

			/* If the interrupt is enabled then write the modified interrupt mask */
			if (!info->int_disabled)
			{
				if (imgpci_write32(info, info->isrparams.addr_mask.bar, info->isrparams.addr_mask.offset, info->int_mask))
				{
					spin_unlock_irq(&info->ioctl_lock);
					return -EINVAL;
				}
			}
			spin_unlock_irq(&info->ioctl_lock);
			break;
		}
		/* ISR parameter set command */
		case IMGPCI_IOCTL_SETISRPARAMS:
		{
			spin_lock_irq(&info->ioctl_lock);
			if (copy_from_user(&info->isrparams, argp, sizeof(info->isrparams)))
			{
				spin_unlock_irq(&info->ioctl_lock);
				return -EFAULT;
			}
			spin_unlock_irq(&info->ioctl_lock);
			break;
		}
		default:
		{
			return -ENOTTY;
		}
	}
	return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              imgpci_pci_probe

******************************************************************************/
static IMG_INT32 imgpci_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	struct imgpci_info *info;
	IMG_UINT32 ui32Bar;

	/* Allocate a imgpci_info structure */
	info = kzalloc(sizeof(struct imgpci_info), GFP_KERNEL);
	if (!info)
		return -ENOMEM;

	/* Enable the device */
	if (pci_enable_device(dev))
	{
		goto out_free;
	}

	/* Remap PCI bars.  */
	for	(ui32Bar = 0; ui32Bar < MAX_IMGPCI_MAPS; ui32Bar++)
	{
		info->mem[ui32Bar].addr = pci_resource_start(dev, ui32Bar);
		info->mem[ui32Bar].size = pci_resource_len(dev, ui32Bar);
		info->mem[ui32Bar].internal_addr = SYSDEVU1_RemapResources(dev, ui32Bar);
	}

	info->name = "imgpcidev";
	info->version = "0.0.1";
	info->irq = dev->irq;
	info->irq_flags = IRQF_DISABLED | IRQF_SHARED;
	info->handler = imgpci_handler;
	info->int_mask = 0;
	info->int_status = 0;
	info->int_disabled = 1;

	info->ioctl = imgpci_perform_ioctl;
	spin_lock_init(&info->ioctl_lock);
	spin_lock_init(&info->read_lock);


	memcpy(&info->isrparams, &default_isrparams, sizeof(struct imgpci_isrparams));

	/* Disable all interrupts to start with */
	imgpci_write32(info, info->isrparams.addr_mask.bar, info->isrparams.addr_mask.offset, 0);

	if (imgpci_register_device(&dev->dev, info))
	{
		goto out_disable;
	}

	pci_set_drvdata(dev, info);
	{
		return IMG_SUCCESS;
	}

out_disable:
	pci_disable_device(dev);

out_free:
	kfree (info);

	return -ENODEV;
}


/*!
******************************************************************************

 @Function              imgpci_pci_remove

******************************************************************************/
static IMG_VOID imgpci_pci_remove(struct pci_dev *dev)
{
	struct imgpci_info *info = pci_get_drvdata(dev);

    /* We disable the device before removing our IRQ, but we do not unmap
       the registers as that will be done by the real driver. */
	pci_disable_device(dev);
	imgpci_unregister_device(info);
	pci_set_drvdata(dev, NULL);

	kfree (info);
}

/*!
******************************************************************************

 @Function              imgpci_register_pdump

******************************************************************************/
IMG_INT32 imgpci_register_pdump(IMG_VOID)
{
	struct pci_dev *dev;

	dev = pci_get_device(IMGPCI_VENDOR_ID, IMGPCI_DEVICE_ID, NULL);
	if(!dev) {
		return -ENODEV;
	}

	if(imgpci_pci_probe(dev, imgpci_pci_ids)) {
		return -ENODEV;
	}

	return IMG_SUCCESS;
}

/*!
******************************************************************************

 @Function              imgpci_unregister_pdump

******************************************************************************/
IMG_VOID imgpci_unregister_pdump(IMG_VOID)
{
	struct pci_dev *dev;

	dev = pci_get_device(IMGPCI_VENDOR_ID, IMGPCI_DEVICE_ID, NULL);
	if(!dev) {
        printk(KERN_INFO "%s device not found\n", __FUNCTION__);
		return;
	}

	imgpci_pci_remove(dev);
}
