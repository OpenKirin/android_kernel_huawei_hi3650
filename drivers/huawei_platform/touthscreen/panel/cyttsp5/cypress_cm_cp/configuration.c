/******************************************************************************
 * @file configuration.c
 *
 * configuration.c
 *
 * @version 0.0.1
 * @authors btok
 *
 ******************************************************************************
 * Copyright (2014), Cypress Semiconductor Corporation. All rights reserved.
 *
 * This software, associated documentation and materials ("Software") is owned
 * by Cypress Semiconductor Corporation ("Cypress") and is protected by and
 * subject to worldwide patent protection (United States and foreign), United
 * States copyright laws and international treaty provisions. Therefore, unless
 * otherwise specified in a separate license agreement between you and Cypress,
 * this Software must be treated like any other copyrighted material.
 * Reproduction, modification, translation, compilation, or representation of
 * this Software in any other form (e.g., paper, magnetic, optical, silicon) is
 * prohibited without Cypress's express written permission.
 *
 * Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 * Cypress reserves the right to make changes to the Software without notice.
 * Cypress does not assume any liability arising out of the application or use
 * of Software or any product or circuit described in the Software. Cypress does
 * not authorize its products for use as critical components in any products
 * where a malfunction or failure may reasonably be expected to result in
 * significant injury or death ("High Risk Product"). By including Cypress's
 * product in a High Risk Product, the manufacturer of such system or
 * application assumes all risk of such use and in doing so indemnifies Cypress
 * against all liability.
 *
 * Use of this Software may be limited by and subject to the applicable Cypress
 * software license agreement.
 *****************************************************************************/

/*#include <stdio.h>*/
/*#include <stdint.h>*/
/*#include <stdlib.h>*/
/*#include <errno.h>*/

#include "configuration.h"
#include "csv.h"
#include "../cyttsp5_core.h"
#include "../cyttsp5_regs.h"

/*#define ARRAY_SIZE(x)         sizeof(x)/sizeof(x[0])*/

#define OFFSET(x, y)		((unsigned long)&(((x *)0)->y))
#define CONFIGURATION_OFFSET(y)	OFFSET(struct configuration, y)

struct single_value_field {
	char *name;
	int offset;
};

struct multiple_value_field {
	char *name;
	int offset;
	int size_offset;
	int max_size;
};

enum parser_state {
	START,
	SINGLE_VALUE_FIELD_FOUND,
	SINGLE_VALUE_FIELD_PARSED,
	MULTIPLE_VALUE_FIELD_FOUND,
	MULTIPLE_VALUE_FIELD_PARSING,
	END,
	ERROR,
};

struct parser_data {
	struct configuration *configuration;
	enum parser_state state;
	struct single_value_field *current_single_value_field;
	struct multiple_value_field *current_multiple_value_field;
	int multiple_value_field_len;
};

static struct single_value_field single_value_fields[] = {
	{"FAMILY_TYPE", CONFIGURATION_OFFSET(family_type)},
	{"CM_EXCLUDING_COL_EDGE", CONFIGURATION_OFFSET(cm_excluding_col_edge)},
	{"CM_EXCLUDING_ROW_EDGE", CONFIGURATION_OFFSET(cm_excluding_row_edge)},
	{"CM_RANGE_LIMIT_ROW", CONFIGURATION_OFFSET(cm_range_limit_row)},
	{"CM_RANGE_LIMIT_COL", CONFIGURATION_OFFSET(cm_range_limit_col)},
	{"CM_MIN_LIMIT_CAL", CONFIGURATION_OFFSET(cm_min_limit_cal)},
	{"CM_MAX_LIMIT_CAL", CONFIGURATION_OFFSET(cm_max_limit_cal)},
	{"CM_MAX_DELTA_SENSOR_PERCENT",
	 CONFIGURATION_OFFSET(cm_max_delta_sensor_percent)},
	{"CM_MAX_DELTA_BUTTON_PERCENT",
	 CONFIGURATION_OFFSET(cm_max_delta_button_percent)},
	{"MIN_BUTTON", CONFIGURATION_OFFSET(min_button)},
	{"MAX_BUTTON", CONFIGURATION_OFFSET(max_button)},
	{"CP_MAX_DELTA_BUTTON_PERCENT",
	 CONFIGURATION_OFFSET(cp_max_delta_button_percent)},
	{"CP_MAX_DELTA_SENSOR_RX_PERCENT",
	 CONFIGURATION_OFFSET(cp_max_delta_sensor_rx_percent)},
	{"CP_MAX_DELTA_SENSOR_TX_PERCENT",
	 CONFIGURATION_OFFSET(cp_max_delta_sensor_tx_percent)},
};

static struct multiple_value_field multiple_value_fields[] = {
	{"CM_GRADIENT_CHECK_COL",
	 CONFIGURATION_OFFSET(cm_gradient_check_col),
	 CONFIGURATION_OFFSET(cm_gradient_check_col_size),
	 MAX_RX_SENSORS},
	{"CM_GRADIENT_CHECK_ROW",
	 CONFIGURATION_OFFSET(cm_gradient_check_row),
	 CONFIGURATION_OFFSET(cm_gradient_check_row_size),
	 MAX_RX_SENSORS},
	{"PER_ELEMENT_MIN_MAX_TABLE_BUTTON",
	 CONFIGURATION_OFFSET(cm_min_max_table_button),
	 CONFIGURATION_OFFSET(cm_min_max_table_button_size),
	 TABLE_BUTTON_MAX_SIZE},
	{"PER_ELEMENT_MIN_MAX_TABLE_SENSOR",
	 CONFIGURATION_OFFSET(cm_min_max_table_sensor),
	 CONFIGURATION_OFFSET(cm_min_max_table_sensor_size),
	 TABLE_SENSOR_MAX_SIZE},
	{"PER_ELEMENT_MIN_MAX_RX",
	 CONFIGURATION_OFFSET(cp_min_max_table_rx),
	 CONFIGURATION_OFFSET(cp_min_max_table_rx_size),
	 TABLE_RX_MAX_SIZE},
	{"PER_ELEMENT_MIN_MAX_TX",
	 CONFIGURATION_OFFSET(cp_min_max_table_tx),
	 CONFIGURATION_OFFSET(cp_min_max_table_tx_size),
	 TABLE_TX_MAX_SIZE},
};

static inline void *parser_get_address(struct parser_data *data, int offset)
{
	return ((void *)data->configuration) + offset;
}

static int parser_set_state(struct parser_data *data, enum parser_state state)
{
	int *size;

	/*
	 * Save multiple field size when
	 * MULTIPLE_VALUE_FIELD_PARSING state changes
	 */
	if (data->state == MULTIPLE_VALUE_FIELD_PARSING
	    && state != MULTIPLE_VALUE_FIELD_PARSING) {
		struct multiple_value_field *field =
		    data->current_multiple_value_field;
		size = (int *)parser_get_address(data, field->size_offset);
		*size = data->multiple_value_field_len;
		data->multiple_value_field_len = 0;
	}

	/* Check for incomplete parsing states */
	if ((data->state == SINGLE_VALUE_FIELD_FOUND
	     || data->state == MULTIPLE_VALUE_FIELD_FOUND)
	    && (state == SINGLE_VALUE_FIELD_FOUND
		|| state == MULTIPLE_VALUE_FIELD_FOUND)) {
		TS_LOG_DEBUG("%s: Incomplete parsing state\n", __func__);
		data->state = ERROR;
		return -EINVAL;
	}

	/* Check for multiple values on single value fields */
	if (data->state == SINGLE_VALUE_FIELD_PARSED
	    && state == SINGLE_VALUE_FIELD_PARSED) {
		TS_LOG_DEBUG("%s: Multiple value on single value field\n",
			     __func__);
		data->state = ERROR;
		return -EINVAL;
	}

	data->state = state;

	return 0;
}

static struct single_value_field *get_single_value_field(char *field)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(single_value_fields); i++)
		if (!strcmp(field, single_value_fields[i].name))
			return &single_value_fields[i];

	return NULL;
}

static struct multiple_value_field *get_multiple_value_field(char *field)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(multiple_value_fields); i++)
		if (!strcmp(field, multiple_value_fields[i].name))
			return &multiple_value_fields[i];

	return NULL;
}

static void field_read_callback(void *s, size_t len, void *d)
{
	struct parser_data *data = (struct parser_data *)d;
	struct single_value_field *single_value_field;
	struct multiple_value_field *multiple_value_field;
	char *field = (char *)s;
	int *element;
	int ret;
	/*int i;*/

	if (!strcmp(field, ""))
		return;

	if (data->state == ERROR)
		return;

	single_value_field = get_single_value_field(field);
	if (single_value_field) {
		ret = parser_set_state(data, SINGLE_VALUE_FIELD_FOUND);
		if (ret)
			return;

		data->current_single_value_field = single_value_field;
		return;
	}

	multiple_value_field = get_multiple_value_field(field);
	if (multiple_value_field) {
		ret = parser_set_state(data, MULTIPLE_VALUE_FIELD_FOUND);
		if (ret)
			return;

		data->current_multiple_value_field = multiple_value_field;
		return;
	}

	switch (data->state) {
	case SINGLE_VALUE_FIELD_FOUND:
		element = (int *)parser_get_address(data,
						    data->
						    current_single_value_field->
						    offset);

		if (sscanf(field, "%d", element) == 1) {
			TS_LOG_DEBUG("%s: Single value field: %s:%d\n",
				     __func__,
				     data->current_single_value_field->name,
				     *element);
			parser_set_state(data, SINGLE_VALUE_FIELD_PARSED);
			return;
		} else {
			TS_LOG_ERR
			    ("%s: Single value field parse failed for %s\n",
			     __func__, field);
			parser_set_state(data, ERROR);
			return;
		}
		break;

	case MULTIPLE_VALUE_FIELD_FOUND:
	case MULTIPLE_VALUE_FIELD_PARSING:
		/* Check multiple value field size for overflow */
		if (data->multiple_value_field_len ==
		    data->current_multiple_value_field->max_size) {
			TS_LOG_ERR
			    ("%s: Overflow for multiple value field: %s\n",
			     __func__,
			     data->current_multiple_value_field->name);
			parser_set_state(data, ERROR);
			return;
		}

		element = (int *)parser_get_address(data,
						    data->
						    current_multiple_value_field->
						    offset);
		element += data->multiple_value_field_len;

		if (sscanf(field, "%d", element) == 1) {
			TS_LOG_DEBUG("%s: Multiple value field: %s[%d]:%d\n",
				     __func__,
				     data->current_multiple_value_field->name,
				     data->multiple_value_field_len, *element);
			data->multiple_value_field_len++;
			parser_set_state(data, MULTIPLE_VALUE_FIELD_PARSING);
			return;
		} else {
			TS_LOG_ERR
			    ("%s: Multiple value field parse failed for %s\n",
			     __func__, field);
			return;
		}
		break;
	default:
		break;
	}
}

static void parser_init(struct parser_data *data,
			struct configuration *configuration)
{
	data->configuration = configuration;
	data->state = START;
	data->current_single_value_field = NULL;
	data->current_multiple_value_field = NULL;
	data->multiple_value_field_len = 0;
}

int configuration_get(struct file *file, struct configuration *configuration)
{
	struct csv_parser p;
	uint8_t buffer[512] = { 0 };
	size_t bytes_read;
	struct parser_data data;
	int ret;

	if (!file || !configuration)
		return -EINVAL;

	ret = csv_init(&p, CSV_APPEND_NULL);
	if (ret) {
		goto exit;
	}

	parser_init(&data, configuration);
	/*bytes_read = vfs_read(config_file, buffer, sizeof(buffer), &(config_file->f_pos));*/

	while ((bytes_read =
		vfs_read(file, buffer, sizeof(buffer), &(file->f_pos))) > 0) {
		if (data.state == ERROR) {
			ret = -EINVAL;
			goto finish;
		}

		if (csv_parse(&p, buffer, bytes_read, field_read_callback,
			      NULL, &data) != bytes_read) {
			TS_LOG_ERR("%s,Error parsing file: %s\n",
				   __func__, csv_strerror(csv_error(&p)));
			ret = -csv_error(&p);
			goto finish;
		}
	}

	csv_fini(&p, field_read_callback, NULL, &data);

	parser_set_state(&data, END);

	TS_LOG_ERR("%s: family_type:%d\n", __func__,
		   configuration->family_type);
	TS_LOG_ERR("%s: cm_excluding_col_edge:%d\n", __func__,
		   configuration->cm_excluding_col_edge);
	TS_LOG_ERR("%s: cm_range_limit_row:%d\n", __func__,
		   configuration->cm_range_limit_row);
	TS_LOG_ERR("%s: cm_range_limit_col:%d\n", __func__,
		   configuration->cm_range_limit_col);
	TS_LOG_ERR("%s: cm_min_limit_cal:%d\n", __func__,
		   configuration->cm_min_limit_cal);
	TS_LOG_ERR("%s: cm_max_limit_cal:%d\n", __func__,
		   configuration->cm_max_limit_cal);
	TS_LOG_ERR("%s: cm_max_delta_sensor_percent:%d\n", __func__,
		   configuration->cm_max_delta_sensor_percent);
	TS_LOG_ERR("%s: cm_max_delta_button_percent:%d\n", __func__,
		   configuration->cm_max_delta_button_percent);
	TS_LOG_ERR("%s: cp_max_delta_button_percent:%d\n", __func__,
		   configuration->cp_max_delta_button_percent);
	TS_LOG_ERR("%s: cp_max_delta_sensor_rx_percent:%d\n", __func__,
		   configuration->cp_max_delta_sensor_rx_percent);
	TS_LOG_ERR("%s: cp_max_delta_sensor_tx_percent:%d\n", __func__,
		   configuration->cp_max_delta_sensor_tx_percent);

	TS_LOG_ERR("%s: cm_min_max_table_button_size:%d\n",
		   __func__, configuration->cm_min_max_table_button_size);
	TS_LOG_ERR("%s: cm_min_max_table_sensor_size:%d\n",
		   __func__, configuration->cm_min_max_table_sensor_size);
	TS_LOG_ERR("%s: cp_min_max_table_rx_size:%d\n",
		   __func__, configuration->cp_min_max_table_rx_size);
	TS_LOG_ERR("%s: cp_min_max_table_tx_size:%d\n",
		   __func__, configuration->cp_min_max_table_tx_size);
finish:
	csv_free(&p);

exit:
	return ret;
}
