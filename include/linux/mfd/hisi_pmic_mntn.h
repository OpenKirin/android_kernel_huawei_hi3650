/*
 * Header file for device driver Hi6421 PMIC
 *
 * Copyright (c) 2013 Linaro Ltd.
 * Copyright (C) 2011 Hisilicon.

 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef	__HISI_PMIC_MNTN_H
#define	__HISI_PMIC_MNTN_H

//�򿪹ر�smpl����
//SYS_CTRL1,0x0DC, np_smpl_open_en(bit 0), SMPL����ʹ��λ��
//enable:true, support smpl
extern int hisi_pmic_mntn_config_smpl(bool enable);

//config vsys_pwroff_abs_pd
//'SYS_CTRL0, 0x0DB,vsys_pwroff_abs_pd_mask(bit 0), vsysС��2.3vʱ�Ƿ��Զ��ػ�����λ��
//enable:true, 1�����Զ��ػ���
extern int hisi_pmic_mntn_config_vsys_pwroff_abs_pd(bool enable);

extern int hisi_pmic_mntn_vsys_pwroff_abs_pd_state(void);

#endif		/* __HISI_PMIC_MNTN_H */
