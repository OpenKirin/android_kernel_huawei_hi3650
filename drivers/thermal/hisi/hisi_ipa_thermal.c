/* Copyright (c) 2008-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
*  Porting from ARM by qushenzheng <qushenzheng@hisilicon.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/
#include <linux/cpu_cooling.h>
#include <linux/debugfs.h>
#include <linux/cpufreq.h>
#include <linux/cpumask.h>
#include <linux/module.h>
#include <linux/platform_device.h>
#include <linux/thermal.h>
#include <linux/topology.h>
#include <trace/events/thermal_power_allocator.h>
#include <linux/version.h>

#ifdef CONFIG_HISI_THERMAL_SPM
#include <linux/string.h>
#endif

#define IPA_SENSOR_MAXID    255
#define IPA_SENSOR "tsens_max"
#define IPA_INIT_OK  0x05a5a5a5b
#define NUM_CLUSTERS 2
#define IPA_SOC_INIT_TEMP  (85000)
#ifdef CONFIG_HISI_THERMAL_SPM
#define MAX_SHOW_STR 5
#endif

enum cluster_type {
	CLUSTER_LITTLE = 0,
	CLUSTER_BIG
};

#ifdef CONFIG_HISI_THERMAL_SPM
struct spm_t {
	struct device *device;
	bool spm_mode;
	bool vr_mode;
};
#endif

struct ipa_sensor {
	u32 sensor_id;
	long prev_temp;
	int alpha;
	struct thermal_zone_device *tzd;
	struct cpumask cluster[NUM_CLUSTERS];
	struct thermal_cooling_device *cdevs[NUM_CLUSTERS];
	u32 cluster_dyn_capacitance[NUM_CLUSTERS];
	u32 cluster_static_capacitance[NUM_CLUSTERS];
	u32 cache_capacitance[NUM_CLUSTERS];
	const char* temperature_scale_capacitance[5];
#ifdef CONFIG_HISI_THERMAL_SPM
	struct class *hisi_thermal_class;
	struct spm_t spm;
#endif
	int init_flag;
};

struct ipa_sensor ipa_temp_sensor;

extern int ipa_get_sensor_value(u32 sensor, unsigned long *val);
extern int ipa_get_sensor_id(char *name);

#ifdef CONFIG_HISI_THERMAL_SPM
int vr_mode_enable;
extern struct cpufreq_frequency_table *cpufreq_frequency_get_table(unsigned int cpu);

static void update_cpufreqs(void)
{
	cpufreq_update_policy(0);
	cpufreq_update_policy(4);
}

static bool setfreq_available(unsigned int idx , u32 freq) {
	struct cpufreq_frequency_table *pos, *table = NULL;
	int ret = false;

	switch (idx) {
		case 0: //Little core
			table = cpufreq_frequency_get_table(0);
			if (!table) {
				pr_err("%s: Unable to find freq table(0)\n", __func__);
				return false;
			}
			break;
		case 1: //Big core
			table = cpufreq_frequency_get_table(4);
			if (!table) {
				pr_err("%s: Unable to find freq table(4)\n", __func__);
				return false;
			}
			break;
		case 2: //GPU
			ret = true;
			break;
		default:
			break;
	}

	if (idx == 0 || idx == 1){
		cpufreq_for_each_valid_entry(pos, table) {
		if(freq == pos->frequency)
			ret = true;
		}
	}

	return ret;
}

#define MAX_POWERHAL_ACTOR	3UL
unsigned int powerhal_profiles[3][MAX_POWERHAL_ACTOR];

#define SHOW_MODE(mode_name)					\
static ssize_t show_##mode_name					\
(struct device *dev, struct device_attribute *attr, char *buf) 			\
{										\
	if (dev == NULL || attr == NULL)					\
		return 0;							\
										\
	return snprintf(buf, (unsigned long)MAX_SHOW_STR, "%d\n",		\
					(int)ipa_temp_sensor.spm.mode_name);	\
}

SHOW_MODE(vr_mode);
SHOW_MODE(spm_mode);

#define STORE_MODE(mode_name)					\
static ssize_t store_##mode_name				\
(struct device *dev, struct device_attribute *attr, 		\
	const char *buf, size_t count)				\
{								\
	u32 mode_name = 0;						\
								\
	if (dev == NULL || attr == NULL)			\
		return 0;					\
								\
	if (kstrtouint(buf, 10, &mode_name)) /*lint !e64*/	\
		return -EINVAL;					\
								\
	ipa_temp_sensor.spm.mode_name = mode_name ? true : false;	\
								\
	update_cpufreqs();			\
	return (ssize_t)count;					\
}

STORE_MODE(vr_mode);
STORE_MODE(spm_mode);

/*lint -e84 -e846 -e514 -e778 -e866 -esym(84,846,514,778,866,*)*/
#define MODE_ATTR_RW(mode_name)				\
static DEVICE_ATTR(mode_name, S_IWUSR | S_IRUGO,	\
				show_##mode_name,	\
				store_##mode_name)

MODE_ATTR_RW(vr_mode);
MODE_ATTR_RW(spm_mode);
/*lint -e84 -e846 -e514 -e778 -e866 +esym(84,846,514,778,866,*)*/

static ssize_t
vr_freq_store(struct device *dev, struct device_attribute *attr,
		     const char *buf, size_t count)
{
	u32 freq;
	unsigned int i = 0;
	char *token;
	char temp_buf[40]={0};
	char *s;

	if (dev == NULL || attr == NULL)
		return 0;

	strncpy(temp_buf, buf, sizeof(temp_buf) - 1);
	s = temp_buf;

	for(token = strsep(&s, ","); (token != NULL) && (i < MAX_POWERHAL_ACTOR); token = strsep(&s, ","),i++) {
		if (kstrtouint(token, 10, &freq)) //lint !e64
			return -EINVAL;
		else {
			if(setfreq_available(i,freq)) {
				powerhal_profiles[1][i]=freq;
			}
		}
	}
	update_cpufreqs();
	return (ssize_t)count;
}

static ssize_t
vr_freq_show(struct device *dev, struct device_attribute *devattr,
		       char *buf)
{
	unsigned int i;
	ssize_t ret = 0;

	if (dev == NULL || devattr == NULL)
		return 0;

	for (i = 0; i < MAX_POWERHAL_ACTOR; i++)
		ret += snprintf(buf + ret, 12UL, "%u%s", powerhal_profiles[1][i],",");

	ret += snprintf(buf + ret - 1, 2UL, "\n");
	return ret;
}
/*lint -e84 -e846 -e514 -e778 -e866 -esym(84,846,514,778,866,*)*/
static DEVICE_ATTR(vr_freq, S_IWUSR | S_IRUGO, vr_freq_show, vr_freq_store);
/*lint -e84 -e846 -e514 -e778 -e866 +esym(84,846,514,778,866,*)*/

static ssize_t
spm_freq_store(struct device *dev, struct device_attribute *attr,
		     const char *buf, size_t count)
{
	u32 freq;
	unsigned int i = 0;
	char *token;
	char temp_buf[40]={0};
	char *s;

	if (dev == NULL || attr == NULL)
		return 0;

	strncpy(temp_buf, buf, sizeof(temp_buf) - 1);
	s = temp_buf;

	for(token = strsep(&s, ","); (token != NULL) && (i < MAX_POWERHAL_ACTOR); token = strsep(&s, ","), i++) {
		if (kstrtouint(token, 10, &freq)) //lint !e64
			return -EINVAL;
		else {
			if(setfreq_available(i,freq)) {
				powerhal_profiles[0][i]=freq;
			}
		}
	}
	update_cpufreqs();
	return (ssize_t)count;
}

static ssize_t
spm_freq_show(struct device *dev, struct device_attribute *devattr,
		       char *buf)
{
	unsigned int i;
	ssize_t ret = 0;

	if (dev == NULL || devattr == NULL)
		return 0;

	for (i = 0; i < MAX_POWERHAL_ACTOR; i++)
		ret += snprintf(buf + ret, 12UL, "%u%s", powerhal_profiles[0][i],",");

	ret += snprintf(buf + ret - 1, 2UL, "\n");
	return ret;
}
/*lint -e84 -e846 -e514 -e778 -e866 -esym(84,846,514,778,866,*)*/
static DEVICE_ATTR(spm_freq, S_IWUSR | S_IRUGO, spm_freq_show, spm_freq_store);
/*lint -e84 -e846 -e514 -e778 -e866 +esym(84,846,514,778,866,*)*/

static ssize_t
min_freq_store(struct device *dev, struct device_attribute *attr,
		     const char *buf, size_t count)
{
	u32 freq;
	unsigned int i = 0;
	char *token;
	char temp_buf[40]={0};
	char *s;

	if (dev == NULL || attr == NULL)
		return 0;

	strncpy(temp_buf, buf, sizeof(temp_buf) - 1);
	s = temp_buf;

	for(token = strsep(&s, ","); (token != NULL) && (i < MAX_POWERHAL_ACTOR); token = strsep(&s, ","),i++) {
		if (kstrtouint(token, 10, &freq))
			return -EINVAL;
		else {
			if(setfreq_available(i,freq)) {
				powerhal_profiles[2][i]=freq;
			}
		}
	}
	update_cpufreqs();
	return (ssize_t)count;
}

static ssize_t
min_freq_show(struct device *dev, struct device_attribute *devattr,
		       char *buf)
{
	unsigned int i;
	ssize_t ret = 0;

	if (dev == NULL || devattr == NULL)
		return 0;

	for (i = 0; i < MAX_POWERHAL_ACTOR; i++)
		ret += snprintf(buf + ret, 12UL, "%u%s", powerhal_profiles[2][i],",");

	ret += snprintf(buf + ret - 1, 2UL, "\n");
	return ret;
}
static DEVICE_ATTR(min_freq, S_IWUSR | S_IRUGO, min_freq_show, min_freq_store);

bool is_spm_mode_enabled(void)
{
	return ipa_temp_sensor.spm.spm_mode || ipa_temp_sensor.spm.vr_mode;
}
EXPORT_SYMBOL(is_spm_mode_enabled);

unsigned int get_powerhal_profile(enum ipa_actor actor)
{
	int cur_policy = -1;
	unsigned int freq = 0;

	if (ipa_temp_sensor.spm.vr_mode)
		cur_policy = 1;
	else if (ipa_temp_sensor.spm.spm_mode)
		cur_policy = 0;

	if (cur_policy != -1 && actor <= IPA_GPU)
		freq = powerhal_profiles[cur_policy][actor];

	return freq;
}
EXPORT_SYMBOL(get_powerhal_profile);
unsigned int get_minfreq_profile(enum ipa_actor actor)
{
	unsigned int freq = 0;

	if (actor <= IPA_GPU)
		freq = powerhal_profiles[2][actor];

	return freq;
}
EXPORT_SYMBOL(get_minfreq_profile);
#endif

unsigned long get_soc_temp(void)
{
	if ((IPA_INIT_OK == ipa_temp_sensor.init_flag) && ipa_temp_sensor.tzd) {
		if (ipa_temp_sensor.tzd->temperature < 0)
			return 0;
		return (unsigned long)ipa_temp_sensor.tzd->temperature;
	}

	return  IPA_SOC_INIT_TEMP;
}
EXPORT_SYMBOL(get_soc_temp);

static int get_dyn_power_coeff(enum cluster_type cluster, struct ipa_sensor *ipa_dev)
{
	if (NULL == ipa_dev) {
		pr_err("%s parm null\n", __func__);
		return 0;
	}

	return ipa_dev->cluster_dyn_capacitance[cluster];
}

static int get_cpu_static_power_coeff(enum cluster_type cluster)
{
	struct ipa_sensor *sensor_data = &ipa_temp_sensor;
	return sensor_data->cluster_static_capacitance[cluster];
}

static u32 get_cache_static_power_coeff(enum cluster_type cluster)
{
	struct ipa_sensor *sensor_data = &ipa_temp_sensor;
	return sensor_data->cache_capacitance[cluster];
}

static unsigned long get_temperature_scale(unsigned long temp)
{
	int i, t_exp = 1, t_scale = 0, ret = 0;
	struct ipa_sensor *sensor_data = &ipa_temp_sensor;
	int capacitance[5] = {0};

	for (i = 0; i < 4; i++) {
		ret = kstrtoint(sensor_data->temperature_scale_capacitance[i], 10, &capacitance[i]);
		if (ret)
			pr_warning("%s kstortoint is failed \n", __func__);
		t_scale += capacitance[i] * t_exp;
		t_exp *= temp;
	}

	ret = kstrtoint(sensor_data->temperature_scale_capacitance[4], 10, &capacitance[4]);
	if (ret)
		pr_warning("%s kstortoint is failed \n", __func__);
	return (unsigned long)(t_scale / capacitance[4]);
}

static unsigned long get_voltage_scale(unsigned long u_volt)
{
	unsigned long m_volt = u_volt / 1000;
	unsigned long v_scale;
	v_scale = m_volt * m_volt * m_volt; /* = (m_V^3) / (900 ^ 3) =  */
	return v_scale / 1000000; /* the value returned needs to be /(1E3)*/
}

/* voltage in uV and temperature in mC */
static int hisi_cluster_get_static_power(cpumask_t *cpumask, int interval,
			    unsigned long u_volt, u32 *static_power)
{
	unsigned long temperature, t_scale, v_scale;
	u32 cpu_coeff;
	int nr_cpus = cpumask_weight(cpumask);
	enum cluster_type cluster =
		topology_physical_package_id(cpumask_any(cpumask));

	temperature = get_soc_temp();
	temperature /= 1000;

	cpu_coeff = get_cpu_static_power_coeff(cluster);

	t_scale = get_temperature_scale(temperature);
	v_scale = get_voltage_scale(u_volt);
	*static_power = nr_cpus * (cpu_coeff * t_scale * v_scale) / 1000000;

	if (nr_cpus) {
		u32 cache_coeff = get_cache_static_power_coeff(cluster);
		*static_power += (cache_coeff * v_scale * t_scale) / 1000000; /* cache leakage */
	}

	return 0;
}

#ifdef CONFIG_HISI_THERMAL_SPM
int hisi_calc_static_power(const struct cpumask *cpumask, unsigned long temp,
				unsigned long u_volt, u32 *static_power)
{
	unsigned long temperature, t_scale, v_scale;
	u32 cpu_coeff;
	int nr_cpus = (int)cpumask_weight(cpumask);
	int cluster =
		topology_physical_package_id(cpumask_any(cpumask));

	temperature = temp / 1000;

	cpu_coeff = (u32)get_cpu_static_power_coeff((enum cluster_type)cluster);

	t_scale = get_temperature_scale(temperature);
	v_scale = get_voltage_scale(u_volt);
	*static_power = (u32)(nr_cpus * (cpu_coeff * t_scale * v_scale) / 1000000); //lint !e737

	if (nr_cpus) {
		u32 cache_coeff = get_cache_static_power_coeff((enum cluster_type)cluster);
		*static_power += (u32)((cache_coeff * v_scale * t_scale) / 1000000); /* cache leakage */
	}

	return 0;
}
EXPORT_SYMBOL(hisi_calc_static_power);
#endif

#define FRAC_BITS 8
#define int_to_frac(x) ((x) << FRAC_BITS)

/**
 * mul_frac() - multiply two fixed-point numbers
 * @x:	first multiplicand
 * @y:	second multiplicand
 *
 * Return: the result of multiplying two fixed-point numbers.  The
 * result is also a fixed-point number.
 */
static inline s64 mul_frac(s64 x, s64 y)
{
	return (x * y) >> FRAC_BITS;
}

static int get_temp_value(void *data, long *temp)
{
	long sensor_val[IPA_SENSOR_NUM] = {0};
	struct ipa_sensor *sensor = (struct ipa_sensor *)data;
	long val = 0;
	long val_max = 0;
	int ret = -EINVAL;
	int id = 0;
	long est_temp = 0;


	if (IPA_SENSOR_MAXID == sensor->sensor_id) {
		/*read all sensor*/
		for (id = 0; id < IPA_SENSOR_NUM; id++) {
			ret = ipa_get_sensor_value(id, &val);
			sensor_val[id] = val;
			if (ret)
				return ret;
		}

		val_max = sensor_val[0];
		for (id = 1; id < IPA_SENSOR_NUM; id++) {
			if (sensor_val[id] > val_max)
				val_max = sensor_val[id];
		}

		val = val_max;

		trace_IPA_get_tsens_value(sensor_val[0], sensor_val[1], sensor_val[2], val_max);

	} else if (sensor->sensor_id < IPA_SENSOR_NUM) {
		ret = ipa_get_sensor_value(sensor->sensor_id, &val);
		if (ret)
			return ret;
	} else {
		return ret;
	}

	if (!sensor->prev_temp)
		sensor->prev_temp = val;

	est_temp = mul_frac(sensor->alpha, val) +
		mul_frac((int_to_frac(1) - sensor->alpha), sensor->prev_temp);

	sensor->prev_temp = est_temp;
	*temp = est_temp;

	return 0;
}

static void update_debugfs(struct ipa_sensor *sensor_data)
{
#ifdef CONFIG_HISI_DEBUG_FS
	struct dentry *dentry_f, *filter_d;

	filter_d = debugfs_create_dir("thermal_lpf_filter", NULL);
	if (IS_ERR_OR_NULL(filter_d)) {
		pr_warning("unable to create debugfs directory for the LPF filter\n");
		return;
	}

	dentry_f = debugfs_create_u32("alpha", S_IWUSR | S_IRUGO, filter_d,
				      (u32 *)&sensor_data->alpha);
	if (IS_ERR_OR_NULL(dentry_f)) {
		debugfs_remove(filter_d);
		pr_warn("IPA:Unable to create debugfsfile: alpha\n");
		return;
	}
#endif
}

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,1,15)
static const struct thermal_zone_of_device_ops hisi_ipa_thermal_ops = {
	.get_temp = get_temp_value,
};
#endif

#ifdef CONFIG_HISI_THERMAL_SPM
static int powerhal_cfg_init(void)
{
	struct device_node *node;
	int ret;
	unsigned int data[MAX_POWERHAL_ACTOR] = {0};

	node = of_find_compatible_node(NULL, NULL, "hisi,powerhal");
	if (!node) {
		pr_err("%s cannot find powerhal dts.\n", __func__);
		return -ENODEV;
	}

	ret = of_property_read_u32_array(node, "hisi,powerhal-spm-cfg", data, MAX_POWERHAL_ACTOR);
	if (ret) {
		pr_err("%s cannot find hisi,powerhal-spm-cfg.\n", __func__);
		return -ENODEV;
	}
	memcpy(powerhal_profiles[0], data, sizeof(data));

	ret = of_property_read_u32_array(node, "hisi,powerhal-vr-cfg", data, MAX_POWERHAL_ACTOR);

	if (ret) {
		pr_err("%s cannot find hisi,powerhal-spm-cfg.\n", __func__);
		return -ENODEV;
	}

	memcpy(powerhal_profiles[1], data, sizeof(data));

	ret = of_property_read_u32_array(node, "hisi,powerhal-min-cfg", data, MAX_POWERHAL_ACTOR);
	if (ret) {
		pr_err("%s cannot find hisi,powerhal-spm-cfg.\n", __func__);
		return -ENODEV;
	}

	memcpy(powerhal_profiles[2], data, sizeof(data));
	return 0;

}
#endif

static int ipa_thermal_probe(struct platform_device *pdev)
{
	struct ipa_sensor *sensor_data = &ipa_temp_sensor;
	struct device_node *np;
	int sensor, cpu;
	int i;
	struct device *dev = &pdev->dev;
	struct device_node *dev_node = dev->of_node;
	int ret;

	if (!of_device_is_available(dev_node))
		return -ENODEV;

	memset((void *)&ipa_temp_sensor, 0, sizeof(ipa_temp_sensor));

	if (!cpufreq_frequency_get_table(0)) {
		dev_info(&pdev->dev,
			"IPA:Frequency table not initialized. Deferring probe...\n");
		return -EPROBE_DEFER;
	}

	platform_set_drvdata(pdev, sensor_data);

	for_each_possible_cpu(cpu) {
		int cluster_id = topology_physical_package_id(cpu);
		if (cluster_id > NUM_CLUSTERS) {
			pr_warn("IPA:Cluster id: %d > %d\n", cluster_id, NUM_CLUSTERS);
			ret = -ENODEV;
			goto error;
		}

		cpumask_set_cpu(cpu, &sensor_data->cluster[cluster_id]);
	}

	ret = of_property_read_u32_array(dev_node, "hisilicon,cluster_dyn_capacitance", sensor_data->cluster_dyn_capacitance, 0x2);
	if (ret) {
		dev_err(dev, "%s actor_dyn_capacitance read err\n", __func__);
		return ret;
	}

	ret = of_property_read_u32_array(dev_node, "hisilicon,cluster_static_capacitance", sensor_data->cluster_static_capacitance, 0x2);
	if (ret) {
		dev_err(dev, "%s actor_dyn_capacitance read err\n", __func__);
		return ret;
	}

	ret = of_property_read_u32_array(dev_node, "hisilicon,cache_capacitance", sensor_data->cache_capacitance, 0x2);
	if (ret) {
		dev_err(dev, "%s actor_dyn_capacitance read err\n", __func__);
		return ret;
	}

	for (i = 0; i < 5; i++) {
		ret =  of_property_read_string_index(dev_node, "hisilicon,temperature_scale_capacitance", i, &sensor_data->temperature_scale_capacitance[i]);
		if (ret) {
			dev_err(dev, "%s temperature_scale_capacitance [%d] read err\n", __func__, i);
			return ret;
		}
	}

	for (i = 0; i < NUM_CLUSTERS; i++) {
		char node[16];
		int cpuid;
		enum cluster_type cluster;
		cpuid = (int)cpumask_any(&sensor_data->cluster[i]);
		if (cpuid >= nr_cpu_ids)
			continue;
		cluster = (enum cluster_type)topology_physical_package_id(cpuid);

		snprintf(node, sizeof(node), "cluster%d", i);
		np = of_find_node_by_name(NULL, node);

		if (!np) {
			dev_err(&pdev->dev, "Node not found: %s\n", node);
			continue;
		}
		sensor_data->cdevs[i] =
			of_cpufreq_power_cooling_register(np,
						&sensor_data->cluster[i],
						get_dyn_power_coeff(cluster, sensor_data),
						hisi_cluster_get_static_power);
		if (IS_ERR(sensor_data->cdevs[i]))
			dev_warn(&pdev->dev,
				"IPA:Error registering cpu power actor: who [%d] ERROR_ID [%lld]\n",
				i, (long long)sensor_data->cdevs[i]);
	}

	sensor = ipa_get_sensor_id(IPA_SENSOR);
	if (sensor < 0)
		sensor = IPA_SENSOR_MAXID;

	sensor_data->sensor_id = (u32)sensor;
	dev_info(&pdev->dev, "IPA:Probed %s sensor. Id=%hu\n", IPA_SENSOR, sensor_data->sensor_id);

	/*
	* alpha ~= 2 / (N + 1) with N the window of a rolling mean We
	 * use 8-bit fixed point arithmetic.  For a rolling average of
	 * window 20, alpha = 2 / (20 + 1) ~= 0.09523809523809523 .
	 * In 8-bit fixed point arigthmetic, 0.09523809523809523 * 256
	 * ~= 24
	 */
	sensor_data->alpha = 24;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(4,1,15)
	sensor_data->tzd = thermal_zone_of_sensor_register(&pdev->dev,
							sensor_data->sensor_id,
							sensor_data,
							&hisi_ipa_thermal_ops);
#else
	sensor_data->tzd = thermal_zone_of_sensor_register(&pdev->dev,
							sensor_data->sensor_id,
							sensor_data,
							get_temp_value, NULL);
#endif

	if (IS_ERR(sensor_data->tzd)) {
		dev_warn(&pdev->dev, "IPA ERR:registering sensor tzd[%p] \n", sensor_data->tzd);
		return (int)PTR_ERR(sensor_data->tzd);
	}

	update_debugfs(sensor_data);
	thermal_zone_device_update(sensor_data->tzd);
	sensor_data->init_flag = IPA_INIT_OK;

#ifdef CONFIG_HISI_THERMAL_SPM
	sensor_data->hisi_thermal_class = class_create(THIS_MODULE, "hisi_thermal"); //lint !e64
	if (IS_ERR(sensor_data->hisi_thermal_class)) {
		return PTR_ERR(sensor_data->hisi_thermal_class);
	}

	if (powerhal_cfg_init()) {
		pr_err("%s: powerhal_init error\n", __func__);
		ret = -ENODEV;
		goto class_destroy;
	}

	sensor_data->spm.device =
	    device_create(sensor_data->hisi_thermal_class, NULL, 0, NULL,
			  "spm");
	if (IS_ERR(sensor_data->spm.device)) {
		ret = (int)PTR_ERR(sensor_data->spm.device);
		goto class_destroy;
	}

	ret = device_create_file(sensor_data->spm.device, &dev_attr_spm_mode);
	if (ret) {
		pr_err("Spm mode create error\n");
		goto device_destroy;
	}

	ret = device_create_file(sensor_data->spm.device, &dev_attr_spm_freq);
	if (ret) {
		goto device_destroy;
	}
	ret = device_create_file(sensor_data->spm.device, &dev_attr_vr_mode);
	if (ret) {
		pr_err("VR mode create error\n");
		goto device_destroy;
	}
	ret = device_create_file(sensor_data->spm.device, &dev_attr_vr_freq);
	if (ret) {
		goto device_destroy;
	}
	ret = device_create_file(sensor_data->spm.device, &dev_attr_min_freq);
	if (ret) {
		goto device_destroy;
	}
#endif
	return 0;

#ifdef CONFIG_HISI_THERMAL_SPM
device_destroy:
	device_destroy(sensor_data->hisi_thermal_class, 0);
class_destroy:
	class_destroy(sensor_data->hisi_thermal_class);
	sensor_data->hisi_thermal_class = NULL;
#endif

error:
	return ret;
}

static int ipa_thermal_remove(struct platform_device *pdev)
{
	struct ipa_sensor *sensor = platform_get_drvdata(pdev);

	if (NULL == sensor) {
		dev_warn(&pdev->dev, "%s sensor is null!\n", __func__);
		return -1;
	}
	thermal_zone_device_unregister(sensor->tzd);
	platform_set_drvdata(pdev, NULL);

#ifdef CONFIG_HISI_THERMAL_SPM
	if (sensor->hisi_thermal_class) {
		device_destroy(sensor->hisi_thermal_class, 0);
		class_destroy(sensor->hisi_thermal_class);
	}
#endif

	return 0;
}

static struct of_device_id ipa_thermal_of_match[] = {
	{ .compatible = "arm,ipa-thermal" },
	{},
};

MODULE_DEVICE_TABLE(of, ipa_thermal_of_match);

static struct platform_driver ipa_thermal_platdrv = {
	.driver = {
		.name		= "ipa-thermal",
		.owner		= THIS_MODULE,
		.of_match_table = ipa_thermal_of_match,
	},
	.probe	= ipa_thermal_probe,
	.remove	= ipa_thermal_remove,
};
module_platform_driver(ipa_thermal_platdrv);

MODULE_LICENSE("GPL");
