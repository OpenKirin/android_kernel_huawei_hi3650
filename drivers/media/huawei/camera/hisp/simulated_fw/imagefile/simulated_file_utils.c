
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/unistd.h>
#include <linux/of.h>
#include <linux/uaccess.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/stddef.h>
#include "simulated_file_utils.h"
#include "../../../cam_log.h"

static int read_info_from_file(void *inputAddr, int size, char *filename)
{
	int rc = 0;
	unsigned int color_delta = 0x55;
	struct file *fp = NULL;
	loff_t pos;
	mm_segment_t fs;

	fp = filp_open(filename, O_RDONLY, 0);
	if (IS_ERR(fp)) {
		cam_info("create file: %s fail, fp is %d!\n", filename, fp);
		static unsigned char num;

		num = num + color_delta;
		memset(inputAddr, num, size);
		return CLT_CAMERA_FILE_EEROR;
	}

	pos = 0;
	fs = get_fs();
	set_fs(KERNEL_DS);
	vfs_read(fp, (const char __user *)inputAddr, size, &pos);

	filp_close(fp, NULL);
	set_fs(fs);

	return rc;
}

int load_capture_yuv_data(int camID, void *buffer, int buf_size, int width,
			  int height)
{
	char yuv_file[CLT_CAMERA_FILE_NAME_SIZE];

	snprintf(yuv_file, sizeof(yuv_file),
		 "%s/reprocess_%d_%d_%d.yuv", CLT_CAMERA_FILE_DIR, camID, width,
		 height);
	if (buffer == NULL || buf_size < 0) {
		cam_err("ERROR:input buffer parameter is wrong!\n");
		return CLT_CAMERA_FILE_EEROR;
	}
	if (NULL != yuv_file)
		return read_info_from_file(buffer, buf_size, yuv_file);
	cam_err("ERROR:load_capture_yuv_data is null!\n");
	return CLT_CAMERA_FILE_EEROR;
}

int load_preview_yuv_data(int camID, void *buffer, int buf_size, int width,
			  int height)
{
	char yuv_file[CLT_CAMERA_FILE_NAME_SIZE];

	snprintf(yuv_file, sizeof(yuv_file),
		 "%s/p_%d_%d_%d.yuv", CLT_CAMERA_FILE_DIR, width, height,
		 camID);
	if (buffer == NULL || buf_size < 0) {
		cam_err("ERROR:input buffer parameter is wrong!\n");
		return CLT_CAMERA_FILE_EEROR;
	}
	if (NULL != yuv_file)
		return read_info_from_file(buffer, buf_size, yuv_file);

	cam_err("ERROR:load_preview_yuv_data is null!\n");
	return CLT_CAMERA_FILE_EEROR;
}
