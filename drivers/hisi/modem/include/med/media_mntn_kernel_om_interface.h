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


#ifndef __MEDIA_MNTN_KERNEL_OM_INTERFACE_H__
#define __MEDIA_MNTN_KERNEL_OM_INTERFACE_H__


/******************************************************************************
  1 ����ͷ�ļ�����
******************************************************************************/


/******************************************************************************
  2 �궨��
******************************************************************************/

#define VIDEO_CPU_ID                (1)          /* ACPU */

#define DISP_FUNCTION_TYPE          (51)         /* IT1's type for SDT message */
#define VIDEO_FUNCTION_TYPE         (52)         /* IT2's type for SDT message */

#define MNTN_MSG_MAX_LENGTH         (4 * 1024) /*��ά�ɲ��ϱ���SDT����Ϣ��󳤶�*/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/* printk level */
typedef enum {
    MNTN_LOG_LEVEL_OFF  = 0,
    MNTN_LOG_LEVEL_ERR,
    MNTN_LOG_LEVEL_WARNING,
    MNTN_LOG_LEVEL_INFO,
    MNTN_LOG_LEVEL_DEBUG,
    MNTN_LOG_LEVEL_MAX
}mntn_print_level_e;

/* OM API ID used by IT2 */
typedef enum {
    MNTN_OM_FUNC_ID_REGISTER_REQ   = 0,    /* OM register request API */
    MNTN_OM_FUNC_ID_ADD_SN_TIME,           /* API of getting serial number and timestamp */
    MNTN_OM_FUNC_ID_MAX
}om_api_func_id_e;

/* ��ϢID����������EDCΪ��:
   config������Ϣ   ��Χ��0x2000~0x20FF
   event ID         ��Χ��0x2100~0x21FF
   reg ID           ��Χ��0x2200~0x22FF
   frame info ID    ��Χ��0x2300~0x23FF
   context ID       ��Χ��0x2400~0x24FF */
typedef enum {
    ID_VIDEO_MSG_INVALID          = 0x0000,

    /*Frame Data Config*/
    ID_FRAME_DATA_CFG_REQ     = 0x1000,
    ID_FRAME_DATA_CFG_CNF     = 0x1001,

    /*Video Dec Config*/
    ID_DEC_CFG_REQ            = 0x2000,   /*DECģ����Ϣ��������*/
    ID_DEC_CFG_CNF            = 0x2001,   /*DECģ����Ϣ����ȷ��*/
    ID_DEC_EVENT_IND          = 0x2100,   /*DECģ���¼��ϱ�*/
    ID_DEC_REG_IND            = 0x2200,   /*DECģ��Ĵ����ϱ�*/
    ID_DEC_FRAME_INFO_IND     = 0x2300,   /*DECģ��֡��Ϣ�ϱ�*/
    ID_DEC_CONTEXT_IND        = 0x2400,   /*DECģ����������Ϣ�ϱ�*/

    /*Video Enc Config*/
    ID_ENC_CFG_REQ            = 0x3000,
    ID_ENC_CFG_CNF            = 0x3001,
    ID_ENC_EVENT_IND          = 0x3100,
    ID_ENC_REG_IND            = 0x3200,
    ID_ENC_FRAME_INFO_IND     = 0x3300,
    ID_ENC_CONTEXT_IND        = 0x3400,

    /*VPP Config*/
    ID_VPP_CFG_REQ            = 0x4000,
    ID_VPP_CFG_CNF            = 0x4001,
    ID_VPP_EVENT_IND          = 0x4100,
    ID_VPP_REG_IND            = 0x4200,
    ID_VPP_FRAME_INFO_IND     = 0x4300,
    ID_VPP_CONTEXT_IND        = 0x4400,

    /*Camera Config*/
    ID_CAMERA_CFG_REQ         = 0x5000,
    ID_CAMERA_CFG_CNF         = 0x5001,
    ID_CAMERA_EVENT_IND       = 0x5100,
    ID_CAMERA_REG_IND         = 0x5200,
    ID_CAMERA_FRAME_INFO_IND  = 0x5300,
    ID_CAMERA_CONTEXT_IND     = 0x5400,

    ID_VIDEO_MSG_MAX
} mntn_video_prim_id_e;

typedef enum {
    ID_DISP_MSG_INVALID           = 0x0000,

    /*disp Edc Config*/
    ID_EDC_CFG_REQ            = 0x2000,   /*EDCģ����Ϣ��������*/
    ID_EDC_CFG_CNF            = 0x2001,   /*EDCģ����Ϣ����ȷ��*/
    ID_EDC_EVENT_IND          = 0x2100,   /*EDCģ���¼��ϱ�*/
    ID_EDC_REG_IND            = 0x2200,   /*EDCģ��Ĵ����ϱ�*/
    ID_EDC_FRAME_INFO_IND     = 0x2300,   /*EDCģ��֡��Ϣ�ϱ�*/
    ID_EDC_CONTEXT_IND        = 0x2400,   /*EDCģ����������Ϣ�ϱ�*/

    /* disp Gpu Config */
    ID_GPU_CFG_REQ            = 0x3000,   /*GPUģ����Ϣ��������*/
    ID_GPU_CFG_CNF            = 0x3001,   /*GPUģ����Ϣ����ȷ��*/
    ID_GPU_EVENT_IND          = 0x3100,   /*GPUģ���¼��ϱ�*/
    ID_GPU_REG_IND            = 0x3200,   /*GPUģ��Ĵ����ϱ�*/
    ID_GPU_FRAME_INFO_IND     = 0x3300,   /*GPUģ��֡��Ϣ�ϱ�*/
    ID_GPU_CONTEXT_IND        = 0x3400,   /*GPUģ����������Ϣ�ϱ�*/

    /* disp Hdmi Config */
    ID_HDMI_CFG_REQ           = 0x4000,   /*HDMIģ����Ϣ��������*/
    ID_HDMI_CFG_CNF           = 0x4001,   /*HDMIģ����Ϣ����ȷ��*/
    ID_HDMI_EVENT_IND         = 0x4100,   /*HDMIģ���¼��ϱ�*/
    ID_HDMI_REG_IND           = 0x4200,   /*HDMIģ��Ĵ����ϱ�*/
    ID_HDMI_FRAME_INFO_IND    = 0x4300,   /*HDMIģ��֡��Ϣ�ϱ�*/
    ID_HDMI_CONTEXT_IND       = 0x4400,   /*HDMIģ����������Ϣ�ϱ�*/

    ID_DISP_MSG_MAX
}mntn_disp_prim_id_e;

/******************************************************************************
  4 ȫ�ֱ�������
******************************************************************************/


/******************************************************************************
  5 ��Ϣͷ����
******************************************************************************/


/******************************************************************************
  6 ��Ϣ����
******************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/******************************************************************************
�ṹ��    : om_api_func
�ṹ˵��  : OM�ṩ��MNTNģ���API�ص���������
*******************************************************************************/
typedef void (*om_api_func)(void);

/******************************************************************************
�ṹ��    : om_req_packet
�ṹ˵��  : OM���͵�mntn����Ϣ����Ϣͷ����Ӧmntn_trace_req_t��Ϣ
*******************************************************************************/
typedef struct {
    unsigned char   func_type;             /* IT2's module ID */
    unsigned char   cpu_id;                /* reserved������ע��ֵ */
    unsigned short  length;                /* msg length after 'length' domain */
    unsigned char   feedback[4];           /* message content */
}om_req_packet;

/******************************************************************************
�ṹ��    : om_rsp_packet
�ṹ˵��  : mntn���͵�OM����Ϣ����Ϣͷ����Ӧmntn_trace_cnf_t��mntn_trace_ind_t��Ϣ
*******************************************************************************/
typedef struct {
    unsigned char   func_type;             /* IT2's module ID */
    unsigned char   cpu_id;                /* ACPU��������д1����ӦACPU */
    unsigned short  length;                /* msg length after 'length' domain */
    unsigned char   feedback[4];           /* message content */
}om_rsp_packet;

/******************************************************************************
�ṹ��    : om_rsp_func
�ṹ˵��  : OM�ص���������
*******************************************************************************/
typedef unsigned int (*om_rsp_func)(om_rsp_packet *rsp_packet, unsigned short length);

/******************************************************************************
�ṹ��    : om_request_func
�ṹ˵��  : mntn�ص���������
*******************************************************************************/
typedef void (*om_request_func)(om_req_packet *req_packet, om_rsp_func rsp_func);

/******************************************************************************
�ṹ��    : om_reg_request_func
�ṹ˵��  : OM�ṩ����ע��mntn�ص������ĺ�������
*******************************************************************************/
typedef unsigned int (*om_reg_request_func)(unsigned char module_id, om_request_func om_request);

/******************************************************************************
�ṹ��    : om_add_sn_time_func
�ṹ˵��  : OM�ṩ�Ļ�ȡSN��timestamp�Ļص���������
*******************************************************************************/
typedef void (*om_add_sn_time_func)(unsigned int *sn, unsigned int *timestamp);


/******************************************************************************
  8 UNION����
******************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

/* �ṩ��OM�Ľӿ� */
void mntn_om_rcv_cfg_req(om_req_packet *req_packet, om_rsp_func rsq_func);
void mntn_om_close_trace(void);
void mntn_proc_reg(om_api_func_id_e func_id, om_api_func func_name);


#endif /* __MEDIA_MNTN_KERNEL_OM_INTERFACE_H__ */

