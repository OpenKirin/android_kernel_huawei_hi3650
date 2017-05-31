#include <linux/module.h>
#include <linux/types.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/version.h>
#include "inputhub_route.h"
#include "inputhub_bridge.h"
#include "sensor_info.h"
#include "sensor_debug.h"
#include "rdr_sensorhub.h"

#define MAX_CMD_BUF_ARGC (64)

extern volatile int vibrator_shake;
extern volatile int hall_value;
extern BH1745_ALS_PARA_TABLE als_para_diff_tp_color_table[];
extern APDS9251_ALS_PARA_TABLE apds_als_para_diff_tp_color_table[];
extern int rohm_rgb_flag;
extern int avago_rgb_flag;
extern int als_para_table;
extern struct als_platform_data als_data;
static time_t get_data_last_time;

extern struct sensorlist_info sensorlist_info[SENSOR_MAX];
static struct class *sensors_class;
struct t_sensor_debug_operations_list sensor_debug_operations_list = {
	.mlock = __MUTEX_INITIALIZER(sensor_debug_operations_list.mlock),
	.head = LIST_HEAD_INIT(sensor_debug_operations_list.head),
};

/*to find tag by str*/
static const struct sensor_debug_tag_map tag_map_tab[] = {
	{"accel", TAG_ACCEL},
	{"magnitic", TAG_MAG},
	{"gyro", TAG_GYRO},
	{"als_light", TAG_ALS},
	{"ps_promixy", TAG_PS},
	{"linear_accel", TAG_LINEAR_ACCEL},
	{"gravity", TAG_GRAVITY},
	{"orientation", TAG_ORIENTATION},
	{"rotationvector", TAG_ROTATION_VECTORS},
	{"maguncalibrated", TAG_MAG_UNCALIBRATED},
	{"gamerv", TAG_GAME_RV},
	{"gyrouncalibrated", TAG_GYRO_UNCALIBRATED},
	{"significantmotion", TAG_SIGNIFICANT_MOTION},
	{"stepdetector", TAG_STEP_DETECTOR},
	{"stepcounter", TAG_STEP_COUNTER},
	{"geomagnetic", TAG_GEOMAGNETIC_RV},
	{"airpress", TAG_PRESSURE},
	{"handpress", TAG_HANDPRESS},
	{"cap_prox", TAG_CAP_PROX},
	{"hall", TAG_HALL},
	{"fault", TAG_FAULT},
	{"ar", TAG_AR},
	{"fingersense", TAG_FINGERSENSE},
	{"fingerprint", TAG_FP},
	{"key", TAG_KEY},
	{"tiltdetector", TAG_TILT_DETECTOR},
};

static const char *fault_type_table[] = {
	"hardfault",
	"busfault",
	"memfault",
	"usagefault",
	"rdrdump",
};

static int open_sensor(int tag, int argv[], int argc)
{
	int ret = 0;
	if (-1 == tag)
		return -1;

	if (ap_sensor_enable(tag, true))
		return 0;

	hwlog_info("open sensor %d\n", tag);
	ret = inputhub_sensor_enable(tag, true);
	if (!ret && (argc > 0)) {
		hwlog_info("set sensor %d delay %d ms\n", tag, argv[0]);
		ret = inputhub_sensor_setdelay(tag, argv[0]);
	}

	return ret;
}

static int set_delay(int tag, int argv[], int argc)
{
	if (-1 == tag || 0 == argc)
		return -1;

	if (ap_sensor_setdelay(tag, argv[0]))
		return 0;

	hwlog_info("set sensor %d delay %d ms\n", tag, argv[0]);
	inputhub_sensor_setdelay(tag, argv[0]);

	return 0;
}

static int close_sensor(int tag, int argv[], int argc)
{
	if (-1 == tag)
		return -1;

	if (ap_sensor_enable(tag, false))
		return 0;

	hwlog_info("close sensor %d\n", tag);
	inputhub_sensor_enable(tag, false);

	return 0;
}

/********************************************
*This funciton is Only for Test:
*I2C address should be modified by virtual address. This virtual address is for Test.
*And Tools out can put data into system for simulating
**********************************************/
static int set_sensor_slave_addr(int tag, int argv[], int argc)
{
	write_info_t pkg_ap;
	read_info_t pkg_mcu;
	unsigned int i2c_address = 0;
	int ret = -1;

	if (argc == 0)
		return -1;

	i2c_address = argv[0] & 0xFF;
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));

	pkg_ap.tag = tag;
	pkg_ap.cmd = CMD_SET_SLAVE_ADDR_REQ;
	pkg_ap.wr_buf = &i2c_address;
	pkg_ap.wr_len = sizeof(i2c_address);

	hwlog_info("set_sensor_slave_addr, %s, i2c_addr:0x%x\n",
		   obj_tag_str[tag], i2c_address);

	ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
	if (ret != 0) {
		hwlog_err("set %s slave addr failed, ret = %d in %s\n",
			  obj_tag_str[tag], ret, __func__);
		return -1;
	}

	if (pkg_mcu.errno != 0) {
		hwlog_err("set %s slave addr failed errno = %d in %s\n",
			  obj_tag_str[tag], pkg_mcu.errno, __func__);
	} else {
		hwlog_info("set %s new slave addr:0x%x success\n",
			   obj_tag_str[tag], i2c_address);
	}

	return 0;
}

#define DEBUG_LEVEL 4
extern struct CONFIG_ON_DDR *pConfigOnDDr;

int set_log_level(int tag, int argv[], int argc)
{
	write_info_t pkg_ap;
	uint32_t log_level;
	int ret = -1;

	if (argc != 1)
		return -1;

	log_level = argv[0];

	if (log_level > DEBUG_LEVEL)
		return -1;

	memset(&pkg_ap, 0, sizeof(pkg_ap));

	pkg_ap.tag = TAG_SYS;
	pkg_ap.cmd = CMD_SYS_LOG_LEVEL_REQ;
	pkg_ap.wr_buf = &log_level;
	pkg_ap.wr_len = sizeof(log_level);

	ret = write_customize_cmd(&pkg_ap, NULL);
	if (ret != 0) {
		hwlog_err("%s faile to write cmd\n", __func__);
		return -1;
	}

	pConfigOnDDr->log_level = log_level;
	hwlog_info("%s set log level %d success\n", __func__,
			   log_level);

	return 0;
}

static int set_fault_type(int tag, int argv[], int argc)
{
	write_info_t pkg_ap;
	uint8_t fault_type = 0;
	int ret = -1;

	if (argc == 0)
		return -1;

	fault_type = argv[0] & 0xFF;

	if (fault_type >=
		(sizeof(fault_type_table)/sizeof(fault_type_table[0]))) {
		hwlog_err("unsupported fault_type : %d\n", fault_type);
		return -1;
	}

	memset(&pkg_ap, 0, sizeof(pkg_ap));

	pkg_ap.tag = TAG_FAULT;
	pkg_ap.cmd = CMD_SET_FAULT_TYPE_REQ;
	pkg_ap.wr_buf = &fault_type;
	pkg_ap.wr_len = sizeof(fault_type);

	hwlog_info("set_fault_type, %s, fault type:%s\n", obj_tag_str[TAG_FAULT],
		   fault_type_table[fault_type]);

	ret = write_customize_cmd(&pkg_ap, NULL);
	if (ret != 0) {
		hwlog_err("set fault type %s failed, ret = %d in %s\n",
			  fault_type_table[fault_type], ret, __func__);
		return -1;
	}

	hwlog_info("set fault type %s success\n", fault_type_table[fault_type]);

	return 0;
}

static int set_fault_addr(int tag, int argv[], int argc)
{
	write_info_t pkg_ap;
	int ret = -1;
	pkt_fault_addr_req_t cpkt;
	pkt_header_t *hd = (pkt_header_t *)&cpkt;

	if (argc == 0)
		return -1;

	memset(&pkg_ap, 0, sizeof(pkg_ap));

	pkg_ap.tag = TAG_FAULT;
	pkg_ap.cmd = CMD_SET_FAULT_ADDR_REQ;
	cpkt.wr = argv[0] & 0xFF;
	cpkt.fault_addr = argv[1];
	pkg_ap.wr_buf = &hd[1];
	pkg_ap.wr_len = 5;

	ret = write_customize_cmd(&pkg_ap, NULL);
	if (ret != 0) {
		hwlog_err
		    ("set fault addr, read/write: %d, 0x%x failed, ret = %d in %s\n",
		     argv[0], argv[1], ret, __func__);
		return -1;
	}

	hwlog_info("set fault addr,  read/write: %d, fault addr: 0x%x success\n",
	     argv[0], argv[1]);

	return 0;
}

/************************************************
*ar_test cmd core para1 para2
*cmd  1: enable 3:close 33:start 35:stop 37:update 39:flush
*core  0:ap 1:modem
*para1: 1/3/39 ignore 33/37/35/39:report interval
*para2: every bit mean a activity status, eg:0x3 is VEHICLE, RIDING
*************************************************/
static int ar_test(int tag, int argv[], int argc)
{
	write_info_t pkg_ap;
	read_info_t pkg_mcu;
	ar_start_cmd_t ar_start;
	ar_stop_cmd_t ar_stop;

	int ret = -1, i;
	unsigned char num = 0;
	unsigned char cmd = argv[0];
	unsigned char core = argv[1];
	unsigned int para1 = argv[2];
	unsigned int para2 = argv[3];

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	memset(&ar_start, 0, sizeof(ar_start));
	memset(&ar_stop, 0, sizeof(ar_stop));

	pkg_ap.tag = TAG_AR;

	if ((cmd == CMD_CMN_OPEN_REQ) || (cmd == CMD_CMN_CLOSE_REQ)) {
		pkg_ap.cmd = cmd;
		pkg_ap.wr_buf = NULL;
		pkg_ap.wr_len = 0;
	} else if ((cmd == CMD_FLP_AR_START_REQ)
		   || (cmd == CMD_FLP_AR_UPDATE_REQ)) {
		pkg_ap.cmd = CMD_CMN_CONFIG_REQ;
		ar_start.core_cmd.sub_cmd = cmd;
		ar_start.core_cmd.core = core;
		if (para1 > UINT_MAX / 1000) {
			ar_start.start_param.report_interval = UINT_MAX;
		} else {
			ar_start.start_param.report_interval = para1 * 1000;
		}
		for (i = 0; i <= AR_UNKNOWN; i++){
			if ((i > AR_ACTIVITY_TILT && i < AR_VE_BUS) || i > AR_FAST_WALK){
				continue;
			}
			else if (1 == ((para2 & (1 << i)) ? 1:0)){
				ar_start.start_param.activity_list[num].activity = i;
				ar_start.start_param.activity_list[num].event_type = EVENT_BOTH;
				num++;
			}
			if (num > AR_MAX_CONFIG_NUM){
				num = AR_MAX_CONFIG_NUM;
				break;
			}
		}
		hwlog_info("receive activity num %d in %s\n", num, __func__);
		pkg_ap.wr_buf = &ar_start;
		pkg_ap.wr_len = sizeof(ar_start.core_cmd) + sizeof(ar_start.start_param.report_interval) + sizeof(ar_config_event_t) * num;
	} else if ((cmd == CMD_FLP_AR_STOP_REQ)
		   || (cmd == CMD_FLP_AR_FLUSH_REQ)) {
		pkg_ap.cmd = CMD_CMN_CONFIG_REQ;
		ar_stop.core_cmd.sub_cmd = cmd;
		ar_stop.core_cmd.core = core;
		if (para1 > UINT_MAX / 1000) {
			ar_stop.para = UINT_MAX;
		} else {
			ar_stop.para = para1 * 1000;
		}
		pkg_ap.wr_buf = &ar_stop;
		pkg_ap.wr_len = sizeof(ar_stop);
	} else {
		hwlog_err("error command in ar_test, cmd=%d\n", cmd);
		return -1;
	}

	ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
	if (ret) {
		hwlog_err("send ar cmd to mcu fail,ret=%d\n", ret);
		return ret;
	}
	if (pkg_mcu.errno != 0) {
		hwlog_err("set ar cmd fail cmd=%d core=%d para1=0x%x para2=0x%x\n", cmd, core,
			  para1, para2);
	} else {
		hwlog_info("set ar cmd success cmd=%d core=%d para1=0x%x para2=0x%x\n",
			   cmd, core, para1, para2);
	}

	return 0;
}

bool find_and_do_cmd(int tag, struct sensor_debug_search_info *tab, int size,
		     int (*op) (struct sensor_debug_search_info *info))
{
	int i;

	if (NULL == tab || NULL == op) {
		hwlog_err("NULL pointer in %s\n", __func__);
		return false;
	}

	for (i = 0; i < size; ++i) {
		if (tag == tab[i].tag) {
			op(&tab[i]);
			break;
		}
	}

	return (i != size);
}

int register_sensorhub_debug_operation(const char *func_name,
				       sensor_debug_pfunc op)
{
	struct sensor_debug_cmd *node = NULL, *n = NULL;
	int ret = 0;

	if (NULL == func_name || NULL == op) {
		hwlog_err("error in %s\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&sensor_debug_operations_list.mlock);
	list_for_each_entry_safe(node, n, &sensor_debug_operations_list.head,
				 entry) {
		if (op == node->operation) {
			hwlog_warn("%s has already registed in %s\n!",
				   func_name, __func__);
			goto out;	/*return when already registed*/
		}
	}

	node = kzalloc(sizeof(*node), GFP_ATOMIC);
	if (NULL == node) {
		hwlog_err("alloc failed in %s\n", __func__);
		ret = -ENOMEM;
		goto out;
	}
	node->str = func_name;
	node->operation = op;
	list_add_tail(&node->entry, &sensor_debug_operations_list.head);

out:
	mutex_unlock(&sensor_debug_operations_list.mlock);

	return ret;
}

int unregister_sensorhub_debug_operation(sensor_debug_pfunc op)
{
	struct sensor_debug_cmd *pos = NULL, *n = NULL;

	if (NULL == op) {
		hwlog_err("error in %s\n", __func__);
		return -EINVAL;
	}

	mutex_lock(&sensor_debug_operations_list.mlock);
	list_for_each_entry_safe(pos, n, &sensor_debug_operations_list.head,
				 entry) {
		if (op == pos->operation) {
			list_del(&pos->entry);
			kfree(pos);
			break;
		}
	}
	mutex_unlock(&sensor_debug_operations_list.mlock);

	return 0;
}

static void register_my_debug_operations(void)
{
	REGISTER_SENSORHUB_DEBUG_OPERATION(open_sensor);
	REGISTER_SENSORHUB_DEBUG_OPERATION(set_delay);
	REGISTER_SENSORHUB_DEBUG_OPERATION(close_sensor);
	REGISTER_SENSORHUB_DEBUG_OPERATION(set_sensor_slave_addr);
	REGISTER_SENSORHUB_DEBUG_OPERATION(set_fault_type);
	REGISTER_SENSORHUB_DEBUG_OPERATION(set_fault_addr);
	REGISTER_SENSORHUB_DEBUG_OPERATION(set_log_level);
	REGISTER_SENSORHUB_DEBUG_OPERATION(ar_test);
}

static inline bool is_space_ch(char ch)
{
	return (' ' == ch) || ('\t' == ch);
}

static inline bool end_of_string(char ch)
{
	bool ret = false;
	switch (ch) {
	case '\0':
	case '\r':
	case '\n':
		ret = true;
		break;

	default:
		ret = false;
		break;
	}

	return ret;
}

/*find first pos*/
static const char *get_str_begin(const char *cmd_buf)
{
	if (NULL == cmd_buf)
		return NULL;

	while (is_space_ch(*cmd_buf))
		++cmd_buf;

	if (end_of_string(*cmd_buf))
		return NULL;

	return cmd_buf;
}

/*find last pos*/
static const char *get_str_end(const char *cmd_buf)
{
	if (NULL == cmd_buf)
		return NULL;

	while (!is_space_ch(*cmd_buf) && !end_of_string(*cmd_buf))
		++cmd_buf;

	return cmd_buf;
}

/*fuzzy matching*/
static bool str_fuzzy_match(const char *cmd_buf, const char *target)
{
	if (NULL == cmd_buf || NULL == target)
		return false;

	for (; !is_space_ch(*cmd_buf) && !end_of_string(*cmd_buf) && *target;
	     ++target) {
		if (*cmd_buf == *target) {
			++cmd_buf;
		}
	}

	return is_space_ch(*cmd_buf) || end_of_string(*cmd_buf);
}

static sensor_debug_pfunc get_operation(const char *str)
{
	sensor_debug_pfunc op = NULL;
	struct sensor_debug_cmd *node = NULL, *n = NULL;

	mutex_lock(&sensor_debug_operations_list.mlock);
	list_for_each_entry_safe(node, n, &sensor_debug_operations_list.head,
				 entry) {
		if (str_fuzzy_match(str, node->str)) {
			op = node->operation;
			break;
		}
	}
	mutex_unlock(&sensor_debug_operations_list.mlock);

	return op;
}

static int get_sensor_tag(const char *str)
{
	int i;
	for (i = 0; i < sizeof(tag_map_tab) / sizeof(tag_map_tab[0]); ++i) {
		if (str_fuzzy_match(str, tag_map_tab[i].str)) {
			return tag_map_tab[i].tag;
		}
	}
	return -1;
}

#define CH_IS_DIGIT(ch) ('0' <= (ch) && (ch) <= '9')
#define CH_IS_HEX(ch) (('A' <= (ch) && (ch) <= 'F') || ('a' <= (ch) && (ch) <= 'f'))
#define CH_IS_HEXDIGIT(ch) (CH_IS_DIGIT(ch) || CH_IS_HEX(ch))
static bool get_arg(const char *str, int *arg)
{
	int val = 0;
	bool neg = false;
	bool hex = false;

	if ('-' == *str) {
		++str;
		neg = true;
	}

	if (('0' == *str) && (('x' == *(str + 1)) || ('X' == *(str + 1)))) {
		str += 2;
		hex = true;
	}

	if (hex) {
		for (; !is_space_ch(*str) && !end_of_string(*str); ++str) {
			if (!CH_IS_HEXDIGIT(*str)) {
				return false;
			}
			val <<= 4;
			val |=
			    (CH_IS_DIGIT(*str) ? (*str - '0')
			     : (((*str | 0x20) - 'a') + 10));
		}
	} else {
		for (; !is_space_ch(*str) && !end_of_string(*str); ++str) {
			if (!CH_IS_DIGIT(*str)) {
				return false;
			}
			val *= 10;
			val += *str - '0';
		}
	}

	*arg = neg ? -val : val;
	return true;
}

static void parse_str(const char *cmd_buf)
{
	sensor_debug_pfunc operation = NULL;
	int tag = -1;
	int arg = -1;
	int argv[MAX_CMD_BUF_ARGC] = { 0 };
	int argc = 0;

	for (; (cmd_buf = get_str_begin(cmd_buf)) != NULL;
	     cmd_buf = get_str_end(cmd_buf)) {
		if (NULL == operation)
			operation = get_operation(cmd_buf);

		if (-1 == tag)
			tag = get_sensor_tag(cmd_buf);

		if (get_arg(cmd_buf, &arg)) {
			if (argc < MAX_CMD_BUF_ARGC) {
				argv[argc++] = arg;
			} else {
				hwlog_err("too many args, %d will be ignored\n",
					  arg);
			}
		}
	}

	if (operation != NULL)
		operation(tag, argv, argc);
}

static ssize_t cls_attr_debug_show_func(struct class *cls,
					struct class_attribute *attr, char *buf)
{
	int i = 0;
	unsigned int offset = 0;
	struct sensor_debug_cmd *node = NULL, *n = NULL;

	offset += sprintf(buf + offset,
		    "operations format:\necho operation+tag+optarg > %s\n",
		    attr->attr.name);
	offset += sprintf(buf + offset,
		    "for example:\nto open accel we input: echo open_sensor accel > %s\n",
		    attr->attr.name);
	offset += sprintf(buf + offset,
		    "to setdelay accel 100 ms we input: echo set_delay accel 100 > %s\n",
		    attr->attr.name);

	offset += sprintf(buf + offset, "\noperations supported as follow:\n");
	mutex_lock(&sensor_debug_operations_list.mlock);
	list_for_each_entry_safe(node, n, &sensor_debug_operations_list.head,
				 entry) {
		offset += sprintf(buf + offset, "%s\n", node->str);
	}
	mutex_unlock(&sensor_debug_operations_list.mlock);

	offset += sprintf(buf + offset, "\ntags supported as follow:\n");
	for (i = 0; i < sizeof(tag_map_tab) / sizeof(tag_map_tab[0]); ++i) {
		offset += sprintf(buf + offset, "%s\n", tag_map_tab[i].str);
	}

	return offset;
}

static ssize_t cls_attr_debug_store_func(struct class *cls,
					 struct class_attribute *attr,
					 const char *buf, size_t size)
{
	parse_str(buf);
	return size;
}

static CLASS_ATTR(sensorhub_dbg, 0660, cls_attr_debug_show_func,
		  cls_attr_debug_store_func);

static ssize_t cls_attr_dump_show_func(struct class *cls,
				       struct class_attribute *attr, char *buf)
{
	hwlog_info("read sensorhub_dump node, IOM7 will restart\n");
	iom3_need_recovery(SENSORHUB_USER_MODID, SH_FAULT_USER_DUMP);
	return snprintf(buf, MAX_STR_SIZE,
			"read sensorhub_dump node, IOM7 will restart\n");
}

static CLASS_ATTR(sensorhub_dump, 0660, cls_attr_dump_show_func, NULL);

static ssize_t cls_attr_kernel_support_lib_ver_show_func(struct class *cls,
							 struct class_attribute
							 *attr, char *buf)
{
	uint32_t ver = 14;
	hwlog_info("read cls_attr_kernel_support_lib_ver_show_func %d\n", ver);
	memcpy(buf, &ver, sizeof(ver));
	return sizeof(ver);
}

static CLASS_ATTR(libsensor_ver, 0660,
		  cls_attr_kernel_support_lib_ver_show_func, NULL);

static void sensorhub_debug_init(void)
{
	if (class_create_file(sensors_class, &class_attr_sensorhub_dbg))
		hwlog_err("create files failed in %s\n", __func__);

	if (class_create_file(sensors_class, &class_attr_sensorhub_dump))
		hwlog_err("create files sensorhub_dump in %s\n", __func__);

	if (class_create_file(sensors_class, &class_attr_libsensor_ver))
		hwlog_err("create files libsensor_ver in %s\n", __func__);

	register_my_debug_operations();
}

#define CHECK_SENSOR_COOKIE(data) \
do {\
	if (NULL == data || (!(TAG_SENSOR_BEGIN <= data->tag && data->tag < TAG_SENSOR_END)) || (NULL == data->name)) {\
		hwlog_err("error in %s\n", __func__);\
		return -EINVAL;\
	} \
} while (0)

static ssize_t show_enable(struct device *dev,
			   struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);
	return snprintf(buf, MAX_STR_SIZE, "%d\n",
			sensor_status.status[data->tag]);
}

static ssize_t store_enable(struct device *dev, struct device_attribute *attr,
			    const char *buf, size_t size)
{
	unsigned long val = 0;
	int ret = -1;
	write_info_t pkg_ap;
	read_info_t pkg_mcu;
	const char *operation = NULL;

	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	if (ap_sensor_enable(data->tag, (1 == val)))
		return size;

	operation = ((1 == val) ? "enable" : "disable");
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	pkg_ap.tag = data->tag;
	pkg_ap.cmd = (1 == val) ? CMD_CMN_OPEN_REQ : CMD_CMN_CLOSE_REQ;
	pkg_ap.wr_buf = NULL;
	pkg_ap.wr_len = 0;
	ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
	if (ret != 0) {
		hwlog_err("%s %s failed, ret = %d in %s\n", operation,
			  data->name, ret, __func__);
		return size;
	}

	if (pkg_mcu.errno != 0) {
		hwlog_err("%s %s failed errno = %d in %s\n", operation,
			  data->name, pkg_mcu.errno, __func__);
	} else {
		hwlog_info("%s %s success\n", operation, data->name);
	}

	return size;
}

static ssize_t show_set_delay(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);
	return snprintf(buf, MAX_STR_SIZE, "%d\n",
			sensor_status.delay[data->tag]);
}

static ssize_t store_set_delay(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t size)
{
	unsigned long val = 0;
	int ret = 0;
	write_info_t pkg_ap;
	read_info_t pkg_mcu;

	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	if (ap_sensor_setdelay(data->tag, val))
		return size;

	if (val >= 10 && val <= 1000) {	/*range [10, 1000]*/
		pkg_ap.tag = data->tag;
		pkg_ap.cmd = CMD_CMN_INTERVAL_REQ;
		pkg_ap.wr_buf = &val;
		pkg_ap.wr_len = sizeof(val);
		ret = write_customize_cmd(&pkg_ap, &pkg_mcu);
		if (ret != 0) {
			hwlog_err("set %s delay cmd to mcu fail, ret = %d in %s\n",
			     data->name, ret, __func__);
			return ret;
		}
		if (pkg_mcu.errno != 0) {
			hwlog_err("set %s delay failed errno %d in %s\n",
				  data->name, pkg_mcu.errno, __func__);
			return -EINVAL;
		} else {
			hwlog_info("set %s delay (%ld)success\n", data->name,
				   val);
		}
	} else {
		hwlog_err("set %s delay_ms %d ms range error in %s\n",
			  data->name, (int)val, __func__);
		return -EINVAL;
	}

	return size;
}

static ssize_t show_info(struct device *dev,
			 struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return snprintf(buf, MAX_STR_SIZE, "%s\n",
			get_sensor_info_by_tag(data->tag));
}

static ssize_t show_get_data(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	{
		struct t_sensor_get_data *get_data =
		    &sensor_status.get_data[data->tag];
		unsigned int offset = 0;
		int i = 0, mem_num = 0;

		atomic_set(&get_data->reading, 1);
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 13, 0))
		INIT_COMPLETION(get_data->complete);
#else
		reinit_completion(&get_data->complete);
#endif
		if (0 == wait_for_completion_interruptible(&get_data->complete)) {/*return -ERESTARTSYS if interrupted, 0 if completed.*/
			for (mem_num =
			     get_data->data.length /
			     sizeof(get_data->data.value[0]); i < mem_num;
			     i++) {
				offset +=
				    sprintf(buf + offset, "%d\t",
					    get_data->data.value[i]);
			}
			offset += sprintf(buf + offset, "\n");
		}

		return offset;
	}

	return 0;
}

static ssize_t store_get_data(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t size)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	{
		struct timeval tv;
		struct sensor_data event;
		int arg;
		int argc = 0;
		time_t get_data_current_time;

		memset(&tv, 0, sizeof(struct timeval));
		do_gettimeofday(&tv);
		get_data_current_time = tv.tv_sec;
		if((get_data_current_time - get_data_last_time) < 1){
			hwlog_info("%s:time interval is less than 1s(from %u to %u), skip\n",
				__func__,get_data_last_time,get_data_current_time);
			return size;
		}
		get_data_last_time = get_data_current_time;

		/*parse cmd buffer*/
		for (; (buf = get_str_begin(buf)) != NULL;
		     buf = get_str_end(buf)) {
			if (get_arg(buf, &arg)) {
				if (argc <
				    (sizeof(event.value) /
				     sizeof(event.value[0]))) {
					event.value[argc++] = arg;
				} else {
					hwlog_err
					    ("too many args, %d will be ignored\n",
					     arg);
				}
			}
		}

		/*fill sensor event and write to sensor event buffer*/
		report_sensor_event(data->tag, event.value,
				    sizeof(event.value[0]) * argc);
	}

	return size;
}

static ssize_t show_selftest(struct device *dev,
			     struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);
	return snprintf(buf, MAX_STR_SIZE, "%s\n",
			sensor_status.selftest_result[data->tag]);
}

static ssize_t store_selftest(struct device *dev, struct device_attribute *attr,
			      const char *buf, size_t size)
{
	unsigned long val = 0;
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	if (strict_strtoul(buf, 10, &val))
		return -EINVAL;

	if (1 == val) {
		pkt_header_t pkt;
		pkt_header_resp_t resp_pkt;

		pkt.tag = data->tag;
		pkt.cmd = CMD_SELFTEST_REQ;
		pkt.resp = RESP;
		pkt.length = 0;
		if (0 == WAIT_FOR_MCU_RESP_DATA_AFTER_SEND(&pkt,
							   inputhub_mcu_write_cmd
							   (&pkt, sizeof(pkt)),
							   4000, &resp_pkt,
							   sizeof(resp_pkt))) {
			hwlog_err("wait for %s selftest timeout\n", data->name);
			memcpy(sensor_status.selftest_result[data->tag], "1", 2);/*flyhorse k : SUC-->"0", OTHERS-->"1"*/
			return size;
		} else {
			if (resp_pkt.errno != 0) {
				hwlog_err("%s selftest fail\n", data->name);
				memcpy(sensor_status.selftest_result[data->tag],
				       "1", 2);
			} else {
				hwlog_info("%s selftest success\n", data->name);
				memcpy(sensor_status.selftest_result[data->tag],
				       "0", 2);
			}
		}
	}

	return size;
}

static ssize_t show_read_airpress(struct device *dev,
				  struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return show_sensor_read_airpress_common(dev, attr, buf);
}

static ssize_t show_calibrate(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return sensors_calibrate_show(data->tag, dev, attr, buf);
}

static ssize_t store_calibrate(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t size)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return sensors_calibrate_store(data->tag, dev, attr, buf, size);
}

/***************************************************************
* modify als para online
* als pattern : vendor1--bh1745,  vendor2-- apds9251
* step 1:   write data to node in ap. eg:echo xx,xx, ... xx  >  /sys/class/sensors/als_debug_data
* step 2:   reboot sensorhub. eg: echo 1 > /sys/devices/platform/huawei_sensor/iom3_recovery
* then sensorhub restart and read als parameter into itself. so als para refreshed.
****************************************************************/
static ssize_t show_als_debug_data(struct device *dev,
			      struct device_attribute *attr, char *buf)
{
	unsigned long als_debug_para[8]={0,0,0,0,0,0,0,0};

	hwlog_info("%s: show cofficient.\n", __FUNCTION__);

	if (rohm_rgb_flag == 1) { //bh745_para
		als_debug_para[0] = als_para_diff_tp_color_table[als_para_table].bh745_para[0];//cofficient_judge
		als_debug_para[1] = als_para_diff_tp_color_table[als_para_table].bh745_para[1];//cofficient_red[0]
		als_debug_para[2] = als_para_diff_tp_color_table[als_para_table].bh745_para[3];//cofficient_green[0]
		als_debug_para[3] = als_para_diff_tp_color_table[als_para_table].bh745_para[2];//cofficient_red[1]
		als_debug_para[4] = als_para_diff_tp_color_table[als_para_table].bh745_para[4];//cofficient_green[1]
		hwlog_info("%s:rohm_rgb_flag is true and als_para_table=%d.\n", __FUNCTION__,als_para_table);
	}
	else if (avago_rgb_flag == 1) { //apds251_para
		als_debug_para[1] = apds_als_para_diff_tp_color_table[als_para_table].apds251_para[9];//avago_cofficient[1]
		als_debug_para[2] = apds_als_para_diff_tp_color_table[als_para_table].apds251_para[10];//avago_cofficient[2]
		als_debug_para[3] = apds_als_para_diff_tp_color_table[als_para_table].apds251_para[20];//avago_cofficient[3]
		als_debug_para[4] = apds_als_para_diff_tp_color_table[als_para_table].apds251_para[2];//LUX_P
		als_debug_para[5] = apds_als_para_diff_tp_color_table[als_para_table].apds251_para[4];//LUX_R
		als_debug_para[6] = apds_als_para_diff_tp_color_table[als_para_table].apds251_para[3];//LUX_Q
		als_debug_para[7] = apds_als_para_diff_tp_color_table[als_para_table].apds251_para[19];//lux_mix
		hwlog_info("%s:avago_rgb_flag is true and als_para_table=%d.\n", __FUNCTION__,als_para_table);
	}

	return snprintf(buf, 128, "%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld\n", als_debug_para[0],als_debug_para[1],als_debug_para[2],
			   als_debug_para[3],als_debug_para[4],als_debug_para[5],als_debug_para[6],als_debug_para[7]);

}

static ssize_t store_als_debug_data(struct device *dev,
			       struct device_attribute *attr, const char *buf,
			       size_t size)
{
	int als_manufactor = 0;
	unsigned long als_debug_para[8]={0,0,0,0,0,0,0,0};

	if (sscanf(buf,"%ld,%ld,%ld,%ld,%ld,%ld,%ld,%ld",&als_debug_para[0],&als_debug_para[1],&als_debug_para[2],\
		           &als_debug_para[3],&als_debug_para[4],&als_debug_para[5],&als_debug_para[6],&als_debug_para[7])){
		hwlog_info("%s: get parameter success.\n", __FUNCTION__);
	}
	else{
		hwlog_info("%s: get parameter fail.\n", __FUNCTION__);
	}

	if (rohm_rgb_flag == 1) { //bh745_para
		als_para_diff_tp_color_table[als_para_table].bh745_para[0]=als_debug_para[0];//cofficient_judge
		als_para_diff_tp_color_table[als_para_table].bh745_para[1]=als_debug_para[1];//cofficient_red[0]
		als_para_diff_tp_color_table[als_para_table].bh745_para[3]=als_debug_para[2];//cofficient_green[0]
		als_para_diff_tp_color_table[als_para_table].bh745_para[2]=als_debug_para[3];//cofficient_red[1]
		als_para_diff_tp_color_table[als_para_table].bh745_para[4]=als_debug_para[4];//cofficient_green[1]
		hwlog_info("%s:rohm_rgb_flag is true and als_para_table=%d.\n", __FUNCTION__,als_para_table);
		memcpy(als_data.als_extend_data, als_para_diff_tp_color_table[als_para_table].bh745_para,
			sizeof(als_para_diff_tp_color_table[als_para_table].bh745_para)>SENSOR_PLATFORM_EXTEND_DATA_SIZE?SENSOR_PLATFORM_EXTEND_DATA_SIZE:sizeof(als_para_diff_tp_color_table[als_para_table].bh745_para));
	}
	else if (avago_rgb_flag == 1) {//apds251_para
		apds_als_para_diff_tp_color_table[als_para_table].apds251_para[9]= als_debug_para[1];//avago_cofficient[1]
		apds_als_para_diff_tp_color_table[als_para_table].apds251_para[10]= als_debug_para[2];//avago_cofficient[2]
		apds_als_para_diff_tp_color_table[als_para_table].apds251_para[20]= als_debug_para[3];//avago_cofficient[3]
		apds_als_para_diff_tp_color_table[als_para_table].apds251_para[2]= als_debug_para[4];//LUX_P
		apds_als_para_diff_tp_color_table[als_para_table].apds251_para[4]= als_debug_para[5];//LUX_R
		apds_als_para_diff_tp_color_table[als_para_table].apds251_para[3]= als_debug_para[6];//LUX_Q
		apds_als_para_diff_tp_color_table[als_para_table].apds251_para[19]= als_debug_para[7];//lux_mix
		hwlog_info("%s:avago_rgb_flag is true and als_para_table=%d.\n", __FUNCTION__,als_para_table);
		memcpy(als_data.als_extend_data, apds_als_para_diff_tp_color_table[als_para_table].apds251_para,
			sizeof(apds_als_para_diff_tp_color_table[als_para_table].apds251_para)>SENSOR_PLATFORM_EXTEND_DATA_SIZE?SENSOR_PLATFORM_EXTEND_DATA_SIZE:sizeof(apds_als_para_diff_tp_color_table[als_para_table].apds251_para));
	}

	return size;

}

static ssize_t show_selftest_timeout(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return snprintf(buf, MAX_STR_SIZE, "%d\n", 3000);	/*ms*/
}

static ssize_t show_calibrate_timeout(struct device *dev,
				      struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return snprintf(buf, MAX_STR_SIZE, "%d\n", 3000);	/*ms*/
}

static ssize_t show_calibrate_method(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return show_mag_calibrate_method(dev, attr, buf);	/*none:0, DOE:1, DOEaG:2*/
}
static ssize_t show_cap_prox_calibrate_type(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return show_cap_prox_calibrate_method(dev, attr, buf);	/*non auto:0, auto:1*/
}
static ssize_t show_cap_prox_calibrate_order(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct sensor_cookie *data =
	    (struct sensor_cookie *)dev_get_drvdata(dev);
	CHECK_SENSOR_COOKIE(data);

	return show_cap_prox_calibrate_orders(dev, attr, buf);
}
static ssize_t store_fingersense_enable(struct device *dev,
					struct device_attribute *attr,
					const char *buf, size_t size)
{
	unsigned long val = 0;
	int ret = -1;

	if (strict_strtoul(buf, 10, &val)) {
		hwlog_err("%s: finger sense enable val(%lu) invalid",
			  __FUNCTION__, val);
		return -EINVAL;
	}

	hwlog_info("%s: finger sense enable val (%ld)\n", __FUNCTION__, val);
	if ((val != 0) && (val != 1)) {
		hwlog_err("%s:finger sense set enable fail, invalid val\n",
			  __FUNCTION__);
		return size;
	}

	if (fingersense_enabled == val) {
		hwlog_info("%s:finger sense already at seted state\n",
			   __FUNCTION__);
		return size;
	}

	hwlog_info("%s: finger sense set enable\n", __FUNCTION__);
	ret = fingersense_enable(val);
	if (ret) {
		hwlog_err("%s: finger sense enable fail: %d \n", __FUNCTION__,
			  ret);
		return size;
	}
	fingersense_enabled = val;

	return size;
}

static ssize_t show_fingersense_enable(struct device *dev,
				       struct device_attribute *attr,
				       const char *buf, size_t size)
{
	return snprintf(buf, MAX_STR_SIZE, "%d\n", fingersense_enabled);
}

static ssize_t show_fingersense_data_ready(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf, size_t size)
{
	return snprintf(buf, MAX_STR_SIZE, "%d\n", fingersense_data_ready);
}

static ssize_t show_fingersense_latch_data(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf, size_t size)
{
	int i = 0;
	size = min(size, sizeof(fingersense_data));

	if ((!fingersense_data_ready)
	    || (!fingersense_enabled)) {
		hwlog_err
		    ("%s:fingersense zaxix not ready(%d) or not enable(%d)\n",
		     __FUNCTION__, fingersense_data_ready, fingersense_enabled);
		return size;
	}

	memcpy(buf, (char *)fingersense_data, size);

	return size;
}

static ssize_t store_fingersense_req_data(struct device *dev,
					  struct device_attribute *attr,
					  const char *buf, size_t size)
{
	int ret = -1;
	unsigned int cmd = CMD_CMN_CONFIG_REQ;
	unsigned int sub_cmd = CMD_ACCEL_FINGERSENSE_REQ_DATA_REQ;

#if defined(CONFIG_HISI_VIBRATOR)
	if ((vibrator_shake == 1) || (HALL_COVERD & hall_value)) {
		hwlog_err
		    ("coverd, vibrator shaking, not send fingersense req data cmd to mcu\n");
		return -1;
	}
#endif

	if (!fingersense_enabled) {
		hwlog_err("%s: finger sense not enable,  dont req data\n",
			  __FUNCTION__);
		return size;
	}

	fingersense_data_ready = false;
	ret = fingersense_commu(cmd, sub_cmd, RESP);
	if (ret) {
		hwlog_err("%s: finger sense send requst data failed\n",
			  __FUNCTION__);
		return size;
	}

	return size;
}

static ssize_t show_ois_ctrl(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	return snprintf(buf, MAX_STR_SIZE, "%d\n",
				sensor_status.gyro_ois_status);
}

static ssize_t store_ois_ctrl(struct device *dev,
					   struct device_attribute *attr,
					   const char *buf, size_t size)
{
	int source = 0, ret = 0, i = 0;
	unsigned int cmd = 0;
	unsigned int delay = 200;
	write_info_t pkg_ap;
	read_info_t pkg_mcu;
	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	source = simple_strtol(buf, NULL, 10);

	if (1 == source) {
		cmd = CMD_CMN_OPEN_REQ;
		ret = ois_commu(TAG_OIS, cmd, source, NO_RESP);
		if (ret) {
			hwlog_err("%s: ois open gyro fail\n",
				  __FUNCTION__);
			return size;
		}

		cmd = CMD_CMN_INTERVAL_REQ;
		ret = ois_commu(TAG_OIS, cmd, delay, NO_RESP);
		if (ret) {
			hwlog_err("%s: set delay fail\n", __FUNCTION__);
			return size;
		}

		cmd = CMD_GYRO_OIS_REQ;
		ret = ois_commu(TAG_GYRO, cmd, source, RESP);
		if (ret) {
			hwlog_err("%s: ois enable fail\n", __FUNCTION__);
			return size;
		}
		hwlog_info("%s:ois enable succsess\n", __FUNCTION__);
	} else {
		cmd = CMD_GYRO_OIS_REQ;
		ret = ois_commu(TAG_GYRO, cmd, source, RESP);
		if (ret) {
			hwlog_err("%s:ois close fail\n", __FUNCTION__);
			return size;
		}

		cmd = CMD_CMN_CLOSE_REQ;
		ret = ois_commu(TAG_OIS, cmd, source, NO_RESP);
		if (ret) {
			hwlog_err("%s: ois close gyro fail\n",
				  __FUNCTION__);
			return size;
		}
		hwlog_info("%s:ois close succsess\n", __FUNCTION__);
	}
	return size;
}

/*files create for every sensor*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 13, 0))
DEVICE_ATTR(enable, 0660, show_enable, store_enable);
DEVICE_ATTR(set_delay, 0660, show_set_delay, store_set_delay);
DEVICE_ATTR(info, 0440, show_info, NULL);
DEVICE_ATTR(get_data, 0660, show_get_data, store_get_data);

static struct attribute *sensors_attributes[] = {
	&dev_attr_enable.attr,
	&dev_attr_set_delay.attr,
	&dev_attr_info.attr,
	&dev_attr_get_data.attr,
	NULL,
};
static const struct attribute_group sensors_attr_group = {
	.attrs = sensors_attributes,
};
static const struct attribute_group sensors_attr_groups[] = {
	&sensors_attr_group,
	NULL,
};
#else
static struct device_attribute sensors_class_attrs[] = {
	__ATTR(enable, 0660, show_enable, store_enable),
	__ATTR(set_delay, 0660, show_set_delay, store_set_delay),
	__ATTR(info, 0440, show_info, NULL),
	__ATTR(get_data, 0660, show_get_data, store_get_data),
	__ATTR_NULL,
};
#endif

/*files create for specific sensor*/
static DEVICE_ATTR(self_test, 0660, show_selftest, store_selftest);
static DEVICE_ATTR(self_test_timeout, 0440, show_selftest_timeout, NULL);
static DEVICE_ATTR(read_airpress, 0440, show_read_airpress, NULL);	/*only for airpress*/
static DEVICE_ATTR(set_calidata, 0660, show_calibrate, store_calibrate);	/*only for airpress*/
static DEVICE_ATTR(calibrate, 0660, show_calibrate, store_calibrate);
static DEVICE_ATTR(als_debug_data, 0660, show_als_debug_data, store_als_debug_data);
static DEVICE_ATTR(calibrate_timeout, 0440, show_calibrate_timeout, NULL);
static DEVICE_ATTR(calibrate_method, 0440, show_calibrate_method, NULL);	/*only for magnetic*/
static DEVICE_ATTR(cap_prox_calibrate_type, 0440, show_cap_prox_calibrate_type, NULL);	/*only for magnetic*/
static DEVICE_ATTR(cap_prox_calibrate_order, 0440, show_cap_prox_calibrate_order, NULL);


static DEVICE_ATTR(set_fingersense_enable, 0660, show_fingersense_enable,
		   store_fingersense_enable);
static DEVICE_ATTR(fingersense_data_ready, 0440, show_fingersense_data_ready,
		   NULL);
static DEVICE_ATTR(fingersense_latch_data, 0440, show_fingersense_latch_data,
		   NULL);
static DEVICE_ATTR(fingersense_req_data, 0220, NULL,
		   store_fingersense_req_data);
static DEVICE_ATTR(ois_ctrl, 0660, show_ois_ctrl, store_ois_ctrl);

static ssize_t show_acc_sensorlist_info(struct device *dev,
					  struct device_attribute *attr,
					  char *buf)
{
	memcpy(buf, &sensorlist_info[ACC], sizeof(struct sensorlist_info));
	return sizeof(struct sensorlist_info);
}
static DEVICE_ATTR(acc_sensorlist_info, 0664, show_acc_sensorlist_info,
		   NULL);

static ssize_t show_mag_sensorlist_info(struct device *dev,
					  struct device_attribute *attr, char *buf)
{
	memcpy(buf, &sensorlist_info[MAG], sizeof(struct sensorlist_info));
	return sizeof(struct sensorlist_info);
}
static DEVICE_ATTR(mag_sensorlist_info, 0664, show_mag_sensorlist_info, NULL);

static ssize_t show_gyro_sensorlist_info(struct device *dev,
					  struct device_attribute *attr, char *buf)
{
	memcpy(buf, &sensorlist_info[GYRO], sizeof(struct sensorlist_info));
	return sizeof(struct sensorlist_info);
}
static DEVICE_ATTR(gyro_sensorlist_info, 0664, show_gyro_sensorlist_info, NULL);

static ssize_t show_ps_sensorlist_info(struct device *dev,
					  struct device_attribute *attr, char *buf)
{
	memcpy(buf, &sensorlist_info[PS], sizeof(struct sensorlist_info));
	return sizeof(struct sensorlist_info);
}
static DEVICE_ATTR(ps_sensorlist_info, 0664, show_ps_sensorlist_info, NULL);

static ssize_t show_als_sensorlist_info(struct device *dev,
					  struct device_attribute *attr, char *buf)
{
	memcpy(buf, &sensorlist_info[ALS], sizeof(struct sensorlist_info));
	return sizeof(struct sensorlist_info);
}
static DEVICE_ATTR(als_sensorlist_info, 0664, show_als_sensorlist_info, NULL);

static ssize_t show_airpress_sensorlist_info(struct device *dev,
					  struct device_attribute *attr, char *buf)
{
	memcpy(buf, &sensorlist_info[AIRPRESS], sizeof(struct sensorlist_info));
	return sizeof(struct sensorlist_info);
}
static DEVICE_ATTR(airpress_sensorlist_info, 0664, show_airpress_sensorlist_info, NULL);

static struct attribute *acc_sensor_attrs[] = {
	&dev_attr_self_test.attr,
	&dev_attr_self_test_timeout.attr,
	&dev_attr_calibrate.attr,
	&dev_attr_calibrate_timeout.attr,
	&dev_attr_acc_sensorlist_info.attr,
	NULL,
};

static const struct attribute_group acc_sensor_attrs_grp = {
	.attrs = acc_sensor_attrs,
};

int sleeve_test_enabled = 0;
extern u8 phone_color;
extern struct sleeve_detect_pare sleeve_detect_paremeter[MAX_PHONE_COLOR_NUM];

static int sleeve_test_ps_prepare(int ps_config)
{
	int ret = -1;
	write_info_t pkg_ap;
	read_info_t pkg_mcu;

	memset(&pkg_ap, 0, sizeof(pkg_ap));
	memset(&pkg_mcu, 0, sizeof(pkg_mcu));
	pkg_ap.tag = TAG_PS;
	pkg_ap.cmd = CMD_CMN_CONFIG_REQ;
	pkg_ap.wr_buf = &ps_config;
	pkg_ap.wr_len = sizeof(ps_config);
	ret = write_customize_cmd(&pkg_ap,  &pkg_mcu);

	if(ret)
	{
		hwlog_err("send sleeve_test ps config cmd to mcu fail,ret=%d\n", ret);
		return ret;
	}
	if(pkg_mcu.errno!=0){
		hwlog_err("sleeve_test ps config fail(%d)\n", pkg_mcu.errno);
	}
	return ret;
}

static ssize_t store_sleeve_test_prepare(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size){

	unsigned long val = 0;
	int ret = -1;

	if (strict_strtoul(buf, 10, &val)){
		hwlog_err("%s: sleeve_test enable val invalid", __FUNCTION__);
		return -EINVAL;
	}

	hwlog_info("%s: sleeve_test enable val (%ld)\n", __FUNCTION__, val);
	if((val !=0) && (val !=1)) {
		hwlog_err("%s:sleeve_test set enable fail, invalid val\n", __FUNCTION__);
		return -EINVAL;
	}

	if(sleeve_test_enabled == val){
		hwlog_info("%s:sleeve_test already at seted state\n", __FUNCTION__);
		return size;
	}

	ret = sleeve_test_ps_prepare(val);
	if(ret){
		hwlog_err("%s: sleeve_test enable fail: %d \n", __FUNCTION__, ret);
		return -EINVAL;
	}
	sleeve_test_enabled = val;

	hwlog_info("%s: sleeve_test set enable success\n", __FUNCTION__);

	return size;

}

static ssize_t show_sleeve_test_threshhold(struct device *dev, struct device_attribute *attr,
				const char *buf, size_t size){
	int i = 0;

	for(i = 0; i < MAX_PHONE_COLOR_NUM; i++){
		if(phone_color == sleeve_detect_paremeter[i].tp_color){
			hwlog_info("sleeve_test threshhold (%d), phone_color(%d)\n",
				sleeve_detect_paremeter[i].sleeve_detect_threshhold, phone_color);
			return snprintf(buf, MAX_STR_SIZE, "%d\n", sleeve_detect_paremeter[i].sleeve_detect_threshhold);
		}
	}

	hwlog_info("sleeve_test get threshhold fail, phone_color(%d)\n", phone_color);
	return -1;
}


static DEVICE_ATTR(sleeve_test_prepare, 0220, NULL, store_sleeve_test_prepare);
static DEVICE_ATTR(sleeve_test_threshhold, 0440, show_sleeve_test_threshhold, NULL);

static struct attribute *ps_sensor_attrs[] = {
	&dev_attr_calibrate.attr,
	&dev_attr_calibrate_timeout.attr,
	&dev_attr_sleeve_test_prepare.attr,
	&dev_attr_ps_sensorlist_info.attr,
	NULL,
};

static const struct attribute_group ps_sensor_attrs_grp = {
	.attrs = ps_sensor_attrs,
};

static struct attribute *als_sensor_attrs[] = {
	&dev_attr_calibrate.attr,
	&dev_attr_als_debug_data.attr,
	&dev_attr_calibrate_timeout.attr,
	&dev_attr_sleeve_test_threshhold.attr,
	&dev_attr_als_sensorlist_info.attr,
	NULL,
};

static const struct attribute_group als_sensor_attrs_grp = {
	.attrs = als_sensor_attrs,
};

static struct attribute *mag_sensor_attrs[] = {
	&dev_attr_self_test.attr,
	&dev_attr_self_test_timeout.attr,
	&dev_attr_calibrate_method.attr,
	&dev_attr_mag_sensorlist_info.attr,
	NULL,
};

static const struct attribute_group mag_sensor_attrs_grp = {
	.attrs = mag_sensor_attrs,
};

static struct attribute *hall_sensor_attrs[] = {
	NULL,
};

static const struct attribute_group hall_sensor_attrs_grp = {
	.attrs = hall_sensor_attrs,
};

static struct attribute *gyro_sensor_attrs[] = {
	&dev_attr_self_test.attr,
	&dev_attr_self_test_timeout.attr,
	&dev_attr_calibrate.attr,
	&dev_attr_calibrate_timeout.attr,
	&dev_attr_gyro_sensorlist_info.attr,
	NULL,
};

static const struct attribute_group gyro_sensor_attrs_grp = {
	.attrs = gyro_sensor_attrs,
};

static struct attribute *airpress_sensor_attrs[] = {
	&dev_attr_read_airpress.attr,
	&dev_attr_set_calidata.attr,
	&dev_attr_airpress_sensorlist_info.attr,
	NULL,
};

static const struct attribute_group airpress_sensor_attrs_grp = {
	.attrs = airpress_sensor_attrs,
};

static struct attribute *finger_sensor_attrs[] = {
	&dev_attr_set_fingersense_enable.attr,
	&dev_attr_fingersense_data_ready.attr,
	&dev_attr_fingersense_latch_data.attr,
	&dev_attr_fingersense_req_data.attr,
	NULL,
};

static const struct attribute_group finger_sensor_attrs_grp = {
	.attrs = finger_sensor_attrs,
};

static struct attribute *handpress_sensor_attrs[] = {
	&dev_attr_self_test.attr,
	&dev_attr_self_test_timeout.attr,
	&dev_attr_calibrate.attr,
	&dev_attr_calibrate_timeout.attr,
	NULL,
};
static const struct attribute_group handpress_sensor_attrs_grp = {
	.attrs = handpress_sensor_attrs,
};

static struct attribute *ois_sensor_attrs[] = {
	&dev_attr_ois_ctrl.attr,
	NULL,
};

static const struct attribute_group ois_sensor_attrs_grp = {
	.attrs = ois_sensor_attrs,
};
static struct attribute *cap_prox_sensor_attrs[] = {
	&dev_attr_calibrate.attr,
	&dev_attr_calibrate_timeout.attr,
	&dev_attr_cap_prox_calibrate_type.attr,
	&dev_attr_cap_prox_calibrate_order.attr,
	NULL,
};
static const struct attribute_group cap_prox_sensor_attrs_grp = {
	.attrs = cap_prox_sensor_attrs,
};

static struct sensor_cookie all_sensors[] = {
	{
	 .tag = TAG_ACCEL,
	 .name = "acc_sensor",
	 .attrs_group = &acc_sensor_attrs_grp,
	 },
	{
	 .tag = TAG_PS,
	 .name = "ps_sensor",
	 .attrs_group = &ps_sensor_attrs_grp,
	 },
	{
	 .tag = TAG_ALS,
	 .name = "als_sensor",
	 .attrs_group = &als_sensor_attrs_grp,
	 },
	{
	 .tag = TAG_MAG,
	 .name = "mag_sensor",
	 .attrs_group = &mag_sensor_attrs_grp,
	 },
	{
	 .tag = TAG_HALL,
	 .name = "hall_sensor",
	 .attrs_group = &hall_sensor_attrs_grp,
	 },
	{
	 .tag = TAG_GYRO,
	 .name = "gyro_sensor",
	 .attrs_group = &gyro_sensor_attrs_grp,
	 },
	{
	 .tag = TAG_PRESSURE,
	 .name = "airpress_sensor",
	 .attrs_group = &airpress_sensor_attrs_grp,
	 },
	{
	 .tag = TAG_FINGERSENSE,
	 .name = "fingersense_sensor",
	 .attrs_group = &finger_sensor_attrs_grp,
	 },
	{
		.tag = TAG_HANDPRESS,
		.name = "handpress_sensor",
		.attrs_group = &handpress_sensor_attrs_grp,
	},
	{
		.tag = TAG_OIS,
		.name = "ois_sensor",
		.attrs_group = &ois_sensor_attrs_grp,
	},
	{
		.tag = TAG_CAP_PROX,
		.name = "cap_prox_sensor",
		.attrs_group = &cap_prox_sensor_attrs_grp,
	},
};

struct device *get_sensor_device_by_name(const char *name)
{
	int i;

	if (NULL == name)
		return NULL;

	for (i = 0; i < sizeof(all_sensors) / sizeof(all_sensors[0]); ++i) {
		if (all_sensors[i].name
		    && (0 == strcmp(name, all_sensors[i].name))) {
			return all_sensors[i].dev;
		}
	}

	return NULL;
}

static void init_sensors_get_data(void)
{
	int tag;
	for (tag = TAG_SENSOR_BEGIN; tag < TAG_SENSOR_END; ++tag) {
		atomic_set(&sensor_status.get_data[tag].reading, 0);
		init_completion(&sensor_status.get_data[tag].complete);
	}
}

void sensor_get_data(struct sensor_data *data)
{
	struct t_sensor_get_data *get_data = NULL;
	if (NULL == data ||
	    (!(TAG_SENSOR_BEGIN <= data->type
	       && data->type < TAG_SENSOR_END))) {
		return;
	}

	get_data = &sensor_status.get_data[data->type];
	if (atomic_cmpxchg(&get_data->reading, 1, 0)) {
		memcpy(&get_data->data, data, sizeof(get_data->data));
		complete(&get_data->complete);
	}
}

/*device_create->device_register->device_add->device_add_attrs->device_add_attributes*/
static int sensors_register(void)
{
	int i;
	for (i = 0; i < sizeof(all_sensors) / sizeof(all_sensors[0]); ++i) {
		all_sensors[i].dev =
		    device_create(sensors_class, NULL, 0, &all_sensors[i],
				  all_sensors[i].name);
		if (NULL == all_sensors[i].dev) {
			hwlog_err("[%s] Failed", __func__);
			return -1;
		} else {
			if (all_sensors[i].attrs_group != NULL) {
				if (sysfs_create_group(&all_sensors[i].dev->kobj,
				     all_sensors[i].attrs_group)) {
					hwlog_err("create files failed in %s\n",
						  __func__);
				}
			}
		}
	}
	return 0;
}

static void sensors_unregister(void)
{
	device_destroy(sensors_class, 0);
}

static int sensors_debug_init(void)
{
	sensors_class = class_create(THIS_MODULE, "sensors");
	if (IS_ERR(sensors_class))
		return PTR_ERR(sensors_class);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 13, 0))
	sensors_class->dev_groups = &sensors_attr_groups;
#else
	sensors_class->dev_attrs = sensors_class_attrs;
#endif
	sensors_register();
	sensorhub_debug_init();

	init_sensors_get_data();

	return 0;
}

static void sensors_debug_exit(void)
{
	sensors_unregister();
	class_destroy(sensors_class);
}

module_init(sensors_debug_init);
module_exit(sensors_debug_exit);

MODULE_AUTHOR("SensorHub <smartphone@huawei.com>");
MODULE_DESCRIPTION("SensorHub debug driver");
MODULE_LICENSE("GPL");
