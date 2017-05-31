/*
 * slowpath_count.h
 *
 * Provide slowpath_count external call interface
 *
 * Copyright (c) 2001-2021, Huawei Tech. Co., Ltd. All rights reserved.
 *
 * Chenjun <chenjun@hisilicon.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef SLOWPATH_COUNT_H
#define SLOWPATH_COUNT_H

#ifdef CONFIG_HISI_SLOW_PATH_COUNT
extern void pgalloc_count_inc(bool is_slowpath, unsigned int order);
#else
static inline void pgalloc_count_inc(bool is_slowpath, unsigned int order) {}
#endif

#endif
