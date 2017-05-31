#ifdef CONFIG_DEBUG_FS
#include "pcie-kirin.h"
int hipcie_get_eyepattern_param(void *dev_data, char *buf, size_t len)
{
	struct kirin_pcie *pcie = (struct kirin_pcie *)dev_data;
	int ret = 0;
	u32 eye_diagram_param;
	u32 eye_diagram_param2;

	if (pcie) {
		eye_diagram_param = pcie->pcie_eye_param_ctrl2;
		eye_diagram_param2 = pcie->pcie_eye_param_ctrl3;
		ret = scnprintf(buf, len, "0x%x,0x%x\n", eye_diagram_param, eye_diagram_param2);
	} else {
		PCIE_PR_INFO("kirin_pcie NULL\n");
		ret = scnprintf(buf, len, "kirin_pcie NULL\n");
	}

	return ret;
}

void hipcie_set_eyepattern_param(void *dev_data, char *buf)
{
	struct kirin_pcie *pcie = (struct kirin_pcie *)dev_data;
	u32 eye_diagram_param_ctrl2;
	u32 eye_diagram_param_ctrl3;
	char *buf_ctrl2;

	if (!pcie) {
		PCIE_PR_ERR("seteye: kirin_pcie is null\n");
		return;
	}
	buf_ctrl2 = strsep(&buf, ",");
	if (!buf_ctrl2 || !buf) {
		PCIE_PR_ERR("seteye: input param is not correct\n");
		return;
	}
	if (sscanf(buf, "%32x", &eye_diagram_param_ctrl3) != 1)
		return;
	if (sscanf(buf_ctrl2, "%32x", &eye_diagram_param_ctrl2) != 1)
		return;
	pcie->pcie_eye_param_ctrl2 = eye_diagram_param_ctrl2;
	pcie->pcie_eye_param_ctrl3 = eye_diagram_param_ctrl3;
}

/* cat eyepattern interface */
static int hipcie_eyepattern_param_show(struct seq_file *s, void *d)
{
	struct kirin_pcie *pcie = s->private;

	if (!pcie) {
		PCIE_PR_INFO("kirin_pcie NULL\n");
		seq_printf(s, "kirin_pcie NULL\n");
	} else {
		seq_printf(s, "0x%x,0x%x\n", pcie->pcie_eye_param_ctrl2, pcie->pcie_eye_param_ctrl3);
	}
	return 0;
}

int hipcie_debug_eyepattern_param_open(struct inode *inode, struct file *file)
{
	return single_open(file, hipcie_eyepattern_param_show, inode->i_private);
}

ssize_t hipcie_debug_eyepattern_param_read(struct file *file, char __user *buf, size_t size, loff_t *ppos)
{
	return seq_read(file, buf, size, ppos);
}

/* echo "xx" > eyepattern interface */
ssize_t hipcie_debug_eyepattern_param_write(struct file *file, const char __user *buf, size_t size, loff_t *ppos)
{
	void *pciedev = ((struct seq_file *)file->private_data)->private;
	char *_pcie_param_buf;

	_pcie_param_buf = kzalloc(PAGE_SIZE, GFP_KERNEL);
	if (!_pcie_param_buf) {
		PCIE_PR_ERR("alloc for _pcie_param_buf fail!");
		return -ENOMEM;
	}

	if (size >= PAGE_SIZE - 1) {
		PCIE_PR_ERR("set pcie eye param cmd too long!");
		kfree(_pcie_param_buf);
		return -ENOMEM;
	}

	if (copy_from_user(_pcie_param_buf, buf, size)) {
		PCIE_PR_ERR("[PCIE.ERROR] Can't get user data!");
		kfree(_pcie_param_buf);
		return -ENOSPC;
	}
	_pcie_param_buf[size] = '\0';

	hipcie_set_eyepattern_param(pciedev, _pcie_param_buf);
	kfree(_pcie_param_buf);

	return size;
}

int hipcie_debug_eyepattern_param_release(struct inode *inode, struct file *file)
{
	return single_release(inode, file);
}

/* eyepattern file ops */
static const struct file_operations hipcie_debug_eyepattern_fops = {
	.open = hipcie_debug_eyepattern_param_open,
	.read = hipcie_debug_eyepattern_param_read,
	.write = hipcie_debug_eyepattern_param_write,
	.release = hipcie_debug_eyepattern_param_release,
};

struct dentry *hipcie_debug_root;
void pcie_debug_init(void *dev_data)
{
#ifdef CONFIG_HISI_DEBUG_FS
	struct kirin_pcie* pcie = dev_data;
	struct device_node *dn = pcie->pp.dev->of_node;

	hipcie_debug_root = debugfs_create_dir(dn->full_name + 1, NULL);
	if (!hipcie_debug_root) {
		PCIE_PR_ERR("create debugfs dir fail");
		return;
	}
	debugfs_create_file("eyepattern", S_IWUSR | S_IRUSR, hipcie_debug_root, dev_data,
					&hipcie_debug_eyepattern_fops);
#endif
}
EXPORT_SYMBOL_GPL(pcie_debug_init);
#endif
