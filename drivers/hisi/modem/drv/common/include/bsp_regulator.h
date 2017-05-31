/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */


#ifndef __BSP_REGULATOR_H__
#define __BSP_REGULATOR_H__
#include "osl_common.h"
#include "osl_sem.h"
#include "osl_list.h"
#include "bsp_sram.h"
#ifdef __cplusplus
extern "C" {
#endif

/*
 * struct regulator
 *
 * One for each consumer device.
 */
#define VOLT_NAME_PA_VCC "PA-vcc"                       /* BUCK0 */
#define VOLT_NAME_RFIC_FRONT_VCC "RFIC_front-vcc"       /* BUCK5/LDO11 or NULL,default BUCK5.if change to LDO11,need to modify regulator table */
#define VOLT_NAME_RFIC_VCC "RFIC-vcc"                   /* LVS07 */
#define VOLT_NAME_RF_FEM_VCC "RF_FEM-vcc"               /* LDO13 */
#define VOLT_NAME_PA_VBIA2_VCC "PA_Vbias2-vcc"          /* LDO12 */

struct regulator_id_ops {
	int (*list_voltage) (int regulator_id, unsigned selector);
	int (*set_voltage) (int regulator_id, int min_uV, int max_uV, unsigned *selector);
	int (*get_voltage) (int regulator_id);
	int (*is_enabled) (int regulator_id);
	int (*enable) (int regulator_id);
	int (*disable) (int regulator_id);
	int (*set_mode) (int regulator_id, unsigned int mode);
	unsigned int (*get_mode) (int regulator_id);
	int (*set_current) (int regulator_id, int min_uA, int max_uA, unsigned *selector);
	int (*get_current_limit) (int regulator_id);
};
struct regulator_type_map{
	char * regulator_type;
	unsigned int is_enabled_flag;
	struct list_head   list;
	struct regulator_id_ops *ops;
};

struct regulator_mtcmos_ops {
	unsigned int mtcoms_id;
	unsigned int mtcmos_addr;
	unsigned 	int mtcmos_en_offset[2];
	unsigned 	int mtcmos_dis_offset[2];
	unsigned 	int clk_en_offset[2];
	unsigned 	int clk_dis_offset[2];
	unsigned 	int srs_en_offset[2];
	unsigned 	int srs_dis_offset[2];
	unsigned 	int ios_en_offset[2];
	unsigned 	int ios_dis_offset[2];
	unsigned 	int mtcmos_stat_offset[2];
};

enum REGULATOR_OPS_ID
{
	REGULATOR_OPS_ENABLE = 0,
	REGULATOR_OPS_DISABLE = 1,
	REGULATOR_OPS_IS_ENABLED = 2,
	REGULATOR_OPS_GET_VOLT = 3,
	REGULATOR_OPS_SET_VOLT = 4,
	REGULATOR_OPS_GET_CURR = 5,
	REGULATOR_OPS_SET_CURR = 6,
};
enum REGULATOR_TYPE_ID
{
	REGULATOR_TYPE = 0,
	MTCMOS_TYPE = 2,
};

#define PMU_TYPE_LEN   (8)
struct regulator_pm_om_log {
	u32 ops_id;
	u32 regulator_id;
	u32 use_count;
	u32 task_id;
	char pmutype[PMU_TYPE_LEN];
};

 #ifdef __KERNEL__
#include <linux/regulator/consumer.h>

#define H6551_DR1_NM "Balong_dr1"
#define H6551_DR2_NM "Balong_dr2"
#define H6551_DR3_NM "Balong_dr3"
#define H6551_DR4_NM "Balong_dr4"
#define H6551_DR5_NM "Balong_dr5"
#define HI6551_SD_DR  "SD_DR-vcc"
#define HI6551_LCD_DR "BL-vcc"


#define BUCK3_ONOFF_FLAG			(((SRAM_SMALL_SECTIONS * )((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_BUCK3_ACORE_ONOFF_FLAG)

#ifndef CONFIG_REGULATOR
static inline int regulator_pmic_ops_register(struct regulator_id_ops *pmic_ops, char *pmic_type)
{
	return 0;
}
#else
int regulator_pmic_ops_register(struct regulator_id_ops *pmic_ops, char *pmic_type);
#endif

#elif defined(__OS_VXWORKS__)||defined(__OS_RTOSCK__)


struct regulator_consumer_supply {
	const char *supply;			/* consumer supply - e.g. "vcc" */
	const char *dev_name;   /* dev_name() for consumer */
};

struct regulator{
	const char *name;
	unsigned int id;
	unsigned int  num_consumer_supplies;
	struct regulator_consumer_supply *consumer_supplies;
	int use_count;
	unsigned int use_count_valid;
	unsigned int is_enabled_flag;
	osl_sem_id mutex;
	char *regulator_pmic_type;
	const char *parent_name;
	struct list_head   list;
	struct list_head   consumer_list;
	struct regulator *parent;/*ָ�򸸽ڵ�ͨ��ÿ��regulator��name���Ҹ��ڵ�*/
	struct regulator_id_ops *regulator_pmic_ops;/*ͨ��ƥ��regulator_pmic_type���ҵ���Ӧ��ops*/
	struct regulator *regu;
	int max_uV;
	int min_uV;
};

struct regulator_consumer_map {
	struct list_head list;
	const char *supply;
	struct regulator *regulator;
};
#define BUCK3_ONOFF_FLAG			(((SRAM_SMALL_SECTIONS * )((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_BUCK3_CCORE_ONOFF_FLAG)

int regulator_pmic_ops_register(struct regulator_id_ops *pmic_ops, char *pmic_type);

int regulator_init(void);

/*****************************************************************************
* �� �� ��  : regulator_get
* ��������  :���Ҳ����regulator�����ں��������в�������ʼ��ʱ����
* �������  :dev:�豸�ṹ�壬������ΪNULL
* �������  :id:regulator��id��regulator�ṩ�����֣�ͨ��id�������Ӧ��regulator
* ����ֵ��   A��:
*			 �ɹ�:��õ�regulator�ṹ��ָ��
*            ʧ��:ID_ERR()�ܴ����errno
*			C��:
*			�ɹ�:��õ�regulator�ṹ��ָ��
*           ʧ��:NULL
* ע        :��ģ���ʼ��ʱ��ȡregulator��ע��ʱ�ͷ�regulator
*            ��ȡregulatorʧ����Ҫ��ģ�������Ӧ�Ĵ������ʼ��ʧ��
*****************************************************************************/
/* regulator get and put */
extern struct regulator *regulator_get(unsigned char *name, char *supply);


/*****************************************************************************
*�� �� ��  : regulator_put
*��������  : �ͷ�regulator��Դ���ͷ�ǰ��ȷ��regulator_enable(),regulator_disable()
*			 �ɶ�ʹ��
*�������  : regulator��Դ
*����ֵ	   ��
*
*****************************************************************************/
extern void regulator_put(struct regulator *regulator);

/*****************************************************************************
*�� �� ��  : regulator_enable
*��������  : ʹ��regulator�������regulator_disable()�ɶ�ʹ��
*�������  : regulator��Դ
*����ֵ	   ���ɹ�: = 0
*			 ʧ��: !0
*ע		   : enable/disable ��Ҫ�ɶ�ʹ��
*****************************************************************************/
/* regulator output control and status */
extern int regulator_enable(struct regulator *regulator);
/*****************************************************************************
*�� �� ��  : regulator_disable
*��������  : ȥʹ��regulator�������regulator_enable()�ɶ�ʹ��
*�������  : regulator��Դ
*����ֵ	   ���ɹ�: = 0
*			 ʧ��: !0
*ע		   : enable/disable ��Ҫ�ɶ�ʹ��
*****************************************************************************/
extern int regulator_disable(struct regulator *regulator);
/*****************************************************************************
*�� �� ��  : regulator_is_enabled
*��������  : regulator�Ƿ���ʹ��
*�������  : regulator��Դ
*����ֵ	   ���ɹ�: > 0
*			 ʧ��: = 0
*
*****************************************************************************/
extern int regulator_is_enabled(struct regulator *regulator);
/*****************************************************************************
*�� �� ��  : regulator_get_voltage
*��������  : ��ȡregulator��ǰ��ѹ
*�������  : regulator��Դ
*����ֵ	   ���ɹ�:��ǰ��ѹֵ
*			 ʧ��:����
*****************************************************************************/
extern int regulator_get_voltage(struct regulator *regulator);
/*****************************************************************************
*�� �� ��  : regulator_set_voltage
*��������  : ����regulator��ѹ��������óɹ���������Ч��
*�������  : regulator��Դ��min_uV��max_uVҪ���õĵ�ѹֵ
*����ֵ	   ���ɹ�:0
*			 ʧ��:����
*****************************************************************************/
extern int regulator_set_voltage(struct regulator *regulator, int min_uV, int max_uV);

/*ģʽ���� NORMAL :�������� IDLE :��regulator����ecoģʽ*/
#ifndef REGULATOR_MODE_NORMAL
#define REGULATOR_MODE_NORMAL		0x2
#endif
#ifndef REGULATOR_MODE_IDLE
#define REGULATOR_MODE_IDLE			0x4
#endif
/*****************************************************************************
*�� �� ��  : regulator_set_mode/regulator_get_mode
*��������  : ���û�ȡregulatorģʽ
*�������  : regulator��Դ��modeҪ���õ�ģʽ
*����ֵ	   ���ɹ�:0
*			 ʧ��:����
*ע        : regulator��ʱֻ�ṩ���ء����õ�ѹ�ȹ��ܣ����û�ȡmode�����ݲ�ʵ��
*****************************************************************************/
extern int regulator_set_mode(struct regulator *regulator, unsigned int mode);
extern unsigned int regulator_get_mode(struct regulator *regulator);
/*****************************************************************************
*�� �� ��  : regulator_get_id
*��������  : ��ȡregulator id
*�������  : regulator��Դ
*����ֵ	   ���ɹ�:id
*			 ʧ��:����
*ע        : ��idΪregulator����pmic��id����Ψһ
*****************************************************************************/

extern int regulator_get_id(struct regulator *regulator);
#elif defined(__CMSIS_RTOS)

#endif
/******************************for regulator interface end****************************/

#ifdef __cplusplus
}
#endif

#endif
