#include <linux/fcntl.h>

#define CLT_CAMERA_FILE_DIR "/data/data/camera"

#define CLT_CAMERA_FILE_NAME_SIZE 100

#define CLT_CAMERA_FILE_EEROR -1

static int read_info_from_file(void *inputAddr, int size, char *filename);

int load_capture_yuv_data(int camID, void *buffer, int buf_size, int width,
			  int height);

int load_preview_yuv_data(int camID, void *buffer, int buf_size, int width,
			  int height);
